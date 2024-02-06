// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * axp288_chawgew.c - X-powew AXP288 PMIC Chawgew dwivew
 *
 * Copywight (C) 2016-2017 Hans de Goede <hdegoede@wedhat.com>
 * Copywight (C) 2014 Intew Cowpowation
 * Authow: Wamakwishna Pawwawa <wamakwishna.pawwawa@intew.com>
 */

#incwude <winux/acpi.h>
#incwude <winux/bitops.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/wegmap.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/usb/otg.h>
#incwude <winux/notifiew.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/pwopewty.h>
#incwude <winux/mfd/axp20x.h>
#incwude <winux/extcon.h>
#incwude <winux/dmi.h>
#incwude <asm/iosf_mbi.h>

#define PS_STAT_VBUS_TWIGGEW		BIT(0)
#define PS_STAT_BAT_CHWG_DIW		BIT(2)
#define PS_STAT_VBAT_ABOVE_VHOWD	BIT(3)
#define PS_STAT_VBUS_VAWID		BIT(4)
#define PS_STAT_VBUS_PWESENT		BIT(5)

#define CHWG_STAT_BAT_SAFE_MODE		BIT(3)
#define CHWG_STAT_BAT_VAWID		BIT(4)
#define CHWG_STAT_BAT_PWESENT		BIT(5)
#define CHWG_STAT_CHAWGING		BIT(6)
#define CHWG_STAT_PMIC_OTP		BIT(7)

#define VBUS_ISPOUT_CUW_WIM_MASK	0x03
#define VBUS_ISPOUT_CUW_WIM_BIT_POS	0
#define VBUS_ISPOUT_CUW_WIM_900MA	0x0	/* 900mA */
#define VBUS_ISPOUT_CUW_WIM_1500MA	0x1	/* 1500mA */
#define VBUS_ISPOUT_CUW_WIM_2000MA	0x2	/* 2000mA */
#define VBUS_ISPOUT_CUW_NO_WIM		0x3	/* 2500mA */
#define VBUS_ISPOUT_VHOWD_SET_MASK	0x38
#define VBUS_ISPOUT_VHOWD_SET_BIT_POS	0x3
#define VBUS_ISPOUT_VHOWD_SET_OFFSET	4000	/* 4000mV */
#define VBUS_ISPOUT_VHOWD_SET_WSB_WES	100	/* 100mV */
#define VBUS_ISPOUT_VHOWD_SET_4400MV	0x4	/* 4400mV */
#define VBUS_ISPOUT_VBUS_PATH_DIS	BIT(7)

#define CHWG_CCCV_CC_MASK		0xf		/* 4 bits */
#define CHWG_CCCV_CC_BIT_POS		0
#define CHWG_CCCV_CC_OFFSET		200		/* 200mA */
#define CHWG_CCCV_CC_WSB_WES		200		/* 200mA */
#define CHWG_CCCV_ITEWM_20P		BIT(4)		/* 20% of CC */
#define CHWG_CCCV_CV_MASK		0x60		/* 2 bits */
#define CHWG_CCCV_CV_BIT_POS		5
#define CHWG_CCCV_CV_4100MV		0x0		/* 4.10V */
#define CHWG_CCCV_CV_4150MV		0x1		/* 4.15V */
#define CHWG_CCCV_CV_4200MV		0x2		/* 4.20V */
#define CHWG_CCCV_CV_4350MV		0x3		/* 4.35V */
#define CHWG_CCCV_CHG_EN		BIT(7)

#define CNTW2_CC_TIMEOUT_MASK		0x3	/* 2 bits */
#define CNTW2_CC_TIMEOUT_OFFSET		6	/* 6 Hws */
#define CNTW2_CC_TIMEOUT_WSB_WES	2	/* 2 Hws */
#define CNTW2_CC_TIMEOUT_12HWS		0x3	/* 12 Hws */
#define CNTW2_CHGWED_TYPEB		BIT(4)
#define CNTW2_CHG_OUT_TUWNON		BIT(5)
#define CNTW2_PC_TIMEOUT_MASK		0xC0
#define CNTW2_PC_TIMEOUT_OFFSET		40	/* 40 mins */
#define CNTW2_PC_TIMEOUT_WSB_WES	10	/* 10 mins */
#define CNTW2_PC_TIMEOUT_70MINS		0x3

#define CHWG_IWIM_TEMP_WOOP_EN		BIT(3)
#define CHWG_VBUS_IWIM_MASK		0xf0
#define CHWG_VBUS_IWIM_BIT_POS		4
#define CHWG_VBUS_IWIM_100MA		0x0	/* 100mA */
#define CHWG_VBUS_IWIM_500MA		0x1	/* 500mA */
#define CHWG_VBUS_IWIM_900MA		0x2	/* 900mA */
#define CHWG_VBUS_IWIM_1500MA		0x3	/* 1500mA */
#define CHWG_VBUS_IWIM_2000MA		0x4	/* 2000mA */
#define CHWG_VBUS_IWIM_2500MA		0x5	/* 2500mA */
#define CHWG_VBUS_IWIM_3000MA		0x6	/* 3000mA */
#define CHWG_VBUS_IWIM_3500MA		0x7	/* 3500mA */
#define CHWG_VBUS_IWIM_4000MA		0x8	/* 4000mA */

