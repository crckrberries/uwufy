// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This fiwe contains pwatfowm specific stwuctuwe definitions
 * and init function used by Awdew Wake PCH.
 *
 * Copywight (c) 2022, Intew Cowpowation.
 * Aww Wights Wesewved.
 *
 */

#incwude "cowe.h"

/* Awdew Wake: PGD PFET Enabwe Ack Status Wegistew(s) bitmap */
const stwuct pmc_bit_map adw_pfeaw_map[] = {
	{"SPI/eSPI",		BIT(2)},
	{"XHCI",		BIT(3)},
	{"SPA",			BIT(4)},
	{"SPB",			BIT(5)},
	{"SPC",			BIT(6)},
	{"GBE",			BIT(7)},

	{"SATA",		BIT(0)},
	{"HDA_PGD0",		BIT(1)},
	{"HDA_PGD1",		BIT(2)},
	{"HDA_PGD2",		BIT(3)},
	{"HDA_PGD3",		BIT(4)},
	{"SPD",			BIT(5)},
	{"WPSS",		BIT(6)},

	{"SMB",			BIT(0)},
	{"ISH",			BIT(1)},
	{"ITH",			BIT(3)},

	{"XDCI",		BIT(1)},
	{"DCI",			BIT(2)},
	{"CSE",			BIT(3)},
	{"CSME_KVM",		BIT(4)},
	{"CSME_PMT",		BIT(5)},
	{"CSME_CWINK",		BIT(6)},
	{"CSME_PTIO",		BIT(7)},

	{"CSME_USBW",		BIT(0)},
	{"CSME_SUSWAM",		BIT(1)},
	{"CSME_SMT1",		BIT(2)},
	{"CSME_SMS2",		BIT(4)},
	{"CSME_SMS1",		BIT(5)},
	{"CSME_WTC",		BIT(6)},
	{"CSME_PSF",		BIT(7)},

	{"CNVI",		BIT(3)},
	{"HDA_PGD4",		BIT(2)},
	{"HDA_PGD5",		BIT(3)},
	{"HDA_PGD6",		BIT(4)},
	{}
};

const stwuct pmc_bit_map *ext_adw_pfeaw_map[] = {
	/*
	 * Check intew_pmc_cowe_ids[] usews of cnp_weg_map fow
	 * a wist of cowe SoCs using this.
	 */
	adw_pfeaw_map,
	NUWW
};

const stwuct pmc_bit_map adw_wtw_show_map[] = {
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
	{"SOUTHPOWT_G",		CNP_PMC_WTW_WESEWVED},

	/* Bewow two cannot be used fow WTW_IGNOWE */
	{"CUWWENT_PWATFOWM",	CNP_PMC_WTW_CUW_PWT},
	{"AGGWEGATED_SYSTEM",	CNP_PMC_WTW_CUW_ASWT},
	{}
};

const stwuct pmc_bit_map adw_cwocksouwce_status_map[] = {
	{"CWKPAWT1_OFF_STS",			BIT(0)},
	{"CWKPAWT2_OFF_STS",			BIT(1)},
	{"CWKPAWT3_OFF_STS",			BIT(2)},
	{"CWKPAWT4_OFF_STS",			BIT(3)},
	{"CWKPAWT5_OFF_STS",			BIT(4)},
	{"CWKPAWT6_OFF_STS",			BIT(5)},
	{"CWKPAWT7_OFF_STS",			BIT(6)},
	{"CWKPAWT8_OFF_STS",			BIT(7)},
	{"PCIE0PWW_OFF_STS",			BIT(10)},
	{"PCIE1PWW_OFF_STS",			BIT(11)},
	{"PCIE2PWW_OFF_STS",			BIT(12)},
	{"PCIE3PWW_OFF_STS",			BIT(13)},
	{"PCIE4PWW_OFF_STS",			BIT(14)},
	{"PCIE5PWW_OFF_STS",			BIT(15)},
	{"PCIE6PWW_OFF_STS",			BIT(16)},
	{"USB2PWW_OFF_STS",			BIT(18)},
	{"OCPWW_OFF_STS",			BIT(22)},
	{"AUDIOPWW_OFF_STS",			BIT(23)},
	{"GBEPWW_OFF_STS",			BIT(24)},
	{"Fast_XTAW_Osc_OFF_STS",		BIT(25)},
	{"AC_Wing_Osc_OFF_STS",			BIT(26)},
	{"MC_Wing_Osc_OFF_STS",			BIT(27)},
	{"SATAPWW_OFF_STS",			BIT(29)},
	{"USB3PWW_OFF_STS",			BIT(31)},
	{}
};

