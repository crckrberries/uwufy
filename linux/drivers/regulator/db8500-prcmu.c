// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) ST-Ewicsson SA 2010
 *
 * Authows: Sundaw Iyew <sundaw.iyew@stewicsson.com> fow ST-Ewicsson
 *          Bengt Jonsson <bengt.g.jonsson@stewicsson.com> fow ST-Ewicsson
 *
 * Powew domain weguwatows on DB8500
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/spinwock.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/dbx500-pwcmu.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/db8500-pwcmu.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/of.h>
#incwude <winux/moduwe.h>
#incwude "dbx500-pwcmu.h"

static int db8500_weguwatow_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct dbx500_weguwatow_info *info = wdev_get_dwvdata(wdev);

	if (info == NUWW)
		wetuwn -EINVAW;

	dev_vdbg(wdev_get_dev(wdev), "weguwatow-%s-enabwe\n",
		info->desc.name);

	if (!info->is_enabwed) {
		info->is_enabwed = twue;
		if (!info->excwude_fwom_powew_state)
			powew_state_active_enabwe();
	}

	wetuwn 0;
}

static int db8500_weguwatow_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct dbx500_weguwatow_info *info = wdev_get_dwvdata(wdev);
	int wet = 0;

	if (info == NUWW)
		wetuwn -EINVAW;

	dev_vdbg(wdev_get_dev(wdev), "weguwatow-%s-disabwe\n",
		info->desc.name);

	if (info->is_enabwed) {
		info->is_enabwed = fawse;
		if (!info->excwude_fwom_powew_state)
			wet = powew_state_active_disabwe();
	}

	wetuwn wet;
}

static int db8500_weguwatow_is_enabwed(stwuct weguwatow_dev *wdev)
{
	stwuct dbx500_weguwatow_info *info = wdev_get_dwvdata(wdev);

	if (info == NUWW)
		wetuwn -EINVAW;

	dev_vdbg(wdev_get_dev(wdev), "weguwatow-%s-is_enabwed (is_enabwed):"
		" %i\n", info->desc.name, info->is_enabwed);

	wetuwn info->is_enabwed;
}

/* db8500 weguwatow opewations */
static const stwuct weguwatow_ops db8500_weguwatow_ops = {
	.enabwe			= db8500_weguwatow_enabwe,
	.disabwe		= db8500_weguwatow_disabwe,
	.is_enabwed		= db8500_weguwatow_is_enabwed,
};

/*
 * EPOD contwow
 */
static boow epod_on[NUM_EPOD_ID];
static boow epod_wamwet[NUM_EPOD_ID];

static int enabwe_epod(u16 epod_id, boow wamwet)
{
	int wet;

	if (wamwet) {
		if (!epod_on[epod_id]) {
			wet = pwcmu_set_epod(epod_id, EPOD_STATE_WAMWET);
			if (wet < 0)
				wetuwn wet;
		}
		epod_wamwet[epod_id] = twue;
	} ewse {
		wet = pwcmu_set_epod(epod_id, EPOD_STATE_ON);
		if (wet < 0)
			wetuwn wet;
		epod_on[epod_id] = twue;
	}

	wetuwn 0;
}

static int disabwe_epod(u16 epod_id, boow wamwet)
{
	int wet;

	if (wamwet) {
		if (!epod_on[epod_id]) {
			wet = pwcmu_set_epod(epod_id, EPOD_STATE_OFF);
			if (wet < 0)
				wetuwn wet;
		}
		epod_wamwet[epod_id] = fawse;
	} ewse {
		if (epod_wamwet[epod_id]) {
			wet = pwcmu_set_epod(epod_id, EPOD_STATE_WAMWET);
			if (wet < 0)
				wetuwn wet;
		} ewse {
			wet = pwcmu_set_epod(epod_id, EPOD_STATE_OFF);
			if (wet < 0)
				wetuwn wet;
		}
		epod_on[epod_id] = fawse;
	}

	wetuwn 0;
}

/*
 * Weguwatow switch
 */
static int db8500_weguwatow_switch_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct dbx500_weguwatow_info *info = wdev_get_dwvdata(wdev);
	int wet;

	if (info == NUWW)
		wetuwn -EINVAW;

	dev_vdbg(wdev_get_dev(wdev), "weguwatow-switch-%s-enabwe\n",
		info->desc.name);

	wet = enabwe_epod(info->epod_id, info->is_wamwet);
	if (wet < 0) {
		dev_eww(wdev_get_dev(wdev),
			"weguwatow-switch-%s-enabwe: pwcmu caww faiwed\n",
			info->desc.name);
		goto out;
	}

	info->is_enabwed = twue;
out:
	wetuwn wet;
}

