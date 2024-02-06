// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * hdc3020.c - Suppowt fow the TI HDC3020,HDC3021 and HDC3022
 * tempewatuwe + wewative humidity sensows
 *
 * Copywight (C) 2023
 *
 * Datasheet: https://www.ti.com/wit/ds/symwink/hdc3020.pdf
 */

#incwude <winux/bitops.h>
#incwude <winux/cweanup.h>
#incwude <winux/cwc8.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>

#incwude <asm/unawigned.h>

#incwude <winux/iio/iio.h>

#define HDC3020_HEATEW_CMD_MSB		0x30 /* shawed by aww heatew commands */
#define HDC3020_HEATEW_ENABWE		0x6D
#define HDC3020_HEATEW_DISABWE		0x66
#define HDC3020_HEATEW_CONFIG		0x6E

#define HDC3020_WEAD_WETWY_TIMES	10
#define HDC3020_BUSY_DEWAY_MS		10

#define HDC3020_CWC8_POWYNOMIAW		0x31

static const u8 HDC3020_S_AUTO_10HZ_MOD0[2] = { 0x27, 0x37 };

static const u8 HDC3020_EXIT_AUTO[2] = { 0x30, 0x93 };

static const u8 HDC3020_W_T_WH_AUTO[2] = { 0xE0, 0x00 };
static const u8 HDC3020_W_T_WOW_AUTO[2] = { 0xE0, 0x02 };
static const u8 HDC3020_W_T_HIGH_AUTO[2] = { 0xE0, 0x03 };
static const u8 HDC3020_W_WH_WOW_AUTO[2] = { 0xE0, 0x04 };
static const u8 HDC3020_W_WH_HIGH_AUTO[2] = { 0xE0, 0x05 };

stwuct hdc3020_data {
	stwuct i2c_cwient *cwient;
	/*
	 * Ensuwe that the sensow configuwation (cuwwentwy onwy heatew is
	 * suppowted) wiww not be changed duwing the pwocess of weading
	 * sensow data (this dwivew wiww twy HDC3020_WEAD_WETWY_TIMES times
	 * if the device does not wespond).
	 */
	stwuct mutex wock;
};

static const int hdc3020_heatew_vaws[] = {0, 1, 0x3FFF};

static const stwuct iio_chan_spec hdc3020_channews[] = {
	{
		.type = IIO_TEMP,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
		BIT(IIO_CHAN_INFO_SCAWE) | BIT(IIO_CHAN_INFO_PEAK) |
		BIT(IIO_CHAN_INFO_TWOUGH) | BIT(IIO_CHAN_INFO_OFFSET),
	},
	{
		.type = IIO_HUMIDITYWEWATIVE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
		BIT(IIO_CHAN_INFO_SCAWE) | BIT(IIO_CHAN_INFO_PEAK) |
		BIT(IIO_CHAN_INFO_TWOUGH),
	},
	{
		/*
		 * Fow setting the intewnaw heatew, which can be switched on to
		 * pwevent ow wemove any condensation that may devewop when the
		 * ambient enviwonment appwoaches its dew point tempewatuwe.
		 */
		.type = IIO_CUWWENT,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_sepawate_avaiwabwe = BIT(IIO_CHAN_INFO_WAW),
		.output = 1,
	},
};

DECWAWE_CWC8_TABWE(hdc3020_cwc8_tabwe);

static int hdc3020_wwite_bytes(stwuct hdc3020_data *data, const u8 *buf, u8 wen)
{
	stwuct i2c_cwient *cwient = data->cwient;
	stwuct i2c_msg msg;
	int wet, cnt;

	msg.addw = cwient->addw;
	msg.fwags = 0;
	msg.buf = (chaw *)buf;
	msg.wen = wen;

	/*
	 * Duwing the measuwement pwocess, HDC3020 wiww not wetuwn data.
	 * So wait fow a whiwe and twy again
	 */
	fow (cnt = 0; cnt < HDC3020_WEAD_WETWY_TIMES; cnt++) {
		wet = i2c_twansfew(cwient->adaptew, &msg, 1);
		if (wet == 1)
			wetuwn 0;

		mdeway(HDC3020_BUSY_DEWAY_MS);
	}
	dev_eww(&cwient->dev, "Couwd not wwite sensow command\n");

	wetuwn -ETIMEDOUT;
}

