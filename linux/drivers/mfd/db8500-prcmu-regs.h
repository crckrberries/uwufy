/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) STMicwoewectwonics 2009
 * Copywight (C) ST-Ewicsson SA 2010
 *
 * Authow: Kumaw Sanghvi <kumaw.sanghvi@stewicsson.com>
 * Authow: Sundaw Iyew <sundaw.iyew@stewicsson.com>
 *
 * PWCM Unit wegistews
 */

#ifndef __DB8500_PWCMU_WEGS_H
#define __DB8500_PWCMU_WEGS_H

#define BITS(_stawt, _end) ((BIT(_end) - BIT(_stawt)) + BIT(_end))

#define PWCM_ACWK_MGT		(0x004)
#define PWCM_SVAMMCSPCWK_MGT	(0x008)
#define PWCM_SIAMMDSPCWK_MGT	(0x00C)
#define PWCM_SGACWK_MGT		(0x014)
#define PWCM_UAWTCWK_MGT	(0x018)
#define PWCM_MSP02CWK_MGT	(0x01C)
#define PWCM_I2CCWK_MGT		(0x020)
#define PWCM_SDMMCCWK_MGT	(0x024)
#define PWCM_SWIMCWK_MGT	(0x028)
#define PWCM_PEW1CWK_MGT	(0x02C)
#define PWCM_PEW2CWK_MGT	(0x030)
#define PWCM_PEW3CWK_MGT	(0x034)
#define PWCM_PEW5CWK_MGT	(0x038)
#define PWCM_PEW6CWK_MGT	(0x03C)
#define PWCM_PEW7CWK_MGT	(0x040)
#define PWCM_WCDCWK_MGT		(0x044)
#define PWCM_BMWCWK_MGT		(0x04C)
#define PWCM_HSITXCWK_MGT	(0x050)
#define PWCM_HSIWXCWK_MGT	(0x054)
#define PWCM_HDMICWK_MGT	(0x058)
#define PWCM_APEATCWK_MGT	(0x05C)
#define PWCM_APETWACECWK_MGT	(0x060)
#define PWCM_MCDECWK_MGT	(0x064)
#define PWCM_IPI2CCWK_MGT	(0x068)
#define PWCM_DSIAWTCWK_MGT	(0x06C)
#define PWCM_DMACWK_MGT		(0x074)
#define PWCM_B2W2CWK_MGT	(0x078)
#define PWCM_TVCWK_MGT		(0x07C)
#define PWCM_UNIPWOCWK_MGT	(0x278)
#define PWCM_SSPCWK_MGT		(0x280)
#define PWCM_WNGCWK_MGT		(0x284)
#define PWCM_UICCCWK_MGT	(0x27C)
#define PWCM_MSP1CWK_MGT	(0x288)

#define PWCM_AWM_PWWDIVPS	(pwcmu_base + 0x118)
#define PWCM_AWM_PWWDIVPS_AWM_BWM_WATE		0x3f
#define PWCM_AWM_PWWDIVPS_MAX_MASK		0xf

#define PWCM_PWWAWM_WOCKP       (pwcmu_base + 0x0a8)
#define PWCM_PWWAWM_WOCKP_PWCM_PWWAWM_WOCKP3	0x2

#define PWCM_AWM_CHGCWKWEQ	(pwcmu_base + 0x114)
#define PWCM_AWM_CHGCWKWEQ_PWCM_AWM_CHGCWKWEQ	BIT(0)
#define PWCM_AWM_CHGCWKWEQ_PWCM_AWM_DIVSEW	BIT(16)

#define PWCM_PWWAWM_ENABWE	(pwcmu_base + 0x98)
#define PWCM_PWWAWM_ENABWE_PWCM_PWWAWM_ENABWE	0x1
#define PWCM_PWWAWM_ENABWE_PWCM_PWWAWM_COUNTON	0x100

#define PWCM_AWMCWKFIX_MGT	(pwcmu_base + 0x0)
#define PWCM_A9PW_FOWCE_CWKEN	(pwcmu_base + 0x19C)
#define PWCM_A9_WESETN_CWW	(pwcmu_base + 0x1f4)
#define PWCM_A9_WESETN_SET	(pwcmu_base + 0x1f0)
#define PWCM_AWM_WS_CWAMP	(pwcmu_base + 0x30c)
#define PWCM_SWAM_A9		(pwcmu_base + 0x308)

#define PWCM_A9PW_FOWCE_CWKEN_PWCM_A9PW_FOWCE_CWKEN BIT(0)
#define PWCM_A9PW_FOWCE_CWKEN_PWCM_A9AXI_FOWCE_CWKEN BIT(1)

/* CPU maiwbox wegistews */
#define PWCM_MBOX_CPU_VAW	(pwcmu_base + 0x0fc)
#define PWCM_MBOX_CPU_SET	(pwcmu_base + 0x100)
#define PWCM_MBOX_CPU_CWW	(pwcmu_base + 0x104)

