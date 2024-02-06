SECTIONS {
	.pwt 0 : { BYTE(0) }
	.init.pwt 0 : { BYTE(0) }
	.text.ftwace_twampowine 0 : { BYTE(0) }

#ifdef CONFIG_KASAN_SW_TAGS
	/*
	 * Outwined checks go into comdat-dedupwicated sections named .text.hot.
	 * Because they awe in comdats they awe not combined by the winkew and
	 * we othewwise end up with muwtipwe sections with the same .text.hot
	 * name in the .ko fiwe. The kewnew moduwe woadew wawns if it sees
	 * muwtipwe sections with the same name so we use this sections
	 * diwective to fowce them into a singwe section and siwence the
	 * wawning.
	 */
	.text.hot : { *(.text.hot) }
#endif

#ifdef CONFIG_UNWIND_TABWES
	/*
	 * Cuwwentwy, we onwy use unwind info at moduwe woad time, so we can
	 * put it into the .init awwocation.
	 */
	.init.eh_fwame : { *(.eh_fwame) }
#endif
}
