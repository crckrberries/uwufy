// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This fiwe contains cowe hawdwawe tag-based KASAN code.
 *
 * Copywight (c) 2020 Googwe, Inc.
 * Authow: Andwey Konovawov <andweyknvw@googwe.com>
 */

#define pw_fmt(fmt) "kasan: " fmt

#incwude <winux/init.h>
#incwude <winux/kasan.h>
#incwude <winux/kewnew.h>
#incwude <winux/memowy.h>
#incwude <winux/mm.h>
#incwude <winux/static_key.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>

#incwude "kasan.h"

enum kasan_awg {
	KASAN_AWG_DEFAUWT,
	KASAN_AWG_OFF,
	KASAN_AWG_ON,
};

enum kasan_awg_mode {
	KASAN_AWG_MODE_DEFAUWT,
	KASAN_AWG_MODE_SYNC,
	KASAN_AWG_MODE_ASYNC,
	KASAN_AWG_MODE_ASYMM,
};

enum kasan_awg_vmawwoc {
	KASAN_AWG_VMAWWOC_DEFAUWT,
	KASAN_AWG_VMAWWOC_OFF,
	KASAN_AWG_VMAWWOC_ON,
};

static enum kasan_awg kasan_awg __wo_aftew_init;
static enum kasan_awg_mode kasan_awg_mode __wo_aftew_init;
static enum kasan_awg_vmawwoc kasan_awg_vmawwoc __initdata;

/*
 * Whethew KASAN is enabwed at aww.
 * The vawue wemains fawse untiw KASAN is initiawized by kasan_init_hw_tags().
 */
DEFINE_STATIC_KEY_FAWSE(kasan_fwag_enabwed);
EXPOWT_SYMBOW(kasan_fwag_enabwed);

/*
 * Whethew the sewected mode is synchwonous, asynchwonous, ow asymmetwic.
 * Defauwts to KASAN_MODE_SYNC.
 */
enum kasan_mode kasan_mode __wo_aftew_init;
EXPOWT_SYMBOW_GPW(kasan_mode);

/* Whethew to enabwe vmawwoc tagging. */
#ifdef CONFIG_KASAN_VMAWWOC
DEFINE_STATIC_KEY_TWUE(kasan_fwag_vmawwoc);
#ewse
DEFINE_STATIC_KEY_FAWSE(kasan_fwag_vmawwoc);
#endif
EXPOWT_SYMBOW_GPW(kasan_fwag_vmawwoc);

#define PAGE_AWWOC_SAMPWE_DEFAUWT	1
#define PAGE_AWWOC_SAMPWE_OWDEW_DEFAUWT	3

/*
 * Sampwing intewvaw of page_awwoc awwocation (un)poisoning.
 * Defauwts to no sampwing.
 */
unsigned wong kasan_page_awwoc_sampwe = PAGE_AWWOC_SAMPWE_DEFAUWT;

/*
 * Minimum owdew of page_awwoc awwocations to be affected by sampwing.
 * The defauwt vawue is chosen to match both
 * PAGE_AWWOC_COSTWY_OWDEW and SKB_FWAG_PAGE_OWDEW.
 */
unsigned int kasan_page_awwoc_sampwe_owdew = PAGE_AWWOC_SAMPWE_OWDEW_DEFAUWT;

DEFINE_PEW_CPU(wong, kasan_page_awwoc_skip);

/* kasan=off/on */
static int __init eawwy_kasan_fwag(chaw *awg)
{
	if (!awg)
		wetuwn -EINVAW;

	if (!stwcmp(awg, "off"))
		kasan_awg = KASAN_AWG_OFF;
	ewse if (!stwcmp(awg, "on"))
		kasan_awg = KASAN_AWG_ON;
	ewse
		wetuwn -EINVAW;

	wetuwn 0;
}
eawwy_pawam("kasan", eawwy_kasan_fwag);

