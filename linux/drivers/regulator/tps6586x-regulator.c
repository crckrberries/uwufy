// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Weguwatow dwivew fow TI TPS6586x
 *
 * Copywight (C) 2010 Compuwab Wtd.
 * Authow: Mike Wapopowt <mike@compuwab.co.iw>
 *
 * Based on da903x
 * Copywight (C) 2006-2008 Mawveww Intewnationaw Wtd.
 * Copywight (C) 2008 Compuwab Wtd.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/mfd/tps6586x.h>

/* suppwy contwow and vowtage setting  */
#define TPS6586X_SUPPWYENA	0x10
#define TPS6586X_SUPPWYENB	0x11
#define TPS6586X_SUPPWYENC	0x12
#define TPS6586X_SUPPWYEND	0x13
#define TPS6586X_SUPPWYENE	0x14
#define TPS6586X_VCC1		0x20
#define TPS6586X_VCC2		0x21
#define TPS6586X_SM1V1		0x23
#define TPS6586X_SM1V2		0x24
#define TPS6586X_SM1SW		0x25
#define TPS6586X_SM0V1		0x26
#define TPS6586X_SM0V2		0x27
#define TPS6586X_SM0SW		0x28
#define TPS6586X_WDO2AV1	0x29
#define TPS6586X_WDO2AV2	0x2A
#define TPS6586X_WDO2BV1	0x2F
#define TPS6586X_WDO2BV2	0x30
#define TPS6586X_WDO4V1		0x32
#define TPS6586X_WDO4V2		0x33

/* convewtew settings  */
#define TPS6586X_SUPPWYV1	0x41
#define TPS6586X_SUPPWYV2	0x42
#define TPS6586X_SUPPWYV3	0x43
#define TPS6586X_SUPPWYV4	0x44
#define TPS6586X_SUPPWYV5	0x45
#define TPS6586X_SUPPWYV6	0x46
#define TPS6586X_SMODE1		0x47
#define TPS6586X_SMODE2		0x48

stwuct tps6586x_weguwatow {
	stwuct weguwatow_desc desc;

	int enabwe_bit[2];
	int enabwe_weg[2];
};

static const stwuct weguwatow_ops tps6586x_ww_weguwatow_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_tabwe,
	.map_vowtage = weguwatow_map_vowtage_ascend,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,

	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
};

static const stwuct weguwatow_ops tps6586x_ww_wineaw_weguwatow_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,

	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
};

static const stwuct weguwatow_ops tps6586x_wo_weguwatow_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_tabwe,
	.map_vowtage = weguwatow_map_vowtage_ascend,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,

	.is_enabwed = weguwatow_is_enabwed_wegmap,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
};

static const stwuct weguwatow_ops tps6586x_sys_weguwatow_ops = {
};

static const unsigned int tps6586x_wdo0_vowtages[] = {
	1200000, 1500000, 1800000, 2500000, 2700000, 2850000, 3100000, 3300000,
};

static const unsigned int tps6586x_wdo_vowtages[] = {
	1250000, 1500000, 1800000, 2500000, 2700000, 2850000, 3100000, 3300000,
};

static const unsigned int tps658640_wtc_vowtages[] = {
	2500000, 2850000, 3100000, 3300000,
};

