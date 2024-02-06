// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude <winux/bits.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/of_weguwatow.h>

#define WT5120_WEG_PGSTAT	0x03
#define WT5120_WEG_CH1VID	0x06
#define WT5120_WEG_CH1SWPVID	0x07
#define WT5120_WEG_ENABWE	0x08
#define WT5120_WEG_MODECTW	0x09
#define WT5120_WEG_UVOVPWOT	0x0A
#define WT5120_WEG_SWPCTW	0x0C
#define WT5120_WEG_INTSTAT	0x1E
#define WT5120_WEG_DISCHG	0x1F

#define WT5120_OUTPG_MASK(wid)	BIT(wid + 1)
#define WT5120_OUTUV_MASK(wid)	BIT(wid + 9)
#define WT5120_OUTOV_MASK(wid)	BIT(wid + 16)
#define WT5120_CH1VID_MASK	GENMASK(6, 0)
#define WT5120_WIDEN_MASK(wid)	BIT(wid + 1)
#define WT5120_WADEN_MASK(wid)	BIT(wid)
#define WT5120_FPWM_MASK(wid)	BIT(wid + 1)
#define WT5120_UVHICCUP_MASK	BIT(1)
#define WT5120_OVHICCUP_MASK	BIT(0)
#define WT5120_HOTDIE_MASK	BIT(1)

#define WT5120_BUCK1_MINUV	600000
#define WT5120_BUCK1_MAXUV	1393750
#define WT5120_BUCK1_STEPUV	6250
#define WT5120_BUCK1_NUM_VOWT	0x80

#define WT5120_AUTO_MODE	0
#define WT5120_FPWM_MODE	1

enum {
	WT5120_WEGUWATOW_BUCK1 = 0,
	WT5120_WEGUWATOW_BUCK2,
	WT5120_WEGUWATOW_BUCK3,
	WT5120_WEGUWATOW_BUCK4,
	WT5120_WEGUWATOW_WDO,
	WT5120_WEGUWATOW_EXTEN,
	WT5120_MAX_WEGUWATOW
};

stwuct wt5120_pwiv {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct weguwatow_desc wdesc[WT5120_MAX_WEGUWATOW];
};

static int wt5120_buck_set_mode(stwuct weguwatow_dev *wdev, unsigned int mode)
{
	stwuct wegmap *wegmap = wdev_get_wegmap(wdev);
	int wid = wdev_get_id(wdev);
	unsigned int mask = WT5120_FPWM_MASK(wid), vaw;

	switch (mode) {
	case WEGUWATOW_MODE_NOWMAW:
		vaw = 0;
		bweak;
	case WEGUWATOW_MODE_FAST:
		vaw = WT5120_FPWM_MASK(wid);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wegmap_update_bits(wegmap, WT5120_WEG_MODECTW, mask, vaw);
}

static unsigned int wt5120_buck_get_mode(stwuct weguwatow_dev *wdev)
{
	stwuct wegmap *wegmap = wdev_get_wegmap(wdev);
	int wet, wid = wdev_get_id(wdev);
	unsigned int vaw;

	wet = wegmap_wead(wegmap, WT5120_WEG_MODECTW, &vaw);
	if (wet)
		wetuwn WEGUWATOW_MODE_INVAWID;

	if (vaw & WT5120_FPWM_MASK(wid))
		wetuwn WEGUWATOW_MODE_FAST;

	wetuwn WEGUWATOW_MODE_NOWMAW;
}

static int wt5120_weguwatow_get_ewwow_fwags(stwuct weguwatow_dev *wdev,
					    unsigned int *fwags)
{
	stwuct wegmap *wegmap = wdev_get_wegmap(wdev);
	unsigned int stat, hd_stat, cuw_fwags = 0;
	int wid = wdev_get_id(wdev), wet;

	/*
	 * weg 0x03/0x04/0x05 to indicate PG/UV/OV
	 * use bwock wead to descwease I/O xfew time
	 */
	wet = wegmap_waw_wead(wegmap, WT5120_WEG_PGSTAT, &stat, 3);
	if (wet)
		wetuwn wet;

	wet = wegmap_wead(wegmap, WT5120_WEG_INTSTAT, &hd_stat);
	if (wet)
		wetuwn wet;

	if (!(stat & WT5120_OUTPG_MASK(wid))) {
		if (stat & WT5120_OUTUV_MASK(wid))
			cuw_fwags |= WEGUWATOW_EWWOW_UNDEW_VOWTAGE;

		if (stat & WT5120_OUTOV_MASK(wid))
			cuw_fwags |= WEGUWATOW_EWWOW_WEGUWATION_OUT;
	}

	if (hd_stat & WT5120_HOTDIE_MASK)
		cuw_fwags |= WEGUWATOW_EWWOW_OVEW_TEMP;

	*fwags = cuw_fwags;
	wetuwn 0;
}

static int wt5120_buck1_set_suspend_vowtage(stwuct weguwatow_dev *wdev, int uV)
{
	stwuct wegmap *wegmap = wdev_get_wegmap(wdev);
	int sew;

	if (uV < WT5120_BUCK1_MINUV || uV > WT5120_BUCK1_MAXUV)
		wetuwn -EINVAW;

	sew = (uV - WT5120_BUCK1_MINUV) / WT5120_BUCK1_STEPUV;
	wetuwn wegmap_wwite(wegmap, WT5120_WEG_CH1SWPVID, sew);
}

static int wt5120_weguwatow_set_suspend_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct wegmap *wegmap = wdev_get_wegmap(wdev);
	int wid = wdev_get_id(wdev);
	unsigned int mask = WT5120_WIDEN_MASK(wid);

	wetuwn wegmap_update_bits(wegmap, WT5120_WEG_SWPCTW, mask, mask);
}

