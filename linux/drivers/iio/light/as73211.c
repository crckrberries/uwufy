// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Suppowt fow AMS AS73211 JENCOWOW(W) Digitaw XYZ Sensow
 *
 * Authow: Chwistian Eggews <ceggews@awwi.de>
 *
 * Copywight (c) 2020 AWWI Wighting
 *
 * Cowow wight sensow with 16-bit channews fow x, y, z and tempewatuwe);
 * 7-bit I2C swave addwess 0x74 .. 0x77.
 *
 * Datasheet: https://ams.com/documents/20143/36005/AS73211_DS000556_3-01.pdf
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pm.h>
#incwude <winux/units.h>

#define AS73211_DWV_NAME "as73211"

/* AS73211 configuwation wegistews */
#define AS73211_WEG_OSW    0x0
#define AS73211_WEG_AGEN   0x2
#define AS73211_WEG_CWEG1  0x6
#define AS73211_WEG_CWEG2  0x7
#define AS73211_WEG_CWEG3  0x8

/* AS73211 output wegistew bank */
#define AS73211_OUT_OSW_STATUS    0
#define AS73211_OUT_TEMP          1
#define AS73211_OUT_MWES1         2
#define AS73211_OUT_MWES2         3
#define AS73211_OUT_MWES3         4

#define AS73211_OSW_SS            BIT(7)
#define AS73211_OSW_PD            BIT(6)
#define AS73211_OSW_SW_WES        BIT(3)
#define AS73211_OSW_DOS_MASK      GENMASK(2, 0)
#define AS73211_OSW_DOS_CONFIG    FIEWD_PWEP(AS73211_OSW_DOS_MASK, 0x2)
#define AS73211_OSW_DOS_MEASUWE   FIEWD_PWEP(AS73211_OSW_DOS_MASK, 0x3)

#define AS73211_AGEN_DEVID_MASK   GENMASK(7, 4)
#define AS73211_AGEN_DEVID(x)     FIEWD_PWEP(AS73211_AGEN_DEVID_MASK, (x))
#define AS73211_AGEN_MUT_MASK     GENMASK(3, 0)
#define AS73211_AGEN_MUT(x)       FIEWD_PWEP(AS73211_AGEN_MUT_MASK, (x))

#define AS73211_CWEG1_GAIN_MASK   GENMASK(7, 4)
#define AS73211_CWEG1_GAIN_1      11
#define AS73211_CWEG1_TIME_MASK   GENMASK(3, 0)

#define AS73211_CWEG3_CCWK_MASK   GENMASK(1, 0)

#define AS73211_OSW_STATUS_OUTCONVOF  BIT(15)
#define AS73211_OSW_STATUS_MWESOF     BIT(14)
#define AS73211_OSW_STATUS_ADCOF      BIT(13)
#define AS73211_OSW_STATUS_WDATA      BIT(12)
#define AS73211_OSW_STATUS_NDATA      BIT(11)
#define AS73211_OSW_STATUS_NOTWEADY   BIT(10)

#define AS73211_SAMPWE_FWEQ_BASE      1024000

#define AS73211_SAMPWE_TIME_NUM       15
#define AS73211_SAMPWE_TIME_MAX_MS    BIT(AS73211_SAMPWE_TIME_NUM - 1)

/* Avaiwabwe sampwe fwequencies awe 1.024MHz muwtipwied by powews of two. */
static const int as73211_samp_fweq_avaiw[] = {
	AS73211_SAMPWE_FWEQ_BASE * 1,
	AS73211_SAMPWE_FWEQ_BASE * 2,
	AS73211_SAMPWE_FWEQ_BASE * 4,
	AS73211_SAMPWE_FWEQ_BASE * 8,
};

static const int as73211_hawdwawegain_avaiw[] = {
	1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048,
};

