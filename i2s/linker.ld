INCLUDE generated/output_format.ld
ENTRY(_start)

__DYNAMIC = 0;

INCLUDE regions.ld

SECTIONS
{
	.text :
	{
		_ftext = .;
		/* Make sure crt0 files come first, and they, and the isr */
		/* don't get disposed of by greedy optimisation */
		*crt0*(.text)
		KEEP(*crt0*(.text))
		*(.text .stub .text.* .gnu.linkonce.t.* .gnu.*lto*)
		_etext = .;
	} > main_ram

	.rodata :
	{
		. = ALIGN(8);
		_frodata = .;
		*(.rodata)
		*(.rodata.* .gnu.linkonce.r.*)
		*(.rodata1)
		. = ALIGN(8);
		_erodata = .;
	} > main_ram


	.data :
	{
		. = ALIGN(8);
		/* _fdata = .; */
		*(.data .data.* .gnu.linkonce.d.*)
		*(.data1)
		/* _gp = ALIGN(16); */
		*(.sdata .sdata.* .gnu.linkonce.s.*)
		. = ALIGN(8);
		/* _edata = .; */
	} > main_ram


	.fast_text : 
	{
        . = ALIGN (8);
	    _fast_text_loadaddr = LOADADDR(.fast_text);
		_fast_text = .;
		*(.fast_text)
        . = ALIGN (8);
		_efast_text = .;
	} > sram AT > main_ram
	
	.fast_data : 
	{
        . = ALIGN (8);
	    _fast_data_loadaddr = LOADADDR(.fast_data);
		_fast_data = .;
		*(.fast_data)
		_efast_data = .;
	}  > sram AT > main_ram
	

	.bss : /* NOTE: this includes _end, so it must come at the end for correct malloc */
	{
		. = ALIGN(8);
		_fbss = .;
		*(.dynsbss)
		*(.sbss .sbss.* .gnu.linkonce.sb.*)
		*(.scommon)
		*(.dynbss)
		*(.bss .bss.* .gnu.linkonce.b.*)
		*(COMMON)
		. = ALIGN(8);
		_ebss = .;
		_end = .;
	} > main_ram

}

PROVIDE(_fstack = ORIGIN(sram) + LENGTH(sram) - 4);

PROVIDE(_fdata_rom = LOADADDR(.data));
PROVIDE(_edata_rom = LOADADDR(.data) + SIZEOF(.data));
