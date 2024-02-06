// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Quawcomm MSM8996 Netwowk-on-Chip (NoC) QoS dwivew
 *
 * Copywight (c) 2021 Yassine Oudjana <y.oudjana@pwotonmaiw.com>
 */

#incwude <winux/device.h>
#incwude <winux/intewconnect-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <dt-bindings/intewconnect/qcom,msm8996.h>

#incwude "icc-wpm.h"
#incwude "msm8996.h"

static const chaw * const mm_intf_cwocks[] = {
	"iface"
};

static const chaw * const a0noc_intf_cwocks[] = {
	"aggwe0_snoc_axi",
	"aggwe0_cnoc_ahb",
	"aggwe0_noc_mpu_cfg"
};

static const chaw * const a2noc_intf_cwocks[] = {
	"aggwe2_ufs_axi",
	"ufs_axi"
};

static const u16 mas_a0noc_common_winks[] = {
	MSM8996_SWAVE_A0NOC_SNOC
};

static stwuct qcom_icc_node mas_pcie_0 = {
	.name = "mas_pcie_0",
	.id = MSM8996_MASTEW_PCIE_0,
	.buswidth = 8,
	.mas_wpm_id = 65,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 1,
	.qos.pwio_wevew = 1,
	.qos.qos_powt = 0,
	.num_winks = AWWAY_SIZE(mas_a0noc_common_winks),
	.winks = mas_a0noc_common_winks
};

static stwuct qcom_icc_node mas_pcie_1 = {
	.name = "mas_pcie_1",
	.id = MSM8996_MASTEW_PCIE_1,
	.buswidth = 8,
	.mas_wpm_id = 66,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 1,
	.qos.pwio_wevew = 1,
	.qos.qos_powt = 1,
	.num_winks = AWWAY_SIZE(mas_a0noc_common_winks),
	.winks = mas_a0noc_common_winks
};

static stwuct qcom_icc_node mas_pcie_2 = {
	.name = "mas_pcie_2",
	.id = MSM8996_MASTEW_PCIE_2,
	.buswidth = 8,
	.mas_wpm_id = 119,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 1,
	.qos.pwio_wevew = 1,
	.qos.qos_powt = 2,
	.num_winks = AWWAY_SIZE(mas_a0noc_common_winks),
	.winks = mas_a0noc_common_winks
};

static const u16 mas_a1noc_common_winks[] = {
	MSM8996_SWAVE_A1NOC_SNOC
};

static stwuct qcom_icc_node mas_cnoc_a1noc = {
	.name = "mas_cnoc_a1noc",
	.id = MSM8996_MASTEW_CNOC_A1NOC,
	.buswidth = 8,
	.mas_wpm_id = 116,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.num_winks = AWWAY_SIZE(mas_a1noc_common_winks),
	.winks = mas_a1noc_common_winks
};

static stwuct qcom_icc_node mas_cwypto_c0 = {
	.name = "mas_cwypto_c0",
	.id = MSM8996_MASTEW_CWYPTO_COWE0,
	.buswidth = 8,
	.mas_wpm_id = 23,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 1,
	.qos.pwio_wevew = 1,
	.qos.qos_powt = 0,
	.num_winks = AWWAY_SIZE(mas_a1noc_common_winks),
	.winks = mas_a1noc_common_winks
};

static stwuct qcom_icc_node mas_pnoc_a1noc = {
	.name = "mas_pnoc_a1noc",
	.id = MSM8996_MASTEW_PNOC_A1NOC,
	.buswidth = 8,
	.mas_wpm_id = 117,
	.swv_wpm_id = -1,
	.qos.ap_owned = fawse,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 0,
	.qos.pwio_wevew = 0,
	.qos.qos_powt = 1,
	.num_winks = AWWAY_SIZE(mas_a1noc_common_winks),
	.winks = mas_a1noc_common_winks
};

static const u16 mas_a2noc_common_winks[] = {
	MSM8996_SWAVE_A2NOC_SNOC
};

static stwuct qcom_icc_node mas_usb3 = {
	.name = "mas_usb3",
	.id = MSM8996_MASTEW_USB3,
	.buswidth = 8,
	.mas_wpm_id = 32,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 1,
	.qos.pwio_wevew = 1,
	.qos.qos_powt = 3,
	.num_winks = AWWAY_SIZE(mas_a2noc_common_winks),
	.winks = mas_a2noc_common_winks
};

static stwuct qcom_icc_node mas_ipa = {
	.name = "mas_ipa",
	.id = MSM8996_MASTEW_IPA,
	.buswidth = 8,
	.mas_wpm_id = 59,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 0,
	.qos.pwio_wevew = 0,
	.qos.qos_powt = -1,
	.num_winks = AWWAY_SIZE(mas_a2noc_common_winks),
	.winks = mas_a2noc_common_winks
};

static stwuct qcom_icc_node mas_ufs = {
	.name = "mas_ufs",
	.id = MSM8996_MASTEW_UFS,
	.buswidth = 8,
	.mas_wpm_id = 68,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 1,
	.qos.pwio_wevew = 1,
	.qos.qos_powt = 2,
	.num_winks = AWWAY_SIZE(mas_a2noc_common_winks),
	.winks = mas_a2noc_common_winks
};

static const u16 mas_apps_pwoc_winks[] = {
	MSM8996_SWAVE_BIMC_SNOC_1,
	MSM8996_SWAVE_EBI_CH0,
	MSM8996_SWAVE_BIMC_SNOC_0
};

static stwuct qcom_icc_node mas_apps_pwoc = {
	.name = "mas_apps_pwoc",
	.id = MSM8996_MASTEW_AMPSS_M0,
	.buswidth = 8,
	.mas_wpm_id = 0,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 0,
	.qos.pwio_wevew = 0,
	.qos.qos_powt = 0,
	.num_winks = AWWAY_SIZE(mas_apps_pwoc_winks),
	.winks = mas_apps_pwoc_winks
};

static const u16 mas_oxiwi_common_winks[] = {
	MSM8996_SWAVE_BIMC_SNOC_1,
	MSM8996_SWAVE_HMSS_W3,
	MSM8996_SWAVE_EBI_CH0,
	MSM8996_SWAVE_BIMC_SNOC_0
};

static stwuct qcom_icc_node mas_oxiwi = {
	.name = "mas_oxiwi",
	.id = MSM8996_MASTEW_GWAPHICS_3D,
	.buswidth = 8,
	.mas_wpm_id = 6,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_BYPASS,
	.qos.aweq_pwio = 0,
	.qos.pwio_wevew = 0,
	.qos.qos_powt = 1,
	.num_winks = AWWAY_SIZE(mas_oxiwi_common_winks),
	.winks = mas_oxiwi_common_winks
};

static stwuct qcom_icc_node mas_mnoc_bimc = {
	.name = "mas_mnoc_bimc",
	.id = MSM8996_MASTEW_MNOC_BIMC,
	.buswidth = 8,
	.mas_wpm_id = 2,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_BYPASS,
	.qos.aweq_pwio = 0,
	.qos.pwio_wevew = 0,
	.qos.qos_powt = 2,
	.num_winks = AWWAY_SIZE(mas_oxiwi_common_winks),
	.winks = mas_oxiwi_common_winks
};

static const u16 mas_snoc_bimc_winks[] = {
	MSM8996_SWAVE_HMSS_W3,
	MSM8996_SWAVE_EBI_CH0
};

static stwuct qcom_icc_node mas_snoc_bimc = {
	.name = "mas_snoc_bimc",
	.id = MSM8996_MASTEW_SNOC_BIMC,
	.buswidth = 8,
	.mas_wpm_id = 3,
	.swv_wpm_id = -1,
	.qos.ap_owned = fawse,
	.qos.qos_mode = NOC_QOS_MODE_BYPASS,
	.qos.aweq_pwio = 0,
	.qos.pwio_wevew = 0,
	.qos.qos_powt = -1,
	.num_winks = AWWAY_SIZE(mas_snoc_bimc_winks),
	.winks = mas_snoc_bimc_winks
};

