#!/usr/bin/env python3

#
# This file is part of LiteX-Boards.
#
# Copyright (c) 2015-2019 Florent Kermarrec <florent@enjoy-digital.fr>
# Copyright (c) 2020 Antmicro <www.antmicro.com>
# SPDX-License-Identifier: BSD-2-Clause

import os
import argparse

from migen import *

from litex_boards.platforms import arty
from litex.build.xilinx.vivado import vivado_build_args, vivado_build_argdict

from litex.soc.cores.clock import *
from litex.soc.integration.soc import SoCRegion
from litex.soc.integration.soc_core import *
from litex.soc.integration.builder import *
from litex.soc.cores.led import LedChaser
from litex.soc.cores.gpio import GPIOTristate
from litex.soc.interconnect.csr import AutoCSR, CSRStorage
from litex.build.generic_platform import Pins, IOStandard, Subsignal

from litedram.modules import MT41K128M16
from litedram.phy import s7ddrphy

from liteeth.phy.mii import LiteEthPHYMII

from litespi.modules import S25FL128L
from litespi.opcodes import SpiNorFlashOpCodes as Codes
from litespi.phy.generic import LiteSPIPHY
from litespi import LiteSPI

DVI = False


"""
##https://github.com/projf/projf-explore/blob/master/graphics/fpga-graphics/xc7/arty.xdc
## Project F: FPGA Graphics - Arty A7-35T Board Constraints
## (C)2021 Will Green, open source hardware released under the MIT License
## VGA Pmod on Header JB/JC
##("pmodb", "E15 E16 D15 C15 J17 J18 K15 J15"),
##("pmodc", "U12 V12 V10 V11 U14 V14 T13 U13"),

set_property -dict {PACKAGE_PIN E15 IOSTANDARD LVCMOS33} [get_ports {vga_r[0]}];
set_property -dict {PACKAGE_PIN E16 IOSTANDARD LVCMOS33} [get_ports {vga_r[1]}];
set_property -dict {PACKAGE_PIN D15 IOSTANDARD LVCMOS33} [get_ports {vga_r[2]}];
set_property -dict {PACKAGE_PIN C15 IOSTANDARD LVCMOS33} [get_ports {vga_r[3]}];
set_property -dict {PACKAGE_PIN J17 IOSTANDARD LVCMOS33} [get_ports {vga_b[0]}];
set_property -dict {PACKAGE_PIN J18 IOSTANDARD LVCMOS33} [get_ports {vga_b[1]}];
set_property -dict {PACKAGE_PIN K15 IOSTANDARD LVCMOS33} [get_ports {vga_b[2]}];
set_property -dict {PACKAGE_PIN J15 IOSTANDARD LVCMOS33} [get_ports {vga_b[3]}];

set_property -dict {PACKAGE_PIN U12 IOSTANDARD LVCMOS33} [get_ports {vga_g[0]}];
set_property -dict {PACKAGE_PIN V12 IOSTANDARD LVCMOS33} [get_ports {vga_g[1]}];
set_property -dict {PACKAGE_PIN V10 IOSTANDARD LVCMOS33} [get_ports {vga_g[2]}];
set_property -dict {PACKAGE_PIN V11 IOSTANDARD LVCMOS33} [get_ports {vga_g[3]}];
set_property -dict {PACKAGE_PIN U14 IOSTANDARD LVCMOS33} [get_ports {vga_hsync}];
set_property -dict {PACKAGE_PIN V14 IOSTANDARD LVCMOS33} [get_ports {vga_vsync}];
"""

