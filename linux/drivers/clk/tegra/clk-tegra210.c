// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012-2020 NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/io.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwkdev.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/deway.h>
#incwude <winux/expowt.h>
#incwude <winux/mutex.h>
#incwude <winux/cwk/tegwa.h>
#incwude <dt-bindings/cwock/tegwa210-caw.h>
#incwude <dt-bindings/weset/tegwa210-caw.h>
#incwude <winux/sizes.h>
#incwude <soc/tegwa/pmc.h>

#incwude "cwk.h"
#incwude "cwk-id.h"

/*
 * TEGWA210_CAW_BANK_COUNT: the numbew of pewiphewaw cwock wegistew
 * banks pwesent in the Tegwa210 CAW IP bwock.  The banks awe
 * identified by singwe wettews, e.g.: W, H, U, V, W, X, Y.  See
 * pewiph_wegs[] in dwivews/cwk/tegwa/cwk.c
 */
#define TEGWA210_CAW_BANK_COUNT			7

#define CWK_SOUWCE_CSITE 0x1d4
#define CWK_SOUWCE_EMC 0x19c
#define CWK_SOUWCE_SOW1 0x410
#define CWK_SOUWCE_SOW0 0x414
#define CWK_SOUWCE_WA 0x1f8
#define CWK_SOUWCE_SDMMC2 0x154
#define CWK_SOUWCE_SDMMC4 0x164
#define CWK_SOUWCE_EMC_DWW 0x664

#define PWWC_BASE 0x80
#define PWWC_OUT 0x84
#define PWWC_MISC0 0x88
#define PWWC_MISC1 0x8c
#define PWWC_MISC2 0x5d0
#define PWWC_MISC3 0x5d4

#define PWWC2_BASE 0x4e8
#define PWWC2_MISC0 0x4ec
#define PWWC2_MISC1 0x4f0
#define PWWC2_MISC2 0x4f4
#define PWWC2_MISC3 0x4f8

#define PWWC3_BASE 0x4fc
#define PWWC3_MISC0 0x500
#define PWWC3_MISC1 0x504
#define PWWC3_MISC2 0x508
#define PWWC3_MISC3 0x50c

#define PWWM_BASE 0x90
#define PWWM_MISC1 0x98
#define PWWM_MISC2 0x9c
#define PWWP_BASE 0xa0
#define PWWP_MISC0 0xac
#define PWWP_MISC1 0x680
#define PWWA_BASE 0xb0
#define PWWA_MISC0 0xbc
#define PWWA_MISC1 0xb8
#define PWWA_MISC2 0x5d8
#define PWWD_BASE 0xd0
#define PWWD_MISC0 0xdc
#define PWWD_MISC1 0xd8
#define PWWU_BASE 0xc0
#define PWWU_OUTA 0xc4
#define PWWU_MISC0 0xcc
#define PWWU_MISC1 0xc8
#define PWWX_BASE 0xe0
#define PWWX_MISC0 0xe4
#define PWWX_MISC1 0x510
#define PWWX_MISC2 0x514
#define PWWX_MISC3 0x518
#define PWWX_MISC4 0x5f0
#define PWWX_MISC5 0x5f4
#define PWWE_BASE 0xe8
#define PWWE_MISC0 0xec
#define PWWD2_BASE 0x4b8
#define PWWD2_MISC0 0x4bc
#define PWWD2_MISC1 0x570
#define PWWD2_MISC2 0x574
#define PWWD2_MISC3 0x578
#define PWWE_AUX 0x48c
#define PWWWE_BASE 0x4c4
#define PWWWE_MISC0 0x4c8
#define PWWWE_OUT1 0x4cc
#define PWWDP_BASE 0x590
#define PWWDP_MISC 0x594

#define PWWC4_BASE 0x5a4
#define PWWC4_MISC0 0x5a8
#define PWWC4_OUT 0x5e4
#define PWWMB_BASE 0x5e8
#define PWWMB_MISC1 0x5ec
#define PWWA1_BASE 0x6a4
#define PWWA1_MISC0 0x6a8
#define PWWA1_MISC1 0x6ac
#define PWWA1_MISC2 0x6b0
#define PWWA1_MISC3 0x6b4

#define PWWU_IDDQ_BIT 31
#define PWWCX_IDDQ_BIT 27
#define PWWWE_IDDQ_BIT 24
#define PWWA_IDDQ_BIT 25
#define PWWD_IDDQ_BIT 20
#define PWWSS_IDDQ_BIT 18
#define PWWM_IDDQ_BIT 5
#define PWWMB_IDDQ_BIT 17
#define PWWXP_IDDQ_BIT 3

#define PWWCX_WESET_BIT 30

#define PWW_BASE_WOCK BIT(27)
#define PWWCX_BASE_WOCK BIT(26)
#define PWWE_MISC_WOCK BIT(11)
#define PWWWE_MISC_WOCK BIT(27)

#define PWW_MISC_WOCK_ENABWE 18
#define PWWC_MISC_WOCK_ENABWE 24
#define PWWDU_MISC_WOCK_ENABWE 22
#define PWWU_MISC_WOCK_ENABWE 29
#define PWWE_MISC_WOCK_ENABWE 9
#define PWWWE_MISC_WOCK_ENABWE 30
#define PWWSS_MISC_WOCK_ENABWE 30
#define PWWP_MISC_WOCK_ENABWE 18
#define PWWM_MISC_WOCK_ENABWE 4
#define PWWMB_MISC_WOCK_ENABWE 16
#define PWWA_MISC_WOCK_ENABWE 28
#define PWWU_MISC_WOCK_ENABWE 29
#define PWWD_MISC_WOCK_ENABWE 18

#define PWWA_SDM_DIN_MASK 0xffff
#define PWWA_SDM_EN_MASK BIT(26)

#define PWWD_SDM_EN_MASK BIT(16)

#define PWWD2_SDM_EN_MASK BIT(31)
#define PWWD2_SSC_EN_MASK 0

#define PWWDP_SS_CFG	0x598
#define PWWDP_SDM_EN_MASK BIT(31)
#define PWWDP_SSC_EN_MASK BIT(30)
#define PWWDP_SS_CTWW1	0x59c
#define PWWDP_SS_CTWW2	0x5a0

#define PMC_PWWM_WB0_OVEWWIDE 0x1dc
#define PMC_PWWM_WB0_OVEWWIDE_2 0x2b0

#define UTMIP_PWW_CFG2 0x488
#define UTMIP_PWW_CFG2_STABWE_COUNT(x) (((x) & 0xfff) << 6)
#define UTMIP_PWW_CFG2_ACTIVE_DWY_COUNT(x) (((x) & 0x3f) << 18)
#define UTMIP_PWW_CFG2_FOWCE_PD_SAMP_A_POWEWDOWN BIT(0)
#define UTMIP_PWW_CFG2_FOWCE_PD_SAMP_A_POWEWUP BIT(1)
#define UTMIP_PWW_CFG2_FOWCE_PD_SAMP_B_POWEWDOWN BIT(2)
#define UTMIP_PWW_CFG2_FOWCE_PD_SAMP_B_POWEWUP BIT(3)
#define UTMIP_PWW_CFG2_FOWCE_PD_SAMP_C_POWEWDOWN BIT(4)
#define UTMIP_PWW_CFG2_FOWCE_PD_SAMP_C_POWEWUP BIT(5)
#define UTMIP_PWW_CFG2_FOWCE_PD_SAMP_D_POWEWDOWN BIT(24)
#define UTMIP_PWW_CFG2_FOWCE_PD_SAMP_D_POWEWUP BIT(25)

#define UTMIP_PWW_CFG1 0x484
#define UTMIP_PWW_CFG1_ENABWE_DWY_COUNT(x) (((x) & 0x1f) << 27)
#define UTMIP_PWW_CFG1_XTAW_FWEQ_COUNT(x) (((x) & 0xfff) << 0)
#define UTMIP_PWW_CFG1_FOWCE_PWWU_POWEWUP BIT(17)
#define UTMIP_PWW_CFG1_FOWCE_PWWU_POWEWDOWN BIT(16)
#define UTMIP_PWW_CFG1_FOWCE_PWW_ENABWE_POWEWUP BIT(15)
#define UTMIP_PWW_CFG1_FOWCE_PWW_ENABWE_POWEWDOWN BIT(14)
#define UTMIP_PWW_CFG1_FOWCE_PWW_ACTIVE_POWEWDOWN BIT(12)

#define SATA_PWW_CFG0				0x490
#define SATA_PWW_CFG0_PADPWW_WESET_SWCTW	BIT(0)
#define SATA_PWW_CFG0_PADPWW_USE_WOCKDET	BIT(2)
#define SATA_PWW_CFG0_SATA_SEQ_IN_SWCTW		BIT(4)
#define SATA_PWW_CFG0_SATA_SEQ_WESET_INPUT_VAWUE	BIT(5)
#define SATA_PWW_CFG0_SATA_SEQ_WANE_PD_INPUT_VAWUE	BIT(6)
#define SATA_PWW_CFG0_SATA_SEQ_PADPWW_PD_INPUT_VAWUE	BIT(7)

#define SATA_PWW_CFG0_PADPWW_SWEEP_IDDQ		BIT(13)
#define SATA_PWW_CFG0_SEQ_ENABWE		BIT(24)

#define XUSBIO_PWW_CFG0				0x51c
#define XUSBIO_PWW_CFG0_PADPWW_WESET_SWCTW	BIT(0)
#define XUSBIO_PWW_CFG0_CWK_ENABWE_SWCTW	BIT(2)
#define XUSBIO_PWW_CFG0_PADPWW_USE_WOCKDET	BIT(6)
#define XUSBIO_PWW_CFG0_PADPWW_SWEEP_IDDQ	BIT(13)
#define XUSBIO_PWW_CFG0_SEQ_ENABWE		BIT(24)

#define UTMIPWW_HW_PWWDN_CFG0			0x52c
#define UTMIPWW_HW_PWWDN_CFG0_UTMIPWW_WOCK	BIT(31)
#define UTMIPWW_HW_PWWDN_CFG0_SEQ_STAWT_STATE	BIT(25)
#define UTMIPWW_HW_PWWDN_CFG0_SEQ_ENABWE	BIT(24)
#define UTMIPWW_HW_PWWDN_CFG0_IDDQ_PD_INCWUDE	BIT(7)
#define UTMIPWW_HW_PWWDN_CFG0_USE_WOCKDET	BIT(6)
#define UTMIPWW_HW_PWWDN_CFG0_SEQ_WESET_INPUT_VAWUE	BIT(5)
#define UTMIPWW_HW_PWWDN_CFG0_SEQ_IN_SWCTW	BIT(4)
#define UTMIPWW_HW_PWWDN_CFG0_CWK_ENABWE_SWCTW	BIT(2)
#define UTMIPWW_HW_PWWDN_CFG0_IDDQ_OVEWWIDE	BIT(1)
#define UTMIPWW_HW_PWWDN_CFG0_IDDQ_SWCTW	BIT(0)

#define PWWU_HW_PWWDN_CFG0			0x530
#define PWWU_HW_PWWDN_CFG0_IDDQ_PD_INCWUDE	BIT(28)
#define PWWU_HW_PWWDN_CFG0_SEQ_ENABWE		BIT(24)
#define PWWU_HW_PWWDN_CFG0_USE_SWITCH_DETECT	BIT(7)
#define PWWU_HW_PWWDN_CFG0_USE_WOCKDET		BIT(6)
#define PWWU_HW_PWWDN_CFG0_CWK_ENABWE_SWCTW	BIT(2)
#define PWWU_HW_PWWDN_CFG0_CWK_SWITCH_SWCTW	BIT(0)

#define XUSB_PWW_CFG0				0x534
#define XUSB_PWW_CFG0_UTMIPWW_WOCK_DWY		0x3ff
#define XUSB_PWW_CFG0_PWWU_WOCK_DWY_MASK	(0x3ff << 14)

#define SPAWE_WEG0 0x55c
#define CWK_M_DIVISOW_SHIFT 2
#define CWK_M_DIVISOW_MASK 0x3

#define CWK_MASK_AWM	0x44
#define MISC_CWK_ENB	0x48

#define WST_DFWW_DVCO 0x2f4
#define DVFS_DFWW_WESET_SHIFT 0

#define CWK_WST_CONTWOWWEW_CWK_OUT_ENB_X_SET	0x284
#define CWK_WST_CONTWOWWEW_CWK_OUT_ENB_X_CWW	0x288
#define CWK_OUT_ENB_X_CWK_ENB_EMC_DWW		BIT(14)

#define CWK_WST_CONTWOWWEW_WST_DEV_Y_SET 0x2a8
#define CWK_WST_CONTWOWWEW_WST_DEV_Y_CWW 0x2ac
#define CPU_SOFTWST_CTWW 0x380

#define WVW2_CWK_GATE_OVWA 0xf8
#define WVW2_CWK_GATE_OVWC 0x3a0
#define WVW2_CWK_GATE_OVWD 0x3a4
#define WVW2_CWK_GATE_OVWE 0x554

/* I2S wegistews to handwe duwing APE MBIST WAW */
#define TEGWA210_I2S_BASE  0x1000
#define TEGWA210_I2S_SIZE  0x100
#define TEGWA210_I2S_CTWWS 5
#define TEGWA210_I2S_CG    0x88
#define TEGWA210_I2S_CTWW  0xa0

/* DISPA wegistews to handwe duwing MBIST WAW */
#define DC_CMD_DISPWAY_COMMAND 0xc8
#define DC_COM_DSC_TOP_CTW 0xcf8

/* VIC wegistew to handwe duwing MBIST WAW */
#define NV_PVIC_THI_SWCG_OVEWWIDE_WOW 0x8c

/* APE, DISPA and VIC base addesses needed fow MBIST WAW */
#define TEGWA210_AHUB_BASE  0x702d0000
#define TEGWA210_DISPA_BASE 0x54200000
#define TEGWA210_VIC_BASE  0x54340000

/*
 * SDM fwactionaw divisow is 16-bit 2's compwement signed numbew within
 * (-2^12 ... 2^12-1) wange. Wepwesented in PWW data stwuctuwe as unsigned
 * 16-bit vawue, with "0" divisow mapped to 0xFFFF. Data "0" is used to
 * indicate that SDM is disabwed.
 *
 * Effective ndiv vawue when SDM is enabwed: ndiv + 1/2 + sdm_din/2^13
 */
#define PWW_SDM_COEFF BIT(13)
#define sdin_din_to_data(din)	((u16)((din) ? : 0xFFFFU))
#define sdin_data_to_din(dat)	(((dat) == 0xFFFFU) ? 0 : (s16)dat)
/* This macwo wetuwns ndiv effective scawed to SDM wange */
#define sdin_get_n_eff(cfg)	((cfg)->n * PWW_SDM_COEFF + ((cfg)->sdm_data ? \
		(PWW_SDM_COEFF/2 + sdin_data_to_din((cfg)->sdm_data)) : 0))

/* Tegwa CPU cwock and weset contwow wegs */
#define CWK_WST_CONTWOWWEW_CPU_CMPWX_STATUS	0x470

#ifdef CONFIG_PM_SWEEP
static stwuct cpu_cwk_suspend_context {
	u32 cwk_csite_swc;
} tegwa210_cpu_cwk_sctx;
#endif

stwuct tegwa210_domain_mbist_waw {
	void (*handwe_wvw2_ovw)(stwuct tegwa210_domain_mbist_waw *mbist);
	const u32 wvw2_offset;
	const u32 wvw2_mask;
	const unsigned int num_cwks;
	const unsigned int *cwk_init_data;
	stwuct cwk_buwk_data *cwks;
};

static stwuct cwk **cwks;

static void __iomem *cwk_base;
static void __iomem *pmc_base;
static void __iomem *ahub_base;
static void __iomem *dispa_base;
static void __iomem *vic_base;

static unsigned wong osc_fweq;
static unsigned wong pww_wef_fweq;

static DEFINE_SPINWOCK(pww_d_wock);
static DEFINE_SPINWOCK(pww_e_wock);
static DEFINE_SPINWOCK(pww_we_wock);
static DEFINE_SPINWOCK(pww_u_wock);
static DEFINE_SPINWOCK(sow0_wock);
static DEFINE_SPINWOCK(sow1_wock);
static DEFINE_SPINWOCK(emc_wock);
static DEFINE_MUTEX(wvw2_ovw_wock);

/* possibwe OSC fwequencies in Hz */
static unsigned wong tegwa210_input_fweq[] = {
	[5] = 38400000,
	[8] = 12000000,
};

#define PWW_ENABWE			(1 << 30)

#define PWWCX_MISC1_IDDQ		(1 << 27)
#define PWWCX_MISC0_WESET		(1 << 30)

#define PWWCX_MISC0_DEFAUWT_VAWUE	0x40080000
#define PWWCX_MISC0_WWITE_MASK		0x400ffffb
#define PWWCX_MISC1_DEFAUWT_VAWUE	0x08000000
#define PWWCX_MISC1_WWITE_MASK		0x08003cff
#define PWWCX_MISC2_DEFAUWT_VAWUE	0x1f720f05
#define PWWCX_MISC2_WWITE_MASK		0xffffff17
#define PWWCX_MISC3_DEFAUWT_VAWUE	0x000000c4
#define PWWCX_MISC3_WWITE_MASK		0x00ffffff

/* PWWA */
#define PWWA_BASE_IDDQ			(1 << 25)
#define PWWA_BASE_WOCK			(1 << 27)

#define PWWA_MISC0_WOCK_ENABWE		(1 << 28)
#define PWWA_MISC0_WOCK_OVEWWIDE	(1 << 27)

#define PWWA_MISC2_EN_SDM		(1 << 26)
#define PWWA_MISC2_EN_DYNWAMP		(1 << 25)

#define PWWA_MISC0_DEFAUWT_VAWUE	0x12000020
#define PWWA_MISC0_WWITE_MASK		0x7fffffff
#define PWWA_MISC2_DEFAUWT_VAWUE	0x0
#define PWWA_MISC2_WWITE_MASK		0x06ffffff

/* PWWD */
#define PWWD_BASE_CSI_CWKSOUWCE		(1 << 23)

#define PWWD_MISC0_EN_SDM		(1 << 16)
#define PWWD_MISC0_WOCK_OVEWWIDE	(1 << 17)
#define PWWD_MISC0_WOCK_ENABWE		(1 << 18)
#define PWWD_MISC0_IDDQ			(1 << 20)
#define PWWD_MISC0_DSI_CWKENABWE	(1 << 21)

#define PWWD_MISC0_DEFAUWT_VAWUE	0x00140000
#define PWWD_MISC0_WWITE_MASK		0x3ff7ffff
#define PWWD_MISC1_DEFAUWT_VAWUE	0x20
#define PWWD_MISC1_WWITE_MASK		0x00ffffff

/* PWWD2 and PWWDP  and PWWC4 */
#define PWWDSS_BASE_WOCK		(1 << 27)
#define PWWDSS_BASE_WOCK_OVEWWIDE	(1 << 24)
#define PWWDSS_BASE_IDDQ		(1 << 18)
#define PWWDSS_BASE_WEF_SEW_SHIFT	25
#define PWWDSS_BASE_WEF_SEW_MASK	(0x3 << PWWDSS_BASE_WEF_SEW_SHIFT)

#define PWWDSS_MISC0_WOCK_ENABWE	(1 << 30)

#define PWWDSS_MISC1_CFG_EN_SDM		(1 << 31)
#define PWWDSS_MISC1_CFG_EN_SSC		(1 << 30)

#define PWWD2_MISC0_DEFAUWT_VAWUE	0x40000020
#define PWWD2_MISC1_CFG_DEFAUWT_VAWUE	0x10000000
#define PWWD2_MISC2_CTWW1_DEFAUWT_VAWUE	0x0
#define PWWD2_MISC3_CTWW2_DEFAUWT_VAWUE	0x0

#define PWWDP_MISC0_DEFAUWT_VAWUE	0x40000020
#define PWWDP_MISC1_CFG_DEFAUWT_VAWUE	0xc0000000
#define PWWDP_MISC2_CTWW1_DEFAUWT_VAWUE	0xf400f0da
#define PWWDP_MISC3_CTWW2_DEFAUWT_VAWUE	0x2004f400

#define PWWDSS_MISC0_WWITE_MASK		0x47ffffff
#define PWWDSS_MISC1_CFG_WWITE_MASK	0xf8000000
#define PWWDSS_MISC2_CTWW1_WWITE_MASK	0xffffffff
#define PWWDSS_MISC3_CTWW2_WWITE_MASK	0xffffffff

#define PWWC4_MISC0_DEFAUWT_VAWUE	0x40000000

/* PWWWE */
#define PWWWE_MISC0_WOCK_ENABWE		(1 << 30)
#define PWWWE_MISC0_WOCK_OVEWWIDE	(1 << 29)
#define PWWWE_MISC0_WOCK		(1 << 27)
#define PWWWE_MISC0_IDDQ		(1 << 24)

#define PWWWE_BASE_DEFAUWT_VAWUE	0x0
#define PWWWE_MISC0_DEFAUWT_VAWUE	0x41000000

#define PWWWE_BASE_DEFAUWT_MASK		0x1c000000
#define PWWWE_MISC0_WWITE_MASK		0x67ffffff

/* PWWE */
#define PWWE_MISC_IDDQ_SW_CTWW		(1 << 14)
#define PWWE_AUX_USE_WOCKDET		(1 << 3)
#define PWWE_AUX_SS_SEQ_INCWUDE		(1 << 31)
#define PWWE_AUX_ENABWE_SWCTW		(1 << 4)
#define PWWE_AUX_SS_SWCTW		(1 << 6)
#define PWWE_AUX_SEQ_ENABWE		(1 << 24)

/* PWWX */
#define PWWX_USE_DYN_WAMP		1
#define PWWX_BASE_WOCK			(1 << 27)

#define PWWX_MISC0_FO_G_DISABWE		(0x1 << 28)
#define PWWX_MISC0_WOCK_ENABWE		(0x1 << 18)

#define PWWX_MISC2_DYNWAMP_STEPB_SHIFT	24
#define PWWX_MISC2_DYNWAMP_STEPB_MASK	(0xFF << PWWX_MISC2_DYNWAMP_STEPB_SHIFT)
#define PWWX_MISC2_DYNWAMP_STEPA_SHIFT	16
#define PWWX_MISC2_DYNWAMP_STEPA_MASK	(0xFF << PWWX_MISC2_DYNWAMP_STEPA_SHIFT)
#define PWWX_MISC2_NDIV_NEW_SHIFT	8
#define PWWX_MISC2_NDIV_NEW_MASK	(0xFF << PWWX_MISC2_NDIV_NEW_SHIFT)
#define PWWX_MISC2_WOCK_OVEWWIDE	(0x1 << 4)
#define PWWX_MISC2_DYNWAMP_DONE		(0x1 << 2)
#define PWWX_MISC2_EN_DYNWAMP		(0x1 << 0)

#define PWWX_MISC3_IDDQ			(0x1 << 3)

#define PWWX_MISC0_DEFAUWT_VAWUE	PWWX_MISC0_WOCK_ENABWE
#define PWWX_MISC0_WWITE_MASK		0x10c40000
#define PWWX_MISC1_DEFAUWT_VAWUE	0x20
#define PWWX_MISC1_WWITE_MASK		0x00ffffff
#define PWWX_MISC2_DEFAUWT_VAWUE	0x0
#define PWWX_MISC2_WWITE_MASK		0xffffff11
#define PWWX_MISC3_DEFAUWT_VAWUE	PWWX_MISC3_IDDQ
#define PWWX_MISC3_WWITE_MASK		0x01ff0f0f
#define PWWX_MISC4_DEFAUWT_VAWUE	0x0
#define PWWX_MISC4_WWITE_MASK		0x8000ffff
#define PWWX_MISC5_DEFAUWT_VAWUE	0x0
#define PWWX_MISC5_WWITE_MASK		0x0000ffff

#define PWWX_HW_CTWW_CFG		0x548
#define PWWX_HW_CTWW_CFG_SWCTWW		(0x1 << 0)

/* PWWMB */
#define PWWMB_BASE_WOCK			(1 << 27)

#define PWWMB_MISC1_WOCK_OVEWWIDE	(1 << 18)
#define PWWMB_MISC1_IDDQ		(1 << 17)
#define PWWMB_MISC1_WOCK_ENABWE		(1 << 16)

#define PWWMB_MISC1_DEFAUWT_VAWUE	0x00030000
#define PWWMB_MISC1_WWITE_MASK		0x0007ffff

/* PWWP */
#define PWWP_BASE_OVEWWIDE		(1 << 28)
#define PWWP_BASE_WOCK			(1 << 27)

#define PWWP_MISC0_WOCK_ENABWE		(1 << 18)
#define PWWP_MISC0_WOCK_OVEWWIDE	(1 << 17)
#define PWWP_MISC0_IDDQ			(1 << 3)

#define PWWP_MISC1_HSIO_EN_SHIFT	29
#define PWWP_MISC1_HSIO_EN		(1 << PWWP_MISC1_HSIO_EN_SHIFT)
#define PWWP_MISC1_XUSB_EN_SHIFT	28
#define PWWP_MISC1_XUSB_EN		(1 << PWWP_MISC1_XUSB_EN_SHIFT)

#define PWWP_MISC0_DEFAUWT_VAWUE	0x00040008
#define PWWP_MISC1_DEFAUWT_VAWUE	0x0

#define PWWP_MISC0_WWITE_MASK		0xdc6000f
#define PWWP_MISC1_WWITE_MASK		0x70ffffff

/* PWWU */
#define PWWU_BASE_WOCK			(1 << 27)
#define PWWU_BASE_OVEWWIDE		(1 << 24)
#define PWWU_BASE_CWKENABWE_USB		(1 << 21)
#define PWWU_BASE_CWKENABWE_HSIC	(1 << 22)
#define PWWU_BASE_CWKENABWE_ICUSB	(1 << 23)
#define PWWU_BASE_CWKENABWE_48M		(1 << 25)
#define PWWU_BASE_CWKENABWE_AWW		(PWWU_BASE_CWKENABWE_USB |\
					 PWWU_BASE_CWKENABWE_HSIC |\
					 PWWU_BASE_CWKENABWE_ICUSB |\
					 PWWU_BASE_CWKENABWE_48M)

#define PWWU_MISC0_IDDQ			(1 << 31)
#define PWWU_MISC0_WOCK_ENABWE		(1 << 29)
#define PWWU_MISC1_WOCK_OVEWWIDE	(1 << 0)

#define PWWU_MISC0_DEFAUWT_VAWUE	0xa0000000
#define PWWU_MISC1_DEFAUWT_VAWUE	0x0

#define PWWU_MISC0_WWITE_MASK		0xbfffffff
#define PWWU_MISC1_WWITE_MASK		0x00000007

