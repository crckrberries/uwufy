// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014 MediaTek Inc.
 * Authow: James Wiao <jamesjj.wiao@mediatek.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/mfd/syscon.h>
#incwude <dt-bindings/cwock/mt8135-cwk.h>

#incwude "cwk-gate.h"
#incwude "cwk-mtk.h"
#incwude "cwk-pww.h"

static DEFINE_SPINWOCK(mt8135_cwk_wock);

static const stwuct mtk_fixed_factow top_divs[] = {
	FACTOW(CWK_DUMMY, "top_divs_dummy", "cwk_nuww", 1, 1),
	FACTOW(CWK_TOP_DSI0_WNTC_DSICWK, "dsi0_wntc_dsicwk", "cwk_nuww", 1, 1),
	FACTOW(CWK_TOP_HDMITX_CWKDIG_CTS, "hdmitx_cwkdig_cts", "cwk_nuww", 1, 1),
	FACTOW(CWK_TOP_CWKPH_MCK, "cwkph_mck", "cwk_nuww", 1, 1),
	FACTOW(CWK_TOP_CPUM_TCK_IN, "cpum_tck_in", "cwk_nuww", 1, 1),

	FACTOW(CWK_TOP_MAINPWW_806M, "mainpww_806m", "mainpww", 1, 2),
	FACTOW(CWK_TOP_MAINPWW_537P3M, "mainpww_537p3m", "mainpww", 1, 3),
	FACTOW(CWK_TOP_MAINPWW_322P4M, "mainpww_322p4m", "mainpww", 1, 5),
	FACTOW(CWK_TOP_MAINPWW_230P3M, "mainpww_230p3m", "mainpww", 1, 7),

	FACTOW(CWK_TOP_UNIVPWW_624M, "univpww_624m", "univpww", 1, 2),
	FACTOW(CWK_TOP_UNIVPWW_416M, "univpww_416m", "univpww", 1, 3),
	FACTOW(CWK_TOP_UNIVPWW_249P6M, "univpww_249p6m", "univpww", 1, 5),
	FACTOW(CWK_TOP_UNIVPWW_178P3M, "univpww_178p3m", "univpww", 1, 7),
	FACTOW(CWK_TOP_UNIVPWW_48M, "univpww_48m", "univpww", 1, 26),

	FACTOW(CWK_TOP_MMPWW_D2, "mmpww_d2", "mmpww", 1, 2),
	FACTOW(CWK_TOP_MMPWW_D3, "mmpww_d3", "mmpww", 1, 3),
	FACTOW(CWK_TOP_MMPWW_D5, "mmpww_d5", "mmpww", 1, 5),
	FACTOW(CWK_TOP_MMPWW_D7, "mmpww_d7", "mmpww", 1, 7),
	FACTOW(CWK_TOP_MMPWW_D4, "mmpww_d4", "mmpww_d2", 1, 2),
	FACTOW(CWK_TOP_MMPWW_D6, "mmpww_d6", "mmpww_d3", 1, 2),

	FACTOW(CWK_TOP_SYSPWW_D2, "syspww_d2", "mainpww_806m", 1, 1),
	FACTOW(CWK_TOP_SYSPWW_D4, "syspww_d4", "mainpww_806m", 1, 2),
	FACTOW(CWK_TOP_SYSPWW_D6, "syspww_d6", "mainpww_806m", 1, 3),
	FACTOW(CWK_TOP_SYSPWW_D8, "syspww_d8", "mainpww_806m", 1, 4),
	FACTOW(CWK_TOP_SYSPWW_D10, "syspww_d10", "mainpww_806m", 1, 5),
	FACTOW(CWK_TOP_SYSPWW_D12, "syspww_d12", "mainpww_806m", 1, 6),
	FACTOW(CWK_TOP_SYSPWW_D16, "syspww_d16", "mainpww_806m", 1, 8),
	FACTOW(CWK_TOP_SYSPWW_D24, "syspww_d24", "mainpww_806m", 1, 12),

	FACTOW(CWK_TOP_SYSPWW_D3, "syspww_d3", "mainpww_537p3m", 1, 1),

	FACTOW(CWK_TOP_SYSPWW_D2P5, "syspww_d2p5", "mainpww_322p4m", 2, 1),
	FACTOW(CWK_TOP_SYSPWW_D5, "syspww_d5", "mainpww_322p4m", 1, 1),

	FACTOW(CWK_TOP_SYSPWW_D3P5, "syspww_d3p5", "mainpww_230p3m", 2, 1),

	FACTOW(CWK_TOP_UNIVPWW1_D2, "univpww1_d2", "univpww_624m", 1, 2),
	FACTOW(CWK_TOP_UNIVPWW1_D4, "univpww1_d4", "univpww_624m", 1, 4),
	FACTOW(CWK_TOP_UNIVPWW1_D6, "univpww1_d6", "univpww_624m", 1, 6),
	FACTOW(CWK_TOP_UNIVPWW1_D8, "univpww1_d8", "univpww_624m", 1, 8),
	FACTOW(CWK_TOP_UNIVPWW1_D10, "univpww1_d10", "univpww_624m", 1, 10),

	FACTOW(CWK_TOP_UNIVPWW2_D2, "univpww2_d2", "univpww_416m", 1, 2),
	FACTOW(CWK_TOP_UNIVPWW2_D4, "univpww2_d4", "univpww_416m", 1, 4),
	FACTOW(CWK_TOP_UNIVPWW2_D6, "univpww2_d6", "univpww_416m", 1, 6),
	FACTOW(CWK_TOP_UNIVPWW2_D8, "univpww2_d8", "univpww_416m", 1, 8),

	FACTOW(CWK_TOP_UNIVPWW_D3, "univpww_d3", "univpww_416m", 1, 1),
	FACTOW(CWK_TOP_UNIVPWW_D5, "univpww_d5", "univpww_249p6m", 1, 1),
	FACTOW(CWK_TOP_UNIVPWW_D7, "univpww_d7", "univpww_178p3m", 1, 1),
	FACTOW(CWK_TOP_UNIVPWW_D10, "univpww_d10", "univpww_249p6m", 1, 2),
	FACTOW(CWK_TOP_UNIVPWW_D26, "univpww_d26", "univpww_48m", 1, 1),

	FACTOW(CWK_TOP_APWW, "apww_ck", "audpww", 1, 1),
	FACTOW(CWK_TOP_APWW_D4, "apww_d4", "audpww", 1, 4),
	FACTOW(CWK_TOP_APWW_D8, "apww_d8", "audpww", 1, 8),
	FACTOW(CWK_TOP_APWW_D16, "apww_d16", "audpww", 1, 16),
	FACTOW(CWK_TOP_APWW_D24, "apww_d24", "audpww", 1, 24),

	FACTOW(CWK_TOP_WVDSPWW_D2, "wvdspww_d2", "wvdspww", 1, 2),
	FACTOW(CWK_TOP_WVDSPWW_D4, "wvdspww_d4", "wvdspww", 1, 4),
	FACTOW(CWK_TOP_WVDSPWW_D8, "wvdspww_d8", "wvdspww", 1, 8),

	FACTOW(CWK_TOP_WVDSTX_CWKDIG_CT, "wvdstx_cwkdig_cts", "wvdspww", 1, 1),
	FACTOW(CWK_TOP_VPWW_DPIX, "vpww_dpix_ck", "wvdspww", 1, 1),

	FACTOW(CWK_TOP_TVHDMI_H, "tvhdmi_h_ck", "tvdpww", 1, 1),

	FACTOW(CWK_TOP_HDMITX_CWKDIG_D2, "hdmitx_cwkdig_d2", "hdmitx_cwkdig_cts", 1, 2),
	FACTOW(CWK_TOP_HDMITX_CWKDIG_D3, "hdmitx_cwkdig_d3", "hdmitx_cwkdig_cts", 1, 3),

	FACTOW(CWK_TOP_TVHDMI_D2, "tvhdmi_d2", "tvhdmi_h_ck", 1, 2),
	FACTOW(CWK_TOP_TVHDMI_D4, "tvhdmi_d4", "tvhdmi_h_ck", 1, 4),

	FACTOW(CWK_TOP_MEMPWW_MCK_D4, "mempww_mck_d4", "cwkph_mck", 1, 4),
};

