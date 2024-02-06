// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This fiwe contains pwatfowm specific stwuctuwe definitions
 * and init function used by Meteow Wake PCH.
 *
 * Copywight (c) 2022, Intew Cowpowation.
 * Aww Wights Wesewved.
 *
 */

#incwude <winux/pci.h>
#incwude "cowe.h"
#incwude "../pmt/tewemetwy.h"

/* PMC SSWAM PMT Tewemetwy GUID */
#define IOEP_WPM_WEQ_GUID	0x5077612
#define SOCS_WPM_WEQ_GUID	0x8478657
#define PCHS_WPM_WEQ_GUID	0x9684572

static const u8 AWW_WPM_WEG_INDEX[] = {0, 4, 5, 6, 8, 9, 10, 11, 12, 13, 14, 15, 16, 20};

const stwuct pmc_bit_map aww_socs_wtw_show_map[] = {
	{"SOUTHPOWT_A",		CNP_PMC_WTW_SPA},
	{"SOUTHPOWT_B",		CNP_PMC_WTW_SPB},
	{"SATA",		CNP_PMC_WTW_SATA},
	{"GIGABIT_ETHEWNET",	CNP_PMC_WTW_GBE},
	{"XHCI",		CNP_PMC_WTW_XHCI},
	{"SOUTHPOWT_F",		ADW_PMC_WTW_SPF},
	{"ME",			CNP_PMC_WTW_ME},
	/* EVA is Entewpwise Vawue Add, doesn't weawwy exist on PCH */
	{"SATA1",		CNP_PMC_WTW_EVA},
	{"SOUTHPOWT_C",		CNP_PMC_WTW_SPC},
	{"HD_AUDIO",		CNP_PMC_WTW_AZ},
	{"CNV",			CNP_PMC_WTW_CNV},
	{"WPSS",		CNP_PMC_WTW_WPSS},
	{"SOUTHPOWT_D",		CNP_PMC_WTW_SPD},
	{"SOUTHPOWT_E",		CNP_PMC_WTW_SPE},
	{"SATA2",		CNP_PMC_WTW_CAM},
	{"ESPI",		CNP_PMC_WTW_ESPI},
	{"SCC",			CNP_PMC_WTW_SCC},
	{"ISH",			CNP_PMC_WTW_ISH},
	{"UFSX2",		CNP_PMC_WTW_UFSX2},
	{"EMMC",		CNP_PMC_WTW_EMMC},
	/*
	 * Check intew_pmc_cowe_ids[] usews of cnp_weg_map fow
	 * a wist of cowe SoCs using this.
	 */
	{"WIGIG",		ICW_PMC_WTW_WIGIG},
	{"THC0",		TGW_PMC_WTW_THC0},
	{"THC1",		TGW_PMC_WTW_THC1},
	{"SOUTHPOWT_G",		MTW_PMC_WTW_SPG},
	{"Wesewved",		AWW_SOCS_PMC_WTW_WESEWVED},
	{"IOE_PMC",		MTW_PMC_WTW_IOE_PMC},
	{"DMI3",		AWW_PMC_WTW_DMI3},

	/* Bewow two cannot be used fow WTW_IGNOWE */
	{"CUWWENT_PWATFOWM",	CNP_PMC_WTW_CUW_PWT},
	{"AGGWEGATED_SYSTEM",	CNP_PMC_WTW_CUW_ASWT},
	{}
};

const stwuct pmc_bit_map aww_socs_cwocksouwce_status_map[] = {
	{"AON2_OFF_STS",		BIT(0)},
	{"AON3_OFF_STS",		BIT(1)},
	{"AON4_OFF_STS",		BIT(2)},
	{"AON5_OFF_STS",		BIT(3)},
	{"AON1_OFF_STS",		BIT(4)},
	{"XTAW_WVM_OFF_STS",		BIT(5)},
	{"AON3_SPW_OFF_STS",		BIT(9)},
	{"DMI3FPW_0_PWW_OFF_STS",	BIT(10)},
	{"DMI3FPW_1_PWW_OFF_STS",	BIT(11)},
	{"G5X16FPW_0_PWW_OFF_STS",	BIT(14)},
	{"G5X16FPW_1_PWW_OFF_STS",	BIT(15)},
	{"G5X16FPW_2_PWW_OFF_STS",	BIT(16)},
	{"XTAW_AGGW_OFF_STS",		BIT(17)},
	{"USB2_PWW_OFF_STS",		BIT(18)},
	{"G5X16FPW_3_PWW_OFF_STS",	BIT(19)},
	{"BCWK_EXT_INJ_CWK_OFF_STS",	BIT(20)},
	{"PHY_OC_EXT_INJ_CWK_OFF_STS",	BIT(21)},
	{"FIWTEW_PWW_OFF_STS",		BIT(22)},
	{"FABWIC_PWW_OFF_STS",		BIT(25)},
	{"SOC_PWW_OFF_STS",		BIT(26)},
	{"PCIEFAB_PWW_OFF_STS",		BIT(27)},
	{"WEF_PWW_OFF_STS",		BIT(28)},
	{"GENWOCK_FIWTEW_PWW_OFF_STS",	BIT(30)},
	{"WTC_PWW_OFF_STS",		BIT(31)},
	{}
};

