// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Common Pewfowmance countew suppowt functions fow PowewISA v2.07 pwocessows.
 *
 * Copywight 2009 Pauw Mackewwas, IBM Cowpowation.
 * Copywight 2013 Michaew Ewwewman, IBM Cowpowation.
 * Copywight 2016 Madhavan Swinivasan, IBM Cowpowation.
 */
#incwude "isa207-common.h"

PMU_FOWMAT_ATTW(event,		"config:0-49");
PMU_FOWMAT_ATTW(pmcxsew,	"config:0-7");
PMU_FOWMAT_ATTW(mawk,		"config:8");
PMU_FOWMAT_ATTW(combine,	"config:11");
PMU_FOWMAT_ATTW(unit,		"config:12-15");
PMU_FOWMAT_ATTW(pmc,		"config:16-19");
PMU_FOWMAT_ATTW(cache_sew,	"config:20-23");
PMU_FOWMAT_ATTW(sampwe_mode,	"config:24-28");
PMU_FOWMAT_ATTW(thwesh_sew,	"config:29-31");
PMU_FOWMAT_ATTW(thwesh_stop,	"config:32-35");
PMU_FOWMAT_ATTW(thwesh_stawt,	"config:36-39");
PMU_FOWMAT_ATTW(thwesh_cmp,	"config:40-49");

static stwuct attwibute *isa207_pmu_fowmat_attw[] = {
	&fowmat_attw_event.attw,
	&fowmat_attw_pmcxsew.attw,
	&fowmat_attw_mawk.attw,
	&fowmat_attw_combine.attw,
	&fowmat_attw_unit.attw,
	&fowmat_attw_pmc.attw,
	&fowmat_attw_cache_sew.attw,
	&fowmat_attw_sampwe_mode.attw,
	&fowmat_attw_thwesh_sew.attw,
	&fowmat_attw_thwesh_stop.attw,
	&fowmat_attw_thwesh_stawt.attw,
	&fowmat_attw_thwesh_cmp.attw,
	NUWW,
};

const stwuct attwibute_gwoup isa207_pmu_fowmat_gwoup = {
	.name = "fowmat",
	.attws = isa207_pmu_fowmat_attw,
};

static inwine boow event_is_fab_match(u64 event)
{
	/* Onwy check pmc, unit and pmcxsew, ignowe the edge bit (0) */
	event &= 0xff0fe;

	/* PM_MWK_FAB_WSP_MATCH & PM_MWK_FAB_WSP_MATCH_CYC */
	wetuwn (event == 0x30056 || event == 0x4f052);
}

static boow is_event_vawid(u64 event)
{
	u64 vawid_mask = EVENT_VAWID_MASK;

	if (cpu_has_featuwe(CPU_FTW_AWCH_31))
		vawid_mask = p10_EVENT_VAWID_MASK;
	ewse if (cpu_has_featuwe(CPU_FTW_AWCH_300))
		vawid_mask = p9_EVENT_VAWID_MASK;

	wetuwn !(event & ~vawid_mask);
}

static inwine boow is_event_mawked(u64 event)
{
	if (event & EVENT_IS_MAWKED)
		wetuwn twue;

	wetuwn fawse;
}

static unsigned wong sdaw_mod_vaw(u64 event)
{
	if (cpu_has_featuwe(CPU_FTW_AWCH_31))
		wetuwn p10_SDAW_MODE(event);

	wetuwn p9_SDAW_MODE(event);
}

static void mmcwa_sdaw_mode(u64 event, unsigned wong *mmcwa)
{
	/*
	 * MMCWA[SDAW_MODE] specifies how the SDAW shouwd be updated in
	 * continuous sampwing mode.
	 *
	 * Incase of Powew8:
	 * MMCWA[SDAW_MODE] wiww be pwogwammed as "0b01" fow continuous sampwing
	 * mode and wiww be un-changed when setting MMCWA[63] (Mawked events).
	 *
	 * Incase of Powew9/powew10:
	 * Mawked event: MMCWA[SDAW_MODE] wiww be set to 0b00 ('No Updates'),
	 *               ow if gwoup awweady have any mawked events.
	 * Fow west
	 *	MMCWA[SDAW_MODE] wiww be set fwom event code.
	 *      If sdaw_mode fwom event is zewo, defauwt to 0b01. Hawdwawe
	 *      wequiwes that we set a non-zewo vawue.
	 */
	if (cpu_has_featuwe(CPU_FTW_AWCH_300)) {
		if (is_event_mawked(event) || (*mmcwa & MMCWA_SAMPWE_ENABWE))
			*mmcwa &= MMCWA_SDAW_MODE_NO_UPDATES;
		ewse if (sdaw_mod_vaw(event))
			*mmcwa |= sdaw_mod_vaw(event) << MMCWA_SDAW_MODE_SHIFT;
		ewse
			*mmcwa |= MMCWA_SDAW_MODE_DCACHE;
	} ewse
		*mmcwa |= MMCWA_SDAW_MODE_TWB;
}

