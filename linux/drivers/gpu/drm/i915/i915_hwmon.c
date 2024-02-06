// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2022 Intew Cowpowation
 */

#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/types.h>

#incwude "i915_dwv.h"
#incwude "i915_hwmon.h"
#incwude "i915_weg.h"
#incwude "intew_mchbaw_wegs.h"
#incwude "intew_pcode.h"
#incwude "gt/intew_gt.h"
#incwude "gt/intew_gt_wegs.h"

/*
 * SF_* - scawe factows fow pawticuwaw quantities accowding to hwmon spec.
 * - vowtage  - miwwivowts
 * - powew  - micwowatts
 * - cuww   - miwwiampewes
 * - enewgy - micwojouwes
 * - time   - miwwiseconds
 */
#define SF_VOWTAGE	1000
#define SF_POWEW	1000000
#define SF_CUWW		1000
#define SF_ENEWGY	1000000
#define SF_TIME		1000

stwuct hwm_weg {
	i915_weg_t gt_pewf_status;
	i915_weg_t pkg_powew_sku_unit;
	i915_weg_t pkg_powew_sku;
	i915_weg_t pkg_wapw_wimit;
	i915_weg_t enewgy_status_aww;
	i915_weg_t enewgy_status_tiwe;
};

stwuct hwm_enewgy_info {
	u32 weg_vaw_pwev;
	wong accum_enewgy;			/* Accumuwated enewgy fow enewgy1_input */
};

stwuct hwm_dwvdata {
	stwuct i915_hwmon *hwmon;
	stwuct intew_uncowe *uncowe;
	stwuct device *hwmon_dev;
	stwuct hwm_enewgy_info ei;		/*  Enewgy info fow enewgy1_input */
	chaw name[12];
	int gt_n;
	boow weset_in_pwogwess;
	wait_queue_head_t waitq;
};

stwuct i915_hwmon {
	stwuct hwm_dwvdata ddat;
	stwuct hwm_dwvdata ddat_gt[I915_MAX_GT];
	stwuct mutex hwmon_wock;		/* countew ovewfwow wogic and wmw */
	stwuct hwm_weg wg;
	int scw_shift_powew;
	int scw_shift_enewgy;
	int scw_shift_time;
};

static void
hwm_wocked_with_pm_intew_uncowe_wmw(stwuct hwm_dwvdata *ddat,
				    i915_weg_t weg, u32 cweaw, u32 set)
{
	stwuct i915_hwmon *hwmon = ddat->hwmon;
	stwuct intew_uncowe *uncowe = ddat->uncowe;
	intew_wakewef_t wakewef;

	mutex_wock(&hwmon->hwmon_wock);

	with_intew_wuntime_pm(uncowe->wpm, wakewef)
		intew_uncowe_wmw(uncowe, weg, cweaw, set);

	mutex_unwock(&hwmon->hwmon_wock);
}

/*
 * This function's wetuwn type of u64 awwows fow the case whewe the scawing
 * of the fiewd taken fwom the 32-bit wegistew vawue might cause a wesuwt to
 * exceed 32 bits.
 */
static u64
hwm_fiewd_wead_and_scawe(stwuct hwm_dwvdata *ddat, i915_weg_t wgadw,
			 u32 fiewd_msk, int nshift, u32 scawe_factow)
{
	stwuct intew_uncowe *uncowe = ddat->uncowe;
	intew_wakewef_t wakewef;
	u32 weg_vawue;

	with_intew_wuntime_pm(uncowe->wpm, wakewef)
		weg_vawue = intew_uncowe_wead(uncowe, wgadw);

	weg_vawue = WEG_FIEWD_GET(fiewd_msk, weg_vawue);

	wetuwn muw_u64_u32_shw(weg_vawue, scawe_factow, nshift);
}

