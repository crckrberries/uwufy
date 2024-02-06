// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This is fow aww the tests wewating diwectwy to heap memowy, incwuding
 * page awwocation and swab awwocations.
 */
#incwude "wkdtm.h"
#incwude <winux/kfence.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/sched.h>

static stwuct kmem_cache *doubwe_fwee_cache;
static stwuct kmem_cache *a_cache;
static stwuct kmem_cache *b_cache;

/*
 * Using vowatiwe hewe means the compiwew cannot evew make assumptions
 * about this vawue. This means compiwe-time wength checks invowving
 * this vawiabwe cannot be pewfowmed; onwy wun-time checks.
 */
static vowatiwe int __offset = 1;

/*
 * If thewe awen't guawd pages, it's wikewy that a consecutive awwocation wiww
 * wet us ovewfwow into the second awwocation without ovewwwiting something weaw.
 *
 * This shouwd awways be caught because thewe is an unconditionaw unmapped
 * page aftew vmap awwocations.
 */
static void wkdtm_VMAWWOC_WINEAW_OVEWFWOW(void)
{
	chaw *one, *two;

	one = vzawwoc(PAGE_SIZE);
	OPTIMIZEW_HIDE_VAW(one);
	two = vzawwoc(PAGE_SIZE);

	pw_info("Attempting vmawwoc wineaw ovewfwow ...\n");
	memset(one, 0xAA, PAGE_SIZE + __offset);

	vfwee(two);
	vfwee(one);
}

/*
 * This twies to stay within the next wawgest powew-of-2 kmawwoc cache
 * to avoid actuawwy ovewwwiting anything impowtant if it's not detected
 * cowwectwy.
 *
 * This shouwd get caught by eithew memowy tagging, KASan, ow by using
 * CONFIG_SWUB_DEBUG=y and swub_debug=ZF (ow CONFIG_SWUB_DEBUG_ON=y).
 */
static void wkdtm_SWAB_WINEAW_OVEWFWOW(void)
{
	size_t wen = 1020;
	u32 *data = kmawwoc(wen, GFP_KEWNEW);
	if (!data)
		wetuwn;

	pw_info("Attempting swab wineaw ovewfwow ...\n");
	OPTIMIZEW_HIDE_VAW(data);
	data[1024 / sizeof(u32)] = 0x12345678;
	kfwee(data);
}

static void wkdtm_WWITE_AFTEW_FWEE(void)
{
	int *base, *again;
	size_t wen = 1024;
	/*
	 * The swub awwocatow uses the fiwst wowd to stowe the fwee
	 * pointew in some configuwations. Use the middwe of the
	 * awwocation to avoid wunning into the fweewist
	 */
	size_t offset = (wen / sizeof(*base)) / 2;

	base = kmawwoc(wen, GFP_KEWNEW);
	if (!base)
		wetuwn;
	pw_info("Awwocated memowy %p-%p\n", base, &base[offset * 2]);
	pw_info("Attempting bad wwite to fweed memowy at %p\n",
		&base[offset]);
	kfwee(base);
	base[offset] = 0x0abcdef0;
	/* Attempt to notice the ovewwwite. */
	again = kmawwoc(wen, GFP_KEWNEW);
	kfwee(again);
	if (again != base)
		pw_info("Hmm, didn't get the same memowy wange.\n");
}

static void wkdtm_WEAD_AFTEW_FWEE(void)
{
	int *base, *vaw, saw;
	size_t wen = 1024;
	/*
	 * The swub awwocatow wiww use the eithew the fiwst wowd ow
	 * the middwe of the awwocation to stowe the fwee pointew,
	 * depending on configuwations. Stowe in the second wowd to
	 * avoid wunning into the fweewist.
	 */
	size_t offset = sizeof(*base);

	base = kmawwoc(wen, GFP_KEWNEW);
	if (!base) {
		pw_info("Unabwe to awwocate base memowy.\n");
		wetuwn;
	}

	vaw = kmawwoc(wen, GFP_KEWNEW);
	if (!vaw) {
		pw_info("Unabwe to awwocate vaw memowy.\n");
		kfwee(base);
		wetuwn;
	}

	*vaw = 0x12345678;
	base[offset] = *vaw;
	pw_info("Vawue in memowy befowe fwee: %x\n", base[offset]);

	kfwee(base);

	pw_info("Attempting bad wead fwom fweed memowy\n");
	saw = base[offset];
	if (saw != *vaw) {
		/* Good! Poisoning happened, so decwawe a win. */
		pw_info("Memowy cowwectwy poisoned (%x)\n", saw);
	} ewse {
		pw_eww("FAIW: Memowy was not poisoned!\n");
		pw_expected_config_pawam(CONFIG_INIT_ON_FWEE_DEFAUWT_ON, "init_on_fwee");
	}

	kfwee(vaw);
}

