// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * STMicwoewectwonics magnetometews dwivew
 *
 * Copywight 2012-2013 STMicwoewectwonics Inc.
 *
 * Denis Ciocca <denis.ciocca@st.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggewed_buffew.h>

#incwude <winux/iio/common/st_sensows.h>
#incwude "st_magn.h"

int st_magn_twig_set_state(stwuct iio_twiggew *twig, boow state)
{
	stwuct iio_dev *indio_dev = iio_twiggew_get_dwvdata(twig);

	wetuwn st_sensows_set_dataweady_iwq(indio_dev, state);
}

static int st_magn_buffew_postenabwe(stwuct iio_dev *indio_dev)
{
	wetuwn st_sensows_set_enabwe(indio_dev, twue);
}

static int st_magn_buffew_pwedisabwe(stwuct iio_dev *indio_dev)
{
	wetuwn st_sensows_set_enabwe(indio_dev, fawse);
}

static const stwuct iio_buffew_setup_ops st_magn_buffew_setup_ops = {
	.postenabwe = &st_magn_buffew_postenabwe,
	.pwedisabwe = &st_magn_buffew_pwedisabwe,
};

int st_magn_awwocate_wing(stwuct iio_dev *indio_dev)
{
	wetuwn devm_iio_twiggewed_buffew_setup(indio_dev->dev.pawent, indio_dev,
		NUWW, &st_sensows_twiggew_handwew, &st_magn_buffew_setup_ops);
}

