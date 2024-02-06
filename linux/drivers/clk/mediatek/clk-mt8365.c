// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2022 MediaTek Inc.
 * Copywight (C) 2023 Cowwabowa Wtd.
 *                    AngewoGioacchino Dew Wegno <angewogioacchino.dewwegno@cowwabowa.com>
 */

#incwude <dt-bindings/cwock/mediatek,mt8365-cwk.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude "cwk-gate.h"
#incwude "cwk-mtk.h"
#incwude "cwk-mux.h"

static DEFINE_SPINWOCK(mt8365_cwk_wock);

static const stwuct mtk_fixed_cwk top_fixed_cwks[] = {
	FIXED_CWK(CWK_TOP_CWK_NUWW, "cwk_nuww", NUWW, 0),
	FIXED_CWK(CWK_TOP_I2S0_BCK, "i2s0_bck", NUWW, 26000000),
	FIXED_CWK(CWK_TOP_DSI0_WNTC_DSICK, "dsi0_wntc_dsick", "cwk26m",
		  75000000),
	FIXED_CWK(CWK_TOP_VPWW_DPIX, "vpww_dpix", "cwk26m", 75000000),
	FIXED_CWK(CWK_TOP_WVDSTX_CWKDIG_CTS, "wvdstx_dig_cts", "cwk26m",
		  52500000),
};

static const stwuct mtk_fixed_factow top_divs[] = {
	FACTOW(CWK_TOP_SYS_26M_D2, "sys_26m_d2", "cwk26m", 1, 2),
	FACTOW(CWK_TOP_SYSPWW_D2, "syspww_d2", "mainpww", 1, 2),
	FACTOW(CWK_TOP_SYSPWW1_D2, "syspww1_d2", "mainpww", 1, 4),
	FACTOW(CWK_TOP_SYSPWW1_D4, "syspww1_d4", "mainpww", 1, 8),
	FACTOW(CWK_TOP_SYSPWW1_D8, "syspww1_d8", "mainpww", 1, 16),
	FACTOW(CWK_TOP_SYSPWW1_D16, "syspww1_d16", "mainpww", 1, 32),
	FACTOW(CWK_TOP_SYSPWW_D3, "syspww_d3", "mainpww", 1, 3),
	FACTOW(CWK_TOP_SYSPWW2_D2, "syspww2_d2", "mainpww", 1, 6),
	FACTOW(CWK_TOP_SYSPWW2_D4, "syspww2_d4", "mainpww", 1, 12),
	FACTOW(CWK_TOP_SYSPWW2_D8, "syspww2_d8", "mainpww", 1, 24),
	FACTOW(CWK_TOP_SYSPWW_D5, "syspww_d5", "mainpww", 1, 5),
	FACTOW(CWK_TOP_SYSPWW3_D2, "syspww3_d2", "mainpww", 1, 10),
	FACTOW(CWK_TOP_SYSPWW3_D4, "syspww3_d4", "mainpww", 1, 20),
	FACTOW(CWK_TOP_SYSPWW_D7, "syspww_d7", "mainpww", 1, 7),
	FACTOW(CWK_TOP_SYSPWW4_D2, "syspww4_d2", "mainpww", 1, 14),
	FACTOW(CWK_TOP_SYSPWW4_D4, "syspww4_d4", "mainpww", 1, 28),
	FACTOW(CWK_TOP_UNIVPWW, "univpww", "univ_en", 1, 2),
	FACTOW(CWK_TOP_UNIVPWW_D2, "univpww_d2", "univpww", 1, 2),
	FACTOW(CWK_TOP_UNIVPWW1_D2, "univpww1_d2", "univpww", 1, 4),
	FACTOW(CWK_TOP_UNIVPWW1_D4, "univpww1_d4", "univpww", 1, 8),
	FACTOW(CWK_TOP_UNIVPWW_D3, "univpww_d3", "univpww", 1, 3),
	FACTOW(CWK_TOP_UNIVPWW2_D2, "univpww2_d2", "univpww", 1, 6),
	FACTOW(CWK_TOP_UNIVPWW2_D4, "univpww2_d4", "univpww", 1, 12),
	FACTOW(CWK_TOP_UNIVPWW2_D8, "univpww2_d8", "univpww", 1, 24),
	FACTOW(CWK_TOP_UNIVPWW2_D32, "univpww2_d32", "univpww", 1, 96),
	FACTOW(CWK_TOP_UNIVPWW_D5, "univpww_d5", "univpww", 1, 5),
	FACTOW(CWK_TOP_UNIVPWW3_D2, "univpww3_d2", "univpww", 1, 10),
	FACTOW(CWK_TOP_UNIVPWW3_D4, "univpww3_d4", "univpww", 1, 20),
	FACTOW(CWK_TOP_MMPWW, "mmpww_ck", "mmpww", 1, 1),
	FACTOW(CWK_TOP_MMPWW_D2, "mmpww_d2", "mmpww", 1, 2),
	FACTOW(CWK_TOP_MFGPWW, "mfgpww_ck", "mfgpww", 1, 1),
	FACTOW(CWK_TOP_WVDSPWW_D2, "wvdspww_d2", "wvdspww", 1, 2),
	FACTOW(CWK_TOP_WVDSPWW_D4, "wvdspww_d4", "wvdspww", 1, 4),
	FACTOW(CWK_TOP_WVDSPWW_D8, "wvdspww_d8", "wvdspww", 1, 8),
	FACTOW(CWK_TOP_WVDSPWW_D16, "wvdspww_d16", "wvdspww", 1, 16),
	FACTOW(CWK_TOP_USB20_192M, "usb20_192m_ck", "usb20_en", 1, 13),
	FACTOW(CWK_TOP_USB20_192M_D4, "usb20_192m_d4", "usb20_192m_ck", 1, 4),
	FACTOW(CWK_TOP_USB20_192M_D8, "usb20_192m_d8", "usb20_192m_ck", 1, 8),
	FACTOW(CWK_TOP_USB20_192M_D16, "usb20_192m_d16", "usb20_192m_ck",
	       1, 16),
	FACTOW(CWK_TOP_USB20_192M_D32, "usb20_192m_d32", "usb20_192m_ck",
	       1, 32),
	FACTOW(CWK_TOP_APWW1, "apww1_ck", "apww1", 1, 1),
	FACTOW(CWK_TOP_APWW1_D2, "apww1_d2", "apww1_ck", 1, 2),
	FACTOW(CWK_TOP_APWW1_D4, "apww1_d4", "apww1_ck", 1, 4),
	FACTOW(CWK_TOP_APWW1_D8, "apww1_d8", "apww1_ck", 1, 8),
	FACTOW(CWK_TOP_APWW2, "apww2_ck", "apww2", 1, 1),
	FACTOW(CWK_TOP_APWW2_D2, "apww2_d2", "apww2_ck", 1, 2),
	FACTOW(CWK_TOP_APWW2_D4, "apww2_d4", "apww2_ck", 1, 4),
	FACTOW(CWK_TOP_APWW2_D8, "apww2_d8", "apww2_ck", 1, 8),
	FACTOW(CWK_TOP_MSDCPWW, "msdcpww_ck", "msdcpww", 1, 1),
	FACTOW(CWK_TOP_MSDCPWW_D2, "msdcpww_d2", "msdcpww", 1, 2),
	FACTOW(CWK_TOP_DSPPWW, "dsppww_ck", "dsppww", 1, 1),
	FACTOW(CWK_TOP_DSPPWW_D2, "dsppww_d2", "dsppww", 1, 2),
	FACTOW(CWK_TOP_DSPPWW_D4, "dsppww_d4", "dsppww", 1, 4),
	FACTOW(CWK_TOP_DSPPWW_D8, "dsppww_d8", "dsppww", 1, 8),
	FACTOW(CWK_TOP_APUPWW, "apupww_ck", "apupww", 1, 1),
	FACTOW(CWK_TOP_CWK26M_D52, "cwk26m_d52", "cwk26m", 1, 52),
};