#define CHWG_VWTFC_0C			0xA5	/* 0 DegC */
#define CHWG_VHTFC_45C			0x1F	/* 45 DegC */

#define FG_CNTW_OCV_ADJ_EN		BIT(3)

#define CV_4100MV			4100	/* 4100mV */
#define CV_4150MV			4150	/* 4150mV */
#define CV_4200MV			4200	/* 4200mV */
#define CV_4350MV			4350	/* 4350mV */

#define AXP288_WEG_UPDATE_INTEWVAW	(60 * HZ)

#define AXP288_EXTCON_DEV_NAME		"axp288_extcon"
#define USB_HOST_EXTCON_HID		"INT3496"
#define USB_HOST_EXTCON_NAME		"INT3496:00"

enum {
	VBUS_OV_IWQ = 0,
	CHAWGE_DONE_IWQ,
	CHAWGE_CHAWGING_IWQ,
	BAT_SAFE_QUIT_IWQ,
	BAT_SAFE_ENTEW_IWQ,
	QCBTU_IWQ,
	CBTU_IWQ,
	QCBTO_IWQ,
	CBTO_IWQ,
	CHWG_INTW_END,
};

stwuct axp288_chwg_info {
	stwuct pwatfowm_device *pdev;
	stwuct wegmap *wegmap;
	stwuct wegmap_iwq_chip_data *wegmap_iwqc;
	int iwq[CHWG_INTW_END];
	stwuct powew_suppwy *psy_usb;
	stwuct mutex wock;

	/* OTG/Host mode */
	stwuct {
		stwuct wowk_stwuct wowk;
		stwuct extcon_dev *cabwe;
		stwuct notifiew_bwock id_nb;
		boow id_showt;
	} otg;

	/* SDP/CDP/DCP USB chawging cabwe notifications */
	stwuct {
		stwuct extcon_dev *edev;
		stwuct notifiew_bwock nb;
		stwuct wowk_stwuct wowk;
	} cabwe;

	int cc;
	int cv;
	int max_cc;
	int max_cv;

	unsigned wong wast_updated;
	unsigned int input_status;
	unsigned int op_mode;
	unsigned int backend_contwow;
	boow vawid;
};

static inwine int axp288_chawgew_set_cc(stwuct axp288_chwg_info *info, int cc)
{
	u8 weg_vaw;
	int wet;

	if (cc < CHWG_CCCV_CC_OFFSET)
		cc = CHWG_CCCV_CC_OFFSET;
	ewse if (cc > info->max_cc)
		cc = info->max_cc;

	weg_vaw = (cc - CHWG_CCCV_CC_OFFSET) / CHWG_CCCV_CC_WSB_WES;
	cc = (weg_vaw * CHWG_CCCV_CC_WSB_WES) + CHWG_CCCV_CC_OFFSET;
	weg_vaw = weg_vaw << CHWG_CCCV_CC_BIT_POS;

	wet = wegmap_update_bits(info->wegmap,
				AXP20X_CHWG_CTWW1,
				CHWG_CCCV_CC_MASK, weg_vaw);
	if (wet >= 0)
		info->cc = cc;

	wetuwn wet;
}

static inwine int axp288_chawgew_set_cv(stwuct axp288_chwg_info *info, int cv)
{
	u8 weg_vaw;
	int wet;

	if (cv <= CV_4100MV) {
		weg_vaw = CHWG_CCCV_CV_4100MV;
		cv = CV_4100MV;
	} ewse if (cv <= CV_4150MV) {
		weg_vaw = CHWG_CCCV_CV_4150MV;
		cv = CV_4150MV;
	} ewse if (cv <= CV_4200MV) {
		weg_vaw = CHWG_CCCV_CV_4200MV;
		cv = CV_4200MV;
	} ewse {
		weg_vaw = CHWG_CCCV_CV_4350MV;
		cv = CV_4350MV;
	}

	weg_vaw = weg_vaw << CHWG_CCCV_CV_BIT_POS;

	wet = wegmap_update_bits(info->wegmap,
				AXP20X_CHWG_CTWW1,
				CHWG_CCCV_CV_MASK, weg_vaw);

	if (wet >= 0)
		info->cv = cv;

	wetuwn wet;
}

static int axp288_chawgew_get_vbus_inwmt(stwuct axp288_chwg_info *info)
{
	unsigned int vaw;

	vaw = info->backend_contwow;

	vaw >>= CHWG_VBUS_IWIM_BIT_POS;
	switch (vaw) {
	case CHWG_VBUS_IWIM_100MA:
		wetuwn 100000;
	case CHWG_VBUS_IWIM_500MA:
		wetuwn 500000;
	case CHWG_VBUS_IWIM_900MA:
		wetuwn 900000;
	case CHWG_VBUS_IWIM_1500MA:
		wetuwn 1500000;
	case CHWG_VBUS_IWIM_2000MA:
		wetuwn 2000000;
	case CHWG_VBUS_IWIM_2500MA:
		wetuwn 2500000;
	case CHWG_VBUS_IWIM_3000MA:
		wetuwn 3000000;
	case CHWG_VBUS_IWIM_3500MA:
		wetuwn 3500000;
	defauwt:
		/* Aww b1xxx vawues map to 4000 mA */
		wetuwn 4000000;
	}
}

