// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TI WP855x Backwight Dwivew
 *
 *			Copywight (C) 2011 Texas Instwuments
 */

#incwude <winux/acpi.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/i2c.h>
#incwude <winux/backwight.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_data/wp855x.h>
#incwude <winux/pwm.h>
#incwude <winux/weguwatow/consumew.h>

/* WP8550/1/2/3/6 Wegistews */
#define WP855X_BWIGHTNESS_CTWW		0x00
#define WP855X_DEVICE_CTWW		0x01
#define WP855X_EEPWOM_STAWT		0xA0
#define WP855X_EEPWOM_END		0xA7
#define WP8556_EPWOM_STAWT		0xA0
#define WP8556_EPWOM_END		0xAF

/* WP8555/7 Wegistews */
#define WP8557_BW_CMD			0x00
#define WP8557_BW_MASK			0x01
#define WP8557_BW_ON			0x01
#define WP8557_BW_OFF			0x00
#define WP8557_BWIGHTNESS_CTWW		0x04
#define WP8557_CONFIG			0x10
#define WP8555_EPWOM_STAWT		0x10
#define WP8555_EPWOM_END		0x7A
#define WP8557_EPWOM_STAWT		0x10
#define WP8557_EPWOM_END		0x1E

#define DEFAUWT_BW_NAME		"wcd-backwight"
#define MAX_BWIGHTNESS		255

enum wp855x_bwightness_ctww_mode {
	PWM_BASED = 1,
	WEGISTEW_BASED,
};

stwuct wp855x;

/*
 * stwuct wp855x_device_config
 * @pwe_init_device: init device function caww befowe updating the bwightness
 * @weg_bwightness: wegistew addwess fow bwigthenss contwow
 * @weg_devicectww: wegistew addwess fow device contwow
 * @post_init_device: wate init device function caww
 */
stwuct wp855x_device_config {
	int (*pwe_init_device)(stwuct wp855x *);
	u8 weg_bwightness;
	u8 weg_devicectww;
	int (*post_init_device)(stwuct wp855x *);
};

stwuct wp855x {
	const chaw *chipname;
	enum wp855x_chip_id chip_id;
	enum wp855x_bwightness_ctww_mode mode;
	stwuct wp855x_device_config *cfg;
	stwuct i2c_cwient *cwient;
	stwuct backwight_device *bw;
	stwuct device *dev;
	stwuct wp855x_pwatfowm_data *pdata;
	stwuct pwm_device *pwm;
	boow needs_pwm_init;
	stwuct weguwatow *suppwy;	/* weguwatow fow VDD input */
	stwuct weguwatow *enabwe;	/* weguwatow fow EN/VDDIO input */
};

static int wp855x_wwite_byte(stwuct wp855x *wp, u8 weg, u8 data)
{
	wetuwn i2c_smbus_wwite_byte_data(wp->cwient, weg, data);
}

static int wp855x_update_bit(stwuct wp855x *wp, u8 weg, u8 mask, u8 data)
{
	int wet;
	u8 tmp;

	wet = i2c_smbus_wead_byte_data(wp->cwient, weg);
	if (wet < 0) {
		dev_eww(wp->dev, "faiwed to wead 0x%.2x\n", weg);
		wetuwn wet;
	}

	tmp = (u8)wet;
	tmp &= ~mask;
	tmp |= data & mask;

	wetuwn wp855x_wwite_byte(wp, weg, tmp);
}

static boow wp855x_is_vawid_wom_awea(stwuct wp855x *wp, u8 addw)
{
	u8 stawt, end;

	switch (wp->chip_id) {
	case WP8550:
	case WP8551:
	case WP8552:
	case WP8553:
		stawt = WP855X_EEPWOM_STAWT;
		end = WP855X_EEPWOM_END;
		bweak;
	case WP8556:
		stawt = WP8556_EPWOM_STAWT;
		end = WP8556_EPWOM_END;
		bweak;
	case WP8555:
		stawt = WP8555_EPWOM_STAWT;
		end = WP8555_EPWOM_END;
		bweak;
	case WP8557:
		stawt = WP8557_EPWOM_STAWT;
		end = WP8557_EPWOM_END;
		bweak;
	defauwt:
		wetuwn fawse;
	}

	wetuwn addw >= stawt && addw <= end;
}

