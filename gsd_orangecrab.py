#!/usr/bin/env python3

#
# This file is part of LiteX-Boards.
#
# Copyright (c) Greg Davill <greg.davill@gmail.com>
# Copyright (c) 2024 Victor Suarez Rovere <suarezvictor@gmail.com>
# SPDX-License-Identifier: BSD-2-Clause

import os
import sys

from migen import *
from migen.genlib.misc import WaitTimer
from migen.genlib.resetsync import AsyncResetSynchronizer

from litex.gen import LiteXModule

from litex_boards.platforms import gsd_orangecrab

from litex.soc.cores.clock import *
from litex.soc.integration.soc_core import *
from litex.soc.integration.builder import *
from litex.soc.cores.led import LedChaser
from litex.soc.cores.gpio import GPIOTristate #required for USB host
from litex.soc.cores.video import video_timings

from litedram.modules import MT41K64M16, MT41K128M16, MT41K256M16, MT41K512M16
from litedram.phy import ECP5DDRPHY

from litex.build.generic_platform import Pins, IOStandard, Subsignal, Drive, Misc
from litex.soc.interconnect.csr import AutoCSR, CSRStorage
from litex.soc.interconnect import stream, wishbone
from litex.soc.interconnect.csr import CSRStatus

DVI = True
FPDLINK = False

from litex.build.io import SDROutput, DDROutput
from litex.soc.cores.code_tmds import TMDSEncoder


from litex.soc.cores.video import VideoTimingGenerator, VideoFrameBuffer, video_timing_layout, _dvi_c2d, video_data_layout

"""
NOTE: NOT TESTED IN ORANGECRAB!

HIGH RESOLUTION VIDEO DRIVER USING 16-bit SDRAM CHIP (1024x768@32bpp and 1280x720@16bpp)
Based on DE0-Nano board (Cyclone IV FPGA with a 143Mhz capable SDRAM, 16-bit bus)
HDMI output using LVDS outputs + decoupling capacitors

1024x768 characteristics:
===============================
Name: "1024x768@50Hz(RB)"
Pixel clock: 46.42MHz
Color depth: 32-bit (RGBA888)
Vertical rate: 50Hz
Sync polarity*: -hsync -vsync
Sys clock: 72.2MHz
SDRAM clock: 144.4MHz
Build Command: ./terasic_de0nano.py --with-video-framebuffer --sys-clk-freq=72222222 --sdram-rate=1:2  --build


1280x720 characteristics:
===============================
Name: "1280x720@60Hz(RB)"
Pixel clock: 61.9 MHz
Color depth: 16-bit (RGB565)
Vertical rate: 60Hz
Sync polarity: -hsync -vsync
Sys clock: 100MHz
SDRAM clock: 100MHz
Build command: ./terasic_de0nano.py --with-video-framebuffer --sys-clk-freq=100000000 --build 


NOTES:
===============================

Timings are based on CVT standard with Reduced Blanking Time (put less pressure in pixel clock)
The timings are obtained by linux "cvt" tool, for example:
#cvt -r 1024 768 60
outputs:
Modeline "1024x768R"   56.00  1024 1072 1104 1184  768 771 775 790 +hsync -vsync

NOTE: besides +hsync is specified, testing shows we beed -hsync
Pixel clock is adjusted to 46.42MHz (instead of 56Mhz) to put less pressure on SDRAM and to mantain < 2/3 rate with SDRAM clock (unavoidable in current design)
The result is that framerate gets to 50Hz and not to the 60Hz standard. Anyways most (if not all) monitors will be happy to show 50Hz Vsync if they're capable of 60Hz.
The 50Hz obtained is not exact but very close, maybe output is 49ish-Hz (pixel clock is set to 46.42 instead of 46.77). To more exact adjusting, some more PLL trickery would be needed or blanking timings could be tweaked to sightly off-standard values. In regards to 1280x720, the pixel clock is also not exact but very close (61.9 is used instead of 64.02). Same criteria applies.

In case of 1280x720, the SDRAM is not maxed to their utmost clock capacity since that would require the 1:2 logic but in that case pixel clock would be too close to sys clock. Some trickery with clock domain crossig would be needed to achieve higher SDRAM clock rates (HIGHLY DESIRED FEATURE).

"""
#hd_rb_timings = ("1280x720@60Hz(RB)", {
#        "pix_clk"       : 64e6,
#        "v_blanking"    : 21,

hd50_rb_timings = ("1280x720@50Hz(RB)", {
        "pix_clk"       : 60e6,
        "h_active"      : 1280,
        "h_blanking"    : 160,
        "h_sync_offset" : 48,
        "h_sync_width"  : 32,
        "v_active"      : 720,
        "v_blanking"    : 111, #FIXME: send to horizontal blankling
        "v_sync_offset" : 3,
        "v_sync_width"  : 5,
})

hd_rb2_timings = ("1280x720@50Hz(RB2)", {
        "pix_clk"       : 50.388e6,
        "h_active"      : 1280,
        "h_blanking"    : 80,
        "h_sync_offset" : 8,
        "h_sync_width"  : 32,
        "v_active"      : 720,
        "v_blanking"    : 7,
        "v_sync_offset" : 3,
        "v_sync_width"  : 8,
})

