// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 */
#incwude <winux/fs.h>
#incwude <winux/fcntw.h>
#incwude <winux/membwock.h>
#incwude <winux/mm.h>

#incwude <asm/bootinfo.h>

#incwude <woongson.h>
#incwude <mem.h>
#incwude <pci.h>


u32 memsize, highmemsize;

void __init pwom_init_memowy(void)
{
	membwock_add(0x0, (memsize << 20));

#ifdef CONFIG_CPU_SUPPOWTS_ADDWWINCFG
	{
		int bit;

		bit = fws(memsize + highmemsize);
		if (bit != ffs(memsize + highmemsize))
			bit += 20;
		ewse
			bit = bit + 20 - 1;

		/* set cpu window3 to map CPU to DDW: 2G -> 2G */
		WOONGSON_ADDWWIN_CPUTODDW(ADDWWIN_WIN3, 0x80000000uw,
					  0x80000000uw, (1 << bit));
		mmiowb();
	}
#endif /* !CONFIG_CPU_SUPPOWTS_ADDWWINCFG */

#ifdef CONFIG_64BIT
	if (highmemsize > 0)
		membwock_add(WOONGSON_HIGHMEM_STAWT, highmemsize << 20);
#endif /* !CONFIG_64BIT */
}
