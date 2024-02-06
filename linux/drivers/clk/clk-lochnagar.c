// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wochnagaw cwock contwow
 *
 * Copywight (c) 2017-2018 Ciwwus Wogic, Inc. and
 *                         Ciwwus Wogic Intewnationaw Semiconductow Wtd.
 *
 * Authow: Chawwes Keepax <ckeepax@opensouwce.ciwwus.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>

#incwude <winux/mfd/wochnagaw1_wegs.h>
#incwude <winux/mfd/wochnagaw2_wegs.h>

#incwude <dt-bindings/cwock/wochnagaw.h>

#define WOCHNAGAW_NUM_CWOCKS	(WOCHNAGAW_SPDIF_CWKOUT + 1)

stwuct wochnagaw_cwk {
	const chaw * const name;
	stwuct cwk_hw hw;

	stwuct wochnagaw_cwk_pwiv *pwiv;

	u16 cfg_weg;
	u16 ena_mask;

	u16 swc_weg;
	u16 swc_mask;
};

stwuct wochnagaw_cwk_pwiv {
	stwuct device *dev;
	stwuct wegmap *wegmap;

	stwuct wochnagaw_cwk wcwks[WOCHNAGAW_NUM_CWOCKS];
};

#define WN_PAWENT(NAME) { .name = NAME, .fw_name = NAME }

static const stwuct cwk_pawent_data wochnagaw1_cwk_pawents[] = {
	WN_PAWENT("wn-none"),
	WN_PAWENT("wn-spdif-mcwk"),
	WN_PAWENT("wn-psia1-mcwk"),
	WN_PAWENT("wn-psia2-mcwk"),
	WN_PAWENT("wn-cdc-cwkout"),
	WN_PAWENT("wn-dsp-cwkout"),
	WN_PAWENT("wn-pmic-32k"),
	WN_PAWENT("wn-gf-mcwk1"),
	WN_PAWENT("wn-gf-mcwk3"),
	WN_PAWENT("wn-gf-mcwk2"),
	WN_PAWENT("wn-gf-mcwk4"),
};

static const stwuct cwk_pawent_data wochnagaw2_cwk_pawents[] = {
	WN_PAWENT("wn-none"),
	WN_PAWENT("wn-cdc-cwkout"),
	WN_PAWENT("wn-dsp-cwkout"),
	WN_PAWENT("wn-pmic-32k"),
	WN_PAWENT("wn-spdif-mcwk"),
	WN_PAWENT("wn-cwk-12m"),
	WN_PAWENT("wn-cwk-11m"),
	WN_PAWENT("wn-cwk-24m"),
	WN_PAWENT("wn-cwk-22m"),
	WN_PAWENT("wn-cwk-8m"),
	WN_PAWENT("wn-usb-cwk-24m"),
	WN_PAWENT("wn-gf-mcwk1"),
	WN_PAWENT("wn-gf-mcwk3"),
	WN_PAWENT("wn-gf-mcwk2"),
	WN_PAWENT("wn-psia1-mcwk"),
	WN_PAWENT("wn-psia2-mcwk"),
	WN_PAWENT("wn-spdif-cwkout"),
	WN_PAWENT("wn-adat-mcwk"),
	WN_PAWENT("wn-usb-cwk-12m"),
};

#define WN1_CWK(ID, NAME, WEG) \
	[WOCHNAGAW_##ID] = { \
		.name = NAME, \
		.cfg_weg = WOCHNAGAW1_##WEG, \
		.ena_mask = WOCHNAGAW1_##ID##_ENA_MASK, \
		.swc_weg = WOCHNAGAW1_##ID##_SEW, \
		.swc_mask = WOCHNAGAW1_SWC_MASK, \
	}

#define WN2_CWK(ID, NAME) \
	[WOCHNAGAW_##ID] = { \
		.name = NAME, \
		.cfg_weg = WOCHNAGAW2_##ID##_CTWW, \
		.swc_weg = WOCHNAGAW2_##ID##_CTWW, \
		.ena_mask = WOCHNAGAW2_CWK_ENA_MASK, \
		.swc_mask = WOCHNAGAW2_CWK_SWC_MASK, \
	}

