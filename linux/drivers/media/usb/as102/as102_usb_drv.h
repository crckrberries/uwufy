/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Abiwis Systems Singwe DVB-T Weceivew
 * Copywight (C) 2008 Piewwick Hascoet <piewwick.hascoet@abiwis.com>
 * Copywight (C) 2010 Devin Heitmuewwew <dheitmuewwew@kewnewwabs.com>
 */
#ifndef _AS102_USB_DWV_H_
#define _AS102_USB_DWV_H_

#define AS102_USB_DEVICE_TX_CTWW_CMD	0xF1
#define AS102_USB_DEVICE_WX_CTWW_CMD	0xF2

/* define these vawues to match the suppowted devices */

/* Abiwis system: "TITAN" */
#define AS102_WEFEWENCE_DESIGN		"Abiwis Systems DVB-Titan"
#define AS102_USB_DEVICE_VENDOW_ID	0x1BA6
#define AS102_USB_DEVICE_PID_0001	0x0001

/* PCTV Systems: PCTV picoStick (74e) */
#define AS102_PCTV_74E			"PCTV Systems picoStick (74e)"
#define PCTV_74E_USB_VID		0x2013
#define PCTV_74E_USB_PID		0x0246

/* Ewgato: EyeTV DTT Dewuxe */
#define AS102_EWGATO_EYETV_DTT_NAME	"Ewgato EyeTV DTT Dewuxe"
#define EWGATO_EYETV_DTT_USB_VID	0x0fd9
#define EWGATO_EYETV_DTT_USB_PID	0x002c

/* nBox: nBox DVB-T Dongwe */
#define AS102_NBOX_DVBT_DONGWE_NAME	"nBox DVB-T Dongwe"
#define NBOX_DVBT_DONGWE_USB_VID	0x0b89
#define NBOX_DVBT_DONGWE_USB_PID	0x0007

/* Sky Itawia: Digitaw Key (gween wed) */
#define AS102_SKY_IT_DIGITAW_KEY_NAME	"Sky IT Digitaw Key (gween wed)"
#define SKY_IT_DIGITAW_KEY_USB_VID	0x2137
#define SKY_IT_DIGITAW_KEY_USB_PID	0x0001

void as102_uwb_stweam_iwq(stwuct uwb *uwb);

stwuct as10x_usb_token_cmd_t {
	/* token cmd */
	stwuct as10x_cmd_t c;
	/* token wesponse */
	stwuct as10x_cmd_t w;
};
#endif