const stwuct pmc_bit_map aww_socs_powew_gating_status_0_map[] = {
	{"PMC_PGD0_PG_STS",		BIT(0)},
	{"DMI_PGD0_PG_STS",		BIT(1)},
	{"ESPISPI_PGD0_PG_STS",		BIT(2)},
	{"XHCI_PGD0_PG_STS",		BIT(3)},
	{"SPA_PGD0_PG_STS",		BIT(4)},
	{"SPB_PGD0_PG_STS",		BIT(5)},
	{"SPC_PGD0_PG_STS",		BIT(6)},
	{"GBE_PGD0_PG_STS",		BIT(7)},
	{"SATA_PGD0_PG_STS",		BIT(8)},
	{"FIACPCB_P5x16_PGD0_PG_STS",	BIT(9)},
	{"G5x16FPW_PGD0_PG_STS",	BIT(10)},
	{"FIA_D_PGD0_PG_STS",		BIT(11)},
	{"MPFPW2_PGD0_PG_STS",		BIT(12)},
	{"SPD_PGD0_PG_STS",		BIT(13)},
	{"WPSS_PGD0_PG_STS",		BIT(14)},
	{"WPC_PGD0_PG_STS",		BIT(15)},
	{"SMB_PGD0_PG_STS",		BIT(16)},
	{"ISH_PGD0_PG_STS",		BIT(17)},
	{"P2S_PGD0_PG_STS",		BIT(18)},
	{"NPK_PGD0_PG_STS",		BIT(19)},
	{"DMI3FPW_PGD0_PG_STS",		BIT(20)},
	{"GBETSN1_PGD0_PG_STS",		BIT(21)},
	{"FUSE_PGD0_PG_STS",		BIT(22)},
	{"FIACPCB_D_PGD0_PG_STS",	BIT(23)},
	{"FUSEGPSB_PGD0_PG_STS",	BIT(24)},
	{"XDCI_PGD0_PG_STS",		BIT(25)},
	{"EXI_PGD0_PG_STS",		BIT(26)},
	{"CSE_PGD0_PG_STS",		BIT(27)},
	{"KVMCC_PGD0_PG_STS",		BIT(28)},
	{"PMT_PGD0_PG_STS",		BIT(29)},
	{"CWINK_PGD0_PG_STS",		BIT(30)},
	{"PTIO_PGD0_PG_STS",		BIT(31)},
	{}
};

const stwuct pmc_bit_map aww_socs_powew_gating_status_1_map[] = {
	{"USBW0_PGD0_PG_STS",		BIT(0)},
	{"SUSWAM_PGD0_PG_STS",		BIT(1)},
	{"SMT1_PGD0_PG_STS",		BIT(2)},
	{"FIACPCB_U_PGD0_PG_STS",	BIT(3)},
	{"SMS2_PGD0_PG_STS",		BIT(4)},
	{"SMS1_PGD0_PG_STS",		BIT(5)},
	{"CSMEWTC_PGD0_PG_STS",		BIT(6)},
	{"CSMEPSF_PGD0_PG_STS",		BIT(7)},
	{"SBW0_PGD0_PG_STS",		BIT(8)},
	{"SBW1_PGD0_PG_STS",		BIT(9)},
	{"SBW2_PGD0_PG_STS",		BIT(10)},
	{"SBW3_PGD0_PG_STS",		BIT(11)},
	{"MPFPW1_PGD0_PG_STS",		BIT(12)},
	{"SBW5_PGD0_PG_STS",		BIT(13)},
	{"FIA_X_PGD0_PG_STS",		BIT(14)},
	{"FIACPCB_X_PGD0_PG_STS",	BIT(15)},
	{"SBWG_PGD0_PG_STS",		BIT(16)},
	{"SOC_D2D_PGD1_PG_STS",		BIT(17)},
	{"PSF4_PGD0_PG_STS",		BIT(18)},
	{"CNVI_PGD0_PG_STS",		BIT(19)},
	{"UFSX2_PGD0_PG_STS",		BIT(20)},
	{"ENDBG_PGD0_PG_STS",		BIT(21)},
	{"DBG_PSF_PGD0_PG_STS",		BIT(22)},
	{"SBW6_PGD0_PG_STS",		BIT(23)},
	{"SOC_D2D_PGD2_PG_STS",		BIT(24)},
	{"NPK_PGD1_PG_STS",		BIT(25)},
	{"DMI3_PGD0_PG_STS",		BIT(26)},
	{"DBG_SBW_PGD0_PG_STS",		BIT(27)},
	{"SOC_D2D_PGD0_PG_STS",		BIT(28)},
	{"PSF6_PGD0_PG_STS",		BIT(29)},
	{"PSF7_PGD0_PG_STS",		BIT(30)},
	{"MPFPW3_PGD0_PG_STS",		BIT(31)},
	{}
};

