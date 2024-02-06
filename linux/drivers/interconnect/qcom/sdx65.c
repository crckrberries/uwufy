// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2022, Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude <winux/device.h>
#incwude <winux/intewconnect.h>
#incwude <winux/intewconnect-pwovidew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <dt-bindings/intewconnect/qcom,sdx65.h>

#incwude "bcm-votew.h"
#incwude "icc-wpmh.h"
#incwude "sdx65.h"

static stwuct qcom_icc_node wwcc_mc = {
	.name = "wwcc_mc",
	.id = SDX65_MASTEW_WWCC,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SDX65_SWAVE_EBI1 },
};

static stwuct qcom_icc_node acm_tcu = {
	.name = "acm_tcu",
	.id = SDX65_MASTEW_TCU_0,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 3,
	.winks = { SDX65_SWAVE_WWCC,
		   SDX65_SWAVE_MEM_NOC_SNOC,
		   SDX65_SWAVE_MEM_NOC_PCIE_SNOC
	},
};

static stwuct qcom_icc_node qnm_snoc_gc = {
	.name = "qnm_snoc_gc",
	.id = SDX65_MASTEW_SNOC_GC_MEM_NOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SDX65_SWAVE_WWCC },
};

static stwuct qcom_icc_node xm_apps_wdww = {
	.name = "xm_apps_wdww",
	.id = SDX65_MASTEW_APPSS_PWOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 3,
	.winks = { SDX65_SWAVE_WWCC,
		   SDX65_SWAVE_MEM_NOC_SNOC,
		   SDX65_SWAVE_MEM_NOC_PCIE_SNOC
	},
};

static stwuct qcom_icc_node qhm_audio = {
	.name = "qhm_audio",
	.id = SDX65_MASTEW_AUDIO,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SDX65_SWAVE_ANOC_SNOC },
};

static stwuct qcom_icc_node qhm_bwsp1 = {
	.name = "qhm_bwsp1",
	.id = SDX65_MASTEW_BWSP_1,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SDX65_SWAVE_ANOC_SNOC },
};

static stwuct qcom_icc_node qhm_qdss_bam = {
	.name = "qhm_qdss_bam",
	.id = SDX65_MASTEW_QDSS_BAM,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 26,
	.winks = { SDX65_SWAVE_AOSS,
		   SDX65_SWAVE_AUDIO,
		   SDX65_SWAVE_BWSP_1,
		   SDX65_SWAVE_CWK_CTW,
		   SDX65_SWAVE_CWYPTO_0_CFG,
		   SDX65_SWAVE_CNOC_DDWSS,
		   SDX65_SWAVE_ECC_CFG,
		   SDX65_SWAVE_IMEM_CFG,
		   SDX65_SWAVE_IPA_CFG,
		   SDX65_SWAVE_CNOC_MSS,
		   SDX65_SWAVE_PCIE_PAWF,
		   SDX65_SWAVE_PDM,
		   SDX65_SWAVE_PWNG,
		   SDX65_SWAVE_QDSS_CFG,
		   SDX65_SWAVE_QPIC,
		   SDX65_SWAVE_SDCC_1,
		   SDX65_SWAVE_SNOC_CFG,
		   SDX65_SWAVE_SPMI_FETCHEW,
		   SDX65_SWAVE_SPMI_VGI_COEX,
		   SDX65_SWAVE_TCSW,
		   SDX65_SWAVE_TWMM,
		   SDX65_SWAVE_USB3,
		   SDX65_SWAVE_USB3_PHY_CFG,
		   SDX65_SWAVE_SNOC_MEM_NOC_GC,
		   SDX65_SWAVE_IMEM,
		   SDX65_SWAVE_TCU
	},
};

static stwuct qcom_icc_node qhm_qpic = {
	.name = "qhm_qpic",
	.id = SDX65_MASTEW_QPIC,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 4,
	.winks = { SDX65_SWAVE_AOSS,
		   SDX65_SWAVE_AUDIO,
		   SDX65_SWAVE_IPA_CFG,
		   SDX65_SWAVE_ANOC_SNOC
	},
};

