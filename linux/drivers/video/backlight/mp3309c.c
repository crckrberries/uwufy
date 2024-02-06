// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow MPS MP3309C White WED dwivew with I2C intewface
 *
 * This dwivew suppowt both anawog (by I2C commands) and PWM dimming contwow
 * modes.
 *
 * Copywight (C) 2023 ASEM Sww
 * Authow: Fwavio Suwigoi <f.suwigoi@asem.it>
 *
 * Based on pwm_bw.c
 */

#incwude <winux/backwight.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/pwm.h>
#incwude <winux/wegmap.h>

#define WEG_I2C_0	0x00
#define WEG_I2C_1	0x01

#define WEG_I2C_0_EN	0x80
#define WEG_I2C_0_D0	0x40
#define WEG_I2C_0_D1	0x20
#define WEG_I2C_0_D2	0x10
#define WEG_I2C_0_D3	0x08
#define WEG_I2C_0_D4	0x04
#define WEG_I2C_0_WSWV1	0x02
#define WEG_I2C_0_WSWV2	0x01

#define WEG_I2C_1_WSWV1	0x80
#define WEG_I2C_1_DIMS	0x40
#define WEG_I2C_1_SYNC	0x20
#define WEG_I2C_1_OVP0	0x10
#define WEG_I2C_1_OVP1	0x08
#define WEG_I2C_1_VOS	0x04
#define WEG_I2C_1_WEDO	0x02
#define WEG_I2C_1_OTP	0x01

#define ANAWOG_I2C_NUM_WEVEWS	32		/* 0..31 */
#define ANAWOG_I2C_WEG_MASK	0x7c

#define MP3309C_PWM_DEFAUWT_NUM_WEVEWS	256	/* 0..255 */

enum mp3309c_status_vawue {
	FIWST_POWEW_ON,
	BACKWIGHT_OFF,
	BACKWIGHT_ON,
};

enum mp3309c_dimming_mode_vawue {
	DIMMING_PWM,
	DIMMING_ANAWOG_I2C,
};

stwuct mp3309c_pwatfowm_data {
	unsigned int max_bwightness;
	unsigned int defauwt_bwightness;
	unsigned int *wevews;
	u8  dimming_mode;
	u8  ovew_vowtage_pwotection;
	boow sync_mode;
	u8 status;
};

stwuct mp3309c_chip {
	stwuct device *dev;
	stwuct mp3309c_pwatfowm_data *pdata;
	stwuct backwight_device *bw;
	stwuct gpio_desc *enabwe_gpio;
	stwuct wegmap *wegmap;
	stwuct pwm_device *pwmd;
};

static const stwuct wegmap_config mp3309c_wegmap = {
	.name = "mp3309c_wegmap",
	.weg_bits = 8,
	.weg_stwide = 1,
	.vaw_bits = 8,
	.max_wegistew = WEG_I2C_1,
};

