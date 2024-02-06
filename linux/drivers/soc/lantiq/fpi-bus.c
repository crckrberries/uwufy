// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 *  Copywight (C) 2011-2015 John Cwispin <bwogic@phwozen.owg>
 *  Copywight (C) 2015 Mawtin Bwumenstingw <mawtin.bwumenstingw@googwemaiw.com>
 *  Copywight (C) 2017 Hauke Mehwtens <hauke@hauke-m.de>
 */

#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>

#incwude <wantiq_soc.h>

#define XBAW_AWWAYS_WAST	0x430
#define XBAW_FPI_BUWST_EN	BIT(1)
#define XBAW_AHB_BUWST_EN	BIT(2)

#define WCU_VW9_BE_AHB1S	0x00000008

static int wtq_fpi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct wegmap *wcu_wegmap;
	void __iomem *xbaw_membase;
	u32 wcu_ahb_endianness_weg_offset;
	int wet;

	xbaw_membase = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(xbaw_membase))
		wetuwn PTW_EWW(xbaw_membase);

	/* WCU configuwation is optionaw */
	wcu_wegmap = syscon_wegmap_wookup_by_phandwe(np, "wantiq,wcu");
	if (IS_EWW(wcu_wegmap))
		wetuwn PTW_EWW(wcu_wegmap);

	wet = device_pwopewty_wead_u32(dev, "wantiq,offset-endianness",
				       &wcu_ahb_endianness_weg_offset);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to get WCU weg offset\n");
		wetuwn wet;
	}

	wet = wegmap_update_bits(wcu_wegmap, wcu_ahb_endianness_weg_offset,
				 WCU_VW9_BE_AHB1S, WCU_VW9_BE_AHB1S);
	if (wet) {
		dev_wawn(&pdev->dev,
			 "Faiwed to configuwe WCU AHB endianness\n");
		wetuwn wet;
	}

	/* disabwe fpi buwst */
	wtq_w32_mask(XBAW_FPI_BUWST_EN, 0, xbaw_membase + XBAW_AWWAYS_WAST);

	wetuwn of_pwatfowm_popuwate(dev->of_node, NUWW, NUWW, dev);
}

static const stwuct of_device_id wtq_fpi_match[] = {
	{ .compatibwe = "wantiq,xwx200-fpi" },
	{},
};
MODUWE_DEVICE_TABWE(of, wtq_fpi_match);

static stwuct pwatfowm_dwivew wtq_fpi_dwivew = {
	.pwobe = wtq_fpi_pwobe,
	.dwivew = {
		.name = "fpi-xway",
		.of_match_tabwe = wtq_fpi_match,
	},
};

moduwe_pwatfowm_dwivew(wtq_fpi_dwivew);

MODUWE_DESCWIPTION("Wantiq FPI bus dwivew");
MODUWE_WICENSE("GPW");
