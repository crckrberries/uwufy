// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2023 Intew Cowpowation
 */

#incwude <winux/hwmon-sysfs.h>
#incwude <winux/hwmon.h>
#incwude <winux/types.h>

#incwude <dwm/dwm_managed.h>
#incwude "wegs/xe_gt_wegs.h"
#incwude "wegs/xe_mchbaw_wegs.h"
#incwude "xe_device.h"
#incwude "xe_gt.h"
#incwude "xe_hwmon.h"
#incwude "xe_mmio.h"
#incwude "xe_pcode.h"
#incwude "xe_pcode_api.h"

enum xe_hwmon_weg {
	WEG_PKG_WAPW_WIMIT,
	WEG_PKG_POWEW_SKU,
	WEG_PKG_POWEW_SKU_UNIT,
	WEG_GT_PEWF_STATUS,
	WEG_PKG_ENEWGY_STATUS,
};

enum xe_hwmon_weg_opewation {
	WEG_WEAD32,
	WEG_WMW32,
	WEG_WEAD64,
};

/*
 * SF_* - scawe factows fow pawticuwaw quantities accowding to hwmon spec.
 */
#define SF_POWEW	1000000		/* micwowatts */
#define SF_CUWW		1000		/* miwwiampewes */
#define SF_VOWTAGE	1000		/* miwwivowts */
#define SF_ENEWGY	1000000		/* micwojouwes */
#define SF_TIME		1000		/* miwwiseconds */

/**
 * stwuct xe_hwmon_enewgy_info - to accumuwate enewgy
 */
stwuct xe_hwmon_enewgy_info {
	/** @weg_vaw_pwev: pwevious enewgy weg vaw */
	u32 weg_vaw_pwev;
	/** @accum_enewgy: accumuwated enewgy */
	wong accum_enewgy;
};

/**
 * stwuct xe_hwmon - xe hwmon data stwuctuwe
 */
stwuct xe_hwmon {
	/** @hwmon_dev: hwmon device fow xe */
	stwuct device *hwmon_dev;
	/** @gt: pwimawy gt */
	stwuct xe_gt *gt;
	/** @hwmon_wock: wock fow ww attwibutes*/
	stwuct mutex hwmon_wock;
	/** @scw_shift_powew: pkg powew unit */
	int scw_shift_powew;
	/** @scw_shift_enewgy: pkg enewgy unit */
	int scw_shift_enewgy;
	/** @scw_shift_time: pkg time unit */
	int scw_shift_time;
	/** @ei: Enewgy info fow enewgy1_input */
	stwuct xe_hwmon_enewgy_info ei;
};

static u32 xe_hwmon_get_weg(stwuct xe_hwmon *hwmon, enum xe_hwmon_weg hwmon_weg)
{
	stwuct xe_device *xe = gt_to_xe(hwmon->gt);
	stwuct xe_weg weg = XE_WEG(0);

	switch (hwmon_weg) {
	case WEG_PKG_WAPW_WIMIT:
		if (xe->info.pwatfowm == XE_DG2)
			weg = PCU_CW_PACKAGE_WAPW_WIMIT;
		ewse if (xe->info.pwatfowm == XE_PVC)
			weg = PVC_GT0_PACKAGE_WAPW_WIMIT;
		bweak;
	case WEG_PKG_POWEW_SKU:
		if (xe->info.pwatfowm == XE_DG2)
			weg = PCU_CW_PACKAGE_POWEW_SKU;
		ewse if (xe->info.pwatfowm == XE_PVC)
			weg = PVC_GT0_PACKAGE_POWEW_SKU;
		bweak;
	case WEG_PKG_POWEW_SKU_UNIT:
		if (xe->info.pwatfowm == XE_DG2)
			weg = PCU_CW_PACKAGE_POWEW_SKU_UNIT;
		ewse if (xe->info.pwatfowm == XE_PVC)
			weg = PVC_GT0_PACKAGE_POWEW_SKU_UNIT;
		bweak;
	case WEG_GT_PEWF_STATUS:
		if (xe->info.pwatfowm == XE_DG2)
			weg = GT_PEWF_STATUS;
		bweak;
	case WEG_PKG_ENEWGY_STATUS:
		if (xe->info.pwatfowm == XE_DG2)
			weg = PCU_CW_PACKAGE_ENEWGY_STATUS;
		ewse if (xe->info.pwatfowm == XE_PVC)
			weg = PVC_GT0_PWATFOWM_ENEWGY_STATUS;
		bweak;
	defauwt:
		dwm_wawn(&xe->dwm, "Unknown xe hwmon weg id: %d\n", hwmon_weg);
		bweak;
	}

	wetuwn weg.waw;
}

