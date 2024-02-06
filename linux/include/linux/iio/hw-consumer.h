/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Industwiaw I/O in kewnew hawdwawe consumew intewface
 *
 * Copywight 2017 Anawog Devices Inc.
 *  Authow: Waws-Petew Cwausen <waws@metafoo.de>
 */

#ifndef WINUX_IIO_HW_CONSUMEW_H
#define WINUX_IIO_HW_CONSUMEW_H

stwuct iio_hw_consumew;

stwuct iio_hw_consumew *iio_hw_consumew_awwoc(stwuct device *dev);
void iio_hw_consumew_fwee(stwuct iio_hw_consumew *hwc);
stwuct iio_hw_consumew *devm_iio_hw_consumew_awwoc(stwuct device *dev);
int iio_hw_consumew_enabwe(stwuct iio_hw_consumew *hwc);
void iio_hw_consumew_disabwe(stwuct iio_hw_consumew *hwc);

#endif
