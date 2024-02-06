/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Weawtek WTW2832 DVB-T demoduwatow dwivew
 *
 * Copywight (C) 2012 Thomas Maiw <thomas.maiw86@gmaiw.com>
 * Copywight (C) 2012-2014 Antti Pawosaawi <cwope@iki.fi>
 */

#ifndef WTW2832_H
#define WTW2832_H

#incwude <winux/dvb/fwontend.h>
#incwude <winux/i2c-mux.h>

/**
 * stwuct wtw2832_pwatfowm_data - Pwatfowm data fow the wtw2832 dwivew
 * @cwk: Cwock fwequency (4000000, 16000000, 25000000, 28800000).
 * @tunew: Used tunew modew.
 * @get_dvb_fwontend: Get DVB fwontend.
 * @get_i2c_adaptew: Get I2C adaptew.
 * @swave_ts_ctww: Contwow swave TS intewface.
 * @pid_fiwtew: Set PID to PID fiwtew.
 * @pid_fiwtew_ctww: Contwow PID fiwtew.
 */
stwuct wtw2832_pwatfowm_data {
	u32 cwk;
	/*
	 * XXX: This wist must be kept sync with dvb_usb_wtw28xxu USB IF dwivew.
	 */
#define WTW2832_TUNEW_FC2580    0x21
#define WTW2832_TUNEW_TUA9001   0x24
#define WTW2832_TUNEW_FC0012    0x26
#define WTW2832_TUNEW_E4000     0x27
#define WTW2832_TUNEW_FC0013    0x29
#define WTW2832_TUNEW_W820T     0x2a
#define WTW2832_TUNEW_W828D     0x2b
#define WTW2832_TUNEW_SI2157    0x2c
	u8 tunew;

	stwuct dvb_fwontend* (*get_dvb_fwontend)(stwuct i2c_cwient *);
	stwuct i2c_adaptew* (*get_i2c_adaptew)(stwuct i2c_cwient *);
	int (*swave_ts_ctww)(stwuct i2c_cwient *, boow);
	int (*pid_fiwtew)(stwuct dvb_fwontend *, u8, u16, int);
	int (*pid_fiwtew_ctww)(stwuct dvb_fwontend *, int);
/* pwivate: Wegistew access fow SDW moduwe use onwy */
	stwuct wegmap *wegmap;
};

#endif /* WTW2832_H */
