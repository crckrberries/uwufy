// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2019-2020, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021, Winawo Wimited
 *
 */

#incwude <winux/intewconnect-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <dt-bindings/intewconnect/qcom,sm8350.h>

#incwude "bcm-votew.h"
#incwude "icc-wpmh.h"
#incwude "sm8350.h"

static stwuct qcom_icc_node qhm_qspi = {
	.name = "qhm_qspi",
	.id = SM8350_MASTEW_QSPI_0,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_A1NOC_SNOC },
};

static stwuct qcom_icc_node qhm_qup0 = {
	.name = "qhm_qup0",
	.id = SM8350_MASTEW_QUP_0,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_A2NOC_SNOC },
};

static stwuct qcom_icc_node qhm_qup1 = {
	.name = "qhm_qup1",
	.id = SM8350_MASTEW_QUP_1,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_A1NOC_SNOC },
};

static stwuct qcom_icc_node qhm_qup2 = {
	.name = "qhm_qup2",
	.id = SM8350_MASTEW_QUP_2,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_A2NOC_SNOC },
};

static stwuct qcom_icc_node qnm_a1noc_cfg = {
	.name = "qnm_a1noc_cfg",
	.id = SM8350_MASTEW_A1NOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_SEWVICE_A1NOC },
};

static stwuct qcom_icc_node xm_sdc4 = {
	.name = "xm_sdc4",
	.id = SM8350_MASTEW_SDCC_4,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_A1NOC_SNOC },
};

static stwuct qcom_icc_node xm_ufs_mem = {
	.name = "xm_ufs_mem",
	.id = SM8350_MASTEW_UFS_MEM,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_A1NOC_SNOC },
};

static stwuct qcom_icc_node xm_usb3_0 = {
	.name = "xm_usb3_0",
	.id = SM8350_MASTEW_USB3_0,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_A1NOC_SNOC },
};

static stwuct qcom_icc_node xm_usb3_1 = {
	.name = "xm_usb3_1",
	.id = SM8350_MASTEW_USB3_1,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_A1NOC_SNOC },
};

static stwuct qcom_icc_node qhm_qdss_bam = {
	.name = "qhm_qdss_bam",
	.id = SM8350_MASTEW_QDSS_BAM,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_A2NOC_SNOC },
};

static stwuct qcom_icc_node qnm_a2noc_cfg = {
	.name = "qnm_a2noc_cfg",
	.id = SM8350_MASTEW_A2NOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_SEWVICE_A2NOC },
};

static stwuct qcom_icc_node qxm_cwypto = {
	.name = "qxm_cwypto",
	.id = SM8350_MASTEW_CWYPTO,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_A2NOC_SNOC },
};

static stwuct qcom_icc_node qxm_ipa = {
	.name = "qxm_ipa",
	.id = SM8350_MASTEW_IPA,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_A2NOC_SNOC },
};

static stwuct qcom_icc_node xm_pcie3_0 = {
	.name = "xm_pcie3_0",
	.id = SM8350_MASTEW_PCIE_0,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_ANOC_PCIE_GEM_NOC },
};

static stwuct qcom_icc_node xm_pcie3_1 = {
	.name = "xm_pcie3_1",
	.id = SM8350_MASTEW_PCIE_1,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_ANOC_PCIE_GEM_NOC },
};

static stwuct qcom_icc_node xm_qdss_etw = {
	.name = "xm_qdss_etw",
	.id = SM8350_MASTEW_QDSS_ETW,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_A2NOC_SNOC },
};

static stwuct qcom_icc_node xm_sdc2 = {
	.name = "xm_sdc2",
	.id = SM8350_MASTEW_SDCC_2,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_A2NOC_SNOC },
};

static stwuct qcom_icc_node xm_ufs_cawd = {
	.name = "xm_ufs_cawd",
	.id = SM8350_MASTEW_UFS_CAWD,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_A2NOC_SNOC },
};

static stwuct qcom_icc_node qnm_gemnoc_cnoc = {
	.name = "qnm_gemnoc_cnoc",
	.id = SM8350_MASTEW_GEM_NOC_CNOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 56,
	.winks = { SM8350_SWAVE_AHB2PHY_SOUTH,
		   SM8350_SWAVE_AHB2PHY_NOWTH,
		   SM8350_SWAVE_AOSS,
		   SM8350_SWAVE_APPSS,
		   SM8350_SWAVE_CAMEWA_CFG,
		   SM8350_SWAVE_CWK_CTW,
		   SM8350_SWAVE_CDSP_CFG,
		   SM8350_SWAVE_WBCPW_CX_CFG,
		   SM8350_SWAVE_WBCPW_MMCX_CFG,
		   SM8350_SWAVE_WBCPW_MX_CFG,
		   SM8350_SWAVE_CWYPTO_0_CFG,
		   SM8350_SWAVE_CX_WDPM,
		   SM8350_SWAVE_DCC_CFG,
		   SM8350_SWAVE_DISPWAY_CFG,
		   SM8350_SWAVE_GFX3D_CFG,
		   SM8350_SWAVE_HWKM,
		   SM8350_SWAVE_IMEM_CFG,
		   SM8350_SWAVE_IPA_CFG,
		   SM8350_SWAVE_IPC_WOUTEW_CFG,
		   SM8350_SWAVE_WPASS,
		   SM8350_SWAVE_CNOC_MSS,
		   SM8350_SWAVE_MX_WDPM,
		   SM8350_SWAVE_PCIE_0_CFG,
		   SM8350_SWAVE_PCIE_1_CFG,
		   SM8350_SWAVE_PDM,
		   SM8350_SWAVE_PIMEM_CFG,
		   SM8350_SWAVE_PKA_WWAPPEW_CFG,
		   SM8350_SWAVE_PMU_WWAPPEW_CFG,
		   SM8350_SWAVE_QDSS_CFG,
		   SM8350_SWAVE_QSPI_0,
		   SM8350_SWAVE_QUP_0,
		   SM8350_SWAVE_QUP_1,
		   SM8350_SWAVE_QUP_2,
		   SM8350_SWAVE_SDCC_2,
		   SM8350_SWAVE_SDCC_4,
		   SM8350_SWAVE_SECUWITY,
		   SM8350_SWAVE_SPSS_CFG,
		   SM8350_SWAVE_TCSW,
		   SM8350_SWAVE_TWMM,
		   SM8350_SWAVE_UFS_CAWD_CFG,
		   SM8350_SWAVE_UFS_MEM_CFG,
		   SM8350_SWAVE_USB3_0,
		   SM8350_SWAVE_USB3_1,
		   SM8350_SWAVE_VENUS_CFG,
		   SM8350_SWAVE_VSENSE_CTWW_CFG,
		   SM8350_SWAVE_A1NOC_CFG,
		   SM8350_SWAVE_A2NOC_CFG,
		   SM8350_SWAVE_DDWSS_CFG,
		   SM8350_SWAVE_CNOC_MNOC_CFG,
		   SM8350_SWAVE_SNOC_CFG,
		   SM8350_SWAVE_BOOT_IMEM,
		   SM8350_SWAVE_IMEM,
		   SM8350_SWAVE_PIMEM,
		   SM8350_SWAVE_SEWVICE_CNOC,
		   SM8350_SWAVE_QDSS_STM,
		   SM8350_SWAVE_TCU
	},
};

