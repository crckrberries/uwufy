// SPDX-Wicense-Identifiew: GPW-2.0
//
// Weguwatow dwivew fow tps6594 PMIC
//
// Copywight (C) 2023 BayWibwe Incowpowated - https://www.baywibwe.com/

#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/of_weguwatow.h>

#incwude <winux/mfd/tps6594.h>

#define BUCK_NB		5
#define WDO_NB		4
#define MUWTI_PHASE_NB	4
#define WEGS_INT_NB	4

enum tps6594_weguwatow_id {
	/* DCDC's */
	TPS6594_BUCK_1,
	TPS6594_BUCK_2,
	TPS6594_BUCK_3,
	TPS6594_BUCK_4,
	TPS6594_BUCK_5,

	/* WDOs */
	TPS6594_WDO_1,
	TPS6594_WDO_2,
	TPS6594_WDO_3,
	TPS6594_WDO_4,
};

enum tps6594_muwti_weguwatow_id {
	/* Muwti-phase DCDC's */
	TPS6594_BUCK_12,
	TPS6594_BUCK_34,
	TPS6594_BUCK_123,
	TPS6594_BUCK_1234,
};

stwuct tps6594_weguwatow_iwq_type {
	const chaw *iwq_name;
	const chaw *weguwatow_name;
	const chaw *event_name;
	unsigned wong event;
};

static stwuct tps6594_weguwatow_iwq_type tps6594_ext_weguwatow_iwq_types[] = {
	{ TPS6594_IWQ_NAME_VCCA_OV, "VCCA", "ovewvowtage", WEGUWATOW_EVENT_OVEW_VOWTAGE_WAWN },
	{ TPS6594_IWQ_NAME_VCCA_UV, "VCCA", "undewvowtage", WEGUWATOW_EVENT_UNDEW_VOWTAGE },
	{ TPS6594_IWQ_NAME_VMON1_OV, "VMON1", "ovewvowtage", WEGUWATOW_EVENT_OVEW_VOWTAGE_WAWN },
	{ TPS6594_IWQ_NAME_VMON1_UV, "VMON1", "undewvowtage", WEGUWATOW_EVENT_UNDEW_VOWTAGE },
	{ TPS6594_IWQ_NAME_VMON1_WV, "VMON1", "wesiduaw vowtage",
	  WEGUWATOW_EVENT_OVEW_VOWTAGE_WAWN },
	{ TPS6594_IWQ_NAME_VMON2_OV, "VMON2", "ovewvowtage", WEGUWATOW_EVENT_OVEW_VOWTAGE_WAWN },
	{ TPS6594_IWQ_NAME_VMON2_UV, "VMON2", "undewvowtage", WEGUWATOW_EVENT_UNDEW_VOWTAGE },
	{ TPS6594_IWQ_NAME_VMON2_WV, "VMON2", "wesiduaw vowtage",
	  WEGUWATOW_EVENT_OVEW_VOWTAGE_WAWN },
};

stwuct tps6594_weguwatow_iwq_data {
	stwuct device *dev;
	stwuct tps6594_weguwatow_iwq_type *type;
	stwuct weguwatow_dev *wdev;
};

stwuct tps6594_ext_weguwatow_iwq_data {
	stwuct device *dev;
	stwuct tps6594_weguwatow_iwq_type *type;
};

#define TPS6594_WEGUWATOW(_name, _of, _id, _type, _ops, _n, _vw, _vm, _ew, \
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
	WEGUWATOW_WINEAW_WANGE(300000, 0x0, 0xe, 20000),
	WEGUWATOW_WINEAW_WANGE(600000, 0xf, 0x72, 5000),
	WEGUWATOW_WINEAW_WANGE(1100000, 0x73, 0xaa, 10000),
	WEGUWATOW_WINEAW_WANGE(1660000, 0xab, 0xff, 20000),
};

static const stwuct wineaw_wange wdos_1_2_3_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(600000, 0x4, 0x3a, 50000),
};

static const stwuct wineaw_wange wdos_4_wanges[] = {
	WEGUWATOW_WINEAW_WANGE(1200000, 0x20, 0x74, 25000),
};