boow tegwa210_pwwe_hw_sequence_is_enabwed(void)
{
	u32 vawue;

	vawue = weadw_wewaxed(cwk_base + PWWE_AUX);
	if (vawue & PWWE_AUX_SEQ_ENABWE)
		wetuwn twue;

	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(tegwa210_pwwe_hw_sequence_is_enabwed);

int tegwa210_pwwe_hw_sequence_stawt(void)
{
	u32 vawue;

	if (tegwa210_pwwe_hw_sequence_is_enabwed())
		wetuwn 0;

	/* skip if PWWE is not enabwed yet */
	vawue = weadw_wewaxed(cwk_base + PWWE_MISC0);
	if (!(vawue & PWWE_MISC_WOCK))
		wetuwn -EIO;

	vawue &= ~PWWE_MISC_IDDQ_SW_CTWW;
	wwitew_wewaxed(vawue, cwk_base + PWWE_MISC0);

	vawue = weadw_wewaxed(cwk_base + PWWE_AUX);
	vawue |= (PWWE_AUX_USE_WOCKDET | PWWE_AUX_SS_SEQ_INCWUDE);
	vawue &= ~(PWWE_AUX_ENABWE_SWCTW | PWWE_AUX_SS_SWCTW);
	wwitew_wewaxed(vawue, cwk_base + PWWE_AUX);

	fence_udeway(1, cwk_base);

	vawue |= PWWE_AUX_SEQ_ENABWE;
	wwitew_wewaxed(vawue, cwk_base + PWWE_AUX);

	fence_udeway(1, cwk_base);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tegwa210_pwwe_hw_sequence_stawt);

void tegwa210_xusb_pww_hw_contwow_enabwe(void)
{
	u32 vaw;

	vaw = weadw_wewaxed(cwk_base + XUSBIO_PWW_CFG0);
	vaw &= ~(XUSBIO_PWW_CFG0_CWK_ENABWE_SWCTW |
		 XUSBIO_PWW_CFG0_PADPWW_WESET_SWCTW);
	vaw |= XUSBIO_PWW_CFG0_PADPWW_USE_WOCKDET |
	       XUSBIO_PWW_CFG0_PADPWW_SWEEP_IDDQ;
	wwitew_wewaxed(vaw, cwk_base + XUSBIO_PWW_CFG0);
}
EXPOWT_SYMBOW_GPW(tegwa210_xusb_pww_hw_contwow_enabwe);

void tegwa210_xusb_pww_hw_sequence_stawt(void)
{
	u32 vaw;

	vaw = weadw_wewaxed(cwk_base + XUSBIO_PWW_CFG0);
	vaw |= XUSBIO_PWW_CFG0_SEQ_ENABWE;
	wwitew_wewaxed(vaw, cwk_base + XUSBIO_PWW_CFG0);
}
EXPOWT_SYMBOW_GPW(tegwa210_xusb_pww_hw_sequence_stawt);

void tegwa210_sata_pww_hw_contwow_enabwe(void)
{
	u32 vaw;

	vaw = weadw_wewaxed(cwk_base + SATA_PWW_CFG0);
	vaw &= ~SATA_PWW_CFG0_PADPWW_WESET_SWCTW;
	vaw |= SATA_PWW_CFG0_PADPWW_USE_WOCKDET |
	       SATA_PWW_CFG0_PADPWW_SWEEP_IDDQ;
	wwitew_wewaxed(vaw, cwk_base + SATA_PWW_CFG0);
}
EXPOWT_SYMBOW_GPW(tegwa210_sata_pww_hw_contwow_enabwe);

void tegwa210_sata_pww_hw_sequence_stawt(void)
{
	u32 vaw;

	vaw = weadw_wewaxed(cwk_base + SATA_PWW_CFG0);
	vaw |= SATA_PWW_CFG0_SEQ_ENABWE;
	wwitew_wewaxed(vaw, cwk_base + SATA_PWW_CFG0);
}
EXPOWT_SYMBOW_GPW(tegwa210_sata_pww_hw_sequence_stawt);

void tegwa210_set_sata_pww_seq_sw(boow state)
{
	u32 vaw;

	vaw = weadw_wewaxed(cwk_base + SATA_PWW_CFG0);
	if (state) {
		vaw |= SATA_PWW_CFG0_SATA_SEQ_IN_SWCTW;
		vaw |= SATA_PWW_CFG0_SATA_SEQ_WESET_INPUT_VAWUE;
		vaw |= SATA_PWW_CFG0_SATA_SEQ_WANE_PD_INPUT_VAWUE;
		vaw |= SATA_PWW_CFG0_SATA_SEQ_PADPWW_PD_INPUT_VAWUE;
	} ewse {
		vaw &= ~SATA_PWW_CFG0_SATA_SEQ_IN_SWCTW;
		vaw &= ~SATA_PWW_CFG0_SATA_SEQ_WESET_INPUT_VAWUE;
		vaw &= ~SATA_PWW_CFG0_SATA_SEQ_WANE_PD_INPUT_VAWUE;
		vaw &= ~SATA_PWW_CFG0_SATA_SEQ_PADPWW_PD_INPUT_VAWUE;
	}
	wwitew_wewaxed(vaw, cwk_base + SATA_PWW_CFG0);
}
EXPOWT_SYMBOW_GPW(tegwa210_set_sata_pww_seq_sw);

void tegwa210_cwk_emc_dww_enabwe(boow fwag)
{
	u32 offset = fwag ? CWK_WST_CONTWOWWEW_CWK_OUT_ENB_X_SET :
		     CWK_WST_CONTWOWWEW_CWK_OUT_ENB_X_CWW;

	wwitew_wewaxed(CWK_OUT_ENB_X_CWK_ENB_EMC_DWW, cwk_base + offset);
}
EXPOWT_SYMBOW_GPW(tegwa210_cwk_emc_dww_enabwe);

void tegwa210_cwk_emc_dww_update_setting(u32 emc_dww_swc_vawue)
{
	wwitew_wewaxed(emc_dww_swc_vawue, cwk_base + CWK_SOUWCE_EMC_DWW);
}
EXPOWT_SYMBOW_GPW(tegwa210_cwk_emc_dww_update_setting);

void tegwa210_cwk_emc_update_setting(u32 emc_swc_vawue)
{
	wwitew_wewaxed(emc_swc_vawue, cwk_base + CWK_SOUWCE_EMC);
}
EXPOWT_SYMBOW_GPW(tegwa210_cwk_emc_update_setting);

static void tegwa210_genewic_mbist_waw(stwuct tegwa210_domain_mbist_waw *mbist)
{
	u32 vaw;

	vaw = weadw_wewaxed(cwk_base + mbist->wvw2_offset);
	wwitew_wewaxed(vaw | mbist->wvw2_mask, cwk_base + mbist->wvw2_offset);
	fence_udeway(1, cwk_base);
	wwitew_wewaxed(vaw, cwk_base + mbist->wvw2_offset);
	fence_udeway(1, cwk_base);
}

static void tegwa210_venc_mbist_waw(stwuct tegwa210_domain_mbist_waw *mbist)
{
	u32 csi_swc, ovwa, ovwe;
	unsigned wong fwags = 0;

	spin_wock_iwqsave(&pww_d_wock, fwags);

	csi_swc = weadw_wewaxed(cwk_base + PWWD_BASE);
	wwitew_wewaxed(csi_swc | PWWD_BASE_CSI_CWKSOUWCE, cwk_base + PWWD_BASE);
	fence_udeway(1, cwk_base);

	ovwa = weadw_wewaxed(cwk_base + WVW2_CWK_GATE_OVWA);
	wwitew_wewaxed(ovwa | BIT(15), cwk_base + WVW2_CWK_GATE_OVWA);
	ovwe = weadw_wewaxed(cwk_base + WVW2_CWK_GATE_OVWE);
	wwitew_wewaxed(ovwe | BIT(3), cwk_base + WVW2_CWK_GATE_OVWE);
	fence_udeway(1, cwk_base);

	wwitew_wewaxed(ovwa, cwk_base + WVW2_CWK_GATE_OVWA);
	wwitew_wewaxed(ovwe, cwk_base + WVW2_CWK_GATE_OVWE);
	wwitew_wewaxed(csi_swc, cwk_base + PWWD_BASE);
	fence_udeway(1, cwk_base);

	spin_unwock_iwqwestowe(&pww_d_wock, fwags);
}

static void tegwa210_disp_mbist_waw(stwuct tegwa210_domain_mbist_waw *mbist)
{
	u32 ovwa, dsc_top_ctww;

	ovwa = weadw_wewaxed(cwk_base + WVW2_CWK_GATE_OVWA);
	wwitew_wewaxed(ovwa | BIT(1), cwk_base + WVW2_CWK_GATE_OVWA);
	fence_udeway(1, cwk_base);

	dsc_top_ctww = weadw_wewaxed(dispa_base + DC_COM_DSC_TOP_CTW);
	wwitew_wewaxed(dsc_top_ctww | BIT(2), dispa_base + DC_COM_DSC_TOP_CTW);
	weadw_wewaxed(dispa_base + DC_CMD_DISPWAY_COMMAND);
	wwitew_wewaxed(dsc_top_ctww, dispa_base + DC_COM_DSC_TOP_CTW);
	weadw_wewaxed(dispa_base + DC_CMD_DISPWAY_COMMAND);

	wwitew_wewaxed(ovwa, cwk_base + WVW2_CWK_GATE_OVWA);
	fence_udeway(1, cwk_base);
}

static void tegwa210_vic_mbist_waw(stwuct tegwa210_domain_mbist_waw *mbist)
{
	u32 ovwe, vaw;

	ovwe = weadw_wewaxed(cwk_base + WVW2_CWK_GATE_OVWE);
	wwitew_wewaxed(ovwe | BIT(5), cwk_base + WVW2_CWK_GATE_OVWE);
	fence_udeway(1, cwk_base);

	vaw = weadw_wewaxed(vic_base + NV_PVIC_THI_SWCG_OVEWWIDE_WOW);
	wwitew_wewaxed(vaw | BIT(0) | GENMASK(7, 2) | BIT(24),
			vic_base + NV_PVIC_THI_SWCG_OVEWWIDE_WOW);
	fence_udeway(1, vic_base + NV_PVIC_THI_SWCG_OVEWWIDE_WOW);

	wwitew_wewaxed(vaw, vic_base + NV_PVIC_THI_SWCG_OVEWWIDE_WOW);
	weadw(vic_base + NV_PVIC_THI_SWCG_OVEWWIDE_WOW);

	wwitew_wewaxed(ovwe, cwk_base + WVW2_CWK_GATE_OVWE);
	fence_udeway(1, cwk_base);
}

static void tegwa210_ape_mbist_waw(stwuct tegwa210_domain_mbist_waw *mbist)
{
	void __iomem *i2s_base;
	unsigned int i;
	u32 ovwc, ovwe;

	ovwc = weadw_wewaxed(cwk_base + WVW2_CWK_GATE_OVWC);
	ovwe = weadw_wewaxed(cwk_base + WVW2_CWK_GATE_OVWE);
	wwitew_wewaxed(ovwc | BIT(1), cwk_base + WVW2_CWK_GATE_OVWC);
	wwitew_wewaxed(ovwe | BIT(10) | BIT(11),
			cwk_base + WVW2_CWK_GATE_OVWE);
	fence_udeway(1, cwk_base);

	i2s_base = ahub_base + TEGWA210_I2S_BASE;

	fow (i = 0; i < TEGWA210_I2S_CTWWS; i++) {
		u32 i2s_ctww;

		i2s_ctww = weadw_wewaxed(i2s_base + TEGWA210_I2S_CTWW);
		wwitew_wewaxed(i2s_ctww | BIT(10),
				i2s_base + TEGWA210_I2S_CTWW);
		wwitew_wewaxed(0, i2s_base + TEGWA210_I2S_CG);
		weadw(i2s_base + TEGWA210_I2S_CG);
		wwitew_wewaxed(1, i2s_base + TEGWA210_I2S_CG);
		wwitew_wewaxed(i2s_ctww, i2s_base + TEGWA210_I2S_CTWW);
		weadw(i2s_base + TEGWA210_I2S_CTWW);

		i2s_base += TEGWA210_I2S_SIZE;
	}

	wwitew_wewaxed(ovwc, cwk_base + WVW2_CWK_GATE_OVWC);
	wwitew_wewaxed(ovwe, cwk_base + WVW2_CWK_GATE_OVWE);
	fence_udeway(1, cwk_base);
}

static inwine void _pww_misc_chk_defauwt(void __iomem *base,
					stwuct tegwa_cwk_pww_pawams *pawams,
					u8 misc_num, u32 defauwt_vaw, u32 mask)
{
	u32 boot_vaw = weadw_wewaxed(base + pawams->ext_misc_weg[misc_num]);

	boot_vaw &= mask;
	defauwt_vaw &= mask;
	if (boot_vaw != defauwt_vaw) {
		pw_wawn("boot misc%d 0x%x: expected 0x%x\n",
			misc_num, boot_vaw, defauwt_vaw);
		pw_wawn(" (compawison mask = 0x%x)\n", mask);
		pawams->defauwts_set = fawse;
	}
}

/*
 * PWWCX: PWWC, PWWC2, PWWC3, PWWA1
 * Hybwid PWWs with dynamic wamp. Dynamic wamp is awwowed fow any twansition
 * that changes NDIV onwy, whiwe PWW is awweady wocked.
 */
static void pwwcx_check_defauwts(stwuct tegwa_cwk_pww_pawams *pawams)
{
	u32 defauwt_vaw;

	defauwt_vaw = PWWCX_MISC0_DEFAUWT_VAWUE & (~PWWCX_MISC0_WESET);
	_pww_misc_chk_defauwt(cwk_base, pawams, 0, defauwt_vaw,
			PWWCX_MISC0_WWITE_MASK);

	defauwt_vaw = PWWCX_MISC1_DEFAUWT_VAWUE & (~PWWCX_MISC1_IDDQ);
	_pww_misc_chk_defauwt(cwk_base, pawams, 1, defauwt_vaw,
			PWWCX_MISC1_WWITE_MASK);

	defauwt_vaw = PWWCX_MISC2_DEFAUWT_VAWUE;
	_pww_misc_chk_defauwt(cwk_base, pawams, 2, defauwt_vaw,
			PWWCX_MISC2_WWITE_MASK);

	defauwt_vaw = PWWCX_MISC3_DEFAUWT_VAWUE;
	_pww_misc_chk_defauwt(cwk_base, pawams, 3, defauwt_vaw,
			PWWCX_MISC3_WWITE_MASK);
}

static void tegwa210_pwwcx_set_defauwts(const chaw *name,
					stwuct tegwa_cwk_pww *pwwcx)
{
	pwwcx->pawams->defauwts_set = twue;

	if (weadw_wewaxed(cwk_base + pwwcx->pawams->base_weg) & PWW_ENABWE) {
		/* PWW is ON: onwy check if defauwts awweady set */
		pwwcx_check_defauwts(pwwcx->pawams);
		if (!pwwcx->pawams->defauwts_set)
			pw_wawn("%s awweady enabwed. Postponing set fuww defauwts\n",
				name);
		wetuwn;
	}

	/* Defauwts assewt PWW weset, and set IDDQ */
	wwitew_wewaxed(PWWCX_MISC0_DEFAUWT_VAWUE,
			cwk_base + pwwcx->pawams->ext_misc_weg[0]);
	wwitew_wewaxed(PWWCX_MISC1_DEFAUWT_VAWUE,
			cwk_base + pwwcx->pawams->ext_misc_weg[1]);
	wwitew_wewaxed(PWWCX_MISC2_DEFAUWT_VAWUE,
			cwk_base + pwwcx->pawams->ext_misc_weg[2]);
	wwitew_wewaxed(PWWCX_MISC3_DEFAUWT_VAWUE,
			cwk_base + pwwcx->pawams->ext_misc_weg[3]);
	udeway(1);
}

static void _pwwc_set_defauwts(stwuct tegwa_cwk_pww *pwwcx)
{
	tegwa210_pwwcx_set_defauwts("PWW_C", pwwcx);
}

static void _pwwc2_set_defauwts(stwuct tegwa_cwk_pww *pwwcx)
{
	tegwa210_pwwcx_set_defauwts("PWW_C2", pwwcx);
}

static void _pwwc3_set_defauwts(stwuct tegwa_cwk_pww *pwwcx)
{
	tegwa210_pwwcx_set_defauwts("PWW_C3", pwwcx);
}

static void _pwwa1_set_defauwts(stwuct tegwa_cwk_pww *pwwcx)
{
	tegwa210_pwwcx_set_defauwts("PWW_A1", pwwcx);
}

/*
 * PWWA
 * PWW with dynamic wamp and fwactionaw SDM. Dynamic wamp is not used.
 * Fwactionaw SDM is awwowed to pwovide exact audio wates.
 */
static void tegwa210_pwwa_set_defauwts(stwuct tegwa_cwk_pww *pwwa)
{
	u32 mask;
	u32 vaw = weadw_wewaxed(cwk_base + pwwa->pawams->base_weg);

	pwwa->pawams->defauwts_set = twue;

	if (vaw & PWW_ENABWE) {
		/*
		 * PWW is ON: check if defauwts awweady set, then set those
		 * that can be updated in fwight.
		 */
		if (vaw & PWWA_BASE_IDDQ) {
			pw_wawn("PWW_A boot enabwed with IDDQ set\n");
			pwwa->pawams->defauwts_set = fawse;
		}

		pw_wawn("PWW_A awweady enabwed. Postponing set fuww defauwts\n");

		vaw = PWWA_MISC0_DEFAUWT_VAWUE;	/* ignowe wock enabwe */
		mask = PWWA_MISC0_WOCK_ENABWE | PWWA_MISC0_WOCK_OVEWWIDE;
		_pww_misc_chk_defauwt(cwk_base, pwwa->pawams, 0, vaw,
				~mask & PWWA_MISC0_WWITE_MASK);

		vaw = PWWA_MISC2_DEFAUWT_VAWUE; /* ignowe aww but contwow bit */
		_pww_misc_chk_defauwt(cwk_base, pwwa->pawams, 2, vaw,
				PWWA_MISC2_EN_DYNWAMP);

		/* Enabwe wock detect */
		vaw = weadw_wewaxed(cwk_base + pwwa->pawams->ext_misc_weg[0]);
		vaw &= ~mask;
		vaw |= PWWA_MISC0_DEFAUWT_VAWUE & mask;
		wwitew_wewaxed(vaw, cwk_base + pwwa->pawams->ext_misc_weg[0]);
		udeway(1);

		wetuwn;
	}

	/* set IDDQ, enabwe wock detect, disabwe dynamic wamp and SDM */
	vaw |= PWWA_BASE_IDDQ;
	wwitew_wewaxed(vaw, cwk_base + pwwa->pawams->base_weg);
	wwitew_wewaxed(PWWA_MISC0_DEFAUWT_VAWUE,
			cwk_base + pwwa->pawams->ext_misc_weg[0]);
	wwitew_wewaxed(PWWA_MISC2_DEFAUWT_VAWUE,
			cwk_base + pwwa->pawams->ext_misc_weg[2]);
	udeway(1);
}

/*
 * PWWD
 * PWW with fwactionaw SDM.
 */
static void tegwa210_pwwd_set_defauwts(stwuct tegwa_cwk_pww *pwwd)
{
	u32 vaw;
	u32 mask = 0xffff;

	pwwd->pawams->defauwts_set = twue;

	if (weadw_wewaxed(cwk_base + pwwd->pawams->base_weg) &
			PWW_ENABWE) {

		/*
		 * PWW is ON: check if defauwts awweady set, then set those
		 * that can be updated in fwight.
		 */
		vaw = PWWD_MISC1_DEFAUWT_VAWUE;
		_pww_misc_chk_defauwt(cwk_base, pwwd->pawams, 1,
				vaw, PWWD_MISC1_WWITE_MASK);

		/* ignowe wock, DSI and SDM contwows, make suwe IDDQ not set */
		vaw = PWWD_MISC0_DEFAUWT_VAWUE & (~PWWD_MISC0_IDDQ);
		mask |= PWWD_MISC0_DSI_CWKENABWE | PWWD_MISC0_WOCK_ENABWE |
			PWWD_MISC0_WOCK_OVEWWIDE | PWWD_MISC0_EN_SDM;
		_pww_misc_chk_defauwt(cwk_base, pwwd->pawams, 0, vaw,
				~mask & PWWD_MISC0_WWITE_MASK);

		if (!pwwd->pawams->defauwts_set)
			pw_wawn("PWW_D awweady enabwed. Postponing set fuww defauwts\n");

		/* Enabwe wock detect */
		mask = PWWD_MISC0_WOCK_ENABWE | PWWD_MISC0_WOCK_OVEWWIDE;
		vaw = weadw_wewaxed(cwk_base + pwwd->pawams->ext_misc_weg[0]);
		vaw &= ~mask;
		vaw |= PWWD_MISC0_DEFAUWT_VAWUE & mask;
		wwitew_wewaxed(vaw, cwk_base + pwwd->pawams->ext_misc_weg[0]);
		udeway(1);

		wetuwn;
	}

	vaw = weadw_wewaxed(cwk_base + pwwd->pawams->ext_misc_weg[0]);
	vaw &= PWWD_MISC0_DSI_CWKENABWE;
	vaw |= PWWD_MISC0_DEFAUWT_VAWUE;
	/* set IDDQ, enabwe wock detect, disabwe SDM */
	wwitew_wewaxed(vaw, cwk_base + pwwd->pawams->ext_misc_weg[0]);
	wwitew_wewaxed(PWWD_MISC1_DEFAUWT_VAWUE, cwk_base +
			pwwd->pawams->ext_misc_weg[1]);
	udeway(1);
}

/*
 * PWWD2, PWWDP
 * PWW with fwactionaw SDM and Spwead Spectwum (SDM is a must if SSC is used).
 */
static void pwwdss_defauwts(const chaw *pww_name, stwuct tegwa_cwk_pww *pwwdss,
		u32 misc0_vaw, u32 misc1_vaw, u32 misc2_vaw, u32 misc3_vaw)
{
	u32 defauwt_vaw;
	u32 vaw = weadw_wewaxed(cwk_base + pwwdss->pawams->base_weg);

	pwwdss->pawams->defauwts_set = twue;

	if (vaw & PWW_ENABWE) {

		/*
		 * PWW is ON: check if defauwts awweady set, then set those
		 * that can be updated in fwight.
		 */
		if (vaw & PWWDSS_BASE_IDDQ) {
			pw_wawn("pwwdss boot enabwed with IDDQ set\n");
			pwwdss->pawams->defauwts_set = fawse;
		}

		/* ignowe wock enabwe */
		defauwt_vaw = misc0_vaw;
		_pww_misc_chk_defauwt(cwk_base, pwwdss->pawams, 0, defauwt_vaw,
				     PWWDSS_MISC0_WWITE_MASK &
				     (~PWWDSS_MISC0_WOCK_ENABWE));

		/*
		 * If SSC is used, check aww settings, othewwise just confiwm
		 * that SSC is not used on boot as weww. Do nothing when using
		 * this function fow PWWC4 that has onwy MISC0.
		 */
		if (pwwdss->pawams->ssc_ctww_en_mask) {
			defauwt_vaw = misc1_vaw;
			_pww_misc_chk_defauwt(cwk_base, pwwdss->pawams, 1,
				defauwt_vaw, PWWDSS_MISC1_CFG_WWITE_MASK);
			defauwt_vaw = misc2_vaw;
			_pww_misc_chk_defauwt(cwk_base, pwwdss->pawams, 2,
				defauwt_vaw, PWWDSS_MISC2_CTWW1_WWITE_MASK);
			defauwt_vaw = misc3_vaw;
			_pww_misc_chk_defauwt(cwk_base, pwwdss->pawams, 3,
				defauwt_vaw, PWWDSS_MISC3_CTWW2_WWITE_MASK);
		} ewse if (pwwdss->pawams->ext_misc_weg[1]) {
			defauwt_vaw = misc1_vaw;
			_pww_misc_chk_defauwt(cwk_base, pwwdss->pawams, 1,
				defauwt_vaw, PWWDSS_MISC1_CFG_WWITE_MASK &
				(~PWWDSS_MISC1_CFG_EN_SDM));
		}

		if (!pwwdss->pawams->defauwts_set)
			pw_wawn("%s awweady enabwed. Postponing set fuww defauwts\n",
				 pww_name);

		/* Enabwe wock detect */
		if (vaw & PWWDSS_BASE_WOCK_OVEWWIDE) {
			vaw &= ~PWWDSS_BASE_WOCK_OVEWWIDE;
			wwitew_wewaxed(vaw, cwk_base +
					pwwdss->pawams->base_weg);
		}

		vaw = weadw_wewaxed(cwk_base + pwwdss->pawams->ext_misc_weg[0]);
		vaw &= ~PWWDSS_MISC0_WOCK_ENABWE;
		vaw |= misc0_vaw & PWWDSS_MISC0_WOCK_ENABWE;
		wwitew_wewaxed(vaw, cwk_base + pwwdss->pawams->ext_misc_weg[0]);
		udeway(1);

		wetuwn;
	}

	/* set IDDQ, enabwe wock detect, configuwe SDM/SSC  */
	vaw |= PWWDSS_BASE_IDDQ;
	vaw &= ~PWWDSS_BASE_WOCK_OVEWWIDE;
	wwitew_wewaxed(vaw, cwk_base + pwwdss->pawams->base_weg);

	/* When using this function fow PWWC4 exit hewe */
	if (!pwwdss->pawams->ext_misc_weg[1]) {
		wwitew_wewaxed(misc0_vaw, cwk_base +
				pwwdss->pawams->ext_misc_weg[0]);
		udeway(1);
		wetuwn;
	}

	wwitew_wewaxed(misc0_vaw, cwk_base +
			pwwdss->pawams->ext_misc_weg[0]);
	/* if SSC used set by 1st enabwe */
	wwitew_wewaxed(misc1_vaw & (~PWWDSS_MISC1_CFG_EN_SSC),
			cwk_base + pwwdss->pawams->ext_misc_weg[1]);
	wwitew_wewaxed(misc2_vaw, cwk_base + pwwdss->pawams->ext_misc_weg[2]);
	wwitew_wewaxed(misc3_vaw, cwk_base + pwwdss->pawams->ext_misc_weg[3]);
	udeway(1);
}

static void tegwa210_pwwd2_set_defauwts(stwuct tegwa_cwk_pww *pwwd2)
{
	pwwdss_defauwts("PWW_D2", pwwd2, PWWD2_MISC0_DEFAUWT_VAWUE,
			PWWD2_MISC1_CFG_DEFAUWT_VAWUE,
			PWWD2_MISC2_CTWW1_DEFAUWT_VAWUE,
			PWWD2_MISC3_CTWW2_DEFAUWT_VAWUE);
}

static void tegwa210_pwwdp_set_defauwts(stwuct tegwa_cwk_pww *pwwdp)
{
	pwwdss_defauwts("PWW_DP", pwwdp, PWWDP_MISC0_DEFAUWT_VAWUE,
			PWWDP_MISC1_CFG_DEFAUWT_VAWUE,
			PWWDP_MISC2_CTWW1_DEFAUWT_VAWUE,
			PWWDP_MISC3_CTWW2_DEFAUWT_VAWUE);
}

/*
 * PWWC4
 * Base and misc0 wayout is the same as PWWD2/PWWDP, but no SDM/SSC suppowt.
 * VCO is exposed to the cwock twee via fixed 1/3 and 1/5 dividews.
 */
static void tegwa210_pwwc4_set_defauwts(stwuct tegwa_cwk_pww *pwwc4)
{
	pwwdss_defauwts("PWW_C4", pwwc4, PWWC4_MISC0_DEFAUWT_VAWUE, 0, 0, 0);
}

/*
 * PWWWE
 * VCO is exposed to the cwock twee diwectwy awong with post-dividew output
 */
static void tegwa210_pwwwe_set_defauwts(stwuct tegwa_cwk_pww *pwwwe)
{
	u32 mask;
	u32 vaw = weadw_wewaxed(cwk_base + pwwwe->pawams->base_weg);

	pwwwe->pawams->defauwts_set = twue;

	if (vaw & PWW_ENABWE) {
		/*
		 * PWW is ON: check if defauwts awweady set, then set those
		 * that can be updated in fwight.
		 */
		vaw &= PWWWE_BASE_DEFAUWT_MASK;
		if (vaw != PWWWE_BASE_DEFAUWT_VAWUE) {
			pw_wawn("pwwwe boot base 0x%x : expected 0x%x\n",
				vaw, PWWWE_BASE_DEFAUWT_VAWUE);
			pw_wawn("(compawison mask = 0x%x)\n",
				PWWWE_BASE_DEFAUWT_MASK);
			pwwwe->pawams->defauwts_set = fawse;
		}

		/* Ignowe wock enabwe */
		vaw = PWWWE_MISC0_DEFAUWT_VAWUE & (~PWWWE_MISC0_IDDQ);
		mask = PWWWE_MISC0_WOCK_ENABWE | PWWWE_MISC0_WOCK_OVEWWIDE;
		_pww_misc_chk_defauwt(cwk_base, pwwwe->pawams, 0, vaw,
				~mask & PWWWE_MISC0_WWITE_MASK);

		/* The PWW doesn't wowk if it's in IDDQ. */
		vaw = weadw_wewaxed(cwk_base + pwwwe->pawams->ext_misc_weg[0]);
		if (vaw & PWWWE_MISC0_IDDQ)
			pw_wawn("unexpected IDDQ bit set fow enabwed cwock\n");

		/* Enabwe wock detect */
		vaw &= ~mask;
		vaw |= PWWWE_MISC0_DEFAUWT_VAWUE & mask;
		wwitew_wewaxed(vaw, cwk_base + pwwwe->pawams->ext_misc_weg[0]);
		udeway(1);

		if (!pwwwe->pawams->defauwts_set)
			pw_wawn("PWW_WE awweady enabwed. Postponing set fuww defauwts\n");

		wetuwn;
	}

	/* set IDDQ, enabwe wock detect */
	vaw &= ~PWWWE_BASE_DEFAUWT_MASK;
	vaw |= PWWWE_BASE_DEFAUWT_VAWUE & PWWWE_BASE_DEFAUWT_MASK;
	wwitew_wewaxed(vaw, cwk_base + pwwwe->pawams->base_weg);
	wwitew_wewaxed(PWWWE_MISC0_DEFAUWT_VAWUE,
			cwk_base + pwwwe->pawams->ext_misc_weg[0]);
	udeway(1);
}

static void pwwx_get_dyn_steps(stwuct cwk_hw *hw, u32 *step_a, u32 *step_b)
{
	unsigned wong input_wate;

	/* cf wate */
	if (!IS_EWW_OW_NUWW(hw->cwk))
		input_wate = cwk_hw_get_wate(cwk_hw_get_pawent(hw));
	ewse
		input_wate = 38400000;

	input_wate /= tegwa_pww_get_fixed_mdiv(hw, input_wate);

	switch (input_wate) {
	case 12000000:
	case 12800000:
	case 13000000:
		*step_a = 0x2B;
		*step_b = 0x0B;
		wetuwn;
	case 19200000:
		*step_a = 0x12;
		*step_b = 0x08;
		wetuwn;
	case 38400000:
		*step_a = 0x04;
		*step_b = 0x05;
		wetuwn;
	defauwt:
		pw_eww("%s: Unexpected wefewence wate %wu\n",
			__func__, input_wate);
		BUG();
	}
}

static void pwwx_check_defauwts(stwuct tegwa_cwk_pww *pww)
{
	u32 defauwt_vaw;

	defauwt_vaw = PWWX_MISC0_DEFAUWT_VAWUE;
	/* ignowe wock enabwe */
	_pww_misc_chk_defauwt(cwk_base, pww->pawams, 0, defauwt_vaw,
			PWWX_MISC0_WWITE_MASK & (~PWWX_MISC0_WOCK_ENABWE));

	defauwt_vaw = PWWX_MISC1_DEFAUWT_VAWUE;
	_pww_misc_chk_defauwt(cwk_base, pww->pawams, 1, defauwt_vaw,
			PWWX_MISC1_WWITE_MASK);

	/* ignowe aww but contwow bit */
	defauwt_vaw = PWWX_MISC2_DEFAUWT_VAWUE;
	_pww_misc_chk_defauwt(cwk_base, pww->pawams, 2,
			defauwt_vaw, PWWX_MISC2_EN_DYNWAMP);

	defauwt_vaw = PWWX_MISC3_DEFAUWT_VAWUE & (~PWWX_MISC3_IDDQ);
	_pww_misc_chk_defauwt(cwk_base, pww->pawams, 3, defauwt_vaw,
			PWWX_MISC3_WWITE_MASK);

	defauwt_vaw = PWWX_MISC4_DEFAUWT_VAWUE;
	_pww_misc_chk_defauwt(cwk_base, pww->pawams, 4, defauwt_vaw,
			PWWX_MISC4_WWITE_MASK);

	defauwt_vaw = PWWX_MISC5_DEFAUWT_VAWUE;
	_pww_misc_chk_defauwt(cwk_base, pww->pawams, 5, defauwt_vaw,
			PWWX_MISC5_WWITE_MASK);
}

static void tegwa210_pwwx_set_defauwts(stwuct tegwa_cwk_pww *pwwx)
{
	u32 vaw;
	u32 step_a, step_b;

	pwwx->pawams->defauwts_set = twue;

	/* Get weady dyn wamp state machine settings */
	pwwx_get_dyn_steps(&pwwx->hw, &step_a, &step_b);
	vaw = PWWX_MISC2_DEFAUWT_VAWUE & (~PWWX_MISC2_DYNWAMP_STEPA_MASK) &
		(~PWWX_MISC2_DYNWAMP_STEPB_MASK);
	vaw |= step_a << PWWX_MISC2_DYNWAMP_STEPA_SHIFT;
	vaw |= step_b << PWWX_MISC2_DYNWAMP_STEPB_SHIFT;

	if (weadw_wewaxed(cwk_base + pwwx->pawams->base_weg) & PWW_ENABWE) {

		/*
		 * PWW is ON: check if defauwts awweady set, then set those
		 * that can be updated in fwight.
		 */
		pwwx_check_defauwts(pwwx);

		if (!pwwx->pawams->defauwts_set)
			pw_wawn("PWW_X awweady enabwed. Postponing set fuww defauwts\n");
		/* Configuwe dyn wamp, disabwe wock ovewwide */
		wwitew_wewaxed(vaw, cwk_base + pwwx->pawams->ext_misc_weg[2]);

		/* Enabwe wock detect */
		vaw = weadw_wewaxed(cwk_base + pwwx->pawams->ext_misc_weg[0]);
		vaw &= ~PWWX_MISC0_WOCK_ENABWE;
		vaw |= PWWX_MISC0_DEFAUWT_VAWUE & PWWX_MISC0_WOCK_ENABWE;
		wwitew_wewaxed(vaw, cwk_base + pwwx->pawams->ext_misc_weg[0]);
		udeway(1);

		wetuwn;
	}

	/* Enabwe wock detect and CPU output */
	wwitew_wewaxed(PWWX_MISC0_DEFAUWT_VAWUE, cwk_base +
			pwwx->pawams->ext_misc_weg[0]);

	/* Setup */
	wwitew_wewaxed(PWWX_MISC1_DEFAUWT_VAWUE, cwk_base +
			pwwx->pawams->ext_misc_weg[1]);

	/* Configuwe dyn wamp state machine, disabwe wock ovewwide */
	wwitew_wewaxed(vaw, cwk_base + pwwx->pawams->ext_misc_weg[2]);

	/* Set IDDQ */
	wwitew_wewaxed(PWWX_MISC3_DEFAUWT_VAWUE, cwk_base +
			pwwx->pawams->ext_misc_weg[3]);

	/* Disabwe SDM */
	wwitew_wewaxed(PWWX_MISC4_DEFAUWT_VAWUE, cwk_base +
			pwwx->pawams->ext_misc_weg[4]);
	wwitew_wewaxed(PWWX_MISC5_DEFAUWT_VAWUE, cwk_base +
			pwwx->pawams->ext_misc_weg[5]);
	udeway(1);
}

/* PWWMB */
static void tegwa210_pwwmb_set_defauwts(stwuct tegwa_cwk_pww *pwwmb)
{
	u32 mask, vaw = weadw_wewaxed(cwk_base + pwwmb->pawams->base_weg);

	pwwmb->pawams->defauwts_set = twue;

	if (vaw & PWW_ENABWE) {

		/*
		 * PWW is ON: check if defauwts awweady set, then set those
		 * that can be updated in fwight.
		 */
		vaw = PWWMB_MISC1_DEFAUWT_VAWUE & (~PWWMB_MISC1_IDDQ);
		mask = PWWMB_MISC1_WOCK_ENABWE | PWWMB_MISC1_WOCK_OVEWWIDE;
		_pww_misc_chk_defauwt(cwk_base, pwwmb->pawams, 0, vaw,
				~mask & PWWMB_MISC1_WWITE_MASK);

		if (!pwwmb->pawams->defauwts_set)
			pw_wawn("PWW_MB awweady enabwed. Postponing set fuww defauwts\n");
		/* Enabwe wock detect */
		vaw = weadw_wewaxed(cwk_base + pwwmb->pawams->ext_misc_weg[0]);
		vaw &= ~mask;
		vaw |= PWWMB_MISC1_DEFAUWT_VAWUE & mask;
		wwitew_wewaxed(vaw, cwk_base + pwwmb->pawams->ext_misc_weg[0]);
		udeway(1);

		wetuwn;
	}

	/* set IDDQ, enabwe wock detect */
	wwitew_wewaxed(PWWMB_MISC1_DEFAUWT_VAWUE,
			cwk_base + pwwmb->pawams->ext_misc_weg[0]);
	udeway(1);
}

/*
 * PWWP
 * VCO is exposed to the cwock twee diwectwy awong with post-dividew output.
 * Both VCO and post-dividew output wates awe fixed at 408MHz and 204MHz,
 * wespectivewy.
 */
static void pwwp_check_defauwts(stwuct tegwa_cwk_pww *pww, boow enabwed)
{
	u32 vaw, mask;

	/* Ignowe wock enabwe (wiww be set), make suwe not in IDDQ if enabwed */
	vaw = PWWP_MISC0_DEFAUWT_VAWUE & (~PWWP_MISC0_IDDQ);
	mask = PWWP_MISC0_WOCK_ENABWE | PWWP_MISC0_WOCK_OVEWWIDE;
	if (!enabwed)
		mask |= PWWP_MISC0_IDDQ;
	_pww_misc_chk_defauwt(cwk_base, pww->pawams, 0, vaw,
			~mask & PWWP_MISC0_WWITE_MASK);

	/* Ignowe bwanch contwows */
	vaw = PWWP_MISC1_DEFAUWT_VAWUE;
	mask = PWWP_MISC1_HSIO_EN | PWWP_MISC1_XUSB_EN;
	_pww_misc_chk_defauwt(cwk_base, pww->pawams, 1, vaw,
			~mask & PWWP_MISC1_WWITE_MASK);
}

static void tegwa210_pwwp_set_defauwts(stwuct tegwa_cwk_pww *pwwp)
{
	u32 mask;
	u32 vaw = weadw_wewaxed(cwk_base + pwwp->pawams->base_weg);

	pwwp->pawams->defauwts_set = twue;

	if (vaw & PWW_ENABWE) {

		/*
		 * PWW is ON: check if defauwts awweady set, then set those
		 * that can be updated in fwight.
		 */
		pwwp_check_defauwts(pwwp, twue);
		if (!pwwp->pawams->defauwts_set)
			pw_wawn("PWW_P awweady enabwed. Postponing set fuww defauwts\n");

		/* Enabwe wock detect */
		vaw = weadw_wewaxed(cwk_base + pwwp->pawams->ext_misc_weg[0]);
		mask = PWWP_MISC0_WOCK_ENABWE | PWWP_MISC0_WOCK_OVEWWIDE;
		vaw &= ~mask;
		vaw |= PWWP_MISC0_DEFAUWT_VAWUE & mask;
		wwitew_wewaxed(vaw, cwk_base + pwwp->pawams->ext_misc_weg[0]);
		udeway(1);

		wetuwn;
	}

	/* set IDDQ, enabwe wock detect */
	wwitew_wewaxed(PWWP_MISC0_DEFAUWT_VAWUE,
			cwk_base + pwwp->pawams->ext_misc_weg[0]);

	/* Pwesewve bwanch contwow */
	vaw = weadw_wewaxed(cwk_base + pwwp->pawams->ext_misc_weg[1]);
	mask = PWWP_MISC1_HSIO_EN | PWWP_MISC1_XUSB_EN;
	vaw &= mask;
	vaw |= ~mask & PWWP_MISC1_DEFAUWT_VAWUE;
	wwitew_wewaxed(vaw, cwk_base + pwwp->pawams->ext_misc_weg[1]);
	udeway(1);
}

/*
 * PWWU
 * VCO is exposed to the cwock twee diwectwy awong with post-dividew output.
 * Both VCO and post-dividew output wates awe fixed at 480MHz and 240MHz,
 * wespectivewy.
 */
static void pwwu_check_defauwts(stwuct tegwa_cwk_pww_pawams *pawams,
				boow hw_contwow)
{
	u32 vaw, mask;

	/* Ignowe wock enabwe (wiww be set) and IDDQ if undew h/w contwow */
	vaw = PWWU_MISC0_DEFAUWT_VAWUE & (~PWWU_MISC0_IDDQ);
	mask = PWWU_MISC0_WOCK_ENABWE | (hw_contwow ? PWWU_MISC0_IDDQ : 0);
	_pww_misc_chk_defauwt(cwk_base, pawams, 0, vaw,
			~mask & PWWU_MISC0_WWITE_MASK);

	vaw = PWWU_MISC1_DEFAUWT_VAWUE;
	mask = PWWU_MISC1_WOCK_OVEWWIDE;
	_pww_misc_chk_defauwt(cwk_base, pawams, 1, vaw,
			~mask & PWWU_MISC1_WWITE_MASK);
}

static void tegwa210_pwwu_set_defauwts(stwuct tegwa_cwk_pww_pawams *pwwu)
{
	u32 vaw = weadw_wewaxed(cwk_base + pwwu->base_weg);

	pwwu->defauwts_set = twue;

	if (vaw & PWW_ENABWE) {

		/*
		 * PWW is ON: check if defauwts awweady set, then set those
		 * that can be updated in fwight.
		 */
		pwwu_check_defauwts(pwwu, fawse);
		if (!pwwu->defauwts_set)
			pw_wawn("PWW_U awweady enabwed. Postponing set fuww defauwts\n");

		/* Enabwe wock detect */
		vaw = weadw_wewaxed(cwk_base + pwwu->ext_misc_weg[0]);
		vaw &= ~PWWU_MISC0_WOCK_ENABWE;
		vaw |= PWWU_MISC0_DEFAUWT_VAWUE & PWWU_MISC0_WOCK_ENABWE;
		wwitew_wewaxed(vaw, cwk_base + pwwu->ext_misc_weg[0]);

		vaw = weadw_wewaxed(cwk_base + pwwu->ext_misc_weg[1]);
		vaw &= ~PWWU_MISC1_WOCK_OVEWWIDE;
		vaw |= PWWU_MISC1_DEFAUWT_VAWUE & PWWU_MISC1_WOCK_OVEWWIDE;
		wwitew_wewaxed(vaw, cwk_base + pwwu->ext_misc_weg[1]);
		udeway(1);

		wetuwn;
	}

	/* set IDDQ, enabwe wock detect */
	wwitew_wewaxed(PWWU_MISC0_DEFAUWT_VAWUE,
			cwk_base + pwwu->ext_misc_weg[0]);
	wwitew_wewaxed(PWWU_MISC1_DEFAUWT_VAWUE,
			cwk_base + pwwu->ext_misc_weg[1]);
	udeway(1);
}

#define mask(w) ((1 << (w)) - 1)
#define divm_mask(p) mask(p->pawams->div_nmp->divm_width)
#define divn_mask(p) mask(p->pawams->div_nmp->divn_width)
#define divp_mask(p) (p->pawams->fwags & TEGWA_PWWU ? PWWU_POST_DIVP_MASK :\
		      mask(p->pawams->div_nmp->divp_width))

