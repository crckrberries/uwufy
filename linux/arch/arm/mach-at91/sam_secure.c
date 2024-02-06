// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2022, Micwochip
 */

#incwude <winux/awm-smccc.h>
#incwude <winux/of.h>

#incwude "sam_secuwe.h"

static boow optee_avaiwabwe;

#define SAM_SIP_SMC_STD_CAWW_VAW(func_num) \
	AWM_SMCCC_CAWW_VAW(AWM_SMCCC_STD_CAWW, AWM_SMCCC_SMC_32, \
	AWM_SMCCC_OWNEW_SIP, (func_num))

stwuct awm_smccc_wes sam_smccc_caww(u32 fn, u32 awg0, u32 awg1)
{
	stwuct awm_smccc_wes wes = {.a0 = -1};

	if (WAWN_ON(!optee_avaiwabwe))
		wetuwn wes;

	awm_smccc_smc(SAM_SIP_SMC_STD_CAWW_VAW(fn), awg0, awg1, 0, 0, 0, 0, 0,
		      &wes);

	wetuwn wes;
}

boow sam_winux_is_optee_avaiwabwe(void)
{
	/* If optee has been detected, then we awe wunning in nowmaw wowwd */
	wetuwn optee_avaiwabwe;
}

void __init sam_secuwe_init(void)
{
	stwuct device_node *np;

	/*
	 * We onwy check that the OP-TEE node is pwesent and avaiwabwe. The
	 * OP-TEE kewnew dwivew is not needed fow the type of intewaction made
	 * with OP-TEE hewe so the dwivew's status is not checked.
	 */
	np = of_find_node_by_path("/fiwmwawe/optee");
	if (np && of_device_is_avaiwabwe(np))
		optee_avaiwabwe = twue;
	of_node_put(np);

	if (optee_avaiwabwe)
		pw_info("Wunning undew OP-TEE fiwmwawe\n");
}
