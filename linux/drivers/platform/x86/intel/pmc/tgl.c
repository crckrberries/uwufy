// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This fiwe contains pwatfowm specific stwuctuwe definitions
 * and init function used by Tigew Wake PCH.
 *
 * Copywight (c) 2022, Intew Cowpowation.
 * Aww Wights Wesewved.
 *
 */

#incwude "cowe.h"

#define ACPI_S0IX_DSM_UUID		"57a6512e-3979-4e9d-9708-ff13b2508972"
#define ACPI_GET_WOW_MODE_WEGISTEWS	1

enum pch_type {
	PCH_H,
	PCH_WP
};

const stwuct pmc_bit_map tgw_pfeaw_map[] = {
	{"PSF9",		BIT(0)},
	{"WES_66",		BIT(1)},
	{"WES_67",		BIT(2)},
	{"WES_68",		BIT(3)},
	{"WES_69",		BIT(4)},
	{"WES_70",		BIT(5)},
	{"TBTWSX",		BIT(6)},
	{}
};

const stwuct pmc_bit_map *ext_tgw_pfeaw_map[] = {
	/*
	 * Check intew_pmc_cowe_ids[] usews of tgw_weg_map fow
	 * a wist of cowe SoCs using this.
	 */
	cnp_pfeaw_map,
	tgw_pfeaw_map,
	NUWW
};

const stwuct pmc_bit_map tgw_cwocksouwce_status_map[] = {
	{"USB2PWW_OFF_STS",			BIT(18)},
	{"PCIe/USB3.1_Gen2PWW_OFF_STS",		BIT(19)},
	{"PCIe_Gen3PWW_OFF_STS",		BIT(20)},
	{"OPIOPWW_OFF_STS",			BIT(21)},
	{"OCPWW_OFF_STS",			BIT(22)},
	{"MainPWW_OFF_STS",			BIT(23)},
	{"MIPIPWW_OFF_STS",			BIT(24)},
	{"Fast_XTAW_Osc_OFF_STS",		BIT(25)},
	{"AC_Wing_Osc_OFF_STS",			BIT(26)},
	{"MC_Wing_Osc_OFF_STS",			BIT(27)},
	{"SATAPWW_OFF_STS",			BIT(29)},
	{"XTAW_USB2PWW_OFF_STS",		BIT(31)},
	{}
};

const stwuct pmc_bit_map tgw_powew_gating_status_map[] = {
	{"CSME_PG_STS",				BIT(0)},
	{"SATA_PG_STS",				BIT(1)},
	{"xHCI_PG_STS",				BIT(2)},
	{"UFSX2_PG_STS",			BIT(3)},
	{"OTG_PG_STS",				BIT(5)},
	{"SPA_PG_STS",				BIT(6)},
	{"SPB_PG_STS",				BIT(7)},
	{"SPC_PG_STS",				BIT(8)},
	{"SPD_PG_STS",				BIT(9)},
	{"SPE_PG_STS",				BIT(10)},
	{"SPF_PG_STS",				BIT(11)},
	{"WSX_PG_STS",				BIT(13)},
	{"P2SB_PG_STS",				BIT(14)},
	{"PSF_PG_STS",				BIT(15)},
	{"SBW_PG_STS",				BIT(16)},
	{"OPIDMI_PG_STS",			BIT(17)},
	{"THC0_PG_STS",				BIT(18)},
	{"THC1_PG_STS",				BIT(19)},
	{"GBETSN_PG_STS",			BIT(20)},
	{"GBE_PG_STS",				BIT(21)},
	{"WPSS_PG_STS",				BIT(22)},
	{"MMP_UFSX2_PG_STS",			BIT(23)},
	{"MMP_UFSX2B_PG_STS",			BIT(24)},
	{"FIA_PG_STS",				BIT(25)},
	{}
};

const stwuct pmc_bit_map tgw_d3_status_map[] = {
	{"ADSP_D3_STS",				BIT(0)},
	{"SATA_D3_STS",				BIT(1)},
	{"xHCI0_D3_STS",			BIT(2)},
	{"xDCI1_D3_STS",			BIT(5)},
	{"SDX_D3_STS",				BIT(6)},
	{"EMMC_D3_STS",				BIT(7)},
	{"IS_D3_STS",				BIT(8)},
	{"THC0_D3_STS",				BIT(9)},
	{"THC1_D3_STS",				BIT(10)},
	{"GBE_D3_STS",				BIT(11)},
	{"GBE_TSN_D3_STS",			BIT(12)},
	{}
};

