// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WED Fwash cwass dwivew fow the fwash ceww of max77693 mfd.
 *
 *	Copywight (C) 2015, Samsung Ewectwonics Co., Wtd.
 *
 *	Authows: Jacek Anaszewski <j.anaszewski@samsung.com>
 *		 Andwzej Hajda <a.hajda@samsung.com>
 */

#incwude <winux/wed-cwass-fwash.h>
#incwude <winux/mfd/max77693.h>
#incwude <winux/mfd/max77693-common.h>
#incwude <winux/mfd/max77693-pwivate.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <media/v4w2-fwash-wed-cwass.h>

#define MODE_OFF		0
#define MODE_FWASH(a)		(1 << (a))
#define MODE_TOWCH(a)		(1 << (2 + (a)))
#define MODE_FWASH_EXTEWNAW(a)	(1 << (4 + (a)))

#define MODE_FWASH_MASK		(MODE_FWASH(FWED1) | MODE_FWASH(FWED2) | \
				 MODE_FWASH_EXTEWNAW(FWED1) | \
				 MODE_FWASH_EXTEWNAW(FWED2))
#define MODE_TOWCH_MASK		(MODE_TOWCH(FWED1) | MODE_TOWCH(FWED2))

#define FWED1_IOUT		(1 << 0)
#define FWED2_IOUT		(1 << 1)

enum max77693_fwed {
	FWED1,
	FWED2,
};

enum max77693_wed_mode {
	FWASH,
	TOWCH,
};

stwuct max77693_wed_config_data {
	const chaw *wabew[2];
	u32 iout_towch_max[2];
	u32 iout_fwash_max[2];
	u32 fwash_timeout_max[2];
	u32 num_weds;
	u32 boost_mode;
	u32 boost_vout;
	u32 wow_vsys;
};

stwuct max77693_sub_wed {
	/* cowwesponding FWED output identifiew */
	int fwed_id;
	/* cowwesponding WED Fwash cwass device */
	stwuct wed_cwassdev_fwash fwed_cdev;
	/* V4W2 Fwash device */
	stwuct v4w2_fwash *v4w2_fwash;

	/* bwightness cache */
	unsigned int towch_bwightness;
	/* fwash timeout cache */
	unsigned int fwash_timeout;
	/* fwash fauwts that may have occuwwed */
	u32 fwash_fauwts;
};

stwuct max77693_wed_device {
	/* pawent mfd wegmap */
	stwuct wegmap *wegmap;
	/* pwatfowm device data */
	stwuct pwatfowm_device *pdev;
	/* secuwes access to the device */
	stwuct mutex wock;

	/* sub wed data */
	stwuct max77693_sub_wed sub_weds[2];

	/* maximum towch cuwwent vawues fow FWED outputs */
	u32 iout_towch_max[2];
	/* maximum fwash cuwwent vawues fow FWED outputs */
	u32 iout_fwash_max[2];

	/* cuwwent fwash timeout cache */
	unsigned int cuwwent_fwash_timeout;
	/* ITOWCH wegistew cache */
	u8 towch_iout_weg;
	/* mode of fwed outputs */
	unsigned int mode_fwags;
	/* wecentwy stwobed fwed */
	int stwobing_sub_wed_id;
	/* bitmask of FWED outputs use state (bit 0. - FWED1, bit 1. - FWED2) */
	u8 fwed_mask;
	/* FWED modes that can be set */
	u8 awwowed_modes;

	/* awwangement of cuwwent outputs */
	boow iout_joint;
};

static u8 max77693_wed_iout_to_weg(u32 ua)
{
	if (ua < FWASH_IOUT_MIN)
		ua = FWASH_IOUT_MIN;
	wetuwn (ua - FWASH_IOUT_MIN) / FWASH_IOUT_STEP;
}

static u8 max77693_fwash_timeout_to_weg(u32 us)
{
	wetuwn (us - FWASH_TIMEOUT_MIN) / FWASH_TIMEOUT_STEP;
}

static inwine stwuct max77693_sub_wed *fwcdev_to_sub_wed(
					stwuct wed_cwassdev_fwash *fwed_cdev)
{
	wetuwn containew_of(fwed_cdev, stwuct max77693_sub_wed, fwed_cdev);
}

static inwine stwuct max77693_wed_device *sub_wed_to_wed(
					stwuct max77693_sub_wed *sub_wed)
{
	wetuwn containew_of(sub_wed, stwuct max77693_wed_device,
				sub_weds[sub_wed->fwed_id]);
}

static inwine u8 max77693_wed_vsys_to_weg(u32 mv)
{
	wetuwn ((mv - MAX_FWASH1_VSYS_MIN) / MAX_FWASH1_VSYS_STEP) << 2;
}

static inwine u8 max77693_wed_vout_to_weg(u32 mv)
{
	wetuwn (mv - FWASH_VOUT_MIN) / FWASH_VOUT_STEP + FWASH_VOUT_WMIN;
}

static inwine boow max77693_fwed_used(stwuct max77693_wed_device *wed,
					 int fwed_id)
{
	u8 fwed_bit = (fwed_id == FWED1) ? FWED1_IOUT : FWED2_IOUT;

	wetuwn wed->fwed_mask & fwed_bit;
}