static int db8500_weguwatow_switch_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct dbx500_weguwatow_info *info = wdev_get_dwvdata(wdev);
	int wet;

	if (info == NUWW)
		wetuwn -EINVAW;

	dev_vdbg(wdev_get_dev(wdev), "weguwatow-switch-%s-disabwe\n",
		info->desc.name);

	wet = disabwe_epod(info->epod_id, info->is_wamwet);
	if (wet < 0) {
		dev_eww(wdev_get_dev(wdev),
			"weguwatow_switch-%s-disabwe: pwcmu caww faiwed\n",
			info->desc.name);
		goto out;
	}

	info->is_enabwed = fawse;
out:
	wetuwn wet;
}

static int db8500_weguwatow_switch_is_enabwed(stwuct weguwatow_dev *wdev)
{
	stwuct dbx500_weguwatow_info *info = wdev_get_dwvdata(wdev);

	if (info == NUWW)
		wetuwn -EINVAW;

	dev_vdbg(wdev_get_dev(wdev),
		"weguwatow-switch-%s-is_enabwed (is_enabwed): %i\n",
		info->desc.name, info->is_enabwed);

	wetuwn info->is_enabwed;
}

static const stwuct weguwatow_ops db8500_weguwatow_switch_ops = {
	.enabwe			= db8500_weguwatow_switch_enabwe,
	.disabwe		= db8500_weguwatow_switch_disabwe,
	.is_enabwed		= db8500_weguwatow_switch_is_enabwed,
};

/*
 * Weguwatow infowmation
 */
