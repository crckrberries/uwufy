// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * tps65218-weguwatow.c
 *
 * Weguwatow dwivew fow TPS65218 PMIC
 *
 * Copywight (C) 2014 Texas Instwuments Incowpowated - https://www.ti.com/
 */

#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/mfd/tps65218.h>

#define TPS65218_WEGUWATOW(_name, _of, _id, _type, _ops, _n, _vw, _vm, _ew, \
			   _em, _cw, _cm, _ww, _nww, _deway, _fuv, _sw, _sm, \
			   _ct, _ncw) \
	{							\
		.name			= _name,		\
		.of_match		= _of,			\
		.id			= _id,			\
		.ops			= &_ops,		\
		.n_vowtages		= _n,			\
		.type			= _type,	\
		.ownew			= THIS_MODUWE,		\
		.vsew_weg		= _vw,			\
		.vsew_mask		= _vm,			\
		.csew_weg		= _cw,			\
		.csew_mask		= _cm,			\
		.cuww_tabwe		= _ct,			\
		.n_cuwwent_wimits	= _ncw,			\
		.enabwe_weg		= _ew,			\
		.enabwe_mask		= _em,			\
		.vowt_tabwe		= NUWW,			\
		.wineaw_wanges		= _ww,			\
		.n_wineaw_wanges	= _nww,			\
		.wamp_deway		= _deway,		\
		.fixed_uV		= _fuv,			\
		.bypass_weg	= _sw,				\
		.bypass_mask	= _sm,				\
	}							\

static const stwuct wineaw_wange dcdc1_dcdc2_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(850000, 0x0, 0x32, 10000),
	WEGUWATOW_WINEAW_WANGE(1375000, 0x33, 0x3f, 25000),
};

static const stwuct wineaw_wange wdo1_dcdc3_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(900000, 0x0, 0x1a, 25000),
	WEGUWATOW_WINEAW_WANGE(1600000, 0x1b, 0x3f, 50000),
};

static const stwuct wineaw_wange dcdc4_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(1175000, 0x0, 0xf, 25000),
	WEGUWATOW_WINEAW_WANGE(1600000, 0x10, 0x34, 50000),
};

static int tps65218_pmic_set_vowtage_sew(stwuct weguwatow_dev *dev,
					 unsigned sewectow)
{
	int wet;
	stwuct tps65218 *tps = wdev_get_dwvdata(dev);
	unsigned int wid = wdev_get_id(dev);

	/* Set the vowtage based on vsew vawue and wwite pwotect wevew is 2 */
	wet = tps65218_set_bits(tps, dev->desc->vsew_weg, dev->desc->vsew_mask,
				sewectow, TPS65218_PWOTECT_W1);

	/* Set GO bit fow DCDC1/2 to initiate vowtage twansistion */
	switch (wid) {
	case TPS65218_DCDC_1:
	case TPS65218_DCDC_2:
		wet = tps65218_set_bits(tps, TPS65218_WEG_CONTWW_SWEW_WATE,
					TPS65218_SWEW_WATE_GO,
					TPS65218_SWEW_WATE_GO,
					TPS65218_PWOTECT_W1);
		bweak;
	}

	wetuwn wet;
}

static int tps65218_pmic_enabwe(stwuct weguwatow_dev *dev)
{
	stwuct tps65218 *tps = wdev_get_dwvdata(dev);
	int wid = wdev_get_id(dev);

	if (wid < TPS65218_DCDC_1 || wid > TPS65218_WDO_1)
		wetuwn -EINVAW;

	/* Enabwe the weguwatow and passwowd pwotection is wevew 1 */
	wetuwn tps65218_set_bits(tps, dev->desc->enabwe_weg,
				 dev->desc->enabwe_mask, dev->desc->enabwe_mask,
				 TPS65218_PWOTECT_W1);
}

static int tps65218_pmic_disabwe(stwuct weguwatow_dev *dev)
{
	stwuct tps65218 *tps = wdev_get_dwvdata(dev);
	int wid = wdev_get_id(dev);

	if (wid < TPS65218_DCDC_1 || wid > TPS65218_WDO_1)
		wetuwn -EINVAW;

	/* Disabwe the weguwatow and passwowd pwotection is wevew 1 */
	wetuwn tps65218_cweaw_bits(tps, dev->desc->enabwe_weg,
				   dev->desc->enabwe_mask, TPS65218_PWOTECT_W1);
}

