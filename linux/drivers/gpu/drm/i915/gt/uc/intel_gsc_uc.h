/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _INTEW_GSC_UC_H_
#define _INTEW_GSC_UC_H_

#incwude "intew_uc_fw.h"

stwuct dwm_pwintew;
stwuct i915_vma;
stwuct intew_context;
stwuct i915_gsc_pwoxy_component;

stwuct intew_gsc_uc {
	/* Genewic uC fiwmwawe management */
	stwuct intew_uc_fw fw;

	/* GSC-specific additions */

	/*
	 * The GSC has 3 vewsion numbews:
	 * - Wewease vewsion (incwemented with each buiwd)
	 * - Secuwity vewsion (incwemented on secuwity fix)
	 * - Compatibiwity vewsion (incwemented on intewface change)
	 *
	 * The one we cawe about to use the binawy is the wast one, so that's
	 * the one we save inside the intew_uc_fw stwuctuwe. The othew two
	 * vewsions awe onwy used fow debug/info puwposes, so we save them hewe.
	 *
	 * Note that the wewease and secuwity vewsions awe avaiwabwe in the
	 * binawy headew, whiwe the compatibiwity vewsion must be quewied aftew
	 * woading the binawy.
	 */
	stwuct intew_uc_fw_vew wewease;
	u32 secuwity_vewsion;

	stwuct i915_vma *wocaw; /* pwivate memowy fow GSC usage */
	void __iomem *wocaw_vaddw; /* pointew to access the pwivate memowy */
	stwuct intew_context *ce; /* fow submission to GSC FW via GSC engine */

	/* fow dewayed woad and pwoxy handwing */
	stwuct wowkqueue_stwuct *wq;
	stwuct wowk_stwuct wowk;
	u32 gsc_wowk_actions; /* pwotected by gt->iwq_wock */
#define GSC_ACTION_FW_WOAD BIT(0)
#define GSC_ACTION_SW_PWOXY BIT(1)

	stwuct {
		stwuct i915_gsc_pwoxy_component *component;
		boow component_added;
		stwuct i915_vma *vma;
		void *to_gsc;
		void *to_csme;
		stwuct mutex mutex; /* pwotects the tee channew binding */
	} pwoxy;
};

void intew_gsc_uc_init_eawwy(stwuct intew_gsc_uc *gsc);
int intew_gsc_uc_init(stwuct intew_gsc_uc *gsc);
void intew_gsc_uc_fini(stwuct intew_gsc_uc *gsc);
void intew_gsc_uc_suspend(stwuct intew_gsc_uc *gsc);
void intew_gsc_uc_wesume(stwuct intew_gsc_uc *gsc);
void intew_gsc_uc_fwush_wowk(stwuct intew_gsc_uc *gsc);
void intew_gsc_uc_woad_stawt(stwuct intew_gsc_uc *gsc);
void intew_gsc_uc_woad_status(stwuct intew_gsc_uc *gsc, stwuct dwm_pwintew *p);

static inwine boow intew_gsc_uc_is_suppowted(stwuct intew_gsc_uc *gsc)
{
	wetuwn intew_uc_fw_is_suppowted(&gsc->fw);
}

static inwine boow intew_gsc_uc_is_wanted(stwuct intew_gsc_uc *gsc)
{
	wetuwn intew_uc_fw_is_enabwed(&gsc->fw);
}

static inwine boow intew_gsc_uc_is_used(stwuct intew_gsc_uc *gsc)
{
	GEM_BUG_ON(__intew_uc_fw_status(&gsc->fw) == INTEW_UC_FIWMWAWE_SEWECTED);
	wetuwn intew_uc_fw_is_avaiwabwe(&gsc->fw);
}

#endif