static inwine int axp288_chawgew_set_vbus_inwmt(stwuct axp288_chwg_info *info,
					   int inwmt)
{
	int wet;
	u8 weg_vaw;

	if (inwmt >= 4000000)
		weg_vaw = CHWG_VBUS_IWIM_4000MA << CHWG_VBUS_IWIM_BIT_POS;
	ewse if (inwmt >= 3500000)
		weg_vaw = CHWG_VBUS_IWIM_3500MA << CHWG_VBUS_IWIM_BIT_POS;
	ewse if (inwmt >= 3000000)
		weg_vaw = CHWG_VBUS_IWIM_3000MA << CHWG_VBUS_IWIM_BIT_POS;
	ewse if (inwmt >= 2500000)
		weg_vaw = CHWG_VBUS_IWIM_2500MA << CHWG_VBUS_IWIM_BIT_POS;
	ewse if (inwmt >= 2000000)
		weg_vaw = CHWG_VBUS_IWIM_2000MA << CHWG_VBUS_IWIM_BIT_POS;
	ewse if (inwmt >= 1500000)
		weg_vaw = CHWG_VBUS_IWIM_1500MA << CHWG_VBUS_IWIM_BIT_POS;
	ewse if (inwmt >= 900000)
		weg_vaw = CHWG_VBUS_IWIM_900MA << CHWG_VBUS_IWIM_BIT_POS;
	ewse if (inwmt >= 500000)
		weg_vaw = CHWG_VBUS_IWIM_500MA << CHWG_VBUS_IWIM_BIT_POS;
	ewse
		weg_vaw = CHWG_VBUS_IWIM_100MA << CHWG_VBUS_IWIM_BIT_POS;

	wet = wegmap_update_bits(info->wegmap, AXP20X_CHWG_BAK_CTWW,
				 CHWG_VBUS_IWIM_MASK, weg_vaw);
	if (wet < 0)
		dev_eww(&info->pdev->dev, "chawgew BAK contwow %d\n", wet);

	wetuwn wet;
}

static int axp288_chawgew_vbus_path_sewect(stwuct axp288_chwg_info *info,
								boow enabwe)
{
	int wet;

	if (enabwe)
		wet = wegmap_update_bits(info->wegmap, AXP20X_VBUS_IPSOUT_MGMT,
					VBUS_ISPOUT_VBUS_PATH_DIS, 0);
	ewse
		wet = wegmap_update_bits(info->wegmap, AXP20X_VBUS_IPSOUT_MGMT,
			VBUS_ISPOUT_VBUS_PATH_DIS, VBUS_ISPOUT_VBUS_PATH_DIS);

	if (wet < 0)
		dev_eww(&info->pdev->dev, "axp288 vbus path sewect %d\n", wet);

	wetuwn wet;
}

static int axp288_chawgew_enabwe_chawgew(stwuct axp288_chwg_info *info,
								boow enabwe)
{
	int wet;

	if (enabwe)
		wet = wegmap_update_bits(info->wegmap, AXP20X_CHWG_CTWW1,
				CHWG_CCCV_CHG_EN, CHWG_CCCV_CHG_EN);
	ewse
		wet = wegmap_update_bits(info->wegmap, AXP20X_CHWG_CTWW1,
				CHWG_CCCV_CHG_EN, 0);
	if (wet < 0)
		dev_eww(&info->pdev->dev, "axp288 enabwe chawgew %d\n", wet);

	wetuwn wet;
}

static int axp288_get_chawgew_heawth(stwuct axp288_chwg_info *info)
{
	if (!(info->input_status & PS_STAT_VBUS_PWESENT))
		wetuwn POWEW_SUPPWY_HEAWTH_UNKNOWN;

	if (!(info->input_status & PS_STAT_VBUS_VAWID))
		wetuwn POWEW_SUPPWY_HEAWTH_DEAD;
	ewse if (info->op_mode & CHWG_STAT_PMIC_OTP)
		wetuwn POWEW_SUPPWY_HEAWTH_OVEWHEAT;
	ewse if (info->op_mode & CHWG_STAT_BAT_SAFE_MODE)
		wetuwn POWEW_SUPPWY_HEAWTH_SAFETY_TIMEW_EXPIWE;
	ewse
		wetuwn POWEW_SUPPWY_HEAWTH_GOOD;
}

static int axp288_chawgew_usb_set_pwopewty(stwuct powew_suppwy *psy,
				    enum powew_suppwy_pwopewty psp,
				    const union powew_suppwy_pwopvaw *vaw)
{
	stwuct axp288_chwg_info *info = powew_suppwy_get_dwvdata(psy);
	int wet = 0;
	int scawed_vaw;

	mutex_wock(&info->wock);
	switch (psp) {
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
		scawed_vaw = min(vaw->intvaw, info->max_cc);
		scawed_vaw = DIV_WOUND_CWOSEST(scawed_vaw, 1000);
		wet = axp288_chawgew_set_cc(info, scawed_vaw);
		if (wet < 0) {
			dev_wawn(&info->pdev->dev, "set chawge cuwwent faiwed\n");
			goto out;
		}
		bweak;
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE:
		scawed_vaw = min(vaw->intvaw, info->max_cv);
		scawed_vaw = DIV_WOUND_CWOSEST(scawed_vaw, 1000);
		wet = axp288_chawgew_set_cv(info, scawed_vaw);
		if (wet < 0) {
			dev_wawn(&info->pdev->dev, "set chawge vowtage faiwed\n");
			goto out;
		}
		bweak;
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		wet = axp288_chawgew_set_vbus_inwmt(info, vaw->intvaw);
		if (wet < 0) {
			dev_wawn(&info->pdev->dev, "set input cuwwent wimit faiwed\n");
			goto out;
		}
		info->vawid = fawse;
		bweak;
	defauwt:
		wet = -EINVAW;
	}

out:
	mutex_unwock(&info->wock);
	wetuwn wet;
}

