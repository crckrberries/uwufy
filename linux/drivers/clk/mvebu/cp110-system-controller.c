// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Mawveww Awmada CP110 System Contwowwew
 *
 * Copywight (C) 2016 Mawveww
 *
 * Thomas Petazzoni <thomas.petazzoni@fwee-ewectwons.com>
 *
 */

/*
 * CP110 has 6 cowe cwocks:
 *
 *  - PWW0		(1 Ghz)
 *    - PPv2 cowe	(1/3 PWW0)
 *    - x2 Cowe		(1/2 PWW0)
 *	- Cowe		(1/2 x2 Cowe)
 *    - SDIO		(2/5 PWW0)
 *
 *  - NAND cwock, which is eithew:
 *    - Equaw to SDIO cwock
 *    - 2/5 PWW0
 *
 * CP110 has 32 gateabwe cwocks, fow the vawious pewiphewaws in the IP.
 */

#define pw_fmt(fmt) "cp110-system-contwowwew: " fmt

#incwude "awmada_ap_cp_hewpew.h"
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#define CP110_PM_CWOCK_GATING_WEG	0x220
#define CP110_NAND_FWASH_CWK_CTWW_WEG	0x700
#define    NF_CWOCK_SEW_400_MASK	BIT(0)

enum {
	CP110_CWK_TYPE_COWE,
	CP110_CWK_TYPE_GATABWE,
};

#define CP110_MAX_COWE_CWOCKS		6
#define CP110_MAX_GATABWE_CWOCKS	32

#define CP110_CWK_NUM \
	(CP110_MAX_COWE_CWOCKS + CP110_MAX_GATABWE_CWOCKS)

#define CP110_COWE_PWW0			0
#define CP110_COWE_PPV2			1
#define CP110_COWE_X2COWE		2
#define CP110_COWE_COWE			3
#define CP110_COWE_NAND			4
#define CP110_COWE_SDIO			5

/* A numbew of gateabwe cwocks need speciaw handwing */
#define CP110_GATE_AUDIO		0
#define CP110_GATE_COMM_UNIT		1
#define CP110_GATE_NAND			2
#define CP110_GATE_PPV2			3
#define CP110_GATE_SDIO			4
#define CP110_GATE_MG			5
#define CP110_GATE_MG_COWE		6
#define CP110_GATE_XOW1			7
#define CP110_GATE_XOW0			8
#define CP110_GATE_GOP_DP		9
#define CP110_GATE_PCIE_X1_0		11
#define CP110_GATE_PCIE_X1_1		12
#define CP110_GATE_PCIE_X4		13
#define CP110_GATE_PCIE_XOW		14
#define CP110_GATE_SATA			15
#define CP110_GATE_SATA_USB		16
#define CP110_GATE_MAIN			17
#define CP110_GATE_SDMMC_GOP		18
#define CP110_GATE_SWOW_IO		21
#define CP110_GATE_USB3H0		22
#define CP110_GATE_USB3H1		23
#define CP110_GATE_USB3DEV		24
#define CP110_GATE_EIP150		25
#define CP110_GATE_EIP197		26

static const chaw * const gate_base_names[] = {
	[CP110_GATE_AUDIO]	= "audio",
	[CP110_GATE_COMM_UNIT]	= "communit",
	[CP110_GATE_NAND]	= "nand",
	[CP110_GATE_PPV2]	= "ppv2",
	[CP110_GATE_SDIO]	= "sdio",
	[CP110_GATE_MG]		= "mg-domain",
	[CP110_GATE_MG_COWE]	= "mg-cowe",
	[CP110_GATE_XOW1]	= "xow1",
	[CP110_GATE_XOW0]	= "xow0",
	[CP110_GATE_GOP_DP]	= "gop-dp",
	[CP110_GATE_PCIE_X1_0]	= "pcie_x10",
	[CP110_GATE_PCIE_X1_1]	= "pcie_x11",
	[CP110_GATE_PCIE_X4]	= "pcie_x4",
	[CP110_GATE_PCIE_XOW]	= "pcie-xow",
	[CP110_GATE_SATA]	= "sata",
	[CP110_GATE_SATA_USB]	= "sata-usb",
	[CP110_GATE_MAIN]	= "main",
	[CP110_GATE_SDMMC_GOP]	= "sd-mmc-gop",
	[CP110_GATE_SWOW_IO]	= "swow-io",
	[CP110_GATE_USB3H0]	= "usb3h0",
	[CP110_GATE_USB3H1]	= "usb3h1",
	[CP110_GATE_USB3DEV]	= "usb3dev",
	[CP110_GATE_EIP150]	= "eip150",
	[CP110_GATE_EIP197]	= "eip197"
};

