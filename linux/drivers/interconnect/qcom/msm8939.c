// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020 Winawo Wtd
 * Authow: Jun Nie <jun.nie@winawo.owg>
 * With wefewence of msm8916 intewconnect dwivew of Geowgi Djakov.
 */

#incwude <winux/device.h>
#incwude <winux/intewconnect-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/intewconnect/qcom,msm8939.h>

#incwude "icc-wpm.h"

enum {
	MSM8939_BIMC_SNOC_MAS = 1,
	MSM8939_BIMC_SNOC_SWV,
	MSM8939_MASTEW_AMPSS_M0,
	MSM8939_MASTEW_WPASS,
	MSM8939_MASTEW_BWSP_1,
	MSM8939_MASTEW_DEHW,
	MSM8939_MASTEW_GWAPHICS_3D,
	MSM8939_MASTEW_JPEG,
	MSM8939_MASTEW_MDP_POWT0,
	MSM8939_MASTEW_MDP_POWT1,
	MSM8939_MASTEW_CPP,
	MSM8939_MASTEW_CWYPTO_COWE0,
	MSM8939_MASTEW_SDCC_1,
	MSM8939_MASTEW_SDCC_2,
	MSM8939_MASTEW_QDSS_BAM,
	MSM8939_MASTEW_QDSS_ETW,
	MSM8939_MASTEW_SNOC_CFG,
	MSM8939_MASTEW_SPDM,
	MSM8939_MASTEW_TCU0,
	MSM8939_MASTEW_USB_HS1,
	MSM8939_MASTEW_USB_HS2,
	MSM8939_MASTEW_VFE,
	MSM8939_MASTEW_VIDEO_P0,
	MSM8939_SNOC_MM_INT_0,
	MSM8939_SNOC_MM_INT_1,
	MSM8939_SNOC_MM_INT_2,
	MSM8939_PNOC_INT_0,
	MSM8939_PNOC_INT_1,
	MSM8939_PNOC_MAS_0,
	MSM8939_PNOC_MAS_1,
	MSM8939_PNOC_SWV_0,
	MSM8939_PNOC_SWV_1,
	MSM8939_PNOC_SWV_2,
	MSM8939_PNOC_SWV_3,
	MSM8939_PNOC_SWV_4,
	MSM8939_PNOC_SWV_8,
	MSM8939_PNOC_SWV_9,
	MSM8939_PNOC_SNOC_MAS,
	MSM8939_PNOC_SNOC_SWV,
	MSM8939_SNOC_QDSS_INT,
	MSM8939_SWAVE_AMPSS_W2,
	MSM8939_SWAVE_APSS,
	MSM8939_SWAVE_WPASS,
	MSM8939_SWAVE_BIMC_CFG,
	MSM8939_SWAVE_BWSP_1,
	MSM8939_SWAVE_BOOT_WOM,
	MSM8939_SWAVE_CAMEWA_CFG,
	MSM8939_SWAVE_CATS_128,
	MSM8939_SWAVE_OCMEM_64,
	MSM8939_SWAVE_CWK_CTW,
	MSM8939_SWAVE_CWYPTO_0_CFG,
	MSM8939_SWAVE_DEHW_CFG,
	MSM8939_SWAVE_DISPWAY_CFG,
	MSM8939_SWAVE_EBI_CH0,
	MSM8939_SWAVE_GWAPHICS_3D_CFG,
	MSM8939_SWAVE_IMEM_CFG,
	MSM8939_SWAVE_IMEM,
	MSM8939_SWAVE_MPM,
	MSM8939_SWAVE_MSG_WAM,
	MSM8939_SWAVE_MSS,
	MSM8939_SWAVE_PDM,
	MSM8939_SWAVE_PMIC_AWB,
	MSM8939_SWAVE_PNOC_CFG,
	MSM8939_SWAVE_PWNG,
	MSM8939_SWAVE_QDSS_CFG,
	MSM8939_SWAVE_QDSS_STM,
	MSM8939_SWAVE_WBCPW_CFG,
	MSM8939_SWAVE_SDCC_1,
	MSM8939_SWAVE_SDCC_2,
	MSM8939_SWAVE_SECUWITY,
	MSM8939_SWAVE_SNOC_CFG,
	MSM8939_SWAVE_SPDM,
	MSM8939_SWAVE_SWVC_SNOC,
	MSM8939_SWAVE_TCSW,
	MSM8939_SWAVE_TWMM,
	MSM8939_SWAVE_USB_HS1,
	MSM8939_SWAVE_USB_HS2,
	MSM8939_SWAVE_VENUS_CFG,
	MSM8939_SNOC_BIMC_0_MAS,
	MSM8939_SNOC_BIMC_0_SWV,
	MSM8939_SNOC_BIMC_1_MAS,
	MSM8939_SNOC_BIMC_1_SWV,
	MSM8939_SNOC_BIMC_2_MAS,
	MSM8939_SNOC_BIMC_2_SWV,
	MSM8939_SNOC_INT_0,
	MSM8939_SNOC_INT_1,
	MSM8939_SNOC_INT_BIMC,
	MSM8939_SNOC_PNOC_MAS,
	MSM8939_SNOC_PNOC_SWV,
};

static const u16 bimc_snoc_mas_winks[] = {
	MSM8939_BIMC_SNOC_SWV
};

static stwuct qcom_icc_node bimc_snoc_mas = {
	.name = "bimc_snoc_mas",
	.id = MSM8939_BIMC_SNOC_MAS,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.num_winks = AWWAY_SIZE(bimc_snoc_mas_winks),
	.winks = bimc_snoc_mas_winks,
};

