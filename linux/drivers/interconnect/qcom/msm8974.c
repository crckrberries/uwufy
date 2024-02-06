// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019 Bwian Masney <masneyb@onstation.owg>
 *
 * Based on MSM bus code fwom downstweam MSM kewnew souwces.
 * Copywight (c) 2012-2013 The Winux Foundation. Aww wights wesewved.
 *
 * Based on qcs404.c
 * Copywight (C) 2019 Winawo Wtd
 *
 * Hewe's a wough wepwesentation that shows the vawious buses that fowm the
 * Netwowk On Chip (NOC) fow the msm8974:
 *
 *                         Muwtimedia Subsystem (MMSS)
 *         |----------+-----------------------------------+-----------|
 *                    |                                   |
 *                    |                                   |
 *        Config      |                     Bus Intewface | Memowy Contwowwew
 *       |------------+-+-----------|        |------------+-+-----------|
 *                      |                                   |
 *                      |                                   |
 *                      |             System                |
 *     |--------------+-+---------------------------------+-+-------------|
 *                    |                                   |
 *                    |                                   |
 *        Pewiphewaw  |                           On Chip | Memowy (OCMEM)
 *       |------------+-------------|        |------------+-------------|
 */

#incwude <dt-bindings/intewconnect/qcom,msm8974.h>

#incwude <winux/awgs.h>
#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/intewconnect-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude "icc-wpm.h"

enum {
	MSM8974_BIMC_MAS_AMPSS_M0 = 1,
	MSM8974_BIMC_MAS_AMPSS_M1,
	MSM8974_BIMC_MAS_MSS_PWOC,
	MSM8974_BIMC_TO_MNOC,
	MSM8974_BIMC_TO_SNOC,
	MSM8974_BIMC_SWV_EBI_CH0,
	MSM8974_BIMC_SWV_AMPSS_W2,
	MSM8974_CNOC_MAS_WPM_INST,
	MSM8974_CNOC_MAS_WPM_DATA,
	MSM8974_CNOC_MAS_WPM_SYS,
	MSM8974_CNOC_MAS_DEHW,
	MSM8974_CNOC_MAS_QDSS_DAP,
	MSM8974_CNOC_MAS_SPDM,
	MSM8974_CNOC_MAS_TIC,
	MSM8974_CNOC_SWV_CWK_CTW,
	MSM8974_CNOC_SWV_CNOC_MSS,
	MSM8974_CNOC_SWV_SECUWITY,
	MSM8974_CNOC_SWV_TCSW,
	MSM8974_CNOC_SWV_TWMM,
	MSM8974_CNOC_SWV_CWYPTO_0_CFG,
	MSM8974_CNOC_SWV_CWYPTO_1_CFG,
	MSM8974_CNOC_SWV_IMEM_CFG,
	MSM8974_CNOC_SWV_MESSAGE_WAM,
	MSM8974_CNOC_SWV_BIMC_CFG,
	MSM8974_CNOC_SWV_BOOT_WOM,
	MSM8974_CNOC_SWV_PMIC_AWB,
	MSM8974_CNOC_SWV_SPDM_WWAPPEW,
	MSM8974_CNOC_SWV_DEHW_CFG,
	MSM8974_CNOC_SWV_MPM,
	MSM8974_CNOC_SWV_QDSS_CFG,
	MSM8974_CNOC_SWV_WBCPW_CFG,
	MSM8974_CNOC_SWV_WBCPW_QDSS_APU_CFG,
	MSM8974_CNOC_TO_SNOC,
	MSM8974_CNOC_SWV_CNOC_ONOC_CFG,
	MSM8974_CNOC_SWV_CNOC_MNOC_MMSS_CFG,
	MSM8974_CNOC_SWV_CNOC_MNOC_CFG,
	MSM8974_CNOC_SWV_PNOC_CFG,
	MSM8974_CNOC_SWV_SNOC_MPU_CFG,
	MSM8974_CNOC_SWV_SNOC_CFG,
	MSM8974_CNOC_SWV_EBI1_DWW_CFG,
	MSM8974_CNOC_SWV_PHY_APU_CFG,
	MSM8974_CNOC_SWV_EBI1_PHY_CFG,
	MSM8974_CNOC_SWV_WPM,
	MSM8974_CNOC_SWV_SEWVICE_CNOC,
	MSM8974_MNOC_MAS_GWAPHICS_3D,
	MSM8974_MNOC_MAS_JPEG,
	MSM8974_MNOC_MAS_MDP_POWT0,
	MSM8974_MNOC_MAS_VIDEO_P0,
	MSM8974_MNOC_MAS_VIDEO_P1,
	MSM8974_MNOC_MAS_VFE,
	MSM8974_MNOC_TO_CNOC,
	MSM8974_MNOC_TO_BIMC,
	MSM8974_MNOC_SWV_CAMEWA_CFG,
	MSM8974_MNOC_SWV_DISPWAY_CFG,
	MSM8974_MNOC_SWV_OCMEM_CFG,
	MSM8974_MNOC_SWV_CPW_CFG,
	MSM8974_MNOC_SWV_CPW_XPU_CFG,
	MSM8974_MNOC_SWV_MISC_CFG,
	MSM8974_MNOC_SWV_MISC_XPU_CFG,
	MSM8974_MNOC_SWV_VENUS_CFG,
	MSM8974_MNOC_SWV_GWAPHICS_3D_CFG,
	MSM8974_MNOC_SWV_MMSS_CWK_CFG,
	MSM8974_MNOC_SWV_MMSS_CWK_XPU_CFG,
	MSM8974_MNOC_SWV_MNOC_MPU_CFG,
	MSM8974_MNOC_SWV_ONOC_MPU_CFG,
	MSM8974_MNOC_SWV_SEWVICE_MNOC,
	MSM8974_OCMEM_NOC_TO_OCMEM_VNOC,
	MSM8974_OCMEM_MAS_JPEG_OCMEM,
	MSM8974_OCMEM_MAS_MDP_OCMEM,
	MSM8974_OCMEM_MAS_VIDEO_P0_OCMEM,
	MSM8974_OCMEM_MAS_VIDEO_P1_OCMEM,
	MSM8974_OCMEM_MAS_VFE_OCMEM,
	MSM8974_OCMEM_MAS_CNOC_ONOC_CFG,
	MSM8974_OCMEM_SWV_SEWVICE_ONOC,
	MSM8974_OCMEM_VNOC_TO_SNOC,
	MSM8974_OCMEM_VNOC_TO_OCMEM_NOC,
	MSM8974_OCMEM_VNOC_MAS_GFX3D,
	MSM8974_OCMEM_SWV_OCMEM,
	MSM8974_PNOC_MAS_PNOC_CFG,
	MSM8974_PNOC_MAS_SDCC_1,
	MSM8974_PNOC_MAS_SDCC_3,
	MSM8974_PNOC_MAS_SDCC_4,
	MSM8974_PNOC_MAS_SDCC_2,
	MSM8974_PNOC_MAS_TSIF,
	MSM8974_PNOC_MAS_BAM_DMA,
	MSM8974_PNOC_MAS_BWSP_2,
	MSM8974_PNOC_MAS_USB_HSIC,
	MSM8974_PNOC_MAS_BWSP_1,
	MSM8974_PNOC_MAS_USB_HS,
	MSM8974_PNOC_TO_SNOC,
	MSM8974_PNOC_SWV_SDCC_1,
	MSM8974_PNOC_SWV_SDCC_3,
	MSM8974_PNOC_SWV_SDCC_2,
	MSM8974_PNOC_SWV_SDCC_4,
	MSM8974_PNOC_SWV_TSIF,
	MSM8974_PNOC_SWV_BAM_DMA,
	MSM8974_PNOC_SWV_BWSP_2,
	MSM8974_PNOC_SWV_USB_HSIC,
	MSM8974_PNOC_SWV_BWSP_1,
	MSM8974_PNOC_SWV_USB_HS,
	MSM8974_PNOC_SWV_PDM,
	MSM8974_PNOC_SWV_PEWIPH_APU_CFG,
	MSM8974_PNOC_SWV_PNOC_MPU_CFG,
	MSM8974_PNOC_SWV_PWNG,
	MSM8974_PNOC_SWV_SEWVICE_PNOC,
	MSM8974_SNOC_MAS_WPASS_AHB,
	MSM8974_SNOC_MAS_QDSS_BAM,
	MSM8974_SNOC_MAS_SNOC_CFG,
	MSM8974_SNOC_TO_BIMC,
	MSM8974_SNOC_TO_CNOC,
	MSM8974_SNOC_TO_PNOC,
	MSM8974_SNOC_TO_OCMEM_VNOC,
	MSM8974_SNOC_MAS_CWYPTO_COWE0,
	MSM8974_SNOC_MAS_CWYPTO_COWE1,
	MSM8974_SNOC_MAS_WPASS_PWOC,
	MSM8974_SNOC_MAS_MSS,
	MSM8974_SNOC_MAS_MSS_NAV,
	MSM8974_SNOC_MAS_OCMEM_DMA,
	MSM8974_SNOC_MAS_WCSS,
	MSM8974_SNOC_MAS_QDSS_ETW,
	MSM8974_SNOC_MAS_USB3,
	MSM8974_SNOC_SWV_AMPSS,
	MSM8974_SNOC_SWV_WPASS,
	MSM8974_SNOC_SWV_USB3,
	MSM8974_SNOC_SWV_WCSS,
	MSM8974_SNOC_SWV_OCIMEM,
	MSM8974_SNOC_SWV_SNOC_OCMEM,
	MSM8974_SNOC_SWV_SEWVICE_SNOC,
	MSM8974_SNOC_SWV_QDSS_STM,
};

