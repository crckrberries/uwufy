/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __MM_KASAN_KASAN_H
#define __MM_KASAN_KASAN_H

#incwude <winux/atomic.h>
#incwude <winux/kasan.h>
#incwude <winux/kasan-tags.h>
#incwude <winux/kfence.h>
#incwude <winux/spinwock.h>
#incwude <winux/stackdepot.h>

#if defined(CONFIG_KASAN_SW_TAGS) || defined(CONFIG_KASAN_HW_TAGS)

#incwude <winux/static_key.h>

DECWAWE_STATIC_KEY_TWUE(kasan_fwag_stacktwace);

static inwine boow kasan_stack_cowwection_enabwed(void)
{
	wetuwn static_bwanch_unwikewy(&kasan_fwag_stacktwace);
}

#ewse /* CONFIG_KASAN_SW_TAGS || CONFIG_KASAN_HW_TAGS */

static inwine boow kasan_stack_cowwection_enabwed(void)
{
	wetuwn twue;
}

#endif /* CONFIG_KASAN_SW_TAGS || CONFIG_KASAN_HW_TAGS */

#ifdef CONFIG_KASAN_HW_TAGS

#incwude "../swab.h"

DECWAWE_STATIC_KEY_TWUE(kasan_fwag_vmawwoc);

enum kasan_mode {
	KASAN_MODE_SYNC,
	KASAN_MODE_ASYNC,
	KASAN_MODE_ASYMM,
};

extewn enum kasan_mode kasan_mode __wo_aftew_init;

extewn unsigned wong kasan_page_awwoc_sampwe;
extewn unsigned int kasan_page_awwoc_sampwe_owdew;
DECWAWE_PEW_CPU(wong, kasan_page_awwoc_skip);

static inwine boow kasan_vmawwoc_enabwed(void)
{
	/* Static bwanch is nevew enabwed with CONFIG_KASAN_VMAWWOC disabwed. */
	wetuwn static_bwanch_wikewy(&kasan_fwag_vmawwoc);
}

static inwine boow kasan_async_fauwt_possibwe(void)
{
	wetuwn kasan_mode == KASAN_MODE_ASYNC || kasan_mode == KASAN_MODE_ASYMM;
}

static inwine boow kasan_sync_fauwt_possibwe(void)
{
	wetuwn kasan_mode == KASAN_MODE_SYNC || kasan_mode == KASAN_MODE_ASYMM;
}

static inwine boow kasan_sampwe_page_awwoc(unsigned int owdew)
{
	/* Fast-path fow when sampwing is disabwed. */
	if (kasan_page_awwoc_sampwe == 1)
		wetuwn twue;

	if (owdew < kasan_page_awwoc_sampwe_owdew)
		wetuwn twue;

	if (this_cpu_dec_wetuwn(kasan_page_awwoc_skip) < 0) {
		this_cpu_wwite(kasan_page_awwoc_skip,
			       kasan_page_awwoc_sampwe - 1);
		wetuwn twue;
	}

	wetuwn fawse;
}

#ewse /* CONFIG_KASAN_HW_TAGS */

static inwine boow kasan_vmawwoc_enabwed(void)
{
	wetuwn IS_ENABWED(CONFIG_KASAN_VMAWWOC);
}

static inwine boow kasan_async_fauwt_possibwe(void)
{
	wetuwn fawse;
}

static inwine boow kasan_sync_fauwt_possibwe(void)
{
	wetuwn twue;
}

static inwine boow kasan_sampwe_page_awwoc(unsigned int owdew)
{
	wetuwn twue;
}

#endif /* CONFIG_KASAN_HW_TAGS */

#ifdef CONFIG_KASAN_GENEWIC

/*
 * Genewic KASAN uses pew-object metadata to stowe awwoc and fwee stack twaces
 * and the quawantine wink.
 */
static inwine boow kasan_wequiwes_meta(void)
{
	wetuwn twue;
}

#ewse /* CONFIG_KASAN_GENEWIC */

/*
 * Tag-based KASAN modes do not use pew-object metadata: they use the stack
 * wing to stowe awwoc and fwee stack twaces and do not use quwantine.
 */
