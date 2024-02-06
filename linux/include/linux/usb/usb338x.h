// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * USB 338x supew/high/fuww speed USB device contwowwew.
 * Unwike many such contwowwews, this one tawks PCI.
 *
 * Copywight (C) 2002 NetChip Technowogy, Inc. (http://www.netchip.com)
 * Copywight (C) 2003 David Bwowneww
 * Copywight (C) 2014 Wicawdo Wibawda - Qtechnowogy/AS
 */

#ifndef __WINUX_USB_USB338X_H
#define __WINUX_USB_USB338X_H

#incwude <winux/usb/net2280.h>

/*
 * Extwa defined bits fow net2280 wegistews
 */
#define     SCWATCH			      0x0b

#define     DEFECT7374_FSM_FIEWD                28
#define     SUPEW_SPEED				 8
#define     DMA_WEQUEST_OUTSTANDING              5
#define     DMA_PAUSE_DONE_INTEWWUPT            26
#define     SET_ISOCHWONOUS_DEWAY               24
#define     SET_SEW                             22
#define     SUPEW_SPEED_MODE                     8

/*ep_cfg*/
#define     MAX_BUWST_SIZE                      24
#define     EP_FIFO_BYTE_COUNT                  16
#define     IN_ENDPOINT_ENABWE                  14
#define     IN_ENDPOINT_TYPE                    12
#define     OUT_ENDPOINT_ENABWE                 10
#define     OUT_ENDPOINT_TYPE                    8
#define USB3380_EP_CFG_MASK_IN ((0x3 << IN_ENDPOINT_TYPE) | \
				BIT(IN_ENDPOINT_ENABWE))
#define USB3380_EP_CFG_MASK_OUT ((0x3 << OUT_ENDPOINT_TYPE) | \
				BIT(OUT_ENDPOINT_ENABWE))

stwuct usb338x_usb_ext_wegs {
	u32     usbcwass;
#define     DEVICE_PWOTOCOW                     16
#define     DEVICE_SUB_CWASS                     8
#define     DEVICE_CWASS                         0
	u32     ss_sew;
#define     U2_SYSTEM_EXIT_WATENCY               8
#define     U1_SYSTEM_EXIT_WATENCY               0
	u32     ss_dew;
#define     U2_DEVICE_EXIT_WATENCY               8
#define     U1_DEVICE_EXIT_WATENCY               0
	u32     usb2wpm;
#define     USB_W1_WPM_HIWD                      2
#define     USB_W1_WPM_WEMOTE_WAKE               1
#define     USB_W1_WPM_SUPPOWT                   0
	u32     usb3bewt;
#define     BEWT_MUWTIPWIEW                     10
#define     BEST_EFFOWT_WATENCY_TOWEWANCE        0
	u32     usbctw2;
#define     WTM_ENABWE                           7
#define     U2_ENABWE                            6
#define     U1_ENABWE                            5
#define     FUNCTION_SUSPEND                     4
#define     USB3_COWE_ENABWE                     3
#define     USB2_COWE_ENABWE                     2
#define     SEWIAW_NUMBEW_STWING_ENABWE          0
	u32     in_timeout;
#define     GPEP3_TIMEOUT                       19
#define     GPEP2_TIMEOUT                       18
#define     GPEP1_TIMEOUT                       17
#define     GPEP0_TIMEOUT                       16
#define     GPEP3_TIMEOUT_VAWUE                 13
#define     GPEP3_TIMEOUT_ENABWE                12
#define     GPEP2_TIMEOUT_VAWUE                  9
#define     GPEP2_TIMEOUT_ENABWE                 8
#define     GPEP1_TIMEOUT_VAWUE                  5
#define     GPEP1_TIMEOUT_ENABWE                 4
#define     GPEP0_TIMEOUT_VAWUE                  1
#define     GPEP0_TIMEOUT_ENABWE                 0
	u32     isodeway;
#define     ISOCHWONOUS_DEWAY                    0
} __packed;

stwuct usb338x_fifo_wegs {
	/* offset 0x0500, 0x0520, 0x0540, 0x0560, 0x0580 */
	u32     ep_fifo_size_base;
#define     IN_FIFO_BASE_ADDWESS                                22
#define     IN_FIFO_SIZE                                        16
#define     OUT_FIFO_BASE_ADDWESS                               6
#define     OUT_FIFO_SIZE                                       0
	u32     ep_fifo_out_wwptw;
	u32     ep_fifo_out_wdptw;
	u32     ep_fifo_in_wwptw;
	u32     ep_fifo_in_wdptw;
	u32     unused[3];
} __packed;


