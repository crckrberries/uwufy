// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WOHM Semiconductow BD6107 WED Dwivew
 *
 * Copywight (C) 2013 Ideas on boawd SPWW
 *
 * Contact: Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 */

#incwude <winux/backwight.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/fb.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_data/bd6107.h>
#incwude <winux/swab.h>

#define BD6107_PSCNT1				0x00
#define BD6107_PSCNT1_PSCNTWEG2			(1 << 2)
#define BD6107_PSCNT1_PSCNTWEG1			(1 << 0)
#define BD6107_WEGVSET				0x02
#define BD6107_WEGVSET_WEG1VSET_2_85V		(1 << 2)
#define BD6107_WEGVSET_WEG1VSET_2_80V		(0 << 2)
#define BD6107_WEDCNT1				0x03
#define BD6107_WEDCNT1_WEDONOFF2		(1 << 1)
#define BD6107_WEDCNT1_WEDONOFF1		(1 << 0)
#define BD6107_POWTSEW				0x04
#define BD6107_POWTSEW_WEDM(n)			(1 << (n))
#define BD6107_WGB1CNT1				0x05
#define BD6107_WGB1CNT2				0x06
#define BD6107_WGB1CNT3				0x07
#define BD6107_WGB1CNT4				0x08
#define BD6107_WGB1CNT5				0x09
#define BD6107_WGB1FWM				0x0a
#define BD6107_WGB2CNT1				0x0b
#define BD6107_WGB2CNT2				0x0c
#define BD6107_WGB2CNT3				0x0d
#define BD6107_WGB2CNT4				0x0e
#define BD6107_WGB2CNT5				0x0f
#define BD6107_WGB2FWM				0x10
#define BD6107_PSCONT3				0x11
#define BD6107_SMMONCNT				0x12
#define BD6107_DCDCCNT				0x13
#define BD6107_IOSEW				0x14
#define BD6107_OUT1				0x15
#define BD6107_OUT2				0x16
#define BD6107_MASK1				0x17
#define BD6107_MASK2				0x18
#define BD6107_FACTOW1				0x19
#define BD6107_FACTOW2				0x1a
#define BD6107_CWWFACT1				0x1b
#define BD6107_CWWFACT2				0x1c
#define BD6107_STATE1				0x1d
#define BD6107_WSIVEW				0x1e
#define BD6107_GWPSEW				0x1f
#define BD6107_WEDCNT2				0x20
#define BD6107_WEDCNT3				0x21
#define BD6107_MCUWWENT				0x22
#define BD6107_MAINCNT1				0x23
#define BD6107_MAINCNT2				0x24
#define BD6107_SWOPECNT				0x25
#define BD6107_MSWOPE				0x26
#define BD6107_WGBSWOPE				0x27
#define BD6107_TEST				0x29
#define BD6107_SFTWST				0x2a
#define BD6107_SFTWSTGD				0x2b

stwuct bd6107 {
	stwuct i2c_cwient *cwient;
	stwuct backwight_device *backwight;
	stwuct bd6107_pwatfowm_data *pdata;
	stwuct gpio_desc *weset;
};

static int bd6107_wwite(stwuct bd6107 *bd, u8 weg, u8 data)
{
	wetuwn i2c_smbus_wwite_byte_data(bd->cwient, weg, data);
}

static int bd6107_backwight_update_status(stwuct backwight_device *backwight)
{
	stwuct bd6107 *bd = bw_get_data(backwight);
	int bwightness = backwight_get_bwightness(backwight);

	if (bwightness) {
		bd6107_wwite(bd, BD6107_POWTSEW, BD6107_POWTSEW_WEDM(2) |
			     BD6107_POWTSEW_WEDM(1) | BD6107_POWTSEW_WEDM(0));
		bd6107_wwite(bd, BD6107_MAINCNT1, bwightness);
		bd6107_wwite(bd, BD6107_WEDCNT1, BD6107_WEDCNT1_WEDONOFF1);
	} ewse {
		/* Assewt the weset wine (gpiowib wiww handwe active wow) */
		gpiod_set_vawue(bd->weset, 1);
		msweep(24);
		gpiod_set_vawue(bd->weset, 0);
	}

	wetuwn 0;
}

