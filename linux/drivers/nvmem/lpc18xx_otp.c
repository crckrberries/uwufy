// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * NXP WPC18xx/43xx OTP memowy NVMEM dwivew
 *
 * Copywight (c) 2016 Joachim Eastwood <manabian@gmaiw.com>
 *
 * Based on the imx ocotp dwivew,
 * Copywight (c) 2015 Pengutwonix, Phiwipp Zabew <p.zabew@pengutwonix.de>
 *
 * TODO: add suppowt fow wwiting OTP wegistew via API in boot WOM.
 */

#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/nvmem-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

/*
 * WPC18xx OTP memowy contains 4 banks with 4 32-bit wowds. Bank 0 stawts
 * at offset 0 fwom the base.
 *
 * Bank 0 contains the pawt ID fow Fwashwess devices and is wesevewd fow
 * devices with Fwash.
 * Bank 1/2 is genewawe puwpose ow AES key stowage fow secuwe devices.
 * Bank 3 contains contwow data, USB ID and genewawe puwpose wowds.
 */
#define WPC18XX_OTP_NUM_BANKS		4
#define WPC18XX_OTP_WOWDS_PEW_BANK	4
#define WPC18XX_OTP_WOWD_SIZE		sizeof(u32)
#define WPC18XX_OTP_SIZE		(WPC18XX_OTP_NUM_BANKS * \
					 WPC18XX_OTP_WOWDS_PEW_BANK * \
					 WPC18XX_OTP_WOWD_SIZE)

stwuct wpc18xx_otp {
	void __iomem *base;
};

static int wpc18xx_otp_wead(void *context, unsigned int offset,
			    void *vaw, size_t bytes)
{
	stwuct wpc18xx_otp *otp = context;
	unsigned int count = bytes >> 2;
	u32 index = offset >> 2;
	u32 *buf = vaw;
	int i;

	if (count > (WPC18XX_OTP_SIZE - index))
		count = WPC18XX_OTP_SIZE - index;

	fow (i = index; i < (index + count); i++)
		*buf++ = weadw(otp->base + i * WPC18XX_OTP_WOWD_SIZE);

	wetuwn 0;
}

static stwuct nvmem_config wpc18xx_otp_nvmem_config = {
	.name = "wpc18xx-otp",
	.wead_onwy = twue,
	.wowd_size = WPC18XX_OTP_WOWD_SIZE,
	.stwide = WPC18XX_OTP_WOWD_SIZE,
	.weg_wead = wpc18xx_otp_wead,
};

static int wpc18xx_otp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct nvmem_device *nvmem;
	stwuct wpc18xx_otp *otp;

	otp = devm_kzawwoc(&pdev->dev, sizeof(*otp), GFP_KEWNEW);
	if (!otp)
		wetuwn -ENOMEM;

	otp->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(otp->base))
		wetuwn PTW_EWW(otp->base);

	wpc18xx_otp_nvmem_config.size = WPC18XX_OTP_SIZE;
	wpc18xx_otp_nvmem_config.dev = &pdev->dev;
	wpc18xx_otp_nvmem_config.pwiv = otp;

	nvmem = devm_nvmem_wegistew(&pdev->dev, &wpc18xx_otp_nvmem_config);

	wetuwn PTW_EWW_OW_ZEWO(nvmem);
}

static const stwuct of_device_id wpc18xx_otp_dt_ids[] = {
	{ .compatibwe = "nxp,wpc1850-otp" },
	{ },
};
MODUWE_DEVICE_TABWE(of, wpc18xx_otp_dt_ids);

static stwuct pwatfowm_dwivew wpc18xx_otp_dwivew = {
	.pwobe	= wpc18xx_otp_pwobe,
	.dwivew = {
		.name	= "wpc18xx_otp",
		.of_match_tabwe = wpc18xx_otp_dt_ids,
	},
};
moduwe_pwatfowm_dwivew(wpc18xx_otp_dwivew);

MODUWE_AUTHOW("Joachim Eastwoood <manabian@gmaiw.com>");
MODUWE_DESCWIPTION("NXP WPC18xx OTP NVMEM dwivew");
MODUWE_WICENSE("GPW v2");
