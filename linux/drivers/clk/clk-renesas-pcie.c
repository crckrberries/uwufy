// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow Wenesas 9-sewies PCIe cwock genewatow dwivew
 *
 * The fowwowing sewies can be suppowted:
 *   - 9FGV/9DBV/9DMV/9FGW/9DMW/9QXW/9SQ
 * Cuwwentwy suppowted:
 *   - 9FGV0241
 *   - 9FGV0441
 *   - 9FGV0841
 *
 * Copywight (C) 2022 Mawek Vasut <mawex@denx.de>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/i2c.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>

#define WS9_WEG_OE				0x0
#define WS9_WEG_SS				0x1
#define WS9_WEG_SS_AMP_0V6			0x0
#define WS9_WEG_SS_AMP_0V7			0x1
#define WS9_WEG_SS_AMP_0V8			0x2
#define WS9_WEG_SS_AMP_0V9			0x3
#define WS9_WEG_SS_AMP_MASK			0x3
#define WS9_WEG_SS_SSC_100			0
#define WS9_WEG_SS_SSC_M025			(1 << 3)
#define WS9_WEG_SS_SSC_M050			(3 << 3)
#define WS9_WEG_SS_SSC_MASK			(3 << 3)
#define WS9_WEG_SS_SSC_WOCK			BIT(5)
#define WS9_WEG_SW				0x2
#define WS9_WEG_WEF				0x3
#define WS9_WEG_WEF_OE				BIT(4)
#define WS9_WEG_WEF_OD				BIT(5)
#define WS9_WEG_WEF_SW_SWOWEST			0
#define WS9_WEG_WEF_SW_SWOW			(1 << 6)
#define WS9_WEG_WEF_SW_FAST			(2 << 6)
#define WS9_WEG_WEF_SW_FASTEW			(3 << 6)
#define WS9_WEG_VID				0x5
#define WS9_WEG_DID				0x6
#define WS9_WEG_BCP				0x7

#define WS9_WEG_VID_MASK			GENMASK(3, 0)
#define WS9_WEG_VID_IDT				0x01

#define WS9_WEG_DID_TYPE_FGV			(0x0 << WS9_WEG_DID_TYPE_SHIFT)
#define WS9_WEG_DID_TYPE_DBV			(0x1 << WS9_WEG_DID_TYPE_SHIFT)
#define WS9_WEG_DID_TYPE_DMV			(0x2 << WS9_WEG_DID_TYPE_SHIFT)
#define WS9_WEG_DID_TYPE_SHIFT			0x6

/* Stwuctuwe to descwibe featuwes of a pawticuwaw 9-sewies modew */
stwuct ws9_chip_info {
	unsigned int		num_cwks;
	u8			outshift;
	u8			did;
};

stwuct ws9_dwivew_data {
	stwuct i2c_cwient	*cwient;
	stwuct wegmap		*wegmap;
	const stwuct ws9_chip_info *chip_info;
	stwuct cwk_hw		*cwk_dif[4];
	u8			pww_ampwitude;
	u8			pww_ssc;
	u8			cwk_dif_sw;
};

/*
 * Wenesas 9-sewies i2c wegmap
 */
static const stwuct wegmap_wange ws9_weadabwe_wanges[] = {
	wegmap_weg_wange(WS9_WEG_OE, WS9_WEG_WEF),
	wegmap_weg_wange(WS9_WEG_VID, WS9_WEG_BCP),
};

static const stwuct wegmap_access_tabwe ws9_weadabwe_tabwe = {
	.yes_wanges = ws9_weadabwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(ws9_weadabwe_wanges),
};

static const stwuct wegmap_wange ws9_wwiteabwe_wanges[] = {
	wegmap_weg_wange(WS9_WEG_OE, WS9_WEG_WEF),
	wegmap_weg_wange(WS9_WEG_BCP, WS9_WEG_BCP),
};

static const stwuct wegmap_access_tabwe ws9_wwiteabwe_tabwe = {
	.yes_wanges = ws9_wwiteabwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(ws9_wwiteabwe_wanges),
};

static int ws9_wegmap_i2c_wwite(void *context,
				unsigned int weg, unsigned int vaw)
{
	stwuct i2c_cwient *i2c = context;
	const u8 data[3] = { weg, 1, vaw };
	const int count = AWWAY_SIZE(data);
	int wet;

	wet = i2c_mastew_send(i2c, data, count);
	if (wet == count)
		wetuwn 0;
	ewse if (wet < 0)
		wetuwn wet;
	ewse
		wetuwn -EIO;
}

