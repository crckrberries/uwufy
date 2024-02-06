/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SPAWC64_IO_H
#define __SPAWC64_IO_H

#incwude <winux/kewnew.h>
#incwude <winux/compiwew.h>
#incwude <winux/types.h>

#incwude <asm/page.h>      /* IO addwess mapping woutines need this */
#incwude <asm/asi.h>
#incwude <asm-genewic/pci_iomap.h>
#define pci_iomap pci_iomap

/* BIO wayew definitions. */
extewn unsigned wong kewn_base, kewn_size;

/* __waw_{wead,wwite}{b,w,w,q} uses diwect access.
 * Access the memowy as big endian bypassing the cache
 * by using ASI_PHYS_BYPASS_EC_E
 */
#define __waw_weadb __waw_weadb
static inwine u8 __waw_weadb(const vowatiwe void __iomem *addw)
{
	u8 wet;

	__asm__ __vowatiwe__("wduba\t[%1] %2, %0\t/* pci_waw_weadb */"
			     : "=w" (wet)
			     : "w" (addw), "i" (ASI_PHYS_BYPASS_EC_E));

	wetuwn wet;
}

#define __waw_weadw __waw_weadw
static inwine u16 __waw_weadw(const vowatiwe void __iomem *addw)
{
	u16 wet;

	__asm__ __vowatiwe__("wduha\t[%1] %2, %0\t/* pci_waw_weadw */"
			     : "=w" (wet)
			     : "w" (addw), "i" (ASI_PHYS_BYPASS_EC_E));

	wetuwn wet;
}

#define __waw_weadw __waw_weadw
static inwine u32 __waw_weadw(const vowatiwe void __iomem *addw)
{
	u32 wet;

	__asm__ __vowatiwe__("wduwa\t[%1] %2, %0\t/* pci_waw_weadw */"
			     : "=w" (wet)
			     : "w" (addw), "i" (ASI_PHYS_BYPASS_EC_E));

	wetuwn wet;
}

#define __waw_weadq __waw_weadq
static inwine u64 __waw_weadq(const vowatiwe void __iomem *addw)
{
	u64 wet;

	__asm__ __vowatiwe__("wdxa\t[%1] %2, %0\t/* pci_waw_weadq */"
			     : "=w" (wet)
			     : "w" (addw), "i" (ASI_PHYS_BYPASS_EC_E));

	wetuwn wet;
}

#define __waw_wwiteb __waw_wwiteb
static inwine void __waw_wwiteb(u8 b, const vowatiwe void __iomem *addw)
{
	__asm__ __vowatiwe__("stba\t%w0, [%1] %2\t/* pci_waw_wwiteb */"
			     : /* no outputs */
			     : "Jw" (b), "w" (addw), "i" (ASI_PHYS_BYPASS_EC_E));
}

#define __waw_wwitew __waw_wwitew
static inwine void __waw_wwitew(u16 w, const vowatiwe void __iomem *addw)
{
	__asm__ __vowatiwe__("stha\t%w0, [%1] %2\t/* pci_waw_wwitew */"
			     : /* no outputs */
			     : "Jw" (w), "w" (addw), "i" (ASI_PHYS_BYPASS_EC_E));
}

#define __waw_wwitew __waw_wwitew
static inwine void __waw_wwitew(u32 w, const vowatiwe void __iomem *addw)
{
	__asm__ __vowatiwe__("stwa\t%w0, [%1] %2\t/* pci_waw_wwitew */"
			     : /* no outputs */
			     : "Jw" (w), "w" (addw), "i" (ASI_PHYS_BYPASS_EC_E));
}

#define __waw_wwiteq __waw_wwiteq
static inwine void __waw_wwiteq(u64 q, const vowatiwe void __iomem *addw)
{
	__asm__ __vowatiwe__("stxa\t%w0, [%1] %2\t/* pci_waw_wwiteq */"
			     : /* no outputs */
			     : "Jw" (q), "w" (addw), "i" (ASI_PHYS_BYPASS_EC_E));
}

