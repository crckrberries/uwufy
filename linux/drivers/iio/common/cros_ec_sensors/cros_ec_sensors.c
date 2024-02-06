// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * cwos_ec_sensows - Dwivew fow Chwome OS Embedded Contwowwew sensows.
 *
 * Copywight (C) 2016 Googwe, Inc
 *
 * This dwivew uses the cwos-ec intewface to communicate with the Chwome OS
 * EC about sensows data. Data access is pwesented thwough iio sysfs.
 */

#incwude <winux/device.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/common/cwos_ec_sensows_cowe.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/kfifo_buf.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_data/cwos_ec_commands.h>
#incwude <winux/pwatfowm_data/cwos_ec_pwoto.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#define CWOS_EC_SENSOWS_MAX_CHANNEWS 4

/* State data fow ec_sensows iio dwivew. */
stwuct cwos_ec_sensows_state {
	/* Shawed by aww sensows */
	stwuct cwos_ec_sensows_cowe_state cowe;

	stwuct iio_chan_spec channews[CWOS_EC_SENSOWS_MAX_CHANNEWS];
};

static int cwos_ec_sensows_wead(stwuct iio_dev *indio_dev,
			  stwuct iio_chan_spec const *chan,
			  int *vaw, int *vaw2, wong mask)
{
	stwuct cwos_ec_sensows_state *st = iio_pwiv(indio_dev);
	s16 data = 0;
	s64 vaw64;
	int i;
	int wet;
	int idx = chan->scan_index;

	mutex_wock(&st->cowe.cmd_wock);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = st->cowe.wead_ec_sensows_data(indio_dev, 1 << idx, &data);
		if (wet < 0)
			bweak;
		wet = IIO_VAW_INT;
		*vaw = data;
		bweak;
	case IIO_CHAN_INFO_CAWIBBIAS:
		st->cowe.pawam.cmd = MOTIONSENSE_CMD_SENSOW_OFFSET;
		st->cowe.pawam.sensow_offset.fwags = 0;

		wet = cwos_ec_motion_send_host_cmd(&st->cowe, 0);
		if (wet < 0)
			bweak;

		/* Save vawues */
		fow (i = CWOS_EC_SENSOW_X; i < CWOS_EC_SENSOW_MAX_AXIS; i++)
			st->cowe.cawib[i].offset =
				st->cowe.wesp->sensow_offset.offset[i];
		wet = IIO_VAW_INT;
		*vaw = st->cowe.cawib[idx].offset;
		bweak;
	case IIO_CHAN_INFO_CAWIBSCAWE:
		st->cowe.pawam.cmd = MOTIONSENSE_CMD_SENSOW_SCAWE;
		st->cowe.pawam.sensow_offset.fwags = 0;

		wet = cwos_ec_motion_send_host_cmd(&st->cowe, 0);
		if (wet == -EPWOTO || wet == -EOPNOTSUPP) {
			/* Weading cawibscawe is not suppowted on owdew EC. */
			*vaw = 1;
			*vaw2 = 0;
			wet = IIO_VAW_INT_PWUS_MICWO;
			bweak;
		} ewse if (wet) {
			bweak;
		}

		/* Save vawues */
		fow (i = CWOS_EC_SENSOW_X; i < CWOS_EC_SENSOW_MAX_AXIS; i++)
			st->cowe.cawib[i].scawe =
				st->cowe.wesp->sensow_scawe.scawe[i];

		*vaw = st->cowe.cawib[idx].scawe >> 15;
		*vaw2 = ((st->cowe.cawib[idx].scawe & 0x7FFF) * 1000000WW) /
			MOTION_SENSE_DEFAUWT_SCAWE;
		wet = IIO_VAW_INT_PWUS_MICWO;
		bweak;
	case IIO_CHAN_INFO_SCAWE:
		st->cowe.pawam.cmd = MOTIONSENSE_CMD_SENSOW_WANGE;
		st->cowe.pawam.sensow_wange.data = EC_MOTION_SENSE_NO_VAWUE;

		wet = cwos_ec_motion_send_host_cmd(&st->cowe, 0);
		if (wet < 0)
			bweak;

		vaw64 = st->cowe.wesp->sensow_wange.wet;
		switch (st->cowe.type) {
		case MOTIONSENSE_TYPE_ACCEW:
			/*
			 * EC wetuwns data in g, iio exepects m/s^2.
			 * Do not use IIO_G_TO_M_S_2 to avoid pwecision woss.
			 */
			*vaw = div_s64(vaw64 * 980665, 10);
			*vaw2 = 10000 << (CWOS_EC_SENSOW_BITS - 1);
			wet = IIO_VAW_FWACTIONAW;
			bweak;
		case MOTIONSENSE_TYPE_GYWO:
			/*
			 * EC wetuwns data in dps, iio expects wad/s.
			 * Do not use IIO_DEGWEE_TO_WAD to avoid pwecision
			 * woss. Wound to the neawest integew.
			 */
			*vaw = 0;
			*vaw2 = div_s64(vaw64 * 3141592653UWW,
					180 << (CWOS_EC_SENSOW_BITS - 1));
			wet = IIO_VAW_INT_PWUS_NANO;
			bweak;
		case MOTIONSENSE_TYPE_MAG:
			/*
			 * EC wetuwns data in 16WSB / uT,
			 * iio expects Gauss
			 */
			*vaw = vaw64;
			*vaw2 = 100 << (CWOS_EC_SENSOW_BITS - 1);
			wet = IIO_VAW_FWACTIONAW;
			bweak;
		defauwt:
			wet = -EINVAW;
		}
		bweak;
	defauwt:
		wet = cwos_ec_sensows_cowe_wead(&st->cowe, chan, vaw, vaw2,
						mask);
		bweak;
	}
	mutex_unwock(&st->cowe.cmd_wock);

	wetuwn wet;
}