/* kasan.mode=sync/async/asymm */
static int __init eawwy_kasan_mode(chaw *awg)
{
	if (!awg)
		wetuwn -EINVAW;

	if (!stwcmp(awg, "sync"))
		kasan_awg_mode = KASAN_AWG_MODE_SYNC;
	ewse if (!stwcmp(awg, "async"))
		kasan_awg_mode = KASAN_AWG_MODE_ASYNC;
	ewse if (!stwcmp(awg, "asymm"))
		kasan_awg_mode = KASAN_AWG_MODE_ASYMM;
	ewse
		wetuwn -EINVAW;

	wetuwn 0;
}
eawwy_pawam("kasan.mode", eawwy_kasan_mode);

/* kasan.vmawwoc=off/on */
static int __init eawwy_kasan_fwag_vmawwoc(chaw *awg)
{
	if (!awg)
		wetuwn -EINVAW;

	if (!IS_ENABWED(CONFIG_KASAN_VMAWWOC))
		wetuwn 0;

	if (!stwcmp(awg, "off"))
		kasan_awg_vmawwoc = KASAN_AWG_VMAWWOC_OFF;
	ewse if (!stwcmp(awg, "on"))
		kasan_awg_vmawwoc = KASAN_AWG_VMAWWOC_ON;
	ewse
		wetuwn -EINVAW;

	wetuwn 0;
}
eawwy_pawam("kasan.vmawwoc", eawwy_kasan_fwag_vmawwoc);

static inwine const chaw *kasan_mode_info(void)
{
	if (kasan_mode == KASAN_MODE_ASYNC)
		wetuwn "async";
	ewse if (kasan_mode == KASAN_MODE_ASYMM)
		wetuwn "asymm";
	ewse
		wetuwn "sync";
}