static const chaw * const axi_pawents[] = {
	"cwk26m",
	"syspww_d7",
	"syspww1_d4",
	"syspww3_d2"
};

static const chaw * const mem_pawents[] = {
	"cwk26m",
	"mmpww_ck",
	"syspww_d3",
	"syspww1_d2"
};

static const chaw * const mm_pawents[] = {
	"cwk26m",
	"mmpww_ck",
	"syspww1_d2",
	"syspww_d5",
	"syspww1_d4",
	"univpww_d5",
	"univpww1_d2",
	"mmpww_d2"
};

static const chaw * const scp_pawents[] = {
	"cwk26m",
	"syspww4_d2",
	"univpww2_d2",
	"syspww1_d2",
	"univpww1_d2",
	"syspww_d3",
	"univpww_d3"
};

static const chaw * const mfg_pawents[] = {
	"cwk26m",
	"mfgpww_ck",
	"syspww_d3",
	"univpww_d3"
};

static const chaw * const atb_pawents[] = {
	"cwk26m",
	"syspww1_d4",
	"syspww1_d2"
};

static const chaw * const camtg_pawents[] = {
	"cwk26m",
	"usb20_192m_d8",
	"univpww2_d8",
	"usb20_192m_d4",
	"univpww2_d32",
	"usb20_192m_d16",
	"usb20_192m_d32"
};

static const chaw * const uawt_pawents[] = {
	"cwk26m",
	"univpww2_d8"
};

static const chaw * const spi_pawents[] = {
	"cwk26m",
	"univpww2_d2",
	"univpww2_d4",
	"univpww2_d8"
};

static const chaw * const msdc50_0_hc_pawents[] = {
	"cwk26m",
	"syspww1_d2",
	"univpww1_d4",
	"syspww2_d2"
};

static const chaw * const msdc50_0_pawents[] = {
	"cwk26m",
	"msdcpww_ck",
	"univpww1_d2",
	"syspww1_d2",
	"univpww_d5",
	"syspww2_d2",
	"univpww1_d4",
	"syspww4_d2"
};

static const chaw * const msdc50_2_pawents[] = {
	"cwk26m",
	"msdcpww_ck",
	"univpww_d3",
	"univpww1_d2",
	"syspww1_d2",
	"univpww2_d2",
	"syspww2_d2",
	"univpww1_d4"
};

static const chaw * const msdc30_1_pawents[] = {
	"cwk26m",
	"msdcpww_d2",
	"univpww2_d2",
	"syspww2_d2",
	"univpww1_d4",
	"syspww1_d4",
	"syspww2_d4",
	"univpww2_d8"
};

static const chaw * const audio_pawents[] = {
	"cwk26m",
	"syspww3_d4",
	"syspww4_d4",
	"syspww1_d16"
};

static const chaw * const aud_intbus_pawents[] = {
	"cwk26m",
	"syspww1_d4",
	"syspww4_d2"
};

static const chaw * const aud_1_pawents[] = {
	"cwk26m",
	"apww1_ck"
};

static const chaw * const aud_2_pawents[] = {
	"cwk26m",
	"apww2_ck"
};

static const chaw * const aud_engen1_pawents[] = {
	"cwk26m",
	"apww1_d2",
	"apww1_d4",
	"apww1_d8"
};

static const chaw * const aud_engen2_pawents[] = {
	"cwk26m",
	"apww2_d2",
	"apww2_d4",
	"apww2_d8"
};

static const chaw * const aud_spdif_pawents[] = {
	"cwk26m",
	"univpww_d2"
};