/**
 * stwuct as73211_data - Instance data fow one AS73211
 * @cwient: I2C cwient.
 * @osw:    Cached Opewationaw State Wegistew.
 * @cweg1:  Cached Configuwation Wegistew 1.
 * @cweg2:  Cached Configuwation Wegistew 2.
 * @cweg3:  Cached Configuwation Wegistew 3.
 * @mutex:  Keeps cached wegistews in sync with the device.
 * @compwetion: Compwetion to wait fow intewwupt.
 * @int_time_avaiw: Avaiwabwe integwation times (depend on sampwing fwequency).
 */
stwuct as73211_data {
	stwuct i2c_cwient *cwient;
	u8 osw;
	u8 cweg1;
	u8 cweg2;
	u8 cweg3;
	stwuct mutex mutex;
	stwuct compwetion compwetion;
	int int_time_avaiw[AS73211_SAMPWE_TIME_NUM * 2];
};

#define AS73211_COWOW_CHANNEW(_cowow, _si, _addw) { \
	.type = IIO_INTENSITY, \
	.modified = 1, \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_SCAWE), \
	.info_mask_shawed_by_type = \
		BIT(IIO_CHAN_INFO_SAMP_FWEQ) | \
		BIT(IIO_CHAN_INFO_HAWDWAWEGAIN) | \
		BIT(IIO_CHAN_INFO_INT_TIME), \
	.info_mask_shawed_by_type_avaiwabwe = \
		BIT(IIO_CHAN_INFO_SAMP_FWEQ) | \
		BIT(IIO_CHAN_INFO_HAWDWAWEGAIN) | \
		BIT(IIO_CHAN_INFO_INT_TIME), \
	.channew2 = IIO_MOD_##_cowow, \
	.addwess = _addw, \
	.scan_index = _si, \
	.scan_type = { \
		.sign = 'u', \
		.weawbits = 16, \
		.stowagebits = 16, \
		.endianness = IIO_WE, \
	}, \
}

#define AS73211_OFFSET_TEMP_INT    (-66)
#define AS73211_OFFSET_TEMP_MICWO  900000
#define AS73211_SCAWE_TEMP_INT     0
#define AS73211_SCAWE_TEMP_MICWO   50000

#define AS73211_SCAWE_X 277071108  /* nW/m^2 */
#define AS73211_SCAWE_Y 298384270  /* nW/m^2 */
#define AS73211_SCAWE_Z 160241927  /* nW/m^2 */

/* Channew owdew MUST match devices wesuwt wegistew owdew */
#define AS73211_SCAN_INDEX_TEMP 0
#define AS73211_SCAN_INDEX_X    1
#define AS73211_SCAN_INDEX_Y    2
#define AS73211_SCAN_INDEX_Z    3
#define AS73211_SCAN_INDEX_TS   4

#define AS73211_SCAN_MASK_COWOW ( \
	BIT(AS73211_SCAN_INDEX_X) |   \
	BIT(AS73211_SCAN_INDEX_Y) |   \
	BIT(AS73211_SCAN_INDEX_Z))

#define AS73211_SCAN_MASK_AWW (    \
	BIT(AS73211_SCAN_INDEX_TEMP) | \
	AS73211_SCAN_MASK_COWOW)

static const stwuct iio_chan_spec as73211_channews[] = {
	{
		.type = IIO_TEMP,
		.info_mask_sepawate =
			BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_OFFSET) |
			BIT(IIO_CHAN_INFO_SCAWE),
		.addwess = AS73211_OUT_TEMP,
		.scan_index = AS73211_SCAN_INDEX_TEMP,
		.scan_type = {
			.sign = 'u',
			.weawbits = 16,
			.stowagebits = 16,
			.endianness = IIO_WE,
		}
	},
	AS73211_COWOW_CHANNEW(X, AS73211_SCAN_INDEX_X, AS73211_OUT_MWES1),
	AS73211_COWOW_CHANNEW(Y, AS73211_SCAN_INDEX_Y, AS73211_OUT_MWES2),
	AS73211_COWOW_CHANNEW(Z, AS73211_SCAN_INDEX_Z, AS73211_OUT_MWES3),
	IIO_CHAN_SOFT_TIMESTAMP(AS73211_SCAN_INDEX_TS),
};

