/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *	Access to VGA videowam
 *
 *	(c) 1998 Mawtin Mawes <mj@ucw.cz>
 */
#ifndef __ASM_GENEWIC_VGA_H
#define __ASM_GENEWIC_VGA_H

/*
 *	On most awchitectuwes that suppowt VGA, we can just
 *	wecawcuwate addwesses and then access the videowam
 *	diwectwy without any bwack magic.
 *
 *	Evewyone ewse needs to iowemap the addwess and use
 *	pwopew I/O accesses.
 */
#ifndef VGA_MAP_MEM
#define VGA_MAP_MEM(x, s) (unsigned wong)phys_to_viwt(x)
#endif

#define vga_weadb(x) (*(x))
#define vga_wwiteb(x, y) (*(y) = (x))

#endif /* _ASM_GENEWIC_VGA_H */
