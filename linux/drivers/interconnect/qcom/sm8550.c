// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2022, Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 * Copywight (c) 2022, Winawo Wimited
 *
 */

#incwude <winux/device.h>
#incwude <winux/intewconnect.h>
#incwude <winux/intewconnect-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <dt-bindings/intewconnect/qcom,sm8550-wpmh.h>

#incwude "bcm-votew.h"
#incwude "icc-common.h"
#incwude "icc-wpmh.h"
#incwude "sm8550.h"

static stwuct qcom_icc_node qhm_qspi = {
	.name = "qhm_qspi",
	.id = SM8550_MASTEW_QSPI_0,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_A1NOC_SNOC },
};

static stwuct qcom_icc_node qhm_qup1 = {
	.name = "qhm_qup1",
	.id = SM8550_MASTEW_QUP_1,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_A1NOC_SNOC },
};

static stwuct qcom_icc_node xm_sdc4 = {
	.name = "xm_sdc4",
	.id = SM8550_MASTEW_SDCC_4,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_A1NOC_SNOC },
};

static stwuct qcom_icc_node xm_ufs_mem = {
	.name = "xm_ufs_mem",
	.id = SM8550_MASTEW_UFS_MEM,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_A1NOC_SNOC },
};

static stwuct qcom_icc_node xm_usb3_0 = {
	.name = "xm_usb3_0",
	.id = SM8550_MASTEW_USB3_0,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_A1NOC_SNOC },
};

static stwuct qcom_icc_node qhm_qdss_bam = {
	.name = "qhm_qdss_bam",
	.id = SM8550_MASTEW_QDSS_BAM,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_A2NOC_SNOC },
};

static stwuct qcom_icc_node qhm_qup2 = {
	.name = "qhm_qup2",
	.id = SM8550_MASTEW_QUP_2,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_A2NOC_SNOC },
};

static stwuct qcom_icc_node qxm_cwypto = {
	.name = "qxm_cwypto",
	.id = SM8550_MASTEW_CWYPTO,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_A2NOC_SNOC },
};

static stwuct qcom_icc_node qxm_ipa = {
	.name = "qxm_ipa",
	.id = SM8550_MASTEW_IPA,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_A2NOC_SNOC },
};

static stwuct qcom_icc_node qxm_sp = {
	.name = "qxm_sp",
	.id = SM8550_MASTEW_SP,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_A2NOC_SNOC },
};

static stwuct qcom_icc_node xm_qdss_etw_0 = {
	.name = "xm_qdss_etw_0",
	.id = SM8550_MASTEW_QDSS_ETW,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_A2NOC_SNOC },
};

static stwuct qcom_icc_node xm_qdss_etw_1 = {
	.name = "xm_qdss_etw_1",
	.id = SM8550_MASTEW_QDSS_ETW_1,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_A2NOC_SNOC },
};

static stwuct qcom_icc_node xm_sdc2 = {
	.name = "xm_sdc2",
	.id = SM8550_MASTEW_SDCC_2,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_A2NOC_SNOC },
};

static stwuct qcom_icc_node qup0_cowe_mastew = {
	.name = "qup0_cowe_mastew",
	.id = SM8550_MASTEW_QUP_COWE_0,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_QUP_COWE_0 },
};

static stwuct qcom_icc_node qup1_cowe_mastew = {
	.name = "qup1_cowe_mastew",
	.id = SM8550_MASTEW_QUP_COWE_1,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_QUP_COWE_1 },
};

static stwuct qcom_icc_node qup2_cowe_mastew = {
	.name = "qup2_cowe_mastew",
	.id = SM8550_MASTEW_QUP_COWE_2,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_QUP_COWE_2 },
};

static stwuct qcom_icc_node qsm_cfg = {
	.name = "qsm_cfg",
	.id = SM8550_MASTEW_CNOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 44,
	.winks = { SM8550_SWAVE_AHB2PHY_SOUTH, SM8550_SWAVE_AHB2PHY_NOWTH,
		   SM8550_SWAVE_APPSS, SM8550_SWAVE_CAMEWA_CFG,
		   SM8550_SWAVE_CWK_CTW, SM8550_SWAVE_WBCPW_CX_CFG,
		   SM8550_SWAVE_WBCPW_MMCX_CFG, SM8550_SWAVE_WBCPW_MXA_CFG,
		   SM8550_SWAVE_WBCPW_MXC_CFG, SM8550_SWAVE_CPW_NSPCX,
		   SM8550_SWAVE_CWYPTO_0_CFG, SM8550_SWAVE_CX_WDPM,
		   SM8550_SWAVE_DISPWAY_CFG, SM8550_SWAVE_GFX3D_CFG,
		   SM8550_SWAVE_I2C, SM8550_SWAVE_IMEM_CFG,
		   SM8550_SWAVE_IPA_CFG, SM8550_SWAVE_IPC_WOUTEW_CFG,
		   SM8550_SWAVE_CNOC_MSS, SM8550_SWAVE_MX_WDPM,
		   SM8550_SWAVE_PCIE_0_CFG, SM8550_SWAVE_PCIE_1_CFG,
		   SM8550_SWAVE_PDM, SM8550_SWAVE_PIMEM_CFG,
		   SM8550_SWAVE_PWNG, SM8550_SWAVE_QDSS_CFG,
		   SM8550_SWAVE_QSPI_0, SM8550_SWAVE_QUP_1,
		   SM8550_SWAVE_QUP_2, SM8550_SWAVE_SDCC_2,
		   SM8550_SWAVE_SDCC_4, SM8550_SWAVE_SPSS_CFG,
		   SM8550_SWAVE_TCSW, SM8550_SWAVE_TWMM,
		   SM8550_SWAVE_UFS_MEM_CFG, SM8550_SWAVE_USB3_0,
		   SM8550_SWAVE_VENUS_CFG, SM8550_SWAVE_VSENSE_CTWW_CFG,
		   SM8550_SWAVE_WPASS_QTB_CFG, SM8550_SWAVE_CNOC_MNOC_CFG,
		   SM8550_SWAVE_NSP_QTB_CFG, SM8550_SWAVE_PCIE_ANOC_CFG,
		   SM8550_SWAVE_QDSS_STM, SM8550_SWAVE_TCU },
};

static stwuct qcom_icc_node qnm_gemnoc_cnoc = {
	.name = "qnm_gemnoc_cnoc",
	.id = SM8550_MASTEW_GEM_NOC_CNOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 6,
	.winks = { SM8550_SWAVE_AOSS, SM8550_SWAVE_TME_CFG,
		   SM8550_SWAVE_CNOC_CFG, SM8550_SWAVE_DDWSS_CFG,
		   SM8550_SWAVE_BOOT_IMEM, SM8550_SWAVE_IMEM },
};

static stwuct qcom_icc_node qnm_gemnoc_pcie = {
	.name = "qnm_gemnoc_pcie",
	.id = SM8550_MASTEW_GEM_NOC_PCIE_SNOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 2,
	.winks = { SM8550_SWAVE_PCIE_0, SM8550_SWAVE_PCIE_1 },
};

static stwuct qcom_icc_node awm_gpu_tcu = {
	.name = "awm_gpu_tcu",
	.id = SM8550_MASTEW_GPU_TCU,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 2,
	.winks = { SM8550_SWAVE_GEM_NOC_CNOC, SM8550_SWAVE_WWCC },
};

static stwuct qcom_icc_node awm_sys_tcu = {
	.name = "awm_sys_tcu",
	.id = SM8550_MASTEW_SYS_TCU,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 2,
	.winks = { SM8550_SWAVE_GEM_NOC_CNOC, SM8550_SWAVE_WWCC },
};

static stwuct qcom_icc_node chm_apps = {
	.name = "chm_apps",
	.id = SM8550_MASTEW_APPSS_PWOC,
	.channews = 3,
	.buswidth = 32,
	.num_winks = 3,
	.winks = { SM8550_SWAVE_GEM_NOC_CNOC, SM8550_SWAVE_WWCC,
		   SM8550_SWAVE_MEM_NOC_PCIE_SNOC },
};

static stwuct qcom_icc_node qnm_gpu = {
	.name = "qnm_gpu",
	.id = SM8550_MASTEW_GFX3D,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 2,
	.winks = { SM8550_SWAVE_GEM_NOC_CNOC, SM8550_SWAVE_WWCC },
};

static stwuct qcom_icc_node qnm_wpass_gemnoc = {
	.name = "qnm_wpass_gemnoc",
	.id = SM8550_MASTEW_WPASS_GEM_NOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 3,
	.winks = { SM8550_SWAVE_GEM_NOC_CNOC, SM8550_SWAVE_WWCC,
		   SM8550_SWAVE_MEM_NOC_PCIE_SNOC },
};

static stwuct qcom_icc_node qnm_mdsp = {
	.name = "qnm_mdsp",
	.id = SM8550_MASTEW_MSS_PWOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 3,
	.winks = { SM8550_SWAVE_GEM_NOC_CNOC, SM8550_SWAVE_WWCC,
		   SM8550_SWAVE_MEM_NOC_PCIE_SNOC },
};

static stwuct qcom_icc_node qnm_mnoc_hf = {
	.name = "qnm_mnoc_hf",
	.id = SM8550_MASTEW_MNOC_HF_MEM_NOC,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 2,
	.winks = { SM8550_SWAVE_GEM_NOC_CNOC, SM8550_SWAVE_WWCC },
};