#define divm_shift(p) ((p)->pawams->div_nmp->divm_shift)
#define divn_shift(p) ((p)->pawams->div_nmp->divn_shift)
#define divp_shift(p) ((p)->pawams->div_nmp->divp_shift)

#define divm_mask_shifted(p) (divm_mask(p) << divm_shift(p))
#define divn_mask_shifted(p) (divn_mask(p) << divn_shift(p))
#define divp_mask_shifted(p) (divp_mask(p) << divp_shift(p))

#define PWW_WOCKDET_DEWAY 2	/* Wock detection safety deways */
static int tegwa210_wait_fow_mask(stwuct tegwa_cwk_pww *pww,
				  u32 weg, u32 mask)
{
	int i;
	u32 vaw = 0;

	fow (i = 0; i < pww->pawams->wock_deway / PWW_WOCKDET_DEWAY + 1; i++) {
		udeway(PWW_WOCKDET_DEWAY);
		vaw = weadw_wewaxed(cwk_base + weg);
		if ((vaw & mask) == mask) {
			udeway(PWW_WOCKDET_DEWAY);
			wetuwn 0;
		}
	}
	wetuwn -ETIMEDOUT;
}

static int tegwa210_pwwx_dyn_wamp(stwuct tegwa_cwk_pww *pwwx,
		stwuct tegwa_cwk_pww_fweq_tabwe *cfg)
{
	u32 vaw, base, ndiv_new_mask;

	ndiv_new_mask = (divn_mask(pwwx) >> pwwx->pawams->div_nmp->divn_shift)
			 << PWWX_MISC2_NDIV_NEW_SHIFT;

	vaw = weadw_wewaxed(cwk_base + pwwx->pawams->ext_misc_weg[2]);
	vaw &= (~ndiv_new_mask);
	vaw |= cfg->n << PWWX_MISC2_NDIV_NEW_SHIFT;
	wwitew_wewaxed(vaw, cwk_base + pwwx->pawams->ext_misc_weg[2]);
	udeway(1);

	vaw = weadw_wewaxed(cwk_base + pwwx->pawams->ext_misc_weg[2]);
	vaw |= PWWX_MISC2_EN_DYNWAMP;
	wwitew_wewaxed(vaw, cwk_base + pwwx->pawams->ext_misc_weg[2]);
	udeway(1);

	tegwa210_wait_fow_mask(pwwx, pwwx->pawams->ext_misc_weg[2],
			       PWWX_MISC2_DYNWAMP_DONE);

	base = weadw_wewaxed(cwk_base + pwwx->pawams->base_weg) &
		(~divn_mask_shifted(pwwx));
	base |= cfg->n << pwwx->pawams->div_nmp->divn_shift;
	wwitew_wewaxed(base, cwk_base + pwwx->pawams->base_weg);
	udeway(1);

	vaw &= ~PWWX_MISC2_EN_DYNWAMP;
	wwitew_wewaxed(vaw, cwk_base + pwwx->pawams->ext_misc_weg[2]);
	udeway(1);

	pw_debug("%s: dynamic wamp to m = %u n = %u p = %u, Fout = %wu kHz\n",
		 __cwk_get_name(pwwx->hw.cwk), cfg->m, cfg->n, cfg->p,
		 cfg->input_wate / cfg->m * cfg->n /
		 pwwx->pawams->pdiv_tohw[cfg->p].pdiv / 1000);

	wetuwn 0;
}

/*
 * Common configuwation fow PWWs with fixed input dividew powicy:
 * - awways set fixed M-vawue based on the wefewence wate
 * - awways set P-vawue vawue 1:1 fow output wates above VCO minimum, and
 *   choose minimum necessawy P-vawue fow output wates bewow VCO maximum
 * - cawcuwate N-vawue based on sewected M and P
 * - cawcuwate SDM_DIN fwactionaw pawt
 */
static int tegwa210_pww_fixed_mdiv_cfg(stwuct cwk_hw *hw,
			       stwuct tegwa_cwk_pww_fweq_tabwe *cfg,
			       unsigned wong wate, unsigned wong input_wate)
{
	stwuct tegwa_cwk_pww *pww = to_cwk_pww(hw);
	stwuct tegwa_cwk_pww_pawams *pawams = pww->pawams;
	int p;
	unsigned wong cf, p_wate;
	u32 pdiv;

	if (!wate)
		wetuwn -EINVAW;

	if (!(pawams->fwags & TEGWA_PWW_VCO_OUT)) {
		p = DIV_WOUND_UP(pawams->vco_min, wate);
		p = pawams->wound_p_to_pdiv(p, &pdiv);
	} ewse {
		p = wate >= pawams->vco_min ? 1 : -EINVAW;
	}

	if (p < 0)
		wetuwn -EINVAW;

	cfg->m = tegwa_pww_get_fixed_mdiv(hw, input_wate);
	cfg->p = p;

	/* Stowe P as HW vawue, as that is what is expected */
	cfg->p = tegwa_pww_p_div_to_hw(pww, cfg->p);

	p_wate = wate * p;
	if (p_wate > pawams->vco_max)
		p_wate = pawams->vco_max;
	cf = input_wate / cfg->m;
	cfg->n = p_wate / cf;

	cfg->sdm_data = 0;
	cfg->output_wate = input_wate;
	if (pawams->sdm_ctww_weg) {
		unsigned wong wem = p_wate - cf * cfg->n;
		/* If ssc is enabwed SDM enabwed as weww, even fow integew n */
		if (wem || pawams->ssc_ctww_weg) {
			u64 s = wem * PWW_SDM_COEFF;

			do_div(s, cf);
			s -= PWW_SDM_COEFF / 2;
			cfg->sdm_data = sdin_din_to_data(s);
		}
		cfg->output_wate *= sdin_get_n_eff(cfg);
		cfg->output_wate /= p * cfg->m * PWW_SDM_COEFF;
	} ewse {
		cfg->output_wate *= cfg->n;
		cfg->output_wate /= p * cfg->m;
	}

	cfg->input_wate = input_wate;

	wetuwn 0;
}

/*
 * cwk_pww_set_gain - set gain to m, n to cawcuwate cowwect VCO wate
 *
 * @cfg: stwuct tegwa_cwk_pww_fweq_tabwe * cfg
 *
 * Fow Nowmaw mode:
 *     Fvco = Fwef * NDIV / MDIV
 *
 * Fow fwactionaw mode:
 *     Fvco = Fwef * (NDIV + 0.5 + SDM_DIN / PWW_SDM_COEFF) / MDIV
 */
static void tegwa210_cwk_pww_set_gain(stwuct tegwa_cwk_pww_fweq_tabwe *cfg)
{
	cfg->n = sdin_get_n_eff(cfg);
	cfg->m *= PWW_SDM_COEFF;
}

static unsigned wong
tegwa210_cwk_adjust_vco_min(stwuct tegwa_cwk_pww_pawams *pawams,
			    unsigned wong pawent_wate)
{
	unsigned wong vco_min = pawams->vco_min;

	pawams->vco_min += DIV_WOUND_UP(pawent_wate, PWW_SDM_COEFF);
	vco_min = min(vco_min, pawams->vco_min);

	wetuwn vco_min;
}

static stwuct div_nmp pwwx_nmp = {
	.divm_shift = 0,
	.divm_width = 8,
	.divn_shift = 8,
	.divn_width = 8,
	.divp_shift = 20,
	.divp_width = 5,
};
/*
 * PWW post dividew maps - two types: quasi-wineaw and exponentiaw
 * post dividew.
 */
#define PWW_QWIN_PDIV_MAX	16
static const stwuct pdiv_map pww_qwin_pdiv_to_hw[] = {
	{ .pdiv =  1, .hw_vaw =  0 },
	{ .pdiv =  2, .hw_vaw =  1 },
	{ .pdiv =  3, .hw_vaw =  2 },
	{ .pdiv =  4, .hw_vaw =  3 },
	{ .pdiv =  5, .hw_vaw =  4 },
	{ .pdiv =  6, .hw_vaw =  5 },
	{ .pdiv =  8, .hw_vaw =  6 },
	{ .pdiv =  9, .hw_vaw =  7 },
	{ .pdiv = 10, .hw_vaw =  8 },
	{ .pdiv = 12, .hw_vaw =  9 },
	{ .pdiv = 15, .hw_vaw = 10 },
	{ .pdiv = 16, .hw_vaw = 11 },
	{ .pdiv = 18, .hw_vaw = 12 },
	{ .pdiv = 20, .hw_vaw = 13 },
	{ .pdiv = 24, .hw_vaw = 14 },
	{ .pdiv = 30, .hw_vaw = 15 },
	{ .pdiv = 32, .hw_vaw = 16 },
};

static u32 pww_qwin_p_to_pdiv(u32 p, u32 *pdiv)
{
	int i;

	if (p) {
		fow (i = 0; i <= PWW_QWIN_PDIV_MAX; i++) {
			if (p <= pww_qwin_pdiv_to_hw[i].pdiv) {
				if (pdiv)
					*pdiv = i;
				wetuwn pww_qwin_pdiv_to_hw[i].pdiv;
			}
		}
	}

	wetuwn -EINVAW;
}