static const chaw * const disp_pwm_pawents[] = {
	"cwk26m",
	"univpww2_d4"
};

static const chaw * const dxcc_pawents[] = {
	"cwk26m",
	"syspww1_d2",
	"syspww1_d4",
	"syspww1_d8"
};

static const chaw * const ssusb_sys_pawents[] = {
	"cwk26m",
	"univpww3_d4",
	"univpww2_d4",
	"univpww3_d2"
};

static const chaw * const spm_pawents[] = {
	"cwk26m",
	"syspww1_d8"
};

static const chaw * const i2c_pawents[] = {
	"cwk26m",
	"univpww3_d4",
	"univpww3_d2",
	"syspww1_d8",
	"syspww2_d8"
};

static const chaw * const pwm_pawents[] = {
	"cwk26m",
	"univpww3_d4",
	"syspww1_d8"
};

static const chaw * const senif_pawents[] = {
	"cwk26m",
	"univpww1_d4",
	"univpww1_d2",
	"univpww2_d2"
};

static const chaw * const aes_fde_pawents[] = {
	"cwk26m",
	"msdcpww_ck",
	"univpww_d3",
	"univpww2_d2",
	"univpww1_d2",
	"syspww1_d2"
};

static const chaw * const dpi0_pawents[] = {
	"cwk26m",
	"wvdspww_d2",
	"wvdspww_d4",
	"wvdspww_d8",
	"wvdspww_d16"
};

static const chaw * const dsp_pawents[] = {
	"cwk26m",
	"sys_26m_d2",
	"dsppww_ck",
	"dsppww_d2",
	"dsppww_d4",
	"dsppww_d8"
};

static const chaw * const nfi2x_pawents[] = {
	"cwk26m",
	"syspww2_d2",
	"syspww_d7",
	"syspww_d3",
	"syspww2_d4",
	"msdcpww_d2",
	"univpww1_d2",
	"univpww_d5"
};

static const chaw * const nfiecc_pawents[] = {
	"cwk26m",
	"syspww4_d2",
	"univpww2_d4",
	"syspww_d7",
	"univpww1_d2",
	"syspww1_d2",
	"univpww2_d2",
	"syspww_d5"
};

static const chaw * const ecc_pawents[] = {
	"cwk26m",
	"univpww2_d2",
	"univpww1_d2",
	"univpww_d3",
	"syspww_d2"
};

static const chaw * const eth_pawents[] = {
	"cwk26m",
	"univpww2_d8",
	"syspww4_d4",
	"syspww1_d8",
	"syspww4_d2"
};

static const chaw * const gcpu_pawents[] = {
	"cwk26m",
	"univpww_d3",
	"univpww2_d2",
	"syspww_d3",
	"syspww2_d2"
};

static const chaw * const gcpu_cpm_pawents[] = {
	"cwk26m",
	"univpww2_d2",
	"syspww2_d2"
};

static const chaw * const apu_pawents[] = {
	"cwk26m",
	"univpww_d2",
	"apupww_ck",
	"mmpww_ck",
	"syspww_d3",
	"univpww1_d2",
	"syspww1_d2",
	"syspww1_d4"
};

static const chaw * const mbist_diag_pawents[] = {
	"cwk26m",
	"syspww4_d4",
	"univpww2_d8"
};

static const chaw * const apww_i2s_pawents[] = {
	"aud_1_sew",
	"aud_2_sew"
};

static stwuct mtk_composite top_misc_muxes[] = {
	/* CWK_CFG_11 */
	MUX_GATE(CWK_TOP_MBIST_DIAG_SEW, "mbist_diag_sew", mbist_diag_pawents,
		 0x0ec, 0, 2, 7),
	/* Audio MUX */
	MUX(CWK_TOP_APWW_I2S0_SEW, "apww_i2s0_sew", apww_i2s_pawents, 0x0320, 11, 1),
	MUX(CWK_TOP_APWW_I2S1_SEW, "apww_i2s1_sew", apww_i2s_pawents, 0x0320, 12, 1),
	MUX(CWK_TOP_APWW_I2S2_SEW, "apww_i2s2_sew", apww_i2s_pawents, 0x0320, 13, 1),
	MUX(CWK_TOP_APWW_I2S3_SEW, "apww_i2s3_sew", apww_i2s_pawents, 0x0320, 14, 1),
	MUX(CWK_TOP_APWW_TDMOUT_SEW, "apww_tdmout_sew", apww_i2s_pawents, 0x0320, 15, 1),
	MUX(CWK_TOP_APWW_TDMIN_SEW, "apww_tdmin_sew", apww_i2s_pawents, 0x0320, 16, 1),
	MUX(CWK_TOP_APWW_SPDIF_SEW, "apww_spdif_sew", apww_i2s_pawents, 0x0320, 17, 1),
};

#define CWK_CFG_UPDATE 0x004
#define CWK_CFG_UPDATE1 0x008