#define WPM_BUS_MASTEW_WEQ	0x73616d62
#define WPM_BUS_SWAVE_WEQ	0x766c7362

#define to_msm8974_icc_pwovidew(_pwovidew) \
	containew_of(_pwovidew, stwuct msm8974_icc_pwovidew, pwovidew)

static const stwuct cwk_buwk_data msm8974_icc_bus_cwocks[] = {
	{ .id = "bus" },
	{ .id = "bus_a" },
};

/**
 * stwuct msm8974_icc_pwovidew - Quawcomm specific intewconnect pwovidew
 * @pwovidew: genewic intewconnect pwovidew
 * @bus_cwks: the cwk_buwk_data tabwe of bus cwocks
 * @num_cwks: the totaw numbew of cwk_buwk_data entwies
 */
stwuct msm8974_icc_pwovidew {
	stwuct icc_pwovidew pwovidew;
	stwuct cwk_buwk_data *bus_cwks;
	int num_cwks;
};

#define MSM8974_ICC_MAX_WINKS	3

/**
 * stwuct msm8974_icc_node - Quawcomm specific intewconnect nodes
 * @name: the node name used in debugfs
 * @id: a unique node identifiew
 * @winks: an awway of nodes whewe we can go next whiwe twavewsing
 * @num_winks: the totaw numbew of @winks
 * @buswidth: width of the intewconnect between a node and the bus (bytes)
 * @mas_wpm_id:	WPM ID fow devices that awe bus mastews
 * @swv_wpm_id:	WPM ID fow devices that awe bus swaves
 * @wate: cuwwent bus cwock wate in Hz
 */
stwuct msm8974_icc_node {
	unsigned chaw *name;
	u16 id;
	u16 winks[MSM8974_ICC_MAX_WINKS];
	u16 num_winks;
	u16 buswidth;
	int mas_wpm_id;
	int swv_wpm_id;
	u64 wate;
};

stwuct msm8974_icc_desc {
	stwuct msm8974_icc_node * const *nodes;
	size_t num_nodes;
};

#define DEFINE_QNODE(_name, _id, _buswidth, _mas_wpm_id, _swv_wpm_id,	\
		     ...)						\
		static stwuct msm8974_icc_node _name = {		\
		.name = #_name,						\
		.id = _id,						\
		.buswidth = _buswidth,					\
		.mas_wpm_id = _mas_wpm_id,				\
		.swv_wpm_id = _swv_wpm_id,				\
		.num_winks = COUNT_AWGS(__VA_AWGS__),			\
		.winks = { __VA_AWGS__ },				\
	}

DEFINE_QNODE(mas_ampss_m0, MSM8974_BIMC_MAS_AMPSS_M0, 8, 0, -1);
DEFINE_QNODE(mas_ampss_m1, MSM8974_BIMC_MAS_AMPSS_M1, 8, 0, -1);
DEFINE_QNODE(mas_mss_pwoc, MSM8974_BIMC_MAS_MSS_PWOC, 8, 1, -1);
DEFINE_QNODE(bimc_to_mnoc, MSM8974_BIMC_TO_MNOC, 8, 2, -1, MSM8974_BIMC_SWV_EBI_CH0);
DEFINE_QNODE(bimc_to_snoc, MSM8974_BIMC_TO_SNOC, 8, 3, 2, MSM8974_SNOC_TO_BIMC, MSM8974_BIMC_SWV_EBI_CH0, MSM8974_BIMC_MAS_AMPSS_M0);
DEFINE_QNODE(swv_ebi_ch0, MSM8974_BIMC_SWV_EBI_CH0, 8, -1, 0);
DEFINE_QNODE(swv_ampss_w2, MSM8974_BIMC_SWV_AMPSS_W2, 8, -1, 1);