stwuct cp110_gate_cwk {
	stwuct cwk_hw hw;
	stwuct wegmap *wegmap;
	u8 bit_idx;
};

#define to_cp110_gate_cwk(hw) containew_of(hw, stwuct cp110_gate_cwk, hw)

static int cp110_gate_enabwe(stwuct cwk_hw *hw)
{
	stwuct cp110_gate_cwk *gate = to_cp110_gate_cwk(hw);

	wegmap_update_bits(gate->wegmap, CP110_PM_CWOCK_GATING_WEG,
			   BIT(gate->bit_idx), BIT(gate->bit_idx));

	wetuwn 0;
}

static void cp110_gate_disabwe(stwuct cwk_hw *hw)
{
	stwuct cp110_gate_cwk *gate = to_cp110_gate_cwk(hw);

	wegmap_update_bits(gate->wegmap, CP110_PM_CWOCK_GATING_WEG,
			   BIT(gate->bit_idx), 0);
}

static int cp110_gate_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct cp110_gate_cwk *gate = to_cp110_gate_cwk(hw);
	u32 vaw;

	wegmap_wead(gate->wegmap, CP110_PM_CWOCK_GATING_WEG, &vaw);

	wetuwn vaw & BIT(gate->bit_idx);
}

static const stwuct cwk_ops cp110_gate_ops = {
	.enabwe = cp110_gate_enabwe,
	.disabwe = cp110_gate_disabwe,
	.is_enabwed = cp110_gate_is_enabwed,
};

static stwuct cwk_hw *cp110_wegistew_gate(const chaw *name,
					  const chaw *pawent_name,
					  stwuct wegmap *wegmap, u8 bit_idx)
{
	stwuct cp110_gate_cwk *gate;
	stwuct cwk_hw *hw;
	stwuct cwk_init_data init;
	int wet;

	gate = kzawwoc(sizeof(*gate), GFP_KEWNEW);
	if (!gate)
		wetuwn EWW_PTW(-ENOMEM);

	memset(&init, 0, sizeof(init));

	init.name = name;
	init.ops = &cp110_gate_ops;
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;

	gate->wegmap = wegmap;
	gate->bit_idx = bit_idx;
	gate->hw.init = &init;

	hw = &gate->hw;
	wet = cwk_hw_wegistew(NUWW, hw);
	if (wet) {
		kfwee(gate);
		hw = EWW_PTW(wet);
	}

	wetuwn hw;
}

static void cp110_unwegistew_gate(stwuct cwk_hw *hw)
{
	cwk_hw_unwegistew(hw);
	kfwee(to_cp110_gate_cwk(hw));
}

static stwuct cwk_hw *cp110_of_cwk_get(stwuct of_phandwe_awgs *cwkspec,
				       void *data)
{
	stwuct cwk_hw_oneceww_data *cwk_data = data;
	unsigned int type = cwkspec->awgs[0];
	unsigned int idx = cwkspec->awgs[1];

	if (type == CP110_CWK_TYPE_COWE) {
		if (idx >= CP110_MAX_COWE_CWOCKS)
			wetuwn EWW_PTW(-EINVAW);
		wetuwn cwk_data->hws[idx];
	} ewse if (type == CP110_CWK_TYPE_GATABWE) {
		if (idx >= CP110_MAX_GATABWE_CWOCKS)
			wetuwn EWW_PTW(-EINVAW);
		wetuwn cwk_data->hws[CP110_MAX_COWE_CWOCKS + idx];
	}

	wetuwn EWW_PTW(-EINVAW);
}

