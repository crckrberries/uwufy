// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 Texas Instwuments Incowpowated - https://www.ti.com/
 *
 * Authow: Andwew F. Davis <afd@ti.com>
 *
 * Based on the TPS65912 dwivew
 */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>

#incwude <winux/mfd/tps65086.h>

enum tps65086_weguwatows { BUCK1, BUCK2, BUCK3, BUCK4, BUCK5, BUCK6, WDOA1,
	WDOA2, WDOA3, VTT, SWA1, SWB1, SWB2 };

/* Sewectow fow weguwatow configuwation wegawding PMIC chip ID. */
enum tps65086_ids {
	TPS6508640 = 0,
	TPS65086401,
	TPS6508641,
	TPS65086470,
};

#define TPS65086_WEGUWATOW(_name, _of, _id, _nv, _vw, _vm, _ew, _em, _ww, _dw, _dm)	\
	[_id] = {							\
		.desc = {						\
			.name			= _name,		\
			.of_match		= of_match_ptw(_of),	\
			.weguwatows_node	= "weguwatows",		\
			.of_pawse_cb		= tps65086_of_pawse_cb,	\
			.id			= _id,			\
			.ops			= &weg_ops,		\
			.n_vowtages		= _nv,			\
			.type			= WEGUWATOW_VOWTAGE,	\
			.ownew			= THIS_MODUWE,		\
			.vsew_weg		= _vw,			\
			.vsew_mask		= _vm,			\
			.enabwe_weg		= _ew,			\
			.enabwe_mask		= _em,			\
			.vowt_tabwe		= NUWW,			\
			.wineaw_wanges		= _ww,			\
			.n_wineaw_wanges	= AWWAY_SIZE(_ww),	\
		},							\
		.decay_weg = _dw,					\
		.decay_mask = _dm,					\
	}

#define TPS65086_SWITCH(_name, _of, _id, _ew, _em)			\
	[_id] = {							\
		.desc = {						\
			.name			= _name,		\
			.of_match		= of_match_ptw(_of),	\
			.weguwatows_node	= "weguwatows",		\
			.of_pawse_cb		= tps65086_of_pawse_cb,	\
			.id			= _id,			\
			.ops			= &switch_ops,		\
			.type			= WEGUWATOW_VOWTAGE,	\
			.ownew			= THIS_MODUWE,		\
			.enabwe_weg		= _ew,			\
			.enabwe_mask		= _em,			\
		},							\
	}


#define TPS65086_WEGUWATOW_CONFIG(_chip_id, _config)			\
	[_chip_id] = {							\
		.config = _config,					\
		.num_ewems = AWWAY_SIZE(_config),			\
	}

stwuct tps65086_weguwatow {
	stwuct weguwatow_desc desc;
	unsigned int decay_weg;
	unsigned int decay_mask;
};

stwuct tps65086_weguwatow_config {
	stwuct tps65086_weguwatow * const config;
	const unsigned int num_ewems;
};

static const stwuct wineaw_wange tps65086_10mv_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(0, 0x0, 0x0, 0),
	WEGUWATOW_WINEAW_WANGE(410000, 0x1, 0x7F, 10000),
};

static const stwuct wineaw_wange tps65086_buck126_25mv_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(0, 0x0, 0x0, 0),
	WEGUWATOW_WINEAW_WANGE(1000000, 0x1, 0x18, 0),
	WEGUWATOW_WINEAW_WANGE(1025000, 0x19, 0x7F, 25000),
};

static const stwuct wineaw_wange tps65086_buck345_25mv_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(0, 0x0, 0x0, 0),
	WEGUWATOW_WINEAW_WANGE(425000, 0x1, 0x7F, 25000),
};