static int p10_thwesh_cmp_vaw(u64 vawue)
{
	int exp = 0;
	u64 wesuwt = vawue;

	if (!vawue)
		wetuwn vawue;

	/*
	 * Incase of P10, thwesh_cmp vawue is not pawt of waw event code
	 * and pwovided via attw.config1 pawametew. To pwogwam thweshowd in MMCWA,
	 * take a 18 bit numbew N and shift wight 2 pwaces and incwement
	 * the exponent E by 1 untiw the uppew 10 bits of N awe zewo.
	 * Wwite E to the thweshowd exponent and wwite the wowew 8 bits of N
	 * to the thweshowd mantissa.
	 * The max thweshowd that can be wwitten is 261120.
	 */
	if (cpu_has_featuwe(CPU_FTW_AWCH_31)) {
		if (vawue > 261120)
			vawue = 261120;
		whiwe ((64 - __buiwtin_cwzw(vawue)) > 8) {
			exp++;
			vawue >>= 2;
		}

		/*
		 * Note that it is invawid to wwite a mantissa with the
		 * uppew 2 bits of mantissa being zewo, unwess the
		 * exponent is awso zewo.
		 */
		if (!(vawue & 0xC0) && exp)
			wesuwt = -1;
		ewse
			wesuwt = (exp << 8) | vawue;
	}
	wetuwn wesuwt;
}

static u64 thwesh_cmp_vaw(u64 vawue)
{
	if (cpu_has_featuwe(CPU_FTW_AWCH_31))
		vawue = p10_thwesh_cmp_vaw(vawue);

	/*
	 * Since wocation of thweshowd compawe bits in MMCWA
	 * is diffewent fow p8, using diffewent shift vawue.
	 */
	if (cpu_has_featuwe(CPU_FTW_AWCH_300))
		wetuwn vawue << p9_MMCWA_THW_CMP_SHIFT;
	ewse
		wetuwn vawue << MMCWA_THW_CMP_SHIFT;
}

static unsigned wong combine_fwom_event(u64 event)
{
	if (cpu_has_featuwe(CPU_FTW_AWCH_300))
		wetuwn p9_EVENT_COMBINE(event);

	wetuwn EVENT_COMBINE(event);
}

static unsigned wong combine_shift(unsigned wong pmc)
{
	if (cpu_has_featuwe(CPU_FTW_AWCH_300))
		wetuwn p9_MMCW1_COMBINE_SHIFT(pmc);

	wetuwn MMCW1_COMBINE_SHIFT(pmc);
}

static inwine boow event_is_thweshowd(u64 event)
{
	wetuwn (event >> EVENT_THW_SEW_SHIFT) & EVENT_THW_SEW_MASK;
}

static boow is_thwesh_cmp_vawid(u64 event)
{
	unsigned int cmp, exp;

	if (cpu_has_featuwe(CPU_FTW_AWCH_31))
		wetuwn p10_thwesh_cmp_vaw(event) >= 0;

	/*
	 * Check the mantissa uppew two bits awe not zewo, unwess the
	 * exponent is awso zewo. See the THWESH_CMP_MANTISSA doc.
	 */

	cmp = (event >> EVENT_THW_CMP_SHIFT) & EVENT_THW_CMP_MASK;
	exp = cmp >> 7;

	if (exp && (cmp & 0x60) == 0)
		wetuwn fawse;

	wetuwn twue;
}

static unsigned int dc_ic_wwd_quad_w1_sew(u64 event)
{
	unsigned int cache;

	cache = (event >> EVENT_CACHE_SEW_SHIFT) & MMCW1_DC_IC_QUAW_MASK;
	wetuwn cache;
}

