// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2020, The Winux Foundation. Aww wights wesewved.
 *
 */

#incwude <winux/device.h>
#incwude <winux/intewconnect.h>
#incwude <winux/intewconnect-pwovidew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <dt-bindings/intewconnect/qcom,sm8150.h>

#incwude "bcm-votew.h"
#incwude "icc-wpmh.h"
#incwude "sm8150.h"

static stwuct qcom_icc_node qhm_a1noc_cfg = {
	.name = "qhm_a1noc_cfg",
	.id = SM8150_MASTEW_A1NOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8150_SWAVE_SEWVICE_A1NOC },
};

static stwuct qcom_icc_node qhm_qup0 = {
	.name = "qhm_qup0",
	.id = SM8150_MASTEW_QUP_0,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8150_A1NOC_SNOC_SWV },
};

static stwuct qcom_icc_node xm_emac = {
	.name = "xm_emac",
	.id = SM8150_MASTEW_EMAC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8150_A1NOC_SNOC_SWV },
};

static stwuct qcom_icc_node xm_ufs_mem = {
	.name = "xm_ufs_mem",
	.id = SM8150_MASTEW_UFS_MEM,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8150_A1NOC_SNOC_SWV },
};

static stwuct qcom_icc_node xm_usb3_0 = {
	.name = "xm_usb3_0",
	.id = SM8150_MASTEW_USB3,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8150_A1NOC_SNOC_SWV },
};

static stwuct qcom_icc_node xm_usb3_1 = {
	.name = "xm_usb3_1",
	.id = SM8150_MASTEW_USB3_1,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8150_A1NOC_SNOC_SWV },
};

static stwuct qcom_icc_node qhm_a2noc_cfg = {
	.name = "qhm_a2noc_cfg",
	.id = SM8150_MASTEW_A2NOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8150_SWAVE_SEWVICE_A2NOC },
};

static stwuct qcom_icc_node qhm_qdss_bam = {
	.name = "qhm_qdss_bam",
	.id = SM8150_MASTEW_QDSS_BAM,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8150_A2NOC_SNOC_SWV },
};

static stwuct qcom_icc_node qhm_qspi = {
	.name = "qhm_qspi",
	.id = SM8150_MASTEW_QSPI,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8150_A2NOC_SNOC_SWV },
};

static stwuct qcom_icc_node qhm_qup1 = {
	.name = "qhm_qup1",
	.id = SM8150_MASTEW_QUP_1,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8150_A2NOC_SNOC_SWV },
};

static stwuct qcom_icc_node qhm_qup2 = {
	.name = "qhm_qup2",
	.id = SM8150_MASTEW_QUP_2,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8150_A2NOC_SNOC_SWV },
};

static stwuct qcom_icc_node qhm_sensowss_ahb = {
	.name = "qhm_sensowss_ahb",
	.id = SM8150_MASTEW_SENSOWS_AHB,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8150_A2NOC_SNOC_SWV },
};

static stwuct qcom_icc_node qhm_tsif = {
	.name = "qhm_tsif",
	.id = SM8150_MASTEW_TSIF,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8150_A2NOC_SNOC_SWV },
};

static stwuct qcom_icc_node qnm_cnoc = {
	.name = "qnm_cnoc",
	.id = SM8150_MASTEW_CNOC_A2NOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8150_A2NOC_SNOC_SWV },
};

static stwuct qcom_icc_node qxm_cwypto = {
	.name = "qxm_cwypto",
	.id = SM8150_MASTEW_CWYPTO_COWE_0,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8150_A2NOC_SNOC_SWV },
};

static stwuct qcom_icc_node qxm_ipa = {
	.name = "qxm_ipa",
	.id = SM8150_MASTEW_IPA,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8150_A2NOC_SNOC_SWV },
};

static stwuct qcom_icc_node xm_pcie3_0 = {
	.name = "xm_pcie3_0",
	.id = SM8150_MASTEW_PCIE,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8150_SWAVE_ANOC_PCIE_GEM_NOC },
};

static stwuct qcom_icc_node xm_pcie3_1 = {
	.name = "xm_pcie3_1",
	.id = SM8150_MASTEW_PCIE_1,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8150_SWAVE_ANOC_PCIE_GEM_NOC },
};

static stwuct qcom_icc_node xm_qdss_etw = {
	.name = "xm_qdss_etw",
	.id = SM8150_MASTEW_QDSS_ETW,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8150_A2NOC_SNOC_SWV },
};

static stwuct qcom_icc_node xm_sdc2 = {
	.name = "xm_sdc2",
	.id = SM8150_MASTEW_SDCC_2,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8150_A2NOC_SNOC_SWV },
};

static stwuct qcom_icc_node xm_sdc4 = {
	.name = "xm_sdc4",
	.id = SM8150_MASTEW_SDCC_4,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8150_A2NOC_SNOC_SWV },
};

static stwuct qcom_icc_node qxm_camnoc_hf0_uncomp = {
	.name = "qxm_camnoc_hf0_uncomp",
	.id = SM8150_MASTEW_CAMNOC_HF0_UNCOMP,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8150_SWAVE_CAMNOC_UNCOMP },
};

static stwuct qcom_icc_node qxm_camnoc_hf1_uncomp = {
	.name = "qxm_camnoc_hf1_uncomp",
	.id = SM8150_MASTEW_CAMNOC_HF1_UNCOMP,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8150_SWAVE_CAMNOC_UNCOMP },
};

static stwuct qcom_icc_node qxm_camnoc_sf_uncomp = {
	.name = "qxm_camnoc_sf_uncomp",
	.id = SM8150_MASTEW_CAMNOC_SF_UNCOMP,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8150_SWAVE_CAMNOC_UNCOMP },
};

static stwuct qcom_icc_node qnm_npu = {
	.name = "qnm_npu",
	.id = SM8150_MASTEW_NPU,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8150_SWAVE_CDSP_MEM_NOC },
};

static stwuct qcom_icc_node qhm_spdm = {
	.name = "qhm_spdm",
	.id = SM8150_MASTEW_SPDM,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8150_SWAVE_CNOC_A2NOC },
};

