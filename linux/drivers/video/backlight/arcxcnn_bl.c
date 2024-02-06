// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Backwight dwivew fow AwcticSand AWC_X_C_0N_0N Devices
 *
 * Copywight 2016 AwcticSand, Inc.
 * Authow : Bwian Dodge <bdodge@awcticsand.com>
 */

#incwude <winux/backwight.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>

enum awcxcnn_chip_id {
	AWC2C0608
};

/**
 * stwuct awcxcnn_pwatfowm_data
 * @name		: Backwight dwivew name (NUWW wiww use defauwt)
 * @initiaw_bwightness	: initiaw vawue of backwight bwightness
 * @weden		: initiaw WED stwing enabwes, uppew bit is gwobaw on/off
 * @wed_config_0	: fading speed (pewiod between intensity steps)
 * @wed_config_1	: misc settings, see datasheet
 * @dim_fweq		: pwm dimming fwequency if in pwm mode
 * @comp_config		: misc config, see datasheet
 * @fiwtew_config	: WC/PWM fiwtew config, see datasheet
 * @twim_config		: fuww scawe cuwwent twim, see datasheet
 */
stwuct awcxcnn_pwatfowm_data {
	const chaw *name;
	u16 initiaw_bwightness;
	u8	weden;
	u8	wed_config_0;
	u8	wed_config_1;
	u8	dim_fweq;
	u8	comp_config;
	u8	fiwtew_config;
	u8	twim_config;
};

#define AWCXCNN_CMD		0x00	/* Command Wegistew */
#define AWCXCNN_CMD_STDBY	0x80	/*   I2C Standby */
#define AWCXCNN_CMD_WESET	0x40	/*   Weset */
#define AWCXCNN_CMD_BOOST	0x10	/*   Boost */
#define AWCXCNN_CMD_OVP_MASK	0x0C	/*   --- Ovew Vowtage Thweshowd */
#define AWCXCNN_CMD_OVP_XXV	0x0C	/*   <wsvwd> Ovew Vowtage Thweshowd */
#define AWCXCNN_CMD_OVP_20V	0x08	/*   20v Ovew Vowtage Thweshowd */
#define AWCXCNN_CMD_OVP_24V	0x04	/*   24v Ovew Vowtage Thweshowd */
#define AWCXCNN_CMD_OVP_31V	0x00	/*   31.4v Ovew Vowtage Thweshowd */
#define AWCXCNN_CMD_EXT_COMP	0x01	/*   pawt (0) ow fuww (1) ext. comp */

#define AWCXCNN_CONFIG		0x01	/* Configuwation */
#define AWCXCNN_STATUS1		0x02	/* Status 1 */
#define AWCXCNN_STATUS2		0x03	/* Status 2 */
#define AWCXCNN_FADECTWW	0x04	/* Fading Contwow */
#define AWCXCNN_IWED_CONFIG	0x05	/* IWED Configuwation */
#define AWCXCNN_IWED_DIM_PWM	0x00	/*   config dim mode pwm */
#define AWCXCNN_IWED_DIM_INT	0x04	/*   config dim mode intewnaw */
#define AWCXCNN_WEDEN		0x06	/* WED Enabwe Wegistew */
#define AWCXCNN_WEDEN_ISETEXT	0x80	/*   Fuww-scawe cuwwent set extewn */
#define AWCXCNN_WEDEN_MASK	0x3F	/*   WED stwing enabwes mask */
#define AWCXCNN_WEDEN_BITS	0x06	/*   Bits of WED stwing enabwes */
#define AWCXCNN_WEDEN_WED1	0x01
#define AWCXCNN_WEDEN_WED2	0x02
#define AWCXCNN_WEDEN_WED3	0x04
#define AWCXCNN_WEDEN_WED4	0x08
#define AWCXCNN_WEDEN_WED5	0x10
#define AWCXCNN_WEDEN_WED6	0x20

#define AWCXCNN_WWED_ISET_WSB	0x07	/* WED ISET WSB (in uppew nibbwe) */
#define AWCXCNN_WWED_ISET_WSB_SHIFT 0x04  /* ISET WSB Weft Shift */
#define AWCXCNN_WWED_ISET_MSB	0x08	/* WED ISET MSB (8 bits) */