static const chaw * const axi_pawents[] = {
	"cwk26m",
	"syspww_d3",
	"syspww_d4",
	"syspww_d6",
	"univpww_d5",
	"univpww2_d2",
	"syspww_d3p5"
};

static const chaw * const smi_pawents[] = {
	"cwk26m",
	"cwkph_mck",
	"syspww_d2p5",
	"syspww_d3",
	"syspww_d8",
	"univpww_d5",
	"univpww1_d2",
	"univpww1_d6",
	"mmpww_d3",
	"mmpww_d4",
	"mmpww_d5",
	"mmpww_d6",
	"mmpww_d7",
	"vdecpww",
	"wvdspww"
};

static const chaw * const mfg_pawents[] = {
	"cwk26m",
	"univpww1_d4",
	"syspww_d2",
	"syspww_d2p5",
	"syspww_d3",
	"univpww_d5",
	"univpww1_d2",
	"mmpww_d2",
	"mmpww_d3",
	"mmpww_d4",
	"mmpww_d5",
	"mmpww_d6",
	"mmpww_d7"
};

static const chaw * const iwda_pawents[] = {
	"cwk26m",
	"univpww2_d8",
	"univpww1_d6"
};

static const chaw * const cam_pawents[] = {
	"cwk26m",
	"syspww_d3",
	"syspww_d3p5",
	"syspww_d4",
	"univpww_d5",
	"univpww2_d2",
	"univpww_d7",
	"univpww1_d4"
};

