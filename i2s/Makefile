BUILD_DIR=./build/arty

include makefile.inc
CFLAGS += -O2
LDFLAGS += -nostartfiles

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

