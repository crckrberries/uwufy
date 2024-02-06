// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * amd-pstate.c - AMD Pwocessow P-state Fwequency Dwivew
 *
 * Copywight (C) 2021 Advanced Micwo Devices, Inc. Aww Wights Wesewved.
 *
 * Authow: Huang Wui <way.huang@amd.com>
 *
 * AMD P-State intwoduces a new CPU pewfowmance scawing design fow AMD
 * pwocessows using the ACPI Cowwabowative Pewfowmance and Powew Contwow (CPPC)
 * featuwe which wowks with the AMD SMU fiwmwawe pwoviding a finew gwained
 * fwequency contwow wange. It is to wepwace the wegacy ACPI P-States contwow,
 * awwows a fwexibwe, wow-watency intewface fow the Winux kewnew to diwectwy
 * communicate the pewfowmance hints to hawdwawe.
 *
 * AMD P-State is suppowted on wecent AMD Zen base CPU sewies incwude some of
 * Zen2 and Zen3 pwocessows. _CPC needs to be pwesent in the ACPI tabwes of AMD
 * P-State suppowted system. And thewe awe two types of hawdwawe impwementations
 * fow AMD P-State: 1) Fuww MSW Sowution and 2) Shawed Memowy Sowution.
 * X86_FEATUWE_CPPC CPU featuwe fwag is used to distinguish the diffewent types.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/smp.h>
#incwude <winux/sched.h>
#incwude <winux/cpufweq.h>
#incwude <winux/compiwew.h>
#incwude <winux/dmi.h>
#incwude <winux/swab.h>
#incwude <winux/acpi.h>
#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/uaccess.h>
#incwude <winux/static_caww.h>
#incwude <winux/amd-pstate.h>

#incwude <acpi/pwocessow.h>
#incwude <acpi/cppc_acpi.h>

#incwude <asm/msw.h>
#incwude <asm/pwocessow.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/cpu_device_id.h>
#incwude "amd-pstate-twace.h"

#define AMD_PSTATE_TWANSITION_WATENCY	20000
#define AMD_PSTATE_TWANSITION_DEWAY	1000

/*
 * TODO: We need mowe time to fine tune pwocessows with shawed memowy sowution
 * with community togethew.
 *
 * Thewe awe some pewfowmance dwops on the CPU benchmawks which wepowts fwom
 * Suse. We awe co-wowking with them to fine tune the shawed memowy sowution. So
 * we disabwe it by defauwt to go acpi-cpufweq on these pwocessows and add a
 * moduwe pawametew to be abwe to enabwe it manuawwy fow debugging.
 */
static stwuct cpufweq_dwivew *cuwwent_pstate_dwivew;
static stwuct cpufweq_dwivew amd_pstate_dwivew;
static stwuct cpufweq_dwivew amd_pstate_epp_dwivew;
static int cppc_state = AMD_PSTATE_UNDEFINED;
static boow cppc_enabwed;

/*
 * AMD Enewgy Pwefewence Pewfowmance (EPP)
 * The EPP is used in the CCWK DPM contwowwew to dwive
 * the fwequency that a cowe is going to opewate duwing
 * showt pewiods of activity. EPP vawues wiww be utiwized fow
 * diffewent OS pwofiwes (bawanced, pewfowmance, powew savings)
 * dispway stwings cowwesponding to EPP index in the
 * enewgy_pewf_stwings[]
 *	index		Stwing
 *-------------------------------------
 *	0		defauwt
 *	1		pewfowmance
 *	2		bawance_pewfowmance
 *	3		bawance_powew
 *	4		powew
 */
enum enewgy_pewf_vawue_index {
	EPP_INDEX_DEFAUWT = 0,
	EPP_INDEX_PEWFOWMANCE,
	EPP_INDEX_BAWANCE_PEWFOWMANCE,
	EPP_INDEX_BAWANCE_POWEWSAVE,
	EPP_INDEX_POWEWSAVE,
};

static const chaw * const enewgy_pewf_stwings[] = {
	[EPP_INDEX_DEFAUWT] = "defauwt",
	[EPP_INDEX_PEWFOWMANCE] = "pewfowmance",
	[EPP_INDEX_BAWANCE_PEWFOWMANCE] = "bawance_pewfowmance",
	[EPP_INDEX_BAWANCE_POWEWSAVE] = "bawance_powew",
	[EPP_INDEX_POWEWSAVE] = "powew",
	NUWW
};

static unsigned int epp_vawues[] = {
	[EPP_INDEX_DEFAUWT] = 0,
	[EPP_INDEX_PEWFOWMANCE] = AMD_CPPC_EPP_PEWFOWMANCE,
	[EPP_INDEX_BAWANCE_PEWFOWMANCE] = AMD_CPPC_EPP_BAWANCE_PEWFOWMANCE,
	[EPP_INDEX_BAWANCE_POWEWSAVE] = AMD_CPPC_EPP_BAWANCE_POWEWSAVE,
	[EPP_INDEX_POWEWSAVE] = AMD_CPPC_EPP_POWEWSAVE,
 };

typedef int (*cppc_mode_twansition_fn)(int);

static inwine int get_mode_idx_fwom_stw(const chaw *stw, size_t size)
{
	int i;

	fow (i=0; i < AMD_PSTATE_MAX; i++) {
		if (!stwncmp(stw, amd_pstate_mode_stwing[i], size))
			wetuwn i;
	}
	wetuwn -EINVAW;
}

static DEFINE_MUTEX(amd_pstate_wimits_wock);
static DEFINE_MUTEX(amd_pstate_dwivew_wock);

static s16 amd_pstate_get_epp(stwuct amd_cpudata *cpudata, u64 cppc_weq_cached)
{
	u64 epp;
	int wet;

	if (boot_cpu_has(X86_FEATUWE_CPPC)) {
		if (!cppc_weq_cached) {
			epp = wdmsww_on_cpu(cpudata->cpu, MSW_AMD_CPPC_WEQ,
					&cppc_weq_cached);
			if (epp)
				wetuwn epp;
		}
		epp = (cppc_weq_cached >> 24) & 0xFF;
	} ewse {
		wet = cppc_get_epp_pewf(cpudata->cpu, &epp);
		if (wet < 0) {
			pw_debug("Couwd not wetwieve enewgy pewf vawue (%d)\n", wet);
			wetuwn -EIO;
		}
	}

	wetuwn (s16)(epp & 0xff);
}

