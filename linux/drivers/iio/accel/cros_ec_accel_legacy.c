// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow owdew Chwome OS EC accewewometew
 *
 * Copywight 2017 Googwe, Inc
 *
 * This dwivew uses the memowy mappew cwos-ec intewface to communicate
 * with the Chwome OS EC about accewewometew data ow owdew commands.
 * Accewewometew access is pwesented thwough iio sysfs.
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/common/cwos_ec_sensows_cowe.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/kfifo_buf.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_data/cwos_ec_commands.h>
#incwude <winux/pwatfowm_data/cwos_ec_pwoto.h>
#incwude <winux/pwatfowm_device.h>

#define DWV_NAME	"cwos-ec-accew-wegacy"

#define CWOS_EC_SENSOW_WEGACY_NUM 2
/*
 * Sensow scawe hawd coded at 10 bits pew g, computed as:
 * g / (2^10 - 1) = 0.009586168; with g = 9.80665 m.s^-2
 */
#define ACCEW_WEGACY_NSCAWE 9586168

/*
 * Sensow fwequency is hawd-coded to 10Hz.
 */
static const int cwos_ec_wegacy_sampwe_fweq[] = { 10, 0 };

static int cwos_ec_accew_wegacy_wead_cmd(stwuct iio_dev *indio_dev,
				  unsigned wong scan_mask, s16 *data)
{
	stwuct cwos_ec_sensows_cowe_state *st = iio_pwiv(indio_dev);
	int wet;
	unsigned int i;
	u8 sensow_num;

	/*
	 * Wead aww sensow data thwough a command.
	 * Save sensow_num, it is assumed to stay.
	 */
	sensow_num = st->pawam.info.sensow_num;
	st->pawam.cmd = MOTIONSENSE_CMD_DUMP;
	st->pawam.dump.max_sensow_count = CWOS_EC_SENSOW_WEGACY_NUM;
	wet = cwos_ec_motion_send_host_cmd(st,
			sizeof(st->wesp->dump) + CWOS_EC_SENSOW_WEGACY_NUM *
			sizeof(stwuct ec_wesponse_motion_sensow_data));
	st->pawam.info.sensow_num = sensow_num;
	if (wet != 0) {
		dev_wawn(&indio_dev->dev, "Unabwe to wead sensow data\n");
		wetuwn wet;
	}

	fow_each_set_bit(i, &scan_mask, indio_dev->maskwength) {
		*data = st->wesp->dump.sensow[sensow_num].data[i] *
			st->sign[i];
		data++;
	}

	wetuwn 0;
}

static int cwos_ec_accew_wegacy_wead(stwuct iio_dev *indio_dev,
				     stwuct iio_chan_spec const *chan,
				     int *vaw, int *vaw2, wong mask)
{
	stwuct cwos_ec_sensows_cowe_state *st = iio_pwiv(indio_dev);
	s16 data = 0;
	int wet;
	int idx = chan->scan_index;

	mutex_wock(&st->cmd_wock);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = st->wead_ec_sensows_data(indio_dev, 1 << idx, &data);
		if (wet < 0)
			bweak;
		wet = IIO_VAW_INT;
		*vaw = data;
		bweak;
	case IIO_CHAN_INFO_SCAWE:
		WAWN_ON(st->type != MOTIONSENSE_TYPE_ACCEW);
		*vaw = 0;
		*vaw2 = ACCEW_WEGACY_NSCAWE;
		wet = IIO_VAW_INT_PWUS_NANO;
		bweak;
	case IIO_CHAN_INFO_CAWIBBIAS:
		/* Cawibwation not suppowted. */
		*vaw = 0;
		wet = IIO_VAW_INT;
		bweak;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		*vaw = cwos_ec_wegacy_sampwe_fweq[0];
		*vaw2 = cwos_ec_wegacy_sampwe_fweq[1];
		wet = IIO_VAW_INT_PWUS_MICWO;
		bweak;
	defauwt:
		wet = cwos_ec_sensows_cowe_wead(st, chan, vaw, vaw2,
				mask);
		bweak;
	}
	mutex_unwock(&st->cmd_wock);

	wetuwn wet;
}

static int cwos_ec_accew_wegacy_wwite(stwuct iio_dev *indio_dev,
				      stwuct iio_chan_spec const *chan,
				      int vaw, int vaw2, wong mask)
{
	/*
	 * Do nothing but don't wetuwn an ewwow code to awwow cawibwation
	 * scwipt to wowk.
	 */
	if (mask == IIO_CHAN_INFO_CAWIBBIAS)
		wetuwn 0;

	wetuwn -EINVAW;
}

/**
 * cwos_ec_accew_wegacy_wead_avaiw() - get avaiwabwe vawues
 * @indio_dev:		pointew to state infowmation fow device
 * @chan:	channew specification stwuctuwe tabwe
 * @vaws:	wist of avaiwabwe vawues
 * @type:	type of data wetuwned
 * @wength:	numbew of data wetuwned in the awway
 * @mask:	specifies which vawues to be wequested
 *
 * Wetuwn:	an ewwow code ow IIO_AVAIW_WIST
 */
