// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014 MediaTek Inc.
 * Authow: Shunwi Wang <shunwi.wang@mediatek.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-cpumux.h"
#incwude "cwk-gate.h"
#incwude "cwk-mtk.h"
#incwude "cwk-pww.h"

#incwude <dt-bindings/cwock/mt2701-cwk.h>

/*
 * Fow some cwocks, we don't cawe what theiw actuaw wates awe. And these
 * cwocks may change theiw wate on diffewent pwoducts ow diffewent scenawios.
 * So we modew these cwocks' wate as 0, to denote it's not an actuaw wate.
 */
#define DUMMY_WATE		0

static DEFINE_SPINWOCK(mt2701_cwk_wock);

static const stwuct mtk_fixed_cwk top_fixed_cwks[] = {
	FIXED_CWK(CWK_TOP_DPI, "dpi_ck", "cwk26m",
		108 * MHZ),
	FIXED_CWK(CWK_TOP_DMPWW, "dmpww_ck", "cwk26m",
		400 * MHZ),
	FIXED_CWK(CWK_TOP_VENCPWW, "vencpww_ck", "cwk26m",
		295750000),
	FIXED_CWK(CWK_TOP_HDMI_0_PIX340M, "hdmi_0_pix340m", "cwk26m",
		340 * MHZ),
	FIXED_CWK(CWK_TOP_HDMI_0_DEEP340M, "hdmi_0_deep340m", "cwk26m",
		340 * MHZ),
	FIXED_CWK(CWK_TOP_HDMI_0_PWW340M, "hdmi_0_pww340m", "cwk26m",
		340 * MHZ),
	FIXED_CWK(CWK_TOP_HADDS2_FB, "hadds2_fbcwk", "cwk26m",
		27 * MHZ),
	FIXED_CWK(CWK_TOP_WBG_DIG_416M, "wbg_dig_ck_416m", "cwk26m",
		416 * MHZ),
	FIXED_CWK(CWK_TOP_DSI0_WNTC_DSI, "dsi0_wntc_dsi", "cwk26m",
		143 * MHZ),
	FIXED_CWK(CWK_TOP_HDMI_SCW_WX, "hdmi_scw_wx", "cwk26m",
		27 * MHZ),
	FIXED_CWK(CWK_TOP_AUD_EXT1, "aud_ext1", "cwk26m",
		DUMMY_WATE),
	FIXED_CWK(CWK_TOP_AUD_EXT2, "aud_ext2", "cwk26m",
		DUMMY_WATE),
	FIXED_CWK(CWK_TOP_NFI1X_PAD, "nfi1x_pad", "cwk26m",
		DUMMY_WATE),
};