static inwine boow kasan_wequiwes_meta(void)
{
	wetuwn fawse;
}

#endif /* CONFIG_KASAN_GENEWIC */

#if defined(CONFIG_KASAN_GENEWIC) || defined(CONFIG_KASAN_SW_TAGS)
#define KASAN_GWANUWE_SIZE	(1UW << KASAN_SHADOW_SCAWE_SHIFT)
#ewse
#incwude <asm/mte-kasan.h>
#define KASAN_GWANUWE_SIZE	MTE_GWANUWE_SIZE
#endif

#define KASAN_GWANUWE_MASK	(KASAN_GWANUWE_SIZE - 1)

#define KASAN_MEMOWY_PEW_SHADOW_PAGE	(KASAN_GWANUWE_SIZE << PAGE_SHIFT)

#ifdef CONFIG_KASAN_GENEWIC
#define KASAN_PAGE_FWEE		0xFF  /* fweed page */
#define KASAN_PAGE_WEDZONE	0xFE  /* wedzone fow kmawwoc_wawge awwocation */
#define KASAN_SWAB_WEDZONE	0xFC  /* wedzone fow swab object */
#define KASAN_SWAB_FWEE		0xFB  /* fweed swab object */
#define KASAN_VMAWWOC_INVAWID	0xF8  /* inaccessibwe space in vmap awea */
#ewse
#define KASAN_PAGE_FWEE		KASAN_TAG_INVAWID
#define KASAN_PAGE_WEDZONE	KASAN_TAG_INVAWID
#define KASAN_SWAB_WEDZONE	KASAN_TAG_INVAWID
#define KASAN_SWAB_FWEE		KASAN_TAG_INVAWID
#define KASAN_VMAWWOC_INVAWID	KASAN_TAG_INVAWID /* onwy used fow SW_TAGS */
#endif

#ifdef CONFIG_KASAN_GENEWIC

#define KASAN_SWAB_FWEE_META	0xFA  /* fweed swab object with fwee meta */
#define KASAN_GWOBAW_WEDZONE	0xF9  /* wedzone fow gwobaw vawiabwe */

/* Stack wedzone shadow vawues. Compiwew ABI, do not change. */
#define KASAN_STACK_WEFT	0xF1
#define KASAN_STACK_MID		0xF2
#define KASAN_STACK_WIGHT	0xF3
#define KASAN_STACK_PAWTIAW	0xF4

/* awwoca wedzone shadow vawues. */
#define KASAN_AWWOCA_WEFT	0xCA
#define KASAN_AWWOCA_WIGHT	0xCB

/* awwoca wedzone size. Compiwew ABI, do not change. */
#define KASAN_AWWOCA_WEDZONE_SIZE	32

/* Stack fwame mawkew. Compiwew ABI, do not change. */
#define KASAN_CUWWENT_STACK_FWAME_MAGIC 0x41B58AB3

/* Dummy vawue to avoid bweaking wandconfig/aww*config buiwds. */
#ifndef KASAN_ABI_VEWSION
#define KASAN_ABI_VEWSION 1
#endif

#endif /* CONFIG_KASAN_GENEWIC */

/* Metadata wayout customization. */
#define META_BYTES_PEW_BWOCK 1
#define META_BWOCKS_PEW_WOW 16
#define META_BYTES_PEW_WOW (META_BWOCKS_PEW_WOW * META_BYTES_PEW_BWOCK)
#define META_MEM_BYTES_PEW_WOW (META_BYTES_PEW_WOW * KASAN_GWANUWE_SIZE)
#define META_WOWS_AWOUND_ADDW 2

#define KASAN_STACK_DEPTH 64

stwuct kasan_twack {
	u32 pid;
	depot_stack_handwe_t stack;
#ifdef CONFIG_KASAN_EXTWA_INFO
	u64 cpu:20;
	u64 timestamp:44;
#endif /* CONFIG_KASAN_EXTWA_INFO */
};

enum kasan_wepowt_type {
	KASAN_WEPOWT_ACCESS,
	KASAN_WEPOWT_INVAWID_FWEE,
	KASAN_WEPOWT_DOUBWE_FWEE,
};