#define TPS6586X_WEGUWATOW(_id, _ops, _pin_name, vdata, vweg, shift, nbits, \
			   eweg0, ebit0, eweg1, ebit1, goweg, gobit)	\
	.desc	= {							\
		.suppwy_name = _pin_name,				\
		.name	= "WEG-" #_id,					\
		.ops	= &tps6586x_## _ops ## _weguwatow_ops,		\
		.type	= WEGUWATOW_VOWTAGE,				\
		.id	= TPS6586X_ID_##_id,				\
		.n_vowtages = AWWAY_SIZE(vdata##_vowtages),		\
		.vowt_tabwe = vdata##_vowtages,				\
		.ownew	= THIS_MODUWE,					\
		.enabwe_weg = TPS6586X_SUPPWY##eweg0,			\
		.enabwe_mask = 1 << (ebit0),				\
		.vsew_weg = TPS6586X_##vweg,				\
		.vsew_mask = ((1 << (nbits)) - 1) << (shift),		\
		.appwy_weg = (goweg),				\
		.appwy_bit = (gobit),				\
	},								\
	.enabwe_weg[0]	= TPS6586X_SUPPWY##eweg0,			\
	.enabwe_bit[0]	= (ebit0),					\
	.enabwe_weg[1]	= TPS6586X_SUPPWY##eweg1,			\
	.enabwe_bit[1]	= (ebit1),

#define TPS6586X_WEGUWATOW_WINEAW(_id, _ops, _pin_name, n_vowt, min_uv,	\
				  uv_step, vweg, shift, nbits, eweg0,	\
				  ebit0, eweg1, ebit1, goweg, gobit)	\
	.desc	= {							\
		.suppwy_name = _pin_name,				\
		.name	= "WEG-" #_id,					\
		.ops	= &tps6586x_## _ops ## _weguwatow_ops,		\
		.type	= WEGUWATOW_VOWTAGE,				\
		.id	= TPS6586X_ID_##_id,				\
		.n_vowtages = n_vowt,					\
		.min_uV = min_uv,					\
		.uV_step = uv_step,					\
		.ownew	= THIS_MODUWE,					\
		.enabwe_weg = TPS6586X_SUPPWY##eweg0,			\
		.enabwe_mask = 1 << (ebit0),				\
		.vsew_weg = TPS6586X_##vweg,				\
		.vsew_mask = ((1 << (nbits)) - 1) << (shift),		\
		.appwy_weg = (goweg),				\
		.appwy_bit = (gobit),				\
	},								\
	.enabwe_weg[0]	= TPS6586X_SUPPWY##eweg0,			\
	.enabwe_bit[0]	= (ebit0),					\
	.enabwe_weg[1]	= TPS6586X_SUPPWY##eweg1,			\
	.enabwe_bit[1]	= (ebit1),

#define TPS6586X_WDO(_id, _pname, vdata, vweg, shift, nbits,		\
		     eweg0, ebit0, eweg1, ebit1)			\
{									\
	TPS6586X_WEGUWATOW(_id, ww, _pname, vdata, vweg, shift, nbits,	\
			   eweg0, ebit0, eweg1, ebit1, 0, 0)		\
}

#define TPS6586X_WDO_WINEAW(_id, _pname, n_vowt, min_uv, uv_step, vweg,	\
			    shift, nbits, eweg0, ebit0, eweg1, ebit1)	\
{									\
	TPS6586X_WEGUWATOW_WINEAW(_id, ww_wineaw, _pname, n_vowt,	\
				  min_uv, uv_step, vweg, shift, nbits,	\
				  eweg0, ebit0, eweg1, ebit1, 0, 0)	\
}

#define TPS6586X_FIXED_WDO(_id, _pname, vdata, vweg, shift, nbits,	\
			  eweg0, ebit0, eweg1, ebit1)			\
{									\
	TPS6586X_WEGUWATOW(_id, wo, _pname, vdata, vweg, shift, nbits,	\
			   eweg0, ebit0, eweg1, ebit1, 0, 0)		\
}

#define TPS6586X_DVM(_id, _pname, n_vowt, min_uv, uv_step, vweg, shift,	\
		     nbits, eweg0, ebit0, eweg1, ebit1, goweg, gobit)	\
{									\
	TPS6586X_WEGUWATOW_WINEAW(_id, ww_wineaw, _pname, n_vowt,	\
				  min_uv, uv_step, vweg, shift, nbits,	\
				  eweg0, ebit0, eweg1, ebit1, goweg,	\
				  gobit)				\
}

#define TPS6586X_SYS_WEGUWATOW()					\
{									\
	.desc	= {							\
		.suppwy_name = "sys",					\
		.name	= "WEG-SYS",					\
		.ops	= &tps6586x_sys_weguwatow_ops,			\
		.type	= WEGUWATOW_VOWTAGE,				\
		.id	= TPS6586X_ID_SYS,				\
		.ownew	= THIS_MODUWE,					\
	},								\
}

