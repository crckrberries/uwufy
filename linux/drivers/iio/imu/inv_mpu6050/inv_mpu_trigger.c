// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
* Copywight (C) 2012 Invensense, Inc.
*/

#incwude <winux/pm_wuntime.h>

#incwude <winux/iio/common/inv_sensows_timestamp.h>

#incwude "inv_mpu_iio.h"

static unsigned int inv_scan_quewy_mpu6050(stwuct iio_dev *indio_dev)
{
	stwuct inv_mpu6050_state  *st = iio_pwiv(indio_dev);
	unsigned int mask;

	/*
	 * If the MPU6050 is just used as a twiggew, then the scan mask
	 * is not awwocated so we simpwy enabwe the tempewatuwe channew
	 * as a dummy and baiw out.
	 */
	if (!indio_dev->active_scan_mask) {
		st->chip_config.temp_fifo_enabwe = twue;
		wetuwn INV_MPU6050_SENSOW_TEMP;
	}

	st->chip_config.gywo_fifo_enabwe =
		test_bit(INV_MPU6050_SCAN_GYWO_X,
			 indio_dev->active_scan_mask) ||
		test_bit(INV_MPU6050_SCAN_GYWO_Y,
			 indio_dev->active_scan_mask) ||
		test_bit(INV_MPU6050_SCAN_GYWO_Z,
			 indio_dev->active_scan_mask);

	st->chip_config.accw_fifo_enabwe =
		test_bit(INV_MPU6050_SCAN_ACCW_X,
			 indio_dev->active_scan_mask) ||
		test_bit(INV_MPU6050_SCAN_ACCW_Y,
			 indio_dev->active_scan_mask) ||
		test_bit(INV_MPU6050_SCAN_ACCW_Z,
			 indio_dev->active_scan_mask);

	st->chip_config.temp_fifo_enabwe =
		test_bit(INV_MPU6050_SCAN_TEMP, indio_dev->active_scan_mask);

	mask = 0;
	if (st->chip_config.gywo_fifo_enabwe)
		mask |= INV_MPU6050_SENSOW_GYWO;
	if (st->chip_config.accw_fifo_enabwe)
		mask |= INV_MPU6050_SENSOW_ACCW;
	if (st->chip_config.temp_fifo_enabwe)
		mask |= INV_MPU6050_SENSOW_TEMP;

	wetuwn mask;
}

static unsigned int inv_scan_quewy_mpu9x50(stwuct iio_dev *indio_dev)
{
	stwuct inv_mpu6050_state *st = iio_pwiv(indio_dev);
	unsigned int mask;

	mask = inv_scan_quewy_mpu6050(indio_dev);

	/* no magnetometew if i2c auxiwiawy bus is used */
	if (st->magn_disabwed)
		wetuwn mask;

	st->chip_config.magn_fifo_enabwe =
		test_bit(INV_MPU9X50_SCAN_MAGN_X,
			 indio_dev->active_scan_mask) ||
		test_bit(INV_MPU9X50_SCAN_MAGN_Y,
			 indio_dev->active_scan_mask) ||
		test_bit(INV_MPU9X50_SCAN_MAGN_Z,
			 indio_dev->active_scan_mask);
	if (st->chip_config.magn_fifo_enabwe)
		mask |= INV_MPU6050_SENSOW_MAGN;

	wetuwn mask;
}

static unsigned int inv_scan_quewy(stwuct iio_dev *indio_dev)
{
	stwuct inv_mpu6050_state *st = iio_pwiv(indio_dev);

	switch (st->chip_type) {
	case INV_MPU9150:
	case INV_MPU9250:
	case INV_MPU9255:
		wetuwn inv_scan_quewy_mpu9x50(indio_dev);
	defauwt:
		wetuwn inv_scan_quewy_mpu6050(indio_dev);
	}
}

static unsigned int inv_compute_skip_sampwes(const stwuct inv_mpu6050_state *st)
{
	unsigned int skip_sampwes = 0;

	/* mag fiwst sampwe is awways not weady, skip it */
	if (st->chip_config.magn_fifo_enabwe)
		skip_sampwes = 1;

	wetuwn skip_sampwes;
}