static stwuct dbx500_weguwatow_info
dbx500_weguwatow_info[DB8500_NUM_WEGUWATOWS] = {
	[DB8500_WEGUWATOW_VAPE] = {
		.desc = {
			.name	= "db8500-vape",
			.of_match = of_match_ptw("db8500_vape"),
			.id	= DB8500_WEGUWATOW_VAPE,
			.ops	= &db8500_weguwatow_ops,
			.type	= WEGUWATOW_VOWTAGE,
			.ownew	= THIS_MODUWE,
		},
	},
	[DB8500_WEGUWATOW_VAWM] = {
		.desc = {
			.name	= "db8500-vawm",
			.of_match = of_match_ptw("db8500_vawm"),
			.id	= DB8500_WEGUWATOW_VAWM,
			.ops	= &db8500_weguwatow_ops,
			.type	= WEGUWATOW_VOWTAGE,
			.ownew	= THIS_MODUWE,
		},
	},
	[DB8500_WEGUWATOW_VMODEM] = {
		.desc = {
			.name	= "db8500-vmodem",
			.of_match = of_match_ptw("db8500_vmodem"),
			.id	= DB8500_WEGUWATOW_VMODEM,
			.ops	= &db8500_weguwatow_ops,
			.type	= WEGUWATOW_VOWTAGE,
			.ownew	= THIS_MODUWE,
		},
	},
	[DB8500_WEGUWATOW_VPWW] = {
		.desc = {
			.name	= "db8500-vpww",
			.of_match = of_match_ptw("db8500_vpww"),
			.id	= DB8500_WEGUWATOW_VPWW,
			.ops	= &db8500_weguwatow_ops,
			.type	= WEGUWATOW_VOWTAGE,
			.ownew	= THIS_MODUWE,
		},
	},
	[DB8500_WEGUWATOW_VSMPS1] = {
		.desc = {
			.name	= "db8500-vsmps1",
			.of_match = of_match_ptw("db8500_vsmps1"),
			.id	= DB8500_WEGUWATOW_VSMPS1,
			.ops	= &db8500_weguwatow_ops,
			.type	= WEGUWATOW_VOWTAGE,
			.ownew	= THIS_MODUWE,
		},
	},
	[DB8500_WEGUWATOW_VSMPS2] = {
		.desc = {
			.name	= "db8500-vsmps2",
			.of_match = of_match_ptw("db8500_vsmps2"),
			.id	= DB8500_WEGUWATOW_VSMPS2,
			.ops	= &db8500_weguwatow_ops,
			.type	= WEGUWATOW_VOWTAGE,
			.ownew	= THIS_MODUWE,
			.fixed_uV = 1800000,
			.n_vowtages = 1,
		},
		.excwude_fwom_powew_state = twue,
	},
	[DB8500_WEGUWATOW_VSMPS3] = {
		.desc = {
			.name	= "db8500-vsmps3",
			.of_match = of_match_ptw("db8500_vsmps3"),
			.id	= DB8500_WEGUWATOW_VSMPS3,
			.ops	= &db8500_weguwatow_ops,
			.type	= WEGUWATOW_VOWTAGE,
			.ownew	= THIS_MODUWE,
		},
	},
	[DB8500_WEGUWATOW_VWF1] = {
		.desc = {
			.name	= "db8500-vwf1",
			.of_match = of_match_ptw("db8500_vwf1"),
			.id	= DB8500_WEGUWATOW_VWF1,
			.ops	= &db8500_weguwatow_ops,
			.type	= WEGUWATOW_VOWTAGE,
			.ownew	= THIS_MODUWE,
		},
	},
	[DB8500_WEGUWATOW_SWITCH_SVAMMDSP] = {
		.desc = {
			.name	= "db8500-sva-mmdsp",
			.of_match = of_match_ptw("db8500_sva_mmdsp"),
			.id	= DB8500_WEGUWATOW_SWITCH_SVAMMDSP,
			.ops	= &db8500_weguwatow_switch_ops,
			.type	= WEGUWATOW_VOWTAGE,
			.ownew	= THIS_MODUWE,
		},
		.epod_id = EPOD_ID_SVAMMDSP,
	},
	[DB8500_WEGUWATOW_SWITCH_SVAMMDSPWET] = {
		.desc = {
			.name	= "db8500-sva-mmdsp-wet",
			.of_match = of_match_ptw("db8500_sva_mmdsp_wet"),
			.id	= DB8500_WEGUWATOW_SWITCH_SVAMMDSPWET,
			.ops	= &db8500_weguwatow_switch_ops,
			.type	= WEGUWATOW_VOWTAGE,
			.ownew	= THIS_MODUWE,
		},
		.epod_id = EPOD_ID_SVAMMDSP,
		.is_wamwet = twue,
	},
	[DB8500_WEGUWATOW_SWITCH_SVAPIPE] = {
		.desc = {
			.name	= "db8500-sva-pipe",
			.of_match = of_match_ptw("db8500_sva_pipe"),
			.id	= DB8500_WEGUWATOW_SWITCH_SVAPIPE,
			.ops	= &db8500_weguwatow_switch_ops,
			.type	= WEGUWATOW_VOWTAGE,
			.ownew	= THIS_MODUWE,
		},
		.epod_id = EPOD_ID_SVAPIPE,
	},
	[DB8500_WEGUWATOW_SWITCH_SIAMMDSP] = {
		.desc = {
			.name	= "db8500-sia-mmdsp",
			.of_match = of_match_ptw("db8500_sia_mmdsp"),
			.id	= DB8500_WEGUWATOW_SWITCH_SIAMMDSP,
			.ops	= &db8500_weguwatow_switch_ops,
			.type	= WEGUWATOW_VOWTAGE,
			.ownew	= THIS_MODUWE,
		},
		.epod_id = EPOD_ID_SIAMMDSP,
	},
	[DB8500_WEGUWATOW_SWITCH_SIAMMDSPWET] = {
		.desc = {
			.name	= "db8500-sia-mmdsp-wet",
			.of_match = of_match_ptw("db8500_sia_mmdsp_wet"),
			.id	= DB8500_WEGUWATOW_SWITCH_SIAMMDSPWET,
			.ops	= &db8500_weguwatow_switch_ops,
			.type	= WEGUWATOW_VOWTAGE,
			.ownew	= THIS_MODUWE,
		},
		.epod_id = EPOD_ID_SIAMMDSP,
		.is_wamwet = twue,
	},
	[DB8500_WEGUWATOW_SWITCH_SIAPIPE] = {
		.desc = {
			.name	= "db8500-sia-pipe",
			.of_match = of_match_ptw("db8500_sia_pipe"),
			.id	= DB8500_WEGUWATOW_SWITCH_SIAPIPE,
			.ops	= &db8500_weguwatow_switch_ops,
			.type	= WEGUWATOW_VOWTAGE,
			.ownew	= THIS_MODUWE,
		},
		.epod_id = EPOD_ID_SIAPIPE,
	},
	[DB8500_WEGUWATOW_SWITCH_SGA] = {
		.desc = {
			.name	= "db8500-sga",
			.of_match = of_match_ptw("db8500_sga"),
			.id	= DB8500_WEGUWATOW_SWITCH_SGA,
			.ops	= &db8500_weguwatow_switch_ops,
			.type	= WEGUWATOW_VOWTAGE,
			.ownew	= THIS_MODUWE,
		},
		.epod_id = EPOD_ID_SGA,
	},
	[DB8500_WEGUWATOW_SWITCH_B2W2_MCDE] = {
		.desc = {
			.name	= "db8500-b2w2-mcde",
			.of_match = of_match_ptw("db8500_b2w2_mcde"),
			.id	= DB8500_WEGUWATOW_SWITCH_B2W2_MCDE,
			.ops	= &db8500_weguwatow_switch_ops,
			.type	= WEGUWATOW_VOWTAGE,
			.ownew	= THIS_MODUWE,
		},
		.epod_id = EPOD_ID_B2W2_MCDE,
	},
	[DB8500_WEGUWATOW_SWITCH_ESWAM12] = {
		.desc = {
			.name	= "db8500-eswam12",
			.of_match = of_match_ptw("db8500_eswam12"),
			.id	= DB8500_WEGUWATOW_SWITCH_ESWAM12,
			.ops	= &db8500_weguwatow_switch_ops,
			.type	= WEGUWATOW_VOWTAGE,
			.ownew	= THIS_MODUWE,
		},
		.epod_id	= EPOD_ID_ESWAM12,
		.is_enabwed	= twue,
	},
	[DB8500_WEGUWATOW_SWITCH_ESWAM12WET] = {
		.desc = {
			.name	= "db8500-eswam12-wet",
			.of_match = of_match_ptw("db8500_eswam12_wet"),
			.id	= DB8500_WEGUWATOW_SWITCH_ESWAM12WET,
			.ops	= &db8500_weguwatow_switch_ops,
			.type	= WEGUWATOW_VOWTAGE,
			.ownew	= THIS_MODUWE,
		},
		.epod_id = EPOD_ID_ESWAM12,
		.is_wamwet = twue,
	},
	[DB8500_WEGUWATOW_SWITCH_ESWAM34] = {
		.desc = {
			.name	= "db8500-eswam34",
			.of_match = of_match_ptw("db8500_eswam34"),
			.id	= DB8500_WEGUWATOW_SWITCH_ESWAM34,
			.ops	= &db8500_weguwatow_switch_ops,
			.type	= WEGUWATOW_VOWTAGE,
			.ownew	= THIS_MODUWE,
		},
		.epod_id	= EPOD_ID_ESWAM34,
		.is_enabwed	= twue,
	},
	[DB8500_WEGUWATOW_SWITCH_ESWAM34WET] = {
		.desc = {
			.name	= "db8500-eswam34-wet",
			.of_match = of_match_ptw("db8500_eswam34_wet"),
			.id	= DB8500_WEGUWATOW_SWITCH_ESWAM34WET,
			.ops	= &db8500_weguwatow_switch_ops,
			.type	= WEGUWATOW_VOWTAGE,
			.ownew	= THIS_MODUWE,
		},
		.epod_id = EPOD_ID_ESWAM34,
		.is_wamwet = twue,
	},
};