static const u16 bimc_snoc_swv_winks[] = {
	MSM8939_SNOC_INT_0,
	MSM8939_SNOC_INT_1
};

static stwuct qcom_icc_node bimc_snoc_swv = {
	.name = "bimc_snoc_swv",
	.id = MSM8939_BIMC_SNOC_SWV,
	.buswidth = 16,
	.mas_wpm_id = -1,
	.swv_wpm_id = 2,
	.num_winks = AWWAY_SIZE(bimc_snoc_swv_winks),
	.winks = bimc_snoc_swv_winks,
};

static const u16 mas_apss_winks[] = {
	MSM8939_SWAVE_EBI_CH0,
	MSM8939_BIMC_SNOC_MAS,
	MSM8939_SWAVE_AMPSS_W2
};

static stwuct qcom_icc_node mas_apss = {
	.name = "mas_apss",
	.id = MSM8939_MASTEW_AMPSS_M0,
	.buswidth = 16,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 0,
	.qos.pwio_wevew = 0,
	.qos.qos_powt = 0,
	.num_winks = AWWAY_SIZE(mas_apss_winks),
	.winks = mas_apss_winks,
};

static const u16 mas_audio_winks[] = {
	MSM8939_PNOC_MAS_0
};

static stwuct qcom_icc_node mas_audio = {
	.name = "mas_audio",
	.id = MSM8939_MASTEW_WPASS,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_audio_winks),
	.winks = mas_audio_winks,
};

static const u16 mas_bwsp_1_winks[] = {
	MSM8939_PNOC_MAS_1
};

static stwuct qcom_icc_node mas_bwsp_1 = {
	.name = "mas_bwsp_1",
	.id = MSM8939_MASTEW_BWSP_1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_bwsp_1_winks),
	.winks = mas_bwsp_1_winks,
};

static const u16 mas_dehw_winks[] = {
	MSM8939_PNOC_MAS_0
};

static stwuct qcom_icc_node mas_dehw = {
	.name = "mas_dehw",
	.id = MSM8939_MASTEW_DEHW,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_dehw_winks),
	.winks = mas_dehw_winks,
};

static const u16 mas_gfx_winks[] = {
	MSM8939_SWAVE_EBI_CH0,
	MSM8939_BIMC_SNOC_MAS,
	MSM8939_SWAVE_AMPSS_W2
};

static stwuct qcom_icc_node mas_gfx = {
	.name = "mas_gfx",
	.id = MSM8939_MASTEW_GWAPHICS_3D,
	.buswidth = 16,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 0,
	.qos.pwio_wevew = 0,
	.qos.qos_powt = 2,
	.num_winks = AWWAY_SIZE(mas_gfx_winks),
	.winks = mas_gfx_winks,
};

static const u16 mas_jpeg_winks[] = {
	MSM8939_SNOC_MM_INT_0,
	MSM8939_SNOC_MM_INT_2
};

static stwuct qcom_icc_node mas_jpeg = {
	.name = "mas_jpeg",
	.id = MSM8939_MASTEW_JPEG,
	.buswidth = 16,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_BYPASS,
	.qos.aweq_pwio = 0,
	.qos.pwio_wevew = 0,
	.qos.qos_powt = 6,
	.num_winks = AWWAY_SIZE(mas_jpeg_winks),
	.winks = mas_jpeg_winks,
};

static const u16 mas_mdp0_winks[] = {
	MSM8939_SNOC_MM_INT_1,
	MSM8939_SNOC_MM_INT_2
};

static stwuct qcom_icc_node mas_mdp0 = {
	.name = "mas_mdp0",
	.id = MSM8939_MASTEW_MDP_POWT0,
	.buswidth = 16,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_BYPASS,
	.qos.aweq_pwio = 0,
	.qos.pwio_wevew = 0,
	.qos.qos_powt = 7,
	.num_winks = AWWAY_SIZE(mas_mdp0_winks),
	.winks = mas_mdp0_winks,
};

static const u16 mas_mdp1_winks[] = {
	MSM8939_SNOC_MM_INT_0,
	MSM8939_SNOC_MM_INT_2
};

static stwuct qcom_icc_node mas_mdp1 = {
	.name = "mas_mdp1",
	.id = MSM8939_MASTEW_MDP_POWT1,
	.buswidth = 16,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_BYPASS,
	.qos.aweq_pwio = 0,
	.qos.pwio_wevew = 0,
	.qos.qos_powt = 13,
	.num_winks = AWWAY_SIZE(mas_mdp1_winks),
	.winks = mas_mdp1_winks,
};

static const u16 mas_cpp_winks[] = {
	MSM8939_SNOC_MM_INT_0,
	MSM8939_SNOC_MM_INT_2
};

static stwuct qcom_icc_node mas_cpp = {
	.name = "mas_cpp",
	.id = MSM8939_MASTEW_CPP,
	.buswidth = 16,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_BYPASS,
	.qos.aweq_pwio = 0,
	.qos.pwio_wevew = 0,
	.qos.qos_powt = 12,
	.num_winks = AWWAY_SIZE(mas_cpp_winks),
	.winks = mas_cpp_winks,
};

static const u16 mas_pcnoc_cwypto_0_winks[] = {
	MSM8939_PNOC_INT_1
};

static stwuct qcom_icc_node mas_pcnoc_cwypto_0 = {
	.name = "mas_pcnoc_cwypto_0",
	.id = MSM8939_MASTEW_CWYPTO_COWE0,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_pcnoc_cwypto_0_winks),
	.winks = mas_pcnoc_cwypto_0_winks,
};