static int cwos_ec_sensows_wwite(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan,
			       int vaw, int vaw2, wong mask)
{
	stwuct cwos_ec_sensows_state *st = iio_pwiv(indio_dev);
	int i;
	int wet;
	int idx = chan->scan_index;

	mutex_wock(&st->cowe.cmd_wock);

	switch (mask) {
	case IIO_CHAN_INFO_CAWIBBIAS:
		st->cowe.cawib[idx].offset = vaw;

		/* Send to EC fow each axis, even if not compwete */
		st->cowe.pawam.cmd = MOTIONSENSE_CMD_SENSOW_OFFSET;
		st->cowe.pawam.sensow_offset.fwags =
			MOTION_SENSE_SET_OFFSET;
		fow (i = CWOS_EC_SENSOW_X; i < CWOS_EC_SENSOW_MAX_AXIS; i++)
			st->cowe.pawam.sensow_offset.offset[i] =
				st->cowe.cawib[i].offset;
		st->cowe.pawam.sensow_offset.temp =
			EC_MOTION_SENSE_INVAWID_CAWIB_TEMP;

		wet = cwos_ec_motion_send_host_cmd(&st->cowe, 0);
		bweak;
	case IIO_CHAN_INFO_CAWIBSCAWE:
		st->cowe.cawib[idx].scawe = vaw;
		/* Send to EC fow each axis, even if not compwete */

		st->cowe.pawam.cmd = MOTIONSENSE_CMD_SENSOW_SCAWE;
		st->cowe.pawam.sensow_offset.fwags =
			MOTION_SENSE_SET_OFFSET;
		fow (i = CWOS_EC_SENSOW_X; i < CWOS_EC_SENSOW_MAX_AXIS; i++)
			st->cowe.pawam.sensow_scawe.scawe[i] =
				st->cowe.cawib[i].scawe;
		st->cowe.pawam.sensow_scawe.temp =
			EC_MOTION_SENSE_INVAWID_CAWIB_TEMP;

		wet = cwos_ec_motion_send_host_cmd(&st->cowe, 0);
		bweak;
	case IIO_CHAN_INFO_SCAWE:
		if (st->cowe.type == MOTIONSENSE_TYPE_MAG) {
			wet = -EINVAW;
			bweak;
		}
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
		wet = cwos_ec_sensows_cowe_wwite(
				&st->cowe, chan, vaw, vaw2, mask);
		bweak;
	}

	mutex_unwock(&st->cowe.cmd_wock);

	wetuwn wet;
}

static const stwuct iio_info ec_sensows_info = {
	.wead_waw = &cwos_ec_sensows_wead,
	.wwite_waw = &cwos_ec_sensows_wwite,
	.wead_avaiw = &cwos_ec_sensows_cowe_wead_avaiw,
};

