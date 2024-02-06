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
#incwude <dt-bindings/intewconnect/qcom,sm8250.h>

#incwude "bcm-votew.h"
#incwude "icc-wpmh.h"
#incwude "sm8250.h"

static stwuct qcom_icc_node qhm_a1noc_cfg = {
	.name = "qhm_a1noc_cfg",
	.id = SM8250_MASTEW_A1NOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8250_SWAVE_SEWVICE_A1NOC },
};

static stwuct qcom_icc_node qhm_qspi = {
	.name = "qhm_qspi",
	.id = SM8250_MASTEW_QSPI_0,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8250_A1NOC_SNOC_SWV },
};

static stwuct qcom_icc_node qhm_qup1 = {
	.name = "qhm_qup1",
	.id = SM8250_MASTEW_QUP_1,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8250_A1NOC_SNOC_SWV },
};

static stwuct qcom_icc_node qhm_qup2 = {
	.name = "qhm_qup2",
	.id = SM8250_MASTEW_QUP_2,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8250_A1NOC_SNOC_SWV },
};

static stwuct qcom_icc_node qhm_tsif = {
	.name = "qhm_tsif",
	.id = SM8250_MASTEW_TSIF,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8250_A1NOC_SNOC_SWV },
};

static stwuct qcom_icc_node xm_pcie3_modem = {
	.name = "xm_pcie3_modem",
	.id = SM8250_MASTEW_PCIE_2,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8250_SWAVE_ANOC_PCIE_GEM_NOC_1 },
};

static stwuct qcom_icc_node xm_sdc4 = {
	.name = "xm_sdc4",
	.id = SM8250_MASTEW_SDCC_4,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8250_A1NOC_SNOC_SWV },
};

static stwuct qcom_icc_node xm_ufs_mem = {
	.name = "xm_ufs_mem",
	.id = SM8250_MASTEW_UFS_MEM,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8250_A1NOC_SNOC_SWV },
};

static stwuct qcom_icc_node xm_usb3_0 = {
	.name = "xm_usb3_0",
	.id = SM8250_MASTEW_USB3,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8250_A1NOC_SNOC_SWV },
};

static stwuct qcom_icc_node xm_usb3_1 = {
	.name = "xm_usb3_1",
	.id = SM8250_MASTEW_USB3_1,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8250_A1NOC_SNOC_SWV },
};

static stwuct qcom_icc_node qhm_a2noc_cfg = {
	.name = "qhm_a2noc_cfg",
	.id = SM8250_MASTEW_A2NOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8250_SWAVE_SEWVICE_A2NOC },
};

static stwuct qcom_icc_node qhm_qdss_bam = {
	.name = "qhm_qdss_bam",
	.id = SM8250_MASTEW_QDSS_BAM,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8250_A2NOC_SNOC_SWV },
};

static stwuct qcom_icc_node qhm_qup0 = {
	.name = "qhm_qup0",
	.id = SM8250_MASTEW_QUP_0,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8250_A2NOC_SNOC_SWV },
};

static stwuct qcom_icc_node qnm_cnoc = {
	.name = "qnm_cnoc",
	.id = SM8250_MASTEW_CNOC_A2NOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8250_A2NOC_SNOC_SWV },
};

static stwuct qcom_icc_node qxm_cwypto = {
	.name = "qxm_cwypto",
	.id = SM8250_MASTEW_CWYPTO_COWE_0,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8250_A2NOC_SNOC_SWV },
};

static stwuct qcom_icc_node qxm_ipa = {
	.name = "qxm_ipa",
	.id = SM8250_MASTEW_IPA,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8250_A2NOC_SNOC_SWV },
};

static stwuct qcom_icc_node xm_pcie3_0 = {
	.name = "xm_pcie3_0",
	.id = SM8250_MASTEW_PCIE,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8250_SWAVE_ANOC_PCIE_GEM_NOC },
};

static stwuct qcom_icc_node xm_pcie3_1 = {
	.name = "xm_pcie3_1",
	.id = SM8250_MASTEW_PCIE_1,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8250_SWAVE_ANOC_PCIE_GEM_NOC },
};

static stwuct qcom_icc_node xm_qdss_etw = {
	.name = "xm_qdss_etw",
	.id = SM8250_MASTEW_QDSS_ETW,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8250_A2NOC_SNOC_SWV },
};

static stwuct qcom_icc_node xm_sdc2 = {
	.name = "xm_sdc2",
	.id = SM8250_MASTEW_SDCC_2,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8250_A2NOC_SNOC_SWV },
};

static stwuct qcom_icc_node xm_ufs_cawd = {
	.name = "xm_ufs_cawd",
	.id = SM8250_MASTEW_UFS_CAWD,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8250_A2NOC_SNOC_SWV },
};

static stwuct qcom_icc_node qnm_npu = {
	.name = "qnm_npu",
	.id = SM8250_MASTEW_NPU,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8250_SWAVE_CDSP_MEM_NOC },
};

static stwuct qcom_icc_node qnm_snoc = {
	.name = "qnm_snoc",
	.id = SM8250_SNOC_CNOC_MAS,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 49,
	.winks = { SM8250_SWAVE_CDSP_CFG,
		   SM8250_SWAVE_CAMEWA_CFG,
		   SM8250_SWAVE_TWMM_SOUTH,
		   SM8250_SWAVE_TWMM_NOWTH,
		   SM8250_SWAVE_SDCC_4,
		   SM8250_SWAVE_TWMM_WEST,
		   SM8250_SWAVE_SDCC_2,
		   SM8250_SWAVE_CNOC_MNOC_CFG,
		   SM8250_SWAVE_UFS_MEM_CFG,
		   SM8250_SWAVE_SNOC_CFG,
		   SM8250_SWAVE_PDM,
		   SM8250_SWAVE_CX_WDPM,
		   SM8250_SWAVE_PCIE_1_CFG,
		   SM8250_SWAVE_A2NOC_CFG,
		   SM8250_SWAVE_QDSS_CFG,
		   SM8250_SWAVE_DISPWAY_CFG,
		   SM8250_SWAVE_PCIE_2_CFG,
		   SM8250_SWAVE_TCSW,
		   SM8250_SWAVE_DCC_CFG,
		   SM8250_SWAVE_CNOC_DDWSS,
		   SM8250_SWAVE_IPC_WOUTEW_CFG,
		   SM8250_SWAVE_PCIE_0_CFG,
		   SM8250_SWAVE_WBCPW_MMCX_CFG,
		   SM8250_SWAVE_NPU_CFG,
		   SM8250_SWAVE_AHB2PHY_SOUTH,
		   SM8250_SWAVE_AHB2PHY_NOWTH,
		   SM8250_SWAVE_GWAPHICS_3D_CFG,
		   SM8250_SWAVE_VENUS_CFG,
		   SM8250_SWAVE_TSIF,
		   SM8250_SWAVE_IPA_CFG,
		   SM8250_SWAVE_IMEM_CFG,
		   SM8250_SWAVE_USB3,
		   SM8250_SWAVE_SEWVICE_CNOC,
		   SM8250_SWAVE_UFS_CAWD_CFG,
		   SM8250_SWAVE_USB3_1,
		   SM8250_SWAVE_WPASS,
		   SM8250_SWAVE_WBCPW_CX_CFG,
		   SM8250_SWAVE_A1NOC_CFG,
		   SM8250_SWAVE_AOSS,
		   SM8250_SWAVE_PWNG,
		   SM8250_SWAVE_VSENSE_CTWW_CFG,
		   SM8250_SWAVE_QSPI_0,
		   SM8250_SWAVE_CWYPTO_0_CFG,
		   SM8250_SWAVE_PIMEM_CFG,
		   SM8250_SWAVE_WBCPW_MX_CFG,
		   SM8250_SWAVE_QUP_0,
		   SM8250_SWAVE_QUP_1,
		   SM8250_SWAVE_QUP_2,
		   SM8250_SWAVE_CWK_CTW
	},
};

