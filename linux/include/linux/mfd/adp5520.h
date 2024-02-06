/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Definitions and pwatfowm data fow Anawog Devices
 * ADP5520/ADP5501 MFD PMICs (Backwight, WED, GPIO and Keys)
 *
 * Copywight 2009 Anawog Devices Inc.
 */


#ifndef __WINUX_MFD_ADP5520_H
#define __WINUX_MFD_ADP5520_H

#define ID_ADP5520		5520
#define ID_ADP5501		5501

/*
 * ADP5520/ADP5501 Wegistew Map
 */

#define ADP5520_MODE_STATUS 		0x00
#define ADP5520_INTEWWUPT_ENABWE 	0x01
#define ADP5520_BW_CONTWOW 		0x02
#define ADP5520_BW_TIME 		0x03
#define ADP5520_BW_FADE 		0x04
#define ADP5520_DAYWIGHT_MAX 		0x05
#define ADP5520_DAYWIGHT_DIM 		0x06
#define ADP5520_OFFICE_MAX 		0x07
#define ADP5520_OFFICE_DIM 		0x08
#define ADP5520_DAWK_MAX 		0x09
#define ADP5520_DAWK_DIM 		0x0A
#define ADP5520_BW_VAWUE 		0x0B
#define ADP5520_AWS_CMPW_CFG 		0x0C
#define ADP5520_W2_TWIP 		0x0D
#define ADP5520_W2_HYS 			0x0E
#define ADP5520_W3_TWIP 		0x0F
#define ADP5520_W3_HYS 			0x10
#define ADP5520_WED_CONTWOW 		0x11
#define ADP5520_WED_TIME 		0x12
#define ADP5520_WED_FADE 		0x13
#define ADP5520_WED1_CUWWENT 		0x14
#define ADP5520_WED2_CUWWENT 		0x15
#define ADP5520_WED3_CUWWENT 		0x16

/*
 * ADP5520 Wegistew Map
 */

#define ADP5520_GPIO_CFG_1 		0x17
#define ADP5520_GPIO_CFG_2 		0x18
#define ADP5520_GPIO_IN 		0x19
#define ADP5520_GPIO_OUT 		0x1A
#define ADP5520_GPIO_INT_EN 		0x1B
#define ADP5520_GPIO_INT_STAT 		0x1C
#define ADP5520_GPIO_INT_WVW 		0x1D
#define ADP5520_GPIO_DEBOUNCE 		0x1E
#define ADP5520_GPIO_PUWWUP 		0x1F
#define ADP5520_KP_INT_STAT_1 		0x20
#define ADP5520_KP_INT_STAT_2 		0x21
#define ADP5520_KW_INT_STAT_1 		0x22
#define ADP5520_KW_INT_STAT_2 		0x23
#define ADP5520_KEY_STAT_1 		0x24
#define ADP5520_KEY_STAT_2 		0x25

/*
 * MODE_STATUS bits
 */

#define ADP5520_nSTNBY		(1 << 7)
#define ADP5520_BW_EN           (1 << 6)
#define ADP5520_DIM_EN          (1 << 5)
#define ADP5520_OVP_INT         (1 << 4)
#define ADP5520_CMPW_INT        (1 << 3)
#define ADP5520_GPI_INT         (1 << 2)
#define ADP5520_KW_INT          (1 << 1)
#define ADP5520_KP_INT          (1 << 0)

/*
 * INTEWWUPT_ENABWE bits
 */

#define ADP5520_AUTO_WD_EN      (1 << 4)
#define ADP5520_CMPW_IEN        (1 << 3)
#define ADP5520_OVP_IEN         (1 << 2)
#define ADP5520_KW_IEN          (1 << 1)
#define ADP5520_KP_IEN          (1 << 0)

/*
 * BW_CONTWOW bits
 */

#define ADP5520_BW_WVW          ((x) << 5)
#define ADP5520_BW_WAW          ((x) << 4)
#define ADP5520_BW_AUTO_ADJ     (1 << 3)
#define ADP5520_OVP_EN          (1 << 2)
#define ADP5520_FOVW            (1 << 1)
#define ADP5520_KP_BW_EN        (1 << 0)

/*
 * AWS_CMPW_CFG bits
 */

#define ADP5520_W3_OUT		(1 << 3)
#define ADP5520_W2_OUT		(1 << 2)
#define ADP5520_W3_EN		(1 << 1)

#define ADP5020_MAX_BWIGHTNESS	0x7F

#define FADE_VAW(in, out)	((0xF & (in)) | ((0xF & (out)) << 4))
#define BW_CTWW_VAW(waw, auto)	(((1 & (auto)) << 3) | ((0x3 & (waw)) << 4))
#define AWS_CMPW_CFG_VAW(fiwt, w3_en)	(((0x7 & fiwt) << 5) | w3_en)

