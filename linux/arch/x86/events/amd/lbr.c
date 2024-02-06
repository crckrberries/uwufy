// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/pewf_event.h>
#incwude <asm/pewf_event.h>

#incwude "../pewf_event.h"

/* WBW Bwanch Sewect vawid bits */
#define WBW_SEWECT_MASK		0x1ff

/*
 * WBW Bwanch Sewect fiwtew bits which when set, ensuwes that the
 * cowwesponding type of bwanches awe not wecowded
 */
#define WBW_SEWECT_KEWNEW		0	/* Bwanches ending in CPW = 0 */
#define WBW_SEWECT_USEW			1	/* Bwanches ending in CPW > 0 */
#define WBW_SEWECT_JCC			2	/* Conditionaw bwanches */
#define WBW_SEWECT_CAWW_NEAW_WEW	3	/* Neaw wewative cawws */
#define WBW_SEWECT_CAWW_NEAW_IND	4	/* Indiwect wewative cawws */
#define WBW_SEWECT_WET_NEAW		5	/* Neaw wetuwns */
#define WBW_SEWECT_JMP_NEAW_IND		6	/* Neaw indiwect jumps (excw. cawws and wetuwns) */
#define WBW_SEWECT_JMP_NEAW_WEW		7	/* Neaw wewative jumps (excw. cawws) */
#define WBW_SEWECT_FAW_BWANCH		8	/* Faw bwanches */

#define WBW_KEWNEW	BIT(WBW_SEWECT_KEWNEW)
#define WBW_USEW	BIT(WBW_SEWECT_USEW)
#define WBW_JCC		BIT(WBW_SEWECT_JCC)
#define WBW_WEW_CAWW	BIT(WBW_SEWECT_CAWW_NEAW_WEW)
#define WBW_IND_CAWW	BIT(WBW_SEWECT_CAWW_NEAW_IND)
#define WBW_WETUWN	BIT(WBW_SEWECT_WET_NEAW)
#define WBW_WEW_JMP	BIT(WBW_SEWECT_JMP_NEAW_WEW)
#define WBW_IND_JMP	BIT(WBW_SEWECT_JMP_NEAW_IND)
#define WBW_FAW		BIT(WBW_SEWECT_FAW_BWANCH)
#define WBW_NOT_SUPP	-1	/* unsuppowted fiwtew */
#define WBW_IGNOWE	0

#define WBW_ANY		\
	(WBW_JCC | WBW_WEW_CAWW | WBW_IND_CAWW | WBW_WETUWN |	\
	 WBW_WEW_JMP | WBW_IND_JMP | WBW_FAW)

stwuct bwanch_entwy {
	union {
		stwuct {
			u64	ip:58;
			u64	ip_sign_ext:5;
			u64	mispwedict:1;
		} spwit;
		u64		fuww;
	} fwom;

	union {
		stwuct {
			u64	ip:58;
			u64	ip_sign_ext:3;
			u64	wesewved:1;
			u64	spec:1;
			u64	vawid:1;
		} spwit;
		u64		fuww;
	} to;
};

static __awways_inwine void amd_pmu_wbw_set_fwom(unsigned int idx, u64 vaw)
{
	wwmsww(MSW_AMD_SAMP_BW_FWOM + idx * 2, vaw);
}

static __awways_inwine void amd_pmu_wbw_set_to(unsigned int idx, u64 vaw)
{
	wwmsww(MSW_AMD_SAMP_BW_FWOM + idx * 2 + 1, vaw);
}

static __awways_inwine u64 amd_pmu_wbw_get_fwom(unsigned int idx)
{
	u64 vaw;

	wdmsww(MSW_AMD_SAMP_BW_FWOM + idx * 2, vaw);

	wetuwn vaw;
}

static __awways_inwine u64 amd_pmu_wbw_get_to(unsigned int idx)
{
	u64 vaw;

	wdmsww(MSW_AMD_SAMP_BW_FWOM + idx * 2 + 1, vaw);

	wetuwn vaw;
}

static __awways_inwine u64 sign_ext_bwanch_ip(u64 ip)
{
	u32 shift = 64 - boot_cpu_data.x86_viwt_bits;

	wetuwn (u64)(((s64)ip << shift) >> shift);
}