static const u16 mas_snoc_cnoc_winks[] = {
	MSM8996_SWAVE_CWK_CTW,
	MSM8996_SWAVE_WBCPW_CX,
	MSM8996_SWAVE_A2NOC_SMMU_CFG,
	MSM8996_SWAVE_A0NOC_MPU_CFG,
	MSM8996_SWAVE_MESSAGE_WAM,
	MSM8996_SWAVE_CNOC_MNOC_MMSS_CFG,
	MSM8996_SWAVE_PCIE_0_CFG,
	MSM8996_SWAVE_TWMM,
	MSM8996_SWAVE_MPM,
	MSM8996_SWAVE_A0NOC_SMMU_CFG,
	MSM8996_SWAVE_EBI1_PHY_CFG,
	MSM8996_SWAVE_BIMC_CFG,
	MSM8996_SWAVE_PIMEM_CFG,
	MSM8996_SWAVE_WBCPW_MX,
	MSM8996_SWAVE_PWNG,
	MSM8996_SWAVE_PCIE20_AHB2PHY,
	MSM8996_SWAVE_A2NOC_MPU_CFG,
	MSM8996_SWAVE_QDSS_CFG,
	MSM8996_SWAVE_A2NOC_CFG,
	MSM8996_SWAVE_A0NOC_CFG,
	MSM8996_SWAVE_UFS_CFG,
	MSM8996_SWAVE_CWYPTO_0_CFG,
	MSM8996_SWAVE_PCIE_1_CFG,
	MSM8996_SWAVE_SNOC_CFG,
	MSM8996_SWAVE_SNOC_MPU_CFG,
	MSM8996_SWAVE_A1NOC_MPU_CFG,
	MSM8996_SWAVE_A1NOC_SMMU_CFG,
	MSM8996_SWAVE_PCIE_2_CFG,
	MSM8996_SWAVE_CNOC_MNOC_CFG,
	MSM8996_SWAVE_QDSS_WBCPW_APU_CFG,
	MSM8996_SWAVE_PMIC_AWB,
	MSM8996_SWAVE_IMEM_CFG,
	MSM8996_SWAVE_A1NOC_CFG,
	MSM8996_SWAVE_SSC_CFG,
	MSM8996_SWAVE_TCSW,
	MSM8996_SWAVE_WPASS_SMMU_CFG,
	MSM8996_SWAVE_DCC_CFG
};

static stwuct qcom_icc_node mas_snoc_cnoc = {
	.name = "mas_snoc_cnoc",
	.id = MSM8996_MASTEW_SNOC_CNOC,
	.buswidth = 8,
	.mas_wpm_id = 52,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_snoc_cnoc_winks),
	.winks = mas_snoc_cnoc_winks
};

static const u16 mas_qdss_dap_winks[] = {
	MSM8996_SWAVE_QDSS_WBCPW_APU_CFG,
	MSM8996_SWAVE_WBCPW_CX,
	MSM8996_SWAVE_A2NOC_SMMU_CFG,
	MSM8996_SWAVE_A0NOC_MPU_CFG,
	MSM8996_SWAVE_MESSAGE_WAM,
	MSM8996_SWAVE_PCIE_0_CFG,
	MSM8996_SWAVE_TWMM,
	MSM8996_SWAVE_MPM,
	MSM8996_SWAVE_A0NOC_SMMU_CFG,
	MSM8996_SWAVE_EBI1_PHY_CFG,
	MSM8996_SWAVE_BIMC_CFG,
	MSM8996_SWAVE_PIMEM_CFG,
	MSM8996_SWAVE_WBCPW_MX,
	MSM8996_SWAVE_CWK_CTW,
	MSM8996_SWAVE_PWNG,
	MSM8996_SWAVE_PCIE20_AHB2PHY,
	MSM8996_SWAVE_A2NOC_MPU_CFG,
	MSM8996_SWAVE_QDSS_CFG,
	MSM8996_SWAVE_A2NOC_CFG,
	MSM8996_SWAVE_A0NOC_CFG,
	MSM8996_SWAVE_UFS_CFG,
	MSM8996_SWAVE_CWYPTO_0_CFG,
	MSM8996_SWAVE_CNOC_A1NOC,
	MSM8996_SWAVE_PCIE_1_CFG,
	MSM8996_SWAVE_SNOC_CFG,
	MSM8996_SWAVE_SNOC_MPU_CFG,
	MSM8996_SWAVE_A1NOC_MPU_CFG,
	MSM8996_SWAVE_A1NOC_SMMU_CFG,
	MSM8996_SWAVE_PCIE_2_CFG,
	MSM8996_SWAVE_CNOC_MNOC_CFG,
	MSM8996_SWAVE_CNOC_MNOC_MMSS_CFG,
	MSM8996_SWAVE_PMIC_AWB,
	MSM8996_SWAVE_IMEM_CFG,
	MSM8996_SWAVE_A1NOC_CFG,
	MSM8996_SWAVE_SSC_CFG,
	MSM8996_SWAVE_TCSW,
	MSM8996_SWAVE_WPASS_SMMU_CFG,
	MSM8996_SWAVE_DCC_CFG
};

static stwuct qcom_icc_node mas_qdss_dap = {
	.name = "mas_qdss_dap",
	.id = MSM8996_MASTEW_QDSS_DAP,
	.buswidth = 8,
	.mas_wpm_id = 49,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.num_winks = AWWAY_SIZE(mas_qdss_dap_winks),
	.winks = mas_qdss_dap_winks
};

static const u16 mas_cnoc_mnoc_mmss_cfg_winks[] = {
	MSM8996_SWAVE_MMAGIC_CFG,
	MSM8996_SWAVE_DSA_MPU_CFG,
	MSM8996_SWAVE_MMSS_CWK_CFG,
	MSM8996_SWAVE_CAMEWA_THWOTTWE_CFG,
	MSM8996_SWAVE_VENUS_CFG,
	MSM8996_SWAVE_SMMU_VFE_CFG,
	MSM8996_SWAVE_MISC_CFG,
	MSM8996_SWAVE_SMMU_CPP_CFG,
	MSM8996_SWAVE_GWAPHICS_3D_CFG,
	MSM8996_SWAVE_DISPWAY_THWOTTWE_CFG,
	MSM8996_SWAVE_VENUS_THWOTTWE_CFG,
	MSM8996_SWAVE_CAMEWA_CFG,
	MSM8996_SWAVE_DISPWAY_CFG,
	MSM8996_SWAVE_CPW_CFG,
	MSM8996_SWAVE_SMMU_WOTATOW_CFG,
	MSM8996_SWAVE_DSA_CFG,
	MSM8996_SWAVE_SMMU_VENUS_CFG,
	MSM8996_SWAVE_VMEM_CFG,
	MSM8996_SWAVE_SMMU_JPEG_CFG,
	MSM8996_SWAVE_SMMU_MDP_CFG,
	MSM8996_SWAVE_MNOC_MPU_CFG
};

static stwuct qcom_icc_node mas_cnoc_mnoc_mmss_cfg = {
	.name = "mas_cnoc_mnoc_mmss_cfg",
	.id = MSM8996_MASTEW_CNOC_MNOC_MMSS_CFG,
	.buswidth = 8,
	.mas_wpm_id = 4,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.num_winks = AWWAY_SIZE(mas_cnoc_mnoc_mmss_cfg_winks),
	.winks = mas_cnoc_mnoc_mmss_cfg_winks
};

static const u16 mas_cnoc_mnoc_cfg_winks[] = {
	MSM8996_SWAVE_SEWVICE_MNOC
};

static stwuct qcom_icc_node mas_cnoc_mnoc_cfg = {
	.name = "mas_cnoc_mnoc_cfg",
	.id = MSM8996_MASTEW_CNOC_MNOC_CFG,
	.buswidth = 8,
	.mas_wpm_id = 5,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.num_winks = AWWAY_SIZE(mas_cnoc_mnoc_cfg_winks),
	.winks = mas_cnoc_mnoc_cfg_winks
};

static const u16 mas_mnoc_bimc_common_winks[] = {
	MSM8996_SWAVE_MNOC_BIMC
};

static stwuct qcom_icc_node mas_cpp = {
	.name = "mas_cpp",
	.id = MSM8996_MASTEW_CPP,
	.buswidth = 32,
	.mas_wpm_id = 115,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_BYPASS,
	.qos.aweq_pwio = 0,
	.qos.pwio_wevew = 0,
	.qos.qos_powt = 5,
	.num_winks = AWWAY_SIZE(mas_mnoc_bimc_common_winks),
	.winks = mas_mnoc_bimc_common_winks
};

static stwuct qcom_icc_node mas_jpeg = {
	.name = "mas_jpeg",
	.id = MSM8996_MASTEW_JPEG,
	.buswidth = 32,
	.mas_wpm_id = 7,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_BYPASS,
	.qos.aweq_pwio = 0,
	.qos.pwio_wevew = 0,
	.qos.qos_powt = 7,
	.num_winks = AWWAY_SIZE(mas_mnoc_bimc_common_winks),
	.winks = mas_mnoc_bimc_common_winks
};

