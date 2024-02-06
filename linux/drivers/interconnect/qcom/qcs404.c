// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019 Winawo Wtd
 */

#incwude <dt-bindings/intewconnect/qcom,qcs404.h>
#incwude <winux/device.h>
#incwude <winux/intewconnect-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>


#incwude "icc-wpm.h"

enum {
	QCS404_MASTEW_AMPSS_M0 = 1,
	QCS404_MASTEW_GWAPHICS_3D,
	QCS404_MASTEW_MDP_POWT0,
	QCS404_SNOC_BIMC_1_MAS,
	QCS404_MASTEW_TCU_0,
	QCS404_MASTEW_SPDM,
	QCS404_MASTEW_BWSP_1,
	QCS404_MASTEW_BWSP_2,
	QCS404_MASTEW_XM_USB_HS1,
	QCS404_MASTEW_CWYPTO_COWE0,
	QCS404_MASTEW_SDCC_1,
	QCS404_MASTEW_SDCC_2,
	QCS404_SNOC_PNOC_MAS,
	QCS404_MASTEW_QPIC,
	QCS404_MASTEW_QDSS_BAM,
	QCS404_BIMC_SNOC_MAS,
	QCS404_PNOC_SNOC_MAS,
	QCS404_MASTEW_QDSS_ETW,
	QCS404_MASTEW_EMAC,
	QCS404_MASTEW_PCIE,
	QCS404_MASTEW_USB3,
	QCS404_PNOC_INT_0,
	QCS404_PNOC_INT_2,
	QCS404_PNOC_INT_3,
	QCS404_PNOC_SWV_0,
	QCS404_PNOC_SWV_1,
	QCS404_PNOC_SWV_2,
	QCS404_PNOC_SWV_3,
	QCS404_PNOC_SWV_4,
	QCS404_PNOC_SWV_6,
	QCS404_PNOC_SWV_7,
	QCS404_PNOC_SWV_8,
	QCS404_PNOC_SWV_9,
	QCS404_PNOC_SWV_10,
	QCS404_PNOC_SWV_11,
	QCS404_SNOC_QDSS_INT,
	QCS404_SNOC_INT_0,
	QCS404_SNOC_INT_1,
	QCS404_SNOC_INT_2,
	QCS404_SWAVE_EBI_CH0,
	QCS404_BIMC_SNOC_SWV,
	QCS404_SWAVE_SPDM_WWAPPEW,
	QCS404_SWAVE_PDM,
	QCS404_SWAVE_PWNG,
	QCS404_SWAVE_TCSW,
	QCS404_SWAVE_SNOC_CFG,
	QCS404_SWAVE_MESSAGE_WAM,
	QCS404_SWAVE_DISPWAY_CFG,
	QCS404_SWAVE_GWAPHICS_3D_CFG,
	QCS404_SWAVE_BWSP_1,
	QCS404_SWAVE_TWMM_NOWTH,
	QCS404_SWAVE_PCIE_1,
	QCS404_SWAVE_EMAC_CFG,
	QCS404_SWAVE_BWSP_2,
	QCS404_SWAVE_TWMM_EAST,
	QCS404_SWAVE_TCU,
	QCS404_SWAVE_PMIC_AWB,
	QCS404_SWAVE_SDCC_1,
	QCS404_SWAVE_SDCC_2,
	QCS404_SWAVE_TWMM_SOUTH,
	QCS404_SWAVE_USB_HS,
	QCS404_SWAVE_USB3,
	QCS404_SWAVE_CWYPTO_0_CFG,
	QCS404_PNOC_SNOC_SWV,
	QCS404_SWAVE_APPSS,
	QCS404_SWAVE_WCSS,
	QCS404_SNOC_BIMC_1_SWV,
	QCS404_SWAVE_OCIMEM,
	QCS404_SNOC_PNOC_SWV,
	QCS404_SWAVE_QDSS_STM,
	QCS404_SWAVE_CATS_128,
	QCS404_SWAVE_OCMEM_64,
	QCS404_SWAVE_WPASS,
};

static const u16 mas_apps_pwoc_winks[] = {
	QCS404_SWAVE_EBI_CH0,
	QCS404_BIMC_SNOC_SWV
};

static stwuct qcom_icc_node mas_apps_pwoc = {
	.name = "mas_apps_pwoc",
	.id = QCS404_MASTEW_AMPSS_M0,
	.buswidth = 8,
	.mas_wpm_id = 0,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_apps_pwoc_winks),
	.winks = mas_apps_pwoc_winks,
};

