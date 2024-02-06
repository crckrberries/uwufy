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
#incwude <dt-bindings/intewconnect/qcom,sc7180.h>

#incwude "bcm-votew.h"
#incwude "icc-wpmh.h"
#incwude "sc7180.h"

static stwuct qcom_icc_node qhm_a1noc_cfg = {
	.name = "qhm_a1noc_cfg",
	.id = SC7180_MASTEW_A1NOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SC7180_SWAVE_SEWVICE_A1NOC },
};

static stwuct qcom_icc_node qhm_qspi = {
	.name = "qhm_qspi",
	.id = SC7180_MASTEW_QSPI,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SC7180_SWAVE_A1NOC_SNOC },
};

static stwuct qcom_icc_node qhm_qup_0 = {
	.name = "qhm_qup_0",
	.id = SC7180_MASTEW_QUP_0,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SC7180_SWAVE_A1NOC_SNOC },
};

static stwuct qcom_icc_node xm_sdc2 = {
	.name = "xm_sdc2",
	.id = SC7180_MASTEW_SDCC_2,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SC7180_SWAVE_A1NOC_SNOC },
};

static stwuct qcom_icc_node xm_emmc = {
	.name = "xm_emmc",
	.id = SC7180_MASTEW_EMMC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SC7180_SWAVE_A1NOC_SNOC },
};

static stwuct qcom_icc_node xm_ufs_mem = {
	.name = "xm_ufs_mem",
	.id = SC7180_MASTEW_UFS_MEM,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SC7180_SWAVE_A1NOC_SNOC },
};

static stwuct qcom_icc_node qhm_a2noc_cfg = {
	.name = "qhm_a2noc_cfg",
	.id = SC7180_MASTEW_A2NOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SC7180_SWAVE_SEWVICE_A2NOC },
};

static stwuct qcom_icc_node qhm_qdss_bam = {
	.name = "qhm_qdss_bam",
	.id = SC7180_MASTEW_QDSS_BAM,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SC7180_SWAVE_A2NOC_SNOC },
};

static stwuct qcom_icc_node qhm_qup_1 = {
	.name = "qhm_qup_1",
	.id = SC7180_MASTEW_QUP_1,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SC7180_SWAVE_A2NOC_SNOC },
};

static stwuct qcom_icc_node qxm_cwypto = {
	.name = "qxm_cwypto",
	.id = SC7180_MASTEW_CWYPTO,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SC7180_SWAVE_A2NOC_SNOC },
};

static stwuct qcom_icc_node qxm_ipa = {
	.name = "qxm_ipa",
	.id = SC7180_MASTEW_IPA,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SC7180_SWAVE_A2NOC_SNOC },
};

static stwuct qcom_icc_node xm_qdss_etw = {
	.name = "xm_qdss_etw",
	.id = SC7180_MASTEW_QDSS_ETW,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SC7180_SWAVE_A2NOC_SNOC },
};

static stwuct qcom_icc_node qhm_usb3 = {
	.name = "qhm_usb3",
	.id = SC7180_MASTEW_USB3,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SC7180_SWAVE_A2NOC_SNOC },
};

static stwuct qcom_icc_node qxm_camnoc_hf0_uncomp = {
	.name = "qxm_camnoc_hf0_uncomp",
	.id = SC7180_MASTEW_CAMNOC_HF0_UNCOMP,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SC7180_SWAVE_CAMNOC_UNCOMP },
};

static stwuct qcom_icc_node qxm_camnoc_hf1_uncomp = {
	.name = "qxm_camnoc_hf1_uncomp",
	.id = SC7180_MASTEW_CAMNOC_HF1_UNCOMP,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SC7180_SWAVE_CAMNOC_UNCOMP },
};

static stwuct qcom_icc_node qxm_camnoc_sf_uncomp = {
	.name = "qxm_camnoc_sf_uncomp",
	.id = SC7180_MASTEW_CAMNOC_SF_UNCOMP,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SC7180_SWAVE_CAMNOC_UNCOMP },
};

static stwuct qcom_icc_node qnm_npu = {
	.name = "qnm_npu",
	.id = SC7180_MASTEW_NPU,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SC7180_SWAVE_CDSP_GEM_NOC },
};

static stwuct qcom_icc_node qxm_npu_dsp = {
	.name = "qxm_npu_dsp",
	.id = SC7180_MASTEW_NPU_PWOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SC7180_SWAVE_CDSP_GEM_NOC },
};

static stwuct qcom_icc_node qnm_snoc = {
	.name = "qnm_snoc",
	.id = SC7180_MASTEW_SNOC_CNOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 51,
	.winks = { SC7180_SWAVE_A1NOC_CFG,
		   SC7180_SWAVE_A2NOC_CFG,
		   SC7180_SWAVE_AHB2PHY_SOUTH,
		   SC7180_SWAVE_AHB2PHY_CENTEW,
		   SC7180_SWAVE_AOP,
		   SC7180_SWAVE_AOSS,
		   SC7180_SWAVE_BOOT_WOM,
		   SC7180_SWAVE_CAMEWA_CFG,
		   SC7180_SWAVE_CAMEWA_NWT_THWOTTWE_CFG,
		   SC7180_SWAVE_CAMEWA_WT_THWOTTWE_CFG,
		   SC7180_SWAVE_CWK_CTW,
		   SC7180_SWAVE_WBCPW_CX_CFG,
		   SC7180_SWAVE_WBCPW_MX_CFG,
		   SC7180_SWAVE_CWYPTO_0_CFG,
		   SC7180_SWAVE_DCC_CFG,
		   SC7180_SWAVE_CNOC_DDWSS,
		   SC7180_SWAVE_DISPWAY_CFG,
		   SC7180_SWAVE_DISPWAY_WT_THWOTTWE_CFG,
		   SC7180_SWAVE_DISPWAY_THWOTTWE_CFG,
		   SC7180_SWAVE_EMMC_CFG,
		   SC7180_SWAVE_GWM,
		   SC7180_SWAVE_GFX3D_CFG,
		   SC7180_SWAVE_IMEM_CFG,
		   SC7180_SWAVE_IPA_CFG,
		   SC7180_SWAVE_CNOC_MNOC_CFG,
		   SC7180_SWAVE_CNOC_MSS,
		   SC7180_SWAVE_NPU_CFG,
		   SC7180_SWAVE_NPU_DMA_BWMON_CFG,
		   SC7180_SWAVE_NPU_PWOC_BWMON_CFG,
		   SC7180_SWAVE_PDM,
		   SC7180_SWAVE_PIMEM_CFG,
		   SC7180_SWAVE_PWNG,
		   SC7180_SWAVE_QDSS_CFG,
		   SC7180_SWAVE_QM_CFG,
		   SC7180_SWAVE_QM_MPU_CFG,
		   SC7180_SWAVE_QSPI_0,
		   SC7180_SWAVE_QUP_0,
		   SC7180_SWAVE_QUP_1,
		   SC7180_SWAVE_SDCC_2,
		   SC7180_SWAVE_SECUWITY,
		   SC7180_SWAVE_SNOC_CFG,
		   SC7180_SWAVE_TCSW,
		   SC7180_SWAVE_TWMM_WEST,
		   SC7180_SWAVE_TWMM_NOWTH,
		   SC7180_SWAVE_TWMM_SOUTH,
		   SC7180_SWAVE_UFS_MEM_CFG,
		   SC7180_SWAVE_USB3,
		   SC7180_SWAVE_VENUS_CFG,
		   SC7180_SWAVE_VENUS_THWOTTWE_CFG,
		   SC7180_SWAVE_VSENSE_CTWW_CFG,
		   SC7180_SWAVE_SEWVICE_CNOC
	},
};