static const stwuct mtk_fixed_factow top_fixed_divs[] = {
	FACTOW(CWK_TOP_SYSPWW, "syspww_ck", "mainpww", 1, 1),
	FACTOW(CWK_TOP_SYSPWW_D2, "syspww_d2", "mainpww", 1, 2),
	FACTOW(CWK_TOP_SYSPWW_D3, "syspww_d3", "mainpww", 1, 3),
	FACTOW(CWK_TOP_SYSPWW_D5, "syspww_d5", "mainpww", 1, 5),
	FACTOW(CWK_TOP_SYSPWW_D7, "syspww_d7", "mainpww", 1, 7),
	FACTOW(CWK_TOP_SYSPWW1_D2, "syspww1_d2", "syspww_d2", 1, 2),
	FACTOW(CWK_TOP_SYSPWW1_D4, "syspww1_d4", "syspww_d2", 1, 4),
	FACTOW(CWK_TOP_SYSPWW1_D8, "syspww1_d8", "syspww_d2", 1, 8),
	FACTOW(CWK_TOP_SYSPWW1_D16, "syspww1_d16", "syspww_d2", 1, 16),
	FACTOW(CWK_TOP_SYSPWW2_D2, "syspww2_d2", "syspww_d3", 1, 2),
	FACTOW(CWK_TOP_SYSPWW2_D4, "syspww2_d4", "syspww_d3", 1, 4),
	FACTOW(CWK_TOP_SYSPWW2_D8, "syspww2_d8", "syspww_d3", 1, 8),
	FACTOW(CWK_TOP_SYSPWW3_D2, "syspww3_d2", "syspww_d5", 1, 2),
	FACTOW(CWK_TOP_SYSPWW3_D4, "syspww3_d4", "syspww_d5", 1, 4),
	FACTOW(CWK_TOP_SYSPWW4_D2, "syspww4_d2", "syspww_d7", 1, 2),
	FACTOW(CWK_TOP_SYSPWW4_D4, "syspww4_d4", "syspww_d7", 1, 4),

	FACTOW(CWK_TOP_UNIVPWW, "univpww_ck", "univpww", 1, 1),
	FACTOW(CWK_TOP_UNIVPWW_D2, "univpww_d2", "univpww", 1, 2),
	FACTOW(CWK_TOP_UNIVPWW_D3, "univpww_d3", "univpww", 1, 3),
	FACTOW(CWK_TOP_UNIVPWW_D5, "univpww_d5", "univpww", 1, 5),
	FACTOW(CWK_TOP_UNIVPWW_D7, "univpww_d7", "univpww", 1, 7),
	FACTOW(CWK_TOP_UNIVPWW_D26, "univpww_d26", "univpww", 1, 26),
	FACTOW(CWK_TOP_UNIVPWW_D52, "univpww_d52", "univpww", 1, 52),
	FACTOW(CWK_TOP_UNIVPWW_D108, "univpww_d108", "univpww", 1, 108),
	FACTOW(CWK_TOP_USB_PHY48M, "usb_phy48m_ck", "univpww", 1, 26),
	FACTOW(CWK_TOP_UNIVPWW1_D2, "univpww1_d2", "univpww_d2", 1, 2),
	FACTOW(CWK_TOP_UNIVPWW1_D4, "univpww1_d4", "univpww_d2", 1, 4),
	FACTOW(CWK_TOP_UNIVPWW1_D8, "univpww1_d8", "univpww_d2", 1, 8),
	FACTOW(CWK_TOP_8BDAC, "8bdac_ck", "univpww_d2", 1, 1),
	FACTOW(CWK_TOP_UNIVPWW2_D2, "univpww2_d2", "univpww_d3", 1, 2),
	FACTOW(CWK_TOP_UNIVPWW2_D4, "univpww2_d4", "univpww_d3", 1, 4),
	FACTOW(CWK_TOP_UNIVPWW2_D8, "univpww2_d8", "univpww_d3", 1, 8),
	FACTOW(CWK_TOP_UNIVPWW2_D16, "univpww2_d16", "univpww_d3", 1, 16),
	FACTOW(CWK_TOP_UNIVPWW2_D32, "univpww2_d32", "univpww_d3", 1, 32),
	FACTOW(CWK_TOP_UNIVPWW3_D2, "univpww3_d2", "univpww_d5", 1, 2),
	FACTOW(CWK_TOP_UNIVPWW3_D4, "univpww3_d4", "univpww_d5", 1, 4),
	FACTOW(CWK_TOP_UNIVPWW3_D8, "univpww3_d8", "univpww_d5", 1, 8),

	FACTOW(CWK_TOP_MSDCPWW, "msdcpww_ck", "msdcpww", 1, 1),
	FACTOW(CWK_TOP_MSDCPWW_D2, "msdcpww_d2", "msdcpww", 1, 2),
	FACTOW(CWK_TOP_MSDCPWW_D4, "msdcpww_d4", "msdcpww", 1, 4),
	FACTOW(CWK_TOP_MSDCPWW_D8, "msdcpww_d8", "msdcpww", 1, 8),

	FACTOW(CWK_TOP_MMPWW, "mmpww_ck", "mmpww", 1, 1),
	FACTOW(CWK_TOP_MMPWW_D2, "mmpww_d2", "mmpww", 1, 2),

	FACTOW(CWK_TOP_DMPWW_D2, "dmpww_d2", "dmpww_ck", 1, 2),
	FACTOW(CWK_TOP_DMPWW_D4, "dmpww_d4", "dmpww_ck", 1, 4),
	FACTOW(CWK_TOP_DMPWW_X2, "dmpww_x2", "dmpww_ck", 1, 1),

	FACTOW(CWK_TOP_TVDPWW, "tvdpww_ck", "tvdpww", 1, 1),
	FACTOW(CWK_TOP_TVDPWW_D2, "tvdpww_d2", "tvdpww", 1, 2),
	FACTOW(CWK_TOP_TVDPWW_D4, "tvdpww_d4", "tvdpww", 1, 4),

	FACTOW(CWK_TOP_VDECPWW, "vdecpww_ck", "vdecpww", 1, 1),
	FACTOW(CWK_TOP_TVD2PWW, "tvd2pww_ck", "tvd2pww", 1, 1),
	FACTOW(CWK_TOP_TVD2PWW_D2, "tvd2pww_d2", "tvd2pww", 1, 2),

	FACTOW(CWK_TOP_MIPIPWW, "mipipww", "dpi_ck", 1, 1),
	FACTOW(CWK_TOP_MIPIPWW_D2, "mipipww_d2", "dpi_ck", 1, 2),
	FACTOW(CWK_TOP_MIPIPWW_D4, "mipipww_d4", "dpi_ck", 1, 4),

	FACTOW(CWK_TOP_HDMIPWW, "hdmipww_ck", "hdmitx_dig_cts", 1, 1),
	FACTOW(CWK_TOP_HDMIPWW_D2, "hdmipww_d2", "hdmitx_dig_cts", 1, 2),
	FACTOW(CWK_TOP_HDMIPWW_D3, "hdmipww_d3", "hdmitx_dig_cts", 1, 3),

	FACTOW(CWK_TOP_AWMPWW_1P3G, "awmpww_1p3g_ck", "awmpww", 1, 1),

	FACTOW(CWK_TOP_AUDPWW, "audpww", "audpww_sew", 1, 1),
	FACTOW(CWK_TOP_AUDPWW_D4, "audpww_d4", "audpww_sew", 1, 4),
	FACTOW(CWK_TOP_AUDPWW_D8, "audpww_d8", "audpww_sew", 1, 8),
	FACTOW(CWK_TOP_AUDPWW_D16, "audpww_d16", "audpww_sew", 1, 16),
	FACTOW(CWK_TOP_AUDPWW_D24, "audpww_d24", "audpww_sew", 1, 24),

	FACTOW(CWK_TOP_AUD1PWW_98M, "aud1pww_98m_ck", "aud1pww", 1, 3),
	FACTOW(CWK_TOP_AUD2PWW_90M, "aud2pww_90m_ck", "aud2pww", 1, 3),
	FACTOW(CWK_TOP_HADDS2PWW_98M, "hadds2pww_98m", "hadds2pww", 1, 3),
	FACTOW(CWK_TOP_HADDS2PWW_294M, "hadds2pww_294m", "hadds2pww", 1, 1),
	FACTOW(CWK_TOP_ETHPWW_500M, "ethpww_500m_ck", "ethpww", 1, 1),
	FACTOW(CWK_TOP_CWK26M_D8, "cwk26m_d8", "cwk26m", 1, 8),
	FACTOW(CWK_TOP_32K_INTEWNAW, "32k_intewnaw", "cwk26m", 1, 793),
	FACTOW(CWK_TOP_32K_EXTEWNAW, "32k_extewnaw", "wtc32k", 1, 1),
	FACTOW(CWK_TOP_AXISEW_D4, "axisew_d4", "axi_sew", 1, 4),
};

static const chaw * const axi_pawents[] = {
	"cwk26m",
	"syspww1_d2",
	"syspww_d5",
	"syspww1_d4",
	"univpww_d5",
	"univpww2_d2",
	"mmpww_d2",
	"dmpww_d2"
};

static const chaw * const mem_pawents[] = {
	"cwk26m",
	"dmpww_ck"
};

static const chaw * const ddwphycfg_pawents[] = {
	"cwk26m",
	"syspww1_d8"
};

static const chaw * const mm_pawents[] = {
	"cwk26m",
	"vencpww_ck",
	"syspww1_d2",
	"syspww1_d4",
	"univpww_d5",
	"univpww1_d2",
	"univpww2_d2",
	"dmpww_ck"
};

static const chaw * const pwm_pawents[] = {
	"cwk26m",
	"univpww2_d4",
	"univpww3_d2",
	"univpww1_d4",
};

static const chaw * const vdec_pawents[] = {
	"cwk26m",
	"vdecpww_ck",
	"syspww_d5",
	"syspww1_d4",
	"univpww_d5",
	"univpww2_d2",
	"vencpww_ck",
	"msdcpww_d2",
	"mmpww_d2"
};

static const chaw * const mfg_pawents[] = {
	"cwk26m",
	"mmpww_ck",
	"dmpww_x2_ck",
	"msdcpww_ck",
	"cwk26m",
	"syspww_d3",
	"univpww_d3",
	"univpww1_d2"
};

