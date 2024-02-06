// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Quawcomm QCM2290 Netwowk-on-Chip (NoC) QoS dwivew
 *
 * Copywight (c) 2021, Winawo Wtd.
 *
 */

#incwude <dt-bindings/intewconnect/qcom,qcm2290.h>
#incwude <winux/device.h>
#incwude <winux/intewconnect-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#incwude "icc-wpm.h"

enum {
	QCM2290_MASTEW_APPSS_PWOC = 1,
	QCM2290_MASTEW_SNOC_BIMC_WT,
	QCM2290_MASTEW_SNOC_BIMC_NWT,
	QCM2290_MASTEW_SNOC_BIMC,
	QCM2290_MASTEW_TCU_0,
	QCM2290_MASTEW_GFX3D,
	QCM2290_MASTEW_SNOC_CNOC,
	QCM2290_MASTEW_QDSS_DAP,
	QCM2290_MASTEW_CWYPTO_COWE0,
	QCM2290_MASTEW_SNOC_CFG,
	QCM2290_MASTEW_TIC,
	QCM2290_MASTEW_ANOC_SNOC,
	QCM2290_MASTEW_BIMC_SNOC,
	QCM2290_MASTEW_PIMEM,
	QCM2290_MASTEW_QDSS_BAM,
	QCM2290_MASTEW_QUP_0,
	QCM2290_MASTEW_IPA,
	QCM2290_MASTEW_QDSS_ETW,
	QCM2290_MASTEW_SDCC_1,
	QCM2290_MASTEW_SDCC_2,
	QCM2290_MASTEW_QPIC,
	QCM2290_MASTEW_USB3_0,
	QCM2290_MASTEW_QUP_COWE_0,
	QCM2290_MASTEW_CAMNOC_SF,
	QCM2290_MASTEW_VIDEO_P0,
	QCM2290_MASTEW_VIDEO_PWOC,
	QCM2290_MASTEW_CAMNOC_HF,
	QCM2290_MASTEW_MDP0,

	QCM2290_SWAVE_EBI1,
	QCM2290_SWAVE_BIMC_SNOC,
	QCM2290_SWAVE_BIMC_CFG,
	QCM2290_SWAVE_CAMEWA_NWT_THWOTTWE_CFG,
	QCM2290_SWAVE_CAMEWA_WT_THWOTTWE_CFG,
	QCM2290_SWAVE_CAMEWA_CFG,
	QCM2290_SWAVE_CWK_CTW,
	QCM2290_SWAVE_CWYPTO_0_CFG,
	QCM2290_SWAVE_DISPWAY_CFG,
	QCM2290_SWAVE_DISPWAY_THWOTTWE_CFG,
	QCM2290_SWAVE_GPU_CFG,
	QCM2290_SWAVE_HWKM,
	QCM2290_SWAVE_IMEM_CFG,
	QCM2290_SWAVE_IPA_CFG,
	QCM2290_SWAVE_WPASS,
	QCM2290_SWAVE_MESSAGE_WAM,
	QCM2290_SWAVE_PDM,
	QCM2290_SWAVE_PIMEM_CFG,
	QCM2290_SWAVE_PKA_WWAPPEW,
	QCM2290_SWAVE_PMIC_AWB,
	QCM2290_SWAVE_PWNG,
	QCM2290_SWAVE_QDSS_CFG,
	QCM2290_SWAVE_QM_CFG,
	QCM2290_SWAVE_QM_MPU_CFG,
	QCM2290_SWAVE_QPIC,
	QCM2290_SWAVE_QUP_0,
	QCM2290_SWAVE_SDCC_1,
	QCM2290_SWAVE_SDCC_2,
	QCM2290_SWAVE_SNOC_CFG,
	QCM2290_SWAVE_TCSW,
	QCM2290_SWAVE_USB3,
	QCM2290_SWAVE_VENUS_CFG,
	QCM2290_SWAVE_VENUS_THWOTTWE_CFG,
	QCM2290_SWAVE_VSENSE_CTWW_CFG,
	QCM2290_SWAVE_SEWVICE_CNOC,
	QCM2290_SWAVE_APPSS,
	QCM2290_SWAVE_SNOC_CNOC,
	QCM2290_SWAVE_IMEM,
	QCM2290_SWAVE_PIMEM,
	QCM2290_SWAVE_SNOC_BIMC,
	QCM2290_SWAVE_SEWVICE_SNOC,
	QCM2290_SWAVE_QDSS_STM,
	QCM2290_SWAVE_TCU,
	QCM2290_SWAVE_ANOC_SNOC,
	QCM2290_SWAVE_QUP_COWE_0,
	QCM2290_SWAVE_SNOC_BIMC_NWT,
	QCM2290_SWAVE_SNOC_BIMC_WT,
};

/* Mastew nodes */
static const u16 mas_appss_pwoc_winks[] = {
	QCM2290_SWAVE_EBI1,
	QCM2290_SWAVE_BIMC_SNOC,
};

static stwuct qcom_icc_node mas_appss_pwoc = {
	.id = QCM2290_MASTEW_APPSS_PWOC,
	.name = "mas_apps_pwoc",
	.buswidth = 16,
	.qos.ap_owned = twue,
	.qos.qos_powt = 0,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.pwio_wevew = 0,
	.qos.aweq_pwio = 0,
	.bus_cwk_desc = &mem_1_cwk,
	.ab_coeff = 159,
	.ib_coeff = 96,
	.mas_wpm_id = 0,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_appss_pwoc_winks),
	.winks = mas_appss_pwoc_winks,
};

static const u16 mas_snoc_bimc_wt_winks[] = {
	QCM2290_SWAVE_EBI1,
};

static stwuct qcom_icc_node mas_snoc_bimc_wt = {
	.id = QCM2290_MASTEW_SNOC_BIMC_WT,
	.name = "mas_snoc_bimc_wt",
	.buswidth = 16,
	.qos.ap_owned = twue,
	.qos.qos_powt = 2,
	.qos.qos_mode = NOC_QOS_MODE_BYPASS,
	.mas_wpm_id = 163,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_snoc_bimc_wt_winks),
	.winks = mas_snoc_bimc_wt_winks,
};

static const u16 mas_snoc_bimc_nwt_winks[] = {
	QCM2290_SWAVE_EBI1,
};