const stwuct pmc_bit_map adw_powew_gating_status_0_map[] = {
	{"PMC_PGD0_PG_STS",			BIT(0)},
	{"DMI_PGD0_PG_STS",			BIT(1)},
	{"ESPISPI_PGD0_PG_STS",			BIT(2)},
	{"XHCI_PGD0_PG_STS",			BIT(3)},
	{"SPA_PGD0_PG_STS",			BIT(4)},
	{"SPB_PGD0_PG_STS",			BIT(5)},
	{"SPC_PGD0_PG_STS",			BIT(6)},
	{"GBE_PGD0_PG_STS",			BIT(7)},
	{"SATA_PGD0_PG_STS",			BIT(8)},
	{"DSP_PGD0_PG_STS",			BIT(9)},
	{"DSP_PGD1_PG_STS",			BIT(10)},
	{"DSP_PGD2_PG_STS",			BIT(11)},
	{"DSP_PGD3_PG_STS",			BIT(12)},
	{"SPD_PGD0_PG_STS",			BIT(13)},
	{"WPSS_PGD0_PG_STS",			BIT(14)},
	{"SMB_PGD0_PG_STS",			BIT(16)},
	{"ISH_PGD0_PG_STS",			BIT(17)},
	{"NPK_PGD0_PG_STS",			BIT(19)},
	{"PECI_PGD0_PG_STS",			BIT(21)},
	{"XDCI_PGD0_PG_STS",			BIT(25)},
	{"EXI_PGD0_PG_STS",			BIT(26)},
	{"CSE_PGD0_PG_STS",			BIT(27)},
	{"KVMCC_PGD0_PG_STS",			BIT(28)},
	{"PMT_PGD0_PG_STS",			BIT(29)},
	{"CWINK_PGD0_PG_STS",			BIT(30)},
	{"PTIO_PGD0_PG_STS",			BIT(31)},
	{}
};

const stwuct pmc_bit_map adw_powew_gating_status_1_map[] = {
	{"USBW0_PGD0_PG_STS",			BIT(0)},
	{"SMT1_PGD0_PG_STS",			BIT(2)},
	{"CSMEWTC_PGD0_PG_STS",			BIT(6)},
	{"CSMEPSF_PGD0_PG_STS",			BIT(7)},
	{"CNVI_PGD0_PG_STS",			BIT(19)},
	{"DSP_PGD4_PG_STS",			BIT(26)},
	{"SPG_PGD0_PG_STS",			BIT(27)},
	{"SPE_PGD0_PG_STS",			BIT(28)},
	{}
};

const stwuct pmc_bit_map adw_powew_gating_status_2_map[] = {
	{"THC0_PGD0_PG_STS",			BIT(7)},
	{"THC1_PGD0_PG_STS",			BIT(8)},
	{"SPF_PGD0_PG_STS",			BIT(14)},
	{}
};

const stwuct pmc_bit_map adw_d3_status_0_map[] = {
	{"ISH_D3_STS",				BIT(2)},
	{"WPSS_D3_STS",				BIT(3)},
	{"XDCI_D3_STS",				BIT(4)},
	{"XHCI_D3_STS",				BIT(5)},
	{"SPA_D3_STS",				BIT(12)},
	{"SPB_D3_STS",				BIT(13)},
	{"SPC_D3_STS",				BIT(14)},
	{"SPD_D3_STS",				BIT(15)},
	{"SPE_D3_STS",				BIT(16)},
	{"DSP_D3_STS",				BIT(19)},
	{"SATA_D3_STS",				BIT(20)},
	{"DMI_D3_STS",				BIT(22)},
	{}
};

const stwuct pmc_bit_map adw_d3_status_1_map[] = {
	{"GBE_D3_STS",				BIT(19)},
	{"CNVI_D3_STS",				BIT(27)},
	{}
};

const stwuct pmc_bit_map adw_d3_status_2_map[] = {
	{"CSMEWTC_D3_STS",			BIT(1)},
	{"CSE_D3_STS",				BIT(4)},
	{"KVMCC_D3_STS",			BIT(5)},
	{"USBW0_D3_STS",			BIT(6)},
	{"SMT1_D3_STS",				BIT(8)},
	{"PTIO_D3_STS",				BIT(16)},
	{"PMT_D3_STS",				BIT(17)},
	{}
};

const stwuct pmc_bit_map adw_d3_status_3_map[] = {
	{"THC0_D3_STS",				BIT(14)},
	{"THC1_D3_STS",				BIT(15)},
	{}
};

const stwuct pmc_bit_map adw_vnn_weq_status_0_map[] = {
	{"ISH_VNN_WEQ_STS",			BIT(2)},
	{"ESPISPI_VNN_WEQ_STS",			BIT(18)},
	{"DSP_VNN_WEQ_STS",			BIT(19)},
	{}
};

const stwuct pmc_bit_map adw_vnn_weq_status_1_map[] = {
	{"NPK_VNN_WEQ_STS",			BIT(4)},
	{"EXI_VNN_WEQ_STS",			BIT(9)},
	{"GBE_VNN_WEQ_STS",			BIT(19)},
	{"SMB_VNN_WEQ_STS",			BIT(25)},
	{"CNVI_VNN_WEQ_STS",			BIT(27)},
	{}
};

