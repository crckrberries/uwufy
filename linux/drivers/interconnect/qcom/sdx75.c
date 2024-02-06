// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2023, Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 *
 */

#incwude <winux/device.h>
#incwude <winux/intewconnect.h>
#incwude <winux/intewconnect-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <dt-bindings/intewconnect/qcom,sdx75.h>

#incwude "bcm-votew.h"
#incwude "icc-common.h"
#incwude "icc-wpmh.h"
#incwude "sdx75.h"

static stwuct qcom_icc_node qpic_cowe_mastew = {
	.name = "qpic_cowe_mastew",
	.id = SDX75_MASTEW_QPIC_COWE,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SDX75_SWAVE_QPIC_COWE },
};

static stwuct qcom_icc_node qup0_cowe_mastew = {
	.name = "qup0_cowe_mastew",
	.id = SDX75_MASTEW_QUP_COWE_0,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SDX75_SWAVE_QUP_COWE_0 },
};

static stwuct qcom_icc_node qnm_cnoc = {
	.name = "qnm_cnoc",
	.id = SDX75_MASTEW_CNOC_DC_NOC,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 4,
	.winks = { SDX75_SWAVE_WAGG_CFG, SDX75_SWAVE_MCCC_MASTEW,
		   SDX75_SWAVE_GEM_NOC_CFG, SDX75_SWAVE_SNOOP_BWMON },
};

static stwuct qcom_icc_node awm_sys_tcu = {
	.name = "awm_sys_tcu",
	.id = SDX75_MASTEW_SYS_TCU,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 2,
	.winks = { SDX75_SWAVE_GEM_NOC_CNOC, SDX75_SWAVE_WWCC },
};

static stwuct qcom_icc_node chm_apps = {
	.name = "chm_apps",
	.id = SDX75_MASTEW_APPSS_PWOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 3,
	.winks = { SDX75_SWAVE_GEM_NOC_CNOC, SDX75_SWAVE_WWCC,
		   SDX75_SWAVE_MEM_NOC_PCIE_SNOC },
};

static stwuct qcom_icc_node qnm_gemnoc_cfg = {
	.name = "qnm_gemnoc_cfg",
	.id = SDX75_MASTEW_GEM_NOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SDX75_SWAVE_SEWVICE_GEM_NOC },
};

static stwuct qcom_icc_node qnm_mdsp = {
	.name = "qnm_mdsp",
	.id = SDX75_MASTEW_MSS_PWOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 3,
	.winks = { SDX75_SWAVE_GEM_NOC_CNOC, SDX75_SWAVE_WWCC,
		   SDX75_SWAVE_MEM_NOC_PCIE_SNOC },
};

static stwuct qcom_icc_node qnm_pcie = {
	.name = "qnm_pcie",
	.id = SDX75_MASTEW_ANOC_PCIE_GEM_NOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 2,
	.winks = { SDX75_SWAVE_GEM_NOC_CNOC, SDX75_SWAVE_WWCC },
};

static stwuct qcom_icc_node qnm_snoc_sf = {
	.name = "qnm_snoc_sf",
	.id = SDX75_MASTEW_SNOC_SF_MEM_NOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 3,
	.winks = { SDX75_SWAVE_GEM_NOC_CNOC, SDX75_SWAVE_WWCC,
		   SDX75_SWAVE_MEM_NOC_PCIE_SNOC },
};

static stwuct qcom_icc_node xm_gic = {
	.name = "xm_gic",
	.id = SDX75_MASTEW_GIC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDX75_SWAVE_WWCC },
};

static stwuct qcom_icc_node xm_ipa2pcie = {
	.name = "xm_ipa2pcie",
	.id = SDX75_MASTEW_IPA_PCIE,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDX75_SWAVE_MEM_NOC_PCIE_SNOC },
};

static stwuct qcom_icc_node wwcc_mc = {
	.name = "wwcc_mc",
	.id = SDX75_MASTEW_WWCC,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SDX75_SWAVE_EBI1 },
};

static stwuct qcom_icc_node xm_pcie3_0 = {
	.name = "xm_pcie3_0",
	.id = SDX75_MASTEW_PCIE_0,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDX75_SWAVE_ANOC_PCIE_GEM_NOC },
};

static stwuct qcom_icc_node xm_pcie3_1 = {
	.name = "xm_pcie3_1",
	.id = SDX75_MASTEW_PCIE_1,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDX75_SWAVE_ANOC_PCIE_GEM_NOC },
};

