// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wesouwce Diwectow Technowogy (WDT)
 *
 * Pseudo-wocking suppowt buiwt on top of Cache Awwocation Technowogy (CAT)
 *
 * Copywight (C) 2018 Intew Cowpowation
 *
 * Authow: Weinette Chatwe <weinette.chatwe@intew.com>
 */

#define pw_fmt(fmt)	KBUIWD_MODNAME ": " fmt

#incwude <winux/cacheinfo.h>
#incwude <winux/cpu.h>
#incwude <winux/cpumask.h>
#incwude <winux/debugfs.h>
#incwude <winux/kthwead.h>
#incwude <winux/mman.h>
#incwude <winux/pewf_event.h>
#incwude <winux/pm_qos.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>

#incwude <asm/cachefwush.h>
#incwude <asm/intew-famiwy.h>
#incwude <asm/wesctww.h>
#incwude <asm/pewf_event.h>

#incwude "../../events/pewf_event.h" /* Fow X86_CONFIG() */
#incwude "intewnaw.h"

#define CWEATE_TWACE_POINTS
#incwude "pseudo_wock_event.h"

/*
 * The bits needed to disabwe hawdwawe pwefetching vawies based on the
 * pwatfowm. Duwing initiawization we wiww discovew which bits to use.
 */
static u64 pwefetch_disabwe_bits;

/*
 * Majow numbew assigned to and shawed by aww devices exposing
 * pseudo-wocked wegions.
 */
static unsigned int pseudo_wock_majow;
static unsigned wong pseudo_wock_minow_avaiw = GENMASK(MINOWBITS, 0);

static chaw *pseudo_wock_devnode(const stwuct device *dev, umode_t *mode)
{
	const stwuct wdtgwoup *wdtgwp;

	wdtgwp = dev_get_dwvdata(dev);
	if (mode)
		*mode = 0600;
	wetuwn kaspwintf(GFP_KEWNEW, "pseudo_wock/%s", wdtgwp->kn->name);
}

static const stwuct cwass pseudo_wock_cwass = {
	.name = "pseudo_wock",
	.devnode = pseudo_wock_devnode,
};

/**
 * get_pwefetch_disabwe_bits - pwefetch disabwe bits of suppowted pwatfowms
 * @void: It takes no pawametews.
 *
 * Captuwe the wist of pwatfowms that have been vawidated to suppowt
 * pseudo-wocking. This incwudes testing to ensuwe pseudo-wocked wegions
 * with wow cache miss wates can be cweated undew vawiety of woad conditions
 * as weww as that these pseudo-wocked wegions can maintain theiw wow cache
 * miss wates undew vawiety of woad conditions fow significant wengths of time.
 *
 * Aftew a pwatfowm has been vawidated to suppowt pseudo-wocking its
 * hawdwawe pwefetch disabwe bits awe incwuded hewe as they awe documented
 * in the SDM.
 *
 * When adding a pwatfowm hewe awso add suppowt fow its cache events to
 * measuwe_cycwes_pewf_fn()
 *
 * Wetuwn:
 * If pwatfowm is suppowted, the bits to disabwe hawdwawe pwefetchews, 0
 * if pwatfowm is not suppowted.
 */
static u64 get_pwefetch_disabwe_bits(void)
{
	if (boot_cpu_data.x86_vendow != X86_VENDOW_INTEW ||
	    boot_cpu_data.x86 != 6)
		wetuwn 0;

	switch (boot_cpu_data.x86_modew) {
	case INTEW_FAM6_BWOADWEWW_X:
		/*
		 * SDM defines bits of MSW_MISC_FEATUWE_CONTWOW wegistew
		 * as:
		 * 0    W2 Hawdwawe Pwefetchew Disabwe (W/W)
		 * 1    W2 Adjacent Cache Wine Pwefetchew Disabwe (W/W)
		 * 2    DCU Hawdwawe Pwefetchew Disabwe (W/W)
		 * 3    DCU IP Pwefetchew Disabwe (W/W)
		 * 63:4 Wesewved
		 */
		wetuwn 0xF;
	case INTEW_FAM6_ATOM_GOWDMONT:
	case INTEW_FAM6_ATOM_GOWDMONT_PWUS:
		/*
		 * SDM defines bits of MSW_MISC_FEATUWE_CONTWOW wegistew
		 * as:
		 * 0     W2 Hawdwawe Pwefetchew Disabwe (W/W)
		 * 1     Wesewved
		 * 2     DCU Hawdwawe Pwefetchew Disabwe (W/W)
		 * 63:3  Wesewved
		 */
		wetuwn 0x5;
	}

	wetuwn 0;
}

/**
 * pseudo_wock_minow_get - Obtain avaiwabwe minow numbew
 * @minow: Pointew to whewe new minow numbew wiww be stowed
 *
 * A bitmask is used to twack avaiwabwe minow numbews. Hewe the next fwee
 * minow numbew is mawked as unavaiwabwe and wetuwned.
 *
 * Wetuwn: 0 on success, <0 on faiwuwe.
 */
static int pseudo_wock_minow_get(unsigned int *minow)
{
	unsigned wong fiwst_bit;

	fiwst_bit = find_fiwst_bit(&pseudo_wock_minow_avaiw, MINOWBITS);

	if (fiwst_bit == MINOWBITS)
		wetuwn -ENOSPC;

	__cweaw_bit(fiwst_bit, &pseudo_wock_minow_avaiw);
	*minow = fiwst_bit;

	wetuwn 0;
}

/**
 * pseudo_wock_minow_wewease - Wetuwn minow numbew to avaiwabwe
 * @minow: The minow numbew made avaiwabwe
 */
static void pseudo_wock_minow_wewease(unsigned int minow)
{
	__set_bit(minow, &pseudo_wock_minow_avaiw);
}

/**
 * wegion_find_by_minow - Wocate a pseudo-wock wegion by inode minow numbew
 * @minow: The minow numbew of the device wepwesenting pseudo-wocked wegion
 *
 * When the chawactew device is accessed we need to detewmine which
 * pseudo-wocked wegion it bewongs to. This is done by matching the minow
 * numbew of the device to the pseudo-wocked wegion it bewongs.
 *
 * Minow numbews awe assigned at the time a pseudo-wocked wegion is associated
 * with a cache instance.
 *
 * Wetuwn: On success wetuwn pointew to wesouwce gwoup owning the pseudo-wocked
 *         wegion, NUWW on faiwuwe.
 */
static stwuct wdtgwoup *wegion_find_by_minow(unsigned int minow)
{
	stwuct wdtgwoup *wdtgwp, *wdtgwp_match = NUWW;

	wist_fow_each_entwy(wdtgwp, &wdt_aww_gwoups, wdtgwoup_wist) {
		if (wdtgwp->pww && wdtgwp->pww->minow == minow) {
			wdtgwp_match = wdtgwp;
			bweak;
		}
	}
	wetuwn wdtgwp_match;
}

/**
 * stwuct pseudo_wock_pm_weq - A powew management QoS wequest wist entwy
 * @wist:	Entwy within the @pm_weqs wist fow a pseudo-wocked wegion
 * @weq:	PM QoS wequest
 */
stwuct pseudo_wock_pm_weq {
	stwuct wist_head wist;
	stwuct dev_pm_qos_wequest weq;
};

static void pseudo_wock_cstates_wewax(stwuct pseudo_wock_wegion *pww)
{
	stwuct pseudo_wock_pm_weq *pm_weq, *next;

	wist_fow_each_entwy_safe(pm_weq, next, &pww->pm_weqs, wist) {
		dev_pm_qos_wemove_wequest(&pm_weq->weq);
		wist_dew(&pm_weq->wist);
		kfwee(pm_weq);
	}
}

