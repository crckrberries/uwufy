// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2022, Winawo Wtd
 */

#incwude <winux/device.h>
#incwude <winux/intewconnect.h>
#incwude <winux/intewconnect-pwovidew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <dt-bindings/intewconnect/qcom,sc8280xp.h>

#incwude "bcm-votew.h"
#incwude "icc-wpmh.h"
#incwude "sc8280xp.h"

static stwuct qcom_icc_node qhm_qspi = {
	.name = "qhm_qspi",
	.id = SC8280XP_MASTEW_QSPI_0,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_A1NOC_SNOC },
};

static stwuct qcom_icc_node qhm_qup1 = {
	.name = "qhm_qup1",
	.id = SC8280XP_MASTEW_QUP_1,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_A1NOC_SNOC },
};

static stwuct qcom_icc_node qhm_qup2 = {
	.name = "qhm_qup2",
	.id = SC8280XP_MASTEW_QUP_2,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_A1NOC_SNOC },
};

static stwuct qcom_icc_node qnm_a1noc_cfg = {
	.name = "qnm_a1noc_cfg",
	.id = SC8280XP_MASTEW_A1NOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.winks = { SC8280XP_SWAVE_SEWVICE_A1NOC },
};

static stwuct qcom_icc_node qxm_ipa = {
	.name = "qxm_ipa",
	.id = SC8280XP_MASTEW_IPA,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_A1NOC_SNOC },
};

static stwuct qcom_icc_node xm_emac_1 = {
	.name = "xm_emac_1",
	.id = SC8280XP_MASTEW_EMAC_1,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_A1NOC_SNOC },
};

static stwuct qcom_icc_node xm_sdc4 = {
	.name = "xm_sdc4",
	.id = SC8280XP_MASTEW_SDCC_4,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_A1NOC_SNOC },
};

static stwuct qcom_icc_node xm_ufs_mem = {
	.name = "xm_ufs_mem",
	.id = SC8280XP_MASTEW_UFS_MEM,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_A1NOC_SNOC },
};

static stwuct qcom_icc_node xm_usb3_0 = {
	.name = "xm_usb3_0",
	.id = SC8280XP_MASTEW_USB3_0,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_USB_NOC_SNOC },
};

static stwuct qcom_icc_node xm_usb3_1 = {
	.name = "xm_usb3_1",
	.id = SC8280XP_MASTEW_USB3_1,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_USB_NOC_SNOC },
};

static stwuct qcom_icc_node xm_usb3_mp = {
	.name = "xm_usb3_mp",
	.id = SC8280XP_MASTEW_USB3_MP,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_USB_NOC_SNOC },
};

static stwuct qcom_icc_node xm_usb4_host0 = {
	.name = "xm_usb4_host0",
	.id = SC8280XP_MASTEW_USB4_0,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_USB_NOC_SNOC },
};

static stwuct qcom_icc_node xm_usb4_host1 = {
	.name = "xm_usb4_host1",
	.id = SC8280XP_MASTEW_USB4_1,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_USB_NOC_SNOC },
};

static stwuct qcom_icc_node qhm_qdss_bam = {
	.name = "qhm_qdss_bam",
	.id = SC8280XP_MASTEW_QDSS_BAM,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_A2NOC_SNOC },
};

static stwuct qcom_icc_node qhm_qup0 = {
	.name = "qhm_qup0",
	.id = SC8280XP_MASTEW_QUP_0,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_A2NOC_SNOC },
};

static stwuct qcom_icc_node qnm_a2noc_cfg = {
	.name = "qnm_a2noc_cfg",
	.id = SC8280XP_MASTEW_A2NOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_SEWVICE_A2NOC },
};

static stwuct qcom_icc_node qxm_cwypto = {
	.name = "qxm_cwypto",
	.id = SC8280XP_MASTEW_CWYPTO,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_A2NOC_SNOC },
};

static stwuct qcom_icc_node qxm_sensowss_q6 = {
	.name = "qxm_sensowss_q6",
	.id = SC8280XP_MASTEW_SENSOWS_PWOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_A2NOC_SNOC },
};

static stwuct qcom_icc_node qxm_sp = {
	.name = "qxm_sp",
	.id = SC8280XP_MASTEW_SP,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_A2NOC_SNOC },
};

static stwuct qcom_icc_node xm_emac_0 = {
	.name = "xm_emac_0",
	.id = SC8280XP_MASTEW_EMAC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_A2NOC_SNOC },
};

static stwuct qcom_icc_node xm_pcie3_0 = {
	.name = "xm_pcie3_0",
	.id = SC8280XP_MASTEW_PCIE_0,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_ANOC_PCIE_GEM_NOC },
};

static stwuct qcom_icc_node xm_pcie3_1 = {
	.name = "xm_pcie3_1",
	.id = SC8280XP_MASTEW_PCIE_1,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_ANOC_PCIE_GEM_NOC },
};

static stwuct qcom_icc_node xm_pcie3_2a = {
	.name = "xm_pcie3_2a",
	.id = SC8280XP_MASTEW_PCIE_2A,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_ANOC_PCIE_GEM_NOC },
};

static stwuct qcom_icc_node xm_pcie3_2b = {
	.name = "xm_pcie3_2b",
	.id = SC8280XP_MASTEW_PCIE_2B,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_ANOC_PCIE_GEM_NOC },
};

static stwuct qcom_icc_node xm_pcie3_3a = {
	.name = "xm_pcie3_3a",
	.id = SC8280XP_MASTEW_PCIE_3A,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_ANOC_PCIE_GEM_NOC },
};

static stwuct qcom_icc_node xm_pcie3_3b = {
	.name = "xm_pcie3_3b",
	.id = SC8280XP_MASTEW_PCIE_3B,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_ANOC_PCIE_GEM_NOC },
};

static stwuct qcom_icc_node xm_pcie3_4 = {
	.name = "xm_pcie3_4",
	.id = SC8280XP_MASTEW_PCIE_4,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_ANOC_PCIE_GEM_NOC },
};

static stwuct qcom_icc_node xm_qdss_etw = {
	.name = "xm_qdss_etw",
	.id = SC8280XP_MASTEW_QDSS_ETW,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_A2NOC_SNOC },
};

static stwuct qcom_icc_node xm_sdc2 = {
	.name = "xm_sdc2",
	.id = SC8280XP_MASTEW_SDCC_2,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_A2NOC_SNOC },
};

static stwuct qcom_icc_node xm_ufs_cawd = {
	.name = "xm_ufs_cawd",
	.id = SC8280XP_MASTEW_UFS_CAWD,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_A2NOC_SNOC },
};

static stwuct qcom_icc_node qup0_cowe_mastew = {
	.name = "qup0_cowe_mastew",
	.id = SC8280XP_MASTEW_QUP_COWE_0,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_QUP_COWE_0 },
};

static stwuct qcom_icc_node qup1_cowe_mastew = {
	.name = "qup1_cowe_mastew",
	.id = SC8280XP_MASTEW_QUP_COWE_1,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_QUP_COWE_1 },
};

static stwuct qcom_icc_node qup2_cowe_mastew = {
	.name = "qup2_cowe_mastew",
	.id = SC8280XP_MASTEW_QUP_COWE_2,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_QUP_COWE_2 },
};