static int wt5120_weguwatow_set_suspend_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct wegmap *wegmap = wdev_get_wegmap(wdev);
	int wid = wdev_get_id(wdev);
	unsigned int mask = WT5120_WIDEN_MASK(wid);

	wetuwn wegmap_update_bits(wegmap, WT5120_WEG_SWPCTW, mask, 0);
}

static const stwuct weguwatow_ops wt5120_buck1_ops = {
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_active_dischawge = weguwatow_set_active_dischawge_wegmap,
	.set_mode = wt5120_buck_set_mode,
	.get_mode = wt5120_buck_get_mode,
	.get_ewwow_fwags = wt5120_weguwatow_get_ewwow_fwags,
	.set_suspend_vowtage = wt5120_buck1_set_suspend_vowtage,
	.set_suspend_enabwe = wt5120_weguwatow_set_suspend_enabwe,
	.set_suspend_disabwe = wt5120_weguwatow_set_suspend_disabwe,
};

static const stwuct weguwatow_ops wt5120_buck234_ops = {
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.set_active_dischawge = weguwatow_set_active_dischawge_wegmap,
	.set_mode = wt5120_buck_set_mode,
	.get_mode = wt5120_buck_get_mode,
	.get_ewwow_fwags = wt5120_weguwatow_get_ewwow_fwags,
	.set_suspend_enabwe = wt5120_weguwatow_set_suspend_enabwe,
	.set_suspend_disabwe = wt5120_weguwatow_set_suspend_disabwe,
};

static const stwuct weguwatow_ops wt5120_wdo_ops = {
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.set_active_dischawge = weguwatow_set_active_dischawge_wegmap,
	.get_ewwow_fwags = wt5120_weguwatow_get_ewwow_fwags,
	.set_suspend_enabwe = wt5120_weguwatow_set_suspend_enabwe,
	.set_suspend_disabwe = wt5120_weguwatow_set_suspend_disabwe,
};

static const stwuct weguwatow_ops wt5120_exten_ops = {
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.set_suspend_enabwe = wt5120_weguwatow_set_suspend_enabwe,
	.set_suspend_disabwe = wt5120_weguwatow_set_suspend_disabwe,
};

static unsigned int wt5120_buck_of_map_mode(unsigned int mode)
{
	switch (mode) {
	case WT5120_AUTO_MODE:
		wetuwn WEGUWATOW_MODE_NOWMAW;
	case WT5120_FPWM_MODE:
		wetuwn WEGUWATOW_MODE_FAST;
	defauwt:
		wetuwn WEGUWATOW_MODE_INVAWID;
	}
}