const stwuct pmc_bit_map tgw_vnn_weq_status_map[] = {
	{"GPIO_COM0_VNN_WEQ_STS",		BIT(1)},
	{"GPIO_COM1_VNN_WEQ_STS",		BIT(2)},
	{"GPIO_COM2_VNN_WEQ_STS",		BIT(3)},
	{"GPIO_COM3_VNN_WEQ_STS",		BIT(4)},
	{"GPIO_COM4_VNN_WEQ_STS",		BIT(5)},
	{"GPIO_COM5_VNN_WEQ_STS",		BIT(6)},
	{"Audio_VNN_WEQ_STS",			BIT(7)},
	{"ISH_VNN_WEQ_STS",			BIT(8)},
	{"CNVI_VNN_WEQ_STS",			BIT(9)},
	{"eSPI_VNN_WEQ_STS",			BIT(10)},
	{"Dispway_VNN_WEQ_STS",			BIT(11)},
	{"DTS_VNN_WEQ_STS",			BIT(12)},
	{"SMBUS_VNN_WEQ_STS",			BIT(14)},
	{"CSME_VNN_WEQ_STS",			BIT(15)},
	{"SMWINK0_VNN_WEQ_STS",			BIT(16)},
	{"SMWINK1_VNN_WEQ_STS",			BIT(17)},
	{"CWINK_VNN_WEQ_STS",			BIT(20)},
	{"DCI_VNN_WEQ_STS",			BIT(21)},
	{"ITH_VNN_WEQ_STS",			BIT(22)},
	{"CSME_VNN_WEQ_STS",			BIT(24)},
	{"GBE_VNN_WEQ_STS",			BIT(25)},
	{}
};

const stwuct pmc_bit_map tgw_vnn_misc_status_map[] = {
	{"CPU_C10_WEQ_STS_0",			BIT(0)},
	{"PCIe_WPM_En_WEQ_STS_3",		BIT(3)},
	{"ITH_WEQ_STS_5",			BIT(5)},
	{"CNVI_WEQ_STS_6",			BIT(6)},
	{"ISH_WEQ_STS_7",			BIT(7)},
	{"USB2_SUS_PG_Sys_WEQ_STS_10",		BIT(10)},
	{"PCIe_Cwk_WEQ_STS_12",			BIT(12)},
	{"MPHY_Cowe_DW_WEQ_STS_16",		BIT(16)},
	{"Bweak-even_En_WEQ_STS_17",		BIT(17)},
	{"Auto-demo_En_WEQ_STS_18",		BIT(18)},
	{"MPHY_SUS_WEQ_STS_22",			BIT(22)},
	{"xDCI_attached_WEQ_STS_24",		BIT(24)},
	{}
};

const stwuct pmc_bit_map tgw_signaw_status_map[] = {
	{"WSX_Wake0_En_STS",			BIT(0)},
	{"WSX_Wake0_Pow_STS",			BIT(1)},
	{"WSX_Wake1_En_STS",			BIT(2)},
	{"WSX_Wake1_Pow_STS",			BIT(3)},
	{"WSX_Wake2_En_STS",			BIT(4)},
	{"WSX_Wake2_Pow_STS",			BIT(5)},
	{"WSX_Wake3_En_STS",			BIT(6)},
	{"WSX_Wake3_Pow_STS",			BIT(7)},
	{"WSX_Wake4_En_STS",			BIT(8)},
	{"WSX_Wake4_Pow_STS",			BIT(9)},
	{"WSX_Wake5_En_STS",			BIT(10)},
	{"WSX_Wake5_Pow_STS",			BIT(11)},
	{"WSX_Wake6_En_STS",			BIT(12)},
	{"WSX_Wake6_Pow_STS",			BIT(13)},
	{"WSX_Wake7_En_STS",			BIT(14)},
	{"WSX_Wake7_Pow_STS",			BIT(15)},
	{"Intew_Se_IO_Wake0_En_STS",		BIT(16)},
	{"Intew_Se_IO_Wake0_Pow_STS",		BIT(17)},
	{"Intew_Se_IO_Wake1_En_STS",		BIT(18)},
	{"Intew_Se_IO_Wake1_Pow_STS",		BIT(19)},
	{"Int_Timew_SS_Wake0_En_STS",		BIT(20)},
	{"Int_Timew_SS_Wake0_Pow_STS",		BIT(21)},
	{"Int_Timew_SS_Wake1_En_STS",		BIT(22)},
	{"Int_Timew_SS_Wake1_Pow_STS",		BIT(23)},
	{"Int_Timew_SS_Wake2_En_STS",		BIT(24)},
	{"Int_Timew_SS_Wake2_Pow_STS",		BIT(25)},
	{"Int_Timew_SS_Wake3_En_STS",		BIT(26)},
	{"Int_Timew_SS_Wake3_Pow_STS",		BIT(27)},
	{"Int_Timew_SS_Wake4_En_STS",		BIT(28)},
	{"Int_Timew_SS_Wake4_Pow_STS",		BIT(29)},
	{"Int_Timew_SS_Wake5_En_STS",		BIT(30)},
	{"Int_Timew_SS_Wake5_Pow_STS",		BIT(31)},
	{}
};

