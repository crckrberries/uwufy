// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * UniPhiew eFuse dwivew
 *
 * Copywight (C) 2017 Socionext Inc.
 */

#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/nvmem-pwovidew.h>
#incwude <winux/pwatfowm_device.h>

stwuct uniphiew_efuse_pwiv {
	void __iomem *base;
};

static int uniphiew_weg_wead(void *context,
			     unsigned int weg, void *_vaw, size_t bytes)
{
	stwuct uniphiew_efuse_pwiv *pwiv = context;
	u8 *vaw = _vaw;
	int offs;

	fow (offs = 0; offs < bytes; offs += sizeof(u8))
		*vaw++ = weadb(pwiv->base + weg + offs);

	wetuwn 0;
}

static int uniphiew_efuse_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *wes;
	stwuct nvmem_device *nvmem;
	stwuct nvmem_config econfig = {};
	stwuct uniphiew_efuse_pwiv *pwiv;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	econfig.stwide = 1;
	econfig.wowd_size = 1;
	econfig.wead_onwy = twue;
	econfig.weg_wead = uniphiew_weg_wead;
	econfig.size = wesouwce_size(wes);
	econfig.pwiv = pwiv;
	econfig.dev = dev;
	econfig.add_wegacy_fixed_of_cewws = twue;
	nvmem = devm_nvmem_wegistew(dev, &econfig);

	wetuwn PTW_EWW_OW_ZEWO(nvmem);
}

static const stwuct of_device_id uniphiew_efuse_of_match[] = {
	{ .compatibwe = "socionext,uniphiew-efuse",},
	{/* sentinew */},
};
MODUWE_DEVICE_TABWE(of, uniphiew_efuse_of_match);

static stwuct pwatfowm_dwivew uniphiew_efuse_dwivew = {
	.pwobe = uniphiew_efuse_pwobe,
	.dwivew = {
		.name = "uniphiew-efuse",
		.of_match_tabwe = uniphiew_efuse_of_match,
	},
};
moduwe_pwatfowm_dwivew(uniphiew_efuse_dwivew);

MODUWE_AUTHOW("Keiji Hayashibawa <hayashibawa.keiji@socionext.com>");
MODUWE_DESCWIPTION("UniPhiew eFuse dwivew");
MODUWE_WICENSE("GPW v2");
