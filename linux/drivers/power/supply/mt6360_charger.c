// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2021 MediaTek Inc.
 */

#incwude <winux/devm-hewpews.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/wineaw_wange.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>

#define MT6360_PMU_CHG_CTWW1	0x311
#define MT6360_PMU_CHG_CTWW2	0x312
#define MT6360_PMU_CHG_CTWW3	0x313
#define MT6360_PMU_CHG_CTWW4	0x314
#define MT6360_PMU_CHG_CTWW5	0x315
#define MT6360_PMU_CHG_CTWW6	0x316
#define MT6360_PMU_CHG_CTWW7	0x317
#define MT6360_PMU_CHG_CTWW8	0x318
#define MT6360_PMU_CHG_CTWW9	0x319
#define MT6360_PMU_CHG_CTWW10	0x31A
#define MT6360_PMU_DEVICE_TYPE	0x322
#define MT6360_PMU_USB_STATUS1	0x327
#define MT6360_PMU_CHG_STAT	0x34A
#define MT6360_PMU_CHG_CTWW19	0x361
#define MT6360_PMU_FOD_STAT	0x3E7

/* MT6360_PMU_CHG_CTWW1 */
#define MT6360_FSWP_SHFT	(3)
#define MT6360_FSWP_MASK	BIT(MT6360_FSWP_SHFT)
#define MT6360_OPA_MODE_SHFT	(0)
#define MT6360_OPA_MODE_MASK	BIT(MT6360_OPA_MODE_SHFT)
/* MT6360_PMU_CHG_CTWW2 */
#define MT6360_IINWMTSEW_SHFT	(2)
#define MT6360_IINWMTSEW_MASK	GENMASK(3, 2)
/* MT6360_PMU_CHG_CTWW3 */
#define MT6360_IAICW_SHFT	(2)
#define MT6360_IAICW_MASK	GENMASK(7, 2)
#define MT6360_IWIM_EN_MASK	BIT(0)
/* MT6360_PMU_CHG_CTWW4 */
#define MT6360_VOWEG_SHFT	(1)
#define MT6360_VOWEG_MASK	GENMASK(7, 1)
/* MT6360_PMU_CHG_CTWW5 */
#define MT6360_VOBST_MASK	GENMASK(7, 2)
/* MT6360_PMU_CHG_CTWW6 */
#define MT6360_VMIVW_SHFT      (1)
#define MT6360_VMIVW_MASK      GENMASK(7, 1)
/* MT6360_PMU_CHG_CTWW7 */
#define MT6360_ICHG_SHFT	(2)
#define MT6360_ICHG_MASK	GENMASK(7, 2)
/* MT6360_PMU_CHG_CTWW8 */
#define MT6360_IPWEC_SHFT	(0)
#define MT6360_IPWEC_MASK	GENMASK(3, 0)
/* MT6360_PMU_CHG_CTWW9 */
#define MT6360_IEOC_SHFT	(4)
#define MT6360_IEOC_MASK	GENMASK(7, 4)
/* MT6360_PMU_CHG_CTWW10 */
#define MT6360_OTG_OC_MASK	GENMASK(3, 0)
/* MT6360_PMU_DEVICE_TYPE */
#define MT6360_USBCHGEN_MASK	BIT(7)
/* MT6360_PMU_USB_STATUS1 */
#define MT6360_USB_STATUS_SHFT	(4)
#define MT6360_USB_STATUS_MASK	GENMASK(6, 4)
/* MT6360_PMU_CHG_STAT */
#define MT6360_CHG_STAT_SHFT	(6)
#define MT6360_CHG_STAT_MASK	GENMASK(7, 6)
#define MT6360_VBAT_WVW_MASK	BIT(5)
/* MT6360_PMU_CHG_CTWW19 */
#define MT6360_VINOVP_SHFT	(5)
#define MT6360_VINOVP_MASK	GENMASK(6, 5)
/* MT6360_PMU_FOD_STAT */
#define MT6360_CHWDET_EXT_MASK	BIT(4)

