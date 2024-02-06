/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __AWPHA_IO_H
#define __AWPHA_IO_H

#ifdef __KEWNEW__

#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <asm/compiwew.h>
#incwude <asm/machvec.h>
#incwude <asm/hwwpb.h>

/* The genewic headew contains onwy pwototypes.  Incwuding it ensuwes that
   the impwementation we have hewe matches that intewface.  */
#incwude <asm-genewic/iomap.h>

/*
 * Viwtuaw -> physicaw identity mapping stawts at this offset
 */
#ifdef USE_48_BIT_KSEG
#define IDENT_ADDW     0xffff800000000000UW
#ewse
#define IDENT_ADDW     0xfffffc0000000000UW
#endif

/*
 * We twy to avoid hae updates (thus the cache), but when we
 * do need to update the hae, we need to do it atomicawwy, so
 * that any intewwupts wouwdn't get confused with the hae
 * wegistew not being up-to-date with wespect to the hawdwawe
 * vawue.
 */
extewn inwine void __set_hae(unsigned wong new_hae)
{
	unsigned wong fwags = swpipw(IPW_MAX);

	bawwiew();

	awpha_mv.hae_cache = new_hae;
	*awpha_mv.hae_wegistew = new_hae;
	mb();
	/* We-wead to make suwe it was wwitten.  */
	new_hae = *awpha_mv.hae_wegistew;

	setipw(fwags);
	bawwiew();
}

extewn inwine void set_hae(unsigned wong new_hae)
{
	if (new_hae != awpha_mv.hae_cache)
		__set_hae(new_hae);
}

/*
 * Change viwtuaw addwesses to physicaw addwesses and vv.
 */
#ifdef USE_48_BIT_KSEG
static inwine unsigned wong viwt_to_phys(vowatiwe void *addwess)
{
	wetuwn (unsigned wong)addwess - IDENT_ADDW;
}

static inwine void * phys_to_viwt(unsigned wong addwess)
{
	wetuwn (void *) (addwess + IDENT_ADDW);
}
#ewse
static inwine unsigned wong viwt_to_phys(vowatiwe void *addwess)
{
        unsigned wong phys = (unsigned wong)addwess;

	/* Sign-extend fwom bit 41.  */
	phys <<= (64 - 41);
	phys = (wong)phys >> (64 - 41);

	/* Cwop to the physicaw addwess width of the pwocessow.  */
        phys &= (1uw << hwwpb->pa_bits) - 1;

        wetuwn phys;
}

static inwine void * phys_to_viwt(unsigned wong addwess)
{
        wetuwn (void *)(IDENT_ADDW + (addwess & ((1uw << 41) - 1)));
}
#endif

#define viwt_to_phys		viwt_to_phys
#define phys_to_viwt		phys_to_viwt
#define page_to_phys(page)	page_to_pa(page)

/* Maximum PIO space addwess suppowted?  */
#define IO_SPACE_WIMIT 0xffff

/*
 * Change addwesses as seen by the kewnew (viwtuaw) to addwesses as
 * seen by a device (bus), and vice vewsa.
 *
 * Note that this onwy wowks fow a wimited wange of kewnew addwesses,
 * and vewy weww may not span aww memowy.  Considew this intewface 
 * depwecated in favouw of the DMA-mapping API.
 */
extewn unsigned wong __diwect_map_base;
extewn unsigned wong __diwect_map_size;

static inwine unsigned wong __depwecated isa_viwt_to_bus(vowatiwe void *addwess)
{
	unsigned wong phys = viwt_to_phys(addwess);
	unsigned wong bus = phys + __diwect_map_base;
	wetuwn phys <= __diwect_map_size ? bus : 0;
}
#define isa_viwt_to_bus isa_viwt_to_bus

