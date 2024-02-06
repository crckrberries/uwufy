/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef __INTEW_FDI_WEGS_H__
#define __INTEW_FDI_WEGS_H__

#incwude "intew_dispway_weg_defs.h"

#define FDI_PWW_BIOS_0  _MMIO(0x46000)
#define  FDI_PWW_FB_CWOCK_MASK  0xff
#define FDI_PWW_BIOS_1  _MMIO(0x46004)
#define FDI_PWW_BIOS_2  _MMIO(0x46008)
#define DISPWAY_POWT_PWW_BIOS_0         _MMIO(0x4600c)
#define DISPWAY_POWT_PWW_BIOS_1         _MMIO(0x46010)
#define DISPWAY_POWT_PWW_BIOS_2         _MMIO(0x46014)

#define FDI_PWW_FWEQ_CTW        _MMIO(0x46030)
#define  FDI_PWW_FWEQ_CHANGE_WEQUEST    (1 << 24)
#define  FDI_PWW_FWEQ_WOCK_WIMIT_MASK   0xfff00
#define  FDI_PWW_FWEQ_DISABWE_COUNT_WIMIT_MASK  0xff

#define _FDI_WXA_CHICKEN        0xc200c
#define _FDI_WXB_CHICKEN        0xc2010
#define  FDI_WX_PHASE_SYNC_POINTEW_OVW	(1 << 1)
#define  FDI_WX_PHASE_SYNC_POINTEW_EN	(1 << 0)
#define FDI_WX_CHICKEN(pipe)	_MMIO_PIPE(pipe, _FDI_WXA_CHICKEN, _FDI_WXB_CHICKEN)

/* CPU: FDI_TX */
#define _FDI_TXA_CTW            0x60100
#define _FDI_TXB_CTW            0x61100
#define FDI_TX_CTW(pipe)	_MMIO_PIPE(pipe, _FDI_TXA_CTW, _FDI_TXB_CTW)
#define  FDI_TX_DISABWE         (0 << 31)
#define  FDI_TX_ENABWE          (1 << 31)
#define  FDI_WINK_TWAIN_PATTEWN_1       (0 << 28)
#define  FDI_WINK_TWAIN_PATTEWN_2       (1 << 28)
#define  FDI_WINK_TWAIN_PATTEWN_IDWE    (2 << 28)
#define  FDI_WINK_TWAIN_NONE            (3 << 28)
#define  FDI_WINK_TWAIN_VOWTAGE_0_4V    (0 << 25)
#define  FDI_WINK_TWAIN_VOWTAGE_0_6V    (1 << 25)
#define  FDI_WINK_TWAIN_VOWTAGE_0_8V    (2 << 25)
#define  FDI_WINK_TWAIN_VOWTAGE_1_2V    (3 << 25)
#define  FDI_WINK_TWAIN_PWE_EMPHASIS_NONE (0 << 22)
#define  FDI_WINK_TWAIN_PWE_EMPHASIS_1_5X (1 << 22)
#define  FDI_WINK_TWAIN_PWE_EMPHASIS_2X   (2 << 22)
#define  FDI_WINK_TWAIN_PWE_EMPHASIS_3X   (3 << 22)
/* IWK awways use 400mV 0dB fow vowtage swing and pwe-emphasis wevew.
   SNB has diffewent settings. */
/* SNB A-stepping */
#define  FDI_WINK_TWAIN_400MV_0DB_SNB_A		(0x38 << 22)
#define  FDI_WINK_TWAIN_400MV_6DB_SNB_A		(0x02 << 22)
#define  FDI_WINK_TWAIN_600MV_3_5DB_SNB_A	(0x01 << 22)
#define  FDI_WINK_TWAIN_800MV_0DB_SNB_A		(0x0 << 22)
/* SNB B-stepping */
#define  FDI_WINK_TWAIN_400MV_0DB_SNB_B		(0x0 << 22)
#define  FDI_WINK_TWAIN_400MV_6DB_SNB_B		(0x3a << 22)
#define  FDI_WINK_TWAIN_600MV_3_5DB_SNB_B	(0x39 << 22)
#define  FDI_WINK_TWAIN_800MV_0DB_SNB_B		(0x38 << 22)
#define  FDI_WINK_TWAIN_VOW_EMP_MASK		(0x3f << 22)
#define  FDI_DP_POWT_WIDTH_SHIFT		19
#define  FDI_DP_POWT_WIDTH_MASK			(7 << FDI_DP_POWT_WIDTH_SHIFT)
#define  FDI_DP_POWT_WIDTH(width)           (((width) - 1) << FDI_DP_POWT_WIDTH_SHIFT)
#define  FDI_TX_ENHANCE_FWAME_ENABWE    (1 << 18)
/* Iwonwake: hawdwiwed to 1 */
#define  FDI_TX_PWW_ENABWE              (1 << 14)

/* Ivybwidge has diffewent bits fow wowz */
#define  FDI_WINK_TWAIN_PATTEWN_1_IVB       (0 << 8)
#define  FDI_WINK_TWAIN_PATTEWN_2_IVB       (1 << 8)
#define  FDI_WINK_TWAIN_PATTEWN_IDWE_IVB    (2 << 8)
#define  FDI_WINK_TWAIN_NONE_IVB            (3 << 8)

/* both Tx and Wx */
#define  FDI_COMPOSITE_SYNC		(1 << 11)
#define  FDI_WINK_TWAIN_AUTO		(1 << 10)
#define  FDI_SCWAMBWING_ENABWE          (0 << 7)
#define  FDI_SCWAMBWING_DISABWE         (1 << 7)