_1024x768_rb_timings = ("1024x768@60Hz(RB)", {
        "pix_clk"       : 56e6, 
        "h_active"      : 1024,
        "h_blanking"    : 160,
        "h_sync_offset" : 48,
        "h_sync_width"  : 32,
        "v_active"      : 768,
        "v_blanking"    : 22,
        "v_sync_offset" : 3,
        "v_sync_width"  : 4,
})

#10.1" M101NWT2 R2, proven compatible with and PC monitor
lvds1024x600_timings = ("1024x600@60Hz", {
        "pix_clk"       : 51.45e6, #44.4 to 65.2
        "h_active"      : 1024,
        "h_blanking"    : 320, #296 a 338 (320 VESA 1024)
        "h_sync_offset" : 136,
        "h_sync_width"  : 24,
        "v_active"      : 600,
        "v_blanking"    : 38, #12 to 38 (38 VESA 768p)
        "v_sync_offset" : 3,
        "v_sync_width"  : 6,
})

#14" LP140WH4(TL)(A1), proven compatible with PC monitor and 10.1" 1024x600 M101NWT2 R2
lvds1366x768_timings = ("1366x768@50Hz", {
        "pix_clk"       : 57.14e6,
        "h_active"      : 1366,
        "h_blanking"    : 32+(32+5)+34, #front, sync, back
        "h_sync_offset" : 32,
        "h_sync_width"  : 32+5,
        "v_active"      : 768,
        "v_blanking"    : 2+(2+2)+4, #front, sync, back
        "v_sync_offset" : 2,
        "v_sync_width"  : 2+2,
})

class VideoHDMI10to1Serializer(LiteXModule):
    def __init__(self, data_i, data_o, clock_domain, clock_domain5x):
        # Clock Domain Crossing.
        self.cdc = stream.ClockDomainCrossing([("data", 10)], cd_from=clock_domain, cd_to=clock_domain5x)
        self.comb += self.cdc.sink.valid.eq(1)
        self.comb += self.cdc.sink.data.eq(data_i)

        # 10:2 Gearbox.
        self.gearbox = ClockDomainsRenamer(clock_domain5x)(stream.Gearbox(i_dw=10, o_dw=2, msb_first=False))
        self.comb += self.cdc.source.connect(self.gearbox.sink)

        # 2:1 Output DDR.
        self.comb += self.gearbox.source.ready.eq(1)
        self.specials += DDROutput(
            clk = ClockSignal(clock_domain5x),
            i1  = self.gearbox.source.data[0],
            i2  = self.gearbox.source.data[1],
            o   = data_o,
        )

class VideoHDMIPHY(LiteXModule):
    def __init__(self, pads, clock_domain="sys", clock_domain5x="sys5x", pn_swap=[]):
        self.sink = sink = stream.Endpoint(video_data_layout)

        # # #

        # Determine driven polarities:
        # - p only for True/Pseudo Differential.
        # - p and n for Fake Differential.
        drive_pols = []
        for pol in ["p", "n"]:
            if hasattr(pads, f"clk_{pol}"):
                drive_pols.append(pol)

        # Always ack Sink, no backpressure.
        self.comb += sink.ready.eq(1)

        # Clocking + Pseudo Differential Signaling.
        for pol in drive_pols:
            self.specials += DDROutput(
                i1  = {"p" : 1, "n" : 0}[pol],
                i2  = {"p" : 0, "n" : 1}[pol],
                o   = getattr(pads, f"clk_{pol}"),
                clk = ClockSignal(clock_domain),
            )

        # Encode/Serialize Datas.
        for pol in drive_pols:
            for color, channel in _dvi_c2d.items():
                # TMDS Encoding.
                encoder = ClockDomainsRenamer(clock_domain)(TMDSEncoder())
                self.add_module(name=f"{color}_encoder_{pol}", module=encoder)
                self.comb += encoder.d.eq(getattr(sink, color))
                self.comb += encoder.c.eq(Cat(sink.hsync, sink.vsync) if channel == 0 else 0)
                self.comb += encoder.de.eq(sink.de)

                # 10:1 Serialization + Pseudo Differential Signaling.
                data_i = encoder.out if color not in pn_swap else ~encoder.out
                data_o = getattr(pads, f"data{channel}_{pol}")
                serializer = VideoHDMI10to1Serializer(
                    data_i       = {"p":data_i, "n": ~data_i}[pol],
                    data_o       = data_o,
                    clock_domain = clock_domain,
                    clock_domain5x = clock_domain5x,
                )
                self.add_module(name=f"{color}_serializer_{pol}", module=serializer)

class VideoFPDLINKPHY(LiteXModule):
    def __init__(self, pads, clock_domain="sys", clock_domain3p5x="sys3p5x", pn_swap=[]):
        self.sink = sink = stream.Endpoint(video_data_layout)

        # # #

        # Always ack Sink, no backpressure.
        self.comb += sink.ready.eq(1)
        r, g, b, de, hs, vs = sink.r, sink.g, sink.b, sink.de, sink.hsync, sink.vsync

        def xdr7(out_q, in_d, invert=False):
           d = in_d if not invert else ~in_d
           self.specials += Instance("ODDR71B",
               i_SCLK=ClockSignal(clock_domain),
               i_ECLK=ClockSignal(clock_domain3p5x), #3.5x speed of SCLK
               i_RST=Constant(0),
               i_D0=d[0], i_D1=d[1], i_D2=d[2], i_D3=d[3], i_D4=d[4], i_D5=d[5], i_D6=d[6],
               o_Q=out_q
           )

        #r = Constant(127, 8)
        #g = Constant(255, 8)
        #b = Constant(64, 8)
        tx0 = Cat(g[2], r[7], r[6], r[5], r[4], r[3], r[2])
        tx1 = Cat(b[3], b[2], g[7], g[6], g[5], g[4], g[3])
        tx2 = Cat(de, vs, hs, b[7], b[6], b[5], b[4])
        clk = Constant(0b1100011, 7)
        
        invert = [x in pn_swap for x in "012c"]
        xdr7(pads.tx0, tx0, invert=invert[0])
        xdr7(pads.tx1, tx1, invert=invert[1])
        xdr7(pads.tx2, tx2, invert=invert[2])
        xdr7(pads.clk, clk, invert=invert[3])
        