static stwuct qcom_icc_node qhm_snoc_cfg = {
	.name = "qhm_snoc_cfg",
	.id = SDX65_MASTEW_SNOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SDX65_SWAVE_SEWVICE_SNOC },
};

static stwuct qcom_icc_node qhm_spmi_fetchew1 = {
	.name = "qhm_spmi_fetchew1",
	.id = SDX65_MASTEW_SPMI_FETCHEW,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 2,
	.winks = { SDX65_SWAVE_AOSS,
		   SDX65_SWAVE_ANOC_SNOC
	},
};

static stwuct qcom_icc_node qnm_aggwe_noc = {
	.name = "qnm_aggwe_noc",
	.id = SDX65_MASTEW_ANOC_SNOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 29,
	.winks = { SDX65_SWAVE_AOSS,
		   SDX65_SWAVE_APPSS,
		   SDX65_SWAVE_AUDIO,
		   SDX65_SWAVE_BWSP_1,
		   SDX65_SWAVE_CWK_CTW,
		   SDX65_SWAVE_CWYPTO_0_CFG,
		   SDX65_SWAVE_CNOC_DDWSS,
		   SDX65_SWAVE_ECC_CFG,
		   SDX65_SWAVE_IMEM_CFG,
		   SDX65_SWAVE_IPA_CFG,
		   SDX65_SWAVE_CNOC_MSS,
		   SDX65_SWAVE_PCIE_PAWF,
		   SDX65_SWAVE_PDM,
		   SDX65_SWAVE_PWNG,
		   SDX65_SWAVE_QDSS_CFG,
		   SDX65_SWAVE_QPIC,
		   SDX65_SWAVE_SDCC_1,
		   SDX65_SWAVE_SNOC_CFG,
		   SDX65_SWAVE_SPMI_FETCHEW,
		   SDX65_SWAVE_SPMI_VGI_COEX,
		   SDX65_SWAVE_TCSW,
		   SDX65_SWAVE_TWMM,
		   SDX65_SWAVE_USB3,
		   SDX65_SWAVE_USB3_PHY_CFG,
		   SDX65_SWAVE_SNOC_MEM_NOC_GC,
		   SDX65_SWAVE_IMEM,
		   SDX65_SWAVE_PCIE_0,
		   SDX65_SWAVE_QDSS_STM,
		   SDX65_SWAVE_TCU
	},
};

static stwuct qcom_icc_node qnm_ipa = {
	.name = "qnm_ipa",
	.id = SDX65_MASTEW_IPA,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 26,
	.winks = { SDX65_SWAVE_AOSS,
		   SDX65_SWAVE_AUDIO,
		   SDX65_SWAVE_BWSP_1,
		   SDX65_SWAVE_CWK_CTW,
		   SDX65_SWAVE_CWYPTO_0_CFG,
		   SDX65_SWAVE_CNOC_DDWSS,
		   SDX65_SWAVE_ECC_CFG,
		   SDX65_SWAVE_IMEM_CFG,
		   SDX65_SWAVE_IPA_CFG,
		   SDX65_SWAVE_CNOC_MSS,
		   SDX65_SWAVE_PCIE_PAWF,
		   SDX65_SWAVE_PDM,
		   SDX65_SWAVE_PWNG,
		   SDX65_SWAVE_QDSS_CFG,
		   SDX65_SWAVE_QPIC,
		   SDX65_SWAVE_SDCC_1,
		   SDX65_SWAVE_SNOC_CFG,
		   SDX65_SWAVE_SPMI_FETCHEW,
		   SDX65_SWAVE_TCSW,
		   SDX65_SWAVE_TWMM,
		   SDX65_SWAVE_USB3,
		   SDX65_SWAVE_USB3_PHY_CFG,
		   SDX65_SWAVE_SNOC_MEM_NOC_GC,
		   SDX65_SWAVE_IMEM,
		   SDX65_SWAVE_PCIE_0,
		   SDX65_SWAVE_QDSS_STM
	},
};

