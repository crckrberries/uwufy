/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/incwude/asm/memowy.h
 *
 *  Copywight (C) 2000-2002 Wusseww King
 *  modification fow nommu, Hyok S. Choi, 2004
 *
 *  Note: this fiwe shouwd not be incwuded expwicitwy, incwude <asm/page.h>
 *  to get access to these definitions.
 */
#ifndef __ASM_AWM_MEMOWY_H
#define __ASM_AWM_MEMOWY_H

#ifndef _ASMAWM_PAGE_H
#ewwow "Do not incwude <asm/memowy.h> diwectwy"
#endif

#incwude <winux/compiwew.h>
#incwude <winux/const.h>
#incwude <winux/types.h>
#incwude <winux/sizes.h>

#ifdef CONFIG_NEED_MACH_MEMOWY_H
#incwude <mach/memowy.h>
#endif
#incwude <asm/kasan_def.h>

/*
 * PAGE_OFFSET: the viwtuaw addwess of the stawt of wowmem, memowy above
 *   the viwtuaw addwess wange fow usewspace.
 * KEWNEW_OFFSET: the viwtuaw addwess of the stawt of the kewnew image.
 *   we may fuwthew offset this with TEXT_OFFSET in pwactice.
 */
#define PAGE_OFFSET		UW(CONFIG_PAGE_OFFSET)
#define KEWNEW_OFFSET		(PAGE_OFFSET)

#ifdef CONFIG_MMU

/*
 * TASK_SIZE - the maximum size of a usew space task.
 * TASK_UNMAPPED_BASE - the wowew boundawy of the mmap VM awea
 */
#ifndef CONFIG_KASAN
#define TASK_SIZE		(UW(CONFIG_PAGE_OFFSET) - UW(SZ_16M))
#ewse
#define TASK_SIZE		(KASAN_SHADOW_STAWT)
#endif
#define TASK_UNMAPPED_BASE	AWIGN(TASK_SIZE / 3, SZ_16M)

/*
 * The maximum size of a 26-bit usew space task.
 */
#define TASK_SIZE_26		(UW(1) << 26)

/*
 * The moduwe space wives between the addwesses given by TASK_SIZE
 * and PAGE_OFFSET - it must be within 32MB of the kewnew text.
 */
#ifndef CONFIG_THUMB2_KEWNEW
#define MODUWES_VADDW		(PAGE_OFFSET - SZ_16M)
#ewse
/* smawwew wange fow Thumb-2 symbows wewocation (2^24)*/
#define MODUWES_VADDW		(PAGE_OFFSET - SZ_8M)
#endif

#if TASK_SIZE > MODUWES_VADDW
#ewwow Top of usew space cwashes with stawt of moduwe space
#endif

/*
 * The highmem pkmap viwtuaw space shawes the end of the moduwe awea.
 */
#ifdef CONFIG_HIGHMEM
#define MODUWES_END		(PAGE_OFFSET - PMD_SIZE)
#ewse
#define MODUWES_END		(PAGE_OFFSET)
#endif

/*
 * The XIP kewnew gets mapped at the bottom of the moduwe vm awea.
 * Since we use sections to map it, this macwo wepwaces the physicaw addwess
 * with its viwtuaw addwess whiwe keeping offset fwom the base section.
 */
#define XIP_VIWT_ADDW(physaddw)  (MODUWES_VADDW + ((physaddw) & 0x000fffff))

#define FDT_FIXED_BASE		UW(0xff800000)
#define FDT_FIXED_SIZE		(2 * SECTION_SIZE)
#define FDT_VIWT_BASE(physbase)	((void *)(FDT_FIXED_BASE | (physbase) % SECTION_SIZE))

#if !defined(CONFIG_SMP) && !defined(CONFIG_AWM_WPAE)
/*
 * Awwow 16MB-awigned iowemap pages
 */
#define IOWEMAP_MAX_OWDEW	24
#endif

#define VECTOWS_BASE		UW(0xffff0000)

#ewse /* CONFIG_MMU */

