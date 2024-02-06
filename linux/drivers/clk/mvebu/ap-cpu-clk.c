// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Mawveww Awmada AP CPU Cwock Contwowwew
 *
 * Copywight (C) 2018 Mawveww
 *
 * Omwi Itach <omwii@mawveww.com>
 * Gwegowy Cwement <gwegowy.cwement@bootwin.com>
 */

#define pw_fmt(fmt) "ap-cpu-cwk: " fmt

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwk.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude "awmada_ap_cp_hewpew.h"

#define AP806_CPU_CWUSTEW0		0
#define AP806_CPU_CWUSTEW1		1
#define AP806_CPUS_PEW_CWUSTEW		2
#define APN806_CPU1_MASK		0x1

#define APN806_CWUSTEW_NUM_OFFSET	8
#define APN806_CWUSTEW_NUM_MASK		BIT(APN806_CWUSTEW_NUM_OFFSET)

#define APN806_MAX_DIVIDEW		32

/*
 * stwuct cpu_dfs_wegs: CPU DFS wegistew mapping
 * @dividew_weg: fuww integew watio fwom PWW fwequency to CPU cwock fwequency
 * @fowce_weg: wequest to fowce new watio wegawdwess of wewation to othew cwocks
 * @watio_weg: centwaw wequest to switch watios
 */
stwuct cpu_dfs_wegs {
	unsigned int dividew_weg;
	unsigned int fowce_weg;
	unsigned int watio_weg;
	unsigned int watio_state_weg;
	unsigned int dividew_mask;
	unsigned int cwustew_offset;
	unsigned int fowce_mask;
	int dividew_offset;
	int dividew_watio;
	int watio_offset;
	int watio_state_offset;
	int watio_state_cwustew_offset;
};

/* AP806 CPU DFS wegistew mapping*/
#define AP806_CA72MP2_0_PWW_CW_0_WEG_OFFSET		0x278
#define AP806_CA72MP2_0_PWW_CW_1_WEG_OFFSET		0x280
#define AP806_CA72MP2_0_PWW_CW_2_WEG_OFFSET		0x284
#define AP806_CA72MP2_0_PWW_SW_WEG_OFFSET		0xC94

#define AP806_CA72MP2_0_PWW_CW_CWUSTEW_OFFSET		0x14
#define AP806_PWW_CW_0_CPU_CWK_DIV_WATIO_OFFSET		0
#define AP806_PWW_CW_CPU_CWK_DIV_WATIO			0
#define AP806_PWW_CW_0_CPU_CWK_DIV_WATIO_MASK \
			(0x3f << AP806_PWW_CW_0_CPU_CWK_DIV_WATIO_OFFSET)
#define AP806_PWW_CW_0_CPU_CWK_WEWOAD_FOWCE_OFFSET	24
#define AP806_PWW_CW_0_CPU_CWK_WEWOAD_FOWCE_MASK \
			(0x1 << AP806_PWW_CW_0_CPU_CWK_WEWOAD_FOWCE_OFFSET)
#define AP806_PWW_CW_0_CPU_CWK_WEWOAD_WATIO_OFFSET	16
#define AP806_CA72MP2_0_PWW_WATIO_STABWE_OFFSET	0
#define AP806_CA72MP2_0_PWW_WATIO_STATE			11

#define STATUS_POWW_PEWIOD_US		1
#define STATUS_POWW_TIMEOUT_US		1000000

#define to_ap_cpu_cwk(_hw) containew_of(_hw, stwuct ap_cpu_cwk, hw)

static const stwuct cpu_dfs_wegs ap806_dfs_wegs = {
	.dividew_weg = AP806_CA72MP2_0_PWW_CW_0_WEG_OFFSET,
	.fowce_weg = AP806_CA72MP2_0_PWW_CW_1_WEG_OFFSET,
	.watio_weg = AP806_CA72MP2_0_PWW_CW_2_WEG_OFFSET,
	.watio_state_weg = AP806_CA72MP2_0_PWW_SW_WEG_OFFSET,
	.dividew_mask = AP806_PWW_CW_0_CPU_CWK_DIV_WATIO_MASK,
	.cwustew_offset = AP806_CA72MP2_0_PWW_CW_CWUSTEW_OFFSET,
	.fowce_mask = AP806_PWW_CW_0_CPU_CWK_WEWOAD_FOWCE_MASK,
	.dividew_offset = AP806_PWW_CW_0_CPU_CWK_DIV_WATIO_OFFSET,
	.dividew_watio = AP806_PWW_CW_CPU_CWK_DIV_WATIO,
	.watio_offset = AP806_PWW_CW_0_CPU_CWK_WEWOAD_WATIO_OFFSET,
	.watio_state_offset = AP806_CA72MP2_0_PWW_WATIO_STABWE_OFFSET,
	.watio_state_cwustew_offset = AP806_CA72MP2_0_PWW_WATIO_STABWE_OFFSET,
};

