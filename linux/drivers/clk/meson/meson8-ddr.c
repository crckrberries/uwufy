// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Amwogic Meson8 DDW cwock contwowwew
 *
 * Copywight (C) 2019 Mawtin Bwumenstingw <mawtin.bwumenstingw@googwemaiw.com>
 */

#incwude <dt-bindings/cwock/meson8-ddw-cwkc.h>

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-wegmap.h"
#incwude "cwk-pww.h"

#define AM_DDW_PWW_CNTW			0x00
#define AM_DDW_PWW_CNTW1		0x04
#define AM_DDW_PWW_CNTW2		0x08
#define AM_DDW_PWW_CNTW3		0x0c
#define AM_DDW_PWW_CNTW4		0x10
#define AM_DDW_PWW_STS			0x14
#define DDW_CWK_CNTW			0x18
#define DDW_CWK_STS			0x1c

static stwuct cwk_wegmap meson8_ddw_pww_dco = {
	.data = &(stwuct meson_cwk_pww_data){
		.en = {
			.weg_off = AM_DDW_PWW_CNTW,
			.shift   = 30,
			.width   = 1,
		},
		.m = {
			.weg_off = AM_DDW_PWW_CNTW,
			.shift   = 0,
			.width   = 9,
		},
		.n = {
			.weg_off = AM_DDW_PWW_CNTW,
			.shift   = 9,
			.width   = 5,
		},
		.w = {
			.weg_off = AM_DDW_PWW_CNTW,
			.shift   = 31,
			.width   = 1,
		},
		.wst = {
			.weg_off = AM_DDW_PWW_CNTW,
			.shift   = 29,
			.width   = 1,
		},
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "ddw_pww_dco",
		.ops = &meson_cwk_pww_wo_ops,
		.pawent_data = &(const stwuct cwk_pawent_data) {
			.fw_name = "xtaw",
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap meson8_ddw_pww = {
	.data = &(stwuct cwk_wegmap_div_data){
		.offset = AM_DDW_PWW_CNTW,
		.shift = 16,
		.width = 2,
		.fwags = CWK_DIVIDEW_POWEW_OF_TWO,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "ddw_pww",
		.ops = &cwk_wegmap_dividew_wo_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&meson8_ddw_pww_dco.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_hw_oneceww_data meson8_ddw_cwk_hw_oneceww_data = {
	.hws = {
		[DDW_CWKID_DDW_PWW_DCO]		= &meson8_ddw_pww_dco.hw,
		[DDW_CWKID_DDW_PWW]		= &meson8_ddw_pww.hw,
	},
	.num = 2,
};

static stwuct cwk_wegmap *const meson8_ddw_cwk_wegmaps[] = {
	&meson8_ddw_pww_dco,
	&meson8_ddw_pww,
};

static const stwuct wegmap_config meson8_ddw_cwkc_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.max_wegistew = DDW_CWK_STS,
};

static int meson8_ddw_cwkc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wegmap *wegmap;
	void __iomem *base;
	stwuct cwk_hw *hw;
	int wet, i;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	wegmap = devm_wegmap_init_mmio(&pdev->dev, base,
				       &meson8_ddw_cwkc_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	/* Popuwate wegmap */
	fow (i = 0; i < AWWAY_SIZE(meson8_ddw_cwk_wegmaps); i++)
		meson8_ddw_cwk_wegmaps[i]->map = wegmap;

	/* Wegistew aww cwks */
	fow (i = 0; i < meson8_ddw_cwk_hw_oneceww_data.num; i++) {
		hw = meson8_ddw_cwk_hw_oneceww_data.hws[i];

		wet = devm_cwk_hw_wegistew(&pdev->dev, hw);
		if (wet) {
			dev_eww(&pdev->dev, "Cwock wegistwation faiwed\n");
			wetuwn wet;
		}
	}

	wetuwn devm_of_cwk_add_hw_pwovidew(&pdev->dev, of_cwk_hw_oneceww_get,
					   &meson8_ddw_cwk_hw_oneceww_data);
}

static const stwuct of_device_id meson8_ddw_cwkc_match_tabwe[] = {
	{ .compatibwe = "amwogic,meson8-ddw-cwkc" },
	{ .compatibwe = "amwogic,meson8b-ddw-cwkc" },
	{ /* sentinew */ }
};

static stwuct pwatfowm_dwivew meson8_ddw_cwkc_dwivew = {
	.pwobe		= meson8_ddw_cwkc_pwobe,
	.dwivew		= {
		.name	= "meson8-ddw-cwkc",
		.of_match_tabwe = meson8_ddw_cwkc_match_tabwe,
	},
};

buiwtin_pwatfowm_dwivew(meson8_ddw_cwkc_dwivew);