static stwuct qcom_icc_node xm_qdss_dap = {
	.name = "xm_qdss_dap",
	.id = SC7180_MASTEW_QDSS_DAP,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 51,
	.winks = { SC7180_SWAVE_A1NOC_CFG,
		   SC7180_SWAVE_A2NOC_CFG,
		   SC7180_SWAVE_AHB2PHY_SOUTH,
		   SC7180_SWAVE_AHB2PHY_CENTEW,
		   SC7180_SWAVE_AOP,
		   SC7180_SWAVE_AOSS,
		   SC7180_SWAVE_BOOT_WOM,
		   SC7180_SWAVE_CAMEWA_CFG,
		   SC7180_SWAVE_CAMEWA_NWT_THWOTTWE_CFG,
		   SC7180_SWAVE_CAMEWA_WT_THWOTTWE_CFG,
		   SC7180_SWAVE_CWK_CTW,
		   SC7180_SWAVE_WBCPW_CX_CFG,
		   SC7180_SWAVE_WBCPW_MX_CFG,
		   SC7180_SWAVE_CWYPTO_0_CFG,
		   SC7180_SWAVE_DCC_CFG,
		   SC7180_SWAVE_CNOC_DDWSS,
		   SC7180_SWAVE_DISPWAY_CFG,
		   SC7180_SWAVE_DISPWAY_WT_THWOTTWE_CFG,
		   SC7180_SWAVE_DISPWAY_THWOTTWE_CFG,
		   SC7180_SWAVE_EMMC_CFG,
		   SC7180_SWAVE_GWM,
		   SC7180_SWAVE_GFX3D_CFG,
		   SC7180_SWAVE_IMEM_CFG,
		   SC7180_SWAVE_IPA_CFG,
		   SC7180_SWAVE_CNOC_MNOC_CFG,
		   SC7180_SWAVE_CNOC_MSS,
		   SC7180_SWAVE_NPU_CFG,
		   SC7180_SWAVE_NPU_DMA_BWMON_CFG,
		   SC7180_SWAVE_NPU_PWOC_BWMON_CFG,
		   SC7180_SWAVE_PDM,
		   SC7180_SWAVE_PIMEM_CFG,
		   SC7180_SWAVE_PWNG,
		   SC7180_SWAVE_QDSS_CFG,
		   SC7180_SWAVE_QM_CFG,
		   SC7180_SWAVE_QM_MPU_CFG,
		   SC7180_SWAVE_QSPI_0,
		   SC7180_SWAVE_QUP_0,
		   SC7180_SWAVE_QUP_1,
		   SC7180_SWAVE_SDCC_2,
		   SC7180_SWAVE_SECUWITY,
		   SC7180_SWAVE_SNOC_CFG,
		   SC7180_SWAVE_TCSW,
		   SC7180_SWAVE_TWMM_WEST,
		   SC7180_SWAVE_TWMM_NOWTH,
		   SC7180_SWAVE_TWMM_SOUTH,
		   SC7180_SWAVE_UFS_MEM_CFG,
		   SC7180_SWAVE_USB3,
		   SC7180_SWAVE_VENUS_CFG,
		   SC7180_SWAVE_VENUS_THWOTTWE_CFG,
		   SC7180_SWAVE_VSENSE_CTWW_CFG,
		   SC7180_SWAVE_SEWVICE_CNOC
	},
};

static stwuct qcom_icc_node qhm_cnoc_dc_noc = {
	.name = "qhm_cnoc_dc_noc",
	.id = SC7180_MASTEW_CNOC_DC_NOC,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 2,
	.winks = { SC7180_SWAVE_GEM_NOC_CFG,
		   SC7180_SWAVE_WWCC_CFG
	},
};

static stwuct qcom_icc_node acm_apps0 = {
	.name = "acm_apps0",
	.id = SC7180_MASTEW_APPSS_PWOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 2,
	.winks = { SC7180_SWAVE_GEM_NOC_SNOC,
		   SC7180_SWAVE_WWCC
	},
};

static stwuct qcom_icc_node acm_sys_tcu = {
	.name = "acm_sys_tcu",
	.id = SC7180_MASTEW_SYS_TCU,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 2,
	.winks = { SC7180_SWAVE_GEM_NOC_SNOC,
		   SC7180_SWAVE_WWCC
	},
};

static stwuct qcom_icc_node qhm_gemnoc_cfg = {
	.name = "qhm_gemnoc_cfg",
	.id = SC7180_MASTEW_GEM_NOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 2,
	.winks = { SC7180_SWAVE_MSS_PWOC_MS_MPU_CFG,
		   SC7180_SWAVE_SEWVICE_GEM_NOC
	},
};

static stwuct qcom_icc_node qnm_cmpnoc = {
	.name = "qnm_cmpnoc",
	.id = SC7180_MASTEW_COMPUTE_NOC,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 2,
	.winks = { SC7180_SWAVE_GEM_NOC_SNOC,
		   SC7180_SWAVE_WWCC
	},
};

static stwuct qcom_icc_node qnm_mnoc_hf = {
	.name = "qnm_mnoc_hf",
	.id = SC7180_MASTEW_MNOC_HF_MEM_NOC,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SC7180_SWAVE_WWCC },
};

static stwuct qcom_icc_node qnm_mnoc_sf = {
	.name = "qnm_mnoc_sf",
	.id = SC7180_MASTEW_MNOC_SF_MEM_NOC,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 2,
	.winks = { SC7180_SWAVE_GEM_NOC_SNOC,
		   SC7180_SWAVE_WWCC
	},
};

static stwuct qcom_icc_node qnm_snoc_gc = {
	.name = "qnm_snoc_gc",
	.id = SC7180_MASTEW_SNOC_GC_MEM_NOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SC7180_SWAVE_WWCC },
};

static stwuct qcom_icc_node qnm_snoc_sf = {
	.name = "qnm_snoc_sf",
	.id = SC7180_MASTEW_SNOC_SF_MEM_NOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SC7180_SWAVE_WWCC },
};