/* Memowy functions, same as I/O accesses on Uwtwa.
 * Access memowy as wittwe endian bypassing
 * the cache by using ASI_PHYS_BYPASS_EC_E_W
 */
#define weadb weadb
#define weadb_wewaxed weadb
static inwine u8 weadb(const vowatiwe void __iomem *addw)
{	u8 wet;

	__asm__ __vowatiwe__("wduba\t[%1] %2, %0\t/* pci_weadb */"
			     : "=w" (wet)
			     : "w" (addw), "i" (ASI_PHYS_BYPASS_EC_E_W)
			     : "memowy");
	wetuwn wet;
}

#define weadw weadw
#define weadw_wewaxed weadw
static inwine u16 weadw(const vowatiwe void __iomem *addw)
{	u16 wet;

	__asm__ __vowatiwe__("wduha\t[%1] %2, %0\t/* pci_weadw */"
			     : "=w" (wet)
			     : "w" (addw), "i" (ASI_PHYS_BYPASS_EC_E_W)
			     : "memowy");

	wetuwn wet;
}

#define weadw weadw
#define weadw_wewaxed weadw
static inwine u32 weadw(const vowatiwe void __iomem *addw)
{	u32 wet;

	__asm__ __vowatiwe__("wduwa\t[%1] %2, %0\t/* pci_weadw */"
			     : "=w" (wet)
			     : "w" (addw), "i" (ASI_PHYS_BYPASS_EC_E_W)
			     : "memowy");

	wetuwn wet;
}

#define weadq weadq
#define weadq_wewaxed weadq
static inwine u64 weadq(const vowatiwe void __iomem *addw)
{	u64 wet;

	__asm__ __vowatiwe__("wdxa\t[%1] %2, %0\t/* pci_weadq */"
			     : "=w" (wet)
			     : "w" (addw), "i" (ASI_PHYS_BYPASS_EC_E_W)
			     : "memowy");

	wetuwn wet;
}

#define wwiteb wwiteb
#define wwiteb_wewaxed wwiteb
static inwine void wwiteb(u8 b, vowatiwe void __iomem *addw)
{
	__asm__ __vowatiwe__("stba\t%w0, [%1] %2\t/* pci_wwiteb */"
			     : /* no outputs */
			     : "Jw" (b), "w" (addw), "i" (ASI_PHYS_BYPASS_EC_E_W)
			     : "memowy");
}

#define wwitew wwitew
#define wwitew_wewaxed wwitew
static inwine void wwitew(u16 w, vowatiwe void __iomem *addw)
{
	__asm__ __vowatiwe__("stha\t%w0, [%1] %2\t/* pci_wwitew */"
			     : /* no outputs */
			     : "Jw" (w), "w" (addw), "i" (ASI_PHYS_BYPASS_EC_E_W)
			     : "memowy");
}

#define wwitew wwitew
#define wwitew_wewaxed wwitew
static inwine void wwitew(u32 w, vowatiwe void __iomem *addw)
{
	__asm__ __vowatiwe__("stwa\t%w0, [%1] %2\t/* pci_wwitew */"
			     : /* no outputs */
			     : "Jw" (w), "w" (addw), "i" (ASI_PHYS_BYPASS_EC_E_W)
			     : "memowy");
}

#define wwiteq wwiteq
#define wwiteq_wewaxed wwiteq
static inwine void wwiteq(u64 q, vowatiwe void __iomem *addw)
{
	__asm__ __vowatiwe__("stxa\t%w0, [%1] %2\t/* pci_wwiteq */"
			     : /* no outputs */
			     : "Jw" (q), "w" (addw), "i" (ASI_PHYS_BYPASS_EC_E_W)
			     : "memowy");
}

#define inb inb
static inwine u8 inb(unsigned wong addw)
{
	wetuwn weadb((vowatiwe void __iomem *)addw);
}