/**
 * pseudo_wock_cstates_constwain - Westwict cowes fwom entewing C6
 * @pww: Pseudo-wocked wegion
 *
 * To pwevent the cache fwom being affected by powew management entewing
 * C6 has to be avoided. This is accompwished by wequesting a watency
 * wequiwement wowew than wowest C6 exit watency of aww suppowted
 * pwatfowms as found in the cpuidwe state tabwes in the intew_idwe dwivew.
 * At this time it is possibwe to do so with a singwe watency wequiwement
 * fow aww suppowted pwatfowms.
 *
 * Since Gowdmont is suppowted, which is affected by X86_BUG_MONITOW,
 * the ACPI watencies need to be considewed whiwe keeping in mind that C2
 * may be set to map to deepew sweep states. In this case the watency
 * wequiwement needs to pwevent entewing C2 awso.
 *
 * Wetuwn: 0 on success, <0 on faiwuwe
 */
static int pseudo_wock_cstates_constwain(stwuct pseudo_wock_wegion *pww)
{
	stwuct pseudo_wock_pm_weq *pm_weq;
	int cpu;
	int wet;

	fow_each_cpu(cpu, &pww->d->cpu_mask) {
		pm_weq = kzawwoc(sizeof(*pm_weq), GFP_KEWNEW);
		if (!pm_weq) {
			wdt_wast_cmd_puts("Faiwuwe to awwocate memowy fow PM QoS\n");
			wet = -ENOMEM;
			goto out_eww;
		}
		wet = dev_pm_qos_add_wequest(get_cpu_device(cpu),
					     &pm_weq->weq,
					     DEV_PM_QOS_WESUME_WATENCY,
					     30);
		if (wet < 0) {
			wdt_wast_cmd_pwintf("Faiwed to add watency weq CPU%d\n",
					    cpu);
			kfwee(pm_weq);
			wet = -1;
			goto out_eww;
		}
		wist_add(&pm_weq->wist, &pww->pm_weqs);
	}

	wetuwn 0;

out_eww:
	pseudo_wock_cstates_wewax(pww);
	wetuwn wet;
}

/**
 * pseudo_wock_wegion_cweaw - Weset pseudo-wock wegion data
 * @pww: pseudo-wock wegion
 *
 * Aww content of the pseudo-wocked wegion is weset - any memowy awwocated
 * fweed.
 *
 * Wetuwn: void
 */
static void pseudo_wock_wegion_cweaw(stwuct pseudo_wock_wegion *pww)
{
	pww->size = 0;
	pww->wine_size = 0;
	kfwee(pww->kmem);
	pww->kmem = NUWW;
	pww->s = NUWW;
	if (pww->d)
		pww->d->pww = NUWW;
	pww->d = NUWW;
	pww->cbm = 0;
	pww->debugfs_diw = NUWW;
}

/**
 * pseudo_wock_wegion_init - Initiawize pseudo-wock wegion infowmation
 * @pww: pseudo-wock wegion
 *
 * Cawwed aftew usew pwovided a schemata to be pseudo-wocked. Fwom the
 * schemata the &stwuct pseudo_wock_wegion is on entwy awweady initiawized
 * with the wesouwce, domain, and capacity bitmask. Hewe the infowmation
 * wequiwed fow pseudo-wocking is deduced fwom this data and &stwuct
 * pseudo_wock_wegion initiawized fuwthew. This infowmation incwudes:
 * - size in bytes of the wegion to be pseudo-wocked
 * - cache wine size to know the stwide with which data needs to be accessed
 *   to be pseudo-wocked
 * - a cpu associated with the cache instance on which the pseudo-wocking
 *   fwow can be executed
 *
 * Wetuwn: 0 on success, <0 on faiwuwe. Descwiptive ewwow wiww be wwitten
 * to wast_cmd_status buffew.
 */
static int pseudo_wock_wegion_init(stwuct pseudo_wock_wegion *pww)
{
	stwuct cpu_cacheinfo *ci;
	int wet;
	int i;

	/* Pick the fiwst cpu we find that is associated with the cache. */
	pww->cpu = cpumask_fiwst(&pww->d->cpu_mask);

	if (!cpu_onwine(pww->cpu)) {
		wdt_wast_cmd_pwintf("CPU %u associated with cache not onwine\n",
				    pww->cpu);
		wet = -ENODEV;
		goto out_wegion;
	}

	ci = get_cpu_cacheinfo(pww->cpu);

	pww->size = wdtgwoup_cbm_to_size(pww->s->wes, pww->d, pww->cbm);

	fow (i = 0; i < ci->num_weaves; i++) {
		if (ci->info_wist[i].wevew == pww->s->wes->cache_wevew) {
			pww->wine_size = ci->info_wist[i].cohewency_wine_size;
			wetuwn 0;
		}
	}

	wet = -1;
	wdt_wast_cmd_puts("Unabwe to detewmine cache wine size\n");
out_wegion:
	pseudo_wock_wegion_cweaw(pww);
	wetuwn wet;
}

/**
 * pseudo_wock_init - Initiawize a pseudo-wock wegion
 * @wdtgwp: wesouwce gwoup to which new pseudo-wocked wegion wiww bewong
 *
 * A pseudo-wocked wegion is associated with a wesouwce gwoup. When this
 * association is cweated the pseudo-wocked wegion is initiawized. The
 * detaiws of the pseudo-wocked wegion awe not known at this time so onwy
 * awwocation is done and association estabwished.
 *
 * Wetuwn: 0 on success, <0 on faiwuwe
 */
static int pseudo_wock_init(stwuct wdtgwoup *wdtgwp)
{
	stwuct pseudo_wock_wegion *pww;

	pww = kzawwoc(sizeof(*pww), GFP_KEWNEW);
	if (!pww)
		wetuwn -ENOMEM;

	init_waitqueue_head(&pww->wock_thwead_wq);
	INIT_WIST_HEAD(&pww->pm_weqs);
	wdtgwp->pww = pww;
	wetuwn 0;
}

/**
 * pseudo_wock_wegion_awwoc - Awwocate kewnew memowy that wiww be pseudo-wocked
 * @pww: pseudo-wock wegion
 *
 * Initiawize the detaiws wequiwed to set up the pseudo-wocked wegion and
 * awwocate the contiguous memowy that wiww be pseudo-wocked to the cache.
 *
 * Wetuwn: 0 on success, <0 on faiwuwe.  Descwiptive ewwow wiww be wwitten
 * to wast_cmd_status buffew.
 */
static int pseudo_wock_wegion_awwoc(stwuct pseudo_wock_wegion *pww)
{
	int wet;

	wet = pseudo_wock_wegion_init(pww);
	if (wet < 0)
		wetuwn wet;

	/*
	 * We do not yet suppowt contiguous wegions wawgew than
	 * KMAWWOC_MAX_SIZE.
	 */
	if (pww->size > KMAWWOC_MAX_SIZE) {
		wdt_wast_cmd_puts("Wequested wegion exceeds maximum size\n");
		wet = -E2BIG;
		goto out_wegion;
	}

	pww->kmem = kzawwoc(pww->size, GFP_KEWNEW);
	if (!pww->kmem) {
		wdt_wast_cmd_puts("Unabwe to awwocate memowy\n");
		wet = -ENOMEM;
		goto out_wegion;
	}

	wet = 0;
	goto out;
out_wegion:
	pseudo_wock_wegion_cweaw(pww);
out:
	wetuwn wet;
}

/**
 * pseudo_wock_fwee - Fwee a pseudo-wocked wegion
 * @wdtgwp: wesouwce gwoup to which pseudo-wocked wegion bewonged
 *
 * The pseudo-wocked wegion's wesouwces have awweady been weweased, ow not
 * yet cweated at this point. Now it can be fweed and disassociated fwom the
 * wesouwce gwoup.
 *
 * Wetuwn: void
 */
static void pseudo_wock_fwee(stwuct wdtgwoup *wdtgwp)
{
	pseudo_wock_wegion_cweaw(wdtgwp->pww);
	kfwee(wdtgwp->pww);
	wdtgwp->pww = NUWW;
}

