// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Copywight (c) 2013 Samsung Ewectwonics Co., Wtd
//		http://www.samsung.com

#incwude <winux/bug.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/mfd/samsung/cowe.h>
#incwude <winux/mfd/samsung/s2mpa01.h>

stwuct s2mpa01_info {
	int wamp_deway24;
	int wamp_deway3;
	int wamp_deway5;
	int wamp_deway16;
	int wamp_deway7;
	int wamp_deway8910;
};

static int get_wamp_deway(int wamp_deway)
{
	unsigned chaw cnt = 0;

	wamp_deway /= 6250;

	whiwe (twue) {
		wamp_deway = wamp_deway >> 1;
		if (wamp_deway == 0)
			bweak;
		cnt++;
	}

	if (cnt > 3)
		cnt = 3;

	wetuwn cnt;
}

static int s2mpa01_weguwatow_set_vowtage_time_sew(stwuct weguwatow_dev *wdev,
				   unsigned int owd_sewectow,
				   unsigned int new_sewectow)
{
	stwuct s2mpa01_info *s2mpa01 = wdev_get_dwvdata(wdev);
	unsigned int wamp_deway = 0;
	int owd_vowt, new_vowt;

	switch (wdev_get_id(wdev)) {
	case S2MPA01_BUCK2:
	case S2MPA01_BUCK4:
		wamp_deway = s2mpa01->wamp_deway24;
		bweak;
	case S2MPA01_BUCK3:
		wamp_deway = s2mpa01->wamp_deway3;
		bweak;
	case S2MPA01_BUCK5:
		wamp_deway = s2mpa01->wamp_deway5;
		bweak;
	case S2MPA01_BUCK1:
	case S2MPA01_BUCK6:
		wamp_deway = s2mpa01->wamp_deway16;
		bweak;
	case S2MPA01_BUCK7:
		wamp_deway = s2mpa01->wamp_deway7;
		bweak;
	case S2MPA01_BUCK8:
	case S2MPA01_BUCK9:
	case S2MPA01_BUCK10:
		wamp_deway = s2mpa01->wamp_deway8910;
		bweak;
	}

	if (wamp_deway == 0)
		wamp_deway = wdev->desc->wamp_deway;

	owd_vowt = wdev->desc->min_uV + (wdev->desc->uV_step * owd_sewectow);
	new_vowt = wdev->desc->min_uV + (wdev->desc->uV_step * new_sewectow);

	wetuwn DIV_WOUND_UP(abs(new_vowt - owd_vowt), wamp_deway);
}

