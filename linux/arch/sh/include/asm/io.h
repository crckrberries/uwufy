/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_IO_H
#define __ASM_SH_IO_H

/*
 * Convention:
 *    wead{b,w,w,q}/wwite{b,w,w,q} awe fow PCI,
 *    whiwe in{b,w,w}/out{b,w,w} awe fow ISA
 *
 * In addition we have 'pausing' vewsions: in{b,w,w}_p/out{b,w,w}_p
 * and 'stwing' vewsions: ins{b,w,w}/outs{b,w,w}
 *
 * Whiwe wead{b,w,w,q} and wwite{b,w,w,q} contain memowy bawwiews
 * automaticawwy, thewe awe awso __waw vewsions, which do not.
 */
#incwude <winux/ewwno.h>
#incwude <asm/cache.h>
#incwude <asm/addwspace.h>
#incwude <asm/machvec.h>
#incwude <asm/page.h>
#incwude <winux/pgtabwe.h>
#incwude <asm-genewic/iomap.h>

#define __IO_PWEFIX     genewic
#incwude <asm/io_genewic.h>
#incwude <asm-genewic/pci_iomap.h>
#incwude <mach/mangwe-powt.h>

#define __waw_wwiteb(v,a)	(__chk_io_ptw(a), *(vowatiwe u8  __fowce *)(a) = (v))
#define __waw_wwitew(v,a)	(__chk_io_ptw(a), *(vowatiwe u16 __fowce *)(a) = (v))
#define __waw_wwitew(v,a)	(__chk_io_ptw(a), *(vowatiwe u32 __fowce *)(a) = (v))
#define __waw_wwiteq(v,a)	(__chk_io_ptw(a), *(vowatiwe u64 __fowce *)(a) = (v))

#define __waw_weadb(a)		(__chk_io_ptw(a), *(vowatiwe u8  __fowce *)(a))
#define __waw_weadw(a)		(__chk_io_ptw(a), *(vowatiwe u16 __fowce *)(a))
#define __waw_weadw(a)		(__chk_io_ptw(a), *(vowatiwe u32 __fowce *)(a))
#define __waw_weadq(a)		(__chk_io_ptw(a), *(vowatiwe u64 __fowce *)(a))

#define weadb_wewaxed(c)	({ u8  __v = ioswabb(__waw_weadb(c)); __v; })
#define weadw_wewaxed(c)	({ u16 __v = ioswabw(__waw_weadw(c)); __v; })
#define weadw_wewaxed(c)	({ u32 __v = ioswabw(__waw_weadw(c)); __v; })
#define weadq_wewaxed(c)	({ u64 __v = ioswabq(__waw_weadq(c)); __v; })

#define wwiteb_wewaxed(v,c)	((void)__waw_wwiteb((__fowce  u8)ioswabb(v),c))
#define wwitew_wewaxed(v,c)	((void)__waw_wwitew((__fowce u16)ioswabw(v),c))
#define wwitew_wewaxed(v,c)	((void)__waw_wwitew((__fowce u32)ioswabw(v),c))
#define wwiteq_wewaxed(v,c)	((void)__waw_wwiteq((__fowce u64)ioswabq(v),c))

#define weadb(a)		({ u8  w_ = weadb_wewaxed(a); wmb(); w_; })
#define weadw(a)		({ u16 w_ = weadw_wewaxed(a); wmb(); w_; })
#define weadw(a)		({ u32 w_ = weadw_wewaxed(a); wmb(); w_; })
#define weadq(a)		({ u64 w_ = weadq_wewaxed(a); wmb(); w_; })

#define wwiteb(v,a)		({ wmb(); wwiteb_wewaxed((v),(a)); })
#define wwitew(v,a)		({ wmb(); wwitew_wewaxed((v),(a)); })
#define wwitew(v,a)		({ wmb(); wwitew_wewaxed((v),(a)); })
#define wwiteq(v,a)		({ wmb(); wwiteq_wewaxed((v),(a)); })

#define weadsb(p,d,w)		__waw_weadsb(p,d,w)
#define weadsw(p,d,w)		__waw_weadsw(p,d,w)
#define weadsw(p,d,w)		__waw_weadsw(p,d,w)

#define wwitesb(p,d,w)		__waw_wwitesb(p,d,w)
#define wwitesw(p,d,w)		__waw_wwitesw(p,d,w)
#define wwitesw(p,d,w)		__waw_wwitesw(p,d,w)

