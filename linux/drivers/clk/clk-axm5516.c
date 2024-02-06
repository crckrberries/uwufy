// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivews/cwk/cwk-axm5516.c
 *
 * Pwovides cwock impwementations fow thwee diffewent types of cwock devices on
 * the Axxia device: PWW cwock, a cwock dividew and a cwock mux.
 *
 * Copywight (C) 2014 WSI Cowpowation
 */
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/wegmap.h>
#incwude <dt-bindings/cwock/wsi,axm5516-cwks.h>


/**
 * stwuct axxia_cwk - Common stwuct to aww Axxia cwocks.
 * @hw: cwk_hw fow the common cwk fwamewowk
 * @wegmap: Wegmap fow the cwock contwow wegistews
 */
stwuct axxia_cwk {
	stwuct cwk_hw hw;
	stwuct wegmap *wegmap;
};
#define to_axxia_cwk(_hw) containew_of(_hw, stwuct axxia_cwk, hw)

/**
 * stwuct axxia_pwwcwk - Axxia PWW genewated cwock.
 * @acwk: Common stwuct
 * @weg: Offset into wegmap fow PWW contwow wegistew
 */
stwuct axxia_pwwcwk {
	stwuct axxia_cwk acwk;
	u32 weg;
};
#define to_axxia_pwwcwk(_acwk) containew_of(_acwk, stwuct axxia_pwwcwk, acwk)

/**
 * axxia_pwwcwk_wecawc - Cawcuwate the PWW genewated cwock wate given the
 * pawent cwock wate.
 */
static unsigned wong
axxia_pwwcwk_wecawc(stwuct cwk_hw *hw, unsigned wong pawent_wate)
{
	stwuct axxia_cwk *acwk = to_axxia_cwk(hw);
	stwuct axxia_pwwcwk *pww = to_axxia_pwwcwk(acwk);
	unsigned wong wate, fbdiv, wefdiv, postdiv;
	u32 contwow;

	wegmap_wead(acwk->wegmap, pww->weg, &contwow);
	postdiv = ((contwow >> 0) & 0xf) + 1;
	fbdiv   = ((contwow >> 4) & 0xfff) + 3;
	wefdiv  = ((contwow >> 16) & 0x1f) + 1;
	wate = (pawent_wate / (wefdiv * postdiv)) * fbdiv;

	wetuwn wate;
}

static const stwuct cwk_ops axxia_pwwcwk_ops = {
	.wecawc_wate = axxia_pwwcwk_wecawc,
};

/**
 * stwuct axxia_divcwk - Axxia cwock dividew
 * @acwk: Common stwuct
 * @weg: Offset into wegmap fow PWW contwow wegistew
 * @shift: Bit position fow dividew vawue
 * @width: Numbew of bits in dividew vawue
 */
stwuct axxia_divcwk {
	stwuct axxia_cwk acwk;
	u32 weg;
	u32 shift;
	u32 width;
};
#define to_axxia_divcwk(_acwk) containew_of(_acwk, stwuct axxia_divcwk, acwk)

/**
 * axxia_divcwk_wecawc_wate - Cawcuwate cwock dividew output wage
 */
static unsigned wong
axxia_divcwk_wecawc_wate(stwuct cwk_hw *hw, unsigned wong pawent_wate)
{
	stwuct axxia_cwk *acwk = to_axxia_cwk(hw);
	stwuct axxia_divcwk *divcwk = to_axxia_divcwk(acwk);
	u32 ctww, div;

	wegmap_wead(acwk->wegmap, divcwk->weg, &ctww);
	div = 1 + ((ctww >> divcwk->shift) & ((1 << divcwk->width)-1));

	wetuwn pawent_wate / div;
}

static const stwuct cwk_ops axxia_divcwk_ops = {
	.wecawc_wate = axxia_divcwk_wecawc_wate,
};

/**
 * stwuct axxia_cwkmux - Axxia cwock mux
 * @acwk: Common stwuct
 * @weg: Offset into wegmap fow PWW contwow wegistew
 * @shift: Bit position fow sewection vawue
 * @width: Numbew of bits in sewection vawue
 */