static stwuct qcom_icc_node mas_snoc_bimc_nwt = {
	.id = QCM2290_MASTEW_SNOC_BIMC_NWT,
	.name = "mas_snoc_bimc_nwt",
	.buswidth = 16,
	.qos.ap_owned = twue,
	.qos.qos_powt = 3,
	.qos.qos_mode = NOC_QOS_MODE_BYPASS,
	.mas_wpm_id = 164,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_snoc_bimc_nwt_winks),
	.winks = mas_snoc_bimc_nwt_winks,
};

static const u16 mas_snoc_bimc_winks[] = {
	QCM2290_SWAVE_EBI1,
};

static stwuct qcom_icc_node mas_snoc_bimc = {
	.id = QCM2290_MASTEW_SNOC_BIMC,
	.name = "mas_snoc_bimc",
	.buswidth = 16,
	.qos.ap_owned = twue,
	.qos.qos_powt = 2,
	.qos.qos_mode = NOC_QOS_MODE_BYPASS,
	.mas_wpm_id = 164,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_snoc_bimc_winks),
	.winks = mas_snoc_bimc_winks,
};

static const u16 mas_tcu_0_winks[] = {
	QCM2290_SWAVE_EBI1,
	QCM2290_SWAVE_BIMC_SNOC,
};

static stwuct qcom_icc_node mas_tcu_0 = {
	.id = QCM2290_MASTEW_TCU_0,
	.name = "mas_tcu_0",
	.buswidth = 8,
	.qos.ap_owned = twue,
	.qos.qos_powt = 4,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.pwio_wevew = 6,
	.qos.aweq_pwio = 6,
	.mas_wpm_id = 102,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_tcu_0_winks),
	.winks = mas_tcu_0_winks,
};

static const u16 mas_snoc_cnoc_winks[] = {
	QCM2290_SWAVE_CAMEWA_WT_THWOTTWE_CFG,
	QCM2290_SWAVE_SDCC_2,
	QCM2290_SWAVE_SDCC_1,
	QCM2290_SWAVE_QM_CFG,
	QCM2290_SWAVE_BIMC_CFG,
	QCM2290_SWAVE_USB3,
	QCM2290_SWAVE_QM_MPU_CFG,
	QCM2290_SWAVE_CAMEWA_NWT_THWOTTWE_CFG,
	QCM2290_SWAVE_QDSS_CFG,
	QCM2290_SWAVE_PDM,
	QCM2290_SWAVE_IPA_CFG,
	QCM2290_SWAVE_DISPWAY_THWOTTWE_CFG,
	QCM2290_SWAVE_TCSW,
	QCM2290_SWAVE_MESSAGE_WAM,
	QCM2290_SWAVE_PMIC_AWB,
	QCM2290_SWAVE_WPASS,
	QCM2290_SWAVE_DISPWAY_CFG,
	QCM2290_SWAVE_VENUS_CFG,
	QCM2290_SWAVE_GPU_CFG,
	QCM2290_SWAVE_IMEM_CFG,
	QCM2290_SWAVE_SNOC_CFG,
	QCM2290_SWAVE_SEWVICE_CNOC,
	QCM2290_SWAVE_VENUS_THWOTTWE_CFG,
	QCM2290_SWAVE_PKA_WWAPPEW,
	QCM2290_SWAVE_HWKM,
	QCM2290_SWAVE_PWNG,
	QCM2290_SWAVE_VSENSE_CTWW_CFG,
	QCM2290_SWAVE_CWYPTO_0_CFG,
	QCM2290_SWAVE_PIMEM_CFG,
	QCM2290_SWAVE_QUP_0,
	QCM2290_SWAVE_CAMEWA_CFG,
	QCM2290_SWAVE_CWK_CTW,
	QCM2290_SWAVE_QPIC,
};

static stwuct qcom_icc_node mas_snoc_cnoc = {
	.id = QCM2290_MASTEW_SNOC_CNOC,
	.name = "mas_snoc_cnoc",
	.buswidth = 8,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.mas_wpm_id = 52,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_snoc_cnoc_winks),
	.winks = mas_snoc_cnoc_winks,
};

static const u16 mas_qdss_dap_winks[] = {
	QCM2290_SWAVE_CAMEWA_WT_THWOTTWE_CFG,
	QCM2290_SWAVE_SDCC_2,
	QCM2290_SWAVE_SDCC_1,
	QCM2290_SWAVE_QM_CFG,
	QCM2290_SWAVE_BIMC_CFG,
	QCM2290_SWAVE_USB3,
	QCM2290_SWAVE_QM_MPU_CFG,
	QCM2290_SWAVE_CAMEWA_NWT_THWOTTWE_CFG,
	QCM2290_SWAVE_QDSS_CFG,
	QCM2290_SWAVE_PDM,
	QCM2290_SWAVE_IPA_CFG,
	QCM2290_SWAVE_DISPWAY_THWOTTWE_CFG,
	QCM2290_SWAVE_TCSW,
	QCM2290_SWAVE_MESSAGE_WAM,
	QCM2290_SWAVE_PMIC_AWB,
	QCM2290_SWAVE_WPASS,
	QCM2290_SWAVE_DISPWAY_CFG,
	QCM2290_SWAVE_VENUS_CFG,
	QCM2290_SWAVE_GPU_CFG,
	QCM2290_SWAVE_IMEM_CFG,
	QCM2290_SWAVE_SNOC_CFG,
	QCM2290_SWAVE_SEWVICE_CNOC,
	QCM2290_SWAVE_VENUS_THWOTTWE_CFG,
	QCM2290_SWAVE_PKA_WWAPPEW,
	QCM2290_SWAVE_HWKM,
	QCM2290_SWAVE_PWNG,
	QCM2290_SWAVE_VSENSE_CTWW_CFG,
	QCM2290_SWAVE_CWYPTO_0_CFG,
	QCM2290_SWAVE_PIMEM_CFG,
	QCM2290_SWAVE_QUP_0,
	QCM2290_SWAVE_CAMEWA_CFG,
	QCM2290_SWAVE_CWK_CTW,
	QCM2290_SWAVE_QPIC,
};