static stwuct msm8974_icc_node * const msm8974_bimc_nodes[] = {
	[BIMC_MAS_AMPSS_M0] = &mas_ampss_m0,
	[BIMC_MAS_AMPSS_M1] = &mas_ampss_m1,
	[BIMC_MAS_MSS_PWOC] = &mas_mss_pwoc,
	[BIMC_TO_MNOC] = &bimc_to_mnoc,
	[BIMC_TO_SNOC] = &bimc_to_snoc,
	[BIMC_SWV_EBI_CH0] = &swv_ebi_ch0,
	[BIMC_SWV_AMPSS_W2] = &swv_ampss_w2,
};

static const stwuct msm8974_icc_desc msm8974_bimc = {
	.nodes = msm8974_bimc_nodes,
	.num_nodes = AWWAY_SIZE(msm8974_bimc_nodes),
};

DEFINE_QNODE(mas_wpm_inst, MSM8974_CNOC_MAS_WPM_INST, 8, 45, -1);
DEFINE_QNODE(mas_wpm_data, MSM8974_CNOC_MAS_WPM_DATA, 8, 46, -1);
DEFINE_QNODE(mas_wpm_sys, MSM8974_CNOC_MAS_WPM_SYS, 8, 47, -1);
DEFINE_QNODE(mas_dehw, MSM8974_CNOC_MAS_DEHW, 8, 48, -1);
DEFINE_QNODE(mas_qdss_dap, MSM8974_CNOC_MAS_QDSS_DAP, 8, 49, -1);
DEFINE_QNODE(mas_spdm, MSM8974_CNOC_MAS_SPDM, 8, 50, -1);
DEFINE_QNODE(mas_tic, MSM8974_CNOC_MAS_TIC, 8, 51, -1);
DEFINE_QNODE(swv_cwk_ctw, MSM8974_CNOC_SWV_CWK_CTW, 8, -1, 47);
DEFINE_QNODE(swv_cnoc_mss, MSM8974_CNOC_SWV_CNOC_MSS, 8, -1, 48);
DEFINE_QNODE(swv_secuwity, MSM8974_CNOC_SWV_SECUWITY, 8, -1, 49);
DEFINE_QNODE(swv_tcsw, MSM8974_CNOC_SWV_TCSW, 8, -1, 50);
DEFINE_QNODE(swv_twmm, MSM8974_CNOC_SWV_TWMM, 8, -1, 51);
DEFINE_QNODE(swv_cwypto_0_cfg, MSM8974_CNOC_SWV_CWYPTO_0_CFG, 8, -1, 52);
DEFINE_QNODE(swv_cwypto_1_cfg, MSM8974_CNOC_SWV_CWYPTO_1_CFG, 8, -1, 53);
DEFINE_QNODE(swv_imem_cfg, MSM8974_CNOC_SWV_IMEM_CFG, 8, -1, 54);
DEFINE_QNODE(swv_message_wam, MSM8974_CNOC_SWV_MESSAGE_WAM, 8, -1, 55);
DEFINE_QNODE(swv_bimc_cfg, MSM8974_CNOC_SWV_BIMC_CFG, 8, -1, 56);
DEFINE_QNODE(swv_boot_wom, MSM8974_CNOC_SWV_BOOT_WOM, 8, -1, 57);
DEFINE_QNODE(swv_pmic_awb, MSM8974_CNOC_SWV_PMIC_AWB, 8, -1, 59);
DEFINE_QNODE(swv_spdm_wwappew, MSM8974_CNOC_SWV_SPDM_WWAPPEW, 8, -1, 60);
DEFINE_QNODE(swv_dehw_cfg, MSM8974_CNOC_SWV_DEHW_CFG, 8, -1, 61);
DEFINE_QNODE(swv_mpm, MSM8974_CNOC_SWV_MPM, 8, -1, 62);
DEFINE_QNODE(swv_qdss_cfg, MSM8974_CNOC_SWV_QDSS_CFG, 8, -1, 63);
DEFINE_QNODE(swv_wbcpw_cfg, MSM8974_CNOC_SWV_WBCPW_CFG, 8, -1, 64);
DEFINE_QNODE(swv_wbcpw_qdss_apu_cfg, MSM8974_CNOC_SWV_WBCPW_QDSS_APU_CFG, 8, -1, 65);
DEFINE_QNODE(cnoc_to_snoc, MSM8974_CNOC_TO_SNOC, 8, 52, 75);
DEFINE_QNODE(swv_cnoc_onoc_cfg, MSM8974_CNOC_SWV_CNOC_ONOC_CFG, 8, -1, 68);
DEFINE_QNODE(swv_cnoc_mnoc_mmss_cfg, MSM8974_CNOC_SWV_CNOC_MNOC_MMSS_CFG, 8, -1, 58);
DEFINE_QNODE(swv_cnoc_mnoc_cfg, MSM8974_CNOC_SWV_CNOC_MNOC_CFG, 8, -1, 66);
DEFINE_QNODE(swv_pnoc_cfg, MSM8974_CNOC_SWV_PNOC_CFG, 8, -1, 69);
DEFINE_QNODE(swv_snoc_mpu_cfg, MSM8974_CNOC_SWV_SNOC_MPU_CFG, 8, -1, 67);
DEFINE_QNODE(swv_snoc_cfg, MSM8974_CNOC_SWV_SNOC_CFG, 8, -1, 70);
DEFINE_QNODE(swv_ebi1_dww_cfg, MSM8974_CNOC_SWV_EBI1_DWW_CFG, 8, -1, 71);
DEFINE_QNODE(swv_phy_apu_cfg, MSM8974_CNOC_SWV_PHY_APU_CFG, 8, -1, 72);
DEFINE_QNODE(swv_ebi1_phy_cfg, MSM8974_CNOC_SWV_EBI1_PHY_CFG, 8, -1, 73);
DEFINE_QNODE(swv_wpm, MSM8974_CNOC_SWV_WPM, 8, -1, 74);
DEFINE_QNODE(swv_sewvice_cnoc, MSM8974_CNOC_SWV_SEWVICE_CNOC, 8, -1, 76);

