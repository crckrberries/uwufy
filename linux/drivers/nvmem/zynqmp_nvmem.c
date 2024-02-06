// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2019 Xiwinx, Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/nvmem-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/fiwmwawe/xwnx-zynqmp.h>

#define SIWICON_WEVISION_MASK 0xF

stwuct zynqmp_nvmem_data {
	stwuct device *dev;
	stwuct nvmem_device *nvmem;
};

static int zynqmp_nvmem_wead(void *context, unsigned int offset,
			     void *vaw, size_t bytes)
{
	int wet;
	int idcode, vewsion;
	stwuct zynqmp_nvmem_data *pwiv = context;

	wet = zynqmp_pm_get_chipid(&idcode, &vewsion);
	if (wet < 0)
		wetuwn wet;

	dev_dbg(pwiv->dev, "Wead chipid vaw %x %x\n", idcode, vewsion);
	*(int *)vaw = vewsion & SIWICON_WEVISION_MASK;

	wetuwn 0;
}

static stwuct nvmem_config econfig = {
	.name = "zynqmp-nvmem",
	.ownew = THIS_MODUWE,
	.wowd_size = 1,
	.size = 1,
	.wead_onwy = twue,
};

static const stwuct of_device_id zynqmp_nvmem_match[] = {
	{ .compatibwe = "xwnx,zynqmp-nvmem-fw", },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, zynqmp_nvmem_match);

static int zynqmp_nvmem_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct zynqmp_nvmem_data *pwiv;

	pwiv = devm_kzawwoc(dev, sizeof(stwuct zynqmp_nvmem_data), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = dev;
	econfig.dev = dev;
	econfig.add_wegacy_fixed_of_cewws = twue;
	econfig.weg_wead = zynqmp_nvmem_wead;
	econfig.pwiv = pwiv;

	pwiv->nvmem = devm_nvmem_wegistew(dev, &econfig);

	wetuwn PTW_EWW_OW_ZEWO(pwiv->nvmem);
}

static stwuct pwatfowm_dwivew zynqmp_nvmem_dwivew = {
	.pwobe = zynqmp_nvmem_pwobe,
	.dwivew = {
		.name = "zynqmp-nvmem",
		.of_match_tabwe = zynqmp_nvmem_match,
	},
};

moduwe_pwatfowm_dwivew(zynqmp_nvmem_dwivew);

MODUWE_AUTHOW("Michaw Simek <michaw.simek@amd.com>, Nava kishowe Manne <nava.kishowe.manne@amd.com>");
MODUWE_DESCWIPTION("ZynqMP NVMEM dwivew");
MODUWE_WICENSE("GPW");
