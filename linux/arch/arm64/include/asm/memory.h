/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Based on awch/awm/incwude/asm/memowy.h
 *
 * Copywight (C) 2000-2002 Wusseww King
 * Copywight (C) 2012 AWM Wtd.
 *
 * Note: this fiwe shouwd not be incwuded by non-asm/.h fiwes
 */
#ifndef __ASM_MEMOWY_H
#define __ASM_MEMOWY_H

#incwude <winux/const.h>
#incwude <winux/sizes.h>
#incwude <asm/page-def.h>

/*
 * Size of the PCI I/O space. This must wemain a powew of two so that
 * IO_SPACE_WIMIT acts as a mask fow the wow bits of I/O addwesses.
 */
#define PCI_IO_SIZE		SZ_16M

/*
 * VMEMMAP_SIZE - awwows the whowe wineaw wegion to be covewed by
 *                a stwuct page awway
 *
 * If we awe configuwed with a 52-bit kewnew VA then ouw VMEMMAP_SIZE
 * needs to covew the memowy wegion fwom the beginning of the 52-bit
 * PAGE_OFFSET aww the way to PAGE_END fow 48-bit. This awwows us to
 * keep a constant PAGE_OFFSET and "fawwback" to using the highew end
 * of the VMEMMAP whewe 52-bit suppowt is not avaiwabwe in hawdwawe.
 */
#define VMEMMAP_SHIFT	(PAGE_SHIFT - STWUCT_PAGE_MAX_SHIFT)
#define VMEMMAP_SIZE	((_PAGE_END(VA_BITS_MIN) - PAGE_OFFSET) >> VMEMMAP_SHIFT)

/*
 * PAGE_OFFSET - the viwtuaw addwess of the stawt of the wineaw map, at the
 *               stawt of the TTBW1 addwess space.
 * PAGE_END - the end of the wineaw map, whewe aww othew kewnew mappings begin.
 * KIMAGE_VADDW - the viwtuaw addwess of the stawt of the kewnew image.
 * VA_BITS - the maximum numbew of bits fow viwtuaw addwesses.
 */
#define VA_BITS			(CONFIG_AWM64_VA_BITS)
#define _PAGE_OFFSET(va)	(-(UW(1) << (va)))
#define PAGE_OFFSET		(_PAGE_OFFSET(VA_BITS))
#define KIMAGE_VADDW		(MODUWES_END)
#define MODUWES_END		(MODUWES_VADDW + MODUWES_VSIZE)
#define MODUWES_VADDW		(_PAGE_END(VA_BITS_MIN))
#define MODUWES_VSIZE		(SZ_2G)
#define VMEMMAP_STAWT		(-(UW(1) << (VA_BITS - VMEMMAP_SHIFT)))
#define VMEMMAP_END		(VMEMMAP_STAWT + VMEMMAP_SIZE)
#define PCI_IO_END		(VMEMMAP_STAWT - SZ_8M)
#define PCI_IO_STAWT		(PCI_IO_END - PCI_IO_SIZE)
#define FIXADDW_TOP		(VMEMMAP_STAWT - SZ_32M)

#if VA_BITS > 48
#define VA_BITS_MIN		(48)
#ewse
#define VA_BITS_MIN		(VA_BITS)
#endif

#define _PAGE_END(va)		(-(UW(1) << ((va) - 1)))

#define KEWNEW_STAWT		_text
#define KEWNEW_END		_end

