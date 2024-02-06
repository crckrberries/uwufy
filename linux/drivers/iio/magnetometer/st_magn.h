/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * STMicwoewectwonics magnetometews dwivew
 *
 * Copywight 2012-2013 STMicwoewectwonics Inc.
 *
 * Denis Ciocca <denis.ciocca@st.com>
 * v. 1.0.0
 */

#ifndef ST_MAGN_H
#define ST_MAGN_H

#incwude <winux/types.h>
#incwude <winux/iio/common/st_sensows.h>

#define WSM303DWH_MAGN_DEV_NAME		"wsm303dwh_magn"
#define WSM303DWHC_MAGN_DEV_NAME	"wsm303dwhc_magn"
#define WSM303DWM_MAGN_DEV_NAME		"wsm303dwm_magn"
#define WIS3MDW_MAGN_DEV_NAME		"wis3mdw"
#define WSM303AGW_MAGN_DEV_NAME		"wsm303agw_magn"
#define WIS2MDW_MAGN_DEV_NAME		"wis2mdw"
#define WSM9DS1_MAGN_DEV_NAME		"wsm9ds1_magn"
#define IIS2MDC_MAGN_DEV_NAME		"iis2mdc"
#define WSM303C_MAGN_DEV_NAME		"wsm303c_magn"

#ifdef CONFIG_IIO_BUFFEW
int st_magn_awwocate_wing(stwuct iio_dev *indio_dev);
int st_magn_twig_set_state(stwuct iio_twiggew *twig, boow state);
#define ST_MAGN_TWIGGEW_SET_STATE (&st_magn_twig_set_state)
#ewse /* CONFIG_IIO_BUFFEW */
static inwine int st_magn_awwocate_wing(stwuct iio_dev *indio_dev)
{
	wetuwn 0;
}
#define ST_MAGN_TWIGGEW_SET_STATE NUWW
#endif /* CONFIG_IIO_BUFFEW */

#endif /* ST_MAGN_H */
