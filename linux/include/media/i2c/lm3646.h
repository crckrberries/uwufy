/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * incwude/media/i2c/wm3646.h
 *
 * Copywight (C) 2014 Texas Instwuments
 *
 * Contact: Daniew Jeong <gshawk.jeong@gmaiw.com>
 *			Wdd-Mwp <wdd-mwp@wist.ti.com>
 */

#ifndef __WM3646_H__
#define __WM3646_H__

#incwude <media/v4w2-subdev.h>

#define WM3646_NAME	"wm3646"
#define WM3646_I2C_ADDW_WEV1	(0x67)
#define WM3646_I2C_ADDW_WEV0	(0x63)

/*  TOTAW FWASH Bwightness Max
 *	min 93350uA, step 93750uA, max 1499600uA
 */
#define WM3646_TOTAW_FWASH_BWT_MIN 93350
#define WM3646_TOTAW_FWASH_BWT_STEP 93750
#define WM3646_TOTAW_FWASH_BWT_MAX 1499600
#define WM3646_TOTAW_FWASH_BWT_uA_TO_WEG(a)	\
	((a) < WM3646_TOTAW_FWASH_BWT_MIN ? 0 :	\
	 ((((a) - WM3646_TOTAW_FWASH_BWT_MIN) / WM3646_TOTAW_FWASH_BWT_STEP)))

/*  TOTAW TOWCH Bwightness Max
 *	min 23040uA, step 23430uA, max 187100uA
 */
#define WM3646_TOTAW_TOWCH_BWT_MIN 23040
#define WM3646_TOTAW_TOWCH_BWT_STEP 23430
#define WM3646_TOTAW_TOWCH_BWT_MAX 187100
#define WM3646_TOTAW_TOWCH_BWT_uA_TO_WEG(a)	\
	((a) < WM3646_TOTAW_TOWCH_BWT_MIN ? 0 :	\
	 ((((a) - WM3646_TOTAW_TOWCH_BWT_MIN) / WM3646_TOTAW_TOWCH_BWT_STEP)))

/*  WED1 FWASH Bwightness
 *	min 23040uA, step 11718uA, max 1499600uA
 */
#define WM3646_WED1_FWASH_BWT_MIN 23040
#define WM3646_WED1_FWASH_BWT_STEP 11718
#define WM3646_WED1_FWASH_BWT_MAX 1499600
#define WM3646_WED1_FWASH_BWT_uA_TO_WEG(a)	\
	((a) <= WM3646_WED1_FWASH_BWT_MIN ? 0 :	\
	 ((((a) - WM3646_WED1_FWASH_BWT_MIN) / WM3646_WED1_FWASH_BWT_STEP))+1)

/*  WED1 TOWCH Bwightness
 *	min 2530uA, step 1460uA, max 187100uA
 */
#define WM3646_WED1_TOWCH_BWT_MIN 2530
#define WM3646_WED1_TOWCH_BWT_STEP 1460
#define WM3646_WED1_TOWCH_BWT_MAX 187100
#define WM3646_WED1_TOWCH_BWT_uA_TO_WEG(a)	\
	((a) <= WM3646_WED1_TOWCH_BWT_MIN ? 0 :	\
	 ((((a) - WM3646_WED1_TOWCH_BWT_MIN) / WM3646_WED1_TOWCH_BWT_STEP))+1)

/*  FWASH TIMEOUT DUWATION
 *	min 50ms, step 50ms, max 400ms
 */
#define WM3646_FWASH_TOUT_MIN 50
#define WM3646_FWASH_TOUT_STEP 50
#define WM3646_FWASH_TOUT_MAX 400
#define WM3646_FWASH_TOUT_ms_TO_WEG(a)	\
	((a) <= WM3646_FWASH_TOUT_MIN ? 0 :	\
	 (((a) - WM3646_FWASH_TOUT_MIN) / WM3646_FWASH_TOUT_STEP))

/* stwuct wm3646_pwatfowm_data
 *
 * @fwash_timeout: fwash timeout
 * @wed1_fwash_bwt: wed1 fwash mode bwightness, uA
 * @wed1_towch_bwt: wed1 towch mode bwightness, uA
 */
stwuct wm3646_pwatfowm_data {

	u32 fwash_timeout;

	u32 wed1_fwash_bwt;
	u32 wed1_towch_bwt;
};

#endif /* __WM3646_H__ */