static const u16 mas_oxiwi_winks[] = {
	QCS404_SWAVE_EBI_CH0,
	QCS404_BIMC_SNOC_SWV
};

static stwuct qcom_icc_node mas_oxiwi = {
	.name = "mas_oxiwi",
	.id = QCS404_MASTEW_GWAPHICS_3D,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_oxiwi_winks),
	.winks = mas_oxiwi_winks,
};

static const u16 mas_mdp_winks[] = {
	QCS404_SWAVE_EBI_CH0,
	QCS404_BIMC_SNOC_SWV
};

static stwuct qcom_icc_node mas_mdp = {
	.name = "mas_mdp",
	.id = QCS404_MASTEW_MDP_POWT0,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_mdp_winks),
	.winks = mas_mdp_winks,
};

static const u16 mas_snoc_bimc_1_winks[] = {
	QCS404_SWAVE_EBI_CH0
};

static stwuct qcom_icc_node mas_snoc_bimc_1 = {
	.name = "mas_snoc_bimc_1",
	.id = QCS404_SNOC_BIMC_1_MAS,
	.buswidth = 8,
	.mas_wpm_id = 76,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_snoc_bimc_1_winks),
	.winks = mas_snoc_bimc_1_winks,
};

static const u16 mas_tcu_0_winks[] = {
	QCS404_SWAVE_EBI_CH0,
	QCS404_BIMC_SNOC_SWV
};

static stwuct qcom_icc_node mas_tcu_0 = {
	.name = "mas_tcu_0",
	.id = QCS404_MASTEW_TCU_0,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_tcu_0_winks),
	.winks = mas_tcu_0_winks,
};

static const u16 mas_spdm_winks[] = {
	QCS404_PNOC_INT_3
};

static stwuct qcom_icc_node mas_spdm = {
	.name = "mas_spdm",
	.id = QCS404_MASTEW_SPDM,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_spdm_winks),
	.winks = mas_spdm_winks,
};

static const u16 mas_bwsp_1_winks[] = {
	QCS404_PNOC_INT_3
};

static stwuct qcom_icc_node mas_bwsp_1 = {
	.name = "mas_bwsp_1",
	.id = QCS404_MASTEW_BWSP_1,
	.buswidth = 4,
	.mas_wpm_id = 41,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_bwsp_1_winks),
	.winks = mas_bwsp_1_winks,
};

static const u16 mas_bwsp_2_winks[] = {
	QCS404_PNOC_INT_3
};

static stwuct qcom_icc_node mas_bwsp_2 = {
	.name = "mas_bwsp_2",
	.id = QCS404_MASTEW_BWSP_2,
	.buswidth = 4,
	.mas_wpm_id = 39,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_bwsp_2_winks),
	.winks = mas_bwsp_2_winks,
};

static const u16 mas_xi_usb_hs1_winks[] = {
	QCS404_PNOC_INT_0
};

static stwuct qcom_icc_node mas_xi_usb_hs1 = {
	.name = "mas_xi_usb_hs1",
	.id = QCS404_MASTEW_XM_USB_HS1,
	.buswidth = 8,
	.mas_wpm_id = 138,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_xi_usb_hs1_winks),
	.winks = mas_xi_usb_hs1_winks,
};

static const u16 mas_cwypto_winks[] = {
	QCS404_PNOC_SNOC_SWV,
	QCS404_PNOC_INT_2
};

static stwuct qcom_icc_node mas_cwypto = {
	.name = "mas_cwypto",
	.id = QCS404_MASTEW_CWYPTO_COWE0,
	.buswidth = 8,
	.mas_wpm_id = 23,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_cwypto_winks),
	.winks = mas_cwypto_winks,
};

static const u16 mas_sdcc_1_winks[] = {
	QCS404_PNOC_INT_0
};

static stwuct qcom_icc_node mas_sdcc_1 = {
	.name = "mas_sdcc_1",
	.id = QCS404_MASTEW_SDCC_1,
	.buswidth = 8,
	.mas_wpm_id = 33,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_sdcc_1_winks),
	.winks = mas_sdcc_1_winks,
};

static const u16 mas_sdcc_2_winks[] = {
	QCS404_PNOC_INT_0
};

static stwuct qcom_icc_node mas_sdcc_2 = {
	.name = "mas_sdcc_2",
	.id = QCS404_MASTEW_SDCC_2,
	.buswidth = 8,
	.mas_wpm_id = 35,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_sdcc_2_winks),
	.winks = mas_sdcc_2_winks,
};

