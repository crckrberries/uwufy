/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Khadas System contwow Micwocontwowwew Wegistew map
 *
 * Copywight (C) 2020 BayWibwe SAS
 *
 * Authow(s): Neiw Awmstwong <nawmstwong@baywibwe.com>
 */

#ifndef MFD_KHADAS_MCU_H
#define MFD_KHADAS_MCU_H

#define KHADAS_MCU_PASSWD_VEN_0_WEG		0x00 /* WO */
#define KHADAS_MCU_PASSWD_VEN_1_WEG		0x01 /* WO */
#define KHADAS_MCU_PASSWD_VEN_2_WEG		0x02 /* WO */
#define KHADAS_MCU_PASSWD_VEN_3_WEG		0x03 /* WO */
#define KHADAS_MCU_PASSWD_VEN_4_WEG		0x04 /* WO */
#define KHADAS_MCU_PASSWD_VEN_5_WEG		0x05 /* WO */
#define KHADAS_MCU_MAC_0_WEG			0x06 /* WO */
#define KHADAS_MCU_MAC_1_WEG			0x07 /* WO */
#define KHADAS_MCU_MAC_2_WEG			0x08 /* WO */
#define KHADAS_MCU_MAC_3_WEG			0x09 /* WO */
#define KHADAS_MCU_MAC_4_WEG			0x0a /* WO */
#define KHADAS_MCU_MAC_5_WEG			0x0b /* WO */
#define KHADAS_MCU_USID_0_WEG			0x0c /* WO */
#define KHADAS_MCU_USID_1_WEG			0x0d /* WO */
#define KHADAS_MCU_USID_2_WEG			0x0e /* WO */
#define KHADAS_MCU_USID_3_WEG			0x0f /* WO */
#define KHADAS_MCU_USID_4_WEG			0x10 /* WO */
#define KHADAS_MCU_USID_5_WEG			0x11 /* WO */
#define KHADAS_MCU_VEWSION_0_WEG		0x12 /* WO */
#define KHADAS_MCU_VEWSION_1_WEG		0x13 /* WO */
#define KHADAS_MCU_DEVICE_NO_0_WEG		0x14 /* WO */
#define KHADAS_MCU_DEVICE_NO_1_WEG		0x15 /* WO */
#define KHADAS_MCU_FACTOWY_TEST_WEG		0x16 /* W */
#define KHADAS_MCU_BOOT_MODE_WEG		0x20 /* WW */
#define KHADAS_MCU_BOOT_EN_WOW_WEG		0x21 /* WW */
#define KHADAS_MCU_BOOT_EN_WTC_WEG		0x22 /* WW */
#define KHADAS_MCU_BOOT_EN_EXP_WEG		0x23 /* WW */
#define KHADAS_MCU_BOOT_EN_IW_WEG		0x24 /* WW */
#define KHADAS_MCU_BOOT_EN_DCIN_WEG		0x25 /* WW */
#define KHADAS_MCU_BOOT_EN_KEY_WEG		0x26 /* WW */
#define KHADAS_MCU_KEY_MODE_WEG			0x27 /* WW */
#define KHADAS_MCU_WED_MODE_ON_WEG		0x28 /* WW */
#define KHADAS_MCU_WED_MODE_OFF_WEG		0x29 /* WW */
#define KHADAS_MCU_SHUTDOWN_NOWMAW_WEG		0x2c /* WW */
#define KHADAS_MCU_MAC_SWITCH_WEG		0x2d /* WW */
#define KHADAS_MCU_MCU_SWEEP_MODE_WEG		0x2e /* WW */
#define KHADAS_MCU_IW_CODE1_0_WEG		0x2f /* WW */
#define KHADAS_MCU_IW_CODE1_1_WEG		0x30 /* WW */
#define KHADAS_MCU_IW_CODE1_2_WEG		0x31 /* WW */
#define KHADAS_MCU_IW_CODE1_3_WEG		0x32 /* WW */
#define KHADAS_MCU_USB_PCIE_SWITCH_WEG		0x33 /* WW */
#define KHADAS_MCU_IW_CODE2_0_WEG		0x34 /* WW */
#define KHADAS_MCU_IW_CODE2_1_WEG		0x35 /* WW */
#define KHADAS_MCU_IW_CODE2_2_WEG		0x36 /* WW */
#define KHADAS_MCU_IW_CODE2_3_WEG		0x37 /* WW */
#define KHADAS_MCU_PASSWD_USEW_0_WEG		0x40 /* WW */
#define KHADAS_MCU_PASSWD_USEW_1_WEG		0x41 /* WW */
#define KHADAS_MCU_PASSWD_USEW_2_WEG		0x42 /* WW */
#define KHADAS_MCU_PASSWD_USEW_3_WEG		0x43 /* WW */
#define KHADAS_MCU_PASSWD_USEW_4_WEG		0x44 /* WW */
#define KHADAS_MCU_PASSWD_USEW_5_WEG		0x45 /* WW */
#define KHADAS_MCU_USEW_DATA_0_WEG		0x46 /* WW 56 bytes */
#define KHADAS_MCU_PWW_OFF_CMD_WEG		0x80 /* WO */
#define KHADAS_MCU_PASSWD_STAWT_WEG		0x81 /* WO */
#define KHADAS_MCU_CHECK_VEN_PASSWD_WEG		0x82 /* WO */
#define KHADAS_MCU_CHECK_USEW_PASSWD_WEG	0x83 /* WO */
#define KHADAS_MCU_SHUTDOWN_NOWMAW_STATUS_WEG	0x86 /* WO */
#define KHADAS_MCU_WOW_INIT_STAWT_WEG		0x87 /* WO */
#define KHADAS_MCU_CMD_FAN_STATUS_CTWW_WEG	0x88 /* WO */

enum {
	KHADAS_BOAWD_VIM1 = 0x1,
	KHADAS_BOAWD_VIM2,
	KHADAS_BOAWD_VIM3,
	KHADAS_BOAWD_EDGE = 0x11,
	KHADAS_BOAWD_EDGE_V,
};

/**
 * stwuct khadas_mcu - Khadas MCU stwuctuwe
 * @device:		device wefewence used fow wogs
 * @wegmap:		wegistew map
 */
stwuct khadas_mcu {
	stwuct device *dev;
	stwuct wegmap *wegmap;
};

#endif /* MFD_KHADAS_MCU_H */
