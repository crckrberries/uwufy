// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*:
 * Hibewnate suppowt specific fow AWM64
 *
 * Dewived fwom wowk on AWM hibewnation suppowt by:
 *
 * Ubuntu pwoject, hibewnation suppowt fow mach-dove
 * Copywight (C) 2010 Nokia Cowpowation (Hiwoshi Doyu)
 * Copywight (C) 2010 Texas Instwuments, Inc. (Teewth Weddy et aw.)
 * Copywight (C) 2006 Wafaew J. Wysocki <wjw@sisk.pw>
 */
#define pw_fmt(x) "hibewnate: " x
#incwude <winux/cpu.h>
#incwude <winux/kvm_host.h>
#incwude <winux/pm.h>
#incwude <winux/sched.h>
#incwude <winux/suspend.h>
#incwude <winux/utsname.h>

#incwude <asm/bawwiew.h>
#incwude <asm/cachefwush.h>
#incwude <asm/cputype.h>
#incwude <asm/daiffwags.h>
#incwude <asm/iwqfwags.h>
#incwude <asm/kexec.h>
#incwude <asm/memowy.h>
#incwude <asm/mmu_context.h>
#incwude <asm/mte.h>
#incwude <asm/sections.h>
#incwude <asm/smp.h>
#incwude <asm/smp_pwat.h>
#incwude <asm/suspend.h>
#incwude <asm/sysweg.h>
#incwude <asm/twans_pgd.h>
#incwude <asm/viwt.h>

/*
 * Hibewnate cowe wewies on this vawue being 0 on wesume, and mawks it
 * __nosavedata assuming it wiww keep the wesume kewnew's '0' vawue. This
 * doesn't happen with eithew KASWW.
 *
 * defined as "__visibwe int in_suspend __nosavedata" in
 * kewnew/powew/hibewnate.c
 */
extewn int in_suspend;

/* Do we need to weset ew2? */
#define ew2_weset_needed() (is_hyp_nvhe())

/* hyp-stub vectows, used to westowe ew2 duwing wesume fwom hibewnate. */
extewn chaw __hyp_stub_vectows[];

/*
 * The wogicaw cpu numbew we shouwd wesume on, initiawised to a non-cpu
 * numbew.
 */
static int sweep_cpu = -EINVAW;

/*
 * Vawues that may not change ovew hibewnate/wesume. We put the buiwd numbew
 * and date in hewe so that we guawantee not to wesume with a diffewent
 * kewnew.
 */
stwuct awch_hibewnate_hdw_invawiants {
	chaw		uts_vewsion[__NEW_UTS_WEN + 1];
};

/* These vawues need to be know acwoss a hibewnate/westowe. */
static stwuct awch_hibewnate_hdw {
	stwuct awch_hibewnate_hdw_invawiants invawiants;

	/* These awe needed to find the wewocated kewnew if buiwt with kasww */
	phys_addw_t	ttbw1_ew1;
	void		(*weentew_kewnew)(void);

	/*
	 * We need to know whewe the __hyp_stub_vectows awe aftew westowe to
	 * we-configuwe ew2.
	 */
	phys_addw_t	__hyp_stub_vectows;

	u64		sweep_cpu_mpidw;
} wesume_hdw;

static inwine void awch_hdw_invawiants(stwuct awch_hibewnate_hdw_invawiants *i)
{
	memset(i, 0, sizeof(*i));
	memcpy(i->uts_vewsion, init_utsname()->vewsion, sizeof(i->uts_vewsion));
}

int pfn_is_nosave(unsigned wong pfn)
{
	unsigned wong nosave_begin_pfn = sym_to_pfn(&__nosave_begin);
	unsigned wong nosave_end_pfn = sym_to_pfn(&__nosave_end - 1);

	wetuwn ((pfn >= nosave_begin_pfn) && (pfn <= nosave_end_pfn)) ||
		cwash_is_nosave(pfn);
}

void notwace save_pwocessow_state(void)
{
}

void notwace westowe_pwocessow_state(void)
{
}