from litex.soc.interconnect import stream
from litex.soc.cores.video import video_data_layout
from litex.build.io import SDROutput, DDROutput
from litex.soc.cores.code_tmds import TMDSEncoder
class Open(Signal): pass
class VideoS7HDMI10to1Serializer_CUSTOM(Module):
    def __init__(self, data_i, data_o, clock_domain):
        # Note: 2 OSERDESE2 are coupled for 10:1 Serialization (8:1 Max with one).

        # Map Input Data to OSERDESE2 Master/Slave.
        data_m = Signal(8)
        data_s = Signal(8)
        self.comb += data_m[0:8].eq(data_i[:8]) # D1 to D8
        self.comb += data_s[2:4].eq(data_i[8:]) # D3 to D4

        # OSERDESE2 Master/Slave.
        shift = Signal(2)
        for data, serdes in zip([data_m, data_s], ["master", "slave"]):
            self.specials += Instance("OSERDESE2",
                # Parameters
                p_DATA_WIDTH     = 10,
                p_TRISTATE_WIDTH = 1,
                p_DATA_RATE_OQ   = "DDR",
                p_DATA_RATE_TQ   = "DDR",
                p_SERDES_MODE    = serdes.upper(),

                # Controls.
                i_OCE    = 1,
                i_TCE    = 0,
                i_RST    = ResetSignal(clock_domain),
                i_CLK    = ClockSignal("sys"),
                i_CLKDIV = ClockSignal(clock_domain),

                # Datas.
                **{f"i_D{n+1}": data[n] for n in range(8)},

                # Master/Slave shift in/out.
                i_SHIFTIN1  = shift[0] if serdes == "master" else 0,
                i_SHIFTIN2  = shift[1] if serdes == "master" else 0,
                o_SHIFTOUT1 = shift[0] if serdes == "slave"  else 0,
                o_SHIFTOUT2 = shift[1] if serdes == "slave"  else 0,

                # Output
                o_OQ = data_o if serdes == "master" else Open(),
            )
            
class VideoS7HDMIPHY_CUSTOM(Module):
    def __init__(self, pads, clock_domain="sys"):
        self.sink = sink = stream.Endpoint(video_data_layout)

        # # #

        # Always ack Sink, no backpressure.
        self.comb += sink.ready.eq(1)

        # Clocking + Differential Signaling.
        pads_clk = Signal()
        self.specials += DDROutput(i1=1, i2=0, o=pads_clk, clk=ClockSignal(clock_domain))
        self.specials += Instance("OBUFDS", i_I=pads_clk, o_O=pads.clk_p, o_OB=pads.clk_n)

        # Encode/Serialize Datas.
        for color in ["r", "g", "b"]:

            # TMDS Encoding.
            encoder = ClockDomainsRenamer(clock_domain)(TMDSEncoder())
            self.submodules += encoder
            self.comb += encoder.d.eq(getattr(sink, color))
            self.comb += encoder.c.eq(Cat(sink.hsync, sink.vsync) if color == "r" else 0)
            self.comb += encoder.de.eq(sink.de)

            # 10:1 Serialization + Differential Signaling.
            pad_o = Signal()
            serializer = VideoS7HDMI10to1Serializer_CUSTOM(
                data_i       = encoder.out,
                data_o       = pad_o,
                clock_domain = clock_domain,
            )
            self.submodules += serializer
            c2d   = {"r": 0, "g": 1, "b": 2}
            pad_p = getattr(pads, f"data{c2d[color]}_p")
            pad_n = getattr(pads, f"data{c2d[color]}_n")
            self.specials += Instance("OBUFDS", i_I=pad_o, o_O=pad_p, o_OB=pad_n)


# CRG ----------------------------------------------------------------------------------------------