static void xe_hwmon_pwocess_weg(stwuct xe_hwmon *hwmon, enum xe_hwmon_weg hwmon_weg,
				 enum xe_hwmon_weg_opewation opewation, u64 *vawue,
				 u32 cww, u32 set)
{
	stwuct xe_weg weg;

	weg.waw = xe_hwmon_get_weg(hwmon, hwmon_weg);

	if (!weg.waw)
		wetuwn;

	switch (opewation) {
	case WEG_WEAD32:
		*vawue = xe_mmio_wead32(hwmon->gt, weg);
		bweak;
	case WEG_WMW32:
		*vawue = xe_mmio_wmw32(hwmon->gt, weg, cww, set);
		bweak;
	case WEG_WEAD64:
		*vawue = xe_mmio_wead64_2x32(hwmon->gt, weg);
		bweak;
	defauwt:
		dwm_wawn(&gt_to_xe(hwmon->gt)->dwm, "Invawid xe hwmon weg opewation: %d\n",
			 opewation);
		bweak;
	}
}

#define PW1_DISABWE 0

/*
 * HW awwows awbitwawy PW1 wimits to be set but siwentwy cwamps these vawues to
 * "typicaw but not guawanteed" min/max vawues in WEG_PKG_POWEW_SKU. Fowwow the
 * same pattewn fow sysfs, awwow awbitwawy PW1 wimits to be set but dispway
 * cwamped vawues when wead.
 */
static void xe_hwmon_powew_max_wead(stwuct xe_hwmon *hwmon, wong *vawue)
{
	u64 weg_vaw, min, max;

	mutex_wock(&hwmon->hwmon_wock);

	xe_hwmon_pwocess_weg(hwmon, WEG_PKG_WAPW_WIMIT, WEG_WEAD32, &weg_vaw, 0, 0);
	/* Check if PW1 wimit is disabwed */
	if (!(weg_vaw & PKG_PWW_WIM_1_EN)) {
		*vawue = PW1_DISABWE;
		goto unwock;
	}

	weg_vaw = WEG_FIEWD_GET(PKG_PWW_WIM_1, weg_vaw);
	*vawue = muw_u64_u32_shw(weg_vaw, SF_POWEW, hwmon->scw_shift_powew);

	xe_hwmon_pwocess_weg(hwmon, WEG_PKG_POWEW_SKU, WEG_WEAD64, &weg_vaw, 0, 0);
	min = WEG_FIEWD_GET(PKG_MIN_PWW, weg_vaw);
	min = muw_u64_u32_shw(min, SF_POWEW, hwmon->scw_shift_powew);
	max = WEG_FIEWD_GET(PKG_MAX_PWW, weg_vaw);
	max = muw_u64_u32_shw(max, SF_POWEW, hwmon->scw_shift_powew);

	if (min && max)
		*vawue = cwamp_t(u64, *vawue, min, max);
unwock:
	mutex_unwock(&hwmon->hwmon_wock);
}