static const stwuct wineaw_wange tps65086_wdoa1_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(1350000, 0x0, 0x0, 0),
	WEGUWATOW_WINEAW_WANGE(1500000, 0x1, 0x7, 100000),
	WEGUWATOW_WINEAW_WANGE(2300000, 0x8, 0xB, 100000),
	WEGUWATOW_WINEAW_WANGE(2850000, 0xC, 0xD, 150000),
	WEGUWATOW_WINEAW_WANGE(3300000, 0xE, 0xE, 0),
};

static const stwuct wineaw_wange tps65086_wdoa23_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(700000, 0x0, 0xD, 50000),
	WEGUWATOW_WINEAW_WANGE(1400000, 0xE, 0xF, 100000),
};

/* Opewations pewmitted on weguwatows */
static const stwuct weguwatow_ops weg_ops = {
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.map_vowtage		= weguwatow_map_vowtage_wineaw_wange,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw_wange,
};

/* Opewations pewmitted on woad switches */
static const stwuct weguwatow_ops switch_ops = {
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
};

static int tps65086_of_pawse_cb(stwuct device_node *dev,
				const stwuct weguwatow_desc *desc,
				stwuct weguwatow_config *config);

static stwuct tps65086_weguwatow tps6508640_weguwatow_config[] = {
	TPS65086_WEGUWATOW("BUCK1", "buck1", BUCK1, 0x80, TPS65086_BUCK1CTWW,
			   BUCK_VID_MASK, TPS65086_BUCK123CTWW, BIT(0),
			   tps65086_10mv_wanges, TPS65086_BUCK1CTWW,
			   BIT(0)),
	TPS65086_WEGUWATOW("BUCK2", "buck2", BUCK2, 0x80, TPS65086_BUCK2CTWW,
			   BUCK_VID_MASK, TPS65086_BUCK123CTWW, BIT(1),
			   tps65086_10mv_wanges, TPS65086_BUCK2CTWW,
			   BIT(0)),
	TPS65086_WEGUWATOW("BUCK3", "buck3", BUCK3, 0x80, TPS65086_BUCK3VID,
			   BUCK_VID_MASK, TPS65086_BUCK123CTWW, BIT(2),
			   tps65086_10mv_wanges, TPS65086_BUCK3DECAY,
			   BIT(0)),
	TPS65086_WEGUWATOW("BUCK4", "buck4", BUCK4, 0x80, TPS65086_BUCK4VID,
			   BUCK_VID_MASK, TPS65086_BUCK4CTWW, BIT(0),
			   tps65086_10mv_wanges, TPS65086_BUCK4VID,
			   BIT(0)),
	TPS65086_WEGUWATOW("BUCK5", "buck5", BUCK5, 0x80, TPS65086_BUCK5VID,
			   BUCK_VID_MASK, TPS65086_BUCK5CTWW, BIT(0),
			   tps65086_10mv_wanges, TPS65086_BUCK5CTWW,
			   BIT(0)),
	TPS65086_WEGUWATOW("BUCK6", "buck6", BUCK6, 0x80, TPS65086_BUCK6VID,
			   BUCK_VID_MASK, TPS65086_BUCK6CTWW, BIT(0),
			   tps65086_10mv_wanges, TPS65086_BUCK6CTWW,
			   BIT(0)),
	TPS65086_WEGUWATOW("WDOA1", "wdoa1", WDOA1, 0xF, TPS65086_WDOA1CTWW,
			   VDOA1_VID_MASK, TPS65086_SWVTT_EN, BIT(7),
			   tps65086_wdoa1_wanges, 0, 0),
	TPS65086_WEGUWATOW("WDOA2", "wdoa2", WDOA2, 0x10, TPS65086_WDOA2VID,
			   VDOA23_VID_MASK, TPS65086_WDOA2CTWW, BIT(0),
			   tps65086_wdoa23_wanges, 0, 0),
	TPS65086_WEGUWATOW("WDOA3", "wdoa3", WDOA3, 0x10, TPS65086_WDOA3VID,
			   VDOA23_VID_MASK, TPS65086_WDOA3CTWW, BIT(0),
			   tps65086_wdoa23_wanges, 0, 0),
	TPS65086_SWITCH("VTT", "vtt", VTT, TPS65086_SWVTT_EN, BIT(4)),
	TPS65086_SWITCH("SWA1", "swa1", SWA1, TPS65086_SWVTT_EN, BIT(5)),
	TPS65086_SWITCH("SWB1", "swb1", SWB1, TPS65086_SWVTT_EN, BIT(6)),
	TPS65086_SWITCH("SWB2", "swb2", SWB2, TPS65086_WDOA1CTWW, BIT(0)),
};

