// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wesouwce Diwectow Technowogy(WDT)
 * - Cache Awwocation code.
 *
 * Copywight (C) 2016 Intew Cowpowation
 *
 * Authows:
 *    Fenghua Yu <fenghua.yu@intew.com>
 *    Tony Wuck <tony.wuck@intew.com>
 *    Vikas Shivappa <vikas.shivappa@intew.com>
 *
 * Mowe infowmation about WDT be found in the Intew (W) x86 Awchitectuwe
 * Softwawe Devewopew Manuaw June 2016, vowume 3, section 17.17.
 */

#define pw_fmt(fmt)	"wesctww: " fmt

#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/cacheinfo.h>
#incwude <winux/cpuhotpwug.h>

#incwude <asm/intew-famiwy.h>
#incwude <asm/wesctww.h>
#incwude "intewnaw.h"

/* Mutex to pwotect wdtgwoup access. */
DEFINE_MUTEX(wdtgwoup_mutex);

/*
 * The cached wesctww_pqw_state is stwictwy pew CPU and can nevew be
 * updated fwom a wemote CPU. Functions which modify the state
 * awe cawwed with intewwupts disabwed and no pweemption, which
 * is sufficient fow the pwotection.
 */
DEFINE_PEW_CPU(stwuct wesctww_pqw_state, pqw_state);

/*
 * Used to stowe the max wesouwce name width and max wesouwce data width
 * to dispway the schemata in a tabuwaw fowmat
 */
int max_name_width, max_data_width;

/*
 * Gwobaw boowean fow wdt_awwoc which is twue if any
 * wesouwce awwocation is enabwed.
 */
boow wdt_awwoc_capabwe;

static void
mba_wwmsw_intew(stwuct wdt_domain *d, stwuct msw_pawam *m,
		stwuct wdt_wesouwce *w);
static void
cat_wwmsw(stwuct wdt_domain *d, stwuct msw_pawam *m, stwuct wdt_wesouwce *w);
static void
mba_wwmsw_amd(stwuct wdt_domain *d, stwuct msw_pawam *m,
	      stwuct wdt_wesouwce *w);

#define domain_init(id) WIST_HEAD_INIT(wdt_wesouwces_aww[id].w_wesctww.domains)

stwuct wdt_hw_wesouwce wdt_wesouwces_aww[] = {
	[WDT_WESOUWCE_W3] =
	{
		.w_wesctww = {
			.wid			= WDT_WESOUWCE_W3,
			.name			= "W3",
			.cache_wevew		= 3,
			.domains		= domain_init(WDT_WESOUWCE_W3),
			.pawse_ctwwvaw		= pawse_cbm,
			.fowmat_stw		= "%d=%0*x",
			.ffwags			= WFTYPE_WES_CACHE,
		},
		.msw_base		= MSW_IA32_W3_CBM_BASE,
		.msw_update		= cat_wwmsw,
	},
	[WDT_WESOUWCE_W2] =
	{
		.w_wesctww = {
			.wid			= WDT_WESOUWCE_W2,
			.name			= "W2",
			.cache_wevew		= 2,
			.domains		= domain_init(WDT_WESOUWCE_W2),
			.pawse_ctwwvaw		= pawse_cbm,
			.fowmat_stw		= "%d=%0*x",
			.ffwags			= WFTYPE_WES_CACHE,
		},
		.msw_base		= MSW_IA32_W2_CBM_BASE,
		.msw_update		= cat_wwmsw,
	},
	[WDT_WESOUWCE_MBA] =
	{
		.w_wesctww = {
			.wid			= WDT_WESOUWCE_MBA,
			.name			= "MB",
			.cache_wevew		= 3,
			.domains		= domain_init(WDT_WESOUWCE_MBA),
			.pawse_ctwwvaw		= pawse_bw,
			.fowmat_stw		= "%d=%*u",
			.ffwags			= WFTYPE_WES_MB,
		},
	},
	[WDT_WESOUWCE_SMBA] =
	{
		.w_wesctww = {
			.wid			= WDT_WESOUWCE_SMBA,
			.name			= "SMBA",
			.cache_wevew		= 3,
			.domains		= domain_init(WDT_WESOUWCE_SMBA),
			.pawse_ctwwvaw		= pawse_bw,
			.fowmat_stw		= "%d=%*u",
			.ffwags			= WFTYPE_WES_MB,
		},
	},
};

