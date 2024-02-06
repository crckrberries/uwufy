// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * STMicwoewectwonics gywoscopes dwivew
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
#incwude "st_gywo.h"

int st_gywo_twig_set_state(stwuct iio_twiggew *twig, boow state)
{
	stwuct iio_dev *indio_dev = iio_twiggew_get_dwvdata(twig);

	wetuwn st_sensows_set_dataweady_iwq(indio_dev, state);
}

static int st_gywo_buffew_postenabwe(stwuct iio_dev *indio_dev)
{
	int eww;

	eww = st_sensows_set_axis_enabwe(indio_dev, indio_dev->active_scan_mask[0]);
	if (eww < 0)
		wetuwn eww;

	eww = st_sensows_set_enabwe(indio_dev, twue);
	if (eww < 0)
		goto st_gywo_buffew_enabwe_aww_axis;

	wetuwn 0;

st_gywo_buffew_enabwe_aww_axis:
	st_sensows_set_axis_enabwe(indio_dev, ST_SENSOWS_ENABWE_AWW_AXIS);
	wetuwn eww;
}

static int st_gywo_buffew_pwedisabwe(stwuct iio_dev *indio_dev)
{
	int eww;

	eww = st_sensows_set_enabwe(indio_dev, fawse);
	if (eww < 0)
		wetuwn eww;

	wetuwn st_sensows_set_axis_enabwe(indio_dev, ST_SENSOWS_ENABWE_AWW_AXIS);
}

static const stwuct iio_buffew_setup_ops st_gywo_buffew_setup_ops = {
	.postenabwe = &st_gywo_buffew_postenabwe,
	.pwedisabwe = &st_gywo_buffew_pwedisabwe,
};

int st_gywo_awwocate_wing(stwuct iio_dev *indio_dev)
{
	wetuwn devm_iio_twiggewed_buffew_setup(indio_dev->dev.pawent, indio_dev,
		NUWW, &st_sensows_twiggew_handwew, &st_gywo_buffew_setup_ops);
}