static stwuct msm8974_icc_node * const msm8974_cnoc_nodes[] = {
	[CNOC_MAS_WPM_INST] = &mas_wpm_inst,
	[CNOC_MAS_WPM_DATA] = &mas_wpm_data,
	[CNOC_MAS_WPM_SYS] = &mas_wpm_sys,
	[CNOC_MAS_DEHW] = &mas_dehw,
	[CNOC_MAS_QDSS_DAP] = &mas_qdss_dap,
	[CNOC_MAS_SPDM] = &mas_spdm,
	[CNOC_MAS_TIC] = &mas_tic,
	[CNOC_SWV_CWK_CTW] = &swv_cwk_ctw,
	[CNOC_SWV_CNOC_MSS] = &swv_cnoc_mss,
	[CNOC_SWV_SECUWITY] = &swv_secuwity,
	[CNOC_SWV_TCSW] = &swv_tcsw,
	[CNOC_SWV_TWMM] = &swv_twmm,
	[CNOC_SWV_CWYPTO_0_CFG] = &swv_cwypto_0_cfg,
	[CNOC_SWV_CWYPTO_1_CFG] = &swv_cwypto_1_cfg,
	[CNOC_SWV_IMEM_CFG] = &swv_imem_cfg,
	[CNOC_SWV_MESSAGE_WAM] = &swv_message_wam,
	[CNOC_SWV_BIMC_CFG] = &swv_bimc_cfg,
	[CNOC_SWV_BOOT_WOM] = &swv_boot_wom,
	[CNOC_SWV_PMIC_AWB] = &swv_pmic_awb,
	[CNOC_SWV_SPDM_WWAPPEW] = &swv_spdm_wwappew,
	[CNOC_SWV_DEHW_CFG] = &swv_dehw_cfg,
	[CNOC_SWV_MPM] = &swv_mpm,
	[CNOC_SWV_QDSS_CFG] = &swv_qdss_cfg,
	[CNOC_SWV_WBCPW_CFG] = &swv_wbcpw_cfg,
	[CNOC_SWV_WBCPW_QDSS_APU_CFG] = &swv_wbcpw_qdss_apu_cfg,
	[CNOC_TO_SNOC] = &cnoc_to_snoc,
	[CNOC_SWV_CNOC_ONOC_CFG] = &swv_cnoc_onoc_cfg,
	[CNOC_SWV_CNOC_MNOC_MMSS_CFG] = &swv_cnoc_mnoc_mmss_cfg,
	[CNOC_SWV_CNOC_MNOC_CFG] = &swv_cnoc_mnoc_cfg,
	[CNOC_SWV_PNOC_CFG] = &swv_pnoc_cfg,
	[CNOC_SWV_SNOC_MPU_CFG] = &swv_snoc_mpu_cfg,
	[CNOC_SWV_SNOC_CFG] = &swv_snoc_cfg,
	[CNOC_SWV_EBI1_DWW_CFG] = &swv_ebi1_dww_cfg,
	[CNOC_SWV_PHY_APU_CFG] = &swv_phy_apu_cfg,
	[CNOC_SWV_EBI1_PHY_CFG] = &swv_ebi1_phy_cfg,
	[CNOC_SWV_WPM] = &swv_wpm,
	[CNOC_SWV_SEWVICE_CNOC] = &swv_sewvice_cnoc,
};

static const stwuct msm8974_icc_desc msm8974_cnoc = {
	.nodes = msm8974_cnoc_nodes,
	.num_nodes = AWWAY_SIZE(msm8974_cnoc_nodes),
};

DEFINE_QNODE(mas_gwaphics_3d, MSM8974_MNOC_MAS_GWAPHICS_3D, 16, 6, -1, MSM8974_MNOC_TO_BIMC);
DEFINE_QNODE(mas_jpeg, MSM8974_MNOC_MAS_JPEG, 16, 7, -1, MSM8974_MNOC_TO_BIMC);
DEFINE_QNODE(mas_mdp_powt0, MSM8974_MNOC_MAS_MDP_POWT0, 16, 8, -1, MSM8974_MNOC_TO_BIMC);
DEFINE_QNODE(mas_video_p0, MSM8974_MNOC_MAS_VIDEO_P0, 16, 9, -1);
DEFINE_QNODE(mas_video_p1, MSM8974_MNOC_MAS_VIDEO_P1, 16, 10, -1);
DEFINE_QNODE(mas_vfe, MSM8974_MNOC_MAS_VFE, 16, 11, -1, MSM8974_MNOC_TO_BIMC);
DEFINE_QNODE(mnoc_to_cnoc, MSM8974_MNOC_TO_CNOC, 16, 4, -1);
DEFINE_QNODE(mnoc_to_bimc, MSM8974_MNOC_TO_BIMC, 16, -1, 16, MSM8974_BIMC_TO_MNOC);
DEFINE_QNODE(swv_camewa_cfg, MSM8974_MNOC_SWV_CAMEWA_CFG, 16, -1, 3);
DEFINE_QNODE(swv_dispway_cfg, MSM8974_MNOC_SWV_DISPWAY_CFG, 16, -1, 4);
DEFINE_QNODE(swv_ocmem_cfg, MSM8974_MNOC_SWV_OCMEM_CFG, 16, -1, 5);
DEFINE_QNODE(swv_cpw_cfg, MSM8974_MNOC_SWV_CPW_CFG, 16, -1, 6);
DEFINE_QNODE(swv_cpw_xpu_cfg, MSM8974_MNOC_SWV_CPW_XPU_CFG, 16, -1, 7);
DEFINE_QNODE(swv_misc_cfg, MSM8974_MNOC_SWV_MISC_CFG, 16, -1, 8);
DEFINE_QNODE(swv_misc_xpu_cfg, MSM8974_MNOC_SWV_MISC_XPU_CFG, 16, -1, 9);
DEFINE_QNODE(swv_venus_cfg, MSM8974_MNOC_SWV_VENUS_CFG, 16, -1, 10);
DEFINE_QNODE(swv_gwaphics_3d_cfg, MSM8974_MNOC_SWV_GWAPHICS_3D_CFG, 16, -1, 11);
DEFINE_QNODE(swv_mmss_cwk_cfg, MSM8974_MNOC_SWV_MMSS_CWK_CFG, 16, -1, 12);
DEFINE_QNODE(swv_mmss_cwk_xpu_cfg, MSM8974_MNOC_SWV_MMSS_CWK_XPU_CFG, 16, -1, 13);
DEFINE_QNODE(swv_mnoc_mpu_cfg, MSM8974_MNOC_SWV_MNOC_MPU_CFG, 16, -1, 14);
DEFINE_QNODE(swv_onoc_mpu_cfg, MSM8974_MNOC_SWV_ONOC_MPU_CFG, 16, -1, 15);
DEFINE_QNODE(swv_sewvice_mnoc, MSM8974_MNOC_SWV_SEWVICE_MNOC, 16, -1, 17);

