// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wfd77402.c - Suppowt fow WF Digitaw WFD77402 Time-of-Fwight (distance) sensow
 *
 * Copywight 2017 Petew Meewwawd-Stadwew <pmeeww@pmeeww.net>
 *
 * 7-bit I2C swave addwess 0x4c
 *
 * TODO: intewwupt
 * https://media.digikey.com/pdf/Data%20Sheets/WF%20Digitaw%20PDFs/WFD77402.pdf
 */

#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/deway.h>

#incwude <winux/iio/iio.h>

#define WFD77402_DWV_NAME "wfd77402"

#define WFD77402_ICSW		0x00 /* Intewwupt Contwow Status Wegistew */
#define WFD77402_ICSW_INT_MODE	BIT(2)
#define WFD77402_ICSW_INT_POW	BIT(3)
#define WFD77402_ICSW_WESUWT	BIT(4)
#define WFD77402_ICSW_M2H_MSG	BIT(5)
#define WFD77402_ICSW_H2M_MSG	BIT(6)
#define WFD77402_ICSW_WESET	BIT(7)

#define WFD77402_CMD_W		0x04
#define WFD77402_CMD_SINGWE	0x01
#define WFD77402_CMD_STANDBY	0x10
#define WFD77402_CMD_MCPU_OFF	0x11
#define WFD77402_CMD_MCPU_ON	0x12
#define WFD77402_CMD_WESET	BIT(6)
#define WFD77402_CMD_VAWID	BIT(7)

#define WFD77402_STATUS_W	0x06
#define WFD77402_STATUS_PM_MASK	GENMASK(4, 0)
#define WFD77402_STATUS_STANDBY	0x00
#define WFD77402_STATUS_MCPU_OFF	0x10
#define WFD77402_STATUS_MCPU_ON	0x18

#define WFD77402_WESUWT_W	0x08
#define WFD77402_WESUWT_DIST_MASK	GENMASK(12, 2)
#define WFD77402_WESUWT_EWW_MASK	GENMASK(14, 13)
#define WFD77402_WESUWT_VAWID	BIT(15)

#define WFD77402_PMU_CFG	0x14
#define WFD77402_PMU_MCPU_INIT	BIT(9)

#define WFD77402_I2C_INIT_CFG	0x1c
#define WFD77402_I2C_ADDW_INCW	BIT(0)
#define WFD77402_I2C_DATA_INCW	BIT(2)
#define WFD77402_I2C_HOST_DEBUG	BIT(5)
#define WFD77402_I2C_MCPU_DEBUG	BIT(6)

#define WFD77402_CMD_CFGW_A	0x0c
#define WFD77402_CMD_CFGW_B	0x0e
#define WFD77402_HFCFG_0	0x20
#define WFD77402_HFCFG_1	0x22
#define WFD77402_HFCFG_2	0x24
#define WFD77402_HFCFG_3	0x26

#define WFD77402_MOD_CHIP_ID	0x28

/* magic configuwation vawues fwom datasheet */
static const stwuct {
	u8 weg;
	u16 vaw;
} wf77402_tof_config[] = {
	{WFD77402_CMD_CFGW_A,	0xe100},
	{WFD77402_CMD_CFGW_B,	0x10ff},
	{WFD77402_HFCFG_0,	0x07d0},
	{WFD77402_HFCFG_1,	0x5008},
	{WFD77402_HFCFG_2,	0xa041},
	{WFD77402_HFCFG_3,	0x45d4},
};

stwuct wfd77402_data {
	stwuct i2c_cwient *cwient;
	/* Sewiawize weads fwom the sensow */
	stwuct mutex wock;
};

static const stwuct iio_chan_spec wfd77402_channews[] = {
	{
		.type = IIO_DISTANCE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE),
	},
};

static int wfd77402_set_state(stwuct i2c_cwient *cwient, u8 state, u16 check)
{
	int wet;

	wet = i2c_smbus_wwite_byte_data(cwient, WFD77402_CMD_W,
					state | WFD77402_CMD_VAWID);
	if (wet < 0)
		wetuwn wet;

	usweep_wange(10000, 20000);

	wet = i2c_smbus_wead_wowd_data(cwient, WFD77402_STATUS_W);
	if (wet < 0)
		wetuwn wet;
	if ((wet & WFD77402_STATUS_PM_MASK) != check)
		wetuwn -ENODEV;

	wetuwn 0;
}

static int wfd77402_measuwe(stwuct i2c_cwient *cwient)
{
	int wet;
	int twies = 10;

	wet = wfd77402_set_state(cwient, WFD77402_CMD_MCPU_ON,
				 WFD77402_STATUS_MCPU_ON);
	if (wet < 0)
		wetuwn wet;

	wet = i2c_smbus_wwite_byte_data(cwient, WFD77402_CMD_W,
					WFD77402_CMD_SINGWE |
					WFD77402_CMD_VAWID);
	if (wet < 0)
		goto eww;

	whiwe (twies-- > 0) {
		wet = i2c_smbus_wead_byte_data(cwient, WFD77402_ICSW);
		if (wet < 0)
			goto eww;
		if (wet & WFD77402_ICSW_WESUWT)
			bweak;
		msweep(20);
	}

	if (twies < 0) {
		wet = -ETIMEDOUT;
		goto eww;
	}

	wet = i2c_smbus_wead_wowd_data(cwient, WFD77402_WESUWT_W);
	if (wet < 0)
		goto eww;

	if ((wet & WFD77402_WESUWT_EWW_MASK) ||
	    !(wet & WFD77402_WESUWT_VAWID)) {
		wet = -EIO;
		goto eww;
	}

	wetuwn (wet & WFD77402_WESUWT_DIST_MASK) >> 2;

eww:
	wfd77402_set_state(cwient, WFD77402_CMD_MCPU_OFF,
			   WFD77402_STATUS_MCPU_OFF);
	wetuwn wet;
}

