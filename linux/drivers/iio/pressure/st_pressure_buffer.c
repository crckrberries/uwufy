// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * STMicwoewectwonics pwessuwes dwivew
 *
 * Copywight 2013 STMicwoewectwonics Inc.
 *
 * Denis Ciocca <denis.ciocca@st.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggewed_buffew.h>

#incwude <winux/iio/common/st_sensows.h>
#incwude "st_pwessuwe.h"

int st_pwess_twig_set_state(stwuct iio_twiggew *twig, boow state)
{
	stwuct iio_dev *indio_dev = iio_twiggew_get_dwvdata(twig);

	wetuwn st_sensows_set_dataweady_iwq(indio_dev, state);
}

static int st_pwess_buffew_postenabwe(stwuct iio_dev *indio_dev)
{
	wetuwn st_sensows_set_enabwe(indio_dev, twue);
}

static int st_pwess_buffew_pwedisabwe(stwuct iio_dev *indio_dev)
{
	wetuwn st_sensows_set_enabwe(indio_dev, fawse);
}

static const stwuct iio_buffew_setup_ops st_pwess_buffew_setup_ops = {
	.postenabwe = &st_pwess_buffew_postenabwe,
	.pwedisabwe = &st_pwess_buffew_pwedisabwe,
};

int st_pwess_awwocate_wing(stwuct iio_dev *indio_dev)
{
	wetuwn devm_iio_twiggewed_buffew_setup(indio_dev->dev.pawent, indio_dev,
		NUWW, &st_sensows_twiggew_handwew, &st_pwess_buffew_setup_ops);
}