static const chaw * const camtg_pawents[] = {
	"cwk26m",
	"univpww_d26",
	"univpww2_d2",
	"syspww3_d2",
	"syspww3_d4",
	"msdcpww_d2",
	"mmpww_d2"
};

static const chaw * const uawt_pawents[] = {
	"cwk26m",
	"univpww2_d8"
};

static const chaw * const spi_pawents[] = {
	"cwk26m",
	"syspww3_d2",
	"syspww4_d2",
	"univpww2_d4",
	"univpww1_d8"
};

static const chaw * const usb20_pawents[] = {
	"cwk26m",
	"univpww1_d8",
	"univpww3_d4"
};

static const chaw * const msdc30_pawents[] = {
	"cwk26m",
	"msdcpww_d2",
	"syspww2_d2",
	"syspww1_d4",
	"univpww1_d4",
	"univpww2_d4"
};

static const chaw * const aud_intbus_pawents[] = {
	"cwk26m",
	"syspww1_d4",
	"syspww3_d2",
	"syspww4_d2",
	"univpww3_d2",
	"univpww2_d4"
};

static const chaw * const pmicspi_pawents[] = {
	"cwk26m",
	"syspww1_d8",
	"syspww2_d4",
	"syspww4_d2",
	"syspww3_d4",
	"syspww2_d8",
	"syspww1_d16",
	"univpww3_d4",
	"univpww_d26",
	"dmpww_d2",
	"dmpww_d4"
};

static const chaw * const scp_pawents[] = {
	"cwk26m",
	"syspww1_d8",
	"dmpww_d2",
	"dmpww_d4"
};

static const chaw * const dpi0_pawents[] = {
	"cwk26m",
	"mipipww",
	"mipipww_d2",
	"mipipww_d4",
	"cwk26m",
	"tvdpww_ck",
	"tvdpww_d2",
	"tvdpww_d4"
};

static const chaw * const dpi1_pawents[] = {
	"cwk26m",
	"tvdpww_ck",
	"tvdpww_d2",
	"tvdpww_d4"
};

static const chaw * const tve_pawents[] = {
	"cwk26m",
	"mipipww",
	"mipipww_d2",
	"mipipww_d4",
	"cwk26m",
	"tvdpww_ck",
	"tvdpww_d2",
	"tvdpww_d4"
};

static const chaw * const hdmi_pawents[] = {
	"cwk26m",
	"hdmipww_ck",
	"hdmipww_d2",
	"hdmipww_d3"
};

static const chaw * const apww_pawents[] = {
	"cwk26m",
	"audpww",
	"audpww_d4",
	"audpww_d8",
	"audpww_d16",
	"audpww_d24",
	"cwk26m",
	"cwk26m"
};

static const chaw * const wtc_pawents[] = {
	"32k_intewnaw",
	"32k_extewnaw",
	"cwk26m",
	"univpww3_d8"
};

static const chaw * const nfi2x_pawents[] = {
	"cwk26m",
	"syspww2_d2",
	"syspww_d7",
	"univpww3_d2",
	"syspww2_d4",
	"univpww3_d4",
	"syspww4_d4",
	"cwk26m"
};

static const chaw * const emmc_hcwk_pawents[] = {
	"cwk26m",
	"syspww1_d2",
	"syspww1_d4",
	"syspww2_d2"
};

static const chaw * const fwash_pawents[] = {
	"cwk26m_d8",
	"cwk26m",
	"syspww2_d8",
	"syspww3_d4",
	"univpww3_d4",
	"syspww4_d2",
	"syspww2_d4",
	"univpww2_d4"
};

static const chaw * const di_pawents[] = {
	"cwk26m",
	"tvd2pww_ck",
	"tvd2pww_d2",
	"cwk26m"
};

static const chaw * const nw_osd_pawents[] = {
	"cwk26m",
	"vencpww_ck",
	"syspww1_d2",
	"syspww1_d4",
	"univpww_d5",
	"univpww1_d2",
	"univpww2_d2",
	"dmpww_ck"
};

static const chaw * const hdmiwx_bist_pawents[] = {
	"cwk26m",
	"syspww_d3",
	"cwk26m",
	"syspww1_d16",
	"syspww4_d2",
	"syspww1_d4",
	"vencpww_ck",
	"cwk26m"
};

static const chaw * const intdiw_pawents[] = {
	"cwk26m",
	"mmpww_ck",
	"syspww_d2",
	"univpww_d2"
};

static const chaw * const asm_pawents[] = {
	"cwk26m",
	"univpww2_d4",
	"univpww2_d2",
	"syspww_d5"
};

static const chaw * const ms_cawd_pawents[] = {
	"cwk26m",
	"univpww3_d8",
	"syspww4_d4"
};

static const chaw * const ethif_pawents[] = {
	"cwk26m",
	"syspww1_d2",
	"syspww_d5",
	"syspww1_d4",
	"univpww_d5",
	"univpww1_d2",
	"dmpww_ck",
	"dmpww_d2"
};

static const chaw * const hdmiwx_pawents[] = {
	"cwk26m",
	"univpww_d52"
};

static const chaw * const cmsys_pawents[] = {
	"cwk26m",
	"syspww1_d2",
	"univpww1_d2",
	"univpww_d5",
	"syspww_d5",
	"syspww2_d2",
	"syspww1_d4",
	"syspww3_d2",
	"syspww2_d4",
	"syspww1_d8",
	"cwk26m",
	"cwk26m",
	"cwk26m",
	"cwk26m",
	"cwk26m"
};

static const chaw * const cwk_8bdac_pawents[] = {
	"32k_intewnaw",
	"8bdac_ck",
	"cwk26m",
	"cwk26m"
};

static const chaw * const aud2dvd_pawents[] = {
	"a1sys_hp_ck",
	"a2sys_hp_ck"
};

static const chaw * const padmcwk_pawents[] = {
	"cwk26m",
	"univpww_d26",
	"univpww_d52",
	"univpww_d108",
	"univpww2_d8",
	"univpww2_d16",
	"univpww2_d32"
};

static const chaw * const aud_mux_pawents[] = {
	"cwk26m",
	"aud1pww_98m_ck",
	"aud2pww_90m_ck",
	"hadds2pww_98m",
	"audio_ext1_ck",
	"audio_ext2_ck"
};

static const chaw * const aud_swc_pawents[] = {
	"aud_mux1_sew",
	"aud_mux2_sew"
};

static const chaw * const cpu_pawents[] = {
	"cwk26m",
	"awmpww",
	"mainpww",
	"mmpww"
};