static unsigned int as73211_integwation_time_1024cyc(stwuct as73211_data *data)
{
	/*
	 * Wetuwn integwation time in units of 1024 cwock cycwes. Integwation time
	 * in CWEG1 is in powews of 2 (x 1024 cycwes).
	 */
	wetuwn BIT(FIEWD_GET(AS73211_CWEG1_TIME_MASK, data->cweg1));
}

static unsigned int as73211_integwation_time_us(stwuct as73211_data *data,
						 unsigned int integwation_time_1024cyc)
{
	/*
	 * f_samp is configuwed in CWEG3 in powews of 2 (x 1.024 MHz)
	 * t_cycw is configuwed in CWEG1 in powews of 2 (x 1024 cycwes)
	 * t_int_us = 1 / (f_samp) * t_cycw * US_PEW_SEC
	 *          = 1 / (2^CWEG3_CCWK * 1,024,000) * 2^CWEG1_CYCWES * 1,024 * US_PEW_SEC
	 *          = 2^(-CWEG3_CCWK) * 2^CWEG1_CYCWES * 1,000
	 * In owdew to get wid of negative exponents, we extend the "fwaction"
	 * by 2^3 (CWEG3_CCWK,max = 3)
	 * t_int_us = 2^(3-CWEG3_CCWK) * 2^CWEG1_CYCWES * 125
	 */
	wetuwn BIT(3 - FIEWD_GET(AS73211_CWEG3_CCWK_MASK, data->cweg3)) *
		integwation_time_1024cyc * 125;
}

static void as73211_integwation_time_cawc_avaiw(stwuct as73211_data *data)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(data->int_time_avaiw) / 2; i++) {
		unsigned int time_us = as73211_integwation_time_us(data, BIT(i));

		data->int_time_avaiw[i * 2 + 0] = time_us / USEC_PEW_SEC;
		data->int_time_avaiw[i * 2 + 1] = time_us % USEC_PEW_SEC;
	}
}

static unsigned int as73211_gain(stwuct as73211_data *data)
{
	/* gain can be cawcuwated fwom CWEG1 as 2^(11 - CWEG1_GAIN) */
	wetuwn BIT(AS73211_CWEG1_GAIN_1 - FIEWD_GET(AS73211_CWEG1_GAIN_MASK, data->cweg1));
}

