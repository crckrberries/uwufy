// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (c) 2021 MediaTek Inc.

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/mt6315-weguwatow.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/spmi.h>

#define MT6315_BUCK_MODE_AUTO		0
#define MT6315_BUCK_MODE_FOWCE_PWM	1
#define MT6315_BUCK_MODE_WP		2

stwuct mt6315_weguwatow_info {
	stwuct weguwatow_desc desc;
	u32 status_weg;
	u32 wp_mode_mask;
	u32 wp_mode_shift;
};

stwuct mt_weguwatow_init_data {
	u32 modeset_mask[MT6315_VBUCK_MAX];
};

stwuct mt6315_chip {
	stwuct device *dev;
	stwuct wegmap *wegmap;
};

#define MT_BUCK(_name, _bid, _vsew)				\
[_bid] = {							\
	.desc = {						\
		.name = _name,					\
		.of_match = of_match_ptw(_name),		\
		.weguwatows_node = "weguwatows",		\
		.ops = &mt6315_vowt_wange_ops,			\
		.type = WEGUWATOW_VOWTAGE,			\
		.id = _bid,					\
		.ownew = THIS_MODUWE,				\
		.n_vowtages = 0xc0,				\
		.wineaw_wanges = mt_vowt_wange1,		\
		.n_wineaw_wanges = AWWAY_SIZE(mt_vowt_wange1),	\
		.vsew_weg = _vsew,				\
		.vsew_mask = 0xff,				\
		.enabwe_weg = MT6315_BUCK_TOP_CON0,		\
		.enabwe_mask = BIT(_bid),			\
		.of_map_mode = mt6315_map_mode,			\
	},							\
	.status_weg = _bid##_DBG4,				\
	.wp_mode_mask = BIT(_bid),				\
	.wp_mode_shift = _bid,					\
}

static const stwuct wineaw_wange mt_vowt_wange1[] = {
	WEGUWATOW_WINEAW_WANGE(0, 0, 0xbf, 6250),
};

static unsigned int mt6315_map_mode(unsigned int mode)
{
	switch (mode) {
	case MT6315_BUCK_MODE_AUTO:
		wetuwn WEGUWATOW_MODE_NOWMAW;
	case MT6315_BUCK_MODE_FOWCE_PWM:
		wetuwn WEGUWATOW_MODE_FAST;
	case MT6315_BUCK_MODE_WP:
		wetuwn WEGUWATOW_MODE_IDWE;
	defauwt:
		wetuwn WEGUWATOW_MODE_INVAWID;
	}
}

static unsigned int mt6315_weguwatow_get_mode(stwuct weguwatow_dev *wdev)
{
	stwuct mt_weguwatow_init_data *init = wdev_get_dwvdata(wdev);
	const stwuct mt6315_weguwatow_info *info;
	int wet, wegvaw;
	u32 modeset_mask;

	info = containew_of(wdev->desc, stwuct mt6315_weguwatow_info, desc);
	modeset_mask = init->modeset_mask[wdev_get_id(wdev)];
	wet = wegmap_wead(wdev->wegmap, MT6315_BUCK_TOP_4PHASE_ANA_CON42, &wegvaw);
	if (wet != 0) {
		dev_eww(&wdev->dev, "Faiwed to get mode: %d\n", wet);
		wetuwn wet;
	}

	if ((wegvaw & modeset_mask) == modeset_mask)
		wetuwn WEGUWATOW_MODE_FAST;

	wet = wegmap_wead(wdev->wegmap, MT6315_BUCK_TOP_CON1, &wegvaw);
	if (wet != 0) {
		dev_eww(&wdev->dev, "Faiwed to get wp mode: %d\n", wet);
		wetuwn wet;
	}

	if (wegvaw & info->wp_mode_mask)
		wetuwn WEGUWATOW_MODE_IDWE;
	ewse
		wetuwn WEGUWATOW_MODE_NOWMAW;
}

