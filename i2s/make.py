#!/usr/bin/env python3

import argparse
import os

from litex.soc.integration.builder import Builder

from soc import SoCZephyr

# Board definition----------------------------------------------------------------------------------

class Board:
    def __init__(self, soc_cls):
        self.soc_cls = soc_cls
        self.mmcm_freq = {}
        self.bitstream_ext=""

    def load(self, soc, filename):
        prog = soc.platform.create_programmer()
        prog.load_bitstream(filename)

    def flash(self):
        raise NotImplementedError

# Arty support -------------------------------------------------------------------------------------

class Arty(Board):
    def __init__(self):
        from litex_boards.targets import arty
        Board.__init__(self, arty.BaseSoC)
        self.mmcm_freq = {
            "i2s_rx" :  11.289e6,
            "i2s_tx" :  22.579e6,
        }
        self.bitstream_ext=".bit"

# Main ---------------------------------------------------------------------------------------------

supported_boards = {
    # Xilinx
    "arty":         Arty,
}

def main():
    description = "Zephyr on LiteX-VexRiscv\n\n"
    description += "Available boards:\n"
    for name in supported_boards.keys():
        description += "- " + name + "\n"
    parser = argparse.ArgumentParser(description=description, formatter_class=argparse.RawTextHelpFormatter)
    parser.add_argument("--board", required=True, help="FPGA board")
    parser.add_argument("--build", action="store_true", help="build bitstream")
    parser.add_argument("--load", action="store_true", help="load bitstream (to SRAM). set path to bitstream")
    parser.add_argument("--with_ethernet", action="store_true", help="Enable ethernet")
    parser.add_argument("--with_i2s", action="store_true", help="Enable i2s")
    parser.add_argument("--with_mmcm", action="store_true", help="Enable mmcm")
    parser.add_argument("--local-ip", default="192.168.1.50", help="local IP address")
    parser.add_argument("--remote-ip", default="192.168.1.100", help="remote IP address of TFTP server")
    args = parser.parse_args()

    if args.board == "all":
        board_names = list(supported_boards.keys())
    else:
        args.board = args.board.lower()
        board_names = [args.board.replace(" ", "_")]
    for board_name in board_names:
        if board_name not in supported_boards:
            print("Board {} is not supported currently".format(board_name))
            continue
        board = supported_boards[board_name]()
        soc_kwargs = {"integrated_rom_size": 0xfa00}
        soc = SoCZephyr(board.soc_cls, **soc_kwargs)
        if args.with_ethernet:
            soc.add_eth(local_ip=args.local_ip, remote_ip=args.remote_ip)
        if args.with_mmcm:
            soc.add_mmcm(board.mmcm_freq)
        if args.with_i2s:
            #if not args.with_mmcm:
            #    print("Adding mmcm implicitly, cause i2s core needs special clk signals")
            #    soc.add_mmcm(board.mmcm_freq)
            soc.add_i2s()

        build_dir = os.path.join("build", board_name)
        if args.build:
            builder = Builder(soc, output_dir=build_dir,
                csr_json=os.path.join(build_dir, "csr.json"))
        else:
            builder = Builder(soc, output_dir="build/" + board_name,
                compile_software=True, compile_gateware=False,
                csr_json=os.path.join(build_dir, "csr.json"))
        builder.build()

        if args.load:
            board.load(soc, filename=os.path.join(build_dir, "gateware", "arty" + board.bitstream_ext))

if __name__ == "__main__":
    main()
