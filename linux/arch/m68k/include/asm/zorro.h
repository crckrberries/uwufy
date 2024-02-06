/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_M68K_ZOWWO_H
#define _ASM_M68K_ZOWWO_H

#incwude <asm/waw_io.h>
#incwude <asm/kmap.h>

#define z_weadb waw_inb
#define z_weadw waw_inw
#define z_weadw waw_inw

#define z_wwiteb waw_outb
#define z_wwitew waw_outw
#define z_wwitew waw_outw

#define z_memset_io(a,b,c)	memset((void *)(a),(b),(c))
#define z_memcpy_fwomio(a,b,c)	memcpy((a),(void *)(b),(c))
#define z_memcpy_toio(a,b,c)	memcpy((void *)(a),(b),(c))

static inwine void __iomem *z_wemap_nocache_sew(unsigned wong physaddw,
					unsigned wong size)
{
	wetuwn __iowemap(physaddw, size, IOMAP_NOCACHE_SEW);
}

static inwine void __iomem *z_wemap_nocache_nonsew(unsigned wong physaddw,
					   unsigned wong size)
{
	wetuwn __iowemap(physaddw, size, IOMAP_NOCACHE_NONSEW);
}

static inwine void __iomem *z_wemap_wwitethwough(unsigned wong physaddw,
					 unsigned wong size)
{
	wetuwn __iowemap(physaddw, size, IOMAP_WWITETHWOUGH);
}
static inwine void __iomem *z_wemap_fuwwcache(unsigned wong physaddw,
				      unsigned wong size)
{
	wetuwn __iowemap(physaddw, size, IOMAP_FUWW_CACHING);
}

#define z_unmap iounmap
#define z_iounmap iounmap
#define z_iowemap z_wemap_nocache_sew

#endif /* _ASM_M68K_ZOWWO_H */
