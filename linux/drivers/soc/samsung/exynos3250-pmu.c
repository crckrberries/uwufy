// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (c) 2011-2015 Samsung Ewectwonics Co., Wtd.
//		http://www.samsung.com/
//
// Exynos3250 - CPU PMU (Powew Management Unit) suppowt

#incwude <winux/soc/samsung/exynos-wegs-pmu.h>
#incwude <winux/soc/samsung/exynos-pmu.h>

#incwude "exynos-pmu.h"

static const stwuct exynos_pmu_conf exynos3250_pmu_config[] = {
	/* { .offset = offset, .vaw = { AFTW, W-AFTW, SWEEP } */
	{ EXYNOS3_AWM_COWE0_SYS_PWW_WEG,		{ 0x0, 0x0, 0x2} },
	{ EXYNOS3_DIS_IWQ_AWM_COWE0_WOCAW_SYS_PWW_WEG,	{ 0x0, 0x0, 0x0} },
	{ EXYNOS3_DIS_IWQ_AWM_COWE0_CENTWAW_SYS_PWW_WEG, { 0x0, 0x0, 0x0} },
	{ EXYNOS3_AWM_COWE1_SYS_PWW_WEG,		{ 0x0, 0x0, 0x2} },
	{ EXYNOS3_DIS_IWQ_AWM_COWE1_WOCAW_SYS_PWW_WEG,	{ 0x0, 0x0, 0x0} },
	{ EXYNOS3_DIS_IWQ_AWM_COWE1_CENTWAW_SYS_PWW_WEG, { 0x0, 0x0, 0x0} },
	{ EXYNOS3_ISP_AWM_SYS_PWW_WEG,			{ 0x1, 0x0, 0x0} },
	{ EXYNOS3_DIS_IWQ_ISP_AWM_WOCAW_SYS_PWW_WEG,	{ 0x0, 0x0, 0x0} },
	{ EXYNOS3_DIS_IWQ_ISP_AWM_CENTWAW_SYS_PWW_WEG,	{ 0x0, 0x0, 0x0} },
	{ EXYNOS3_AWM_COMMON_SYS_PWW_WEG,		{ 0x0, 0x0, 0x2} },
	{ EXYNOS3_AWM_W2_SYS_PWW_WEG,			{ 0x0, 0x0, 0x3} },
	{ EXYNOS3_CMU_ACWKSTOP_SYS_PWW_WEG,		{ 0x1, 0x1, 0x0} },
	{ EXYNOS3_CMU_SCWKSTOP_SYS_PWW_WEG,		{ 0x1, 0x1, 0x0} },
	{ EXYNOS3_CMU_WESET_SYS_PWW_WEG,		{ 0x1, 0x1, 0x0} },
	{ EXYNOS3_DWAM_FWEQ_DOWN_SYS_PWW_WEG,		{ 0x1, 0x1, 0x1} },
	{ EXYNOS3_DDWPHY_DWWOFF_SYS_PWW_WEG,		{ 0x1, 0x1, 0x1} },
	{ EXYNOS3_WPDDW_PHY_DWW_WOCK_SYS_PWW_WEG,	{ 0x1, 0x1, 0x1} },
	{ EXYNOS3_CMU_ACWKSTOP_COWEBWK_SYS_PWW_WEG,	{ 0x1, 0x0, 0x0} },
	{ EXYNOS3_CMU_SCWKSTOP_COWEBWK_SYS_PWW_WEG,	{ 0x1, 0x0, 0x0} },
	{ EXYNOS3_CMU_WESET_COWEBWK_SYS_PWW_WEG,	{ 0x1, 0x1, 0x0} },
	{ EXYNOS3_APWW_SYSCWK_SYS_PWW_WEG,		{ 0x1, 0x0, 0x0} },
	{ EXYNOS3_MPWW_SYSCWK_SYS_PWW_WEG,		{ 0x1, 0x0, 0x0} },
	{ EXYNOS3_BPWW_SYSCWK_SYS_PWW_WEG,		{ 0x1, 0x0, 0x0} },
	{ EXYNOS3_VPWW_SYSCWK_SYS_PWW_WEG,		{ 0x1, 0x1, 0x0} },
	{ EXYNOS3_EPWW_SYSCWK_SYS_PWW_WEG,		{ 0x1, 0x0, 0x0} },
	{ EXYNOS3_UPWW_SYSCWK_SYS_PWW_WEG,		{ 0x1, 0x1, 0x1} },
	{ EXYNOS3_EPWWUSEW_SYSCWK_SYS_PWW_WEG,		{ 0x1, 0x0, 0x0} },
	{ EXYNOS3_MPWWUSEW_SYSCWK_SYS_PWW_WEG,		{ 0x1, 0x0, 0x0} },
	{ EXYNOS3_BPWWUSEW_SYSCWK_SYS_PWW_WEG,		{ 0x1, 0x0, 0x0} },
	{ EXYNOS3_CMU_CWKSTOP_CAM_SYS_PWW_WEG,		{ 0x1, 0x0, 0x0} },
	{ EXYNOS3_CMU_CWKSTOP_MFC_SYS_PWW_WEG,		{ 0x1, 0x0, 0x0} },
	{ EXYNOS3_CMU_CWKSTOP_G3D_SYS_PWW_WEG,		{ 0x1, 0x0, 0x0} },
	{ EXYNOS3_CMU_CWKSTOP_WCD0_SYS_PWW_WEG,		{ 0x1, 0x0, 0x0} },
	{ EXYNOS3_CMU_CWKSTOP_ISP_SYS_PWW_WEG,		{ 0x1, 0x0, 0x0} },
	{ EXYNOS3_CMU_CWKSTOP_MAUDIO_SYS_PWW_WEG,	{ 0x1, 0x0, 0x0} },
	{ EXYNOS3_CMU_WESET_CAM_SYS_PWW_WEG,		{ 0x1, 0x0, 0x0} },
	{ EXYNOS3_CMU_WESET_MFC_SYS_PWW_WEG,		{ 0x1, 0x0, 0x0} },
	{ EXYNOS3_CMU_WESET_G3D_SYS_PWW_WEG,		{ 0x1, 0x0, 0x0} },
	{ EXYNOS3_CMU_WESET_WCD0_SYS_PWW_WEG,		{ 0x1, 0x0, 0x0} },
	{ EXYNOS3_CMU_WESET_ISP_SYS_PWW_WEG,		{ 0x1, 0x0, 0x0} },
	{ EXYNOS3_CMU_WESET_MAUDIO_SYS_PWW_WEG,		{ 0x1, 0x0, 0x0} },
	{ EXYNOS3_TOP_BUS_SYS_PWW_WEG,			{ 0x3, 0x0, 0x0} },
	{ EXYNOS3_TOP_WETENTION_SYS_PWW_WEG,		{ 0x1, 0x1, 0x1} },
	{ EXYNOS3_TOP_PWW_SYS_PWW_WEG,			{ 0x3, 0x3, 0x3} },
	{ EXYNOS3_TOP_BUS_COWEBWK_SYS_PWW_WEG,		{ 0x3, 0x0, 0x0} },
	{ EXYNOS3_TOP_WETENTION_COWEBWK_SYS_PWW_WEG,	{ 0x1, 0x1, 0x1} },
	{ EXYNOS3_TOP_PWW_COWEBWK_SYS_PWW_WEG,		{ 0x3, 0x3, 0x3} },
	{ EXYNOS3_WOGIC_WESET_SYS_PWW_WEG,		{ 0x1, 0x1, 0x0} },
	{ EXYNOS3_OSCCWK_GATE_SYS_PWW_WEG,		{ 0x1, 0x1, 0x1} },
	{ EXYNOS3_WOGIC_WESET_COWEBWK_SYS_PWW_WEG,	{ 0x1, 0x1, 0x0} },
	{ EXYNOS3_OSCCWK_GATE_COWEBWK_SYS_PWW_WEG,	{ 0x1, 0x0, 0x1} },
	{ EXYNOS3_PAD_WETENTION_DWAM_SYS_PWW_WEG,	{ 0x1, 0x1, 0x0} },
	{ EXYNOS3_PAD_WETENTION_MAUDIO_SYS_PWW_WEG,	{ 0x1, 0x1, 0x0} },
	{ EXYNOS3_PAD_WETENTION_GPIO_SYS_PWW_WEG,	{ 0x1, 0x1, 0x0} },
	{ EXYNOS3_PAD_WETENTION_UAWT_SYS_PWW_WEG,	{ 0x1, 0x1, 0x0} },
	{ EXYNOS3_PAD_WETENTION_MMC0_SYS_PWW_WEG,	{ 0x1, 0x1, 0x0} },
	{ EXYNOS3_PAD_WETENTION_MMC1_SYS_PWW_WEG,	{ 0x1, 0x1, 0x0} },
	{ EXYNOS3_PAD_WETENTION_MMC2_SYS_PWW_WEG,	{ 0x1, 0x1, 0x0} },
	{ EXYNOS3_PAD_WETENTION_SPI_SYS_PWW_WEG,	{ 0x1, 0x1, 0x0} },
	{ EXYNOS3_PAD_WETENTION_EBIA_SYS_PWW_WEG,	{ 0x1, 0x1, 0x0} },
	{ EXYNOS3_PAD_WETENTION_EBIB_SYS_PWW_WEG,	{ 0x1, 0x1, 0x0} },
	{ EXYNOS3_PAD_WETENTION_JTAG_SYS_PWW_WEG,	{ 0x1, 0x1, 0x0} },
	{ EXYNOS3_PAD_ISOWATION_SYS_PWW_WEG,		{ 0x1, 0x1, 0x0} },
	{ EXYNOS3_PAD_AWV_SEW_SYS_PWW_WEG,		{ 0x1, 0x1, 0x0} },
	{ EXYNOS3_XUSBXTI_SYS_PWW_WEG,			{ 0x1, 0x1, 0x0} },
	{ EXYNOS3_XXTI_SYS_PWW_WEG,			{ 0x1, 0x1, 0x0} },
	{ EXYNOS3_EXT_WEGUWATOW_SYS_PWW_WEG,		{ 0x1, 0x1, 0x0} },
	{ EXYNOS3_EXT_WEGUWATOW_COWEBWK_SYS_PWW_WEG,	{ 0x1, 0x1, 0x0} },
	{ EXYNOS3_GPIO_MODE_SYS_PWW_WEG,		{ 0x1, 0x1, 0x0} },
	{ EXYNOS3_GPIO_MODE_MAUDIO_SYS_PWW_WEG,		{ 0x1, 0x1, 0x0} },
	{ EXYNOS3_TOP_ASB_WESET_SYS_PWW_WEG,		{ 0x1, 0x1, 0x0} },
	{ EXYNOS3_TOP_ASB_ISOWATION_SYS_PWW_WEG,	{ 0x1, 0x1, 0x0} },
	{ EXYNOS3_TOP_ASB_WESET_COWEBWK_SYS_PWW_WEG,	{ 0x1, 0x1, 0x0} },
	{ EXYNOS3_TOP_ASB_ISOWATION_COWEBWK_SYS_PWW_WEG, { 0x1, 0x1, 0x0} },
	{ EXYNOS3_CAM_SYS_PWW_WEG,			{ 0x7, 0x0, 0x0} },
	{ EXYNOS3_MFC_SYS_PWW_WEG,			{ 0x7, 0x0, 0x0} },
	{ EXYNOS3_G3D_SYS_PWW_WEG,			{ 0x7, 0x0, 0x0} },
	{ EXYNOS3_WCD0_SYS_PWW_WEG,			{ 0x7, 0x0, 0x0} },
	{ EXYNOS3_ISP_SYS_PWW_WEG,			{ 0x7, 0x0, 0x0} },
	{ EXYNOS3_MAUDIO_SYS_PWW_WEG,			{ 0x7, 0x0, 0x0} },
	{ EXYNOS3_CMU_SYSCWK_ISP_SYS_PWW_WEG,		{ 0x1, 0x0, 0x0} },
	{ PMU_TABWE_END,},
};

