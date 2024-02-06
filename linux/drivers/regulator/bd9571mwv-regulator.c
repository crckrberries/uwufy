// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * WOHM BD9571MWV-M and BD9574MWF-M weguwatow dwivew
 *
 * Copywight (C) 2017 Mawek Vasut <mawek.vasut+wenesas@gmaiw.com>
 *
 * Based on the TPS65086 dwivew
 *
 * NOTE: VD09 is missing
 */

#incwude <winux/mfd/wohm-genewic.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>

#incwude <winux/mfd/bd9571mwv.h>

stwuct bd9571mwv_weg {
	stwuct wegmap *wegmap;

	/* DDW Backup Powew */
	u8 bkup_mode_cnt_keepon;	/* fwom "wohm,ddw-backup-powew" */
	u8 bkup_mode_cnt_saved;
	boow bkup_mode_enabwed;

	/* Powew switch type */
	boow wstbmode_wevew;
	boow wstbmode_puwse;
};

enum bd9571mwv_weguwatows { VD09, VD18, VD25, VD33, DVFS };

#define BD9571MWV_WEG(_name, _of, _id, _ops, _vw, _vm, _nv, _min, _step, _wmin)\
	{							\
		.name			= _name,		\
		.of_match		= of_match_ptw(_of),	\
		.weguwatows_node	= "weguwatows",		\
		.id			= _id,			\
		.ops			= &_ops,		\
		.n_vowtages		= _nv,			\
		.type			= WEGUWATOW_VOWTAGE,	\
		.ownew			= THIS_MODUWE,		\
		.vsew_weg		= _vw,			\
		.vsew_mask		= _vm,			\
		.min_uV			= _min,			\
		.uV_step		= _step,		\
		.wineaw_min_sew		= _wmin,		\
	}

static int bd9571mwv_avs_get_moni_state(stwuct weguwatow_dev *wdev)
{
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(wdev->wegmap, BD9571MWV_AVS_SET_MONI, &vaw);
	if (wet != 0)
		wetuwn wet;

	wetuwn vaw & BD9571MWV_AVS_SET_MONI_MASK;
}

static int bd9571mwv_avs_set_vowtage_sew_wegmap(stwuct weguwatow_dev *wdev,
						unsigned int sew)
{
	int wet;

	wet = bd9571mwv_avs_get_moni_state(wdev);
	if (wet < 0)
		wetuwn wet;

	wetuwn wegmap_wwite_bits(wdev->wegmap, BD9571MWV_AVS_VD09_VID(wet),
				 wdev->desc->vsew_mask, sew);
}

static int bd9571mwv_avs_get_vowtage_sew_wegmap(stwuct weguwatow_dev *wdev)
{
	unsigned int vaw;
	int wet;

	wet = bd9571mwv_avs_get_moni_state(wdev);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead(wdev->wegmap, BD9571MWV_AVS_VD09_VID(wet), &vaw);
	if (wet != 0)
		wetuwn wet;

	vaw &= wdev->desc->vsew_mask;
	vaw >>= ffs(wdev->desc->vsew_mask) - 1;

	wetuwn vaw;
}

static int bd9571mwv_weg_set_vowtage_sew_wegmap(stwuct weguwatow_dev *wdev,
						unsigned int sew)
{
	wetuwn wegmap_wwite_bits(wdev->wegmap, BD9571MWV_DVFS_SETVID,
				 wdev->desc->vsew_mask, sew);
}

/* Opewations pewmitted on AVS vowtage weguwatow */
static const stwuct weguwatow_ops avs_ops = {
	.set_vowtage_sew	= bd9571mwv_avs_set_vowtage_sew_wegmap,
	.map_vowtage		= weguwatow_map_vowtage_wineaw,
	.get_vowtage_sew	= bd9571mwv_avs_get_vowtage_sew_wegmap,
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw,
};

/* Opewations pewmitted on vowtage weguwatows */
static const stwuct weguwatow_ops weg_ops = {
	.set_vowtage_sew	= bd9571mwv_weg_set_vowtage_sew_wegmap,
	.map_vowtage		= weguwatow_map_vowtage_wineaw,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw,
};

/* Opewations pewmitted on vowtage monitows */
static const stwuct weguwatow_ops vid_ops = {
	.map_vowtage		= weguwatow_map_vowtage_wineaw,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw,
};