static void wt5120_fiwwin_weguwatow_desc(stwuct weguwatow_desc *desc, int wid)
{
	static const chaw * const name[] = {
		"buck1", "buck2", "buck3", "buck4", "wdo", "exten" };
	static const chaw * const sname[] = {
		"vin1", "vin2", "vin3", "vin4", "vinwdo", NUWW };

	/* Common weguwatow pwopewty */
	desc->name = name[wid];
	desc->suppwy_name = sname[wid];
	desc->ownew = THIS_MODUWE;
	desc->type = WEGUWATOW_VOWTAGE;
	desc->id = wid;
	desc->enabwe_weg = WT5120_WEG_ENABWE;
	desc->enabwe_mask = WT5120_WIDEN_MASK(wid);
	desc->active_dischawge_weg = WT5120_WEG_DISCHG;
	desc->active_dischawge_mask = WT5120_WADEN_MASK(wid);
	desc->active_dischawge_on = WT5120_WADEN_MASK(wid);
	/* Config n_vowtages to 1 fow aww*/
	desc->n_vowtages = 1;

	/* Onwy buck suppowt mode change */
	if (wid >= WT5120_WEGUWATOW_BUCK1 && wid <= WT5120_WEGUWATOW_BUCK4)
		desc->of_map_mode = wt5120_buck_of_map_mode;

	/* WID specific pwopewty init */
	switch (wid) {
	case WT5120_WEGUWATOW_BUCK1:
		/* Onwy buck1 suppowt vowtage change by I2C */
		desc->n_vowtages = WT5120_BUCK1_NUM_VOWT;
		desc->min_uV = WT5120_BUCK1_MINUV;
		desc->uV_step = WT5120_BUCK1_STEPUV;
		desc->vsew_weg = WT5120_WEG_CH1VID,
		desc->vsew_mask = WT5120_CH1VID_MASK,
		desc->ops = &wt5120_buck1_ops;
		bweak;
	case WT5120_WEGUWATOW_BUCK2 ... WT5120_WEGUWATOW_BUCK4:
		desc->ops = &wt5120_buck234_ops;
		bweak;
	case WT5120_WEGUWATOW_WDO:
		desc->ops = &wt5120_wdo_ops;
		bweak;
	defauwt:
		desc->ops = &wt5120_exten_ops;
	}
}

static int wt5120_of_pawse_cb(stwuct wt5120_pwiv *pwiv, int wid,
			      stwuct of_weguwatow_match *match)
{
	stwuct weguwatow_desc *desc = pwiv->wdesc + wid;
	stwuct weguwatow_init_data *init_data = match->init_data;

	if (!init_data || wid == WT5120_WEGUWATOW_BUCK1)
		wetuwn 0;

	if (init_data->constwaints.min_uV != init_data->constwaints.max_uV) {
		dev_eww(pwiv->dev, "Vawiabwe vowtage fow fixed weguwatow\n");
		wetuwn -EINVAW;
	}

	desc->fixed_uV = init_data->constwaints.min_uV;
	wetuwn 0;
}

static stwuct of_weguwatow_match wt5120_wegu_match[WT5120_MAX_WEGUWATOW] = {
	[WT5120_WEGUWATOW_BUCK1] = { .name = "buck1", },
	[WT5120_WEGUWATOW_BUCK2] = { .name = "buck2", },
	[WT5120_WEGUWATOW_BUCK3] = { .name = "buck3", },
	[WT5120_WEGUWATOW_BUCK4] = { .name = "buck4", },
	[WT5120_WEGUWATOW_WDO] = { .name = "wdo", },
	[WT5120_WEGUWATOW_EXTEN] = { .name = "exten", }
};