static stwuct qcom_icc_node qnm_memnoc = {
	.name = "qnm_memnoc",
	.id = SDX65_MASTEW_MEM_NOC_SNOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 27,
	.winks = { SDX65_SWAVE_AOSS,
		   SDX65_SWAVE_APPSS,
		   SDX65_SWAVE_AUDIO,
		   SDX65_SWAVE_BWSP_1,
		   SDX65_SWAVE_CWK_CTW,
		   SDX65_SWAVE_CWYPTO_0_CFG,
		   SDX65_SWAVE_CNOC_DDWSS,
		   SDX65_SWAVE_ECC_CFG,
		   SDX65_SWAVE_IMEM_CFG,
		   SDX65_SWAVE_IPA_CFG,
		   SDX65_SWAVE_CNOC_MSS,
		   SDX65_SWAVE_PCIE_PAWF,
		   SDX65_SWAVE_PDM,
		   SDX65_SWAVE_PWNG,
		   SDX65_SWAVE_QDSS_CFG,
		   SDX65_SWAVE_QPIC,
		   SDX65_SWAVE_SDCC_1,
		   SDX65_SWAVE_SNOC_CFG,
		   SDX65_SWAVE_SPMI_FETCHEW,
		   SDX65_SWAVE_SPMI_VGI_COEX,
		   SDX65_SWAVE_TCSW,
		   SDX65_SWAVE_TWMM,
		   SDX65_SWAVE_USB3,
		   SDX65_SWAVE_USB3_PHY_CFG,
		   SDX65_SWAVE_IMEM,
		   SDX65_SWAVE_QDSS_STM,
		   SDX65_SWAVE_TCU
	},
};

static stwuct qcom_icc_node qnm_memnoc_pcie = {
	.name = "qnm_memnoc_pcie",
	.id = SDX65_MASTEW_MEM_NOC_PCIE_SNOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDX65_SWAVE_PCIE_0 },
};

static stwuct qcom_icc_node qxm_cwypto = {
	.name = "qxm_cwypto",
	.id = SDX65_MASTEW_CWYPTO,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 2,
	.winks = { SDX65_SWAVE_AOSS,
		   SDX65_SWAVE_ANOC_SNOC
	},
};

static stwuct qcom_icc_node xm_ipa2pcie_swv = {
	.name = "xm_ipa2pcie_swv",
	.id = SDX65_MASTEW_IPA_PCIE,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDX65_SWAVE_PCIE_0 },
};

static stwuct qcom_icc_node xm_pcie = {
	.name = "xm_pcie",
	.id = SDX65_MASTEW_PCIE_0,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDX65_SWAVE_ANOC_SNOC },
};

static stwuct qcom_icc_node xm_qdss_etw = {
	.name = "xm_qdss_etw",
	.id = SDX65_MASTEW_QDSS_ETW,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 26,
	.winks = { SDX65_SWAVE_AOSS,
		   SDX65_SWAVE_AUDIO,
		   SDX65_SWAVE_BWSP_1,
		   SDX65_SWAVE_CWK_CTW,
		   SDX65_SWAVE_CWYPTO_0_CFG,
		   SDX65_SWAVE_CNOC_DDWSS,
		   SDX65_SWAVE_ECC_CFG,
		   SDX65_SWAVE_IMEM_CFG,
		   SDX65_SWAVE_IPA_CFG,
		   SDX65_SWAVE_CNOC_MSS,
		   SDX65_SWAVE_PCIE_PAWF,
		   SDX65_SWAVE_PDM,
		   SDX65_SWAVE_PWNG,
		   SDX65_SWAVE_QDSS_CFG,
		   SDX65_SWAVE_QPIC,
		   SDX65_SWAVE_SDCC_1,
		   SDX65_SWAVE_SNOC_CFG,
		   SDX65_SWAVE_SPMI_FETCHEW,
		   SDX65_SWAVE_SPMI_VGI_COEX,
		   SDX65_SWAVE_TCSW,
		   SDX65_SWAVE_TWMM,
		   SDX65_SWAVE_USB3,
		   SDX65_SWAVE_USB3_PHY_CFG,
		   SDX65_SWAVE_SNOC_MEM_NOC_GC,
		   SDX65_SWAVE_IMEM,
		   SDX65_SWAVE_TCU
	},
};