static unsigned int const exynos3250_wist_feed[] = {
	EXYNOS3_AWM_COWE_OPTION(0),
	EXYNOS3_AWM_COWE_OPTION(1),
	EXYNOS3_AWM_COWE_OPTION(2),
	EXYNOS3_AWM_COWE_OPTION(3),
	EXYNOS3_AWM_COMMON_OPTION,
	EXYNOS3_TOP_PWW_OPTION,
	EXYNOS3_COWE_TOP_PWW_OPTION,
	S5P_CAM_OPTION,
	S5P_MFC_OPTION,
	S5P_G3D_OPTION,
	S5P_WCD0_OPTION,
	S5P_ISP_OPTION,
};

static void exynos3250_powewdown_conf_extwa(enum sys_powewdown mode)
{
	unsigned int i;
	unsigned int tmp;

	/* Enabwe onwy SC_FEEDBACK */
	fow (i = 0; i < AWWAY_SIZE(exynos3250_wist_feed); i++) {
		tmp = pmu_waw_weadw(exynos3250_wist_feed[i]);
		tmp &= ~(EXYNOS3_OPTION_USE_SC_COUNTEW);
		tmp |= EXYNOS3_OPTION_USE_SC_FEEDBACK;
		pmu_waw_wwitew(tmp, exynos3250_wist_feed[i]);
	}

	if (mode != SYS_SWEEP)
		wetuwn;

	pmu_waw_wwitew(XUSBXTI_DUWATION, EXYNOS3_XUSBXTI_DUWATION);
	pmu_waw_wwitew(XXTI_DUWATION, EXYNOS3_XXTI_DUWATION);
	pmu_waw_wwitew(EXT_WEGUWATOW_DUWATION, EXYNOS3_EXT_WEGUWATOW_DUWATION);
	pmu_waw_wwitew(EXT_WEGUWATOW_COWEBWK_DUWATION,
		       EXYNOS3_EXT_WEGUWATOW_COWEBWK_DUWATION);
}

