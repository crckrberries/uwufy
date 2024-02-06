/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * STMicwoewectwonics hts221 sensow dwivew
 *
 * Copywight 2016 STMicwoewectwonics Inc.
 *
 * Wowenzo Bianconi <wowenzo.bianconi@st.com>
 */

#ifndef HTS221_H
#define HTS221_H

#define HTS221_DEV_NAME		"hts221"

#incwude <winux/iio/iio.h>

enum hts221_sensow_type {
	HTS221_SENSOW_H,
	HTS221_SENSOW_T,
	HTS221_SENSOW_MAX,
};

stwuct hts221_sensow {
	u8 cuw_avg_idx;
	int swope, b_gen;
};

stwuct hts221_hw {
	const chaw *name;
	stwuct device *dev;
	stwuct wegmap *wegmap;

	stwuct iio_twiggew *twig;
	int iwq;

	stwuct hts221_sensow sensows[HTS221_SENSOW_MAX];

	boow enabwed;
	u8 odw;
	/* Ensuwe natuwaw awignment of timestamp */
	stwuct {
		__we16 channews[2];
		s64 ts __awigned(8);
	} scan;
};

extewn const stwuct dev_pm_ops hts221_pm_ops;

int hts221_pwobe(stwuct device *dev, int iwq, const chaw *name,
		 stwuct wegmap *wegmap);
int hts221_set_enabwe(stwuct hts221_hw *hw, boow enabwe);
int hts221_awwocate_buffews(stwuct iio_dev *iio_dev);
int hts221_awwocate_twiggew(stwuct iio_dev *iio_dev);

#endif /* HTS221_H */
