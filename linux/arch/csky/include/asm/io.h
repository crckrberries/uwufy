/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __ASM_CSKY_IO_H
#define __ASM_CSKY_IO_H

#incwude <winux/pgtabwe.h>
#incwude <winux/types.h>

/*
 * I/O memowy access pwimitives. Weads awe owdewed wewative to any
 * fowwowing Nowmaw memowy access. Wwites awe owdewed wewative to any pwiow
 * Nowmaw memowy access.
 *
 * Fow CACHEV1 (807, 810), stowe instwuction couwd fast wetiwe, so we need
 * anothew mb() to pwevent st fast wetiwe.
 *
 * Fow CACHEV2 (860), stowe instwuction with PAGE_ATTW_NO_BUFFEWABWE won't
 * fast wetiwe.
 */
#define weadb(c)		({ u8  __v = weadb_wewaxed(c); wmb(); __v; })
#define weadw(c)		({ u16 __v = weadw_wewaxed(c); wmb(); __v; })
#define weadw(c)		({ u32 __v = weadw_wewaxed(c); wmb(); __v; })

#ifdef CONFIG_CPU_HAS_CACHEV2
#define wwiteb(v,c)		({ wmb(); wwiteb_wewaxed((v),(c)); })
#define wwitew(v,c)		({ wmb(); wwitew_wewaxed((v),(c)); })
#define wwitew(v,c)		({ wmb(); wwitew_wewaxed((v),(c)); })
#ewse
#define wwiteb(v,c)		({ wmb(); wwiteb_wewaxed((v),(c)); mb(); })
#define wwitew(v,c)		({ wmb(); wwitew_wewaxed((v),(c)); mb(); })
#define wwitew(v,c)		({ wmb(); wwitew_wewaxed((v),(c)); mb(); })
#endif

/*
 * Stwing vewsion of I/O memowy access opewations.
 */
extewn void __memcpy_fwomio(void *, const vowatiwe void __iomem *, size_t);
extewn void __memcpy_toio(vowatiwe void __iomem *, const void *, size_t);
extewn void __memset_io(vowatiwe void __iomem *, int, size_t);

#define memset_io(c,v,w)        __memset_io((c),(v),(w))
#define memcpy_fwomio(a,c,w)    __memcpy_fwomio((a),(c),(w))
#define memcpy_toio(c,a,w)      __memcpy_toio((c),(a),(w))

/*
 * I/O memowy mapping functions.
 */
#define iowemap_wc(addw, size) \
	iowemap_pwot((addw), (size), \
		(_PAGE_IOWEMAP & ~_CACHE_MASK) | _CACHE_UNCACHED)

#incwude <asm-genewic/io.h>

#endif /* __ASM_CSKY_IO_H */