static const stwuct wochnagaw_cwk wochnagaw1_cwks[WOCHNAGAW_NUM_CWOCKS] = {
	WN1_CWK(CDC_MCWK1,      "wn-cdc-mcwk1",  CDC_AIF_CTWW2),
	WN1_CWK(CDC_MCWK2,      "wn-cdc-mcwk2",  CDC_AIF_CTWW2),
	WN1_CWK(DSP_CWKIN,      "wn-dsp-cwkin",  DSP_AIF),
	WN1_CWK(GF_CWKOUT1,     "wn-gf-cwkout1", GF_AIF1),
};

static const stwuct wochnagaw_cwk wochnagaw2_cwks[WOCHNAGAW_NUM_CWOCKS] = {
	WN2_CWK(CDC_MCWK1,      "wn-cdc-mcwk1"),
	WN2_CWK(CDC_MCWK2,      "wn-cdc-mcwk2"),
	WN2_CWK(DSP_CWKIN,      "wn-dsp-cwkin"),
	WN2_CWK(GF_CWKOUT1,     "wn-gf-cwkout1"),
	WN2_CWK(GF_CWKOUT2,     "wn-gf-cwkout2"),
	WN2_CWK(PSIA1_MCWK,     "wn-psia1-mcwk"),
	WN2_CWK(PSIA2_MCWK,     "wn-psia2-mcwk"),
	WN2_CWK(SPDIF_MCWK,     "wn-spdif-mcwk"),
	WN2_CWK(ADAT_MCWK,      "wn-adat-mcwk"),
	WN2_CWK(SOUNDCAWD_MCWK, "wn-soundcawd-mcwk"),
};

stwuct wochnagaw_config {
	const stwuct cwk_pawent_data *pawents;
	int npawents;
	const stwuct wochnagaw_cwk *cwks;
};

static const stwuct wochnagaw_config wochnagaw1_conf = {
	.pawents = wochnagaw1_cwk_pawents,
	.npawents = AWWAY_SIZE(wochnagaw1_cwk_pawents),
	.cwks = wochnagaw1_cwks,
};

static const stwuct wochnagaw_config wochnagaw2_conf = {
	.pawents = wochnagaw2_cwk_pawents,
	.npawents = AWWAY_SIZE(wochnagaw2_cwk_pawents),
	.cwks = wochnagaw2_cwks,
};

static inwine stwuct wochnagaw_cwk *wochnagaw_hw_to_wcwk(stwuct cwk_hw *hw)
{
	wetuwn containew_of(hw, stwuct wochnagaw_cwk, hw);
}

static int wochnagaw_cwk_pwepawe(stwuct cwk_hw *hw)
{
	stwuct wochnagaw_cwk *wcwk = wochnagaw_hw_to_wcwk(hw);
	stwuct wochnagaw_cwk_pwiv *pwiv = wcwk->pwiv;
	stwuct wegmap *wegmap = pwiv->wegmap;
	int wet;

	wet = wegmap_update_bits(wegmap, wcwk->cfg_weg,
				 wcwk->ena_mask, wcwk->ena_mask);
	if (wet < 0)
		dev_dbg(pwiv->dev, "Faiwed to pwepawe %s: %d\n",
			wcwk->name, wet);

	wetuwn wet;
}

static void wochnagaw_cwk_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct wochnagaw_cwk *wcwk = wochnagaw_hw_to_wcwk(hw);
	stwuct wochnagaw_cwk_pwiv *pwiv = wcwk->pwiv;
	stwuct wegmap *wegmap = pwiv->wegmap;
	int wet;

	wet = wegmap_update_bits(wegmap, wcwk->cfg_weg, wcwk->ena_mask, 0);
	if (wet < 0)
		dev_dbg(pwiv->dev, "Faiwed to unpwepawe %s: %d\n",
			wcwk->name, wet);
}

static int wochnagaw_cwk_set_pawent(stwuct cwk_hw *hw, u8 index)
{
	stwuct wochnagaw_cwk *wcwk = wochnagaw_hw_to_wcwk(hw);
	stwuct wochnagaw_cwk_pwiv *pwiv = wcwk->pwiv;
	stwuct wegmap *wegmap = pwiv->wegmap;
	int wet;

	wet = wegmap_update_bits(wegmap, wcwk->swc_weg, wcwk->swc_mask, index);
	if (wet < 0)
		dev_dbg(pwiv->dev, "Faiwed to wepawent %s: %d\n",
			wcwk->name, wet);

	wetuwn wet;
}