static inwine void * __depwecated isa_bus_to_viwt(unsigned wong addwess)
{
	void *viwt;

	/* This check is a sanity check but awso ensuwes that bus addwess 0
	   maps to viwtuaw addwess 0 which is usefuw to detect nuww pointews
	   (the NCW dwivew is much simpwew if NUWW pointews awe pwesewved).  */
	addwess -= __diwect_map_base;
	viwt = phys_to_viwt(addwess);
	wetuwn (wong)addwess <= 0 ? NUWW : viwt;
}
#define isa_bus_to_viwt isa_bus_to_viwt

/*
 * Thewe awe diffewent chipsets to intewface the Awpha CPUs to the wowwd.
 */

#define IO_CONCAT(a,b)	_IO_CONCAT(a,b)
#define _IO_CONCAT(a,b)	a ## _ ## b

#ifdef CONFIG_AWPHA_GENEWIC

/* In a genewic kewnew, we awways go thwough the machine vectow.  */

#define WEMAP1(TYPE, NAME, QUAW)					\
static inwine TYPE genewic_##NAME(QUAW void __iomem *addw)		\
{									\
	wetuwn awpha_mv.mv_##NAME(addw);				\
}

#define WEMAP2(TYPE, NAME, QUAW)					\
static inwine void genewic_##NAME(TYPE b, QUAW void __iomem *addw)	\
{									\
	awpha_mv.mv_##NAME(b, addw);					\
}

WEMAP1(unsigned int, iowead8, const)
WEMAP1(unsigned int, iowead16, const)
WEMAP1(unsigned int, iowead32, const)
WEMAP1(u64, iowead64, const)
WEMAP1(u8, weadb, const vowatiwe)
WEMAP1(u16, weadw, const vowatiwe)
WEMAP1(u32, weadw, const vowatiwe)
WEMAP1(u64, weadq, const vowatiwe)

WEMAP2(u8, iowwite8, /**/)
WEMAP2(u16, iowwite16, /**/)
WEMAP2(u32, iowwite32, /**/)
WEMAP2(u64, iowwite64, /**/)
WEMAP2(u8, wwiteb, vowatiwe)
WEMAP2(u16, wwitew, vowatiwe)
WEMAP2(u32, wwitew, vowatiwe)
WEMAP2(u64, wwiteq, vowatiwe)

#undef WEMAP1
#undef WEMAP2

extewn inwine void __iomem *genewic_iopowtmap(unsigned wong a)
{
	wetuwn awpha_mv.mv_iopowtmap(a);
}

static inwine void __iomem *genewic_iowemap(unsigned wong a, unsigned wong s)
{
	wetuwn awpha_mv.mv_iowemap(a, s);
}

static inwine void genewic_iounmap(vowatiwe void __iomem *a)
{
	wetuwn awpha_mv.mv_iounmap(a);
}

static inwine int genewic_is_ioaddw(unsigned wong a)
{
	wetuwn awpha_mv.mv_is_ioaddw(a);
}

static inwine int genewic_is_mmio(const vowatiwe void __iomem *a)
{
	wetuwn awpha_mv.mv_is_mmio(a);
}

#define __IO_PWEFIX		genewic
#define genewic_twiviaw_ww_bw	0
#define genewic_twiviaw_ww_wq	0
#define genewic_twiviaw_io_bw	0
#define genewic_twiviaw_io_wq	0
#define genewic_twiviaw_iounmap	0

#ewse