class _CRG(Module):
    def __init__(self, platform, sys_clk_freq, with_rst=True):
        self.rst = Signal()
        self.clock_domains.cd_sys       = ClockDomain()
        self.clock_domains.cd_sys4x     = ClockDomain(reset_less=True)
        self.clock_domains.cd_sys4x_dqs = ClockDomain(reset_less=True)
        self.clock_domains.cd_idelay    = ClockDomain()
        #self.clock_domains.cd_eth       = ClockDomain()

        # # #

        self.submodules.pll = pll = S7PLL(speedgrade=-1)
        rst    = ~platform.request("cpu_reset") if with_rst else 0
        self.comb += pll.reset.eq(rst | self.rst)
        pll.register_clkin(platform.request("clk100"), 100e6)
        pll.create_clkout(self.cd_sys,       sys_clk_freq)
        pll.create_clkout(self.cd_sys4x,     4*sys_clk_freq)
        pll.create_clkout(self.cd_sys4x_dqs, 4*sys_clk_freq, phase=90)
        if sys_clk_freq > 100e6 and sys_clk_freq < 200e6:
           pll.create_clkout(self.cd_idelay,    sys_clk_freq)
        else:
            pll.create_clkout(self.cd_idelay,    200e6)

        if False:
            pll.create_clkout(self.cd_eth,       25e6)

        if DVI:
            video_clock = 100.e6/3
            self.clock_domains.cd_hdmi   = ClockDomain()
            pll.create_clkout(self.cd_hdmi,     video_clock, margin=1e-3)
            if int(video_clock*5) != sys_clk_freq:
              self.clock_domains.cd_hdmi5x = ClockDomain()
              pll.create_clkout(self.cd_hdmi5x, 5*video_clock, margin=1e-3)
            else:
              print(f"shared HDMI 5x clock @{sys_clk_freq/1e6}Mhz")
              #quit()
        else:
            video_clock = 25.e6 #"800x600@75Hz" =>  49.5e6, "640x480@60Hz" => 25.175e6 "800x600@60Hz"  => 40e6, "800x600@50Hz"=> 33.3..e6 1280x720@60Hz(RB) => 61.9e6 1024 46.42e6
            #self.clock_domains.cd_vga       = ClockDomain(reset_less=True)
            self.clock_domains.cd_vga       = ClockDomain(reset_less=False) #TODO: chech why True brings errors
            pll.create_clkout(self.cd_vga, video_clock, margin=1e-3)

        platform.add_false_path_constraints(self.cd_sys.clk, pll.clkin) # Ignore sys_clk to pll.clkin path created by SoC's rst.

        self.submodules.idelayctrl = S7IDELAYCTRL(self.cd_idelay)

        #self.comb += platform.request("eth_ref_clk").eq(self.cd_eth.clk)

# BaseSoC ------------------------------------------------------------------------------------------
#Code based on Blitter module from https://github.com/BrunoLevy/learn-fpga/blob/cb5a64997ca95fbd521656a82b75772a0cb0d76a/LiteX/boards/radiona_ulx3s_ex.py#L54
#(C) 2022 Bruno Levy, BSD 3-Clause License

class Blitter(Module, AutoCSR): #TODO: use a DMA of pixel size and another of full DRAM port width to optimize transfers
    def __init__(self,port):
        self._value = CSRStorage(port.data_width) #this fix is to match port size
        from litedram.frontend.dma import LiteDRAMDMAWriter
        dma_writer = LiteDRAMDMAWriter(port=port, fifo_depth=16, fifo_buffered=False, with_csr=True)
        self.submodules.dma_writer = dma_writer
        self.comb += dma_writer.sink.data.eq(self._value.storage)
        self.comb += dma_writer.sink.valid.eq(1)

