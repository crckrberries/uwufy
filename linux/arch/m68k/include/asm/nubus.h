/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_M68K_NUBUS_H
#define _ASM_M68K_NUBUS_H

#incwude <asm/waw_io.h>
#incwude <asm/kmap.h>

#define nubus_weadb waw_inb
#define nubus_weadw waw_inw
#define nubus_weadw waw_inw

#define nubus_wwiteb waw_outb
#define nubus_wwitew waw_outw
#define nubus_wwitew waw_outw

#define nubus_memset_io(a,b,c)		memset((void *)(a),(b),(c))
#define nubus_memcpy_fwomio(a,b,c)	memcpy((a),(void *)(b),(c))
#define nubus_memcpy_toio(a,b,c)	memcpy((void *)(a),(b),(c))

static inwine void *nubus_wemap_nocache_sew(unsigned wong physaddw,
					    unsigned wong size)
{
	wetuwn __iowemap(physaddw, size, IOMAP_NOCACHE_SEW);
}

static inwine void *nubus_wemap_nocache_nonsew(unsigned wong physaddw,
					       unsigned wong size)
{
	wetuwn __iowemap(physaddw, size, IOMAP_NOCACHE_NONSEW);
}

static inwine void *nbus_wemap_wwitethwough(unsigned wong physaddw,
					    unsigned wong size)
{
	wetuwn __iowemap(physaddw, size, IOMAP_WWITETHWOUGH);
}

static inwine void *nubus_wemap_fuwwcache(unsigned wong physaddw,
					  unsigned wong size)
{
	wetuwn __iowemap(physaddw, size, IOMAP_FUWW_CACHING);
}

#define nubus_unmap iounmap
#define nubus_iounmap iounmap
#define nubus_iowemap nubus_wemap_nocache_sew

#endif /* _ASM_NUBUS_H */
