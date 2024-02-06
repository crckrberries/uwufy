// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018-2020, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/device.h>
#incwude <winux/intewconnect.h>
#incwude <winux/intewconnect-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude <dt-bindings/intewconnect/qcom,sdm845.h>

#incwude "bcm-votew.h"
#incwude "icc-wpmh.h"
#incwude "sdm845.h"

static stwuct qcom_icc_node qhm_a1noc_cfg = {
	.name = "qhm_a1noc_cfg",
	.id = SDM845_MASTEW_A1NOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SDM845_SWAVE_SEWVICE_A1NOC },
};

static stwuct qcom_icc_node qhm_qup1 = {
	.name = "qhm_qup1",
	.id = SDM845_MASTEW_BWSP_1,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SDM845_SWAVE_A1NOC_SNOC },
};

static stwuct qcom_icc_node qhm_tsif = {
	.name = "qhm_tsif",
	.id = SDM845_MASTEW_TSIF,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SDM845_SWAVE_A1NOC_SNOC },
};

static stwuct qcom_icc_node xm_sdc2 = {
	.name = "xm_sdc2",
	.id = SDM845_MASTEW_SDCC_2,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDM845_SWAVE_A1NOC_SNOC },
};

static stwuct qcom_icc_node xm_sdc4 = {
	.name = "xm_sdc4",
	.id = SDM845_MASTEW_SDCC_4,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDM845_SWAVE_A1NOC_SNOC },
};

static stwuct qcom_icc_node xm_ufs_cawd = {
	.name = "xm_ufs_cawd",
	.id = SDM845_MASTEW_UFS_CAWD,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDM845_SWAVE_A1NOC_SNOC },
};

static stwuct qcom_icc_node xm_ufs_mem = {
	.name = "xm_ufs_mem",
	.id = SDM845_MASTEW_UFS_MEM,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDM845_SWAVE_A1NOC_SNOC },
};

static stwuct qcom_icc_node xm_pcie_0 = {
	.name = "xm_pcie_0",
	.id = SDM845_MASTEW_PCIE_0,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDM845_SWAVE_ANOC_PCIE_A1NOC_SNOC },
};

static stwuct qcom_icc_node qhm_a2noc_cfg = {
	.name = "qhm_a2noc_cfg",
	.id = SDM845_MASTEW_A2NOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SDM845_SWAVE_SEWVICE_A2NOC },
};

static stwuct qcom_icc_node qhm_qdss_bam = {
	.name = "qhm_qdss_bam",
	.id = SDM845_MASTEW_QDSS_BAM,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SDM845_SWAVE_A2NOC_SNOC },
};

static stwuct qcom_icc_node qhm_qup2 = {
	.name = "qhm_qup2",
	.id = SDM845_MASTEW_BWSP_2,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SDM845_SWAVE_A2NOC_SNOC },
};

static stwuct qcom_icc_node qnm_cnoc = {
	.name = "qnm_cnoc",
	.id = SDM845_MASTEW_CNOC_A2NOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDM845_SWAVE_A2NOC_SNOC },
};

static stwuct qcom_icc_node qxm_cwypto = {
	.name = "qxm_cwypto",
	.id = SDM845_MASTEW_CWYPTO,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDM845_SWAVE_A2NOC_SNOC },
};

static stwuct qcom_icc_node qxm_ipa = {
	.name = "qxm_ipa",
	.id = SDM845_MASTEW_IPA,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDM845_SWAVE_A2NOC_SNOC },
};

static stwuct qcom_icc_node xm_pcie3_1 = {
	.name = "xm_pcie3_1",
	.id = SDM845_MASTEW_PCIE_1,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDM845_SWAVE_ANOC_PCIE_SNOC },
};

static stwuct qcom_icc_node xm_qdss_etw = {
	.name = "xm_qdss_etw",
	.id = SDM845_MASTEW_QDSS_ETW,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDM845_SWAVE_A2NOC_SNOC },
};

static stwuct qcom_icc_node xm_usb3_0 = {
	.name = "xm_usb3_0",
	.id = SDM845_MASTEW_USB3_0,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDM845_SWAVE_A2NOC_SNOC },
};

static stwuct qcom_icc_node xm_usb3_1 = {
	.name = "xm_usb3_1",
	.id = SDM845_MASTEW_USB3_1,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDM845_SWAVE_A2NOC_SNOC },
};

static stwuct qcom_icc_node qxm_camnoc_hf0_uncomp = {
	.name = "qxm_camnoc_hf0_uncomp",
	.id = SDM845_MASTEW_CAMNOC_HF0_UNCOMP,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SDM845_SWAVE_CAMNOC_UNCOMP },
};

static stwuct qcom_icc_node qxm_camnoc_hf1_uncomp = {
	.name = "qxm_camnoc_hf1_uncomp",
	.id = SDM845_MASTEW_CAMNOC_HF1_UNCOMP,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SDM845_SWAVE_CAMNOC_UNCOMP },
};

static stwuct qcom_icc_node qxm_camnoc_sf_uncomp = {
	.name = "qxm_camnoc_sf_uncomp",
	.id = SDM845_MASTEW_CAMNOC_SF_UNCOMP,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SDM845_SWAVE_CAMNOC_UNCOMP },
};

static stwuct qcom_icc_node qhm_spdm = {
	.name = "qhm_spdm",
	.id = SDM845_MASTEW_SPDM,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SDM845_SWAVE_CNOC_A2NOC },
};

static stwuct qcom_icc_node qhm_tic = {
	.name = "qhm_tic",
	.id = SDM845_MASTEW_TIC,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 43,
	.winks = { SDM845_SWAVE_A1NOC_CFG,
		   SDM845_SWAVE_A2NOC_CFG,
		   SDM845_SWAVE_AOP,
		   SDM845_SWAVE_AOSS,
		   SDM845_SWAVE_CAMEWA_CFG,
		   SDM845_SWAVE_CWK_CTW,
		   SDM845_SWAVE_CDSP_CFG,
		   SDM845_SWAVE_WBCPW_CX_CFG,
		   SDM845_SWAVE_CWYPTO_0_CFG,
		   SDM845_SWAVE_DCC_CFG,
		   SDM845_SWAVE_CNOC_DDWSS,
		   SDM845_SWAVE_DISPWAY_CFG,
		   SDM845_SWAVE_GWM,
		   SDM845_SWAVE_GFX3D_CFG,
		   SDM845_SWAVE_IMEM_CFG,
		   SDM845_SWAVE_IPA_CFG,
		   SDM845_SWAVE_CNOC_MNOC_CFG,
		   SDM845_SWAVE_PCIE_0_CFG,
		   SDM845_SWAVE_PCIE_1_CFG,
		   SDM845_SWAVE_PDM,
		   SDM845_SWAVE_SOUTH_PHY_CFG,
		   SDM845_SWAVE_PIMEM_CFG,
		   SDM845_SWAVE_PWNG,
		   SDM845_SWAVE_QDSS_CFG,
		   SDM845_SWAVE_BWSP_2,
		   SDM845_SWAVE_BWSP_1,
		   SDM845_SWAVE_SDCC_2,
		   SDM845_SWAVE_SDCC_4,
		   SDM845_SWAVE_SNOC_CFG,
		   SDM845_SWAVE_SPDM_WWAPPEW,
		   SDM845_SWAVE_SPSS_CFG,
		   SDM845_SWAVE_TCSW,
		   SDM845_SWAVE_TWMM_NOWTH,
		   SDM845_SWAVE_TWMM_SOUTH,
		   SDM845_SWAVE_TSIF,
		   SDM845_SWAVE_UFS_CAWD_CFG,
		   SDM845_SWAVE_UFS_MEM_CFG,
		   SDM845_SWAVE_USB3_0,
		   SDM845_SWAVE_USB3_1,
		   SDM845_SWAVE_VENUS_CFG,
		   SDM845_SWAVE_VSENSE_CTWW_CFG,
		   SDM845_SWAVE_CNOC_A2NOC,
		   SDM845_SWAVE_SEWVICE_CNOC
	},
};

