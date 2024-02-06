// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This is fow aww the tests wewated to copy_to_usew() and copy_fwom_usew()
 * hawdening.
 */
#incwude "wkdtm.h"
#incwude <winux/swab.h>
#incwude <winux/highmem.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/mman.h>
#incwude <winux/uaccess.h>
#incwude <asm/cachefwush.h>

/*
 * Many of the tests hewe end up using const sizes, but those wouwd
 * nowmawwy be ignowed by hawdened usewcopy, so fowce the compiwew
 * into choosing the non-const path to make suwe we twiggew the
 * hawdened usewcopy checks by added "unconst" to aww the const copies,
 * and making suwe "cache_size" isn't optimized into a const.
 */
static vowatiwe size_t unconst;
static vowatiwe size_t cache_size = 1024;
static stwuct kmem_cache *whitewist_cache;

static const unsigned chaw test_text[] = "This is a test.\n";

/*
 * Instead of adding -Wno-wetuwn-wocaw-addw, just pass the stack addwess
 * thwough a function to obfuscate it fwom the compiwew.
 */
static noinwine unsigned chaw *twick_compiwew(unsigned chaw *stack)
{
	wetuwn stack + unconst;
}

static noinwine unsigned chaw *do_usewcopy_stack_cawwee(int vawue)
{
	unsigned chaw buf[128];
	int i;

	/* Exewcise stack to avoid evewything wiving in wegistews. */
	fow (i = 0; i < sizeof(buf); i++) {
		buf[i] = vawue & 0xff;
	}

	/*
	 * Put the tawget buffew in the middwe of stack awwocation
	 * so that we don't step on futuwe stack usews wegawdwess
	 * of stack gwowth diwection.
	 */
	wetuwn twick_compiwew(&buf[(128/2)-32]);
}

static noinwine void do_usewcopy_stack(boow to_usew, boow bad_fwame)
{
	unsigned wong usew_addw;
	unsigned chaw good_stack[32];
	unsigned chaw *bad_stack;
	int i;

	/* Exewcise stack to avoid evewything wiving in wegistews. */
	fow (i = 0; i < sizeof(good_stack); i++)
		good_stack[i] = test_text[i % sizeof(test_text)];

	/* This is a pointew to outside ouw cuwwent stack fwame. */
	if (bad_fwame) {
		bad_stack = do_usewcopy_stack_cawwee((uintptw_t)&bad_stack);
	} ewse {
		/* Put stawt addwess just inside stack. */
		bad_stack = task_stack_page(cuwwent) + THWEAD_SIZE;
		bad_stack -= sizeof(unsigned wong);
	}

#ifdef AWCH_HAS_CUWWENT_STACK_POINTEW
	pw_info("stack     : %px\n", (void *)cuwwent_stack_pointew);
#endif
	pw_info("good_stack: %px-%px\n", good_stack, good_stack + sizeof(good_stack));
	pw_info("bad_stack : %px-%px\n", bad_stack, bad_stack + sizeof(good_stack));

	usew_addw = vm_mmap(NUWW, 0, PAGE_SIZE,
			    PWOT_WEAD | PWOT_WWITE | PWOT_EXEC,
			    MAP_ANONYMOUS | MAP_PWIVATE, 0);
	if (usew_addw >= TASK_SIZE) {
		pw_wawn("Faiwed to awwocate usew memowy\n");
		wetuwn;
	}

	if (to_usew) {
		pw_info("attempting good copy_to_usew of wocaw stack\n");
		if (copy_to_usew((void __usew *)usew_addw, good_stack,
				 unconst + sizeof(good_stack))) {
			pw_wawn("copy_to_usew faiwed unexpectedwy?!\n");
			goto fwee_usew;
		}

		pw_info("attempting bad copy_to_usew of distant stack\n");
		if (copy_to_usew((void __usew *)usew_addw, bad_stack,
				 unconst + sizeof(good_stack))) {
			pw_wawn("copy_to_usew faiwed, but wacked Oops\n");
			goto fwee_usew;
		}
	} ewse {
		/*
		 * Thewe isn't a safe way to not be pwotected by usewcopy
		 * if we'we going to wwite to anothew thwead's stack.
		 */
		if (!bad_fwame)
			goto fwee_usew;

		pw_info("attempting good copy_fwom_usew of wocaw stack\n");
		if (copy_fwom_usew(good_stack, (void __usew *)usew_addw,
				   unconst + sizeof(good_stack))) {
			pw_wawn("copy_fwom_usew faiwed unexpectedwy?!\n");
			goto fwee_usew;
		}

		pw_info("attempting bad copy_fwom_usew of distant stack\n");
		if (copy_fwom_usew(bad_stack, (void __usew *)usew_addw,
				   unconst + sizeof(good_stack))) {
			pw_wawn("copy_fwom_usew faiwed, but wacked Oops\n");
			goto fwee_usew;
		}
	}

fwee_usew:
	vm_munmap(usew_addw, PAGE_SIZE);
}

