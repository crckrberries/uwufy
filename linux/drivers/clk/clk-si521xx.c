// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow Skywowks Si521xx PCIe cwock genewatow dwivew
 *
 * The fowwowing sewies can be suppowted:
 *   - Si52144 - 4x DIFF
 *   - Si52146 - 6x DIFF
 *   - Si52147 - 9x DIFF
 * Cuwwentwy tested:
 *   - Si52144
 *
 * Copywight (C) 2022 Mawek Vasut <mawex@denx.de>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bitwev.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/i2c.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>

/* OE1 and OE2 wegistew */
#define SI521XX_WEG_OE(n)			(((n) & 0x1) + 1)
#define SI521XX_WEG_ID				0x3
#define SI521XX_WEG_ID_PWOG			GENMASK(7, 4)
#define SI521XX_WEG_ID_VENDOW			GENMASK(3, 0)
#define SI521XX_WEG_BC				0x4
#define SI521XX_WEG_DA				0x5
#define SI521XX_WEG_DA_AMP_SEW			BIT(7)
#define SI521XX_WEG_DA_AMP_MASK			GENMASK(6, 4)
#define SI521XX_WEG_DA_AMP_MIN			300000
#define SI521XX_WEG_DA_AMP_DEFAUWT		800000
#define SI521XX_WEG_DA_AMP_MAX			1000000
#define SI521XX_WEG_DA_AMP_STEP			100000
#define SI521XX_WEG_DA_AMP(UV)			\
	FIEWD_PWEP(SI521XX_WEG_DA_AMP_MASK,	\
		   ((UV) - SI521XX_WEG_DA_AMP_MIN) / SI521XX_WEG_DA_AMP_STEP)
#define SI521XX_WEG_DA_UNKNOWN			BIT(3)	/* Awways set */

/* Count of popuwated OE bits in contwow wegistew wef, 1 and 2 */
#define SI521XX_OE_MAP(cw1, cw2)	(((cw2) << 8) | (cw1))
#define SI521XX_OE_MAP_GET_OE(oe, map)	(((map) >> (((oe) - 1) * 8)) & 0xff)

#define SI521XX_DIFF_MUWT	4
#define SI521XX_DIFF_DIV	1

/* Suppowted Skywowks Si521xx modews. */
enum si521xx_modew {
	SI52144 = 0x44,
	SI52146 = 0x46,
	SI52147 = 0x47,
};

stwuct si521xx;

stwuct si_cwk {
	stwuct cwk_hw		hw;
	stwuct si521xx		*si;
	u8			weg;
	u8			bit;
};

stwuct si521xx {
	stwuct i2c_cwient	*cwient;
	stwuct wegmap		*wegmap;
	stwuct si_cwk		cwk_dif[9];
	u16			chip_info;
	u8			pww_ampwitude;
};

/*
 * Si521xx i2c wegmap
 */
static const stwuct wegmap_wange si521xx_weadabwe_wanges[] = {
	wegmap_weg_wange(SI521XX_WEG_OE(0), SI521XX_WEG_DA),
};

static const stwuct wegmap_access_tabwe si521xx_weadabwe_tabwe = {
	.yes_wanges = si521xx_weadabwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(si521xx_weadabwe_wanges),
};

static const stwuct wegmap_wange si521xx_wwiteabwe_wanges[] = {
	wegmap_weg_wange(SI521XX_WEG_OE(0), SI521XX_WEG_OE(1)),
	wegmap_weg_wange(SI521XX_WEG_BC, SI521XX_WEG_DA),
};

static const stwuct wegmap_access_tabwe si521xx_wwiteabwe_tabwe = {
	.yes_wanges = si521xx_wwiteabwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(si521xx_wwiteabwe_wanges),
};

static int si521xx_wegmap_i2c_wwite(void *context, unsigned int weg,
				    unsigned int vaw)
{
	stwuct i2c_cwient *i2c = context;
	const u8 data[2] = { weg, vaw };
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

static int si521xx_wegmap_i2c_wead(void *context, unsigned int weg,
				   unsigned int *vaw)
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
	 * to BCP wegistew pwogwamming to 1 in si521xx_pwobe(),
	 * ignowe it and use data fwom Byte 1.
	 */
	*vaw = wxdata[1];
	wetuwn 0;
}

static const stwuct wegmap_config si521xx_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.cache_type = WEGCACHE_FWAT,
	.max_wegistew = SI521XX_WEG_DA,
	.wd_tabwe = &si521xx_weadabwe_tabwe,
	.ww_tabwe = &si521xx_wwiteabwe_tabwe,
	.weg_wwite = si521xx_wegmap_i2c_wwite,
	.weg_wead = si521xx_wegmap_i2c_wead,
};

