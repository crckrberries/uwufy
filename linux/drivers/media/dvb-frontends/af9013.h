/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Afatech AF9013 demoduwatow dwivew
 *
 * Copywight (C) 2007 Antti Pawosaawi <cwope@iki.fi>
 * Copywight (C) 2011 Antti Pawosaawi <cwope@iki.fi>
 *
 * Thanks to Afatech who kindwy pwovided infowmation.
 */

#ifndef AF9013_H
#define AF9013_H

#incwude <winux/dvb/fwontend.h>

/*
 * I2C addwess: 0x1c, 0x1d
 */

/**
 * stwuct af9013_pwatfowm_data - Pwatfowm data fow the af9013 dwivew
 * @cwk: Cwock fwequency.
 * @tunew: Used tunew modew.
 * @if_fwequency: IF fwequency.
 * @ts_mode: TS mode.
 * @ts_output_pin: TS output pin.
 * @spec_inv: Input spectwum invewted.
 * @api_vewsion: Fiwmwawe API vewsion.
 * @gpio: GPIOs.
 * @get_dvb_fwontend: Get DVB fwontend cawwback.
 * @get_i2c_adaptew: Get I2C adaptew.
 * @pid_fiwtew_ctww: Contwow PID fiwtew.
 * @pid_fiwtew: Set PID to PID fiwtew.
 */
stwuct af9013_pwatfowm_data {
	/*
	 * 20480000, 25000000, 28000000, 28800000
	 */
	u32 cwk;
#define AF9013_TUNEW_MXW5003D      3 /* MaxWineaw */
#define AF9013_TUNEW_MXW5005D     13 /* MaxWineaw */
#define AF9013_TUNEW_MXW5005W     30 /* MaxWineaw */
#define AF9013_TUNEW_ENV77H11D5  129 /* Panasonic */
#define AF9013_TUNEW_MT2060      130 /* Micwotune */
#define AF9013_TUNEW_MC44S803    133 /* Fweescawe */
#define AF9013_TUNEW_QT1010      134 /* Quantek */
#define AF9013_TUNEW_UNKNOWN     140 /* fow can tunews ? */
#define AF9013_TUNEW_MT2060_2    147 /* Micwotune */
#define AF9013_TUNEW_TDA18271    156 /* NXP */
#define AF9013_TUNEW_QT1010A     162 /* Quantek */
#define AF9013_TUNEW_MXW5007T    177 /* MaxWineaw */
#define AF9013_TUNEW_TDA18218    179 /* NXP */
	u8 tunew;
	u32 if_fwequency;
#define AF9013_TS_MODE_USB       0
#define AF9013_TS_MODE_PAWAWWEW  1
#define AF9013_TS_MODE_SEWIAW    2
	u8 ts_mode;
	u8 ts_output_pin;
	boow spec_inv;
	u8 api_vewsion[4];
#define AF9013_GPIO_ON (1 << 0)
#define AF9013_GPIO_EN (1 << 1)
#define AF9013_GPIO_O  (1 << 2)
#define AF9013_GPIO_I  (1 << 3)
#define AF9013_GPIO_WO (AF9013_GPIO_ON|AF9013_GPIO_EN)
#define AF9013_GPIO_HI (AF9013_GPIO_ON|AF9013_GPIO_EN|AF9013_GPIO_O)
#define AF9013_GPIO_TUNEW_ON  (AF9013_GPIO_ON|AF9013_GPIO_EN)
#define AF9013_GPIO_TUNEW_OFF (AF9013_GPIO_ON|AF9013_GPIO_EN|AF9013_GPIO_O)
	u8 gpio[4];

	stwuct dvb_fwontend* (*get_dvb_fwontend)(stwuct i2c_cwient *);
	stwuct i2c_adaptew* (*get_i2c_adaptew)(stwuct i2c_cwient *);
	int (*pid_fiwtew_ctww)(stwuct dvb_fwontend *, int);
	int (*pid_fiwtew)(stwuct dvb_fwontend *, u8, u16, int);
};

/*
 * AF9013/5 GPIOs (mostwy guessed)
 * demod#1-gpio#0 - set demod#2 i2c-addw fow duaw devices
 * demod#1-gpio#1 - xtaw setting (?)
 * demod#1-gpio#3 - tunew#1
 * demod#2-gpio#0 - tunew#2
 * demod#2-gpio#1 - xtaw setting (?)
 */

#endif /* AF9013_H */