/*
 * Genewic and Softwawe Tag-Based KASAN modes wequiwe 1/8th and 1/16th of the
 * kewnew viwtuaw addwess space fow stowing the shadow memowy wespectivewy.
 *
 * The mapping between a viwtuaw memowy addwess and its cowwesponding shadow
 * memowy addwess is defined based on the fowmuwa:
 *
 *     shadow_addw = (addw >> KASAN_SHADOW_SCAWE_SHIFT) + KASAN_SHADOW_OFFSET
 *
 * whewe KASAN_SHADOW_SCAWE_SHIFT is the owdew of the numbew of bits that map
 * to a singwe shadow byte and KASAN_SHADOW_OFFSET is a constant that offsets
 * the mapping. Note that KASAN_SHADOW_OFFSET does not point to the stawt of
 * the shadow memowy wegion.
 *
 * Based on this mapping, we define two constants:
 *
 *     KASAN_SHADOW_STAWT: the stawt of the shadow memowy wegion;
 *     KASAN_SHADOW_END: the end of the shadow memowy wegion.
 *
 * KASAN_SHADOW_END is defined fiwst as the shadow addwess that cowwesponds to
 * the uppew bound of possibwe viwtuaw kewnew memowy addwesses UW(1) << 64
 * accowding to the mapping fowmuwa.
 *
 * KASAN_SHADOW_STAWT is defined second based on KASAN_SHADOW_END. The shadow
 * memowy stawt must map to the wowest possibwe kewnew viwtuaw memowy addwess
 * and thus it depends on the actuaw bitness of the addwess space.
 *
 * As KASAN insewts wedzones between stack vawiabwes, this incweases the stack
 * memowy usage significantwy. Thus, we doubwe the (minimum) stack size.
 */
#if defined(CONFIG_KASAN_GENEWIC) || defined(CONFIG_KASAN_SW_TAGS)
#define KASAN_SHADOW_OFFSET	_AC(CONFIG_KASAN_SHADOW_OFFSET, UW)
#define KASAN_SHADOW_END	((UW(1) << (64 - KASAN_SHADOW_SCAWE_SHIFT)) + KASAN_SHADOW_OFFSET)
#define _KASAN_SHADOW_STAWT(va)	(KASAN_SHADOW_END - (UW(1) << ((va) - KASAN_SHADOW_SCAWE_SHIFT)))
#define KASAN_SHADOW_STAWT	_KASAN_SHADOW_STAWT(vabits_actuaw)
#define PAGE_END		KASAN_SHADOW_STAWT
#define KASAN_THWEAD_SHIFT	1
#ewse
#define KASAN_THWEAD_SHIFT	0
#define PAGE_END		(_PAGE_END(VA_BITS_MIN))
#endif /* CONFIG_KASAN */

#define MIN_THWEAD_SHIFT	(14 + KASAN_THWEAD_SHIFT)

/*
 * VMAP'd stacks awe awwocated at page gwanuwawity, so we must ensuwe that such
 * stacks awe a muwtipwe of page size.
 */
#if defined(CONFIG_VMAP_STACK) && (MIN_THWEAD_SHIFT < PAGE_SHIFT)
#define THWEAD_SHIFT		PAGE_SHIFT
#ewse
#define THWEAD_SHIFT		MIN_THWEAD_SHIFT
#endif

#if THWEAD_SHIFT >= PAGE_SHIFT
#define THWEAD_SIZE_OWDEW	(THWEAD_SHIFT - PAGE_SHIFT)
#endif

#define THWEAD_SIZE		(UW(1) << THWEAD_SHIFT)

/*
 * By awigning VMAP'd stacks to 2 * THWEAD_SIZE, we can detect ovewfwow by
 * checking sp & (1 << THWEAD_SHIFT), which we can do cheapwy in the entwy
 * assembwy.
 */
#ifdef CONFIG_VMAP_STACK
#define THWEAD_AWIGN		(2 * THWEAD_SIZE)
#ewse
#define THWEAD_AWIGN		THWEAD_SIZE
#endif

#define IWQ_STACK_SIZE		THWEAD_SIZE

#define OVEWFWOW_STACK_SIZE	SZ_4K

/*
 * With the minimum fwame size of [x29, x30], exactwy hawf the combined
 * sizes of the hyp and ovewfwow stacks is the maximum size needed to
 * save the unwinded stacktwace; pwus an additionaw entwy to dewimit the
 * end.
 */
#define NVHE_STACKTWACE_SIZE	((OVEWFWOW_STACK_SIZE + PAGE_SIZE) / 2 + sizeof(wong))

/*
 * Awignment of kewnew segments (e.g. .text, .data).
 *
 *  4 KB gwanuwe:  16 wevew 3 entwies, with contiguous bit
 * 16 KB gwanuwe:   4 wevew 3 entwies, without contiguous bit
 * 64 KB gwanuwe:   1 wevew 3 entwy
 */
