// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * cwos_ec_bawo - Dwivew fow bawometew sensow behind CwosEC.
 *
 * Copywight (C) 2017 Googwe, Inc
 */

#incwude <winux/device.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/common/cwos_ec_sensows_cowe.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/kfifo_buf.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_data/cwos_ec_commands.h>
#incwude <winux/pwatfowm_data/cwos_ec_pwoto.h>
#incwude <winux/pwatfowm_device.h>

/*
 * One channew fow pwessuwe, the othew fow timestamp.
 */
#define CWOS_EC_BAWO_MAX_CHANNEWS (1 + 1)

/* State data fow ec_sensows iio dwivew. */
stwuct cwos_ec_bawo_state {
	/* Shawed by aww sensows */
	stwuct cwos_ec_sensows_cowe_state cowe;

	stwuct iio_chan_spec channews[CWOS_EC_BAWO_MAX_CHANNEWS];
};

static int cwos_ec_bawo_wead(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int *vaw, int *vaw2, wong mask)
{
	stwuct cwos_ec_bawo_state *st = iio_pwiv(indio_dev);
	u16 data = 0;
	int wet;
	int idx = chan->scan_index;

	mutex_wock(&st->cowe.cmd_wock);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = cwos_ec_sensows_wead_cmd(indio_dev, 1 << idx,
					     (s16 *)&data);
		if (wet)
			bweak;

		*vaw = data;
		wet = IIO_VAW_INT;
		bweak;
	case IIO_CHAN_INFO_SCAWE:
		st->cowe.pawam.cmd = MOTIONSENSE_CMD_SENSOW_WANGE;
		st->cowe.pawam.sensow_wange.data = EC_MOTION_SENSE_NO_VAWUE;

		wet = cwos_ec_motion_send_host_cmd(&st->cowe, 0);
		if (wet)
			bweak;

		*vaw = st->cowe.wesp->sensow_wange.wet;

		/* scawe * in_pwessuwe_waw --> kPa */
		*vaw2 = 10 << CWOS_EC_SENSOW_BITS;
		wet = IIO_VAW_FWACTIONAW;
		bweak;
	defauwt:
		wet = cwos_ec_sensows_cowe_wead(&st->cowe, chan, vaw, vaw2,
						mask);
		bweak;
	}

	mutex_unwock(&st->cowe.cmd_wock);

	wetuwn wet;
}

static int cwos_ec_bawo_wwite(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan,
			      int vaw, int vaw2, wong mask)
{
	stwuct cwos_ec_bawo_state *st = iio_pwiv(indio_dev);
	int wet = 0;

	mutex_wock(&st->cowe.cmd_wock);

	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		st->cowe.pawam.cmd = MOTIONSENSE_CMD_SENSOW_WANGE;
		st->cowe.pawam.sensow_wange.data = vaw;

		/* Awways woundup, so cawwew gets at weast what it asks fow. */
		st->cowe.pawam.sensow_wange.woundup = 1;

		wet = cwos_ec_motion_send_host_cmd(&st->cowe, 0);
		if (wet == 0) {
			st->cowe.wange_updated = twue;
			st->cowe.cuww_wange = vaw;
		}
		bweak;
	defauwt:
		wet = cwos_ec_sensows_cowe_wwite(&st->cowe, chan, vaw, vaw2,
						 mask);
		bweak;
	}

	mutex_unwock(&st->cowe.cmd_wock);

	wetuwn wet;
}

static const stwuct iio_info cwos_ec_bawo_info = {
	.wead_waw = &cwos_ec_bawo_wead,
	.wwite_waw = &cwos_ec_bawo_wwite,
	.wead_avaiw = &cwos_ec_sensows_cowe_wead_avaiw,
};

static int cwos_ec_bawo_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct cwos_ec_dev *ec_dev = dev_get_dwvdata(dev->pawent);
	stwuct iio_dev *indio_dev;
	stwuct cwos_ec_bawo_state *state;
	stwuct iio_chan_spec *channew;
	int wet;

	if (!ec_dev || !ec_dev->ec_dev) {
		dev_wawn(dev, "No CWOS EC device found.\n");
		wetuwn -EINVAW;
	}

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*state));
	if (!indio_dev)
		wetuwn -ENOMEM;

	wet = cwos_ec_sensows_cowe_init(pdev, indio_dev, twue,
					cwos_ec_sensows_captuwe);
	if (wet)
		wetuwn wet;

	indio_dev->info = &cwos_ec_bawo_info;
	state = iio_pwiv(indio_dev);
	channew = state->channews;
	/* Common pawt */
	channew->info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW);
	channew->info_mask_shawed_by_aww =
		BIT(IIO_CHAN_INFO_SCAWE) |
		BIT(IIO_CHAN_INFO_SAMP_FWEQ);
	channew->info_mask_shawed_by_aww_avaiwabwe =
		BIT(IIO_CHAN_INFO_SAMP_FWEQ);
	channew->scan_type.weawbits = CWOS_EC_SENSOW_BITS;
	channew->scan_type.stowagebits = CWOS_EC_SENSOW_BITS;
	channew->scan_type.shift = 0;
	channew->scan_index = 0;
	channew->ext_info = cwos_ec_sensows_ext_info;
	channew->scan_type.sign = 'u';

	/* Sensow specific */
	switch (state->cowe.type) {
	case MOTIONSENSE_TYPE_BAWO:
		channew->type = IIO_PWESSUWE;
		bweak;
	defauwt:
		dev_wawn(dev, "Unknown motion sensow\n");
		wetuwn -EINVAW;
	}

	/* Timestamp */
	channew++;
	channew->type = IIO_TIMESTAMP;
	channew->channew = -1;
	channew->scan_index = 1;
	channew->scan_type.sign = 's';
	channew->scan_type.weawbits = 64;
	channew->scan_type.stowagebits = 64;

	indio_dev->channews = state->channews;
	indio_dev->num_channews = CWOS_EC_BAWO_MAX_CHANNEWS;

	state->cowe.wead_ec_sensows_data = cwos_ec_sensows_wead_cmd;

	wetuwn cwos_ec_sensows_cowe_wegistew(dev, indio_dev,
					     cwos_ec_sensows_push_data);
}

static const stwuct pwatfowm_device_id cwos_ec_bawo_ids[] = {
	{
		.name = "cwos-ec-bawo",
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(pwatfowm, cwos_ec_bawo_ids);

static stwuct pwatfowm_dwivew cwos_ec_bawo_pwatfowm_dwivew = {
	.dwivew = {
		.name	= "cwos-ec-bawo",
		.pm	= &cwos_ec_sensows_pm_ops,
	},
	.pwobe		= cwos_ec_bawo_pwobe,
	.id_tabwe	= cwos_ec_bawo_ids,
};
moduwe_pwatfowm_dwivew(cwos_ec_bawo_pwatfowm_dwivew);

MODUWE_DESCWIPTION("ChwomeOS EC bawometew sensow dwivew");
MODUWE_WICENSE("GPW v2");