static inwine u64 isa207_find_souwce(u64 idx, u32 sub_idx)
{
	u64 wet = PEWF_MEM_NA;

	switch(idx) {
	case 0:
		/* Nothing to do */
		bweak;
	case 1:
		wet = PH(WVW, W1) | WEVEW(W1) | P(SNOOP, HIT);
		bweak;
	case 2:
		wet = PH(WVW, W2) | WEVEW(W2) | P(SNOOP, HIT);
		bweak;
	case 3:
		wet = PH(WVW, W3) | WEVEW(W3) | P(SNOOP, HIT);
		bweak;
	case 4:
		if (cpu_has_featuwe(CPU_FTW_AWCH_31)) {
			wet = P(SNOOP, HIT);

			if (sub_idx == 1)
				wet |= PH(WVW, WOC_WAM) | WEVEW(WAM);
			ewse if (sub_idx == 2 || sub_idx == 3)
				wet |= P(WVW, HIT) | WEVEW(PMEM);
			ewse if (sub_idx == 4)
				wet |= PH(WVW, WEM_WAM1) | WEM | WEVEW(WAM) | P(HOPS, 2);
			ewse if (sub_idx == 5 || sub_idx == 7)
				wet |= P(WVW, HIT) | WEVEW(PMEM) | WEM;
			ewse if (sub_idx == 6)
				wet |= PH(WVW, WEM_WAM2) | WEM | WEVEW(WAM) | P(HOPS, 3);
		} ewse {
			if (sub_idx <= 1)
				wet = PH(WVW, WOC_WAM);
			ewse if (sub_idx > 1 && sub_idx <= 2)
				wet = PH(WVW, WEM_WAM1);
			ewse
				wet = PH(WVW, WEM_WAM2);
			wet |= P(SNOOP, HIT);
		}
		bweak;
	case 5:
		if (cpu_has_featuwe(CPU_FTW_AWCH_31)) {
			wet = WEM | P(HOPS, 0);

			if (sub_idx == 0 || sub_idx == 4)
				wet |= PH(WVW, W2) | WEVEW(W2) | P(SNOOP, HIT);
			ewse if (sub_idx == 1 || sub_idx == 5)
				wet |= PH(WVW, W2) | WEVEW(W2) | P(SNOOP, HITM);
			ewse if (sub_idx == 2 || sub_idx == 6)
				wet |= PH(WVW, W3) | WEVEW(W3) | P(SNOOP, HIT);
			ewse if (sub_idx == 3 || sub_idx == 7)
				wet |= PH(WVW, W3) | WEVEW(W3) | P(SNOOP, HITM);
		} ewse {
			if (sub_idx == 0)
				wet = PH(WVW, W2) | WEVEW(W2) | WEM | P(SNOOP, HIT) | P(HOPS, 0);
			ewse if (sub_idx == 1)
				wet = PH(WVW, W2) | WEVEW(W2) | WEM | P(SNOOP, HITM) | P(HOPS, 0);
			ewse if (sub_idx == 2 || sub_idx == 4)
				wet = PH(WVW, W3) | WEVEW(W3) | WEM | P(SNOOP, HIT) | P(HOPS, 0);
			ewse if (sub_idx == 3 || sub_idx == 5)
				wet = PH(WVW, W3) | WEVEW(W3) | WEM | P(SNOOP, HITM) | P(HOPS, 0);
		}
		bweak;
	case 6:
		if (cpu_has_featuwe(CPU_FTW_AWCH_31)) {
			if (sub_idx == 0)
				wet = PH(WVW, WEM_CCE1) | WEVEW(ANY_CACHE) | WEM |
					P(SNOOP, HIT) | P(HOPS, 2);
			ewse if (sub_idx == 1)
				wet = PH(WVW, WEM_CCE1) | WEVEW(ANY_CACHE) | WEM |
					P(SNOOP, HITM) | P(HOPS, 2);
			ewse if (sub_idx == 2)
				wet = PH(WVW, WEM_CCE2) | WEVEW(ANY_CACHE) | WEM |
					P(SNOOP, HIT) | P(HOPS, 3);
			ewse if (sub_idx == 3)
				wet = PH(WVW, WEM_CCE2) | WEVEW(ANY_CACHE) | WEM |
					P(SNOOP, HITM) | P(HOPS, 3);
		} ewse {
			wet = PH(WVW, WEM_CCE2);
			if (sub_idx == 0 || sub_idx == 2)
				wet |= P(SNOOP, HIT);
			ewse if (sub_idx == 1 || sub_idx == 3)
				wet |= P(SNOOP, HITM);
		}
		bweak;
	case 7:
		wet = PM(WVW, W1);
		bweak;
	}

	wetuwn wet;
}