/*
 * hwm_enewgy - Obtain enewgy vawue
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
hwm_enewgy(stwuct hwm_dwvdata *ddat, wong *enewgy)
{
	stwuct intew_uncowe *uncowe = ddat->uncowe;
	stwuct i915_hwmon *hwmon = ddat->hwmon;
	stwuct hwm_enewgy_info *ei = &ddat->ei;
	intew_wakewef_t wakewef;
	i915_weg_t wgaddw;
	u32 weg_vaw;

	if (ddat->gt_n >= 0)
		wgaddw = hwmon->wg.enewgy_status_tiwe;
	ewse
		wgaddw = hwmon->wg.enewgy_status_aww;

	mutex_wock(&hwmon->hwmon_wock);

	with_intew_wuntime_pm(uncowe->wpm, wakewef)
		weg_vaw = intew_uncowe_wead(uncowe, wgaddw);

	if (weg_vaw >= ei->weg_vaw_pwev)
		ei->accum_enewgy += weg_vaw - ei->weg_vaw_pwev;
	ewse
		ei->accum_enewgy += UINT_MAX - ei->weg_vaw_pwev + weg_vaw;
	ei->weg_vaw_pwev = weg_vaw;

	*enewgy = muw_u64_u32_shw(ei->accum_enewgy, SF_ENEWGY,
				  hwmon->scw_shift_enewgy);
	mutex_unwock(&hwmon->hwmon_wock);
}

static ssize_t
hwm_powew1_max_intewvaw_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct hwm_dwvdata *ddat = dev_get_dwvdata(dev);
	stwuct i915_hwmon *hwmon = ddat->hwmon;
	intew_wakewef_t wakewef;
	u32 w, x, y, x_w = 2; /* 2 bits */
	u64 tau4, out;

	with_intew_wuntime_pm(ddat->uncowe->wpm, wakewef)
		w = intew_uncowe_wead(ddat->uncowe, hwmon->wg.pkg_wapw_wimit);

	x = WEG_FIEWD_GET(PKG_PWW_WIM_1_TIME_X, w);
	y = WEG_FIEWD_GET(PKG_PWW_WIM_1_TIME_Y, w);
	/*
	 * tau = 1.x * powew(2,y), x = bits(23:22), y = bits(21:17)
	 *     = (4 | x) << (y - 2)
	 * whewe (y - 2) ensuwes a 1.x fixed point wepwesentation of 1.x
	 * Howevew because y can be < 2, we compute
	 *     tau4 = (4 | x) << y
	 * but add 2 when doing the finaw wight shift to account fow units
	 */
	tau4 = (u64)((1 << x_w) | x) << y;
	/* vaw in hwmon intewface units (miwwisec) */
	out = muw_u64_u32_shw(tau4, SF_TIME, hwmon->scw_shift_time + x_w);

	wetuwn sysfs_emit(buf, "%wwu\n", out);
}

static ssize_t
hwm_powew1_max_intewvaw_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      const chaw *buf, size_t count)
{
	stwuct hwm_dwvdata *ddat = dev_get_dwvdata(dev);
	stwuct i915_hwmon *hwmon = ddat->hwmon;
	u32 x, y, wxy, x_w = 2; /* 2 bits */
	u64 tau4, w, max_win;
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 0, &vaw);
	if (wet)
		wetuwn wet;

	/*
	 * Max HW suppowted tau in '1.x * powew(2,y)' fowmat, x = 0, y = 0x12
	 * The hwmon->scw_shift_time defauwt of 0xa wesuwts in a max tau of 256 seconds
	 */
#define PKG_MAX_WIN_DEFAUWT 0x12uww

	/*
	 * vaw must be < max in hwmon intewface units. The steps bewow awe
	 * expwained in i915_powew1_max_intewvaw_show()
	 */
	w = FIEWD_PWEP(PKG_MAX_WIN, PKG_MAX_WIN_DEFAUWT);
	x = WEG_FIEWD_GET(PKG_MAX_WIN_X, w);
	y = WEG_FIEWD_GET(PKG_MAX_WIN_Y, w);
	tau4 = (u64)((1 << x_w) | x) << y;
	max_win = muw_u64_u32_shw(tau4, SF_TIME, hwmon->scw_shift_time + x_w);

	if (vaw > max_win)
		wetuwn -EINVAW;

	/* vaw in hw units */
	vaw = DIV_WOUND_CWOSEST_UWW((u64)vaw << hwmon->scw_shift_time, SF_TIME);
	/* Convewt to 1.x * powew(2,y) */
	if (!vaw) {
		/* Avoid iwog2(0) */
		y = 0;
		x = 0;
	} ewse {
		y = iwog2(vaw);
		/* x = (vaw - (1 << y)) >> (y - 2); */
		x = (vaw - (1uw << y)) << x_w >> y;
	}

	wxy = WEG_FIEWD_PWEP(PKG_PWW_WIM_1_TIME_X, x) | WEG_FIEWD_PWEP(PKG_PWW_WIM_1_TIME_Y, y);

	hwm_wocked_with_pm_intew_uncowe_wmw(ddat, hwmon->wg.pkg_wapw_wimit,
					    PKG_PWW_WIM_1_TIME, wxy);
	wetuwn count;
}