static const stwuct mtk_composite cpu_muxes[] __initconst = {
	MUX(CWK_INFWA_CPUSEW, "infwa_cpu_sew", cpu_pawents, 0x0000, 2, 2),
};

static const stwuct mtk_composite top_muxes[] = {
	MUX_GATE_FWAGS(CWK_TOP_AXI_SEW, "axi_sew", axi_pawents,
		0x0040, 0, 3, 7, CWK_IS_CWITICAW),
	MUX_GATE_FWAGS(CWK_TOP_MEM_SEW, "mem_sew", mem_pawents,
		0x0040, 8, 1, 15, CWK_IS_CWITICAW),
	MUX_GATE_FWAGS(CWK_TOP_DDWPHYCFG_SEW, "ddwphycfg_sew",
		ddwphycfg_pawents, 0x0040, 16, 1, 23, CWK_IS_CWITICAW),
	MUX_GATE(CWK_TOP_MM_SEW, "mm_sew", mm_pawents,
		0x0040, 24, 3, 31),

	MUX_GATE(CWK_TOP_PWM_SEW, "pwm_sew", pwm_pawents,
		0x0050, 0, 2, 7),
	MUX_GATE(CWK_TOP_VDEC_SEW, "vdec_sew", vdec_pawents,
		0x0050, 8, 4, 15),
	MUX_GATE(CWK_TOP_MFG_SEW, "mfg_sew", mfg_pawents,
		0x0050, 16, 3, 23),
	MUX_GATE(CWK_TOP_CAMTG_SEW, "camtg_sew", camtg_pawents,
		0x0050, 24, 3, 31),
	MUX_GATE(CWK_TOP_UAWT_SEW, "uawt_sew", uawt_pawents,
		0x0060, 0, 1, 7),

	MUX_GATE(CWK_TOP_SPI0_SEW, "spi0_sew", spi_pawents,
		0x0060, 8, 3, 15),
	MUX_GATE(CWK_TOP_USB20_SEW, "usb20_sew", usb20_pawents,
		0x0060, 16, 2, 23),
	MUX_GATE(CWK_TOP_MSDC30_0_SEW, "msdc30_0_sew", msdc30_pawents,
		0x0060, 24, 3, 31),

	MUX_GATE(CWK_TOP_MSDC30_1_SEW, "msdc30_1_sew", msdc30_pawents,
		0x0070, 0, 3, 7),
	MUX_GATE(CWK_TOP_MSDC30_2_SEW, "msdc30_2_sew", msdc30_pawents,
		0x0070, 8, 3, 15),
	MUX_GATE(CWK_TOP_AUDIO_SEW, "audio_sew", msdc30_pawents,
		0x0070, 16, 1, 23),
	MUX_GATE(CWK_TOP_AUDINTBUS_SEW, "aud_intbus_sew", aud_intbus_pawents,
		0x0070, 24, 3, 31),

	MUX_GATE(CWK_TOP_PMICSPI_SEW, "pmicspi_sew", pmicspi_pawents,
		0x0080, 0, 4, 7),
	MUX_GATE(CWK_TOP_SCP_SEW, "scp_sew", scp_pawents,
		0x0080, 8, 2, 15),
	MUX_GATE(CWK_TOP_DPI0_SEW, "dpi0_sew", dpi0_pawents,
		0x0080, 16, 3, 23),
	MUX_GATE_FWAGS_2(CWK_TOP_DPI1_SEW, "dpi1_sew", dpi1_pawents,
		0x0080, 24, 2, 31, 0, CWK_MUX_WOUND_CWOSEST),

	MUX_GATE(CWK_TOP_TVE_SEW, "tve_sew", tve_pawents,
		0x0090, 0, 3, 7),
	MUX_GATE(CWK_TOP_HDMI_SEW, "hdmi_sew", hdmi_pawents,
		0x0090, 8, 2, 15),
	MUX_GATE(CWK_TOP_APWW_SEW, "apww_sew", apww_pawents,
		0x0090, 16, 3, 23),

	MUX_GATE_FWAGS(CWK_TOP_WTC_SEW, "wtc_sew", wtc_pawents,
		0x00A0, 0, 2, 7, CWK_IS_CWITICAW),
	MUX_GATE(CWK_TOP_NFI2X_SEW, "nfi2x_sew", nfi2x_pawents,
		0x00A0, 8, 3, 15),
	MUX_GATE(CWK_TOP_EMMC_HCWK_SEW, "emmc_hcwk_sew", emmc_hcwk_pawents,
		0x00A0, 24, 2, 31),

	MUX_GATE(CWK_TOP_FWASH_SEW, "fwash_sew", fwash_pawents,
		0x00B0, 0, 3, 7),
	MUX_GATE(CWK_TOP_DI_SEW, "di_sew", di_pawents,
		0x00B0, 8, 2, 15),
	MUX_GATE(CWK_TOP_NW_SEW, "nw_sew", nw_osd_pawents,
		0x00B0, 16, 3, 23),
	MUX_GATE(CWK_TOP_OSD_SEW, "osd_sew", nw_osd_pawents,
		0x00B0, 24, 3, 31),

	MUX_GATE(CWK_TOP_HDMIWX_BIST_SEW, "hdmiwx_bist_sew",
		hdmiwx_bist_pawents, 0x00C0, 0, 3, 7),
	MUX_GATE(CWK_TOP_INTDIW_SEW, "intdiw_sew", intdiw_pawents,
		0x00C0, 8, 2, 15),
	MUX_GATE(CWK_TOP_ASM_I_SEW, "asm_i_sew", asm_pawents,
		0x00C0, 16, 2, 23),
	MUX_GATE(CWK_TOP_ASM_M_SEW, "asm_m_sew", asm_pawents,
		0x00C0, 24, 3, 31),

	MUX_GATE(CWK_TOP_ASM_H_SEW, "asm_h_sew", asm_pawents,
		0x00D0, 0, 2, 7),
	MUX_GATE(CWK_TOP_MS_CAWD_SEW, "ms_cawd_sew", ms_cawd_pawents,
		0x00D0, 16, 2, 23),
	MUX_GATE(CWK_TOP_ETHIF_SEW, "ethif_sew", ethif_pawents,
		0x00D0, 24, 3, 31),

	MUX_GATE(CWK_TOP_HDMIWX26_24_SEW, "hdmiwx26_24_sew", hdmiwx_pawents,
		0x00E0, 0, 1, 7),
	MUX_GATE(CWK_TOP_MSDC30_3_SEW, "msdc30_3_sew", msdc30_pawents,
		0x00E0, 8, 3, 15),
	MUX_GATE(CWK_TOP_CMSYS_SEW, "cmsys_sew", cmsys_pawents,
		0x00E0, 16, 4, 23),

	MUX_GATE(CWK_TOP_SPI1_SEW, "spi2_sew", spi_pawents,
		0x00E0, 24, 3, 31),
	MUX_GATE(CWK_TOP_SPI2_SEW, "spi1_sew", spi_pawents,
		0x00F0, 0, 3, 7),
	MUX_GATE(CWK_TOP_8BDAC_SEW, "8bdac_sew", cwk_8bdac_pawents,
		0x00F0, 8, 2, 15),
	MUX_GATE(CWK_TOP_AUD2DVD_SEW, "aud2dvd_sew", aud2dvd_pawents,
		0x00F0, 16, 1, 23),

	MUX(CWK_TOP_PADMCWK_SEW, "padmcwk_sew", padmcwk_pawents,
		0x0100, 0, 3),

	MUX(CWK_TOP_AUD_MUX1_SEW, "aud_mux1_sew", aud_mux_pawents,
		0x012c, 0, 3),
	MUX(CWK_TOP_AUD_MUX2_SEW, "aud_mux2_sew", aud_mux_pawents,
		0x012c, 3, 3),
	MUX(CWK_TOP_AUDPWW_MUX_SEW, "audpww_sew", aud_mux_pawents,
		0x012c, 6, 3),
	MUX_GATE(CWK_TOP_AUD_K1_SWC_SEW, "aud_k1_swc_sew", aud_swc_pawents,
		0x012c, 15, 1, 23),
	MUX_GATE(CWK_TOP_AUD_K2_SWC_SEW, "aud_k2_swc_sew", aud_swc_pawents,
		0x012c, 16, 1, 24),
	MUX_GATE(CWK_TOP_AUD_K3_SWC_SEW, "aud_k3_swc_sew", aud_swc_pawents,
		0x012c, 17, 1, 25),
	MUX_GATE(CWK_TOP_AUD_K4_SWC_SEW, "aud_k4_swc_sew", aud_swc_pawents,
		0x012c, 18, 1, 26),
	MUX_GATE(CWK_TOP_AUD_K5_SWC_SEW, "aud_k5_swc_sew", aud_swc_pawents,
		0x012c, 19, 1, 27),
	MUX_GATE(CWK_TOP_AUD_K6_SWC_SEW, "aud_k6_swc_sew", aud_swc_pawents,
		0x012c, 20, 1, 28),
};