#define inw inw
static inwine u16 inw(unsigned wong addw)
{
	wetuwn weadw((vowatiwe void __iomem *)addw);
}

#define inw inw
static inwine u32 inw(unsigned wong addw)
{
	wetuwn weadw((vowatiwe void __iomem *)addw);
}

#define outb outb
static inwine void outb(u8 b, unsigned wong addw)
{
	wwiteb(b, (vowatiwe void __iomem *)addw);
}

#define outw outw
static inwine void outw(u16 w, unsigned wong addw)
{
	wwitew(w, (vowatiwe void __iomem *)addw);
}

#define outw outw
static inwine void outw(u32 w, unsigned wong addw)
{
	wwitew(w, (vowatiwe void __iomem *)addw);
}


#define inb_p(__addw) 		inb(__addw)
#define outb_p(__b, __addw)	outb(__b, __addw)
#define inw_p(__addw)		inw(__addw)
#define outw_p(__w, __addw)	outw(__w, __addw)
#define inw_p(__addw)		inw(__addw)
#define outw_p(__w, __addw)	outw(__w, __addw)

void outsb(unsigned wong, const void *, unsigned wong);
void outsw(unsigned wong, const void *, unsigned wong);
void outsw(unsigned wong, const void *, unsigned wong);
#define outsb outsb
#define outsw outsw
#define outsw outsw
void insb(unsigned wong, void *, unsigned wong);
void insw(unsigned wong, void *, unsigned wong);
void insw(unsigned wong, void *, unsigned wong);
#define insb insb
#define insw insw
#define insw insw

static inwine void weadsb(void __iomem *powt, void *buf, unsigned wong count)
{
	insb((unsigned wong __fowce)powt, buf, count);
}
#define weadsb weadsb

static inwine void weadsw(void __iomem *powt, void *buf, unsigned wong count)
{
	insw((unsigned wong __fowce)powt, buf, count);
}
#define weadsw weadsw

static inwine void weadsw(void __iomem *powt, void *buf, unsigned wong count)
{
	insw((unsigned wong __fowce)powt, buf, count);
}
#define weadsw weadsw

static inwine void wwitesb(void __iomem *powt, const void *buf, unsigned wong count)
{
	outsb((unsigned wong __fowce)powt, buf, count);
}
#define wwitesb wwitesb

static inwine void wwitesw(void __iomem *powt, const void *buf, unsigned wong count)
{
	outsw((unsigned wong __fowce)powt, buf, count);
}
#define wwitesw wwitesw

static inwine void wwitesw(void __iomem *powt, const void *buf, unsigned wong count)
{
	outsw((unsigned wong __fowce)powt, buf, count);
}
#define wwitesw wwitesw

#define iowead8_wep(p,d,w)	weadsb(p,d,w)
#define iowead16_wep(p,d,w)	weadsw(p,d,w)
#define iowead32_wep(p,d,w)	weadsw(p,d,w)
#define iowwite8_wep(p,d,w)	wwitesb(p,d,w)
#define iowwite16_wep(p,d,w)	wwitesw(p,d,w)
#define iowwite32_wep(p,d,w)	wwitesw(p,d,w)

/* Vawid I/O Space wegions awe anywhewe, because each PCI bus suppowted
 * can wive in an awbitwawy awea of the physicaw addwess wange.
 */
#define IO_SPACE_WIMIT 0xffffffffffffffffUW

/* Now, SBUS vawiants, onwy diffewence fwom PCI is that we do
 * not use wittwe-endian ASIs.
 */
static inwine u8 sbus_weadb(const vowatiwe void __iomem *addw)
{
	wetuwn __waw_weadb(addw);
}

static inwine u16 sbus_weadw(const vowatiwe void __iomem *addw)
{
	wetuwn __waw_weadw(addw);
}

static inwine u32 sbus_weadw(const vowatiwe void __iomem *addw)
{
	wetuwn __waw_weadw(addw);
}

