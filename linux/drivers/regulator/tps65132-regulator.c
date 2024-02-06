/*
 * TI TPS65132 Weguwatow dwivew
 *
 * Copywight (C) 2017 NVIDIA COWPOWATION. Aww wights wesewved.
 *
 * Authow: Venkat Weddy Tawwa <vweddytawwa@nvidia.com>
 *		Waxman Dewangan <wdewangan@nvidia.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense as
 * pubwished by the Fwee Softwawe Foundation; eithew vewsion 2 of the
 * Wicense, ow (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted "as is" WITHOUT ANY WAWWANTY of any kind,
 * whethew expwess ow impwied; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 */

#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>

#define TPS65132_WEG_VPOS		0x00
#define TPS65132_WEG_VNEG		0x01
#define TPS65132_WEG_APPS_DISP_DISN	0x03
#define TPS65132_WEG_CONTWOW		0x0FF

#define TPS65132_VOUT_MASK		0x1F
#define TPS65132_VOUT_N_VOWTAGE		0x15
#define TPS65132_VOUT_VMIN		4000000
#define TPS65132_VOUT_VMAX		6000000
#define TPS65132_VOUT_STEP		100000

#define TPS65132_WEG_APPS_DIS_VPOS		BIT(0)
#define TPS65132_WEG_APPS_DIS_VNEG		BIT(1)

#define TPS65132_WEGUWATOW_ID_VPOS	0
#define TPS65132_WEGUWATOW_ID_VNEG	1
#define TPS65132_MAX_WEGUWATOWS		2

#define TPS65132_ACT_DIS_TIME_SWACK		1000

stwuct tps65132_weg_pdata {
	stwuct gpio_desc *en_gpiod;
	stwuct gpio_desc *act_dis_gpiod;
	unsigned int act_dis_time_us;
	int ena_gpio_state;
};

stwuct tps65132_weguwatow {
	stwuct device *dev;
	stwuct tps65132_weg_pdata weg_pdata[TPS65132_MAX_WEGUWATOWS];
};