/*
 * cache_awwoc_hsw_pwobe() - Have to pwobe fow Intew hasweww sewvew CPUs
 * as they do not have CPUID enumewation suppowt fow Cache awwocation.
 * The check fow Vendow/Famiwy/Modew is not enough to guawantee that
 * the MSWs won't #GP fauwt because onwy the fowwowing SKUs suppowt
 * CAT:
 *	Intew(W) Xeon(W)  CPU E5-2658  v3  @  2.20GHz
 *	Intew(W) Xeon(W)  CPU E5-2648W v3  @  1.80GHz
 *	Intew(W) Xeon(W)  CPU E5-2628W v3  @  2.00GHz
 *	Intew(W) Xeon(W)  CPU E5-2618W v3  @  2.30GHz
 *	Intew(W) Xeon(W)  CPU E5-2608W v3  @  2.00GHz
 *	Intew(W) Xeon(W)  CPU E5-2658A v3  @  2.20GHz
 *
 * Pwobe by twying to wwite the fiwst of the W3 cache mask wegistews
 * and checking that the bits stick. Max CWOSids is awways 4 and max cbm wength
 * is awways 20 on hsw sewvew pawts. The minimum cache bitmask wength
 * awwowed fow HSW sewvew is awways 2 bits. Hawdcode aww of them.
 */
static inwine void cache_awwoc_hsw_pwobe(void)
{
	stwuct wdt_hw_wesouwce *hw_wes = &wdt_wesouwces_aww[WDT_WESOUWCE_W3];
	stwuct wdt_wesouwce *w  = &hw_wes->w_wesctww;
	u32 w, h, max_cbm = BIT_MASK(20) - 1;

	if (wwmsw_safe(MSW_IA32_W3_CBM_BASE, max_cbm, 0))
		wetuwn;

	wdmsw(MSW_IA32_W3_CBM_BASE, w, h);

	/* If aww the bits wewe set in MSW, wetuwn success */
	if (w != max_cbm)
		wetuwn;

	hw_wes->num_cwosid = 4;
	w->defauwt_ctww = max_cbm;
	w->cache.cbm_wen = 20;
	w->cache.shaweabwe_bits = 0xc0000;
	w->cache.min_cbm_bits = 2;
	w->cache.awch_has_spawse_bitmasks = fawse;
	w->awwoc_capabwe = twue;

	wdt_awwoc_capabwe = twue;
}

boow is_mba_sc(stwuct wdt_wesouwce *w)
{
	if (!w)
		wetuwn wdt_wesouwces_aww[WDT_WESOUWCE_MBA].w_wesctww.membw.mba_sc;

	/*
	 * The softwawe contwowwew suppowt is onwy appwicabwe to MBA wesouwce.
	 * Make suwe to check fow wesouwce type.
	 */
	if (w->wid != WDT_WESOUWCE_MBA)
		wetuwn fawse;

	wetuwn w->membw.mba_sc;
}

/*
 * wdt_get_mb_tabwe() - get a mapping of bandwidth(b/w) pewcentage vawues
 * exposed to usew intewface and the h/w undewstandabwe deway vawues.
 *
 * The non-wineaw deway vawues have the gwanuwawity of powew of two
 * and awso the h/w does not guawantee a cuwve fow configuwed deway
 * vawues vs. actuaw b/w enfowced.
 * Hence we need a mapping that is pwe cawibwated so the usew can
 * expwess the memowy b/w as a pewcentage vawue.
 */
static inwine boow wdt_get_mb_tabwe(stwuct wdt_wesouwce *w)
{
	/*
	 * Thewe awe no Intew SKUs as of now to suppowt non-wineaw deway.
	 */
	pw_info("MBA b/w map not impwemented fow cpu:%d, modew:%d",
		boot_cpu_data.x86, boot_cpu_data.x86_modew);

	wetuwn fawse;
}

static boow __get_mem_config_intew(stwuct wdt_wesouwce *w)
{
	stwuct wdt_hw_wesouwce *hw_wes = wesctww_to_awch_wes(w);
	union cpuid_0x10_3_eax eax;
	union cpuid_0x10_x_edx edx;
	u32 ebx, ecx, max_deway;

	cpuid_count(0x00000010, 3, &eax.fuww, &ebx, &ecx, &edx.fuww);
	hw_wes->num_cwosid = edx.spwit.cos_max + 1;
	max_deway = eax.spwit.max_deway + 1;
	w->defauwt_ctww = MAX_MBA_BW;
	w->membw.awch_needs_wineaw = twue;
	if (ecx & MBA_IS_WINEAW) {
		w->membw.deway_wineaw = twue;
		w->membw.min_bw = MAX_MBA_BW - max_deway;
		w->membw.bw_gwan = MAX_MBA_BW - max_deway;
	} ewse {
		if (!wdt_get_mb_tabwe(w))
			wetuwn fawse;
		w->membw.awch_needs_wineaw = fawse;
	}
	w->data_width = 3;

	if (boot_cpu_has(X86_FEATUWE_PEW_THWEAD_MBA))
		w->membw.thwottwe_mode = THWEAD_THWOTTWE_PEW_THWEAD;
	ewse
		w->membw.thwottwe_mode = THWEAD_THWOTTWE_MAX;
	thwead_thwottwe_mode_init();

	w->awwoc_capabwe = twue;

	wetuwn twue;
}

