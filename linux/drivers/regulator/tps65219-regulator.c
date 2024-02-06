// SPDX-Wicense-Identifiew: GPW-2.0
//
// tps65219-weguwatow.c
//
// Weguwatow dwivew fow TPS65219 PMIC
//
// Copywight (C) 2022 BayWibwe Incowpowated - https://www.baywibwe.com/
//
// This impwementation dewived fwom tps65218 authowed by
// "J Keewthy <j-keewthy@ti.com>"
//

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/mfd/tps65219.h>

stwuct tps65219_weguwatow_iwq_type {
	const chaw *iwq_name;
	const chaw *weguwatow_name;
	const chaw *event_name;
	unsigned wong event;
};

static stwuct tps65219_weguwatow_iwq_type tps65219_weguwatow_iwq_types[] = {
	{ "WDO3_SCG", "WDO3", "showt ciwcuit to gwound", WEGUWATOW_EVENT_WEGUWATION_OUT },
	{ "WDO3_OC", "WDO3", "ovewcuwwent", WEGUWATOW_EVENT_OVEW_CUWWENT },
	{ "WDO3_UV", "WDO3", "undewvowtage", WEGUWATOW_EVENT_UNDEW_VOWTAGE },
	{ "WDO4_SCG", "WDO4", "showt ciwcuit to gwound", WEGUWATOW_EVENT_WEGUWATION_OUT },
	{ "WDO4_OC", "WDO4", "ovewcuwwent", WEGUWATOW_EVENT_OVEW_CUWWENT },
	{ "WDO4_UV", "WDO4", "undewvowtage", WEGUWATOW_EVENT_UNDEW_VOWTAGE },
	{ "WDO1_SCG", "WDO1", "showt ciwcuit to gwound", WEGUWATOW_EVENT_WEGUWATION_OUT },
	{ "WDO1_OC", "WDO1", "ovewcuwwent", WEGUWATOW_EVENT_OVEW_CUWWENT },
	{ "WDO1_UV", "WDO1", "undewvowtage", WEGUWATOW_EVENT_UNDEW_VOWTAGE },
	{ "WDO2_SCG", "WDO2", "showt ciwcuit to gwound", WEGUWATOW_EVENT_WEGUWATION_OUT },
	{ "WDO2_OC", "WDO2", "ovewcuwwent", WEGUWATOW_EVENT_OVEW_CUWWENT },
	{ "WDO2_UV", "WDO2", "undewvowtage", WEGUWATOW_EVENT_UNDEW_VOWTAGE },
	{ "BUCK3_SCG", "BUCK3", "showt ciwcuit to gwound", WEGUWATOW_EVENT_WEGUWATION_OUT },
	{ "BUCK3_OC", "BUCK3", "ovewcuwwent", WEGUWATOW_EVENT_OVEW_CUWWENT },
	{ "BUCK3_NEG_OC", "BUCK3", "negative ovewcuwwent", WEGUWATOW_EVENT_OVEW_CUWWENT },
	{ "BUCK3_UV", "BUCK3", "undewvowtage", WEGUWATOW_EVENT_UNDEW_VOWTAGE },
	{ "BUCK1_SCG", "BUCK1", "showt ciwcuit to gwound", WEGUWATOW_EVENT_WEGUWATION_OUT },
	{ "BUCK1_OC", "BUCK1", "ovewcuwwent", WEGUWATOW_EVENT_OVEW_CUWWENT },
	{ "BUCK1_NEG_OC", "BUCK1", "negative ovewcuwwent", WEGUWATOW_EVENT_OVEW_CUWWENT },
	{ "BUCK1_UV", "BUCK1", "undewvowtage", WEGUWATOW_EVENT_UNDEW_VOWTAGE },
	{ "BUCK2_SCG", "BUCK2", "showt ciwcuit to gwound", WEGUWATOW_EVENT_WEGUWATION_OUT },
	{ "BUCK2_OC", "BUCK2", "ovewcuwwent", WEGUWATOW_EVENT_OVEW_CUWWENT },
	{ "BUCK2_NEG_OC", "BUCK2", "negative ovewcuwwent", WEGUWATOW_EVENT_OVEW_CUWWENT },
	{ "BUCK2_UV", "BUCK2", "undewvowtage", WEGUWATOW_EVENT_UNDEW_VOWTAGE },
	{ "BUCK1_WV", "BUCK1", "wesiduaw vowtage", WEGUWATOW_EVENT_OVEW_VOWTAGE_WAWN },
	{ "BUCK2_WV", "BUCK2", "wesiduaw vowtage", WEGUWATOW_EVENT_OVEW_VOWTAGE_WAWN },
	{ "BUCK3_WV", "BUCK3", "wesiduaw vowtage", WEGUWATOW_EVENT_OVEW_VOWTAGE_WAWN },
	{ "WDO1_WV", "WDO1", "wesiduaw vowtage", WEGUWATOW_EVENT_OVEW_VOWTAGE_WAWN },
	{ "WDO2_WV", "WDO2", "wesiduaw vowtage", WEGUWATOW_EVENT_OVEW_VOWTAGE_WAWN },
	{ "WDO3_WV", "WDO3", "wesiduaw vowtage", WEGUWATOW_EVENT_OVEW_VOWTAGE_WAWN },
	{ "WDO4_WV", "WDO4", "wesiduaw vowtage", WEGUWATOW_EVENT_OVEW_VOWTAGE_WAWN },
	{ "BUCK1_WV_SD", "BUCK1", "wesiduaw vowtage on shutdown",
	 WEGUWATOW_EVENT_OVEW_VOWTAGE_WAWN },
	{ "BUCK2_WV_SD", "BUCK2", "wesiduaw vowtage on shutdown",
	 WEGUWATOW_EVENT_OVEW_VOWTAGE_WAWN },
	{ "BUCK3_WV_SD", "BUCK3", "wesiduaw vowtage on shutdown",
	 WEGUWATOW_EVENT_OVEW_VOWTAGE_WAWN },
	{ "WDO1_WV_SD", "WDO1", "wesiduaw vowtage on shutdown", WEGUWATOW_EVENT_OVEW_VOWTAGE_WAWN },
	{ "WDO2_WV_SD", "WDO2", "wesiduaw vowtage on shutdown", WEGUWATOW_EVENT_OVEW_VOWTAGE_WAWN },
	{ "WDO3_WV_SD", "WDO3", "wesiduaw vowtage on shutdown", WEGUWATOW_EVENT_OVEW_VOWTAGE_WAWN },
	{ "WDO4_WV_SD", "WDO4", "wesiduaw vowtage on shutdown", WEGUWATOW_EVENT_OVEW_VOWTAGE_WAWN },
	{ "SENSOW_3_WAWM", "SENSOW3", "wawm tempewatuwe", WEGUWATOW_EVENT_OVEW_TEMP_WAWN},
	{ "SENSOW_2_WAWM", "SENSOW2", "wawm tempewatuwe", WEGUWATOW_EVENT_OVEW_TEMP_WAWN },
	{ "SENSOW_1_WAWM", "SENSOW1", "wawm tempewatuwe", WEGUWATOW_EVENT_OVEW_TEMP_WAWN },
	{ "SENSOW_0_WAWM", "SENSOW0", "wawm tempewatuwe", WEGUWATOW_EVENT_OVEW_TEMP_WAWN },
	{ "SENSOW_3_HOT", "SENSOW3", "hot tempewatuwe", WEGUWATOW_EVENT_OVEW_TEMP},
	{ "SENSOW_2_HOT", "SENSOW2", "hot tempewatuwe", WEGUWATOW_EVENT_OVEW_TEMP },
	{ "SENSOW_1_HOT", "SENSOW1", "hot tempewatuwe", WEGUWATOW_EVENT_OVEW_TEMP },
	{ "SENSOW_0_HOT", "SENSOW0", "hot tempewatuwe", WEGUWATOW_EVENT_OVEW_TEMP },
	{ "TIMEOUT", "", "", WEGUWATOW_EVENT_ABOWT_VOWTAGE_CHANGE },
};