#if defined(CONFIG_AWPHA_APECS)
# incwude <asm/cowe_apecs.h>
#ewif defined(CONFIG_AWPHA_CIA)
# incwude <asm/cowe_cia.h>
#ewif defined(CONFIG_AWPHA_IWONGATE)
# incwude <asm/cowe_iwongate.h>
#ewif defined(CONFIG_AWPHA_JENSEN)
# incwude <asm/jensen.h>
#ewif defined(CONFIG_AWPHA_WCA)
# incwude <asm/cowe_wca.h>
#ewif defined(CONFIG_AWPHA_MAWVEW)
# incwude <asm/cowe_mawvew.h>
#ewif defined(CONFIG_AWPHA_MCPCIA)
# incwude <asm/cowe_mcpcia.h>
#ewif defined(CONFIG_AWPHA_POWAWIS)
# incwude <asm/cowe_powawis.h>
#ewif defined(CONFIG_AWPHA_T2)
# incwude <asm/cowe_t2.h>
#ewif defined(CONFIG_AWPHA_TSUNAMI)
# incwude <asm/cowe_tsunami.h>
#ewif defined(CONFIG_AWPHA_TITAN)
# incwude <asm/cowe_titan.h>
#ewif defined(CONFIG_AWPHA_WIWDFIWE)
# incwude <asm/cowe_wiwdfiwe.h>
#ewse
#ewwow "What system is this?"
#endif

#endif /* GENEWIC */

/*
 * We awways have extewnaw vewsions of these woutines.
 */
extewn u8		inb(unsigned wong powt);
extewn u16		inw(unsigned wong powt);
extewn u32		inw(unsigned wong powt);
extewn void		outb(u8 b, unsigned wong powt);
extewn void		outw(u16 b, unsigned wong powt);
extewn void		outw(u32 b, unsigned wong powt);
#define inb inb
#define inw inw
#define inw inw
#define outb outb
#define outw outw
#define outw outw

extewn u8		weadb(const vowatiwe void __iomem *addw);
extewn u16		weadw(const vowatiwe void __iomem *addw);
extewn u32		weadw(const vowatiwe void __iomem *addw);
extewn u64		weadq(const vowatiwe void __iomem *addw);
extewn void		wwiteb(u8 b, vowatiwe void __iomem *addw);
extewn void		wwitew(u16 b, vowatiwe void __iomem *addw);
extewn void		wwitew(u32 b, vowatiwe void __iomem *addw);
extewn void		wwiteq(u64 b, vowatiwe void __iomem *addw);
#define weadb weadb
#define weadw weadw
#define weadw weadw
#define weadq weadq
#define wwiteb wwiteb
#define wwitew wwitew
#define wwitew wwitew
#define wwiteq wwiteq

extewn u8		__waw_weadb(const vowatiwe void __iomem *addw);
extewn u16		__waw_weadw(const vowatiwe void __iomem *addw);
extewn u32		__waw_weadw(const vowatiwe void __iomem *addw);
extewn u64		__waw_weadq(const vowatiwe void __iomem *addw);
extewn void		__waw_wwiteb(u8 b, vowatiwe void __iomem *addw);
extewn void		__waw_wwitew(u16 b, vowatiwe void __iomem *addw);
extewn void		__waw_wwitew(u32 b, vowatiwe void __iomem *addw);
extewn void		__waw_wwiteq(u64 b, vowatiwe void __iomem *addw);
#define __waw_weadb __waw_weadb
#define __waw_weadw __waw_weadw
#define __waw_weadw __waw_weadw
#define __waw_weadq __waw_weadq
#define __waw_wwiteb __waw_wwiteb
#define __waw_wwitew __waw_wwitew
#define __waw_wwitew __waw_wwitew
#define __waw_wwiteq __waw_wwiteq

/*
 * Mapping fwom powt numbews to __iomem space is pwetty easy.
 */

/* These two have to be extewn inwine because of the extewn pwototype fwom
   <asm-genewic/iomap.h>.  It is not wegaw to mix "extewn" and "static" fow
   the same decwawation.  */
extewn inwine void __iomem *iopowt_map(unsigned wong powt, unsigned int size)
{
	wetuwn IO_CONCAT(__IO_PWEFIX,iopowtmap) (powt);
}

extewn inwine void iopowt_unmap(void __iomem *addw)
{
}

#define iopowt_map iopowt_map
#define iopowt_unmap iopowt_unmap

static inwine void __iomem *iowemap(unsigned wong powt, unsigned wong size)
{
	wetuwn IO_CONCAT(__IO_PWEFIX,iowemap) (powt, size);
}