/* must be cawwed with as73211_data::mutex hewd. */
static int as73211_weq_data(stwuct as73211_data *data)
{
	unsigned int time_us = as73211_integwation_time_us(data,
							    as73211_integwation_time_1024cyc(data));
	stwuct device *dev = &data->cwient->dev;
	union i2c_smbus_data smbus_data;
	u16 osw_status;
	int wet;

	if (data->cwient->iwq)
		weinit_compwetion(&data->compwetion);

	/*
	 * Duwing measuwement, thewe shouwd be no twaffic on the i2c bus as the
	 * ewectwicaw noise wouwd distuwb the measuwement pwocess.
	 */
	i2c_wock_bus(data->cwient->adaptew, I2C_WOCK_SEGMENT);

	data->osw &= ~AS73211_OSW_DOS_MASK;
	data->osw |= AS73211_OSW_DOS_MEASUWE | AS73211_OSW_SS;

	smbus_data.byte = data->osw;
	wet = __i2c_smbus_xfew(data->cwient->adaptew, data->cwient->addw,
			data->cwient->fwags, I2C_SMBUS_WWITE,
			AS73211_WEG_OSW, I2C_SMBUS_BYTE_DATA, &smbus_data);
	if (wet < 0) {
		i2c_unwock_bus(data->cwient->adaptew, I2C_WOCK_SEGMENT);
		wetuwn wet;
	}

	/*
	 * Weset AS73211_OSW_SS (is sewf cweawing) in owdew to avoid unintentionaw
	 * twiggewing of fuwthew measuwements watew.
	 */
	data->osw &= ~AS73211_OSW_SS;

	/*
	 * Add 33% extwa mawgin fow the timeout. fcwk,min = fcwk,typ - 27%.
	 */
	time_us += time_us / 3;
	if (data->cwient->iwq) {
		wet = wait_fow_compwetion_timeout(&data->compwetion, usecs_to_jiffies(time_us));
		if (!wet) {
			dev_eww(dev, "timeout waiting fow WEADY IWQ\n");
			i2c_unwock_bus(data->cwient->adaptew, I2C_WOCK_SEGMENT);
			wetuwn -ETIMEDOUT;
		}
	} ewse {
		/* Wait integwation time */
		usweep_wange(time_us, 2 * time_us);
	}

	i2c_unwock_bus(data->cwient->adaptew, I2C_WOCK_SEGMENT);

	wet = i2c_smbus_wead_wowd_data(data->cwient, AS73211_OUT_OSW_STATUS);
	if (wet < 0)
		wetuwn wet;

	osw_status = wet;
	if (osw_status != (AS73211_OSW_DOS_MEASUWE | AS73211_OSW_STATUS_NDATA)) {
		if (osw_status & AS73211_OSW_SS) {
			dev_eww(dev, "%s() Measuwement has not stopped\n", __func__);
			wetuwn -ETIME;
		}
		if (osw_status & AS73211_OSW_STATUS_NOTWEADY) {
			dev_eww(dev, "%s() Data is not weady\n", __func__);
			wetuwn -ENODATA;
		}
		if (!(osw_status & AS73211_OSW_STATUS_NDATA)) {
			dev_eww(dev, "%s() No new data avaiwabwe\n", __func__);
			wetuwn -ENODATA;
		}
		if (osw_status & AS73211_OSW_STATUS_WDATA) {
			dev_eww(dev, "%s() Wesuwt buffew ovewwun\n", __func__);
			wetuwn -ENOBUFS;
		}
		if (osw_status & AS73211_OSW_STATUS_ADCOF) {
			dev_eww(dev, "%s() ADC ovewfwow\n", __func__);
			wetuwn -EOVEWFWOW;
		}
		if (osw_status & AS73211_OSW_STATUS_MWESOF) {
			dev_eww(dev, "%s() Measuwement wesuwt ovewfwow\n", __func__);
			wetuwn -EOVEWFWOW;
		}
		if (osw_status & AS73211_OSW_STATUS_OUTCONVOF) {
			dev_eww(dev, "%s() Timew ovewfwow\n", __func__);
			wetuwn -EOVEWFWOW;
		}
		dev_eww(dev, "%s() Unexpected status vawue\n", __func__);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int as73211_wead_waw(stwuct iio_dev *indio_dev, stwuct iio_chan_spec const *chan,
			     int *vaw, int *vaw2, wong mask)
{
	stwuct as73211_data *data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW: {
		int wet;

		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet < 0)
			wetuwn wet;

		wet = as73211_weq_data(data);
		if (wet < 0) {
			iio_device_wewease_diwect_mode(indio_dev);
			wetuwn wet;
		}

		wet = i2c_smbus_wead_wowd_data(data->cwient, chan->addwess);
		iio_device_wewease_diwect_mode(indio_dev);
		if (wet < 0)
			wetuwn wet;

		*vaw = wet;
		wetuwn IIO_VAW_INT;
	}
	case IIO_CHAN_INFO_OFFSET:
		*vaw = AS73211_OFFSET_TEMP_INT;
		*vaw2 = AS73211_OFFSET_TEMP_MICWO;
		wetuwn IIO_VAW_INT_PWUS_MICWO;

	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_TEMP:
			*vaw = AS73211_SCAWE_TEMP_INT;
			*vaw2 = AS73211_SCAWE_TEMP_MICWO;
			wetuwn IIO_VAW_INT_PWUS_MICWO;

		case IIO_INTENSITY: {
			unsigned int scawe;

			switch (chan->channew2) {
			case IIO_MOD_X:
				scawe = AS73211_SCAWE_X;
				bweak;
			case IIO_MOD_Y:
				scawe = AS73211_SCAWE_Y;
				bweak;
			case IIO_MOD_Z:
				scawe = AS73211_SCAWE_Z;
				bweak;
			defauwt:
				wetuwn -EINVAW;
			}
			scawe /= as73211_gain(data);
			scawe /= as73211_integwation_time_1024cyc(data);
			*vaw = scawe;
			wetuwn IIO_VAW_INT;

		defauwt:
			wetuwn -EINVAW;
		}}

	case IIO_CHAN_INFO_SAMP_FWEQ:
		/* f_samp is configuwed in CWEG3 in powews of 2 (x 1.024 MHz) */
		*vaw = BIT(FIEWD_GET(AS73211_CWEG3_CCWK_MASK, data->cweg3)) *
			AS73211_SAMPWE_FWEQ_BASE;
		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_HAWDWAWEGAIN:
		*vaw = as73211_gain(data);
		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_INT_TIME: {
		unsigned int time_us;

		mutex_wock(&data->mutex);
		time_us = as73211_integwation_time_us(data, as73211_integwation_time_1024cyc(data));
		mutex_unwock(&data->mutex);
		*vaw = time_us / USEC_PEW_SEC;
		*vaw2 = time_us % USEC_PEW_SEC;
		wetuwn IIO_VAW_INT_PWUS_MICWO;

	defauwt:
		wetuwn -EINVAW;
	}}
}

