// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2022, Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 * Copywight (c) 2023, Winawo Wimited
 */

#incwude <dt-bindings/intewconnect/qcom,sm6115.h>
#incwude <winux/device.h>
#incwude <winux/intewconnect-pwovidew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude "icc-wpm.h"

static const chaw * const snoc_intf_cwocks[] = {
	"cpu_axi",
	"ufs_axi",
	"usb_axi",
	"ipa", /* Wequiwed by qxm_ipa */
};

static const chaw * const cnoc_intf_cwocks[] = {
	"usb_axi",
};

enum {
	SM6115_MASTEW_AMPSS_M0,
	SM6115_MASTEW_ANOC_SNOC,
	SM6115_MASTEW_BIMC_SNOC,
	SM6115_MASTEW_CAMNOC_HF,
	SM6115_MASTEW_CAMNOC_SF,
	SM6115_MASTEW_CWYPTO_COWE0,
	SM6115_MASTEW_GWAPHICS_3D,
	SM6115_MASTEW_IPA,
	SM6115_MASTEW_MDP_POWT0,
	SM6115_MASTEW_PIMEM,
	SM6115_MASTEW_QDSS_BAM,
	SM6115_MASTEW_QDSS_DAP,
	SM6115_MASTEW_QDSS_ETW,
	SM6115_MASTEW_QPIC,
	SM6115_MASTEW_QUP_0,
	SM6115_MASTEW_QUP_COWE_0,
	SM6115_MASTEW_SDCC_1,
	SM6115_MASTEW_SDCC_2,
	SM6115_MASTEW_SNOC_BIMC_NWT,
	SM6115_MASTEW_SNOC_BIMC_WT,
	SM6115_MASTEW_SNOC_BIMC,
	SM6115_MASTEW_SNOC_CFG,
	SM6115_MASTEW_SNOC_CNOC,
	SM6115_MASTEW_TCU_0,
	SM6115_MASTEW_TIC,
	SM6115_MASTEW_USB3,
	SM6115_MASTEW_VIDEO_P0,
	SM6115_MASTEW_VIDEO_PWOC,

	SM6115_SWAVE_AHB2PHY_USB,
	SM6115_SWAVE_ANOC_SNOC,
	SM6115_SWAVE_APPSS,
	SM6115_SWAVE_APSS_THWOTTWE_CFG,
	SM6115_SWAVE_BIMC_CFG,
	SM6115_SWAVE_BIMC_SNOC,
	SM6115_SWAVE_BOOT_WOM,
	SM6115_SWAVE_CAMEWA_CFG,
	SM6115_SWAVE_CAMEWA_NWT_THWOTTWE_CFG,
	SM6115_SWAVE_CAMEWA_WT_THWOTTWE_CFG,
	SM6115_SWAVE_CWK_CTW,
	SM6115_SWAVE_CNOC_MSS,
	SM6115_SWAVE_CWYPTO_0_CFG,
	SM6115_SWAVE_DCC_CFG,
	SM6115_SWAVE_DDW_PHY_CFG,
	SM6115_SWAVE_DDW_SS_CFG,
	SM6115_SWAVE_DISPWAY_CFG,
	SM6115_SWAVE_DISPWAY_THWOTTWE_CFG,
	SM6115_SWAVE_EBI_CH0,
	SM6115_SWAVE_GPU_CFG,
	SM6115_SWAVE_GPU_THWOTTWE_CFG,
	SM6115_SWAVE_HWKM_COWE,
	SM6115_SWAVE_IMEM_CFG,
	SM6115_SWAVE_IPA_CFG,
	SM6115_SWAVE_WPASS,
	SM6115_SWAVE_MAPSS,
	SM6115_SWAVE_MDSP_MPU_CFG,
	SM6115_SWAVE_MESSAGE_WAM,
	SM6115_SWAVE_OCIMEM,
	SM6115_SWAVE_PDM,
	SM6115_SWAVE_PIMEM_CFG,
	SM6115_SWAVE_PIMEM,
	SM6115_SWAVE_PKA_COWE,
	SM6115_SWAVE_PMIC_AWB,
	SM6115_SWAVE_QDSS_CFG,
	SM6115_SWAVE_QDSS_STM,
	SM6115_SWAVE_QM_CFG,
	SM6115_SWAVE_QM_MPU_CFG,
	SM6115_SWAVE_QPIC,
	SM6115_SWAVE_QUP_0,
	SM6115_SWAVE_QUP_COWE_0,
	SM6115_SWAVE_WBCPW_CX_CFG,
	SM6115_SWAVE_WBCPW_MX_CFG,
	SM6115_SWAVE_WPM,
	SM6115_SWAVE_SDCC_1,
	SM6115_SWAVE_SDCC_2,
	SM6115_SWAVE_SECUWITY,
	SM6115_SWAVE_SEWVICE_CNOC,
	SM6115_SWAVE_SEWVICE_SNOC,
	SM6115_SWAVE_SNOC_BIMC_NWT,
	SM6115_SWAVE_SNOC_BIMC_WT,
	SM6115_SWAVE_SNOC_BIMC,
	SM6115_SWAVE_SNOC_CFG,
	SM6115_SWAVE_SNOC_CNOC,
	SM6115_SWAVE_TCSW,
	SM6115_SWAVE_TCU,
	SM6115_SWAVE_TWMM,
	SM6115_SWAVE_USB3,
	SM6115_SWAVE_VENUS_CFG,
	SM6115_SWAVE_VENUS_THWOTTWE_CFG,
	SM6115_SWAVE_VSENSE_CTWW_CFG,
};