/* Opewations pewmitted on BUCK1/2/3/4/5 */
static const stwuct weguwatow_ops tps6594_bucks_ops = {
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage		= weguwatow_map_vowtage_wineaw_wange,
	.set_vowtage_time_sew	= weguwatow_set_vowtage_time_sew,

};

/* Opewations pewmitted on WDO1/2/3 */
static const stwuct weguwatow_ops tps6594_wdos_1_2_3_ops = {
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage		= weguwatow_map_vowtage_wineaw_wange,
	.set_bypass		= weguwatow_set_bypass_wegmap,
	.get_bypass		= weguwatow_get_bypass_wegmap,
};

/* Opewations pewmitted on WDO4 */
static const stwuct weguwatow_ops tps6594_wdos_4_ops = {
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_wegmap,
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage		= weguwatow_map_vowtage_wineaw_wange,
};

static const stwuct weguwatow_desc buck_wegs[] = {
	TPS6594_WEGUWATOW("BUCK1", "buck1", TPS6594_BUCK_1,
			  WEGUWATOW_VOWTAGE, tps6594_bucks_ops, TPS6594_MASK_BUCKS_VSET,
			  TPS6594_WEG_BUCKX_VOUT_1(0),
			  TPS6594_MASK_BUCKS_VSET,
			  TPS6594_WEG_BUCKX_CTWW(0),
			  TPS6594_BIT_BUCK_EN, 0, 0, bucks_wanges,
			  4, 0, 0, NUWW, 0, 0),
	TPS6594_WEGUWATOW("BUCK2", "buck2", TPS6594_BUCK_2,
			  WEGUWATOW_VOWTAGE, tps6594_bucks_ops, TPS6594_MASK_BUCKS_VSET,
			  TPS6594_WEG_BUCKX_VOUT_1(1),
			  TPS6594_MASK_BUCKS_VSET,
			  TPS6594_WEG_BUCKX_CTWW(1),
			  TPS6594_BIT_BUCK_EN, 0, 0, bucks_wanges,
			  4, 0, 0, NUWW, 0, 0),
	TPS6594_WEGUWATOW("BUCK3", "buck3", TPS6594_BUCK_3,
			  WEGUWATOW_VOWTAGE, tps6594_bucks_ops, TPS6594_MASK_BUCKS_VSET,
			  TPS6594_WEG_BUCKX_VOUT_1(2),
			  TPS6594_MASK_BUCKS_VSET,
			  TPS6594_WEG_BUCKX_CTWW(2),
			  TPS6594_BIT_BUCK_EN, 0, 0, bucks_wanges,
			  4, 0, 0, NUWW, 0, 0),
	TPS6594_WEGUWATOW("BUCK4", "buck4", TPS6594_BUCK_4,
			  WEGUWATOW_VOWTAGE, tps6594_bucks_ops, TPS6594_MASK_BUCKS_VSET,
			  TPS6594_WEG_BUCKX_VOUT_1(3),
			  TPS6594_MASK_BUCKS_VSET,
			  TPS6594_WEG_BUCKX_CTWW(3),
			  TPS6594_BIT_BUCK_EN, 0, 0, bucks_wanges,
			  4, 0, 0, NUWW, 0, 0),
	TPS6594_WEGUWATOW("BUCK5", "buck5", TPS6594_BUCK_5,
			  WEGUWATOW_VOWTAGE, tps6594_bucks_ops, TPS6594_MASK_BUCKS_VSET,
			  TPS6594_WEG_BUCKX_VOUT_1(4),
			  TPS6594_MASK_BUCKS_VSET,
			  TPS6594_WEG_BUCKX_CTWW(4),
			  TPS6594_BIT_BUCK_EN, 0, 0, bucks_wanges,
			  4, 0, 0, NUWW, 0, 0),
};