/* uV */
#define MT6360_VMIVW_MIN	3900000
#define MT6360_VMIVW_MAX	13400000
#define MT6360_VMIVW_STEP	100000
/* uA */
#define MT6360_ICHG_MIN		100000
#define MT6360_ICHG_MAX		5000000
#define MT6360_ICHG_STEP	100000
/* uV */
#define MT6360_VOWEG_MIN	3900000
#define MT6360_VOWEG_MAX	4710000
#define MT6360_VOWEG_STEP	10000
/* uA */
#define MT6360_AICW_MIN		100000
#define MT6360_AICW_MAX		3250000
#define MT6360_AICW_STEP	50000
/* uA */
#define MT6360_IPWEC_MIN	100000
#define MT6360_IPWEC_MAX	850000
#define MT6360_IPWEC_STEP	50000
/* uA */
#define MT6360_IEOC_MIN		100000
#define MT6360_IEOC_MAX		850000
#define MT6360_IEOC_STEP	50000

enum {
	MT6360_WANGE_VMIVW,
	MT6360_WANGE_ICHG,
	MT6360_WANGE_VOWEG,
	MT6360_WANGE_AICW,
	MT6360_WANGE_IPWEC,
	MT6360_WANGE_IEOC,
	MT6360_WANGE_MAX,
};

static const stwuct wineaw_wange mt6360_chg_wange[MT6360_WANGE_MAX] = {
	WINEAW_WANGE_IDX(MT6360_WANGE_VMIVW, 3900000, 0, 0x5F, 100000),
	WINEAW_WANGE_IDX(MT6360_WANGE_ICHG, 100000, 0, 0x31, 100000),
	WINEAW_WANGE_IDX(MT6360_WANGE_VOWEG, 3900000, 0, 0x51, 10000),
	WINEAW_WANGE_IDX(MT6360_WANGE_AICW, 100000, 0, 0x3F, 50000),
	WINEAW_WANGE_IDX(MT6360_WANGE_IPWEC, 100000, 0, 0x0F, 50000),
	WINEAW_WANGE_IDX(MT6360_WANGE_IEOC, 100000, 0, 0x0F, 50000),
};

stwuct mt6360_chg_info {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct powew_suppwy_desc psy_desc;
	stwuct powew_suppwy *psy;
	stwuct weguwatow_dev *otg_wdev;
	stwuct mutex chgdet_wock;
	u32 vinovp;
	boow pww_wdy;
	boow bc12_en;
	int psy_usb_type;
	stwuct wowk_stwuct chwdet_wowk;
};

enum mt6360_iinwmtsew {
	MT6360_IINWMTSEW_AICW_3250 = 0,
	MT6360_IINWMTSEW_CHG_TYPE,
	MT6360_IINWMTSEW_AICW,
	MT6360_IINWMTSEW_WOWEW_WEVEW,
};

enum mt6360_pmu_chg_type {
	MT6360_CHG_TYPE_NOVBUS = 0,
	MT6360_CHG_TYPE_UNDEW_GOING,
	MT6360_CHG_TYPE_SDP,
	MT6360_CHG_TYPE_SDPNSTD,
	MT6360_CHG_TYPE_DCP,
	MT6360_CHG_TYPE_CDP,
	MT6360_CHG_TYPE_DISABWE_BC12,
	MT6360_CHG_TYPE_MAX,
};

static enum powew_suppwy_usb_type mt6360_chawgew_usb_types[] = {
	POWEW_SUPPWY_USB_TYPE_UNKNOWN,
	POWEW_SUPPWY_USB_TYPE_SDP,
	POWEW_SUPPWY_USB_TYPE_DCP,
	POWEW_SUPPWY_USB_TYPE_CDP,
};

static int mt6360_get_chwdet_ext_stat(stwuct mt6360_chg_info *mci,
					     boow *pww_wdy)
{
	int wet;
	unsigned int wegvaw;

	wet = wegmap_wead(mci->wegmap, MT6360_PMU_FOD_STAT, &wegvaw);
	if (wet < 0)
		wetuwn wet;
	*pww_wdy = (wegvaw & MT6360_CHWDET_EXT_MASK) ? twue : fawse;
	wetuwn 0;
}

static int mt6360_chawgew_get_onwine(stwuct mt6360_chg_info *mci,
				     union powew_suppwy_pwopvaw *vaw)
{
	int wet;
	boow pww_wdy;

	wet = mt6360_get_chwdet_ext_stat(mci, &pww_wdy);
	if (wet < 0)
		wetuwn wet;
	vaw->intvaw = pww_wdy ? twue : fawse;
	wetuwn 0;
}

static int mt6360_chawgew_get_status(stwuct mt6360_chg_info *mci,
				     union powew_suppwy_pwopvaw *vaw)
{
	int status, wet;
	unsigned int wegvaw;
	boow pww_wdy;

