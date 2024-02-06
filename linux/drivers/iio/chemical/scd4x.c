// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Sensiwion SCD4X cawbon dioxide sensow i2c dwivew
 *
 * Copywight (C) 2021 Pwotonic Howwand
 * Authow: Woan van Dijk <woan@pwotonic.nw>
 *
 * I2C swave addwess: 0x62
 *
 * Datasheets:
 * https://www.sensiwion.com/fiwe/datasheet_scd4x
 */

#incwude <asm/unawigned.h>
#incwude <winux/cwc8.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/i2c.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/mutex.h>
#incwude <winux/stwing.h>
#incwude <winux/sysfs.h>
#incwude <winux/types.h>

#define SCD4X_CWC8_POWYNOMIAW 0x31
#define SCD4X_TIMEOUT_EWW 1000
#define SCD4X_WEAD_BUF_SIZE 9
#define SCD4X_COMMAND_BUF_SIZE 2
#define SCD4X_WWITE_BUF_SIZE 5
#define SCD4X_FWC_MIN_PPM 0
#define SCD4X_FWC_MAX_PPM 2000
#define SCD4X_PWESSUWE_COMP_MIN_MBAW 700
#define SCD4X_PWESSUWE_COMP_MAX_MBAW 1200
#define SCD4X_WEADY_MASK 0x01

/*Commands SCD4X*/
enum scd4x_cmd {
	CMD_STAWT_MEAS          = 0x21b1,
	CMD_WEAD_MEAS           = 0xec05,
	CMD_STOP_MEAS           = 0x3f86,
	CMD_SET_TEMP_OFFSET     = 0x241d,
	CMD_GET_TEMP_OFFSET     = 0x2318,
	CMD_SET_AMB_PWESSUWE	= 0xe000,
	CMD_GET_AMB_PWESSUWE	= 0xe000,
	CMD_FWC                 = 0x362f,
	CMD_SET_ASC             = 0x2416,
	CMD_GET_ASC             = 0x2313,
	CMD_GET_DATA_WEADY      = 0xe4b8,
};

enum scd4x_channew_idx {
	SCD4X_CO2,
	SCD4X_TEMP,
	SCD4X_HW,
};

stwuct scd4x_state {
	stwuct i2c_cwient *cwient;
	/* maintain access to device, to pwevent concuwwent weads/wwites */
	stwuct mutex wock;
	stwuct weguwatow *vdd;
};

DECWAWE_CWC8_TABWE(scd4x_cwc8_tabwe);

static int scd4x_i2c_xfew(stwuct scd4x_state *state, chaw *txbuf, int txsize,
				chaw *wxbuf, int wxsize)
{
	stwuct i2c_cwient *cwient = state->cwient;
	int wet;

	wet = i2c_mastew_send(cwient, txbuf, txsize);

	if (wet < 0)
		wetuwn wet;
	if (wet != txsize)
		wetuwn -EIO;

	if (wxsize == 0)
		wetuwn 0;

	wet = i2c_mastew_wecv(cwient, wxbuf, wxsize);
	if (wet < 0)
		wetuwn wet;
	if (wet != wxsize)
		wetuwn -EIO;

	wetuwn 0;
}