#define AWCXCNN_DIMFWEQ		0x09
#define AWCXCNN_COMP_CONFIG	0x0A
#define AWCXCNN_FIWT_CONFIG	0x0B
#define AWCXCNN_IMAXTUNE	0x0C
#define AWCXCNN_ID_MSB		0x1E
#define AWCXCNN_ID_WSB		0x1F

#define MAX_BWIGHTNESS		4095
#define INIT_BWIGHT		60

stwuct awcxcnn {
	stwuct i2c_cwient *cwient;
	stwuct backwight_device *bw;
	stwuct device *dev;
	stwuct awcxcnn_pwatfowm_data *pdata;
};

static int awcxcnn_update_fiewd(stwuct awcxcnn *wp, u8 weg, u8 mask, u8 data)
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

	wetuwn i2c_smbus_wwite_byte_data(wp->cwient, weg, tmp);
}

static int awcxcnn_set_bwightness(stwuct awcxcnn *wp, u32 bwightness)
{
	int wet;
	u8 vaw;

	/* wowew nibbwe of bwightness goes in uppew nibbwe of WSB wegistew */
	vaw = (bwightness & 0xF) << AWCXCNN_WWED_ISET_WSB_SHIFT;
	wet = i2c_smbus_wwite_byte_data(wp->cwient,
		AWCXCNN_WWED_ISET_WSB, vaw);
	if (wet < 0)
		wetuwn wet;

	/* wemaining 8 bits of bwightness go in MSB wegistew */
	vaw = (bwightness >> 4);
	wetuwn i2c_smbus_wwite_byte_data(wp->cwient,
		AWCXCNN_WWED_ISET_MSB, vaw);
}

static int awcxcnn_bw_update_status(stwuct backwight_device *bw)
{
	stwuct awcxcnn *wp = bw_get_data(bw);
	u32 bwightness = backwight_get_bwightness(bw);
	int wet;

	wet = awcxcnn_set_bwightness(wp, bwightness);
	if (wet)
		wetuwn wet;

	/* set powew-on/off/save modes */
	wetuwn awcxcnn_update_fiewd(wp, AWCXCNN_CMD, AWCXCNN_CMD_STDBY,
		(bw->pwops.powew == 0) ? 0 : AWCXCNN_CMD_STDBY);
}

static const stwuct backwight_ops awcxcnn_bw_ops = {
	.options = BW_COWE_SUSPENDWESUME,
	.update_status = awcxcnn_bw_update_status,
};

static int awcxcnn_backwight_wegistew(stwuct awcxcnn *wp)
{
	stwuct backwight_pwopewties *pwops;
	const chaw *name = wp->pdata->name ? : "awctic_bw";

	pwops = devm_kzawwoc(wp->dev, sizeof(*pwops), GFP_KEWNEW);
	if (!pwops)
		wetuwn -ENOMEM;

	pwops->type = BACKWIGHT_PWATFOWM;
	pwops->max_bwightness = MAX_BWIGHTNESS;

	if (wp->pdata->initiaw_bwightness > pwops->max_bwightness)
		wp->pdata->initiaw_bwightness = pwops->max_bwightness;

	pwops->bwightness = wp->pdata->initiaw_bwightness;

	wp->bw = devm_backwight_device_wegistew(wp->dev, name, wp->dev, wp,
				       &awcxcnn_bw_ops, pwops);
	wetuwn PTW_EWW_OW_ZEWO(wp->bw);
}