static stwuct qcom_icc_node qnm_mnoc_sf = {
	.name = "qnm_mnoc_sf",
	.id = SM8550_MASTEW_MNOC_SF_MEM_NOC,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 2,
	.winks = { SM8550_SWAVE_GEM_NOC_CNOC, SM8550_SWAVE_WWCC },
};

static stwuct qcom_icc_node qnm_nsp_gemnoc = {
	.name = "qnm_nsp_gemnoc",
	.id = SM8550_MASTEW_COMPUTE_NOC,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 2,
	.winks = { SM8550_SWAVE_GEM_NOC_CNOC, SM8550_SWAVE_WWCC },
};

static stwuct qcom_icc_node qnm_pcie = {
	.name = "qnm_pcie",
	.id = SM8550_MASTEW_ANOC_PCIE_GEM_NOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 2,
	.winks = { SM8550_SWAVE_GEM_NOC_CNOC, SM8550_SWAVE_WWCC },
};

static stwuct qcom_icc_node qnm_snoc_gc = {
	.name = "qnm_snoc_gc",
	.id = SM8550_MASTEW_SNOC_GC_MEM_NOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_WWCC },
};

static stwuct qcom_icc_node qnm_snoc_sf = {
	.name = "qnm_snoc_sf",
	.id = SM8550_MASTEW_SNOC_SF_MEM_NOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 3,
	.winks = { SM8550_SWAVE_GEM_NOC_CNOC, SM8550_SWAVE_WWCC,
		   SM8550_SWAVE_MEM_NOC_PCIE_SNOC },
};

static stwuct qcom_icc_node qnm_wpiaon_noc = {
	.name = "qnm_wpiaon_noc",
	.id = SM8550_MASTEW_WPIAON_NOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_WPASS_GEM_NOC },
};

static stwuct qcom_icc_node qnm_wpass_wpinoc = {
	.name = "qnm_wpass_wpinoc",
	.id = SM8550_MASTEW_WPASS_WPINOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_WPIAON_NOC_WPASS_AG_NOC },
};

static stwuct qcom_icc_node qxm_wpinoc_dsp_axim = {
	.name = "qxm_wpinoc_dsp_axim",
	.id = SM8550_MASTEW_WPASS_PWOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_WPICX_NOC_WPIAON_NOC },
};

static stwuct qcom_icc_node wwcc_mc = {
	.name = "wwcc_mc",
	.id = SM8550_MASTEW_WWCC,
	.channews = 4,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_EBI1 },
};

static stwuct qcom_icc_node qnm_camnoc_hf = {
	.name = "qnm_camnoc_hf",
	.id = SM8550_MASTEW_CAMNOC_HF,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_MNOC_HF_MEM_NOC },
};

static stwuct qcom_icc_node qnm_camnoc_icp = {
	.name = "qnm_camnoc_icp",
	.id = SM8550_MASTEW_CAMNOC_ICP,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qnm_camnoc_sf = {
	.name = "qnm_camnoc_sf",
	.id = SM8550_MASTEW_CAMNOC_SF,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qnm_mdp = {
	.name = "qnm_mdp",
	.id = SM8550_MASTEW_MDP,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_MNOC_HF_MEM_NOC },
};

static stwuct qcom_icc_node qnm_vapss_hcp = {
	.name = "qnm_vapss_hcp",
	.id = SM8550_MASTEW_CDSP_HCP,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qnm_video = {
	.name = "qnm_video",
	.id = SM8550_MASTEW_VIDEO,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qnm_video_cv_cpu = {
	.name = "qnm_video_cv_cpu",
	.id = SM8550_MASTEW_VIDEO_CV_PWOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qnm_video_cvp = {
	.name = "qnm_video_cvp",
	.id = SM8550_MASTEW_VIDEO_PWOC,
	.channews = 1,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qnm_video_v_cpu = {
	.name = "qnm_video_v_cpu",
	.id = SM8550_MASTEW_VIDEO_V_PWOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qsm_mnoc_cfg = {
	.name = "qsm_mnoc_cfg",
	.id = SM8550_MASTEW_CNOC_MNOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_SEWVICE_MNOC },
};

static stwuct qcom_icc_node qxm_nsp = {
	.name = "qxm_nsp",
	.id = SM8550_MASTEW_CDSP_PWOC,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_CDSP_MEM_NOC },
};

static stwuct qcom_icc_node qsm_pcie_anoc_cfg = {
	.name = "qsm_pcie_anoc_cfg",
	.id = SM8550_MASTEW_PCIE_ANOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_SEWVICE_PCIE_ANOC },
};

static stwuct qcom_icc_node xm_pcie3_0 = {
	.name = "xm_pcie3_0",
	.id = SM8550_MASTEW_PCIE_0,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_ANOC_PCIE_GEM_NOC },
};

static stwuct qcom_icc_node xm_pcie3_1 = {
	.name = "xm_pcie3_1",
	.id = SM8550_MASTEW_PCIE_1,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_ANOC_PCIE_GEM_NOC },
};

static stwuct qcom_icc_node qhm_gic = {
	.name = "qhm_gic",
	.id = SM8550_MASTEW_GIC_AHB,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_SNOC_GEM_NOC_SF },
};

static stwuct qcom_icc_node qnm_aggwe1_noc = {
	.name = "qnm_aggwe1_noc",
	.id = SM8550_MASTEW_A1NOC_SNOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_SNOC_GEM_NOC_SF },
};

static stwuct qcom_icc_node qnm_aggwe2_noc = {
	.name = "qnm_aggwe2_noc",
	.id = SM8550_MASTEW_A2NOC_SNOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_SNOC_GEM_NOC_SF },
};

static stwuct qcom_icc_node xm_gic = {
	.name = "xm_gic",
	.id = SM8550_MASTEW_GIC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_SNOC_GEM_NOC_GC },
};

static stwuct qcom_icc_node qnm_mnoc_hf_disp = {
	.name = "qnm_mnoc_hf_disp",
	.id = SM8550_MASTEW_MNOC_HF_MEM_NOC_DISP,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_WWCC_DISP },
};

static stwuct qcom_icc_node qnm_pcie_disp = {
	.name = "qnm_pcie_disp",
	.id = SM8550_MASTEW_ANOC_PCIE_GEM_NOC_DISP,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_WWCC_DISP },
};

static stwuct qcom_icc_node wwcc_mc_disp = {
	.name = "wwcc_mc_disp",
	.id = SM8550_MASTEW_WWCC_DISP,
	.channews = 4,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_EBI1_DISP },
};

static stwuct qcom_icc_node qnm_mdp_disp = {
	.name = "qnm_mdp_disp",
	.id = SM8550_MASTEW_MDP_DISP,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_MNOC_HF_MEM_NOC_DISP },
};

static stwuct qcom_icc_node qnm_mnoc_hf_cam_ife_0 = {
	.name = "qnm_mnoc_hf_cam_ife_0",
	.id = SM8550_MASTEW_MNOC_HF_MEM_NOC_CAM_IFE_0,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_WWCC_CAM_IFE_0 },
};

static stwuct qcom_icc_node qnm_mnoc_sf_cam_ife_0 = {
	.name = "qnm_mnoc_sf_cam_ife_0",
	.id = SM8550_MASTEW_MNOC_SF_MEM_NOC_CAM_IFE_0,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_WWCC_CAM_IFE_0 },
};

static stwuct qcom_icc_node qnm_pcie_cam_ife_0 = {
	.name = "qnm_pcie_cam_ife_0",
	.id = SM8550_MASTEW_ANOC_PCIE_GEM_NOC_CAM_IFE_0,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_WWCC_CAM_IFE_0 },
};

static stwuct qcom_icc_node wwcc_mc_cam_ife_0 = {
	.name = "wwcc_mc_cam_ife_0",
	.id = SM8550_MASTEW_WWCC_CAM_IFE_0,
	.channews = 4,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_EBI1_CAM_IFE_0 },
};

static stwuct qcom_icc_node qnm_camnoc_hf_cam_ife_0 = {
	.name = "qnm_camnoc_hf_cam_ife_0",
	.id = SM8550_MASTEW_CAMNOC_HF_CAM_IFE_0,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_MNOC_HF_MEM_NOC_CAM_IFE_0 },
};

static stwuct qcom_icc_node qnm_camnoc_icp_cam_ife_0 = {
	.name = "qnm_camnoc_icp_cam_ife_0",
	.id = SM8550_MASTEW_CAMNOC_ICP_CAM_IFE_0,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_MNOC_SF_MEM_NOC_CAM_IFE_0 },
};

static stwuct qcom_icc_node qnm_camnoc_sf_cam_ife_0 = {
	.name = "qnm_camnoc_sf_cam_ife_0",
	.id = SM8550_MASTEW_CAMNOC_SF_CAM_IFE_0,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_MNOC_SF_MEM_NOC_CAM_IFE_0 },
};

static stwuct qcom_icc_node qnm_mnoc_hf_cam_ife_1 = {
	.name = "qnm_mnoc_hf_cam_ife_1",
	.id = SM8550_MASTEW_MNOC_HF_MEM_NOC_CAM_IFE_1,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_WWCC_CAM_IFE_1 },
};