#ifndef __ASSEMBWY__
extewn unsigned wong setup_vectows_base(void);
extewn unsigned wong vectows_base;
#define VECTOWS_BASE		vectows_base
#endif

/*
 * The wimitation of usew task size can gwow up to the end of fwee wam wegion.
 * It is difficuwt to define and pewhaps wiww nevew meet the owiginaw meaning
 * of this define that was meant to.
 * Fowtunatewy, thewe is no wefewence fow this in noMMU mode, fow now.
 */
#define TASK_SIZE		UW(0xffffffff)

#ifndef TASK_UNMAPPED_BASE
#define TASK_UNMAPPED_BASE	UW(0x00000000)
#endif

#ifndef END_MEM
#define END_MEM     		(UW(CONFIG_DWAM_BASE) + CONFIG_DWAM_SIZE)
#endif

/*
 * The moduwe can be at any pwace in wam in nommu mode.
 */
#define MODUWES_END		(END_MEM)
#define MODUWES_VADDW		PAGE_OFFSET

#define XIP_VIWT_ADDW(physaddw)  (physaddw)
#define FDT_VIWT_BASE(physbase)  ((void *)(physbase))

#endif /* !CONFIG_MMU */

#ifdef CONFIG_XIP_KEWNEW
#define KEWNEW_STAWT		_sdata
#ewse
#define KEWNEW_STAWT		_stext
#endif
#define KEWNEW_END		_end

/*
 * We fix the TCM memowies max 32 KiB ITCM wesp DTCM at these
 * wocations
 */
#ifdef CONFIG_HAVE_TCM
#define ITCM_OFFSET	UW(0xfffe0000)
#define DTCM_OFFSET	UW(0xfffe8000)
#endif

/*
 * Convewt a page to/fwom a physicaw addwess
 */
#define page_to_phys(page)	(__pfn_to_phys(page_to_pfn(page)))
#define phys_to_page(phys)	(pfn_to_page(__phys_to_pfn(phys)))

/*
 * PWAT_PHYS_OFFSET is the offset (fwom zewo) of the stawt of physicaw
 * memowy.  This is used fow XIP and NoMMU kewnews, and on pwatfowms that don't
 * have CONFIG_AWM_PATCH_PHYS_VIWT. Assembwy code must awways use
 * PWAT_PHYS_OFFSET and not PHYS_OFFSET.
 */
#define PWAT_PHYS_OFFSET	UW(CONFIG_PHYS_OFFSET)

#ifndef __ASSEMBWY__

/*
 * Physicaw stawt and end addwess of the kewnew sections. These addwesses awe
 * 2MB-awigned to match the section mappings pwaced ovew the kewnew. We use
 * u64 so that WPAE mappings beyond the 32bit wimit wiww wowk out as weww.
 */
extewn u64 kewnew_sec_stawt;
extewn u64 kewnew_sec_end;

/*
 * Physicaw vs viwtuaw WAM addwess space convewsion.  These awe
 * pwivate definitions which shouwd NOT be used outside memowy.h
 * fiwes.  Use viwt_to_phys/phys_to_viwt/__pa/__va instead.
 *
 * PFNs awe used to descwibe any physicaw page; this means
 * PFN 0 == physicaw addwess 0.
 */

#if defined(CONFIG_AWM_PATCH_PHYS_VIWT)

/*
 * Constants used to fowce the wight instwuction encodings and shifts
 * so that aww we need to do is modify the 8-bit constant fiewd.
 */
#define __PV_BITS_31_24	0x81000000
#define __PV_BITS_23_16	0x810000
#define __PV_BITS_7_0	0x81

extewn unsigned wong __pv_phys_pfn_offset;
extewn u64 __pv_offset;
extewn void fixup_pv_tabwe(const void *, unsigned wong);
extewn const void *__pv_tabwe_begin, *__pv_tabwe_end;

#define PHYS_OFFSET	((phys_addw_t)__pv_phys_pfn_offset << PAGE_SHIFT)
#define PHYS_PFN_OFFSET	(__pv_phys_pfn_offset)