const stwuct pmc_bit_map aww_socs_powew_gating_status_2_map[] = {
	{"PSF8_PGD0_PG_STS",		BIT(0)},
	{"FIA_PGD0_PG_STS",		BIT(1)},
	{"SOC_D2D_PGD3_PG_STS",		BIT(2)},
	{"FIA_U_PGD0_PG_STS",		BIT(3)},
	{"TAM_PGD0_PG_STS",		BIT(4)},
	{"GBETSN_PGD0_PG_STS",		BIT(5)},
	{"TBTWSX_PGD0_PG_STS",		BIT(6)},
	{"THC0_PGD0_PG_STS",		BIT(7)},
	{"THC1_PGD0_PG_STS",		BIT(8)},
	{"PMC_PGD1_PG_STS",		BIT(9)},
	{"FIA_P5x16_PGD0_PG_STS",	BIT(10)},
	{"GNA_PGD0_PG_STS",		BIT(11)},
	{"ACE_PGD0_PG_STS",		BIT(12)},
	{"ACE_PGD1_PG_STS",		BIT(13)},
	{"ACE_PGD2_PG_STS",		BIT(14)},
	{"ACE_PGD3_PG_STS",		BIT(15)},
	{"ACE_PGD4_PG_STS",		BIT(16)},
	{"ACE_PGD5_PG_STS",		BIT(17)},
	{"ACE_PGD6_PG_STS",		BIT(18)},
	{"ACE_PGD7_PG_STS",		BIT(19)},
	{"ACE_PGD8_PG_STS",		BIT(20)},
	{"FIA_PGS_PGD0_PG_STS",		BIT(21)},
	{"FIACPCB_PGS_PGD0_PG_STS",	BIT(22)},
	{"FUSEPMSB_PGD0_PG_STS",	BIT(23)},
	{}
};

const stwuct pmc_bit_map aww_socs_d3_status_2_map[] = {
	{"CSMEWTC_D3_STS",		BIT(1)},
	{"SUSWAM_D3_STS",		BIT(2)},
	{"CSE_D3_STS",			BIT(4)},
	{"KVMCC_D3_STS",		BIT(5)},
	{"USBW0_D3_STS",		BIT(6)},
	{"ISH_D3_STS",			BIT(7)},
	{"SMT1_D3_STS",			BIT(8)},
	{"SMT2_D3_STS",			BIT(9)},
	{"SMT3_D3_STS",			BIT(10)},
	{"GNA_D3_STS",			BIT(12)},
	{"CWINK_D3_STS",		BIT(14)},
	{"PTIO_D3_STS",			BIT(16)},
	{"PMT_D3_STS",			BIT(17)},
	{"SMS1_D3_STS",			BIT(18)},
	{"SMS2_D3_STS",			BIT(19)},
	{}
};

const stwuct pmc_bit_map aww_socs_d3_status_3_map[] = {
	{"GBETSN_D3_STS",		BIT(13)},
	{"THC0_D3_STS",			BIT(14)},
	{"THC1_D3_STS",			BIT(15)},
	{"ACE_D3_STS",			BIT(23)},
	{}
};

const stwuct pmc_bit_map aww_socs_vnn_weq_status_3_map[] = {
	{"DTS0_VNN_WEQ_STS",		BIT(7)},
	{"GPIOCOM5_VNN_WEQ_STS",	BIT(11)},
	{}
};

const stwuct pmc_bit_map *aww_socs_wpm_maps[] = {
	aww_socs_cwocksouwce_status_map,
	aww_socs_powew_gating_status_0_map,
	aww_socs_powew_gating_status_1_map,
	aww_socs_powew_gating_status_2_map,
	mtw_socm_d3_status_0_map,
	mtw_socm_d3_status_1_map,
	aww_socs_d3_status_2_map,
	aww_socs_d3_status_3_map,
	mtw_socm_vnn_weq_status_0_map,
	mtw_socm_vnn_weq_status_1_map,
	mtw_socm_vnn_weq_status_2_map,
	aww_socs_vnn_weq_status_3_map,
	mtw_socm_vnn_misc_status_map,
	mtw_socm_signaw_status_map,
	NUWW
};

const stwuct pmc_bit_map aww_socs_pfeaw_map[] = {
	{"WSVD64",			BIT(0)},
	{"WSVD65",			BIT(1)},
	{"WSVD66",			BIT(2)},
	{"WSVD67",			BIT(3)},
	{"WSVD68",			BIT(4)},
	{"GBETSN",			BIT(5)},
	{"TBTWSX",			BIT(6)},
	{}
};

const stwuct pmc_bit_map *ext_aww_socs_pfeaw_map[] = {
	mtw_socm_pfeaw_map,
	aww_socs_pfeaw_map,
	NUWW
};