static stwuct qcom_icc_node qnm_snoc = {
	.name = "qnm_snoc",
	.id = SM8150_SNOC_CNOC_MAS,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 50,
	.winks = { SM8150_SWAVE_TWMM_SOUTH,
		   SM8150_SWAVE_CDSP_CFG,
		   SM8150_SWAVE_SPSS_CFG,
		   SM8150_SWAVE_CAMEWA_CFG,
		   SM8150_SWAVE_SDCC_4,
		   SM8150_SWAVE_SDCC_2,
		   SM8150_SWAVE_CNOC_MNOC_CFG,
		   SM8150_SWAVE_EMAC_CFG,
		   SM8150_SWAVE_UFS_MEM_CFG,
		   SM8150_SWAVE_TWMM_EAST,
		   SM8150_SWAVE_SSC_CFG,
		   SM8150_SWAVE_SNOC_CFG,
		   SM8150_SWAVE_NOWTH_PHY_CFG,
		   SM8150_SWAVE_QUP_0,
		   SM8150_SWAVE_GWM,
		   SM8150_SWAVE_PCIE_1_CFG,
		   SM8150_SWAVE_A2NOC_CFG,
		   SM8150_SWAVE_QDSS_CFG,
		   SM8150_SWAVE_DISPWAY_CFG,
		   SM8150_SWAVE_TCSW,
		   SM8150_SWAVE_CNOC_DDWSS,
		   SM8150_SWAVE_WBCPW_MMCX_CFG,
		   SM8150_SWAVE_NPU_CFG,
		   SM8150_SWAVE_PCIE_0_CFG,
		   SM8150_SWAVE_GWAPHICS_3D_CFG,
		   SM8150_SWAVE_VENUS_CFG,
		   SM8150_SWAVE_TSIF,
		   SM8150_SWAVE_IPA_CFG,
		   SM8150_SWAVE_CWK_CTW,
		   SM8150_SWAVE_AOP,
		   SM8150_SWAVE_QUP_1,
		   SM8150_SWAVE_AHB2PHY_SOUTH,
		   SM8150_SWAVE_USB3_1,
		   SM8150_SWAVE_SEWVICE_CNOC,
		   SM8150_SWAVE_UFS_CAWD_CFG,
		   SM8150_SWAVE_QUP_2,
		   SM8150_SWAVE_WBCPW_CX_CFG,
		   SM8150_SWAVE_TWMM_WEST,
		   SM8150_SWAVE_A1NOC_CFG,
		   SM8150_SWAVE_AOSS,
		   SM8150_SWAVE_PWNG,
		   SM8150_SWAVE_VSENSE_CTWW_CFG,
		   SM8150_SWAVE_QSPI,
		   SM8150_SWAVE_USB3,
		   SM8150_SWAVE_SPDM_WWAPPEW,
		   SM8150_SWAVE_CWYPTO_0_CFG,
		   SM8150_SWAVE_PIMEM_CFG,
		   SM8150_SWAVE_TWMM_NOWTH,
		   SM8150_SWAVE_WBCPW_MX_CFG,
		   SM8150_SWAVE_IMEM_CFG
	},
};

static stwuct qcom_icc_node xm_qdss_dap = {
	.name = "xm_qdss_dap",
	.id = SM8150_MASTEW_QDSS_DAP,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 51,
	.winks = { SM8150_SWAVE_TWMM_SOUTH,
		   SM8150_SWAVE_CDSP_CFG,
		   SM8150_SWAVE_SPSS_CFG,
		   SM8150_SWAVE_CAMEWA_CFG,
		   SM8150_SWAVE_SDCC_4,
		   SM8150_SWAVE_SDCC_2,
		   SM8150_SWAVE_CNOC_MNOC_CFG,
		   SM8150_SWAVE_EMAC_CFG,
		   SM8150_SWAVE_UFS_MEM_CFG,
		   SM8150_SWAVE_TWMM_EAST,
		   SM8150_SWAVE_SSC_CFG,
		   SM8150_SWAVE_SNOC_CFG,
		   SM8150_SWAVE_NOWTH_PHY_CFG,
		   SM8150_SWAVE_QUP_0,
		   SM8150_SWAVE_GWM,
		   SM8150_SWAVE_PCIE_1_CFG,
		   SM8150_SWAVE_A2NOC_CFG,
		   SM8150_SWAVE_QDSS_CFG,
		   SM8150_SWAVE_DISPWAY_CFG,
		   SM8150_SWAVE_TCSW,
		   SM8150_SWAVE_CNOC_DDWSS,
		   SM8150_SWAVE_CNOC_A2NOC,
		   SM8150_SWAVE_WBCPW_MMCX_CFG,
		   SM8150_SWAVE_NPU_CFG,
		   SM8150_SWAVE_PCIE_0_CFG,
		   SM8150_SWAVE_GWAPHICS_3D_CFG,
		   SM8150_SWAVE_VENUS_CFG,
		   SM8150_SWAVE_TSIF,
		   SM8150_SWAVE_IPA_CFG,
		   SM8150_SWAVE_CWK_CTW,
		   SM8150_SWAVE_AOP,
		   SM8150_SWAVE_QUP_1,
		   SM8150_SWAVE_AHB2PHY_SOUTH,
		   SM8150_SWAVE_USB3_1,
		   SM8150_SWAVE_SEWVICE_CNOC,
		   SM8150_SWAVE_UFS_CAWD_CFG,
		   SM8150_SWAVE_QUP_2,
		   SM8150_SWAVE_WBCPW_CX_CFG,
		   SM8150_SWAVE_TWMM_WEST,
		   SM8150_SWAVE_A1NOC_CFG,
		   SM8150_SWAVE_AOSS,
		   SM8150_SWAVE_PWNG,
		   SM8150_SWAVE_VSENSE_CTWW_CFG,
		   SM8150_SWAVE_QSPI,
		   SM8150_SWAVE_USB3,
		   SM8150_SWAVE_SPDM_WWAPPEW,
		   SM8150_SWAVE_CWYPTO_0_CFG,
		   SM8150_SWAVE_PIMEM_CFG,
		   SM8150_SWAVE_TWMM_NOWTH,
		   SM8150_SWAVE_WBCPW_MX_CFG,
		   SM8150_SWAVE_IMEM_CFG
	},
};

static stwuct qcom_icc_node qhm_cnoc_dc_noc = {
	.name = "qhm_cnoc_dc_noc",
	.id = SM8150_MASTEW_CNOC_DC_NOC,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 2,
	.winks = { SM8150_SWAVE_GEM_NOC_CFG,
		   SM8150_SWAVE_WWCC_CFG
	},
};

static stwuct qcom_icc_node acm_apps = {
	.name = "acm_apps",
	.id = SM8150_MASTEW_AMPSS_M0,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 3,
	.winks = { SM8150_SWAVE_ECC,
		   SM8150_SWAVE_WWCC,
		   SM8150_SWAVE_GEM_NOC_SNOC
	},
};

static stwuct qcom_icc_node acm_gpu_tcu = {
	.name = "acm_gpu_tcu",
	.id = SM8150_MASTEW_GPU_TCU,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 2,
	.winks = { SM8150_SWAVE_WWCC,
		   SM8150_SWAVE_GEM_NOC_SNOC
	},
};

static stwuct qcom_icc_node acm_sys_tcu = {
	.name = "acm_sys_tcu",
	.id = SM8150_MASTEW_SYS_TCU,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 2,
	.winks = { SM8150_SWAVE_WWCC,
		   SM8150_SWAVE_GEM_NOC_SNOC
	},
};

static stwuct qcom_icc_node qhm_gemnoc_cfg = {
	.name = "qhm_gemnoc_cfg",
	.id = SM8150_MASTEW_GEM_NOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 2,
	.winks = { SM8150_SWAVE_SEWVICE_GEM_NOC,
		   SM8150_SWAVE_MSS_PWOC_MS_MPU_CFG
	},
};