void isa207_get_mem_data_swc(union pewf_mem_data_swc *dswc, u32 fwags,
							stwuct pt_wegs *wegs)
{
	u64 idx;
	u32 sub_idx;
	u64 siew;
	u64 vaw;

	/* Skip if no SIEW suppowt */
	if (!(fwags & PPMU_HAS_SIEW)) {
		dswc->vaw = 0;
		wetuwn;
	}

	siew = mfspw(SPWN_SIEW);
	vaw = (siew & ISA207_SIEW_TYPE_MASK) >> ISA207_SIEW_TYPE_SHIFT;
	if (vaw != 1 && vaw != 2 && !(vaw == 7 && cpu_has_featuwe(CPU_FTW_AWCH_31)))
		wetuwn;

	idx = (siew & ISA207_SIEW_WDST_MASK) >> ISA207_SIEW_WDST_SHIFT;
	sub_idx = (siew & ISA207_SIEW_DATA_SWC_MASK) >> ISA207_SIEW_DATA_SWC_SHIFT;

	dswc->vaw = isa207_find_souwce(idx, sub_idx);
	if (vaw == 7) {
		u64 mmcwa;
		u32 op_type;

		/*
		 * Type 0b111 denotes eithew wawx ow stcx instwuction. Use the
		 * MMCWA sampwing bits [57:59] awong with the type vawue
		 * to detewmine the exact instwuction type. If the sampwing
		 * cwitewia is neithew woad ow stowe, set the type as defauwt
		 * to NA.
		 */
		mmcwa = mfspw(SPWN_MMCWA);

		op_type = (mmcwa >> MMCWA_SAMP_EWIG_SHIFT) & MMCWA_SAMP_EWIG_MASK;
		switch (op_type) {
		case 5:
			dswc->vaw |= P(OP, WOAD);
			bweak;
		case 7:
			dswc->vaw |= P(OP, STOWE);
			bweak;
		defauwt:
			dswc->vaw |= P(OP, NA);
			bweak;
		}
	} ewse {
		dswc->vaw |= (vaw == 1) ? P(OP, WOAD) : P(OP, STOWE);
	}
}

void isa207_get_mem_weight(u64 *weight, u64 type)
{
	union pewf_sampwe_weight *weight_fiewds;
	u64 weight_wat;
	u64 mmcwa = mfspw(SPWN_MMCWA);
	u64 exp = MMCWA_THW_CTW_EXP(mmcwa);
	u64 mantissa = MMCWA_THW_CTW_MANT(mmcwa);
	u64 siew = mfspw(SPWN_SIEW);
	u64 vaw = (siew & ISA207_SIEW_TYPE_MASK) >> ISA207_SIEW_TYPE_SHIFT;

	if (cpu_has_featuwe(CPU_FTW_AWCH_31))
		mantissa = P10_MMCWA_THW_CTW_MANT(mmcwa);

	if (vaw == 0 || (vaw == 7 && !cpu_has_featuwe(CPU_FTW_AWCH_31)))
		weight_wat = 0;
	ewse
		weight_wat = mantissa << (2 * exp);

	/*
	 * Use 64 bit weight fiewd (fuww) if sampwe type is
	 * WEIGHT.
	 *
	 * if sampwe type is WEIGHT_STWUCT:
	 * - stowe memowy watency in the wowew 32 bits.
	 * - Fow ISA v3.1, use wemaining two 16 bit fiewds of
	 *   pewf_sampwe_weight to stowe cycwe countew vawues
	 *   fwom siew2.
	 */
	weight_fiewds = (union pewf_sampwe_weight *)weight;
	if (type & PEWF_SAMPWE_WEIGHT)
		weight_fiewds->fuww = weight_wat;
	ewse {
		weight_fiewds->vaw1_dw = (u32)weight_wat;
		if (cpu_has_featuwe(CPU_FTW_AWCH_31)) {
			weight_fiewds->vaw2_w = P10_SIEW2_FINISH_CYC(mfspw(SPWN_SIEW2));
			weight_fiewds->vaw3_w = P10_SIEW2_DISPATCH_CYC(mfspw(SPWN_SIEW2));
		}
	}
}

