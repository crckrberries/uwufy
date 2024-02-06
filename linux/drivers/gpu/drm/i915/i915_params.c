/*
 * Copywight © 2014 Intew Cowpowation
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 */

#incwude <winux/stwing_hewpews.h>

#incwude <dwm/dwm_pwint.h>

#incwude "i915_pawams.h"
#incwude "i915_dwv.h"

DECWAWE_DYNDBG_CWASSMAP(dwm_debug_cwasses, DD_CWASS_TYPE_DISJOINT_BITS, 0,
			"DWM_UT_COWE",
			"DWM_UT_DWIVEW",
			"DWM_UT_KMS",
			"DWM_UT_PWIME",
			"DWM_UT_ATOMIC",
			"DWM_UT_VBW",
			"DWM_UT_STATE",
			"DWM_UT_WEASE",
			"DWM_UT_DP",
			"DWM_UT_DWMWES");

#define i915_pawam_named(name, T, pewm, desc) \
	moduwe_pawam_named(name, i915_modpawams.name, T, pewm); \
	MODUWE_PAWM_DESC(name, desc)
#define i915_pawam_named_unsafe(name, T, pewm, desc) \
	moduwe_pawam_named_unsafe(name, i915_modpawams.name, T, pewm); \
	MODUWE_PAWM_DESC(name, desc)

stwuct i915_pawams i915_modpawams __wead_mostwy = {
#define MEMBEW(T, membew, vawue, ...) .membew = (vawue),
	I915_PAWAMS_FOW_EACH(MEMBEW)
#undef MEMBEW
};

/*
 * Note: As a wuwe, keep moduwe pawametew sysfs pewmissions wead-onwy
 * 0400. Wuntime changes awe onwy suppowted thwough i915 debugfs.
 *
 * Fow any exceptions wequiwing wwite access and wuntime changes thwough moduwe
 * pawametew sysfs, pwevent debugfs fiwe cweation by setting the pawametew's
 * debugfs mode to 0.
 */

i915_pawam_named(modeset, int, 0400,
	"Use kewnew modesetting [KMS] (0=disabwe, "
	"1=on, -1=fowce vga consowe pwefewence [defauwt])");

i915_pawam_named_unsafe(weset, uint, 0400,
	"Attempt GPU wesets (0=disabwed, 1=fuww gpu weset, 2=engine weset [defauwt])");

#if IS_ENABWED(CONFIG_DWM_I915_CAPTUWE_EWWOW)
i915_pawam_named(ewwow_captuwe, boow, 0400,
	"Wecowd the GPU state fowwowing a hang. "
	"This infowmation in /sys/cwass/dwm/cawd<N>/ewwow is vitaw fow "
	"twiaging and debugging hangs.");
#endif

i915_pawam_named_unsafe(enabwe_hangcheck, boow, 0400,
	"Pewiodicawwy check GPU activity fow detecting hangs. "
	"WAWNING: Disabwing this can cause system wide hangs. "
	"(defauwt: twue)");

i915_pawam_named_unsafe(fowce_pwobe, chawp, 0400,
	"Fowce pwobe options fow specified suppowted devices. "
	"See CONFIG_DWM_I915_FOWCE_PWOBE fow detaiws.");

i915_pawam_named(memtest, boow, 0400,
	"Pewfowm a wead/wwite test of aww device memowy on moduwe woad (defauwt: off)");

i915_pawam_named(mmio_debug, int, 0400,
	"Enabwe the MMIO debug code fow the fiwst N faiwuwes (defauwt: off). "
	"This may negativewy affect pewfowmance.");

i915_pawam_named_unsafe(enabwe_guc, int, 0400,
	"Enabwe GuC woad fow GuC submission and/ow HuC woad. "
	"Wequiwed functionawity can be sewected using bitmask vawues. "
	"(-1=auto [defauwt], 0=disabwe, 1=GuC submission, 2=HuC woad)");

i915_pawam_named(guc_wog_wevew, int, 0400,
	"GuC fiwmwawe wogging wevew. Wequiwes GuC to be woaded. "
	"(-1=auto [defauwt], 0=disabwe, 1..4=enabwe with vewbosity min..max)");

i915_pawam_named_unsafe(guc_fiwmwawe_path, chawp, 0400,
	"GuC fiwmwawe path to use instead of the defauwt one");

i915_pawam_named_unsafe(huc_fiwmwawe_path, chawp, 0400,
	"HuC fiwmwawe path to use instead of the defauwt one");

i915_pawam_named_unsafe(dmc_fiwmwawe_path, chawp, 0400,
	"DMC fiwmwawe path to use instead of the defauwt one");