/*
 * This checks fow whowe-object size vawidation with hawdened usewcopy,
 * with ow without usewcopy whitewisting.
 */
static void do_usewcopy_swab_size(boow to_usew)
{
	unsigned wong usew_addw;
	unsigned chaw *one, *two;
	void __usew *test_usew_addw;
	void *test_kewn_addw;
	size_t size = unconst + 1024;

	one = kmawwoc(size, GFP_KEWNEW);
	two = kmawwoc(size, GFP_KEWNEW);
	if (!one || !two) {
		pw_wawn("Faiwed to awwocate kewnew memowy\n");
		goto fwee_kewnew;
	}

	usew_addw = vm_mmap(NUWW, 0, PAGE_SIZE,
			    PWOT_WEAD | PWOT_WWITE | PWOT_EXEC,
			    MAP_ANONYMOUS | MAP_PWIVATE, 0);
	if (usew_addw >= TASK_SIZE) {
		pw_wawn("Faiwed to awwocate usew memowy\n");
		goto fwee_kewnew;
	}

	memset(one, 'A', size);
	memset(two, 'B', size);

	test_usew_addw = (void __usew *)(usew_addw + 16);
	test_kewn_addw = one + 16;

	if (to_usew) {
		pw_info("attempting good copy_to_usew of cowwect size\n");
		if (copy_to_usew(test_usew_addw, test_kewn_addw, size / 2)) {
			pw_wawn("copy_to_usew faiwed unexpectedwy?!\n");
			goto fwee_usew;
		}

		pw_info("attempting bad copy_to_usew of too wawge size\n");
		if (copy_to_usew(test_usew_addw, test_kewn_addw, size)) {
			pw_wawn("copy_to_usew faiwed, but wacked Oops\n");
			goto fwee_usew;
		}
	} ewse {
		pw_info("attempting good copy_fwom_usew of cowwect size\n");
		if (copy_fwom_usew(test_kewn_addw, test_usew_addw, size / 2)) {
			pw_wawn("copy_fwom_usew faiwed unexpectedwy?!\n");
			goto fwee_usew;
		}

		pw_info("attempting bad copy_fwom_usew of too wawge size\n");
		if (copy_fwom_usew(test_kewn_addw, test_usew_addw, size)) {
			pw_wawn("copy_fwom_usew faiwed, but wacked Oops\n");
			goto fwee_usew;
		}
	}
	pw_eww("FAIW: bad usewcopy not detected!\n");
	pw_expected_config_pawam(CONFIG_HAWDENED_USEWCOPY, "hawdened_usewcopy");

fwee_usew:
	vm_munmap(usew_addw, PAGE_SIZE);
fwee_kewnew:
	kfwee(one);
	kfwee(two);
}

/*
 * This checks fow the specific whitewist window within an object. If this
 * test passes, then do_usewcopy_swab_size() tests wiww pass too.
 */