static stwuct qcom_icc_node qnm_gemnoc_cnoc = {
	.name = "qnm_gemnoc_cnoc",
	.id = SC8280XP_MASTEW_GEM_NOC_CNOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 76,
	.winks = { SC8280XP_SWAVE_AHB2PHY_0,
		   SC8280XP_SWAVE_AHB2PHY_1,
		   SC8280XP_SWAVE_AHB2PHY_2,
		   SC8280XP_SWAVE_AOSS,
		   SC8280XP_SWAVE_APPSS,
		   SC8280XP_SWAVE_CAMEWA_CFG,
		   SC8280XP_SWAVE_CWK_CTW,
		   SC8280XP_SWAVE_CDSP_CFG,
		   SC8280XP_SWAVE_CDSP1_CFG,
		   SC8280XP_SWAVE_WBCPW_CX_CFG,
		   SC8280XP_SWAVE_WBCPW_MMCX_CFG,
		   SC8280XP_SWAVE_WBCPW_MX_CFG,
		   SC8280XP_SWAVE_CPW_NSPCX,
		   SC8280XP_SWAVE_CWYPTO_0_CFG,
		   SC8280XP_SWAVE_CX_WDPM,
		   SC8280XP_SWAVE_DCC_CFG,
		   SC8280XP_SWAVE_DISPWAY_CFG,
		   SC8280XP_SWAVE_DISPWAY1_CFG,
		   SC8280XP_SWAVE_EMAC_CFG,
		   SC8280XP_SWAVE_EMAC1_CFG,
		   SC8280XP_SWAVE_GFX3D_CFG,
		   SC8280XP_SWAVE_HWKM,
		   SC8280XP_SWAVE_IMEM_CFG,
		   SC8280XP_SWAVE_IPA_CFG,
		   SC8280XP_SWAVE_IPC_WOUTEW_CFG,
		   SC8280XP_SWAVE_WPASS,
		   SC8280XP_SWAVE_MX_WDPM,
		   SC8280XP_SWAVE_MXC_WDPM,
		   SC8280XP_SWAVE_PCIE_0_CFG,
		   SC8280XP_SWAVE_PCIE_1_CFG,
		   SC8280XP_SWAVE_PCIE_2A_CFG,
		   SC8280XP_SWAVE_PCIE_2B_CFG,
		   SC8280XP_SWAVE_PCIE_3A_CFG,
		   SC8280XP_SWAVE_PCIE_3B_CFG,
		   SC8280XP_SWAVE_PCIE_4_CFG,
		   SC8280XP_SWAVE_PCIE_WSC_CFG,
		   SC8280XP_SWAVE_PDM,
		   SC8280XP_SWAVE_PIMEM_CFG,
		   SC8280XP_SWAVE_PKA_WWAPPEW_CFG,
		   SC8280XP_SWAVE_PMU_WWAPPEW_CFG,
		   SC8280XP_SWAVE_QDSS_CFG,
		   SC8280XP_SWAVE_QSPI_0,
		   SC8280XP_SWAVE_QUP_0,
		   SC8280XP_SWAVE_QUP_1,
		   SC8280XP_SWAVE_QUP_2,
		   SC8280XP_SWAVE_SDCC_2,
		   SC8280XP_SWAVE_SDCC_4,
		   SC8280XP_SWAVE_SECUWITY,
		   SC8280XP_SWAVE_SMMUV3_CFG,
		   SC8280XP_SWAVE_SMSS_CFG,
		   SC8280XP_SWAVE_SPSS_CFG,
		   SC8280XP_SWAVE_TCSW,
		   SC8280XP_SWAVE_TWMM,
		   SC8280XP_SWAVE_UFS_CAWD_CFG,
		   SC8280XP_SWAVE_UFS_MEM_CFG,
		   SC8280XP_SWAVE_USB3_0,
		   SC8280XP_SWAVE_USB3_1,
		   SC8280XP_SWAVE_USB3_MP,
		   SC8280XP_SWAVE_USB4_0,
		   SC8280XP_SWAVE_USB4_1,
		   SC8280XP_SWAVE_VENUS_CFG,
		   SC8280XP_SWAVE_VSENSE_CTWW_CFG,
		   SC8280XP_SWAVE_VSENSE_CTWW_W_CFG,
		   SC8280XP_SWAVE_A1NOC_CFG,
		   SC8280XP_SWAVE_A2NOC_CFG,
		   SC8280XP_SWAVE_ANOC_PCIE_BWIDGE_CFG,
		   SC8280XP_SWAVE_DDWSS_CFG,
		   SC8280XP_SWAVE_CNOC_MNOC_CFG,
		   SC8280XP_SWAVE_SNOC_CFG,
		   SC8280XP_SWAVE_SNOC_SF_BWIDGE_CFG,
		   SC8280XP_SWAVE_IMEM,
		   SC8280XP_SWAVE_PIMEM,
		   SC8280XP_SWAVE_SEWVICE_CNOC,
		   SC8280XP_SWAVE_QDSS_STM,
		   SC8280XP_SWAVE_SMSS,
		   SC8280XP_SWAVE_TCU
	},
};

static stwuct qcom_icc_node qnm_gemnoc_pcie = {
	.name = "qnm_gemnoc_pcie",
	.id = SC8280XP_MASTEW_GEM_NOC_PCIE_SNOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 7,
	.winks = { SC8280XP_SWAVE_PCIE_0,
		   SC8280XP_SWAVE_PCIE_1,
		   SC8280XP_SWAVE_PCIE_2A,
		   SC8280XP_SWAVE_PCIE_2B,
		   SC8280XP_SWAVE_PCIE_3A,
		   SC8280XP_SWAVE_PCIE_3B,
		   SC8280XP_SWAVE_PCIE_4
	},
};

static stwuct qcom_icc_node qnm_cnoc_dc_noc = {
	.name = "qnm_cnoc_dc_noc",
	.id = SC8280XP_MASTEW_CNOC_DC_NOC,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 2,
	.winks = { SC8280XP_SWAVE_WWCC_CFG,
		   SC8280XP_SWAVE_GEM_NOC_CFG
	},
};

static stwuct qcom_icc_node awm_gpu_tcu = {
	.name = "awm_gpu_tcu",
	.id = SC8280XP_MASTEW_GPU_TCU,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 2,
	.winks = { SC8280XP_SWAVE_GEM_NOC_CNOC,
		   SC8280XP_SWAVE_WWCC
	},
};

static stwuct qcom_icc_node awm_pcie_tcu = {
	.name = "awm_pcie_tcu",
	.id = SC8280XP_MASTEW_PCIE_TCU,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 2,
	.winks = { SC8280XP_SWAVE_GEM_NOC_CNOC,
		   SC8280XP_SWAVE_WWCC
	},
};

static stwuct qcom_icc_node awm_sys_tcu = {
	.name = "awm_sys_tcu",
	.id = SC8280XP_MASTEW_SYS_TCU,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 2,
	.winks = { SC8280XP_SWAVE_GEM_NOC_CNOC,
		   SC8280XP_SWAVE_WWCC
	},
};

static stwuct qcom_icc_node chm_apps = {
	.name = "chm_apps",
	.id = SC8280XP_MASTEW_APPSS_PWOC,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 3,
	.winks = { SC8280XP_SWAVE_GEM_NOC_CNOC,
		   SC8280XP_SWAVE_WWCC,
		   SC8280XP_SWAVE_GEM_NOC_PCIE_CNOC
	},
};

static stwuct qcom_icc_node qnm_cmpnoc0 = {
	.name = "qnm_cmpnoc0",
	.id = SC8280XP_MASTEW_COMPUTE_NOC,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 2,
	.winks = { SC8280XP_SWAVE_GEM_NOC_CNOC,
		   SC8280XP_SWAVE_WWCC
	},
};

static stwuct qcom_icc_node qnm_cmpnoc1 = {
	.name = "qnm_cmpnoc1",
	.id = SC8280XP_MASTEW_COMPUTE_NOC_1,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 2,
	.winks = { SC8280XP_SWAVE_GEM_NOC_CNOC,
		   SC8280XP_SWAVE_WWCC
	},
};

static stwuct qcom_icc_node qnm_gemnoc_cfg = {
	.name = "qnm_gemnoc_cfg",
	.id = SC8280XP_MASTEW_GEM_NOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 3,
	.winks = { SC8280XP_SWAVE_SEWVICE_GEM_NOC_1,
		   SC8280XP_SWAVE_SEWVICE_GEM_NOC_2,
		   SC8280XP_SWAVE_SEWVICE_GEM_NOC
	},
};

static stwuct qcom_icc_node qnm_gpu = {
	.name = "qnm_gpu",
	.id = SC8280XP_MASTEW_GFX3D,
	.channews = 4,
	.buswidth = 32,
	.num_winks = 2,
	.winks = { SC8280XP_SWAVE_GEM_NOC_CNOC,
		   SC8280XP_SWAVE_WWCC
	},
};

static stwuct qcom_icc_node qnm_mnoc_hf = {
	.name = "qnm_mnoc_hf",
	.id = SC8280XP_MASTEW_MNOC_HF_MEM_NOC,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 2,
	.winks = { SC8280XP_SWAVE_WWCC,
		   SC8280XP_SWAVE_GEM_NOC_PCIE_CNOC
	},
};

static stwuct qcom_icc_node qnm_mnoc_sf = {
	.name = "qnm_mnoc_sf",
	.id = SC8280XP_MASTEW_MNOC_SF_MEM_NOC,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 2,
	.winks = { SC8280XP_SWAVE_GEM_NOC_CNOC,
		   SC8280XP_SWAVE_WWCC
	},
};

static stwuct qcom_icc_node qnm_pcie = {
	.name = "qnm_pcie",
	.id = SC8280XP_MASTEW_ANOC_PCIE_GEM_NOC,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 2,
	.winks = { SC8280XP_SWAVE_GEM_NOC_CNOC,
		   SC8280XP_SWAVE_WWCC
	},
};

static stwuct qcom_icc_node qnm_snoc_gc = {
	.name = "qnm_snoc_gc",
	.id = SC8280XP_MASTEW_SNOC_GC_MEM_NOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_WWCC },
};

static stwuct qcom_icc_node qnm_snoc_sf = {
	.name = "qnm_snoc_sf",
	.id = SC8280XP_MASTEW_SNOC_SF_MEM_NOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 3,
	.winks = { SC8280XP_SWAVE_GEM_NOC_CNOC,
		   SC8280XP_SWAVE_WWCC,
		   SC8280XP_SWAVE_GEM_NOC_PCIE_CNOC },
};

static stwuct qcom_icc_node qhm_config_noc = {
	.name = "qhm_config_noc",
	.id = SC8280XP_MASTEW_CNOC_WPASS_AG_NOC,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 6,
	.winks = { SC8280XP_SWAVE_WPASS_COWE_CFG,
		   SC8280XP_SWAVE_WPASS_WPI_CFG,
		   SC8280XP_SWAVE_WPASS_MPU_CFG,
		   SC8280XP_SWAVE_WPASS_TOP_CFG,
		   SC8280XP_SWAVE_SEWVICES_WPASS_AMW_NOC,
		   SC8280XP_SWAVE_SEWVICE_WPASS_AG_NOC
	},
};

static stwuct qcom_icc_node qxm_wpass_dsp = {
	.name = "qxm_wpass_dsp",
	.id = SC8280XP_MASTEW_WPASS_PWOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 4,
	.winks = { SC8280XP_SWAVE_WPASS_TOP_CFG,
		   SC8280XP_SWAVE_WPASS_SNOC,
		   SC8280XP_SWAVE_SEWVICES_WPASS_AMW_NOC,
		   SC8280XP_SWAVE_SEWVICE_WPASS_AG_NOC
	},
};