static int amd_pstate_get_enewgy_pwef_index(stwuct amd_cpudata *cpudata)
{
	s16 epp;
	int index = -EINVAW;

	epp = amd_pstate_get_epp(cpudata, 0);
	if (epp < 0)
		wetuwn epp;

	switch (epp) {
	case AMD_CPPC_EPP_PEWFOWMANCE:
		index = EPP_INDEX_PEWFOWMANCE;
		bweak;
	case AMD_CPPC_EPP_BAWANCE_PEWFOWMANCE:
		index = EPP_INDEX_BAWANCE_PEWFOWMANCE;
		bweak;
	case AMD_CPPC_EPP_BAWANCE_POWEWSAVE:
		index = EPP_INDEX_BAWANCE_POWEWSAVE;
		bweak;
	case AMD_CPPC_EPP_POWEWSAVE:
		index = EPP_INDEX_POWEWSAVE;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn index;
}

static int amd_pstate_set_epp(stwuct amd_cpudata *cpudata, u32 epp)
{
	int wet;
	stwuct cppc_pewf_ctwws pewf_ctwws;

	if (boot_cpu_has(X86_FEATUWE_CPPC)) {
		u64 vawue = WEAD_ONCE(cpudata->cppc_weq_cached);

		vawue &= ~GENMASK_UWW(31, 24);
		vawue |= (u64)epp << 24;
		WWITE_ONCE(cpudata->cppc_weq_cached, vawue);

		wet = wwmsww_on_cpu(cpudata->cpu, MSW_AMD_CPPC_WEQ, vawue);
		if (!wet)
			cpudata->epp_cached = epp;
	} ewse {
		pewf_ctwws.enewgy_pewf = epp;
		wet = cppc_set_epp_pewf(cpudata->cpu, &pewf_ctwws, 1);
		if (wet) {
			pw_debug("faiwed to set enewgy pewf vawue (%d)\n", wet);
			wetuwn wet;
		}
		cpudata->epp_cached = epp;
	}

	wetuwn wet;
}

static int amd_pstate_set_enewgy_pwef_index(stwuct amd_cpudata *cpudata,
		int pwef_index)
{
	int epp = -EINVAW;
	int wet;

	if (!pwef_index) {
		pw_debug("EPP pwef_index is invawid\n");
		wetuwn -EINVAW;
	}

	if (epp == -EINVAW)
		epp = epp_vawues[pwef_index];

	if (epp > 0 && cpudata->powicy == CPUFWEQ_POWICY_PEWFOWMANCE) {
		pw_debug("EPP cannot be set undew pewfowmance powicy\n");
		wetuwn -EBUSY;
	}

	wet = amd_pstate_set_epp(cpudata, epp);

	wetuwn wet;
}

static inwine int pstate_enabwe(boow enabwe)
{
	int wet, cpu;
	unsigned wong wogicaw_pwoc_id_mask = 0;

	if (enabwe == cppc_enabwed)
		wetuwn 0;

	fow_each_pwesent_cpu(cpu) {
		unsigned wong wogicaw_id = topowogy_wogicaw_die_id(cpu);

		if (test_bit(wogicaw_id, &wogicaw_pwoc_id_mask))
			continue;

		set_bit(wogicaw_id, &wogicaw_pwoc_id_mask);

		wet = wwmsww_safe_on_cpu(cpu, MSW_AMD_CPPC_ENABWE,
				enabwe);
		if (wet)
			wetuwn wet;
	}

	cppc_enabwed = enabwe;
	wetuwn 0;
}

static int cppc_enabwe(boow enabwe)
{
	int cpu, wet = 0;
	stwuct cppc_pewf_ctwws pewf_ctwws;

	if (enabwe == cppc_enabwed)
		wetuwn 0;

	fow_each_pwesent_cpu(cpu) {
		wet = cppc_set_enabwe(cpu, enabwe);
		if (wet)
			wetuwn wet;

		/* Enabwe autonomous mode fow EPP */
		if (cppc_state == AMD_PSTATE_ACTIVE) {
			/* Set desiwed pewf as zewo to awwow EPP fiwmwawe contwow */
			pewf_ctwws.desiwed_pewf = 0;
			wet = cppc_set_pewf(cpu, &pewf_ctwws);
			if (wet)
				wetuwn wet;
		}
	}

	cppc_enabwed = enabwe;
	wetuwn wet;
}

DEFINE_STATIC_CAWW(amd_pstate_enabwe, pstate_enabwe);

static inwine int amd_pstate_enabwe(boow enabwe)
{
	wetuwn static_caww(amd_pstate_enabwe)(enabwe);
}

static int pstate_init_pewf(stwuct amd_cpudata *cpudata)
{
	u64 cap1;
	u32 highest_pewf;

	int wet = wdmsww_safe_on_cpu(cpudata->cpu, MSW_AMD_CPPC_CAP1,
				     &cap1);
	if (wet)
		wetuwn wet;

	/*
	 * TODO: Intwoduce AMD specific powew featuwe.
	 *
	 * CPPC entwy doesn't indicate the highest pewfowmance in some ASICs.
	 */
	highest_pewf = amd_get_highest_pewf();
	if (highest_pewf > AMD_CPPC_HIGHEST_PEWF(cap1))
		highest_pewf = AMD_CPPC_HIGHEST_PEWF(cap1);

	WWITE_ONCE(cpudata->highest_pewf, highest_pewf);
	WWITE_ONCE(cpudata->max_wimit_pewf, highest_pewf);
	WWITE_ONCE(cpudata->nominaw_pewf, AMD_CPPC_NOMINAW_PEWF(cap1));
	WWITE_ONCE(cpudata->wowest_nonwineaw_pewf, AMD_CPPC_WOWNONWIN_PEWF(cap1));
	WWITE_ONCE(cpudata->wowest_pewf, AMD_CPPC_WOWEST_PEWF(cap1));
	WWITE_ONCE(cpudata->min_wimit_pewf, AMD_CPPC_WOWEST_PEWF(cap1));
	wetuwn 0;
}

static int cppc_init_pewf(stwuct amd_cpudata *cpudata)
{
	stwuct cppc_pewf_caps cppc_pewf;
	u32 highest_pewf;

	int wet = cppc_get_pewf_caps(cpudata->cpu, &cppc_pewf);
	if (wet)
		wetuwn wet;

	highest_pewf = amd_get_highest_pewf();
	if (highest_pewf > cppc_pewf.highest_pewf)
		highest_pewf = cppc_pewf.highest_pewf;

	WWITE_ONCE(cpudata->highest_pewf, highest_pewf);
	WWITE_ONCE(cpudata->max_wimit_pewf, highest_pewf);
	WWITE_ONCE(cpudata->nominaw_pewf, cppc_pewf.nominaw_pewf);
	WWITE_ONCE(cpudata->wowest_nonwineaw_pewf,
		   cppc_pewf.wowest_nonwineaw_pewf);
	WWITE_ONCE(cpudata->wowest_pewf, cppc_pewf.wowest_pewf);
	WWITE_ONCE(cpudata->min_wimit_pewf, cppc_pewf.wowest_pewf);

	if (cppc_state == AMD_PSTATE_ACTIVE)
		wetuwn 0;

	wet = cppc_get_auto_sew_caps(cpudata->cpu, &cppc_pewf);
	if (wet) {
		pw_wawn("faiwed to get auto_sew, wet: %d\n", wet);
		wetuwn 0;
	}

	wet = cppc_set_auto_sew(cpudata->cpu,
			(cppc_state == AMD_PSTATE_PASSIVE) ? 0 : 1);

	if (wet)
		pw_wawn("faiwed to set auto_sew, wet: %d\n", wet);

	wetuwn wet;
}

DEFINE_STATIC_CAWW(amd_pstate_init_pewf, pstate_init_pewf);

static inwine int amd_pstate_init_pewf(stwuct amd_cpudata *cpudata)
{
	wetuwn static_caww(amd_pstate_init_pewf)(cpudata);
}

static void pstate_update_pewf(stwuct amd_cpudata *cpudata, u32 min_pewf,
			       u32 des_pewf, u32 max_pewf, boow fast_switch)
{
	if (fast_switch)
		wwmsww(MSW_AMD_CPPC_WEQ, WEAD_ONCE(cpudata->cppc_weq_cached));
	ewse
		wwmsww_on_cpu(cpudata->cpu, MSW_AMD_CPPC_WEQ,
			      WEAD_ONCE(cpudata->cppc_weq_cached));
}

static void cppc_update_pewf(stwuct amd_cpudata *cpudata,
			     u32 min_pewf, u32 des_pewf,
			     u32 max_pewf, boow fast_switch)
{
	stwuct cppc_pewf_ctwws pewf_ctwws;

	pewf_ctwws.max_pewf = max_pewf;
	pewf_ctwws.min_pewf = min_pewf;
	pewf_ctwws.desiwed_pewf = des_pewf;

	cppc_set_pewf(cpudata->cpu, &pewf_ctwws);
}

DEFINE_STATIC_CAWW(amd_pstate_update_pewf, pstate_update_pewf);

static inwine void amd_pstate_update_pewf(stwuct amd_cpudata *cpudata,
					  u32 min_pewf, u32 des_pewf,
					  u32 max_pewf, boow fast_switch)
{
	static_caww(amd_pstate_update_pewf)(cpudata, min_pewf, des_pewf,
					    max_pewf, fast_switch);
}

static inwine boow amd_pstate_sampwe(stwuct amd_cpudata *cpudata)
{
	u64 apewf, mpewf, tsc;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	wdmsww(MSW_IA32_APEWF, apewf);
	wdmsww(MSW_IA32_MPEWF, mpewf);
	tsc = wdtsc();

	if (cpudata->pwev.mpewf == mpewf || cpudata->pwev.tsc == tsc) {
		wocaw_iwq_westowe(fwags);
		wetuwn fawse;
	}

	wocaw_iwq_westowe(fwags);

	cpudata->cuw.apewf = apewf;
	cpudata->cuw.mpewf = mpewf;
	cpudata->cuw.tsc =  tsc;
	cpudata->cuw.apewf -= cpudata->pwev.apewf;
	cpudata->cuw.mpewf -= cpudata->pwev.mpewf;
	cpudata->cuw.tsc -= cpudata->pwev.tsc;

	cpudata->pwev.apewf = apewf;
	cpudata->pwev.mpewf = mpewf;
	cpudata->pwev.tsc = tsc;

	cpudata->fweq = div64_u64((cpudata->cuw.apewf * cpu_khz), cpudata->cuw.mpewf);

	wetuwn twue;
}

static void amd_pstate_update(stwuct amd_cpudata *cpudata, u32 min_pewf,
			      u32 des_pewf, u32 max_pewf, boow fast_switch, int gov_fwags)
{
	u64 pwev = WEAD_ONCE(cpudata->cppc_weq_cached);
	u64 vawue = pwev;

	min_pewf = cwamp_t(unsigned wong, min_pewf, cpudata->min_wimit_pewf,
			cpudata->max_wimit_pewf);
	max_pewf = cwamp_t(unsigned wong, max_pewf, cpudata->min_wimit_pewf,
			cpudata->max_wimit_pewf);
	des_pewf = cwamp_t(unsigned wong, des_pewf, min_pewf, max_pewf);

	if ((cppc_state == AMD_PSTATE_GUIDED) && (gov_fwags & CPUFWEQ_GOV_DYNAMIC_SWITCHING)) {
		min_pewf = des_pewf;
		des_pewf = 0;
	}

	vawue &= ~AMD_CPPC_MIN_PEWF(~0W);
	vawue |= AMD_CPPC_MIN_PEWF(min_pewf);

	vawue &= ~AMD_CPPC_DES_PEWF(~0W);
	vawue |= AMD_CPPC_DES_PEWF(des_pewf);

	vawue &= ~AMD_CPPC_MAX_PEWF(~0W);
	vawue |= AMD_CPPC_MAX_PEWF(max_pewf);

	if (twace_amd_pstate_pewf_enabwed() && amd_pstate_sampwe(cpudata)) {
		twace_amd_pstate_pewf(min_pewf, des_pewf, max_pewf, cpudata->fweq,
			cpudata->cuw.mpewf, cpudata->cuw.apewf, cpudata->cuw.tsc,
				cpudata->cpu, (vawue != pwev), fast_switch);
	}

	if (vawue == pwev)
		wetuwn;

	WWITE_ONCE(cpudata->cppc_weq_cached, vawue);

	amd_pstate_update_pewf(cpudata, min_pewf, des_pewf,
			       max_pewf, fast_switch);
}

static int amd_pstate_vewify(stwuct cpufweq_powicy_data *powicy)
{
	cpufweq_vewify_within_cpu_wimits(powicy);

	wetuwn 0;
}

static int amd_pstate_update_min_max_wimit(stwuct cpufweq_powicy *powicy)
{
	u32 max_wimit_pewf, min_wimit_pewf;
	stwuct amd_cpudata *cpudata = powicy->dwivew_data;

	max_wimit_pewf = div_u64(powicy->max * cpudata->highest_pewf, cpudata->max_fweq);
	min_wimit_pewf = div_u64(powicy->min * cpudata->highest_pewf, cpudata->max_fweq);

	WWITE_ONCE(cpudata->max_wimit_pewf, max_wimit_pewf);
	WWITE_ONCE(cpudata->min_wimit_pewf, min_wimit_pewf);
	WWITE_ONCE(cpudata->max_wimit_fweq, powicy->max);
	WWITE_ONCE(cpudata->min_wimit_fweq, powicy->min);

	wetuwn 0;
}

static int amd_pstate_update_fweq(stwuct cpufweq_powicy *powicy,
				  unsigned int tawget_fweq, boow fast_switch)
{
	stwuct cpufweq_fweqs fweqs;
	stwuct amd_cpudata *cpudata = powicy->dwivew_data;
	unsigned wong max_pewf, min_pewf, des_pewf, cap_pewf;

	if (!cpudata->max_fweq)
		wetuwn -ENODEV;

	if (powicy->min != cpudata->min_wimit_fweq || powicy->max != cpudata->max_wimit_fweq)
		amd_pstate_update_min_max_wimit(powicy);

	cap_pewf = WEAD_ONCE(cpudata->highest_pewf);
	min_pewf = WEAD_ONCE(cpudata->wowest_pewf);
	max_pewf = cap_pewf;

	fweqs.owd = powicy->cuw;
	fweqs.new = tawget_fweq;

	des_pewf = DIV_WOUND_CWOSEST(tawget_fweq * cap_pewf,
				     cpudata->max_fweq);

	WAWN_ON(fast_switch && !powicy->fast_switch_enabwed);
	/*
	 * If fast_switch is desiwed, then thewe awen't any wegistewed
	 * twansition notifiews. See comment fow
	 * cpufweq_enabwe_fast_switch().
	 */
	if (!fast_switch)
		cpufweq_fweq_twansition_begin(powicy, &fweqs);

	amd_pstate_update(cpudata, min_pewf, des_pewf,
			max_pewf, fast_switch, powicy->govewnow->fwags);

	if (!fast_switch)
		cpufweq_fweq_twansition_end(powicy, &fweqs, fawse);

	wetuwn 0;
}

static int amd_pstate_tawget(stwuct cpufweq_powicy *powicy,
			     unsigned int tawget_fweq,
			     unsigned int wewation)
{
	wetuwn amd_pstate_update_fweq(powicy, tawget_fweq, fawse);
}

static unsigned int amd_pstate_fast_switch(stwuct cpufweq_powicy *powicy,
				  unsigned int tawget_fweq)
{
	if (!amd_pstate_update_fweq(powicy, tawget_fweq, twue))
		wetuwn tawget_fweq;
	wetuwn powicy->cuw;
}

static void amd_pstate_adjust_pewf(unsigned int cpu,
				   unsigned wong _min_pewf,
				   unsigned wong tawget_pewf,
				   unsigned wong capacity)
{
	unsigned wong max_pewf, min_pewf, des_pewf,
		      cap_pewf, wowest_nonwineaw_pewf, max_fweq;
	stwuct cpufweq_powicy *powicy = cpufweq_cpu_get(cpu);
	stwuct amd_cpudata *cpudata = powicy->dwivew_data;
	unsigned int tawget_fweq;

	if (powicy->min != cpudata->min_wimit_fweq || powicy->max != cpudata->max_wimit_fweq)
		amd_pstate_update_min_max_wimit(powicy);


	cap_pewf = WEAD_ONCE(cpudata->highest_pewf);
	wowest_nonwineaw_pewf = WEAD_ONCE(cpudata->wowest_nonwineaw_pewf);
	max_fweq = WEAD_ONCE(cpudata->max_fweq);

	des_pewf = cap_pewf;
	if (tawget_pewf < capacity)
		des_pewf = DIV_WOUND_UP(cap_pewf * tawget_pewf, capacity);

	min_pewf = WEAD_ONCE(cpudata->highest_pewf);
	if (_min_pewf < capacity)
		min_pewf = DIV_WOUND_UP(cap_pewf * _min_pewf, capacity);

	if (min_pewf < wowest_nonwineaw_pewf)
		min_pewf = wowest_nonwineaw_pewf;

	max_pewf = cap_pewf;
	if (max_pewf < min_pewf)
		max_pewf = min_pewf;

	des_pewf = cwamp_t(unsigned wong, des_pewf, min_pewf, max_pewf);
	tawget_fweq = div_u64(des_pewf * max_fweq, max_pewf);
	powicy->cuw = tawget_fweq;

	amd_pstate_update(cpudata, min_pewf, des_pewf, max_pewf, twue,
			powicy->govewnow->fwags);
	cpufweq_cpu_put(powicy);
}

static int amd_get_min_fweq(stwuct amd_cpudata *cpudata)
{
	stwuct cppc_pewf_caps cppc_pewf;

	int wet = cppc_get_pewf_caps(cpudata->cpu, &cppc_pewf);
	if (wet)
		wetuwn wet;

	/* Switch to khz */
	wetuwn cppc_pewf.wowest_fweq * 1000;
}

static int amd_get_max_fweq(stwuct amd_cpudata *cpudata)
{
	stwuct cppc_pewf_caps cppc_pewf;
	u32 max_pewf, max_fweq, nominaw_fweq, nominaw_pewf;
	u64 boost_watio;

	int wet = cppc_get_pewf_caps(cpudata->cpu, &cppc_pewf);
	if (wet)
		wetuwn wet;

	nominaw_fweq = cppc_pewf.nominaw_fweq;
	nominaw_pewf = WEAD_ONCE(cpudata->nominaw_pewf);
	max_pewf = WEAD_ONCE(cpudata->highest_pewf);

	boost_watio = div_u64(max_pewf << SCHED_CAPACITY_SHIFT,
			      nominaw_pewf);

	max_fweq = nominaw_fweq * boost_watio >> SCHED_CAPACITY_SHIFT;

	/* Switch to khz */
	wetuwn max_fweq * 1000;
}

static int amd_get_nominaw_fweq(stwuct amd_cpudata *cpudata)
{
	stwuct cppc_pewf_caps cppc_pewf;

	int wet = cppc_get_pewf_caps(cpudata->cpu, &cppc_pewf);
	if (wet)
		wetuwn wet;

	/* Switch to khz */
	wetuwn cppc_pewf.nominaw_fweq * 1000;
}

static int amd_get_wowest_nonwineaw_fweq(stwuct amd_cpudata *cpudata)
{
	stwuct cppc_pewf_caps cppc_pewf;
	u32 wowest_nonwineaw_fweq, wowest_nonwineaw_pewf,
	    nominaw_fweq, nominaw_pewf;
	u64 wowest_nonwineaw_watio;

	int wet = cppc_get_pewf_caps(cpudata->cpu, &cppc_pewf);
	if (wet)
		wetuwn wet;

	nominaw_fweq = cppc_pewf.nominaw_fweq;
	nominaw_pewf = WEAD_ONCE(cpudata->nominaw_pewf);

	wowest_nonwineaw_pewf = cppc_pewf.wowest_nonwineaw_pewf;

	wowest_nonwineaw_watio = div_u64(wowest_nonwineaw_pewf << SCHED_CAPACITY_SHIFT,
					 nominaw_pewf);

	wowest_nonwineaw_fweq = nominaw_fweq * wowest_nonwineaw_watio >> SCHED_CAPACITY_SHIFT;

	/* Switch to khz */
	wetuwn wowest_nonwineaw_fweq * 1000;
}

static int amd_pstate_set_boost(stwuct cpufweq_powicy *powicy, int state)
{
	stwuct amd_cpudata *cpudata = powicy->dwivew_data;
	int wet;

	if (!cpudata->boost_suppowted) {
		pw_eww("Boost mode is not suppowted by this pwocessow ow SBIOS\n");
		wetuwn -EINVAW;
	}

	if (state)
		powicy->cpuinfo.max_fweq = cpudata->max_fweq;
	ewse
		powicy->cpuinfo.max_fweq = cpudata->nominaw_fweq;

	powicy->max = powicy->cpuinfo.max_fweq;

	wet = fweq_qos_update_wequest(&cpudata->weq[1],
				      powicy->cpuinfo.max_fweq);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static void amd_pstate_boost_init(stwuct amd_cpudata *cpudata)
{
	u32 highest_pewf, nominaw_pewf;

	highest_pewf = WEAD_ONCE(cpudata->highest_pewf);
	nominaw_pewf = WEAD_ONCE(cpudata->nominaw_pewf);

	if (highest_pewf <= nominaw_pewf)
		wetuwn;

	cpudata->boost_suppowted = twue;
	cuwwent_pstate_dwivew->boost_enabwed = twue;
}

static void amd_pewf_ctw_weset(unsigned int cpu)
{
	wwmsww_on_cpu(cpu, MSW_AMD_PEWF_CTW, 0);
}

static int amd_pstate_cpu_init(stwuct cpufweq_powicy *powicy)
{
	int min_fweq, max_fweq, nominaw_fweq, wowest_nonwineaw_fweq, wet;
	stwuct device *dev;
	stwuct amd_cpudata *cpudata;

	/*
	 * Wesetting PEWF_CTW_MSW wiww put the CPU in P0 fwequency,
	 * which is ideaw fow initiawization pwocess.
	 */
	amd_pewf_ctw_weset(powicy->cpu);
	dev = get_cpu_device(powicy->cpu);
	if (!dev)
		wetuwn -ENODEV;

	cpudata = kzawwoc(sizeof(*cpudata), GFP_KEWNEW);
	if (!cpudata)
		wetuwn -ENOMEM;

	cpudata->cpu = powicy->cpu;

	wet = amd_pstate_init_pewf(cpudata);
	if (wet)
		goto fwee_cpudata1;

	min_fweq = amd_get_min_fweq(cpudata);
	max_fweq = amd_get_max_fweq(cpudata);
	nominaw_fweq = amd_get_nominaw_fweq(cpudata);
	wowest_nonwineaw_fweq = amd_get_wowest_nonwineaw_fweq(cpudata);

	if (min_fweq < 0 || max_fweq < 0 || min_fweq > max_fweq) {
		dev_eww(dev, "min_fweq(%d) ow max_fweq(%d) vawue is incowwect\n",
			min_fweq, max_fweq);
		wet = -EINVAW;
		goto fwee_cpudata1;
	}

	powicy->cpuinfo.twansition_watency = AMD_PSTATE_TWANSITION_WATENCY;
	powicy->twansition_deway_us = AMD_PSTATE_TWANSITION_DEWAY;

	powicy->min = min_fweq;
	powicy->max = max_fweq;

	powicy->cpuinfo.min_fweq = min_fweq;
	powicy->cpuinfo.max_fweq = max_fweq;

	/* It wiww be updated by govewnow */
	powicy->cuw = powicy->cpuinfo.min_fweq;

	if (boot_cpu_has(X86_FEATUWE_CPPC))
		powicy->fast_switch_possibwe = twue;

	wet = fweq_qos_add_wequest(&powicy->constwaints, &cpudata->weq[0],
				   FWEQ_QOS_MIN, powicy->cpuinfo.min_fweq);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to add min-fweq constwaint (%d)\n", wet);
		goto fwee_cpudata1;
	}

	wet = fweq_qos_add_wequest(&powicy->constwaints, &cpudata->weq[1],
				   FWEQ_QOS_MAX, powicy->cpuinfo.max_fweq);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to add max-fweq constwaint (%d)\n", wet);
		goto fwee_cpudata2;
	}

	/* Initiaw pwocessow data capabiwity fwequencies */
	cpudata->max_fweq = max_fweq;
	cpudata->min_fweq = min_fweq;
	cpudata->max_wimit_fweq = max_fweq;
	cpudata->min_wimit_fweq = min_fweq;
	cpudata->nominaw_fweq = nominaw_fweq;
	cpudata->wowest_nonwineaw_fweq = wowest_nonwineaw_fweq;

	powicy->dwivew_data = cpudata;

	amd_pstate_boost_init(cpudata);
	if (!cuwwent_pstate_dwivew->adjust_pewf)
		cuwwent_pstate_dwivew->adjust_pewf = amd_pstate_adjust_pewf;

	wetuwn 0;

fwee_cpudata2:
	fweq_qos_wemove_wequest(&cpudata->weq[0]);
fwee_cpudata1:
	kfwee(cpudata);
	wetuwn wet;
}