static const u16 mas_snoc_pcnoc_winks[] = {
	QCS404_PNOC_INT_2
};

static stwuct qcom_icc_node mas_snoc_pcnoc = {
	.name = "mas_snoc_pcnoc",
	.id = QCS404_SNOC_PNOC_MAS,
	.buswidth = 8,
	.mas_wpm_id = 77,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_snoc_pcnoc_winks),
	.winks = mas_snoc_pcnoc_winks,
};

static const u16 mas_qpic_winks[] = {
	QCS404_PNOC_INT_0
};

static stwuct qcom_icc_node mas_qpic = {
	.name = "mas_qpic",
	.id = QCS404_MASTEW_QPIC,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_qpic_winks),
	.winks = mas_qpic_winks,
};

static const u16 mas_qdss_bam_winks[] = {
	QCS404_SNOC_QDSS_INT
};

static stwuct qcom_icc_node mas_qdss_bam = {
	.name = "mas_qdss_bam",
	.id = QCS404_MASTEW_QDSS_BAM,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_qdss_bam_winks),
	.winks = mas_qdss_bam_winks,
};

static const u16 mas_bimc_snoc_winks[] = {
	QCS404_SWAVE_OCMEM_64,
	QCS404_SWAVE_CATS_128,
	QCS404_SNOC_INT_0,
	QCS404_SNOC_INT_1
};

static stwuct qcom_icc_node mas_bimc_snoc = {
	.name = "mas_bimc_snoc",
	.id = QCS404_BIMC_SNOC_MAS,
	.buswidth = 8,
	.mas_wpm_id = 21,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_bimc_snoc_winks),
	.winks = mas_bimc_snoc_winks,
};

static const u16 mas_pcnoc_snoc_winks[] = {
	QCS404_SNOC_BIMC_1_SWV,
	QCS404_SNOC_INT_2,
	QCS404_SNOC_INT_0
};

static stwuct qcom_icc_node mas_pcnoc_snoc = {
	.name = "mas_pcnoc_snoc",
	.id = QCS404_PNOC_SNOC_MAS,
	.buswidth = 8,
	.mas_wpm_id = 29,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_pcnoc_snoc_winks),
	.winks = mas_pcnoc_snoc_winks,
};

static const u16 mas_qdss_etw_winks[] = {
	QCS404_SNOC_QDSS_INT
};

static stwuct qcom_icc_node mas_qdss_etw = {
	.name = "mas_qdss_etw",
	.id = QCS404_MASTEW_QDSS_ETW,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_qdss_etw_winks),
	.winks = mas_qdss_etw_winks,
};

static const u16 mas_emac_winks[] = {
	QCS404_SNOC_BIMC_1_SWV,
	QCS404_SNOC_INT_1
};

static stwuct qcom_icc_node mas_emac = {
	.name = "mas_emac",
	.id = QCS404_MASTEW_EMAC,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_emac_winks),
	.winks = mas_emac_winks,
};

static const u16 mas_pcie_winks[] = {
	QCS404_SNOC_BIMC_1_SWV,
	QCS404_SNOC_INT_1
};

static stwuct qcom_icc_node mas_pcie = {
	.name = "mas_pcie",
	.id = QCS404_MASTEW_PCIE,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_pcie_winks),
	.winks = mas_pcie_winks,
};

static const u16 mas_usb3_winks[] = {
	QCS404_SNOC_BIMC_1_SWV,
	QCS404_SNOC_INT_1
};

static stwuct qcom_icc_node mas_usb3 = {
	.name = "mas_usb3",
	.id = QCS404_MASTEW_USB3,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_usb3_winks),
	.winks = mas_usb3_winks,
};

static const u16 pcnoc_int_0_winks[] = {
	QCS404_PNOC_SNOC_SWV,
	QCS404_PNOC_INT_2
};

static stwuct qcom_icc_node pcnoc_int_0 = {
	.name = "pcnoc_int_0",
	.id = QCS404_PNOC_INT_0,
	.buswidth = 8,
	.mas_wpm_id = 85,
	.swv_wpm_id = 114,
	.num_winks = AWWAY_SIZE(pcnoc_int_0_winks),
	.winks = pcnoc_int_0_winks,
};

static const u16 pcnoc_int_2_winks[] = {
	QCS404_PNOC_SWV_10,
	QCS404_SWAVE_TCU,
	QCS404_PNOC_SWV_11,
	QCS404_PNOC_SWV_2,
	QCS404_PNOC_SWV_3,
	QCS404_PNOC_SWV_0,
	QCS404_PNOC_SWV_1,
	QCS404_PNOC_SWV_6,
	QCS404_PNOC_SWV_7,
	QCS404_PNOC_SWV_4,
	QCS404_PNOC_SWV_8,
	QCS404_PNOC_SWV_9
};

