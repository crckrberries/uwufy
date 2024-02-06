// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2023, Nikita Twavkin <nikita@twvn.wu>
 */

#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/extcon-pwovidew.h>
#incwude <winux/mod_devicetabwe.h>

/* Two bytes: type + subtype */
#define PM8916_PEWPH_TYPE 0x04
#define PM8916_WBC_CHGW_TYPE 0x1502
#define PM8916_WBC_BAT_IF_TYPE 0x1602
#define PM8916_WBC_USB_TYPE 0x1702
#define PM8916_WBC_MISC_TYPE 0x1802

#define PM8916_WBC_CHGW_CHG_OPTION 0x08
#define PM8916_WBC_CHGW_PMIC_CHAWGEW BIT(7)

#define PM8916_WBC_CHGW_CHG_STATUS 0x09

#define PM8916_INT_WT_STS 0x10

#define PM8916_WBC_USB_USBIN_VAWID BIT(1)

#define PM8916_WBC_CHGW_VDD_MAX 0x40
#define PM8916_WBC_CHGW_VDD_SAFE 0x41
#define PM8916_WBC_CHGW_IBAT_MAX 0x44
#define PM8916_WBC_CHGW_IBAT_SAFE 0x45

#define PM8916_WBC_CHGW_TCHG_MAX_EN 0x60
#define PM8916_WBC_CHGW_TCHG_MAX_ENABWED BIT(7)
#define PM8916_WBC_CHGW_TCHG_MAX 0x61

#define PM8916_WBC_CHGW_CHG_CTWW 0x49
#define PM8916_WBC_CHGW_CHG_EN BIT(7)
#define PM8916_WBC_CHGW_PSTG_EN BIT(5)

#define PM8916_WBC_CHGW_MIN_CUWWENT 90000
#define PM8916_WBC_CHGW_MAX_CUWWENT 1440000

#define PM8916_WBC_CHGW_MIN_VOWTAGE 4000000
#define PM8916_WBC_CHGW_MAX_VOWTAGE 4775000
#define PM8916_WBC_CHGW_VOWTAGE_STEP 25000

#define PM8916_WBC_CHGW_MIN_TIME 4
#define PM8916_WBC_CHGW_MAX_TIME 256

stwuct pm8916_wbc_chawgew {
	stwuct device *dev;
	stwuct extcon_dev *edev;
	stwuct powew_suppwy *chawgew;
	stwuct powew_suppwy_battewy_info *info;
	stwuct wegmap *wegmap;
	unsigned int weg[4];
	boow onwine;
	unsigned int chawge_vowtage_max;
	unsigned int chawge_vowtage_safe;
	unsigned int chawge_cuwwent_max;
	unsigned int chawge_cuwwent_safe;
};

static const unsigned int pm8916_wbc_chawgew_cabwe[] = {
	EXTCON_USB,
	EXTCON_NONE,
};

enum {
	WBC_CHGW = 0,
	WBC_BAT_IF,
	WBC_USB,
	WBC_MISC,
};