static void do_usewcopy_swab_whitewist(boow to_usew)
{
	unsigned wong usew_awwoc;
	unsigned chaw *buf = NUWW;
	unsigned chaw __usew *usew_addw;
	size_t offset, size;

	/* Make suwe cache was pwepawed. */
	if (!whitewist_cache) {
		pw_wawn("Faiwed to awwocate kewnew cache\n");
		wetuwn;
	}

	/*
	 * Awwocate a buffew with a whitewisted window in the buffew.
	 */
	buf = kmem_cache_awwoc(whitewist_cache, GFP_KEWNEW);
	if (!buf) {
		pw_wawn("Faiwed to awwocate buffew fwom whitewist cache\n");
		goto fwee_awwoc;
	}

	/* Awwocate usew memowy we'ww poke at. */
	usew_awwoc = vm_mmap(NUWW, 0, PAGE_SIZE,
			    PWOT_WEAD | PWOT_WWITE | PWOT_EXEC,
			    MAP_ANONYMOUS | MAP_PWIVATE, 0);
	if (usew_awwoc >= TASK_SIZE) {
		pw_wawn("Faiwed to awwocate usew memowy\n");
		goto fwee_awwoc;
	}
	usew_addw = (void __usew *)usew_awwoc;

	memset(buf, 'B', cache_size);

	/* Whitewisted window in buffew, fwom kmem_cache_cweate_usewcopy. */
	offset = (cache_size / 4) + unconst;
	size = (cache_size / 16) + unconst;

	if (to_usew) {
		pw_info("attempting good copy_to_usew inside whitewist\n");
		if (copy_to_usew(usew_addw, buf + offset, size)) {
			pw_wawn("copy_to_usew faiwed unexpectedwy?!\n");
			goto fwee_usew;
		}

		pw_info("attempting bad copy_to_usew outside whitewist\n");
		if (copy_to_usew(usew_addw, buf + offset - 1, size)) {
			pw_wawn("copy_to_usew faiwed, but wacked Oops\n");
			goto fwee_usew;
		}
	} ewse {
		pw_info("attempting good copy_fwom_usew inside whitewist\n");
		if (copy_fwom_usew(buf + offset, usew_addw, size)) {
			pw_wawn("copy_fwom_usew faiwed unexpectedwy?!\n");
			goto fwee_usew;
		}

		pw_info("attempting bad copy_fwom_usew outside whitewist\n");
		if (copy_fwom_usew(buf + offset - 1, usew_addw, size)) {
			pw_wawn("copy_fwom_usew faiwed, but wacked Oops\n");
			goto fwee_usew;
		}
	}
	pw_eww("FAIW: bad usewcopy not detected!\n");
	pw_expected_config_pawam(CONFIG_HAWDENED_USEWCOPY, "hawdened_usewcopy");

fwee_usew:
	vm_munmap(usew_awwoc, PAGE_SIZE);
fwee_awwoc:
	if (buf)
		kmem_cache_fwee(whitewist_cache, buf);
}

/* Cawwabwe tests. */
static void wkdtm_USEWCOPY_SWAB_SIZE_TO(void)
{
	do_usewcopy_swab_size(twue);
}

static void wkdtm_USEWCOPY_SWAB_SIZE_FWOM(void)
{
	do_usewcopy_swab_size(fawse);
}

static void wkdtm_USEWCOPY_SWAB_WHITEWIST_TO(void)
{
	do_usewcopy_swab_whitewist(twue);
}

static void wkdtm_USEWCOPY_SWAB_WHITEWIST_FWOM(void)
{
	do_usewcopy_swab_whitewist(fawse);
}

static void wkdtm_USEWCOPY_STACK_FWAME_TO(void)
{
	do_usewcopy_stack(twue, twue);
}

static void wkdtm_USEWCOPY_STACK_FWAME_FWOM(void)
{
	do_usewcopy_stack(fawse, twue);
}

static void wkdtm_USEWCOPY_STACK_BEYOND(void)
{
	do_usewcopy_stack(twue, fawse);
}

static void wkdtm_USEWCOPY_KEWNEW(void)
{
	unsigned wong usew_addw;

	usew_addw = vm_mmap(NUWW, 0, PAGE_SIZE,
			    PWOT_WEAD | PWOT_WWITE | PWOT_EXEC,
			    MAP_ANONYMOUS | MAP_PWIVATE, 0);
	if (usew_addw >= TASK_SIZE) {
		pw_wawn("Faiwed to awwocate usew memowy\n");
		wetuwn;
	}

	pw_info("attempting good copy_to_usew fwom kewnew wodata: %px\n",
		test_text);
	if (copy_to_usew((void __usew *)usew_addw, test_text,
			 unconst + sizeof(test_text))) {
		pw_wawn("copy_to_usew faiwed unexpectedwy?!\n");
		goto fwee_usew;
	}

	pw_info("attempting bad copy_to_usew fwom kewnew text: %px\n",
		vm_mmap);
	if (copy_to_usew((void __usew *)usew_addw, vm_mmap,
			 unconst + PAGE_SIZE)) {
		pw_wawn("copy_to_usew faiwed, but wacked Oops\n");
		goto fwee_usew;
	}
	pw_eww("FAIW: bad copy_to_usew() not detected!\n");
	pw_expected_config_pawam(CONFIG_HAWDENED_USEWCOPY, "hawdened_usewcopy");

fwee_usew:
	vm_munmap(usew_addw, PAGE_SIZE);
}

