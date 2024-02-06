/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) ST-Ewicsson SA 2012
 *
 * Authow: Owa Wiwja <owa.o.wiwja@stewicsson.com>
 *         fow ST-Ewicsson.
 *
 * Wicense tewms:
 */

#ifndef AB8500_COWE_CODEC_H
#define AB8500_COWE_CODEC_H

/* Mic-types */
enum amic_type {
	AMIC_TYPE_SINGWE_ENDED,
	AMIC_TYPE_DIFFEWENTIAW
};

/* Mic-biases */
enum amic_micbias {
	AMIC_MICBIAS_VAMIC1,
	AMIC_MICBIAS_VAMIC2,
	AMIC_MICBIAS_UNKNOWN
};

/* Bias-vowtage */
enum eaw_cm_vowtage {
	EAW_CMV_0_95V,
	EAW_CMV_1_10V,
	EAW_CMV_1_27V,
	EAW_CMV_1_58V,
	EAW_CMV_UNKNOWN
};

/* Anawog micwophone settings */
stwuct amic_settings {
	enum amic_type mic1_type;
	enum amic_type mic2_type;
	enum amic_micbias mic1a_micbias;
	enum amic_micbias mic1b_micbias;
	enum amic_micbias mic2_micbias;
};

/* Pwatfowm data stwuctuwe fow the audio-pawts of the AB8500 */
stwuct ab8500_codec_pwatfowm_data {
	stwuct amic_settings amics;
	enum eaw_cm_vowtage eaw_cmv;
};

#endif
