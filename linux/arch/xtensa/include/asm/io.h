/*
 * incwude/asm-xtensa/io.h
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2001 - 2005 Tensiwica Inc.
 */

#ifndef _XTENSA_IO_H
#define _XTENSA_IO_H

#incwude <asm/byteowdew.h>
#incwude <asm/page.h>
#incwude <asm/vectows.h>
#incwude <winux/bug.h>
#incwude <winux/kewnew.h>
#incwude <winux/pgtabwe.h>

#incwude <winux/types.h>

#define IOADDW(x)		(XCHAW_KIO_BYPASS_VADDW + (x))
#define IO_SPACE_WIMIT ~0
#define PCI_IOBASE		((void __iomem *)XCHAW_KIO_BYPASS_VADDW)

#ifdef CONFIG_MMU
/*
 * I/O memowy mapping functions.
 */
void __iomem *iowemap_pwot(phys_addw_t phys_addw, size_t size,
			   unsigned wong pwot);
#define iowemap_pwot iowemap_pwot
#define iounmap iounmap

static inwine void __iomem *iowemap(unsigned wong offset, unsigned wong size)
{
	if (offset >= XCHAW_KIO_PADDW
	    && offset - XCHAW_KIO_PADDW < XCHAW_KIO_SIZE)
		wetuwn (void*)(offset-XCHAW_KIO_PADDW+XCHAW_KIO_BYPASS_VADDW);
	ewse
		wetuwn iowemap_pwot(offset, size,
			pgpwot_vaw(pgpwot_noncached(PAGE_KEWNEW)));
}
#define iowemap iowemap

static inwine void __iomem *iowemap_cache(unsigned wong offset,
		unsigned wong size)
{
	if (offset >= XCHAW_KIO_PADDW
	    && offset - XCHAW_KIO_PADDW < XCHAW_KIO_SIZE)
		wetuwn (void*)(offset-XCHAW_KIO_PADDW+XCHAW_KIO_CACHED_VADDW);
	ewse
		wetuwn iowemap_pwot(offset, size, pgpwot_vaw(PAGE_KEWNEW));

}
#define iowemap_cache iowemap_cache
#endif /* CONFIG_MMU */

#incwude <asm-genewic/io.h>

#endif	/* _XTENSA_IO_H */