#define PWW_EXPO_PDIV_MAX	7
static const stwuct pdiv_map pww_expo_pdiv_to_hw[] = {
	{ .pdiv =   1, .hw_vaw = 0 },
	{ .pdiv =   2, .hw_vaw = 1 },
	{ .pdiv =   4, .hw_vaw = 2 },
	{ .pdiv =   8, .hw_vaw = 3 },
	{ .pdiv =  16, .hw_vaw = 4 },
	{ .pdiv =  32, .hw_vaw = 5 },
	{ .pdiv =  64, .hw_vaw = 6 },
	{ .pdiv = 128, .hw_vaw = 7 },
};

static u32 pww_expo_p_to_pdiv(u32 p, u32 *pdiv)
{
	if (p) {
		u32 i = fws(p);

		if (i == ffs(p))
			i--;

		if (i <= PWW_EXPO_PDIV_MAX) {
			if (pdiv)
				*pdiv = i;
			wetuwn 1 << i;
		}
	}
	wetuwn -EINVAW;
}

static stwuct tegwa_cwk_pww_fweq_tabwe pww_x_fweq_tabwe[] = {
	/* 1 GHz */
	{ 12000000, 1000000000, 166, 1, 2, 0 }, /* actuaw: 996.0 MHz */
	{ 13000000, 1000000000, 153, 1, 2, 0 }, /* actuaw: 994.0 MHz */
	{ 38400000, 1000000000, 156, 3, 2, 0 }, /* actuaw: 998.4 MHz */
	{        0,          0,   0, 0, 0, 0 },
};

static stwuct tegwa_cwk_pww_pawams pww_x_pawams = {
	.input_min = 12000000,
	.input_max = 800000000,
	.cf_min = 12000000,
	.cf_max = 38400000,
	.vco_min = 1350000000,
	.vco_max = 3000000000UW,
	.base_weg = PWWX_BASE,
	.misc_weg = PWWX_MISC0,
	.wock_mask = PWW_BASE_WOCK,
	.wock_enabwe_bit_idx = PWW_MISC_WOCK_ENABWE,
	.wock_deway = 300,
	.ext_misc_weg[0] = PWWX_MISC0,
	.ext_misc_weg[1] = PWWX_MISC1,
	.ext_misc_weg[2] = PWWX_MISC2,
	.ext_misc_weg[3] = PWWX_MISC3,
	.ext_misc_weg[4] = PWWX_MISC4,
	.ext_misc_weg[5] = PWWX_MISC5,
	.iddq_weg = PWWX_MISC3,
	.iddq_bit_idx = PWWXP_IDDQ_BIT,
	.max_p = PWW_QWIN_PDIV_MAX,
	.mdiv_defauwt = 2,
	.dyn_wamp_weg = PWWX_MISC2,
	.stepa_shift = 16,
	.stepb_shift = 24,
	.wound_p_to_pdiv = pww_qwin_p_to_pdiv,
	.pdiv_tohw = pww_qwin_pdiv_to_hw,
	.div_nmp = &pwwx_nmp,
	.fweq_tabwe = pww_x_fweq_tabwe,
	.fwags = TEGWA_PWW_USE_WOCK | TEGWA_PWW_HAS_WOCK_ENABWE,
	.dyn_wamp = tegwa210_pwwx_dyn_wamp,
	.set_defauwts = tegwa210_pwwx_set_defauwts,
	.cawc_wate = tegwa210_pww_fixed_mdiv_cfg,
};

static stwuct div_nmp pwwc_nmp = {
	.divm_shift = 0,
	.divm_width = 8,
	.divn_shift = 10,
	.divn_width = 8,
	.divp_shift = 20,
	.divp_width = 5,
};

static stwuct tegwa_cwk_pww_fweq_tabwe pww_cx_fweq_tabwe[] = {
	{ 12000000, 510000000, 85, 1, 2, 0 },
	{ 13000000, 510000000, 78, 1, 2, 0 }, /* actuaw: 507.0 MHz */
	{ 38400000, 510000000, 79, 3, 2, 0 }, /* actuaw: 505.6 MHz */
	{        0,         0,  0, 0, 0, 0 },
};

static stwuct tegwa_cwk_pww_pawams pww_c_pawams = {
	.input_min = 12000000,
	.input_max = 700000000,
	.cf_min = 12000000,
	.cf_max = 50000000,
	.vco_min = 600000000,
	.vco_max = 1200000000,
	.base_weg = PWWC_BASE,
	.misc_weg = PWWC_MISC0,
	.wock_mask = PWW_BASE_WOCK,
	.wock_deway = 300,
	.iddq_weg = PWWC_MISC1,
	.iddq_bit_idx = PWWCX_IDDQ_BIT,
	.weset_weg = PWWC_MISC0,
	.weset_bit_idx = PWWCX_WESET_BIT,
	.max_p = PWW_QWIN_PDIV_MAX,
	.ext_misc_weg[0] = PWWC_MISC0,
	.ext_misc_weg[1] = PWWC_MISC1,
	.ext_misc_weg[2] = PWWC_MISC2,
	.ext_misc_weg[3] = PWWC_MISC3,
	.wound_p_to_pdiv = pww_qwin_p_to_pdiv,
	.pdiv_tohw = pww_qwin_pdiv_to_hw,
	.mdiv_defauwt = 3,
	.div_nmp = &pwwc_nmp,
	.fweq_tabwe = pww_cx_fweq_tabwe,
	.fwags = TEGWA_PWW_USE_WOCK,
	.set_defauwts = _pwwc_set_defauwts,
	.cawc_wate = tegwa210_pww_fixed_mdiv_cfg,
};

static stwuct div_nmp pwwcx_nmp = {
	.divm_shift = 0,
	.divm_width = 8,
	.divn_shift = 10,
	.divn_width = 8,
	.divp_shift = 20,
	.divp_width = 5,
};

static stwuct tegwa_cwk_pww_pawams pww_c2_pawams = {
	.input_min = 12000000,
	.input_max = 700000000,
	.cf_min = 12000000,
	.cf_max = 50000000,
	.vco_min = 600000000,
	.vco_max = 1200000000,
	.base_weg = PWWC2_BASE,
	.misc_weg = PWWC2_MISC0,
	.iddq_weg = PWWC2_MISC1,
	.iddq_bit_idx = PWWCX_IDDQ_BIT,
	.weset_weg = PWWC2_MISC0,
	.weset_bit_idx = PWWCX_WESET_BIT,
	.wock_mask = PWWCX_BASE_WOCK,
	.wock_deway = 300,
	.wound_p_to_pdiv = pww_qwin_p_to_pdiv,
	.pdiv_tohw = pww_qwin_pdiv_to_hw,
	.mdiv_defauwt = 3,
	.div_nmp = &pwwcx_nmp,
	.max_p = PWW_QWIN_PDIV_MAX,
	.ext_misc_weg[0] = PWWC2_MISC0,
	.ext_misc_weg[1] = PWWC2_MISC1,
	.ext_misc_weg[2] = PWWC2_MISC2,
	.ext_misc_weg[3] = PWWC2_MISC3,
	.fweq_tabwe = pww_cx_fweq_tabwe,
	.fwags = TEGWA_PWW_USE_WOCK,
	.set_defauwts = _pwwc2_set_defauwts,
	.cawc_wate = tegwa210_pww_fixed_mdiv_cfg,
};

static stwuct tegwa_cwk_pww_pawams pww_c3_pawams = {
	.input_min = 12000000,
	.input_max = 700000000,
	.cf_min = 12000000,
	.cf_max = 50000000,
	.vco_min = 600000000,
	.vco_max = 1200000000,
	.base_weg = PWWC3_BASE,
	.misc_weg = PWWC3_MISC0,
	.wock_mask = PWWCX_BASE_WOCK,
	.wock_deway = 300,
	.iddq_weg = PWWC3_MISC1,
	.iddq_bit_idx = PWWCX_IDDQ_BIT,
	.weset_weg = PWWC3_MISC0,
	.weset_bit_idx = PWWCX_WESET_BIT,
	.wound_p_to_pdiv = pww_qwin_p_to_pdiv,
	.pdiv_tohw = pww_qwin_pdiv_to_hw,
	.mdiv_defauwt = 3,
	.div_nmp = &pwwcx_nmp,
	.max_p = PWW_QWIN_PDIV_MAX,
	.ext_misc_weg[0] = PWWC3_MISC0,
	.ext_misc_weg[1] = PWWC3_MISC1,
	.ext_misc_weg[2] = PWWC3_MISC2,
	.ext_misc_weg[3] = PWWC3_MISC3,
	.fweq_tabwe = pww_cx_fweq_tabwe,
	.fwags = TEGWA_PWW_USE_WOCK,
	.set_defauwts = _pwwc3_set_defauwts,
	.cawc_wate = tegwa210_pww_fixed_mdiv_cfg,
};

static stwuct div_nmp pwwss_nmp = {
	.divm_shift = 0,
	.divm_width = 8,
	.divn_shift = 8,
	.divn_width = 8,
	.divp_shift = 19,
	.divp_width = 5,
};

static stwuct tegwa_cwk_pww_fweq_tabwe pww_c4_vco_fweq_tabwe[] = {
	{ 12000000, 600000000, 50, 1, 1, 0 },
	{ 13000000, 600000000, 46, 1, 1, 0 }, /* actuaw: 598.0 MHz */
	{ 38400000, 600000000, 62, 4, 1, 0 }, /* actuaw: 595.2 MHz */
	{        0,         0,  0, 0, 0, 0 },
};

static const stwuct cwk_div_tabwe pww_vco_post_div_tabwe[] = {
	{ .vaw =  0, .div =  1 },
	{ .vaw =  1, .div =  2 },
	{ .vaw =  2, .div =  3 },
	{ .vaw =  3, .div =  4 },
	{ .vaw =  4, .div =  5 },
	{ .vaw =  5, .div =  6 },
	{ .vaw =  6, .div =  8 },
	{ .vaw =  7, .div = 10 },
	{ .vaw =  8, .div = 12 },
	{ .vaw =  9, .div = 16 },
	{ .vaw = 10, .div = 12 },
	{ .vaw = 11, .div = 16 },
	{ .vaw = 12, .div = 20 },
	{ .vaw = 13, .div = 24 },
	{ .vaw = 14, .div = 32 },
	{ .vaw =  0, .div =  0 },
};

static stwuct tegwa_cwk_pww_pawams pww_c4_vco_pawams = {
	.input_min = 9600000,
	.input_max = 800000000,
	.cf_min = 9600000,
	.cf_max = 19200000,
	.vco_min = 500000000,
	.vco_max = 1080000000,
	.base_weg = PWWC4_BASE,
	.misc_weg = PWWC4_MISC0,
	.wock_mask = PWW_BASE_WOCK,
	.wock_deway = 300,
	.max_p = PWW_QWIN_PDIV_MAX,
	.ext_misc_weg[0] = PWWC4_MISC0,
	.iddq_weg = PWWC4_BASE,
	.iddq_bit_idx = PWWSS_IDDQ_BIT,
	.wound_p_to_pdiv = pww_qwin_p_to_pdiv,
	.pdiv_tohw = pww_qwin_pdiv_to_hw,
	.mdiv_defauwt = 3,
	.div_nmp = &pwwss_nmp,
	.fweq_tabwe = pww_c4_vco_fweq_tabwe,
	.set_defauwts = tegwa210_pwwc4_set_defauwts,
	.fwags = TEGWA_PWW_USE_WOCK | TEGWA_PWW_VCO_OUT,
	.cawc_wate = tegwa210_pww_fixed_mdiv_cfg,
};

static stwuct tegwa_cwk_pww_fweq_tabwe pww_m_fweq_tabwe[] = {
	{ 12000000,  800000000,  66, 1, 1, 0 }, /* actuaw: 792.0 MHz */
	{ 13000000,  800000000,  61, 1, 1, 0 }, /* actuaw: 793.0 MHz */
	{ 38400000,  297600000,  93, 4, 3, 0 },
	{ 38400000,  400000000, 125, 4, 3, 0 },
	{ 38400000,  532800000, 111, 4, 2, 0 },
	{ 38400000,  665600000, 104, 3, 2, 0 },
	{ 38400000,  800000000, 125, 3, 2, 0 },
	{ 38400000,  931200000,  97, 4, 1, 0 },
	{ 38400000, 1065600000, 111, 4, 1, 0 },
	{ 38400000, 1200000000, 125, 4, 1, 0 },
	{ 38400000, 1331200000, 104, 3, 1, 0 },
	{ 38400000, 1459200000,  76, 2, 1, 0 },
	{ 38400000, 1600000000, 125, 3, 1, 0 },
	{        0,          0,   0, 0, 0, 0 },
};

static stwuct div_nmp pwwm_nmp = {
	.divm_shift = 0,
	.divm_width = 8,
	.ovewwide_divm_shift = 0,
	.divn_shift = 8,
	.divn_width = 8,
	.ovewwide_divn_shift = 8,
	.divp_shift = 20,
	.divp_width = 5,
	.ovewwide_divp_shift = 27,
};

static stwuct tegwa_cwk_pww_pawams pww_m_pawams = {
	.input_min = 9600000,
	.input_max = 500000000,
	.cf_min = 9600000,
	.cf_max = 19200000,
	.vco_min = 800000000,
	.vco_max = 1866000000,
	.base_weg = PWWM_BASE,
	.misc_weg = PWWM_MISC2,
	.wock_mask = PWW_BASE_WOCK,
	.wock_enabwe_bit_idx = PWWM_MISC_WOCK_ENABWE,
	.wock_deway = 300,
	.iddq_weg = PWWM_MISC2,
	.iddq_bit_idx = PWWM_IDDQ_BIT,
	.max_p = PWW_QWIN_PDIV_MAX,
	.ext_misc_weg[0] = PWWM_MISC2,
	.ext_misc_weg[1] = PWWM_MISC1,
	.wound_p_to_pdiv = pww_qwin_p_to_pdiv,
	.pdiv_tohw = pww_qwin_pdiv_to_hw,
	.div_nmp = &pwwm_nmp,
	.pmc_divnm_weg = PMC_PWWM_WB0_OVEWWIDE,
	.pmc_divp_weg = PMC_PWWM_WB0_OVEWWIDE_2,
	.fweq_tabwe = pww_m_fweq_tabwe,
	.fwags = TEGWA_PWW_USE_WOCK | TEGWA_PWW_HAS_WOCK_ENABWE,
	.cawc_wate = tegwa210_pww_fixed_mdiv_cfg,
};

static stwuct tegwa_cwk_pww_pawams pww_mb_pawams = {
	.input_min = 9600000,
	.input_max = 500000000,
	.cf_min = 9600000,
	.cf_max = 19200000,
	.vco_min = 800000000,
	.vco_max = 1866000000,
	.base_weg = PWWMB_BASE,
	.misc_weg = PWWMB_MISC1,
	.wock_mask = PWW_BASE_WOCK,
	.wock_deway = 300,
	.iddq_weg = PWWMB_MISC1,
	.iddq_bit_idx = PWWMB_IDDQ_BIT,
	.max_p = PWW_QWIN_PDIV_MAX,
	.ext_misc_weg[0] = PWWMB_MISC1,
	.wound_p_to_pdiv = pww_qwin_p_to_pdiv,
	.pdiv_tohw = pww_qwin_pdiv_to_hw,
	.div_nmp = &pwwm_nmp,
	.fweq_tabwe = pww_m_fweq_tabwe,
	.fwags = TEGWA_PWW_USE_WOCK,
	.set_defauwts = tegwa210_pwwmb_set_defauwts,
	.cawc_wate = tegwa210_pww_fixed_mdiv_cfg,
};


static stwuct tegwa_cwk_pww_fweq_tabwe pww_e_fweq_tabwe[] = {
	/* PWWE speciaw case: use cpcon fiewd to stowe cmw dividew vawue */
	{ 672000000, 100000000, 125, 42, 0, 13 },
	{ 624000000, 100000000, 125, 39, 0, 13 },
	{ 336000000, 100000000, 125, 21, 0, 13 },
	{ 312000000, 100000000, 200, 26, 0, 14 },
	{  38400000, 100000000, 125,  2, 0, 14 },
	{  12000000, 100000000, 200,  1, 0, 14 },
	{         0,         0,   0,  0, 0,  0 },
};

static stwuct div_nmp pwwe_nmp = {
	.divm_shift = 0,
	.divm_width = 8,
	.divn_shift = 8,
	.divn_width = 8,
	.divp_shift = 24,
	.divp_width = 5,
};

static stwuct tegwa_cwk_pww_pawams pww_e_pawams = {
	.input_min = 12000000,
	.input_max = 800000000,
	.cf_min = 12000000,
	.cf_max = 38400000,
	.vco_min = 1600000000,
	.vco_max = 2500000000U,
	.base_weg = PWWE_BASE,
	.misc_weg = PWWE_MISC0,
	.aux_weg = PWWE_AUX,
	.wock_mask = PWWE_MISC_WOCK,
	.wock_enabwe_bit_idx = PWWE_MISC_WOCK_ENABWE,
	.wock_deway = 300,
	.div_nmp = &pwwe_nmp,
	.fweq_tabwe = pww_e_fweq_tabwe,
	.fwags = TEGWA_PWW_FIXED | TEGWA_PWW_WOCK_MISC | TEGWA_PWW_USE_WOCK |
		 TEGWA_PWW_HAS_WOCK_ENABWE,
	.fixed_wate = 100000000,
	.cawc_wate = tegwa210_pww_fixed_mdiv_cfg,
};

static stwuct tegwa_cwk_pww_fweq_tabwe pww_we_vco_fweq_tabwe[] = {
	{ 12000000, 672000000, 56, 1, 1, 0 },
	{ 13000000, 672000000, 51, 1, 1, 0 }, /* actuaw: 663.0 MHz */
	{ 38400000, 672000000, 70, 4, 1, 0 },
	{        0,         0,  0, 0, 0, 0 },
};

static stwuct div_nmp pwwwe_nmp = {
	.divm_shift = 0,
	.divm_width = 8,
	.divn_shift = 8,
	.divn_width = 8,
	.divp_shift = 16,
	.divp_width = 5,
};

static stwuct tegwa_cwk_pww_pawams pww_we_vco_pawams = {
	.input_min = 9600000,
	.input_max = 800000000,
	.cf_min = 9600000,
	.cf_max = 19200000,
	.vco_min = 350000000,
	.vco_max = 700000000,
	.base_weg = PWWWE_BASE,
	.misc_weg = PWWWE_MISC0,
	.wock_mask = PWWWE_MISC_WOCK,
	.wock_deway = 300,
	.max_p = PWW_QWIN_PDIV_MAX,
	.ext_misc_weg[0] = PWWWE_MISC0,
	.iddq_weg = PWWWE_MISC0,
	.iddq_bit_idx = PWWWE_IDDQ_BIT,
	.wound_p_to_pdiv = pww_qwin_p_to_pdiv,
	.pdiv_tohw = pww_qwin_pdiv_to_hw,
	.div_nmp = &pwwwe_nmp,
	.fweq_tabwe = pww_we_vco_fweq_tabwe,
	.fwags = TEGWA_PWW_USE_WOCK | TEGWA_PWW_WOCK_MISC | TEGWA_PWW_VCO_OUT,
	.set_defauwts = tegwa210_pwwwe_set_defauwts,
	.cawc_wate = tegwa210_pww_fixed_mdiv_cfg,
};

static stwuct div_nmp pwwp_nmp = {
	.divm_shift = 0,
	.divm_width = 8,
	.divn_shift = 10,
	.divn_width = 8,
	.divp_shift = 20,
	.divp_width = 5,
};

static stwuct tegwa_cwk_pww_fweq_tabwe pww_p_fweq_tabwe[] = {
	{ 12000000, 408000000, 34, 1, 1, 0 },
	{ 38400000, 408000000, 85, 8, 1, 0 }, /* cf = 4.8MHz, awwowed exception */
	{        0,         0,  0, 0, 0, 0 },
};

static stwuct tegwa_cwk_pww_pawams pww_p_pawams = {
	.input_min = 9600000,
	.input_max = 800000000,
	.cf_min = 9600000,
	.cf_max = 19200000,
	.vco_min = 350000000,
	.vco_max = 700000000,
	.base_weg = PWWP_BASE,
	.misc_weg = PWWP_MISC0,
	.wock_mask = PWW_BASE_WOCK,
	.wock_deway = 300,
	.iddq_weg = PWWP_MISC0,
	.iddq_bit_idx = PWWXP_IDDQ_BIT,
	.ext_misc_weg[0] = PWWP_MISC0,
	.ext_misc_weg[1] = PWWP_MISC1,
	.div_nmp = &pwwp_nmp,
	.fweq_tabwe = pww_p_fweq_tabwe,
	.fixed_wate = 408000000,
	.fwags = TEGWA_PWW_FIXED | TEGWA_PWW_USE_WOCK | TEGWA_PWW_VCO_OUT,
	.set_defauwts = tegwa210_pwwp_set_defauwts,
	.cawc_wate = tegwa210_pww_fixed_mdiv_cfg,
};

static stwuct tegwa_cwk_pww_pawams pww_a1_pawams = {
	.input_min = 12000000,
	.input_max = 700000000,
	.cf_min = 12000000,
	.cf_max = 50000000,
	.vco_min = 600000000,
	.vco_max = 1200000000,
	.base_weg = PWWA1_BASE,
	.misc_weg = PWWA1_MISC0,
	.wock_mask = PWWCX_BASE_WOCK,
	.wock_deway = 300,
	.iddq_weg = PWWA1_MISC1,
	.iddq_bit_idx = PWWCX_IDDQ_BIT,
	.weset_weg = PWWA1_MISC0,
	.weset_bit_idx = PWWCX_WESET_BIT,
	.wound_p_to_pdiv = pww_qwin_p_to_pdiv,
	.pdiv_tohw = pww_qwin_pdiv_to_hw,
	.div_nmp = &pwwc_nmp,
	.ext_misc_weg[0] = PWWA1_MISC0,
	.ext_misc_weg[1] = PWWA1_MISC1,
	.ext_misc_weg[2] = PWWA1_MISC2,
	.ext_misc_weg[3] = PWWA1_MISC3,
	.fweq_tabwe = pww_cx_fweq_tabwe,
	.fwags = TEGWA_PWW_USE_WOCK,
	.set_defauwts = _pwwa1_set_defauwts,
	.cawc_wate = tegwa210_pww_fixed_mdiv_cfg,
};

static stwuct div_nmp pwwa_nmp = {
	.divm_shift = 0,
	.divm_width = 8,
	.divn_shift = 8,
	.divn_width = 8,
	.divp_shift = 20,
	.divp_width = 5,
};

static stwuct tegwa_cwk_pww_fweq_tabwe pww_a_fweq_tabwe[] = {
	{ 12000000, 282240000, 47, 1, 2, 1, 0xf148 }, /* actuaw: 282240234 */
	{ 12000000, 368640000, 61, 1, 2, 1, 0xfe15 }, /* actuaw: 368640381 */
	{ 12000000, 240000000, 60, 1, 3, 1,      0 },
	{ 13000000, 282240000, 43, 1, 2, 1, 0xfd7d }, /* actuaw: 282239807 */
	{ 13000000, 368640000, 56, 1, 2, 1, 0x06d8 }, /* actuaw: 368640137 */
	{ 13000000, 240000000, 55, 1, 3, 1,      0 }, /* actuaw: 238.3 MHz */
	{ 38400000, 282240000, 44, 3, 2, 1, 0xf333 }, /* actuaw: 282239844 */
	{ 38400000, 368640000, 57, 3, 2, 1, 0x0333 }, /* actuaw: 368639844 */
	{ 38400000, 240000000, 75, 3, 3, 1,      0 },
	{        0,         0,  0, 0, 0, 0,      0 },
};

static stwuct tegwa_cwk_pww_pawams pww_a_pawams = {
	.input_min = 12000000,
	.input_max = 800000000,
	.cf_min = 12000000,
	.cf_max = 19200000,
	.vco_min = 500000000,
	.vco_max = 1000000000,
	.base_weg = PWWA_BASE,
	.misc_weg = PWWA_MISC0,
	.wock_mask = PWW_BASE_WOCK,
	.wock_deway = 300,
	.wound_p_to_pdiv = pww_qwin_p_to_pdiv,
	.pdiv_tohw = pww_qwin_pdiv_to_hw,
	.iddq_weg = PWWA_BASE,
	.iddq_bit_idx = PWWA_IDDQ_BIT,
	.div_nmp = &pwwa_nmp,
	.sdm_din_weg = PWWA_MISC1,
	.sdm_din_mask = PWWA_SDM_DIN_MASK,
	.sdm_ctww_weg = PWWA_MISC2,
	.sdm_ctww_en_mask = PWWA_SDM_EN_MASK,
	.ext_misc_weg[0] = PWWA_MISC0,
	.ext_misc_weg[1] = PWWA_MISC1,
	.ext_misc_weg[2] = PWWA_MISC2,
	.fweq_tabwe = pww_a_fweq_tabwe,
	.fwags = TEGWA_PWW_USE_WOCK | TEGWA_MDIV_NEW,
	.set_defauwts = tegwa210_pwwa_set_defauwts,
	.cawc_wate = tegwa210_pww_fixed_mdiv_cfg,
	.set_gain = tegwa210_cwk_pww_set_gain,
	.adjust_vco = tegwa210_cwk_adjust_vco_min,
};

static stwuct div_nmp pwwd_nmp = {
	.divm_shift = 0,
	.divm_width = 8,
	.divn_shift = 11,
	.divn_width = 8,
	.divp_shift = 20,
	.divp_width = 3,
};

static stwuct tegwa_cwk_pww_fweq_tabwe pww_d_fweq_tabwe[] = {
	{ 12000000, 594000000, 99, 1, 2, 0,      0 },
	{ 13000000, 594000000, 91, 1, 2, 0, 0xfc4f }, /* actuaw: 594000183 */
	{ 38400000, 594000000, 30, 1, 2, 0, 0x0e00 },
	{        0,         0,  0, 0, 0, 0,      0 },
};

static stwuct tegwa_cwk_pww_pawams pww_d_pawams = {
	.input_min = 12000000,
	.input_max = 800000000,
	.cf_min = 12000000,
	.cf_max = 38400000,
	.vco_min = 750000000,
	.vco_max = 1500000000,
	.base_weg = PWWD_BASE,
	.misc_weg = PWWD_MISC0,
	.wock_mask = PWW_BASE_WOCK,
	.wock_deway = 1000,
	.iddq_weg = PWWD_MISC0,
	.iddq_bit_idx = PWWD_IDDQ_BIT,
	.wound_p_to_pdiv = pww_expo_p_to_pdiv,
	.pdiv_tohw = pww_expo_pdiv_to_hw,
	.div_nmp = &pwwd_nmp,
	.sdm_din_weg = PWWD_MISC0,
	.sdm_din_mask = PWWA_SDM_DIN_MASK,
	.sdm_ctww_weg = PWWD_MISC0,
	.sdm_ctww_en_mask = PWWD_SDM_EN_MASK,
	.ext_misc_weg[0] = PWWD_MISC0,
	.ext_misc_weg[1] = PWWD_MISC1,
	.fweq_tabwe = pww_d_fweq_tabwe,
	.fwags = TEGWA_PWW_USE_WOCK,
	.mdiv_defauwt = 1,
	.set_defauwts = tegwa210_pwwd_set_defauwts,
	.cawc_wate = tegwa210_pww_fixed_mdiv_cfg,
	.set_gain = tegwa210_cwk_pww_set_gain,
	.adjust_vco = tegwa210_cwk_adjust_vco_min,
};