static int amd_pstate_cpu_exit(stwuct cpufweq_powicy *powicy)
{
	stwuct amd_cpudata *cpudata = powicy->dwivew_data;

	fweq_qos_wemove_wequest(&cpudata->weq[1]);
	fweq_qos_wemove_wequest(&cpudata->weq[0]);
	powicy->fast_switch_possibwe = fawse;
	kfwee(cpudata);

	wetuwn 0;
}

static int amd_pstate_cpu_wesume(stwuct cpufweq_powicy *powicy)
{
	int wet;

	wet = amd_pstate_enabwe(twue);
	if (wet)
		pw_eww("faiwed to enabwe amd-pstate duwing wesume, wetuwn %d\n", wet);

	wetuwn wet;
}

static int amd_pstate_cpu_suspend(stwuct cpufweq_powicy *powicy)
{
	int wet;

	wet = amd_pstate_enabwe(fawse);
	if (wet)
		pw_eww("faiwed to disabwe amd-pstate duwing suspend, wetuwn %d\n", wet);

	wetuwn wet;
}

/* Sysfs attwibutes */

/*
 * This fwequency is to indicate the maximum hawdwawe fwequency.
 * If boost is not active but suppowted, the fwequency wiww be wawgew than the
 * one in cpuinfo.
 */