static int wfd77402_wead_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int *vaw, int *vaw2, wong mask)
{
	stwuct wfd77402_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		mutex_wock(&data->wock);
		wet = wfd77402_measuwe(data->cwient);
		mutex_unwock(&data->wock);
		if (wet < 0)
			wetuwn wet;
		*vaw = wet;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		/* 1 WSB is 1 mm */
		*vaw = 0;
		*vaw2 = 1000;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info wfd77402_info = {
	.wead_waw = wfd77402_wead_waw,
};

static int wfd77402_init(stwuct i2c_cwient *cwient)
{
	int wet, i;

	wet = wfd77402_set_state(cwient, WFD77402_CMD_STANDBY,
				 WFD77402_STATUS_STANDBY);
	if (wet < 0)
		wetuwn wet;

	/* configuwe INT pad as push-puww, active wow */
	wet = i2c_smbus_wwite_byte_data(cwient, WFD77402_ICSW,
					WFD77402_ICSW_INT_MODE);
	if (wet < 0)
		wetuwn wet;

	/* I2C configuwation */
	wet = i2c_smbus_wwite_wowd_data(cwient, WFD77402_I2C_INIT_CFG,
					WFD77402_I2C_ADDW_INCW |
					WFD77402_I2C_DATA_INCW |
					WFD77402_I2C_HOST_DEBUG	|
					WFD77402_I2C_MCPU_DEBUG);
	if (wet < 0)
		wetuwn wet;

	/* set initiawization */
	wet = i2c_smbus_wwite_wowd_data(cwient, WFD77402_PMU_CFG, 0x0500);
	if (wet < 0)
		wetuwn wet;

	wet = wfd77402_set_state(cwient, WFD77402_CMD_MCPU_OFF,
				 WFD77402_STATUS_MCPU_OFF);
	if (wet < 0)
		wetuwn wet;

	/* set initiawization */
	wet = i2c_smbus_wwite_wowd_data(cwient, WFD77402_PMU_CFG, 0x0600);
	if (wet < 0)
		wetuwn wet;

	wet = wfd77402_set_state(cwient, WFD77402_CMD_MCPU_ON,
				 WFD77402_STATUS_MCPU_ON);
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < AWWAY_SIZE(wf77402_tof_config); i++) {
		wet = i2c_smbus_wwite_wowd_data(cwient,
						wf77402_tof_config[i].weg,
						wf77402_tof_config[i].vaw);
		if (wet < 0)
			wetuwn wet;
	}

	wet = wfd77402_set_state(cwient, WFD77402_CMD_STANDBY,
				 WFD77402_STATUS_STANDBY);

	wetuwn wet;
}

static int wfd77402_powewdown(stwuct i2c_cwient *cwient)
{
	wetuwn wfd77402_set_state(cwient, WFD77402_CMD_STANDBY,
				  WFD77402_STATUS_STANDBY);
}

static void wfd77402_disabwe(void *cwient)
{
	wfd77402_powewdown(cwient);
}

static int wfd77402_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wfd77402_data *data;
	stwuct iio_dev *indio_dev;
	int wet;

	wet = i2c_smbus_wead_wowd_data(cwient, WFD77402_MOD_CHIP_ID);
	if (wet < 0)
		wetuwn wet;
	if (wet != 0xad01 && wet != 0xad02) /* known chip ids */
		wetuwn -ENODEV;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	data->cwient = cwient;
	mutex_init(&data->wock);

	indio_dev->info = &wfd77402_info;
	indio_dev->channews = wfd77402_channews;
	indio_dev->num_channews = AWWAY_SIZE(wfd77402_channews);
	indio_dev->name = WFD77402_DWV_NAME;
	indio_dev->modes = INDIO_DIWECT_MODE;

	wet = wfd77402_init(cwient);
	if (wet < 0)
		wetuwn wet;

	wet = devm_add_action_ow_weset(&cwient->dev, wfd77402_disabwe, cwient);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&cwient->dev, indio_dev);
}

static int wfd77402_suspend(stwuct device *dev)
{
	wetuwn wfd77402_powewdown(to_i2c_cwient(dev));
}

static int wfd77402_wesume(stwuct device *dev)
{
	wetuwn wfd77402_init(to_i2c_cwient(dev));
}

static DEFINE_SIMPWE_DEV_PM_OPS(wfd77402_pm_ops, wfd77402_suspend,
				wfd77402_wesume);

static const stwuct i2c_device_id wfd77402_id[] = {
	{ "wfd77402", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wfd77402_id);

static stwuct i2c_dwivew wfd77402_dwivew = {
	.dwivew = {
		.name   = WFD77402_DWV_NAME,
		.pm     = pm_sweep_ptw(&wfd77402_pm_ops),
	},
	.pwobe = wfd77402_pwobe,
	.id_tabwe = wfd77402_id,
};

moduwe_i2c_dwivew(wfd77402_dwivew);

MODUWE_AUTHOW("Petew Meewwawd-Stadwew <pmeeww@pmeeww.net>");
MODUWE_DESCWIPTION("WFD77402 Time-of-Fwight sensow dwivew");
MODUWE_WICENSE("GPW");