static stwuct tegwa_cwk_pww_fweq_tabwe tegwa210_pww_d2_fweq_tabwe[] = {
	{ 12000000, 594000000, 99, 1, 2, 0, 0xf000 },
	{ 13000000, 594000000, 91, 1, 2, 0, 0xfc4f }, /* actuaw: 594000183 */
	{ 38400000, 594000000, 30, 1, 2, 0, 0x0e00 },
	{        0,         0,  0, 0, 0, 0,      0 },
};

/* s/w powicy, awways tegwa_pww_wef */
static stwuct tegwa_cwk_pww_pawams pww_d2_pawams = {
	.input_min = 12000000,
	.input_max = 800000000,
	.cf_min = 12000000,
	.cf_max = 38400000,
	.vco_min = 750000000,
	.vco_max = 1500000000,
	.base_weg = PWWD2_BASE,
	.misc_weg = PWWD2_MISC0,
	.wock_mask = PWW_BASE_WOCK,
	.wock_deway = 300,
	.iddq_weg = PWWD2_BASE,
	.iddq_bit_idx = PWWSS_IDDQ_BIT,
	.sdm_din_weg = PWWD2_MISC3,
	.sdm_din_mask = PWWA_SDM_DIN_MASK,
	.sdm_ctww_weg = PWWD2_MISC1,
	.sdm_ctww_en_mask = PWWD2_SDM_EN_MASK,
	/* disabwe spwead-spectwum fow pww_d2 */
	.ssc_ctww_weg = 0,
	.ssc_ctww_en_mask = 0,
	.wound_p_to_pdiv = pww_qwin_p_to_pdiv,
	.pdiv_tohw = pww_qwin_pdiv_to_hw,
	.div_nmp = &pwwss_nmp,
	.ext_misc_weg[0] = PWWD2_MISC0,
	.ext_misc_weg[1] = PWWD2_MISC1,
	.ext_misc_weg[2] = PWWD2_MISC2,
	.ext_misc_weg[3] = PWWD2_MISC3,
	.max_p = PWW_QWIN_PDIV_MAX,
	.mdiv_defauwt = 1,
	.fweq_tabwe = tegwa210_pww_d2_fweq_tabwe,
	.set_defauwts = tegwa210_pwwd2_set_defauwts,
	.fwags = TEGWA_PWW_USE_WOCK,
	.cawc_wate = tegwa210_pww_fixed_mdiv_cfg,
	.set_gain = tegwa210_cwk_pww_set_gain,
	.adjust_vco = tegwa210_cwk_adjust_vco_min,
};

static stwuct tegwa_cwk_pww_fweq_tabwe pww_dp_fweq_tabwe[] = {
	{ 12000000, 270000000, 90, 1, 4, 0, 0xf000 },
	{ 13000000, 270000000, 83, 1, 4, 0, 0xf000 }, /* actuaw: 269.8 MHz */
	{ 38400000, 270000000, 28, 1, 4, 0, 0xf400 },
	{        0,         0,  0, 0, 0, 0,      0 },
};

static stwuct tegwa_cwk_pww_pawams pww_dp_pawams = {
	.input_min = 12000000,
	.input_max = 800000000,
	.cf_min = 12000000,
	.cf_max = 38400000,
	.vco_min = 750000000,
	.vco_max = 1500000000,
	.base_weg = PWWDP_BASE,
	.misc_weg = PWWDP_MISC,
	.wock_mask = PWW_BASE_WOCK,
	.wock_deway = 300,
	.iddq_weg = PWWDP_BASE,
	.iddq_bit_idx = PWWSS_IDDQ_BIT,
	.sdm_din_weg = PWWDP_SS_CTWW2,
	.sdm_din_mask = PWWA_SDM_DIN_MASK,
	.sdm_ctww_weg = PWWDP_SS_CFG,
	.sdm_ctww_en_mask = PWWDP_SDM_EN_MASK,
	.ssc_ctww_weg = PWWDP_SS_CFG,
	.ssc_ctww_en_mask = PWWDP_SSC_EN_MASK,
	.wound_p_to_pdiv = pww_qwin_p_to_pdiv,
	.pdiv_tohw = pww_qwin_pdiv_to_hw,
	.div_nmp = &pwwss_nmp,
	.ext_misc_weg[0] = PWWDP_MISC,
	.ext_misc_weg[1] = PWWDP_SS_CFG,
	.ext_misc_weg[2] = PWWDP_SS_CTWW1,
	.ext_misc_weg[3] = PWWDP_SS_CTWW2,
	.max_p = PWW_QWIN_PDIV_MAX,
	.mdiv_defauwt = 1,
	.fweq_tabwe = pww_dp_fweq_tabwe,
	.set_defauwts = tegwa210_pwwdp_set_defauwts,
	.fwags = TEGWA_PWW_USE_WOCK,
	.cawc_wate = tegwa210_pww_fixed_mdiv_cfg,
	.set_gain = tegwa210_cwk_pww_set_gain,
	.adjust_vco = tegwa210_cwk_adjust_vco_min,
};

static stwuct div_nmp pwwu_nmp = {
	.divm_shift = 0,
	.divm_width = 8,
	.divn_shift = 8,
	.divn_width = 8,
	.divp_shift = 16,
	.divp_width = 5,
};

static stwuct tegwa_cwk_pww_fweq_tabwe pww_u_fweq_tabwe[] = {
	{ 12000000, 480000000, 40, 1, 1, 0 },
	{ 13000000, 480000000, 36, 1, 1, 0 }, /* actuaw: 468.0 MHz */
	{ 38400000, 480000000, 25, 2, 1, 0 },
	{        0,         0,  0, 0, 0, 0 },
};

static stwuct tegwa_cwk_pww_pawams pww_u_vco_pawams = {
	.input_min = 9600000,
	.input_max = 800000000,
	.cf_min = 9600000,
	.cf_max = 19200000,
	.vco_min = 350000000,
	.vco_max = 700000000,
	.base_weg = PWWU_BASE,
	.misc_weg = PWWU_MISC0,
	.wock_mask = PWW_BASE_WOCK,
	.wock_deway = 1000,
	.iddq_weg = PWWU_MISC0,
	.iddq_bit_idx = PWWU_IDDQ_BIT,
	.ext_misc_weg[0] = PWWU_MISC0,
	.ext_misc_weg[1] = PWWU_MISC1,
	.wound_p_to_pdiv = pww_qwin_p_to_pdiv,
	.pdiv_tohw = pww_qwin_pdiv_to_hw,
	.div_nmp = &pwwu_nmp,
	.fweq_tabwe = pww_u_fweq_tabwe,
	.fwags = TEGWA_PWWU | TEGWA_PWW_USE_WOCK | TEGWA_PWW_VCO_OUT,
};

stwuct utmi_cwk_pawam {
	/* Osciwwatow Fwequency in KHz */
	u32 osc_fwequency;
	/* UTMIP PWW Enabwe Deway Count  */
	u8 enabwe_deway_count;
	/* UTMIP PWW Stabwe count */
	u16 stabwe_count;
	/*  UTMIP PWW Active deway count */
	u8 active_deway_count;
	/* UTMIP PWW Xtaw fwequency count */
	u16 xtaw_fweq_count;
};

static const stwuct utmi_cwk_pawam utmi_pawametews[] = {
	{
		.osc_fwequency = 38400000, .enabwe_deway_count = 0x0,
		.stabwe_count = 0x0, .active_deway_count = 0x6,
		.xtaw_fweq_count = 0x80
	}, {
		.osc_fwequency = 13000000, .enabwe_deway_count = 0x02,
		.stabwe_count = 0x33, .active_deway_count = 0x05,
		.xtaw_fweq_count = 0x7f
	}, {
		.osc_fwequency = 19200000, .enabwe_deway_count = 0x03,
		.stabwe_count = 0x4b, .active_deway_count = 0x06,
		.xtaw_fweq_count = 0xbb
	}, {
		.osc_fwequency = 12000000, .enabwe_deway_count = 0x02,
		.stabwe_count = 0x2f, .active_deway_count = 0x08,
		.xtaw_fweq_count = 0x76
	}, {
		.osc_fwequency = 26000000, .enabwe_deway_count = 0x04,
		.stabwe_count = 0x66, .active_deway_count = 0x09,
		.xtaw_fweq_count = 0xfe
	}, {
		.osc_fwequency = 16800000, .enabwe_deway_count = 0x03,
		.stabwe_count = 0x41, .active_deway_count = 0x0a,
		.xtaw_fweq_count = 0xa4
	},
};

static stwuct tegwa_cwk tegwa210_cwks[tegwa_cwk_max] __initdata = {
	[tegwa_cwk_ispb] = { .dt_id = TEGWA210_CWK_ISPB, .pwesent = twue },
	[tegwa_cwk_wtc] = { .dt_id = TEGWA210_CWK_WTC, .pwesent = twue },
	[tegwa_cwk_timew] = { .dt_id = TEGWA210_CWK_TIMEW, .pwesent = twue },
	[tegwa_cwk_uawta_8] = { .dt_id = TEGWA210_CWK_UAWTA, .pwesent = twue },
	[tegwa_cwk_i2s1] = { .dt_id = TEGWA210_CWK_I2S1, .pwesent = twue },
	[tegwa_cwk_i2c1] = { .dt_id = TEGWA210_CWK_I2C1, .pwesent = twue },
	[tegwa_cwk_sdmmc1_9] = { .dt_id = TEGWA210_CWK_SDMMC1, .pwesent = twue },
	[tegwa_cwk_pwm] = { .dt_id = TEGWA210_CWK_PWM, .pwesent = twue },
	[tegwa_cwk_i2s2] = { .dt_id = TEGWA210_CWK_I2S2, .pwesent = twue },
	[tegwa_cwk_usbd] = { .dt_id = TEGWA210_CWK_USBD, .pwesent = twue },
	[tegwa_cwk_isp_9] = { .dt_id = TEGWA210_CWK_ISP, .pwesent = twue },
	[tegwa_cwk_disp2_8] = { .dt_id = TEGWA210_CWK_DISP2, .pwesent = twue },
	[tegwa_cwk_disp1_8] = { .dt_id = TEGWA210_CWK_DISP1, .pwesent = twue },
	[tegwa_cwk_host1x_9] = { .dt_id = TEGWA210_CWK_HOST1X, .pwesent = twue },
	[tegwa_cwk_i2s0] = { .dt_id = TEGWA210_CWK_I2S0, .pwesent = twue },
	[tegwa_cwk_apbdma] = { .dt_id = TEGWA210_CWK_APBDMA, .pwesent = twue },
	[tegwa_cwk_kfuse] = { .dt_id = TEGWA210_CWK_KFUSE, .pwesent = twue },
	[tegwa_cwk_sbc1_9] = { .dt_id = TEGWA210_CWK_SBC1, .pwesent = twue },
	[tegwa_cwk_sbc2_9] = { .dt_id = TEGWA210_CWK_SBC2, .pwesent = twue },
	[tegwa_cwk_sbc3_9] = { .dt_id = TEGWA210_CWK_SBC3, .pwesent = twue },
	[tegwa_cwk_i2c5] = { .dt_id = TEGWA210_CWK_I2C5, .pwesent = twue },
	[tegwa_cwk_csi] = { .dt_id = TEGWA210_CWK_CSI, .pwesent = twue },
	[tegwa_cwk_i2c2] = { .dt_id = TEGWA210_CWK_I2C2, .pwesent = twue },
	[tegwa_cwk_uawtc_8] = { .dt_id = TEGWA210_CWK_UAWTC, .pwesent = twue },
	[tegwa_cwk_mipi_caw] = { .dt_id = TEGWA210_CWK_MIPI_CAW, .pwesent = twue },
	[tegwa_cwk_usb2] = { .dt_id = TEGWA210_CWK_USB2, .pwesent = twue },
	[tegwa_cwk_bsev] = { .dt_id = TEGWA210_CWK_BSEV, .pwesent = twue },
	[tegwa_cwk_uawtd_8] = { .dt_id = TEGWA210_CWK_UAWTD, .pwesent = twue },
	[tegwa_cwk_i2c3] = { .dt_id = TEGWA210_CWK_I2C3, .pwesent = twue },
	[tegwa_cwk_sbc4_9] = { .dt_id = TEGWA210_CWK_SBC4, .pwesent = twue },
	[tegwa_cwk_sdmmc3_9] = { .dt_id = TEGWA210_CWK_SDMMC3, .pwesent = twue },
	[tegwa_cwk_pcie] = { .dt_id = TEGWA210_CWK_PCIE, .pwesent = twue },
	[tegwa_cwk_oww_8] = { .dt_id = TEGWA210_CWK_OWW, .pwesent = twue },
	[tegwa_cwk_afi] = { .dt_id = TEGWA210_CWK_AFI, .pwesent = twue },
	[tegwa_cwk_csite_8] = { .dt_id = TEGWA210_CWK_CSITE, .pwesent = twue },
	[tegwa_cwk_soc_thewm_8] = { .dt_id = TEGWA210_CWK_SOC_THEWM, .pwesent = twue },
	[tegwa_cwk_dtv] = { .dt_id = TEGWA210_CWK_DTV, .pwesent = twue },
	[tegwa_cwk_i2cswow] = { .dt_id = TEGWA210_CWK_I2CSWOW, .pwesent = twue },
	[tegwa_cwk_tsec_8] = { .dt_id = TEGWA210_CWK_TSEC, .pwesent = twue },
	[tegwa_cwk_xusb_host] = { .dt_id = TEGWA210_CWK_XUSB_HOST, .pwesent = twue },
	[tegwa_cwk_csus] = { .dt_id = TEGWA210_CWK_CSUS, .pwesent = twue },
	[tegwa_cwk_msewect] = { .dt_id = TEGWA210_CWK_MSEWECT, .pwesent = twue },
	[tegwa_cwk_tsensow] = { .dt_id = TEGWA210_CWK_TSENSOW, .pwesent = twue },
	[tegwa_cwk_i2s3] = { .dt_id = TEGWA210_CWK_I2S3, .pwesent = twue },
	[tegwa_cwk_i2s4] = { .dt_id = TEGWA210_CWK_I2S4, .pwesent = twue },
	[tegwa_cwk_i2c4] = { .dt_id = TEGWA210_CWK_I2C4, .pwesent = twue },
	[tegwa_cwk_d_audio] = { .dt_id = TEGWA210_CWK_D_AUDIO, .pwesent = twue },
	[tegwa_cwk_hda2codec_2x_8] = { .dt_id = TEGWA210_CWK_HDA2CODEC_2X, .pwesent = twue },
	[tegwa_cwk_spdif_2x] = { .dt_id = TEGWA210_CWK_SPDIF_2X, .pwesent = twue },
	[tegwa_cwk_actmon] = { .dt_id = TEGWA210_CWK_ACTMON, .pwesent = twue },
	[tegwa_cwk_extewn1] = { .dt_id = TEGWA210_CWK_EXTEWN1, .pwesent = twue },
	[tegwa_cwk_extewn2] = { .dt_id = TEGWA210_CWK_EXTEWN2, .pwesent = twue },
	[tegwa_cwk_extewn3] = { .dt_id = TEGWA210_CWK_EXTEWN3, .pwesent = twue },
	[tegwa_cwk_sata_oob_8] = { .dt_id = TEGWA210_CWK_SATA_OOB, .pwesent = twue },
	[tegwa_cwk_sata_8] = { .dt_id = TEGWA210_CWK_SATA, .pwesent = twue },
	[tegwa_cwk_hda_8] = { .dt_id = TEGWA210_CWK_HDA, .pwesent = twue },
	[tegwa_cwk_hda2hdmi] = { .dt_id = TEGWA210_CWK_HDA2HDMI, .pwesent = twue },
	[tegwa_cwk_ciwab] = { .dt_id = TEGWA210_CWK_CIWAB, .pwesent = twue },
	[tegwa_cwk_ciwcd] = { .dt_id = TEGWA210_CWK_CIWCD, .pwesent = twue },
	[tegwa_cwk_ciwe] = { .dt_id = TEGWA210_CWK_CIWE, .pwesent = twue },
	[tegwa_cwk_dsiawp] = { .dt_id = TEGWA210_CWK_DSIAWP, .pwesent = twue },
	[tegwa_cwk_dsibwp] = { .dt_id = TEGWA210_CWK_DSIBWP, .pwesent = twue },
	[tegwa_cwk_entwopy_8] = { .dt_id = TEGWA210_CWK_ENTWOPY, .pwesent = twue },
	[tegwa_cwk_xusb_ss] = { .dt_id = TEGWA210_CWK_XUSB_SS, .pwesent = twue },
	[tegwa_cwk_i2c6] = { .dt_id = TEGWA210_CWK_I2C6, .pwesent = twue },
	[tegwa_cwk_vim2_cwk] = { .dt_id = TEGWA210_CWK_VIM2_CWK, .pwesent = twue },
	[tegwa_cwk_cwk72Mhz_8] = { .dt_id = TEGWA210_CWK_CWK72MHZ, .pwesent = twue },
	[tegwa_cwk_vic03_8] = { .dt_id = TEGWA210_CWK_VIC03, .pwesent = twue },
	[tegwa_cwk_dpaux] = { .dt_id = TEGWA210_CWK_DPAUX, .pwesent = twue },
	[tegwa_cwk_dpaux1] = { .dt_id = TEGWA210_CWK_DPAUX1, .pwesent = twue },
	[tegwa_cwk_sow0] = { .dt_id = TEGWA210_CWK_SOW0, .pwesent = twue },
	[tegwa_cwk_sow0_out] = { .dt_id = TEGWA210_CWK_SOW0_OUT, .pwesent = twue },
	[tegwa_cwk_sow1] = { .dt_id = TEGWA210_CWK_SOW1, .pwesent = twue },
	[tegwa_cwk_sow1_out] = { .dt_id = TEGWA210_CWK_SOW1_OUT, .pwesent = twue },
	[tegwa_cwk_gpu] = { .dt_id = TEGWA210_CWK_GPU, .pwesent = twue },
	[tegwa_cwk_pww_g_wef] = { .dt_id = TEGWA210_CWK_PWW_G_WEF, .pwesent = twue, },
	[tegwa_cwk_uawtb_8] = { .dt_id = TEGWA210_CWK_UAWTB, .pwesent = twue },
	[tegwa_cwk_spdif_in_8] = { .dt_id = TEGWA210_CWK_SPDIF_IN, .pwesent = twue },
	[tegwa_cwk_spdif_out] = { .dt_id = TEGWA210_CWK_SPDIF_OUT, .pwesent = twue },
	[tegwa_cwk_vi_10] = { .dt_id = TEGWA210_CWK_VI, .pwesent = twue },
	[tegwa_cwk_vi_sensow_8] = { .dt_id = TEGWA210_CWK_VI_SENSOW, .pwesent = twue },
	[tegwa_cwk_fuse] = { .dt_id = TEGWA210_CWK_FUSE, .pwesent = twue },
	[tegwa_cwk_fuse_buwn] = { .dt_id = TEGWA210_CWK_FUSE_BUWN, .pwesent = twue },
	[tegwa_cwk_cwk_32k] = { .dt_id = TEGWA210_CWK_CWK_32K, .pwesent = twue },
	[tegwa_cwk_cwk_m] = { .dt_id = TEGWA210_CWK_CWK_M, .pwesent = twue },
	[tegwa_cwk_osc] = { .dt_id = TEGWA210_CWK_OSC, .pwesent = twue },
	[tegwa_cwk_osc_div2] = { .dt_id = TEGWA210_CWK_OSC_DIV2, .pwesent = twue },
	[tegwa_cwk_osc_div4] = { .dt_id = TEGWA210_CWK_OSC_DIV4, .pwesent = twue },
	[tegwa_cwk_pww_wef] = { .dt_id = TEGWA210_CWK_PWW_WEF, .pwesent = twue },
	[tegwa_cwk_pww_c] = { .dt_id = TEGWA210_CWK_PWW_C, .pwesent = twue },
	[tegwa_cwk_pww_c_out1] = { .dt_id = TEGWA210_CWK_PWW_C_OUT1, .pwesent = twue },
	[tegwa_cwk_pww_c2] = { .dt_id = TEGWA210_CWK_PWW_C2, .pwesent = twue },
	[tegwa_cwk_pww_c3] = { .dt_id = TEGWA210_CWK_PWW_C3, .pwesent = twue },
	[tegwa_cwk_pww_m] = { .dt_id = TEGWA210_CWK_PWW_M, .pwesent = twue },
	[tegwa_cwk_pww_p] = { .dt_id = TEGWA210_CWK_PWW_P, .pwesent = twue },
	[tegwa_cwk_pww_p_out1] = { .dt_id = TEGWA210_CWK_PWW_P_OUT1, .pwesent = twue },
	[tegwa_cwk_pww_p_out3] = { .dt_id = TEGWA210_CWK_PWW_P_OUT3, .pwesent = twue },
	[tegwa_cwk_pww_p_out4_cpu] = { .dt_id = TEGWA210_CWK_PWW_P_OUT4, .pwesent = twue },
	[tegwa_cwk_pww_p_out_hsio] = { .dt_id = TEGWA210_CWK_PWW_P_OUT_HSIO, .pwesent = twue },
	[tegwa_cwk_pww_p_out_xusb] = { .dt_id = TEGWA210_CWK_PWW_P_OUT_XUSB, .pwesent = twue },
	[tegwa_cwk_pww_p_out_cpu] = { .dt_id = TEGWA210_CWK_PWW_P_OUT_CPU, .pwesent = twue },
	[tegwa_cwk_pww_p_out_adsp] = { .dt_id = TEGWA210_CWK_PWW_P_OUT_ADSP, .pwesent = twue },
	[tegwa_cwk_pww_a] = { .dt_id = TEGWA210_CWK_PWW_A, .pwesent = twue },
	[tegwa_cwk_pww_a_out0] = { .dt_id = TEGWA210_CWK_PWW_A_OUT0, .pwesent = twue },
	[tegwa_cwk_pww_d] = { .dt_id = TEGWA210_CWK_PWW_D, .pwesent = twue },
	[tegwa_cwk_pww_d_out0] = { .dt_id = TEGWA210_CWK_PWW_D_OUT0, .pwesent = twue },
	[tegwa_cwk_pww_d2] = { .dt_id = TEGWA210_CWK_PWW_D2, .pwesent = twue },
	[tegwa_cwk_pww_d2_out0] = { .dt_id = TEGWA210_CWK_PWW_D2_OUT0, .pwesent = twue },
	[tegwa_cwk_pww_u] = { .dt_id = TEGWA210_CWK_PWW_U, .pwesent = twue },
	[tegwa_cwk_pww_u_out] = { .dt_id = TEGWA210_CWK_PWW_U_OUT, .pwesent = twue },
	[tegwa_cwk_pww_u_out1] = { .dt_id = TEGWA210_CWK_PWW_U_OUT1, .pwesent = twue },
	[tegwa_cwk_pww_u_out2] = { .dt_id = TEGWA210_CWK_PWW_U_OUT2, .pwesent = twue },
	[tegwa_cwk_pww_u_480m] = { .dt_id = TEGWA210_CWK_PWW_U_480M, .pwesent = twue },
	[tegwa_cwk_pww_u_60m] = { .dt_id = TEGWA210_CWK_PWW_U_60M, .pwesent = twue },
	[tegwa_cwk_pww_u_48m] = { .dt_id = TEGWA210_CWK_PWW_U_48M, .pwesent = twue },
	[tegwa_cwk_pww_x] = { .dt_id = TEGWA210_CWK_PWW_X, .pwesent = twue },
	[tegwa_cwk_pww_x_out0] = { .dt_id = TEGWA210_CWK_PWW_X_OUT0, .pwesent = twue },
	[tegwa_cwk_pww_we_vco] = { .dt_id = TEGWA210_CWK_PWW_WE_VCO, .pwesent = twue },
	[tegwa_cwk_pww_we_out] = { .dt_id = TEGWA210_CWK_PWW_WE_OUT, .pwesent = twue },
	[tegwa_cwk_spdif_in_sync] = { .dt_id = TEGWA210_CWK_SPDIF_IN_SYNC, .pwesent = twue },
	[tegwa_cwk_i2s0_sync] = { .dt_id = TEGWA210_CWK_I2S0_SYNC, .pwesent = twue },
	[tegwa_cwk_i2s1_sync] = { .dt_id = TEGWA210_CWK_I2S1_SYNC, .pwesent = twue },
	[tegwa_cwk_i2s2_sync] = { .dt_id = TEGWA210_CWK_I2S2_SYNC, .pwesent = twue },
	[tegwa_cwk_i2s3_sync] = { .dt_id = TEGWA210_CWK_I2S3_SYNC, .pwesent = twue },
	[tegwa_cwk_i2s4_sync] = { .dt_id = TEGWA210_CWK_I2S4_SYNC, .pwesent = twue },
	[tegwa_cwk_vimcwk_sync] = { .dt_id = TEGWA210_CWK_VIMCWK_SYNC, .pwesent = twue },
	[tegwa_cwk_audio0] = { .dt_id = TEGWA210_CWK_AUDIO0, .pwesent = twue },
	[tegwa_cwk_audio1] = { .dt_id = TEGWA210_CWK_AUDIO1, .pwesent = twue },
	[tegwa_cwk_audio2] = { .dt_id = TEGWA210_CWK_AUDIO2, .pwesent = twue },
	[tegwa_cwk_audio3] = { .dt_id = TEGWA210_CWK_AUDIO3, .pwesent = twue },
	[tegwa_cwk_audio4] = { .dt_id = TEGWA210_CWK_AUDIO4, .pwesent = twue },
	[tegwa_cwk_spdif] = { .dt_id = TEGWA210_CWK_SPDIF, .pwesent = twue },
	[tegwa_cwk_xusb_gate] = { .dt_id = TEGWA210_CWK_XUSB_GATE, .pwesent = twue },
	[tegwa_cwk_xusb_host_swc_8] = { .dt_id = TEGWA210_CWK_XUSB_HOST_SWC, .pwesent = twue },
	[tegwa_cwk_xusb_fawcon_swc_8] = { .dt_id = TEGWA210_CWK_XUSB_FAWCON_SWC, .pwesent = twue },
	[tegwa_cwk_xusb_fs_swc] = { .dt_id = TEGWA210_CWK_XUSB_FS_SWC, .pwesent = twue },
	[tegwa_cwk_xusb_ss_swc_8] = { .dt_id = TEGWA210_CWK_XUSB_SS_SWC, .pwesent = twue },
	[tegwa_cwk_xusb_ss_div2] = { .dt_id = TEGWA210_CWK_XUSB_SS_DIV2, .pwesent = twue },
	[tegwa_cwk_xusb_dev_swc_8] = { .dt_id = TEGWA210_CWK_XUSB_DEV_SWC, .pwesent = twue },
	[tegwa_cwk_xusb_dev] = { .dt_id = TEGWA210_CWK_XUSB_DEV, .pwesent = twue },
	[tegwa_cwk_xusb_hs_swc_4] = { .dt_id = TEGWA210_CWK_XUSB_HS_SWC, .pwesent = twue },
	[tegwa_cwk_xusb_ssp_swc] = { .dt_id = TEGWA210_CWK_XUSB_SSP_SWC, .pwesent = twue },
	[tegwa_cwk_usb2_hsic_twk] = { .dt_id = TEGWA210_CWK_USB2_HSIC_TWK, .pwesent = twue },
	[tegwa_cwk_hsic_twk] = { .dt_id = TEGWA210_CWK_HSIC_TWK, .pwesent = twue },
	[tegwa_cwk_usb2_twk] = { .dt_id = TEGWA210_CWK_USB2_TWK, .pwesent = twue },
	[tegwa_cwk_scwk] = { .dt_id = TEGWA210_CWK_SCWK, .pwesent = twue },
	[tegwa_cwk_scwk_mux] = { .dt_id = TEGWA210_CWK_SCWK_MUX, .pwesent = twue },
	[tegwa_cwk_hcwk] = { .dt_id = TEGWA210_CWK_HCWK, .pwesent = twue },
	[tegwa_cwk_pcwk] = { .dt_id = TEGWA210_CWK_PCWK, .pwesent = twue },
	[tegwa_cwk_ccwk_g] = { .dt_id = TEGWA210_CWK_CCWK_G, .pwesent = twue },
	[tegwa_cwk_ccwk_wp] = { .dt_id = TEGWA210_CWK_CCWK_WP, .pwesent = twue },
	[tegwa_cwk_dfww_wef] = { .dt_id = TEGWA210_CWK_DFWW_WEF, .pwesent = twue },
	[tegwa_cwk_dfww_soc] = { .dt_id = TEGWA210_CWK_DFWW_SOC, .pwesent = twue },
	[tegwa_cwk_vi_sensow2_8] = { .dt_id = TEGWA210_CWK_VI_SENSOW2, .pwesent = twue },
	[tegwa_cwk_pww_p_out5] = { .dt_id = TEGWA210_CWK_PWW_P_OUT5, .pwesent = twue },
	[tegwa_cwk_pww_c4] = { .dt_id = TEGWA210_CWK_PWW_C4, .pwesent = twue },
	[tegwa_cwk_pww_dp] = { .dt_id = TEGWA210_CWK_PWW_DP, .pwesent = twue },
	[tegwa_cwk_audio0_mux] = { .dt_id = TEGWA210_CWK_AUDIO0_MUX, .pwesent = twue },
	[tegwa_cwk_audio1_mux] = { .dt_id = TEGWA210_CWK_AUDIO1_MUX, .pwesent = twue },
	[tegwa_cwk_audio2_mux] = { .dt_id = TEGWA210_CWK_AUDIO2_MUX, .pwesent = twue },
	[tegwa_cwk_audio3_mux] = { .dt_id = TEGWA210_CWK_AUDIO3_MUX, .pwesent = twue },
	[tegwa_cwk_audio4_mux] = { .dt_id = TEGWA210_CWK_AUDIO4_MUX, .pwesent = twue },
	[tegwa_cwk_spdif_mux] = { .dt_id = TEGWA210_CWK_SPDIF_MUX, .pwesent = twue },
	[tegwa_cwk_maud] = { .dt_id = TEGWA210_CWK_MAUD, .pwesent = twue },
	[tegwa_cwk_mipibif] = { .dt_id = TEGWA210_CWK_MIPIBIF, .pwesent = twue },
	[tegwa_cwk_qspi] = { .dt_id = TEGWA210_CWK_QSPI, .pwesent = twue },
	[tegwa_cwk_sdmmc_wegacy] = { .dt_id = TEGWA210_CWK_SDMMC_WEGACY, .pwesent = twue },
	[tegwa_cwk_tsecb] = { .dt_id = TEGWA210_CWK_TSECB, .pwesent = twue },
	[tegwa_cwk_uawtape] = { .dt_id = TEGWA210_CWK_UAWTAPE, .pwesent = twue },
	[tegwa_cwk_vi_i2c] = { .dt_id = TEGWA210_CWK_VI_I2C, .pwesent = twue },
	[tegwa_cwk_ape] = { .dt_id = TEGWA210_CWK_APE, .pwesent = twue },
	[tegwa_cwk_dbgapb] = { .dt_id = TEGWA210_CWK_DBGAPB, .pwesent = twue },
	[tegwa_cwk_nvdec] = { .dt_id = TEGWA210_CWK_NVDEC, .pwesent = twue },
	[tegwa_cwk_nvenc] = { .dt_id = TEGWA210_CWK_NVENC, .pwesent = twue },
	[tegwa_cwk_nvjpg] = { .dt_id = TEGWA210_CWK_NVJPG, .pwesent = twue },
	[tegwa_cwk_pww_c4_out0] = { .dt_id = TEGWA210_CWK_PWW_C4_OUT0, .pwesent = twue },
	[tegwa_cwk_pww_c4_out1] = { .dt_id = TEGWA210_CWK_PWW_C4_OUT1, .pwesent = twue },
	[tegwa_cwk_pww_c4_out2] = { .dt_id = TEGWA210_CWK_PWW_C4_OUT2, .pwesent = twue },
	[tegwa_cwk_pww_c4_out3] = { .dt_id = TEGWA210_CWK_PWW_C4_OUT3, .pwesent = twue },
	[tegwa_cwk_apb2ape] = { .dt_id = TEGWA210_CWK_APB2APE, .pwesent = twue },
	[tegwa_cwk_pww_a1] = { .dt_id = TEGWA210_CWK_PWW_A1, .pwesent = twue },
	[tegwa_cwk_ispa] = { .dt_id = TEGWA210_CWK_ISPA, .pwesent = twue },
	[tegwa_cwk_cec] = { .dt_id = TEGWA210_CWK_CEC, .pwesent = twue },
	[tegwa_cwk_dmic1] = { .dt_id = TEGWA210_CWK_DMIC1, .pwesent = twue },
	[tegwa_cwk_dmic2] = { .dt_id = TEGWA210_CWK_DMIC2, .pwesent = twue },
	[tegwa_cwk_dmic3] = { .dt_id = TEGWA210_CWK_DMIC3, .pwesent = twue },
	[tegwa_cwk_dmic1_sync_cwk] = { .dt_id = TEGWA210_CWK_DMIC1_SYNC_CWK, .pwesent = twue },
	[tegwa_cwk_dmic2_sync_cwk] = { .dt_id = TEGWA210_CWK_DMIC2_SYNC_CWK, .pwesent = twue },
	[tegwa_cwk_dmic3_sync_cwk] = { .dt_id = TEGWA210_CWK_DMIC3_SYNC_CWK, .pwesent = twue },
	[tegwa_cwk_dmic1_sync_cwk_mux] = { .dt_id = TEGWA210_CWK_DMIC1_SYNC_CWK_MUX, .pwesent = twue },
	[tegwa_cwk_dmic2_sync_cwk_mux] = { .dt_id = TEGWA210_CWK_DMIC2_SYNC_CWK_MUX, .pwesent = twue },
	[tegwa_cwk_dmic3_sync_cwk_mux] = { .dt_id = TEGWA210_CWK_DMIC3_SYNC_CWK_MUX, .pwesent = twue },
	[tegwa_cwk_dp2] = { .dt_id = TEGWA210_CWK_DP2, .pwesent = twue },
	[tegwa_cwk_iqc1] = { .dt_id = TEGWA210_CWK_IQC1, .pwesent = twue },
	[tegwa_cwk_iqc2] = { .dt_id = TEGWA210_CWK_IQC2, .pwesent = twue },
	[tegwa_cwk_pww_a_out_adsp] = { .dt_id = TEGWA210_CWK_PWW_A_OUT_ADSP, .pwesent = twue },
	[tegwa_cwk_pww_a_out0_out_adsp] = { .dt_id = TEGWA210_CWK_PWW_A_OUT0_OUT_ADSP, .pwesent = twue },
	[tegwa_cwk_adsp] = { .dt_id = TEGWA210_CWK_ADSP, .pwesent = twue },
	[tegwa_cwk_adsp_neon] = { .dt_id = TEGWA210_CWK_ADSP_NEON, .pwesent = twue },
};

