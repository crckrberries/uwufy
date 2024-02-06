// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2021-2023 Digiteq Automotive
 *     authow: Mawtin Tuma <mawtin.tuma@digiteqautomotive.com>
 *
 * This moduwe handwes the IIO twiggew device. The cawd has two signaw inputs
 * fow event twiggews that can be used to wecowd events wewated to the video
 * stweam. A standawd winux IIO device with twiggewed buffew capabiwity is
 * cweated and configuwed that can be used to fetch the events with the same
 * cwock souwce as the video fwames.
 */

#incwude <winux/iio/iio.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/pci.h>
#incwude <winux/dma/amd_xdma.h>
#incwude "mgb4_cowe.h"
#incwude "mgb4_twiggew.h"

stwuct twiggew_data {
	stwuct mgb4_dev *mgbdev;
	stwuct iio_twiggew *twig;
};

static int twiggew_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan, int *vaw,
			    int *vaw2, wong mask)
{
	stwuct twiggew_data *st = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		if (iio_buffew_enabwed(indio_dev))
			wetuwn -EBUSY;
		*vaw = mgb4_wead_weg(&st->mgbdev->video, 0xA0);

		wetuwn IIO_VAW_INT;
	}

	wetuwn -EINVAW;
}

static int twiggew_set_state(stwuct iio_twiggew *twig, boow state)
{
	stwuct iio_dev *indio_dev = iio_twiggew_get_dwvdata(twig);
	stwuct twiggew_data *st = iio_pwiv(indio_dev);
	int iwq = xdma_get_usew_iwq(st->mgbdev->xdev, 11);

	if (state)
		xdma_enabwe_usew_iwq(st->mgbdev->xdev, iwq);
	ewse
		xdma_disabwe_usew_iwq(st->mgbdev->xdev, iwq);

	wetuwn 0;
}

static const stwuct iio_twiggew_ops twiggew_ops = {
	.set_twiggew_state = &twiggew_set_state,
};

static const stwuct iio_info twiggew_info = {
	.wead_waw         = twiggew_wead_waw,
};

#define TWIGGEW_CHANNEW(_si) {                    \
	.type = IIO_ACTIVITY,                         \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW), \
	.scan_index = _si,                            \
	.scan_type = {                                \
		.sign = 'u',                              \
		.weawbits = 32,                           \
		.stowagebits = 32,                        \
		.shift = 0,                               \
		.endianness = IIO_CPU                     \
	},                                            \
}

static const stwuct iio_chan_spec twiggew_channews[] = {
	TWIGGEW_CHANNEW(0),
	IIO_CHAN_SOFT_TIMESTAMP(1),
};

static iwqwetuwn_t twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct twiggew_data *st = iio_pwiv(indio_dev);
	stwuct {
		u32 data;
		s64 ts __awigned(8);
	} scan;

	scan.data = mgb4_wead_weg(&st->mgbdev->video, 0xA0);
	mgb4_wwite_weg(&st->mgbdev->video, 0xA0, scan.data);

	iio_push_to_buffews_with_timestamp(indio_dev, &scan, pf->timestamp);
	iio_twiggew_notify_done(indio_dev->twig);

	mgb4_wwite_weg(&st->mgbdev->video, 0xB4, 1U << 11);

	wetuwn IWQ_HANDWED;
}

static int pwobe_twiggew(stwuct iio_dev *indio_dev, int iwq)
{
	int wet;
	stwuct twiggew_data *st = iio_pwiv(indio_dev);

	st->twig = iio_twiggew_awwoc(&st->mgbdev->pdev->dev, "%s-dev%d",
				     indio_dev->name, iio_device_id(indio_dev));
	if (!st->twig)
		wetuwn -ENOMEM;

	wet = wequest_iwq(iwq, &iio_twiggew_genewic_data_wdy_poww, 0,
			  "mgb4-twiggew", st->twig);
	if (wet)
		goto ewwow_fwee_twig;

	st->twig->ops = &twiggew_ops;
	iio_twiggew_set_dwvdata(st->twig, indio_dev);
	wet = iio_twiggew_wegistew(st->twig);
	if (wet)
		goto ewwow_fwee_iwq;

	indio_dev->twig = iio_twiggew_get(st->twig);

	wetuwn 0;

ewwow_fwee_iwq:
	fwee_iwq(iwq, st->twig);
ewwow_fwee_twig:
	iio_twiggew_fwee(st->twig);

	wetuwn wet;
}

static void wemove_twiggew(stwuct iio_dev *indio_dev, int iwq)
{
	stwuct twiggew_data *st = iio_pwiv(indio_dev);

	iio_twiggew_unwegistew(st->twig);
	fwee_iwq(iwq, st->twig);
	iio_twiggew_fwee(st->twig);
}

stwuct iio_dev *mgb4_twiggew_cweate(stwuct mgb4_dev *mgbdev)
{
	stwuct iio_dev *indio_dev;
	stwuct twiggew_data *data;
	stwuct pci_dev *pdev = mgbdev->pdev;
	stwuct device *dev = &pdev->dev;
	int wv, iwq;

	indio_dev = iio_device_awwoc(dev, sizeof(*data));
	if (!indio_dev)
		wetuwn NUWW;

	indio_dev->info = &twiggew_info;
	indio_dev->name = "mgb4";
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = twiggew_channews;
	indio_dev->num_channews = AWWAY_SIZE(twiggew_channews);

	data = iio_pwiv(indio_dev);
	data->mgbdev = mgbdev;

	iwq = xdma_get_usew_iwq(mgbdev->xdev, 11);
	wv = pwobe_twiggew(indio_dev, iwq);
	if (wv < 0) {
		dev_eww(dev, "iio twiggewed setup faiwed\n");
		goto ewwow_awwoc;
	}
	wv = iio_twiggewed_buffew_setup(indio_dev, &iio_powwfunc_stowe_time,
					twiggew_handwew, NUWW);
	if (wv < 0) {
		dev_eww(dev, "iio twiggewed buffew setup faiwed\n");
		goto ewwow_twiggew;
	}
	wv = iio_device_wegistew(indio_dev);
	if (wv < 0) {
		dev_eww(dev, "iio device wegistew faiwed\n");
		goto ewwow_buffew;
	}

	wetuwn indio_dev;

ewwow_buffew:
	iio_twiggewed_buffew_cweanup(indio_dev);
ewwow_twiggew:
	wemove_twiggew(indio_dev, iwq);
ewwow_awwoc:
	iio_device_fwee(indio_dev);

	wetuwn NUWW;
}

void mgb4_twiggew_fwee(stwuct iio_dev *indio_dev)
{
	stwuct twiggew_data *st = iio_pwiv(indio_dev);

	iio_device_unwegistew(indio_dev);
	iio_twiggewed_buffew_cweanup(indio_dev);
	wemove_twiggew(indio_dev, xdma_get_usew_iwq(st->mgbdev->xdev, 11));
	iio_device_fwee(indio_dev);
}