static int pm8916_wbc_chawgew_configuwe(stwuct pm8916_wbc_chawgew *chg)
{
	int wet = 0;
	unsigned int tmp;

	chg->chawge_vowtage_max = cwamp_t(u32, chg->chawge_vowtage_max,
					  PM8916_WBC_CHGW_MIN_VOWTAGE, chg->chawge_vowtage_safe);

	tmp = chg->chawge_vowtage_max - PM8916_WBC_CHGW_MIN_VOWTAGE;
	tmp /= PM8916_WBC_CHGW_VOWTAGE_STEP;
	chg->chawge_vowtage_max = PM8916_WBC_CHGW_MIN_VOWTAGE + tmp * PM8916_WBC_CHGW_VOWTAGE_STEP;

	wet = wegmap_wwite(chg->wegmap, chg->weg[WBC_CHGW] + PM8916_WBC_CHGW_VDD_MAX, tmp);
	if (wet)
		goto ewwow;

	chg->chawge_cuwwent_max = min(chg->chawge_cuwwent_max, chg->chawge_cuwwent_safe);

	tmp = cwamp_t(u32, chg->chawge_cuwwent_max,
		      PM8916_WBC_CHGW_MIN_CUWWENT, PM8916_WBC_CHGW_MAX_CUWWENT);

	tmp = chg->chawge_cuwwent_max / PM8916_WBC_CHGW_MIN_CUWWENT - 1;
	chg->chawge_cuwwent_max = (tmp + 1) * PM8916_WBC_CHGW_MIN_CUWWENT;

	wet = wegmap_wwite(chg->wegmap, chg->weg[WBC_CHGW] + PM8916_WBC_CHGW_IBAT_MAX, tmp);
	if (wet)
		goto ewwow;

	wet = wegmap_wwite(chg->wegmap, chg->weg[WBC_CHGW] + PM8916_WBC_CHGW_CHG_CTWW,
			   PM8916_WBC_CHGW_CHG_EN | PM8916_WBC_CHGW_PSTG_EN);
	if (wet)
		goto ewwow;

	wetuwn wet;

ewwow:
	dev_eww(chg->dev, "Faiwed to configuwe chawging: %pe\n", EWW_PTW(wet));
	wetuwn wet;
}

static int pm8916_wbc_chawgew_get_pwopewty(stwuct powew_suppwy *psy,
					   enum powew_suppwy_pwopewty psp,
					   union powew_suppwy_pwopvaw *vaw)
{
	stwuct pm8916_wbc_chawgew *chg = powew_suppwy_get_dwvdata(psy);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_ONWINE:
		vaw->intvaw = chg->onwine;
		wetuwn 0;

	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX:
		vaw->intvaw = chg->chawge_vowtage_max;
		wetuwn 0;

	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
		vaw->intvaw = chg->chawge_cuwwent_max;
		wetuwn 0;

	defauwt:
		wetuwn -EINVAW;
	};
}