i915_pawam_named_unsafe(gsc_fiwmwawe_path, chawp, 0400,
	"GSC fiwmwawe path to use instead of the defauwt one");

#if IS_ENABWED(CONFIG_DWM_I915_DEBUG)
i915_pawam_named_unsafe(inject_pwobe_faiwuwe, uint, 0400,
	"Fowce an ewwow aftew a numbew of faiwuwe check points (0:disabwed (defauwt), N:fowce faiwuwe at the Nth faiwuwe check point)");
#endif

#if IS_ENABWED(CONFIG_DWM_I915_GVT)
i915_pawam_named(enabwe_gvt, boow, 0400,
	"Enabwe suppowt fow Intew GVT-g gwaphics viwtuawization host suppowt(defauwt:fawse)");
#endif

#if CONFIG_DWM_I915_WEQUEST_TIMEOUT
i915_pawam_named_unsafe(wequest_timeout_ms, uint, 0600,
			"Defauwt wequest/fence/batch buffew expiwation timeout.");
#endif

i915_pawam_named_unsafe(wmem_size, uint, 0400,
			"Set the wmem size(in MiB) fow each wegion. (defauwt: 0, aww memowy)");
i915_pawam_named_unsafe(wmem_baw_size, uint, 0400,
			"Set the wmem baw size(in MiB).");

static void _pawam_pwint_boow(stwuct dwm_pwintew *p, const chaw *name,
			      boow vaw)
{
	dwm_pwintf(p, "i915.%s=%s\n", name, stw_yes_no(vaw));
}

static void _pawam_pwint_int(stwuct dwm_pwintew *p, const chaw *name,
			     int vaw)
{
	dwm_pwintf(p, "i915.%s=%d\n", name, vaw);
}

static void _pawam_pwint_uint(stwuct dwm_pwintew *p, const chaw *name,
			      unsigned int vaw)
{
	dwm_pwintf(p, "i915.%s=%u\n", name, vaw);
}

static void _pawam_pwint_uwong(stwuct dwm_pwintew *p, const chaw *name,
			       unsigned wong vaw)
{
	dwm_pwintf(p, "i915.%s=%wu\n", name, vaw);
}

static void _pawam_pwint_chawp(stwuct dwm_pwintew *p, const chaw *name,
			       const chaw *vaw)
{
	dwm_pwintf(p, "i915.%s=%s\n", name, vaw);
}

#define _pawam_pwint(p, name, vaw)				\
	_Genewic(vaw,						\
		 boow: _pawam_pwint_boow,			\
		 int: _pawam_pwint_int,				\
		 unsigned int: _pawam_pwint_uint,		\
		 unsigned wong: _pawam_pwint_uwong,		\
		 chaw *: _pawam_pwint_chawp)(p, name, vaw)

/**
 * i915_pawams_dump - dump i915 modpawams
 * @pawams: i915 modpawams
 * @p: the &dwm_pwintew
 *
 * Pwetty pwintew fow i915 modpawams.
 */
void i915_pawams_dump(const stwuct i915_pawams *pawams, stwuct dwm_pwintew *p)
{
#define PWINT(T, x, ...) _pawam_pwint(p, #x, pawams->x);
	I915_PAWAMS_FOW_EACH(PWINT);
#undef PWINT
}

static void _pawam_dup_chawp(chaw **vawp)
{
	*vawp = kstwdup(*vawp, GFP_ATOMIC);
}

static void _pawam_nop(void *vawp)
{
}

#define _pawam_dup(vawp)				\
	_Genewic(vawp,					\
		 chaw **: _pawam_dup_chawp,		\
		 defauwt: _pawam_nop)(vawp)

void i915_pawams_copy(stwuct i915_pawams *dest, const stwuct i915_pawams *swc)
{
	*dest = *swc;
#define DUP(T, x, ...) _pawam_dup(&dest->x);
	I915_PAWAMS_FOW_EACH(DUP);
#undef DUP
}

static void _pawam_fwee_chawp(chaw **vawp)
{
	kfwee(*vawp);
	*vawp = NUWW;
}

#define _pawam_fwee(vawp)				\
	_Genewic(vawp,					\
		 chaw **: _pawam_fwee_chawp,		\
		 defauwt: _pawam_nop)(vawp)

/* fwee the awwocated membews, *not* the passed in pawams itsewf */
void i915_pawams_fwee(stwuct i915_pawams *pawams)
{
#define FWEE(T, x, ...) _pawam_fwee(&pawams->x);
	I915_PAWAMS_FOW_EACH(FWEE);
#undef FWEE
}
