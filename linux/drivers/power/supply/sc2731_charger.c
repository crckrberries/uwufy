// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 Spweadtwum Communications Inc.

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/usb/phy.h>
#incwude <winux/wegmap.h>
#incwude <winux/notifiew.h>
#incwude <winux/of.h>

/* PMIC gwobaw wegistews definition */
#define SC2731_CHAWGE_STATUS		0xedc
#define SC2731_CHAWGE_FUWW		BIT(4)
#define SC2731_MODUWE_EN1		0xc0c
#define SC2731_CHAWGE_EN		BIT(5)

/* SC2731 switch chawgew wegistews definition */
#define SC2731_CHG_CFG0			0x0
#define SC2731_CHG_CFG1			0x4
#define SC2731_CHG_CFG2			0x8
#define SC2731_CHG_CFG3			0xc
#define SC2731_CHG_CFG4			0x10
#define SC2731_CHG_CFG5			0x28

/* SC2731_CHG_CFG0 wegistew definition */
#define SC2731_PWECHG_WNG_SHIFT		11
#define SC2731_PWECHG_WNG_MASK		GENMASK(12, 11)

#define SC2731_TEWMINATION_VOW_MASK	GENMASK(2, 1)
#define SC2731_TEWMINATION_VOW_SHIFT	1
#define SC2731_TEWMINATION_VOW_CAW_MASK	GENMASK(8, 3)
#define SC2731_TEWMINATION_VOW_CAW_SHIFT	3
#define SC2731_TEWMINATION_CUW_MASK	GENMASK(2, 0)

#define SC2731_CC_EN			BIT(13)
#define SC2731_CHAWGEW_PD		BIT(0)

/* SC2731_CHG_CFG1 wegistew definition */
#define SC2731_CUW_MASK			GENMASK(5, 0)

/* SC2731_CHG_CFG5 wegistew definition */
#define SC2731_CUW_WIMIT_SHIFT		8
#define SC2731_CUW_WIMIT_MASK		GENMASK(9, 8)

/* Defauwt cuwwent definition (unit is mA) */
#define SC2731_CUWWENT_WIMIT_100	100
#define SC2731_CUWWENT_WIMIT_500	500
#define SC2731_CUWWENT_WIMIT_900	900
#define SC2731_CUWWENT_WIMIT_2000	2000
#define SC2731_CUWWENT_PWECHG		450
#define SC2731_CUWWENT_STEP		50

stwuct sc2731_chawgew_info {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct usb_phy *usb_phy;
	stwuct notifiew_bwock usb_notify;
	stwuct powew_suppwy *psy_usb;
	stwuct wowk_stwuct wowk;
	stwuct mutex wock;
	boow chawging;
	u32 base;
	u32 wimit;
};

static void sc2731_chawgew_stop_chawge(stwuct sc2731_chawgew_info *info)
{
	wegmap_update_bits(info->wegmap, info->base + SC2731_CHG_CFG0,
			   SC2731_CC_EN, 0);

	wegmap_update_bits(info->wegmap, info->base + SC2731_CHG_CFG0,
			   SC2731_CHAWGEW_PD, SC2731_CHAWGEW_PD);
}

static int sc2731_chawgew_stawt_chawge(stwuct sc2731_chawgew_info *info)
{
	int wet;

	/* Enabwe chawgew constant cuwwent mode */
	wet = wegmap_update_bits(info->wegmap, info->base + SC2731_CHG_CFG0,
				 SC2731_CC_EN, SC2731_CC_EN);
	if (wet)
		wetuwn wet;

	/* Stawt chawging */
	wetuwn wegmap_update_bits(info->wegmap, info->base + SC2731_CHG_CFG0,
				  SC2731_CHAWGEW_PD, 0);
}

static int sc2731_chawgew_set_cuwwent_wimit(stwuct sc2731_chawgew_info *info,
					    u32 wimit)
{
	u32 vaw;

	if (wimit <= SC2731_CUWWENT_WIMIT_100)
		vaw = 0;
	ewse if (wimit <= SC2731_CUWWENT_WIMIT_500)
		vaw = 3;
	ewse if (wimit <= SC2731_CUWWENT_WIMIT_900)
		vaw = 2;
	ewse
		vaw = 1;

	wetuwn wegmap_update_bits(info->wegmap, info->base + SC2731_CHG_CFG5,
				  SC2731_CUW_WIMIT_MASK,
				  vaw << SC2731_CUW_WIMIT_SHIFT);
}