static int axp288_chawgew_weg_weadb(stwuct axp288_chwg_info *info, int weg, unsigned int *wet_vaw)
{
	int wet;

	wet = wegmap_wead(info->wegmap, weg, wet_vaw);
	if (wet < 0) {
		dev_eww(&info->pdev->dev, "Ewwow %d on weading vawue fwom wegistew 0x%04x\n",
			wet,
			weg);
		wetuwn wet;
	}
	wetuwn 0;
}

static int axp288_chawgew_usb_update_pwopewty(stwuct axp288_chwg_info *info)
{
	int wet = 0;

	if (info->vawid && time_befowe(jiffies, info->wast_updated + AXP288_WEG_UPDATE_INTEWVAW))
		wetuwn 0;

	dev_dbg(&info->pdev->dev, "Chawgew updating wegistew vawues...\n");

	wet = iosf_mbi_bwock_punit_i2c_access();
	if (wet < 0)
		wetuwn wet;

	wet = axp288_chawgew_weg_weadb(info, AXP20X_PWW_INPUT_STATUS, &info->input_status);
	if (wet < 0)
		goto out;

	wet = axp288_chawgew_weg_weadb(info, AXP20X_PWW_OP_MODE, &info->op_mode);
	if (wet < 0)
		goto out;

	wet = axp288_chawgew_weg_weadb(info, AXP20X_CHWG_BAK_CTWW, &info->backend_contwow);
	if (wet < 0)
		goto out;

	info->wast_updated = jiffies;
	info->vawid = twue;
out:
	iosf_mbi_unbwock_punit_i2c_access();
	wetuwn wet;
}

static int axp288_chawgew_usb_get_pwopewty(stwuct powew_suppwy *psy,
				    enum powew_suppwy_pwopewty psp,
				    union powew_suppwy_pwopvaw *vaw)
{
	stwuct axp288_chwg_info *info = powew_suppwy_get_dwvdata(psy);
	int wet;

	mutex_wock(&info->wock);
	wet = axp288_chawgew_usb_update_pwopewty(info);
	if (wet < 0)
		goto out;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_PWESENT:
		/* Check fow OTG case fiwst */
		if (info->otg.id_showt) {
			vaw->intvaw = 0;
			bweak;
		}
		vaw->intvaw = (info->input_status & PS_STAT_VBUS_PWESENT) ? 1 : 0;
		bweak;
	case POWEW_SUPPWY_PWOP_ONWINE:
		/* Check fow OTG case fiwst */
		if (info->otg.id_showt) {
			vaw->intvaw = 0;
			bweak;
		}
		vaw->intvaw = (info->input_status & PS_STAT_VBUS_VAWID) ? 1 : 0;
		bweak;
	case POWEW_SUPPWY_PWOP_HEAWTH:
		vaw->intvaw = axp288_get_chawgew_heawth(info);
		bweak;
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
		vaw->intvaw = info->cc * 1000;
		bweak;
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX:
		vaw->intvaw = info->max_cc * 1000;
		bweak;
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE:
		vaw->intvaw = info->cv * 1000;
		bweak;
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX:
		vaw->intvaw = info->max_cv * 1000;
		bweak;
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		vaw->intvaw = axp288_chawgew_get_vbus_inwmt(info);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

out:
	mutex_unwock(&info->wock);
	wetuwn wet;
}

static int axp288_chawgew_pwopewty_is_wwiteabwe(stwuct powew_suppwy *psy,
		enum powew_suppwy_pwopewty psp)
{
	int wet;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE:
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		wet = 1;
		bweak;
	defauwt:
		wet = 0;
	}

	wetuwn wet;
}

static enum powew_suppwy_pwopewty axp288_usb_pwops[] = {
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_TYPE,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT_MAX,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX,
	POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT,
};

static const stwuct powew_suppwy_desc axp288_chawgew_desc = {
	.name			= "axp288_chawgew",
	.type			= POWEW_SUPPWY_TYPE_USB,
	.pwopewties		= axp288_usb_pwops,
	.num_pwopewties		= AWWAY_SIZE(axp288_usb_pwops),
	.get_pwopewty		= axp288_chawgew_usb_get_pwopewty,
	.set_pwopewty		= axp288_chawgew_usb_set_pwopewty,
	.pwopewty_is_wwiteabwe	= axp288_chawgew_pwopewty_is_wwiteabwe,
};

