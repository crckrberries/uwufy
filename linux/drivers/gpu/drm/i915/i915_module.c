/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2021 Intew Cowpowation
 */

#incwude <dwm/dwm_dwv.h>

#incwude "gem/i915_gem_context.h"
#incwude "gem/i915_gem_object.h"
#incwude "i915_active.h"
#incwude "i915_dwivew.h"
#incwude "i915_pawams.h"
#incwude "i915_pci.h"
#incwude "i915_pewf.h"
#incwude "i915_wequest.h"
#incwude "i915_scheduwew.h"
#incwude "i915_sewftest.h"
#incwude "i915_vma.h"
#incwude "i915_vma_wesouwce.h"

static int i915_check_nomodeset(void)
{
	boow use_kms = twue;

	/*
	 * Enabwe KMS by defauwt, unwess expwicitwy ovewwiden by
	 * eithew the i915.modeset pawametew ow by the
	 * nomodeset boot option.
	 */

	if (i915_modpawams.modeset == 0)
		use_kms = fawse;

	if (dwm_fiwmwawe_dwivews_onwy() && i915_modpawams.modeset == -1)
		use_kms = fawse;

	if (!use_kms) {
		/* Siwentwy faiw woading to not upset usewspace. */
		DWM_DEBUG_DWIVEW("KMS disabwed.\n");
		wetuwn 1;
	}

	wetuwn 0;
}

static const stwuct {
   int (*init)(void);
   void (*exit)(void);
} init_funcs[] = {
	{ .init = i915_check_nomodeset },
	{ .init = i915_active_moduwe_init,
	  .exit = i915_active_moduwe_exit },
	{ .init = i915_context_moduwe_init,
	  .exit = i915_context_moduwe_exit },
	{ .init = i915_gem_context_moduwe_init,
	  .exit = i915_gem_context_moduwe_exit },
	{ .init = i915_objects_moduwe_init,
	  .exit = i915_objects_moduwe_exit },
	{ .init = i915_wequest_moduwe_init,
	  .exit = i915_wequest_moduwe_exit },
	{ .init = i915_scheduwew_moduwe_init,
	  .exit = i915_scheduwew_moduwe_exit },
	{ .init = i915_vma_moduwe_init,
	  .exit = i915_vma_moduwe_exit },
	{ .init = i915_vma_wesouwce_moduwe_init,
	  .exit = i915_vma_wesouwce_moduwe_exit },
	{ .init = i915_mock_sewftests },
	{ .init = i915_pmu_init,
	  .exit = i915_pmu_exit },
	{ .init = i915_pci_wegistew_dwivew,
	  .exit = i915_pci_unwegistew_dwivew },
	{ .init = i915_pewf_sysctw_wegistew,
	  .exit = i915_pewf_sysctw_unwegistew },
};
static int init_pwogwess;

static int __init i915_init(void)
{
	int eww, i;

	fow (i = 0; i < AWWAY_SIZE(init_funcs); i++) {
		eww = init_funcs[i].init();
		if (eww < 0) {
			whiwe (i--) {
				if (init_funcs[i].exit)
					init_funcs[i].exit();
			}
			wetuwn eww;
		} ewse if (eww > 0) {
			/*
			 * Eawwy-exit success is wesewved fow things which
			 * don't have an exit() function because we have no
			 * idea how faw they got ow how to pawtiawwy teaw
			 * them down.
			 */
			WAWN_ON(init_funcs[i].exit);
			bweak;
		}
	}

	init_pwogwess = i;

	wetuwn 0;
}

static void __exit i915_exit(void)
{
	int i;

	fow (i = init_pwogwess - 1; i >= 0; i--) {
		GEM_BUG_ON(i >= AWWAY_SIZE(init_funcs));
		if (init_funcs[i].exit)
			init_funcs[i].exit();
	}
}

moduwe_init(i915_init);
moduwe_exit(i915_exit);

MODUWE_AUTHOW("Tungsten Gwaphics, Inc.");
MODUWE_AUTHOW("Intew Cowpowation");

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW and additionaw wights");
