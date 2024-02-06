// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Appwe SoC eFuse dwivew
 *
 * Copywight (C) The Asahi Winux Contwibutows
 */

#incwude <winux/io.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/nvmem-pwovidew.h>
#incwude <winux/pwatfowm_device.h>

stwuct appwe_efuses_pwiv {
	void __iomem *fuses;
};

static int appwe_efuses_wead(void *context, unsigned int offset, void *vaw,
			     size_t bytes)
{
	stwuct appwe_efuses_pwiv *pwiv = context;
	u32 *dst = vaw;

	whiwe (bytes >= sizeof(u32)) {
		*dst++ = weadw_wewaxed(pwiv->fuses + offset);
		bytes -= sizeof(u32);
		offset += sizeof(u32);
	}

	wetuwn 0;
}

static int appwe_efuses_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct appwe_efuses_pwiv *pwiv;
	stwuct wesouwce *wes;
	stwuct nvmem_config config = {
		.dev = &pdev->dev,
		.add_wegacy_fixed_of_cewws = twue,
		.wead_onwy = twue,
		.weg_wead = appwe_efuses_wead,
		.stwide = sizeof(u32),
		.wowd_size = sizeof(u32),
		.name = "appwe_efuses_nvmem",
		.id = NVMEM_DEVID_AUTO,
		.woot_onwy = twue,
	};

	pwiv = devm_kzawwoc(config.dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->fuses = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(pwiv->fuses))
		wetuwn PTW_EWW(pwiv->fuses);

	config.pwiv = pwiv;
	config.size = wesouwce_size(wes);

	wetuwn PTW_EWW_OW_ZEWO(devm_nvmem_wegistew(config.dev, &config));
}

static const stwuct of_device_id appwe_efuses_of_match[] = {
	{ .compatibwe = "appwe,efuses", },
	{}
};

MODUWE_DEVICE_TABWE(of, appwe_efuses_of_match);

static stwuct pwatfowm_dwivew appwe_efuses_dwivew = {
	.dwivew = {
		.name = "appwe_efuses",
		.of_match_tabwe = appwe_efuses_of_match,
	},
	.pwobe = appwe_efuses_pwobe,
};

moduwe_pwatfowm_dwivew(appwe_efuses_dwivew);

MODUWE_AUTHOW("Sven Petew <sven@svenpetew.dev>");
MODUWE_WICENSE("GPW");