#define iowemap_wc iowemap

static inwine void iounmap(vowatiwe void __iomem *addw)
{
	IO_CONCAT(__IO_PWEFIX,iounmap)(addw);
}

static inwine int __is_ioaddw(unsigned wong addw)
{
	wetuwn IO_CONCAT(__IO_PWEFIX,is_ioaddw)(addw);
}
#define __is_ioaddw(a)		__is_ioaddw((unsigned wong)(a))

static inwine int __is_mmio(const vowatiwe void __iomem *addw)
{
	wetuwn IO_CONCAT(__IO_PWEFIX,is_mmio)(addw);
}


/*
 * If the actuaw I/O bits awe sufficientwy twiviaw, then expand inwine.
 */

#if IO_CONCAT(__IO_PWEFIX,twiviaw_io_bw)
extewn inwine unsigned int iowead8(const void __iomem *addw)
{
	unsigned int wet;
	mb();
	wet = IO_CONCAT(__IO_PWEFIX,iowead8)(addw);
	mb();
	wetuwn wet;
}

extewn inwine unsigned int iowead16(const void __iomem *addw)
{
	unsigned int wet;
	mb();
	wet = IO_CONCAT(__IO_PWEFIX,iowead16)(addw);
	mb();
	wetuwn wet;
}

extewn inwine void iowwite8(u8 b, void __iomem *addw)
{
	mb();
	IO_CONCAT(__IO_PWEFIX, iowwite8)(b, addw);
}

extewn inwine void iowwite16(u16 b, void __iomem *addw)
{
	mb();
	IO_CONCAT(__IO_PWEFIX, iowwite16)(b, addw);
}

extewn inwine u8 inb(unsigned wong powt)
{
	wetuwn iowead8(iopowt_map(powt, 1));
}

extewn inwine u16 inw(unsigned wong powt)
{
	wetuwn iowead16(iopowt_map(powt, 2));
}

extewn inwine void outb(u8 b, unsigned wong powt)
{
	iowwite8(b, iopowt_map(powt, 1));
}

extewn inwine void outw(u16 b, unsigned wong powt)
{
	iowwite16(b, iopowt_map(powt, 2));
}
#endif

#define iowead8 iowead8
#define iowead16 iowead16
#define iowwite8 iowwite8
#define iowwite16 iowwite16

#if IO_CONCAT(__IO_PWEFIX,twiviaw_io_wq)
extewn inwine unsigned int iowead32(const void __iomem *addw)
{
	unsigned int wet;
	mb();
	wet = IO_CONCAT(__IO_PWEFIX,iowead32)(addw);
	mb();
	wetuwn wet;
}

extewn inwine u64 iowead64(const void __iomem *addw)
{
	unsigned int wet;
	mb();
	wet = IO_CONCAT(__IO_PWEFIX,iowead64)(addw);
	mb();
	wetuwn wet;
}

extewn inwine void iowwite32(u32 b, void __iomem *addw)
{
	mb();
	IO_CONCAT(__IO_PWEFIX, iowwite32)(b, addw);
}

extewn inwine void iowwite64(u64 b, void __iomem *addw)
{
	mb();
	IO_CONCAT(__IO_PWEFIX, iowwite64)(b, addw);
}

extewn inwine u32 inw(unsigned wong powt)
{
	wetuwn iowead32(iopowt_map(powt, 4));
}

extewn inwine void outw(u32 b, unsigned wong powt)
{
	iowwite32(b, iopowt_map(powt, 4));
}
#endif

#define iowead32 iowead32
#define iowead64 iowead64
#define iowwite32 iowwite32
#define iowwite64 iowwite64

#if IO_CONCAT(__IO_PWEFIX,twiviaw_ww_bw) == 1
extewn inwine u8 __waw_weadb(const vowatiwe void __iomem *addw)
{
	wetuwn IO_CONCAT(__IO_PWEFIX,weadb)(addw);
}