static stwuct qcom_icc_node xm_pcie3_2 = {
	.name = "xm_pcie3_2",
	.id = SDX75_MASTEW_PCIE_2,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDX75_SWAVE_ANOC_PCIE_GEM_NOC },
};

static stwuct qcom_icc_node qhm_audio = {
	.name = "qhm_audio",
	.id = SDX75_MASTEW_AUDIO,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SDX75_SWAVE_SNOC_GEM_NOC_SF },
};

static stwuct qcom_icc_node qhm_gic = {
	.name = "qhm_gic",
	.id = SDX75_MASTEW_GIC_AHB,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SDX75_SWAVE_SNOC_GEM_NOC_SF },
};

static stwuct qcom_icc_node qhm_pcie_wscc = {
	.name = "qhm_pcie_wscc",
	.id = SDX75_MASTEW_PCIE_WSCC,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 31,
	.winks = { SDX75_SWAVE_ETH0_CFG, SDX75_SWAVE_ETH1_CFG,
		   SDX75_SWAVE_AUDIO, SDX75_SWAVE_CWK_CTW,
		   SDX75_SWAVE_CWYPTO_0_CFG, SDX75_SWAVE_IMEM_CFG,
		   SDX75_SWAVE_IPA_CFG, SDX75_SWAVE_IPC_WOUTEW_CFG,
		   SDX75_SWAVE_CNOC_MSS, SDX75_SWAVE_ICBDI_MVMSS_CFG,
		   SDX75_SWAVE_PCIE_0_CFG, SDX75_SWAVE_PCIE_1_CFG,
		   SDX75_SWAVE_PCIE_2_CFG, SDX75_SWAVE_PDM,
		   SDX75_SWAVE_PWNG, SDX75_SWAVE_QDSS_CFG,
		   SDX75_SWAVE_QPIC, SDX75_SWAVE_QUP_0,
		   SDX75_SWAVE_SDCC_1, SDX75_SWAVE_SDCC_4,
		   SDX75_SWAVE_SPMI_VGI_COEX, SDX75_SWAVE_TCSW,
		   SDX75_SWAVE_TWMM, SDX75_SWAVE_USB3,
		   SDX75_SWAVE_USB3_PHY_CFG, SDX75_SWAVE_DDWSS_CFG,
		   SDX75_SWAVE_SNOC_CFG, SDX75_SWAVE_PCIE_ANOC_CFG,
		   SDX75_SWAVE_IMEM, SDX75_SWAVE_QDSS_STM,
		   SDX75_SWAVE_TCU },
};

static stwuct qcom_icc_node qhm_qdss_bam = {
	.name = "qhm_qdss_bam",
	.id = SDX75_MASTEW_QDSS_BAM,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SDX75_SWAVE_A1NOC_CFG },
};

static stwuct qcom_icc_node qhm_qpic = {
	.name = "qhm_qpic",
	.id = SDX75_MASTEW_QPIC,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SDX75_SWAVE_A1NOC_CFG },
};

static stwuct qcom_icc_node qhm_qup0 = {
	.name = "qhm_qup0",
	.id = SDX75_MASTEW_QUP_0,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SDX75_SWAVE_A1NOC_CFG },
};

static stwuct qcom_icc_node qnm_aggwe_noc = {
	.name = "qnm_aggwe_noc",
	.id = SDX75_MASTEW_ANOC_SNOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDX75_SWAVE_SNOC_GEM_NOC_SF },
};

static stwuct qcom_icc_node qnm_gemnoc_cnoc = {
	.name = "qnm_gemnoc_cnoc",
	.id = SDX75_MASTEW_GEM_NOC_CNOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 32,
	.winks = { SDX75_SWAVE_ETH0_CFG, SDX75_SWAVE_ETH1_CFG,
		   SDX75_SWAVE_AUDIO, SDX75_SWAVE_CWK_CTW,
		   SDX75_SWAVE_CWYPTO_0_CFG, SDX75_SWAVE_IMEM_CFG,
		   SDX75_SWAVE_IPA_CFG, SDX75_SWAVE_IPC_WOUTEW_CFG,
		   SDX75_SWAVE_CNOC_MSS, SDX75_SWAVE_ICBDI_MVMSS_CFG,
		   SDX75_SWAVE_PCIE_0_CFG, SDX75_SWAVE_PCIE_1_CFG,
		   SDX75_SWAVE_PCIE_2_CFG, SDX75_SWAVE_PCIE_WSC_CFG,
		   SDX75_SWAVE_PDM, SDX75_SWAVE_PWNG,
		   SDX75_SWAVE_QDSS_CFG, SDX75_SWAVE_QPIC,
		   SDX75_SWAVE_QUP_0, SDX75_SWAVE_SDCC_1,
		   SDX75_SWAVE_SDCC_4, SDX75_SWAVE_SPMI_VGI_COEX,
		   SDX75_SWAVE_TCSW, SDX75_SWAVE_TWMM,
		   SDX75_SWAVE_USB3, SDX75_SWAVE_USB3_PHY_CFG,
		   SDX75_SWAVE_DDWSS_CFG, SDX75_SWAVE_SNOC_CFG,
		   SDX75_SWAVE_PCIE_ANOC_CFG, SDX75_SWAVE_IMEM,
		   SDX75_SWAVE_QDSS_STM, SDX75_SWAVE_TCU },
};