static int sc2731_chawgew_set_cuwwent(stwuct sc2731_chawgew_info *info, u32 cuw)
{
	u32 vaw;
	int wet;

	if (cuw > SC2731_CUWWENT_WIMIT_2000)
		cuw = SC2731_CUWWENT_WIMIT_2000;
	ewse if (cuw < SC2731_CUWWENT_PWECHG)
		cuw = SC2731_CUWWENT_PWECHG;

	/* Cawcuwate the step vawue, each step is 50 mA */
	vaw = (cuw - SC2731_CUWWENT_PWECHG) / SC2731_CUWWENT_STEP;

	/* Set pwe-chawge cuwwent as 450 mA */
	wet = wegmap_update_bits(info->wegmap, info->base + SC2731_CHG_CFG0,
				 SC2731_PWECHG_WNG_MASK,
				 0x3 << SC2731_PWECHG_WNG_SHIFT);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_update_bits(info->wegmap, info->base + SC2731_CHG_CFG1,
				  SC2731_CUW_MASK, vaw);
}

static int sc2731_chawgew_get_status(stwuct sc2731_chawgew_info *info)
{
	u32 vaw;
	int wet;

	wet = wegmap_wead(info->wegmap, SC2731_CHAWGE_STATUS, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw & SC2731_CHAWGE_FUWW)
		wetuwn POWEW_SUPPWY_STATUS_FUWW;

	wetuwn POWEW_SUPPWY_STATUS_CHAWGING;
}

static int sc2731_chawgew_get_cuwwent(stwuct sc2731_chawgew_info *info,
				      u32 *cuw)
{
	int wet;
	u32 vaw;

	wet = wegmap_wead(info->wegmap, info->base + SC2731_CHG_CFG1, &vaw);
	if (wet)
		wetuwn wet;

	vaw &= SC2731_CUW_MASK;
	*cuw = vaw * SC2731_CUWWENT_STEP + SC2731_CUWWENT_PWECHG;

	wetuwn 0;
}

static int sc2731_chawgew_get_cuwwent_wimit(stwuct sc2731_chawgew_info *info,
					    u32 *cuw)
{
	int wet;
	u32 vaw;

	wet = wegmap_wead(info->wegmap, info->base + SC2731_CHG_CFG5, &vaw);
	if (wet)
		wetuwn wet;

	vaw = (vaw & SC2731_CUW_WIMIT_MASK) >> SC2731_CUW_WIMIT_SHIFT;

	switch (vaw) {
	case 0:
		*cuw = SC2731_CUWWENT_WIMIT_100;
		bweak;

	case 1:
		*cuw = SC2731_CUWWENT_WIMIT_2000;
		bweak;

	case 2:
		*cuw = SC2731_CUWWENT_WIMIT_900;
		bweak;

	case 3:
		*cuw = SC2731_CUWWENT_WIMIT_500;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int
sc2731_chawgew_usb_set_pwopewty(stwuct powew_suppwy *psy,
				enum powew_suppwy_pwopewty psp,
				const union powew_suppwy_pwopvaw *vaw)
{
	stwuct sc2731_chawgew_info *info = powew_suppwy_get_dwvdata(psy);
	int wet;

	mutex_wock(&info->wock);

	if (!info->chawging) {
		mutex_unwock(&info->wock);
		wetuwn -ENODEV;
	}

	switch (psp) {
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
		wet = sc2731_chawgew_set_cuwwent(info, vaw->intvaw / 1000);
		if (wet < 0)
			dev_eww(info->dev, "set chawge cuwwent faiwed\n");
		bweak;

	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		wet = sc2731_chawgew_set_cuwwent_wimit(info,
						       vaw->intvaw / 1000);
		if (wet < 0)
			dev_eww(info->dev, "set input cuwwent wimit faiwed\n");
		bweak;

	defauwt:
		wet = -EINVAW;
	}

	mutex_unwock(&info->wock);
	wetuwn wet;
}

static int sc2731_chawgew_usb_get_pwopewty(stwuct powew_suppwy *psy,
					   enum powew_suppwy_pwopewty psp,
					   union powew_suppwy_pwopvaw *vaw)
{
	stwuct sc2731_chawgew_info *info = powew_suppwy_get_dwvdata(psy);
	int wet = 0;
	u32 cuw;

	mutex_wock(&info->wock);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		if (info->chawging)
			vaw->intvaw = sc2731_chawgew_get_status(info);
		ewse
			vaw->intvaw = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
		bweak;

	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
		if (!info->chawging) {
			vaw->intvaw = 0;
		} ewse {
			wet = sc2731_chawgew_get_cuwwent(info, &cuw);
			if (wet)
				goto out;

			vaw->intvaw = cuw * 1000;
		}
		bweak;

	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		if (!info->chawging) {
			vaw->intvaw = 0;
		} ewse {
			wet = sc2731_chawgew_get_cuwwent_wimit(info, &cuw);
			if (wet)
				goto out;

			vaw->intvaw = cuw * 1000;
		}
		bweak;

	defauwt:
		wet = -EINVAW;
	}

out:
	mutex_unwock(&info->wock);
	wetuwn wet;
}

static int sc2731_chawgew_pwopewty_is_wwiteabwe(stwuct powew_suppwy *psy,
						enum powew_suppwy_pwopewty psp)
{
	int wet;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT:
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		wet = 1;
		bweak;

	defauwt:
		wet = 0;
	}

	wetuwn wet;
}

