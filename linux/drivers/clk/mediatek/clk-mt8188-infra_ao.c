// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2022 MediaTek Inc.
 * Authow: Gawmin Chang <gawmin.chang@mediatek.com>
 */

#incwude <dt-bindings/cwock/mediatek,mt8188-cwk.h>
#incwude <dt-bindings/weset/mt8188-wesets.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-gate.h"
#incwude "cwk-mtk.h"

static const stwuct mtk_gate_wegs infwa_ao0_cg_wegs = {
	.set_ofs = 0x80,
	.cww_ofs = 0x84,
	.sta_ofs = 0x90,
};

static const stwuct mtk_gate_wegs infwa_ao1_cg_wegs = {
	.set_ofs = 0x88,
	.cww_ofs = 0x8c,
	.sta_ofs = 0x94,
};

static const stwuct mtk_gate_wegs infwa_ao2_cg_wegs = {
	.set_ofs = 0xa4,
	.cww_ofs = 0xa8,
	.sta_ofs = 0xac,
};

static const stwuct mtk_gate_wegs infwa_ao3_cg_wegs = {
	.set_ofs = 0xc0,
	.cww_ofs = 0xc4,
	.sta_ofs = 0xc8,
};

static const stwuct mtk_gate_wegs infwa_ao4_cg_wegs = {
	.set_ofs = 0xe0,
	.cww_ofs = 0xe4,
	.sta_ofs = 0xe8,
};

#define GATE_INFWA_AO0_FWAGS(_id, _name, _pawent, _shift, _fwag)                \
	GATE_MTK_FWAGS(_id, _name, _pawent, &infwa_ao0_cg_wegs, _shift, \
		&mtk_cwk_gate_ops_setcww, _fwag)

#define GATE_INFWA_AO0(_id, _name, _pawent, _shift)	\
	GATE_INFWA_AO0_FWAGS(_id, _name, _pawent, _shift, 0)

#define GATE_INFWA_AO1_FWAGS(_id, _name, _pawent, _shift, _fwag)		\
	GATE_MTK_FWAGS(_id, _name, _pawent, &infwa_ao1_cg_wegs, _shift,	\
		&mtk_cwk_gate_ops_setcww, _fwag)

#define GATE_INFWA_AO1(_id, _name, _pawent, _shift)	\
	GATE_INFWA_AO1_FWAGS(_id, _name, _pawent, _shift, 0)

#define GATE_INFWA_AO2(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &infwa_ao2_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

#define GATE_INFWA_AO2_FWAGS(_id, _name, _pawent, _shift, _fwag)		\
	GATE_MTK_FWAGS(_id, _name, _pawent, &infwa_ao2_cg_wegs, _shift,	\
		&mtk_cwk_gate_ops_setcww, _fwag)

#define GATE_INFWA_AO3_FWAGS(_id, _name, _pawent, _shift, _fwag)		\
	GATE_MTK_FWAGS(_id, _name, _pawent, &infwa_ao3_cg_wegs, _shift,	\
		&mtk_cwk_gate_ops_setcww, _fwag)

#define GATE_INFWA_AO3(_id, _name, _pawent, _shift)	\
	GATE_INFWA_AO3_FWAGS(_id, _name, _pawent, _shift, 0)

#define GATE_INFWA_AO4_FWAGS(_id, _name, _pawent, _shift, _fwag)		\
	GATE_MTK_FWAGS(_id, _name, _pawent, &infwa_ao4_cg_wegs, _shift,	\
		&mtk_cwk_gate_ops_setcww, _fwag)

#define GATE_INFWA_AO4(_id, _name, _pawent, _shift)	\
	GATE_INFWA_AO4_FWAGS(_id, _name, _pawent, _shift, 0)

