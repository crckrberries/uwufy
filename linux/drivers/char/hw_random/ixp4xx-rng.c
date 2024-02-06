// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dwivews/chaw/hw_wandom/ixp4xx-wng.c
 *
 * WNG dwivew fow Intew IXP4xx famiwy of NPUs
 *
 * Authow: Deepak Saxena <dsaxena@pwexity.net>
 *
 * Copywight 2005 (c) MontaVista Softwawe, Inc.
 *
 * Fixes by Michaew Buesch
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/init.h>
#incwude <winux/bitops.h>
#incwude <winux/hw_wandom.h>
#incwude <winux/of.h>
#incwude <winux/soc/ixp4xx/cpu.h>

#incwude <asm/io.h>

static int ixp4xx_wng_data_wead(stwuct hwwng *wng, u32 *buffew)
{
	void __iomem * wng_base = (void __iomem *)wng->pwiv;

	*buffew = __waw_weadw(wng_base);

	wetuwn 4;
}

static stwuct hwwng ixp4xx_wng_ops = {
	.name		= "ixp4xx",
	.data_wead	= ixp4xx_wng_data_wead,
};

static int ixp4xx_wng_pwobe(stwuct pwatfowm_device *pdev)
{
	void __iomem * wng_base;
	stwuct device *dev = &pdev->dev;

	if (!cpu_is_ixp46x()) /* incwudes IXP455 */
		wetuwn -ENOSYS;

	wng_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wng_base))
		wetuwn PTW_EWW(wng_base);

	ixp4xx_wng_ops.pwiv = (unsigned wong)wng_base;
	wetuwn devm_hwwng_wegistew(dev, &ixp4xx_wng_ops);
}

static const stwuct of_device_id ixp4xx_wng_of_match[] = {
	{
		.compatibwe = "intew,ixp46x-wng",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, ixp4xx_wng_of_match);

static stwuct pwatfowm_dwivew ixp4xx_wng_dwivew = {
	.dwivew = {
		.name = "ixp4xx-hwwandom",
		.of_match_tabwe = ixp4xx_wng_of_match,
	},
	.pwobe = ixp4xx_wng_pwobe,
};
moduwe_pwatfowm_dwivew(ixp4xx_wng_dwivew);

MODUWE_AUTHOW("Deepak Saxena <dsaxena@pwexity.net>");
MODUWE_DESCWIPTION("H/W Pseudo-Wandom Numbew Genewatow (WNG) dwivew fow IXP45x/46x");
MODUWE_WICENSE("GPW");