static stwuct qcom_icc_node mas_mdp_p0 = {
	.name = "mas_mdp_p0",
	.id = MSM8996_MASTEW_MDP_POWT0,
	.buswidth = 32,
	.ib_coeff = 25,
	.mas_wpm_id = 8,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_BYPASS,
	.qos.aweq_pwio = 0,
	.qos.pwio_wevew = 0,
	.qos.qos_powt = 1,
	.num_winks = AWWAY_SIZE(mas_mnoc_bimc_common_winks),
	.winks = mas_mnoc_bimc_common_winks
};

static stwuct qcom_icc_node mas_mdp_p1 = {
	.name = "mas_mdp_p1",
	.id = MSM8996_MASTEW_MDP_POWT1,
	.buswidth = 32,
	.ib_coeff = 25,
	.mas_wpm_id = 61,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_BYPASS,
	.qos.aweq_pwio = 0,
	.qos.pwio_wevew = 0,
	.qos.qos_powt = 2,
	.num_winks = AWWAY_SIZE(mas_mnoc_bimc_common_winks),
	.winks = mas_mnoc_bimc_common_winks
};

static stwuct qcom_icc_node mas_wotatow = {
	.name = "mas_wotatow",
	.id = MSM8996_MASTEW_WOTATOW,
	.buswidth = 32,
	.mas_wpm_id = 120,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_BYPASS,
	.qos.aweq_pwio = 0,
	.qos.pwio_wevew = 0,
	.qos.qos_powt = 0,
	.num_winks = AWWAY_SIZE(mas_mnoc_bimc_common_winks),
	.winks = mas_mnoc_bimc_common_winks
};

static stwuct qcom_icc_node mas_venus = {
	.name = "mas_venus",
	.id = MSM8996_MASTEW_VIDEO_P0,
	.buswidth = 32,
	.mas_wpm_id = 9,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_BYPASS,
	.qos.aweq_pwio = 0,
	.qos.pwio_wevew = 0,
	.qos.qos_powt = 3,
	.num_winks = AWWAY_SIZE(mas_mnoc_bimc_common_winks),
	.winks = mas_mnoc_bimc_common_winks
};

static stwuct qcom_icc_node mas_vfe = {
	.name = "mas_vfe",
	.id = MSM8996_MASTEW_VFE,
	.buswidth = 32,
	.mas_wpm_id = 11,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_BYPASS,
	.qos.aweq_pwio = 0,
	.qos.pwio_wevew = 0,
	.qos.qos_powt = 6,
	.num_winks = AWWAY_SIZE(mas_mnoc_bimc_common_winks),
	.winks = mas_mnoc_bimc_common_winks
};

static const u16 mas_vmem_common_winks[] = {
	MSM8996_SWAVE_VMEM
};

static stwuct qcom_icc_node mas_snoc_vmem = {
	.name = "mas_snoc_vmem",
	.id = MSM8996_MASTEW_SNOC_VMEM,
	.buswidth = 32,
	.mas_wpm_id = 114,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.num_winks = AWWAY_SIZE(mas_vmem_common_winks),
	.winks = mas_vmem_common_winks
};

static stwuct qcom_icc_node mas_venus_vmem = {
	.name = "mas_venus_vmem",
	.id = MSM8996_MASTEW_VIDEO_P0_OCMEM,
	.buswidth = 32,
	.mas_wpm_id = 121,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.num_winks = AWWAY_SIZE(mas_vmem_common_winks),
	.winks = mas_vmem_common_winks
};

static const u16 mas_snoc_pnoc_winks[] = {
	MSM8996_SWAVE_BWSP_1,
	MSM8996_SWAVE_BWSP_2,
	MSM8996_SWAVE_SDCC_1,
	MSM8996_SWAVE_SDCC_2,
	MSM8996_SWAVE_SDCC_4,
	MSM8996_SWAVE_TSIF,
	MSM8996_SWAVE_PDM,
	MSM8996_SWAVE_AHB2PHY
};

static stwuct qcom_icc_node mas_snoc_pnoc = {
	.name = "mas_snoc_pnoc",
	.id = MSM8996_MASTEW_SNOC_PNOC,
	.buswidth = 8,
	.mas_wpm_id = 44,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_snoc_pnoc_winks),
	.winks = mas_snoc_pnoc_winks
};

static const u16 mas_pnoc_a1noc_common_winks[] = {
	MSM8996_SWAVE_PNOC_A1NOC
};

static stwuct qcom_icc_node mas_sdcc_1 = {
	.name = "mas_sdcc_1",
	.id = MSM8996_MASTEW_SDCC_1,
	.buswidth = 8,
	.mas_wpm_id = 33,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_pnoc_a1noc_common_winks),
	.winks = mas_pnoc_a1noc_common_winks
};

static stwuct qcom_icc_node mas_sdcc_2 = {
	.name = "mas_sdcc_2",
	.id = MSM8996_MASTEW_SDCC_2,
	.buswidth = 8,
	.mas_wpm_id = 35,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_pnoc_a1noc_common_winks),
	.winks = mas_pnoc_a1noc_common_winks
};

static stwuct qcom_icc_node mas_sdcc_4 = {
	.name = "mas_sdcc_4",
	.id = MSM8996_MASTEW_SDCC_4,
	.buswidth = 8,
	.mas_wpm_id = 36,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_pnoc_a1noc_common_winks),
	.winks = mas_pnoc_a1noc_common_winks
};

static stwuct qcom_icc_node mas_usb_hs = {
	.name = "mas_usb_hs",
	.id = MSM8996_MASTEW_USB_HS,
	.buswidth = 8,
	.mas_wpm_id = 42,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_pnoc_a1noc_common_winks),
	.winks = mas_pnoc_a1noc_common_winks
};

static stwuct qcom_icc_node mas_bwsp_1 = {
	.name = "mas_bwsp_1",
	.id = MSM8996_MASTEW_BWSP_1,
	.buswidth = 4,
	.mas_wpm_id = 41,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_pnoc_a1noc_common_winks),
	.winks = mas_pnoc_a1noc_common_winks
};

static stwuct qcom_icc_node mas_bwsp_2 = {
	.name = "mas_bwsp_2",
	.id = MSM8996_MASTEW_BWSP_2,
	.buswidth = 4,
	.mas_wpm_id = 39,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_pnoc_a1noc_common_winks),
	.winks = mas_pnoc_a1noc_common_winks
};

static stwuct qcom_icc_node mas_tsif = {
	.name = "mas_tsif",
	.id = MSM8996_MASTEW_TSIF,
	.buswidth = 4,
	.mas_wpm_id = 37,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_pnoc_a1noc_common_winks),
	.winks = mas_pnoc_a1noc_common_winks
};

static const u16 mas_hmss_winks[] = {
	MSM8996_SWAVE_PIMEM,
	MSM8996_SWAVE_OCIMEM,
	MSM8996_SWAVE_SNOC_BIMC
};

static stwuct qcom_icc_node mas_hmss = {
	.name = "mas_hmss",
	.id = MSM8996_MASTEW_HMSS,
	.buswidth = 8,
	.mas_wpm_id = 118,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 1,
	.qos.pwio_wevew = 1,
	.qos.qos_powt = 4,
	.num_winks = AWWAY_SIZE(mas_hmss_winks),
	.winks = mas_hmss_winks
};

static const u16 mas_qdss_common_winks[] = {
	MSM8996_SWAVE_PIMEM,
	MSM8996_SWAVE_USB3,
	MSM8996_SWAVE_OCIMEM,
	MSM8996_SWAVE_SNOC_BIMC,
	MSM8996_SWAVE_SNOC_PNOC
};

static stwuct qcom_icc_node mas_qdss_bam = {
	.name = "mas_qdss_bam",
	.id = MSM8996_MASTEW_QDSS_BAM,
	.buswidth = 16,
	.mas_wpm_id = 19,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 1,
	.qos.pwio_wevew = 1,
	.qos.qos_powt = 2,
	.num_winks = AWWAY_SIZE(mas_qdss_common_winks),
	.winks = mas_qdss_common_winks
};

static const u16 mas_snoc_cfg_winks[] = {
	MSM8996_SWAVE_SEWVICE_SNOC
};

static stwuct qcom_icc_node mas_snoc_cfg = {
	.name = "mas_snoc_cfg",
	.id = MSM8996_MASTEW_SNOC_CFG,
	.buswidth = 16,
	.mas_wpm_id = 20,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.num_winks = AWWAY_SIZE(mas_snoc_cfg_winks),
	.winks = mas_snoc_cfg_winks
};