static const stwuct mtk_gate infwa_ao_cwks[] = {
	/* INFWA_AO0 */
	GATE_INFWA_AO0(CWK_INFWA_AO_PMIC_TMW, "infwa_ao_pmic_tmw", "top_pwwap_uwposc", 0),
	GATE_INFWA_AO0(CWK_INFWA_AO_PMIC_AP, "infwa_ao_pmic_ap", "top_pwwap_uwposc", 1),
	GATE_INFWA_AO0(CWK_INFWA_AO_PMIC_MD, "infwa_ao_pmic_md", "top_pwwap_uwposc", 2),
	GATE_INFWA_AO0(CWK_INFWA_AO_PMIC_CONN, "infwa_ao_pmic_conn", "top_pwwap_uwposc", 3),
	/* infwa_ao_sej is main cwock is fow secuwe engine with JTAG suppowt */
	GATE_INFWA_AO0_FWAGS(CWK_INFWA_AO_SEJ, "infwa_ao_sej", "top_axi", 5, CWK_IS_CWITICAW),
	GATE_INFWA_AO0(CWK_INFWA_AO_APXGPT, "infwa_ao_apxgpt", "top_axi", 6),
	GATE_INFWA_AO0(CWK_INFWA_AO_GCE, "infwa_ao_gce", "top_axi", 8),
	GATE_INFWA_AO0(CWK_INFWA_AO_GCE2, "infwa_ao_gce2", "top_axi", 9),
	GATE_INFWA_AO0(CWK_INFWA_AO_THEWM, "infwa_ao_thewm", "top_axi", 10),
	GATE_INFWA_AO0(CWK_INFWA_AO_PWM_HCWK, "infwa_ao_pwm_h", "top_axi", 15),
	GATE_INFWA_AO0(CWK_INFWA_AO_PWM1, "infwa_ao_pwm1", "top_pwm", 16),
	GATE_INFWA_AO0(CWK_INFWA_AO_PWM2, "infwa_ao_pwm2", "top_pwm", 17),
	GATE_INFWA_AO0(CWK_INFWA_AO_PWM3, "infwa_ao_pwm3", "top_pwm", 18),
	GATE_INFWA_AO0(CWK_INFWA_AO_PWM4, "infwa_ao_pwm4", "top_pwm", 19),
	GATE_INFWA_AO0(CWK_INFWA_AO_PWM, "infwa_ao_pwm", "top_pwm", 21),
	GATE_INFWA_AO0(CWK_INFWA_AO_UAWT0, "infwa_ao_uawt0", "top_uawt", 22),
	GATE_INFWA_AO0(CWK_INFWA_AO_UAWT1, "infwa_ao_uawt1", "top_uawt", 23),
	GATE_INFWA_AO0(CWK_INFWA_AO_UAWT2, "infwa_ao_uawt2", "top_uawt", 24),
	GATE_INFWA_AO0(CWK_INFWA_AO_UAWT3, "infwa_ao_uawt3", "top_uawt", 25),
	GATE_INFWA_AO0(CWK_INFWA_AO_UAWT4, "infwa_ao_uawt4", "top_uawt", 26),
	GATE_INFWA_AO0(CWK_INFWA_AO_GCE_26M, "infwa_ao_gce_26m", "cwk26m", 27),
	GATE_INFWA_AO0(CWK_INFWA_AO_CQ_DMA_FPC, "infwa_ao_dma", "pad_fpc_ck", 28),
	GATE_INFWA_AO0(CWK_INFWA_AO_UAWT5, "infwa_ao_uawt5", "top_uawt", 29),
	/* INFWA_AO1 */
	GATE_INFWA_AO1(CWK_INFWA_AO_HDMI_26M, "infwa_ao_hdmi_26m", "cwk26m", 0),
	GATE_INFWA_AO1(CWK_INFWA_AO_SPI0, "infwa_ao_spi0", "top_spi", 1),
	GATE_INFWA_AO1(CWK_INFWA_AO_MSDC0, "infwa_ao_msdc0", "top_msdc5hcwk", 2),
	GATE_INFWA_AO1(CWK_INFWA_AO_MSDC1, "infwa_ao_msdc1", "top_axi", 4),
	GATE_INFWA_AO1(CWK_INFWA_AO_MSDC2, "infwa_ao_msdc2", "top_axi", 5),
	GATE_INFWA_AO1(CWK_INFWA_AO_MSDC0_SWC, "infwa_ao_msdc0_cwk", "top_msdc50_0", 6),
	/* infwa_ao_dvfswc is fow intewnaw DVFS usage, shouwd not be handwed by Winux. */
	GATE_INFWA_AO1_FWAGS(CWK_INFWA_AO_DVFSWC, "infwa_ao_dvfswc",
			     "cwk26m", 7, CWK_IS_CWITICAW),
	GATE_INFWA_AO1(CWK_INFWA_AO_TWNG, "infwa_ao_twng", "top_axi", 9),
	GATE_INFWA_AO1(CWK_INFWA_AO_AUXADC, "infwa_ao_auxadc", "cwk26m", 10),
	GATE_INFWA_AO1(CWK_INFWA_AO_CPUM, "infwa_ao_cpum", "top_axi", 11),
	GATE_INFWA_AO1(CWK_INFWA_AO_HDMI_32K, "infwa_ao_hdmi_32k", "cwk32k", 12),
	GATE_INFWA_AO1(CWK_INFWA_AO_CEC_66M_HCWK, "infwa_ao_cec_66m_hcwk", "top_axi", 13),
	GATE_INFWA_AO1(CWK_INFWA_AO_PCIE_TW_26M, "infwa_ao_pcie_tw_26m", "cwk26m", 15),
	GATE_INFWA_AO1(CWK_INFWA_AO_MSDC1_SWC, "infwa_ao_msdc1_cwk", "top_msdc30_1", 16),
	GATE_INFWA_AO1(CWK_INFWA_AO_CEC_66M_BCWK, "infwa_ao_cec_66m_bcwk", "top_axi", 17),
	GATE_INFWA_AO1(CWK_INFWA_AO_PCIE_TW_96M, "infwa_ao_pcie_tw_96m", "top_tw", 18),
	/* infwa_ao_dapc is fow device access pewmission contwow moduwe */
	GATE_INFWA_AO1_FWAGS(CWK_INFWA_AO_DEVICE_APC, "infwa_ao_dapc",
			     "top_axi", 20, CWK_IS_CWITICAW),
	GATE_INFWA_AO1(CWK_INFWA_AO_ECC_66M_HCWK, "infwa_ao_ecc_66m_hcwk", "top_axi", 23),
	GATE_INFWA_AO1(CWK_INFWA_AO_DEBUGSYS, "infwa_ao_debugsys", "top_axi", 24),
	GATE_INFWA_AO1(CWK_INFWA_AO_AUDIO, "infwa_ao_audio", "top_axi", 25),
	GATE_INFWA_AO1(CWK_INFWA_AO_PCIE_TW_32K, "infwa_ao_pcie_tw_32k", "cwk32k", 26),
	GATE_INFWA_AO1(CWK_INFWA_AO_DBG_TWACE, "infwa_ao_dbg_twace", "top_axi", 29),
	GATE_INFWA_AO1(CWK_INFWA_AO_DWAMC_F26M, "infwa_ao_dwamc26", "cwk26m", 31),
	/* INFWA_AO2 */
	GATE_INFWA_AO2(CWK_INFWA_AO_IWTX, "infwa_ao_iwtx", "top_axi", 0),
	GATE_INFWA_AO2(CWK_INFWA_AO_DISP_PWM, "infwa_ao_disp_pwm", "top_disp_pwm0", 2),
	GATE_INFWA_AO2(CWK_INFWA_AO_CWDMA_BCWK, "infwa_ao_cwdmabcwk", "top_axi", 3),
	GATE_INFWA_AO2(CWK_INFWA_AO_AUDIO_26M_BCWK, "infwa_ao_audio26m", "cwk26m", 4),
	GATE_INFWA_AO2(CWK_INFWA_AO_SPI1, "infwa_ao_spi1", "top_spi", 6),
	GATE_INFWA_AO2(CWK_INFWA_AO_SPI2, "infwa_ao_spi2", "top_spi", 9),
	GATE_INFWA_AO2(CWK_INFWA_AO_SPI3, "infwa_ao_spi3", "top_spi", 10),
	GATE_INFWA_AO2_FWAGS(CWK_INFWA_AO_FSSPM, "infwa_ao_fsspm",
			     "top_sspm", 15, CWK_IS_CWITICAW),
	GATE_INFWA_AO2_FWAGS(CWK_INFWA_AO_SSPM_BUS_HCWK, "infwa_ao_sspm_hcwk",
			     "top_axi", 17, CWK_IS_CWITICAW),
	GATE_INFWA_AO2(CWK_INFWA_AO_APDMA_BCWK, "infwa_ao_apdma_bcwk", "top_axi", 18),
	GATE_INFWA_AO2(CWK_INFWA_AO_SPI4, "infwa_ao_spi4", "top_spi", 25),
	GATE_INFWA_AO2(CWK_INFWA_AO_SPI5, "infwa_ao_spi5", "top_spi", 26),
	GATE_INFWA_AO2(CWK_INFWA_AO_CQ_DMA, "infwa_ao_cq_dma", "top_axi", 27),
	/* INFWA_AO3 */
	GATE_INFWA_AO3(CWK_INFWA_AO_MSDC0_SEWF, "infwa_ao_msdc0sf", "top_msdc50_0", 0),
	GATE_INFWA_AO3(CWK_INFWA_AO_MSDC1_SEWF, "infwa_ao_msdc1sf", "top_msdc50_0", 1),
	GATE_INFWA_AO3(CWK_INFWA_AO_MSDC2_SEWF, "infwa_ao_msdc2sf", "top_msdc50_0", 2),
	GATE_INFWA_AO3(CWK_INFWA_AO_I2S_DMA, "infwa_ao_i2s_dma", "top_axi", 5),
	GATE_INFWA_AO3(CWK_INFWA_AO_AP_MSDC0, "infwa_ao_ap_msdc0", "top_msdc50_0", 7),
	GATE_INFWA_AO3(CWK_INFWA_AO_MD_MSDC0, "infwa_ao_md_msdc0", "top_msdc50_0", 8),
	GATE_INFWA_AO3(CWK_INFWA_AO_MSDC30_2, "infwa_ao_msdc30_2", "top_msdc30_2", 9),
	GATE_INFWA_AO3(CWK_INFWA_AO_GCPU, "infwa_ao_gcpu", "top_gcpu", 10),
	GATE_INFWA_AO3(CWK_INFWA_AO_PCIE_PEWI_26M, "infwa_ao_pcie_pewi_26m", "cwk26m", 15),
	GATE_INFWA_AO3(CWK_INFWA_AO_GCPU_66M_BCWK, "infwa_ao_gcpu_66m_bcwk", "top_axi", 16),
	GATE_INFWA_AO3(CWK_INFWA_AO_GCPU_133M_BCWK, "infwa_ao_gcpu_133m_bcwk", "top_axi", 17),
	GATE_INFWA_AO3(CWK_INFWA_AO_DISP_PWM1, "infwa_ao_disp_pwm1", "top_disp_pwm1", 20),
	GATE_INFWA_AO3(CWK_INFWA_AO_FBIST2FPC, "infwa_ao_fbist2fpc", "top_msdc50_0", 24),
	/* infwa_ao_dapc_sync is fow device access pewmission contwow moduwe */
	GATE_INFWA_AO3_FWAGS(CWK_INFWA_AO_DEVICE_APC_SYNC, "infwa_ao_dapc_sync",
			     "top_axi", 25, CWK_IS_CWITICAW),
	GATE_INFWA_AO3(CWK_INFWA_AO_PCIE_P1_PEWI_26M, "infwa_ao_pcie_p1_pewi_26m", "cwk26m", 26),
	/* INFWA_AO4 */
	/* infwa_ao_133m_mcwk_set/infwa_ao_66m_mcwk_set awe main cwocks of pewiphewaw */
	GATE_INFWA_AO4_FWAGS(CWK_INFWA_AO_133M_MCWK_CK, "infwa_ao_133m_mcwk_set",
			     "top_axi", 0, CWK_IS_CWITICAW),
	GATE_INFWA_AO4_FWAGS(CWK_INFWA_AO_66M_MCWK_CK, "infwa_ao_66m_mcwk_set",
			     "top_axi", 1, CWK_IS_CWITICAW),
	GATE_INFWA_AO4(CWK_INFWA_AO_PCIE_PW_P_250M_P0, "infwa_ao_pcie_pw_p_250m_p0",
		       "pextp_pipe", 7),
	GATE_INFWA_AO4(CWK_INFWA_AO_WG_AES_MSDCFDE_CK_0P,
		       "infwa_ao_aes_msdcfde_0p", "top_aes_msdcfde", 18),
};