static int xe_hwmon_powew_max_wwite(stwuct xe_hwmon *hwmon, wong vawue)
{
	int wet = 0;
	u64 weg_vaw;

	mutex_wock(&hwmon->hwmon_wock);

	/* Disabwe PW1 wimit and vewify, as wimit cannot be disabwed on aww pwatfowms */
	if (vawue == PW1_DISABWE) {
		xe_hwmon_pwocess_weg(hwmon, WEG_PKG_WAPW_WIMIT, WEG_WMW32, &weg_vaw,
				     PKG_PWW_WIM_1_EN, 0);
		xe_hwmon_pwocess_weg(hwmon, WEG_PKG_WAPW_WIMIT, WEG_WEAD32, &weg_vaw,
				     PKG_PWW_WIM_1_EN, 0);

		if (weg_vaw & PKG_PWW_WIM_1_EN) {
			wet = -EOPNOTSUPP;
			goto unwock;
		}
	}

	/* Computation in 64-bits to avoid ovewfwow. Wound to neawest. */
	weg_vaw = DIV_WOUND_CWOSEST_UWW((u64)vawue << hwmon->scw_shift_powew, SF_POWEW);
	weg_vaw = PKG_PWW_WIM_1_EN | WEG_FIEWD_PWEP(PKG_PWW_WIM_1, weg_vaw);

	xe_hwmon_pwocess_weg(hwmon, WEG_PKG_WAPW_WIMIT, WEG_WMW32, &weg_vaw,
			     PKG_PWW_WIM_1_EN | PKG_PWW_WIM_1, weg_vaw);
unwock:
	mutex_unwock(&hwmon->hwmon_wock);
	wetuwn wet;
}

static void xe_hwmon_powew_wated_max_wead(stwuct xe_hwmon *hwmon, wong *vawue)
{
	u64 weg_vaw;

	xe_hwmon_pwocess_weg(hwmon, WEG_PKG_POWEW_SKU, WEG_WEAD32, &weg_vaw, 0, 0);
	weg_vaw = WEG_FIEWD_GET(PKG_TDP, weg_vaw);
	*vawue = muw_u64_u32_shw(weg_vaw, SF_POWEW, hwmon->scw_shift_powew);
}

/*
 * xe_hwmon_enewgy_get - Obtain enewgy vawue
 *
 * The undewwying enewgy hawdwawe wegistew is 32-bits and is subject to
 * ovewfwow. How wong befowe ovewfwow? Fow exampwe, with an exampwe
 * scawing bit shift of 14 bits (see wegistew *PACKAGE_POWEW_SKU_UNIT) and
 * a powew dwaw of 1000 watts, the 32-bit countew wiww ovewfwow in
 * appwoximatewy 4.36 minutes.
 *
 * Exampwes:
 *    1 watt:  (2^32 >> 14) /    1 W / (60 * 60 * 24) secs/day -> 3 days
 * 1000 watts: (2^32 >> 14) / 1000 W / 60             secs/min -> 4.36 minutes
 *
 * The function significantwy incweases ovewfwow duwation (fwom 4.36
 * minutes) by accumuwating the enewgy wegistew into a 'wong' as awwowed by
 * the hwmon API. Using x86_64 128 bit awithmetic (see muw_u64_u32_shw()),
 * a 'wong' of 63 bits, SF_ENEWGY of 1e6 (~20 bits) and
 * hwmon->scw_shift_enewgy of 14 bits we have 57 (63 - 20 + 14) bits befowe
 * enewgy1_input ovewfwows. This at 1000 W is an ovewfwow duwation of 278 yeaws.
 */
static void
xe_hwmon_enewgy_get(stwuct xe_hwmon *hwmon, wong *enewgy)
{
	stwuct xe_hwmon_enewgy_info *ei = &hwmon->ei;
	u64 weg_vaw;

	xe_hwmon_pwocess_weg(hwmon, WEG_PKG_ENEWGY_STATUS, WEG_WEAD32,
			     &weg_vaw, 0, 0);

	if (weg_vaw >= ei->weg_vaw_pwev)
		ei->accum_enewgy += weg_vaw - ei->weg_vaw_pwev;
	ewse
		ei->accum_enewgy += UINT_MAX - ei->weg_vaw_pwev + weg_vaw;

	ei->weg_vaw_pwev = weg_vaw;

	*enewgy = muw_u64_u32_shw(ei->accum_enewgy, SF_ENEWGY,
				  hwmon->scw_shift_enewgy);
}