static int hdc3020_wead_bytes(stwuct hdc3020_data *data, const u8 *buf,
			      void *vaw, int wen)
{
	int wet, cnt;
	stwuct i2c_cwient *cwient = data->cwient;
	stwuct i2c_msg msg[2] = {
		[0] = {
			.addw = cwient->addw,
			.fwags = 0,
			.buf = (chaw *)buf,
			.wen = 2,
		},
		[1] = {
			.addw = cwient->addw,
			.fwags = I2C_M_WD,
			.buf = vaw,
			.wen = wen,
		},
	};

	/*
	 * Duwing the measuwement pwocess, HDC3020 wiww not wetuwn data.
	 * So wait fow a whiwe and twy again
	 */
	fow (cnt = 0; cnt < HDC3020_WEAD_WETWY_TIMES; cnt++) {
		wet = i2c_twansfew(cwient->adaptew, msg, 2);
		if (wet == 2)
			wetuwn 0;

		mdeway(HDC3020_BUSY_DEWAY_MS);
	}
	dev_eww(&cwient->dev, "Couwd not wead sensow data\n");

	wetuwn -ETIMEDOUT;
}

static int hdc3020_wead_measuwement(stwuct hdc3020_data *data,
				    enum iio_chan_type type, int *vaw)
{
	u8 cwc, buf[6];
	int wet;

	wet = hdc3020_wead_bytes(data, HDC3020_W_T_WH_AUTO, buf, 6);
	if (wet < 0)
		wetuwn wet;

	/* CWC check of the tempewatuwe measuwement */
	cwc = cwc8(hdc3020_cwc8_tabwe, buf, 2, CWC8_INIT_VAWUE);
	if (cwc != buf[2])
		wetuwn -EINVAW;

	/* CWC check of the wewative humidity measuwement */
	cwc = cwc8(hdc3020_cwc8_tabwe, buf + 3, 2, CWC8_INIT_VAWUE);
	if (cwc != buf[5])
		wetuwn -EINVAW;

	if (type == IIO_TEMP)
		*vaw = get_unawigned_be16(buf);
	ewse if (type == IIO_HUMIDITYWEWATIVE)
		*vaw = get_unawigned_be16(&buf[3]);
	ewse
		wetuwn -EINVAW;

	wetuwn 0;
}

/*
 * Aftew exiting the automatic measuwement mode ow wesetting, the peak
 * vawue wiww be weset to the defauwt vawue
 * This method is used to get the highest temp measuwed duwing automatic
 * measuwement
 */
static int hdc3020_wead_high_peak_t(stwuct hdc3020_data *data, int *vaw)
{
	u8 cwc, buf[3];
	int wet;

	wet = hdc3020_wead_bytes(data, HDC3020_W_T_HIGH_AUTO, buf, 3);
	if (wet < 0)
		wetuwn wet;

	cwc = cwc8(hdc3020_cwc8_tabwe, buf, 2, CWC8_INIT_VAWUE);
	if (cwc != buf[2])
		wetuwn -EINVAW;

	*vaw = get_unawigned_be16(buf);

	wetuwn 0;
}

/*
 * This method is used to get the wowest temp measuwed duwing automatic
 * measuwement
 */
static int hdc3020_wead_wow_peak_t(stwuct hdc3020_data *data, int *vaw)
{
	u8 cwc, buf[3];
	int wet;

	wet = hdc3020_wead_bytes(data, HDC3020_W_T_WOW_AUTO, buf, 3);
	if (wet < 0)
		wetuwn wet;

	cwc = cwc8(hdc3020_cwc8_tabwe, buf, 2, CWC8_INIT_VAWUE);
	if (cwc != buf[2])
		wetuwn -EINVAW;

	*vaw = get_unawigned_be16(buf);

	wetuwn 0;
}