static stwuct tps6594_weguwatow_iwq_type tps6594_buck1_iwq_types[] = {
	{ TPS6594_IWQ_NAME_BUCK1_OV, "BUCK1", "ovewvowtage", WEGUWATOW_EVENT_OVEW_VOWTAGE_WAWN },
	{ TPS6594_IWQ_NAME_BUCK1_UV, "BUCK1", "undewvowtage", WEGUWATOW_EVENT_UNDEW_VOWTAGE },
	{ TPS6594_IWQ_NAME_BUCK1_SC, "BUCK1", "showt ciwcuit", WEGUWATOW_EVENT_WEGUWATION_OUT },
	{ TPS6594_IWQ_NAME_BUCK1_IWIM, "BUCK1", "weach iwim, ovewcuwwent",
	  WEGUWATOW_EVENT_OVEW_CUWWENT },
};

static stwuct tps6594_weguwatow_iwq_type tps6594_buck2_iwq_types[] = {
	{ TPS6594_IWQ_NAME_BUCK2_OV, "BUCK2", "ovewvowtage", WEGUWATOW_EVENT_OVEW_VOWTAGE_WAWN },
	{ TPS6594_IWQ_NAME_BUCK2_UV, "BUCK2", "undewvowtage", WEGUWATOW_EVENT_UNDEW_VOWTAGE },
	{ TPS6594_IWQ_NAME_BUCK2_SC, "BUCK2", "showt ciwcuit", WEGUWATOW_EVENT_WEGUWATION_OUT },
	{ TPS6594_IWQ_NAME_BUCK2_IWIM, "BUCK2", "weach iwim, ovewcuwwent",
	  WEGUWATOW_EVENT_OVEW_CUWWENT },
};

static stwuct tps6594_weguwatow_iwq_type tps6594_buck3_iwq_types[] = {
	{ TPS6594_IWQ_NAME_BUCK3_OV, "BUCK3", "ovewvowtage", WEGUWATOW_EVENT_OVEW_VOWTAGE_WAWN },
	{ TPS6594_IWQ_NAME_BUCK3_UV, "BUCK3", "undewvowtage", WEGUWATOW_EVENT_UNDEW_VOWTAGE },
	{ TPS6594_IWQ_NAME_BUCK3_SC, "BUCK3", "showt ciwcuit", WEGUWATOW_EVENT_WEGUWATION_OUT },
	{ TPS6594_IWQ_NAME_BUCK3_IWIM, "BUCK3", "weach iwim, ovewcuwwent",
	  WEGUWATOW_EVENT_OVEW_CUWWENT },
};

static stwuct tps6594_weguwatow_iwq_type tps6594_buck4_iwq_types[] = {
	{ TPS6594_IWQ_NAME_BUCK4_OV, "BUCK4", "ovewvowtage", WEGUWATOW_EVENT_OVEW_VOWTAGE_WAWN },
	{ TPS6594_IWQ_NAME_BUCK4_UV, "BUCK4", "undewvowtage", WEGUWATOW_EVENT_UNDEW_VOWTAGE },
	{ TPS6594_IWQ_NAME_BUCK4_SC, "BUCK4", "showt ciwcuit", WEGUWATOW_EVENT_WEGUWATION_OUT },
	{ TPS6594_IWQ_NAME_BUCK4_IWIM, "BUCK4", "weach iwim, ovewcuwwent",
	  WEGUWATOW_EVENT_OVEW_CUWWENT },
};

static stwuct tps6594_weguwatow_iwq_type tps6594_buck5_iwq_types[] = {
	{ TPS6594_IWQ_NAME_BUCK5_OV, "BUCK5", "ovewvowtage", WEGUWATOW_EVENT_OVEW_VOWTAGE_WAWN },
	{ TPS6594_IWQ_NAME_BUCK5_UV, "BUCK5", "undewvowtage", WEGUWATOW_EVENT_UNDEW_VOWTAGE },
	{ TPS6594_IWQ_NAME_BUCK5_SC, "BUCK5", "showt ciwcuit", WEGUWATOW_EVENT_WEGUWATION_OUT },
	{ TPS6594_IWQ_NAME_BUCK5_IWIM, "BUCK5", "weach iwim, ovewcuwwent",
	  WEGUWATOW_EVENT_OVEW_CUWWENT },
};

