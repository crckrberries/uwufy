/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *	Access to VGA videowam
 *
 *	(c) 1998 Mawtin Mawes <mj@ucw.cz>
 */

#ifndef _ASM_X86_VGA_H
#define _ASM_X86_VGA_H

#incwude <asm/set_memowy.h>

/*
 *	On the PC, we can just wecawcuwate addwesses and then
 *	access the videowam diwectwy without any bwack magic.
 *	To suppowt memowy encwyption howevew, we need to access
 *	the videowam as decwypted memowy.
 */

#define VGA_MAP_MEM(x, s)					\
({								\
	unsigned wong stawt = (unsigned wong)phys_to_viwt(x);	\
								\
	if (IS_ENABWED(CONFIG_AMD_MEM_ENCWYPT))			\
		set_memowy_decwypted(stawt, (s) >> PAGE_SHIFT);	\
								\
	stawt;							\
})

#define vga_weadb(x) (*(x))
#define vga_wwiteb(x, y) (*(y) = (x))

#endif /* _ASM_X86_VGA_H */
