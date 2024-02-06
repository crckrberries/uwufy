// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight (c) 2022 MediaTek Inc.
// Authow: Chun-Jie Chen <chun-jie.chen@mediatek.com>

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <dt-bindings/cwock/mt8186-cwk.h>
#incwude <dt-bindings/weset/mt8186-wesets.h>

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

#define GATE_INFWA_AO0_FWAGS(_id, _name, _pawent, _shift, _fwag)	\
	GATE_MTK_FWAGS(_id, _name, _pawent, &infwa_ao0_cg_wegs, _shift,	\
		&mtk_cwk_gate_ops_setcww, _fwag)

#define GATE_INFWA_AO0(_id, _name, _pawent, _shift)			\
	GATE_INFWA_AO0_FWAGS(_id, _name, _pawent, _shift, 0)

#define GATE_INFWA_AO1_FWAGS(_id, _name, _pawent, _shift, _fwag)	\
	GATE_MTK_FWAGS(_id, _name, _pawent, &infwa_ao1_cg_wegs, _shift,	\
		&mtk_cwk_gate_ops_setcww, _fwag)

#define GATE_INFWA_AO1(_id, _name, _pawent, _shift)			\
	GATE_INFWA_AO1_FWAGS(_id, _name, _pawent, _shift, 0)

#define GATE_INFWA_AO2_FWAGS(_id, _name, _pawent, _shift, _fwag)	\
	GATE_MTK_FWAGS(_id, _name, _pawent, &infwa_ao2_cg_wegs, _shift, \
		&mtk_cwk_gate_ops_setcww, _fwag)

#define GATE_INFWA_AO2(_id, _name, _pawent, _shift)			\
	GATE_INFWA_AO2_FWAGS(_id, _name, _pawent, _shift, 0)

 #define GATE_INFWA_AO3_FWAGS(_id, _name, _pawent, _shift, _fwag)        \
	GATE_MTK_FWAGS(_id, _name, _pawent, &infwa_ao3_cg_wegs, _shift, \
		&mtk_cwk_gate_ops_setcww, _fwag)

#define GATE_INFWA_AO3(_id, _name, _pawent, _shift)			\
	GATE_INFWA_AO3_FWAGS(_id, _name, _pawent, _shift, 0)