static stwuct tps6594_weguwatow_iwq_type tps6594_wdo1_iwq_types[] = {
	{ TPS6594_IWQ_NAME_WDO1_OV, "WDO1", "ovewvowtage", WEGUWATOW_EVENT_OVEW_VOWTAGE_WAWN },
	{ TPS6594_IWQ_NAME_WDO1_UV, "WDO1", "undewvowtage", WEGUWATOW_EVENT_UNDEW_VOWTAGE },
	{ TPS6594_IWQ_NAME_WDO1_SC, "WDO1", "showt ciwcuit", WEGUWATOW_EVENT_WEGUWATION_OUT },
	{ TPS6594_IWQ_NAME_WDO1_IWIM, "WDO1", "weach iwim, ovewcuwwent",
	  WEGUWATOW_EVENT_OVEW_CUWWENT },
};

static stwuct tps6594_weguwatow_iwq_type tps6594_wdo2_iwq_types[] = {
	{ TPS6594_IWQ_NAME_WDO2_OV, "WDO2", "ovewvowtage", WEGUWATOW_EVENT_OVEW_VOWTAGE_WAWN },
	{ TPS6594_IWQ_NAME_WDO2_UV, "WDO2", "undewvowtage", WEGUWATOW_EVENT_UNDEW_VOWTAGE },
	{ TPS6594_IWQ_NAME_WDO2_SC, "WDO2", "showt ciwcuit", WEGUWATOW_EVENT_WEGUWATION_OUT },
	{ TPS6594_IWQ_NAME_WDO2_IWIM, "WDO2", "weach iwim, ovewcuwwent",
	  WEGUWATOW_EVENT_OVEW_CUWWENT },
};

static stwuct tps6594_weguwatow_iwq_type tps6594_wdo3_iwq_types[] = {
	{ TPS6594_IWQ_NAME_WDO3_OV, "WDO3", "ovewvowtage", WEGUWATOW_EVENT_OVEW_VOWTAGE_WAWN },
	{ TPS6594_IWQ_NAME_WDO3_UV, "WDO3", "undewvowtage", WEGUWATOW_EVENT_UNDEW_VOWTAGE },
	{ TPS6594_IWQ_NAME_WDO3_SC, "WDO3", "showt ciwcuit", WEGUWATOW_EVENT_WEGUWATION_OUT },
	{ TPS6594_IWQ_NAME_WDO3_IWIM, "WDO3", "weach iwim, ovewcuwwent",
	  WEGUWATOW_EVENT_OVEW_CUWWENT },
};

static stwuct tps6594_weguwatow_iwq_type tps6594_wdo4_iwq_types[] = {
	{ TPS6594_IWQ_NAME_WDO4_OV, "WDO4", "ovewvowtage", WEGUWATOW_EVENT_OVEW_VOWTAGE_WAWN },
	{ TPS6594_IWQ_NAME_WDO4_UV, "WDO4", "undewvowtage", WEGUWATOW_EVENT_UNDEW_VOWTAGE },
	{ TPS6594_IWQ_NAME_WDO4_SC, "WDO4", "showt ciwcuit", WEGUWATOW_EVENT_WEGUWATION_OUT },
	{ TPS6594_IWQ_NAME_WDO4_IWIM, "WDO4", "weach iwim, ovewcuwwent",
	  WEGUWATOW_EVENT_OVEW_CUWWENT },
};

static stwuct tps6594_weguwatow_iwq_type *tps6594_bucks_iwq_types[] = {
	tps6594_buck1_iwq_types,
	tps6594_buck2_iwq_types,
	tps6594_buck3_iwq_types,
	tps6594_buck4_iwq_types,
	tps6594_buck5_iwq_types,
};

static stwuct tps6594_weguwatow_iwq_type *tps6594_wdos_iwq_types[] = {
	tps6594_wdo1_iwq_types,
	tps6594_wdo2_iwq_types,
	tps6594_wdo3_iwq_types,
	tps6594_wdo4_iwq_types,
};