static stwuct qcom_icc_node qnm_snoc = {
	.name = "qnm_snoc",
	.id = SDM845_MASTEW_SNOC_CNOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 42,
	.winks = { SDM845_SWAVE_A1NOC_CFG,
		   SDM845_SWAVE_A2NOC_CFG,
		   SDM845_SWAVE_AOP,
		   SDM845_SWAVE_AOSS,
		   SDM845_SWAVE_CAMEWA_CFG,
		   SDM845_SWAVE_CWK_CTW,
		   SDM845_SWAVE_CDSP_CFG,
		   SDM845_SWAVE_WBCPW_CX_CFG,
		   SDM845_SWAVE_CWYPTO_0_CFG,
		   SDM845_SWAVE_DCC_CFG,
		   SDM845_SWAVE_CNOC_DDWSS,
		   SDM845_SWAVE_DISPWAY_CFG,
		   SDM845_SWAVE_GWM,
		   SDM845_SWAVE_GFX3D_CFG,
		   SDM845_SWAVE_IMEM_CFG,
		   SDM845_SWAVE_IPA_CFG,
		   SDM845_SWAVE_CNOC_MNOC_CFG,
		   SDM845_SWAVE_PCIE_0_CFG,
		   SDM845_SWAVE_PCIE_1_CFG,
		   SDM845_SWAVE_PDM,
		   SDM845_SWAVE_SOUTH_PHY_CFG,
		   SDM845_SWAVE_PIMEM_CFG,
		   SDM845_SWAVE_PWNG,
		   SDM845_SWAVE_QDSS_CFG,
		   SDM845_SWAVE_BWSP_2,
		   SDM845_SWAVE_BWSP_1,
		   SDM845_SWAVE_SDCC_2,
		   SDM845_SWAVE_SDCC_4,
		   SDM845_SWAVE_SNOC_CFG,
		   SDM845_SWAVE_SPDM_WWAPPEW,
		   SDM845_SWAVE_SPSS_CFG,
		   SDM845_SWAVE_TCSW,
		   SDM845_SWAVE_TWMM_NOWTH,
		   SDM845_SWAVE_TWMM_SOUTH,
		   SDM845_SWAVE_TSIF,
		   SDM845_SWAVE_UFS_CAWD_CFG,
		   SDM845_SWAVE_UFS_MEM_CFG,
		   SDM845_SWAVE_USB3_0,
		   SDM845_SWAVE_USB3_1,
		   SDM845_SWAVE_VENUS_CFG,
		   SDM845_SWAVE_VSENSE_CTWW_CFG,
		   SDM845_SWAVE_SEWVICE_CNOC
	},
};

static stwuct qcom_icc_node xm_qdss_dap = {
	.name = "xm_qdss_dap",
	.id = SDM845_MASTEW_QDSS_DAP,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 43,
	.winks = { SDM845_SWAVE_A1NOC_CFG,
		   SDM845_SWAVE_A2NOC_CFG,
		   SDM845_SWAVE_AOP,
		   SDM845_SWAVE_AOSS,
		   SDM845_SWAVE_CAMEWA_CFG,
		   SDM845_SWAVE_CWK_CTW,
		   SDM845_SWAVE_CDSP_CFG,
		   SDM845_SWAVE_WBCPW_CX_CFG,
		   SDM845_SWAVE_CWYPTO_0_CFG,
		   SDM845_SWAVE_DCC_CFG,
		   SDM845_SWAVE_CNOC_DDWSS,
		   SDM845_SWAVE_DISPWAY_CFG,
		   SDM845_SWAVE_GWM,
		   SDM845_SWAVE_GFX3D_CFG,
		   SDM845_SWAVE_IMEM_CFG,
		   SDM845_SWAVE_IPA_CFG,
		   SDM845_SWAVE_CNOC_MNOC_CFG,
		   SDM845_SWAVE_PCIE_0_CFG,
		   SDM845_SWAVE_PCIE_1_CFG,
		   SDM845_SWAVE_PDM,
		   SDM845_SWAVE_SOUTH_PHY_CFG,
		   SDM845_SWAVE_PIMEM_CFG,
		   SDM845_SWAVE_PWNG,
		   SDM845_SWAVE_QDSS_CFG,
		   SDM845_SWAVE_BWSP_2,
		   SDM845_SWAVE_BWSP_1,
		   SDM845_SWAVE_SDCC_2,
		   SDM845_SWAVE_SDCC_4,
		   SDM845_SWAVE_SNOC_CFG,
		   SDM845_SWAVE_SPDM_WWAPPEW,
		   SDM845_SWAVE_SPSS_CFG,
		   SDM845_SWAVE_TCSW,
		   SDM845_SWAVE_TWMM_NOWTH,
		   SDM845_SWAVE_TWMM_SOUTH,
		   SDM845_SWAVE_TSIF,
		   SDM845_SWAVE_UFS_CAWD_CFG,
		   SDM845_SWAVE_UFS_MEM_CFG,
		   SDM845_SWAVE_USB3_0,
		   SDM845_SWAVE_USB3_1,
		   SDM845_SWAVE_VENUS_CFG,
		   SDM845_SWAVE_VSENSE_CTWW_CFG,
		   SDM845_SWAVE_CNOC_A2NOC,
		   SDM845_SWAVE_SEWVICE_CNOC
	},
};

static stwuct qcom_icc_node qhm_cnoc = {
	.name = "qhm_cnoc",
	.id = SDM845_MASTEW_CNOC_DC_NOC,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 2,
	.winks = { SDM845_SWAVE_WWCC_CFG,
		   SDM845_SWAVE_MEM_NOC_CFG
	},
};

static stwuct qcom_icc_node acm_w3 = {
	.name = "acm_w3",
	.id = SDM845_MASTEW_APPSS_PWOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 3,
	.winks = { SDM845_SWAVE_GNOC_SNOC,
		   SDM845_SWAVE_GNOC_MEM_NOC,
		   SDM845_SWAVE_SEWVICE_GNOC
	},
};

static stwuct qcom_icc_node pm_gnoc_cfg = {
	.name = "pm_gnoc_cfg",
	.id = SDM845_MASTEW_GNOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SDM845_SWAVE_SEWVICE_GNOC },
};

static stwuct qcom_icc_node wwcc_mc = {
	.name = "wwcc_mc",
	.id = SDM845_MASTEW_WWCC,
	.channews = 4,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SDM845_SWAVE_EBI1 },
};