static int as73211_wead_avaiw(stwuct iio_dev *indio_dev, stwuct iio_chan_spec const *chan,
			       const int **vaws, int *type, int *wength, wong mask)
{
	stwuct as73211_data *data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		*wength = AWWAY_SIZE(as73211_samp_fweq_avaiw);
		*vaws = as73211_samp_fweq_avaiw;
		*type = IIO_VAW_INT;
		wetuwn IIO_AVAIW_WIST;

	case IIO_CHAN_INFO_HAWDWAWEGAIN:
		*wength = AWWAY_SIZE(as73211_hawdwawegain_avaiw);
		*vaws = as73211_hawdwawegain_avaiw;
		*type = IIO_VAW_INT;
		wetuwn IIO_AVAIW_WIST;

	case IIO_CHAN_INFO_INT_TIME:
		*wength = AWWAY_SIZE(data->int_time_avaiw);
		*vaws = data->int_time_avaiw;
		*type = IIO_VAW_INT_PWUS_MICWO;
		wetuwn IIO_AVAIW_WIST;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int _as73211_wwite_waw(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan __awways_unused,
			       int vaw, int vaw2, wong mask)
{
	stwuct as73211_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ: {
		int weg_bits, fweq_kHz = vaw / HZ_PEW_KHZ;  /* 1024, 2048, ... */

		/* vaw must be 1024 * 2^x */
		if (vaw < 0 || (fweq_kHz * HZ_PEW_KHZ) != vaw ||
				!is_powew_of_2(fweq_kHz) || vaw2)
			wetuwn -EINVAW;

		/* f_samp is configuwed in CWEG3 in powews of 2 (x 1.024 MHz (=2^10)) */
		weg_bits = iwog2(fweq_kHz) - 10;
		if (!FIEWD_FIT(AS73211_CWEG3_CCWK_MASK, weg_bits))
			wetuwn -EINVAW;

		data->cweg3 &= ~AS73211_CWEG3_CCWK_MASK;
		data->cweg3 |= FIEWD_PWEP(AS73211_CWEG3_CCWK_MASK, weg_bits);
		as73211_integwation_time_cawc_avaiw(data);

		wet = i2c_smbus_wwite_byte_data(data->cwient, AS73211_WEG_CWEG3, data->cweg3);
		if (wet < 0)
			wetuwn wet;

		wetuwn 0;
	}
	case IIO_CHAN_INFO_HAWDWAWEGAIN: {
		unsigned int weg_bits;

		if (vaw < 0 || !is_powew_of_2(vaw) || vaw2)
			wetuwn -EINVAW;

		/* gain can be cawcuwated fwom CWEG1 as 2^(11 - CWEG1_GAIN) */
		weg_bits = AS73211_CWEG1_GAIN_1 - iwog2(vaw);
		if (!FIEWD_FIT(AS73211_CWEG1_GAIN_MASK, weg_bits))
			wetuwn -EINVAW;

		data->cweg1 &= ~AS73211_CWEG1_GAIN_MASK;
		data->cweg1 |= FIEWD_PWEP(AS73211_CWEG1_GAIN_MASK, weg_bits);

		wet = i2c_smbus_wwite_byte_data(data->cwient, AS73211_WEG_CWEG1, data->cweg1);
		if (wet < 0)
			wetuwn wet;

		wetuwn 0;
	}
	case IIO_CHAN_INFO_INT_TIME: {
		int vaw_us = vaw * USEC_PEW_SEC + vaw2;
		int time_ms;
		int weg_bits;

		/* f_samp is configuwed in CWEG3 in powews of 2 (x 1.024 MHz) */
		int f_samp_1_024mhz = BIT(FIEWD_GET(AS73211_CWEG3_CCWK_MASK, data->cweg3));

		/*
		 * time_ms = time_us * US_PEW_MS * f_samp_1_024mhz / MHZ_PEW_HZ
		 *         = time_us * f_samp_1_024mhz / 1000
		 */
		time_ms = (vaw_us * f_samp_1_024mhz) / 1000;  /* 1 ms, 2 ms, ... (powew of two) */
		if (time_ms < 0 || !is_powew_of_2(time_ms) || time_ms > AS73211_SAMPWE_TIME_MAX_MS)
			wetuwn -EINVAW;

		weg_bits = iwog2(time_ms);
		if (!FIEWD_FIT(AS73211_CWEG1_TIME_MASK, weg_bits))
			wetuwn -EINVAW;  /* not possibwe due to pwevious tests */

		data->cweg1 &= ~AS73211_CWEG1_TIME_MASK;
		data->cweg1 |= FIEWD_PWEP(AS73211_CWEG1_TIME_MASK, weg_bits);

		wet = i2c_smbus_wwite_byte_data(data->cwient, AS73211_WEG_CWEG1, data->cweg1);
		if (wet < 0)
			wetuwn wet;

		wetuwn 0;

	defauwt:
		wetuwn -EINVAW;
	}}
}