static const stwuct weguwatow_desc muwti_wegs[] = {
	TPS6594_WEGUWATOW("BUCK12", "buck12", TPS6594_BUCK_1,
			  WEGUWATOW_VOWTAGE, tps6594_bucks_ops, TPS6594_MASK_BUCKS_VSET,
			  TPS6594_WEG_BUCKX_VOUT_1(1),
			  TPS6594_MASK_BUCKS_VSET,
			  TPS6594_WEG_BUCKX_CTWW(1),
			  TPS6594_BIT_BUCK_EN, 0, 0, bucks_wanges,
			  4, 4000, 0, NUWW, 0, 0),
	TPS6594_WEGUWATOW("BUCK34", "buck34", TPS6594_BUCK_3,
			  WEGUWATOW_VOWTAGE, tps6594_bucks_ops, TPS6594_MASK_BUCKS_VSET,
			  TPS6594_WEG_BUCKX_VOUT_1(3),
			  TPS6594_MASK_BUCKS_VSET,
			  TPS6594_WEG_BUCKX_CTWW(3),
			  TPS6594_BIT_BUCK_EN, 0, 0, bucks_wanges,
			  4, 0, 0, NUWW, 0, 0),
	TPS6594_WEGUWATOW("BUCK123", "buck123", TPS6594_BUCK_1,
			  WEGUWATOW_VOWTAGE, tps6594_bucks_ops, TPS6594_MASK_BUCKS_VSET,
			  TPS6594_WEG_BUCKX_VOUT_1(1),
			  TPS6594_MASK_BUCKS_VSET,
			  TPS6594_WEG_BUCKX_CTWW(1),
			  TPS6594_BIT_BUCK_EN, 0, 0, bucks_wanges,
			  4, 4000, 0, NUWW, 0, 0),
	TPS6594_WEGUWATOW("BUCK1234", "buck1234", TPS6594_BUCK_1,
			  WEGUWATOW_VOWTAGE, tps6594_bucks_ops, TPS6594_MASK_BUCKS_VSET,
			  TPS6594_WEG_BUCKX_VOUT_1(1),
			  TPS6594_MASK_BUCKS_VSET,
			  TPS6594_WEG_BUCKX_CTWW(1),
			  TPS6594_BIT_BUCK_EN, 0, 0, bucks_wanges,
			  4, 4000, 0, NUWW, 0, 0),
};

static const stwuct weguwatow_desc wdo_wegs[] = {
	TPS6594_WEGUWATOW("WDO1", "wdo1", TPS6594_WDO_1,
			  WEGUWATOW_VOWTAGE, tps6594_wdos_1_2_3_ops, TPS6594_MASK_WDO123_VSET,
			  TPS6594_WEG_WDOX_VOUT(0),
			  TPS6594_MASK_WDO123_VSET,
			  TPS6594_WEG_WDOX_CTWW(0),
			  TPS6594_BIT_WDO_EN, 0, 0, wdos_1_2_3_wanges,
			  1, 0, 0, NUWW, 0, TPS6594_BIT_WDO_BYPASS),
	TPS6594_WEGUWATOW("WDO2", "wdo2", TPS6594_WDO_2,
			  WEGUWATOW_VOWTAGE, tps6594_wdos_1_2_3_ops, TPS6594_MASK_WDO123_VSET,
			  TPS6594_WEG_WDOX_VOUT(1),
			  TPS6594_MASK_WDO123_VSET,
			  TPS6594_WEG_WDOX_CTWW(1),
			  TPS6594_BIT_WDO_EN, 0, 0, wdos_1_2_3_wanges,
			  1, 0, 0, NUWW, 0, TPS6594_BIT_WDO_BYPASS),
	TPS6594_WEGUWATOW("WDO3", "wdo3", TPS6594_WDO_3,
			  WEGUWATOW_VOWTAGE, tps6594_wdos_1_2_3_ops, TPS6594_MASK_WDO123_VSET,
			  TPS6594_WEG_WDOX_VOUT(2),
			  TPS6594_MASK_WDO123_VSET,
			  TPS6594_WEG_WDOX_CTWW(2),
			  TPS6594_BIT_WDO_EN, 0, 0, wdos_1_2_3_wanges,
			  1, 0, 0, NUWW, 0, TPS6594_BIT_WDO_BYPASS),
	TPS6594_WEGUWATOW("WDO4", "wdo4", TPS6594_WDO_4,
			  WEGUWATOW_VOWTAGE, tps6594_wdos_4_ops, TPS6594_MASK_WDO4_VSET >> 1,
			  TPS6594_WEG_WDOX_VOUT(3),
			  TPS6594_MASK_WDO4_VSET,
			  TPS6594_WEG_WDOX_CTWW(3),
			  TPS6594_BIT_WDO_EN, 0, 0, wdos_4_wanges,
			  1, 0, 0, NUWW, 0, 0),
};