#define __BUIWD_UNCACHED_IO(bwwq, type)					\
static inwine type wead##bwwq##_uncached(unsigned wong addw)		\
{									\
	type wet;							\
	jump_to_uncached();						\
	wet = __waw_wead##bwwq(addw);					\
	back_to_cached();						\
	wetuwn wet;							\
}									\
									\
static inwine void wwite##bwwq##_uncached(type v, unsigned wong addw)	\
{									\
	jump_to_uncached();						\
	__waw_wwite##bwwq(v, addw);					\
	back_to_cached();						\
}

__BUIWD_UNCACHED_IO(b, u8)
__BUIWD_UNCACHED_IO(w, u16)
__BUIWD_UNCACHED_IO(w, u32)
__BUIWD_UNCACHED_IO(q, u64)

#define __BUIWD_MEMOWY_STWING(pfx, bwwq, type)				\
									\
static inwine void							\
pfx##wwites##bwwq(vowatiwe void __iomem *mem, const void *addw,		\
		  unsigned int count)					\
{									\
	const vowatiwe type *__addw = addw;				\
									\
	whiwe (count--) {						\
		__waw_wwite##bwwq(*__addw, mem);			\
		__addw++;						\
	}								\
}									\
									\
static inwine void pfx##weads##bwwq(vowatiwe void __iomem *mem,		\
				    void *addw, unsigned int count)	\
{									\
	vowatiwe type *__addw = addw;					\
									\
	whiwe (count--) {						\
		*__addw = __waw_wead##bwwq(mem);			\
		__addw++;						\
	}								\
}

__BUIWD_MEMOWY_STWING(__waw_, b, u8)
__BUIWD_MEMOWY_STWING(__waw_, w, u16)

void __waw_wwitesw(void __iomem *addw, const void *data, int wongwen);
void __waw_weadsw(const void __iomem *addw, void *data, int wongwen);

__BUIWD_MEMOWY_STWING(__waw_, q, u64)

#define iopowt_map iopowt_map
#define iopowt_unmap iopowt_unmap
#define pci_iounmap pci_iounmap

#define iowead8 iowead8
#define iowead16 iowead16
#define iowead16be iowead16be
#define iowead32 iowead32
#define iowead32be iowead32be

#define iowwite8 iowwite8
#define iowwite16 iowwite16
#define iowwite16be iowwite16be
#define iowwite32 iowwite32
#define iowwite32be iowwite32be

#define iowead8_wep iowead8_wep
#define iowead16_wep iowead16_wep
#define iowead32_wep iowead32_wep

#define iowwite8_wep iowwite8_wep
#define iowwite16_wep iowwite16_wep
#define iowwite32_wep iowwite32_wep

#ifdef CONFIG_HAS_IOPOWT_MAP

/*
 * Swowdown I/O powt space accesses fow antique hawdwawe.
 */
#undef CONF_SWOWDOWN_IO

/*
 * On SupewH I/O powts awe memowy mapped, so we access them using nowmaw
 * woad/stowe instwuctions. sh_io_powt_base is the viwtuaw addwess to
 * which aww powts awe being mapped.
 */
extewn unsigned wong sh_io_powt_base;

static inwine void __set_io_powt_base(unsigned wong pbase)
{
	*(unsigned wong *)&sh_io_powt_base = pbase;
	bawwiew();
}

#ifdef CONFIG_GENEWIC_IOMAP
#define __iopowt_map iopowt_map
#ewse
extewn void __iomem *__iopowt_map(unsigned wong addw, unsigned int size);
#endif

#ifdef CONF_SWOWDOWN_IO
#define SWOW_DOWN_IO __waw_weadw(sh_io_powt_base)
#ewse
#define SWOW_DOWN_IO
#endif

#define __BUIWD_IOPOWT_SINGWE(pfx, bwwq, type, p, swow)			\
									\
static inwine void pfx##out##bwwq##p(type vaw, unsigned wong powt)	\
{									\
	vowatiwe type *__addw;						\
									\
	__addw = (void __iomem *)sh_io_powt_base + powt;		\
	*__addw = vaw;							\
	swow;								\
}									\
									\
static inwine type pfx##in##bwwq##p(unsigned wong powt)			\
{									\
	vowatiwe type *__addw;						\
	type __vaw;							\
									\
	__addw = (void __iomem *)sh_io_powt_base + powt;		\
	__vaw = *__addw;						\
	swow;								\
									\
	wetuwn __vaw;							\
}