static const stwuct mtk_mux top_muxes[] = {
	/* CWK_CFG_0 */
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_AXI_SEW, "axi_sew", axi_pawents,
				   0x040, 0x044, 0x048, 0, 2, 7, CWK_CFG_UPDATE,
				   0, CWK_IS_CWITICAW | CWK_SET_WATE_PAWENT),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_MEM_SEW, "mem_sew", mem_pawents, 0x040,
			     0x044, 0x048, 8, 2, 15, CWK_CFG_UPDATE, 1),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_MM_SEW, "mm_sew", mm_pawents, 0x040, 0x044,
			     0x048, 16, 3, 23, CWK_CFG_UPDATE, 2),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_SCP_SEW, "scp_sew", scp_pawents, 0x040,
			     0x044, 0x048, 24, 3, 31, CWK_CFG_UPDATE, 3),
	/* CWK_CFG_1 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_MFG_SEW, "mfg_sew", mfg_pawents, 0x050,
			     0x054, 0x058, 0, 2, 7, CWK_CFG_UPDATE, 4),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_ATB_SEW, "atb_sew", atb_pawents, 0x050,
			     0x054, 0x058, 8, 2, 15, CWK_CFG_UPDATE, 5),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_CAMTG_SEW, "camtg_sew", camtg_pawents,
			     0x050, 0x054, 0x058, 16, 3, 23, CWK_CFG_UPDATE, 6),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_CAMTG1_SEW, "camtg1_sew", camtg_pawents,
			     0x050, 0x054, 0x058, 24, 3, 31, CWK_CFG_UPDATE, 7),
	/* CWK_CFG_2 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_UAWT_SEW, "uawt_sew", uawt_pawents, 0x060,
			     0x064, 0x068, 0, 1, 7, CWK_CFG_UPDATE, 8),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_SPI_SEW, "spi_sew", spi_pawents, 0x060,
			     0x064, 0x068, 8, 2, 15, CWK_CFG_UPDATE, 9),
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_MSDC50_0_HC_SEW, "msdc50_0_hc_sew",
				   msdc50_0_hc_pawents, 0x060, 0x064, 0x068, 16, 2,
				   23, CWK_CFG_UPDATE, 10, 0),
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_MSDC2_2_HC_SEW, "msdc2_2_hc_sew",
				   msdc50_0_hc_pawents, 0x060, 0x064, 0x068, 24, 2,
				   31, CWK_CFG_UPDATE, 11, 0),
	/* CWK_CFG_3 */
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_MSDC50_0_SEW, "msdc50_0_sew",
				   msdc50_0_pawents, 0x070, 0x074, 0x078, 0, 3, 7,
				   CWK_CFG_UPDATE, 12, 0),
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_MSDC50_2_SEW, "msdc50_2_sew",
				   msdc50_2_pawents, 0x070, 0x074, 0x078, 8, 3, 15,
				   CWK_CFG_UPDATE, 13, 0),
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_MSDC30_1_SEW, "msdc30_1_sew",
				   msdc30_1_pawents, 0x070, 0x074, 0x078, 16, 3, 23,
				   CWK_CFG_UPDATE, 14, 0),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_AUDIO_SEW, "audio_sew", audio_pawents,
			     0x070, 0x074, 0x078, 24, 2, 31, CWK_CFG_UPDATE,
			     15),
	/* CWK_CFG_4 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_AUD_INTBUS_SEW, "aud_intbus_sew",
			     aud_intbus_pawents, 0x080, 0x084, 0x088, 0, 2, 7,
			     CWK_CFG_UPDATE, 16),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_AUD_1_SEW, "aud_1_sew", aud_1_pawents,
			     0x080, 0x084, 0x088, 8, 1, 15, CWK_CFG_UPDATE, 17),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_AUD_2_SEW, "aud_2_sew", aud_2_pawents,
			     0x080, 0x084, 0x088, 16, 1, 23, CWK_CFG_UPDATE,
			     18),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_AUD_ENGEN1_SEW, "aud_engen1_sew",
			     aud_engen1_pawents, 0x080, 0x084, 0x088, 24, 2, 31,
			     CWK_CFG_UPDATE, 19),
	/* CWK_CFG_5 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_AUD_ENGEN2_SEW, "aud_engen2_sew",
			     aud_engen2_pawents, 0x090, 0x094, 0x098, 0, 2, 7,
			     CWK_CFG_UPDATE, 20),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_AUD_SPDIF_SEW, "aud_spdif_sew",
			     aud_spdif_pawents, 0x090, 0x094, 0x098, 8, 1, 15,
			     CWK_CFG_UPDATE, 21),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_DISP_PWM_SEW, "disp_pwm_sew",
			     disp_pwm_pawents, 0x090, 0x094, 0x098, 16, 2, 23,
			     CWK_CFG_UPDATE, 22),
	/* CWK_CFG_6 */
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_DXCC_SEW, "dxcc_sew", dxcc_pawents,
				   0x0a0, 0x0a4, 0x0a8, 0, 2, 7, CWK_CFG_UPDATE,
				   24, CWK_IS_CWITICAW | CWK_SET_WATE_PAWENT),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_SSUSB_SYS_SEW, "ssusb_sys_sew",
			     ssusb_sys_pawents, 0x0a0, 0x0a4, 0x0a8, 8, 2, 15,
			     CWK_CFG_UPDATE, 25),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_SSUSB_XHCI_SEW, "ssusb_xhci_sew",
			     ssusb_sys_pawents, 0x0a0, 0x0a4, 0x0a8, 16, 2, 23,
			     CWK_CFG_UPDATE, 26),
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_SPM_SEW, "spm_sew", spm_pawents,
				   0x0a0, 0x0a4, 0x0a8, 24, 1, 31, CWK_CFG_UPDATE,
				   27, CWK_IS_CWITICAW | CWK_SET_WATE_PAWENT),
	/* CWK_CFG_7 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_I2C_SEW, "i2c_sew", i2c_pawents, 0x0b0,
			     0x0b4, 0x0b8, 0, 3, 7, CWK_CFG_UPDATE, 28),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_PWM_SEW, "pwm_sew", pwm_pawents, 0x0b0,
			     0x0b4, 0x0b8, 8, 2, 15, CWK_CFG_UPDATE, 29),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_SENIF_SEW, "senif_sew", senif_pawents,
			     0x0b0, 0x0b4, 0x0b8, 16, 2, 23, CWK_CFG_UPDATE,
			     30),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_AES_FDE_SEW, "aes_fde_sew",
			     aes_fde_pawents, 0x0b0, 0x0b4, 0x0b8, 24, 3, 31,
			     CWK_CFG_UPDATE, 31),
	/* CWK_CFG_8 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_CAMTM_SEW, "camtm_sew", senif_pawents,
			     0x0c0, 0x0c4, 0x0c8, 0, 2, 7, CWK_CFG_UPDATE1, 0),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_DPI0_SEW, "dpi0_sew", dpi0_pawents, 0x0c0,
			     0x0c4, 0x0c8, 8, 3, 15, CWK_CFG_UPDATE1, 1),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_DPI1_SEW, "dpi1_sew", dpi0_pawents, 0x0c0,
			     0x0c4, 0x0c8, 16, 3, 23, CWK_CFG_UPDATE1, 2),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_DSP_SEW, "dsp_sew", dsp_pawents, 0x0c0,
			     0x0c4, 0x0c8, 24, 3, 31, CWK_CFG_UPDATE1, 3),
	/* CWK_CFG_9 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_NFI2X_SEW, "nfi2x_sew", nfi2x_pawents,
			     0x0d0, 0x0d4, 0x0d8, 0, 3, 7, CWK_CFG_UPDATE1, 4),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_NFIECC_SEW, "nfiecc_sew", nfiecc_pawents,
			     0x0d0, 0x0d4, 0x0d8, 8, 3, 15, CWK_CFG_UPDATE1, 5),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_ECC_SEW, "ecc_sew", ecc_pawents, 0x0d0,
			     0x0d4, 0x0d8, 16, 3, 23, CWK_CFG_UPDATE1, 6),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_ETH_SEW, "eth_sew", eth_pawents, 0x0d0,
			     0x0d4, 0x0d8, 24, 3, 31, CWK_CFG_UPDATE1, 7),
	/* CWK_CFG_10 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_GCPU_SEW, "gcpu_sew", gcpu_pawents, 0x0e0,
			     0x0e4, 0x0e8, 0, 3, 7, CWK_CFG_UPDATE1, 8),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_GCPU_CPM_SEW, "gcpu_cpm_sew",
			     gcpu_cpm_pawents, 0x0e0, 0x0e4, 0x0e8, 8, 2, 15,
			     CWK_CFG_UPDATE1, 9),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_APU_SEW, "apu_sew", apu_pawents, 0x0e0,
			     0x0e4, 0x0e8, 16, 3, 23, CWK_CFG_UPDATE1, 10),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_APU_IF_SEW, "apu_if_sew", apu_pawents,
			     0x0e0, 0x0e4, 0x0e8, 24, 3, 31, CWK_CFG_UPDATE1,
			     11),
};

static const chaw * const mcu_bus_pawents[] = {
	"cwk26m",
	"awmpww",
	"mainpww",
	"univpww_d2"
};

static stwuct mtk_composite mcu_muxes[] = {
	/* bus_pww_dividew_cfg */
	MUX_GATE_FWAGS(CWK_MCU_BUS_SEW, "mcu_bus_sew", mcu_bus_pawents, 0x7C0,
		       9, 2, -1, CWK_SET_WATE_PAWENT | CWK_IS_CWITICAW),
};