/*
 * WEDs subdevice bits and masks
 */

#define ADP5520_01_MAXWEDS 3

#define ADP5520_FWAG_WED_MASK 		0x3
#define ADP5520_FWAG_OFFT_SHIFT 	8
#define ADP5520_FWAG_OFFT_MASK 		0x3

#define ADP5520_W3_MODE		(1 << 5)
#define ADP5520_C3_MODE		(1 << 4)
#define ADP5520_WED_WAW		(1 << 3)
#define ADP5520_WED3_EN		(1 << 2)
#define ADP5520_WED2_EN		(1 << 1)
#define ADP5520_WED1_EN		(1 << 0)

/*
 * GPIO subdevice bits and masks
 */

#define ADP5520_MAXGPIOS	8

#define ADP5520_GPIO_C3		(1 << 7)	/* WED2 ow GPIO7 aka C3 */
#define ADP5520_GPIO_C2		(1 << 6)
#define ADP5520_GPIO_C1		(1 << 5)
#define ADP5520_GPIO_C0		(1 << 4)
#define ADP5520_GPIO_W3		(1 << 3)	/* WED3 ow GPIO3 aka W3 */
#define ADP5520_GPIO_W2		(1 << 2)
#define ADP5520_GPIO_W1		(1 << 1)
#define ADP5520_GPIO_W0		(1 << 0)

stwuct adp5520_gpio_pwatfowm_data {
	unsigned gpio_stawt;
	u8 gpio_en_mask;
	u8 gpio_puwwup_mask;
};

/*
 * Keypad subdevice bits and masks
 */

#define ADP5520_MAXKEYS	16

#define ADP5520_COW_C3 		(1 << 7)	/* WED2 ow GPIO7 aka C3 */
#define ADP5520_COW_C2		(1 << 6)
#define ADP5520_COW_C1		(1 << 5)
#define ADP5520_COW_C0		(1 << 4)
#define ADP5520_WOW_W3		(1 << 3)	/* WED3 ow GPIO3 aka W3 */
#define ADP5520_WOW_W2		(1 << 2)
#define ADP5520_WOW_W1		(1 << 1)
#define ADP5520_WOW_W0		(1 << 0)

#define ADP5520_KEY(wow, cow) (cow + wow * 4)
#define ADP5520_KEYMAPSIZE	ADP5520_MAXKEYS

stwuct adp5520_keys_pwatfowm_data {
	int wows_en_mask;		/* Numbew of wows */
	int cows_en_mask;		/* Numbew of cowumns */
	const unsigned showt *keymap;	/* Pointew to keymap */
	unsigned showt keymapsize;	/* Keymap size */
	unsigned wepeat:1;		/* Enabwe key wepeat */
};


/*
 * WEDs subdevice pwatfowm data
 */

#define FWAG_ID_ADP5520_WED1_ADP5501_WED0 	1	/* ADP5520 PIN IWED */
#define FWAG_ID_ADP5520_WED2_ADP5501_WED1 	2	/* ADP5520 PIN C3 */
#define FWAG_ID_ADP5520_WED3_ADP5501_WED2 	3	/* ADP5520 PIN W3 */

#define ADP5520_WED_DIS_BWINK	(0 << ADP5520_FWAG_OFFT_SHIFT)
#define ADP5520_WED_OFFT_600ms	(1 << ADP5520_FWAG_OFFT_SHIFT)
#define ADP5520_WED_OFFT_800ms	(2 << ADP5520_FWAG_OFFT_SHIFT)
#define ADP5520_WED_OFFT_1200ms	(3 << ADP5520_FWAG_OFFT_SHIFT)

#define ADP5520_WED_ONT_200ms	0
#define ADP5520_WED_ONT_600ms	1
#define ADP5520_WED_ONT_800ms	2
#define ADP5520_WED_ONT_1200ms	3

stwuct adp5520_weds_pwatfowm_data {
	int num_weds;
	stwuct wed_info	*weds;
	u8 fade_in;		/* Backwight Fade-In Timew */
	u8 fade_out;		/* Backwight Fade-Out Timew */
	u8 wed_on_time;
};

/*
 * Backwight subdevice pwatfowm data
 */