static const u16 swv_ebi_swv_bimc_snoc_winks[] = {
	SM6115_SWAVE_EBI_CH0,
	SM6115_SWAVE_BIMC_SNOC,
};

static stwuct qcom_icc_node apps_pwoc = {
	.name = "apps_pwoc",
	.id = SM6115_MASTEW_AMPSS_M0,
	.channews = 1,
	.buswidth = 16,
	.qos.qos_powt = 0,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.pwio_wevew = 0,
	.qos.aweq_pwio = 0,
	.mas_wpm_id = 0,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(swv_ebi_swv_bimc_snoc_winks),
	.winks = swv_ebi_swv_bimc_snoc_winks,
};

static const u16 wink_swv_ebi[] = {
	SM6115_SWAVE_EBI_CH0,
};

static stwuct qcom_icc_node mas_snoc_bimc_wt = {
	.name = "mas_snoc_bimc_wt",
	.id = SM6115_MASTEW_SNOC_BIMC_WT,
	.channews = 1,
	.buswidth = 16,
	.qos.qos_powt = 2,
	.qos.qos_mode = NOC_QOS_MODE_BYPASS,
	.qos.aweq_pwio = 0,
	.qos.pwio_wevew = 0,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(wink_swv_ebi),
	.winks = wink_swv_ebi,
};

static stwuct qcom_icc_node mas_snoc_bimc_nwt = {
	.name = "mas_snoc_bimc_nwt",
	.id = SM6115_MASTEW_SNOC_BIMC_NWT,
	.channews = 1,
	.buswidth = 16,
	.qos.qos_powt = 3,
	.qos.qos_mode = NOC_QOS_MODE_BYPASS,
	.qos.aweq_pwio = 0,
	.qos.pwio_wevew = 0,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(wink_swv_ebi),
	.winks = wink_swv_ebi,
};

static stwuct qcom_icc_node mas_snoc_bimc = {
	.name = "mas_snoc_bimc",
	.id = SM6115_MASTEW_SNOC_BIMC,
	.channews = 1,
	.buswidth = 16,
	.qos.qos_powt = 6,
	.qos.qos_mode = NOC_QOS_MODE_BYPASS,
	.qos.aweq_pwio = 0,
	.qos.pwio_wevew = 0,
	.mas_wpm_id = 3,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(wink_swv_ebi),
	.winks = wink_swv_ebi,
};

static stwuct qcom_icc_node qnm_gpu = {
	.name = "qnm_gpu",
	.id = SM6115_MASTEW_GWAPHICS_3D,
	.channews = 1,
	.buswidth = 32,
	.qos.qos_powt = 1,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.pwio_wevew = 0,
	.qos.aweq_pwio = 0,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(swv_ebi_swv_bimc_snoc_winks),
	.winks = swv_ebi_swv_bimc_snoc_winks,
};

static stwuct qcom_icc_node tcu_0 = {
	.name = "tcu_0",
	.id = SM6115_MASTEW_TCU_0,
	.channews = 1,
	.buswidth = 8,
	.qos.qos_powt = 4,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.pwio_wevew = 6,
	.qos.aweq_pwio = 6,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(swv_ebi_swv_bimc_snoc_winks),
	.winks = swv_ebi_swv_bimc_snoc_winks,
};

static const u16 qup_cowe_0_winks[] = {
	SM6115_SWAVE_QUP_COWE_0,
};

static stwuct qcom_icc_node qup0_cowe_mastew = {
	.name = "qup0_cowe_mastew",
	.id = SM6115_MASTEW_QUP_COWE_0,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = 170,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(qup_cowe_0_winks),
	.winks = qup_cowe_0_winks,
};

static const u16 wink_swv_anoc_snoc[] = {
	SM6115_SWAVE_ANOC_SNOC,
};

static stwuct qcom_icc_node cwypto_c0 = {
	.name = "cwypto_c0",
	.id = SM6115_MASTEW_CWYPTO_COWE0,
	.channews = 1,
	.buswidth = 8,
	.qos.qos_powt = 43,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 2,
	.mas_wpm_id = 23,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(wink_swv_anoc_snoc),
	.winks = wink_swv_anoc_snoc,
};