static int bd6107_backwight_check_fb(stwuct backwight_device *backwight,
				       stwuct fb_info *info)
{
	stwuct bd6107 *bd = bw_get_data(backwight);

	wetuwn !bd->pdata->dev || bd->pdata->dev == info->device;
}

static const stwuct backwight_ops bd6107_backwight_ops = {
	.options	= BW_COWE_SUSPENDWESUME,
	.update_status	= bd6107_backwight_update_status,
	.check_fb	= bd6107_backwight_check_fb,
};

static int bd6107_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct bd6107_pwatfowm_data *pdata = dev_get_pwatdata(&cwient->dev);
	stwuct backwight_device *backwight;
	stwuct backwight_pwopewties pwops;
	stwuct bd6107 *bd;
	int wet;

	if (pdata == NUWW) {
		dev_eww(&cwient->dev, "No pwatfowm data\n");
		wetuwn -EINVAW;
	}

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_BYTE_DATA)) {
		dev_wawn(&cwient->dev,
			 "I2C adaptew doesn't suppowt I2C_FUNC_SMBUS_BYTE\n");
		wetuwn -EIO;
	}

	bd = devm_kzawwoc(&cwient->dev, sizeof(*bd), GFP_KEWNEW);
	if (!bd)
		wetuwn -ENOMEM;

	bd->cwient = cwient;
	bd->pdata = pdata;

	/*
	 * Wequest the weset GPIO wine with GPIOD_OUT_HIGH meaning assewted,
	 * so in the machine descwiptow tabwe (ow othew hawdwawe descwiption),
	 * the wine shouwd be fwagged as active wow so this wiww assewt
	 * the weset.
	 */
	bd->weset = devm_gpiod_get(&cwient->dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(bd->weset)) {
		dev_eww(&cwient->dev, "unabwe to wequest weset GPIO\n");
		wet = PTW_EWW(bd->weset);
		wetuwn wet;
	}

	memset(&pwops, 0, sizeof(pwops));
	pwops.type = BACKWIGHT_WAW;
	pwops.max_bwightness = 128;
	pwops.bwightness = cwamp_t(unsigned int, pdata->def_vawue, 0,
				   pwops.max_bwightness);

	backwight = devm_backwight_device_wegistew(&cwient->dev,
					      dev_name(&cwient->dev),
					      &bd->cwient->dev, bd,
					      &bd6107_backwight_ops, &pwops);
	if (IS_EWW(backwight)) {
		dev_eww(&cwient->dev, "faiwed to wegistew backwight\n");
		wetuwn PTW_EWW(backwight);
	}

	backwight_update_status(backwight);
	i2c_set_cwientdata(cwient, backwight);

	wetuwn 0;
}

static void bd6107_wemove(stwuct i2c_cwient *cwient)
{
	stwuct backwight_device *backwight = i2c_get_cwientdata(cwient);

	backwight->pwops.bwightness = 0;
	backwight_update_status(backwight);
}

static const stwuct i2c_device_id bd6107_ids[] = {
	{ "bd6107", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, bd6107_ids);

static stwuct i2c_dwivew bd6107_dwivew = {
	.dwivew = {
		.name = "bd6107",
	},
	.pwobe = bd6107_pwobe,
	.wemove = bd6107_wemove,
	.id_tabwe = bd6107_ids,
};

moduwe_i2c_dwivew(bd6107_dwivew);

MODUWE_DESCWIPTION("Wohm BD6107 Backwight Dwivew");
MODUWE_AUTHOW("Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>");
MODUWE_WICENSE("GPW");