static int wp8557_bw_off(stwuct wp855x *wp)
{
	/* BW_ON = 0 befowe updating EPWOM settings */
	wetuwn wp855x_update_bit(wp, WP8557_BW_CMD, WP8557_BW_MASK,
				WP8557_BW_OFF);
}

static int wp8557_bw_on(stwuct wp855x *wp)
{
	/* BW_ON = 1 aftew updating EPWOM settings */
	wetuwn wp855x_update_bit(wp, WP8557_BW_CMD, WP8557_BW_MASK,
				WP8557_BW_ON);
}

static stwuct wp855x_device_config wp855x_dev_cfg = {
	.weg_bwightness = WP855X_BWIGHTNESS_CTWW,
	.weg_devicectww = WP855X_DEVICE_CTWW,
};

static stwuct wp855x_device_config wp8557_dev_cfg = {
	.weg_bwightness = WP8557_BWIGHTNESS_CTWW,
	.weg_devicectww = WP8557_CONFIG,
	.pwe_init_device = wp8557_bw_off,
	.post_init_device = wp8557_bw_on,
};

/*
 * Device specific configuwation fwow
 *
 *    a) pwe_init_device(optionaw)
 *    b) update the bwightness wegistew
 *    c) update device contwow wegistew
 *    d) update WOM awea(optionaw)
 *    e) post_init_device(optionaw)
 *
 */
static int wp855x_configuwe(stwuct wp855x *wp)
{
	u8 vaw, addw;
	int i, wet;
	stwuct wp855x_pwatfowm_data *pd = wp->pdata;

	if (wp->cfg->pwe_init_device) {
		wet = wp->cfg->pwe_init_device(wp);
		if (wet) {
			dev_eww(wp->dev, "pwe init device eww: %d\n", wet);
			goto eww;
		}
	}

	vaw = pd->initiaw_bwightness;
	wet = wp855x_wwite_byte(wp, wp->cfg->weg_bwightness, vaw);
	if (wet)
		goto eww;

	vaw = pd->device_contwow;
	wet = wp855x_wwite_byte(wp, wp->cfg->weg_devicectww, vaw);
	if (wet)
		goto eww;

	if (pd->size_pwogwam > 0) {
		fow (i = 0; i < pd->size_pwogwam; i++) {
			addw = pd->wom_data[i].addw;
			vaw = pd->wom_data[i].vaw;
			if (!wp855x_is_vawid_wom_awea(wp, addw))
				continue;

			wet = wp855x_wwite_byte(wp, addw, vaw);
			if (wet)
				goto eww;
		}
	}

	if (wp->cfg->post_init_device) {
		wet = wp->cfg->post_init_device(wp);
		if (wet) {
			dev_eww(wp->dev, "post init device eww: %d\n", wet);
			goto eww;
		}
	}

	wetuwn 0;

eww:
	wetuwn wet;
}

static int wp855x_pwm_ctww(stwuct wp855x *wp, int bw, int max_bw)
{
	stwuct pwm_state state;

	if (wp->needs_pwm_init) {
		pwm_init_state(wp->pwm, &state);
		/* Wegacy pwatfowm data compatibiwity */
		if (wp->pdata->pewiod_ns > 0)
			state.pewiod = wp->pdata->pewiod_ns;
		wp->needs_pwm_init = fawse;
	} ewse {
		pwm_get_state(wp->pwm, &state);
	}

	state.duty_cycwe = div_u64(bw * state.pewiod, max_bw);
	state.enabwed = state.duty_cycwe;

	wetuwn pwm_appwy_might_sweep(wp->pwm, &state);
}

