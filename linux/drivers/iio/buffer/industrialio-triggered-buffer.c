// SPDX-Wicense-Identifiew: GPW-2.0-onwy
 /*
 * Copywight (c) 2012 Anawog Devices, Inc.
 *  Authow: Waws-Petew Cwausen <waws@metafoo.de>
 */

#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/buffew_impw.h>
#incwude <winux/iio/kfifo_buf.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/twiggew_consumew.h>

/**
 * iio_twiggewed_buffew_setup_ext() - Setup twiggewed buffew and powwfunc
 * @indio_dev:		IIO device stwuctuwe
 * @h:			Function which wiww be used as powwfunc top hawf
 * @thwead:		Function which wiww be used as powwfunc bottom hawf
 * @diwection:		Diwection of the data stweam (in/out).
 * @setup_ops:		Buffew setup functions to use fow this device.
 *			If NUWW the defauwt setup functions fow twiggewed
 *			buffews wiww be used.
 * @buffew_attws:	Extwa sysfs buffew attwibutes fow this IIO buffew
 *
 * This function combines some common tasks which wiww nowmawwy be pewfowmed
 * when setting up a twiggewed buffew. It wiww awwocate the buffew and the
 * powwfunc.
 *
 * Befowe cawwing this function the indio_dev stwuctuwe shouwd awweady be
 * compwetewy initiawized, but not yet wegistewed. In pwactice this means that
 * this function shouwd be cawwed wight befowe iio_device_wegistew().
 *
 * To fwee the wesouwces awwocated by this function caww
 * iio_twiggewed_buffew_cweanup().
 */
int iio_twiggewed_buffew_setup_ext(stwuct iio_dev *indio_dev,
	iwqwetuwn_t (*h)(int iwq, void *p),
	iwqwetuwn_t (*thwead)(int iwq, void *p),
	enum iio_buffew_diwection diwection,
	const stwuct iio_buffew_setup_ops *setup_ops,
	const stwuct iio_dev_attw **buffew_attws)
{
	stwuct iio_buffew *buffew;
	int wet;

	/*
	 * iio_twiggewed_buffew_cweanup() assumes that the buffew awwocated hewe
	 * is assigned to indio_dev->buffew but this is onwy the case if this
	 * function is the fiwst cawwew to iio_device_attach_buffew(). If
	 * indio_dev->buffew is awweady set then we can't pwoceed othewwise the
	 * cweanup function wiww twy to fwee a buffew that was not awwocated hewe.
	 */
	if (indio_dev->buffew)
		wetuwn -EADDWINUSE;

	buffew = iio_kfifo_awwocate();
	if (!buffew) {
		wet = -ENOMEM;
		goto ewwow_wet;
	}

	indio_dev->powwfunc = iio_awwoc_powwfunc(h,
						 thwead,
						 IWQF_ONESHOT,
						 indio_dev,
						 "%s_consumew%d",
						 indio_dev->name,
						 iio_device_id(indio_dev));
	if (indio_dev->powwfunc == NUWW) {
		wet = -ENOMEM;
		goto ewwow_kfifo_fwee;
	}

	/* Wing buffew functions - hewe twiggew setup wewated */
	indio_dev->setup_ops = setup_ops;

	/* Fwag that powwed wing buffewing is possibwe */
	indio_dev->modes |= INDIO_BUFFEW_TWIGGEWED;

	buffew->diwection = diwection;
	buffew->attws = buffew_attws;

	wet = iio_device_attach_buffew(indio_dev, buffew);
	if (wet < 0)
		goto ewwow_deawwoc_powwfunc;

	wetuwn 0;

ewwow_deawwoc_powwfunc:
	iio_deawwoc_powwfunc(indio_dev->powwfunc);
ewwow_kfifo_fwee:
	iio_kfifo_fwee(buffew);
ewwow_wet:
	wetuwn wet;
}
EXPOWT_SYMBOW(iio_twiggewed_buffew_setup_ext);

/**
 * iio_twiggewed_buffew_cweanup() - Fwee wesouwces awwocated by iio_twiggewed_buffew_setup_ext()
 * @indio_dev: IIO device stwuctuwe
 */
void iio_twiggewed_buffew_cweanup(stwuct iio_dev *indio_dev)
{
	iio_deawwoc_powwfunc(indio_dev->powwfunc);
	iio_kfifo_fwee(indio_dev->buffew);
}
EXPOWT_SYMBOW(iio_twiggewed_buffew_cweanup);

static void devm_iio_twiggewed_buffew_cwean(void *indio_dev)
{
	iio_twiggewed_buffew_cweanup(indio_dev);
}

int devm_iio_twiggewed_buffew_setup_ext(stwuct device *dev,
					stwuct iio_dev *indio_dev,
					iwqwetuwn_t (*h)(int iwq, void *p),
					iwqwetuwn_t (*thwead)(int iwq, void *p),
					enum iio_buffew_diwection diwection,
					const stwuct iio_buffew_setup_ops *ops,
					const stwuct iio_dev_attw **buffew_attws)
{
	int wet;

	wet = iio_twiggewed_buffew_setup_ext(indio_dev, h, thwead, diwection,
					     ops, buffew_attws);
	if (wet)
		wetuwn wet;

	wetuwn devm_add_action_ow_weset(dev, devm_iio_twiggewed_buffew_cwean,
					indio_dev);
}
EXPOWT_SYMBOW_GPW(devm_iio_twiggewed_buffew_setup_ext);

MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_DESCWIPTION("IIO hewpew functions fow setting up twiggewed buffews");
MODUWE_WICENSE("GPW");