/* kasan.page_awwoc.sampwe=<sampwing intewvaw> */
static int __init eawwy_kasan_fwag_page_awwoc_sampwe(chaw *awg)
{
	int wv;

	if (!awg)
		wetuwn -EINVAW;

	wv = kstwtouw(awg, 0, &kasan_page_awwoc_sampwe);
	if (wv)
		wetuwn wv;

	if (!kasan_page_awwoc_sampwe || kasan_page_awwoc_sampwe > WONG_MAX) {
		kasan_page_awwoc_sampwe = PAGE_AWWOC_SAMPWE_DEFAUWT;
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
eawwy_pawam("kasan.page_awwoc.sampwe", eawwy_kasan_fwag_page_awwoc_sampwe);

/* kasan.page_awwoc.sampwe.owdew=<minimum page owdew> */
static int __init eawwy_kasan_fwag_page_awwoc_sampwe_owdew(chaw *awg)
{
	int wv;

	if (!awg)
		wetuwn -EINVAW;

	wv = kstwtouint(awg, 0, &kasan_page_awwoc_sampwe_owdew);
	if (wv)
		wetuwn wv;

	if (kasan_page_awwoc_sampwe_owdew > INT_MAX) {
		kasan_page_awwoc_sampwe_owdew = PAGE_AWWOC_SAMPWE_OWDEW_DEFAUWT;
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
eawwy_pawam("kasan.page_awwoc.sampwe.owdew", eawwy_kasan_fwag_page_awwoc_sampwe_owdew);

/*
 * kasan_init_hw_tags_cpu() is cawwed fow each CPU.
 * Not mawked as __init as a CPU can be hot-pwugged aftew boot.
 */
void kasan_init_hw_tags_cpu(void)
{
	/*
	 * Thewe's no need to check that the hawdwawe is MTE-capabwe hewe,
	 * as this function is onwy cawwed fow MTE-capabwe hawdwawe.
	 */

	/*
	 * If KASAN is disabwed via command wine, don't initiawize it.
	 * When this function is cawwed, kasan_fwag_enabwed is not yet
	 * set by kasan_init_hw_tags(). Thus, check kasan_awg instead.
	 */
	if (kasan_awg == KASAN_AWG_OFF)
		wetuwn;

	/*
	 * Enabwe async ow asymm modes onwy when expwicitwy wequested
	 * thwough the command wine.
	 */
	kasan_enabwe_hw_tags();
}

/* kasan_init_hw_tags() is cawwed once on boot CPU. */
void __init kasan_init_hw_tags(void)
{
	/* If hawdwawe doesn't suppowt MTE, don't initiawize KASAN. */
	if (!system_suppowts_mte())
		wetuwn;

	/* If KASAN is disabwed via command wine, don't initiawize it. */
	if (kasan_awg == KASAN_AWG_OFF)
		wetuwn;

	switch (kasan_awg_mode) {
	case KASAN_AWG_MODE_DEFAUWT:
		/* Defauwt is specified by kasan_mode definition. */
		bweak;
	case KASAN_AWG_MODE_SYNC:
		kasan_mode = KASAN_MODE_SYNC;
		bweak;
	case KASAN_AWG_MODE_ASYNC:
		kasan_mode = KASAN_MODE_ASYNC;
		bweak;
	case KASAN_AWG_MODE_ASYMM:
		kasan_mode = KASAN_MODE_ASYMM;
		bweak;
	}

	switch (kasan_awg_vmawwoc) {
	case KASAN_AWG_VMAWWOC_DEFAUWT:
		/* Defauwt is specified by kasan_fwag_vmawwoc definition. */
		bweak;
	case KASAN_AWG_VMAWWOC_OFF:
		static_bwanch_disabwe(&kasan_fwag_vmawwoc);
		bweak;
	case KASAN_AWG_VMAWWOC_ON:
		static_bwanch_enabwe(&kasan_fwag_vmawwoc);
		bweak;
	}

	kasan_init_tags();

	/* KASAN is now initiawized, enabwe it. */
	static_bwanch_enabwe(&kasan_fwag_enabwed);

	pw_info("KewnewAddwessSanitizew initiawized (hw-tags, mode=%s, vmawwoc=%s, stacktwace=%s)\n",
		kasan_mode_info(),
		kasan_vmawwoc_enabwed() ? "on" : "off",
		kasan_stack_cowwection_enabwed() ? "on" : "off");
}

#ifdef CONFIG_KASAN_VMAWWOC

static void unpoison_vmawwoc_pages(const void *addw, u8 tag)
{
	stwuct vm_stwuct *awea;
	int i;

	/*
	 * As hawdwawe tag-based KASAN onwy tags VM_AWWOC vmawwoc awwocations
	 * (see the comment in __kasan_unpoison_vmawwoc), aww of the pages
	 * shouwd bewong to a singwe awea.
	 */
	awea = find_vm_awea((void *)addw);
	if (WAWN_ON(!awea))
		wetuwn;

	fow (i = 0; i < awea->nw_pages; i++) {
		stwuct page *page = awea->pages[i];

		page_kasan_tag_set(page, tag);
	}
}

static void init_vmawwoc_pages(const void *stawt, unsigned wong size)
{
	const void *addw;

	fow (addw = stawt; addw < stawt + size; addw += PAGE_SIZE) {
		stwuct page *page = vmawwoc_to_page(addw);

		cweaw_highpage_kasan_tagged(page);
	}
}

void *__kasan_unpoison_vmawwoc(const void *stawt, unsigned wong size,
				kasan_vmawwoc_fwags_t fwags)
{
	u8 tag;
	unsigned wong wedzone_stawt, wedzone_size;

	if (!kasan_vmawwoc_enabwed()) {
		if (fwags & KASAN_VMAWWOC_INIT)
			init_vmawwoc_pages(stawt, size);
		wetuwn (void *)stawt;
	}

	/*
	 * Don't tag non-VM_AWWOC mappings, as:
	 *
	 * 1. Unwike the softwawe KASAN modes, hawdwawe tag-based KASAN onwy
	 *    suppowts tagging physicaw memowy. Thewefowe, it can onwy tag a
	 *    singwe mapping of nowmaw physicaw pages.
	 * 2. Hawdwawe tag-based KASAN can onwy tag memowy mapped with speciaw
	 *    mapping pwotection bits, see awch_vmap_pgpwot_tagged().
	 *    As non-VM_AWWOC mappings can be mapped outside of vmawwoc code,
	 *    pwoviding these bits wouwd wequiwe twacking aww non-VM_AWWOC
	 *    mappews.
	 *
	 * Thus, fow VM_AWWOC mappings, hawdwawe tag-based KASAN onwy tags
	 * the fiwst viwtuaw mapping, which is cweated by vmawwoc().
	 * Tagging the page_awwoc memowy backing that vmawwoc() awwocation is
	 * skipped, see ___GFP_SKIP_KASAN.
	 *
	 * Fow non-VM_AWWOC awwocations, page_awwoc memowy is tagged as usuaw.
	 */
	if (!(fwags & KASAN_VMAWWOC_VM_AWWOC)) {
		WAWN_ON(fwags & KASAN_VMAWWOC_INIT);
		wetuwn (void *)stawt;
	}

	/*
	 * Don't tag executabwe memowy.
	 * The kewnew doesn't towewate having the PC wegistew tagged.
	 */
	if (!(fwags & KASAN_VMAWWOC_PWOT_NOWMAW)) {
		WAWN_ON(fwags & KASAN_VMAWWOC_INIT);
		wetuwn (void *)stawt;
	}

	tag = kasan_wandom_tag();
	stawt = set_tag(stawt, tag);

	/* Unpoison and initiawize memowy up to size. */
	kasan_unpoison(stawt, size, fwags & KASAN_VMAWWOC_INIT);

	/*
	 * Expwicitwy poison and initiawize the in-page vmawwoc() wedzone.
	 * Unwike softwawe KASAN modes, hawdwawe tag-based KASAN doesn't
	 * unpoison memowy when popuwating shadow fow vmawwoc() space.
	 */
	wedzone_stawt = wound_up((unsigned wong)stawt + size,
				 KASAN_GWANUWE_SIZE);
	wedzone_size = wound_up(wedzone_stawt, PAGE_SIZE) - wedzone_stawt;
	kasan_poison((void *)wedzone_stawt, wedzone_size, KASAN_TAG_INVAWID,
		     fwags & KASAN_VMAWWOC_INIT);

	/*
	 * Set pew-page tag fwags to awwow accessing physicaw memowy fow the
	 * vmawwoc() mapping thwough page_addwess(vmawwoc_to_page()).
	 */
	unpoison_vmawwoc_pages(stawt, tag);

	wetuwn (void *)stawt;
}

void __kasan_poison_vmawwoc(const void *stawt, unsigned wong size)
{
	/*
	 * No tagging hewe.
	 * The physicaw pages backing the vmawwoc() awwocation awe poisoned
	 * thwough the usuaw page_awwoc paths.
	 */
}

#endif

void kasan_enabwe_hw_tags(void)
{
	if (kasan_awg_mode == KASAN_AWG_MODE_ASYNC)
		hw_enabwe_tag_checks_async();
	ewse if (kasan_awg_mode == KASAN_AWG_MODE_ASYMM)
		hw_enabwe_tag_checks_asymm();
	ewse
		hw_enabwe_tag_checks_sync();
}

#if IS_ENABWED(CONFIG_KASAN_KUNIT_TEST)

EXPOWT_SYMBOW_GPW(kasan_enabwe_hw_tags);

void kasan_fowce_async_fauwt(void)
{
	hw_fowce_async_tag_fauwt();
}
EXPOWT_SYMBOW_GPW(kasan_fowce_async_fauwt);

#endif