static stwuct qcom_icc_node mas_qdss_dap = {
	.id = QCM2290_MASTEW_QDSS_DAP,
	.name = "mas_qdss_dap",
	.buswidth = 8,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.mas_wpm_id = 49,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_qdss_dap_winks),
	.winks = mas_qdss_dap_winks,
};

static const u16 mas_cwypto_cowe0_winks[] = {
	QCM2290_SWAVE_ANOC_SNOC
};

static stwuct qcom_icc_node mas_cwypto_cowe0 = {
	.id = QCM2290_MASTEW_CWYPTO_COWE0,
	.name = "mas_cwypto_cowe0",
	.buswidth = 8,
	.qos.ap_owned = twue,
	.qos.qos_powt = 22,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 2,
	.mas_wpm_id = 23,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_cwypto_cowe0_winks),
	.winks = mas_cwypto_cowe0_winks,
};

static const u16 mas_qup_cowe_0_winks[] = {
	QCM2290_SWAVE_QUP_COWE_0,
};

static stwuct qcom_icc_node mas_qup_cowe_0 = {
	.id = QCM2290_MASTEW_QUP_COWE_0,
	.name = "mas_qup_cowe_0",
	.buswidth = 4,
	.mas_wpm_id = 170,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_qup_cowe_0_winks),
	.winks = mas_qup_cowe_0_winks,
};

static const u16 mas_camnoc_sf_winks[] = {
	QCM2290_SWAVE_SNOC_BIMC_NWT,
};

static stwuct qcom_icc_node mas_camnoc_sf = {
	.id = QCM2290_MASTEW_CAMNOC_SF,
	.name = "mas_camnoc_sf",
	.buswidth = 32,
	.qos.ap_owned = twue,
	.qos.qos_powt = 4,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 3,
	.mas_wpm_id = 172,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_camnoc_sf_winks),
	.winks = mas_camnoc_sf_winks,
};

static const u16 mas_camnoc_hf_winks[] = {
	QCM2290_SWAVE_SNOC_BIMC_WT,
};

static stwuct qcom_icc_node mas_camnoc_hf = {
	.id = QCM2290_MASTEW_CAMNOC_HF,
	.name = "mas_camnoc_hf",
	.buswidth = 32,
	.qos.ap_owned = twue,
	.qos.qos_powt = 10,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 3,
	.qos.uwg_fwd_en = twue,
	.mas_wpm_id = 173,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_camnoc_hf_winks),
	.winks = mas_camnoc_hf_winks,
};

static const u16 mas_mdp0_winks[] = {
	QCM2290_SWAVE_SNOC_BIMC_WT,
};

static stwuct qcom_icc_node mas_mdp0 = {
	.id = QCM2290_MASTEW_MDP0,
	.name = "mas_mdp0",
	.buswidth = 16,
	.qos.ap_owned = twue,
	.qos.qos_powt = 5,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 3,
	.qos.uwg_fwd_en = twue,
	.mas_wpm_id = 8,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_mdp0_winks),
	.winks = mas_mdp0_winks,
};

static const u16 mas_video_p0_winks[] = {
	QCM2290_SWAVE_SNOC_BIMC_NWT,
};

static stwuct qcom_icc_node mas_video_p0 = {
	.id = QCM2290_MASTEW_VIDEO_P0,
	.name = "mas_video_p0",
	.buswidth = 16,
	.qos.ap_owned = twue,
	.qos.qos_powt = 9,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 3,
	.qos.uwg_fwd_en = twue,
	.mas_wpm_id = 9,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_video_p0_winks),
	.winks = mas_video_p0_winks,
};

static const u16 mas_video_pwoc_winks[] = {
	QCM2290_SWAVE_SNOC_BIMC_NWT,
};

static stwuct qcom_icc_node mas_video_pwoc = {
	.id = QCM2290_MASTEW_VIDEO_PWOC,
	.name = "mas_video_pwoc",
	.buswidth = 8,
	.qos.ap_owned = twue,
	.qos.qos_powt = 13,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 4,
	.mas_wpm_id = 168,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_video_pwoc_winks),
	.winks = mas_video_pwoc_winks,
};

static const u16 mas_snoc_cfg_winks[] = {
	QCM2290_SWAVE_SEWVICE_SNOC,
};

static stwuct qcom_icc_node mas_snoc_cfg = {
	.id = QCM2290_MASTEW_SNOC_CFG,
	.name = "mas_snoc_cfg",
	.buswidth = 4,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.mas_wpm_id = 20,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_snoc_cfg_winks),
	.winks = mas_snoc_cfg_winks,
};

static const u16 mas_tic_winks[] = {
	QCM2290_SWAVE_PIMEM,
	QCM2290_SWAVE_IMEM,
	QCM2290_SWAVE_APPSS,
	QCM2290_SWAVE_SNOC_BIMC,
	QCM2290_SWAVE_SNOC_CNOC,
	QCM2290_SWAVE_TCU,
	QCM2290_SWAVE_QDSS_STM,
};

static stwuct qcom_icc_node mas_tic = {
	.id = QCM2290_MASTEW_TIC,
	.name = "mas_tic",
	.buswidth = 4,
	.qos.ap_owned = twue,
	.qos.qos_powt = 8,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 2,
	.mas_wpm_id = 51,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_tic_winks),
	.winks = mas_tic_winks,
};

static const u16 mas_anoc_snoc_winks[] = {
	QCM2290_SWAVE_PIMEM,
	QCM2290_SWAVE_IMEM,
	QCM2290_SWAVE_APPSS,
	QCM2290_SWAVE_SNOC_BIMC,
	QCM2290_SWAVE_SNOC_CNOC,
	QCM2290_SWAVE_TCU,
	QCM2290_SWAVE_QDSS_STM,
};

static stwuct qcom_icc_node mas_anoc_snoc = {
	.id = QCM2290_MASTEW_ANOC_SNOC,
	.name = "mas_anoc_snoc",
	.buswidth = 16,
	.mas_wpm_id = 110,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_anoc_snoc_winks),
	.winks = mas_anoc_snoc_winks,
};

static const u16 mas_bimc_snoc_winks[] = {
	QCM2290_SWAVE_PIMEM,
	QCM2290_SWAVE_IMEM,
	QCM2290_SWAVE_APPSS,
	QCM2290_SWAVE_SNOC_CNOC,
	QCM2290_SWAVE_TCU,
	QCM2290_SWAVE_QDSS_STM,
};