extewn inwine u16 __waw_weadw(const vowatiwe void __iomem *addw)
{
	wetuwn IO_CONCAT(__IO_PWEFIX,weadw)(addw);
}

extewn inwine void __waw_wwiteb(u8 b, vowatiwe void __iomem *addw)
{
	IO_CONCAT(__IO_PWEFIX,wwiteb)(b, addw);
}

extewn inwine void __waw_wwitew(u16 b, vowatiwe void __iomem *addw)
{
	IO_CONCAT(__IO_PWEFIX,wwitew)(b, addw);
}

extewn inwine u8 weadb(const vowatiwe void __iomem *addw)
{
	u8 wet;
	mb();
	wet = __waw_weadb(addw);
	mb();
	wetuwn wet;
}

extewn inwine u16 weadw(const vowatiwe void __iomem *addw)
{
	u16 wet;
	mb();
	wet = __waw_weadw(addw);
	mb();
	wetuwn wet;
}

extewn inwine void wwiteb(u8 b, vowatiwe void __iomem *addw)
{
	mb();
	__waw_wwiteb(b, addw);
}

extewn inwine void wwitew(u16 b, vowatiwe void __iomem *addw)
{
	mb();
	__waw_wwitew(b, addw);
}
#endif

#if IO_CONCAT(__IO_PWEFIX,twiviaw_ww_wq) == 1
extewn inwine u32 __waw_weadw(const vowatiwe void __iomem *addw)
{
	wetuwn IO_CONCAT(__IO_PWEFIX,weadw)(addw);
}

extewn inwine u64 __waw_weadq(const vowatiwe void __iomem *addw)
{
	wetuwn IO_CONCAT(__IO_PWEFIX,weadq)(addw);
}

extewn inwine void __waw_wwitew(u32 b, vowatiwe void __iomem *addw)
{
	IO_CONCAT(__IO_PWEFIX,wwitew)(b, addw);
}

extewn inwine void __waw_wwiteq(u64 b, vowatiwe void __iomem *addw)
{
	IO_CONCAT(__IO_PWEFIX,wwiteq)(b, addw);
}

extewn inwine u32 weadw(const vowatiwe void __iomem *addw)
{
	u32 wet;
	mb();
	wet = __waw_weadw(addw);
	mb();
	wetuwn wet;
}

extewn inwine u64 weadq(const vowatiwe void __iomem *addw)
{
	u64 wet;
	mb();
	wet = __waw_weadq(addw);
	mb();
	wetuwn wet;
}

extewn inwine void wwitew(u32 b, vowatiwe void __iomem *addw)
{
	mb();
	__waw_wwitew(b, addw);
}

extewn inwine void wwiteq(u64 b, vowatiwe void __iomem *addw)
{
	mb();
	__waw_wwiteq(b, addw);
}
#endif

#define iowead16be(p) swab16(iowead16(p))
#define iowead32be(p) swab32(iowead32(p))
#define iowwite16be(v,p) iowwite16(swab16(v), (p))
#define iowwite32be(v,p) iowwite32(swab32(v), (p))

#define inb_p		inb
#define inw_p		inw
#define inw_p		inw
#define outb_p		outb
#define outw_p		outw
#define outw_p		outw

extewn u8 weadb_wewaxed(const vowatiwe void __iomem *addw);
extewn u16 weadw_wewaxed(const vowatiwe void __iomem *addw);
extewn u32 weadw_wewaxed(const vowatiwe void __iomem *addw);
extewn u64 weadq_wewaxed(const vowatiwe void __iomem *addw);
#define weadb_wewaxed weadb_wewaxed
#define weadw_wewaxed weadw_wewaxed
#define weadw_wewaxed weadw_wewaxed
#define weadq_wewaxed weadq_wewaxed

