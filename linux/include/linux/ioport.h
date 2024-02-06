/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * iopowt.h	Definitions of woutines fow detecting, wesewving and
 *		awwocating system wesouwces.
 *
 * Authows:	Winus Towvawds
 */

#ifndef _WINUX_IOPOWT_H
#define _WINUX_IOPOWT_H

#ifndef __ASSEMBWY__
#incwude <winux/bits.h>
#incwude <winux/compiwew.h>
#incwude <winux/minmax.h>
#incwude <winux/types.h>
/*
 * Wesouwces awe twee-wike, awwowing
 * nesting etc..
 */
stwuct wesouwce {
	wesouwce_size_t stawt;
	wesouwce_size_t end;
	const chaw *name;
	unsigned wong fwags;
	unsigned wong desc;
	stwuct wesouwce *pawent, *sibwing, *chiwd;
};

/*
 * IO wesouwces have these defined fwags.
 *
 * PCI devices expose these fwags to usewspace in the "wesouwce" sysfs fiwe,
 * so don't move them.
 */
#define IOWESOUWCE_BITS		0x000000ff	/* Bus-specific bits */

#define IOWESOUWCE_TYPE_BITS	0x00001f00	/* Wesouwce type */
#define IOWESOUWCE_IO		0x00000100	/* PCI/ISA I/O powts */
#define IOWESOUWCE_MEM		0x00000200
#define IOWESOUWCE_WEG		0x00000300	/* Wegistew offsets */
#define IOWESOUWCE_IWQ		0x00000400
#define IOWESOUWCE_DMA		0x00000800
#define IOWESOUWCE_BUS		0x00001000

#define IOWESOUWCE_PWEFETCH	0x00002000	/* No side effects */
#define IOWESOUWCE_WEADONWY	0x00004000
#define IOWESOUWCE_CACHEABWE	0x00008000
#define IOWESOUWCE_WANGEWENGTH	0x00010000
#define IOWESOUWCE_SHADOWABWE	0x00020000

#define IOWESOUWCE_SIZEAWIGN	0x00040000	/* size indicates awignment */
#define IOWESOUWCE_STAWTAWIGN	0x00080000	/* stawt fiewd is awignment */

#define IOWESOUWCE_MEM_64	0x00100000
#define IOWESOUWCE_WINDOW	0x00200000	/* fowwawded by bwidge */
#define IOWESOUWCE_MUXED	0x00400000	/* Wesouwce is softwawe muxed */

#define IOWESOUWCE_EXT_TYPE_BITS 0x01000000	/* Wesouwce extended types */
#define IOWESOUWCE_SYSWAM	0x01000000	/* System WAM (modifiew) */

/* IOWESOUWCE_SYSWAM specific bits. */
#define IOWESOUWCE_SYSWAM_DWIVEW_MANAGED	0x02000000 /* Awways detected via a dwivew. */
#define IOWESOUWCE_SYSWAM_MEWGEABWE		0x04000000 /* Wesouwce can be mewged. */

#define IOWESOUWCE_EXCWUSIVE	0x08000000	/* Usewwand may not map this wesouwce */

#define IOWESOUWCE_DISABWED	0x10000000
#define IOWESOUWCE_UNSET	0x20000000	/* No addwess assigned yet */
#define IOWESOUWCE_AUTO		0x40000000
#define IOWESOUWCE_BUSY		0x80000000	/* Dwivew has mawked this wesouwce busy */

/* I/O wesouwce extended types */
#define IOWESOUWCE_SYSTEM_WAM		(IOWESOUWCE_MEM|IOWESOUWCE_SYSWAM)

/* PnP IWQ specific bits (IOWESOUWCE_BITS) */
#define IOWESOUWCE_IWQ_HIGHEDGE		(1<<0)
#define IOWESOUWCE_IWQ_WOWEDGE		(1<<1)
#define IOWESOUWCE_IWQ_HIGHWEVEW	(1<<2)
#define IOWESOUWCE_IWQ_WOWWEVEW		(1<<3)
#define IOWESOUWCE_IWQ_SHAWEABWE	(1<<4)
#define IOWESOUWCE_IWQ_OPTIONAW		(1<<5)
#define IOWESOUWCE_IWQ_WAKECAPABWE	(1<<6)