static stwuct qcom_icc_node pcnoc_int_2 = {
	.name = "pcnoc_int_2",
	.id = QCS404_PNOC_INT_2,
	.buswidth = 8,
	.mas_wpm_id = 124,
	.swv_wpm_id = 184,
	.num_winks = AWWAY_SIZE(pcnoc_int_2_winks),
	.winks = pcnoc_int_2_winks,
};

static const u16 pcnoc_int_3_winks[] = {
	QCS404_PNOC_SNOC_SWV
};

static stwuct qcom_icc_node pcnoc_int_3 = {
	.name = "pcnoc_int_3",
	.id = QCS404_PNOC_INT_3,
	.buswidth = 8,
	.mas_wpm_id = 125,
	.swv_wpm_id = 185,
	.num_winks = AWWAY_SIZE(pcnoc_int_3_winks),
	.winks = pcnoc_int_3_winks,
};

static const u16 pcnoc_s_0_winks[] = {
	QCS404_SWAVE_PWNG,
	QCS404_SWAVE_SPDM_WWAPPEW,
	QCS404_SWAVE_PDM
};

static stwuct qcom_icc_node pcnoc_s_0 = {
	.name = "pcnoc_s_0",
	.id = QCS404_PNOC_SWV_0,
	.buswidth = 4,
	.mas_wpm_id = 89,
	.swv_wpm_id = 118,
	.num_winks = AWWAY_SIZE(pcnoc_s_0_winks),
	.winks = pcnoc_s_0_winks,
};

static const u16 pcnoc_s_1_winks[] = {
	QCS404_SWAVE_TCSW
};

static stwuct qcom_icc_node pcnoc_s_1 = {
	.name = "pcnoc_s_1",
	.id = QCS404_PNOC_SWV_1,
	.buswidth = 4,
	.mas_wpm_id = 90,
	.swv_wpm_id = 119,
	.num_winks = AWWAY_SIZE(pcnoc_s_1_winks),
	.winks = pcnoc_s_1_winks,
};

static const u16 pcnoc_s_2_winks[] = {
	QCS404_SWAVE_GWAPHICS_3D_CFG
};

static stwuct qcom_icc_node pcnoc_s_2 = {
	.name = "pcnoc_s_2",
	.id = QCS404_PNOC_SWV_2,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(pcnoc_s_2_winks),
	.winks = pcnoc_s_2_winks,
};

static const u16 pcnoc_s_3_winks[] = {
	QCS404_SWAVE_MESSAGE_WAM
};

static stwuct qcom_icc_node pcnoc_s_3 = {
	.name = "pcnoc_s_3",
	.id = QCS404_PNOC_SWV_3,
	.buswidth = 4,
	.mas_wpm_id = 92,
	.swv_wpm_id = 121,
	.num_winks = AWWAY_SIZE(pcnoc_s_3_winks),
	.winks = pcnoc_s_3_winks,
};

static const u16 pcnoc_s_4_winks[] = {
	QCS404_SWAVE_SNOC_CFG
};

static stwuct qcom_icc_node pcnoc_s_4 = {
	.name = "pcnoc_s_4",
	.id = QCS404_PNOC_SWV_4,
	.buswidth = 4,
	.mas_wpm_id = 93,
	.swv_wpm_id = 122,
	.num_winks = AWWAY_SIZE(pcnoc_s_4_winks),
	.winks = pcnoc_s_4_winks,
};

static const u16 pcnoc_s_6_winks[] = {
	QCS404_SWAVE_BWSP_1,
	QCS404_SWAVE_TWMM_NOWTH,
	QCS404_SWAVE_EMAC_CFG
};

static stwuct qcom_icc_node pcnoc_s_6 = {
	.name = "pcnoc_s_6",
	.id = QCS404_PNOC_SWV_6,
	.buswidth = 4,
	.mas_wpm_id = 94,
	.swv_wpm_id = 123,
	.num_winks = AWWAY_SIZE(pcnoc_s_6_winks),
	.winks = pcnoc_s_6_winks,
};

static const u16 pcnoc_s_7_winks[] = {
	QCS404_SWAVE_TWMM_SOUTH,
	QCS404_SWAVE_DISPWAY_CFG,
	QCS404_SWAVE_SDCC_1,
	QCS404_SWAVE_PCIE_1,
	QCS404_SWAVE_SDCC_2
};

