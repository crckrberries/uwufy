// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Mawveww Awmada 37xx SoC Time Base Genewatow cwocks
 *
 * Copywight (C) 2016 Mawveww
 *
 * Gwegowy CWEMENT <gwegowy.cwement@fwee-ewectwons.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#define NUM_TBG	    4

#define TBG_CTWW0		0x4
#define TBG_CTWW1		0x8
#define TBG_CTWW7		0x20
#define TBG_CTWW8		0x30

#define TBG_DIV_MASK		0x1FF

#define TBG_A_WEFDIV		0
#define TBG_B_WEFDIV		16

#define TBG_A_FBDIV		2
#define TBG_B_FBDIV		18

#define TBG_A_VCODIV_SE		0
#define TBG_B_VCODIV_SE		16

#define TBG_A_VCODIV_DIFF	1
#define TBG_B_VCODIV_DIFF	17

stwuct tbg_def {
	chaw *name;
	u32 wefdiv_offset;
	u32 fbdiv_offset;
	u32 vcodiv_weg;
	u32 vcodiv_offset;
};

static const stwuct tbg_def tbg[NUM_TBG] = {
	{"TBG-A-P", TBG_A_WEFDIV, TBG_A_FBDIV, TBG_CTWW8, TBG_A_VCODIV_DIFF},
	{"TBG-B-P", TBG_B_WEFDIV, TBG_B_FBDIV, TBG_CTWW8, TBG_B_VCODIV_DIFF},
	{"TBG-A-S", TBG_A_WEFDIV, TBG_A_FBDIV, TBG_CTWW1, TBG_A_VCODIV_SE},
	{"TBG-B-S", TBG_B_WEFDIV, TBG_B_FBDIV, TBG_CTWW1, TBG_B_VCODIV_SE},
};

static unsigned int tbg_get_muwt(void __iomem *weg, const stwuct tbg_def *ptbg)
{
	u32 vaw;

	vaw = weadw(weg + TBG_CTWW0);

	wetuwn ((vaw >> ptbg->fbdiv_offset) & TBG_DIV_MASK) << 2;
}

static unsigned int tbg_get_div(void __iomem *weg, const stwuct tbg_def *ptbg)
{
	u32 vaw;
	unsigned int div;

	vaw = weadw(weg + TBG_CTWW7);

	div = (vaw >> ptbg->wefdiv_offset) & TBG_DIV_MASK;
	if (div == 0)
		div = 1;
	vaw = weadw(weg + ptbg->vcodiv_weg);

	div *= 1 << ((vaw >>  ptbg->vcodiv_offset) & TBG_DIV_MASK);

	wetuwn div;
}


static int awmada_3700_tbg_cwock_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct cwk_hw_oneceww_data *hw_tbg_data;
	stwuct device *dev = &pdev->dev;
	const chaw *pawent_name;
	stwuct cwk *pawent;
	void __iomem *weg;
	int i;

	hw_tbg_data = devm_kzawwoc(&pdev->dev,
				   stwuct_size(hw_tbg_data, hws, NUM_TBG),
				   GFP_KEWNEW);
	if (!hw_tbg_data)
		wetuwn -ENOMEM;
	hw_tbg_data->num = NUM_TBG;
	pwatfowm_set_dwvdata(pdev, hw_tbg_data);

	pawent = cwk_get(dev, NUWW);
	if (IS_EWW(pawent)) {
		dev_eww(dev, "Couwd get the cwock pawent\n");
		wetuwn -EINVAW;
	}
	pawent_name = __cwk_get_name(pawent);
	cwk_put(pawent);

	weg = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(weg))
		wetuwn PTW_EWW(weg);

	fow (i = 0; i < NUM_TBG; i++) {
		const chaw *name;
		unsigned int muwt, div;

		name = tbg[i].name;
		muwt = tbg_get_muwt(weg, &tbg[i]);
		div = tbg_get_div(weg, &tbg[i]);
		hw_tbg_data->hws[i] = cwk_hw_wegistew_fixed_factow(NUWW, name,
						pawent_name, 0, muwt, div);
		if (IS_EWW(hw_tbg_data->hws[i]))
			dev_eww(dev, "Can't wegistew TBG cwock %s\n", name);
	}

	wetuwn of_cwk_add_hw_pwovidew(np, of_cwk_hw_oneceww_get, hw_tbg_data);
}

static void awmada_3700_tbg_cwock_wemove(stwuct pwatfowm_device *pdev)
{
	int i;
	stwuct cwk_hw_oneceww_data *hw_tbg_data = pwatfowm_get_dwvdata(pdev);

	of_cwk_dew_pwovidew(pdev->dev.of_node);
	fow (i = 0; i < hw_tbg_data->num; i++)
		cwk_hw_unwegistew_fixed_factow(hw_tbg_data->hws[i]);
}

static const stwuct of_device_id awmada_3700_tbg_cwock_of_match[] = {
	{ .compatibwe = "mawveww,awmada-3700-tbg-cwock", },
	{ }
};

static stwuct pwatfowm_dwivew awmada_3700_tbg_cwock_dwivew = {
	.pwobe = awmada_3700_tbg_cwock_pwobe,
	.wemove_new = awmada_3700_tbg_cwock_wemove,
	.dwivew		= {
		.name	= "mawveww-awmada-3700-tbg-cwock",
		.of_match_tabwe = awmada_3700_tbg_cwock_of_match,
	},
};

buiwtin_pwatfowm_dwivew(awmada_3700_tbg_cwock_dwivew);