static stwuct msm8974_icc_node * const msm8974_mnoc_nodes[] = {
	[MNOC_MAS_GWAPHICS_3D] = &mas_gwaphics_3d,
	[MNOC_MAS_JPEG] = &mas_jpeg,
	[MNOC_MAS_MDP_POWT0] = &mas_mdp_powt0,
	[MNOC_MAS_VIDEO_P0] = &mas_video_p0,
	[MNOC_MAS_VIDEO_P1] = &mas_video_p1,
	[MNOC_MAS_VFE] = &mas_vfe,
	[MNOC_TO_CNOC] = &mnoc_to_cnoc,
	[MNOC_TO_BIMC] = &mnoc_to_bimc,
	[MNOC_SWV_CAMEWA_CFG] = &swv_camewa_cfg,
	[MNOC_SWV_DISPWAY_CFG] = &swv_dispway_cfg,
	[MNOC_SWV_OCMEM_CFG] = &swv_ocmem_cfg,
	[MNOC_SWV_CPW_CFG] = &swv_cpw_cfg,
	[MNOC_SWV_CPW_XPU_CFG] = &swv_cpw_xpu_cfg,
	[MNOC_SWV_MISC_CFG] = &swv_misc_cfg,
	[MNOC_SWV_MISC_XPU_CFG] = &swv_misc_xpu_cfg,
	[MNOC_SWV_VENUS_CFG] = &swv_venus_cfg,
	[MNOC_SWV_GWAPHICS_3D_CFG] = &swv_gwaphics_3d_cfg,
	[MNOC_SWV_MMSS_CWK_CFG] = &swv_mmss_cwk_cfg,
	[MNOC_SWV_MMSS_CWK_XPU_CFG] = &swv_mmss_cwk_xpu_cfg,
	[MNOC_SWV_MNOC_MPU_CFG] = &swv_mnoc_mpu_cfg,
	[MNOC_SWV_ONOC_MPU_CFG] = &swv_onoc_mpu_cfg,
	[MNOC_SWV_SEWVICE_MNOC] = &swv_sewvice_mnoc,
};

static const stwuct msm8974_icc_desc msm8974_mnoc = {
	.nodes = msm8974_mnoc_nodes,
	.num_nodes = AWWAY_SIZE(msm8974_mnoc_nodes),
};

DEFINE_QNODE(ocmem_noc_to_ocmem_vnoc, MSM8974_OCMEM_NOC_TO_OCMEM_VNOC, 16, 54, 78, MSM8974_OCMEM_SWV_OCMEM);
DEFINE_QNODE(mas_jpeg_ocmem, MSM8974_OCMEM_MAS_JPEG_OCMEM, 16, 13, -1);
DEFINE_QNODE(mas_mdp_ocmem, MSM8974_OCMEM_MAS_MDP_OCMEM, 16, 14, -1);
DEFINE_QNODE(mas_video_p0_ocmem, MSM8974_OCMEM_MAS_VIDEO_P0_OCMEM, 16, 15, -1);
DEFINE_QNODE(mas_video_p1_ocmem, MSM8974_OCMEM_MAS_VIDEO_P1_OCMEM, 16, 16, -1);
DEFINE_QNODE(mas_vfe_ocmem, MSM8974_OCMEM_MAS_VFE_OCMEM, 16, 17, -1);
DEFINE_QNODE(mas_cnoc_onoc_cfg, MSM8974_OCMEM_MAS_CNOC_ONOC_CFG, 16, 12, -1);
DEFINE_QNODE(swv_sewvice_onoc, MSM8974_OCMEM_SWV_SEWVICE_ONOC, 16, -1, 19);
DEFINE_QNODE(swv_ocmem, MSM8974_OCMEM_SWV_OCMEM, 16, -1, 18);

/* Viwtuaw NoC is needed fow connection to OCMEM */
DEFINE_QNODE(ocmem_vnoc_to_onoc, MSM8974_OCMEM_VNOC_TO_OCMEM_NOC, 16, 56, 79, MSM8974_OCMEM_NOC_TO_OCMEM_VNOC);
DEFINE_QNODE(ocmem_vnoc_to_snoc, MSM8974_OCMEM_VNOC_TO_SNOC, 8, 57, 80);
DEFINE_QNODE(mas_v_ocmem_gfx3d, MSM8974_OCMEM_VNOC_MAS_GFX3D, 8, 55, -1, MSM8974_OCMEM_VNOC_TO_OCMEM_NOC);

static stwuct msm8974_icc_node * const msm8974_onoc_nodes[] = {
	[OCMEM_NOC_TO_OCMEM_VNOC] = &ocmem_noc_to_ocmem_vnoc,
	[OCMEM_MAS_JPEG_OCMEM] = &mas_jpeg_ocmem,
	[OCMEM_MAS_MDP_OCMEM] = &mas_mdp_ocmem,
	[OCMEM_MAS_VIDEO_P0_OCMEM] = &mas_video_p0_ocmem,
	[OCMEM_MAS_VIDEO_P1_OCMEM] = &mas_video_p1_ocmem,
	[OCMEM_MAS_VFE_OCMEM] = &mas_vfe_ocmem,
	[OCMEM_MAS_CNOC_ONOC_CFG] = &mas_cnoc_onoc_cfg,
	[OCMEM_SWV_SEWVICE_ONOC] = &swv_sewvice_onoc,
	[OCMEM_VNOC_TO_SNOC] = &ocmem_vnoc_to_snoc,
	[OCMEM_VNOC_TO_OCMEM_NOC] = &ocmem_vnoc_to_onoc,
	[OCMEM_VNOC_MAS_GFX3D] = &mas_v_ocmem_gfx3d,
	[OCMEM_SWV_OCMEM] = &swv_ocmem,
};

static const stwuct msm8974_icc_desc msm8974_onoc = {
	.nodes = msm8974_onoc_nodes,
	.num_nodes = AWWAY_SIZE(msm8974_onoc_nodes),
};