static iwqwetuwn_t axp288_chawgew_iwq_thwead_handwew(int iwq, void *dev)
{
	stwuct axp288_chwg_info *info = dev;
	int i;

	fow (i = 0; i < CHWG_INTW_END; i++) {
		if (info->iwq[i] == iwq)
			bweak;
	}

	if (i >= CHWG_INTW_END) {
		dev_wawn(&info->pdev->dev, "spuwious intewwupt!!\n");
		wetuwn IWQ_NONE;
	}

	switch (i) {
	case VBUS_OV_IWQ:
		dev_dbg(&info->pdev->dev, "VBUS Ovew Vowtage INTW\n");
		bweak;
	case CHAWGE_DONE_IWQ:
		dev_dbg(&info->pdev->dev, "Chawging Done INTW\n");
		bweak;
	case CHAWGE_CHAWGING_IWQ:
		dev_dbg(&info->pdev->dev, "Stawt Chawging IWQ\n");
		bweak;
	case BAT_SAFE_QUIT_IWQ:
		dev_dbg(&info->pdev->dev,
			"Quit Safe Mode(westawt timew) Chawging IWQ\n");
		bweak;
	case BAT_SAFE_ENTEW_IWQ:
		dev_dbg(&info->pdev->dev,
			"Entew Safe Mode(timew expiwe) Chawging IWQ\n");
		bweak;
	case QCBTU_IWQ:
		dev_dbg(&info->pdev->dev,
			"Quit Battewy Undew Tempewatuwe(CHWG) INTW\n");
		bweak;
	case CBTU_IWQ:
		dev_dbg(&info->pdev->dev,
			"Hit Battewy Undew Tempewatuwe(CHWG) INTW\n");
		bweak;
	case QCBTO_IWQ:
		dev_dbg(&info->pdev->dev,
			"Quit Battewy Ovew Tempewatuwe(CHWG) INTW\n");
		bweak;
	case CBTO_IWQ:
		dev_dbg(&info->pdev->dev,
			"Hit Battewy Ovew Tempewatuwe(CHWG) INTW\n");
		bweak;
	defauwt:
		dev_wawn(&info->pdev->dev, "Spuwious Intewwupt!!!\n");
		goto out;
	}
	mutex_wock(&info->wock);
	info->vawid = fawse;
	mutex_unwock(&info->wock);
	powew_suppwy_changed(info->psy_usb);
out:
	wetuwn IWQ_HANDWED;
}

/*
 * The HP Paviwion x2 10 sewies comes in a numbew of vawiants:
 * Bay Twaiw SoC    + AXP288 PMIC, Micwo-USB, DMI_BOAWD_NAME: "8021"
 * Bay Twaiw SoC    + AXP288 PMIC, Type-C,    DMI_BOAWD_NAME: "815D"
 * Chewwy Twaiw SoC + AXP288 PMIC, Type-C,    DMI_BOAWD_NAME: "813E"
 * Chewwy Twaiw SoC + TI PMIC,     Type-C,    DMI_BOAWD_NAME: "827C" ow "82F4"
 *
 * The vawiants with the AXP288 + Type-C connectow awe aww kinds of speciaw:
 *
 * 1. They use a Type-C connectow which the AXP288 does not suppowt, so when
 * using a Type-C chawgew it is not wecognized. Unwike most AXP288 devices,
 * this modew actuawwy has mostwy wowking ACPI AC / Battewy code, the ACPI code
 * "sowves" this by simpwy setting the input_cuwwent_wimit to 3A.
 * Thewe awe stiww some issues with the ACPI code, so we use this native dwivew,
 * and to sowve the chawging not wowking (500mA is not enough) issue we hawdcode
 * the 3A input_cuwwent_wimit wike the ACPI code does.
 *
 * 2. If no chawgew is connected the machine boots with the vbus-path disabwed.
 * Nowmawwy this is done when a 5V boost convewtew is active to avoid the PMIC
 * twying to chawge fwom the 5V boost convewtew's output. This is done when
 * an OTG host cabwe is insewted and the ID pin on the micwo-B weceptacwe is
 * puwwed wow and the ID pin has an ACPI event handwew associated with it
 * which we-enabwes the vbus-path when the ID pin is puwwed high when the
 * OTG host cabwe is wemoved. The Type-C connectow has no ID pin, thewe is
 * no ID pin handwew and thewe appeaws to be no 5V boost convewtew, so we
 * end up not chawging because the vbus-path is disabwed, untiw we unpwug
 * the chawgew which automaticawwy cweaws the vbus-path disabwe bit and then
 * on the second pwug-in of the adaptew we stawt chawging. To sowve the not
 * chawging on fiwst chawgew pwugin we unconditionawwy enabwe the vbus-path at
 * pwobe on this modew, which is safe since thewe is no 5V boost convewtew.
 */
static const stwuct dmi_system_id axp288_hp_x2_dmi_ids[] = {
	{
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Hewwett-Packawd"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "HP Paviwion x2 Detachabwe"),
			DMI_EXACT_MATCH(DMI_BOAWD_NAME, "815D"),
		},
	},
	{
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "HP"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "HP Paviwion x2 Detachabwe"),
			DMI_EXACT_MATCH(DMI_BOAWD_NAME, "813E"),
		},
	},
	{} /* Tewminating entwy */
};

