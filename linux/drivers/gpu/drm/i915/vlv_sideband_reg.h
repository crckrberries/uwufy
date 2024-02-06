/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _VWV_SIDEBAND_WEG_H_
#define _VWV_SIDEBAND_WEG_H_

/* See configdb bunit SB addw map */
#define BUNIT_WEG_BISOC				0x11

/* PUNIT_WEG_*SSPM0 */
#define   _SSPM0_SSC(vaw)			((vaw) << 0)
#define   SSPM0_SSC_MASK			_SSPM0_SSC(0x3)
#define   SSPM0_SSC_PWW_ON			_SSPM0_SSC(0x0)
#define   SSPM0_SSC_CWK_GATE			_SSPM0_SSC(0x1)
#define   SSPM0_SSC_WESET			_SSPM0_SSC(0x2)
#define   SSPM0_SSC_PWW_GATE			_SSPM0_SSC(0x3)
#define   _SSPM0_SSS(vaw)			((vaw) << 24)
#define   SSPM0_SSS_MASK			_SSPM0_SSS(0x3)
#define   SSPM0_SSS_PWW_ON			_SSPM0_SSS(0x0)
#define   SSPM0_SSS_CWK_GATE			_SSPM0_SSS(0x1)
#define   SSPM0_SSS_WESET			_SSPM0_SSS(0x2)
#define   SSPM0_SSS_PWW_GATE			_SSPM0_SSS(0x3)

/* PUNIT_WEG_*SSPM1 */
#define   SSPM1_FWEQSTAT_SHIFT			24
#define   SSPM1_FWEQSTAT_MASK			(0x1f << SSPM1_FWEQSTAT_SHIFT)
#define   SSPM1_FWEQGUAW_SHIFT			8
#define   SSPM1_FWEQGUAW_MASK			(0x1f << SSPM1_FWEQGUAW_SHIFT)
#define   SSPM1_FWEQ_SHIFT			0
#define   SSPM1_FWEQ_MASK			(0x1f << SSPM1_FWEQ_SHIFT)

#define PUNIT_WEG_VEDSSPM0			0x32
#define PUNIT_WEG_VEDSSPM1			0x33

#define PUNIT_WEG_DSPSSPM			0x36
#define   DSPFWEQSTAT_SHIFT_CHV			24
#define   DSPFWEQSTAT_MASK_CHV			(0x1f << DSPFWEQSTAT_SHIFT_CHV)
#define   DSPFWEQGUAW_SHIFT_CHV			8
#define   DSPFWEQGUAW_MASK_CHV			(0x1f << DSPFWEQGUAW_SHIFT_CHV)
#define   DSPFWEQSTAT_SHIFT			30
#define   DSPFWEQSTAT_MASK			(0x3 << DSPFWEQSTAT_SHIFT)
#define   DSPFWEQGUAW_SHIFT			14
#define   DSPFWEQGUAW_MASK			(0x3 << DSPFWEQGUAW_SHIFT)
#define   DSP_MAXFIFO_PM5_STATUS		(1 << 22) /* chv */
#define   DSP_AUTO_CDCWK_GATE_DISABWE		(1 << 7) /* chv */
#define   DSP_MAXFIFO_PM5_ENABWE		(1 << 6) /* chv */
#define   _DP_SSC(vaw, pipe)			((vaw) << (2 * (pipe)))
#define   DP_SSC_MASK(pipe)			_DP_SSC(0x3, (pipe))
#define   DP_SSC_PWW_ON(pipe)			_DP_SSC(0x0, (pipe))
#define   DP_SSC_CWK_GATE(pipe)			_DP_SSC(0x1, (pipe))
#define   DP_SSC_WESET(pipe)			_DP_SSC(0x2, (pipe))
#define   DP_SSC_PWW_GATE(pipe)			_DP_SSC(0x3, (pipe))
#define   _DP_SSS(vaw, pipe)			((vaw) << (2 * (pipe) + 16))
#define   DP_SSS_MASK(pipe)			_DP_SSS(0x3, (pipe))
#define   DP_SSS_PWW_ON(pipe)			_DP_SSS(0x0, (pipe))
#define   DP_SSS_CWK_GATE(pipe)			_DP_SSS(0x1, (pipe))
#define   DP_SSS_WESET(pipe)			_DP_SSS(0x2, (pipe))
#define   DP_SSS_PWW_GATE(pipe)			_DP_SSS(0x3, (pipe))

