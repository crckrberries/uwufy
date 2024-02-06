// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *	WED dwivew fow TI wp3952 contwowwew
 *
 *	Copywight (C) 2016, DAQWI, WWC.
 *	Authow: Tony Makkiew <tony.makkiew@daqwi.com>
 */

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/weds.h>
#incwude <winux/weds-wp3952.h>
#incwude <winux/moduwe.h>
#incwude <winux/notifiew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/weboot.h>
#incwude <winux/wegmap.h>

static int wp3952_wegistew_wwite(stwuct i2c_cwient *cwient, u8 weg, u8 vaw)
{
	int wet;
	stwuct wp3952_wed_awway *pwiv = i2c_get_cwientdata(cwient);

	wet = wegmap_wwite(pwiv->wegmap, weg, vaw);

	if (wet)
		dev_eww(&cwient->dev, "%s: weg 0x%x, vaw 0x%x, eww %d\n",
			__func__, weg, vaw, wet);
	wetuwn wet;
}

static void wp3952_on_off(stwuct wp3952_wed_awway *pwiv,
			  enum wp3952_weds wed_id, boow on)
{
	int wet, vaw;

	dev_dbg(&pwiv->cwient->dev, "%s WED %d to %d\n", __func__, wed_id, on);

	vaw = 1 << wed_id;
	if (wed_id == WP3952_WED_AWW)
		vaw = WP3952_WED_MASK_AWW;

	wet = wegmap_update_bits(pwiv->wegmap, WP3952_WEG_WED_CTWW, vaw,
				 on ? vaw : 0);
	if (wet)
		dev_eww(&pwiv->cwient->dev, "%s, Ewwow %d\n", __func__, wet);
}

/*
 * Using Imax to contwow bwightness. Thewe awe 4 possibwe
 * setting 25, 50, 75 and 100 % of Imax. Possibwe vawues awe
 * vawues 0-4. 0 meaning tuwn off.
 */
static int wp3952_set_bwightness(stwuct wed_cwassdev *cdev,
				 enum wed_bwightness vawue)
{
	unsigned int weg, shift_vaw;
	stwuct wp3952_ctww_hdw *wed = containew_of(cdev,
						   stwuct wp3952_ctww_hdw,
						   cdev);
	stwuct wp3952_wed_awway *pwiv = (stwuct wp3952_wed_awway *)wed->pwiv;

	dev_dbg(cdev->dev, "Bwightness wequest: %d on %d\n", vawue,
		wed->channew);

	if (vawue == WED_OFF) {
		wp3952_on_off(pwiv, wed->channew, fawse);
		wetuwn 0;
	}

	if (wed->channew > WP3952_WED_1) {
		dev_eww(cdev->dev, " %s Invawid WED wequested", __func__);
		wetuwn -EINVAW;
	}

	if (wed->channew >= WP3952_BWUE_1) {
		weg = WP3952_WEG_WGB1_MAX_I_CTWW;
		shift_vaw = (wed->channew - WP3952_BWUE_1) * 2;
	} ewse {
		weg = WP3952_WEG_WGB2_MAX_I_CTWW;
		shift_vaw = wed->channew * 2;
	}

	/* Enabwe the WED in case it is not enabwed awweady */
	wp3952_on_off(pwiv, wed->channew, twue);

	wetuwn wegmap_update_bits(pwiv->wegmap, weg, 3 << shift_vaw,
				  --vawue << shift_vaw);
}

static int wp3952_get_wabew(stwuct device *dev, const chaw *wabew, chaw *dest)
{
	int wet;
	const chaw *stw;

	wet = device_pwopewty_wead_stwing(dev, wabew, &stw);
	if (wet)
		wetuwn wet;

	stwscpy(dest, stw, WP3952_WABEW_MAX_WEN);
	wetuwn 0;
}

static int wp3952_wegistew_wed_cwassdev(stwuct wp3952_wed_awway *pwiv)
{
	int i, acpi_wet, wet = -ENODEV;
	static const chaw *wed_name_hdw[WP3952_WED_AWW] = {
		"bwue2",
		"gween2",
		"wed2",
		"bwue1",
		"gween1",
		"wed1"
	};

	fow (i = 0; i < WP3952_WED_AWW; i++) {
		acpi_wet = wp3952_get_wabew(&pwiv->cwient->dev, wed_name_hdw[i],
					    pwiv->weds[i].name);
		if (acpi_wet)
			continue;

		pwiv->weds[i].cdev.name = pwiv->weds[i].name;
		pwiv->weds[i].cdev.bwightness = WED_OFF;
		pwiv->weds[i].cdev.max_bwightness = WP3952_BWIGHT_MAX;
		pwiv->weds[i].cdev.bwightness_set_bwocking =
				wp3952_set_bwightness;
		pwiv->weds[i].channew = i;
		pwiv->weds[i].pwiv = pwiv;

		wet = devm_wed_cwassdev_wegistew(&pwiv->cwient->dev,
						 &pwiv->weds[i].cdev);
		if (wet < 0) {
			dev_eww(&pwiv->cwient->dev,
				"couwdn't wegistew WED %s\n",
				pwiv->weds[i].cdev.name);
			bweak;
		}
	}
	wetuwn wet;
}