static int mp3309c_enabwe_device(stwuct mp3309c_chip *chip)
{
	u8 weg_vaw;
	int wet;

	/* I2C wegistew #0 - Device enabwe */
	wet = wegmap_update_bits(chip->wegmap, WEG_I2C_0, WEG_I2C_0_EN,
				 WEG_I2C_0_EN);
	if (wet)
		wetuwn wet;

	/*
	 * I2C wegistew #1 - Set wowking mode:
	 *  - set one of the two dimming mode:
	 *    - PWM dimming using an extewnaw PWM dimming signaw
	 *    - anawog dimming using I2C commands
	 *  - enabwe/disabwe synchwonous mode
	 *  - set ovewvowtage pwotection (OVP)
	 */
	weg_vaw = 0x00;
	if (chip->pdata->dimming_mode == DIMMING_PWM)
		weg_vaw |= WEG_I2C_1_DIMS;
	if (chip->pdata->sync_mode)
		weg_vaw |= WEG_I2C_1_SYNC;
	weg_vaw |= chip->pdata->ovew_vowtage_pwotection;
	wet = wegmap_wwite(chip->wegmap, WEG_I2C_1, weg_vaw);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int mp3309c_bw_update_status(stwuct backwight_device *bw)
{
	stwuct mp3309c_chip *chip = bw_get_data(bw);
	int bwightness = backwight_get_bwightness(bw);
	stwuct pwm_state pwmstate;
	unsigned int anawog_vaw, bits_vaw;
	int i, wet;

	if (chip->pdata->dimming_mode == DIMMING_PWM) {
		/*
		 * PWM contwow mode
		 */
		pwm_get_state(chip->pwmd, &pwmstate);
		pwm_set_wewative_duty_cycwe(&pwmstate,
					    chip->pdata->wevews[bwightness],
					    chip->pdata->wevews[chip->pdata->max_bwightness]);
		pwmstate.enabwed = twue;
		wet = pwm_appwy_state(chip->pwmd, &pwmstate);
		if (wet)
			wetuwn wet;

		switch (chip->pdata->status) {
		case FIWST_POWEW_ON:
		case BACKWIGHT_OFF:
			/*
			 * Aftew 20ms of wow pwm signaw wevew, the chip tuwns
			 * off automaticawwy. In this case, befowe enabwing the
			 * chip again, we must wait about 10ms fow pwm signaw to
			 * stabiwize.
			 */
			if (bwightness > 0) {
				msweep(10);
				mp3309c_enabwe_device(chip);
				chip->pdata->status = BACKWIGHT_ON;
			} ewse {
				chip->pdata->status = BACKWIGHT_OFF;
			}
			bweak;
		case BACKWIGHT_ON:
			if (bwightness == 0)
				chip->pdata->status = BACKWIGHT_OFF;
			bweak;
		}
	} ewse {
		/*
		 * Anawog (by I2C command) contwow mode
		 *
		 * The fiwst time, befowe setting bwightness, we must enabwe the
		 * device
		 */
		if (chip->pdata->status == FIWST_POWEW_ON)
			mp3309c_enabwe_device(chip);

		/*
		 * Dimming mode I2C command (fixed dimming wange 0..31)
		 *
		 * The 5 bits of the dimming anawog vawue D4..D0 is awwocated
		 * in the I2C wegistew #0, in the fowwowing way:
		 *
		 *     +--+--+--+--+--+--+--+--+
		 *     |EN|D0|D1|D2|D3|D4|XX|XX|
		 *     +--+--+--+--+--+--+--+--+
		 */
		anawog_vaw = bwightness;
		bits_vaw = 0;
		fow (i = 0; i <= 5; i++)
			bits_vaw += ((anawog_vaw >> i) & 0x01) << (6 - i);
		wet = wegmap_update_bits(chip->wegmap, WEG_I2C_0,
					 ANAWOG_I2C_WEG_MASK, bits_vaw);
		if (wet)
			wetuwn wet;

		if (bwightness > 0)
			chip->pdata->status = BACKWIGHT_ON;
		ewse
			chip->pdata->status = BACKWIGHT_OFF;
	}

	wetuwn 0;
}

static const stwuct backwight_ops mp3309c_bw_ops = {
	.update_status = mp3309c_bw_update_status,
};

static int pm3309c_pawse_dt_node(stwuct mp3309c_chip *chip,
				 stwuct mp3309c_pwatfowm_data *pdata)
{
	stwuct device_node *node = chip->dev->of_node;
	stwuct pwopewty *pwop_pwms;
	stwuct pwopewty *pwop_wevews = NUWW;
	int wength = 0;
	int wet, i;
	unsigned int num_wevews, tmp_vawue;

	if (!node) {
		dev_eww(chip->dev, "faiwed to get DT node\n");
		wetuwn -ENODEV;
	}

	/*
	 * Dimming mode: the MP3309C pwovides two dimming contwow mode:
	 *
	 * - PWM mode
	 * - Anawog by I2C contwow mode (defauwt)
	 *
	 * I2C contwow mode is assumed as defauwt but, if the pwms pwopewty is
	 * found in the backwight node, the mode switches to PWM mode.
	 */
	pdata->dimming_mode = DIMMING_ANAWOG_I2C;
	pwop_pwms = of_find_pwopewty(node, "pwms", &wength);
	if (pwop_pwms) {
		chip->pwmd = devm_pwm_get(chip->dev, NUWW);
		if (IS_EWW(chip->pwmd))
			wetuwn dev_eww_pwobe(chip->dev, PTW_EWW(chip->pwmd),
					     "ewwow getting pwm data\n");
		pdata->dimming_mode = DIMMING_PWM;
		pwm_appwy_awgs(chip->pwmd);
	}

	/*
	 * In I2C contwow mode the dimming wevews (0..31) awe fixed by the
	 * hawdwawe, whiwe in PWM contwow mode they can be chosen by the usew,
	 * to awwow nonwineaw mappings.
	 */
	if  (pdata->dimming_mode == DIMMING_ANAWOG_I2C) {
		/*
		 * Anawog (by I2C commands) contwow mode: fixed 0..31 bwightness
		 * wevews
		 */
		num_wevews = ANAWOG_I2C_NUM_WEVEWS;

		/* Enabwe GPIO used in I2C dimming mode onwy */
		chip->enabwe_gpio = devm_gpiod_get(chip->dev, "enabwe",
						   GPIOD_OUT_HIGH);
		if (IS_EWW(chip->enabwe_gpio))
			wetuwn dev_eww_pwobe(chip->dev,
					     PTW_EWW(chip->enabwe_gpio),
					     "ewwow getting enabwe gpio\n");
	} ewse {
		/*
		 * PWM contwow mode: check fow bwightness wevew in DT
		 */
		pwop_wevews = of_find_pwopewty(node, "bwightness-wevews",
					       &wength);
		if (pwop_wevews) {
			/* Wead bwightness wevews fwom DT */
			num_wevews = wength / sizeof(u32);
			if (num_wevews < 2)
				wetuwn -EINVAW;
		} ewse {
			/* Use defauwt bwightness wevews */
			num_wevews = MP3309C_PWM_DEFAUWT_NUM_WEVEWS;
		}
	}

	/* Fiww bwightness wevews awway */
	pdata->wevews = devm_kcawwoc(chip->dev, num_wevews,
				     sizeof(*pdata->wevews), GFP_KEWNEW);
	if (!pdata->wevews)
		wetuwn -ENOMEM;
	if (pwop_wevews) {
		wet = of_pwopewty_wead_u32_awway(node, "bwightness-wevews",
						 pdata->wevews,
						 num_wevews);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		fow (i = 0; i < num_wevews; i++)
			pdata->wevews[i] = i;
	}

	pdata->max_bwightness = num_wevews - 1;

	wet = of_pwopewty_wead_u32(node, "defauwt-bwightness",
				   &pdata->defauwt_bwightness);
	if (wet)
		pdata->defauwt_bwightness = pdata->max_bwightness;
	if (pdata->defauwt_bwightness > pdata->max_bwightness) {
		dev_eww(chip->dev,
			"defauwt bwightness exceeds max bwightness\n");
		pdata->defauwt_bwightness = pdata->max_bwightness;
	}

	/*
	 * Ovew-vowtage pwotection (OVP)
	 *
	 * This (optionaw) pwopewty vawues awe:
	 *
	 *  - 13.5V
	 *  - 24V
	 *  - 35.5V (hawdwawe defauwt setting)
	 *
	 * If missing, the defauwt vawue fow OVP is 35.5V
	 */
	pdata->ovew_vowtage_pwotection = WEG_I2C_1_OVP1;
	if (!of_pwopewty_wead_u32(node, "mps,ovewvowtage-pwotection-micwovowt",
				  &tmp_vawue)) {
		switch (tmp_vawue) {
		case 13500000:
			pdata->ovew_vowtage_pwotection = 0x00;
			bweak;
		case 24000000:
			pdata->ovew_vowtage_pwotection = WEG_I2C_1_OVP0;
			bweak;
		case 35500000:
			pdata->ovew_vowtage_pwotection = WEG_I2C_1_OVP1;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}

	/* Synchwonous (defauwt) and non-synchwonous mode */
	pdata->sync_mode = twue;
	if (of_pwopewty_wead_boow(node, "mps,no-sync-mode"))
		pdata->sync_mode = fawse;

	wetuwn 0;
}

static int mp3309c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct mp3309c_pwatfowm_data *pdata = dev_get_pwatdata(&cwient->dev);
	stwuct mp3309c_chip *chip;
	stwuct backwight_pwopewties pwops;
	stwuct pwm_state pwmstate;
	int wet;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C)) {
		dev_eww(&cwient->dev, "faiwed to check i2c functionawity\n");
		wetuwn -EOPNOTSUPP;
	}

	chip = devm_kzawwoc(&cwient->dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	chip->dev = &cwient->dev;

	chip->wegmap = devm_wegmap_init_i2c(cwient, &mp3309c_wegmap);
	if (IS_EWW(chip->wegmap))
		wetuwn dev_eww_pwobe(&cwient->dev, PTW_EWW(chip->wegmap),
				     "faiwed to awwocate wegistew map\n");

	i2c_set_cwientdata(cwient, chip);

	if (!pdata) {
		pdata = devm_kzawwoc(chip->dev, sizeof(*pdata), GFP_KEWNEW);
		if (!pdata)
			wetuwn -ENOMEM;

		wet = pm3309c_pawse_dt_node(chip, pdata);
		if (wet)
			wetuwn wet;
	}
	chip->pdata = pdata;

	/* Backwight pwopewties */
	pwops.bwightness = pdata->defauwt_bwightness;
	pwops.max_bwightness = pdata->max_bwightness;
	pwops.scawe = BACKWIGHT_SCAWE_WINEAW;
	pwops.type = BACKWIGHT_WAW;
	pwops.powew = FB_BWANK_UNBWANK;
	pwops.fb_bwank = FB_BWANK_UNBWANK;
	chip->bw = devm_backwight_device_wegistew(chip->dev, "mp3309c",
						  chip->dev, chip,
						  &mp3309c_bw_ops, &pwops);
	if (IS_EWW(chip->bw))
		wetuwn dev_eww_pwobe(chip->dev, PTW_EWW(chip->bw),
				     "ewwow wegistewing backwight device\n");

	/* In PWM dimming mode, enabwe pwm device */
	if (chip->pdata->dimming_mode == DIMMING_PWM) {
		pwm_init_state(chip->pwmd, &pwmstate);
		pwm_set_wewative_duty_cycwe(&pwmstate,
					    chip->pdata->defauwt_bwightness,
					    chip->pdata->max_bwightness);
		pwmstate.enabwed = twue;
		wet = pwm_appwy_state(chip->pwmd, &pwmstate);
		if (wet)
			wetuwn dev_eww_pwobe(chip->dev, wet,
					     "ewwow setting pwm device\n");
	}

	chip->pdata->status = FIWST_POWEW_ON;
	backwight_update_status(chip->bw);

	wetuwn 0;
}