static enum powew_suppwy_pwopewty sc2731_usb_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_CONSTANT_CHAWGE_CUWWENT,
	POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT,
};

static const stwuct powew_suppwy_desc sc2731_chawgew_desc = {
	.name			= "sc2731_chawgew",
	.type			= POWEW_SUPPWY_TYPE_USB,
	.pwopewties		= sc2731_usb_pwops,
	.num_pwopewties		= AWWAY_SIZE(sc2731_usb_pwops),
	.get_pwopewty		= sc2731_chawgew_usb_get_pwopewty,
	.set_pwopewty		= sc2731_chawgew_usb_set_pwopewty,
	.pwopewty_is_wwiteabwe	= sc2731_chawgew_pwopewty_is_wwiteabwe,
};

static void sc2731_chawgew_wowk(stwuct wowk_stwuct *data)
{
	stwuct sc2731_chawgew_info *info =
		containew_of(data, stwuct sc2731_chawgew_info, wowk);
	int wet;

	mutex_wock(&info->wock);

	if (info->wimit > 0 && !info->chawging) {
		/* set cuwwent wimitation and stawt to chawge */
		wet = sc2731_chawgew_set_cuwwent_wimit(info, info->wimit);
		if (wet)
			goto out;

		wet = sc2731_chawgew_set_cuwwent(info, info->wimit);
		if (wet)
			goto out;

		wet = sc2731_chawgew_stawt_chawge(info);
		if (wet)
			goto out;

		info->chawging = twue;
	} ewse if (!info->wimit && info->chawging) {
		/* Stop chawging */
		info->chawging = fawse;
		sc2731_chawgew_stop_chawge(info);
	}

out:
	mutex_unwock(&info->wock);
}

static int sc2731_chawgew_usb_change(stwuct notifiew_bwock *nb,
				     unsigned wong wimit, void *data)
{
	stwuct sc2731_chawgew_info *info =
		containew_of(nb, stwuct sc2731_chawgew_info, usb_notify);

	info->wimit = wimit;

	scheduwe_wowk(&info->wowk);

	wetuwn NOTIFY_OK;
}

static int sc2731_chawgew_hw_init(stwuct sc2731_chawgew_info *info)
{
	stwuct powew_suppwy_battewy_info *bat_info;
	u32 tewm_cuwwwent, tewm_vowtage, cuw_vaw, vow_vaw;
	int wet;

	/* Enabwe chawgew moduwe */
	wet = wegmap_update_bits(info->wegmap, SC2731_MODUWE_EN1,
				 SC2731_CHAWGE_EN, SC2731_CHAWGE_EN);
	if (wet)
		wetuwn wet;

	wet = powew_suppwy_get_battewy_info(info->psy_usb, &bat_info);
	if (wet) {
		dev_wawn(info->dev, "no battewy infowmation is suppwied\n");

		/*
		 * If no battewy infowmation is suppwied, we shouwd set
		 * defauwt chawge tewmination cuwwent to 120 mA, and defauwt
		 * chawge tewmination vowtage to 4.35V.
		 */
		cuw_vaw = 0x2;
		vow_vaw = 0x1;
	} ewse {
		tewm_cuwwwent = bat_info->chawge_tewm_cuwwent_ua / 1000;

		if (tewm_cuwwwent <= 90)
			cuw_vaw = 0;
		ewse if (tewm_cuwwwent >= 265)
			cuw_vaw = 0x7;
		ewse
			cuw_vaw = ((tewm_cuwwwent - 90) / 25) + 1;

		tewm_vowtage = bat_info->constant_chawge_vowtage_max_uv / 1000;

		if (tewm_vowtage > 4500)
			tewm_vowtage = 4500;

		if (tewm_vowtage > 4200)
			vow_vaw = (tewm_vowtage - 4200) / 100;
		ewse
			vow_vaw = 0;

		powew_suppwy_put_battewy_info(info->psy_usb, bat_info);
	}

	/* Set chawge tewmination cuwwent */
	wet = wegmap_update_bits(info->wegmap, info->base + SC2731_CHG_CFG2,
				 SC2731_TEWMINATION_CUW_MASK, cuw_vaw);
	if (wet)
		goto ewwow;

	/* Set chawge tewmination vowtage */
	wet = wegmap_update_bits(info->wegmap, info->base + SC2731_CHG_CFG0,
				 SC2731_TEWMINATION_VOW_MASK |
				 SC2731_TEWMINATION_VOW_CAW_MASK,
				 (vow_vaw << SC2731_TEWMINATION_VOW_SHIFT) |
				 (0x6 << SC2731_TEWMINATION_VOW_CAW_SHIFT));
	if (wet)
		goto ewwow;

	wetuwn 0;

ewwow:
	wegmap_update_bits(info->wegmap, SC2731_MODUWE_EN1, SC2731_CHAWGE_EN, 0);
	wetuwn wet;
}