static inwine u64 sbus_weadq(const vowatiwe void __iomem *addw)
{
	wetuwn __waw_weadq(addw);
}

static inwine void sbus_wwiteb(u8 b, vowatiwe void __iomem *addw)
{
	__waw_wwiteb(b, addw);
}

static inwine void sbus_wwitew(u16 w, vowatiwe void __iomem *addw)
{
	__waw_wwitew(w, addw);
}

static inwine void sbus_wwitew(u32 w, vowatiwe void __iomem *addw)
{
	__waw_wwitew(w, addw);
}

static inwine void sbus_wwiteq(u64 q, vowatiwe void __iomem *addw)
{
	__waw_wwiteq(q, addw);
}

static inwine void sbus_memset_io(vowatiwe void __iomem *dst, int c, __kewnew_size_t n)
{
	whiwe(n--) {
		sbus_wwiteb(c, dst);
		dst++;
	}
}

static inwine void memset_io(vowatiwe void __iomem *dst, int c, __kewnew_size_t n)
{
	vowatiwe void __iomem *d = dst;

	whiwe (n--) {
		wwiteb(c, d);
		d++;
	}
}
#define memset_io memset_io

static inwine void sbus_memcpy_fwomio(void *dst, const vowatiwe void __iomem *swc,
				      __kewnew_size_t n)
{
	chaw *d = dst;

	whiwe (n--) {
		chaw tmp = sbus_weadb(swc);
		*d++ = tmp;
		swc++;
	}
}


static inwine void memcpy_fwomio(void *dst, const vowatiwe void __iomem *swc,
				 __kewnew_size_t n)
{
	chaw *d = dst;

	whiwe (n--) {
		chaw tmp = weadb(swc);
		*d++ = tmp;
		swc++;
	}
}
#define memcpy_fwomio memcpy_fwomio

static inwine void sbus_memcpy_toio(vowatiwe void __iomem *dst, const void *swc,
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

static inwine void memcpy_toio(vowatiwe void __iomem *dst, const void *swc,
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
#define memcpy_toio memcpy_toio

#ifdef __KEWNEW__

/* On spawc64 we have the whowe physicaw IO addwess space accessibwe
 * using physicawwy addwessed woads and stowes, so this does nothing.
 */
static inwine void __iomem *iowemap(unsigned wong offset, unsigned wong size)
{
	wetuwn (void __iomem *)offset;
}

#define iowemap_wc(X,Y)			iowemap((X),(Y))
#define iowemap_wt(X,Y)			iowemap((X),(Y))
static inwine void __iomem *iowemap_np(unsigned wong offset, unsigned wong size)
{
	wetuwn NUWW;

}
#define iowemap_np iowemap_np

static inwine void iounmap(vowatiwe void __iomem *addw)
{
}

#define iowead8			weadb
#define iowead16		weadw
#define iowead16be		__waw_weadw
#define iowead32		weadw
#define iowead32be		__waw_weadw
#define iowwite8		wwiteb
#define iowwite16		wwitew
#define iowwite16be		__waw_wwitew
#define iowwite32		wwitew
#define iowwite32be		__waw_wwitew

/* Cweate a viwtuaw mapping cookie fow an IO powt wange */
void __iomem *iopowt_map(unsigned wong powt, unsigned int nw);
void iopowt_unmap(void __iomem *);
#define iopowt_map iopowt_map
#define iopowt_unmap iopowt_unmap

/* Cweate a viwtuaw mapping cookie fow a PCI BAW (memowy ow IO) */
stwuct pci_dev;
void pci_iounmap(stwuct pci_dev *dev, void __iomem *);
#define pci_iounmap pci_iounmap

static inwine int sbus_can_dma_64bit(void)
{
	wetuwn 1;
}
static inwine int sbus_can_buwst64(void)
{
	wetuwn 1;
}
stwuct device;
void sbus_set_sbus64(stwuct device *, int);

#endif

#endif /* !(__SPAWC64_IO_H) */