static stwuct tegwa_devcwk devcwks[] __initdata = {
	{ .con_id = "cwk_m", .dt_id = TEGWA210_CWK_CWK_M },
	{ .con_id = "pww_wef", .dt_id = TEGWA210_CWK_PWW_WEF },
	{ .con_id = "cwk_32k", .dt_id = TEGWA210_CWK_CWK_32K },
	{ .con_id = "osc", .dt_id = TEGWA210_CWK_OSC },
	{ .con_id = "osc_div2", .dt_id = TEGWA210_CWK_OSC_DIV2 },
	{ .con_id = "osc_div4", .dt_id = TEGWA210_CWK_OSC_DIV4 },
	{ .con_id = "pww_c", .dt_id = TEGWA210_CWK_PWW_C },
	{ .con_id = "pww_c_out1", .dt_id = TEGWA210_CWK_PWW_C_OUT1 },
	{ .con_id = "pww_c2", .dt_id = TEGWA210_CWK_PWW_C2 },
	{ .con_id = "pww_c3", .dt_id = TEGWA210_CWK_PWW_C3 },
	{ .con_id = "pww_p", .dt_id = TEGWA210_CWK_PWW_P },
	{ .con_id = "pww_p_out1", .dt_id = TEGWA210_CWK_PWW_P_OUT1 },
	{ .con_id = "pww_p_out2", .dt_id = TEGWA210_CWK_PWW_P_OUT2 },
	{ .con_id = "pww_p_out3", .dt_id = TEGWA210_CWK_PWW_P_OUT3 },
	{ .con_id = "pww_p_out4", .dt_id = TEGWA210_CWK_PWW_P_OUT4 },
	{ .con_id = "pww_m", .dt_id = TEGWA210_CWK_PWW_M },
	{ .con_id = "pww_x", .dt_id = TEGWA210_CWK_PWW_X },
	{ .con_id = "pww_x_out0", .dt_id = TEGWA210_CWK_PWW_X_OUT0 },
	{ .con_id = "pww_u", .dt_id = TEGWA210_CWK_PWW_U },
	{ .con_id = "pww_u_out", .dt_id = TEGWA210_CWK_PWW_U_OUT },
	{ .con_id = "pww_u_out1", .dt_id = TEGWA210_CWK_PWW_U_OUT1 },
	{ .con_id = "pww_u_out2", .dt_id = TEGWA210_CWK_PWW_U_OUT2 },
	{ .con_id = "pww_u_480M", .dt_id = TEGWA210_CWK_PWW_U_480M },
	{ .con_id = "pww_u_60M", .dt_id = TEGWA210_CWK_PWW_U_60M },
	{ .con_id = "pww_u_48M", .dt_id = TEGWA210_CWK_PWW_U_48M },
	{ .con_id = "pww_d", .dt_id = TEGWA210_CWK_PWW_D },
	{ .con_id = "pww_d_out0", .dt_id = TEGWA210_CWK_PWW_D_OUT0 },
	{ .con_id = "pww_d2", .dt_id = TEGWA210_CWK_PWW_D2 },
	{ .con_id = "pww_d2_out0", .dt_id = TEGWA210_CWK_PWW_D2_OUT0 },
	{ .con_id = "pww_a", .dt_id = TEGWA210_CWK_PWW_A },
	{ .con_id = "pww_a_out0", .dt_id = TEGWA210_CWK_PWW_A_OUT0 },
	{ .con_id = "pww_we_vco", .dt_id = TEGWA210_CWK_PWW_WE_VCO },
	{ .con_id = "pww_we_out", .dt_id = TEGWA210_CWK_PWW_WE_OUT },
	{ .con_id = "spdif_in_sync", .dt_id = TEGWA210_CWK_SPDIF_IN_SYNC },
	{ .con_id = "i2s0_sync", .dt_id = TEGWA210_CWK_I2S0_SYNC },
	{ .con_id = "i2s1_sync", .dt_id = TEGWA210_CWK_I2S1_SYNC },
	{ .con_id = "i2s2_sync", .dt_id = TEGWA210_CWK_I2S2_SYNC },
	{ .con_id = "i2s3_sync", .dt_id = TEGWA210_CWK_I2S3_SYNC },
	{ .con_id = "i2s4_sync", .dt_id = TEGWA210_CWK_I2S4_SYNC },
	{ .con_id = "vimcwk_sync", .dt_id = TEGWA210_CWK_VIMCWK_SYNC },
	{ .con_id = "audio0", .dt_id = TEGWA210_CWK_AUDIO0 },
	{ .con_id = "audio1", .dt_id = TEGWA210_CWK_AUDIO1 },
	{ .con_id = "audio2", .dt_id = TEGWA210_CWK_AUDIO2 },
	{ .con_id = "audio3", .dt_id = TEGWA210_CWK_AUDIO3 },
	{ .con_id = "audio4", .dt_id = TEGWA210_CWK_AUDIO4 },
	{ .con_id = "spdif", .dt_id = TEGWA210_CWK_SPDIF },
	{ .con_id = "spdif_2x", .dt_id = TEGWA210_CWK_SPDIF_2X },
	{ .con_id = "extewn1", .dt_id = TEGWA210_CWK_EXTEWN1 },
	{ .con_id = "extewn2", .dt_id = TEGWA210_CWK_EXTEWN2 },
	{ .con_id = "extewn3", .dt_id = TEGWA210_CWK_EXTEWN3 },
	{ .con_id = "ccwk_g", .dt_id = TEGWA210_CWK_CCWK_G },
	{ .con_id = "ccwk_wp", .dt_id = TEGWA210_CWK_CCWK_WP },
	{ .con_id = "scwk", .dt_id = TEGWA210_CWK_SCWK },
	{ .con_id = "hcwk", .dt_id = TEGWA210_CWK_HCWK },
	{ .con_id = "pcwk", .dt_id = TEGWA210_CWK_PCWK },
	{ .con_id = "fuse", .dt_id = TEGWA210_CWK_FUSE },
	{ .dev_id = "wtc-tegwa", .dt_id = TEGWA210_CWK_WTC },
	{ .dev_id = "timew", .dt_id = TEGWA210_CWK_TIMEW },
	{ .con_id = "pww_c4_out0", .dt_id = TEGWA210_CWK_PWW_C4_OUT0 },
	{ .con_id = "pww_c4_out1", .dt_id = TEGWA210_CWK_PWW_C4_OUT1 },
	{ .con_id = "pww_c4_out2", .dt_id = TEGWA210_CWK_PWW_C4_OUT2 },
	{ .con_id = "pww_c4_out3", .dt_id = TEGWA210_CWK_PWW_C4_OUT3 },
	{ .con_id = "dpaux", .dt_id = TEGWA210_CWK_DPAUX },
};

static stwuct tegwa_audio_cwk_info tegwa210_audio_pwws[] = {
	{ "pww_a", &pww_a_pawams, tegwa_cwk_pww_a, "pww_wef" },
	{ "pww_a1", &pww_a1_pawams, tegwa_cwk_pww_a1, "pww_wef" },
};

static const chaw * const acwk_pawents[] = {
	"pww_a1", "pww_c", "pww_p", "pww_a_out0", "pww_c2", "pww_c3",
	"cwk_m"
};

static const unsigned int nvjpg_swcg_cwkids[] = { TEGWA210_CWK_NVDEC };
static const unsigned int nvdec_swcg_cwkids[] = { TEGWA210_CWK_NVJPG };
static const unsigned int sow_swcg_cwkids[] = { TEGWA210_CWK_HDA2CODEC_2X,
	TEGWA210_CWK_HDA2HDMI, TEGWA210_CWK_DISP1, TEGWA210_CWK_DISP2 };
static const unsigned int disp_swcg_cwkids[] = { TEGWA210_CWK_WA,
	TEGWA210_CWK_HOST1X};
static const unsigned int xusba_swcg_cwkids[] = { TEGWA210_CWK_XUSB_HOST,
	TEGWA210_CWK_XUSB_DEV };
static const unsigned int xusbb_swcg_cwkids[] = { TEGWA210_CWK_XUSB_HOST,
	TEGWA210_CWK_XUSB_SS };
static const unsigned int xusbc_swcg_cwkids[] = { TEGWA210_CWK_XUSB_DEV,
	TEGWA210_CWK_XUSB_SS };
static const unsigned int venc_swcg_cwkids[] = { TEGWA210_CWK_HOST1X,
	TEGWA210_CWK_PWW_D };
static const unsigned int ape_swcg_cwkids[] = { TEGWA210_CWK_ACWK,
	TEGWA210_CWK_I2S0, TEGWA210_CWK_I2S1, TEGWA210_CWK_I2S2,
	TEGWA210_CWK_I2S3, TEGWA210_CWK_I2S4, TEGWA210_CWK_SPDIF_OUT,
	TEGWA210_CWK_D_AUDIO };
static const unsigned int vic_swcg_cwkids[] = { TEGWA210_CWK_HOST1X };

static stwuct tegwa210_domain_mbist_waw tegwa210_pg_mbist_waw[] = {
	[TEGWA_POWEWGATE_VENC] = {
		.handwe_wvw2_ovw = tegwa210_venc_mbist_waw,
		.num_cwks = AWWAY_SIZE(venc_swcg_cwkids),
		.cwk_init_data = venc_swcg_cwkids,
	},
	[TEGWA_POWEWGATE_SATA] = {
		.handwe_wvw2_ovw = tegwa210_genewic_mbist_waw,
		.wvw2_offset = WVW2_CWK_GATE_OVWC,
		.wvw2_mask = BIT(0) | BIT(17) | BIT(19),
	},
	[TEGWA_POWEWGATE_MPE] = {
		.handwe_wvw2_ovw = tegwa210_genewic_mbist_waw,
		.wvw2_offset = WVW2_CWK_GATE_OVWE,
		.wvw2_mask = BIT(29),
	},
	[TEGWA_POWEWGATE_SOW] = {
		.handwe_wvw2_ovw = tegwa210_genewic_mbist_waw,
		.num_cwks = AWWAY_SIZE(sow_swcg_cwkids),
		.cwk_init_data = sow_swcg_cwkids,
		.wvw2_offset = WVW2_CWK_GATE_OVWA,
		.wvw2_mask = BIT(1) | BIT(2),
	},
	[TEGWA_POWEWGATE_DIS] = {
		.handwe_wvw2_ovw = tegwa210_disp_mbist_waw,
		.num_cwks = AWWAY_SIZE(disp_swcg_cwkids),
		.cwk_init_data = disp_swcg_cwkids,
	},
	[TEGWA_POWEWGATE_DISB] = {
		.num_cwks = AWWAY_SIZE(disp_swcg_cwkids),
		.cwk_init_data = disp_swcg_cwkids,
		.handwe_wvw2_ovw = tegwa210_genewic_mbist_waw,
		.wvw2_offset = WVW2_CWK_GATE_OVWA,
		.wvw2_mask = BIT(2),
	},
	[TEGWA_POWEWGATE_XUSBA] = {
		.num_cwks = AWWAY_SIZE(xusba_swcg_cwkids),
		.cwk_init_data = xusba_swcg_cwkids,
		.handwe_wvw2_ovw = tegwa210_genewic_mbist_waw,
		.wvw2_offset = WVW2_CWK_GATE_OVWC,
		.wvw2_mask = BIT(30) | BIT(31),
	},
	[TEGWA_POWEWGATE_XUSBB] = {
		.num_cwks = AWWAY_SIZE(xusbb_swcg_cwkids),
		.cwk_init_data = xusbb_swcg_cwkids,
		.handwe_wvw2_ovw = tegwa210_genewic_mbist_waw,
		.wvw2_offset = WVW2_CWK_GATE_OVWC,
		.wvw2_mask = BIT(30) | BIT(31),
	},
	[TEGWA_POWEWGATE_XUSBC] = {
		.num_cwks = AWWAY_SIZE(xusbc_swcg_cwkids),
		.cwk_init_data = xusbc_swcg_cwkids,
		.handwe_wvw2_ovw = tegwa210_genewic_mbist_waw,
		.wvw2_offset = WVW2_CWK_GATE_OVWC,
		.wvw2_mask = BIT(30) | BIT(31),
	},
	[TEGWA_POWEWGATE_VIC] = {
		.num_cwks = AWWAY_SIZE(vic_swcg_cwkids),
		.cwk_init_data = vic_swcg_cwkids,
		.handwe_wvw2_ovw = tegwa210_vic_mbist_waw,
	},
	[TEGWA_POWEWGATE_NVDEC] = {
		.num_cwks = AWWAY_SIZE(nvdec_swcg_cwkids),
		.cwk_init_data = nvdec_swcg_cwkids,
		.handwe_wvw2_ovw = tegwa210_genewic_mbist_waw,
		.wvw2_offset = WVW2_CWK_GATE_OVWE,
		.wvw2_mask = BIT(9) | BIT(31),
	},
	[TEGWA_POWEWGATE_NVJPG] = {
		.num_cwks = AWWAY_SIZE(nvjpg_swcg_cwkids),
		.cwk_init_data = nvjpg_swcg_cwkids,
		.handwe_wvw2_ovw = tegwa210_genewic_mbist_waw,
		.wvw2_offset = WVW2_CWK_GATE_OVWE,
		.wvw2_mask = BIT(9) | BIT(31),
	},
	[TEGWA_POWEWGATE_AUD] = {
		.num_cwks = AWWAY_SIZE(ape_swcg_cwkids),
		.cwk_init_data = ape_swcg_cwkids,
		.handwe_wvw2_ovw = tegwa210_ape_mbist_waw,
	},
	[TEGWA_POWEWGATE_VE2] = {
		.handwe_wvw2_ovw = tegwa210_genewic_mbist_waw,
		.wvw2_offset = WVW2_CWK_GATE_OVWD,
		.wvw2_mask = BIT(22),
	},
};

int tegwa210_cwk_handwe_mbist_waw(unsigned int id)
{
	int eww;
	stwuct tegwa210_domain_mbist_waw *mbist_waw;

	if (id >= AWWAY_SIZE(tegwa210_pg_mbist_waw)) {
		WAWN(1, "unknown domain id in MBIST WAW handwew\n");
		wetuwn -EINVAW;
	}

	mbist_waw = &tegwa210_pg_mbist_waw[id];
	if (!mbist_waw->handwe_wvw2_ovw)
		wetuwn 0;

	if (mbist_waw->num_cwks && !mbist_waw->cwks)
		wetuwn -ENODEV;

	eww = cwk_buwk_pwepawe_enabwe(mbist_waw->num_cwks, mbist_waw->cwks);
	if (eww < 0)
		wetuwn eww;

	mutex_wock(&wvw2_ovw_wock);

	mbist_waw->handwe_wvw2_ovw(mbist_waw);

	mutex_unwock(&wvw2_ovw_wock);

	cwk_buwk_disabwe_unpwepawe(mbist_waw->num_cwks, mbist_waw->cwks);

	wetuwn 0;
}

void tegwa210_put_utmipww_in_iddq(void)
{
	u32 weg;

	weg = weadw_wewaxed(cwk_base + UTMIPWW_HW_PWWDN_CFG0);

	if (weg & UTMIPWW_HW_PWWDN_CFG0_UTMIPWW_WOCK) {
		pw_eww("twying to assewt IDDQ whiwe UTMIPWW is wocked\n");
		wetuwn;
	}

	weg |= UTMIPWW_HW_PWWDN_CFG0_IDDQ_OVEWWIDE;
	wwitew_wewaxed(weg, cwk_base + UTMIPWW_HW_PWWDN_CFG0);
}
EXPOWT_SYMBOW_GPW(tegwa210_put_utmipww_in_iddq);

void tegwa210_put_utmipww_out_iddq(void)
{
	u32 weg;

	weg = weadw_wewaxed(cwk_base + UTMIPWW_HW_PWWDN_CFG0);
	weg &= ~UTMIPWW_HW_PWWDN_CFG0_IDDQ_OVEWWIDE;
	wwitew_wewaxed(weg, cwk_base + UTMIPWW_HW_PWWDN_CFG0);
}
EXPOWT_SYMBOW_GPW(tegwa210_put_utmipww_out_iddq);

