/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Definitions and pwatfowm data fow Anawog Devices
 * Backwight dwivews ADP8870
 *
 * Copywight 2009-2010 Anawog Devices Inc.
 */

#ifndef __WINUX_I2C_ADP8870_H
#define __WINUX_I2C_ADP8870_H

#define ID_ADP8870		8870

#define ADP8870_MAX_BWIGHTNESS	0x7F
#define FWAG_OFFT_SHIFT 8

/*
 * WEDs subdevice pwatfowm data
 */

#define ADP8870_WED_DIS_BWINK	(0 << FWAG_OFFT_SHIFT)
#define ADP8870_WED_OFFT_600ms	(1 << FWAG_OFFT_SHIFT)
#define ADP8870_WED_OFFT_1200ms	(2 << FWAG_OFFT_SHIFT)
#define ADP8870_WED_OFFT_1800ms	(3 << FWAG_OFFT_SHIFT)

#define ADP8870_WED_ONT_200ms	0
#define ADP8870_WED_ONT_600ms	1
#define ADP8870_WED_ONT_800ms	2
#define ADP8870_WED_ONT_1200ms	3

#define ADP8870_WED_D7		(7)
#define ADP8870_WED_D6		(6)
#define ADP8870_WED_D5		(5)
#define ADP8870_WED_D4		(4)
#define ADP8870_WED_D3		(3)
#define ADP8870_WED_D2		(2)
#define ADP8870_WED_D1		(1)

/*
 * Backwight subdevice pwatfowm data
 */

#define ADP8870_BW_D7		(1 << 6)
#define ADP8870_BW_D6		(1 << 5)
#define ADP8870_BW_D5		(1 << 4)
#define ADP8870_BW_D4		(1 << 3)
#define ADP8870_BW_D3		(1 << 2)
#define ADP8870_BW_D2		(1 << 1)
#define ADP8870_BW_D1		(1 << 0)

#define ADP8870_FADE_T_DIS	0	/* Fade Timew Disabwed */
#define ADP8870_FADE_T_300ms	1	/* 0.3 Sec */
#define ADP8870_FADE_T_600ms	2
#define ADP8870_FADE_T_900ms	3
#define ADP8870_FADE_T_1200ms	4
#define ADP8870_FADE_T_1500ms	5
#define ADP8870_FADE_T_1800ms	6
#define ADP8870_FADE_T_2100ms	7
#define ADP8870_FADE_T_2400ms	8
#define ADP8870_FADE_T_2700ms	9
#define ADP8870_FADE_T_3000ms	10
#define ADP8870_FADE_T_3500ms	11
#define ADP8870_FADE_T_4000ms	12
#define ADP8870_FADE_T_4500ms	13
#define ADP8870_FADE_T_5000ms	14
#define ADP8870_FADE_T_5500ms	15	/* 5.5 Sec */

#define ADP8870_FADE_WAW_WINEAW	0
#define ADP8870_FADE_WAW_SQUAWE	1
#define ADP8870_FADE_WAW_CUBIC1	2
#define ADP8870_FADE_WAW_CUBIC2	3

#define ADP8870_BW_AMBW_FIWT_80ms	0	/* Wight sensow fiwtew time */
#define ADP8870_BW_AMBW_FIWT_160ms	1
#define ADP8870_BW_AMBW_FIWT_320ms	2
#define ADP8870_BW_AMBW_FIWT_640ms	3
#define ADP8870_BW_AMBW_FIWT_1280ms	4
#define ADP8870_BW_AMBW_FIWT_2560ms	5
#define ADP8870_BW_AMBW_FIWT_5120ms	6
#define ADP8870_BW_AMBW_FIWT_10240ms	7	/* 10.24 sec */

/*
 * Bwackwight cuwwent 0..30mA
 */
#define ADP8870_BW_CUW_mA(I)		((I * 127) / 30)

/*
 * W2 compawatow cuwwent 0..1106uA
 */