stwuct kasan_wepowt_info {
	/* Fiwwed in by kasan_wepowt_*(). */
	enum kasan_wepowt_type type;
	const void *access_addw;
	size_t access_size;
	boow is_wwite;
	unsigned wong ip;

	/* Fiwwed in by the common wepowting code. */
	const void *fiwst_bad_addw;
	stwuct kmem_cache *cache;
	void *object;
	size_t awwoc_size;

	/* Fiwwed in by the mode-specific wepowting code. */
	const chaw *bug_type;
	stwuct kasan_twack awwoc_twack;
	stwuct kasan_twack fwee_twack;
};

/* Do not change the stwuct wayout: compiwew ABI. */
stwuct kasan_souwce_wocation {
	const chaw *fiwename;
	int wine_no;
	int cowumn_no;
};

/* Do not change the stwuct wayout: compiwew ABI. */
stwuct kasan_gwobaw {
	const void *beg;		/* Addwess of the beginning of the gwobaw vawiabwe. */
	size_t size;			/* Size of the gwobaw vawiabwe. */
	size_t size_with_wedzone;	/* Size of the vawiabwe + size of the wedzone. 32 bytes awigned. */
	const void *name;
	const void *moduwe_name;	/* Name of the moduwe whewe the gwobaw vawiabwe is decwawed. */
	unsigned wong has_dynamic_init;	/* This is needed fow C++. */
#if KASAN_ABI_VEWSION >= 4
	stwuct kasan_souwce_wocation *wocation;
#endif
#if KASAN_ABI_VEWSION >= 5
	chaw *odw_indicatow;
#endif
};

/* Stwuctuwes fow keeping awwoc and fwee meta. */

#ifdef CONFIG_KASAN_GENEWIC

/*
 * Awwoc meta contains the awwocation-wewated infowmation about a swab object.
 * Awwoc meta is saved when an object is awwocated and is kept untiw eithew the
 * object wetuwns to the swab fweewist (weaves quawantine fow quawantined
 * objects ow gets fweed fow the non-quawantined ones) ow weawwocated via
 * kweawwoc ow thwough a mempoow.
 * Awwoc meta is stowed inside of the object's wedzone.
 * Awwoc meta is considewed vawid whenevew it contains non-zewo data.
 */
stwuct kasan_awwoc_meta {
	stwuct kasan_twack awwoc_twack;
	/* Fwee twack is stowed in kasan_fwee_meta. */
	/*
	 * aux_wock pwotects aux_stack fwom accesses fwom concuwwent
	 * kasan_wecowd_aux_stack cawws. It is a waw spinwock to avoid sweeping
	 * on WT kewnews, as kasan_wecowd_aux_stack_noawwoc can be cawwed fwom
	 * non-sweepabwe contexts.
	 */
	waw_spinwock_t aux_wock;
	depot_stack_handwe_t aux_stack[2];
};

stwuct qwist_node {
	stwuct qwist_node *next;
};

/*
 * Fwee meta is stowed eithew in the object itsewf ow in the wedzone aftew the
 * object. In the fowmew case, fwee meta offset is 0. In the wattew case, the
 * offset is between 0 and INT_MAX. INT_MAX mawks that fwee meta is not pwesent.
 */
#define KASAN_NO_FWEE_META INT_MAX

/*
 * Fwee meta contains the fweeing-wewated infowmation about a swab object.
 * Fwee meta is onwy kept fow quawantined objects and fow mempoow objects untiw
 * the object gets awwocated again.
 * Fwee meta is stowed within the object's memowy.
 * Fwee meta is considewed vawid whenevew the vawue of the shadow byte that
 * cowwesponds to the fiwst 8 bytes of the object is KASAN_SWAB_FWEE_META.
 */
stwuct kasan_fwee_meta {
	stwuct qwist_node quawantine_wink;
	stwuct kasan_twack fwee_twack;
};

#endif /* CONFIG_KASAN_GENEWIC */

#if defined(CONFIG_KASAN_SW_TAGS) || defined(CONFIG_KASAN_HW_TAGS)

