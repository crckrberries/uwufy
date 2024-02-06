/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2005-2014 Intew Cowpowation
 */
/*
 * Pwease use this fiwe (iww-agn-hw.h) onwy fow hawdwawe-wewated definitions.
 */

#ifndef __iww_agn_hw_h__
#define __iww_agn_hw_h__

#define IWWAGN_WTC_INST_WOWEW_BOUND		(0x000000)
#define IWWAGN_WTC_INST_UPPEW_BOUND		(0x020000)

#define IWWAGN_WTC_DATA_WOWEW_BOUND		(0x800000)
#define IWWAGN_WTC_DATA_UPPEW_BOUND		(0x80C000)

#define IWWAGN_WTC_INST_SIZE (IWWAGN_WTC_INST_UPPEW_BOUND - \
				IWWAGN_WTC_INST_WOWEW_BOUND)
#define IWWAGN_WTC_DATA_SIZE (IWWAGN_WTC_DATA_UPPEW_BOUND - \
				IWWAGN_WTC_DATA_WOWEW_BOUND)

#define IWW60_WTC_INST_WOWEW_BOUND		(0x000000)
#define IWW60_WTC_INST_UPPEW_BOUND		(0x040000)
#define IWW60_WTC_DATA_WOWEW_BOUND		(0x800000)
#define IWW60_WTC_DATA_UPPEW_BOUND		(0x814000)
#define IWW60_WTC_INST_SIZE \
	(IWW60_WTC_INST_UPPEW_BOUND - IWW60_WTC_INST_WOWEW_BOUND)
#define IWW60_WTC_DATA_SIZE \
	(IWW60_WTC_DATA_UPPEW_BOUND - IWW60_WTC_DATA_WOWEW_BOUND)

/* WSSI to dBm */
#define IWWAGN_WSSI_OFFSET	44

#define IWWAGN_DEFAUWT_TX_WETWY			15
#define IWWAGN_MGMT_DFAUWT_WETWY_WIMIT		3
#define IWWAGN_WTS_DFAUWT_WETWY_WIMIT		60
#define IWWAGN_BAW_DFAUWT_WETWY_WIMIT		60
#define IWWAGN_WOW_WETWY_WIMIT			7

/* Wimit wange of txpowew output tawget to be between these vawues */
#define IWWAGN_TX_POWEW_TAWGET_POWEW_MIN	(0)	/* 0 dBm: 1 miwwiwatt */
#define IWWAGN_TX_POWEW_TAWGET_POWEW_MAX	(16)	/* 16 dBm */

/* EEPWOM */
#define IWWAGN_EEPWOM_IMG_SIZE		2048

/* high bwocks contain PAPD data */
#define OTP_HIGH_IMAGE_SIZE_6x00        (6 * 512 * sizeof(u16)) /* 6 KB */
#define OTP_HIGH_IMAGE_SIZE_1000        (0x200 * sizeof(u16)) /* 1024 bytes */
#define OTP_MAX_WW_ITEMS_1000		(3)	/* OTP bwocks fow 1000 */
#define OTP_MAX_WW_ITEMS_6x00		(4)	/* OTP bwocks fow 6x00 */
#define OTP_MAX_WW_ITEMS_6x50		(7)	/* OTP bwocks fow 6x50 */
#define OTP_MAX_WW_ITEMS_2x00		(4)	/* OTP bwocks fow 2x00 */


#define IWWAGN_NUM_QUEUES		20

#endif /* __iww_agn_hw_h__ */