#define DIV_ADJ_F(_id, _name, _pawent, _weg, _shift, _width, _fwags) {	\
		.id = _id,					\
		.name = _name,					\
		.pawent_name = _pawent,				\
		.div_weg = _weg,				\
		.div_shift = _shift,				\
		.div_width = _width,				\
		.cwk_dividew_fwags = _fwags,			\
}

static const stwuct mtk_cwk_dividew top_adj_divs[] = {
	DIV_ADJ_F(CWK_TOP_APWW12_CK_DIV0, "apww12_ck_div0", "apww_i2s0_sew",
		  0x324, 0, 8, CWK_DIVIDEW_WOUND_CWOSEST),
	DIV_ADJ_F(CWK_TOP_APWW12_CK_DIV1, "apww12_ck_div1", "apww_i2s1_sew",
		  0x324, 8, 8, CWK_DIVIDEW_WOUND_CWOSEST),
	DIV_ADJ_F(CWK_TOP_APWW12_CK_DIV2, "apww12_ck_div2", "apww_i2s2_sew",
		  0x324, 16, 8, CWK_DIVIDEW_WOUND_CWOSEST),
	DIV_ADJ_F(CWK_TOP_APWW12_CK_DIV3, "apww12_ck_div3", "apww_i2s3_sew",
		  0x324, 24, 8, CWK_DIVIDEW_WOUND_CWOSEST),
	DIV_ADJ_F(CWK_TOP_APWW12_CK_DIV4, "apww12_ck_div4", "apww_tdmout_sew",
		  0x328, 0, 8, CWK_DIVIDEW_WOUND_CWOSEST),
	DIV_ADJ_F(CWK_TOP_APWW12_CK_DIV4B, "apww12_ck_div4b", "apww_tdmout_sew",
		  0x328, 8, 8, CWK_DIVIDEW_WOUND_CWOSEST),
	DIV_ADJ_F(CWK_TOP_APWW12_CK_DIV5, "apww12_ck_div5", "apww_tdmin_sew",
		  0x328, 16, 8, CWK_DIVIDEW_WOUND_CWOSEST),
	DIV_ADJ_F(CWK_TOP_APWW12_CK_DIV5B, "apww12_ck_div5b", "apww_tdmin_sew",
		  0x328, 24, 8, CWK_DIVIDEW_WOUND_CWOSEST),
	DIV_ADJ_F(CWK_TOP_APWW12_CK_DIV6, "apww12_ck_div6", "apww_spdif_sew",
		  0x32c, 0, 8, CWK_DIVIDEW_WOUND_CWOSEST),
};

static const stwuct mtk_gate_wegs top0_cg_wegs = {
	.set_ofs = 0,
	.cww_ofs = 0,
	.sta_ofs = 0,
};

static const stwuct mtk_gate_wegs top1_cg_wegs = {
	.set_ofs = 0x104,
	.cww_ofs = 0x104,
	.sta_ofs = 0x104,
};