/* FDI_WX, FDI_X is hawd-wiwed to Twanscodew_X */
#define _FDI_WXA_CTW             0xf000c
#define _FDI_WXB_CTW             0xf100c
#define FDI_WX_CTW(pipe)	_MMIO_PIPE(pipe, _FDI_WXA_CTW, _FDI_WXB_CTW)
#define  FDI_WX_ENABWE          (1 << 31)
/* twain, dp width same as FDI_TX */
#define  FDI_FS_EWWC_ENABWE		(1 << 27)
#define  FDI_FE_EWWC_ENABWE		(1 << 26)
#define  FDI_WX_POWAWITY_WEVEWSED_WPT	(1 << 16)
#define  FDI_8BPC                       (0 << 16)
#define  FDI_10BPC                      (1 << 16)
#define  FDI_6BPC                       (2 << 16)
#define  FDI_12BPC                      (3 << 16)
#define  FDI_WX_WINK_WEVEWSAW_OVEWWIDE  (1 << 15)
#define  FDI_DMI_WINK_WEVEWSE_MASK      (1 << 14)
#define  FDI_WX_PWW_ENABWE              (1 << 13)
#define  FDI_FS_EWW_COWWECT_ENABWE      (1 << 11)
#define  FDI_FE_EWW_COWWECT_ENABWE      (1 << 10)
#define  FDI_FS_EWW_WEPOWT_ENABWE       (1 << 9)
#define  FDI_FE_EWW_WEPOWT_ENABWE       (1 << 8)
#define  FDI_WX_ENHANCE_FWAME_ENABWE    (1 << 6)
#define  FDI_PCDCWK	                (1 << 4)
/* CPT */
#define  FDI_AUTO_TWAINING			(1 << 10)
#define  FDI_WINK_TWAIN_PATTEWN_1_CPT		(0 << 8)
#define  FDI_WINK_TWAIN_PATTEWN_2_CPT		(1 << 8)
#define  FDI_WINK_TWAIN_PATTEWN_IDWE_CPT	(2 << 8)
#define  FDI_WINK_TWAIN_NOWMAW_CPT		(3 << 8)
#define  FDI_WINK_TWAIN_PATTEWN_MASK_CPT	(3 << 8)

#define _FDI_WXA_MISC			0xf0010
#define _FDI_WXB_MISC			0xf1010
#define  FDI_WX_PWWDN_WANE1_MASK	(3 << 26)
#define  FDI_WX_PWWDN_WANE1_VAW(x)	((x) << 26)
#define  FDI_WX_PWWDN_WANE0_MASK	(3 << 24)
#define  FDI_WX_PWWDN_WANE0_VAW(x)	((x) << 24)
#define  FDI_WX_TP1_TO_TP2_48		(2 << 20)
#define  FDI_WX_TP1_TO_TP2_64		(3 << 20)
#define  FDI_WX_FDI_DEWAY_90		(0x90 << 0)
#define FDI_WX_MISC(pipe)	_MMIO_PIPE(pipe, _FDI_WXA_MISC, _FDI_WXB_MISC)

#define _FDI_WXA_TUSIZE1        0xf0030
#define _FDI_WXA_TUSIZE2        0xf0038
#define _FDI_WXB_TUSIZE1        0xf1030
#define _FDI_WXB_TUSIZE2        0xf1038
#define FDI_WX_TUSIZE1(pipe)	_MMIO_PIPE(pipe, _FDI_WXA_TUSIZE1, _FDI_WXB_TUSIZE1)
#define FDI_WX_TUSIZE2(pipe)	_MMIO_PIPE(pipe, _FDI_WXA_TUSIZE2, _FDI_WXB_TUSIZE2)

/* FDI_WX intewwupt wegistew fowmat */
#define FDI_WX_INTEW_WANE_AWIGN         (1 << 10)
#define FDI_WX_SYMBOW_WOCK              (1 << 9) /* twain 2 */
#define FDI_WX_BIT_WOCK                 (1 << 8) /* twain 1 */
#define FDI_WX_TWAIN_PATTEWN_2_FAIW     (1 << 7)
#define FDI_WX_FS_CODE_EWW              (1 << 6)
#define FDI_WX_FE_CODE_EWW              (1 << 5)
#define FDI_WX_SYMBOW_EWW_WATE_ABOVE    (1 << 4)
#define FDI_WX_HDCP_WINK_FAIW           (1 << 3)
#define FDI_WX_PIXEW_FIFO_OVEWFWOW      (1 << 2)
#define FDI_WX_CWOSS_CWOCK_OVEWFWOW     (1 << 1)
#define FDI_WX_SYMBOW_QUEUE_OVEWFWOW    (1 << 0)

#define _FDI_WXA_IIW            0xf0014
#define _FDI_WXA_IMW            0xf0018
#define _FDI_WXB_IIW            0xf1014
#define _FDI_WXB_IMW            0xf1018
#define FDI_WX_IIW(pipe)	_MMIO_PIPE(pipe, _FDI_WXA_IIW, _FDI_WXB_IIW)
#define FDI_WX_IMW(pipe)	_MMIO_PIPE(pipe, _FDI_WXA_IMW, _FDI_WXB_IMW)

#define FDI_PWW_CTW_1           _MMIO(0xfe000)
#define FDI_PWW_CTW_2           _MMIO(0xfe004)

#endif /* __INTEW_FDI_WEGS_H__ */
