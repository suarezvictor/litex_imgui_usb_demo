LITEX_DIR?=/media/vsuarez/elocaldata/SCRATCH/litex
SOC_DIRECTORY?=$(LITEX_DIR)/litex/soc
BUILD_DIR?=build
BIOS_SRC_DIR=$(LITEX_DIR)/litex/soc/software/bios
include $(BUILD_DIR)/software/include/generated/variables.mak
include $(SOC_DIRECTORY)/software/common.mak

# Include path 
CFLAGS:=$(CFLAGS) -I$(BIOS_SRC_DIR)

%.o: %.c
	$(compile)

%.o: $(BIOS_SRC_DIR)/%.c
	$(compile)

%.o: %.S
	$(assemble)

%.bin: %.elf
	$(OBJCOPY) -O binary $< $@
	chmod -x $@

clean:
	$(RM) *.d *.o *.a *.elf *.list *.map *.bin .*~ *~

.PHONY: all clean 