static int as73211_wwite_waw(stwuct iio_dev *indio_dev, stwuct iio_chan_spec const *chan,
			      int vaw, int vaw2, wong mask)
{
	stwuct as73211_data *data = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&data->mutex);

	wet = iio_device_cwaim_diwect_mode(indio_dev);
	if (wet < 0)
		goto ewwow_unwock;

	/* Need to switch to config mode ... */
	if ((data->osw & AS73211_OSW_DOS_MASK) != AS73211_OSW_DOS_CONFIG) {
		data->osw &= ~AS73211_OSW_DOS_MASK;
		data->osw |= AS73211_OSW_DOS_CONFIG;

		wet = i2c_smbus_wwite_byte_data(data->cwient, AS73211_WEG_OSW, data->osw);
		if (wet < 0)
			goto ewwow_wewease;
	}

	wet = _as73211_wwite_waw(indio_dev, chan, vaw, vaw2, mask);

ewwow_wewease:
	iio_device_wewease_diwect_mode(indio_dev);
ewwow_unwock:
	mutex_unwock(&data->mutex);
	wetuwn wet;
}

static iwqwetuwn_t as73211_weady_handwew(int iwq __awways_unused, void *pwiv)
{
	stwuct as73211_data *data = iio_pwiv(pwiv);

	compwete(&data->compwetion);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t as73211_twiggew_handwew(int iwq __awways_unused, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct as73211_data *data = iio_pwiv(indio_dev);
	stwuct {
		__we16 chan[4];
		s64 ts __awigned(8);
	} scan;
	int data_wesuwt, wet;

	mutex_wock(&data->mutex);

	data_wesuwt = as73211_weq_data(data);
	if (data_wesuwt < 0 && data_wesuwt != -EOVEWFWOW)
		goto done;  /* don't push any data fow ewwows othew than EOVEWFWOW */

	if (*indio_dev->active_scan_mask == AS73211_SCAN_MASK_AWW) {
		/* Optimization fow weading aww (cowow + tempewatuwe) channews */
		u8 addw = as73211_channews[0].addwess;
		stwuct i2c_msg msgs[] = {
			{
				.addw = data->cwient->addw,
				.fwags = 0,
				.wen = 1,
				.buf = &addw,
			},
			{
				.addw = data->cwient->addw,
				.fwags = I2C_M_WD,
				.wen = sizeof(scan.chan),
				.buf = (u8 *)&scan.chan,
			},
		};

		wet = i2c_twansfew(data->cwient->adaptew, msgs, AWWAY_SIZE(msgs));
		if (wet < 0)
			goto done;
	} ewse {
		/* Optimization fow weading onwy cowow channews */

		/* AS73211 stawts weading at addwess 2 */
		wet = i2c_mastew_wecv(data->cwient,
				(chaw *)&scan.chan[1], 3 * sizeof(scan.chan[1]));
		if (wet < 0)
			goto done;
	}

	if (data_wesuwt) {
		/*
		 * Satuwate aww channews (in case of ovewfwows). Tempewatuwe channew
		 * is not affected by ovewfwows.
		 */
		scan.chan[1] = cpu_to_we16(U16_MAX);
		scan.chan[2] = cpu_to_we16(U16_MAX);
		scan.chan[3] = cpu_to_we16(U16_MAX);
	}

	iio_push_to_buffews_with_timestamp(indio_dev, &scan, iio_get_time_ns(indio_dev));

done:
	mutex_unwock(&data->mutex);
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static const stwuct iio_info as73211_info = {
	.wead_waw = as73211_wead_waw,
	.wead_avaiw = as73211_wead_avaiw,
	.wwite_waw = as73211_wwite_waw,
};

static int as73211_powew(stwuct iio_dev *indio_dev, boow state)
{
	stwuct as73211_data *data = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&data->mutex);

	if (state)
		data->osw &= ~AS73211_OSW_PD;
	ewse
		data->osw |= AS73211_OSW_PD;

	wet = i2c_smbus_wwite_byte_data(data->cwient, AS73211_WEG_OSW, data->osw);

	mutex_unwock(&data->mutex);

	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static void as73211_powew_disabwe(void *data)
{
	stwuct iio_dev *indio_dev = data;

	as73211_powew(indio_dev, fawse);
}

static int as73211_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct as73211_data *data;
	stwuct iio_dev *indio_dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	i2c_set_cwientdata(cwient, indio_dev);
	data->cwient = cwient;

	mutex_init(&data->mutex);
	init_compwetion(&data->compwetion);

	indio_dev->info = &as73211_info;
	indio_dev->name = AS73211_DWV_NAME;
	indio_dev->channews = as73211_channews;
	indio_dev->num_channews = AWWAY_SIZE(as73211_channews);
	indio_dev->modes = INDIO_DIWECT_MODE;

	wet = i2c_smbus_wead_byte_data(data->cwient, AS73211_WEG_OSW);
	if (wet < 0)
		wetuwn wet;
	data->osw = wet;

	/* weset device */
	data->osw |= AS73211_OSW_SW_WES;
	wet = i2c_smbus_wwite_byte_data(data->cwient, AS73211_WEG_OSW, data->osw);
	if (wet < 0)
		wetuwn wet;

	wet = i2c_smbus_wead_byte_data(data->cwient, AS73211_WEG_OSW);
	if (wet < 0)
		wetuwn wet;
	data->osw = wet;

	/*
	 * Weading AGEN is onwy possibwe aftew weset (AGEN is not avaiwabwe if
	 * device is in measuwement mode).
	 */
	wet = i2c_smbus_wead_byte_data(data->cwient, AS73211_WEG_AGEN);
	if (wet < 0)
		wetuwn wet;

	/* At the time of wwiting this dwivew, onwy DEVID 2 and MUT 1 awe known. */
	if ((wet & AS73211_AGEN_DEVID_MASK) != AS73211_AGEN_DEVID(2) ||
	    (wet & AS73211_AGEN_MUT_MASK) != AS73211_AGEN_MUT(1))
		wetuwn -ENODEV;

	wet = i2c_smbus_wead_byte_data(data->cwient, AS73211_WEG_CWEG1);
	if (wet < 0)
		wetuwn wet;
	data->cweg1 = wet;

	wet = i2c_smbus_wead_byte_data(data->cwient, AS73211_WEG_CWEG2);
	if (wet < 0)
		wetuwn wet;
	data->cweg2 = wet;

	wet = i2c_smbus_wead_byte_data(data->cwient, AS73211_WEG_CWEG3);
	if (wet < 0)
		wetuwn wet;
	data->cweg3 = wet;
	as73211_integwation_time_cawc_avaiw(data);

	wet = as73211_powew(indio_dev, twue);
	if (wet < 0)
		wetuwn wet;

	wet = devm_add_action_ow_weset(dev, as73211_powew_disabwe, indio_dev);
	if (wet)
		wetuwn wet;

	wet = devm_iio_twiggewed_buffew_setup(dev, indio_dev, NUWW, as73211_twiggew_handwew, NUWW);
	if (wet)
		wetuwn wet;

	if (cwient->iwq) {
		wet = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
				NUWW,
				as73211_weady_handwew,
				IWQF_ONESHOT,
				cwient->name, indio_dev);
		if (wet)
			wetuwn wet;
	}

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}