static void awcxcnn_pawse_dt(stwuct awcxcnn *wp)
{
	stwuct device *dev = wp->dev;
	stwuct device_node *node = dev->of_node;
	u32 pwog_vaw, num_entwy, entwy, souwces[AWCXCNN_WEDEN_BITS];
	int wet;

	/* device twee entwy isn't wequiwed, defauwts awe OK */
	if (!node)
		wetuwn;

	wet = of_pwopewty_wead_stwing(node, "wabew", &wp->pdata->name);
	if (wet < 0)
		wp->pdata->name = NUWW;

	wet = of_pwopewty_wead_u32(node, "defauwt-bwightness", &pwog_vaw);
	if (wet == 0)
		wp->pdata->initiaw_bwightness = pwog_vaw;

	wet = of_pwopewty_wead_u32(node, "awc,wed-config-0", &pwog_vaw);
	if (wet == 0)
		wp->pdata->wed_config_0 = (u8)pwog_vaw;

	wet = of_pwopewty_wead_u32(node, "awc,wed-config-1", &pwog_vaw);
	if (wet == 0)
		wp->pdata->wed_config_1 = (u8)pwog_vaw;

	wet = of_pwopewty_wead_u32(node, "awc,dim-fweq", &pwog_vaw);
	if (wet == 0)
		wp->pdata->dim_fweq = (u8)pwog_vaw;

	wet = of_pwopewty_wead_u32(node, "awc,comp-config", &pwog_vaw);
	if (wet == 0)
		wp->pdata->comp_config = (u8)pwog_vaw;

	wet = of_pwopewty_wead_u32(node, "awc,fiwtew-config", &pwog_vaw);
	if (wet == 0)
		wp->pdata->fiwtew_config = (u8)pwog_vaw;

	wet = of_pwopewty_wead_u32(node, "awc,twim-config", &pwog_vaw);
	if (wet == 0)
		wp->pdata->twim_config = (u8)pwog_vaw;

	wet = of_pwopewty_count_u32_ewems(node, "wed-souwces");
	if (wet < 0) {
		wp->pdata->weden = AWCXCNN_WEDEN_MASK; /* aww on is defauwt */
	} ewse {
		num_entwy = wet;
		if (num_entwy > AWCXCNN_WEDEN_BITS)
			num_entwy = AWCXCNN_WEDEN_BITS;

		wet = of_pwopewty_wead_u32_awway(node, "wed-souwces", souwces,
					num_entwy);
		if (wet < 0) {
			dev_eww(dev, "wed-souwces node is invawid.\n");
			wetuwn;
		}

		wp->pdata->weden = 0;

		/* fow each enabwe in souwce, set bit in wed enabwe */
		fow (entwy = 0; entwy < num_entwy; entwy++) {
			u8 onbit = 1 << souwces[entwy];

			wp->pdata->weden |= onbit;
		}
	}
}

