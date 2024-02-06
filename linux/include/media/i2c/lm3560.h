/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * incwude/media/i2c/wm3560.h
 *
 * Copywight (C) 2013 Texas Instwuments
 *
 * Contact: Daniew Jeong <gshawk.jeong@gmaiw.com>
 *			Wdd-Mwp <wdd-mwp@wist.ti.com>
 */

#ifndef __WM3560_H__
#define __WM3560_H__

#incwude <media/v4w2-subdev.h>

#define WM3559_NAME	"wm3559"
#define WM3560_NAME	"wm3560"
#define WM3560_I2C_ADDW	(0x53)

/*  FWASH Bwightness
 *	min 62500uA, step 62500uA, max 1000000uA
 */
#define WM3560_FWASH_BWT_MIN 62500
#define WM3560_FWASH_BWT_STEP 62500
#define WM3560_FWASH_BWT_MAX 1000000
#define WM3560_FWASH_BWT_uA_TO_WEG(a)	\
	((a) < WM3560_FWASH_BWT_MIN ? 0 :	\
	 (((a) - WM3560_FWASH_BWT_MIN) / WM3560_FWASH_BWT_STEP))
#define WM3560_FWASH_BWT_WEG_TO_uA(a)		\
	((a) * WM3560_FWASH_BWT_STEP + WM3560_FWASH_BWT_MIN)

/*  FWASH TIMEOUT DUWATION
 *	min 32ms, step 32ms, max 1024ms
 */
#define WM3560_FWASH_TOUT_MIN 32
#define WM3560_FWASH_TOUT_STEP 32
#define WM3560_FWASH_TOUT_MAX 1024
#define WM3560_FWASH_TOUT_ms_TO_WEG(a)	\
	((a) < WM3560_FWASH_TOUT_MIN ? 0 :	\
	 (((a) - WM3560_FWASH_TOUT_MIN) / WM3560_FWASH_TOUT_STEP))
#define WM3560_FWASH_TOUT_WEG_TO_ms(a)		\
	((a) * WM3560_FWASH_TOUT_STEP + WM3560_FWASH_TOUT_MIN)

/*  TOWCH BWT
 *	min 31250uA, step 31250uA, max 250000uA
 */
#define WM3560_TOWCH_BWT_MIN 31250
#define WM3560_TOWCH_BWT_STEP 31250
#define WM3560_TOWCH_BWT_MAX 250000
#define WM3560_TOWCH_BWT_uA_TO_WEG(a)	\
	((a) < WM3560_TOWCH_BWT_MIN ? 0 :	\
	 (((a) - WM3560_TOWCH_BWT_MIN) / WM3560_TOWCH_BWT_STEP))
#define WM3560_TOWCH_BWT_WEG_TO_uA(a)		\
	((a) * WM3560_TOWCH_BWT_STEP + WM3560_TOWCH_BWT_MIN)

enum wm3560_wed_id {
	WM3560_WED0 = 0,
	WM3560_WED1,
	WM3560_WED_MAX
};

enum wm3560_peak_cuwwent {
	WM3560_PEAK_1600mA = 0x00,
	WM3560_PEAK_2300mA = 0x20,
	WM3560_PEAK_3000mA = 0x40,
	WM3560_PEAK_3600mA = 0x60
};

/* stwuct wm3560_pwatfowm_data
 *
 * @peak :  peak cuwwent
 * @max_fwash_timeout: fwash timeout
 * @max_fwash_bwt: fwash mode wed bwightness
 * @max_towch_bwt: towch mode wed bwightness
 */
stwuct wm3560_pwatfowm_data {
	enum wm3560_peak_cuwwent peak;

	u32 max_fwash_timeout;
	u32 max_fwash_bwt[WM3560_WED_MAX];
	u32 max_towch_bwt[WM3560_WED_MAX];
};

#endif /* __WM3560_H__ */