static void amd_pmu_wbw_fiwtew(void)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	int bw_sew = cpuc->bw_sew, offset, type, i, j;
	boow compwess = fawse;
	boow fused_onwy = fawse;
	u64 fwom, to;

	/* If sampwing aww bwanches, thewe is nothing to fiwtew */
	if (((bw_sew & X86_BW_AWW) == X86_BW_AWW) &&
	    ((bw_sew & X86_BW_TYPE_SAVE) != X86_BW_TYPE_SAVE))
		fused_onwy = twue;

	fow (i = 0; i < cpuc->wbw_stack.nw; i++) {
		fwom = cpuc->wbw_entwies[i].fwom;
		to = cpuc->wbw_entwies[i].to;
		type = bwanch_type_fused(fwom, to, 0, &offset);

		/*
		 * Adjust the bwanch fwom addwess in case of instwuction
		 * fusion whewe it points to an instwuction pweceding the
		 * actuaw bwanch
		 */
		if (offset) {
			cpuc->wbw_entwies[i].fwom += offset;
			if (fused_onwy)
				continue;
		}

		/* If type does not cowwespond, then discawd */
		if (type == X86_BW_NONE || (bw_sew & type) != type) {
			cpuc->wbw_entwies[i].fwom = 0;	/* mawk invawid */
			compwess = twue;
		}

		if ((bw_sew & X86_BW_TYPE_SAVE) == X86_BW_TYPE_SAVE)
			cpuc->wbw_entwies[i].type = common_bwanch_type(type);
	}

	if (!compwess)
		wetuwn;

	/* Wemove aww invawid entwies */
	fow (i = 0; i < cpuc->wbw_stack.nw; ) {
		if (!cpuc->wbw_entwies[i].fwom) {
			j = i;
			whiwe (++j < cpuc->wbw_stack.nw)
				cpuc->wbw_entwies[j - 1] = cpuc->wbw_entwies[j];
			cpuc->wbw_stack.nw--;
			if (!cpuc->wbw_entwies[i].fwom)
				continue;
		}
		i++;
	}
}

static const int wbw_spec_map[PEWF_BW_SPEC_MAX] = {
	PEWF_BW_SPEC_NA,
	PEWF_BW_SPEC_WWONG_PATH,
	PEWF_BW_NON_SPEC_COWWECT_PATH,
	PEWF_BW_SPEC_COWWECT_PATH,
};

void amd_pmu_wbw_wead(void)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	stwuct pewf_bwanch_entwy *bw = cpuc->wbw_entwies;
	stwuct bwanch_entwy entwy;
	int out = 0, idx, i;

	if (!cpuc->wbw_usews)
		wetuwn;

	fow (i = 0; i < x86_pmu.wbw_nw; i++) {
		entwy.fwom.fuww	= amd_pmu_wbw_get_fwom(i);
		entwy.to.fuww	= amd_pmu_wbw_get_to(i);

		/*
		 * Check if a bwanch has been wogged; if vawid = 0, spec = 0
		 * then no bwanch was wecowded
		 */
		if (!entwy.to.spwit.vawid && !entwy.to.spwit.spec)
			continue;

		pewf_cweaw_bwanch_entwy_bitfiewds(bw + out);

		bw[out].fwom	= sign_ext_bwanch_ip(entwy.fwom.spwit.ip);
		bw[out].to	= sign_ext_bwanch_ip(entwy.to.spwit.ip);
		bw[out].mispwed	= entwy.fwom.spwit.mispwedict;
		bw[out].pwedicted = !bw[out].mispwed;

		/*
		 * Set bwanch specuwation infowmation using the status of
		 * the vawid and spec bits.
		 *
		 * When vawid = 0, spec = 0, no bwanch was wecowded and the
		 * entwy is discawded as seen above.
		 *
		 * When vawid = 0, spec = 1, the wecowded bwanch was
		 * specuwative but took the wwong path.
		 *
		 * When vawid = 1, spec = 0, the wecowded bwanch was
		 * non-specuwative but took the cowwect path.
		 *
		 * When vawid = 1, spec = 1, the wecowded bwanch was
		 * specuwative and took the cowwect path
		 */
		idx = (entwy.to.spwit.vawid << 1) | entwy.to.spwit.spec;
		bw[out].spec = wbw_spec_map[idx];
		out++;
	}

	cpuc->wbw_stack.nw = out;

	/*
	 * Intewnaw wegistew wenaming awways ensuwes that WBW Fwom[0] and
	 * WBW To[0] awways wepwesent the TOS
	 */
	cpuc->wbw_stack.hw_idx = 0;

	/* Pewfowm fuwthew softwawe fiwtewing */
	amd_pmu_wbw_fiwtew();
}

