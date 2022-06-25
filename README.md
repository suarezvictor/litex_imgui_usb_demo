# LiteUSB
This is an implementation of a 100% software USB host stack for a LiteX SoC, and a GUI demo based on Dear ImGui library both running on the same CPU. It currently supports the Digilent Arty A7 board implementing a VexRiscv soft-core CPU running at 166/200MHz, and a mouse on low-speed mode.

## Hardware requirements
* Referenced Arty board
* a VGA PMOD (connectors B-C) or DVI adapter PMOD (connector C) 
* USB host PMOD on connector D (D+ on pin 0, D- on pin 4)

## Software dependencies
* LiteX and associated tools (compilers, synthesis tools, etc.)
* Risc-V soft float emulation library https://github.com/pulp-platform/RVfplib
* Other libraries used are already put into the Libs folder

##  Building dependencies
It's assumed you will use a folder with this and other repos, referenced as $REPOS_ROOT (so this project gets in $REPOS_ROOT/LiteUSB)

To build the RVfplib:
```
cd $REPOS_ROOT
git clone https://github.com/pulp-platform/RVfplib
cd Rvfplib
```

Tweak the makefile to replace compiler and architecture/ABI:
```
CC             := riscv64-unknown-elf-gcc
CCFLAGS        := -march=rv32im -mabi=ilp32
OBJDUMP        := riscv64-unknown-elf-objdump
```

##  Commands to run for generating the SoC with LiteX
It's assumed that LiteX is downloaded and compilers correctly set<br>
To generate the bitstream, tweak the .py file and run one of the following commands:

<br>(with DVI=False, 640x480@60Hz)
<br>```./digilent_arty.py --timer-uptime --uart-baudrate=1000000 --with-pmod-gpio --integrated-sram-size 32768 --sys-clk-freq=200e6     --cpu-type=vexriscv --cpu-variant=full --build```
<br>
<br>(with DVI=True,  800x600@50Hz)
<br>```./digilent_arty.py --timer-uptime --uart-baudrate=1000000 --with-pmod-gpio --integrated-sram-size 32768 --sys-clk-freq=166666666 --cpu-type=vexriscv --cpu-variant=full --build```

Loading the bitstream:<br>
```openFPGALoader -b arty build/digilent_arty/gateware/digilent_arty.bit```
<br><br>
After this, a screen showing the random data of the framebuffer memory should appear

## Compiling the USB host and GUI demo
```
cd $REPOS_ROOT/LiteUSB/src
make all
litex_term --speed 1000000 --kernel usb_main.elf.bin /dev/ttyUSB1
```
*NOTE: update the USB device to match your OS. The LiteX generated bitstream may need to be reloaded*

## Integrated dependencies
Software that integrates the demo, related repos (with detailed commit history), and where sources are expected (assumes . = $REPOS_ROOT/LiteUSB/src)
<br>*NOTE: some of these project sources were modified as this project requires*

ESP32 USB host:
https://github.com/suarezvictor/ESP32-USB-Soft-Host/tree/main/src → ./Libs/usbhost
<br>
TinyUSB:
https://github.com/suarezvictor/tinyusb/tree/master/src → ./Libs/tinyusb
<br>
LearnFPGA's LiteFB:
https://github.com/suarezvictor/learn-fpga/tree/master/LiteX/software/Libs→ ./Libs/litefb
<br>
LearnFPGA ImGUI:
https://github.com/suarezvictor/learn-fpga/tree/master/LiteX/software/Libs/imgui → ./Libs/imgui
(originally from https://github.com/ocornut/imgui/tree/78b28d545f79c5c5ed3e0ebae4099e44bdc6c5a6 and https://github.com/emilk/imgui_software_renderer)
<br>
Printf library:
https://github.com/mpaland/printf -> ./
<br>
LiteX C DK:
https://github.com/suarezvictor/micropython/tree/litex-rebase/ports/litex/liblitesdk → ./Libs/liblitesdk
<br>
digilent_arty.py from LiteX boards:
[digilent_arty.py](https://github.com/suarezvictor/litex-boards/blob/master/litex_boards/targets/digilent_arty.py) → ../
<br>