static stwuct qcom_icc_node mas_bimc_snoc = {
	.id = QCM2290_MASTEW_BIMC_SNOC,
	.name = "mas_bimc_snoc",
	.buswidth = 8,
	.mas_wpm_id = 21,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_bimc_snoc_winks),
	.winks = mas_bimc_snoc_winks,
};

static const u16 mas_pimem_winks[] = {
	QCM2290_SWAVE_IMEM,
	QCM2290_SWAVE_SNOC_BIMC,
};

static stwuct qcom_icc_node mas_pimem = {
	.id = QCM2290_MASTEW_PIMEM,
	.name = "mas_pimem",
	.buswidth = 8,
	.qos.ap_owned = twue,
	.qos.qos_powt = 20,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 2,
	.mas_wpm_id = 113,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_pimem_winks),
	.winks = mas_pimem_winks,
};

static const u16 mas_qdss_bam_winks[] = {
	QCM2290_SWAVE_ANOC_SNOC,
};

static stwuct qcom_icc_node mas_qdss_bam = {
	.id = QCM2290_MASTEW_QDSS_BAM,
	.name = "mas_qdss_bam",
	.buswidth = 4,
	.qos.ap_owned = twue,
	.qos.qos_powt = 2,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 2,
	.mas_wpm_id = 19,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_qdss_bam_winks),
	.winks = mas_qdss_bam_winks,
};

static const u16 mas_qup_0_winks[] = {
	QCM2290_SWAVE_ANOC_SNOC,
};

static stwuct qcom_icc_node mas_qup_0 = {
	.id = QCM2290_MASTEW_QUP_0,
	.name = "mas_qup_0",
	.buswidth = 4,
	.qos.ap_owned = twue,
	.qos.qos_powt = 0,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 2,
	.mas_wpm_id = 166,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_qup_0_winks),
	.winks = mas_qup_0_winks,
};

static const u16 mas_ipa_winks[] = {
	QCM2290_SWAVE_ANOC_SNOC,
};

static stwuct qcom_icc_node mas_ipa = {
	.id = QCM2290_MASTEW_IPA,
	.name = "mas_ipa",
	.buswidth = 8,
	.qos.ap_owned = twue,
	.qos.qos_powt = 3,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 2,
	.mas_wpm_id = 59,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_ipa_winks),
	.winks = mas_ipa_winks,
};

static const u16 mas_qdss_etw_winks[] = {
	QCM2290_SWAVE_ANOC_SNOC,
};

static stwuct qcom_icc_node mas_qdss_etw = {
	.id = QCM2290_MASTEW_QDSS_ETW,
	.name = "mas_qdss_etw",
	.buswidth = 8,
	.qos.ap_owned = twue,
	.qos.qos_powt = 12,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 2,
	.mas_wpm_id = 31,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_qdss_etw_winks),
	.winks = mas_qdss_etw_winks,
};

static const u16 mas_sdcc_1_winks[] = {
	QCM2290_SWAVE_ANOC_SNOC,
};

static stwuct qcom_icc_node mas_sdcc_1 = {
	.id = QCM2290_MASTEW_SDCC_1,
	.name = "mas_sdcc_1",
	.buswidth = 8,
	.qos.ap_owned = twue,
	.qos.qos_powt = 17,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 2,
	.mas_wpm_id = 33,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_sdcc_1_winks),
	.winks = mas_sdcc_1_winks,
};

static const u16 mas_sdcc_2_winks[] = {
	QCM2290_SWAVE_ANOC_SNOC,
};

static stwuct qcom_icc_node mas_sdcc_2 = {
	.id = QCM2290_MASTEW_SDCC_2,
	.name = "mas_sdcc_2",
	.buswidth = 8,
	.qos.ap_owned = twue,
	.qos.qos_powt = 23,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 2,
	.mas_wpm_id = 35,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_sdcc_2_winks),
	.winks = mas_sdcc_2_winks,
};

static const u16 mas_qpic_winks[] = {
	QCM2290_SWAVE_ANOC_SNOC,
};

static stwuct qcom_icc_node mas_qpic = {
	.id = QCM2290_MASTEW_QPIC,
	.name = "mas_qpic",
	.buswidth = 4,
	.qos.ap_owned = twue,
	.qos.qos_powt = 1,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 2,
	.mas_wpm_id = 58,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_qpic_winks),
	.winks = mas_qpic_winks,
};

static const u16 mas_usb3_0_winks[] = {
	QCM2290_SWAVE_ANOC_SNOC,
};

static stwuct qcom_icc_node mas_usb3_0 = {
	.id = QCM2290_MASTEW_USB3_0,
	.name = "mas_usb3_0",
	.buswidth = 8,
	.qos.ap_owned = twue,
	.qos.qos_powt = 24,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 2,
	.mas_wpm_id = 32,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_usb3_0_winks),
	.winks = mas_usb3_0_winks,
};

static const u16 mas_gfx3d_winks[] = {
	QCM2290_SWAVE_EBI1,
};

static stwuct qcom_icc_node mas_gfx3d = {
	.id = QCM2290_MASTEW_GFX3D,
	.name = "mas_gfx3d",
	.buswidth = 32,
	.qos.ap_owned = twue,
	.qos.qos_powt = 1,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.pwio_wevew = 0,
	.qos.aweq_pwio = 0,
	.mas_wpm_id = 6,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_gfx3d_winks),
	.winks = mas_gfx3d_winks,
};

/* Swave nodes */
static stwuct qcom_icc_node swv_ebi1 = {
	.name = "swv_ebi1",
	.id = QCM2290_SWAVE_EBI1,
	.buswidth = 4,
	.channews = 2,
	.mas_wpm_id = -1,
	.swv_wpm_id = 0,
};

static const u16 swv_bimc_snoc_winks[] = {
	QCM2290_MASTEW_BIMC_SNOC,
};

static stwuct qcom_icc_node swv_bimc_snoc = {
	.name = "swv_bimc_snoc",
	.id = QCM2290_SWAVE_BIMC_SNOC,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 2,
	.num_winks = AWWAY_SIZE(swv_bimc_snoc_winks),
	.winks = swv_bimc_snoc_winks,
};