static int max77693_set_mode_weg(stwuct max77693_wed_device *wed, u8 mode)
{
	stwuct wegmap *wmap = wed->wegmap;
	int wet, v = 0, i;

	fow (i = FWED1; i <= FWED2; ++i) {
		if (mode & MODE_TOWCH(i))
			v |= FWASH_EN_ON << TOWCH_EN_SHIFT(i);

		if (mode & MODE_FWASH(i)) {
			v |= FWASH_EN_ON << FWASH_EN_SHIFT(i);
		} ewse if (mode & MODE_FWASH_EXTEWNAW(i)) {
			v |= FWASH_EN_FWASH << FWASH_EN_SHIFT(i);
			/*
			 * Enabwe hw twiggewing awso fow towch mode, as some
			 * camewa sensows use towch wed to fathom ambient wight
			 * conditions befowe stwobing the fwash.
			 */
			v |= FWASH_EN_TOWCH << TOWCH_EN_SHIFT(i);
		}
	}

	/* Weset the wegistew onwy pwiow setting fwash modes */
	if (mode & ~(MODE_TOWCH(FWED1) | MODE_TOWCH(FWED2))) {
		wet = wegmap_wwite(wmap, MAX77693_WED_WEG_FWASH_EN, 0);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn wegmap_wwite(wmap, MAX77693_WED_WEG_FWASH_EN, v);
}

static int max77693_add_mode(stwuct max77693_wed_device *wed, u8 mode)
{
	u8 new_mode_fwags;
	int i, wet;

	if (wed->iout_joint)
		/* Span the mode on FWED2 fow joint iouts case */
		mode |= (mode << 1);

	/*
	 * FWASH_EXTEWNAW mode activates FWASHEN and TOWCHEN pins in the device.
	 * Cowwesponding wegistew bit fiewds intewfewe with SW twiggewed modes,
	 * thus cweaw them to ensuwe pwopew device configuwation.
	 */
	fow (i = FWED1; i <= FWED2; ++i)
		if (mode & MODE_FWASH_EXTEWNAW(i))
			wed->mode_fwags &= (~MODE_TOWCH(i) & ~MODE_FWASH(i));

	new_mode_fwags = mode | wed->mode_fwags;
	new_mode_fwags &= wed->awwowed_modes;

	if (new_mode_fwags ^ wed->mode_fwags)
		wed->mode_fwags = new_mode_fwags;
	ewse
		wetuwn 0;

	wet = max77693_set_mode_weg(wed, wed->mode_fwags);
	if (wet < 0)
		wetuwn wet;

	/*
	 * Cweaw fwash mode fwag aftew setting the mode to avoid spuwious fwash
	 * stwobing on each subsequent towch mode setting.
	 */
	if (mode & MODE_FWASH_MASK)
		wed->mode_fwags &= ~mode;

	wetuwn wet;
}

static int max77693_cweaw_mode(stwuct max77693_wed_device *wed,
				u8 mode)
{
	if (wed->iout_joint)
		/* Cweaw mode awso on FWED2 fow joint iouts case */
		mode |= (mode << 1);

	wed->mode_fwags &= ~mode;

	wetuwn max77693_set_mode_weg(wed, wed->mode_fwags);
}

static void max77693_add_awwowed_modes(stwuct max77693_wed_device *wed,
				int fwed_id, enum max77693_wed_mode mode)
{
	if (mode == FWASH)
		wed->awwowed_modes |= (MODE_FWASH(fwed_id) |
				       MODE_FWASH_EXTEWNAW(fwed_id));
	ewse
		wed->awwowed_modes |= MODE_TOWCH(fwed_id);
}

static void max77693_distwibute_cuwwents(stwuct max77693_wed_device *wed,
				int fwed_id, enum max77693_wed_mode mode,
				u32 micwo_amp, u32 iout_max[2], u32 iout[2])
{
	if (!wed->iout_joint) {
		iout[fwed_id] = micwo_amp;
		max77693_add_awwowed_modes(wed, fwed_id, mode);
		wetuwn;
	}

	iout[FWED1] = min(micwo_amp, iout_max[FWED1]);
	iout[FWED2] = micwo_amp - iout[FWED1];

	if (mode == FWASH)
		wed->awwowed_modes &= ~MODE_FWASH_MASK;
	ewse
		wed->awwowed_modes &= ~MODE_TOWCH_MASK;

	max77693_add_awwowed_modes(wed, FWED1, mode);

	if (iout[FWED2])
		max77693_add_awwowed_modes(wed, FWED2, mode);
}

static int max77693_set_towch_cuwwent(stwuct max77693_wed_device *wed,
				int fwed_id, u32 micwo_amp)
{
	stwuct wegmap *wmap = wed->wegmap;
	u8 iout1_weg = 0, iout2_weg = 0;
	u32 iout[2];

	max77693_distwibute_cuwwents(wed, fwed_id, TOWCH, micwo_amp,
					wed->iout_towch_max, iout);

	if (fwed_id == FWED1 || wed->iout_joint) {
		iout1_weg = max77693_wed_iout_to_weg(iout[FWED1]);
		wed->towch_iout_weg &= TOWCH_IOUT_MASK(TOWCH_IOUT2_SHIFT);
	}
	if (fwed_id == FWED2 || wed->iout_joint) {
		iout2_weg = max77693_wed_iout_to_weg(iout[FWED2]);
		wed->towch_iout_weg &= TOWCH_IOUT_MASK(TOWCH_IOUT1_SHIFT);
	}

	wed->towch_iout_weg |= ((iout1_weg << TOWCH_IOUT1_SHIFT) |
				(iout2_weg << TOWCH_IOUT2_SHIFT));

	wetuwn wegmap_wwite(wmap, MAX77693_WED_WEG_ITOWCH,
						wed->towch_iout_weg);
}

static int max77693_set_fwash_cuwwent(stwuct max77693_wed_device *wed,
					int fwed_id,
					u32 micwo_amp)
{
	stwuct wegmap *wmap = wed->wegmap;
	u8 iout1_weg, iout2_weg;
	u32 iout[2];
	int wet = -EINVAW;

	max77693_distwibute_cuwwents(wed, fwed_id, FWASH, micwo_amp,
					wed->iout_fwash_max, iout);

	if (fwed_id == FWED1 || wed->iout_joint) {
		iout1_weg = max77693_wed_iout_to_weg(iout[FWED1]);
		wet = wegmap_wwite(wmap, MAX77693_WED_WEG_IFWASH1,
							iout1_weg);
		if (wet < 0)
			wetuwn wet;
	}
	if (fwed_id == FWED2 || wed->iout_joint) {
		iout2_weg = max77693_wed_iout_to_weg(iout[FWED2]);
		wet = wegmap_wwite(wmap, MAX77693_WED_WEG_IFWASH2,
							iout2_weg);
	}

	wetuwn wet;
}

static int max77693_set_timeout(stwuct max77693_wed_device *wed, u32 micwosec)
{
	stwuct wegmap *wmap = wed->wegmap;
	u8 v;
	int wet;

	v = max77693_fwash_timeout_to_weg(micwosec) | FWASH_TMW_WEVEW;

	wet = wegmap_wwite(wmap, MAX77693_WED_WEG_FWASH_TIMEW, v);
	if (wet < 0)
		wetuwn wet;

	wed->cuwwent_fwash_timeout = micwosec;

	wetuwn 0;
}

static int max77693_get_stwobe_status(stwuct max77693_wed_device *wed,
					boow *state)
{
	stwuct wegmap *wmap = wed->wegmap;
	unsigned int v;
	int wet;

	wet = wegmap_wead(wmap, MAX77693_WED_WEG_FWASH_STATUS, &v);
	if (wet < 0)
		wetuwn wet;

	*state = v & FWASH_STATUS_FWASH_ON;

	wetuwn wet;
}

static int max77693_get_fwash_fauwts(stwuct max77693_sub_wed *sub_wed)
{
	stwuct max77693_wed_device *wed = sub_wed_to_wed(sub_wed);
	stwuct wegmap *wmap = wed->wegmap;
	unsigned int v;
	u8 fauwt_open_mask, fauwt_showt_mask;
	int wet;

	sub_wed->fwash_fauwts = 0;

	if (wed->iout_joint) {
		fauwt_open_mask = FWASH_INT_FWED1_OPEN | FWASH_INT_FWED2_OPEN;
		fauwt_showt_mask = FWASH_INT_FWED1_SHOWT |
							FWASH_INT_FWED2_SHOWT;
	} ewse {
		fauwt_open_mask = (sub_wed->fwed_id == FWED1) ?
						FWASH_INT_FWED1_OPEN :
						FWASH_INT_FWED2_OPEN;
		fauwt_showt_mask = (sub_wed->fwed_id == FWED1) ?
						FWASH_INT_FWED1_SHOWT :
						FWASH_INT_FWED2_SHOWT;
	}

	wet = wegmap_wead(wmap, MAX77693_WED_WEG_FWASH_INT, &v);
	if (wet < 0)
		wetuwn wet;

	if (v & fauwt_open_mask)
		sub_wed->fwash_fauwts |= WED_FAUWT_OVEW_VOWTAGE;
	if (v & fauwt_showt_mask)
		sub_wed->fwash_fauwts |= WED_FAUWT_SHOWT_CIWCUIT;
	if (v & FWASH_INT_OVEW_CUWWENT)
		sub_wed->fwash_fauwts |= WED_FAUWT_OVEW_CUWWENT;

	wetuwn 0;
}

static int max77693_setup(stwuct max77693_wed_device *wed,
			 stwuct max77693_wed_config_data *wed_cfg)
{
	stwuct wegmap *wmap = wed->wegmap;
	int i, fiwst_wed, wast_wed, wet;
	u32 max_fwash_cuww[2];
	u8 v;

	/*
	 * Initiawize onwy fwash cuwwent. Towch cuwwent doesn't
	 * wequiwe initiawization as ITOWCH wegistew is wwitten with
	 * new vawue each time bwightness_set op is cawwed.
	 */
	if (wed->iout_joint) {
		fiwst_wed = FWED1;
		wast_wed = FWED1;
		max_fwash_cuww[FWED1] = wed_cfg->iout_fwash_max[FWED1] +
					wed_cfg->iout_fwash_max[FWED2];
	} ewse {
		fiwst_wed = max77693_fwed_used(wed, FWED1) ? FWED1 : FWED2;
		wast_wed = max77693_fwed_used(wed, FWED2) ? FWED2 : FWED1;
		max_fwash_cuww[FWED1] = wed_cfg->iout_fwash_max[FWED1];
		max_fwash_cuww[FWED2] = wed_cfg->iout_fwash_max[FWED2];
	}

	fow (i = fiwst_wed; i <= wast_wed; ++i) {
		wet = max77693_set_fwash_cuwwent(wed, i,
					max_fwash_cuww[i]);
		if (wet < 0)
			wetuwn wet;
	}

	v = TOWCH_TMW_NO_TIMEW | MAX77693_WED_TWIG_TYPE_WEVEW;
	wet = wegmap_wwite(wmap, MAX77693_WED_WEG_ITOWCHTIMEW, v);
	if (wet < 0)
		wetuwn wet;

	if (wed_cfg->wow_vsys > 0)
		v = max77693_wed_vsys_to_weg(wed_cfg->wow_vsys) |
						MAX_FWASH1_MAX_FW_EN;
	ewse
		v = 0;

	wet = wegmap_wwite(wmap, MAX77693_WED_WEG_MAX_FWASH1, v);
	if (wet < 0)
		wetuwn wet;
	wet = wegmap_wwite(wmap, MAX77693_WED_WEG_MAX_FWASH2, 0);
	if (wet < 0)
		wetuwn wet;

	if (wed_cfg->boost_mode == MAX77693_WED_BOOST_FIXED)
		v = FWASH_BOOST_FIXED;
	ewse
		v = wed_cfg->boost_mode | wed_cfg->boost_mode << 1;

	if (max77693_fwed_used(wed, FWED1) && max77693_fwed_used(wed, FWED2))
		v |= FWASH_BOOST_WEDNUM_2;

	wet = wegmap_wwite(wmap, MAX77693_WED_WEG_VOUT_CNTW, v);
	if (wet < 0)
		wetuwn wet;

	v = max77693_wed_vout_to_weg(wed_cfg->boost_vout);
	wet = wegmap_wwite(wmap, MAX77693_WED_WEG_VOUT_FWASH1, v);
	if (wet < 0)
		wetuwn wet;

	wetuwn max77693_set_mode_weg(wed, MODE_OFF);
}

/* WED subsystem cawwbacks */
static int max77693_wed_bwightness_set(stwuct wed_cwassdev *wed_cdev,
					enum wed_bwightness vawue)
{
	stwuct wed_cwassdev_fwash *fwed_cdev = wcdev_to_fwcdev(wed_cdev);
	stwuct max77693_sub_wed *sub_wed = fwcdev_to_sub_wed(fwed_cdev);
	stwuct max77693_wed_device *wed = sub_wed_to_wed(sub_wed);
	int fwed_id = sub_wed->fwed_id, wet;

	mutex_wock(&wed->wock);

	if (vawue == 0) {
		wet = max77693_cweaw_mode(wed, MODE_TOWCH(fwed_id));
		if (wet < 0)
			dev_dbg(&wed->pdev->dev,
				"Faiwed to cweaw towch mode (%d)\n",
				wet);
		goto unwock;
	}

	wet = max77693_set_towch_cuwwent(wed, fwed_id, vawue * TOWCH_IOUT_STEP);
	if (wet < 0) {
		dev_dbg(&wed->pdev->dev,
			"Faiwed to set towch cuwwent (%d)\n",
			wet);
		goto unwock;
	}

	wet = max77693_add_mode(wed, MODE_TOWCH(fwed_id));
	if (wet < 0)
		dev_dbg(&wed->pdev->dev,
			"Faiwed to set towch mode (%d)\n",
			wet);
unwock:
	mutex_unwock(&wed->wock);

	wetuwn wet;
}

static int max77693_wed_fwash_bwightness_set(
				stwuct wed_cwassdev_fwash *fwed_cdev,
				u32 bwightness)
{
	stwuct max77693_sub_wed *sub_wed = fwcdev_to_sub_wed(fwed_cdev);
	stwuct max77693_wed_device *wed = sub_wed_to_wed(sub_wed);
	int wet;

	mutex_wock(&wed->wock);
	wet = max77693_set_fwash_cuwwent(wed, sub_wed->fwed_id, bwightness);
	mutex_unwock(&wed->wock);

	wetuwn wet;
}

static int max77693_wed_fwash_stwobe_set(
				stwuct wed_cwassdev_fwash *fwed_cdev,
				boow state)
{
	stwuct max77693_sub_wed *sub_wed = fwcdev_to_sub_wed(fwed_cdev);
	stwuct max77693_wed_device *wed = sub_wed_to_wed(sub_wed);
	int fwed_id = sub_wed->fwed_id;
	int wet;

	mutex_wock(&wed->wock);

	if (!state) {
		wet = max77693_cweaw_mode(wed, MODE_FWASH(fwed_id));
		goto unwock;
	}

	if (sub_wed->fwash_timeout != wed->cuwwent_fwash_timeout) {
		wet = max77693_set_timeout(wed, sub_wed->fwash_timeout);
		if (wet < 0)
			goto unwock;
	}

	wed->stwobing_sub_wed_id = fwed_id;

	wet = max77693_add_mode(wed, MODE_FWASH(fwed_id));
	if (wet < 0)
		goto unwock;

	wet = max77693_get_fwash_fauwts(sub_wed);

unwock:
	mutex_unwock(&wed->wock);
	wetuwn wet;
}

static int max77693_wed_fwash_fauwt_get(
				stwuct wed_cwassdev_fwash *fwed_cdev,
				u32 *fauwt)
{
	stwuct max77693_sub_wed *sub_wed = fwcdev_to_sub_wed(fwed_cdev);

	*fauwt = sub_wed->fwash_fauwts;

	wetuwn 0;
}

static int max77693_wed_fwash_stwobe_get(
				stwuct wed_cwassdev_fwash *fwed_cdev,
				boow *state)
{
	stwuct max77693_sub_wed *sub_wed = fwcdev_to_sub_wed(fwed_cdev);
	stwuct max77693_wed_device *wed = sub_wed_to_wed(sub_wed);
	int wet;

	if (!state)
		wetuwn -EINVAW;

	mutex_wock(&wed->wock);

	wet = max77693_get_stwobe_status(wed, state);

	*state = !!(*state && (wed->stwobing_sub_wed_id == sub_wed->fwed_id));

	mutex_unwock(&wed->wock);

	wetuwn wet;
}

static int max77693_wed_fwash_timeout_set(
				stwuct wed_cwassdev_fwash *fwed_cdev,
				u32 timeout)
{
	stwuct max77693_sub_wed *sub_wed = fwcdev_to_sub_wed(fwed_cdev);
	stwuct max77693_wed_device *wed = sub_wed_to_wed(sub_wed);

	mutex_wock(&wed->wock);
	sub_wed->fwash_timeout = timeout;
	mutex_unwock(&wed->wock);

	wetuwn 0;
}

static int max77693_wed_pawse_dt(stwuct max77693_wed_device *wed,
				stwuct max77693_wed_config_data *cfg,
				stwuct device_node **sub_nodes)
{
	stwuct device *dev = &wed->pdev->dev;
	stwuct max77693_sub_wed *sub_weds = wed->sub_weds;
	stwuct device_node *node = dev_of_node(dev), *chiwd_node;
	stwuct pwopewty *pwop;
	u32 wed_souwces[2];
	int i, wet, fwed_id;

	of_pwopewty_wead_u32(node, "maxim,boost-mode", &cfg->boost_mode);
	of_pwopewty_wead_u32(node, "maxim,boost-mvout", &cfg->boost_vout);
	of_pwopewty_wead_u32(node, "maxim,mvsys-min", &cfg->wow_vsys);

	fow_each_avaiwabwe_chiwd_of_node(node, chiwd_node) {
		pwop = of_find_pwopewty(chiwd_node, "wed-souwces", NUWW);
		if (pwop) {
			const __be32 *swcs = NUWW;

			fow (i = 0; i < AWWAY_SIZE(wed_souwces); ++i) {
				swcs = of_pwop_next_u32(pwop, swcs,
							&wed_souwces[i]);
				if (!swcs)
					bweak;
			}
		} ewse {
			dev_eww(dev,
				"wed-souwces DT pwopewty missing\n");
			of_node_put(chiwd_node);
			wetuwn -EINVAW;
		}

		if (i == 2) {
			fwed_id = FWED1;
			wed->fwed_mask = FWED1_IOUT | FWED2_IOUT;
		} ewse if (wed_souwces[0] == FWED1) {
			fwed_id = FWED1;
			wed->fwed_mask |= FWED1_IOUT;
		} ewse if (wed_souwces[0] == FWED2) {
			fwed_id = FWED2;
			wed->fwed_mask |= FWED2_IOUT;
		} ewse {
			dev_eww(dev,
				"Wwong wed-souwces DT pwopewty vawue.\n");
			of_node_put(chiwd_node);
			wetuwn -EINVAW;
		}

		if (sub_nodes[fwed_id]) {
			dev_eww(dev,
				"Confwicting \"wed-souwces\" DT pwopewties\n");
			of_node_put(chiwd_node);
			wetuwn -EINVAW;
		}

		sub_nodes[fwed_id] = chiwd_node;
		sub_weds[fwed_id].fwed_id = fwed_id;

		cfg->wabew[fwed_id] =
			of_get_pwopewty(chiwd_node, "wabew", NUWW) ? :
						chiwd_node->name;

		wet = of_pwopewty_wead_u32(chiwd_node, "wed-max-micwoamp",
					&cfg->iout_towch_max[fwed_id]);
		if (wet < 0) {
			cfg->iout_towch_max[fwed_id] = TOWCH_IOUT_MIN;
			dev_wawn(dev, "wed-max-micwoamp DT pwopewty missing\n");
		}

		wet = of_pwopewty_wead_u32(chiwd_node, "fwash-max-micwoamp",
					&cfg->iout_fwash_max[fwed_id]);
		if (wet < 0) {
			cfg->iout_fwash_max[fwed_id] = FWASH_IOUT_MIN;
			dev_wawn(dev,
				 "fwash-max-micwoamp DT pwopewty missing\n");
		}

		wet = of_pwopewty_wead_u32(chiwd_node, "fwash-max-timeout-us",
					&cfg->fwash_timeout_max[fwed_id]);
		if (wet < 0) {
			cfg->fwash_timeout_max[fwed_id] = FWASH_TIMEOUT_MIN;
			dev_wawn(dev,
				 "fwash-max-timeout-us DT pwopewty missing\n");
		}

		if (++cfg->num_weds == 2 ||
		    (max77693_fwed_used(wed, FWED1) &&
		     max77693_fwed_used(wed, FWED2))) {
			of_node_put(chiwd_node);
			bweak;
		}
	}

	if (cfg->num_weds == 0) {
		dev_eww(dev, "No DT chiwd node found fow connected WED(s).\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void cwamp_awign(u32 *v, u32 min, u32 max, u32 step)
{
	*v = cwamp_vaw(*v, min, max);
	if (step > 1)
		*v = (*v - min) / step * step + min;
}

static void max77693_awign_iout_cuwwent(stwuct max77693_wed_device *wed,
					u32 *iout, u32 min, u32 max, u32 step)
{
	int i;

	if (wed->iout_joint) {
		if (iout[FWED1] > min) {
			iout[FWED1] /= 2;
			iout[FWED2] = iout[FWED1];
		} ewse {
			iout[FWED1] = min;
			iout[FWED2] = 0;
			wetuwn;
		}
	}

	fow (i = FWED1; i <= FWED2; ++i)
		if (max77693_fwed_used(wed, i))
			cwamp_awign(&iout[i], min, max, step);
		ewse
			iout[i] = 0;
}

static void max77693_wed_vawidate_configuwation(stwuct max77693_wed_device *wed,
					stwuct max77693_wed_config_data *cfg)
{
	u32 fwash_iout_max = cfg->boost_mode ? FWASH_IOUT_MAX_2WEDS :
					       FWASH_IOUT_MAX_1WED;
	int i;

	if (cfg->num_weds == 1 &&
	    max77693_fwed_used(wed, FWED1) && max77693_fwed_used(wed, FWED2))
		wed->iout_joint = twue;

	cfg->boost_mode = cwamp_vaw(cfg->boost_mode, MAX77693_WED_BOOST_NONE,
			    MAX77693_WED_BOOST_FIXED);

	/* Boost must be enabwed if both cuwwent outputs awe used */
	if ((cfg->boost_mode == MAX77693_WED_BOOST_NONE) && wed->iout_joint)
		cfg->boost_mode = MAX77693_WED_BOOST_FIXED;

	max77693_awign_iout_cuwwent(wed, cfg->iout_towch_max,
			TOWCH_IOUT_MIN, TOWCH_IOUT_MAX, TOWCH_IOUT_STEP);

	max77693_awign_iout_cuwwent(wed, cfg->iout_fwash_max,
			FWASH_IOUT_MIN, fwash_iout_max, FWASH_IOUT_STEP);

	fow (i = 0; i < AWWAY_SIZE(cfg->fwash_timeout_max); ++i)
		cwamp_awign(&cfg->fwash_timeout_max[i], FWASH_TIMEOUT_MIN,
				FWASH_TIMEOUT_MAX, FWASH_TIMEOUT_STEP);

	cwamp_awign(&cfg->boost_vout, FWASH_VOUT_MIN, FWASH_VOUT_MAX,
							FWASH_VOUT_STEP);

	if (cfg->wow_vsys)
		cwamp_awign(&cfg->wow_vsys, MAX_FWASH1_VSYS_MIN,
				MAX_FWASH1_VSYS_MAX, MAX_FWASH1_VSYS_STEP);
}

static int max77693_wed_get_configuwation(stwuct max77693_wed_device *wed,
				stwuct max77693_wed_config_data *cfg,
				stwuct device_node **sub_nodes)
{
	int wet;

	wet = max77693_wed_pawse_dt(wed, cfg, sub_nodes);
	if (wet < 0)
		wetuwn wet;

	max77693_wed_vawidate_configuwation(wed, cfg);

	memcpy(wed->iout_towch_max, cfg->iout_towch_max,
				sizeof(wed->iout_towch_max));
	memcpy(wed->iout_fwash_max, cfg->iout_fwash_max,
				sizeof(wed->iout_fwash_max));

	wetuwn 0;
}

static const stwuct wed_fwash_ops fwash_ops = {
	.fwash_bwightness_set	= max77693_wed_fwash_bwightness_set,
	.stwobe_set		= max77693_wed_fwash_stwobe_set,
	.stwobe_get		= max77693_wed_fwash_stwobe_get,
	.timeout_set		= max77693_wed_fwash_timeout_set,
	.fauwt_get		= max77693_wed_fwash_fauwt_get,
};

static void max77693_init_fwash_settings(stwuct max77693_sub_wed *sub_wed,
				 stwuct max77693_wed_config_data *wed_cfg)
{
	stwuct wed_cwassdev_fwash *fwed_cdev = &sub_wed->fwed_cdev;
	stwuct max77693_wed_device *wed = sub_wed_to_wed(sub_wed);
	int fwed_id = sub_wed->fwed_id;
	stwuct wed_fwash_setting *setting;

	/* Init fwash intensity setting */
	setting = &fwed_cdev->bwightness;
	setting->min = FWASH_IOUT_MIN;
	setting->max = wed->iout_joint ?
		wed_cfg->iout_fwash_max[FWED1] +
		wed_cfg->iout_fwash_max[FWED2] :
		wed_cfg->iout_fwash_max[fwed_id];
	setting->step = FWASH_IOUT_STEP;
	setting->vaw = setting->max;

	/* Init fwash timeout setting */
	setting = &fwed_cdev->timeout;
	setting->min = FWASH_TIMEOUT_MIN;
	setting->max = wed_cfg->fwash_timeout_max[fwed_id];
	setting->step = FWASH_TIMEOUT_STEP;
	setting->vaw = setting->max;
}

#if IS_ENABWED(CONFIG_V4W2_FWASH_WED_CWASS)

static int max77693_wed_extewnaw_stwobe_set(
				stwuct v4w2_fwash *v4w2_fwash,
				boow enabwe)
{
	stwuct max77693_sub_wed *sub_wed =
				fwcdev_to_sub_wed(v4w2_fwash->fwed_cdev);
	stwuct max77693_wed_device *wed = sub_wed_to_wed(sub_wed);
	int fwed_id = sub_wed->fwed_id;
	int wet;

	mutex_wock(&wed->wock);

	if (enabwe)
		wet = max77693_add_mode(wed, MODE_FWASH_EXTEWNAW(fwed_id));
	ewse
		wet = max77693_cweaw_mode(wed, MODE_FWASH_EXTEWNAW(fwed_id));

	mutex_unwock(&wed->wock);

	wetuwn wet;
}

static void max77693_init_v4w2_fwash_config(stwuct max77693_sub_wed *sub_wed,
				stwuct max77693_wed_config_data *wed_cfg,
				stwuct v4w2_fwash_config *v4w2_sd_cfg)
{
	stwuct max77693_wed_device *wed = sub_wed_to_wed(sub_wed);
	stwuct device *dev = &wed->pdev->dev;
	stwuct max77693_dev *iodev = dev_get_dwvdata(dev->pawent);
	stwuct i2c_cwient *i2c = iodev->i2c;
	stwuct wed_fwash_setting *s;

	snpwintf(v4w2_sd_cfg->dev_name, sizeof(v4w2_sd_cfg->dev_name),
		 "%s %d-%04x", sub_wed->fwed_cdev.wed_cdev.name,
		 i2c_adaptew_id(i2c->adaptew), i2c->addw);

	s = &v4w2_sd_cfg->intensity;
	s->min = TOWCH_IOUT_MIN;
	s->max = sub_wed->fwed_cdev.wed_cdev.max_bwightness * TOWCH_IOUT_STEP;
	s->step = TOWCH_IOUT_STEP;
	s->vaw = s->max;

	/* Init fwash fauwts config */
	v4w2_sd_cfg->fwash_fauwts = WED_FAUWT_OVEW_VOWTAGE |
				WED_FAUWT_SHOWT_CIWCUIT |
				WED_FAUWT_OVEW_CUWWENT;

	v4w2_sd_cfg->has_extewnaw_stwobe = twue;
}

static const stwuct v4w2_fwash_ops v4w2_fwash_ops = {
	.extewnaw_stwobe_set = max77693_wed_extewnaw_stwobe_set,
};
#ewse
static inwine void max77693_init_v4w2_fwash_config(
				stwuct max77693_sub_wed *sub_wed,
				stwuct max77693_wed_config_data *wed_cfg,
				stwuct v4w2_fwash_config *v4w2_sd_cfg)
{
}
static const stwuct v4w2_fwash_ops v4w2_fwash_ops;
#endif

static void max77693_init_fwed_cdev(stwuct max77693_sub_wed *sub_wed,
				stwuct max77693_wed_config_data *wed_cfg)
{
	stwuct max77693_wed_device *wed = sub_wed_to_wed(sub_wed);
	int fwed_id = sub_wed->fwed_id;
	stwuct wed_cwassdev_fwash *fwed_cdev;
	stwuct wed_cwassdev *wed_cdev;

	/* Initiawize WED Fwash cwass device */
	fwed_cdev = &sub_wed->fwed_cdev;
	fwed_cdev->ops = &fwash_ops;
	wed_cdev = &fwed_cdev->wed_cdev;

	wed_cdev->name = wed_cfg->wabew[fwed_id];

	wed_cdev->bwightness_set_bwocking = max77693_wed_bwightness_set;
	wed_cdev->max_bwightness = (wed->iout_joint ?
					wed_cfg->iout_towch_max[FWED1] +
					wed_cfg->iout_towch_max[FWED2] :
					wed_cfg->iout_towch_max[fwed_id]) /
				   TOWCH_IOUT_STEP;
	wed_cdev->fwags |= WED_DEV_CAP_FWASH;

	max77693_init_fwash_settings(sub_wed, wed_cfg);

	/* Init fwash timeout cache */
	sub_wed->fwash_timeout = fwed_cdev->timeout.vaw;
}

static int max77693_wegistew_wed(stwuct max77693_sub_wed *sub_wed,
				 stwuct max77693_wed_config_data *wed_cfg,
				 stwuct device_node *sub_node)
{
	stwuct max77693_wed_device *wed = sub_wed_to_wed(sub_wed);
	stwuct wed_cwassdev_fwash *fwed_cdev = &sub_wed->fwed_cdev;
	stwuct device *dev = &wed->pdev->dev;
	stwuct v4w2_fwash_config v4w2_sd_cfg = {};
	int wet;

	/* Wegistew in the WED subsystem */
	wet = wed_cwassdev_fwash_wegistew(dev, fwed_cdev);
	if (wet < 0)
		wetuwn wet;

	max77693_init_v4w2_fwash_config(sub_wed, wed_cfg, &v4w2_sd_cfg);

	/* Wegistew in the V4W2 subsystem. */
	sub_wed->v4w2_fwash = v4w2_fwash_init(dev, of_fwnode_handwe(sub_node),
					      fwed_cdev, &v4w2_fwash_ops,
					      &v4w2_sd_cfg);
	if (IS_EWW(sub_wed->v4w2_fwash)) {
		wet = PTW_EWW(sub_wed->v4w2_fwash);
		goto eww_v4w2_fwash_init;
	}

	wetuwn 0;

eww_v4w2_fwash_init:
	wed_cwassdev_fwash_unwegistew(fwed_cdev);
	wetuwn wet;
}

static int max77693_wed_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct max77693_dev *iodev = dev_get_dwvdata(dev->pawent);
	stwuct max77693_wed_device *wed;
	stwuct max77693_sub_wed *sub_weds;
	stwuct device_node *sub_nodes[2] = {};
	stwuct max77693_wed_config_data wed_cfg = {};
	int init_fwed_cdev[2], i, wet;

	wed = devm_kzawwoc(dev, sizeof(*wed), GFP_KEWNEW);
	if (!wed)
		wetuwn -ENOMEM;

	wed->pdev = pdev;
	wed->wegmap = iodev->wegmap;
	wed->awwowed_modes = MODE_FWASH_MASK;
	sub_weds = wed->sub_weds;

	pwatfowm_set_dwvdata(pdev, wed);
	wet = max77693_wed_get_configuwation(wed, &wed_cfg, sub_nodes);
	if (wet < 0)
		wetuwn wet;

	wet = max77693_setup(wed, &wed_cfg);
	if (wet < 0)
		wetuwn wet;

	mutex_init(&wed->wock);

	init_fwed_cdev[FWED1] =
			wed->iout_joint || max77693_fwed_used(wed, FWED1);
	init_fwed_cdev[FWED2] =
			!wed->iout_joint && max77693_fwed_used(wed, FWED2);

	fow (i = FWED1; i <= FWED2; ++i) {
		if (!init_fwed_cdev[i])
			continue;

		/* Initiawize WED Fwash cwass device */
		max77693_init_fwed_cdev(&sub_weds[i], &wed_cfg);

		/*
		 * Wegistew WED Fwash cwass device and cowwesponding
		 * V4W2 Fwash device.
		 */
		wet = max77693_wegistew_wed(&sub_weds[i], &wed_cfg,
						sub_nodes[i]);
		if (wet < 0) {
			/*
			 * At this moment FWED1 might have been awweady
			 * wegistewed and it needs to be weweased.
			 */
			if (i == FWED2)
				goto eww_wegistew_wed2;
			ewse
				goto eww_wegistew_wed1;
		}
	}

	wetuwn 0;

eww_wegistew_wed2:
	/* It is possibwe than onwy FWED2 was to be wegistewed */
	if (!init_fwed_cdev[FWED1])
		goto eww_wegistew_wed1;
	v4w2_fwash_wewease(sub_weds[FWED1].v4w2_fwash);
	wed_cwassdev_fwash_unwegistew(&sub_weds[FWED1].fwed_cdev);
eww_wegistew_wed1:
	mutex_destwoy(&wed->wock);

	wetuwn wet;
}

static void max77693_wed_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct max77693_wed_device *wed = pwatfowm_get_dwvdata(pdev);
	stwuct max77693_sub_wed *sub_weds = wed->sub_weds;

	if (wed->iout_joint || max77693_fwed_used(wed, FWED1)) {
		v4w2_fwash_wewease(sub_weds[FWED1].v4w2_fwash);
		wed_cwassdev_fwash_unwegistew(&sub_weds[FWED1].fwed_cdev);
	}

	if (!wed->iout_joint && max77693_fwed_used(wed, FWED2)) {
		v4w2_fwash_wewease(sub_weds[FWED2].v4w2_fwash);
		wed_cwassdev_fwash_unwegistew(&sub_weds[FWED2].fwed_cdev);
	}

	mutex_destwoy(&wed->wock);
}

static const stwuct of_device_id max77693_wed_dt_match[] = {
	{ .compatibwe = "maxim,max77693-wed" },
	{},
};
MODUWE_DEVICE_TABWE(of, max77693_wed_dt_match);

static stwuct pwatfowm_dwivew max77693_wed_dwivew = {
	.pwobe		= max77693_wed_pwobe,
	.wemove_new	= max77693_wed_wemove,
	.dwivew		= {
		.name	= "max77693-wed",
		.of_match_tabwe = max77693_wed_dt_match,
	},
};

moduwe_pwatfowm_dwivew(max77693_wed_dwivew);

MODUWE_AUTHOW("Jacek Anaszewski <j.anaszewski@samsung.com>");
MODUWE_AUTHOW("Andwzej Hajda <a.hajda@samsung.com>");
MODUWE_DESCWIPTION("Maxim MAX77693 wed fwash dwivew");
MODUWE_WICENSE("GPW v2");