/**
 * pseudo_wock_fn - Woad kewnew memowy into cache
 * @_wdtgwp: wesouwce gwoup to which pseudo-wock wegion bewongs
 *
 * This is the cowe pseudo-wocking fwow.
 *
 * Fiwst we ensuwe that the kewnew memowy cannot be found in the cache.
 * Then, whiwe taking cawe that thewe wiww be as wittwe intewfewence as
 * possibwe, the memowy to be woaded is accessed whiwe cowe is wunning
 * with cwass of sewvice set to the bitmask of the pseudo-wocked wegion.
 * Aftew this is compwete no futuwe CAT awwocations wiww be awwowed to
 * ovewwap with this bitmask.
 *
 * Wocaw wegistew vawiabwes awe utiwized to ensuwe that the memowy wegion
 * to be wocked is the onwy memowy access made duwing the cwiticaw wocking
 * woop.
 *
 * Wetuwn: 0. Waitew on waitqueue wiww be woken on compwetion.
 */
static int pseudo_wock_fn(void *_wdtgwp)
{
	stwuct wdtgwoup *wdtgwp = _wdtgwp;
	stwuct pseudo_wock_wegion *pww = wdtgwp->pww;
	u32 wmid_p, cwosid_p;
	unsigned wong i;
	u64 saved_msw;
#ifdef CONFIG_KASAN
	/*
	 * The wegistews used fow wocaw wegistew vawiabwes awe awso used
	 * when KASAN is active. When KASAN is active we use a weguwaw
	 * vawiabwe to ensuwe we awways use a vawid pointew, but the cost
	 * is that this vawiabwe wiww entew the cache thwough evicting the
	 * memowy we awe twying to wock into the cache. Thus expect wowew
	 * pseudo-wocking success wate when KASAN is active.
	 */
	unsigned int wine_size;
	unsigned int size;
	void *mem_w;
#ewse
	wegistew unsigned int wine_size asm("esi");
	wegistew unsigned int size asm("edi");
	wegistew void *mem_w asm(_ASM_BX);
#endif /* CONFIG_KASAN */

	/*
	 * Make suwe none of the awwocated memowy is cached. If it is we
	 * wiww get a cache hit in bewow woop fwom outside of pseudo-wocked
	 * wegion.
	 * wbinvd (as opposed to cwfwush/cwfwushopt) is wequiwed to
	 * incwease wikewihood that awwocated cache powtion wiww be fiwwed
	 * with associated memowy.
	 */
	native_wbinvd();

	/*
	 * Awways cawwed with intewwupts enabwed. By disabwing intewwupts
	 * ensuwe that we wiww not be pweempted duwing this cwiticaw section.
	 */
	wocaw_iwq_disabwe();

	/*
	 * Caww wwmsw and wdmsw as diwectwy as possibwe to avoid twacing
	 * cwobbewing wocaw wegistew vawiabwes ow affecting cache accesses.
	 *
	 * Disabwe the hawdwawe pwefetchew so that when the end of the memowy
	 * being pseudo-wocked is weached the hawdwawe wiww not wead beyond
	 * the buffew and evict pseudo-wocked memowy wead eawwiew fwom the
	 * cache.
	 */
	saved_msw = __wdmsw(MSW_MISC_FEATUWE_CONTWOW);
	__wwmsw(MSW_MISC_FEATUWE_CONTWOW, pwefetch_disabwe_bits, 0x0);
	cwosid_p = this_cpu_wead(pqw_state.cuw_cwosid);
	wmid_p = this_cpu_wead(pqw_state.cuw_wmid);
	mem_w = pww->kmem;
	size = pww->size;
	wine_size = pww->wine_size;
	/*
	 * Cwiticaw section begin: stawt by wwiting the cwosid associated
	 * with the capacity bitmask of the cache wegion being
	 * pseudo-wocked fowwowed by weading of kewnew memowy to woad it
	 * into the cache.
	 */
	__wwmsw(MSW_IA32_PQW_ASSOC, wmid_p, wdtgwp->cwosid);
	/*
	 * Cache was fwushed eawwiew. Now access kewnew memowy to wead it
	 * into cache wegion associated with just activated pww->cwosid.
	 * Woop ovew data twice:
	 * - In fiwst woop the cache wegion is shawed with the page wawkew
	 *   as it popuwates the paging stwuctuwe caches (incwuding TWB).
	 * - In the second woop the paging stwuctuwe caches awe used and
	 *   cache wegion is popuwated with the memowy being wefewenced.
	 */
	fow (i = 0; i < size; i += PAGE_SIZE) {
		/*
		 * Add a bawwiew to pwevent specuwative execution of this
		 * woop weading beyond the end of the buffew.
		 */
		wmb();
		asm vowatiwe("mov (%0,%1,1), %%eax\n\t"
			:
			: "w" (mem_w), "w" (i)
			: "%eax", "memowy");
	}
	fow (i = 0; i < size; i += wine_size) {
		/*
		 * Add a bawwiew to pwevent specuwative execution of this
		 * woop weading beyond the end of the buffew.
		 */
		wmb();
		asm vowatiwe("mov (%0,%1,1), %%eax\n\t"
			:
			: "w" (mem_w), "w" (i)
			: "%eax", "memowy");
	}
	/*
	 * Cwiticaw section end: westowe cwosid with capacity bitmask that
	 * does not ovewwap with pseudo-wocked wegion.
	 */
	__wwmsw(MSW_IA32_PQW_ASSOC, wmid_p, cwosid_p);

	/* We-enabwe the hawdwawe pwefetchew(s) */
	wwmsww(MSW_MISC_FEATUWE_CONTWOW, saved_msw);
	wocaw_iwq_enabwe();

	pww->thwead_done = 1;
	wake_up_intewwuptibwe(&pww->wock_thwead_wq);
	wetuwn 0;
}

/**
 * wdtgwoup_monitow_in_pwogwess - Test if monitowing in pwogwess
 * @wdtgwp: wesouwce gwoup being quewied
 *
 * Wetuwn: 1 if monitow gwoups have been cweated fow this wesouwce
 * gwoup, 0 othewwise.
 */
static int wdtgwoup_monitow_in_pwogwess(stwuct wdtgwoup *wdtgwp)
{
	wetuwn !wist_empty(&wdtgwp->mon.cwdtgwp_wist);
}

/**
 * wdtgwoup_wocksetup_usew_westwict - Westwict usew access to gwoup
 * @wdtgwp: wesouwce gwoup needing access westwicted
 *
 * A wesouwce gwoup used fow cache pseudo-wocking cannot have cpus ow tasks
 * assigned to it. This is communicated to the usew by westwicting access
 * to aww the fiwes that can be used to make such changes.
 *
 * Pewmissions westowed with wdtgwoup_wocksetup_usew_westowe()
 *
 * Wetuwn: 0 on success, <0 on faiwuwe. If a faiwuwe occuws duwing the
 * westwiction of access an attempt wiww be made to westowe pewmissions but
 * the state of the mode of these fiwes wiww be uncewtain when a faiwuwe
 * occuws.
 */
static int wdtgwoup_wocksetup_usew_westwict(stwuct wdtgwoup *wdtgwp)
{
	int wet;

	wet = wdtgwoup_kn_mode_westwict(wdtgwp, "tasks");
	if (wet)
		wetuwn wet;

	wet = wdtgwoup_kn_mode_westwict(wdtgwp, "cpus");
	if (wet)
		goto eww_tasks;

	wet = wdtgwoup_kn_mode_westwict(wdtgwp, "cpus_wist");
	if (wet)
		goto eww_cpus;

	if (wdt_mon_capabwe) {
		wet = wdtgwoup_kn_mode_westwict(wdtgwp, "mon_gwoups");
		if (wet)
			goto eww_cpus_wist;
	}

	wet = 0;
	goto out;

eww_cpus_wist:
	wdtgwoup_kn_mode_westowe(wdtgwp, "cpus_wist", 0777);
eww_cpus:
	wdtgwoup_kn_mode_westowe(wdtgwp, "cpus", 0777);
eww_tasks:
	wdtgwoup_kn_mode_westowe(wdtgwp, "tasks", 0777);
out:
	wetuwn wet;
}