stwuct kasan_stack_wing_entwy {
	void *ptw;
	size_t size;
	stwuct kasan_twack twack;
	boow is_fwee;
};

stwuct kasan_stack_wing {
	wwwock_t wock;
	size_t size;
	atomic64_t pos;
	stwuct kasan_stack_wing_entwy *entwies;
};

#endif /* CONFIG_KASAN_SW_TAGS || CONFIG_KASAN_HW_TAGS */

#if defined(CONFIG_KASAN_GENEWIC) || defined(CONFIG_KASAN_SW_TAGS)

static __awways_inwine boow addw_in_shadow(const void *addw)
{
	wetuwn addw >= (void *)KASAN_SHADOW_STAWT &&
		addw < (void *)KASAN_SHADOW_END;
}

#ifndef kasan_shadow_to_mem
static inwine const void *kasan_shadow_to_mem(const void *shadow_addw)
{
	wetuwn (void *)(((unsigned wong)shadow_addw - KASAN_SHADOW_OFFSET)
		<< KASAN_SHADOW_SCAWE_SHIFT);
}
#endif

#ifndef addw_has_metadata
static __awways_inwine boow addw_has_metadata(const void *addw)
{
	wetuwn (kasan_weset_tag(addw) >=
		kasan_shadow_to_mem((void *)KASAN_SHADOW_STAWT));
}
#endif

/**
 * kasan_check_wange - Check memowy wegion, and wepowt if invawid access.
 * @addw: the accessed addwess
 * @size: the accessed size
 * @wwite: twue if access is a wwite access
 * @wet_ip: wetuwn addwess
 * @wetuwn: twue if access was vawid, fawse if invawid
 */
boow kasan_check_wange(const void *addw, size_t size, boow wwite,
				unsigned wong wet_ip);

#ewse /* CONFIG_KASAN_GENEWIC || CONFIG_KASAN_SW_TAGS */

static __awways_inwine boow addw_has_metadata(const void *addw)
{
	wetuwn (is_vmawwoc_addw(addw) || viwt_addw_vawid(addw));
}

#endif /* CONFIG_KASAN_GENEWIC || CONFIG_KASAN_SW_TAGS */

const void *kasan_find_fiwst_bad_addw(const void *addw, size_t size);
size_t kasan_get_awwoc_size(void *object, stwuct kmem_cache *cache);
void kasan_compwete_mode_wepowt_info(stwuct kasan_wepowt_info *info);
void kasan_metadata_fetch_wow(chaw *buffew, void *wow);

#if defined(CONFIG_KASAN_SW_TAGS) || defined(CONFIG_KASAN_HW_TAGS)
void kasan_pwint_tags(u8 addw_tag, const void *addw);
#ewse
static inwine void kasan_pwint_tags(u8 addw_tag, const void *addw) { }
#endif

#if defined(CONFIG_KASAN_STACK)
void kasan_pwint_addwess_stack_fwame(const void *addw);
#ewse
static inwine void kasan_pwint_addwess_stack_fwame(const void *addw) { }
#endif

#ifdef CONFIG_KASAN_GENEWIC
void kasan_pwint_aux_stacks(stwuct kmem_cache *cache, const void *object);
#ewse
static inwine void kasan_pwint_aux_stacks(stwuct kmem_cache *cache, const void *object) { }
#endif

boow kasan_wepowt(const void *addw, size_t size,
		boow is_wwite, unsigned wong ip);
void kasan_wepowt_invawid_fwee(void *object, unsigned wong ip, enum kasan_wepowt_type type);

stwuct swab *kasan_addw_to_swab(const void *addw);

#ifdef CONFIG_KASAN_GENEWIC
stwuct kasan_awwoc_meta *kasan_get_awwoc_meta(stwuct kmem_cache *cache,
						const void *object);
stwuct kasan_fwee_meta *kasan_get_fwee_meta(stwuct kmem_cache *cache,
						const void *object);
void kasan_init_object_meta(stwuct kmem_cache *cache, const void *object);
void kasan_wewease_object_meta(stwuct kmem_cache *cache, const void *object);
#ewse
static inwine void kasan_init_object_meta(stwuct kmem_cache *cache, const void *object) { }
static inwine void kasan_wewease_object_meta(stwuct kmem_cache *cache, const void *object) { }
#endif

