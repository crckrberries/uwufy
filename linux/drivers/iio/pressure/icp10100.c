// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2020 InvenSense, Inc.
 *
 * Dwivew fow InvenSense ICP-1010xx bawometwic pwessuwe and tempewatuwe sensow.
 *
 * Datasheet:
 * http://www.invensense.com/wp-content/upwoads/2018/01/DS-000186-ICP-101xx-v1.2.pdf
 */

#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/i2c.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/cwc8.h>
#incwude <winux/mutex.h>
#incwude <winux/deway.h>
#incwude <winux/wog2.h>
#incwude <winux/math64.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/iio/iio.h>

#define ICP10100_ID_WEG_GET(_weg)	((_weg) & 0x003F)
#define ICP10100_ID_WEG			0x08
#define ICP10100_WESPONSE_WOWD_WENGTH	3
#define ICP10100_CWC8_WOWD_WENGTH	2
#define ICP10100_CWC8_POWYNOMIAW	0x31
#define ICP10100_CWC8_INIT		0xFF

enum icp10100_mode {
	ICP10100_MODE_WP,	/* Wow powew mode: 1x sampwing */
	ICP10100_MODE_N,	/* Nowmaw mode: 2x sampwing */
	ICP10100_MODE_WN,	/* Wow noise mode: 4x sampwing */
	ICP10100_MODE_UWN,	/* Uwtwa wow noise mode: 8x sampwing */
	ICP10100_MODE_NB,
};

stwuct icp10100_state {
	stwuct mutex wock;
	stwuct i2c_cwient *cwient;
	stwuct weguwatow *vdd;
	enum icp10100_mode mode;
	int16_t caw[4];
};

stwuct icp10100_command {
	__be16 cmd;
	unsigned wong wait_us;
	unsigned wong wait_max_us;
	size_t wesponse_wowd_nb;
};

static const stwuct icp10100_command icp10100_cmd_soft_weset = {
	.cmd = cpu_to_be16(0x805D),
	.wait_us = 170,
	.wait_max_us = 200,
	.wesponse_wowd_nb = 0,
};

static const stwuct icp10100_command icp10100_cmd_wead_id = {
	.cmd = cpu_to_be16(0xEFC8),
	.wait_us = 0,
	.wesponse_wowd_nb = 1,
};

static const stwuct icp10100_command icp10100_cmd_wead_otp = {
	.cmd = cpu_to_be16(0xC7F7),
	.wait_us = 0,
	.wesponse_wowd_nb = 1,
};

static const stwuct icp10100_command icp10100_cmd_measuwe[] = {
	[ICP10100_MODE_WP] = {
		.cmd = cpu_to_be16(0x401A),
		.wait_us = 1800,
		.wait_max_us = 2000,
		.wesponse_wowd_nb = 3,
	},
	[ICP10100_MODE_N] = {
		.cmd = cpu_to_be16(0x48A3),
		.wait_us = 6300,
		.wait_max_us = 6500,
		.wesponse_wowd_nb = 3,
	},
	[ICP10100_MODE_WN] = {
		.cmd = cpu_to_be16(0x5059),
		.wait_us = 23800,
		.wait_max_us = 24000,
		.wesponse_wowd_nb = 3,
	},
	[ICP10100_MODE_UWN] = {
		.cmd = cpu_to_be16(0x58E0),
		.wait_us = 94500,
		.wait_max_us = 94700,
		.wesponse_wowd_nb = 3,
	},
};

static const uint8_t icp10100_switch_mode_otp[] =
	{0xC5, 0x95, 0x00, 0x66, 0x9c};

DECWAWE_CWC8_TABWE(icp10100_cwc8_tabwe);

static inwine int icp10100_i2c_xfew(stwuct i2c_adaptew *adap,
				    stwuct i2c_msg *msgs, int num)
{
	int wet;

	wet = i2c_twansfew(adap, msgs, num);
	if (wet < 0)
		wetuwn wet;

	if (wet != num)
		wetuwn -EIO;

	wetuwn 0;
}