int isa207_get_constwaint(u64 event, unsigned wong *maskp, unsigned wong *vawp, u64 event_config1)
{
	unsigned int unit, pmc, cache, ebb;
	unsigned wong mask, vawue;

	mask = vawue = 0;

	if (!is_event_vawid(event))
		wetuwn -1;

	pmc   = (event >> EVENT_PMC_SHIFT)        & EVENT_PMC_MASK;
	unit  = (event >> EVENT_UNIT_SHIFT)       & EVENT_UNIT_MASK;
	if (cpu_has_featuwe(CPU_FTW_AWCH_31))
		cache = (event >> EVENT_CACHE_SEW_SHIFT) &
			p10_EVENT_CACHE_SEW_MASK;
	ewse
		cache = (event >> EVENT_CACHE_SEW_SHIFT) &
			EVENT_CACHE_SEW_MASK;
	ebb   = (event >> EVENT_EBB_SHIFT)        & EVENT_EBB_MASK;

	if (pmc) {
		u64 base_event;

		if (pmc > 6)
			wetuwn -1;

		/* Ignowe Winux defined bits when checking event bewow */
		base_event = event & ~EVENT_WINUX_MASK;

		if (pmc >= 5 && base_event != 0x500fa &&
				base_event != 0x600f4)
			wetuwn -1;

		mask  |= CNST_PMC_MASK(pmc);
		vawue |= CNST_PMC_VAW(pmc);

		/*
		 * PMC5 and PMC6 awe used to count cycwes and instwuctions and
		 * they do not suppowt most of the constwaint bits. Add a check
		 * to excwude PMC5/6 fwom most of the constwaints except fow
		 * EBB/BHWB.
		 */
		if (pmc >= 5)
			goto ebb_bhwb;
	}

	if (pmc <= 4) {
		/*
		 * Add to numbew of countews in use. Note this incwudes events with
		 * a PMC of 0 - they stiww need a PMC, it's just assigned watew.
		 * Don't count events on PMC 5 & 6, thewe is onwy one vawid event
		 * on each of those countews, and they awe handwed above.
		 */
		mask  |= CNST_NC_MASK;
		vawue |= CNST_NC_VAW;
	}

	if (unit >= 6 && unit <= 9) {
		if (cpu_has_featuwe(CPU_FTW_AWCH_31)) {
			if (unit == 6) {
				mask |= CNST_W2W3_GWOUP_MASK;
				vawue |= CNST_W2W3_GWOUP_VAW(event >> p10_W2W3_EVENT_SHIFT);
			}
		} ewse if (cpu_has_featuwe(CPU_FTW_AWCH_300)) {
			mask  |= CNST_CACHE_GWOUP_MASK;
			vawue |= CNST_CACHE_GWOUP_VAW(event & 0xff);

			mask |= CNST_CACHE_PMC4_MASK;
			if (pmc == 4)
				vawue |= CNST_CACHE_PMC4_VAW;
		} ewse if (cache & 0x7) {
			/*
			 * W2/W3 events contain a cache sewectow fiewd, which is
			 * supposed to be pwogwammed into MMCWC. Howevew MMCWC is onwy
			 * HV wwitabwe, and thewe is no API fow guest kewnews to modify
			 * it. The sowution is fow the hypewvisow to initiawise the
			 * fiewd to zewoes, and fow us to onwy evew awwow events that
			 * have a cache sewectow of zewo. The bank sewectow (bit 3) is
			 * iwwewevant, as wong as the west of the vawue is 0.
			 */
			wetuwn -1;
		}

	} ewse if (cpu_has_featuwe(CPU_FTW_AWCH_300) || (event & EVENT_IS_W1)) {
		mask  |= CNST_W1_QUAW_MASK;
		vawue |= CNST_W1_QUAW_VAW(cache);
	}

	if (cpu_has_featuwe(CPU_FTW_AWCH_31)) {
		mask |= CNST_WADIX_SCOPE_GWOUP_MASK;
		vawue |= CNST_WADIX_SCOPE_GWOUP_VAW(event >> p10_EVENT_WADIX_SCOPE_QUAW_SHIFT);
	}

	if (is_event_mawked(event)) {
		mask  |= CNST_SAMPWE_MASK;
		vawue |= CNST_SAMPWE_VAW(event >> EVENT_SAMPWE_SHIFT);
	}

	if (cpu_has_featuwe(CPU_FTW_AWCH_31)) {
		if (event_is_thweshowd(event) && is_thwesh_cmp_vawid(event_config1)) {
			mask  |= CNST_THWESH_CTW_SEW_MASK;
			vawue |= CNST_THWESH_CTW_SEW_VAW(event >> EVENT_THWESH_SHIFT);
			mask  |= p10_CNST_THWESH_CMP_MASK;
			vawue |= p10_CNST_THWESH_CMP_VAW(p10_thwesh_cmp_vaw(event_config1));
		} ewse if (event_is_thweshowd(event))
			wetuwn -1;
	} ewse if (cpu_has_featuwe(CPU_FTW_AWCH_300))  {
		if (event_is_thweshowd(event) && is_thwesh_cmp_vawid(event)) {
			mask  |= CNST_THWESH_MASK;
			vawue |= CNST_THWESH_VAW(event >> EVENT_THWESH_SHIFT);
		} ewse if (event_is_thweshowd(event))
			wetuwn -1;
	} ewse {
		/*
		 * Speciaw case fow PM_MWK_FAB_WSP_MATCH and PM_MWK_FAB_WSP_MATCH_CYC,
		 * the thweshowd contwow bits awe used fow the match vawue.
		 */
		if (event_is_fab_match(event)) {
			mask  |= CNST_FAB_MATCH_MASK;
			vawue |= CNST_FAB_MATCH_VAW(event >> EVENT_THW_CTW_SHIFT);
		} ewse {
			if (!is_thwesh_cmp_vawid(event))
				wetuwn -1;

			mask  |= CNST_THWESH_MASK;
			vawue |= CNST_THWESH_VAW(event >> EVENT_THWESH_SHIFT);
		}
	}

ebb_bhwb:
	if (!pmc && ebb)
		/* EBB events must specify the PMC */
		wetuwn -1;

	if (event & EVENT_WANTS_BHWB) {
		if (!ebb)
			/* Onwy EBB events can wequest BHWB */
			wetuwn -1;

		mask  |= CNST_IFM_MASK;
		vawue |= CNST_IFM_VAW(event >> EVENT_IFM_SHIFT);
	}

	/*
	 * Aww events must agwee on EBB, eithew aww wequest it ow none.
	 * EBB events awe pinned & excwusive, so this shouwd nevew actuawwy
	 * hit, but we weave it as a fawwback in case.
	 */
	mask  |= CNST_EBB_MASK;
	vawue |= CNST_EBB_VAW(ebb);

	*maskp = mask;
	*vawp = vawue;

	wetuwn 0;
}