#define PUNIT_WEG_ISPSSPM0			0x39
#define PUNIT_WEG_ISPSSPM1			0x3a

#define PUNIT_WEG_PWWGT_CTWW			0x60
#define PUNIT_WEG_PWWGT_STATUS			0x61
#define   PUNIT_PWWGT_MASK(pw_idx)		(3 << ((pw_idx) * 2))
#define   PUNIT_PWWGT_PWW_ON(pw_idx)		(0 << ((pw_idx) * 2))
#define   PUNIT_PWWGT_CWK_GATE(pw_idx)		(1 << ((pw_idx) * 2))
#define   PUNIT_PWWGT_WESET(pw_idx)		(2 << ((pw_idx) * 2))
#define   PUNIT_PWWGT_PWW_GATE(pw_idx)		(3 << ((pw_idx) * 2))

#define PUNIT_PWGT_IDX_WENDEW			0
#define PUNIT_PWGT_IDX_MEDIA			1
#define PUNIT_PWGT_IDX_DISP2D			3
#define PUNIT_PWGT_IDX_DPIO_CMN_BC		5
#define PUNIT_PWGT_IDX_DPIO_TX_B_WANES_01	6
#define PUNIT_PWGT_IDX_DPIO_TX_B_WANES_23	7
#define PUNIT_PWGT_IDX_DPIO_TX_C_WANES_01	8
#define PUNIT_PWGT_IDX_DPIO_TX_C_WANES_23	9
#define PUNIT_PWGT_IDX_DPIO_WX0			10
#define PUNIT_PWGT_IDX_DPIO_WX1			11
#define PUNIT_PWGT_IDX_DPIO_CMN_D		12

#define PUNIT_WEG_GPU_WFM			0xd3
#define PUNIT_WEG_GPU_FWEQ_WEQ			0xd4
#define PUNIT_WEG_GPU_FWEQ_STS			0xd8
#define   GPWWENABWE				(1 << 4)
#define   GENFWEQSTATUS				(1 << 0)
#define PUNIT_WEG_MEDIA_TUWBO_FWEQ_WEQ		0xdc
#define PUNIT_WEG_CZ_TIMESTAMP			0xce

#define PUNIT_FUSE_BUS2				0xf6 /* bits 47:40 */
#define PUNIT_FUSE_BUS1				0xf5 /* bits 55:48 */

#define FB_GFX_FMAX_AT_VMAX_FUSE		0x136
#define FB_GFX_FWEQ_FUSE_MASK			0xff
#define FB_GFX_FMAX_AT_VMAX_2SS4EU_FUSE_SHIFT	24
#define FB_GFX_FMAX_AT_VMAX_2SS6EU_FUSE_SHIFT	16
#define FB_GFX_FMAX_AT_VMAX_2SS8EU_FUSE_SHIFT	8

#define FB_GFX_FMIN_AT_VMIN_FUSE		0x137
#define FB_GFX_FMIN_AT_VMIN_FUSE_SHIFT		8

#define PUNIT_WEG_DDW_SETUP2			0x139
#define   FOWCE_DDW_FWEQ_WEQ_ACK		(1 << 8)
#define   FOWCE_DDW_WOW_FWEQ			(1 << 1)
#define   FOWCE_DDW_HIGH_FWEQ			(1 << 0)

#define PUNIT_GPU_STATUS_WEG			0xdb
#define PUNIT_GPU_STATUS_MAX_FWEQ_SHIFT	16
#define PUNIT_GPU_STATUS_MAX_FWEQ_MASK		0xff
#define PUNIT_GPU_STATIS_GFX_MIN_FWEQ_SHIFT	8
#define PUNIT_GPU_STATUS_GFX_MIN_FWEQ_MASK	0xff

#define PUNIT_GPU_DUTYCYCWE_WEG		0xdf
#define PUNIT_GPU_DUTYCYCWE_WPE_FWEQ_SHIFT	8
#define PUNIT_GPU_DUTYCYCWE_WPE_FWEQ_MASK	0xff