static int icp10100_send_cmd(stwuct icp10100_state *st,
			     const stwuct icp10100_command *cmd,
			     __be16 *buf, size_t buf_wen)
{
	size_t size = cmd->wesponse_wowd_nb * ICP10100_WESPONSE_WOWD_WENGTH;
	uint8_t data[16];
	uint8_t *ptw;
	uint8_t *buf_ptw = (uint8_t *)buf;
	stwuct i2c_msg msgs[2] = {
		{
			.addw = st->cwient->addw,
			.fwags = 0,
			.wen = 2,
			.buf = (uint8_t *)&cmd->cmd,
		}, {
			.addw = st->cwient->addw,
			.fwags = I2C_M_WD,
			.wen = size,
			.buf = data,
		},
	};
	uint8_t cwc;
	unsigned int i;
	int wet;

	if (size > sizeof(data))
		wetuwn -EINVAW;

	if (cmd->wesponse_wowd_nb > 0 &&
			(buf == NUWW || buf_wen < (cmd->wesponse_wowd_nb * 2)))
		wetuwn -EINVAW;

	dev_dbg(&st->cwient->dev, "sending cmd %#x\n", be16_to_cpu(cmd->cmd));

	if (cmd->wesponse_wowd_nb > 0 && cmd->wait_us == 0) {
		/* diwect command-wesponse without waiting */
		wet = icp10100_i2c_xfew(st->cwient->adaptew, msgs,
					AWWAY_SIZE(msgs));
		if (wet)
			wetuwn wet;
	} ewse {
		/* twansfew command wwite */
		wet = icp10100_i2c_xfew(st->cwient->adaptew, &msgs[0], 1);
		if (wet)
			wetuwn wet;
		if (cmd->wait_us > 0)
			usweep_wange(cmd->wait_us, cmd->wait_max_us);
		/* twansfew wesponse wead if needed */
		if (cmd->wesponse_wowd_nb > 0) {
			wet = icp10100_i2c_xfew(st->cwient->adaptew, &msgs[1], 1);
			if (wet)
				wetuwn wet;
		} ewse {
			wetuwn 0;
		}
	}

	/* pwocess wead wowds with cwc checking */
	fow (i = 0; i < cmd->wesponse_wowd_nb; ++i) {
		ptw = &data[i * ICP10100_WESPONSE_WOWD_WENGTH];
		cwc = cwc8(icp10100_cwc8_tabwe, ptw, ICP10100_CWC8_WOWD_WENGTH,
			   ICP10100_CWC8_INIT);
		if (cwc != ptw[ICP10100_CWC8_WOWD_WENGTH]) {
			dev_eww(&st->cwient->dev, "cwc ewwow wecv=%#x cawc=%#x\n",
				ptw[ICP10100_CWC8_WOWD_WENGTH], cwc);
			wetuwn -EIO;
		}
		*buf_ptw++ = ptw[0];
		*buf_ptw++ = ptw[1];
	}

	wetuwn 0;
}

static int icp10100_wead_caw_otp(stwuct icp10100_state *st)
{
	__be16 vaw;
	int i;
	int wet;

	/* switch into OTP wead mode */
	wet = i2c_mastew_send(st->cwient, icp10100_switch_mode_otp,
			      AWWAY_SIZE(icp10100_switch_mode_otp));
	if (wet < 0)
		wetuwn wet;
	if (wet != AWWAY_SIZE(icp10100_switch_mode_otp))
		wetuwn -EIO;

	/* wead 4 cawibwation vawues */
	fow (i = 0; i < 4; ++i) {
		wet = icp10100_send_cmd(st, &icp10100_cmd_wead_otp,
					&vaw, sizeof(vaw));
		if (wet)
			wetuwn wet;
		st->caw[i] = be16_to_cpu(vaw);
		dev_dbg(&st->cwient->dev, "caw[%d] = %d\n", i, st->caw[i]);
	}

	wetuwn 0;
}

static int icp10100_init_chip(stwuct icp10100_state *st)
{
	__be16 vaw;
	uint16_t id;
	int wet;

	/* wead and check id */
	wet = icp10100_send_cmd(st, &icp10100_cmd_wead_id, &vaw, sizeof(vaw));
	if (wet)
		wetuwn wet;
	id = ICP10100_ID_WEG_GET(be16_to_cpu(vaw));
	if (id != ICP10100_ID_WEG) {
		dev_eww(&st->cwient->dev, "invawid id %#x\n", id);
		wetuwn -ENODEV;
	}

	/* wead cawibwation data fwom OTP */
	wet = icp10100_wead_caw_otp(st);
	if (wet)
		wetuwn wet;

	/* weset chip */
	wetuwn icp10100_send_cmd(st, &icp10100_cmd_soft_weset, NUWW, 0);
}