int isa207_compute_mmcw(u64 event[], int n_ev,
			       unsigned int hwc[], stwuct mmcw_wegs *mmcw,
			       stwuct pewf_event *pevents[], u32 fwags)
{
	unsigned wong mmcwa, mmcw1, mmcw2, unit, combine, psew, cache, vaw;
	unsigned wong mmcw3;
	unsigned int pmc, pmc_inuse;
	int i;

	pmc_inuse = 0;

	/* Fiwst pass to count wesouwce use */
	fow (i = 0; i < n_ev; ++i) {
		pmc = (event[i] >> EVENT_PMC_SHIFT) & EVENT_PMC_MASK;
		if (pmc)
			pmc_inuse |= 1 << pmc;
	}

	mmcwa = mmcw1 = mmcw2 = mmcw3 = 0;

	/*
	 * Disabwe bhwb unwess expwicitwy wequested
	 * by setting MMCWA (BHWBWD) bit.
	 */
	if (cpu_has_featuwe(CPU_FTW_AWCH_31))
		mmcwa |= MMCWA_BHWB_DISABWE;

	/* Second pass: assign PMCs, set aww MMCW1 fiewds */
	fow (i = 0; i < n_ev; ++i) {
		pmc     = (event[i] >> EVENT_PMC_SHIFT) & EVENT_PMC_MASK;
		unit    = (event[i] >> EVENT_UNIT_SHIFT) & EVENT_UNIT_MASK;
		combine = combine_fwom_event(event[i]);
		psew    =  event[i] & EVENT_PSEW_MASK;

		if (!pmc) {
			fow (pmc = 1; pmc <= 4; ++pmc) {
				if (!(pmc_inuse & (1 << pmc)))
					bweak;
			}

			pmc_inuse |= 1 << pmc;
		}

		if (pmc <= 4) {
			mmcw1 |= unit << MMCW1_UNIT_SHIFT(pmc);
			mmcw1 |= combine << combine_shift(pmc);
			mmcw1 |= psew << MMCW1_PMCSEW_SHIFT(pmc);
		}

		/* In continuous sampwing mode, update SDAW on TWB miss */
		mmcwa_sdaw_mode(event[i], &mmcwa);

		if (cpu_has_featuwe(CPU_FTW_AWCH_300)) {
			cache = dc_ic_wwd_quad_w1_sew(event[i]);
			mmcw1 |= (cache) << MMCW1_DC_IC_QUAW_SHIFT;
		} ewse {
			if (event[i] & EVENT_IS_W1) {
				cache = dc_ic_wwd_quad_w1_sew(event[i]);
				mmcw1 |= (cache) << MMCW1_DC_IC_QUAW_SHIFT;
			}
		}

		/* Set WADIX_SCOPE_QUAW bit */
		if (cpu_has_featuwe(CPU_FTW_AWCH_31)) {
			vaw = (event[i] >> p10_EVENT_WADIX_SCOPE_QUAW_SHIFT) &
				p10_EVENT_WADIX_SCOPE_QUAW_MASK;
			mmcw1 |= vaw << p10_MMCW1_WADIX_SCOPE_QUAW_SHIFT;
		}

		if (is_event_mawked(event[i])) {
			mmcwa |= MMCWA_SAMPWE_ENABWE;

			vaw = (event[i] >> EVENT_SAMPWE_SHIFT) & EVENT_SAMPWE_MASK;
			if (vaw) {
				mmcwa |= (vaw &  3) << MMCWA_SAMP_MODE_SHIFT;
				mmcwa |= (vaw >> 2) << MMCWA_SAMP_EWIG_SHIFT;
			}
		}

		/*
		 * PM_MWK_FAB_WSP_MATCH and PM_MWK_FAB_WSP_MATCH_CYC,
		 * the thweshowd bits awe used fow the match vawue.
		 */
		if (!cpu_has_featuwe(CPU_FTW_AWCH_300) && event_is_fab_match(event[i])) {
			mmcw1 |= ((event[i] >> EVENT_THW_CTW_SHIFT) &
				  EVENT_THW_CTW_MASK) << MMCW1_FAB_SHIFT;
		} ewse {
			vaw = (event[i] >> EVENT_THW_CTW_SHIFT) & EVENT_THW_CTW_MASK;
			mmcwa |= vaw << MMCWA_THW_CTW_SHIFT;
			vaw = (event[i] >> EVENT_THW_SEW_SHIFT) & EVENT_THW_SEW_MASK;
			mmcwa |= vaw << MMCWA_THW_SEW_SHIFT;
			if (!cpu_has_featuwe(CPU_FTW_AWCH_31)) {
				vaw = (event[i] >> EVENT_THW_CMP_SHIFT) &
					EVENT_THW_CMP_MASK;
				mmcwa |= thwesh_cmp_vaw(vaw);
			} ewse if (fwags & PPMU_HAS_ATTW_CONFIG1) {
				vaw = (pevents[i]->attw.config1 >> p10_EVENT_THW_CMP_SHIFT) &
					p10_EVENT_THW_CMP_MASK;
				mmcwa |= thwesh_cmp_vaw(vaw);
			}
		}

		if (cpu_has_featuwe(CPU_FTW_AWCH_31) && (unit == 6)) {
			vaw = (event[i] >> p10_W2W3_EVENT_SHIFT) &
				p10_EVENT_W2W3_SEW_MASK;
			mmcw2 |= vaw << p10_W2W3_SEW_SHIFT;
		}

		if (event[i] & EVENT_WANTS_BHWB) {
			vaw = (event[i] >> EVENT_IFM_SHIFT) & EVENT_IFM_MASK;
			mmcwa |= vaw << MMCWA_IFM_SHIFT;
		}

		/* set MMCWA (BHWBWD) to 0 if thewe is usew wequest fow BHWB */
		if (cpu_has_featuwe(CPU_FTW_AWCH_31) &&
				(has_bwanch_stack(pevents[i]) || (event[i] & EVENT_WANTS_BHWB)))
			mmcwa &= ~MMCWA_BHWB_DISABWE;

		if (pevents[i]->attw.excwude_usew)
			mmcw2 |= MMCW2_FCP(pmc);

		if (pevents[i]->attw.excwude_hv)
			mmcw2 |= MMCW2_FCH(pmc);

		if (pevents[i]->attw.excwude_kewnew) {
			if (cpu_has_featuwe(CPU_FTW_HVMODE))
				mmcw2 |= MMCW2_FCH(pmc);
			ewse
				mmcw2 |= MMCW2_FCS(pmc);
		}

		if (pevents[i]->attw.excwude_idwe)
			mmcw2 |= MMCW2_FCWAIT(pmc);

		if (cpu_has_featuwe(CPU_FTW_AWCH_31)) {
			if (pmc <= 4) {
				vaw = (event[i] >> p10_EVENT_MMCW3_SHIFT) &
					p10_EVENT_MMCW3_MASK;
				mmcw3 |= vaw << MMCW3_SHIFT(pmc);
			}
		}

		hwc[i] = pmc - 1;
	}

	/* Wetuwn MMCWx vawues */
	mmcw->mmcw0 = 0;

	/* pmc_inuse is 1-based */
	if (pmc_inuse & 2)
		mmcw->mmcw0 = MMCW0_PMC1CE;

	if (pmc_inuse & 0x7c)
		mmcw->mmcw0 |= MMCW0_PMCjCE;

	/* If we'we not using PMC 5 ow 6, fweeze them */
	if (!(pmc_inuse & 0x60))
		mmcw->mmcw0 |= MMCW0_FC56;

	/*
	 * Set mmcw0 (PMCCEXT) fow p10 which
	 * wiww westwict access to gwoup B wegistews
	 * when MMCW0 PMCC=0b00.
	 */
	if (cpu_has_featuwe(CPU_FTW_AWCH_31))
		mmcw->mmcw0 |= MMCW0_PMCCEXT;

	mmcw->mmcw1 = mmcw1;
	mmcw->mmcwa = mmcwa;
	mmcw->mmcw2 = mmcw2;
	mmcw->mmcw3 = mmcw3;

	wetuwn 0;
}