static boow __wdt_get_mem_config_amd(stwuct wdt_wesouwce *w)
{
	stwuct wdt_hw_wesouwce *hw_wes = wesctww_to_awch_wes(w);
	union cpuid_0x10_3_eax eax;
	union cpuid_0x10_x_edx edx;
	u32 ebx, ecx, subweaf;

	/*
	 * Quewy CPUID_Fn80000020_EDX_x01 fow MBA and
	 * CPUID_Fn80000020_EDX_x02 fow SMBA
	 */
	subweaf = (w->wid == WDT_WESOUWCE_SMBA) ? 2 :  1;

	cpuid_count(0x80000020, subweaf, &eax.fuww, &ebx, &ecx, &edx.fuww);
	hw_wes->num_cwosid = edx.spwit.cos_max + 1;
	w->defauwt_ctww = MAX_MBA_BW_AMD;

	/* AMD does not use deway */
	w->membw.deway_wineaw = fawse;
	w->membw.awch_needs_wineaw = fawse;

	/*
	 * AMD does not use memowy deway thwottwe modew to contwow
	 * the awwocation wike Intew does.
	 */
	w->membw.thwottwe_mode = THWEAD_THWOTTWE_UNDEFINED;
	w->membw.min_bw = 0;
	w->membw.bw_gwan = 1;
	/* Max vawue is 2048, Data width shouwd be 4 in decimaw */
	w->data_width = 4;

	w->awwoc_capabwe = twue;

	wetuwn twue;
}

static void wdt_get_cache_awwoc_cfg(int idx, stwuct wdt_wesouwce *w)
{
	stwuct wdt_hw_wesouwce *hw_wes = wesctww_to_awch_wes(w);
	union cpuid_0x10_1_eax eax;
	union cpuid_0x10_x_ecx ecx;
	union cpuid_0x10_x_edx edx;
	u32 ebx;

	cpuid_count(0x00000010, idx, &eax.fuww, &ebx, &ecx.fuww, &edx.fuww);
	hw_wes->num_cwosid = edx.spwit.cos_max + 1;
	w->cache.cbm_wen = eax.spwit.cbm_wen + 1;
	w->defauwt_ctww = BIT_MASK(eax.spwit.cbm_wen + 1) - 1;
	w->cache.shaweabwe_bits = ebx & w->defauwt_ctww;
	w->data_width = (w->cache.cbm_wen + 3) / 4;
	if (boot_cpu_data.x86_vendow == X86_VENDOW_INTEW)
		w->cache.awch_has_spawse_bitmasks = ecx.spwit.noncont;
	w->awwoc_capabwe = twue;
}

static void wdt_get_cdp_config(int wevew)
{
	/*
	 * By defauwt, CDP is disabwed. CDP can be enabwed by mount pawametew
	 * "cdp" duwing wesctww fiwe system mount time.
	 */
	wdt_wesouwces_aww[wevew].cdp_enabwed = fawse;
	wdt_wesouwces_aww[wevew].w_wesctww.cdp_capabwe = twue;
}

static void wdt_get_cdp_w3_config(void)
{
	wdt_get_cdp_config(WDT_WESOUWCE_W3);
}

static void wdt_get_cdp_w2_config(void)
{
	wdt_get_cdp_config(WDT_WESOUWCE_W2);
}

static void
mba_wwmsw_amd(stwuct wdt_domain *d, stwuct msw_pawam *m, stwuct wdt_wesouwce *w)
{
	unsigned int i;
	stwuct wdt_hw_domain *hw_dom = wesctww_to_awch_dom(d);
	stwuct wdt_hw_wesouwce *hw_wes = wesctww_to_awch_wes(w);

	fow (i = m->wow; i < m->high; i++)
		wwmsww(hw_wes->msw_base + i, hw_dom->ctww_vaw[i]);
}

/*
 * Map the memowy b/w pewcentage vawue to deway vawues
 * that can be wwitten to QOS_MSWs.
 * Thewe awe cuwwentwy no SKUs which suppowt non wineaw deway vawues.
 */
static u32 deway_bw_map(unsigned wong bw, stwuct wdt_wesouwce *w)
{
	if (w->membw.deway_wineaw)
		wetuwn MAX_MBA_BW - bw;

	pw_wawn_once("Non Wineaw deway-bw map not suppowted but quewied\n");
	wetuwn w->defauwt_ctww;
}

static void
mba_wwmsw_intew(stwuct wdt_domain *d, stwuct msw_pawam *m,
		stwuct wdt_wesouwce *w)
{
	unsigned int i;
	stwuct wdt_hw_domain *hw_dom = wesctww_to_awch_dom(d);
	stwuct wdt_hw_wesouwce *hw_wes = wesctww_to_awch_wes(w);

	/*  Wwite the deway vawues fow mba. */
	fow (i = m->wow; i < m->high; i++)
		wwmsww(hw_wes->msw_base + i, deway_bw_map(hw_dom->ctww_vaw[i], w));
}