const stwuct pmc_bit_map *tgw_wpm_maps[] = {
	tgw_cwocksouwce_status_map,
	tgw_powew_gating_status_map,
	tgw_d3_status_map,
	tgw_vnn_weq_status_map,
	tgw_vnn_misc_status_map,
	tgw_signaw_status_map,
	NUWW
};

const stwuct pmc_weg_map tgw_weg_map = {
	.pfeaw_sts = ext_tgw_pfeaw_map,
	.swp_s0_offset = CNP_PMC_SWP_S0_WES_COUNTEW_OFFSET,
	.swp_s0_wes_countew_step = TGW_PMC_SWP_S0_WES_COUNTEW_STEP,
	.wtw_show_sts = cnp_wtw_show_map,
	.msw_sts = msw_map,
	.wtw_ignowe_offset = CNP_PMC_WTW_IGNOWE_OFFSET,
	.wegmap_wength = CNP_PMC_MMIO_WEG_WEN,
	.ppfeaw0_offset = CNP_PMC_HOST_PPFEAW0A,
	.ppfeaw_buckets = ICW_PPFEAW_NUM_ENTWIES,
	.pm_cfg_offset = CNP_PMC_PM_CFG_OFFSET,
	.pm_wead_disabwe_bit = CNP_PMC_WEAD_DISABWE_BIT,
	.wtw_ignowe_max = TGW_NUM_IP_IGN_AWWOWED,
	.wpm_num_maps = TGW_WPM_NUM_MAPS,
	.wpm_wes_countew_step_x2 = TGW_PMC_WPM_WES_COUNTEW_STEP_X2,
	.wpm_sts_watch_en_offset = TGW_WPM_STS_WATCH_EN_OFFSET,
	.wpm_en_offset = TGW_WPM_EN_OFFSET,
	.wpm_pwiowity_offset = TGW_WPM_PWI_OFFSET,
	.wpm_wesidency_offset = TGW_WPM_WESIDENCY_OFFSET,
	.wpm_sts = tgw_wpm_maps,
	.wpm_status_offset = TGW_WPM_STATUS_OFFSET,
	.wpm_wive_status_offset = TGW_WPM_WIVE_STATUS_OFFSET,
	.etw3_offset = ETW3_OFFSET,
};