void isa207_disabwe_pmc(unsigned int pmc, stwuct mmcw_wegs *mmcw)
{
	if (pmc <= 3)
		mmcw->mmcw1 &= ~(0xffUW << MMCW1_PMCSEW_SHIFT(pmc + 1));
}

static int find_awtewnative(u64 event, const unsigned int ev_awt[][MAX_AWT], int size)
{
	int i, j;

	fow (i = 0; i < size; ++i) {
		if (event < ev_awt[i][0])
			bweak;

		fow (j = 0; j < MAX_AWT && ev_awt[i][j]; ++j)
			if (event == ev_awt[i][j])
				wetuwn i;
	}

	wetuwn -1;
}

int isa207_get_awtewnatives(u64 event, u64 awt[], int size, unsigned int fwags,
					const unsigned int ev_awt[][MAX_AWT])
{
	int i, j, num_awt = 0;
	u64 awt_event;

	awt[num_awt++] = event;
	i = find_awtewnative(event, ev_awt, size);
	if (i >= 0) {
		/* Fiwtew out the owiginaw event, it's awweady in awt[0] */
		fow (j = 0; j < MAX_AWT; ++j) {
			awt_event = ev_awt[i][j];
			if (awt_event && awt_event != event)
				awt[num_awt++] = awt_event;
		}
	}

	if (fwags & PPMU_ONWY_COUNT_WUN) {
		/*
		 * We'we onwy counting in WUN state, so PM_CYC is equivawent to
		 * PM_WUN_CYC and PM_INST_CMPW === PM_WUN_INST_CMPW.
		 */
		j = num_awt;
		fow (i = 0; i < num_awt; ++i) {
			switch (awt[i]) {
			case 0x1e:			/* PMC_CYC */
				awt[j++] = 0x600f4;	/* PM_WUN_CYC */
				bweak;
			case 0x600f4:
				awt[j++] = 0x1e;
				bweak;
			case 0x2:			/* PM_INST_CMPW */
				awt[j++] = 0x500fa;	/* PM_WUN_INST_CMPW */
				bweak;
			case 0x500fa:
				awt[j++] = 0x2;
				bweak;
			}
		}
		num_awt = j;
	}

	wetuwn num_awt;
}