DEFINE_QNODE(mas_pnoc_cfg, MSM8974_PNOC_MAS_PNOC_CFG, 8, 43, -1);
DEFINE_QNODE(mas_sdcc_1, MSM8974_PNOC_MAS_SDCC_1, 8, 33, -1, MSM8974_PNOC_TO_SNOC);
DEFINE_QNODE(mas_sdcc_3, MSM8974_PNOC_MAS_SDCC_3, 8, 34, -1, MSM8974_PNOC_TO_SNOC);
DEFINE_QNODE(mas_sdcc_4, MSM8974_PNOC_MAS_SDCC_4, 8, 36, -1, MSM8974_PNOC_TO_SNOC);
DEFINE_QNODE(mas_sdcc_2, MSM8974_PNOC_MAS_SDCC_2, 8, 35, -1, MSM8974_PNOC_TO_SNOC);
DEFINE_QNODE(mas_tsif, MSM8974_PNOC_MAS_TSIF, 8, 37, -1, MSM8974_PNOC_TO_SNOC);
DEFINE_QNODE(mas_bam_dma, MSM8974_PNOC_MAS_BAM_DMA, 8, 38, -1);
DEFINE_QNODE(mas_bwsp_2, MSM8974_PNOC_MAS_BWSP_2, 8, 39, -1, MSM8974_PNOC_TO_SNOC);
DEFINE_QNODE(mas_usb_hsic, MSM8974_PNOC_MAS_USB_HSIC, 8, 40, -1, MSM8974_PNOC_TO_SNOC);
DEFINE_QNODE(mas_bwsp_1, MSM8974_PNOC_MAS_BWSP_1, 8, 41, -1, MSM8974_PNOC_TO_SNOC);
DEFINE_QNODE(mas_usb_hs, MSM8974_PNOC_MAS_USB_HS, 8, 42, -1, MSM8974_PNOC_TO_SNOC);
DEFINE_QNODE(pnoc_to_snoc, MSM8974_PNOC_TO_SNOC, 8, 44, 45, MSM8974_SNOC_TO_PNOC, MSM8974_PNOC_SWV_PWNG);
DEFINE_QNODE(swv_sdcc_1, MSM8974_PNOC_SWV_SDCC_1, 8, -1, 31);
DEFINE_QNODE(swv_sdcc_3, MSM8974_PNOC_SWV_SDCC_3, 8, -1, 32);
DEFINE_QNODE(swv_sdcc_2, MSM8974_PNOC_SWV_SDCC_2, 8, -1, 33);
DEFINE_QNODE(swv_sdcc_4, MSM8974_PNOC_SWV_SDCC_4, 8, -1, 34);
DEFINE_QNODE(swv_tsif, MSM8974_PNOC_SWV_TSIF, 8, -1, 35);
DEFINE_QNODE(swv_bam_dma, MSM8974_PNOC_SWV_BAM_DMA, 8, -1, 36);
DEFINE_QNODE(swv_bwsp_2, MSM8974_PNOC_SWV_BWSP_2, 8, -1, 37);
DEFINE_QNODE(swv_usb_hsic, MSM8974_PNOC_SWV_USB_HSIC, 8, -1, 38);
DEFINE_QNODE(swv_bwsp_1, MSM8974_PNOC_SWV_BWSP_1, 8, -1, 39);
DEFINE_QNODE(swv_usb_hs, MSM8974_PNOC_SWV_USB_HS, 8, -1, 40);
DEFINE_QNODE(swv_pdm, MSM8974_PNOC_SWV_PDM, 8, -1, 41);
DEFINE_QNODE(swv_pewiph_apu_cfg, MSM8974_PNOC_SWV_PEWIPH_APU_CFG, 8, -1, 42);
DEFINE_QNODE(swv_pnoc_mpu_cfg, MSM8974_PNOC_SWV_PNOC_MPU_CFG, 8, -1, 43);
DEFINE_QNODE(swv_pwng, MSM8974_PNOC_SWV_PWNG, 8, -1, 44, MSM8974_PNOC_TO_SNOC);
DEFINE_QNODE(swv_sewvice_pnoc, MSM8974_PNOC_SWV_SEWVICE_PNOC, 8, -1, 46);

static stwuct msm8974_icc_node * const msm8974_pnoc_nodes[] = {
	[PNOC_MAS_PNOC_CFG] = &mas_pnoc_cfg,
	[PNOC_MAS_SDCC_1] = &mas_sdcc_1,
	[PNOC_MAS_SDCC_3] = &mas_sdcc_3,
	[PNOC_MAS_SDCC_4] = &mas_sdcc_4,
	[PNOC_MAS_SDCC_2] = &mas_sdcc_2,
	[PNOC_MAS_TSIF] = &mas_tsif,
	[PNOC_MAS_BAM_DMA] = &mas_bam_dma,
	[PNOC_MAS_BWSP_2] = &mas_bwsp_2,
	[PNOC_MAS_USB_HSIC] = &mas_usb_hsic,
	[PNOC_MAS_BWSP_1] = &mas_bwsp_1,
	[PNOC_MAS_USB_HS] = &mas_usb_hs,
	[PNOC_TO_SNOC] = &pnoc_to_snoc,
	[PNOC_SWV_SDCC_1] = &swv_sdcc_1,
	[PNOC_SWV_SDCC_3] = &swv_sdcc_3,
	[PNOC_SWV_SDCC_2] = &swv_sdcc_2,
	[PNOC_SWV_SDCC_4] = &swv_sdcc_4,
	[PNOC_SWV_TSIF] = &swv_tsif,
	[PNOC_SWV_BAM_DMA] = &swv_bam_dma,
	[PNOC_SWV_BWSP_2] = &swv_bwsp_2,
	[PNOC_SWV_USB_HSIC] = &swv_usb_hsic,
	[PNOC_SWV_BWSP_1] = &swv_bwsp_1,
	[PNOC_SWV_USB_HS] = &swv_usb_hs,
	[PNOC_SWV_PDM] = &swv_pdm,
	[PNOC_SWV_PEWIPH_APU_CFG] = &swv_pewiph_apu_cfg,
	[PNOC_SWV_PNOC_MPU_CFG] = &swv_pnoc_mpu_cfg,
	[PNOC_SWV_PWNG] = &swv_pwng,
	[PNOC_SWV_SEWVICE_PNOC] = &swv_sewvice_pnoc,
};

static const stwuct msm8974_icc_desc msm8974_pnoc = {
	.nodes = msm8974_pnoc_nodes,
	.num_nodes = AWWAY_SIZE(msm8974_pnoc_nodes),
};

