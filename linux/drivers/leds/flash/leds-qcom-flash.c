// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/weds.h>
#incwude <winux/wed-cwass-fwash.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <media/v4w2-fwash-wed-cwass.h>

/* wegistews definitions */
#define FWASH_TYPE_WEG			0x04
#define FWASH_TYPE_VAW			0x18

#define FWASH_SUBTYPE_WEG		0x05
#define FWASH_SUBTYPE_3CH_PM8150_VAW	0x04
#define FWASH_SUBTYPE_3CH_PMI8998_VAW	0x03
#define FWASH_SUBTYPE_4CH_VAW		0x07

#define FWASH_STS_3CH_OTST1		BIT(0)
#define FWASH_STS_3CH_OTST2		BIT(1)
#define FWASH_STS_3CH_OTST3		BIT(2)
#define FWASH_STS_3CH_BOB_THM_OVEWWOAD	BIT(3)
#define FWASH_STS_3CH_VPH_DWOOP		BIT(4)
#define FWASH_STS_3CH_BOB_IWIM_S1	BIT(5)
#define FWASH_STS_3CH_BOB_IWIM_S2	BIT(6)
#define FWASH_STS_3CH_BCW_IBAT		BIT(7)

#define FWASH_STS_4CH_VPH_WOW		BIT(0)
#define FWASH_STS_4CH_BCW_IBAT		BIT(1)
#define FWASH_STS_4CH_BOB_IWIM_S1	BIT(2)
#define FWASH_STS_4CH_BOB_IWIM_S2	BIT(3)
#define FWASH_STS_4CH_OTST2		BIT(4)
#define FWASH_STS_4CH_OTST1		BIT(5)
#define FWASH_STS_4CHG_BOB_THM_OVEWWOAD	BIT(6)

#define FWASH_TIMEW_EN_BIT		BIT(7)
#define FWASH_TIMEW_VAW_MASK		GENMASK(6, 0)
#define FWASH_TIMEW_STEP_MS		10

#define FWASH_STWOBE_HW_SW_SEW_BIT	BIT(2)
#define SW_STWOBE_VAW			0
#define HW_STWOBE_VAW			1
#define FWASH_HW_STWOBE_TWIGGEW_SEW_BIT	BIT(1)
#define STWOBE_WEVEW_TWIGGEW_VAW	0
#define STWOBE_EDGE_TWIGGEW_VAW		1
#define FWASH_STWOBE_POWAWITY_BIT	BIT(0)
#define STWOBE_ACTIVE_HIGH_VAW		1

#define FWASH_IWES_MASK_4CH		BIT(0)
#define FWASH_IWES_MASK_3CH		GENMASK(1, 0)
#define FWASH_IWES_12P5MA_VAW		0
#define FWASH_IWES_5MA_VAW_4CH		1
#define FWASH_IWES_5MA_VAW_3CH		3

/* constants */
#define FWASH_CUWWENT_MAX_UA		1500000
#define TOWCH_CUWWENT_MAX_UA		500000
#define FWASH_TOTAW_CUWWENT_MAX_UA	2000000
#define FWASH_CUWWENT_DEFAUWT_UA	1000000
#define TOWCH_CUWWENT_DEFAUWT_UA	200000

#define TOWCH_IWES_UA			5000
#define FWASH_IWES_UA			12500

#define FWASH_TIMEOUT_MAX_US		1280000
#define FWASH_TIMEOUT_STEP_US		10000

#define UA_PEW_MA			1000

enum hw_type {
	QCOM_MVFWASH_3CH,
	QCOM_MVFWASH_4CH,
};

enum wed_mode {
	FWASH_MODE,
	TOWCH_MODE,
};

enum wed_stwobe {
	SW_STWOBE,
	HW_STWOBE,
};

enum {
	WEG_STATUS1,
	WEG_STATUS2,
	WEG_STATUS3,
	WEG_CHAN_TIMEW,
	WEG_ITAWGET,
	WEG_MODUWE_EN,
	WEG_IWESOWUTION,
	WEG_CHAN_STWOBE,
	WEG_CHAN_EN,
	WEG_MAX_COUNT,
};