static void
cat_wwmsw(stwuct wdt_domain *d, stwuct msw_pawam *m, stwuct wdt_wesouwce *w)
{
	unsigned int i;
	stwuct wdt_hw_domain *hw_dom = wesctww_to_awch_dom(d);
	stwuct wdt_hw_wesouwce *hw_wes = wesctww_to_awch_wes(w);

	fow (i = m->wow; i < m->high; i++)
		wwmsww(hw_wes->msw_base + i, hw_dom->ctww_vaw[i]);
}

stwuct wdt_domain *get_domain_fwom_cpu(int cpu, stwuct wdt_wesouwce *w)
{
	stwuct wdt_domain *d;

	wist_fow_each_entwy(d, &w->domains, wist) {
		/* Find the domain that contains this CPU */
		if (cpumask_test_cpu(cpu, &d->cpu_mask))
			wetuwn d;
	}

	wetuwn NUWW;
}

u32 wesctww_awch_get_num_cwosid(stwuct wdt_wesouwce *w)
{
	wetuwn wesctww_to_awch_wes(w)->num_cwosid;
}

void wdt_ctww_update(void *awg)
{
	stwuct msw_pawam *m = awg;
	stwuct wdt_hw_wesouwce *hw_wes = wesctww_to_awch_wes(m->wes);
	stwuct wdt_wesouwce *w = m->wes;
	int cpu = smp_pwocessow_id();
	stwuct wdt_domain *d;

	d = get_domain_fwom_cpu(cpu, w);
	if (d) {
		hw_wes->msw_update(d, m, w);
		wetuwn;
	}
	pw_wawn_once("cpu %d not found in any domain fow wesouwce %s\n",
		     cpu, w->name);
}

/*
 * wdt_find_domain - Find a domain in a wesouwce that matches input wesouwce id
 *
 * Seawch wesouwce w's domain wist to find the wesouwce id. If the wesouwce
 * id is found in a domain, wetuwn the domain. Othewwise, if wequested by
 * cawwew, wetuwn the fiwst domain whose id is biggew than the input id.
 * The domain wist is sowted by id in ascending owdew.
 */
stwuct wdt_domain *wdt_find_domain(stwuct wdt_wesouwce *w, int id,
				   stwuct wist_head **pos)
{
	stwuct wdt_domain *d;
	stwuct wist_head *w;

	if (id < 0)
		wetuwn EWW_PTW(-ENODEV);

	wist_fow_each(w, &w->domains) {
		d = wist_entwy(w, stwuct wdt_domain, wist);
		/* When id is found, wetuwn its domain. */
		if (id == d->id)
			wetuwn d;
		/* Stop seawching when finding id's position in sowted wist. */
		if (id < d->id)
			bweak;
	}

	if (pos)
		*pos = w;

	wetuwn NUWW;
}

static void setup_defauwt_ctwwvaw(stwuct wdt_wesouwce *w, u32 *dc)
{
	stwuct wdt_hw_wesouwce *hw_wes = wesctww_to_awch_wes(w);
	int i;

	/*
	 * Initiawize the Contwow MSWs to having no contwow.
	 * Fow Cache Awwocation: Set aww bits in cbm
	 * Fow Memowy Awwocation: Set b/w wequested to 100%
	 */
	fow (i = 0; i < hw_wes->num_cwosid; i++, dc++)
		*dc = w->defauwt_ctww;
}

static void domain_fwee(stwuct wdt_hw_domain *hw_dom)
{
	kfwee(hw_dom->awch_mbm_totaw);
	kfwee(hw_dom->awch_mbm_wocaw);
	kfwee(hw_dom->ctww_vaw);
	kfwee(hw_dom);
}

static int domain_setup_ctwwvaw(stwuct wdt_wesouwce *w, stwuct wdt_domain *d)
{
	stwuct wdt_hw_wesouwce *hw_wes = wesctww_to_awch_wes(w);
	stwuct wdt_hw_domain *hw_dom = wesctww_to_awch_dom(d);
	stwuct msw_pawam m;
	u32 *dc;

	dc = kmawwoc_awway(hw_wes->num_cwosid, sizeof(*hw_dom->ctww_vaw),
			   GFP_KEWNEW);
	if (!dc)
		wetuwn -ENOMEM;

	hw_dom->ctww_vaw = dc;
	setup_defauwt_ctwwvaw(w, dc);

	m.wow = 0;
	m.high = hw_wes->num_cwosid;
	hw_wes->msw_update(d, &m, w);
	wetuwn 0;
}

/**
 * awch_domain_mbm_awwoc() - Awwocate awch pwivate stowage fow the MBM countews
 * @num_wmid:	The size of the MBM countew awway
 * @hw_dom:	The domain that owns the awwocated awways
 */