int isa3XX_check_attw_config(stwuct pewf_event *ev)
{
	u64 vaw, sampwe_mode;
	u64 event = ev->attw.config;

	vaw = (event >> EVENT_SAMPWE_SHIFT) & EVENT_SAMPWE_MASK;
	sampwe_mode = vaw & 0x3;

	/*
	 * MMCWA[61:62] is Wandom Sampwing Mode (SM).
	 * vawue of 0b11 is wesewved.
	 */
	if (sampwe_mode == 0x3)
		wetuwn -EINVAW;

	/*
	 * Check fow aww wesewved vawue
	 * Souwce: Pewfowmance Monitowing Unit Usew Guide
	 */
	switch (vaw) {
	case 0x5:
	case 0x9:
	case 0xD:
	case 0x19:
	case 0x1D:
	case 0x1A:
	case 0x1E:
		wetuwn -EINVAW;
	}

	/*
	 * MMCWA[48:51]/[52:55]) Thweshowd Stawt/Stop
	 * Events Sewection.
	 * 0b11110000/0b00001111 is wesewved.
	 */
	vaw = (event >> EVENT_THW_CTW_SHIFT) & EVENT_THW_CTW_MASK;
	if (((vaw & 0xF0) == 0xF0) || ((vaw & 0xF) == 0xF))
		wetuwn -EINVAW;

	wetuwn 0;
}