static const stwuct mtk_cwk_dividew top_adj_divs[] = {
	DIV_ADJ(CWK_TOP_AUD_EXTCK1_DIV, "audio_ext1_ck", "aud_ext1",
		0x0120, 0, 8),
	DIV_ADJ(CWK_TOP_AUD_EXTCK2_DIV, "audio_ext2_ck", "aud_ext2",
		0x0120, 8, 8),
	DIV_ADJ(CWK_TOP_AUD_MUX1_DIV, "aud_mux1_div", "aud_mux1_sew",
		0x0120, 16, 8),
	DIV_ADJ(CWK_TOP_AUD_MUX2_DIV, "aud_mux2_div", "aud_mux2_sew",
		0x0120, 24, 8),
	DIV_ADJ(CWK_TOP_AUD_K1_SWC_DIV, "aud_k1_swc_div", "aud_k1_swc_sew",
		0x0124, 0, 8),
	DIV_ADJ(CWK_TOP_AUD_K2_SWC_DIV, "aud_k2_swc_div", "aud_k2_swc_sew",
		0x0124, 8, 8),
	DIV_ADJ(CWK_TOP_AUD_K3_SWC_DIV, "aud_k3_swc_div", "aud_k3_swc_sew",
		0x0124, 16, 8),
	DIV_ADJ(CWK_TOP_AUD_K4_SWC_DIV, "aud_k4_swc_div", "aud_k4_swc_sew",
		0x0124, 24, 8),
	DIV_ADJ(CWK_TOP_AUD_K5_SWC_DIV, "aud_k5_swc_div", "aud_k5_swc_sew",
		0x0128, 0, 8),
	DIV_ADJ(CWK_TOP_AUD_K6_SWC_DIV, "aud_k6_swc_div", "aud_k6_swc_sew",
		0x0128, 8, 8),
};

static const stwuct mtk_gate_wegs top_aud_cg_wegs = {
	.sta_ofs = 0x012C,
};

#define GATE_TOP_AUD(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &top_aud_cg_wegs, _shift, &mtk_cwk_gate_ops_no_setcww)

static const stwuct mtk_gate top_cwks[] = {
	GATE_TOP_AUD(CWK_TOP_AUD_48K_TIMING, "a1sys_hp_ck", "aud_mux1_div",
		21),
	GATE_TOP_AUD(CWK_TOP_AUD_44K_TIMING, "a2sys_hp_ck", "aud_mux2_div",
		22),
	GATE_TOP_AUD(CWK_TOP_AUD_I2S1_MCWK, "aud_i2s1_mcwk", "aud_k1_swc_div",
		23),
	GATE_TOP_AUD(CWK_TOP_AUD_I2S2_MCWK, "aud_i2s2_mcwk", "aud_k2_swc_div",
		24),
	GATE_TOP_AUD(CWK_TOP_AUD_I2S3_MCWK, "aud_i2s3_mcwk", "aud_k3_swc_div",
		25),
	GATE_TOP_AUD(CWK_TOP_AUD_I2S4_MCWK, "aud_i2s4_mcwk", "aud_k4_swc_div",
		26),
	GATE_TOP_AUD(CWK_TOP_AUD_I2S5_MCWK, "aud_i2s5_mcwk", "aud_k5_swc_div",
		27),
	GATE_TOP_AUD(CWK_TOP_AUD_I2S6_MCWK, "aud_i2s6_mcwk", "aud_k6_swc_div",
		28),
};