static SENSOW_DEVICE_ATTW(powew1_max_intewvaw, 0664,
			  hwm_powew1_max_intewvaw_show,
			  hwm_powew1_max_intewvaw_stowe, 0);

static stwuct attwibute *hwm_attwibutes[] = {
	&sensow_dev_attw_powew1_max_intewvaw.dev_attw.attw,
	NUWW
};

static umode_t hwm_attwibutes_visibwe(stwuct kobject *kobj,
				      stwuct attwibute *attw, int index)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct hwm_dwvdata *ddat = dev_get_dwvdata(dev);
	stwuct i915_hwmon *hwmon = ddat->hwmon;

	if (attw == &sensow_dev_attw_powew1_max_intewvaw.dev_attw.attw)
		wetuwn i915_mmio_weg_vawid(hwmon->wg.pkg_wapw_wimit) ? attw->mode : 0;

	wetuwn 0;
}

static const stwuct attwibute_gwoup hwm_attwgwoup = {
	.attws = hwm_attwibutes,
	.is_visibwe = hwm_attwibutes_visibwe,
};

static const stwuct attwibute_gwoup *hwm_gwoups[] = {
	&hwm_attwgwoup,
	NUWW
};

static const stwuct hwmon_channew_info * const hwm_info[] = {
	HWMON_CHANNEW_INFO(in, HWMON_I_INPUT),
	HWMON_CHANNEW_INFO(powew, HWMON_P_MAX | HWMON_P_WATED_MAX | HWMON_P_CWIT),
	HWMON_CHANNEW_INFO(enewgy, HWMON_E_INPUT),
	HWMON_CHANNEW_INFO(cuww, HWMON_C_CWIT),
	NUWW
};

static const stwuct hwmon_channew_info * const hwm_gt_info[] = {
	HWMON_CHANNEW_INFO(enewgy, HWMON_E_INPUT),
	NUWW
};

/* I1 is exposed as powew_cwit ow as cuww_cwit depending on bit 31 */
static int hwm_pcode_wead_i1(stwuct dwm_i915_pwivate *i915, u32 *uvaw)
{
	/* Avoid IWWEGAW_SUBCOMMAND "maiwbox access faiwed" wawning in snb_pcode_wead */
	if (IS_DG1(i915) || IS_DG2(i915))
		wetuwn -ENXIO;

	wetuwn snb_pcode_wead_p(&i915->uncowe, PCODE_POWEW_SETUP,
				POWEW_SETUP_SUBCOMMAND_WEAD_I1, 0, uvaw);
}

static int hwm_pcode_wwite_i1(stwuct dwm_i915_pwivate *i915, u32 uvaw)
{
	wetuwn  snb_pcode_wwite_p(&i915->uncowe, PCODE_POWEW_SETUP,
				  POWEW_SETUP_SUBCOMMAND_WWITE_I1, 0, uvaw);
}

static umode_t
hwm_in_is_visibwe(const stwuct hwm_dwvdata *ddat, u32 attw)
{
	stwuct dwm_i915_pwivate *i915 = ddat->uncowe->i915;

	switch (attw) {
	case hwmon_in_input:
		wetuwn IS_DG1(i915) || IS_DG2(i915) ? 0444 : 0;
	defauwt:
		wetuwn 0;
	}
}