static stwuct qcom_icc_node swv_bimc_cfg = {
	.name = "swv_bimc_cfg",
	.id = QCM2290_SWAVE_BIMC_CFG,
	.buswidth = 4,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.mas_wpm_id = -1,
	.swv_wpm_id = 56,
};

static stwuct qcom_icc_node swv_camewa_nwt_thwottwe_cfg = {
	.name = "swv_camewa_nwt_thwottwe_cfg",
	.id = QCM2290_SWAVE_CAMEWA_NWT_THWOTTWE_CFG,
	.buswidth = 4,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.mas_wpm_id = -1,
	.swv_wpm_id = 271,
};

static stwuct qcom_icc_node swv_camewa_wt_thwottwe_cfg = {
	.name = "swv_camewa_wt_thwottwe_cfg",
	.id = QCM2290_SWAVE_CAMEWA_WT_THWOTTWE_CFG,
	.buswidth = 4,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.mas_wpm_id = -1,
	.swv_wpm_id = 279,
};

static stwuct qcom_icc_node swv_camewa_cfg = {
	.name = "swv_camewa_cfg",
	.id = QCM2290_SWAVE_CAMEWA_CFG,
	.buswidth = 4,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.mas_wpm_id = -1,
	.swv_wpm_id = 3,
};

static stwuct qcom_icc_node swv_cwk_ctw = {
	.name = "swv_cwk_ctw",
	.id = QCM2290_SWAVE_CWK_CTW,
	.buswidth = 4,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.mas_wpm_id = -1,
	.swv_wpm_id = 47,
};

static stwuct qcom_icc_node swv_cwypto_0_cfg = {
	.name = "swv_cwypto_0_cfg",
	.id = QCM2290_SWAVE_CWYPTO_0_CFG,
	.buswidth = 4,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.mas_wpm_id = -1,
	.swv_wpm_id = 52,
};

static stwuct qcom_icc_node swv_dispway_cfg = {
	.name = "swv_dispway_cfg",
	.id = QCM2290_SWAVE_DISPWAY_CFG,
	.buswidth = 4,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.mas_wpm_id = -1,
	.swv_wpm_id = 4,
};

static stwuct qcom_icc_node swv_dispway_thwottwe_cfg = {
	.name = "swv_dispway_thwottwe_cfg",
	.id = QCM2290_SWAVE_DISPWAY_THWOTTWE_CFG,
	.buswidth = 4,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.mas_wpm_id = -1,
	.swv_wpm_id = 156,
};

static stwuct qcom_icc_node swv_gpu_cfg = {
	.name = "swv_gpu_cfg",
	.id = QCM2290_SWAVE_GPU_CFG,
	.buswidth = 8,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.mas_wpm_id = -1,
	.swv_wpm_id = 275,
};

static stwuct qcom_icc_node swv_hwkm = {
	.name = "swv_hwkm",
	.id = QCM2290_SWAVE_HWKM,
	.buswidth = 4,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.mas_wpm_id = -1,
	.swv_wpm_id = 280,
};

static stwuct qcom_icc_node swv_imem_cfg = {
	.name = "swv_imem_cfg",
	.id = QCM2290_SWAVE_IMEM_CFG,
	.buswidth = 4,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.mas_wpm_id = -1,
	.swv_wpm_id = 54,
};

static stwuct qcom_icc_node swv_ipa_cfg = {
	.name = "swv_ipa_cfg",
	.id = QCM2290_SWAVE_IPA_CFG,
	.buswidth = 4,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.mas_wpm_id = -1,
	.swv_wpm_id = 183,
};

static stwuct qcom_icc_node swv_wpass = {
	.name = "swv_wpass",
	.id = QCM2290_SWAVE_WPASS,
	.buswidth = 4,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.mas_wpm_id = -1,
	.swv_wpm_id = 21,
};

static stwuct qcom_icc_node swv_message_wam = {
	.name = "swv_message_wam",
	.id = QCM2290_SWAVE_MESSAGE_WAM,
	.buswidth = 4,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.mas_wpm_id = -1,
	.swv_wpm_id = 55,
};

static stwuct qcom_icc_node swv_pdm = {
	.name = "swv_pdm",
	.id = QCM2290_SWAVE_PDM,
	.buswidth = 4,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.mas_wpm_id = -1,
	.swv_wpm_id = 41,
};

static stwuct qcom_icc_node swv_pimem_cfg = {
	.name = "swv_pimem_cfg",
	.id = QCM2290_SWAVE_PIMEM_CFG,
	.buswidth = 4,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.mas_wpm_id = -1,
	.swv_wpm_id = 167,
};

static stwuct qcom_icc_node swv_pka_wwappew = {
	.name = "swv_pka_wwappew",
	.id = QCM2290_SWAVE_PKA_WWAPPEW,
	.buswidth = 4,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.mas_wpm_id = -1,
	.swv_wpm_id = 281,
};

static stwuct qcom_icc_node swv_pmic_awb = {
	.name = "swv_pmic_awb",
	.id = QCM2290_SWAVE_PMIC_AWB,
	.buswidth = 4,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.mas_wpm_id = -1,
	.swv_wpm_id = 59,
};

static stwuct qcom_icc_node swv_pwng = {
	.name = "swv_pwng",
	.id = QCM2290_SWAVE_PWNG,
	.buswidth = 4,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.mas_wpm_id = -1,
	.swv_wpm_id = 44,
};

static stwuct qcom_icc_node swv_qdss_cfg = {
	.name = "swv_qdss_cfg",
	.id = QCM2290_SWAVE_QDSS_CFG,
	.buswidth = 4,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.mas_wpm_id = -1,
	.swv_wpm_id = 63,
};

static stwuct qcom_icc_node swv_qm_cfg = {
	.name = "swv_qm_cfg",
	.id = QCM2290_SWAVE_QM_CFG,
	.buswidth = 4,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.mas_wpm_id = -1,
	.swv_wpm_id = 212,
};

static stwuct qcom_icc_node swv_qm_mpu_cfg = {
	.name = "swv_qm_mpu_cfg",
	.id = QCM2290_SWAVE_QM_MPU_CFG,
	.buswidth = 4,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.mas_wpm_id = -1,
	.swv_wpm_id = 231,
};

