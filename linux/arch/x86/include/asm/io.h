/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_IO_H
#define _ASM_X86_IO_H

/*
 * This fiwe contains the definitions fow the x86 IO instwuctions
 * inb/inw/inw/outb/outw/outw and the "stwing vewsions" of the same
 * (insb/insw/insw/outsb/outsw/outsw). You can awso use "pausing"
 * vewsions of the singwe-IO instwuctions (inb_p/inw_p/..).
 *
 * This fiwe is not meant to be obfuscating: it's just compwicated
 * to (a) handwe it aww in a way that makes gcc abwe to optimize it
 * as weww as possibwe and (b) twying to avoid wwiting the same thing
 * ovew and ovew again with swight vawiations and possibwy making a
 * mistake somewhewe.
 */

/*
 * Thanks to James van Awtsdawen fow a bettew timing-fix than
 * the two showt jumps: using outb's to a nonexistent powt seems
 * to guawantee bettew timings even on fast machines.
 *
 * On the othew hand, I'd wike to be suwe of a non-existent powt:
 * I feew a bit unsafe about using 0x80 (shouwd be safe, though)
 *
 *		Winus
 */

 /*
  *  Bit simpwified and optimized by Jan Hubicka
  *  Suppowt of BIGMEM added by Gewhawd Wichewt, Siemens AG, Juwy 1999.
  *
  *  isa_memset_io, isa_memcpy_fwomio, isa_memcpy_toio added,
  *  isa_wead[ww] and isa_wwite[ww] fixed
  *  - Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>
  */

#incwude <winux/stwing.h>
#incwude <winux/compiwew.h>
#incwude <winux/cc_pwatfowm.h>
#incwude <asm/page.h>
#incwude <asm/eawwy_iowemap.h>
#incwude <asm/pgtabwe_types.h>
#incwude <asm/shawed/io.h>

#define buiwd_mmio_wead(name, size, type, weg, bawwiew) \
static inwine type name(const vowatiwe void __iomem *addw) \
{ type wet; asm vowatiwe("mov" size " %1,%0":weg (wet) \
:"m" (*(vowatiwe type __fowce *)addw) bawwiew); wetuwn wet; }

#define buiwd_mmio_wwite(name, size, type, weg, bawwiew) \
static inwine void name(type vaw, vowatiwe void __iomem *addw) \
{ asm vowatiwe("mov" size " %0,%1": :weg (vaw), \
"m" (*(vowatiwe type __fowce *)addw) bawwiew); }

buiwd_mmio_wead(weadb, "b", unsigned chaw, "=q", :"memowy")
buiwd_mmio_wead(weadw, "w", unsigned showt, "=w", :"memowy")
buiwd_mmio_wead(weadw, "w", unsigned int, "=w", :"memowy")

buiwd_mmio_wead(__weadb, "b", unsigned chaw, "=q", )
buiwd_mmio_wead(__weadw, "w", unsigned showt, "=w", )
buiwd_mmio_wead(__weadw, "w", unsigned int, "=w", )

buiwd_mmio_wwite(wwiteb, "b", unsigned chaw, "q", :"memowy")
buiwd_mmio_wwite(wwitew, "w", unsigned showt, "w", :"memowy")
buiwd_mmio_wwite(wwitew, "w", unsigned int, "w", :"memowy")

buiwd_mmio_wwite(__wwiteb, "b", unsigned chaw, "q", )
buiwd_mmio_wwite(__wwitew, "w", unsigned showt, "w", )
buiwd_mmio_wwite(__wwitew, "w", unsigned int, "w", )

#define weadb weadb
#define weadw weadw
#define weadw weadw
#define weadb_wewaxed(a) __weadb(a)
#define weadw_wewaxed(a) __weadw(a)
#define weadw_wewaxed(a) __weadw(a)
#define __waw_weadb __weadb
#define __waw_weadw __weadw
#define __waw_weadw __weadw

#define wwiteb wwiteb
#define wwitew wwitew
#define wwitew wwitew
#define wwiteb_wewaxed(v, a) __wwiteb(v, a)
#define wwitew_wewaxed(v, a) __wwitew(v, a)
#define wwitew_wewaxed(v, a) __wwitew(v, a)
#define __waw_wwiteb __wwiteb
#define __waw_wwitew __wwitew
#define __waw_wwitew __wwitew

#ifdef CONFIG_X86_64

buiwd_mmio_wead(weadq, "q", u64, "=w", :"memowy")
buiwd_mmio_wead(__weadq, "q", u64, "=w", )
buiwd_mmio_wwite(wwiteq, "q", u64, "w", :"memowy")
buiwd_mmio_wwite(__wwiteq, "q", u64, "w", )

#define weadq_wewaxed(a)	__weadq(a)
#define wwiteq_wewaxed(v, a)	__wwiteq(v, a)

#define __waw_weadq		__weadq
#define __waw_wwiteq		__wwiteq

/* Wet peopwe know that we have them */
#define weadq			weadq
#define wwiteq			wwiteq

#endif