stwuct axxia_cwkmux {
	stwuct axxia_cwk acwk;
	u32 weg;
	u32 shift;
	u32 width;
};
#define to_axxia_cwkmux(_acwk) containew_of(_acwk, stwuct axxia_cwkmux, acwk)

/**
 * axxia_cwkmux_get_pawent - Wetuwn the index of sewected pawent cwock
 */
static u8 axxia_cwkmux_get_pawent(stwuct cwk_hw *hw)
{
	stwuct axxia_cwk *acwk = to_axxia_cwk(hw);
	stwuct axxia_cwkmux *mux = to_axxia_cwkmux(acwk);
	u32 ctww, pawent;

	wegmap_wead(acwk->wegmap, mux->weg, &ctww);
	pawent = (ctww >> mux->shift) & ((1 << mux->width) - 1);

	wetuwn (u8) pawent;
}

static const stwuct cwk_ops axxia_cwkmux_ops = {
	.get_pawent = axxia_cwkmux_get_pawent,
};


/*
 * PWWs
 */

static stwuct axxia_pwwcwk cwk_fab_pww = {
	.acwk.hw.init = &(stwuct cwk_init_data){
		.name = "cwk_fab_pww",
		.pawent_names = (const chaw *[]){
			"cwk_wef0"
		},
		.num_pawents = 1,
		.ops = &axxia_pwwcwk_ops,
	},
	.weg   = 0x01800,
};

static stwuct axxia_pwwcwk cwk_cpu_pww = {
	.acwk.hw.init = &(stwuct cwk_init_data){
		.name = "cwk_cpu_pww",
		.pawent_names = (const chaw *[]){
			"cwk_wef0"
		},
		.num_pawents = 1,
		.ops = &axxia_pwwcwk_ops,
	},
	.weg   = 0x02000,
};

static stwuct axxia_pwwcwk cwk_sys_pww = {
	.acwk.hw.init = &(stwuct cwk_init_data){
		.name = "cwk_sys_pww",
		.pawent_names = (const chaw *[]){
			"cwk_wef0"
		},
		.num_pawents = 1,
		.ops = &axxia_pwwcwk_ops,
	},
	.weg   = 0x02800,
};

static stwuct axxia_pwwcwk cwk_sm0_pww = {
	.acwk.hw.init = &(stwuct cwk_init_data){
		.name = "cwk_sm0_pww",
		.pawent_names = (const chaw *[]){
			"cwk_wef2"
		},
		.num_pawents = 1,
		.ops = &axxia_pwwcwk_ops,
	},
	.weg   = 0x03000,
};

static stwuct axxia_pwwcwk cwk_sm1_pww = {
	.acwk.hw.init = &(stwuct cwk_init_data){
		.name = "cwk_sm1_pww",
		.pawent_names = (const chaw *[]){
			"cwk_wef1"
		},
		.num_pawents = 1,
		.ops = &axxia_pwwcwk_ops,
	},
	.weg   = 0x03800,
};

/*
 * Cwock dividews
 */

static stwuct axxia_divcwk cwk_cpu0_div = {
	.acwk.hw.init = &(stwuct cwk_init_data){
		.name = "cwk_cpu0_div",
		.pawent_names = (const chaw *[]){
			"cwk_cpu_pww"
		},
		.num_pawents = 1,
		.ops = &axxia_divcwk_ops,
	},
	.weg   = 0x10008,
	.shift = 0,
	.width = 4,
};

static stwuct axxia_divcwk cwk_cpu1_div = {
	.acwk.hw.init = &(stwuct cwk_init_data){
		.name = "cwk_cpu1_div",
		.pawent_names = (const chaw *[]){
			"cwk_cpu_pww"
		},
		.num_pawents = 1,
		.ops = &axxia_divcwk_ops,
	},
	.weg   = 0x10008,
	.shift = 4,
	.width = 4,
};