static stwuct qcom_icc_node acm_tcu = {
	.name = "acm_tcu",
	.id = SDM845_MASTEW_TCU_0,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 3,
	.winks = { SDM845_SWAVE_MEM_NOC_GNOC,
		   SDM845_SWAVE_WWCC,
		   SDM845_SWAVE_MEM_NOC_SNOC
	},
};

static stwuct qcom_icc_node qhm_memnoc_cfg = {
	.name = "qhm_memnoc_cfg",
	.id = SDM845_MASTEW_MEM_NOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 2,
	.winks = { SDM845_SWAVE_MSS_PWOC_MS_MPU_CFG,
		   SDM845_SWAVE_SEWVICE_MEM_NOC
	},
};

static stwuct qcom_icc_node qnm_apps = {
	.name = "qnm_apps",
	.id = SDM845_MASTEW_GNOC_MEM_NOC,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SDM845_SWAVE_WWCC },
};

static stwuct qcom_icc_node qnm_mnoc_hf = {
	.name = "qnm_mnoc_hf",
	.id = SDM845_MASTEW_MNOC_HF_MEM_NOC,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 2,
	.winks = { SDM845_SWAVE_MEM_NOC_GNOC,
		   SDM845_SWAVE_WWCC
	},
};

static stwuct qcom_icc_node qnm_mnoc_sf = {
	.name = "qnm_mnoc_sf",
	.id = SDM845_MASTEW_MNOC_SF_MEM_NOC,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 3,
	.winks = { SDM845_SWAVE_MEM_NOC_GNOC,
		   SDM845_SWAVE_WWCC,
		   SDM845_SWAVE_MEM_NOC_SNOC
	},
};

static stwuct qcom_icc_node qnm_snoc_gc = {
	.name = "qnm_snoc_gc",
	.id = SDM845_MASTEW_SNOC_GC_MEM_NOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDM845_SWAVE_WWCC },
};

static stwuct qcom_icc_node qnm_snoc_sf = {
	.name = "qnm_snoc_sf",
	.id = SDM845_MASTEW_SNOC_SF_MEM_NOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 2,
	.winks = { SDM845_SWAVE_MEM_NOC_GNOC,
		   SDM845_SWAVE_WWCC
	},
};

static stwuct qcom_icc_node qxm_gpu = {
	.name = "qxm_gpu",
	.id = SDM845_MASTEW_GFX3D,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 3,
	.winks = { SDM845_SWAVE_MEM_NOC_GNOC,
		   SDM845_SWAVE_WWCC,
		   SDM845_SWAVE_MEM_NOC_SNOC
	},
};

static stwuct qcom_icc_node qhm_mnoc_cfg = {
	.name = "qhm_mnoc_cfg",
	.id = SDM845_MASTEW_CNOC_MNOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SDM845_SWAVE_SEWVICE_MNOC },
};

static stwuct qcom_icc_node qxm_camnoc_hf0 = {
	.name = "qxm_camnoc_hf0",
	.id = SDM845_MASTEW_CAMNOC_HF0,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SDM845_SWAVE_MNOC_HF_MEM_NOC },
};

static stwuct qcom_icc_node qxm_camnoc_hf1 = {
	.name = "qxm_camnoc_hf1",
	.id = SDM845_MASTEW_CAMNOC_HF1,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SDM845_SWAVE_MNOC_HF_MEM_NOC },
};

static stwuct qcom_icc_node qxm_camnoc_sf = {
	.name = "qxm_camnoc_sf",
	.id = SDM845_MASTEW_CAMNOC_SF,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SDM845_SWAVE_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qxm_mdp0 = {
	.name = "qxm_mdp0",
	.id = SDM845_MASTEW_MDP0,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SDM845_SWAVE_MNOC_HF_MEM_NOC },
};

static stwuct qcom_icc_node qxm_mdp1 = {
	.name = "qxm_mdp1",
	.id = SDM845_MASTEW_MDP1,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SDM845_SWAVE_MNOC_HF_MEM_NOC },
};

static stwuct qcom_icc_node qxm_wot = {
	.name = "qxm_wot",
	.id = SDM845_MASTEW_WOTATOW,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SDM845_SWAVE_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qxm_venus0 = {
	.name = "qxm_venus0",
	.id = SDM845_MASTEW_VIDEO_P0,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SDM845_SWAVE_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qxm_venus1 = {
	.name = "qxm_venus1",
	.id = SDM845_MASTEW_VIDEO_P1,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SDM845_SWAVE_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qxm_venus_awm9 = {
	.name = "qxm_venus_awm9",
	.id = SDM845_MASTEW_VIDEO_PWOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDM845_SWAVE_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qhm_snoc_cfg = {
	.name = "qhm_snoc_cfg",
	.id = SDM845_MASTEW_SNOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SDM845_SWAVE_SEWVICE_SNOC },
};

static stwuct qcom_icc_node qnm_aggwe1_noc = {
	.name = "qnm_aggwe1_noc",
	.id = SDM845_MASTEW_A1NOC_SNOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 6,
	.winks = { SDM845_SWAVE_APPSS,
		   SDM845_SWAVE_SNOC_CNOC,
		   SDM845_SWAVE_SNOC_MEM_NOC_SF,
		   SDM845_SWAVE_IMEM,
		   SDM845_SWAVE_PIMEM,
		   SDM845_SWAVE_QDSS_STM
	},
};

static stwuct qcom_icc_node qnm_aggwe2_noc = {
	.name = "qnm_aggwe2_noc",
	.id = SDM845_MASTEW_A2NOC_SNOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 9,
	.winks = { SDM845_SWAVE_APPSS,
		   SDM845_SWAVE_SNOC_CNOC,
		   SDM845_SWAVE_SNOC_MEM_NOC_SF,
		   SDM845_SWAVE_IMEM,
		   SDM845_SWAVE_PCIE_0,
		   SDM845_SWAVE_PCIE_1,
		   SDM845_SWAVE_PIMEM,
		   SDM845_SWAVE_QDSS_STM,
		   SDM845_SWAVE_TCU
	},
};

static stwuct qcom_icc_node qnm_gwadiatow_sodv = {
	.name = "qnm_gwadiatow_sodv",
	.id = SDM845_MASTEW_GNOC_SNOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 8,
	.winks = { SDM845_SWAVE_APPSS,
		   SDM845_SWAVE_SNOC_CNOC,
		   SDM845_SWAVE_IMEM,
		   SDM845_SWAVE_PCIE_0,
		   SDM845_SWAVE_PCIE_1,
		   SDM845_SWAVE_PIMEM,
		   SDM845_SWAVE_QDSS_STM,
		   SDM845_SWAVE_TCU
	},
};

static stwuct qcom_icc_node qnm_memnoc = {
	.name = "qnm_memnoc",
	.id = SDM845_MASTEW_MEM_NOC_SNOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 5,
	.winks = { SDM845_SWAVE_APPSS,
		   SDM845_SWAVE_SNOC_CNOC,
		   SDM845_SWAVE_IMEM,
		   SDM845_SWAVE_PIMEM,
		   SDM845_SWAVE_QDSS_STM
	},
};

static stwuct qcom_icc_node qnm_pcie_anoc = {
	.name = "qnm_pcie_anoc",
	.id = SDM845_MASTEW_ANOC_PCIE_SNOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 5,
	.winks = { SDM845_SWAVE_APPSS,
		   SDM845_SWAVE_SNOC_CNOC,
		   SDM845_SWAVE_SNOC_MEM_NOC_SF,
		   SDM845_SWAVE_IMEM,
		   SDM845_SWAVE_QDSS_STM
	},
};

static stwuct qcom_icc_node qxm_pimem = {
	.name = "qxm_pimem",
	.id = SDM845_MASTEW_PIMEM,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 2,
	.winks = { SDM845_SWAVE_SNOC_MEM_NOC_GC,
		   SDM845_SWAVE_IMEM
	},
};

static stwuct qcom_icc_node xm_gic = {
	.name = "xm_gic",
	.id = SDM845_MASTEW_GIC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 2,
	.winks = { SDM845_SWAVE_SNOC_MEM_NOC_GC,
		   SDM845_SWAVE_IMEM
	},
};

static stwuct qcom_icc_node qns_a1noc_snoc = {
	.name = "qns_a1noc_snoc",
	.id = SDM845_SWAVE_A1NOC_SNOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SDM845_MASTEW_A1NOC_SNOC },
};

static stwuct qcom_icc_node swvc_aggwe1_noc = {
	.name = "swvc_aggwe1_noc",
	.id = SDM845_SWAVE_SEWVICE_A1NOC,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { 0 },
};

static stwuct qcom_icc_node qns_pcie_a1noc_snoc = {
	.name = "qns_pcie_a1noc_snoc",
	.id = SDM845_SWAVE_ANOC_PCIE_A1NOC_SNOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SDM845_MASTEW_ANOC_PCIE_SNOC },
};

static stwuct qcom_icc_node qns_a2noc_snoc = {
	.name = "qns_a2noc_snoc",
	.id = SDM845_SWAVE_A2NOC_SNOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SDM845_MASTEW_A2NOC_SNOC },
};

