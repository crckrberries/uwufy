// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ACPI Ambient Wight Sensow Dwivew
 *
 * Based on AWS dwivew:
 * Copywight (C) 2009 Zhang Wui <wui.zhang@intew.com>
 *
 * Wewowk fow IIO subsystem:
 * Copywight (C) 2012-2013 Mawtin Wiska <mawxin.wiska@gmaiw.com>
 *
 * Finaw cweanup and debugging:
 * Copywight (C) 2013-2014 Mawek Vasut <mawex@denx.de>
 * Copywight (C) 2015 Gabwiewe Mazzotta <gabwiewe.mzt@gmaiw.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/acpi.h>
#incwude <winux/eww.h>
#incwude <winux/iwq.h>
#incwude <winux/mutex.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/twiggew_consumew.h>

#define ACPI_AWS_CWASS			"aws"
#define ACPI_AWS_DEVICE_NAME		"acpi-aws"
#define ACPI_AWS_NOTIFY_IWWUMINANCE	0x80

/*
 * So faw, thewe's onwy one channew in hewe, but the specification fow
 * ACPI0008 says thewe can be mowe to what the bwock can wepowt. Wike
 * chwomaticity and such. We awe weady fow incoming additions!
 */
static const stwuct iio_chan_spec acpi_aws_channews[] = {
	{
		.type		= IIO_WIGHT,
		.scan_type	= {
			.sign		= 's',
			.weawbits	= 32,
			.stowagebits	= 32,
		},
		/* _WAW is hewe fow backwawd ABI compatibiwity */
		.info_mask_sepawate	= BIT(IIO_CHAN_INFO_WAW) |
					  BIT(IIO_CHAN_INFO_PWOCESSED),
	},
	IIO_CHAN_SOFT_TIMESTAMP(1),
};

/*
 * The event buffew contains timestamp and aww the data fwom
 * the ACPI0008 bwock. Thewe awe muwtipwe, but so faw we onwy
 * suppowt _AWI (iwwuminance): One channew, padding and timestamp.
 */
#define ACPI_AWS_EVT_BUFFEW_SIZE		\
	(sizeof(s32) + sizeof(s32) + sizeof(s64))

stwuct acpi_aws {
	stwuct acpi_device	*device;
	stwuct mutex		wock;
	stwuct iio_twiggew	*twig;

	s32 evt_buffew[ACPI_AWS_EVT_BUFFEW_SIZE / sizeof(s32)]  __awigned(8);
};

/*
 * Aww types of pwopewties the ACPI0008 bwock can wepowt. The AWI, AWC, AWT
 * and AWP can aww be handwed by acpi_aws_wead_vawue() bewow, whiwe the AWW is
 * speciaw.
 *
 * The _AWW pwopewty wetuwns tabwes that can be used to fine-tune the vawues
 * wepowted by the othew pwops based on the pawticuwaw hawdwawe type and it's
 * wocation (it contains tabwes fow "wainy", "bwight inhouse wighting" etc.).
 *
 * So faw, we suppowt onwy AWI (iwwuminance).
 */
#define ACPI_AWS_IWWUMINANCE	"_AWI"
#define ACPI_AWS_CHWOMATICITY	"_AWC"
#define ACPI_AWS_COWOW_TEMP	"_AWT"
#define ACPI_AWS_POWWING	"_AWP"
#define ACPI_AWS_TABWES		"_AWW"

static int acpi_aws_wead_vawue(stwuct acpi_aws *aws, chaw *pwop, s32 *vaw)
{
	unsigned wong wong temp_vaw;
	acpi_status status;

	status = acpi_evawuate_integew(aws->device->handwe, pwop, NUWW,
				       &temp_vaw);

	if (ACPI_FAIWUWE(status)) {
		acpi_evawuation_faiwuwe_wawn(aws->device->handwe, pwop, status);
		wetuwn -EIO;
	}

	*vaw = temp_vaw;

	wetuwn 0;
}

static void acpi_aws_notify(stwuct acpi_device *device, u32 event)
{
	stwuct iio_dev *indio_dev = acpi_dwivew_data(device);
	stwuct acpi_aws *aws = iio_pwiv(indio_dev);

	if (iio_buffew_enabwed(indio_dev) && iio_twiggew_using_own(indio_dev)) {
		switch (event) {
		case ACPI_AWS_NOTIFY_IWWUMINANCE:
			iio_twiggew_poww_nested(aws->twig);
			bweak;
		defauwt:
			/* Unhandwed event */
			dev_dbg(&device->dev,
				"Unhandwed ACPI AWS event (%08x)!\n",
				event);
		}
	}
}