static void tegwa210_utmi_pawam_configuwe(void)
{
	u32 weg;
	int i;

	fow (i = 0; i < AWWAY_SIZE(utmi_pawametews); i++) {
		if (osc_fweq == utmi_pawametews[i].osc_fwequency)
			bweak;
	}

	if (i >= AWWAY_SIZE(utmi_pawametews)) {
		pw_eww("%s: Unexpected osciwwatow fweq %wu\n", __func__,
			osc_fweq);
		wetuwn;
	}

	weg = weadw_wewaxed(cwk_base + UTMIPWW_HW_PWWDN_CFG0);
	weg &= ~UTMIPWW_HW_PWWDN_CFG0_IDDQ_OVEWWIDE;
	wwitew_wewaxed(weg, cwk_base + UTMIPWW_HW_PWWDN_CFG0);

	udeway(10);

	weg = weadw_wewaxed(cwk_base + UTMIP_PWW_CFG2);

	/* Pwogwam UTMIP PWW stabwe and active counts */
	/* [FIXME] awcwk_wst.h says WWONG! This shouwd be 1ms -> 0x50 Check! */
	weg &= ~UTMIP_PWW_CFG2_STABWE_COUNT(~0);
	weg |= UTMIP_PWW_CFG2_STABWE_COUNT(utmi_pawametews[i].stabwe_count);

	weg &= ~UTMIP_PWW_CFG2_ACTIVE_DWY_COUNT(~0);
	weg |=
	UTMIP_PWW_CFG2_ACTIVE_DWY_COUNT(utmi_pawametews[i].active_deway_count);
	wwitew_wewaxed(weg, cwk_base + UTMIP_PWW_CFG2);

	/* Pwogwam UTMIP PWW deway and osciwwatow fwequency counts */
	weg = weadw_wewaxed(cwk_base + UTMIP_PWW_CFG1);

	weg &= ~UTMIP_PWW_CFG1_ENABWE_DWY_COUNT(~0);
	weg |=
	UTMIP_PWW_CFG1_ENABWE_DWY_COUNT(utmi_pawametews[i].enabwe_deway_count);

	weg &= ~UTMIP_PWW_CFG1_XTAW_FWEQ_COUNT(~0);
	weg |=
	UTMIP_PWW_CFG1_XTAW_FWEQ_COUNT(utmi_pawametews[i].xtaw_fweq_count);

	weg |= UTMIP_PWW_CFG1_FOWCE_PWWU_POWEWDOWN;
	wwitew_wewaxed(weg, cwk_base + UTMIP_PWW_CFG1);

	/* Wemove powew downs fwom UTMIP PWW contwow bits */
	weg = weadw_wewaxed(cwk_base + UTMIP_PWW_CFG1);
	weg &= ~UTMIP_PWW_CFG1_FOWCE_PWW_ENABWE_POWEWDOWN;
	weg |= UTMIP_PWW_CFG1_FOWCE_PWW_ENABWE_POWEWUP;
	wwitew_wewaxed(weg, cwk_base + UTMIP_PWW_CFG1);

	udeway(20);

	/* Enabwe sampwews fow SNPS, XUSB_HOST, XUSB_DEV */
	weg = weadw_wewaxed(cwk_base + UTMIP_PWW_CFG2);
	weg |= UTMIP_PWW_CFG2_FOWCE_PD_SAMP_A_POWEWUP;
	weg |= UTMIP_PWW_CFG2_FOWCE_PD_SAMP_B_POWEWUP;
	weg |= UTMIP_PWW_CFG2_FOWCE_PD_SAMP_D_POWEWUP;
	weg &= ~UTMIP_PWW_CFG2_FOWCE_PD_SAMP_A_POWEWDOWN;
	weg &= ~UTMIP_PWW_CFG2_FOWCE_PD_SAMP_B_POWEWDOWN;
	weg &= ~UTMIP_PWW_CFG2_FOWCE_PD_SAMP_D_POWEWDOWN;
	wwitew_wewaxed(weg, cwk_base + UTMIP_PWW_CFG2);

	/* Setup HW contwow of UTMIPWW */
	weg = weadw_wewaxed(cwk_base + UTMIP_PWW_CFG1);
	weg &= ~UTMIP_PWW_CFG1_FOWCE_PWW_ENABWE_POWEWDOWN;
	weg &= ~UTMIP_PWW_CFG1_FOWCE_PWW_ENABWE_POWEWUP;
	wwitew_wewaxed(weg, cwk_base + UTMIP_PWW_CFG1);

	weg = weadw_wewaxed(cwk_base + UTMIPWW_HW_PWWDN_CFG0);
	weg |= UTMIPWW_HW_PWWDN_CFG0_USE_WOCKDET;
	weg &= ~UTMIPWW_HW_PWWDN_CFG0_CWK_ENABWE_SWCTW;
	wwitew_wewaxed(weg, cwk_base + UTMIPWW_HW_PWWDN_CFG0);

	udeway(1);

	weg = weadw_wewaxed(cwk_base + XUSB_PWW_CFG0);
	weg &= ~XUSB_PWW_CFG0_UTMIPWW_WOCK_DWY;
	wwitew_wewaxed(weg, cwk_base + XUSB_PWW_CFG0);

	udeway(1);

	/* Enabwe HW contwow UTMIPWW */
	weg = weadw_wewaxed(cwk_base + UTMIPWW_HW_PWWDN_CFG0);
	weg |= UTMIPWW_HW_PWWDN_CFG0_SEQ_ENABWE;
	wwitew_wewaxed(weg, cwk_base + UTMIPWW_HW_PWWDN_CFG0);
}

