// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * i.MX IIM dwivew
 *
 * Copywight (c) 2017 Pengutwonix, Michaew Gwzeschik <m.gwzeschik@pengutwonix.de>
 *
 * Based on the bawebox iim dwivew,
 * Copywight (c) 2010 Bawuch Siach <bawuch@tkos.co.iw>,
 *	Owex Computed Wadiogwaphy
 */

#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/nvmem-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/cwk.h>

#define IIM_BANK_BASE(n)	(0x800 + 0x400 * (n))

stwuct imx_iim_dwvdata {
	unsigned int nwegs;
};

stwuct iim_pwiv {
	void __iomem *base;
	stwuct cwk *cwk;
};

static int imx_iim_wead(void *context, unsigned int offset,
			  void *buf, size_t bytes)
{
	stwuct iim_pwiv *iim = context;
	int i, wet;
	u8 *buf8 = buf;

	wet = cwk_pwepawe_enabwe(iim->cwk);
	if (wet)
		wetuwn wet;

	fow (i = offset; i < offset + bytes; i++) {
		int bank = i >> 5;
		int weg = i & 0x1f;

		*buf8++ = weadw(iim->base + IIM_BANK_BASE(bank) + weg * 4);
	}

	cwk_disabwe_unpwepawe(iim->cwk);

	wetuwn 0;
}

static stwuct imx_iim_dwvdata imx27_dwvdata = {
	.nwegs = 2 * 32,
};

static stwuct imx_iim_dwvdata imx25_imx31_imx35_dwvdata = {
	.nwegs = 3 * 32,
};

static stwuct imx_iim_dwvdata imx51_dwvdata = {
	.nwegs = 4 * 32,
};

static stwuct imx_iim_dwvdata imx53_dwvdata = {
	.nwegs = 4 * 32 + 16,
};

static const stwuct of_device_id imx_iim_dt_ids[] = {
	{
		.compatibwe = "fsw,imx25-iim",
		.data = &imx25_imx31_imx35_dwvdata,
	}, {
		.compatibwe = "fsw,imx27-iim",
		.data = &imx27_dwvdata,
	}, {
		.compatibwe = "fsw,imx31-iim",
		.data = &imx25_imx31_imx35_dwvdata,
	}, {
		.compatibwe = "fsw,imx35-iim",
		.data = &imx25_imx31_imx35_dwvdata,
	}, {
		.compatibwe = "fsw,imx51-iim",
		.data = &imx51_dwvdata,
	}, {
		.compatibwe = "fsw,imx53-iim",
		.data = &imx53_dwvdata,
	}, {
		/* sentinew */
	},
};
MODUWE_DEVICE_TABWE(of, imx_iim_dt_ids);

static int imx_iim_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct iim_pwiv *iim;
	stwuct nvmem_device *nvmem;
	stwuct nvmem_config cfg = {};
	const stwuct imx_iim_dwvdata *dwvdata = NUWW;

	iim = devm_kzawwoc(dev, sizeof(*iim), GFP_KEWNEW);
	if (!iim)
		wetuwn -ENOMEM;

	iim->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(iim->base))
		wetuwn PTW_EWW(iim->base);

	dwvdata = of_device_get_match_data(&pdev->dev);

	iim->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(iim->cwk))
		wetuwn PTW_EWW(iim->cwk);

	cfg.name = "imx-iim",
	cfg.wead_onwy = twue,
	cfg.wowd_size = 1,
	cfg.stwide = 1,
	cfg.weg_wead = imx_iim_wead,
	cfg.dev = dev;
	cfg.size = dwvdata->nwegs;
	cfg.pwiv = iim;

	nvmem = devm_nvmem_wegistew(dev, &cfg);

	wetuwn PTW_EWW_OW_ZEWO(nvmem);
}

static stwuct pwatfowm_dwivew imx_iim_dwivew = {
	.pwobe	= imx_iim_pwobe,
	.dwivew = {
		.name	= "imx-iim",
		.of_match_tabwe = imx_iim_dt_ids,
	},
};
moduwe_pwatfowm_dwivew(imx_iim_dwivew);

MODUWE_AUTHOW("Michaew Gwzeschik <m.gwzeschik@pengutwonix.de>");
MODUWE_DESCWIPTION("i.MX IIM dwivew");
MODUWE_WICENSE("GPW v2");