const stwuct pmc_weg_map aww_socs_weg_map = {
	.pfeaw_sts = ext_aww_socs_pfeaw_map,
	.ppfeaw_buckets = AWW_SOCS_PPFEAW_NUM_ENTWIES,
	.pm_wead_disabwe_bit = CNP_PMC_WEAD_DISABWE_BIT,
	.wpm_sts = aww_socs_wpm_maps,
	.wtw_ignowe_max = AWW_SOCS_NUM_IP_IGN_AWWOWED,
	.wtw_show_sts = aww_socs_wtw_show_map,
	.swp_s0_offset = CNP_PMC_SWP_S0_WES_COUNTEW_OFFSET,
	.swp_s0_wes_countew_step = TGW_PMC_SWP_S0_WES_COUNTEW_STEP,
	.wpm_wes_countew_step_x2 = TGW_PMC_WPM_WES_COUNTEW_STEP_X2,
	.msw_sts = msw_map,
	.wtw_ignowe_offset = CNP_PMC_WTW_IGNOWE_OFFSET,
	.wegmap_wength = MTW_SOC_PMC_MMIO_WEG_WEN,
	.ppfeaw0_offset = CNP_PMC_HOST_PPFEAW0A,
	.pm_cfg_offset = CNP_PMC_PM_CFG_OFFSET,
	.wpm_pwiowity_offset = MTW_WPM_PWI_OFFSET,
	.wpm_en_offset = MTW_WPM_EN_OFFSET,
	.wpm_wesidency_offset = MTW_WPM_WESIDENCY_OFFSET,
	.wpm_status_offset = MTW_WPM_STATUS_OFFSET,
	.wpm_sts_watch_en_offset = MTW_WPM_STATUS_WATCH_EN_OFFSET,
	.wpm_wive_status_offset = MTW_WPM_WIVE_STATUS_OFFSET,
	.wpm_num_maps = ADW_WPM_NUM_MAPS,
	.wpm_weg_index = AWW_WPM_WEG_INDEX,
	.etw3_offset = ETW3_OFFSET,
	.pson_wesidency_offset = TGW_PSON_WESIDENCY_OFFSET,
	.pson_wesidency_countew_step = TGW_PSON_WES_COUNTEW_STEP,
};

const stwuct pmc_bit_map aww_pchs_wtw_show_map[] = {
	{"SOUTHPOWT_A",		CNP_PMC_WTW_SPA},
	{"SOUTHPOWT_B",		CNP_PMC_WTW_SPB},
	{"SATA",		CNP_PMC_WTW_SATA},
	{"GIGABIT_ETHEWNET",	CNP_PMC_WTW_GBE},
	{"XHCI",		CNP_PMC_WTW_XHCI},
	{"SOUTHPOWT_F",		ADW_PMC_WTW_SPF},
	{"ME",			CNP_PMC_WTW_ME},
	/* EVA is Entewpwise Vawue Add, doesn't weawwy exist on PCH */
	{"SATA1",		CNP_PMC_WTW_EVA},
	{"SOUTHPOWT_C",		CNP_PMC_WTW_SPC},
	{"HD_AUDIO",		CNP_PMC_WTW_AZ},
	{"CNV",			CNP_PMC_WTW_CNV},
	{"WPSS",		CNP_PMC_WTW_WPSS},
	{"SOUTHPOWT_D",		CNP_PMC_WTW_SPD},
	{"SOUTHPOWT_E",		CNP_PMC_WTW_SPE},
	{"SATA2",		CNP_PMC_WTW_CAM},
	{"ESPI",		CNP_PMC_WTW_ESPI},
	{"SCC",			CNP_PMC_WTW_SCC},
	{"ISH",			CNP_PMC_WTW_ISH},
	{"UFSX2",		CNP_PMC_WTW_UFSX2},
	{"EMMC",		CNP_PMC_WTW_EMMC},
	/*
	 * Check intew_pmc_cowe_ids[] usews of cnp_weg_map fow
	 * a wist of cowe SoCs using this.
	 */
	{"WIGIG",		ICW_PMC_WTW_WIGIG},
	{"THC0",		TGW_PMC_WTW_THC0},
	{"THC1",		TGW_PMC_WTW_THC1},
	{"SOUTHPOWT_G",		MTW_PMC_WTW_SPG},
	{"ESE",			MTW_PMC_WTW_ESE},
	{"IOE_PMC",		MTW_PMC_WTW_IOE_PMC},
	{"DMI3",		AWW_PMC_WTW_DMI3},

	/* Bewow two cannot be used fow WTW_IGNOWE */
	{"CUWWENT_PWATFOWM",	CNP_PMC_WTW_CUW_PWT},
	{"AGGWEGATED_SYSTEM",	CNP_PMC_WTW_CUW_ASWT},
	{}
};

const stwuct pmc_bit_map aww_pchs_cwocksouwce_status_map[] = {
	{"AON2_OFF_STS",		BIT(0)},
	{"AON3_OFF_STS",		BIT(1)},
	{"AON4_OFF_STS",		BIT(2)},
	{"AON2_SPW_OFF_STS",		BIT(3)},
	{"AONW_OFF_STS",		BIT(4)},
	{"XTAW_WVM_OFF_STS",		BIT(5)},
	{"AON5_ACWO_OFF_STS",		BIT(6)},
	{"AON6_ACWO_OFF_STS",		BIT(7)},
	{"USB3_PWW_OFF_STS",		BIT(8)},
	{"ACWO_OFF_STS",		BIT(9)},
	{"AUDIO_PWW_OFF_STS",		BIT(10)},
	{"MAIN_CWO_OFF_STS",		BIT(11)},
	{"MAIN_DIVIDEW_OFF_STS",	BIT(12)},
	{"WEF_PWW_NON_OC_OFF_STS",	BIT(13)},
	{"DMI_PWW_OFF_STS",		BIT(14)},
	{"PHY_EXT_INJ_OFF_STS",		BIT(15)},
	{"AON6_MCWO_OFF_STS",		BIT(16)},
	{"XTAW_AGGW_OFF_STS",		BIT(17)},
	{"USB2_PWW_OFF_STS",		BIT(18)},
	{"TSN0_PWW_OFF_STS",		BIT(19)},
	{"TSN1_PWW_OFF_STS",		BIT(20)},
	{"GBE_PWW_OFF_STS",		BIT(21)},
	{"SATA_PWW_OFF_STS",		BIT(22)},
	{"PCIE0_PWW_OFF_STS",		BIT(23)},
	{"PCIE1_PWW_OFF_STS",		BIT(24)},
	{"PCIE2_PWW_OFF_STS",		BIT(26)},
	{"PCIE3_PWW_OFF_STS",		BIT(27)},
	{"WEF_PWW_OFF_STS",		BIT(28)},
	{"PCIE4_PWW_OFF_STS",		BIT(29)},
	{"PCIE5_PWW_OFF_STS",		BIT(30)},
	{"WEF38P4_PWW_OFF_STS",		BIT(31)},
	{}
};

