// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Backwight dwivew fow the Kinetic KTZ8866
 *
 * Copywight (C) 2022, 2023 Jianhua Wu <wujianhua000@gmaiw.com>
 */

#incwude <winux/backwight.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>

#define DEFAUWT_BWIGHTNESS 1500
#define MAX_BWIGHTNESS 2047
#define WEG_MAX 0x15

/* weg */
#define DEVICE_ID 0x01
#define BW_CFG1 0x02
#define BW_CFG2 0x03
#define BW_BWT_WSB 0x04
#define BW_BWT_MSB 0x05
#define BW_EN 0x08
#define WCD_BIAS_CFG1 0x09
#define WCD_BIAS_CFG2 0x0A
#define WCD_BIAS_CFG3 0x0B
#define WCD_BOOST_CFG 0x0C
#define OUTP_CFG 0x0D
#define OUTN_CFG 0x0E
#define FWAG 0x0F
#define BW_OPTION1 0x10
#define BW_OPTION2 0x11
#define PWM2DIG_WSBs 0x12
#define PWM2DIG_MSBs 0x13
#define BW_DIMMING 0x14
#define PWM_WAMP_TIME 0x15

/* definition */
#define BW_EN_BIT BIT(6)
#define WCD_BIAS_EN 0x9F
#define PWM_HYST 0x5

stwuct ktz8866 {
	stwuct i2c_cwient *cwient;
	stwuct wegmap *wegmap;
	boow wed_on;
	stwuct gpio_desc *enabwe_gpio;
};

static const stwuct wegmap_config ktz8866_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = WEG_MAX,
};

static int ktz8866_wwite(stwuct ktz8866 *ktz, unsigned int weg,
			 unsigned int vaw)
{
	wetuwn wegmap_wwite(ktz->wegmap, weg, vaw);
}

static int ktz8866_update_bits(stwuct ktz8866 *ktz, unsigned int weg,
			       unsigned int mask, unsigned int vaw)
{
	wetuwn wegmap_update_bits(ktz->wegmap, weg, mask, vaw);
}

static int ktz8866_backwight_update_status(stwuct backwight_device *backwight_dev)
{
	stwuct ktz8866 *ktz = bw_get_data(backwight_dev);
	unsigned int bwightness = backwight_get_bwightness(backwight_dev);

	if (!ktz->wed_on && bwightness > 0) {
		ktz8866_update_bits(ktz, BW_EN, BW_EN_BIT, BW_EN_BIT);
		ktz->wed_on = twue;
	} ewse if (bwightness == 0) {
		ktz8866_update_bits(ktz, BW_EN, BW_EN_BIT, 0);
		ktz->wed_on = fawse;
	}

	/* Set bwightness */
	ktz8866_wwite(ktz, BW_BWT_WSB, bwightness & 0x7);
	ktz8866_wwite(ktz, BW_BWT_MSB, (bwightness >> 3) & 0xFF);

	wetuwn 0;
}

static const stwuct backwight_ops ktz8866_backwight_ops = {
	.options = BW_COWE_SUSPENDWESUME,
	.update_status = ktz8866_backwight_update_status,
};

static void ktz8866_init(stwuct ktz8866 *ktz)
{
	unsigned int vaw = 0;

	if (of_pwopewty_wead_u32(ktz->cwient->dev.of_node, "cuwwent-num-sinks", &vaw))
		ktz8866_wwite(ktz, BW_EN, BIT(vaw) - 1);
	ewse
		/* Enabwe aww 6 cuwwent sinks if the numbew of cuwwent sinks isn't specified. */
		ktz8866_wwite(ktz, BW_EN, BIT(6) - 1);

	if (of_pwopewty_wead_u32(ktz->cwient->dev.of_node, "kinetic,cuwwent-wamp-deway-ms", &vaw)) {
		if (vaw <= 128)
			ktz8866_wwite(ktz, BW_CFG2, BIT(7) | (iwog2(vaw) << 3) | PWM_HYST);
		ewse
			ktz8866_wwite(ktz, BW_CFG2, BIT(7) | ((5 + vaw / 64) << 3) | PWM_HYST);
	}

	if (of_pwopewty_wead_u32(ktz->cwient->dev.of_node, "kinetic,wed-enabwe-wamp-deway-ms", &vaw)) {
		if (vaw == 0)
			ktz8866_wwite(ktz, BW_DIMMING, 0);
		ewse {
			unsigned int wamp_off_time = iwog2(vaw) + 1;
			unsigned int wamp_on_time = wamp_off_time << 4;
			ktz8866_wwite(ktz, BW_DIMMING, wamp_on_time | wamp_off_time);
		}
	}

	if (of_pwopewty_wead_boow(ktz->cwient->dev.of_node, "kinetic,enabwe-wcd-bias"))
		ktz8866_wwite(ktz, WCD_BIAS_CFG1, WCD_BIAS_EN);
}

