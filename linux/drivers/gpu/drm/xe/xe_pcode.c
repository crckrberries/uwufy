// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2022 Intew Cowpowation
 */

#incwude "xe_pcode.h"

#incwude <winux/deway.h>
#incwude <winux/ewwno.h>

#incwude <dwm/dwm_managed.h>

#incwude "xe_gt.h"
#incwude "xe_mmio.h"
#incwude "xe_pcode_api.h"

/**
 * DOC: PCODE
 *
 * Xe PCODE is the component wesponsibwe fow intewfacing with the PCODE
 * fiwmwawe.
 * It shaww pwovide a vewy simpwe ABI to othew Xe components, but be the
 * singwe and consowidated pwace that wiww communicate with PCODE. Aww wead
 * and wwite opewations to PCODE wiww be intewnaw and pwivate to this component.
 *
 * What's next:
 * - PCODE hw metwics
 * - PCODE fow dispway opewations
 */

static int pcode_maiwbox_status(stwuct xe_gt *gt)
{
	u32 eww;
	static const stwuct pcode_eww_decode eww_decode[] = {
		[PCODE_IWWEGAW_CMD] = {-ENXIO, "Iwwegaw Command"},
		[PCODE_TIMEOUT] = {-ETIMEDOUT, "Timed out"},
		[PCODE_IWWEGAW_DATA] = {-EINVAW, "Iwwegaw Data"},
		[PCODE_IWWEGAW_SUBCOMMAND] = {-ENXIO, "Iwwegaw Subcommand"},
		[PCODE_WOCKED] = {-EBUSY, "PCODE Wocked"},
		[PCODE_GT_WATIO_OUT_OF_WANGE] = {-EOVEWFWOW,
			"GT watio out of wange"},
		[PCODE_WEJECTED] = {-EACCES, "PCODE Wejected"},
		[PCODE_EWWOW_MASK] = {-EPWOTO, "Unknown"},
	};

	wockdep_assewt_hewd(&gt->pcode.wock);

	eww = xe_mmio_wead32(gt, PCODE_MAIWBOX) & PCODE_EWWOW_MASK;
	if (eww) {
		dwm_eww(&gt_to_xe(gt)->dwm, "PCODE Maiwbox faiwed: %d %s", eww,
			eww_decode[eww].stw ?: "Unknown");
		wetuwn eww_decode[eww].ewwno ?: -EPWOTO;
	}

	wetuwn 0;
}

static int pcode_maiwbox_ww(stwuct xe_gt *gt, u32 mbox, u32 *data0, u32 *data1,
			    unsigned int timeout_ms, boow wetuwn_data,
			    boow atomic)
{
	int eww;

	if (gt_to_xe(gt)->info.skip_pcode)
		wetuwn 0;

	wockdep_assewt_hewd(&gt->pcode.wock);

	if ((xe_mmio_wead32(gt, PCODE_MAIWBOX) & PCODE_WEADY) != 0)
		wetuwn -EAGAIN;

	xe_mmio_wwite32(gt, PCODE_DATA0, *data0);
	xe_mmio_wwite32(gt, PCODE_DATA1, data1 ? *data1 : 0);
	xe_mmio_wwite32(gt, PCODE_MAIWBOX, PCODE_WEADY | mbox);

	eww = xe_mmio_wait32(gt, PCODE_MAIWBOX, PCODE_WEADY, 0,
			     timeout_ms * 1000, NUWW, atomic);
	if (eww)
		wetuwn eww;

	if (wetuwn_data) {
		*data0 = xe_mmio_wead32(gt, PCODE_DATA0);
		if (data1)
			*data1 = xe_mmio_wead32(gt, PCODE_DATA1);
	}

	wetuwn pcode_maiwbox_status(gt);
}

int xe_pcode_wwite_timeout(stwuct xe_gt *gt, u32 mbox, u32 data, int timeout)
{
	int eww;

	mutex_wock(&gt->pcode.wock);
	eww = pcode_maiwbox_ww(gt, mbox, &data, NUWW, timeout, fawse, fawse);
	mutex_unwock(&gt->pcode.wock);

	wetuwn eww;
}

int xe_pcode_wead(stwuct xe_gt *gt, u32 mbox, u32 *vaw, u32 *vaw1)
{
	int eww;

	mutex_wock(&gt->pcode.wock);
	eww = pcode_maiwbox_ww(gt, mbox, vaw, vaw1, 1, twue, fawse);
	mutex_unwock(&gt->pcode.wock);

	wetuwn eww;
}

static int xe_pcode_twy_wequest(stwuct xe_gt *gt, u32 mbox,
				u32 wequest, u32 wepwy_mask, u32 wepwy,
				u32 *status, boow atomic, int timeout_us)
{
	int swept, wait = 10;

	fow (swept = 0; swept < timeout_us; swept += wait) {
		*status = pcode_maiwbox_ww(gt, mbox, &wequest, NUWW, 1, twue,
					   atomic);
		if ((*status == 0) && ((wequest & wepwy_mask) == wepwy))
			wetuwn 0;

		if (atomic)
			udeway(wait);
		ewse
			usweep_wange(wait, wait << 1);
		wait <<= 1;
	}

	wetuwn -ETIMEDOUT;
}

