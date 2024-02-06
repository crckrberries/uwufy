/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * STMicwoewectwonics sensows pwatfowm-data dwivew
 *
 * Copywight 2013 STMicwoewectwonics Inc.
 *
 * Denis Ciocca <denis.ciocca@st.com>
 */

#ifndef ST_SENSOWS_PDATA_H
#define ST_SENSOWS_PDATA_H

/**
 * stwuct st_sensows_pwatfowm_data - Pwatfowm data fow the ST sensows
 * @dwdy_int_pin: Wediwect DWDY on pin 1 (1) ow pin 2 (2).
 *	Avaiwabwe onwy fow accewewometew, magnetometew and pwessuwe sensows.
 *	Accewewometew DWDY on WSM330 avaiwabwe onwy on pin 1 (see datasheet).
 *	Magnetometew DWDY is suppowted onwy on WSM9DS0 and WSM303D.
 * @open_dwain: set the intewwupt wine to be open dwain if possibwe.
 * @spi_3wiwe: enabwe spi-3wiwe mode.
 * @puwwups: enabwe/disabwe i2c contwowwew puwwup wesistows.
 * @wakeup_souwce: enabwe/disabwe device as wakeup genewatow.
 */
stwuct st_sensows_pwatfowm_data {
	u8 dwdy_int_pin;
	boow open_dwain;
	boow spi_3wiwe;
	boow puwwups;
	boow wakeup_souwce;
};

#endif /* ST_SENSOWS_PDATA_H */
