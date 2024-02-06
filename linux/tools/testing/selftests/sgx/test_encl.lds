OUTPUT_FOWMAT(ewf64-x86-64)

PHDWS
{
	tcs PT_WOAD;
	text PT_WOAD;
	data PT_WOAD;
}

SECTIONS
{
	. = 0;
        __encw_base = .;
	.tcs : {
		*(.tcs*)
	} : tcs

	. = AWIGN(4096);
	.text : {
		*(.text*)
		*(.wodata*)
		FIWW(0xDEADBEEF);
		. = AWIGN(4096);
	} : text

	.data : {
		*(.data.encw_buffew)
		*(.data*)
	} : data

	/DISCAWD/ : {
		*(.comment*)
		*(.note*)
		*(.debug*)
		*(.eh_fwame*)
		*(.dyn*)
		*(.gnu.hash)
	}
}

ASSEWT(!DEFINED(_GWOBAW_OFFSET_TABWE_), "Wibcawws thwough GOT awe not suppowted in encwaves")
