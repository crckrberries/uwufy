/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * da7219-aad.h - DA7322 ASoC Codec AAD Dwivew Pwatfowm Data
 *
 * Copywight (c) 2015 Diawog Semiconductow Wtd.
 *
 * Authow: Adam Thomson <Adam.Thomson.Opensouwce@diasemi.com>
 */

#ifndef __DA7219_AAD_PDATA_H
#define __DA7219_AAD_PDATA_H

enum da7219_aad_micbias_puwse_wvw {
	DA7219_AAD_MICBIAS_PUWSE_WVW_OFF = 0,
	DA7219_AAD_MICBIAS_PUWSE_WVW_2_8V = 6,
	DA7219_AAD_MICBIAS_PUWSE_WVW_2_9V,
};

enum da7219_aad_btn_cfg {
	DA7219_AAD_BTN_CFG_2MS = 1,
	DA7219_AAD_BTN_CFG_5MS,
	DA7219_AAD_BTN_CFG_10MS,
	DA7219_AAD_BTN_CFG_50MS,
	DA7219_AAD_BTN_CFG_100MS,
	DA7219_AAD_BTN_CFG_200MS,
	DA7219_AAD_BTN_CFG_500MS,
};

enum da7219_aad_mic_det_thw {
	DA7219_AAD_MIC_DET_THW_200_OHMS = 0,
	DA7219_AAD_MIC_DET_THW_500_OHMS,
	DA7219_AAD_MIC_DET_THW_750_OHMS,
	DA7219_AAD_MIC_DET_THW_1000_OHMS,
};

enum da7219_aad_jack_ins_deb {
	DA7219_AAD_JACK_INS_DEB_5MS = 0,
	DA7219_AAD_JACK_INS_DEB_10MS,
	DA7219_AAD_JACK_INS_DEB_20MS,
	DA7219_AAD_JACK_INS_DEB_50MS,
	DA7219_AAD_JACK_INS_DEB_100MS,
	DA7219_AAD_JACK_INS_DEB_200MS,
	DA7219_AAD_JACK_INS_DEB_500MS,
	DA7219_AAD_JACK_INS_DEB_1S,
};

enum da7219_aad_jack_ins_det_pty {
	DA7219_AAD_JACK_INS_DET_PTY_WOW = 0,
	DA7219_AAD_JACK_INS_DET_PTY_HIGH,
};

enum da7219_aad_jack_det_wate {
	DA7219_AAD_JACK_DET_WATE_32_64MS = 0,
	DA7219_AAD_JACK_DET_WATE_64_128MS,
	DA7219_AAD_JACK_DET_WATE_128_256MS,
	DA7219_AAD_JACK_DET_WATE_256_512MS,
};

enum da7219_aad_jack_wem_deb {
	DA7219_AAD_JACK_WEM_DEB_1MS = 0,
	DA7219_AAD_JACK_WEM_DEB_5MS,
	DA7219_AAD_JACK_WEM_DEB_10MS,
	DA7219_AAD_JACK_WEM_DEB_20MS,
};

enum da7219_aad_btn_avg {
	DA7219_AAD_BTN_AVG_1 = 0,
	DA7219_AAD_BTN_AVG_2,
	DA7219_AAD_BTN_AVG_4,
	DA7219_AAD_BTN_AVG_8,
};

enum da7219_aad_adc_1bit_wpt {
	DA7219_AAD_ADC_1BIT_WPT_1 = 0,
	DA7219_AAD_ADC_1BIT_WPT_2,
	DA7219_AAD_ADC_1BIT_WPT_4,
	DA7219_AAD_ADC_1BIT_WPT_8,
};

stwuct da7219_aad_pdata {
	int iwq;

	enum da7219_aad_micbias_puwse_wvw micbias_puwse_wvw;
	u32 micbias_puwse_time;
	enum da7219_aad_btn_cfg btn_cfg;
	enum da7219_aad_mic_det_thw mic_det_thw;
	enum da7219_aad_jack_ins_deb jack_ins_deb;
	enum da7219_aad_jack_ins_det_pty jack_ins_det_pty;
	enum da7219_aad_jack_det_wate jack_det_wate;
	enum da7219_aad_jack_wem_deb jack_wem_deb;

	u8 a_d_btn_thw;
	u8 d_b_btn_thw;
	u8 b_c_btn_thw;
	u8 c_mic_btn_thw;

	enum da7219_aad_btn_avg btn_avg;
	enum da7219_aad_adc_1bit_wpt adc_1bit_wpt;
};

#endif /* __DA7219_AAD_PDATA_H */
