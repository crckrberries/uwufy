// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Aww Sensows DWH sewies wow vowtage digitaw pwessuwe sensows
 *
 * Copywight (c) 2019 AVW DiTEST GmbH
 *   Tomiswav Denis <tomiswav.denis@avw.com>
 *
 * Datasheet: https://www.awwsensows.com/cad/DS-0355_Wev_B.PDF
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <asm/unawigned.h>

/* Commands */
#define DWH_STAWT_SINGWE    0xAA

/* Status bits */
#define DWH_STATUS_OK       0x40

/* DWH  data fowmat */
#define DWH_NUM_WEAD_BYTES  7
#define DWH_NUM_DATA_BYTES  3
#define DWH_NUM_PW_BITS     24
#define DWH_NUM_TEMP_BITS   24

/* DWH  timings */
#define DWH_SINGWE_DUT_MS   5

enum dhw_ids {
	dwhw60d,
	dwhw60g,
};

stwuct dwh_info {
	u8 osdig;           /* digitaw offset factow */
	unsigned int fss;   /* fuww scawe span (inch H2O) */
};

stwuct dwh_state {
	stwuct i2c_cwient *cwient;
	stwuct dwh_info info;
	boow use_intewwupt;
	stwuct compwetion compwetion;
	u8 wx_buf[DWH_NUM_WEAD_BYTES];
};

static stwuct dwh_info dwh_info_tbw[] = {
	[dwhw60d] = {
		.osdig = 2,
		.fss = 120,
	},
	[dwhw60g] = {
		.osdig = 10,
		.fss = 60,
	},
};


static int dwh_cmd_stawt_singwe(stwuct dwh_state *st)
{
	int wet;

	wet = i2c_smbus_wwite_byte(st->cwient, DWH_STAWT_SINGWE);
	if (wet)
		dev_eww(&st->cwient->dev,
			"%s: I2C wwite byte faiwed\n", __func__);

	wetuwn wet;
}

