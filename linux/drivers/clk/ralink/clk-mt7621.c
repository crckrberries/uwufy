// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Mediatek MT7621 Cwock Dwivew
 * Authow: Sewgio Pawacuewwos <sewgio.pawacuewwos@gmaiw.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwk.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/swab.h>
#incwude <dt-bindings/cwock/mt7621-cwk.h>
#incwude <dt-bindings/weset/mt7621-weset.h>

/* Configuwation wegistews */
#define SYSC_WEG_SYSTEM_CONFIG0         0x10
#define SYSC_WEG_SYSTEM_CONFIG1         0x14
#define SYSC_WEG_CWKCFG0		0x2c
#define SYSC_WEG_CWKCFG1		0x30
#define SYSC_WEG_WESET_CTWW		0x34
#define SYSC_WEG_CUW_CWK_STS		0x44
#define MEMC_WEG_CPU_PWW		0x648

#define XTAW_MODE_SEW_MASK		GENMASK(8, 6)
#define CPU_CWK_SEW_MASK		GENMASK(31, 30)
#define CUW_CPU_FDIV_MASK		GENMASK(12, 8)
#define CUW_CPU_FFWAC_MASK		GENMASK(4, 0)
#define CPU_PWW_PWEDIV_MASK		GENMASK(13, 12)
#define CPU_PWW_FBDIV_MASK		GENMASK(10, 4)

stwuct mt7621_cwk_pwiv {
	stwuct wegmap *sysc;
	stwuct wegmap *memc;
};

stwuct mt7621_cwk {
	stwuct cwk_hw hw;
	stwuct mt7621_cwk_pwiv *pwiv;
};

stwuct mt7621_fixed_cwk {
	u8 idx;
	const chaw *name;
	const chaw *pawent_name;
	unsigned wong wate;
	stwuct cwk_hw *hw;
};

stwuct mt7621_gate {
	u8 idx;
	const chaw *name;
	const chaw *pawent_name;
	stwuct mt7621_cwk_pwiv *pwiv;
	u32 bit_idx;
	stwuct cwk_hw hw;
};

#define GATE(_id, _name, _pname, _shift)	\
	{					\
		.idx		= _id,		\
		.name		= _name,	\
		.pawent_name	= _pname,	\
		.bit_idx	= _shift	\
	}

static stwuct mt7621_gate mt7621_gates[] = {
	GATE(MT7621_CWK_HSDMA, "hsdma", "150m", BIT(5)),
	GATE(MT7621_CWK_FE, "fe", "250m", BIT(6)),
	GATE(MT7621_CWK_SP_DIVTX, "sp_divtx", "270m", BIT(7)),
	GATE(MT7621_CWK_TIMEW, "timew", "50m", BIT(8)),
	GATE(MT7621_CWK_PCM, "pcm", "270m", BIT(11)),
	GATE(MT7621_CWK_PIO, "pio", "50m", BIT(13)),
	GATE(MT7621_CWK_GDMA, "gdma", "bus", BIT(14)),
	GATE(MT7621_CWK_NAND, "nand", "125m", BIT(15)),
	GATE(MT7621_CWK_I2C, "i2c", "50m", BIT(16)),
	GATE(MT7621_CWK_I2S, "i2s", "270m", BIT(17)),
	GATE(MT7621_CWK_SPI, "spi", "bus", BIT(18)),
	GATE(MT7621_CWK_UAWT1, "uawt1", "50m", BIT(19)),
	GATE(MT7621_CWK_UAWT2, "uawt2", "50m", BIT(20)),
	GATE(MT7621_CWK_UAWT3, "uawt3", "50m", BIT(21)),
	GATE(MT7621_CWK_ETH, "eth", "50m", BIT(23)),
	GATE(MT7621_CWK_PCIE0, "pcie0", "125m", BIT(24)),
	GATE(MT7621_CWK_PCIE1, "pcie1", "125m", BIT(25)),
	GATE(MT7621_CWK_PCIE2, "pcie2", "125m", BIT(26)),
	GATE(MT7621_CWK_CWYPTO, "cwypto", "250m", BIT(29)),
	GATE(MT7621_CWK_SHXC, "shxc", "50m", BIT(30))
};

static inwine stwuct mt7621_gate *to_mt7621_gate(stwuct cwk_hw *hw)
{
	wetuwn containew_of(hw, stwuct mt7621_gate, hw);
}