class VideoFrameBufferN(Module, AutoCSR):
    """Video FrameBuffer"""
    def __init__(self, dram_port, hres=800, vres=600, base=0x00000000, fifo_depth=65536, clock_domain="sys", clock_faster_than_sys=False, bit_depth = 32):
        self.vtg_sink  = vtg_sink = stream.Endpoint(video_timing_layout)
        self.source    = source   = stream.Endpoint(video_data_layout)
        self.underflow = Signal()

        # # #

        # Video DMA.
        from litedram.frontend.dma import LiteDRAMDMAReader
        self.submodules.dma = LiteDRAMDMAReader(dram_port, fifo_depth=fifo_depth//(dram_port.data_width//8), fifo_buffered=True)
        self.dma.add_csr(
            default_base   = base,
            default_length = hres*vres*bit_depth//8,
            default_enable = 0,
            default_loop   = 1
        )

        # If DRAM Data Width > N-bit and Video clock is faster than sys_clk:
        if (dram_port.data_width > bit_depth) and clock_faster_than_sys:
            # Do Clock Domain Crossing first...
            self.submodules.cdc = stream.ClockDomainCrossing([("data", dram_port.data_width)], cd_from="sys", cd_to=clock_domain)
            self.comb += self.dma.source.connect(self.cdc.sink)
            # ... and then Data-Width Conversion.
            if bit_depth > 16:
              self.submodules.conv = stream.Converter(dram_port.data_width, bit_depth)
              self.comb += self.cdc.source.connect(self.conv.sink)
              video_pipe_source = self.conv.source
            else:
              video_pipe_source = self.cdc.source #direct 1:1 connection

        # Elsif DRAM Data Widt < N-bit or Video clock is slower than sys_clk:
        else:
            # Do Data-Width Conversion first...
            if bit_depth > 16:
              self.submodules.conv = stream.Converter(dram_port.data_width, bit_depth)
              self.comb += self.dma.source.connect(self.conv.sink)
              # ... and then Clock Domain Crossing.
              self.submodules.cdc = stream.ClockDomainCrossing([("data", bit_depth)], cd_from="sys", cd_to=clock_domain)
              self.comb += self.conv.source.connect(self.cdc.sink)
              self.comb += If(dram_port.data_width < 32, # FIXME.
                self.cdc.sink.data[ 0: 8].eq(self.conv.source.data[16:24]),
                self.cdc.sink.data[16:24].eq(self.conv.source.data[ 0: 8]),
              )
              video_pipe_source = self.cdc.source
            else:
              # Do Clock Domain Crossing first...
              self.submodules.cdc = stream.ClockDomainCrossing([("data", dram_port.data_width)], cd_from="sys", cd_to=clock_domain)
              self.comb += self.dma.source.connect(self.cdc.sink)
              video_pipe_source = self.cdc.source #direct 1:1 connection

        # Video Generation.
        self.comb += [
            vtg_sink.ready.eq(1),
            If(vtg_sink.valid & vtg_sink.de,
                video_pipe_source.connect(source, keep={"valid", "ready"}),
                vtg_sink.ready.eq(source.valid & source.ready),

            ),
            vtg_sink.connect(source, keep={"de", "hsync", "vsync"}),
            source.r.eq(video_pipe_source.data[16:24] if bit_depth > 16 else Cat(Signal(3, reset = 0), video_pipe_source.data[11:16])),
            source.g.eq(video_pipe_source.data[ 8:16] if bit_depth > 16 else Cat(Signal(2, reset = 0), video_pipe_source.data[ 5:11])),
            source.b.eq(video_pipe_source.data[ 0: 8] if bit_depth > 16 else Cat(Signal(3, reset = 0), video_pipe_source.data[ 0: 5])),
        ]

        # Underflow.
        self.comb += self.underflow.eq(~source.valid)

class VideoGenericPHY(LiteXModule):
    def __init__(self, pads, clock_domain="sys", with_clk_ddr_output=True):
        self.sink = sink = stream.Endpoint(video_data_layout)

        # # #

        # Always ack Sink, no backpressure.
        self.comb += sink.ready.eq(1)

        # Drive Clk.
        if hasattr(pads, "clk"):
            if with_clk_ddr_output:
                self.specials += DDROutput(i1=1, i2=0, o=pads.clk, clk=ClockSignal(clock_domain))
            else:
                self.comb += pads.clk.eq(ClockSignal(clock_domain))

        # Drive Controls.
        if hasattr(pads, "de"):
            self.specials += SDROutput(i=sink.de, o=pads.de, clk=ClockSignal(clock_domain))
        if hasattr(pads, "hsync_n"):
            self.specials += SDROutput(i=~sink.hsync, o=pads.hsync_n, clk=ClockSignal(clock_domain))
        else:
            self.specials += SDROutput(i=sink.hsync,  o=pads.hsync,   clk=ClockSignal(clock_domain))

        if hasattr(pads, "vsync_n"):
            self.specials += SDROutput(i=~sink.vsync, o=pads.vsync_n, clk=ClockSignal(clock_domain))
        else:
            self.specials += SDROutput(i=sink.vsync,  o=pads.vsync,   clk=ClockSignal(clock_domain))

        # Drive Datas.
        cbits  = len(pads.r)
        cshift = (8 - cbits)
        for i in range(cbits):
            # VGA monitors interpret minimum value as black so ensure data is set to 0 during blanking.
            self.specials += SDROutput(i=sink.r[cshift + i] & sink.de, o=pads.r[i], clk=ClockSignal(clock_domain))
            self.specials += SDROutput(i=sink.g[cshift + i] & sink.de, o=pads.g[i], clk=ClockSignal(clock_domain))
            self.specials += SDROutput(i=sink.b[cshift + i] & sink.de, o=pads.b[i], clk=ClockSignal(clock_domain))

# VGA (Generic).

class VideoVGAPHY(VideoGenericPHY): pass
# CRG ----------------------------------------------------------------------------------------------

class _CRGSDRAM(LiteXModule):
    def __init__(self, platform, sys_clk_freq, video_clock, with_usb_pll=False):
        self.rst = Signal()
        self.cd_init     = ClockDomain()
        self.cd_por      = ClockDomain()
        self.cd_sys      = ClockDomain()
        self.cd_sys2x    = ClockDomain()
        self.cd_sys2x_i  = ClockDomain()

        # # #

        self.stop  = Signal()
        self.reset = Signal()

        # Clk / Rst
        clk48 = platform.request("clk48")
        rst_n = platform.request("usr_btn", loose=True)
        if rst_n is None: rst_n = 1

        # Power on reset
        por_count = Signal(16, reset=2**16-1)
        por_done  = Signal()
        self.comb += self.cd_por.clk.eq(clk48)
        self.comb += por_done.eq(por_count == 0)
        self.sync.por += If(~por_done, por_count.eq(por_count - 1))

        # PLL
        sys2x_clk_ecsout = Signal()
        self.pll = pll = ECP5PLL()
        self.comb += pll.reset.eq(~por_done | ~rst_n | self.rst)
        pll.register_clkin(clk48, 48e6)
        pll.create_clkout(self.cd_sys2x_i, 2*sys_clk_freq)
        pll.create_clkout(self.cd_init, 24e6)
        self.specials += [
            Instance("ECLKBRIDGECS",
                i_CLK0   = self.cd_sys2x_i.clk,
                i_SEL    = 0,
                o_ECSOUT = sys2x_clk_ecsout),
            Instance("ECLKSYNCB",
                i_ECLKI = sys2x_clk_ecsout,
                i_STOP  = self.stop,
                o_ECLKO = self.cd_sys2x.clk),
            Instance("CLKDIVF",
                p_DIV     = "2.0",
                i_ALIGNWD = 0,
                i_CLKI    = self.cd_sys2x.clk,
                i_RST     = self.reset,
                o_CDIVX   = self.cd_sys.clk),
            AsyncResetSynchronizer(self.cd_sys, ~pll.locked | self.reset),
        ]

        # USB PLL
        if with_usb_pll:
            self.cd_usb_12 = ClockDomain()
            self.cd_usb_48 = ClockDomain()
            usb_pll = ECP5PLL()
            self.submodules += usb_pll
            self.comb += usb_pll.reset.eq(~por_done)
            usb_pll.register_clkin(clk48, 48e6)
            usb_pll.create_clkout(self.cd_usb_48, 48e6)
            usb_pll.create_clkout(self.cd_usb_12, 12e6)
            
            
        # Video PLL
        vga_pll = ECP5PLL()
        self.submodules += vga_pll
        self.comb += vga_pll.reset.eq(~por_done)
        vga_pll.register_clkin(clk48, 48e6)
        if DVI:
            self.cd_hdmi   = ClockDomain()
            self.cd_hdmi5x = ClockDomain()
            vga_pll.create_clkout(self.cd_hdmi,     video_clock, margin=1e-2)
            vga_pll.create_clkout(self.cd_hdmi5x, 5*video_clock, margin=1e-2) #ECP5 max: 400MHz
        elif FPDLINK:
            self.cd_fpdlink   = ClockDomain()
            self.cd_fpdlink3p5x = ClockDomain()
            vga_pll.create_clkout(self.cd_fpdlink,        video_clock, margin=1e-3)
            vga_pll.create_clkout(self.cd_fpdlink3p5x, 3.5*video_clock, margin=1e-3)
        else: 
            self.cd_vga  = ClockDomain()
            vga_pll.create_clkout(self.cd_vga, video_clock)
        

        # FPGA Reset (press usr_btn for 1 second to fallback to bootloader)
        reset_timer = WaitTimer(int(48e6))
        reset_timer = ClockDomainsRenamer("por")(reset_timer)
        self.submodules += reset_timer
        self.comb += reset_timer.wait.eq(~rst_n)
        self.comb += platform.request("rst_n").eq(~reset_timer.done)


#Code based on Blitter module from https://github.com/BrunoLevy/learn-fpga/blob/cb5a64997ca95fbd521656a82b75772a0cb0d76a/LiteX/boards/radiona_ulx3s_ex.py#L54
#(C) 2022 Bruno Levy, BSD 3-Clause License

#FIXME: use accelerators from GPU2D project

class Blitter(Module, AutoCSR): #TODO: use a DMA of pixel size and another of full DRAM port width to optimize transfers
    def __init__(self,port):
        self._value = CSRStorage(port.data_width) #this fix is to match port size
        from litedram.frontend.dma import LiteDRAMDMAWriter
        dma_writer = LiteDRAMDMAWriter(port=port, fifo_depth=16, fifo_buffered=False, with_csr=True)
# BaseSoC ------------------------------------------------------------------------------------------
        self.submodules.dma_writer = dma_writer
        self.comb += dma_writer.sink.data.eq(self._value.storage)
        self.comb += dma_writer.sink.valid.eq(1)


# BaseSoC ------------------------------------------------------------------------------------------

class BaseSoC(SoCCore):
    def __init__(self, revision="0.1", device="25F", sdram_device="MT41K64M16",
                 sys_clk_freq=int(100e6), toolchain="trellis", with_led_chaser=False, with_pmod_gpio=True, **kwargs):
        platform = gsd_orangecrab.Platform(revision=revision, device=device ,toolchain=toolchain)

        # CRG --------------------------------------------------------------------------------------
        crg_cls      = _CRGSDRAM if kwargs.get("integrated_main_ram_size", 0) == 0 else _CRG
        
        #timings = hd50_rb_timings # works with 100mhz sys
        #timings = hd_rb2_timings #doesn't work
        #timings = _1024x768_rb_timings #48MHz pix produces 51Hz, 112.5e6/2 produces 61Hz
        ###############################################
        if FPDLINK:
            timings = lvds1366x768_timings #lvds1024x600_timings
            timings[1]["pix_clk"] *= 30.0/50.0 #make display refresh slower (works up to 30 Hz)
        else:
            res = "800x600@60Hz"
            timings = (res, video_timings[res])
        ###############################################
        
        self.crg = crg_cls(platform, sys_clk_freq, timings[1]["pix_clk"], with_usb_pll=True)

        # SoCCore ----------------------------------------------------------------------------------
        # Defaults to USB ACM through ValentyUSB.
        #kwargs["uart_name"] = "usb_acm" #set this to get USB ACM serial, or use --uart-name=usb_acm 
        platform.add_extension(gsd_orangecrab.feather_serial) #rx=GPIO:0 & tx=GPIO:1
        SoCCore.__init__(self, platform, sys_clk_freq, ident="LiteX SoC on OrangeCrab", **kwargs)

        # DDR3 SDRAM -------------------------------------------------------------------------------
        if not self.integrated_main_ram_size:
            available_sdram_modules = {
                "MT41K64M16":  MT41K64M16,
                "MT41K128M16": MT41K128M16,
                "MT41K256M16": MT41K256M16,
                "MT41K512M16": MT41K512M16,
            }
            sdram_module = available_sdram_modules.get(sdram_device)

            ddram_pads = platform.request("ddram")
            self.ddrphy = ECP5DDRPHY(
                pads         = ddram_pads,
                sys_clk_freq = sys_clk_freq, #calculates cl/cwl latencies
                dm_remapping = {0:1, 1:0},
                cmd_delay    = 0 if sys_clk_freq > 64e6 else 100)
            self.ddrphy.settings.rtt_nom = "disabled"
            if hasattr(ddram_pads, "vccio"):
                self.comb += ddram_pads.vccio.eq(0b111111)
            if hasattr(ddram_pads, "gnd"):
                self.comb += ddram_pads.gnd.eq(0)
            self.comb += self.crg.stop.eq(self.ddrphy.init.stop)
            self.comb += self.crg.reset.eq(self.ddrphy.init.reset)

            #calculates tRP tRCD tWR tREFI tRFC tWTR tFAW tCCD tRRD tRC tRAS tZQCS
            

            from litedram.core.controller import ControllerSettings
            bank_byte_alignment = 0x1000000 #all HD framebuffers in same bank (this provides about 4% speed gains con buffer copy)
            controller_settings = ControllerSettings(
            	address_mapping="ROW_BANK_COL", #ROW_BANK_COL or BANK_ROW_COL (latter is not supported in LiteX)
            	bank_byte_alignment = bank_byte_alignment 
            	) 
            self.add_sdram("sdram", # actual chip MT41K64M16TW-107:J TR / 1.07ns @ CL = 13 (DDR3-1866, 8 internal banks, Fixed burst length (BL) of 8 and burst chop (BC) of 4)
                phy           = self.ddrphy,
                #module        = sdram_module(sys_clk_freq/sdram_overclock, "1:2", speedgrade="1600"), #overclocked version
                module        = sdram_module(sys_clk_freq, "1:2", speedgrade="1600"),
                l2_cache_size = kwargs.get("l2_size", 8192),
                controller_settings = controller_settings
            )
            self.add_constant("BANK_BYTE_ALIGNMENT", bank_byte_alignment)
            
            print(self.sdram.controller.settings.address_mapping)
            # MT41K64M16TW (1Gb) row: 8K A[12:0] / bank: 8 BA[2:0] / Column: 1K A[9:0] / Page size: 2KB

        # Leds -------------------------------------------------------------------------------------
        if with_led_chaser:
            self.leds = LedChaser(
                pads         = platform.request_all("user_led"),
                sys_clk_freq = sys_clk_freq)
                
                
        
        # GPIO -------------------------------------------------------------------------------------
        if with_pmod_gpio:
            gpio_l = "F1 H1 A8 H2 C8 B8 B10 B9" #bits 0-7 on NORTH connector (outer side): AUX_3+/AUX_3-/IO_11/IO_12/IO_9/IO_10/IO_5/IO_6 (dummy for USB host)
            gpio_h = "R17 J2 C10 C9 A10 C11 A11 B11" #(bits 8-16) USB device on USB and others: IO_SCK/IO_13/IO_SDA/IO_SCL/SPI_0/SPI_1/USBH_D+/USBH_D-
            platform.add_extension([("gpio", 0, Pins(gpio_l + " " + gpio_h), IOStandard("LVCMOS33"))])
            self.submodules.gpio = GPIOTristate(platform.request("gpio"))
            self.add_constant("LITEX_SOFTUSB_HOST");

        
        # SD card -------------------------------------------------------------------------------------
        with_sdcard = True
        if with_sdcard:
            """
            platform.add_extension([("sdcard", 0,
                Subsignal("clk",  Pins("K1"), IOStandard("LVCMOS33"), Misc("SLEWRATE=FAST")),
                Subsignal("cmd",  Pins("K2"), IOStandard("LVCMOS33"), Misc("SLEWRATE=FAST"), Misc("PULLMODE=UP")),
                Subsignal("data", Pins("J1 K3 L3 M1"), IOStandard("LVCMOS33"), Misc("SLEWRATE=FAST"), Misc("PULLMODE=UP")),
                )])
            self.add_sdcard(mode="read") #FIXME: if read+write is enabled, ECP5 25F runs out of DP16KD block-ram resources (57 required of 56 max in current test)
            """
            self.add_spi_sdcard()


        with_video_framebuffer = True
        if with_video_framebuffer and DVI:
        	#from litex.soc.cores.video import VideoHDMIPHY
        	platform.add_extension([("hdmi_out", 0, #can use GND and just 4 more wires
                #TOP TO BOTTOM
                Subsignal("data2_p", Pins("N4"), IOStandard("LVCMOS33D"), Misc("DRIVE=8"), Misc("SLEWRATE=FAST")), #aux0-=N3, aux0+=N4 INVERT
                Subsignal("data1_p", Pins("H3"), IOStandard("LVCMOS33D"), Misc("DRIVE=8"), Misc("SLEWRATE=FAST")), #aux1-=G3, aux1+=H3 INVERT
                Subsignal("data0_p", Pins("F2"), IOStandard("LVCMOS33D"), Misc("DRIVE=8"), Misc("SLEWRATE=FAST")), #aux2-=G1, aux2+=F2 INVERT
                Subsignal("clk_p",   Pins("F4"), IOStandard("LVCMOS33D"), Misc("DRIVE=8"), Misc("SLEWRATE=FAST")), #aux6+=F4, aux6-=F3
                )])
                #Organgecrab 0.1: clk "F4" AUX 6 (bottom), "F2 H3 N4" #0.1 AUX 2, 1, 0 => D0/D1/D2 (bottom to top)
        	hdmi_domain = "hdmi"
        	self.submodules.videophy = VideoHDMIPHY(platform.request("hdmi_out"), clock_domain=hdmi_domain, clock_domain5x="hdmi5x", pn_swap="rgb")
        	#self.add_video_terminal2(phy=self.videophy, timings=timings, clock_domain=hdmi_domain)
            #self.add_video_framebuffer3(phy=self.videophy, timings=timings, clock_domain=vga_cd, format="rgb565")
        	fifo_depth = timings[1]["h_active"] + timings[1]["h_blanking"] #one line
        	self.add_video_framebuffer2(phy=self.videophy, timings=timings, clock_domain=hdmi_domain, format="rgb888", fifo_depth=fifo_depth*5) #ok
        	
        elif with_video_framebuffer and FPDLINK:
        	"""
        	platform.add_extension([("fpdlink_out", 0, #can use GND and just 4 more wires
                #TOP TO BOTTOM
        	Subsignal("clk", Pins("N4"), IOStandard("LVDS25E"), Misc("SLEWRATE=FAST")), #aux0-=N3, aux0+=N4 INVERT
        	Subsignal("tx2", Pins("H3"), IOStandard("LVDS25E"), Misc("SLEWRATE=FAST")), #aux1-=G3, aux1+=H3 INVERT
        	Subsignal("tx1", Pins("F2"), IOStandard("LVDS25E"), Misc("SLEWRATE=FAST")), #aux2-=G1, aux2+=F2 INVERT
        	Subsignal("tx0", Pins("F4"), IOStandard("LVDS25E"), Misc("SLEWRATE=FAST")), #aux6+=F4, aux6-=F3
                )])
        	"""
        	platform.add_extension([("fpdlink_out", 0, #can use GND and just 4 more wires
                #TOP TO BOTTOM
                Subsignal("clk", Pins("N4"), IOStandard("LVCMOS33D"), Misc("SLEWRATE=FAST"), Misc("DRIVE=8")), #aux0-=N3, aux0+=N4 INVERT
                Subsignal("tx2", Pins("H3"), IOStandard("LVCMOS33D"), Misc("SLEWRATE=FAST"), Misc("DRIVE=8")), #aux1-=G3, aux1+=H3 INVERT
                Subsignal("tx1", Pins("F2"), IOStandard("LVCMOS33D"), Misc("SLEWRATE=FAST"), Misc("DRIVE=8")), #aux2-=G1, aux2+=F2 INVERT
                Subsignal("tx0", Pins("F4"), IOStandard("LVCMOS33D"), Misc("SLEWRATE=FAST"), Misc("DRIVE=8")), #aux6+=F4, aux6-=F3
                )])
        	fpdlink_domain = "fpdlink"
        	self.submodules.videophy = VideoFPDLINKPHY(platform.request("fpdlink_out"), clock_domain=fpdlink_domain, clock_domain3p5x="fpdlink3p5x", pn_swap="12c")
        	#self.add_video_terminal2(phy=self.videophy, timings=timings, clock_domain=fpdlink_domain)
        	fifo_depth = timings[1]["h_active"] + timings[1]["h_blanking"] #one line
        	self.add_video_framebuffer2(phy=self.videophy, timings=timings, clock_domain=fpdlink_domain, format="rgb888", fifo_depth=fifo_depth*5) #needs more than one line at 75Mhz sys and 30Hz refresh

        	platform.add_extension([("backlight", 0,
                Subsignal("en", Pins("A10"), IOStandard("LVCMOS33")),
                Subsignal("pwm", Pins("C11"), IOStandard("LVCMOS33"))
                )])
        	bl = platform.request("backlight")
        	self.comb += [bl.en.eq(1), bl.pwm.eq(1)] #allways enable backlight
        
        elif with_video_framebuffer:
            platform.add_extension([("vga", 0,
                Subsignal("hsync", Pins("A10")), #SPI_0
                Subsignal("vsync", Pins("J3")), #LED_B #- pol for 1024x768, but + works
                Subsignal("b", Pins("H3")), #aux1+
                Subsignal("g", Pins("B9")), #IO_6
                Subsignal("r", Pins("N4")), #aux0+
                IOStandard("LVCMOS33"))])
            #from litex.soc.cores.video import VideoVGAPHY
            vga_cd = "vga" if True else "usb_48" #FIXME: adapt to clock
            self.submodules.videophy = VideoVGAPHY(platform.request("vga"), clock_domain=vga_cd)
            self.add_video_framebuffer3(phy=self.videophy, timings=timings, clock_domain=vga_cd, format="rgb565")
        	#self.add_video_framebuffer2(phy=self.videophy, timings=timings, clock_domain=hdmi_domain, format="rgb888")
            #self.add_video_terminal2(phy=self.videophy, timings=timings, clock_domain=vga_cd)

        if with_video_framebuffer:
            port = self.sdram.crossbar.get_port(mode="write")
            dma_width = port.data_width if port.data_width < 64 else 64 #using a wider bus optimizes access, uses software correction for partial word access
            self.blitter = Blitter(port=self.sdram.crossbar.get_port(mode="write", data_width=dma_width))
            self.submodules.blitter = self.blitter

    #NOTE: this is the same as the base implementation but allows to specify the fifo depth
    #it's needed to synth in the 25F
    def add_video_framebuffer2(self, name="video_framebuffer", phy=None, timings="800x600@60Hz", clock_domain="sys", format="rgb888", fifo_depth=16384): #tested with fifo_depth=16384
        # Imports.
        from litex.soc.cores.video import VideoTimingGenerator, VideoFrameBuffer

        # Video Timing Generator.
        vtg = VideoTimingGenerator(default_video_timings=timings if isinstance(timings, str) else timings[1])
        vtg = ClockDomainsRenamer(clock_domain)(vtg)
        self.add_module(name=f"{name}_vtg", module=vtg)

        # Video FrameBuffer.
        timings = timings if isinstance(timings, str) else timings[0]
        base = self.mem_map.get(name, None)
        from litex.soc.integration.soc import SoCRegion
        if base is None:
            self.bus.add_region(name, SoCRegion(
                origin = 0x40c00000,
                size   = 0x800000,
                linker = True)
            )
            base = self.bus.regions[name].origin
        hres = int(timings.split("@")[0].split("x")[0])
        vres = int(timings.split("@")[0].split("x")[1])
        vfb = VideoFrameBuffer(self.sdram.crossbar.get_port(),
            hres   = hres,
            vres   = vres,
            base   = base,
            format = format,
            clock_domain          = clock_domain,
            clock_faster_than_sys = vtg.video_timings["pix_clk"] >= self.sys_clk_freq,
            fifo_depth = fifo_depth
        )
        self.add_module(name=name, module=vfb)

        # Connect Video Timing Generator to Video FrameBuffer.
        self.comb += vtg.source.connect(vfb.vtg_sink)

        # Connect Video FrameBuffer to Video PHY.
        self.comb += vfb.source.connect(phy if isinstance(phy, stream.Endpoint) else phy.sink)

        # Constants.
        self.add_constant("VIDEO_FRAMEBUFFER_BASE", base)
        self.add_constant("VIDEO_FRAMEBUFFER_HRES", hres)
        self.add_constant("VIDEO_FRAMEBUFFER_VRES", vres)
        self.add_constant("VIDEO_FRAMEBUFFER_DEPTH", vfb.depth)

    def add_video_framebuffer3(self, name="video_framebuffer", phy=None, timings="800x600@60Hz", clock_domain="sys", format="rgb888", fifo_depth=16384):
        # Video Timing Generator.
        vtg = VideoTimingGenerator(default_video_timings=timings if isinstance(timings, str) else timings[1])
        vtg = ClockDomainsRenamer(clock_domain)(vtg)
        setattr(self.submodules, f"{name}_vtg", vtg)

        # Video FrameBuffer.
        timings = timings if isinstance(timings, str) else timings[0]
        base = self.mem_map.get(name, 0x41800000)
        hres = int(timings.split("@")[0].split("x")[0])
        vres = int(timings.split("@")[0].split("x")[1])
        bit_depth = {"rgb565":16,"rgb888":32}[format]
        vfb = VideoFrameBufferN(self.sdram.crossbar.get_port(),
            hres = hres,
            vres = vres,
            base = base,
            clock_domain          = clock_domain,
            clock_faster_than_sys = vtg.video_timings["pix_clk"] > self.sys_clk_freq,
            fifo_depth = fifo_depth,
            bit_depth = bit_depth
        )
        setattr(self.submodules, name, vfb)

        # Connect Video Timing Generator to Video FrameBuffer.
        self.comb += vtg.source.connect(vfb.vtg_sink)

        # Connect Video FrameBuffer to Video PHY.
        self.comb += vfb.source.connect(phy if isinstance(phy, stream.Endpoint) else phy.sink)

        # Constants.
        self.add_constant("VIDEO_FRAMEBUFFER_BASE", base)
        self.add_constant("VIDEO_FRAMEBUFFER_HRES", hres)
        self.add_constant("VIDEO_FRAMEBUFFER_VRES", vres)
        self.add_constant("VIDEO_FRAMEBUFFER_DEPTH", bit_depth)

    def add_video_terminal2(self, name="video_terminal", phy=None, timings="800x600@60Hz", clock_domain="sys"):
        # Imports.
        from litex.soc.cores.video import VideoTimingGenerator, VideoTerminal

        # Video Timing Generator.
        self.check_if_exists(f"{name}_vtg")
        vtg = VideoTimingGenerator(default_video_timings=timings if isinstance(timings, str) else timings[1])
        vtg = ClockDomainsRenamer(clock_domain)(vtg)
        self.add_module(name=f"{name}_vtg", module=vtg)

        # Video Terminal.
        timings = timings if isinstance(timings, str) else timings[0]
        vt = VideoTerminal(
            hres = int(timings.split("@")[0].split("x")[0]),
            vres = int(timings.split("@")[0].split("x")[1]),
        )
        vt = ClockDomainsRenamer(clock_domain)(vt)
        self.add_module(name=name, module=vt)

        # Connect Video Timing Generator to Video Terminal.
        self.comb += vtg.source.connect(vt.vtg_sink)

        # Connect UART to Video Terminal.
        uart_cdc = stream.ClockDomainCrossing([("data", 8)], cd_from="sys", cd_to=clock_domain)
        self.add_module(name=f"{name}_uart_cdc", module=uart_cdc)
        
        source = self.uart.tx_fifo.source if hasattr(self.uart, "tx_fifo") else self.uart.source #TODO: text with USB
        self.comb += [
            uart_cdc.sink.valid.eq(source.valid & source.ready),
            uart_cdc.sink.data.eq(source.data),
            uart_cdc.source.connect(vt.uart_sink),
        ]

        # Connect Video Terminal to Video PHY.
        self.comb += vt.source.connect(phy if isinstance(phy, stream.Endpoint) else phy.sink)


# LiteXSoCArgumentParser ---------------------------------------------------------------------------

from litex.build.parser import LiteXArgumentParser

class LiteXSoCArgumentParser(LiteXArgumentParser): pass # FIXME: Add compat and remove.
# Build --------------------------------------------------------------------------------------------


def set_args(parser):
    parser.add_target_argument("--sdram-data-width",     default=128,             help="Set SDRAM chip data width.")
    parser.add_target_argument("--pixel-bus-width",      default=32,              help="Pixel access bus width")
    parser.add_target_argument("--sdram-init",           default=None,            help="SDRAM init file (.bin or .json).")
    parser.add_target_argument("--with-pmod-gpio",      action="store_true",      help="Enable GPIOs through PMOD")

def main():
    from litex.build.parser import LiteXArgumentParser
    parser = LiteXArgumentParser(platform=gsd_orangecrab.Platform, description="LiteX SoC on OrangeCrab")
    parser.add_target_argument("--device",          default="25F",       help="ECP5 device")
    parser.add_target_argument("--sys-clk-freq",    default=96e6,        help="System clock frequency.") #works up to 75MHz with 1366x768@30Hz
    set_args(parser)

    args = parser.parse_args()

    soc = BaseSoC(
        device                 = args.device,
        sys_clk_freq           = int(float(args.sys_clk_freq)),
        toolchain              = args.toolchain,
        pixel_bus_width = int(args.pixel_bus_width),
        with_pmod_gpio = args.with_pmod_gpio,
        **parser.soc_argdict
    )
    
    
    
    builder = Builder(soc, **parser.builder_argdict)
    builder.build(**parser.toolchain_argdict, run=not args.no_compile_gateware)

if __name__ == "__main__":
    main()