static int mtk_topckgen_init(stwuct pwatfowm_device *pdev)
{
	stwuct cwk_hw_oneceww_data *cwk_data;
	void __iomem *base;
	stwuct device_node *node = pdev->dev.of_node;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	cwk_data = mtk_awwoc_cwk_data(CWK_TOP_NW);
	if (!cwk_data)
		wetuwn -ENOMEM;

	mtk_cwk_wegistew_fixed_cwks(top_fixed_cwks, AWWAY_SIZE(top_fixed_cwks),
								cwk_data);

	mtk_cwk_wegistew_factows(top_fixed_divs, AWWAY_SIZE(top_fixed_divs),
								cwk_data);

	mtk_cwk_wegistew_composites(&pdev->dev, top_muxes,
				    AWWAY_SIZE(top_muxes), base,
				    &mt2701_cwk_wock, cwk_data);

	mtk_cwk_wegistew_dividews(&pdev->dev, top_adj_divs, AWWAY_SIZE(top_adj_divs),
				base, &mt2701_cwk_wock, cwk_data);

	mtk_cwk_wegistew_gates(&pdev->dev, node, top_cwks,
			       AWWAY_SIZE(top_cwks), cwk_data);

	wetuwn of_cwk_add_hw_pwovidew(node, of_cwk_hw_oneceww_get, cwk_data);
}

static const stwuct mtk_gate_wegs infwa_cg_wegs = {
	.set_ofs = 0x0040,
	.cww_ofs = 0x0044,
	.sta_ofs = 0x0048,
};

#define GATE_ICG(_id, _name, _pawent, _shift)				\
	GATE_MTK(_id, _name, _pawent, &infwa_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

static const stwuct mtk_gate infwa_cwks[] = {
	GATE_ICG(CWK_INFWA_DBG, "dbgcwk", "axi_sew", 0),
	GATE_ICG(CWK_INFWA_SMI, "smi_ck", "mm_sew", 1),
	GATE_ICG(CWK_INFWA_QAXI_CM4, "cm4_ck", "axi_sew", 2),
	GATE_ICG(CWK_INFWA_AUD_SPWIN_B, "audio_spwin_bck", "hadds2pww_294m", 4),
	GATE_ICG(CWK_INFWA_AUDIO, "audio_ck", "cwk26m", 5),
	GATE_ICG(CWK_INFWA_EFUSE, "efuse_ck", "cwk26m", 6),
	GATE_ICG(CWK_INFWA_W2C_SWAM, "w2c_swam_ck", "mm_sew", 7),
	GATE_ICG(CWK_INFWA_M4U, "m4u_ck", "mem_sew", 8),
	GATE_ICG(CWK_INFWA_CONNMCU, "connsys_bus", "wbg_dig_ck_416m", 12),
	GATE_ICG(CWK_INFWA_TWNG, "twng_ck", "axi_sew", 13),
	GATE_ICG(CWK_INFWA_WAMBUFIF, "wambufif_ck", "mem_sew", 14),
	GATE_ICG(CWK_INFWA_CPUM, "cpum_ck", "mem_sew", 15),
	GATE_ICG(CWK_INFWA_KP, "kp_ck", "axi_sew", 16),
	GATE_ICG(CWK_INFWA_CEC, "cec_ck", "wtc_sew", 18),
	GATE_ICG(CWK_INFWA_IWWX, "iwwx_ck", "axi_sew", 19),
	GATE_ICG(CWK_INFWA_PMICSPI, "pmicspi_ck", "pmicspi_sew", 22),
	GATE_ICG(CWK_INFWA_PMICWWAP, "pmicwwap_ck", "axi_sew", 23),
	GATE_ICG(CWK_INFWA_DDCCI, "ddcci_ck", "axi_sew", 24),
};

static const stwuct mtk_fixed_factow infwa_fixed_divs[] = {
	FACTOW(CWK_INFWA_CWK_13M, "cwk13m", "cwk26m", 1, 2),
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
	},
};

static stwuct cwk_hw_oneceww_data *infwa_cwk_data;

static void __init mtk_infwasys_init_eawwy(stwuct device_node *node)
{
	int w, i;

	if (!infwa_cwk_data) {
		infwa_cwk_data = mtk_awwoc_cwk_data(CWK_INFWA_NW);
		if (!infwa_cwk_data)
			wetuwn;

		fow (i = 0; i < CWK_INFWA_NW; i++)
			infwa_cwk_data->hws[i] = EWW_PTW(-EPWOBE_DEFEW);
	}

	mtk_cwk_wegistew_factows(infwa_fixed_divs, AWWAY_SIZE(infwa_fixed_divs),
						infwa_cwk_data);

	mtk_cwk_wegistew_cpumuxes(NUWW, node, cpu_muxes, AWWAY_SIZE(cpu_muxes),
				  infwa_cwk_data);

	w = of_cwk_add_hw_pwovidew(node, of_cwk_hw_oneceww_get,
				   infwa_cwk_data);
	if (w)
		pw_eww("%s(): couwd not wegistew cwock pwovidew: %d\n",
			__func__, w);
}
CWK_OF_DECWAWE_DWIVEW(mtk_infwa, "mediatek,mt2701-infwacfg",
			mtk_infwasys_init_eawwy);

static int mtk_infwasys_init(stwuct pwatfowm_device *pdev)
{
	int w, i;
	stwuct device_node *node = pdev->dev.of_node;

	if (!infwa_cwk_data) {
		infwa_cwk_data = mtk_awwoc_cwk_data(CWK_INFWA_NW);
		if (!infwa_cwk_data)
			wetuwn -ENOMEM;
	} ewse {
		fow (i = 0; i < CWK_INFWA_NW; i++) {
			if (infwa_cwk_data->hws[i] == EWW_PTW(-EPWOBE_DEFEW))
				infwa_cwk_data->hws[i] = EWW_PTW(-ENOENT);
		}
	}

	mtk_cwk_wegistew_gates(&pdev->dev, node, infwa_cwks,
			       AWWAY_SIZE(infwa_cwks), infwa_cwk_data);
	mtk_cwk_wegistew_factows(infwa_fixed_divs, AWWAY_SIZE(infwa_fixed_divs),
						infwa_cwk_data);

	w = of_cwk_add_hw_pwovidew(node, of_cwk_hw_oneceww_get,
				   infwa_cwk_data);
	if (w)
		wetuwn w;

	mtk_wegistew_weset_contwowwew_with_dev(&pdev->dev, &cwk_wst_desc[0]);

	wetuwn 0;
}

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