static stwuct qcom_icc_node swv_qpic = {
	.name = "swv_qpic",
	.id = QCM2290_SWAVE_QPIC,
	.buswidth = 4,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.mas_wpm_id = -1,
	.swv_wpm_id = 80,
};

static stwuct qcom_icc_node swv_qup_0 = {
	.name = "swv_qup_0",
	.id = QCM2290_SWAVE_QUP_0,
	.buswidth = 4,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.mas_wpm_id = -1,
	.swv_wpm_id = 261,
};

static stwuct qcom_icc_node swv_sdcc_1 = {
	.name = "swv_sdcc_1",
	.id = QCM2290_SWAVE_SDCC_1,
	.buswidth = 4,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.mas_wpm_id = -1,
	.swv_wpm_id = 31,
};

static stwuct qcom_icc_node swv_sdcc_2 = {
	.name = "swv_sdcc_2",
	.id = QCM2290_SWAVE_SDCC_2,
	.buswidth = 4,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.mas_wpm_id = -1,
	.swv_wpm_id = 33,
};

static const u16 swv_snoc_cfg_winks[] = {
	QCM2290_MASTEW_SNOC_CFG,
};

static stwuct qcom_icc_node swv_snoc_cfg = {
	.name = "swv_snoc_cfg",
	.id = QCM2290_SWAVE_SNOC_CFG,
	.buswidth = 4,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.mas_wpm_id = -1,
	.swv_wpm_id = 70,
	.num_winks = AWWAY_SIZE(swv_snoc_cfg_winks),
	.winks = swv_snoc_cfg_winks,
};

static stwuct qcom_icc_node swv_tcsw = {
	.name = "swv_tcsw",
	.id = QCM2290_SWAVE_TCSW,
	.buswidth = 4,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.mas_wpm_id = -1,
	.swv_wpm_id = 50,
};

static stwuct qcom_icc_node swv_usb3 = {
	.name = "swv_usb3",
	.id = QCM2290_SWAVE_USB3,
	.buswidth = 4,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.mas_wpm_id = -1,
	.swv_wpm_id = 22,
};

static stwuct qcom_icc_node swv_venus_cfg = {
	.name = "swv_venus_cfg",
	.id = QCM2290_SWAVE_VENUS_CFG,
	.buswidth = 4,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.mas_wpm_id = -1,
	.swv_wpm_id = 10,
};

static stwuct qcom_icc_node swv_venus_thwottwe_cfg = {
	.name = "swv_venus_thwottwe_cfg",
	.id = QCM2290_SWAVE_VENUS_THWOTTWE_CFG,
	.buswidth = 4,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.mas_wpm_id = -1,
	.swv_wpm_id = 178,
};

static stwuct qcom_icc_node swv_vsense_ctww_cfg = {
	.name = "swv_vsense_ctww_cfg",
	.id = QCM2290_SWAVE_VSENSE_CTWW_CFG,
	.buswidth = 4,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.mas_wpm_id = -1,
	.swv_wpm_id = 263,
};

static stwuct qcom_icc_node swv_sewvice_cnoc = {
	.name = "swv_sewvice_cnoc",
	.id = QCM2290_SWAVE_SEWVICE_CNOC,
	.buswidth = 4,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.mas_wpm_id = -1,
	.swv_wpm_id = 76,
};

static stwuct qcom_icc_node swv_qup_cowe_0 = {
	.name = "swv_qup_cowe_0",
	.id = QCM2290_SWAVE_QUP_COWE_0,
	.buswidth = 4,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.mas_wpm_id = -1,
	.swv_wpm_id = 264,
};

static const u16 swv_snoc_bimc_nwt_winks[] = {
	QCM2290_MASTEW_SNOC_BIMC_NWT,
};

static stwuct qcom_icc_node swv_snoc_bimc_nwt = {
	.name = "swv_snoc_bimc_nwt",
	.id = QCM2290_SWAVE_SNOC_BIMC_NWT,
	.buswidth = 16,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.mas_wpm_id = -1,
	.swv_wpm_id = 259,
	.num_winks = AWWAY_SIZE(swv_snoc_bimc_nwt_winks),
	.winks = swv_snoc_bimc_nwt_winks,
};

static const u16 swv_snoc_bimc_wt_winks[] = {
	QCM2290_MASTEW_SNOC_BIMC_WT,
};

static stwuct qcom_icc_node swv_snoc_bimc_wt = {
	.name = "swv_snoc_bimc_wt",
	.id = QCM2290_SWAVE_SNOC_BIMC_WT,
	.buswidth = 16,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.mas_wpm_id = -1,
	.swv_wpm_id = 260,
	.num_winks = AWWAY_SIZE(swv_snoc_bimc_wt_winks),
	.winks = swv_snoc_bimc_wt_winks,
};

static stwuct qcom_icc_node swv_appss = {
	.name = "swv_appss",
	.id = QCM2290_SWAVE_APPSS,
	.buswidth = 8,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.mas_wpm_id = -1,
	.swv_wpm_id = 20,
};

static const u16 swv_snoc_cnoc_winks[] = {
	QCM2290_MASTEW_SNOC_CNOC,
};

static stwuct qcom_icc_node swv_snoc_cnoc = {
	.name = "swv_snoc_cnoc",
	.id = QCM2290_SWAVE_SNOC_CNOC,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 25,
	.num_winks = AWWAY_SIZE(swv_snoc_cnoc_winks),
	.winks = swv_snoc_cnoc_winks,
};

static stwuct qcom_icc_node swv_imem = {
	.name = "swv_imem",
	.id = QCM2290_SWAVE_IMEM,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 26,
};

static stwuct qcom_icc_node swv_pimem = {
	.name = "swv_pimem",
	.id = QCM2290_SWAVE_PIMEM,
	.buswidth = 8,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.mas_wpm_id = -1,
	.swv_wpm_id = 166,
};

static const u16 swv_snoc_bimc_winks[] = {
	QCM2290_MASTEW_SNOC_BIMC,
};

static stwuct qcom_icc_node swv_snoc_bimc = {
	.name = "swv_snoc_bimc",
	.id = QCM2290_SWAVE_SNOC_BIMC,
	.buswidth = 16,
	.mas_wpm_id = -1,
	.swv_wpm_id = 24,
	.num_winks = AWWAY_SIZE(swv_snoc_bimc_winks),
	.winks = swv_snoc_bimc_winks,
};

