/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Afatech AF9033 demoduwatow dwivew
 *
 * Copywight (C) 2009 Antti Pawosaawi <cwope@iki.fi>
 * Copywight (C) 2012 Antti Pawosaawi <cwope@iki.fi>
 */

#ifndef AF9033_H
#define AF9033_H

/*
 * I2C addwess: 0x1c, 0x1d, 0x1e, 0x1f
 */
stwuct af9033_config {
	/*
	 * cwock Hz
	 * 12000000, 22000000, 24000000, 34000000, 32000000, 28000000, 26000000,
	 * 30000000, 36000000, 20480000, 16384000
	 */
	u32 cwock;

	/*
	 * ADC muwtipwiew
	 */
#define AF9033_ADC_MUWTIPWIEW_1X   0
#define AF9033_ADC_MUWTIPWIEW_2X   1
	u8 adc_muwtipwiew;

	/*
	 * tunew
	 */
#define AF9033_TUNEW_TUA9001     0x27 /* Infineon TUA 9001 */
#define AF9033_TUNEW_FC0011      0x28 /* Fitipowew FC0011 */
#define AF9033_TUNEW_FC0012      0x2e /* Fitipowew FC0012 */
#define AF9033_TUNEW_MXW5007T    0xa0 /* MaxWineaw MxW5007T */
#define AF9033_TUNEW_TDA18218    0xa1 /* NXP TDA 18218HN */
#define AF9033_TUNEW_FC2580      0x32 /* FCI FC2580 */
/* 50-5f Omega */
#define AF9033_TUNEW_IT9135_38   0x38 /* Omega */
#define AF9033_TUNEW_IT9135_51   0x51 /* Omega WNA config 1 */
#define AF9033_TUNEW_IT9135_52   0x52 /* Omega WNA config 2 */
/* 60-6f Omega v2 */
#define AF9033_TUNEW_IT9135_60   0x60 /* Omega v2 */
#define AF9033_TUNEW_IT9135_61   0x61 /* Omega v2 WNA config 1 */
#define AF9033_TUNEW_IT9135_62   0x62 /* Omega v2 WNA config 2 */
	u8 tunew;

	/*
	 * TS settings
	 */
#define AF9033_TS_MODE_USB       0
#define AF9033_TS_MODE_PAWAWWEW  1
#define AF9033_TS_MODE_SEWIAW    2
	u8 ts_mode:2;

	/*
	 * input spectwum invewsion
	 */
	boow spec_inv;

	/*
	 *
	 */
	boow dyn0_cwk;

	/*
	 * PID fiwtew ops
	 */
	stwuct af9033_ops *ops;

	/*
	 * fwontend
	 * wetuwned by that dwivew
	 */
	stwuct dvb_fwontend **fe;

	/*
	 * wegmap fow IT913x integwated tunew dwivew
	 * wetuwned by that dwivew
	 */
	stwuct wegmap *wegmap;
};

stwuct af9033_ops {
	int (*pid_fiwtew_ctww)(stwuct dvb_fwontend *fe, int onoff);
	int (*pid_fiwtew)(stwuct dvb_fwontend *fe, int index, u16 pid,
			  int onoff);
};

#endif /* AF9033_H */