class BaseSoC(SoCCore):
    def __init__(self, variant="a7-35", toolchain="vivado", sys_clk_freq=int(100e6), with_ethernet=False, with_etherbone=False, eth_ip="192.168.1.50", eth_dynamic_ip=False, with_jtagbone=True, with_mapped_flash=False, with_spi_flash = False,
        with_pmod_gpio = False, with_led_chaser = True, **kwargs):
        platform = arty.Platform(variant=variant, toolchain=toolchain)


        # SoCCore ----------------------------------------------------------------------------------
        SoCCore.__init__(self, platform, sys_clk_freq, **kwargs)

        # CRG --------------------------------------------------------------------------------------
        self.submodules.crg = _CRG(platform, sys_clk_freq, False) #, with_mapped_flash)

        # DDR3 SDRAM -------------------------------------------------------------------------------
        if not self.integrated_main_ram_size:
            self.submodules.ddrphy = s7ddrphy.A7DDRPHY(platform.request("ddram"),
                memtype        = "DDR3",
                nphases        = 4,
                sys_clk_freq   = sys_clk_freq)
            self.add_sdram("sdram",
                phy           = self.ddrphy,
                #module        = MT41K128M16(sys_clk_freq, "1:4" if int(sys_clk_freq) < int(200e6) else "1:2"),
                module        = MT41K128M16(sys_clk_freq, "1:4"),
                l2_cache_size = kwargs.get("l2_size", 8192)
            )

        # Ethernet / Etherbone ---------------------------------------------------------------------
        if with_ethernet or with_etherbone:
            self.submodules.ethphy = LiteEthPHYMII(
                clock_pads = self.platform.request("eth_clocks"),
                pads       = self.platform.request("eth"))
            if with_ethernet:
                self.add_ethernet(phy=self.ethphy, dynamic_ip=eth_dynamic_ip)
            if with_etherbone:
                self.add_etherbone(phy=self.ethphy, ip_address=eth_ip)

        # Jtagbone ---------------------------------------------------------------------------------
        if with_jtagbone:
            self.add_jtagbone()

        # Flash (through LiteSPI, experimental).
        if False: #with_mapped_flash:
            self.submodules.spiflash_phy  = LiteSPIPHY(platform.request("spiflash4x"), S25FL128L(Codes.READ_1_1_4))
            self.submodules.spiflash_mmap = LiteSPI(self.spiflash_phy, clk_freq=sys_clk_freq, mmap_endianness=self.cpu.endianness)
            spiflash_region = SoCRegion(origin=self.mem_map.get("spiflash", None), size=S25FL128L.total_size, cached=False)
            self.bus.add_slave(name="spiflash", slave=self.spiflash_mmap.bus, region=spiflash_region)

        # SPI Flash --------------------------------------------------------------------------------
        if False: #if with_spi_flash:
            from litespi.modules import S25FL128L
            from litespi.opcodes import SpiNorFlashOpCodes as Codes
            self.add_spi_flash(mode="4x", module=S25FL128L(Codes.READ_1_1_4), with_master=True)

        # Leds -------------------------------------------------------------------------------------
        if with_led_chaser:
            self.submodules.leds = LedChaser(
                pads         = platform.request_all("user_led"),
                sys_clk_freq = sys_clk_freq)

        # GPIOs ------------------------------------------------------------------------------------
        if with_pmod_gpio:
            #ext = arty.raw_pmod_io("pmoda")
            pa = [f"pmoda:{i:d}" for i in range(8)] #dummy bits required by software-only USB host
            pd = [f"pmodd:{i:d}" for i in range(8)] #USB device on PMOD-D (bits 8-16)
            ext = [("gpio", 0, Pins(" ".join(pa + pd)), IOStandard("LVCMOS33"))]
            platform.add_extension(ext)
            self.submodules.gpio = GPIOTristate(platform.request("gpio"))

        """
        if with_spi:
            #SPI pins and GPIO pins cannot be the same
            platform.add_extension([("spi0", 0,
                #Subsignal("cs_n", Pins("A3")), #A3=JP1:6
                #Subsignal("clk",  Pins("D3")), #D3=JP1:2
                #Subsignal("mosi", Pins("C3")), #C3=JP1:4
                #Subsignal("miso", Pins("A2")), #A2=JP1:5
                Subsignal("cs_n", Pins("A10")), #A10=ADC CS
                Subsignal("clk",  Pins("B14")), #B14=ADC CLK
                Subsignal("mosi", Pins("B10")), #B10=ADC SADDR
                Subsignal("miso", Pins("A9")),  # A9=ADC SDAT
                IOStandard("3.3-V LVTTL"))])

            self.add_spi_port(name="spi0");
        """
        with_video_framebuffer = True
        if with_video_framebuffer and DVI:
            platform.add_extension([("hdmi_out", 0, #DVI pmod breakout on pmod C (seems not working in others than C)
                Subsignal("data0_p", Pins("pmodc:0"), IOStandard("TMDS_33")),
                Subsignal("data0_n", Pins("pmodc:1"), IOStandard("TMDS_33")),
                Subsignal("data1_p", Pins("pmodc:2"), IOStandard("TMDS_33")),
                Subsignal("data1_n", Pins("pmodc:3"), IOStandard("TMDS_33")),
                Subsignal("data2_p", Pins("pmodc:4"), IOStandard("TMDS_33")),
                Subsignal("data2_n", Pins("pmodc:5"), IOStandard("TMDS_33")),
                Subsignal("clk_p",   Pins("pmodc:6"), IOStandard("TMDS_33")),
                Subsignal("clk_n",   Pins("pmodc:7"), IOStandard("TMDS_33")))])
            from litex.soc.cores.video import VideoS7HDMIPHY
            self.submodules.videophy = VideoS7HDMIPHY_CUSTOM(platform.request("hdmi_out"), clock_domain="hdmi")
            #self.add_video_framebuffer(phy=self.videophy, timings="640x480@60Hz", clock_domain="hdmi", format="rgb888") #FIXME: issue 1198
            self.add_video_framebuffer(phy=self.videophy, timings="800x600@60Hz", clock_domain="hdmi", format="rgb888") #FIXME: issue 1198
        elif with_video_framebuffer:
            platform.add_extension([("vga", 0, #PMOD VGA on pmod B & C
                Subsignal("hsync", Pins("U14")), #pmodc.4
                Subsignal("vsync", Pins("V14")), #pmodc.5
                Subsignal("r", Pins("E15 E16 D15 C15")), #pmodb.0-3
                Subsignal("g", Pins("U12 V12 V10 V11")), #pmodc.0-3
                Subsignal("b", Pins("J17 J18 K15 J15")), #pmodb.4-7
                IOStandard("LVCMOS33"))])
            from litex.soc.cores.video import VideoVGAPHY
            self.submodules.videophy = VideoVGAPHY(platform.request("vga"), clock_domain="vga")
            self.add_video_framebuffer(phy=self.videophy, timings="640x480@60Hz", clock_domain="vga", format="rgb888") #FIXME: issue 1198
            
        if with_video_framebuffer:
            port = self.sdram.crossbar.get_port(mode="write")
            #dma_width = 32 #FIXED, framebuffer is access DMA-only and not by software
            dma_width = port.data_width if port.data_width < 64 else 64 #using a wider bus optimizes access, uses software correction
            self.blitter = Blitter(port=self.sdram.crossbar.get_port(mode="write", data_width=dma_width))
            self.submodules.blitter = self.blitter
        
        #DMA
        with_dma = False
        if with_dma:
            from litex.soc.cores.dma import WishboneDMAReader
            from litex.soc.interconnect import wishbone
            dma_width = 32 #FIXME read memory width
            self.submodules.dma_reader = WishboneDMAReader(endianness="big", bus=wishbone.Interface(data_width=dma_width), with_csr=True)
            self.bus.add_master("dma_reader", self.dma_reader.bus)
            if True: #needed in Arty
                from litex.soc.cores.dma import WishboneDMAWriter
                self.submodules.dma_writer = WishboneDMAWriter(endianness="big", bus=wishbone.Interface(data_width=dma_width), with_csr=True)
                self.bus.add_master("dma_writer", self.dma_writer.bus)
            else:
                from litedram.frontend.dma import LiteDRAMDMAWriter
                port = self.sdram.crossbar.get_port("write")
                self.submodules.dma_writer = LiteDRAMDMAWriter(port, fifo_depth=16, with_csr=True)


            self.comb += self.dma_reader.source.connect(self.dma_writer.sink) #Connect Reader to Writer