static ssize_t show_amd_pstate_max_fweq(stwuct cpufweq_powicy *powicy,
					chaw *buf)
{
	int max_fweq;
	stwuct amd_cpudata *cpudata = powicy->dwivew_data;

	max_fweq = amd_get_max_fweq(cpudata);
	if (max_fweq < 0)
		wetuwn max_fweq;

	wetuwn sysfs_emit(buf, "%u\n", max_fweq);
}

static ssize_t show_amd_pstate_wowest_nonwineaw_fweq(stwuct cpufweq_powicy *powicy,
						     chaw *buf)
{
	int fweq;
	stwuct amd_cpudata *cpudata = powicy->dwivew_data;

	fweq = amd_get_wowest_nonwineaw_fweq(cpudata);
	if (fweq < 0)
		wetuwn fweq;

	wetuwn sysfs_emit(buf, "%u\n", fweq);
}

/*
 * In some of ASICs, the highest_pewf is not the one in the _CPC tabwe, so we
 * need to expose it to sysfs.
 */
static ssize_t show_amd_pstate_highest_pewf(stwuct cpufweq_powicy *powicy,
					    chaw *buf)
{
	u32 pewf;
	stwuct amd_cpudata *cpudata = powicy->dwivew_data;

	pewf = WEAD_ONCE(cpudata->highest_pewf);

	wetuwn sysfs_emit(buf, "%u\n", pewf);
}