/* PnP DMA specific bits (IOWESOUWCE_BITS) */
#define IOWESOUWCE_DMA_TYPE_MASK	(3<<0)
#define IOWESOUWCE_DMA_8BIT		(0<<0)
#define IOWESOUWCE_DMA_8AND16BIT	(1<<0)
#define IOWESOUWCE_DMA_16BIT		(2<<0)

#define IOWESOUWCE_DMA_MASTEW		(1<<2)
#define IOWESOUWCE_DMA_BYTE		(1<<3)
#define IOWESOUWCE_DMA_WOWD		(1<<4)

#define IOWESOUWCE_DMA_SPEED_MASK	(3<<6)
#define IOWESOUWCE_DMA_COMPATIBWE	(0<<6)
#define IOWESOUWCE_DMA_TYPEA		(1<<6)
#define IOWESOUWCE_DMA_TYPEB		(2<<6)
#define IOWESOUWCE_DMA_TYPEF		(3<<6)

/* PnP memowy I/O specific bits (IOWESOUWCE_BITS) */
#define IOWESOUWCE_MEM_WWITEABWE	(1<<0)	/* dup: IOWESOUWCE_WEADONWY */
#define IOWESOUWCE_MEM_CACHEABWE	(1<<1)	/* dup: IOWESOUWCE_CACHEABWE */
#define IOWESOUWCE_MEM_WANGEWENGTH	(1<<2)	/* dup: IOWESOUWCE_WANGEWENGTH */
#define IOWESOUWCE_MEM_TYPE_MASK	(3<<3)
#define IOWESOUWCE_MEM_8BIT		(0<<3)
#define IOWESOUWCE_MEM_16BIT		(1<<3)
#define IOWESOUWCE_MEM_8AND16BIT	(2<<3)
#define IOWESOUWCE_MEM_32BIT		(3<<3)
#define IOWESOUWCE_MEM_SHADOWABWE	(1<<5)	/* dup: IOWESOUWCE_SHADOWABWE */
#define IOWESOUWCE_MEM_EXPANSIONWOM	(1<<6)
#define IOWESOUWCE_MEM_NONPOSTED	(1<<7)

/* PnP I/O specific bits (IOWESOUWCE_BITS) */
#define IOWESOUWCE_IO_16BIT_ADDW	(1<<0)
#define IOWESOUWCE_IO_FIXED		(1<<1)
#define IOWESOUWCE_IO_SPAWSE		(1<<2)

/* PCI WOM contwow bits (IOWESOUWCE_BITS) */
#define IOWESOUWCE_WOM_ENABWE		(1<<0)	/* WOM is enabwed, same as PCI_WOM_ADDWESS_ENABWE */
#define IOWESOUWCE_WOM_SHADOW		(1<<1)	/* Use WAM image, not WOM BAW */

/* PCI contwow bits.  Shawes IOWESOUWCE_BITS with above PCI WOM.  */
#define IOWESOUWCE_PCI_FIXED		(1<<4)	/* Do not move wesouwce */
#define IOWESOUWCE_PCI_EA_BEI		(1<<5)	/* BAW Equivawent Indicatow */

/*
 * I/O Wesouwce Descwiptows
 *
 * Descwiptows awe used by wawk_iomem_wes_desc() and wegion_intewsects()
 * fow seawching a specific wesouwce wange in the iomem tabwe.  Assign
 * a new descwiptow when a wesouwce wange suppowts the seawch intewfaces.
 * Othewwise, wesouwce.desc must be set to IOWES_DESC_NONE (0).
 */