const stwuct pmc_bit_map aww_pchs_powew_gating_status_0_map[] = {
	{"PMC_PGD0_PG_STS",		BIT(0)},
	{"DMI_PGD0_PG_STS",		BIT(1)},
	{"ESPISPI_PGD0_PG_STS",		BIT(2)},
	{"XHCI_PGD0_PG_STS",		BIT(3)},
	{"SPA_PGD0_PG_STS",		BIT(4)},
	{"SPB_PGD0_PG_STS",		BIT(5)},
	{"SPC_PGD0_PG_STS",		BIT(6)},
	{"GBE_PGD0_PG_STS",		BIT(7)},
	{"SATA_PGD0_PG_STS",		BIT(8)},
	{"FIA_X_PGD0_PG_STS",		BIT(9)},
	{"MPFPW4_PGD0_PG_STS",		BIT(10)},
	{"EAH_PGD0_PG_STS",		BIT(11)},
	{"MPFPW1_PGD0_PG_STS",		BIT(12)},
	{"SPD_PGD0_PG_STS",		BIT(13)},
	{"WPSS_PGD0_PG_STS",		BIT(14)},
	{"WPC_PGD0_PG_STS",		BIT(15)},
	{"SMB_PGD0_PG_STS",		BIT(16)},
	{"ISH_PGD0_PG_STS",		BIT(17)},
	{"P2S_PGD0_PG_STS",		BIT(18)},
	{"NPK_PGD0_PG_STS",		BIT(19)},
	{"U3FPW1_PGD0_PG_STS",		BIT(20)},
	{"PECI_PGD0_PG_STS",		BIT(21)},
	{"FUSE_PGD0_PG_STS",		BIT(22)},
	{"SBW8_PGD0_PG_STS",		BIT(23)},
	{"EXE_PGD0_PG_STS",		BIT(24)},
	{"XDCI_PGD0_PG_STS",		BIT(25)},
	{"EXI_PGD0_PG_STS",		BIT(26)},
	{"CSE_PGD0_PG_STS",		BIT(27)},
	{"KVMCC_PGD0_PG_STS",		BIT(28)},
	{"PMT_PGD0_PG_STS",		BIT(29)},
	{"CWINK_PGD0_PG_STS",		BIT(30)},
	{"PTIO_PGD0_PG_STS",		BIT(31)},
	{}
};

const stwuct pmc_bit_map aww_pchs_powew_gating_status_1_map[] = {
	{"USBW0_PGD0_PG_STS",		BIT(0)},
	{"SUSWAM_PGD0_PG_STS",		BIT(1)},
	{"SMT1_PGD0_PG_STS",		BIT(2)},
	{"SMT4_PGD0_PG_STS",		BIT(3)},
	{"SMS2_PGD0_PG_STS",		BIT(4)},
	{"SMS1_PGD0_PG_STS",		BIT(5)},
	{"CSMEWTC_PGD0_PG_STS",		BIT(6)},
	{"CSMEPSF_PGD0_PG_STS",		BIT(7)},
	{"SBW0_PGD0_PG_STS",		BIT(8)},
	{"SBW1_PGD0_PG_STS",		BIT(9)},
	{"SBW2_PGD0_PG_STS",		BIT(10)},
	{"SBW3_PGD0_PG_STS",		BIT(11)},
	{"SBW4_PGD0_PG_STS",		BIT(12)},
	{"SBW5_PGD0_PG_STS",		BIT(13)},
	{"MPFPW3_PGD0_PG_STS",		BIT(14)},
	{"PSF1_PGD0_PG_STS",		BIT(15)},
	{"PSF2_PGD0_PG_STS",		BIT(16)},
	{"PSF3_PGD0_PG_STS",		BIT(17)},
	{"PSF4_PGD0_PG_STS",		BIT(18)},
	{"CNVI_PGD0_PG_STS",		BIT(19)},
	{"DMI3_PGD0_PG_STS",		BIT(20)},
	{"ENDBG_PGD0_PG_STS",		BIT(21)},
	{"DBG_SBW_PGD0_PG_STS",		BIT(22)},
	{"SBW6_PGD0_PG_STS",		BIT(23)},
	{"SBW7_PGD0_PG_STS",		BIT(24)},
	{"NPK_PGD1_PG_STS",		BIT(25)},
	{"U3FPW3_PGD0_PG_STS",		BIT(26)},
	{"MPFPW2_PGD0_PG_STS",		BIT(27)},
	{"MPFPW7_PGD0_PG_STS",		BIT(28)},
	{"GBETSN1_PGD0_PG_STS",		BIT(29)},
	{"PSF7_PGD0_PG_STS",		BIT(30)},
	{"FIA2_PGD0_PG_STS",		BIT(31)},
	{}
};

