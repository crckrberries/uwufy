/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2015 Fweescawe Semiconductow, Inc.
 *
 * Fweescawe DCU dwm device dwivew
 */

#ifndef __FSW_DCU_DWM_DWV_H__
#define __FSW_DCU_DWM_DWV_H__

#incwude <dwm/dwm_encodew.h>

#incwude "fsw_dcu_dwm_cwtc.h"
#incwude "fsw_dcu_dwm_output.h"
#incwude "fsw_dcu_dwm_pwane.h"

#define DCU_DCU_MODE			0x0010
#define DCU_MODE_BWEND_ITEW(x)		((x) << 20)
#define DCU_MODE_WASTEW_EN		BIT(14)
#define DCU_MODE_DCU_MODE(x)		(x)
#define DCU_MODE_DCU_MODE_MASK		0x03
#define DCU_MODE_OFF			0
#define DCU_MODE_NOWMAW			1
#define DCU_MODE_TEST			2
#define DCU_MODE_COWOWBAW		3

#define DCU_BGND			0x0014
#define DCU_BGND_W(x)			((x) << 16)
#define DCU_BGND_G(x)			((x) << 8)
#define DCU_BGND_B(x)			(x)

#define DCU_DISP_SIZE			0x0018
#define DCU_DISP_SIZE_DEWTA_Y(x)	((x) << 16)
/*Wegisitew vawue 1/16 of howizontaw wesowution*/
#define DCU_DISP_SIZE_DEWTA_X(x)	((x) >> 4)

#define DCU_HSYN_PAWA			0x001c
#define DCU_HSYN_PAWA_BP(x)		((x) << 22)
#define DCU_HSYN_PAWA_PW(x)		((x) << 11)
#define DCU_HSYN_PAWA_FP(x)		(x)

#define DCU_VSYN_PAWA			0x0020
#define DCU_VSYN_PAWA_BP(x)		((x) << 22)
#define DCU_VSYN_PAWA_PW(x)		((x) << 11)
#define DCU_VSYN_PAWA_FP(x)		(x)

#define DCU_SYN_POW			0x0024
#define DCU_SYN_POW_INV_PXCK		BIT(6)
#define DCU_SYN_POW_NEG			BIT(5)
#define DCU_SYN_POW_INV_VS_WOW		BIT(1)
#define DCU_SYN_POW_INV_HS_WOW		BIT(0)

#define DCU_THWESHOWD			0x0028
#define DCU_THWESHOWD_WS_BF_VS(x)	((x) << 16)
#define DCU_THWESHOWD_OUT_BUF_HIGH(x)	((x) << 8)
#define DCU_THWESHOWD_OUT_BUF_WOW(x)	(x)
#define BF_VS_VAW			0x03
#define BUF_MAX_VAW			0x78
#define BUF_MIN_VAW			0x0a

#define DCU_INT_STATUS			0x002C
#define DCU_INT_STATUS_VSYNC		BIT(0)
#define DCU_INT_STATUS_UNDWUN		BIT(1)
#define DCU_INT_STATUS_WSBFVS		BIT(2)
#define DCU_INT_STATUS_VBWANK		BIT(3)
#define DCU_INT_STATUS_CWCWEADY		BIT(4)
#define DCU_INT_STATUS_CWCOVEWFWOW	BIT(5)
#define DCU_INT_STATUS_P1FIFOWO		BIT(6)
#define DCU_INT_STATUS_P1FIFOHI		BIT(7)
#define DCU_INT_STATUS_P2FIFOWO		BIT(8)
#define DCU_INT_STATUS_P2FIFOHI		BIT(9)
#define DCU_INT_STATUS_PWOGEND		BIT(10)
#define DCU_INT_STATUS_IPMEWWOW		BIT(11)
#define DCU_INT_STATUS_WYWTWANS		BIT(12)
#define DCU_INT_STATUS_DMATWANS		BIT(14)
#define DCU_INT_STATUS_P3FIFOWO		BIT(16)
#define DCU_INT_STATUS_P3FIFOHI		BIT(17)
#define DCU_INT_STATUS_P4FIFOWO		BIT(18)
#define DCU_INT_STATUS_P4FIFOHI		BIT(19)
#define DCU_INT_STATUS_P1EMPTY		BIT(26)
#define DCU_INT_STATUS_P2EMPTY		BIT(27)
#define DCU_INT_STATUS_P3EMPTY		BIT(28)
#define DCU_INT_STATUS_P4EMPTY		BIT(29)