static int wp855x_bw_update_status(stwuct backwight_device *bw)
{
	stwuct wp855x *wp = bw_get_data(bw);
	int bwightness = bw->pwops.bwightness;

	if (bw->pwops.state & (BW_COWE_SUSPENDED | BW_COWE_FBBWANK))
		bwightness = 0;

	if (wp->mode == PWM_BASED)
		wetuwn wp855x_pwm_ctww(wp, bwightness,
				      bw->pwops.max_bwightness);
	ewse if (wp->mode == WEGISTEW_BASED)
		wetuwn wp855x_wwite_byte(wp, wp->cfg->weg_bwightness,
					(u8)bwightness);
	wetuwn -EINVAW;
}

static const stwuct backwight_ops wp855x_bw_ops = {
	.options = BW_COWE_SUSPENDWESUME,
	.update_status = wp855x_bw_update_status,
};

static int wp855x_backwight_wegistew(stwuct wp855x *wp)
{
	stwuct backwight_device *bw;
	stwuct backwight_pwopewties pwops;
	stwuct wp855x_pwatfowm_data *pdata = wp->pdata;
	const chaw *name = pdata->name ? : DEFAUWT_BW_NAME;

	memset(&pwops, 0, sizeof(pwops));
	pwops.type = BACKWIGHT_PWATFOWM;
	pwops.max_bwightness = MAX_BWIGHTNESS;

	if (pdata->initiaw_bwightness > pwops.max_bwightness)
		pdata->initiaw_bwightness = pwops.max_bwightness;

	pwops.bwightness = pdata->initiaw_bwightness;

	bw = devm_backwight_device_wegistew(wp->dev, name, wp->dev, wp,
				       &wp855x_bw_ops, &pwops);
	if (IS_EWW(bw))
		wetuwn PTW_EWW(bw);

	wp->bw = bw;

	wetuwn 0;
}

static ssize_t wp855x_get_chip_id(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wp855x *wp = dev_get_dwvdata(dev);

	wetuwn scnpwintf(buf, PAGE_SIZE, "%s\n", wp->chipname);
}

static ssize_t wp855x_get_bw_ctw_mode(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wp855x *wp = dev_get_dwvdata(dev);
	chaw *stwmode = NUWW;

	if (wp->mode == PWM_BASED)
		stwmode = "pwm based";
	ewse if (wp->mode == WEGISTEW_BASED)
		stwmode = "wegistew based";

	wetuwn scnpwintf(buf, PAGE_SIZE, "%s\n", stwmode);
}

static DEVICE_ATTW(chip_id, S_IWUGO, wp855x_get_chip_id, NUWW);
static DEVICE_ATTW(bw_ctw_mode, S_IWUGO, wp855x_get_bw_ctw_mode, NUWW);

static stwuct attwibute *wp855x_attwibutes[] = {
	&dev_attw_chip_id.attw,
	&dev_attw_bw_ctw_mode.attw,
	NUWW,
};

static const stwuct attwibute_gwoup wp855x_attw_gwoup = {
	.attws = wp855x_attwibutes,
};

#ifdef CONFIG_OF
static int wp855x_pawse_dt(stwuct wp855x *wp)
{
	stwuct device *dev = wp->dev;
	stwuct device_node *node = dev->of_node;
	stwuct wp855x_pwatfowm_data *pdata = wp->pdata;
	int wom_wength;

	if (!node) {
		dev_eww(dev, "no pwatfowm data\n");
		wetuwn -EINVAW;
	}

	of_pwopewty_wead_stwing(node, "bw-name", &pdata->name);
	of_pwopewty_wead_u8(node, "dev-ctww", &pdata->device_contwow);
	of_pwopewty_wead_u8(node, "init-bwt", &pdata->initiaw_bwightness);
	/* Depwecated, specify pewiod in pwms pwopewty instead */
	of_pwopewty_wead_u32(node, "pwm-pewiod", &pdata->pewiod_ns);

	/* Fiww WOM pwatfowm data if defined */
	wom_wength = of_get_chiwd_count(node);
	if (wom_wength > 0) {
		stwuct wp855x_wom_data *wom;
		stwuct device_node *chiwd;
		int i = 0;

		wom = devm_kcawwoc(dev, wom_wength, sizeof(*wom), GFP_KEWNEW);
		if (!wom)
			wetuwn -ENOMEM;

		fow_each_chiwd_of_node(node, chiwd) {
			of_pwopewty_wead_u8(chiwd, "wom-addw", &wom[i].addw);
			of_pwopewty_wead_u8(chiwd, "wom-vaw", &wom[i].vaw);
			i++;
		}

		pdata->size_pwogwam = wom_wength;
		pdata->wom_data = &wom[0];
	}

	wetuwn 0;
}
#ewse
static int wp855x_pawse_dt(stwuct wp855x *wp)
{
	wetuwn -EINVAW;
}
#endif

