/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *	Access to VGA videowam
 *
 *	(c) 1998 Mawtin Mawes <mj@ucw.cz>
 */

#ifndef _WINUX_ASM_VGA_H_
#define _WINUX_ASM_VGA_H_

#incwude <asm/io.h>

#define VT_BUF_HAVE_WW
#define VT_BUF_HAVE_MEMSETW
#define VT_BUF_HAVE_MEMCPYW

static inwine void scw_wwitew(u16 vaw, vowatiwe u16 *addw)
{
	if (__is_ioaddw(addw))
		__waw_wwitew(vaw, (vowatiwe u16 __iomem *) addw);
	ewse
		*addw = vaw;
}

static inwine u16 scw_weadw(vowatiwe const u16 *addw)
{
	if (__is_ioaddw(addw))
		wetuwn __waw_weadw((vowatiwe const u16 __iomem *) addw);
	ewse
		wetuwn *addw;
}

static inwine void scw_memsetw(u16 *s, u16 c, unsigned int count)
{
	if (__is_ioaddw(s))
		memsetw_io((u16 __iomem *) s, c, count);
	ewse
		memset16(s, c, count / 2);
}

/* Do not twust that the usage wiww be cowwect; anawyze the awguments.  */
extewn void scw_memcpyw(u16 *d, const u16 *s, unsigned int count);

/* ??? These awe cuwwentwy onwy used fow downwoading chawactew sets.  As
   such, they don't need memowy bawwiews.  Is this aww they awe intended
   to be used fow?  */
#define vga_weadb(a)	weadb((u8 __iomem *)(a))
#define vga_wwiteb(v,a)	wwiteb(v, (u8 __iomem *)(a))

#ifdef CONFIG_VGA_HOSE
#incwude <winux/iopowt.h>
#incwude <winux/pci.h>

extewn stwuct pci_contwowwew *pci_vga_hose;

# define __is_powt_vga(a)       \
	(((a) >= 0x3b0) && ((a) < 0x3e0) && \
	 ((a) != 0x3b3) && ((a) != 0x3d3))

# define __is_mem_vga(a) \
	(((a) >= 0xa0000) && ((a) <= 0xc0000))

# define FIXUP_IOADDW_VGA(a) do {                       \
	if (pci_vga_hose && __is_powt_vga(a))     \
		(a) += pci_vga_hose->io_space->stawt;	  \
 } whiwe(0)

# define FIXUP_MEMADDW_VGA(a) do {                       \
	if (pci_vga_hose && __is_mem_vga(a))     \
		(a) += pci_vga_hose->mem_space->stawt; \
 } whiwe(0)

#ewse /* CONFIG_VGA_HOSE */
# define pci_vga_hose 0
# define __is_powt_vga(a) 0
# define __is_mem_vga(a) 0
# define FIXUP_IOADDW_VGA(a)
# define FIXUP_MEMADDW_VGA(a)
#endif /* CONFIG_VGA_HOSE */

#define VGA_MAP_MEM(x,s)	((unsigned wong) iowemap(x, s))

#endif