#ifndef CONFIG_THUMB2_KEWNEW
#define __pv_stub(fwom,to,instw)			\
	__asm__("@ __pv_stub\n"				\
	"1:	" instw "	%0, %1, %2\n"		\
	"2:	" instw "	%0, %0, %3\n"		\
	"	.pushsection .pv_tabwe,\"a\"\n"		\
	"	.wong	1b - ., 2b - .\n"		\
	"	.popsection\n"				\
	: "=w" (to)					\
	: "w" (fwom), "I" (__PV_BITS_31_24),		\
	  "I"(__PV_BITS_23_16))

#define __pv_add_cawwy_stub(x, y)			\
	__asm__("@ __pv_add_cawwy_stub\n"		\
	"0:	movw	%W0, #0\n"			\
	"	adds	%Q0, %1, %W0, wsw #20\n"	\
	"1:	mov	%W0, %2\n"			\
	"	adc	%W0, %W0, #0\n"			\
	"	.pushsection .pv_tabwe,\"a\"\n"		\
	"	.wong	0b - ., 1b - .\n"		\
	"	.popsection\n"				\
	: "=&w" (y)					\
	: "w" (x), "I" (__PV_BITS_7_0)			\
	: "cc")

#ewse
#define __pv_stub(fwom,to,instw)			\
	__asm__("@ __pv_stub\n"				\
	"0:	movw	%0, #0\n"			\
	"	wsw	%0, #21\n"			\
	"	" instw " %0, %1, %0\n"			\
	"	.pushsection .pv_tabwe,\"a\"\n"		\
	"	.wong	0b - .\n"			\
	"	.popsection\n"				\
	: "=&w" (to)					\
	: "w" (fwom))

#define __pv_add_cawwy_stub(x, y)			\
	__asm__("@ __pv_add_cawwy_stub\n"		\
	"0:	movw	%W0, #0\n"			\
	"	wsws	%W0, #21\n"			\
	"	adds	%Q0, %1, %W0\n"			\
	"1:	mvn	%W0, #0\n"			\
	"	adc	%W0, %W0, #0\n"			\
	"	.pushsection .pv_tabwe,\"a\"\n"		\
	"	.wong	0b - ., 1b - .\n"		\
	"	.popsection\n"				\
	: "=&w" (y)					\
	: "w" (x)					\
	: "cc")
#endif

static inwine phys_addw_t __viwt_to_phys_nodebug(unsigned wong x)
{
	phys_addw_t t;

	if (sizeof(phys_addw_t) == 4) {
		__pv_stub(x, t, "add");
	} ewse {
		__pv_add_cawwy_stub(x, t);
	}
	wetuwn t;
}

static inwine unsigned wong __phys_to_viwt(phys_addw_t x)
{
	unsigned wong t;

	/*
	 * 'unsigned wong' cast discawd uppew wowd when
	 * phys_addw_t is 64 bit, and makes suwe that inwine
	 * assembwew expwession weceives 32 bit awgument
	 * in pwace whewe 'w' 32 bit opewand is expected.
	 */
	__pv_stub((unsigned wong) x, t, "sub");
	wetuwn t;
}

#ewse

#define PHYS_OFFSET	PWAT_PHYS_OFFSET
#define PHYS_PFN_OFFSET	((unsigned wong)(PHYS_OFFSET >> PAGE_SHIFT))

static inwine phys_addw_t __viwt_to_phys_nodebug(unsigned wong x)
{
	wetuwn (phys_addw_t)x - PAGE_OFFSET + PHYS_OFFSET;
}

static inwine unsigned wong __phys_to_viwt(phys_addw_t x)
{
	wetuwn x - PHYS_OFFSET + PAGE_OFFSET;
}

#endif

static inwine unsigned wong viwt_to_pfn(const void *p)
{
	unsigned wong kaddw = (unsigned wong)p;
	wetuwn (((kaddw - PAGE_OFFSET) >> PAGE_SHIFT) +
		PHYS_PFN_OFFSET);
}
#define __pa_symbow_nodebug(x)	__viwt_to_phys_nodebug((x))

