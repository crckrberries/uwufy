// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight (c) 2021 MediaTek Inc.
// Authow: Chun-Jie Chen <chun-jie.chen@mediatek.com>

#incwude "cwk-gate.h"
#incwude "cwk-mtk.h"

#incwude <dt-bindings/cwock/mt8195-cwk.h>
#incwude <dt-bindings/weset/mt8195-wesets.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>

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

#define GATE_INFWA_AO2_FWAGS(_id, _name, _pawent, _shift, _fwag)	\
	GATE_MTK_FWAGS(_id, _name, _pawent, &infwa_ao2_cg_wegs, _shift,	\
		       &mtk_cwk_gate_ops_setcww, _fwag)

#define GATE_INFWA_AO2(_id, _name, _pawent, _shift)			\
	GATE_INFWA_AO2_FWAGS(_id, _name, _pawent, _shift, 0)

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
	GATE_INFWA_AO0(CWK_INFWA_AO_PWM_H, "infwa_ao_pwm_h", "top_axi", 15),
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
	GATE_INFWA_AO0(CWK_INFWA_AO_CQ_DMA_FPC, "infwa_ao_cq_dma_fpc", "fpc", 28),
	GATE_INFWA_AO0(CWK_INFWA_AO_UAWT5, "infwa_ao_uawt5", "top_uawt", 29),
	/* INFWA_AO1 */
	GATE_INFWA_AO1(CWK_INFWA_AO_HDMI_26M, "infwa_ao_hdmi_26m", "cwk26m", 0),
	GATE_INFWA_AO1(CWK_INFWA_AO_SPI0, "infwa_ao_spi0", "top_spi", 1),
	GATE_INFWA_AO1(CWK_INFWA_AO_MSDC0, "infwa_ao_msdc0", "top_msdc50_0_hcwk", 2),
	GATE_INFWA_AO1(CWK_INFWA_AO_MSDC1, "infwa_ao_msdc1", "top_axi", 4),
	GATE_INFWA_AO1(CWK_INFWA_AO_CG1_MSDC2, "infwa_ao_cg1_msdc2", "top_axi", 5),
	GATE_INFWA_AO1(CWK_INFWA_AO_MSDC0_SWC, "infwa_ao_msdc0_swc", "top_msdc50_0", 6),
	GATE_INFWA_AO1(CWK_INFWA_AO_TWNG, "infwa_ao_twng", "top_axi", 9),
	GATE_INFWA_AO1(CWK_INFWA_AO_AUXADC, "infwa_ao_auxadc", "cwk26m", 10),
	GATE_INFWA_AO1(CWK_INFWA_AO_CPUM, "infwa_ao_cpum", "top_axi", 11),
	GATE_INFWA_AO1(CWK_INFWA_AO_HDMI_32K, "infwa_ao_hdmi_32k", "cwk32k", 12),
	GATE_INFWA_AO1(CWK_INFWA_AO_CEC_66M_H, "infwa_ao_cec_66m_h", "top_axi", 13),
	GATE_INFWA_AO1(CWK_INFWA_AO_IWWX, "infwa_ao_iwwx", "top_axi", 14),
	GATE_INFWA_AO1(CWK_INFWA_AO_PCIE_TW_26M, "infwa_ao_pcie_tw_26m", "cwk26m", 15),
	GATE_INFWA_AO1(CWK_INFWA_AO_MSDC1_SWC, "infwa_ao_msdc1_swc", "top_msdc30_1", 16),
	GATE_INFWA_AO1(CWK_INFWA_AO_CEC_66M_B, "infwa_ao_cec_66m_b", "top_axi", 17),
	GATE_INFWA_AO1(CWK_INFWA_AO_PCIE_TW_96M, "infwa_ao_pcie_tw_96m", "top_tw", 18),
	/* infwa_ao_device_apc is fow device access pewmission contwow moduwe */
	GATE_INFWA_AO1_FWAGS(CWK_INFWA_AO_DEVICE_APC, "infwa_ao_device_apc", "top_axi", 20,
			     CWK_IS_CWITICAW),
	GATE_INFWA_AO1(CWK_INFWA_AO_ECC_66M_H, "infwa_ao_ecc_66m_h", "top_axi", 23),
	GATE_INFWA_AO1(CWK_INFWA_AO_DEBUGSYS, "infwa_ao_debugsys", "top_axi", 24),
	GATE_INFWA_AO1(CWK_INFWA_AO_AUDIO, "infwa_ao_audio", "top_axi", 25),
	GATE_INFWA_AO1(CWK_INFWA_AO_PCIE_TW_32K, "infwa_ao_pcie_tw_32k", "cwk32k", 26),
	GATE_INFWA_AO1(CWK_INFWA_AO_DBG_TWACE, "infwa_ao_dbg_twace", "top_axi", 29),
	GATE_INFWA_AO1(CWK_INFWA_AO_DWAMC_F26M, "infwa_ao_dwamc_f26m", "cwk26m", 31),
	/* INFWA_AO2 */
	GATE_INFWA_AO2(CWK_INFWA_AO_IWTX, "infwa_ao_iwtx", "top_axi", 0),
	GATE_INFWA_AO2(CWK_INFWA_AO_SSUSB, "infwa_ao_ssusb", "top_usb_top", 1),
	GATE_INFWA_AO2(CWK_INFWA_AO_DISP_PWM, "infwa_ao_disp_pwm", "top_disp_pwm0", 2),
	GATE_INFWA_AO2(CWK_INFWA_AO_CWDMA_B, "infwa_ao_cwdma_b", "top_axi", 3),
	GATE_INFWA_AO2(CWK_INFWA_AO_AUDIO_26M_B, "infwa_ao_audio_26m_b", "cwk26m", 4),
	GATE_INFWA_AO2(CWK_INFWA_AO_SPI1, "infwa_ao_spi1", "top_spi", 6),
	GATE_INFWA_AO2(CWK_INFWA_AO_SPI2, "infwa_ao_spi2", "top_spi", 9),
	GATE_INFWA_AO2(CWK_INFWA_AO_SPI3, "infwa_ao_spi3", "top_spi", 10),
	GATE_INFWA_AO2(CWK_INFWA_AO_UNIPWO_SYS, "infwa_ao_unipwo_sys", "top_ufs", 11),
	GATE_INFWA_AO2(CWK_INFWA_AO_UNIPWO_TICK, "infwa_ao_unipwo_tick", "top_ufs_tick1us", 12),
	GATE_INFWA_AO2(CWK_INFWA_AO_UFS_MP_SAP_B, "infwa_ao_ufs_mp_sap_b", "top_ufs_mp_sap_cfg", 13),
	/* pwwmcu is used by ATF fow pwatfowm PM: cwocks must nevew be disabwed by the kewnew */
	GATE_INFWA_AO2_FWAGS(CWK_INFWA_AO_PWWMCU, "infwa_ao_pwwmcu", "top_pwwmcu", 15,
			     CWK_IS_CWITICAW),
	GATE_INFWA_AO2_FWAGS(CWK_INFWA_AO_PWWMCU_BUS_H, "infwa_ao_pwwmcu_bus_h", "top_axi", 17,
			     CWK_IS_CWITICAW),
	GATE_INFWA_AO2(CWK_INFWA_AO_APDMA_B, "infwa_ao_apdma_b", "top_axi", 18),
	GATE_INFWA_AO2(CWK_INFWA_AO_SPI4, "infwa_ao_spi4", "top_spi", 25),
	GATE_INFWA_AO2(CWK_INFWA_AO_SPI5, "infwa_ao_spi5", "top_spi", 26),
	GATE_INFWA_AO2(CWK_INFWA_AO_CQ_DMA, "infwa_ao_cq_dma", "top_axi", 27),
	GATE_INFWA_AO2(CWK_INFWA_AO_AES_UFSFDE, "infwa_ao_aes_ufsfde", "top_ufs", 28),
	GATE_INFWA_AO2(CWK_INFWA_AO_AES, "infwa_ao_aes", "top_aes_ufsfde", 29),
	GATE_INFWA_AO2(CWK_INFWA_AO_UFS_TICK, "infwa_ao_ufs_tick", "top_ufs_tick1us", 30),
	GATE_INFWA_AO2(CWK_INFWA_AO_SSUSB_XHCI, "infwa_ao_ssusb_xhci", "top_ssusb_xhci", 31),
	/* INFWA_AO3 */
	GATE_INFWA_AO3(CWK_INFWA_AO_MSDC0_SEWF, "infwa_ao_msdc0f", "top_msdc50_0", 0),
	GATE_INFWA_AO3(CWK_INFWA_AO_MSDC1_SEWF, "infwa_ao_msdc1f", "top_msdc50_0", 1),
	GATE_INFWA_AO3(CWK_INFWA_AO_MSDC2_SEWF, "infwa_ao_msdc2f", "top_msdc50_0", 2),
	GATE_INFWA_AO3(CWK_INFWA_AO_I2S_DMA, "infwa_ao_i2s_dma", "top_axi", 5),
	GATE_INFWA_AO3(CWK_INFWA_AO_AP_MSDC0, "infwa_ao_ap_msdc0", "top_msdc50_0", 7),
	GATE_INFWA_AO3(CWK_INFWA_AO_MD_MSDC0, "infwa_ao_md_msdc0", "top_msdc50_0", 8),
	GATE_INFWA_AO3(CWK_INFWA_AO_CG3_MSDC2, "infwa_ao_cg3_msdc2", "top_msdc30_2", 9),
	GATE_INFWA_AO3(CWK_INFWA_AO_GCPU, "infwa_ao_gcpu", "top_gcpu", 10),
	GATE_INFWA_AO3(CWK_INFWA_AO_PCIE_PEWI_26M, "infwa_ao_pcie_pewi_26m", "cwk26m", 15),
	GATE_INFWA_AO3(CWK_INFWA_AO_GCPU_66M_B, "infwa_ao_gcpu_66m_b", "top_axi", 16),
	GATE_INFWA_AO3(CWK_INFWA_AO_GCPU_133M_B, "infwa_ao_gcpu_133m_b", "top_axi", 17),
	GATE_INFWA_AO3(CWK_INFWA_AO_DISP_PWM1, "infwa_ao_disp_pwm1", "top_disp_pwm1", 20),
	GATE_INFWA_AO3(CWK_INFWA_AO_FBIST2FPC, "infwa_ao_fbist2fpc", "top_msdc50_0", 24),
	/* infwa_ao_device_apc_sync is fow device access pewmission contwow moduwe */
	GATE_INFWA_AO3_FWAGS(CWK_INFWA_AO_DEVICE_APC_SYNC, "infwa_ao_device_apc_sync", "top_axi", 25,
			     CWK_IS_CWITICAW),
	GATE_INFWA_AO3(CWK_INFWA_AO_PCIE_P1_PEWI_26M, "infwa_ao_pcie_p1_pewi_26m", "cwk26m", 26),
	GATE_INFWA_AO3(CWK_INFWA_AO_SPIS0, "infwa_ao_spis0", "top_spis", 28),
	GATE_INFWA_AO3(CWK_INFWA_AO_SPIS1, "infwa_ao_spis1", "top_spis", 29),
	/* INFWA_AO4 */
	/* infwa_ao_133m_m_pewi infwa_ao_66m_m_pewi awe main cwocks of pewiphewaw */
	GATE_INFWA_AO4_FWAGS(CWK_INFWA_AO_133M_M_PEWI, "infwa_ao_133m_m_pewi", "top_axi", 0,
			     CWK_IS_CWITICAW),
	GATE_INFWA_AO4_FWAGS(CWK_INFWA_AO_66M_M_PEWI, "infwa_ao_66m_m_pewi", "top_axi", 1,
			     CWK_IS_CWITICAW),
	GATE_INFWA_AO4(CWK_INFWA_AO_PCIE_PW_P_250M_P0, "infwa_ao_pcie_pw_p_250m_p0", "pextp_pipe", 7),
	GATE_INFWA_AO4(CWK_INFWA_AO_PCIE_PW_P_250M_P1, "infwa_ao_pcie_pw_p_250m_p1",
		       "ssusb_u3phy_p1_p_p0", 8),
	GATE_INFWA_AO4(CWK_INFWA_AO_PCIE_P1_TW_96M, "infwa_ao_pcie_p1_tw_96m", "top_tw_p1", 17),
	GATE_INFWA_AO4(CWK_INFWA_AO_AES_MSDCFDE_0P, "infwa_ao_aes_msdcfde_0p", "top_aes_msdcfde", 18),
	GATE_INFWA_AO4(CWK_INFWA_AO_UFS_TX_SYMBOW, "infwa_ao_ufs_tx_symbow", "ufs_tx_symbow", 22),
	GATE_INFWA_AO4(CWK_INFWA_AO_UFS_WX_SYMBOW, "infwa_ao_ufs_wx_symbow", "ufs_wx_symbow", 23),
	GATE_INFWA_AO4(CWK_INFWA_AO_UFS_WX_SYMBOW1, "infwa_ao_ufs_wx_symbow1", "ufs_wx_symbow1", 24),
	GATE_INFWA_AO4(CWK_INFWA_AO_PEWI_UFS_MEM_SUB, "infwa_ao_pewi_ufs_mem_sub", "mem_466m", 31),
};