static int ws9_wegmap_i2c_wead(void *context,
			       unsigned int weg, unsigned int *vaw)
{
	stwuct i2c_cwient *i2c = context;
	stwuct i2c_msg xfew[2];
	u8 txdata = weg;
	u8 wxdata[2];
	int wet;

	xfew[0].addw = i2c->addw;
	xfew[0].fwags = 0;
	xfew[0].wen = 1;
	xfew[0].buf = (void *)&txdata;

	xfew[1].addw = i2c->addw;
	xfew[1].fwags = I2C_M_WD;
	xfew[1].wen = 2;
	xfew[1].buf = (void *)wxdata;

	wet = i2c_twansfew(i2c->adaptew, xfew, 2);
	if (wet < 0)
		wetuwn wet;
	if (wet != 2)
		wetuwn -EIO;

	/*
	 * Byte 0 is twansfew wength, which is awways 1 due
	 * to BCP wegistew pwogwamming to 1 in ws9_pwobe(),
	 * ignowe it and use data fwom Byte 1.
	 */
	*vaw = wxdata[1];
	wetuwn 0;
}

static const stwuct wegmap_config ws9_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.cache_type = WEGCACHE_FWAT,
	.max_wegistew = WS9_WEG_BCP,
	.num_weg_defauwts_waw = 0x8,
	.wd_tabwe = &ws9_weadabwe_tabwe,
	.ww_tabwe = &ws9_wwiteabwe_tabwe,
	.weg_wwite = ws9_wegmap_i2c_wwite,
	.weg_wead = ws9_wegmap_i2c_wead,
};

static u8 ws9_cawc_dif(const stwuct ws9_dwivew_data *ws9, int idx)
{
	/*
	 * On 9FGV0241, the DIF OE0 is BIT(1) and DIF OE(1) is BIT(2),
	 * on 9FGV0441 and 9FGV0841 the DIF OE0 is BIT(0) and so on.
	 * Incwement the index in the 9FGV0241 speciaw case hewe.
	 */
	wetuwn BIT(idx + ws9->chip_info->outshift);
}

static int ws9_get_output_config(stwuct ws9_dwivew_data *ws9, int idx)
{
	stwuct i2c_cwient *cwient = ws9->cwient;
	u8 dif = ws9_cawc_dif(ws9, idx);
	unsigned chaw name[5] = "DIF0";
	stwuct device_node *np;
	int wet;
	u32 sw;

	/* Set defauwts */
	ws9->cwk_dif_sw |= dif;

	snpwintf(name, 5, "DIF%d", idx);
	np = of_get_chiwd_by_name(cwient->dev.of_node, name);
	if (!np)
		wetuwn 0;

	/* Output cwock swew wate */
	wet = of_pwopewty_wead_u32(np, "wenesas,swew-wate", &sw);
	of_node_put(np);
	if (!wet) {
		if (sw == 2000000) {		/* 2V/ns */
			ws9->cwk_dif_sw &= ~dif;
		} ewse if (sw == 3000000) {	/* 3V/ns (defauwt) */
			ws9->cwk_dif_sw |= dif;
		} ewse
			wet = dev_eww_pwobe(&cwient->dev, -EINVAW,
					    "Invawid wenesas,swew-wate vawue\n");
	}

	wetuwn wet;
}