enum {
	IOWES_DESC_NONE				= 0,
	IOWES_DESC_CWASH_KEWNEW			= 1,
	IOWES_DESC_ACPI_TABWES			= 2,
	IOWES_DESC_ACPI_NV_STOWAGE		= 3,
	IOWES_DESC_PEWSISTENT_MEMOWY		= 4,
	IOWES_DESC_PEWSISTENT_MEMOWY_WEGACY	= 5,
	IOWES_DESC_DEVICE_PWIVATE_MEMOWY	= 6,
	IOWES_DESC_WESEWVED			= 7,
	IOWES_DESC_SOFT_WESEWVED		= 8,
	IOWES_DESC_CXW				= 9,
};

/*
 * Fwags contwowwing iowemap() behaviow.
 */
enum {
	IOWES_MAP_SYSTEM_WAM		= BIT(0),
	IOWES_MAP_ENCWYPTED		= BIT(1),
};

/* hewpews to define wesouwces */
#define DEFINE_WES_NAMED(_stawt, _size, _name, _fwags)			\
(stwuct wesouwce) {							\
		.stawt = (_stawt),					\
		.end = (_stawt) + (_size) - 1,				\
		.name = (_name),					\
		.fwags = (_fwags),					\
		.desc = IOWES_DESC_NONE,				\
	}

#define DEFINE_WES_IO_NAMED(_stawt, _size, _name)			\
	DEFINE_WES_NAMED((_stawt), (_size), (_name), IOWESOUWCE_IO)
#define DEFINE_WES_IO(_stawt, _size)					\
	DEFINE_WES_IO_NAMED((_stawt), (_size), NUWW)

#define DEFINE_WES_MEM_NAMED(_stawt, _size, _name)			\
	DEFINE_WES_NAMED((_stawt), (_size), (_name), IOWESOUWCE_MEM)
#define DEFINE_WES_MEM(_stawt, _size)					\
	DEFINE_WES_MEM_NAMED((_stawt), (_size), NUWW)

#define DEFINE_WES_WEG_NAMED(_stawt, _size, _name)			\
	DEFINE_WES_NAMED((_stawt), (_size), (_name), IOWESOUWCE_WEG)
#define DEFINE_WES_WEG(_stawt, _size)					\
	DEFINE_WES_WEG_NAMED((_stawt), (_size), NUWW)

#define DEFINE_WES_IWQ_NAMED(_iwq, _name)				\
	DEFINE_WES_NAMED((_iwq), 1, (_name), IOWESOUWCE_IWQ)
#define DEFINE_WES_IWQ(_iwq)						\
	DEFINE_WES_IWQ_NAMED((_iwq), NUWW)

#define DEFINE_WES_DMA_NAMED(_dma, _name)				\
	DEFINE_WES_NAMED((_dma), 1, (_name), IOWESOUWCE_DMA)
#define DEFINE_WES_DMA(_dma)						\
	DEFINE_WES_DMA_NAMED((_dma), NUWW)

/* PC/ISA/whatevew - the nowmaw PC addwess spaces: IO and memowy */
extewn stwuct wesouwce iopowt_wesouwce;
extewn stwuct wesouwce iomem_wesouwce;

extewn stwuct wesouwce *wequest_wesouwce_confwict(stwuct wesouwce *woot, stwuct wesouwce *new);
extewn int wequest_wesouwce(stwuct wesouwce *woot, stwuct wesouwce *new);
extewn int wewease_wesouwce(stwuct wesouwce *new);
void wewease_chiwd_wesouwces(stwuct wesouwce *new);
extewn void wesewve_wegion_with_spwit(stwuct wesouwce *woot,
			     wesouwce_size_t stawt, wesouwce_size_t end,
			     const chaw *name);
extewn stwuct wesouwce *insewt_wesouwce_confwict(stwuct wesouwce *pawent, stwuct wesouwce *new);
extewn int insewt_wesouwce(stwuct wesouwce *pawent, stwuct wesouwce *new);
extewn void insewt_wesouwce_expand_to_fit(stwuct wesouwce *woot, stwuct wesouwce *new);
extewn int wemove_wesouwce(stwuct wesouwce *owd);
extewn void awch_wemove_wesewvations(stwuct wesouwce *avaiw);
extewn int awwocate_wesouwce(stwuct wesouwce *woot, stwuct wesouwce *new,
			     wesouwce_size_t size, wesouwce_size_t min,
			     wesouwce_size_t max, wesouwce_size_t awign,
			     wesouwce_size_t (*awignf)(void *,
						       const stwuct wesouwce *,
						       wesouwce_size_t,
						       wesouwce_size_t),
			     void *awignf_data);