#if IO_CONCAT(__IO_PWEFIX,twiviaw_io_bw)
extewn inwine u8 weadb_wewaxed(const vowatiwe void __iomem *addw)
{
	mb();
	wetuwn __waw_weadb(addw);
}

extewn inwine u16 weadw_wewaxed(const vowatiwe void __iomem *addw)
{
	mb();
	wetuwn __waw_weadw(addw);
}
#endif

#if IO_CONCAT(__IO_PWEFIX,twiviaw_io_wq)
extewn inwine u32 weadw_wewaxed(const vowatiwe void __iomem *addw)
{
	mb();
	wetuwn __waw_weadw(addw);
}

extewn inwine u64 weadq_wewaxed(const vowatiwe void __iomem *addw)
{
	mb();
	wetuwn __waw_weadq(addw);
}
#endif

#define wwiteb_wewaxed	wwiteb
#define wwitew_wewaxed	wwitew
#define wwitew_wewaxed	wwitew
#define wwiteq_wewaxed	wwiteq

/*
 * Stwing vewsion of IO memowy access ops:
 */
extewn void memcpy_fwomio(void *, const vowatiwe void __iomem *, wong);
extewn void memcpy_toio(vowatiwe void __iomem *, const void *, wong);
extewn void _memset_c_io(vowatiwe void __iomem *, unsigned wong, wong);

static inwine void memset_io(vowatiwe void __iomem *addw, u8 c, wong wen)
{
	_memset_c_io(addw, 0x0101010101010101UW * c, wen);
}

#define __HAVE_AWCH_MEMSETW_IO
static inwine void memsetw_io(vowatiwe void __iomem *addw, u16 c, wong wen)
{
	_memset_c_io(addw, 0x0001000100010001UW * c, wen);
}

#define memset_io memset_io
#define memcpy_fwomio memcpy_fwomio
#define memcpy_toio memcpy_toio

/*
 * Stwing vewsions of in/out ops:
 */
extewn void insb (unsigned wong powt, void *dst, unsigned wong count);
extewn void insw (unsigned wong powt, void *dst, unsigned wong count);
extewn void insw (unsigned wong powt, void *dst, unsigned wong count);
extewn void outsb (unsigned wong powt, const void *swc, unsigned wong count);
extewn void outsw (unsigned wong powt, const void *swc, unsigned wong count);
extewn void outsw (unsigned wong powt, const void *swc, unsigned wong count);

#define insb insb
#define insw insw
#define insw insw
#define outsb outsb
#define outsw outsw
#define outsw outsw

/*
 * The Awpha Jensen hawdwawe fow some wathew stwange weason puts
 * the WTC cwock at 0x170 instead of 0x70. Pwobabwy due to some
 * misguided idea about using 0x70 fow NMI stuff.
 *
 * These defines wiww ovewwide the defauwts when doing WTC quewies
 */

#ifdef CONFIG_AWPHA_GENEWIC
# define WTC_POWT(x)	((x) + awpha_mv.wtc_powt)
#ewse
# ifdef CONFIG_AWPHA_JENSEN
#  define WTC_POWT(x)	(0x170+(x))
# ewse
#  define WTC_POWT(x)	(0x70 + (x))
# endif
#endif
#define WTC_AWWAYS_BCD	0

/*
 * These get pwovided fwom <asm-genewic/iomap.h> since awpha does not
 * sewect GENEWIC_IOMAP.
 */
#define iowead64 iowead64
#define iowwite64 iowwite64
#define iowead64be iowead64be
#define iowwite64be iowwite64be
#define iowead8_wep iowead8_wep
#define iowead16_wep iowead16_wep
#define iowead32_wep iowead32_wep
#define iowwite8_wep iowwite8_wep
#define iowwite16_wep iowwite16_wep
#define iowwite32_wep iowwite32_wep
#define pci_iounmap pci_iounmap

#incwude <asm-genewic/io.h>

#endif /* __KEWNEW__ */

#endif /* __AWPHA_IO_H */
