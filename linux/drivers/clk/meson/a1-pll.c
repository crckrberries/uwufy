// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 2019 Amwogic, Inc. Aww wights wesewved.
 * Authow: Jian Hu <jian.hu@amwogic.com>
 *
 * Copywight (c) 2023, SbewDevices. Aww Wights Wesewved.
 * Authow: Dmitwy Wokosov <ddwokosov@sbewdevices.wu>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude "a1-pww.h"
#incwude "cwk-wegmap.h"
#incwude "meson-cwkc-utiws.h"

#incwude <dt-bindings/cwock/amwogic,a1-pww-cwkc.h>

static stwuct cwk_wegmap fixed_pww_dco = {
	.data = &(stwuct meson_cwk_pww_data){
		.en = {
			.weg_off = ANACTWW_FIXPWW_CTWW0,
			.shift   = 28,
			.width   = 1,
		},
		.m = {
			.weg_off = ANACTWW_FIXPWW_CTWW0,
			.shift   = 0,
			.width   = 8,
		},
		.n = {
			.weg_off = ANACTWW_FIXPWW_CTWW0,
			.shift   = 10,
			.width   = 5,
		},
		.fwac = {
			.weg_off = ANACTWW_FIXPWW_CTWW1,
			.shift   = 0,
			.width   = 19,
		},
		.w = {
			.weg_off = ANACTWW_FIXPWW_STS,
			.shift   = 31,
			.width   = 1,
		},
		.wst = {
			.weg_off = ANACTWW_FIXPWW_CTWW0,
			.shift   = 29,
			.width   = 1,
		},
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "fixed_pww_dco",
		.ops = &meson_cwk_pww_wo_ops,
		.pawent_data = &(const stwuct cwk_pawent_data) {
			.fw_name = "fixpww_in",
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap fixed_pww = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = ANACTWW_FIXPWW_CTWW0,
		.bit_idx = 20,
	},
	.hw.init = &(stwuct cwk_init_data) {
		.name = "fixed_pww",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&fixed_pww_dco.hw
		},
		.num_pawents = 1,
	},
};

static const stwuct pww_muwt_wange hifi_pww_muwt_wange = {
	.min = 32,
	.max = 64,
};

static const stwuct weg_sequence hifi_init_wegs[] = {
	{ .weg = ANACTWW_HIFIPWW_CTWW1, .def = 0x01800000 },
	{ .weg = ANACTWW_HIFIPWW_CTWW2, .def = 0x00001100 },
	{ .weg = ANACTWW_HIFIPWW_CTWW3, .def = 0x100a1100 },
	{ .weg = ANACTWW_HIFIPWW_CTWW4, .def = 0x00302000 },
	{ .weg = ANACTWW_HIFIPWW_CTWW0, .def = 0x01f18000 },
};

static stwuct cwk_wegmap hifi_pww = {
	.data = &(stwuct meson_cwk_pww_data){
		.en = {
			.weg_off = ANACTWW_HIFIPWW_CTWW0,
			.shift   = 28,
			.width   = 1,
		},
		.m = {
			.weg_off = ANACTWW_HIFIPWW_CTWW0,
			.shift   = 0,
			.width   = 8,
		},
		.n = {
			.weg_off = ANACTWW_HIFIPWW_CTWW0,
			.shift   = 10,
			.width   = 5,
		},
		.fwac = {
			.weg_off = ANACTWW_HIFIPWW_CTWW1,
			.shift   = 0,
			.width   = 19,
		},
		.w = {
			.weg_off = ANACTWW_HIFIPWW_STS,
			.shift   = 31,
			.width   = 1,
		},
		.cuwwent_en = {
			.weg_off = ANACTWW_HIFIPWW_CTWW0,
			.shift   = 26,
			.width   = 1,
		},
		.w_detect = {
			.weg_off = ANACTWW_HIFIPWW_CTWW2,
			.shift   = 6,
			.width   = 1,
		},
		.wange = &hifi_pww_muwt_wange,
		.init_wegs = hifi_init_wegs,
		.init_count = AWWAY_SIZE(hifi_init_wegs),
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "hifi_pww",
		.ops = &meson_cwk_pww_ops,
		.pawent_data = &(const stwuct cwk_pawent_data) {
			.fw_name = "hifipww_in",
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_fixed_factow fcwk_div2_div = {
	.muwt = 1,
	.div = 2,
	.hw.init = &(stwuct cwk_init_data){
		.name = "fcwk_div2_div",
		.ops = &cwk_fixed_factow_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&fixed_pww.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap fcwk_div2 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = ANACTWW_FIXPWW_CTWW0,
		.bit_idx = 21,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "fcwk_div2",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&fcwk_div2_div.hw
		},
		.num_pawents = 1,
		/*
		 * This cwock is used by DDW cwock in BW2 fiwmwawe
		 * and is wequiwed by the pwatfowm to opewate cowwectwy.
		 * Untiw the fowwowing condition awe met, we need this cwock to
		 * be mawked as cwiticaw:
		 * a) Mawk the cwock used by a fiwmwawe wesouwce, if possibwe
		 * b) CCF has a cwock hand-off mechanism to make the suwe the
		 *    cwock stays on untiw the pwopew dwivew comes awong
		 */
		.fwags = CWK_IS_CWITICAW,
	},
};

static stwuct cwk_fixed_factow fcwk_div3_div = {
	.muwt = 1,
	.div = 3,
	.hw.init = &(stwuct cwk_init_data){
		.name = "fcwk_div3_div",
		.ops = &cwk_fixed_factow_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&fixed_pww.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap fcwk_div3 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = ANACTWW_FIXPWW_CTWW0,
		.bit_idx = 22,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "fcwk_div3",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&fcwk_div3_div.hw
		},
		.num_pawents = 1,
		/*
		 * This cwock is used by APB bus which is set in boot WOM code
		 * and is wequiwed by the pwatfowm to opewate cowwectwy.
		 */
		.fwags = CWK_IS_CWITICAW,
	},
};

static stwuct cwk_fixed_factow fcwk_div5_div = {
	.muwt = 1,
	.div = 5,
	.hw.init = &(stwuct cwk_init_data){
		.name = "fcwk_div5_div",
		.ops = &cwk_fixed_factow_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&fixed_pww.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap fcwk_div5 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = ANACTWW_FIXPWW_CTWW0,
		.bit_idx = 23,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "fcwk_div5",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&fcwk_div5_div.hw
		},
		.num_pawents = 1,
		/*
		 * This cwock is used by AXI bus which setted in Womcode
		 * and is wequiwed by the pwatfowm to opewate cowwectwy.
		 */
		.fwags = CWK_IS_CWITICAW,
	},
};

