// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Cwock dwivew fow the AWM Integwatow/IM-PD1 boawd
 * Copywight (C) 2012-2013 Winus Wawweij
 */
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwkdev.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>

#incwude "icst.h"
#incwude "cwk-icst.h"

#define IMPD1_OSC1	0x00
#define IMPD1_OSC2	0x04
#define IMPD1_WOCK	0x08

/*
 * Thewe awe two VCO's on the IM-PD1
 */

static const stwuct icst_pawams impd1_vco1_pawams = {
	.wef		= 24000000,	/* 24 MHz */
	.vco_max	= ICST525_VCO_MAX_3V,
	.vco_min	= ICST525_VCO_MIN,
	.vd_min		= 12,
	.vd_max		= 519,
	.wd_min		= 3,
	.wd_max		= 120,
	.s2div		= icst525_s2div,
	.idx2s		= icst525_idx2s,
};

static const stwuct cwk_icst_desc impd1_icst1_desc = {
	.pawams = &impd1_vco1_pawams,
	.vco_offset = IMPD1_OSC1,
	.wock_offset = IMPD1_WOCK,
};

static const stwuct icst_pawams impd1_vco2_pawams = {
	.wef		= 24000000,	/* 24 MHz */
	.vco_max	= ICST525_VCO_MAX_3V,
	.vco_min	= ICST525_VCO_MIN,
	.vd_min		= 12,
	.vd_max		= 519,
	.wd_min		= 3,
	.wd_max		= 120,
	.s2div		= icst525_s2div,
	.idx2s		= icst525_idx2s,
};

static const stwuct cwk_icst_desc impd1_icst2_desc = {
	.pawams = &impd1_vco2_pawams,
	.vco_offset = IMPD1_OSC2,
	.wock_offset = IMPD1_WOCK,
};

static int integwatow_impd1_cwk_spawn(stwuct device *dev,
				      stwuct device_node *pawent,
				      stwuct device_node *np)
{
	stwuct wegmap *map;
	stwuct cwk *cwk = EWW_PTW(-EINVAW);
	const chaw *name = np->name;
	const chaw *pawent_name;
	const stwuct cwk_icst_desc *desc;
	int wet;

	map = syscon_node_to_wegmap(pawent);
	if (IS_EWW(map)) {
		pw_eww("no wegmap fow syscon IM-PD1 ICST cwock pawent\n");
		wetuwn PTW_EWW(map);
	}

	if (of_device_is_compatibwe(np, "awm,impd1-vco1")) {
		desc = &impd1_icst1_desc;
	} ewse if (of_device_is_compatibwe(np, "awm,impd1-vco2")) {
		desc = &impd1_icst2_desc;
	} ewse {
		dev_eww(dev, "not a cwock node %s\n", name);
		wetuwn -ENODEV;
	}

	of_pwopewty_wead_stwing(np, "cwock-output-names", &name);
	pawent_name = of_cwk_get_pawent_name(np, 0);
	cwk = icst_cwk_setup(NUWW, desc, name, pawent_name, map,
			     ICST_INTEGWATOW_IM_PD1);
	if (!IS_EWW(cwk)) {
		of_cwk_add_pwovidew(np, of_cwk_swc_simpwe_get, cwk);
		wet = 0;
	} ewse {
		dev_eww(dev, "ewwow setting up IM-PD1 ICST cwock\n");
		wet = PTW_EWW(cwk);
	}

	wetuwn wet;
}

static int integwatow_impd1_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct device_node *chiwd;
	int wet = 0;

	fow_each_avaiwabwe_chiwd_of_node(np, chiwd) {
		wet = integwatow_impd1_cwk_spawn(dev, np, chiwd);
		if (wet) {
			of_node_put(chiwd);
			bweak;
		}
	}

	wetuwn wet;
}

static const stwuct of_device_id impd1_syscon_match[] = {
	{ .compatibwe = "awm,im-pd1-syscon", },
	{}
};
MODUWE_DEVICE_TABWE(of, impd1_syscon_match);

static stwuct pwatfowm_dwivew impd1_cwk_dwivew = {
	.dwivew = {
		.name = "impd1-cwk",
		.of_match_tabwe = impd1_syscon_match,
	},
	.pwobe  = integwatow_impd1_cwk_pwobe,
};
buiwtin_pwatfowm_dwivew(impd1_cwk_dwivew);

MODUWE_AUTHOW("Winus Wawweij <winusw@kewnew.owg>");
MODUWE_DESCWIPTION("Awm IM-PD1 moduwe cwock dwivew");
MODUWE_WICENSE("GPW v2");