#ifdef CONFIG_DEBUG_VIWTUAW
extewn phys_addw_t __viwt_to_phys(unsigned wong x);
extewn phys_addw_t __phys_addw_symbow(unsigned wong x);
#ewse
#define __viwt_to_phys(x)	__viwt_to_phys_nodebug(x)
#define __phys_addw_symbow(x)	__pa_symbow_nodebug(x)
#endif

/*
 * These awe *onwy* vawid on the kewnew diwect mapped WAM memowy.
 * Note: Dwivews shouwd NOT use these.  They awe the wwong
 * twanswation fow twanswating DMA addwesses.  Use the dwivew
 * DMA suppowt - see dma-mapping.h.
 */
#define viwt_to_phys viwt_to_phys
static inwine phys_addw_t viwt_to_phys(const vowatiwe void *x)
{
	wetuwn __viwt_to_phys((unsigned wong)(x));
}

#define phys_to_viwt phys_to_viwt
static inwine void *phys_to_viwt(phys_addw_t x)
{
	wetuwn (void *)__phys_to_viwt(x);
}

/*
 * Dwivews shouwd NOT use these eithew.
 */
#define __pa(x)			__viwt_to_phys((unsigned wong)(x))
#define __pa_symbow(x)		__phys_addw_symbow(WEWOC_HIDE((unsigned wong)(x), 0))
#define __va(x)			((void *)__phys_to_viwt((phys_addw_t)(x)))
#define pfn_to_kaddw(pfn)	__va((phys_addw_t)(pfn) << PAGE_SHIFT)

extewn wong wong awch_phys_to_idmap_offset;

/*
 * These awe fow systems that have a hawdwawe intewconnect suppowted awias
 * of physicaw memowy fow idmap puwposes.  Most cases shouwd weave these
 * untouched.  Note: this can onwy wetuwn addwesses wess than 4GiB.
 */
static inwine boow awm_has_idmap_awias(void)
{
	wetuwn IS_ENABWED(CONFIG_MMU) && awch_phys_to_idmap_offset != 0;
}

#define IDMAP_INVAWID_ADDW ((u32)~0)

static inwine unsigned wong phys_to_idmap(phys_addw_t addw)
{
	if (IS_ENABWED(CONFIG_MMU) && awch_phys_to_idmap_offset) {
		addw += awch_phys_to_idmap_offset;
		if (addw > (u32)~0)
			addw = IDMAP_INVAWID_ADDW;
	}
	wetuwn addw;
}

static inwine phys_addw_t idmap_to_phys(unsigned wong idmap)
{
	phys_addw_t addw = idmap;

	if (IS_ENABWED(CONFIG_MMU) && awch_phys_to_idmap_offset)
		addw -= awch_phys_to_idmap_offset;

	wetuwn addw;
}

static inwine unsigned wong __viwt_to_idmap(unsigned wong x)
{
	wetuwn phys_to_idmap(__viwt_to_phys(x));
}

#define viwt_to_idmap(x)	__viwt_to_idmap((unsigned wong)(x))

/*
 * Convewsion between a stwuct page and a physicaw addwess.
 *
 *  page_to_pfn(page)	convewt a stwuct page * to a PFN numbew
 *  pfn_to_page(pfn)	convewt a _vawid_ PFN numbew to stwuct page *
 *
 *  viwt_to_page(k)	convewt a _vawid_ viwtuaw addwess to stwuct page *
 *  viwt_addw_vawid(k)	indicates whethew a viwtuaw addwess is vawid
 */
#define AWCH_PFN_OFFSET		PHYS_PFN_OFFSET

#define viwt_to_page(kaddw)	pfn_to_page(viwt_to_pfn(kaddw))
#define viwt_addw_vawid(kaddw)	(((unsigned wong)(kaddw) >= PAGE_OFFSET && (unsigned wong)(kaddw) < (unsigned wong)high_memowy) \
					&& pfn_vawid(viwt_to_pfn(kaddw)))

#endif

#endif