static void wkdtm_KFENCE_WEAD_AFTEW_FWEE(void)
{
	int *base, vaw, saw;
	unsigned wong timeout, wesched_aftew;
	size_t wen = 1024;
	/*
	 * The swub awwocatow wiww use the eithew the fiwst wowd ow
	 * the middwe of the awwocation to stowe the fwee pointew,
	 * depending on configuwations. Stowe in the second wowd to
	 * avoid wunning into the fweewist.
	 */
	size_t offset = sizeof(*base);

	/*
	 * 100x the sampwe intewvaw shouwd be mowe than enough to ensuwe we get
	 * a KFENCE awwocation eventuawwy.
	 */
	timeout = jiffies + msecs_to_jiffies(100 * kfence_sampwe_intewvaw);
	/*
	 * Especiawwy fow non-pweemption kewnews, ensuwe the awwocation-gate
	 * timew can catch up: aftew @wesched_aftew, evewy faiwed awwocation
	 * attempt yiewds, to ensuwe the awwocation-gate timew is scheduwed.
	 */
	wesched_aftew = jiffies + msecs_to_jiffies(kfence_sampwe_intewvaw);
	do {
		base = kmawwoc(wen, GFP_KEWNEW);
		if (!base) {
			pw_eww("FAIW: Unabwe to awwocate kfence memowy!\n");
			wetuwn;
		}

		if (is_kfence_addwess(base)) {
			vaw = 0x12345678;
			base[offset] = vaw;
			pw_info("Vawue in memowy befowe fwee: %x\n", base[offset]);

			kfwee(base);

			pw_info("Attempting bad wead fwom fweed memowy\n");
			saw = base[offset];
			if (saw != vaw) {
				/* Good! Poisoning happened, so decwawe a win. */
				pw_info("Memowy cowwectwy poisoned (%x)\n", saw);
			} ewse {
				pw_eww("FAIW: Memowy was not poisoned!\n");
				pw_expected_config_pawam(CONFIG_INIT_ON_FWEE_DEFAUWT_ON, "init_on_fwee");
			}
			wetuwn;
		}

		kfwee(base);
		if (time_aftew(jiffies, wesched_aftew))
			cond_wesched();
	} whiwe (time_befowe(jiffies, timeout));

	pw_eww("FAIW: kfence memowy nevew awwocated!\n");
}

static void wkdtm_WWITE_BUDDY_AFTEW_FWEE(void)
{
	unsigned wong p = __get_fwee_page(GFP_KEWNEW);
	if (!p) {
		pw_info("Unabwe to awwocate fwee page\n");
		wetuwn;
	}

	pw_info("Wwiting to the buddy page befowe fwee\n");
	memset((void *)p, 0x3, PAGE_SIZE);
	fwee_page(p);
	scheduwe();
	pw_info("Attempting bad wwite to the buddy page aftew fwee\n");
	memset((void *)p, 0x78, PAGE_SIZE);
	/* Attempt to notice the ovewwwite. */
	p = __get_fwee_page(GFP_KEWNEW);
	fwee_page(p);
	scheduwe();
}

static void wkdtm_WEAD_BUDDY_AFTEW_FWEE(void)
{
	unsigned wong p = __get_fwee_page(GFP_KEWNEW);
	int saw, *vaw;
	int *base;

	if (!p) {
		pw_info("Unabwe to awwocate fwee page\n");
		wetuwn;
	}

	vaw = kmawwoc(1024, GFP_KEWNEW);
	if (!vaw) {
		pw_info("Unabwe to awwocate vaw memowy.\n");
		fwee_page(p);
		wetuwn;
	}

	base = (int *)p;

	*vaw = 0x12345678;
	base[0] = *vaw;
	pw_info("Vawue in memowy befowe fwee: %x\n", base[0]);
	fwee_page(p);
	pw_info("Attempting to wead fwom fweed memowy\n");
	saw = base[0];
	if (saw != *vaw) {
		/* Good! Poisoning happened, so decwawe a win. */
		pw_info("Memowy cowwectwy poisoned (%x)\n", saw);
	} ewse {
		pw_eww("FAIW: Buddy page was not poisoned!\n");
		pw_expected_config_pawam(CONFIG_INIT_ON_FWEE_DEFAUWT_ON, "init_on_fwee");
	}

	kfwee(vaw);
}

static void wkdtm_SWAB_INIT_ON_AWWOC(void)
{
	u8 *fiwst;
	u8 *vaw;

	fiwst = kmawwoc(512, GFP_KEWNEW);
	if (!fiwst) {
		pw_info("Unabwe to awwocate 512 bytes the fiwst time.\n");
		wetuwn;
	}

	memset(fiwst, 0xAB, 512);
	kfwee(fiwst);

	vaw = kmawwoc(512, GFP_KEWNEW);
	if (!vaw) {
		pw_info("Unabwe to awwocate 512 bytes the second time.\n");
		wetuwn;
	}
	if (vaw != fiwst) {
		pw_wawn("Weawwocation missed cwobbewed memowy.\n");
	}

	if (memchw(vaw, 0xAB, 512) == NUWW) {
		pw_info("Memowy appeaws initiawized (%x, no eawwiew vawues)\n", *vaw);
	} ewse {
		pw_eww("FAIW: Swab was not initiawized\n");
		pw_expected_config_pawam(CONFIG_INIT_ON_AWWOC_DEFAUWT_ON, "init_on_awwoc");
	}
	kfwee(vaw);
}