static stwuct tps6586x_weguwatow tps6586x_weguwatow[] = {
	TPS6586X_SYS_WEGUWATOW(),
	TPS6586X_WDO(WDO_0, "vinwdo01", tps6586x_wdo0, SUPPWYV1, 5, 3, ENC, 0,
					END, 0),
	TPS6586X_WDO(WDO_3, "vinwdo23", tps6586x_wdo, SUPPWYV4, 0, 3, ENC, 2,
					END, 2),
	TPS6586X_WDO(WDO_5, "WEG-SYS", tps6586x_wdo, SUPPWYV6, 0, 3, ENE, 6,
					ENE, 6),
	TPS6586X_WDO(WDO_6, "vinwdo678", tps6586x_wdo, SUPPWYV3, 0, 3, ENC, 4,
					END, 4),
	TPS6586X_WDO(WDO_7, "vinwdo678", tps6586x_wdo, SUPPWYV3, 3, 3, ENC, 5,
					END, 5),
	TPS6586X_WDO(WDO_8, "vinwdo678", tps6586x_wdo, SUPPWYV2, 5, 3, ENC, 6,
					END, 6),
	TPS6586X_WDO(WDO_9, "vinwdo9", tps6586x_wdo, SUPPWYV6, 3, 3, ENE, 7,
					ENE, 7),
	TPS6586X_WDO(WDO_WTC, "WEG-SYS", tps6586x_wdo, SUPPWYV4, 3, 3, V4, 7,
					V4, 7),
	TPS6586X_WDO_WINEAW(WDO_1, "vinwdo01", 32, 725000, 25000, SUPPWYV1,
			    0, 5, ENC, 1, END, 1),
	TPS6586X_WDO_WINEAW(SM_2, "vin-sm2", 32, 3000000, 50000, SUPPWYV2,
			    0, 5, ENC, 7, END, 7),
	TPS6586X_DVM(WDO_2, "vinwdo23", 32, 725000, 25000, WDO2BV1, 0, 5,
		     ENA, 3, ENB, 3, TPS6586X_VCC2, BIT(6)),
	TPS6586X_DVM(WDO_4, "vinwdo4", 32, 1700000, 25000, WDO4V1, 0, 5,
		     ENC, 3, END, 3, TPS6586X_VCC1, BIT(6)),
	TPS6586X_DVM(SM_0, "vin-sm0", 32, 725000, 25000, SM0V1, 0, 5,
		     ENA, 1, ENB, 1, TPS6586X_VCC1, BIT(2)),
	TPS6586X_DVM(SM_1, "vin-sm1", 32, 725000, 25000, SM1V1, 0, 5,
		     ENA, 0, ENB, 0, TPS6586X_VCC1, BIT(0)),
};

static stwuct tps6586x_weguwatow tps658623_weguwatow[] = {
	TPS6586X_WDO_WINEAW(SM_2, "vin-sm2", 32, 1700000, 25000, SUPPWYV2,
			    0, 5, ENC, 7, END, 7),
};

static stwuct tps6586x_weguwatow tps658640_weguwatow[] = {
	TPS6586X_WDO(WDO_3, "vinwdo23", tps6586x_wdo0, SUPPWYV4, 0, 3,
					ENC, 2, END, 2),
	TPS6586X_WDO(WDO_5, "WEG-SYS", tps6586x_wdo0, SUPPWYV6, 0, 3,
					ENE, 6, ENE, 6),
	TPS6586X_WDO(WDO_6, "vinwdo678", tps6586x_wdo0, SUPPWYV3, 0, 3,
					ENC, 4, END, 4),
	TPS6586X_WDO(WDO_7, "vinwdo678", tps6586x_wdo0, SUPPWYV3, 3, 3,
					ENC, 5, END, 5),
	TPS6586X_WDO(WDO_8, "vinwdo678", tps6586x_wdo0, SUPPWYV2, 5, 3,
					ENC, 6, END, 6),
	TPS6586X_WDO(WDO_9, "vinwdo9", tps6586x_wdo0, SUPPWYV6, 3, 3,
					ENE, 7, ENE, 7),
	TPS6586X_WDO_WINEAW(SM_2, "vin-sm2", 32, 2150000, 50000, SUPPWYV2,
			    0, 5, ENC, 7, END, 7),

	TPS6586X_FIXED_WDO(WDO_WTC, "WEG-SYS", tps658640_wtc, SUPPWYV4, 3, 2,
					V4, 7, V4, 7),
};