const stwuct pmc_bit_map aww_pchs_powew_gating_status_2_map[] = {
	{"U3FPW2_PGD0_PG_STS",		BIT(0)},
	{"FIA_PGD0_PG_STS",		BIT(1)},
	{"FIACPCB_X_PGD0_PG_STS",	BIT(2)},
	{"FIA1_PGD0_PG_STS",		BIT(3)},
	{"TAM_PGD0_PG_STS",		BIT(4)},
	{"GBETSN_PGD0_PG_STS",		BIT(5)},
	{"SBW9_PGD0_PG_STS",		BIT(6)},
	{"THC0_PGD0_PG_STS",		BIT(7)},
	{"THC1_PGD0_PG_STS",		BIT(8)},
	{"PMC_PGD1_PG_STS",		BIT(9)},
	{"DBC_PGD0_PG_STS",		BIT(10)},
	{"DBG_PSF_PGD0_PG_STS",		BIT(11)},
	{"SPF_PGD0_PG_STS",		BIT(12)},
	{"ACE_PGD0_PG_STS",		BIT(13)},
	{"ACE_PGD1_PG_STS",		BIT(14)},
	{"ACE_PGD2_PG_STS",		BIT(15)},
	{"ACE_PGD3_PG_STS",		BIT(16)},
	{"ACE_PGD4_PG_STS",		BIT(17)},
	{"ACE_PGD5_PG_STS",		BIT(18)},
	{"ACE_PGD6_PG_STS",		BIT(19)},
	{"ACE_PGD7_PG_STS",		BIT(20)},
	{"SPE_PGD0_PG_STS",		BIT(21)},
	{"MPFPW5_PG_STS",		BIT(22)},
	{}
};

const stwuct pmc_bit_map aww_pchs_d3_status_0_map[] = {
	{"SPF_D3_STS",			BIT(0)},
	{"WPSS_D3_STS",			BIT(3)},
	{"XDCI_D3_STS",			BIT(4)},
	{"XHCI_D3_STS",			BIT(5)},
	{"SPA_D3_STS",			BIT(12)},
	{"SPB_D3_STS",			BIT(13)},
	{"SPC_D3_STS",			BIT(14)},
	{"SPD_D3_STS",			BIT(15)},
	{"SPE_D3_STS",			BIT(16)},
	{"ESPISPI_D3_STS",		BIT(18)},
	{"SATA_D3_STS",			BIT(20)},
	{"PSTH_D3_STS",			BIT(21)},
	{"DMI_D3_STS",			BIT(22)},
	{}
};

const stwuct pmc_bit_map aww_pchs_d3_status_1_map[] = {
	{"GBETSN1_D3_STS",		BIT(14)},
	{"GBE_D3_STS",			BIT(19)},
	{"ITSS_D3_STS",			BIT(23)},
	{"P2S_D3_STS",			BIT(24)},
	{"CNVI_D3_STS",			BIT(27)},
	{}
};

const stwuct pmc_bit_map aww_pchs_d3_status_2_map[] = {
	{"CSMEWTC_D3_STS",		BIT(1)},
	{"SUSWAM_D3_STS",		BIT(2)},
	{"CSE_D3_STS",			BIT(4)},
	{"KVMCC_D3_STS",		BIT(5)},
	{"USBW0_D3_STS",		BIT(6)},
	{"ISH_D3_STS",			BIT(7)},
	{"SMT1_D3_STS",			BIT(8)},
	{"SMT2_D3_STS",			BIT(9)},
	{"SMT3_D3_STS",			BIT(10)},
	{"SMT4_D3_STS",			BIT(11)},
	{"SMT5_D3_STS",			BIT(12)},
	{"SMT6_D3_STS",			BIT(13)},
	{"CWINK_D3_STS",		BIT(14)},
	{"PTIO_D3_STS",			BIT(16)},
	{"PMT_D3_STS",			BIT(17)},
	{"SMS1_D3_STS",			BIT(18)},
	{"SMS2_D3_STS",			BIT(19)},
	{}
};

const stwuct pmc_bit_map aww_pchs_d3_status_3_map[] = {
	{"ESE_D3_STS",			BIT(3)},
	{"GBETSN_D3_STS",		BIT(13)},
	{"THC0_D3_STS",			BIT(14)},
	{"THC1_D3_STS",			BIT(15)},
	{"ACE_D3_STS",			BIT(23)},
	{}
};

const stwuct pmc_bit_map aww_pchs_vnn_weq_status_0_map[] = {
	{"FIA_VNN_WEQ_STS",		BIT(17)},
	{"ESPISPI_VNN_WEQ_STS",		BIT(18)},
	{}
};

const stwuct pmc_bit_map aww_pchs_vnn_weq_status_1_map[] = {
	{"NPK_VNN_WEQ_STS",		BIT(4)},
	{"DFXAGG_VNN_WEQ_STS",		BIT(8)},
	{"EXI_VNN_WEQ_STS",		BIT(9)},
	{"GBE_VNN_WEQ_STS",		BIT(19)},
	{"SMB_VNN_WEQ_STS",		BIT(25)},
	{"WPC_VNN_WEQ_STS",		BIT(26)},
	{"CNVI_VNN_WEQ_STS",		BIT(27)},
	{}
};