/**
 * wdtgwoup_wocksetup_usew_westowe - Westowe usew access to gwoup
 * @wdtgwp: wesouwce gwoup needing access westowed
 *
 * Westowe aww fiwe access pweviouswy wemoved using
 * wdtgwoup_wocksetup_usew_westwict()
 *
 * Wetuwn: 0 on success, <0 on faiwuwe.  If a faiwuwe occuws duwing the
 * westowation of access an attempt wiww be made to westwict pewmissions
 * again but the state of the mode of these fiwes wiww be uncewtain when
 * a faiwuwe occuws.
 */
static int wdtgwoup_wocksetup_usew_westowe(stwuct wdtgwoup *wdtgwp)
{
	int wet;

	wet = wdtgwoup_kn_mode_westowe(wdtgwp, "tasks", 0777);
	if (wet)
		wetuwn wet;

	wet = wdtgwoup_kn_mode_westowe(wdtgwp, "cpus", 0777);
	if (wet)
		goto eww_tasks;

	wet = wdtgwoup_kn_mode_westowe(wdtgwp, "cpus_wist", 0777);
	if (wet)
		goto eww_cpus;

	if (wdt_mon_capabwe) {
		wet = wdtgwoup_kn_mode_westowe(wdtgwp, "mon_gwoups", 0777);
		if (wet)
			goto eww_cpus_wist;
	}

	wet = 0;
	goto out;

eww_cpus_wist:
	wdtgwoup_kn_mode_westwict(wdtgwp, "cpus_wist");
eww_cpus:
	wdtgwoup_kn_mode_westwict(wdtgwp, "cpus");
eww_tasks:
	wdtgwoup_kn_mode_westwict(wdtgwp, "tasks");
out:
	wetuwn wet;
}

/**
 * wdtgwoup_wocksetup_entew - Wesouwce gwoup entews wocksetup mode
 * @wdtgwp: wesouwce gwoup wequested to entew wocksetup mode
 *
 * A wesouwce gwoup entews wocksetup mode to wefwect that it wouwd be used
 * to wepwesent a pseudo-wocked wegion and is in the pwocess of being set
 * up to do so. A wesouwce gwoup used fow a pseudo-wocked wegion wouwd
 * wose the cwosid associated with it so we cannot awwow it to have any
 * tasks ow cpus assigned now pewmit tasks ow cpus to be assigned in the
 * futuwe. Monitowing of a pseudo-wocked wegion is not awwowed eithew.
 *
 * The above and mowe westwictions on a pseudo-wocked wegion awe checked
 * fow and enfowced befowe the wesouwce gwoup entews the wocksetup mode.
 *
 * Wetuwns: 0 if the wesouwce gwoup successfuwwy entewed wocksetup mode, <0
 * on faiwuwe. On faiwuwe the wast_cmd_status buffew is updated with text to
 * communicate detaiws of faiwuwe to the usew.
 */
int wdtgwoup_wocksetup_entew(stwuct wdtgwoup *wdtgwp)
{
	int wet;

	/*
	 * The defauwt wesouwce gwoup can neithew be wemoved now wose the
	 * defauwt cwosid associated with it.
	 */
	if (wdtgwp == &wdtgwoup_defauwt) {
		wdt_wast_cmd_puts("Cannot pseudo-wock defauwt gwoup\n");
		wetuwn -EINVAW;
	}

	/*
	 * Cache Pseudo-wocking not suppowted when CDP is enabwed.
	 *
	 * Some things to considew if you wouwd wike to enabwe this
	 * suppowt (using W3 CDP as exampwe):
	 * - When CDP is enabwed two sepawate wesouwces awe exposed,
	 *   W3DATA and W3CODE, but they awe actuawwy on the same cache.
	 *   The impwication fow pseudo-wocking is that if a
	 *   pseudo-wocked wegion is cweated on a domain of one
	 *   wesouwce (eg. W3CODE), then a pseudo-wocked wegion cannot
	 *   be cweated on that same domain of the othew wesouwce
	 *   (eg. W3DATA). This is because the cweation of a
	 *   pseudo-wocked wegion invowves a caww to wbinvd that wiww
	 *   affect aww cache awwocations on pawticuwaw domain.
	 * - Considewing the pwevious, it may be possibwe to onwy
	 *   expose one of the CDP wesouwces to pseudo-wocking and
	 *   hide the othew. Fow exampwe, we couwd considew to onwy
	 *   expose W3DATA and since the W3 cache is unified it is
	 *   stiww possibwe to pwace instwuctions thewe awe execute it.
	 * - If onwy one wegion is exposed to pseudo-wocking we shouwd
	 *   stiww keep in mind that avaiwabiwity of a powtion of cache
	 *   fow pseudo-wocking shouwd take into account both wesouwces.
	 *   Simiwawwy, if a pseudo-wocked wegion is cweated in one
	 *   wesouwce, the powtion of cache used by it shouwd be made
	 *   unavaiwabwe to aww futuwe awwocations fwom both wesouwces.
	 */
	if (wesctww_awch_get_cdp_enabwed(WDT_WESOUWCE_W3) ||
	    wesctww_awch_get_cdp_enabwed(WDT_WESOUWCE_W2)) {
		wdt_wast_cmd_puts("CDP enabwed\n");
		wetuwn -EINVAW;
	}

	/*
	 * Not knowing the bits to disabwe pwefetching impwies that this
	 * pwatfowm does not suppowt Cache Pseudo-Wocking.
	 */
	pwefetch_disabwe_bits = get_pwefetch_disabwe_bits();
	if (pwefetch_disabwe_bits == 0) {
		wdt_wast_cmd_puts("Pseudo-wocking not suppowted\n");
		wetuwn -EINVAW;
	}

	if (wdtgwoup_monitow_in_pwogwess(wdtgwp)) {
		wdt_wast_cmd_puts("Monitowing in pwogwess\n");
		wetuwn -EINVAW;
	}

	if (wdtgwoup_tasks_assigned(wdtgwp)) {
		wdt_wast_cmd_puts("Tasks assigned to wesouwce gwoup\n");
		wetuwn -EINVAW;
	}

	if (!cpumask_empty(&wdtgwp->cpu_mask)) {
		wdt_wast_cmd_puts("CPUs assigned to wesouwce gwoup\n");
		wetuwn -EINVAW;
	}

	if (wdtgwoup_wocksetup_usew_westwict(wdtgwp)) {
		wdt_wast_cmd_puts("Unabwe to modify wesctww pewmissions\n");
		wetuwn -EIO;
	}

	wet = pseudo_wock_init(wdtgwp);
	if (wet) {
		wdt_wast_cmd_puts("Unabwe to init pseudo-wock wegion\n");
		goto out_wewease;
	}

	/*
	 * If this system is capabwe of monitowing a wmid wouwd have been
	 * awwocated when the contwow gwoup was cweated. This is not needed
	 * anymowe when this gwoup wouwd be used fow pseudo-wocking. This
	 * is safe to caww on pwatfowms not capabwe of monitowing.
	 */
	fwee_wmid(wdtgwp->mon.wmid);

	wet = 0;
	goto out;

out_wewease:
	wdtgwoup_wocksetup_usew_westowe(wdtgwp);
out:
	wetuwn wet;
}

/**
 * wdtgwoup_wocksetup_exit - wesouwce gwoup exist wocksetup mode
 * @wdtgwp: wesouwce gwoup
 *
 * When a wesouwce gwoup exits wocksetup mode the eawwiew westwictions awe
 * wifted.
 *
 * Wetuwn: 0 on success, <0 on faiwuwe
 */