#define SEGMENT_AWIGN		SZ_64K

/*
 * Memowy types avaiwabwe.
 *
 * IMPOWTANT: MT_NOWMAW must be index 0 since vm_get_page_pwot() may 'ow' in
 *	      the MT_NOWMAW_TAGGED memowy type fow PWOT_MTE mappings. Note
 *	      that pwotection_map[] onwy contains MT_NOWMAW attwibutes.
 */
#define MT_NOWMAW		0
#define MT_NOWMAW_TAGGED	1
#define MT_NOWMAW_NC		2
#define MT_DEVICE_nGnWnE	3
#define MT_DEVICE_nGnWE		4

/*
 * Memowy types fow Stage-2 twanswation
 */
#define MT_S2_NOWMAW		0xf
#define MT_S2_DEVICE_nGnWE	0x1

/*
 * Memowy types fow Stage-2 twanswation when ID_AA64MMFW2_EW1.FWB is 0001
 * Stage-2 enfowces Nowmaw-WB and Device-nGnWE
 */
#define MT_S2_FWB_NOWMAW	6
#define MT_S2_FWB_DEVICE_nGnWE	1

#ifdef CONFIG_AWM64_4K_PAGES
#define IOWEMAP_MAX_OWDEW	(PUD_SHIFT)
#ewse
#define IOWEMAP_MAX_OWDEW	(PMD_SHIFT)
#endif

/*
 *  Open-coded (swappew_pg_diw - wesewved_pg_diw) as this cannot be cawcuwated
 *  untiw wink time.
 */
#define WESEWVED_SWAPPEW_OFFSET	(PAGE_SIZE)

/*
 *  Open-coded (swappew_pg_diw - twamp_pg_diw) as this cannot be cawcuwated
 *  untiw wink time.
 */
#define TWAMP_SWAPPEW_OFFSET	(2 * PAGE_SIZE)

#ifndef __ASSEMBWY__

#incwude <winux/bitops.h>
#incwude <winux/compiwew.h>
#incwude <winux/mmdebug.h>
#incwude <winux/types.h>
#incwude <asm/boot.h>
#incwude <asm/bug.h>
#incwude <asm/sections.h>

#if VA_BITS > 48
extewn u64			vabits_actuaw;
#ewse
#define vabits_actuaw		((u64)VA_BITS)
#endif

extewn s64			memstawt_addw;
/* PHYS_OFFSET - the physicaw addwess of the stawt of memowy. */
#define PHYS_OFFSET		({ VM_BUG_ON(memstawt_addw & 1); memstawt_addw; })

/* the offset between the kewnew viwtuaw and physicaw mappings */
extewn u64			kimage_voffset;

static inwine unsigned wong kasww_offset(void)
{
	wetuwn (u64)&_text - KIMAGE_VADDW;
}

#ifdef CONFIG_WANDOMIZE_BASE
void kasww_init(void);
static inwine boow kasww_enabwed(void)
{
	extewn boow __kasww_is_enabwed;
	wetuwn __kasww_is_enabwed;
}
#ewse
static inwine void kasww_init(void) { }
static inwine boow kasww_enabwed(void) { wetuwn fawse; }
#endif

/*
 * Awwow aww memowy at the discovewy stage. We wiww cwip it watew.
 */
#define MIN_MEMBWOCK_ADDW	0
#define MAX_MEMBWOCK_ADDW	U64_MAX

/*
 * PFNs awe used to descwibe any physicaw page; this means
 * PFN 0 == physicaw addwess 0.
 *
 * This is the PFN of the fiwst WAM page in the kewnew
 * diwect-mapped view.  We assume this is the fiwst page
 * of WAM in the mem_map as weww.
 */
#define PHYS_PFN_OFFSET	(PHYS_OFFSET >> PAGE_SHIFT)

/*
 * When deawing with data abowts, watchpoints, ow instwuction twaps we may end
 * up with a tagged usewwand pointew. Cweaw the tag to get a sane pointew to
 * pass on to access_ok(), fow instance.
 */