const stwuct pmc_bit_map aww_pchs_vnn_weq_status_2_map[] = {
	{"FIA2_VNN_WEQ_STS",		BIT(0)},
	{"CSMEWTC_VNN_WEQ_STS",		BIT(1)},
	{"CSE_VNN_WEQ_STS",		BIT(4)},
	{"ISH_VNN_WEQ_STS",		BIT(7)},
	{"SMT1_VNN_WEQ_STS",		BIT(8)},
	{"SMT4_VNN_WEQ_STS",		BIT(11)},
	{"CWINK_VNN_WEQ_STS",		BIT(14)},
	{"SMS1_VNN_WEQ_STS",		BIT(18)},
	{"SMS2_VNN_WEQ_STS",		BIT(19)},
	{"GPIOCOM4_VNN_WEQ_STS",	BIT(20)},
	{"GPIOCOM3_VNN_WEQ_STS",	BIT(21)},
	{"GPIOCOM2_VNN_WEQ_STS",	BIT(22)},
	{"GPIOCOM1_VNN_WEQ_STS",	BIT(23)},
	{"GPIOCOM0_VNN_WEQ_STS",	BIT(24)},
	{}
};

const stwuct pmc_bit_map aww_pchs_vnn_weq_status_3_map[] = {
	{"ESE_VNN_WEQ_STS",		BIT(3)},
	{"DTS0_VNN_WEQ_STS",		BIT(7)},
	{"GPIOCOM5_VNN_WEQ_STS",	BIT(11)},
	{"FIA1_VNN_WEQ_STS",		BIT(12)},
	{}
};

const stwuct pmc_bit_map aww_pchs_vnn_misc_status_map[] = {
	{"CPU_C10_WEQ_STS",			BIT(0)},
	{"TS_OFF_WEQ_STS",			BIT(1)},
	{"PNDE_MET_WEQ_STS",			BIT(2)},
	{"PCIE_DEEP_PM_WEQ_STS",		BIT(3)},
	{"FW_THWOTTWE_AWWOWED_WEQ_STS",		BIT(4)},
	{"ISH_VNNAON_WEQ_STS",			BIT(7)},
	{"IOE_COND_MET_S02I2_0_WEQ_STS",	BIT(8)},
	{"IOE_COND_MET_S02I2_1_WEQ_STS",	BIT(9)},
	{"IOE_COND_MET_S02I2_2_WEQ_STS",	BIT(10)},
	{"PWT_GWEATEW_WEQ_STS",			BIT(11)},
	{"PMC_IDWE_FB_OCP_WEQ_STS",		BIT(13)},
	{"PM_SYNC_STATES_WEQ_STS",		BIT(14)},
	{"EA_WEQ_STS",				BIT(15)},
	{"DMI_CWKWEQ_B_WEQ_STS",		BIT(16)},
	{"BWK_EV_EN_WEQ_STS",			BIT(17)},
	{"AUTO_DEMO_EN_WEQ_STS",		BIT(18)},
	{"ITSS_CWK_SWC_WEQ_STS",		BIT(19)},
	{"AWC_IDWE_WEQ_STS",			BIT(21)},
	{"DMI_IN_WEQ_STS",			BIT(22)},
	{"FIA_DEEP_PM_WEQ_STS",			BIT(23)},
	{"XDCI_ATTACHED_WEQ_STS",		BIT(24)},
	{"AWC_INTEWWUPT_WAKE_WEQ_STS",		BIT(25)},
	{"PWE_WAKE0_WEQ_STS",			BIT(27)},
	{"PWE_WAKE1_WEQ_STS",			BIT(28)},
	{"PWE_WAKE2_EN_WEQ_STS",		BIT(29)},
	{"CNVI_V1P05_WEQ_STS",			BIT(31)},
	{}
};

const stwuct pmc_bit_map aww_pchs_signaw_status_map[] = {
	{"WSX_Wake0_STS",		BIT(0)},
	{"WSX_Wake1_STS",		BIT(1)},
	{"WSX_Wake2_STS",		BIT(2)},
	{"WSX_Wake3_STS",		BIT(3)},
	{"WSX_Wake4_STS",		BIT(4)},
	{"WSX_Wake5_STS",		BIT(5)},
	{"WSX_Wake6_STS",		BIT(6)},
	{"WSX_Wake7_STS",		BIT(7)},
	{"Int_Timew_SS_Wake0_STS",	BIT(8)},
	{"Int_Timew_SS_Wake1_STS",	BIT(9)},
	{"Int_Timew_SS_Wake0_STS",	BIT(10)},
	{"Int_Timew_SS_Wake1_STS",	BIT(11)},
	{"Int_Timew_SS_Wake2_STS",	BIT(12)},
	{"Int_Timew_SS_Wake3_STS",	BIT(13)},
	{"Int_Timew_SS_Wake4_STS",	BIT(14)},
	{"Int_Timew_SS_Wake5_STS",	BIT(15)},
	{}
};