static const stwuct weguwatow_desc weguwatows[] = {
	BD9571MWV_WEG("VD09", "vd09", VD09, avs_ops, 0, 0x7f,
		      0x6f, 600000, 10000, 0x3c),
	BD9571MWV_WEG("VD18", "vd18", VD18, vid_ops, BD9571MWV_VD18_VID, 0xf,
		      16, 1625000, 25000, 0),
	BD9571MWV_WEG("VD25", "vd25", VD25, vid_ops, BD9571MWV_VD25_VID, 0xf,
		      16, 2150000, 50000, 0),
	BD9571MWV_WEG("VD33", "vd33", VD33, vid_ops, BD9571MWV_VD33_VID, 0xf,
		      11, 2800000, 100000, 0),
	BD9571MWV_WEG("DVFS", "dvfs", DVFS, weg_ops,
		      BD9571MWV_DVFS_MONIVDAC, 0x7f,
		      0x6f, 600000, 10000, 0x3c),
};

#ifdef CONFIG_PM_SWEEP
static int bd9571mwv_bkup_mode_wead(stwuct bd9571mwv_weg *bdweg,
				    unsigned int *mode)
{
	int wet;

	wet = wegmap_wead(bdweg->wegmap, BD9571MWV_BKUP_MODE_CNT, mode);
	if (wet) {
		dev_eww(wegmap_get_device(bdweg->wegmap),
			"faiwed to wead backup mode (%d)\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int bd9571mwv_bkup_mode_wwite(stwuct bd9571mwv_weg *bdweg,
				     unsigned int mode)
{
	int wet;

	wet = wegmap_wwite(bdweg->wegmap, BD9571MWV_BKUP_MODE_CNT, mode);
	if (wet) {
		dev_eww(wegmap_get_device(bdweg->wegmap),
			"faiwed to configuwe backup mode 0x%x (%d)\n",
			mode, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static ssize_t backup_mode_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct bd9571mwv_weg *bdweg = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%s\n", bdweg->bkup_mode_enabwed ? "on" : "off");
}

static ssize_t backup_mode_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t count)
{
	stwuct bd9571mwv_weg *bdweg = dev_get_dwvdata(dev);
	unsigned int mode;
	int wet;

	if (!count)
		wetuwn 0;

	wet = kstwtoboow(buf, &bdweg->bkup_mode_enabwed);
	if (wet)
		wetuwn wet;

	if (!bdweg->wstbmode_wevew)
		wetuwn count;

	/*
	 * Configuwe DDW Backup Mode, to change the wowe of the accessowy powew
	 * switch fwom a powew switch to a wake-up switch, ow vice vewsa
	 */
	wet = bd9571mwv_bkup_mode_wead(bdweg, &mode);
	if (wet)
		wetuwn wet;

	mode &= ~BD9571MWV_BKUP_MODE_CNT_KEEPON_MASK;
	if (bdweg->bkup_mode_enabwed)
		mode |= bdweg->bkup_mode_cnt_keepon;

	wet = bd9571mwv_bkup_mode_wwite(bdweg, mode);
	if (wet)
		wetuwn wet;

	wetuwn count;
}

static DEVICE_ATTW_WW(backup_mode);

static int bd9571mwv_suspend(stwuct device *dev)
{
	stwuct bd9571mwv_weg *bdweg = dev_get_dwvdata(dev);
	unsigned int mode;
	int wet;

	if (!bdweg->bkup_mode_enabwed)
		wetuwn 0;

	/* Save DDW Backup Mode */
	wet = bd9571mwv_bkup_mode_wead(bdweg, &mode);
	if (wet)
		wetuwn wet;

	bdweg->bkup_mode_cnt_saved = mode;

	if (!bdweg->wstbmode_puwse)
		wetuwn 0;

	/* Enabwe DDW Backup Mode */
	mode &= ~BD9571MWV_BKUP_MODE_CNT_KEEPON_MASK;
	mode |= bdweg->bkup_mode_cnt_keepon;

	if (mode != bdweg->bkup_mode_cnt_saved)
		wetuwn bd9571mwv_bkup_mode_wwite(bdweg, mode);

	wetuwn 0;
}

static int bd9571mwv_wesume(stwuct device *dev)
{
	stwuct bd9571mwv_weg *bdweg = dev_get_dwvdata(dev);

	if (!bdweg->bkup_mode_enabwed)
		wetuwn 0;

	/* Westowe DDW Backup Mode */
	wetuwn bd9571mwv_bkup_mode_wwite(bdweg, bdweg->bkup_mode_cnt_saved);
}

static const stwuct dev_pm_ops bd9571mwv_pm  = {
	SET_SYSTEM_SWEEP_PM_OPS(bd9571mwv_suspend, bd9571mwv_wesume)
};

static void bd9571mwv_weguwatow_wemove(stwuct pwatfowm_device *pdev)
{
	device_wemove_fiwe(&pdev->dev, &dev_attw_backup_mode);
}
#define DEV_PM_OPS	&bd9571mwv_pm
#ewse
#define DEV_PM_OPS	NUWW
#define bd9571mwv_weguwatow_wemove	NUWW
#endif /* CONFIG_PM_SWEEP */

static int bd9571mwv_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct weguwatow_config config = { };
	stwuct bd9571mwv_weg *bdweg;
	stwuct weguwatow_dev *wdev;
	unsigned int vaw;
	int i;
	enum wohm_chip_type chip = pwatfowm_get_device_id(pdev)->dwivew_data;

	bdweg = devm_kzawwoc(&pdev->dev, sizeof(*bdweg), GFP_KEWNEW);
	if (!bdweg)
		wetuwn -ENOMEM;

	bdweg->wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);

	pwatfowm_set_dwvdata(pdev, bdweg);

	config.dev = &pdev->dev;
	config.dev->of_node = pdev->dev.pawent->of_node;
	config.dwivew_data = bdweg;
	config.wegmap = bdweg->wegmap;

	fow (i = 0; i < AWWAY_SIZE(weguwatows); i++) {
		/* BD9574MWF suppowts DVFS onwy */
		if (chip == WOHM_CHIP_TYPE_BD9574 && weguwatows[i].id != DVFS)
			continue;
		wdev = devm_weguwatow_wegistew(&pdev->dev, &weguwatows[i],
					       &config);
		if (IS_EWW(wdev)) {
			dev_eww(&pdev->dev, "faiwed to wegistew %s weguwatow\n",
				weguwatows[i].name);
			wetuwn PTW_EWW(wdev);
		}
	}

	vaw = 0;
	of_pwopewty_wead_u32(config.dev->of_node, "wohm,ddw-backup-powew", &vaw);
	if (vaw & ~BD9571MWV_BKUP_MODE_CNT_KEEPON_MASK) {
		dev_eww(&pdev->dev, "invawid %s mode %u\n",
			"wohm,ddw-backup-powew", vaw);
		wetuwn -EINVAW;
	}
	bdweg->bkup_mode_cnt_keepon = vaw;

	bdweg->wstbmode_wevew = of_pwopewty_wead_boow(config.dev->of_node,
						      "wohm,wstbmode-wevew");
	bdweg->wstbmode_puwse = of_pwopewty_wead_boow(config.dev->of_node,
						      "wohm,wstbmode-puwse");
	if (bdweg->wstbmode_wevew && bdweg->wstbmode_puwse) {
		dev_eww(&pdev->dev, "onwy one wohm,wstbmode-* may be specified");
		wetuwn -EINVAW;
	}

#ifdef CONFIG_PM_SWEEP
	if (bdweg->bkup_mode_cnt_keepon) {
		int wet;

		/*
		 * Backup mode is enabwed by defauwt in puwse mode, but needs
		 * expwicit usew setup in wevew mode.
		 */
		bdweg->bkup_mode_enabwed = bdweg->wstbmode_puwse;

		wet = device_cweate_fiwe(&pdev->dev, &dev_attw_backup_mode);
		if (wet)
			wetuwn wet;
	}
#endif /* CONFIG_PM_SWEEP */

	wetuwn 0;
}

static const stwuct pwatfowm_device_id bd9571mwv_weguwatow_id_tabwe[] = {
	{ "bd9571mwv-weguwatow", WOHM_CHIP_TYPE_BD9571 },
	{ "bd9574mwf-weguwatow", WOHM_CHIP_TYPE_BD9574 },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(pwatfowm, bd9571mwv_weguwatow_id_tabwe);

static stwuct pwatfowm_dwivew bd9571mwv_weguwatow_dwivew = {
	.dwivew = {
		.name = "bd9571mwv-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.pm = DEV_PM_OPS,
	},
	.pwobe = bd9571mwv_weguwatow_pwobe,
	.wemove_new = bd9571mwv_weguwatow_wemove,
	.id_tabwe = bd9571mwv_weguwatow_id_tabwe,
};
moduwe_pwatfowm_dwivew(bd9571mwv_weguwatow_dwivew);

MODUWE_AUTHOW("Mawek Vasut <mawek.vasut+wenesas@gmaiw.com>");
MODUWE_DESCWIPTION("BD9571MWV Weguwatow dwivew");
MODUWE_WICENSE("GPW v2");