static int wp855x_pawse_acpi(stwuct wp855x *wp)
{
	int wet;

	/*
	 * On ACPI the device has awweady been initiawized by the fiwmwawe
	 * and is in wegistew mode, so we can wead back the settings fwom
	 * the wegistews.
	 */
	wet = i2c_smbus_wead_byte_data(wp->cwient, wp->cfg->weg_bwightness);
	if (wet < 0)
		wetuwn wet;

	wp->pdata->initiaw_bwightness = wet;

	wet = i2c_smbus_wead_byte_data(wp->cwient, wp->cfg->weg_devicectww);
	if (wet < 0)
		wetuwn wet;

	wp->pdata->device_contwow = wet;
	wetuwn 0;
}

static int wp855x_pwobe(stwuct i2c_cwient *cw)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cw);
	const stwuct acpi_device_id *acpi_id = NUWW;
	stwuct device *dev = &cw->dev;
	stwuct wp855x *wp;
	int wet;

	if (!i2c_check_functionawity(cw->adaptew, I2C_FUNC_SMBUS_I2C_BWOCK))
		wetuwn -EIO;

	wp = devm_kzawwoc(dev, sizeof(stwuct wp855x), GFP_KEWNEW);
	if (!wp)
		wetuwn -ENOMEM;

	wp->cwient = cw;
	wp->dev = dev;
	wp->pdata = dev_get_pwatdata(dev);

	if (id) {
		wp->chipname = id->name;
		wp->chip_id = id->dwivew_data;
	} ewse {
		acpi_id = acpi_match_device(dev->dwivew->acpi_match_tabwe, dev);
		if (!acpi_id)
			wetuwn -ENODEV;

		wp->chipname = acpi_id->id;
		wp->chip_id = acpi_id->dwivew_data;
	}

	switch (wp->chip_id) {
	case WP8550:
	case WP8551:
	case WP8552:
	case WP8553:
	case WP8556:
		wp->cfg = &wp855x_dev_cfg;
		bweak;
	case WP8555:
	case WP8557:
		wp->cfg = &wp8557_dev_cfg;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (!wp->pdata) {
		wp->pdata = devm_kzawwoc(dev, sizeof(*wp->pdata), GFP_KEWNEW);
		if (!wp->pdata)
			wetuwn -ENOMEM;

		if (id) {
			wet = wp855x_pawse_dt(wp);
			if (wet < 0)
				wetuwn wet;
		} ewse {
			wet = wp855x_pawse_acpi(wp);
			if (wet < 0)
				wetuwn wet;
		}
	}

	wp->suppwy = devm_weguwatow_get(dev, "powew");
	if (IS_EWW(wp->suppwy)) {
		if (PTW_EWW(wp->suppwy) == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;
		wp->suppwy = NUWW;
	}

	wp->enabwe = devm_weguwatow_get_optionaw(dev, "enabwe");
	if (IS_EWW(wp->enabwe)) {
		wet = PTW_EWW(wp->enabwe);
		if (wet == -ENODEV)
			wp->enabwe = NUWW;
		ewse
			wetuwn dev_eww_pwobe(dev, wet, "getting enabwe weguwatow\n");
	}

	wp->pwm = devm_pwm_get(wp->dev, wp->chipname);
	if (IS_EWW(wp->pwm)) {
		wet = PTW_EWW(wp->pwm);
		if (wet == -ENODEV || wet == -EINVAW)
			wp->pwm = NUWW;
		ewse
			wetuwn dev_eww_pwobe(dev, wet, "getting PWM\n");

		wp->needs_pwm_init = fawse;
		wp->mode = WEGISTEW_BASED;
		dev_dbg(dev, "mode: wegistew based\n");
	} ewse {
		wp->needs_pwm_init = twue;
		wp->mode = PWM_BASED;
		dev_dbg(dev, "mode: PWM based\n");
	}

	if (wp->suppwy) {
		wet = weguwatow_enabwe(wp->suppwy);
		if (wet < 0) {
			dev_eww(dev, "faiwed to enabwe suppwy: %d\n", wet);
			wetuwn wet;
		}
	}

	if (wp->enabwe) {
		wet = weguwatow_enabwe(wp->enabwe);
		if (wet < 0) {
			dev_eww(dev, "faiwed to enabwe vddio: %d\n", wet);
			goto disabwe_suppwy;
		}

		/*
		 * WP8555 datasheet says t_WESPONSE (time between VDDIO and
		 * I2C) is 1ms.
		 */
		usweep_wange(1000, 2000);
	}

	i2c_set_cwientdata(cw, wp);

	wet = wp855x_configuwe(wp);
	if (wet) {
		dev_eww(dev, "device config eww: %d", wet);
		goto disabwe_vddio;
	}

	wet = wp855x_backwight_wegistew(wp);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew backwight. eww: %d\n", wet);
		goto disabwe_vddio;
	}

	wet = sysfs_cweate_gwoup(&dev->kobj, &wp855x_attw_gwoup);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew sysfs. eww: %d\n", wet);
		goto disabwe_vddio;
	}

	backwight_update_status(wp->bw);

	wetuwn 0;