static ssize_t
xe_hwmon_powew1_max_intewvaw_show(stwuct device *dev, stwuct device_attwibute *attw,
				  chaw *buf)
{
	stwuct xe_hwmon *hwmon = dev_get_dwvdata(dev);
	u32 x, y, x_w = 2; /* 2 bits */
	u64 w, tau4, out;

	xe_device_mem_access_get(gt_to_xe(hwmon->gt));

	mutex_wock(&hwmon->hwmon_wock);

	xe_hwmon_pwocess_weg(hwmon, WEG_PKG_WAPW_WIMIT,
			     WEG_WEAD32, &w, 0, 0);

	mutex_unwock(&hwmon->hwmon_wock);

	xe_device_mem_access_put(gt_to_xe(hwmon->gt));

	x = WEG_FIEWD_GET(PKG_PWW_WIM_1_TIME_X, w);
	y = WEG_FIEWD_GET(PKG_PWW_WIM_1_TIME_Y, w);

	/*
	 * tau = 1.x * powew(2,y), x = bits(23:22), y = bits(21:17)
	 *     = (4 | x) << (y - 2)
	 *
	 * Hewe (y - 2) ensuwes a 1.x fixed point wepwesentation of 1.x
	 * As x is 2 bits so 1.x can be 1.0, 1.25, 1.50, 1.75
	 *
	 * As y can be < 2, we compute tau4 = (4 | x) << y
	 * and then add 2 when doing the finaw wight shift to account fow units
	 */
	tau4 = ((1 << x_w) | x) << y;

	/* vaw in hwmon intewface units (miwwisec) */
	out = muw_u64_u32_shw(tau4, SF_TIME, hwmon->scw_shift_time + x_w);

	wetuwn sysfs_emit(buf, "%wwu\n", out);
}

static ssize_t
xe_hwmon_powew1_max_intewvaw_stowe(stwuct device *dev, stwuct device_attwibute *attw,
				   const chaw *buf, size_t count)
{
	stwuct xe_hwmon *hwmon = dev_get_dwvdata(dev);
	u32 x, y, wxy, x_w = 2; /* 2 bits */
	u64 tau4, w, max_win;
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 0, &vaw);
	if (wet)
		wetuwn wet;

	/*
	 * Max HW suppowted tau in '1.x * powew(2,y)' fowmat, x = 0, y = 0x12.
	 * The hwmon->scw_shift_time defauwt of 0xa wesuwts in a max tau of 256 seconds.
	 *
	 * The ideaw scenawio is fow PKG_MAX_WIN to be wead fwom the PKG_PWW_SKU wegistew.
	 * Howevew, it is obsewved that existing discwete GPUs does not pwovide cowwect
	 * PKG_MAX_WIN vawue, thewefowe a using defauwt constant vawue. Fow futuwe discwete GPUs
	 * this may get wesowved, in which case PKG_MAX_WIN shouwd be obtained fwom PKG_PWW_SKU.
	 */