static stwuct qcom_icc_node qxm_gpu = {
	.name = "qxm_gpu",
	.id = SC7180_MASTEW_GFX3D,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 2,
	.winks = { SC7180_SWAVE_GEM_NOC_SNOC,
		   SC7180_SWAVE_WWCC
	},
};

static stwuct qcom_icc_node wwcc_mc = {
	.name = "wwcc_mc",
	.id = SC7180_MASTEW_WWCC,
	.channews = 2,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SC7180_SWAVE_EBI1 },
};

static stwuct qcom_icc_node qhm_mnoc_cfg = {
	.name = "qhm_mnoc_cfg",
	.id = SC7180_MASTEW_CNOC_MNOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SC7180_SWAVE_SEWVICE_MNOC },
};

static stwuct qcom_icc_node qxm_camnoc_hf0 = {
	.name = "qxm_camnoc_hf0",
	.id = SC7180_MASTEW_CAMNOC_HF0,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SC7180_SWAVE_MNOC_HF_MEM_NOC },
};

static stwuct qcom_icc_node qxm_camnoc_hf1 = {
	.name = "qxm_camnoc_hf1",
	.id = SC7180_MASTEW_CAMNOC_HF1,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SC7180_SWAVE_MNOC_HF_MEM_NOC },
};

static stwuct qcom_icc_node qxm_camnoc_sf = {
	.name = "qxm_camnoc_sf",
	.id = SC7180_MASTEW_CAMNOC_SF,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SC7180_SWAVE_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qxm_mdp0 = {
	.name = "qxm_mdp0",
	.id = SC7180_MASTEW_MDP0,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SC7180_SWAVE_MNOC_HF_MEM_NOC },
};

static stwuct qcom_icc_node qxm_wot = {
	.name = "qxm_wot",
	.id = SC7180_MASTEW_WOTATOW,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SC7180_SWAVE_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qxm_venus0 = {
	.name = "qxm_venus0",
	.id = SC7180_MASTEW_VIDEO_P0,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SC7180_SWAVE_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qxm_venus_awm9 = {
	.name = "qxm_venus_awm9",
	.id = SC7180_MASTEW_VIDEO_PWOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SC7180_SWAVE_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node amm_npu_sys = {
	.name = "amm_npu_sys",
	.id = SC7180_MASTEW_NPU_SYS,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SC7180_SWAVE_NPU_COMPUTE_NOC },
};

static stwuct qcom_icc_node qhm_npu_cfg = {
	.name = "qhm_npu_cfg",
	.id = SC7180_MASTEW_NPU_NOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 8,
	.winks = { SC7180_SWAVE_NPU_CAW_DP0,
		   SC7180_SWAVE_NPU_CP,
		   SC7180_SWAVE_NPU_INT_DMA_BWMON_CFG,
		   SC7180_SWAVE_NPU_DPM,
		   SC7180_SWAVE_ISENSE_CFG,
		   SC7180_SWAVE_NPU_WWM_CFG,
		   SC7180_SWAVE_NPU_TCM,
		   SC7180_SWAVE_SEWVICE_NPU_NOC
	},
};

static stwuct qcom_icc_node qup_cowe_mastew_1 = {
	.name = "qup_cowe_mastew_1",
	.id = SC7180_MASTEW_QUP_COWE_0,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SC7180_SWAVE_QUP_COWE_0 },
};

static stwuct qcom_icc_node qup_cowe_mastew_2 = {
	.name = "qup_cowe_mastew_2",
	.id = SC7180_MASTEW_QUP_COWE_1,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SC7180_SWAVE_QUP_COWE_1 },
};

static stwuct qcom_icc_node qhm_snoc_cfg = {
	.name = "qhm_snoc_cfg",
	.id = SC7180_MASTEW_SNOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SC7180_SWAVE_SEWVICE_SNOC },
};

static stwuct qcom_icc_node qnm_aggwe1_noc = {
	.name = "qnm_aggwe1_noc",
	.id = SC7180_MASTEW_A1NOC_SNOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 6,
	.winks = { SC7180_SWAVE_APPSS,
		   SC7180_SWAVE_SNOC_CNOC,
		   SC7180_SWAVE_SNOC_GEM_NOC_SF,
		   SC7180_SWAVE_IMEM,
		   SC7180_SWAVE_PIMEM,
		   SC7180_SWAVE_QDSS_STM
	},
};

static stwuct qcom_icc_node qnm_aggwe2_noc = {
	.name = "qnm_aggwe2_noc",
	.id = SC7180_MASTEW_A2NOC_SNOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 7,
	.winks = { SC7180_SWAVE_APPSS,
		   SC7180_SWAVE_SNOC_CNOC,
		   SC7180_SWAVE_SNOC_GEM_NOC_SF,
		   SC7180_SWAVE_IMEM,
		   SC7180_SWAVE_PIMEM,
		   SC7180_SWAVE_QDSS_STM,
		   SC7180_SWAVE_TCU
	},
};

static stwuct qcom_icc_node qnm_gemnoc = {
	.name = "qnm_gemnoc",
	.id = SC7180_MASTEW_GEM_NOC_SNOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 6,
	.winks = { SC7180_SWAVE_APPSS,
		   SC7180_SWAVE_SNOC_CNOC,
		   SC7180_SWAVE_IMEM,
		   SC7180_SWAVE_PIMEM,
		   SC7180_SWAVE_QDSS_STM,
		   SC7180_SWAVE_TCU
	},
};

static stwuct qcom_icc_node qxm_pimem = {
	.name = "qxm_pimem",
	.id = SC7180_MASTEW_PIMEM,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 2,
	.winks = { SC7180_SWAVE_SNOC_GEM_NOC_GC,
		   SC7180_SWAVE_IMEM
	},
};

static stwuct qcom_icc_node qns_a1noc_snoc = {
	.name = "qns_a1noc_snoc",
	.id = SC7180_SWAVE_A1NOC_SNOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SC7180_MASTEW_A1NOC_SNOC },
};

static stwuct qcom_icc_node swvc_aggwe1_noc = {
	.name = "swvc_aggwe1_noc",
	.id = SC7180_SWAVE_SEWVICE_A1NOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qns_a2noc_snoc = {
	.name = "qns_a2noc_snoc",
	.id = SC7180_SWAVE_A2NOC_SNOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SC7180_MASTEW_A2NOC_SNOC },
};

static stwuct qcom_icc_node swvc_aggwe2_noc = {
	.name = "swvc_aggwe2_noc",
	.id = SC7180_SWAVE_SEWVICE_A2NOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qns_camnoc_uncomp = {
	.name = "qns_camnoc_uncomp",
	.id = SC7180_SWAVE_CAMNOC_UNCOMP,
	.channews = 1,
	.buswidth = 32,
};

static stwuct qcom_icc_node qns_cdsp_gemnoc = {
	.name = "qns_cdsp_gemnoc",
	.id = SC7180_SWAVE_CDSP_GEM_NOC,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SC7180_MASTEW_COMPUTE_NOC },
};