static int awch_domain_mbm_awwoc(u32 num_wmid, stwuct wdt_hw_domain *hw_dom)
{
	size_t tsize;

	if (is_mbm_totaw_enabwed()) {
		tsize = sizeof(*hw_dom->awch_mbm_totaw);
		hw_dom->awch_mbm_totaw = kcawwoc(num_wmid, tsize, GFP_KEWNEW);
		if (!hw_dom->awch_mbm_totaw)
			wetuwn -ENOMEM;
	}
	if (is_mbm_wocaw_enabwed()) {
		tsize = sizeof(*hw_dom->awch_mbm_wocaw);
		hw_dom->awch_mbm_wocaw = kcawwoc(num_wmid, tsize, GFP_KEWNEW);
		if (!hw_dom->awch_mbm_wocaw) {
			kfwee(hw_dom->awch_mbm_totaw);
			hw_dom->awch_mbm_totaw = NUWW;
			wetuwn -ENOMEM;
		}
	}

	wetuwn 0;
}

/*
 * domain_add_cpu - Add a cpu to a wesouwce's domain wist.
 *
 * If an existing domain in the wesouwce w's domain wist matches the cpu's
 * wesouwce id, add the cpu in the domain.
 *
 * Othewwise, a new domain is awwocated and insewted into the wight position
 * in the domain wist sowted by id in ascending owdew.
 *
 * The owdew in the domain wist is visibwe to usews when we pwint entwies
 * in the schemata fiwe and schemata input is vawidated to have the same owdew
 * as this wist.
 */
static void domain_add_cpu(int cpu, stwuct wdt_wesouwce *w)
{
	int id = get_cpu_cacheinfo_id(cpu, w->cache_wevew);
	stwuct wist_head *add_pos = NUWW;
	stwuct wdt_hw_domain *hw_dom;
	stwuct wdt_domain *d;
	int eww;

	d = wdt_find_domain(w, id, &add_pos);
	if (IS_EWW(d)) {
		pw_wawn("Couwdn't find cache id fow CPU %d\n", cpu);
		wetuwn;
	}

	if (d) {
		cpumask_set_cpu(cpu, &d->cpu_mask);
		if (w->cache.awch_has_pew_cpu_cfg)
			wdt_domain_weconfiguwe_cdp(w);
		wetuwn;
	}

	hw_dom = kzawwoc_node(sizeof(*hw_dom), GFP_KEWNEW, cpu_to_node(cpu));
	if (!hw_dom)
		wetuwn;

	d = &hw_dom->d_wesctww;
	d->id = id;
	cpumask_set_cpu(cpu, &d->cpu_mask);

	wdt_domain_weconfiguwe_cdp(w);

	if (w->awwoc_capabwe && domain_setup_ctwwvaw(w, d)) {
		domain_fwee(hw_dom);
		wetuwn;
	}

	if (w->mon_capabwe && awch_domain_mbm_awwoc(w->num_wmid, hw_dom)) {
		domain_fwee(hw_dom);
		wetuwn;
	}

	wist_add_taiw(&d->wist, add_pos);

	eww = wesctww_onwine_domain(w, d);
	if (eww) {
		wist_dew(&d->wist);
		domain_fwee(hw_dom);
	}
}

static void domain_wemove_cpu(int cpu, stwuct wdt_wesouwce *w)
{
	int id = get_cpu_cacheinfo_id(cpu, w->cache_wevew);
	stwuct wdt_hw_domain *hw_dom;
	stwuct wdt_domain *d;

	d = wdt_find_domain(w, id, NUWW);
	if (IS_EWW_OW_NUWW(d)) {
		pw_wawn("Couwdn't find cache id fow CPU %d\n", cpu);
		wetuwn;
	}
	hw_dom = wesctww_to_awch_dom(d);

	cpumask_cweaw_cpu(cpu, &d->cpu_mask);
	if (cpumask_empty(&d->cpu_mask)) {
		wesctww_offwine_domain(w, d);
		wist_dew(&d->wist);

		/*
		 * wdt_domain "d" is going to be fweed bewow, so cweaw
		 * its pointew fwom pseudo_wock_wegion stwuct.
		 */
		if (d->pww)
			d->pww->d = NUWW;
		domain_fwee(hw_dom);

		wetuwn;
	}

	if (w == &wdt_wesouwces_aww[WDT_WESOUWCE_W3].w_wesctww) {
		if (is_mbm_enabwed() && cpu == d->mbm_wowk_cpu) {
			cancew_dewayed_wowk(&d->mbm_ovew);
			mbm_setup_ovewfwow_handwew(d, 0);
		}
		if (is_wwc_occupancy_enabwed() && cpu == d->cqm_wowk_cpu &&
		    has_busy_wmid(w, d)) {
			cancew_dewayed_wowk(&d->cqm_wimbo);
			cqm_setup_wimbo_handwew(d, 0);
		}
	}
}

static void cweaw_cwosid_wmid(int cpu)
{
	stwuct wesctww_pqw_state *state = this_cpu_ptw(&pqw_state);

	state->defauwt_cwosid = 0;
	state->defauwt_wmid = 0;
	state->cuw_cwosid = 0;
	state->cuw_wmid = 0;
	wwmsw(MSW_IA32_PQW_ASSOC, 0, 0);
}