# Build --------------------------------------------------------------------------------------------
# (DVI=False, 640x480@60Hz) ./digilent_arty.VIDEO.py --timer-uptime --uart-baudrate=1000000 --with-pmod-gpio --integrated-sram-size 32768 --sys-clk-freq=200e6     --cpu-type=vexriscv --cpu-variant=full --build
# (DVI=True,  800x600@50Hz) ./digilent_arty.VIDEO.py --timer-uptime --uart-baudrate=1000000 --with-pmod-gpio --integrated-sram-size 32768 --sys-clk-freq=166666666 --cpu-type=vexriscv --cpu-variant=full --build

def main():
    parser = argparse.ArgumentParser(description="LiteX SoC on Arty A7")
    parser.add_argument("--toolchain",           default="vivado",                 help="Toolchain use to build (default: vivado)")
    parser.add_argument("--build",               action="store_true",              help="Build bitstream")
    parser.add_argument("--load",                action="store_true",              help="Load bitstream")
    parser.add_argument("--variant",             default="a7-35",                  help="Board variant: a7-35 (default) or a7-100")
    parser.add_argument("--sys-clk-freq",        default=100e6,                    help="System clock frequency (default: 100MHz)")
    ethopts = parser.add_mutually_exclusive_group()
    ethopts.add_argument("--with-ethernet",      action="store_true",              help="Enable Ethernet support")
    ethopts.add_argument("--with-etherbone",     action="store_true",              help="Enable Etherbone support")
    parser.add_argument("--eth-ip",              default="192.168.1.50", type=str, help="Ethernet/Etherbone IP address")
    parser.add_argument("--eth-dynamic-ip",      action="store_true",              help="Enable dynamic Ethernet IP addresses setting")
    sdopts = parser.add_mutually_exclusive_group()
    sdopts.add_argument("--with-spi-sdcard",     action="store_true",              help="Enable SPI-mode SDCard support")
    sdopts.add_argument("--with-sdcard",         action="store_true",              help="Enable SDCard support")
    parser.add_argument("--sdcard-adapter",      type=str,                         help="SDCard PMOD adapter: digilent (default) or numato")
    parser.add_argument("--with-jtagbone",       action="store_true",              help="Enable Jtagbone support")
    parser.add_argument("--with-mapped-flash",   action="store_true",              help="Enable Memory Mapped Flash")
    parser.add_argument("--with-spi-flash",      action="store_true",              help="Enable SPI Flash (MMAPed)")
    parser.add_argument("--with-pmod-gpio",      action="store_true",              help="Enable GPIOs through PMOD") # FIXME: Temporary test.
    builder_args(parser)
    soc_core_args(parser)
    vivado_build_args(parser)
    args = parser.parse_args()

    assert not (args.with_etherbone and args.eth_dynamic_ip)

    soc = BaseSoC(
        variant        = args.variant,
        toolchain      = args.toolchain,
        sys_clk_freq   = int(float(args.sys_clk_freq)),
        with_ethernet  = args.with_ethernet,
        with_etherbone = args.with_etherbone,
        eth_ip         = args.eth_ip,
        eth_dynamic_ip = args.eth_dynamic_ip,
        with_jtagbone  = args.with_jtagbone,
        with_mapped_flash = args.with_mapped_flash,
        with_spi_flash = args.with_spi_flash,
        with_pmod_gpio = args.with_pmod_gpio,
        **soc_core_argdict(args)
    )
    if args.sdcard_adapter == "numato":
        soc.platform.add_extension(arty._numato_sdcard_pmod_io)
    else:
        soc.platform.add_extension(arty._sdcard_pmod_io)
    if args.with_spi_sdcard:
        soc.add_spi_sdcard()
    if args.with_sdcard:
        soc.add_sdcard()
    builder = Builder(soc, **builder_argdict(args))
    builder_kwargs = vivado_build_argdict(args) if args.toolchain == "vivado" else {}
    builder.build(**builder_kwargs, run=args.build)

    if args.load:
        prog = soc.platform.create_programmer()
        prog.load_bitstream(os.path.join(builder.gateware_dir, soc.build_name + ".bit"))

if __name__ == "__main__":
    main()