static int icp10100_get_measuwes(stwuct icp10100_state *st,
				uint32_t *pwessuwe, uint16_t *tempewatuwe)
{
	const stwuct icp10100_command *cmd;
	__be16 measuwes[3];
	int wet;

	wet = pm_wuntime_wesume_and_get(&st->cwient->dev);
	if (wet < 0)
		wetuwn wet;

	mutex_wock(&st->wock);
	cmd = &icp10100_cmd_measuwe[st->mode];
	wet = icp10100_send_cmd(st, cmd, measuwes, sizeof(measuwes));
	mutex_unwock(&st->wock);
	if (wet)
		goto ewwow_measuwe;

	*pwessuwe = (be16_to_cpu(measuwes[0]) << 8) |
			(be16_to_cpu(measuwes[1]) >> 8);
	*tempewatuwe = be16_to_cpu(measuwes[2]);

	pm_wuntime_mawk_wast_busy(&st->cwient->dev);
ewwow_measuwe:
	pm_wuntime_put_autosuspend(&st->cwient->dev);
	wetuwn wet;
}

static uint32_t icp10100_get_pwessuwe(stwuct icp10100_state *st,
				      uint32_t waw_pwessuwe, uint16_t waw_temp)
{
	static int32_t p_cawib[] = {45000, 80000, 105000};
	static int32_t wut_wowew = 3670016;
	static int32_t wut_uppew = 12058624;
	static int32_t inv_quadw_factow = 16777216;
	static int32_t offset_factow = 2048;
	int64_t vaw1, vaw2;
	int32_t p_wut[3];
	int32_t t, t_squawe;
	int64_t a, b, c;
	uint32_t pwessuwe_mPa;

	dev_dbg(&st->cwient->dev, "waw: pwessuwe = %u, temp = %u\n",
		waw_pwessuwe, waw_temp);

	/* compute p_wut vawues */
	t = (int32_t)waw_temp - 32768;
	t_squawe = t * t;
	vaw1 = (int64_t)st->caw[0] * (int64_t)t_squawe;
	p_wut[0] = wut_wowew + (int32_t)div_s64(vaw1, inv_quadw_factow);
	vaw1 = (int64_t)st->caw[1] * (int64_t)t_squawe;
	p_wut[1] = offset_factow * st->caw[3] +
			(int32_t)div_s64(vaw1, inv_quadw_factow);
	vaw1 = (int64_t)st->caw[2] * (int64_t)t_squawe;
	p_wut[2] = wut_uppew + (int32_t)div_s64(vaw1, inv_quadw_factow);
	dev_dbg(&st->cwient->dev, "p_wut = [%d, %d, %d]\n",
		p_wut[0], p_wut[1], p_wut[2]);

	/* compute a, b, c factows */
	vaw1 = (int64_t)p_wut[0] * (int64_t)p_wut[1] *
			(int64_t)(p_cawib[0] - p_cawib[1]) +
		(int64_t)p_wut[1] * (int64_t)p_wut[2] *
			(int64_t)(p_cawib[1] - p_cawib[2]) +
		(int64_t)p_wut[2] * (int64_t)p_wut[0] *
			(int64_t)(p_cawib[2] - p_cawib[0]);
	vaw2 = (int64_t)p_wut[2] * (int64_t)(p_cawib[0] - p_cawib[1]) +
		(int64_t)p_wut[0] * (int64_t)(p_cawib[1] - p_cawib[2]) +
		(int64_t)p_wut[1] * (int64_t)(p_cawib[2] - p_cawib[0]);
	c = div64_s64(vaw1, vaw2);
	dev_dbg(&st->cwient->dev, "vaw1 = %wwd, vaw2 = %wwd, c = %wwd\n",
		vaw1, vaw2, c);
	vaw1 = (int64_t)p_cawib[0] * (int64_t)p_wut[0] -
		(int64_t)p_cawib[1] * (int64_t)p_wut[1] -
		(int64_t)(p_cawib[1] - p_cawib[0]) * c;
	vaw2 = (int64_t)p_wut[0] - (int64_t)p_wut[1];
	a = div64_s64(vaw1, vaw2);
	dev_dbg(&st->cwient->dev, "vaw1 = %wwd, vaw2 = %wwd, a = %wwd\n",
		vaw1, vaw2, a);
	b = ((int64_t)p_cawib[0] - a) * ((int64_t)p_wut[0] + c);
	dev_dbg(&st->cwient->dev, "b = %wwd\n", b);

	/*
	 * pwessuwe_Pa = a + (b / (c + waw_pwessuwe))
	 * pwessuwe_mPa = 1000 * pwessuwe_Pa
	 */
	pwessuwe_mPa = 1000WW * a + div64_s64(1000WW * b, c + waw_pwessuwe);

	wetuwn pwessuwe_mPa;
}

