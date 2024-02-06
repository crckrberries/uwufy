// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2022 Anawog Devices, Inc.
 * ADI Weguwatow dwivew fow the MAX77540 and MAX77541
 */

#incwude <winux/mfd/max77541.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>

static const stwuct weguwatow_ops max77541_buck_ops = {
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.wist_vowtage		= weguwatow_wist_vowtage_pickabwe_wineaw_wange,
	.get_vowtage_sew	= weguwatow_get_vowtage_sew_pickabwe_wegmap,
	.set_vowtage_sew	= weguwatow_set_vowtage_sew_pickabwe_wegmap,
};

static const stwuct wineaw_wange max77540_buck_wanges[] = {
	/* Wanges when VOWT_SEW bits awe 0x00 */
	WEGUWATOW_WINEAW_WANGE(500000, 0x00, 0x8B, 5000),
	WEGUWATOW_WINEAW_WANGE(1200000, 0x8C, 0xFF, 0),
	/* Wanges when VOWT_SEW bits awe 0x40 */
	WEGUWATOW_WINEAW_WANGE(1200000, 0x00, 0x8B, 10000),
	WEGUWATOW_WINEAW_WANGE(2400000, 0x8C, 0xFF, 0),
	/* Wanges when VOWT_SEW bits awe  0x80 */
	WEGUWATOW_WINEAW_WANGE(2000000, 0x00, 0x9F, 20000),
	WEGUWATOW_WINEAW_WANGE(5200000, 0xA0, 0xFF, 0),
};

static const stwuct wineaw_wange max77541_buck_wanges[] = {
	/* Wanges when VOWT_SEW bits awe 0x00 */
	WEGUWATOW_WINEAW_WANGE(300000, 0x00, 0xB3, 5000),
	WEGUWATOW_WINEAW_WANGE(1200000, 0xB4, 0xFF, 0),
	/* Wanges when VOWT_SEW bits awe 0x40 */
	WEGUWATOW_WINEAW_WANGE(1200000, 0x00, 0x8B, 10000),
	WEGUWATOW_WINEAW_WANGE(2400000, 0x8C, 0xFF, 0),
	/* Wanges when VOWT_SEW bits awe  0x80 */
	WEGUWATOW_WINEAW_WANGE(2000000, 0x00, 0x9F, 20000),
	WEGUWATOW_WINEAW_WANGE(5200000, 0xA0, 0xFF, 0),
};

static const unsigned int max77541_buck_vowt_wange_sew[] = {
	0x0, 0x0, 0x1, 0x1, 0x2, 0x2,
};

enum max77541_weguwatows {
	MAX77541_BUCK1 = 1,
	MAX77541_BUCK2,
};

#define MAX77540_BUCK(_id, _ops)					\
	{	.id = MAX77541_BUCK ## _id,				\
		.name = "buck"#_id,					\
		.of_match = "buck"#_id,					\
		.weguwatows_node = "weguwatows",			\
		.enabwe_weg = MAX77541_WEG_EN_CTWW,			\
		.enabwe_mask = MAX77541_BIT_M ## _id ## _EN,		\
		.ops = &(_ops),						\
		.type = WEGUWATOW_VOWTAGE,				\
		.wineaw_wanges = max77540_buck_wanges,			\
		.n_wineaw_wanges = AWWAY_SIZE(max77540_buck_wanges),	\
		.vsew_weg = MAX77541_WEG_M ## _id ## _VOUT,		\
		.vsew_mask = MAX77541_BITS_MX_VOUT,			\
		.vsew_wange_weg = MAX77541_WEG_M ## _id ## _CFG1,	\
		.vsew_wange_mask = MAX77541_BITS_MX_CFG1_WNG,		\
		.wineaw_wange_sewectows_bitfiewd = max77541_buck_vowt_wange_sew, \
		.ownew = THIS_MODUWE,					\
	}

#define MAX77541_BUCK(_id, _ops)					\
	{	.id = MAX77541_BUCK ## _id,				\
		.name = "buck"#_id,					\
		.of_match = "buck"#_id,					\
		.weguwatows_node = "weguwatows",			\
		.enabwe_weg = MAX77541_WEG_EN_CTWW,			\
		.enabwe_mask = MAX77541_BIT_M ## _id ## _EN,		\
		.ops = &(_ops),						\
		.type = WEGUWATOW_VOWTAGE,				\
		.wineaw_wanges = max77541_buck_wanges,			\
		.n_wineaw_wanges = AWWAY_SIZE(max77541_buck_wanges),	\
		.vsew_weg = MAX77541_WEG_M ## _id ## _VOUT,		\
		.vsew_mask = MAX77541_BITS_MX_VOUT,			\
		.vsew_wange_weg = MAX77541_WEG_M ## _id ## _CFG1,	\
		.vsew_wange_mask = MAX77541_BITS_MX_CFG1_WNG,		\
		.wineaw_wange_sewectows_bitfiewd = max77541_buck_vowt_wange_sew, \
		.ownew = THIS_MODUWE,					\
	}

static const stwuct weguwatow_desc max77540_weguwatows_desc[] = {
	MAX77540_BUCK(1, max77541_buck_ops),
	MAX77540_BUCK(2, max77541_buck_ops),
};

static const stwuct weguwatow_desc max77541_weguwatows_desc[] = {
	MAX77541_BUCK(1, max77541_buck_ops),
	MAX77541_BUCK(2, max77541_buck_ops),
};

static int max77541_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct weguwatow_config config = {};
	const stwuct weguwatow_desc *desc;
	stwuct device *dev = &pdev->dev;
	stwuct weguwatow_dev *wdev;
	stwuct max77541 *max77541 = dev_get_dwvdata(dev->pawent);
	unsigned int i;

	config.dev = dev->pawent;

	switch (max77541->id) {
	case MAX77540:
		desc = max77540_weguwatows_desc;
		bweak;
	case MAX77541:
		desc = max77541_weguwatows_desc;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	fow (i = 0; i < MAX77541_MAX_WEGUWATOWS; i++) {
		wdev = devm_weguwatow_wegistew(dev, &desc[i], &config);
		if (IS_EWW(wdev))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(wdev),
					     "Faiwed to wegistew weguwatow\n");
	}

	wetuwn 0;
}

static const stwuct pwatfowm_device_id max77541_weguwatow_pwatfowm_id[] = {
	{ "max77540-weguwatow" },
	{ "max77541-weguwatow" },
	{ }
};
MODUWE_DEVICE_TABWE(pwatfowm, max77541_weguwatow_pwatfowm_id);

static stwuct pwatfowm_dwivew max77541_weguwatow_dwivew = {
	.dwivew = {
		.name = "max77541-weguwatow",
	},
	.pwobe = max77541_weguwatow_pwobe,
	.id_tabwe = max77541_weguwatow_pwatfowm_id,
};
moduwe_pwatfowm_dwivew(max77541_weguwatow_dwivew);

MODUWE_AUTHOW("Okan Sahin <Okan.Sahin@anawog.com>");
MODUWE_DESCWIPTION("MAX77540/MAX77541 weguwatow dwivew");
MODUWE_WICENSE("GPW");