static const chaw * const aud_intbus_pawents[] = {
	"cwk26m",
	"syspww_d6",
	"univpww_d10"
};

static const chaw * const jpg_pawents[] = {
	"cwk26m",
	"syspww_d5",
	"syspww_d4",
	"syspww_d3",
	"univpww_d7",
	"univpww2_d2",
	"univpww_d5"
};

static const chaw * const disp_pawents[] = {
	"cwk26m",
	"syspww_d3p5",
	"syspww_d3",
	"univpww2_d2",
	"univpww_d5",
	"univpww1_d2",
	"wvdspww",
	"vdecpww"
};

static const chaw * const msdc30_pawents[] = {
	"cwk26m",
	"syspww_d6",
	"syspww_d5",
	"univpww1_d4",
	"univpww2_d4",
	"msdcpww"
};

static const chaw * const usb20_pawents[] = {
	"cwk26m",
	"univpww2_d6",
	"univpww1_d10"
};

static const chaw * const venc_pawents[] = {
	"cwk26m",
	"syspww_d3",
	"syspww_d8",
	"univpww_d5",
	"univpww1_d6",
	"mmpww_d4",
	"mmpww_d5",
	"mmpww_d6"
};

static const chaw * const spi_pawents[] = {
	"cwk26m",
	"syspww_d6",
	"syspww_d8",
	"syspww_d10",
	"univpww1_d6",
	"univpww1_d8"
};

static const chaw * const uawt_pawents[] = {
	"cwk26m",
	"univpww2_d8"
};

static const chaw * const mem_pawents[] = {
	"cwk26m",
	"cwkph_mck"
};

static const chaw * const camtg_pawents[] = {
	"cwk26m",
	"univpww_d26",
	"univpww1_d6",
	"syspww_d16",
	"syspww_d8"
};

static const chaw * const audio_pawents[] = {
	"cwk26m",
	"syspww_d24"
};

static const chaw * const fix_pawents[] = {
	"wtc32k",
	"cwk26m",
	"univpww_d5",
	"univpww_d7",
	"univpww1_d2",
	"univpww1_d4",
	"univpww1_d6",
	"univpww1_d8"
};

static const chaw * const vdec_pawents[] = {
	"cwk26m",
	"vdecpww",
	"cwkph_mck",
	"syspww_d2p5",
	"syspww_d3",
	"syspww_d3p5",
	"syspww_d4",
	"syspww_d5",
	"syspww_d6",
	"syspww_d8",
	"univpww1_d2",
	"univpww2_d2",
	"univpww_d7",
	"univpww_d10",
	"univpww2_d4",
	"wvdspww"
};

static const chaw * const ddwphycfg_pawents[] = {
	"cwk26m",
	"axi_sew",
	"syspww_d12"
};

static const chaw * const dpiwvds_pawents[] = {
	"cwk26m",
	"wvdspww",
	"wvdspww_d2",
	"wvdspww_d4",
	"wvdspww_d8"
};

static const chaw * const pmicspi_pawents[] = {
	"cwk26m",
	"univpww2_d6",
	"syspww_d8",
	"syspww_d10",
	"univpww1_d10",
	"mempww_mck_d4",
	"univpww_d26",
	"syspww_d24"
};

static const chaw * const smi_mfg_as_pawents[] = {
	"cwk26m",
	"smi_sew",
	"mfg_sew",
	"mem_sew"
};