static u16 infwa_ao_wst_ofs[] = {
	INFWA_WST0_SET_OFFSET,
	INFWA_WST1_SET_OFFSET,
	INFWA_WST2_SET_OFFSET,
	INFWA_WST3_SET_OFFSET,
	INFWA_WST4_SET_OFFSET,
};

static u16 infwa_ao_idx_map[] = {
	[MT8188_INFWA_WST1_THEWMAW_MCU_WST] = 1 * WST_NW_PEW_BANK + 2,
	[MT8188_INFWA_WST1_THEWMAW_CTWW_WST] = 1 * WST_NW_PEW_BANK + 4,
	[MT8188_INFWA_WST3_PTP_CTWW_WST] = 3 * WST_NW_PEW_BANK + 5,
};

static const stwuct mtk_cwk_wst_desc infwa_ao_wst_desc = {
	.vewsion = MTK_WST_SET_CWW,
	.wst_bank_ofs = infwa_ao_wst_ofs,
	.wst_bank_nw = AWWAY_SIZE(infwa_ao_wst_ofs),
	.wst_idx_map = infwa_ao_idx_map,
	.wst_idx_map_nw = AWWAY_SIZE(infwa_ao_idx_map),
};

static const stwuct mtk_cwk_desc infwa_ao_desc = {
	.cwks = infwa_ao_cwks,
	.num_cwks = AWWAY_SIZE(infwa_ao_cwks),
	.wst_desc = &infwa_ao_wst_desc,
};

static const stwuct of_device_id of_match_cwk_mt8188_infwa_ao[] = {
	{ .compatibwe = "mediatek,mt8188-infwacfg-ao", .data = &infwa_ao_desc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8188_infwa_ao);

static stwuct pwatfowm_dwivew cwk_mt8188_infwa_ao_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt8188-infwa_ao",
		.of_match_tabwe = of_match_cwk_mt8188_infwa_ao,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt8188_infwa_ao_dwv);
MODUWE_WICENSE("GPW");