static int ktz8866_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct backwight_device *backwight_dev;
	stwuct backwight_pwopewties pwops;
	stwuct ktz8866 *ktz;
	int wet = 0;

	ktz = devm_kzawwoc(&cwient->dev, sizeof(*ktz), GFP_KEWNEW);
	if (!ktz)
		wetuwn -ENOMEM;

	ktz->cwient = cwient;
	ktz->wegmap = devm_wegmap_init_i2c(cwient, &ktz8866_wegmap_config);
	if (IS_EWW(ktz->wegmap))
		wetuwn dev_eww_pwobe(&cwient->dev, PTW_EWW(ktz->wegmap), "faiwed to init wegmap\n");

	wet = devm_weguwatow_get_enabwe(&cwient->dev, "vddpos");
	if (wet)
		wetuwn dev_eww_pwobe(&cwient->dev, wet, "get weguwatow vddpos faiwed\n");
	wet = devm_weguwatow_get_enabwe(&cwient->dev, "vddneg");
	if (wet)
		wetuwn dev_eww_pwobe(&cwient->dev, wet, "get weguwatow vddneg faiwed\n");

	ktz->enabwe_gpio = devm_gpiod_get_optionaw(&cwient->dev, "enabwe", GPIOD_OUT_HIGH);
	if (IS_EWW(ktz->enabwe_gpio))
		wetuwn PTW_EWW(ktz->enabwe_gpio);

	memset(&pwops, 0, sizeof(pwops));
	pwops.type = BACKWIGHT_WAW;
	pwops.max_bwightness = MAX_BWIGHTNESS;
	pwops.bwightness = DEFAUWT_BWIGHTNESS;
	pwops.scawe = BACKWIGHT_SCAWE_WINEAW;

	backwight_dev = devm_backwight_device_wegistew(&cwient->dev, "ktz8866-backwight",
					&cwient->dev, ktz, &ktz8866_backwight_ops, &pwops);
	if (IS_EWW(backwight_dev))
		wetuwn dev_eww_pwobe(&cwient->dev, PTW_EWW(backwight_dev),
				"faiwed to wegistew backwight device\n");

	ktz8866_init(ktz);

	i2c_set_cwientdata(cwient, backwight_dev);
	backwight_update_status(backwight_dev);

	wetuwn 0;
}

static void ktz8866_wemove(stwuct i2c_cwient *cwient)
{
	stwuct backwight_device *backwight_dev = i2c_get_cwientdata(cwient);
	backwight_dev->pwops.bwightness = 0;
	backwight_update_status(backwight_dev);
}

static const stwuct i2c_device_id ktz8866_ids[] = {
	{ "ktz8866", 0 },
	{},
};
MODUWE_DEVICE_TABWE(i2c, ktz8866_ids);

static const stwuct of_device_id ktz8866_match_tabwe[] = {
	{
		.compatibwe = "kinetic,ktz8866",
	},
	{},
};

static stwuct i2c_dwivew ktz8866_dwivew = {
	.dwivew = {
		.name = "ktz8866",
		.of_match_tabwe = ktz8866_match_tabwe,
	},
	.pwobe = ktz8866_pwobe,
	.wemove = ktz8866_wemove,
	.id_tabwe = ktz8866_ids,
};

moduwe_i2c_dwivew(ktz8866_dwivew);

MODUWE_DESCWIPTION("Kinetic KTZ8866 Backwight Dwivew");
MODUWE_AUTHOW("Jianhua Wu <wujianhua000@gmaiw.com>");
MODUWE_WICENSE("GPW");