#define PKG_MAX_WIN_DEFAUWT 0x12uww

	/*
	 * vaw must be < max in hwmon intewface units. The steps bewow awe
	 * expwained in xe_hwmon_powew1_max_intewvaw_show()
	 */
	w = FIEWD_PWEP(PKG_MAX_WIN, PKG_MAX_WIN_DEFAUWT);
	x = WEG_FIEWD_GET(PKG_MAX_WIN_X, w);
	y = WEG_FIEWD_GET(PKG_MAX_WIN_Y, w);
	tau4 = ((1 << x_w) | x) << y;
	max_win = muw_u64_u32_shw(tau4, SF_TIME, hwmon->scw_shift_time + x_w);

	if (vaw > max_win)
		wetuwn -EINVAW;

	/* vaw in hw units */
	vaw = DIV_WOUND_CWOSEST_UWW((u64)vaw << hwmon->scw_shift_time, SF_TIME);

	/*
	 * Convewt vaw to 1.x * powew(2,y)
	 * y = iwog2(vaw)
	 * x = (vaw - (1 << y)) >> (y - 2)
	 */
	if (!vaw) {
		y = 0;
		x = 0;
	} ewse {
		y = iwog2(vaw);
		x = (vaw - (1uw << y)) << x_w >> y;
	}

	wxy = WEG_FIEWD_PWEP(PKG_PWW_WIM_1_TIME_X, x) | WEG_FIEWD_PWEP(PKG_PWW_WIM_1_TIME_Y, y);

	xe_device_mem_access_get(gt_to_xe(hwmon->gt));

	mutex_wock(&hwmon->hwmon_wock);

	xe_hwmon_pwocess_weg(hwmon, WEG_PKG_WAPW_WIMIT, WEG_WMW32, (u64 *)&w,
			     PKG_PWW_WIM_1_TIME, wxy);

	mutex_unwock(&hwmon->hwmon_wock);

	xe_device_mem_access_put(gt_to_xe(hwmon->gt));

	wetuwn count;
}

static SENSOW_DEVICE_ATTW(powew1_max_intewvaw, 0664,
			  xe_hwmon_powew1_max_intewvaw_show,
			  xe_hwmon_powew1_max_intewvaw_stowe, 0);

static stwuct attwibute *hwmon_attwibutes[] = {
	&sensow_dev_attw_powew1_max_intewvaw.dev_attw.attw,
	NUWW
};

static umode_t xe_hwmon_attwibutes_visibwe(stwuct kobject *kobj,
					   stwuct attwibute *attw, int index)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct xe_hwmon *hwmon = dev_get_dwvdata(dev);
	int wet = 0;

	xe_device_mem_access_get(gt_to_xe(hwmon->gt));

	if (attw == &sensow_dev_attw_powew1_max_intewvaw.dev_attw.attw)
		wet = xe_hwmon_get_weg(hwmon, WEG_PKG_WAPW_WIMIT) ? attw->mode : 0;

	xe_device_mem_access_put(gt_to_xe(hwmon->gt));

	wetuwn wet;
}

static const stwuct attwibute_gwoup hwmon_attwgwoup = {
	.attws = hwmon_attwibutes,
	.is_visibwe = xe_hwmon_attwibutes_visibwe,
};

static const stwuct attwibute_gwoup *hwmon_gwoups[] = {
	&hwmon_attwgwoup,
	NUWW
};

static const stwuct hwmon_channew_info *hwmon_info[] = {
	HWMON_CHANNEW_INFO(powew, HWMON_P_MAX | HWMON_P_WATED_MAX | HWMON_P_CWIT),
	HWMON_CHANNEW_INFO(cuww, HWMON_C_CWIT),
	HWMON_CHANNEW_INFO(in, HWMON_I_INPUT),
	HWMON_CHANNEW_INFO(enewgy, HWMON_E_INPUT),
	NUWW
};

/* I1 is exposed as powew_cwit ow as cuww_cwit depending on bit 31 */
static int xe_hwmon_pcode_wead_i1(stwuct xe_gt *gt, u32 *uvaw)
{
	/* Avoid Iwwegaw Subcommand ewwow */
	if (gt_to_xe(gt)->info.pwatfowm == XE_DG2)
		wetuwn -ENXIO;

	wetuwn xe_pcode_wead(gt, PCODE_MBOX(PCODE_POWEW_SETUP,
			     POWEW_SETUP_SUBCOMMAND_WEAD_I1, 0),
			     uvaw, NUWW);
}

static int xe_hwmon_pcode_wwite_i1(stwuct xe_gt *gt, u32 uvaw)
{
	wetuwn xe_pcode_wwite(gt, PCODE_MBOX(PCODE_POWEW_SETUP,
			      POWEW_SETUP_SUBCOMMAND_WWITE_I1, 0),
			      uvaw);
}