static stwuct qcom_icc_node qnm_gemnoc_pcie = {
	.name = "qnm_gemnoc_pcie",
	.id = SM8350_MASTEW_GEM_NOC_PCIE_SNOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 2,
	.winks = { SM8350_SWAVE_PCIE_0,
		   SM8350_SWAVE_PCIE_1
	},
};

static stwuct qcom_icc_node xm_qdss_dap = {
	.name = "xm_qdss_dap",
	.id = SM8350_MASTEW_QDSS_DAP,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 56,
	.winks = { SM8350_SWAVE_AHB2PHY_SOUTH,
		   SM8350_SWAVE_AHB2PHY_NOWTH,
		   SM8350_SWAVE_AOSS,
		   SM8350_SWAVE_APPSS,
		   SM8350_SWAVE_CAMEWA_CFG,
		   SM8350_SWAVE_CWK_CTW,
		   SM8350_SWAVE_CDSP_CFG,
		   SM8350_SWAVE_WBCPW_CX_CFG,
		   SM8350_SWAVE_WBCPW_MMCX_CFG,
		   SM8350_SWAVE_WBCPW_MX_CFG,
		   SM8350_SWAVE_CWYPTO_0_CFG,
		   SM8350_SWAVE_CX_WDPM,
		   SM8350_SWAVE_DCC_CFG,
		   SM8350_SWAVE_DISPWAY_CFG,
		   SM8350_SWAVE_GFX3D_CFG,
		   SM8350_SWAVE_HWKM,
		   SM8350_SWAVE_IMEM_CFG,
		   SM8350_SWAVE_IPA_CFG,
		   SM8350_SWAVE_IPC_WOUTEW_CFG,
		   SM8350_SWAVE_WPASS,
		   SM8350_SWAVE_CNOC_MSS,
		   SM8350_SWAVE_MX_WDPM,
		   SM8350_SWAVE_PCIE_0_CFG,
		   SM8350_SWAVE_PCIE_1_CFG,
		   SM8350_SWAVE_PDM,
		   SM8350_SWAVE_PIMEM_CFG,
		   SM8350_SWAVE_PKA_WWAPPEW_CFG,
		   SM8350_SWAVE_PMU_WWAPPEW_CFG,
		   SM8350_SWAVE_QDSS_CFG,
		   SM8350_SWAVE_QSPI_0,
		   SM8350_SWAVE_QUP_0,
		   SM8350_SWAVE_QUP_1,
		   SM8350_SWAVE_QUP_2,
		   SM8350_SWAVE_SDCC_2,
		   SM8350_SWAVE_SDCC_4,
		   SM8350_SWAVE_SECUWITY,
		   SM8350_SWAVE_SPSS_CFG,
		   SM8350_SWAVE_TCSW,
		   SM8350_SWAVE_TWMM,
		   SM8350_SWAVE_UFS_CAWD_CFG,
		   SM8350_SWAVE_UFS_MEM_CFG,
		   SM8350_SWAVE_USB3_0,
		   SM8350_SWAVE_USB3_1,
		   SM8350_SWAVE_VENUS_CFG,
		   SM8350_SWAVE_VSENSE_CTWW_CFG,
		   SM8350_SWAVE_A1NOC_CFG,
		   SM8350_SWAVE_A2NOC_CFG,
		   SM8350_SWAVE_DDWSS_CFG,
		   SM8350_SWAVE_CNOC_MNOC_CFG,
		   SM8350_SWAVE_SNOC_CFG,
		   SM8350_SWAVE_BOOT_IMEM,
		   SM8350_SWAVE_IMEM,
		   SM8350_SWAVE_PIMEM,
		   SM8350_SWAVE_SEWVICE_CNOC,
		   SM8350_SWAVE_QDSS_STM,
		   SM8350_SWAVE_TCU
	},
};

static stwuct qcom_icc_node qnm_cnoc_dc_noc = {
	.name = "qnm_cnoc_dc_noc",
	.id = SM8350_MASTEW_CNOC_DC_NOC,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 2,
	.winks = { SM8350_SWAVE_WWCC_CFG,
		   SM8350_SWAVE_GEM_NOC_CFG
	},
};

static stwuct qcom_icc_node awm_gpu_tcu = {
	.name = "awm_gpu_tcu",
	.id = SM8350_MASTEW_GPU_TCU,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 2,
	.winks = { SM8350_SWAVE_GEM_NOC_CNOC,
		   SM8350_SWAVE_WWCC
	},
};

static stwuct qcom_icc_node awm_sys_tcu = {
	.name = "awm_sys_tcu",
	.id = SM8350_MASTEW_SYS_TCU,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 2,
	.winks = { SM8350_SWAVE_GEM_NOC_CNOC,
		   SM8350_SWAVE_WWCC
	},
};

static stwuct qcom_icc_node chm_apps = {
	.name = "chm_apps",
	.id = SM8350_MASTEW_APPSS_PWOC,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 3,
	.winks = { SM8350_SWAVE_GEM_NOC_CNOC,
		   SM8350_SWAVE_WWCC,
		   SM8350_SWAVE_MEM_NOC_PCIE_SNOC
	},
};

static stwuct qcom_icc_node qnm_cmpnoc = {
	.name = "qnm_cmpnoc",
	.id = SM8350_MASTEW_COMPUTE_NOC,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 2,
	.winks = { SM8350_SWAVE_GEM_NOC_CNOC,
		   SM8350_SWAVE_WWCC
	},
};

static stwuct qcom_icc_node qnm_gemnoc_cfg = {
	.name = "qnm_gemnoc_cfg",
	.id = SM8350_MASTEW_GEM_NOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 5,
	.winks = { SM8350_SWAVE_MSS_PWOC_MS_MPU_CFG,
		   SM8350_SWAVE_MCDMA_MS_MPU_CFG,
		   SM8350_SWAVE_SEWVICE_GEM_NOC_1,
		   SM8350_SWAVE_SEWVICE_GEM_NOC_2,
		   SM8350_SWAVE_SEWVICE_GEM_NOC
	},
};

static stwuct qcom_icc_node qnm_gpu = {
	.name = "qnm_gpu",
	.id = SM8350_MASTEW_GFX3D,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 2,
	.winks = { SM8350_SWAVE_GEM_NOC_CNOC,
		   SM8350_SWAVE_WWCC
	},
};

static stwuct qcom_icc_node qnm_mnoc_hf = {
	.name = "qnm_mnoc_hf",
	.id = SM8350_MASTEW_MNOC_HF_MEM_NOC,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_WWCC },
};

static stwuct qcom_icc_node qnm_mnoc_sf = {
	.name = "qnm_mnoc_sf",
	.id = SM8350_MASTEW_MNOC_SF_MEM_NOC,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 2,
	.winks = { SM8350_SWAVE_GEM_NOC_CNOC,
		   SM8350_SWAVE_WWCC
	},
};

static stwuct qcom_icc_node qnm_pcie = {
	.name = "qnm_pcie",
	.id = SM8350_MASTEW_ANOC_PCIE_GEM_NOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 2,
	.winks = { SM8350_SWAVE_GEM_NOC_CNOC,
		   SM8350_SWAVE_WWCC
	},
};

static stwuct qcom_icc_node qnm_snoc_gc = {
	.name = "qnm_snoc_gc",
	.id = SM8350_MASTEW_SNOC_GC_MEM_NOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_WWCC },
};