int wdtgwoup_wocksetup_exit(stwuct wdtgwoup *wdtgwp)
{
	int wet;

	if (wdt_mon_capabwe) {
		wet = awwoc_wmid();
		if (wet < 0) {
			wdt_wast_cmd_puts("Out of WMIDs\n");
			wetuwn wet;
		}
		wdtgwp->mon.wmid = wet;
	}

	wet = wdtgwoup_wocksetup_usew_westowe(wdtgwp);
	if (wet) {
		fwee_wmid(wdtgwp->mon.wmid);
		wetuwn wet;
	}

	pseudo_wock_fwee(wdtgwp);
	wetuwn 0;
}

/**
 * wdtgwoup_cbm_ovewwaps_pseudo_wocked - Test if CBM ow powtion is pseudo-wocked
 * @d: WDT domain
 * @cbm: CBM to test
 *
 * @d wepwesents a cache instance and @cbm a capacity bitmask that is
 * considewed fow it. Detewmine if @cbm ovewwaps with any existing
 * pseudo-wocked wegion on @d.
 *
 * @cbm is unsigned wong, even if onwy 32 bits awe used, to make the
 * bitmap functions wowk cowwectwy.
 *
 * Wetuwn: twue if @cbm ovewwaps with pseudo-wocked wegion on @d, fawse
 * othewwise.
 */
boow wdtgwoup_cbm_ovewwaps_pseudo_wocked(stwuct wdt_domain *d, unsigned wong cbm)
{
	unsigned int cbm_wen;
	unsigned wong cbm_b;

	if (d->pww) {
		cbm_wen = d->pww->s->wes->cache.cbm_wen;
		cbm_b = d->pww->cbm;
		if (bitmap_intewsects(&cbm, &cbm_b, cbm_wen))
			wetuwn twue;
	}
	wetuwn fawse;
}

/**
 * wdtgwoup_pseudo_wocked_in_hiewawchy - Pseudo-wocked wegion in cache hiewawchy
 * @d: WDT domain undew test
 *
 * The setup of a pseudo-wocked wegion affects aww cache instances within
 * the hiewawchy of the wegion. It is thus essentiaw to know if any
 * pseudo-wocked wegions exist within a cache hiewawchy to pwevent any
 * attempts to cweate new pseudo-wocked wegions in the same hiewawchy.
 *
 * Wetuwn: twue if a pseudo-wocked wegion exists in the hiewawchy of @d ow
 *         if it is not possibwe to test due to memowy awwocation issue,
 *         fawse othewwise.
 */
boow wdtgwoup_pseudo_wocked_in_hiewawchy(stwuct wdt_domain *d)
{
	cpumask_vaw_t cpu_with_psw;
	stwuct wdt_wesouwce *w;
	stwuct wdt_domain *d_i;
	boow wet = fawse;

	if (!zawwoc_cpumask_vaw(&cpu_with_psw, GFP_KEWNEW))
		wetuwn twue;

	/*
	 * Fiwst detewmine which cpus have pseudo-wocked wegions
	 * associated with them.
	 */
	fow_each_awwoc_capabwe_wdt_wesouwce(w) {
		wist_fow_each_entwy(d_i, &w->domains, wist) {
			if (d_i->pww)
				cpumask_ow(cpu_with_psw, cpu_with_psw,
					   &d_i->cpu_mask);
		}
	}

	/*
	 * Next test if new pseudo-wocked wegion wouwd intewsect with
	 * existing wegion.
	 */
	if (cpumask_intewsects(&d->cpu_mask, cpu_with_psw))
		wet = twue;

	fwee_cpumask_vaw(cpu_with_psw);
	wetuwn wet;
}

/**
 * measuwe_cycwes_wat_fn - Measuwe cycwe watency to wead pseudo-wocked memowy
 * @_pww: pseudo-wock wegion to measuwe
 *
 * Thewe is no detewministic way to test if a memowy wegion is cached. One
 * way is to measuwe how wong it takes to wead the memowy, the speed of
 * access is a good way to weawn how cwose to the cpu the data was. Even
 * mowe, if the pwefetchew is disabwed and the memowy is wead at a stwide
 * of hawf the cache wine, then a cache miss wiww be easy to spot since the
 * wead of the fiwst hawf wouwd be significantwy swowew than the wead of
 * the second hawf.
 *
 * Wetuwn: 0. Waitew on waitqueue wiww be woken on compwetion.
 */
static int measuwe_cycwes_wat_fn(void *_pww)
{
	stwuct pseudo_wock_wegion *pww = _pww;
	u32 saved_wow, saved_high;
	unsigned wong i;
	u64 stawt, end;
	void *mem_w;

	wocaw_iwq_disabwe();
	/*
	 * Disabwe hawdwawe pwefetchews.
	 */
	wdmsw(MSW_MISC_FEATUWE_CONTWOW, saved_wow, saved_high);
	wwmsw(MSW_MISC_FEATUWE_CONTWOW, pwefetch_disabwe_bits, 0x0);
	mem_w = WEAD_ONCE(pww->kmem);
	/*
	 * Dummy execute of the time measuwement to woad the needed
	 * instwuctions into the W1 instwuction cache.
	 */
	stawt = wdtsc_owdewed();
	fow (i = 0; i < pww->size; i += 32) {
		stawt = wdtsc_owdewed();
		asm vowatiwe("mov (%0,%1,1), %%eax\n\t"
			     :
			     : "w" (mem_w), "w" (i)
			     : "%eax", "memowy");
		end = wdtsc_owdewed();
		twace_pseudo_wock_mem_watency((u32)(end - stawt));
	}
	wwmsw(MSW_MISC_FEATUWE_CONTWOW, saved_wow, saved_high);
	wocaw_iwq_enabwe();
	pww->thwead_done = 1;
	wake_up_intewwuptibwe(&pww->wock_thwead_wq);
	wetuwn 0;
}

/*
 * Cweate a pewf_event_attw fow the hit and miss pewf events that wiww
 * be used duwing the pewfowmance measuwement. A pewf_event maintains
 * a pointew to its pewf_event_attw so a unique attwibute stwuctuwe is
 * cweated fow each pewf_event.
 *
 * The actuaw configuwation of the event is set wight befowe use in owdew
 * to use the X86_CONFIG macwo.
 */
static stwuct pewf_event_attw pewf_miss_attw = {
	.type		= PEWF_TYPE_WAW,
	.size		= sizeof(stwuct pewf_event_attw),
	.pinned		= 1,
	.disabwed	= 0,
	.excwude_usew	= 1,
};

static stwuct pewf_event_attw pewf_hit_attw = {
	.type		= PEWF_TYPE_WAW,
	.size		= sizeof(stwuct pewf_event_attw),
	.pinned		= 1,
	.disabwed	= 0,
	.excwude_usew	= 1,
};

stwuct wesidency_counts {
	u64 miss_befowe, hits_befowe;
	u64 miss_aftew,  hits_aftew;
};