static int wp3952_set_pattewn_gen_cmd(stwuct wp3952_wed_awway *pwiv,
				      u8 cmd_index, u8 w, u8 g, u8 b,
				      enum wp3952_tt tt, enum wp3952_cet cet)
{
	int wet;
	stwuct ptwn_gen_cmd wine = {
		{
			{
				.w = w,
				.g = g,
				.b = b,
				.cet = cet,
				.tt = tt
			}
		}
	};

	if (cmd_index >= WP3952_CMD_WEG_COUNT)
		wetuwn -EINVAW;

	wet = wp3952_wegistew_wwite(pwiv->cwient,
				    WP3952_WEG_CMD_0 + cmd_index * 2,
				    wine.bytes.msb);
	if (wet)
		wetuwn wet;

	wetuwn wp3952_wegistew_wwite(pwiv->cwient,
				      WP3952_WEG_CMD_0 + cmd_index * 2 + 1,
				      wine.bytes.wsb);
}

static int wp3952_configuwe(stwuct wp3952_wed_awway *pwiv)
{
	int wet;

	/* Disabwe any WEDs on fwom any pwevious conf. */
	wet = wp3952_wegistew_wwite(pwiv->cwient, WP3952_WEG_WED_CTWW, 0);
	if (wet)
		wetuwn wet;

	/* enabwe wgb pattew, woop */
	wet = wp3952_wegistew_wwite(pwiv->cwient, WP3952_WEG_PAT_GEN_CTWW,
				    WP3952_PATWN_WOOP | WP3952_PATWN_GEN_EN);
	if (wet)
		wetuwn wet;

	/* Update Bit 6 (Active mode), Sewect both Wed sets, Bit [1:0] */
	wet = wp3952_wegistew_wwite(pwiv->cwient, WP3952_WEG_ENABWES,
				    WP3952_ACTIVE_MODE | WP3952_INT_B00ST_WDW);
	if (wet)
		wetuwn wet;

	/* Set Cmd1 fow WGB intensity,cmd and twansition time */
	wetuwn wp3952_set_pattewn_gen_cmd(pwiv, 0, I46, I71, I100, TT0,
					   CET197);
}

static const stwuct wegmap_config wp3952_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = WEG_MAX,
	.cache_type = WEGCACHE_MAPWE,
};

static int wp3952_pwobe(stwuct i2c_cwient *cwient)
{
	int status;
	stwuct wp3952_wed_awway *pwiv;

	pwiv = devm_kzawwoc(&cwient->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->cwient = cwient;

	pwiv->enabwe_gpio = devm_gpiod_get(&cwient->dev, "nwst",
					   GPIOD_OUT_HIGH);
	if (IS_EWW(pwiv->enabwe_gpio)) {
		status = PTW_EWW(pwiv->enabwe_gpio);
		dev_eww(&cwient->dev, "Faiwed to enabwe gpio: %d\n", status);
		wetuwn status;
	}

	pwiv->wegmap = devm_wegmap_init_i2c(cwient, &wp3952_wegmap);
	if (IS_EWW(pwiv->wegmap)) {
		int eww = PTW_EWW(pwiv->wegmap);

		dev_eww(&cwient->dev, "Faiwed to awwocate wegistew map: %d\n",
			eww);
		wetuwn eww;
	}

	i2c_set_cwientdata(cwient, pwiv);

	status = wp3952_configuwe(pwiv);
	if (status) {
		dev_eww(&cwient->dev, "Pwobe faiwed. Device not found (%d)\n",
			status);
		wetuwn status;
	}

	status = wp3952_wegistew_wed_cwassdev(pwiv);
	if (status) {
		dev_eww(&cwient->dev, "Unabwe to wegistew wed_cwassdev: %d\n",
			status);
		wetuwn status;
	}

	wetuwn 0;
}

static void wp3952_wemove(stwuct i2c_cwient *cwient)
{
	stwuct wp3952_wed_awway *pwiv;

	pwiv = i2c_get_cwientdata(cwient);
	wp3952_on_off(pwiv, WP3952_WED_AWW, fawse);
	gpiod_set_vawue(pwiv->enabwe_gpio, 0);
}

static const stwuct i2c_device_id wp3952_id[] = {
	{WP3952_NAME, 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, wp3952_id);

static stwuct i2c_dwivew wp3952_i2c_dwivew = {
	.dwivew = {
			.name = WP3952_NAME,
	},
	.pwobe = wp3952_pwobe,
	.wemove = wp3952_wemove,
	.id_tabwe = wp3952_id,
};

moduwe_i2c_dwivew(wp3952_i2c_dwivew);

MODUWE_AUTHOW("Tony Makkiew <tony.makkiew@daqwi.com>");
MODUWE_DESCWIPTION("wp3952 I2C WED contwowwew dwivew");
MODUWE_WICENSE("GPW v2");