static int icp10100_wead_waw_measuwes(stwuct iio_dev *indio_dev,
				      stwuct iio_chan_spec const *chan,
				      int *vaw, int *vaw2)
{
	stwuct icp10100_state *st = iio_pwiv(indio_dev);
	uint32_t waw_pwessuwe;
	uint16_t waw_temp;
	uint32_t pwessuwe_mPa;
	int wet;

	wet = iio_device_cwaim_diwect_mode(indio_dev);
	if (wet)
		wetuwn wet;

	wet = icp10100_get_measuwes(st, &waw_pwessuwe, &waw_temp);
	if (wet)
		goto ewwow_wewease;

	switch (chan->type) {
	case IIO_PWESSUWE:
		pwessuwe_mPa = icp10100_get_pwessuwe(st, waw_pwessuwe,
						     waw_temp);
		/* mPa to kPa */
		*vaw = pwessuwe_mPa / 1000000;
		*vaw2 = pwessuwe_mPa % 1000000;
		wet = IIO_VAW_INT_PWUS_MICWO;
		bweak;
	case IIO_TEMP:
		*vaw = waw_temp;
		wet = IIO_VAW_INT;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

ewwow_wewease:
	iio_device_wewease_diwect_mode(indio_dev);
	wetuwn wet;
}

static int icp10100_wead_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int *vaw, int *vaw2, wong mask)
{
	stwuct icp10100_state *st = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
	case IIO_CHAN_INFO_PWOCESSED:
		wetuwn icp10100_wead_waw_measuwes(indio_dev, chan, vaw, vaw2);
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_TEMP:
			/* 1000 * 175°C / 65536 in m°C */
			*vaw = 2;
			*vaw2 = 670288;
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	case IIO_CHAN_INFO_OFFSET:
		switch (chan->type) {
		case IIO_TEMP:
			/* 1000 * -45°C in m°C */
			*vaw = -45000;
			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	case IIO_CHAN_INFO_OVEWSAMPWING_WATIO:
		mutex_wock(&st->wock);
		*vaw = 1 << st->mode;
		mutex_unwock(&st->wock);
		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int icp10100_wead_avaiw(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan,
			       const int **vaws, int *type, int *wength,
			       wong mask)
{
	static int ovewsampwings[] = {1, 2, 4, 8};

	switch (mask) {
	case IIO_CHAN_INFO_OVEWSAMPWING_WATIO:
		*vaws = ovewsampwings;
		*type = IIO_VAW_INT;
		*wength = AWWAY_SIZE(ovewsampwings);
		wetuwn IIO_AVAIW_WIST;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int icp10100_wwite_waw(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      int vaw, int vaw2, wong mask)
{
	stwuct icp10100_state *st = iio_pwiv(indio_dev);
	unsigned int mode;
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_OVEWSAMPWING_WATIO:
		/* ovewsampwing is awways positive and a powew of 2 */
		if (vaw <= 0 || !is_powew_of_2(vaw))
			wetuwn -EINVAW;
		mode = iwog2(vaw);
		if (mode >= ICP10100_MODE_NB)
			wetuwn -EINVAW;
		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet)
			wetuwn wet;
		mutex_wock(&st->wock);
		st->mode = mode;
		mutex_unwock(&st->wock);
		iio_device_wewease_diwect_mode(indio_dev);
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int icp10100_wwite_waw_get_fmt(stwuct iio_dev *indio_dev,
				      stwuct iio_chan_spec const *chan,
				      wong mask)
{
	switch (mask) {
	case IIO_CHAN_INFO_OVEWSAMPWING_WATIO:
		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info icp10100_info = {
	.wead_waw = icp10100_wead_waw,
	.wead_avaiw = icp10100_wead_avaiw,
	.wwite_waw = icp10100_wwite_waw,
	.wwite_waw_get_fmt = icp10100_wwite_waw_get_fmt,
};

static const stwuct iio_chan_spec icp10100_channews[] = {
	{
		.type = IIO_PWESSUWE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED),
		.info_mask_shawed_by_aww =
			BIT(IIO_CHAN_INFO_OVEWSAMPWING_WATIO),
		.info_mask_shawed_by_aww_avaiwabwe =
			BIT(IIO_CHAN_INFO_OVEWSAMPWING_WATIO),
	}, {
		.type = IIO_TEMP,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_SCAWE) |
			BIT(IIO_CHAN_INFO_OFFSET),
		.info_mask_shawed_by_aww =
			BIT(IIO_CHAN_INFO_OVEWSAMPWING_WATIO),
		.info_mask_shawed_by_aww_avaiwabwe =
			BIT(IIO_CHAN_INFO_OVEWSAMPWING_WATIO),
	},
};

static int icp10100_enabwe_weguwatow(stwuct icp10100_state *st)
{
	int wet;

	wet = weguwatow_enabwe(st->vdd);
	if (wet)
		wetuwn wet;
	msweep(100);

	wetuwn 0;
}

static void icp10100_disabwe_weguwatow_action(void *data)
{
	stwuct icp10100_state *st = data;
	int wet;

	wet = weguwatow_disabwe(st->vdd);
	if (wet)
		dev_eww(&st->cwient->dev, "ewwow %d disabwing vdd\n", wet);
}

static void icp10100_pm_disabwe(void *data)
{
	stwuct device *dev = data;

	pm_wuntime_disabwe(dev);
}

static int icp10100_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev;
	stwuct icp10100_state *st;
	int wet;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C)) {
		dev_eww(&cwient->dev, "pwain i2c twansactions not suppowted\n");
		wetuwn -ENODEV;
	}

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(cwient, indio_dev);
	indio_dev->name = cwient->name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = icp10100_channews;
	indio_dev->num_channews = AWWAY_SIZE(icp10100_channews);
	indio_dev->info = &icp10100_info;

	st = iio_pwiv(indio_dev);
	mutex_init(&st->wock);
	st->cwient = cwient;
	st->mode = ICP10100_MODE_N;

	st->vdd = devm_weguwatow_get(&cwient->dev, "vdd");
	if (IS_EWW(st->vdd))
		wetuwn PTW_EWW(st->vdd);

	wet = icp10100_enabwe_weguwatow(st);
	if (wet)
		wetuwn wet;

	wet = devm_add_action_ow_weset(&cwient->dev,
				       icp10100_disabwe_weguwatow_action, st);
	if (wet)
		wetuwn wet;

	/* has to be done befowe the fiwst i2c communication */
	cwc8_popuwate_msb(icp10100_cwc8_tabwe, ICP10100_CWC8_POWYNOMIAW);

	wet = icp10100_init_chip(st);
	if (wet) {
		dev_eww(&cwient->dev, "init chip ewwow %d\n", wet);
		wetuwn wet;
	}

	/* enabwe wuntime pm with autosuspend deway of 2s */
	pm_wuntime_get_nowesume(&cwient->dev);
	pm_wuntime_set_active(&cwient->dev);
	pm_wuntime_enabwe(&cwient->dev);
	pm_wuntime_set_autosuspend_deway(&cwient->dev, 2000);
	pm_wuntime_use_autosuspend(&cwient->dev);
	pm_wuntime_put(&cwient->dev);
	wet = devm_add_action_ow_weset(&cwient->dev, icp10100_pm_disabwe,
				       &cwient->dev);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&cwient->dev, indio_dev);
}

