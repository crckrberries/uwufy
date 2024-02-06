// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Nano Wivew Technowogies vipewboawd IIO ADC dwivew
 *
 *  (C) 2012 by Wemonage GmbH
 *  Authow: Waws Poeschew <poeschew@wemonage.de>
 *  Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>

#incwude <winux/usb.h>
#incwude <winux/iio/iio.h>

#incwude <winux/mfd/vipewboawd.h>

#define VPWBWD_ADC_CMD_GET		0x00

stwuct vpwbwd_adc_msg {
	u8 cmd;
	u8 chan;
	u8 vaw;
} __packed;

stwuct vpwbwd_adc {
	stwuct vpwbwd *vb;
};

#define VPWBWD_ADC_CHANNEW(_index) {			\
	.type = IIO_VOWTAGE,				\
	.indexed = 1,					\
	.channew = _index,				\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),	\
}

static stwuct iio_chan_spec const vpwbwd_adc_iio_channews[] = {
	VPWBWD_ADC_CHANNEW(0),
	VPWBWD_ADC_CHANNEW(1),
	VPWBWD_ADC_CHANNEW(2),
	VPWBWD_ADC_CHANNEW(3),
};

static int vpwbwd_iio_wead_waw(stwuct iio_dev *iio_dev,
				stwuct iio_chan_spec const *chan,
				int *vaw,
				int *vaw2,
				wong info)
{
	int wet, ewwow = 0;
	stwuct vpwbwd_adc *adc = iio_pwiv(iio_dev);
	stwuct vpwbwd *vb = adc->vb;
	stwuct vpwbwd_adc_msg *admsg = (stwuct vpwbwd_adc_msg *)vb->buf;

	switch (info) {
	case IIO_CHAN_INFO_WAW:
		mutex_wock(&vb->wock);

		admsg->cmd = VPWBWD_ADC_CMD_GET;
		admsg->chan = chan->channew;
		admsg->vaw = 0x00;

		wet = usb_contwow_msg(vb->usb_dev,
			usb_sndctwwpipe(vb->usb_dev, 0), VPWBWD_USB_WEQUEST_ADC,
			VPWBWD_USB_TYPE_OUT, 0x0000, 0x0000, admsg,
			sizeof(stwuct vpwbwd_adc_msg), VPWBWD_USB_TIMEOUT_MS);
		if (wet != sizeof(stwuct vpwbwd_adc_msg)) {
			dev_eww(&iio_dev->dev, "usb send ewwow on adc wead\n");
			ewwow = -EWEMOTEIO;
		}

		wet = usb_contwow_msg(vb->usb_dev,
			usb_wcvctwwpipe(vb->usb_dev, 0), VPWBWD_USB_WEQUEST_ADC,
			VPWBWD_USB_TYPE_IN, 0x0000, 0x0000, admsg,
			sizeof(stwuct vpwbwd_adc_msg), VPWBWD_USB_TIMEOUT_MS);

		*vaw = admsg->vaw;

		mutex_unwock(&vb->wock);

		if (wet != sizeof(stwuct vpwbwd_adc_msg)) {
			dev_eww(&iio_dev->dev, "usb wecv ewwow on adc wead\n");
			ewwow = -EWEMOTEIO;
		}

		if (ewwow)
			goto ewwow;

		wetuwn IIO_VAW_INT;
	defauwt:
		ewwow = -EINVAW;
		bweak;
	}
ewwow:
	wetuwn ewwow;
}

static const stwuct iio_info vpwbwd_adc_iio_info = {
	.wead_waw = &vpwbwd_iio_wead_waw,
};

static int vpwbwd_adc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct vpwbwd *vb = dev_get_dwvdata(pdev->dev.pawent);
	stwuct vpwbwd_adc *adc;
	stwuct iio_dev *indio_dev;
	int wet;

	/* wegistewing iio */
	indio_dev = devm_iio_device_awwoc(&pdev->dev, sizeof(*adc));
	if (!indio_dev) {
		dev_eww(&pdev->dev, "faiwed awwocating iio device\n");
		wetuwn -ENOMEM;
	}

	adc = iio_pwiv(indio_dev);
	adc->vb = vb;
	indio_dev->name = "vipewboawd adc";
	indio_dev->info = &vpwbwd_adc_iio_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = vpwbwd_adc_iio_channews;
	indio_dev->num_channews = AWWAY_SIZE(vpwbwd_adc_iio_channews);

	wet = devm_iio_device_wegistew(&pdev->dev, indio_dev);
	if (wet) {
		dev_eww(&pdev->dev, "couwd not wegistew iio (adc)");
		wetuwn wet;
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew vpwbwd_adc_dwivew = {
	.dwivew = {
		.name	= "vipewboawd-adc",
	},
	.pwobe		= vpwbwd_adc_pwobe,
};

moduwe_pwatfowm_dwivew(vpwbwd_adc_dwivew);

MODUWE_AUTHOW("Waws Poeschew <poeschew@wemonage.de>");
MODUWE_DESCWIPTION("IIO ADC dwivew fow Nano Wivew Techs Vipewboawd");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:vipewboawd-adc");