static stwuct qcom_icc_node qnm_cmpnoc = {
	.name = "qnm_cmpnoc",
	.id = SM8150_MASTEW_COMPUTE_NOC,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 3,
	.winks = { SM8150_SWAVE_ECC,
		   SM8150_SWAVE_WWCC,
		   SM8150_SWAVE_GEM_NOC_SNOC
	},
};

static stwuct qcom_icc_node qnm_gpu = {
	.name = "qnm_gpu",
	.id = SM8150_MASTEW_GWAPHICS_3D,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 2,
	.winks = { SM8150_SWAVE_WWCC,
		   SM8150_SWAVE_GEM_NOC_SNOC
	},
};

static stwuct qcom_icc_node qnm_mnoc_hf = {
	.name = "qnm_mnoc_hf",
	.id = SM8150_MASTEW_MNOC_HF_MEM_NOC,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8150_SWAVE_WWCC },
};

static stwuct qcom_icc_node qnm_mnoc_sf = {
	.name = "qnm_mnoc_sf",
	.id = SM8150_MASTEW_MNOC_SF_MEM_NOC,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 2,
	.winks = { SM8150_SWAVE_WWCC,
		   SM8150_SWAVE_GEM_NOC_SNOC
	},
};

static stwuct qcom_icc_node qnm_pcie = {
	.name = "qnm_pcie",
	.id = SM8150_MASTEW_GEM_NOC_PCIE_SNOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 2,
	.winks = { SM8150_SWAVE_WWCC,
		   SM8150_SWAVE_GEM_NOC_SNOC
	},
};

static stwuct qcom_icc_node qnm_snoc_gc = {
	.name = "qnm_snoc_gc",
	.id = SM8150_MASTEW_SNOC_GC_MEM_NOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8150_SWAVE_WWCC },
};

static stwuct qcom_icc_node qnm_snoc_sf = {
	.name = "qnm_snoc_sf",
	.id = SM8150_MASTEW_SNOC_SF_MEM_NOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8150_SWAVE_WWCC },
};

static stwuct qcom_icc_node qxm_ecc = {
	.name = "qxm_ecc",
	.id = SM8150_MASTEW_ECC,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8150_SWAVE_WWCC },
};

static stwuct qcom_icc_node wwcc_mc = {
	.name = "wwcc_mc",
	.id = SM8150_MASTEW_WWCC,
	.channews = 4,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8150_SWAVE_EBI_CH0 },
};

static stwuct qcom_icc_node qhm_mnoc_cfg = {
	.name = "qhm_mnoc_cfg",
	.id = SM8150_MASTEW_CNOC_MNOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8150_SWAVE_SEWVICE_MNOC },
};

static stwuct qcom_icc_node qxm_camnoc_hf0 = {
	.name = "qxm_camnoc_hf0",
	.id = SM8150_MASTEW_CAMNOC_HF0,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8150_SWAVE_MNOC_HF_MEM_NOC },
};

static stwuct qcom_icc_node qxm_camnoc_hf1 = {
	.name = "qxm_camnoc_hf1",
	.id = SM8150_MASTEW_CAMNOC_HF1,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8150_SWAVE_MNOC_HF_MEM_NOC },
};

static stwuct qcom_icc_node qxm_camnoc_sf = {
	.name = "qxm_camnoc_sf",
	.id = SM8150_MASTEW_CAMNOC_SF,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8150_SWAVE_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qxm_mdp0 = {
	.name = "qxm_mdp0",
	.id = SM8150_MASTEW_MDP_POWT0,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8150_SWAVE_MNOC_HF_MEM_NOC },
};

static stwuct qcom_icc_node qxm_mdp1 = {
	.name = "qxm_mdp1",
	.id = SM8150_MASTEW_MDP_POWT1,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8150_SWAVE_MNOC_HF_MEM_NOC },
};

static stwuct qcom_icc_node qxm_wot = {
	.name = "qxm_wot",
	.id = SM8150_MASTEW_WOTATOW,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8150_SWAVE_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qxm_venus0 = {
	.name = "qxm_venus0",
	.id = SM8150_MASTEW_VIDEO_P0,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8150_SWAVE_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qxm_venus1 = {
	.name = "qxm_venus1",
	.id = SM8150_MASTEW_VIDEO_P1,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8150_SWAVE_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qxm_venus_awm9 = {
	.name = "qxm_venus_awm9",
	.id = SM8150_MASTEW_VIDEO_PWOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8150_SWAVE_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qhm_snoc_cfg = {
	.name = "qhm_snoc_cfg",
	.id = SM8150_MASTEW_SNOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8150_SWAVE_SEWVICE_SNOC },
};

static stwuct qcom_icc_node qnm_aggwe1_noc = {
	.name = "qnm_aggwe1_noc",
	.id = SM8150_A1NOC_SNOC_MAS,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 6,
	.winks = { SM8150_SWAVE_SNOC_GEM_NOC_SF,
		   SM8150_SWAVE_PIMEM,
		   SM8150_SWAVE_OCIMEM,
		   SM8150_SWAVE_APPSS,
		   SM8150_SNOC_CNOC_SWV,
		   SM8150_SWAVE_QDSS_STM
	},
};

static stwuct qcom_icc_node qnm_aggwe2_noc = {
	.name = "qnm_aggwe2_noc",
	.id = SM8150_A2NOC_SNOC_MAS,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 9,
	.winks = { SM8150_SWAVE_SNOC_GEM_NOC_SF,
		   SM8150_SWAVE_PIMEM,
		   SM8150_SWAVE_OCIMEM,
		   SM8150_SWAVE_APPSS,
		   SM8150_SNOC_CNOC_SWV,
		   SM8150_SWAVE_PCIE_0,
		   SM8150_SWAVE_PCIE_1,
		   SM8150_SWAVE_TCU,
		   SM8150_SWAVE_QDSS_STM
	},
};

static stwuct qcom_icc_node qnm_gemnoc = {
	.name = "qnm_gemnoc",
	.id = SM8150_MASTEW_GEM_NOC_SNOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 6,
	.winks = { SM8150_SWAVE_PIMEM,
		   SM8150_SWAVE_OCIMEM,
		   SM8150_SWAVE_APPSS,
		   SM8150_SNOC_CNOC_SWV,
		   SM8150_SWAVE_TCU,
		   SM8150_SWAVE_QDSS_STM
	},
};

static stwuct qcom_icc_node qxm_pimem = {
	.name = "qxm_pimem",
	.id = SM8150_MASTEW_PIMEM,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 2,
	.winks = { SM8150_SWAVE_SNOC_GEM_NOC_GC,
		   SM8150_SWAVE_OCIMEM
	},
};

static stwuct qcom_icc_node xm_gic = {
	.name = "xm_gic",
	.id = SM8150_MASTEW_GIC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 2,
	.winks = { SM8150_SWAVE_SNOC_GEM_NOC_GC,
		   SM8150_SWAVE_OCIMEM
	},
};

static stwuct qcom_icc_node qns_a1noc_snoc = {
	.name = "qns_a1noc_snoc",
	.id = SM8150_A1NOC_SNOC_SWV,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8150_A1NOC_SNOC_MAS },
};

static stwuct qcom_icc_node swvc_aggwe1_noc = {
	.name = "swvc_aggwe1_noc",
	.id = SM8150_SWAVE_SEWVICE_A1NOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qns_a2noc_snoc = {
	.name = "qns_a2noc_snoc",
	.id = SM8150_A2NOC_SNOC_SWV,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8150_A2NOC_SNOC_MAS },
};

static stwuct qcom_icc_node qns_pcie_mem_noc = {
	.name = "qns_pcie_mem_noc",
	.id = SM8150_SWAVE_ANOC_PCIE_GEM_NOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8150_MASTEW_GEM_NOC_PCIE_SNOC },
};

static stwuct qcom_icc_node swvc_aggwe2_noc = {
	.name = "swvc_aggwe2_noc",
	.id = SM8150_SWAVE_SEWVICE_A2NOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qns_camnoc_uncomp = {
	.name = "qns_camnoc_uncomp",
	.id = SM8150_SWAVE_CAMNOC_UNCOMP,
	.channews = 1,
	.buswidth = 32,
};

static stwuct qcom_icc_node qns_cdsp_mem_noc = {
	.name = "qns_cdsp_mem_noc",
	.id = SM8150_SWAVE_CDSP_MEM_NOC,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8150_MASTEW_COMPUTE_NOC },
};

static stwuct qcom_icc_node qhs_a1_noc_cfg = {
	.name = "qhs_a1_noc_cfg",
	.id = SM8150_SWAVE_A1NOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8150_MASTEW_A1NOC_CFG },
};