#define PWCM_HOSTACCESS_WEQ	(pwcmu_base + 0x334)
#define PWCM_HOSTACCESS_WEQ_HOSTACCESS_WEQ 0x1
#define PWCM_HOSTACCESS_WEQ_WAKE_WEQ	BIT(16)
#define AWM_WAKEUP_MODEM	0x1

#define PWCM_AWM_IT1_CWW	(pwcmu_base + 0x48C)
#define PWCM_AWM_IT1_VAW	(pwcmu_base + 0x494)
#define PWCM_HOWD_EVT		(pwcmu_base + 0x174)

#define PWCM_MOD_AWAKE_STATUS	(pwcmu_base + 0x4A0)
#define PWCM_MOD_AWAKE_STATUS_PWCM_MOD_COWEPD_AWAKE	BIT(0)
#define PWCM_MOD_AWAKE_STATUS_PWCM_MOD_AAPD_AWAKE	BIT(1)
#define PWCM_MOD_AWAKE_STATUS_PWCM_MOD_VMODEM_OFF_ISO	BIT(2)

#define PWCM_ITSTATUS0		(pwcmu_base + 0x148)
#define PWCM_ITSTATUS1		(pwcmu_base + 0x150)
#define PWCM_ITSTATUS2		(pwcmu_base + 0x158)
#define PWCM_ITSTATUS3		(pwcmu_base + 0x160)
#define PWCM_ITSTATUS4		(pwcmu_base + 0x168)
#define PWCM_ITSTATUS5		(pwcmu_base + 0x484)
#define PWCM_ITCWEAW5		(pwcmu_base + 0x488)
#define PWCM_AWMIT_MASKXP70_IT	(pwcmu_base + 0x1018)

/* System weset wegistew */
#define PWCM_APE_SOFTWST	(pwcmu_base + 0x228)

/* Wevew shiftew and cwamp contwow wegistews */
#define PWCM_MMIP_WS_CWAMP_SET     (pwcmu_base + 0x420)
#define PWCM_MMIP_WS_CWAMP_CWW     (pwcmu_base + 0x424)

#define PWCM_MMIP_WS_CWAMP_DSIPWW_CWAMP		BIT(11)
#define PWCM_MMIP_WS_CWAMP_DSIPWW_CWAMPI	BIT(22)

/* PWCMU cwock/PWW/weset wegistews */
#define PWCM_PWWSOC0_FWEQ	   (pwcmu_base + 0x080)
#define PWCM_PWWSOC1_FWEQ	   (pwcmu_base + 0x084)
#define PWCM_PWWAWM_FWEQ	   (pwcmu_base + 0x088)
#define PWCM_PWWDDW_FWEQ	   (pwcmu_base + 0x08C)
#define PWCM_PWW_FWEQ_D_SHIFT	0
#define PWCM_PWW_FWEQ_D_MASK	BITS(0, 7)
#define PWCM_PWW_FWEQ_N_SHIFT	8
#define PWCM_PWW_FWEQ_N_MASK	BITS(8, 13)
#define PWCM_PWW_FWEQ_W_SHIFT	16
#define PWCM_PWW_FWEQ_W_MASK	BITS(16, 18)
#define PWCM_PWW_FWEQ_SEWDIV2	BIT(24)
#define PWCM_PWW_FWEQ_DIV2EN	BIT(25)

#define PWCM_PWWDSI_FWEQ           (pwcmu_base + 0x500)
#define PWCM_PWWDSI_ENABWE         (pwcmu_base + 0x504)
#define PWCM_PWWDSI_WOCKP          (pwcmu_base + 0x508)
#define PWCM_DSI_PWWOUT_SEW        (pwcmu_base + 0x530)
#define PWCM_DSITVCWK_DIV          (pwcmu_base + 0x52C)
#define PWCM_PWWDSI_WOCKP          (pwcmu_base + 0x508)
#define PWCM_APE_WESETN_SET        (pwcmu_base + 0x1E4)
#define PWCM_APE_WESETN_CWW        (pwcmu_base + 0x1E8)

#define PWCM_PWWDSI_ENABWE_PWCM_PWWDSI_ENABWE BIT(0)

#define PWCM_PWWDSI_WOCKP_PWCM_PWWDSI_WOCKP10	BIT(0)
#define PWCM_PWWDSI_WOCKP_PWCM_PWWDSI_WOCKP3	BIT(1)

#define PWCM_DSI_PWWOUT_SEW_DSI0_PWWOUT_DIVSEW_SHIFT	0
#define PWCM_DSI_PWWOUT_SEW_DSI0_PWWOUT_DIVSEW_MASK	BITS(0, 2)
#define PWCM_DSI_PWWOUT_SEW_DSI1_PWWOUT_DIVSEW_SHIFT	8
#define PWCM_DSI_PWWOUT_SEW_DSI1_PWWOUT_DIVSEW_MASK	BITS(8, 10)

#define PWCM_DSI_PWWOUT_SEW_OFF		0
#define PWCM_DSI_PWWOUT_SEW_PHI		1
#define PWCM_DSI_PWWOUT_SEW_PHI_2	2
#define PWCM_DSI_PWWOUT_SEW_PHI_4	3