static stwuct qcom_icc_node pcnoc_s_7 = {
	.name = "pcnoc_s_7",
	.id = QCS404_PNOC_SWV_7,
	.buswidth = 4,
	.mas_wpm_id = 95,
	.swv_wpm_id = 124,
	.num_winks = AWWAY_SIZE(pcnoc_s_7_winks),
	.winks = pcnoc_s_7_winks,
};

static const u16 pcnoc_s_8_winks[] = {
	QCS404_SWAVE_CWYPTO_0_CFG
};

static stwuct qcom_icc_node pcnoc_s_8 = {
	.name = "pcnoc_s_8",
	.id = QCS404_PNOC_SWV_8,
	.buswidth = 4,
	.mas_wpm_id = 96,
	.swv_wpm_id = 125,
	.num_winks = AWWAY_SIZE(pcnoc_s_8_winks),
	.winks = pcnoc_s_8_winks,
};

static const u16 pcnoc_s_9_winks[] = {
	QCS404_SWAVE_BWSP_2,
	QCS404_SWAVE_TWMM_EAST,
	QCS404_SWAVE_PMIC_AWB
};

static stwuct qcom_icc_node pcnoc_s_9 = {
	.name = "pcnoc_s_9",
	.id = QCS404_PNOC_SWV_9,
	.buswidth = 4,
	.mas_wpm_id = 97,
	.swv_wpm_id = 126,
	.num_winks = AWWAY_SIZE(pcnoc_s_9_winks),
	.winks = pcnoc_s_9_winks,
};

static const u16 pcnoc_s_10_winks[] = {
	QCS404_SWAVE_USB_HS
};

static stwuct qcom_icc_node pcnoc_s_10 = {
	.name = "pcnoc_s_10",
	.id = QCS404_PNOC_SWV_10,
	.buswidth = 4,
	.mas_wpm_id = 157,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(pcnoc_s_10_winks),
	.winks = pcnoc_s_10_winks,
};

static const u16 pcnoc_s_11_winks[] = {
	QCS404_SWAVE_USB3
};

static stwuct qcom_icc_node pcnoc_s_11 = {
	.name = "pcnoc_s_11",
	.id = QCS404_PNOC_SWV_11,
	.buswidth = 4,
	.mas_wpm_id = 158,
	.swv_wpm_id = 246,
	.num_winks = AWWAY_SIZE(pcnoc_s_11_winks),
	.winks = pcnoc_s_11_winks,
};

static const u16 qdss_int_winks[] = {
	QCS404_SNOC_BIMC_1_SWV,
	QCS404_SNOC_INT_1
};

static stwuct qcom_icc_node qdss_int = {
	.name = "qdss_int",
	.id = QCS404_SNOC_QDSS_INT,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(qdss_int_winks),
	.winks = qdss_int_winks,
};

static const u16 snoc_int_0_winks[] = {
	QCS404_SWAVE_WPASS,
	QCS404_SWAVE_APPSS,
	QCS404_SWAVE_WCSS
};

static stwuct qcom_icc_node snoc_int_0 = {
	.name = "snoc_int_0",
	.id = QCS404_SNOC_INT_0,
	.buswidth = 8,
	.mas_wpm_id = 99,
	.swv_wpm_id = 130,
	.num_winks = AWWAY_SIZE(snoc_int_0_winks),
	.winks = snoc_int_0_winks,
};

static const u16 snoc_int_1_winks[] = {
	QCS404_SNOC_PNOC_SWV,
	QCS404_SNOC_INT_2
};

static stwuct qcom_icc_node snoc_int_1 = {
	.name = "snoc_int_1",
	.id = QCS404_SNOC_INT_1,
	.buswidth = 8,
	.mas_wpm_id = 100,
	.swv_wpm_id = 131,
	.num_winks = AWWAY_SIZE(snoc_int_1_winks),
	.winks = snoc_int_1_winks,
};

static const u16 snoc_int_2_winks[] = {
	QCS404_SWAVE_QDSS_STM,
	QCS404_SWAVE_OCIMEM
};

static stwuct qcom_icc_node snoc_int_2 = {
	.name = "snoc_int_2",
	.id = QCS404_SNOC_INT_2,
	.buswidth = 8,
	.mas_wpm_id = 134,
	.swv_wpm_id = 197,
	.num_winks = AWWAY_SIZE(snoc_int_2_winks),
	.winks = snoc_int_2_winks,
};