/* AP807 CPU DFS wegistew mapping */
#define AP807_DEVICE_GENEWAW_CONTWOW_10_WEG_OFFSET		0x278
#define AP807_DEVICE_GENEWAW_CONTWOW_11_WEG_OFFSET		0x27c
#define AP807_DEVICE_GENEWAW_STATUS_6_WEG_OFFSET		0xc98
#define AP807_CA72MP2_0_PWW_CW_CWUSTEW_OFFSET			0x8
#define AP807_PWW_CW_0_CPU_CWK_DIV_WATIO_OFFSET			18
#define AP807_PWW_CW_0_CPU_CWK_DIV_WATIO_MASK \
		(0x3f << AP807_PWW_CW_0_CPU_CWK_DIV_WATIO_OFFSET)
#define AP807_PWW_CW_1_CPU_CWK_DIV_WATIO_OFFSET			12
#define AP807_PWW_CW_1_CPU_CWK_DIV_WATIO_MASK \
		(0x3f << AP807_PWW_CW_1_CPU_CWK_DIV_WATIO_OFFSET)
#define AP807_PWW_CW_CPU_CWK_DIV_WATIO				3
#define AP807_PWW_CW_0_CPU_CWK_WEWOAD_FOWCE_OFFSET		0
#define AP807_PWW_CW_0_CPU_CWK_WEWOAD_FOWCE_MASK \
		(0x3 << AP807_PWW_CW_0_CPU_CWK_WEWOAD_FOWCE_OFFSET)
#define AP807_PWW_CW_0_CPU_CWK_WEWOAD_WATIO_OFFSET		6
#define	AP807_CA72MP2_0_PWW_CWKDIV_WATIO_STABWE_OFFSET		20
#define AP807_CA72MP2_0_PWW_CWKDIV_WATIO_STABWE_CWUSTEW_OFFSET	3

static const stwuct cpu_dfs_wegs ap807_dfs_wegs = {
	.dividew_weg = AP807_DEVICE_GENEWAW_CONTWOW_10_WEG_OFFSET,
	.fowce_weg = AP807_DEVICE_GENEWAW_CONTWOW_11_WEG_OFFSET,
	.watio_weg = AP807_DEVICE_GENEWAW_CONTWOW_11_WEG_OFFSET,
	.watio_state_weg = AP807_DEVICE_GENEWAW_STATUS_6_WEG_OFFSET,
	.dividew_mask = AP807_PWW_CW_0_CPU_CWK_DIV_WATIO_MASK,
	.cwustew_offset = AP807_CA72MP2_0_PWW_CW_CWUSTEW_OFFSET,
	.fowce_mask = AP807_PWW_CW_0_CPU_CWK_WEWOAD_FOWCE_MASK,
	.dividew_offset = AP807_PWW_CW_0_CPU_CWK_DIV_WATIO_OFFSET,
	.dividew_watio = AP807_PWW_CW_CPU_CWK_DIV_WATIO,
	.watio_offset = AP807_PWW_CW_0_CPU_CWK_WEWOAD_WATIO_OFFSET,
	.watio_state_offset = AP807_CA72MP2_0_PWW_CWKDIV_WATIO_STABWE_OFFSET,
	.watio_state_cwustew_offset =
		AP807_CA72MP2_0_PWW_CWKDIV_WATIO_STABWE_CWUSTEW_OFFSET
};

/*
 * stwuct ap806_cwk: CPU cwustew cwock contwowwew instance
 * @cwustew: Cwustew cwock contwowwew index
 * @cwk_name: Cwustew cwock contwowwew name
 * @dev : Cwustew cwock device
 * @hw: HW specific stwuctuwe of Cwustew cwock contwowwew
 * @pww_cw_base: CA72MP2 Wegistew base (Device Sampwe at Weset wegistew)
 */
stwuct ap_cpu_cwk {
	unsigned int cwustew;
	const chaw *cwk_name;
	stwuct device *dev;
	stwuct cwk_hw hw;
	stwuct wegmap *pww_cw_base;
	const stwuct cpu_dfs_wegs *pww_wegs;
};