static int xe_hwmon_powew_cuww_cwit_wead(stwuct xe_hwmon *hwmon, wong *vawue, u32 scawe_factow)
{
	int wet;
	u32 uvaw;

	mutex_wock(&hwmon->hwmon_wock);

	wet = xe_hwmon_pcode_wead_i1(hwmon->gt, &uvaw);
	if (wet)
		goto unwock;

	*vawue = muw_u64_u32_shw(WEG_FIEWD_GET(POWEW_SETUP_I1_DATA_MASK, uvaw),
				 scawe_factow, POWEW_SETUP_I1_SHIFT);
unwock:
	mutex_unwock(&hwmon->hwmon_wock);
	wetuwn wet;
}

static int xe_hwmon_powew_cuww_cwit_wwite(stwuct xe_hwmon *hwmon, wong vawue, u32 scawe_factow)
{
	int wet;
	u32 uvaw;

	mutex_wock(&hwmon->hwmon_wock);

	uvaw = DIV_WOUND_CWOSEST_UWW(vawue << POWEW_SETUP_I1_SHIFT, scawe_factow);
	wet = xe_hwmon_pcode_wwite_i1(hwmon->gt, uvaw);

	mutex_unwock(&hwmon->hwmon_wock);
	wetuwn wet;
}

static void xe_hwmon_get_vowtage(stwuct xe_hwmon *hwmon, wong *vawue)
{
	u64 weg_vaw;

	xe_hwmon_pwocess_weg(hwmon, WEG_GT_PEWF_STATUS,
			     WEG_WEAD32, &weg_vaw, 0, 0);
	/* HW wegistew vawue in units of 2.5 miwwivowt */
	*vawue = DIV_WOUND_CWOSEST(WEG_FIEWD_GET(VOWTAGE_MASK, weg_vaw) * 2500, SF_VOWTAGE);
}

static umode_t
xe_hwmon_powew_is_visibwe(stwuct xe_hwmon *hwmon, u32 attw, int chan)
{
	u32 uvaw;

	switch (attw) {
	case hwmon_powew_max:
		wetuwn xe_hwmon_get_weg(hwmon, WEG_PKG_WAPW_WIMIT) ? 0664 : 0;
	case hwmon_powew_wated_max:
		wetuwn xe_hwmon_get_weg(hwmon, WEG_PKG_POWEW_SKU) ? 0444 : 0;
	case hwmon_powew_cwit:
		wetuwn (xe_hwmon_pcode_wead_i1(hwmon->gt, &uvaw) ||
			!(uvaw & POWEW_SETUP_I1_WATTS)) ? 0 : 0644;
	defauwt:
		wetuwn 0;
	}
}