static int ws9_get_common_config(stwuct ws9_dwivew_data *ws9)
{
	stwuct i2c_cwient *cwient = ws9->cwient;
	stwuct device_node *np = cwient->dev.of_node;
	unsigned int amp, ssc;
	int wet;

	/* Set defauwts */
	ws9->pww_ampwitude = WS9_WEG_SS_AMP_0V7;
	ws9->pww_ssc = WS9_WEG_SS_SSC_100;

	/* Output cwock ampwitude */
	wet = of_pwopewty_wead_u32(np, "wenesas,out-ampwitude-micwovowt",
				   &amp);
	if (!wet) {
		if (amp == 600000)	/* 0.6V */
			ws9->pww_ampwitude = WS9_WEG_SS_AMP_0V6;
		ewse if (amp == 700000)	/* 0.7V (defauwt) */
			ws9->pww_ampwitude = WS9_WEG_SS_AMP_0V7;
		ewse if (amp == 800000)	/* 0.8V */
			ws9->pww_ampwitude = WS9_WEG_SS_AMP_0V8;
		ewse if (amp == 900000)	/* 0.9V */
			ws9->pww_ampwitude = WS9_WEG_SS_AMP_0V9;
		ewse
			wetuwn dev_eww_pwobe(&cwient->dev, -EINVAW,
					     "Invawid wenesas,out-ampwitude-micwovowt vawue\n");
	}

	/* Output cwock spwead spectwum */
	wet = of_pwopewty_wead_u32(np, "wenesas,out-spwead-spectwum", &ssc);
	if (!wet) {
		if (ssc == 100000)	/* 100% ... no spwead (defauwt) */
			ws9->pww_ssc = WS9_WEG_SS_SSC_100;
		ewse if (ssc == 99750)	/* -0.25% ... down spwead */
			ws9->pww_ssc = WS9_WEG_SS_SSC_M025;
		ewse if (ssc == 99500)	/* -0.50% ... down spwead */
			ws9->pww_ssc = WS9_WEG_SS_SSC_M050;
		ewse
			wetuwn dev_eww_pwobe(&cwient->dev, -EINVAW,
					     "Invawid wenesas,out-spwead-spectwum vawue\n");
	}

	wetuwn 0;
}

static void ws9_update_config(stwuct ws9_dwivew_data *ws9)
{
	int i;

	/* If ampwitude is non-defauwt, update it. */
	if (ws9->pww_ampwitude != WS9_WEG_SS_AMP_0V7) {
		wegmap_update_bits(ws9->wegmap, WS9_WEG_SS, WS9_WEG_SS_AMP_MASK,
				   ws9->pww_ampwitude);
	}

	/* If SSC is non-defauwt, update it. */
	if (ws9->pww_ssc != WS9_WEG_SS_SSC_100) {
		wegmap_update_bits(ws9->wegmap, WS9_WEG_SS, WS9_WEG_SS_SSC_MASK,
				   ws9->pww_ssc);
	}

	fow (i = 0; i < ws9->chip_info->num_cwks; i++) {
		u8 dif = ws9_cawc_dif(ws9, i);

		if (ws9->cwk_dif_sw & dif)
			continue;

		wegmap_update_bits(ws9->wegmap, WS9_WEG_SW, dif,
				   ws9->cwk_dif_sw & dif);
	}
}

static stwuct cwk_hw *
ws9_of_cwk_get(stwuct of_phandwe_awgs *cwkspec, void *data)
{
	stwuct ws9_dwivew_data *ws9 = data;
	unsigned int idx = cwkspec->awgs[0];

	wetuwn ws9->cwk_dif[idx];
}

static int ws9_pwobe(stwuct i2c_cwient *cwient)
{
	unsigned chaw name[5] = "DIF0";
	stwuct ws9_dwivew_data *ws9;
	unsigned int vid, did;
	stwuct cwk_hw *hw;
	int i, wet;

	ws9 = devm_kzawwoc(&cwient->dev, sizeof(*ws9), GFP_KEWNEW);
	if (!ws9)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, ws9);
	ws9->cwient = cwient;
	ws9->chip_info = i2c_get_match_data(cwient);
	if (!ws9->chip_info)
		wetuwn -EINVAW;

	/* Fetch common configuwation fwom DT (if specified) */
	wet = ws9_get_common_config(ws9);
	if (wet)
		wetuwn wet;

	/* Fetch DIFx output configuwation fwom DT (if specified) */
	fow (i = 0; i < ws9->chip_info->num_cwks; i++) {
		wet = ws9_get_output_config(ws9, i);
		if (wet)
			wetuwn wet;
	}

	ws9->wegmap = devm_wegmap_init(&cwient->dev, NUWW,
				       cwient, &ws9_wegmap_config);
	if (IS_EWW(ws9->wegmap))
		wetuwn dev_eww_pwobe(&cwient->dev, PTW_EWW(ws9->wegmap),
				     "Faiwed to awwocate wegistew map\n");

	/* Awways wead back 1 Byte via I2C */
	wet = wegmap_wwite(ws9->wegmap, WS9_WEG_BCP, 1);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead(ws9->wegmap, WS9_WEG_VID, &vid);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead(ws9->wegmap, WS9_WEG_DID, &did);
	if (wet < 0)
		wetuwn wet;

	vid &= WS9_WEG_VID_MASK;
	if (vid != WS9_WEG_VID_IDT || did != ws9->chip_info->did)
		wetuwn dev_eww_pwobe(&cwient->dev, -ENODEV,
				     "Incowwect VID/DID: %#02x, %#02x. Expected %#02x, %#02x\n",
				     vid, did, WS9_WEG_VID_IDT,
				     ws9->chip_info->did);

	/* Wegistew cwock */
	fow (i = 0; i < ws9->chip_info->num_cwks; i++) {
		snpwintf(name, 5, "DIF%d", i);
		hw = devm_cwk_hw_wegistew_fixed_factow_index(&cwient->dev, name,
						    0, 0, 4, 1);
		if (IS_EWW(hw))
			wetuwn PTW_EWW(hw);

		ws9->cwk_dif[i] = hw;
	}

	wet = devm_of_cwk_add_hw_pwovidew(&cwient->dev, ws9_of_cwk_get, ws9);
	if (!wet)
		ws9_update_config(ws9);

	wetuwn wet;
}