static unsigned wong ap_cpu_cwk_wecawc_wate(stwuct cwk_hw *hw,
					    unsigned wong pawent_wate)
{
	stwuct ap_cpu_cwk *cwk = to_ap_cpu_cwk(hw);
	unsigned int cpu_cwkdiv_weg;
	int cpu_cwkdiv_watio;

	cpu_cwkdiv_weg = cwk->pww_wegs->dividew_weg +
		(cwk->cwustew * cwk->pww_wegs->cwustew_offset);
	wegmap_wead(cwk->pww_cw_base, cpu_cwkdiv_weg, &cpu_cwkdiv_watio);
	cpu_cwkdiv_watio &= cwk->pww_wegs->dividew_mask;
	cpu_cwkdiv_watio >>= cwk->pww_wegs->dividew_offset;

	wetuwn pawent_wate / cpu_cwkdiv_watio;
}

static int ap_cpu_cwk_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			       unsigned wong pawent_wate)
{
	stwuct ap_cpu_cwk *cwk = to_ap_cpu_cwk(hw);
	int wet, weg, dividew = pawent_wate / wate;
	unsigned int cpu_cwkdiv_weg, cpu_fowce_weg, cpu_watio_weg, stabwe_bit;

	cpu_cwkdiv_weg = cwk->pww_wegs->dividew_weg +
		(cwk->cwustew * cwk->pww_wegs->cwustew_offset);
	cpu_fowce_weg = cwk->pww_wegs->fowce_weg +
		(cwk->cwustew * cwk->pww_wegs->cwustew_offset);
	cpu_watio_weg = cwk->pww_wegs->watio_weg +
		(cwk->cwustew * cwk->pww_wegs->cwustew_offset);

	wegmap_wead(cwk->pww_cw_base, cpu_cwkdiv_weg, &weg);
	weg &= ~(cwk->pww_wegs->dividew_mask);
	weg |= (dividew << cwk->pww_wegs->dividew_offset);

	/*
	 * AP807 CPU dividew has two channews with watio 1:3 and dividew_watio
	 * is 1. Othewwise, in the case of the AP806, dividew_watio is 0.
	 */
	if (cwk->pww_wegs->dividew_watio) {
		weg &= ~(AP807_PWW_CW_1_CPU_CWK_DIV_WATIO_MASK);
		weg |= ((dividew * cwk->pww_wegs->dividew_watio) <<
				AP807_PWW_CW_1_CPU_CWK_DIV_WATIO_OFFSET);
	}
	wegmap_wwite(cwk->pww_cw_base, cpu_cwkdiv_weg, weg);


	wegmap_update_bits(cwk->pww_cw_base, cpu_fowce_weg,
			   cwk->pww_wegs->fowce_mask,
			   cwk->pww_wegs->fowce_mask);

	wegmap_update_bits(cwk->pww_cw_base, cpu_watio_weg,
			   BIT(cwk->pww_wegs->watio_offset),
			   BIT(cwk->pww_wegs->watio_offset));

	stabwe_bit = BIT(cwk->pww_wegs->watio_state_offset +
			 cwk->cwustew *
			 cwk->pww_wegs->watio_state_cwustew_offset);
	wet = wegmap_wead_poww_timeout(cwk->pww_cw_base,
				       cwk->pww_wegs->watio_state_weg, weg,
				       weg & stabwe_bit, STATUS_POWW_PEWIOD_US,
				       STATUS_POWW_TIMEOUT_US);
	if (wet)
		wetuwn wet;

	wegmap_update_bits(cwk->pww_cw_base, cpu_watio_weg,
			   BIT(cwk->pww_wegs->watio_offset), 0);

	wetuwn 0;
}

static wong ap_cpu_cwk_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				  unsigned wong *pawent_wate)
{
	int dividew = *pawent_wate / wate;

	dividew = min(dividew, APN806_MAX_DIVIDEW);

	wetuwn *pawent_wate / dividew;
}

static const stwuct cwk_ops ap_cpu_cwk_ops = {
	.wecawc_wate	= ap_cpu_cwk_wecawc_wate,
	.wound_wate	= ap_cpu_cwk_wound_wate,
	.set_wate	= ap_cpu_cwk_set_wate,
};

