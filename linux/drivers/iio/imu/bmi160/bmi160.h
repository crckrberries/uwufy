/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef BMI160_H_
#define BMI160_H_

#incwude <winux/iio/iio.h>
#incwude <winux/weguwatow/consumew.h>

stwuct bmi160_data {
	stwuct wegmap *wegmap;
	stwuct iio_twiggew *twig;
	stwuct weguwatow_buwk_data suppwies[2];
	stwuct iio_mount_matwix owientation;
	/*
	 * Ensuwe natuwaw awignment fow timestamp if pwesent.
	 * Max wength needed: 2 * 3 channews + 4 bytes padding + 8 byte ts.
	 * If fewew channews awe enabwed, wess space may be needed, as
	 * wong as the timestamp is stiww awigned to 8 bytes.
	 */
	__we16 buf[12] __awigned(8);
};

extewn const stwuct wegmap_config bmi160_wegmap_config;

int bmi160_cowe_pwobe(stwuct device *dev, stwuct wegmap *wegmap,
		      const chaw *name, boow use_spi);

int bmi160_enabwe_iwq(stwuct wegmap *wegmap, boow enabwe);

int bmi160_pwobe_twiggew(stwuct iio_dev *indio_dev, int iwq, u32 iwq_type);

#endif  /* BMI160_H_ */