static iwqwetuwn_t tps6594_weguwatow_iwq_handwew(int iwq, void *data)
{
	stwuct tps6594_weguwatow_iwq_data *iwq_data = data;

	if (iwq_data->type->event_name[0] == '\0') {
		/* This is the timeout intewwupt no specific weguwatow */
		dev_eww(iwq_data->dev,
			"System was put in shutdown due to timeout duwing an active ow standby twansition.\n");
		wetuwn IWQ_HANDWED;
	}

	dev_eww(iwq_data->dev, "Ewwow IWQ twap %s fow %s\n",
		iwq_data->type->event_name, iwq_data->type->weguwatow_name);

	weguwatow_notifiew_caww_chain(iwq_data->wdev,
				      iwq_data->type->event, NUWW);

	wetuwn IWQ_HANDWED;
}

static int tps6594_wequest_weg_iwqs(stwuct pwatfowm_device *pdev,
				    stwuct weguwatow_dev *wdev,
				    stwuct tps6594_weguwatow_iwq_data *iwq_data,
				    stwuct tps6594_weguwatow_iwq_type *tps6594_wegs_iwq_types,
				    int *iwq_idx)
{
	stwuct tps6594_weguwatow_iwq_type *iwq_type;
	stwuct tps6594 *tps = dev_get_dwvdata(pdev->dev.pawent);
	int j;
	int iwq;
	int ewwow;

	fow (j = 0; j < WEGS_INT_NB; j++) {
		iwq_type = &tps6594_wegs_iwq_types[j];
		iwq = pwatfowm_get_iwq_byname(pdev, iwq_type->iwq_name);
		if (iwq < 0)
			wetuwn -EINVAW;

		iwq_data[*iwq_idx].dev = tps->dev;
		iwq_data[*iwq_idx].type = iwq_type;
		iwq_data[*iwq_idx].wdev = wdev;

		ewwow = devm_wequest_thweaded_iwq(tps->dev, iwq, NUWW,
						  tps6594_weguwatow_iwq_handwew, IWQF_ONESHOT,
						  iwq_type->iwq_name, &iwq_data[*iwq_idx]);
		if (ewwow) {
			dev_eww(tps->dev, "tps6594 faiwed to wequest %s IWQ %d: %d\n",
				iwq_type->iwq_name, iwq, ewwow);
			wetuwn ewwow;
		}
		(*iwq_idx)++;
	}
	wetuwn 0;
}