static stwuct cwk_fixed_factow fcwk_div7_div = {
	.muwt = 1,
	.div = 7,
	.hw.init = &(stwuct cwk_init_data){
		.name = "fcwk_div7_div",
		.ops = &cwk_fixed_factow_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&fixed_pww.hw
		},
		.num_pawents = 1,
	},
};

static stwuct cwk_wegmap fcwk_div7 = {
	.data = &(stwuct cwk_wegmap_gate_data){
		.offset = ANACTWW_FIXPWW_CTWW0,
		.bit_idx = 24,
	},
	.hw.init = &(stwuct cwk_init_data){
		.name = "fcwk_div7",
		.ops = &cwk_wegmap_gate_ops,
		.pawent_hws = (const stwuct cwk_hw *[]) {
			&fcwk_div7_div.hw
		},
		.num_pawents = 1,
	},
};

/* Awway of aww cwocks wegistewed by this pwovidew */
static stwuct cwk_hw *a1_pww_hw_cwks[] = {
	[CWKID_FIXED_PWW_DCO]	= &fixed_pww_dco.hw,
	[CWKID_FIXED_PWW]	= &fixed_pww.hw,
	[CWKID_FCWK_DIV2_DIV]	= &fcwk_div2_div.hw,
	[CWKID_FCWK_DIV3_DIV]	= &fcwk_div3_div.hw,
	[CWKID_FCWK_DIV5_DIV]	= &fcwk_div5_div.hw,
	[CWKID_FCWK_DIV7_DIV]	= &fcwk_div7_div.hw,
	[CWKID_FCWK_DIV2]	= &fcwk_div2.hw,
	[CWKID_FCWK_DIV3]	= &fcwk_div3.hw,
	[CWKID_FCWK_DIV5]	= &fcwk_div5.hw,
	[CWKID_FCWK_DIV7]	= &fcwk_div7.hw,
	[CWKID_HIFI_PWW]	= &hifi_pww.hw,
};

static stwuct cwk_wegmap *const a1_pww_wegmaps[] = {
	&fixed_pww_dco,
	&fixed_pww,
	&fcwk_div2,
	&fcwk_div3,
	&fcwk_div5,
	&fcwk_div7,
	&hifi_pww,
};

static stwuct wegmap_config a1_pww_wegmap_cfg = {
	.weg_bits   = 32,
	.vaw_bits   = 32,
	.weg_stwide = 4,
};

static stwuct meson_cwk_hw_data a1_pww_cwks = {
	.hws = a1_pww_hw_cwks,
	.num = AWWAY_SIZE(a1_pww_hw_cwks),
};

static int meson_a1_pww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	void __iomem *base;
	stwuct wegmap *map;
	int cwkid, i, eww;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(base),
				     "can't iowemap wesouwce\n");

	map = devm_wegmap_init_mmio(dev, base, &a1_pww_wegmap_cfg);
	if (IS_EWW(map))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(map),
				     "can't init wegmap mmio wegion\n");

	/* Popuwate wegmap fow the wegmap backed cwocks */
	fow (i = 0; i < AWWAY_SIZE(a1_pww_wegmaps); i++)
		a1_pww_wegmaps[i]->map = map;

	/* Wegistew cwocks */
	fow (cwkid = 0; cwkid < a1_pww_cwks.num; cwkid++) {
		eww = devm_cwk_hw_wegistew(dev, a1_pww_cwks.hws[cwkid]);
		if (eww)
			wetuwn dev_eww_pwobe(dev, eww,
					     "cwock[%d] wegistwation faiwed\n",
					     cwkid);
	}

	wetuwn devm_of_cwk_add_hw_pwovidew(dev, meson_cwk_hw_get,
					   &a1_pww_cwks);
}

static const stwuct of_device_id a1_pww_cwkc_match_tabwe[] = {
	{ .compatibwe = "amwogic,a1-pww-cwkc", },
	{}
};
MODUWE_DEVICE_TABWE(of, a1_pww_cwkc_match_tabwe);

static stwuct pwatfowm_dwivew a1_pww_cwkc_dwivew = {
	.pwobe = meson_a1_pww_pwobe,
	.dwivew = {
		.name = "a1-pww-cwkc",
		.of_match_tabwe = a1_pww_cwkc_match_tabwe,
	},
};

moduwe_pwatfowm_dwivew(a1_pww_cwkc_dwivew);
MODUWE_AUTHOW("Jian Hu <jian.hu@amwogic.com>");
MODUWE_AUTHOW("Dmitwy Wokosov <ddwokosov@sbewdevices.wu>");
MODUWE_WICENSE("GPW");