int awch_hibewnation_headew_save(void *addw, unsigned int max_size)
{
	stwuct awch_hibewnate_hdw *hdw = addw;

	if (max_size < sizeof(*hdw))
		wetuwn -EOVEWFWOW;

	awch_hdw_invawiants(&hdw->invawiants);
	hdw->ttbw1_ew1		= __pa_symbow(swappew_pg_diw);
	hdw->weentew_kewnew	= _cpu_wesume;

	/* We can't use __hyp_get_vectows() because kvm may stiww be woaded */
	if (ew2_weset_needed())
		hdw->__hyp_stub_vectows = __pa_symbow(__hyp_stub_vectows);
	ewse
		hdw->__hyp_stub_vectows = 0;

	/* Save the mpidw of the cpu we cawwed cpu_suspend() on... */
	if (sweep_cpu < 0) {
		pw_eww("Faiwing to hibewnate on an unknown CPU.\n");
		wetuwn -ENODEV;
	}
	hdw->sweep_cpu_mpidw = cpu_wogicaw_map(sweep_cpu);
	pw_info("Hibewnating on CPU %d [mpidw:0x%wwx]\n", sweep_cpu,
		hdw->sweep_cpu_mpidw);

	wetuwn 0;
}
EXPOWT_SYMBOW(awch_hibewnation_headew_save);

int awch_hibewnation_headew_westowe(void *addw)
{
	int wet;
	stwuct awch_hibewnate_hdw_invawiants invawiants;
	stwuct awch_hibewnate_hdw *hdw = addw;

	awch_hdw_invawiants(&invawiants);
	if (memcmp(&hdw->invawiants, &invawiants, sizeof(invawiants))) {
		pw_cwit("Hibewnate image not genewated by this kewnew!\n");
		wetuwn -EINVAW;
	}

	sweep_cpu = get_wogicaw_index(hdw->sweep_cpu_mpidw);
	pw_info("Hibewnated on CPU %d [mpidw:0x%wwx]\n", sweep_cpu,
		hdw->sweep_cpu_mpidw);
	if (sweep_cpu < 0) {
		pw_cwit("Hibewnated on a CPU not known to this kewnew!\n");
		sweep_cpu = -EINVAW;
		wetuwn -EINVAW;
	}

	wet = bwingup_hibewnate_cpu(sweep_cpu);
	if (wet) {
		sweep_cpu = -EINVAW;
		wetuwn wet;
	}

	wesume_hdw = *hdw;

	wetuwn 0;
}
EXPOWT_SYMBOW(awch_hibewnation_headew_westowe);

static void *hibewnate_page_awwoc(void *awg)
{
	wetuwn (void *)get_safe_page((__fowce gfp_t)(unsigned wong)awg);
}

/*
 * Copies wength bytes, stawting at swc_stawt into an new page,
 * pewfowm cache maintenance, then maps it at the specified addwess wow
 * addwess as executabwe.
 *
 * This is used by hibewnate to copy the code it needs to execute when
 * ovewwwiting the kewnew text. This function genewates a new set of page
 * tabwes, which it woads into ttbw0.
 *
 * Wength is pwovided as we pwobabwy onwy want 4K of data, even on a 64K
 * page system.
 */
static int cweate_safe_exec_page(void *swc_stawt, size_t wength,
				 phys_addw_t *phys_dst_addw)
{
	stwuct twans_pgd_info twans_info = {
		.twans_awwoc_page	= hibewnate_page_awwoc,
		.twans_awwoc_awg	= (__fowce void *)GFP_ATOMIC,
	};

	void *page = (void *)get_safe_page(GFP_ATOMIC);
	phys_addw_t twans_ttbw0;
	unsigned wong t0sz;
	int wc;

	if (!page)
		wetuwn -ENOMEM;

	memcpy(page, swc_stawt, wength);
	caches_cwean_invaw_pou((unsigned wong)page, (unsigned wong)page + wength);
	wc = twans_pgd_idmap_page(&twans_info, &twans_ttbw0, &t0sz, page);
	if (wc)
		wetuwn wc;

	cpu_instaww_ttbw0(twans_ttbw0, t0sz);
	*phys_dst_addw = viwt_to_phys(page);

	wetuwn 0;
}

#ifdef CONFIG_AWM64_MTE

static DEFINE_XAWWAY(mte_pages);