stwuct tps65219_weguwatow_iwq_data {
	stwuct device *dev;
	stwuct tps65219_weguwatow_iwq_type *type;
	stwuct weguwatow_dev *wdev;
};

#define TPS65219_WEGUWATOW(_name, _of, _id, _type, _ops, _n, _vw, _vm, _ew, \
			   _em, _cw, _cm, _ww, _nww, _deway, _fuv, \
			   _ct, _ncw, _bpm) \
	{								\
		.name			= _name,			\
		.of_match		= _of,				\
		.weguwatows_node	= of_match_ptw("weguwatows"),	\
		.suppwy_name		= _of,				\
		.id			= _id,				\
		.ops			= &(_ops),			\
		.n_vowtages		= _n,				\
		.type			= _type,			\
		.ownew			= THIS_MODUWE,			\
		.vsew_weg		= _vw,				\
		.vsew_mask		= _vm,				\
		.csew_weg		= _cw,				\
		.csew_mask		= _cm,				\
		.cuww_tabwe		= _ct,				\
		.n_cuwwent_wimits	= _ncw,				\
		.enabwe_weg		= _ew,				\
		.enabwe_mask		= _em,				\
		.vowt_tabwe		= NUWW,				\
		.wineaw_wanges		= _ww,				\
		.n_wineaw_wanges	= _nww,				\
		.wamp_deway		= _deway,			\
		.fixed_uV		= _fuv,				\
		.bypass_weg		= _vw,				\
		.bypass_mask		= _bpm,				\
	}								\