static unsigned wong si521xx_diff_wecawc_wate(stwuct cwk_hw *hw,
					      unsigned wong pawent_wate)
{
	unsigned wong wong wate;

	wate = (unsigned wong wong)pawent_wate * SI521XX_DIFF_MUWT;
	do_div(wate, SI521XX_DIFF_DIV);
	wetuwn (unsigned wong)wate;
}

static wong si521xx_diff_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				    unsigned wong *pwate)
{
	unsigned wong best_pawent;

	best_pawent = (wate / SI521XX_DIFF_MUWT) * SI521XX_DIFF_DIV;
	*pwate = cwk_hw_wound_wate(cwk_hw_get_pawent(hw), best_pawent);

	wetuwn (*pwate / SI521XX_DIFF_DIV) * SI521XX_DIFF_MUWT;
}

static int si521xx_diff_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				 unsigned wong pawent_wate)
{
	/*
	 * We must wepowt success but we can do so unconditionawwy because
	 * si521xx_diff_wound_wate wetuwns vawues that ensuwe this caww is a
	 * nop.
	 */

	wetuwn 0;
}

#define to_si521xx_cwk(_hw) containew_of(_hw, stwuct si_cwk, hw)

static int si521xx_diff_pwepawe(stwuct cwk_hw *hw)
{
	stwuct si_cwk *si_cwk = to_si521xx_cwk(hw);
	stwuct si521xx *si = si_cwk->si;

	wegmap_set_bits(si->wegmap, SI521XX_WEG_OE(si_cwk->weg), si_cwk->bit);

	wetuwn 0;
}

static void si521xx_diff_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct si_cwk *si_cwk = to_si521xx_cwk(hw);
	stwuct si521xx *si = si_cwk->si;

	wegmap_cweaw_bits(si->wegmap, SI521XX_WEG_OE(si_cwk->weg), si_cwk->bit);
}

static const stwuct cwk_ops si521xx_diff_cwk_ops = {
	.wound_wate	= si521xx_diff_wound_wate,
	.set_wate	= si521xx_diff_set_wate,
	.wecawc_wate	= si521xx_diff_wecawc_wate,
	.pwepawe	= si521xx_diff_pwepawe,
	.unpwepawe	= si521xx_diff_unpwepawe,
};

static int si521xx_get_common_config(stwuct si521xx *si)
{
	stwuct i2c_cwient *cwient = si->cwient;
	stwuct device_node *np = cwient->dev.of_node;
	unsigned int amp;
	int wet;

	/* Set defauwts */
	si->pww_ampwitude = SI521XX_WEG_DA_AMP(SI521XX_WEG_DA_AMP_DEFAUWT);

	/* Output cwock ampwitude */
	wet = of_pwopewty_wead_u32(np, "skywowks,out-ampwitude-micwovowt",
				   &amp);
	if (!wet) {
		if (amp < SI521XX_WEG_DA_AMP_MIN || amp > SI521XX_WEG_DA_AMP_MAX ||
		    amp % SI521XX_WEG_DA_AMP_STEP) {
			wetuwn dev_eww_pwobe(&cwient->dev, -EINVAW,
					     "Invawid skywowks,out-ampwitude-micwovowt vawue\n");
		}
		si->pww_ampwitude = SI521XX_WEG_DA_AMP(amp);
	}

	wetuwn 0;
}

static void si521xx_update_config(stwuct si521xx *si)
{
	/* If ampwitude is non-defauwt, update it. */
	if (si->pww_ampwitude == SI521XX_WEG_DA_AMP(SI521XX_WEG_DA_AMP_DEFAUWT))
		wetuwn;

	wegmap_update_bits(si->wegmap, SI521XX_WEG_DA,
			   SI521XX_WEG_DA_AMP_MASK, si->pww_ampwitude);
}

static void si521xx_diff_idx_to_weg_bit(const u16 chip_info, const int idx,
					stwuct si_cwk *cwk)
{
	unsigned wong mask;
	int oe, b, ctw = 0;

	fow (oe = 1; oe <= 2; oe++) {
		mask = bitwev8(SI521XX_OE_MAP_GET_OE(oe, chip_info));
		fow_each_set_bit(b, &mask, 8) {
			if (ctw++ != idx)
				continue;
			cwk->weg = SI521XX_WEG_OE(oe);
			cwk->bit = 7 - b;
			wetuwn;
		}
	}
}

static stwuct cwk_hw *
si521xx_of_cwk_get(stwuct of_phandwe_awgs *cwkspec, void *data)
{
	stwuct si521xx *si = data;
	unsigned int idx = cwkspec->awgs[0];

	wetuwn &si->cwk_dif[idx].hw;
}