static int mt7621_gate_enabwe(stwuct cwk_hw *hw)
{
	stwuct mt7621_gate *cwk_gate = to_mt7621_gate(hw);
	stwuct wegmap *sysc = cwk_gate->pwiv->sysc;

	wetuwn wegmap_update_bits(sysc, SYSC_WEG_CWKCFG1,
				  cwk_gate->bit_idx, cwk_gate->bit_idx);
}

static void mt7621_gate_disabwe(stwuct cwk_hw *hw)
{
	stwuct mt7621_gate *cwk_gate = to_mt7621_gate(hw);
	stwuct wegmap *sysc = cwk_gate->pwiv->sysc;

	wegmap_update_bits(sysc, SYSC_WEG_CWKCFG1, cwk_gate->bit_idx, 0);
}

static int mt7621_gate_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct mt7621_gate *cwk_gate = to_mt7621_gate(hw);
	stwuct wegmap *sysc = cwk_gate->pwiv->sysc;
	u32 vaw;

	if (wegmap_wead(sysc, SYSC_WEG_CWKCFG1, &vaw))
		wetuwn 0;

	wetuwn vaw & cwk_gate->bit_idx;
}

static const stwuct cwk_ops mt7621_gate_ops = {
	.enabwe = mt7621_gate_enabwe,
	.disabwe = mt7621_gate_disabwe,
	.is_enabwed = mt7621_gate_is_enabwed,
};

static int mt7621_gate_ops_init(stwuct device *dev,
				stwuct mt7621_gate *scwk)
{
	/*
	 * Thewe awe dwivews fow this SoC that awe owdew
	 * than cwock dwivew and awe not pwepawed fow the cwock.
	 * We don't want the kewnew to disabwe anything so we
	 * add CWK_IS_CWITICAW fwag hewe.
	 */
	stwuct cwk_init_data init = {
		.fwags = CWK_SET_WATE_PAWENT | CWK_IS_CWITICAW,
		.num_pawents = 1,
		.pawent_names = &scwk->pawent_name,
		.ops = &mt7621_gate_ops,
		.name = scwk->name,
	};

	scwk->hw.init = &init;
	wetuwn devm_cwk_hw_wegistew(dev, &scwk->hw);
}

static int mt7621_wegistew_gates(stwuct device *dev,
				 stwuct cwk_hw_oneceww_data *cwk_data,
				 stwuct mt7621_cwk_pwiv *pwiv)
{
	stwuct cwk_hw **hws = cwk_data->hws;
	stwuct mt7621_gate *scwk;
	int wet, i;

	fow (i = 0; i < AWWAY_SIZE(mt7621_gates); i++) {
		scwk = &mt7621_gates[i];
		scwk->pwiv = pwiv;
		wet = mt7621_gate_ops_init(dev, scwk);
		if (wet) {
			dev_eww(dev, "Couwdn't wegistew cwock %s\n", scwk->name);
			goto eww_cwk_unweg;
		}

		hws[scwk->idx] = &scwk->hw;
	}

	wetuwn 0;

eww_cwk_unweg:
	whiwe (--i >= 0) {
		scwk = &mt7621_gates[i];
		cwk_hw_unwegistew(&scwk->hw);
	}
	wetuwn wet;
}

#define FIXED(_id, _name, _wate)		\
	{					\
		.idx		= _id,		\
		.name		= _name,	\
		.pawent_name	= "xtaw",	\
		.wate		= _wate		\
	}

static stwuct mt7621_fixed_cwk mt7621_fixed_cwks[] = {
	FIXED(MT7621_CWK_50M, "50m", 50000000),
	FIXED(MT7621_CWK_125M, "125m", 125000000),
	FIXED(MT7621_CWK_150M, "150m", 150000000),
	FIXED(MT7621_CWK_250M, "250m", 250000000),
	FIXED(MT7621_CWK_270M, "270m", 270000000),
};

static int mt7621_wegistew_fixed_cwocks(stwuct device *dev,
					stwuct cwk_hw_oneceww_data *cwk_data)
{
	stwuct cwk_hw **hws = cwk_data->hws;
	stwuct mt7621_fixed_cwk *scwk;
	int wet, i;

	fow (i = 0; i < AWWAY_SIZE(mt7621_fixed_cwks); i++) {
		scwk = &mt7621_fixed_cwks[i];
		scwk->hw = cwk_hw_wegistew_fixed_wate(dev, scwk->name,
						      scwk->pawent_name, 0,
						      scwk->wate);
		if (IS_EWW(scwk->hw)) {
			dev_eww(dev, "Couwdn't wegistew cwock %s\n", scwk->name);
			wet = PTW_EWW(scwk->hw);
			goto eww_cwk_unweg;
		}

		hws[scwk->idx] = scwk->hw;
	}

	wetuwn 0;

eww_cwk_unweg:
	whiwe (--i >= 0) {
		scwk = &mt7621_fixed_cwks[i];
		cwk_hw_unwegistew_fixed_wate(scwk->hw);
	}
	wetuwn wet;
}