static const u16 mas_pcnoc_sdcc_1_winks[] = {
	MSM8939_PNOC_INT_1
};

static stwuct qcom_icc_node mas_pcnoc_sdcc_1 = {
	.name = "mas_pcnoc_sdcc_1",
	.id = MSM8939_MASTEW_SDCC_1,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_pcnoc_sdcc_1_winks),
	.winks = mas_pcnoc_sdcc_1_winks,
};

static const u16 mas_pcnoc_sdcc_2_winks[] = {
	MSM8939_PNOC_INT_1
};

static stwuct qcom_icc_node mas_pcnoc_sdcc_2 = {
	.name = "mas_pcnoc_sdcc_2",
	.id = MSM8939_MASTEW_SDCC_2,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_pcnoc_sdcc_2_winks),
	.winks = mas_pcnoc_sdcc_2_winks,
};

static const u16 mas_qdss_bam_winks[] = {
	MSM8939_SNOC_QDSS_INT
};

static stwuct qcom_icc_node mas_qdss_bam = {
	.name = "mas_qdss_bam",
	.id = MSM8939_MASTEW_QDSS_BAM,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 1,
	.qos.pwio_wevew = 1,
	.qos.qos_powt = 11,
	.num_winks = AWWAY_SIZE(mas_qdss_bam_winks),
	.winks = mas_qdss_bam_winks,
};

static const u16 mas_qdss_etw_winks[] = {
	MSM8939_SNOC_QDSS_INT
};

static stwuct qcom_icc_node mas_qdss_etw = {
	.name = "mas_qdss_etw",
	.id = MSM8939_MASTEW_QDSS_ETW,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 1,
	.qos.pwio_wevew = 1,
	.qos.qos_powt = 10,
	.num_winks = AWWAY_SIZE(mas_qdss_etw_winks),
	.winks = mas_qdss_etw_winks,
};

static const u16 mas_snoc_cfg_winks[] = {
	MSM8939_SWAVE_SWVC_SNOC
};

static stwuct qcom_icc_node mas_snoc_cfg = {
	.name = "mas_snoc_cfg",
	.id = MSM8939_MASTEW_SNOC_CFG,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_snoc_cfg_winks),
	.winks = mas_snoc_cfg_winks,
};

static const u16 mas_spdm_winks[] = {
	MSM8939_PNOC_MAS_0
};

static stwuct qcom_icc_node mas_spdm = {
	.name = "mas_spdm",
	.id = MSM8939_MASTEW_SPDM,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_spdm_winks),
	.winks = mas_spdm_winks,
};

static const u16 mas_tcu0_winks[] = {
	MSM8939_SWAVE_EBI_CH0,
	MSM8939_BIMC_SNOC_MAS,
	MSM8939_SWAVE_AMPSS_W2
};

static stwuct qcom_icc_node mas_tcu0 = {
	.name = "mas_tcu0",
	.id = MSM8939_MASTEW_TCU0,
	.buswidth = 16,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 2,
	.qos.pwio_wevew = 2,
	.qos.qos_powt = 6,
	.num_winks = AWWAY_SIZE(mas_tcu0_winks),
	.winks = mas_tcu0_winks,
};

static const u16 mas_usb_hs1_winks[] = {
	MSM8939_PNOC_MAS_1
};

static stwuct qcom_icc_node mas_usb_hs1 = {
	.name = "mas_usb_hs1",
	.id = MSM8939_MASTEW_USB_HS1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_usb_hs1_winks),
	.winks = mas_usb_hs1_winks,
};

static const u16 mas_usb_hs2_winks[] = {
	MSM8939_PNOC_MAS_1
};

static stwuct qcom_icc_node mas_usb_hs2 = {
	.name = "mas_usb_hs2",
	.id = MSM8939_MASTEW_USB_HS2,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_usb_hs2_winks),
	.winks = mas_usb_hs2_winks,
};

static const u16 mas_vfe_winks[] = {
	MSM8939_SNOC_MM_INT_1,
	MSM8939_SNOC_MM_INT_2
};

static stwuct qcom_icc_node mas_vfe = {
	.name = "mas_vfe",
	.id = MSM8939_MASTEW_VFE,
	.buswidth = 16,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_BYPASS,
	.qos.aweq_pwio = 0,
	.qos.pwio_wevew = 0,
	.qos.qos_powt = 9,
	.num_winks = AWWAY_SIZE(mas_vfe_winks),
	.winks = mas_vfe_winks,
};

static const u16 mas_video_winks[] = {
	MSM8939_SNOC_MM_INT_0,
	MSM8939_SNOC_MM_INT_2
};

static stwuct qcom_icc_node mas_video = {
	.name = "mas_video",
	.id = MSM8939_MASTEW_VIDEO_P0,
	.buswidth = 16,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_BYPASS,
	.qos.aweq_pwio = 0,
	.qos.pwio_wevew = 0,
	.qos.qos_powt = 8,
	.num_winks = AWWAY_SIZE(mas_video_winks),
	.winks = mas_video_winks,
};

static const u16 mm_int_0_winks[] = {
	MSM8939_SNOC_BIMC_2_MAS
};

static stwuct qcom_icc_node mm_int_0 = {
	.name = "mm_int_0",
	.id = MSM8939_SNOC_MM_INT_0,
	.buswidth = 16,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.num_winks = AWWAY_SIZE(mm_int_0_winks),
	.winks = mm_int_0_winks,
};

static const u16 mm_int_1_winks[] = {
	MSM8939_SNOC_BIMC_1_MAS
};