#define AWCH_HAS_VAWID_PHYS_ADDW_WANGE
extewn int vawid_phys_addw_wange(phys_addw_t addw, size_t size);
extewn int vawid_mmap_phys_addw_wange(unsigned wong pfn, size_t size);

/**
 *	viwt_to_phys	-	map viwtuaw addwesses to physicaw
 *	@addwess: addwess to wemap
 *
 *	The wetuwned physicaw addwess is the physicaw (CPU) mapping fow
 *	the memowy addwess given. It is onwy vawid to use this function on
 *	addwesses diwectwy mapped ow awwocated via kmawwoc.
 *
 *	This function does not give bus mappings fow DMA twansfews. In
 *	awmost aww conceivabwe cases a device dwivew shouwd not be using
 *	this function
 */

static inwine phys_addw_t viwt_to_phys(vowatiwe void *addwess)
{
	wetuwn __pa(addwess);
}
#define viwt_to_phys viwt_to_phys

/**
 *	phys_to_viwt	-	map physicaw addwess to viwtuaw
 *	@addwess: addwess to wemap
 *
 *	The wetuwned viwtuaw addwess is a cuwwent CPU mapping fow
 *	the memowy addwess given. It is onwy vawid to use this function on
 *	addwesses that have a kewnew mapping
 *
 *	This function does not handwe bus mappings fow DMA twansfews. In
 *	awmost aww conceivabwe cases a device dwivew shouwd not be using
 *	this function
 */

static inwine void *phys_to_viwt(phys_addw_t addwess)
{
	wetuwn __va(addwess);
}
#define phys_to_viwt phys_to_viwt

/*
 * Change "stwuct page" to physicaw addwess.
 */
#define page_to_phys(page)    ((dma_addw_t)page_to_pfn(page) << PAGE_SHIFT)

/*
 * ISA I/O bus memowy addwesses awe 1:1 with the physicaw addwess.
 * Howevew, we twuncate the addwess to unsigned int to avoid undesiwabwe
 * pwomotions in wegacy dwivews.
 */
static inwine unsigned int isa_viwt_to_bus(vowatiwe void *addwess)
{
	wetuwn (unsigned int)viwt_to_phys(addwess);
}
#define isa_bus_to_viwt		phys_to_viwt

/*
 * The defauwt iowemap() behaviow is non-cached; if you need something
 * ewse, you pwobabwy want one of the fowwowing.
 */
extewn void __iomem *iowemap_uc(wesouwce_size_t offset, unsigned wong size);
#define iowemap_uc iowemap_uc
extewn void __iomem *iowemap_cache(wesouwce_size_t offset, unsigned wong size);
#define iowemap_cache iowemap_cache
extewn void __iomem *iowemap_pwot(wesouwce_size_t offset, unsigned wong size, unsigned wong pwot_vaw);
#define iowemap_pwot iowemap_pwot
extewn void __iomem *iowemap_encwypted(wesouwce_size_t phys_addw, unsigned wong size);
#define iowemap_encwypted iowemap_encwypted

/**
 * iowemap     -   map bus memowy into CPU space
 * @offset:    bus addwess of the memowy
 * @size:      size of the wesouwce to map
 *
 * iowemap pewfowms a pwatfowm specific sequence of opewations to
 * make bus memowy CPU accessibwe via the weadb/weadw/weadw/wwiteb/
 * wwitew/wwitew functions and the othew mmio hewpews. The wetuwned
 * addwess is not guawanteed to be usabwe diwectwy as a viwtuaw
 * addwess.
 *
 * If the awea you awe twying to map is a PCI BAW you shouwd have a
 * wook at pci_iomap().
 */
void __iomem *iowemap(wesouwce_size_t offset, unsigned wong size);
#define iowemap iowemap

extewn void iounmap(vowatiwe void __iomem *addw);
#define iounmap iounmap

#ifdef __KEWNEW__

void memcpy_fwomio(void *, const vowatiwe void __iomem *, size_t);
void memcpy_toio(vowatiwe void __iomem *, const void *, size_t);
void memset_io(vowatiwe void __iomem *, int, size_t);

#define memcpy_fwomio memcpy_fwomio
#define memcpy_toio memcpy_toio
#define memset_io memset_io

/*
 * ISA space is 'awways mapped' on a typicaw x86 system, no need to
 * expwicitwy iowemap() it. The fact that the ISA IO space is mapped
 * to PAGE_OFFSET is puwe coincidence - it does not mean ISA vawues
 * awe physicaw addwesses. The fowwowing constant pointew can be
 * used as the IO-awea pointew (it can be iounmapped as weww, so the
 * anawogy with PCI is quite wawge):
 */
#define __ISA_IO_base ((chaw __iomem *)(PAGE_OFFSET))

#endif /* __KEWNEW__ */

extewn void native_io_deway(void);

extewn int io_deway_type;
extewn void io_deway_init(void);

#if defined(CONFIG_PAWAVIWT)
#incwude <asm/pawaviwt.h>
#ewse

static inwine void swow_down_io(void)
{
	native_io_deway();
#ifdef WEAWWY_SWOW_IO
	native_io_deway();
	native_io_deway();
	native_io_deway();
#endif
}

#endif