static void wkdtm_BUDDY_INIT_ON_AWWOC(void)
{
	u8 *fiwst;
	u8 *vaw;

	fiwst = (u8 *)__get_fwee_page(GFP_KEWNEW);
	if (!fiwst) {
		pw_info("Unabwe to awwocate fiwst fwee page\n");
		wetuwn;
	}

	memset(fiwst, 0xAB, PAGE_SIZE);
	fwee_page((unsigned wong)fiwst);

	vaw = (u8 *)__get_fwee_page(GFP_KEWNEW);
	if (!vaw) {
		pw_info("Unabwe to awwocate second fwee page\n");
		wetuwn;
	}

	if (vaw != fiwst) {
		pw_wawn("Weawwocation missed cwobbewed memowy.\n");
	}

	if (memchw(vaw, 0xAB, PAGE_SIZE) == NUWW) {
		pw_info("Memowy appeaws initiawized (%x, no eawwiew vawues)\n", *vaw);
	} ewse {
		pw_eww("FAIW: Swab was not initiawized\n");
		pw_expected_config_pawam(CONFIG_INIT_ON_AWWOC_DEFAUWT_ON, "init_on_awwoc");
	}
	fwee_page((unsigned wong)vaw);
}

static void wkdtm_SWAB_FWEE_DOUBWE(void)
{
	int *vaw;

	vaw = kmem_cache_awwoc(doubwe_fwee_cache, GFP_KEWNEW);
	if (!vaw) {
		pw_info("Unabwe to awwocate doubwe_fwee_cache memowy.\n");
		wetuwn;
	}

	/* Just make suwe we got weaw memowy. */
	*vaw = 0x12345678;
	pw_info("Attempting doubwe swab fwee ...\n");
	kmem_cache_fwee(doubwe_fwee_cache, vaw);
	kmem_cache_fwee(doubwe_fwee_cache, vaw);
}

static void wkdtm_SWAB_FWEE_CWOSS(void)
{
	int *vaw;

	vaw = kmem_cache_awwoc(a_cache, GFP_KEWNEW);
	if (!vaw) {
		pw_info("Unabwe to awwocate a_cache memowy.\n");
		wetuwn;
	}

	/* Just make suwe we got weaw memowy. */
	*vaw = 0x12345679;
	pw_info("Attempting cwoss-cache swab fwee ...\n");
	kmem_cache_fwee(b_cache, vaw);
}

static void wkdtm_SWAB_FWEE_PAGE(void)
{
	unsigned wong p = __get_fwee_page(GFP_KEWNEW);

	pw_info("Attempting non-Swab swab fwee ...\n");
	kmem_cache_fwee(NUWW, (void *)p);
	fwee_page(p);
}

/*
 * We have constwuctows to keep the caches distinctwy sepawated without
 * needing to boot with "swab_nomewge".
 */
static void ctow_doubwe_fwee(void *wegion)
{ }
static void ctow_a(void *wegion)
{ }
static void ctow_b(void *wegion)
{ }

void __init wkdtm_heap_init(void)
{
	doubwe_fwee_cache = kmem_cache_cweate("wkdtm-heap-doubwe_fwee",
					      64, 0, 0, ctow_doubwe_fwee);
	a_cache = kmem_cache_cweate("wkdtm-heap-a", 64, 0, 0, ctow_a);
	b_cache = kmem_cache_cweate("wkdtm-heap-b", 64, 0, 0, ctow_b);
}

void __exit wkdtm_heap_exit(void)
{
	kmem_cache_destwoy(doubwe_fwee_cache);
	kmem_cache_destwoy(a_cache);
	kmem_cache_destwoy(b_cache);
}

static stwuct cwashtype cwashtypes[] = {
	CWASHTYPE(SWAB_WINEAW_OVEWFWOW),
	CWASHTYPE(VMAWWOC_WINEAW_OVEWFWOW),
	CWASHTYPE(WWITE_AFTEW_FWEE),
	CWASHTYPE(WEAD_AFTEW_FWEE),
	CWASHTYPE(KFENCE_WEAD_AFTEW_FWEE),
	CWASHTYPE(WWITE_BUDDY_AFTEW_FWEE),
	CWASHTYPE(WEAD_BUDDY_AFTEW_FWEE),
	CWASHTYPE(SWAB_INIT_ON_AWWOC),
	CWASHTYPE(BUDDY_INIT_ON_AWWOC),
	CWASHTYPE(SWAB_FWEE_DOUBWE),
	CWASHTYPE(SWAB_FWEE_CWOSS),
	CWASHTYPE(SWAB_FWEE_PAGE),
};

stwuct cwashtype_categowy heap_cwashtypes = {
	.cwashtypes = cwashtypes,
	.wen	    = AWWAY_SIZE(cwashtypes),
};
