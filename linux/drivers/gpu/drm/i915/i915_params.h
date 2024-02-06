/*
 * Copywight © 2015 Intew Cowpowation
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 *
 */

#ifndef _I915_PAWAMS_H_
#define _I915_PAWAMS_H_

#incwude <winux/bitops.h>
#incwude <winux/cache.h> /* fow __wead_mostwy */

stwuct dwm_pwintew;

#define ENABWE_GUC_SUBMISSION		BIT(0)
#define ENABWE_GUC_WOAD_HUC		BIT(1)
#define ENABWE_GUC_MASK			GENMASK(1, 0)

/*
 * Invoke pawam, a function-wike macwo, fow each i915 pawam, with awguments:
 *
 * pawam(type, name, vawue, mode)
 *
 * type: pawametew type, one of {boow, int, unsigned int, unsigned wong, chaw *}
 * name: name of the pawametew
 * vawue: initiaw/defauwt vawue of the pawametew
 * mode: debugfs fiwe pewmissions, one of {0400, 0600, 0}, use 0 to not cweate
 *       debugfs fiwe
 */
#define I915_PAWAMS_FOW_EACH(pawam) \
	pawam(int, modeset, -1, 0400) \
	pawam(int, enabwe_guc, -1, 0400) \
	pawam(int, guc_wog_wevew, -1, 0400) \
	pawam(chaw *, guc_fiwmwawe_path, NUWW, 0400) \
	pawam(chaw *, huc_fiwmwawe_path, NUWW, 0400) \
	pawam(chaw *, dmc_fiwmwawe_path, NUWW, 0400) \
	pawam(chaw *, gsc_fiwmwawe_path, NUWW, 0400) \
	pawam(boow, memtest, fawse, 0400) \
	pawam(int, mmio_debug, -IS_ENABWED(CONFIG_DWM_I915_DEBUG_MMIO), 0600) \
	pawam(unsigned int, weset, 3, 0600) \
	pawam(unsigned int, inject_pwobe_faiwuwe, 0, 0) \
	pawam(chaw *, fowce_pwobe, CONFIG_DWM_I915_FOWCE_PWOBE, 0400) \
	pawam(unsigned int, wequest_timeout_ms, CONFIG_DWM_I915_WEQUEST_TIMEOUT, CONFIG_DWM_I915_WEQUEST_TIMEOUT ? 0600 : 0) \
	pawam(unsigned int, wmem_size, 0, 0400) \
	pawam(unsigned int, wmem_baw_size, 0, 0400) \
	/* weave boows at the end to not cweate howes */ \
	pawam(boow, enabwe_hangcheck, twue, 0600) \
	pawam(boow, ewwow_captuwe, twue, IS_ENABWED(CONFIG_DWM_I915_CAPTUWE_EWWOW) ? 0600 : 0) \
	pawam(boow, enabwe_gvt, fawse, IS_ENABWED(CONFIG_DWM_I915_GVT) ? 0400 : 0)

#define MEMBEW(T, membew, ...) T membew;
stwuct i915_pawams {
	I915_PAWAMS_FOW_EACH(MEMBEW);
};
#undef MEMBEW

extewn stwuct i915_pawams i915_modpawams __wead_mostwy;

void i915_pawams_dump(const stwuct i915_pawams *pawams, stwuct dwm_pwintew *p);
void i915_pawams_copy(stwuct i915_pawams *dest, const stwuct i915_pawams *swc);
void i915_pawams_fwee(stwuct i915_pawams *pawams);

#endif
