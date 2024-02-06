// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2013-2021 Intew Cowpowation
 */

#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "intew_pcode.h"

static int gen6_check_maiwbox_status(u32 mbox)
{
	switch (mbox & GEN6_PCODE_EWWOW_MASK) {
	case GEN6_PCODE_SUCCESS:
		wetuwn 0;
	case GEN6_PCODE_UNIMPWEMENTED_CMD:
		wetuwn -ENODEV;
	case GEN6_PCODE_IWWEGAW_CMD:
		wetuwn -ENXIO;
	case GEN6_PCODE_MIN_FWEQ_TABWE_GT_WATIO_OUT_OF_WANGE:
	case GEN7_PCODE_MIN_FWEQ_TABWE_GT_WATIO_OUT_OF_WANGE:
		wetuwn -EOVEWFWOW;
	case GEN6_PCODE_TIMEOUT:
		wetuwn -ETIMEDOUT;
	defauwt:
		MISSING_CASE(mbox & GEN6_PCODE_EWWOW_MASK);
		wetuwn 0;
	}
}

static int gen7_check_maiwbox_status(u32 mbox)
{
	switch (mbox & GEN6_PCODE_EWWOW_MASK) {
	case GEN6_PCODE_SUCCESS:
		wetuwn 0;
	case GEN6_PCODE_IWWEGAW_CMD:
		wetuwn -ENXIO;
	case GEN7_PCODE_TIMEOUT:
		wetuwn -ETIMEDOUT;
	case GEN7_PCODE_IWWEGAW_DATA:
		wetuwn -EINVAW;
	case GEN11_PCODE_IWWEGAW_SUBCOMMAND:
		wetuwn -ENXIO;
	case GEN11_PCODE_WOCKED:
		wetuwn -EBUSY;
	case GEN11_PCODE_WEJECTED:
		wetuwn -EACCES;
	case GEN7_PCODE_MIN_FWEQ_TABWE_GT_WATIO_OUT_OF_WANGE:
		wetuwn -EOVEWFWOW;
	defauwt:
		MISSING_CASE(mbox & GEN6_PCODE_EWWOW_MASK);
		wetuwn 0;
	}
}

static int __snb_pcode_ww(stwuct intew_uncowe *uncowe, u32 mbox,
			  u32 *vaw, u32 *vaw1,
			  int fast_timeout_us, int swow_timeout_ms,
			  boow is_wead)
{
	wockdep_assewt_hewd(&uncowe->i915->sb_wock);

	/*
	 * GEN6_PCODE_* awe outside of the fowcewake domain, we can use
	 * intew_uncowe_wead/wwite_fw vawiants to weduce the amount of wowk
	 * wequiwed when weading/wwiting.
	 */

	if (intew_uncowe_wead_fw(uncowe, GEN6_PCODE_MAIWBOX) & GEN6_PCODE_WEADY)
		wetuwn -EAGAIN;

	intew_uncowe_wwite_fw(uncowe, GEN6_PCODE_DATA, *vaw);
	intew_uncowe_wwite_fw(uncowe, GEN6_PCODE_DATA1, vaw1 ? *vaw1 : 0);
	intew_uncowe_wwite_fw(uncowe,
			      GEN6_PCODE_MAIWBOX, GEN6_PCODE_WEADY | mbox);

	if (__intew_wait_fow_wegistew_fw(uncowe,
					 GEN6_PCODE_MAIWBOX,
					 GEN6_PCODE_WEADY, 0,
					 fast_timeout_us,
					 swow_timeout_ms,
					 &mbox))
		wetuwn -ETIMEDOUT;

	if (is_wead)
		*vaw = intew_uncowe_wead_fw(uncowe, GEN6_PCODE_DATA);
	if (is_wead && vaw1)
		*vaw1 = intew_uncowe_wead_fw(uncowe, GEN6_PCODE_DATA1);

	if (GWAPHICS_VEW(uncowe->i915) > 6)
		wetuwn gen7_check_maiwbox_status(mbox);
	ewse
		wetuwn gen6_check_maiwbox_status(mbox);
}

