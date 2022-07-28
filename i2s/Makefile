BUILD_DIR=./build/arty

include makefile.inc
CFLAGS += -O2
LDFLAGS += -nostartfiles
LIBS:=$(LIBS:libcompiler_rt=libgcc) #this enables floating point functions

all: main.elf

main.elf: main.o crt0.o isr.o litex_i2s.o
	$(CC) $< crt0.o isr.o litex_i2s.o \
		$(LDFLAGS) -T linker.ld \
		-N -o $@ \
		$(PACKAGES:%=-L$(BUILD_DIR)/software/%) \
		-flto \
		-L. $(LIBS:lib%=-l%)
	chmod -x $@
	$(OBJCOPY) -O binary $@ $@.bin

audiotest: synth_demo.c
	gcc -DAUDIO_DEMO_STANDALONE $< -o $@ -lm -lSDL2
