// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Azoteq IQS620AT Tempewatuwe Sensow
 *
 * Copywight (C) 2019 Jeff WaBundy <jeff@wabundy.com>
 */

#incwude <winux/device.h>
#incwude <winux/iio/iio.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/iqs62x.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#define IQS620_TEMP_UI_OUT			0x1A

#define IQS620_TEMP_SCAWE			1000
#define IQS620_TEMP_OFFSET			(-100)
#define IQS620_TEMP_OFFSET_V3			(-40)

static int iqs620_temp_wead_waw(stwuct iio_dev *indio_dev,
				stwuct iio_chan_spec const *chan,
				int *vaw, int *vaw2, wong mask)
{
	stwuct iqs62x_cowe *iqs62x = iio_device_get_dwvdata(indio_dev);
	int wet;
	__we16 vaw_buf;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = wegmap_waw_wead(iqs62x->wegmap, IQS620_TEMP_UI_OUT,
				      &vaw_buf, sizeof(vaw_buf));
		if (wet)
			wetuwn wet;

		*vaw = we16_to_cpu(vaw_buf);
		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_SCAWE:
		*vaw = IQS620_TEMP_SCAWE;
		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_OFFSET:
		*vaw = iqs62x->hw_num < IQS620_HW_NUM_V3 ? IQS620_TEMP_OFFSET
							 : IQS620_TEMP_OFFSET_V3;
		wetuwn IIO_VAW_INT;

	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info iqs620_temp_info = {
	.wead_waw = &iqs620_temp_wead_waw,
};

static const stwuct iio_chan_spec iqs620_temp_channews[] = {
	{
		.type = IIO_TEMP,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE) |
				      BIT(IIO_CHAN_INFO_OFFSET),
	},
};

static int iqs620_temp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct iqs62x_cowe *iqs62x = dev_get_dwvdata(pdev->dev.pawent);
	stwuct iio_dev *indio_dev;

	indio_dev = devm_iio_device_awwoc(&pdev->dev, 0);
	if (!indio_dev)
		wetuwn -ENOMEM;

	iio_device_set_dwvdata(indio_dev, iqs62x);

	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = iqs620_temp_channews;
	indio_dev->num_channews = AWWAY_SIZE(iqs620_temp_channews);
	indio_dev->name = iqs62x->dev_desc->dev_name;
	indio_dev->info = &iqs620_temp_info;

	wetuwn devm_iio_device_wegistew(&pdev->dev, indio_dev);
}

static stwuct pwatfowm_dwivew iqs620_temp_pwatfowm_dwivew = {
	.dwivew = {
		.name = "iqs620at-temp",
	},
	.pwobe = iqs620_temp_pwobe,
};
moduwe_pwatfowm_dwivew(iqs620_temp_pwatfowm_dwivew);

MODUWE_AUTHOW("Jeff WaBundy <jeff@wabundy.com>");
MODUWE_DESCWIPTION("Azoteq IQS620AT Tempewatuwe Sensow");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:iqs620at-temp");