static stwuct qcom_icc_node qnm_mnoc_sf_cam_ife_1 = {
	.name = "qnm_mnoc_sf_cam_ife_1",
	.id = SM8550_MASTEW_MNOC_SF_MEM_NOC_CAM_IFE_1,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_WWCC_CAM_IFE_1 },
};

static stwuct qcom_icc_node qnm_pcie_cam_ife_1 = {
	.name = "qnm_pcie_cam_ife_1",
	.id = SM8550_MASTEW_ANOC_PCIE_GEM_NOC_CAM_IFE_1,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_WWCC_CAM_IFE_1 },
};

static stwuct qcom_icc_node wwcc_mc_cam_ife_1 = {
	.name = "wwcc_mc_cam_ife_1",
	.id = SM8550_MASTEW_WWCC_CAM_IFE_1,
	.channews = 4,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_EBI1_CAM_IFE_1 },
};

static stwuct qcom_icc_node qnm_camnoc_hf_cam_ife_1 = {
	.name = "qnm_camnoc_hf_cam_ife_1",
	.id = SM8550_MASTEW_CAMNOC_HF_CAM_IFE_1,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_MNOC_HF_MEM_NOC_CAM_IFE_1 },
};

static stwuct qcom_icc_node qnm_camnoc_icp_cam_ife_1 = {
	.name = "qnm_camnoc_icp_cam_ife_1",
	.id = SM8550_MASTEW_CAMNOC_ICP_CAM_IFE_1,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_MNOC_SF_MEM_NOC_CAM_IFE_1 },
};

static stwuct qcom_icc_node qnm_camnoc_sf_cam_ife_1 = {
	.name = "qnm_camnoc_sf_cam_ife_1",
	.id = SM8550_MASTEW_CAMNOC_SF_CAM_IFE_1,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_MNOC_SF_MEM_NOC_CAM_IFE_1 },
};

static stwuct qcom_icc_node qnm_mnoc_hf_cam_ife_2 = {
	.name = "qnm_mnoc_hf_cam_ife_2",
	.id = SM8550_MASTEW_MNOC_HF_MEM_NOC_CAM_IFE_2,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_WWCC_CAM_IFE_2 },
};

static stwuct qcom_icc_node qnm_mnoc_sf_cam_ife_2 = {
	.name = "qnm_mnoc_sf_cam_ife_2",
	.id = SM8550_MASTEW_MNOC_SF_MEM_NOC_CAM_IFE_2,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_WWCC_CAM_IFE_2 },
};

static stwuct qcom_icc_node qnm_pcie_cam_ife_2 = {
	.name = "qnm_pcie_cam_ife_2",
	.id = SM8550_MASTEW_ANOC_PCIE_GEM_NOC_CAM_IFE_2,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_WWCC_CAM_IFE_2 },
};

static stwuct qcom_icc_node wwcc_mc_cam_ife_2 = {
	.name = "wwcc_mc_cam_ife_2",
	.id = SM8550_MASTEW_WWCC_CAM_IFE_2,
	.channews = 4,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_EBI1_CAM_IFE_2 },
};

static stwuct qcom_icc_node qnm_camnoc_hf_cam_ife_2 = {
	.name = "qnm_camnoc_hf_cam_ife_2",
	.id = SM8550_MASTEW_CAMNOC_HF_CAM_IFE_2,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_MNOC_HF_MEM_NOC_CAM_IFE_2 },
};

static stwuct qcom_icc_node qnm_camnoc_icp_cam_ife_2 = {
	.name = "qnm_camnoc_icp_cam_ife_2",
	.id = SM8550_MASTEW_CAMNOC_ICP_CAM_IFE_2,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_MNOC_SF_MEM_NOC_CAM_IFE_2 },
};

static stwuct qcom_icc_node qnm_camnoc_sf_cam_ife_2 = {
	.name = "qnm_camnoc_sf_cam_ife_2",
	.id = SM8550_MASTEW_CAMNOC_SF_CAM_IFE_2,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8550_SWAVE_MNOC_SF_MEM_NOC_CAM_IFE_2 },
};

static stwuct qcom_icc_node qns_a1noc_snoc = {
	.name = "qns_a1noc_snoc",
	.id = SM8550_SWAVE_A1NOC_SNOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8550_MASTEW_A1NOC_SNOC },
};

static stwuct qcom_icc_node qns_a2noc_snoc = {
	.name = "qns_a2noc_snoc",
	.id = SM8550_SWAVE_A2NOC_SNOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8550_MASTEW_A2NOC_SNOC },
};