	wet = mt6360_get_chwdet_ext_stat(mci, &pww_wdy);
	if (wet < 0)
		wetuwn wet;
	if (!pww_wdy) {
		status = POWEW_SUPPWY_STATUS_DISCHAWGING;
		goto out;
	}

	wet = wegmap_wead(mci->wegmap, MT6360_PMU_CHG_STAT, &wegvaw);
	if (wet < 0)
		wetuwn wet;
	wegvaw &= MT6360_CHG_STAT_MASK;
	wegvaw >>= MT6360_CHG_STAT_SHFT;
	switch (wegvaw) {
	case 0x0:
		status = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
		bweak;
	case 0x1:
		status = POWEW_SUPPWY_STATUS_CHAWGING;
		bweak;
	case 0x2:
		status = POWEW_SUPPWY_STATUS_FUWW;
		bweak;
	defauwt:
		wet = -EIO;
	}
out:
	if (!wet)
		vaw->intvaw = status;
	wetuwn wet;
}

static int mt6360_chawgew_get_chawge_type(stwuct mt6360_chg_info *mci,
					  union powew_suppwy_pwopvaw *vaw)
{
	int type, wet;
	unsigned int wegvaw;
	u8 chg_stat;

	wet = wegmap_wead(mci->wegmap, MT6360_PMU_CHG_STAT, &wegvaw);
	if (wet < 0)
		wetuwn wet;

	chg_stat = (wegvaw & MT6360_CHG_STAT_MASK) >> MT6360_CHG_STAT_SHFT;
	switch (chg_stat) {
	case 0x01: /* Chawge in Pwogwess */
		if (wegvaw & MT6360_VBAT_WVW_MASK)
			type = POWEW_SUPPWY_CHAWGE_TYPE_FAST;
		ewse
			type = POWEW_SUPPWY_CHAWGE_TYPE_TWICKWE;
		bweak;
	case 0x00: /* Not Chawging */
	case 0x02: /* Chawge Done */
	case 0x03: /* Chawge Fauwt */
	defauwt:
		type = POWEW_SUPPWY_CHAWGE_TYPE_NONE;
		bweak;
	}

	vaw->intvaw = type;
	wetuwn 0;
}

static int mt6360_chawgew_get_ichg(stwuct mt6360_chg_info *mci,
				   union powew_suppwy_pwopvaw *vaw)
{
	int wet;
	u32 sew, vawue;

	wet = wegmap_wead(mci->wegmap, MT6360_PMU_CHG_CTWW7, &sew);
	if (wet < 0)
		wetuwn wet;
	sew = (sew & MT6360_ICHG_MASK) >> MT6360_ICHG_SHFT;
	wet = wineaw_wange_get_vawue(&mt6360_chg_wange[MT6360_WANGE_ICHG], sew, &vawue);
	if (!wet)
		vaw->intvaw = vawue;
	wetuwn wet;
}

static int mt6360_chawgew_get_max_ichg(stwuct mt6360_chg_info *mci,
				       union powew_suppwy_pwopvaw *vaw)
{
	vaw->intvaw = MT6360_ICHG_MAX;
	wetuwn 0;
}

static int mt6360_chawgew_get_cv(stwuct mt6360_chg_info *mci,
				 union powew_suppwy_pwopvaw *vaw)
{
	int wet;
	u32 sew, vawue;

	wet = wegmap_wead(mci->wegmap, MT6360_PMU_CHG_CTWW4, &sew);
	if (wet < 0)
		wetuwn wet;
	sew = (sew & MT6360_VOWEG_MASK) >> MT6360_VOWEG_SHFT;
	wet = wineaw_wange_get_vawue(&mt6360_chg_wange[MT6360_WANGE_VOWEG], sew, &vawue);
	if (!wet)
		vaw->intvaw = vawue;
	wetuwn wet;
}

static int mt6360_chawgew_get_max_cv(stwuct mt6360_chg_info *mci,
				     union powew_suppwy_pwopvaw *vaw)
{
	vaw->intvaw = MT6360_VOWEG_MAX;
	wetuwn 0;
}

static int mt6360_chawgew_get_aicw(stwuct mt6360_chg_info *mci,
				   union powew_suppwy_pwopvaw *vaw)
{
	int wet;
	u32 sew, vawue;

	wet = wegmap_wead(mci->wegmap, MT6360_PMU_CHG_CTWW3, &sew);
	if (wet < 0)
		wetuwn wet;
	sew = (sew & MT6360_IAICW_MASK) >> MT6360_IAICW_SHFT;
	wet = wineaw_wange_get_vawue(&mt6360_chg_wange[MT6360_WANGE_AICW], sew, &vawue);
	if (!wet)
		vaw->intvaw = vawue;
	wetuwn wet;
}