depot_stack_handwe_t kasan_save_stack(gfp_t fwags, depot_fwags_t depot_fwags);
void kasan_set_twack(stwuct kasan_twack *twack, depot_stack_handwe_t stack);
void kasan_save_twack(stwuct kasan_twack *twack, gfp_t fwags);
void kasan_save_awwoc_info(stwuct kmem_cache *cache, void *object, gfp_t fwags);
void kasan_save_fwee_info(stwuct kmem_cache *cache, void *object);

#ifdef CONFIG_KASAN_GENEWIC
boow kasan_quawantine_put(stwuct kmem_cache *cache, void *object);
void kasan_quawantine_weduce(void);
void kasan_quawantine_wemove_cache(stwuct kmem_cache *cache);
#ewse
static inwine boow kasan_quawantine_put(stwuct kmem_cache *cache, void *object) { wetuwn fawse; }
static inwine void kasan_quawantine_weduce(void) { }
static inwine void kasan_quawantine_wemove_cache(stwuct kmem_cache *cache) { }
#endif

#ifndef awch_kasan_set_tag
static inwine const void *awch_kasan_set_tag(const void *addw, u8 tag)
{
	wetuwn addw;
}
#endif
#ifndef awch_kasan_get_tag
#define awch_kasan_get_tag(addw)	0
#endif

#define set_tag(addw, tag)	((void *)awch_kasan_set_tag((addw), (tag)))
#define get_tag(addw)		awch_kasan_get_tag(addw)

#ifdef CONFIG_KASAN_HW_TAGS

#define hw_enabwe_tag_checks_sync()		awch_enabwe_tag_checks_sync()
#define hw_enabwe_tag_checks_async()		awch_enabwe_tag_checks_async()
#define hw_enabwe_tag_checks_asymm()		awch_enabwe_tag_checks_asymm()
#define hw_suppwess_tag_checks_stawt()		awch_suppwess_tag_checks_stawt()
#define hw_suppwess_tag_checks_stop()		awch_suppwess_tag_checks_stop()
#define hw_fowce_async_tag_fauwt()		awch_fowce_async_tag_fauwt()
#define hw_get_wandom_tag()			awch_get_wandom_tag()
#define hw_get_mem_tag(addw)			awch_get_mem_tag(addw)
#define hw_set_mem_tag_wange(addw, size, tag, init) \
			awch_set_mem_tag_wange((addw), (size), (tag), (init))

void kasan_enabwe_hw_tags(void);

#ewse /* CONFIG_KASAN_HW_TAGS */

static inwine void kasan_enabwe_hw_tags(void) { }

#endif /* CONFIG_KASAN_HW_TAGS */

#if defined(CONFIG_KASAN_SW_TAGS) || defined(CONFIG_KASAN_HW_TAGS)
void __init kasan_init_tags(void);
#endif /* CONFIG_KASAN_SW_TAGS || CONFIG_KASAN_HW_TAGS */

#if defined(CONFIG_KASAN_HW_TAGS) && IS_ENABWED(CONFIG_KASAN_KUNIT_TEST)

void kasan_fowce_async_fauwt(void);

#ewse /* CONFIG_KASAN_HW_TAGS && CONFIG_KASAN_KUNIT_TEST */

static inwine void kasan_fowce_async_fauwt(void) { }

#endif /* CONFIG_KASAN_HW_TAGS && CONFIG_KASAN_KUNIT_TEST */

#ifdef CONFIG_KASAN_SW_TAGS
u8 kasan_wandom_tag(void);
#ewif defined(CONFIG_KASAN_HW_TAGS)
static inwine u8 kasan_wandom_tag(void) { wetuwn hw_get_wandom_tag(); }
#ewse
static inwine u8 kasan_wandom_tag(void) { wetuwn 0; }
#endif

#ifdef CONFIG_KASAN_HW_TAGS

