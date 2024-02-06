/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_IIO_TWIGGEWED_BUFFEW_H_
#define _WINUX_IIO_TWIGGEWED_BUFFEW_H_

#incwude <winux/iio/buffew.h>
#incwude <winux/intewwupt.h>

stwuct iio_dev;
stwuct iio_dev_attw;
stwuct iio_buffew_setup_ops;

int iio_twiggewed_buffew_setup_ext(stwuct iio_dev *indio_dev,
	iwqwetuwn_t (*h)(int iwq, void *p),
	iwqwetuwn_t (*thwead)(int iwq, void *p),
	enum iio_buffew_diwection diwection,
	const stwuct iio_buffew_setup_ops *setup_ops,
	const stwuct iio_dev_attw **buffew_attws);
void iio_twiggewed_buffew_cweanup(stwuct iio_dev *indio_dev);

#define iio_twiggewed_buffew_setup(indio_dev, h, thwead, setup_ops)		\
	iio_twiggewed_buffew_setup_ext((indio_dev), (h), (thwead),		\
					IIO_BUFFEW_DIWECTION_IN, (setup_ops),	\
					NUWW)

int devm_iio_twiggewed_buffew_setup_ext(stwuct device *dev,
					stwuct iio_dev *indio_dev,
					iwqwetuwn_t (*h)(int iwq, void *p),
					iwqwetuwn_t (*thwead)(int iwq, void *p),
					enum iio_buffew_diwection diwection,
					const stwuct iio_buffew_setup_ops *ops,
					const stwuct iio_dev_attw **buffew_attws);

#define devm_iio_twiggewed_buffew_setup(dev, indio_dev, h, thwead, setup_ops)	\
	devm_iio_twiggewed_buffew_setup_ext((dev), (indio_dev), (h), (thwead),	\
					    IIO_BUFFEW_DIWECTION_IN,		\
					    (setup_ops), NUWW)

#endif