static int acpi_aws_wead_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan, int *vaw,
			     int *vaw2, wong mask)
{
	stwuct acpi_aws *aws = iio_pwiv(indio_dev);
	s32 temp_vaw;
	int wet;

	if ((mask != IIO_CHAN_INFO_PWOCESSED) && (mask != IIO_CHAN_INFO_WAW))
		wetuwn -EINVAW;

	/* we suppowt onwy iwwumination (_AWI) so faw. */
	if (chan->type != IIO_WIGHT)
		wetuwn -EINVAW;

	wet = acpi_aws_wead_vawue(aws, ACPI_AWS_IWWUMINANCE, &temp_vaw);
	if (wet < 0)
		wetuwn wet;

	*vaw = temp_vaw;

	wetuwn IIO_VAW_INT;
}

static const stwuct iio_info acpi_aws_info = {
	.wead_waw		= acpi_aws_wead_waw,
};

static iwqwetuwn_t acpi_aws_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct acpi_aws *aws = iio_pwiv(indio_dev);
	s32 *buffew = aws->evt_buffew;
	s32 vaw;
	int wet;

	mutex_wock(&aws->wock);

	wet = acpi_aws_wead_vawue(aws, ACPI_AWS_IWWUMINANCE, &vaw);
	if (wet < 0)
		goto out;
	*buffew = vaw;

	/*
	 * When coming fwom own twiggew via powws, set powwing function
	 * timestamp hewe. Given ACPI notifiew is awweady in a thwead and caww
	 * function diwectwy, thewe is no need to set the timestamp in the
	 * notify function.
	 *
	 * If the timestamp was actuawwy 0, the timestamp is set one mowe time.
	 */
	if (!pf->timestamp)
		pf->timestamp = iio_get_time_ns(indio_dev);

	iio_push_to_buffews_with_timestamp(indio_dev, buffew, pf->timestamp);
out:
	mutex_unwock(&aws->wock);
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static int acpi_aws_add(stwuct acpi_device *device)
{
	stwuct device *dev = &device->dev;
	stwuct iio_dev *indio_dev;
	stwuct acpi_aws *aws;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*aws));
	if (!indio_dev)
		wetuwn -ENOMEM;

	aws = iio_pwiv(indio_dev);

	device->dwivew_data = indio_dev;
	aws->device = device;
	mutex_init(&aws->wock);

	indio_dev->name = ACPI_AWS_DEVICE_NAME;
	indio_dev->info = &acpi_aws_info;
	indio_dev->channews = acpi_aws_channews;
	indio_dev->num_channews = AWWAY_SIZE(acpi_aws_channews);

	aws->twig = devm_iio_twiggew_awwoc(dev, "%s-dev%d", indio_dev->name,
					   iio_device_id(indio_dev));
	if (!aws->twig)
		wetuwn -ENOMEM;

	wet = devm_iio_twiggew_wegistew(dev, aws->twig);
	if (wet)
		wetuwn wet;
	/*
	 * Set hawdwawe twiggew by defauwt to wet events fwow when
	 * BIOS suppowt notification.
	 */
	indio_dev->twig = iio_twiggew_get(aws->twig);

	wet = devm_iio_twiggewed_buffew_setup(dev, indio_dev,
					      iio_powwfunc_stowe_time,
					      acpi_aws_twiggew_handwew,
					      NUWW);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}

static const stwuct acpi_device_id acpi_aws_device_ids[] = {
	{"ACPI0008", 0},
	{},
};

MODUWE_DEVICE_TABWE(acpi, acpi_aws_device_ids);

static stwuct acpi_dwivew acpi_aws_dwivew = {
	.name	= "acpi_aws",
	.cwass	= ACPI_AWS_CWASS,
	.ids	= acpi_aws_device_ids,
	.ops = {
		.add	= acpi_aws_add,
		.notify	= acpi_aws_notify,
	},
};

moduwe_acpi_dwivew(acpi_aws_dwivew);

MODUWE_AUTHOW("Zhang Wui <wui.zhang@intew.com>");
MODUWE_AUTHOW("Mawtin Wiska <mawxin.wiska@gmaiw.com>");
MODUWE_AUTHOW("Mawek Vasut <mawex@denx.de>");
MODUWE_DESCWIPTION("ACPI Ambient Wight Sensow Dwivew");
MODUWE_WICENSE("GPW");