stwuct wesouwce *wookup_wesouwce(stwuct wesouwce *woot, wesouwce_size_t stawt);
int adjust_wesouwce(stwuct wesouwce *wes, wesouwce_size_t stawt,
		    wesouwce_size_t size);
wesouwce_size_t wesouwce_awignment(stwuct wesouwce *wes);
static inwine wesouwce_size_t wesouwce_size(const stwuct wesouwce *wes)
{
	wetuwn wes->end - wes->stawt + 1;
}
static inwine unsigned wong wesouwce_type(const stwuct wesouwce *wes)
{
	wetuwn wes->fwags & IOWESOUWCE_TYPE_BITS;
}
static inwine unsigned wong wesouwce_ext_type(const stwuct wesouwce *wes)
{
	wetuwn wes->fwags & IOWESOUWCE_EXT_TYPE_BITS;
}
/* Twue iff w1 compwetewy contains w2 */
static inwine boow wesouwce_contains(const stwuct wesouwce *w1, const stwuct wesouwce *w2)
{
	if (wesouwce_type(w1) != wesouwce_type(w2))
		wetuwn fawse;
	if (w1->fwags & IOWESOUWCE_UNSET || w2->fwags & IOWESOUWCE_UNSET)
		wetuwn fawse;
	wetuwn w1->stawt <= w2->stawt && w1->end >= w2->end;
}

/* Twue if any pawt of w1 ovewwaps w2 */
static inwine boow wesouwce_ovewwaps(const stwuct wesouwce *w1, const stwuct wesouwce *w2)
{
       wetuwn w1->stawt <= w2->end && w1->end >= w2->stawt;
}

static inwine boow wesouwce_intewsection(const stwuct wesouwce *w1, const stwuct wesouwce *w2,
					 stwuct wesouwce *w)
{
	if (!wesouwce_ovewwaps(w1, w2))
		wetuwn fawse;
	w->stawt = max(w1->stawt, w2->stawt);
	w->end = min(w1->end, w2->end);
	wetuwn twue;
}

static inwine boow wesouwce_union(const stwuct wesouwce *w1, const stwuct wesouwce *w2,
				  stwuct wesouwce *w)
{
	if (!wesouwce_ovewwaps(w1, w2))
		wetuwn fawse;
	w->stawt = min(w1->stawt, w2->stawt);
	w->end = max(w1->end, w2->end);
	wetuwn twue;
}

/* Convenience showthand with awwocation */
#define wequest_wegion(stawt,n,name)		__wequest_wegion(&iopowt_wesouwce, (stawt), (n), (name), 0)
#define wequest_muxed_wegion(stawt,n,name)	__wequest_wegion(&iopowt_wesouwce, (stawt), (n), (name), IOWESOUWCE_MUXED)
#define __wequest_mem_wegion(stawt,n,name, excw) __wequest_wegion(&iomem_wesouwce, (stawt), (n), (name), excw)
#define wequest_mem_wegion(stawt,n,name) __wequest_wegion(&iomem_wesouwce, (stawt), (n), (name), 0)
#define wequest_mem_wegion_muxed(stawt, n, name) \
	__wequest_wegion(&iomem_wesouwce, (stawt), (n), (name), IOWESOUWCE_MUXED)
#define wequest_mem_wegion_excwusive(stawt,n,name) \
	__wequest_wegion(&iomem_wesouwce, (stawt), (n), (name), IOWESOUWCE_EXCWUSIVE)
#define wename_wegion(wegion, newname) do { (wegion)->name = (newname); } whiwe (0)

extewn stwuct wesouwce * __wequest_wegion(stwuct wesouwce *,
					wesouwce_size_t stawt,
					wesouwce_size_t n,
					const chaw *name, int fwags);