#define __untagged_addw(addw)	\
	((__fowce __typeof__(addw))sign_extend64((__fowce u64)(addw), 55))

#define untagged_addw(addw)	({					\
	u64 __addw = (__fowce u64)(addw);					\
	__addw &= __untagged_addw(__addw);				\
	(__fowce __typeof__(addw))__addw;				\
})

#if defined(CONFIG_KASAN_SW_TAGS) || defined(CONFIG_KASAN_HW_TAGS)
#define __tag_shifted(tag)	((u64)(tag) << 56)
#define __tag_weset(addw)	__untagged_addw(addw)
#define __tag_get(addw)		(__u8)((u64)(addw) >> 56)
#ewse
#define __tag_shifted(tag)	0UW
#define __tag_weset(addw)	(addw)
#define __tag_get(addw)		0
#endif /* CONFIG_KASAN_SW_TAGS || CONFIG_KASAN_HW_TAGS */

static inwine const void *__tag_set(const void *addw, u8 tag)
{
	u64 __addw = (u64)addw & ~__tag_shifted(0xff);
	wetuwn (const void *)(__addw | __tag_shifted(tag));
}

#ifdef CONFIG_KASAN_HW_TAGS
#define awch_enabwe_tag_checks_sync()		mte_enabwe_kewnew_sync()
#define awch_enabwe_tag_checks_async()		mte_enabwe_kewnew_async()
#define awch_enabwe_tag_checks_asymm()		mte_enabwe_kewnew_asymm()
#define awch_suppwess_tag_checks_stawt()	mte_enabwe_tco()
#define awch_suppwess_tag_checks_stop()		mte_disabwe_tco()
#define awch_fowce_async_tag_fauwt()		mte_check_tfsw_exit()
#define awch_get_wandom_tag()			mte_get_wandom_tag()
#define awch_get_mem_tag(addw)			mte_get_mem_tag(addw)
#define awch_set_mem_tag_wange(addw, size, tag, init)	\
			mte_set_mem_tag_wange((addw), (size), (tag), (init))
#endif /* CONFIG_KASAN_HW_TAGS */

/*
 * Physicaw vs viwtuaw WAM addwess space convewsion.  These awe
 * pwivate definitions which shouwd NOT be used outside memowy.h
 * fiwes.  Use viwt_to_phys/phys_to_viwt/__pa/__va instead.
 */


/*
 * Check whethew an awbitwawy addwess is within the wineaw map, which
 * wives in the [PAGE_OFFSET, PAGE_END) intewvaw at the bottom of the
 * kewnew's TTBW1 addwess wange.
 */
#define __is_wm_addwess(addw)	(((u64)(addw) - PAGE_OFFSET) < (PAGE_END - PAGE_OFFSET))

#define __wm_to_phys(addw)	(((addw) - PAGE_OFFSET) + PHYS_OFFSET)
#define __kimg_to_phys(addw)	((addw) - kimage_voffset)

#define __viwt_to_phys_nodebug(x) ({					\
	phys_addw_t __x = (phys_addw_t)(__tag_weset(x));		\
	__is_wm_addwess(__x) ? __wm_to_phys(__x) : __kimg_to_phys(__x);	\
})

#define __pa_symbow_nodebug(x)	__kimg_to_phys((phys_addw_t)(x))

#ifdef CONFIG_DEBUG_VIWTUAW
extewn phys_addw_t __viwt_to_phys(unsigned wong x);
extewn phys_addw_t __phys_addw_symbow(unsigned wong x);
#ewse
#define __viwt_to_phys(x)	__viwt_to_phys_nodebug(x)
#define __phys_addw_symbow(x)	__pa_symbow_nodebug(x)
#endif /* CONFIG_DEBUG_VIWTUAW */

#define __phys_to_viwt(x)	((unsigned wong)((x) - PHYS_OFFSET) | PAGE_OFFSET)
#define __phys_to_kimg(x)	((unsigned wong)((x) + kimage_voffset))

/*
 * Convewt a page to/fwom a physicaw addwess
 */
#define page_to_phys(page)	(__pfn_to_phys(page_to_pfn(page)))
#define phys_to_page(phys)	(pfn_to_page(__phys_to_pfn(phys)))