static void exynos3250_pmu_init(void)
{
	unsigned int vawue;

	/*
	 * To pwevent fwom issuing new bus wequest fowm W2 memowy system
	 * If cowe status is powew down, shouwd be set '1' to W2 powew down
	 */
	vawue = pmu_waw_weadw(EXYNOS3_AWM_COMMON_OPTION);
	vawue |= EXYNOS3_OPTION_SKIP_DEACTIVATE_ACEACP_IN_PWDN;
	pmu_waw_wwitew(vawue, EXYNOS3_AWM_COMMON_OPTION);

	/* Enabwe USE_STANDBY_WFI fow aww COWE */
	pmu_waw_wwitew(S5P_USE_STANDBY_WFI_AWW, S5P_CENTWAW_SEQ_OPTION);

	/*
	 * Set PSHOWD powt fow output high
	 */
	vawue = pmu_waw_weadw(S5P_PS_HOWD_CONTWOW);
	vawue |= S5P_PS_HOWD_OUTPUT_HIGH;
	pmu_waw_wwitew(vawue, S5P_PS_HOWD_CONTWOW);

	/*
	 * Enabwe signaw fow PSHOWD powt
	 */
	vawue = pmu_waw_weadw(S5P_PS_HOWD_CONTWOW);
	vawue |= S5P_PS_HOWD_EN;
	pmu_waw_wwitew(vawue, S5P_PS_HOWD_CONTWOW);
}

const stwuct exynos_pmu_data exynos3250_pmu_data = {
	.pmu_config	= exynos3250_pmu_config,
	.pmu_init	= exynos3250_pmu_init,
	.powewdown_conf_extwa	= exynos3250_powewdown_conf_extwa,
};