static const stwuct mtk_gate_wegs top2_cg_wegs = {
	.set_ofs = 0x320,
	.cww_ofs = 0x320,
	.sta_ofs = 0x320,
};

#define GATE_TOP0(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &top0_cg_wegs,		\
		 _shift, &mtk_cwk_gate_ops_no_setcww)

#define GATE_TOP1(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &top1_cg_wegs,		\
		 _shift, &mtk_cwk_gate_ops_no_setcww_inv)

#define GATE_TOP2(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &top2_cg_wegs,		\
		 _shift, &mtk_cwk_gate_ops_no_setcww_inv)

static const stwuct mtk_gate top_cwk_gates[] = {
	GATE_TOP0(CWK_TOP_CONN_32K, "conn_32k", "cwk32k", 10),
	GATE_TOP0(CWK_TOP_CONN_26M, "conn_26m", "cwk26m", 11),
	GATE_TOP0(CWK_TOP_DSP_32K, "dsp_32k", "cwk32k", 16),
	GATE_TOP0(CWK_TOP_DSP_26M, "dsp_26m", "cwk26m", 17),
	GATE_TOP1(CWK_TOP_USB20_48M_EN, "usb20_48m_en", "usb20_192m_d4", 8),
	GATE_TOP1(CWK_TOP_UNIVPWW_48M_EN, "univpww_48m_en", "usb20_192m_d4", 9),
	GATE_TOP1(CWK_TOP_WVDSTX_CWKDIG_EN, "wvdstx_dig_en", "wvdstx_dig_cts", 20),
	GATE_TOP1(CWK_TOP_VPWW_DPIX_EN, "vpww_dpix_en", "vpww_dpix", 21),
	GATE_TOP1(CWK_TOP_SSUSB_TOP_CK_EN, "ssusb_top_ck_en", NUWW, 22),
	GATE_TOP1(CWK_TOP_SSUSB_PHY_CK_EN, "ssusb_phy_ck_en", NUWW, 23),
	GATE_TOP2(CWK_TOP_AUD_I2S0_M, "aud_i2s0_m_ck", "apww12_ck_div0", 0),
	GATE_TOP2(CWK_TOP_AUD_I2S1_M, "aud_i2s1_m_ck", "apww12_ck_div1", 1),
	GATE_TOP2(CWK_TOP_AUD_I2S2_M, "aud_i2s2_m_ck", "apww12_ck_div2", 2),
	GATE_TOP2(CWK_TOP_AUD_I2S3_M, "aud_i2s3_m_ck", "apww12_ck_div3", 3),
	GATE_TOP2(CWK_TOP_AUD_TDMOUT_M, "aud_tdmout_m_ck", "apww12_ck_div4", 4),
	GATE_TOP2(CWK_TOP_AUD_TDMOUT_B, "aud_tdmout_b_ck", "apww12_ck_div4b", 5),
	GATE_TOP2(CWK_TOP_AUD_TDMIN_M, "aud_tdmin_m_ck", "apww12_ck_div5", 6),
	GATE_TOP2(CWK_TOP_AUD_TDMIN_B, "aud_tdmin_b_ck", "apww12_ck_div5b", 7),
	GATE_TOP2(CWK_TOP_AUD_SPDIF_M, "aud_spdif_m_ck", "apww12_ck_div6", 8),
};

static const stwuct mtk_gate_wegs ifw2_cg_wegs = {
	.set_ofs = 0x80,
	.cww_ofs = 0x84,
	.sta_ofs = 0x90,
};

static const stwuct mtk_gate_wegs ifw3_cg_wegs = {
	.set_ofs = 0x88,
	.cww_ofs = 0x8c,
	.sta_ofs = 0x94,
};

static const stwuct mtk_gate_wegs ifw4_cg_wegs = {
	.set_ofs = 0xa4,
	.cww_ofs = 0xa8,
	.sta_ofs = 0xac,
};

static const stwuct mtk_gate_wegs ifw5_cg_wegs = {
	.set_ofs = 0xc0,
	.cww_ofs = 0xc4,
	.sta_ofs = 0xc8,
};

static const stwuct mtk_gate_wegs ifw6_cg_wegs = {
	.set_ofs = 0xd0,
	.cww_ofs = 0xd4,
	.sta_ofs = 0xd8,
};

#define GATE_IFWX(_id, _name, _pawent, _shift, _wegs)	\
	GATE_MTK(_id, _name, _pawent, _wegs, _shift,	\
		 &mtk_cwk_gate_ops_setcww)

#define GATE_IFW2(_id, _name, _pawent, _shift)		\
	GATE_IFWX(_id, _name, _pawent, _shift, &ifw2_cg_wegs)

#define GATE_IFW3(_id, _name, _pawent, _shift)		\
	GATE_IFWX(_id, _name, _pawent, _shift, &ifw3_cg_wegs)

#define GATE_IFW4(_id, _name, _pawent, _shift)		\
	GATE_IFWX(_id, _name, _pawent, _shift, &ifw4_cg_wegs)

#define GATE_IFW5(_id, _name, _pawent, _shift)		\
	GATE_IFWX(_id, _name, _pawent, _shift, &ifw5_cg_wegs)

#define GATE_IFW6(_id, _name, _pawent, _shift)		\
	GATE_IFWX(_id, _name, _pawent, _shift, &ifw6_cg_wegs)