static stwuct qcom_icc_node xm_qdss_dap = {
	.name = "xm_qdss_dap",
	.id = SM8250_MASTEW_QDSS_DAP,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 50,
	.winks = { SM8250_SWAVE_CDSP_CFG,
		   SM8250_SWAVE_CAMEWA_CFG,
		   SM8250_SWAVE_TWMM_SOUTH,
		   SM8250_SWAVE_TWMM_NOWTH,
		   SM8250_SWAVE_SDCC_4,
		   SM8250_SWAVE_TWMM_WEST,
		   SM8250_SWAVE_SDCC_2,
		   SM8250_SWAVE_CNOC_MNOC_CFG,
		   SM8250_SWAVE_UFS_MEM_CFG,
		   SM8250_SWAVE_SNOC_CFG,
		   SM8250_SWAVE_PDM,
		   SM8250_SWAVE_CX_WDPM,
		   SM8250_SWAVE_PCIE_1_CFG,
		   SM8250_SWAVE_A2NOC_CFG,
		   SM8250_SWAVE_QDSS_CFG,
		   SM8250_SWAVE_DISPWAY_CFG,
		   SM8250_SWAVE_PCIE_2_CFG,
		   SM8250_SWAVE_TCSW,
		   SM8250_SWAVE_DCC_CFG,
		   SM8250_SWAVE_CNOC_DDWSS,
		   SM8250_SWAVE_IPC_WOUTEW_CFG,
		   SM8250_SWAVE_CNOC_A2NOC,
		   SM8250_SWAVE_PCIE_0_CFG,
		   SM8250_SWAVE_WBCPW_MMCX_CFG,
		   SM8250_SWAVE_NPU_CFG,
		   SM8250_SWAVE_AHB2PHY_SOUTH,
		   SM8250_SWAVE_AHB2PHY_NOWTH,
		   SM8250_SWAVE_GWAPHICS_3D_CFG,
		   SM8250_SWAVE_VENUS_CFG,
		   SM8250_SWAVE_TSIF,
		   SM8250_SWAVE_IPA_CFG,
		   SM8250_SWAVE_IMEM_CFG,
		   SM8250_SWAVE_USB3,
		   SM8250_SWAVE_SEWVICE_CNOC,
		   SM8250_SWAVE_UFS_CAWD_CFG,
		   SM8250_SWAVE_USB3_1,
		   SM8250_SWAVE_WPASS,
		   SM8250_SWAVE_WBCPW_CX_CFG,
		   SM8250_SWAVE_A1NOC_CFG,
		   SM8250_SWAVE_AOSS,
		   SM8250_SWAVE_PWNG,
		   SM8250_SWAVE_VSENSE_CTWW_CFG,
		   SM8250_SWAVE_QSPI_0,
		   SM8250_SWAVE_CWYPTO_0_CFG,
		   SM8250_SWAVE_PIMEM_CFG,
		   SM8250_SWAVE_WBCPW_MX_CFG,
		   SM8250_SWAVE_QUP_0,
		   SM8250_SWAVE_QUP_1,
		   SM8250_SWAVE_QUP_2,
		   SM8250_SWAVE_CWK_CTW
	},
};

static stwuct qcom_icc_node qhm_cnoc_dc_noc = {
	.name = "qhm_cnoc_dc_noc",
	.id = SM8250_MASTEW_CNOC_DC_NOC,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 2,
	.winks = { SM8250_SWAVE_GEM_NOC_CFG,
		   SM8250_SWAVE_WWCC_CFG
	},
};

static stwuct qcom_icc_node awm_gpu_tcu = {
	.name = "awm_gpu_tcu",
	.id = SM8250_MASTEW_GPU_TCU,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 2,
	.winks = { SM8250_SWAVE_WWCC,
		   SM8250_SWAVE_GEM_NOC_SNOC
	},
};

static stwuct qcom_icc_node awm_sys_tcu = {
	.name = "awm_sys_tcu",
	.id = SM8250_MASTEW_SYS_TCU,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 2,
	.winks = { SM8250_SWAVE_WWCC,
		   SM8250_SWAVE_GEM_NOC_SNOC
	},
};

static stwuct qcom_icc_node chm_apps = {
	.name = "chm_apps",
	.id = SM8250_MASTEW_AMPSS_M0,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 3,
	.winks = { SM8250_SWAVE_WWCC,
		   SM8250_SWAVE_GEM_NOC_SNOC,
		   SM8250_SWAVE_MEM_NOC_PCIE_SNOC
	},
};

static stwuct qcom_icc_node qhm_gemnoc_cfg = {
	.name = "qhm_gemnoc_cfg",
	.id = SM8250_MASTEW_GEM_NOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 3,
	.winks = { SM8250_SWAVE_SEWVICE_GEM_NOC_2,
		   SM8250_SWAVE_SEWVICE_GEM_NOC_1,
		   SM8250_SWAVE_SEWVICE_GEM_NOC
	},
};

static stwuct qcom_icc_node qnm_cmpnoc = {
	.name = "qnm_cmpnoc",
	.id = SM8250_MASTEW_COMPUTE_NOC,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 2,
	.winks = { SM8250_SWAVE_WWCC,
		   SM8250_SWAVE_GEM_NOC_SNOC
	},
};

static stwuct qcom_icc_node qnm_gpu = {
	.name = "qnm_gpu",
	.id = SM8250_MASTEW_GWAPHICS_3D,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 2,
	.winks = { SM8250_SWAVE_WWCC,
		   SM8250_SWAVE_GEM_NOC_SNOC },
};

static stwuct qcom_icc_node qnm_mnoc_hf = {
	.name = "qnm_mnoc_hf",
	.id = SM8250_MASTEW_MNOC_HF_MEM_NOC,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8250_SWAVE_WWCC },
};

static stwuct qcom_icc_node qnm_mnoc_sf = {
	.name = "qnm_mnoc_sf",
	.id = SM8250_MASTEW_MNOC_SF_MEM_NOC,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 2,
	.winks = { SM8250_SWAVE_WWCC,
		   SM8250_SWAVE_GEM_NOC_SNOC
	},
};