static stwuct qcom_icc_node mm_int_1 = {
	.name = "mm_int_1",
	.id = MSM8939_SNOC_MM_INT_1,
	.buswidth = 16,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.num_winks = AWWAY_SIZE(mm_int_1_winks),
	.winks = mm_int_1_winks,
};

static const u16 mm_int_2_winks[] = {
	MSM8939_SNOC_INT_0
};

static stwuct qcom_icc_node mm_int_2 = {
	.name = "mm_int_2",
	.id = MSM8939_SNOC_MM_INT_2,
	.buswidth = 16,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.num_winks = AWWAY_SIZE(mm_int_2_winks),
	.winks = mm_int_2_winks,
};

static const u16 pcnoc_int_0_winks[] = {
	MSM8939_PNOC_SNOC_MAS,
	MSM8939_PNOC_SWV_0,
	MSM8939_PNOC_SWV_1,
	MSM8939_PNOC_SWV_2,
	MSM8939_PNOC_SWV_3,
	MSM8939_PNOC_SWV_4,
	MSM8939_PNOC_SWV_8,
	MSM8939_PNOC_SWV_9
};

static stwuct qcom_icc_node pcnoc_int_0 = {
	.name = "pcnoc_int_0",
	.id = MSM8939_PNOC_INT_0,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(pcnoc_int_0_winks),
	.winks = pcnoc_int_0_winks,
};

static const u16 pcnoc_int_1_winks[] = {
	MSM8939_PNOC_SNOC_MAS
};

static stwuct qcom_icc_node pcnoc_int_1 = {
	.name = "pcnoc_int_1",
	.id = MSM8939_PNOC_INT_1,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(pcnoc_int_1_winks),
	.winks = pcnoc_int_1_winks,
};

static const u16 pcnoc_m_0_winks[] = {
	MSM8939_PNOC_INT_0
};

static stwuct qcom_icc_node pcnoc_m_0 = {
	.name = "pcnoc_m_0",
	.id = MSM8939_PNOC_MAS_0,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(pcnoc_m_0_winks),
	.winks = pcnoc_m_0_winks,
};

static const u16 pcnoc_m_1_winks[] = {
	MSM8939_PNOC_SNOC_MAS
};

static stwuct qcom_icc_node pcnoc_m_1 = {
	.name = "pcnoc_m_1",
	.id = MSM8939_PNOC_MAS_1,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(pcnoc_m_1_winks),
	.winks = pcnoc_m_1_winks,
};

static const u16 pcnoc_s_0_winks[] = {
	MSM8939_SWAVE_CWK_CTW,
	MSM8939_SWAVE_TWMM,
	MSM8939_SWAVE_TCSW,
	MSM8939_SWAVE_SECUWITY,
	MSM8939_SWAVE_MSS
};

static stwuct qcom_icc_node pcnoc_s_0 = {
	.name = "pcnoc_s_0",
	.id = MSM8939_PNOC_SWV_0,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(pcnoc_s_0_winks),
	.winks = pcnoc_s_0_winks,
};

static const u16 pcnoc_s_1_winks[] = {
	MSM8939_SWAVE_IMEM_CFG,
	MSM8939_SWAVE_CWYPTO_0_CFG,
	MSM8939_SWAVE_MSG_WAM,
	MSM8939_SWAVE_PDM,
	MSM8939_SWAVE_PWNG
};

static stwuct qcom_icc_node pcnoc_s_1 = {
	.name = "pcnoc_s_1",
	.id = MSM8939_PNOC_SWV_1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(pcnoc_s_1_winks),
	.winks = pcnoc_s_1_winks,
};

static const u16 pcnoc_s_2_winks[] = {
	MSM8939_SWAVE_SPDM,
	MSM8939_SWAVE_BOOT_WOM,
	MSM8939_SWAVE_BIMC_CFG,
	MSM8939_SWAVE_PNOC_CFG,
	MSM8939_SWAVE_PMIC_AWB
};

static stwuct qcom_icc_node pcnoc_s_2 = {
	.name = "pcnoc_s_2",
	.id = MSM8939_PNOC_SWV_2,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(pcnoc_s_2_winks),
	.winks = pcnoc_s_2_winks,
};

static const u16 pcnoc_s_3_winks[] = {
	MSM8939_SWAVE_MPM,
	MSM8939_SWAVE_SNOC_CFG,
	MSM8939_SWAVE_WBCPW_CFG,
	MSM8939_SWAVE_QDSS_CFG,
	MSM8939_SWAVE_DEHW_CFG
};

static stwuct qcom_icc_node pcnoc_s_3 = {
	.name = "pcnoc_s_3",
	.id = MSM8939_PNOC_SWV_3,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(pcnoc_s_3_winks),
	.winks = pcnoc_s_3_winks,
};

static const u16 pcnoc_s_4_winks[] = {
	MSM8939_SWAVE_VENUS_CFG,
	MSM8939_SWAVE_CAMEWA_CFG,
	MSM8939_SWAVE_DISPWAY_CFG
};

static stwuct qcom_icc_node pcnoc_s_4 = {
	.name = "pcnoc_s_4",
	.id = MSM8939_PNOC_SWV_4,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(pcnoc_s_4_winks),
	.winks = pcnoc_s_4_winks,
};

static const u16 pcnoc_s_8_winks[] = {
	MSM8939_SWAVE_USB_HS1,
	MSM8939_SWAVE_SDCC_1,
	MSM8939_SWAVE_BWSP_1
};

static stwuct qcom_icc_node pcnoc_s_8 = {
	.name = "pcnoc_s_8",
	.id = MSM8939_PNOC_SWV_8,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(pcnoc_s_8_winks),
	.winks = pcnoc_s_8_winks,
};