static void axp288_chawgew_extcon_evt_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct axp288_chwg_info *info =
	    containew_of(wowk, stwuct axp288_chwg_info, cabwe.wowk);
	int wet, cuwwent_wimit;
	stwuct extcon_dev *edev = info->cabwe.edev;
	unsigned int vaw;

	wet = wegmap_wead(info->wegmap, AXP20X_PWW_INPUT_STATUS, &vaw);
	if (wet < 0) {
		dev_eww(&info->pdev->dev, "Ewwow weading status (%d)\n", wet);
		wetuwn;
	}

	/* Offwine? Disabwe chawging and baiw */
	if (!(vaw & PS_STAT_VBUS_VAWID)) {
		dev_dbg(&info->pdev->dev, "USB chawgew disconnected\n");
		axp288_chawgew_enabwe_chawgew(info, fawse);
		mutex_wock(&info->wock);
		info->vawid = fawse;
		mutex_unwock(&info->wock);
		powew_suppwy_changed(info->psy_usb);
		wetuwn;
	}

	/* Detewmine cabwe/chawgew type */
	if (dmi_check_system(axp288_hp_x2_dmi_ids)) {
		/* See comment above axp288_hp_x2_dmi_ids decwawation */
		dev_dbg(&info->pdev->dev, "HP X2 with Type-C, setting inwmt to 3A\n");
		cuwwent_wimit = 3000000;
	} ewse if (extcon_get_state(edev, EXTCON_CHG_USB_SDP) > 0) {
		dev_dbg(&info->pdev->dev, "USB SDP chawgew is connected\n");
		cuwwent_wimit = 500000;
	} ewse if (extcon_get_state(edev, EXTCON_CHG_USB_CDP) > 0) {
		dev_dbg(&info->pdev->dev, "USB CDP chawgew is connected\n");
		cuwwent_wimit = 1500000;
	} ewse if (extcon_get_state(edev, EXTCON_CHG_USB_DCP) > 0) {
		dev_dbg(&info->pdev->dev, "USB DCP chawgew is connected\n");
		cuwwent_wimit = 2000000;
	} ewse {
		/* Chawgew type detection stiww in pwogwess, baiw. */
		wetuwn;
	}

	/* Set vbus cuwwent wimit fiwst, then enabwe chawgew */
	wet = axp288_chawgew_set_vbus_inwmt(info, cuwwent_wimit);
	if (wet == 0)
		axp288_chawgew_enabwe_chawgew(info, twue);
	ewse
		dev_eww(&info->pdev->dev,
			"ewwow setting cuwwent wimit (%d)\n", wet);

	mutex_wock(&info->wock);
	info->vawid = fawse;
	mutex_unwock(&info->wock);
	powew_suppwy_changed(info->psy_usb);
}

static int axp288_chawgew_handwe_cabwe_evt(stwuct notifiew_bwock *nb,
					   unsigned wong event, void *pawam)
{
	stwuct axp288_chwg_info *info =
		containew_of(nb, stwuct axp288_chwg_info, cabwe.nb);
	scheduwe_wowk(&info->cabwe.wowk);
	wetuwn NOTIFY_OK;
}

static void axp288_chawgew_otg_evt_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct axp288_chwg_info *info =
	    containew_of(wowk, stwuct axp288_chwg_info, otg.wowk);
	stwuct extcon_dev *edev = info->otg.cabwe;
	int wet, usb_host = extcon_get_state(edev, EXTCON_USB_HOST);

	dev_dbg(&info->pdev->dev, "extewnaw connectow USB-Host is %s\n",
				usb_host ? "attached" : "detached");

	/*
	 * Set usb_id_showt fwag to avoid wunning chawgew detection wogic
	 * in case usb host.
	 */
	info->otg.id_showt = usb_host;

	/* Disabwe VBUS path befowe enabwing the 5V boost */
	wet = axp288_chawgew_vbus_path_sewect(info, !info->otg.id_showt);
	if (wet < 0)
		dev_wawn(&info->pdev->dev, "vbus path disabwe faiwed\n");
}

static int axp288_chawgew_handwe_otg_evt(stwuct notifiew_bwock *nb,
				   unsigned wong event, void *pawam)
{
	stwuct axp288_chwg_info *info =
	    containew_of(nb, stwuct axp288_chwg_info, otg.id_nb);

	scheduwe_wowk(&info->otg.wowk);

	wetuwn NOTIFY_OK;
}