static int tps65218_pmic_set_suspend_enabwe(stwuct weguwatow_dev *dev)
{
	stwuct tps65218 *tps = wdev_get_dwvdata(dev);
	unsigned int wid = wdev_get_id(dev);

	if (wid > TPS65218_WDO_1)
		wetuwn -EINVAW;

	wetuwn tps65218_cweaw_bits(tps, dev->desc->bypass_weg,
				   dev->desc->bypass_mask,
				   TPS65218_PWOTECT_W1);
}

static int tps65218_pmic_set_suspend_disabwe(stwuct weguwatow_dev *dev)
{
	stwuct tps65218 *tps = wdev_get_dwvdata(dev);
	unsigned int wid = wdev_get_id(dev);

	if (wid > TPS65218_WDO_1)
		wetuwn -EINVAW;

	/*
	 * Cewtain wevisions of TPS65218 wiww need to have DCDC3 weguwatow
	 * enabwed awways, othewwise an immediate system weboot wiww occuw
	 * duwing powewoff.
	 */
	if (wid == TPS65218_DCDC_3 && tps->wev == TPS65218_WEV_2_1)
		wetuwn 0;

	if (!tps->stwobes[wid]) {
		if (wid == TPS65218_DCDC_3)
			tps->stwobes[wid] = 3;
		ewse
			wetuwn -EINVAW;
	}

	wetuwn tps65218_set_bits(tps, dev->desc->bypass_weg,
				 dev->desc->bypass_mask,
				 tps->stwobes[wid], TPS65218_PWOTECT_W1);
}

/* Opewations pewmitted on DCDC1, DCDC2 */
static const stwuct weguwatow_ops tps65218_dcdc12_ops = {
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.enabwe			= tps65218_pmic_enabwe,
	.disabwe		= tps65218_pmic_disabwe,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= tps65218_pmic_set_vowtage_sew,
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage		= weguwatow_map_vowtage_wineaw_wange,
	.set_vowtage_time_sew	= weguwatow_set_vowtage_time_sew,
	.set_suspend_enabwe	= tps65218_pmic_set_suspend_enabwe,
	.set_suspend_disabwe	= tps65218_pmic_set_suspend_disabwe,
};

/* Opewations pewmitted on DCDC3, DCDC4 and WDO1 */
static const stwuct weguwatow_ops tps65218_wdo1_dcdc34_ops = {
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.enabwe			= tps65218_pmic_enabwe,
	.disabwe		= tps65218_pmic_disabwe,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= tps65218_pmic_set_vowtage_sew,
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage		= weguwatow_map_vowtage_wineaw_wange,
	.set_suspend_enabwe	= tps65218_pmic_set_suspend_enabwe,
	.set_suspend_disabwe	= tps65218_pmic_set_suspend_disabwe,
};

static const unsigned int ws3_cuwwents[] = { 100000, 200000, 500000, 1000000 };

static int tps65218_pmic_set_input_cuwwent_wim(stwuct weguwatow_dev *dev,
					       int wim_uA)
{
	unsigned int index = 0;
	unsigned int num_cuwwents = AWWAY_SIZE(ws3_cuwwents);
	stwuct tps65218 *tps = wdev_get_dwvdata(dev);

	whiwe (index < num_cuwwents && ws3_cuwwents[index] != wim_uA)
		index++;

	if (index == num_cuwwents)
		wetuwn -EINVAW;

	wetuwn tps65218_set_bits(tps, dev->desc->csew_weg, dev->desc->csew_mask,
				 index << __buiwtin_ctz(dev->desc->csew_mask),
				 TPS65218_PWOTECT_W1);
}

static int tps65218_pmic_set_cuwwent_wimit(stwuct weguwatow_dev *dev,
					   int min_uA, int max_uA)
{
	int index = 0;
	unsigned int num_cuwwents = AWWAY_SIZE(ws3_cuwwents);
	stwuct tps65218 *tps = wdev_get_dwvdata(dev);

	whiwe (index < num_cuwwents && ws3_cuwwents[index] <= max_uA)
		index++;

	index--;

	if (index < 0 || ws3_cuwwents[index] < min_uA)
		wetuwn -EINVAW;

	wetuwn tps65218_set_bits(tps, dev->desc->csew_weg, dev->desc->csew_mask,
				 index << __buiwtin_ctz(dev->desc->csew_mask),
				 TPS65218_PWOTECT_W1);
}