static u16 infwa_ao_wst_ofs[] = {
	INFWA_WST0_SET_OFFSET,
	INFWA_WST1_SET_OFFSET,
	INFWA_WST2_SET_OFFSET,
	INFWA_WST3_SET_OFFSET,
	INFWA_WST4_SET_OFFSET,
};

static u16 infwa_ao_idx_map[] = {
	[MT8195_INFWA_WST0_THEWM_CTWW_SWWST] = 0 * WST_NW_PEW_BANK + 0,
	[MT8195_INFWA_WST2_USBSIF_P1_SWWST] = 2 * WST_NW_PEW_BANK + 18,
	[MT8195_INFWA_WST2_PCIE_P0_SWWST] = 2 * WST_NW_PEW_BANK + 26,
	[MT8195_INFWA_WST2_PCIE_P1_SWWST] = 2 * WST_NW_PEW_BANK + 27,
	[MT8195_INFWA_WST3_THEWM_CTWW_PTP_SWWST] = 3 * WST_NW_PEW_BANK + 5,
	[MT8195_INFWA_WST4_THEWM_CTWW_MCU_SWWST] = 4 * WST_NW_PEW_BANK + 10,
};

static stwuct mtk_cwk_wst_desc infwa_ao_wst_desc = {
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

static const stwuct of_device_id of_match_cwk_mt8195_infwa_ao[] = {
	{
		.compatibwe = "mediatek,mt8195-infwacfg_ao",
		.data = &infwa_ao_desc,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8195_infwa_ao);

static stwuct pwatfowm_dwivew cwk_mt8195_infwa_ao_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt8195-infwa_ao",
		.of_match_tabwe = of_match_cwk_mt8195_infwa_ao,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt8195_infwa_ao_dwv);
MODUWE_WICENSE("GPW");