static stwuct qcom_icc_node qnm_snoc_sf = {
	.name = "qnm_snoc_sf",
	.id = SM8350_MASTEW_SNOC_SF_MEM_NOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 3,
	.winks = { SM8350_SWAVE_GEM_NOC_CNOC,
		   SM8350_SWAVE_WWCC,
		   SM8350_SWAVE_MEM_NOC_PCIE_SNOC
	},
};

static stwuct qcom_icc_node qhm_config_noc = {
	.name = "qhm_config_noc",
	.id = SM8350_MASTEW_CNOC_WPASS_AG_NOC,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 6,
	.winks = { SM8350_SWAVE_WPASS_COWE_CFG,
		   SM8350_SWAVE_WPASS_WPI_CFG,
		   SM8350_SWAVE_WPASS_MPU_CFG,
		   SM8350_SWAVE_WPASS_TOP_CFG,
		   SM8350_SWAVE_SEWVICES_WPASS_AMW_NOC,
		   SM8350_SWAVE_SEWVICE_WPASS_AG_NOC
	},
};

static stwuct qcom_icc_node wwcc_mc = {
	.name = "wwcc_mc",
	.id = SM8350_MASTEW_WWCC,
	.channews = 4,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_EBI1 },
};

static stwuct qcom_icc_node qnm_camnoc_hf = {
	.name = "qnm_camnoc_hf",
	.id = SM8350_MASTEW_CAMNOC_HF,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_MNOC_HF_MEM_NOC },
};

static stwuct qcom_icc_node qnm_camnoc_icp = {
	.name = "qnm_camnoc_icp",
	.id = SM8350_MASTEW_CAMNOC_ICP,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qnm_camnoc_sf = {
	.name = "qnm_camnoc_sf",
	.id = SM8350_MASTEW_CAMNOC_SF,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qnm_mnoc_cfg = {
	.name = "qnm_mnoc_cfg",
	.id = SM8350_MASTEW_CNOC_MNOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_SEWVICE_MNOC },
};

static stwuct qcom_icc_node qnm_video0 = {
	.name = "qnm_video0",
	.id = SM8350_MASTEW_VIDEO_P0,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qnm_video1 = {
	.name = "qnm_video1",
	.id = SM8350_MASTEW_VIDEO_P1,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qnm_video_cvp = {
	.name = "qnm_video_cvp",
	.id = SM8350_MASTEW_VIDEO_PWOC,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qxm_mdp0 = {
	.name = "qxm_mdp0",
	.id = SM8350_MASTEW_MDP0,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_MNOC_HF_MEM_NOC },
};

static stwuct qcom_icc_node qxm_mdp1 = {
	.name = "qxm_mdp1",
	.id = SM8350_MASTEW_MDP1,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_MNOC_HF_MEM_NOC },
};

static stwuct qcom_icc_node qxm_wot = {
	.name = "qxm_wot",
	.id = SM8350_MASTEW_WOTATOW,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qhm_nsp_noc_config = {
	.name = "qhm_nsp_noc_config",
	.id = SM8350_MASTEW_CDSP_NOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_SEWVICE_NSP_NOC },
};

static stwuct qcom_icc_node qxm_nsp = {
	.name = "qxm_nsp",
	.id = SM8350_MASTEW_CDSP_PWOC,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_CDSP_MEM_NOC },
};

static stwuct qcom_icc_node qnm_aggwe1_noc = {
	.name = "qnm_aggwe1_noc",
	.id = SM8350_MASTEW_A1NOC_SNOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_SNOC_GEM_NOC_SF },
};

static stwuct qcom_icc_node qnm_aggwe2_noc = {
	.name = "qnm_aggwe2_noc",
	.id = SM8350_MASTEW_A2NOC_SNOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_SNOC_GEM_NOC_SF },
};

static stwuct qcom_icc_node qnm_snoc_cfg = {
	.name = "qnm_snoc_cfg",
	.id = SM8350_MASTEW_SNOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_SEWVICE_SNOC },
};

static stwuct qcom_icc_node qxm_pimem = {
	.name = "qxm_pimem",
	.id = SM8350_MASTEW_PIMEM,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_SNOC_GEM_NOC_GC },
};

static stwuct qcom_icc_node xm_gic = {
	.name = "xm_gic",
	.id = SM8350_MASTEW_GIC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_SNOC_GEM_NOC_GC },
};

static stwuct qcom_icc_node qnm_mnoc_hf_disp = {
	.name = "qnm_mnoc_hf_disp",
	.id = SM8350_MASTEW_MNOC_HF_MEM_NOC_DISP,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_WWCC_DISP },
};

static stwuct qcom_icc_node qnm_mnoc_sf_disp = {
	.name = "qnm_mnoc_sf_disp",
	.id = SM8350_MASTEW_MNOC_SF_MEM_NOC_DISP,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_WWCC_DISP },
};

static stwuct qcom_icc_node wwcc_mc_disp = {
	.name = "wwcc_mc_disp",
	.id = SM8350_MASTEW_WWCC_DISP,
	.channews = 4,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_EBI1_DISP },
};

static stwuct qcom_icc_node qxm_mdp0_disp = {
	.name = "qxm_mdp0_disp",
	.id = SM8350_MASTEW_MDP0_DISP,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_MNOC_HF_MEM_NOC_DISP },
};

static stwuct qcom_icc_node qxm_mdp1_disp = {
	.name = "qxm_mdp1_disp",
	.id = SM8350_MASTEW_MDP1_DISP,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_MNOC_HF_MEM_NOC_DISP },
};

static stwuct qcom_icc_node qxm_wot_disp = {
	.name = "qxm_wot_disp",
	.id = SM8350_MASTEW_WOTATOW_DISP,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8350_SWAVE_MNOC_SF_MEM_NOC_DISP },
};

static stwuct qcom_icc_node qns_a1noc_snoc = {
	.name = "qns_a1noc_snoc",
	.id = SM8350_SWAVE_A1NOC_SNOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8350_MASTEW_A1NOC_SNOC },
};

static stwuct qcom_icc_node swvc_aggwe1_noc = {
	.name = "swvc_aggwe1_noc",
	.id = SM8350_SWAVE_SEWVICE_A1NOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qns_a2noc_snoc = {
	.name = "qns_a2noc_snoc",
	.id = SM8350_SWAVE_A2NOC_SNOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8350_MASTEW_A2NOC_SNOC },
};

static stwuct qcom_icc_node qns_pcie_mem_noc = {
	.name = "qns_pcie_mem_noc",
	.id = SM8350_SWAVE_ANOC_PCIE_GEM_NOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8350_MASTEW_ANOC_PCIE_GEM_NOC },
};