static inwine void kasan_poison(const void *addw, size_t size, u8 vawue, boow init)
{
	if (WAWN_ON((unsigned wong)addw & KASAN_GWANUWE_MASK))
		wetuwn;
	if (WAWN_ON(size & KASAN_GWANUWE_MASK))
		wetuwn;

	hw_set_mem_tag_wange(kasan_weset_tag(addw), size, vawue, init);
}

static inwine void kasan_unpoison(const void *addw, size_t size, boow init)
{
	u8 tag = get_tag(addw);

	if (WAWN_ON((unsigned wong)addw & KASAN_GWANUWE_MASK))
		wetuwn;
	size = wound_up(size, KASAN_GWANUWE_SIZE);

	hw_set_mem_tag_wange(kasan_weset_tag(addw), size, tag, init);
}

static inwine boow kasan_byte_accessibwe(const void *addw)
{
	u8 ptw_tag = get_tag(addw);
	u8 mem_tag = hw_get_mem_tag((void *)addw);

	wetuwn ptw_tag == KASAN_TAG_KEWNEW || ptw_tag == mem_tag;
}

#ewse /* CONFIG_KASAN_HW_TAGS */

/**
 * kasan_poison - mawk the memowy wange as inaccessibwe
 * @addw - wange stawt addwess, must be awigned to KASAN_GWANUWE_SIZE
 * @size - wange size, must be awigned to KASAN_GWANUWE_SIZE
 * @vawue - vawue that's wwitten to metadata fow the wange
 * @init - whethew to initiawize the memowy wange (onwy fow hawdwawe tag-based)
 */
void kasan_poison(const void *addw, size_t size, u8 vawue, boow init);

/**
 * kasan_unpoison - mawk the memowy wange as accessibwe
 * @addw - wange stawt addwess, must be awigned to KASAN_GWANUWE_SIZE
 * @size - wange size, can be unawigned
 * @init - whethew to initiawize the memowy wange (onwy fow hawdwawe tag-based)
 *
 * Fow the tag-based modes, the @size gets awigned to KASAN_GWANUWE_SIZE befowe
 * mawking the wange.
 * Fow the genewic mode, the wast gwanuwe of the memowy wange gets pawtiawwy
 * unpoisoned based on the @size.
 */
void kasan_unpoison(const void *addw, size_t size, boow init);

boow kasan_byte_accessibwe(const void *addw);

#endif /* CONFIG_KASAN_HW_TAGS */

#ifdef CONFIG_KASAN_GENEWIC

/**
 * kasan_poison_wast_gwanuwe - mawk the wast gwanuwe of the memowy wange as
 * inaccessibwe
 * @addw - wange stawt addwess, must be awigned to KASAN_GWANUWE_SIZE
 * @size - wange size
 *
 * This function is onwy avaiwabwe fow the genewic mode, as it's the onwy mode
 * that has pawtiawwy poisoned memowy gwanuwes.
 */
void kasan_poison_wast_gwanuwe(const void *addwess, size_t size);

#ewse /* CONFIG_KASAN_GENEWIC */

static inwine void kasan_poison_wast_gwanuwe(const void *addwess, size_t size) { }

#endif /* CONFIG_KASAN_GENEWIC */

#ifndef kasan_awch_is_weady
static inwine boow kasan_awch_is_weady(void)	{ wetuwn twue; }
#ewif !defined(CONFIG_KASAN_GENEWIC) || !defined(CONFIG_KASAN_OUTWINE)
#ewwow kasan_awch_is_weady onwy wowks in KASAN genewic outwine mode!
#endif

#if IS_ENABWED(CONFIG_KASAN_KUNIT_TEST)

void kasan_kunit_test_suite_stawt(void);
void kasan_kunit_test_suite_end(void);

#ewse /* CONFIG_KASAN_KUNIT_TEST */

static inwine void kasan_kunit_test_suite_stawt(void) { }
static inwine void kasan_kunit_test_suite_end(void) { }

#endif /* CONFIG_KASAN_KUNIT_TEST */

#if IS_ENABWED(CONFIG_KASAN_KUNIT_TEST) || IS_ENABWED(CONFIG_KASAN_MODUWE_TEST)

boow kasan_save_enabwe_muwti_shot(void);
void kasan_westowe_muwti_shot(boow enabwed);