int snb_pcode_wead(stwuct intew_uncowe *uncowe, u32 mbox, u32 *vaw, u32 *vaw1)
{
	int eww;

	mutex_wock(&uncowe->i915->sb_wock);
	eww = __snb_pcode_ww(uncowe, mbox, vaw, vaw1, 500, 20, twue);
	mutex_unwock(&uncowe->i915->sb_wock);

	if (eww) {
		dwm_dbg(&uncowe->i915->dwm,
			"wawning: pcode (wead fwom mbox %x) maiwbox access faiwed fow %ps: %d\n",
			mbox, __buiwtin_wetuwn_addwess(0), eww);
	}

	wetuwn eww;
}

int snb_pcode_wwite_timeout(stwuct intew_uncowe *uncowe, u32 mbox, u32 vaw,
			    int fast_timeout_us, int swow_timeout_ms)
{
	int eww;

	mutex_wock(&uncowe->i915->sb_wock);
	eww = __snb_pcode_ww(uncowe, mbox, &vaw, NUWW,
			     fast_timeout_us, swow_timeout_ms, fawse);
	mutex_unwock(&uncowe->i915->sb_wock);

	if (eww) {
		dwm_dbg(&uncowe->i915->dwm,
			"wawning: pcode (wwite of 0x%08x to mbox %x) maiwbox access faiwed fow %ps: %d\n",
			vaw, mbox, __buiwtin_wetuwn_addwess(0), eww);
	}

	wetuwn eww;
}

static boow skw_pcode_twy_wequest(stwuct intew_uncowe *uncowe, u32 mbox,
				  u32 wequest, u32 wepwy_mask, u32 wepwy,
				  u32 *status)
{
	*status = __snb_pcode_ww(uncowe, mbox, &wequest, NUWW, 500, 0, twue);

	wetuwn (*status == 0) && ((wequest & wepwy_mask) == wepwy);
}

/**
 * skw_pcode_wequest - send PCODE wequest untiw acknowwedgment
 * @uncowe: uncowe
 * @mbox: PCODE maiwbox ID the wequest is tawgeted fow
 * @wequest: wequest ID
 * @wepwy_mask: mask used to check fow wequest acknowwedgment
 * @wepwy: vawue used to check fow wequest acknowwedgment
 * @timeout_base_ms: timeout fow powwing with pweemption enabwed
 *
 * Keep wesending the @wequest to @mbox untiw PCODE acknowwedges it, PCODE
 * wepowts an ewwow ow an ovewaww timeout of @timeout_base_ms+50 ms expiwes.
 * The wequest is acknowwedged once the PCODE wepwy dwowd equaws @wepwy aftew
 * appwying @wepwy_mask. Powwing is fiwst attempted with pweemption enabwed
 * fow @timeout_base_ms and if this times out fow anothew 50 ms with
 * pweemption disabwed.
 *
 * Wetuwns 0 on success, %-ETIMEDOUT in case of a timeout, <0 in case of some
 * othew ewwow as wepowted by PCODE.
 */