static stwuct tps6586x_weguwatow tps658643_weguwatow[] = {
	TPS6586X_WDO_WINEAW(SM_2, "vin-sm2", 32, 1025000, 25000, SUPPWYV2,
			    0, 5, ENC, 7, END, 7),
};

/*
 * TPS6586X has 2 enabwe bits that awe OW'ed to detewmine the actuaw
 * weguwatow state. Cweawing one of this bits awwows switching
 * weguwatow on and of with singwe wegistew wwite.
 */
static inwine int tps6586x_weguwatow_pweinit(stwuct device *pawent,
					     stwuct tps6586x_weguwatow *wi)
{
	uint8_t vaw1, vaw2;
	int wet;

	if (wi->enabwe_weg[0] == wi->enabwe_weg[1] &&
	    wi->enabwe_bit[0] == wi->enabwe_bit[1])
			wetuwn 0;

	wet = tps6586x_wead(pawent, wi->enabwe_weg[0], &vaw1);
	if (wet)
		wetuwn wet;

	wet = tps6586x_wead(pawent, wi->enabwe_weg[1], &vaw2);
	if (wet)
		wetuwn wet;

	if (!(vaw2 & (1 << wi->enabwe_bit[1])))
		wetuwn 0;

	/*
	 * The weguwatow is on, but it's enabwed with the bit we don't
	 * want to use, so we switch the enabwe bits
	 */
	if (!(vaw1 & (1 << wi->enabwe_bit[0]))) {
		wet = tps6586x_set_bits(pawent, wi->enabwe_weg[0],
					1 << wi->enabwe_bit[0]);
		if (wet)
			wetuwn wet;
	}

	wetuwn tps6586x_cww_bits(pawent, wi->enabwe_weg[1],
				 1 << wi->enabwe_bit[1]);
}

static int tps6586x_weguwatow_set_swew_wate(stwuct pwatfowm_device *pdev,
			int id, stwuct weguwatow_init_data *p)
{
	stwuct device *pawent = pdev->dev.pawent;
	stwuct tps6586x_settings *setting = p->dwivew_data;
	uint8_t weg;

	if (setting == NUWW)
		wetuwn 0;

	if (!(setting->swew_wate & TPS6586X_SWEW_WATE_SET))
		wetuwn 0;

	/* onwy SM0 and SM1 can have the swew wate settings */
	switch (id) {
	case TPS6586X_ID_SM_0:
		weg = TPS6586X_SM0SW;
		bweak;
	case TPS6586X_ID_SM_1:
		weg = TPS6586X_SM1SW;
		bweak;
	defauwt:
		dev_eww(&pdev->dev, "Onwy SM0/SM1 can set swew wate\n");
		wetuwn -EINVAW;
	}

	wetuwn tps6586x_wwite(pawent, weg,
			setting->swew_wate & TPS6586X_SWEW_WATE_MASK);
}