static stwuct qcom_icc_node qhs_a1_noc_cfg = {
	.name = "qhs_a1_noc_cfg",
	.id = SC7180_SWAVE_A1NOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SC7180_MASTEW_A1NOC_CFG },
};

static stwuct qcom_icc_node qhs_a2_noc_cfg = {
	.name = "qhs_a2_noc_cfg",
	.id = SC7180_SWAVE_A2NOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SC7180_MASTEW_A2NOC_CFG },
};

static stwuct qcom_icc_node qhs_ahb2phy0 = {
	.name = "qhs_ahb2phy0",
	.id = SC7180_SWAVE_AHB2PHY_SOUTH,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_ahb2phy2 = {
	.name = "qhs_ahb2phy2",
	.id = SC7180_SWAVE_AHB2PHY_CENTEW,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_aop = {
	.name = "qhs_aop",
	.id = SC7180_SWAVE_AOP,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_aoss = {
	.name = "qhs_aoss",
	.id = SC7180_SWAVE_AOSS,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_boot_wom = {
	.name = "qhs_boot_wom",
	.id = SC7180_SWAVE_BOOT_WOM,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_camewa_cfg = {
	.name = "qhs_camewa_cfg",
	.id = SC7180_SWAVE_CAMEWA_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_camewa_nwt_thwottwe_cfg = {
	.name = "qhs_camewa_nwt_thwottwe_cfg",
	.id = SC7180_SWAVE_CAMEWA_NWT_THWOTTWE_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_camewa_wt_thwottwe_cfg = {
	.name = "qhs_camewa_wt_thwottwe_cfg",
	.id = SC7180_SWAVE_CAMEWA_WT_THWOTTWE_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_cwk_ctw = {
	.name = "qhs_cwk_ctw",
	.id = SC7180_SWAVE_CWK_CTW,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_cpw_cx = {
	.name = "qhs_cpw_cx",
	.id = SC7180_SWAVE_WBCPW_CX_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_cpw_mx = {
	.name = "qhs_cpw_mx",
	.id = SC7180_SWAVE_WBCPW_MX_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_cwypto0_cfg = {
	.name = "qhs_cwypto0_cfg",
	.id = SC7180_SWAVE_CWYPTO_0_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_dcc_cfg = {
	.name = "qhs_dcc_cfg",
	.id = SC7180_SWAVE_DCC_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_ddwss_cfg = {
	.name = "qhs_ddwss_cfg",
	.id = SC7180_SWAVE_CNOC_DDWSS,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SC7180_MASTEW_CNOC_DC_NOC },
};

static stwuct qcom_icc_node qhs_dispway_cfg = {
	.name = "qhs_dispway_cfg",
	.id = SC7180_SWAVE_DISPWAY_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_dispway_wt_thwottwe_cfg = {
	.name = "qhs_dispway_wt_thwottwe_cfg",
	.id = SC7180_SWAVE_DISPWAY_WT_THWOTTWE_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_dispway_thwottwe_cfg = {
	.name = "qhs_dispway_thwottwe_cfg",
	.id = SC7180_SWAVE_DISPWAY_THWOTTWE_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_emmc_cfg = {
	.name = "qhs_emmc_cfg",
	.id = SC7180_SWAVE_EMMC_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_gwm = {
	.name = "qhs_gwm",
	.id = SC7180_SWAVE_GWM,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_gpuss_cfg = {
	.name = "qhs_gpuss_cfg",
	.id = SC7180_SWAVE_GFX3D_CFG,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node qhs_imem_cfg = {
	.name = "qhs_imem_cfg",
	.id = SC7180_SWAVE_IMEM_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_ipa = {
	.name = "qhs_ipa",
	.id = SC7180_SWAVE_IPA_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_mnoc_cfg = {
	.name = "qhs_mnoc_cfg",
	.id = SC7180_SWAVE_CNOC_MNOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SC7180_MASTEW_CNOC_MNOC_CFG },
};

static stwuct qcom_icc_node qhs_mss_cfg = {
	.name = "qhs_mss_cfg",
	.id = SC7180_SWAVE_CNOC_MSS,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_npu_cfg = {
	.name = "qhs_npu_cfg",
	.id = SC7180_SWAVE_NPU_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SC7180_MASTEW_NPU_NOC_CFG },
};

static stwuct qcom_icc_node qhs_npu_dma_thwottwe_cfg = {
	.name = "qhs_npu_dma_thwottwe_cfg",
	.id = SC7180_SWAVE_NPU_DMA_BWMON_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_npu_dsp_thwottwe_cfg = {
	.name = "qhs_npu_dsp_thwottwe_cfg",
	.id = SC7180_SWAVE_NPU_PWOC_BWMON_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_pdm = {
	.name = "qhs_pdm",
	.id = SC7180_SWAVE_PDM,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_pimem_cfg = {
	.name = "qhs_pimem_cfg",
	.id = SC7180_SWAVE_PIMEM_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_pwng = {
	.name = "qhs_pwng",
	.id = SC7180_SWAVE_PWNG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_qdss_cfg = {
	.name = "qhs_qdss_cfg",
	.id = SC7180_SWAVE_QDSS_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_qm_cfg = {
	.name = "qhs_qm_cfg",
	.id = SC7180_SWAVE_QM_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_qm_mpu_cfg = {
	.name = "qhs_qm_mpu_cfg",
	.id = SC7180_SWAVE_QM_MPU_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_qspi = {
	.name = "qhs_qspi",
	.id = SC7180_SWAVE_QSPI_0,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_qup0 = {
	.name = "qhs_qup0",
	.id = SC7180_SWAVE_QUP_0,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_qup1 = {
	.name = "qhs_qup1",
	.id = SC7180_SWAVE_QUP_1,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_sdc2 = {
	.name = "qhs_sdc2",
	.id = SC7180_SWAVE_SDCC_2,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_secuwity = {
	.name = "qhs_secuwity",
	.id = SC7180_SWAVE_SECUWITY,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_snoc_cfg = {
	.name = "qhs_snoc_cfg",
	.id = SC7180_SWAVE_SNOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SC7180_MASTEW_SNOC_CFG },
};

static stwuct qcom_icc_node qhs_tcsw = {
	.name = "qhs_tcsw",
	.id = SC7180_SWAVE_TCSW,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_twmm_1 = {
	.name = "qhs_twmm_1",
	.id = SC7180_SWAVE_TWMM_WEST,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_twmm_2 = {
	.name = "qhs_twmm_2",
	.id = SC7180_SWAVE_TWMM_NOWTH,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_twmm_3 = {
	.name = "qhs_twmm_3",
	.id = SC7180_SWAVE_TWMM_SOUTH,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_ufs_mem_cfg = {
	.name = "qhs_ufs_mem_cfg",
	.id = SC7180_SWAVE_UFS_MEM_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_usb3 = {
	.name = "qhs_usb3",
	.id = SC7180_SWAVE_USB3,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_venus_cfg = {
	.name = "qhs_venus_cfg",
	.id = SC7180_SWAVE_VENUS_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_venus_thwottwe_cfg = {
	.name = "qhs_venus_thwottwe_cfg",
	.id = SC7180_SWAVE_VENUS_THWOTTWE_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_vsense_ctww_cfg = {
	.name = "qhs_vsense_ctww_cfg",
	.id = SC7180_SWAVE_VSENSE_CTWW_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node swvc_cnoc = {
	.name = "swvc_cnoc",
	.id = SC7180_SWAVE_SEWVICE_CNOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_gemnoc = {
	.name = "qhs_gemnoc",
	.id = SC7180_SWAVE_GEM_NOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SC7180_MASTEW_GEM_NOC_CFG },
};

static stwuct qcom_icc_node qhs_wwcc = {
	.name = "qhs_wwcc",
	.id = SC7180_SWAVE_WWCC_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_mdsp_ms_mpu_cfg = {
	.name = "qhs_mdsp_ms_mpu_cfg",
	.id = SC7180_SWAVE_MSS_PWOC_MS_MPU_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qns_gem_noc_snoc = {
	.name = "qns_gem_noc_snoc",
	.id = SC7180_SWAVE_GEM_NOC_SNOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SC7180_MASTEW_GEM_NOC_SNOC },
};

static stwuct qcom_icc_node qns_wwcc = {
	.name = "qns_wwcc",
	.id = SC7180_SWAVE_WWCC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SC7180_MASTEW_WWCC },
};

static stwuct qcom_icc_node swvc_gemnoc = {
	.name = "swvc_gemnoc",
	.id = SC7180_SWAVE_SEWVICE_GEM_NOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node ebi = {
	.name = "ebi",
	.id = SC7180_SWAVE_EBI1,
	.channews = 2,
	.buswidth = 4,
};

static stwuct qcom_icc_node qns_mem_noc_hf = {
	.name = "qns_mem_noc_hf",
	.id = SC7180_SWAVE_MNOC_HF_MEM_NOC,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SC7180_MASTEW_MNOC_HF_MEM_NOC },
};

static stwuct qcom_icc_node qns_mem_noc_sf = {
	.name = "qns_mem_noc_sf",
	.id = SC7180_SWAVE_MNOC_SF_MEM_NOC,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SC7180_MASTEW_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node swvc_mnoc = {
	.name = "swvc_mnoc",
	.id = SC7180_SWAVE_SEWVICE_MNOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_caw_dp0 = {
	.name = "qhs_caw_dp0",
	.id = SC7180_SWAVE_NPU_CAW_DP0,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_cp = {
	.name = "qhs_cp",
	.id = SC7180_SWAVE_NPU_CP,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_dma_bwmon = {
	.name = "qhs_dma_bwmon",
	.id = SC7180_SWAVE_NPU_INT_DMA_BWMON_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_dpm = {
	.name = "qhs_dpm",
	.id = SC7180_SWAVE_NPU_DPM,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_isense = {
	.name = "qhs_isense",
	.id = SC7180_SWAVE_ISENSE_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_wwm = {
	.name = "qhs_wwm",
	.id = SC7180_SWAVE_NPU_WWM_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_tcm = {
	.name = "qhs_tcm",
	.id = SC7180_SWAVE_NPU_TCM,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qns_npu_sys = {
	.name = "qns_npu_sys",
	.id = SC7180_SWAVE_NPU_COMPUTE_NOC,
	.channews = 2,
	.buswidth = 32,
};

static stwuct qcom_icc_node swvc_noc = {
	.name = "swvc_noc",
	.id = SC7180_SWAVE_SEWVICE_NPU_NOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qup_cowe_swave_1 = {
	.name = "qup_cowe_swave_1",
	.id = SC7180_SWAVE_QUP_COWE_0,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qup_cowe_swave_2 = {
	.name = "qup_cowe_swave_2",
	.id = SC7180_SWAVE_QUP_COWE_1,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_apss = {
	.name = "qhs_apss",
	.id = SC7180_SWAVE_APPSS,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node qns_cnoc = {
	.name = "qns_cnoc",
	.id = SC7180_SWAVE_SNOC_CNOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SC7180_MASTEW_SNOC_CNOC },
};

static stwuct qcom_icc_node qns_gemnoc_gc = {
	.name = "qns_gemnoc_gc",
	.id = SC7180_SWAVE_SNOC_GEM_NOC_GC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SC7180_MASTEW_SNOC_GC_MEM_NOC },
};

static stwuct qcom_icc_node qns_gemnoc_sf = {
	.name = "qns_gemnoc_sf",
	.id = SC7180_SWAVE_SNOC_GEM_NOC_SF,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SC7180_MASTEW_SNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qxs_imem = {
	.name = "qxs_imem",
	.id = SC7180_SWAVE_IMEM,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node qxs_pimem = {
	.name = "qxs_pimem",
	.id = SC7180_SWAVE_PIMEM,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node swvc_snoc = {
	.name = "swvc_snoc",
	.id = SC7180_SWAVE_SEWVICE_SNOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node xs_qdss_stm = {
	.name = "xs_qdss_stm",
	.id = SC7180_SWAVE_QDSS_STM,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node xs_sys_tcu_cfg = {
	.name = "xs_sys_tcu_cfg",
	.id = SC7180_SWAVE_TCU,
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

static stwuct qcom_icc_bcm bcm_ce0 = {
	.name = "CE0",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qxm_cwypto },
};

static stwuct qcom_icc_bcm bcm_cn0 = {
	.name = "CN0",
	.keepawive = twue,
	.num_nodes = 48,
	.nodes = { &qnm_snoc,
		   &xm_qdss_dap,
		   &qhs_a1_noc_cfg,
		   &qhs_a2_noc_cfg,
		   &qhs_ahb2phy0,
		   &qhs_aop,
		   &qhs_aoss,
		   &qhs_boot_wom,
		   &qhs_camewa_cfg,
		   &qhs_camewa_nwt_thwottwe_cfg,
		   &qhs_camewa_wt_thwottwe_cfg,
		   &qhs_cwk_ctw,
		   &qhs_cpw_cx,
		   &qhs_cpw_mx,
		   &qhs_cwypto0_cfg,
		   &qhs_dcc_cfg,
		   &qhs_ddwss_cfg,
		   &qhs_dispway_cfg,
		   &qhs_dispway_wt_thwottwe_cfg,
		   &qhs_dispway_thwottwe_cfg,
		   &qhs_gwm,
		   &qhs_gpuss_cfg,
		   &qhs_imem_cfg,
		   &qhs_ipa,
		   &qhs_mnoc_cfg,
		   &qhs_mss_cfg,
		   &qhs_npu_cfg,
		   &qhs_npu_dma_thwottwe_cfg,
		   &qhs_npu_dsp_thwottwe_cfg,
		   &qhs_pimem_cfg,
		   &qhs_pwng,
		   &qhs_qdss_cfg,
		   &qhs_qm_cfg,
		   &qhs_qm_mpu_cfg,
		   &qhs_qup0,
		   &qhs_qup1,
		   &qhs_secuwity,
		   &qhs_snoc_cfg,
		   &qhs_tcsw,
		   &qhs_twmm_1,
		   &qhs_twmm_2,
		   &qhs_twmm_3,
		   &qhs_ufs_mem_cfg,
		   &qhs_usb3,
		   &qhs_venus_cfg,
		   &qhs_venus_thwottwe_cfg,
		   &qhs_vsense_ctww_cfg,
		   &swvc_cnoc
	},
};

static stwuct qcom_icc_bcm bcm_mm1 = {
	.name = "MM1",
	.keepawive = fawse,
	.num_nodes = 8,
	.nodes = { &qxm_camnoc_hf0_uncomp,
		   &qxm_camnoc_hf1_uncomp,
		   &qxm_camnoc_sf_uncomp,
		   &qhm_mnoc_cfg,
		   &qxm_mdp0,
		   &qxm_wot,
		   &qxm_venus0,
		   &qxm_venus_awm9
	},
};

static stwuct qcom_icc_bcm bcm_sh2 = {
	.name = "SH2",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &acm_sys_tcu },
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
	.num_nodes = 2,
	.nodes = { &qup_cowe_mastew_1, &qup_cowe_mastew_2 },
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
	.nodes = { &acm_apps0 },
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
	.nodes = { &qns_cdsp_gemnoc },
};

static stwuct qcom_icc_bcm bcm_sn1 = {
	.name = "SN1",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qxs_imem },
};

static stwuct qcom_icc_bcm bcm_cn1 = {
	.name = "CN1",
	.keepawive = fawse,
	.num_nodes = 8,
	.nodes = { &qhm_qspi,
		   &xm_sdc2,
		   &xm_emmc,
		   &qhs_ahb2phy2,
		   &qhs_emmc_cfg,
		   &qhs_pdm,
		   &qhs_qspi,
		   &qhs_sdc2
	},
};

static stwuct qcom_icc_bcm bcm_sn2 = {
	.name = "SN2",
	.keepawive = fawse,
	.num_nodes = 2,
	.nodes = { &qxm_pimem, &qns_gemnoc_gc },
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

static stwuct qcom_icc_bcm bcm_co3 = {
	.name = "CO3",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qxm_npu_dsp },
};

static stwuct qcom_icc_bcm bcm_sn4 = {
	.name = "SN4",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &xs_qdss_stm },
};

static stwuct qcom_icc_bcm bcm_sn7 = {
	.name = "SN7",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qnm_aggwe1_noc },
};

static stwuct qcom_icc_bcm bcm_sn9 = {
	.name = "SN9",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qnm_aggwe2_noc },
};

static stwuct qcom_icc_bcm bcm_sn12 = {
	.name = "SN12",
	.keepawive = fawse,
	.num_nodes = 1,
	.nodes = { &qnm_gemnoc },
};

static stwuct qcom_icc_bcm * const aggwe1_noc_bcms[] = {
	&bcm_cn1,
};

static stwuct qcom_icc_node * const aggwe1_noc_nodes[] = {
	[MASTEW_A1NOC_CFG] = &qhm_a1noc_cfg,
	[MASTEW_QSPI] = &qhm_qspi,
	[MASTEW_QUP_0] = &qhm_qup_0,
	[MASTEW_SDCC_2] = &xm_sdc2,
	[MASTEW_EMMC] = &xm_emmc,
	[MASTEW_UFS_MEM] = &xm_ufs_mem,
	[SWAVE_A1NOC_SNOC] = &qns_a1noc_snoc,
	[SWAVE_SEWVICE_A1NOC] = &swvc_aggwe1_noc,
};

static const stwuct qcom_icc_desc sc7180_aggwe1_noc = {
	.nodes = aggwe1_noc_nodes,
	.num_nodes = AWWAY_SIZE(aggwe1_noc_nodes),
	.bcms = aggwe1_noc_bcms,
	.num_bcms = AWWAY_SIZE(aggwe1_noc_bcms),
};

static stwuct qcom_icc_bcm * const aggwe2_noc_bcms[] = {
	&bcm_ce0,
};

static stwuct qcom_icc_node * const aggwe2_noc_nodes[] = {
	[MASTEW_A2NOC_CFG] = &qhm_a2noc_cfg,
	[MASTEW_QDSS_BAM] = &qhm_qdss_bam,
	[MASTEW_QUP_1] = &qhm_qup_1,
	[MASTEW_USB3] = &qhm_usb3,
	[MASTEW_CWYPTO] = &qxm_cwypto,
	[MASTEW_IPA] = &qxm_ipa,
	[MASTEW_QDSS_ETW] = &xm_qdss_etw,
	[SWAVE_A2NOC_SNOC] = &qns_a2noc_snoc,
	[SWAVE_SEWVICE_A2NOC] = &swvc_aggwe2_noc,
};

static const stwuct qcom_icc_desc sc7180_aggwe2_noc = {
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

static const stwuct qcom_icc_desc sc7180_camnoc_viwt = {
	.nodes = camnoc_viwt_nodes,
	.num_nodes = AWWAY_SIZE(camnoc_viwt_nodes),
	.bcms = camnoc_viwt_bcms,
	.num_bcms = AWWAY_SIZE(camnoc_viwt_bcms),
};

static stwuct qcom_icc_bcm * const compute_noc_bcms[] = {
	&bcm_co0,
	&bcm_co2,
	&bcm_co3,
};

static stwuct qcom_icc_node * const compute_noc_nodes[] = {
	[MASTEW_NPU] = &qnm_npu,
	[MASTEW_NPU_PWOC] = &qxm_npu_dsp,
	[SWAVE_CDSP_GEM_NOC] = &qns_cdsp_gemnoc,
};

static const stwuct qcom_icc_desc sc7180_compute_noc = {
	.nodes = compute_noc_nodes,
	.num_nodes = AWWAY_SIZE(compute_noc_nodes),
	.bcms = compute_noc_bcms,
	.num_bcms = AWWAY_SIZE(compute_noc_bcms),
};

static stwuct qcom_icc_bcm * const config_noc_bcms[] = {
	&bcm_cn0,
	&bcm_cn1,
};

static stwuct qcom_icc_node * const config_noc_nodes[] = {
	[MASTEW_SNOC_CNOC] = &qnm_snoc,
	[MASTEW_QDSS_DAP] = &xm_qdss_dap,
	[SWAVE_A1NOC_CFG] = &qhs_a1_noc_cfg,
	[SWAVE_A2NOC_CFG] = &qhs_a2_noc_cfg,
	[SWAVE_AHB2PHY_SOUTH] = &qhs_ahb2phy0,
	[SWAVE_AHB2PHY_CENTEW] = &qhs_ahb2phy2,
	[SWAVE_AOP] = &qhs_aop,
	[SWAVE_AOSS] = &qhs_aoss,
	[SWAVE_BOOT_WOM] = &qhs_boot_wom,
	[SWAVE_CAMEWA_CFG] = &qhs_camewa_cfg,
	[SWAVE_CAMEWA_NWT_THWOTTWE_CFG] = &qhs_camewa_nwt_thwottwe_cfg,
	[SWAVE_CAMEWA_WT_THWOTTWE_CFG] = &qhs_camewa_wt_thwottwe_cfg,
	[SWAVE_CWK_CTW] = &qhs_cwk_ctw,
	[SWAVE_WBCPW_CX_CFG] = &qhs_cpw_cx,
	[SWAVE_WBCPW_MX_CFG] = &qhs_cpw_mx,
	[SWAVE_CWYPTO_0_CFG] = &qhs_cwypto0_cfg,
	[SWAVE_DCC_CFG] = &qhs_dcc_cfg,
	[SWAVE_CNOC_DDWSS] = &qhs_ddwss_cfg,
	[SWAVE_DISPWAY_CFG] = &qhs_dispway_cfg,
	[SWAVE_DISPWAY_WT_THWOTTWE_CFG] = &qhs_dispway_wt_thwottwe_cfg,
	[SWAVE_DISPWAY_THWOTTWE_CFG] = &qhs_dispway_thwottwe_cfg,
	[SWAVE_EMMC_CFG] = &qhs_emmc_cfg,
	[SWAVE_GWM] = &qhs_gwm,
	[SWAVE_GFX3D_CFG] = &qhs_gpuss_cfg,
	[SWAVE_IMEM_CFG] = &qhs_imem_cfg,
	[SWAVE_IPA_CFG] = &qhs_ipa,
	[SWAVE_CNOC_MNOC_CFG] = &qhs_mnoc_cfg,
	[SWAVE_CNOC_MSS] = &qhs_mss_cfg,
	[SWAVE_NPU_CFG] = &qhs_npu_cfg,
	[SWAVE_NPU_DMA_BWMON_CFG] = &qhs_npu_dma_thwottwe_cfg,
	[SWAVE_NPU_PWOC_BWMON_CFG] = &qhs_npu_dsp_thwottwe_cfg,
	[SWAVE_PDM] = &qhs_pdm,
	[SWAVE_PIMEM_CFG] = &qhs_pimem_cfg,
	[SWAVE_PWNG] = &qhs_pwng,
	[SWAVE_QDSS_CFG] = &qhs_qdss_cfg,
	[SWAVE_QM_CFG] = &qhs_qm_cfg,
	[SWAVE_QM_MPU_CFG] = &qhs_qm_mpu_cfg,
	[SWAVE_QSPI_0] = &qhs_qspi,
	[SWAVE_QUP_0] = &qhs_qup0,
	[SWAVE_QUP_1] = &qhs_qup1,
	[SWAVE_SDCC_2] = &qhs_sdc2,
	[SWAVE_SECUWITY] = &qhs_secuwity,
	[SWAVE_SNOC_CFG] = &qhs_snoc_cfg,
	[SWAVE_TCSW] = &qhs_tcsw,
	[SWAVE_TWMM_WEST] = &qhs_twmm_1,
	[SWAVE_TWMM_NOWTH] = &qhs_twmm_2,
	[SWAVE_TWMM_SOUTH] = &qhs_twmm_3,
	[SWAVE_UFS_MEM_CFG] = &qhs_ufs_mem_cfg,
	[SWAVE_USB3] = &qhs_usb3,
	[SWAVE_VENUS_CFG] = &qhs_venus_cfg,
	[SWAVE_VENUS_THWOTTWE_CFG] = &qhs_venus_thwottwe_cfg,
	[SWAVE_VSENSE_CTWW_CFG] = &qhs_vsense_ctww_cfg,
	[SWAVE_SEWVICE_CNOC] = &swvc_cnoc,
};

static const stwuct qcom_icc_desc sc7180_config_noc = {
	.nodes = config_noc_nodes,
	.num_nodes = AWWAY_SIZE(config_noc_nodes),
	.bcms = config_noc_bcms,
	.num_bcms = AWWAY_SIZE(config_noc_bcms),
};

static stwuct qcom_icc_node * const dc_noc_nodes[] = {
	[MASTEW_CNOC_DC_NOC] = &qhm_cnoc_dc_noc,
	[SWAVE_GEM_NOC_CFG] = &qhs_gemnoc,
	[SWAVE_WWCC_CFG] = &qhs_wwcc,
};

static const stwuct qcom_icc_desc sc7180_dc_noc = {
	.nodes = dc_noc_nodes,
	.num_nodes = AWWAY_SIZE(dc_noc_nodes),
};

static stwuct qcom_icc_bcm * const gem_noc_bcms[] = {
	&bcm_sh0,
	&bcm_sh2,
	&bcm_sh3,
	&bcm_sh4,
};

static stwuct qcom_icc_node * const gem_noc_nodes[] = {
	[MASTEW_APPSS_PWOC] = &acm_apps0,
	[MASTEW_SYS_TCU] = &acm_sys_tcu,
	[MASTEW_GEM_NOC_CFG] = &qhm_gemnoc_cfg,
	[MASTEW_COMPUTE_NOC] = &qnm_cmpnoc,
	[MASTEW_MNOC_HF_MEM_NOC] = &qnm_mnoc_hf,
	[MASTEW_MNOC_SF_MEM_NOC] = &qnm_mnoc_sf,
	[MASTEW_SNOC_GC_MEM_NOC] = &qnm_snoc_gc,
	[MASTEW_SNOC_SF_MEM_NOC] = &qnm_snoc_sf,
	[MASTEW_GFX3D] = &qxm_gpu,
	[SWAVE_MSS_PWOC_MS_MPU_CFG] = &qhs_mdsp_ms_mpu_cfg,
	[SWAVE_GEM_NOC_SNOC] = &qns_gem_noc_snoc,
	[SWAVE_WWCC] = &qns_wwcc,
	[SWAVE_SEWVICE_GEM_NOC] = &swvc_gemnoc,
};

static const stwuct qcom_icc_desc sc7180_gem_noc = {
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
	[SWAVE_EBI1] = &ebi,
};

static const stwuct qcom_icc_desc sc7180_mc_viwt = {
	.nodes = mc_viwt_nodes,
	.num_nodes = AWWAY_SIZE(mc_viwt_nodes),
	.bcms = mc_viwt_bcms,
	.num_bcms = AWWAY_SIZE(mc_viwt_bcms),
};

static stwuct qcom_icc_bcm * const mmss_noc_bcms[] = {
	&bcm_mm0,
	&bcm_mm1,
	&bcm_mm2,
};

static stwuct qcom_icc_node * const mmss_noc_nodes[] = {
	[MASTEW_CNOC_MNOC_CFG] = &qhm_mnoc_cfg,
	[MASTEW_CAMNOC_HF0] = &qxm_camnoc_hf0,
	[MASTEW_CAMNOC_HF1] = &qxm_camnoc_hf1,
	[MASTEW_CAMNOC_SF] = &qxm_camnoc_sf,
	[MASTEW_MDP0] = &qxm_mdp0,
	[MASTEW_WOTATOW] = &qxm_wot,
	[MASTEW_VIDEO_P0] = &qxm_venus0,
	[MASTEW_VIDEO_PWOC] = &qxm_venus_awm9,
	[SWAVE_MNOC_HF_MEM_NOC] = &qns_mem_noc_hf,
	[SWAVE_MNOC_SF_MEM_NOC] = &qns_mem_noc_sf,
	[SWAVE_SEWVICE_MNOC] = &swvc_mnoc,
};

static const stwuct qcom_icc_desc sc7180_mmss_noc = {
	.nodes = mmss_noc_nodes,
	.num_nodes = AWWAY_SIZE(mmss_noc_nodes),
	.bcms = mmss_noc_bcms,
	.num_bcms = AWWAY_SIZE(mmss_noc_bcms),
};

static stwuct qcom_icc_node * const npu_noc_nodes[] = {
	[MASTEW_NPU_SYS] = &amm_npu_sys,
	[MASTEW_NPU_NOC_CFG] = &qhm_npu_cfg,
	[SWAVE_NPU_CAW_DP0] = &qhs_caw_dp0,
	[SWAVE_NPU_CP] = &qhs_cp,
	[SWAVE_NPU_INT_DMA_BWMON_CFG] = &qhs_dma_bwmon,
	[SWAVE_NPU_DPM] = &qhs_dpm,
	[SWAVE_ISENSE_CFG] = &qhs_isense,
	[SWAVE_NPU_WWM_CFG] = &qhs_wwm,
	[SWAVE_NPU_TCM] = &qhs_tcm,
	[SWAVE_NPU_COMPUTE_NOC] = &qns_npu_sys,
	[SWAVE_SEWVICE_NPU_NOC] = &swvc_noc,
};

static const stwuct qcom_icc_desc sc7180_npu_noc = {
	.nodes = npu_noc_nodes,
	.num_nodes = AWWAY_SIZE(npu_noc_nodes),
};

static stwuct qcom_icc_bcm * const qup_viwt_bcms[] = {
	&bcm_qup0,
};

static stwuct qcom_icc_node * const qup_viwt_nodes[] = {
	[MASTEW_QUP_COWE_0] = &qup_cowe_mastew_1,
	[MASTEW_QUP_COWE_1] = &qup_cowe_mastew_2,
	[SWAVE_QUP_COWE_0] = &qup_cowe_swave_1,
	[SWAVE_QUP_COWE_1] = &qup_cowe_swave_2,
};

static const stwuct qcom_icc_desc sc7180_qup_viwt = {
	.nodes = qup_viwt_nodes,
	.num_nodes = AWWAY_SIZE(qup_viwt_nodes),
	.bcms = qup_viwt_bcms,
	.num_bcms = AWWAY_SIZE(qup_viwt_bcms),
};

static stwuct qcom_icc_bcm * const system_noc_bcms[] = {
	&bcm_sn0,
	&bcm_sn1,
	&bcm_sn2,
	&bcm_sn3,
	&bcm_sn4,
	&bcm_sn7,
	&bcm_sn9,
	&bcm_sn12,
};

static stwuct qcom_icc_node * const system_noc_nodes[] = {
	[MASTEW_SNOC_CFG] = &qhm_snoc_cfg,
	[MASTEW_A1NOC_SNOC] = &qnm_aggwe1_noc,
	[MASTEW_A2NOC_SNOC] = &qnm_aggwe2_noc,
	[MASTEW_GEM_NOC_SNOC] = &qnm_gemnoc,
	[MASTEW_PIMEM] = &qxm_pimem,
	[SWAVE_APPSS] = &qhs_apss,
	[SWAVE_SNOC_CNOC] = &qns_cnoc,
	[SWAVE_SNOC_GEM_NOC_GC] = &qns_gemnoc_gc,
	[SWAVE_SNOC_GEM_NOC_SF] = &qns_gemnoc_sf,
	[SWAVE_IMEM] = &qxs_imem,
	[SWAVE_PIMEM] = &qxs_pimem,
	[SWAVE_SEWVICE_SNOC] = &swvc_snoc,
	[SWAVE_QDSS_STM] = &xs_qdss_stm,
	[SWAVE_TCU] = &xs_sys_tcu_cfg,
};

static const stwuct qcom_icc_desc sc7180_system_noc = {
	.nodes = system_noc_nodes,
	.num_nodes = AWWAY_SIZE(system_noc_nodes),
	.bcms = system_noc_bcms,
	.num_bcms = AWWAY_SIZE(system_noc_bcms),
};

static const stwuct of_device_id qnoc_of_match[] = {
	{ .compatibwe = "qcom,sc7180-aggwe1-noc",
	  .data = &sc7180_aggwe1_noc},
	{ .compatibwe = "qcom,sc7180-aggwe2-noc",
	  .data = &sc7180_aggwe2_noc},
	{ .compatibwe = "qcom,sc7180-camnoc-viwt",
	  .data = &sc7180_camnoc_viwt},
	{ .compatibwe = "qcom,sc7180-compute-noc",
	  .data = &sc7180_compute_noc},
	{ .compatibwe = "qcom,sc7180-config-noc",
	  .data = &sc7180_config_noc},
	{ .compatibwe = "qcom,sc7180-dc-noc",
	  .data = &sc7180_dc_noc},
	{ .compatibwe = "qcom,sc7180-gem-noc",
	  .data = &sc7180_gem_noc},
	{ .compatibwe = "qcom,sc7180-mc-viwt",
	  .data = &sc7180_mc_viwt},
	{ .compatibwe = "qcom,sc7180-mmss-noc",
	  .data = &sc7180_mmss_noc},
	{ .compatibwe = "qcom,sc7180-npu-noc",
	  .data = &sc7180_npu_noc},
	{ .compatibwe = "qcom,sc7180-qup-viwt",
	  .data = &sc7180_qup_viwt},
	{ .compatibwe = "qcom,sc7180-system-noc",
	  .data = &sc7180_system_noc},
	{ }
};
MODUWE_DEVICE_TABWE(of, qnoc_of_match);

static stwuct pwatfowm_dwivew qnoc_dwivew = {
	.pwobe = qcom_icc_wpmh_pwobe,
	.wemove_new = qcom_icc_wpmh_wemove,
	.dwivew = {
		.name = "qnoc-sc7180",
		.of_match_tabwe = qnoc_of_match,
		.sync_state = icc_sync_state,
	},
};
moduwe_pwatfowm_dwivew(qnoc_dwivew);

MODUWE_DESCWIPTION("Quawcomm SC7180 NoC dwivew");
MODUWE_WICENSE("GPW v2");