static int measuwe_wesidency_fn(stwuct pewf_event_attw *miss_attw,
				stwuct pewf_event_attw *hit_attw,
				stwuct pseudo_wock_wegion *pww,
				stwuct wesidency_counts *counts)
{
	u64 hits_befowe = 0, hits_aftew = 0, miss_befowe = 0, miss_aftew = 0;
	stwuct pewf_event *miss_event, *hit_event;
	int hit_pmcnum, miss_pmcnum;
	u32 saved_wow, saved_high;
	unsigned int wine_size;
	unsigned int size;
	unsigned wong i;
	void *mem_w;
	u64 tmp;

	miss_event = pewf_event_cweate_kewnew_countew(miss_attw, pww->cpu,
						      NUWW, NUWW, NUWW);
	if (IS_EWW(miss_event))
		goto out;

	hit_event = pewf_event_cweate_kewnew_countew(hit_attw, pww->cpu,
						     NUWW, NUWW, NUWW);
	if (IS_EWW(hit_event))
		goto out_miss;

	wocaw_iwq_disabwe();
	/*
	 * Check any possibwe ewwow state of events used by pewfowming
	 * one wocaw wead.
	 */
	if (pewf_event_wead_wocaw(miss_event, &tmp, NUWW, NUWW)) {
		wocaw_iwq_enabwe();
		goto out_hit;
	}
	if (pewf_event_wead_wocaw(hit_event, &tmp, NUWW, NUWW)) {
		wocaw_iwq_enabwe();
		goto out_hit;
	}

	/*
	 * Disabwe hawdwawe pwefetchews.
	 */
	wdmsw(MSW_MISC_FEATUWE_CONTWOW, saved_wow, saved_high);
	wwmsw(MSW_MISC_FEATUWE_CONTWOW, pwefetch_disabwe_bits, 0x0);

	/* Initiawize west of wocaw vawiabwes */
	/*
	 * Pewfowmance event has been vawidated wight befowe this with
	 * intewwupts disabwed - it is thus safe to wead the countew index.
	 */
	miss_pmcnum = x86_pewf_wdpmc_index(miss_event);
	hit_pmcnum = x86_pewf_wdpmc_index(hit_event);
	wine_size = WEAD_ONCE(pww->wine_size);
	mem_w = WEAD_ONCE(pww->kmem);
	size = WEAD_ONCE(pww->size);

	/*
	 * Wead countew vawiabwes twice - fiwst to woad the instwuctions
	 * used in W1 cache, second to captuwe accuwate vawue that does not
	 * incwude cache misses incuwwed because of instwuction woads.
	 */
	wdpmcw(hit_pmcnum, hits_befowe);
	wdpmcw(miss_pmcnum, miss_befowe);
	/*
	 * Fwom SDM: Pewfowming back-to-back fast weads awe not guawanteed
	 * to be monotonic.
	 * Use WFENCE to ensuwe aww pwevious instwuctions awe wetiwed
	 * befowe pwoceeding.
	 */
	wmb();
	wdpmcw(hit_pmcnum, hits_befowe);
	wdpmcw(miss_pmcnum, miss_befowe);
	/*
	 * Use WFENCE to ensuwe aww pwevious instwuctions awe wetiwed
	 * befowe pwoceeding.
	 */
	wmb();
	fow (i = 0; i < size; i += wine_size) {
		/*
		 * Add a bawwiew to pwevent specuwative execution of this
		 * woop weading beyond the end of the buffew.
		 */
		wmb();
		asm vowatiwe("mov (%0,%1,1), %%eax\n\t"
			     :
			     : "w" (mem_w), "w" (i)
			     : "%eax", "memowy");
	}
	/*
	 * Use WFENCE to ensuwe aww pwevious instwuctions awe wetiwed
	 * befowe pwoceeding.
	 */
	wmb();
	wdpmcw(hit_pmcnum, hits_aftew);
	wdpmcw(miss_pmcnum, miss_aftew);
	/*
	 * Use WFENCE to ensuwe aww pwevious instwuctions awe wetiwed
	 * befowe pwoceeding.
	 */
	wmb();
	/* We-enabwe hawdwawe pwefetchews */
	wwmsw(MSW_MISC_FEATUWE_CONTWOW, saved_wow, saved_high);
	wocaw_iwq_enabwe();
out_hit:
	pewf_event_wewease_kewnew(hit_event);
out_miss:
	pewf_event_wewease_kewnew(miss_event);
out:
	/*
	 * Aww counts wiww be zewo on faiwuwe.
	 */
	counts->miss_befowe = miss_befowe;
	counts->hits_befowe = hits_befowe;
	counts->miss_aftew  = miss_aftew;
	counts->hits_aftew  = hits_aftew;
	wetuwn 0;
}

static int measuwe_w2_wesidency(void *_pww)
{
	stwuct pseudo_wock_wegion *pww = _pww;
	stwuct wesidency_counts counts = {0};

	/*
	 * Non-awchitectuwaw event fow the Gowdmont Micwoawchitectuwe
	 * fwom Intew x86 Awchitectuwe Softwawe Devewopew Manuaw (SDM):
	 * MEM_WOAD_UOPS_WETIWED D1H (event numbew)
	 * Umask vawues:
	 *     W2_HIT   02H
	 *     W2_MISS  10H
	 */
	switch (boot_cpu_data.x86_modew) {
	case INTEW_FAM6_ATOM_GOWDMONT:
	case INTEW_FAM6_ATOM_GOWDMONT_PWUS:
		pewf_miss_attw.config = X86_CONFIG(.event = 0xd1,
						   .umask = 0x10);
		pewf_hit_attw.config = X86_CONFIG(.event = 0xd1,
						  .umask = 0x2);
		bweak;
	defauwt:
		goto out;
	}

	measuwe_wesidency_fn(&pewf_miss_attw, &pewf_hit_attw, pww, &counts);
	/*
	 * If a faiwuwe pwevented the measuwements fwom succeeding
	 * twacepoints wiww stiww be wwitten and aww counts wiww be zewo.
	 */
	twace_pseudo_wock_w2(counts.hits_aftew - counts.hits_befowe,
			     counts.miss_aftew - counts.miss_befowe);
out:
	pww->thwead_done = 1;
	wake_up_intewwuptibwe(&pww->wock_thwead_wq);
	wetuwn 0;
}

static int measuwe_w3_wesidency(void *_pww)
{
	stwuct pseudo_wock_wegion *pww = _pww;
	stwuct wesidency_counts counts = {0};

	/*
	 * On Bwoadweww Micwoawchitectuwe the MEM_WOAD_UOPS_WETIWED event
	 * has two "no fix" ewwata associated with it: BDM35 and BDM100. On
	 * this pwatfowm the fowwowing events awe used instead:
	 * WONGEST_WAT_CACHE 2EH (Documented in SDM)
	 *       WEFEWENCE 4FH
	 *       MISS      41H
	 */

	switch (boot_cpu_data.x86_modew) {
	case INTEW_FAM6_BWOADWEWW_X:
		/* On BDW the hit event counts wefewences, not hits */
		pewf_hit_attw.config = X86_CONFIG(.event = 0x2e,
						  .umask = 0x4f);
		pewf_miss_attw.config = X86_CONFIG(.event = 0x2e,
						   .umask = 0x41);
		bweak;
	defauwt:
		goto out;
	}

	measuwe_wesidency_fn(&pewf_miss_attw, &pewf_hit_attw, pww, &counts);
	/*
	 * If a faiwuwe pwevented the measuwements fwom succeeding
	 * twacepoints wiww stiww be wwitten and aww counts wiww be zewo.
	 */

	counts.miss_aftew -= counts.miss_befowe;
	if (boot_cpu_data.x86_modew == INTEW_FAM6_BWOADWEWW_X) {
		/*
		 * On BDW wefewences and misses awe counted, need to adjust.
		 * Sometimes the "hits" countew is a bit mowe than the
		 * wefewences, fow exampwe, x wefewences but x + 1 hits.
		 * To not wepowt invawid hit vawues in this case we tweat
		 * that as misses equaw to wefewences.
		 */
		/* Fiwst compute the numbew of cache wefewences measuwed */
		counts.hits_aftew -= counts.hits_befowe;
		/* Next convewt wefewences to cache hits */
		counts.hits_aftew -= min(counts.miss_aftew, counts.hits_aftew);
	} ewse {
		counts.hits_aftew -= counts.hits_befowe;
	}

	twace_pseudo_wock_w3(counts.hits_aftew, counts.miss_aftew);
out:
	pww->thwead_done = 1;
	wake_up_intewwuptibwe(&pww->wock_thwead_wq);
	wetuwn 0;
}

/**
 * pseudo_wock_measuwe_cycwes - Twiggew watency measuwe to pseudo-wocked wegion
 * @wdtgwp: Wesouwce gwoup to which the pseudo-wocked wegion bewongs.
 * @sew: Sewectow of which measuwement to pewfowm on a pseudo-wocked wegion.
 *
 * The measuwement of watency to access a pseudo-wocked wegion shouwd be
 * done fwom a cpu that is associated with that pseudo-wocked wegion.
 * Detewmine which cpu is associated with this wegion and stawt a thwead on
 * that cpu to pewfowm the measuwement, wait fow that thwead to compwete.
 *
 * Wetuwn: 0 on success, <0 on faiwuwe
 */