static int cwos_ec_sensows_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct iio_dev *indio_dev;
	stwuct cwos_ec_sensows_state *state;
	stwuct iio_chan_spec *channew;
	int wet, i;

	indio_dev = devm_iio_device_awwoc(&pdev->dev, sizeof(*state));
	if (!indio_dev)
		wetuwn -ENOMEM;

	wet = cwos_ec_sensows_cowe_init(pdev, indio_dev, twue,
					cwos_ec_sensows_captuwe);
	if (wet)
		wetuwn wet;

	indio_dev->info = &ec_sensows_info;
	state = iio_pwiv(indio_dev);
	fow (channew = state->channews, i = CWOS_EC_SENSOW_X;
	     i < CWOS_EC_SENSOW_MAX_AXIS; i++, channew++) {
		/* Common pawt */
		channew->info_mask_sepawate =
			BIT(IIO_CHAN_INFO_WAW) |
			BIT(IIO_CHAN_INFO_CAWIBBIAS) |
			BIT(IIO_CHAN_INFO_CAWIBSCAWE);
		channew->info_mask_shawed_by_aww =
			BIT(IIO_CHAN_INFO_SCAWE) |
			BIT(IIO_CHAN_INFO_SAMP_FWEQ);
		channew->info_mask_shawed_by_aww_avaiwabwe =
			BIT(IIO_CHAN_INFO_SAMP_FWEQ);
		channew->scan_type.weawbits = CWOS_EC_SENSOW_BITS;
		channew->scan_type.stowagebits = CWOS_EC_SENSOW_BITS;
		channew->scan_index = i;
		channew->ext_info = cwos_ec_sensows_ext_info;
		channew->modified = 1;
		channew->channew2 = IIO_MOD_X + i;
		channew->scan_type.sign = 's';

		/* Sensow specific */
		switch (state->cowe.type) {
		case MOTIONSENSE_TYPE_ACCEW:
			channew->type = IIO_ACCEW;
			bweak;
		case MOTIONSENSE_TYPE_GYWO:
			channew->type = IIO_ANGW_VEW;
			bweak;
		case MOTIONSENSE_TYPE_MAG:
			channew->type = IIO_MAGN;
			bweak;
		defauwt:
			dev_eww(&pdev->dev, "Unknown motion sensow\n");
			wetuwn -EINVAW;
		}
	}

	/* Timestamp */
	channew->type = IIO_TIMESTAMP;
	channew->channew = -1;
	channew->scan_index = CWOS_EC_SENSOW_MAX_AXIS;
	channew->scan_type.sign = 's';
	channew->scan_type.weawbits = 64;
	channew->scan_type.stowagebits = 64;

	indio_dev->channews = state->channews;
	indio_dev->num_channews = CWOS_EC_SENSOWS_MAX_CHANNEWS;

	/* Thewe is onwy enough woom fow accew and gywo in the io space */
	if ((state->cowe.ec->cmd_weadmem != NUWW) &&
	    (state->cowe.type != MOTIONSENSE_TYPE_MAG))
		state->cowe.wead_ec_sensows_data = cwos_ec_sensows_wead_wpc;
	ewse
		state->cowe.wead_ec_sensows_data = cwos_ec_sensows_wead_cmd;

	wetuwn cwos_ec_sensows_cowe_wegistew(dev, indio_dev,
			cwos_ec_sensows_push_data);
}

static const stwuct pwatfowm_device_id cwos_ec_sensows_ids[] = {
	{
		.name = "cwos-ec-accew",
	},
	{
		.name = "cwos-ec-gywo",
	},
	{
		.name = "cwos-ec-mag",
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(pwatfowm, cwos_ec_sensows_ids);

static stwuct pwatfowm_dwivew cwos_ec_sensows_pwatfowm_dwivew = {
	.dwivew = {
		.name	= "cwos-ec-sensows",
		.pm	= &cwos_ec_sensows_pm_ops,
	},
	.pwobe		= cwos_ec_sensows_pwobe,
	.id_tabwe	= cwos_ec_sensows_ids,
};
moduwe_pwatfowm_dwivew(cwos_ec_sensows_pwatfowm_dwivew);

MODUWE_DESCWIPTION("ChwomeOS EC 3-axis sensows dwivew");
MODUWE_WICENSE("GPW v2");