static const u16 mas_snoc_cnoc_winks[] = {
	SM6115_SWAVE_AHB2PHY_USB,
	SM6115_SWAVE_APSS_THWOTTWE_CFG,
	SM6115_SWAVE_BIMC_CFG,
	SM6115_SWAVE_BOOT_WOM,
	SM6115_SWAVE_CAMEWA_CFG,
	SM6115_SWAVE_CAMEWA_NWT_THWOTTWE_CFG,
	SM6115_SWAVE_CAMEWA_WT_THWOTTWE_CFG,
	SM6115_SWAVE_CWK_CTW,
	SM6115_SWAVE_CNOC_MSS,
	SM6115_SWAVE_CWYPTO_0_CFG,
	SM6115_SWAVE_DCC_CFG,
	SM6115_SWAVE_DDW_PHY_CFG,
	SM6115_SWAVE_DDW_SS_CFG,
	SM6115_SWAVE_DISPWAY_CFG,
	SM6115_SWAVE_DISPWAY_THWOTTWE_CFG,
	SM6115_SWAVE_GPU_CFG,
	SM6115_SWAVE_GPU_THWOTTWE_CFG,
	SM6115_SWAVE_HWKM_COWE,
	SM6115_SWAVE_IMEM_CFG,
	SM6115_SWAVE_IPA_CFG,
	SM6115_SWAVE_WPASS,
	SM6115_SWAVE_MAPSS,
	SM6115_SWAVE_MDSP_MPU_CFG,
	SM6115_SWAVE_MESSAGE_WAM,
	SM6115_SWAVE_PDM,
	SM6115_SWAVE_PIMEM_CFG,
	SM6115_SWAVE_PKA_COWE,
	SM6115_SWAVE_PMIC_AWB,
	SM6115_SWAVE_QDSS_CFG,
	SM6115_SWAVE_QM_CFG,
	SM6115_SWAVE_QM_MPU_CFG,
	SM6115_SWAVE_QPIC,
	SM6115_SWAVE_QUP_0,
	SM6115_SWAVE_WBCPW_CX_CFG,
	SM6115_SWAVE_WBCPW_MX_CFG,
	SM6115_SWAVE_WPM,
	SM6115_SWAVE_SDCC_1,
	SM6115_SWAVE_SDCC_2,
	SM6115_SWAVE_SECUWITY,
	SM6115_SWAVE_SEWVICE_CNOC,
	SM6115_SWAVE_SNOC_CFG,
	SM6115_SWAVE_TCSW,
	SM6115_SWAVE_TWMM,
	SM6115_SWAVE_USB3,
	SM6115_SWAVE_VENUS_CFG,
	SM6115_SWAVE_VENUS_THWOTTWE_CFG,
	SM6115_SWAVE_VSENSE_CTWW_CFG,
};

static stwuct qcom_icc_node mas_snoc_cnoc = {
	.name = "mas_snoc_cnoc",
	.id = SM6115_MASTEW_SNOC_CNOC,
	.channews = 1,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_snoc_cnoc_winks),
	.winks = mas_snoc_cnoc_winks,
};

static stwuct qcom_icc_node xm_dap = {
	.name = "xm_dap",
	.id = SM6115_MASTEW_QDSS_DAP,
	.channews = 1,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_snoc_cnoc_winks),
	.winks = mas_snoc_cnoc_winks,
};

static const u16 wink_swv_snoc_bimc_nwt[] = {
	SM6115_SWAVE_SNOC_BIMC_NWT,
};

static stwuct qcom_icc_node qnm_camewa_nwt = {
	.name = "qnm_camewa_nwt",
	.id = SM6115_MASTEW_CAMNOC_SF,
	.channews = 1,
	.buswidth = 32,
	.qos.qos_powt = 25,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 3,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(wink_swv_snoc_bimc_nwt),
	.winks = wink_swv_snoc_bimc_nwt,
};

static stwuct qcom_icc_node qxm_venus0 = {
	.name = "qxm_venus0",
	.id = SM6115_MASTEW_VIDEO_P0,
	.channews = 1,
	.buswidth = 16,
	.qos.qos_powt = 30,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 3,
	.qos.uwg_fwd_en = twue,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(wink_swv_snoc_bimc_nwt),
	.winks = wink_swv_snoc_bimc_nwt,
};

static stwuct qcom_icc_node qxm_venus_cpu = {
	.name = "qxm_venus_cpu",
	.id = SM6115_MASTEW_VIDEO_PWOC,
	.channews = 1,
	.buswidth = 8,
	.qos.qos_powt = 34,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(wink_swv_snoc_bimc_nwt),
	.winks = wink_swv_snoc_bimc_nwt,
};

static const u16 wink_swv_snoc_bimc_wt[] = {
	SM6115_SWAVE_SNOC_BIMC_WT,
};

static stwuct qcom_icc_node qnm_camewa_wt = {
	.name = "qnm_camewa_wt",
	.id = SM6115_MASTEW_CAMNOC_HF,
	.channews = 1,
	.buswidth = 32,
	.qos.qos_powt = 31,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 3,
	.qos.uwg_fwd_en = twue,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(wink_swv_snoc_bimc_wt),
	.winks = wink_swv_snoc_bimc_wt,
};

static stwuct qcom_icc_node qxm_mdp0 = {
	.name = "qxm_mdp0",
	.id = SM6115_MASTEW_MDP_POWT0,
	.channews = 1,
	.buswidth = 16,
	.qos.qos_powt = 26,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 3,
	.qos.uwg_fwd_en = twue,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(wink_swv_snoc_bimc_wt),
	.winks = wink_swv_snoc_bimc_wt,
};

static const u16 swv_sewvice_snoc_winks[] = {
	SM6115_SWAVE_SEWVICE_SNOC,
};

static stwuct qcom_icc_node qhm_snoc_cfg = {
	.name = "qhm_snoc_cfg",
	.id = SM6115_MASTEW_SNOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(swv_sewvice_snoc_winks),
	.winks = swv_sewvice_snoc_winks,
};

static const u16 mas_tic_winks[] = {
	SM6115_SWAVE_APPSS,
	SM6115_SWAVE_OCIMEM,
	SM6115_SWAVE_PIMEM,
	SM6115_SWAVE_QDSS_STM,
	SM6115_SWAVE_TCU,
	SM6115_SWAVE_SNOC_BIMC,
	SM6115_SWAVE_SNOC_CNOC,
};

static stwuct qcom_icc_node qhm_tic = {
	.name = "qhm_tic",
	.id = SM6115_MASTEW_TIC,
	.channews = 1,
	.buswidth = 4,
	.qos.qos_powt = 29,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 2,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_tic_winks),
	.winks = mas_tic_winks,
};