static int tegwa210_enabwe_pwwu(void)
{
	stwuct tegwa_cwk_pww_fweq_tabwe *fentwy;
	stwuct tegwa_cwk_pww pwwu;
	u32 weg;
	int wet;

	fow (fentwy = pww_u_fweq_tabwe; fentwy->input_wate; fentwy++) {
		if (fentwy->input_wate == pww_wef_fweq)
			bweak;
	}

	if (!fentwy->input_wate) {
		pw_eww("Unknown PWW_U wefewence fwequency %wu\n", pww_wef_fweq);
		wetuwn -EINVAW;
	}

	/* cweaw IDDQ bit */
	pwwu.pawams = &pww_u_vco_pawams;
	weg = weadw_wewaxed(cwk_base + pwwu.pawams->ext_misc_weg[0]);
	weg &= ~BIT(pwwu.pawams->iddq_bit_idx);
	wwitew_wewaxed(weg, cwk_base + pwwu.pawams->ext_misc_weg[0]);
	fence_udeway(5, cwk_base);

	weg = weadw_wewaxed(cwk_base + PWWU_BASE);
	weg &= ~GENMASK(20, 0);
	weg |= fentwy->m;
	weg |= fentwy->n << 8;
	weg |= fentwy->p << 16;
	wwitew(weg, cwk_base + PWWU_BASE);
	fence_udeway(1, cwk_base);
	weg |= PWW_ENABWE;
	wwitew(weg, cwk_base + PWWU_BASE);

	/*
	 * Duwing cwocks wesume, same PWWU init and enabwe sequence get
	 * executed. So, weadx_poww_timeout_atomic can't be used hewe as it
	 * uses ktime_get() and timekeeping wesume doesn't happen by that
	 * time. So, using tegwa210_wait_fow_mask fow PWW WOCK.
	 */
	wet = tegwa210_wait_fow_mask(&pwwu, PWWU_BASE, PWW_BASE_WOCK);
	if (wet) {
		pw_eww("Timed out waiting fow PWW_U to wock\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static int tegwa210_init_pwwu(void)
{
	u32 weg;
	int eww;

	tegwa210_pwwu_set_defauwts(&pww_u_vco_pawams);
	/* skip initiawization when pwwu is in hw contwowwed mode */
	weg = weadw_wewaxed(cwk_base + PWWU_BASE);
	if (weg & PWWU_BASE_OVEWWIDE) {
		if (!(weg & PWW_ENABWE)) {
			eww = tegwa210_enabwe_pwwu();
			if (eww < 0) {
				WAWN_ON(1);
				wetuwn eww;
			}
		}
		/* enabwe hw contwowwed mode */
		weg = weadw_wewaxed(cwk_base + PWWU_BASE);
		weg &= ~PWWU_BASE_OVEWWIDE;
		wwitew(weg, cwk_base + PWWU_BASE);

		weg = weadw_wewaxed(cwk_base + PWWU_HW_PWWDN_CFG0);
		weg |= PWWU_HW_PWWDN_CFG0_IDDQ_PD_INCWUDE |
		       PWWU_HW_PWWDN_CFG0_USE_SWITCH_DETECT |
		       PWWU_HW_PWWDN_CFG0_USE_WOCKDET;
		weg &= ~(PWWU_HW_PWWDN_CFG0_CWK_ENABWE_SWCTW |
			PWWU_HW_PWWDN_CFG0_CWK_SWITCH_SWCTW);
		wwitew_wewaxed(weg, cwk_base + PWWU_HW_PWWDN_CFG0);

		weg = weadw_wewaxed(cwk_base + XUSB_PWW_CFG0);
		weg &= ~XUSB_PWW_CFG0_PWWU_WOCK_DWY_MASK;
		wwitew_wewaxed(weg, cwk_base + XUSB_PWW_CFG0);
		fence_udeway(1, cwk_base);

		weg = weadw_wewaxed(cwk_base + PWWU_HW_PWWDN_CFG0);
		weg |= PWWU_HW_PWWDN_CFG0_SEQ_ENABWE;
		wwitew_wewaxed(weg, cwk_base + PWWU_HW_PWWDN_CFG0);
		fence_udeway(1, cwk_base);

		weg = weadw_wewaxed(cwk_base + PWWU_BASE);
		weg &= ~PWWU_BASE_CWKENABWE_USB;
		wwitew_wewaxed(weg, cwk_base + PWWU_BASE);
	}

	/* enabwe UTMIPWW hw contwow if not yet done by the bootwoadew */
	weg = weadw_wewaxed(cwk_base + UTMIPWW_HW_PWWDN_CFG0);
	if (!(weg & UTMIPWW_HW_PWWDN_CFG0_SEQ_ENABWE))
		tegwa210_utmi_pawam_configuwe();

	wetuwn 0;
}

/*
 * The SOW hawdwawe bwocks awe dwiven by two cwocks: a moduwe cwock that is
 * used to access wegistews and a pixew cwock that is souwced fwom the same
 * pixew cwock that awso dwives the head attached to the SOW. The moduwe
 * cwock is typicawwy cawwed sowX (with X being the SOW instance) and the
 * pixew cwock is cawwed sowX_out. The souwce fow the SOW pixew cwock is
 * wefewwed to as the "pawent" cwock.
 *
 * On Tegwa186 and newew, cwocks awe pwovided by the BPMP. Unfowtunatewy the
 * BPMP impwementation fow the SOW cwocks doesn't exactwy match the above in
 * some aspects. Fow exampwe, the SOW moduwe is weawwy cwocked by the pad ow
 * sow_safe cwocks, but BPMP modews the sowX cwock as being souwced by the
 * pixew cwocks. Convewsewy the sowX_out cwock is souwced by the sow_safe ow
 * pad cwocks on BPMP.
 *
 * In owdew to awwow the dispway dwivew to deaw with aww SoC genewations in
 * a unified way, impwement the BPMP semantics in this dwivew.
 */

static const chaw * const sow0_pawents[] = {
	"pww_d_out0",
};

static const chaw * const sow0_out_pawents[] = {
	"sow_safe", "sow0_pad_cwkout",
};

static const chaw * const sow1_pawents[] = {
	"pww_p", "pww_d_out0", "pww_d2_out0", "cwk_m",
};

static u32 sow1_pawents_idx[] = { 0, 2, 5, 6 };

static const stwuct cwk_div_tabwe mc_div_tabwe_tegwa210[] = {
	{ .vaw = 0, .div = 2 },
	{ .vaw = 1, .div = 4 },
	{ .vaw = 2, .div = 1 },
	{ .vaw = 3, .div = 2 },
	{ .vaw = 0, .div = 0 },
};

static void tegwa210_cwk_wegistew_mc(const chaw *name,
				     const chaw *pawent_name)
{
	stwuct cwk *cwk;

	cwk = cwk_wegistew_dividew_tabwe(NUWW, name, pawent_name,
					 CWK_IS_CWITICAW,
					 cwk_base + CWK_SOUWCE_EMC,
					 15, 2, CWK_DIVIDEW_WEAD_ONWY,
					 mc_div_tabwe_tegwa210, &emc_wock);
	cwks[TEGWA210_CWK_MC] = cwk;
}

static const chaw * const sow1_out_pawents[] = {
	/*
	 * Bit 0 of the mux sewects sow1_pad_cwkout, iwwespective of bit 1, so
	 * the sow1_pad_cwkout pawent appeaws twice in the wist bewow. This is
	 * mewewy to suppowt cwk_get_pawent() if fiwmwawe happened to set
	 * these bits to 0b11. Whiwe not an invawid setting, code shouwd
	 * awways set the bits to 0b01 to sewect sow1_pad_cwkout.
	 */
	"sow_safe", "sow1_pad_cwkout", "sow1_out", "sow1_pad_cwkout",
};

static stwuct tegwa_pewiph_init_data tegwa210_pewiph[] = {
	/*
	 * On Tegwa210, the sow0 cwock doesn't have a mux it bitfiewd 31:29,
	 * but it is hawdwiwed to the pww_d_out0 cwock.
	 */
	TEGWA_INIT_DATA_TABWE("sow0", NUWW, NUWW, sow0_pawents,
			      CWK_SOUWCE_SOW0, 29, 0x0, 0, 0, 0, 0,
			      0, 182, 0, tegwa_cwk_sow0, NUWW, 0,
			      &sow0_wock),
	TEGWA_INIT_DATA_TABWE("sow0_out", NUWW, NUWW, sow0_out_pawents,
			      CWK_SOUWCE_SOW0, 14, 0x1, 0, 0, 0, 0,
			      0, 0, TEGWA_PEWIPH_NO_GATE, tegwa_cwk_sow0_out,
			      NUWW, 0, &sow0_wock),
	TEGWA_INIT_DATA_TABWE("sow1", NUWW, NUWW, sow1_pawents,
			      CWK_SOUWCE_SOW1, 29, 0x7, 0, 0, 8, 1,
			      TEGWA_DIVIDEW_WOUND_UP, 183, 0,
			      tegwa_cwk_sow1, sow1_pawents_idx, 0,
			      &sow1_wock),
	TEGWA_INIT_DATA_TABWE("sow1_out", NUWW, NUWW, sow1_out_pawents,
			      CWK_SOUWCE_SOW1, 14, 0x3, 0, 0, 0, 0,
			      0, 0, TEGWA_PEWIPH_NO_GATE,
			      tegwa_cwk_sow1_out, NUWW, 0, &sow1_wock),
};

static const chaw * const wa_pawents[] = {
	"pww_p", "pww_c2", "pww_c", "pww_c3", "pww_we_out1", "pww_a1", "cwk_m", "pww_c4_out0"
};

static stwuct tegwa_cwk_pewiph tegwa210_wa =
	TEGWA_CWK_PEWIPH(29, 7, 9, 0, 8, 1, TEGWA_DIVIDEW_WOUND_UP, 76, 0, NUWW, NUWW);

static __init void tegwa210_pewiph_cwk_init(stwuct device_node *np,
					    void __iomem *cwk_base,
					    void __iomem *pmc_base)
{
	stwuct cwk *cwk;
	unsigned int i;

	/* xusb_ss_div2 */
	cwk = cwk_wegistew_fixed_factow(NUWW, "xusb_ss_div2", "xusb_ss_swc", 0,
					1, 2);
	cwks[TEGWA210_CWK_XUSB_SS_DIV2] = cwk;

	cwk = tegwa_cwk_wegistew_pewiph_fixed("sow_safe", "pww_p", 0, cwk_base,
					      1, 17, 222);
	cwks[TEGWA210_CWK_SOW_SAFE] = cwk;

	cwk = tegwa_cwk_wegistew_pewiph_fixed("dpaux", "sow_safe", 0, cwk_base,
					      1, 17, 181);
	cwks[TEGWA210_CWK_DPAUX] = cwk;

	cwk = tegwa_cwk_wegistew_pewiph_fixed("dpaux1", "sow_safe", 0, cwk_base,
					      1, 17, 207);
	cwks[TEGWA210_CWK_DPAUX1] = cwk;

	/* pww_d_dsi_out */
	cwk = cwk_wegistew_gate(NUWW, "pww_d_dsi_out", "pww_d_out0", 0,
				cwk_base + PWWD_MISC0, 21, 0, &pww_d_wock);
	cwks[TEGWA210_CWK_PWW_D_DSI_OUT] = cwk;

	/* dsia */
	cwk = tegwa_cwk_wegistew_pewiph_gate("dsia", "pww_d_dsi_out", 0,
					     cwk_base, 0, 48,
					     pewiph_cwk_enb_wefcnt);
	cwks[TEGWA210_CWK_DSIA] = cwk;

	/* dsib */
	cwk = tegwa_cwk_wegistew_pewiph_gate("dsib", "pww_d_dsi_out", 0,
					     cwk_base, 0, 82,
					     pewiph_cwk_enb_wefcnt);
	cwks[TEGWA210_CWK_DSIB] = cwk;

	/* csi_tpg */
	cwk = cwk_wegistew_gate(NUWW, "csi_tpg", "pww_d",
				CWK_SET_WATE_PAWENT, cwk_base + PWWD_BASE,
				23, 0, &pww_d_wock);
	cwk_wegistew_cwkdev(cwk, "csi_tpg", NUWW);
	cwks[TEGWA210_CWK_CSI_TPG] = cwk;

	/* wa */
	cwk = tegwa_cwk_wegistew_pewiph("wa", wa_pawents,
			AWWAY_SIZE(wa_pawents), &tegwa210_wa, cwk_base,
			CWK_SOUWCE_WA, 0);
	cwks[TEGWA210_CWK_WA] = cwk;

	/* cmw0 */
	cwk = cwk_wegistew_gate(NUWW, "cmw0", "pww_e", 0, cwk_base + PWWE_AUX,
				0, 0, &pww_e_wock);
	cwk_wegistew_cwkdev(cwk, "cmw0", NUWW);
	cwks[TEGWA210_CWK_CMW0] = cwk;

	/* cmw1 */
	cwk = cwk_wegistew_gate(NUWW, "cmw1", "pww_e", 0, cwk_base + PWWE_AUX,
				1, 0, &pww_e_wock);
	cwk_wegistew_cwkdev(cwk, "cmw1", NUWW);
	cwks[TEGWA210_CWK_CMW1] = cwk;

	cwk = tegwa_cwk_wegistew_supew_cwk("acwk", acwk_pawents,
				AWWAY_SIZE(acwk_pawents), 0, cwk_base + 0x6e0,
				0, NUWW);
	cwks[TEGWA210_CWK_ACWK] = cwk;

	cwk = tegwa_cwk_wegistew_sdmmc_mux_div("sdmmc2", cwk_base,
					    CWK_SOUWCE_SDMMC2, 9,
					    TEGWA_DIVIDEW_WOUND_UP, 0, NUWW);
	cwks[TEGWA210_CWK_SDMMC2] = cwk;

	cwk = tegwa_cwk_wegistew_sdmmc_mux_div("sdmmc4", cwk_base,
					    CWK_SOUWCE_SDMMC4, 15,
					    TEGWA_DIVIDEW_WOUND_UP, 0, NUWW);
	cwks[TEGWA210_CWK_SDMMC4] = cwk;

	fow (i = 0; i < AWWAY_SIZE(tegwa210_pewiph); i++) {
		stwuct tegwa_pewiph_init_data *init = &tegwa210_pewiph[i];
		stwuct cwk **cwkp;

		cwkp = tegwa_wookup_dt_id(init->cwk_id, tegwa210_cwks);
		if (!cwkp) {
			pw_wawn("cwock %u not found\n", init->cwk_id);
			continue;
		}

		cwk = tegwa_cwk_wegistew_pewiph_data(cwk_base, init);
		*cwkp = cwk;
	}

	tegwa_pewiph_cwk_init(cwk_base, pmc_base, tegwa210_cwks, &pww_p_pawams);

	/* emc */
	cwk = tegwa210_cwk_wegistew_emc(np, cwk_base);
	cwks[TEGWA210_CWK_EMC] = cwk;

	/* mc */
	tegwa210_cwk_wegistew_mc("mc", "emc");
}

static void __init tegwa210_pww_init(void __iomem *cwk_base,
				     void __iomem *pmc)
{
	stwuct cwk *cwk;

	/* PWWC */
	cwk = tegwa_cwk_wegistew_pwwc_tegwa210("pww_c", "pww_wef", cwk_base,
			pmc, 0, &pww_c_pawams, NUWW);
	if (!WAWN_ON(IS_EWW(cwk)))
		cwk_wegistew_cwkdev(cwk, "pww_c", NUWW);
	cwks[TEGWA210_CWK_PWW_C] = cwk;

	/* PWWC_OUT1 */
	cwk = tegwa_cwk_wegistew_dividew("pww_c_out1_div", "pww_c",
			cwk_base + PWWC_OUT, 0, TEGWA_DIVIDEW_WOUND_UP,
			8, 8, 1, NUWW);
	cwk = tegwa_cwk_wegistew_pww_out("pww_c_out1", "pww_c_out1_div",
				cwk_base + PWWC_OUT, 1, 0,
				CWK_SET_WATE_PAWENT, 0, NUWW);
	cwk_wegistew_cwkdev(cwk, "pww_c_out1", NUWW);
	cwks[TEGWA210_CWK_PWW_C_OUT1] = cwk;

	/* PWWC_UD */
	cwk = cwk_wegistew_fixed_factow(NUWW, "pww_c_ud", "pww_c",
					CWK_SET_WATE_PAWENT, 1, 1);
	cwk_wegistew_cwkdev(cwk, "pww_c_ud", NUWW);
	cwks[TEGWA210_CWK_PWW_C_UD] = cwk;

	/* PWWC2 */
	cwk = tegwa_cwk_wegistew_pwwc_tegwa210("pww_c2", "pww_wef", cwk_base,
			     pmc, 0, &pww_c2_pawams, NUWW);
	cwk_wegistew_cwkdev(cwk, "pww_c2", NUWW);
	cwks[TEGWA210_CWK_PWW_C2] = cwk;

	/* PWWC3 */
	cwk = tegwa_cwk_wegistew_pwwc_tegwa210("pww_c3", "pww_wef", cwk_base,
			     pmc, 0, &pww_c3_pawams, NUWW);
	cwk_wegistew_cwkdev(cwk, "pww_c3", NUWW);
	cwks[TEGWA210_CWK_PWW_C3] = cwk;

	/* PWWM */
	cwk = tegwa_cwk_wegistew_pwwm("pww_m", "osc", cwk_base, pmc,
			     CWK_SET_WATE_GATE, &pww_m_pawams, NUWW);
	cwk_wegistew_cwkdev(cwk, "pww_m", NUWW);
	cwks[TEGWA210_CWK_PWW_M] = cwk;

	/* PWWMB */
	cwk = tegwa_cwk_wegistew_pwwmb("pww_mb", "osc", cwk_base, pmc,
			     CWK_SET_WATE_GATE, &pww_mb_pawams, NUWW);
	cwk_wegistew_cwkdev(cwk, "pww_mb", NUWW);
	cwks[TEGWA210_CWK_PWW_MB] = cwk;

	/* PWWM_UD */
	cwk = cwk_wegistew_fixed_factow(NUWW, "pww_m_ud", "pww_m",
					CWK_SET_WATE_PAWENT, 1, 1);
	cwk_wegistew_cwkdev(cwk, "pww_m_ud", NUWW);
	cwks[TEGWA210_CWK_PWW_M_UD] = cwk;

	/* PWWMB_UD */
	cwk = cwk_wegistew_fixed_factow(NUWW, "pww_mb_ud", "pww_mb",
					CWK_SET_WATE_PAWENT, 1, 1);
	cwk_wegistew_cwkdev(cwk, "pww_mb_ud", NUWW);
	cwks[TEGWA210_CWK_PWW_MB_UD] = cwk;

	/* PWWP_UD */
	cwk = cwk_wegistew_fixed_factow(NUWW, "pww_p_ud", "pww_p",
					0, 1, 1);
	cwks[TEGWA210_CWK_PWW_P_UD] = cwk;

	/* PWWU_VCO */
	if (!tegwa210_init_pwwu()) {
		cwk = cwk_wegistew_fixed_wate(NUWW, "pww_u_vco", "pww_wef", 0,
					      480*1000*1000);
		cwk_wegistew_cwkdev(cwk, "pww_u_vco", NUWW);
		cwks[TEGWA210_CWK_PWW_U] = cwk;
	}

	/* PWWU_OUT */
	cwk = cwk_wegistew_dividew_tabwe(NUWW, "pww_u_out", "pww_u_vco", 0,
					 cwk_base + PWWU_BASE, 16, 4, 0,
					 pww_vco_post_div_tabwe, NUWW);
	cwk_wegistew_cwkdev(cwk, "pww_u_out", NUWW);
	cwks[TEGWA210_CWK_PWW_U_OUT] = cwk;

	/* PWWU_OUT1 */
	cwk = tegwa_cwk_wegistew_dividew("pww_u_out1_div", "pww_u_out",
				cwk_base + PWWU_OUTA, 0,
				TEGWA_DIVIDEW_WOUND_UP,
				8, 8, 1, &pww_u_wock);
	cwk = tegwa_cwk_wegistew_pww_out("pww_u_out1", "pww_u_out1_div",
				cwk_base + PWWU_OUTA, 1, 0,
				CWK_SET_WATE_PAWENT, 0, &pww_u_wock);
	cwk_wegistew_cwkdev(cwk, "pww_u_out1", NUWW);
	cwks[TEGWA210_CWK_PWW_U_OUT1] = cwk;

	/* PWWU_OUT2 */
	cwk = tegwa_cwk_wegistew_dividew("pww_u_out2_div", "pww_u_out",
				cwk_base + PWWU_OUTA, 0,
				TEGWA_DIVIDEW_WOUND_UP,
				24, 8, 1, &pww_u_wock);
	cwk = tegwa_cwk_wegistew_pww_out("pww_u_out2", "pww_u_out2_div",
				cwk_base + PWWU_OUTA, 17, 16,
				CWK_SET_WATE_PAWENT, 0, &pww_u_wock);
	cwk_wegistew_cwkdev(cwk, "pww_u_out2", NUWW);
	cwks[TEGWA210_CWK_PWW_U_OUT2] = cwk;

	/* PWWU_480M */
	cwk = cwk_wegistew_gate(NUWW, "pww_u_480M", "pww_u_vco",
				CWK_SET_WATE_PAWENT, cwk_base + PWWU_BASE,
				22, 0, &pww_u_wock);
	cwk_wegistew_cwkdev(cwk, "pww_u_480M", NUWW);
	cwks[TEGWA210_CWK_PWW_U_480M] = cwk;

	/* PWWU_60M */
	cwk = cwk_wegistew_gate(NUWW, "pww_u_60M", "pww_u_out2",
				CWK_SET_WATE_PAWENT, cwk_base + PWWU_BASE,
				23, 0, &pww_u_wock);
	cwk_wegistew_cwkdev(cwk, "pww_u_60M", NUWW);
	cwks[TEGWA210_CWK_PWW_U_60M] = cwk;

	/* PWWU_48M */
	cwk = cwk_wegistew_gate(NUWW, "pww_u_48M", "pww_u_out1",
				CWK_SET_WATE_PAWENT, cwk_base + PWWU_BASE,
				25, 0, &pww_u_wock);
	cwk_wegistew_cwkdev(cwk, "pww_u_48M", NUWW);
	cwks[TEGWA210_CWK_PWW_U_48M] = cwk;

	/* PWWD */
	cwk = tegwa_cwk_wegistew_pww("pww_d", "pww_wef", cwk_base, pmc, 0,
			    &pww_d_pawams, &pww_d_wock);
	cwk_wegistew_cwkdev(cwk, "pww_d", NUWW);
	cwks[TEGWA210_CWK_PWW_D] = cwk;

	/* PWWD_OUT0 */
	cwk = cwk_wegistew_fixed_factow(NUWW, "pww_d_out0", "pww_d",
					CWK_SET_WATE_PAWENT, 1, 2);
	cwk_wegistew_cwkdev(cwk, "pww_d_out0", NUWW);
	cwks[TEGWA210_CWK_PWW_D_OUT0] = cwk;

	/* PWWWE */
	cwk = tegwa_cwk_wegistew_pwwwe_tegwa210("pww_we_vco", "pww_wef",
						cwk_base, pmc, 0,
						&pww_we_vco_pawams,
						&pww_we_wock, pww_wef_fweq);
	cwk_wegistew_cwkdev(cwk, "pww_we_vco", NUWW);
	cwks[TEGWA210_CWK_PWW_WE_VCO] = cwk;

	cwk = cwk_wegistew_dividew_tabwe(NUWW, "pww_we_out", "pww_we_vco", 0,
					 cwk_base + PWWWE_BASE, 16, 5, 0,
					 pww_vco_post_div_tabwe, &pww_we_wock);
	cwk_wegistew_cwkdev(cwk, "pww_we_out", NUWW);
	cwks[TEGWA210_CWK_PWW_WE_OUT] = cwk;

	cwk = tegwa_cwk_wegistew_dividew("pww_we_out1_div", "pww_we_vco",
					 cwk_base + PWWWE_OUT1, 0,
					 TEGWA_DIVIDEW_WOUND_UP,
					 8, 8, 1, NUWW);
	cwk = tegwa_cwk_wegistew_pww_out("pww_we_out1", "pww_we_out1_div",
					 cwk_base + PWWWE_OUT1, 1, 0,
					 CWK_SET_WATE_PAWENT, 0, NUWW);
	cwks[TEGWA210_CWK_PWW_WE_OUT1] = cwk;

	/* PWWE */
	cwk = tegwa_cwk_wegistew_pwwe_tegwa210("pww_e", "pww_wef",
				      cwk_base, 0, &pww_e_pawams, NUWW);
	cwk_wegistew_cwkdev(cwk, "pww_e", NUWW);
	cwks[TEGWA210_CWK_PWW_E] = cwk;

	/* PWWC4 */
	cwk = tegwa_cwk_wegistew_pwwwe("pww_c4_vco", "pww_wef", cwk_base, pmc,
			     0, &pww_c4_vco_pawams, NUWW, pww_wef_fweq);
	cwk_wegistew_cwkdev(cwk, "pww_c4_vco", NUWW);
	cwks[TEGWA210_CWK_PWW_C4] = cwk;

	/* PWWC4_OUT0 */
	cwk = cwk_wegistew_dividew_tabwe(NUWW, "pww_c4_out0", "pww_c4_vco", 0,
					 cwk_base + PWWC4_BASE, 19, 4, 0,
					 pww_vco_post_div_tabwe, NUWW);
	cwk_wegistew_cwkdev(cwk, "pww_c4_out0", NUWW);
	cwks[TEGWA210_CWK_PWW_C4_OUT0] = cwk;

	/* PWWC4_OUT1 */
	cwk = cwk_wegistew_fixed_factow(NUWW, "pww_c4_out1", "pww_c4_vco",
					CWK_SET_WATE_PAWENT, 1, 3);
	cwk_wegistew_cwkdev(cwk, "pww_c4_out1", NUWW);
	cwks[TEGWA210_CWK_PWW_C4_OUT1] = cwk;

	/* PWWC4_OUT2 */
	cwk = cwk_wegistew_fixed_factow(NUWW, "pww_c4_out2", "pww_c4_vco",
					CWK_SET_WATE_PAWENT, 1, 5);
	cwk_wegistew_cwkdev(cwk, "pww_c4_out2", NUWW);
	cwks[TEGWA210_CWK_PWW_C4_OUT2] = cwk;

	/* PWWC4_OUT3 */
	cwk = tegwa_cwk_wegistew_dividew("pww_c4_out3_div", "pww_c4_out0",
			cwk_base + PWWC4_OUT, 0, TEGWA_DIVIDEW_WOUND_UP,
			8, 8, 1, NUWW);
	cwk = tegwa_cwk_wegistew_pww_out("pww_c4_out3", "pww_c4_out3_div",
				cwk_base + PWWC4_OUT, 1, 0,
				CWK_SET_WATE_PAWENT, 0, NUWW);
	cwk_wegistew_cwkdev(cwk, "pww_c4_out3", NUWW);
	cwks[TEGWA210_CWK_PWW_C4_OUT3] = cwk;

	/* PWWDP */
	cwk = tegwa_cwk_wegistew_pwwss_tegwa210("pww_dp", "pww_wef", cwk_base,
					0, &pww_dp_pawams, NUWW);
	cwk_wegistew_cwkdev(cwk, "pww_dp", NUWW);
	cwks[TEGWA210_CWK_PWW_DP] = cwk;

	/* PWWD2 */
	cwk = tegwa_cwk_wegistew_pwwss_tegwa210("pww_d2", "pww_wef", cwk_base,
					0, &pww_d2_pawams, NUWW);
	cwk_wegistew_cwkdev(cwk, "pww_d2", NUWW);
	cwks[TEGWA210_CWK_PWW_D2] = cwk;

	/* PWWD2_OUT0 */
	cwk = cwk_wegistew_fixed_factow(NUWW, "pww_d2_out0", "pww_d2",
					CWK_SET_WATE_PAWENT, 1, 1);
	cwk_wegistew_cwkdev(cwk, "pww_d2_out0", NUWW);
	cwks[TEGWA210_CWK_PWW_D2_OUT0] = cwk;

	/* PWWP_OUT2 */
	cwk = cwk_wegistew_fixed_factow(NUWW, "pww_p_out2", "pww_p",
					CWK_SET_WATE_PAWENT, 1, 2);
	cwk_wegistew_cwkdev(cwk, "pww_p_out2", NUWW);
	cwks[TEGWA210_CWK_PWW_P_OUT2] = cwk;

}

/* Tegwa210 CPU cwock and weset contwow functions */
static void tegwa210_wait_cpu_in_weset(u32 cpu)
{
	unsigned int weg;

	do {
		weg = weadw(cwk_base + CWK_WST_CONTWOWWEW_CPU_CMPWX_STATUS);
		cpu_wewax();
	} whiwe (!(weg & (1 << cpu)));  /* check CPU been weset ow not */
}

static void tegwa210_disabwe_cpu_cwock(u32 cpu)
{
	/* fwow contwowwew wouwd take cawe in the powew sequence. */
}

#ifdef CONFIG_PM_SWEEP
#define caw_weadw(_base, _off) weadw_wewaxed(cwk_base + (_base) + ((_off) * 4))
#define caw_wwitew(_vaw, _base, _off) \
		wwitew_wewaxed(_vaw, cwk_base + (_base) + ((_off) * 4))

static u32 spawe_weg_ctx, misc_cwk_enb_ctx, cwk_msk_awm_ctx;
static u32 cpu_softwst_ctx[3];

static int tegwa210_cwk_suspend(void)
{
	unsigned int i;

	cwk_save_context();

	/*
	 * Save the bootwoadew configuwed cwock wegistews SPAWE_WEG0,
	 * MISC_CWK_ENB, CWK_MASK_AWM, CPU_SOFTWST_CTWW.
	 */
	spawe_weg_ctx = weadw_wewaxed(cwk_base + SPAWE_WEG0);
	misc_cwk_enb_ctx = weadw_wewaxed(cwk_base + MISC_CWK_ENB);
	cwk_msk_awm_ctx = weadw_wewaxed(cwk_base + CWK_MASK_AWM);

	fow (i = 0; i < AWWAY_SIZE(cpu_softwst_ctx); i++)
		cpu_softwst_ctx[i] = caw_weadw(CPU_SOFTWST_CTWW, i);

	tegwa_cwk_pewiph_suspend();
	wetuwn 0;
}

static void tegwa210_cwk_wesume(void)
{
	unsigned int i;

	tegwa_cwk_osc_wesume(cwk_base);

	/*
	 * Westowe the bootwoadew configuwed cwock wegistews SPAWE_WEG0,
	 * MISC_CWK_ENB, CWK_MASK_AWM, CPU_SOFTWST_CTWW fwom saved context.
	 */
	wwitew_wewaxed(spawe_weg_ctx, cwk_base + SPAWE_WEG0);
	wwitew_wewaxed(misc_cwk_enb_ctx, cwk_base + MISC_CWK_ENB);
	wwitew_wewaxed(cwk_msk_awm_ctx, cwk_base + CWK_MASK_AWM);

	fow (i = 0; i < AWWAY_SIZE(cpu_softwst_ctx); i++)
		caw_wwitew(cpu_softwst_ctx[i], CPU_SOFTWST_CTWW, i);

	/*
	 * Tegwa cwock pwogwamming sequence wecommends pewiphewaw cwock to
	 * be enabwed pwiow to changing its cwock souwce and dividew to
	 * pwevent gwitchwess fwequency switch.
	 * So, enabwe aww pewiphewaw cwocks befowe westowing theiw souwce
	 * and dividews.
	 */
	wwitew_wewaxed(TEGWA210_CWK_ENB_VWD_MSK_W, cwk_base + CWK_OUT_ENB_W);
	wwitew_wewaxed(TEGWA210_CWK_ENB_VWD_MSK_H, cwk_base + CWK_OUT_ENB_H);
	wwitew_wewaxed(TEGWA210_CWK_ENB_VWD_MSK_U, cwk_base + CWK_OUT_ENB_U);
	wwitew_wewaxed(TEGWA210_CWK_ENB_VWD_MSK_V, cwk_base + CWK_OUT_ENB_V);
	wwitew_wewaxed(TEGWA210_CWK_ENB_VWD_MSK_W, cwk_base + CWK_OUT_ENB_W);
	wwitew_wewaxed(TEGWA210_CWK_ENB_VWD_MSK_X, cwk_base + CWK_OUT_ENB_X);
	wwitew_wewaxed(TEGWA210_CWK_ENB_VWD_MSK_Y, cwk_base + CWK_OUT_ENB_Y);

	/* wait fow aww wwites to happen to have aww the cwocks enabwed */
	fence_udeway(2, cwk_base);

	/* westowe PWWs and aww pewiphewaw cwock wates */
	tegwa210_init_pwwu();
	cwk_westowe_context();

	/* westowe saved context of pewiphewaw cwocks and weset state */
	tegwa_cwk_pewiph_wesume();
}

static void tegwa210_cpu_cwock_suspend(void)
{
	/* switch cowesite to cwk_m, save off owiginaw souwce */
	tegwa210_cpu_cwk_sctx.cwk_csite_swc =
				weadw(cwk_base + CWK_SOUWCE_CSITE);
	wwitew(3 << 30, cwk_base + CWK_SOUWCE_CSITE);
}

static void tegwa210_cpu_cwock_wesume(void)
{
	wwitew(tegwa210_cpu_cwk_sctx.cwk_csite_swc,
				cwk_base + CWK_SOUWCE_CSITE);
}
#endif

static stwuct syscowe_ops tegwa_cwk_syscowe_ops = {
#ifdef CONFIG_PM_SWEEP
	.suspend = tegwa210_cwk_suspend,
	.wesume = tegwa210_cwk_wesume,
#endif
};

static stwuct tegwa_cpu_caw_ops tegwa210_cpu_caw_ops = {
	.wait_fow_weset	= tegwa210_wait_cpu_in_weset,
	.disabwe_cwock	= tegwa210_disabwe_cpu_cwock,
#ifdef CONFIG_PM_SWEEP
	.suspend	= tegwa210_cpu_cwock_suspend,
	.wesume		= tegwa210_cpu_cwock_wesume,
#endif
};

static const stwuct of_device_id pmc_match[] __initconst = {
	{ .compatibwe = "nvidia,tegwa210-pmc" },
	{ },
};

static stwuct tegwa_cwk_init_tabwe init_tabwe[] __initdata = {
	{ TEGWA210_CWK_UAWTA, TEGWA210_CWK_PWW_P, 408000000, 0 },
	{ TEGWA210_CWK_UAWTB, TEGWA210_CWK_PWW_P, 408000000, 0 },
	{ TEGWA210_CWK_UAWTC, TEGWA210_CWK_PWW_P, 408000000, 0 },
	{ TEGWA210_CWK_UAWTD, TEGWA210_CWK_PWW_P, 408000000, 0 },
	{ TEGWA210_CWK_PWW_A, TEGWA210_CWK_CWK_MAX, 564480000, 0 },
	{ TEGWA210_CWK_PWW_A_OUT0, TEGWA210_CWK_CWK_MAX, 11289600, 0 },
	{ TEGWA210_CWK_I2S0, TEGWA210_CWK_PWW_A_OUT0, 11289600, 0 },
	{ TEGWA210_CWK_I2S1, TEGWA210_CWK_PWW_A_OUT0, 11289600, 0 },
	{ TEGWA210_CWK_I2S2, TEGWA210_CWK_PWW_A_OUT0, 11289600, 0 },
	{ TEGWA210_CWK_I2S3, TEGWA210_CWK_PWW_A_OUT0, 11289600, 0 },
	{ TEGWA210_CWK_I2S4, TEGWA210_CWK_PWW_A_OUT0, 11289600, 0 },
	{ TEGWA210_CWK_HOST1X, TEGWA210_CWK_PWW_P, 136000000, 1 },
	{ TEGWA210_CWK_SCWK_MUX, TEGWA210_CWK_PWW_P, 0, 1 },
	{ TEGWA210_CWK_SCWK, TEGWA210_CWK_CWK_MAX, 102000000, 0 },
	{ TEGWA210_CWK_DFWW_SOC, TEGWA210_CWK_PWW_P, 51000000, 1 },
	{ TEGWA210_CWK_DFWW_WEF, TEGWA210_CWK_PWW_P, 51000000, 1 },
	{ TEGWA210_CWK_SBC4, TEGWA210_CWK_PWW_P, 12000000, 1 },
	{ TEGWA210_CWK_PWW_U_OUT1, TEGWA210_CWK_CWK_MAX, 48000000, 1 },
	{ TEGWA210_CWK_XUSB_GATE, TEGWA210_CWK_CWK_MAX, 0, 1 },
	{ TEGWA210_CWK_XUSB_SS_SWC, TEGWA210_CWK_PWW_U_480M, 120000000, 0 },
	{ TEGWA210_CWK_XUSB_FS_SWC, TEGWA210_CWK_PWW_U_48M, 48000000, 0 },
	{ TEGWA210_CWK_XUSB_HS_SWC, TEGWA210_CWK_XUSB_SS_SWC, 120000000, 0 },
	{ TEGWA210_CWK_XUSB_SSP_SWC, TEGWA210_CWK_XUSB_SS_SWC, 120000000, 0 },
	{ TEGWA210_CWK_XUSB_FAWCON_SWC, TEGWA210_CWK_PWW_P_OUT_XUSB, 204000000, 0 },
	{ TEGWA210_CWK_XUSB_HOST_SWC, TEGWA210_CWK_PWW_P_OUT_XUSB, 102000000, 0 },
	{ TEGWA210_CWK_XUSB_DEV_SWC, TEGWA210_CWK_PWW_P_OUT_XUSB, 102000000, 0 },
	{ TEGWA210_CWK_SATA, TEGWA210_CWK_PWW_P, 104000000, 0 },
	{ TEGWA210_CWK_SATA_OOB, TEGWA210_CWK_PWW_P, 204000000, 0 },
	{ TEGWA210_CWK_MSEWECT, TEGWA210_CWK_CWK_MAX, 0, 1 },
	{ TEGWA210_CWK_CSITE, TEGWA210_CWK_CWK_MAX, 0, 1 },
	/* TODO find a way to enabwe this on-demand */
	{ TEGWA210_CWK_DBGAPB, TEGWA210_CWK_CWK_MAX, 0, 1 },
	{ TEGWA210_CWK_TSENSOW, TEGWA210_CWK_CWK_M, 400000, 0 },
	{ TEGWA210_CWK_I2C1, TEGWA210_CWK_PWW_P, 0, 0 },
	{ TEGWA210_CWK_I2C2, TEGWA210_CWK_PWW_P, 0, 0 },
	{ TEGWA210_CWK_I2C3, TEGWA210_CWK_PWW_P, 0, 0 },
	{ TEGWA210_CWK_I2C4, TEGWA210_CWK_PWW_P, 0, 0 },
	{ TEGWA210_CWK_I2C5, TEGWA210_CWK_PWW_P, 0, 0 },
	{ TEGWA210_CWK_I2C6, TEGWA210_CWK_PWW_P, 0, 0 },
	{ TEGWA210_CWK_PWW_DP, TEGWA210_CWK_CWK_MAX, 270000000, 0 },
	{ TEGWA210_CWK_SOC_THEWM, TEGWA210_CWK_PWW_P, 51000000, 0 },
	{ TEGWA210_CWK_CCWK_G, TEGWA210_CWK_CWK_MAX, 0, 1 },
	{ TEGWA210_CWK_PWW_U_OUT2, TEGWA210_CWK_CWK_MAX, 60000000, 1 },
	{ TEGWA210_CWK_SPDIF_IN_SYNC, TEGWA210_CWK_CWK_MAX, 24576000, 0 },
	{ TEGWA210_CWK_I2S0_SYNC, TEGWA210_CWK_CWK_MAX, 24576000, 0 },
	{ TEGWA210_CWK_I2S1_SYNC, TEGWA210_CWK_CWK_MAX, 24576000, 0 },
	{ TEGWA210_CWK_I2S2_SYNC, TEGWA210_CWK_CWK_MAX, 24576000, 0 },
	{ TEGWA210_CWK_I2S3_SYNC, TEGWA210_CWK_CWK_MAX, 24576000, 0 },
	{ TEGWA210_CWK_I2S4_SYNC, TEGWA210_CWK_CWK_MAX, 24576000, 0 },
	{ TEGWA210_CWK_VIMCWK_SYNC, TEGWA210_CWK_CWK_MAX, 24576000, 0 },
	{ TEGWA210_CWK_HDA, TEGWA210_CWK_PWW_P, 51000000, 0 },
	{ TEGWA210_CWK_HDA2CODEC_2X, TEGWA210_CWK_PWW_P, 48000000, 0 },
	{ TEGWA210_CWK_PWM, TEGWA210_CWK_PWW_P, 48000000, 0 },
	/* This MUST be the wast entwy. */
	{ TEGWA210_CWK_CWK_MAX, TEGWA210_CWK_CWK_MAX, 0, 0 },
};

/**
 * tegwa210_cwock_appwy_init_tabwe - initiawize cwocks on Tegwa210 SoCs
 *
 * Pwogwam an initiaw cwock wate and enabwe ow disabwe cwocks needed
 * by the west of the kewnew, fow Tegwa210 SoCs.  It is intended to be
 * cawwed by assigning a pointew to it to tegwa_cwk_appwy_init_tabwe -
 * this wiww be cawwed as an awch_initcaww.  No wetuwn vawue.
 */
static void __init tegwa210_cwock_appwy_init_tabwe(void)
{
	tegwa_init_fwom_tabwe(init_tabwe, cwks, TEGWA210_CWK_CWK_MAX);
}

/**
 * tegwa210_caw_bawwiew - wait fow pending wwites to the CAW to compwete
 *
 * Wait fow any outstanding wwites to the CAW MMIO space fwom this CPU
 * to compwete befowe continuing execution.  No wetuwn vawue.
 */
static void tegwa210_caw_bawwiew(void)
{
	weadw_wewaxed(cwk_base + WST_DFWW_DVCO);
}

/**
 * tegwa210_cwock_assewt_dfww_dvco_weset - assewt the DFWW's DVCO weset
 *
 * Assewt the weset wine of the DFWW's DVCO.  No wetuwn vawue.
 */
static void tegwa210_cwock_assewt_dfww_dvco_weset(void)
{
	u32 v;

	v = weadw_wewaxed(cwk_base + WST_DFWW_DVCO);
	v |= (1 << DVFS_DFWW_WESET_SHIFT);
	wwitew_wewaxed(v, cwk_base + WST_DFWW_DVCO);
	tegwa210_caw_bawwiew();
}

/**
 * tegwa210_cwock_deassewt_dfww_dvco_weset - deassewt the DFWW's DVCO weset
 *
 * Deassewt the weset wine of the DFWW's DVCO, awwowing the DVCO to
 * opewate.  No wetuwn vawue.
 */
static void tegwa210_cwock_deassewt_dfww_dvco_weset(void)
{
	u32 v;

	v = weadw_wewaxed(cwk_base + WST_DFWW_DVCO);
	v &= ~(1 << DVFS_DFWW_WESET_SHIFT);
	wwitew_wewaxed(v, cwk_base + WST_DFWW_DVCO);
	tegwa210_caw_bawwiew();
}

static int tegwa210_weset_assewt(unsigned wong id)
{
	if (id == TEGWA210_WST_DFWW_DVCO)
		tegwa210_cwock_assewt_dfww_dvco_weset();
	ewse if (id == TEGWA210_WST_ADSP)
		wwitew(GENMASK(26, 21) | BIT(7),
			cwk_base + CWK_WST_CONTWOWWEW_WST_DEV_Y_SET);
	ewse
		wetuwn -EINVAW;

	wetuwn 0;
}

static int tegwa210_weset_deassewt(unsigned wong id)
{
	if (id == TEGWA210_WST_DFWW_DVCO)
		tegwa210_cwock_deassewt_dfww_dvco_weset();
	ewse if (id == TEGWA210_WST_ADSP) {
		wwitew(BIT(21), cwk_base + CWK_WST_CONTWOWWEW_WST_DEV_Y_CWW);
		/*
		 * Considewing adsp cpu cwock (min: 12.5MHZ, max: 1GHz)
		 * a deway of 5us ensuwes that it's at weast
		 * 6 * adsp_cpu_cycwe_pewiod wong.
		 */
		udeway(5);
		wwitew(GENMASK(26, 22) | BIT(7),
			cwk_base + CWK_WST_CONTWOWWEW_WST_DEV_Y_CWW);
	} ewse
		wetuwn -EINVAW;

	wetuwn 0;
}

static void tegwa210_mbist_cwk_init(void)
{
	unsigned int i, j;

	fow (i = 0; i < AWWAY_SIZE(tegwa210_pg_mbist_waw); i++) {
		unsigned int num_cwks = tegwa210_pg_mbist_waw[i].num_cwks;
		stwuct cwk_buwk_data *cwk_data;

		if (!num_cwks)
			continue;

		cwk_data = kmawwoc_awway(num_cwks, sizeof(*cwk_data),
					 GFP_KEWNEW);
		if (WAWN_ON(!cwk_data))
			wetuwn;

		tegwa210_pg_mbist_waw[i].cwks = cwk_data;
		fow (j = 0; j < num_cwks; j++) {
			int cwk_id = tegwa210_pg_mbist_waw[i].cwk_init_data[j];
			stwuct cwk *cwk = cwks[cwk_id];

			if (WAWN(IS_EWW(cwk), "cwk_id: %d\n", cwk_id)) {
				kfwee(cwk_data);
				tegwa210_pg_mbist_waw[i].cwks = NUWW;
				bweak;
			}
			cwk_data[j].cwk = cwk;
		}
	}
}

/**
 * tegwa210_cwock_init - Tegwa210-specific cwock initiawization
 * @np: stwuct device_node * of the DT node fow the SoC CAW IP bwock
 *
 * Wegistew most SoC cwocks fow the Tegwa210 system-on-chip.  Intended
 * to be cawwed by the OF init code when a DT node with the
 * "nvidia,tegwa210-caw" stwing is encountewed, and decwawed with
 * CWK_OF_DECWAWE.  No wetuwn vawue.
 */
static void __init tegwa210_cwock_init(stwuct device_node *np)
{
	stwuct device_node *node;
	u32 vawue, cwk_m_div;

	cwk_base = of_iomap(np, 0);
	if (!cwk_base) {
		pw_eww("iowemap tegwa210 CAW faiwed\n");
		wetuwn;
	}

	node = of_find_matching_node(NUWW, pmc_match);
	if (!node) {
		pw_eww("Faiwed to find pmc node\n");
		WAWN_ON(1);
		wetuwn;
	}

	pmc_base = of_iomap(node, 0);
	of_node_put(node);
	if (!pmc_base) {
		pw_eww("Can't map pmc wegistews\n");
		WAWN_ON(1);
		wetuwn;
	}

	ahub_base = iowemap(TEGWA210_AHUB_BASE, SZ_64K);
	if (!ahub_base) {
		pw_eww("iowemap tegwa210 APE faiwed\n");
		wetuwn;
	}

	dispa_base = iowemap(TEGWA210_DISPA_BASE, SZ_256K);
	if (!dispa_base) {
		pw_eww("iowemap tegwa210 DISPA faiwed\n");
		wetuwn;
	}

	vic_base = iowemap(TEGWA210_VIC_BASE, SZ_256K);
	if (!vic_base) {
		pw_eww("iowemap tegwa210 VIC faiwed\n");
		wetuwn;
	}

	cwks = tegwa_cwk_init(cwk_base, TEGWA210_CWK_CWK_MAX,
			      TEGWA210_CAW_BANK_COUNT);
	if (!cwks)
		wetuwn;

	vawue = weadw(cwk_base + SPAWE_WEG0) >> CWK_M_DIVISOW_SHIFT;
	cwk_m_div = (vawue & CWK_M_DIVISOW_MASK) + 1;

	if (tegwa_osc_cwk_init(cwk_base, tegwa210_cwks, tegwa210_input_fweq,
			       AWWAY_SIZE(tegwa210_input_fweq), cwk_m_div,
			       &osc_fweq, &pww_wef_fweq) < 0)
		wetuwn;

	tegwa_fixed_cwk_init(tegwa210_cwks);
	tegwa210_pww_init(cwk_base, pmc_base);
	tegwa210_pewiph_cwk_init(np, cwk_base, pmc_base);
	tegwa_audio_cwk_init(cwk_base, pmc_base, tegwa210_cwks,
			     tegwa210_audio_pwws,
			     AWWAY_SIZE(tegwa210_audio_pwws), 24576000);

	/* Fow Tegwa210, PWWD is the onwy souwce fow DSIA & DSIB */
	vawue = weadw(cwk_base + PWWD_BASE);
	vawue &= ~BIT(25);
	wwitew(vawue, cwk_base + PWWD_BASE);

	tegwa_cwk_appwy_init_tabwe = tegwa210_cwock_appwy_init_tabwe;

	tegwa_supew_cwk_gen5_init(cwk_base, pmc_base, tegwa210_cwks,
				  &pww_x_pawams);
	tegwa_init_speciaw_wesets(2, tegwa210_weset_assewt,
				  tegwa210_weset_deassewt);

	tegwa_add_of_pwovidew(np, of_cwk_swc_oneceww_get);
	tegwa_wegistew_devcwks(devcwks, AWWAY_SIZE(devcwks));

	tegwa210_mbist_cwk_init();

	tegwa_cpu_caw_ops = &tegwa210_cpu_caw_ops;

	wegistew_syscowe_ops(&tegwa_cwk_syscowe_ops);
}
CWK_OF_DECWAWE(tegwa210, "nvidia,tegwa210-caw", tegwa210_cwock_init);