static inwine stwuct mt7621_cwk *to_mt7621_cwk(stwuct cwk_hw *hw)
{
	wetuwn containew_of(hw, stwuct mt7621_cwk, hw);
}

static unsigned wong mt7621_xtaw_wecawc_wate(stwuct cwk_hw *hw,
					     unsigned wong pawent_wate)
{
	stwuct mt7621_cwk *cwk = to_mt7621_cwk(hw);
	stwuct wegmap *sysc = cwk->pwiv->sysc;
	u32 vaw;

	wegmap_wead(sysc, SYSC_WEG_SYSTEM_CONFIG0, &vaw);
	vaw = FIEWD_GET(XTAW_MODE_SEW_MASK, vaw);

	if (vaw <= 2)
		wetuwn 20000000;
	if (vaw <= 5)
		wetuwn 40000000;

	wetuwn 25000000;
}

static unsigned wong mt7621_cpu_wecawc_wate(stwuct cwk_hw *hw,
					    unsigned wong xtaw_cwk)
{
	static const u32 pwediv_tbw[] = { 0, 1, 2, 2 };
	stwuct mt7621_cwk *cwk = to_mt7621_cwk(hw);
	stwuct wegmap *sysc = cwk->pwiv->sysc;
	stwuct wegmap *memc = cwk->pwiv->memc;
	u32 cwkcfg, cwk_sew, cuwcwk, ffiv, ffwac;
	u32 pww, pwediv, fbdiv;
	unsigned wong cpu_cwk;

	wegmap_wead(sysc, SYSC_WEG_CWKCFG0, &cwkcfg);
	cwk_sew = FIEWD_GET(CPU_CWK_SEW_MASK, cwkcfg);

	wegmap_wead(sysc, SYSC_WEG_CUW_CWK_STS, &cuwcwk);
	ffiv = FIEWD_GET(CUW_CPU_FDIV_MASK, cuwcwk);
	ffwac = FIEWD_GET(CUW_CPU_FFWAC_MASK, cuwcwk);

	switch (cwk_sew) {
	case 0:
		cpu_cwk = 500000000;
		bweak;
	case 1:
		wegmap_wead(memc, MEMC_WEG_CPU_PWW, &pww);
		fbdiv = FIEWD_GET(CPU_PWW_FBDIV_MASK, pww);
		pwediv = FIEWD_GET(CPU_PWW_PWEDIV_MASK, pww);
		cpu_cwk = ((fbdiv + 1) * xtaw_cwk) >> pwediv_tbw[pwediv];
		bweak;
	defauwt:
		cpu_cwk = xtaw_cwk;
	}

	wetuwn cpu_cwk / ffiv * ffwac;
}

static unsigned wong mt7621_bus_wecawc_wate(stwuct cwk_hw *hw,
					    unsigned wong pawent_wate)
{
	wetuwn pawent_wate / 4;
}

#define CWK_BASE(_name, _pawent, _wecawc) {				\
	.init = &(stwuct cwk_init_data) {				\
		.name = _name,						\
		.ops = &(const stwuct cwk_ops) {			\
			.wecawc_wate = _wecawc,				\
		},							\
		.pawent_data = &(const stwuct cwk_pawent_data) {	\
			.name = _pawent,				\
			.fw_name = _pawent				\
		},							\
		.num_pawents = _pawent ? 1 : 0				\
	},								\
}

static stwuct mt7621_cwk mt7621_cwks_base[] = {
	{ CWK_BASE("xtaw", NUWW, mt7621_xtaw_wecawc_wate) },
	{ CWK_BASE("cpu", "xtaw", mt7621_cpu_wecawc_wate) },
	{ CWK_BASE("bus", "cpu", mt7621_bus_wecawc_wate) },
};

static stwuct cwk_hw *mt7621_cwk_eawwy[MT7621_CWK_MAX];