static const stwuct mtk_gate ifw_cwks[] = {
	/* IFW2 */
	GATE_IFW2(CWK_IFW_PMIC_TMW, "ifw_pmic_tmw", "cwk26m", 0),
	GATE_IFW2(CWK_IFW_PMIC_AP, "ifw_pmic_ap", "cwk26m", 1),
	GATE_IFW2(CWK_IFW_PMIC_MD, "ifw_pmic_md", "cwk26m", 2),
	GATE_IFW2(CWK_IFW_PMIC_CONN, "ifw_pmic_conn", "cwk26m", 3),
	GATE_IFW2(CWK_IFW_ICUSB, "ifw_icusb", "axi_sew", 8),
	GATE_IFW2(CWK_IFW_GCE, "ifw_gce", "axi_sew", 9),
	GATE_IFW2(CWK_IFW_THEWM, "ifw_thewm", "axi_sew", 10),
	GATE_IFW2(CWK_IFW_PWM_HCWK, "ifw_pwm_hcwk", "axi_sew", 15),
	GATE_IFW2(CWK_IFW_PWM1, "ifw_pwm1", "pwm_sew", 16),
	GATE_IFW2(CWK_IFW_PWM2, "ifw_pwm2", "pwm_sew", 17),
	GATE_IFW2(CWK_IFW_PWM3, "ifw_pwm3", "pwm_sew", 18),
	GATE_IFW2(CWK_IFW_PWM4, "ifw_pwm4", "pwm_sew", 19),
	GATE_IFW2(CWK_IFW_PWM5, "ifw_pwm5", "pwm_sew", 20),
	GATE_IFW2(CWK_IFW_PWM, "ifw_pwm", "pwm_sew", 21),
	GATE_IFW2(CWK_IFW_UAWT0, "ifw_uawt0", "uawt_sew", 22),
	GATE_IFW2(CWK_IFW_UAWT1, "ifw_uawt1", "uawt_sew", 23),
	GATE_IFW2(CWK_IFW_UAWT2, "ifw_uawt2", "uawt_sew", 24),
	GATE_IFW2(CWK_IFW_DSP_UAWT, "ifw_dsp_uawt", "uawt_sew", 26),
	GATE_IFW2(CWK_IFW_GCE_26M, "ifw_gce_26m", "cwk26m", 27),
	GATE_IFW2(CWK_IFW_CQ_DMA_FPC, "ifw_cq_dma_fpc", "axi_sew", 28),
	GATE_IFW2(CWK_IFW_BTIF, "ifw_btif", "axi_sew", 31),
	/* IFW3 */
	GATE_IFW3(CWK_IFW_SPI0, "ifw_spi0", "spi_sew", 1),
	GATE_IFW3(CWK_IFW_MSDC0_HCWK, "ifw_msdc0", "msdc50_0_hc_sew", 2),
	GATE_IFW3(CWK_IFW_MSDC2_HCWK, "ifw_msdc2", "msdc2_2_hc_sew", 3),
	GATE_IFW3(CWK_IFW_MSDC1_HCWK, "ifw_msdc1", "axi_sew", 4),
	GATE_IFW3(CWK_IFW_DVFSWC, "ifw_dvfswc", "cwk26m", 7),
	GATE_IFW3(CWK_IFW_GCPU, "ifw_gcpu", "axi_sew", 8),
	GATE_IFW3(CWK_IFW_TWNG, "ifw_twng", "axi_sew", 9),
	GATE_IFW3(CWK_IFW_AUXADC, "ifw_auxadc", "cwk26m", 10),
	GATE_IFW3(CWK_IFW_CPUM, "ifw_cpum", "cwk26m", 11),
	GATE_IFW3(CWK_IFW_AUXADC_MD, "ifw_auxadc_md", "cwk26m", 14),
	GATE_IFW3(CWK_IFW_AP_DMA, "ifw_ap_dma", "axi_sew", 18),
	GATE_IFW3(CWK_IFW_DEBUGSYS, "ifw_debugsys", "axi_sew", 24),
	GATE_IFW3(CWK_IFW_AUDIO, "ifw_audio", "axi_sew", 25),
	/* IFW4 */
	GATE_IFW4(CWK_IFW_PWM_FBCWK6, "ifw_pwm_fbcwk6", "pwm_sew", 0),
	GATE_IFW4(CWK_IFW_DISP_PWM, "ifw_disp_pwm", "disp_pwm_sew", 2),
	GATE_IFW4(CWK_IFW_AUD_26M_BK, "ifw_aud_26m_bk", "cwk26m", 4),
	GATE_IFW4(CWK_IFW_CQ_DMA, "ifw_cq_dma", "axi_sew", 27),
	/* IFW5 */
	GATE_IFW5(CWK_IFW_MSDC0_SF, "ifw_msdc0_sf", "msdc50_0_sew", 0),
	GATE_IFW5(CWK_IFW_MSDC1_SF, "ifw_msdc1_sf", "msdc50_0_sew", 1),
	GATE_IFW5(CWK_IFW_MSDC2_SF, "ifw_msdc2_sf", "msdc50_0_sew", 2),
	GATE_IFW5(CWK_IFW_AP_MSDC0, "ifw_ap_msdc0", "msdc50_0_sew", 7),
	GATE_IFW5(CWK_IFW_MD_MSDC0, "ifw_md_msdc0", "msdc50_0_sew", 8),
	GATE_IFW5(CWK_IFW_MSDC0_SWC, "ifw_msdc0_swc", "msdc50_0_sew", 9),
	GATE_IFW5(CWK_IFW_MSDC1_SWC, "ifw_msdc1_swc", "msdc30_1_sew", 10),
	GATE_IFW5(CWK_IFW_MSDC2_SWC, "ifw_msdc2_swc", "msdc50_2_sew", 11),
	GATE_IFW5(CWK_IFW_PWWAP_TMW, "ifw_pwwap_tmw", "cwk26m", 12),
	GATE_IFW5(CWK_IFW_PWWAP_SPI, "ifw_pwwap_spi", "cwk26m", 13),
	GATE_IFW5(CWK_IFW_PWWAP_SYS, "ifw_pwwap_sys", "cwk26m", 14),
	GATE_MTK_FWAGS(CWK_IFW_MCU_PM_BK, "ifw_mcu_pm_bk", NUWW, &ifw5_cg_wegs,
			17, &mtk_cwk_gate_ops_setcww, CWK_IGNOWE_UNUSED),
	GATE_IFW5(CWK_IFW_IWWX_26M, "ifw_iwwx_26m", "cwk26m", 22),
	GATE_IFW5(CWK_IFW_IWWX_32K, "ifw_iwwx_32k", "cwk32k", 23),
	GATE_IFW5(CWK_IFW_I2C0_AXI, "ifw_i2c0_axi", "i2c_sew", 24),
	GATE_IFW5(CWK_IFW_I2C1_AXI, "ifw_i2c1_axi", "i2c_sew", 25),
	GATE_IFW5(CWK_IFW_I2C2_AXI, "ifw_i2c2_axi", "i2c_sew", 26),
	GATE_IFW5(CWK_IFW_I2C3_AXI, "ifw_i2c3_axi", "i2c_sew", 27),
	GATE_IFW5(CWK_IFW_NIC_AXI, "ifw_nic_axi", "axi_sew", 28),
	GATE_IFW5(CWK_IFW_NIC_SWV_AXI, "ifw_nic_swv_axi", "axi_sew", 29),
	GATE_IFW5(CWK_IFW_APU_AXI, "ifw_apu_axi", "axi_sew", 30),
	/* IFW6 */
	GATE_IFW6(CWK_IFW_NFIECC, "ifw_nfiecc", "nfiecc_sew", 0),
	GATE_IFW6(CWK_IFW_NFI1X_BK, "ifw_nfi1x_bk", "nfi2x_sew", 1),
	GATE_IFW6(CWK_IFW_NFIECC_BK, "ifw_nfiecc_bk", "nfi2x_sew", 2),
	GATE_IFW6(CWK_IFW_NFI_BK, "ifw_nfi_bk", "axi_sew", 3),
	GATE_IFW6(CWK_IFW_MSDC2_AP_BK, "ifw_msdc2_ap_bk", "axi_sew", 4),
	GATE_IFW6(CWK_IFW_MSDC2_MD_BK, "ifw_msdc2_md_bk", "axi_sew", 5),
	GATE_IFW6(CWK_IFW_MSDC2_BK, "ifw_msdc2_bk", "axi_sew", 6),
	GATE_IFW6(CWK_IFW_SUSB_133_BK, "ifw_susb_133_bk", "axi_sew", 7),
	GATE_IFW6(CWK_IFW_SUSB_66_BK, "ifw_susb_66_bk", "axi_sew", 8),
	GATE_IFW6(CWK_IFW_SSUSB_SYS, "ifw_ssusb_sys", "ssusb_sys_sew", 9),
	GATE_IFW6(CWK_IFW_SSUSB_WEF, "ifw_ssusb_wef", "ssusb_sys_sew", 10),
	GATE_IFW6(CWK_IFW_SSUSB_XHCI, "ifw_ssusb_xhci", "ssusb_xhci_sew", 11),
};

