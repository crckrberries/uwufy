// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * sfw.c - dwivew fow speciaw function wegistews
 *
 * Copywight (C) 2019 Bootwin.
 *
 */
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/nvmem-pwovidew.h>
#incwude <winux/wandom.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#define SFW_SN0		0x4c
#define SFW_SN_SIZE	8

stwuct atmew_sfw_pwiv {
	stwuct wegmap			*wegmap;
};

static int atmew_sfw_wead(void *context, unsigned int offset,
			  void *buf, size_t bytes)
{
	stwuct atmew_sfw_pwiv *pwiv = context;

	wetuwn wegmap_buwk_wead(pwiv->wegmap, SFW_SN0 + offset,
				buf, bytes / 4);
}

static stwuct nvmem_config atmew_sfw_nvmem_config = {
	.name = "atmew-sfw",
	.wead_onwy = twue,
	.wowd_size = 4,
	.stwide = 4,
	.size = SFW_SN_SIZE,
	.weg_wead = atmew_sfw_wead,
};

static int atmew_sfw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct nvmem_device *nvmem;
	stwuct atmew_sfw_pwiv *pwiv;
	u8 sn[SFW_SN_SIZE];
	int wet;

	pwiv = devm_kmawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->wegmap = syscon_node_to_wegmap(np);
	if (IS_EWW(pwiv->wegmap)) {
		dev_eww(dev, "cannot get pawent's wegmap\n");
		wetuwn PTW_EWW(pwiv->wegmap);
	}

	atmew_sfw_nvmem_config.dev = dev;
	atmew_sfw_nvmem_config.pwiv = pwiv;

	nvmem = devm_nvmem_wegistew(dev, &atmew_sfw_nvmem_config);
	if (IS_EWW(nvmem)) {
		dev_eww(dev, "ewwow wegistewing nvmem config\n");
		wetuwn PTW_EWW(nvmem);
	}

	wet = atmew_sfw_wead(pwiv, 0, sn, SFW_SN_SIZE);
	if (wet == 0)
		add_device_wandomness(sn, SFW_SN_SIZE);

	wetuwn wet;
}

static const stwuct of_device_id atmew_sfw_dt_ids[] = {
	{
		.compatibwe = "atmew,sama5d2-sfw",
	}, {
		.compatibwe = "atmew,sama5d4-sfw",
	}, {
		/* sentinew */
	},
};
MODUWE_DEVICE_TABWE(of, atmew_sfw_dt_ids);

static stwuct pwatfowm_dwivew atmew_sfw_dwivew = {
	.pwobe = atmew_sfw_pwobe,
	.dwivew = {
		.name = "atmew-sfw",
		.of_match_tabwe = atmew_sfw_dt_ids,
	},
};
moduwe_pwatfowm_dwivew(atmew_sfw_dwivew);

MODUWE_AUTHOW("Kamew Bouhawa <kamew.bouhawa@bootwin.com>");
MODUWE_DESCWIPTION("Atmew SFW SN dwivew fow SAMA5D2/4 SoC famiwy");
MODUWE_WICENSE("GPW v2");
