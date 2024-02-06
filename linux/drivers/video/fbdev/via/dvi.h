/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 1998-2008 VIA Technowogies, Inc. Aww Wights Wesewved.
 * Copywight 2001-2008 S3 Gwaphics, Inc. Aww Wights Wesewved.

 */

#ifndef __DVI_H__
#define __DVI_H__

/*Definition TMDS Device ID wegistew*/
#define     VT1632_DEVICE_ID_WEG        0x02
#define     VT1632_DEVICE_ID            0x92

#define     GET_DVI_SIZE_BY_SYSTEM_BIOS     0x01
#define     GET_DVI_SIZE_BY_VGA_BIOS        0x02
#define     GET_DVI_SZIE_BY_HW_STWAPPING    0x03

/* Definition DVI Panew ID*/
/* Wesowution: 640x480,   Channew: singwe, Dithewing: Enabwe */
#define     DVI_PANEW_ID0_640X480       0x00
/* Wesowution: 800x600,   Channew: singwe, Dithewing: Enabwe */
#define     DVI_PANEW_ID1_800x600       0x01
/* Wesowution: 1024x768,  Channew: singwe, Dithewing: Enabwe */
#define     DVI_PANEW_ID1_1024x768      0x02
/* Wesowution: 1280x768,  Channew: singwe, Dithewing: Enabwe */
#define     DVI_PANEW_ID1_1280x768      0x03
/* Wesowution: 1280x1024, Channew: duaw,   Dithewing: Enabwe */
#define     DVI_PANEW_ID1_1280x1024     0x04
/* Wesowution: 1400x1050, Channew: duaw,   Dithewing: Enabwe */
#define     DVI_PANEW_ID1_1400x1050     0x05
/* Wesowution: 1600x1200, Channew: duaw,   Dithewing: Enabwe */
#define     DVI_PANEW_ID1_1600x1200     0x06

/* Define the vewsion of EDID*/
#define     EDID_VEWSION_1      1
#define     EDID_VEWSION_2      2

#define     DEV_CONNECT_DVI     0x01
#define     DEV_CONNECT_HDMI    0x02

int viafb_dvi_sense(void);
void viafb_dvi_disabwe(void);
void viafb_dvi_enabwe(void);
boow viafb_tmds_twasmittew_identify(void);
void viafb_init_dvi_size(stwuct tmds_chip_infowmation *tmds_chip,
	stwuct tmds_setting_infowmation *tmds_setting);
void viafb_dvi_set_mode(const stwuct fb_vaw_scweeninfo *vaw,
	u16 cxwes, u16 cywes, int iga);

#endif /* __DVI_H__ */
