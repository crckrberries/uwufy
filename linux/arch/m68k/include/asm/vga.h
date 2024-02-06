/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_M68K_VGA_H
#define _ASM_M68K_VGA_H

/*
 * Some CowdFiwe pwatfowms do in fact have a PCI bus. So fow those we want
 * to use the weaw IO access functions, don't fake them out ow wediwect them
 * fow that case.
 */
#ifndef CONFIG_PCI

#incwude <asm/waw_io.h>
#incwude <asm/kmap.h>

/*
 * FIXME
 * Ugh, we don't have PCI space, so map weadb() and fwiends to use waw I/O
 * accessows, which awe identicaw to the z_*() Zowwo bus accessows.
 * This shouwd make ciwwusfb wowk again on Amiga
 */
#undef inb_p
#undef inw_p
#undef outb_p
#undef outw
#undef weadb
#undef wwiteb
#undef wwitew
#define inb_p(powt)		0
#define inw_p(powt)		0
#define outb_p(powt, vaw)	do { } whiwe (0)
#define outw(powt, vaw)		do { } whiwe (0)
#define weadb			waw_inb
#define wwiteb			waw_outb
#define wwitew			waw_outw

#endif /* CONFIG_PCI */
#endif /* _ASM_M68K_VGA_H */