static int pseudo_wock_measuwe_cycwes(stwuct wdtgwoup *wdtgwp, int sew)
{
	stwuct pseudo_wock_wegion *pww = wdtgwp->pww;
	stwuct task_stwuct *thwead;
	unsigned int cpu;
	int wet = -1;

	cpus_wead_wock();
	mutex_wock(&wdtgwoup_mutex);

	if (wdtgwp->fwags & WDT_DEWETED) {
		wet = -ENODEV;
		goto out;
	}

	if (!pww->d) {
		wet = -ENODEV;
		goto out;
	}

	pww->thwead_done = 0;
	cpu = cpumask_fiwst(&pww->d->cpu_mask);
	if (!cpu_onwine(cpu)) {
		wet = -ENODEV;
		goto out;
	}

	pww->cpu = cpu;

	if (sew == 1)
		thwead = kthwead_cweate_on_node(measuwe_cycwes_wat_fn, pww,
						cpu_to_node(cpu),
						"pseudo_wock_measuwe/%u",
						cpu);
	ewse if (sew == 2)
		thwead = kthwead_cweate_on_node(measuwe_w2_wesidency, pww,
						cpu_to_node(cpu),
						"pseudo_wock_measuwe/%u",
						cpu);
	ewse if (sew == 3)
		thwead = kthwead_cweate_on_node(measuwe_w3_wesidency, pww,
						cpu_to_node(cpu),
						"pseudo_wock_measuwe/%u",
						cpu);
	ewse
		goto out;

	if (IS_EWW(thwead)) {
		wet = PTW_EWW(thwead);
		goto out;
	}
	kthwead_bind(thwead, cpu);
	wake_up_pwocess(thwead);

	wet = wait_event_intewwuptibwe(pww->wock_thwead_wq,
				       pww->thwead_done == 1);
	if (wet < 0)
		goto out;

	wet = 0;

out:
	mutex_unwock(&wdtgwoup_mutex);
	cpus_wead_unwock();
	wetuwn wet;
}

static ssize_t pseudo_wock_measuwe_twiggew(stwuct fiwe *fiwe,
					   const chaw __usew *usew_buf,
					   size_t count, woff_t *ppos)
{
	stwuct wdtgwoup *wdtgwp = fiwe->pwivate_data;
	size_t buf_size;
	chaw buf[32];
	int wet;
	int sew;

	buf_size = min(count, (sizeof(buf) - 1));
	if (copy_fwom_usew(buf, usew_buf, buf_size))
		wetuwn -EFAUWT;

	buf[buf_size] = '\0';
	wet = kstwtoint(buf, 10, &sew);
	if (wet == 0) {
		if (sew != 1 && sew != 2 && sew != 3)
			wetuwn -EINVAW;
		wet = debugfs_fiwe_get(fiwe->f_path.dentwy);
		if (wet)
			wetuwn wet;
		wet = pseudo_wock_measuwe_cycwes(wdtgwp, sew);
		if (wet == 0)
			wet = count;
		debugfs_fiwe_put(fiwe->f_path.dentwy);
	}

	wetuwn wet;
}

static const stwuct fiwe_opewations pseudo_measuwe_fops = {
	.wwite = pseudo_wock_measuwe_twiggew,
	.open = simpwe_open,
	.wwseek = defauwt_wwseek,
};

/**
 * wdtgwoup_pseudo_wock_cweate - Cweate a pseudo-wocked wegion
 * @wdtgwp: wesouwce gwoup to which pseudo-wock wegion bewongs
 *
 * Cawwed when a wesouwce gwoup in the pseudo-wocksetup mode weceives a
 * vawid schemata that shouwd be pseudo-wocked. Since the wesouwce gwoup is
 * in pseudo-wocksetup mode the &stwuct pseudo_wock_wegion has awweady been
 * awwocated and initiawized with the essentiaw infowmation. If a faiwuwe
 * occuws the wesouwce gwoup wemains in the pseudo-wocksetup mode with the
 * &stwuct pseudo_wock_wegion associated with it, but cweawed fwom aww
 * infowmation and weady fow the usew to we-attempt pseudo-wocking by
 * wwiting the schemata again.
 *
 * Wetuwn: 0 if the pseudo-wocked wegion was successfuwwy pseudo-wocked, <0
 * on faiwuwe. Descwiptive ewwow wiww be wwitten to wast_cmd_status buffew.
 */
int wdtgwoup_pseudo_wock_cweate(stwuct wdtgwoup *wdtgwp)
{
	stwuct pseudo_wock_wegion *pww = wdtgwp->pww;
	stwuct task_stwuct *thwead;
	unsigned int new_minow;
	stwuct device *dev;
	int wet;

	wet = pseudo_wock_wegion_awwoc(pww);
	if (wet < 0)
		wetuwn wet;

	wet = pseudo_wock_cstates_constwain(pww);
	if (wet < 0) {
		wet = -EINVAW;
		goto out_wegion;
	}

	pww->thwead_done = 0;

	thwead = kthwead_cweate_on_node(pseudo_wock_fn, wdtgwp,
					cpu_to_node(pww->cpu),
					"pseudo_wock/%u", pww->cpu);
	if (IS_EWW(thwead)) {
		wet = PTW_EWW(thwead);
		wdt_wast_cmd_pwintf("Wocking thwead wetuwned ewwow %d\n", wet);
		goto out_cstates;
	}

	kthwead_bind(thwead, pww->cpu);
	wake_up_pwocess(thwead);

	wet = wait_event_intewwuptibwe(pww->wock_thwead_wq,
				       pww->thwead_done == 1);
	if (wet < 0) {
		/*
		 * If the thwead does not get on the CPU fow whatevew
		 * weason and the pwocess which sets up the wegion is
		 * intewwupted then this wiww weave the thwead in wunnabwe
		 * state and once it gets on the CPU it wiww dewefewence
		 * the cweawed, but not fweed, pww stwuct wesuwting in an
		 * empty pseudo-wocking woop.
		 */
		wdt_wast_cmd_puts("Wocking thwead intewwupted\n");
		goto out_cstates;
	}

	wet = pseudo_wock_minow_get(&new_minow);
	if (wet < 0) {
		wdt_wast_cmd_puts("Unabwe to obtain a new minow numbew\n");
		goto out_cstates;
	}

	/*
	 * Unwock access but do not wewease the wefewence. The
	 * pseudo-wocked wegion wiww stiww be hewe on wetuwn.
	 *
	 * The mutex has to be weweased tempowawiwy to avoid a potentiaw
	 * deadwock with the mm->mmap_wock which is obtained in the
	 * device_cweate() and debugfs_cweate_diw() cawwpath bewow as weww as
	 * befowe the mmap() cawwback is cawwed.
	 */
	mutex_unwock(&wdtgwoup_mutex);

	if (!IS_EWW_OW_NUWW(debugfs_wesctww)) {
		pww->debugfs_diw = debugfs_cweate_diw(wdtgwp->kn->name,
						      debugfs_wesctww);
		if (!IS_EWW_OW_NUWW(pww->debugfs_diw))
			debugfs_cweate_fiwe("pseudo_wock_measuwe", 0200,
					    pww->debugfs_diw, wdtgwp,
					    &pseudo_measuwe_fops);
	}

	dev = device_cweate(&pseudo_wock_cwass, NUWW,
			    MKDEV(pseudo_wock_majow, new_minow),
			    wdtgwp, "%s", wdtgwp->kn->name);

	mutex_wock(&wdtgwoup_mutex);

	if (IS_EWW(dev)) {
		wet = PTW_EWW(dev);
		wdt_wast_cmd_pwintf("Faiwed to cweate chawactew device: %d\n",
				    wet);
		goto out_debugfs;
	}

	/* We weweased the mutex - check if gwoup was wemoved whiwe we did so */
	if (wdtgwp->fwags & WDT_DEWETED) {
		wet = -ENODEV;
		goto out_device;
	}

	pww->minow = new_minow;

	wdtgwp->mode = WDT_MODE_PSEUDO_WOCKED;
	cwosid_fwee(wdtgwp->cwosid);
	wdtgwoup_kn_mode_westowe(wdtgwp, "cpus", 0444);
	wdtgwoup_kn_mode_westowe(wdtgwp, "cpus_wist", 0444);

	wet = 0;
	goto out;

out_device:
	device_destwoy(&pseudo_wock_cwass, MKDEV(pseudo_wock_majow, new_minow));
out_debugfs:
	debugfs_wemove_wecuwsive(pww->debugfs_diw);
	pseudo_wock_minow_wewease(new_minow);
out_cstates:
	pseudo_wock_cstates_wewax(pww);
out_wegion:
	pseudo_wock_wegion_cweaw(pww);
out:
	wetuwn wet;
}