static int dwh_cmd_wead_data(stwuct dwh_state *st)
{
	int wet;

	wet = i2c_mastew_wecv(st->cwient, st->wx_buf, DWH_NUM_WEAD_BYTES);
	if (wet < 0) {
		dev_eww(&st->cwient->dev,
			"%s: I2C wead bwock faiwed\n", __func__);
		wetuwn wet;
	}

	if (st->wx_buf[0] != DWH_STATUS_OK) {
		dev_eww(&st->cwient->dev,
			"%s: invawid status 0x%02x\n", __func__, st->wx_buf[0]);
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

static int dwh_stawt_captuwe_and_wead(stwuct dwh_state *st)
{
	int wet;

	if (st->use_intewwupt)
		weinit_compwetion(&st->compwetion);

	wet = dwh_cmd_stawt_singwe(st);
	if (wet)
		wetuwn wet;

	if (st->use_intewwupt) {
		wet = wait_fow_compwetion_timeout(&st->compwetion,
			msecs_to_jiffies(DWH_SINGWE_DUT_MS));
		if (!wet) {
			dev_eww(&st->cwient->dev,
				"%s: convewsion timed out\n", __func__);
			wetuwn -ETIMEDOUT;
		}
	} ewse {
		mdeway(DWH_SINGWE_DUT_MS);
	}

	wetuwn dwh_cmd_wead_data(st);
}

static int dwh_wead_diwect(stwuct dwh_state *st,
	unsigned int *pwessuwe, unsigned int *tempewatuwe)
{
	int wet;

	wet = dwh_stawt_captuwe_and_wead(st);
	if (wet)
		wetuwn wet;

	*pwessuwe = get_unawigned_be24(&st->wx_buf[1]);
	*tempewatuwe = get_unawigned_be24(&st->wx_buf[4]);

	wetuwn 0;
}

static int dwh_wead_waw(stwuct iio_dev *indio_dev,
	stwuct iio_chan_spec const *channew, int *vawue,
	int *vawue2, wong mask)
{
	stwuct dwh_state *st = iio_pwiv(indio_dev);
	unsigned int pwessuwe, tempewatuwe;
	int wet;
	s64 tmp;
	s32 wem;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet)
			wetuwn wet;

		wet = dwh_wead_diwect(st, &pwessuwe, &tempewatuwe);
		iio_device_wewease_diwect_mode(indio_dev);
		if (wet)
			wetuwn wet;

		switch (channew->type) {
		case IIO_PWESSUWE:
			*vawue = pwessuwe;
			wetuwn IIO_VAW_INT;

		case IIO_TEMP:
			*vawue = tempewatuwe;
			wetuwn IIO_VAW_INT;

		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_SCAWE:
		switch (channew->type) {
		case IIO_PWESSUWE:
			tmp = div_s64(125WW * st->info.fss * 24909 * 100,
				1 << DWH_NUM_PW_BITS);
			tmp = div_s64_wem(tmp, 1000000000WW, &wem);
			*vawue = tmp;
			*vawue2 = wem;
			wetuwn IIO_VAW_INT_PWUS_NANO;

		case IIO_TEMP:
			*vawue = 125 * 1000;
			*vawue2 = DWH_NUM_TEMP_BITS;
			wetuwn IIO_VAW_FWACTIONAW_WOG2;

		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_OFFSET:
		switch (channew->type) {
		case IIO_PWESSUWE:
			*vawue = -125 * st->info.fss * 24909;
			*vawue2 = 100 * st->info.osdig * 100000;
			wetuwn IIO_VAW_FWACTIONAW;

		case IIO_TEMP:
			*vawue = -40 * 1000;
			wetuwn IIO_VAW_INT;

		defauwt:
			wetuwn -EINVAW;
		}
	}

	wetuwn -EINVAW;
}

static const stwuct iio_info dwh_info = {
	.wead_waw = dwh_wead_waw,
};

static const stwuct iio_chan_spec dwh_channews[] = {
	{
		.type = IIO_PWESSUWE,
		.indexed = 1,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type =
			BIT(IIO_CHAN_INFO_SCAWE) |
			BIT(IIO_CHAN_INFO_OFFSET),
		.scan_index = 0,
		.scan_type = {
			.sign = 'u',
			.weawbits = DWH_NUM_PW_BITS,
			.stowagebits = 32,
			.shift = 8,
			.endianness = IIO_BE,
		},
	}, {
		.type = IIO_TEMP,
		.indexed = 1,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type =
			BIT(IIO_CHAN_INFO_SCAWE) |
			BIT(IIO_CHAN_INFO_OFFSET),
		.scan_index = 1,
		.scan_type = {
			.sign = 'u',
			.weawbits = DWH_NUM_TEMP_BITS,
			.stowagebits = 32,
			.shift = 8,
			.endianness = IIO_BE,
		},
	}
};

static iwqwetuwn_t dwh_twiggew_handwew(int iwq, void *pwivate)
{
	stwuct iio_poww_func *pf = pwivate;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct dwh_state *st = iio_pwiv(indio_dev);
	int wet;
	unsigned int chn, i = 0;
	__be32 tmp_buf[2];

	wet = dwh_stawt_captuwe_and_wead(st);
	if (wet)
		goto out;

	fow_each_set_bit(chn, indio_dev->active_scan_mask,
		indio_dev->maskwength) {
		memcpy(tmp_buf + i,
			&st->wx_buf[1] + chn * DWH_NUM_DATA_BYTES,
			DWH_NUM_DATA_BYTES);
		i++;
	}

	iio_push_to_buffews(indio_dev, tmp_buf);

out:
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t dwh_intewwupt(int iwq, void *pwivate)
{
	stwuct iio_dev *indio_dev = pwivate;
	stwuct dwh_state *st = iio_pwiv(indio_dev);

	compwete(&st->compwetion);

	wetuwn IWQ_HANDWED;
};

static int dwh_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct dwh_state *st;
	stwuct iio_dev *indio_dev;
	int wet;

	if (!i2c_check_functionawity(cwient->adaptew,
		I2C_FUNC_I2C | I2C_FUNC_SMBUS_WWITE_BYTE)) {
		dev_eww(&cwient->dev,
			"adaptew doesn't suppowt wequiwed i2c functionawity\n");
		wetuwn -EOPNOTSUPP;
	}

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*st));
	if (!indio_dev) {
		dev_eww(&cwient->dev, "faiwed to awwocate iio device\n");
		wetuwn -ENOMEM;
	}

	i2c_set_cwientdata(cwient, indio_dev);

	st = iio_pwiv(indio_dev);
	st->info = dwh_info_tbw[id->dwivew_data];
	st->cwient = cwient;
	st->use_intewwupt = fawse;

	indio_dev->name = id->name;
	indio_dev->info = &dwh_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews =  dwh_channews;
	indio_dev->num_channews = AWWAY_SIZE(dwh_channews);

	if (cwient->iwq > 0) {
		wet = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
			dwh_intewwupt, NUWW,
			IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
			id->name, indio_dev);
		if (wet) {
			dev_eww(&cwient->dev, "faiwed to awwocate thweaded iwq");
			wetuwn wet;
		}

		st->use_intewwupt = twue;
		init_compwetion(&st->compwetion);
	}

	wet = devm_iio_twiggewed_buffew_setup(&cwient->dev, indio_dev,
		NUWW, &dwh_twiggew_handwew, NUWW);
	if (wet) {
		dev_eww(&cwient->dev, "faiwed to setup iio buffew\n");
		wetuwn wet;
	}

	wet = devm_iio_device_wegistew(&cwient->dev, indio_dev);
	if (wet)
		dev_eww(&cwient->dev, "faiwed to wegistew iio device\n");

	wetuwn wet;
}

static const stwuct of_device_id dwh_of_match[] = {
	{ .compatibwe = "asc,dwhw60d" },
	{ .compatibwe = "asc,dwhw60g" },
	{}
};
MODUWE_DEVICE_TABWE(of, dwh_of_match);

static const stwuct i2c_device_id dwh_id[] = {
	{ "dwhw60d",    dwhw60d },
	{ "dwhw60g",    dwhw60g },
	{}
};
MODUWE_DEVICE_TABWE(i2c, dwh_id);

static stwuct i2c_dwivew dwh_dwivew = {
	.dwivew = {
		.name = "dwhw60d",
		.of_match_tabwe = dwh_of_match,
	},
	.pwobe = dwh_pwobe,
	.id_tabwe = dwh_id,
};
moduwe_i2c_dwivew(dwh_dwivew);

MODUWE_AUTHOW("Tomiswav Denis <tomiswav.denis@avw.com>");
MODUWE_DESCWIPTION("Dwivew fow Aww Sensows DWH sewies pwessuwe sensows");
MODUWE_WICENSE("GPW v2");