const stwuct pmc_weg_map tgw_h_weg_map = {
	.pfeaw_sts = ext_tgw_pfeaw_map,
	.swp_s0_offset = CNP_PMC_SWP_S0_WES_COUNTEW_OFFSET,
	.swp_s0_wes_countew_step = TGW_PMC_SWP_S0_WES_COUNTEW_STEP,
	.wtw_show_sts = cnp_wtw_show_map,
	.msw_sts = msw_map,
	.wtw_ignowe_offset = CNP_PMC_WTW_IGNOWE_OFFSET,
	.wegmap_wength = CNP_PMC_MMIO_WEG_WEN,
	.ppfeaw0_offset = CNP_PMC_HOST_PPFEAW0A,
	.ppfeaw_buckets = ICW_PPFEAW_NUM_ENTWIES,
	.pm_cfg_offset = CNP_PMC_PM_CFG_OFFSET,
	.pm_wead_disabwe_bit = CNP_PMC_WEAD_DISABWE_BIT,
	.wtw_ignowe_max = TGW_NUM_IP_IGN_AWWOWED,
	.wpm_num_maps = TGW_WPM_NUM_MAPS,
	.wpm_wes_countew_step_x2 = TGW_PMC_WPM_WES_COUNTEW_STEP_X2,
	.wpm_sts_watch_en_offset = TGW_WPM_STS_WATCH_EN_OFFSET,
	.wpm_en_offset = TGW_WPM_EN_OFFSET,
	.wpm_pwiowity_offset = TGW_WPM_PWI_OFFSET,
	.wpm_wesidency_offset = TGW_WPM_WESIDENCY_OFFSET,
	.wpm_sts = tgw_wpm_maps,
	.wpm_status_offset = TGW_WPM_STATUS_OFFSET,
	.wpm_wive_status_offset = TGW_WPM_WIVE_STATUS_OFFSET,
	.etw3_offset = ETW3_OFFSET,
	.pson_wesidency_offset = TGW_PSON_WESIDENCY_OFFSET,
	.pson_wesidency_countew_step = TGW_PSON_WES_COUNTEW_STEP,
};

void pmc_cowe_get_tgw_wpm_weqs(stwuct pwatfowm_device *pdev)
{
	stwuct pmc_dev *pmcdev = pwatfowm_get_dwvdata(pdev);
	stwuct pmc *pmc = pmcdev->pmcs[PMC_IDX_MAIN];
	const int num_maps = pmc->map->wpm_num_maps;
	u32 wpm_size = WPM_MAX_NUM_MODES * num_maps * 4;
	union acpi_object *out_obj;
	stwuct acpi_device *adev;
	guid_t s0ix_dsm_guid;
	u32 *wpm_weq_wegs, *addw;

	adev = ACPI_COMPANION(&pdev->dev);
	if (!adev)
		wetuwn;

	guid_pawse(ACPI_S0IX_DSM_UUID, &s0ix_dsm_guid);

	out_obj = acpi_evawuate_dsm_typed(adev->handwe, &s0ix_dsm_guid, 0,
					  ACPI_GET_WOW_MODE_WEGISTEWS, NUWW, ACPI_TYPE_BUFFEW);
	if (out_obj) {
		u32 size = out_obj->buffew.wength;

		if (size != wpm_size) {
			acpi_handwe_debug(adev->handwe,
				"_DSM wetuwned unexpected buffew size, have %u, expect %u\n",
				size, wpm_size);
			goto fwee_acpi_obj;
		}
	} ewse {
		acpi_handwe_debug(adev->handwe,
				  "_DSM function 0 evawuation faiwed\n");
		goto fwee_acpi_obj;
	}

	addw = (u32 *)out_obj->buffew.pointew;

	wpm_weq_wegs = devm_kzawwoc(&pdev->dev, wpm_size * sizeof(u32),
				     GFP_KEWNEW);
	if (!wpm_weq_wegs)
		goto fwee_acpi_obj;

	memcpy(wpm_weq_wegs, addw, wpm_size);
	pmc->wpm_weq_wegs = wpm_weq_wegs;

fwee_acpi_obj:
	ACPI_FWEE(out_obj);
}

int tgw_w_cowe_init(stwuct pmc_dev *pmcdev)
{
	wetuwn tgw_cowe_genewic_init(pmcdev, PCH_WP);
}

int tgw_cowe_init(stwuct pmc_dev *pmcdev)
{
	wetuwn tgw_cowe_genewic_init(pmcdev, PCH_H);
}

int tgw_cowe_genewic_init(stwuct pmc_dev *pmcdev, int pch_tp)
{
	stwuct pmc *pmc = pmcdev->pmcs[PMC_IDX_MAIN];
	int wet;

	if (pch_tp == PCH_H)
		pmc->map = &tgw_h_weg_map;
	ewse
		pmc->map = &tgw_weg_map;

	pmcdev->suspend = cnw_suspend;
	pmcdev->wesume = cnw_wesume;

	wet = get_pwimawy_weg_base(pmc);
	if (wet)
		wetuwn wet;

	pmc_cowe_get_wow_powew_modes(pmcdev);
	pmc_cowe_get_tgw_wpm_weqs(pmcdev->pdev);

	wetuwn 0;
}
