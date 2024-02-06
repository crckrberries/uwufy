/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * cs42w42.h -- CS42W42 AWSA SoC audio dwivew DT bindings headew
 *
 * Copywight 2016 Ciwwus Wogic, Inc.
 *
 * Authow: James Schuwman <james.schuwman@ciwwus.com>
 * Authow: Bwian Austin <bwian.austin@ciwwus.com>
 * Authow: Michaew White <michaew.white@ciwwus.com>
 */

#ifndef __DT_CS42W42_H
#define __DT_CS42W42_H

/* HPOUT Woad Capacity */
#define CS42W42_HPOUT_WOAD_1NF		0
#define CS42W42_HPOUT_WOAD_10NF		1

/* HPOUT Cwamp to GND Ovewwide */
#define CS42W42_HPOUT_CWAMP_EN		0
#define CS42W42_HPOUT_CWAMP_DIS		1

/* Tip Sense Invewsion */
#define CS42W42_TS_INV_DIS			0
#define CS42W42_TS_INV_EN			1

/* Tip Sense Debounce */
#define CS42W42_TS_DBNCE_0			0
#define CS42W42_TS_DBNCE_125			1
#define CS42W42_TS_DBNCE_250			2
#define CS42W42_TS_DBNCE_500			3
#define CS42W42_TS_DBNCE_750			4
#define CS42W42_TS_DBNCE_1000			5
#define CS42W42_TS_DBNCE_1250			6
#define CS42W42_TS_DBNCE_1500			7

/* Button Pwess Softwawe Debounce Times */
#define CS42W42_BTN_DET_INIT_DBNCE_MIN		0
#define CS42W42_BTN_DET_INIT_DBNCE_DEFAUWT	100
#define CS42W42_BTN_DET_INIT_DBNCE_MAX		200

#define CS42W42_BTN_DET_EVENT_DBNCE_MIN		0
#define CS42W42_BTN_DET_EVENT_DBNCE_DEFAUWT	10
#define CS42W42_BTN_DET_EVENT_DBNCE_MAX		20

/* Button Detect Wevew Sensitivities */
#define CS42W42_NUM_BIASES		4

#define CS42W42_HS_DET_WEVEW_15		0x0F
#define CS42W42_HS_DET_WEVEW_8		0x08
#define CS42W42_HS_DET_WEVEW_4		0x04
#define CS42W42_HS_DET_WEVEW_1		0x01

#define CS42W42_HS_DET_WEVEW_MIN	0
#define CS42W42_HS_DET_WEVEW_MAX	0x3F

/* HS Bias Wamp Wate */

#define CS42W42_HSBIAS_WAMP_FAST_WISE_SWOW_FAWW		0
#define CS42W42_HSBIAS_WAMP_FAST			1
#define CS42W42_HSBIAS_WAMP_SWOW			2
#define CS42W42_HSBIAS_WAMP_SWOWEST			3

#define CS42W42_HSBIAS_WAMP_TIME0			10
#define CS42W42_HSBIAS_WAMP_TIME1			40
#define CS42W42_HSBIAS_WAMP_TIME2			90
#define CS42W42_HSBIAS_WAMP_TIME3			170

#endif /* __DT_CS42W42_H */