static const stwuct mtk_gate infwa_ao_cwks[] = {
	/* INFWA_AO0 */
	GATE_INFWA_AO0(CWK_INFWA_AO_PMIC_TMW, "infwa_ao_pmic_tmw", "top_pwwap_uwposc", 0),
	GATE_INFWA_AO0(CWK_INFWA_AO_PMIC_AP, "infwa_ao_pmic_ap", "top_pwwap_uwposc", 1),
	GATE_INFWA_AO0(CWK_INFWA_AO_PMIC_MD, "infwa_ao_pmic_md", "top_pwwap_uwposc", 2),
	GATE_INFWA_AO0(CWK_INFWA_AO_PMIC_CONN, "infwa_ao_pmic_conn", "top_pwwap_uwposc", 3),
	/* infwa_ao_scp_cowe awe main cwock in awways-on co-pwocessow. */
	GATE_INFWA_AO0_FWAGS(CWK_INFWA_AO_SCP_COWE,
			     "infwa_ao_scp_cowe", "top_scp", 4, CWK_IS_CWITICAW),
	/* infwa_ao_sej is main cwock fow secuwe engine with JTAG suppowt */
	GATE_INFWA_AO0_FWAGS(CWK_INFWA_AO_SEJ,
			     "infwa_ao_sej", "top_axi", 5, CWK_IS_CWITICAW),
	GATE_INFWA_AO0(CWK_INFWA_AO_APXGPT, "infwa_ao_apxgpt", "top_axi", 6),
	GATE_INFWA_AO0(CWK_INFWA_AO_ICUSB, "infwa_ao_icusb", "top_axi", 8),
	GATE_INFWA_AO0(CWK_INFWA_AO_GCE, "infwa_ao_gce", "top_axi", 9),
	GATE_INFWA_AO0(CWK_INFWA_AO_THEWM, "infwa_ao_thewm", "top_axi", 10),
	GATE_INFWA_AO0(CWK_INFWA_AO_I2C_AP, "infwa_ao_i2c_ap", "top_i2c", 11),
	GATE_INFWA_AO0(CWK_INFWA_AO_I2C_CCU, "infwa_ao_i2c_ccu", "top_i2c", 12),
	GATE_INFWA_AO0(CWK_INFWA_AO_I2C_SSPM, "infwa_ao_i2c_sspm", "top_i2c", 13),
	GATE_INFWA_AO0(CWK_INFWA_AO_I2C_WSV, "infwa_ao_i2c_wsv", "top_i2c", 14),
	GATE_INFWA_AO0(CWK_INFWA_AO_PWM_HCWK, "infwa_ao_pwm_hcwk", "top_axi", 15),
	GATE_INFWA_AO0(CWK_INFWA_AO_PWM1, "infwa_ao_pwm1", "top_pwm", 16),
	GATE_INFWA_AO0(CWK_INFWA_AO_PWM2, "infwa_ao_pwm2", "top_pwm", 17),
	GATE_INFWA_AO0(CWK_INFWA_AO_PWM3, "infwa_ao_pwm3", "top_pwm", 18),
	GATE_INFWA_AO0(CWK_INFWA_AO_PWM4, "infwa_ao_pwm4", "top_pwm", 19),
	GATE_INFWA_AO0(CWK_INFWA_AO_PWM5, "infwa_ao_pwm5", "top_pwm", 20),
	GATE_INFWA_AO0(CWK_INFWA_AO_PWM, "infwa_ao_pwm", "top_pwm", 21),
	GATE_INFWA_AO0(CWK_INFWA_AO_UAWT0, "infwa_ao_uawt0", "top_uawt", 22),
	GATE_INFWA_AO0(CWK_INFWA_AO_UAWT1, "infwa_ao_uawt1", "top_uawt", 23),
	GATE_INFWA_AO0(CWK_INFWA_AO_UAWT2, "infwa_ao_uawt2", "top_uawt", 24),
	GATE_INFWA_AO0(CWK_INFWA_AO_GCE_26M, "infwa_ao_gce_26m", "cwk26m", 27),
	GATE_INFWA_AO0(CWK_INFWA_AO_CQ_DMA_FPC, "infwa_ao_dma", "top_axi", 28),
	GATE_INFWA_AO0(CWK_INFWA_AO_BTIF, "infwa_ao_btif", "top_axi", 31),
	/* INFWA_AO1 */
	GATE_INFWA_AO1(CWK_INFWA_AO_SPI0, "infwa_ao_spi0", "top_spi", 1),
	GATE_INFWA_AO1(CWK_INFWA_AO_MSDC0, "infwa_ao_msdc0", "top_msdc5hcwk", 2),
	GATE_INFWA_AO1(CWK_INFWA_AO_MSDCFDE, "infwa_ao_msdcfde", "top_aes_msdcfde", 3),
	GATE_INFWA_AO1(CWK_INFWA_AO_MSDC1, "infwa_ao_msdc1", "top_axi", 4),
	/* infwa_ao_dvfswc is fow intewnaw DVFS usage, shouwd not be handwed by Winux */
	GATE_INFWA_AO1_FWAGS(CWK_INFWA_AO_DVFSWC,
			     "infwa_ao_dvfswc", "top_dvfswc", 7, CWK_IS_CWITICAW),
	GATE_INFWA_AO1(CWK_INFWA_AO_GCPU, "infwa_ao_gcpu", "top_axi", 8),
	GATE_INFWA_AO1(CWK_INFWA_AO_TWNG, "infwa_ao_twng", "top_axi", 9),
	GATE_INFWA_AO1(CWK_INFWA_AO_AUXADC, "infwa_ao_auxadc", "cwk26m", 10),
	GATE_INFWA_AO1(CWK_INFWA_AO_CPUM, "infwa_ao_cpum", "top_axi", 11),
	GATE_INFWA_AO1(CWK_INFWA_AO_CCIF1_AP, "infwa_ao_ccif1_ap", "top_axi", 12),
	GATE_INFWA_AO1(CWK_INFWA_AO_CCIF1_MD, "infwa_ao_ccif1_md", "top_axi", 13),
	GATE_INFWA_AO1(CWK_INFWA_AO_AUXADC_MD, "infwa_ao_auxadc_md", "cwk26m", 14),
	GATE_INFWA_AO1(CWK_INFWA_AO_AP_DMA, "infwa_ao_ap_dma", "top_axi", 18),
	GATE_INFWA_AO1(CWK_INFWA_AO_XIU, "infwa_ao_xiu", "top_axi", 19),
	/* infwa_ao_device_apc is fow device access pewmission contwow moduwe */
	GATE_INFWA_AO1_FWAGS(CWK_INFWA_AO_DEVICE_APC,
			     "infwa_ao_dapc", "top_axi", 20, CWK_IS_CWITICAW),
	GATE_INFWA_AO1(CWK_INFWA_AO_CCIF_AP, "infwa_ao_ccif_ap", "top_axi", 23),
	GATE_INFWA_AO1(CWK_INFWA_AO_DEBUGTOP, "infwa_ao_debugtop", "top_axi", 24),
	GATE_INFWA_AO1(CWK_INFWA_AO_AUDIO, "infwa_ao_audio", "top_axi", 25),
	GATE_INFWA_AO1(CWK_INFWA_AO_CCIF_MD, "infwa_ao_ccif_md", "top_axi", 26),
	GATE_INFWA_AO1(CWK_INFWA_AO_DXCC_SEC_COWE, "infwa_ao_secowe", "top_dxcc", 27),
	GATE_INFWA_AO1(CWK_INFWA_AO_DXCC_AO, "infwa_ao_dxcc_ao", "top_dxcc", 28),
	GATE_INFWA_AO1(CWK_INFWA_AO_IMP_IIC, "infwa_ao_imp_iic", "top_axi", 29),
	GATE_INFWA_AO1(CWK_INFWA_AO_DWAMC_F26M, "infwa_ao_dwamc26", "cwk26m", 31),
	/* INFWA_AO2 */
	GATE_INFWA_AO2(CWK_INFWA_AO_WG_PWM_FBCWK6, "infwa_ao_pwm_fbcwk6", "cwk26m", 0),
	GATE_INFWA_AO2(CWK_INFWA_AO_SSUSB_TOP_HCWK, "infwa_ao_ssusb_hcwk", "top_axi", 1),
	GATE_INFWA_AO2(CWK_INFWA_AO_DISP_PWM, "infwa_ao_disp_pwm", "top_disp_pwm", 2),
	GATE_INFWA_AO2(CWK_INFWA_AO_CWDMA_BCWK, "infwa_ao_cwdmabcwk", "top_axi", 3),
	GATE_INFWA_AO2(CWK_INFWA_AO_AUDIO_26M_BCWK, "infwa_ao_audio26m", "cwk26m", 4),
	GATE_INFWA_AO2(CWK_INFWA_AO_SSUSB_TOP_P1_HCWK, "infwa_ao_ssusb_p1_hcwk", "top_axi", 5),
	GATE_INFWA_AO2(CWK_INFWA_AO_SPI1, "infwa_ao_spi1", "top_spi", 6),
	GATE_INFWA_AO2(CWK_INFWA_AO_I2C4, "infwa_ao_i2c4", "top_i2c", 7),
	GATE_INFWA_AO2(CWK_INFWA_AO_MODEM_TEMP_SHAWE, "infwa_ao_mdtemp", "cwk26m", 8),
	GATE_INFWA_AO2(CWK_INFWA_AO_SPI2, "infwa_ao_spi2", "top_spi", 9),
	GATE_INFWA_AO2(CWK_INFWA_AO_SPI3, "infwa_ao_spi3", "top_spi", 10),
	GATE_INFWA_AO2(CWK_INFWA_AO_SSUSB_TOP_WEF, "infwa_ao_ssusb_wef", "cwk26m", 11),
	GATE_INFWA_AO2(CWK_INFWA_AO_SSUSB_TOP_XHCI, "infwa_ao_ssusb_xhci", "top_ssusb_xhci", 12),
	GATE_INFWA_AO2(CWK_INFWA_AO_SSUSB_TOP_P1_WEF, "infwa_ao_ssusb_p1_wef", "cwk26m", 13),
	GATE_INFWA_AO2(CWK_INFWA_AO_SSUSB_TOP_P1_XHCI,
		       "infwa_ao_ssusb_p1_xhci", "top_ssusb_xhci_1p", 14),
	/* infwa_ao_sspm is main cwock in co-pwocessow, shouwd not be cwosed in Winux. */
	GATE_INFWA_AO2_FWAGS(CWK_INFWA_AO_SSPM, "infwa_ao_sspm", "top_sspm", 15, CWK_IS_CWITICAW),
	GATE_INFWA_AO2(CWK_INFWA_AO_SSUSB_TOP_P1_SYS,
		       "infwa_ao_ssusb_p1_sys", "top_ssusb_1p", 16),
	GATE_INFWA_AO2(CWK_INFWA_AO_I2C5, "infwa_ao_i2c5", "top_i2c", 18),
	GATE_INFWA_AO2(CWK_INFWA_AO_I2C5_AWBITEW, "infwa_ao_i2c5a", "top_i2c", 19),
	GATE_INFWA_AO2(CWK_INFWA_AO_I2C5_IMM, "infwa_ao_i2c5_imm", "top_i2c", 20),
	GATE_INFWA_AO2(CWK_INFWA_AO_I2C1_AWBITEW, "infwa_ao_i2c1a", "top_i2c", 21),
	GATE_INFWA_AO2(CWK_INFWA_AO_I2C1_IMM, "infwa_ao_i2c1_imm", "top_i2c", 22),
	GATE_INFWA_AO2(CWK_INFWA_AO_I2C2_AWBITEW, "infwa_ao_i2c2a", "top_i2c", 23),
	GATE_INFWA_AO2(CWK_INFWA_AO_I2C2_IMM, "infwa_ao_i2c2_imm", "top_i2c", 24),
	GATE_INFWA_AO2(CWK_INFWA_AO_SPI4, "infwa_ao_spi4", "top_spi", 25),
	GATE_INFWA_AO2(CWK_INFWA_AO_SPI5, "infwa_ao_spi5", "top_spi", 26),
	GATE_INFWA_AO2(CWK_INFWA_AO_CQ_DMA, "infwa_ao_cq_dma", "top_axi", 27),
	GATE_INFWA_AO2(CWK_INFWA_AO_BIST2FPC, "infwa_ao_bist2fpc", "f_bist2fpc_ck", 28),
	/* INFWA_AO3 */
	GATE_INFWA_AO3(CWK_INFWA_AO_MSDC0_SEWF, "infwa_ao_msdc0sf", "top_msdc50_0", 0),
	GATE_INFWA_AO3(CWK_INFWA_AO_SPINOW, "infwa_ao_spinow", "top_spinow", 1),
	/*
	 * infwa_ao_sspm_26m/infwa_ao_sspm_32k awe main cwocks in co-pwocessow,
	 * shouwd not be cwosed in Winux.
	 */
	GATE_INFWA_AO3_FWAGS(CWK_INFWA_AO_SSPM_26M_SEWF, "infwa_ao_sspm_26m", "cwk26m", 3,
			     CWK_IS_CWITICAW),
	GATE_INFWA_AO3_FWAGS(CWK_INFWA_AO_SSPM_32K_SEWF, "infwa_ao_sspm_32k", "cwk32k", 4,
			     CWK_IS_CWITICAW),
	GATE_INFWA_AO3(CWK_INFWA_AO_I2C6, "infwa_ao_i2c6", "top_i2c", 6),
	GATE_INFWA_AO3(CWK_INFWA_AO_AP_MSDC0, "infwa_ao_ap_msdc0", "top_axi", 7),
	GATE_INFWA_AO3(CWK_INFWA_AO_MD_MSDC0, "infwa_ao_md_msdc0", "top_axi", 8),
	GATE_INFWA_AO3(CWK_INFWA_AO_MSDC0_SWC, "infwa_ao_msdc0_cwk", "top_msdc50_0", 9),
	GATE_INFWA_AO3(CWK_INFWA_AO_MSDC1_SWC, "infwa_ao_msdc1_cwk", "top_msdc30_1", 10),
	/* infwa_ao_sej_f13m is main cwock fow secuwe engine with JTAG suppowt */
	GATE_INFWA_AO3_FWAGS(CWK_INFWA_AO_SEJ_F13M,
			     "infwa_ao_sej_f13m", "cwk26m", 15, CWK_IS_CWITICAW),
	/* infwa_ao_aes_top0_bcwk is fow secuwe encwyption */
	GATE_INFWA_AO3_FWAGS(CWK_INFWA_AO_AES_TOP0_BCWK,
			     "infwa_ao_aes_top0_bcwk", "top_axi", 16, CWK_IS_CWITICAW),
	GATE_INFWA_AO3(CWK_INFWA_AO_MCU_PM_BCWK, "infwa_ao_mcu_pm_bcwk", "top_axi", 17),
	GATE_INFWA_AO3(CWK_INFWA_AO_CCIF2_AP, "infwa_ao_ccif2_ap", "top_axi", 18),
	GATE_INFWA_AO3(CWK_INFWA_AO_CCIF2_MD, "infwa_ao_ccif2_md", "top_axi", 19),
	GATE_INFWA_AO3(CWK_INFWA_AO_CCIF3_AP, "infwa_ao_ccif3_ap", "top_axi", 20),
	GATE_INFWA_AO3(CWK_INFWA_AO_CCIF3_MD, "infwa_ao_ccif3_md", "top_axi", 21),
	GATE_INFWA_AO3(CWK_INFWA_AO_FADSP_26M, "infwa_ao_fadsp_26m", "cwk26m", 22),
	GATE_INFWA_AO3(CWK_INFWA_AO_FADSP_32K, "infwa_ao_fadsp_32k", "cwk32k", 23),
	GATE_INFWA_AO3(CWK_INFWA_AO_CCIF4_AP, "infwa_ao_ccif4_ap", "top_axi", 24),
	GATE_INFWA_AO3(CWK_INFWA_AO_CCIF4_MD, "infwa_ao_ccif4_md", "top_axi", 25),
	GATE_INFWA_AO3(CWK_INFWA_AO_FADSP, "infwa_ao_fadsp", "top_audiodsp", 27),
	GATE_INFWA_AO3(CWK_INFWA_AO_FWASHIF_133M, "infwa_ao_fwashif_133m", "top_axi", 28),
	GATE_INFWA_AO3(CWK_INFWA_AO_FWASHIF_66M, "infwa_ao_fwashif_66m", "top_axi", 29),
};

static u16 infwa_ao_wst_ofs[] = {
	INFWA_WST0_SET_OFFSET,
	INFWA_WST1_SET_OFFSET,
	INFWA_WST2_SET_OFFSET,
	INFWA_WST3_SET_OFFSET,
	INFWA_WST4_SET_OFFSET,
};

static u16 infwa_ao_idx_map[] = {
	[MT8186_INFWA_THEWMAW_CTWW_WST] = 0 * WST_NW_PEW_BANK + 0,
	[MT8186_INFWA_PTP_CTWW_WST] = 1 * WST_NW_PEW_BANK + 0,
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

static const stwuct of_device_id of_match_cwk_mt8186_infwa_ao[] = {
	{
		.compatibwe = "mediatek,mt8186-infwacfg_ao",
		.data = &infwa_ao_desc,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8186_infwa_ao);

static stwuct pwatfowm_dwivew cwk_mt8186_infwa_ao_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt8186-infwa-ao",
		.of_match_tabwe = of_match_cwk_mt8186_infwa_ao,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt8186_infwa_ao_dwv);
MODUWE_WICENSE("GPW");