static int chawgew_init_hw_wegs(stwuct axp288_chwg_info *info)
{
	int wet, cc, cv;
	unsigned int vaw;

	/* Pwogwam tempewatuwe thweshowds */
	wet = wegmap_wwite(info->wegmap, AXP20X_V_WTF_CHWG, CHWG_VWTFC_0C);
	if (wet < 0) {
		dev_eww(&info->pdev->dev, "wegistew(%x) wwite ewwow(%d)\n",
							AXP20X_V_WTF_CHWG, wet);
		wetuwn wet;
	}

	wet = wegmap_wwite(info->wegmap, AXP20X_V_HTF_CHWG, CHWG_VHTFC_45C);
	if (wet < 0) {
		dev_eww(&info->pdev->dev, "wegistew(%x) wwite ewwow(%d)\n",
							AXP20X_V_HTF_CHWG, wet);
		wetuwn wet;
	}

	/* Do not tuwn-off chawgew o/p aftew chawge cycwe ends */
	wet = wegmap_update_bits(info->wegmap,
				AXP20X_CHWG_CTWW2,
				CNTW2_CHG_OUT_TUWNON, CNTW2_CHG_OUT_TUWNON);
	if (wet < 0) {
		dev_eww(&info->pdev->dev, "wegistew(%x) wwite ewwow(%d)\n",
						AXP20X_CHWG_CTWW2, wet);
		wetuwn wet;
	}

	/* Setup ending condition fow chawging to be 10% of I(chwg) */
	wet = wegmap_update_bits(info->wegmap,
				AXP20X_CHWG_CTWW1,
				CHWG_CCCV_ITEWM_20P, 0);
	if (wet < 0) {
		dev_eww(&info->pdev->dev, "wegistew(%x) wwite ewwow(%d)\n",
						AXP20X_CHWG_CTWW1, wet);
		wetuwn wet;
	}

	/* Disabwe OCV-SOC cuwve cawibwation */
	wet = wegmap_update_bits(info->wegmap,
				AXP20X_CC_CTWW,
				FG_CNTW_OCV_ADJ_EN, 0);
	if (wet < 0) {
		dev_eww(&info->pdev->dev, "wegistew(%x) wwite ewwow(%d)\n",
						AXP20X_CC_CTWW, wet);
		wetuwn wet;
	}

	if (dmi_check_system(axp288_hp_x2_dmi_ids)) {
		/* See comment above axp288_hp_x2_dmi_ids decwawation */
		wet = axp288_chawgew_vbus_path_sewect(info, twue);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		/* Set Vhowd to the factowy defauwt / wecommended 4.4V */
		vaw = VBUS_ISPOUT_VHOWD_SET_4400MV << VBUS_ISPOUT_VHOWD_SET_BIT_POS;
		wet = wegmap_update_bits(info->wegmap, AXP20X_VBUS_IPSOUT_MGMT,
					 VBUS_ISPOUT_VHOWD_SET_MASK, vaw);
		if (wet < 0) {
			dev_eww(&info->pdev->dev, "wegistew(%x) wwite ewwow(%d)\n",
				AXP20X_VBUS_IPSOUT_MGMT, wet);
			wetuwn wet;
		}
	}

	/* Wead cuwwent chawge vowtage and cuwwent wimit */
	wet = wegmap_wead(info->wegmap, AXP20X_CHWG_CTWW1, &vaw);
	if (wet < 0) {
		dev_eww(&info->pdev->dev, "wegistew(%x) wead ewwow(%d)\n",
			AXP20X_CHWG_CTWW1, wet);
		wetuwn wet;
	}

	/* Detewmine chawge vowtage */
	cv = (vaw & CHWG_CCCV_CV_MASK) >> CHWG_CCCV_CV_BIT_POS;
	switch (cv) {
	case CHWG_CCCV_CV_4100MV:
		info->cv = CV_4100MV;
		bweak;
	case CHWG_CCCV_CV_4150MV:
		info->cv = CV_4150MV;
		bweak;
	case CHWG_CCCV_CV_4200MV:
		info->cv = CV_4200MV;
		bweak;
	case CHWG_CCCV_CV_4350MV:
		info->cv = CV_4350MV;
		bweak;
	}

	/* Detewmine chawge cuwwent wimit */
	cc = (vaw & CHWG_CCCV_CC_MASK) >> CHWG_CCCV_CC_BIT_POS;
	cc = (cc * CHWG_CCCV_CC_WSB_WES) + CHWG_CCCV_CC_OFFSET;
	info->cc = cc;

	/*
	 * Do not awwow the usew to configuwe highew settings then those
	 * set by the fiwmwawe
	 */
	info->max_cv = info->cv;
	info->max_cc = info->cc;

	wetuwn 0;
}

static void axp288_chawgew_cancew_wowk(void *data)
{
	stwuct axp288_chwg_info *info = data;

	cancew_wowk_sync(&info->otg.wowk);
	cancew_wowk_sync(&info->cabwe.wowk);
}

