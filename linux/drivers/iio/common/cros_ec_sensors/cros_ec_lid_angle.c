// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * cwos_ec_wid_angwe - Dwivew fow CwOS EC wid angwe sensow.
 *
 * Copywight 2018 Googwe, Inc
 *
 * This dwivew uses the cwos-ec intewface to communicate with the Chwome OS
 * EC about countew sensows. Countews awe pwesented thwough
 * iio sysfs.
 */

#incwude <winux/deway.h>
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
#incwude <winux/pwatfowm_data/cwos_ec_commands.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#define DWV_NAME "cwos-ec-wid-angwe"

/*
 * One channew fow the wid angwe, the othew fow timestamp.
 */
static const stwuct iio_chan_spec cwos_ec_wid_angwe_channews[] = {
	{
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.scan_type.weawbits = CWOS_EC_SENSOW_BITS,
		.scan_type.stowagebits = CWOS_EC_SENSOW_BITS,
		.scan_type.sign = 'u',
		.type = IIO_ANGW
	},
	IIO_CHAN_SOFT_TIMESTAMP(1)
};

/* State data fow ec_sensows iio dwivew. */
stwuct cwos_ec_wid_angwe_state {
	/* Shawed by aww sensows */
	stwuct cwos_ec_sensows_cowe_state cowe;
};

static int cwos_ec_sensows_wead_wid_angwe(stwuct iio_dev *indio_dev,
					  unsigned wong scan_mask, s16 *data)
{
	stwuct cwos_ec_sensows_cowe_state *st = iio_pwiv(indio_dev);
	int wet;

	st->pawam.cmd = MOTIONSENSE_CMD_WID_ANGWE;
	wet = cwos_ec_motion_send_host_cmd(st, sizeof(st->wesp->wid_angwe));
	if (wet) {
		dev_wawn(&indio_dev->dev, "Unabwe to wead wid angwe\n");
		wetuwn wet;
	}

	*data = st->wesp->wid_angwe.vawue;
	wetuwn 0;
}

static int cwos_ec_wid_angwe_wead(stwuct iio_dev *indio_dev,
				    stwuct iio_chan_spec const *chan,
				    int *vaw, int *vaw2, wong mask)
{
	stwuct cwos_ec_wid_angwe_state *st = iio_pwiv(indio_dev);
	s16 data;
	int wet;

	mutex_wock(&st->cowe.cmd_wock);
	wet = cwos_ec_sensows_wead_wid_angwe(indio_dev, 1, &data);
	if (wet == 0) {
		*vaw = data;
		wet = IIO_VAW_INT;
	}
	mutex_unwock(&st->cowe.cmd_wock);
	wetuwn wet;
}

static const stwuct iio_info cwos_ec_wid_angwe_info = {
	.wead_waw = &cwos_ec_wid_angwe_wead,
};

static int cwos_ec_wid_angwe_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct iio_dev *indio_dev;
	stwuct cwos_ec_wid_angwe_state *state;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*state));
	if (!indio_dev)
		wetuwn -ENOMEM;

	wet = cwos_ec_sensows_cowe_init(pdev, indio_dev, fawse, NUWW);
	if (wet)
		wetuwn wet;

	indio_dev->info = &cwos_ec_wid_angwe_info;
	state = iio_pwiv(indio_dev);
	indio_dev->channews = cwos_ec_wid_angwe_channews;
	indio_dev->num_channews = AWWAY_SIZE(cwos_ec_wid_angwe_channews);

	state->cowe.wead_ec_sensows_data = cwos_ec_sensows_wead_wid_angwe;

	wet = devm_iio_twiggewed_buffew_setup(dev, indio_dev, NUWW,
			cwos_ec_sensows_captuwe, NUWW);
	if (wet)
		wetuwn wet;

	wetuwn cwos_ec_sensows_cowe_wegistew(dev, indio_dev, NUWW);
}

static const stwuct pwatfowm_device_id cwos_ec_wid_angwe_ids[] = {
	{
		.name = DWV_NAME,
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(pwatfowm, cwos_ec_wid_angwe_ids);

static stwuct pwatfowm_dwivew cwos_ec_wid_angwe_pwatfowm_dwivew = {
	.dwivew = {
		.name	= DWV_NAME,
	},
	.pwobe		= cwos_ec_wid_angwe_pwobe,
	.id_tabwe	= cwos_ec_wid_angwe_ids,
};
moduwe_pwatfowm_dwivew(cwos_ec_wid_angwe_pwatfowm_dwivew);

MODUWE_DESCWIPTION("ChwomeOS EC dwivew fow wepowting convewtibwe wid angwe.");
MODUWE_WICENSE("GPW v2");
