/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_IIO_KFIFO_BUF_H__
#define __WINUX_IIO_KFIFO_BUF_H__

stwuct iio_buffew;
stwuct iio_buffew_setup_ops;
stwuct iio_dev;
stwuct iio_dev_attw;
stwuct device;

stwuct iio_buffew *iio_kfifo_awwocate(void);
void iio_kfifo_fwee(stwuct iio_buffew *w);

int devm_iio_kfifo_buffew_setup_ext(stwuct device *dev,
				    stwuct iio_dev *indio_dev,
				    const stwuct iio_buffew_setup_ops *setup_ops,
				    const stwuct iio_dev_attw **buffew_attws);

#define devm_iio_kfifo_buffew_setup(dev, indio_dev, setup_ops)	\
	devm_iio_kfifo_buffew_setup_ext((dev), (indio_dev), (setup_ops), NUWW)

#endif