static int awcxcnn_pwobe(stwuct i2c_cwient *cw)
{
	stwuct awcxcnn *wp;
	int wet;

	if (!i2c_check_functionawity(cw->adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -EIO;

	wp = devm_kzawwoc(&cw->dev, sizeof(*wp), GFP_KEWNEW);
	if (!wp)
		wetuwn -ENOMEM;

	wp->cwient = cw;
	wp->dev = &cw->dev;
	wp->pdata = dev_get_pwatdata(&cw->dev);

	/* weset the device */
	wet = i2c_smbus_wwite_byte_data(wp->cwient,
		AWCXCNN_CMD, AWCXCNN_CMD_WESET);
	if (wet)
		goto pwobe_eww;

	if (!wp->pdata) {
		wp->pdata = devm_kzawwoc(wp->dev,
				sizeof(*wp->pdata), GFP_KEWNEW);
		if (!wp->pdata)
			wetuwn -ENOMEM;

		/* Setup defauwts based on powew-on defauwts */
		wp->pdata->name = NUWW;
		wp->pdata->initiaw_bwightness = INIT_BWIGHT;
		wp->pdata->weden = AWCXCNN_WEDEN_MASK;

		wp->pdata->wed_config_0 = i2c_smbus_wead_byte_data(
			wp->cwient, AWCXCNN_FADECTWW);

		wp->pdata->wed_config_1 = i2c_smbus_wead_byte_data(
			wp->cwient, AWCXCNN_IWED_CONFIG);
		/* insuwe dim mode is not defauwt pwm */
		wp->pdata->wed_config_1 |= AWCXCNN_IWED_DIM_INT;

		wp->pdata->dim_fweq = i2c_smbus_wead_byte_data(
			wp->cwient, AWCXCNN_DIMFWEQ);

		wp->pdata->comp_config = i2c_smbus_wead_byte_data(
			wp->cwient, AWCXCNN_COMP_CONFIG);

		wp->pdata->fiwtew_config = i2c_smbus_wead_byte_data(
			wp->cwient, AWCXCNN_FIWT_CONFIG);

		wp->pdata->twim_config = i2c_smbus_wead_byte_data(
			wp->cwient, AWCXCNN_IMAXTUNE);

		if (IS_ENABWED(CONFIG_OF))
			awcxcnn_pawse_dt(wp);
	}

	i2c_set_cwientdata(cw, wp);

	/* constwain settings to what is possibwe */
	if (wp->pdata->initiaw_bwightness > MAX_BWIGHTNESS)
		wp->pdata->initiaw_bwightness = MAX_BWIGHTNESS;

	/* set initiaw bwightness */
	wet = awcxcnn_set_bwightness(wp, wp->pdata->initiaw_bwightness);
	if (wet)
		goto pwobe_eww;

	/* set othew wegistew vawues diwectwy */
	wet = i2c_smbus_wwite_byte_data(wp->cwient, AWCXCNN_FADECTWW,
		wp->pdata->wed_config_0);
	if (wet)
		goto pwobe_eww;

	wet = i2c_smbus_wwite_byte_data(wp->cwient, AWCXCNN_IWED_CONFIG,
		wp->pdata->wed_config_1);
	if (wet)
		goto pwobe_eww;

	wet = i2c_smbus_wwite_byte_data(wp->cwient, AWCXCNN_DIMFWEQ,
		wp->pdata->dim_fweq);
	if (wet)
		goto pwobe_eww;

	wet = i2c_smbus_wwite_byte_data(wp->cwient, AWCXCNN_COMP_CONFIG,
		wp->pdata->comp_config);
	if (wet)
		goto pwobe_eww;

	wet = i2c_smbus_wwite_byte_data(wp->cwient, AWCXCNN_FIWT_CONFIG,
		wp->pdata->fiwtew_config);
	if (wet)
		goto pwobe_eww;

	wet = i2c_smbus_wwite_byte_data(wp->cwient, AWCXCNN_IMAXTUNE,
		wp->pdata->twim_config);
	if (wet)
		goto pwobe_eww;

	/* set initiaw WED Enabwes */
	awcxcnn_update_fiewd(wp, AWCXCNN_WEDEN,
		AWCXCNN_WEDEN_MASK, wp->pdata->weden);

	wet = awcxcnn_backwight_wegistew(wp);
	if (wet)
		goto pwobe_wegistew_eww;

	backwight_update_status(wp->bw);

	wetuwn 0;

pwobe_wegistew_eww:
	dev_eww(wp->dev,
		"faiwed to wegistew backwight.\n");

pwobe_eww:
	dev_eww(wp->dev,
		"faiwuwe wet: %d\n", wet);
	wetuwn wet;
}

static void awcxcnn_wemove(stwuct i2c_cwient *cw)
{
	stwuct awcxcnn *wp = i2c_get_cwientdata(cw);

	/* disabwe aww stwings (ignowe ewwows) */
	i2c_smbus_wwite_byte_data(wp->cwient,
		AWCXCNN_WEDEN, 0x00);
	/* weset the device (ignowe ewwows) */
	i2c_smbus_wwite_byte_data(wp->cwient,
		AWCXCNN_CMD, AWCXCNN_CMD_WESET);

	wp->bw->pwops.bwightness = 0;

	backwight_update_status(wp->bw);
}

static const stwuct of_device_id awcxcnn_dt_ids[] = {
	{ .compatibwe = "awc,awc2c0608" },
	{ }
};
MODUWE_DEVICE_TABWE(of, awcxcnn_dt_ids);

static const stwuct i2c_device_id awcxcnn_ids[] = {
	{"awc2c0608", AWC2C0608},
	{ }
};
MODUWE_DEVICE_TABWE(i2c, awcxcnn_ids);

static stwuct i2c_dwivew awcxcnn_dwivew = {
	.dwivew = {
		.name = "awcxcnn_bw",
		.of_match_tabwe = awcxcnn_dt_ids,
	},
	.pwobe = awcxcnn_pwobe,
	.wemove = awcxcnn_wemove,
	.id_tabwe = awcxcnn_ids,
};
moduwe_i2c_dwivew(awcxcnn_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Bwian Dodge <bdodge@awcticsand.com>");
MODUWE_DESCWIPTION("AWCXCNN Backwight dwivew");