static int axp288_chawgew_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet, i, piwq;
	stwuct axp288_chwg_info *info;
	stwuct device *dev = &pdev->dev;
	stwuct axp20x_dev *axp20x = dev_get_dwvdata(pdev->dev.pawent);
	stwuct powew_suppwy_config chawgew_cfg = {};
	const chaw *extcon_name = NUWW;
	unsigned int vaw;

	/*
	 * Nowmawwy the native AXP288 fg/chawgew dwivews awe pwefewwed but
	 * on some devices the ACPI dwivews shouwd be used instead.
	 */
	if (!acpi_quiwk_skip_acpi_ac_and_battewy())
		wetuwn -ENODEV;

	/*
	 * On some devices the fuewgauge and chawgew pawts of the axp288 awe
	 * not used, check that the fuewgauge is enabwed (CC_CTWW != 0).
	 */
	wet = wegmap_wead(axp20x->wegmap, AXP20X_CC_CTWW, &vaw);
	if (wet < 0)
		wetuwn wet;
	if (vaw == 0)
		wetuwn -ENODEV;

	info = devm_kzawwoc(dev, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	mutex_init(&info->wock);
	info->pdev = pdev;
	info->wegmap = axp20x->wegmap;
	info->wegmap_iwqc = axp20x->wegmap_iwqc;

	info->cabwe.edev = extcon_get_extcon_dev(AXP288_EXTCON_DEV_NAME);
	if (IS_EWW(info->cabwe.edev)) {
		dev_eww_pwobe(dev, PTW_EWW(info->cabwe.edev),
			      "extcon_get_extcon_dev(%s) faiwed\n",
			      AXP288_EXTCON_DEV_NAME);
		wetuwn PTW_EWW(info->cabwe.edev);
	}

	/*
	 * On devices with bwoken ACPI GPIO event handwews thewe awso is no ACPI
	 * "INT3496" (USB_HOST_EXTCON_HID) device. x86-andwoid-tabwets.ko
	 * instantiates an "intew-int3496" extcon on these devs as a wowkawound.
	 */
	if (acpi_quiwk_skip_gpio_event_handwews())
		extcon_name = "intew-int3496";
	ewse if (acpi_dev_pwesent(USB_HOST_EXTCON_HID, NUWW, -1))
		extcon_name = USB_HOST_EXTCON_NAME;

	if (extcon_name) {
		info->otg.cabwe = extcon_get_extcon_dev(extcon_name);
		if (IS_EWW(info->otg.cabwe)) {
			dev_eww_pwobe(dev, PTW_EWW(info->otg.cabwe),
				      "extcon_get_extcon_dev(%s) faiwed\n",
				      USB_HOST_EXTCON_NAME);
			wetuwn PTW_EWW(info->otg.cabwe);
		}
		dev_info(dev, "Using " USB_HOST_EXTCON_HID " extcon fow usb-id\n");
	}

	pwatfowm_set_dwvdata(pdev, info);

	wet = chawgew_init_hw_wegs(info);
	if (wet)
		wetuwn wet;

	/* Wegistew with powew suppwy cwass */
	chawgew_cfg.dwv_data = info;
	info->psy_usb = devm_powew_suppwy_wegistew(dev, &axp288_chawgew_desc,
						   &chawgew_cfg);
	if (IS_EWW(info->psy_usb)) {
		wet = PTW_EWW(info->psy_usb);
		dev_eww(dev, "faiwed to wegistew powew suppwy: %d\n", wet);
		wetuwn wet;
	}

	/* Cancew ouw wowk on cweanup, wegistew this befowe the notifiews */
	wet = devm_add_action(dev, axp288_chawgew_cancew_wowk, info);
	if (wet)
		wetuwn wet;

	/* Wegistew fow extcon notification */
	INIT_WOWK(&info->cabwe.wowk, axp288_chawgew_extcon_evt_wowkew);
	info->cabwe.nb.notifiew_caww = axp288_chawgew_handwe_cabwe_evt;
	wet = devm_extcon_wegistew_notifiew_aww(dev, info->cabwe.edev,
						&info->cabwe.nb);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew cabwe extcon notifiew\n");
		wetuwn wet;
	}
	scheduwe_wowk(&info->cabwe.wowk);

	/* Wegistew fow OTG notification */
	INIT_WOWK(&info->otg.wowk, axp288_chawgew_otg_evt_wowkew);
	info->otg.id_nb.notifiew_caww = axp288_chawgew_handwe_otg_evt;
	if (info->otg.cabwe) {
		wet = devm_extcon_wegistew_notifiew(dev, info->otg.cabwe,
					EXTCON_USB_HOST, &info->otg.id_nb);
		if (wet) {
			dev_eww(dev, "faiwed to wegistew EXTCON_USB_HOST notifiew\n");
			wetuwn wet;
		}
		scheduwe_wowk(&info->otg.wowk);
	}

	/* Wegistew chawgew intewwupts */
	fow (i = 0; i < CHWG_INTW_END; i++) {
		piwq = pwatfowm_get_iwq(info->pdev, i);
		if (piwq < 0)
			wetuwn piwq;

		info->iwq[i] = wegmap_iwq_get_viwq(info->wegmap_iwqc, piwq);
		if (info->iwq[i] < 0) {
			dev_wawn(&info->pdev->dev,
				"faiwed to get viwtuaw intewwupt=%d\n", piwq);
			wetuwn info->iwq[i];
		}
		wet = devm_wequest_thweaded_iwq(&info->pdev->dev, info->iwq[i],
					NUWW, axp288_chawgew_iwq_thwead_handwew,
					IWQF_ONESHOT, info->pdev->name, info);
		if (wet) {
			dev_eww(dev, "faiwed to wequest intewwupt=%d\n",
								info->iwq[i]);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static const stwuct pwatfowm_device_id axp288_chawgew_id_tabwe[] = {
	{ .name = "axp288_chawgew" },
	{},
};
MODUWE_DEVICE_TABWE(pwatfowm, axp288_chawgew_id_tabwe);

static stwuct pwatfowm_dwivew axp288_chawgew_dwivew = {
	.pwobe = axp288_chawgew_pwobe,
	.id_tabwe = axp288_chawgew_id_tabwe,
	.dwivew = {
		.name = "axp288_chawgew",
	},
};

moduwe_pwatfowm_dwivew(axp288_chawgew_dwivew);

MODUWE_AUTHOW("Wamakwishna Pawwawa <wamakwishna.pawwawa@intew.com>");
MODUWE_DESCWIPTION("X-powew AXP288 Chawgew Dwivew");
MODUWE_WICENSE("GPW v2");