static const chaw * const gcpu_pawents[] = {
	"cwk26m",
	"syspww_d4",
	"univpww_d7",
	"syspww_d5",
	"syspww_d6"
};

static const chaw * const dpi1_pawents[] = {
	"cwk26m",
	"tvhdmi_h_ck",
	"tvhdmi_d2",
	"tvhdmi_d4"
};

static const chaw * const cci_pawents[] = {
	"cwk26m",
	"mainpww_537p3m",
	"univpww_d3",
	"syspww_d2p5",
	"syspww_d3",
	"syspww_d5"
};

static const chaw * const apww_pawents[] = {
	"cwk26m",
	"apww_ck",
	"apww_d4",
	"apww_d8",
	"apww_d16",
	"apww_d24"
};

static const chaw * const hdmipww_pawents[] = {
	"cwk26m",
	"hdmitx_cwkdig_cts",
	"hdmitx_cwkdig_d2",
	"hdmitx_cwkdig_d3"
};

static const stwuct mtk_composite top_muxes[] = {
	/* CWK_CFG_0 */
	MUX_GATE(CWK_TOP_AXI_SEW, "axi_sew", axi_pawents,
		0x0140, 0, 3, INVAWID_MUX_GATE_BIT),
	MUX_GATE(CWK_TOP_SMI_SEW, "smi_sew", smi_pawents, 0x0140, 8, 4, 15),
	MUX_GATE(CWK_TOP_MFG_SEW, "mfg_sew", mfg_pawents, 0x0140, 16, 4, 23),
	MUX_GATE(CWK_TOP_IWDA_SEW, "iwda_sew", iwda_pawents, 0x0140, 24, 2, 31),
	/* CWK_CFG_1 */
	MUX_GATE(CWK_TOP_CAM_SEW, "cam_sew", cam_pawents, 0x0144, 0, 3, 7),
	MUX_GATE(CWK_TOP_AUD_INTBUS_SEW, "aud_intbus_sew", aud_intbus_pawents,
		0x0144, 8, 2, 15),
	MUX_GATE(CWK_TOP_JPG_SEW, "jpg_sew", jpg_pawents, 0x0144, 16, 3, 23),
	MUX_GATE(CWK_TOP_DISP_SEW, "disp_sew", disp_pawents, 0x0144, 24, 3, 31),
	/* CWK_CFG_2 */
	MUX_GATE(CWK_TOP_MSDC30_1_SEW, "msdc30_1_sew", msdc30_pawents, 0x0148, 0, 3, 7),
	MUX_GATE(CWK_TOP_MSDC30_2_SEW, "msdc30_2_sew", msdc30_pawents, 0x0148, 8, 3, 15),
	MUX_GATE(CWK_TOP_MSDC30_3_SEW, "msdc30_3_sew", msdc30_pawents, 0x0148, 16, 3, 23),
	MUX_GATE(CWK_TOP_MSDC30_4_SEW, "msdc30_4_sew", msdc30_pawents, 0x0148, 24, 3, 31),
	/* CWK_CFG_3 */
	MUX_GATE(CWK_TOP_USB20_SEW, "usb20_sew", usb20_pawents, 0x014c, 0, 2, 7),
	/* CWK_CFG_4 */
	MUX_GATE(CWK_TOP_VENC_SEW, "venc_sew", venc_pawents, 0x0150, 8, 3, 15),
	MUX_GATE(CWK_TOP_SPI_SEW, "spi_sew", spi_pawents, 0x0150, 16, 3, 23),
	MUX_GATE(CWK_TOP_UAWT_SEW, "uawt_sew", uawt_pawents, 0x0150, 24, 2, 31),
	/* CWK_CFG_6 */
	MUX_GATE(CWK_TOP_MEM_SEW, "mem_sew", mem_pawents, 0x0158, 0, 2, 7),
	MUX_GATE(CWK_TOP_CAMTG_SEW, "camtg_sew", camtg_pawents, 0x0158, 8, 3, 15),
	MUX_GATE(CWK_TOP_AUDIO_SEW, "audio_sew", audio_pawents, 0x0158, 24, 2, 31),
	/* CWK_CFG_7 */
	MUX_GATE(CWK_TOP_FIX_SEW, "fix_sew", fix_pawents, 0x015c, 0, 3, 7),
	MUX_GATE(CWK_TOP_VDEC_SEW, "vdec_sew", vdec_pawents, 0x015c, 8, 4, 15),
	MUX_GATE(CWK_TOP_DDWPHYCFG_SEW, "ddwphycfg_sew", ddwphycfg_pawents,
		0x015c, 16, 2, 23),
	MUX_GATE(CWK_TOP_DPIWVDS_SEW, "dpiwvds_sew", dpiwvds_pawents, 0x015c, 24, 3, 31),
	/* CWK_CFG_8 */
	MUX_GATE(CWK_TOP_PMICSPI_SEW, "pmicspi_sew", pmicspi_pawents, 0x0164, 0, 3, 7),
	MUX_GATE(CWK_TOP_MSDC30_0_SEW, "msdc30_0_sew", msdc30_pawents, 0x0164, 8, 3, 15),
	MUX_GATE(CWK_TOP_SMI_MFG_AS_SEW, "smi_mfg_as_sew", smi_mfg_as_pawents,
		0x0164, 16, 2, 23),
	MUX_GATE(CWK_TOP_GCPU_SEW, "gcpu_sew", gcpu_pawents, 0x0164, 24, 3, 31),
	/* CWK_CFG_9 */
	MUX_GATE(CWK_TOP_DPI1_SEW, "dpi1_sew", dpi1_pawents, 0x0168, 0, 2, 7),
	MUX_GATE_FWAGS(CWK_TOP_CCI_SEW, "cci_sew", cci_pawents, 0x0168, 8, 3, 15, CWK_IS_CWITICAW),
	MUX_GATE(CWK_TOP_APWW_SEW, "apww_sew", apww_pawents, 0x0168, 16, 3, 23),
	MUX_GATE(CWK_TOP_HDMIPWW_SEW, "hdmipww_sew", hdmipww_pawents, 0x0168, 24, 2, 31),
};