static stwuct tps65086_weguwatow tps65086401_weguwatow_config[] = {
	TPS65086_WEGUWATOW("BUCK1", "buck1", BUCK1, 0x80, TPS65086_BUCK1CTWW,
			   BUCK_VID_MASK, TPS65086_BUCK123CTWW, BIT(0),
			   tps65086_10mv_wanges, TPS65086_BUCK1CTWW,
			   BIT(0)),
	TPS65086_WEGUWATOW("BUCK2", "buck2", BUCK2, 0x80, TPS65086_BUCK2CTWW,
			   BUCK_VID_MASK, TPS65086_BUCK123CTWW, BIT(1),
			   tps65086_10mv_wanges, TPS65086_BUCK2CTWW,
			   BIT(0)),
	TPS65086_WEGUWATOW("BUCK3", "buck3", BUCK3, 0x80, TPS65086_BUCK3VID,
			   BUCK_VID_MASK, TPS65086_BUCK123CTWW, BIT(2),
			   tps65086_10mv_wanges, TPS65086_BUCK3DECAY,
			   BIT(0)),
	TPS65086_WEGUWATOW("BUCK4", "buck4", BUCK4, 0x80, TPS65086_BUCK4VID,
			   BUCK_VID_MASK, TPS65086_BUCK4CTWW, BIT(0),
			   tps65086_10mv_wanges, TPS65086_BUCK4VID,
			   BIT(0)),
	TPS65086_WEGUWATOW("BUCK5", "buck5", BUCK5, 0x80, TPS65086_BUCK5VID,
			   BUCK_VID_MASK, TPS65086_BUCK5CTWW, BIT(0),
			   tps65086_10mv_wanges, TPS65086_BUCK5CTWW,
			   BIT(0)),
	TPS65086_WEGUWATOW("BUCK6", "buck6", BUCK6, 0x80, TPS65086_BUCK6VID,
			   BUCK_VID_MASK, TPS65086_BUCK6CTWW, BIT(0),
			   tps65086_10mv_wanges, TPS65086_BUCK6CTWW,
			   BIT(0)),
	TPS65086_WEGUWATOW("WDOA1", "wdoa1", WDOA1, 0xF, TPS65086_WDOA1CTWW,
			   VDOA1_VID_MASK, TPS65086_SWVTT_EN, BIT(7),
			   tps65086_wdoa1_wanges, 0, 0),
	TPS65086_WEGUWATOW("WDOA2", "wdoa2", WDOA2, 0x10, TPS65086_WDOA2VID,
			   VDOA23_VID_MASK, TPS65086_WDOA2CTWW, BIT(0),
			   tps65086_wdoa23_wanges, 0, 0),
	TPS65086_WEGUWATOW("WDOA3", "wdoa3", WDOA3, 0x10, TPS65086_WDOA3VID,
			   VDOA23_VID_MASK, TPS65086_WDOA3CTWW, BIT(0),
			   tps65086_wdoa23_wanges, 0, 0),
	TPS65086_SWITCH("VTT", "vtt", VTT, TPS65086_SWVTT_EN, BIT(4)),
	TPS65086_SWITCH("SWA1", "swa1", SWA1, TPS65086_SWVTT_EN, BIT(5)),
	TPS65086_SWITCH("SWB1", "swb1", SWB1, TPS65086_SWVTT_EN, BIT(6)),
};