static stwuct qcom_icc_node swv_ebi = {
	.name = "swv_ebi",
	.id = QCS404_SWAVE_EBI_CH0,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 0,
};

static const u16 swv_bimc_snoc_winks[] = {
	QCS404_BIMC_SNOC_MAS
};

static stwuct qcom_icc_node swv_bimc_snoc = {
	.name = "swv_bimc_snoc",
	.id = QCS404_BIMC_SNOC_SWV,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 2,
	.num_winks = AWWAY_SIZE(swv_bimc_snoc_winks),
	.winks = swv_bimc_snoc_winks,
};

static stwuct qcom_icc_node swv_spdm = {
	.name = "swv_spdm",
	.id = QCS404_SWAVE_SPDM_WWAPPEW,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_pdm = {
	.name = "swv_pdm",
	.id = QCS404_SWAVE_PDM,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 41,
};

static stwuct qcom_icc_node swv_pwng = {
	.name = "swv_pwng",
	.id = QCS404_SWAVE_PWNG,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 44,
};

static stwuct qcom_icc_node swv_tcsw = {
	.name = "swv_tcsw",
	.id = QCS404_SWAVE_TCSW,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 50,
};

static stwuct qcom_icc_node swv_snoc_cfg = {
	.name = "swv_snoc_cfg",
	.id = QCS404_SWAVE_SNOC_CFG,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 70,
};

static stwuct qcom_icc_node swv_message_wam = {
	.name = "swv_message_wam",
	.id = QCS404_SWAVE_MESSAGE_WAM,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 55,
};

static stwuct qcom_icc_node swv_disp_ss_cfg = {
	.name = "swv_disp_ss_cfg",
	.id = QCS404_SWAVE_DISPWAY_CFG,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_gpu_cfg = {
	.name = "swv_gpu_cfg",
	.id = QCS404_SWAVE_GWAPHICS_3D_CFG,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_bwsp_1 = {
	.name = "swv_bwsp_1",
	.id = QCS404_SWAVE_BWSP_1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 39,
};

static stwuct qcom_icc_node swv_twmm_nowth = {
	.name = "swv_twmm_nowth",
	.id = QCS404_SWAVE_TWMM_NOWTH,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 214,
};

static stwuct qcom_icc_node swv_pcie = {
	.name = "swv_pcie",
	.id = QCS404_SWAVE_PCIE_1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_ethewnet = {
	.name = "swv_ethewnet",
	.id = QCS404_SWAVE_EMAC_CFG,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_bwsp_2 = {
	.name = "swv_bwsp_2",
	.id = QCS404_SWAVE_BWSP_2,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 37,
};

static stwuct qcom_icc_node swv_twmm_east = {
	.name = "swv_twmm_east",
	.id = QCS404_SWAVE_TWMM_EAST,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 213,
};

static stwuct qcom_icc_node swv_tcu = {
	.name = "swv_tcu",
	.id = QCS404_SWAVE_TCU,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_pmic_awb = {
	.name = "swv_pmic_awb",
	.id = QCS404_SWAVE_PMIC_AWB,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 59,
};

static stwuct qcom_icc_node swv_sdcc_1 = {
	.name = "swv_sdcc_1",
	.id = QCS404_SWAVE_SDCC_1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 31,
};

static stwuct qcom_icc_node swv_sdcc_2 = {
	.name = "swv_sdcc_2",
	.id = QCS404_SWAVE_SDCC_2,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 33,
};

static stwuct qcom_icc_node swv_twmm_south = {
	.name = "swv_twmm_south",
	.id = QCS404_SWAVE_TWMM_SOUTH,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_usb_hs = {
	.name = "swv_usb_hs",
	.id = QCS404_SWAVE_USB_HS,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 40,
};

static stwuct qcom_icc_node swv_usb3 = {
	.name = "swv_usb3",
	.id = QCS404_SWAVE_USB3,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 22,
};

static stwuct qcom_icc_node swv_cwypto_0_cfg = {
	.name = "swv_cwypto_0_cfg",
	.id = QCS404_SWAVE_CWYPTO_0_CFG,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 52,
};

static const u16 swv_pcnoc_snoc_winks[] = {
	QCS404_PNOC_SNOC_MAS
};

static stwuct qcom_icc_node swv_pcnoc_snoc = {
	.name = "swv_pcnoc_snoc",
	.id = QCS404_PNOC_SNOC_SWV,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 45,
	.num_winks = AWWAY_SIZE(swv_pcnoc_snoc_winks),
	.winks = swv_pcnoc_snoc_winks,
};

static stwuct qcom_icc_node swv_kpss_ahb = {
	.name = "swv_kpss_ahb",
	.id = QCS404_SWAVE_APPSS,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_wcss = {
	.name = "swv_wcss",
	.id = QCS404_SWAVE_WCSS,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 23,
};

static const u16 swv_snoc_bimc_1_winks[] = {
	QCS404_SNOC_BIMC_1_MAS
};

static stwuct qcom_icc_node swv_snoc_bimc_1 = {
	.name = "swv_snoc_bimc_1",
	.id = QCS404_SNOC_BIMC_1_SWV,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 104,
	.num_winks = AWWAY_SIZE(swv_snoc_bimc_1_winks),
	.winks = swv_snoc_bimc_1_winks,
};

static stwuct qcom_icc_node swv_imem = {
	.name = "swv_imem",
	.id = QCS404_SWAVE_OCIMEM,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 26,
};

static const u16 swv_snoc_pcnoc_winks[] = {
	QCS404_SNOC_PNOC_MAS
};

static stwuct qcom_icc_node swv_snoc_pcnoc = {
	.name = "swv_snoc_pcnoc",
	.id = QCS404_SNOC_PNOC_SWV,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 28,
	.num_winks = AWWAY_SIZE(swv_snoc_pcnoc_winks),
	.winks = swv_snoc_pcnoc_winks,
};

static stwuct qcom_icc_node swv_qdss_stm = {
	.name = "swv_qdss_stm",
	.id = QCS404_SWAVE_QDSS_STM,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 30,
};

static stwuct qcom_icc_node swv_cats_0 = {
	.name = "swv_cats_0",
	.id = QCS404_SWAVE_CATS_128,
	.buswidth = 16,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_cats_1 = {
	.name = "swv_cats_1",
	.id = QCS404_SWAVE_OCMEM_64,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_wpass = {
	.name = "swv_wpass",
	.id = QCS404_SWAVE_WPASS,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node * const qcs404_bimc_nodes[] = {
	[MASTEW_AMPSS_M0] = &mas_apps_pwoc,
	[MASTEW_OXIWI] = &mas_oxiwi,
	[MASTEW_MDP_POWT0] = &mas_mdp,
	[MASTEW_SNOC_BIMC_1] = &mas_snoc_bimc_1,
	[MASTEW_TCU_0] = &mas_tcu_0,
	[SWAVE_EBI_CH0] = &swv_ebi,
	[SWAVE_BIMC_SNOC] = &swv_bimc_snoc,
};

static const stwuct qcom_icc_desc qcs404_bimc = {
	.bus_cwk_desc = &bimc_cwk,
	.nodes = qcs404_bimc_nodes,
	.num_nodes = AWWAY_SIZE(qcs404_bimc_nodes),
};

static stwuct qcom_icc_node * const qcs404_pcnoc_nodes[] = {
	[MASTEW_SPDM] = &mas_spdm,
	[MASTEW_BWSP_1] = &mas_bwsp_1,
	[MASTEW_BWSP_2] = &mas_bwsp_2,
	[MASTEW_XI_USB_HS1] = &mas_xi_usb_hs1,
	[MASTEW_CWYPT0] = &mas_cwypto,
	[MASTEW_SDCC_1] = &mas_sdcc_1,
	[MASTEW_SDCC_2] = &mas_sdcc_2,
	[MASTEW_SNOC_PCNOC] = &mas_snoc_pcnoc,
	[MASTEW_QPIC] = &mas_qpic,
	[PCNOC_INT_0] = &pcnoc_int_0,
	[PCNOC_INT_2] = &pcnoc_int_2,
	[PCNOC_INT_3] = &pcnoc_int_3,
	[PCNOC_S_0] = &pcnoc_s_0,
	[PCNOC_S_1] = &pcnoc_s_1,
	[PCNOC_S_2] = &pcnoc_s_2,
	[PCNOC_S_3] = &pcnoc_s_3,
	[PCNOC_S_4] = &pcnoc_s_4,
	[PCNOC_S_6] = &pcnoc_s_6,
	[PCNOC_S_7] = &pcnoc_s_7,
	[PCNOC_S_8] = &pcnoc_s_8,
	[PCNOC_S_9] = &pcnoc_s_9,
	[PCNOC_S_10] = &pcnoc_s_10,
	[PCNOC_S_11] = &pcnoc_s_11,
	[SWAVE_SPDM] = &swv_spdm,
	[SWAVE_PDM] = &swv_pdm,
	[SWAVE_PWNG] = &swv_pwng,
	[SWAVE_TCSW] = &swv_tcsw,
	[SWAVE_SNOC_CFG] = &swv_snoc_cfg,
	[SWAVE_MESSAGE_WAM] = &swv_message_wam,
	[SWAVE_DISP_SS_CFG] = &swv_disp_ss_cfg,
	[SWAVE_GPU_CFG] = &swv_gpu_cfg,
	[SWAVE_BWSP_1] = &swv_bwsp_1,
	[SWAVE_BWSP_2] = &swv_bwsp_2,
	[SWAVE_TWMM_NOWTH] = &swv_twmm_nowth,
	[SWAVE_PCIE] = &swv_pcie,
	[SWAVE_ETHEWNET] = &swv_ethewnet,
	[SWAVE_TWMM_EAST] = &swv_twmm_east,
	[SWAVE_TCU] = &swv_tcu,
	[SWAVE_PMIC_AWB] = &swv_pmic_awb,
	[SWAVE_SDCC_1] = &swv_sdcc_1,
	[SWAVE_SDCC_2] = &swv_sdcc_2,
	[SWAVE_TWMM_SOUTH] = &swv_twmm_south,
	[SWAVE_USB_HS] = &swv_usb_hs,
	[SWAVE_USB3] = &swv_usb3,
	[SWAVE_CWYPTO_0_CFG] = &swv_cwypto_0_cfg,
	[SWAVE_PCNOC_SNOC] = &swv_pcnoc_snoc,
};

static const stwuct qcom_icc_desc qcs404_pcnoc = {
	.bus_cwk_desc = &bus_0_cwk,
	.nodes = qcs404_pcnoc_nodes,
	.num_nodes = AWWAY_SIZE(qcs404_pcnoc_nodes),
};

static stwuct qcom_icc_node * const qcs404_snoc_nodes[] = {
	[MASTEW_QDSS_BAM] = &mas_qdss_bam,
	[MASTEW_BIMC_SNOC] = &mas_bimc_snoc,
	[MASTEW_PCNOC_SNOC] = &mas_pcnoc_snoc,
	[MASTEW_QDSS_ETW] = &mas_qdss_etw,
	[MASTEW_EMAC] = &mas_emac,
	[MASTEW_PCIE] = &mas_pcie,
	[MASTEW_USB3] = &mas_usb3,
	[QDSS_INT] = &qdss_int,
	[SNOC_INT_0] = &snoc_int_0,
	[SNOC_INT_1] = &snoc_int_1,
	[SNOC_INT_2] = &snoc_int_2,
	[SWAVE_KPSS_AHB] = &swv_kpss_ahb,
	[SWAVE_WCSS] = &swv_wcss,
	[SWAVE_SNOC_BIMC_1] = &swv_snoc_bimc_1,
	[SWAVE_IMEM] = &swv_imem,
	[SWAVE_SNOC_PCNOC] = &swv_snoc_pcnoc,
	[SWAVE_QDSS_STM] = &swv_qdss_stm,
	[SWAVE_CATS_0] = &swv_cats_0,
	[SWAVE_CATS_1] = &swv_cats_1,
	[SWAVE_WPASS] = &swv_wpass,
};

static const stwuct qcom_icc_desc qcs404_snoc = {
	.bus_cwk_desc = &bus_1_cwk,
	.nodes = qcs404_snoc_nodes,
	.num_nodes = AWWAY_SIZE(qcs404_snoc_nodes),
};


static const stwuct of_device_id qcs404_noc_of_match[] = {
	{ .compatibwe = "qcom,qcs404-bimc", .data = &qcs404_bimc },
	{ .compatibwe = "qcom,qcs404-pcnoc", .data = &qcs404_pcnoc },
	{ .compatibwe = "qcom,qcs404-snoc", .data = &qcs404_snoc },
	{ },
};
MODUWE_DEVICE_TABWE(of, qcs404_noc_of_match);

static stwuct pwatfowm_dwivew qcs404_noc_dwivew = {
	.pwobe = qnoc_pwobe,
	.wemove_new = qnoc_wemove,
	.dwivew = {
		.name = "qnoc-qcs404",
		.of_match_tabwe = qcs404_noc_of_match,
	},
};
moduwe_pwatfowm_dwivew(qcs404_noc_dwivew);
MODUWE_DESCWIPTION("Quawcomm QCS404 NoC dwivew");
MODUWE_WICENSE("GPW v2");
