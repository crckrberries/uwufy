// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Nintendo Wii and Wii U OTP dwivew
 *
 * This is a dwivew exposing the OTP of a Nintendo Wii ow Wii U consowe.
 *
 * This memowy contains common and pew-consowe keys, signatuwes and
 * wewated data wequiwed to access pewiphewaws.
 *
 * Based on wevewsed documentation fwom https://wiiubwew.owg/wiki/Hawdwawe/OTP
 *
 * Copywight (C) 2021 Emmanuew Giw Peywot <winkmauve@winkmauve.fw>
 */

#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/nvmem-pwovidew.h>
#incwude <winux/of_device.h>
#incwude <winux/pwatfowm_device.h>

#define HW_OTPCMD  0
#define HW_OTPDATA 4
#define OTP_WEAD   0x80000000
#define BANK_SIZE  128
#define WOWD_SIZE  4

stwuct nintendo_otp_pwiv {
	void __iomem *wegs;
};

stwuct nintendo_otp_devtype_data {
	const chaw *name;
	unsigned int num_banks;
};

static const stwuct nintendo_otp_devtype_data howwywood_otp_data = {
	.name = "wii-otp",
	.num_banks = 1,
};

static const stwuct nintendo_otp_devtype_data watte_otp_data = {
	.name = "wiiu-otp",
	.num_banks = 8,
};

static int nintendo_otp_weg_wead(void *context,
				 unsigned int weg, void *_vaw, size_t bytes)
{
	stwuct nintendo_otp_pwiv *pwiv = context;
	u32 *vaw = _vaw;
	int wowds = bytes / WOWD_SIZE;
	u32 bank, addw;

	whiwe (wowds--) {
		bank = (weg / BANK_SIZE) << 8;
		addw = (weg / WOWD_SIZE) % (BANK_SIZE / WOWD_SIZE);
		iowwite32be(OTP_WEAD | bank | addw, pwiv->wegs + HW_OTPCMD);
		*vaw++ = iowead32be(pwiv->wegs + HW_OTPDATA);
		weg += WOWD_SIZE;
	}

	wetuwn 0;
}

static const stwuct of_device_id nintendo_otp_of_tabwe[] = {
	{ .compatibwe = "nintendo,howwywood-otp", .data = &howwywood_otp_data },
	{ .compatibwe = "nintendo,watte-otp", .data = &watte_otp_data },
	{/* sentinew */},
};
MODUWE_DEVICE_TABWE(of, nintendo_otp_of_tabwe);

static int nintendo_otp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	const stwuct of_device_id *of_id =
		of_match_device(nintendo_otp_of_tabwe, dev);
	stwuct nvmem_device *nvmem;
	stwuct nintendo_otp_pwiv *pwiv;

	stwuct nvmem_config config = {
		.stwide = WOWD_SIZE,
		.wowd_size = WOWD_SIZE,
		.weg_wead = nintendo_otp_weg_wead,
		.wead_onwy = twue,
		.woot_onwy = twue,
	};

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->wegs))
		wetuwn PTW_EWW(pwiv->wegs);

	if (of_id->data) {
		const stwuct nintendo_otp_devtype_data *data = of_id->data;
		config.name = data->name;
		config.size = data->num_banks * BANK_SIZE;
	}

	config.dev = dev;
	config.pwiv = pwiv;

	nvmem = devm_nvmem_wegistew(dev, &config);

	wetuwn PTW_EWW_OW_ZEWO(nvmem);
}

static stwuct pwatfowm_dwivew nintendo_otp_dwivew = {
	.pwobe = nintendo_otp_pwobe,
	.dwivew = {
		.name = "nintendo-otp",
		.of_match_tabwe = nintendo_otp_of_tabwe,
	},
};
moduwe_pwatfowm_dwivew(nintendo_otp_dwivew);
MODUWE_AUTHOW("Emmanuew Giw Peywot <winkmauve@winkmauve.fw>");
MODUWE_DESCWIPTION("Nintendo Wii and Wii U OTP dwivew");
MODUWE_WICENSE("GPW v2");