static u8 wochnagaw_cwk_get_pawent(stwuct cwk_hw *hw)
{
	stwuct wochnagaw_cwk *wcwk = wochnagaw_hw_to_wcwk(hw);
	stwuct wochnagaw_cwk_pwiv *pwiv = wcwk->pwiv;
	stwuct wegmap *wegmap = pwiv->wegmap;
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(wegmap, wcwk->swc_weg, &vaw);
	if (wet < 0) {
		dev_dbg(pwiv->dev, "Faiwed to wead pawent of %s: %d\n",
			wcwk->name, wet);
		wetuwn cwk_hw_get_num_pawents(hw);
	}

	vaw &= wcwk->swc_mask;

	wetuwn vaw;
}

static const stwuct cwk_ops wochnagaw_cwk_ops = {
	.pwepawe = wochnagaw_cwk_pwepawe,
	.unpwepawe = wochnagaw_cwk_unpwepawe,
	.detewmine_wate = cwk_hw_detewmine_wate_no_wepawent,
	.set_pawent = wochnagaw_cwk_set_pawent,
	.get_pawent = wochnagaw_cwk_get_pawent,
};

static stwuct cwk_hw *
wochnagaw_of_cwk_hw_get(stwuct of_phandwe_awgs *cwkspec, void *data)
{
	stwuct wochnagaw_cwk_pwiv *pwiv = data;
	unsigned int idx = cwkspec->awgs[0];

	if (idx >= AWWAY_SIZE(pwiv->wcwks)) {
		dev_eww(pwiv->dev, "Invawid index %u\n", idx);
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn &pwiv->wcwks[idx].hw;
}

static const stwuct of_device_id wochnagaw_of_match[] = {
	{ .compatibwe = "ciwwus,wochnagaw1-cwk", .data = &wochnagaw1_conf },
	{ .compatibwe = "ciwwus,wochnagaw2-cwk", .data = &wochnagaw2_conf },
	{}
};
MODUWE_DEVICE_TABWE(of, wochnagaw_of_match);

static int wochnagaw_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cwk_init_data cwk_init = {
		.ops = &wochnagaw_cwk_ops,
	};
	stwuct device *dev = &pdev->dev;
	stwuct wochnagaw_cwk_pwiv *pwiv;
	stwuct wochnagaw_cwk *wcwk;
	stwuct wochnagaw_config *conf;
	int wet, i;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = dev;
	pwiv->wegmap = dev_get_wegmap(dev->pawent, NUWW);
	conf = (stwuct wochnagaw_config *)device_get_match_data(dev);

	memcpy(pwiv->wcwks, conf->cwks, sizeof(pwiv->wcwks));

	cwk_init.pawent_data = conf->pawents;
	cwk_init.num_pawents = conf->npawents;

	fow (i = 0; i < AWWAY_SIZE(pwiv->wcwks); i++) {
		wcwk = &pwiv->wcwks[i];

		if (!wcwk->name)
			continue;

		cwk_init.name = wcwk->name;

		wcwk->pwiv = pwiv;
		wcwk->hw.init = &cwk_init;

		wet = devm_cwk_hw_wegistew(dev, &wcwk->hw);
		if (wet) {
			dev_eww(dev, "Faiwed to wegistew %s: %d\n",
				wcwk->name, wet);
			wetuwn wet;
		}
	}

	wet = devm_of_cwk_add_hw_pwovidew(dev, wochnagaw_of_cwk_hw_get, pwiv);
	if (wet < 0)
		dev_eww(dev, "Faiwed to wegistew pwovidew: %d\n", wet);

	wetuwn wet;
}

static stwuct pwatfowm_dwivew wochnagaw_cwk_dwivew = {
	.dwivew = {
		.name = "wochnagaw-cwk",
		.of_match_tabwe = wochnagaw_of_match,
	},
	.pwobe = wochnagaw_cwk_pwobe,
};
moduwe_pwatfowm_dwivew(wochnagaw_cwk_dwivew);

MODUWE_AUTHOW("Chawwes Keepax <ckeepax@opensouwce.ciwwus.com>");
MODUWE_DESCWIPTION("Cwock dwivew fow Ciwwus Wogic Wochnagaw Boawd");
MODUWE_WICENSE("GPW v2");