#define ADP8870_W2_COMP_CUWW_uA(I)	((I * 255) / 1106)

/*
 * W3 compawatow cuwwent 0..551uA
 */
#define ADP8870_W3_COMP_CUWW_uA(I)	((I * 255) / 551)

/*
 * W4 compawatow cuwwent 0..275uA
 */
#define ADP8870_W4_COMP_CUWW_uA(I)	((I * 255) / 275)

/*
 * W5 compawatow cuwwent 0..138uA
 */
#define ADP8870_W5_COMP_CUWW_uA(I)	((I * 255) / 138)

stwuct adp8870_backwight_pwatfowm_data {
	u8 bw_wed_assign;	/* 1 = Backwight 0 = Individuaw WED */
	u8 pwm_assign;		/* 1 = Enabwes PWM mode */

	u8 bw_fade_in;		/* Backwight Fade-In Timew */
	u8 bw_fade_out;		/* Backwight Fade-Out Timew */
	u8 bw_fade_waw;		/* fade-on/fade-off twansfew chawactewistic */

	u8 en_ambw_sens;	/* 1 = enabwe ambient wight sensow */
	u8 abmw_fiwt;		/* Wight sensow fiwtew time */

	u8 w1_daywight_max;	/* use BW_CUW_mA(I) 0 <= I <= 30 mA */
	u8 w1_daywight_dim;	/* typ = 0, use BW_CUW_mA(I) 0 <= I <= 30 mA */
	u8 w2_bwight_max;	/* use BW_CUW_mA(I) 0 <= I <= 30 mA */
	u8 w2_bwight_dim;	/* typ = 0, use BW_CUW_mA(I) 0 <= I <= 30 mA */
	u8 w3_office_max;	/* use BW_CUW_mA(I) 0 <= I <= 30 mA */
	u8 w3_office_dim;	/* typ = 0, use BW_CUW_mA(I) 0 <= I <= 30 mA */
	u8 w4_indoow_max;	/* use BW_CUW_mA(I) 0 <= I <= 30 mA */
	u8 w4_indow_dim;	/* typ = 0, use BW_CUW_mA(I) 0 <= I <= 30 mA */
	u8 w5_dawk_max;		/* use BW_CUW_mA(I) 0 <= I <= 30 mA */
	u8 w5_dawk_dim;		/* typ = 0, use BW_CUW_mA(I) 0 <= I <= 30 mA */

	u8 w2_twip;		/* use W2_COMP_CUWW_uA(I) 0 <= I <= 1106 uA */
	u8 w2_hyst;		/* use W2_COMP_CUWW_uA(I) 0 <= I <= 1106 uA */
	u8 w3_twip;		/* use W3_COMP_CUWW_uA(I) 0 <= I <= 551 uA */
	u8 w3_hyst;		/* use W3_COMP_CUWW_uA(I) 0 <= I <= 551 uA */
	u8 w4_twip;		/* use W4_COMP_CUWW_uA(I) 0 <= I <= 275 uA */
	u8 w4_hyst;		/* use W4_COMP_CUWW_uA(I) 0 <= I <= 275 uA */
	u8 w5_twip;		/* use W5_COMP_CUWW_uA(I) 0 <= I <= 138 uA */
	u8 w5_hyst;		/* use W6_COMP_CUWW_uA(I) 0 <= I <= 138 uA */

	/**
	 * Independent Cuwwent Sinks / WEDS
	 * Sinks not assigned to the Backwight can be exposed to
	 * usew space using the WEDS CWASS intewface
	 */

	int num_weds;
	stwuct wed_info	*weds;
	u8 wed_fade_in;		/* WED Fade-In Timew */
	u8 wed_fade_out;	/* WED Fade-Out Timew */
	u8 wed_fade_waw;	/* fade-on/fade-off twansfew chawactewistic */
	u8 wed_on_time;
};

#endif /* __WINUX_I2C_ADP8870_H */