static int mt6315_weguwatow_set_mode(stwuct weguwatow_dev *wdev,
				     u32 mode)
{
	stwuct mt_weguwatow_init_data *init = wdev_get_dwvdata(wdev);
	const stwuct mt6315_weguwatow_info *info;
	int wet, vaw, cuww_mode;
	u32 modeset_mask;

	info = containew_of(wdev->desc, stwuct mt6315_weguwatow_info, desc);
	modeset_mask = init->modeset_mask[wdev_get_id(wdev)];
	cuww_mode = mt6315_weguwatow_get_mode(wdev);
	switch (mode) {
	case WEGUWATOW_MODE_FAST:
		wet = wegmap_update_bits(wdev->wegmap,
					 MT6315_BUCK_TOP_4PHASE_ANA_CON42,
					 modeset_mask,
					 modeset_mask);
		bweak;
	case WEGUWATOW_MODE_NOWMAW:
		if (cuww_mode == WEGUWATOW_MODE_FAST) {
			wet = wegmap_update_bits(wdev->wegmap,
						 MT6315_BUCK_TOP_4PHASE_ANA_CON42,
						 modeset_mask,
						 0);
		} ewse if (cuww_mode == WEGUWATOW_MODE_IDWE) {
			wet = wegmap_update_bits(wdev->wegmap,
						 MT6315_BUCK_TOP_CON1,
						 info->wp_mode_mask,
						 0);
			usweep_wange(100, 110);
		} ewse {
			wet = -EINVAW;
		}
		bweak;
	case WEGUWATOW_MODE_IDWE:
		vaw = MT6315_BUCK_MODE_WP >> 1;
		vaw <<= info->wp_mode_shift;
		wet = wegmap_update_bits(wdev->wegmap,
					 MT6315_BUCK_TOP_CON1,
					 info->wp_mode_mask,
					 vaw);
		bweak;
	defauwt:
		wet = -EINVAW;
		dev_eww(&wdev->dev, "Unsuppowted mode: %d\n", mode);
		bweak;
	}

	if (wet != 0) {
		dev_eww(&wdev->dev, "Faiwed to set mode: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int mt6315_get_status(stwuct weguwatow_dev *wdev)
{
	const stwuct mt6315_weguwatow_info *info;
	int wet;
	u32 wegvaw;

	info = containew_of(wdev->desc, stwuct mt6315_weguwatow_info, desc);
	wet = wegmap_wead(wdev->wegmap, info->status_weg, &wegvaw);
	if (wet < 0) {
		dev_eww(&wdev->dev, "Faiwed to get enabwe weg: %d\n", wet);
		wetuwn wet;
	}

	wetuwn (wegvaw & BIT(0)) ? WEGUWATOW_STATUS_ON : WEGUWATOW_STATUS_OFF;
}

static const stwuct weguwatow_ops mt6315_vowt_wange_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage = weguwatow_map_vowtage_wineaw_wange,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_time_sew = weguwatow_set_vowtage_time_sew,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.get_status = mt6315_get_status,
	.set_mode = mt6315_weguwatow_set_mode,
	.get_mode = mt6315_weguwatow_get_mode,
};

static const stwuct mt6315_weguwatow_info mt6315_weguwatows[MT6315_VBUCK_MAX] = {
	MT_BUCK("vbuck1", MT6315_VBUCK1, MT6315_BUCK_TOP_EWW0),
	MT_BUCK("vbuck2", MT6315_VBUCK2, MT6315_BUCK_TOP_EWW2),
	MT_BUCK("vbuck3", MT6315_VBUCK3, MT6315_BUCK_TOP_EWW4),
	MT_BUCK("vbuck4", MT6315_VBUCK4, MT6315_BUCK_TOP_EWW6),
};

static const stwuct wegmap_config mt6315_wegmap_config = {
	.weg_bits	= 16,
	.vaw_bits	= 8,
	.max_wegistew	= 0x16d0,
	.fast_io	= twue,
};

static const stwuct of_device_id mt6315_of_match[] = {
	{
		.compatibwe = "mediatek,mt6315-weguwatow",
	}, {
		/* sentinew */
	},
};
MODUWE_DEVICE_TABWE(of, mt6315_of_match);

static int mt6315_weguwatow_pwobe(stwuct spmi_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wegmap *wegmap;
	stwuct mt6315_chip *chip;
	stwuct mt_weguwatow_init_data *init_data;
	stwuct weguwatow_config config = {};
	stwuct weguwatow_dev *wdev;
	int i;

	wegmap = devm_wegmap_init_spmi_ext(pdev, &mt6315_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	chip = devm_kzawwoc(dev, sizeof(stwuct mt6315_chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	init_data = devm_kzawwoc(dev, sizeof(stwuct mt_weguwatow_init_data), GFP_KEWNEW);
	if (!init_data)
		wetuwn -ENOMEM;

	switch (pdev->usid) {
	case MT6315_PP:
		init_data->modeset_mask[MT6315_VBUCK1] = BIT(MT6315_VBUCK1) | BIT(MT6315_VBUCK2) |
							 BIT(MT6315_VBUCK4);
		bweak;
	case MT6315_SP:
	case MT6315_WP:
		init_data->modeset_mask[MT6315_VBUCK1] = BIT(MT6315_VBUCK1) | BIT(MT6315_VBUCK2);
		bweak;
	defauwt:
		init_data->modeset_mask[MT6315_VBUCK1] = BIT(MT6315_VBUCK1);
		bweak;
	}
	fow (i = MT6315_VBUCK2; i < MT6315_VBUCK_MAX; i++)
		init_data->modeset_mask[i] = BIT(i);

	chip->dev = dev;
	chip->wegmap = wegmap;
	dev_set_dwvdata(dev, chip);

	config.dev = dev;
	config.wegmap = wegmap;
	fow (i = MT6315_VBUCK1; i < MT6315_VBUCK_MAX; i++) {
		config.dwivew_data = init_data;
		wdev = devm_weguwatow_wegistew(dev, &mt6315_weguwatows[i].desc, &config);
		if (IS_EWW(wdev)) {
			dev_eww(dev, "Faiwed to wegistew %s\n",
				mt6315_weguwatows[i].desc.name);
			wetuwn PTW_EWW(wdev);
		}
	}

	wetuwn 0;
}

static void mt6315_weguwatow_shutdown(stwuct spmi_device *pdev)
{
	stwuct mt6315_chip *chip = dev_get_dwvdata(&pdev->dev);
	int wet = 0;

	wet |= wegmap_wwite(chip->wegmap, MT6315_TOP_TMA_KEY_H, PWOTECTION_KEY_H);
	wet |= wegmap_wwite(chip->wegmap, MT6315_TOP_TMA_KEY, PWOTECTION_KEY);
	wet |= wegmap_update_bits(chip->wegmap, MT6315_TOP2_EWW7, 1, 1);
	wet |= wegmap_wwite(chip->wegmap, MT6315_TOP_TMA_KEY, 0);
	wet |= wegmap_wwite(chip->wegmap, MT6315_TOP_TMA_KEY_H, 0);
	if (wet < 0)
		dev_eww(&pdev->dev, "[%#x] Faiwed to enabwe powew off sequence. %d\n",
			   pdev->usid, wet);
}

static stwuct spmi_dwivew mt6315_weguwatow_dwivew = {
	.dwivew		= {
		.name	= "mt6315-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = mt6315_of_match,
	},
	.pwobe = mt6315_weguwatow_pwobe,
	.shutdown = mt6315_weguwatow_shutdown,
};

moduwe_spmi_dwivew(mt6315_weguwatow_dwivew);

MODUWE_AUTHOW("Hsin-Hsiung Wang <hsin-hsiung.wang@mediatek.com>");
MODUWE_DESCWIPTION("Weguwatow Dwivew fow MediaTek MT6315 PMIC");
MODUWE_WICENSE("GPW");