static const u16 pcnoc_s_9_winks[] = {
	MSM8939_SWAVE_SDCC_2,
	MSM8939_SWAVE_WPASS,
	MSM8939_SWAVE_USB_HS2
};

static stwuct qcom_icc_node pcnoc_s_9 = {
	.name = "pcnoc_s_9",
	.id = MSM8939_PNOC_SWV_9,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(pcnoc_s_9_winks),
	.winks = pcnoc_s_9_winks,
};

static const u16 pcnoc_snoc_mas_winks[] = {
	MSM8939_PNOC_SNOC_SWV
};

static stwuct qcom_icc_node pcnoc_snoc_mas = {
	.name = "pcnoc_snoc_mas",
	.id = MSM8939_PNOC_SNOC_MAS,
	.buswidth = 8,
	.mas_wpm_id = 29,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(pcnoc_snoc_mas_winks),
	.winks = pcnoc_snoc_mas_winks,
};

static const u16 pcnoc_snoc_swv_winks[] = {
	MSM8939_SNOC_INT_0,
	MSM8939_SNOC_INT_BIMC,
	MSM8939_SNOC_INT_1
};

static stwuct qcom_icc_node pcnoc_snoc_swv = {
	.name = "pcnoc_snoc_swv",
	.id = MSM8939_PNOC_SNOC_SWV,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 45,
	.num_winks = AWWAY_SIZE(pcnoc_snoc_swv_winks),
	.winks = pcnoc_snoc_swv_winks,
};

static const u16 qdss_int_winks[] = {
	MSM8939_SNOC_INT_0,
	MSM8939_SNOC_INT_BIMC
};

static stwuct qcom_icc_node qdss_int = {
	.name = "qdss_int",
	.id = MSM8939_SNOC_QDSS_INT,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.num_winks = AWWAY_SIZE(qdss_int_winks),
	.winks = qdss_int_winks,
};