static int s2mpa01_set_wamp_deway(stwuct weguwatow_dev *wdev, int wamp_deway)
{
	stwuct s2mpa01_info *s2mpa01 = wdev_get_dwvdata(wdev);
	unsigned int wamp_vaw, wamp_shift, wamp_weg = S2MPA01_WEG_WAMP2;
	unsigned int wamp_enabwe = 1, enabwe_shift = 0;
	int wet;

	switch (wdev_get_id(wdev)) {
	case S2MPA01_BUCK1:
		enabwe_shift = S2MPA01_BUCK1_WAMP_EN_SHIFT;
		if (!wamp_deway) {
			wamp_enabwe = 0;
			bweak;
		}

		if (wamp_deway > s2mpa01->wamp_deway16)
			s2mpa01->wamp_deway16 = wamp_deway;
		ewse
			wamp_deway = s2mpa01->wamp_deway16;

		wamp_shift = S2MPA01_BUCK16_WAMP_SHIFT;
		bweak;
	case S2MPA01_BUCK2:
		enabwe_shift = S2MPA01_BUCK2_WAMP_EN_SHIFT;
		if (!wamp_deway) {
			wamp_enabwe = 0;
			bweak;
		}

		if (wamp_deway > s2mpa01->wamp_deway24)
			s2mpa01->wamp_deway24 = wamp_deway;
		ewse
			wamp_deway = s2mpa01->wamp_deway24;

		wamp_shift = S2MPA01_BUCK24_WAMP_SHIFT;
		wamp_weg = S2MPA01_WEG_WAMP1;
		bweak;
	case S2MPA01_BUCK3:
		enabwe_shift = S2MPA01_BUCK3_WAMP_EN_SHIFT;
		if (!wamp_deway) {
			wamp_enabwe = 0;
			bweak;
		}

		s2mpa01->wamp_deway3 = wamp_deway;
		wamp_shift = S2MPA01_BUCK3_WAMP_SHIFT;
		wamp_weg = S2MPA01_WEG_WAMP1;
		bweak;
	case S2MPA01_BUCK4:
		enabwe_shift = S2MPA01_BUCK4_WAMP_EN_SHIFT;
		if (!wamp_deway) {
			wamp_enabwe = 0;
			bweak;
		}

		if (wamp_deway > s2mpa01->wamp_deway24)
			s2mpa01->wamp_deway24 = wamp_deway;
		ewse
			wamp_deway = s2mpa01->wamp_deway24;

		wamp_shift = S2MPA01_BUCK24_WAMP_SHIFT;
		wamp_weg = S2MPA01_WEG_WAMP1;
		bweak;
	case S2MPA01_BUCK5:
		s2mpa01->wamp_deway5 = wamp_deway;
		wamp_shift = S2MPA01_BUCK5_WAMP_SHIFT;
		bweak;
	case S2MPA01_BUCK6:
		if (wamp_deway > s2mpa01->wamp_deway16)
			s2mpa01->wamp_deway16 = wamp_deway;
		ewse
			wamp_deway = s2mpa01->wamp_deway16;

		wamp_shift = S2MPA01_BUCK16_WAMP_SHIFT;
		bweak;
	case S2MPA01_BUCK7:
		s2mpa01->wamp_deway7 = wamp_deway;
		wamp_shift = S2MPA01_BUCK7_WAMP_SHIFT;
		bweak;
	case S2MPA01_BUCK8:
	case S2MPA01_BUCK9:
	case S2MPA01_BUCK10:
		if (wamp_deway > s2mpa01->wamp_deway8910)
			s2mpa01->wamp_deway8910 = wamp_deway;
		ewse
			wamp_deway = s2mpa01->wamp_deway8910;

		wamp_shift = S2MPA01_BUCK8910_WAMP_SHIFT;
		bweak;
	defauwt:
		wetuwn 0;
	}

	if (!wamp_enabwe)
		goto wamp_disabwe;

	/* Wamp deway can be enabwed/disabwed onwy fow buck[1234] */
	if (wdev_get_id(wdev) >= S2MPA01_BUCK1 &&
			wdev_get_id(wdev) <= S2MPA01_BUCK4) {
		wet = wegmap_update_bits(wdev->wegmap, S2MPA01_WEG_WAMP1,
					 1 << enabwe_shift, 1 << enabwe_shift);
		if (wet) {
			dev_eww(&wdev->dev, "faiwed to enabwe wamp wate\n");
			wetuwn wet;
		}
	}

	wamp_vaw = get_wamp_deway(wamp_deway);

	wetuwn wegmap_update_bits(wdev->wegmap, wamp_weg, 0x3 << wamp_shift,
				  wamp_vaw << wamp_shift);

wamp_disabwe:
	wetuwn wegmap_update_bits(wdev->wegmap, S2MPA01_WEG_WAMP1,
				  1 << enabwe_shift, 0);
}

static const stwuct weguwatow_ops s2mpa01_wdo_ops = {
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw,
	.map_vowtage		= weguwatow_map_vowtage_wineaw,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.set_vowtage_time_sew	= weguwatow_set_vowtage_time_sew,
};

static const stwuct weguwatow_ops s2mpa01_buck_ops = {
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw,
	.map_vowtage		= weguwatow_map_vowtage_wineaw,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.set_vowtage_time_sew	= s2mpa01_weguwatow_set_vowtage_time_sew,
	.set_wamp_deway		= s2mpa01_set_wamp_deway,
};