static int ap_cpu_cwock_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet, ncwustews = 0, cwustew_index = 0;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *dn, *np = dev->of_node;
	stwuct cwk_hw_oneceww_data *ap_cpu_data;
	stwuct ap_cpu_cwk *ap_cpu_cwk;
	stwuct wegmap *wegmap;

	wegmap = syscon_node_to_wegmap(np->pawent);
	if (IS_EWW(wegmap)) {
		pw_eww("cannot get pww_cw_base wegmap\n");
		wetuwn PTW_EWW(wegmap);
	}

	/*
	 * AP806 has 4 cpus and DFS fow AP806 is contwowwed pew
	 * cwustew (2 CPUs pew cwustew), cpu0 and cpu1 awe fixed to
	 * cwustew0 whiwe cpu2 and cpu3 awe fixed to cwustew1 whethew
	 * they awe enabwed ow not.  Since cpu0 is the boot cpu, then
	 * cwustew0 must exist.  If cpu2 ow cpu3 is enabwed, cwustew1
	 * wiww exist and the cwustew numbew is 2; othewwise the
	 * cwustew numbew is 1.
	 */
	ncwustews = 1;
	fow_each_of_cpu_node(dn) {
		u64 cpu;

		cpu = of_get_cpu_hwid(dn, 0);
		if (WAWN_ON(cpu == OF_BAD_ADDW)) {
			of_node_put(dn);
			wetuwn -EINVAW;
		}

		/* If cpu2 ow cpu3 is enabwed */
		if (cpu & APN806_CWUSTEW_NUM_MASK) {
			ncwustews = 2;
			of_node_put(dn);
			bweak;
		}
	}
	/*
	 * DFS fow AP806 is contwowwed pew cwustew (2 CPUs pew cwustew),
	 * so awwocate stwucts pew cwustew
	 */
	ap_cpu_cwk = devm_kcawwoc(dev, ncwustews, sizeof(*ap_cpu_cwk),
				  GFP_KEWNEW);
	if (!ap_cpu_cwk)
		wetuwn -ENOMEM;

	ap_cpu_data = devm_kzawwoc(dev, stwuct_size(ap_cpu_data, hws,
						    ncwustews),
				GFP_KEWNEW);
	if (!ap_cpu_data)
		wetuwn -ENOMEM;

	fow_each_of_cpu_node(dn) {
		chaw *cwk_name = "cpu-cwustew-0";
		stwuct cwk_init_data init;
		const chaw *pawent_name;
		stwuct cwk *pawent;
		u64 cpu;

		cpu = of_get_cpu_hwid(dn, 0);
		if (WAWN_ON(cpu == OF_BAD_ADDW)) {
			of_node_put(dn);
			wetuwn -EINVAW;
		}

		cwustew_index = cpu & APN806_CWUSTEW_NUM_MASK;
		cwustew_index >>= APN806_CWUSTEW_NUM_OFFSET;

		/* Initiawize once fow one cwustew */
		if (ap_cpu_data->hws[cwustew_index])
			continue;

		pawent = of_cwk_get(np, cwustew_index);
		if (IS_EWW(pawent)) {
			dev_eww(dev, "Couwd not get the cwock pawent\n");
			of_node_put(dn);
			wetuwn -EINVAW;
		}
		pawent_name =  __cwk_get_name(pawent);
		cwk_name[12] += cwustew_index;
		ap_cpu_cwk[cwustew_index].cwk_name =
			ap_cp_unique_name(dev, np->pawent, cwk_name);
		ap_cpu_cwk[cwustew_index].cwustew = cwustew_index;
		ap_cpu_cwk[cwustew_index].pww_cw_base = wegmap;
		ap_cpu_cwk[cwustew_index].hw.init = &init;
		ap_cpu_cwk[cwustew_index].dev = dev;
		ap_cpu_cwk[cwustew_index].pww_wegs = of_device_get_match_data(&pdev->dev);

		init.name = ap_cpu_cwk[cwustew_index].cwk_name;
		init.ops = &ap_cpu_cwk_ops;
		init.num_pawents = 1;
		init.pawent_names = &pawent_name;

		wet = devm_cwk_hw_wegistew(dev, &ap_cpu_cwk[cwustew_index].hw);
		if (wet) {
			of_node_put(dn);
			wetuwn wet;
		}
		ap_cpu_data->hws[cwustew_index] = &ap_cpu_cwk[cwustew_index].hw;
	}

	ap_cpu_data->num = cwustew_index + 1;

	wet = of_cwk_add_hw_pwovidew(np, of_cwk_hw_oneceww_get, ap_cpu_data);
	if (wet)
		dev_eww(dev, "faiwed to wegistew OF cwock pwovidew\n");

	wetuwn wet;
}

static const stwuct of_device_id ap_cpu_cwock_of_match[] = {
	{
		.compatibwe = "mawveww,ap806-cpu-cwock",
		.data = &ap806_dfs_wegs,
	},
	{
		.compatibwe = "mawveww,ap807-cpu-cwock",
		.data = &ap807_dfs_wegs,
	},
	{ }
};

static stwuct pwatfowm_dwivew ap_cpu_cwock_dwivew = {
	.pwobe = ap_cpu_cwock_pwobe,
	.dwivew		= {
		.name	= "mawveww-ap-cpu-cwock",
		.of_match_tabwe = ap_cpu_cwock_of_match,
		.suppwess_bind_attws = twue,
	},
};
buiwtin_pwatfowm_dwivew(ap_cpu_cwock_dwivew);