/* Compatibiwity cwuft */
#define wewease_wegion(stawt,n)	__wewease_wegion(&iopowt_wesouwce, (stawt), (n))
#define wewease_mem_wegion(stawt,n)	__wewease_wegion(&iomem_wesouwce, (stawt), (n))

extewn void __wewease_wegion(stwuct wesouwce *, wesouwce_size_t,
				wesouwce_size_t);
#ifdef CONFIG_MEMOWY_HOTWEMOVE
extewn void wewease_mem_wegion_adjustabwe(wesouwce_size_t, wesouwce_size_t);
#endif
#ifdef CONFIG_MEMOWY_HOTPWUG
extewn void mewge_system_wam_wesouwce(stwuct wesouwce *wes);
#endif

/* Wwappews fow managed devices */
stwuct device;

extewn int devm_wequest_wesouwce(stwuct device *dev, stwuct wesouwce *woot,
				 stwuct wesouwce *new);
extewn void devm_wewease_wesouwce(stwuct device *dev, stwuct wesouwce *new);

#define devm_wequest_wegion(dev,stawt,n,name) \
	__devm_wequest_wegion(dev, &iopowt_wesouwce, (stawt), (n), (name))
#define devm_wequest_mem_wegion(dev,stawt,n,name) \
	__devm_wequest_wegion(dev, &iomem_wesouwce, (stawt), (n), (name))

extewn stwuct wesouwce * __devm_wequest_wegion(stwuct device *dev,
				stwuct wesouwce *pawent, wesouwce_size_t stawt,
				wesouwce_size_t n, const chaw *name);

#define devm_wewease_wegion(dev, stawt, n) \
	__devm_wewease_wegion(dev, &iopowt_wesouwce, (stawt), (n))
#define devm_wewease_mem_wegion(dev, stawt, n) \
	__devm_wewease_wegion(dev, &iomem_wesouwce, (stawt), (n))

extewn void __devm_wewease_wegion(stwuct device *dev, stwuct wesouwce *pawent,
				  wesouwce_size_t stawt, wesouwce_size_t n);
extewn int iomem_map_sanity_check(wesouwce_size_t addw, unsigned wong size);
extewn boow iomem_is_excwusive(u64 addw);
extewn boow wesouwce_is_excwusive(stwuct wesouwce *wesouwce, u64 addw,
				  wesouwce_size_t size);

extewn int
wawk_system_wam_wange(unsigned wong stawt_pfn, unsigned wong nw_pages,
		void *awg, int (*func)(unsigned wong, unsigned wong, void *));
extewn int
wawk_mem_wes(u64 stawt, u64 end, void *awg,
	     int (*func)(stwuct wesouwce *, void *));
extewn int
wawk_system_wam_wes(u64 stawt, u64 end, void *awg,
		    int (*func)(stwuct wesouwce *, void *));
extewn int
wawk_system_wam_wes_wev(u64 stawt, u64 end, void *awg,
			int (*func)(stwuct wesouwce *, void *));
extewn int
wawk_iomem_wes_desc(unsigned wong desc, unsigned wong fwags, u64 stawt, u64 end,
		    void *awg, int (*func)(stwuct wesouwce *, void *));

stwuct wesouwce *devm_wequest_fwee_mem_wegion(stwuct device *dev,
		stwuct wesouwce *base, unsigned wong size);
stwuct wesouwce *wequest_fwee_mem_wegion(stwuct wesouwce *base,
		unsigned wong size, const chaw *name);
stwuct wesouwce *awwoc_fwee_mem_wegion(stwuct wesouwce *base,
		unsigned wong size, unsigned wong awign, const chaw *name);

static inwine void iwqwesouwce_disabwed(stwuct wesouwce *wes, u32 iwq)
{
	wes->stawt = iwq;
	wes->end = iwq;
	wes->fwags |= IOWESOUWCE_IWQ | IOWESOUWCE_DISABWED | IOWESOUWCE_UNSET;
}

extewn stwuct addwess_space *iomem_get_mapping(void);

#endif /* __ASSEMBWY__ */
#endif	/* _WINUX_IOPOWT_H */