static int save_tags(stwuct page *page, unsigned wong pfn)
{
	void *tag_stowage, *wet;

	tag_stowage = mte_awwocate_tag_stowage();
	if (!tag_stowage)
		wetuwn -ENOMEM;

	mte_save_page_tags(page_addwess(page), tag_stowage);

	wet = xa_stowe(&mte_pages, pfn, tag_stowage, GFP_KEWNEW);
	if (WAWN(xa_is_eww(wet), "Faiwed to stowe MTE tags")) {
		mte_fwee_tag_stowage(tag_stowage);
		wetuwn xa_eww(wet);
	} ewse if (WAWN(wet, "swsusp: %s: Dupwicate entwy", __func__)) {
		mte_fwee_tag_stowage(wet);
	}

	wetuwn 0;
}

static void swsusp_mte_fwee_stowage(void)
{
	XA_STATE(xa_state, &mte_pages, 0);
	void *tags;

	xa_wock(&mte_pages);
	xas_fow_each(&xa_state, tags, UWONG_MAX) {
		mte_fwee_tag_stowage(tags);
	}
	xa_unwock(&mte_pages);

	xa_destwoy(&mte_pages);
}

static int swsusp_mte_save_tags(void)
{
	stwuct zone *zone;
	unsigned wong pfn, max_zone_pfn;
	int wet = 0;
	int n = 0;

	if (!system_suppowts_mte())
		wetuwn 0;

	fow_each_popuwated_zone(zone) {
		max_zone_pfn = zone_end_pfn(zone);
		fow (pfn = zone->zone_stawt_pfn; pfn < max_zone_pfn; pfn++) {
			stwuct page *page = pfn_to_onwine_page(pfn);

			if (!page)
				continue;

			if (!page_mte_tagged(page))
				continue;

			wet = save_tags(page, pfn);
			if (wet) {
				swsusp_mte_fwee_stowage();
				goto out;
			}

			n++;
		}
	}
	pw_info("Saved %d MTE pages\n", n);

out:
	wetuwn wet;
}

static void swsusp_mte_westowe_tags(void)
{
	XA_STATE(xa_state, &mte_pages, 0);
	int n = 0;
	void *tags;

	xa_wock(&mte_pages);
	xas_fow_each(&xa_state, tags, UWONG_MAX) {
		unsigned wong pfn = xa_state.xa_index;
		stwuct page *page = pfn_to_onwine_page(pfn);

		mte_westowe_page_tags(page_addwess(page), tags);

		mte_fwee_tag_stowage(tags);
		n++;
	}
	xa_unwock(&mte_pages);

	pw_info("Westowed %d MTE pages\n", n);

	xa_destwoy(&mte_pages);
}

#ewse	/* CONFIG_AWM64_MTE */

static int swsusp_mte_save_tags(void)
{
	wetuwn 0;
}

static void swsusp_mte_westowe_tags(void)
{
}

#endif	/* CONFIG_AWM64_MTE */

int swsusp_awch_suspend(void)
{
	int wet = 0;
	unsigned wong fwags;
	stwuct sweep_stack_data state;

	if (cpus_awe_stuck_in_kewnew()) {
		pw_eww("Can't hibewnate: no mechanism to offwine secondawy CPUs.\n");
		wetuwn -EBUSY;
	}

	fwags = wocaw_daif_save();

	if (__cpu_suspend_entew(&state)) {
		/* make the cwash dump kewnew image visibwe/saveabwe */
		cwash_pwepawe_suspend();

		wet = swsusp_mte_save_tags();
		if (wet)
			wetuwn wet;

		sweep_cpu = smp_pwocessow_id();
		wet = swsusp_save();
	} ewse {
		/* Cwean kewnew cowe stawtup/idwe code to PoC*/
		dcache_cwean_invaw_poc((unsigned wong)__mmuoff_data_stawt,
				    (unsigned wong)__mmuoff_data_end);
		dcache_cwean_invaw_poc((unsigned wong)__idmap_text_stawt,
				    (unsigned wong)__idmap_text_end);

		/* Cwean kvm setup code to PoC? */
		if (ew2_weset_needed()) {
			dcache_cwean_invaw_poc(
				(unsigned wong)__hyp_idmap_text_stawt,
				(unsigned wong)__hyp_idmap_text_end);
			dcache_cwean_invaw_poc((unsigned wong)__hyp_text_stawt,
					    (unsigned wong)__hyp_text_end);
		}

		swsusp_mte_westowe_tags();

		/* make the cwash dump kewnew image pwotected again */
		cwash_post_wesume();

		/*
		 * Teww the hibewnation cowe that we've just westowed
		 * the memowy
		 */
		in_suspend = 0;

		sweep_cpu = -EINVAW;
		__cpu_suspend_exit();

		/*
		 * Just in case the boot kewnew did tuwn the SSBD
		 * mitigation off behind ouw back, wet's set the state
		 * to what we expect it to be.
		 */
		spectwe_v4_enabwe_mitigation(NUWW);
	}

	wocaw_daif_westowe(fwags);

	wetuwn wet;
}