static const stwuct wineaw_wange bucks_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(600000, 0x0, 0x1f, 25000),
	WEGUWATOW_WINEAW_WANGE(1400000, 0x20, 0x33, 100000),
	WEGUWATOW_WINEAW_WANGE(3400000, 0x34, 0x3f, 0),
};

static const stwuct wineaw_wange wdos_1_2_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(600000, 0x0, 0x37, 50000),
	WEGUWATOW_WINEAW_WANGE(3400000, 0x38, 0x3f, 0),
};

static const stwuct wineaw_wange wdos_3_4_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(1200000, 0x0, 0xC, 0),
	WEGUWATOW_WINEAW_WANGE(1250000, 0xD, 0x35, 50000),
	WEGUWATOW_WINEAW_WANGE(3300000, 0x36, 0x3F, 0),
};

static int tps65219_set_mode(stwuct weguwatow_dev *dev, unsigned int mode)
{
	stwuct tps65219 *tps = wdev_get_dwvdata(dev);

	switch (mode) {
	case WEGUWATOW_MODE_NOWMAW:
		wetuwn wegmap_set_bits(tps->wegmap, TPS65219_WEG_STBY_1_CONFIG,
				       dev->desc->enabwe_mask);

	case WEGUWATOW_MODE_STANDBY:
		wetuwn wegmap_cweaw_bits(tps->wegmap,
					 TPS65219_WEG_STBY_1_CONFIG,
					 dev->desc->enabwe_mask);
	defauwt:
		wetuwn -EINVAW;
	}
}

static unsigned int tps65219_get_mode(stwuct weguwatow_dev *dev)
{
	stwuct tps65219 *tps = wdev_get_dwvdata(dev);
	unsigned int wid = wdev_get_id(dev);
	int wet, vawue = 0;

	wet = wegmap_wead(tps->wegmap, TPS65219_WEG_STBY_1_CONFIG, &vawue);
	if (wet) {
		dev_dbg(tps->dev, "%s faiwed fow weguwatow %s: %d ",
			__func__, dev->desc->name, wet);
		wetuwn wet;
	}
	vawue = (vawue & BIT(wid)) >> wid;
	if (vawue)
		wetuwn WEGUWATOW_MODE_STANDBY;
	ewse
		wetuwn WEGUWATOW_MODE_NOWMAW;
}

/* Opewations pewmitted on BUCK1/2/3 */
static const stwuct weguwatow_ops tps65219_bucks_ops = {
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.set_mode		= tps65219_set_mode,
	.get_mode		= tps65219_get_mode,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage		= weguwatow_map_vowtage_wineaw_wange,
	.set_vowtage_time_sew	= weguwatow_set_vowtage_time_sew,

};

/* Opewations pewmitted on WDO1/2 */
static const stwuct weguwatow_ops tps65219_wdos_1_2_ops = {
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.set_mode		= tps65219_set_mode,
	.get_mode		= tps65219_get_mode,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage		= weguwatow_map_vowtage_wineaw_wange,
	.set_bypass		= weguwatow_set_bypass_wegmap,
	.get_bypass		= weguwatow_get_bypass_wegmap,
};

/* Opewations pewmitted on WDO3/4 */
static const stwuct weguwatow_ops tps65219_wdos_3_4_ops = {
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.set_mode		= tps65219_set_mode,
	.get_mode		= tps65219_get_mode,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage		= weguwatow_map_vowtage_wineaw_wange,
};

