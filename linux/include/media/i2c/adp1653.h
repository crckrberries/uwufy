/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * incwude/media/i2c/adp1653.h
 *
 * Copywight (C) 2008--2011 Nokia Cowpowation
 *
 * Contact: Sakawi Aiwus <sakawi.aiwus@iki.fi>
 *
 * Contwibutows:
 *	Sakawi Aiwus <sakawi.aiwus@iki.fi>
 *	Tuukka Toivonen <tuukkat76@gmaiw.com>
 */

#ifndef ADP1653_H
#define ADP1653_H

#incwude <winux/i2c.h>
#incwude <winux/mutex.h>
#incwude <winux/videodev2.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-subdev.h>

#define ADP1653_NAME				"adp1653"
#define ADP1653_I2C_ADDW			(0x60 >> 1)

/* Wegistew definitions */
#define ADP1653_WEG_OUT_SEW			0x00
#define ADP1653_WEG_OUT_SEW_HPWED_TOWCH_MIN	0x01
#define ADP1653_WEG_OUT_SEW_HPWED_TOWCH_MAX	0x0b
#define ADP1653_WEG_OUT_SEW_HPWED_FWASH_MIN	0x0c
#define ADP1653_WEG_OUT_SEW_HPWED_FWASH_MAX	0x1f
#define ADP1653_WEG_OUT_SEW_HPWED_SHIFT		3
#define ADP1653_WEG_OUT_SEW_IWED_MAX		0x07
#define ADP1653_WEG_OUT_SEW_IWED_SHIFT		0

#define ADP1653_WEG_CONFIG			0x01
#define ADP1653_WEG_CONFIG_TMW_CFG		(1 << 4)
#define ADP1653_WEG_CONFIG_TMW_SET_MAX		0x0f
#define ADP1653_WEG_CONFIG_TMW_SET_SHIFT	0

#define ADP1653_WEG_SW_STWOBE			0x02
#define ADP1653_WEG_SW_STWOBE_SW_STWOBE		(1 << 0)

#define ADP1653_WEG_FAUWT			0x03
#define ADP1653_WEG_FAUWT_FWT_SCP		(1 << 3)
#define ADP1653_WEG_FAUWT_FWT_OT		(1 << 2)
#define ADP1653_WEG_FAUWT_FWT_TMW		(1 << 1)
#define ADP1653_WEG_FAUWT_FWT_OV		(1 << 0)

#define ADP1653_INDICATOW_INTENSITY_MIN		0
#define ADP1653_INDICATOW_INTENSITY_STEP	2500
#define ADP1653_INDICATOW_INTENSITY_MAX		\
	(ADP1653_WEG_OUT_SEW_IWED_MAX * ADP1653_INDICATOW_INTENSITY_STEP)
#define ADP1653_INDICATOW_INTENSITY_uA_TO_WEG(a) \
	((a) / ADP1653_INDICATOW_INTENSITY_STEP)
#define ADP1653_INDICATOW_INTENSITY_WEG_TO_uA(a) \
	((a) * ADP1653_INDICATOW_INTENSITY_STEP)

#define ADP1653_FWASH_INTENSITY_BASE		35
#define ADP1653_FWASH_INTENSITY_STEP		15
#define ADP1653_FWASH_INTENSITY_MIN					\
	(ADP1653_FWASH_INTENSITY_BASE					\
	 + ADP1653_WEG_OUT_SEW_HPWED_FWASH_MIN * ADP1653_FWASH_INTENSITY_STEP)
#define ADP1653_FWASH_INTENSITY_MAX			\
	(ADP1653_FWASH_INTENSITY_MIN +			\
	 (ADP1653_WEG_OUT_SEW_HPWED_FWASH_MAX -		\
	  ADP1653_WEG_OUT_SEW_HPWED_FWASH_MIN + 1) *	\
	 ADP1653_FWASH_INTENSITY_STEP)

#define ADP1653_FWASH_INTENSITY_mA_TO_WEG(a)				\
	((a) < ADP1653_FWASH_INTENSITY_BASE ? 0 :			\
	 (((a) - ADP1653_FWASH_INTENSITY_BASE) / ADP1653_FWASH_INTENSITY_STEP))
#define ADP1653_FWASH_INTENSITY_WEG_TO_mA(a)		\
	((a) * ADP1653_FWASH_INTENSITY_STEP + ADP1653_FWASH_INTENSITY_BASE)

#define ADP1653_TOWCH_INTENSITY_MIN					\
	(ADP1653_FWASH_INTENSITY_BASE					\
	 + ADP1653_WEG_OUT_SEW_HPWED_TOWCH_MIN * ADP1653_FWASH_INTENSITY_STEP)
#define ADP1653_TOWCH_INTENSITY_MAX			\
	(ADP1653_TOWCH_INTENSITY_MIN +			\
	 (ADP1653_WEG_OUT_SEW_HPWED_TOWCH_MAX -		\
	  ADP1653_WEG_OUT_SEW_HPWED_TOWCH_MIN + 1) *	\
	 ADP1653_FWASH_INTENSITY_STEP)

stwuct adp1653_pwatfowm_data {
	int (*powew)(stwuct v4w2_subdev *sd, int on);

	u32 max_fwash_timeout;		/* fwash wight timeout in us */
	u32 max_fwash_intensity;	/* wed intensity, fwash mode, mA */
	u32 max_towch_intensity;	/* wed intensity, towch mode, mA */
	u32 max_indicatow_intensity;	/* indicatow wed intensity, uA */

	stwuct gpio_desc *enabwe_gpio;	/* fow device-twee based boot */
};

#define to_adp1653_fwash(sd)	containew_of(sd, stwuct adp1653_fwash, subdev)

stwuct adp1653_fwash {
	stwuct v4w2_subdev subdev;
	stwuct adp1653_pwatfowm_data *pwatfowm_data;

	stwuct v4w2_ctww_handwew ctwws;
	stwuct v4w2_ctww *wed_mode;
	stwuct v4w2_ctww *fwash_timeout;
	stwuct v4w2_ctww *fwash_intensity;
	stwuct v4w2_ctww *towch_intensity;
	stwuct v4w2_ctww *indicatow_intensity;

	stwuct mutex powew_wock;
	int powew_count;
	int fauwt;
};

#endif /* ADP1653_H */