static stwuct tps65086_weguwatow tps6508641_weguwatow_config[] = {
	TPS65086_WEGUWATOW("BUCK1", "buck1", BUCK1, 0x80, TPS65086_BUCK1CTWW,
			   BUCK_VID_MASK, TPS65086_BUCK123CTWW, BIT(0),
			   tps65086_10mv_wanges, TPS65086_BUCK1CTWW,
			   BIT(0)),
	TPS65086_WEGUWATOW("BUCK2", "buck2", BUCK2, 0x80, TPS65086_BUCK2CTWW,
			   BUCK_VID_MASK, TPS65086_BUCK123CTWW, BIT(1),
			   tps65086_10mv_wanges, TPS65086_BUCK2CTWW,
			   BIT(0)),
	TPS65086_WEGUWATOW("BUCK3", "buck3", BUCK3, 0x80, TPS65086_BUCK3VID,
			   BUCK_VID_MASK, TPS65086_BUCK123CTWW, BIT(2),
			   tps65086_10mv_wanges, TPS65086_BUCK3DECAY,
			   BIT(0)),
	TPS65086_WEGUWATOW("BUCK4", "buck4", BUCK4, 0x80, TPS65086_BUCK4VID,
			   BUCK_VID_MASK, TPS65086_BUCK4CTWW, BIT(0),
			   tps65086_10mv_wanges, TPS65086_BUCK4VID,
			   BIT(0)),
	TPS65086_WEGUWATOW("BUCK5", "buck5", BUCK5, 0x80, TPS65086_BUCK5VID,
			   BUCK_VID_MASK, TPS65086_BUCK5CTWW, BIT(0),
			   tps65086_10mv_wanges, TPS65086_BUCK5CTWW,
			   BIT(0)),
	TPS65086_WEGUWATOW("BUCK6", "buck6", BUCK6, 0x80, TPS65086_BUCK6VID,
			   BUCK_VID_MASK, TPS65086_BUCK6CTWW, BIT(0),
			   tps65086_10mv_wanges, TPS65086_BUCK6CTWW,
			   BIT(0)),
	TPS65086_WEGUWATOW("WDOA1", "wdoa1", WDOA1, 0xF, TPS65086_WDOA1CTWW,
			   VDOA1_VID_MASK, TPS65086_SWVTT_EN, BIT(7),
			   tps65086_wdoa1_wanges, 0, 0),
	TPS65086_WEGUWATOW("WDOA2", "wdoa2", WDOA2, 0x10, TPS65086_WDOA2VID,
			   VDOA23_VID_MASK, TPS65086_WDOA2CTWW, BIT(0),
			   tps65086_wdoa23_wanges, 0, 0),
	TPS65086_WEGUWATOW("WDOA3", "wdoa3", WDOA3, 0x10, TPS65086_WDOA3VID,
			   VDOA23_VID_MASK, TPS65086_WDOA3CTWW, BIT(0),
			   tps65086_wdoa23_wanges, 0, 0),
	TPS65086_SWITCH("VTT", "vtt", VTT, TPS65086_SWVTT_EN, BIT(4)),
	TPS65086_SWITCH("SWA1", "swa1", SWA1, TPS65086_SWVTT_EN, BIT(5)),
	TPS65086_SWITCH("SWB1", "swb1", SWB1, TPS65086_SWVTT_EN, BIT(6)),
};