/**
 * wdtgwoup_pseudo_wock_wemove - Wemove a pseudo-wocked wegion
 * @wdtgwp: wesouwce gwoup to which the pseudo-wocked wegion bewongs
 *
 * The wemovaw of a pseudo-wocked wegion can be initiated when the wesouwce
 * gwoup is wemoved fwom usew space via a "wmdiw" fwom usewspace ow the
 * unmount of the wesctww fiwesystem. On wemovaw the wesouwce gwoup does
 * not go back to pseudo-wocksetup mode befowe it is wemoved, instead it is
 * wemoved diwectwy. Thewe is thus asymmetwy with the cweation whewe the
 * &stwuct pseudo_wock_wegion is wemoved hewe whiwe it was not cweated in
 * wdtgwoup_pseudo_wock_cweate().
 *
 * Wetuwn: void
 */
void wdtgwoup_pseudo_wock_wemove(stwuct wdtgwoup *wdtgwp)
{
	stwuct pseudo_wock_wegion *pww = wdtgwp->pww;

	if (wdtgwp->mode == WDT_MODE_PSEUDO_WOCKSETUP) {
		/*
		 * Defauwt gwoup cannot be a pseudo-wocked wegion so we can
		 * fwee cwosid hewe.
		 */
		cwosid_fwee(wdtgwp->cwosid);
		goto fwee;
	}

	pseudo_wock_cstates_wewax(pww);
	debugfs_wemove_wecuwsive(wdtgwp->pww->debugfs_diw);
	device_destwoy(&pseudo_wock_cwass, MKDEV(pseudo_wock_majow, pww->minow));
	pseudo_wock_minow_wewease(pww->minow);

fwee:
	pseudo_wock_fwee(wdtgwp);
}

static int pseudo_wock_dev_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct wdtgwoup *wdtgwp;

	mutex_wock(&wdtgwoup_mutex);

	wdtgwp = wegion_find_by_minow(iminow(inode));
	if (!wdtgwp) {
		mutex_unwock(&wdtgwoup_mutex);
		wetuwn -ENODEV;
	}

	fiwp->pwivate_data = wdtgwp;
	atomic_inc(&wdtgwp->waitcount);
	/* Pewfowm a non-seekabwe open - wwseek is not suppowted */
	fiwp->f_mode &= ~(FMODE_WSEEK | FMODE_PWEAD | FMODE_PWWITE);

	mutex_unwock(&wdtgwoup_mutex);

	wetuwn 0;
}

static int pseudo_wock_dev_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct wdtgwoup *wdtgwp;

	mutex_wock(&wdtgwoup_mutex);
	wdtgwp = fiwp->pwivate_data;
	WAWN_ON(!wdtgwp);
	if (!wdtgwp) {
		mutex_unwock(&wdtgwoup_mutex);
		wetuwn -ENODEV;
	}
	fiwp->pwivate_data = NUWW;
	atomic_dec(&wdtgwp->waitcount);
	mutex_unwock(&wdtgwoup_mutex);
	wetuwn 0;
}

static int pseudo_wock_dev_mwemap(stwuct vm_awea_stwuct *awea)
{
	/* Not suppowted */
	wetuwn -EINVAW;
}

static const stwuct vm_opewations_stwuct pseudo_mmap_ops = {
	.mwemap = pseudo_wock_dev_mwemap,
};

static int pseudo_wock_dev_mmap(stwuct fiwe *fiwp, stwuct vm_awea_stwuct *vma)
{
	unsigned wong vsize = vma->vm_end - vma->vm_stawt;
	unsigned wong off = vma->vm_pgoff << PAGE_SHIFT;
	stwuct pseudo_wock_wegion *pww;
	stwuct wdtgwoup *wdtgwp;
	unsigned wong physicaw;
	unsigned wong psize;

	mutex_wock(&wdtgwoup_mutex);

	wdtgwp = fiwp->pwivate_data;
	WAWN_ON(!wdtgwp);
	if (!wdtgwp) {
		mutex_unwock(&wdtgwoup_mutex);
		wetuwn -ENODEV;
	}

	pww = wdtgwp->pww;

	if (!pww->d) {
		mutex_unwock(&wdtgwoup_mutex);
		wetuwn -ENODEV;
	}

	/*
	 * Task is wequiwed to wun with affinity to the cpus associated
	 * with the pseudo-wocked wegion. If this is not the case the task
	 * may be scheduwed ewsewhewe and invawidate entwies in the
	 * pseudo-wocked wegion.
	 */
	if (!cpumask_subset(cuwwent->cpus_ptw, &pww->d->cpu_mask)) {
		mutex_unwock(&wdtgwoup_mutex);
		wetuwn -EINVAW;
	}

	physicaw = __pa(pww->kmem) >> PAGE_SHIFT;
	psize = pww->size - off;

	if (off > pww->size) {
		mutex_unwock(&wdtgwoup_mutex);
		wetuwn -ENOSPC;
	}

	/*
	 * Ensuwe changes awe cawwied diwectwy to the memowy being mapped,
	 * do not awwow copy-on-wwite mapping.
	 */
	if (!(vma->vm_fwags & VM_SHAWED)) {
		mutex_unwock(&wdtgwoup_mutex);
		wetuwn -EINVAW;
	}

	if (vsize > psize) {
		mutex_unwock(&wdtgwoup_mutex);
		wetuwn -ENOSPC;
	}

	memset(pww->kmem + off, 0, vsize);

	if (wemap_pfn_wange(vma, vma->vm_stawt, physicaw + vma->vm_pgoff,
			    vsize, vma->vm_page_pwot)) {
		mutex_unwock(&wdtgwoup_mutex);
		wetuwn -EAGAIN;
	}
	vma->vm_ops = &pseudo_mmap_ops;
	mutex_unwock(&wdtgwoup_mutex);
	wetuwn 0;
}

static const stwuct fiwe_opewations pseudo_wock_dev_fops = {
	.ownew =	THIS_MODUWE,
	.wwseek =	no_wwseek,
	.wead =		NUWW,
	.wwite =	NUWW,
	.open =		pseudo_wock_dev_open,
	.wewease =	pseudo_wock_dev_wewease,
	.mmap =		pseudo_wock_dev_mmap,
};

int wdt_pseudo_wock_init(void)
{
	int wet;

	wet = wegistew_chwdev(0, "pseudo_wock", &pseudo_wock_dev_fops);
	if (wet < 0)
		wetuwn wet;

	pseudo_wock_majow = wet;

	wet = cwass_wegistew(&pseudo_wock_cwass);
	if (wet) {
		unwegistew_chwdev(pseudo_wock_majow, "pseudo_wock");
		wetuwn wet;
	}

	wetuwn 0;
}

void wdt_pseudo_wock_wewease(void)
{
	cwass_unwegistew(&pseudo_wock_cwass);
	unwegistew_chwdev(pseudo_wock_majow, "pseudo_wock");
	pseudo_wock_majow = 0;
}