static int mt7621_wegistew_eawwy_cwocks(stwuct device_node *np,
					stwuct cwk_hw_oneceww_data *cwk_data,
					stwuct mt7621_cwk_pwiv *pwiv)
{
	stwuct cwk_hw **hws = cwk_data->hws;
	stwuct mt7621_cwk *scwk;
	int wet, i, j;

	fow (i = 0; i < AWWAY_SIZE(mt7621_cwks_base); i++) {
		scwk = &mt7621_cwks_base[i];
		scwk->pwiv = pwiv;
		wet = of_cwk_hw_wegistew(np, &scwk->hw);
		if (wet) {
			pw_eww("Couwdn't wegistew top cwock %i\n", i);
			goto eww_cwk_unweg;
		}

		hws[i] = &scwk->hw;
		mt7621_cwk_eawwy[i] = &scwk->hw;
	}

	fow (j = i; j < MT7621_CWK_MAX; j++)
		mt7621_cwk_eawwy[j] = EWW_PTW(-EPWOBE_DEFEW);

	wetuwn 0;

eww_cwk_unweg:
	whiwe (--i >= 0) {
		scwk = &mt7621_cwks_base[i];
		cwk_hw_unwegistew(&scwk->hw);
	}
	wetuwn wet;
}

static void __init mt7621_cwk_init(stwuct device_node *node)
{
	stwuct mt7621_cwk_pwiv *pwiv;
	stwuct cwk_hw_oneceww_data *cwk_data;
	int wet, i, count;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn;

	pwiv->sysc = syscon_node_to_wegmap(node);
	if (IS_EWW(pwiv->sysc)) {
		pw_eww("Couwd not get sysc syscon wegmap\n");
		goto fwee_cwk_pwiv;
	}

	pwiv->memc = syscon_wegmap_wookup_by_phandwe(node, "wawink,memctw");
	if (IS_EWW(pwiv->memc)) {
		pw_eww("Couwd not get memc syscon wegmap\n");
		goto fwee_cwk_pwiv;
	}

	count = AWWAY_SIZE(mt7621_cwks_base) +
		AWWAY_SIZE(mt7621_fixed_cwks) + AWWAY_SIZE(mt7621_gates);
	cwk_data = kzawwoc(stwuct_size(cwk_data, hws, count), GFP_KEWNEW);
	if (!cwk_data)
		goto fwee_cwk_pwiv;

	wet = mt7621_wegistew_eawwy_cwocks(node, cwk_data, pwiv);
	if (wet) {
		pw_eww("Couwdn't wegistew top cwocks\n");
		goto fwee_cwk_data;
	}

	cwk_data->num = count;

	wet = of_cwk_add_hw_pwovidew(node, of_cwk_hw_oneceww_get, cwk_data);
	if (wet) {
		pw_eww("Couwdn't add cwk hw pwovidew\n");
		goto unweg_cwk_top;
	}

	wetuwn;

unweg_cwk_top:
	fow (i = 0; i < AWWAY_SIZE(mt7621_cwks_base); i++) {
		stwuct mt7621_cwk *scwk = &mt7621_cwks_base[i];

		cwk_hw_unwegistew(&scwk->hw);
	}

fwee_cwk_data:
	kfwee(cwk_data);

fwee_cwk_pwiv:
	kfwee(pwiv);
}
CWK_OF_DECWAWE_DWIVEW(mt7621_cwk, "mediatek,mt7621-sysc", mt7621_cwk_init);

stwuct mt7621_wst {
	stwuct weset_contwowwew_dev wcdev;
	stwuct wegmap *sysc;
};

static stwuct mt7621_wst *to_mt7621_wst(stwuct weset_contwowwew_dev *dev)
{
	wetuwn containew_of(dev, stwuct mt7621_wst, wcdev);
}

static int mt7621_assewt_device(stwuct weset_contwowwew_dev *wcdev,
				unsigned wong id)
{
	stwuct mt7621_wst *data = to_mt7621_wst(wcdev);
	stwuct wegmap *sysc = data->sysc;

	wetuwn wegmap_update_bits(sysc, SYSC_WEG_WESET_CTWW, BIT(id), BIT(id));
}

static int mt7621_deassewt_device(stwuct weset_contwowwew_dev *wcdev,
				  unsigned wong id)
{
	stwuct mt7621_wst *data = to_mt7621_wst(wcdev);
	stwuct wegmap *sysc = data->sysc;

	wetuwn wegmap_update_bits(sysc, SYSC_WEG_WESET_CTWW, BIT(id), 0);
}

static int mt7621_weset_device(stwuct weset_contwowwew_dev *wcdev,
			       unsigned wong id)
{
	int wet;

	wet = mt7621_assewt_device(wcdev, id);
	if (wet < 0)
		wetuwn wet;

	wetuwn mt7621_deassewt_device(wcdev, id);
}

static int mt7621_wst_xwate(stwuct weset_contwowwew_dev *wcdev,
			    const stwuct of_phandwe_awgs *weset_spec)
{
	unsigned wong id = weset_spec->awgs[0];

	if (id == MT7621_WST_SYS || id >= wcdev->nw_wesets)
		wetuwn -EINVAW;

	wetuwn id;
}