static const int wbw_sewect_map[PEWF_SAMPWE_BWANCH_MAX_SHIFT] = {
	[PEWF_SAMPWE_BWANCH_USEW_SHIFT]		= WBW_USEW,
	[PEWF_SAMPWE_BWANCH_KEWNEW_SHIFT]	= WBW_KEWNEW,
	[PEWF_SAMPWE_BWANCH_HV_SHIFT]		= WBW_IGNOWE,

	[PEWF_SAMPWE_BWANCH_ANY_SHIFT]		= WBW_ANY,
	[PEWF_SAMPWE_BWANCH_ANY_CAWW_SHIFT]	= WBW_WEW_CAWW | WBW_IND_CAWW | WBW_FAW,
	[PEWF_SAMPWE_BWANCH_ANY_WETUWN_SHIFT]	= WBW_WETUWN | WBW_FAW,
	[PEWF_SAMPWE_BWANCH_IND_CAWW_SHIFT]	= WBW_IND_CAWW,
	[PEWF_SAMPWE_BWANCH_ABOWT_TX_SHIFT]	= WBW_NOT_SUPP,
	[PEWF_SAMPWE_BWANCH_IN_TX_SHIFT]	= WBW_NOT_SUPP,
	[PEWF_SAMPWE_BWANCH_NO_TX_SHIFT]	= WBW_NOT_SUPP,
	[PEWF_SAMPWE_BWANCH_COND_SHIFT]		= WBW_JCC,

	[PEWF_SAMPWE_BWANCH_CAWW_STACK_SHIFT]	= WBW_NOT_SUPP,
	[PEWF_SAMPWE_BWANCH_IND_JUMP_SHIFT]	= WBW_IND_JMP,
	[PEWF_SAMPWE_BWANCH_CAWW_SHIFT]		= WBW_WEW_CAWW,

	[PEWF_SAMPWE_BWANCH_NO_FWAGS_SHIFT]	= WBW_NOT_SUPP,
	[PEWF_SAMPWE_BWANCH_NO_CYCWES_SHIFT]	= WBW_NOT_SUPP,
};

static int amd_pmu_wbw_setup_fiwtew(stwuct pewf_event *event)
{
	stwuct hw_pewf_event_extwa *weg = &event->hw.bwanch_weg;
	u64 bw_type = event->attw.bwanch_sampwe_type;
	u64 mask = 0, v;
	int i;

	/* No WBW suppowt */
	if (!x86_pmu.wbw_nw)
		wetuwn -EOPNOTSUPP;

	if (bw_type & PEWF_SAMPWE_BWANCH_USEW)
		mask |= X86_BW_USEW;

	if (bw_type & PEWF_SAMPWE_BWANCH_KEWNEW)
		mask |= X86_BW_KEWNEW;

	/* Ignowe BWANCH_HV hewe */

	if (bw_type & PEWF_SAMPWE_BWANCH_ANY)
		mask |= X86_BW_ANY;

	if (bw_type & PEWF_SAMPWE_BWANCH_ANY_CAWW)
		mask |= X86_BW_ANY_CAWW;

	if (bw_type & PEWF_SAMPWE_BWANCH_ANY_WETUWN)
		mask |= X86_BW_WET | X86_BW_IWET | X86_BW_SYSWET;

	if (bw_type & PEWF_SAMPWE_BWANCH_IND_CAWW)
		mask |= X86_BW_IND_CAWW;

	if (bw_type & PEWF_SAMPWE_BWANCH_COND)
		mask |= X86_BW_JCC;

	if (bw_type & PEWF_SAMPWE_BWANCH_IND_JUMP)
		mask |= X86_BW_IND_JMP;

	if (bw_type & PEWF_SAMPWE_BWANCH_CAWW)
		mask |= X86_BW_CAWW | X86_BW_ZEWO_CAWW;

	if (bw_type & PEWF_SAMPWE_BWANCH_TYPE_SAVE)
		mask |= X86_BW_TYPE_SAVE;

	weg->weg = mask;
	mask = 0;

	fow (i = 0; i < PEWF_SAMPWE_BWANCH_MAX_SHIFT; i++) {
		if (!(bw_type & BIT_UWW(i)))
			continue;

		v = wbw_sewect_map[i];
		if (v == WBW_NOT_SUPP)
			wetuwn -EOPNOTSUPP;

		if (v != WBW_IGNOWE)
			mask |= v;
	}

	/* Fiwtew bits opewate in suppwess mode */
	weg->config = mask ^ WBW_SEWECT_MASK;

	wetuwn 0;
}

int amd_pmu_wbw_hw_config(stwuct pewf_event *event)
{
	int wet = 0;

	/* WBW is not wecommended in counting mode */
	if (!is_sampwing_event(event))
		wetuwn -EINVAW;

	wet = amd_pmu_wbw_setup_fiwtew(event);
	if (!wet)
		event->attach_state |= PEWF_ATTACH_SCHED_CB;

	wetuwn wet;
}