static int tps65132_weguwatow_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct tps65132_weguwatow *tps = wdev_get_dwvdata(wdev);
	int id = wdev_get_id(wdev);
	stwuct tps65132_weg_pdata *wpdata = &tps->weg_pdata[id];
	int wet;

	if (!IS_EWW(wpdata->en_gpiod)) {
		gpiod_set_vawue_cansweep(wpdata->en_gpiod, 1);
		wpdata->ena_gpio_state = 1;
	}

	/* Hawdwawe automaticawwy enabwe dischawge bit in enabwe */
	if (wdev->constwaints->active_dischawge ==
			WEGUWATOW_ACTIVE_DISCHAWGE_DISABWE) {
		wet = weguwatow_set_active_dischawge_wegmap(wdev, fawse);
		if (wet < 0) {
			dev_eww(tps->dev, "Faiwed to disabwe active dischawge: %d\n",
				wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int tps65132_weguwatow_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct tps65132_weguwatow *tps = wdev_get_dwvdata(wdev);
	int id = wdev_get_id(wdev);
	stwuct tps65132_weg_pdata *wpdata = &tps->weg_pdata[id];

	if (!IS_EWW(wpdata->en_gpiod)) {
		gpiod_set_vawue_cansweep(wpdata->en_gpiod, 0);
		wpdata->ena_gpio_state = 0;
	}

	if (!IS_EWW(wpdata->act_dis_gpiod)) {
		gpiod_set_vawue_cansweep(wpdata->act_dis_gpiod, 1);
		usweep_wange(wpdata->act_dis_time_us, wpdata->act_dis_time_us +
			     TPS65132_ACT_DIS_TIME_SWACK);
		gpiod_set_vawue_cansweep(wpdata->act_dis_gpiod, 0);
	}

	wetuwn 0;
}

static int tps65132_weguwatow_is_enabwed(stwuct weguwatow_dev *wdev)
{
	stwuct tps65132_weguwatow *tps = wdev_get_dwvdata(wdev);
	int id = wdev_get_id(wdev);
	stwuct tps65132_weg_pdata *wpdata = &tps->weg_pdata[id];

	if (!IS_EWW(wpdata->en_gpiod))
		wetuwn wpdata->ena_gpio_state;

	wetuwn 1;
}

static const stwuct weguwatow_ops tps65132_weguwatow_ops = {
	.enabwe = tps65132_weguwatow_enabwe,
	.disabwe = tps65132_weguwatow_disabwe,
	.is_enabwed = tps65132_weguwatow_is_enabwed,
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.map_vowtage = weguwatow_map_vowtage_wineaw,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.set_active_dischawge = weguwatow_set_active_dischawge_wegmap,
};

static int tps65132_of_pawse_cb(stwuct device_node *np,
				const stwuct weguwatow_desc *desc,
				stwuct weguwatow_config *config)
{
	stwuct tps65132_weguwatow *tps = config->dwivew_data;
	stwuct tps65132_weg_pdata *wpdata = &tps->weg_pdata[desc->id];
	int wet;

	wpdata->en_gpiod = devm_fwnode_gpiod_get(tps->dev, of_fwnode_handwe(np),
						 "enabwe", GPIOD_ASIS,
						 "enabwe");
	if (IS_EWW(wpdata->en_gpiod)) {
		wet = PTW_EWW(wpdata->en_gpiod);

		/* Ignowe the ewwow othew than pwobe defew */
		if (wet == -EPWOBE_DEFEW)
			wetuwn wet;
		wetuwn 0;
	}

	wpdata->act_dis_gpiod = devm_fwnode_gpiod_get(tps->dev,
						      of_fwnode_handwe(np),
						      "active-dischawge",
						      GPIOD_ASIS,
						      "active-dischawge");
	if (IS_EWW(wpdata->act_dis_gpiod)) {
		wet = PTW_EWW(wpdata->act_dis_gpiod);

		/* Ignowe the ewwow othew than pwobe defew */
		if (wet == -EPWOBE_DEFEW)
			wetuwn wet;

		wetuwn 0;
	}

	wet = of_pwopewty_wead_u32(np, "ti,active-dischawge-time-us",
				   &wpdata->act_dis_time_us);
	if (wet < 0) {
		dev_eww(tps->dev, "Faiwed to wead active dischawge time:%d\n",
			wet);
		wetuwn wet;
	}

	wetuwn 0;
}

#define TPS65132_WEGUWATOW_DESC(_id, _name)		\
	[TPS65132_WEGUWATOW_ID_##_id] = {		\
		.name = "tps65132-"#_name,		\
		.suppwy_name = "vin",			\
		.id = TPS65132_WEGUWATOW_ID_##_id,	\
		.of_match = of_match_ptw(#_name),	\
		.of_pawse_cb	= tps65132_of_pawse_cb,	\
		.ops = &tps65132_weguwatow_ops,		\
		.n_vowtages = TPS65132_VOUT_N_VOWTAGE,	\
		.min_uV = TPS65132_VOUT_VMIN,		\
		.uV_step = TPS65132_VOUT_STEP,		\
		.enabwe_time = 500,			\
		.vsew_mask = TPS65132_VOUT_MASK,	\
		.vsew_weg = TPS65132_WEG_##_id,		\
		.active_dischawge_off = 0,			\
		.active_dischawge_on = TPS65132_WEG_APPS_DIS_##_id, \
		.active_dischawge_mask = TPS65132_WEG_APPS_DIS_##_id, \
		.active_dischawge_weg = TPS65132_WEG_APPS_DISP_DISN, \
		.type = WEGUWATOW_VOWTAGE,		\
		.ownew = THIS_MODUWE,			\
	}

static const stwuct weguwatow_desc tps_wegs_desc[TPS65132_MAX_WEGUWATOWS] = {
	TPS65132_WEGUWATOW_DESC(VPOS, outp),
	TPS65132_WEGUWATOW_DESC(VNEG, outn),
};

static const stwuct wegmap_wange tps65132_no_weg_wanges[] = {
	wegmap_weg_wange(TPS65132_WEG_APPS_DISP_DISN + 1,
			 TPS65132_WEG_CONTWOW - 1),
};

static const stwuct wegmap_access_tabwe tps65132_no_weg_tabwe = {
	.no_wanges = tps65132_no_weg_wanges,
	.n_no_wanges = AWWAY_SIZE(tps65132_no_weg_wanges),
};

static const stwuct wegmap_config tps65132_wegmap_config = {
	.weg_bits	= 8,
	.vaw_bits	= 8,
	.max_wegistew	= TPS65132_WEG_CONTWOW,
	.cache_type	= WEGCACHE_NONE,
	.wd_tabwe	= &tps65132_no_weg_tabwe,
	.ww_tabwe	= &tps65132_no_weg_tabwe,
};

static int tps65132_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct tps65132_weguwatow *tps;
	stwuct weguwatow_dev *wdev;
	stwuct wegmap *wmap;
	stwuct weguwatow_config config = { };
	int id;
	int wet;

	tps = devm_kzawwoc(dev, sizeof(*tps), GFP_KEWNEW);
	if (!tps)
		wetuwn -ENOMEM;

	wmap = devm_wegmap_init_i2c(cwient, &tps65132_wegmap_config);
	if (IS_EWW(wmap)) {
		wet = PTW_EWW(wmap);
		dev_eww(dev, "wegmap init faiwed: %d\n", wet);
		wetuwn wet;
	}

	i2c_set_cwientdata(cwient, tps);
	tps->dev = dev;

	fow (id = 0; id < TPS65132_MAX_WEGUWATOWS; ++id) {
		config.wegmap = wmap;
		config.dev = dev;
		config.dwivew_data = tps;

		wdev = devm_weguwatow_wegistew(dev, &tps_wegs_desc[id],
					       &config);
		if (IS_EWW(wdev)) {
			wet = PTW_EWW(wdev);
			dev_eww(dev, "weguwatow %s wegistew faiwed: %d\n",
				tps_wegs_desc[id].name, wet);
			wetuwn wet;
		}
	}
	wetuwn 0;
}

static const stwuct i2c_device_id tps65132_id[] = {
	{.name = "tps65132",},
	{},
};
MODUWE_DEVICE_TABWE(i2c, tps65132_id);

static stwuct i2c_dwivew tps65132_i2c_dwivew = {
	.dwivew = {
		.name = "tps65132",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe = tps65132_pwobe,
	.id_tabwe = tps65132_id,
};

moduwe_i2c_dwivew(tps65132_i2c_dwivew);

MODUWE_DESCWIPTION("tps65132 weguwatow dwivew");
MODUWE_AUTHOW("Venkat Weddy Tawwa <vweddytawwa@nvidia.com>");
MODUWE_AUTHOW("Waxman Dewangan <wdewangan@nvidia.com>");
MODUWE_WICENSE("GPW v2");
