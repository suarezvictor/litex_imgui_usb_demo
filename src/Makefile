SHELL := /bin/bash

BOARD?=gsd_orangecrab
BUILD_DIRECTORY=../build/$(BOARD)
USBHOST_DIR?=../Libs/usbhost
FB_DIR=../Libs/litefb
IMGUI_DIR=../Libs/imgui
TINYUSB_SCR_DIR=../Libs/tinyusb
LITEX_SDK_DIR?=../Libs/litex_sdk
RVFPLIB?=../../RVfplib/
MICROPYTHON_PORT_DIR?=/media/vsuarez/elocaldata/SCRATCH/micropython-private/ports/litex
include makefile.inc

INC += -I$(USBHOST_DIR) -I$(FB_DIR) -I$(TINYUSB_SCR_DIR) -I$(LITEX_SDK_DIR)
#INC += -I$(BUILD_DIRECTORY)/software/include
#CCDEFS = -DIMGUI_USE_BGRA_PACKED_COLOR #tested not needed for ECP5 target
CXXFLAGS += $(CCDEFS) $(INC) -O2 -march=rv32im -mabi=ilp32
CFLAGS += $(CCDEFS) $(INC) -O2 -Wno-missing-prototypes -march=rv32im -mabi=ilp32

IMGUI_OBJECTS=imgui.o imgui_demo.o imgui_draw.o imgui_tables.o imgui_widgets.o imgui_sw.o
USB_OBJECTS=$(USBHOST_DIR)/usb_host.o $(USBHOST_DIR)/usb_host_hid.o $(TINYUSB_SCR_DIR)/common/tusb_fifo.o
I2S_OBJECTS=../Libs/i2s/litex_i2s.o audio.o

all: firmware

#lto flag added to allow sources with mixed -flto or -fno-lto (link time) optimizations settings
%.elf: %.o crt0.o sbrk.o usb_main.o isr.o usb.o printf.o $(FB_DIR)/lite_fb.o $(IMGUI_OBJECTS) $(USB_OBJECTS) \
	$(I2S_OBJECTS) #$(MICROPYTHON_PORT_DIR)/build/libmicropython.a \
	linker.ld
	$(CC)  $< ./crt0.o sbrk.o $(USB_OBJECTS) isr.o usb.o printf.o \
	     $(FB_DIR)/lite_fb.o $(IMGUI_OBJECTS) $(I2S_OBJECTS) $(LDFLAGS) \
		-T linker.ld \
		-Xlinker -Map=$@.map \
		-N -o $@ \
		$(PACKAGES:%=-L$(BUILD_DIR)/software/%) \
		-flto \
		-L. $(LIBS:lib%=-l%) -L$(RVFPLIB)/build/lib -lrvfp -L$(MICROPYTHON_PORT_DIR)/build #-lmicropython
	chmod -x $@
	$(OBJCOPY) -O binary $@ $@.bin

firmware: usb_main.elf


sim: sdl_main.cpp test_ui.cpp
	 $(CXX) `sdl2-config --cflags` -I$(IMGUI_DIR) sdl_main.cpp `sdl2-config --libs` -lGL -o sim
	 ./sim
	 
verilator: ../build/sim/software/include/generated/variables.mak usb_main.elf
	cd .. && ./sim.py --with-video-framebuffer --timer-uptime --with-sdram --sdram-init src/usb_main.elf.bin

../build/sim/software/include/generated/variables.mak: ../sim.py
	read -t 10 -p "Close window after it first appears"
	cd .. && ./sim.py --with-video-framebuffer --timer-uptime --with-sdram --non-interactive

clean:
	$(RM) $(IMGUI_DIR)/*.o $(FB_DIR)/*.o $(LITEX_SDK_DIR)/*.o $(USBHOST_DIR)/*.o $(LITEX_SDK_DIR)/*.o *.o *.elf *.bin *.d ./sim
	$(RM) -R build ../build