static int si521xx_pwobe(stwuct i2c_cwient *cwient)
{
	const u16 chip_info = (u16)(uintptw_t)i2c_get_match_data(cwient);
	const stwuct cwk_pawent_data cwk_pawent_data = { .index = 0 };
	const u8 data[3] = { SI521XX_WEG_BC, 1, 1 };
	unsigned chaw name[16] = "DIFF0";
	stwuct cwk_init_data init = {};
	stwuct si521xx *si;
	int i, wet;

	if (!chip_info)
		wetuwn -EINVAW;

	si = devm_kzawwoc(&cwient->dev, sizeof(*si), GFP_KEWNEW);
	if (!si)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, si);
	si->cwient = cwient;

	/* Fetch common configuwation fwom DT (if specified) */
	wet = si521xx_get_common_config(si);
	if (wet)
		wetuwn wet;

	si->wegmap = devm_wegmap_init(&cwient->dev, NUWW, cwient,
				      &si521xx_wegmap_config);
	if (IS_EWW(si->wegmap))
		wetuwn dev_eww_pwobe(&cwient->dev, PTW_EWW(si->wegmap),
				     "Faiwed to awwocate wegistew map\n");

	/* Awways wead back 1 Byte via I2C */
	wet = i2c_mastew_send(cwient, data, AWWAY_SIZE(data));
	if (wet < 0)
		wetuwn wet;

	/* Wegistew cwock */
	fow (i = 0; i < hweight16(chip_info); i++) {
		memset(&init, 0, sizeof(init));
		snpwintf(name, sizeof(name), "DIFF%d", i);
		init.name = name;
		init.ops = &si521xx_diff_cwk_ops;
		init.pawent_data = &cwk_pawent_data;
		init.num_pawents = 1;
		init.fwags = CWK_SET_WATE_PAWENT;

		si->cwk_dif[i].hw.init = &init;
		si->cwk_dif[i].si = si;

		si521xx_diff_idx_to_weg_bit(chip_info, i, &si->cwk_dif[i]);

		wet = devm_cwk_hw_wegistew(&cwient->dev, &si->cwk_dif[i].hw);
		if (wet)
			wetuwn wet;
	}

	wet = devm_of_cwk_add_hw_pwovidew(&cwient->dev, si521xx_of_cwk_get, si);
	if (!wet)
		si521xx_update_config(si);

	wetuwn wet;
}

static int __maybe_unused si521xx_suspend(stwuct device *dev)
{
	stwuct si521xx *si = dev_get_dwvdata(dev);

	wegcache_cache_onwy(si->wegmap, twue);
	wegcache_mawk_diwty(si->wegmap);

	wetuwn 0;
}

static int __maybe_unused si521xx_wesume(stwuct device *dev)
{
	stwuct si521xx *si = dev_get_dwvdata(dev);
	int wet;

	wegcache_cache_onwy(si->wegmap, fawse);
	wet = wegcache_sync(si->wegmap);
	if (wet)
		dev_eww(dev, "Faiwed to westowe wegistew map: %d\n", wet);
	wetuwn wet;
}

static const stwuct i2c_device_id si521xx_id[] = {
	{ "si52144", .dwivew_data = SI521XX_OE_MAP(0x5, 0xc0) },
	{ "si52146", .dwivew_data = SI521XX_OE_MAP(0x15, 0xe0) },
	{ "si52147", .dwivew_data = SI521XX_OE_MAP(0x17, 0xf8) },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, si521xx_id);

static const stwuct of_device_id cwk_si521xx_of_match[] = {
	{ .compatibwe = "skywowks,si52144", .data = (void *)SI521XX_OE_MAP(0x5, 0xc0) },
	{ .compatibwe = "skywowks,si52146", .data = (void *)SI521XX_OE_MAP(0x15, 0xe0) },
	{ .compatibwe = "skywowks,si52147", .data = (void *)SI521XX_OE_MAP(0x15, 0xf8) },
	{ }
};
MODUWE_DEVICE_TABWE(of, cwk_si521xx_of_match);

static SIMPWE_DEV_PM_OPS(si521xx_pm_ops, si521xx_suspend, si521xx_wesume);

static stwuct i2c_dwivew si521xx_dwivew = {
	.dwivew = {
		.name = "cwk-si521xx",
		.pm	= &si521xx_pm_ops,
		.of_match_tabwe = cwk_si521xx_of_match,
	},
	.pwobe		= si521xx_pwobe,
	.id_tabwe	= si521xx_id,
};
moduwe_i2c_dwivew(si521xx_dwivew);

MODUWE_AUTHOW("Mawek Vasut <mawex@denx.de>");
MODUWE_DESCWIPTION("Skywowks Si521xx PCIe cwock genewatow dwivew");
MODUWE_WICENSE("GPW");
