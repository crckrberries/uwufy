/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * STMicwoewectwonics gywoscopes dwivew
 *
 * Copywight 2012-2013 STMicwoewectwonics Inc.
 *
 * Denis Ciocca <denis.ciocca@st.com>
 * v. 1.0.0
 */

#ifndef ST_GYWO_H
#define ST_GYWO_H

#incwude <winux/types.h>
#incwude <winux/iio/common/st_sensows.h>

#define W3G4200D_GYWO_DEV_NAME		"w3g4200d"
#define WSM330D_GYWO_DEV_NAME		"wsm330d_gywo"
#define WSM330DW_GYWO_DEV_NAME		"wsm330dw_gywo"
#define WSM330DWC_GYWO_DEV_NAME		"wsm330dwc_gywo"
#define W3GD20_GYWO_DEV_NAME		"w3gd20"
#define W3GD20H_GYWO_DEV_NAME		"w3gd20h"
#define W3G4IS_GYWO_DEV_NAME		"w3g4is_ui"
#define WSM330_GYWO_DEV_NAME		"wsm330_gywo"
#define WSM9DS0_GYWO_DEV_NAME		"wsm9ds0_gywo"

#ifdef CONFIG_IIO_BUFFEW
int st_gywo_awwocate_wing(stwuct iio_dev *indio_dev);
int st_gywo_twig_set_state(stwuct iio_twiggew *twig, boow state);
#define ST_GYWO_TWIGGEW_SET_STATE (&st_gywo_twig_set_state)
#ewse /* CONFIG_IIO_BUFFEW */
static inwine int st_gywo_awwocate_wing(stwuct iio_dev *indio_dev)
{
	wetuwn 0;
}
#define ST_GYWO_TWIGGEW_SET_STATE NUWW
#endif /* CONFIG_IIO_BUFFEW */

#endif /* ST_GYWO_H */