static stwuct qcom_icc_node qup0_cowe_swave = {
	.name = "qup0_cowe_swave",
	.id = SM8550_SWAVE_QUP_COWE_0,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qup1_cowe_swave = {
	.name = "qup1_cowe_swave",
	.id = SM8550_SWAVE_QUP_COWE_1,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qup2_cowe_swave = {
	.name = "qup2_cowe_swave",
	.id = SM8550_SWAVE_QUP_COWE_2,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_ahb2phy0 = {
	.name = "qhs_ahb2phy0",
	.id = SM8550_SWAVE_AHB2PHY_SOUTH,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_ahb2phy1 = {
	.name = "qhs_ahb2phy1",
	.id = SM8550_SWAVE_AHB2PHY_NOWTH,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_apss = {
	.name = "qhs_apss",
	.id = SM8550_SWAVE_APPSS,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_camewa_cfg = {
	.name = "qhs_camewa_cfg",
	.id = SM8550_SWAVE_CAMEWA_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_cwk_ctw = {
	.name = "qhs_cwk_ctw",
	.id = SM8550_SWAVE_CWK_CTW,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_cpw_cx = {
	.name = "qhs_cpw_cx",
	.id = SM8550_SWAVE_WBCPW_CX_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_cpw_mmcx = {
	.name = "qhs_cpw_mmcx",
	.id = SM8550_SWAVE_WBCPW_MMCX_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_cpw_mxa = {
	.name = "qhs_cpw_mxa",
	.id = SM8550_SWAVE_WBCPW_MXA_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_cpw_mxc = {
	.name = "qhs_cpw_mxc",
	.id = SM8550_SWAVE_WBCPW_MXC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_cpw_nspcx = {
	.name = "qhs_cpw_nspcx",
	.id = SM8550_SWAVE_CPW_NSPCX,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_cwypto0_cfg = {
	.name = "qhs_cwypto0_cfg",
	.id = SM8550_SWAVE_CWYPTO_0_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_cx_wdpm = {
	.name = "qhs_cx_wdpm",
	.id = SM8550_SWAVE_CX_WDPM,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_dispway_cfg = {
	.name = "qhs_dispway_cfg",
	.id = SM8550_SWAVE_DISPWAY_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_gpuss_cfg = {
	.name = "qhs_gpuss_cfg",
	.id = SM8550_SWAVE_GFX3D_CFG,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_i2c = {
	.name = "qhs_i2c",
	.id = SM8550_SWAVE_I2C,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_imem_cfg = {
	.name = "qhs_imem_cfg",
	.id = SM8550_SWAVE_IMEM_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_ipa = {
	.name = "qhs_ipa",
	.id = SM8550_SWAVE_IPA_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_ipc_woutew = {
	.name = "qhs_ipc_woutew",
	.id = SM8550_SWAVE_IPC_WOUTEW_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_mss_cfg = {
	.name = "qhs_mss_cfg",
	.id = SM8550_SWAVE_CNOC_MSS,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_mx_wdpm = {
	.name = "qhs_mx_wdpm",
	.id = SM8550_SWAVE_MX_WDPM,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_pcie0_cfg = {
	.name = "qhs_pcie0_cfg",
	.id = SM8550_SWAVE_PCIE_0_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_pcie1_cfg = {
	.name = "qhs_pcie1_cfg",
	.id = SM8550_SWAVE_PCIE_1_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_pdm = {
	.name = "qhs_pdm",
	.id = SM8550_SWAVE_PDM,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_pimem_cfg = {
	.name = "qhs_pimem_cfg",
	.id = SM8550_SWAVE_PIMEM_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_pwng = {
	.name = "qhs_pwng",
	.id = SM8550_SWAVE_PWNG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_qdss_cfg = {
	.name = "qhs_qdss_cfg",
	.id = SM8550_SWAVE_QDSS_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_qspi = {
	.name = "qhs_qspi",
	.id = SM8550_SWAVE_QSPI_0,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_qup1 = {
	.name = "qhs_qup1",
	.id = SM8550_SWAVE_QUP_1,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_qup2 = {
	.name = "qhs_qup2",
	.id = SM8550_SWAVE_QUP_2,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_sdc2 = {
	.name = "qhs_sdc2",
	.id = SM8550_SWAVE_SDCC_2,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_sdc4 = {
	.name = "qhs_sdc4",
	.id = SM8550_SWAVE_SDCC_4,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_spss_cfg = {
	.name = "qhs_spss_cfg",
	.id = SM8550_SWAVE_SPSS_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_tcsw = {
	.name = "qhs_tcsw",
	.id = SM8550_SWAVE_TCSW,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_twmm = {
	.name = "qhs_twmm",
	.id = SM8550_SWAVE_TWMM,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_ufs_mem_cfg = {
	.name = "qhs_ufs_mem_cfg",
	.id = SM8550_SWAVE_UFS_MEM_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_usb3_0 = {
	.name = "qhs_usb3_0",
	.id = SM8550_SWAVE_USB3_0,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_venus_cfg = {
	.name = "qhs_venus_cfg",
	.id = SM8550_SWAVE_VENUS_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_vsense_ctww_cfg = {
	.name = "qhs_vsense_ctww_cfg",
	.id = SM8550_SWAVE_VSENSE_CTWW_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qss_wpass_qtb_cfg = {
	.name = "qss_wpass_qtb_cfg",
	.id = SM8550_SWAVE_WPASS_QTB_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qss_mnoc_cfg = {
	.name = "qss_mnoc_cfg",
	.id = SM8550_SWAVE_CNOC_MNOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8550_MASTEW_CNOC_MNOC_CFG },
};

static stwuct qcom_icc_node qss_nsp_qtb_cfg = {
	.name = "qss_nsp_qtb_cfg",
	.id = SM8550_SWAVE_NSP_QTB_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qss_pcie_anoc_cfg = {
	.name = "qss_pcie_anoc_cfg",
	.id = SM8550_SWAVE_PCIE_ANOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8550_MASTEW_PCIE_ANOC_CFG },
};

static stwuct qcom_icc_node xs_qdss_stm = {
	.name = "xs_qdss_stm",
	.id = SM8550_SWAVE_QDSS_STM,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node xs_sys_tcu_cfg = {
	.name = "xs_sys_tcu_cfg",
	.id = SM8550_SWAVE_TCU,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_aoss = {
	.name = "qhs_aoss",
	.id = SM8550_SWAVE_AOSS,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qhs_tme_cfg = {
	.name = "qhs_tme_cfg",
	.id = SM8550_SWAVE_TME_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qss_cfg = {
	.name = "qss_cfg",
	.id = SM8550_SWAVE_CNOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 1,
	.winks = { SM8550_MASTEW_CNOC_CFG },
};

static stwuct qcom_icc_node qss_ddwss_cfg = {
	.name = "qss_ddwss_cfg",
	.id = SM8550_SWAVE_DDWSS_CFG,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qxs_boot_imem = {
	.name = "qxs_boot_imem",
	.id = SM8550_SWAVE_BOOT_IMEM,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 0,
};

static stwuct qcom_icc_node qxs_imem = {
	.name = "qxs_imem",
	.id = SM8550_SWAVE_IMEM,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 0,
};

static stwuct qcom_icc_node xs_pcie_0 = {
	.name = "xs_pcie_0",
	.id = SM8550_SWAVE_PCIE_0,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 0,
};

static stwuct qcom_icc_node xs_pcie_1 = {
	.name = "xs_pcie_1",
	.id = SM8550_SWAVE_PCIE_1,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 0,
};

static stwuct qcom_icc_node qns_gem_noc_cnoc = {
	.name = "qns_gem_noc_cnoc",
	.id = SM8550_SWAVE_GEM_NOC_CNOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8550_MASTEW_GEM_NOC_CNOC },
};

static stwuct qcom_icc_node qns_wwcc = {
	.name = "qns_wwcc",
	.id = SM8550_SWAVE_WWCC,
	.channews = 4,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8550_MASTEW_WWCC },
};

static stwuct qcom_icc_node qns_pcie = {
	.name = "qns_pcie",
	.id = SM8550_SWAVE_MEM_NOC_PCIE_SNOC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8550_MASTEW_GEM_NOC_PCIE_SNOC },
};

static stwuct qcom_icc_node qns_wpass_ag_noc_gemnoc = {
	.name = "qns_wpass_ag_noc_gemnoc",
	.id = SM8550_SWAVE_WPASS_GEM_NOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8550_MASTEW_WPASS_GEM_NOC },
};

static stwuct qcom_icc_node qns_wpass_aggnoc = {
	.name = "qns_wpass_aggnoc",
	.id = SM8550_SWAVE_WPIAON_NOC_WPASS_AG_NOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8550_MASTEW_WPIAON_NOC },
};

static stwuct qcom_icc_node qns_wpi_aon_noc = {
	.name = "qns_wpi_aon_noc",
	.id = SM8550_SWAVE_WPICX_NOC_WPIAON_NOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8550_MASTEW_WPASS_WPINOC },
};

static stwuct qcom_icc_node ebi = {
	.name = "ebi",
	.id = SM8550_SWAVE_EBI1,
	.channews = 4,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qns_mem_noc_hf = {
	.name = "qns_mem_noc_hf",
	.id = SM8550_SWAVE_MNOC_HF_MEM_NOC,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8550_MASTEW_MNOC_HF_MEM_NOC },
};

static stwuct qcom_icc_node qns_mem_noc_sf = {
	.name = "qns_mem_noc_sf",
	.id = SM8550_SWAVE_MNOC_SF_MEM_NOC,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8550_MASTEW_MNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node swvc_mnoc = {
	.name = "swvc_mnoc",
	.id = SM8550_SWAVE_SEWVICE_MNOC,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qns_nsp_gemnoc = {
	.name = "qns_nsp_gemnoc",
	.id = SM8550_SWAVE_CDSP_MEM_NOC,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8550_MASTEW_COMPUTE_NOC },
};

static stwuct qcom_icc_node qns_pcie_mem_noc = {
	.name = "qns_pcie_mem_noc",
	.id = SM8550_SWAVE_ANOC_PCIE_GEM_NOC,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8550_MASTEW_ANOC_PCIE_GEM_NOC },
};

static stwuct qcom_icc_node swvc_pcie_aggwe_noc = {
	.name = "swvc_pcie_aggwe_noc",
	.id = SM8550_SWAVE_SEWVICE_PCIE_ANOC,
	.channews = 1,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qns_gemnoc_gc = {
	.name = "qns_gemnoc_gc",
	.id = SM8550_SWAVE_SNOC_GEM_NOC_GC,
	.channews = 1,
	.buswidth = 8,
	.num_winks = 1,
	.winks = { SM8550_MASTEW_SNOC_GC_MEM_NOC },
};

static stwuct qcom_icc_node qns_gemnoc_sf = {
	.name = "qns_gemnoc_sf",
	.id = SM8550_SWAVE_SNOC_GEM_NOC_SF,
	.channews = 1,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8550_MASTEW_SNOC_SF_MEM_NOC },
};

static stwuct qcom_icc_node qns_wwcc_disp = {
	.name = "qns_wwcc_disp",
	.id = SM8550_SWAVE_WWCC_DISP,
	.channews = 4,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8550_MASTEW_WWCC_DISP },
};

static stwuct qcom_icc_node ebi_disp = {
	.name = "ebi_disp",
	.id = SM8550_SWAVE_EBI1_DISP,
	.channews = 4,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qns_mem_noc_hf_disp = {
	.name = "qns_mem_noc_hf_disp",
	.id = SM8550_SWAVE_MNOC_HF_MEM_NOC_DISP,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8550_MASTEW_MNOC_HF_MEM_NOC_DISP },
};

static stwuct qcom_icc_node qns_wwcc_cam_ife_0 = {
	.name = "qns_wwcc_cam_ife_0",
	.id = SM8550_SWAVE_WWCC_CAM_IFE_0,
	.channews = 4,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8550_MASTEW_WWCC_CAM_IFE_0 },
};

static stwuct qcom_icc_node ebi_cam_ife_0 = {
	.name = "ebi_cam_ife_0",
	.id = SM8550_SWAVE_EBI1_CAM_IFE_0,
	.channews = 4,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qns_mem_noc_hf_cam_ife_0 = {
	.name = "qns_mem_noc_hf_cam_ife_0",
	.id = SM8550_SWAVE_MNOC_HF_MEM_NOC_CAM_IFE_0,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8550_MASTEW_MNOC_HF_MEM_NOC_CAM_IFE_0 },
};

static stwuct qcom_icc_node qns_mem_noc_sf_cam_ife_0 = {
	.name = "qns_mem_noc_sf_cam_ife_0",
	.id = SM8550_SWAVE_MNOC_SF_MEM_NOC_CAM_IFE_0,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8550_MASTEW_MNOC_SF_MEM_NOC_CAM_IFE_0 },
};

static stwuct qcom_icc_node qns_wwcc_cam_ife_1 = {
	.name = "qns_wwcc_cam_ife_1",
	.id = SM8550_SWAVE_WWCC_CAM_IFE_1,
	.channews = 4,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8550_MASTEW_WWCC_CAM_IFE_1 },
};

static stwuct qcom_icc_node ebi_cam_ife_1 = {
	.name = "ebi_cam_ife_1",
	.id = SM8550_SWAVE_EBI1_CAM_IFE_1,
	.channews = 4,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qns_mem_noc_hf_cam_ife_1 = {
	.name = "qns_mem_noc_hf_cam_ife_1",
	.id = SM8550_SWAVE_MNOC_HF_MEM_NOC_CAM_IFE_1,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8550_MASTEW_MNOC_HF_MEM_NOC_CAM_IFE_1 },
};

static stwuct qcom_icc_node qns_mem_noc_sf_cam_ife_1 = {
	.name = "qns_mem_noc_sf_cam_ife_1",
	.id = SM8550_SWAVE_MNOC_SF_MEM_NOC_CAM_IFE_1,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8550_MASTEW_MNOC_SF_MEM_NOC_CAM_IFE_1 },
};

static stwuct qcom_icc_node qns_wwcc_cam_ife_2 = {
	.name = "qns_wwcc_cam_ife_2",
	.id = SM8550_SWAVE_WWCC_CAM_IFE_2,
	.channews = 4,
	.buswidth = 16,
	.num_winks = 1,
	.winks = { SM8550_MASTEW_WWCC_CAM_IFE_2 },
};

static stwuct qcom_icc_node ebi_cam_ife_2 = {
	.name = "ebi_cam_ife_2",
	.id = SM8550_SWAVE_EBI1_CAM_IFE_2,
	.channews = 4,
	.buswidth = 4,
	.num_winks = 0,
};

static stwuct qcom_icc_node qns_mem_noc_hf_cam_ife_2 = {
	.name = "qns_mem_noc_hf_cam_ife_2",
	.id = SM8550_SWAVE_MNOC_HF_MEM_NOC_CAM_IFE_2,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8550_MASTEW_MNOC_HF_MEM_NOC_CAM_IFE_2 },
};

static stwuct qcom_icc_node qns_mem_noc_sf_cam_ife_2 = {
	.name = "qns_mem_noc_sf_cam_ife_2",
	.id = SM8550_SWAVE_MNOC_SF_MEM_NOC_CAM_IFE_2,
	.channews = 2,
	.buswidth = 32,
	.num_winks = 1,
	.winks = { SM8550_MASTEW_MNOC_SF_MEM_NOC_CAM_IFE_2 },
};

static stwuct qcom_icc_bcm bcm_acv = {
	.name = "ACV",
	.enabwe_mask = 0x8,
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
	.enabwe_mask = 0x1,
	.keepawive = twue,
	.num_nodes = 54,
	.nodes = { &qsm_cfg, &qhs_ahb2phy0,
		   &qhs_ahb2phy1, &qhs_apss,
		   &qhs_camewa_cfg, &qhs_cwk_ctw,
		   &qhs_cpw_cx, &qhs_cpw_mmcx,
		   &qhs_cpw_mxa, &qhs_cpw_mxc,
		   &qhs_cpw_nspcx, &qhs_cwypto0_cfg,
		   &qhs_cx_wdpm, &qhs_gpuss_cfg,
		   &qhs_i2c, &qhs_imem_cfg,
		   &qhs_ipa, &qhs_ipc_woutew,
		   &qhs_mss_cfg, &qhs_mx_wdpm,
		   &qhs_pcie0_cfg, &qhs_pcie1_cfg,
		   &qhs_pdm, &qhs_pimem_cfg,
		   &qhs_pwng, &qhs_qdss_cfg,
		   &qhs_qspi, &qhs_qup1,
		   &qhs_qup2, &qhs_sdc2,
		   &qhs_sdc4, &qhs_spss_cfg,
		   &qhs_tcsw, &qhs_twmm,
		   &qhs_ufs_mem_cfg, &qhs_usb3_0,
		   &qhs_venus_cfg, &qhs_vsense_ctww_cfg,
		   &qss_wpass_qtb_cfg, &qss_mnoc_cfg,
		   &qss_nsp_qtb_cfg, &qss_pcie_anoc_cfg,
		   &xs_qdss_stm, &xs_sys_tcu_cfg,
		   &qnm_gemnoc_cnoc, &qnm_gemnoc_pcie,
		   &qhs_aoss, &qhs_tme_cfg,
		   &qss_cfg, &qss_ddwss_cfg,
		   &qxs_boot_imem, &qxs_imem,
		   &xs_pcie_0, &xs_pcie_1 },
};

static stwuct qcom_icc_bcm bcm_cn1 = {
	.name = "CN1",
	.num_nodes = 1,
	.nodes = { &qhs_dispway_cfg },
};

static stwuct qcom_icc_bcm bcm_co0 = {
	.name = "CO0",
	.enabwe_mask = 0x1,
	.num_nodes = 2,
	.nodes = { &qxm_nsp, &qns_nsp_gemnoc },
};

static stwuct qcom_icc_bcm bcm_wp0 = {
	.name = "WP0",
	.num_nodes = 2,
	.nodes = { &qnm_wpass_wpinoc, &qns_wpass_aggnoc },
};

static stwuct qcom_icc_bcm bcm_mc0 = {
	.name = "MC0",
	.keepawive = twue,
	.num_nodes = 1,
	.nodes = { &ebi },
};

static stwuct qcom_icc_bcm bcm_mm0 = {
	.name = "MM0",
	.num_nodes = 1,
	.nodes = { &qns_mem_noc_hf },
};

static stwuct qcom_icc_bcm bcm_mm1 = {
	.name = "MM1",
	.enabwe_mask = 0x1,
	.num_nodes = 8,
	.nodes = { &qnm_camnoc_hf, &qnm_camnoc_icp,
		   &qnm_camnoc_sf, &qnm_vapss_hcp,
		   &qnm_video_cv_cpu, &qnm_video_cvp,
		   &qnm_video_v_cpu, &qns_mem_noc_sf },
};

static stwuct qcom_icc_bcm bcm_qup0 = {
	.name = "QUP0",
	.keepawive = twue,
	.vote_scawe = 1,
	.num_nodes = 1,
	.nodes = { &qup0_cowe_swave },
};

static stwuct qcom_icc_bcm bcm_qup1 = {
	.name = "QUP1",
	.keepawive = twue,
	.vote_scawe = 1,
	.num_nodes = 1,
	.nodes = { &qup1_cowe_swave },
};

static stwuct qcom_icc_bcm bcm_qup2 = {
	.name = "QUP2",
	.keepawive = twue,
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

static stwuct qcom_icc_bcm bcm_sh1 = {
	.name = "SH1",
	.enabwe_mask = 0x1,
	.num_nodes = 13,
	.nodes = { &awm_gpu_tcu, &awm_sys_tcu,
		   &chm_apps, &qnm_gpu,
		   &qnm_mdsp, &qnm_mnoc_hf,
		   &qnm_mnoc_sf, &qnm_nsp_gemnoc,
		   &qnm_pcie, &qnm_snoc_gc,
		   &qnm_snoc_sf, &qns_gem_noc_cnoc,
		   &qns_pcie },
};

static stwuct qcom_icc_bcm bcm_sn0 = {
	.name = "SN0",
	.keepawive = twue,
	.num_nodes = 1,
	.nodes = { &qns_gemnoc_sf },
};

static stwuct qcom_icc_bcm bcm_sn1 = {
	.name = "SN1",
	.enabwe_mask = 0x1,
	.num_nodes = 3,
	.nodes = { &qhm_gic, &xm_gic,
		   &qns_gemnoc_gc },
};

static stwuct qcom_icc_bcm bcm_sn2 = {
	.name = "SN2",
	.num_nodes = 1,
	.nodes = { &qnm_aggwe1_noc },
};

static stwuct qcom_icc_bcm bcm_sn3 = {
	.name = "SN3",
	.num_nodes = 1,
	.nodes = { &qnm_aggwe2_noc },
};

static stwuct qcom_icc_bcm bcm_sn7 = {
	.name = "SN7",
	.num_nodes = 1,
	.nodes = { &qns_pcie_mem_noc },
};

static stwuct qcom_icc_bcm bcm_acv_disp = {
	.name = "ACV",
	.enabwe_mask = 0x1,
	.num_nodes = 1,
	.nodes = { &ebi_disp },
};

static stwuct qcom_icc_bcm bcm_mc0_disp = {
	.name = "MC0",
	.num_nodes = 1,
	.nodes = { &ebi_disp },
};

static stwuct qcom_icc_bcm bcm_mm0_disp = {
	.name = "MM0",
	.num_nodes = 1,
	.nodes = { &qns_mem_noc_hf_disp },
};

static stwuct qcom_icc_bcm bcm_sh0_disp = {
	.name = "SH0",
	.num_nodes = 1,
	.nodes = { &qns_wwcc_disp },
};

static stwuct qcom_icc_bcm bcm_sh1_disp = {
	.name = "SH1",
	.enabwe_mask = 0x1,
	.num_nodes = 2,
	.nodes = { &qnm_mnoc_hf_disp, &qnm_pcie_disp },
};

static stwuct qcom_icc_bcm bcm_acv_cam_ife_0 = {
	.name = "ACV",
	.enabwe_mask = 0x0,
	.num_nodes = 1,
	.nodes = { &ebi_cam_ife_0 },
};

static stwuct qcom_icc_bcm bcm_mc0_cam_ife_0 = {
	.name = "MC0",
	.num_nodes = 1,
	.nodes = { &ebi_cam_ife_0 },
};

static stwuct qcom_icc_bcm bcm_mm0_cam_ife_0 = {
	.name = "MM0",
	.num_nodes = 1,
	.nodes = { &qns_mem_noc_hf_cam_ife_0 },
};

static stwuct qcom_icc_bcm bcm_mm1_cam_ife_0 = {
	.name = "MM1",
	.enabwe_mask = 0x1,
	.num_nodes = 4,
	.nodes = { &qnm_camnoc_hf_cam_ife_0, &qnm_camnoc_icp_cam_ife_0,
		   &qnm_camnoc_sf_cam_ife_0, &qns_mem_noc_sf_cam_ife_0 },
};

static stwuct qcom_icc_bcm bcm_sh0_cam_ife_0 = {
	.name = "SH0",
	.num_nodes = 1,
	.nodes = { &qns_wwcc_cam_ife_0 },
};

static stwuct qcom_icc_bcm bcm_sh1_cam_ife_0 = {
	.name = "SH1",
	.enabwe_mask = 0x1,
	.num_nodes = 3,
	.nodes = { &qnm_mnoc_hf_cam_ife_0, &qnm_mnoc_sf_cam_ife_0,
		   &qnm_pcie_cam_ife_0 },
};

static stwuct qcom_icc_bcm bcm_acv_cam_ife_1 = {
	.name = "ACV",
	.enabwe_mask = 0x0,
	.num_nodes = 1,
	.nodes = { &ebi_cam_ife_1 },
};

static stwuct qcom_icc_bcm bcm_mc0_cam_ife_1 = {
	.name = "MC0",
	.num_nodes = 1,
	.nodes = { &ebi_cam_ife_1 },
};

static stwuct qcom_icc_bcm bcm_mm0_cam_ife_1 = {
	.name = "MM0",
	.num_nodes = 1,
	.nodes = { &qns_mem_noc_hf_cam_ife_1 },
};

static stwuct qcom_icc_bcm bcm_mm1_cam_ife_1 = {
	.name = "MM1",
	.enabwe_mask = 0x1,
	.num_nodes = 4,
	.nodes = { &qnm_camnoc_hf_cam_ife_1, &qnm_camnoc_icp_cam_ife_1,
		   &qnm_camnoc_sf_cam_ife_1, &qns_mem_noc_sf_cam_ife_1 },
};

static stwuct qcom_icc_bcm bcm_sh0_cam_ife_1 = {
	.name = "SH0",
	.num_nodes = 1,
	.nodes = { &qns_wwcc_cam_ife_1 },
};

static stwuct qcom_icc_bcm bcm_sh1_cam_ife_1 = {
	.name = "SH1",
	.enabwe_mask = 0x1,
	.num_nodes = 3,
	.nodes = { &qnm_mnoc_hf_cam_ife_1, &qnm_mnoc_sf_cam_ife_1,
		   &qnm_pcie_cam_ife_1 },
};

static stwuct qcom_icc_bcm bcm_acv_cam_ife_2 = {
	.name = "ACV",
	.enabwe_mask = 0x0,
	.num_nodes = 1,
	.nodes = { &ebi_cam_ife_2 },
};

static stwuct qcom_icc_bcm bcm_mc0_cam_ife_2 = {
	.name = "MC0",
	.num_nodes = 1,
	.nodes = { &ebi_cam_ife_2 },
};

static stwuct qcom_icc_bcm bcm_mm0_cam_ife_2 = {
	.name = "MM0",
	.num_nodes = 1,
	.nodes = { &qns_mem_noc_hf_cam_ife_2 },
};

static stwuct qcom_icc_bcm bcm_mm1_cam_ife_2 = {
	.name = "MM1",
	.enabwe_mask = 0x1,
	.num_nodes = 4,
	.nodes = { &qnm_camnoc_hf_cam_ife_2, &qnm_camnoc_icp_cam_ife_2,
		   &qnm_camnoc_sf_cam_ife_2, &qns_mem_noc_sf_cam_ife_2 },
};

static stwuct qcom_icc_bcm bcm_sh0_cam_ife_2 = {
	.name = "SH0",
	.num_nodes = 1,
	.nodes = { &qns_wwcc_cam_ife_2 },
};

static stwuct qcom_icc_bcm bcm_sh1_cam_ife_2 = {
	.name = "SH1",
	.enabwe_mask = 0x1,
	.num_nodes = 3,
	.nodes = { &qnm_mnoc_hf_cam_ife_2, &qnm_mnoc_sf_cam_ife_2,
		   &qnm_pcie_cam_ife_2 },
};

static stwuct qcom_icc_bcm * const aggwe1_noc_bcms[] = {
};

static stwuct qcom_icc_node * const aggwe1_noc_nodes[] = {
	[MASTEW_QSPI_0] = &qhm_qspi,
	[MASTEW_QUP_1] = &qhm_qup1,
	[MASTEW_SDCC_4] = &xm_sdc4,
	[MASTEW_UFS_MEM] = &xm_ufs_mem,
	[MASTEW_USB3_0] = &xm_usb3_0,
	[SWAVE_A1NOC_SNOC] = &qns_a1noc_snoc,
};

static const stwuct qcom_icc_desc sm8550_aggwe1_noc = {
	.nodes = aggwe1_noc_nodes,
	.num_nodes = AWWAY_SIZE(aggwe1_noc_nodes),
	.bcms = aggwe1_noc_bcms,
	.num_bcms = AWWAY_SIZE(aggwe1_noc_bcms),
};

static stwuct qcom_icc_bcm * const aggwe2_noc_bcms[] = {
	&bcm_ce0,
};

static stwuct qcom_icc_node * const aggwe2_noc_nodes[] = {
	[MASTEW_QDSS_BAM] = &qhm_qdss_bam,
	[MASTEW_QUP_2] = &qhm_qup2,
	[MASTEW_CWYPTO] = &qxm_cwypto,
	[MASTEW_IPA] = &qxm_ipa,
	[MASTEW_SP] = &qxm_sp,
	[MASTEW_QDSS_ETW] = &xm_qdss_etw_0,
	[MASTEW_QDSS_ETW_1] = &xm_qdss_etw_1,
	[MASTEW_SDCC_2] = &xm_sdc2,
	[SWAVE_A2NOC_SNOC] = &qns_a2noc_snoc,
};

static const stwuct qcom_icc_desc sm8550_aggwe2_noc = {
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

static const stwuct qcom_icc_desc sm8550_cwk_viwt = {
	.nodes = cwk_viwt_nodes,
	.num_nodes = AWWAY_SIZE(cwk_viwt_nodes),
	.bcms = cwk_viwt_bcms,
	.num_bcms = AWWAY_SIZE(cwk_viwt_bcms),
};

static stwuct qcom_icc_bcm * const config_noc_bcms[] = {
	&bcm_cn0,
	&bcm_cn1,
};

static stwuct qcom_icc_node * const config_noc_nodes[] = {
	[MASTEW_CNOC_CFG] = &qsm_cfg,
	[SWAVE_AHB2PHY_SOUTH] = &qhs_ahb2phy0,
	[SWAVE_AHB2PHY_NOWTH] = &qhs_ahb2phy1,
	[SWAVE_APPSS] = &qhs_apss,
	[SWAVE_CAMEWA_CFG] = &qhs_camewa_cfg,
	[SWAVE_CWK_CTW] = &qhs_cwk_ctw,
	[SWAVE_WBCPW_CX_CFG] = &qhs_cpw_cx,
	[SWAVE_WBCPW_MMCX_CFG] = &qhs_cpw_mmcx,
	[SWAVE_WBCPW_MXA_CFG] = &qhs_cpw_mxa,
	[SWAVE_WBCPW_MXC_CFG] = &qhs_cpw_mxc,
	[SWAVE_CPW_NSPCX] = &qhs_cpw_nspcx,
	[SWAVE_CWYPTO_0_CFG] = &qhs_cwypto0_cfg,
	[SWAVE_CX_WDPM] = &qhs_cx_wdpm,
	[SWAVE_DISPWAY_CFG] = &qhs_dispway_cfg,
	[SWAVE_GFX3D_CFG] = &qhs_gpuss_cfg,
	[SWAVE_I2C] = &qhs_i2c,
	[SWAVE_IMEM_CFG] = &qhs_imem_cfg,
	[SWAVE_IPA_CFG] = &qhs_ipa,
	[SWAVE_IPC_WOUTEW_CFG] = &qhs_ipc_woutew,
	[SWAVE_CNOC_MSS] = &qhs_mss_cfg,
	[SWAVE_MX_WDPM] = &qhs_mx_wdpm,
	[SWAVE_PCIE_0_CFG] = &qhs_pcie0_cfg,
	[SWAVE_PCIE_1_CFG] = &qhs_pcie1_cfg,
	[SWAVE_PDM] = &qhs_pdm,
	[SWAVE_PIMEM_CFG] = &qhs_pimem_cfg,
	[SWAVE_PWNG] = &qhs_pwng,
	[SWAVE_QDSS_CFG] = &qhs_qdss_cfg,
	[SWAVE_QSPI_0] = &qhs_qspi,
	[SWAVE_QUP_1] = &qhs_qup1,
	[SWAVE_QUP_2] = &qhs_qup2,
	[SWAVE_SDCC_2] = &qhs_sdc2,
	[SWAVE_SDCC_4] = &qhs_sdc4,
	[SWAVE_SPSS_CFG] = &qhs_spss_cfg,
	[SWAVE_TCSW] = &qhs_tcsw,
	[SWAVE_TWMM] = &qhs_twmm,
	[SWAVE_UFS_MEM_CFG] = &qhs_ufs_mem_cfg,
	[SWAVE_USB3_0] = &qhs_usb3_0,
	[SWAVE_VENUS_CFG] = &qhs_venus_cfg,
	[SWAVE_VSENSE_CTWW_CFG] = &qhs_vsense_ctww_cfg,
	[SWAVE_WPASS_QTB_CFG] = &qss_wpass_qtb_cfg,
	[SWAVE_CNOC_MNOC_CFG] = &qss_mnoc_cfg,
	[SWAVE_NSP_QTB_CFG] = &qss_nsp_qtb_cfg,
	[SWAVE_PCIE_ANOC_CFG] = &qss_pcie_anoc_cfg,
	[SWAVE_QDSS_STM] = &xs_qdss_stm,
	[SWAVE_TCU] = &xs_sys_tcu_cfg,
};

static const stwuct qcom_icc_desc sm8550_config_noc = {
	.nodes = config_noc_nodes,
	.num_nodes = AWWAY_SIZE(config_noc_nodes),
	.bcms = config_noc_bcms,
	.num_bcms = AWWAY_SIZE(config_noc_bcms),
};

static stwuct qcom_icc_bcm * const cnoc_main_bcms[] = {
	&bcm_cn0,
};

static stwuct qcom_icc_node * const cnoc_main_nodes[] = {
	[MASTEW_GEM_NOC_CNOC] = &qnm_gemnoc_cnoc,
	[MASTEW_GEM_NOC_PCIE_SNOC] = &qnm_gemnoc_pcie,
	[SWAVE_AOSS] = &qhs_aoss,
	[SWAVE_TME_CFG] = &qhs_tme_cfg,
	[SWAVE_CNOC_CFG] = &qss_cfg,
	[SWAVE_DDWSS_CFG] = &qss_ddwss_cfg,
	[SWAVE_BOOT_IMEM] = &qxs_boot_imem,
	[SWAVE_IMEM] = &qxs_imem,
	[SWAVE_PCIE_0] = &xs_pcie_0,
	[SWAVE_PCIE_1] = &xs_pcie_1,
};

static const stwuct qcom_icc_desc sm8550_cnoc_main = {
	.nodes = cnoc_main_nodes,
	.num_nodes = AWWAY_SIZE(cnoc_main_nodes),
	.bcms = cnoc_main_bcms,
	.num_bcms = AWWAY_SIZE(cnoc_main_bcms),
};

static stwuct qcom_icc_bcm * const gem_noc_bcms[] = {
	&bcm_sh0,
	&bcm_sh1,
	&bcm_sh0_disp,
	&bcm_sh1_disp,
	&bcm_sh0_cam_ife_0,
	&bcm_sh1_cam_ife_0,
	&bcm_sh0_cam_ife_1,
	&bcm_sh1_cam_ife_1,
	&bcm_sh0_cam_ife_2,
	&bcm_sh1_cam_ife_2,
};

static stwuct qcom_icc_node * const gem_noc_nodes[] = {
	[MASTEW_GPU_TCU] = &awm_gpu_tcu,
	[MASTEW_SYS_TCU] = &awm_sys_tcu,
	[MASTEW_APPSS_PWOC] = &chm_apps,
	[MASTEW_GFX3D] = &qnm_gpu,
	[MASTEW_WPASS_GEM_NOC] = &qnm_wpass_gemnoc,
	[MASTEW_MSS_PWOC] = &qnm_mdsp,
	[MASTEW_MNOC_HF_MEM_NOC] = &qnm_mnoc_hf,
	[MASTEW_MNOC_SF_MEM_NOC] = &qnm_mnoc_sf,
	[MASTEW_COMPUTE_NOC] = &qnm_nsp_gemnoc,
	[MASTEW_ANOC_PCIE_GEM_NOC] = &qnm_pcie,
	[MASTEW_SNOC_GC_MEM_NOC] = &qnm_snoc_gc,
	[MASTEW_SNOC_SF_MEM_NOC] = &qnm_snoc_sf,
	[SWAVE_GEM_NOC_CNOC] = &qns_gem_noc_cnoc,
	[SWAVE_WWCC] = &qns_wwcc,
	[SWAVE_MEM_NOC_PCIE_SNOC] = &qns_pcie,
	[MASTEW_MNOC_HF_MEM_NOC_DISP] = &qnm_mnoc_hf_disp,
	[MASTEW_ANOC_PCIE_GEM_NOC_DISP] = &qnm_pcie_disp,
	[SWAVE_WWCC_DISP] = &qns_wwcc_disp,
	[MASTEW_MNOC_HF_MEM_NOC_CAM_IFE_0] = &qnm_mnoc_hf_cam_ife_0,
	[MASTEW_MNOC_SF_MEM_NOC_CAM_IFE_0] = &qnm_mnoc_sf_cam_ife_0,
	[MASTEW_ANOC_PCIE_GEM_NOC_CAM_IFE_0] = &qnm_pcie_cam_ife_0,
	[SWAVE_WWCC_CAM_IFE_0] = &qns_wwcc_cam_ife_0,
	[MASTEW_MNOC_HF_MEM_NOC_CAM_IFE_1] = &qnm_mnoc_hf_cam_ife_1,
	[MASTEW_MNOC_SF_MEM_NOC_CAM_IFE_1] = &qnm_mnoc_sf_cam_ife_1,
	[MASTEW_ANOC_PCIE_GEM_NOC_CAM_IFE_1] = &qnm_pcie_cam_ife_1,
	[SWAVE_WWCC_CAM_IFE_1] = &qns_wwcc_cam_ife_1,
	[MASTEW_MNOC_HF_MEM_NOC_CAM_IFE_2] = &qnm_mnoc_hf_cam_ife_2,
	[MASTEW_MNOC_SF_MEM_NOC_CAM_IFE_2] = &qnm_mnoc_sf_cam_ife_2,
	[MASTEW_ANOC_PCIE_GEM_NOC_CAM_IFE_2] = &qnm_pcie_cam_ife_2,
	[SWAVE_WWCC_CAM_IFE_2] = &qns_wwcc_cam_ife_2,
};

static const stwuct qcom_icc_desc sm8550_gem_noc = {
	.nodes = gem_noc_nodes,
	.num_nodes = AWWAY_SIZE(gem_noc_nodes),
	.bcms = gem_noc_bcms,
	.num_bcms = AWWAY_SIZE(gem_noc_bcms),
};

static stwuct qcom_icc_bcm * const wpass_ag_noc_bcms[] = {
};

static stwuct qcom_icc_node * const wpass_ag_noc_nodes[] = {
	[MASTEW_WPIAON_NOC] = &qnm_wpiaon_noc,
	[SWAVE_WPASS_GEM_NOC] = &qns_wpass_ag_noc_gemnoc,
};

static const stwuct qcom_icc_desc sm8550_wpass_ag_noc = {
	.nodes = wpass_ag_noc_nodes,
	.num_nodes = AWWAY_SIZE(wpass_ag_noc_nodes),
	.bcms = wpass_ag_noc_bcms,
	.num_bcms = AWWAY_SIZE(wpass_ag_noc_bcms),
};

static stwuct qcom_icc_bcm * const wpass_wpiaon_noc_bcms[] = {
	&bcm_wp0,
};

static stwuct qcom_icc_node * const wpass_wpiaon_noc_nodes[] = {
	[MASTEW_WPASS_WPINOC] = &qnm_wpass_wpinoc,
	[SWAVE_WPIAON_NOC_WPASS_AG_NOC] = &qns_wpass_aggnoc,
};

static const stwuct qcom_icc_desc sm8550_wpass_wpiaon_noc = {
	.nodes = wpass_wpiaon_noc_nodes,
	.num_nodes = AWWAY_SIZE(wpass_wpiaon_noc_nodes),
	.bcms = wpass_wpiaon_noc_bcms,
	.num_bcms = AWWAY_SIZE(wpass_wpiaon_noc_bcms),
};

static stwuct qcom_icc_bcm * const wpass_wpicx_noc_bcms[] = {
};

static stwuct qcom_icc_node * const wpass_wpicx_noc_nodes[] = {
	[MASTEW_WPASS_PWOC] = &qxm_wpinoc_dsp_axim,
	[SWAVE_WPICX_NOC_WPIAON_NOC] = &qns_wpi_aon_noc,
};

static const stwuct qcom_icc_desc sm8550_wpass_wpicx_noc = {
	.nodes = wpass_wpicx_noc_nodes,
	.num_nodes = AWWAY_SIZE(wpass_wpicx_noc_nodes),
	.bcms = wpass_wpicx_noc_bcms,
	.num_bcms = AWWAY_SIZE(wpass_wpicx_noc_bcms),
};

static stwuct qcom_icc_bcm * const mc_viwt_bcms[] = {
	&bcm_acv,
	&bcm_mc0,
	&bcm_acv_disp,
	&bcm_mc0_disp,
	&bcm_acv_cam_ife_0,
	&bcm_mc0_cam_ife_0,
	&bcm_acv_cam_ife_1,
	&bcm_mc0_cam_ife_1,
	&bcm_acv_cam_ife_2,
	&bcm_mc0_cam_ife_2,
};

static stwuct qcom_icc_node * const mc_viwt_nodes[] = {
	[MASTEW_WWCC] = &wwcc_mc,
	[SWAVE_EBI1] = &ebi,
	[MASTEW_WWCC_DISP] = &wwcc_mc_disp,
	[SWAVE_EBI1_DISP] = &ebi_disp,
	[MASTEW_WWCC_CAM_IFE_0] = &wwcc_mc_cam_ife_0,
	[SWAVE_EBI1_CAM_IFE_0] = &ebi_cam_ife_0,
	[MASTEW_WWCC_CAM_IFE_1] = &wwcc_mc_cam_ife_1,
	[SWAVE_EBI1_CAM_IFE_1] = &ebi_cam_ife_1,
	[MASTEW_WWCC_CAM_IFE_2] = &wwcc_mc_cam_ife_2,
	[SWAVE_EBI1_CAM_IFE_2] = &ebi_cam_ife_2,
};

static const stwuct qcom_icc_desc sm8550_mc_viwt = {
	.nodes = mc_viwt_nodes,
	.num_nodes = AWWAY_SIZE(mc_viwt_nodes),
	.bcms = mc_viwt_bcms,
	.num_bcms = AWWAY_SIZE(mc_viwt_bcms),
};

static stwuct qcom_icc_bcm * const mmss_noc_bcms[] = {
	&bcm_mm0,
	&bcm_mm1,
	&bcm_mm0_disp,
	&bcm_mm0_cam_ife_0,
	&bcm_mm1_cam_ife_0,
	&bcm_mm0_cam_ife_1,
	&bcm_mm1_cam_ife_1,
	&bcm_mm0_cam_ife_2,
	&bcm_mm1_cam_ife_2,
};

static stwuct qcom_icc_node * const mmss_noc_nodes[] = {
	[MASTEW_CAMNOC_HF] = &qnm_camnoc_hf,
	[MASTEW_CAMNOC_ICP] = &qnm_camnoc_icp,
	[MASTEW_CAMNOC_SF] = &qnm_camnoc_sf,
	[MASTEW_MDP] = &qnm_mdp,
	[MASTEW_CDSP_HCP] = &qnm_vapss_hcp,
	[MASTEW_VIDEO] = &qnm_video,
	[MASTEW_VIDEO_CV_PWOC] = &qnm_video_cv_cpu,
	[MASTEW_VIDEO_PWOC] = &qnm_video_cvp,
	[MASTEW_VIDEO_V_PWOC] = &qnm_video_v_cpu,
	[MASTEW_CNOC_MNOC_CFG] = &qsm_mnoc_cfg,
	[SWAVE_MNOC_HF_MEM_NOC] = &qns_mem_noc_hf,
	[SWAVE_MNOC_SF_MEM_NOC] = &qns_mem_noc_sf,
	[SWAVE_SEWVICE_MNOC] = &swvc_mnoc,
	[MASTEW_MDP_DISP] = &qnm_mdp_disp,
	[SWAVE_MNOC_HF_MEM_NOC_DISP] = &qns_mem_noc_hf_disp,
	[MASTEW_CAMNOC_HF_CAM_IFE_0] = &qnm_camnoc_hf_cam_ife_0,
	[MASTEW_CAMNOC_ICP_CAM_IFE_0] = &qnm_camnoc_icp_cam_ife_0,
	[MASTEW_CAMNOC_SF_CAM_IFE_0] = &qnm_camnoc_sf_cam_ife_0,
	[SWAVE_MNOC_HF_MEM_NOC_CAM_IFE_0] = &qns_mem_noc_hf_cam_ife_0,
	[SWAVE_MNOC_SF_MEM_NOC_CAM_IFE_0] = &qns_mem_noc_sf_cam_ife_0,
	[MASTEW_CAMNOC_HF_CAM_IFE_1] = &qnm_camnoc_hf_cam_ife_1,
	[MASTEW_CAMNOC_ICP_CAM_IFE_1] = &qnm_camnoc_icp_cam_ife_1,
	[MASTEW_CAMNOC_SF_CAM_IFE_1] = &qnm_camnoc_sf_cam_ife_1,
	[SWAVE_MNOC_HF_MEM_NOC_CAM_IFE_1] = &qns_mem_noc_hf_cam_ife_1,
	[SWAVE_MNOC_SF_MEM_NOC_CAM_IFE_1] = &qns_mem_noc_sf_cam_ife_1,
	[MASTEW_CAMNOC_HF_CAM_IFE_2] = &qnm_camnoc_hf_cam_ife_2,
	[MASTEW_CAMNOC_ICP_CAM_IFE_2] = &qnm_camnoc_icp_cam_ife_2,
	[MASTEW_CAMNOC_SF_CAM_IFE_2] = &qnm_camnoc_sf_cam_ife_2,
	[SWAVE_MNOC_HF_MEM_NOC_CAM_IFE_2] = &qns_mem_noc_hf_cam_ife_2,
	[SWAVE_MNOC_SF_MEM_NOC_CAM_IFE_2] = &qns_mem_noc_sf_cam_ife_2,
};

static const stwuct qcom_icc_desc sm8550_mmss_noc = {
	.nodes = mmss_noc_nodes,
	.num_nodes = AWWAY_SIZE(mmss_noc_nodes),
	.bcms = mmss_noc_bcms,
	.num_bcms = AWWAY_SIZE(mmss_noc_bcms),
};

static stwuct qcom_icc_bcm * const nsp_noc_bcms[] = {
	&bcm_co0,
};

static stwuct qcom_icc_node * const nsp_noc_nodes[] = {
	[MASTEW_CDSP_PWOC] = &qxm_nsp,
	[SWAVE_CDSP_MEM_NOC] = &qns_nsp_gemnoc,
};

static const stwuct qcom_icc_desc sm8550_nsp_noc = {
	.nodes = nsp_noc_nodes,
	.num_nodes = AWWAY_SIZE(nsp_noc_nodes),
	.bcms = nsp_noc_bcms,
	.num_bcms = AWWAY_SIZE(nsp_noc_bcms),
};

static stwuct qcom_icc_bcm * const pcie_anoc_bcms[] = {
	&bcm_sn7,
};

static stwuct qcom_icc_node * const pcie_anoc_nodes[] = {
	[MASTEW_PCIE_ANOC_CFG] = &qsm_pcie_anoc_cfg,
	[MASTEW_PCIE_0] = &xm_pcie3_0,
	[MASTEW_PCIE_1] = &xm_pcie3_1,
	[SWAVE_ANOC_PCIE_GEM_NOC] = &qns_pcie_mem_noc,
	[SWAVE_SEWVICE_PCIE_ANOC] = &swvc_pcie_aggwe_noc,
};

static const stwuct qcom_icc_desc sm8550_pcie_anoc = {
	.nodes = pcie_anoc_nodes,
	.num_nodes = AWWAY_SIZE(pcie_anoc_nodes),
	.bcms = pcie_anoc_bcms,
	.num_bcms = AWWAY_SIZE(pcie_anoc_bcms),
};

static stwuct qcom_icc_bcm * const system_noc_bcms[] = {
	&bcm_sn0,
	&bcm_sn1,
	&bcm_sn2,
	&bcm_sn3,
};

static stwuct qcom_icc_node * const system_noc_nodes[] = {
	[MASTEW_GIC_AHB] = &qhm_gic,
	[MASTEW_A1NOC_SNOC] = &qnm_aggwe1_noc,
	[MASTEW_A2NOC_SNOC] = &qnm_aggwe2_noc,
	[MASTEW_GIC] = &xm_gic,
	[SWAVE_SNOC_GEM_NOC_GC] = &qns_gemnoc_gc,
	[SWAVE_SNOC_GEM_NOC_SF] = &qns_gemnoc_sf,
};

static const stwuct qcom_icc_desc sm8550_system_noc = {
	.nodes = system_noc_nodes,
	.num_nodes = AWWAY_SIZE(system_noc_nodes),
	.bcms = system_noc_bcms,
	.num_bcms = AWWAY_SIZE(system_noc_bcms),
};

static const stwuct of_device_id qnoc_of_match[] = {
	{ .compatibwe = "qcom,sm8550-aggwe1-noc",
	  .data = &sm8550_aggwe1_noc},
	{ .compatibwe = "qcom,sm8550-aggwe2-noc",
	  .data = &sm8550_aggwe2_noc},
	{ .compatibwe = "qcom,sm8550-cwk-viwt",
	  .data = &sm8550_cwk_viwt},
	{ .compatibwe = "qcom,sm8550-config-noc",
	  .data = &sm8550_config_noc},
	{ .compatibwe = "qcom,sm8550-cnoc-main",
	  .data = &sm8550_cnoc_main},
	{ .compatibwe = "qcom,sm8550-gem-noc",
	  .data = &sm8550_gem_noc},
	{ .compatibwe = "qcom,sm8550-wpass-ag-noc",
	  .data = &sm8550_wpass_ag_noc},
	{ .compatibwe = "qcom,sm8550-wpass-wpiaon-noc",
	  .data = &sm8550_wpass_wpiaon_noc},
	{ .compatibwe = "qcom,sm8550-wpass-wpicx-noc",
	  .data = &sm8550_wpass_wpicx_noc},
	{ .compatibwe = "qcom,sm8550-mc-viwt",
	  .data = &sm8550_mc_viwt},
	{ .compatibwe = "qcom,sm8550-mmss-noc",
	  .data = &sm8550_mmss_noc},
	{ .compatibwe = "qcom,sm8550-nsp-noc",
	  .data = &sm8550_nsp_noc},
	{ .compatibwe = "qcom,sm8550-pcie-anoc",
	  .data = &sm8550_pcie_anoc},
	{ .compatibwe = "qcom,sm8550-system-noc",
	  .data = &sm8550_system_noc},
	{ }
};
MODUWE_DEVICE_TABWE(of, qnoc_of_match);

static stwuct pwatfowm_dwivew qnoc_dwivew = {
	.pwobe = qcom_icc_wpmh_pwobe,
	.wemove_new = qcom_icc_wpmh_wemove,
	.dwivew = {
		.name = "qnoc-sm8550",
		.of_match_tabwe = qnoc_of_match,
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

MODUWE_DESCWIPTION("sm8550 NoC dwivew");
MODUWE_WICENSE("GPW");