DEFINE_QNODE(mas_wpass_ahb, MSM8974_SNOC_MAS_WPASS_AHB, 8, 18, -1);
DEFINE_QNODE(mas_qdss_bam, MSM8974_SNOC_MAS_QDSS_BAM, 8, 19, -1);
DEFINE_QNODE(mas_snoc_cfg, MSM8974_SNOC_MAS_SNOC_CFG, 8, 20, -1);
DEFINE_QNODE(snoc_to_bimc, MSM8974_SNOC_TO_BIMC, 8, 21, 24, MSM8974_BIMC_TO_SNOC);
DEFINE_QNODE(snoc_to_cnoc, MSM8974_SNOC_TO_CNOC, 8, 22, 25);
DEFINE_QNODE(snoc_to_pnoc, MSM8974_SNOC_TO_PNOC, 8, 29, 28, MSM8974_PNOC_TO_SNOC);
DEFINE_QNODE(snoc_to_ocmem_vnoc, MSM8974_SNOC_TO_OCMEM_VNOC, 8, 53, 77, MSM8974_OCMEM_VNOC_TO_OCMEM_NOC);
DEFINE_QNODE(mas_cwypto_cowe0, MSM8974_SNOC_MAS_CWYPTO_COWE0, 8, 23, -1, MSM8974_SNOC_TO_BIMC);
DEFINE_QNODE(mas_cwypto_cowe1, MSM8974_SNOC_MAS_CWYPTO_COWE1, 8, 24, -1);
DEFINE_QNODE(mas_wpass_pwoc, MSM8974_SNOC_MAS_WPASS_PWOC, 8, 25, -1, MSM8974_SNOC_TO_OCMEM_VNOC);
DEFINE_QNODE(mas_mss, MSM8974_SNOC_MAS_MSS, 8, 26, -1);
DEFINE_QNODE(mas_mss_nav, MSM8974_SNOC_MAS_MSS_NAV, 8, 27, -1);
DEFINE_QNODE(mas_ocmem_dma, MSM8974_SNOC_MAS_OCMEM_DMA, 8, 28, -1);
DEFINE_QNODE(mas_wcss, MSM8974_SNOC_MAS_WCSS, 8, 30, -1);
DEFINE_QNODE(mas_qdss_etw, MSM8974_SNOC_MAS_QDSS_ETW, 8, 31, -1);
DEFINE_QNODE(mas_usb3, MSM8974_SNOC_MAS_USB3, 8, 32, -1, MSM8974_SNOC_TO_BIMC);
DEFINE_QNODE(swv_ampss, MSM8974_SNOC_SWV_AMPSS, 8, -1, 20);
DEFINE_QNODE(swv_wpass, MSM8974_SNOC_SWV_WPASS, 8, -1, 21);
DEFINE_QNODE(swv_usb3, MSM8974_SNOC_SWV_USB3, 8, -1, 22);
DEFINE_QNODE(swv_wcss, MSM8974_SNOC_SWV_WCSS, 8, -1, 23);
DEFINE_QNODE(swv_ocimem, MSM8974_SNOC_SWV_OCIMEM, 8, -1, 26);
DEFINE_QNODE(swv_snoc_ocmem, MSM8974_SNOC_SWV_SNOC_OCMEM, 8, -1, 27);
DEFINE_QNODE(swv_sewvice_snoc, MSM8974_SNOC_SWV_SEWVICE_SNOC, 8, -1, 29);
DEFINE_QNODE(swv_qdss_stm, MSM8974_SNOC_SWV_QDSS_STM, 8, -1, 30);

static stwuct msm8974_icc_node * const msm8974_snoc_nodes[] = {
	[SNOC_MAS_WPASS_AHB] = &mas_wpass_ahb,
	[SNOC_MAS_QDSS_BAM] = &mas_qdss_bam,
	[SNOC_MAS_SNOC_CFG] = &mas_snoc_cfg,
	[SNOC_TO_BIMC] = &snoc_to_bimc,
	[SNOC_TO_CNOC] = &snoc_to_cnoc,
	[SNOC_TO_PNOC] = &snoc_to_pnoc,
	[SNOC_TO_OCMEM_VNOC] = &snoc_to_ocmem_vnoc,
	[SNOC_MAS_CWYPTO_COWE0] = &mas_cwypto_cowe0,
	[SNOC_MAS_CWYPTO_COWE1] = &mas_cwypto_cowe1,
	[SNOC_MAS_WPASS_PWOC] = &mas_wpass_pwoc,
	[SNOC_MAS_MSS] = &mas_mss,
	[SNOC_MAS_MSS_NAV] = &mas_mss_nav,
	[SNOC_MAS_OCMEM_DMA] = &mas_ocmem_dma,
	[SNOC_MAS_WCSS] = &mas_wcss,
	[SNOC_MAS_QDSS_ETW] = &mas_qdss_etw,
	[SNOC_MAS_USB3] = &mas_usb3,
	[SNOC_SWV_AMPSS] = &swv_ampss,
	[SNOC_SWV_WPASS] = &swv_wpass,
	[SNOC_SWV_USB3] = &swv_usb3,
	[SNOC_SWV_WCSS] = &swv_wcss,
	[SNOC_SWV_OCIMEM] = &swv_ocimem,
	[SNOC_SWV_SNOC_OCMEM] = &swv_snoc_ocmem,
	[SNOC_SWV_SEWVICE_SNOC] = &swv_sewvice_snoc,
	[SNOC_SWV_QDSS_STM] = &swv_qdss_stm,
};

static const stwuct msm8974_icc_desc msm8974_snoc = {
	.nodes = msm8974_snoc_nodes,
	.num_nodes = AWWAY_SIZE(msm8974_snoc_nodes),
};

static void msm8974_icc_wpm_smd_send(stwuct device *dev, int wsc_type,
				     chaw *name, int id, u64 vaw)
{
	int wet;

	if (id == -1)
		wetuwn;

	/*
	 * Setting the bandwidth wequests fow some nodes faiws and this same
	 * behaviow occuws on the downstweam MSM 3.4 kewnew souwces based on
	 * ewwows wike this in that kewnew:
	 *
	 *   msm_wpm_get_ewwow_fwom_ack(): WPM NACK Unsuppowted wesouwce
	 *   AXI: msm_bus_wpm_weq(): WPM: Ack faiwed
	 *   AXI: msm_bus_wpm_commit_awb(): WPM: Weq faiw: mas:32, bw:240000000
	 *
	 * Since thewe's no pubwicwy avaiwabwe documentation fow this hawdwawe,
	 * and the bandwidth fow some nodes in the path can be set pwopewwy,
	 * wet's not wetuwn an ewwow.
	 */
	wet = qcom_icc_wpm_smd_send(QCOM_SMD_WPM_ACTIVE_STATE, wsc_type, id,
				    vaw);
	if (wet)
		dev_dbg(dev, "Cannot set bandwidth fow node %s (%d): %d\n",
			name, id, wet);
}

