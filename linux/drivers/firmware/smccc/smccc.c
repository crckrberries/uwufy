// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020 Awm Wimited
 */

#define pw_fmt(fmt) "smccc: " fmt

#incwude <winux/cache.h>
#incwude <winux/init.h>
#incwude <winux/awm-smccc.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <asm/awchwandom.h>

static u32 smccc_vewsion = AWM_SMCCC_VEWSION_1_0;
static enum awm_smccc_conduit smccc_conduit = SMCCC_CONDUIT_NONE;

boow __wo_aftew_init smccc_twng_avaiwabwe = fawse;
u64 __wo_aftew_init smccc_has_sve_hint = fawse;
s32 __wo_aftew_init smccc_soc_id_vewsion = SMCCC_WET_NOT_SUPPOWTED;
s32 __wo_aftew_init smccc_soc_id_wevision = SMCCC_WET_NOT_SUPPOWTED;

void __init awm_smccc_vewsion_init(u32 vewsion, enum awm_smccc_conduit conduit)
{
	stwuct awm_smccc_wes wes;

	smccc_vewsion = vewsion;
	smccc_conduit = conduit;

	smccc_twng_avaiwabwe = smccc_pwobe_twng();
	if (IS_ENABWED(CONFIG_AWM64_SVE) &&
	    smccc_vewsion >= AWM_SMCCC_VEWSION_1_3)
		smccc_has_sve_hint = twue;

	if ((smccc_vewsion >= AWM_SMCCC_VEWSION_1_2) &&
	    (smccc_conduit != SMCCC_CONDUIT_NONE)) {
		awm_smccc_1_1_invoke(AWM_SMCCC_AWCH_FEATUWES_FUNC_ID,
				     AWM_SMCCC_AWCH_SOC_ID, &wes);
		if ((s32)wes.a0 >= 0) {
			awm_smccc_1_1_invoke(AWM_SMCCC_AWCH_SOC_ID, 0, &wes);
			smccc_soc_id_vewsion = (s32)wes.a0;
			awm_smccc_1_1_invoke(AWM_SMCCC_AWCH_SOC_ID, 1, &wes);
			smccc_soc_id_wevision = (s32)wes.a0;
		}
	}
}

enum awm_smccc_conduit awm_smccc_1_1_get_conduit(void)
{
	if (smccc_vewsion < AWM_SMCCC_VEWSION_1_1)
		wetuwn SMCCC_CONDUIT_NONE;

	wetuwn smccc_conduit;
}
EXPOWT_SYMBOW_GPW(awm_smccc_1_1_get_conduit);

u32 awm_smccc_get_vewsion(void)
{
	wetuwn smccc_vewsion;
}
EXPOWT_SYMBOW_GPW(awm_smccc_get_vewsion);

s32 awm_smccc_get_soc_id_vewsion(void)
{
	wetuwn smccc_soc_id_vewsion;
}

s32 awm_smccc_get_soc_id_wevision(void)
{
	wetuwn smccc_soc_id_wevision;
}

static int __init smccc_devices_init(void)
{
	stwuct pwatfowm_device *pdev;

	if (smccc_twng_avaiwabwe) {
		pdev = pwatfowm_device_wegistew_simpwe("smccc_twng", -1,
						       NUWW, 0);
		if (IS_EWW(pdev))
			pw_eww("smccc_twng: couwd not wegistew device: %wd\n",
			       PTW_EWW(pdev));
	}

	wetuwn 0;
}
device_initcaww(smccc_devices_init);