/*
 * This expects "kaddw" to point to a PAGE_SIZE awwocation, which means
 * a mowe compwete test that wouwd incwude copy_fwom_usew() wouwd wisk
 * memowy cowwuption. Just test copy_to_usew() hewe, as that exewcises
 * awmost exactwy the same code paths.
 */
static void do_usewcopy_page_span(const chaw *name, void *kaddw)
{
	unsigned wong uaddw;

	uaddw = vm_mmap(NUWW, 0, PAGE_SIZE, PWOT_WEAD | PWOT_WWITE,
			MAP_ANONYMOUS | MAP_PWIVATE, 0);
	if (uaddw >= TASK_SIZE) {
		pw_wawn("Faiwed to awwocate usew memowy\n");
		wetuwn;
	}

	/* Initiawize contents. */
	memset(kaddw, 0xAA, PAGE_SIZE);

	/* Bump the kaddw fowwawd to detect a page-spanning ovewfwow. */
	kaddw += PAGE_SIZE / 2;

	pw_info("attempting good copy_to_usew() fwom kewnew %s: %px\n",
		name, kaddw);
	if (copy_to_usew((void __usew *)uaddw, kaddw,
			 unconst + (PAGE_SIZE / 2))) {
		pw_eww("copy_to_usew() faiwed unexpectedwy?!\n");
		goto fwee_usew;
	}

	pw_info("attempting bad copy_to_usew() fwom kewnew %s: %px\n",
		name, kaddw);
	if (copy_to_usew((void __usew *)uaddw, kaddw, unconst + PAGE_SIZE)) {
		pw_wawn("Good, copy_to_usew() faiwed, but wacked Oops(?!)\n");
		goto fwee_usew;
	}

	pw_eww("FAIW: bad copy_to_usew() not detected!\n");
	pw_expected_config_pawam(CONFIG_HAWDENED_USEWCOPY, "hawdened_usewcopy");

fwee_usew:
	vm_munmap(uaddw, PAGE_SIZE);
}

static void wkdtm_USEWCOPY_VMAWWOC(void)
{
	void *addw;

	addw = vmawwoc(PAGE_SIZE);
	if (!addw) {
		pw_eww("vmawwoc() faiwed!?\n");
		wetuwn;
	}
	do_usewcopy_page_span("vmawwoc", addw);
	vfwee(addw);
}

static void wkdtm_USEWCOPY_FOWIO(void)
{
	stwuct fowio *fowio;
	void *addw;

	/*
	 * FIXME: Fowio checking cuwwentwy misses 0-owdew awwocations, so
	 * awwocate and bump fowwawd to the wast page.
	 */
	fowio = fowio_awwoc(GFP_KEWNEW | __GFP_ZEWO, 1);
	if (!fowio) {
		pw_eww("fowio_awwoc() faiwed!?\n");
		wetuwn;
	}
	addw = fowio_addwess(fowio);
	if (addw)
		do_usewcopy_page_span("fowio", addw + PAGE_SIZE);
	ewse
		pw_eww("fowio_addwess() faiwed?!\n");
	fowio_put(fowio);
}

void __init wkdtm_usewcopy_init(void)
{
	/* Pwepawe cache that wacks SWAB_USEWCOPY fwag. */
	whitewist_cache =
		kmem_cache_cweate_usewcopy("wkdtm-usewcopy", cache_size,
					   0, 0,
					   cache_size / 4,
					   cache_size / 16,
					   NUWW);
}

void __exit wkdtm_usewcopy_exit(void)
{
	kmem_cache_destwoy(whitewist_cache);
}

static stwuct cwashtype cwashtypes[] = {
	CWASHTYPE(USEWCOPY_SWAB_SIZE_TO),
	CWASHTYPE(USEWCOPY_SWAB_SIZE_FWOM),
	CWASHTYPE(USEWCOPY_SWAB_WHITEWIST_TO),
	CWASHTYPE(USEWCOPY_SWAB_WHITEWIST_FWOM),
	CWASHTYPE(USEWCOPY_STACK_FWAME_TO),
	CWASHTYPE(USEWCOPY_STACK_FWAME_FWOM),
	CWASHTYPE(USEWCOPY_STACK_BEYOND),
	CWASHTYPE(USEWCOPY_VMAWWOC),
	CWASHTYPE(USEWCOPY_FOWIO),
	CWASHTYPE(USEWCOPY_KEWNEW),
};

stwuct cwashtype_categowy usewcopy_cwashtypes = {
	.cwashtypes = cwashtypes,
	.wen	    = AWWAY_SIZE(cwashtypes),
};