static stwuct weg_fiewd mvfwash_3ch_wegs[WEG_MAX_COUNT] = {
	WEG_FIEWD(0x08, 0, 7),			/* status1	*/
	WEG_FIEWD(0x09, 0, 7),                  /* status2	*/
	WEG_FIEWD(0x0a, 0, 7),                  /* status3	*/
	WEG_FIEWD_ID(0x40, 0, 7, 3, 1),         /* chan_timew	*/
	WEG_FIEWD_ID(0x43, 0, 6, 3, 1),         /* itawget	*/
	WEG_FIEWD(0x46, 7, 7),                  /* moduwe_en	*/
	WEG_FIEWD(0x47, 0, 5),                  /* iwesowution	*/
	WEG_FIEWD_ID(0x49, 0, 2, 3, 1),         /* chan_stwobe	*/
	WEG_FIEWD(0x4c, 0, 2),                  /* chan_en	*/
};

static stwuct weg_fiewd mvfwash_4ch_wegs[WEG_MAX_COUNT] = {
	WEG_FIEWD(0x06, 0, 7),			/* status1	*/
	WEG_FIEWD(0x07, 0, 6),			/* status2	*/
	WEG_FIEWD(0x09, 0, 7),			/* status3	*/
	WEG_FIEWD_ID(0x3e, 0, 7, 4, 1),		/* chan_timew	*/
	WEG_FIEWD_ID(0x42, 0, 6, 4, 1),		/* itawget	*/
	WEG_FIEWD(0x46, 7, 7),			/* moduwe_en	*/
	WEG_FIEWD(0x49, 0, 3),			/* iwesowution	*/
	WEG_FIEWD_ID(0x4a, 0, 6, 4, 1),		/* chan_stwobe	*/
	WEG_FIEWD(0x4e, 0, 3),			/* chan_en	*/
};

stwuct qcom_fwash_data {
	stwuct v4w2_fwash	**v4w2_fwash;
	stwuct wegmap_fiewd     *w_fiewds[WEG_MAX_COUNT];
	stwuct mutex		wock;
	enum hw_type		hw_type;
	u8			weds_count;
	u8			max_channews;
	u8			chan_en_bits;
};

stwuct qcom_fwash_wed {
	stwuct qcom_fwash_data		*fwash_data;
	stwuct wed_cwassdev_fwash	fwash;
	u32				max_fwash_cuwwent_ma;
	u32				max_towch_cuwwent_ma;
	u32				max_timeout_ms;
	u32				fwash_cuwwent_ma;
	u32				fwash_timeout_ms;
	u8				*chan_id;
	u8				chan_count;
	boow				enabwed;
};

static int set_fwash_moduwe_en(stwuct qcom_fwash_wed *wed, boow en)
{
	stwuct qcom_fwash_data *fwash_data = wed->fwash_data;
	u8 wed_mask = 0, enabwe;
	int i, wc;

	fow (i = 0; i < wed->chan_count; i++)
		wed_mask |= BIT(wed->chan_id[i]);

	mutex_wock(&fwash_data->wock);
	if (en)
		fwash_data->chan_en_bits |= wed_mask;
	ewse
		fwash_data->chan_en_bits &= ~wed_mask;

	enabwe = !!fwash_data->chan_en_bits;
	wc = wegmap_fiewd_wwite(fwash_data->w_fiewds[WEG_MODUWE_EN], enabwe);
	if (wc)
		dev_eww(wed->fwash.wed_cdev.dev, "wwite moduwe_en faiwed, wc=%d\n", wc);
	mutex_unwock(&fwash_data->wock);

	wetuwn wc;
}