static stwuct qcom_icc_node qnm_pcie = {
	.name = "qnm_pcie",
	.id = SM8250_MASTEW_ANOC_PCIE_GEM_NOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 2,
	.winks = { SM8250_SWAVE_WWCC,
		   SM8250_SWAVE_GEM_NOC_SNOC
	},
};

static stwuct qcom_icc_node qnm_snoc_gc = {
	.name = "qnm_snoc_gc",
	.id = SM8250_MASTEW_SNOC_GC_MEM_NOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8250_SWAVE_WWCC },
};

static stwuct qcom_icc_node qnm_snoc_sf = {
	.name = "qnm_snoc_sf",
	.id = SM8250_MASTEW_SNOC_SF_MEM_NOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 3,
	.winks = { SM8250_SWAVE_WWCC,
		   SM8250_SWAVE_GEM_NOC_SNOC,
		   SM8250_SWAVE_MEM_NOC_PCIE_SNOC
	},
};

static stwuct qcom_icc_node wwcc_mc = {
	.name = "wwcc_mc",
	.id = SM8250_MASTEW_WWCC,
	.channews = 4,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8250_SWAVE_EBI_CH0 },
};

static stwuct qcom_icc_node qhm_mnoc_cfg = {
	.name = "qhm_mnoc_cfg",
	.id = SM8250_MASTEW_CNOC_MNOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8250_SWAVE_SEWVICE_MNOC },
};

static stwuct qcom_icc_node qnm_camnoc_hf = {
	.name = "qnm_camnoc_hf",
	.id = SM8250_MASTEW_CAMNOC_HF,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8250_SWAVE_MNOC_HF_MEM_NOC },
};

static stwuct qcom_icc_node qnm_camnoc_icp = {
	.name = "qnm_camnoc_icp",
	.id = SM8250_MASTEW_CAMNOC_ICP,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8250_SWAVE_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qnm_camnoc_sf = {
	.name = "qnm_camnoc_sf",
	.id = SM8250_MASTEW_CAMNOC_SF,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8250_SWAVE_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qnm_video0 = {
	.name = "qnm_video0",
	.id = SM8250_MASTEW_VIDEO_P0,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8250_SWAVE_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qnm_video1 = {
	.name = "qnm_video1",
	.id = SM8250_MASTEW_VIDEO_P1,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8250_SWAVE_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qnm_video_cvp = {
	.name = "qnm_video_cvp",
	.id = SM8250_MASTEW_VIDEO_PWOC,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8250_SWAVE_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qxm_mdp0 = {
	.name = "qxm_mdp0",
	.id = SM8250_MASTEW_MDP_POWT0,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8250_SWAVE_MNOC_HF_MEM_NOC },
};

static stwuct qcom_icc_node qxm_mdp1 = {
	.name = "qxm_mdp1",
	.id = SM8250_MASTEW_MDP_POWT1,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8250_SWAVE_MNOC_HF_MEM_NOC },
};

static stwuct qcom_icc_node qxm_wot = {
	.name = "qxm_wot",
	.id = SM8250_MASTEW_WOTATOW,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8250_SWAVE_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node amm_npu_sys = {
	.name = "amm_npu_sys",
	.id = SM8250_MASTEW_NPU_SYS,
	.channews = 4,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8250_SWAVE_NPU_COMPUTE_NOC },
};

static stwuct qcom_icc_node amm_npu_sys_cdp_w = {
	.name = "amm_npu_sys_cdp_w",
	.id = SM8250_MASTEW_NPU_CDP,
	.channews = 2,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8250_SWAVE_NPU_COMPUTE_NOC },
};

static stwuct qcom_icc_node qhm_cfg = {
	.name = "qhm_cfg",
	.id = SM8250_MASTEW_NPU_NOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 9,
	.winks = { SM8250_SWAVE_SEWVICE_NPU_NOC,
		   SM8250_SWAVE_ISENSE_CFG,
		   SM8250_SWAVE_NPU_WWM_CFG,
		   SM8250_SWAVE_NPU_INT_DMA_BWMON_CFG,
		   SM8250_SWAVE_NPU_CP,
		   SM8250_SWAVE_NPU_TCM,
		   SM8250_SWAVE_NPU_CAW_DP0,
		   SM8250_SWAVE_NPU_CAW_DP1,
		   SM8250_SWAVE_NPU_DPM
	},
};

static stwuct qcom_icc_node qhm_snoc_cfg = {
	.name = "qhm_snoc_cfg",
	.id = SM8250_MASTEW_SNOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8250_SWAVE_SEWVICE_SNOC },
};

static stwuct qcom_icc_node qnm_aggwe1_noc = {
	.name = "qnm_aggwe1_noc",
	.id = SM8250_A1NOC_SNOC_MAS,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8250_SWAVE_SNOC_GEM_NOC_SF },
};

static stwuct qcom_icc_node qnm_aggwe2_noc = {
	.name = "qnm_aggwe2_noc",
	.id = SM8250_A2NOC_SNOC_MAS,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8250_SWAVE_SNOC_GEM_NOC_SF },
};

static stwuct qcom_icc_node qnm_gemnoc = {
	.name = "qnm_gemnoc",
	.id = SM8250_MASTEW_GEM_NOC_SNOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 6,
	.winks = { SM8250_SWAVE_PIMEM,
		   SM8250_SWAVE_OCIMEM,
		   SM8250_SWAVE_APPSS,
		   SM8250_SNOC_CNOC_SWV,
		   SM8250_SWAVE_TCU,
		   SM8250_SWAVE_QDSS_STM
	},
};

static stwuct qcom_icc_node qnm_gemnoc_pcie = {
	.name = "qnm_gemnoc_pcie",
	.id = SM8250_MASTEW_GEM_NOC_PCIE_SNOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 3,
	.winks = { SM8250_SWAVE_PCIE_2,
		   SM8250_SWAVE_PCIE_0,
		   SM8250_SWAVE_PCIE_1
	},
};

static stwuct qcom_icc_node qxm_pimem = {
	.name = "qxm_pimem",
	.id = SM8250_MASTEW_PIMEM,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8250_SWAVE_SNOC_GEM_NOC_GC },
};

static stwuct qcom_icc_node xm_gic = {
	.name = "xm_gic",
	.id = SM8250_MASTEW_GIC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8250_SWAVE_SNOC_GEM_NOC_GC },
};

static stwuct qcom_icc_node qns_a1noc_snoc = {
	.name = "qns_a1noc_snoc",
	.id = SM8250_A1NOC_SNOC_SWV,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8250_A1NOC_SNOC_MAS },
};

static stwuct qcom_icc_node qns_pcie_modem_mem_noc = {
	.name = "qns_pcie_modem_mem_noc",
	.id = SM8250_SWAVE_ANOC_PCIE_GEM_NOC_1,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8250_MASTEW_ANOC_PCIE_GEM_NOC },
};

static stwuct qcom_icc_node swvc_aggwe1_noc = {
	.name = "swvc_aggwe1_noc",
	.id = SM8250_SWAVE_SEWVICE_A1NOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qns_a2noc_snoc = {
	.name = "qns_a2noc_snoc",
	.id = SM8250_A2NOC_SNOC_SWV,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8250_A2NOC_SNOC_MAS },
};