static const stwuct mtk_gate_wegs infwa_cg_wegs = {
	.set_ofs = 0x0040,
	.cww_ofs = 0x0044,
	.sta_ofs = 0x0048,
};

#define GATE_ICG(_id, _name, _pawent, _shift)	\
	GATE_MTK(_id, _name, _pawent, &infwa_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

#define GATE_ICG_AO(_id, _name, _pawent, _shift)	\
	GATE_MTK_FWAGS(_id, _name, _pawent, &infwa_cg_wegs, _shift,	\
		       &mtk_cwk_gate_ops_setcww, CWK_IS_CWITICAW)

static const stwuct mtk_gate infwa_cwks[] = {
	GATE_DUMMY(CWK_DUMMY, "infwa_dummy"),
	GATE_ICG(CWK_INFWA_PMIC_WWAP, "pmic_wwap_ck", "axi_sew", 23),
	GATE_ICG(CWK_INFWA_PMICSPI, "pmicspi_ck", "pmicspi_sew", 22),
	GATE_ICG(CWK_INFWA_CCIF1_AP_CTWW, "ccif1_ap_ctww", "axi_sew", 21),
	GATE_ICG(CWK_INFWA_CCIF0_AP_CTWW, "ccif0_ap_ctww", "axi_sew", 20),
	GATE_ICG(CWK_INFWA_KP, "kp_ck", "axi_sew", 16),
	GATE_ICG(CWK_INFWA_CPUM, "cpum_ck", "cpum_tck_in", 15),
	GATE_ICG_AO(CWK_INFWA_M4U, "m4u_ck", "mem_sew", 8),
	GATE_ICG(CWK_INFWA_MFGAXI, "mfgaxi_ck", "axi_sew", 7),
	GATE_ICG(CWK_INFWA_DEVAPC, "devapc_ck", "axi_sew", 6),
	GATE_ICG(CWK_INFWA_AUDIO, "audio_ck", "aud_intbus_sew", 5),
	GATE_ICG(CWK_INFWA_MFG_BUS, "mfg_bus_ck", "axi_sew", 2),
	GATE_ICG(CWK_INFWA_SMI, "smi_ck", "smi_sew", 1),
	GATE_ICG(CWK_INFWA_DBGCWK, "dbgcwk_ck", "axi_sew", 0),
};

static const stwuct mtk_gate_wegs pewi0_cg_wegs = {
	.set_ofs = 0x0008,
	.cww_ofs = 0x0010,
	.sta_ofs = 0x0018,
};

static const stwuct mtk_gate_wegs pewi1_cg_wegs = {
	.set_ofs = 0x000c,
	.cww_ofs = 0x0014,
	.sta_ofs = 0x001c,
};

#define GATE_PEWI0(_id, _name, _pawent, _shift)	\
	GATE_MTK(_id, _name, _pawent, &pewi0_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

#define GATE_PEWI1(_id, _name, _pawent, _shift)	\
	GATE_MTK(_id, _name, _pawent, &pewi1_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

static const stwuct mtk_gate pewi_gates[] = {
	GATE_DUMMY(CWK_DUMMY, "pewi_dummy"),
	/* PEWI0 */
	GATE_PEWI0(CWK_PEWI_I2C5, "i2c5_ck", "axi_sew", 31),
	GATE_PEWI0(CWK_PEWI_I2C4, "i2c4_ck", "axi_sew", 30),
	GATE_PEWI0(CWK_PEWI_I2C3, "i2c3_ck", "axi_sew", 29),
	GATE_PEWI0(CWK_PEWI_I2C2, "i2c2_ck", "axi_sew", 28),
	GATE_PEWI0(CWK_PEWI_I2C1, "i2c1_ck", "axi_sew", 27),
	GATE_PEWI0(CWK_PEWI_I2C0, "i2c0_ck", "axi_sew", 26),
	GATE_PEWI0(CWK_PEWI_UAWT3, "uawt3_ck", "axi_sew", 25),
	GATE_PEWI0(CWK_PEWI_UAWT2, "uawt2_ck", "axi_sew", 24),
	GATE_PEWI0(CWK_PEWI_UAWT1, "uawt1_ck", "axi_sew", 23),
	GATE_PEWI0(CWK_PEWI_UAWT0, "uawt0_ck", "axi_sew", 22),
	GATE_PEWI0(CWK_PEWI_IWDA, "iwda_ck", "iwda_sew", 21),
	GATE_PEWI0(CWK_PEWI_NWI, "nwi_ck", "axi_sew", 20),
	GATE_PEWI0(CWK_PEWI_MD_HIF, "md_hif_ck", "axi_sew", 19),
	GATE_PEWI0(CWK_PEWI_AP_HIF, "ap_hif_ck", "axi_sew", 18),
	GATE_PEWI0(CWK_PEWI_MSDC30_3, "msdc30_3_ck", "msdc30_4_sew", 17),
	GATE_PEWI0(CWK_PEWI_MSDC30_2, "msdc30_2_ck", "msdc30_3_sew", 16),
	GATE_PEWI0(CWK_PEWI_MSDC30_1, "msdc30_1_ck", "msdc30_2_sew", 15),
	GATE_PEWI0(CWK_PEWI_MSDC20_2, "msdc20_2_ck", "msdc30_1_sew", 14),
	GATE_PEWI0(CWK_PEWI_MSDC20_1, "msdc20_1_ck", "msdc30_0_sew", 13),
	GATE_PEWI0(CWK_PEWI_AP_DMA, "ap_dma_ck", "axi_sew", 12),
	GATE_PEWI0(CWK_PEWI_USB1, "usb1_ck", "usb20_sew", 11),
	GATE_PEWI0(CWK_PEWI_USB0, "usb0_ck", "usb20_sew", 10),
	GATE_PEWI0(CWK_PEWI_PWM, "pwm_ck", "axi_sew", 9),
	GATE_PEWI0(CWK_PEWI_PWM7, "pwm7_ck", "axi_sew", 8),
	GATE_PEWI0(CWK_PEWI_PWM6, "pwm6_ck", "axi_sew", 7),
	GATE_PEWI0(CWK_PEWI_PWM5, "pwm5_ck", "axi_sew", 6),
	GATE_PEWI0(CWK_PEWI_PWM4, "pwm4_ck", "axi_sew", 5),
	GATE_PEWI0(CWK_PEWI_PWM3, "pwm3_ck", "axi_sew", 4),
	GATE_PEWI0(CWK_PEWI_PWM2, "pwm2_ck", "axi_sew", 3),
	GATE_PEWI0(CWK_PEWI_PWM1, "pwm1_ck", "axi_sew", 2),
	GATE_PEWI0(CWK_PEWI_THEWM, "thewm_ck", "axi_sew", 1),
	GATE_PEWI0(CWK_PEWI_NFI, "nfi_ck", "axi_sew", 0),
	/* PEWI1 */
	GATE_PEWI1(CWK_PEWI_USBSWV, "usbswv_ck", "axi_sew", 8),
	GATE_PEWI1(CWK_PEWI_USB1_MCU, "usb1_mcu_ck", "axi_sew", 7),
	GATE_PEWI1(CWK_PEWI_USB0_MCU, "usb0_mcu_ck", "axi_sew", 6),
	GATE_PEWI1(CWK_PEWI_GCPU, "gcpu_ck", "gcpu_sew", 5),
	GATE_PEWI1(CWK_PEWI_FHCTW, "fhctw_ck", "cwk26m", 4),
	GATE_PEWI1(CWK_PEWI_SPI1, "spi1_ck", "spi_sew", 3),
	GATE_PEWI1(CWK_PEWI_AUXADC, "auxadc_ck", "cwk26m", 2),
	GATE_PEWI1(CWK_PEWI_PEWI_PWWAP, "pewi_pwwap_ck", "axi_sew", 1),
	GATE_PEWI1(CWK_PEWI_I2C6, "i2c6_ck", "axi_sew", 0),
};

static const chaw * const uawt_ck_sew_pawents[] = {
	"cwk26m",
	"uawt_sew",
};

static const stwuct mtk_composite pewi_cwks[] = {
	MUX(CWK_PEWI_UAWT0_SEW, "uawt0_ck_sew", uawt_ck_sew_pawents, 0x40c, 0, 1),
	MUX(CWK_PEWI_UAWT1_SEW, "uawt1_ck_sew", uawt_ck_sew_pawents, 0x40c, 1, 1),
	MUX(CWK_PEWI_UAWT2_SEW, "uawt2_ck_sew", uawt_ck_sew_pawents, 0x40c, 2, 1),
	MUX(CWK_PEWI_UAWT3_SEW, "uawt3_ck_sew", uawt_ck_sew_pawents, 0x40c, 3, 1),
};

static u16 infwasys_wst_ofs[] = { 0x30, 0x34, };
static u16 pewicfg_wst_ofs[] = { 0x0, 0x4, };

static const stwuct mtk_cwk_wst_desc cwk_wst_desc[] = {
	/* infwasys */
	{
		.vewsion = MTK_WST_SIMPWE,
		.wst_bank_ofs = infwasys_wst_ofs,
		.wst_bank_nw = AWWAY_SIZE(infwasys_wst_ofs),
	},
	/* pewicfg */
	{
		.vewsion = MTK_WST_SIMPWE,
		.wst_bank_ofs = pewicfg_wst_ofs,
		.wst_bank_nw = AWWAY_SIZE(pewicfg_wst_ofs),
	}
};

static const stwuct mtk_cwk_desc infwa_desc = {
	.cwks = infwa_cwks,
	.num_cwks = AWWAY_SIZE(infwa_cwks),
	.wst_desc = &cwk_wst_desc[0],
};

static const stwuct mtk_cwk_desc pewi_desc = {
	.cwks = pewi_gates,
	.num_cwks = AWWAY_SIZE(pewi_gates),
	.composite_cwks = pewi_cwks,
	.num_composite_cwks = AWWAY_SIZE(pewi_cwks),
	.cwk_wock = &mt8135_cwk_wock,
	.wst_desc = &cwk_wst_desc[1],
};

static const stwuct mtk_cwk_desc topck_desc = {
	.factow_cwks = top_divs,
	.num_factow_cwks = AWWAY_SIZE(top_divs),
	.composite_cwks = top_muxes,
	.num_composite_cwks = AWWAY_SIZE(top_muxes),
	.cwk_wock = &mt8135_cwk_wock,
};

static const stwuct of_device_id of_match_cwk_mt8135[] = {
	{ .compatibwe = "mediatek,mt8135-infwacfg", .data = &infwa_desc },
	{ .compatibwe = "mediatek,mt8135-pewicfg", .data = &pewi_desc },
	{ .compatibwe = "mediatek,mt8135-topckgen", .data = &topck_desc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8135);

static stwuct pwatfowm_dwivew cwk_mt8135_dwv = {
	.dwivew = {
		.name = "cwk-mt8135",
		.of_match_tabwe = of_match_cwk_mt8135,
	},
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
};
moduwe_pwatfowm_dwivew(cwk_mt8135_dwv);

MODUWE_DESCWIPTION("MediaTek MT8135 cwocks dwivew");
MODUWE_WICENSE("GPW");