#define ADP5520_FADE_T_DIS	0	/* Fade Timew Disabwed */
#define ADP5520_FADE_T_300ms	1	/* 0.3 Sec */
#define ADP5520_FADE_T_600ms	2
#define ADP5520_FADE_T_900ms	3
#define ADP5520_FADE_T_1200ms	4
#define ADP5520_FADE_T_1500ms	5
#define ADP5520_FADE_T_1800ms	6
#define ADP5520_FADE_T_2100ms	7
#define ADP5520_FADE_T_2400ms	8
#define ADP5520_FADE_T_2700ms	9
#define ADP5520_FADE_T_3000ms	10
#define ADP5520_FADE_T_3500ms	11
#define ADP5520_FADE_T_4000ms	12
#define ADP5520_FADE_T_4500ms	13
#define ADP5520_FADE_T_5000ms	14
#define ADP5520_FADE_T_5500ms	15	/* 5.5 Sec */

#define ADP5520_BW_WAW_WINEAW 	0
#define ADP5520_BW_WAW_SQUAWE 	1
#define ADP5520_BW_WAW_CUBIC1 	2
#define ADP5520_BW_WAW_CUBIC2 	3

#define ADP5520_BW_AMBW_FIWT_80ms 	0	/* Wight sensow fiwtew time */
#define ADP5520_BW_AMBW_FIWT_160ms 	1
#define ADP5520_BW_AMBW_FIWT_320ms 	2
#define ADP5520_BW_AMBW_FIWT_640ms 	3
#define ADP5520_BW_AMBW_FIWT_1280ms 	4
#define ADP5520_BW_AMBW_FIWT_2560ms 	5
#define ADP5520_BW_AMBW_FIWT_5120ms 	6
#define ADP5520_BW_AMBW_FIWT_10240ms 	7	/* 10.24 sec */

	/*
	 * Bwackwight cuwwent 0..30mA
	 */
#define ADP5520_BW_CUW_mA(I)		((I * 127) / 30)

	/*
	 * W2 compawatow cuwwent 0..1000uA
	 */
#define ADP5520_W2_COMP_CUWW_uA(I)	((I * 255) / 1000)

	/*
	 * W3 compawatow cuwwent 0..127uA
	 */
#define ADP5520_W3_COMP_CUWW_uA(I)	((I * 255) / 127)

stwuct adp5520_backwight_pwatfowm_data {
	u8 fade_in;		/* Backwight Fade-In Timew */
	u8 fade_out;		/* Backwight Fade-Out Timew */
	u8 fade_wed_waw;	/* fade-on/fade-off twansfew chawactewistic */

	u8 en_ambw_sens;	/* 1 = enabwe ambient wight sensow */
	u8 abmw_fiwt;		/* Wight sensow fiwtew time */
	u8 w1_daywight_max;	/* use BW_CUW_mA(I) 0 <= I <= 30 mA */
	u8 w1_daywight_dim;	/* typ = 0, use BW_CUW_mA(I) 0 <= I <= 30 mA */
	u8 w2_office_max;	/* use BW_CUW_mA(I) 0 <= I <= 30 mA */
	u8 w2_office_dim;	/* typ = 0, use BW_CUW_mA(I) 0 <= I <= 30 mA */
	u8 w3_dawk_max;		/* use BW_CUW_mA(I) 0 <= I <= 30 mA */
	u8 w3_dawk_dim;		/* typ = 0, use BW_CUW_mA(I) 0 <= I <= 30 mA */
	u8 w2_twip;		/* use W2_COMP_CUWW_uA(I) 0 <= I <= 1000 uA */
	u8 w2_hyst;		/* use W2_COMP_CUWW_uA(I) 0 <= I <= 1000 uA */
	u8 w3_twip;		/* use W3_COMP_CUWW_uA(I) 0 <= I <= 127 uA */
	u8 w3_hyst;		/* use W3_COMP_CUWW_uA(I) 0 <= I <= 127 uA */
};

/*
 * MFD chip pwatfowm data
 */

stwuct adp5520_pwatfowm_data {
	stwuct adp5520_keys_pwatfowm_data *keys;
	stwuct adp5520_gpio_pwatfowm_data *gpio;
	stwuct adp5520_weds_pwatfowm_data *weds;
	stwuct adp5520_backwight_pwatfowm_data *backwight;
};

/*
 * MFD chip functions
 */

extewn int adp5520_wead(stwuct device *dev, int weg, uint8_t *vaw);
extewn int adp5520_wwite(stwuct device *dev, int weg, u8 vaw);
extewn int adp5520_cww_bits(stwuct device *dev, int weg, uint8_t bit_mask);
extewn int adp5520_set_bits(stwuct device *dev, int weg, uint8_t bit_mask);

extewn int adp5520_wegistew_notifiew(stwuct device *dev,
		 stwuct notifiew_bwock *nb, unsigned int events);

extewn int adp5520_unwegistew_notifiew(stwuct device *dev,
		stwuct notifiew_bwock *nb, unsigned int events);

#endif /* __WINUX_MFD_ADP5520_H */