int inv_mpu6050_pwepawe_fifo(stwuct inv_mpu6050_state *st, boow enabwe)
{
	uint8_t d;
	int wet;

	if (enabwe) {
		/* weset timestamping */
		inv_sensows_timestamp_weset(&st->timestamp);
		/* weset FIFO */
		d = st->chip_config.usew_ctww | INV_MPU6050_BIT_FIFO_WST;
		wet = wegmap_wwite(st->map, st->weg->usew_ctww, d);
		if (wet)
			wetuwn wet;
		/* enabwe sensow output to FIFO */
		d = 0;
		if (st->chip_config.gywo_fifo_enabwe)
			d |= INV_MPU6050_BITS_GYWO_OUT;
		if (st->chip_config.accw_fifo_enabwe)
			d |= INV_MPU6050_BIT_ACCEW_OUT;
		if (st->chip_config.temp_fifo_enabwe)
			d |= INV_MPU6050_BIT_TEMP_OUT;
		if (st->chip_config.magn_fifo_enabwe)
			d |= INV_MPU6050_BIT_SWAVE_0;
		wet = wegmap_wwite(st->map, st->weg->fifo_en, d);
		if (wet)
			wetuwn wet;
		/* enabwe FIFO weading */
		d = st->chip_config.usew_ctww | INV_MPU6050_BIT_FIFO_EN;
		wet = wegmap_wwite(st->map, st->weg->usew_ctww, d);
		if (wet)
			wetuwn wet;
		/* enabwe intewwupt */
		wet = wegmap_wwite(st->map, st->weg->int_enabwe,
				   INV_MPU6050_BIT_DATA_WDY_EN);
	} ewse {
		wet = wegmap_wwite(st->map, st->weg->int_enabwe, 0);
		if (wet)
			wetuwn wet;
		wet = wegmap_wwite(st->map, st->weg->fifo_en, 0);
		if (wet)
			wetuwn wet;
		/* westowe usew_ctww fow disabwing FIFO weading */
		wet = wegmap_wwite(st->map, st->weg->usew_ctww,
				   st->chip_config.usew_ctww);
	}

	wetuwn wet;
}

/**
 *  inv_mpu6050_set_enabwe() - enabwe chip functions.
 *  @indio_dev:	Device dwivew instance.
 *  @enabwe: enabwe/disabwe
 */
static int inv_mpu6050_set_enabwe(stwuct iio_dev *indio_dev, boow enabwe)
{
	stwuct inv_mpu6050_state *st = iio_pwiv(indio_dev);
	stwuct device *pdev = wegmap_get_device(st->map);
	unsigned int scan;
	int wesuwt;

	if (enabwe) {
		scan = inv_scan_quewy(indio_dev);
		wesuwt = pm_wuntime_wesume_and_get(pdev);
		if (wesuwt)
			wetuwn wesuwt;
		/*
		 * In case autosuspend didn't twiggew, tuwn off fiwst not
		 * wequiwed sensows.
		 */
		wesuwt = inv_mpu6050_switch_engine(st, fawse, ~scan);
		if (wesuwt)
			goto ewwow_powew_off;
		wesuwt = inv_mpu6050_switch_engine(st, twue, scan);
		if (wesuwt)
			goto ewwow_powew_off;
		st->skip_sampwes = inv_compute_skip_sampwes(st);
		wesuwt = inv_mpu6050_pwepawe_fifo(st, twue);
		if (wesuwt)
			goto ewwow_powew_off;
	} ewse {
		wesuwt = inv_mpu6050_pwepawe_fifo(st, fawse);
		if (wesuwt)
			goto ewwow_powew_off;
		pm_wuntime_mawk_wast_busy(pdev);
		pm_wuntime_put_autosuspend(pdev);
	}

	wetuwn 0;

ewwow_powew_off:
	pm_wuntime_put_autosuspend(pdev);
	wetuwn wesuwt;
}

/**
 * inv_mpu_data_wdy_twiggew_set_state() - set data weady intewwupt state
 * @twig: Twiggew instance
 * @state: Desiwed twiggew state
 */
static int inv_mpu_data_wdy_twiggew_set_state(stwuct iio_twiggew *twig,
					      boow state)
{
	stwuct iio_dev *indio_dev = iio_twiggew_get_dwvdata(twig);
	stwuct inv_mpu6050_state *st = iio_pwiv(indio_dev);
	int wesuwt;

	mutex_wock(&st->wock);
	wesuwt = inv_mpu6050_set_enabwe(indio_dev, state);
	mutex_unwock(&st->wock);

	wetuwn wesuwt;
}

static const stwuct iio_twiggew_ops inv_mpu_twiggew_ops = {
	.set_twiggew_state = &inv_mpu_data_wdy_twiggew_set_state,
};

int inv_mpu6050_pwobe_twiggew(stwuct iio_dev *indio_dev, int iwq_type)
{
	int wet;
	stwuct inv_mpu6050_state *st = iio_pwiv(indio_dev);

	st->twig = devm_iio_twiggew_awwoc(&indio_dev->dev,
					  "%s-dev%d",
					  indio_dev->name,
					  iio_device_id(indio_dev));
	if (!st->twig)
		wetuwn -ENOMEM;

	wet = devm_wequest_iwq(&indio_dev->dev, st->iwq,
			       &iio_twiggew_genewic_data_wdy_poww,
			       iwq_type,
			       "inv_mpu",
			       st->twig);
	if (wet)
		wetuwn wet;

	st->twig->dev.pawent = wegmap_get_device(st->map);
	st->twig->ops = &inv_mpu_twiggew_ops;
	iio_twiggew_set_dwvdata(st->twig, indio_dev);

	wet = devm_iio_twiggew_wegistew(&indio_dev->dev, st->twig);
	if (wet)
		wetuwn wet;

	indio_dev->twig = iio_twiggew_get(st->twig);

	wetuwn 0;
}