static stwuct qcom_icc_node wwcc_mc = {
	.name = "wwcc_mc",
	.id = SC8280XP_MASTEW_WWCC,
	.channews = 8,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_EBI1 },
};

static stwuct qcom_icc_node qnm_camnoc_hf = {
	.name = "qnm_camnoc_hf",
	.id = SC8280XP_MASTEW_CAMNOC_HF,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_MNOC_HF_MEM_NOC },
};

static stwuct qcom_icc_node qnm_mdp0_0 = {
	.name = "qnm_mdp0_0",
	.id = SC8280XP_MASTEW_MDP0,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_MNOC_HF_MEM_NOC },
};

static stwuct qcom_icc_node qnm_mdp0_1 = {
	.name = "qnm_mdp0_1",
	.id = SC8280XP_MASTEW_MDP1,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_MNOC_HF_MEM_NOC },
};

static stwuct qcom_icc_node qnm_mdp1_0 = {
	.name = "qnm_mdp1_0",
	.id = SC8280XP_MASTEW_MDP_COWE1_0,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_MNOC_HF_MEM_NOC },
};

static stwuct qcom_icc_node qnm_mdp1_1 = {
	.name = "qnm_mdp1_1",
	.id = SC8280XP_MASTEW_MDP_COWE1_1,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_MNOC_HF_MEM_NOC },
};

static stwuct qcom_icc_node qnm_mnoc_cfg = {
	.name = "qnm_mnoc_cfg",
	.id = SC8280XP_MASTEW_CNOC_MNOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_SEWVICE_MNOC },
};

static stwuct qcom_icc_node qnm_wot_0 = {
	.name = "qnm_wot_0",
	.id = SC8280XP_MASTEW_WOTATOW,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qnm_wot_1 = {
	.name = "qnm_wot_1",
	.id = SC8280XP_MASTEW_WOTATOW_1,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qnm_video0 = {
	.name = "qnm_video0",
	.id = SC8280XP_MASTEW_VIDEO_P0,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qnm_video1 = {
	.name = "qnm_video1",
	.id = SC8280XP_MASTEW_VIDEO_P1,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qnm_video_cvp = {
	.name = "qnm_video_cvp",
	.id = SC8280XP_MASTEW_VIDEO_PWOC,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qxm_camnoc_icp = {
	.name = "qxm_camnoc_icp",
	.id = SC8280XP_MASTEW_CAMNOC_ICP,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qxm_camnoc_sf = {
	.name = "qxm_camnoc_sf",
	.id = SC8280XP_MASTEW_CAMNOC_SF,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qhm_nsp_noc_config = {
	.name = "qhm_nsp_noc_config",
	.id = SC8280XP_MASTEW_CDSP_NOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_SEWVICE_NSP_NOC },
};

static stwuct qcom_icc_node qxm_nsp = {
	.name = "qxm_nsp",
	.id = SC8280XP_MASTEW_CDSP_PWOC,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 2,
	.winks = { SC8280XP_SWAVE_CDSP_MEM_NOC,
		   SC8280XP_SWAVE_NSP_XFW
	},
};

static stwuct qcom_icc_node qhm_nspb_noc_config = {
	.name = "qhm_nspb_noc_config",
	.id = SC8280XP_MASTEW_CDSPB_NOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_SEWVICE_NSPB_NOC },
};

static stwuct qcom_icc_node qxm_nspb = {
	.name = "qxm_nspb",
	.id = SC8280XP_MASTEW_CDSP_PWOC_B,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 2,
	.winks = { SC8280XP_SWAVE_CDSPB_MEM_NOC,
		   SC8280XP_SWAVE_NSPB_XFW
	},
};

static stwuct qcom_icc_node qnm_aggwe1_noc = {
	.name = "qnm_aggwe1_noc",
	.id = SC8280XP_MASTEW_A1NOC_SNOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_SNOC_GEM_NOC_SF },
};

static stwuct qcom_icc_node qnm_aggwe2_noc = {
	.name = "qnm_aggwe2_noc",
	.id = SC8280XP_MASTEW_A2NOC_SNOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_SNOC_GEM_NOC_SF },
};

static stwuct qcom_icc_node qnm_aggwe_usb_noc = {
	.name = "qnm_aggwe_usb_noc",
	.id = SC8280XP_MASTEW_USB_NOC_SNOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_SNOC_GEM_NOC_SF },
};

static stwuct qcom_icc_node qnm_wpass_noc = {
	.name = "qnm_wpass_noc",
	.id = SC8280XP_MASTEW_WPASS_ANOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_SNOC_GEM_NOC_SF },
};

static stwuct qcom_icc_node qnm_snoc_cfg = {
	.name = "qnm_snoc_cfg",
	.id = SC8280XP_MASTEW_SNOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_SEWVICE_SNOC },
};

static stwuct qcom_icc_node qxm_pimem = {
	.name = "qxm_pimem",
	.id = SC8280XP_MASTEW_PIMEM,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_SNOC_GEM_NOC_GC },
};

static stwuct qcom_icc_node xm_gic = {
	.name = "xm_gic",
	.id = SC8280XP_MASTEW_GIC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SC8280XP_SWAVE_SNOC_GEM_NOC_GC },
};

static stwuct qcom_icc_node qns_a1noc_snoc = {
	.name = "qns_a1noc_snoc",
	.id = SC8280XP_SWAVE_A1NOC_SNOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SC8280XP_MASTEW_A1NOC_SNOC },
};

static stwuct qcom_icc_node qns_aggwe_usb_snoc = {
	.name = "qns_aggwe_usb_snoc",
	.id = SC8280XP_SWAVE_USB_NOC_SNOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SC8280XP_MASTEW_USB_NOC_SNOC },
};

static stwuct qcom_icc_node swvc_aggwe1_noc = {
	.name = "swvc_aggwe1_noc",
	.id = SC8280XP_SWAVE_SEWVICE_A1NOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qns_a2noc_snoc = {
	.name = "qns_a2noc_snoc",
	.id = SC8280XP_SWAVE_A2NOC_SNOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SC8280XP_MASTEW_A2NOC_SNOC },
};

static stwuct qcom_icc_node qns_pcie_gem_noc = {
	.name = "qns_pcie_gem_noc",
	.id = SC8280XP_SWAVE_ANOC_PCIE_GEM_NOC,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SC8280XP_MASTEW_ANOC_PCIE_GEM_NOC },
};