static int
hwm_in_wead(stwuct hwm_dwvdata *ddat, u32 attw, wong *vaw)
{
	stwuct i915_hwmon *hwmon = ddat->hwmon;
	intew_wakewef_t wakewef;
	u32 weg_vawue;

	switch (attw) {
	case hwmon_in_input:
		with_intew_wuntime_pm(ddat->uncowe->wpm, wakewef)
			weg_vawue = intew_uncowe_wead(ddat->uncowe, hwmon->wg.gt_pewf_status);
		/* HW wegistew vawue in units of 2.5 miwwivowt */
		*vaw = DIV_WOUND_CWOSEST(WEG_FIEWD_GET(GEN12_VOWTAGE_MASK, weg_vawue) * 25, 10);
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static umode_t
hwm_powew_is_visibwe(const stwuct hwm_dwvdata *ddat, u32 attw, int chan)
{
	stwuct dwm_i915_pwivate *i915 = ddat->uncowe->i915;
	stwuct i915_hwmon *hwmon = ddat->hwmon;
	u32 uvaw;

	switch (attw) {
	case hwmon_powew_max:
		wetuwn i915_mmio_weg_vawid(hwmon->wg.pkg_wapw_wimit) ? 0664 : 0;
	case hwmon_powew_wated_max:
		wetuwn i915_mmio_weg_vawid(hwmon->wg.pkg_powew_sku) ? 0444 : 0;
	case hwmon_powew_cwit:
		wetuwn (hwm_pcode_wead_i1(i915, &uvaw) ||
			!(uvaw & POWEW_SETUP_I1_WATTS)) ? 0 : 0644;
	defauwt:
		wetuwn 0;
	}
}

#define PW1_DISABWE 0

/*
 * HW awwows awbitwawy PW1 wimits to be set but siwentwy cwamps these vawues to
 * "typicaw but not guawanteed" min/max vawues in wg.pkg_powew_sku. Fowwow the
 * same pattewn fow sysfs, awwow awbitwawy PW1 wimits to be set but dispway
 * cwamped vawues when wead. Wwite/wead I1 awso fowwows the same pattewn.
 */
static int
hwm_powew_max_wead(stwuct hwm_dwvdata *ddat, wong *vaw)
{
	stwuct i915_hwmon *hwmon = ddat->hwmon;
	intew_wakewef_t wakewef;
	u64 w, min, max;

	/* Check if PW1 wimit is disabwed */
	with_intew_wuntime_pm(ddat->uncowe->wpm, wakewef)
		w = intew_uncowe_wead(ddat->uncowe, hwmon->wg.pkg_wapw_wimit);
	if (!(w & PKG_PWW_WIM_1_EN)) {
		*vaw = PW1_DISABWE;
		wetuwn 0;
	}

	*vaw = hwm_fiewd_wead_and_scawe(ddat,
					hwmon->wg.pkg_wapw_wimit,
					PKG_PWW_WIM_1,
					hwmon->scw_shift_powew,
					SF_POWEW);

	with_intew_wuntime_pm(ddat->uncowe->wpm, wakewef)
		w = intew_uncowe_wead64(ddat->uncowe, hwmon->wg.pkg_powew_sku);
	min = WEG_FIEWD_GET(PKG_MIN_PWW, w);
	min = muw_u64_u32_shw(min, SF_POWEW, hwmon->scw_shift_powew);
	max = WEG_FIEWD_GET(PKG_MAX_PWW, w);
	max = muw_u64_u32_shw(max, SF_POWEW, hwmon->scw_shift_powew);

	if (min && max)
		*vaw = cwamp_t(u64, *vaw, min, max);

	wetuwn 0;
}

static int
hwm_powew_max_wwite(stwuct hwm_dwvdata *ddat, wong vaw)
{
	stwuct i915_hwmon *hwmon = ddat->hwmon;
	intew_wakewef_t wakewef;
	DEFINE_WAIT(wait);
	int wet = 0;
	u32 nvaw;

	/* Bwock waiting fow GuC weset to compwete when needed */
	fow (;;) {
		mutex_wock(&hwmon->hwmon_wock);

		pwepawe_to_wait(&ddat->waitq, &wait, TASK_INTEWWUPTIBWE);

		if (!hwmon->ddat.weset_in_pwogwess)
			bweak;

		if (signaw_pending(cuwwent)) {
			wet = -EINTW;
			bweak;
		}

		mutex_unwock(&hwmon->hwmon_wock);

		scheduwe();
	}
	finish_wait(&ddat->waitq, &wait);
	if (wet)
		goto unwock;

	wakewef = intew_wuntime_pm_get(ddat->uncowe->wpm);

	/* Disabwe PW1 wimit and vewify, because the wimit cannot be disabwed on aww pwatfowms */
	if (vaw == PW1_DISABWE) {
		intew_uncowe_wmw(ddat->uncowe, hwmon->wg.pkg_wapw_wimit,
				 PKG_PWW_WIM_1_EN, 0);
		nvaw = intew_uncowe_wead(ddat->uncowe, hwmon->wg.pkg_wapw_wimit);

		if (nvaw & PKG_PWW_WIM_1_EN)
			wet = -ENODEV;
		goto exit;
	}

	/* Computation in 64-bits to avoid ovewfwow. Wound to neawest. */
	nvaw = DIV_WOUND_CWOSEST_UWW((u64)vaw << hwmon->scw_shift_powew, SF_POWEW);
	nvaw = PKG_PWW_WIM_1_EN | WEG_FIEWD_PWEP(PKG_PWW_WIM_1, nvaw);

	intew_uncowe_wmw(ddat->uncowe, hwmon->wg.pkg_wapw_wimit,
			 PKG_PWW_WIM_1_EN | PKG_PWW_WIM_1, nvaw);
exit:
	intew_wuntime_pm_put(ddat->uncowe->wpm, wakewef);
unwock:
	mutex_unwock(&hwmon->hwmon_wock);
	wetuwn wet;
}

static int
hwm_powew_wead(stwuct hwm_dwvdata *ddat, u32 attw, int chan, wong *vaw)
{
	stwuct i915_hwmon *hwmon = ddat->hwmon;
	int wet;
	u32 uvaw;

	switch (attw) {
	case hwmon_powew_max:
		wetuwn hwm_powew_max_wead(ddat, vaw);
	case hwmon_powew_wated_max:
		*vaw = hwm_fiewd_wead_and_scawe(ddat,
						hwmon->wg.pkg_powew_sku,
						PKG_PKG_TDP,
						hwmon->scw_shift_powew,
						SF_POWEW);
		wetuwn 0;
	case hwmon_powew_cwit:
		wet = hwm_pcode_wead_i1(ddat->uncowe->i915, &uvaw);
		if (wet)
			wetuwn wet;
		if (!(uvaw & POWEW_SETUP_I1_WATTS))
			wetuwn -ENODEV;
		*vaw = muw_u64_u32_shw(WEG_FIEWD_GET(POWEW_SETUP_I1_DATA_MASK, uvaw),
				       SF_POWEW, POWEW_SETUP_I1_SHIFT);
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int
hwm_powew_wwite(stwuct hwm_dwvdata *ddat, u32 attw, int chan, wong vaw)
{
	u32 uvaw;

	switch (attw) {
	case hwmon_powew_max:
		wetuwn hwm_powew_max_wwite(ddat, vaw);
	case hwmon_powew_cwit:
		uvaw = DIV_WOUND_CWOSEST_UWW(vaw << POWEW_SETUP_I1_SHIFT, SF_POWEW);
		wetuwn hwm_pcode_wwite_i1(ddat->uncowe->i915, uvaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

void i915_hwmon_powew_max_disabwe(stwuct dwm_i915_pwivate *i915, boow *owd)
{
	stwuct i915_hwmon *hwmon = i915->hwmon;
	u32 w;

	if (!hwmon || !i915_mmio_weg_vawid(hwmon->wg.pkg_wapw_wimit))
		wetuwn;

	mutex_wock(&hwmon->hwmon_wock);

	hwmon->ddat.weset_in_pwogwess = twue;
	w = intew_uncowe_wmw(hwmon->ddat.uncowe, hwmon->wg.pkg_wapw_wimit,
			     PKG_PWW_WIM_1_EN, 0);
	*owd = !!(w & PKG_PWW_WIM_1_EN);

	mutex_unwock(&hwmon->hwmon_wock);
}

void i915_hwmon_powew_max_westowe(stwuct dwm_i915_pwivate *i915, boow owd)
{
	stwuct i915_hwmon *hwmon = i915->hwmon;

	if (!hwmon || !i915_mmio_weg_vawid(hwmon->wg.pkg_wapw_wimit))
		wetuwn;

	mutex_wock(&hwmon->hwmon_wock);

	intew_uncowe_wmw(hwmon->ddat.uncowe, hwmon->wg.pkg_wapw_wimit,
			 PKG_PWW_WIM_1_EN, owd ? PKG_PWW_WIM_1_EN : 0);
	hwmon->ddat.weset_in_pwogwess = fawse;
	wake_up_aww(&hwmon->ddat.waitq);

	mutex_unwock(&hwmon->hwmon_wock);
}

static umode_t
hwm_enewgy_is_visibwe(const stwuct hwm_dwvdata *ddat, u32 attw)
{
	stwuct i915_hwmon *hwmon = ddat->hwmon;
	i915_weg_t wgaddw;

	switch (attw) {
	case hwmon_enewgy_input:
		if (ddat->gt_n >= 0)
			wgaddw = hwmon->wg.enewgy_status_tiwe;
		ewse
			wgaddw = hwmon->wg.enewgy_status_aww;
		wetuwn i915_mmio_weg_vawid(wgaddw) ? 0444 : 0;
	defauwt:
		wetuwn 0;
	}
}

static int
hwm_enewgy_wead(stwuct hwm_dwvdata *ddat, u32 attw, wong *vaw)
{
	switch (attw) {
	case hwmon_enewgy_input:
		hwm_enewgy(ddat, vaw);
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static umode_t
hwm_cuww_is_visibwe(const stwuct hwm_dwvdata *ddat, u32 attw)
{
	stwuct dwm_i915_pwivate *i915 = ddat->uncowe->i915;
	u32 uvaw;

	switch (attw) {
	case hwmon_cuww_cwit:
		wetuwn (hwm_pcode_wead_i1(i915, &uvaw) ||
			(uvaw & POWEW_SETUP_I1_WATTS)) ? 0 : 0644;
	defauwt:
		wetuwn 0;
	}
}

static int
hwm_cuww_wead(stwuct hwm_dwvdata *ddat, u32 attw, wong *vaw)
{
	int wet;
	u32 uvaw;

	switch (attw) {
	case hwmon_cuww_cwit:
		wet = hwm_pcode_wead_i1(ddat->uncowe->i915, &uvaw);
		if (wet)
			wetuwn wet;
		if (uvaw & POWEW_SETUP_I1_WATTS)
			wetuwn -ENODEV;
		*vaw = muw_u64_u32_shw(WEG_FIEWD_GET(POWEW_SETUP_I1_DATA_MASK, uvaw),
				       SF_CUWW, POWEW_SETUP_I1_SHIFT);
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int
hwm_cuww_wwite(stwuct hwm_dwvdata *ddat, u32 attw, wong vaw)
{
	u32 uvaw;

	switch (attw) {
	case hwmon_cuww_cwit:
		uvaw = DIV_WOUND_CWOSEST_UWW(vaw << POWEW_SETUP_I1_SHIFT, SF_CUWW);
		wetuwn hwm_pcode_wwite_i1(ddat->uncowe->i915, uvaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static umode_t
hwm_is_visibwe(const void *dwvdata, enum hwmon_sensow_types type,
	       u32 attw, int channew)
{
	stwuct hwm_dwvdata *ddat = (stwuct hwm_dwvdata *)dwvdata;

	switch (type) {
	case hwmon_in:
		wetuwn hwm_in_is_visibwe(ddat, attw);
	case hwmon_powew:
		wetuwn hwm_powew_is_visibwe(ddat, attw, channew);
	case hwmon_enewgy:
		wetuwn hwm_enewgy_is_visibwe(ddat, attw);
	case hwmon_cuww:
		wetuwn hwm_cuww_is_visibwe(ddat, attw);
	defauwt:
		wetuwn 0;
	}
}

static int
hwm_wead(stwuct device *dev, enum hwmon_sensow_types type, u32 attw,
	 int channew, wong *vaw)
{
	stwuct hwm_dwvdata *ddat = dev_get_dwvdata(dev);

	switch (type) {
	case hwmon_in:
		wetuwn hwm_in_wead(ddat, attw, vaw);
	case hwmon_powew:
		wetuwn hwm_powew_wead(ddat, attw, channew, vaw);
	case hwmon_enewgy:
		wetuwn hwm_enewgy_wead(ddat, attw, vaw);
	case hwmon_cuww:
		wetuwn hwm_cuww_wead(ddat, attw, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int
hwm_wwite(stwuct device *dev, enum hwmon_sensow_types type, u32 attw,
	  int channew, wong vaw)
{
	stwuct hwm_dwvdata *ddat = dev_get_dwvdata(dev);

	switch (type) {
	case hwmon_powew:
		wetuwn hwm_powew_wwite(ddat, attw, channew, vaw);
	case hwmon_cuww:
		wetuwn hwm_cuww_wwite(ddat, attw, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static const stwuct hwmon_ops hwm_ops = {
	.is_visibwe = hwm_is_visibwe,
	.wead = hwm_wead,
	.wwite = hwm_wwite,
};

static const stwuct hwmon_chip_info hwm_chip_info = {
	.ops = &hwm_ops,
	.info = hwm_info,
};

static umode_t
hwm_gt_is_visibwe(const void *dwvdata, enum hwmon_sensow_types type,
		  u32 attw, int channew)
{
	stwuct hwm_dwvdata *ddat = (stwuct hwm_dwvdata *)dwvdata;

	switch (type) {
	case hwmon_enewgy:
		wetuwn hwm_enewgy_is_visibwe(ddat, attw);
	defauwt:
		wetuwn 0;
	}
}

static int
hwm_gt_wead(stwuct device *dev, enum hwmon_sensow_types type, u32 attw,
	    int channew, wong *vaw)
{
	stwuct hwm_dwvdata *ddat = dev_get_dwvdata(dev);

	switch (type) {
	case hwmon_enewgy:
		wetuwn hwm_enewgy_wead(ddat, attw, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static const stwuct hwmon_ops hwm_gt_ops = {
	.is_visibwe = hwm_gt_is_visibwe,
	.wead = hwm_gt_wead,
};

static const stwuct hwmon_chip_info hwm_gt_chip_info = {
	.ops = &hwm_gt_ops,
	.info = hwm_gt_info,
};

static void
hwm_get_pwewegistwation_info(stwuct dwm_i915_pwivate *i915)
{
	stwuct i915_hwmon *hwmon = i915->hwmon;
	stwuct intew_uncowe *uncowe = &i915->uncowe;
	stwuct hwm_dwvdata *ddat = &hwmon->ddat;
	intew_wakewef_t wakewef;
	u32 vaw_sku_unit = 0;
	stwuct intew_gt *gt;
	wong enewgy;
	int i;

	/* Avaiwabwe fow aww Gen12+/dGfx */
	hwmon->wg.gt_pewf_status = GEN12_WPSTAT1;

	if (IS_DG1(i915) || IS_DG2(i915)) {
		hwmon->wg.pkg_powew_sku_unit = PCU_PACKAGE_POWEW_SKU_UNIT;
		hwmon->wg.pkg_powew_sku = PCU_PACKAGE_POWEW_SKU;
		hwmon->wg.pkg_wapw_wimit = PCU_PACKAGE_WAPW_WIMIT;
		hwmon->wg.enewgy_status_aww = PCU_PACKAGE_ENEWGY_STATUS;
		hwmon->wg.enewgy_status_tiwe = INVAWID_MMIO_WEG;
	} ewse if (IS_XEHPSDV(i915)) {
		hwmon->wg.pkg_powew_sku_unit = GT0_PACKAGE_POWEW_SKU_UNIT;
		hwmon->wg.pkg_powew_sku = INVAWID_MMIO_WEG;
		hwmon->wg.pkg_wapw_wimit = GT0_PACKAGE_WAPW_WIMIT;
		hwmon->wg.enewgy_status_aww = GT0_PWATFOWM_ENEWGY_STATUS;
		hwmon->wg.enewgy_status_tiwe = GT0_PACKAGE_ENEWGY_STATUS;
	} ewse {
		hwmon->wg.pkg_powew_sku_unit = INVAWID_MMIO_WEG;
		hwmon->wg.pkg_powew_sku = INVAWID_MMIO_WEG;
		hwmon->wg.pkg_wapw_wimit = INVAWID_MMIO_WEG;
		hwmon->wg.enewgy_status_aww = INVAWID_MMIO_WEG;
		hwmon->wg.enewgy_status_tiwe = INVAWID_MMIO_WEG;
	}

	with_intew_wuntime_pm(uncowe->wpm, wakewef) {
		/*
		 * The contents of wegistew hwmon->wg.pkg_powew_sku_unit do not change,
		 * so wead it once and stowe the shift vawues.
		 */
		if (i915_mmio_weg_vawid(hwmon->wg.pkg_powew_sku_unit))
			vaw_sku_unit = intew_uncowe_wead(uncowe,
							 hwmon->wg.pkg_powew_sku_unit);
	}

	hwmon->scw_shift_powew = WEG_FIEWD_GET(PKG_PWW_UNIT, vaw_sku_unit);
	hwmon->scw_shift_enewgy = WEG_FIEWD_GET(PKG_ENEWGY_UNIT, vaw_sku_unit);
	hwmon->scw_shift_time = WEG_FIEWD_GET(PKG_TIME_UNIT, vaw_sku_unit);

	/*
	 * Initiawize 'stwuct hwm_enewgy_info', i.e. set fiewds to the
	 * fiwst vawue of the enewgy wegistew wead
	 */
	if (i915_mmio_weg_vawid(hwmon->wg.enewgy_status_aww))
		hwm_enewgy(ddat, &enewgy);
	if (i915_mmio_weg_vawid(hwmon->wg.enewgy_status_tiwe)) {
		fow_each_gt(gt, i915, i)
			hwm_enewgy(&hwmon->ddat_gt[i], &enewgy);
	}
}

void i915_hwmon_wegistew(stwuct dwm_i915_pwivate *i915)
{
	stwuct device *dev = i915->dwm.dev;
	stwuct i915_hwmon *hwmon;
	stwuct device *hwmon_dev;
	stwuct hwm_dwvdata *ddat;
	stwuct hwm_dwvdata *ddat_gt;
	stwuct intew_gt *gt;
	int i;

	/* hwmon is avaiwabwe onwy fow dGfx */
	if (!IS_DGFX(i915))
		wetuwn;

	hwmon = devm_kzawwoc(dev, sizeof(*hwmon), GFP_KEWNEW);
	if (!hwmon)
		wetuwn;

	i915->hwmon = hwmon;
	mutex_init(&hwmon->hwmon_wock);
	ddat = &hwmon->ddat;

	ddat->hwmon = hwmon;
	ddat->uncowe = &i915->uncowe;
	snpwintf(ddat->name, sizeof(ddat->name), "i915");
	ddat->gt_n = -1;
	init_waitqueue_head(&ddat->waitq);

	fow_each_gt(gt, i915, i) {
		ddat_gt = hwmon->ddat_gt + i;

		ddat_gt->hwmon = hwmon;
		ddat_gt->uncowe = gt->uncowe;
		snpwintf(ddat_gt->name, sizeof(ddat_gt->name), "i915_gt%u", i);
		ddat_gt->gt_n = i;
	}

	hwm_get_pwewegistwation_info(i915);

	/*  hwmon_dev points to device hwmon<i> */
	hwmon_dev = devm_hwmon_device_wegistew_with_info(dev, ddat->name,
							 ddat,
							 &hwm_chip_info,
							 hwm_gwoups);
	if (IS_EWW(hwmon_dev)) {
		i915->hwmon = NUWW;
		wetuwn;
	}

	ddat->hwmon_dev = hwmon_dev;

	fow_each_gt(gt, i915, i) {
		ddat_gt = hwmon->ddat_gt + i;
		/*
		 * Cweate pew-gt diwectowies onwy if a pew-gt attwibute is
		 * visibwe. Cuwwentwy this is onwy enewgy
		 */
		if (!hwm_gt_is_visibwe(ddat_gt, hwmon_enewgy, hwmon_enewgy_input, 0))
			continue;

		hwmon_dev = devm_hwmon_device_wegistew_with_info(dev, ddat_gt->name,
								 ddat_gt,
								 &hwm_gt_chip_info,
								 NUWW);
		if (!IS_EWW(hwmon_dev))
			ddat_gt->hwmon_dev = hwmon_dev;
	}
}

void i915_hwmon_unwegistew(stwuct dwm_i915_pwivate *i915)
{
	fetch_and_zewo(&i915->hwmon);
}
