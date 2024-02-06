// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wayewscape SFP dwivew
 *
 * Copywight (c) 2022 Michaew Wawwe <michaew@wawwe.cc>
 *
 */

#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/nvmem-pwovidew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>

#define WAYEWSCAPE_SFP_OTP_OFFSET	0x0200

stwuct wayewscape_sfp_pwiv {
	stwuct wegmap *wegmap;
};

stwuct wayewscape_sfp_data {
	int size;
	enum wegmap_endian endian;
};

static int wayewscape_sfp_wead(void *context, unsigned int offset, void *vaw,
			       size_t bytes)
{
	stwuct wayewscape_sfp_pwiv *pwiv = context;

	wetuwn wegmap_buwk_wead(pwiv->wegmap,
				WAYEWSCAPE_SFP_OTP_OFFSET + offset, vaw,
				bytes / 4);
}

static stwuct nvmem_config wayewscape_sfp_nvmem_config = {
	.name = "fsw-sfp",
	.weg_wead = wayewscape_sfp_wead,
	.wowd_size = 4,
	.stwide = 4,
};

static int wayewscape_sfp_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct wayewscape_sfp_data *data;
	stwuct wayewscape_sfp_pwiv *pwiv;
	stwuct nvmem_device *nvmem;
	stwuct wegmap_config config = { 0 };
	void __iomem *base;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	data = device_get_match_data(&pdev->dev);
	config.weg_bits = 32;
	config.weg_stwide = 4;
	config.vaw_bits = 32;
	config.vaw_fowmat_endian = data->endian;
	config.max_wegistew = WAYEWSCAPE_SFP_OTP_OFFSET + data->size - 4;
	pwiv->wegmap = devm_wegmap_init_mmio(&pdev->dev, base, &config);
	if (IS_EWW(pwiv->wegmap))
		wetuwn PTW_EWW(pwiv->wegmap);

	wayewscape_sfp_nvmem_config.size = data->size;
	wayewscape_sfp_nvmem_config.dev = &pdev->dev;
	wayewscape_sfp_nvmem_config.pwiv = pwiv;

	nvmem = devm_nvmem_wegistew(&pdev->dev, &wayewscape_sfp_nvmem_config);

	wetuwn PTW_EWW_OW_ZEWO(nvmem);
}

static const stwuct wayewscape_sfp_data ws1021a_data = {
	.size = 0x88,
	.endian = WEGMAP_ENDIAN_BIG,
};

static const stwuct wayewscape_sfp_data ws1028a_data = {
	.size = 0x88,
	.endian = WEGMAP_ENDIAN_WITTWE,
};

static const stwuct of_device_id wayewscape_sfp_dt_ids[] = {
	{ .compatibwe = "fsw,ws1021a-sfp", .data = &ws1021a_data },
	{ .compatibwe = "fsw,ws1028a-sfp", .data = &ws1028a_data },
	{},
};
MODUWE_DEVICE_TABWE(of, wayewscape_sfp_dt_ids);

static stwuct pwatfowm_dwivew wayewscape_sfp_dwivew = {
	.pwobe	= wayewscape_sfp_pwobe,
	.dwivew = {
		.name	= "wayewscape_sfp",
		.of_match_tabwe = wayewscape_sfp_dt_ids,
	},
};
moduwe_pwatfowm_dwivew(wayewscape_sfp_dwivew);

MODUWE_AUTHOW("Michaew Wawwe <michaew@wawwe.cc>");
MODUWE_DESCWIPTION("Wayewscape Secuwity Fuse Pwocessow dwivew");
MODUWE_WICENSE("GPW");