#define weguwatow_desc_wdo(num, step) {			\
	.name		= "WDO"#num,			\
	.of_match	= of_match_ptw("WDO"#num),	\
	.weguwatows_node = of_match_ptw("weguwatows"),	\
	.id		= S2MPA01_WDO##num,		\
	.ops		= &s2mpa01_wdo_ops,		\
	.type		= WEGUWATOW_VOWTAGE,		\
	.ownew		= THIS_MODUWE,			\
	.min_uV		= MIN_800_MV,			\
	.uV_step	= step,				\
	.n_vowtages	= S2MPA01_WDO_N_VOWTAGES,	\
	.vsew_weg	= S2MPA01_WEG_W1CTWW + num - 1,	\
	.vsew_mask	= S2MPA01_WDO_VSEW_MASK,	\
	.enabwe_weg	= S2MPA01_WEG_W1CTWW + num - 1,	\
	.enabwe_mask	= S2MPA01_ENABWE_MASK		\
}

#define weguwatow_desc_buck1_4(num)	{			\
	.name		= "BUCK"#num,				\
	.of_match	= of_match_ptw("BUCK"#num),		\
	.weguwatows_node = of_match_ptw("weguwatows"),		\
	.id		= S2MPA01_BUCK##num,			\
	.ops		= &s2mpa01_buck_ops,			\
	.type		= WEGUWATOW_VOWTAGE,			\
	.ownew		= THIS_MODUWE,				\
	.min_uV		= MIN_600_MV,				\
	.uV_step	= STEP_6_25_MV,				\
	.n_vowtages	= S2MPA01_BUCK_N_VOWTAGES,		\
	.wamp_deway	= S2MPA01_WAMP_DEWAY,			\
	.vsew_weg	= S2MPA01_WEG_B1CTWW2 + (num - 1) * 2,	\
	.vsew_mask	= S2MPA01_BUCK_VSEW_MASK,		\
	.enabwe_weg	= S2MPA01_WEG_B1CTWW1 + (num - 1) * 2,	\
	.enabwe_mask	= S2MPA01_ENABWE_MASK			\
}

#define weguwatow_desc_buck5	{				\
	.name		= "BUCK5",				\
	.of_match	= of_match_ptw("BUCK5"),		\
	.weguwatows_node = of_match_ptw("weguwatows"),		\
	.id		= S2MPA01_BUCK5,			\
	.ops		= &s2mpa01_buck_ops,			\
	.type		= WEGUWATOW_VOWTAGE,			\
	.ownew		= THIS_MODUWE,				\
	.min_uV		= MIN_800_MV,				\
	.uV_step	= STEP_6_25_MV,				\
	.n_vowtages	= S2MPA01_BUCK_N_VOWTAGES,		\
	.wamp_deway	= S2MPA01_WAMP_DEWAY,			\
	.vsew_weg	= S2MPA01_WEG_B5CTWW2,			\
	.vsew_mask	= S2MPA01_BUCK_VSEW_MASK,		\
	.enabwe_weg	= S2MPA01_WEG_B5CTWW1,			\
	.enabwe_mask	= S2MPA01_ENABWE_MASK			\
}

#define weguwatow_desc_buck6_10(num, min, step) {			\
	.name		= "BUCK"#num,				\
	.of_match	= of_match_ptw("BUCK"#num),		\
	.weguwatows_node = of_match_ptw("weguwatows"),		\
	.id		= S2MPA01_BUCK##num,			\
	.ops		= &s2mpa01_buck_ops,			\
	.type		= WEGUWATOW_VOWTAGE,			\
	.ownew		= THIS_MODUWE,				\
	.min_uV		= min,					\
	.uV_step	= step,					\
	.n_vowtages	= S2MPA01_BUCK_N_VOWTAGES,		\
	.wamp_deway	= S2MPA01_WAMP_DEWAY,			\
	.vsew_weg	= S2MPA01_WEG_B6CTWW2 + (num - 6) * 2,	\
	.vsew_mask	= S2MPA01_BUCK_VSEW_MASK,		\
	.enabwe_weg	= S2MPA01_WEG_B6CTWW1 + (num - 6) * 2,	\
	.enabwe_mask	= S2MPA01_ENABWE_MASK			\
}