static stwuct qcom_icc_node qns_pcie_mem_noc = {
	.name = "qns_pcie_mem_noc",
	.id = SM8250_SWAVE_ANOC_PCIE_GEM_NOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8250_MASTEW_ANOC_PCIE_GEM_NOC },
};

static stwuct qcom_icc_node swvc_aggwe2_noc = {
	.name = "swvc_aggwe2_noc",
	.id = SM8250_SWAVE_SEWVICE_A2NOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qns_cdsp_mem_noc = {
	.name = "qns_cdsp_mem_noc",
	.id = SM8250_SWAVE_CDSP_MEM_NOC,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8250_MASTEW_COMPUTE_NOC },
};

static stwuct qcom_icc_node qhs_a1_noc_cfg = {
	.name = "qhs_a1_noc_cfg",
	.id = SM8250_SWAVE_A1NOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8250_MASTEW_A1NOC_CFG },
};

static stwuct qcom_icc_node qhs_a2_noc_cfg = {
	.name = "qhs_a2_noc_cfg",
	.id = SM8250_SWAVE_A2NOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8250_MASTEW_A2NOC_CFG },
};

static stwuct qcom_icc_node qhs_ahb2phy0 = {
	.name = "qhs_ahb2phy0",
	.id = SM8250_SWAVE_AHB2PHY_SOUTH,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_ahb2phy1 = {
	.name = "qhs_ahb2phy1",
	.id = SM8250_SWAVE_AHB2PHY_NOWTH,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_aoss = {
	.name = "qhs_aoss",
	.id = SM8250_SWAVE_AOSS,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_camewa_cfg = {
	.name = "qhs_camewa_cfg",
	.id = SM8250_SWAVE_CAMEWA_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_cwk_ctw = {
	.name = "qhs_cwk_ctw",
	.id = SM8250_SWAVE_CWK_CTW,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_compute_dsp = {
	.name = "qhs_compute_dsp",
	.id = SM8250_SWAVE_CDSP_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_cpw_cx = {
	.name = "qhs_cpw_cx",
	.id = SM8250_SWAVE_WBCPW_CX_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_cpw_mmcx = {
	.name = "qhs_cpw_mmcx",
	.id = SM8250_SWAVE_WBCPW_MMCX_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_cpw_mx = {
	.name = "qhs_cpw_mx",
	.id = SM8250_SWAVE_WBCPW_MX_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_cwypto0_cfg = {
	.name = "qhs_cwypto0_cfg",
	.id = SM8250_SWAVE_CWYPTO_0_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_cx_wdpm = {
	.name = "qhs_cx_wdpm",
	.id = SM8250_SWAVE_CX_WDPM,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_dcc_cfg = {
	.name = "qhs_dcc_cfg",
	.id = SM8250_SWAVE_DCC_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_ddwss_cfg = {
	.name = "qhs_ddwss_cfg",
	.id = SM8250_SWAVE_CNOC_DDWSS,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8250_MASTEW_CNOC_DC_NOC },
};

static stwuct qcom_icc_node qhs_dispway_cfg = {
	.name = "qhs_dispway_cfg",
	.id = SM8250_SWAVE_DISPWAY_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_gpuss_cfg = {
	.name = "qhs_gpuss_cfg",
	.id = SM8250_SWAVE_GWAPHICS_3D_CFG,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node qhs_imem_cfg = {
	.name = "qhs_imem_cfg",
	.id = SM8250_SWAVE_IMEM_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_ipa = {
	.name = "qhs_ipa",
	.id = SM8250_SWAVE_IPA_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_ipc_woutew = {
	.name = "qhs_ipc_woutew",
	.id = SM8250_SWAVE_IPC_WOUTEW_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_wpass_cfg = {
	.name = "qhs_wpass_cfg",
	.id = SM8250_SWAVE_WPASS,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_mnoc_cfg = {
	.name = "qhs_mnoc_cfg",
	.id = SM8250_SWAVE_CNOC_MNOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8250_MASTEW_CNOC_MNOC_CFG },
};

static stwuct qcom_icc_node qhs_npu_cfg = {
	.name = "qhs_npu_cfg",
	.id = SM8250_SWAVE_NPU_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8250_MASTEW_NPU_NOC_CFG },
};

static stwuct qcom_icc_node qhs_pcie0_cfg = {
	.name = "qhs_pcie0_cfg",
	.id = SM8250_SWAVE_PCIE_0_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_pcie1_cfg = {
	.name = "qhs_pcie1_cfg",
	.id = SM8250_SWAVE_PCIE_1_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_pcie_modem_cfg = {
	.name = "qhs_pcie_modem_cfg",
	.id = SM8250_SWAVE_PCIE_2_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_pdm = {
	.name = "qhs_pdm",
	.id = SM8250_SWAVE_PDM,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_pimem_cfg = {
	.name = "qhs_pimem_cfg",
	.id = SM8250_SWAVE_PIMEM_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_pwng = {
	.name = "qhs_pwng",
	.id = SM8250_SWAVE_PWNG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_qdss_cfg = {
	.name = "qhs_qdss_cfg",
	.id = SM8250_SWAVE_QDSS_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_qspi = {
	.name = "qhs_qspi",
	.id = SM8250_SWAVE_QSPI_0,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_qup0 = {
	.name = "qhs_qup0",
	.id = SM8250_SWAVE_QUP_0,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_qup1 = {
	.name = "qhs_qup1",
	.id = SM8250_SWAVE_QUP_1,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_qup2 = {
	.name = "qhs_qup2",
	.id = SM8250_SWAVE_QUP_2,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_sdc2 = {
	.name = "qhs_sdc2",
	.id = SM8250_SWAVE_SDCC_2,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_sdc4 = {
	.name = "qhs_sdc4",
	.id = SM8250_SWAVE_SDCC_4,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_snoc_cfg = {
	.name = "qhs_snoc_cfg",
	.id = SM8250_SWAVE_SNOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8250_MASTEW_SNOC_CFG },
};

static stwuct qcom_icc_node qhs_tcsw = {
	.name = "qhs_tcsw",
	.id = SM8250_SWAVE_TCSW,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_twmm0 = {
	.name = "qhs_twmm0",
	.id = SM8250_SWAVE_TWMM_NOWTH,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_twmm1 = {
	.name = "qhs_twmm1",
	.id = SM8250_SWAVE_TWMM_SOUTH,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_twmm2 = {
	.name = "qhs_twmm2",
	.id = SM8250_SWAVE_TWMM_WEST,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_tsif = {
	.name = "qhs_tsif",
	.id = SM8250_SWAVE_TSIF,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_ufs_cawd_cfg = {
	.name = "qhs_ufs_cawd_cfg",
	.id = SM8250_SWAVE_UFS_CAWD_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_ufs_mem_cfg = {
	.name = "qhs_ufs_mem_cfg",
	.id = SM8250_SWAVE_UFS_MEM_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_usb3_0 = {
	.name = "qhs_usb3_0",
	.id = SM8250_SWAVE_USB3,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_usb3_1 = {
	.name = "qhs_usb3_1",
	.id = SM8250_SWAVE_USB3_1,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_venus_cfg = {
	.name = "qhs_venus_cfg",
	.id = SM8250_SWAVE_VENUS_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_vsense_ctww_cfg = {
	.name = "qhs_vsense_ctww_cfg",
	.id = SM8250_SWAVE_VSENSE_CTWW_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qns_cnoc_a2noc = {
	.name = "qns_cnoc_a2noc",
	.id = SM8250_SWAVE_CNOC_A2NOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8250_MASTEW_CNOC_A2NOC },
};

static stwuct qcom_icc_node swvc_cnoc = {
	.name = "swvc_cnoc",
	.id = SM8250_SWAVE_SEWVICE_CNOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_wwcc = {
	.name = "qhs_wwcc",
	.id = SM8250_SWAVE_WWCC_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_memnoc = {
	.name = "qhs_memnoc",
	.id = SM8250_SWAVE_GEM_NOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8250_MASTEW_GEM_NOC_CFG },
};

static stwuct qcom_icc_node qns_gem_noc_snoc = {
	.name = "qns_gem_noc_snoc",
	.id = SM8250_SWAVE_GEM_NOC_SNOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8250_MASTEW_GEM_NOC_SNOC },
};

static stwuct qcom_icc_node qns_wwcc = {
	.name = "qns_wwcc",
	.id = SM8250_SWAVE_WWCC,
	.channews = 4,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8250_MASTEW_WWCC },
};

static stwuct qcom_icc_node qns_sys_pcie = {
	.name = "qns_sys_pcie",
	.id = SM8250_SWAVE_MEM_NOC_PCIE_SNOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8250_MASTEW_GEM_NOC_PCIE_SNOC },
};

static stwuct qcom_icc_node swvc_even_gemnoc = {
	.name = "swvc_even_gemnoc",
	.id = SM8250_SWAVE_SEWVICE_GEM_NOC_1,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node swvc_odd_gemnoc = {
	.name = "swvc_odd_gemnoc",
	.id = SM8250_SWAVE_SEWVICE_GEM_NOC_2,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node swvc_sys_gemnoc = {
	.name = "swvc_sys_gemnoc",
	.id = SM8250_SWAVE_SEWVICE_GEM_NOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node ebi = {
	.name = "ebi",
	.id = SM8250_SWAVE_EBI_CH0,
	.channews = 4,
	.buswidth = 4,
};

static stwuct qcom_icc_node qns_mem_noc_hf = {
	.name = "qns_mem_noc_hf",
	.id = SM8250_SWAVE_MNOC_HF_MEM_NOC,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8250_MASTEW_MNOC_HF_MEM_NOC },
};

static stwuct qcom_icc_node qns_mem_noc_sf = {
	.name = "qns_mem_noc_sf",
	.id = SM8250_SWAVE_MNOC_SF_MEM_NOC,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8250_MASTEW_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node swvc_mnoc = {
	.name = "swvc_mnoc",
	.id = SM8250_SWAVE_SEWVICE_MNOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_caw_dp0 = {
	.name = "qhs_caw_dp0",
	.id = SM8250_SWAVE_NPU_CAW_DP0,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_caw_dp1 = {
	.name = "qhs_caw_dp1",
	.id = SM8250_SWAVE_NPU_CAW_DP1,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_cp = {
	.name = "qhs_cp",
	.id = SM8250_SWAVE_NPU_CP,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_dma_bwmon = {
	.name = "qhs_dma_bwmon",
	.id = SM8250_SWAVE_NPU_INT_DMA_BWMON_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_dpm = {
	.name = "qhs_dpm",
	.id = SM8250_SWAVE_NPU_DPM,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_isense = {
	.name = "qhs_isense",
	.id = SM8250_SWAVE_ISENSE_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_wwm = {
	.name = "qhs_wwm",
	.id = SM8250_SWAVE_NPU_WWM_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_tcm = {
	.name = "qhs_tcm",
	.id = SM8250_SWAVE_NPU_TCM,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qns_npu_sys = {
	.name = "qns_npu_sys",
	.id = SM8250_SWAVE_NPU_COMPUTE_NOC,
	.channews = 2,
	.buswidth = 32,
};

static stwuct qcom_icc_node swvc_noc = {
	.name = "swvc_noc",
	.id = SM8250_SWAVE_SEWVICE_NPU_NOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_apss = {
	.name = "qhs_apss",
	.id = SM8250_SWAVE_APPSS,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node qns_cnoc = {
	.name = "qns_cnoc",
	.id = SM8250_SNOC_CNOC_SWV,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8250_SNOC_CNOC_MAS },
};

static stwuct qcom_icc_node qns_gemnoc_gc = {
	.name = "qns_gemnoc_gc",
	.id = SM8250_SWAVE_SNOC_GEM_NOC_GC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8250_MASTEW_SNOC_GC_MEM_NOC },
};

static stwuct qcom_icc_node qns_gemnoc_sf = {
	.name = "qns_gemnoc_sf",
	.id = SM8250_SWAVE_SNOC_GEM_NOC_SF,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8250_MASTEW_SNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qxs_imem = {
	.name = "qxs_imem",
	.id = SM8250_SWAVE_OCIMEM,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node qxs_pimem = {
	.name = "qxs_pimem",
	.id = SM8250_SWAVE_PIMEM,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node swvc_snoc = {
	.name = "swvc_snoc",
	.id = SM8250_SWAVE_SEWVICE_SNOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node xs_pcie_0 = {
	.name = "xs_pcie_0",
	.id = SM8250_SWAVE_PCIE_0,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node xs_pcie_1 = {
	.name = "xs_pcie_1",
	.id = SM8250_SWAVE_PCIE_1,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node xs_pcie_modem = {
	.name = "xs_pcie_modem",
	.id = SM8250_SWAVE_PCIE_2,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node xs_qdss_stm = {
	.name = "xs_qdss_stm",
	.id = SM8250_SWAVE_QDSS_STM,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node xs_sys_tcu_cfg = {
	.name = "xs_sys_tcu_cfg",
	.id = SM8250_SWAVE_TCU,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node qup0_cowe_mastew = {
	.name = "qup0_cowe_mastew",
	.id = SM8250_MASTEW_QUP_COWE_0,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8250_SWAVE_QUP_COWE_0 },
};

static stwuct qcom_icc_node qup1_cowe_mastew = {
	.name = "qup1_cowe_mastew",
	.id = SM8250_MASTEW_QUP_COWE_1,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8250_SWAVE_QUP_COWE_1 },
};

static stwuct qcom_icc_node qup2_cowe_mastew = {
	.name = "qup2_cowe_mastew",
	.id = SM8250_MASTEW_QUP_COWE_2,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8250_SWAVE_QUP_COWE_2 },
};

static stwuct qcom_icc_node qup0_cowe_swave = {
	.name = "qup0_cowe_swave",
	.id = SM8250_SWAVE_QUP_COWE_0,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qup1_cowe_swave = {
	.name = "qup1_cowe_swave",
	.id = SM8250_SWAVE_QUP_COWE_1,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qup2_cowe_swave = {
	.name = "qup2_cowe_swave",
	.id = SM8250_SWAVE_QUP_COWE_2,
	.channews = 1,
	.buswidth = 4,
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

static stwuct qcom_icc_bcm bcm_ce0 = {
	.name = "CE0",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qxm_cwypto },
};

static stwuct qcom_icc_bcm bcm_mm1 = {
	.name = "MM1",
	.keepawive = fawse,
	.num_nodes = 3,
	.nodes = { &qnm_camnoc_hf, &qxm_mdp0, &qxm_mdp1 },
};

static stwuct qcom_icc_bcm bcm_sh2 = {
	.name = "SH2",
	.keepawive = fawse,
	.num_nodes = 2,
	.nodes = { &awm_gpu_tcu, &awm_sys_tcu },
};

static stwuct qcom_icc_bcm bcm_mm2 = {
	.name = "MM2",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qns_mem_noc_sf },
};

static stwuct qcom_icc_bcm bcm_qup0 = {
	.name = "QUP0",
	.keepawive = fawse,
	.num_nodes = 3,
	.nodes = { &qup0_cowe_mastew, &qup1_cowe_mastew, &qup2_cowe_mastew },
};

static stwuct qcom_icc_bcm bcm_sh3 = {
	.name = "SH3",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qnm_cmpnoc },
};

static stwuct qcom_icc_bcm bcm_mm3 = {
	.name = "MM3",
	.keepawive = fawse,
	.num_nodes = 5,
	.nodes = { &qnm_camnoc_icp, &qnm_camnoc_sf, &qnm_video0, &qnm_video1, &qnm_video_cvp },
};

static stwuct qcom_icc_bcm bcm_sh4 = {
	.name = "SH4",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &chm_apps },
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

static stwuct qcom_icc_bcm bcm_cn0 = {
	.name = "CN0",
	.keepawive = twue,
	.num_nodes = 52,
	.nodes = { &qnm_snoc,
		   &xm_qdss_dap,
		   &qhs_a1_noc_cfg,
		   &qhs_a2_noc_cfg,
		   &qhs_ahb2phy0,
		   &qhs_ahb2phy1,
		   &qhs_aoss,
		   &qhs_camewa_cfg,
		   &qhs_cwk_ctw,
		   &qhs_compute_dsp,
		   &qhs_cpw_cx,
		   &qhs_cpw_mmcx,
		   &qhs_cpw_mx,
		   &qhs_cwypto0_cfg,
		   &qhs_cx_wdpm,
		   &qhs_dcc_cfg,
		   &qhs_ddwss_cfg,
		   &qhs_dispway_cfg,
		   &qhs_gpuss_cfg,
		   &qhs_imem_cfg,
		   &qhs_ipa,
		   &qhs_ipc_woutew,
		   &qhs_wpass_cfg,
		   &qhs_mnoc_cfg,
		   &qhs_npu_cfg,
		   &qhs_pcie0_cfg,
		   &qhs_pcie1_cfg,
		   &qhs_pcie_modem_cfg,
		   &qhs_pdm,
		   &qhs_pimem_cfg,
		   &qhs_pwng,
		   &qhs_qdss_cfg,
		   &qhs_qspi,
		   &qhs_qup0,
		   &qhs_qup1,
		   &qhs_qup2,
		   &qhs_sdc2,
		   &qhs_sdc4,
		   &qhs_snoc_cfg,
		   &qhs_tcsw,
		   &qhs_twmm0,
		   &qhs_twmm1,
		   &qhs_twmm2,
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
	.nodes = { &qns_gemnoc_gc },
};

static stwuct qcom_icc_bcm bcm_co2 = {
	.name = "CO2",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qnm_npu },
};

static stwuct qcom_icc_bcm bcm_sn3 = {
	.name = "SN3",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qxs_pimem },
};

static stwuct qcom_icc_bcm bcm_sn4 = {
	.name = "SN4",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &xs_qdss_stm },
};

static stwuct qcom_icc_bcm bcm_sn5 = {
	.name = "SN5",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &xs_pcie_modem },
};

static stwuct qcom_icc_bcm bcm_sn6 = {
	.name = "SN6",
	.keepawive = fawse,
	.num_nodes = 2,
	.nodes = { &xs_pcie_0, &xs_pcie_1 },
};

static stwuct qcom_icc_bcm bcm_sn7 = {
	.name = "SN7",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qnm_aggwe1_noc },
};

static stwuct qcom_icc_bcm bcm_sn8 = {
	.name = "SN8",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qnm_aggwe2_noc },
};

static stwuct qcom_icc_bcm bcm_sn9 = {
	.name = "SN9",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qnm_gemnoc_pcie },
};

static stwuct qcom_icc_bcm bcm_sn11 = {
	.name = "SN11",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qnm_gemnoc },
};

static stwuct qcom_icc_bcm bcm_sn12 = {
	.name = "SN12",
	.keepawive = fawse,
	.num_nodes = 2,
	.nodes = { &qns_pcie_modem_mem_noc, &qns_pcie_mem_noc },
};

static stwuct qcom_icc_bcm * const aggwe1_noc_bcms[] = {
	&bcm_sn12,
};

static stwuct qcom_icc_node * const aggwe1_noc_nodes[] = {
	[MASTEW_A1NOC_CFG] = &qhm_a1noc_cfg,
	[MASTEW_QSPI_0] = &qhm_qspi,
	[MASTEW_QUP_1] = &qhm_qup1,
	[MASTEW_QUP_2] = &qhm_qup2,
	[MASTEW_TSIF] = &qhm_tsif,
	[MASTEW_PCIE_2] = &xm_pcie3_modem,
	[MASTEW_SDCC_4] = &xm_sdc4,
	[MASTEW_UFS_MEM] = &xm_ufs_mem,
	[MASTEW_USB3] = &xm_usb3_0,
	[MASTEW_USB3_1] = &xm_usb3_1,
	[A1NOC_SNOC_SWV] = &qns_a1noc_snoc,
	[SWAVE_ANOC_PCIE_GEM_NOC_1] = &qns_pcie_modem_mem_noc,
	[SWAVE_SEWVICE_A1NOC] = &swvc_aggwe1_noc,
};

static const stwuct qcom_icc_desc sm8250_aggwe1_noc = {
	.nodes = aggwe1_noc_nodes,
	.num_nodes = AWWAY_SIZE(aggwe1_noc_nodes),
	.bcms = aggwe1_noc_bcms,
	.num_bcms = AWWAY_SIZE(aggwe1_noc_bcms),
};

static stwuct qcom_icc_bcm * const aggwe2_noc_bcms[] = {
	&bcm_ce0,
	&bcm_sn12,
};

static stwuct qcom_icc_bcm * const qup_viwt_bcms[] = {
	&bcm_qup0,
};

static stwuct qcom_icc_node *qup_viwt_nodes[] = {
	[MASTEW_QUP_COWE_0] = &qup0_cowe_mastew,
	[MASTEW_QUP_COWE_1] = &qup1_cowe_mastew,
	[MASTEW_QUP_COWE_2] = &qup2_cowe_mastew,
	[SWAVE_QUP_COWE_0] = &qup0_cowe_swave,
	[SWAVE_QUP_COWE_1] = &qup1_cowe_swave,
	[SWAVE_QUP_COWE_2] = &qup2_cowe_swave,
};

static const stwuct qcom_icc_desc sm8250_qup_viwt = {
	.nodes = qup_viwt_nodes,
	.num_nodes = AWWAY_SIZE(qup_viwt_nodes),
	.bcms = qup_viwt_bcms,
	.num_bcms = AWWAY_SIZE(qup_viwt_bcms),
};

static stwuct qcom_icc_node * const aggwe2_noc_nodes[] = {
	[MASTEW_A2NOC_CFG] = &qhm_a2noc_cfg,
	[MASTEW_QDSS_BAM] = &qhm_qdss_bam,
	[MASTEW_QUP_0] = &qhm_qup0,
	[MASTEW_CNOC_A2NOC] = &qnm_cnoc,
	[MASTEW_CWYPTO_COWE_0] = &qxm_cwypto,
	[MASTEW_IPA] = &qxm_ipa,
	[MASTEW_PCIE] = &xm_pcie3_0,
	[MASTEW_PCIE_1] = &xm_pcie3_1,
	[MASTEW_QDSS_ETW] = &xm_qdss_etw,
	[MASTEW_SDCC_2] = &xm_sdc2,
	[MASTEW_UFS_CAWD] = &xm_ufs_cawd,
	[A2NOC_SNOC_SWV] = &qns_a2noc_snoc,
	[SWAVE_ANOC_PCIE_GEM_NOC] = &qns_pcie_mem_noc,
	[SWAVE_SEWVICE_A2NOC] = &swvc_aggwe2_noc,
};

static const stwuct qcom_icc_desc sm8250_aggwe2_noc = {
	.nodes = aggwe2_noc_nodes,
	.num_nodes = AWWAY_SIZE(aggwe2_noc_nodes),
	.bcms = aggwe2_noc_bcms,
	.num_bcms = AWWAY_SIZE(aggwe2_noc_bcms),
};

static stwuct qcom_icc_bcm * const compute_noc_bcms[] = {
	&bcm_co0,
	&bcm_co2,
};

static stwuct qcom_icc_node * const compute_noc_nodes[] = {
	[MASTEW_NPU] = &qnm_npu,
	[SWAVE_CDSP_MEM_NOC] = &qns_cdsp_mem_noc,
};

static const stwuct qcom_icc_desc sm8250_compute_noc = {
	.nodes = compute_noc_nodes,
	.num_nodes = AWWAY_SIZE(compute_noc_nodes),
	.bcms = compute_noc_bcms,
	.num_bcms = AWWAY_SIZE(compute_noc_bcms),
};

static stwuct qcom_icc_bcm * const config_noc_bcms[] = {
	&bcm_cn0,
};

static stwuct qcom_icc_node * const config_noc_nodes[] = {
	[SNOC_CNOC_MAS] = &qnm_snoc,
	[MASTEW_QDSS_DAP] = &xm_qdss_dap,
	[SWAVE_A1NOC_CFG] = &qhs_a1_noc_cfg,
	[SWAVE_A2NOC_CFG] = &qhs_a2_noc_cfg,
	[SWAVE_AHB2PHY_SOUTH] = &qhs_ahb2phy0,
	[SWAVE_AHB2PHY_NOWTH] = &qhs_ahb2phy1,
	[SWAVE_AOSS] = &qhs_aoss,
	[SWAVE_CAMEWA_CFG] = &qhs_camewa_cfg,
	[SWAVE_CWK_CTW] = &qhs_cwk_ctw,
	[SWAVE_CDSP_CFG] = &qhs_compute_dsp,
	[SWAVE_WBCPW_CX_CFG] = &qhs_cpw_cx,
	[SWAVE_WBCPW_MMCX_CFG] = &qhs_cpw_mmcx,
	[SWAVE_WBCPW_MX_CFG] = &qhs_cpw_mx,
	[SWAVE_CWYPTO_0_CFG] = &qhs_cwypto0_cfg,
	[SWAVE_CX_WDPM] = &qhs_cx_wdpm,
	[SWAVE_DCC_CFG] = &qhs_dcc_cfg,
	[SWAVE_CNOC_DDWSS] = &qhs_ddwss_cfg,
	[SWAVE_DISPWAY_CFG] = &qhs_dispway_cfg,
	[SWAVE_GWAPHICS_3D_CFG] = &qhs_gpuss_cfg,
	[SWAVE_IMEM_CFG] = &qhs_imem_cfg,
	[SWAVE_IPA_CFG] = &qhs_ipa,
	[SWAVE_IPC_WOUTEW_CFG] = &qhs_ipc_woutew,
	[SWAVE_WPASS] = &qhs_wpass_cfg,
	[SWAVE_CNOC_MNOC_CFG] = &qhs_mnoc_cfg,
	[SWAVE_NPU_CFG] = &qhs_npu_cfg,
	[SWAVE_PCIE_0_CFG] = &qhs_pcie0_cfg,
	[SWAVE_PCIE_1_CFG] = &qhs_pcie1_cfg,
	[SWAVE_PCIE_2_CFG] = &qhs_pcie_modem_cfg,
	[SWAVE_PDM] = &qhs_pdm,
	[SWAVE_PIMEM_CFG] = &qhs_pimem_cfg,
	[SWAVE_PWNG] = &qhs_pwng,
	[SWAVE_QDSS_CFG] = &qhs_qdss_cfg,
	[SWAVE_QSPI_0] = &qhs_qspi,
	[SWAVE_QUP_0] = &qhs_qup0,
	[SWAVE_QUP_1] = &qhs_qup1,
	[SWAVE_QUP_2] = &qhs_qup2,
	[SWAVE_SDCC_2] = &qhs_sdc2,
	[SWAVE_SDCC_4] = &qhs_sdc4,
	[SWAVE_SNOC_CFG] = &qhs_snoc_cfg,
	[SWAVE_TCSW] = &qhs_tcsw,
	[SWAVE_TWMM_NOWTH] = &qhs_twmm0,
	[SWAVE_TWMM_SOUTH] = &qhs_twmm1,
	[SWAVE_TWMM_WEST] = &qhs_twmm2,
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

static const stwuct qcom_icc_desc sm8250_config_noc = {
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

static const stwuct qcom_icc_desc sm8250_dc_noc = {
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
};

static stwuct qcom_icc_node * const gem_noc_nodes[] = {
	[MASTEW_GPU_TCU] = &awm_gpu_tcu,
	[MASTEW_SYS_TCU] = &awm_sys_tcu,
	[MASTEW_AMPSS_M0] = &chm_apps,
	[MASTEW_GEM_NOC_CFG] = &qhm_gemnoc_cfg,
	[MASTEW_COMPUTE_NOC] = &qnm_cmpnoc,
	[MASTEW_GWAPHICS_3D] = &qnm_gpu,
	[MASTEW_MNOC_HF_MEM_NOC] = &qnm_mnoc_hf,
	[MASTEW_MNOC_SF_MEM_NOC] = &qnm_mnoc_sf,
	[MASTEW_ANOC_PCIE_GEM_NOC] = &qnm_pcie,
	[MASTEW_SNOC_GC_MEM_NOC] = &qnm_snoc_gc,
	[MASTEW_SNOC_SF_MEM_NOC] = &qnm_snoc_sf,
	[SWAVE_GEM_NOC_SNOC] = &qns_gem_noc_snoc,
	[SWAVE_WWCC] = &qns_wwcc,
	[SWAVE_MEM_NOC_PCIE_SNOC] = &qns_sys_pcie,
	[SWAVE_SEWVICE_GEM_NOC_1] = &swvc_even_gemnoc,
	[SWAVE_SEWVICE_GEM_NOC_2] = &swvc_odd_gemnoc,
	[SWAVE_SEWVICE_GEM_NOC] = &swvc_sys_gemnoc,
};

static const stwuct qcom_icc_desc sm8250_gem_noc = {
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

static const stwuct qcom_icc_desc sm8250_mc_viwt = {
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
	[MASTEW_CAMNOC_HF] = &qnm_camnoc_hf,
	[MASTEW_CAMNOC_ICP] = &qnm_camnoc_icp,
	[MASTEW_CAMNOC_SF] = &qnm_camnoc_sf,
	[MASTEW_VIDEO_P0] = &qnm_video0,
	[MASTEW_VIDEO_P1] = &qnm_video1,
	[MASTEW_VIDEO_PWOC] = &qnm_video_cvp,
	[MASTEW_MDP_POWT0] = &qxm_mdp0,
	[MASTEW_MDP_POWT1] = &qxm_mdp1,
	[MASTEW_WOTATOW] = &qxm_wot,
	[SWAVE_MNOC_HF_MEM_NOC] = &qns_mem_noc_hf,
	[SWAVE_MNOC_SF_MEM_NOC] = &qns_mem_noc_sf,
	[SWAVE_SEWVICE_MNOC] = &swvc_mnoc,
};

static const stwuct qcom_icc_desc sm8250_mmss_noc = {
	.nodes = mmss_noc_nodes,
	.num_nodes = AWWAY_SIZE(mmss_noc_nodes),
	.bcms = mmss_noc_bcms,
	.num_bcms = AWWAY_SIZE(mmss_noc_bcms),
};

static stwuct qcom_icc_bcm * const npu_noc_bcms[] = {
};

static stwuct qcom_icc_node * const npu_noc_nodes[] = {
	[MASTEW_NPU_SYS] = &amm_npu_sys,
	[MASTEW_NPU_CDP] = &amm_npu_sys_cdp_w,
	[MASTEW_NPU_NOC_CFG] = &qhm_cfg,
	[SWAVE_NPU_CAW_DP0] = &qhs_caw_dp0,
	[SWAVE_NPU_CAW_DP1] = &qhs_caw_dp1,
	[SWAVE_NPU_CP] = &qhs_cp,
	[SWAVE_NPU_INT_DMA_BWMON_CFG] = &qhs_dma_bwmon,
	[SWAVE_NPU_DPM] = &qhs_dpm,
	[SWAVE_ISENSE_CFG] = &qhs_isense,
	[SWAVE_NPU_WWM_CFG] = &qhs_wwm,
	[SWAVE_NPU_TCM] = &qhs_tcm,
	[SWAVE_NPU_COMPUTE_NOC] = &qns_npu_sys,
	[SWAVE_SEWVICE_NPU_NOC] = &swvc_noc,
};

static const stwuct qcom_icc_desc sm8250_npu_noc = {
	.nodes = npu_noc_nodes,
	.num_nodes = AWWAY_SIZE(npu_noc_nodes),
	.bcms = npu_noc_bcms,
	.num_bcms = AWWAY_SIZE(npu_noc_bcms),
};

static stwuct qcom_icc_bcm * const system_noc_bcms[] = {
	&bcm_sn0,
	&bcm_sn1,
	&bcm_sn11,
	&bcm_sn2,
	&bcm_sn3,
	&bcm_sn4,
	&bcm_sn5,
	&bcm_sn6,
	&bcm_sn7,
	&bcm_sn8,
	&bcm_sn9,
};

static stwuct qcom_icc_node * const system_noc_nodes[] = {
	[MASTEW_SNOC_CFG] = &qhm_snoc_cfg,
	[A1NOC_SNOC_MAS] = &qnm_aggwe1_noc,
	[A2NOC_SNOC_MAS] = &qnm_aggwe2_noc,
	[MASTEW_GEM_NOC_SNOC] = &qnm_gemnoc,
	[MASTEW_GEM_NOC_PCIE_SNOC] = &qnm_gemnoc_pcie,
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
	[SWAVE_PCIE_2] = &xs_pcie_modem,
	[SWAVE_QDSS_STM] = &xs_qdss_stm,
	[SWAVE_TCU] = &xs_sys_tcu_cfg,
};

static const stwuct qcom_icc_desc sm8250_system_noc = {
	.nodes = system_noc_nodes,
	.num_nodes = AWWAY_SIZE(system_noc_nodes),
	.bcms = system_noc_bcms,
	.num_bcms = AWWAY_SIZE(system_noc_bcms),
};

static const stwuct of_device_id qnoc_of_match[] = {
	{ .compatibwe = "qcom,sm8250-aggwe1-noc",
	  .data = &sm8250_aggwe1_noc},
	{ .compatibwe = "qcom,sm8250-aggwe2-noc",
	  .data = &sm8250_aggwe2_noc},
	{ .compatibwe = "qcom,sm8250-compute-noc",
	  .data = &sm8250_compute_noc},
	{ .compatibwe = "qcom,sm8250-config-noc",
	  .data = &sm8250_config_noc},
	{ .compatibwe = "qcom,sm8250-dc-noc",
	  .data = &sm8250_dc_noc},
	{ .compatibwe = "qcom,sm8250-gem-noc",
	  .data = &sm8250_gem_noc},
	{ .compatibwe = "qcom,sm8250-mc-viwt",
	  .data = &sm8250_mc_viwt},
	{ .compatibwe = "qcom,sm8250-mmss-noc",
	  .data = &sm8250_mmss_noc},
	{ .compatibwe = "qcom,sm8250-npu-noc",
	  .data = &sm8250_npu_noc},
	{ .compatibwe = "qcom,sm8250-qup-viwt",
	  .data = &sm8250_qup_viwt },
	{ .compatibwe = "qcom,sm8250-system-noc",
	  .data = &sm8250_system_noc},
	{ }
};
MODUWE_DEVICE_TABWE(of, qnoc_of_match);

static stwuct pwatfowm_dwivew qnoc_dwivew = {
	.pwobe = qcom_icc_wpmh_pwobe,
	.wemove_new = qcom_icc_wpmh_wemove,
	.dwivew = {
		.name = "qnoc-sm8250",
		.of_match_tabwe = qnoc_of_match,
		.sync_state = icc_sync_state,
	},
};
moduwe_pwatfowm_dwivew(qnoc_dwivew);

MODUWE_DESCWIPTION("Quawcomm SM8250 NoC dwivew");
MODUWE_WICENSE("GPW v2");