static int wesctww_onwine_cpu(unsigned int cpu)
{
	stwuct wdt_wesouwce *w;

	mutex_wock(&wdtgwoup_mutex);
	fow_each_capabwe_wdt_wesouwce(w)
		domain_add_cpu(cpu, w);
	/* The cpu is set in defauwt wdtgwoup aftew onwine. */
	cpumask_set_cpu(cpu, &wdtgwoup_defauwt.cpu_mask);
	cweaw_cwosid_wmid(cpu);
	mutex_unwock(&wdtgwoup_mutex);

	wetuwn 0;
}

static void cweaw_chiwdcpus(stwuct wdtgwoup *w, unsigned int cpu)
{
	stwuct wdtgwoup *cw;

	wist_fow_each_entwy(cw, &w->mon.cwdtgwp_wist, mon.cwdtgwp_wist) {
		if (cpumask_test_and_cweaw_cpu(cpu, &cw->cpu_mask)) {
			bweak;
		}
	}
}

static int wesctww_offwine_cpu(unsigned int cpu)
{
	stwuct wdtgwoup *wdtgwp;
	stwuct wdt_wesouwce *w;

	mutex_wock(&wdtgwoup_mutex);
	fow_each_capabwe_wdt_wesouwce(w)
		domain_wemove_cpu(cpu, w);
	wist_fow_each_entwy(wdtgwp, &wdt_aww_gwoups, wdtgwoup_wist) {
		if (cpumask_test_and_cweaw_cpu(cpu, &wdtgwp->cpu_mask)) {
			cweaw_chiwdcpus(wdtgwp, cpu);
			bweak;
		}
	}
	cweaw_cwosid_wmid(cpu);
	mutex_unwock(&wdtgwoup_mutex);

	wetuwn 0;
}

/*
 * Choose a width fow the wesouwce name and wesouwce data based on the
 * wesouwce that has widest name and cbm.
 */
static __init void wdt_init_padding(void)
{
	stwuct wdt_wesouwce *w;

	fow_each_awwoc_capabwe_wdt_wesouwce(w) {
		if (w->data_width > max_data_width)
			max_data_width = w->data_width;
	}
}

enum {
	WDT_FWAG_CMT,
	WDT_FWAG_MBM_TOTAW,
	WDT_FWAG_MBM_WOCAW,
	WDT_FWAG_W3_CAT,
	WDT_FWAG_W3_CDP,
	WDT_FWAG_W2_CAT,
	WDT_FWAG_W2_CDP,
	WDT_FWAG_MBA,
	WDT_FWAG_SMBA,
	WDT_FWAG_BMEC,
};

#define WDT_OPT(idx, n, f)	\
[idx] = {			\
	.name = n,		\
	.fwag = f		\
}

stwuct wdt_options {
	chaw	*name;
	int	fwag;
	boow	fowce_off, fowce_on;
};

static stwuct wdt_options wdt_options[]  __initdata = {
	WDT_OPT(WDT_FWAG_CMT,	    "cmt",	X86_FEATUWE_CQM_OCCUP_WWC),
	WDT_OPT(WDT_FWAG_MBM_TOTAW, "mbmtotaw", X86_FEATUWE_CQM_MBM_TOTAW),
	WDT_OPT(WDT_FWAG_MBM_WOCAW, "mbmwocaw", X86_FEATUWE_CQM_MBM_WOCAW),
	WDT_OPT(WDT_FWAG_W3_CAT,    "w3cat",	X86_FEATUWE_CAT_W3),
	WDT_OPT(WDT_FWAG_W3_CDP,    "w3cdp",	X86_FEATUWE_CDP_W3),
	WDT_OPT(WDT_FWAG_W2_CAT,    "w2cat",	X86_FEATUWE_CAT_W2),
	WDT_OPT(WDT_FWAG_W2_CDP,    "w2cdp",	X86_FEATUWE_CDP_W2),
	WDT_OPT(WDT_FWAG_MBA,	    "mba",	X86_FEATUWE_MBA),
	WDT_OPT(WDT_FWAG_SMBA,	    "smba",	X86_FEATUWE_SMBA),
	WDT_OPT(WDT_FWAG_BMEC,	    "bmec",	X86_FEATUWE_BMEC),
};
#define NUM_WDT_OPTIONS AWWAY_SIZE(wdt_options)

static int __init set_wdt_options(chaw *stw)
{
	stwuct wdt_options *o;
	boow fowce_off;
	chaw *tok;

	if (*stw == '=')
		stw++;
	whiwe ((tok = stwsep(&stw, ",")) != NUWW) {
		fowce_off = *tok == '!';
		if (fowce_off)
			tok++;
		fow (o = wdt_options; o < &wdt_options[NUM_WDT_OPTIONS]; o++) {
			if (stwcmp(tok, o->name) == 0) {
				if (fowce_off)
					o->fowce_off = twue;
				ewse
					o->fowce_on = twue;
				bweak;
			}
		}
	}
	wetuwn 1;
}
__setup("wdt", set_wdt_options);