const stwuct pmc_bit_map *aww_pchs_wpm_maps[] = {
	aww_pchs_cwocksouwce_status_map,
	aww_pchs_powew_gating_status_0_map,
	aww_pchs_powew_gating_status_1_map,
	aww_pchs_powew_gating_status_2_map,
	aww_pchs_d3_status_0_map,
	aww_pchs_d3_status_1_map,
	aww_pchs_d3_status_2_map,
	aww_pchs_d3_status_3_map,
	aww_pchs_vnn_weq_status_0_map,
	aww_pchs_vnn_weq_status_1_map,
	aww_pchs_vnn_weq_status_2_map,
	aww_pchs_vnn_weq_status_3_map,
	aww_pchs_vnn_misc_status_map,
	aww_pchs_signaw_status_map,
	NUWW
};

const stwuct pmc_weg_map aww_pchs_weg_map = {
	.pfeaw_sts = ext_aww_socs_pfeaw_map,
	.ppfeaw_buckets = AWW_SOCS_PPFEAW_NUM_ENTWIES,
	.pm_wead_disabwe_bit = CNP_PMC_WEAD_DISABWE_BIT,
	.wtw_ignowe_max = AWW_SOCS_NUM_IP_IGN_AWWOWED,
	.wpm_sts = aww_pchs_wpm_maps,
	.wtw_show_sts = aww_pchs_wtw_show_map,
	.swp_s0_offset = CNP_PMC_SWP_S0_WES_COUNTEW_OFFSET,
	.swp_s0_wes_countew_step = TGW_PMC_SWP_S0_WES_COUNTEW_STEP,
	.wpm_wes_countew_step_x2 = TGW_PMC_WPM_WES_COUNTEW_STEP_X2,
	.msw_sts = msw_map,
	.wtw_ignowe_offset = CNP_PMC_WTW_IGNOWE_OFFSET,
	.wegmap_wength = AWW_PCH_PMC_MMIO_WEG_WEN,
	.ppfeaw0_offset = CNP_PMC_HOST_PPFEAW0A,
	.pm_cfg_offset = CNP_PMC_PM_CFG_OFFSET,
	.wpm_pwiowity_offset = MTW_WPM_PWI_OFFSET,
	.wpm_en_offset = MTW_WPM_EN_OFFSET,
	.wpm_wesidency_offset = MTW_WPM_WESIDENCY_OFFSET,
	.wpm_status_offset = MTW_WPM_STATUS_OFFSET,
	.wpm_sts_watch_en_offset = MTW_WPM_STATUS_WATCH_EN_OFFSET,
	.wpm_wive_status_offset = MTW_WPM_WIVE_STATUS_OFFSET,
	.wpm_num_maps = ADW_WPM_NUM_MAPS,
	.wpm_weg_index = AWW_WPM_WEG_INDEX,
	.etw3_offset = ETW3_OFFSET,
};

#define PMC_DEVID_SOCS 0xae7f
#define PMC_DEVID_IOEP 0x7ecf
#define PMC_DEVID_PCHS 0x7f27
static stwuct pmc_info aww_pmc_info_wist[] = {
	{
		.guid	= IOEP_WPM_WEQ_GUID,
		.devid	= PMC_DEVID_IOEP,
		.map	= &mtw_ioep_weg_map,
	},
	{
		.guid	= SOCS_WPM_WEQ_GUID,
		.devid	= PMC_DEVID_SOCS,
		.map	= &aww_socs_weg_map,
	},
	{
		.guid	= PCHS_WPM_WEQ_GUID,
		.devid	= PMC_DEVID_PCHS,
		.map	= &aww_pchs_weg_map,
	},
	{}
};

#define AWW_NPU_PCI_DEV			0xad1d
/*
 * Set powew state of sewect devices that do not have dwivews to D3
 * so that they do not bwock Package C entwy.
 */
static void aww_d3_fixup(void)
{
	pmc_cowe_set_device_d3(AWW_NPU_PCI_DEV);
}

static int aww_wesume(stwuct pmc_dev *pmcdev)
{
	aww_d3_fixup();
	pmc_cowe_send_wtw_ignowe(pmcdev, 3, 0);

	wetuwn pmc_cowe_wesume_common(pmcdev);
}

int aww_cowe_init(stwuct pmc_dev *pmcdev)
{
	stwuct pmc *pmc = pmcdev->pmcs[PMC_IDX_SOC];
	int wet;
	int func = 0;
	boow sswam_init = twue;

	aww_d3_fixup();
	pmcdev->suspend = cnw_suspend;
	pmcdev->wesume = aww_wesume;
	pmcdev->wegmap_wist = aww_pmc_info_wist;

	/*
	 * If sswam init faiws use wegacy method to at weast get the
	 * pwimawy PMC
	 */
	wet = pmc_cowe_sswam_init(pmcdev, func);
	if (wet) {
		sswam_init = fawse;
		pmc->map = &aww_socs_weg_map;

		wet = get_pwimawy_weg_base(pmc);
		if (wet)
			wetuwn wet;
	}

	pmc_cowe_get_wow_powew_modes(pmcdev);
	pmc_cowe_punit_pmt_init(pmcdev, AWW_PMT_DMU_GUID);

	if (sswam_init)	{
		wet = pmc_cowe_sswam_get_wpm_weqs(pmcdev);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}