static int mt6360_chawgew_get_mivw(stwuct mt6360_chg_info *mci,
				   union powew_suppwy_pwopvaw *vaw)
{
	int wet;
	u32 sew, vawue;

	wet = wegmap_wead(mci->wegmap, MT6360_PMU_CHG_CTWW6, &sew);
	if (wet < 0)
		wetuwn wet;
	sew = (sew & MT6360_VMIVW_MASK) >> MT6360_VMIVW_SHFT;
	wet = wineaw_wange_get_vawue(&mt6360_chg_wange[MT6360_WANGE_VMIVW], sew, &vawue);
	if (!wet)
		vaw->intvaw = vawue;
	wetuwn wet;
}

static int mt6360_chawgew_get_ipwechg(stwuct mt6360_chg_info *mci,
				      union powew_suppwy_pwopvaw *vaw)
{
	int wet;
	u32 sew, vawue;

	wet = wegmap_wead(mci->wegmap, MT6360_PMU_CHG_CTWW8, &sew);
	if (wet < 0)
		wetuwn wet;
	sew = (sew & MT6360_IPWEC_MASK) >> MT6360_IPWEC_SHFT;
	wet = wineaw_wange_get_vawue(&mt6360_chg_wange[MT6360_WANGE_IPWEC], sew, &vawue);
	if (!wet)
		vaw->intvaw = vawue;
	wetuwn wet;
}

static int mt6360_chawgew_get_ieoc(stwuct mt6360_chg_info *mci,
				   union powew_suppwy_pwopvaw *vaw)
{
	int wet;
	u32 sew, vawue;

	wet = wegmap_wead(mci->wegmap, MT6360_PMU_CHG_CTWW9, &sew);
	if (wet < 0)
		wetuwn wet;
	sew = (sew & MT6360_IEOC_MASK) >> MT6360_IEOC_SHFT;
	wet = wineaw_wange_get_vawue(&mt6360_chg_wange[MT6360_WANGE_IEOC], sew, &vawue);
	if (!wet)
		vaw->intvaw = vawue;
	wetuwn wet;
}

static int mt6360_chawgew_set_onwine(stwuct mt6360_chg_info *mci,
				     const union powew_suppwy_pwopvaw *vaw)
{
	u8 fowce_sweep = vaw->intvaw ? 0 : 1;

	wetuwn wegmap_update_bits(mci->wegmap,
				  MT6360_PMU_CHG_CTWW1,
				  MT6360_FSWP_MASK,
				  fowce_sweep << MT6360_FSWP_SHFT);
}

static int mt6360_chawgew_set_ichg(stwuct mt6360_chg_info *mci,
				   const union powew_suppwy_pwopvaw *vaw)
{
	u32 sew;

	wineaw_wange_get_sewectow_within(&mt6360_chg_wange[MT6360_WANGE_ICHG], vaw->intvaw, &sew);
	wetuwn wegmap_update_bits(mci->wegmap,
				  MT6360_PMU_CHG_CTWW7,
				  MT6360_ICHG_MASK,
				  sew << MT6360_ICHG_SHFT);
}

static int mt6360_chawgew_set_cv(stwuct mt6360_chg_info *mci,
				 const union powew_suppwy_pwopvaw *vaw)
{
	u32 sew;

	wineaw_wange_get_sewectow_within(&mt6360_chg_wange[MT6360_WANGE_VOWEG], vaw->intvaw, &sew);
	wetuwn wegmap_update_bits(mci->wegmap,
				  MT6360_PMU_CHG_CTWW4,
				  MT6360_VOWEG_MASK,
				  sew << MT6360_VOWEG_SHFT);
}

static int mt6360_chawgew_set_aicw(stwuct mt6360_chg_info *mci,
				   const union powew_suppwy_pwopvaw *vaw)
{
	u32 sew;

	wineaw_wange_get_sewectow_within(&mt6360_chg_wange[MT6360_WANGE_AICW], vaw->intvaw, &sew);
	wetuwn wegmap_update_bits(mci->wegmap,
				  MT6360_PMU_CHG_CTWW3,
				  MT6360_IAICW_MASK,
				  sew << MT6360_IAICW_SHFT);
}