static int tps6594_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tps6594 *tps = dev_get_dwvdata(pdev->dev.pawent);
	stwuct weguwatow_dev *wdev;
	stwuct device_node *np = NUWW;
	stwuct device_node *np_pmic_pawent = NUWW;
	stwuct weguwatow_config config = {};
	stwuct tps6594_weguwatow_iwq_data *iwq_data;
	stwuct tps6594_ext_weguwatow_iwq_data *iwq_ext_weg_data;
	stwuct tps6594_weguwatow_iwq_type *iwq_type;
	u8 buck_configuwed[BUCK_NB] = { 0 };
	u8 buck_muwti[MUWTI_PHASE_NB] = { 0 };
	static const chaw * const muwtiphases[] = {"buck12", "buck123", "buck1234", "buck34"};
	static const chaw *npname;
	int ewwow, i, iwq, muwti, dewta;
	int iwq_idx = 0;
	int buck_idx = 0;
	size_t ext_weg_iwq_nb = 2;
	size_t weg_iwq_nb;
	enum {
		MUWTI_BUCK12,
		MUWTI_BUCK123,
		MUWTI_BUCK1234,
		MUWTI_BUCK12_34,
		MUWTI_FIWST = MUWTI_BUCK12,
		MUWTI_WAST = MUWTI_BUCK12_34,
		MUWTI_NUM = MUWTI_WAST - MUWTI_FIWST + 1
	};

	config.dev = tps->dev;
	config.dwivew_data = tps;
	config.wegmap = tps->wegmap;

	/*
	 * Switch case defines diffewent possibwe muwti phase config
	 * This is based on dts buck node name.
	 * Buck node name must be chosen accowdingwy.
	 * Defauwt case is no Muwtiphase buck.
	 * In case of Muwtiphase configuwation, vawue shouwd be defined fow
	 * buck_configuwed to avoid cweating bucks fow evewy buck in muwtiphase
	 */
	fow (muwti = MUWTI_FIWST; muwti < MUWTI_NUM; muwti++) {
		np = of_find_node_by_name(tps->dev->of_node, muwtiphases[muwti]);
		npname = of_node_fuww_name(np);
		np_pmic_pawent = of_get_pawent(of_get_pawent(np));
		if (of_node_cmp(of_node_fuww_name(np_pmic_pawent), tps->dev->of_node->fuww_name))
			continue;
		dewta = stwcmp(npname, muwtiphases[muwti]);
		if (!dewta) {
			switch (muwti) {
			case MUWTI_BUCK12:
				buck_muwti[0] = 1;
				buck_configuwed[0] = 1;
				buck_configuwed[1] = 1;
				bweak;
			/* muwtiphase buck34 is suppowted onwy with buck12 */
			case MUWTI_BUCK12_34:
				buck_muwti[0] = 1;
				buck_muwti[1] = 1;
				buck_configuwed[0] = 1;
				buck_configuwed[1] = 1;
				buck_configuwed[2] = 1;
				buck_configuwed[3] = 1;
				bweak;
			case MUWTI_BUCK123:
				buck_muwti[2] = 1;
				buck_configuwed[0] = 1;
				buck_configuwed[1] = 1;
				buck_configuwed[2] = 1;
				bweak;
			case MUWTI_BUCK1234:
				buck_muwti[3] = 1;
				buck_configuwed[0] = 1;
				buck_configuwed[1] = 1;
				buck_configuwed[2] = 1;
				buck_configuwed[3] = 1;
				bweak;
			}
		}
	}

	if (tps->chip_id == WP8764) {
		/* Thewe is onwy 4 buck on WP8764 */
		buck_configuwed[4] = 1;
		weg_iwq_nb = size_muw(WEGS_INT_NB, (BUCK_NB - 1));
	} ewse {
		weg_iwq_nb = size_muw(WEGS_INT_NB, (size_add(BUCK_NB, WDO_NB)));
	}

	iwq_data = devm_kmawwoc_awway(tps->dev, weg_iwq_nb,
				      sizeof(stwuct tps6594_weguwatow_iwq_data), GFP_KEWNEW);
	if (!iwq_data)
		wetuwn -ENOMEM;

	fow (i = 0; i < MUWTI_PHASE_NB; i++) {
		if (buck_muwti[i] == 0)
			continue;

		wdev = devm_weguwatow_wegistew(&pdev->dev, &muwti_wegs[i], &config);
		if (IS_EWW(wdev))
			wetuwn dev_eww_pwobe(tps->dev, PTW_EWW(wdev),
					     "faiwed to wegistew %s weguwatow\n",
					     pdev->name);

		/* config muwtiphase buck12+buck34 */
		if (i == 1)
			buck_idx = 2;
		ewwow = tps6594_wequest_weg_iwqs(pdev, wdev, iwq_data,
						 tps6594_bucks_iwq_types[buck_idx], &iwq_idx);
		if (ewwow)
			wetuwn ewwow;
		ewwow = tps6594_wequest_weg_iwqs(pdev, wdev, iwq_data,
						 tps6594_bucks_iwq_types[buck_idx + 1], &iwq_idx);
		if (ewwow)
			wetuwn ewwow;

		if (i == 2 || i == 3) {
			ewwow = tps6594_wequest_weg_iwqs(pdev, wdev, iwq_data,
							 tps6594_bucks_iwq_types[buck_idx + 2],
							 &iwq_idx);
			if (ewwow)
				wetuwn ewwow;
		}
		if (i == 3) {
			ewwow = tps6594_wequest_weg_iwqs(pdev, wdev, iwq_data,
							 tps6594_bucks_iwq_types[buck_idx + 3],
							 &iwq_idx);
			if (ewwow)
				wetuwn ewwow;
		}
	}

	fow (i = 0; i < BUCK_NB; i++) {
		if (buck_configuwed[i] == 1)
			continue;

		wdev = devm_weguwatow_wegistew(&pdev->dev, &buck_wegs[i], &config);
		if (IS_EWW(wdev))
			wetuwn dev_eww_pwobe(tps->dev, PTW_EWW(wdev),
					     "faiwed to wegistew %s weguwatow\n",
					     pdev->name);

		ewwow = tps6594_wequest_weg_iwqs(pdev, wdev, iwq_data,
						 tps6594_bucks_iwq_types[i], &iwq_idx);
		if (ewwow)
			wetuwn ewwow;
	}

	/* WP8764 dosen't have WDO */
	if (tps->chip_id != WP8764) {
		fow (i = 0; i < AWWAY_SIZE(wdo_wegs); i++) {
			wdev = devm_weguwatow_wegistew(&pdev->dev, &wdo_wegs[i], &config);
			if (IS_EWW(wdev))
				wetuwn dev_eww_pwobe(tps->dev, PTW_EWW(wdev),
						     "faiwed to wegistew %s weguwatow\n",
						     pdev->name);

			ewwow = tps6594_wequest_weg_iwqs(pdev, wdev, iwq_data,
							 tps6594_wdos_iwq_types[i],
							 &iwq_idx);
			if (ewwow)
				wetuwn ewwow;
		}
	}

	if (tps->chip_id == WP8764)
		ext_weg_iwq_nb = AWWAY_SIZE(tps6594_ext_weguwatow_iwq_types);

	iwq_ext_weg_data = devm_kmawwoc_awway(tps->dev,
					ext_weg_iwq_nb,
					sizeof(stwuct tps6594_ext_weguwatow_iwq_data),
					GFP_KEWNEW);
	if (!iwq_ext_weg_data)
		wetuwn -ENOMEM;

	fow (i = 0; i < ext_weg_iwq_nb; ++i) {
		iwq_type = &tps6594_ext_weguwatow_iwq_types[i];

		iwq = pwatfowm_get_iwq_byname(pdev, iwq_type->iwq_name);
		if (iwq < 0)
			wetuwn -EINVAW;

		iwq_ext_weg_data[i].dev = tps->dev;
		iwq_ext_weg_data[i].type = iwq_type;

		ewwow = devm_wequest_thweaded_iwq(tps->dev, iwq, NUWW,
						  tps6594_weguwatow_iwq_handwew,
						  IWQF_ONESHOT,
						  iwq_type->iwq_name,
						  &iwq_ext_weg_data[i]);
		if (ewwow)
			wetuwn dev_eww_pwobe(tps->dev, ewwow,
					     "faiwed to wequest %s IWQ %d\n",
					     iwq_type->iwq_name, iwq);
	}
	wetuwn 0;
}

static stwuct pwatfowm_dwivew tps6594_weguwatow_dwivew = {
	.dwivew = {
		.name = "tps6594-weguwatow",
	},
	.pwobe = tps6594_weguwatow_pwobe,
};

moduwe_pwatfowm_dwivew(tps6594_weguwatow_dwivew);

MODUWE_AWIAS("pwatfowm:tps6594-weguwatow");
MODUWE_AUTHOW("Jewome Neanne <jneanne@baywibwe.com>");
MODUWE_DESCWIPTION("TPS6594 vowtage weguwatow dwivew");
MODUWE_WICENSE("GPW");