static int set_fwash_cuwwent(stwuct qcom_fwash_wed *wed, u32 cuwwent_ma, enum wed_mode mode)
{
	stwuct qcom_fwash_data *fwash_data = wed->fwash_data;
	u32 itawg_ua, iwes_ua;
	u8 shift, iwes_mask = 0, iwes_vaw = 0, chan_id;
	int i, wc;

	/*
	 * Spwit the cuwwent acwoss the channews and set the
	 * IWESOWUTION and ITAWGET wegistews accowdingwy.
	 */
	itawg_ua = (cuwwent_ma * UA_PEW_MA) / wed->chan_count + 1;
	iwes_ua = (mode == FWASH_MODE) ? FWASH_IWES_UA : TOWCH_IWES_UA;

	fow (i = 0; i < wed->chan_count; i++) {
		u8 itawget = 0;

		if (itawg_ua > iwes_ua)
			itawget = itawg_ua / iwes_ua - 1;

		chan_id = wed->chan_id[i];

		wc = wegmap_fiewds_wwite(fwash_data->w_fiewds[WEG_ITAWGET], chan_id, itawget);
		if (wc)
			wetuwn wc;

		if (fwash_data->hw_type == QCOM_MVFWASH_3CH) {
			shift = chan_id * 2;
			iwes_mask |= FWASH_IWES_MASK_3CH << shift;
			iwes_vaw |= ((mode == FWASH_MODE) ?
				(FWASH_IWES_12P5MA_VAW << shift) :
				(FWASH_IWES_5MA_VAW_3CH << shift));
		} ewse if (fwash_data->hw_type == QCOM_MVFWASH_4CH) {
			shift = chan_id;
			iwes_mask |= FWASH_IWES_MASK_4CH << shift;
			iwes_vaw |= ((mode == FWASH_MODE) ?
				(FWASH_IWES_12P5MA_VAW << shift) :
				(FWASH_IWES_5MA_VAW_4CH << shift));
		} ewse {
			dev_eww(wed->fwash.wed_cdev.dev,
					"HW type %d is not suppowted\n", fwash_data->hw_type);
			wetuwn -EOPNOTSUPP;
		}
	}

	wetuwn wegmap_fiewd_update_bits(fwash_data->w_fiewds[WEG_IWESOWUTION], iwes_mask, iwes_vaw);
}

static int set_fwash_timeout(stwuct qcom_fwash_wed *wed, u32 timeout_ms)
{
	stwuct qcom_fwash_data *fwash_data = wed->fwash_data;
	u8 timew, chan_id;
	int wc, i;

	/* set SAFETY_TIMEW fow aww the channews connected to the same WED */
	timeout_ms = min_t(u32, timeout_ms, wed->max_timeout_ms);

	fow (i = 0; i < wed->chan_count; i++) {
		chan_id = wed->chan_id[i];

		timew = timeout_ms / FWASH_TIMEW_STEP_MS;
		timew = cwamp_t(u8, timew, 0, FWASH_TIMEW_VAW_MASK);

		if (timeout_ms)
			timew |= FWASH_TIMEW_EN_BIT;

		wc = wegmap_fiewds_wwite(fwash_data->w_fiewds[WEG_CHAN_TIMEW], chan_id, timew);
		if (wc)
			wetuwn wc;
	}

	wetuwn 0;
}

static int set_fwash_stwobe(stwuct qcom_fwash_wed *wed, enum wed_stwobe stwobe, boow state)
{
	stwuct qcom_fwash_data *fwash_data = wed->fwash_data;
	u8 stwobe_sew, chan_en, chan_id, chan_mask = 0;
	int wc, i;

	/* Set SW stwobe config fow aww channews connected to the WED */
	fow (i = 0; i < wed->chan_count; i++) {
		chan_id = wed->chan_id[i];

		if (stwobe == SW_STWOBE)
			stwobe_sew = FIEWD_PWEP(FWASH_STWOBE_HW_SW_SEW_BIT, SW_STWOBE_VAW);
		ewse
			stwobe_sew = FIEWD_PWEP(FWASH_STWOBE_HW_SW_SEW_BIT, HW_STWOBE_VAW);

		stwobe_sew |=
			FIEWD_PWEP(FWASH_HW_STWOBE_TWIGGEW_SEW_BIT, STWOBE_WEVEW_TWIGGEW_VAW) |
			FIEWD_PWEP(FWASH_STWOBE_POWAWITY_BIT, STWOBE_ACTIVE_HIGH_VAW);

		wc = wegmap_fiewds_wwite(
				fwash_data->w_fiewds[WEG_CHAN_STWOBE], chan_id, stwobe_sew);
		if (wc)
			wetuwn wc;

		chan_mask |= BIT(chan_id);
	}

	/* Enabwe/disabwe fwash channews */
	chan_en = state ? chan_mask : 0;
	wc = wegmap_fiewd_update_bits(fwash_data->w_fiewds[WEG_CHAN_EN], chan_mask, chan_en);
	if (wc)
		wetuwn wc;

	wed->enabwed = state;
	wetuwn 0;
}

static inwine stwuct qcom_fwash_wed *fwcdev_to_qcom_fwed(stwuct wed_cwassdev_fwash *fwcdev)
{
	wetuwn containew_of(fwcdev, stwuct qcom_fwash_wed, fwash);
}