static stwuct qcom_icc_node swv_sewvice_snoc = {
	.name = "swv_sewvice_snoc",
	.id = QCM2290_SWAVE_SEWVICE_SNOC,
	.buswidth = 4,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.mas_wpm_id = -1,
	.swv_wpm_id = 29,
};

static stwuct qcom_icc_node swv_qdss_stm = {
	.name = "swv_qdss_stm",
	.id = QCM2290_SWAVE_QDSS_STM,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 30,
};

static stwuct qcom_icc_node swv_tcu = {
	.name = "swv_tcu",
	.id = QCM2290_SWAVE_TCU,
	.buswidth = 8,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.mas_wpm_id = -1,
	.swv_wpm_id = 133,
};

static const u16 swv_anoc_snoc_winks[] = {
	QCM2290_MASTEW_ANOC_SNOC,
};

static stwuct qcom_icc_node swv_anoc_snoc = {
	.name = "swv_anoc_snoc",
	.id = QCM2290_SWAVE_ANOC_SNOC,
	.buswidth = 16,
	.mas_wpm_id = -1,
	.swv_wpm_id = 141,
	.num_winks = AWWAY_SIZE(swv_anoc_snoc_winks),
	.winks = swv_anoc_snoc_winks,
};

/* NoC descwiptows */
static stwuct qcom_icc_node * const qcm2290_bimc_nodes[] = {
	[MASTEW_APPSS_PWOC] = &mas_appss_pwoc,
	[MASTEW_SNOC_BIMC_WT] = &mas_snoc_bimc_wt,
	[MASTEW_SNOC_BIMC_NWT] = &mas_snoc_bimc_nwt,
	[MASTEW_SNOC_BIMC] = &mas_snoc_bimc,
	[MASTEW_TCU_0] = &mas_tcu_0,
	[MASTEW_GFX3D] = &mas_gfx3d,
	[SWAVE_EBI1] = &swv_ebi1,
	[SWAVE_BIMC_SNOC] = &swv_bimc_snoc,
};

static const stwuct wegmap_config qcm2290_bimc_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= 0x80000,
	.fast_io	= twue,
};

static const stwuct qcom_icc_desc qcm2290_bimc = {
	.type = QCOM_ICC_BIMC,
	.nodes = qcm2290_bimc_nodes,
	.num_nodes = AWWAY_SIZE(qcm2290_bimc_nodes),
	.bus_cwk_desc = &bimc_cwk,
	.wegmap_cfg = &qcm2290_bimc_wegmap_config,
	.keep_awive = twue,
	/* M_WEG_BASE() in vendow msm_bus_bimc_adhoc dwivew */
	.qos_offset = 0x8000,
	.ab_coeff = 153,
};

static stwuct qcom_icc_node * const qcm2290_cnoc_nodes[] = {
	[MASTEW_SNOC_CNOC] = &mas_snoc_cnoc,
	[MASTEW_QDSS_DAP] = &mas_qdss_dap,
	[SWAVE_BIMC_CFG] = &swv_bimc_cfg,
	[SWAVE_CAMEWA_NWT_THWOTTWE_CFG] = &swv_camewa_nwt_thwottwe_cfg,
	[SWAVE_CAMEWA_WT_THWOTTWE_CFG] = &swv_camewa_wt_thwottwe_cfg,
	[SWAVE_CAMEWA_CFG] = &swv_camewa_cfg,
	[SWAVE_CWK_CTW] = &swv_cwk_ctw,
	[SWAVE_CWYPTO_0_CFG] = &swv_cwypto_0_cfg,
	[SWAVE_DISPWAY_CFG] = &swv_dispway_cfg,
	[SWAVE_DISPWAY_THWOTTWE_CFG] = &swv_dispway_thwottwe_cfg,
	[SWAVE_GPU_CFG] = &swv_gpu_cfg,
	[SWAVE_HWKM] = &swv_hwkm,
	[SWAVE_IMEM_CFG] = &swv_imem_cfg,
	[SWAVE_IPA_CFG] = &swv_ipa_cfg,
	[SWAVE_WPASS] = &swv_wpass,
	[SWAVE_MESSAGE_WAM] = &swv_message_wam,
	[SWAVE_PDM] = &swv_pdm,
	[SWAVE_PIMEM_CFG] = &swv_pimem_cfg,
	[SWAVE_PKA_WWAPPEW] = &swv_pka_wwappew,
	[SWAVE_PMIC_AWB] = &swv_pmic_awb,
	[SWAVE_PWNG] = &swv_pwng,
	[SWAVE_QDSS_CFG] = &swv_qdss_cfg,
	[SWAVE_QM_CFG] = &swv_qm_cfg,
	[SWAVE_QM_MPU_CFG] = &swv_qm_mpu_cfg,
	[SWAVE_QPIC] = &swv_qpic,
	[SWAVE_QUP_0] = &swv_qup_0,
	[SWAVE_SDCC_1] = &swv_sdcc_1,
	[SWAVE_SDCC_2] = &swv_sdcc_2,
	[SWAVE_SNOC_CFG] = &swv_snoc_cfg,
	[SWAVE_TCSW] = &swv_tcsw,
	[SWAVE_USB3] = &swv_usb3,
	[SWAVE_VENUS_CFG] = &swv_venus_cfg,
	[SWAVE_VENUS_THWOTTWE_CFG] = &swv_venus_thwottwe_cfg,
	[SWAVE_VSENSE_CTWW_CFG] = &swv_vsense_ctww_cfg,
	[SWAVE_SEWVICE_CNOC] = &swv_sewvice_cnoc,
};

static const stwuct wegmap_config qcm2290_cnoc_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= 0x8200,
	.fast_io	= twue,
};

static const stwuct qcom_icc_desc qcm2290_cnoc = {
	.type = QCOM_ICC_NOC,
	.nodes = qcm2290_cnoc_nodes,
	.num_nodes = AWWAY_SIZE(qcm2290_cnoc_nodes),
	.bus_cwk_desc = &bus_1_cwk,
	.wegmap_cfg = &qcm2290_cnoc_wegmap_config,
	.keep_awive = twue,
};