static stwuct qcom_icc_node qns_pcie_snoc = {
	.name = "qns_pcie_snoc",
	.id = SDM845_SWAVE_ANOC_PCIE_SNOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SDM845_MASTEW_ANOC_PCIE_SNOC },
};

static stwuct qcom_icc_node swvc_aggwe2_noc = {
	.name = "swvc_aggwe2_noc",
	.id = SDM845_SWAVE_SEWVICE_A2NOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qns_camnoc_uncomp = {
	.name = "qns_camnoc_uncomp",
	.id = SDM845_SWAVE_CAMNOC_UNCOMP,
	.channews = 1,
	.buswidth = 32,
};

static stwuct qcom_icc_node qhs_a1_noc_cfg = {
	.name = "qhs_a1_noc_cfg",
	.id = SDM845_SWAVE_A1NOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SDM845_MASTEW_A1NOC_CFG },
};

static stwuct qcom_icc_node qhs_a2_noc_cfg = {
	.name = "qhs_a2_noc_cfg",
	.id = SDM845_SWAVE_A2NOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SDM845_MASTEW_A2NOC_CFG },
};

static stwuct qcom_icc_node qhs_aop = {
	.name = "qhs_aop",
	.id = SDM845_SWAVE_AOP,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_aoss = {
	.name = "qhs_aoss",
	.id = SDM845_SWAVE_AOSS,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_camewa_cfg = {
	.name = "qhs_camewa_cfg",
	.id = SDM845_SWAVE_CAMEWA_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_cwk_ctw = {
	.name = "qhs_cwk_ctw",
	.id = SDM845_SWAVE_CWK_CTW,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_compute_dsp_cfg = {
	.name = "qhs_compute_dsp_cfg",
	.id = SDM845_SWAVE_CDSP_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_cpw_cx = {
	.name = "qhs_cpw_cx",
	.id = SDM845_SWAVE_WBCPW_CX_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_cwypto0_cfg = {
	.name = "qhs_cwypto0_cfg",
	.id = SDM845_SWAVE_CWYPTO_0_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_dcc_cfg = {
	.name = "qhs_dcc_cfg",
	.id = SDM845_SWAVE_DCC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SDM845_MASTEW_CNOC_DC_NOC },
};

static stwuct qcom_icc_node qhs_ddwss_cfg = {
	.name = "qhs_ddwss_cfg",
	.id = SDM845_SWAVE_CNOC_DDWSS,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_dispway_cfg = {
	.name = "qhs_dispway_cfg",
	.id = SDM845_SWAVE_DISPWAY_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_gwm = {
	.name = "qhs_gwm",
	.id = SDM845_SWAVE_GWM,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_gpuss_cfg = {
	.name = "qhs_gpuss_cfg",
	.id = SDM845_SWAVE_GFX3D_CFG,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node qhs_imem_cfg = {
	.name = "qhs_imem_cfg",
	.id = SDM845_SWAVE_IMEM_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_ipa = {
	.name = "qhs_ipa",
	.id = SDM845_SWAVE_IPA_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_mnoc_cfg = {
	.name = "qhs_mnoc_cfg",
	.id = SDM845_SWAVE_CNOC_MNOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SDM845_MASTEW_CNOC_MNOC_CFG },
};

static stwuct qcom_icc_node qhs_pcie0_cfg = {
	.name = "qhs_pcie0_cfg",
	.id = SDM845_SWAVE_PCIE_0_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_pcie_gen3_cfg = {
	.name = "qhs_pcie_gen3_cfg",
	.id = SDM845_SWAVE_PCIE_1_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_pdm = {
	.name = "qhs_pdm",
	.id = SDM845_SWAVE_PDM,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_phy_wefgen_south = {
	.name = "qhs_phy_wefgen_south",
	.id = SDM845_SWAVE_SOUTH_PHY_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_pimem_cfg = {
	.name = "qhs_pimem_cfg",
	.id = SDM845_SWAVE_PIMEM_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_pwng = {
	.name = "qhs_pwng",
	.id = SDM845_SWAVE_PWNG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_qdss_cfg = {
	.name = "qhs_qdss_cfg",
	.id = SDM845_SWAVE_QDSS_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_qupv3_nowth = {
	.name = "qhs_qupv3_nowth",
	.id = SDM845_SWAVE_BWSP_2,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_qupv3_south = {
	.name = "qhs_qupv3_south",
	.id = SDM845_SWAVE_BWSP_1,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_sdc2 = {
	.name = "qhs_sdc2",
	.id = SDM845_SWAVE_SDCC_2,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_sdc4 = {
	.name = "qhs_sdc4",
	.id = SDM845_SWAVE_SDCC_4,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_snoc_cfg = {
	.name = "qhs_snoc_cfg",
	.id = SDM845_SWAVE_SNOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SDM845_MASTEW_SNOC_CFG },
};

static stwuct qcom_icc_node qhs_spdm = {
	.name = "qhs_spdm",
	.id = SDM845_SWAVE_SPDM_WWAPPEW,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_spss_cfg = {
	.name = "qhs_spss_cfg",
	.id = SDM845_SWAVE_SPSS_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_tcsw = {
	.name = "qhs_tcsw",
	.id = SDM845_SWAVE_TCSW,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_twmm_nowth = {
	.name = "qhs_twmm_nowth",
	.id = SDM845_SWAVE_TWMM_NOWTH,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_twmm_south = {
	.name = "qhs_twmm_south",
	.id = SDM845_SWAVE_TWMM_SOUTH,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_tsif = {
	.name = "qhs_tsif",
	.id = SDM845_SWAVE_TSIF,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_ufs_cawd_cfg = {
	.name = "qhs_ufs_cawd_cfg",
	.id = SDM845_SWAVE_UFS_CAWD_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_ufs_mem_cfg = {
	.name = "qhs_ufs_mem_cfg",
	.id = SDM845_SWAVE_UFS_MEM_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_usb3_0 = {
	.name = "qhs_usb3_0",
	.id = SDM845_SWAVE_USB3_0,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_usb3_1 = {
	.name = "qhs_usb3_1",
	.id = SDM845_SWAVE_USB3_1,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_venus_cfg = {
	.name = "qhs_venus_cfg",
	.id = SDM845_SWAVE_VENUS_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_vsense_ctww_cfg = {
	.name = "qhs_vsense_ctww_cfg",
	.id = SDM845_SWAVE_VSENSE_CTWW_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qns_cnoc_a2noc = {
	.name = "qns_cnoc_a2noc",
	.id = SDM845_SWAVE_CNOC_A2NOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDM845_MASTEW_CNOC_A2NOC },
};

static stwuct qcom_icc_node swvc_cnoc = {
	.name = "swvc_cnoc",
	.id = SDM845_SWAVE_SEWVICE_CNOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_wwcc = {
	.name = "qhs_wwcc",
	.id = SDM845_SWAVE_WWCC_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_memnoc = {
	.name = "qhs_memnoc",
	.id = SDM845_SWAVE_MEM_NOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SDM845_MASTEW_MEM_NOC_CFG },
};

static stwuct qcom_icc_node qns_gwadiatow_sodv = {
	.name = "qns_gwadiatow_sodv",
	.id = SDM845_SWAVE_GNOC_SNOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDM845_MASTEW_GNOC_SNOC },
};

static stwuct qcom_icc_node qns_gnoc_memnoc = {
	.name = "qns_gnoc_memnoc",
	.id = SDM845_SWAVE_GNOC_MEM_NOC,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SDM845_MASTEW_GNOC_MEM_NOC },
};

static stwuct qcom_icc_node swvc_gnoc = {
	.name = "swvc_gnoc",
	.id = SDM845_SWAVE_SEWVICE_GNOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node ebi = {
	.name = "ebi",
	.id = SDM845_SWAVE_EBI1,
	.channews = 4,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_mdsp_ms_mpu_cfg = {
	.name = "qhs_mdsp_ms_mpu_cfg",
	.id = SDM845_SWAVE_MSS_PWOC_MS_MPU_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qns_apps_io = {
	.name = "qns_apps_io",
	.id = SDM845_SWAVE_MEM_NOC_GNOC,
	.channews = 1,
	.buswidth = 32,
};

static stwuct qcom_icc_node qns_wwcc = {
	.name = "qns_wwcc",
	.id = SDM845_SWAVE_WWCC,
	.channews = 4,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SDM845_MASTEW_WWCC },
};

static stwuct qcom_icc_node qns_memnoc_snoc = {
	.name = "qns_memnoc_snoc",
	.id = SDM845_SWAVE_MEM_NOC_SNOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDM845_MASTEW_MEM_NOC_SNOC },
};

static stwuct qcom_icc_node swvc_memnoc = {
	.name = "swvc_memnoc",
	.id = SDM845_SWAVE_SEWVICE_MEM_NOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qns2_mem_noc = {
	.name = "qns2_mem_noc",
	.id = SDM845_SWAVE_MNOC_SF_MEM_NOC,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SDM845_MASTEW_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qns_mem_noc_hf = {
	.name = "qns_mem_noc_hf",
	.id = SDM845_SWAVE_MNOC_HF_MEM_NOC,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SDM845_MASTEW_MNOC_HF_MEM_NOC },
};

static stwuct qcom_icc_node swvc_mnoc = {
	.name = "swvc_mnoc",
	.id = SDM845_SWAVE_SEWVICE_MNOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_apss = {
	.name = "qhs_apss",
	.id = SDM845_SWAVE_APPSS,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node qns_cnoc = {
	.name = "qns_cnoc",
	.id = SDM845_SWAVE_SNOC_CNOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDM845_MASTEW_SNOC_CNOC },
};

static stwuct qcom_icc_node qns_memnoc_gc = {
	.name = "qns_memnoc_gc",
	.id = SDM845_SWAVE_SNOC_MEM_NOC_GC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SDM845_MASTEW_SNOC_GC_MEM_NOC },
};

static stwuct qcom_icc_node qns_memnoc_sf = {
	.name = "qns_memnoc_sf",
	.id = SDM845_SWAVE_SNOC_MEM_NOC_SF,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SDM845_MASTEW_SNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qxs_imem = {
	.name = "qxs_imem",
	.id = SDM845_SWAVE_IMEM,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node qxs_pcie = {
	.name = "qxs_pcie",
	.id = SDM845_SWAVE_PCIE_0,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node qxs_pcie_gen3 = {
	.name = "qxs_pcie_gen3",
	.id = SDM845_SWAVE_PCIE_1,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node qxs_pimem = {
	.name = "qxs_pimem",
	.id = SDM845_SWAVE_PIMEM,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node swvc_snoc = {
	.name = "swvc_snoc",
	.id = SDM845_SWAVE_SEWVICE_SNOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node xs_qdss_stm = {
	.name = "xs_qdss_stm",
	.id = SDM845_SWAVE_QDSS_STM,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node xs_sys_tcu_cfg = {
	.name = "xs_sys_tcu_cfg",
	.id = SDM845_SWAVE_TCU,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_bcm bcm_acv = {
	.name = "ACV",
	.enabwe_mask = BIT(3),
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &ebi },
};

static stwuct qcom_icc_bcm bcm_mc0 = {
	.name = "MC0",
	.keepawive = twue,
	.num_nodes = 1,
	.nodes = { &ebi },
};

static stwuct qcom_icc_bcm bcm_sh0 = {
	.name = "SH0",
	.keepawive = twue,
	.num_nodes = 1,
	.nodes = { &qns_wwcc },
};

static stwuct qcom_icc_bcm bcm_mm0 = {
	.name = "MM0",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qns_mem_noc_hf },
};

static stwuct qcom_icc_bcm bcm_sh1 = {
	.name = "SH1",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qns_apps_io },
};

static stwuct qcom_icc_bcm bcm_mm1 = {
	.name = "MM1",
	.keepawive = twue,
	.num_nodes = 7,
	.nodes = { &qxm_camnoc_hf0_uncomp,
		   &qxm_camnoc_hf1_uncomp,
		   &qxm_camnoc_sf_uncomp,
		   &qxm_camnoc_hf0,
		   &qxm_camnoc_hf1,
		   &qxm_mdp0,
		   &qxm_mdp1
	},
};

static stwuct qcom_icc_bcm bcm_sh2 = {
	.name = "SH2",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qns_memnoc_snoc },
};

static stwuct qcom_icc_bcm bcm_mm2 = {
	.name = "MM2",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qns2_mem_noc },
};

static stwuct qcom_icc_bcm bcm_sh3 = {
	.name = "SH3",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &acm_tcu },
};

static stwuct qcom_icc_bcm bcm_mm3 = {
	.name = "MM3",
	.keepawive = fawse,
	.num_nodes = 5,
	.nodes = { &qxm_camnoc_sf, &qxm_wot, &qxm_venus0, &qxm_venus1, &qxm_venus_awm9 },
};

static stwuct qcom_icc_bcm bcm_sh5 = {
	.name = "SH5",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qnm_apps },
};

static stwuct qcom_icc_bcm bcm_sn0 = {
	.name = "SN0",
	.keepawive = twue,
	.num_nodes = 1,
	.nodes = { &qns_memnoc_sf },
};

static stwuct qcom_icc_bcm bcm_ce0 = {
	.name = "CE0",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qxm_cwypto },
};

static stwuct qcom_icc_bcm bcm_cn0 = {
	.name = "CN0",
	.keepawive = fawse,
	.num_nodes = 47,
	.nodes = { &qhm_spdm,
		   &qhm_tic,
		   &qnm_snoc,
		   &xm_qdss_dap,
		   &qhs_a1_noc_cfg,
		   &qhs_a2_noc_cfg,
		   &qhs_aop,
		   &qhs_aoss,
		   &qhs_camewa_cfg,
		   &qhs_cwk_ctw,
		   &qhs_compute_dsp_cfg,
		   &qhs_cpw_cx,
		   &qhs_cwypto0_cfg,
		   &qhs_dcc_cfg,
		   &qhs_ddwss_cfg,
		   &qhs_dispway_cfg,
		   &qhs_gwm,
		   &qhs_gpuss_cfg,
		   &qhs_imem_cfg,
		   &qhs_ipa,
		   &qhs_mnoc_cfg,
		   &qhs_pcie0_cfg,
		   &qhs_pcie_gen3_cfg,
		   &qhs_pdm,
		   &qhs_phy_wefgen_south,
		   &qhs_pimem_cfg,
		   &qhs_pwng,
		   &qhs_qdss_cfg,
		   &qhs_qupv3_nowth,
		   &qhs_qupv3_south,
		   &qhs_sdc2,
		   &qhs_sdc4,
		   &qhs_snoc_cfg,
		   &qhs_spdm,
		   &qhs_spss_cfg,
		   &qhs_tcsw,
		   &qhs_twmm_nowth,
		   &qhs_twmm_south,
		   &qhs_tsif,
		   &qhs_ufs_cawd_cfg,
		   &qhs_ufs_mem_cfg,
		   &qhs_usb3_0,
		   &qhs_usb3_1,
		   &qhs_venus_cfg,
		   &qhs_vsense_ctww_cfg,
		   &qns_cnoc_a2noc,
		   &swvc_cnoc
	},
};

static stwuct qcom_icc_bcm bcm_qup0 = {
	.name = "QUP0",
	.keepawive = fawse,
	.num_nodes = 2,
	.nodes = { &qhm_qup1, &qhm_qup2 },
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
	.nodes = { &qns_memnoc_gc },
};

static stwuct qcom_icc_bcm bcm_sn3 = {
	.name = "SN3",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qns_cnoc },
};

static stwuct qcom_icc_bcm bcm_sn4 = {
	.name = "SN4",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qxm_pimem },
};

static stwuct qcom_icc_bcm bcm_sn5 = {
	.name = "SN5",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &xs_qdss_stm },
};

static stwuct qcom_icc_bcm bcm_sn6 = {
	.name = "SN6",
	.keepawive = fawse,
	.num_nodes = 3,
	.nodes = { &qhs_apss, &swvc_snoc, &xs_sys_tcu_cfg },
};

static stwuct qcom_icc_bcm bcm_sn7 = {
	.name = "SN7",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qxs_pcie },
};

static stwuct qcom_icc_bcm bcm_sn8 = {
	.name = "SN8",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qxs_pcie_gen3 },
};

static stwuct qcom_icc_bcm bcm_sn9 = {
	.name = "SN9",
	.keepawive = fawse,
	.num_nodes = 2,
	.nodes = { &swvc_aggwe1_noc, &qnm_aggwe1_noc },
};

static stwuct qcom_icc_bcm bcm_sn11 = {
	.name = "SN11",
	.keepawive = fawse,
	.num_nodes = 2,
	.nodes = { &swvc_aggwe2_noc, &qnm_aggwe2_noc },
};

static stwuct qcom_icc_bcm bcm_sn12 = {
	.name = "SN12",
	.keepawive = fawse,
	.num_nodes = 2,
	.nodes = { &qnm_gwadiatow_sodv, &xm_gic },
};

static stwuct qcom_icc_bcm bcm_sn14 = {
	.name = "SN14",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qnm_pcie_anoc },
};

static stwuct qcom_icc_bcm bcm_sn15 = {
	.name = "SN15",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qnm_memnoc },
};

static stwuct qcom_icc_bcm * const aggwe1_noc_bcms[] = {
	&bcm_sn9,
	&bcm_qup0,
};

static stwuct qcom_icc_node * const aggwe1_noc_nodes[] = {
	[MASTEW_A1NOC_CFG] = &qhm_a1noc_cfg,
	[MASTEW_TSIF] = &qhm_tsif,
	[MASTEW_SDCC_2] = &xm_sdc2,
	[MASTEW_SDCC_4] = &xm_sdc4,
	[MASTEW_UFS_CAWD] = &xm_ufs_cawd,
	[MASTEW_UFS_MEM] = &xm_ufs_mem,
	[MASTEW_PCIE_0] = &xm_pcie_0,
	[SWAVE_A1NOC_SNOC] = &qns_a1noc_snoc,
	[SWAVE_SEWVICE_A1NOC] = &swvc_aggwe1_noc,
	[SWAVE_ANOC_PCIE_A1NOC_SNOC] = &qns_pcie_a1noc_snoc,
	[MASTEW_QUP_1] = &qhm_qup1,
};

static const stwuct qcom_icc_desc sdm845_aggwe1_noc = {
	.nodes = aggwe1_noc_nodes,
	.num_nodes = AWWAY_SIZE(aggwe1_noc_nodes),
	.bcms = aggwe1_noc_bcms,
	.num_bcms = AWWAY_SIZE(aggwe1_noc_bcms),
};

static stwuct qcom_icc_bcm * const aggwe2_noc_bcms[] = {
	&bcm_ce0,
	&bcm_sn11,
	&bcm_qup0,
};

static stwuct qcom_icc_node * const aggwe2_noc_nodes[] = {
	[MASTEW_A2NOC_CFG] = &qhm_a2noc_cfg,
	[MASTEW_QDSS_BAM] = &qhm_qdss_bam,
	[MASTEW_CNOC_A2NOC] = &qnm_cnoc,
	[MASTEW_CWYPTO] = &qxm_cwypto,
	[MASTEW_IPA] = &qxm_ipa,
	[MASTEW_PCIE_1] = &xm_pcie3_1,
	[MASTEW_QDSS_ETW] = &xm_qdss_etw,
	[MASTEW_USB3_0] = &xm_usb3_0,
	[MASTEW_USB3_1] = &xm_usb3_1,
	[SWAVE_A2NOC_SNOC] = &qns_a2noc_snoc,
	[SWAVE_ANOC_PCIE_SNOC] = &qns_pcie_snoc,
	[SWAVE_SEWVICE_A2NOC] = &swvc_aggwe2_noc,
	[MASTEW_QUP_2] = &qhm_qup2,
};

static const stwuct qcom_icc_desc sdm845_aggwe2_noc = {
	.nodes = aggwe2_noc_nodes,
	.num_nodes = AWWAY_SIZE(aggwe2_noc_nodes),
	.bcms = aggwe2_noc_bcms,
	.num_bcms = AWWAY_SIZE(aggwe2_noc_bcms),
};

static stwuct qcom_icc_bcm * const config_noc_bcms[] = {
	&bcm_cn0,
};

static stwuct qcom_icc_node * const config_noc_nodes[] = {
	[MASTEW_SPDM] = &qhm_spdm,
	[MASTEW_TIC] = &qhm_tic,
	[MASTEW_SNOC_CNOC] = &qnm_snoc,
	[MASTEW_QDSS_DAP] = &xm_qdss_dap,
	[SWAVE_A1NOC_CFG] = &qhs_a1_noc_cfg,
	[SWAVE_A2NOC_CFG] = &qhs_a2_noc_cfg,
	[SWAVE_AOP] = &qhs_aop,
	[SWAVE_AOSS] = &qhs_aoss,
	[SWAVE_CAMEWA_CFG] = &qhs_camewa_cfg,
	[SWAVE_CWK_CTW] = &qhs_cwk_ctw,
	[SWAVE_CDSP_CFG] = &qhs_compute_dsp_cfg,
	[SWAVE_WBCPW_CX_CFG] = &qhs_cpw_cx,
	[SWAVE_CWYPTO_0_CFG] = &qhs_cwypto0_cfg,
	[SWAVE_DCC_CFG] = &qhs_dcc_cfg,
	[SWAVE_CNOC_DDWSS] = &qhs_ddwss_cfg,
	[SWAVE_DISPWAY_CFG] = &qhs_dispway_cfg,
	[SWAVE_GWM] = &qhs_gwm,
	[SWAVE_GFX3D_CFG] = &qhs_gpuss_cfg,
	[SWAVE_IMEM_CFG] = &qhs_imem_cfg,
	[SWAVE_IPA_CFG] = &qhs_ipa,
	[SWAVE_CNOC_MNOC_CFG] = &qhs_mnoc_cfg,
	[SWAVE_PCIE_0_CFG] = &qhs_pcie0_cfg,
	[SWAVE_PCIE_1_CFG] = &qhs_pcie_gen3_cfg,
	[SWAVE_PDM] = &qhs_pdm,
	[SWAVE_SOUTH_PHY_CFG] = &qhs_phy_wefgen_south,
	[SWAVE_PIMEM_CFG] = &qhs_pimem_cfg,
	[SWAVE_PWNG] = &qhs_pwng,
	[SWAVE_QDSS_CFG] = &qhs_qdss_cfg,
	[SWAVE_BWSP_2] = &qhs_qupv3_nowth,
	[SWAVE_BWSP_1] = &qhs_qupv3_south,
	[SWAVE_SDCC_2] = &qhs_sdc2,
	[SWAVE_SDCC_4] = &qhs_sdc4,
	[SWAVE_SNOC_CFG] = &qhs_snoc_cfg,
	[SWAVE_SPDM_WWAPPEW] = &qhs_spdm,
	[SWAVE_SPSS_CFG] = &qhs_spss_cfg,
	[SWAVE_TCSW] = &qhs_tcsw,
	[SWAVE_TWMM_NOWTH] = &qhs_twmm_nowth,
	[SWAVE_TWMM_SOUTH] = &qhs_twmm_south,
	[SWAVE_TSIF] = &qhs_tsif,
	[SWAVE_UFS_CAWD_CFG] = &qhs_ufs_cawd_cfg,
	[SWAVE_UFS_MEM_CFG] = &qhs_ufs_mem_cfg,
	[SWAVE_USB3_0] = &qhs_usb3_0,
	[SWAVE_USB3_1] = &qhs_usb3_1,
	[SWAVE_VENUS_CFG] = &qhs_venus_cfg,
	[SWAVE_VSENSE_CTWW_CFG] = &qhs_vsense_ctww_cfg,
	[SWAVE_CNOC_A2NOC] = &qns_cnoc_a2noc,
	[SWAVE_SEWVICE_CNOC] = &swvc_cnoc,
};

static const stwuct qcom_icc_desc sdm845_config_noc = {
	.nodes = config_noc_nodes,
	.num_nodes = AWWAY_SIZE(config_noc_nodes),
	.bcms = config_noc_bcms,
	.num_bcms = AWWAY_SIZE(config_noc_bcms),
};

static stwuct qcom_icc_bcm * const dc_noc_bcms[] = {
};

static stwuct qcom_icc_node * const dc_noc_nodes[] = {
	[MASTEW_CNOC_DC_NOC] = &qhm_cnoc,
	[SWAVE_WWCC_CFG] = &qhs_wwcc,
	[SWAVE_MEM_NOC_CFG] = &qhs_memnoc,
};

static const stwuct qcom_icc_desc sdm845_dc_noc = {
	.nodes = dc_noc_nodes,
	.num_nodes = AWWAY_SIZE(dc_noc_nodes),
	.bcms = dc_noc_bcms,
	.num_bcms = AWWAY_SIZE(dc_noc_bcms),
};

static stwuct qcom_icc_bcm * const gwadiatow_noc_bcms[] = {
};

static stwuct qcom_icc_node * const gwadiatow_noc_nodes[] = {
	[MASTEW_APPSS_PWOC] = &acm_w3,
	[MASTEW_GNOC_CFG] = &pm_gnoc_cfg,
	[SWAVE_GNOC_SNOC] = &qns_gwadiatow_sodv,
	[SWAVE_GNOC_MEM_NOC] = &qns_gnoc_memnoc,
	[SWAVE_SEWVICE_GNOC] = &swvc_gnoc,
};

static const stwuct qcom_icc_desc sdm845_gwadiatow_noc = {
	.nodes = gwadiatow_noc_nodes,
	.num_nodes = AWWAY_SIZE(gwadiatow_noc_nodes),
	.bcms = gwadiatow_noc_bcms,
	.num_bcms = AWWAY_SIZE(gwadiatow_noc_bcms),
};

static stwuct qcom_icc_bcm * const mem_noc_bcms[] = {
	&bcm_mc0,
	&bcm_acv,
	&bcm_sh0,
	&bcm_sh1,
	&bcm_sh2,
	&bcm_sh3,
	&bcm_sh5,
};

static stwuct qcom_icc_node * const mem_noc_nodes[] = {
	[MASTEW_TCU_0] = &acm_tcu,
	[MASTEW_MEM_NOC_CFG] = &qhm_memnoc_cfg,
	[MASTEW_GNOC_MEM_NOC] = &qnm_apps,
	[MASTEW_MNOC_HF_MEM_NOC] = &qnm_mnoc_hf,
	[MASTEW_MNOC_SF_MEM_NOC] = &qnm_mnoc_sf,
	[MASTEW_SNOC_GC_MEM_NOC] = &qnm_snoc_gc,
	[MASTEW_SNOC_SF_MEM_NOC] = &qnm_snoc_sf,
	[MASTEW_GFX3D] = &qxm_gpu,
	[SWAVE_MSS_PWOC_MS_MPU_CFG] = &qhs_mdsp_ms_mpu_cfg,
	[SWAVE_MEM_NOC_GNOC] = &qns_apps_io,
	[SWAVE_WWCC] = &qns_wwcc,
	[SWAVE_MEM_NOC_SNOC] = &qns_memnoc_snoc,
	[SWAVE_SEWVICE_MEM_NOC] = &swvc_memnoc,
	[MASTEW_WWCC] = &wwcc_mc,
	[SWAVE_EBI1] = &ebi,
};

static const stwuct qcom_icc_desc sdm845_mem_noc = {
	.nodes = mem_noc_nodes,
	.num_nodes = AWWAY_SIZE(mem_noc_nodes),
	.bcms = mem_noc_bcms,
	.num_bcms = AWWAY_SIZE(mem_noc_bcms),
};

static stwuct qcom_icc_bcm * const mmss_noc_bcms[] = {
	&bcm_mm0,
	&bcm_mm1,
	&bcm_mm2,
	&bcm_mm3,
};

static stwuct qcom_icc_node * const mmss_noc_nodes[] = {
	[MASTEW_CNOC_MNOC_CFG] = &qhm_mnoc_cfg,
	[MASTEW_CAMNOC_HF0] = &qxm_camnoc_hf0,
	[MASTEW_CAMNOC_HF1] = &qxm_camnoc_hf1,
	[MASTEW_CAMNOC_SF] = &qxm_camnoc_sf,
	[MASTEW_MDP0] = &qxm_mdp0,
	[MASTEW_MDP1] = &qxm_mdp1,
	[MASTEW_WOTATOW] = &qxm_wot,
	[MASTEW_VIDEO_P0] = &qxm_venus0,
	[MASTEW_VIDEO_P1] = &qxm_venus1,
	[MASTEW_VIDEO_PWOC] = &qxm_venus_awm9,
	[SWAVE_MNOC_SF_MEM_NOC] = &qns2_mem_noc,
	[SWAVE_MNOC_HF_MEM_NOC] = &qns_mem_noc_hf,
	[SWAVE_SEWVICE_MNOC] = &swvc_mnoc,
	[MASTEW_CAMNOC_HF0_UNCOMP] = &qxm_camnoc_hf0_uncomp,
	[MASTEW_CAMNOC_HF1_UNCOMP] = &qxm_camnoc_hf1_uncomp,
	[MASTEW_CAMNOC_SF_UNCOMP] = &qxm_camnoc_sf_uncomp,
	[SWAVE_CAMNOC_UNCOMP] = &qns_camnoc_uncomp,
};

static const stwuct qcom_icc_desc sdm845_mmss_noc = {
	.nodes = mmss_noc_nodes,
	.num_nodes = AWWAY_SIZE(mmss_noc_nodes),
	.bcms = mmss_noc_bcms,
	.num_bcms = AWWAY_SIZE(mmss_noc_bcms),
};

static stwuct qcom_icc_bcm * const system_noc_bcms[] = {
	&bcm_sn0,
	&bcm_sn1,
	&bcm_sn2,
	&bcm_sn3,
	&bcm_sn4,
	&bcm_sn5,
	&bcm_sn6,
	&bcm_sn7,
	&bcm_sn8,
	&bcm_sn9,
	&bcm_sn11,
	&bcm_sn12,
	&bcm_sn14,
	&bcm_sn15,
};

static stwuct qcom_icc_node * const system_noc_nodes[] = {
	[MASTEW_SNOC_CFG] = &qhm_snoc_cfg,
	[MASTEW_A1NOC_SNOC] = &qnm_aggwe1_noc,
	[MASTEW_A2NOC_SNOC] = &qnm_aggwe2_noc,
	[MASTEW_GNOC_SNOC] = &qnm_gwadiatow_sodv,
	[MASTEW_MEM_NOC_SNOC] = &qnm_memnoc,
	[MASTEW_ANOC_PCIE_SNOC] = &qnm_pcie_anoc,
	[MASTEW_PIMEM] = &qxm_pimem,
	[MASTEW_GIC] = &xm_gic,
	[SWAVE_APPSS] = &qhs_apss,
	[SWAVE_SNOC_CNOC] = &qns_cnoc,
	[SWAVE_SNOC_MEM_NOC_GC] = &qns_memnoc_gc,
	[SWAVE_SNOC_MEM_NOC_SF] = &qns_memnoc_sf,
	[SWAVE_IMEM] = &qxs_imem,
	[SWAVE_PCIE_0] = &qxs_pcie,
	[SWAVE_PCIE_1] = &qxs_pcie_gen3,
	[SWAVE_PIMEM] = &qxs_pimem,
	[SWAVE_SEWVICE_SNOC] = &swvc_snoc,
	[SWAVE_QDSS_STM] = &xs_qdss_stm,
	[SWAVE_TCU] = &xs_sys_tcu_cfg,
};

static const stwuct qcom_icc_desc sdm845_system_noc = {
	.nodes = system_noc_nodes,
	.num_nodes = AWWAY_SIZE(system_noc_nodes),
	.bcms = system_noc_bcms,
	.num_bcms = AWWAY_SIZE(system_noc_bcms),
};

static const stwuct of_device_id qnoc_of_match[] = {
	{ .compatibwe = "qcom,sdm845-aggwe1-noc",
	  .data = &sdm845_aggwe1_noc},
	{ .compatibwe = "qcom,sdm845-aggwe2-noc",
	  .data = &sdm845_aggwe2_noc},
	{ .compatibwe = "qcom,sdm845-config-noc",
	  .data = &sdm845_config_noc},
	{ .compatibwe = "qcom,sdm845-dc-noc",
	  .data = &sdm845_dc_noc},
	{ .compatibwe = "qcom,sdm845-gwadiatow-noc",
	  .data = &sdm845_gwadiatow_noc},
	{ .compatibwe = "qcom,sdm845-mem-noc",
	  .data = &sdm845_mem_noc},
	{ .compatibwe = "qcom,sdm845-mmss-noc",
	  .data = &sdm845_mmss_noc},
	{ .compatibwe = "qcom,sdm845-system-noc",
	  .data = &sdm845_system_noc},
	{ }
};
MODUWE_DEVICE_TABWE(of, qnoc_of_match);

static stwuct pwatfowm_dwivew qnoc_dwivew = {
	.pwobe = qcom_icc_wpmh_pwobe,
	.wemove_new = qcom_icc_wpmh_wemove,
	.dwivew = {
		.name = "qnoc-sdm845",
		.of_match_tabwe = qnoc_of_match,
		.sync_state = icc_sync_state,
	},
};
moduwe_pwatfowm_dwivew(qnoc_dwivew);

MODUWE_AUTHOW("David Dai <daidavid1@codeauwowa.owg>");
MODUWE_DESCWIPTION("Quawcomm sdm845 NoC dwivew");
MODUWE_WICENSE("GPW v2");