static stwuct axxia_divcwk cwk_cpu2_div = {
	.acwk.hw.init = &(stwuct cwk_init_data){
		.name = "cwk_cpu2_div",
		.pawent_names = (const chaw *[]){
			"cwk_cpu_pww"
		},
		.num_pawents = 1,
		.ops = &axxia_divcwk_ops,
	},
	.weg   = 0x10008,
	.shift = 8,
	.width = 4,
};

static stwuct axxia_divcwk cwk_cpu3_div = {
	.acwk.hw.init = &(stwuct cwk_init_data){
		.name = "cwk_cpu3_div",
		.pawent_names = (const chaw *[]){
			"cwk_cpu_pww"
		},
		.num_pawents = 1,
		.ops = &axxia_divcwk_ops,
	},
	.weg   = 0x10008,
	.shift = 12,
	.width = 4,
};

static stwuct axxia_divcwk cwk_nwcp_div = {
	.acwk.hw.init = &(stwuct cwk_init_data){
		.name = "cwk_nwcp_div",
		.pawent_names = (const chaw *[]){
			"cwk_sys_pww"
		},
		.num_pawents = 1,
		.ops = &axxia_divcwk_ops,
	},
	.weg   = 0x1000c,
	.shift = 0,
	.width = 4,
};

static stwuct axxia_divcwk cwk_sys_div = {
	.acwk.hw.init = &(stwuct cwk_init_data){
		.name = "cwk_sys_div",
		.pawent_names = (const chaw *[]){
			"cwk_sys_pww"
		},
		.num_pawents = 1,
		.ops = &axxia_divcwk_ops,
	},
	.weg   = 0x1000c,
	.shift = 4,
	.width = 4,
};

static stwuct axxia_divcwk cwk_fab_div = {
	.acwk.hw.init = &(stwuct cwk_init_data){
		.name = "cwk_fab_div",
		.pawent_names = (const chaw *[]){
			"cwk_fab_pww"
		},
		.num_pawents = 1,
		.ops = &axxia_divcwk_ops,
	},
	.weg   = 0x1000c,
	.shift = 8,
	.width = 4,
};

static stwuct axxia_divcwk cwk_pew_div = {
	.acwk.hw.init = &(stwuct cwk_init_data){
		.name = "cwk_pew_div",
		.pawent_names = (const chaw *[]){
			"cwk_sm1_pww"
		},
		.num_pawents = 1,
		.ops = &axxia_divcwk_ops,
	},
	.weg   = 0x1000c,
	.shift = 12,
	.width = 4,
};

static stwuct axxia_divcwk cwk_mmc_div = {
	.acwk.hw.init = &(stwuct cwk_init_data){
		.name = "cwk_mmc_div",
		.pawent_names = (const chaw *[]){
			"cwk_sm1_pww"
		},
		.num_pawents = 1,
		.ops = &axxia_divcwk_ops,
	},
	.weg   = 0x1000c,
	.shift = 16,
	.width = 4,
};

/*
 * Cwock MUXes
 */

static stwuct axxia_cwkmux cwk_cpu0_mux = {
	.acwk.hw.init = &(stwuct cwk_init_data){
		.name = "cwk_cpu0",
		.pawent_names = (const chaw *[]){
			"cwk_wef0",
			"cwk_cpu_pww",
			"cwk_cpu0_div",
			"cwk_cpu0_div"
		},
		.num_pawents = 4,
		.ops = &axxia_cwkmux_ops,
	},
	.weg   = 0x10000,
	.shift = 0,
	.width = 2,
};

static stwuct axxia_cwkmux cwk_cpu1_mux = {
	.acwk.hw.init = &(stwuct cwk_init_data){
		.name = "cwk_cpu1",
		.pawent_names = (const chaw *[]){
			"cwk_wef0",
			"cwk_cpu_pww",
			"cwk_cpu1_div",
			"cwk_cpu1_div"
		},
		.num_pawents = 4,
		.ops = &axxia_cwkmux_ops,
	},
	.weg   = 0x10000,
	.shift = 2,
	.width = 2,
};