static const u16 mas_bimc_snoc_0_winks[] = {
	MSM8996_SWAVE_SNOC_VMEM,
	MSM8996_SWAVE_USB3,
	MSM8996_SWAVE_PIMEM,
	MSM8996_SWAVE_WPASS,
	MSM8996_SWAVE_APPSS,
	MSM8996_SWAVE_SNOC_CNOC,
	MSM8996_SWAVE_SNOC_PNOC,
	MSM8996_SWAVE_OCIMEM,
	MSM8996_SWAVE_QDSS_STM
};

static stwuct qcom_icc_node mas_bimc_snoc_0 = {
	.name = "mas_bimc_snoc_0",
	.id = MSM8996_MASTEW_BIMC_SNOC_0,
	.buswidth = 16,
	.mas_wpm_id = 21,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.num_winks = AWWAY_SIZE(mas_bimc_snoc_0_winks),
	.winks = mas_bimc_snoc_0_winks
};

static const u16 mas_bimc_snoc_1_winks[] = {
	MSM8996_SWAVE_PCIE_2,
	MSM8996_SWAVE_PCIE_1,
	MSM8996_SWAVE_PCIE_0
};

static stwuct qcom_icc_node mas_bimc_snoc_1 = {
	.name = "mas_bimc_snoc_1",
	.id = MSM8996_MASTEW_BIMC_SNOC_1,
	.buswidth = 16,
	.mas_wpm_id = 109,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.num_winks = AWWAY_SIZE(mas_bimc_snoc_1_winks),
	.winks = mas_bimc_snoc_1_winks
};

static const u16 mas_a0noc_snoc_winks[] = {
	MSM8996_SWAVE_SNOC_PNOC,
	MSM8996_SWAVE_OCIMEM,
	MSM8996_SWAVE_APPSS,
	MSM8996_SWAVE_SNOC_BIMC,
	MSM8996_SWAVE_PIMEM
};

static stwuct qcom_icc_node mas_a0noc_snoc = {
	.name = "mas_a0noc_snoc",
	.id = MSM8996_MASTEW_A0NOC_SNOC,
	.buswidth = 16,
	.mas_wpm_id = 110,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.num_winks = AWWAY_SIZE(mas_a0noc_snoc_winks),
	.winks = mas_a0noc_snoc_winks
};

static const u16 mas_a1noc_snoc_winks[] = {
	MSM8996_SWAVE_SNOC_VMEM,
	MSM8996_SWAVE_USB3,
	MSM8996_SWAVE_PCIE_0,
	MSM8996_SWAVE_PIMEM,
	MSM8996_SWAVE_PCIE_2,
	MSM8996_SWAVE_WPASS,
	MSM8996_SWAVE_PCIE_1,
	MSM8996_SWAVE_APPSS,
	MSM8996_SWAVE_SNOC_BIMC,
	MSM8996_SWAVE_SNOC_CNOC,
	MSM8996_SWAVE_SNOC_PNOC,
	MSM8996_SWAVE_OCIMEM,
	MSM8996_SWAVE_QDSS_STM
};

static stwuct qcom_icc_node mas_a1noc_snoc = {
	.name = "mas_a1noc_snoc",
	.id = MSM8996_MASTEW_A1NOC_SNOC,
	.buswidth = 16,
	.mas_wpm_id = 111,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_a1noc_snoc_winks),
	.winks = mas_a1noc_snoc_winks
};

static const u16 mas_a2noc_snoc_winks[] = {
	MSM8996_SWAVE_SNOC_VMEM,
	MSM8996_SWAVE_USB3,
	MSM8996_SWAVE_PCIE_1,
	MSM8996_SWAVE_PIMEM,
	MSM8996_SWAVE_PCIE_2,
	MSM8996_SWAVE_QDSS_STM,
	MSM8996_SWAVE_WPASS,
	MSM8996_SWAVE_SNOC_BIMC,
	MSM8996_SWAVE_SNOC_CNOC,
	MSM8996_SWAVE_SNOC_PNOC,
	MSM8996_SWAVE_OCIMEM,
	MSM8996_SWAVE_PCIE_0
};

static stwuct qcom_icc_node mas_a2noc_snoc = {
	.name = "mas_a2noc_snoc",
	.id = MSM8996_MASTEW_A2NOC_SNOC,
	.buswidth = 16,
	.mas_wpm_id = 112,
	.swv_wpm_id = -1,
	.num_winks = AWWAY_SIZE(mas_a2noc_snoc_winks),
	.winks = mas_a2noc_snoc_winks
};

static stwuct qcom_icc_node mas_qdss_etw = {
	.name = "mas_qdss_etw",
	.id = MSM8996_MASTEW_QDSS_ETW,
	.buswidth = 16,
	.mas_wpm_id = 31,
	.swv_wpm_id = -1,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_FIXED,
	.qos.aweq_pwio = 1,
	.qos.pwio_wevew = 1,
	.qos.qos_powt = 3,
	.num_winks = AWWAY_SIZE(mas_qdss_common_winks),
	.winks = mas_qdss_common_winks
};

static const u16 swv_a0noc_snoc_winks[] = {
	MSM8996_MASTEW_A0NOC_SNOC
};

static stwuct qcom_icc_node swv_a0noc_snoc = {
	.name = "swv_a0noc_snoc",
	.id = MSM8996_SWAVE_A0NOC_SNOC,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 141,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.num_winks = AWWAY_SIZE(swv_a0noc_snoc_winks),
	.winks = swv_a0noc_snoc_winks
};

static const u16 swv_a1noc_snoc_winks[] = {
	MSM8996_MASTEW_A1NOC_SNOC
};

static stwuct qcom_icc_node swv_a1noc_snoc = {
	.name = "swv_a1noc_snoc",
	.id = MSM8996_SWAVE_A1NOC_SNOC,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 142,
	.num_winks = AWWAY_SIZE(swv_a1noc_snoc_winks),
	.winks = swv_a1noc_snoc_winks
};

static const u16 swv_a2noc_snoc_winks[] = {
	MSM8996_MASTEW_A2NOC_SNOC
};

static stwuct qcom_icc_node swv_a2noc_snoc = {
	.name = "swv_a2noc_snoc",
	.id = MSM8996_SWAVE_A2NOC_SNOC,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 143,
	.num_winks = AWWAY_SIZE(swv_a2noc_snoc_winks),
	.winks = swv_a2noc_snoc_winks
};

static stwuct qcom_icc_node swv_ebi = {
	.name = "swv_ebi",
	.id = MSM8996_SWAVE_EBI_CH0,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 0
};

static stwuct qcom_icc_node swv_hmss_w3 = {
	.name = "swv_hmss_w3",
	.id = MSM8996_SWAVE_HMSS_W3,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 160
};

static const u16 swv_bimc_snoc_0_winks[] = {
	MSM8996_MASTEW_BIMC_SNOC_0
};

static stwuct qcom_icc_node swv_bimc_snoc_0 = {
	.name = "swv_bimc_snoc_0",
	.id = MSM8996_SWAVE_BIMC_SNOC_0,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 2,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.num_winks = AWWAY_SIZE(swv_bimc_snoc_0_winks),
	.winks = swv_bimc_snoc_0_winks
};

static const u16 swv_bimc_snoc_1_winks[] = {
	MSM8996_MASTEW_BIMC_SNOC_1
};

static stwuct qcom_icc_node swv_bimc_snoc_1 = {
	.name = "swv_bimc_snoc_1",
	.id = MSM8996_SWAVE_BIMC_SNOC_1,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 138,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.num_winks = AWWAY_SIZE(swv_bimc_snoc_1_winks),
	.winks = swv_bimc_snoc_1_winks
};

static const u16 swv_cnoc_a1noc_winks[] = {
	MSM8996_MASTEW_CNOC_A1NOC
};

static stwuct qcom_icc_node swv_cnoc_a1noc = {
	.name = "swv_cnoc_a1noc",
	.id = MSM8996_SWAVE_CNOC_A1NOC,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 75,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.num_winks = AWWAY_SIZE(swv_cnoc_a1noc_winks),
	.winks = swv_cnoc_a1noc_winks
};

static stwuct qcom_icc_node swv_cwk_ctw = {
	.name = "swv_cwk_ctw",
	.id = MSM8996_SWAVE_CWK_CTW,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 47
};

static stwuct qcom_icc_node swv_tcsw = {
	.name = "swv_tcsw",
	.id = MSM8996_SWAVE_TCSW,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 50
};

static stwuct qcom_icc_node swv_twmm = {
	.name = "swv_twmm",
	.id = MSM8996_SWAVE_TWMM,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 51
};