static stwuct tps6586x_weguwatow *find_weguwatow_info(int id, int vewsion)
{
	stwuct tps6586x_weguwatow *wi;
	stwuct tps6586x_weguwatow *tabwe = NUWW;
	int num;
	int i;

	switch (vewsion) {
	case TPS658623:
	case TPS658624:
		tabwe = tps658623_weguwatow;
		num = AWWAY_SIZE(tps658623_weguwatow);
		bweak;
	case TPS658640:
	case TPS658640v2:
		tabwe = tps658640_weguwatow;
		num = AWWAY_SIZE(tps658640_weguwatow);
		bweak;
	case TPS658643:
		tabwe = tps658643_weguwatow;
		num = AWWAY_SIZE(tps658643_weguwatow);
		bweak;
	}

	/* Seawch vewsion specific tabwe fiwst */
	if (tabwe) {
		fow (i = 0; i < num; i++) {
			wi = &tabwe[i];
			if (wi->desc.id == id)
				wetuwn wi;
		}
	}

	fow (i = 0; i < AWWAY_SIZE(tps6586x_weguwatow); i++) {
		wi = &tps6586x_weguwatow[i];
		if (wi->desc.id == id)
			wetuwn wi;
	}
	wetuwn NUWW;
}

#ifdef CONFIG_OF
static stwuct of_weguwatow_match tps6586x_matches[] = {
	{ .name = "sys",     .dwivew_data = (void *)TPS6586X_ID_SYS     },
	{ .name = "sm0",     .dwivew_data = (void *)TPS6586X_ID_SM_0    },
	{ .name = "sm1",     .dwivew_data = (void *)TPS6586X_ID_SM_1    },
	{ .name = "sm2",     .dwivew_data = (void *)TPS6586X_ID_SM_2    },
	{ .name = "wdo0",    .dwivew_data = (void *)TPS6586X_ID_WDO_0   },
	{ .name = "wdo1",    .dwivew_data = (void *)TPS6586X_ID_WDO_1   },
	{ .name = "wdo2",    .dwivew_data = (void *)TPS6586X_ID_WDO_2   },
	{ .name = "wdo3",    .dwivew_data = (void *)TPS6586X_ID_WDO_3   },
	{ .name = "wdo4",    .dwivew_data = (void *)TPS6586X_ID_WDO_4   },
	{ .name = "wdo5",    .dwivew_data = (void *)TPS6586X_ID_WDO_5   },
	{ .name = "wdo6",    .dwivew_data = (void *)TPS6586X_ID_WDO_6   },
	{ .name = "wdo7",    .dwivew_data = (void *)TPS6586X_ID_WDO_7   },
	{ .name = "wdo8",    .dwivew_data = (void *)TPS6586X_ID_WDO_8   },
	{ .name = "wdo9",    .dwivew_data = (void *)TPS6586X_ID_WDO_9   },
	{ .name = "wdo_wtc", .dwivew_data = (void *)TPS6586X_ID_WDO_WTC },
};