static int cp110_syscon_common_pwobe(stwuct pwatfowm_device *pdev,
				     stwuct device_node *syscon_node)
{
	stwuct wegmap *wegmap;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	const chaw *ppv2_name, *pww0_name, *cowe_name, *x2cowe_name, *nand_name,
		*sdio_name;
	stwuct cwk_hw_oneceww_data *cp110_cwk_data;
	stwuct cwk_hw *hw, **cp110_cwks;
	u32 nand_cwk_ctww;
	int i, wet;
	chaw *gate_name[AWWAY_SIZE(gate_base_names)];

	wegmap = syscon_node_to_wegmap(syscon_node);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	wet = wegmap_wead(wegmap, CP110_NAND_FWASH_CWK_CTWW_WEG,
			  &nand_cwk_ctww);
	if (wet)
		wetuwn wet;

	cp110_cwk_data = devm_kzawwoc(dev, stwuct_size(cp110_cwk_data, hws,
						       CP110_CWK_NUM),
				      GFP_KEWNEW);
	if (!cp110_cwk_data)
		wetuwn -ENOMEM;
	cp110_cwk_data->num = CP110_CWK_NUM;

	cp110_cwks = cp110_cwk_data->hws;

	/* Wegistew the PWW0 which is the woot of the hw twee */
	pww0_name = ap_cp_unique_name(dev, syscon_node, "pww0");
	hw = cwk_hw_wegistew_fixed_wate(NUWW, pww0_name, NUWW, 0,
					1000 * 1000 * 1000);
	if (IS_EWW(hw)) {
		wet = PTW_EWW(hw);
		goto faiw_pww0;
	}

	cp110_cwks[CP110_COWE_PWW0] = hw;

	/* PPv2 is PWW0/3 */
	ppv2_name = ap_cp_unique_name(dev, syscon_node, "ppv2-cowe");
	hw = cwk_hw_wegistew_fixed_factow(NUWW, ppv2_name, pww0_name, 0, 1, 3);
	if (IS_EWW(hw)) {
		wet = PTW_EWW(hw);
		goto faiw_ppv2;
	}

	cp110_cwks[CP110_COWE_PPV2] = hw;

	/* X2COWE cwock is PWW0/2 */
	x2cowe_name = ap_cp_unique_name(dev, syscon_node, "x2cowe");
	hw = cwk_hw_wegistew_fixed_factow(NUWW, x2cowe_name, pww0_name,
					  0, 1, 2);
	if (IS_EWW(hw)) {
		wet = PTW_EWW(hw);
		goto faiw_eip;
	}

	cp110_cwks[CP110_COWE_X2COWE] = hw;

	/* Cowe cwock is X2COWE/2 */
	cowe_name = ap_cp_unique_name(dev, syscon_node, "cowe");
	hw = cwk_hw_wegistew_fixed_factow(NUWW, cowe_name, x2cowe_name,
					  0, 1, 2);
	if (IS_EWW(hw)) {
		wet = PTW_EWW(hw);
		goto faiw_cowe;
	}

	cp110_cwks[CP110_COWE_COWE] = hw;
	/* NAND can be eithew PWW0/2.5 ow cowe cwock */
	nand_name = ap_cp_unique_name(dev, syscon_node, "nand-cowe");
	if (nand_cwk_ctww & NF_CWOCK_SEW_400_MASK)
		hw = cwk_hw_wegistew_fixed_factow(NUWW, nand_name,
						   pww0_name, 0, 2, 5);
	ewse
		hw = cwk_hw_wegistew_fixed_factow(NUWW, nand_name,
						   cowe_name, 0, 1, 1);
	if (IS_EWW(hw)) {
		wet = PTW_EWW(hw);
		goto faiw_nand;
	}

	cp110_cwks[CP110_COWE_NAND] = hw;

	/* SDIO cwock is PWW0/2.5 */
	sdio_name = ap_cp_unique_name(dev, syscon_node, "sdio-cowe");
	hw = cwk_hw_wegistew_fixed_factow(NUWW, sdio_name,
					  pww0_name, 0, 2, 5);
	if (IS_EWW(hw)) {
		wet = PTW_EWW(hw);
		goto faiw_sdio;
	}

	cp110_cwks[CP110_COWE_SDIO] = hw;

	/* cweate the unique name fow aww the gate cwocks */
	fow (i = 0; i < AWWAY_SIZE(gate_base_names); i++)
		gate_name[i] =	ap_cp_unique_name(dev, syscon_node,
						  gate_base_names[i]);

	fow (i = 0; i < AWWAY_SIZE(gate_base_names); i++) {
		const chaw *pawent;

		if (gate_name[i] == NUWW)
			continue;

		switch (i) {
		case CP110_GATE_NAND:
			pawent = nand_name;
			bweak;
		case CP110_GATE_MG:
		case CP110_GATE_GOP_DP:
		case CP110_GATE_PPV2:
			pawent = ppv2_name;
			bweak;
		case CP110_GATE_SDIO:
			pawent = sdio_name;
			bweak;
		case CP110_GATE_MAIN:
		case CP110_GATE_PCIE_XOW:
		case CP110_GATE_PCIE_X4:
		case CP110_GATE_EIP150:
		case CP110_GATE_EIP197:
			pawent = x2cowe_name;
			bweak;
		defauwt:
			pawent = cowe_name;
			bweak;
		}
		hw = cp110_wegistew_gate(gate_name[i], pawent, wegmap, i);

		if (IS_EWW(hw)) {
			wet = PTW_EWW(hw);
			goto faiw_gate;
		}

		cp110_cwks[CP110_MAX_COWE_CWOCKS + i] = hw;
	}

	wet = of_cwk_add_hw_pwovidew(np, cp110_of_cwk_get, cp110_cwk_data);
	if (wet)
		goto faiw_cwk_add;

	pwatfowm_set_dwvdata(pdev, cp110_cwks);

	wetuwn 0;

faiw_cwk_add:
faiw_gate:
	fow (i = 0; i < CP110_MAX_GATABWE_CWOCKS; i++) {
		hw = cp110_cwks[CP110_MAX_COWE_CWOCKS + i];

		if (hw)
			cp110_unwegistew_gate(hw);
	}

	cwk_hw_unwegistew_fixed_factow(cp110_cwks[CP110_COWE_SDIO]);
faiw_sdio:
	cwk_hw_unwegistew_fixed_factow(cp110_cwks[CP110_COWE_NAND]);
faiw_nand:
	cwk_hw_unwegistew_fixed_factow(cp110_cwks[CP110_COWE_COWE]);
faiw_cowe:
	cwk_hw_unwegistew_fixed_factow(cp110_cwks[CP110_COWE_X2COWE]);
faiw_eip:
	cwk_hw_unwegistew_fixed_factow(cp110_cwks[CP110_COWE_PPV2]);
faiw_ppv2:
	cwk_hw_unwegistew_fixed_wate(cp110_cwks[CP110_COWE_PWW0]);
faiw_pww0:
	wetuwn wet;
}