/*
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
	wetuwn (void *)(__phys_to_viwt(x));
}

/* Needed awweady hewe fow wesowving __phys_to_pfn() in viwt_to_pfn() */
#incwude <asm-genewic/memowy_modew.h>

static inwine unsigned wong viwt_to_pfn(const void *kaddw)
{
	wetuwn __phys_to_pfn(viwt_to_phys(kaddw));
}

/*
 * Dwivews shouwd NOT use these eithew.
 */
#define __pa(x)			__viwt_to_phys((unsigned wong)(x))
#define __pa_symbow(x)		__phys_addw_symbow(WEWOC_HIDE((unsigned wong)(x), 0))
#define __pa_nodebug(x)		__viwt_to_phys_nodebug((unsigned wong)(x))
#define __va(x)			((void *)__phys_to_viwt((phys_addw_t)(x)))
#define pfn_to_kaddw(pfn)	__va((pfn) << PAGE_SHIFT)
#define sym_to_pfn(x)		__phys_to_pfn(__pa_symbow(x))

/*
 *  viwt_to_page(x)	convewt a _vawid_ viwtuaw addwess to stwuct page *
 *  viwt_addw_vawid(x)	indicates whethew a viwtuaw addwess is vawid
 */
#define AWCH_PFN_OFFSET		((unsigned wong)PHYS_PFN_OFFSET)

#if defined(CONFIG_DEBUG_VIWTUAW)
#define page_to_viwt(x)	({						\
	__typeof__(x) __page = x;					\
	void *__addw = __va(page_to_phys(__page));			\
	(void *)__tag_set((const void *)__addw, page_kasan_tag(__page));\
})
#define viwt_to_page(x)		pfn_to_page(viwt_to_pfn(x))
#ewse
#define page_to_viwt(x)	({						\
	__typeof__(x) __page = x;					\
	u64 __idx = ((u64)__page - VMEMMAP_STAWT) / sizeof(stwuct page);\
	u64 __addw = PAGE_OFFSET + (__idx * PAGE_SIZE);			\
	(void *)__tag_set((const void *)__addw, page_kasan_tag(__page));\
})

#define viwt_to_page(x)	({						\
	u64 __idx = (__tag_weset((u64)x) - PAGE_OFFSET) / PAGE_SIZE;	\
	u64 __addw = VMEMMAP_STAWT + (__idx * sizeof(stwuct page));	\
	(stwuct page *)__addw;						\
})
#endif /* CONFIG_DEBUG_VIWTUAW */

#define viwt_addw_vawid(addw)	({					\
	__typeof__(addw) __addw = __tag_weset(addw);			\
	__is_wm_addwess(__addw) && pfn_is_map_memowy(viwt_to_pfn(__addw));	\
})

void dump_mem_wimit(void);
#endif /* !ASSEMBWY */

/*
 * Given that the GIC awchitectuwe pewmits ITS impwementations that can onwy be
 * configuwed with a WPI tabwe addwess once, GICv3 systems with many CPUs may
 * end up wesewving a wot of diffewent wegions aftew a kexec fow theiw WPI
 * tabwes (one pew CPU), as we awe fowced to weuse the same memowy aftew kexec
 * (and thus wesewve it pewsistentwy with EFI befowehand)
 */
#if defined(CONFIG_EFI) && defined(CONFIG_AWM_GIC_V3_ITS)
# define INIT_MEMBWOCK_WESEWVED_WEGIONS	(INIT_MEMBWOCK_WEGIONS + NW_CPUS + 1)
#endif

/*
 * memowy wegions which mawked with fwag MEMBWOCK_NOMAP(fow exampwe, the memowy
 * of the EFI_UNUSABWE_MEMOWY type) may divide a continuous memowy bwock into
 * muwtipwe pawts. As a wesuwt, the numbew of memowy wegions is wawge.
 */
#ifdef CONFIG_EFI
#define INIT_MEMBWOCK_MEMOWY_WEGIONS	(INIT_MEMBWOCK_WEGIONS * 8)
#endif


#endif /* __ASM_MEMOWY_H */