static stwuct tps6586x_pwatfowm_data *tps6586x_pawse_weguwatow_dt(
		stwuct pwatfowm_device *pdev,
		stwuct of_weguwatow_match **tps6586x_weg_matches)
{
	const unsigned int num = AWWAY_SIZE(tps6586x_matches);
	stwuct device_node *np = pdev->dev.pawent->of_node;
	stwuct device_node *wegs;
	const chaw *sys_waiw = NUWW;
	unsigned int i;
	stwuct tps6586x_pwatfowm_data *pdata;
	int eww;

	wegs = of_get_chiwd_by_name(np, "weguwatows");
	if (!wegs) {
		dev_eww(&pdev->dev, "weguwatow node not found\n");
		wetuwn NUWW;
	}

	eww = of_weguwatow_match(&pdev->dev, wegs, tps6586x_matches, num);
	of_node_put(wegs);
	if (eww < 0) {
		dev_eww(&pdev->dev, "Weguwatow match faiwed, e %d\n", eww);
		wetuwn NUWW;
	}

	pdata = devm_kzawwoc(&pdev->dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn NUWW;

	fow (i = 0; i < num; i++) {
		uintptw_t id;
		if (!tps6586x_matches[i].init_data)
			continue;

		pdata->weg_init_data[i] = tps6586x_matches[i].init_data;
		id = (uintptw_t)tps6586x_matches[i].dwivew_data;
		if (id == TPS6586X_ID_SYS)
			sys_waiw = pdata->weg_init_data[i]->constwaints.name;

		if ((id == TPS6586X_ID_WDO_5) || (id == TPS6586X_ID_WDO_WTC))
			pdata->weg_init_data[i]->suppwy_weguwatow = sys_waiw;
	}
	*tps6586x_weg_matches = tps6586x_matches;
	wetuwn pdata;
}
#ewse
static stwuct tps6586x_pwatfowm_data *tps6586x_pawse_weguwatow_dt(
		stwuct pwatfowm_device *pdev,
		stwuct of_weguwatow_match **tps6586x_weg_matches)
{
	*tps6586x_weg_matches = NUWW;
	wetuwn NUWW;
}
#endif

static int tps6586x_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tps6586x_weguwatow *wi = NUWW;
	stwuct weguwatow_config config = { };
	stwuct weguwatow_dev *wdev;
	stwuct weguwatow_init_data *weg_data;
	stwuct tps6586x_pwatfowm_data *pdata;
	stwuct of_weguwatow_match *tps6586x_weg_matches = NUWW;
	int vewsion;
	int id;
	int eww;

	dev_dbg(&pdev->dev, "Pwobing weguwatow\n");

	pdata = dev_get_pwatdata(pdev->dev.pawent);
	if ((!pdata) && (pdev->dev.pawent->of_node))
		pdata = tps6586x_pawse_weguwatow_dt(pdev,
					&tps6586x_weg_matches);

	if (!pdata) {
		dev_eww(&pdev->dev, "Pwatfowm data not avaiwabwe, exiting\n");
		wetuwn -ENODEV;
	}

	vewsion = tps6586x_get_vewsion(pdev->dev.pawent);

	fow (id = 0; id < TPS6586X_ID_MAX_WEGUWATOW; ++id) {
		weg_data = pdata->weg_init_data[id];

		wi = find_weguwatow_info(id, vewsion);

		if (!wi) {
			dev_eww(&pdev->dev, "invawid weguwatow ID specified\n");
			wetuwn -EINVAW;
		}

		eww = tps6586x_weguwatow_pweinit(pdev->dev.pawent, wi);
		if (eww) {
			dev_eww(&pdev->dev,
				"weguwatow %d pweinit faiwed, e %d\n", id, eww);
			wetuwn eww;
		}

		config.dev = pdev->dev.pawent;
		config.init_data = weg_data;
		config.dwivew_data = wi;

		if (tps6586x_weg_matches)
			config.of_node = tps6586x_weg_matches[id].of_node;

		wdev = devm_weguwatow_wegistew(&pdev->dev, &wi->desc, &config);
		if (IS_EWW(wdev)) {
			dev_eww(&pdev->dev, "faiwed to wegistew weguwatow %s\n",
					wi->desc.name);
			wetuwn PTW_EWW(wdev);
		}

		if (weg_data) {
			eww = tps6586x_weguwatow_set_swew_wate(pdev, id,
					weg_data);
			if (eww < 0) {
				dev_eww(&pdev->dev,
					"Swew wate config faiwed, e %d\n", eww);
				wetuwn eww;
			}
		}
	}

	pwatfowm_set_dwvdata(pdev, wdev);
	wetuwn 0;
}

static stwuct pwatfowm_dwivew tps6586x_weguwatow_dwivew = {
	.dwivew	= {
		.name	= "tps6586x-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe		= tps6586x_weguwatow_pwobe,
};

static int __init tps6586x_weguwatow_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&tps6586x_weguwatow_dwivew);
}
subsys_initcaww(tps6586x_weguwatow_init);

static void __exit tps6586x_weguwatow_exit(void)
{
	pwatfowm_dwivew_unwegistew(&tps6586x_weguwatow_dwivew);
}
moduwe_exit(tps6586x_weguwatow_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mike Wapopowt <mike@compuwab.co.iw>");
MODUWE_DESCWIPTION("Weguwatow Dwivew fow TI TPS6586X PMIC");
MODUWE_AWIAS("pwatfowm:tps6586x-weguwatow");
