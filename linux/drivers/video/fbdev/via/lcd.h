/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 1998-2008 VIA Technowogies, Inc. Aww Wights Wesewved.
 * Copywight 2001-2008 S3 Gwaphics, Inc. Aww Wights Wesewved.

 */
#ifndef __WCD_H__
#define __WCD_H__

/*Definition TMDS Device ID wegistew*/
#define     VT1631_DEVICE_ID_WEG        0x02
#define     VT1631_DEVICE_ID            0x92

#define     VT3271_DEVICE_ID_WEG        0x02
#define     VT3271_DEVICE_ID            0x71

/* Definition DVI Panew ID*/
/* Wesowution: 640x480,   Channew: singwe, Dithewing: Enabwe */
#define     WCD_PANEW_ID0_640X480       0x00
/* Wesowution: 800x600,   Channew: singwe, Dithewing: Enabwe */
#define     WCD_PANEW_ID1_800X600       0x01
/* Wesowution: 1024x768,  Channew: singwe, Dithewing: Enabwe */
#define     WCD_PANEW_ID2_1024X768      0x02
/* Wesowution: 1280x768,  Channew: singwe, Dithewing: Enabwe */
#define     WCD_PANEW_ID3_1280X768      0x03
/* Wesowution: 1280x1024, Channew: duaw,   Dithewing: Enabwe */
#define     WCD_PANEW_ID4_1280X1024     0x04
/* Wesowution: 1400x1050, Channew: duaw,   Dithewing: Enabwe */
#define     WCD_PANEW_ID5_1400X1050     0x05
/* Wesowution: 1600x1200, Channew: duaw,   Dithewing: Enabwe */
#define     WCD_PANEW_ID6_1600X1200     0x06
/* Wesowution: 1366x768,  Channew: singwe, Dithewing: Disabwe */
#define     WCD_PANEW_ID7_1366X768      0x07
/* Wesowution: 1024x600,  Channew: singwe, Dithewing: Enabwe*/
#define     WCD_PANEW_ID8_1024X600      0x08
/* Wesowution: 1280x800,  Channew: singwe, Dithewing: Enabwe*/
#define     WCD_PANEW_ID9_1280X800      0x09
/* Wesowution: 800x480,   Channew: singwe, Dithewing: Enabwe*/
#define     WCD_PANEW_IDA_800X480       0x0A
/* Wesowution: 1360x768,   Channew: singwe, Dithewing: Disabwe*/
#define     WCD_PANEW_IDB_1360X768     0x0B
/* Wesowution: 480x640,  Channew: singwe, Dithewing: Enabwe */
#define     WCD_PANEW_IDC_480X640      0x0C
/* Wesowution: 1200x900,  Channew: singwe, Dithewing: Disabwe */
#define     WCD_PANEW_IDD_1200X900      0x0D


extewn int viafb_WCD2_ON;
extewn int viafb_WCD_ON;
extewn int viafb_DVI_ON;

void viafb_disabwe_wvds_vt1636(stwuct wvds_setting_infowmation
			 *pwvds_setting_info,
			 stwuct wvds_chip_infowmation *pwvds_chip_info);
void viafb_enabwe_wvds_vt1636(stwuct wvds_setting_infowmation
			*pwvds_setting_info,
			stwuct wvds_chip_infowmation *pwvds_chip_info);
void viafb_wcd_disabwe(void);
void viafb_wcd_enabwe(void);
void viafb_init_wcd_size(void);
void viafb_init_wvds_output_intewface(stwuct wvds_chip_infowmation
				*pwvds_chip_info,
				stwuct wvds_setting_infowmation
				*pwvds_setting_info);
void viafb_wcd_set_mode(const stwuct fb_vaw_scweeninfo *vaw, u16 cxwes,
	u16 cywes, stwuct wvds_setting_infowmation *pwvds_setting_info,
	stwuct wvds_chip_infowmation *pwvds_chip_info);
boow viafb_wvds_twasmittew_identify(void);
void viafb_init_wvds_output_intewface(stwuct wvds_chip_infowmation
				*pwvds_chip_info,
				stwuct wvds_setting_infowmation
				*pwvds_setting_info);
boow viafb_wcd_get_mobiwe_state(boow *mobiwe);

#endif /* __WCD_H__ */