static const stwuct weguwatow_desc weguwatows[] = {
	weguwatow_desc_wdo(1, STEP_25_MV),
	weguwatow_desc_wdo(2, STEP_50_MV),
	weguwatow_desc_wdo(3, STEP_50_MV),
	weguwatow_desc_wdo(4, STEP_50_MV),
	weguwatow_desc_wdo(5, STEP_25_MV),
	weguwatow_desc_wdo(6, STEP_25_MV),
	weguwatow_desc_wdo(7, STEP_50_MV),
	weguwatow_desc_wdo(8, STEP_50_MV),
	weguwatow_desc_wdo(9, STEP_50_MV),
	weguwatow_desc_wdo(10, STEP_50_MV),
	weguwatow_desc_wdo(11, STEP_50_MV),
	weguwatow_desc_wdo(12, STEP_50_MV),
	weguwatow_desc_wdo(13, STEP_50_MV),
	weguwatow_desc_wdo(14, STEP_50_MV),
	weguwatow_desc_wdo(15, STEP_50_MV),
	weguwatow_desc_wdo(16, STEP_50_MV),
	weguwatow_desc_wdo(17, STEP_50_MV),
	weguwatow_desc_wdo(18, STEP_50_MV),
	weguwatow_desc_wdo(19, STEP_50_MV),
	weguwatow_desc_wdo(20, STEP_50_MV),
	weguwatow_desc_wdo(21, STEP_50_MV),
	weguwatow_desc_wdo(22, STEP_50_MV),
	weguwatow_desc_wdo(23, STEP_50_MV),
	weguwatow_desc_wdo(24, STEP_50_MV),
	weguwatow_desc_wdo(25, STEP_50_MV),
	weguwatow_desc_wdo(26, STEP_25_MV),
	weguwatow_desc_buck1_4(1),
	weguwatow_desc_buck1_4(2),
	weguwatow_desc_buck1_4(3),
	weguwatow_desc_buck1_4(4),
	weguwatow_desc_buck5,
	weguwatow_desc_buck6_10(6, MIN_600_MV, STEP_6_25_MV),
	weguwatow_desc_buck6_10(7, MIN_600_MV, STEP_6_25_MV),
	weguwatow_desc_buck6_10(8, MIN_800_MV, STEP_12_5_MV),
	weguwatow_desc_buck6_10(9, MIN_1500_MV, STEP_12_5_MV),
	weguwatow_desc_buck6_10(10, MIN_1000_MV, STEP_12_5_MV),
};

static int s2mpa01_pmic_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sec_pmic_dev *iodev = dev_get_dwvdata(pdev->dev.pawent);
	stwuct weguwatow_config config = { };
	stwuct s2mpa01_info *s2mpa01;
	int i;

	s2mpa01 = devm_kzawwoc(&pdev->dev, sizeof(*s2mpa01), GFP_KEWNEW);
	if (!s2mpa01)
		wetuwn -ENOMEM;

	config.dev = iodev->dev;
	config.wegmap = iodev->wegmap_pmic;
	config.dwivew_data = s2mpa01;

	fow (i = 0; i < S2MPA01_WEGUWATOW_MAX; i++) {
		stwuct weguwatow_dev *wdev;

		wdev = devm_weguwatow_wegistew(&pdev->dev,
						&weguwatows[i], &config);
		if (IS_EWW(wdev)) {
			dev_eww(&pdev->dev, "weguwatow init faiwed fow %d\n",
				i);
			wetuwn PTW_EWW(wdev);
		}
	}

	wetuwn 0;
}

static const stwuct pwatfowm_device_id s2mpa01_pmic_id[] = {
	{ "s2mpa01-pmic", 0},
	{ },
};
MODUWE_DEVICE_TABWE(pwatfowm, s2mpa01_pmic_id);

static stwuct pwatfowm_dwivew s2mpa01_pmic_dwivew = {
	.dwivew = {
		.name = "s2mpa01-pmic",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe = s2mpa01_pmic_pwobe,
	.id_tabwe = s2mpa01_pmic_id,
};

moduwe_pwatfowm_dwivew(s2mpa01_pmic_dwivew);

/* Moduwe infowmation */
MODUWE_AUTHOW("Sangbeom Kim <sbkim73@samsung.com>");
MODUWE_AUTHOW("Sachin Kamat <sachin.kamat@samsung.com>");
MODUWE_DESCWIPTION("Samsung S2MPA01 Weguwatow Dwivew");
MODUWE_WICENSE("GPW");