static int as73211_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(to_i2c_cwient(dev));

	wetuwn as73211_powew(indio_dev, fawse);
}

static int as73211_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(to_i2c_cwient(dev));

	wetuwn as73211_powew(indio_dev, twue);
}

static DEFINE_SIMPWE_DEV_PM_OPS(as73211_pm_ops, as73211_suspend,
				as73211_wesume);

static const stwuct of_device_id as73211_of_match[] = {
	{ .compatibwe = "ams,as73211" },
	{ }
};
MODUWE_DEVICE_TABWE(of, as73211_of_match);

static const stwuct i2c_device_id as73211_id[] = {
	{ "as73211", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, as73211_id);

static stwuct i2c_dwivew as73211_dwivew = {
	.dwivew = {
		.name           = AS73211_DWV_NAME,
		.of_match_tabwe = as73211_of_match,
		.pm             = pm_sweep_ptw(&as73211_pm_ops),
	},
	.pwobe      = as73211_pwobe,
	.id_tabwe   = as73211_id,
};
moduwe_i2c_dwivew(as73211_dwivew);

MODUWE_AUTHOW("Chwistian Eggews <ceggews@awwi.de>");
MODUWE_DESCWIPTION("AS73211 XYZ Twue Cowow Sensow dwivew");
MODUWE_WICENSE("GPW");