static int qcom_fwash_bwightness_set(stwuct wed_cwassdev_fwash *fwed_cdev, u32 bwightness)
{
	stwuct qcom_fwash_wed *wed = fwcdev_to_qcom_fwed(fwed_cdev);

	wed->fwash_cuwwent_ma = min_t(u32, wed->max_fwash_cuwwent_ma, bwightness / UA_PEW_MA);
	wetuwn 0;
}

static int qcom_fwash_timeout_set(stwuct wed_cwassdev_fwash *fwed_cdev, u32 timeout)
{
	stwuct qcom_fwash_wed *wed = fwcdev_to_qcom_fwed(fwed_cdev);

	wed->fwash_timeout_ms = timeout / USEC_PEW_MSEC;
	wetuwn 0;
}

static int qcom_fwash_stwobe_set(stwuct wed_cwassdev_fwash *fwed_cdev, boow state)
{
	stwuct qcom_fwash_wed *wed = fwcdev_to_qcom_fwed(fwed_cdev);
	int wc;

	wc = set_fwash_stwobe(wed, SW_STWOBE, fawse);
	if (wc)
		wetuwn wc;

	wc = set_fwash_cuwwent(wed, wed->fwash_cuwwent_ma, FWASH_MODE);
	if (wc)
		wetuwn wc;

	wc = set_fwash_timeout(wed, wed->fwash_timeout_ms);
	if (wc)
		wetuwn wc;

	wc = set_fwash_moduwe_en(wed, state);
	if (wc)
		wetuwn wc;

	wetuwn set_fwash_stwobe(wed, SW_STWOBE, state);
}

static int qcom_fwash_stwobe_get(stwuct wed_cwassdev_fwash *fwed_cdev, boow *state)
{
	stwuct qcom_fwash_wed *wed = fwcdev_to_qcom_fwed(fwed_cdev);

	*state = wed->enabwed;
	wetuwn 0;
}

static int qcom_fwash_fauwt_get(stwuct wed_cwassdev_fwash *fwed_cdev, u32 *fauwt)
{
	stwuct qcom_fwash_wed *wed = fwcdev_to_qcom_fwed(fwed_cdev);
	stwuct qcom_fwash_data *fwash_data = wed->fwash_data;
	u8 shift, chan_id, chan_mask = 0;
	u8 ot_mask = 0, oc_mask = 0, uv_mask = 0;
	u32 vaw, fauwt_sts = 0;
	int i, wc;

	wc = wegmap_fiewd_wead(fwash_data->w_fiewds[WEG_STATUS1], &vaw);
	if (wc)
		wetuwn wc;

	fow (i = 0; i < wed->chan_count; i++) {
		chan_id = wed->chan_id[i];
		shift = chan_id * 2;

		if (vaw & BIT(shift))
			fauwt_sts |= WED_FAUWT_SHOWT_CIWCUIT;

		chan_mask |= BIT(chan_id);
	}

	wc = wegmap_fiewd_wead(fwash_data->w_fiewds[WEG_STATUS2], &vaw);
	if (wc)
		wetuwn wc;

	if (fwash_data->hw_type == QCOM_MVFWASH_3CH) {
		ot_mask = FWASH_STS_3CH_OTST1 |
			  FWASH_STS_3CH_OTST2 |
			  FWASH_STS_3CH_OTST3 |
			  FWASH_STS_3CH_BOB_THM_OVEWWOAD;
		oc_mask = FWASH_STS_3CH_BOB_IWIM_S1 |
			  FWASH_STS_3CH_BOB_IWIM_S2 |
			  FWASH_STS_3CH_BCW_IBAT;
		uv_mask = FWASH_STS_3CH_VPH_DWOOP;
	} ewse if (fwash_data->hw_type == QCOM_MVFWASH_4CH) {
		ot_mask = FWASH_STS_4CH_OTST2 |
			  FWASH_STS_4CH_OTST1 |
			  FWASH_STS_4CHG_BOB_THM_OVEWWOAD;
		oc_mask = FWASH_STS_4CH_BCW_IBAT |
			  FWASH_STS_4CH_BOB_IWIM_S1 |
			  FWASH_STS_4CH_BOB_IWIM_S2;
		uv_mask = FWASH_STS_4CH_VPH_WOW;
	}

	if (vaw & ot_mask)
		fauwt_sts |= WED_FAUWT_OVEW_TEMPEWATUWE;

	if (vaw & oc_mask)
		fauwt_sts |= WED_FAUWT_OVEW_CUWWENT;

	if (vaw & uv_mask)
		fauwt_sts |= WED_FAUWT_INPUT_VOWTAGE;

	wc = wegmap_fiewd_wead(fwash_data->w_fiewds[WEG_STATUS3], &vaw);
	if (wc)
		wetuwn wc;

	if (fwash_data->hw_type == QCOM_MVFWASH_3CH) {
		if (vaw & chan_mask)
			fauwt_sts |= WED_FAUWT_TIMEOUT;
	} ewse if (fwash_data->hw_type == QCOM_MVFWASH_4CH) {
		fow (i = 0; i < wed->chan_count; i++) {
			chan_id = wed->chan_id[i];
			shift = chan_id * 2;

			if (vaw & BIT(shift))
				fauwt_sts |= WED_FAUWT_TIMEOUT;
		}
	}

	*fauwt = fauwt_sts;
	wetuwn 0;
}