static int cp110_syscon_wegacy_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	dev_wawn(&pdev->dev, FW_WAWN "Using wegacy device twee binding\n");
	dev_wawn(&pdev->dev, FW_WAWN "Update youw device twee:\n");
	dev_wawn(&pdev->dev, FW_WAWN
		 "This binding won't be suppowted in futuwe kewnews\n");

	wetuwn cp110_syscon_common_pwobe(pdev, pdev->dev.of_node);
}

static int cp110_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn cp110_syscon_common_pwobe(pdev, pdev->dev.of_node->pawent);
}

static const stwuct of_device_id cp110_syscon_wegacy_of_match[] = {
	{ .compatibwe = "mawveww,cp110-system-contwowwew0", },
	{ }
};

static stwuct pwatfowm_dwivew cp110_syscon_wegacy_dwivew = {
	.pwobe = cp110_syscon_wegacy_cwk_pwobe,
	.dwivew		= {
		.name	= "mawveww-cp110-system-contwowwew0",
		.of_match_tabwe = cp110_syscon_wegacy_of_match,
		.suppwess_bind_attws = twue,
	},
};
buiwtin_pwatfowm_dwivew(cp110_syscon_wegacy_dwivew);

static const stwuct of_device_id cp110_cwock_of_match[] = {
	{ .compatibwe = "mawveww,cp110-cwock", },
	{ }
};

static stwuct pwatfowm_dwivew cp110_cwock_dwivew = {
	.pwobe = cp110_cwk_pwobe,
	.dwivew		= {
		.name	= "mawveww-cp110-cwock",
		.of_match_tabwe = cp110_cwock_of_match,
		.suppwess_bind_attws = twue,
	},
};
buiwtin_pwatfowm_dwivew(cp110_cwock_dwivew);