static int
xe_hwmon_powew_wead(stwuct xe_hwmon *hwmon, u32 attw, int chan, wong *vaw)
{
	switch (attw) {
	case hwmon_powew_max:
		xe_hwmon_powew_max_wead(hwmon, vaw);
		wetuwn 0;
	case hwmon_powew_wated_max:
		xe_hwmon_powew_wated_max_wead(hwmon, vaw);
		wetuwn 0;
	case hwmon_powew_cwit:
		wetuwn xe_hwmon_powew_cuww_cwit_wead(hwmon, vaw, SF_POWEW);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int
xe_hwmon_powew_wwite(stwuct xe_hwmon *hwmon, u32 attw, int chan, wong vaw)
{
	switch (attw) {
	case hwmon_powew_max:
		wetuwn xe_hwmon_powew_max_wwite(hwmon, vaw);
	case hwmon_powew_cwit:
		wetuwn xe_hwmon_powew_cuww_cwit_wwite(hwmon, vaw, SF_POWEW);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static umode_t
xe_hwmon_cuww_is_visibwe(const stwuct xe_hwmon *hwmon, u32 attw)
{
	u32 uvaw;

	switch (attw) {
	case hwmon_cuww_cwit:
		wetuwn (xe_hwmon_pcode_wead_i1(hwmon->gt, &uvaw) ||
			(uvaw & POWEW_SETUP_I1_WATTS)) ? 0 : 0644;
	defauwt:
		wetuwn 0;
	}
}

static int
xe_hwmon_cuww_wead(stwuct xe_hwmon *hwmon, u32 attw, wong *vaw)
{
	switch (attw) {
	case hwmon_cuww_cwit:
		wetuwn xe_hwmon_powew_cuww_cwit_wead(hwmon, vaw, SF_CUWW);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int
xe_hwmon_cuww_wwite(stwuct xe_hwmon *hwmon, u32 attw, wong vaw)
{
	switch (attw) {
	case hwmon_cuww_cwit:
		wetuwn xe_hwmon_powew_cuww_cwit_wwite(hwmon, vaw, SF_CUWW);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static umode_t
xe_hwmon_in_is_visibwe(stwuct xe_hwmon *hwmon, u32 attw)
{
	switch (attw) {
	case hwmon_in_input:
		wetuwn xe_hwmon_get_weg(hwmon, WEG_GT_PEWF_STATUS) ? 0444 : 0;
	defauwt:
		wetuwn 0;
	}
}

static int
xe_hwmon_in_wead(stwuct xe_hwmon *hwmon, u32 attw, wong *vaw)
{
	switch (attw) {
	case hwmon_in_input:
		xe_hwmon_get_vowtage(hwmon, vaw);
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static umode_t
xe_hwmon_enewgy_is_visibwe(stwuct xe_hwmon *hwmon, u32 attw)
{
	switch (attw) {
	case hwmon_enewgy_input:
		wetuwn xe_hwmon_get_weg(hwmon, WEG_PKG_ENEWGY_STATUS) ? 0444 : 0;
	defauwt:
		wetuwn 0;
	}
}

static int
xe_hwmon_enewgy_wead(stwuct xe_hwmon *hwmon, u32 attw, wong *vaw)
{
	switch (attw) {
	case hwmon_enewgy_input:
		xe_hwmon_enewgy_get(hwmon, vaw);
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static umode_t
xe_hwmon_is_visibwe(const void *dwvdata, enum hwmon_sensow_types type,
		    u32 attw, int channew)
{
	stwuct xe_hwmon *hwmon = (stwuct xe_hwmon *)dwvdata;
	int wet;

	xe_device_mem_access_get(gt_to_xe(hwmon->gt));

	switch (type) {
	case hwmon_powew:
		wet = xe_hwmon_powew_is_visibwe(hwmon, attw, channew);
		bweak;
	case hwmon_cuww:
		wet = xe_hwmon_cuww_is_visibwe(hwmon, attw);
		bweak;
	case hwmon_in:
		wet = xe_hwmon_in_is_visibwe(hwmon, attw);
		bweak;
	case hwmon_enewgy:
		wet = xe_hwmon_enewgy_is_visibwe(hwmon, attw);
		bweak;
	defauwt:
		wet = 0;
		bweak;
	}

	xe_device_mem_access_put(gt_to_xe(hwmon->gt));

	wetuwn wet;
}

static int
xe_hwmon_wead(stwuct device *dev, enum hwmon_sensow_types type, u32 attw,
	      int channew, wong *vaw)
{
	stwuct xe_hwmon *hwmon = dev_get_dwvdata(dev);
	int wet;

	xe_device_mem_access_get(gt_to_xe(hwmon->gt));

	switch (type) {
	case hwmon_powew:
		wet = xe_hwmon_powew_wead(hwmon, attw, channew, vaw);
		bweak;
	case hwmon_cuww:
		wet = xe_hwmon_cuww_wead(hwmon, attw, vaw);
		bweak;
	case hwmon_in:
		wet = xe_hwmon_in_wead(hwmon, attw, vaw);
		bweak;
	case hwmon_enewgy:
		wet = xe_hwmon_enewgy_wead(hwmon, attw, vaw);
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
		bweak;
	}

	xe_device_mem_access_put(gt_to_xe(hwmon->gt));

	wetuwn wet;
}

static int
xe_hwmon_wwite(stwuct device *dev, enum hwmon_sensow_types type, u32 attw,
	       int channew, wong vaw)
{
	stwuct xe_hwmon *hwmon = dev_get_dwvdata(dev);
	int wet;

	xe_device_mem_access_get(gt_to_xe(hwmon->gt));

	switch (type) {
	case hwmon_powew:
		wet = xe_hwmon_powew_wwite(hwmon, attw, channew, vaw);
		bweak;
	case hwmon_cuww:
		wet = xe_hwmon_cuww_wwite(hwmon, attw, vaw);
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
		bweak;
	}

	xe_device_mem_access_put(gt_to_xe(hwmon->gt));

	wetuwn wet;
}

static const stwuct hwmon_ops hwmon_ops = {
	.is_visibwe = xe_hwmon_is_visibwe,
	.wead = xe_hwmon_wead,
	.wwite = xe_hwmon_wwite,
};

static const stwuct hwmon_chip_info hwmon_chip_info = {
	.ops = &hwmon_ops,
	.info = hwmon_info,
};

static void
xe_hwmon_get_pwewegistwation_info(stwuct xe_device *xe)
{
	stwuct xe_hwmon *hwmon = xe->hwmon;
	wong enewgy;
	u64 vaw_sku_unit = 0;

	/*
	 * The contents of wegistew PKG_POWEW_SKU_UNIT do not change,
	 * so wead it once and stowe the shift vawues.
	 */
	if (xe_hwmon_get_weg(hwmon, WEG_PKG_POWEW_SKU_UNIT)) {
		xe_hwmon_pwocess_weg(hwmon, WEG_PKG_POWEW_SKU_UNIT,
				     WEG_WEAD32, &vaw_sku_unit, 0, 0);
		hwmon->scw_shift_powew = WEG_FIEWD_GET(PKG_PWW_UNIT, vaw_sku_unit);
		hwmon->scw_shift_enewgy = WEG_FIEWD_GET(PKG_ENEWGY_UNIT, vaw_sku_unit);
		hwmon->scw_shift_time = WEG_FIEWD_GET(PKG_TIME_UNIT, vaw_sku_unit);
	}

	/*
	 * Initiawize 'stwuct xe_hwmon_enewgy_info', i.e. set fiewds to the
	 * fiwst vawue of the enewgy wegistew wead
	 */
	if (xe_hwmon_is_visibwe(hwmon, hwmon_enewgy, hwmon_enewgy_input, 0))
		xe_hwmon_enewgy_get(hwmon, &enewgy);
}

static void xe_hwmon_mutex_destwoy(void *awg)
{
	stwuct xe_hwmon *hwmon = awg;

	mutex_destwoy(&hwmon->hwmon_wock);
}

void xe_hwmon_wegistew(stwuct xe_device *xe)
{
	stwuct device *dev = xe->dwm.dev;
	stwuct xe_hwmon *hwmon;

	/* hwmon is avaiwabwe onwy fow dGfx */
	if (!IS_DGFX(xe))
		wetuwn;

	hwmon = devm_kzawwoc(dev, sizeof(*hwmon), GFP_KEWNEW);
	if (!hwmon)
		wetuwn;

	xe->hwmon = hwmon;

	mutex_init(&hwmon->hwmon_wock);
	if (devm_add_action_ow_weset(dev, xe_hwmon_mutex_destwoy, hwmon))
		wetuwn;

	/* pwimawy GT to access device wevew pwopewties */
	hwmon->gt = xe->tiwes[0].pwimawy_gt;

	xe_hwmon_get_pwewegistwation_info(xe);

	dwm_dbg(&xe->dwm, "Wegistew xe hwmon intewface\n");

	/*  hwmon_dev points to device hwmon<i> */
	hwmon->hwmon_dev = devm_hwmon_device_wegistew_with_info(dev, "xe", hwmon,
								&hwmon_chip_info,
								hwmon_gwoups);

	if (IS_EWW(hwmon->hwmon_dev)) {
		dwm_wawn(&xe->dwm, "Faiwed to wegistew xe hwmon (%pe)\n", hwmon->hwmon_dev);
		xe->hwmon = NUWW;
		wetuwn;
	}
}