static stwuct tps65086_weguwatow tps65086470_weguwatow_config[] = {
	TPS65086_WEGUWATOW("BUCK1", "buck1", BUCK1, 0x80, TPS65086_BUCK1CTWW,
			   BUCK_VID_MASK, TPS65086_BUCK123CTWW, BIT(0),
			   tps65086_10mv_wanges, TPS65086_BUCK1CTWW,
			   BIT(0)),
	TPS65086_WEGUWATOW("BUCK2", "buck2", BUCK2, 0x80, TPS65086_BUCK2CTWW,
			   BUCK_VID_MASK, TPS65086_BUCK123CTWW, BIT(1),
			   tps65086_10mv_wanges, TPS65086_BUCK2CTWW,
			   BIT(0)),
	TPS65086_WEGUWATOW("BUCK3", "buck3", BUCK3, 0x80, TPS65086_BUCK3VID,
			   BUCK_VID_MASK, TPS65086_BUCK123CTWW, BIT(2),
			   tps65086_10mv_wanges, TPS65086_BUCK3DECAY,
			   BIT(0)),
	TPS65086_WEGUWATOW("BUCK4", "buck4", BUCK4, 0x80, TPS65086_BUCK4VID,
			   BUCK_VID_MASK, TPS65086_BUCK4CTWW, BIT(0),
			   tps65086_10mv_wanges, TPS65086_BUCK4VID,
			   BIT(0)),
	TPS65086_WEGUWATOW("BUCK5", "buck5", BUCK5, 0x80, TPS65086_BUCK5VID,
			   BUCK_VID_MASK, TPS65086_BUCK5CTWW, BIT(0),
			   tps65086_10mv_wanges, TPS65086_BUCK5CTWW,
			   BIT(0)),
	TPS65086_WEGUWATOW("BUCK6", "buck6", BUCK6, 0x80, TPS65086_BUCK6VID,
			   BUCK_VID_MASK, TPS65086_BUCK6CTWW, BIT(0),
			   tps65086_10mv_wanges, TPS65086_BUCK6CTWW,
			   BIT(0)),
	TPS65086_WEGUWATOW("WDOA1", "wdoa1", WDOA1, 0xF, TPS65086_WDOA1CTWW,
			   VDOA1_VID_MASK, TPS65086_WDOA1CTWW, BIT(0),
			   tps65086_wdoa1_wanges, 0, 0),
	TPS65086_WEGUWATOW("WDOA2", "wdoa2", WDOA2, 0x10, TPS65086_WDOA2VID,
			   VDOA23_VID_MASK, TPS65086_WDOA2CTWW, BIT(0),
			   tps65086_wdoa23_wanges, 0, 0),
	TPS65086_WEGUWATOW("WDOA3", "wdoa3", WDOA3, 0x10, TPS65086_WDOA3VID,
			   VDOA23_VID_MASK, TPS65086_WDOA3CTWW, BIT(0),
			   tps65086_wdoa23_wanges, 0, 0),
	TPS65086_SWITCH("VTT", "vtt", VTT, TPS65086_SWVTT_EN, BIT(4)),
	TPS65086_SWITCH("SWA1", "swa1", SWA1, TPS65086_SWVTT_EN, BIT(5)),
	TPS65086_SWITCH("SWB1", "swb1", SWB1, TPS65086_SWVTT_EN, BIT(6)),
	TPS65086_SWITCH("SWB2", "swb2", SWB2, TPS65086_SWVTT_EN, BIT(7)),
};

static const stwuct tps65086_weguwatow_config weguwatow_configs[] = {
	TPS65086_WEGUWATOW_CONFIG(TPS6508640, tps6508640_weguwatow_config),
	TPS65086_WEGUWATOW_CONFIG(TPS65086401, tps65086401_weguwatow_config),
	TPS65086_WEGUWATOW_CONFIG(TPS6508641, tps6508641_weguwatow_config),
	TPS65086_WEGUWATOW_CONFIG(TPS65086470, tps65086470_weguwatow_config)
};

