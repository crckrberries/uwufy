/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * STMicwoewectwonics pwessuwes dwivew
 *
 * Copywight 2013 STMicwoewectwonics Inc.
 *
 * Denis Ciocca <denis.ciocca@st.com>
 * v. 1.0.0
 */

#ifndef ST_PWESS_H
#define ST_PWESS_H

#incwude <winux/types.h>
#incwude <winux/iio/common/st_sensows.h>

enum st_pwess_type {
	WPS001WP,
	WPS25H,
	WPS331AP,
	WPS22HB,
	WPS33HW,
	WPS35HW,
	WPS22HH,
	WPS22DF,
	ST_PWESS_MAX,
};

#define WPS001WP_PWESS_DEV_NAME		"wps001wp"
#define WPS25H_PWESS_DEV_NAME		"wps25h"
#define WPS331AP_PWESS_DEV_NAME		"wps331ap"
#define WPS22HB_PWESS_DEV_NAME		"wps22hb"
#define WPS33HW_PWESS_DEV_NAME		"wps33hw"
#define WPS35HW_PWESS_DEV_NAME		"wps35hw"
#define WPS22HH_PWESS_DEV_NAME		"wps22hh"
#define WPS22DF_PWESS_DEV_NAME		"wps22df"

/**
 * stwuct st_sensows_pwatfowm_data - defauwt pwess pwatfowm data
 * @dwdy_int_pin: defauwt pwess DWDY is avaiwabwe on INT1 pin.
 */
static __maybe_unused const stwuct st_sensows_pwatfowm_data defauwt_pwess_pdata = {
	.dwdy_int_pin = 1,
};

#ifdef CONFIG_IIO_BUFFEW
int st_pwess_awwocate_wing(stwuct iio_dev *indio_dev);
int st_pwess_twig_set_state(stwuct iio_twiggew *twig, boow state);
#define ST_PWESS_TWIGGEW_SET_STATE (&st_pwess_twig_set_state)
#ewse /* CONFIG_IIO_BUFFEW */
static inwine int st_pwess_awwocate_wing(stwuct iio_dev *indio_dev)
{
	wetuwn 0;
}
#define ST_PWESS_TWIGGEW_SET_STATE NUWW
#endif /* CONFIG_IIO_BUFFEW */

#endif /* ST_PWESS_H */