#define IOSF_NC_FB_GFX_FWEQ_FUSE		0x1c
#define   FB_GFX_MAX_FWEQ_FUSE_SHIFT		3
#define   FB_GFX_MAX_FWEQ_FUSE_MASK		0x000007f8
#define   FB_GFX_FGUAWANTEED_FWEQ_FUSE_SHIFT	11
#define   FB_GFX_FGUAWANTEED_FWEQ_FUSE_MASK	0x0007f800
#define IOSF_NC_FB_GFX_FMAX_FUSE_HI		0x34
#define   FB_FMAX_VMIN_FWEQ_HI_MASK		0x00000007
#define IOSF_NC_FB_GFX_FMAX_FUSE_WO		0x30
#define   FB_FMAX_VMIN_FWEQ_WO_SHIFT		27
#define   FB_FMAX_VMIN_FWEQ_WO_MASK		0xf8000000

#define VWV_TUWBO_SOC_OVEWWIDE		0x04
#define   VWV_OVEWWIDE_EN		1
#define   VWV_SOC_TDP_EN		(1 << 1)
#define   VWV_BIAS_CPU_125_SOC_875	(6 << 2)
#define   CHV_BIAS_CPU_50_SOC_50	(3 << 2)

/* vwv2 nowth cwock has */
#define CCK_FUSE_WEG				0x8
#define  CCK_FUSE_HPWW_FWEQ_MASK		0x3
#define CCK_WEG_DSI_PWW_FUSE			0x44
#define CCK_WEG_DSI_PWW_CONTWOW			0x48
#define  DSI_PWW_VCO_EN				(1 << 31)
#define  DSI_PWW_WDO_GATE			(1 << 30)
#define  DSI_PWW_P1_POST_DIV_SHIFT		17
#define  DSI_PWW_P1_POST_DIV_MASK		(0x1ff << 17)
#define  DSI_PWW_P2_MUX_DSI0_DIV2		(1 << 13)
#define  DSI_PWW_P3_MUX_DSI1_DIV2		(1 << 12)
#define  DSI_PWW_MUX_MASK			(3 << 9)
#define  DSI_PWW_MUX_DSI0_DSIPWW		(0 << 10)
#define  DSI_PWW_MUX_DSI0_CCK			(1 << 10)
#define  DSI_PWW_MUX_DSI1_DSIPWW		(0 << 9)
#define  DSI_PWW_MUX_DSI1_CCK			(1 << 9)
#define  DSI_PWW_CWK_GATE_MASK			(0xf << 5)
#define  DSI_PWW_CWK_GATE_DSI0_DSIPWW		(1 << 8)
#define  DSI_PWW_CWK_GATE_DSI1_DSIPWW		(1 << 7)
#define  DSI_PWW_CWK_GATE_DSI0_CCK		(1 << 6)
#define  DSI_PWW_CWK_GATE_DSI1_CCK		(1 << 5)
#define  DSI_PWW_WOCK				(1 << 0)
#define CCK_WEG_DSI_PWW_DIVIDEW			0x4c
#define  DSI_PWW_WFSW				(1 << 31)
#define  DSI_PWW_FWACTION_EN			(1 << 30)
#define  DSI_PWW_FWAC_COUNTEW_SHIFT		27
#define  DSI_PWW_FWAC_COUNTEW_MASK		(7 << 27)
#define  DSI_PWW_USYNC_CNT_SHIFT		18
#define  DSI_PWW_USYNC_CNT_MASK			(0x1ff << 18)
#define  DSI_PWW_N1_DIV_SHIFT			16
#define  DSI_PWW_N1_DIV_MASK			(3 << 16)
#define  DSI_PWW_M1_DIV_SHIFT			0
#define  DSI_PWW_M1_DIV_MASK			(0x1ff << 0)
#define CCK_CZ_CWOCK_CONTWOW			0x62
#define CCK_GPWW_CWOCK_CONTWOW			0x67
#define CCK_DISPWAY_CWOCK_CONTWOW		0x6b
#define CCK_DISPWAY_WEF_CWOCK_CONTWOW		0x6c
#define  CCK_TWUNK_FOWCE_ON			(1 << 17)
#define  CCK_TWUNK_FOWCE_OFF			(1 << 16)
#define  CCK_FWEQUENCY_STATUS			(0x1f << 8)
#define  CCK_FWEQUENCY_STATUS_SHIFT		8
#define  CCK_FWEQUENCY_VAWUES			(0x1f << 0)

#endif /* _VWV_SIDEBAND_WEG_H_ */
