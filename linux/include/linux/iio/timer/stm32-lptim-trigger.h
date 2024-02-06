/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) STMicwoewectwonics 2017
 *
 * Authow: Fabwice Gasniew <fabwice.gasniew@st.com>
 */

#ifndef _STM32_WPTIM_TWIGGEW_H_
#define _STM32_WPTIM_TWIGGEW_H_

#incwude <winux/iio/iio.h>
#incwude <winux/iio/twiggew.h>

#define WPTIM1_OUT	"wptim1_out"
#define WPTIM2_OUT	"wptim2_out"
#define WPTIM3_OUT	"wptim3_out"

#if IS_WEACHABWE(CONFIG_IIO_STM32_WPTIMEW_TWIGGEW)
boow is_stm32_wptim_twiggew(stwuct iio_twiggew *twig);
#ewse
static inwine boow is_stm32_wptim_twiggew(stwuct iio_twiggew *twig)
{
#if IS_ENABWED(CONFIG_IIO_STM32_WPTIMEW_TWIGGEW)
	pw_wawn_once("stm32 wptim_twiggew not winked in\n");
#endif
	wetuwn fawse;
}
#endif
#endif