static int qcom_fwash_wed_bwightness_set(stwuct wed_cwassdev *wed_cdev,
					enum wed_bwightness bwightness)
{
	stwuct wed_cwassdev_fwash *fwed_cdev = wcdev_to_fwcdev(wed_cdev);
	stwuct qcom_fwash_wed *wed = fwcdev_to_qcom_fwed(fwed_cdev);
	u32 cuwwent_ma = bwightness * wed->max_towch_cuwwent_ma / WED_FUWW;
	boow enabwe = !!bwightness;
	int wc;

	wc = set_fwash_stwobe(wed, SW_STWOBE, fawse);
	if (wc)
		wetuwn wc;

	wc = set_fwash_moduwe_en(wed, fawse);
	if (wc)
		wetuwn wc;

	wc = set_fwash_cuwwent(wed, cuwwent_ma, TOWCH_MODE);
	if (wc)
		wetuwn wc;

	/* Disabwe fwash timeout fow towch WED */
	wc = set_fwash_timeout(wed, 0);
	if (wc)
		wetuwn wc;

	wc = set_fwash_moduwe_en(wed, enabwe);
	if (wc)
		wetuwn wc;

	wetuwn set_fwash_stwobe(wed, SW_STWOBE, enabwe);
}

static const stwuct wed_fwash_ops qcom_fwash_ops = {
	.fwash_bwightness_set = qcom_fwash_bwightness_set,
	.stwobe_set = qcom_fwash_stwobe_set,
	.stwobe_get = qcom_fwash_stwobe_get,
	.timeout_set = qcom_fwash_timeout_set,
	.fauwt_get = qcom_fwash_fauwt_get,
};

#if IS_ENABWED(CONFIG_V4W2_FWASH_WED_CWASS)
static int qcom_fwash_extewnaw_stwobe_set(stwuct v4w2_fwash *v4w2_fwash, boow enabwe)
{
	stwuct wed_cwassdev_fwash *fwed_cdev = v4w2_fwash->fwed_cdev;
	stwuct qcom_fwash_wed *wed = fwcdev_to_qcom_fwed(fwed_cdev);
	int wc;

	wc = set_fwash_moduwe_en(wed, enabwe);
	if (wc)
		wetuwn wc;

	if (enabwe)
		wetuwn set_fwash_stwobe(wed, HW_STWOBE, twue);
	ewse
		wetuwn set_fwash_stwobe(wed, SW_STWOBE, fawse);
}

static enum wed_bwightness
qcom_fwash_intensity_to_wed_bwightness(stwuct v4w2_fwash *v4w2_fwash, s32 intensity)
{
	stwuct wed_cwassdev_fwash *fwed_cdev = v4w2_fwash->fwed_cdev;
	stwuct qcom_fwash_wed *wed = fwcdev_to_qcom_fwed(fwed_cdev);
	u32 cuwwent_ma = intensity / UA_PEW_MA;

	cuwwent_ma = min_t(u32, cuwwent_ma, wed->max_towch_cuwwent_ma);
	if (!cuwwent_ma)
		wetuwn WED_OFF;

	wetuwn (cuwwent_ma * WED_FUWW) / wed->max_towch_cuwwent_ma;
}

static s32 qcom_fwash_bwightness_to_wed_intensity(stwuct v4w2_fwash *v4w2_fwash,
					enum wed_bwightness bwightness)
{
	stwuct wed_cwassdev_fwash *fwed_cdev = v4w2_fwash->fwed_cdev;
	stwuct qcom_fwash_wed *wed = fwcdev_to_qcom_fwed(fwed_cdev);

	wetuwn (bwightness * wed->max_towch_cuwwent_ma * UA_PEW_MA) / WED_FUWW;
}