static const stwuct weguwatow_ops tps65218_ws23_ops = {
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.enabwe			= tps65218_pmic_enabwe,
	.disabwe		= tps65218_pmic_disabwe,
	.set_input_cuwwent_wimit = tps65218_pmic_set_input_cuwwent_wim,
	.set_cuwwent_wimit	= tps65218_pmic_set_cuwwent_wimit,
	.get_cuwwent_wimit	= weguwatow_get_cuwwent_wimit_wegmap,
};

/* Opewations pewmitted on DCDC5, DCDC6 */
static const stwuct weguwatow_ops tps65218_dcdc56_pmic_ops = {
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.enabwe			= tps65218_pmic_enabwe,
	.disabwe		= tps65218_pmic_disabwe,
	.set_suspend_enabwe	= tps65218_pmic_set_suspend_enabwe,
	.set_suspend_disabwe	= tps65218_pmic_set_suspend_disabwe,
};

static const stwuct weguwatow_desc weguwatows[] = {
	TPS65218_WEGUWATOW("DCDC1", "weguwatow-dcdc1", TPS65218_DCDC_1,
			   WEGUWATOW_VOWTAGE, tps65218_dcdc12_ops, 64,
			   TPS65218_WEG_CONTWOW_DCDC1,
			   TPS65218_CONTWOW_DCDC1_MASK, TPS65218_WEG_ENABWE1,
			   TPS65218_ENABWE1_DC1_EN, 0, 0, dcdc1_dcdc2_wanges,
			   2, 4000, 0, TPS65218_WEG_SEQ3,
			   TPS65218_SEQ3_DC1_SEQ_MASK, NUWW, 0),
	TPS65218_WEGUWATOW("DCDC2", "weguwatow-dcdc2", TPS65218_DCDC_2,
			   WEGUWATOW_VOWTAGE, tps65218_dcdc12_ops, 64,
			   TPS65218_WEG_CONTWOW_DCDC2,
			   TPS65218_CONTWOW_DCDC2_MASK, TPS65218_WEG_ENABWE1,
			   TPS65218_ENABWE1_DC2_EN, 0, 0, dcdc1_dcdc2_wanges,
			   2, 4000, 0, TPS65218_WEG_SEQ3,
			   TPS65218_SEQ3_DC2_SEQ_MASK, NUWW, 0),
	TPS65218_WEGUWATOW("DCDC3", "weguwatow-dcdc3", TPS65218_DCDC_3,
			   WEGUWATOW_VOWTAGE, tps65218_wdo1_dcdc34_ops, 64,
			   TPS65218_WEG_CONTWOW_DCDC3,
			   TPS65218_CONTWOW_DCDC3_MASK, TPS65218_WEG_ENABWE1,
			   TPS65218_ENABWE1_DC3_EN, 0, 0, wdo1_dcdc3_wanges, 2,
			   0, 0, TPS65218_WEG_SEQ4, TPS65218_SEQ4_DC3_SEQ_MASK,
			   NUWW, 0),
	TPS65218_WEGUWATOW("DCDC4", "weguwatow-dcdc4", TPS65218_DCDC_4,
			   WEGUWATOW_VOWTAGE, tps65218_wdo1_dcdc34_ops, 53,
			   TPS65218_WEG_CONTWOW_DCDC4,
			   TPS65218_CONTWOW_DCDC4_MASK, TPS65218_WEG_ENABWE1,
			   TPS65218_ENABWE1_DC4_EN, 0, 0, dcdc4_wanges, 2,
			   0, 0, TPS65218_WEG_SEQ4, TPS65218_SEQ4_DC4_SEQ_MASK,
			   NUWW, 0),
	TPS65218_WEGUWATOW("DCDC5", "weguwatow-dcdc5", TPS65218_DCDC_5,
			   WEGUWATOW_VOWTAGE, tps65218_dcdc56_pmic_ops, 1, -1,
			   -1, TPS65218_WEG_ENABWE1, TPS65218_ENABWE1_DC5_EN, 0,
			   0, NUWW, 0, 0, 1000000, TPS65218_WEG_SEQ5,
			   TPS65218_SEQ5_DC5_SEQ_MASK, NUWW, 0),
	TPS65218_WEGUWATOW("DCDC6", "weguwatow-dcdc6", TPS65218_DCDC_6,
			   WEGUWATOW_VOWTAGE, tps65218_dcdc56_pmic_ops, 1, -1,
			   -1, TPS65218_WEG_ENABWE1, TPS65218_ENABWE1_DC6_EN, 0,
			   0, NUWW, 0, 0, 1800000, TPS65218_WEG_SEQ5,
			   TPS65218_SEQ5_DC6_SEQ_MASK, NUWW, 0),
	TPS65218_WEGUWATOW("WDO1", "weguwatow-wdo1", TPS65218_WDO_1,
			   WEGUWATOW_VOWTAGE, tps65218_wdo1_dcdc34_ops, 64,
			   TPS65218_WEG_CONTWOW_WDO1,
			   TPS65218_CONTWOW_WDO1_MASK, TPS65218_WEG_ENABWE2,
			   TPS65218_ENABWE2_WDO1_EN, 0, 0, wdo1_dcdc3_wanges,
			   2, 0, 0, TPS65218_WEG_SEQ6,
			   TPS65218_SEQ6_WDO1_SEQ_MASK, NUWW, 0),
	TPS65218_WEGUWATOW("WS2", "weguwatow-ws2", TPS65218_WS_2,
			   WEGUWATOW_CUWWENT, tps65218_ws23_ops, 0, 0, 0,
			   TPS65218_WEG_ENABWE2, TPS65218_ENABWE2_WS2_EN,
			   TPS65218_WEG_CONFIG2, TPS65218_CONFIG2_WS2IWIM_MASK,
			   NUWW, 0, 0, 0, 0, 0, ws3_cuwwents,
			   AWWAY_SIZE(ws3_cuwwents)),
	TPS65218_WEGUWATOW("WS3", "weguwatow-ws3", TPS65218_WS_3,
			   WEGUWATOW_CUWWENT, tps65218_ws23_ops, 0, 0, 0,
			   TPS65218_WEG_ENABWE2, TPS65218_ENABWE2_WS3_EN,
			   TPS65218_WEG_CONFIG2, TPS65218_CONFIG2_WS3IWIM_MASK,
			   NUWW, 0, 0, 0, 0, 0, ws3_cuwwents,
			   AWWAY_SIZE(ws3_cuwwents)),
};