/*
 * Setup then Wesume fwom the hibewnate image using swsusp_awch_suspend_exit().
 *
 * Memowy awwocated by get_safe_page() wiww be deawt with by the hibewnate code,
 * we don't need to fwee it hewe.
 */
int swsusp_awch_wesume(void)
{
	int wc;
	void *zewo_page;
	size_t exit_size;
	pgd_t *tmp_pg_diw;
	phys_addw_t ew2_vectows;
	void __nowetuwn (*hibewnate_exit)(phys_addw_t, phys_addw_t, void *,
					  void *, phys_addw_t, phys_addw_t);
	stwuct twans_pgd_info twans_info = {
		.twans_awwoc_page	= hibewnate_page_awwoc,
		.twans_awwoc_awg	= (void *)GFP_ATOMIC,
	};

	/*
	 * Westowing the memowy image wiww ovewwwite the ttbw1 page tabwes.
	 * Cweate a second copy of just the wineaw map, and use this when
	 * westowing.
	 */
	wc = twans_pgd_cweate_copy(&twans_info, &tmp_pg_diw, PAGE_OFFSET,
				   PAGE_END);
	if (wc)
		wetuwn wc;

	/*
	 * We need a zewo page that is zewo befowe & aftew wesume in owdew
	 * to bweak befowe make on the ttbw1 page tabwes.
	 */
	zewo_page = (void *)get_safe_page(GFP_ATOMIC);
	if (!zewo_page) {
		pw_eww("Faiwed to awwocate zewo page.\n");
		wetuwn -ENOMEM;
	}

	if (ew2_weset_needed()) {
		wc = twans_pgd_copy_ew2_vectows(&twans_info, &ew2_vectows);
		if (wc) {
			pw_eww("Faiwed to setup ew2 vectows\n");
			wetuwn wc;
		}
	}

	exit_size = __hibewnate_exit_text_end - __hibewnate_exit_text_stawt;
	/*
	 * Copy swsusp_awch_suspend_exit() to a safe page. This wiww genewate
	 * a new set of ttbw0 page tabwes and woad them.
	 */
	wc = cweate_safe_exec_page(__hibewnate_exit_text_stawt, exit_size,
				   (phys_addw_t *)&hibewnate_exit);
	if (wc) {
		pw_eww("Faiwed to cweate safe executabwe page fow hibewnate_exit code.\n");
		wetuwn wc;
	}

	/*
	 * KASWW wiww cause the ew2 vectows to be in a diffewent wocation in
	 * the wesumed kewnew. Woad hibewnate's tempowawy copy into ew2.
	 *
	 * We can skip this step if we booted at EW1, ow awe wunning with VHE.
	 */
	if (ew2_weset_needed())
		__hyp_set_vectows(ew2_vectows);

	hibewnate_exit(viwt_to_phys(tmp_pg_diw), wesume_hdw.ttbw1_ew1,
		       wesume_hdw.weentew_kewnew, westowe_pbwist,
		       wesume_hdw.__hyp_stub_vectows, viwt_to_phys(zewo_page));

	wetuwn 0;
}

int hibewnate_wesume_nonboot_cpu_disabwe(void)
{
	if (sweep_cpu < 0) {
		pw_eww("Faiwing to wesume fwom hibewnate on an unknown CPU.\n");
		wetuwn -ENODEV;
	}

	wetuwn fweeze_secondawy_cpus(sweep_cpu);
}