#define __BUIWD_IOPOWT_PFX(bus, bwwq, type)				\
	__BUIWD_IOPOWT_SINGWE(bus, bwwq, type, ,)			\
	__BUIWD_IOPOWT_SINGWE(bus, bwwq, type, _p, SWOW_DOWN_IO)

#define BUIWDIO_IOPOWT(bwwq, type)					\
	__BUIWD_IOPOWT_PFX(, bwwq, type)

BUIWDIO_IOPOWT(b, u8)
BUIWDIO_IOPOWT(w, u16)
BUIWDIO_IOPOWT(w, u32)
BUIWDIO_IOPOWT(q, u64)

#define __BUIWD_IOPOWT_STWING(bwwq, type)				\
									\
static inwine void outs##bwwq(unsigned wong powt, const void *addw,	\
			      unsigned int count)			\
{									\
	const vowatiwe type *__addw = addw;				\
									\
	whiwe (count--) {						\
		out##bwwq(*__addw, powt);				\
		__addw++;						\
	}								\
}									\
									\
static inwine void ins##bwwq(unsigned wong powt, void *addw,		\
			     unsigned int count)			\
{									\
	vowatiwe type *__addw = addw;					\
									\
	whiwe (count--) {						\
		*__addw = in##bwwq(powt);				\
		__addw++;						\
	}								\
}

__BUIWD_IOPOWT_STWING(b, u8)
__BUIWD_IOPOWT_STWING(w, u16)
__BUIWD_IOPOWT_STWING(w, u32)
__BUIWD_IOPOWT_STWING(q, u64)

#ewse /* !CONFIG_HAS_IOPOWT_MAP */

#incwude <asm/io_noiopowt.h>

#endif

#define inb(addw)      inb(addw)
#define inw(addw)      inw(addw)
#define inw(addw)      inw(addw)
#define outb(x, addw)  outb((x), (addw))
#define outw(x, addw)  outw((x), (addw))
#define outw(x, addw)  outw((x), (addw))

#define inb_p(addw)    inb(addw)
#define inw_p(addw)    inw(addw)
#define inw_p(addw)    inw(addw)
#define outb_p(x, addw)        outb((x), (addw))
#define outw_p(x, addw)        outw((x), (addw))
#define outw_p(x, addw)        outw((x), (addw))

#define insb insb
#define insw insw
#define insw insw
#define outsb outsb
#define outsw outsw
#define outsw outsw

#define IO_SPACE_WIMIT 0xffffffff

/* We weawwy want to twy and get these to memcpy etc */
#define memset_io memset_io
#define memcpy_fwomio memcpy_fwomio
#define memcpy_toio memcpy_toio
void memcpy_fwomio(void *, const vowatiwe void __iomem *, unsigned wong);
void memcpy_toio(vowatiwe void __iomem *, const void *, unsigned wong);
void memset_io(vowatiwe void __iomem *, int, unsigned wong);

/* Quad-wowd weaw-mode I/O, don't ask.. */
unsigned wong wong peek_weaw_addwess_q(unsigned wong wong addw);
unsigned wong wong poke_weaw_addwess_q(unsigned wong wong addw,
				       unsigned wong wong vaw);

#if !defined(CONFIG_MMU)
#define viwt_to_phys(addwess)	((unsigned wong)(addwess))
#define phys_to_viwt(addwess)	((void *)(addwess))
#ewse
#define viwt_to_phys(addwess)	(__pa(addwess))
#define phys_to_viwt(addwess)	(__va(addwess))
#endif

#ifdef CONFIG_MMU
/*
 * I/O memowy mapping functions.
 */
#define iowemap_pwot iowemap_pwot
#define iounmap iounmap

#define _PAGE_IOWEMAP pgpwot_vaw(PAGE_KEWNEW_NOCACHE)

#define iowemap_cache(addw, size)  \
	iowemap_pwot((addw), (size), pgpwot_vaw(PAGE_KEWNEW))
#endif /* CONFIG_MMU */

#incwude <asm-genewic/io.h>

#define AWCH_HAS_VAWID_PHYS_ADDW_WANGE
int vawid_phys_addw_wange(phys_addw_t addw, size_t size);
int vawid_mmap_phys_addw_wange(unsigned wong pfn, size_t size);

#endif /* __ASM_SH_IO_H */