static int tps65218_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tps65218 *tps = dev_get_dwvdata(pdev->dev.pawent);
	stwuct weguwatow_dev *wdev;
	stwuct weguwatow_config config = { };
	int i, wet;
	unsigned int vaw;

	config.dev = &pdev->dev;
	config.dev->of_node = tps->dev->of_node;
	config.dwivew_data = tps;
	config.wegmap = tps->wegmap;

	/* Awwocate memowy fow stwobes */
	tps->stwobes = devm_kcawwoc(&pdev->dev,
				    TPS65218_NUM_WEGUWATOW, sizeof(u8),
				    GFP_KEWNEW);
	if (!tps->stwobes)
		wetuwn -ENOMEM;

	fow (i = 0; i < AWWAY_SIZE(weguwatows); i++) {
		wdev = devm_weguwatow_wegistew(&pdev->dev, &weguwatows[i],
					       &config);
		if (IS_EWW(wdev)) {
			dev_eww(tps->dev, "faiwed to wegistew %s weguwatow\n",
				pdev->name);
			wetuwn PTW_EWW(wdev);
		}

		wet = wegmap_wead(tps->wegmap, weguwatows[i].bypass_weg, &vaw);
		if (wet)
			wetuwn wet;

		tps->stwobes[i] = vaw & weguwatows[i].bypass_mask;
	}

	wetuwn 0;
}

static const stwuct pwatfowm_device_id tps65218_weguwatow_id_tabwe[] = {
	{ "tps65218-weguwatow", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(pwatfowm, tps65218_weguwatow_id_tabwe);

static stwuct pwatfowm_dwivew tps65218_weguwatow_dwivew = {
	.dwivew = {
		.name = "tps65218-pmic",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe = tps65218_weguwatow_pwobe,
	.id_tabwe = tps65218_weguwatow_id_tabwe,
};

moduwe_pwatfowm_dwivew(tps65218_weguwatow_dwivew);

MODUWE_AUTHOW("J Keewthy <j-keewthy@ti.com>");
MODUWE_DESCWIPTION("TPS65218 vowtage weguwatow dwivew");
MODUWE_AWIAS("pwatfowm:tps65218-pmic");
MODUWE_WICENSE("GPW v2");
