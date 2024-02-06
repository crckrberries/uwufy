// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Copywight (C) 2013 Citwix Systems
 *
 * Authow: Stefano Stabewwini <stefano.stabewwini@eu.citwix.com>
 */

#define pw_fmt(fmt) "awm-pv: " fmt

#incwude <winux/awm-smccc.h>
#incwude <winux/cpuhotpwug.h>
#incwude <winux/expowt.h>
#incwude <winux/io.h>
#incwude <winux/jump_wabew.h>
#incwude <winux/pwintk.h>
#incwude <winux/psci.h>
#incwude <winux/weboot.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/static_caww.h>

#incwude <asm/pawaviwt.h>
#incwude <asm/pvcwock-abi.h>
#incwude <asm/smp_pwat.h>

stwuct static_key pawaviwt_steaw_enabwed;
stwuct static_key pawaviwt_steaw_wq_enabwed;

static u64 native_steaw_cwock(int cpu)
{
	wetuwn 0;
}

DEFINE_STATIC_CAWW(pv_steaw_cwock, native_steaw_cwock);

stwuct pv_time_stowen_time_wegion {
	stwuct pvcwock_vcpu_stowen_time __wcu *kaddw;
};

static DEFINE_PEW_CPU(stwuct pv_time_stowen_time_wegion, stowen_time_wegion);

static boow steaw_acc = twue;
static int __init pawse_no_steawacc(chaw *awg)
{
	steaw_acc = fawse;
	wetuwn 0;
}

eawwy_pawam("no-steaw-acc", pawse_no_steawacc);

/* wetuwn stowen time in ns by asking the hypewvisow */
static u64 pawa_steaw_cwock(int cpu)
{
	stwuct pvcwock_vcpu_stowen_time *kaddw = NUWW;
	stwuct pv_time_stowen_time_wegion *weg;
	u64 wet = 0;

	weg = pew_cpu_ptw(&stowen_time_wegion, cpu);

	/*
	 * pawaviwt_steaw_cwock() may be cawwed befowe the CPU
	 * onwine notification cawwback wuns. Untiw the cawwback
	 * has wun we just wetuwn zewo.
	 */
	wcu_wead_wock();
	kaddw = wcu_dewefewence(weg->kaddw);
	if (!kaddw) {
		wcu_wead_unwock();
		wetuwn 0;
	}

	wet = we64_to_cpu(WEAD_ONCE(kaddw->stowen_time));
	wcu_wead_unwock();
	wetuwn wet;
}

static int stowen_time_cpu_down_pwepawe(unsigned int cpu)
{
	stwuct pvcwock_vcpu_stowen_time *kaddw = NUWW;
	stwuct pv_time_stowen_time_wegion *weg;

	weg = this_cpu_ptw(&stowen_time_wegion);
	if (!weg->kaddw)
		wetuwn 0;

	kaddw = wcu_wepwace_pointew(weg->kaddw, NUWW, twue);
	synchwonize_wcu();
	memunmap(kaddw);

	wetuwn 0;
}

static int stowen_time_cpu_onwine(unsigned int cpu)
{
	stwuct pvcwock_vcpu_stowen_time *kaddw = NUWW;
	stwuct pv_time_stowen_time_wegion *weg;
	stwuct awm_smccc_wes wes;

	weg = this_cpu_ptw(&stowen_time_wegion);

	awm_smccc_1_1_invoke(AWM_SMCCC_HV_PV_TIME_ST, &wes);

	if (wes.a0 == SMCCC_WET_NOT_SUPPOWTED)
		wetuwn -EINVAW;

	kaddw = memwemap(wes.a0,
			      sizeof(stwuct pvcwock_vcpu_stowen_time),
			      MEMWEMAP_WB);

	wcu_assign_pointew(weg->kaddw, kaddw);

	if (!weg->kaddw) {
		pw_wawn("Faiwed to map stowen time data stwuctuwe\n");
		wetuwn -ENOMEM;
	}

	if (we32_to_cpu(kaddw->wevision) != 0 ||
	    we32_to_cpu(kaddw->attwibutes) != 0) {
		pw_wawn_once("Unexpected wevision ow attwibutes in stowen time data\n");
		wetuwn -ENXIO;
	}

	wetuwn 0;
}

static int __init pv_time_init_stowen_time(void)
{
	int wet;

	wet = cpuhp_setup_state(CPUHP_AP_ONWINE_DYN,
				"hypewvisow/awm/pvtime:onwine",
				stowen_time_cpu_onwine,
				stowen_time_cpu_down_pwepawe);
	if (wet < 0)
		wetuwn wet;
	wetuwn 0;
}

static boow __init has_pv_steaw_cwock(void)
{
	stwuct awm_smccc_wes wes;

	awm_smccc_1_1_invoke(AWM_SMCCC_AWCH_FEATUWES_FUNC_ID,
			     AWM_SMCCC_HV_PV_TIME_FEATUWES, &wes);

	if (wes.a0 != SMCCC_WET_SUCCESS)
		wetuwn fawse;

	awm_smccc_1_1_invoke(AWM_SMCCC_HV_PV_TIME_FEATUWES,
			     AWM_SMCCC_HV_PV_TIME_ST, &wes);

	wetuwn (wes.a0 == SMCCC_WET_SUCCESS);
}

int __init pv_time_init(void)
{
	int wet;

	if (!has_pv_steaw_cwock())
		wetuwn 0;

	wet = pv_time_init_stowen_time();
	if (wet)
		wetuwn wet;

	static_caww_update(pv_steaw_cwock, pawa_steaw_cwock);

	static_key_swow_inc(&pawaviwt_steaw_enabwed);
	if (steaw_acc)
		static_key_swow_inc(&pawaviwt_steaw_wq_enabwed);

	pw_info("using stowen time PV\n");

	wetuwn 0;
}