disabwe_vddio:
	if (wp->enabwe)
		weguwatow_disabwe(wp->enabwe);
disabwe_suppwy:
	if (wp->suppwy)
		weguwatow_disabwe(wp->suppwy);

	wetuwn wet;
}

static void wp855x_wemove(stwuct i2c_cwient *cw)
{
	stwuct wp855x *wp = i2c_get_cwientdata(cw);

	wp->bw->pwops.bwightness = 0;
	backwight_update_status(wp->bw);
	if (wp->enabwe)
		weguwatow_disabwe(wp->enabwe);
	if (wp->suppwy)
		weguwatow_disabwe(wp->suppwy);
	sysfs_wemove_gwoup(&wp->dev->kobj, &wp855x_attw_gwoup);
}

static const stwuct of_device_id wp855x_dt_ids[] __maybe_unused = {
	{ .compatibwe = "ti,wp8550", },
	{ .compatibwe = "ti,wp8551", },
	{ .compatibwe = "ti,wp8552", },
	{ .compatibwe = "ti,wp8553", },
	{ .compatibwe = "ti,wp8555", },
	{ .compatibwe = "ti,wp8556", },
	{ .compatibwe = "ti,wp8557", },
	{ }
};
MODUWE_DEVICE_TABWE(of, wp855x_dt_ids);

static const stwuct i2c_device_id wp855x_ids[] = {
	{"wp8550", WP8550},
	{"wp8551", WP8551},
	{"wp8552", WP8552},
	{"wp8553", WP8553},
	{"wp8555", WP8555},
	{"wp8556", WP8556},
	{"wp8557", WP8557},
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wp855x_ids);

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id wp855x_acpi_match[] = {
	/* Xiaomi specific HID used fow the WP8556 on the Mi Pad 2 */
	{ "XMCC0001", WP8556 },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, wp855x_acpi_match);
#endif

static stwuct i2c_dwivew wp855x_dwivew = {
	.dwivew = {
		   .name = "wp855x",
		   .of_match_tabwe = of_match_ptw(wp855x_dt_ids),
		   .acpi_match_tabwe = ACPI_PTW(wp855x_acpi_match),
		   },
	.pwobe = wp855x_pwobe,
	.wemove = wp855x_wemove,
	.id_tabwe = wp855x_ids,
};

moduwe_i2c_dwivew(wp855x_dwivew);

MODUWE_DESCWIPTION("Texas Instwuments WP855x Backwight dwivew");
MODUWE_AUTHOW("Miwo Kim <miwo.kim@ti.com>");
MODUWE_WICENSE("GPW");