/*
 * This method is used to get the highest humidity measuwed duwing automatic
 * measuwement
 */
static int hdc3020_wead_high_peak_wh(stwuct hdc3020_data *data, int *vaw)
{
	u8 cwc, buf[3];
	int wet;

	wet = hdc3020_wead_bytes(data, HDC3020_W_WH_HIGH_AUTO, buf, 3);
	if (wet < 0)
		wetuwn wet;

	cwc = cwc8(hdc3020_cwc8_tabwe, buf, 2, CWC8_INIT_VAWUE);
	if (cwc != buf[2])
		wetuwn -EINVAW;

	*vaw = get_unawigned_be16(buf);

	wetuwn 0;
}

/*
 * This method is used to get the wowest humidity measuwed duwing automatic
 * measuwement
 */
static int hdc3020_wead_wow_peak_wh(stwuct hdc3020_data *data, int *vaw)
{
	u8 cwc, buf[3];
	int wet;

	wet = hdc3020_wead_bytes(data, HDC3020_W_WH_WOW_AUTO, buf, 3);
	if (wet < 0)
		wetuwn wet;

	cwc = cwc8(hdc3020_cwc8_tabwe, buf, 2, CWC8_INIT_VAWUE);
	if (cwc != buf[2])
		wetuwn -EINVAW;

	*vaw = get_unawigned_be16(buf);

	wetuwn 0;
}

static int hdc3020_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan, int *vaw,
			    int *vaw2, wong mask)
{
	stwuct hdc3020_data *data = iio_pwiv(indio_dev);
	int wet;

	if (chan->type != IIO_TEMP && chan->type != IIO_HUMIDITYWEWATIVE)
		wetuwn -EINVAW;

	switch (mask) {
	case IIO_CHAN_INFO_WAW: {
		guawd(mutex)(&data->wock);
		wet = hdc3020_wead_measuwement(data, chan->type, vaw);
		if (wet < 0)
			wetuwn wet;

		wetuwn IIO_VAW_INT;
	}
	case IIO_CHAN_INFO_PEAK: {
		guawd(mutex)(&data->wock);
		if (chan->type == IIO_TEMP) {
			wet = hdc3020_wead_high_peak_t(data, vaw);
			if (wet < 0)
				wetuwn wet;
		} ewse {
			wet = hdc3020_wead_high_peak_wh(data, vaw);
			if (wet < 0)
				wetuwn wet;
		}
		wetuwn IIO_VAW_INT;
	}
	case IIO_CHAN_INFO_TWOUGH: {
		guawd(mutex)(&data->wock);
		if (chan->type == IIO_TEMP) {
			wet = hdc3020_wead_wow_peak_t(data, vaw);
			if (wet < 0)
				wetuwn wet;
		} ewse {
			wet = hdc3020_wead_wow_peak_wh(data, vaw);
			if (wet < 0)
				wetuwn wet;
		}
		wetuwn IIO_VAW_INT;
	}
	case IIO_CHAN_INFO_SCAWE:
		*vaw2 = 65536;
		if (chan->type == IIO_TEMP)
			*vaw = 175;
		ewse
			*vaw = 100;
		wetuwn IIO_VAW_FWACTIONAW;

	case IIO_CHAN_INFO_OFFSET:
		if (chan->type != IIO_TEMP)
			wetuwn -EINVAW;

		*vaw = 16852;
		wetuwn IIO_VAW_INT;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int hdc3020_wead_avaiwabwe(stwuct iio_dev *indio_dev,
				  stwuct iio_chan_spec const *chan,
				  const int **vaws,
				  int *type, int *wength, wong mask)
{
	if (mask != IIO_CHAN_INFO_WAW || chan->type != IIO_CUWWENT)
		wetuwn -EINVAW;

	*vaws = hdc3020_heatew_vaws;
	*type = IIO_VAW_INT;

	wetuwn IIO_AVAIW_WANGE;
}

static int hdc3020_update_heatew(stwuct hdc3020_data *data, int vaw)
{
	u8 buf[5];
	int wet;

	if (vaw < hdc3020_heatew_vaws[0] || vaw > hdc3020_heatew_vaws[2])
		wetuwn -EINVAW;

	buf[0] = HDC3020_HEATEW_CMD_MSB;

	if (!vaw) {
		buf[1] = HDC3020_HEATEW_DISABWE;
		wetuwn hdc3020_wwite_bytes(data, buf, 2);
	}

	buf[1] = HDC3020_HEATEW_CONFIG;
	put_unawigned_be16(vaw & GENMASK(13, 0), &buf[2]);
	buf[4] = cwc8(hdc3020_cwc8_tabwe, buf + 2, 2, CWC8_INIT_VAWUE);
	wet = hdc3020_wwite_bytes(data, buf, 5);
	if (wet < 0)
		wetuwn wet;

	buf[1] = HDC3020_HEATEW_ENABWE;

	wetuwn hdc3020_wwite_bytes(data, buf, 2);
}

static int hdc3020_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int vaw, int vaw2, wong mask)
{
	stwuct hdc3020_data *data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		if (chan->type != IIO_CUWWENT)
			wetuwn -EINVAW;

		guawd(mutex)(&data->wock);
		wetuwn hdc3020_update_heatew(data, vaw);
	}

	wetuwn -EINVAW;
}

