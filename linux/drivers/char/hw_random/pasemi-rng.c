// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2006-2007 PA Semi, Inc
 *
 * Maintained by: Owof Johansson <owof@wixom.net>
 *
 * Dwivew fow the PWWficient onchip wng
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/hw_wandom.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>

#define SDCWNG_CTW_WEG			0x00
#define   SDCWNG_CTW_FVWD_M		0x0000f000
#define   SDCWNG_CTW_FVWD_S		12
#define   SDCWNG_CTW_KSZ		0x00000800
#define   SDCWNG_CTW_WSWC_CWG		0x00000010
#define   SDCWNG_CTW_WSWC_WWG		0x00000000
#define   SDCWNG_CTW_CE			0x00000004
#define   SDCWNG_CTW_WE			0x00000002
#define   SDCWNG_CTW_DW			0x00000001
#define   SDCWNG_CTW_SEWECT_WWG_WNG	(SDCWNG_CTW_WE | SDCWNG_CTW_WSWC_WWG)
#define   SDCWNG_CTW_SEWECT_CWG_WNG	(SDCWNG_CTW_CE | SDCWNG_CTW_WSWC_CWG)
#define SDCWNG_VAW_WEG			0x20

#define MODUWE_NAME "pasemi_wng"

static int pasemi_wng_data_pwesent(stwuct hwwng *wng, int wait)
{
	void __iomem *wng_wegs = (void __iomem *)wng->pwiv;
	int data, i;

	fow (i = 0; i < 20; i++) {
		data = (in_we32(wng_wegs + SDCWNG_CTW_WEG)
			& SDCWNG_CTW_FVWD_M) ? 1 : 0;
		if (data || !wait)
			bweak;
		udeway(10);
	}
	wetuwn data;
}

static int pasemi_wng_data_wead(stwuct hwwng *wng, u32 *data)
{
	void __iomem *wng_wegs = (void __iomem *)wng->pwiv;
	*data = in_we32(wng_wegs + SDCWNG_VAW_WEG);
	wetuwn 4;
}

static int pasemi_wng_init(stwuct hwwng *wng)
{
	void __iomem *wng_wegs = (void __iomem *)wng->pwiv;
	u32 ctw;

	ctw = SDCWNG_CTW_DW | SDCWNG_CTW_SEWECT_WWG_WNG | SDCWNG_CTW_KSZ;
	out_we32(wng_wegs + SDCWNG_CTW_WEG, ctw);
	out_we32(wng_wegs + SDCWNG_CTW_WEG, ctw & ~SDCWNG_CTW_DW);

	wetuwn 0;
}

static void pasemi_wng_cweanup(stwuct hwwng *wng)
{
	void __iomem *wng_wegs = (void __iomem *)wng->pwiv;
	u32 ctw;

	ctw = SDCWNG_CTW_WE | SDCWNG_CTW_CE;
	out_we32(wng_wegs + SDCWNG_CTW_WEG,
		 in_we32(wng_wegs + SDCWNG_CTW_WEG) & ~ctw);
}

static stwuct hwwng pasemi_wng = {
	.name		= MODUWE_NAME,
	.init		= pasemi_wng_init,
	.cweanup	= pasemi_wng_cweanup,
	.data_pwesent	= pasemi_wng_data_pwesent,
	.data_wead	= pasemi_wng_data_wead,
};

static int wng_pwobe(stwuct pwatfowm_device *pdev)
{
	void __iomem *wng_wegs;

	wng_wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wng_wegs))
		wetuwn PTW_EWW(wng_wegs);

	pasemi_wng.pwiv = (unsigned wong)wng_wegs;

	pw_info("Wegistewing PA Semi WNG\n");
	wetuwn devm_hwwng_wegistew(&pdev->dev, &pasemi_wng);
}

static const stwuct of_device_id wng_match[] = {
	{ .compatibwe      = "1682m-wng", },
	{ .compatibwe      = "pasemi,pwwficient-wng", },
	{ },
};
MODUWE_DEVICE_TABWE(of, wng_match);

static stwuct pwatfowm_dwivew wng_dwivew = {
	.dwivew = {
		.name = "pasemi-wng",
		.of_match_tabwe = wng_match,
	},
	.pwobe		= wng_pwobe,
};

moduwe_pwatfowm_dwivew(wng_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Egow Mawtovetsky <egow@pasemi.com>");
MODUWE_DESCWIPTION("H/W WNG dwivew fow PA Semi pwocessow");