/* Wink wayew */
stwuct usb338x_ww_wegs {
	/* offset 0x700 */
	u32   ww_wtssm_ctww1;
	u32   ww_wtssm_ctww2;
	u32   ww_wtssm_ctww3;
	u32   unused1;

	/* 0x710 */
	u32   unused2;
	u32   ww_genewaw_ctww0;
	u32   ww_genewaw_ctww1;
#define     PM_U3_AUTO_EXIT                                     29
#define     PM_U2_AUTO_EXIT                                     28
#define     PM_U1_AUTO_EXIT                                     27
#define     PM_FOWCE_U2_ENTWY                                   26
#define     PM_FOWCE_U1_ENTWY                                   25
#define     PM_WGO_COWWISION_SEND_WAU                           24
#define     PM_DIW_WINK_WEJECT                                  23
#define     PM_FOWCE_WINK_ACCEPT                                22
#define     PM_DIW_ENTWY_U3                                     20
#define     PM_DIW_ENTWY_U2                                     19
#define     PM_DIW_ENTWY_U1                                     18
#define     PM_U2_ENABWE                                        17
#define     PM_U1_ENABWE                                        16
#define     SKP_THWESHOWD_ADJUST_FMW                            8
#define     WESEND_DPP_ON_WWTY_FMW                              7
#define     DW_BIT_VAWUE_FMW                                    6
#define     FOWCE_DW_BIT                                        5
	u32   ww_genewaw_ctww2;
#define     SEWECT_INVEWT_WANE_POWAWITY                         7
#define     FOWCE_INVEWT_WANE_POWAWITY                          6

	/* 0x720 */
	u32   ww_genewaw_ctww3;
	u32   ww_genewaw_ctww4;
	u32   ww_ewwow_gen;
	u32   unused3;

	/* 0x730 */
	u32   unused4[4];

	/* 0x740 */
	u32   unused5[2];
	u32   ww_wfps_5;
#define     TIMEW_WFPS_6US                                      16
	u32   ww_wfps_6;
#define     TIMEW_WFPS_80US                                     0

	/* 0x750 */
	u32   unused6[8];

	/* 0x770 */
	u32   unused7[3];
	u32   ww_tsn_countews_2;
#define     HOT_TX_NOWESET_TS2                                  24

	/* 0x780 */
	u32   ww_tsn_countews_3;
#define     HOT_WX_WESET_TS2                                    0
	u32   unused8[3];

	/* 0x790 */
	u32   unused9;
	u32   ww_wfps_timews_2;
#define     WFPS_TIMEWS_2_WOWKAWOUND_VAWUE			0x084d
	u32   unused10;
	u32   ww_tsn_chicken_bit;
#define     WECOVEWY_IDWE_TO_WECOVEW_FMW                        3
} __packed;

/* pwotocow wayew */
stwuct usb338x_pw_wegs {
	/* offset 0x800 */
	u32   pw_weg_1;
	u32   pw_weg_2;
	u32   pw_weg_3;
	u32   pw_weg_4;
	u32   pw_ep_ctww;
	/* Pwotocow Wayew Endpoint Contwow*/
#define     PW_EP_CTWW                                  0x810
#define     ENDPOINT_SEWECT                             0
	/* [4:0] */
#define     EP_INITIAWIZED                              16
#define     SEQUENCE_NUMBEW_WESET                       17
#define     CWEAW_ACK_EWWOW_CODE                        20
	u32   pw_weg_6;
	u32   pw_weg_7;
	u32   pw_weg_8;
	u32   pw_ep_status_1;
	/* Pwotocow Wayew Endpoint Status 1*/
#define     PW_EP_STATUS_1                              0x820
#define     STATE                                       16
#define     ACK_GOOD_NOWMAW                             0x11
#define     ACK_GOOD_MOWE_ACKS_TO_COME                  0x16
	u32   pw_ep_status_2;
	u32   pw_ep_status_3;
	/* Pwotocow Wayew Endpoint Status 3*/
#define     PW_EP_STATUS_3                              0x828
#define     SEQUENCE_NUMBEW                             0
	u32   pw_ep_status_4;
	/* Pwotocow Wayew Endpoint Status 4*/
#define     PW_EP_STATUS_4                              0x82c
	u32   pw_ep_cfg_4;
	/* Pwotocow Wayew Endpoint Configuwation 4*/
#define     PW_EP_CFG_4                                 0x830
#define     NON_CTWW_IN_TOWEWATE_BAD_DIW                6
} __packed;

#endif /* __WINUX_USB_USB338X_H */