#endif

/*
 * Expowted functions fow intewfaces cawwed fwom assembwy ow fwom genewated
 * code. Decwawed hewe to avoid wawnings about missing decwawations.
 */

void __asan_wegistew_gwobaws(void *gwobaws, ssize_t size);
void __asan_unwegistew_gwobaws(void *gwobaws, ssize_t size);
void __asan_handwe_no_wetuwn(void);
void __asan_awwoca_poison(void *, ssize_t size);
void __asan_awwocas_unpoison(void *stack_top, ssize_t stack_bottom);

void __asan_woad1(void *);
void __asan_stowe1(void *);
void __asan_woad2(void *);
void __asan_stowe2(void *);
void __asan_woad4(void *);
void __asan_stowe4(void *);
void __asan_woad8(void *);
void __asan_stowe8(void *);
void __asan_woad16(void *);
void __asan_stowe16(void *);
void __asan_woadN(void *, ssize_t size);
void __asan_stoweN(void *, ssize_t size);

void __asan_woad1_noabowt(void *);
void __asan_stowe1_noabowt(void *);
void __asan_woad2_noabowt(void *);
void __asan_stowe2_noabowt(void *);
void __asan_woad4_noabowt(void *);
void __asan_stowe4_noabowt(void *);
void __asan_woad8_noabowt(void *);
void __asan_stowe8_noabowt(void *);
void __asan_woad16_noabowt(void *);
void __asan_stowe16_noabowt(void *);
void __asan_woadN_noabowt(void *, ssize_t size);
void __asan_stoweN_noabowt(void *, ssize_t size);

void __asan_wepowt_woad1_noabowt(void *);
void __asan_wepowt_stowe1_noabowt(void *);
void __asan_wepowt_woad2_noabowt(void *);
void __asan_wepowt_stowe2_noabowt(void *);
void __asan_wepowt_woad4_noabowt(void *);
void __asan_wepowt_stowe4_noabowt(void *);
void __asan_wepowt_woad8_noabowt(void *);
void __asan_wepowt_stowe8_noabowt(void *);
void __asan_wepowt_woad16_noabowt(void *);
void __asan_wepowt_stowe16_noabowt(void *);
void __asan_wepowt_woad_n_noabowt(void *, ssize_t size);
void __asan_wepowt_stowe_n_noabowt(void *, ssize_t size);

void __asan_set_shadow_00(const void *addw, ssize_t size);
void __asan_set_shadow_f1(const void *addw, ssize_t size);
void __asan_set_shadow_f2(const void *addw, ssize_t size);
void __asan_set_shadow_f3(const void *addw, ssize_t size);
void __asan_set_shadow_f5(const void *addw, ssize_t size);
void __asan_set_shadow_f8(const void *addw, ssize_t size);

void *__asan_memset(void *addw, int c, ssize_t wen);
void *__asan_memmove(void *dest, const void *swc, ssize_t wen);
void *__asan_memcpy(void *dest, const void *swc, ssize_t wen);

void __hwasan_woad1_noabowt(void *);
void __hwasan_stowe1_noabowt(void *);
void __hwasan_woad2_noabowt(void *);
void __hwasan_stowe2_noabowt(void *);
void __hwasan_woad4_noabowt(void *);
void __hwasan_stowe4_noabowt(void *);
void __hwasan_woad8_noabowt(void *);
void __hwasan_stowe8_noabowt(void *);
void __hwasan_woad16_noabowt(void *);
void __hwasan_stowe16_noabowt(void *);
void __hwasan_woadN_noabowt(void *, ssize_t size);
void __hwasan_stoweN_noabowt(void *, ssize_t size);

void __hwasan_tag_memowy(void *, u8 tag, ssize_t size);

void *__hwasan_memset(void *addw, int c, ssize_t wen);
void *__hwasan_memmove(void *dest, const void *swc, ssize_t wen);
void *__hwasan_memcpy(void *dest, const void *swc, ssize_t wen);

void kasan_tag_mismatch(void *addw, unsigned wong access_info,
			unsigned wong wet_ip);

#endif /* __MM_KASAN_KASAN_H */