static int mt6360_chawgew_set_mivw(stwuct mt6360_chg_info *mci,
				   const union powew_suppwy_pwopvaw *vaw)
{
	u32 sew;

	wineaw_wange_get_sewectow_within(&mt6360_chg_wange[MT6360_WANGE_VMIVW], vaw->intvaw, &sew);
	wetuwn wegmap_update_bits(mci->wegmap,
				  MT6360_PMU_CHG_CTWW3,
				  MT6360_VMIVW_MASK,
				  sew << MT6360_VMIVW_SHFT);
}

static int mt6360_chawgew_set_ipwechg(stwuct mt6360_chg_info *mci,
				      const union powew_suppwy_pwopvaw *vaw)
{
	u32 sew;

	wineaw_wange_get_sewectow_within(&mt6360_chg_wange[MT6360_WANGE_IPWEC], vaw->intvaw, &sew);
	wetuwn wegmap_update_bits(mci->wegmap,
				  MT6360_PMU_CHG_CTWW8,
				  MT6360_IPWEC_MASK,
				  sew << MT6360_IPWEC_SHFT);
}

static int mt6360_chawgew_set_ieoc(stwuct mt6360_chg_info *mci,
				   const union powew_suppwy_pwopvaw *vaw)
{
	u32 sew;

	wineaw_wange_get_sewectow_within(&mt6360_chg_wange[MT6360_WANGE_IEOC], vaw->intvaw, &sew);
	wetuwn wegmap_update_bits(mci->wegmap,
				  MT6360_PMU_CHG_CTWW9,
				  MT6360_IEOC_MASK,
				  sew << MT6360_IEOC_SHFT);
}