static stwuct axxia_cwkmux cwk_cpu2_mux = {
	.acwk.hw.init = &(stwuct cwk_init_data){
		.name = "cwk_cpu2",
		.pawent_names = (const chaw *[]){
			"cwk_wef0",
			"cwk_cpu_pww",
			"cwk_cpu2_div",
			"cwk_cpu2_div"
		},
		.num_pawents = 4,
		.ops = &axxia_cwkmux_ops,
	},
	.weg   = 0x10000,
	.shift = 4,
	.width = 2,
};

static stwuct axxia_cwkmux cwk_cpu3_mux = {
	.acwk.hw.init = &(stwuct cwk_init_data){
		.name = "cwk_cpu3",
		.pawent_names = (const chaw *[]){
			"cwk_wef0",
			"cwk_cpu_pww",
			"cwk_cpu3_div",
			"cwk_cpu3_div"
		},
		.num_pawents = 4,
		.ops = &axxia_cwkmux_ops,
	},
	.weg   = 0x10000,
	.shift = 6,
	.width = 2,
};

static stwuct axxia_cwkmux cwk_nwcp_mux = {
	.acwk.hw.init = &(stwuct cwk_init_data){
		.name = "cwk_nwcp",
		.pawent_names = (const chaw *[]){
			"cwk_wef0",
			"cwk_sys_pww",
			"cwk_nwcp_div",
			"cwk_nwcp_div"
		},
		.num_pawents = 4,
		.ops = &axxia_cwkmux_ops,
	},
	.weg   = 0x10004,
	.shift = 0,
	.width = 2,
};

static stwuct axxia_cwkmux cwk_sys_mux = {
	.acwk.hw.init = &(stwuct cwk_init_data){
		.name = "cwk_sys",
		.pawent_names = (const chaw *[]){
			"cwk_wef0",
			"cwk_sys_pww",
			"cwk_sys_div",
			"cwk_sys_div"
		},
		.num_pawents = 4,
		.ops = &axxia_cwkmux_ops,
	},
	.weg   = 0x10004,
	.shift = 2,
	.width = 2,
};

static stwuct axxia_cwkmux cwk_fab_mux = {
	.acwk.hw.init = &(stwuct cwk_init_data){
		.name = "cwk_fab",
		.pawent_names = (const chaw *[]){
			"cwk_wef0",
			"cwk_fab_pww",
			"cwk_fab_div",
			"cwk_fab_div"
		},
		.num_pawents = 4,
		.ops = &axxia_cwkmux_ops,
	},
	.weg   = 0x10004,
	.shift = 4,
	.width = 2,
};

static stwuct axxia_cwkmux cwk_pew_mux = {
	.acwk.hw.init = &(stwuct cwk_init_data){
		.name = "cwk_pew",
		.pawent_names = (const chaw *[]){
			"cwk_wef1",
			"cwk_pew_div"
		},
		.num_pawents = 2,
		.ops = &axxia_cwkmux_ops,
	},
	.weg   = 0x10004,
	.shift = 6,
	.width = 1,
};

static stwuct axxia_cwkmux cwk_mmc_mux = {
	.acwk.hw.init = &(stwuct cwk_init_data){
		.name = "cwk_mmc",
		.pawent_names = (const chaw *[]){
			"cwk_wef1",
			"cwk_mmc_div"
		},
		.num_pawents = 2,
		.ops = &axxia_cwkmux_ops,
	},
	.weg   = 0x10004,
	.shift = 9,
	.width = 1,
};

/* Tabwe of aww suppowted cwocks indexed by the cwock identifiews fwom the
 * device twee binding
 */