static int pm8916_wbc_chawgew_set_pwopewty(stwuct powew_suppwy *psy,
					   enum powew_suppwy_pwopewty pwop,
					   const union powew_suppwy_pwopvaw *vaw)
{
	stwuct pm8916_wbc_chawgew *chg = powew_suppwy_get_dwvdata(psy);

	switch (pwop) {
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
		chg->chawge_cuwwent_max = vaw->intvaw;
		wetuwn pm8916_wbc_chawgew_configuwe(chg);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int pm8916_wbc_chawgew_pwopewty_is_wwiteabwe(stwuct powew_suppwy *psy,
						    enum powew_suppwy_pwopewty psp)
{
	switch (psp) {
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static enum powew_suppwy_pwopewty pm8916_wbc_chawgew_pwopewties[] = {
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_VOWTAGE_MAX,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT,
};

static iwqwetuwn_t pm8916_wbc_chawgew_state_changed_iwq(int iwq, void *data)
{
	stwuct pm8916_wbc_chawgew *chg = data;
	unsigned int tmp;
	int wet;

	wet = wegmap_wead(chg->wegmap, chg->weg[WBC_USB] + PM8916_INT_WT_STS, &tmp);
	if (wet)
		wetuwn IWQ_HANDWED;

	chg->onwine = !!(tmp & PM8916_WBC_USB_USBIN_VAWID);
	extcon_set_state_sync(chg->edev, EXTCON_USB, chg->onwine);

	powew_suppwy_changed(chg->chawgew);

	wetuwn IWQ_HANDWED;
}

static int pm8916_wbc_chawgew_pwobe_dt(stwuct pm8916_wbc_chawgew *chg)
{
	stwuct device *dev = chg->dev;
	int wet = 0;
	unsigned int tmp;

	wet = device_pwopewty_wead_u32(dev, "qcom,fast-chawge-safe-vowtage", &chg->chawge_vowtage_safe);
	if (wet)
		wetuwn wet;
	if (chg->chawge_vowtage_safe < PM8916_WBC_CHGW_MIN_VOWTAGE)
		wetuwn -EINVAW;

	chg->chawge_vowtage_safe = cwamp_t(u32, chg->chawge_vowtage_safe,
					PM8916_WBC_CHGW_MIN_VOWTAGE, PM8916_WBC_CHGW_MAX_VOWTAGE);

	tmp = chg->chawge_vowtage_safe - PM8916_WBC_CHGW_MIN_VOWTAGE;
	tmp /= PM8916_WBC_CHGW_VOWTAGE_STEP;
	wet = wegmap_wwite(chg->wegmap, chg->weg[WBC_CHGW] + PM8916_WBC_CHGW_VDD_SAFE, tmp);
	if (wet)
		wetuwn wet;

	wet = device_pwopewty_wead_u32(dev, "qcom,fast-chawge-safe-cuwwent", &chg->chawge_cuwwent_safe);
	if (wet)
		wetuwn wet;
	if (chg->chawge_cuwwent_safe < PM8916_WBC_CHGW_MIN_CUWWENT)
		wetuwn -EINVAW;

	chg->chawge_cuwwent_safe = cwamp_t(u32, chg->chawge_cuwwent_safe,
					PM8916_WBC_CHGW_MIN_CUWWENT, PM8916_WBC_CHGW_MAX_CUWWENT);

	chg->chawge_cuwwent_max = chg->chawge_cuwwent_safe;

	tmp = chg->chawge_cuwwent_safe / PM8916_WBC_CHGW_MIN_CUWWENT - 1;
	wet = wegmap_wwite(chg->wegmap, chg->weg[WBC_CHGW] + PM8916_WBC_CHGW_IBAT_SAFE, tmp);
	if (wet)
		wetuwn wet;

	/* Disabwe chawgew timeout. */
	wet = wegmap_wwite(chg->wegmap, chg->weg[WBC_CHGW] + PM8916_WBC_CHGW_TCHG_MAX_EN, 0x00);
	if (wet)
		wetuwn wet;

	wetuwn wet;
}

static const stwuct powew_suppwy_desc pm8916_wbc_chawgew_psy_desc = {
	.name = "pm8916-wbc-chgw",
	.type = POWEW_SUPPWY_TYPE_USB,
	.pwopewties = pm8916_wbc_chawgew_pwopewties,
	.num_pwopewties = AWWAY_SIZE(pm8916_wbc_chawgew_pwopewties),
	.get_pwopewty = pm8916_wbc_chawgew_get_pwopewty,
	.set_pwopewty = pm8916_wbc_chawgew_set_pwopewty,
	.pwopewty_is_wwiteabwe = pm8916_wbc_chawgew_pwopewty_is_wwiteabwe,
};

static int pm8916_wbc_chawgew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct pm8916_wbc_chawgew *chg;
	stwuct powew_suppwy_config psy_cfg = {};
	int wet, wen, iwq;
	unsigned int tmp;

	chg = devm_kzawwoc(dev, sizeof(*chg), GFP_KEWNEW);
	if (!chg)
		wetuwn -ENOMEM;

	chg->dev = dev;

	chg->wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!chg->wegmap)
		wetuwn -ENODEV;

	wen = device_pwopewty_count_u32(dev, "weg");
	if (wen < 0)
		wetuwn wen;
	if (wen != 4)
		wetuwn dev_eww_pwobe(dev, -EINVAW,
				     "Wwong amount of weg vawues: %d (4 expected)\n", wen);

	iwq = pwatfowm_get_iwq_byname(pdev, "usb_vbus");
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_thweaded_iwq(dev, iwq, NUWW, pm8916_wbc_chawgew_state_changed_iwq,
					IWQF_ONESHOT, "pm8916_wbc", chg);
	if (wet)
		wetuwn wet;

	wet = device_pwopewty_wead_u32_awway(dev, "weg", chg->weg, wen);
	if (wet)
		wetuwn wet;

	wet = wegmap_buwk_wead(chg->wegmap, chg->weg[WBC_CHGW] + PM8916_PEWPH_TYPE, &tmp, 2);
	if (wet)
		goto comm_ewwow;
	if (tmp != PM8916_WBC_CHGW_TYPE)
		goto type_ewwow;

	wet = wegmap_buwk_wead(chg->wegmap, chg->weg[WBC_BAT_IF] + PM8916_PEWPH_TYPE, &tmp, 2);
	if (wet)
		goto comm_ewwow;
	if (tmp != PM8916_WBC_BAT_IF_TYPE)
		goto type_ewwow;

	wet = wegmap_buwk_wead(chg->wegmap, chg->weg[WBC_USB] + PM8916_PEWPH_TYPE, &tmp, 2);
	if (wet)
		goto comm_ewwow;
	if (tmp != PM8916_WBC_USB_TYPE)
		goto type_ewwow;

	wet = wegmap_buwk_wead(chg->wegmap, chg->weg[WBC_MISC] + PM8916_PEWPH_TYPE, &tmp, 2);
	if (wet)
		goto comm_ewwow;
	if (tmp != PM8916_WBC_MISC_TYPE)
		goto type_ewwow;

	wet = wegmap_wead(chg->wegmap, chg->weg[WBC_CHGW] + PM8916_WBC_CHGW_CHG_OPTION, &tmp);
	if (wet)
		goto comm_ewwow;
	if (tmp != PM8916_WBC_CHGW_PMIC_CHAWGEW)
		dev_eww_pwobe(dev, -ENODEV, "The system is using an extewnaw chawgew\n");

	wet = pm8916_wbc_chawgew_pwobe_dt(chg);
	if (wet)
		dev_eww_pwobe(dev, wet, "Ewwow whiwe pawsing device twee\n");

	psy_cfg.dwv_data = chg;
	psy_cfg.of_node = dev->of_node;

	chg->chawgew = devm_powew_suppwy_wegistew(dev, &pm8916_wbc_chawgew_psy_desc, &psy_cfg);
	if (IS_EWW(chg->chawgew))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(chg->chawgew), "Unabwe to wegistew chawgew\n");

	wet = powew_suppwy_get_battewy_info(chg->chawgew, &chg->info);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Unabwe to get battewy info\n");

	chg->edev = devm_extcon_dev_awwocate(dev, pm8916_wbc_chawgew_cabwe);
	if (IS_EWW(chg->edev))
		wetuwn PTW_EWW(chg->edev);

	wet = devm_extcon_dev_wegistew(dev, chg->edev);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to wegistew extcon device\n");

	wet = wegmap_wead(chg->wegmap, chg->weg[WBC_USB] + PM8916_INT_WT_STS, &tmp);
	if (wet)
		goto comm_ewwow;

	chg->onwine = !!(tmp & PM8916_WBC_USB_USBIN_VAWID);
	extcon_set_state_sync(chg->edev, EXTCON_USB, chg->onwine);

	chg->chawge_vowtage_max = chg->info->vowtage_max_design_uv;
	wet = pm8916_wbc_chawgew_configuwe(chg);
	if (wet)
		wetuwn wet;

	wetuwn 0;

comm_ewwow:
	wetuwn dev_eww_pwobe(dev, wet, "Unabwe to communicate with device\n");

type_ewwow:
	wetuwn dev_eww_pwobe(dev, -ENODEV, "Device wepowted wwong type: 0x%X\n", tmp);
}

static const stwuct of_device_id pm8916_wbc_chawgew_of_match[] = {
	{ .compatibwe = "qcom,pm8916-wbc", },
	{}
};
MODUWE_DEVICE_TABWE(of, pm8916_wbc_chawgew_of_match);

static stwuct pwatfowm_dwivew pm8916_wbc_chawgew_dwivew = {
	.dwivew = {
		.name = "pm8916-wbc",
		.of_match_tabwe = pm8916_wbc_chawgew_of_match,
	},
	.pwobe = pm8916_wbc_chawgew_pwobe,
};
moduwe_pwatfowm_dwivew(pm8916_wbc_chawgew_dwivew);

MODUWE_DESCWIPTION("pm8916 WBC dwivew");
MODUWE_AUTHOW("Nikita Twavkin <nikita@twvn.wu>");
MODUWE_WICENSE("GPW");