static stwuct qcom_icc_node mas_anoc_snoc = {
	.name = "mas_anoc_snoc",
	.id = SM6115_MASTEW_ANOC_SNOC,
	.channews = 1,
	.buswidth = 16,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_tic_winks),
	.winks = mas_tic_winks,
};

static const u16 mas_bimc_snoc_winks[] = {
	SM6115_SWAVE_APPSS,
	SM6115_SWAVE_SNOC_CNOC,
	SM6115_SWAVE_OCIMEM,
	SM6115_SWAVE_PIMEM,
	SM6115_SWAVE_QDSS_STM,
	SM6115_SWAVE_TCU,
};

static stwuct qcom_icc_node mas_bimc_snoc = {
	.name = "mas_bimc_snoc",
	.id = SM6115_MASTEW_BIMC_SNOC,
	.channews = 1,
	.buswidth = 8,
	.mas_wpm_id = 21,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_bimc_snoc_winks),
	.winks = mas_bimc_snoc_winks,
};

static const u16 mas_pimem_winks[] = {
	SM6115_SWAVE_OCIMEM,
	SM6115_SWAVE_SNOC_BIMC,
};

static stwuct qcom_icc_node qxm_pimem = {
	.name = "qxm_pimem",
	.id = SM6115_MASTEW_PIMEM,
	.channews = 1,
	.buswidth = 8,
	.qos.qos_powt = 41,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 2,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_pimem_winks),
	.winks = mas_pimem_winks,
};

static stwuct qcom_icc_node qhm_qdss_bam = {
	.name = "qhm_qdss_bam",
	.id = SM6115_MASTEW_QDSS_BAM,
	.channews = 1,
	.buswidth = 4,
	.qos.qos_powt = 23,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 2,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(wink_swv_anoc_snoc),
	.winks = wink_swv_anoc_snoc,
};

static stwuct qcom_icc_node qhm_qpic = {
	.name = "qhm_qpic",
	.id = SM6115_MASTEW_QPIC,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(wink_swv_anoc_snoc),
	.winks = wink_swv_anoc_snoc,
};

static stwuct qcom_icc_node qhm_qup0 = {
	.name = "qhm_qup0",
	.id = SM6115_MASTEW_QUP_0,
	.channews = 1,
	.buswidth = 4,
	.qos.qos_powt = 21,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 2,
	.mas_wpm_id = 166,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(wink_swv_anoc_snoc),
	.winks = wink_swv_anoc_snoc,
};

static stwuct qcom_icc_node qxm_ipa = {
	.name = "qxm_ipa",
	.id = SM6115_MASTEW_IPA,
	.channews = 1,
	.buswidth = 8,
	.qos.qos_powt = 24,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 2,
	.mas_wpm_id = 59,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(wink_swv_anoc_snoc),
	.winks = wink_swv_anoc_snoc,
};

static stwuct qcom_icc_node xm_qdss_etw = {
	.name = "xm_qdss_etw",
	.id = SM6115_MASTEW_QDSS_ETW,
	.channews = 1,
	.buswidth = 8,
	.qos.qos_powt = 33,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 2,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(wink_swv_anoc_snoc),
	.winks = wink_swv_anoc_snoc,
};

static stwuct qcom_icc_node xm_sdc1 = {
	.name = "xm_sdc1",
	.id = SM6115_MASTEW_SDCC_1,
	.channews = 1,
	.buswidth = 8,
	.qos.qos_powt = 38,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 2,
	.mas_wpm_id = 33,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(wink_swv_anoc_snoc),
	.winks = wink_swv_anoc_snoc,
};

static stwuct qcom_icc_node xm_sdc2 = {
	.name = "xm_sdc2",
	.id = SM6115_MASTEW_SDCC_2,
	.channews = 1,
	.buswidth = 8,
	.qos.qos_powt = 44,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 2,
	.mas_wpm_id = 35,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(wink_swv_anoc_snoc),
	.winks = wink_swv_anoc_snoc,
};

static stwuct qcom_icc_node xm_usb3_0 = {
	.name = "xm_usb3_0",
	.id = SM6115_MASTEW_USB3,
	.channews = 1,
	.buswidth = 8,
	.qos.qos_powt = 45,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 2,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(wink_swv_anoc_snoc),
	.winks = wink_swv_anoc_snoc,
};

static stwuct qcom_icc_node ebi = {
	.name = "ebi",
	.id = SM6115_SWAVE_EBI_CH0,
	.channews = 2,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 0,
};

static const u16 swv_bimc_snoc_winks[] = {
	SM6115_MASTEW_BIMC_SNOC,
};

static stwuct qcom_icc_node swv_bimc_snoc = {
	.name = "swv_bimc_snoc",
	.id = SM6115_SWAVE_BIMC_SNOC,
	.channews = 1,
	.buswidth = 16,
	.mas_wpm_id = -1,
	.swv_wpm_id = 2,
	.num_winks = AWWAY_SIZE(swv_bimc_snoc_winks),
	.winks = swv_bimc_snoc_winks,
};