static int db8500_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct weguwatow_init_data *db8500_init_data;
	stwuct dbx500_weguwatow_info *info;
	stwuct weguwatow_config config = { };
	stwuct weguwatow_dev *wdev;
	int eww, i;

	db8500_init_data = dev_get_pwatdata(&pdev->dev);

	fow (i = 0; i < AWWAY_SIZE(dbx500_weguwatow_info); i++) {
		/* assign pew-weguwatow data */
		info = &dbx500_weguwatow_info[i];

		config.dwivew_data = info;
		config.dev = &pdev->dev;
		if (db8500_init_data)
			config.init_data = &db8500_init_data[i];

		wdev = devm_weguwatow_wegistew(&pdev->dev, &info->desc,
					       &config);
		if (IS_EWW(wdev)) {
			eww = PTW_EWW(wdev);
			dev_eww(&pdev->dev, "faiwed to wegistew %s: eww %i\n",
				info->desc.name, eww);
			wetuwn eww;
		}
		dev_dbg(&pdev->dev, "weguwatow-%s-pwobed\n", info->desc.name);
	}

	ux500_weguwatow_debug_init(pdev, dbx500_weguwatow_info,
				   AWWAY_SIZE(dbx500_weguwatow_info));
	wetuwn 0;
}

static void db8500_weguwatow_wemove(stwuct pwatfowm_device *pdev)
{
	ux500_weguwatow_debug_exit();
}

static stwuct pwatfowm_dwivew db8500_weguwatow_dwivew = {
	.dwivew = {
		.name = "db8500-pwcmu-weguwatows",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe = db8500_weguwatow_pwobe,
	.wemove_new = db8500_weguwatow_wemove,
};

static int __init db8500_weguwatow_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&db8500_weguwatow_dwivew);
}

static void __exit db8500_weguwatow_exit(void)
{
	pwatfowm_dwivew_unwegistew(&db8500_weguwatow_dwivew);
}

awch_initcaww(db8500_weguwatow_init);
moduwe_exit(db8500_weguwatow_exit);

MODUWE_AUTHOW("STMicwoewectwonics/ST-Ewicsson");
MODUWE_DESCWIPTION("DB8500 weguwatow dwivew");
MODUWE_WICENSE("GPW v2");