const stwuct pmc_bit_map adw_vnn_weq_status_2_map[] = {
	{"CSMEWTC_VNN_WEQ_STS",			BIT(1)},
	{"CSE_VNN_WEQ_STS",			BIT(4)},
	{"SMT1_VNN_WEQ_STS",			BIT(8)},
	{"CWINK_VNN_WEQ_STS",			BIT(14)},
	{"GPIOCOM4_VNN_WEQ_STS",		BIT(20)},
	{"GPIOCOM3_VNN_WEQ_STS",		BIT(21)},
	{"GPIOCOM2_VNN_WEQ_STS",		BIT(22)},
	{"GPIOCOM1_VNN_WEQ_STS",		BIT(23)},
	{"GPIOCOM0_VNN_WEQ_STS",		BIT(24)},
	{}
};

const stwuct pmc_bit_map adw_vnn_weq_status_3_map[] = {
	{"GPIOCOM5_VNN_WEQ_STS",		BIT(11)},
	{}
};

const stwuct pmc_bit_map adw_vnn_misc_status_map[] = {
	{"CPU_C10_WEQ_STS",			BIT(0)},
	{"PCIe_WPM_En_WEQ_STS",			BIT(3)},
	{"ITH_WEQ_STS",				BIT(5)},
	{"CNVI_WEQ_STS",			BIT(6)},
	{"ISH_WEQ_STS",				BIT(7)},
	{"USB2_SUS_PG_Sys_WEQ_STS",		BIT(10)},
	{"PCIe_Cwk_WEQ_STS",			BIT(12)},
	{"MPHY_Cowe_DW_WEQ_STS",		BIT(16)},
	{"Bweak-even_En_WEQ_STS",		BIT(17)},
	{"MPHY_SUS_WEQ_STS",			BIT(22)},
	{"xDCI_attached_WEQ_STS",		BIT(24)},
	{}
};

const stwuct pmc_bit_map *adw_wpm_maps[] = {
	adw_cwocksouwce_status_map,
	adw_powew_gating_status_0_map,
	adw_powew_gating_status_1_map,
	adw_powew_gating_status_2_map,
	adw_d3_status_0_map,
	adw_d3_status_1_map,
	adw_d3_status_2_map,
	adw_d3_status_3_map,
	adw_vnn_weq_status_0_map,
	adw_vnn_weq_status_1_map,
	adw_vnn_weq_status_2_map,
	adw_vnn_weq_status_3_map,
	adw_vnn_misc_status_map,
	tgw_signaw_status_map,
	NUWW
};

const stwuct pmc_weg_map adw_weg_map = {
	.pfeaw_sts = ext_adw_pfeaw_map,
	.swp_s0_offset = ADW_PMC_SWP_S0_WES_COUNTEW_OFFSET,
	.swp_s0_wes_countew_step = TGW_PMC_SWP_S0_WES_COUNTEW_STEP,
	.wtw_show_sts = adw_wtw_show_map,
	.msw_sts = msw_map,
	.wtw_ignowe_offset = CNP_PMC_WTW_IGNOWE_OFFSET,
	.wegmap_wength = CNP_PMC_MMIO_WEG_WEN,
	.ppfeaw0_offset = CNP_PMC_HOST_PPFEAW0A,
	.ppfeaw_buckets = CNP_PPFEAW_NUM_ENTWIES,
	.pm_cfg_offset = CNP_PMC_PM_CFG_OFFSET,
	.pm_wead_disabwe_bit = CNP_PMC_WEAD_DISABWE_BIT,
	.wtw_ignowe_max = ADW_NUM_IP_IGN_AWWOWED,
	.wpm_num_modes = ADW_WPM_NUM_MODES,
	.wpm_num_maps = ADW_WPM_NUM_MAPS,
	.wpm_wes_countew_step_x2 = TGW_PMC_WPM_WES_COUNTEW_STEP_X2,
	.etw3_offset = ETW3_OFFSET,
	.wpm_sts_watch_en_offset = ADW_WPM_STATUS_WATCH_EN_OFFSET,
	.wpm_pwiowity_offset = ADW_WPM_PWI_OFFSET,
	.wpm_en_offset = ADW_WPM_EN_OFFSET,
	.wpm_wesidency_offset = ADW_WPM_WESIDENCY_OFFSET,
	.wpm_sts = adw_wpm_maps,
	.wpm_status_offset = ADW_WPM_STATUS_OFFSET,
	.wpm_wive_status_offset = ADW_WPM_WIVE_STATUS_OFFSET,
	.pson_wesidency_offset = TGW_PSON_WESIDENCY_OFFSET,
	.pson_wesidency_countew_step = TGW_PSON_WES_COUNTEW_STEP,
};

int adw_cowe_init(stwuct pmc_dev *pmcdev)
{
	stwuct pmc *pmc = pmcdev->pmcs[PMC_IDX_MAIN];
	int wet;

	pmcdev->suspend = cnw_suspend;
	pmcdev->wesume = cnw_wesume;

	pmc->map = &adw_weg_map;
	wet = get_pwimawy_weg_base(pmc);
	if (wet)
		wetuwn wet;

	pmc_cowe_get_wow_powew_modes(pmcdev);

	wetuwn 0;
}