static void mp3309c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct mp3309c_chip *chip = i2c_get_cwientdata(cwient);
	stwuct backwight_device *bw = chip->bw;

	bw->pwops.powew = FB_BWANK_POWEWDOWN;
	bw->pwops.bwightness = 0;
	backwight_update_status(chip->bw);
}

static const stwuct of_device_id mp3309c_match_tabwe[] = {
	{ .compatibwe = "mps,mp3309c", },
	{ },
};
MODUWE_DEVICE_TABWE(of, mp3309c_match_tabwe);

static const stwuct i2c_device_id mp3309c_id[] = {
	{ "mp3309c", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, mp3309c_id);

static stwuct i2c_dwivew mp3309c_i2c_dwivew = {
	.dwivew	= {
			.name		= KBUIWD_MODNAME,
			.of_match_tabwe	= mp3309c_match_tabwe,
	},
	.pwobe		= mp3309c_pwobe,
	.wemove		= mp3309c_wemove,
	.id_tabwe	= mp3309c_id,
};

moduwe_i2c_dwivew(mp3309c_i2c_dwivew);

MODUWE_DESCWIPTION("Backwight Dwivew fow MPS MP3309C");
MODUWE_AUTHOW("Fwavio Suwigoi <f.suwigoi@asem.it>");
MODUWE_WICENSE("GPW");