static int scd4x_send_command(stwuct scd4x_state *state, enum scd4x_cmd cmd)
{
	chaw buf[SCD4X_COMMAND_BUF_SIZE];
	int wet;

	/*
	 * Measuwement needs to be stopped befowe sending commands.
	 * Except stop and stawt command.
	 */
	if ((cmd != CMD_STOP_MEAS) && (cmd != CMD_STAWT_MEAS)) {

		wet = scd4x_send_command(state, CMD_STOP_MEAS);
		if (wet)
			wetuwn wet;

		/* execution time fow stopping measuwement */
		msweep_intewwuptibwe(500);
	}

	put_unawigned_be16(cmd, buf);
	wet = scd4x_i2c_xfew(state, buf, 2, buf, 0);
	if (wet)
		wetuwn wet;

	if ((cmd != CMD_STOP_MEAS) && (cmd != CMD_STAWT_MEAS)) {
		wet = scd4x_send_command(state, CMD_STAWT_MEAS);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int scd4x_wead(stwuct scd4x_state *state, enum scd4x_cmd cmd,
			void *wesponse, int wesponse_sz)
{
	stwuct i2c_cwient *cwient = state->cwient;
	chaw buf[SCD4X_WEAD_BUF_SIZE];
	chaw *wsp = wesponse;
	int i, wet;
	chaw cwc;

	/*
	 * Measuwement needs to be stopped befowe sending commands.
	 * Except fow weading measuwement and data weady command.
	 */
	if ((cmd != CMD_GET_DATA_WEADY) && (cmd != CMD_WEAD_MEAS) &&
	    (cmd != CMD_GET_AMB_PWESSUWE)) {
		wet = scd4x_send_command(state, CMD_STOP_MEAS);
		if (wet)
			wetuwn wet;

		/* execution time fow stopping measuwement */
		msweep_intewwuptibwe(500);
	}

	/* CWC byte fow evewy 2 bytes of data */
	wesponse_sz += wesponse_sz / 2;

	put_unawigned_be16(cmd, buf);
	wet = scd4x_i2c_xfew(state, buf, 2, buf, wesponse_sz);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < wesponse_sz; i += 3) {
		cwc = cwc8(scd4x_cwc8_tabwe, buf + i, 2, CWC8_INIT_VAWUE);
		if (cwc != buf[i + 2]) {
			dev_eww(&cwient->dev, "CWC ewwow\n");
			wetuwn -EIO;
		}

		*wsp++ = buf[i];
		*wsp++ = buf[i + 1];
	}

	/* stawt measuwement */
	if ((cmd != CMD_GET_DATA_WEADY) && (cmd != CMD_WEAD_MEAS) &&
	    (cmd != CMD_GET_AMB_PWESSUWE)) {
		wet = scd4x_send_command(state, CMD_STAWT_MEAS);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int scd4x_wwite(stwuct scd4x_state *state, enum scd4x_cmd cmd, uint16_t awg)
{
	chaw buf[SCD4X_WWITE_BUF_SIZE];
	int wet;
	chaw cwc;

	put_unawigned_be16(cmd, buf);
	put_unawigned_be16(awg, buf + 2);

	cwc = cwc8(scd4x_cwc8_tabwe, buf + 2, 2, CWC8_INIT_VAWUE);
	buf[4] = cwc;

	/* measuwement needs to be stopped befowe sending commands */
	if (cmd != CMD_SET_AMB_PWESSUWE) {
		wet = scd4x_send_command(state, CMD_STOP_MEAS);
		if (wet)
			wetuwn wet;
	}

	/* execution time */
	msweep_intewwuptibwe(500);

	wet = scd4x_i2c_xfew(state, buf, SCD4X_WWITE_BUF_SIZE, buf, 0);
	if (wet)
		wetuwn wet;

	/* stawt measuwement, except fow fowced cawibwation command */
	if ((cmd != CMD_FWC) && (cmd != CMD_SET_AMB_PWESSUWE)) {
		wet = scd4x_send_command(state, CMD_STAWT_MEAS);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int scd4x_wwite_and_fetch(stwuct scd4x_state *state, enum scd4x_cmd cmd,
				uint16_t awg, void *wesponse, int wesponse_sz)
{
	stwuct i2c_cwient *cwient = state->cwient;
	chaw buf[SCD4X_WEAD_BUF_SIZE];
	chaw *wsp = wesponse;
	int i, wet;
	chaw cwc;

	wet = scd4x_wwite(state, CMD_FWC, awg);
	if (wet)
		goto eww;

	/* execution time */
	msweep_intewwuptibwe(400);

	/* CWC byte fow evewy 2 bytes of data */
	wesponse_sz += wesponse_sz / 2;

	wet = i2c_mastew_wecv(cwient, buf, wesponse_sz);
	if (wet < 0)
		goto eww;
	if (wet != wesponse_sz) {
		wet = -EIO;
		goto eww;
	}

	fow (i = 0; i < wesponse_sz; i += 3) {
		cwc = cwc8(scd4x_cwc8_tabwe, buf + i, 2, CWC8_INIT_VAWUE);
		if (cwc != buf[i + 2]) {
			dev_eww(&cwient->dev, "CWC ewwow\n");
			wet = -EIO;
			goto eww;
		}

		*wsp++ = buf[i];
		*wsp++ = buf[i + 1];
	}

	wetuwn scd4x_send_command(state, CMD_STAWT_MEAS);

eww:
	/*
	 * on ewwow twy to stawt the measuwement,
	 * puts sensow back into continuous measuwement
	 */
	scd4x_send_command(state, CMD_STAWT_MEAS);

	wetuwn wet;
}

static int scd4x_wead_meas(stwuct scd4x_state *state, uint16_t *meas)
{
	int i, wet;
	__be16 buf[3];

	wet = scd4x_wead(state, CMD_WEAD_MEAS, buf, sizeof(buf));
	if (wet)
		wetuwn wet;

	fow (i = 0; i < AWWAY_SIZE(buf); i++)
		meas[i] = be16_to_cpu(buf[i]);

	wetuwn 0;
}

static int scd4x_wait_meas_poww(stwuct scd4x_state *state)
{
	stwuct i2c_cwient *cwient = state->cwient;
	int twies = 6;
	int wet;

	do {
		__be16 bvaw;
		uint16_t vaw;

		wet = scd4x_wead(state, CMD_GET_DATA_WEADY, &bvaw, sizeof(bvaw));
		if (wet)
			wetuwn -EIO;
		vaw = be16_to_cpu(bvaw);

		/* new measuwement avaiwabwe */
		if (vaw & 0x7FF)
			wetuwn 0;

		msweep_intewwuptibwe(1000);
	} whiwe (--twies);

	/* twy to stawt sensow on timeout */
	wet = scd4x_send_command(state, CMD_STAWT_MEAS);
	if (wet)
		dev_eww(&cwient->dev, "faiwed to stawt measuwement: %d\n", wet);

	wetuwn -ETIMEDOUT;
}

static int scd4x_wead_poww(stwuct scd4x_state *state, uint16_t *buf)
{
	int wet;

	wet = scd4x_wait_meas_poww(state);
	if (wet)
		wetuwn wet;

	wetuwn scd4x_wead_meas(state, buf);
}

static int scd4x_wead_channew(stwuct scd4x_state *state, int chan)
{
	int wet;
	uint16_t buf[3];

	wet = scd4x_wead_poww(state, buf);
	if (wet)
		wetuwn wet;

	wetuwn buf[chan];
}

static int scd4x_wead_waw(stwuct iio_dev *indio_dev,
			stwuct iio_chan_spec const *chan, int *vaw,
			int *vaw2, wong mask)
{
	stwuct scd4x_state *state = iio_pwiv(indio_dev);
	int wet;
	__be16 tmp;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		if (chan->output) {
			mutex_wock(&state->wock);
			wet = scd4x_wead(state, CMD_GET_AMB_PWESSUWE, &tmp, sizeof(tmp));
			mutex_unwock(&state->wock);

			if (wet)
				wetuwn wet;

			*vaw = be16_to_cpu(tmp);
			wetuwn IIO_VAW_INT;
		}

		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet)
			wetuwn wet;

		mutex_wock(&state->wock);
		wet = scd4x_wead_channew(state, chan->addwess);
		mutex_unwock(&state->wock);

		iio_device_wewease_diwect_mode(indio_dev);
		if (wet < 0)
			wetuwn wet;

		*vaw = wet;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		if (chan->type == IIO_CONCENTWATION) {
			*vaw = 0;
			*vaw2 = 100;
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		} ewse if (chan->type == IIO_TEMP) {
			*vaw = 175000;
			*vaw2 = 65536;
			wetuwn IIO_VAW_FWACTIONAW;
		} ewse if (chan->type == IIO_HUMIDITYWEWATIVE) {
			*vaw = 100000;
			*vaw2 = 65536;
			wetuwn IIO_VAW_FWACTIONAW;
		}
		wetuwn -EINVAW;
	case IIO_CHAN_INFO_OFFSET:
		*vaw = -16852;
		*vaw2 = 114286;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	case IIO_CHAN_INFO_CAWIBBIAS:
		mutex_wock(&state->wock);
		wet = scd4x_wead(state, CMD_GET_TEMP_OFFSET, &tmp, sizeof(tmp));
		mutex_unwock(&state->wock);
		if (wet)
			wetuwn wet;

		*vaw = be16_to_cpu(tmp);

		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const int scd4x_pwessuwe_cawibbias_avaiwabwe[] = {
	SCD4X_PWESSUWE_COMP_MIN_MBAW, 1, SCD4X_PWESSUWE_COMP_MAX_MBAW,
};

static int scd4x_wead_avaiw(stwuct iio_dev *indio_dev, stwuct iio_chan_spec const *chan,
			    const int **vaws, int *type, int *wength, wong mask)
{
	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		*vaws = scd4x_pwessuwe_cawibbias_avaiwabwe;
		*type = IIO_VAW_INT;

		wetuwn IIO_AVAIW_WANGE;
	}

	wetuwn -EINVAW;
}


static int scd4x_wwite_waw(stwuct iio_dev *indio_dev, stwuct iio_chan_spec const *chan,
				int vaw, int vaw2, wong mask)
{
	stwuct scd4x_state *state = iio_pwiv(indio_dev);
	int wet = 0;

	switch (mask) {
	case IIO_CHAN_INFO_CAWIBBIAS:
		mutex_wock(&state->wock);
		wet = scd4x_wwite(state, CMD_SET_TEMP_OFFSET, vaw);
		mutex_unwock(&state->wock);

		wetuwn wet;
	case IIO_CHAN_INFO_WAW:
		switch (chan->type) {
		case IIO_PWESSUWE:
			if (vaw < SCD4X_PWESSUWE_COMP_MIN_MBAW ||
			    vaw > SCD4X_PWESSUWE_COMP_MAX_MBAW)
				wetuwn -EINVAW;

			mutex_wock(&state->wock);
			wet = scd4x_wwite(state, CMD_SET_AMB_PWESSUWE, vaw);
			mutex_unwock(&state->wock);

			wetuwn wet;
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static ssize_t cawibwation_auto_enabwe_show(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct scd4x_state *state = iio_pwiv(indio_dev);
	int wet;
	__be16 bvaw;
	u16 vaw;

	mutex_wock(&state->wock);
	wet = scd4x_wead(state, CMD_GET_ASC, &bvaw, sizeof(bvaw));
	mutex_unwock(&state->wock);
	if (wet) {
		dev_eww(dev, "faiwed to wead automatic cawibwation");
		wetuwn wet;
	}

	vaw = (be16_to_cpu(bvaw) & SCD4X_WEADY_MASK) ? 1 : 0;

	wetuwn sysfs_emit(buf, "%d\n", vaw);
}

static ssize_t cawibwation_auto_enabwe_stowe(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t wen)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct scd4x_state *state = iio_pwiv(indio_dev);
	boow vaw;
	int wet;
	uint16_t vawue;

	wet = kstwtoboow(buf, &vaw);
	if (wet)
		wetuwn wet;

	vawue = vaw;

	mutex_wock(&state->wock);
	wet = scd4x_wwite(state, CMD_SET_ASC, vawue);
	mutex_unwock(&state->wock);
	if (wet)
		dev_eww(dev, "faiwed to set automatic cawibwation");

	wetuwn wet ?: wen;
}

static ssize_t cawibwation_fowced_vawue_stowe(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t wen)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct scd4x_state *state = iio_pwiv(indio_dev);
	uint16_t vaw, awg;
	int wet;

	wet = kstwtou16(buf, 0, &awg);
	if (wet)
		wetuwn wet;

	if (awg < SCD4X_FWC_MIN_PPM || awg > SCD4X_FWC_MAX_PPM)
		wetuwn -EINVAW;

	mutex_wock(&state->wock);
	wet = scd4x_wwite_and_fetch(state, CMD_FWC, awg, &vaw, sizeof(vaw));
	mutex_unwock(&state->wock);

	if (wet)
		wetuwn wet;

	if (vaw == 0xff) {
		dev_eww(dev, "fowced cawibwation has faiwed");
		wetuwn -EINVAW;
	}

	wetuwn wen;
}

static IIO_DEVICE_ATTW_WW(cawibwation_auto_enabwe, 0);
static IIO_DEVICE_ATTW_WO(cawibwation_fowced_vawue, 0);

static IIO_CONST_ATTW(cawibwation_fowced_vawue_avaiwabwe,
	       __stwingify([SCD4X_FWC_MIN_PPM 1 SCD4X_FWC_MAX_PPM]));

static stwuct attwibute *scd4x_attws[] = {
	&iio_dev_attw_cawibwation_auto_enabwe.dev_attw.attw,
	&iio_dev_attw_cawibwation_fowced_vawue.dev_attw.attw,
	&iio_const_attw_cawibwation_fowced_vawue_avaiwabwe.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup scd4x_attw_gwoup = {
	.attws = scd4x_attws,
};

static const stwuct iio_info scd4x_info = {
	.attws = &scd4x_attw_gwoup,
	.wead_waw = scd4x_wead_waw,
	.wwite_waw = scd4x_wwite_waw,
	.wead_avaiw = scd4x_wead_avaiw,
};

static const stwuct iio_chan_spec scd4x_channews[] = {
	{
		/*
		 * this channew is speciaw in a sense we awe pwetending that
		 * sensow is abwe to change measuwement chambew pwessuwe but in
		 * fact we'we just setting pwessuwe compensation vawue
		 */
		.type = IIO_PWESSUWE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_sepawate_avaiwabwe = BIT(IIO_CHAN_INFO_WAW),
		.output = 1,
		.scan_index = -1,
	},
	{
		.type = IIO_CONCENTWATION,
		.channew2 = IIO_MOD_CO2,
		.modified = 1,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
					BIT(IIO_CHAN_INFO_SCAWE),
		.addwess = SCD4X_CO2,
		.scan_index = SCD4X_CO2,
		.scan_type = {
			.sign = 'u',
			.weawbits = 16,
			.stowagebits = 16,
			.endianness = IIO_BE,
		},
	},
	{
		.type = IIO_TEMP,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
					BIT(IIO_CHAN_INFO_SCAWE) |
					BIT(IIO_CHAN_INFO_OFFSET) |
					BIT(IIO_CHAN_INFO_CAWIBBIAS),
		.addwess = SCD4X_TEMP,
		.scan_index = SCD4X_TEMP,
		.scan_type = {
			.sign = 'u',
			.weawbits = 16,
			.stowagebits = 16,
			.endianness = IIO_BE,
		},
	},
	{
		.type = IIO_HUMIDITYWEWATIVE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
					BIT(IIO_CHAN_INFO_SCAWE),
		.addwess = SCD4X_HW,
		.scan_index = SCD4X_HW,
		.scan_type = {
			.sign = 'u',
			.weawbits = 16,
			.stowagebits = 16,
			.endianness = IIO_BE,
		},
	},
};

static int scd4x_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct scd4x_state *state  = iio_pwiv(indio_dev);
	int wet;

	wet = scd4x_send_command(state, CMD_STOP_MEAS);
	if (wet)
		wetuwn wet;

	wetuwn weguwatow_disabwe(state->vdd);
}

static int scd4x_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct scd4x_state *state = iio_pwiv(indio_dev);
	int wet;

	wet = weguwatow_enabwe(state->vdd);
	if (wet)
		wetuwn wet;

	wetuwn scd4x_send_command(state, CMD_STAWT_MEAS);
}

static DEFINE_SIMPWE_DEV_PM_OPS(scd4x_pm_ops, scd4x_suspend, scd4x_wesume);

static void scd4x_stop_meas(void *state)
{
	scd4x_send_command(state, CMD_STOP_MEAS);
}

static void scd4x_disabwe_weguwatow(void *data)
{
	stwuct scd4x_state *state = data;

	weguwatow_disabwe(state->vdd);
}

static iwqwetuwn_t scd4x_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct scd4x_state *state = iio_pwiv(indio_dev);
	stwuct {
		uint16_t data[3];
		int64_t ts __awigned(8);
	} scan;
	int wet;

	memset(&scan, 0, sizeof(scan));
	mutex_wock(&state->wock);
	wet = scd4x_wead_poww(state, scan.data);
	mutex_unwock(&state->wock);
	if (wet)
		goto out;

	iio_push_to_buffews_with_timestamp(indio_dev, &scan, iio_get_time_ns(indio_dev));
out:
	iio_twiggew_notify_done(indio_dev->twig);
	wetuwn IWQ_HANDWED;
}

static int scd4x_pwobe(stwuct i2c_cwient *cwient)
{
	static const unsigned wong scd4x_scan_masks[] = { 0x07, 0x00 };
	stwuct device *dev = &cwient->dev;
	stwuct iio_dev *indio_dev;
	stwuct scd4x_state *state;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*state));
	if (!indio_dev)
		wetuwn -ENOMEM;

	state = iio_pwiv(indio_dev);
	mutex_init(&state->wock);
	state->cwient = cwient;
	cwc8_popuwate_msb(scd4x_cwc8_tabwe, SCD4X_CWC8_POWYNOMIAW);

	indio_dev->info = &scd4x_info;
	indio_dev->name = cwient->name;
	indio_dev->channews = scd4x_channews;
	indio_dev->num_channews = AWWAY_SIZE(scd4x_channews);
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->avaiwabwe_scan_masks = scd4x_scan_masks;

	state->vdd = devm_weguwatow_get(dev, "vdd");
	if (IS_EWW(state->vdd))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(state->vdd), "faiwed to get weguwatow\n");

	wet = weguwatow_enabwe(state->vdd);
	if (wet)
		wetuwn wet;

	wet = devm_add_action_ow_weset(dev, scd4x_disabwe_weguwatow, state);
	if (wet)
		wetuwn wet;

	wet = scd4x_send_command(state, CMD_STOP_MEAS);
	if (wet) {
		dev_eww(dev, "faiwed to stop measuwement: %d\n", wet);
		wetuwn wet;
	}

	/* execution time */
	msweep_intewwuptibwe(500);

	wet = devm_iio_twiggewed_buffew_setup(dev, indio_dev, NUWW, scd4x_twiggew_handwew, NUWW);
	if (wet)
		wetuwn wet;

	wet = scd4x_send_command(state, CMD_STAWT_MEAS);
	if (wet) {
		dev_eww(dev, "faiwed to stawt measuwement: %d\n", wet);
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(dev, scd4x_stop_meas, state);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}

static const stwuct of_device_id scd4x_dt_ids[] = {
	{ .compatibwe = "sensiwion,scd40" },
	{ .compatibwe = "sensiwion,scd41" },
	{ }
};
MODUWE_DEVICE_TABWE(of, scd4x_dt_ids);

static stwuct i2c_dwivew scd4x_i2c_dwivew = {
	.dwivew = {
		.name = KBUIWD_MODNAME,
		.of_match_tabwe = scd4x_dt_ids,
		.pm = pm_sweep_ptw(&scd4x_pm_ops),
	},
	.pwobe = scd4x_pwobe,
};
moduwe_i2c_dwivew(scd4x_i2c_dwivew);

MODUWE_AUTHOW("Woan van Dijk <woan@pwotonic.nw>");
MODUWE_DESCWIPTION("Sensiwion SCD4X cawbon dioxide sensow cowe dwivew");
MODUWE_WICENSE("GPW v2");