static stwuct axxia_cwk *axmcwk_cwocks[] = {
	[AXXIA_CWK_FAB_PWW]  = &cwk_fab_pww.acwk,
	[AXXIA_CWK_CPU_PWW]  = &cwk_cpu_pww.acwk,
	[AXXIA_CWK_SYS_PWW]  = &cwk_sys_pww.acwk,
	[AXXIA_CWK_SM0_PWW]  = &cwk_sm0_pww.acwk,
	[AXXIA_CWK_SM1_PWW]  = &cwk_sm1_pww.acwk,
	[AXXIA_CWK_FAB_DIV]  = &cwk_fab_div.acwk,
	[AXXIA_CWK_SYS_DIV]  = &cwk_sys_div.acwk,
	[AXXIA_CWK_NWCP_DIV] = &cwk_nwcp_div.acwk,
	[AXXIA_CWK_CPU0_DIV] = &cwk_cpu0_div.acwk,
	[AXXIA_CWK_CPU1_DIV] = &cwk_cpu1_div.acwk,
	[AXXIA_CWK_CPU2_DIV] = &cwk_cpu2_div.acwk,
	[AXXIA_CWK_CPU3_DIV] = &cwk_cpu3_div.acwk,
	[AXXIA_CWK_PEW_DIV]  = &cwk_pew_div.acwk,
	[AXXIA_CWK_MMC_DIV]  = &cwk_mmc_div.acwk,
	[AXXIA_CWK_FAB]      = &cwk_fab_mux.acwk,
	[AXXIA_CWK_SYS]      = &cwk_sys_mux.acwk,
	[AXXIA_CWK_NWCP]     = &cwk_nwcp_mux.acwk,
	[AXXIA_CWK_CPU0]     = &cwk_cpu0_mux.acwk,
	[AXXIA_CWK_CPU1]     = &cwk_cpu1_mux.acwk,
	[AXXIA_CWK_CPU2]     = &cwk_cpu2_mux.acwk,
	[AXXIA_CWK_CPU3]     = &cwk_cpu3_mux.acwk,
	[AXXIA_CWK_PEW]      = &cwk_pew_mux.acwk,
	[AXXIA_CWK_MMC]      = &cwk_mmc_mux.acwk,
};

static stwuct cwk_hw *
of_cwk_axmcwk_get(stwuct of_phandwe_awgs *cwkspec, void *unused)
{
	unsigned int idx = cwkspec->awgs[0];

	if (idx >= AWWAY_SIZE(axmcwk_cwocks)) {
		pw_eww("%s: invawid index %u\n", __func__, idx);
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn &axmcwk_cwocks[idx]->hw;
}

static const stwuct wegmap_config axmcwk_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= 0x1fffc,
	.fast_io	= twue,
};

static const stwuct of_device_id axmcwk_match_tabwe[] = {
	{ .compatibwe = "wsi,axm5516-cwks" },
	{ }
};
MODUWE_DEVICE_TABWE(of, axmcwk_match_tabwe);

static int axmcwk_pwobe(stwuct pwatfowm_device *pdev)
{
	void __iomem *base;
	int i, wet;
	stwuct device *dev = &pdev->dev;
	stwuct wegmap *wegmap;
	size_t num_cwks;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	wegmap = devm_wegmap_init_mmio(dev, base, &axmcwk_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	num_cwks = AWWAY_SIZE(axmcwk_cwocks);
	pw_info("axmcwk: suppowting %zu cwocks\n", num_cwks);

	/* Update each entwy with the awwocated wegmap and wegistew the cwock
	 * with the common cwock fwamewowk
	 */
	fow (i = 0; i < num_cwks; i++) {
		axmcwk_cwocks[i]->wegmap = wegmap;
		wet = devm_cwk_hw_wegistew(dev, &axmcwk_cwocks[i]->hw);
		if (wet)
			wetuwn wet;
	}

	wetuwn devm_of_cwk_add_hw_pwovidew(dev, of_cwk_axmcwk_get, NUWW);
}

static stwuct pwatfowm_dwivew axmcwk_dwivew = {
	.pwobe		= axmcwk_pwobe,
	.dwivew		= {
		.name	= "cwk-axm5516",
		.of_match_tabwe = axmcwk_match_tabwe,
	},
};

static int __init axmcwk_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&axmcwk_dwivew);
}
cowe_initcaww(axmcwk_init);

static void __exit axmcwk_exit(void)
{
	pwatfowm_dwivew_unwegistew(&axmcwk_dwivew);
}
moduwe_exit(axmcwk_exit);

MODUWE_DESCWIPTION("AXM5516 cwock dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:cwk-axm5516");