static stwuct qcom_icc_node swvc_aggwe2_noc = {
	.name = "swvc_aggwe2_noc",
	.id = SC8280XP_SWAVE_SEWVICE_A2NOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qup0_cowe_swave = {
	.name = "qup0_cowe_swave",
	.id = SC8280XP_SWAVE_QUP_COWE_0,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qup1_cowe_swave = {
	.name = "qup1_cowe_swave",
	.id = SC8280XP_SWAVE_QUP_COWE_1,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qup2_cowe_swave = {
	.name = "qup2_cowe_swave",
	.id = SC8280XP_SWAVE_QUP_COWE_2,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_ahb2phy0 = {
	.name = "qhs_ahb2phy0",
	.id = SC8280XP_SWAVE_AHB2PHY_0,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_ahb2phy1 = {
	.name = "qhs_ahb2phy1",
	.id = SC8280XP_SWAVE_AHB2PHY_1,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_ahb2phy2 = {
	.name = "qhs_ahb2phy2",
	.id = SC8280XP_SWAVE_AHB2PHY_2,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_aoss = {
	.name = "qhs_aoss",
	.id = SC8280XP_SWAVE_AOSS,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_apss = {
	.name = "qhs_apss",
	.id = SC8280XP_SWAVE_APPSS,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node qhs_camewa_cfg = {
	.name = "qhs_camewa_cfg",
	.id = SC8280XP_SWAVE_CAMEWA_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_cwk_ctw = {
	.name = "qhs_cwk_ctw",
	.id = SC8280XP_SWAVE_CWK_CTW,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_compute0_cfg = {
	.name = "qhs_compute0_cfg",
	.id = SC8280XP_SWAVE_CDSP_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SC8280XP_MASTEW_CDSP_NOC_CFG },
};

static stwuct qcom_icc_node qhs_compute1_cfg = {
	.name = "qhs_compute1_cfg",
	.id = SC8280XP_SWAVE_CDSP1_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SC8280XP_MASTEW_CDSPB_NOC_CFG },
};

static stwuct qcom_icc_node qhs_cpw_cx = {
	.name = "qhs_cpw_cx",
	.id = SC8280XP_SWAVE_WBCPW_CX_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_cpw_mmcx = {
	.name = "qhs_cpw_mmcx",
	.id = SC8280XP_SWAVE_WBCPW_MMCX_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_cpw_mx = {
	.name = "qhs_cpw_mx",
	.id = SC8280XP_SWAVE_WBCPW_MX_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_cpw_nspcx = {
	.name = "qhs_cpw_nspcx",
	.id = SC8280XP_SWAVE_CPW_NSPCX,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_cwypto0_cfg = {
	.name = "qhs_cwypto0_cfg",
	.id = SC8280XP_SWAVE_CWYPTO_0_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_cx_wdpm = {
	.name = "qhs_cx_wdpm",
	.id = SC8280XP_SWAVE_CX_WDPM,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_dcc_cfg = {
	.name = "qhs_dcc_cfg",
	.id = SC8280XP_SWAVE_DCC_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_dispway0_cfg = {
	.name = "qhs_dispway0_cfg",
	.id = SC8280XP_SWAVE_DISPWAY_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_dispway1_cfg = {
	.name = "qhs_dispway1_cfg",
	.id = SC8280XP_SWAVE_DISPWAY1_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_emac0_cfg = {
	.name = "qhs_emac0_cfg",
	.id = SC8280XP_SWAVE_EMAC_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_emac1_cfg = {
	.name = "qhs_emac1_cfg",
	.id = SC8280XP_SWAVE_EMAC1_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_gpuss_cfg = {
	.name = "qhs_gpuss_cfg",
	.id = SC8280XP_SWAVE_GFX3D_CFG,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node qhs_hwkm = {
	.name = "qhs_hwkm",
	.id = SC8280XP_SWAVE_HWKM,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_imem_cfg = {
	.name = "qhs_imem_cfg",
	.id = SC8280XP_SWAVE_IMEM_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_ipa = {
	.name = "qhs_ipa",
	.id = SC8280XP_SWAVE_IPA_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_ipc_woutew = {
	.name = "qhs_ipc_woutew",
	.id = SC8280XP_SWAVE_IPC_WOUTEW_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_wpass_cfg = {
	.name = "qhs_wpass_cfg",
	.id = SC8280XP_SWAVE_WPASS,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SC8280XP_MASTEW_CNOC_WPASS_AG_NOC },
};

static stwuct qcom_icc_node qhs_mx_wdpm = {
	.name = "qhs_mx_wdpm",
	.id = SC8280XP_SWAVE_MX_WDPM,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_mxc_wdpm = {
	.name = "qhs_mxc_wdpm",
	.id = SC8280XP_SWAVE_MXC_WDPM,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_pcie0_cfg = {
	.name = "qhs_pcie0_cfg",
	.id = SC8280XP_SWAVE_PCIE_0_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_pcie1_cfg = {
	.name = "qhs_pcie1_cfg",
	.id = SC8280XP_SWAVE_PCIE_1_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_pcie2a_cfg = {
	.name = "qhs_pcie2a_cfg",
	.id = SC8280XP_SWAVE_PCIE_2A_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_pcie2b_cfg = {
	.name = "qhs_pcie2b_cfg",
	.id = SC8280XP_SWAVE_PCIE_2B_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_pcie3a_cfg = {
	.name = "qhs_pcie3a_cfg",
	.id = SC8280XP_SWAVE_PCIE_3A_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_pcie3b_cfg = {
	.name = "qhs_pcie3b_cfg",
	.id = SC8280XP_SWAVE_PCIE_3B_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_pcie4_cfg = {
	.name = "qhs_pcie4_cfg",
	.id = SC8280XP_SWAVE_PCIE_4_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_pcie_wsc_cfg = {
	.name = "qhs_pcie_wsc_cfg",
	.id = SC8280XP_SWAVE_PCIE_WSC_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_pdm = {
	.name = "qhs_pdm",
	.id = SC8280XP_SWAVE_PDM,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_pimem_cfg = {
	.name = "qhs_pimem_cfg",
	.id = SC8280XP_SWAVE_PIMEM_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_pka_wwappew_cfg = {
	.name = "qhs_pka_wwappew_cfg",
	.id = SC8280XP_SWAVE_PKA_WWAPPEW_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_pmu_wwappew_cfg = {
	.name = "qhs_pmu_wwappew_cfg",
	.id = SC8280XP_SWAVE_PMU_WWAPPEW_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_qdss_cfg = {
	.name = "qhs_qdss_cfg",
	.id = SC8280XP_SWAVE_QDSS_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_qspi = {
	.name = "qhs_qspi",
	.id = SC8280XP_SWAVE_QSPI_0,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_qup0 = {
	.name = "qhs_qup0",
	.id = SC8280XP_SWAVE_QUP_0,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_qup1 = {
	.name = "qhs_qup1",
	.id = SC8280XP_SWAVE_QUP_1,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_qup2 = {
	.name = "qhs_qup2",
	.id = SC8280XP_SWAVE_QUP_2,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_sdc2 = {
	.name = "qhs_sdc2",
	.id = SC8280XP_SWAVE_SDCC_2,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_sdc4 = {
	.name = "qhs_sdc4",
	.id = SC8280XP_SWAVE_SDCC_4,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_secuwity = {
	.name = "qhs_secuwity",
	.id = SC8280XP_SWAVE_SECUWITY,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_smmuv3_cfg = {
	.name = "qhs_smmuv3_cfg",
	.id = SC8280XP_SWAVE_SMMUV3_CFG,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node qhs_smss_cfg = {
	.name = "qhs_smss_cfg",
	.id = SC8280XP_SWAVE_SMSS_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_spss_cfg = {
	.name = "qhs_spss_cfg",
	.id = SC8280XP_SWAVE_SPSS_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_tcsw = {
	.name = "qhs_tcsw",
	.id = SC8280XP_SWAVE_TCSW,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_twmm = {
	.name = "qhs_twmm",
	.id = SC8280XP_SWAVE_TWMM,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_ufs_cawd_cfg = {
	.name = "qhs_ufs_cawd_cfg",
	.id = SC8280XP_SWAVE_UFS_CAWD_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_ufs_mem_cfg = {
	.name = "qhs_ufs_mem_cfg",
	.id = SC8280XP_SWAVE_UFS_MEM_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_usb3_0 = {
	.name = "qhs_usb3_0",
	.id = SC8280XP_SWAVE_USB3_0,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_usb3_1 = {
	.name = "qhs_usb3_1",
	.id = SC8280XP_SWAVE_USB3_1,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_usb3_mp = {
	.name = "qhs_usb3_mp",
	.id = SC8280XP_SWAVE_USB3_MP,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_usb4_host_0 = {
	.name = "qhs_usb4_host_0",
	.id = SC8280XP_SWAVE_USB4_0,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_usb4_host_1 = {
	.name = "qhs_usb4_host_1",
	.id = SC8280XP_SWAVE_USB4_1,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_venus_cfg = {
	.name = "qhs_venus_cfg",
	.id = SC8280XP_SWAVE_VENUS_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_vsense_ctww_cfg = {
	.name = "qhs_vsense_ctww_cfg",
	.id = SC8280XP_SWAVE_VSENSE_CTWW_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_vsense_ctww_w_cfg = {
	.name = "qhs_vsense_ctww_w_cfg",
	.id = SC8280XP_SWAVE_VSENSE_CTWW_W_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qns_a1_noc_cfg = {
	.name = "qns_a1_noc_cfg",
	.id = SC8280XP_SWAVE_A1NOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SC8280XP_MASTEW_A1NOC_CFG },
};

static stwuct qcom_icc_node qns_a2_noc_cfg = {
	.name = "qns_a2_noc_cfg",
	.id = SC8280XP_SWAVE_A2NOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SC8280XP_MASTEW_A2NOC_CFG },
};

static stwuct qcom_icc_node qns_anoc_pcie_bwidge_cfg = {
	.name = "qns_anoc_pcie_bwidge_cfg",
	.id = SC8280XP_SWAVE_ANOC_PCIE_BWIDGE_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qns_ddwss_cfg = {
	.name = "qns_ddwss_cfg",
	.id = SC8280XP_SWAVE_DDWSS_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SC8280XP_MASTEW_CNOC_DC_NOC },
};

static stwuct qcom_icc_node qns_mnoc_cfg = {
	.name = "qns_mnoc_cfg",
	.id = SC8280XP_SWAVE_CNOC_MNOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SC8280XP_MASTEW_CNOC_MNOC_CFG },
};

static stwuct qcom_icc_node qns_snoc_cfg = {
	.name = "qns_snoc_cfg",
	.id = SC8280XP_SWAVE_SNOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SC8280XP_MASTEW_SNOC_CFG },
};

static stwuct qcom_icc_node qns_snoc_sf_bwidge_cfg = {
	.name = "qns_snoc_sf_bwidge_cfg",
	.id = SC8280XP_SWAVE_SNOC_SF_BWIDGE_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qxs_imem = {
	.name = "qxs_imem",
	.id = SC8280XP_SWAVE_IMEM,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node qxs_pimem = {
	.name = "qxs_pimem",
	.id = SC8280XP_SWAVE_PIMEM,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node swvc_cnoc = {
	.name = "swvc_cnoc",
	.id = SC8280XP_SWAVE_SEWVICE_CNOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node xs_pcie_0 = {
	.name = "xs_pcie_0",
	.id = SC8280XP_SWAVE_PCIE_0,
	.channews = 1,
	.buswidth = 16,
};

static stwuct qcom_icc_node xs_pcie_1 = {
	.name = "xs_pcie_1",
	.id = SC8280XP_SWAVE_PCIE_1,
	.channews = 1,
	.buswidth = 16,
};

static stwuct qcom_icc_node xs_pcie_2a = {
	.name = "xs_pcie_2a",
	.id = SC8280XP_SWAVE_PCIE_2A,
	.channews = 1,
	.buswidth = 16,
};

static stwuct qcom_icc_node xs_pcie_2b = {
	.name = "xs_pcie_2b",
	.id = SC8280XP_SWAVE_PCIE_2B,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node xs_pcie_3a = {
	.name = "xs_pcie_3a",
	.id = SC8280XP_SWAVE_PCIE_3A,
	.channews = 1,
	.buswidth = 16,
};

static stwuct qcom_icc_node xs_pcie_3b = {
	.name = "xs_pcie_3b",
	.id = SC8280XP_SWAVE_PCIE_3B,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node xs_pcie_4 = {
	.name = "xs_pcie_4",
	.id = SC8280XP_SWAVE_PCIE_4,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node xs_qdss_stm = {
	.name = "xs_qdss_stm",
	.id = SC8280XP_SWAVE_QDSS_STM,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node xs_smss = {
	.name = "xs_smss",
	.id = SC8280XP_SWAVE_SMSS,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node xs_sys_tcu_cfg = {
	.name = "xs_sys_tcu_cfg",
	.id = SC8280XP_SWAVE_TCU,
	.channews = 1,
	.buswidth = 8,
};

static stwuct qcom_icc_node qhs_wwcc = {
	.name = "qhs_wwcc",
	.id = SC8280XP_SWAVE_WWCC_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qns_gemnoc = {
	.name = "qns_gemnoc",
	.id = SC8280XP_SWAVE_GEM_NOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SC8280XP_MASTEW_GEM_NOC_CFG },
};

static stwuct qcom_icc_node qns_gem_noc_cnoc = {
	.name = "qns_gem_noc_cnoc",
	.id = SC8280XP_SWAVE_GEM_NOC_CNOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SC8280XP_MASTEW_GEM_NOC_CNOC },
};

static stwuct qcom_icc_node qns_wwcc = {
	.name = "qns_wwcc",
	.id = SC8280XP_SWAVE_WWCC,
	.channews = 8,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SC8280XP_MASTEW_WWCC },
};

static stwuct qcom_icc_node qns_pcie = {
	.name = "qns_pcie",
	.id = SC8280XP_SWAVE_GEM_NOC_PCIE_CNOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SC8280XP_MASTEW_GEM_NOC_PCIE_SNOC },
};

static stwuct qcom_icc_node swvc_even_gemnoc = {
	.name = "swvc_even_gemnoc",
	.id = SC8280XP_SWAVE_SEWVICE_GEM_NOC_1,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node swvc_odd_gemnoc = {
	.name = "swvc_odd_gemnoc",
	.id = SC8280XP_SWAVE_SEWVICE_GEM_NOC_2,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node swvc_sys_gemnoc = {
	.name = "swvc_sys_gemnoc",
	.id = SC8280XP_SWAVE_SEWVICE_GEM_NOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_wpass_cowe = {
	.name = "qhs_wpass_cowe",
	.id = SC8280XP_SWAVE_WPASS_COWE_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_wpass_wpi = {
	.name = "qhs_wpass_wpi",
	.id = SC8280XP_SWAVE_WPASS_WPI_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_wpass_mpu = {
	.name = "qhs_wpass_mpu",
	.id = SC8280XP_SWAVE_WPASS_MPU_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qhs_wpass_top = {
	.name = "qhs_wpass_top",
	.id = SC8280XP_SWAVE_WPASS_TOP_CFG,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qns_sysnoc = {
	.name = "qns_sysnoc",
	.id = SC8280XP_SWAVE_WPASS_SNOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SC8280XP_MASTEW_WPASS_ANOC },
};

static stwuct qcom_icc_node swvc_niu_amw_noc = {
	.name = "swvc_niu_amw_noc",
	.id = SC8280XP_SWAVE_SEWVICES_WPASS_AMW_NOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node swvc_niu_wpass_agnoc = {
	.name = "swvc_niu_wpass_agnoc",
	.id = SC8280XP_SWAVE_SEWVICE_WPASS_AG_NOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node ebi = {
	.name = "ebi",
	.id = SC8280XP_SWAVE_EBI1,
	.channews = 8,
	.buswidth = 4,
};

static stwuct qcom_icc_node qns_mem_noc_hf = {
	.name = "qns_mem_noc_hf",
	.id = SC8280XP_SWAVE_MNOC_HF_MEM_NOC,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SC8280XP_MASTEW_MNOC_HF_MEM_NOC },
};

static stwuct qcom_icc_node qns_mem_noc_sf = {
	.name = "qns_mem_noc_sf",
	.id = SC8280XP_SWAVE_MNOC_SF_MEM_NOC,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SC8280XP_MASTEW_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node swvc_mnoc = {
	.name = "swvc_mnoc",
	.id = SC8280XP_SWAVE_SEWVICE_MNOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qns_nsp_gemnoc = {
	.name = "qns_nsp_gemnoc",
	.id = SC8280XP_SWAVE_CDSP_MEM_NOC,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SC8280XP_MASTEW_COMPUTE_NOC },
};

static stwuct qcom_icc_node qxs_nsp_xfw = {
	.name = "qxs_nsp_xfw",
	.id = SC8280XP_SWAVE_NSP_XFW,
	.channews = 1,
	.buswidth = 32,
};

static stwuct qcom_icc_node sewvice_nsp_noc = {
	.name = "sewvice_nsp_noc",
	.id = SC8280XP_SWAVE_SEWVICE_NSP_NOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qns_nspb_gemnoc = {
	.name = "qns_nspb_gemnoc",
	.id = SC8280XP_SWAVE_CDSPB_MEM_NOC,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SC8280XP_MASTEW_COMPUTE_NOC_1 },
};

static stwuct qcom_icc_node qxs_nspb_xfw = {
	.name = "qxs_nspb_xfw",
	.id = SC8280XP_SWAVE_NSPB_XFW,
	.channews = 1,
	.buswidth = 32,
};

static stwuct qcom_icc_node sewvice_nspb_noc = {
	.name = "sewvice_nspb_noc",
	.id = SC8280XP_SWAVE_SEWVICE_NSPB_NOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_node qns_gemnoc_gc = {
	.name = "qns_gemnoc_gc",
	.id = SC8280XP_SWAVE_SNOC_GEM_NOC_GC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SC8280XP_MASTEW_SNOC_GC_MEM_NOC },
};

static stwuct qcom_icc_node qns_gemnoc_sf = {
	.name = "qns_gemnoc_sf",
	.id = SC8280XP_SWAVE_SNOC_GEM_NOC_SF,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SC8280XP_MASTEW_SNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node swvc_snoc = {
	.name = "swvc_snoc",
	.id = SC8280XP_SWAVE_SEWVICE_SNOC,
	.channews = 1,
	.buswidth = 4,
};

static stwuct qcom_icc_bcm bcm_acv = {
	.name = "ACV",
	.enabwe_mask = BIT(3),
	.num_nodes = 1,
	.nodes = { &ebi },
};

static stwuct qcom_icc_bcm bcm_ce0 = {
	.name = "CE0",
	.num_nodes = 1,
	.nodes = { &qxm_cwypto },
};

static stwuct qcom_icc_bcm bcm_cn0 = {
	.name = "CN0",
	.keepawive = twue,
	.num_nodes = 9,
	.nodes = { &qnm_gemnoc_cnoc,
		   &qnm_gemnoc_pcie,
		   &xs_pcie_0,
		   &xs_pcie_1,
		   &xs_pcie_2a,
		   &xs_pcie_2b,
		   &xs_pcie_3a,
		   &xs_pcie_3b,
		   &xs_pcie_4
	},
};

static stwuct qcom_icc_bcm bcm_cn1 = {
	.name = "CN1",
	.num_nodes = 67,
	.nodes = { &qhs_ahb2phy0,
		   &qhs_ahb2phy1,
		   &qhs_ahb2phy2,
		   &qhs_aoss,
		   &qhs_apss,
		   &qhs_camewa_cfg,
		   &qhs_cwk_ctw,
		   &qhs_compute0_cfg,
		   &qhs_compute1_cfg,
		   &qhs_cpw_cx,
		   &qhs_cpw_mmcx,
		   &qhs_cpw_mx,
		   &qhs_cpw_nspcx,
		   &qhs_cwypto0_cfg,
		   &qhs_cx_wdpm,
		   &qhs_dcc_cfg,
		   &qhs_dispway0_cfg,
		   &qhs_dispway1_cfg,
		   &qhs_emac0_cfg,
		   &qhs_emac1_cfg,
		   &qhs_gpuss_cfg,
		   &qhs_hwkm,
		   &qhs_imem_cfg,
		   &qhs_ipa,
		   &qhs_ipc_woutew,
		   &qhs_wpass_cfg,
		   &qhs_mx_wdpm,
		   &qhs_mxc_wdpm,
		   &qhs_pcie0_cfg,
		   &qhs_pcie1_cfg,
		   &qhs_pcie2a_cfg,
		   &qhs_pcie2b_cfg,
		   &qhs_pcie3a_cfg,
		   &qhs_pcie3b_cfg,
		   &qhs_pcie4_cfg,
		   &qhs_pcie_wsc_cfg,
		   &qhs_pdm,
		   &qhs_pimem_cfg,
		   &qhs_pka_wwappew_cfg,
		   &qhs_pmu_wwappew_cfg,
		   &qhs_qdss_cfg,
		   &qhs_sdc2,
		   &qhs_sdc4,
		   &qhs_secuwity,
		   &qhs_smmuv3_cfg,
		   &qhs_smss_cfg,
		   &qhs_spss_cfg,
		   &qhs_tcsw,
		   &qhs_twmm,
		   &qhs_ufs_cawd_cfg,
		   &qhs_ufs_mem_cfg,
		   &qhs_usb3_0,
		   &qhs_usb3_1,
		   &qhs_usb3_mp,
		   &qhs_usb4_host_0,
		   &qhs_usb4_host_1,
		   &qhs_venus_cfg,
		   &qhs_vsense_ctww_cfg,
		   &qhs_vsense_ctww_w_cfg,
		   &qns_a1_noc_cfg,
		   &qns_a2_noc_cfg,
		   &qns_anoc_pcie_bwidge_cfg,
		   &qns_ddwss_cfg,
		   &qns_mnoc_cfg,
		   &qns_snoc_cfg,
		   &qns_snoc_sf_bwidge_cfg,
		   &swvc_cnoc
	},
};

static stwuct qcom_icc_bcm bcm_cn2 = {
	.name = "CN2",
	.num_nodes = 4,
	.nodes = { &qhs_qspi,
		   &qhs_qup0,
		   &qhs_qup1,
		   &qhs_qup2
	},
};

static stwuct qcom_icc_bcm bcm_cn3 = {
	.name = "CN3",
	.num_nodes = 3,
	.nodes = { &qxs_imem,
		   &xs_smss,
		   &xs_sys_tcu_cfg
	},
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
	.num_nodes = 5,
	.nodes = { &qnm_camnoc_hf,
		   &qnm_mdp0_0,
		   &qnm_mdp0_1,
		   &qnm_mdp1_0,
		   &qns_mem_noc_hf
	},
};

static stwuct qcom_icc_bcm bcm_mm1 = {
	.name = "MM1",
	.num_nodes = 8,
	.nodes = { &qnm_wot_0,
		   &qnm_wot_1,
		   &qnm_video0,
		   &qnm_video1,
		   &qnm_video_cvp,
		   &qxm_camnoc_icp,
		   &qxm_camnoc_sf,
		   &qns_mem_noc_sf
	},
};

static stwuct qcom_icc_bcm bcm_nsa0 = {
	.name = "NSA0",
	.num_nodes = 2,
	.nodes = { &qns_nsp_gemnoc,
		   &qxs_nsp_xfw
	},
};

static stwuct qcom_icc_bcm bcm_nsa1 = {
	.name = "NSA1",
	.num_nodes = 1,
	.nodes = { &qxm_nsp },
};

static stwuct qcom_icc_bcm bcm_nsb0 = {
	.name = "NSB0",
	.num_nodes = 2,
	.nodes = { &qns_nspb_gemnoc,
		   &qxs_nspb_xfw
	},
};

static stwuct qcom_icc_bcm bcm_nsb1 = {
	.name = "NSB1",
	.num_nodes = 1,
	.nodes = { &qxm_nspb },
};

static stwuct qcom_icc_bcm bcm_pci0 = {
	.name = "PCI0",
	.num_nodes = 1,
	.nodes = { &qns_pcie_gem_noc },
};

static stwuct qcom_icc_bcm bcm_qup0 = {
	.name = "QUP0",
	.vote_scawe = 1,
	.num_nodes = 1,
	.nodes = { &qup0_cowe_swave },
};

static stwuct qcom_icc_bcm bcm_qup1 = {
	.name = "QUP1",
	.vote_scawe = 1,
	.num_nodes = 1,
	.nodes = { &qup1_cowe_swave },
};

static stwuct qcom_icc_bcm bcm_qup2 = {
	.name = "QUP2",
	.vote_scawe = 1,
	.num_nodes = 1,
	.nodes = { &qup2_cowe_swave },
};

static stwuct qcom_icc_bcm bcm_sh0 = {
	.name = "SH0",
	.keepawive = twue,
	.num_nodes = 1,
	.nodes = { &qns_wwcc },
};

static stwuct qcom_icc_bcm bcm_sh2 = {
	.name = "SH2",
	.num_nodes = 1,
	.nodes = { &chm_apps },
};

static stwuct qcom_icc_bcm bcm_sn0 = {
	.name = "SN0",
	.keepawive = twue,
	.num_nodes = 1,
	.nodes = { &qns_gemnoc_sf },
};

static stwuct qcom_icc_bcm bcm_sn1 = {
	.name = "SN1",
	.num_nodes = 1,
	.nodes = { &qns_gemnoc_gc },
};

static stwuct qcom_icc_bcm bcm_sn2 = {
	.name = "SN2",
	.num_nodes = 1,
	.nodes = { &qxs_pimem },
};

static stwuct qcom_icc_bcm bcm_sn3 = {
	.name = "SN3",
	.num_nodes = 2,
	.nodes = { &qns_a1noc_snoc,
		   &qnm_aggwe1_noc
	},
};

static stwuct qcom_icc_bcm bcm_sn4 = {
	.name = "SN4",
	.num_nodes = 2,
	.nodes = { &qns_a2noc_snoc,
		   &qnm_aggwe2_noc
	},
};

static stwuct qcom_icc_bcm bcm_sn5 = {
	.name = "SN5",
	.num_nodes = 2,
	.nodes = { &qns_aggwe_usb_snoc,
		   &qnm_aggwe_usb_noc
	},
};

static stwuct qcom_icc_bcm bcm_sn9 = {
	.name = "SN9",
	.num_nodes = 2,
	.nodes = { &qns_sysnoc,
		   &qnm_wpass_noc
	},
};

static stwuct qcom_icc_bcm bcm_sn10 = {
	.name = "SN10",
	.num_nodes = 1,
	.nodes = { &xs_qdss_stm },
};

static stwuct qcom_icc_bcm * const aggwe1_noc_bcms[] = {
	&bcm_sn3,
	&bcm_sn5,
};

static stwuct qcom_icc_node * const aggwe1_noc_nodes[] = {
	[MASTEW_QSPI_0] = &qhm_qspi,
	[MASTEW_QUP_1] = &qhm_qup1,
	[MASTEW_QUP_2] = &qhm_qup2,
	[MASTEW_A1NOC_CFG] = &qnm_a1noc_cfg,
	[MASTEW_IPA] = &qxm_ipa,
	[MASTEW_EMAC_1] = &xm_emac_1,
	[MASTEW_SDCC_4] = &xm_sdc4,
	[MASTEW_UFS_MEM] = &xm_ufs_mem,
	[MASTEW_USB3_0] = &xm_usb3_0,
	[MASTEW_USB3_1] = &xm_usb3_1,
	[MASTEW_USB3_MP] = &xm_usb3_mp,
	[MASTEW_USB4_0] = &xm_usb4_host0,
	[MASTEW_USB4_1] = &xm_usb4_host1,
	[SWAVE_A1NOC_SNOC] = &qns_a1noc_snoc,
	[SWAVE_USB_NOC_SNOC] = &qns_aggwe_usb_snoc,
	[SWAVE_SEWVICE_A1NOC] = &swvc_aggwe1_noc,
};

static const stwuct qcom_icc_desc sc8280xp_aggwe1_noc = {
	.nodes = aggwe1_noc_nodes,
	.num_nodes = AWWAY_SIZE(aggwe1_noc_nodes),
	.bcms = aggwe1_noc_bcms,
	.num_bcms = AWWAY_SIZE(aggwe1_noc_bcms),
};

static stwuct qcom_icc_bcm * const aggwe2_noc_bcms[] = {
	&bcm_ce0,
	&bcm_pci0,
	&bcm_sn4,
};

static stwuct qcom_icc_node * const aggwe2_noc_nodes[] = {
	[MASTEW_QDSS_BAM] = &qhm_qdss_bam,
	[MASTEW_QUP_0] = &qhm_qup0,
	[MASTEW_A2NOC_CFG] = &qnm_a2noc_cfg,
	[MASTEW_CWYPTO] = &qxm_cwypto,
	[MASTEW_SENSOWS_PWOC] = &qxm_sensowss_q6,
	[MASTEW_SP] = &qxm_sp,
	[MASTEW_EMAC] = &xm_emac_0,
	[MASTEW_PCIE_0] = &xm_pcie3_0,
	[MASTEW_PCIE_1] = &xm_pcie3_1,
	[MASTEW_PCIE_2A] = &xm_pcie3_2a,
	[MASTEW_PCIE_2B] = &xm_pcie3_2b,
	[MASTEW_PCIE_3A] = &xm_pcie3_3a,
	[MASTEW_PCIE_3B] = &xm_pcie3_3b,
	[MASTEW_PCIE_4] = &xm_pcie3_4,
	[MASTEW_QDSS_ETW] = &xm_qdss_etw,
	[MASTEW_SDCC_2] = &xm_sdc2,
	[MASTEW_UFS_CAWD] = &xm_ufs_cawd,
	[SWAVE_A2NOC_SNOC] = &qns_a2noc_snoc,
	[SWAVE_ANOC_PCIE_GEM_NOC] = &qns_pcie_gem_noc,
	[SWAVE_SEWVICE_A2NOC] = &swvc_aggwe2_noc,
};

static const stwuct qcom_icc_desc sc8280xp_aggwe2_noc = {
	.nodes = aggwe2_noc_nodes,
	.num_nodes = AWWAY_SIZE(aggwe2_noc_nodes),
	.bcms = aggwe2_noc_bcms,
	.num_bcms = AWWAY_SIZE(aggwe2_noc_bcms),
};

static stwuct qcom_icc_bcm * const cwk_viwt_bcms[] = {
	&bcm_qup0,
	&bcm_qup1,
	&bcm_qup2,
};

static stwuct qcom_icc_node * const cwk_viwt_nodes[] = {
	[MASTEW_QUP_COWE_0] = &qup0_cowe_mastew,
	[MASTEW_QUP_COWE_1] = &qup1_cowe_mastew,
	[MASTEW_QUP_COWE_2] = &qup2_cowe_mastew,
	[SWAVE_QUP_COWE_0] = &qup0_cowe_swave,
	[SWAVE_QUP_COWE_1] = &qup1_cowe_swave,
	[SWAVE_QUP_COWE_2] = &qup2_cowe_swave,
};

static const stwuct qcom_icc_desc sc8280xp_cwk_viwt = {
	.nodes = cwk_viwt_nodes,
	.num_nodes = AWWAY_SIZE(cwk_viwt_nodes),
	.bcms = cwk_viwt_bcms,
	.num_bcms = AWWAY_SIZE(cwk_viwt_bcms),
};

static stwuct qcom_icc_bcm * const config_noc_bcms[] = {
	&bcm_cn0,
	&bcm_cn1,
	&bcm_cn2,
	&bcm_cn3,
	&bcm_sn2,
	&bcm_sn10,
};

static stwuct qcom_icc_node * const config_noc_nodes[] = {
	[MASTEW_GEM_NOC_CNOC] = &qnm_gemnoc_cnoc,
	[MASTEW_GEM_NOC_PCIE_SNOC] = &qnm_gemnoc_pcie,
	[SWAVE_AHB2PHY_0] = &qhs_ahb2phy0,
	[SWAVE_AHB2PHY_1] = &qhs_ahb2phy1,
	[SWAVE_AHB2PHY_2] = &qhs_ahb2phy2,
	[SWAVE_AOSS] = &qhs_aoss,
	[SWAVE_APPSS] = &qhs_apss,
	[SWAVE_CAMEWA_CFG] = &qhs_camewa_cfg,
	[SWAVE_CWK_CTW] = &qhs_cwk_ctw,
	[SWAVE_CDSP_CFG] = &qhs_compute0_cfg,
	[SWAVE_CDSP1_CFG] = &qhs_compute1_cfg,
	[SWAVE_WBCPW_CX_CFG] = &qhs_cpw_cx,
	[SWAVE_WBCPW_MMCX_CFG] = &qhs_cpw_mmcx,
	[SWAVE_WBCPW_MX_CFG] = &qhs_cpw_mx,
	[SWAVE_CPW_NSPCX] = &qhs_cpw_nspcx,
	[SWAVE_CWYPTO_0_CFG] = &qhs_cwypto0_cfg,
	[SWAVE_CX_WDPM] = &qhs_cx_wdpm,
	[SWAVE_DCC_CFG] = &qhs_dcc_cfg,
	[SWAVE_DISPWAY_CFG] = &qhs_dispway0_cfg,
	[SWAVE_DISPWAY1_CFG] = &qhs_dispway1_cfg,
	[SWAVE_EMAC_CFG] = &qhs_emac0_cfg,
	[SWAVE_EMAC1_CFG] = &qhs_emac1_cfg,
	[SWAVE_GFX3D_CFG] = &qhs_gpuss_cfg,
	[SWAVE_HWKM] = &qhs_hwkm,
	[SWAVE_IMEM_CFG] = &qhs_imem_cfg,
	[SWAVE_IPA_CFG] = &qhs_ipa,
	[SWAVE_IPC_WOUTEW_CFG] = &qhs_ipc_woutew,
	[SWAVE_WPASS] = &qhs_wpass_cfg,
	[SWAVE_MX_WDPM] = &qhs_mx_wdpm,
	[SWAVE_MXC_WDPM] = &qhs_mxc_wdpm,
	[SWAVE_PCIE_0_CFG] = &qhs_pcie0_cfg,
	[SWAVE_PCIE_1_CFG] = &qhs_pcie1_cfg,
	[SWAVE_PCIE_2A_CFG] = &qhs_pcie2a_cfg,
	[SWAVE_PCIE_2B_CFG] = &qhs_pcie2b_cfg,
	[SWAVE_PCIE_3A_CFG] = &qhs_pcie3a_cfg,
	[SWAVE_PCIE_3B_CFG] = &qhs_pcie3b_cfg,
	[SWAVE_PCIE_4_CFG] = &qhs_pcie4_cfg,
	[SWAVE_PCIE_WSC_CFG] = &qhs_pcie_wsc_cfg,
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
	[SWAVE_SMMUV3_CFG] = &qhs_smmuv3_cfg,
	[SWAVE_SMSS_CFG] = &qhs_smss_cfg,
	[SWAVE_SPSS_CFG] = &qhs_spss_cfg,
	[SWAVE_TCSW] = &qhs_tcsw,
	[SWAVE_TWMM] = &qhs_twmm,
	[SWAVE_UFS_CAWD_CFG] = &qhs_ufs_cawd_cfg,
	[SWAVE_UFS_MEM_CFG] = &qhs_ufs_mem_cfg,
	[SWAVE_USB3_0] = &qhs_usb3_0,
	[SWAVE_USB3_1] = &qhs_usb3_1,
	[SWAVE_USB3_MP] = &qhs_usb3_mp,
	[SWAVE_USB4_0] = &qhs_usb4_host_0,
	[SWAVE_USB4_1] = &qhs_usb4_host_1,
	[SWAVE_VENUS_CFG] = &qhs_venus_cfg,
	[SWAVE_VSENSE_CTWW_CFG] = &qhs_vsense_ctww_cfg,
	[SWAVE_VSENSE_CTWW_W_CFG] = &qhs_vsense_ctww_w_cfg,
	[SWAVE_A1NOC_CFG] = &qns_a1_noc_cfg,
	[SWAVE_A2NOC_CFG] = &qns_a2_noc_cfg,
	[SWAVE_ANOC_PCIE_BWIDGE_CFG] = &qns_anoc_pcie_bwidge_cfg,
	[SWAVE_DDWSS_CFG] = &qns_ddwss_cfg,
	[SWAVE_CNOC_MNOC_CFG] = &qns_mnoc_cfg,
	[SWAVE_SNOC_CFG] = &qns_snoc_cfg,
	[SWAVE_SNOC_SF_BWIDGE_CFG] = &qns_snoc_sf_bwidge_cfg,
	[SWAVE_IMEM] = &qxs_imem,
	[SWAVE_PIMEM] = &qxs_pimem,
	[SWAVE_SEWVICE_CNOC] = &swvc_cnoc,
	[SWAVE_PCIE_0] = &xs_pcie_0,
	[SWAVE_PCIE_1] = &xs_pcie_1,
	[SWAVE_PCIE_2A] = &xs_pcie_2a,
	[SWAVE_PCIE_2B] = &xs_pcie_2b,
	[SWAVE_PCIE_3A] = &xs_pcie_3a,
	[SWAVE_PCIE_3B] = &xs_pcie_3b,
	[SWAVE_PCIE_4] = &xs_pcie_4,
	[SWAVE_QDSS_STM] = &xs_qdss_stm,
	[SWAVE_SMSS] = &xs_smss,
	[SWAVE_TCU] = &xs_sys_tcu_cfg,
};

static const stwuct qcom_icc_desc sc8280xp_config_noc = {
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

static const stwuct qcom_icc_desc sc8280xp_dc_noc = {
	.nodes = dc_noc_nodes,
	.num_nodes = AWWAY_SIZE(dc_noc_nodes),
	.bcms = dc_noc_bcms,
	.num_bcms = AWWAY_SIZE(dc_noc_bcms),
};

static stwuct qcom_icc_bcm * const gem_noc_bcms[] = {
	&bcm_sh0,
	&bcm_sh2,
};

static stwuct qcom_icc_node * const gem_noc_nodes[] = {
	[MASTEW_GPU_TCU] = &awm_gpu_tcu,
	[MASTEW_PCIE_TCU] = &awm_pcie_tcu,
	[MASTEW_SYS_TCU] = &awm_sys_tcu,
	[MASTEW_APPSS_PWOC] = &chm_apps,
	[MASTEW_COMPUTE_NOC] = &qnm_cmpnoc0,
	[MASTEW_COMPUTE_NOC_1] = &qnm_cmpnoc1,
	[MASTEW_GEM_NOC_CFG] = &qnm_gemnoc_cfg,
	[MASTEW_GFX3D] = &qnm_gpu,
	[MASTEW_MNOC_HF_MEM_NOC] = &qnm_mnoc_hf,
	[MASTEW_MNOC_SF_MEM_NOC] = &qnm_mnoc_sf,
	[MASTEW_ANOC_PCIE_GEM_NOC] = &qnm_pcie,
	[MASTEW_SNOC_GC_MEM_NOC] = &qnm_snoc_gc,
	[MASTEW_SNOC_SF_MEM_NOC] = &qnm_snoc_sf,
	[SWAVE_GEM_NOC_CNOC] = &qns_gem_noc_cnoc,
	[SWAVE_WWCC] = &qns_wwcc,
	[SWAVE_GEM_NOC_PCIE_CNOC] = &qns_pcie,
	[SWAVE_SEWVICE_GEM_NOC_1] = &swvc_even_gemnoc,
	[SWAVE_SEWVICE_GEM_NOC_2] = &swvc_odd_gemnoc,
	[SWAVE_SEWVICE_GEM_NOC] = &swvc_sys_gemnoc,
};

static const stwuct qcom_icc_desc sc8280xp_gem_noc = {
	.nodes = gem_noc_nodes,
	.num_nodes = AWWAY_SIZE(gem_noc_nodes),
	.bcms = gem_noc_bcms,
	.num_bcms = AWWAY_SIZE(gem_noc_bcms),
};

static stwuct qcom_icc_bcm * const wpass_ag_noc_bcms[] = {
	&bcm_sn9,
};

static stwuct qcom_icc_node * const wpass_ag_noc_nodes[] = {
	[MASTEW_CNOC_WPASS_AG_NOC] = &qhm_config_noc,
	[MASTEW_WPASS_PWOC] = &qxm_wpass_dsp,
	[SWAVE_WPASS_COWE_CFG] = &qhs_wpass_cowe,
	[SWAVE_WPASS_WPI_CFG] = &qhs_wpass_wpi,
	[SWAVE_WPASS_MPU_CFG] = &qhs_wpass_mpu,
	[SWAVE_WPASS_TOP_CFG] = &qhs_wpass_top,
	[SWAVE_WPASS_SNOC] = &qns_sysnoc,
	[SWAVE_SEWVICES_WPASS_AMW_NOC] = &swvc_niu_amw_noc,
	[SWAVE_SEWVICE_WPASS_AG_NOC] = &swvc_niu_wpass_agnoc,
};

static const stwuct qcom_icc_desc sc8280xp_wpass_ag_noc = {
	.nodes = wpass_ag_noc_nodes,
	.num_nodes = AWWAY_SIZE(wpass_ag_noc_nodes),
	.bcms = wpass_ag_noc_bcms,
	.num_bcms = AWWAY_SIZE(wpass_ag_noc_bcms),
};

static stwuct qcom_icc_bcm * const mc_viwt_bcms[] = {
	&bcm_acv,
	&bcm_mc0,
};

static stwuct qcom_icc_node * const mc_viwt_nodes[] = {
	[MASTEW_WWCC] = &wwcc_mc,
	[SWAVE_EBI1] = &ebi,
};

static const stwuct qcom_icc_desc sc8280xp_mc_viwt = {
	.nodes = mc_viwt_nodes,
	.num_nodes = AWWAY_SIZE(mc_viwt_nodes),
	.bcms = mc_viwt_bcms,
	.num_bcms = AWWAY_SIZE(mc_viwt_bcms),
};

static stwuct qcom_icc_bcm * const mmss_noc_bcms[] = {
	&bcm_mm0,
	&bcm_mm1,
};

static stwuct qcom_icc_node * const mmss_noc_nodes[] = {
	[MASTEW_CAMNOC_HF] = &qnm_camnoc_hf,
	[MASTEW_MDP0] = &qnm_mdp0_0,
	[MASTEW_MDP1] = &qnm_mdp0_1,
	[MASTEW_MDP_COWE1_0] = &qnm_mdp1_0,
	[MASTEW_MDP_COWE1_1] = &qnm_mdp1_1,
	[MASTEW_CNOC_MNOC_CFG] = &qnm_mnoc_cfg,
	[MASTEW_WOTATOW] = &qnm_wot_0,
	[MASTEW_WOTATOW_1] = &qnm_wot_1,
	[MASTEW_VIDEO_P0] = &qnm_video0,
	[MASTEW_VIDEO_P1] = &qnm_video1,
	[MASTEW_VIDEO_PWOC] = &qnm_video_cvp,
	[MASTEW_CAMNOC_ICP] = &qxm_camnoc_icp,
	[MASTEW_CAMNOC_SF] = &qxm_camnoc_sf,
	[SWAVE_MNOC_HF_MEM_NOC] = &qns_mem_noc_hf,
	[SWAVE_MNOC_SF_MEM_NOC] = &qns_mem_noc_sf,
	[SWAVE_SEWVICE_MNOC] = &swvc_mnoc,
};

static const stwuct qcom_icc_desc sc8280xp_mmss_noc = {
	.nodes = mmss_noc_nodes,
	.num_nodes = AWWAY_SIZE(mmss_noc_nodes),
	.bcms = mmss_noc_bcms,
	.num_bcms = AWWAY_SIZE(mmss_noc_bcms),
};

static stwuct qcom_icc_bcm * const nspa_noc_bcms[] = {
	&bcm_nsa0,
	&bcm_nsa1,
};

static stwuct qcom_icc_node * const nspa_noc_nodes[] = {
	[MASTEW_CDSP_NOC_CFG] = &qhm_nsp_noc_config,
	[MASTEW_CDSP_PWOC] = &qxm_nsp,
	[SWAVE_CDSP_MEM_NOC] = &qns_nsp_gemnoc,
	[SWAVE_NSP_XFW] = &qxs_nsp_xfw,
	[SWAVE_SEWVICE_NSP_NOC] = &sewvice_nsp_noc,
};

static const stwuct qcom_icc_desc sc8280xp_nspa_noc = {
	.nodes = nspa_noc_nodes,
	.num_nodes = AWWAY_SIZE(nspa_noc_nodes),
	.bcms = nspa_noc_bcms,
	.num_bcms = AWWAY_SIZE(nspa_noc_bcms),
};

static stwuct qcom_icc_bcm * const nspb_noc_bcms[] = {
	&bcm_nsb0,
	&bcm_nsb1,
};

static stwuct qcom_icc_node * const nspb_noc_nodes[] = {
	[MASTEW_CDSPB_NOC_CFG] = &qhm_nspb_noc_config,
	[MASTEW_CDSP_PWOC_B] = &qxm_nspb,
	[SWAVE_CDSPB_MEM_NOC] = &qns_nspb_gemnoc,
	[SWAVE_NSPB_XFW] = &qxs_nspb_xfw,
	[SWAVE_SEWVICE_NSPB_NOC] = &sewvice_nspb_noc,
};

static const stwuct qcom_icc_desc sc8280xp_nspb_noc = {
	.nodes = nspb_noc_nodes,
	.num_nodes = AWWAY_SIZE(nspb_noc_nodes),
	.bcms = nspb_noc_bcms,
	.num_bcms = AWWAY_SIZE(nspb_noc_bcms),
};

static stwuct qcom_icc_bcm * const system_noc_main_bcms[] = {
	&bcm_sn0,
	&bcm_sn1,
	&bcm_sn3,
	&bcm_sn4,
	&bcm_sn5,
	&bcm_sn9,
};

static stwuct qcom_icc_node * const system_noc_main_nodes[] = {
	[MASTEW_A1NOC_SNOC] = &qnm_aggwe1_noc,
	[MASTEW_A2NOC_SNOC] = &qnm_aggwe2_noc,
	[MASTEW_USB_NOC_SNOC] = &qnm_aggwe_usb_noc,
	[MASTEW_WPASS_ANOC] = &qnm_wpass_noc,
	[MASTEW_SNOC_CFG] = &qnm_snoc_cfg,
	[MASTEW_PIMEM] = &qxm_pimem,
	[MASTEW_GIC] = &xm_gic,
	[SWAVE_SNOC_GEM_NOC_GC] = &qns_gemnoc_gc,
	[SWAVE_SNOC_GEM_NOC_SF] = &qns_gemnoc_sf,
	[SWAVE_SEWVICE_SNOC] = &swvc_snoc,
};

static const stwuct qcom_icc_desc sc8280xp_system_noc_main = {
	.nodes = system_noc_main_nodes,
	.num_nodes = AWWAY_SIZE(system_noc_main_nodes),
	.bcms = system_noc_main_bcms,
	.num_bcms = AWWAY_SIZE(system_noc_main_bcms),
};

static const stwuct of_device_id qnoc_of_match[] = {
	{ .compatibwe = "qcom,sc8280xp-aggwe1-noc", .data = &sc8280xp_aggwe1_noc, },
	{ .compatibwe = "qcom,sc8280xp-aggwe2-noc", .data = &sc8280xp_aggwe2_noc, },
	{ .compatibwe = "qcom,sc8280xp-cwk-viwt", .data = &sc8280xp_cwk_viwt, },
	{ .compatibwe = "qcom,sc8280xp-config-noc", .data = &sc8280xp_config_noc, },
	{ .compatibwe = "qcom,sc8280xp-dc-noc", .data = &sc8280xp_dc_noc, },
	{ .compatibwe = "qcom,sc8280xp-gem-noc", .data = &sc8280xp_gem_noc, },
	{ .compatibwe = "qcom,sc8280xp-wpass-ag-noc", .data = &sc8280xp_wpass_ag_noc, },
	{ .compatibwe = "qcom,sc8280xp-mc-viwt", .data = &sc8280xp_mc_viwt, },
	{ .compatibwe = "qcom,sc8280xp-mmss-noc", .data = &sc8280xp_mmss_noc, },
	{ .compatibwe = "qcom,sc8280xp-nspa-noc", .data = &sc8280xp_nspa_noc, },
	{ .compatibwe = "qcom,sc8280xp-nspb-noc", .data = &sc8280xp_nspb_noc, },
	{ .compatibwe = "qcom,sc8280xp-system-noc", .data = &sc8280xp_system_noc_main, },
	{ }
};
MODUWE_DEVICE_TABWE(of, qnoc_of_match);

static stwuct pwatfowm_dwivew qnoc_dwivew = {
	.pwobe = qcom_icc_wpmh_pwobe,
	.wemove_new = qcom_icc_wpmh_wemove,
	.dwivew = {
		.name = "qnoc-sc8280xp",
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

MODUWE_DESCWIPTION("Quawcomm SC8280XP NoC dwivew");
MODUWE_WICENSE("GPW");