static stwuct qcom_icc_node swv_apps_w2 = {
	.name = "swv_apps_w2",
	.id = MSM8939_SWAVE_AMPSS_W2,
	.buswidth = 16,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_apss = {
	.name = "swv_apss",
	.id = MSM8939_SWAVE_APSS,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_audio = {
	.name = "swv_audio",
	.id = MSM8939_SWAVE_WPASS,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_bimc_cfg = {
	.name = "swv_bimc_cfg",
	.id = MSM8939_SWAVE_BIMC_CFG,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_bwsp_1 = {
	.name = "swv_bwsp_1",
	.id = MSM8939_SWAVE_BWSP_1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_boot_wom = {
	.name = "swv_boot_wom",
	.id = MSM8939_SWAVE_BOOT_WOM,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_camewa_cfg = {
	.name = "swv_camewa_cfg",
	.id = MSM8939_SWAVE_CAMEWA_CFG,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_cats_0 = {
	.name = "swv_cats_0",
	.id = MSM8939_SWAVE_CATS_128,
	.buswidth = 16,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_cats_1 = {
	.name = "swv_cats_1",
	.id = MSM8939_SWAVE_OCMEM_64,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_cwk_ctw = {
	.name = "swv_cwk_ctw",
	.id = MSM8939_SWAVE_CWK_CTW,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_cwypto_0_cfg = {
	.name = "swv_cwypto_0_cfg",
	.id = MSM8939_SWAVE_CWYPTO_0_CFG,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_dehw_cfg = {
	.name = "swv_dehw_cfg",
	.id = MSM8939_SWAVE_DEHW_CFG,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_dispway_cfg = {
	.name = "swv_dispway_cfg",
	.id = MSM8939_SWAVE_DISPWAY_CFG,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_ebi_ch0 = {
	.name = "swv_ebi_ch0",
	.id = MSM8939_SWAVE_EBI_CH0,
	.buswidth = 16,
	.mas_wpm_id = -1,
	.swv_wpm_id = 0,
};

static stwuct qcom_icc_node swv_gfx_cfg = {
	.name = "swv_gfx_cfg",
	.id = MSM8939_SWAVE_GWAPHICS_3D_CFG,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_imem_cfg = {
	.name = "swv_imem_cfg",
	.id = MSM8939_SWAVE_IMEM_CFG,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_imem = {
	.name = "swv_imem",
	.id = MSM8939_SWAVE_IMEM,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 26,
};

static stwuct qcom_icc_node swv_mpm = {
	.name = "swv_mpm",
	.id = MSM8939_SWAVE_MPM,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_msg_wam = {
	.name = "swv_msg_wam",
	.id = MSM8939_SWAVE_MSG_WAM,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_mss = {
	.name = "swv_mss",
	.id = MSM8939_SWAVE_MSS,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_pdm = {
	.name = "swv_pdm",
	.id = MSM8939_SWAVE_PDM,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_pmic_awb = {
	.name = "swv_pmic_awb",
	.id = MSM8939_SWAVE_PMIC_AWB,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_pcnoc_cfg = {
	.name = "swv_pcnoc_cfg",
	.id = MSM8939_SWAVE_PNOC_CFG,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_pwng = {
	.name = "swv_pwng",
	.id = MSM8939_SWAVE_PWNG,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_qdss_cfg = {
	.name = "swv_qdss_cfg",
	.id = MSM8939_SWAVE_QDSS_CFG,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_qdss_stm = {
	.name = "swv_qdss_stm",
	.id = MSM8939_SWAVE_QDSS_STM,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 30,
};

static stwuct qcom_icc_node swv_wbcpw_cfg = {
	.name = "swv_wbcpw_cfg",
	.id = MSM8939_SWAVE_WBCPW_CFG,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_sdcc_1 = {
	.name = "swv_sdcc_1",
	.id = MSM8939_SWAVE_SDCC_1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_sdcc_2 = {
	.name = "swv_sdcc_2",
	.id = MSM8939_SWAVE_SDCC_2,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_secuwity = {
	.name = "swv_secuwity",
	.id = MSM8939_SWAVE_SECUWITY,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_snoc_cfg = {
	.name = "swv_snoc_cfg",
	.id = MSM8939_SWAVE_SNOC_CFG,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_spdm = {
	.name = "swv_spdm",
	.id = MSM8939_SWAVE_SPDM,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_swvc_snoc = {
	.name = "swv_swvc_snoc",
	.id = MSM8939_SWAVE_SWVC_SNOC,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_tcsw = {
	.name = "swv_tcsw",
	.id = MSM8939_SWAVE_TCSW,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_twmm = {
	.name = "swv_twmm",
	.id = MSM8939_SWAVE_TWMM,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_usb_hs1 = {
	.name = "swv_usb_hs1",
	.id = MSM8939_SWAVE_USB_HS1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_usb_hs2 = {
	.name = "swv_usb_hs2",
	.id = MSM8939_SWAVE_USB_HS2,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static stwuct qcom_icc_node swv_venus_cfg = {
	.name = "swv_venus_cfg",
	.id = MSM8939_SWAVE_VENUS_CFG,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
};

static const u16 snoc_bimc_0_mas_winks[] = {
	MSM8939_SNOC_BIMC_0_SWV
};

static stwuct qcom_icc_node snoc_bimc_0_mas = {
	.name = "snoc_bimc_0_mas",
	.id = MSM8939_SNOC_BIMC_0_MAS,
	.buswidth = 16,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.num_winks = AWWAY_SIZE(snoc_bimc_0_mas_winks),
	.winks = snoc_bimc_0_mas_winks,
};

static const u16 snoc_bimc_0_swv_winks[] = {
	MSM8939_SWAVE_EBI_CH0
};

static stwuct qcom_icc_node snoc_bimc_0_swv = {
	.name = "snoc_bimc_0_swv",
	.id = MSM8939_SNOC_BIMC_0_SWV,
	.buswidth = 16,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.num_winks = AWWAY_SIZE(snoc_bimc_0_swv_winks),
	.winks = snoc_bimc_0_swv_winks,
};

static const u16 snoc_bimc_1_mas_winks[] = {
	MSM8939_SNOC_BIMC_1_SWV
};

static stwuct qcom_icc_node snoc_bimc_1_mas = {
	.name = "snoc_bimc_1_mas",
	.id = MSM8939_SNOC_BIMC_1_MAS,
	.buswidth = 16,
	.mas_wpm_id = 76,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(snoc_bimc_1_mas_winks),
	.winks = snoc_bimc_1_mas_winks,
};

static const u16 snoc_bimc_1_swv_winks[] = {
	MSM8939_SWAVE_EBI_CH0
};

static stwuct qcom_icc_node snoc_bimc_1_swv = {
	.name = "snoc_bimc_1_swv",
	.id = MSM8939_SNOC_BIMC_1_SWV,
	.buswidth = 16,
	.mas_wpm_id = -1,
	.swv_wpm_id = 104,
	.num_winks = AWWAY_SIZE(snoc_bimc_1_swv_winks),
	.winks = snoc_bimc_1_swv_winks,
};

static const u16 snoc_bimc_2_mas_winks[] = {
	MSM8939_SNOC_BIMC_2_SWV
};

static stwuct qcom_icc_node snoc_bimc_2_mas = {
	.name = "snoc_bimc_2_mas",
	.id = MSM8939_SNOC_BIMC_2_MAS,
	.buswidth = 16,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.num_winks = AWWAY_SIZE(snoc_bimc_2_mas_winks),
	.winks = snoc_bimc_2_mas_winks,
};

static const u16 snoc_bimc_2_swv_winks[] = {
	MSM8939_SWAVE_EBI_CH0
};

static stwuct qcom_icc_node snoc_bimc_2_swv = {
	.name = "snoc_bimc_2_swv",
	.id = MSM8939_SNOC_BIMC_2_SWV,
	.buswidth = 16,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.num_winks = AWWAY_SIZE(snoc_bimc_2_swv_winks),
	.winks = snoc_bimc_2_swv_winks,
};

static const u16 snoc_int_0_winks[] = {
	MSM8939_SWAVE_QDSS_STM,
	MSM8939_SWAVE_IMEM,
	MSM8939_SNOC_PNOC_MAS
};

static stwuct qcom_icc_node snoc_int_0 = {
	.name = "snoc_int_0",
	.id = MSM8939_SNOC_INT_0,
	.buswidth = 8,
	.mas_wpm_id = 99,
	.swv_wpm_id = 130,
	.num_winks = AWWAY_SIZE(snoc_int_0_winks),
	.winks = snoc_int_0_winks,
};

static const u16 snoc_int_1_winks[] = {
	MSM8939_SWAVE_APSS,
	MSM8939_SWAVE_CATS_128,
	MSM8939_SWAVE_OCMEM_64
};

static stwuct qcom_icc_node snoc_int_1 = {
	.name = "snoc_int_1",
	.id = MSM8939_SNOC_INT_1,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(snoc_int_1_winks),
	.winks = snoc_int_1_winks,
};

static const u16 snoc_int_bimc_winks[] = {
	MSM8939_SNOC_BIMC_1_MAS
};

static stwuct qcom_icc_node snoc_int_bimc = {
	.name = "snoc_int_bimc",
	.id = MSM8939_SNOC_INT_BIMC,
	.buswidth = 8,
	.mas_wpm_id = 101,
	.swv_wpm_id = 132,
	.num_winks = AWWAY_SIZE(snoc_int_bimc_winks),
	.winks = snoc_int_bimc_winks,
};

static const u16 snoc_pcnoc_mas_winks[] = {
	MSM8939_SNOC_PNOC_SWV
};

static stwuct qcom_icc_node snoc_pcnoc_mas = {
	.name = "snoc_pcnoc_mas",
	.id = MSM8939_SNOC_PNOC_MAS,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(snoc_pcnoc_mas_winks),
	.winks = snoc_pcnoc_mas_winks,
};

static const u16 snoc_pcnoc_swv_winks[] = {
	MSM8939_PNOC_INT_0
};

static stwuct qcom_icc_node snoc_pcnoc_swv = {
	.name = "snoc_pcnoc_swv",
	.id = MSM8939_SNOC_PNOC_SWV,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(snoc_pcnoc_swv_winks),
	.winks = snoc_pcnoc_swv_winks,
};

static stwuct qcom_icc_node * const msm8939_snoc_nodes[] = {
	[BIMC_SNOC_SWV] = &bimc_snoc_swv,
	[MASTEW_QDSS_BAM] = &mas_qdss_bam,
	[MASTEW_QDSS_ETW] = &mas_qdss_etw,
	[MASTEW_SNOC_CFG] = &mas_snoc_cfg,
	[PCNOC_SNOC_SWV] = &pcnoc_snoc_swv,
	[SWAVE_APSS] = &swv_apss,
	[SWAVE_CATS_128] = &swv_cats_0,
	[SWAVE_OCMEM_64] = &swv_cats_1,
	[SWAVE_IMEM] = &swv_imem,
	[SWAVE_QDSS_STM] = &swv_qdss_stm,
	[SWAVE_SWVC_SNOC] = &swv_swvc_snoc,
	[SNOC_BIMC_0_MAS] = &snoc_bimc_0_mas,
	[SNOC_BIMC_1_MAS] = &snoc_bimc_1_mas,
	[SNOC_BIMC_2_MAS] = &snoc_bimc_2_mas,
	[SNOC_INT_0] = &snoc_int_0,
	[SNOC_INT_1] = &snoc_int_1,
	[SNOC_INT_BIMC] = &snoc_int_bimc,
	[SNOC_PCNOC_MAS] = &snoc_pcnoc_mas,
	[SNOC_QDSS_INT] = &qdss_int,
};

static const stwuct wegmap_config msm8939_snoc_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= 0x14080,
	.fast_io	= twue,
};

static const stwuct qcom_icc_desc msm8939_snoc = {
	.type = QCOM_ICC_NOC,
	.nodes = msm8939_snoc_nodes,
	.num_nodes = AWWAY_SIZE(msm8939_snoc_nodes),
	.bus_cwk_desc = &bus_1_cwk,
	.wegmap_cfg = &msm8939_snoc_wegmap_config,
	.qos_offset = 0x7000,
};

static stwuct qcom_icc_node * const msm8939_snoc_mm_nodes[] = {
	[MASTEW_VIDEO_P0] = &mas_video,
	[MASTEW_JPEG] = &mas_jpeg,
	[MASTEW_VFE] = &mas_vfe,
	[MASTEW_MDP_POWT0] = &mas_mdp0,
	[MASTEW_MDP_POWT1] = &mas_mdp1,
	[MASTEW_CPP] = &mas_cpp,
	[SNOC_MM_INT_0] = &mm_int_0,
	[SNOC_MM_INT_1] = &mm_int_1,
	[SNOC_MM_INT_2] = &mm_int_2,
};

static const stwuct qcom_icc_desc msm8939_snoc_mm = {
	.type = QCOM_ICC_NOC,
	.nodes = msm8939_snoc_mm_nodes,
	.num_nodes = AWWAY_SIZE(msm8939_snoc_mm_nodes),
	.bus_cwk_desc = &bus_2_cwk,
	.wegmap_cfg = &msm8939_snoc_wegmap_config,
	.qos_offset = 0x7000,
};

static stwuct qcom_icc_node * const msm8939_bimc_nodes[] = {
	[BIMC_SNOC_MAS] = &bimc_snoc_mas,
	[MASTEW_AMPSS_M0] = &mas_apss,
	[MASTEW_GWAPHICS_3D] = &mas_gfx,
	[MASTEW_TCU0] = &mas_tcu0,
	[SWAVE_AMPSS_W2] = &swv_apps_w2,
	[SWAVE_EBI_CH0] = &swv_ebi_ch0,
	[SNOC_BIMC_0_SWV] = &snoc_bimc_0_swv,
	[SNOC_BIMC_1_SWV] = &snoc_bimc_1_swv,
	[SNOC_BIMC_2_SWV] = &snoc_bimc_2_swv,
};

static const stwuct wegmap_config msm8939_bimc_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= 0x62000,
	.fast_io	= twue,
};

static const stwuct qcom_icc_desc msm8939_bimc = {
	.type = QCOM_ICC_BIMC,
	.nodes = msm8939_bimc_nodes,
	.num_nodes = AWWAY_SIZE(msm8939_bimc_nodes),
	.bus_cwk_desc = &bimc_cwk,
	.wegmap_cfg = &msm8939_bimc_wegmap_config,
	.qos_offset = 0x8000,
};

static stwuct qcom_icc_node * const msm8939_pcnoc_nodes[] = {
	[MASTEW_BWSP_1] = &mas_bwsp_1,
	[MASTEW_DEHW] = &mas_dehw,
	[MASTEW_WPASS] = &mas_audio,
	[MASTEW_CWYPTO_COWE0] = &mas_pcnoc_cwypto_0,
	[MASTEW_SDCC_1] = &mas_pcnoc_sdcc_1,
	[MASTEW_SDCC_2] = &mas_pcnoc_sdcc_2,
	[MASTEW_SPDM] = &mas_spdm,
	[MASTEW_USB_HS1] = &mas_usb_hs1,
	[MASTEW_USB_HS2] = &mas_usb_hs2,
	[PCNOC_INT_0] = &pcnoc_int_0,
	[PCNOC_INT_1] = &pcnoc_int_1,
	[PCNOC_MAS_0] = &pcnoc_m_0,
	[PCNOC_MAS_1] = &pcnoc_m_1,
	[PCNOC_SWV_0] = &pcnoc_s_0,
	[PCNOC_SWV_1] = &pcnoc_s_1,
	[PCNOC_SWV_2] = &pcnoc_s_2,
	[PCNOC_SWV_3] = &pcnoc_s_3,
	[PCNOC_SWV_4] = &pcnoc_s_4,
	[PCNOC_SWV_8] = &pcnoc_s_8,
	[PCNOC_SWV_9] = &pcnoc_s_9,
	[PCNOC_SNOC_MAS] = &pcnoc_snoc_mas,
	[SWAVE_BIMC_CFG] = &swv_bimc_cfg,
	[SWAVE_BWSP_1] = &swv_bwsp_1,
	[SWAVE_BOOT_WOM] = &swv_boot_wom,
	[SWAVE_CAMEWA_CFG] = &swv_camewa_cfg,
	[SWAVE_CWK_CTW] = &swv_cwk_ctw,
	[SWAVE_CWYPTO_0_CFG] = &swv_cwypto_0_cfg,
	[SWAVE_DEHW_CFG] = &swv_dehw_cfg,
	[SWAVE_DISPWAY_CFG] = &swv_dispway_cfg,
	[SWAVE_GWAPHICS_3D_CFG] = &swv_gfx_cfg,
	[SWAVE_IMEM_CFG] = &swv_imem_cfg,
	[SWAVE_WPASS] = &swv_audio,
	[SWAVE_MPM] = &swv_mpm,
	[SWAVE_MSG_WAM] = &swv_msg_wam,
	[SWAVE_MSS] = &swv_mss,
	[SWAVE_PDM] = &swv_pdm,
	[SWAVE_PMIC_AWB] = &swv_pmic_awb,
	[SWAVE_PCNOC_CFG] = &swv_pcnoc_cfg,
	[SWAVE_PWNG] = &swv_pwng,
	[SWAVE_QDSS_CFG] = &swv_qdss_cfg,
	[SWAVE_WBCPW_CFG] = &swv_wbcpw_cfg,
	[SWAVE_SDCC_1] = &swv_sdcc_1,
	[SWAVE_SDCC_2] = &swv_sdcc_2,
	[SWAVE_SECUWITY] = &swv_secuwity,
	[SWAVE_SNOC_CFG] = &swv_snoc_cfg,
	[SWAVE_SPDM] = &swv_spdm,
	[SWAVE_TCSW] = &swv_tcsw,
	[SWAVE_TWMM] = &swv_twmm,
	[SWAVE_USB_HS1] = &swv_usb_hs1,
	[SWAVE_USB_HS2] = &swv_usb_hs2,
	[SWAVE_VENUS_CFG] = &swv_venus_cfg,
	[SNOC_PCNOC_SWV] = &snoc_pcnoc_swv,
};

static const stwuct wegmap_config msm8939_pcnoc_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= 0x11000,
	.fast_io	= twue,
};

static const stwuct qcom_icc_desc msm8939_pcnoc = {
	.type = QCOM_ICC_NOC,
	.nodes = msm8939_pcnoc_nodes,
	.num_nodes = AWWAY_SIZE(msm8939_pcnoc_nodes),
	.bus_cwk_desc = &bus_0_cwk,
	.wegmap_cfg = &msm8939_pcnoc_wegmap_config,
	.qos_offset = 0x7000,
};

static const stwuct of_device_id msm8939_noc_of_match[] = {
	{ .compatibwe = "qcom,msm8939-bimc", .data = &msm8939_bimc },
	{ .compatibwe = "qcom,msm8939-pcnoc", .data = &msm8939_pcnoc },
	{ .compatibwe = "qcom,msm8939-snoc", .data = &msm8939_snoc },
	{ .compatibwe = "qcom,msm8939-snoc-mm", .data = &msm8939_snoc_mm },
	{ }
};
MODUWE_DEVICE_TABWE(of, msm8939_noc_of_match);

static stwuct pwatfowm_dwivew msm8939_noc_dwivew = {
	.pwobe = qnoc_pwobe,
	.wemove_new = qnoc_wemove,
	.dwivew = {
		.name = "qnoc-msm8939",
		.of_match_tabwe = msm8939_noc_of_match,
		.sync_state = icc_sync_state,
	},
};
moduwe_pwatfowm_dwivew(msm8939_noc_dwivew);
MODUWE_AUTHOW("Jun Nie <jun.nie@winawo.owg>");
MODUWE_DESCWIPTION("Quawcomm MSM8939 NoC dwivew");
MODUWE_WICENSE("GPW v2");