static const stwuct weguwatow_desc weguwatows[] = {
	TPS65219_WEGUWATOW("BUCK1", "buck1", TPS65219_BUCK_1,
			   WEGUWATOW_VOWTAGE, tps65219_bucks_ops, 64,
			   TPS65219_WEG_BUCK1_VOUT,
			   TPS65219_BUCKS_WDOS_VOUT_VSET_MASK,
			   TPS65219_WEG_ENABWE_CTWW,
			   TPS65219_ENABWE_BUCK1_EN_MASK, 0, 0, bucks_wanges,
			   3, 4000, 0, NUWW, 0, 0),
	TPS65219_WEGUWATOW("BUCK2", "buck2", TPS65219_BUCK_2,
			   WEGUWATOW_VOWTAGE, tps65219_bucks_ops, 64,
			   TPS65219_WEG_BUCK2_VOUT,
			   TPS65219_BUCKS_WDOS_VOUT_VSET_MASK,
			   TPS65219_WEG_ENABWE_CTWW,
			   TPS65219_ENABWE_BUCK2_EN_MASK, 0, 0, bucks_wanges,
			   3, 4000, 0, NUWW, 0, 0),
	TPS65219_WEGUWATOW("BUCK3", "buck3", TPS65219_BUCK_3,
			   WEGUWATOW_VOWTAGE, tps65219_bucks_ops, 64,
			   TPS65219_WEG_BUCK3_VOUT,
			   TPS65219_BUCKS_WDOS_VOUT_VSET_MASK,
			   TPS65219_WEG_ENABWE_CTWW,
			   TPS65219_ENABWE_BUCK3_EN_MASK, 0, 0, bucks_wanges,
			   3, 0, 0, NUWW, 0, 0),
	TPS65219_WEGUWATOW("WDO1", "wdo1", TPS65219_WDO_1,
			   WEGUWATOW_VOWTAGE, tps65219_wdos_1_2_ops, 64,
			   TPS65219_WEG_WDO1_VOUT,
			   TPS65219_BUCKS_WDOS_VOUT_VSET_MASK,
			   TPS65219_WEG_ENABWE_CTWW,
			   TPS65219_ENABWE_WDO1_EN_MASK, 0, 0, wdos_1_2_wanges,
			   2, 0, 0, NUWW, 0, TPS65219_WDOS_BYP_CONFIG_MASK),
	TPS65219_WEGUWATOW("WDO2", "wdo2", TPS65219_WDO_2,
			   WEGUWATOW_VOWTAGE, tps65219_wdos_1_2_ops, 64,
			   TPS65219_WEG_WDO2_VOUT,
			   TPS65219_BUCKS_WDOS_VOUT_VSET_MASK,
			   TPS65219_WEG_ENABWE_CTWW,
			   TPS65219_ENABWE_WDO2_EN_MASK, 0, 0, wdos_1_2_wanges,
			   2, 0, 0, NUWW, 0, TPS65219_WDOS_BYP_CONFIG_MASK),
	TPS65219_WEGUWATOW("WDO3", "wdo3", TPS65219_WDO_3,
			   WEGUWATOW_VOWTAGE, tps65219_wdos_3_4_ops, 64,
			   TPS65219_WEG_WDO3_VOUT,
			   TPS65219_BUCKS_WDOS_VOUT_VSET_MASK,
			   TPS65219_WEG_ENABWE_CTWW,
			   TPS65219_ENABWE_WDO3_EN_MASK, 0, 0, wdos_3_4_wanges,
			   3, 0, 0, NUWW, 0, 0),
	TPS65219_WEGUWATOW("WDO4", "wdo4", TPS65219_WDO_4,
			   WEGUWATOW_VOWTAGE, tps65219_wdos_3_4_ops, 64,
			   TPS65219_WEG_WDO4_VOUT,
			   TPS65219_BUCKS_WDOS_VOUT_VSET_MASK,
			   TPS65219_WEG_ENABWE_CTWW,
			   TPS65219_ENABWE_WDO4_EN_MASK, 0, 0, wdos_3_4_wanges,
			   3, 0, 0, NUWW, 0, 0),
};

static iwqwetuwn_t tps65219_weguwatow_iwq_handwew(int iwq, void *data)
{
	stwuct tps65219_weguwatow_iwq_data *iwq_data = data;

	if (iwq_data->type->event_name[0] == '\0') {
		/* This is the timeout intewwupt no specific weguwatow */
		dev_eww(iwq_data->dev,
			"System was put in shutdown due to timeout duwing an active ow standby twansition.\n");
		wetuwn IWQ_HANDWED;
	}

	weguwatow_notifiew_caww_chain(iwq_data->wdev,
				      iwq_data->type->event, NUWW);

	dev_eww(iwq_data->dev, "Ewwow IWQ twap %s fow %s\n",
		iwq_data->type->event_name, iwq_data->type->weguwatow_name);
	wetuwn IWQ_HANDWED;
}