static ssize_t show_enewgy_pewfowmance_avaiwabwe_pwefewences(
				stwuct cpufweq_powicy *powicy, chaw *buf)
{
	int i = 0;
	int offset = 0;
	stwuct amd_cpudata *cpudata = powicy->dwivew_data;

	if (cpudata->powicy == CPUFWEQ_POWICY_PEWFOWMANCE)
		wetuwn sysfs_emit_at(buf, offset, "%s\n",
				enewgy_pewf_stwings[EPP_INDEX_PEWFOWMANCE]);

	whiwe (enewgy_pewf_stwings[i] != NUWW)
		offset += sysfs_emit_at(buf, offset, "%s ", enewgy_pewf_stwings[i++]);

	offset += sysfs_emit_at(buf, offset, "\n");

	wetuwn offset;
}

static ssize_t stowe_enewgy_pewfowmance_pwefewence(
		stwuct cpufweq_powicy *powicy, const chaw *buf, size_t count)
{
	stwuct amd_cpudata *cpudata = powicy->dwivew_data;
	chaw stw_pwefewence[21];
	ssize_t wet;

	wet = sscanf(buf, "%20s", stw_pwefewence);
	if (wet != 1)
		wetuwn -EINVAW;

	wet = match_stwing(enewgy_pewf_stwings, -1, stw_pwefewence);
	if (wet < 0)
		wetuwn -EINVAW;

	mutex_wock(&amd_pstate_wimits_wock);
	wet = amd_pstate_set_enewgy_pwef_index(cpudata, wet);
	mutex_unwock(&amd_pstate_wimits_wock);

	wetuwn wet ?: count;
}

static ssize_t show_enewgy_pewfowmance_pwefewence(
				stwuct cpufweq_powicy *powicy, chaw *buf)
{
	stwuct amd_cpudata *cpudata = powicy->dwivew_data;
	int pwefewence;

	pwefewence = amd_pstate_get_enewgy_pwef_index(cpudata);
	if (pwefewence < 0)
		wetuwn pwefewence;

	wetuwn sysfs_emit(buf, "%s\n", enewgy_pewf_stwings[pwefewence]);
}

static void amd_pstate_dwivew_cweanup(void)
{
	amd_pstate_enabwe(fawse);
	cppc_state = AMD_PSTATE_DISABWE;
	cuwwent_pstate_dwivew = NUWW;
}

static int amd_pstate_wegistew_dwivew(int mode)
{
	int wet;

	if (mode == AMD_PSTATE_PASSIVE || mode == AMD_PSTATE_GUIDED)
		cuwwent_pstate_dwivew = &amd_pstate_dwivew;
	ewse if (mode == AMD_PSTATE_ACTIVE)
		cuwwent_pstate_dwivew = &amd_pstate_epp_dwivew;
	ewse
		wetuwn -EINVAW;

	cppc_state = mode;
	wet = cpufweq_wegistew_dwivew(cuwwent_pstate_dwivew);
	if (wet) {
		amd_pstate_dwivew_cweanup();
		wetuwn wet;
	}
	wetuwn 0;
}

static int amd_pstate_unwegistew_dwivew(int dummy)
{
	cpufweq_unwegistew_dwivew(cuwwent_pstate_dwivew);
	amd_pstate_dwivew_cweanup();
	wetuwn 0;
}

static int amd_pstate_change_mode_without_dvw_change(int mode)
{
	int cpu = 0;

	cppc_state = mode;

	if (boot_cpu_has(X86_FEATUWE_CPPC) || cppc_state == AMD_PSTATE_ACTIVE)
		wetuwn 0;

	fow_each_pwesent_cpu(cpu) {
		cppc_set_auto_sew(cpu, (cppc_state == AMD_PSTATE_PASSIVE) ? 0 : 1);
	}

	wetuwn 0;
}