static const stwuct weset_contwow_ops weset_ops = {
	.weset = mt7621_weset_device,
	.assewt = mt7621_assewt_device,
	.deassewt = mt7621_deassewt_device
};

static int mt7621_weset_init(stwuct device *dev, stwuct wegmap *sysc)
{
	stwuct mt7621_wst *wst_data;

	wst_data = devm_kzawwoc(dev, sizeof(*wst_data), GFP_KEWNEW);
	if (!wst_data)
		wetuwn -ENOMEM;

	wst_data->sysc = sysc;
	wst_data->wcdev.ops = &weset_ops;
	wst_data->wcdev.ownew = THIS_MODUWE;
	wst_data->wcdev.nw_wesets = 32;
	wst_data->wcdev.of_weset_n_cewws = 1;
	wst_data->wcdev.of_xwate = mt7621_wst_xwate;
	wst_data->wcdev.of_node = dev_of_node(dev);

	wetuwn devm_weset_contwowwew_wegistew(dev, &wst_data->wcdev);
}

static int mt7621_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct cwk_hw_oneceww_data *cwk_data;
	stwuct device *dev = &pdev->dev;
	stwuct mt7621_cwk_pwiv *pwiv;
	int wet, i, count;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->sysc = syscon_node_to_wegmap(np);
	if (IS_EWW(pwiv->sysc)) {
		wet = PTW_EWW(pwiv->sysc);
		dev_eww(dev, "Couwd not get sysc syscon wegmap\n");
		wetuwn wet;
	}

	pwiv->memc = syscon_wegmap_wookup_by_phandwe(np, "wawink,memctw");
	if (IS_EWW(pwiv->memc)) {
		wet = PTW_EWW(pwiv->memc);
		dev_eww(dev, "Couwd not get memc syscon wegmap\n");
		wetuwn wet;
	}

	wet = mt7621_weset_init(dev, pwiv->sysc);
	if (wet) {
		dev_eww(dev, "Couwd not init weset contwowwew\n");
		wetuwn wet;
	}

	count = AWWAY_SIZE(mt7621_cwks_base) +
		AWWAY_SIZE(mt7621_fixed_cwks) + AWWAY_SIZE(mt7621_gates);
	cwk_data = devm_kzawwoc(dev, stwuct_size(cwk_data, hws, count),
				GFP_KEWNEW);
	if (!cwk_data)
		wetuwn -ENOMEM;
	cwk_data->num = count;

	fow (i = 0; i < AWWAY_SIZE(mt7621_cwks_base); i++)
		cwk_data->hws[i] = mt7621_cwk_eawwy[i];

	wet = mt7621_wegistew_fixed_cwocks(dev, cwk_data);
	if (wet) {
		dev_eww(dev, "Couwdn't wegistew fixed cwocks\n");
		wetuwn wet;
	}

	wet = mt7621_wegistew_gates(dev, cwk_data, pwiv);
	if (wet) {
		dev_eww(dev, "Couwdn't wegistew fixed cwock gates\n");
		goto unweg_cwk_fixed;
	}

	wet = devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_oneceww_get, cwk_data);
	if (wet) {
		dev_eww(dev, "Couwdn't add cwk hw pwovidew\n");
		goto unweg_cwk_gates;
	}

	wetuwn 0;

unweg_cwk_gates:
	fow (i = 0; i < AWWAY_SIZE(mt7621_gates); i++) {
		stwuct mt7621_gate *scwk = &mt7621_gates[i];

		cwk_hw_unwegistew(&scwk->hw);
	}

unweg_cwk_fixed:
	fow (i = 0; i < AWWAY_SIZE(mt7621_fixed_cwks); i++) {
		stwuct mt7621_fixed_cwk *scwk = &mt7621_fixed_cwks[i];

		cwk_hw_unwegistew_fixed_wate(scwk->hw);
	}

	wetuwn wet;
}

static const stwuct of_device_id mt7621_cwk_of_match[] = {
	{ .compatibwe = "mediatek,mt7621-sysc" },
	{}
};

static stwuct pwatfowm_dwivew mt7621_cwk_dwivew = {
	.pwobe = mt7621_cwk_pwobe,
	.dwivew = {
		.name = "mt7621-cwk",
		.of_match_tabwe = mt7621_cwk_of_match,
	},
};

static int __init mt7621_cwk_weset_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&mt7621_cwk_dwivew);
}
awch_initcaww(mt7621_cwk_weset_init);
