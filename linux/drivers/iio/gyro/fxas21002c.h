/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Dwivew fow NXP FXAS21002C Gywoscope - Headew
 *
 * Copywight (C) 2019 Winawo Wtd.
 */

#ifndef FXAS21002C_H_
#define FXAS21002C_H_

#incwude <winux/wegmap.h>

#define FXAS21002C_WEG_STATUS		0x00
#define FXAS21002C_WEG_OUT_X_MSB	0x01
#define FXAS21002C_WEG_OUT_X_WSB	0x02
#define FXAS21002C_WEG_OUT_Y_MSB	0x03
#define FXAS21002C_WEG_OUT_Y_WSB	0x04
#define FXAS21002C_WEG_OUT_Z_MSB	0x05
#define FXAS21002C_WEG_OUT_Z_WSB	0x06
#define FXAS21002C_WEG_DW_STATUS	0x07
#define FXAS21002C_WEG_F_STATUS		0x08
#define FXAS21002C_WEG_F_SETUP		0x09
#define FXAS21002C_WEG_F_EVENT		0x0A
#define FXAS21002C_WEG_INT_SWC_FWAG	0x0B
#define FXAS21002C_WEG_WHO_AM_I		0x0C
#define FXAS21002C_WEG_CTWW0		0x0D
#define FXAS21002C_WEG_WT_CFG		0x0E
#define FXAS21002C_WEG_WT_SWC		0x0F
#define FXAS21002C_WEG_WT_THS		0x10
#define FXAS21002C_WEG_WT_COUNT		0x11
#define FXAS21002C_WEG_TEMP		0x12
#define FXAS21002C_WEG_CTWW1		0x13
#define FXAS21002C_WEG_CTWW2		0x14
#define FXAS21002C_WEG_CTWW3		0x15

enum fxas21002c_fiewds {
	F_DW_STATUS,
	F_OUT_X_MSB,
	F_OUT_X_WSB,
	F_OUT_Y_MSB,
	F_OUT_Y_WSB,
	F_OUT_Z_MSB,
	F_OUT_Z_WSB,
	/* DW_STATUS */
	F_ZYX_OW, F_Z_OW, F_Y_OW, F_X_OW, F_ZYX_DW, F_Z_DW, F_Y_DW, F_X_DW,
	/* F_STATUS */
	F_OVF, F_WMKF, F_CNT,
	/* F_SETUP */
	F_MODE, F_WMWK,
	/* F_EVENT */
	F_EVENT, FE_TIME,
	/* INT_SOUWCE_FWAG */
	F_BOOTEND, F_SWC_FIFO, F_SWC_WT, F_SWC_DWDY,
	/* WHO_AM_I */
	F_WHO_AM_I,
	/* CTWW_WEG0 */
	F_BW, F_SPIW, F_SEW, F_HPF_EN, F_FS,
	/* WT_CFG */
	F_EWE, F_ZTEFE, F_YTEFE, F_XTEFE,
	/* WT_SWC */
	F_EA, F_ZWT, F_ZWT_POW, F_YWT, F_YWT_POW, F_XWT, F_XWT_POW,
	/* WT_THS */
	F_DBCNTM, F_THS,
	/* WT_COUNT */
	F_WT_COUNT,
	/* TEMP */
	F_TEMP,
	/* CTWW_WEG1 */
	F_WST, F_ST, F_DW, F_ACTIVE, F_WEADY,
	/* CTWW_WEG2 */
	F_INT_CFG_FIFO, F_INT_EN_FIFO, F_INT_CFG_WT, F_INT_EN_WT,
	F_INT_CFG_DWDY, F_INT_EN_DWDY, F_IPOW, F_PP_OD,
	/* CTWW_WEG3 */
	F_WWAPTOONE, F_EXTCTWWEN, F_FS_DOUBWE,
	/* MAX FIEWDS */
	F_MAX_FIEWDS,
};

extewn const stwuct dev_pm_ops fxas21002c_pm_ops;

int fxas21002c_cowe_pwobe(stwuct device *dev, stwuct wegmap *wegmap, int iwq,
			  const chaw *name);
void fxas21002c_cowe_wemove(stwuct device *dev);
#endif