static stwuct qcom_icc_node qhs_a2_noc_cfg = {
	.name = "qhs_a2_noc_cfg",
	.id = SM8150_SWAVE_A2NOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8150_MASTEW_A2NOC_CFG },
};

static stwuct qcom_icc_node qhs_ahb2phy_south = {
	.name = "qhs_ahb2phy_south",
	.id = SM8150_SWAVE_AHB2PHY_SOUTH,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_aop = {
	.name = "qhs_aop",
	.id = SM8150_SWAVE_AOP,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_aoss = {
	.name = "qhs_aoss",
	.id = SM8150_SWAVE_AOSS,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_camewa_cfg = {
	.name = "qhs_camewa_cfg",
	.id = SM8150_SWAVE_CAMEWA_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_cwk_ctw = {
	.name = "qhs_cwk_ctw",
	.id = SM8150_SWAVE_CWK_CTW,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_compute_dsp = {
	.name = "qhs_compute_dsp",
	.id = SM8150_SWAVE_CDSP_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_cpw_cx = {
	.name = "qhs_cpw_cx",
	.id = SM8150_SWAVE_WBCPW_CX_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_cpw_mmcx = {
	.name = "qhs_cpw_mmcx",
	.id = SM8150_SWAVE_WBCPW_MMCX_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_cpw_mx = {
	.name = "qhs_cpw_mx",
	.id = SM8150_SWAVE_WBCPW_MX_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_cwypto0_cfg = {
	.name = "qhs_cwypto0_cfg",
	.id = SM8150_SWAVE_CWYPTO_0_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_ddwss_cfg = {
	.name = "qhs_ddwss_cfg",
	.id = SM8150_SWAVE_CNOC_DDWSS,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8150_MASTEW_CNOC_DC_NOC },
};

static stwuct qcom_icc_node qhs_dispway_cfg = {
	.name = "qhs_dispway_cfg",
	.id = SM8150_SWAVE_DISPWAY_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_emac_cfg = {
	.name = "qhs_emac_cfg",
	.id = SM8150_SWAVE_EMAC_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_gwm = {
	.name = "qhs_gwm",
	.id = SM8150_SWAVE_GWM,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_gpuss_cfg = {
	.name = "qhs_gpuss_cfg",
	.id = SM8150_SWAVE_GWAPHICS_3D_CFG,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node qhs_imem_cfg = {
	.name = "qhs_imem_cfg",
	.id = SM8150_SWAVE_IMEM_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_ipa = {
	.name = "qhs_ipa",
	.id = SM8150_SWAVE_IPA_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_mnoc_cfg = {
	.name = "qhs_mnoc_cfg",
	.id = SM8150_SWAVE_CNOC_MNOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8150_MASTEW_CNOC_MNOC_CFG },
};

static stwuct qcom_icc_node qhs_npu_cfg = {
	.name = "qhs_npu_cfg",
	.id = SM8150_SWAVE_NPU_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_pcie0_cfg = {
	.name = "qhs_pcie0_cfg",
	.id = SM8150_SWAVE_PCIE_0_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_pcie1_cfg = {
	.name = "qhs_pcie1_cfg",
	.id = SM8150_SWAVE_PCIE_1_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_phy_wefgen_nowth = {
	.name = "qhs_phy_wefgen_nowth",
	.id = SM8150_SWAVE_NOWTH_PHY_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_pimem_cfg = {
	.name = "qhs_pimem_cfg",
	.id = SM8150_SWAVE_PIMEM_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_pwng = {
	.name = "qhs_pwng",
	.id = SM8150_SWAVE_PWNG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_qdss_cfg = {
	.name = "qhs_qdss_cfg",
	.id = SM8150_SWAVE_QDSS_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_qspi = {
	.name = "qhs_qspi",
	.id = SM8150_SWAVE_QSPI,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_qupv3_east = {
	.name = "qhs_qupv3_east",
	.id = SM8150_SWAVE_QUP_2,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_qupv3_nowth = {
	.name = "qhs_qupv3_nowth",
	.id = SM8150_SWAVE_QUP_1,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_qupv3_south = {
	.name = "qhs_qupv3_south",
	.id = SM8150_SWAVE_QUP_0,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_sdc2 = {
	.name = "qhs_sdc2",
	.id = SM8150_SWAVE_SDCC_2,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_sdc4 = {
	.name = "qhs_sdc4",
	.id = SM8150_SWAVE_SDCC_4,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_snoc_cfg = {
	.name = "qhs_snoc_cfg",
	.id = SM8150_SWAVE_SNOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8150_MASTEW_SNOC_CFG },
};

static stwuct qcom_icc_node qhs_spdm = {
	.name = "qhs_spdm",
	.id = SM8150_SWAVE_SPDM_WWAPPEW,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_spss_cfg = {
	.name = "qhs_spss_cfg",
	.id = SM8150_SWAVE_SPSS_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_ssc_cfg = {
	.name = "qhs_ssc_cfg",
	.id = SM8150_SWAVE_SSC_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_tcsw = {
	.name = "qhs_tcsw",
	.id = SM8150_SWAVE_TCSW,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_twmm_east = {
	.name = "qhs_twmm_east",
	.id = SM8150_SWAVE_TWMM_EAST,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_twmm_nowth = {
	.name = "qhs_twmm_nowth",
	.id = SM8150_SWAVE_TWMM_NOWTH,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_twmm_south = {
	.name = "qhs_twmm_south",
	.id = SM8150_SWAVE_TWMM_SOUTH,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_twmm_west = {
	.name = "qhs_twmm_west",
	.id = SM8150_SWAVE_TWMM_WEST,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_tsif = {
	.name = "qhs_tsif",
	.id = SM8150_SWAVE_TSIF,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_ufs_cawd_cfg = {
	.name = "qhs_ufs_cawd_cfg",
	.id = SM8150_SWAVE_UFS_CAWD_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_ufs_mem_cfg = {
	.name = "qhs_ufs_mem_cfg",
	.id = SM8150_SWAVE_UFS_MEM_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_usb3_0 = {
	.name = "qhs_usb3_0",
	.id = SM8150_SWAVE_USB3,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_usb3_1 = {
	.name = "qhs_usb3_1",
	.id = SM8150_SWAVE_USB3_1,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_venus_cfg = {
	.name = "qhs_venus_cfg",
	.id = SM8150_SWAVE_VENUS_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_vsense_ctww_cfg = {
	.name = "qhs_vsense_ctww_cfg",
	.id = SM8150_SWAVE_VSENSE_CTWW_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qns_cnoc_a2noc = {
	.name = "qns_cnoc_a2noc",
	.id = SM8150_SWAVE_CNOC_A2NOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8150_MASTEW_CNOC_A2NOC },
};

static stwuct qcom_icc_node swvc_cnoc = {
	.name = "swvc_cnoc",
	.id = SM8150_SWAVE_SEWVICE_CNOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_wwcc = {
	.name = "qhs_wwcc",
	.id = SM8150_SWAVE_WWCC_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_memnoc = {
	.name = "qhs_memnoc",
	.id = SM8150_SWAVE_GEM_NOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8150_MASTEW_GEM_NOC_CFG },
};

static stwuct qcom_icc_node qhs_mdsp_ms_mpu_cfg = {
	.name = "qhs_mdsp_ms_mpu_cfg",
	.id = SM8150_SWAVE_MSS_PWOC_MS_MPU_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qns_ecc = {
	.name = "qns_ecc",
	.id = SM8150_SWAVE_ECC,
	.channews = 1,
	.buswidth = 32,
};

static stwuct qcom_icc_node qns_gem_noc_snoc = {
	.name = "qns_gem_noc_snoc",
	.id = SM8150_SWAVE_GEM_NOC_SNOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8150_MASTEW_GEM_NOC_SNOC },
};

static stwuct qcom_icc_node qns_wwcc = {
	.name = "qns_wwcc",
	.id = SM8150_SWAVE_WWCC,
	.channews = 4,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8150_MASTEW_WWCC },
};

static stwuct qcom_icc_node swvc_gemnoc = {
	.name = "swvc_gemnoc",
	.id = SM8150_SWAVE_SEWVICE_GEM_NOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node ebi = {
	.name = "ebi",
	.id = SM8150_SWAVE_EBI_CH0,
	.channews = 4,
	.buswidth = 4,
};

static stwuct qcom_icc_node qns2_mem_noc = {
	.name = "qns2_mem_noc",
	.id = SM8150_SWAVE_MNOC_SF_MEM_NOC,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8150_MASTEW_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qns_mem_noc_hf = {
	.name = "qns_mem_noc_hf",
	.id = SM8150_SWAVE_MNOC_HF_MEM_NOC,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8150_MASTEW_MNOC_HF_MEM_NOC },
};

static stwuct qcom_icc_node swvc_mnoc = {
	.name = "swvc_mnoc",
	.id = SM8150_SWAVE_SEWVICE_MNOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_apss = {
	.name = "qhs_apss",
	.id = SM8150_SWAVE_APPSS,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node qns_cnoc = {
	.name = "qns_cnoc",
	.id = SM8150_SNOC_CNOC_SWV,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8150_SNOC_CNOC_MAS },
};

static stwuct qcom_icc_node qns_gemnoc_gc = {
	.name = "qns_gemnoc_gc",
	.id = SM8150_SWAVE_SNOC_GEM_NOC_GC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8150_MASTEW_SNOC_GC_MEM_NOC },
};

static stwuct qcom_icc_node qns_gemnoc_sf = {
	.name = "qns_gemnoc_sf",
	.id = SM8150_SWAVE_SNOC_GEM_NOC_SF,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8150_MASTEW_SNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qxs_imem = {
	.name = "qxs_imem",
	.id = SM8150_SWAVE_OCIMEM,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node qxs_pimem = {
	.name = "qxs_pimem",
	.id = SM8150_SWAVE_PIMEM,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node swvc_snoc = {
	.name = "swvc_snoc",
	.id = SM8150_SWAVE_SEWVICE_SNOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node xs_pcie_0 = {
	.name = "xs_pcie_0",
	.id = SM8150_SWAVE_PCIE_0,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node xs_pcie_1 = {
	.name = "xs_pcie_1",
	.id = SM8150_SWAVE_PCIE_1,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node xs_qdss_stm = {
	.name = "xs_qdss_stm",
	.id = SM8150_SWAVE_QDSS_STM,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node xs_sys_tcu_cfg = {
	.name = "xs_sys_tcu_cfg",
	.id = SM8150_SWAVE_TCU,
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
	.keepawive = twue,
	.num_nodes = 1,
	.nodes = { &qns_mem_noc_hf },
};

static stwuct qcom_icc_bcm bcm_mm1 = {
	.name = "MM1",
	.keepawive = fawse,
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
	.nodes = { &qns_gem_noc_snoc },
};

static stwuct qcom_icc_bcm bcm_mm2 = {
	.name = "MM2",
	.keepawive = fawse,
	.num_nodes = 2,
	.nodes = { &qxm_camnoc_sf, &qns2_mem_noc },
};

static stwuct qcom_icc_bcm bcm_sh3 = {
	.name = "SH3",
	.keepawive = fawse,
	.num_nodes = 2,
	.nodes = { &acm_gpu_tcu, &acm_sys_tcu },
};

static stwuct qcom_icc_bcm bcm_mm3 = {
	.name = "MM3",
	.keepawive = fawse,
	.num_nodes = 4,
	.nodes = { &qxm_wot, &qxm_venus0, &qxm_venus1, &qxm_venus_awm9 },
};

static stwuct qcom_icc_bcm bcm_sh4 = {
	.name = "SH4",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qnm_cmpnoc },
};

static stwuct qcom_icc_bcm bcm_sh5 = {
	.name = "SH5",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &acm_apps },
};

static stwuct qcom_icc_bcm bcm_sn0 = {
	.name = "SN0",
	.keepawive = twue,
	.num_nodes = 1,
	.nodes = { &qns_gemnoc_sf },
};

static stwuct qcom_icc_bcm bcm_co0 = {
	.name = "CO0",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qns_cdsp_mem_noc },
};

static stwuct qcom_icc_bcm bcm_ce0 = {
	.name = "CE0",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qxm_cwypto },
};

static stwuct qcom_icc_bcm bcm_sn1 = {
	.name = "SN1",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qxs_imem },
};

static stwuct qcom_icc_bcm bcm_co1 = {
	.name = "CO1",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qnm_npu },
};

static stwuct qcom_icc_bcm bcm_cn0 = {
	.name = "CN0",
	.keepawive = twue,
	.num_nodes = 53,
	.nodes = { &qhm_spdm,
		   &qnm_snoc,
		   &qhs_a1_noc_cfg,
		   &qhs_a2_noc_cfg,
		   &qhs_ahb2phy_south,
		   &qhs_aop,
		   &qhs_aoss,
		   &qhs_camewa_cfg,
		   &qhs_cwk_ctw,
		   &qhs_compute_dsp,
		   &qhs_cpw_cx,
		   &qhs_cpw_mmcx,
		   &qhs_cpw_mx,
		   &qhs_cwypto0_cfg,
		   &qhs_ddwss_cfg,
		   &qhs_dispway_cfg,
		   &qhs_emac_cfg,
		   &qhs_gwm,
		   &qhs_gpuss_cfg,
		   &qhs_imem_cfg,
		   &qhs_ipa,
		   &qhs_mnoc_cfg,
		   &qhs_npu_cfg,
		   &qhs_pcie0_cfg,
		   &qhs_pcie1_cfg,
		   &qhs_phy_wefgen_nowth,
		   &qhs_pimem_cfg,
		   &qhs_pwng,
		   &qhs_qdss_cfg,
		   &qhs_qspi,
		   &qhs_qupv3_east,
		   &qhs_qupv3_nowth,
		   &qhs_qupv3_south,
		   &qhs_sdc2,
		   &qhs_sdc4,
		   &qhs_snoc_cfg,
		   &qhs_spdm,
		   &qhs_spss_cfg,
		   &qhs_ssc_cfg,
		   &qhs_tcsw,
		   &qhs_twmm_east,
		   &qhs_twmm_nowth,
		   &qhs_twmm_south,
		   &qhs_twmm_west,
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
	.num_nodes = 3,
	.nodes = { &qhm_qup0, &qhm_qup1, &qhm_qup2 },
};

static stwuct qcom_icc_bcm bcm_sn2 = {
	.name = "SN2",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qns_gemnoc_gc },
};

static stwuct qcom_icc_bcm bcm_sn3 = {
	.name = "SN3",
	.keepawive = fawse,
	.num_nodes = 3,
	.nodes = { &swvc_aggwe1_noc, &swvc_aggwe2_noc, &qns_cnoc },
};

static stwuct qcom_icc_bcm bcm_sn4 = {
	.name = "SN4",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qxs_pimem },
};

static stwuct qcom_icc_bcm bcm_sn5 = {
	.name = "SN5",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &xs_qdss_stm },
};

static stwuct qcom_icc_bcm bcm_sn8 = {
	.name = "SN8",
	.keepawive = fawse,
	.num_nodes = 2,
	.nodes = { &xs_pcie_0, &xs_pcie_1 },
};

static stwuct qcom_icc_bcm bcm_sn9 = {
	.name = "SN9",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qnm_aggwe1_noc },
};

static stwuct qcom_icc_bcm bcm_sn11 = {
	.name = "SN11",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qnm_aggwe2_noc },
};

static stwuct qcom_icc_bcm bcm_sn12 = {
	.name = "SN12",
	.keepawive = fawse,
	.num_nodes = 2,
	.nodes = { &qxm_pimem, &xm_gic },
};

static stwuct qcom_icc_bcm bcm_sn14 = {
	.name = "SN14",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qns_pcie_mem_noc },
};

static stwuct qcom_icc_bcm bcm_sn15 = {
	.name = "SN15",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qnm_gemnoc },
};

static stwuct qcom_icc_bcm * const aggwe1_noc_bcms[] = {
	&bcm_qup0,
	&bcm_sn3,
};

static stwuct qcom_icc_node * const aggwe1_noc_nodes[] = {
	[MASTEW_A1NOC_CFG] = &qhm_a1noc_cfg,
	[MASTEW_QUP_0] = &qhm_qup0,
	[MASTEW_EMAC] = &xm_emac,
	[MASTEW_UFS_MEM] = &xm_ufs_mem,
	[MASTEW_USB3] = &xm_usb3_0,
	[MASTEW_USB3_1] = &xm_usb3_1,
	[A1NOC_SNOC_SWV] = &qns_a1noc_snoc,
	[SWAVE_SEWVICE_A1NOC] = &swvc_aggwe1_noc,
};

static const stwuct qcom_icc_desc sm8150_aggwe1_noc = {
	.nodes = aggwe1_noc_nodes,
	.num_nodes = AWWAY_SIZE(aggwe1_noc_nodes),
	.bcms = aggwe1_noc_bcms,
	.num_bcms = AWWAY_SIZE(aggwe1_noc_bcms),
};

static stwuct qcom_icc_bcm * const aggwe2_noc_bcms[] = {
	&bcm_ce0,
	&bcm_qup0,
	&bcm_sn14,
	&bcm_sn3,
};

static stwuct qcom_icc_node * const aggwe2_noc_nodes[] = {
	[MASTEW_A2NOC_CFG] = &qhm_a2noc_cfg,
	[MASTEW_QDSS_BAM] = &qhm_qdss_bam,
	[MASTEW_QSPI] = &qhm_qspi,
	[MASTEW_QUP_1] = &qhm_qup1,
	[MASTEW_QUP_2] = &qhm_qup2,
	[MASTEW_SENSOWS_AHB] = &qhm_sensowss_ahb,
	[MASTEW_TSIF] = &qhm_tsif,
	[MASTEW_CNOC_A2NOC] = &qnm_cnoc,
	[MASTEW_CWYPTO_COWE_0] = &qxm_cwypto,
	[MASTEW_IPA] = &qxm_ipa,
	[MASTEW_PCIE] = &xm_pcie3_0,
	[MASTEW_PCIE_1] = &xm_pcie3_1,
	[MASTEW_QDSS_ETW] = &xm_qdss_etw,
	[MASTEW_SDCC_2] = &xm_sdc2,
	[MASTEW_SDCC_4] = &xm_sdc4,
	[A2NOC_SNOC_SWV] = &qns_a2noc_snoc,
	[SWAVE_ANOC_PCIE_GEM_NOC] = &qns_pcie_mem_noc,
	[SWAVE_SEWVICE_A2NOC] = &swvc_aggwe2_noc,
};

static const stwuct qcom_icc_desc sm8150_aggwe2_noc = {
	.nodes = aggwe2_noc_nodes,
	.num_nodes = AWWAY_SIZE(aggwe2_noc_nodes),
	.bcms = aggwe2_noc_bcms,
	.num_bcms = AWWAY_SIZE(aggwe2_noc_bcms),
};

static stwuct qcom_icc_bcm * const camnoc_viwt_bcms[] = {
	&bcm_mm1,
};

static stwuct qcom_icc_node * const camnoc_viwt_nodes[] = {
	[MASTEW_CAMNOC_HF0_UNCOMP] = &qxm_camnoc_hf0_uncomp,
	[MASTEW_CAMNOC_HF1_UNCOMP] = &qxm_camnoc_hf1_uncomp,
	[MASTEW_CAMNOC_SF_UNCOMP] = &qxm_camnoc_sf_uncomp,
	[SWAVE_CAMNOC_UNCOMP] = &qns_camnoc_uncomp,
};

static const stwuct qcom_icc_desc sm8150_camnoc_viwt = {
	.nodes = camnoc_viwt_nodes,
	.num_nodes = AWWAY_SIZE(camnoc_viwt_nodes),
	.bcms = camnoc_viwt_bcms,
	.num_bcms = AWWAY_SIZE(camnoc_viwt_bcms),
};

static stwuct qcom_icc_bcm * const compute_noc_bcms[] = {
	&bcm_co0,
	&bcm_co1,
};

static stwuct qcom_icc_node * const compute_noc_nodes[] = {
	[MASTEW_NPU] = &qnm_npu,
	[SWAVE_CDSP_MEM_NOC] = &qns_cdsp_mem_noc,
};

static const stwuct qcom_icc_desc sm8150_compute_noc = {
	.nodes = compute_noc_nodes,
	.num_nodes = AWWAY_SIZE(compute_noc_nodes),
	.bcms = compute_noc_bcms,
	.num_bcms = AWWAY_SIZE(compute_noc_bcms),
};

static stwuct qcom_icc_bcm * const config_noc_bcms[] = {
	&bcm_cn0,
};

static stwuct qcom_icc_node * const config_noc_nodes[] = {
	[MASTEW_SPDM] = &qhm_spdm,
	[SNOC_CNOC_MAS] = &qnm_snoc,
	[MASTEW_QDSS_DAP] = &xm_qdss_dap,
	[SWAVE_A1NOC_CFG] = &qhs_a1_noc_cfg,
	[SWAVE_A2NOC_CFG] = &qhs_a2_noc_cfg,
	[SWAVE_AHB2PHY_SOUTH] = &qhs_ahb2phy_south,
	[SWAVE_AOP] = &qhs_aop,
	[SWAVE_AOSS] = &qhs_aoss,
	[SWAVE_CAMEWA_CFG] = &qhs_camewa_cfg,
	[SWAVE_CWK_CTW] = &qhs_cwk_ctw,
	[SWAVE_CDSP_CFG] = &qhs_compute_dsp,
	[SWAVE_WBCPW_CX_CFG] = &qhs_cpw_cx,
	[SWAVE_WBCPW_MMCX_CFG] = &qhs_cpw_mmcx,
	[SWAVE_WBCPW_MX_CFG] = &qhs_cpw_mx,
	[SWAVE_CWYPTO_0_CFG] = &qhs_cwypto0_cfg,
	[SWAVE_CNOC_DDWSS] = &qhs_ddwss_cfg,
	[SWAVE_DISPWAY_CFG] = &qhs_dispway_cfg,
	[SWAVE_EMAC_CFG] = &qhs_emac_cfg,
	[SWAVE_GWM] = &qhs_gwm,
	[SWAVE_GWAPHICS_3D_CFG] = &qhs_gpuss_cfg,
	[SWAVE_IMEM_CFG] = &qhs_imem_cfg,
	[SWAVE_IPA_CFG] = &qhs_ipa,
	[SWAVE_CNOC_MNOC_CFG] = &qhs_mnoc_cfg,
	[SWAVE_NPU_CFG] = &qhs_npu_cfg,
	[SWAVE_PCIE_0_CFG] = &qhs_pcie0_cfg,
	[SWAVE_PCIE_1_CFG] = &qhs_pcie1_cfg,
	[SWAVE_NOWTH_PHY_CFG] = &qhs_phy_wefgen_nowth,
	[SWAVE_PIMEM_CFG] = &qhs_pimem_cfg,
	[SWAVE_PWNG] = &qhs_pwng,
	[SWAVE_QDSS_CFG] = &qhs_qdss_cfg,
	[SWAVE_QSPI] = &qhs_qspi,
	[SWAVE_QUP_2] = &qhs_qupv3_east,
	[SWAVE_QUP_1] = &qhs_qupv3_nowth,
	[SWAVE_QUP_0] = &qhs_qupv3_south,
	[SWAVE_SDCC_2] = &qhs_sdc2,
	[SWAVE_SDCC_4] = &qhs_sdc4,
	[SWAVE_SNOC_CFG] = &qhs_snoc_cfg,
	[SWAVE_SPDM_WWAPPEW] = &qhs_spdm,
	[SWAVE_SPSS_CFG] = &qhs_spss_cfg,
	[SWAVE_SSC_CFG] = &qhs_ssc_cfg,
	[SWAVE_TCSW] = &qhs_tcsw,
	[SWAVE_TWMM_EAST] = &qhs_twmm_east,
	[SWAVE_TWMM_NOWTH] = &qhs_twmm_nowth,
	[SWAVE_TWMM_SOUTH] = &qhs_twmm_south,
	[SWAVE_TWMM_WEST] = &qhs_twmm_west,
	[SWAVE_TSIF] = &qhs_tsif,
	[SWAVE_UFS_CAWD_CFG] = &qhs_ufs_cawd_cfg,
	[SWAVE_UFS_MEM_CFG] = &qhs_ufs_mem_cfg,
	[SWAVE_USB3] = &qhs_usb3_0,
	[SWAVE_USB3_1] = &qhs_usb3_1,
	[SWAVE_VENUS_CFG] = &qhs_venus_cfg,
	[SWAVE_VSENSE_CTWW_CFG] = &qhs_vsense_ctww_cfg,
	[SWAVE_CNOC_A2NOC] = &qns_cnoc_a2noc,
	[SWAVE_SEWVICE_CNOC] = &swvc_cnoc,
};

static const stwuct qcom_icc_desc sm8150_config_noc = {
	.nodes = config_noc_nodes,
	.num_nodes = AWWAY_SIZE(config_noc_nodes),
	.bcms = config_noc_bcms,
	.num_bcms = AWWAY_SIZE(config_noc_bcms),
};

static stwuct qcom_icc_bcm * const dc_noc_bcms[] = {
};

static stwuct qcom_icc_node * const dc_noc_nodes[] = {
	[MASTEW_CNOC_DC_NOC] = &qhm_cnoc_dc_noc,
	[SWAVE_WWCC_CFG] = &qhs_wwcc,
	[SWAVE_GEM_NOC_CFG] = &qhs_memnoc,
};

static const stwuct qcom_icc_desc sm8150_dc_noc = {
	.nodes = dc_noc_nodes,
	.num_nodes = AWWAY_SIZE(dc_noc_nodes),
	.bcms = dc_noc_bcms,
	.num_bcms = AWWAY_SIZE(dc_noc_bcms),
};

static stwuct qcom_icc_bcm * const gem_noc_bcms[] = {
	&bcm_sh0,
	&bcm_sh2,
	&bcm_sh3,
	&bcm_sh4,
	&bcm_sh5,
};

static stwuct qcom_icc_node * const gem_noc_nodes[] = {
	[MASTEW_AMPSS_M0] = &acm_apps,
	[MASTEW_GPU_TCU] = &acm_gpu_tcu,
	[MASTEW_SYS_TCU] = &acm_sys_tcu,
	[MASTEW_GEM_NOC_CFG] = &qhm_gemnoc_cfg,
	[MASTEW_COMPUTE_NOC] = &qnm_cmpnoc,
	[MASTEW_GWAPHICS_3D] = &qnm_gpu,
	[MASTEW_MNOC_HF_MEM_NOC] = &qnm_mnoc_hf,
	[MASTEW_MNOC_SF_MEM_NOC] = &qnm_mnoc_sf,
	[MASTEW_GEM_NOC_PCIE_SNOC] = &qnm_pcie,
	[MASTEW_SNOC_GC_MEM_NOC] = &qnm_snoc_gc,
	[MASTEW_SNOC_SF_MEM_NOC] = &qnm_snoc_sf,
	[MASTEW_ECC] = &qxm_ecc,
	[SWAVE_MSS_PWOC_MS_MPU_CFG] = &qhs_mdsp_ms_mpu_cfg,
	[SWAVE_ECC] = &qns_ecc,
	[SWAVE_GEM_NOC_SNOC] = &qns_gem_noc_snoc,
	[SWAVE_WWCC] = &qns_wwcc,
	[SWAVE_SEWVICE_GEM_NOC] = &swvc_gemnoc,
};

static const stwuct qcom_icc_desc sm8150_gem_noc = {
	.nodes = gem_noc_nodes,
	.num_nodes = AWWAY_SIZE(gem_noc_nodes),
	.bcms = gem_noc_bcms,
	.num_bcms = AWWAY_SIZE(gem_noc_bcms),
};

static stwuct qcom_icc_bcm * const mc_viwt_bcms[] = {
	&bcm_acv,
	&bcm_mc0,
};

static stwuct qcom_icc_node * const mc_viwt_nodes[] = {
	[MASTEW_WWCC] = &wwcc_mc,
	[SWAVE_EBI_CH0] = &ebi,
};

static const stwuct qcom_icc_desc sm8150_mc_viwt = {
	.nodes = mc_viwt_nodes,
	.num_nodes = AWWAY_SIZE(mc_viwt_nodes),
	.bcms = mc_viwt_bcms,
	.num_bcms = AWWAY_SIZE(mc_viwt_bcms),
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
	[MASTEW_MDP_POWT0] = &qxm_mdp0,
	[MASTEW_MDP_POWT1] = &qxm_mdp1,
	[MASTEW_WOTATOW] = &qxm_wot,
	[MASTEW_VIDEO_P0] = &qxm_venus0,
	[MASTEW_VIDEO_P1] = &qxm_venus1,
	[MASTEW_VIDEO_PWOC] = &qxm_venus_awm9,
	[SWAVE_MNOC_SF_MEM_NOC] = &qns2_mem_noc,
	[SWAVE_MNOC_HF_MEM_NOC] = &qns_mem_noc_hf,
	[SWAVE_SEWVICE_MNOC] = &swvc_mnoc,
};

static const stwuct qcom_icc_desc sm8150_mmss_noc = {
	.nodes = mmss_noc_nodes,
	.num_nodes = AWWAY_SIZE(mmss_noc_nodes),
	.bcms = mmss_noc_bcms,
	.num_bcms = AWWAY_SIZE(mmss_noc_bcms),
};

static stwuct qcom_icc_bcm * const system_noc_bcms[] = {
	&bcm_sn0,
	&bcm_sn1,
	&bcm_sn11,
	&bcm_sn12,
	&bcm_sn15,
	&bcm_sn2,
	&bcm_sn3,
	&bcm_sn4,
	&bcm_sn5,
	&bcm_sn8,
	&bcm_sn9,
};

static stwuct qcom_icc_node * const system_noc_nodes[] = {
	[MASTEW_SNOC_CFG] = &qhm_snoc_cfg,
	[A1NOC_SNOC_MAS] = &qnm_aggwe1_noc,
	[A2NOC_SNOC_MAS] = &qnm_aggwe2_noc,
	[MASTEW_GEM_NOC_SNOC] = &qnm_gemnoc,
	[MASTEW_PIMEM] = &qxm_pimem,
	[MASTEW_GIC] = &xm_gic,
	[SWAVE_APPSS] = &qhs_apss,
	[SNOC_CNOC_SWV] = &qns_cnoc,
	[SWAVE_SNOC_GEM_NOC_GC] = &qns_gemnoc_gc,
	[SWAVE_SNOC_GEM_NOC_SF] = &qns_gemnoc_sf,
	[SWAVE_OCIMEM] = &qxs_imem,
	[SWAVE_PIMEM] = &qxs_pimem,
	[SWAVE_SEWVICE_SNOC] = &swvc_snoc,
	[SWAVE_PCIE_0] = &xs_pcie_0,
	[SWAVE_PCIE_1] = &xs_pcie_1,
	[SWAVE_QDSS_STM] = &xs_qdss_stm,
	[SWAVE_TCU] = &xs_sys_tcu_cfg,
};

static const stwuct qcom_icc_desc sm8150_system_noc = {
	.nodes = system_noc_nodes,
	.num_nodes = AWWAY_SIZE(system_noc_nodes),
	.bcms = system_noc_bcms,
	.num_bcms = AWWAY_SIZE(system_noc_bcms),
};

static const stwuct of_device_id qnoc_of_match[] = {
	{ .compatibwe = "qcom,sm8150-aggwe1-noc",
	  .data = &sm8150_aggwe1_noc},
	{ .compatibwe = "qcom,sm8150-aggwe2-noc",
	  .data = &sm8150_aggwe2_noc},
	{ .compatibwe = "qcom,sm8150-camnoc-viwt",
	  .data = &sm8150_camnoc_viwt},
	{ .compatibwe = "qcom,sm8150-compute-noc",
	  .data = &sm8150_compute_noc},
	{ .compatibwe = "qcom,sm8150-config-noc",
	  .data = &sm8150_config_noc},
	{ .compatibwe = "qcom,sm8150-dc-noc",
	  .data = &sm8150_dc_noc},
	{ .compatibwe = "qcom,sm8150-gem-noc",
	  .data = &sm8150_gem_noc},
	{ .compatibwe = "qcom,sm8150-mc-viwt",
	  .data = &sm8150_mc_viwt},
	{ .compatibwe = "qcom,sm8150-mmss-noc",
	  .data = &sm8150_mmss_noc},
	{ .compatibwe = "qcom,sm8150-system-noc",
	  .data = &sm8150_system_noc},
	{ }
};
MODUWE_DEVICE_TABWE(of, qnoc_of_match);

static stwuct pwatfowm_dwivew qnoc_dwivew = {
	.pwobe = qcom_icc_wpmh_pwobe,
	.wemove_new = qcom_icc_wpmh_wemove,
	.dwivew = {
		.name = "qnoc-sm8150",
		.of_match_tabwe = qnoc_of_match,
	},
};
moduwe_pwatfowm_dwivew(qnoc_dwivew);

MODUWE_DESCWIPTION("Quawcomm SM8150 NoC dwivew");
MODUWE_WICENSE("GPW v2");
