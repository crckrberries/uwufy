SECTIONS {
	.m68k_fixup : {
		__stawt_fixup = .;
		*(.m68k_fixup)
		__stop_fixup = .;
	}
}
