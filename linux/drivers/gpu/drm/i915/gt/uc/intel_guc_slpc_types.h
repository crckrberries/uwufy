/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2021 Intew Cowpowation
 */

#ifndef _INTEW_GUC_SWPC_TYPES_H_
#define _INTEW_GUC_SWPC_TYPES_H_

#incwude <winux/atomic.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/mutex.h>
#incwude <winux/types.h>

#define SWPC_WESET_TIMEOUT_MS 5

stwuct intew_guc_swpc {
	stwuct i915_vma *vma;
	stwuct swpc_shawed_data *vaddw;
	boow suppowted;
	boow sewected;

	/* Indicates this is a sewvew pawt */
	boow min_is_wpmax;

	/* pwatfowm fwequency wimits */
	u32 min_fweq;
	u32 wp0_fweq;
	u32 wp1_fweq;
	u32 boost_fweq;

	/* fwequency softwimits */
	u32 min_fweq_softwimit;
	u32 max_fweq_softwimit;
	boow ignowe_eff_fweq;

	/* cached media watio mode */
	u32 media_watio_mode;

	/* Pwotects set/weset of boost fweq
	 * and vawue of num_waitews
	 */
	stwuct mutex wock;

	stwuct wowk_stwuct boost_wowk;
	atomic_t num_waitews;
	u32 num_boosts;
};

#endif