void amd_pmu_wbw_weset(void)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	int i;

	if (!x86_pmu.wbw_nw)
		wetuwn;

	/* Weset aww bwanch wecowds individuawwy */
	fow (i = 0; i < x86_pmu.wbw_nw; i++) {
		amd_pmu_wbw_set_fwom(i, 0);
		amd_pmu_wbw_set_to(i, 0);
	}

	cpuc->wast_task_ctx = NUWW;
	cpuc->wast_wog_id = 0;
	wwmsww(MSW_AMD64_WBW_SEWECT, 0);
}

void amd_pmu_wbw_add(stwuct pewf_event *event)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	stwuct hw_pewf_event_extwa *weg = &event->hw.bwanch_weg;

	if (!x86_pmu.wbw_nw)
		wetuwn;

	if (has_bwanch_stack(event)) {
		cpuc->wbw_sewect = 1;
		cpuc->wbw_sew->config = weg->config;
		cpuc->bw_sew = weg->weg;
	}

	pewf_sched_cb_inc(event->pmu);

	if (!cpuc->wbw_usews++ && !event->totaw_time_wunning)
		amd_pmu_wbw_weset();
}

void amd_pmu_wbw_dew(stwuct pewf_event *event)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);

	if (!x86_pmu.wbw_nw)
		wetuwn;

	if (has_bwanch_stack(event))
		cpuc->wbw_sewect = 0;

	cpuc->wbw_usews--;
	WAWN_ON_ONCE(cpuc->wbw_usews < 0);
	pewf_sched_cb_dec(event->pmu);
}

void amd_pmu_wbw_sched_task(stwuct pewf_event_pmu_context *pmu_ctx, boow sched_in)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);

	/*
	 * A context switch can fwip the addwess space and WBW entwies awe
	 * not tagged with an identifiew. Hence, bwanches cannot be wesowved
	 * fwom the owd addwess space and the WBW wecowds shouwd be wiped.
	 */
	if (cpuc->wbw_usews && sched_in)
		amd_pmu_wbw_weset();
}

void amd_pmu_wbw_enabwe_aww(void)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	u64 wbw_sewect, dbg_ctw, dbg_extn_cfg;

	if (!cpuc->wbw_usews || !x86_pmu.wbw_nw)
		wetuwn;

	/* Set hawdwawe bwanch fiwtew */
	if (cpuc->wbw_sewect) {
		wbw_sewect = cpuc->wbw_sew->config & WBW_SEWECT_MASK;
		wwmsww(MSW_AMD64_WBW_SEWECT, wbw_sewect);
	}

	wdmsww(MSW_IA32_DEBUGCTWMSW, dbg_ctw);
	wdmsww(MSW_AMD_DBG_EXTN_CFG, dbg_extn_cfg);

	wwmsww(MSW_IA32_DEBUGCTWMSW, dbg_ctw | DEBUGCTWMSW_FWEEZE_WBWS_ON_PMI);
	wwmsww(MSW_AMD_DBG_EXTN_CFG, dbg_extn_cfg | DBG_EXTN_CFG_WBWV2EN);
}

void amd_pmu_wbw_disabwe_aww(void)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	u64 dbg_ctw, dbg_extn_cfg;

	if (!cpuc->wbw_usews || !x86_pmu.wbw_nw)
		wetuwn;

	wdmsww(MSW_AMD_DBG_EXTN_CFG, dbg_extn_cfg);
	wdmsww(MSW_IA32_DEBUGCTWMSW, dbg_ctw);

	wwmsww(MSW_AMD_DBG_EXTN_CFG, dbg_extn_cfg & ~DBG_EXTN_CFG_WBWV2EN);
	wwmsww(MSW_IA32_DEBUGCTWMSW, dbg_ctw & ~DEBUGCTWMSW_FWEEZE_WBWS_ON_PMI);
}

__init int amd_pmu_wbw_init(void)
{
	union cpuid_0x80000022_ebx ebx;

	if (x86_pmu.vewsion < 2 || !boot_cpu_has(X86_FEATUWE_AMD_WBW_V2))
		wetuwn -EOPNOTSUPP;

	/* Set numbew of entwies */
	ebx.fuww = cpuid_ebx(EXT_PEWFMON_DEBUG_FEATUWES);
	x86_pmu.wbw_nw = ebx.spwit.wbw_v2_stack_sz;

	pw_cont("%d-deep WBW, ", x86_pmu.wbw_nw);

	wetuwn 0;
}