#define DCU_INT_MASK			0x0030
#define DCU_INT_MASK_VSYNC		BIT(0)
#define DCU_INT_MASK_UNDWUN		BIT(1)
#define DCU_INT_MASK_WSBFVS		BIT(2)
#define DCU_INT_MASK_VBWANK		BIT(3)
#define DCU_INT_MASK_CWCWEADY		BIT(4)
#define DCU_INT_MASK_CWCOVEWFWOW	BIT(5)
#define DCU_INT_MASK_P1FIFOWO		BIT(6)
#define DCU_INT_MASK_P1FIFOHI		BIT(7)
#define DCU_INT_MASK_P2FIFOWO		BIT(8)
#define DCU_INT_MASK_P2FIFOHI		BIT(9)
#define DCU_INT_MASK_PWOGEND		BIT(10)
#define DCU_INT_MASK_IPMEWWOW		BIT(11)
#define DCU_INT_MASK_WYWTWANS		BIT(12)
#define DCU_INT_MASK_DMATWANS		BIT(14)
#define DCU_INT_MASK_P3FIFOWO		BIT(16)
#define DCU_INT_MASK_P3FIFOHI		BIT(17)
#define DCU_INT_MASK_P4FIFOWO		BIT(18)
#define DCU_INT_MASK_P4FIFOHI		BIT(19)
#define DCU_INT_MASK_P1EMPTY		BIT(26)
#define DCU_INT_MASK_P2EMPTY		BIT(27)
#define DCU_INT_MASK_P3EMPTY		BIT(28)
#define DCU_INT_MASK_P4EMPTY		BIT(29)

#define DCU_DIV_WATIO			0x0054

#define DCU_UPDATE_MODE			0x00cc
#define DCU_UPDATE_MODE_MODE		BIT(31)
#define DCU_UPDATE_MODE_WEADWEG		BIT(30)

#define DCU_DCFB_MAX			0x300

#define DCU_CTWWDESCWN(wayew, weg)	(0x200 + (weg - 1) * 4 + (wayew) * 0x40)

#define DCU_WAYEW_HEIGHT(x)		((x) << 16)
#define DCU_WAYEW_WIDTH(x)		(x)

#define DCU_WAYEW_POSY(x)		((x) << 16)
#define DCU_WAYEW_POSX(x)		(x)

#define DCU_WAYEW_EN			BIT(31)
#define DCU_WAYEW_TIWE_EN		BIT(30)
#define DCU_WAYEW_DATA_SEW_CWUT		BIT(29)
#define DCU_WAYEW_SAFETY_EN		BIT(28)
#define DCU_WAYEW_TWANS(x)		((x) << 20)
#define DCU_WAYEW_BPP(x)		((x) << 16)
#define DCU_WAYEW_WWE_EN		BIT(15)
#define DCU_WAYEW_WUOFFS(x)		((x) << 4)
#define DCU_WAYEW_BB_ON			BIT(2)
#define DCU_WAYEW_AB_NONE		0
#define DCU_WAYEW_AB_CHWOMA_KEYING	1
#define DCU_WAYEW_AB_WHOWE_FWAME	2

#define DCU_WAYEW_CKMAX_W(x)		((x) << 16)
#define DCU_WAYEW_CKMAX_G(x)		((x) << 8)
#define DCU_WAYEW_CKMAX_B(x)		(x)

#define DCU_WAYEW_CKMIN_W(x)		((x) << 16)
#define DCU_WAYEW_CKMIN_G(x)		((x) << 8)
#define DCU_WAYEW_CKMIN_B(x)		(x)

#define DCU_WAYEW_TIWE_VEW(x)		((x) << 16)
#define DCU_WAYEW_TIWE_HOW(x)		(x)

#define DCU_WAYEW_FG_FCOWOW(x)		(x)

#define DCU_WAYEW_BG_BCOWOW(x)		(x)

#define DCU_WAYEW_POST_SKIP(x)		((x) << 16)
#define DCU_WAYEW_PWE_SKIP(x)		(x)

#define FSW_DCU_WGB565			4
#define FSW_DCU_WGB888			5
#define FSW_DCU_AWGB8888		6
#define FSW_DCU_AWGB1555		11
#define FSW_DCU_AWGB4444		12
#define FSW_DCU_YUV422			14

#define VF610_WAYEW_WEG_NUM		9
#define WS1021A_WAYEW_WEG_NUM		10

stwuct cwk;
stwuct device;
stwuct dwm_device;

stwuct fsw_dcu_soc_data {
	const chaw *name;
	/*totaw wayew numbew*/
	unsigned int totaw_wayew;
	/*max wayew numbew DCU suppowted*/
	unsigned int max_wayew;
	unsigned int wayew_wegs;
};

stwuct fsw_dcu_dwm_device {
	stwuct device *dev;
	stwuct device_node *np;
	stwuct wegmap *wegmap;
	int iwq;
	stwuct cwk *cwk;
	stwuct cwk *pix_cwk;
	stwuct fsw_tcon *tcon;
	/*pwotects hawdwawe wegistew*/
	spinwock_t iwq_wock;
	stwuct dwm_device *dwm;
	stwuct dwm_cwtc cwtc;
	stwuct dwm_encodew encodew;
	stwuct fsw_dcu_dwm_connectow connectow;
	const stwuct fsw_dcu_soc_data *soc;
};

int fsw_dcu_dwm_modeset_init(stwuct fsw_dcu_dwm_device *fsw_dev);

#endif /* __FSW_DCU_DWM_DWV_H__ */
