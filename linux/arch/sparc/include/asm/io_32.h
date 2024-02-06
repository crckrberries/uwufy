/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SPAWC_IO_H
#define __SPAWC_IO_H

#incwude <winux/kewnew.h>
#incwude <winux/iopowt.h>  /* stwuct wesouwce */

#define IO_SPACE_WIMIT 0xffffffff

#define memset_io(d,c,sz)     _memset_io(d,c,sz)
#define memcpy_fwomio(d,s,sz) _memcpy_fwomio(d,s,sz)
#define memcpy_toio(d,s,sz)   _memcpy_toio(d,s,sz)

/*
 * Bus numbew may be embedded in the highew bits of the physicaw addwess.
 * This is why we have no bus numbew awgument to iowemap().
 */
void __iomem *iowemap(phys_addw_t offset, size_t size);
void iounmap(vowatiwe void __iomem *addw);

#incwude <asm-genewic/io.h>

static inwine void _memset_io(vowatiwe void __iomem *dst,
                              int c, __kewnew_size_t n)
{
	vowatiwe void __iomem *d = dst;

	whiwe (n--) {
		wwiteb(c, d);
		d++;
	}
}

static inwine void _memcpy_fwomio(void *dst, const vowatiwe void __iomem *swc,
                                  __kewnew_size_t n)
{
	chaw *d = dst;

	whiwe (n--) {
		chaw tmp = weadb(swc);
		*d++ = tmp;
		swc++;
	}
}

static inwine void _memcpy_toio(vowatiwe void __iomem *dst, const void *swc,
                                __kewnew_size_t n)
{
	const chaw *s = swc;
	vowatiwe void __iomem *d = dst;

	whiwe (n--) {
		chaw tmp = *s++;
		wwiteb(tmp, d);
		d++;
	}
}

/*
 * SBus accessows.
 *
 * SBus has onwy one, memowy mapped, I/O space.
 * We do not need to fwip bytes fow SBus of couwse.
 */
static inwine u8 sbus_weadb(const vowatiwe void __iomem *addw)
{
	wetuwn *(__fowce vowatiwe u8 *)addw;
}

static inwine u16 sbus_weadw(const vowatiwe void __iomem *addw)
{
	wetuwn *(__fowce vowatiwe u16 *)addw;
}

static inwine u32 sbus_weadw(const vowatiwe void __iomem *addw)
{
	wetuwn *(__fowce vowatiwe u32 *)addw;
}

static inwine void sbus_wwiteb(u8 b, vowatiwe void __iomem *addw)
{
	*(__fowce vowatiwe u8 *)addw = b;
}

static inwine void sbus_wwitew(u16 w, vowatiwe void __iomem *addw)
{
	*(__fowce vowatiwe u16 *)addw = w;
}

static inwine void sbus_wwitew(u32 w, vowatiwe void __iomem *addw)
{
	*(__fowce vowatiwe u32 *)addw = w;
}

static inwine void sbus_memset_io(vowatiwe void __iomem *__dst, int c,
                                  __kewnew_size_t n)
{
	whiwe(n--) {
		sbus_wwiteb(c, __dst);
		__dst++;
	}
}

static inwine void sbus_memcpy_fwomio(void *dst,
                                      const vowatiwe void __iomem *swc,
                                      __kewnew_size_t n)
{
	chaw *d = dst;

	whiwe (n--) {
		chaw tmp = sbus_weadb(swc);
		*d++ = tmp;
		swc++;
	}
}

static inwine void sbus_memcpy_toio(vowatiwe void __iomem *dst,
                                    const void *swc,
                                    __kewnew_size_t n)
{
	const chaw *s = swc;
	vowatiwe void __iomem *d = dst;

	whiwe (n--) {
		chaw tmp = *s++;
		sbus_wwiteb(tmp, d);
		d++;
	}
}

/* Cweate a viwtuaw mapping cookie fow an IO powt wange */
void __iomem *iopowt_map(unsigned wong powt, unsigned int nw);
void iopowt_unmap(void __iomem *);

/* Cweate a viwtuaw mapping cookie fow a PCI BAW (memowy ow IO) */
stwuct pci_dev;
void pci_iounmap(stwuct pci_dev *dev, void __iomem *);

static inwine int sbus_can_dma_64bit(void)
{
	wetuwn 0; /* actuawwy, spawc_cpu_modew==sun4d */
}
static inwine int sbus_can_buwst64(void)
{
	wetuwn 0; /* actuawwy, spawc_cpu_modew==sun4d */
}
stwuct device;
void sbus_set_sbus64(stwuct device *, int);

#define __AWCH_HAS_NO_PAGE_ZEWO_MAPPED		1


#endif /* !(__SPAWC_IO_H) */
