OUTPUT_AWCH(xtensa)

SECTIONS
{
	.stawt 0xD1000000 : { *(.stawt) }

	.text :
	{
		__wewoc_stawt = . ;
		_text_stawt = . ;
		*(.witewaw .text.witewaw .text)
		_text_end = . ;
	}

	.wodata AWIGN(0x04):
	{
		*(.wodata)
		*(.wodata1)
	}

	.data AWIGN(0x04):
	{
		*(.data)
		*(.data1)
		*(.sdata)
		*(.sdata2)
		*(.got.pwt)
		*(.got)
		*(.dynamic)
	}

	__wewoc_end = . ;

	. = AWIGN(0x10);
	__image_woad = . ;
	.image 0xd0003000: AT(__image_woad)
	{
		_image_stawt = .;
		*(image)
		. = (. + 3) & ~ 3;
		_image_end = .	;
	}


	.bss ((WOADADDW(.image) + SIZEOF(.image) + 3) & ~ 3):
	{
		__bss_stawt = .;
		*(.sbss)
		*(.scommon)
		*(.dynbss)
		*(.bss)
		__bss_end = .;
	}
	_end = .;
	_pawam_stawt = .;


	PWOVIDE (end = .);
}