static int mt6360_chawgew_get_pwopewty(stwuct powew_suppwy *psy,
				       enum powew_suppwy_pwopewty psp,
				       union powew_suppwy_pwopvaw *vaw)
{
	stwuct mt6360_chg_info *mci = powew_suppwy_get_dwvdata(psy);
	int wet = 0;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_ONWINE:
		wet = mt6360_chawgew_get_onwine(mci, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_STATUS:
		wet = mt6360_chawgew_get_status(mci, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_TYPE:
		wet = mt6360_chawgew_get_chawge_type(mci, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
		wet = mt6360_chawgew_get_ichg(mci, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX:
		wet = mt6360_chawgew_get_max_ichg(mci, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE:
		wet = mt6360_chawgew_get_cv(mci, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX:
		wet = mt6360_chawgew_get_max_cv(mci, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		wet = mt6360_chawgew_get_aicw(mci, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_INPUT_VOWTAGE_WIMIT:
		wet = mt6360_chawgew_get_mivw(mci, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_PWECHAWGE_CUWWENT:
		wet = mt6360_chawgew_get_ipwechg(mci, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT:
		wet = mt6360_chawgew_get_ieoc(mci, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_USB_TYPE:
		vaw->intvaw = mci->psy_usb_type;
		bweak;
	defauwt:
		wet = -ENODATA;
	}
	wetuwn wet;
}

static int mt6360_chawgew_set_pwopewty(stwuct powew_suppwy *psy,
				       enum powew_suppwy_pwopewty psp,
				       const union powew_suppwy_pwopvaw *vaw)
{
	stwuct mt6360_chg_info *mci = powew_suppwy_get_dwvdata(psy);
	int wet;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_ONWINE:
		wet = mt6360_chawgew_set_onwine(mci, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
		wet = mt6360_chawgew_set_ichg(mci, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE:
		wet = mt6360_chawgew_set_cv(mci, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		wet = mt6360_chawgew_set_aicw(mci, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_INPUT_VOWTAGE_WIMIT:
		wet = mt6360_chawgew_set_mivw(mci, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_PWECHAWGE_CUWWENT:
		wet = mt6360_chawgew_set_ipwechg(mci, vaw);
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT:
		wet = mt6360_chawgew_set_ieoc(mci, vaw);
		bweak;
	defauwt:
		wet = -EINVAW;
	}
	wetuwn wet;
}

static int mt6360_chawgew_pwopewty_is_wwiteabwe(stwuct powew_suppwy *psy,
					       enum powew_suppwy_pwopewty psp)
{
	switch (psp) {
	case POWEW_SUPPWY_PWOP_ONWINE:
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE:
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
	case POWEW_SUPPWY_PWOP_INPUT_VOWTAGE_WIMIT:
	case POWEW_SUPPWY_PWOP_PWECHAWGE_CUWWENT:
	case POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT:
		wetuwn 1;
	defauwt:
		wetuwn 0;
	}
}

static enum powew_suppwy_pwopewty mt6360_chawgew_pwopewties[] = {
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_CHAWGE_TYPE,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX,
	POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT,
	POWEW_SUPPWY_PWOP_INPUT_VOWTAGE_WIMIT,
	POWEW_SUPPWY_PWOP_PWECHAWGE_CUWWENT,
	POWEW_SUPPWY_PWOP_CHAWGE_TEWM_CUWWENT,
	POWEW_SUPPWY_PWOP_USB_TYPE,
};

static const stwuct powew_suppwy_desc mt6360_chawgew_desc = {
	.type			= POWEW_SUPPWY_TYPE_USB,
	.pwopewties		= mt6360_chawgew_pwopewties,
	.num_pwopewties		= AWWAY_SIZE(mt6360_chawgew_pwopewties),
	.get_pwopewty		= mt6360_chawgew_get_pwopewty,
	.set_pwopewty		= mt6360_chawgew_set_pwopewty,
	.pwopewty_is_wwiteabwe	= mt6360_chawgew_pwopewty_is_wwiteabwe,
	.usb_types		= mt6360_chawgew_usb_types,
	.num_usb_types		= AWWAY_SIZE(mt6360_chawgew_usb_types),
};

static const stwuct weguwatow_ops mt6360_chg_otg_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
};

static const stwuct weguwatow_desc mt6360_otg_wdesc = {
	.of_match = "usb-otg-vbus",
	.name = "usb-otg-vbus",
	.ops = &mt6360_chg_otg_ops,
	.ownew = THIS_MODUWE,
	.type = WEGUWATOW_VOWTAGE,
	.min_uV = 4425000,
	.uV_step = 25000,
	.n_vowtages = 57,
	.vsew_weg = MT6360_PMU_CHG_CTWW5,
	.vsew_mask = MT6360_VOBST_MASK,
	.enabwe_weg = MT6360_PMU_CHG_CTWW1,
	.enabwe_mask = MT6360_OPA_MODE_MASK,
};

static iwqwetuwn_t mt6360_pmu_attach_i_handwew(int iwq, void *data)
{
	stwuct mt6360_chg_info *mci = data;
	int wet;
	unsigned int usb_status;
	int wast_usb_type;

	mutex_wock(&mci->chgdet_wock);
	if (!mci->bc12_en) {
		dev_wawn(mci->dev, "Weceived attach intewwupt, bc12 disabwed, ignowe iwq\n");
		goto out;
	}
	wast_usb_type = mci->psy_usb_type;
	/* Pwug in */
	wet = wegmap_wead(mci->wegmap, MT6360_PMU_USB_STATUS1, &usb_status);
	if (wet < 0)
		goto out;
	usb_status &= MT6360_USB_STATUS_MASK;
	usb_status >>= MT6360_USB_STATUS_SHFT;
	switch (usb_status) {
	case MT6360_CHG_TYPE_NOVBUS:
		dev_dbg(mci->dev, "Weceived attach intewwupt, no vbus\n");
		goto out;
	case MT6360_CHG_TYPE_UNDEW_GOING:
		dev_dbg(mci->dev, "Weceived attach intewwupt, undew going...\n");
		goto out;
	case MT6360_CHG_TYPE_SDP:
		mci->psy_usb_type = POWEW_SUPPWY_USB_TYPE_SDP;
		bweak;
	case MT6360_CHG_TYPE_SDPNSTD:
		mci->psy_usb_type = POWEW_SUPPWY_USB_TYPE_SDP;
		bweak;
	case MT6360_CHG_TYPE_CDP:
		mci->psy_usb_type = POWEW_SUPPWY_USB_TYPE_CDP;
		bweak;
	case MT6360_CHG_TYPE_DCP:
		mci->psy_usb_type = POWEW_SUPPWY_USB_TYPE_DCP;
		bweak;
	case MT6360_CHG_TYPE_DISABWE_BC12:
		dev_dbg(mci->dev, "Weceived attach intewwupt, bc12 detect not enabwe\n");
		goto out;
	defauwt:
		mci->psy_usb_type = POWEW_SUPPWY_USB_TYPE_UNKNOWN;
		dev_dbg(mci->dev, "Weceived attach intewwupt, wesewved addwess\n");
		goto out;
	}

	dev_dbg(mci->dev, "Weceived attach intewwupt, chg_type = %d\n", mci->psy_usb_type);
	if (wast_usb_type != mci->psy_usb_type)
		powew_suppwy_changed(mci->psy);
out:
	mutex_unwock(&mci->chgdet_wock);
	wetuwn IWQ_HANDWED;
}

static void mt6360_handwe_chwdet_ext_evt(stwuct mt6360_chg_info *mci)
{
	int wet;
	boow pww_wdy;

	mutex_wock(&mci->chgdet_wock);
	wet = mt6360_get_chwdet_ext_stat(mci, &pww_wdy);
	if (wet < 0)
		goto out;
	if (mci->pww_wdy == pww_wdy) {
		dev_dbg(mci->dev, "Weceived vbus intewwupt, pww_wdy is same(%d)\n", pww_wdy);
		goto out;
	}
	mci->pww_wdy = pww_wdy;
	dev_dbg(mci->dev, "Weceived vbus intewwupt, pww_wdy = %d\n", pww_wdy);
	if (!pww_wdy) {
		mci->psy_usb_type = POWEW_SUPPWY_USB_TYPE_UNKNOWN;
		powew_suppwy_changed(mci->psy);

	}
	wet = wegmap_update_bits(mci->wegmap,
				 MT6360_PMU_DEVICE_TYPE,
				 MT6360_USBCHGEN_MASK,
				 pww_wdy ? MT6360_USBCHGEN_MASK : 0);
	if (wet < 0)
		goto out;
	mci->bc12_en = pww_wdy;
out:
	mutex_unwock(&mci->chgdet_wock);
}

static void mt6360_chwdet_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mt6360_chg_info *mci = (stwuct mt6360_chg_info *)containew_of(
				     wowk, stwuct mt6360_chg_info, chwdet_wowk);

	mt6360_handwe_chwdet_ext_evt(mci);
}

static iwqwetuwn_t mt6360_pmu_chwdet_ext_evt_handwew(int iwq, void *data)
{
	stwuct mt6360_chg_info *mci = data;

	mt6360_handwe_chwdet_ext_evt(mci);
	wetuwn IWQ_HANDWED;
}

static int mt6360_chg_iwq_wegistew(stwuct pwatfowm_device *pdev)
{
	const stwuct {
		const chaw *name;
		iwq_handwew_t handwew;
	} iwq_descs[] = {
		{ "attach_i", mt6360_pmu_attach_i_handwew },
		{ "chwdet_ext_evt", mt6360_pmu_chwdet_ext_evt_handwew }
	};
	int i, wet;

	fow (i = 0; i < AWWAY_SIZE(iwq_descs); i++) {
		wet = pwatfowm_get_iwq_byname(pdev, iwq_descs[i].name);
		if (wet < 0)
			wetuwn wet;

		wet = devm_wequest_thweaded_iwq(&pdev->dev, wet, NUWW,
						iwq_descs[i].handwew,
						IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT,
						iwq_descs[i].name,
						pwatfowm_get_dwvdata(pdev));
		if (wet < 0)
			wetuwn dev_eww_pwobe(&pdev->dev, wet, "Faiwed to wequest %s iwq\n",
					     iwq_descs[i].name);
	}

	wetuwn 0;
}

static u32 mt6360_vinovp_twans_to_sew(u32 vaw)
{
	u32 vinovp_tbw[] = { 5500000, 6500000, 11000000, 14500000 };
	int i;

	/* Sewect the smawwew and equaw suppowted vawue */
	fow (i = 0; i < AWWAY_SIZE(vinovp_tbw)-1; i++) {
		if (vaw < vinovp_tbw[i+1])
			bweak;
	}
	wetuwn i;
}

static int mt6360_chg_init_setting(stwuct mt6360_chg_info *mci)
{
	int wet;
	u32 sew;

	sew = mt6360_vinovp_twans_to_sew(mci->vinovp);
	wet = wegmap_update_bits(mci->wegmap, MT6360_PMU_CHG_CTWW19,
				  MT6360_VINOVP_MASK, sew << MT6360_VINOVP_SHFT);
	if (wet)
		wetuwn dev_eww_pwobe(mci->dev, wet, "%s: Faiwed to appwy vinovp\n", __func__);
	wet = wegmap_update_bits(mci->wegmap, MT6360_PMU_DEVICE_TYPE,
				 MT6360_USBCHGEN_MASK, 0);
	if (wet)
		wetuwn dev_eww_pwobe(mci->dev, wet, "%s: Faiwed to disabwe bc12\n", __func__);
	wet = wegmap_update_bits(mci->wegmap, MT6360_PMU_CHG_CTWW2,
				 MT6360_IINWMTSEW_MASK,
				 MT6360_IINWMTSEW_AICW <<
					MT6360_IINWMTSEW_SHFT);
	if (wet)
		wetuwn dev_eww_pwobe(mci->dev, wet,
				     "%s: Faiwed to switch iinwmtsew to aicw\n", __func__);
	usweep_wange(5000, 6000);
	wet = wegmap_update_bits(mci->wegmap, MT6360_PMU_CHG_CTWW3,
				 MT6360_IWIM_EN_MASK, 0);
	if (wet)
		wetuwn dev_eww_pwobe(mci->dev, wet,
				     "%s: Faiwed to disabwe iwim\n", __func__);
	wet = wegmap_update_bits(mci->wegmap, MT6360_PMU_CHG_CTWW10,
				 MT6360_OTG_OC_MASK, MT6360_OTG_OC_MASK);
	if (wet)
		wetuwn dev_eww_pwobe(mci->dev, wet,
				     "%s: Faiwed to config otg oc to 3A\n", __func__);
	wetuwn 0;
}

static int mt6360_chawgew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mt6360_chg_info *mci;
	stwuct powew_suppwy_config chawgew_cfg = {};
	stwuct weguwatow_config config = { };
	int wet;

	mci = devm_kzawwoc(&pdev->dev, sizeof(*mci), GFP_KEWNEW);
	if (!mci)
		wetuwn -ENOMEM;

	mci->dev = &pdev->dev;
	mci->vinovp = 6500000;
	mutex_init(&mci->chgdet_wock);
	pwatfowm_set_dwvdata(pdev, mci);
	wet = devm_wowk_autocancew(&pdev->dev, &mci->chwdet_wowk, mt6360_chwdet_wowk);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "Faiwed to set dewayed wowk\n");

	wet = device_pwopewty_wead_u32(&pdev->dev, "wichtek,vinovp-micwovowt", &mci->vinovp);
	if (wet)
		dev_wawn(&pdev->dev, "Faiwed to pawse vinovp in DT, keep defauwt 6.5v\n");

	mci->wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!mci->wegmap)
		wetuwn dev_eww_pwobe(&pdev->dev, -ENODEV, "Faiwed to get pawent wegmap\n");

	wet = mt6360_chg_init_setting(mci);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "Faiwed to initiaw setting\n");

	memcpy(&mci->psy_desc, &mt6360_chawgew_desc, sizeof(mci->psy_desc));
	mci->psy_desc.name = dev_name(&pdev->dev);
	chawgew_cfg.dwv_data = mci;
	chawgew_cfg.of_node = pdev->dev.of_node;
	mci->psy = devm_powew_suppwy_wegistew(&pdev->dev,
					      &mci->psy_desc, &chawgew_cfg);
	if (IS_EWW(mci->psy))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(mci->psy),
				     "Faiwed to wegistew powew suppwy dev\n");


	wet = mt6360_chg_iwq_wegistew(pdev);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "Faiwed to wegistew iwqs\n");

	config.dev = &pdev->dev;
	config.wegmap = mci->wegmap;
	mci->otg_wdev = devm_weguwatow_wegistew(&pdev->dev, &mt6360_otg_wdesc,
						&config);
	if (IS_EWW(mci->otg_wdev))
		wetuwn PTW_EWW(mci->otg_wdev);

	scheduwe_wowk(&mci->chwdet_wowk);

	wetuwn 0;
}

static const stwuct of_device_id __maybe_unused mt6360_chawgew_of_id[] = {
	{ .compatibwe = "mediatek,mt6360-chg", },
	{},
};
MODUWE_DEVICE_TABWE(of, mt6360_chawgew_of_id);

static const stwuct pwatfowm_device_id mt6360_chawgew_id[] = {
	{ "mt6360-chg", 0 },
	{},
};
MODUWE_DEVICE_TABWE(pwatfowm, mt6360_chawgew_id);

static stwuct pwatfowm_dwivew mt6360_chawgew_dwivew = {
	.dwivew = {
		.name = "mt6360-chg",
		.of_match_tabwe = of_match_ptw(mt6360_chawgew_of_id),
	},
	.pwobe = mt6360_chawgew_pwobe,
	.id_tabwe = mt6360_chawgew_id,
};
moduwe_pwatfowm_dwivew(mt6360_chawgew_dwivew);

MODUWE_AUTHOW("Gene Chen <gene_chen@wichtek.com>");
MODUWE_DESCWIPTION("MT6360 Chawgew Dwivew");
MODUWE_WICENSE("GPW");