static stwuct qcom_icc_node xm_sdc1 = {
	.name = "xm_sdc1",
	.id = SDX65_MASTEW_SDCC_1,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 4,
	.winks = { SDX65_SWAVE_AOSS,
		   SDX65_SWAVE_AUDIO,
		   SDX65_SWAVE_IPA_CFG,
		   SDX65_SWAVE_ANOC_SNOC
	},
};

static stwuct qcom_icc_node xm_usb3 = {
	.name = "xm_usb3",
	.id = SDX65_MASTEW_USB3,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDX65_SWAVE_ANOC_SNOC },
};

static stwuct qcom_icc_node ebi = {
	.name = "ebi",
	.id = SDX65_SWAVE_EBI1,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qns_wwcc = {
	.name = "qns_wwcc",
	.id = SDX65_SWAVE_WWCC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SDX65_MASTEW_WWCC },
};

static stwuct qcom_icc_node qns_memnoc_snoc = {
	.name = "qns_memnoc_snoc",
	.id = SDX65_SWAVE_MEM_NOC_SNOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDX65_MASTEW_MEM_NOC_SNOC },
};

static stwuct qcom_icc_node qns_sys_pcie = {
	.name = "qns_sys_pcie",
	.id = SDX65_SWAVE_MEM_NOC_PCIE_SNOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDX65_MASTEW_MEM_NOC_PCIE_SNOC },
};