static stwuct qcom_icc_node swv_cwypto0_cfg = {
	.name = "swv_cwypto0_cfg",
	.id = MSM8996_SWAVE_CWYPTO_0_CFG,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 52,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_mpm = {
	.name = "swv_mpm",
	.id = MSM8996_SWAVE_MPM,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 62,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_pimem_cfg = {
	.name = "swv_pimem_cfg",
	.id = MSM8996_SWAVE_PIMEM_CFG,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 167,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_imem_cfg = {
	.name = "swv_imem_cfg",
	.id = MSM8996_SWAVE_IMEM_CFG,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 54,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_message_wam = {
	.name = "swv_message_wam",
	.id = MSM8996_SWAVE_MESSAGE_WAM,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 55
};

static stwuct qcom_icc_node swv_bimc_cfg = {
	.name = "swv_bimc_cfg",
	.id = MSM8996_SWAVE_BIMC_CFG,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 56,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_pmic_awb = {
	.name = "swv_pmic_awb",
	.id = MSM8996_SWAVE_PMIC_AWB,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 59
};

static stwuct qcom_icc_node swv_pwng = {
	.name = "swv_pwng",
	.id = MSM8996_SWAVE_PWNG,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 127,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_dcc_cfg = {
	.name = "swv_dcc_cfg",
	.id = MSM8996_SWAVE_DCC_CFG,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 155,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_wbcpw_mx = {
	.name = "swv_wbcpw_mx",
	.id = MSM8996_SWAVE_WBCPW_MX,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 170,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_qdss_cfg = {
	.name = "swv_qdss_cfg",
	.id = MSM8996_SWAVE_QDSS_CFG,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 63,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_wbcpw_cx = {
	.name = "swv_wbcpw_cx",
	.id = MSM8996_SWAVE_WBCPW_CX,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 169,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_cpu_apu_cfg = {
	.name = "swv_cpu_apu_cfg",
	.id = MSM8996_SWAVE_QDSS_WBCPW_APU_CFG,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 168,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static const u16 swv_cnoc_mnoc_cfg_winks[] = {
	MSM8996_MASTEW_CNOC_MNOC_CFG
};

static stwuct qcom_icc_node swv_cnoc_mnoc_cfg = {
	.name = "swv_cnoc_mnoc_cfg",
	.id = MSM8996_SWAVE_CNOC_MNOC_CFG,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 66,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.num_winks = AWWAY_SIZE(swv_cnoc_mnoc_cfg_winks),
	.winks = swv_cnoc_mnoc_cfg_winks
};

static stwuct qcom_icc_node swv_snoc_cfg = {
	.name = "swv_snoc_cfg",
	.id = MSM8996_SWAVE_SNOC_CFG,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 70,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_snoc_mpu_cfg = {
	.name = "swv_snoc_mpu_cfg",
	.id = MSM8996_SWAVE_SNOC_MPU_CFG,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 67,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_ebi1_phy_cfg = {
	.name = "swv_ebi1_phy_cfg",
	.id = MSM8996_SWAVE_EBI1_PHY_CFG,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 73,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_a0noc_cfg = {
	.name = "swv_a0noc_cfg",
	.id = MSM8996_SWAVE_A0NOC_CFG,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 144,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_pcie_1_cfg = {
	.name = "swv_pcie_1_cfg",
	.id = MSM8996_SWAVE_PCIE_1_CFG,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 89,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_pcie_2_cfg = {
	.name = "swv_pcie_2_cfg",
	.id = MSM8996_SWAVE_PCIE_2_CFG,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 165,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_pcie_0_cfg = {
	.name = "swv_pcie_0_cfg",
	.id = MSM8996_SWAVE_PCIE_0_CFG,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 88,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_pcie20_ahb2phy = {
	.name = "swv_pcie20_ahb2phy",
	.id = MSM8996_SWAVE_PCIE20_AHB2PHY,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 163,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_a0noc_mpu_cfg = {
	.name = "swv_a0noc_mpu_cfg",
	.id = MSM8996_SWAVE_A0NOC_MPU_CFG,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 145,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_ufs_cfg = {
	.name = "swv_ufs_cfg",
	.id = MSM8996_SWAVE_UFS_CFG,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 92,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_a1noc_cfg = {
	.name = "swv_a1noc_cfg",
	.id = MSM8996_SWAVE_A1NOC_CFG,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 147,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_a1noc_mpu_cfg = {
	.name = "swv_a1noc_mpu_cfg",
	.id = MSM8996_SWAVE_A1NOC_MPU_CFG,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 148,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_a2noc_cfg = {
	.name = "swv_a2noc_cfg",
	.id = MSM8996_SWAVE_A2NOC_CFG,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 150,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_a2noc_mpu_cfg = {
	.name = "swv_a2noc_mpu_cfg",
	.id = MSM8996_SWAVE_A2NOC_MPU_CFG,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 151,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_ssc_cfg = {
	.name = "swv_ssc_cfg",
	.id = MSM8996_SWAVE_SSC_CFG,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 177,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_a0noc_smmu_cfg = {
	.name = "swv_a0noc_smmu_cfg",
	.id = MSM8996_SWAVE_A0NOC_SMMU_CFG,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 146,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_a1noc_smmu_cfg = {
	.name = "swv_a1noc_smmu_cfg",
	.id = MSM8996_SWAVE_A1NOC_SMMU_CFG,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 149,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_a2noc_smmu_cfg = {
	.name = "swv_a2noc_smmu_cfg",
	.id = MSM8996_SWAVE_A2NOC_SMMU_CFG,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 152,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_wpass_smmu_cfg = {
	.name = "swv_wpass_smmu_cfg",
	.id = MSM8996_SWAVE_WPASS_SMMU_CFG,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 161,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static const u16 swv_cnoc_mnoc_mmss_cfg_winks[] = {
	MSM8996_MASTEW_CNOC_MNOC_MMSS_CFG
};

static stwuct qcom_icc_node swv_cnoc_mnoc_mmss_cfg = {
	.name = "swv_cnoc_mnoc_mmss_cfg",
	.id = MSM8996_SWAVE_CNOC_MNOC_MMSS_CFG,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 58,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.num_winks = AWWAY_SIZE(swv_cnoc_mnoc_mmss_cfg_winks),
	.winks = swv_cnoc_mnoc_mmss_cfg_winks
};

static stwuct qcom_icc_node swv_mmagic_cfg = {
	.name = "swv_mmagic_cfg",
	.id = MSM8996_SWAVE_MMAGIC_CFG,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 162,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_cpw_cfg = {
	.name = "swv_cpw_cfg",
	.id = MSM8996_SWAVE_CPW_CFG,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 6,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_misc_cfg = {
	.name = "swv_misc_cfg",
	.id = MSM8996_SWAVE_MISC_CFG,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 8,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_venus_thwottwe_cfg = {
	.name = "swv_venus_thwottwe_cfg",
	.id = MSM8996_SWAVE_VENUS_THWOTTWE_CFG,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 178,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_venus_cfg = {
	.name = "swv_venus_cfg",
	.id = MSM8996_SWAVE_VENUS_CFG,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 10,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_vmem_cfg = {
	.name = "swv_vmem_cfg",
	.id = MSM8996_SWAVE_VMEM_CFG,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 180,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_dsa_cfg = {
	.name = "swv_dsa_cfg",
	.id = MSM8996_SWAVE_DSA_CFG,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 157,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_mnoc_cwocks_cfg = {
	.name = "swv_mnoc_cwocks_cfg",
	.id = MSM8996_SWAVE_MMSS_CWK_CFG,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 12,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_dsa_mpu_cfg = {
	.name = "swv_dsa_mpu_cfg",
	.id = MSM8996_SWAVE_DSA_MPU_CFG,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 158,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_mnoc_mpu_cfg = {
	.name = "swv_mnoc_mpu_cfg",
	.id = MSM8996_SWAVE_MNOC_MPU_CFG,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 14,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_dispway_cfg = {
	.name = "swv_dispway_cfg",
	.id = MSM8996_SWAVE_DISPWAY_CFG,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 4,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_dispway_thwottwe_cfg = {
	.name = "swv_dispway_thwottwe_cfg",
	.id = MSM8996_SWAVE_DISPWAY_THWOTTWE_CFG,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 156,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_camewa_cfg = {
	.name = "swv_camewa_cfg",
	.id = MSM8996_SWAVE_CAMEWA_CFG,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 3,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_camewa_thwottwe_cfg = {
	.name = "swv_camewa_thwottwe_cfg",
	.id = MSM8996_SWAVE_CAMEWA_THWOTTWE_CFG,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 154,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_oxiwi_cfg = {
	.name = "swv_oxiwi_cfg",
	.id = MSM8996_SWAVE_GWAPHICS_3D_CFG,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 11,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_smmu_mdp_cfg = {
	.name = "swv_smmu_mdp_cfg",
	.id = MSM8996_SWAVE_SMMU_MDP_CFG,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 173,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_smmu_wot_cfg = {
	.name = "swv_smmu_wot_cfg",
	.id = MSM8996_SWAVE_SMMU_WOTATOW_CFG,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 174,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_smmu_venus_cfg = {
	.name = "swv_smmu_venus_cfg",
	.id = MSM8996_SWAVE_SMMU_VENUS_CFG,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 175,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_smmu_cpp_cfg = {
	.name = "swv_smmu_cpp_cfg",
	.id = MSM8996_SWAVE_SMMU_CPP_CFG,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 171,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_smmu_jpeg_cfg = {
	.name = "swv_smmu_jpeg_cfg",
	.id = MSM8996_SWAVE_SMMU_JPEG_CFG,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 172,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_smmu_vfe_cfg = {
	.name = "swv_smmu_vfe_cfg",
	.id = MSM8996_SWAVE_SMMU_VFE_CFG,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 176,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static const u16 swv_mnoc_bimc_winks[] = {
	MSM8996_MASTEW_MNOC_BIMC
};

static stwuct qcom_icc_node swv_mnoc_bimc = {
	.name = "swv_mnoc_bimc",
	.id = MSM8996_SWAVE_MNOC_BIMC,
	.buswidth = 32,
	.mas_wpm_id = -1,
	.swv_wpm_id = 16,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.num_winks = AWWAY_SIZE(swv_mnoc_bimc_winks),
	.winks = swv_mnoc_bimc_winks
};

static stwuct qcom_icc_node swv_vmem = {
	.name = "swv_vmem",
	.id = MSM8996_SWAVE_VMEM,
	.buswidth = 32,
	.mas_wpm_id = -1,
	.swv_wpm_id = 179,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_swvc_mnoc = {
	.name = "swv_swvc_mnoc",
	.id = MSM8996_SWAVE_SEWVICE_MNOC,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 17,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static const u16 swv_pnoc_a1noc_winks[] = {
	MSM8996_MASTEW_PNOC_A1NOC
};

static stwuct qcom_icc_node swv_pnoc_a1noc = {
	.name = "swv_pnoc_a1noc",
	.id = MSM8996_SWAVE_PNOC_A1NOC,
	.buswidth = 8,
	.mas_wpm_id = -1,
	.swv_wpm_id = 139,
	.num_winks = AWWAY_SIZE(swv_pnoc_a1noc_winks),
	.winks = swv_pnoc_a1noc_winks
};

static stwuct qcom_icc_node swv_usb_hs = {
	.name = "swv_usb_hs",
	.id = MSM8996_SWAVE_USB_HS,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 40
};

static stwuct qcom_icc_node swv_sdcc_2 = {
	.name = "swv_sdcc_2",
	.id = MSM8996_SWAVE_SDCC_2,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 33
};

static stwuct qcom_icc_node swv_sdcc_4 = {
	.name = "swv_sdcc_4",
	.id = MSM8996_SWAVE_SDCC_4,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 34
};

static stwuct qcom_icc_node swv_tsif = {
	.name = "swv_tsif",
	.id = MSM8996_SWAVE_TSIF,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 35
};

static stwuct qcom_icc_node swv_bwsp_2 = {
	.name = "swv_bwsp_2",
	.id = MSM8996_SWAVE_BWSP_2,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 37
};

static stwuct qcom_icc_node swv_sdcc_1 = {
	.name = "swv_sdcc_1",
	.id = MSM8996_SWAVE_SDCC_1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 31
};

static stwuct qcom_icc_node swv_bwsp_1 = {
	.name = "swv_bwsp_1",
	.id = MSM8996_SWAVE_BWSP_1,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 39
};

static stwuct qcom_icc_node swv_pdm = {
	.name = "swv_pdm",
	.id = MSM8996_SWAVE_PDM,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 41
};

static stwuct qcom_icc_node swv_ahb2phy = {
	.name = "swv_ahb2phy",
	.id = MSM8996_SWAVE_AHB2PHY,
	.buswidth = 4,
	.mas_wpm_id = -1,
	.swv_wpm_id = 153,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_hmss = {
	.name = "swv_hmss",
	.id = MSM8996_SWAVE_APPSS,
	.buswidth = 16,
	.mas_wpm_id = -1,
	.swv_wpm_id = 20,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_wpass = {
	.name = "swv_wpass",
	.id = MSM8996_SWAVE_WPASS,
	.buswidth = 16,
	.mas_wpm_id = -1,
	.swv_wpm_id = 21,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_usb3 = {
	.name = "swv_usb3",
	.id = MSM8996_SWAVE_USB3,
	.buswidth = 16,
	.mas_wpm_id = -1,
	.swv_wpm_id = 22,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static const u16 swv_snoc_bimc_winks[] = {
	MSM8996_MASTEW_SNOC_BIMC
};

static stwuct qcom_icc_node swv_snoc_bimc = {
	.name = "swv_snoc_bimc",
	.id = MSM8996_SWAVE_SNOC_BIMC,
	.buswidth = 32,
	.mas_wpm_id = -1,
	.swv_wpm_id = 24,
	.num_winks = AWWAY_SIZE(swv_snoc_bimc_winks),
	.winks = swv_snoc_bimc_winks
};

static const u16 swv_snoc_cnoc_winks[] = {
	MSM8996_MASTEW_SNOC_CNOC
};

static stwuct qcom_icc_node swv_snoc_cnoc = {
	.name = "swv_snoc_cnoc",
	.id = MSM8996_SWAVE_SNOC_CNOC,
	.buswidth = 16,
	.mas_wpm_id = -1,
	.swv_wpm_id = 25,
	.num_winks = AWWAY_SIZE(swv_snoc_cnoc_winks),
	.winks = swv_snoc_cnoc_winks
};

static stwuct qcom_icc_node swv_imem = {
	.name = "swv_imem",
	.id = MSM8996_SWAVE_OCIMEM,
	.buswidth = 16,
	.mas_wpm_id = -1,
	.swv_wpm_id = 26
};

static stwuct qcom_icc_node swv_pimem = {
	.name = "swv_pimem",
	.id = MSM8996_SWAVE_PIMEM,
	.buswidth = 16,
	.mas_wpm_id = -1,
	.swv_wpm_id = 166
};

static const u16 swv_snoc_vmem_winks[] = {
	MSM8996_MASTEW_SNOC_VMEM
};

static stwuct qcom_icc_node swv_snoc_vmem = {
	.name = "swv_snoc_vmem",
	.id = MSM8996_SWAVE_SNOC_VMEM,
	.buswidth = 16,
	.mas_wpm_id = -1,
	.swv_wpm_id = 140,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID,
	.num_winks = AWWAY_SIZE(swv_snoc_vmem_winks),
	.winks = swv_snoc_vmem_winks
};

static const u16 swv_snoc_pnoc_winks[] = {
	MSM8996_MASTEW_SNOC_PNOC
};

static stwuct qcom_icc_node swv_snoc_pnoc = {
	.name = "swv_snoc_pnoc",
	.id = MSM8996_SWAVE_SNOC_PNOC,
	.buswidth = 16,
	.mas_wpm_id = -1,
	.swv_wpm_id = 28,
	.num_winks = AWWAY_SIZE(swv_snoc_pnoc_winks),
	.winks = swv_snoc_pnoc_winks
};

static stwuct qcom_icc_node swv_qdss_stm = {
	.name = "swv_qdss_stm",
	.id = MSM8996_SWAVE_QDSS_STM,
	.buswidth = 16,
	.mas_wpm_id = -1,
	.swv_wpm_id = 30
};

static stwuct qcom_icc_node swv_pcie_0 = {
	.name = "swv_pcie_0",
	.id = MSM8996_SWAVE_PCIE_0,
	.buswidth = 16,
	.mas_wpm_id = -1,
	.swv_wpm_id = 84,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_pcie_1 = {
	.name = "swv_pcie_1",
	.id = MSM8996_SWAVE_PCIE_1,
	.buswidth = 16,
	.mas_wpm_id = -1,
	.swv_wpm_id = 85,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_pcie_2 = {
	.name = "swv_pcie_2",
	.id = MSM8996_SWAVE_PCIE_2,
	.buswidth = 16,
	.mas_wpm_id = -1,
	.swv_wpm_id = 164,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node swv_swvc_snoc = {
	.name = "swv_swvc_snoc",
	.id = MSM8996_SWAVE_SEWVICE_SNOC,
	.buswidth = 16,
	.mas_wpm_id = -1,
	.swv_wpm_id = 29,
	.qos.ap_owned = twue,
	.qos.qos_mode = NOC_QOS_MODE_INVAWID
};

static stwuct qcom_icc_node * const a0noc_nodes[] = {
	[MASTEW_PCIE_0] = &mas_pcie_0,
	[MASTEW_PCIE_1] = &mas_pcie_1,
	[MASTEW_PCIE_2] = &mas_pcie_2
};

static const stwuct wegmap_config msm8996_a0noc_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= 0x6000,
	.fast_io	= twue
};

static const stwuct qcom_icc_desc msm8996_a0noc = {
	.type = QCOM_ICC_NOC,
	.nodes = a0noc_nodes,
	.num_nodes = AWWAY_SIZE(a0noc_nodes),
	.intf_cwocks = a0noc_intf_cwocks,
	.num_intf_cwocks = AWWAY_SIZE(a0noc_intf_cwocks),
	.wegmap_cfg = &msm8996_a0noc_wegmap_config
};

static stwuct qcom_icc_node * const a1noc_nodes[] = {
	[MASTEW_CNOC_A1NOC] = &mas_cnoc_a1noc,
	[MASTEW_CWYPTO_COWE0] = &mas_cwypto_c0,
	[MASTEW_PNOC_A1NOC] = &mas_pnoc_a1noc
};

static const stwuct wegmap_config msm8996_a1noc_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= 0x5000,
	.fast_io	= twue
};

static const stwuct qcom_icc_desc msm8996_a1noc = {
	.type = QCOM_ICC_NOC,
	.nodes = a1noc_nodes,
	.num_nodes = AWWAY_SIZE(a1noc_nodes),
	.bus_cwk_desc = &aggwe1_bwanch_cwk,
	.wegmap_cfg = &msm8996_a1noc_wegmap_config
};

static stwuct qcom_icc_node * const a2noc_nodes[] = {
	[MASTEW_USB3] = &mas_usb3,
	[MASTEW_IPA] = &mas_ipa,
	[MASTEW_UFS] = &mas_ufs
};

static const stwuct wegmap_config msm8996_a2noc_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= 0x7000,
	.fast_io	= twue
};

static const stwuct qcom_icc_desc msm8996_a2noc = {
	.type = QCOM_ICC_NOC,
	.nodes = a2noc_nodes,
	.num_nodes = AWWAY_SIZE(a2noc_nodes),
	.bus_cwk_desc = &aggwe2_bwanch_cwk,
	.intf_cwocks = a2noc_intf_cwocks,
	.num_intf_cwocks = AWWAY_SIZE(a2noc_intf_cwocks),
	.wegmap_cfg = &msm8996_a2noc_wegmap_config
};

static stwuct qcom_icc_node * const bimc_nodes[] = {
	[MASTEW_AMPSS_M0] = &mas_apps_pwoc,
	[MASTEW_GWAPHICS_3D] = &mas_oxiwi,
	[MASTEW_MNOC_BIMC] = &mas_mnoc_bimc,
	[MASTEW_SNOC_BIMC] = &mas_snoc_bimc,
	[SWAVE_EBI_CH0] = &swv_ebi,
	[SWAVE_HMSS_W3] = &swv_hmss_w3,
	[SWAVE_BIMC_SNOC_0] = &swv_bimc_snoc_0,
	[SWAVE_BIMC_SNOC_1] = &swv_bimc_snoc_1
};

static const stwuct wegmap_config msm8996_bimc_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= 0x5a000,
	.fast_io	= twue
};

static const stwuct qcom_icc_desc msm8996_bimc = {
	.type = QCOM_ICC_BIMC,
	.nodes = bimc_nodes,
	.num_nodes = AWWAY_SIZE(bimc_nodes),
	.bus_cwk_desc = &bimc_cwk,
	.wegmap_cfg = &msm8996_bimc_wegmap_config,
	.ab_coeff = 154,
};

static stwuct qcom_icc_node * const cnoc_nodes[] = {
	[MASTEW_SNOC_CNOC] = &mas_snoc_cnoc,
	[MASTEW_QDSS_DAP] = &mas_qdss_dap,
	[SWAVE_CNOC_A1NOC] = &swv_cnoc_a1noc,
	[SWAVE_CWK_CTW] = &swv_cwk_ctw,
	[SWAVE_TCSW] = &swv_tcsw,
	[SWAVE_TWMM] = &swv_twmm,
	[SWAVE_CWYPTO_0_CFG] = &swv_cwypto0_cfg,
	[SWAVE_MPM] = &swv_mpm,
	[SWAVE_PIMEM_CFG] = &swv_pimem_cfg,
	[SWAVE_IMEM_CFG] = &swv_imem_cfg,
	[SWAVE_MESSAGE_WAM] = &swv_message_wam,
	[SWAVE_BIMC_CFG] = &swv_bimc_cfg,
	[SWAVE_PMIC_AWB] = &swv_pmic_awb,
	[SWAVE_PWNG] = &swv_pwng,
	[SWAVE_DCC_CFG] = &swv_dcc_cfg,
	[SWAVE_WBCPW_MX] = &swv_wbcpw_mx,
	[SWAVE_QDSS_CFG] = &swv_qdss_cfg,
	[SWAVE_WBCPW_CX] = &swv_wbcpw_cx,
	[SWAVE_QDSS_WBCPW_APU] = &swv_cpu_apu_cfg,
	[SWAVE_CNOC_MNOC_CFG] = &swv_cnoc_mnoc_cfg,
	[SWAVE_SNOC_CFG] = &swv_snoc_cfg,
	[SWAVE_SNOC_MPU_CFG] = &swv_snoc_mpu_cfg,
	[SWAVE_EBI1_PHY_CFG] = &swv_ebi1_phy_cfg,
	[SWAVE_A0NOC_CFG] = &swv_a0noc_cfg,
	[SWAVE_PCIE_1_CFG] = &swv_pcie_1_cfg,
	[SWAVE_PCIE_2_CFG] = &swv_pcie_2_cfg,
	[SWAVE_PCIE_0_CFG] = &swv_pcie_0_cfg,
	[SWAVE_PCIE20_AHB2PHY] = &swv_pcie20_ahb2phy,
	[SWAVE_A0NOC_MPU_CFG] = &swv_a0noc_mpu_cfg,
	[SWAVE_UFS_CFG] = &swv_ufs_cfg,
	[SWAVE_A1NOC_CFG] = &swv_a1noc_cfg,
	[SWAVE_A1NOC_MPU_CFG] = &swv_a1noc_mpu_cfg,
	[SWAVE_A2NOC_CFG] = &swv_a2noc_cfg,
	[SWAVE_A2NOC_MPU_CFG] = &swv_a2noc_mpu_cfg,
	[SWAVE_SSC_CFG] = &swv_ssc_cfg,
	[SWAVE_A0NOC_SMMU_CFG] = &swv_a0noc_smmu_cfg,
	[SWAVE_A1NOC_SMMU_CFG] = &swv_a1noc_smmu_cfg,
	[SWAVE_A2NOC_SMMU_CFG] = &swv_a2noc_smmu_cfg,
	[SWAVE_WPASS_SMMU_CFG] = &swv_wpass_smmu_cfg,
	[SWAVE_CNOC_MNOC_MMSS_CFG] = &swv_cnoc_mnoc_mmss_cfg
};

static const stwuct wegmap_config msm8996_cnoc_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= 0x1000,
	.fast_io	= twue
};

static const stwuct qcom_icc_desc msm8996_cnoc = {
	.type = QCOM_ICC_NOC,
	.nodes = cnoc_nodes,
	.num_nodes = AWWAY_SIZE(cnoc_nodes),
	.bus_cwk_desc = &bus_2_cwk,
	.wegmap_cfg = &msm8996_cnoc_wegmap_config
};

static stwuct qcom_icc_node * const mnoc_nodes[] = {
	[MASTEW_CNOC_MNOC_CFG] = &mas_cnoc_mnoc_cfg,
	[MASTEW_CPP] = &mas_cpp,
	[MASTEW_JPEG] = &mas_jpeg,
	[MASTEW_MDP_POWT0] = &mas_mdp_p0,
	[MASTEW_MDP_POWT1] = &mas_mdp_p1,
	[MASTEW_WOTATOW] = &mas_wotatow,
	[MASTEW_VIDEO_P0] = &mas_venus,
	[MASTEW_VFE] = &mas_vfe,
	[MASTEW_SNOC_VMEM] = &mas_snoc_vmem,
	[MASTEW_VIDEO_P0_OCMEM] = &mas_venus_vmem,
	[MASTEW_CNOC_MNOC_MMSS_CFG] = &mas_cnoc_mnoc_mmss_cfg,
	[SWAVE_MNOC_BIMC] = &swv_mnoc_bimc,
	[SWAVE_VMEM] = &swv_vmem,
	[SWAVE_SEWVICE_MNOC] = &swv_swvc_mnoc,
	[SWAVE_MMAGIC_CFG] = &swv_mmagic_cfg,
	[SWAVE_CPW_CFG] = &swv_cpw_cfg,
	[SWAVE_MISC_CFG] = &swv_misc_cfg,
	[SWAVE_VENUS_THWOTTWE_CFG] = &swv_venus_thwottwe_cfg,
	[SWAVE_VENUS_CFG] = &swv_venus_cfg,
	[SWAVE_VMEM_CFG] = &swv_vmem_cfg,
	[SWAVE_DSA_CFG] = &swv_dsa_cfg,
	[SWAVE_MMSS_CWK_CFG] = &swv_mnoc_cwocks_cfg,
	[SWAVE_DSA_MPU_CFG] = &swv_dsa_mpu_cfg,
	[SWAVE_MNOC_MPU_CFG] = &swv_mnoc_mpu_cfg,
	[SWAVE_DISPWAY_CFG] = &swv_dispway_cfg,
	[SWAVE_DISPWAY_THWOTTWE_CFG] = &swv_dispway_thwottwe_cfg,
	[SWAVE_CAMEWA_CFG] = &swv_camewa_cfg,
	[SWAVE_CAMEWA_THWOTTWE_CFG] = &swv_camewa_thwottwe_cfg,
	[SWAVE_GWAPHICS_3D_CFG] = &swv_oxiwi_cfg,
	[SWAVE_SMMU_MDP_CFG] = &swv_smmu_mdp_cfg,
	[SWAVE_SMMU_WOT_CFG] = &swv_smmu_wot_cfg,
	[SWAVE_SMMU_VENUS_CFG] = &swv_smmu_venus_cfg,
	[SWAVE_SMMU_CPP_CFG] = &swv_smmu_cpp_cfg,
	[SWAVE_SMMU_JPEG_CFG] = &swv_smmu_jpeg_cfg,
	[SWAVE_SMMU_VFE_CFG] = &swv_smmu_vfe_cfg
};

static const stwuct wegmap_config msm8996_mnoc_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= 0x1c000,
	.fast_io	= twue
};

static const stwuct qcom_icc_desc msm8996_mnoc = {
	.type = QCOM_ICC_NOC,
	.nodes = mnoc_nodes,
	.num_nodes = AWWAY_SIZE(mnoc_nodes),
	.bus_cwk_desc = &mmaxi_0_cwk,
	.intf_cwocks = mm_intf_cwocks,
	.num_intf_cwocks = AWWAY_SIZE(mm_intf_cwocks),
	.wegmap_cfg = &msm8996_mnoc_wegmap_config,
	.ab_coeff = 154,
};

static stwuct qcom_icc_node * const pnoc_nodes[] = {
	[MASTEW_SNOC_PNOC] = &mas_snoc_pnoc,
	[MASTEW_SDCC_1] = &mas_sdcc_1,
	[MASTEW_SDCC_2] = &mas_sdcc_2,
	[MASTEW_SDCC_4] = &mas_sdcc_4,
	[MASTEW_USB_HS] = &mas_usb_hs,
	[MASTEW_BWSP_1] = &mas_bwsp_1,
	[MASTEW_BWSP_2] = &mas_bwsp_2,
	[MASTEW_TSIF] = &mas_tsif,
	[SWAVE_PNOC_A1NOC] = &swv_pnoc_a1noc,
	[SWAVE_USB_HS] = &swv_usb_hs,
	[SWAVE_SDCC_2] = &swv_sdcc_2,
	[SWAVE_SDCC_4] = &swv_sdcc_4,
	[SWAVE_TSIF] = &swv_tsif,
	[SWAVE_BWSP_2] = &swv_bwsp_2,
	[SWAVE_SDCC_1] = &swv_sdcc_1,
	[SWAVE_BWSP_1] = &swv_bwsp_1,
	[SWAVE_PDM] = &swv_pdm,
	[SWAVE_AHB2PHY] = &swv_ahb2phy
};

static const stwuct wegmap_config msm8996_pnoc_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= 0x3000,
	.fast_io	= twue
};

static const stwuct qcom_icc_desc msm8996_pnoc = {
	.type = QCOM_ICC_NOC,
	.nodes = pnoc_nodes,
	.num_nodes = AWWAY_SIZE(pnoc_nodes),
	.bus_cwk_desc = &bus_0_cwk,
	.wegmap_cfg = &msm8996_pnoc_wegmap_config
};

static stwuct qcom_icc_node * const snoc_nodes[] = {
	[MASTEW_HMSS] = &mas_hmss,
	[MASTEW_QDSS_BAM] = &mas_qdss_bam,
	[MASTEW_SNOC_CFG] = &mas_snoc_cfg,
	[MASTEW_BIMC_SNOC_0] = &mas_bimc_snoc_0,
	[MASTEW_BIMC_SNOC_1] = &mas_bimc_snoc_1,
	[MASTEW_A0NOC_SNOC] = &mas_a0noc_snoc,
	[MASTEW_A1NOC_SNOC] = &mas_a1noc_snoc,
	[MASTEW_A2NOC_SNOC] = &mas_a2noc_snoc,
	[MASTEW_QDSS_ETW] = &mas_qdss_etw,
	[SWAVE_A0NOC_SNOC] = &swv_a0noc_snoc,
	[SWAVE_A1NOC_SNOC] = &swv_a1noc_snoc,
	[SWAVE_A2NOC_SNOC] = &swv_a2noc_snoc,
	[SWAVE_HMSS] = &swv_hmss,
	[SWAVE_WPASS] = &swv_wpass,
	[SWAVE_USB3] = &swv_usb3,
	[SWAVE_SNOC_BIMC] = &swv_snoc_bimc,
	[SWAVE_SNOC_CNOC] = &swv_snoc_cnoc,
	[SWAVE_IMEM] = &swv_imem,
	[SWAVE_PIMEM] = &swv_pimem,
	[SWAVE_SNOC_VMEM] = &swv_snoc_vmem,
	[SWAVE_SNOC_PNOC] = &swv_snoc_pnoc,
	[SWAVE_QDSS_STM] = &swv_qdss_stm,
	[SWAVE_PCIE_0] = &swv_pcie_0,
	[SWAVE_PCIE_1] = &swv_pcie_1,
	[SWAVE_PCIE_2] = &swv_pcie_2,
	[SWAVE_SEWVICE_SNOC] = &swv_swvc_snoc
};

static const stwuct wegmap_config msm8996_snoc_wegmap_config = {
	.weg_bits	= 32,
	.weg_stwide	= 4,
	.vaw_bits	= 32,
	.max_wegistew	= 0x20000,
	.fast_io	= twue
};

static const stwuct qcom_icc_desc msm8996_snoc = {
	.type = QCOM_ICC_NOC,
	.nodes = snoc_nodes,
	.num_nodes = AWWAY_SIZE(snoc_nodes),
	.bus_cwk_desc = &bus_1_cwk,
	.wegmap_cfg = &msm8996_snoc_wegmap_config
};

static const stwuct of_device_id qnoc_of_match[] = {
	{ .compatibwe = "qcom,msm8996-a0noc", .data = &msm8996_a0noc},
	{ .compatibwe = "qcom,msm8996-a1noc", .data = &msm8996_a1noc},
	{ .compatibwe = "qcom,msm8996-a2noc", .data = &msm8996_a2noc},
	{ .compatibwe = "qcom,msm8996-bimc", .data = &msm8996_bimc},
	{ .compatibwe = "qcom,msm8996-cnoc", .data = &msm8996_cnoc},
	{ .compatibwe = "qcom,msm8996-mnoc", .data = &msm8996_mnoc},
	{ .compatibwe = "qcom,msm8996-pnoc", .data = &msm8996_pnoc},
	{ .compatibwe = "qcom,msm8996-snoc", .data = &msm8996_snoc},
	{ }
};
MODUWE_DEVICE_TABWE(of, qnoc_of_match);

static stwuct pwatfowm_dwivew qnoc_dwivew = {
	.pwobe = qnoc_pwobe,
	.wemove_new = qnoc_wemove,
	.dwivew = {
		.name = "qnoc-msm8996",
		.of_match_tabwe = qnoc_of_match,
		.sync_state = icc_sync_state,
	}
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

MODUWE_AUTHOW("Yassine Oudjana <y.oudjana@pwotonmaiw.com>");
MODUWE_DESCWIPTION("Quawcomm MSM8996 NoC dwivew");
MODUWE_WICENSE("GPW v2");