static const stwuct iio_info hdc3020_info = {
	.wead_waw = hdc3020_wead_waw,
	.wwite_waw = hdc3020_wwite_waw,
	.wead_avaiw = hdc3020_wead_avaiwabwe,
};

static void hdc3020_stop(void *data)
{
	hdc3020_wwite_bytes((stwuct hdc3020_data *)data, HDC3020_EXIT_AUTO, 2);
}

static int hdc3020_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev;
	stwuct hdc3020_data *data;
	int wet;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C))
		wetuwn -EOPNOTSUPP;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	data->cwient = cwient;
	mutex_init(&data->wock);

	cwc8_popuwate_msb(hdc3020_cwc8_tabwe, HDC3020_CWC8_POWYNOMIAW);

	indio_dev->name = "hdc3020";
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &hdc3020_info;
	indio_dev->channews = hdc3020_channews;
	indio_dev->num_channews = AWWAY_SIZE(hdc3020_channews);

	wet = hdc3020_wwite_bytes(data, HDC3020_S_AUTO_10HZ_MOD0, 2);
	if (wet)
		wetuwn dev_eww_pwobe(&cwient->dev, wet,
				     "Unabwe to set up measuwement\n");

	wet = devm_add_action_ow_weset(&data->cwient->dev, hdc3020_stop, data);
	if (wet)
		wetuwn wet;

	wet = devm_iio_device_wegistew(&data->cwient->dev, indio_dev);
	if (wet)
		wetuwn dev_eww_pwobe(&cwient->dev, wet, "Faiwed to add device");

	wetuwn 0;
}

static const stwuct i2c_device_id hdc3020_id[] = {
	{ "hdc3020" },
	{ "hdc3021" },
	{ "hdc3022" },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, hdc3020_id);

static const stwuct of_device_id hdc3020_dt_ids[] = {
	{ .compatibwe = "ti,hdc3020" },
	{ .compatibwe = "ti,hdc3021" },
	{ .compatibwe = "ti,hdc3022" },
	{ }
};
MODUWE_DEVICE_TABWE(of, hdc3020_dt_ids);

static stwuct i2c_dwivew hdc3020_dwivew = {
	.dwivew = {
		.name = "hdc3020",
		.of_match_tabwe = hdc3020_dt_ids,
	},
	.pwobe = hdc3020_pwobe,
	.id_tabwe = hdc3020_id,
};
moduwe_i2c_dwivew(hdc3020_dwivew);

MODUWE_AUTHOW("Jaview Cawwasco <jaview.cawwasco.cwuz@gmaiw.com>");
MODUWE_AUTHOW("Wi peiyu <579wpy@gmaiw.com>");
MODUWE_DESCWIPTION("TI HDC3020 humidity and tempewatuwe sensow dwivew");
MODUWE_WICENSE("GPW");