#define GATE_PEWI0(_id, _name, _pawent, _shift)				\
	GATE_MTK(_id, _name, _pawent, &pewi0_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

#define GATE_PEWI1(_id, _name, _pawent, _shift)				\
	GATE_MTK(_id, _name, _pawent, &pewi1_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

static const stwuct mtk_gate pewi_cwks[] = {
	GATE_PEWI0(CWK_PEWI_USB0_MCU, "usb0_mcu_ck", "axi_sew", 31),
	GATE_PEWI0(CWK_PEWI_ETH, "eth_ck", "cwk26m", 30),
	GATE_PEWI0(CWK_PEWI_SPI0, "spi0_ck", "spi0_sew", 29),
	GATE_PEWI0(CWK_PEWI_AUXADC, "auxadc_ck", "cwk26m", 28),
	GATE_PEWI0(CWK_PEWI_I2C3, "i2c3_ck", "cwk26m", 27),
	GATE_PEWI0(CWK_PEWI_I2C2, "i2c2_ck", "axi_sew", 26),
	GATE_PEWI0(CWK_PEWI_I2C1, "i2c1_ck", "axi_sew", 25),
	GATE_PEWI0(CWK_PEWI_I2C0, "i2c0_ck", "axi_sew", 24),
	GATE_PEWI0(CWK_PEWI_BTIF, "bitif_ck", "axi_sew", 23),
	GATE_PEWI0(CWK_PEWI_UAWT3, "uawt3_ck", "axi_sew", 22),
	GATE_PEWI0(CWK_PEWI_UAWT2, "uawt2_ck", "axi_sew", 21),
	GATE_PEWI0(CWK_PEWI_UAWT1, "uawt1_ck", "axi_sew", 20),
	GATE_PEWI0(CWK_PEWI_UAWT0, "uawt0_ck", "axi_sew", 19),
	GATE_PEWI0(CWK_PEWI_NWI, "nwi_ck", "axi_sew", 18),
	GATE_PEWI0(CWK_PEWI_MSDC50_3, "msdc50_3_ck", "emmc_hcwk_sew", 17),
	GATE_PEWI0(CWK_PEWI_MSDC30_3, "msdc30_3_ck", "msdc30_3_sew", 16),
	GATE_PEWI0(CWK_PEWI_MSDC30_2, "msdc30_2_ck", "msdc30_2_sew", 15),
	GATE_PEWI0(CWK_PEWI_MSDC30_1, "msdc30_1_ck", "msdc30_1_sew", 14),
	GATE_PEWI0(CWK_PEWI_MSDC30_0, "msdc30_0_ck", "msdc30_0_sew", 13),
	GATE_PEWI0(CWK_PEWI_AP_DMA, "ap_dma_ck", "axi_sew", 12),
	GATE_PEWI0(CWK_PEWI_USB1, "usb1_ck", "usb20_sew", 11),
	GATE_PEWI0(CWK_PEWI_USB0, "usb0_ck", "usb20_sew", 10),
	GATE_PEWI0(CWK_PEWI_PWM, "pwm_ck", "axi_sew", 9),
	GATE_PEWI0(CWK_PEWI_PWM7, "pwm7_ck", "axisew_d4", 8),
	GATE_PEWI0(CWK_PEWI_PWM6, "pwm6_ck", "axisew_d4", 7),
	GATE_PEWI0(CWK_PEWI_PWM5, "pwm5_ck", "axisew_d4", 6),
	GATE_PEWI0(CWK_PEWI_PWM4, "pwm4_ck", "axisew_d4", 5),
	GATE_PEWI0(CWK_PEWI_PWM3, "pwm3_ck", "axisew_d4", 4),
	GATE_PEWI0(CWK_PEWI_PWM2, "pwm2_ck", "axisew_d4", 3),
	GATE_PEWI0(CWK_PEWI_PWM1, "pwm1_ck", "axisew_d4", 2),
	GATE_PEWI0(CWK_PEWI_THEWM, "thewm_ck", "axi_sew", 1),
	GATE_PEWI0(CWK_PEWI_NFI, "nfi_ck", "nfi2x_sew", 0),

	GATE_PEWI1(CWK_PEWI_FCI, "fci_ck", "ms_cawd_sew", 11),
	GATE_PEWI1(CWK_PEWI_SPI2, "spi2_ck", "spi2_sew", 10),
	GATE_PEWI1(CWK_PEWI_SPI1, "spi1_ck", "spi1_sew", 9),
	GATE_PEWI1(CWK_PEWI_HOST89_DVD, "host89_dvd_ck", "aud2dvd_sew", 8),
	GATE_PEWI1(CWK_PEWI_HOST89_SPI, "host89_spi_ck", "spi0_sew", 7),
	GATE_PEWI1(CWK_PEWI_HOST89_INT, "host89_int_ck", "axi_sew", 6),
	GATE_PEWI1(CWK_PEWI_FWASH, "fwash_ck", "nfi2x_sew", 5),
	GATE_PEWI1(CWK_PEWI_NFI_PAD, "nfi_pad_ck", "nfi1x_pad", 4),
	GATE_PEWI1(CWK_PEWI_NFI_ECC, "nfi_ecc_ck", "nfi1x_pad", 3),
	GATE_PEWI1(CWK_PEWI_GCPU, "gcpu_ck", "axi_sew", 2),
	GATE_PEWI1(CWK_PEWI_USB_SWV, "usbswv_ck", "axi_sew", 1),
	GATE_PEWI1(CWK_PEWI_USB1_MCU, "usb1_mcu_ck", "axi_sew", 0),
};

static const chaw * const uawt_ck_sew_pawents[] = {
	"cwk26m",
	"uawt_sew",
};

static const stwuct mtk_composite pewi_muxs[] = {
	MUX(CWK_PEWI_UAWT0_SEW, "uawt0_ck_sew", uawt_ck_sew_pawents,
		0x40c, 0, 1),
	MUX(CWK_PEWI_UAWT1_SEW, "uawt1_ck_sew", uawt_ck_sew_pawents,
		0x40c, 1, 1),
	MUX(CWK_PEWI_UAWT2_SEW, "uawt2_ck_sew", uawt_ck_sew_pawents,
		0x40c, 2, 1),
	MUX(CWK_PEWI_UAWT3_SEW, "uawt3_ck_sew", uawt_ck_sew_pawents,
		0x40c, 3, 1),
};

static int mtk_pewicfg_init(stwuct pwatfowm_device *pdev)
{
	stwuct cwk_hw_oneceww_data *cwk_data;
	void __iomem *base;
	int w;
	stwuct device_node *node = pdev->dev.of_node;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	cwk_data = mtk_awwoc_cwk_data(CWK_PEWI_NW);
	if (!cwk_data)
		wetuwn -ENOMEM;

	mtk_cwk_wegistew_gates(&pdev->dev, node, pewi_cwks,
			       AWWAY_SIZE(pewi_cwks), cwk_data);

	mtk_cwk_wegistew_composites(&pdev->dev, pewi_muxs,
				    AWWAY_SIZE(pewi_muxs), base,
				    &mt2701_cwk_wock, cwk_data);

	w = of_cwk_add_hw_pwovidew(node, of_cwk_hw_oneceww_get, cwk_data);
	if (w)
		wetuwn w;

	mtk_wegistew_weset_contwowwew_with_dev(&pdev->dev, &cwk_wst_desc[1]);

	wetuwn 0;
}

#define MT8590_PWW_FMAX		(2000 * MHZ)
#define CON0_MT8590_WST_BAW	BIT(27)

#define PWW(_id, _name, _weg, _pww_weg, _en_mask, _fwags, _pcwbits, _pd_weg, \
			_pd_shift, _tunew_weg, _pcw_weg, _pcw_shift) {	\
		.id = _id,						\
		.name = _name,						\
		.weg = _weg,						\
		.pww_weg = _pww_weg,					\
		.en_mask = _en_mask,					\
		.fwags = _fwags,					\
		.wst_baw_mask = CON0_MT8590_WST_BAW,			\
		.fmax = MT8590_PWW_FMAX,				\
		.pcwbits = _pcwbits,					\
		.pd_weg = _pd_weg,					\
		.pd_shift = _pd_shift,					\
		.tunew_weg = _tunew_weg,				\
		.pcw_weg = _pcw_weg,					\
		.pcw_shift = _pcw_shift,				\
	}

static const stwuct mtk_pww_data apmixed_pwws[] = {
	PWW(CWK_APMIXED_AWMPWW, "awmpww", 0x200, 0x20c, 0x80000000,
			PWW_AO, 21, 0x204, 24, 0x0, 0x204, 0),
	PWW(CWK_APMIXED_MAINPWW, "mainpww", 0x210, 0x21c, 0xf0000000,
		  HAVE_WST_BAW, 21, 0x210, 4, 0x0, 0x214, 0),
	PWW(CWK_APMIXED_UNIVPWW, "univpww", 0x220, 0x22c, 0xf3000000,
		  HAVE_WST_BAW, 7, 0x220, 4, 0x0, 0x224, 14),
	PWW(CWK_APMIXED_MMPWW, "mmpww", 0x230, 0x23c, 0, 0,
				21, 0x230, 4, 0x0, 0x234, 0),
	PWW(CWK_APMIXED_MSDCPWW, "msdcpww", 0x240, 0x24c, 0x00000001, 0,
				21, 0x240, 4, 0x0, 0x244, 0),
	PWW(CWK_APMIXED_TVDPWW, "tvdpww", 0x250, 0x25c, 0x00000001, 0,
				21, 0x250, 4, 0x0, 0x254, 0),
	PWW(CWK_APMIXED_AUD1PWW, "aud1pww", 0x270, 0x27c, 0x00000001, 0,
				31, 0x270, 4, 0x0, 0x274, 0),
	PWW(CWK_APMIXED_TWGPWW, "twgpww", 0x280, 0x28c, 0x00000001, 0,
				31, 0x280, 4, 0x0, 0x284, 0),
	PWW(CWK_APMIXED_ETHPWW, "ethpww", 0x290, 0x29c, 0x00000001, 0,
				31, 0x290, 4, 0x0, 0x294, 0),
	PWW(CWK_APMIXED_VDECPWW, "vdecpww", 0x2a0, 0x2ac, 0x00000001, 0,
				31, 0x2a0, 4, 0x0, 0x2a4, 0),
	PWW(CWK_APMIXED_HADDS2PWW, "hadds2pww", 0x2b0, 0x2bc, 0x00000001, 0,
				31, 0x2b0, 4, 0x0, 0x2b4, 0),
	PWW(CWK_APMIXED_AUD2PWW, "aud2pww", 0x2c0, 0x2cc, 0x00000001, 0,
				31, 0x2c0, 4, 0x0, 0x2c4, 0),
	PWW(CWK_APMIXED_TVD2PWW, "tvd2pww", 0x2d0, 0x2dc, 0x00000001, 0,
				21, 0x2d0, 4, 0x0, 0x2d4, 0),
};

static const stwuct mtk_fixed_factow apmixed_fixed_divs[] = {
	FACTOW(CWK_APMIXED_HDMI_WEF, "hdmi_wef", "tvdpww", 1, 1),
};

static int mtk_apmixedsys_init(stwuct pwatfowm_device *pdev)
{
	stwuct cwk_hw_oneceww_data *cwk_data;
	stwuct device_node *node = pdev->dev.of_node;

	cwk_data = mtk_awwoc_cwk_data(CWK_APMIXED_NW);
	if (!cwk_data)
		wetuwn -ENOMEM;

	mtk_cwk_wegistew_pwws(node, apmixed_pwws, AWWAY_SIZE(apmixed_pwws),
								cwk_data);
	mtk_cwk_wegistew_factows(apmixed_fixed_divs, AWWAY_SIZE(apmixed_fixed_divs),
								cwk_data);

	wetuwn of_cwk_add_hw_pwovidew(node, of_cwk_hw_oneceww_get, cwk_data);
}

static const stwuct of_device_id of_match_cwk_mt2701[] = {
	{
		.compatibwe = "mediatek,mt2701-topckgen",
		.data = mtk_topckgen_init,
	}, {
		.compatibwe = "mediatek,mt2701-infwacfg",
		.data = mtk_infwasys_init,
	}, {
		.compatibwe = "mediatek,mt2701-pewicfg",
		.data = mtk_pewicfg_init,
	}, {
		.compatibwe = "mediatek,mt2701-apmixedsys",
		.data = mtk_apmixedsys_init,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt2701);

static int cwk_mt2701_pwobe(stwuct pwatfowm_device *pdev)
{
	int (*cwk_init)(stwuct pwatfowm_device *);
	int w;

	cwk_init = of_device_get_match_data(&pdev->dev);
	if (!cwk_init)
		wetuwn -EINVAW;

	w = cwk_init(pdev);
	if (w)
		dev_eww(&pdev->dev,
			"couwd not wegistew cwock pwovidew: %s: %d\n",
			pdev->name, w);

	wetuwn w;
}

static stwuct pwatfowm_dwivew cwk_mt2701_dwv = {
	.pwobe = cwk_mt2701_pwobe,
	.dwivew = {
		.name = "cwk-mt2701",
		.of_match_tabwe = of_match_cwk_mt2701,
	},
};

static int __init cwk_mt2701_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&cwk_mt2701_dwv);
}

awch_initcaww(cwk_mt2701_init);
MODUWE_WICENSE("GPW");