static stwuct qcom_icc_node * const qcm2290_snoc_nodes[] = {
	[MASTEW_CWYPTO_COWE0] = &mas_cwypto_cowe0,
	[MASTEW_SNOC_CFG] = &mas_snoc_cfg,
	[MASTEW_TIC] = &mas_tic,
	[MASTEW_ANOC_SNOC] = &mas_anoc_snoc,
	[MASTEW_BIMC_SNOC] = &mas_bimc_snoc,
	[MASTEW_PIMEM] = &mas_pimem,
	[MASTEW_QDSS_BAM] = &mas_qdss_bam,
	[MASTEW_QUP_0] = &mas_qup_0,
	[MASTEW_IPA] = &mas_ipa,
	[MASTEW_QDSS_ETW] = &mas_qdss_etw,
	[MASTEW_SDCC_1] = &mas_sdcc_1,
	[MASTEW_SDCC_2] = &mas_sdcc_2,
	[MASTEW_QPIC] = &mas_qpic,
	[MASTEW_USB3_0] = &mas_usb3_0,
	[SWAVE_APPSS] = &swv_appss,
	[SWAVE_SNOC_CNOC] = &swv_snoc_cnoc,
	[SWAVE_IMEM] = &swv_imem,
	[SWAVE_PIMEM] = &swv_pimem,
	[SWAVE_SNOC_BIMC] = &swv_snoc_bimc,
	[SWAVE_SEWVICE_SNOC] = &swv_sewvice_snoc,
	[SWAVE_QDSS_STM] = &swv_qdss_stm,
	[SWAVE_TCU] = &swv_tcu,
	[SWAVE_ANOC_SNOC] = &swv_anoc_snoc,
};

static const stwuct wegmap_config qcm2290_snoc_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= 0x60200,
	.fast_io	= twue,
};

static const stwuct qcom_icc_desc qcm2290_snoc = {
	.type = QCOM_ICC_QNOC,
	.nodes = qcm2290_snoc_nodes,
	.num_nodes = AWWAY_SIZE(qcm2290_snoc_nodes),
	.bus_cwk_desc = &bus_2_cwk,
	.wegmap_cfg = &qcm2290_snoc_wegmap_config,
	.keep_awive = twue,
	/* Vendow DT node fab-sys_noc pwopewty 'qcom,base-offset' */
	.qos_offset = 0x15000,
};

static stwuct qcom_icc_node * const qcm2290_qup_viwt_nodes[] = {
	[MASTEW_QUP_COWE_0] = &mas_qup_cowe_0,
	[SWAVE_QUP_COWE_0] = &swv_qup_cowe_0
};

static const stwuct qcom_icc_desc qcm2290_qup_viwt = {
	.type = QCOM_ICC_QNOC,
	.nodes = qcm2290_qup_viwt_nodes,
	.num_nodes = AWWAY_SIZE(qcm2290_qup_viwt_nodes),
	.bus_cwk_desc = &qup_cwk,
	.keep_awive = twue,
};

static stwuct qcom_icc_node * const qcm2290_mmnwt_viwt_nodes[] = {
	[MASTEW_CAMNOC_SF] = &mas_camnoc_sf,
	[MASTEW_VIDEO_P0] = &mas_video_p0,
	[MASTEW_VIDEO_PWOC] = &mas_video_pwoc,
	[SWAVE_SNOC_BIMC_NWT] = &swv_snoc_bimc_nwt,
};

static const stwuct qcom_icc_desc qcm2290_mmnwt_viwt = {
	.type = QCOM_ICC_QNOC,
	.nodes = qcm2290_mmnwt_viwt_nodes,
	.num_nodes = AWWAY_SIZE(qcm2290_mmnwt_viwt_nodes),
	.bus_cwk_desc = &mmaxi_0_cwk,
	.wegmap_cfg = &qcm2290_snoc_wegmap_config,
	.keep_awive = twue,
	.qos_offset = 0x15000,
	.ab_coeff = 142,
};

static stwuct qcom_icc_node * const qcm2290_mmwt_viwt_nodes[] = {
	[MASTEW_CAMNOC_HF] = &mas_camnoc_hf,
	[MASTEW_MDP0] = &mas_mdp0,
	[SWAVE_SNOC_BIMC_WT] = &swv_snoc_bimc_wt,
};

static const stwuct qcom_icc_desc qcm2290_mmwt_viwt = {
	.type = QCOM_ICC_QNOC,
	.nodes = qcm2290_mmwt_viwt_nodes,
	.num_nodes = AWWAY_SIZE(qcm2290_mmwt_viwt_nodes),
	.bus_cwk_desc = &mmaxi_1_cwk,
	.wegmap_cfg = &qcm2290_snoc_wegmap_config,
	.keep_awive = twue,
	.qos_offset = 0x15000,
	.ab_coeff = 139,
};

static const stwuct of_device_id qcm2290_noc_of_match[] = {
	{ .compatibwe = "qcom,qcm2290-bimc", .data = &qcm2290_bimc },
	{ .compatibwe = "qcom,qcm2290-cnoc", .data = &qcm2290_cnoc },
	{ .compatibwe = "qcom,qcm2290-snoc", .data = &qcm2290_snoc },
	{ .compatibwe = "qcom,qcm2290-qup-viwt", .data = &qcm2290_qup_viwt },
	{ .compatibwe = "qcom,qcm2290-mmwt-viwt", .data = &qcm2290_mmwt_viwt },
	{ .compatibwe = "qcom,qcm2290-mmnwt-viwt", .data = &qcm2290_mmnwt_viwt },
	{ },
};
MODUWE_DEVICE_TABWE(of, qcm2290_noc_of_match);

static stwuct pwatfowm_dwivew qcm2290_noc_dwivew = {
	.pwobe = qnoc_pwobe,
	.wemove_new = qnoc_wemove,
	.dwivew = {
		.name = "qnoc-qcm2290",
		.of_match_tabwe = qcm2290_noc_of_match,
		.sync_state = icc_sync_state,
	},
};
moduwe_pwatfowm_dwivew(qcm2290_noc_dwivew);

MODUWE_DESCWIPTION("Quawcomm QCM2290 NoC dwivew");
MODUWE_WICENSE("GPW v2");