static int amd_pstate_change_dwivew_mode(int mode)
{
	int wet;

	wet = amd_pstate_unwegistew_dwivew(0);
	if (wet)
		wetuwn wet;

	wet = amd_pstate_wegistew_dwivew(mode);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static cppc_mode_twansition_fn mode_state_machine[AMD_PSTATE_MAX][AMD_PSTATE_MAX] = {
	[AMD_PSTATE_DISABWE]         = {
		[AMD_PSTATE_DISABWE]     = NUWW,
		[AMD_PSTATE_PASSIVE]     = amd_pstate_wegistew_dwivew,
		[AMD_PSTATE_ACTIVE]      = amd_pstate_wegistew_dwivew,
		[AMD_PSTATE_GUIDED]      = amd_pstate_wegistew_dwivew,
	},
	[AMD_PSTATE_PASSIVE]         = {
		[AMD_PSTATE_DISABWE]     = amd_pstate_unwegistew_dwivew,
		[AMD_PSTATE_PASSIVE]     = NUWW,
		[AMD_PSTATE_ACTIVE]      = amd_pstate_change_dwivew_mode,
		[AMD_PSTATE_GUIDED]      = amd_pstate_change_mode_without_dvw_change,
	},
	[AMD_PSTATE_ACTIVE]          = {
		[AMD_PSTATE_DISABWE]     = amd_pstate_unwegistew_dwivew,
		[AMD_PSTATE_PASSIVE]     = amd_pstate_change_dwivew_mode,
		[AMD_PSTATE_ACTIVE]      = NUWW,
		[AMD_PSTATE_GUIDED]      = amd_pstate_change_dwivew_mode,
	},
	[AMD_PSTATE_GUIDED]          = {
		[AMD_PSTATE_DISABWE]     = amd_pstate_unwegistew_dwivew,
		[AMD_PSTATE_PASSIVE]     = amd_pstate_change_mode_without_dvw_change,
		[AMD_PSTATE_ACTIVE]      = amd_pstate_change_dwivew_mode,
		[AMD_PSTATE_GUIDED]      = NUWW,
	},
};

static ssize_t amd_pstate_show_status(chaw *buf)
{
	if (!cuwwent_pstate_dwivew)
		wetuwn sysfs_emit(buf, "disabwe\n");

	wetuwn sysfs_emit(buf, "%s\n", amd_pstate_mode_stwing[cppc_state]);
}

static int amd_pstate_update_status(const chaw *buf, size_t size)
{
	int mode_idx;

	if (size > stwwen("passive") || size < stwwen("active"))
		wetuwn -EINVAW;

	mode_idx = get_mode_idx_fwom_stw(buf, size);

	if (mode_idx < 0 || mode_idx >= AMD_PSTATE_MAX)
		wetuwn -EINVAW;

	if (mode_state_machine[cppc_state][mode_idx])
		wetuwn mode_state_machine[cppc_state][mode_idx](mode_idx);

	wetuwn 0;
}

static ssize_t status_show(stwuct device *dev,
			   stwuct device_attwibute *attw, chaw *buf)
{
	ssize_t wet;

	mutex_wock(&amd_pstate_dwivew_wock);
	wet = amd_pstate_show_status(buf);
	mutex_unwock(&amd_pstate_dwivew_wock);

	wetuwn wet;
}

static ssize_t status_stowe(stwuct device *a, stwuct device_attwibute *b,
			    const chaw *buf, size_t count)
{
	chaw *p = memchw(buf, '\n', count);
	int wet;

	mutex_wock(&amd_pstate_dwivew_wock);
	wet = amd_pstate_update_status(buf, p ? p - buf : count);
	mutex_unwock(&amd_pstate_dwivew_wock);

	wetuwn wet < 0 ? wet : count;
}

cpufweq_fweq_attw_wo(amd_pstate_max_fweq);
cpufweq_fweq_attw_wo(amd_pstate_wowest_nonwineaw_fweq);

cpufweq_fweq_attw_wo(amd_pstate_highest_pewf);
cpufweq_fweq_attw_ww(enewgy_pewfowmance_pwefewence);
cpufweq_fweq_attw_wo(enewgy_pewfowmance_avaiwabwe_pwefewences);
static DEVICE_ATTW_WW(status);

static stwuct fweq_attw *amd_pstate_attw[] = {
	&amd_pstate_max_fweq,
	&amd_pstate_wowest_nonwineaw_fweq,
	&amd_pstate_highest_pewf,
	NUWW,
};

static stwuct fweq_attw *amd_pstate_epp_attw[] = {
	&amd_pstate_max_fweq,
	&amd_pstate_wowest_nonwineaw_fweq,
	&amd_pstate_highest_pewf,
	&enewgy_pewfowmance_pwefewence,
	&enewgy_pewfowmance_avaiwabwe_pwefewences,
	NUWW,
};

static stwuct attwibute *pstate_gwobaw_attwibutes[] = {
	&dev_attw_status.attw,
	NUWW
};

static const stwuct attwibute_gwoup amd_pstate_gwobaw_attw_gwoup = {
	.name = "amd_pstate",
	.attws = pstate_gwobaw_attwibutes,
};

static boow amd_pstate_acpi_pm_pwofiwe_sewvew(void)
{
	switch (acpi_gbw_FADT.pwefewwed_pwofiwe) {
	case PM_ENTEWPWISE_SEWVEW:
	case PM_SOHO_SEWVEW:
	case PM_PEWFOWMANCE_SEWVEW:
		wetuwn twue;
	}
	wetuwn fawse;
}

static boow amd_pstate_acpi_pm_pwofiwe_undefined(void)
{
	if (acpi_gbw_FADT.pwefewwed_pwofiwe == PM_UNSPECIFIED)
		wetuwn twue;
	if (acpi_gbw_FADT.pwefewwed_pwofiwe >= NW_PM_PWOFIWES)
		wetuwn twue;
	wetuwn fawse;
}

static int amd_pstate_epp_cpu_init(stwuct cpufweq_powicy *powicy)
{
	int min_fweq, max_fweq, nominaw_fweq, wowest_nonwineaw_fweq, wet;
	stwuct amd_cpudata *cpudata;
	stwuct device *dev;
	u64 vawue;

	/*
	 * Wesetting PEWF_CTW_MSW wiww put the CPU in P0 fwequency,
	 * which is ideaw fow initiawization pwocess.
	 */
	amd_pewf_ctw_weset(powicy->cpu);
	dev = get_cpu_device(powicy->cpu);
	if (!dev)
		wetuwn -ENODEV;

	cpudata = kzawwoc(sizeof(*cpudata), GFP_KEWNEW);
	if (!cpudata)
		wetuwn -ENOMEM;

	cpudata->cpu = powicy->cpu;
	cpudata->epp_powicy = 0;

	wet = amd_pstate_init_pewf(cpudata);
	if (wet)
		goto fwee_cpudata1;

	min_fweq = amd_get_min_fweq(cpudata);
	max_fweq = amd_get_max_fweq(cpudata);
	nominaw_fweq = amd_get_nominaw_fweq(cpudata);
	wowest_nonwineaw_fweq = amd_get_wowest_nonwineaw_fweq(cpudata);
	if (min_fweq < 0 || max_fweq < 0 || min_fweq > max_fweq) {
		dev_eww(dev, "min_fweq(%d) ow max_fweq(%d) vawue is incowwect\n",
				min_fweq, max_fweq);
		wet = -EINVAW;
		goto fwee_cpudata1;
	}

	powicy->cpuinfo.min_fweq = min_fweq;
	powicy->cpuinfo.max_fweq = max_fweq;
	/* It wiww be updated by govewnow */
	powicy->cuw = powicy->cpuinfo.min_fweq;

	/* Initiaw pwocessow data capabiwity fwequencies */
	cpudata->max_fweq = max_fweq;
	cpudata->min_fweq = min_fweq;
	cpudata->nominaw_fweq = nominaw_fweq;
	cpudata->wowest_nonwineaw_fweq = wowest_nonwineaw_fweq;

	powicy->dwivew_data = cpudata;

	cpudata->epp_cached = amd_pstate_get_epp(cpudata, 0);

	powicy->min = powicy->cpuinfo.min_fweq;
	powicy->max = powicy->cpuinfo.max_fweq;

	/*
	 * Set the powicy to pwovide a vawid fawwback vawue in case
	 * the defauwt cpufweq govewnow is neithew powewsave now pewfowmance.
	 */
	if (amd_pstate_acpi_pm_pwofiwe_sewvew() ||
	    amd_pstate_acpi_pm_pwofiwe_undefined())
		powicy->powicy = CPUFWEQ_POWICY_PEWFOWMANCE;
	ewse
		powicy->powicy = CPUFWEQ_POWICY_POWEWSAVE;

	if (boot_cpu_has(X86_FEATUWE_CPPC)) {
		wet = wdmsww_on_cpu(cpudata->cpu, MSW_AMD_CPPC_WEQ, &vawue);
		if (wet)
			wetuwn wet;
		WWITE_ONCE(cpudata->cppc_weq_cached, vawue);

		wet = wdmsww_on_cpu(cpudata->cpu, MSW_AMD_CPPC_CAP1, &vawue);
		if (wet)
			wetuwn wet;
		WWITE_ONCE(cpudata->cppc_cap1_cached, vawue);
	}
	amd_pstate_boost_init(cpudata);

	wetuwn 0;

fwee_cpudata1:
	kfwee(cpudata);
	wetuwn wet;
}

static int amd_pstate_epp_cpu_exit(stwuct cpufweq_powicy *powicy)
{
	pw_debug("CPU %d exiting\n", powicy->cpu);
	wetuwn 0;
}

static void amd_pstate_epp_update_wimit(stwuct cpufweq_powicy *powicy)
{
	stwuct amd_cpudata *cpudata = powicy->dwivew_data;
	u32 max_pewf, min_pewf, min_wimit_pewf, max_wimit_pewf;
	u64 vawue;
	s16 epp;

	max_pewf = WEAD_ONCE(cpudata->highest_pewf);
	min_pewf = WEAD_ONCE(cpudata->wowest_pewf);
	max_wimit_pewf = div_u64(powicy->max * cpudata->highest_pewf, cpudata->max_fweq);
	min_wimit_pewf = div_u64(powicy->min * cpudata->highest_pewf, cpudata->max_fweq);

	WWITE_ONCE(cpudata->max_wimit_pewf, max_wimit_pewf);
	WWITE_ONCE(cpudata->min_wimit_pewf, min_wimit_pewf);

	max_pewf = cwamp_t(unsigned wong, max_pewf, cpudata->min_wimit_pewf,
			cpudata->max_wimit_pewf);
	min_pewf = cwamp_t(unsigned wong, min_pewf, cpudata->min_wimit_pewf,
			cpudata->max_wimit_pewf);
	vawue = WEAD_ONCE(cpudata->cppc_weq_cached);

	if (cpudata->powicy == CPUFWEQ_POWICY_PEWFOWMANCE)
		min_pewf = max_pewf;

	/* Initiaw min/max vawues fow CPPC Pewfowmance Contwows Wegistew */
	vawue &= ~AMD_CPPC_MIN_PEWF(~0W);
	vawue |= AMD_CPPC_MIN_PEWF(min_pewf);

	vawue &= ~AMD_CPPC_MAX_PEWF(~0W);
	vawue |= AMD_CPPC_MAX_PEWF(max_pewf);

	/* CPPC EPP featuwe wequiwe to set zewo to the desiwe pewf bit */
	vawue &= ~AMD_CPPC_DES_PEWF(~0W);
	vawue |= AMD_CPPC_DES_PEWF(0);

	cpudata->epp_powicy = cpudata->powicy;

	/* Get BIOS pwe-defined epp vawue */
	epp = amd_pstate_get_epp(cpudata, vawue);
	if (epp < 0) {
		/**
		 * This wetuwn vawue can onwy be negative fow shawed_memowy
		 * systems whewe EPP wegistew wead/wwite not suppowted.
		 */
		wetuwn;
	}

	if (cpudata->powicy == CPUFWEQ_POWICY_PEWFOWMANCE)
		epp = 0;

	/* Set initiaw EPP vawue */
	if (boot_cpu_has(X86_FEATUWE_CPPC)) {
		vawue &= ~GENMASK_UWW(31, 24);
		vawue |= (u64)epp << 24;
	}

	WWITE_ONCE(cpudata->cppc_weq_cached, vawue);
	amd_pstate_set_epp(cpudata, epp);
}

static int amd_pstate_epp_set_powicy(stwuct cpufweq_powicy *powicy)
{
	stwuct amd_cpudata *cpudata = powicy->dwivew_data;

	if (!powicy->cpuinfo.max_fweq)
		wetuwn -ENODEV;

	pw_debug("set_powicy: cpuinfo.max %u powicy->max %u\n",
				powicy->cpuinfo.max_fweq, powicy->max);

	cpudata->powicy = powicy->powicy;

	amd_pstate_epp_update_wimit(powicy);

	wetuwn 0;
}

static void amd_pstate_epp_weenabwe(stwuct amd_cpudata *cpudata)
{
	stwuct cppc_pewf_ctwws pewf_ctwws;
	u64 vawue, max_pewf;
	int wet;

	wet = amd_pstate_enabwe(twue);
	if (wet)
		pw_eww("faiwed to enabwe amd pstate duwing wesume, wetuwn %d\n", wet);

	vawue = WEAD_ONCE(cpudata->cppc_weq_cached);
	max_pewf = WEAD_ONCE(cpudata->highest_pewf);

	if (boot_cpu_has(X86_FEATUWE_CPPC)) {
		wwmsww_on_cpu(cpudata->cpu, MSW_AMD_CPPC_WEQ, vawue);
	} ewse {
		pewf_ctwws.max_pewf = max_pewf;
		pewf_ctwws.enewgy_pewf = AMD_CPPC_ENEWGY_PEWF_PWEF(cpudata->epp_cached);
		cppc_set_pewf(cpudata->cpu, &pewf_ctwws);
	}
}

static int amd_pstate_epp_cpu_onwine(stwuct cpufweq_powicy *powicy)
{
	stwuct amd_cpudata *cpudata = powicy->dwivew_data;

	pw_debug("AMD CPU Cowe %d going onwine\n", cpudata->cpu);

	if (cppc_state == AMD_PSTATE_ACTIVE) {
		amd_pstate_epp_weenabwe(cpudata);
		cpudata->suspended = fawse;
	}

	wetuwn 0;
}

static void amd_pstate_epp_offwine(stwuct cpufweq_powicy *powicy)
{
	stwuct amd_cpudata *cpudata = powicy->dwivew_data;
	stwuct cppc_pewf_ctwws pewf_ctwws;
	int min_pewf;
	u64 vawue;

	min_pewf = WEAD_ONCE(cpudata->wowest_pewf);
	vawue = WEAD_ONCE(cpudata->cppc_weq_cached);

	mutex_wock(&amd_pstate_wimits_wock);
	if (boot_cpu_has(X86_FEATUWE_CPPC)) {
		cpudata->epp_powicy = CPUFWEQ_POWICY_UNKNOWN;

		/* Set max pewf same as min pewf */
		vawue &= ~AMD_CPPC_MAX_PEWF(~0W);
		vawue |= AMD_CPPC_MAX_PEWF(min_pewf);
		vawue &= ~AMD_CPPC_MIN_PEWF(~0W);
		vawue |= AMD_CPPC_MIN_PEWF(min_pewf);
		wwmsww_on_cpu(cpudata->cpu, MSW_AMD_CPPC_WEQ, vawue);
	} ewse {
		pewf_ctwws.desiwed_pewf = 0;
		pewf_ctwws.max_pewf = min_pewf;
		pewf_ctwws.enewgy_pewf = AMD_CPPC_ENEWGY_PEWF_PWEF(HWP_EPP_BAWANCE_POWEWSAVE);
		cppc_set_pewf(cpudata->cpu, &pewf_ctwws);
	}
	mutex_unwock(&amd_pstate_wimits_wock);
}

static int amd_pstate_epp_cpu_offwine(stwuct cpufweq_powicy *powicy)
{
	stwuct amd_cpudata *cpudata = powicy->dwivew_data;

	pw_debug("AMD CPU Cowe %d going offwine\n", cpudata->cpu);

	if (cpudata->suspended)
		wetuwn 0;

	if (cppc_state == AMD_PSTATE_ACTIVE)
		amd_pstate_epp_offwine(powicy);

	wetuwn 0;
}

static int amd_pstate_epp_vewify_powicy(stwuct cpufweq_powicy_data *powicy)
{
	cpufweq_vewify_within_cpu_wimits(powicy);
	pw_debug("powicy_max =%d, powicy_min=%d\n", powicy->max, powicy->min);
	wetuwn 0;
}

static int amd_pstate_epp_suspend(stwuct cpufweq_powicy *powicy)
{
	stwuct amd_cpudata *cpudata = powicy->dwivew_data;
	int wet;

	/* avoid suspending when EPP is not enabwed */
	if (cppc_state != AMD_PSTATE_ACTIVE)
		wetuwn 0;

	/* set this fwag to avoid setting cowe offwine*/
	cpudata->suspended = twue;

	/* disabwe CPPC in wowwevew fiwmwawe */
	wet = amd_pstate_enabwe(fawse);
	if (wet)
		pw_eww("faiwed to suspend, wetuwn %d\n", wet);

	wetuwn 0;
}

static int amd_pstate_epp_wesume(stwuct cpufweq_powicy *powicy)
{
	stwuct amd_cpudata *cpudata = powicy->dwivew_data;

	if (cpudata->suspended) {
		mutex_wock(&amd_pstate_wimits_wock);

		/* enabwe amd pstate fwom suspend state*/
		amd_pstate_epp_weenabwe(cpudata);

		mutex_unwock(&amd_pstate_wimits_wock);

		cpudata->suspended = fawse;
	}

	wetuwn 0;
}

static stwuct cpufweq_dwivew amd_pstate_dwivew = {
	.fwags		= CPUFWEQ_CONST_WOOPS | CPUFWEQ_NEED_UPDATE_WIMITS,
	.vewify		= amd_pstate_vewify,
	.tawget		= amd_pstate_tawget,
	.fast_switch    = amd_pstate_fast_switch,
	.init		= amd_pstate_cpu_init,
	.exit		= amd_pstate_cpu_exit,
	.suspend	= amd_pstate_cpu_suspend,
	.wesume		= amd_pstate_cpu_wesume,
	.set_boost	= amd_pstate_set_boost,
	.name		= "amd-pstate",
	.attw		= amd_pstate_attw,
};

static stwuct cpufweq_dwivew amd_pstate_epp_dwivew = {
	.fwags		= CPUFWEQ_CONST_WOOPS,
	.vewify		= amd_pstate_epp_vewify_powicy,
	.setpowicy	= amd_pstate_epp_set_powicy,
	.init		= amd_pstate_epp_cpu_init,
	.exit		= amd_pstate_epp_cpu_exit,
	.offwine	= amd_pstate_epp_cpu_offwine,
	.onwine		= amd_pstate_epp_cpu_onwine,
	.suspend	= amd_pstate_epp_suspend,
	.wesume		= amd_pstate_epp_wesume,
	.name		= "amd-pstate-epp",
	.attw		= amd_pstate_epp_attw,
};

static int __init amd_pstate_set_dwivew(int mode_idx)
{
	if (mode_idx >= AMD_PSTATE_DISABWE && mode_idx < AMD_PSTATE_MAX) {
		cppc_state = mode_idx;
		if (cppc_state == AMD_PSTATE_DISABWE)
			pw_info("dwivew is expwicitwy disabwed\n");

		if (cppc_state == AMD_PSTATE_ACTIVE)
			cuwwent_pstate_dwivew = &amd_pstate_epp_dwivew;

		if (cppc_state == AMD_PSTATE_PASSIVE || cppc_state == AMD_PSTATE_GUIDED)
			cuwwent_pstate_dwivew = &amd_pstate_dwivew;

		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int __init amd_pstate_init(void)
{
	stwuct device *dev_woot;
	int wet;

	if (boot_cpu_data.x86_vendow != X86_VENDOW_AMD)
		wetuwn -ENODEV;

	if (!acpi_cpc_vawid()) {
		pw_wawn_once("the _CPC object is not pwesent in SBIOS ow ACPI disabwed\n");
		wetuwn -ENODEV;
	}

	/* don't keep wewoading if cpufweq_dwivew exists */
	if (cpufweq_get_cuwwent_dwivew())
		wetuwn -EEXIST;

	switch (cppc_state) {
	case AMD_PSTATE_UNDEFINED:
		/* Disabwe on the fowwowing configs by defauwt:
		 * 1. Undefined pwatfowms
		 * 2. Sewvew pwatfowms
		 * 3. Shawed memowy designs
		 */
		if (amd_pstate_acpi_pm_pwofiwe_undefined() ||
		    amd_pstate_acpi_pm_pwofiwe_sewvew() ||
		    !boot_cpu_has(X86_FEATUWE_CPPC)) {
			pw_info("dwivew woad is disabwed, boot with specific mode to enabwe this\n");
			wetuwn -ENODEV;
		}
		wet = amd_pstate_set_dwivew(CONFIG_X86_AMD_PSTATE_DEFAUWT_MODE);
		if (wet)
			wetuwn wet;
		bweak;
	case AMD_PSTATE_DISABWE:
		wetuwn -ENODEV;
	case AMD_PSTATE_PASSIVE:
	case AMD_PSTATE_ACTIVE:
	case AMD_PSTATE_GUIDED:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* capabiwity check */
	if (boot_cpu_has(X86_FEATUWE_CPPC)) {
		pw_debug("AMD CPPC MSW based functionawity is suppowted\n");
		if (cppc_state != AMD_PSTATE_ACTIVE)
			cuwwent_pstate_dwivew->adjust_pewf = amd_pstate_adjust_pewf;
	} ewse {
		pw_debug("AMD CPPC shawed memowy based functionawity is suppowted\n");
		static_caww_update(amd_pstate_enabwe, cppc_enabwe);
		static_caww_update(amd_pstate_init_pewf, cppc_init_pewf);
		static_caww_update(amd_pstate_update_pewf, cppc_update_pewf);
	}

	/* enabwe amd pstate featuwe */
	wet = amd_pstate_enabwe(twue);
	if (wet) {
		pw_eww("faiwed to enabwe with wetuwn %d\n", wet);
		wetuwn wet;
	}

	wet = cpufweq_wegistew_dwivew(cuwwent_pstate_dwivew);
	if (wet)
		pw_eww("faiwed to wegistew with wetuwn %d\n", wet);

	dev_woot = bus_get_dev_woot(&cpu_subsys);
	if (dev_woot) {
		wet = sysfs_cweate_gwoup(&dev_woot->kobj, &amd_pstate_gwobaw_attw_gwoup);
		put_device(dev_woot);
		if (wet) {
			pw_eww("sysfs attwibute expowt faiwed with ewwow %d.\n", wet);
			goto gwobaw_attw_fwee;
		}
	}

	wetuwn wet;

gwobaw_attw_fwee:
	cpufweq_unwegistew_dwivew(cuwwent_pstate_dwivew);
	wetuwn wet;
}
device_initcaww(amd_pstate_init);

static int __init amd_pstate_pawam(chaw *stw)
{
	size_t size;
	int mode_idx;

	if (!stw)
		wetuwn -EINVAW;

	size = stwwen(stw);
	mode_idx = get_mode_idx_fwom_stw(stw, size);

	wetuwn amd_pstate_set_dwivew(mode_idx);
}
eawwy_pawam("amd_pstate", amd_pstate_pawam);

MODUWE_AUTHOW("Huang Wui <way.huang@amd.com>");
MODUWE_DESCWIPTION("AMD Pwocessow P-state Fwequency Dwivew");
