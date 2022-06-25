BUILD_DIRECTORY=../build/digilent_arty
USBHOST_DIR?=../Libs/usbhost
FB_DIR=../Libs/litefb
TINYUSB_SCR_DIR=../Libs/tinyusb
RVFPLIB?=../../RVfplib/

include makefile.inc

INC += -I$(USBHOST_DIR)
INC += -I$(FB_DIR)
INC += -I$(TINYUSB_SCR_DIR)
#INC += -I$(BUILD_DIRECTORY)/software/include
CXXFLAGS += $(INC) -O2 -march=rv32im -mabi=ilp32
CFLAGS += $(INC) -O2 -Wno-missing-prototypes -march=rv32im -mabi=ilp32

IMGUI_OBJECTS=imgui.o imgui_demo.o imgui_draw.o imgui_tables.o imgui_widgets.o imgui_sw.o
USB_OBJECTS=$(USBHOST_DIR)/usb_host.o $(TINYUSB_SCR_DIR)/common/tusb_fifo.o


all: usb_main.elf

#lto flag added to allow sources with mixed -flto or -fno-lto (link time) optimizations settings
%.elf: %.o crt0.o sbrk.o usb_main.o isr.o usb.o printf.o $(FB_DIR)/lite_fb.o $(IMGUI_OBJECTS) $(USB_OBJECTS) linker.ld regions.ld
	$(CC)  $< ./crt0.o sbrk.o $(USB_OBJECTS) isr.o usb.o printf.o \
	     $(FB_DIR)/lite_fb.o $(IMGUI_OBJECTS) $(LDFLAGS) \
		-T linker.ld \
		-Xlinker -Map=$@.map \
		-N -o $@ \
		$(PACKAGES:%=-L$(BUILD_DIR)/software/%) \
		-flto \
		-L. $(LIBS:lib%=-l%) -L$(RVFPLIB)/build/lib -lrvfp
	chmod -x $@
	$(OBJCOPY) -O binary $@ $@.bin