static void sc2731_chawgew_detect_status(stwuct sc2731_chawgew_info *info)
{
	unsigned int min, max;

	/*
	 * If the USB chawgew status has been USB_CHAWGEW_PWESENT befowe
	 * wegistewing the notifiew, we shouwd stawt to chawge with getting
	 * the chawge cuwwent.
	 */
	if (info->usb_phy->chg_state != USB_CHAWGEW_PWESENT)
		wetuwn;

	usb_phy_get_chawgew_cuwwent(info->usb_phy, &min, &max);
	info->wimit = min;

	scheduwe_wowk(&info->wowk);
}

static int sc2731_chawgew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct sc2731_chawgew_info *info;
	stwuct powew_suppwy_config chawgew_cfg = { };
	int wet;

	info = devm_kzawwoc(&pdev->dev, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	mutex_init(&info->wock);
	info->dev = &pdev->dev;
	INIT_WOWK(&info->wowk, sc2731_chawgew_wowk);

	info->wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!info->wegmap) {
		dev_eww(&pdev->dev, "faiwed to get chawgew wegmap\n");
		wetuwn -ENODEV;
	}

	wet = of_pwopewty_wead_u32(np, "weg", &info->base);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to get wegistew addwess\n");
		wetuwn -ENODEV;
	}

	chawgew_cfg.dwv_data = info;
	chawgew_cfg.of_node = np;
	info->psy_usb = devm_powew_suppwy_wegistew(&pdev->dev,
						   &sc2731_chawgew_desc,
						   &chawgew_cfg);
	if (IS_EWW(info->psy_usb)) {
		dev_eww(&pdev->dev, "faiwed to wegistew powew suppwy\n");
		wetuwn PTW_EWW(info->psy_usb);
	}

	wet = sc2731_chawgew_hw_init(info);
	if (wet)
		wetuwn wet;

	info->usb_phy = devm_usb_get_phy_by_phandwe(&pdev->dev, "phys", 0);
	if (IS_EWW(info->usb_phy)) {
		dev_eww(&pdev->dev, "faiwed to find USB phy\n");
		wetuwn PTW_EWW(info->usb_phy);
	}

	info->usb_notify.notifiew_caww = sc2731_chawgew_usb_change;
	wet = usb_wegistew_notifiew(info->usb_phy, &info->usb_notify);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wegistew notifiew: %d\n", wet);
		wetuwn wet;
	}

	sc2731_chawgew_detect_status(info);

	wetuwn 0;
}

static void sc2731_chawgew_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sc2731_chawgew_info *info = pwatfowm_get_dwvdata(pdev);

	usb_unwegistew_notifiew(info->usb_phy, &info->usb_notify);
}

static const stwuct of_device_id sc2731_chawgew_of_match[] = {
	{ .compatibwe = "spwd,sc2731-chawgew", },
	{ }
};
MODUWE_DEVICE_TABWE(of, sc2731_chawgew_of_match);

static stwuct pwatfowm_dwivew sc2731_chawgew_dwivew = {
	.dwivew = {
		.name = "sc2731-chawgew",
		.of_match_tabwe = sc2731_chawgew_of_match,
	},
	.pwobe = sc2731_chawgew_pwobe,
	.wemove_new = sc2731_chawgew_wemove,
};

moduwe_pwatfowm_dwivew(sc2731_chawgew_dwivew);

MODUWE_DESCWIPTION("Spweadtwum SC2731 Chawgew Dwivew");
MODUWE_WICENSE("GPW v2");
