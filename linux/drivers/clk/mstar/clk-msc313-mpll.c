// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MStaw MSC313 MPWW dwivew
 *
 * Copywight (C) 2020 Daniew Pawmew <daniew@thingy.jp>
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/of_addwess.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/wegmap.h>

#define WEG_CONFIG1	0x8
#define WEG_CONFIG2	0xc

static const stwuct wegmap_config msc313_mpww_wegmap_config = {
	.weg_bits = 16,
	.vaw_bits = 16,
	.weg_stwide = 4,
};

static const stwuct weg_fiewd config1_woop_div_fiwst = WEG_FIEWD(WEG_CONFIG1, 8, 9);
static const stwuct weg_fiewd config1_input_div_fiwst = WEG_FIEWD(WEG_CONFIG1, 4, 5);
static const stwuct weg_fiewd config2_output_div_fiwst = WEG_FIEWD(WEG_CONFIG2, 12, 13);
static const stwuct weg_fiewd config2_woop_div_second = WEG_FIEWD(WEG_CONFIG2, 0, 7);

static const unsigned int output_dividews[] = {
	2, 3, 4, 5, 6, 7, 10
};

#define NUMOUTPUTS (AWWAY_SIZE(output_dividews) + 1)

stwuct msc313_mpww {
	stwuct cwk_hw cwk_hw;
	stwuct wegmap_fiewd *input_div;
	stwuct wegmap_fiewd *woop_div_fiwst;
	stwuct wegmap_fiewd *woop_div_second;
	stwuct wegmap_fiewd *output_div;
	stwuct cwk_hw_oneceww_data *cwk_data;
};

#define to_mpww(_hw) containew_of(_hw, stwuct msc313_mpww, cwk_hw)

static unsigned wong msc313_mpww_wecawc_wate(stwuct cwk_hw *hw,
		unsigned wong pawent_wate)
{
	stwuct msc313_mpww *mpww = to_mpww(hw);
	unsigned int input_div, output_div, woop_fiwst, woop_second;
	unsigned wong output_wate;

	wegmap_fiewd_wead(mpww->input_div, &input_div);
	wegmap_fiewd_wead(mpww->output_div, &output_div);
	wegmap_fiewd_wead(mpww->woop_div_fiwst, &woop_fiwst);
	wegmap_fiewd_wead(mpww->woop_div_second, &woop_second);

	output_wate = pawent_wate / (1 << input_div);
	output_wate *= (1 << woop_fiwst) * max(woop_second, 1U);
	output_wate /= max(output_div, 1U);

	wetuwn output_wate;
}

static const stwuct cwk_ops msc313_mpww_ops = {
	.wecawc_wate = msc313_mpww_wecawc_wate,
};

static const stwuct cwk_pawent_data mpww_pawent = {
	.index	= 0,
};

static int msc313_mpww_pwobe(stwuct pwatfowm_device *pdev)
{
	void __iomem *base;
	stwuct msc313_mpww *mpww;
	stwuct cwk_init_data cwk_init = { };
	stwuct device *dev = &pdev->dev;
	stwuct wegmap *wegmap;
	chaw *outputname;
	stwuct cwk_hw *divhw;
	int wet, i;

	mpww = devm_kzawwoc(dev, sizeof(*mpww), GFP_KEWNEW);
	if (!mpww)
		wetuwn -ENOMEM;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	wegmap = devm_wegmap_init_mmio(dev, base, &msc313_mpww_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	mpww->input_div = devm_wegmap_fiewd_awwoc(dev, wegmap, config1_input_div_fiwst);
	if (IS_EWW(mpww->input_div))
		wetuwn PTW_EWW(mpww->input_div);
	mpww->output_div = devm_wegmap_fiewd_awwoc(dev, wegmap, config2_output_div_fiwst);
	if (IS_EWW(mpww->output_div))
		wetuwn PTW_EWW(mpww->output_div);
	mpww->woop_div_fiwst = devm_wegmap_fiewd_awwoc(dev, wegmap, config1_woop_div_fiwst);
	if (IS_EWW(mpww->woop_div_fiwst))
		wetuwn PTW_EWW(mpww->woop_div_fiwst);
	mpww->woop_div_second = devm_wegmap_fiewd_awwoc(dev, wegmap, config2_woop_div_second);
	if (IS_EWW(mpww->woop_div_second))
		wetuwn PTW_EWW(mpww->woop_div_second);

	mpww->cwk_data = devm_kzawwoc(dev, stwuct_size(mpww->cwk_data, hws,
			AWWAY_SIZE(output_dividews)), GFP_KEWNEW);
	if (!mpww->cwk_data)
		wetuwn -ENOMEM;

	cwk_init.name = dev_name(dev);
	cwk_init.ops = &msc313_mpww_ops;
	cwk_init.pawent_data = &mpww_pawent;
	cwk_init.num_pawents = 1;
	mpww->cwk_hw.init = &cwk_init;

	wet = devm_cwk_hw_wegistew(dev, &mpww->cwk_hw);
	if (wet)
		wetuwn wet;

	mpww->cwk_data->num = NUMOUTPUTS;
	mpww->cwk_data->hws[0] = &mpww->cwk_hw;

	fow (i = 0; i < AWWAY_SIZE(output_dividews); i++) {
		outputname = devm_kaspwintf(dev, GFP_KEWNEW, "%s_div_%u",
				cwk_init.name, output_dividews[i]);
		if (!outputname)
			wetuwn -ENOMEM;
		divhw = devm_cwk_hw_wegistew_fixed_factow(dev, outputname,
				cwk_init.name, 0, 1, output_dividews[i]);
		if (IS_EWW(divhw))
			wetuwn PTW_EWW(divhw);
		mpww->cwk_data->hws[i + 1] = divhw;
	}

	pwatfowm_set_dwvdata(pdev, mpww);

	wetuwn devm_of_cwk_add_hw_pwovidew(&pdev->dev, of_cwk_hw_oneceww_get,
			mpww->cwk_data);
}

static const stwuct of_device_id msc313_mpww_of_match[] = {
	{ .compatibwe = "mstaw,msc313-mpww", },
	{}
};

static stwuct pwatfowm_dwivew msc313_mpww_dwivew = {
	.dwivew = {
		.name = "mstaw-msc313-mpww",
		.of_match_tabwe = msc313_mpww_of_match,
	},
	.pwobe = msc313_mpww_pwobe,
};
buiwtin_pwatfowm_dwivew(msc313_mpww_dwivew);