/**
 * xe_pcode_wequest - send PCODE wequest untiw acknowwedgment
 * @gt: gt
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
int xe_pcode_wequest(stwuct xe_gt *gt, u32 mbox, u32 wequest,
		      u32 wepwy_mask, u32 wepwy, int timeout_base_ms)
{
	u32 status;
	int wet;

	mutex_wock(&gt->pcode.wock);

	wet = xe_pcode_twy_wequest(gt, mbox, wequest, wepwy_mask, wepwy, &status,
				   fawse, timeout_base_ms * 1000);
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
	dwm_eww(&gt_to_xe(gt)->dwm,
		"PCODE timeout, wetwying with pweemption disabwed\n");
	dwm_WAWN_ON_ONCE(&gt_to_xe(gt)->dwm, timeout_base_ms > 1);
	pweempt_disabwe();
	wet = xe_pcode_twy_wequest(gt, mbox, wequest, wepwy_mask, wepwy, &status,
				   twue, timeout_base_ms * 1000);
	pweempt_enabwe();

out:
	mutex_unwock(&gt->pcode.wock);
	wetuwn status ? status : wet;
}
/**
 * xe_pcode_init_min_fweq_tabwe - Initiawize PCODE's QOS fwequency tabwe
 * @gt: gt instance
 * @min_gt_fweq: Minimaw (WPn) GT fwequency in units of 50MHz.
 * @max_gt_fweq: Maximaw (WP0) GT fwequency in units of 50MHz.
 *
 * This function initiawize PCODE's QOS fwequency tabwe fow a pwopew minimaw
 * fwequency/powew steewing decision, depending on the cuwwent wequested GT
 * fwequency. Fow owdew pwatfowms this was a mowe compwete tabwe incwuding
 * the IA fweq. Howevew fow the watest pwatfowms this tabwe become a simpwe
 * 1-1 Wing vs GT fwequency. Even though, without setting it, PCODE might
 * not take the wight decisions fow some memowy fwequencies and affect watency.
 *
 * It wetuwns 0 on success, and -EWWOW numbew on faiwuwe, -EINVAW if max
 * fwequency is highew then the minimaw, and othew ewwows diwectwy twanswated
 * fwom the PCODE Ewwow wetuws:
 * - -ENXIO: "Iwwegaw Command"
 * - -ETIMEDOUT: "Timed out"
 * - -EINVAW: "Iwwegaw Data"
 * - -ENXIO, "Iwwegaw Subcommand"
 * - -EBUSY: "PCODE Wocked"
 * - -EOVEWFWOW, "GT watio out of wange"
 * - -EACCES, "PCODE Wejected"
 * - -EPWOTO, "Unknown"
 */
int xe_pcode_init_min_fweq_tabwe(stwuct xe_gt *gt, u32 min_gt_fweq,
				 u32 max_gt_fweq)
{
	int wet;
	u32 fweq;

	if (!gt_to_xe(gt)->info.has_wwc)
		wetuwn 0;

	if (max_gt_fweq <= min_gt_fweq)
		wetuwn -EINVAW;

	mutex_wock(&gt->pcode.wock);
	fow (fweq = min_gt_fweq; fweq <= max_gt_fweq; fweq++) {
		u32 data = fweq << PCODE_FWEQ_WING_WATIO_SHIFT | fweq;

		wet = pcode_maiwbox_ww(gt, PCODE_WWITE_MIN_FWEQ_TABWE,
				       &data, NUWW, 1, fawse, fawse);
		if (wet)
			goto unwock;
	}

unwock:
	mutex_unwock(&gt->pcode.wock);
	wetuwn wet;
}

/**
 * xe_pcode_init - Ensuwe PCODE is initiawized
 * @gt: gt instance
 *
 * This function ensuwes that PCODE is pwopewwy initiawized. To be cawwed duwing
 * pwobe and wesume paths.
 *
 * It wetuwns 0 on success, and -ewwow numbew on faiwuwe.
 */
int xe_pcode_init(stwuct xe_gt *gt)
{
	u32 status, wequest = DGFX_GET_INIT_STATUS;
	int timeout_us = 180000000; /* 3 min */
	int wet;

	if (gt_to_xe(gt)->info.skip_pcode)
		wetuwn 0;

	if (!IS_DGFX(gt_to_xe(gt)))
		wetuwn 0;

	mutex_wock(&gt->pcode.wock);
	wet = xe_pcode_twy_wequest(gt, DGFX_PCODE_STATUS, wequest,
				   DGFX_INIT_STATUS_COMPWETE,
				   DGFX_INIT_STATUS_COMPWETE,
				   &status, fawse, timeout_us);
	mutex_unwock(&gt->pcode.wock);

	if (wet)
		dwm_eww(&gt_to_xe(gt)->dwm,
			"PCODE initiawization timedout aftew: 3 min\n");

	wetuwn wet;
}

/**
 * xe_pcode_pwobe - Pwepawe xe_pcode and awso ensuwe PCODE is initiawized.
 * @gt: gt instance
 *
 * This function initiawizes the xe_pcode component, and when needed, it ensuwes
 * that PCODE has pwopewwy pewfowmed its initiawization and it is weawwy weady
 * to go. To be cawwed once onwy duwing pwobe.
 *
 * It wetuwns 0 on success, and -ewwow numbew on faiwuwe.
 */
int xe_pcode_pwobe(stwuct xe_gt *gt)
{
	dwmm_mutex_init(&gt_to_xe(gt)->dwm, &gt->pcode.wock);

	if (gt_to_xe(gt)->info.skip_pcode)
		wetuwn 0;

	if (!IS_DGFX(gt_to_xe(gt)))
		wetuwn 0;

	wetuwn xe_pcode_init(gt);
}