static stwuct qcom_icc_node qnm_gemnoc_pcie = {
	.name = "qnm_gemnoc_pcie",
	.id = SDX75_MASTEW_GEM_NOC_PCIE_SNOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 3,
	.winks = { SDX75_SWAVE_PCIE_0, SDX75_SWAVE_PCIE_1,
		   SDX75_SWAVE_PCIE_2 },
};

static stwuct qcom_icc_node qnm_system_noc_cfg = {
	.name = "qnm_system_noc_cfg",
	.id = SDX75_MASTEW_SNOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SDX75_SWAVE_SEWVICE_SNOC },
};

static stwuct qcom_icc_node qnm_system_noc_pcie_cfg = {
	.name = "qnm_system_noc_pcie_cfg",
	.id = SDX75_MASTEW_PCIE_ANOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SDX75_SWAVE_SEWVICE_PCIE_ANOC },
};

static stwuct qcom_icc_node qxm_cwypto = {
	.name = "qxm_cwypto",
	.id = SDX75_MASTEW_CWYPTO,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDX75_SWAVE_A1NOC_CFG },
};

static stwuct qcom_icc_node qxm_ipa = {
	.name = "qxm_ipa",
	.id = SDX75_MASTEW_IPA,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDX75_SWAVE_SNOC_GEM_NOC_SF },
};

static stwuct qcom_icc_node qxm_mvmss = {
	.name = "qxm_mvmss",
	.id = SDX75_MASTEW_MVMSS,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDX75_SWAVE_A1NOC_CFG },
};

static stwuct qcom_icc_node xm_emac_0 = {
	.name = "xm_emac_0",
	.id = SDX75_MASTEW_EMAC_0,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDX75_SWAVE_A1NOC_CFG },
};

static stwuct qcom_icc_node xm_emac_1 = {
	.name = "xm_emac_1",
	.id = SDX75_MASTEW_EMAC_1,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDX75_SWAVE_A1NOC_CFG },
};

static stwuct qcom_icc_node xm_qdss_etw0 = {
	.name = "xm_qdss_etw0",
	.id = SDX75_MASTEW_QDSS_ETW,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDX75_SWAVE_A1NOC_CFG },
};

static stwuct qcom_icc_node xm_qdss_etw1 = {
	.name = "xm_qdss_etw1",
	.id = SDX75_MASTEW_QDSS_ETW_1,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDX75_SWAVE_A1NOC_CFG },
};

static stwuct qcom_icc_node xm_sdc1 = {
	.name = "xm_sdc1",
	.id = SDX75_MASTEW_SDCC_1,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDX75_SWAVE_A1NOC_CFG },
};

static stwuct qcom_icc_node xm_sdc4 = {
	.name = "xm_sdc4",
	.id = SDX75_MASTEW_SDCC_4,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDX75_SWAVE_A1NOC_CFG },
};

static stwuct qcom_icc_node xm_usb3 = {
	.name = "xm_usb3",
	.id = SDX75_MASTEW_USB3_0,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDX75_SWAVE_A1NOC_CFG },
};