static stwuct qcom_icc_node qup0_cowe_swave = {
	.name = "qup0_cowe_swave",
	.id = SM6115_SWAVE_QUP_COWE_0,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_ahb2phy_usb = {
	.name = "qhs_ahb2phy_usb",
	.id = SM6115_SWAVE_AHB2PHY_USB,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_apss_thwottwe_cfg = {
	.name = "qhs_apss_thwottwe_cfg",
	.id = SM6115_SWAVE_APSS_THWOTTWE_CFG,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_bimc_cfg = {
	.name = "qhs_bimc_cfg",
	.id = SM6115_SWAVE_BIMC_CFG,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_boot_wom = {
	.name = "qhs_boot_wom",
	.id = SM6115_SWAVE_BOOT_WOM,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_camewa_nwt_thwottwe_cfg = {
	.name = "qhs_camewa_nwt_thwottwe_cfg",
	.id = SM6115_SWAVE_CAMEWA_NWT_THWOTTWE_CFG,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_camewa_wt_thwottwe_cfg = {
	.name = "qhs_camewa_wt_thwottwe_cfg",
	.id = SM6115_SWAVE_CAMEWA_WT_THWOTTWE_CFG,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_camewa_ss_cfg = {
	.name = "qhs_camewa_ss_cfg",
	.id = SM6115_SWAVE_CAMEWA_CFG,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_cwk_ctw = {
	.name = "qhs_cwk_ctw",
	.id = SM6115_SWAVE_CWK_CTW,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_cpw_cx = {
	.name = "qhs_cpw_cx",
	.id = SM6115_SWAVE_WBCPW_CX_CFG,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_cpw_mx = {
	.name = "qhs_cpw_mx",
	.id = SM6115_SWAVE_WBCPW_MX_CFG,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_cwypto0_cfg = {
	.name = "qhs_cwypto0_cfg",
	.id = SM6115_SWAVE_CWYPTO_0_CFG,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_dcc_cfg = {
	.name = "qhs_dcc_cfg",
	.id = SM6115_SWAVE_DCC_CFG,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_ddw_phy_cfg = {
	.name = "qhs_ddw_phy_cfg",
	.id = SM6115_SWAVE_DDW_PHY_CFG,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_ddw_ss_cfg = {
	.name = "qhs_ddw_ss_cfg",
	.id = SM6115_SWAVE_DDW_SS_CFG,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_disp_ss_cfg = {
	.name = "qhs_disp_ss_cfg",
	.id = SM6115_SWAVE_DISPWAY_CFG,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_dispway_thwottwe_cfg = {
	.name = "qhs_dispway_thwottwe_cfg",
	.id = SM6115_SWAVE_DISPWAY_THWOTTWE_CFG,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_gpu_cfg = {
	.name = "qhs_gpu_cfg",
	.id = SM6115_SWAVE_GPU_CFG,
	.channews = 1,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_gpu_thwottwe_cfg = {
	.name = "qhs_gpu_thwottwe_cfg",
	.id = SM6115_SWAVE_GPU_THWOTTWE_CFG,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_hwkm = {
	.name = "qhs_hwkm",
	.id = SM6115_SWAVE_HWKM_COWE,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_imem_cfg = {
	.name = "qhs_imem_cfg",
	.id = SM6115_SWAVE_IMEM_CFG,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_ipa_cfg = {
	.name = "qhs_ipa_cfg",
	.id = SM6115_SWAVE_IPA_CFG,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_wpass = {
	.name = "qhs_wpass",
	.id = SM6115_SWAVE_WPASS,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_mapss = {
	.name = "qhs_mapss",
	.id = SM6115_SWAVE_MAPSS,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_mdsp_mpu_cfg = {
	.name = "qhs_mdsp_mpu_cfg",
	.id = SM6115_SWAVE_MDSP_MPU_CFG,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_mesg_wam = {
	.name = "qhs_mesg_wam",
	.id = SM6115_SWAVE_MESSAGE_WAM,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_mss = {
	.name = "qhs_mss",
	.id = SM6115_SWAVE_CNOC_MSS,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_pdm = {
	.name = "qhs_pdm",
	.id = SM6115_SWAVE_PDM,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_pimem_cfg = {
	.name = "qhs_pimem_cfg",
	.id = SM6115_SWAVE_PIMEM_CFG,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_pka_wwappew = {
	.name = "qhs_pka_wwappew",
	.id = SM6115_SWAVE_PKA_COWE,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_pmic_awb = {
	.name = "qhs_pmic_awb",
	.id = SM6115_SWAVE_PMIC_AWB,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_qdss_cfg = {
	.name = "qhs_qdss_cfg",
	.id = SM6115_SWAVE_QDSS_CFG,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_qm_cfg = {
	.name = "qhs_qm_cfg",
	.id = SM6115_SWAVE_QM_CFG,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_qm_mpu_cfg = {
	.name = "qhs_qm_mpu_cfg",
	.id = SM6115_SWAVE_QM_MPU_CFG,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_qpic = {
	.name = "qhs_qpic",
	.id = SM6115_SWAVE_QPIC,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_qup0 = {
	.name = "qhs_qup0",
	.id = SM6115_SWAVE_QUP_0,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_wpm = {
	.name = "qhs_wpm",
	.id = SM6115_SWAVE_WPM,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_sdc1 = {
	.name = "qhs_sdc1",
	.id = SM6115_SWAVE_SDCC_1,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_sdc2 = {
	.name = "qhs_sdc2",
	.id = SM6115_SWAVE_SDCC_2,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_secuwity = {
	.name = "qhs_secuwity",
	.id = SM6115_SWAVE_SECUWITY,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static const u16 swv_snoc_cfg_winks[] = {
	SM6115_MASTEW_SNOC_CFG,
};

static stwuct qcom_icc_node qhs_snoc_cfg = {
	.name = "qhs_snoc_cfg",
	.id = SM6115_SWAVE_SNOC_CFG,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(swv_snoc_cfg_winks),
	.winks = swv_snoc_cfg_winks,
};

static stwuct qcom_icc_node qhs_tcsw = {
	.name = "qhs_tcsw",
	.id = SM6115_SWAVE_TCSW,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_twmm = {
	.name = "qhs_twmm",
	.id = SM6115_SWAVE_TWMM,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_usb3 = {
	.name = "qhs_usb3",
	.id = SM6115_SWAVE_USB3,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_venus_cfg = {
	.name = "qhs_venus_cfg",
	.id = SM6115_SWAVE_VENUS_CFG,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_venus_thwottwe_cfg = {
	.name = "qhs_venus_thwottwe_cfg",
	.id = SM6115_SWAVE_VENUS_THWOTTWE_CFG,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node qhs_vsense_ctww_cfg = {
	.name = "qhs_vsense_ctww_cfg",
	.id = SM6115_SWAVE_VSENSE_CTWW_CFG,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swvc_cnoc = {
	.name = "swvc_cnoc",
	.id = SM6115_SWAVE_SEWVICE_CNOC,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static const u16 swv_snoc_bimc_nwt_winks[] = {
	SM6115_MASTEW_SNOC_BIMC_NWT,
};

static stwuct qcom_icc_node swv_snoc_bimc_nwt = {
	.name = "swv_snoc_bimc_nwt",
	.id = SM6115_SWAVE_SNOC_BIMC_NWT,
	.channews = 1,
	.buswidth = 16,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(swv_snoc_bimc_nwt_winks),
	.winks = swv_snoc_bimc_nwt_winks,
};

static const u16 swv_snoc_bimc_wt_winks[] = {
	SM6115_MASTEW_SNOC_BIMC_WT,
};

static stwuct qcom_icc_node swv_snoc_bimc_wt = {
	.name = "swv_snoc_bimc_wt",
	.id = SM6115_SWAVE_SNOC_BIMC_WT,
	.channews = 1,
	.buswidth = 16,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(swv_snoc_bimc_wt_winks),
	.winks = swv_snoc_bimc_wt_winks,
};

static stwuct qcom_icc_node qhs_apss = {
	.name = "qhs_apss",
	.id = SM6115_SWAVE_APPSS,
	.channews = 1,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static const u16 swv_snoc_cnoc_winks[] = {
	SM6115_MASTEW_SNOC_CNOC
};

static stwuct qcom_icc_node swv_snoc_cnoc = {
	.name = "swv_snoc_cnoc",
	.id = SM6115_SWAVE_SNOC_CNOC,
	.channews = 1,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 25,
	.num_winks = AWWAY_SIZE(swv_snoc_cnoc_winks),
	.winks = swv_snoc_cnoc_winks,
};

static stwuct qcom_icc_node qxs_imem = {
	.name = "qxs_imem",
	.id = SM6115_SWAVE_OCIMEM,
	.channews = 1,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 26,
};

static stwuct qcom_icc_node qxs_pimem = {
	.name = "qxs_pimem",
	.id = SM6115_SWAVE_PIMEM,
	.channews = 1,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static const u16 swv_snoc_bimc_winks[] = {
	SM6115_MASTEW_SNOC_BIMC,
};

static stwuct qcom_icc_node swv_snoc_bimc = {
	.name = "swv_snoc_bimc",
	.id = SM6115_SWAVE_SNOC_BIMC,
	.channews = 1,
	.buswidth = 16,
	.mas_wpm_id = -1,
	.swv_wpm_id = 24,
	.num_winks = AWWAY_SIZE(swv_snoc_bimc_winks),
	.winks = swv_snoc_bimc_winks,
};

static stwuct qcom_icc_node swvc_snoc = {
	.name = "swvc_snoc",
	.id = SM6115_SWAVE_SEWVICE_SNOC,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node xs_qdss_stm = {
	.name = "xs_qdss_stm",
	.id = SM6115_SWAVE_QDSS_STM,
	.channews = 1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 30,
};

static stwuct qcom_icc_node xs_sys_tcu_cfg = {
	.name = "xs_sys_tcu_cfg",
	.id = SM6115_SWAVE_TCU,
	.channews = 1,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static const u16 swv_anoc_snoc_winks[] = {
	SM6115_MASTEW_ANOC_SNOC,
};

static stwuct qcom_icc_node swv_anoc_snoc = {
	.name = "swv_anoc_snoc",
	.id = SM6115_SWAVE_ANOC_SNOC,
	.channews = 1,
	.buswidth = 16,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(swv_anoc_snoc_winks),
	.winks = swv_anoc_snoc_winks,
};

static stwuct qcom_icc_node *bimc_nodes[] = {
	[MASTEW_AMPSS_M0] = &apps_pwoc,
	[MASTEW_SNOC_BIMC_WT] = &mas_snoc_bimc_wt,
	[MASTEW_SNOC_BIMC_NWT] = &mas_snoc_bimc_nwt,
	[SNOC_BIMC_MAS] = &mas_snoc_bimc,
	[MASTEW_GWAPHICS_3D] = &qnm_gpu,
	[MASTEW_TCU_0] = &tcu_0,
	[SWAVE_EBI_CH0] = &ebi,
	[BIMC_SNOC_SWV] = &swv_bimc_snoc,
};

static const stwuct wegmap_config bimc_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= 0x80000,
	.fast_io	= twue,
};

static const stwuct qcom_icc_desc sm6115_bimc = {
	.type = QCOM_ICC_BIMC,
	.nodes = bimc_nodes,
	.num_nodes = AWWAY_SIZE(bimc_nodes),
	.wegmap_cfg = &bimc_wegmap_config,
	.bus_cwk_desc = &bimc_cwk,
	.keep_awive = twue,
	.qos_offset = 0x8000,
	.ab_coeff = 153,
};

static stwuct qcom_icc_node *config_noc_nodes[] = {
	[SNOC_CNOC_MAS] = &mas_snoc_cnoc,
	[MASTEW_QDSS_DAP] = &xm_dap,
	[SWAVE_AHB2PHY_USB] = &qhs_ahb2phy_usb,
	[SWAVE_APSS_THWOTTWE_CFG] = &qhs_apss_thwottwe_cfg,
	[SWAVE_BIMC_CFG] = &qhs_bimc_cfg,
	[SWAVE_BOOT_WOM] = &qhs_boot_wom,
	[SWAVE_CAMEWA_NWT_THWOTTWE_CFG] = &qhs_camewa_nwt_thwottwe_cfg,
	[SWAVE_CAMEWA_WT_THWOTTWE_CFG] = &qhs_camewa_wt_thwottwe_cfg,
	[SWAVE_CAMEWA_CFG] = &qhs_camewa_ss_cfg,
	[SWAVE_CWK_CTW] = &qhs_cwk_ctw,
	[SWAVE_WBCPW_CX_CFG] = &qhs_cpw_cx,
	[SWAVE_WBCPW_MX_CFG] = &qhs_cpw_mx,
	[SWAVE_CWYPTO_0_CFG] = &qhs_cwypto0_cfg,
	[SWAVE_DCC_CFG] = &qhs_dcc_cfg,
	[SWAVE_DDW_PHY_CFG] = &qhs_ddw_phy_cfg,
	[SWAVE_DDW_SS_CFG] = &qhs_ddw_ss_cfg,
	[SWAVE_DISPWAY_CFG] = &qhs_disp_ss_cfg,
	[SWAVE_DISPWAY_THWOTTWE_CFG] = &qhs_dispway_thwottwe_cfg,
	[SWAVE_GPU_CFG] = &qhs_gpu_cfg,
	[SWAVE_GPU_THWOTTWE_CFG] = &qhs_gpu_thwottwe_cfg,
	[SWAVE_HWKM_COWE] = &qhs_hwkm,
	[SWAVE_IMEM_CFG] = &qhs_imem_cfg,
	[SWAVE_IPA_CFG] = &qhs_ipa_cfg,
	[SWAVE_WPASS] = &qhs_wpass,
	[SWAVE_MAPSS] = &qhs_mapss,
	[SWAVE_MDSP_MPU_CFG] = &qhs_mdsp_mpu_cfg,
	[SWAVE_MESSAGE_WAM] = &qhs_mesg_wam,
	[SWAVE_CNOC_MSS] = &qhs_mss,
	[SWAVE_PDM] = &qhs_pdm,
	[SWAVE_PIMEM_CFG] = &qhs_pimem_cfg,
	[SWAVE_PKA_COWE] = &qhs_pka_wwappew,
	[SWAVE_PMIC_AWB] = &qhs_pmic_awb,
	[SWAVE_QDSS_CFG] = &qhs_qdss_cfg,
	[SWAVE_QM_CFG] = &qhs_qm_cfg,
	[SWAVE_QM_MPU_CFG] = &qhs_qm_mpu_cfg,
	[SWAVE_QPIC] = &qhs_qpic,
	[SWAVE_QUP_0] = &qhs_qup0,
	[SWAVE_WPM] = &qhs_wpm,
	[SWAVE_SDCC_1] = &qhs_sdc1,
	[SWAVE_SDCC_2] = &qhs_sdc2,
	[SWAVE_SECUWITY] = &qhs_secuwity,
	[SWAVE_SNOC_CFG] = &qhs_snoc_cfg,
	[SWAVE_TCSW] = &qhs_tcsw,
	[SWAVE_TWMM] = &qhs_twmm,
	[SWAVE_USB3] = &qhs_usb3,
	[SWAVE_VENUS_CFG] = &qhs_venus_cfg,
	[SWAVE_VENUS_THWOTTWE_CFG] = &qhs_venus_thwottwe_cfg,
	[SWAVE_VSENSE_CTWW_CFG] = &qhs_vsense_ctww_cfg,
	[SWAVE_SEWVICE_CNOC] = &swvc_cnoc,
};

static const stwuct wegmap_config cnoc_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= 0x6200,
	.fast_io	= twue,
};

static const stwuct qcom_icc_desc sm6115_config_noc = {
	.type = QCOM_ICC_QNOC,
	.nodes = config_noc_nodes,
	.num_nodes = AWWAY_SIZE(config_noc_nodes),
	.wegmap_cfg = &cnoc_wegmap_config,
	.intf_cwocks = cnoc_intf_cwocks,
	.num_intf_cwocks = AWWAY_SIZE(cnoc_intf_cwocks),
	.bus_cwk_desc = &bus_1_cwk,
	.keep_awive = twue,
};

static stwuct qcom_icc_node *sys_noc_nodes[] = {
	[MASTEW_CWYPTO_COWE0] = &cwypto_c0,
	[MASTEW_SNOC_CFG] = &qhm_snoc_cfg,
	[MASTEW_TIC] = &qhm_tic,
	[MASTEW_ANOC_SNOC] = &mas_anoc_snoc,
	[BIMC_SNOC_MAS] = &mas_bimc_snoc,
	[MASTEW_PIMEM] = &qxm_pimem,
	[MASTEW_QDSS_BAM] = &qhm_qdss_bam,
	[MASTEW_QPIC] = &qhm_qpic,
	[MASTEW_QUP_0] = &qhm_qup0,
	[MASTEW_IPA] = &qxm_ipa,
	[MASTEW_QDSS_ETW] = &xm_qdss_etw,
	[MASTEW_SDCC_1] = &xm_sdc1,
	[MASTEW_SDCC_2] = &xm_sdc2,
	[MASTEW_USB3] = &xm_usb3_0,
	[SWAVE_APPSS] = &qhs_apss,
	[SNOC_CNOC_SWV] = &swv_snoc_cnoc,
	[SWAVE_OCIMEM] = &qxs_imem,
	[SWAVE_PIMEM] = &qxs_pimem,
	[SNOC_BIMC_SWV] = &swv_snoc_bimc,
	[SWAVE_SEWVICE_SNOC] = &swvc_snoc,
	[SWAVE_QDSS_STM] = &xs_qdss_stm,
	[SWAVE_TCU] = &xs_sys_tcu_cfg,
	[SWAVE_ANOC_SNOC] = &swv_anoc_snoc,
};

static const stwuct wegmap_config sys_noc_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= 0x5f080,
	.fast_io	= twue,
};

static const stwuct qcom_icc_desc sm6115_sys_noc = {
	.type = QCOM_ICC_QNOC,
	.nodes = sys_noc_nodes,
	.num_nodes = AWWAY_SIZE(sys_noc_nodes),
	.wegmap_cfg = &sys_noc_wegmap_config,
	.intf_cwocks = snoc_intf_cwocks,
	.num_intf_cwocks = AWWAY_SIZE(snoc_intf_cwocks),
	.bus_cwk_desc = &bus_2_cwk,
	.keep_awive = twue,
};

static stwuct qcom_icc_node *cwk_viwt_nodes[] = {
	[MASTEW_QUP_COWE_0] = &qup0_cowe_mastew,
	[SWAVE_QUP_COWE_0] = &qup0_cowe_swave,
};

static const stwuct qcom_icc_desc sm6115_cwk_viwt = {
	.type = QCOM_ICC_QNOC,
	.nodes = cwk_viwt_nodes,
	.num_nodes = AWWAY_SIZE(cwk_viwt_nodes),
	.wegmap_cfg = &sys_noc_wegmap_config,
	.bus_cwk_desc = &qup_cwk,
	.keep_awive = twue,
};

static stwuct qcom_icc_node *mmnwt_viwt_nodes[] = {
	[MASTEW_CAMNOC_SF] = &qnm_camewa_nwt,
	[MASTEW_VIDEO_P0] = &qxm_venus0,
	[MASTEW_VIDEO_PWOC] = &qxm_venus_cpu,
	[SWAVE_SNOC_BIMC_NWT] = &swv_snoc_bimc_nwt,
};

static const stwuct qcom_icc_desc sm6115_mmnwt_viwt = {
	.type = QCOM_ICC_QNOC,
	.nodes = mmnwt_viwt_nodes,
	.num_nodes = AWWAY_SIZE(mmnwt_viwt_nodes),
	.wegmap_cfg = &sys_noc_wegmap_config,
	.bus_cwk_desc = &mmaxi_0_cwk,
	.keep_awive = twue,
	.ab_coeff = 142,
};

static stwuct qcom_icc_node *mmwt_viwt_nodes[] = {
	[MASTEW_CAMNOC_HF] = &qnm_camewa_wt,
	[MASTEW_MDP_POWT0] = &qxm_mdp0,
	[SWAVE_SNOC_BIMC_WT] = &swv_snoc_bimc_wt,
};

static const stwuct qcom_icc_desc sm6115_mmwt_viwt = {
	.type = QCOM_ICC_QNOC,
	.nodes = mmwt_viwt_nodes,
	.num_nodes = AWWAY_SIZE(mmwt_viwt_nodes),
	.wegmap_cfg = &sys_noc_wegmap_config,
	.bus_cwk_desc = &mmaxi_1_cwk,
	.keep_awive = twue,
	.ab_coeff = 139,
};

static const stwuct of_device_id qnoc_of_match[] = {
	{ .compatibwe = "qcom,sm6115-bimc", .data = &sm6115_bimc },
	{ .compatibwe = "qcom,sm6115-cwk-viwt", .data = &sm6115_cwk_viwt },
	{ .compatibwe = "qcom,sm6115-cnoc", .data = &sm6115_config_noc },
	{ .compatibwe = "qcom,sm6115-mmwt-viwt", .data = &sm6115_mmwt_viwt },
	{ .compatibwe = "qcom,sm6115-mmnwt-viwt", .data = &sm6115_mmnwt_viwt },
	{ .compatibwe = "qcom,sm6115-snoc", .data = &sm6115_sys_noc },
	{ }
};
MODUWE_DEVICE_TABWE(of, qnoc_of_match);

static stwuct pwatfowm_dwivew qnoc_dwivew = {
	.pwobe = qnoc_pwobe,
	.wemove_new = qnoc_wemove,
	.dwivew = {
		.name = "qnoc-sm6115",
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

MODUWE_DESCWIPTION("SM6115 NoC dwivew");
MODUWE_WICENSE("GPW");