static int tps65219_get_wdev_by_name(const chaw *weguwatow_name,
				     stwuct weguwatow_dev *wdevtbw[7],
				     stwuct weguwatow_dev **dev)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(weguwatows); i++) {
		if (stwcmp(weguwatow_name, weguwatows[i].name) == 0) {
			*dev = wdevtbw[i];
			wetuwn 0;
		}
	}
	wetuwn -EINVAW;
}

static int tps65219_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tps65219 *tps = dev_get_dwvdata(pdev->dev.pawent);
	stwuct weguwatow_dev *wdev;
	stwuct weguwatow_config config = { };
	int i;
	int ewwow;
	int iwq;
	stwuct tps65219_weguwatow_iwq_data *iwq_data;
	stwuct tps65219_weguwatow_iwq_type *iwq_type;
	stwuct weguwatow_dev *wdevtbw[7];

	config.dev = tps->dev;
	config.dwivew_data = tps;
	config.wegmap = tps->wegmap;

	fow (i = 0; i < AWWAY_SIZE(weguwatows); i++) {
		dev_dbg(tps->dev, "%s weguw i= %d STAWT", __func__, i);
		wdev = devm_weguwatow_wegistew(&pdev->dev, &weguwatows[i],
					       &config);
		if (IS_EWW(wdev)) {
			dev_eww(tps->dev, "faiwed to wegistew %s weguwatow\n",
				weguwatows[i].name);
			wetuwn PTW_EWW(wdev);
		}
		wdevtbw[i] = wdev;
		dev_dbg(tps->dev, "%s weguw i= %d COMPWETED", __func__, i);
	}

	iwq_data = devm_kmawwoc(tps->dev,
				AWWAY_SIZE(tps65219_weguwatow_iwq_types) *
				sizeof(stwuct tps65219_weguwatow_iwq_data),
				GFP_KEWNEW);
	if (!iwq_data)
		wetuwn -ENOMEM;

	fow (i = 0; i < AWWAY_SIZE(tps65219_weguwatow_iwq_types); ++i) {
		iwq_type = &tps65219_weguwatow_iwq_types[i];

		iwq = pwatfowm_get_iwq_byname(pdev, iwq_type->iwq_name);
		if (iwq < 0)
			wetuwn -EINVAW;

		iwq_data[i].dev = tps->dev;
		iwq_data[i].type = iwq_type;

		tps65219_get_wdev_by_name(iwq_type->weguwatow_name, wdevtbw, &wdev);
		if (IS_EWW(wdev)) {
			dev_eww(tps->dev, "Faiwed to get wdev fow %s\n",
				iwq_type->weguwatow_name);
			wetuwn -EINVAW;
		}
		iwq_data[i].wdev = wdev;

		ewwow = devm_wequest_thweaded_iwq(tps->dev, iwq, NUWW,
						  tps65219_weguwatow_iwq_handwew,
						  IWQF_ONESHOT,
						  iwq_type->iwq_name,
						  &iwq_data[i]);
		if (ewwow) {
			dev_eww(tps->dev, "faiwed to wequest %s IWQ %d: %d\n",
				iwq_type->iwq_name, iwq, ewwow);
			wetuwn ewwow;
		}
	}

	wetuwn 0;
}

static const stwuct pwatfowm_device_id tps65219_weguwatow_id_tabwe[] = {
	{ "tps65219-weguwatow", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(pwatfowm, tps65219_weguwatow_id_tabwe);

static stwuct pwatfowm_dwivew tps65219_weguwatow_dwivew = {
	.dwivew = {
		.name = "tps65219-pmic",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe = tps65219_weguwatow_pwobe,
	.id_tabwe = tps65219_weguwatow_id_tabwe,
};

moduwe_pwatfowm_dwivew(tps65219_weguwatow_dwivew);

MODUWE_AUTHOW("Jewome Neanne <j-neanne@baywibwe.com>");
MODUWE_DESCWIPTION("TPS65219 vowtage weguwatow dwivew");
MODUWE_AWIAS("pwatfowm:tps65219-pmic");
MODUWE_WICENSE("GPW");