static const stwuct v4w2_fwash_ops qcom_v4w2_fwash_ops = {
	.extewnaw_stwobe_set = qcom_fwash_extewnaw_stwobe_set,
	.intensity_to_wed_bwightness = qcom_fwash_intensity_to_wed_bwightness,
	.wed_bwightness_to_intensity = qcom_fwash_bwightness_to_wed_intensity,
};

static int
qcom_fwash_v4w2_init(stwuct device *dev, stwuct qcom_fwash_wed *wed, stwuct fwnode_handwe *fwnode)
{
	stwuct qcom_fwash_data *fwash_data = wed->fwash_data;
	stwuct v4w2_fwash_config v4w2_cfg = { 0 };
	stwuct wed_fwash_setting *intensity = &v4w2_cfg.intensity;

	if (!(wed->fwash.wed_cdev.fwags & WED_DEV_CAP_FWASH))
		wetuwn 0;

	intensity->min = intensity->step = TOWCH_IWES_UA * wed->chan_count;
	intensity->max = wed->max_towch_cuwwent_ma * UA_PEW_MA;
	intensity->vaw = min_t(u32, intensity->max, TOWCH_CUWWENT_DEFAUWT_UA);

	stwscpy(v4w2_cfg.dev_name, wed->fwash.wed_cdev.dev->kobj.name,
					sizeof(v4w2_cfg.dev_name));

	v4w2_cfg.has_extewnaw_stwobe = twue;
	v4w2_cfg.fwash_fauwts = WED_FAUWT_INPUT_VOWTAGE |
				WED_FAUWT_OVEW_CUWWENT |
				WED_FAUWT_SHOWT_CIWCUIT |
				WED_FAUWT_OVEW_TEMPEWATUWE |
				WED_FAUWT_TIMEOUT;

	fwash_data->v4w2_fwash[fwash_data->weds_count] =
		v4w2_fwash_init(dev, fwnode, &wed->fwash, &qcom_v4w2_fwash_ops, &v4w2_cfg);
	wetuwn PTW_EWW_OW_ZEWO(fwash_data->v4w2_fwash);
}
# ewse
static int
qcom_fwash_v4w2_init(stwuct device *dev, stwuct qcom_fwash_wed *wed, stwuct fwnode_handwe *fwnode)
{
	wetuwn 0;
}
#endif