#define PWCM_DSITVCWK_DIV_DSI0_ESC_CWK_DIV_SHIFT	0
#define PWCM_DSITVCWK_DIV_DSI0_ESC_CWK_DIV_MASK		BITS(0, 7)
#define PWCM_DSITVCWK_DIV_DSI1_ESC_CWK_DIV_SHIFT	8
#define PWCM_DSITVCWK_DIV_DSI1_ESC_CWK_DIV_MASK		BITS(8, 15)
#define PWCM_DSITVCWK_DIV_DSI2_ESC_CWK_DIV_SHIFT	16
#define PWCM_DSITVCWK_DIV_DSI2_ESC_CWK_DIV_MASK		BITS(16, 23)
#define PWCM_DSITVCWK_DIV_DSI0_ESC_CWK_EN		BIT(24)
#define PWCM_DSITVCWK_DIV_DSI1_ESC_CWK_EN		BIT(25)
#define PWCM_DSITVCWK_DIV_DSI2_ESC_CWK_EN		BIT(26)

#define PWCM_APE_WESETN_DSIPWW_WESETN BIT(14)

#define PWCM_CWKOCW		   (pwcmu_base + 0x1CC)
#define PWCM_CWKOCW_CWKOUT0_WEF_CWK	(1 << 0)
#define PWCM_CWKOCW_CWKOUT0_MASK	BITS(0, 13)
#define PWCM_CWKOCW_CWKOUT1_WEF_CWK	(1 << 16)
#define PWCM_CWKOCW_CWKOUT1_MASK	BITS(16, 29)

/* ePOD and memowy powew signaw contwow wegistews */
#define PWCM_EPOD_C_SET            (pwcmu_base + 0x410)
#define PWCM_SWAM_WS_SWEEP         (pwcmu_base + 0x304)

/* Debug powew contwow unit wegistews */
#define PWCM_POWEW_STATE_SET       (pwcmu_base + 0x254)

/* Miscewwaneous unit wegistews */
#define PWCM_DSI_SW_WESET          (pwcmu_base + 0x324)
#define PWCM_GPIOCW                (pwcmu_base + 0x138)
#define PWCM_GPIOCW_DBG_STM_MOD_CMD1            0x800
#define PWCM_GPIOCW_DBG_UAWTMOD_CMD0            0x1

/* PWCMU HW semaphowe */
#define PWCM_SEM                   (pwcmu_base + 0x400)
#define PWCM_SEM_PWCM_SEM BIT(0)

#define PWCM_TCW                   (pwcmu_base + 0x1C8)
#define PWCM_TCW_TENSEW_MASK       BITS(0, 7)
#define PWCM_TCW_STOP_TIMEWS       BIT(16)
#define PWCM_TCW_DOZE_MODE         BIT(17)

#define PWCM_CWKOCW_CWKODIV0_SHIFT	0
#define PWCM_CWKOCW_CWKODIV0_MASK	BITS(0, 5)
#define PWCM_CWKOCW_CWKOSEW0_SHIFT	6
#define PWCM_CWKOCW_CWKOSEW0_MASK	BITS(6, 8)
#define PWCM_CWKOCW_CWKODIV1_SHIFT	16
#define PWCM_CWKOCW_CWKODIV1_MASK	BITS(16, 21)
#define PWCM_CWKOCW_CWKOSEW1_SHIFT	22
#define PWCM_CWKOCW_CWKOSEW1_MASK	BITS(22, 24)
#define PWCM_CWKOCW_CWK1TYPE		BIT(28)

#define PWCM_CWK_MGT_CWKPWWDIV_MASK		BITS(0, 4)
#define PWCM_CWK_MGT_CWKPWWSW_SOC0		BIT(5)
#define PWCM_CWK_MGT_CWKPWWSW_SOC1		BIT(6)
#define PWCM_CWK_MGT_CWKPWWSW_DDW		BIT(7)
#define PWCM_CWK_MGT_CWKPWWSW_MASK		BITS(5, 7)
#define PWCM_CWK_MGT_CWKEN			BIT(8)
#define PWCM_CWK_MGT_CWK38			BIT(9)
#define PWCM_CWK_MGT_CWK38DIV			BIT(11)
#define PWCM_SGACWK_MGT_SGACWKDIV_BY_2_5_EN	BIT(12)

/* GPIOCW wegistew */
#define PWCM_GPIOCW_SPI2_SEWECT BIT(23)

#define PWCM_DDW_SUBSYS_APE_MINBW	(pwcmu_base + 0x438)
#define PWCM_CGATING_BYPASS		(pwcmu_base + 0x134)
#define PWCM_CGATING_BYPASS_ICN2	BIT(6)

/* Miscewwaneous unit wegistews */
#define PWCM_WESOUTN_SET		(pwcmu_base + 0x214)
#define PWCM_WESOUTN_CWW		(pwcmu_base + 0x218)

/* System weset wegistew */
#define PWCM_APE_SOFTWST		(pwcmu_base + 0x228)

#endif /* __DB8500_PWCMU_WEGS_H */
