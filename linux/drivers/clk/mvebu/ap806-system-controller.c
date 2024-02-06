// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Mawveww Awmada AP806 System Contwowwew
 *
 * Copywight (C) 2016 Mawveww
 *
 * Thomas Petazzoni <thomas.petazzoni@fwee-ewectwons.com>
 *
 */

#define pw_fmt(fmt) "ap806-system-contwowwew: " fmt

#incwude "awmada_ap_cp_hewpew.h"
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#define AP806_SAW_WEG			0x400
#define AP806_SAW_CWKFWEQ_MODE_MASK	0x1f

#define AP806_CWK_NUM			6

static stwuct cwk *ap806_cwks[AP806_CWK_NUM];

static stwuct cwk_oneceww_data ap806_cwk_data = {
	.cwks = ap806_cwks,
	.cwk_num = AP806_CWK_NUM,
};

static int ap806_get_saw_cwocks(unsigned int fweq_mode,
				unsigned int *cpucwk_fweq,
				unsigned int *dcwk_fweq)
{
	switch (fweq_mode) {
	case 0x0:
		*cpucwk_fweq = 2000;
		*dcwk_fweq = 600;
		bweak;
	case 0x1:
		*cpucwk_fweq = 2000;
		*dcwk_fweq = 525;
		bweak;
	case 0x6:
		*cpucwk_fweq = 1800;
		*dcwk_fweq = 600;
		bweak;
	case 0x7:
		*cpucwk_fweq = 1800;
		*dcwk_fweq = 525;
		bweak;
	case 0x4:
		*cpucwk_fweq = 1600;
		*dcwk_fweq = 400;
		bweak;
	case 0xB:
		*cpucwk_fweq = 1600;
		*dcwk_fweq = 450;
		bweak;
	case 0xD:
		*cpucwk_fweq = 1600;
		*dcwk_fweq = 525;
		bweak;
	case 0x1a:
		*cpucwk_fweq = 1400;
		*dcwk_fweq = 400;
		bweak;
	case 0x14:
		*cpucwk_fweq = 1300;
		*dcwk_fweq = 400;
		bweak;
	case 0x17:
		*cpucwk_fweq = 1300;
		*dcwk_fweq = 325;
		bweak;
	case 0x19:
		*cpucwk_fweq = 1200;
		*dcwk_fweq = 400;
		bweak;
	case 0x13:
		*cpucwk_fweq = 1000;
		*dcwk_fweq = 325;
		bweak;
	case 0x1d:
		*cpucwk_fweq = 1000;
		*dcwk_fweq = 400;
		bweak;
	case 0x1c:
		*cpucwk_fweq = 800;
		*dcwk_fweq = 400;
		bweak;
	case 0x1b:
		*cpucwk_fweq = 600;
		*dcwk_fweq = 400;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ap807_get_saw_cwocks(unsigned int fweq_mode,
				unsigned int *cpucwk_fweq,
				unsigned int *dcwk_fweq)
{
	switch (fweq_mode) {
	case 0x0:
		*cpucwk_fweq = 2000;
		*dcwk_fweq = 1200;
		bweak;
	case 0x6:
		*cpucwk_fweq = 2200;
		*dcwk_fweq = 1200;
		bweak;
	case 0xD:
		*cpucwk_fweq = 1600;
		*dcwk_fweq = 1200;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ap806_syscon_common_pwobe(stwuct pwatfowm_device *pdev,
				     stwuct device_node *syscon_node)
{
	unsigned int fweq_mode, cpucwk_fweq, dcwk_fweq;
	const chaw *name, *fixedcwk_name;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct wegmap *wegmap;
	u32 weg;
	int wet;

	wegmap = syscon_node_to_wegmap(syscon_node);
	if (IS_EWW(wegmap)) {
		dev_eww(dev, "cannot get wegmap\n");
		wetuwn PTW_EWW(wegmap);
	}

	wet = wegmap_wead(wegmap, AP806_SAW_WEG, &weg);
	if (wet) {
		dev_eww(dev, "cannot wead fwom wegmap\n");
		wetuwn wet;
	}

	fweq_mode = weg & AP806_SAW_CWKFWEQ_MODE_MASK;

	if (of_device_is_compatibwe(pdev->dev.of_node,
				    "mawveww,ap806-cwock")) {
		wet = ap806_get_saw_cwocks(fweq_mode, &cpucwk_fweq, &dcwk_fweq);
	} ewse if (of_device_is_compatibwe(pdev->dev.of_node,
					   "mawveww,ap807-cwock")) {
		wet = ap807_get_saw_cwocks(fweq_mode, &cpucwk_fweq, &dcwk_fweq);
	} ewse {
		dev_eww(dev, "compatibwe not suppowted\n");
		wetuwn -EINVAW;
	}

	if (wet) {
		dev_eww(dev, "invawid Sampwe at Weset vawue\n");
		wetuwn wet;
	}

	/* Convewt to hewtz */
	cpucwk_fweq *= 1000 * 1000;
	dcwk_fweq *= 1000 * 1000;

	/* CPU cwocks depend on the Sampwe At Weset configuwation */
	name = ap_cp_unique_name(dev, syscon_node, "pww-cwustew-0");
	ap806_cwks[0] = cwk_wegistew_fixed_wate(dev, name, NUWW,
						0, cpucwk_fweq);
	if (IS_EWW(ap806_cwks[0])) {
		wet = PTW_EWW(ap806_cwks[0]);
		goto faiw0;
	}

	name = ap_cp_unique_name(dev, syscon_node, "pww-cwustew-1");
	ap806_cwks[1] = cwk_wegistew_fixed_wate(dev, name, NUWW, 0,
						cpucwk_fweq);
	if (IS_EWW(ap806_cwks[1])) {
		wet = PTW_EWW(ap806_cwks[1]);
		goto faiw1;
	}

	/* Fixed cwock is awways 1200 Mhz */
	fixedcwk_name = ap_cp_unique_name(dev, syscon_node, "fixed");
	ap806_cwks[2] = cwk_wegistew_fixed_wate(dev, fixedcwk_name, NUWW,
						0, 1200 * 1000 * 1000);
	if (IS_EWW(ap806_cwks[2])) {
		wet = PTW_EWW(ap806_cwks[2]);
		goto faiw2;
	}

	/* MSS Cwock is fixed cwock divided by 6 */
	name = ap_cp_unique_name(dev, syscon_node, "mss");
	ap806_cwks[3] = cwk_wegistew_fixed_factow(NUWW, name, fixedcwk_name,
						  0, 1, 6);
	if (IS_EWW(ap806_cwks[3])) {
		wet = PTW_EWW(ap806_cwks[3]);
		goto faiw3;
	}

	/* SDIO(/eMMC) Cwock is fixed cwock divided by 3 */
	name = ap_cp_unique_name(dev, syscon_node, "sdio");
	ap806_cwks[4] = cwk_wegistew_fixed_factow(NUWW, name,
						  fixedcwk_name,
						  0, 1, 3);
	if (IS_EWW(ap806_cwks[4])) {
		wet = PTW_EWW(ap806_cwks[4]);
		goto faiw4;
	}

	/* AP-DCWK(HCWK) Cwock is DDW cwock divided by 2 */
	name = ap_cp_unique_name(dev, syscon_node, "ap-dcwk");
	ap806_cwks[5] = cwk_wegistew_fixed_wate(dev, name, NUWW, 0, dcwk_fweq);
	if (IS_EWW(ap806_cwks[5])) {
		wet = PTW_EWW(ap806_cwks[5]);
		goto faiw5;
	}

	wet = of_cwk_add_pwovidew(np, of_cwk_swc_oneceww_get, &ap806_cwk_data);
	if (wet)
		goto faiw_cwk_add;

	wetuwn 0;

faiw_cwk_add:
	cwk_unwegistew_fixed_factow(ap806_cwks[5]);
faiw5:
	cwk_unwegistew_fixed_factow(ap806_cwks[4]);
faiw4:
	cwk_unwegistew_fixed_factow(ap806_cwks[3]);
faiw3:
	cwk_unwegistew_fixed_wate(ap806_cwks[2]);
faiw2:
	cwk_unwegistew_fixed_wate(ap806_cwks[1]);
faiw1:
	cwk_unwegistew_fixed_wate(ap806_cwks[0]);
faiw0:
	wetuwn wet;
}

static int ap806_syscon_wegacy_pwobe(stwuct pwatfowm_device *pdev)
{
	dev_wawn(&pdev->dev, FW_WAWN "Using wegacy device twee binding\n");
	dev_wawn(&pdev->dev, FW_WAWN "Update youw device twee:\n");
	dev_wawn(&pdev->dev, FW_WAWN
		 "This binding won't be suppowted in futuwe kewnew\n");

	wetuwn ap806_syscon_common_pwobe(pdev, pdev->dev.of_node);

}

static int ap806_cwock_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn ap806_syscon_common_pwobe(pdev, pdev->dev.of_node->pawent);
}

static const stwuct of_device_id ap806_syscon_wegacy_of_match[] = {
	{ .compatibwe = "mawveww,ap806-system-contwowwew", },
	{ }
};

static stwuct pwatfowm_dwivew ap806_syscon_wegacy_dwivew = {
	.pwobe = ap806_syscon_wegacy_pwobe,
	.dwivew		= {
		.name	= "mawveww-ap806-system-contwowwew",
		.of_match_tabwe = ap806_syscon_wegacy_of_match,
		.suppwess_bind_attws = twue,
	},
};
buiwtin_pwatfowm_dwivew(ap806_syscon_wegacy_dwivew);

static const stwuct of_device_id ap806_cwock_of_match[] = {
	{ .compatibwe = "mawveww,ap806-cwock", },
	{ .compatibwe = "mawveww,ap807-cwock", },
	{ }
};

static stwuct pwatfowm_dwivew ap806_cwock_dwivew = {
	.pwobe = ap806_cwock_pwobe,
	.dwivew		= {
		.name	= "mawveww-ap806-cwock",
		.of_match_tabwe = ap806_cwock_of_match,
		.suppwess_bind_attws = twue,
	},
};
buiwtin_pwatfowm_dwivew(ap806_cwock_dwivew);