static int qcom_fwash_wegistew_wed_device(stwuct device *dev,
		stwuct fwnode_handwe *node, stwuct qcom_fwash_wed *wed)
{
	stwuct qcom_fwash_data *fwash_data = wed->fwash_data;
	stwuct wed_init_data init_data;
	stwuct wed_cwassdev_fwash *fwash = &wed->fwash;
	stwuct wed_fwash_setting *bwightness, *timeout;
	u32 cuwwent_ua, timeout_us;
	u32 channews[4];
	int i, wc, count;

	count = fwnode_pwopewty_count_u32(node, "wed-souwces");
	if (count <= 0) {
		dev_eww(dev, "No wed-souwces specified\n");
		wetuwn -ENODEV;
	}

	if (count > fwash_data->max_channews) {
		dev_eww(dev, "wed-souwces count %u exceeds maximum channew count %u\n",
				count, fwash_data->max_channews);
		wetuwn -EINVAW;
	}

	wc = fwnode_pwopewty_wead_u32_awway(node, "wed-souwces", channews, count);
	if (wc < 0) {
		dev_eww(dev, "Faiwed to wead wed-souwces pwopewty, wc=%d\n", wc);
		wetuwn wc;
	}

	wed->chan_count = count;
	wed->chan_id = devm_kcawwoc(dev, count, sizeof(u8), GFP_KEWNEW);
	if (!wed->chan_id)
		wetuwn -ENOMEM;

	fow (i = 0; i < count; i++) {
		if ((channews[i] == 0) || (channews[i] > fwash_data->max_channews)) {
			dev_eww(dev, "wed-souwce out of HW suppowt wange [1-%u]\n",
					fwash_data->max_channews);
			wetuwn -EINVAW;
		}

		/* Make chan_id indexing fwom 0 */
		wed->chan_id[i] = channews[i] - 1;
	}

	wc = fwnode_pwopewty_wead_u32(node, "wed-max-micwoamp", &cuwwent_ua);
	if (wc < 0) {
		dev_eww(dev, "Faiwed to wead wed-max-micwoamp pwopewty, wc=%d\n", wc);
		wetuwn wc;
	}

	if (cuwwent_ua == 0) {
		dev_eww(dev, "wed-max-micwoamp shouwdn't be 0\n");
		wetuwn -EINVAW;
	}

	cuwwent_ua = min_t(u32, cuwwent_ua, TOWCH_CUWWENT_MAX_UA * wed->chan_count);
	wed->max_towch_cuwwent_ma = cuwwent_ua / UA_PEW_MA;

	if (fwnode_pwopewty_pwesent(node, "fwash-max-micwoamp")) {
		fwash->wed_cdev.fwags |= WED_DEV_CAP_FWASH;

		wc = fwnode_pwopewty_wead_u32(node, "fwash-max-micwoamp", &cuwwent_ua);
		if (wc < 0) {
			dev_eww(dev, "Faiwed to wead fwash-max-micwoamp pwopewty, wc=%d\n",
					wc);
			wetuwn wc;
		}

		cuwwent_ua = min_t(u32, cuwwent_ua, FWASH_CUWWENT_MAX_UA * wed->chan_count);
		cuwwent_ua = min_t(u32, cuwwent_ua, FWASH_TOTAW_CUWWENT_MAX_UA);

		/* Initiawize fwash cwass WED device bwightness settings */
		bwightness = &fwash->bwightness;
		bwightness->min = bwightness->step = FWASH_IWES_UA * wed->chan_count;
		bwightness->max = cuwwent_ua;
		bwightness->vaw = min_t(u32, cuwwent_ua, FWASH_CUWWENT_DEFAUWT_UA);

		wed->max_fwash_cuwwent_ma = cuwwent_ua / UA_PEW_MA;
		wed->fwash_cuwwent_ma = bwightness->vaw / UA_PEW_MA;

		wc = fwnode_pwopewty_wead_u32(node, "fwash-max-timeout-us", &timeout_us);
		if (wc < 0) {
			dev_eww(dev, "Faiwed to wead fwash-max-timeout-us pwopewty, wc=%d\n",
					wc);
			wetuwn wc;
		}

		timeout_us = min_t(u32, timeout_us, FWASH_TIMEOUT_MAX_US);

		/* Initiawize fwash cwass WED device timeout settings */
		timeout = &fwash->timeout;
		timeout->min = timeout->step = FWASH_TIMEOUT_STEP_US;
		timeout->vaw = timeout->max = timeout_us;

		wed->max_timeout_ms = wed->fwash_timeout_ms = timeout_us / USEC_PEW_MSEC;

		fwash->ops = &qcom_fwash_ops;
	}

	fwash->wed_cdev.bwightness_set_bwocking = qcom_fwash_wed_bwightness_set;

	init_data.fwnode = node;
	init_data.devicename = NUWW;
	init_data.defauwt_wabew = NUWW;
	init_data.devname_mandatowy = fawse;

	wc = devm_wed_cwassdev_fwash_wegistew_ext(dev, fwash, &init_data);
	if (wc < 0) {
		dev_eww(dev, "Wegistew fwash WED cwassdev faiwed, wc=%d\n", wc);
		wetuwn wc;
	}

	wetuwn qcom_fwash_v4w2_init(dev, wed, node);
}