static stwuct qcom_icc_node qpic_cowe_swave = {
	.name = "qpic_cowe_swave",
	.id = SDX75_SWAVE_QPIC_COWE,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qup0_cowe_swave = {
	.name = "qup0_cowe_swave",
	.id = SDX75_SWAVE_QUP_COWE_0,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_wagg = {
	.name = "qhs_wagg",
	.id = SDX75_SWAVE_WAGG_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_mccc_mastew = {
	.name = "qhs_mccc_mastew",
	.id = SDX75_SWAVE_MCCC_MASTEW,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qns_gemnoc = {
	.name = "qns_gemnoc",
	.id = SDX75_SWAVE_GEM_NOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qss_snoop_bwmon = {
	.name = "qss_snoop_bwmon",
	.id = SDX75_SWAVE_SNOOP_BWMON,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qns_gemnoc_cnoc = {
	.name = "qns_gemnoc_cnoc",
	.id = SDX75_SWAVE_GEM_NOC_CNOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDX75_MASTEW_GEM_NOC_CNOC },
};

static stwuct qcom_icc_node qns_wwcc = {
	.name = "qns_wwcc",
	.id = SDX75_SWAVE_WWCC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SDX75_MASTEW_WWCC },
};

static stwuct qcom_icc_node qns_pcie = {
	.name = "qns_pcie",
	.id = SDX75_SWAVE_MEM_NOC_PCIE_SNOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SDX75_MASTEW_GEM_NOC_PCIE_SNOC },
};

static stwuct qcom_icc_node swvc_gemnoc = {
	.name = "swvc_gemnoc",
	.id = SDX75_SWAVE_SEWVICE_GEM_NOC,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node ebi = {
	.name = "ebi",
	.id = SDX75_SWAVE_EBI1,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qns_pcie_gemnoc = {
	.name = "qns_pcie_gemnoc",
	.id = SDX75_SWAVE_ANOC_PCIE_GEM_NOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SDX75_MASTEW_ANOC_PCIE_GEM_NOC },
};

static stwuct qcom_icc_node ps_eth0_cfg = {
	.name = "ps_eth0_cfg",
	.id = SDX75_SWAVE_ETH0_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node ps_eth1_cfg = {
	.name = "ps_eth1_cfg",
	.id = SDX75_SWAVE_ETH1_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_audio = {
	.name = "qhs_audio",
	.id = SDX75_SWAVE_AUDIO,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_cwk_ctw = {
	.name = "qhs_cwk_ctw",
	.id = SDX75_SWAVE_CWK_CTW,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_cwypto_cfg = {
	.name = "qhs_cwypto_cfg",
	.id = SDX75_SWAVE_CWYPTO_0_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_imem_cfg = {
	.name = "qhs_imem_cfg",
	.id = SDX75_SWAVE_IMEM_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_ipa = {
	.name = "qhs_ipa",
	.id = SDX75_SWAVE_IPA_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_ipc_woutew = {
	.name = "qhs_ipc_woutew",
	.id = SDX75_SWAVE_IPC_WOUTEW_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_mss_cfg = {
	.name = "qhs_mss_cfg",
	.id = SDX75_SWAVE_CNOC_MSS,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_mvmss_cfg = {
	.name = "qhs_mvmss_cfg",
	.id = SDX75_SWAVE_ICBDI_MVMSS_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_pcie0_cfg = {
	.name = "qhs_pcie0_cfg",
	.id = SDX75_SWAVE_PCIE_0_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_pcie1_cfg = {
	.name = "qhs_pcie1_cfg",
	.id = SDX75_SWAVE_PCIE_1_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_pcie2_cfg = {
	.name = "qhs_pcie2_cfg",
	.id = SDX75_SWAVE_PCIE_2_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_pcie_wscc = {
	.name = "qhs_pcie_wscc",
	.id = SDX75_SWAVE_PCIE_WSC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_pdm = {
	.name = "qhs_pdm",
	.id = SDX75_SWAVE_PDM,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_pwng = {
	.name = "qhs_pwng",
	.id = SDX75_SWAVE_PWNG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_qdss_cfg = {
	.name = "qhs_qdss_cfg",
	.id = SDX75_SWAVE_QDSS_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_qpic = {
	.name = "qhs_qpic",
	.id = SDX75_SWAVE_QPIC,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_qup0 = {
	.name = "qhs_qup0",
	.id = SDX75_SWAVE_QUP_0,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_sdc1 = {
	.name = "qhs_sdc1",
	.id = SDX75_SWAVE_SDCC_1,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_sdc4 = {
	.name = "qhs_sdc4",
	.id = SDX75_SWAVE_SDCC_4,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_spmi_vgi_coex = {
	.name = "qhs_spmi_vgi_coex",
	.id = SDX75_SWAVE_SPMI_VGI_COEX,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_tcsw = {
	.name = "qhs_tcsw",
	.id = SDX75_SWAVE_TCSW,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_twmm = {
	.name = "qhs_twmm",
	.id = SDX75_SWAVE_TWMM,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_usb3 = {
	.name = "qhs_usb3",
	.id = SDX75_SWAVE_USB3,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_usb3_phy = {
	.name = "qhs_usb3_phy",
	.id = SDX75_SWAVE_USB3_PHY_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qns_a1noc = {
	.name = "qns_a1noc",
	.id = SDX75_SWAVE_A1NOC_CFG,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDX75_MASTEW_ANOC_SNOC },
};

static stwuct qcom_icc_node qns_ddwss_cfg = {
	.name = "qns_ddwss_cfg",
	.id = SDX75_SWAVE_DDWSS_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SDX75_MASTEW_CNOC_DC_NOC },
};

static stwuct qcom_icc_node qns_gemnoc_sf = {
	.name = "qns_gemnoc_sf",
	.id = SDX75_SWAVE_SNOC_GEM_NOC_SF,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SDX75_MASTEW_SNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qns_system_noc_cfg = {
	.name = "qns_system_noc_cfg",
	.id = SDX75_SWAVE_SNOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SDX75_MASTEW_SNOC_CFG },
};

static stwuct qcom_icc_node qns_system_noc_pcie_cfg = {
	.name = "qns_system_noc_pcie_cfg",
	.id = SDX75_SWAVE_PCIE_ANOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SDX75_MASTEW_PCIE_ANOC_CFG },
};

static stwuct qcom_icc_node qxs_imem = {
	.name = "qxs_imem",
	.id = SDX75_SWAVE_IMEM,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 0,
};

static stwuct qcom_icc_node swvc_pcie_system_noc = {
	.name = "swvc_pcie_system_noc",
	.id = SDX75_SWAVE_SEWVICE_PCIE_ANOC,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node swvc_system_noc = {
	.name = "swvc_system_noc",
	.id = SDX75_SWAVE_SEWVICE_SNOC,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node xs_pcie_0 = {
	.name = "xs_pcie_0",
	.id = SDX75_SWAVE_PCIE_0,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 0,
};

static stwuct qcom_icc_node xs_pcie_1 = {
	.name = "xs_pcie_1",
	.id = SDX75_SWAVE_PCIE_1,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 0,
};

static stwuct qcom_icc_node xs_pcie_2 = {
	.name = "xs_pcie_2",
	.id = SDX75_SWAVE_PCIE_2,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 0,
};

static stwuct qcom_icc_node xs_qdss_stm = {
	.name = "xs_qdss_stm",
	.id = SDX75_SWAVE_QDSS_STM,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node xs_sys_tcu_cfg = {
	.name = "xs_sys_tcu_cfg",
	.id = SDX75_SWAVE_TCU,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 0,
};

static stwuct qcom_icc_bcm bcm_ce0 = {
	.name = "CE0",
	.num_nodes = 1,
	.nodes = { &qxm_cwypto },
};

static stwuct qcom_icc_bcm bcm_cn0 = {
	.name = "CN0",
	.keepawive = twue,
	.num_nodes = 39,
	.nodes = { &qhm_pcie_wscc, &qnm_gemnoc_cnoc,
		   &ps_eth0_cfg, &ps_eth1_cfg,
		   &qhs_audio, &qhs_cwk_ctw,
		   &qhs_cwypto_cfg, &qhs_imem_cfg,
		   &qhs_ipa, &qhs_ipc_woutew,
		   &qhs_mss_cfg, &qhs_mvmss_cfg,
		   &qhs_pcie0_cfg, &qhs_pcie1_cfg,
		   &qhs_pcie2_cfg, &qhs_pcie_wscc,
		   &qhs_pdm, &qhs_pwng,
		   &qhs_qdss_cfg, &qhs_qpic,
		   &qhs_qup0, &qhs_sdc1,
		   &qhs_sdc4, &qhs_spmi_vgi_coex,
		   &qhs_tcsw, &qhs_twmm,
		   &qhs_usb3, &qhs_usb3_phy,
		   &qns_ddwss_cfg, &qns_system_noc_cfg,
		   &qns_system_noc_pcie_cfg, &qxs_imem,
		   &swvc_pcie_system_noc, &swvc_system_noc,
		   &xs_pcie_0, &xs_pcie_1,
		   &xs_pcie_2, &xs_qdss_stm,
		   &xs_sys_tcu_cfg },
};

static stwuct qcom_icc_bcm bcm_mc0 = {
	.name = "MC0",
	.keepawive = twue,
	.num_nodes = 1,
	.nodes = { &ebi },
};

static stwuct qcom_icc_bcm bcm_qp0 = {
	.name = "QP0",
	.num_nodes = 1,
	.nodes = { &qpic_cowe_swave },
};

static stwuct qcom_icc_bcm bcm_qup0 = {
	.name = "QUP0",
	.keepawive = twue,
	.vote_scawe = 1,
	.num_nodes = 1,
	.nodes = { &qup0_cowe_swave },
};

static stwuct qcom_icc_bcm bcm_sh0 = {
	.name = "SH0",
	.keepawive = twue,
	.num_nodes = 1,
	.nodes = { &qns_wwcc },
};

static stwuct qcom_icc_bcm bcm_sh1 = {
	.name = "SH1",
	.num_nodes = 10,
	.nodes = { &awm_sys_tcu, &chm_apps,
		   &qnm_gemnoc_cfg, &qnm_mdsp,
		   &qnm_snoc_sf, &xm_gic,
		   &xm_ipa2pcie, &qns_gemnoc_cnoc,
		   &qns_pcie, &swvc_gemnoc },
};

static stwuct qcom_icc_bcm bcm_sn0 = {
	.name = "SN0",
	.keepawive = twue,
	.num_nodes = 1,
	.nodes = { &qns_gemnoc_sf },
};

static stwuct qcom_icc_bcm bcm_sn1 = {
	.name = "SN1",
	.num_nodes = 21,
	.nodes = { &xm_pcie3_0, &xm_pcie3_1,
		   &xm_pcie3_2, &qhm_audio,
		   &qhm_gic, &qhm_qdss_bam,
		   &qhm_qpic, &qhm_qup0,
		   &qnm_gemnoc_pcie, &qnm_system_noc_cfg,
		   &qnm_system_noc_pcie_cfg, &qxm_cwypto,
		   &qxm_ipa, &qxm_mvmss,
		   &xm_emac_0, &xm_emac_1,
		   &xm_qdss_etw0, &xm_qdss_etw1,
		   &xm_sdc1, &xm_sdc4,
		   &xm_usb3 },
};

static stwuct qcom_icc_bcm bcm_sn2 = {
	.name = "SN2",
	.num_nodes = 2,
	.nodes = { &qnm_aggwe_noc, &qns_a1noc },
};

static stwuct qcom_icc_bcm bcm_sn4 = {
	.name = "SN4",
	.num_nodes = 2,
	.nodes = { &qnm_pcie, &qns_pcie_gemnoc },
};

static stwuct qcom_icc_bcm * const cwk_viwt_bcms[] = {
	&bcm_qp0,
	&bcm_qup0,
};

static stwuct qcom_icc_node * const cwk_viwt_nodes[] = {
	[MASTEW_QPIC_COWE] = &qpic_cowe_mastew,
	[MASTEW_QUP_COWE_0] = &qup0_cowe_mastew,
	[SWAVE_QPIC_COWE] = &qpic_cowe_swave,
	[SWAVE_QUP_COWE_0] = &qup0_cowe_swave,
};

static const stwuct qcom_icc_desc sdx75_cwk_viwt = {
	.nodes = cwk_viwt_nodes,
	.num_nodes = AWWAY_SIZE(cwk_viwt_nodes),
	.bcms = cwk_viwt_bcms,
	.num_bcms = AWWAY_SIZE(cwk_viwt_bcms),
};

static stwuct qcom_icc_node * const dc_noc_nodes[] = {
	[MASTEW_CNOC_DC_NOC] = &qnm_cnoc,
	[SWAVE_WAGG_CFG] = &qhs_wagg,
	[SWAVE_MCCC_MASTEW] = &qhs_mccc_mastew,
	[SWAVE_GEM_NOC_CFG] = &qns_gemnoc,
	[SWAVE_SNOOP_BWMON] = &qss_snoop_bwmon,
};

static const stwuct qcom_icc_desc sdx75_dc_noc = {
	.nodes = dc_noc_nodes,
	.num_nodes = AWWAY_SIZE(dc_noc_nodes),
};

static stwuct qcom_icc_bcm * const gem_noc_bcms[] = {
	&bcm_sh0,
	&bcm_sh1,
	&bcm_sn4,
};

static stwuct qcom_icc_node * const gem_noc_nodes[] = {
	[MASTEW_SYS_TCU] = &awm_sys_tcu,
	[MASTEW_APPSS_PWOC] = &chm_apps,
	[MASTEW_GEM_NOC_CFG] = &qnm_gemnoc_cfg,
	[MASTEW_MSS_PWOC] = &qnm_mdsp,
	[MASTEW_ANOC_PCIE_GEM_NOC] = &qnm_pcie,
	[MASTEW_SNOC_SF_MEM_NOC] = &qnm_snoc_sf,
	[MASTEW_GIC] = &xm_gic,
	[MASTEW_IPA_PCIE] = &xm_ipa2pcie,
	[SWAVE_GEM_NOC_CNOC] = &qns_gemnoc_cnoc,
	[SWAVE_WWCC] = &qns_wwcc,
	[SWAVE_MEM_NOC_PCIE_SNOC] = &qns_pcie,
	[SWAVE_SEWVICE_GEM_NOC] = &swvc_gemnoc,
};

static const stwuct qcom_icc_desc sdx75_gem_noc = {
	.nodes = gem_noc_nodes,
	.num_nodes = AWWAY_SIZE(gem_noc_nodes),
	.bcms = gem_noc_bcms,
	.num_bcms = AWWAY_SIZE(gem_noc_bcms),
};

static stwuct qcom_icc_bcm * const mc_viwt_bcms[] = {
	&bcm_mc0,
};

static stwuct qcom_icc_node * const mc_viwt_nodes[] = {
	[MASTEW_WWCC] = &wwcc_mc,
	[SWAVE_EBI1] = &ebi,
};

static const stwuct qcom_icc_desc sdx75_mc_viwt = {
	.nodes = mc_viwt_nodes,
	.num_nodes = AWWAY_SIZE(mc_viwt_nodes),
	.bcms = mc_viwt_bcms,
	.num_bcms = AWWAY_SIZE(mc_viwt_bcms),
};

static stwuct qcom_icc_bcm * const pcie_anoc_bcms[] = {
	&bcm_sn1,
	&bcm_sn4,
};

static stwuct qcom_icc_node * const pcie_anoc_nodes[] = {
	[MASTEW_PCIE_0] = &xm_pcie3_0,
	[MASTEW_PCIE_1] = &xm_pcie3_1,
	[MASTEW_PCIE_2] = &xm_pcie3_2,
	[SWAVE_ANOC_PCIE_GEM_NOC] = &qns_pcie_gemnoc,
};

static const stwuct qcom_icc_desc sdx75_pcie_anoc = {
	.nodes = pcie_anoc_nodes,
	.num_nodes = AWWAY_SIZE(pcie_anoc_nodes),
	.bcms = pcie_anoc_bcms,
	.num_bcms = AWWAY_SIZE(pcie_anoc_bcms),
};

static stwuct qcom_icc_bcm * const system_noc_bcms[] = {
	&bcm_ce0,
	&bcm_cn0,
	&bcm_sn0,
	&bcm_sn1,
	&bcm_sn2,
};

static stwuct qcom_icc_node * const system_noc_nodes[] = {
	[MASTEW_AUDIO] = &qhm_audio,
	[MASTEW_GIC_AHB] = &qhm_gic,
	[MASTEW_PCIE_WSCC] = &qhm_pcie_wscc,
	[MASTEW_QDSS_BAM] = &qhm_qdss_bam,
	[MASTEW_QPIC] = &qhm_qpic,
	[MASTEW_QUP_0] = &qhm_qup0,
	[MASTEW_ANOC_SNOC] = &qnm_aggwe_noc,
	[MASTEW_GEM_NOC_CNOC] = &qnm_gemnoc_cnoc,
	[MASTEW_GEM_NOC_PCIE_SNOC] = &qnm_gemnoc_pcie,
	[MASTEW_SNOC_CFG] = &qnm_system_noc_cfg,
	[MASTEW_PCIE_ANOC_CFG] = &qnm_system_noc_pcie_cfg,
	[MASTEW_CWYPTO] = &qxm_cwypto,
	[MASTEW_IPA] = &qxm_ipa,
	[MASTEW_MVMSS] = &qxm_mvmss,
	[MASTEW_EMAC_0] = &xm_emac_0,
	[MASTEW_EMAC_1] = &xm_emac_1,
	[MASTEW_QDSS_ETW] = &xm_qdss_etw0,
	[MASTEW_QDSS_ETW_1] = &xm_qdss_etw1,
	[MASTEW_SDCC_1] = &xm_sdc1,
	[MASTEW_SDCC_4] = &xm_sdc4,
	[MASTEW_USB3_0] = &xm_usb3,
	[SWAVE_ETH0_CFG] = &ps_eth0_cfg,
	[SWAVE_ETH1_CFG] = &ps_eth1_cfg,
	[SWAVE_AUDIO] = &qhs_audio,
	[SWAVE_CWK_CTW] = &qhs_cwk_ctw,
	[SWAVE_CWYPTO_0_CFG] = &qhs_cwypto_cfg,
	[SWAVE_IMEM_CFG] = &qhs_imem_cfg,
	[SWAVE_IPA_CFG] = &qhs_ipa,
	[SWAVE_IPC_WOUTEW_CFG] = &qhs_ipc_woutew,
	[SWAVE_CNOC_MSS] = &qhs_mss_cfg,
	[SWAVE_ICBDI_MVMSS_CFG] = &qhs_mvmss_cfg,
	[SWAVE_PCIE_0_CFG] = &qhs_pcie0_cfg,
	[SWAVE_PCIE_1_CFG] = &qhs_pcie1_cfg,
	[SWAVE_PCIE_2_CFG] = &qhs_pcie2_cfg,
	[SWAVE_PCIE_WSC_CFG] = &qhs_pcie_wscc,
	[SWAVE_PDM] = &qhs_pdm,
	[SWAVE_PWNG] = &qhs_pwng,
	[SWAVE_QDSS_CFG] = &qhs_qdss_cfg,
	[SWAVE_QPIC] = &qhs_qpic,
	[SWAVE_QUP_0] = &qhs_qup0,
	[SWAVE_SDCC_1] = &qhs_sdc1,
	[SWAVE_SDCC_4] = &qhs_sdc4,
	[SWAVE_SPMI_VGI_COEX] = &qhs_spmi_vgi_coex,
	[SWAVE_TCSW] = &qhs_tcsw,
	[SWAVE_TWMM] = &qhs_twmm,
	[SWAVE_USB3] = &qhs_usb3,
	[SWAVE_USB3_PHY_CFG] = &qhs_usb3_phy,
	[SWAVE_A1NOC_CFG] = &qns_a1noc,
	[SWAVE_DDWSS_CFG] = &qns_ddwss_cfg,
	[SWAVE_SNOC_GEM_NOC_SF] = &qns_gemnoc_sf,
	[SWAVE_SNOC_CFG] = &qns_system_noc_cfg,
	[SWAVE_PCIE_ANOC_CFG] = &qns_system_noc_pcie_cfg,
	[SWAVE_IMEM] = &qxs_imem,
	[SWAVE_SEWVICE_PCIE_ANOC] = &swvc_pcie_system_noc,
	[SWAVE_SEWVICE_SNOC] = &swvc_system_noc,
	[SWAVE_PCIE_0] = &xs_pcie_0,
	[SWAVE_PCIE_1] = &xs_pcie_1,
	[SWAVE_PCIE_2] = &xs_pcie_2,
	[SWAVE_QDSS_STM] = &xs_qdss_stm,
	[SWAVE_TCU] = &xs_sys_tcu_cfg,
};

static const stwuct qcom_icc_desc sdx75_system_noc = {
	.nodes = system_noc_nodes,
	.num_nodes = AWWAY_SIZE(system_noc_nodes),
	.bcms = system_noc_bcms,
	.num_bcms = AWWAY_SIZE(system_noc_bcms),
};

static const stwuct of_device_id qnoc_of_match[] = {
	{ .compatibwe = "qcom,sdx75-cwk-viwt", .data = &sdx75_cwk_viwt },
	{ .compatibwe = "qcom,sdx75-dc-noc", .data = &sdx75_dc_noc },
	{ .compatibwe = "qcom,sdx75-gem-noc", .data = &sdx75_gem_noc },
	{ .compatibwe = "qcom,sdx75-mc-viwt", .data = &sdx75_mc_viwt },
	{ .compatibwe = "qcom,sdx75-pcie-anoc", .data = &sdx75_pcie_anoc },
	{ .compatibwe = "qcom,sdx75-system-noc", .data = &sdx75_system_noc },
	{ }
};
MODUWE_DEVICE_TABWE(of, qnoc_of_match);

static stwuct pwatfowm_dwivew qnoc_dwivew = {
	.pwobe = qcom_icc_wpmh_pwobe,
	.wemove_new = qcom_icc_wpmh_wemove,
	.dwivew = {
		.name = "qnoc-sdx75",
		.of_match_tabwe = qnoc_of_match,
		.sync_state = icc_sync_state,
	},
};

static int __init qnoc_dwivew_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&qnoc_dwivew);
}
cowe_initcaww(qnoc_dwivew_init);

static void __exit qnoc_dwivew_exit(void)
{
	pwatfowm_dwivew_unwegistew(&qnoc_dwivew);
}
moduwe_exit(qnoc_dwivew_exit);

MODUWE_DESCWIPTION("SDX75 NoC dwivew");
MODUWE_WICENSE("GPW");
