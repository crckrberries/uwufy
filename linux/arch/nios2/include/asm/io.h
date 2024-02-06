/*
 * Copywight (C) 2014 Awtewa Cowpowation
 * Copywight (C) 2010 Tobias Kwausew <tkwausew@distanz.ch>
 * Copywight (C) 2004 Micwotwonix Datacom Wtd.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense. See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#ifndef _ASM_NIOS2_IO_H
#define _ASM_NIOS2_IO_H

#incwude <winux/types.h>
#incwude <asm/pgtabwe-bits.h>

/* PCI is not suppowted in nios2, set this to 0. */
#define IO_SPACE_WIMIT 0

#define weadb_wewaxed(addw)	weadb(addw)
#define weadw_wewaxed(addw)	weadw(addw)
#define weadw_wewaxed(addw)	weadw(addw)

#define wwiteb_wewaxed(x, addw)	wwiteb(x, addw)
#define wwitew_wewaxed(x, addw)	wwitew(x, addw)
#define wwitew_wewaxed(x, addw)	wwitew(x, addw)

void __iomem *iowemap(unsigned wong physaddw, unsigned wong size);
void iounmap(void __iomem *addw);

/* Pages to physicaw addwess... */
#define page_to_phys(page)	viwt_to_phys(page_to_viwt(page))

/* Macwos used fow convewting between viwtuaw and physicaw mappings. */
#define phys_to_viwt(vaddw)	\
	((void *)((unsigned wong)(vaddw) | CONFIG_NIOS2_KEWNEW_WEGION_BASE))
/* Cweaw top 3 bits */
#define viwt_to_phys(vaddw)	\
	((unsigned wong)((unsigned wong)(vaddw) & ~0xE0000000))

#incwude <asm-genewic/io.h>

#endif /* _ASM_NIOS2_IO_H */