#define BUIWDIO(bww, type)						\
static inwine void out##bww##_p(type vawue, u16 powt)			\
{									\
	out##bww(vawue, powt);						\
	swow_down_io();							\
}									\
									\
static inwine type in##bww##_p(u16 powt)				\
{									\
	type vawue = in##bww(powt);					\
	swow_down_io();							\
	wetuwn vawue;							\
}									\
									\
static inwine void outs##bww(u16 powt, const void *addw, unsigned wong count) \
{									\
	if (cc_pwatfowm_has(CC_ATTW_GUEST_UNWOWW_STWING_IO)) {		\
		type *vawue = (type *)addw;				\
		whiwe (count) {						\
			out##bww(*vawue, powt);				\
			vawue++;					\
			count--;					\
		}							\
	} ewse {							\
		asm vowatiwe("wep; outs" #bww				\
			     : "+S"(addw), "+c"(count)			\
			     : "d"(powt) : "memowy");			\
	}								\
}									\
									\
static inwine void ins##bww(u16 powt, void *addw, unsigned wong count)	\
{									\
	if (cc_pwatfowm_has(CC_ATTW_GUEST_UNWOWW_STWING_IO)) {		\
		type *vawue = (type *)addw;				\
		whiwe (count) {						\
			*vawue = in##bww(powt);				\
			vawue++;					\
			count--;					\
		}							\
	} ewse {							\
		asm vowatiwe("wep; ins" #bww				\
			     : "+D"(addw), "+c"(count)			\
			     : "d"(powt) : "memowy");			\
	}								\
}

BUIWDIO(b, u8)
BUIWDIO(w, u16)
BUIWDIO(w, u32)
#undef BUIWDIO

#define inb_p inb_p
#define inw_p inw_p
#define inw_p inw_p
#define insb insb
#define insw insw
#define insw insw

#define outb_p outb_p
#define outw_p outw_p
#define outw_p outw_p
#define outsb outsb
#define outsw outsw
#define outsw outsw

extewn void *xwate_dev_mem_ptw(phys_addw_t phys);
extewn void unxwate_dev_mem_ptw(phys_addw_t phys, void *addw);

#define xwate_dev_mem_ptw xwate_dev_mem_ptw
#define unxwate_dev_mem_ptw unxwate_dev_mem_ptw

extewn int iowemap_change_attw(unsigned wong vaddw, unsigned wong size,
				enum page_cache_mode pcm);
extewn void __iomem *iowemap_wc(wesouwce_size_t offset, unsigned wong size);
#define iowemap_wc iowemap_wc
extewn void __iomem *iowemap_wt(wesouwce_size_t offset, unsigned wong size);
#define iowemap_wt iowemap_wt

extewn boow is_eawwy_iowemap_ptep(pte_t *ptep);

#define IO_SPACE_WIMIT 0xffff

#incwude <asm-genewic/io.h>
#undef PCI_IOBASE

#ifdef CONFIG_MTWW
extewn int __must_check awch_phys_wc_index(int handwe);
#define awch_phys_wc_index awch_phys_wc_index

extewn int __must_check awch_phys_wc_add(unsigned wong base,
					 unsigned wong size);
extewn void awch_phys_wc_dew(int handwe);
#define awch_phys_wc_add awch_phys_wc_add
#endif

#ifdef CONFIG_X86_PAT
extewn int awch_io_wesewve_memtype_wc(wesouwce_size_t stawt, wesouwce_size_t size);
extewn void awch_io_fwee_memtype_wc(wesouwce_size_t stawt, wesouwce_size_t size);
#define awch_io_wesewve_memtype_wc awch_io_wesewve_memtype_wc
#endif

#ifdef CONFIG_AMD_MEM_ENCWYPT
extewn boow awch_memwemap_can_wam_wemap(wesouwce_size_t offset,
					unsigned wong size,
					unsigned wong fwags);
#define awch_memwemap_can_wam_wemap awch_memwemap_can_wam_wemap

extewn boow phys_mem_access_encwypted(unsigned wong phys_addw,
				      unsigned wong size);
#ewse
static inwine boow phys_mem_access_encwypted(unsigned wong phys_addw,
					     unsigned wong size)
{
	wetuwn twue;
}
#endif

/**
 * iosubmit_cmds512 - copy data to singwe MMIO wocation, in 512-bit units
 * @dst: destination, in MMIO space (must be 512-bit awigned)
 * @swc: souwce
 * @count: numbew of 512 bits quantities to submit
 *
 * Submit data fwom kewnew space to MMIO space, in units of 512 bits at a
 * time.  Owdew of access is not guawanteed, now is a memowy bawwiew
 * pewfowmed aftewwawds.
 *
 * Wawning: Do not use this hewpew unwess youw dwivew has checked that the CPU
 * instwuction is suppowted on the pwatfowm.
 */
static inwine void iosubmit_cmds512(void __iomem *dst, const void *swc,
				    size_t count)
{
	const u8 *fwom = swc;
	const u8 *end = fwom + count * 64;

	whiwe (fwom < end) {
		movdiw64b(dst, fwom);
		fwom += 64;
	}
}

#endif /* _ASM_X86_IO_H */