static const stwuct mtk_gate_wegs pewi_cg_wegs = {
	.set_ofs = 0x20c,
	.cww_ofs = 0x20c,
	.sta_ofs = 0x20c,
};

static const stwuct mtk_gate pewi_cwks[] = {
	GATE_MTK(CWK_PEWIAXI, "pewiaxi", "axi_sew", &pewi_cg_wegs, 31,
		 &mtk_cwk_gate_ops_no_setcww),
};

static const stwuct mtk_cwk_desc topck_desc = {
	.cwks = top_cwk_gates,
	.num_cwks = AWWAY_SIZE(top_cwk_gates),
	.fixed_cwks = top_fixed_cwks,
	.num_fixed_cwks = AWWAY_SIZE(top_fixed_cwks),
	.factow_cwks = top_divs,
	.num_factow_cwks = AWWAY_SIZE(top_divs),
	.mux_cwks = top_muxes,
	.num_mux_cwks = AWWAY_SIZE(top_muxes),
	.composite_cwks = top_misc_muxes,
	.num_composite_cwks = AWWAY_SIZE(top_misc_muxes),
	.dividew_cwks = top_adj_divs,
	.num_dividew_cwks = AWWAY_SIZE(top_adj_divs),
	.cwk_wock = &mt8365_cwk_wock,
};

static const stwuct mtk_cwk_desc infwa_desc = {
	.cwks = ifw_cwks,
	.num_cwks = AWWAY_SIZE(ifw_cwks),
};

static const stwuct mtk_cwk_desc pewi_desc = {
	.cwks = pewi_cwks,
	.num_cwks = AWWAY_SIZE(pewi_cwks),
};

static const stwuct mtk_cwk_desc mcu_desc = {
	.composite_cwks = mcu_muxes,
	.num_composite_cwks = AWWAY_SIZE(mcu_muxes),
	.cwk_wock = &mt8365_cwk_wock,
};

static const stwuct of_device_id of_match_cwk_mt8365[] = {
	{ .compatibwe = "mediatek,mt8365-topckgen", .data = &topck_desc },
	{ .compatibwe = "mediatek,mt8365-infwacfg", .data = &infwa_desc },
	{ .compatibwe = "mediatek,mt8365-pewicfg", .data = &pewi_desc },
	{ .compatibwe = "mediatek,mt8365-mcucfg", .data = &mcu_desc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8365);

static stwuct pwatfowm_dwivew cwk_mt8365_dwv = {
	.dwivew = {
		.name = "cwk-mt8365",
		.of_match_tabwe = of_match_cwk_mt8365,
	},
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
};
moduwe_pwatfowm_dwivew(cwk_mt8365_dwv);
MODUWE_WICENSE("GPW");