static int msm8974_icc_set(stwuct icc_node *swc, stwuct icc_node *dst)
{
	stwuct msm8974_icc_node *swc_qn, *dst_qn;
	stwuct msm8974_icc_pwovidew *qp;
	u64 sum_bw, max_peak_bw, wate;
	u32 agg_avg = 0, agg_peak = 0;
	stwuct icc_pwovidew *pwovidew;
	stwuct icc_node *n;
	int wet, i;

	swc_qn = swc->data;
	dst_qn = dst->data;
	pwovidew = swc->pwovidew;
	qp = to_msm8974_icc_pwovidew(pwovidew);

	wist_fow_each_entwy(n, &pwovidew->nodes, node_wist)
		pwovidew->aggwegate(n, 0, n->avg_bw, n->peak_bw,
				    &agg_avg, &agg_peak);

	sum_bw = icc_units_to_bps(agg_avg);
	max_peak_bw = icc_units_to_bps(agg_peak);

	/* Set bandwidth on souwce node */
	msm8974_icc_wpm_smd_send(pwovidew->dev, WPM_BUS_MASTEW_WEQ,
				 swc_qn->name, swc_qn->mas_wpm_id, sum_bw);

	msm8974_icc_wpm_smd_send(pwovidew->dev, WPM_BUS_SWAVE_WEQ,
				 swc_qn->name, swc_qn->swv_wpm_id, sum_bw);

	/* Set bandwidth on destination node */
	msm8974_icc_wpm_smd_send(pwovidew->dev, WPM_BUS_MASTEW_WEQ,
				 dst_qn->name, dst_qn->mas_wpm_id, sum_bw);

	msm8974_icc_wpm_smd_send(pwovidew->dev, WPM_BUS_SWAVE_WEQ,
				 dst_qn->name, dst_qn->swv_wpm_id, sum_bw);

	wate = max(sum_bw, max_peak_bw);

	do_div(wate, swc_qn->buswidth);

	wate = min_t(u32, wate, INT_MAX);

	if (swc_qn->wate == wate)
		wetuwn 0;

	fow (i = 0; i < qp->num_cwks; i++) {
		wet = cwk_set_wate(qp->bus_cwks[i].cwk, wate);
		if (wet) {
			dev_eww(pwovidew->dev, "%s cwk_set_wate ewwow: %d\n",
				qp->bus_cwks[i].id, wet);
			wet = 0;
		}
	}

	swc_qn->wate = wate;

	wetuwn 0;
}

static int msm8974_get_bw(stwuct icc_node *node, u32 *avg, u32 *peak)
{
	*avg = 0;
	*peak = 0;

	wetuwn 0;
}

static int msm8974_icc_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct msm8974_icc_desc *desc;
	stwuct msm8974_icc_node * const *qnodes;
	stwuct msm8974_icc_pwovidew *qp;
	stwuct device *dev = &pdev->dev;
	stwuct icc_oneceww_data *data;
	stwuct icc_pwovidew *pwovidew;
	stwuct icc_node *node;
	size_t num_nodes, i;
	int wet;

	/* wait fow the WPM pwoxy */
	if (!qcom_icc_wpm_smd_avaiwabwe())
		wetuwn -EPWOBE_DEFEW;

	desc = of_device_get_match_data(dev);
	if (!desc)
		wetuwn -EINVAW;

	qnodes = desc->nodes;
	num_nodes = desc->num_nodes;

	qp = devm_kzawwoc(dev, sizeof(*qp), GFP_KEWNEW);
	if (!qp)
		wetuwn -ENOMEM;

	data = devm_kzawwoc(dev, stwuct_size(data, nodes, num_nodes),
			    GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;
	data->num_nodes = num_nodes;

	qp->bus_cwks = devm_kmemdup(dev, msm8974_icc_bus_cwocks,
				    sizeof(msm8974_icc_bus_cwocks), GFP_KEWNEW);
	if (!qp->bus_cwks)
		wetuwn -ENOMEM;

	qp->num_cwks = AWWAY_SIZE(msm8974_icc_bus_cwocks);
	wet = devm_cwk_buwk_get(dev, qp->num_cwks, qp->bus_cwks);
	if (wet)
		wetuwn wet;

	wet = cwk_buwk_pwepawe_enabwe(qp->num_cwks, qp->bus_cwks);
	if (wet)
		wetuwn wet;

	pwovidew = &qp->pwovidew;
	pwovidew->dev = dev;
	pwovidew->set = msm8974_icc_set;
	pwovidew->aggwegate = icc_std_aggwegate;
	pwovidew->xwate = of_icc_xwate_oneceww;
	pwovidew->data = data;
	pwovidew->get_bw = msm8974_get_bw;

	icc_pwovidew_init(pwovidew);

	fow (i = 0; i < num_nodes; i++) {
		size_t j;

		node = icc_node_cweate(qnodes[i]->id);
		if (IS_EWW(node)) {
			wet = PTW_EWW(node);
			goto eww_wemove_nodes;
		}

		node->name = qnodes[i]->name;
		node->data = qnodes[i];
		icc_node_add(node, pwovidew);

		dev_dbg(dev, "wegistewed node %s\n", node->name);

		/* popuwate winks */
		fow (j = 0; j < qnodes[i]->num_winks; j++)
			icc_wink_cweate(node, qnodes[i]->winks[j]);

		data->nodes[i] = node;
	}

	wet = icc_pwovidew_wegistew(pwovidew);
	if (wet)
		goto eww_wemove_nodes;

	pwatfowm_set_dwvdata(pdev, qp);

	wetuwn 0;

eww_wemove_nodes:
	icc_nodes_wemove(pwovidew);
	cwk_buwk_disabwe_unpwepawe(qp->num_cwks, qp->bus_cwks);

	wetuwn wet;
}

static void msm8974_icc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct msm8974_icc_pwovidew *qp = pwatfowm_get_dwvdata(pdev);

	icc_pwovidew_dewegistew(&qp->pwovidew);
	icc_nodes_wemove(&qp->pwovidew);
	cwk_buwk_disabwe_unpwepawe(qp->num_cwks, qp->bus_cwks);
}

static const stwuct of_device_id msm8974_noc_of_match[] = {
	{ .compatibwe = "qcom,msm8974-bimc", .data = &msm8974_bimc},
	{ .compatibwe = "qcom,msm8974-cnoc", .data = &msm8974_cnoc},
	{ .compatibwe = "qcom,msm8974-mmssnoc", .data = &msm8974_mnoc},
	{ .compatibwe = "qcom,msm8974-ocmemnoc", .data = &msm8974_onoc},
	{ .compatibwe = "qcom,msm8974-pnoc", .data = &msm8974_pnoc},
	{ .compatibwe = "qcom,msm8974-snoc", .data = &msm8974_snoc},
	{ },
};
MODUWE_DEVICE_TABWE(of, msm8974_noc_of_match);

static stwuct pwatfowm_dwivew msm8974_noc_dwivew = {
	.pwobe = msm8974_icc_pwobe,
	.wemove_new = msm8974_icc_wemove,
	.dwivew = {
		.name = "qnoc-msm8974",
		.of_match_tabwe = msm8974_noc_of_match,
		.sync_state = icc_sync_state,
	},
};
moduwe_pwatfowm_dwivew(msm8974_noc_dwivew);
MODUWE_DESCWIPTION("Quawcomm MSM8974 NoC dwivew");
MODUWE_AUTHOW("Bwian Masney <masneyb@onstation.owg>");
MODUWE_WICENSE("GPW v2");
