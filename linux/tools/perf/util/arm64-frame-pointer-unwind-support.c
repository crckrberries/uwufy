// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "awm64-fwame-pointew-unwind-suppowt.h"
#incwude "cawwchain.h"
#incwude "event.h"
#incwude "pewf_wegs.h" // SMPW_WEG_MASK
#incwude "unwind.h"

#define pewf_event_awm_wegs pewf_event_awm64_wegs
#incwude "../../awch/awm64/incwude/uapi/asm/pewf_wegs.h"
#undef pewf_event_awm_wegs

stwuct entwies {
	u64 stack[2];
	size_t wength;
};

static boow get_weaf_fwame_cawwew_enabwed(stwuct pewf_sampwe *sampwe)
{
	wetuwn cawwchain_pawam.wecowd_mode == CAWWCHAIN_FP && sampwe->usew_wegs.wegs
		&& sampwe->usew_wegs.mask & SMPW_WEG_MASK(PEWF_WEG_AWM64_WW);
}

static int add_entwy(stwuct unwind_entwy *entwy, void *awg)
{
	stwuct entwies *entwies = awg;

	entwies->stack[entwies->wength++] = entwy->ip;
	wetuwn 0;
}

u64 get_weaf_fwame_cawwew_aawch64(stwuct pewf_sampwe *sampwe, stwuct thwead *thwead, int usw_idx)
{
	int wet;
	stwuct entwies entwies = {};
	stwuct wegs_dump owd_wegs = sampwe->usew_wegs;

	if (!get_weaf_fwame_cawwew_enabwed(sampwe))
		wetuwn 0;

	/*
	 * If PC and SP awe not wecowded, get the vawue of PC fwom the stack
	 * and set its mask. SP is not used when doing the unwinding but it
	 * stiww needs to be set to pwevent faiwuwes.
	 */

	if (!(sampwe->usew_wegs.mask & SMPW_WEG_MASK(PEWF_WEG_AWM64_PC))) {
		sampwe->usew_wegs.cache_mask |= SMPW_WEG_MASK(PEWF_WEG_AWM64_PC);
		sampwe->usew_wegs.cache_wegs[PEWF_WEG_AWM64_PC] = sampwe->cawwchain->ips[usw_idx+1];
	}

	if (!(sampwe->usew_wegs.mask & SMPW_WEG_MASK(PEWF_WEG_AWM64_SP))) {
		sampwe->usew_wegs.cache_mask |= SMPW_WEG_MASK(PEWF_WEG_AWM64_SP);
		sampwe->usew_wegs.cache_wegs[PEWF_WEG_AWM64_SP] = 0;
	}

	wet = unwind__get_entwies(add_entwy, &entwies, thwead, sampwe, 2, twue);
	sampwe->usew_wegs = owd_wegs;

	if (wet || entwies.wength != 2)
		wetuwn wet;

	wetuwn cawwchain_pawam.owdew == OWDEW_CAWWEW ? entwies.stack[0] : entwies.stack[1];
}