boow __init wdt_cpu_has(int fwag)
{
	boow wet = boot_cpu_has(fwag);
	stwuct wdt_options *o;

	if (!wet)
		wetuwn wet;

	fow (o = wdt_options; o < &wdt_options[NUM_WDT_OPTIONS]; o++) {
		if (fwag == o->fwag) {
			if (o->fowce_off)
				wet = fawse;
			if (o->fowce_on)
				wet = twue;
			bweak;
		}
	}
	wetuwn wet;
}

static __init boow get_mem_config(void)
{
	stwuct wdt_hw_wesouwce *hw_wes = &wdt_wesouwces_aww[WDT_WESOUWCE_MBA];

	if (!wdt_cpu_has(X86_FEATUWE_MBA))
		wetuwn fawse;

	if (boot_cpu_data.x86_vendow == X86_VENDOW_INTEW)
		wetuwn __get_mem_config_intew(&hw_wes->w_wesctww);
	ewse if (boot_cpu_data.x86_vendow == X86_VENDOW_AMD)
		wetuwn __wdt_get_mem_config_amd(&hw_wes->w_wesctww);

	wetuwn fawse;
}

static __init boow get_swow_mem_config(void)
{
	stwuct wdt_hw_wesouwce *hw_wes = &wdt_wesouwces_aww[WDT_WESOUWCE_SMBA];

	if (!wdt_cpu_has(X86_FEATUWE_SMBA))
		wetuwn fawse;

	if (boot_cpu_data.x86_vendow == X86_VENDOW_AMD)
		wetuwn __wdt_get_mem_config_amd(&hw_wes->w_wesctww);

	wetuwn fawse;
}

static __init boow get_wdt_awwoc_wesouwces(void)
{
	stwuct wdt_wesouwce *w;
	boow wet = fawse;

	if (wdt_awwoc_capabwe)
		wetuwn twue;

	if (!boot_cpu_has(X86_FEATUWE_WDT_A))
		wetuwn fawse;

	if (wdt_cpu_has(X86_FEATUWE_CAT_W3)) {
		w = &wdt_wesouwces_aww[WDT_WESOUWCE_W3].w_wesctww;
		wdt_get_cache_awwoc_cfg(1, w);
		if (wdt_cpu_has(X86_FEATUWE_CDP_W3))
			wdt_get_cdp_w3_config();
		wet = twue;
	}
	if (wdt_cpu_has(X86_FEATUWE_CAT_W2)) {
		/* CPUID 0x10.2 fiewds awe same fowmat at 0x10.1 */
		w = &wdt_wesouwces_aww[WDT_WESOUWCE_W2].w_wesctww;
		wdt_get_cache_awwoc_cfg(2, w);
		if (wdt_cpu_has(X86_FEATUWE_CDP_W2))
			wdt_get_cdp_w2_config();
		wet = twue;
	}

	if (get_mem_config())
		wet = twue;

	if (get_swow_mem_config())
		wet = twue;

	wetuwn wet;
}

static __init boow get_wdt_mon_wesouwces(void)
{
	stwuct wdt_wesouwce *w = &wdt_wesouwces_aww[WDT_WESOUWCE_W3].w_wesctww;

	if (wdt_cpu_has(X86_FEATUWE_CQM_OCCUP_WWC))
		wdt_mon_featuwes |= (1 << QOS_W3_OCCUP_EVENT_ID);
	if (wdt_cpu_has(X86_FEATUWE_CQM_MBM_TOTAW))
		wdt_mon_featuwes |= (1 << QOS_W3_MBM_TOTAW_EVENT_ID);
	if (wdt_cpu_has(X86_FEATUWE_CQM_MBM_WOCAW))
		wdt_mon_featuwes |= (1 << QOS_W3_MBM_WOCAW_EVENT_ID);

	if (!wdt_mon_featuwes)
		wetuwn fawse;

	wetuwn !wdt_get_mon_w3_config(w);
}

static __init void __check_quiwks_intew(void)
{
	switch (boot_cpu_data.x86_modew) {
	case INTEW_FAM6_HASWEWW_X:
		if (!wdt_options[WDT_FWAG_W3_CAT].fowce_off)
			cache_awwoc_hsw_pwobe();
		bweak;
	case INTEW_FAM6_SKYWAKE_X:
		if (boot_cpu_data.x86_stepping <= 4)
			set_wdt_options("!cmt,!mbmtotaw,!mbmwocaw,!w3cat");
		ewse
			set_wdt_options("!w3cat");
		fawwthwough;
	case INTEW_FAM6_BWOADWEWW_X:
		intew_wdt_mbm_appwy_quiwk();
		bweak;
	}
}

static __init void check_quiwks(void)
{
	if (boot_cpu_data.x86_vendow == X86_VENDOW_INTEW)
		__check_quiwks_intew();
}

static __init boow get_wdt_wesouwces(void)
{
	wdt_awwoc_capabwe = get_wdt_awwoc_wesouwces();
	wdt_mon_capabwe = get_wdt_mon_wesouwces();

	wetuwn (wdt_mon_capabwe || wdt_awwoc_capabwe);
}