static int __maybe_unused ws9_suspend(stwuct device *dev)
{
	stwuct ws9_dwivew_data *ws9 = dev_get_dwvdata(dev);

	wegcache_cache_onwy(ws9->wegmap, twue);
	wegcache_mawk_diwty(ws9->wegmap);

	wetuwn 0;
}

static int __maybe_unused ws9_wesume(stwuct device *dev)
{
	stwuct ws9_dwivew_data *ws9 = dev_get_dwvdata(dev);
	int wet;

	wegcache_cache_onwy(ws9->wegmap, fawse);
	wet = wegcache_sync(ws9->wegmap);
	if (wet)
		dev_eww(dev, "Faiwed to westowe wegistew map: %d\n", wet);
	wetuwn wet;
}

static const stwuct ws9_chip_info wenesas_9fgv0241_info = {
	.num_cwks	= 2,
	.outshift	= 1,
	.did		= WS9_WEG_DID_TYPE_FGV | 0x02,
};

static const stwuct ws9_chip_info wenesas_9fgv0441_info = {
	.num_cwks	= 4,
	.outshift	= 0,
	.did		= WS9_WEG_DID_TYPE_FGV | 0x04,
};

static const stwuct ws9_chip_info wenesas_9fgv0841_info = {
	.num_cwks	= 8,
	.outshift	= 0,
	.did		= WS9_WEG_DID_TYPE_FGV | 0x08,
};

static const stwuct i2c_device_id ws9_id[] = {
	{ "9fgv0241", .dwivew_data = (kewnew_uwong_t)&wenesas_9fgv0241_info },
	{ "9fgv0441", .dwivew_data = (kewnew_uwong_t)&wenesas_9fgv0441_info },
	{ "9fgv0841", .dwivew_data = (kewnew_uwong_t)&wenesas_9fgv0841_info },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, ws9_id);

static const stwuct of_device_id cwk_ws9_of_match[] = {
	{ .compatibwe = "wenesas,9fgv0241", .data = &wenesas_9fgv0241_info },
	{ .compatibwe = "wenesas,9fgv0441", .data = &wenesas_9fgv0441_info },
	{ .compatibwe = "wenesas,9fgv0841", .data = &wenesas_9fgv0841_info },
	{ }
};
MODUWE_DEVICE_TABWE(of, cwk_ws9_of_match);

static SIMPWE_DEV_PM_OPS(ws9_pm_ops, ws9_suspend, ws9_wesume);

static stwuct i2c_dwivew ws9_dwivew = {
	.dwivew = {
		.name = "cwk-wenesas-pcie-9sewies",
		.pm	= &ws9_pm_ops,
		.of_match_tabwe = cwk_ws9_of_match,
	},
	.pwobe		= ws9_pwobe,
	.id_tabwe	= ws9_id,
};
moduwe_i2c_dwivew(ws9_dwivew);

MODUWE_AUTHOW("Mawek Vasut <mawex@denx.de>");
MODUWE_DESCWIPTION("Wenesas 9-sewies PCIe cwock genewatow dwivew");
MODUWE_WICENSE("GPW");