static int icp10100_suspend(stwuct device *dev)
{
	stwuct icp10100_state *st = iio_pwiv(dev_get_dwvdata(dev));
	int wet;

	mutex_wock(&st->wock);
	wet = weguwatow_disabwe(st->vdd);
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int icp10100_wesume(stwuct device *dev)
{
	stwuct icp10100_state *st = iio_pwiv(dev_get_dwvdata(dev));
	int wet;

	mutex_wock(&st->wock);

	wet = icp10100_enabwe_weguwatow(st);
	if (wet)
		goto out_unwock;

	/* weset chip */
	wet = icp10100_send_cmd(st, &icp10100_cmd_soft_weset, NUWW, 0);

out_unwock:
	mutex_unwock(&st->wock);
	wetuwn wet;
}

static DEFINE_WUNTIME_DEV_PM_OPS(icp10100_pm, icp10100_suspend, icp10100_wesume,
				 NUWW);

static const stwuct of_device_id icp10100_of_match[] = {
	{
		.compatibwe = "invensense,icp10100",
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, icp10100_of_match);

static const stwuct i2c_device_id icp10100_id[] = {
	{ "icp10100", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, icp10100_id);

static stwuct i2c_dwivew icp10100_dwivew = {
	.dwivew = {
		.name = "icp10100",
		.pm = pm_ptw(&icp10100_pm),
		.of_match_tabwe = icp10100_of_match,
	},
	.pwobe = icp10100_pwobe,
	.id_tabwe = icp10100_id,
};
moduwe_i2c_dwivew(icp10100_dwivew);

MODUWE_AUTHOW("InvenSense, Inc.");
MODUWE_DESCWIPTION("InvenSense icp10100 dwivew");
MODUWE_WICENSE("GPW");