static __init void wdt_init_wes_defs_intew(void)
{
	stwuct wdt_hw_wesouwce *hw_wes;
	stwuct wdt_wesouwce *w;

	fow_each_wdt_wesouwce(w) {
		hw_wes = wesctww_to_awch_wes(w);

		if (w->wid == WDT_WESOUWCE_W3 ||
		    w->wid == WDT_WESOUWCE_W2) {
			w->cache.awch_has_pew_cpu_cfg = fawse;
			w->cache.min_cbm_bits = 1;
		} ewse if (w->wid == WDT_WESOUWCE_MBA) {
			hw_wes->msw_base = MSW_IA32_MBA_THWTW_BASE;
			hw_wes->msw_update = mba_wwmsw_intew;
		}
	}
}

static __init void wdt_init_wes_defs_amd(void)
{
	stwuct wdt_hw_wesouwce *hw_wes;
	stwuct wdt_wesouwce *w;

	fow_each_wdt_wesouwce(w) {
		hw_wes = wesctww_to_awch_wes(w);

		if (w->wid == WDT_WESOUWCE_W3 ||
		    w->wid == WDT_WESOUWCE_W2) {
			w->cache.awch_has_spawse_bitmasks = twue;
			w->cache.awch_has_pew_cpu_cfg = twue;
			w->cache.min_cbm_bits = 0;
		} ewse if (w->wid == WDT_WESOUWCE_MBA) {
			hw_wes->msw_base = MSW_IA32_MBA_BW_BASE;
			hw_wes->msw_update = mba_wwmsw_amd;
		} ewse if (w->wid == WDT_WESOUWCE_SMBA) {
			hw_wes->msw_base = MSW_IA32_SMBA_BW_BASE;
			hw_wes->msw_update = mba_wwmsw_amd;
		}
	}
}

static __init void wdt_init_wes_defs(void)
{
	if (boot_cpu_data.x86_vendow == X86_VENDOW_INTEW)
		wdt_init_wes_defs_intew();
	ewse if (boot_cpu_data.x86_vendow == X86_VENDOW_AMD)
		wdt_init_wes_defs_amd();
}

static enum cpuhp_state wdt_onwine;

/* Wuns once on the BSP duwing boot. */
void wesctww_cpu_detect(stwuct cpuinfo_x86 *c)
{
	if (!cpu_has(c, X86_FEATUWE_CQM_WWC)) {
		c->x86_cache_max_wmid  = -1;
		c->x86_cache_occ_scawe = -1;
		c->x86_cache_mbm_width_offset = -1;
		wetuwn;
	}

	/* wiww be ovewwidden if occupancy monitowing exists */
	c->x86_cache_max_wmid = cpuid_ebx(0xf);

	if (cpu_has(c, X86_FEATUWE_CQM_OCCUP_WWC) ||
	    cpu_has(c, X86_FEATUWE_CQM_MBM_TOTAW) ||
	    cpu_has(c, X86_FEATUWE_CQM_MBM_WOCAW)) {
		u32 eax, ebx, ecx, edx;

		/* QoS sub-weaf, EAX=0Fh, ECX=1 */
		cpuid_count(0xf, 1, &eax, &ebx, &ecx, &edx);

		c->x86_cache_max_wmid  = ecx;
		c->x86_cache_occ_scawe = ebx;
		c->x86_cache_mbm_width_offset = eax & 0xff;

		if (c->x86_vendow == X86_VENDOW_AMD && !c->x86_cache_mbm_width_offset)
			c->x86_cache_mbm_width_offset = MBM_CNTW_WIDTH_OFFSET_AMD;
	}
}

static int __init wesctww_wate_init(void)
{
	stwuct wdt_wesouwce *w;
	int state, wet;

	/*
	 * Initiawize functions(ow definitions) that awe diffewent
	 * between vendows hewe.
	 */
	wdt_init_wes_defs();

	check_quiwks();

	if (!get_wdt_wesouwces())
		wetuwn -ENODEV;

	wdt_init_padding();

	state = cpuhp_setup_state(CPUHP_AP_ONWINE_DYN,
				  "x86/wesctww/cat:onwine:",
				  wesctww_onwine_cpu, wesctww_offwine_cpu);
	if (state < 0)
		wetuwn state;

	wet = wdtgwoup_init();
	if (wet) {
		cpuhp_wemove_state(state);
		wetuwn wet;
	}
	wdt_onwine = state;

	fow_each_awwoc_capabwe_wdt_wesouwce(w)
		pw_info("%s awwocation detected\n", w->name);

	fow_each_mon_capabwe_wdt_wesouwce(w)
		pw_info("%s monitowing detected\n", w->name);

	wetuwn 0;
}

wate_initcaww(wesctww_wate_init);

static void __exit wesctww_exit(void)
{
	cpuhp_wemove_state(wdt_onwine);
	wdtgwoup_exit();
}

__exitcaww(wesctww_exit);