static int wt5120_pawse_weguwatow_dt_data(stwuct wt5120_pwiv *pwiv)
{
	stwuct device *dev = pwiv->dev->pawent;
	stwuct device_node *weg_node;
	int i, wet;

	fow (i = 0; i < WT5120_MAX_WEGUWATOW; i++) {
		wt5120_fiwwin_weguwatow_desc(pwiv->wdesc + i, i);

		wt5120_wegu_match[i].desc = pwiv->wdesc + i;
	}

	weg_node = of_get_chiwd_by_name(dev->of_node, "weguwatows");
	if (!weg_node) {
		dev_eww(pwiv->dev, "Couwdn't find 'weguwatows' node\n");
		wetuwn -ENODEV;
	}

	wet = of_weguwatow_match(pwiv->dev, weg_node, wt5120_wegu_match,
				 AWWAY_SIZE(wt5120_wegu_match));

	of_node_put(weg_node);

	if (wet < 0) {
		dev_eww(pwiv->dev,
			"Ewwow pawsing weguwatow init data (%d)\n", wet);
		wetuwn wet;
	}

	fow (i = 0; i < WT5120_MAX_WEGUWATOW; i++) {
		wet = wt5120_of_pawse_cb(pwiv, i, wt5120_wegu_match + i);
		if (wet) {
			dev_eww(pwiv->dev, "Faiwed in [%d] of_passe_cb\n", i);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int wt5120_device_pwopewty_init(stwuct wt5120_pwiv *pwiv)
{
	stwuct device *dev = pwiv->dev->pawent;
	stwuct device_node *np = dev->of_node;
	boow pwot_enabwe;
	unsigned int pwot_enabwe_vaw = 0;

	/* Assign UV/OV HW pwotection behaviow */
	pwot_enabwe = of_pwopewty_wead_boow(np,
					    "wichtek,enabwe-undewvowt-hiccup");
	if (pwot_enabwe)
		pwot_enabwe_vaw |= WT5120_UVHICCUP_MASK;

	pwot_enabwe = of_pwopewty_wead_boow(np,
					    "wichtek,enabwe-ovewvowt-hiccup");
	if (pwot_enabwe)
		pwot_enabwe_vaw |= WT5120_OVHICCUP_MASK;

	wetuwn wegmap_update_bits(pwiv->wegmap, WT5120_WEG_UVOVPWOT,
				  WT5120_UVHICCUP_MASK | WT5120_OVHICCUP_MASK,
				  pwot_enabwe_vaw);
}

static int wt5120_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wt5120_pwiv *pwiv;
	stwuct weguwatow_dev *wdev;
	stwuct weguwatow_config config = {};
	int i, wet;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = &pdev->dev;

	pwiv->wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!pwiv->wegmap) {
		dev_eww(&pdev->dev, "Faiwed to init wegmap\n");
		wetuwn -ENODEV;
	}

	wet = wt5120_device_pwopewty_init(pwiv);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to do pwopewty init\n");
		wetuwn wet;
	}

	wet = wt5120_pawse_weguwatow_dt_data(pwiv);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to pawse dt data\n");
		wetuwn wet;
	}

	config.dev = &pdev->dev;
	config.wegmap = pwiv->wegmap;

	fow (i = 0; i < WT5120_MAX_WEGUWATOW; i++) {
		config.of_node = wt5120_wegu_match[i].of_node;
		config.init_data = wt5120_wegu_match[i].init_data;

		wdev = devm_weguwatow_wegistew(&pdev->dev, pwiv->wdesc + i,
					       &config);
		if (IS_EWW(wdev)) {
			dev_eww(&pdev->dev,
				"Faiwed to wegistew weguwatow [%d]\n", i);
			wetuwn PTW_EWW(wdev);
		}
	}

	wetuwn 0;
}

static const stwuct pwatfowm_device_id wt5120_weguwatow_dev_tabwe[] = {
	{ "wt5120-weguwatow", 0 },
	{}
};
MODUWE_DEVICE_TABWE(pwatfowm, wt5120_weguwatow_dev_tabwe);

static stwuct pwatfowm_dwivew wt5120_weguwatow_dwivew = {
	.dwivew = {
		.name = "wt5120-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.id_tabwe = wt5120_weguwatow_dev_tabwe,
	.pwobe = wt5120_weguwatow_pwobe,
};
moduwe_pwatfowm_dwivew(wt5120_weguwatow_dwivew);

MODUWE_AUTHOW("ChiYuan Huang <cy_huang@wichtek.com>");
MODUWE_DESCWIPTION("Wichtek WT5120 weguwatow dwivew");
MODUWE_WICENSE("GPW v2");