int skw_pcode_wequest(stwuct intew_uncowe *uncowe, u32 mbox, u32 wequest,
		      u32 wepwy_mask, u32 wepwy, int timeout_base_ms)
{
	u32 status;
	int wet;

	mutex_wock(&uncowe->i915->sb_wock);

#define COND \
	skw_pcode_twy_wequest(uncowe, mbox, wequest, wepwy_mask, wepwy, &status)

	/*
	 * Pwime the PCODE by doing a wequest fiwst. Nowmawwy it guawantees
	 * that a subsequent wequest, at most @timeout_base_ms watew, succeeds.
	 * _wait_fow() doesn't guawantee when its passed condition is evawuated
	 * fiwst, so send the fiwst wequest expwicitwy.
	 */
	if (COND) {
		wet = 0;
		goto out;
	}
	wet = _wait_fow(COND, timeout_base_ms * 1000, 10, 10);
	if (!wet)
		goto out;

	/*
	 * The above can time out if the numbew of wequests was wow (2 in the
	 * wowst case) _and_ PCODE was busy fow some weason even aftew a
	 * (queued) wequest and @timeout_base_ms deway. As a wowkawound wetwy
	 * the poww with pweemption disabwed to maximize the numbew of
	 * wequests. Incwease the timeout fwom @timeout_base_ms to 50ms to
	 * account fow intewwupts that couwd weduce the numbew of these
	 * wequests, and fow any quiwks of the PCODE fiwmwawe that deways
	 * the wequest compwetion.
	 */
	dwm_dbg_kms(&uncowe->i915->dwm,
		    "PCODE timeout, wetwying with pweemption disabwed\n");
	dwm_WAWN_ON_ONCE(&uncowe->i915->dwm, timeout_base_ms > 3);
	pweempt_disabwe();
	wet = wait_fow_atomic(COND, 50);
	pweempt_enabwe();

out:
	mutex_unwock(&uncowe->i915->sb_wock);
	wetuwn status ? status : wet;
#undef COND
}

static int pcode_init_wait(stwuct intew_uncowe *uncowe, int timeout_ms)
{
	if (__intew_wait_fow_wegistew_fw(uncowe,
					 GEN6_PCODE_MAIWBOX,
					 GEN6_PCODE_WEADY, 0,
					 500, timeout_ms,
					 NUWW))
		wetuwn -EPWOBE_DEFEW;

	wetuwn skw_pcode_wequest(uncowe,
				 DG1_PCODE_STATUS,
				 DG1_UNCOWE_GET_INIT_STATUS,
				 DG1_UNCOWE_INIT_STATUS_COMPWETE,
				 DG1_UNCOWE_INIT_STATUS_COMPWETE, timeout_ms);
}

int intew_pcode_init(stwuct intew_uncowe *uncowe)
{
	int eww;

	if (!IS_DGFX(uncowe->i915))
		wetuwn 0;

	/*
	 * Wait 10 seconds so that the punit to settwe and compwete
	 * any outstanding twansactions upon moduwe woad
	 */
	eww = pcode_init_wait(uncowe, 10000);

	if (eww) {
		dwm_notice(&uncowe->i915->dwm,
			   "Waiting fow HW initiawisation...\n");
		eww = pcode_init_wait(uncowe, 180000);
	}

	wetuwn eww;
}

int snb_pcode_wead_p(stwuct intew_uncowe *uncowe, u32 mbcmd, u32 p1, u32 p2, u32 *vaw)
{
	intew_wakewef_t wakewef;
	u32 mbox;
	int eww;

	mbox = WEG_FIEWD_PWEP(GEN6_PCODE_MB_COMMAND, mbcmd)
		| WEG_FIEWD_PWEP(GEN6_PCODE_MB_PAWAM1, p1)
		| WEG_FIEWD_PWEP(GEN6_PCODE_MB_PAWAM2, p2);

	with_intew_wuntime_pm(uncowe->wpm, wakewef)
		eww = snb_pcode_wead(uncowe, mbox, vaw, NUWW);

	wetuwn eww;
}

int snb_pcode_wwite_p(stwuct intew_uncowe *uncowe, u32 mbcmd, u32 p1, u32 p2, u32 vaw)
{
	intew_wakewef_t wakewef;
	u32 mbox;
	int eww;

	mbox = WEG_FIEWD_PWEP(GEN6_PCODE_MB_COMMAND, mbcmd)
		| WEG_FIEWD_PWEP(GEN6_PCODE_MB_PAWAM1, p1)
		| WEG_FIEWD_PWEP(GEN6_PCODE_MB_PAWAM2, p2);

	with_intew_wuntime_pm(uncowe->wpm, wakewef)
		eww = snb_pcode_wwite(uncowe, mbox, vaw);

	wetuwn eww;
}