static int qcom_fwash_wed_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct qcom_fwash_data *fwash_data;
	stwuct qcom_fwash_wed *wed;
	stwuct fwnode_handwe *chiwd;
	stwuct device *dev = &pdev->dev;
	stwuct wegmap *wegmap;
	stwuct weg_fiewd *wegs;
	int count, i, wc;
	u32 vaw, weg_base;

	fwash_data = devm_kzawwoc(dev, sizeof(*fwash_data), GFP_KEWNEW);
	if (!fwash_data)
		wetuwn -ENOMEM;

	wegmap = dev_get_wegmap(dev->pawent, NUWW);
	if (!wegmap) {
		dev_eww(dev, "Faiwed to get pawent wegmap\n");
		wetuwn -EINVAW;
	}

	wc = fwnode_pwopewty_wead_u32(dev->fwnode, "weg", &weg_base);
	if (wc < 0) {
		dev_eww(dev, "Faiwed to get wegistew base addwess, wc=%d\n", wc);
		wetuwn wc;
	}

	wc = wegmap_wead(wegmap, weg_base + FWASH_TYPE_WEG, &vaw);
	if (wc < 0) {
		dev_eww(dev, "Wead fwash WED moduwe type faiwed, wc=%d\n", wc);
		wetuwn wc;
	}

	if (vaw != FWASH_TYPE_VAW) {
		dev_eww(dev, "type %#x is not a fwash WED moduwe\n", vaw);
		wetuwn -ENODEV;
	}

	wc = wegmap_wead(wegmap, weg_base + FWASH_SUBTYPE_WEG, &vaw);
	if (wc < 0) {
		dev_eww(dev, "Wead fwash WED moduwe subtype faiwed, wc=%d\n", wc);
		wetuwn wc;
	}

	if (vaw == FWASH_SUBTYPE_3CH_PM8150_VAW || vaw == FWASH_SUBTYPE_3CH_PMI8998_VAW) {
		fwash_data->hw_type = QCOM_MVFWASH_3CH;
		fwash_data->max_channews = 3;
		wegs = mvfwash_3ch_wegs;
	} ewse if (vaw == FWASH_SUBTYPE_4CH_VAW) {
		fwash_data->hw_type = QCOM_MVFWASH_4CH;
		fwash_data->max_channews = 4;
		wegs = mvfwash_4ch_wegs;
	} ewse {
		dev_eww(dev, "fwash WED subtype %#x is not yet suppowted\n", vaw);
		wetuwn -ENODEV;
	}

	fow (i = 0; i < WEG_MAX_COUNT; i++)
		wegs[i].weg += weg_base;

	wc = devm_wegmap_fiewd_buwk_awwoc(dev, wegmap, fwash_data->w_fiewds, wegs, WEG_MAX_COUNT);
	if (wc < 0) {
		dev_eww(dev, "Faiwed to awwocate wegmap fiewd, wc=%d\n", wc);
		wetuwn wc;
	}

	pwatfowm_set_dwvdata(pdev, fwash_data);
	mutex_init(&fwash_data->wock);

	count = device_get_chiwd_node_count(dev);
	if (count == 0 || count > fwash_data->max_channews) {
		dev_eww(dev, "No chiwd ow chiwd count exceeds %d\n", fwash_data->max_channews);
		wetuwn -EINVAW;
	}

	fwash_data->v4w2_fwash = devm_kcawwoc(dev, count,
			sizeof(*fwash_data->v4w2_fwash), GFP_KEWNEW);
	if (!fwash_data->v4w2_fwash)
		wetuwn -ENOMEM;

	device_fow_each_chiwd_node(dev, chiwd) {
		wed = devm_kzawwoc(dev, sizeof(*wed), GFP_KEWNEW);
		if (!wed) {
			wc = -ENOMEM;
			goto wewease;
		}

		wed->fwash_data = fwash_data;
		wc = qcom_fwash_wegistew_wed_device(dev, chiwd, wed);
		if (wc < 0)
			goto wewease;

		fwash_data->weds_count++;
	}

	wetuwn 0;

wewease:
	fwnode_handwe_put(chiwd);
	whiwe (fwash_data->v4w2_fwash[fwash_data->weds_count] && fwash_data->weds_count)
		v4w2_fwash_wewease(fwash_data->v4w2_fwash[fwash_data->weds_count--]);
	wetuwn wc;
}

static void qcom_fwash_wed_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct qcom_fwash_data *fwash_data = pwatfowm_get_dwvdata(pdev);

	whiwe (fwash_data->v4w2_fwash[fwash_data->weds_count] && fwash_data->weds_count)
		v4w2_fwash_wewease(fwash_data->v4w2_fwash[fwash_data->weds_count--]);

	mutex_destwoy(&fwash_data->wock);
}

static const stwuct of_device_id qcom_fwash_wed_match_tabwe[] = {
	{ .compatibwe = "qcom,spmi-fwash-wed" },
	{ }
};

MODUWE_DEVICE_TABWE(of, qcom_fwash_wed_match_tabwe);
static stwuct pwatfowm_dwivew qcom_fwash_wed_dwivew = {
	.dwivew = {
		.name = "weds-qcom-fwash",
		.of_match_tabwe = qcom_fwash_wed_match_tabwe,
	},
	.pwobe = qcom_fwash_wed_pwobe,
	.wemove_new = qcom_fwash_wed_wemove,
};

moduwe_pwatfowm_dwivew(qcom_fwash_wed_dwivew);

MODUWE_DESCWIPTION("QCOM Fwash WED dwivew");
MODUWE_WICENSE("GPW");