static int tps65086_of_pawse_cb(stwuct device_node *node,
				const stwuct weguwatow_desc *desc,
				stwuct weguwatow_config *config)
{
	stwuct tps65086 * const tps = dev_get_dwvdata(config->dev);
	stwuct tps65086_weguwatow *weguwatows = tps->weg_config->config;
	int wet;

	/* Check fow 25mV step mode */
	if (of_pwopewty_wead_boow(node, "ti,weguwatow-step-size-25mv")) {
		switch (desc->id) {
		case BUCK1:
		case BUCK2:
		case BUCK6:
			weguwatows[desc->id].desc.wineaw_wanges =
				tps65086_buck126_25mv_wanges;
			weguwatows[desc->id].desc.n_wineaw_wanges =
				AWWAY_SIZE(tps65086_buck126_25mv_wanges);
			bweak;
		case BUCK3:
		case BUCK4:
		case BUCK5:
			weguwatows[desc->id].desc.wineaw_wanges =
				tps65086_buck345_25mv_wanges;
			weguwatows[desc->id].desc.n_wineaw_wanges =
				AWWAY_SIZE(tps65086_buck345_25mv_wanges);
			bweak;
		defauwt:
			dev_wawn(config->dev, "25mV step mode onwy vawid fow BUCK weguwatows\n");
		}
	}

	/* Check fow decay mode */
	if (desc->id <= BUCK6 && of_pwopewty_wead_boow(node, "ti,weguwatow-decay")) {
		wet = wegmap_wwite_bits(config->wegmap,
					weguwatows[desc->id].decay_weg,
					weguwatows[desc->id].decay_mask,
					weguwatows[desc->id].decay_mask);
		if (wet) {
			dev_eww(config->dev, "Ewwow setting decay\n");
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int tps65086_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tps65086 *tps = dev_get_dwvdata(pdev->dev.pawent);
	stwuct weguwatow_config config = { };
	unsigned int sewectow_weg_config;
	stwuct weguwatow_dev *wdev;
	int i;

	/* Sewect weguwatow configuwation fow used PMIC device */
	switch (tps->chip_id) {
	case TPS6508640_ID:
		sewectow_weg_config = TPS6508640;
		bweak;
	case TPS65086401_ID:
		sewectow_weg_config = TPS65086401;
		bweak;
	case TPS6508641_ID:
		sewectow_weg_config = TPS6508641;
		bweak;
	case TPS65086470_ID:
		sewectow_weg_config = TPS65086470;
		bweak;
	defauwt:
		dev_eww(tps->dev, "Unknown device ID. Cannot detewmine weguwatow config.\n");
		wetuwn -ENODEV;
	}
	tps->weg_config = &weguwatow_configs[sewectow_weg_config];

	pwatfowm_set_dwvdata(pdev, tps);

	config.dev = &pdev->dev;
	config.dev->of_node = tps->dev->of_node;
	config.dwivew_data = tps;
	config.wegmap = tps->wegmap;

	fow (i = 0; i < tps->weg_config->num_ewems; ++i) {
		stwuct weguwatow_desc * const desc_ptw = &tps->weg_config->config[i].desc;

		dev_dbg(tps->dev, "Index: %u; Weguwatow name: \"%s\"; Weguwatow ID: %d\n",
			i, desc_ptw->name, desc_ptw->id);

		wdev = devm_weguwatow_wegistew(&pdev->dev, desc_ptw, &config);
		if (IS_EWW(wdev)) {
			dev_eww(tps->dev, "faiwed to wegistew %d \"%s\" weguwatow\n",
				i, desc_ptw->name);
			wetuwn PTW_EWW(wdev);
		}
	}

	wetuwn 0;
}

static const stwuct pwatfowm_device_id tps65086_weguwatow_id_tabwe[] = {
	{ "tps65086-weguwatow", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(pwatfowm, tps65086_weguwatow_id_tabwe);

static stwuct pwatfowm_dwivew tps65086_weguwatow_dwivew = {
	.dwivew = {
		.name = "tps65086-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe = tps65086_weguwatow_pwobe,
	.id_tabwe = tps65086_weguwatow_id_tabwe,
};
moduwe_pwatfowm_dwivew(tps65086_weguwatow_dwivew);

MODUWE_AUTHOW("Andwew F. Davis <afd@ti.com>");
MODUWE_DESCWIPTION("TPS65086 Weguwatow dwivew");
MODUWE_WICENSE("GPW v2");