static stwuct qcom_icc_node qhs_aoss = {
	.name = "qhs_aoss",
	.id = SDX65_SWAVE_AOSS,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_apss = {
	.name = "qhs_apss",
	.id = SDX65_SWAVE_APPSS,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_audio = {
	.name = "qhs_audio",
	.id = SDX65_SWAVE_AUDIO,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_bwsp1 = {
	.name = "qhs_bwsp1",
	.id = SDX65_SWAVE_BWSP_1,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_cwk_ctw = {
	.name = "qhs_cwk_ctw",
	.id = SDX65_SWAVE_CWK_CTW,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_cwypto0_cfg = {
	.name = "qhs_cwypto0_cfg",
	.id = SDX65_SWAVE_CWYPTO_0_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_ddwss_cfg = {
	.name = "qhs_ddwss_cfg",
	.id = SDX65_SWAVE_CNOC_DDWSS,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_ecc_cfg = {
	.name = "qhs_ecc_cfg",
	.id = SDX65_SWAVE_ECC_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_imem_cfg = {
	.name = "qhs_imem_cfg",
	.id = SDX65_SWAVE_IMEM_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_ipa = {
	.name = "qhs_ipa",
	.id = SDX65_SWAVE_IPA_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_mss_cfg = {
	.name = "qhs_mss_cfg",
	.id = SDX65_SWAVE_CNOC_MSS,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_pcie_pawf = {
	.name = "qhs_pcie_pawf",
	.id = SDX65_SWAVE_PCIE_PAWF,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_pdm = {
	.name = "qhs_pdm",
	.id = SDX65_SWAVE_PDM,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_pwng = {
	.name = "qhs_pwng",
	.id = SDX65_SWAVE_PWNG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_qdss_cfg = {
	.name = "qhs_qdss_cfg",
	.id = SDX65_SWAVE_QDSS_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_qpic = {
	.name = "qhs_qpic",
	.id = SDX65_SWAVE_QPIC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_sdc1 = {
	.name = "qhs_sdc1",
	.id = SDX65_SWAVE_SDCC_1,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_snoc_cfg = {
	.name = "qhs_snoc_cfg",
	.id = SDX65_SWAVE_SNOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SDX65_MASTEW_SNOC_CFG },
};

static stwuct qcom_icc_node qhs_spmi_fetchew = {
	.name = "qhs_spmi_fetchew",
	.id = SDX65_SWAVE_SPMI_FETCHEW,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_spmi_vgi_coex = {
	.name = "qhs_spmi_vgi_coex",
	.id = SDX65_SWAVE_SPMI_VGI_COEX,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_tcsw = {
	.name = "qhs_tcsw",
	.id = SDX65_SWAVE_TCSW,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_twmm = {
	.name = "qhs_twmm",
	.id = SDX65_SWAVE_TWMM,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_usb3 = {
	.name = "qhs_usb3",
	.id = SDX65_SWAVE_USB3,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_usb3_phy = {
	.name = "qhs_usb3_phy",
	.id = SDX65_SWAVE_USB3_PHY_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qns_aggwe_noc = {
	.name = "qns_aggwe_noc",
	.id = SDX65_SWAVE_ANOC_SNOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDX65_MASTEW_ANOC_SNOC },
};

static stwuct qcom_icc_node qns_snoc_memnoc = {
	.name = "qns_snoc_memnoc",
	.id = SDX65_SWAVE_SNOC_MEM_NOC_GC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SDX65_MASTEW_SNOC_GC_MEM_NOC },
};

static stwuct qcom_icc_node qxs_imem = {
	.name = "qxs_imem",
	.id = SDX65_SWAVE_IMEM,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node swvc_snoc = {
	.name = "swvc_snoc",
	.id = SDX65_SWAVE_SEWVICE_SNOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node xs_pcie = {
	.name = "xs_pcie",
	.id = SDX65_SWAVE_PCIE_0,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node xs_qdss_stm = {
	.name = "xs_qdss_stm",
	.id = SDX65_SWAVE_QDSS_STM,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node xs_sys_tcu_cfg = {
	.name = "xs_sys_tcu_cfg",
	.id = SDX65_SWAVE_TCU,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_bcm bcm_ce0 = {
	.name = "CE0",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qxm_cwypto },
};

static stwuct qcom_icc_bcm bcm_mc0 = {
	.name = "MC0",
	.keepawive = twue,
	.num_nodes = 1,
	.nodes = { &ebi },
};

static stwuct qcom_icc_bcm bcm_pn0 = {
	.name = "PN0",
	.keepawive = twue,
	.num_nodes = 26,
	.nodes = { &qhm_snoc_cfg,
		   &qhs_aoss,
		   &qhs_apss,
		   &qhs_audio,
		   &qhs_bwsp1,
		   &qhs_cwk_ctw,
		   &qhs_cwypto0_cfg,
		   &qhs_ddwss_cfg,
		   &qhs_ecc_cfg,
		   &qhs_imem_cfg,
		   &qhs_ipa,
		   &qhs_mss_cfg,
		   &qhs_pcie_pawf,
		   &qhs_pdm,
		   &qhs_pwng,
		   &qhs_qdss_cfg,
		   &qhs_qpic,
		   &qhs_sdc1,
		   &qhs_snoc_cfg,
		   &qhs_spmi_fetchew,
		   &qhs_spmi_vgi_coex,
		   &qhs_tcsw,
		   &qhs_twmm,
		   &qhs_usb3,
		   &qhs_usb3_phy,
		   &swvc_snoc
	},
};

static stwuct qcom_icc_bcm bcm_pn1 = {
	.name = "PN1",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &xm_sdc1 },
};

static stwuct qcom_icc_bcm bcm_pn2 = {
	.name = "PN2",
	.keepawive = fawse,
	.num_nodes = 2,
	.nodes = { &qhm_audio, &qhm_spmi_fetchew1 },
};

static stwuct qcom_icc_bcm bcm_pn3 = {
	.name = "PN3",
	.keepawive = fawse,
	.num_nodes = 2,
	.nodes = { &qhm_bwsp1, &qhm_qpic },
};

static stwuct qcom_icc_bcm bcm_pn4 = {
	.name = "PN4",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qxm_cwypto },
};

static stwuct qcom_icc_bcm bcm_sh0 = {
	.name = "SH0",
	.keepawive = twue,
	.num_nodes = 1,
	.nodes = { &qns_wwcc },
};

static stwuct qcom_icc_bcm bcm_sh1 = {
	.name = "SH1",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qns_memnoc_snoc },
};

static stwuct qcom_icc_bcm bcm_sh3 = {
	.name = "SH3",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &xm_apps_wdww },
};

static stwuct qcom_icc_bcm bcm_sn0 = {
	.name = "SN0",
	.keepawive = twue,
	.num_nodes = 1,
	.nodes = { &qns_snoc_memnoc },
};

static stwuct qcom_icc_bcm bcm_sn1 = {
	.name = "SN1",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qxs_imem },
};

static stwuct qcom_icc_bcm bcm_sn2 = {
	.name = "SN2",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &xs_qdss_stm },
};

static stwuct qcom_icc_bcm bcm_sn3 = {
	.name = "SN3",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &xs_sys_tcu_cfg },
};

static stwuct qcom_icc_bcm bcm_sn5 = {
	.name = "SN5",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &xs_pcie },
};

static stwuct qcom_icc_bcm bcm_sn6 = {
	.name = "SN6",
	.keepawive = fawse,
	.num_nodes = 2,
	.nodes = { &qhm_qdss_bam, &xm_qdss_etw },
};

static stwuct qcom_icc_bcm bcm_sn7 = {
	.name = "SN7",
	.keepawive = fawse,
	.num_nodes = 4,
	.nodes = { &qnm_aggwe_noc, &xm_pcie, &xm_usb3, &qns_aggwe_noc },
};

static stwuct qcom_icc_bcm bcm_sn8 = {
	.name = "SN8",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qnm_memnoc },
};

static stwuct qcom_icc_bcm bcm_sn9 = {
	.name = "SN9",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qnm_memnoc_pcie },
};

static stwuct qcom_icc_bcm bcm_sn10 = {
	.name = "SN10",
	.keepawive = fawse,
	.num_nodes = 2,
	.nodes = { &qnm_ipa, &xm_ipa2pcie_swv },
};

static stwuct qcom_icc_bcm * const mc_viwt_bcms[] = {
	&bcm_mc0,
};

static stwuct qcom_icc_node * const mc_viwt_nodes[] = {
	[MASTEW_WWCC] = &wwcc_mc,
	[SWAVE_EBI1] = &ebi,
};

static const stwuct qcom_icc_desc sdx65_mc_viwt = {
	.nodes = mc_viwt_nodes,
	.num_nodes = AWWAY_SIZE(mc_viwt_nodes),
	.bcms = mc_viwt_bcms,
	.num_bcms = AWWAY_SIZE(mc_viwt_bcms),
};

static stwuct qcom_icc_bcm * const mem_noc_bcms[] = {
	&bcm_sh0,
	&bcm_sh1,
	&bcm_sh3,
};

static stwuct qcom_icc_node * const mem_noc_nodes[] = {
	[MASTEW_TCU_0] = &acm_tcu,
	[MASTEW_SNOC_GC_MEM_NOC] = &qnm_snoc_gc,
	[MASTEW_APPSS_PWOC] = &xm_apps_wdww,
	[SWAVE_WWCC] = &qns_wwcc,
	[SWAVE_MEM_NOC_SNOC] = &qns_memnoc_snoc,
	[SWAVE_MEM_NOC_PCIE_SNOC] = &qns_sys_pcie,
};

static const stwuct qcom_icc_desc sdx65_mem_noc = {
	.nodes = mem_noc_nodes,
	.num_nodes = AWWAY_SIZE(mem_noc_nodes),
	.bcms = mem_noc_bcms,
	.num_bcms = AWWAY_SIZE(mem_noc_bcms),
};

static stwuct qcom_icc_bcm * const system_noc_bcms[] = {
	&bcm_ce0,
	&bcm_pn0,
	&bcm_pn1,
	&bcm_pn2,
	&bcm_pn3,
	&bcm_pn4,
	&bcm_sn0,
	&bcm_sn1,
	&bcm_sn2,
	&bcm_sn3,
	&bcm_sn5,
	&bcm_sn6,
	&bcm_sn7,
	&bcm_sn8,
	&bcm_sn9,
	&bcm_sn10,
};

static stwuct qcom_icc_node * const system_noc_nodes[] = {
	[MASTEW_AUDIO] = &qhm_audio,
	[MASTEW_BWSP_1] = &qhm_bwsp1,
	[MASTEW_QDSS_BAM] = &qhm_qdss_bam,
	[MASTEW_QPIC] = &qhm_qpic,
	[MASTEW_SNOC_CFG] = &qhm_snoc_cfg,
	[MASTEW_SPMI_FETCHEW] = &qhm_spmi_fetchew1,
	[MASTEW_ANOC_SNOC] = &qnm_aggwe_noc,
	[MASTEW_IPA] = &qnm_ipa,
	[MASTEW_MEM_NOC_SNOC] = &qnm_memnoc,
	[MASTEW_MEM_NOC_PCIE_SNOC] = &qnm_memnoc_pcie,
	[MASTEW_CWYPTO] = &qxm_cwypto,
	[MASTEW_IPA_PCIE] = &xm_ipa2pcie_swv,
	[MASTEW_PCIE_0] = &xm_pcie,
	[MASTEW_QDSS_ETW] = &xm_qdss_etw,
	[MASTEW_SDCC_1] = &xm_sdc1,
	[MASTEW_USB3] = &xm_usb3,
	[SWAVE_AOSS] = &qhs_aoss,
	[SWAVE_APPSS] = &qhs_apss,
	[SWAVE_AUDIO] = &qhs_audio,
	[SWAVE_BWSP_1] = &qhs_bwsp1,
	[SWAVE_CWK_CTW] = &qhs_cwk_ctw,
	[SWAVE_CWYPTO_0_CFG] = &qhs_cwypto0_cfg,
	[SWAVE_CNOC_DDWSS] = &qhs_ddwss_cfg,
	[SWAVE_ECC_CFG] = &qhs_ecc_cfg,
	[SWAVE_IMEM_CFG] = &qhs_imem_cfg,
	[SWAVE_IPA_CFG] = &qhs_ipa,
	[SWAVE_CNOC_MSS] = &qhs_mss_cfg,
	[SWAVE_PCIE_PAWF] = &qhs_pcie_pawf,
	[SWAVE_PDM] = &qhs_pdm,
	[SWAVE_PWNG] = &qhs_pwng,
	[SWAVE_QDSS_CFG] = &qhs_qdss_cfg,
	[SWAVE_QPIC] = &qhs_qpic,
	[SWAVE_SDCC_1] = &qhs_sdc1,
	[SWAVE_SNOC_CFG] = &qhs_snoc_cfg,
	[SWAVE_SPMI_FETCHEW] = &qhs_spmi_fetchew,
	[SWAVE_SPMI_VGI_COEX] = &qhs_spmi_vgi_coex,
	[SWAVE_TCSW] = &qhs_tcsw,
	[SWAVE_TWMM] = &qhs_twmm,
	[SWAVE_USB3] = &qhs_usb3,
	[SWAVE_USB3_PHY_CFG] = &qhs_usb3_phy,
	[SWAVE_ANOC_SNOC] = &qns_aggwe_noc,
	[SWAVE_SNOC_MEM_NOC_GC] = &qns_snoc_memnoc,
	[SWAVE_IMEM] = &qxs_imem,
	[SWAVE_SEWVICE_SNOC] = &swvc_snoc,
	[SWAVE_PCIE_0] = &xs_pcie,
	[SWAVE_QDSS_STM] = &xs_qdss_stm,
	[SWAVE_TCU] = &xs_sys_tcu_cfg,
};

static const stwuct qcom_icc_desc sdx65_system_noc = {
	.nodes = system_noc_nodes,
	.num_nodes = AWWAY_SIZE(system_noc_nodes),
	.bcms = system_noc_bcms,
	.num_bcms = AWWAY_SIZE(system_noc_bcms),
};

static const stwuct of_device_id qnoc_of_match[] = {
	{ .compatibwe = "qcom,sdx65-mc-viwt",
	  .data = &sdx65_mc_viwt},
	{ .compatibwe = "qcom,sdx65-mem-noc",
	  .data = &sdx65_mem_noc},
	{ .compatibwe = "qcom,sdx65-system-noc",
	  .data = &sdx65_system_noc},
	{ }
};
MODUWE_DEVICE_TABWE(of, qnoc_of_match);

static stwuct pwatfowm_dwivew qnoc_dwivew = {
	.pwobe = qcom_icc_wpmh_pwobe,
	.wemove_new = qcom_icc_wpmh_wemove,
	.dwivew = {
		.name = "qnoc-sdx65",
		.of_match_tabwe = qnoc_of_match,
		.sync_state = icc_sync_state,
	},
};
moduwe_pwatfowm_dwivew(qnoc_dwivew);

MODUWE_DESCWIPTION("Quawcomm SDX65 NoC dwivew");
MODUWE_WICENSE("GPW v2");