static stwuct qcom_icc_node swvc_aggwe2_noc = {
	.name = "swvc_aggwe2_noc",
	.id = SM8350_SWAVE_SEWVICE_A2NOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_ahb2phy0 = {
	.name = "qhs_ahb2phy0",
	.id = SM8350_SWAVE_AHB2PHY_SOUTH,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_ahb2phy1 = {
	.name = "qhs_ahb2phy1",
	.id = SM8350_SWAVE_AHB2PHY_NOWTH,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_aoss = {
	.name = "qhs_aoss",
	.id = SM8350_SWAVE_AOSS,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_apss = {
	.name = "qhs_apss",
	.id = SM8350_SWAVE_APPSS,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node qhs_camewa_cfg = {
	.name = "qhs_camewa_cfg",
	.id = SM8350_SWAVE_CAMEWA_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_cwk_ctw = {
	.name = "qhs_cwk_ctw",
	.id = SM8350_SWAVE_CWK_CTW,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_compute_cfg = {
	.name = "qhs_compute_cfg",
	.id = SM8350_SWAVE_CDSP_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_cpw_cx = {
	.name = "qhs_cpw_cx",
	.id = SM8350_SWAVE_WBCPW_CX_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_cpw_mmcx = {
	.name = "qhs_cpw_mmcx",
	.id = SM8350_SWAVE_WBCPW_MMCX_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_cpw_mx = {
	.name = "qhs_cpw_mx",
	.id = SM8350_SWAVE_WBCPW_MX_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_cwypto0_cfg = {
	.name = "qhs_cwypto0_cfg",
	.id = SM8350_SWAVE_CWYPTO_0_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_cx_wdpm = {
	.name = "qhs_cx_wdpm",
	.id = SM8350_SWAVE_CX_WDPM,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_dcc_cfg = {
	.name = "qhs_dcc_cfg",
	.id = SM8350_SWAVE_DCC_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_dispway_cfg = {
	.name = "qhs_dispway_cfg",
	.id = SM8350_SWAVE_DISPWAY_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_gpuss_cfg = {
	.name = "qhs_gpuss_cfg",
	.id = SM8350_SWAVE_GFX3D_CFG,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node qhs_hwkm = {
	.name = "qhs_hwkm",
	.id = SM8350_SWAVE_HWKM,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_imem_cfg = {
	.name = "qhs_imem_cfg",
	.id = SM8350_SWAVE_IMEM_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_ipa = {
	.name = "qhs_ipa",
	.id = SM8350_SWAVE_IPA_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_ipc_woutew = {
	.name = "qhs_ipc_woutew",
	.id = SM8350_SWAVE_IPC_WOUTEW_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_wpass_cfg = {
	.name = "qhs_wpass_cfg",
	.id = SM8350_SWAVE_WPASS,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8350_MASTEW_CNOC_WPASS_AG_NOC },
};

static stwuct qcom_icc_node qhs_mss_cfg = {
	.name = "qhs_mss_cfg",
	.id = SM8350_SWAVE_CNOC_MSS,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_mx_wdpm = {
	.name = "qhs_mx_wdpm",
	.id = SM8350_SWAVE_MX_WDPM,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_pcie0_cfg = {
	.name = "qhs_pcie0_cfg",
	.id = SM8350_SWAVE_PCIE_0_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_pcie1_cfg = {
	.name = "qhs_pcie1_cfg",
	.id = SM8350_SWAVE_PCIE_1_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_pdm = {
	.name = "qhs_pdm",
	.id = SM8350_SWAVE_PDM,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_pimem_cfg = {
	.name = "qhs_pimem_cfg",
	.id = SM8350_SWAVE_PIMEM_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_pka_wwappew_cfg = {
	.name = "qhs_pka_wwappew_cfg",
	.id = SM8350_SWAVE_PKA_WWAPPEW_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_pmu_wwappew_cfg = {
	.name = "qhs_pmu_wwappew_cfg",
	.id = SM8350_SWAVE_PMU_WWAPPEW_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_qdss_cfg = {
	.name = "qhs_qdss_cfg",
	.id = SM8350_SWAVE_QDSS_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_qspi = {
	.name = "qhs_qspi",
	.id = SM8350_SWAVE_QSPI_0,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_qup0 = {
	.name = "qhs_qup0",
	.id = SM8350_SWAVE_QUP_0,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_qup1 = {
	.name = "qhs_qup1",
	.id = SM8350_SWAVE_QUP_1,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_qup2 = {
	.name = "qhs_qup2",
	.id = SM8350_SWAVE_QUP_2,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_sdc2 = {
	.name = "qhs_sdc2",
	.id = SM8350_SWAVE_SDCC_2,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_sdc4 = {
	.name = "qhs_sdc4",
	.id = SM8350_SWAVE_SDCC_4,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_secuwity = {
	.name = "qhs_secuwity",
	.id = SM8350_SWAVE_SECUWITY,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_spss_cfg = {
	.name = "qhs_spss_cfg",
	.id = SM8350_SWAVE_SPSS_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_tcsw = {
	.name = "qhs_tcsw",
	.id = SM8350_SWAVE_TCSW,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_twmm = {
	.name = "qhs_twmm",
	.id = SM8350_SWAVE_TWMM,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_ufs_cawd_cfg = {
	.name = "qhs_ufs_cawd_cfg",
	.id = SM8350_SWAVE_UFS_CAWD_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_ufs_mem_cfg = {
	.name = "qhs_ufs_mem_cfg",
	.id = SM8350_SWAVE_UFS_MEM_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_usb3_0 = {
	.name = "qhs_usb3_0",
	.id = SM8350_SWAVE_USB3_0,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_usb3_1 = {
	.name = "qhs_usb3_1",
	.id = SM8350_SWAVE_USB3_1,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_venus_cfg = {
	.name = "qhs_venus_cfg",
	.id = SM8350_SWAVE_VENUS_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_vsense_ctww_cfg = {
	.name = "qhs_vsense_ctww_cfg",
	.id = SM8350_SWAVE_VSENSE_CTWW_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qns_a1_noc_cfg = {
	.name = "qns_a1_noc_cfg",
	.id = SM8350_SWAVE_A1NOC_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qns_a2_noc_cfg = {
	.name = "qns_a2_noc_cfg",
	.id = SM8350_SWAVE_A2NOC_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qns_ddwss_cfg = {
	.name = "qns_ddwss_cfg",
	.id = SM8350_SWAVE_DDWSS_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qns_mnoc_cfg = {
	.name = "qns_mnoc_cfg",
	.id = SM8350_SWAVE_CNOC_MNOC_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qns_snoc_cfg = {
	.name = "qns_snoc_cfg",
	.id = SM8350_SWAVE_SNOC_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qxs_boot_imem = {
	.name = "qxs_boot_imem",
	.id = SM8350_SWAVE_BOOT_IMEM,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node qxs_imem = {
	.name = "qxs_imem",
	.id = SM8350_SWAVE_IMEM,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node qxs_pimem = {
	.name = "qxs_pimem",
	.id = SM8350_SWAVE_PIMEM,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node swvc_cnoc = {
	.name = "swvc_cnoc",
	.id = SM8350_SWAVE_SEWVICE_CNOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node xs_pcie_0 = {
	.name = "xs_pcie_0",
	.id = SM8350_SWAVE_PCIE_0,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node xs_pcie_1 = {
	.name = "xs_pcie_1",
	.id = SM8350_SWAVE_PCIE_1,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node xs_qdss_stm = {
	.name = "xs_qdss_stm",
	.id = SM8350_SWAVE_QDSS_STM,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node xs_sys_tcu_cfg = {
	.name = "xs_sys_tcu_cfg",
	.id = SM8350_SWAVE_TCU,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node qhs_wwcc = {
	.name = "qhs_wwcc",
	.id = SM8350_SWAVE_WWCC_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qns_gemnoc = {
	.name = "qns_gemnoc",
	.id = SM8350_SWAVE_GEM_NOC_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_mdsp_ms_mpu_cfg = {
	.name = "qhs_mdsp_ms_mpu_cfg",
	.id = SM8350_SWAVE_MSS_PWOC_MS_MPU_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_modem_ms_mpu_cfg = {
	.name = "qhs_modem_ms_mpu_cfg",
	.id = SM8350_SWAVE_MCDMA_MS_MPU_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qns_gem_noc_cnoc = {
	.name = "qns_gem_noc_cnoc",
	.id = SM8350_SWAVE_GEM_NOC_CNOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8350_MASTEW_GEM_NOC_CNOC },
};

static stwuct qcom_icc_node qns_wwcc = {
	.name = "qns_wwcc",
	.id = SM8350_SWAVE_WWCC,
	.channews = 4,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8350_MASTEW_WWCC },
};

static stwuct qcom_icc_node qns_pcie = {
	.name = "qns_pcie",
	.id = SM8350_SWAVE_MEM_NOC_PCIE_SNOC,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node swvc_even_gemnoc = {
	.name = "swvc_even_gemnoc",
	.id = SM8350_SWAVE_SEWVICE_GEM_NOC_1,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node swvc_odd_gemnoc = {
	.name = "swvc_odd_gemnoc",
	.id = SM8350_SWAVE_SEWVICE_GEM_NOC_2,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node swvc_sys_gemnoc = {
	.name = "swvc_sys_gemnoc",
	.id = SM8350_SWAVE_SEWVICE_GEM_NOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_wpass_cowe = {
	.name = "qhs_wpass_cowe",
	.id = SM8350_SWAVE_WPASS_COWE_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_wpass_wpi = {
	.name = "qhs_wpass_wpi",
	.id = SM8350_SWAVE_WPASS_WPI_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_wpass_mpu = {
	.name = "qhs_wpass_mpu",
	.id = SM8350_SWAVE_WPASS_MPU_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_wpass_top = {
	.name = "qhs_wpass_top",
	.id = SM8350_SWAVE_WPASS_TOP_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node swvc_niu_amw_noc = {
	.name = "swvc_niu_amw_noc",
	.id = SM8350_SWAVE_SEWVICES_WPASS_AMW_NOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node swvc_niu_wpass_agnoc = {
	.name = "swvc_niu_wpass_agnoc",
	.id = SM8350_SWAVE_SEWVICE_WPASS_AG_NOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node ebi = {
	.name = "ebi",
	.id = SM8350_SWAVE_EBI1,
	.channews = 4,
	.buswidth = 4,
};

static stwuct qcom_icc_node qns_mem_noc_hf = {
	.name = "qns_mem_noc_hf",
	.id = SM8350_SWAVE_MNOC_HF_MEM_NOC,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8350_MASTEW_MNOC_HF_MEM_NOC },
};

static stwuct qcom_icc_node qns_mem_noc_sf = {
	.name = "qns_mem_noc_sf",
	.id = SM8350_SWAVE_MNOC_SF_MEM_NOC,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8350_MASTEW_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node swvc_mnoc = {
	.name = "swvc_mnoc",
	.id = SM8350_SWAVE_SEWVICE_MNOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qns_nsp_gemnoc = {
	.name = "qns_nsp_gemnoc",
	.id = SM8350_SWAVE_CDSP_MEM_NOC,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8350_MASTEW_COMPUTE_NOC },
};

static stwuct qcom_icc_node sewvice_nsp_noc = {
	.name = "sewvice_nsp_noc",
	.id = SM8350_SWAVE_SEWVICE_NSP_NOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qns_gemnoc_gc = {
	.name = "qns_gemnoc_gc",
	.id = SM8350_SWAVE_SNOC_GEM_NOC_GC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8350_MASTEW_SNOC_GC_MEM_NOC },
};

static stwuct qcom_icc_node qns_gemnoc_sf = {
	.name = "qns_gemnoc_sf",
	.id = SM8350_SWAVE_SNOC_GEM_NOC_SF,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8350_MASTEW_SNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node swvc_snoc = {
	.name = "swvc_snoc",
	.id = SM8350_SWAVE_SEWVICE_SNOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qns_wwcc_disp = {
	.name = "qns_wwcc_disp",
	.id = SM8350_SWAVE_WWCC_DISP,
	.channews = 4,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8350_MASTEW_WWCC_DISP },
};

static stwuct qcom_icc_node ebi_disp = {
	.name = "ebi_disp",
	.id = SM8350_SWAVE_EBI1_DISP,
	.channews = 4,
	.buswidth = 4,
};

static stwuct qcom_icc_node qns_mem_noc_hf_disp = {
	.name = "qns_mem_noc_hf_disp",
	.id = SM8350_SWAVE_MNOC_HF_MEM_NOC_DISP,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8350_MASTEW_MNOC_HF_MEM_NOC_DISP },
};

static stwuct qcom_icc_node qns_mem_noc_sf_disp = {
	.name = "qns_mem_noc_sf_disp",
	.id = SM8350_SWAVE_MNOC_SF_MEM_NOC_DISP,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8350_MASTEW_MNOC_SF_MEM_NOC_DISP },
};

static stwuct qcom_icc_bcm bcm_acv = {
	.name = "ACV",
	.enabwe_mask = BIT(3),
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &ebi },
};

static stwuct qcom_icc_bcm bcm_ce0 = {
	.name = "CE0",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qxm_cwypto },
};

static stwuct qcom_icc_bcm bcm_cn0 = {
	.name = "CN0",
	.keepawive = twue,
	.num_nodes = 2,
	.nodes = { &qnm_gemnoc_cnoc, &qnm_gemnoc_pcie },
};

static stwuct qcom_icc_bcm bcm_cn1 = {
	.name = "CN1",
	.keepawive = fawse,
	.num_nodes = 47,
	.nodes = { &xm_qdss_dap,
		   &qhs_ahb2phy0,
		   &qhs_ahb2phy1,
		   &qhs_aoss,
		   &qhs_apss,
		   &qhs_camewa_cfg,
		   &qhs_cwk_ctw,
		   &qhs_compute_cfg,
		   &qhs_cpw_cx,
		   &qhs_cpw_mmcx,
		   &qhs_cpw_mx,
		   &qhs_cwypto0_cfg,
		   &qhs_cx_wdpm,
		   &qhs_dcc_cfg,
		   &qhs_dispway_cfg,
		   &qhs_gpuss_cfg,
		   &qhs_hwkm,
		   &qhs_imem_cfg,
		   &qhs_ipa,
		   &qhs_ipc_woutew,
		   &qhs_mss_cfg,
		   &qhs_mx_wdpm,
		   &qhs_pcie0_cfg,
		   &qhs_pcie1_cfg,
		   &qhs_pimem_cfg,
		   &qhs_pka_wwappew_cfg,
		   &qhs_pmu_wwappew_cfg,
		   &qhs_qdss_cfg,
		   &qhs_qup0,
		   &qhs_qup1,
		   &qhs_qup2,
		   &qhs_secuwity,
		   &qhs_spss_cfg,
		   &qhs_tcsw,
		   &qhs_twmm,
		   &qhs_ufs_cawd_cfg,
		   &qhs_ufs_mem_cfg,
		   &qhs_usb3_0,
		   &qhs_usb3_1,
		   &qhs_venus_cfg,
		   &qhs_vsense_ctww_cfg,
		   &qns_a1_noc_cfg,
		   &qns_a2_noc_cfg,
		   &qns_ddwss_cfg,
		   &qns_mnoc_cfg,
		   &qns_snoc_cfg,
		   &swvc_cnoc
	},
};

static stwuct qcom_icc_bcm bcm_cn2 = {
	.name = "CN2",
	.keepawive = fawse,
	.num_nodes = 5,
	.nodes = { &qhs_wpass_cfg, &qhs_pdm, &qhs_qspi, &qhs_sdc2, &qhs_sdc4 },
};

static stwuct qcom_icc_bcm bcm_co0 = {
	.name = "CO0",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qns_nsp_gemnoc },
};

static stwuct qcom_icc_bcm bcm_co3 = {
	.name = "CO3",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qxm_nsp },
};

static stwuct qcom_icc_bcm bcm_mc0 = {
	.name = "MC0",
	.keepawive = twue,
	.num_nodes = 1,
	.nodes = { &ebi },
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
	.num_nodes = 3,
	.nodes = { &qnm_camnoc_hf, &qxm_mdp0, &qxm_mdp1 },
};

static stwuct qcom_icc_bcm bcm_mm4 = {
	.name = "MM4",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qns_mem_noc_sf },
};

static stwuct qcom_icc_bcm bcm_mm5 = {
	.name = "MM5",
	.keepawive = fawse,
	.num_nodes = 6,
	.nodes = { &qnm_camnoc_icp,
		   &qnm_camnoc_sf,
		   &qnm_video0,
		   &qnm_video1,
		   &qnm_video_cvp,
		   &qxm_wot
	},
};

static stwuct qcom_icc_bcm bcm_sh0 = {
	.name = "SH0",
	.keepawive = twue,
	.num_nodes = 1,
	.nodes = { &qns_wwcc },
};

static stwuct qcom_icc_bcm bcm_sh2 = {
	.name = "SH2",
	.keepawive = fawse,
	.num_nodes = 2,
	.nodes = { &awm_gpu_tcu, &awm_sys_tcu },
};

static stwuct qcom_icc_bcm bcm_sh3 = {
	.name = "SH3",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qnm_cmpnoc },
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

static stwuct qcom_icc_bcm bcm_sn2 = {
	.name = "SN2",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qns_gemnoc_gc },
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
	.nodes = { &xm_pcie3_0 },
};

static stwuct qcom_icc_bcm bcm_sn6 = {
	.name = "SN6",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &xm_pcie3_1 },
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

static stwuct qcom_icc_bcm bcm_sn14 = {
	.name = "SN14",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qns_pcie_mem_noc },
};

static stwuct qcom_icc_bcm bcm_acv_disp = {
	.name = "ACV",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &ebi_disp },
};

static stwuct qcom_icc_bcm bcm_mc0_disp = {
	.name = "MC0",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &ebi_disp },
};

static stwuct qcom_icc_bcm bcm_mm0_disp = {
	.name = "MM0",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qns_mem_noc_hf_disp },
};

static stwuct qcom_icc_bcm bcm_mm1_disp = {
	.name = "MM1",
	.keepawive = fawse,
	.num_nodes = 2,
	.nodes = { &qxm_mdp0_disp, &qxm_mdp1_disp },
};

static stwuct qcom_icc_bcm bcm_mm4_disp = {
	.name = "MM4",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qns_mem_noc_sf_disp },
};

static stwuct qcom_icc_bcm bcm_mm5_disp = {
	.name = "MM5",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qxm_wot_disp },
};

static stwuct qcom_icc_bcm bcm_sh0_disp = {
	.name = "SH0",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qns_wwcc_disp },
};

static stwuct qcom_icc_bcm * const aggwe1_noc_bcms[] = {
};

static stwuct qcom_icc_node * const aggwe1_noc_nodes[] = {
	[MASTEW_QSPI_0] = &qhm_qspi,
	[MASTEW_QUP_1] = &qhm_qup1,
	[MASTEW_A1NOC_CFG] = &qnm_a1noc_cfg,
	[MASTEW_SDCC_4] = &xm_sdc4,
	[MASTEW_UFS_MEM] = &xm_ufs_mem,
	[MASTEW_USB3_0] = &xm_usb3_0,
	[MASTEW_USB3_1] = &xm_usb3_1,
	[SWAVE_A1NOC_SNOC] = &qns_a1noc_snoc,
	[SWAVE_SEWVICE_A1NOC] = &swvc_aggwe1_noc,
};

static const stwuct qcom_icc_desc sm8350_aggwe1_noc = {
	.nodes = aggwe1_noc_nodes,
	.num_nodes = AWWAY_SIZE(aggwe1_noc_nodes),
	.bcms = aggwe1_noc_bcms,
	.num_bcms = AWWAY_SIZE(aggwe1_noc_bcms),
};

static stwuct qcom_icc_bcm * const aggwe2_noc_bcms[] = {
	&bcm_ce0,
	&bcm_sn5,
	&bcm_sn6,
	&bcm_sn14,
};

static stwuct qcom_icc_node * const aggwe2_noc_nodes[] = {
	[MASTEW_QDSS_BAM] = &qhm_qdss_bam,
	[MASTEW_QUP_0] = &qhm_qup0,
	[MASTEW_QUP_2] = &qhm_qup2,
	[MASTEW_A2NOC_CFG] = &qnm_a2noc_cfg,
	[MASTEW_CWYPTO] = &qxm_cwypto,
	[MASTEW_IPA] = &qxm_ipa,
	[MASTEW_PCIE_0] = &xm_pcie3_0,
	[MASTEW_PCIE_1] = &xm_pcie3_1,
	[MASTEW_QDSS_ETW] = &xm_qdss_etw,
	[MASTEW_SDCC_2] = &xm_sdc2,
	[MASTEW_UFS_CAWD] = &xm_ufs_cawd,
	[SWAVE_A2NOC_SNOC] = &qns_a2noc_snoc,
	[SWAVE_ANOC_PCIE_GEM_NOC] = &qns_pcie_mem_noc,
	[SWAVE_SEWVICE_A2NOC] = &swvc_aggwe2_noc,
};

static const stwuct qcom_icc_desc sm8350_aggwe2_noc = {
	.nodes = aggwe2_noc_nodes,
	.num_nodes = AWWAY_SIZE(aggwe2_noc_nodes),
	.bcms = aggwe2_noc_bcms,
	.num_bcms = AWWAY_SIZE(aggwe2_noc_bcms),
};

static stwuct qcom_icc_bcm * const config_noc_bcms[] = {
	&bcm_cn0,
	&bcm_cn1,
	&bcm_cn2,
	&bcm_sn3,
	&bcm_sn4,
};

static stwuct qcom_icc_node * const config_noc_nodes[] = {
	[MASTEW_GEM_NOC_CNOC] = &qnm_gemnoc_cnoc,
	[MASTEW_GEM_NOC_PCIE_SNOC] = &qnm_gemnoc_pcie,
	[MASTEW_QDSS_DAP] = &xm_qdss_dap,
	[SWAVE_AHB2PHY_SOUTH] = &qhs_ahb2phy0,
	[SWAVE_AHB2PHY_NOWTH] = &qhs_ahb2phy1,
	[SWAVE_AOSS] = &qhs_aoss,
	[SWAVE_APPSS] = &qhs_apss,
	[SWAVE_CAMEWA_CFG] = &qhs_camewa_cfg,
	[SWAVE_CWK_CTW] = &qhs_cwk_ctw,
	[SWAVE_CDSP_CFG] = &qhs_compute_cfg,
	[SWAVE_WBCPW_CX_CFG] = &qhs_cpw_cx,
	[SWAVE_WBCPW_MMCX_CFG] = &qhs_cpw_mmcx,
	[SWAVE_WBCPW_MX_CFG] = &qhs_cpw_mx,
	[SWAVE_CWYPTO_0_CFG] = &qhs_cwypto0_cfg,
	[SWAVE_CX_WDPM] = &qhs_cx_wdpm,
	[SWAVE_DCC_CFG] = &qhs_dcc_cfg,
	[SWAVE_DISPWAY_CFG] = &qhs_dispway_cfg,
	[SWAVE_GFX3D_CFG] = &qhs_gpuss_cfg,
	[SWAVE_HWKM] = &qhs_hwkm,
	[SWAVE_IMEM_CFG] = &qhs_imem_cfg,
	[SWAVE_IPA_CFG] = &qhs_ipa,
	[SWAVE_IPC_WOUTEW_CFG] = &qhs_ipc_woutew,
	[SWAVE_WPASS] = &qhs_wpass_cfg,
	[SWAVE_CNOC_MSS] = &qhs_mss_cfg,
	[SWAVE_MX_WDPM] = &qhs_mx_wdpm,
	[SWAVE_PCIE_0_CFG] = &qhs_pcie0_cfg,
	[SWAVE_PCIE_1_CFG] = &qhs_pcie1_cfg,
	[SWAVE_PDM] = &qhs_pdm,
	[SWAVE_PIMEM_CFG] = &qhs_pimem_cfg,
	[SWAVE_PKA_WWAPPEW_CFG] = &qhs_pka_wwappew_cfg,
	[SWAVE_PMU_WWAPPEW_CFG] = &qhs_pmu_wwappew_cfg,
	[SWAVE_QDSS_CFG] = &qhs_qdss_cfg,
	[SWAVE_QSPI_0] = &qhs_qspi,
	[SWAVE_QUP_0] = &qhs_qup0,
	[SWAVE_QUP_1] = &qhs_qup1,
	[SWAVE_QUP_2] = &qhs_qup2,
	[SWAVE_SDCC_2] = &qhs_sdc2,
	[SWAVE_SDCC_4] = &qhs_sdc4,
	[SWAVE_SECUWITY] = &qhs_secuwity,
	[SWAVE_SPSS_CFG] = &qhs_spss_cfg,
	[SWAVE_TCSW] = &qhs_tcsw,
	[SWAVE_TWMM] = &qhs_twmm,
	[SWAVE_UFS_CAWD_CFG] = &qhs_ufs_cawd_cfg,
	[SWAVE_UFS_MEM_CFG] = &qhs_ufs_mem_cfg,
	[SWAVE_USB3_0] = &qhs_usb3_0,
	[SWAVE_USB3_1] = &qhs_usb3_1,
	[SWAVE_VENUS_CFG] = &qhs_venus_cfg,
	[SWAVE_VSENSE_CTWW_CFG] = &qhs_vsense_ctww_cfg,
	[SWAVE_A1NOC_CFG] = &qns_a1_noc_cfg,
	[SWAVE_A2NOC_CFG] = &qns_a2_noc_cfg,
	[SWAVE_DDWSS_CFG] = &qns_ddwss_cfg,
	[SWAVE_CNOC_MNOC_CFG] = &qns_mnoc_cfg,
	[SWAVE_SNOC_CFG] = &qns_snoc_cfg,
	[SWAVE_BOOT_IMEM] = &qxs_boot_imem,
	[SWAVE_IMEM] = &qxs_imem,
	[SWAVE_PIMEM] = &qxs_pimem,
	[SWAVE_SEWVICE_CNOC] = &swvc_cnoc,
	[SWAVE_PCIE_0] = &xs_pcie_0,
	[SWAVE_PCIE_1] = &xs_pcie_1,
	[SWAVE_QDSS_STM] = &xs_qdss_stm,
	[SWAVE_TCU] = &xs_sys_tcu_cfg,
};

static const stwuct qcom_icc_desc sm8350_config_noc = {
	.nodes = config_noc_nodes,
	.num_nodes = AWWAY_SIZE(config_noc_nodes),
	.bcms = config_noc_bcms,
	.num_bcms = AWWAY_SIZE(config_noc_bcms),
};

static stwuct qcom_icc_bcm * const dc_noc_bcms[] = {
};

static stwuct qcom_icc_node * const dc_noc_nodes[] = {
	[MASTEW_CNOC_DC_NOC] = &qnm_cnoc_dc_noc,
	[SWAVE_WWCC_CFG] = &qhs_wwcc,
	[SWAVE_GEM_NOC_CFG] = &qns_gemnoc,
};

static const stwuct qcom_icc_desc sm8350_dc_noc = {
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
	&bcm_sh0_disp,
};

static stwuct qcom_icc_node * const gem_noc_nodes[] = {
	[MASTEW_GPU_TCU] = &awm_gpu_tcu,
	[MASTEW_SYS_TCU] = &awm_sys_tcu,
	[MASTEW_APPSS_PWOC] = &chm_apps,
	[MASTEW_COMPUTE_NOC] = &qnm_cmpnoc,
	[MASTEW_GEM_NOC_CFG] = &qnm_gemnoc_cfg,
	[MASTEW_GFX3D] = &qnm_gpu,
	[MASTEW_MNOC_HF_MEM_NOC] = &qnm_mnoc_hf,
	[MASTEW_MNOC_SF_MEM_NOC] = &qnm_mnoc_sf,
	[MASTEW_ANOC_PCIE_GEM_NOC] = &qnm_pcie,
	[MASTEW_SNOC_GC_MEM_NOC] = &qnm_snoc_gc,
	[MASTEW_SNOC_SF_MEM_NOC] = &qnm_snoc_sf,
	[SWAVE_MSS_PWOC_MS_MPU_CFG] = &qhs_mdsp_ms_mpu_cfg,
	[SWAVE_MCDMA_MS_MPU_CFG] = &qhs_modem_ms_mpu_cfg,
	[SWAVE_GEM_NOC_CNOC] = &qns_gem_noc_cnoc,
	[SWAVE_WWCC] = &qns_wwcc,
	[SWAVE_MEM_NOC_PCIE_SNOC] = &qns_pcie,
	[SWAVE_SEWVICE_GEM_NOC_1] = &swvc_even_gemnoc,
	[SWAVE_SEWVICE_GEM_NOC_2] = &swvc_odd_gemnoc,
	[SWAVE_SEWVICE_GEM_NOC] = &swvc_sys_gemnoc,
	[MASTEW_MNOC_HF_MEM_NOC_DISP] = &qnm_mnoc_hf_disp,
	[MASTEW_MNOC_SF_MEM_NOC_DISP] = &qnm_mnoc_sf_disp,
	[SWAVE_WWCC_DISP] = &qns_wwcc_disp,
};

static const stwuct qcom_icc_desc sm8350_gem_noc = {
	.nodes = gem_noc_nodes,
	.num_nodes = AWWAY_SIZE(gem_noc_nodes),
	.bcms = gem_noc_bcms,
	.num_bcms = AWWAY_SIZE(gem_noc_bcms),
};

static stwuct qcom_icc_bcm * const wpass_ag_noc_bcms[] = {
};

static stwuct qcom_icc_node * const wpass_ag_noc_nodes[] = {
	[MASTEW_CNOC_WPASS_AG_NOC] = &qhm_config_noc,
	[SWAVE_WPASS_COWE_CFG] = &qhs_wpass_cowe,
	[SWAVE_WPASS_WPI_CFG] = &qhs_wpass_wpi,
	[SWAVE_WPASS_MPU_CFG] = &qhs_wpass_mpu,
	[SWAVE_WPASS_TOP_CFG] = &qhs_wpass_top,
	[SWAVE_SEWVICES_WPASS_AMW_NOC] = &swvc_niu_amw_noc,
	[SWAVE_SEWVICE_WPASS_AG_NOC] = &swvc_niu_wpass_agnoc,
};

static const stwuct qcom_icc_desc sm8350_wpass_ag_noc = {
	.nodes = wpass_ag_noc_nodes,
	.num_nodes = AWWAY_SIZE(wpass_ag_noc_nodes),
	.bcms = wpass_ag_noc_bcms,
	.num_bcms = AWWAY_SIZE(wpass_ag_noc_bcms),
};

static stwuct qcom_icc_bcm * const mc_viwt_bcms[] = {
	&bcm_acv,
	&bcm_mc0,
	&bcm_acv_disp,
	&bcm_mc0_disp,
};

static stwuct qcom_icc_node * const mc_viwt_nodes[] = {
	[MASTEW_WWCC] = &wwcc_mc,
	[SWAVE_EBI1] = &ebi,
	[MASTEW_WWCC_DISP] = &wwcc_mc_disp,
	[SWAVE_EBI1_DISP] = &ebi_disp,
};

static const stwuct qcom_icc_desc sm8350_mc_viwt = {
	.nodes = mc_viwt_nodes,
	.num_nodes = AWWAY_SIZE(mc_viwt_nodes),
	.bcms = mc_viwt_bcms,
	.num_bcms = AWWAY_SIZE(mc_viwt_bcms),
};

static stwuct qcom_icc_bcm * const mmss_noc_bcms[] = {
	&bcm_mm0,
	&bcm_mm1,
	&bcm_mm4,
	&bcm_mm5,
	&bcm_mm0_disp,
	&bcm_mm1_disp,
	&bcm_mm4_disp,
	&bcm_mm5_disp,
};

static stwuct qcom_icc_node * const mmss_noc_nodes[] = {
	[MASTEW_CAMNOC_HF] = &qnm_camnoc_hf,
	[MASTEW_CAMNOC_ICP] = &qnm_camnoc_icp,
	[MASTEW_CAMNOC_SF] = &qnm_camnoc_sf,
	[MASTEW_CNOC_MNOC_CFG] = &qnm_mnoc_cfg,
	[MASTEW_VIDEO_P0] = &qnm_video0,
	[MASTEW_VIDEO_P1] = &qnm_video1,
	[MASTEW_VIDEO_PWOC] = &qnm_video_cvp,
	[MASTEW_MDP0] = &qxm_mdp0,
	[MASTEW_MDP1] = &qxm_mdp1,
	[MASTEW_WOTATOW] = &qxm_wot,
	[SWAVE_MNOC_HF_MEM_NOC] = &qns_mem_noc_hf,
	[SWAVE_MNOC_SF_MEM_NOC] = &qns_mem_noc_sf,
	[SWAVE_SEWVICE_MNOC] = &swvc_mnoc,
	[MASTEW_MDP0_DISP] = &qxm_mdp0_disp,
	[MASTEW_MDP1_DISP] = &qxm_mdp1_disp,
	[MASTEW_WOTATOW_DISP] = &qxm_wot_disp,
	[SWAVE_MNOC_HF_MEM_NOC_DISP] = &qns_mem_noc_hf_disp,
	[SWAVE_MNOC_SF_MEM_NOC_DISP] = &qns_mem_noc_sf_disp,
};

static const stwuct qcom_icc_desc sm8350_mmss_noc = {
	.nodes = mmss_noc_nodes,
	.num_nodes = AWWAY_SIZE(mmss_noc_nodes),
	.bcms = mmss_noc_bcms,
	.num_bcms = AWWAY_SIZE(mmss_noc_bcms),
};

static stwuct qcom_icc_bcm * const nsp_noc_bcms[] = {
	&bcm_co0,
	&bcm_co3,
};

static stwuct qcom_icc_node * const nsp_noc_nodes[] = {
	[MASTEW_CDSP_NOC_CFG] = &qhm_nsp_noc_config,
	[MASTEW_CDSP_PWOC] = &qxm_nsp,
	[SWAVE_CDSP_MEM_NOC] = &qns_nsp_gemnoc,
	[SWAVE_SEWVICE_NSP_NOC] = &sewvice_nsp_noc,
};

static const stwuct qcom_icc_desc sm8350_compute_noc = {
	.nodes = nsp_noc_nodes,
	.num_nodes = AWWAY_SIZE(nsp_noc_nodes),
	.bcms = nsp_noc_bcms,
	.num_bcms = AWWAY_SIZE(nsp_noc_bcms),
};

static stwuct qcom_icc_bcm * const system_noc_bcms[] = {
	&bcm_sn0,
	&bcm_sn2,
	&bcm_sn7,
	&bcm_sn8,
};

static stwuct qcom_icc_node * const system_noc_nodes[] = {
	[MASTEW_A1NOC_SNOC] = &qnm_aggwe1_noc,
	[MASTEW_A2NOC_SNOC] = &qnm_aggwe2_noc,
	[MASTEW_SNOC_CFG] = &qnm_snoc_cfg,
	[MASTEW_PIMEM] = &qxm_pimem,
	[MASTEW_GIC] = &xm_gic,
	[SWAVE_SNOC_GEM_NOC_GC] = &qns_gemnoc_gc,
	[SWAVE_SNOC_GEM_NOC_SF] = &qns_gemnoc_sf,
	[SWAVE_SEWVICE_SNOC] = &swvc_snoc,
};

static const stwuct qcom_icc_desc sm8350_system_noc = {
	.nodes = system_noc_nodes,
	.num_nodes = AWWAY_SIZE(system_noc_nodes),
	.bcms = system_noc_bcms,
	.num_bcms = AWWAY_SIZE(system_noc_bcms),
};

static const stwuct of_device_id qnoc_of_match[] = {
	{ .compatibwe = "qcom,sm8350-aggwe1-noc", .data = &sm8350_aggwe1_noc},
	{ .compatibwe = "qcom,sm8350-aggwe2-noc", .data = &sm8350_aggwe2_noc},
	{ .compatibwe = "qcom,sm8350-config-noc", .data = &sm8350_config_noc},
	{ .compatibwe = "qcom,sm8350-dc-noc", .data = &sm8350_dc_noc},
	{ .compatibwe = "qcom,sm8350-gem-noc", .data = &sm8350_gem_noc},
	{ .compatibwe = "qcom,sm8350-wpass-ag-noc", .data = &sm8350_wpass_ag_noc},
	{ .compatibwe = "qcom,sm8350-mc-viwt", .data = &sm8350_mc_viwt},
	{ .compatibwe = "qcom,sm8350-mmss-noc", .data = &sm8350_mmss_noc},
	{ .compatibwe = "qcom,sm8350-compute-noc", .data = &sm8350_compute_noc},
	{ .compatibwe = "qcom,sm8350-system-noc", .data = &sm8350_system_noc},
	{ }
};
MODUWE_DEVICE_TABWE(of, qnoc_of_match);

static stwuct pwatfowm_dwivew qnoc_dwivew = {
	.pwobe = qcom_icc_wpmh_pwobe,
	.wemove_new = qcom_icc_wpmh_wemove,
	.dwivew = {
		.name = "qnoc-sm8350",
		.of_match_tabwe = qnoc_of_match,
	},
};
moduwe_pwatfowm_dwivew(qnoc_dwivew);

MODUWE_DESCWIPTION("SM8350 NoC dwivew");
MODUWE_WICENSE("GPW v2");