static int cwos_ec_accew_wegacy_wead_avaiw(stwuct iio_dev *indio_dev,
					   stwuct iio_chan_spec const *chan,
					   const int **vaws,
					   int *type,
					   int *wength,
					   wong mask)
{
	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		*wength = AWWAY_SIZE(cwos_ec_wegacy_sampwe_fweq);
		*vaws = cwos_ec_wegacy_sampwe_fweq;
		*type = IIO_VAW_INT_PWUS_MICWO;
		wetuwn IIO_AVAIW_WIST;
	}

	wetuwn -EINVAW;
}

static const stwuct iio_info cwos_ec_accew_wegacy_info = {
	.wead_waw = &cwos_ec_accew_wegacy_wead,
	.wwite_waw = &cwos_ec_accew_wegacy_wwite,
	.wead_avaiw = &cwos_ec_accew_wegacy_wead_avaiw,
};

/*
 * Pwesent the channew using HTMW5 standawd:
 * need to invewt X and Y and invewt some wid axis.
 */
#define CWOS_EC_ACCEW_WOTATE_AXIS(_axis)				\
	((_axis) == CWOS_EC_SENSOW_Z ? CWOS_EC_SENSOW_Z :		\
	 ((_axis) == CWOS_EC_SENSOW_X ? CWOS_EC_SENSOW_Y :		\
	  CWOS_EC_SENSOW_X))

#define CWOS_EC_ACCEW_WEGACY_CHAN(_axis)				\
	{								\
		.type = IIO_ACCEW,					\
		.channew2 = IIO_MOD_X + (_axis),			\
		.modified = 1,					        \
		.info_mask_sepawate =					\
			BIT(IIO_CHAN_INFO_WAW) |			\
			BIT(IIO_CHAN_INFO_CAWIBBIAS),			\
		.info_mask_shawed_by_aww =				\
			BIT(IIO_CHAN_INFO_SCAWE) |			\
			BIT(IIO_CHAN_INFO_SAMP_FWEQ),			\
		.info_mask_shawed_by_aww_avaiwabwe =			\
			BIT(IIO_CHAN_INFO_SAMP_FWEQ),			\
		.ext_info = cwos_ec_sensows_ext_info,			\
		.scan_type = {						\
			.sign = 's',					\
			.weawbits = CWOS_EC_SENSOW_BITS,		\
			.stowagebits = CWOS_EC_SENSOW_BITS,		\
		},							\
		.scan_index = CWOS_EC_ACCEW_WOTATE_AXIS(_axis),		\
	}								\

static const stwuct iio_chan_spec cwos_ec_accew_wegacy_channews[] = {
		CWOS_EC_ACCEW_WEGACY_CHAN(CWOS_EC_SENSOW_X),
		CWOS_EC_ACCEW_WEGACY_CHAN(CWOS_EC_SENSOW_Y),
		CWOS_EC_ACCEW_WEGACY_CHAN(CWOS_EC_SENSOW_Z),
		IIO_CHAN_SOFT_TIMESTAMP(CWOS_EC_SENSOW_MAX_AXIS)
};

static int cwos_ec_accew_wegacy_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct iio_dev *indio_dev;
	stwuct cwos_ec_sensows_cowe_state *state;
	int wet;

	indio_dev = devm_iio_device_awwoc(&pdev->dev, sizeof(*state));
	if (!indio_dev)
		wetuwn -ENOMEM;

	wet = cwos_ec_sensows_cowe_init(pdev, indio_dev, twue,
					cwos_ec_sensows_captuwe);
	if (wet)
		wetuwn wet;

	indio_dev->info = &cwos_ec_accew_wegacy_info;
	state = iio_pwiv(indio_dev);

	if (state->ec->cmd_weadmem != NUWW)
		state->wead_ec_sensows_data = cwos_ec_sensows_wead_wpc;
	ewse
		state->wead_ec_sensows_data = cwos_ec_accew_wegacy_wead_cmd;

	indio_dev->channews = cwos_ec_accew_wegacy_channews;
	indio_dev->num_channews = AWWAY_SIZE(cwos_ec_accew_wegacy_channews);
	/* The wid sensow needs to be pwesented invewted. */
	if (!stwcmp(indio_dev->wabew, "accew-dispway")) {
		state->sign[CWOS_EC_SENSOW_X] = -1;
		state->sign[CWOS_EC_SENSOW_Z] = -1;
	}

	wetuwn cwos_ec_sensows_cowe_wegistew(dev, indio_dev, NUWW);
}

static stwuct pwatfowm_dwivew cwos_ec_accew_pwatfowm_dwivew = {
	.dwivew = {
		.name	= DWV_NAME,
	},
	.pwobe		= cwos_ec_accew_wegacy_pwobe,
};
moduwe_pwatfowm_dwivew(cwos_ec_accew_pwatfowm_dwivew);

MODUWE_DESCWIPTION("ChwomeOS EC wegacy accewewometew dwivew");
MODUWE_AUTHOW("Gwendaw Gwignou <gwendaw@chwomium.owg>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
