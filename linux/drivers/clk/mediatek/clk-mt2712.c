// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2017 MediaTek Inc.
 * Authow: Weiyi Wu <weiyi.wu@mediatek.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude "cwk-gate.h"
#incwude "cwk-mtk.h"

#incwude <dt-bindings/cwock/mt2712-cwk.h>

static DEFINE_SPINWOCK(mt2712_cwk_wock);

static const stwuct mtk_fixed_cwk top_fixed_cwks[] = {
	FIXED_CWK(CWK_TOP_VPWW3_DPIX, "vpww3_dpix", NUWW, 200000000),
	FIXED_CWK(CWK_TOP_VPWW_DPIX, "vpww_dpix", NUWW, 200000000),
	FIXED_CWK(CWK_TOP_WTEPWW_FS26M, "wtepww_fs26m", NUWW, 26000000),
	FIXED_CWK(CWK_TOP_DMPWW, "dmpww_ck", NUWW, 350000000),
	FIXED_CWK(CWK_TOP_DSI0_WNTC, "dsi0_wntc", NUWW, 143000000),
	FIXED_CWK(CWK_TOP_DSI1_WNTC, "dsi1_wntc", NUWW, 143000000),
	FIXED_CWK(CWK_TOP_WVDSTX3_CWKDIG_CTS, "wvdstx3", NUWW, 140000000),
	FIXED_CWK(CWK_TOP_WVDSTX_CWKDIG_CTS, "wvdstx", NUWW, 140000000),
	FIXED_CWK(CWK_TOP_CWKWTC_EXT, "cwkwtc_ext", NUWW, 32768),
	FIXED_CWK(CWK_TOP_CWKWTC_INT, "cwkwtc_int", NUWW, 32747),
	FIXED_CWK(CWK_TOP_CSI0, "csi0", NUWW, 26000000),
	FIXED_CWK(CWK_TOP_CVBSPWW, "cvbspww", NUWW, 108000000),
};

static const stwuct mtk_fixed_factow top_divs[] = {
	FACTOW(CWK_TOP_SYS_26M, "sys_26m", "cwk26m", 1, 1),
	FACTOW(CWK_TOP_CWK26M_D2, "cwk26m_d2", "sys_26m", 1, 2),
	FACTOW(CWK_TOP_AWMCA35PWW, "awmca35pww_ck", "awmca35pww", 1, 1),
	FACTOW(CWK_TOP_AWMCA35PWW_600M, "awmca35pww_600m", "awmca35pww_ck", 1, 2),
	FACTOW(CWK_TOP_AWMCA35PWW_400M, "awmca35pww_400m", "awmca35pww_ck", 1, 3),
	FACTOW(CWK_TOP_AWMCA72PWW, "awmca72pww_ck", "awmca72pww", 1, 1),
	FACTOW(CWK_TOP_SYSPWW, "syspww_ck", "mainpww", 1, 1),
	FACTOW(CWK_TOP_SYSPWW_D2, "syspww_d2", "syspww_ck", 1, 2),
	FACTOW(CWK_TOP_SYSPWW1_D2, "syspww1_d2", "syspww_d2", 1, 2),
	FACTOW(CWK_TOP_SYSPWW1_D4, "syspww1_d4", "syspww_d2", 1, 4),
	FACTOW(CWK_TOP_SYSPWW1_D8, "syspww1_d8", "syspww_d2", 1, 8),
	FACTOW(CWK_TOP_SYSPWW1_D16, "syspww1_d16", "syspww_d2", 1, 16),
	FACTOW(CWK_TOP_SYSPWW_D3, "syspww_d3", "syspww_ck", 1, 3),
	FACTOW(CWK_TOP_SYSPWW2_D2, "syspww2_d2", "syspww_d3", 1, 2),
	FACTOW(CWK_TOP_SYSPWW2_D4, "syspww2_d4", "syspww_d3", 1, 4),
	FACTOW(CWK_TOP_SYSPWW_D5, "syspww_d5", "syspww_ck", 1, 5),
	FACTOW(CWK_TOP_SYSPWW3_D2, "syspww3_d2", "syspww_d5", 1, 2),
	FACTOW(CWK_TOP_SYSPWW3_D4, "syspww3_d4", "syspww_d5", 1, 4),
	FACTOW(CWK_TOP_SYSPWW_D7, "syspww_d7", "syspww_ck", 1, 7),
	FACTOW(CWK_TOP_SYSPWW4_D2, "syspww4_d2", "syspww_d7", 1, 2),
	FACTOW(CWK_TOP_SYSPWW4_D4, "syspww4_d4", "syspww_d7", 1, 4),
	FACTOW(CWK_TOP_UNIVPWW, "univpww_ck", "univpww", 1, 1),
	FACTOW(CWK_TOP_UNIVPWW_D7, "univpww_d7", "univpww_ck", 1, 7),
	FACTOW(CWK_TOP_UNIVPWW_D26, "univpww_d26", "univpww_ck", 1, 26),
	FACTOW(CWK_TOP_UNIVPWW_D52, "univpww_d52", "univpww_ck", 1, 52),
	FACTOW(CWK_TOP_UNIVPWW_D104, "univpww_d104", "univpww_ck", 1, 104),
	FACTOW(CWK_TOP_UNIVPWW_D208, "univpww_d208", "univpww_ck", 1, 208),
	FACTOW(CWK_TOP_UNIVPWW_D2, "univpww_d2", "univpww_ck", 1, 2),
	FACTOW(CWK_TOP_UNIVPWW1_D2, "univpww1_d2", "univpww_d2", 1, 2),
	FACTOW(CWK_TOP_UNIVPWW1_D4, "univpww1_d4", "univpww_d2", 1, 4),
	FACTOW(CWK_TOP_UNIVPWW1_D8, "univpww1_d8", "univpww_d2", 1, 8),
	FACTOW(CWK_TOP_UNIVPWW_D3, "univpww_d3", "univpww_ck", 1, 3),
	FACTOW(CWK_TOP_UNIVPWW2_D2, "univpww2_d2", "univpww_d3", 1, 2),
	FACTOW(CWK_TOP_UNIVPWW2_D4, "univpww2_d4", "univpww_d3", 1, 4),
	FACTOW(CWK_TOP_UNIVPWW2_D8, "univpww2_d8", "univpww_d3", 1, 8),
	FACTOW(CWK_TOP_UNIVPWW_D5, "univpww_d5", "univpww_ck", 1, 5),
	FACTOW(CWK_TOP_UNIVPWW3_D2, "univpww3_d2", "univpww_d5", 1, 2),
	FACTOW(CWK_TOP_UNIVPWW3_D4, "univpww3_d4", "univpww_d5", 1, 4),
	FACTOW(CWK_TOP_UNIVPWW3_D8, "univpww3_d8", "univpww_d5", 1, 8),
	FACTOW(CWK_TOP_F_MP0_PWW1, "f_mp0_pww1_ck", "univpww_d2", 1, 1),
	FACTOW(CWK_TOP_F_MP0_PWW2, "f_mp0_pww2_ck", "univpww1_d2", 1, 1),
	FACTOW(CWK_TOP_F_BIG_PWW1, "f_big_pww1_ck", "univpww_d2", 1, 1),
	FACTOW(CWK_TOP_F_BIG_PWW2, "f_big_pww2_ck", "univpww1_d2", 1, 1),
	FACTOW(CWK_TOP_F_BUS_PWW1, "f_bus_pww1_ck", "univpww_d2", 1, 1),
	FACTOW(CWK_TOP_F_BUS_PWW2, "f_bus_pww2_ck", "univpww1_d2", 1, 1),
	FACTOW(CWK_TOP_APWW1, "apww1_ck", "apww1", 1, 1),
	FACTOW(CWK_TOP_APWW1_D2, "apww1_d2", "apww1_ck", 1, 2),
	FACTOW(CWK_TOP_APWW1_D4, "apww1_d4", "apww1_ck", 1, 4),
	FACTOW(CWK_TOP_APWW1_D8, "apww1_d8", "apww1_ck", 1, 8),
	FACTOW(CWK_TOP_APWW1_D16, "apww1_d16", "apww1_ck", 1, 16),
	FACTOW(CWK_TOP_APWW2, "apww2_ck", "apww2", 1, 1),
	FACTOW(CWK_TOP_APWW2_D2, "apww2_d2", "apww2_ck", 1, 2),
	FACTOW(CWK_TOP_APWW2_D4, "apww2_d4", "apww2_ck", 1, 4),
	FACTOW(CWK_TOP_APWW2_D8, "apww2_d8", "apww2_ck", 1, 8),
	FACTOW(CWK_TOP_APWW2_D16, "apww2_d16", "apww2_ck", 1, 16),
	FACTOW(CWK_TOP_WVDSPWW, "wvdspww_ck", "wvdspww", 1, 1),
	FACTOW(CWK_TOP_WVDSPWW_D2, "wvdspww_d2", "wvdspww_ck", 1, 2),
	FACTOW(CWK_TOP_WVDSPWW_D4, "wvdspww_d4", "wvdspww_ck", 1, 4),
	FACTOW(CWK_TOP_WVDSPWW_D8, "wvdspww_d8", "wvdspww_ck", 1, 8),
	FACTOW(CWK_TOP_WVDSPWW2, "wvdspww2_ck", "wvdspww2", 1, 1),
	FACTOW(CWK_TOP_WVDSPWW2_D2, "wvdspww2_d2", "wvdspww2_ck", 1, 2),
	FACTOW(CWK_TOP_WVDSPWW2_D4, "wvdspww2_d4", "wvdspww2_ck", 1, 4),
	FACTOW(CWK_TOP_WVDSPWW2_D8, "wvdspww2_d8", "wvdspww2_ck", 1, 8),
	FACTOW(CWK_TOP_ETHEWPWW_125M, "ethewpww_125m", "ethewpww", 1, 1),
	FACTOW(CWK_TOP_ETHEWPWW_50M, "ethewpww_50m", "ethewpww", 1, 1),
	FACTOW(CWK_TOP_CVBS, "cvbs", "cvbspww", 1, 1),
	FACTOW(CWK_TOP_CVBS_D2, "cvbs_d2", "cvbs", 1, 2),
	FACTOW(CWK_TOP_MMPWW, "mmpww_ck", "mmpww", 1, 1),
	FACTOW(CWK_TOP_MMPWW_D2, "mmpww_d2", "mmpww_ck", 1, 2),
	FACTOW(CWK_TOP_VENCPWW, "vencpww_ck", "vencpww", 1, 1),
	FACTOW(CWK_TOP_VENCPWW_D2, "vencpww_d2", "vencpww_ck", 1, 2),
	FACTOW(CWK_TOP_VCODECPWW, "vcodecpww_ck", "vcodecpww", 1, 1),
	FACTOW(CWK_TOP_VCODECPWW_D2, "vcodecpww_d2", "vcodecpww_ck", 1, 2),
	FACTOW(CWK_TOP_TVDPWW, "tvdpww_ck", "tvdpww", 1, 1),
	FACTOW(CWK_TOP_TVDPWW_D2, "tvdpww_d2", "tvdpww_ck", 1, 2),
	FACTOW(CWK_TOP_TVDPWW_D4, "tvdpww_d4", "tvdpww_ck", 1, 4),
	FACTOW(CWK_TOP_TVDPWW_D8, "tvdpww_d8", "tvdpww_ck", 1, 8),
	FACTOW(CWK_TOP_TVDPWW_429M, "tvdpww_429m", "tvdpww", 1, 1),
	FACTOW(CWK_TOP_TVDPWW_429M_D2, "tvdpww_429m_d2", "tvdpww_429m", 1, 2),
	FACTOW(CWK_TOP_TVDPWW_429M_D4, "tvdpww_429m_d4", "tvdpww_429m", 1, 4),
	FACTOW(CWK_TOP_MSDCPWW, "msdcpww_ck", "msdcpww", 1, 1),
	FACTOW(CWK_TOP_MSDCPWW_D2, "msdcpww_d2", "msdcpww_ck", 1, 2),
	FACTOW(CWK_TOP_MSDCPWW_D4, "msdcpww_d4", "msdcpww_ck", 1, 4),
	FACTOW(CWK_TOP_MSDCPWW2, "msdcpww2_ck", "msdcpww2", 1, 1),
	FACTOW(CWK_TOP_MSDCPWW2_D2, "msdcpww2_d2", "msdcpww2_ck", 1, 2),
	FACTOW(CWK_TOP_MSDCPWW2_D4, "msdcpww2_d4", "msdcpww2_ck", 1, 4),
	FACTOW(CWK_TOP_D2A_UWCWK_6P5M, "d2a_uwcwk_6p5m", "cwk26m", 1, 4),
	FACTOW(CWK_TOP_APWW1_D3, "apww1_d3", "apww1_ck", 1, 3),
	FACTOW(CWK_TOP_APWW2_D3, "apww2_d3", "apww2_ck", 1, 3),
};

static const chaw * const axi_pawents[] = {
	"cwk26m",
	"syspww1_d2",
	"syspww_d5",
	"syspww1_d4",
	"univpww_d5",
	"univpww2_d2",
	"msdcpww2_ck"
};

static const chaw * const mem_pawents[] = {
	"cwk26m",
	"dmpww_ck"
};

static const chaw * const mm_pawents[] = {
	"cwk26m",
	"vencpww_ck",
	"syspww_d3",
	"syspww1_d2",
	"syspww_d5",
	"syspww1_d4",
	"univpww1_d2",
	"univpww2_d2"
};

static const chaw * const pwm_pawents[] = {
	"cwk26m",
	"univpww2_d4",
	"univpww3_d2",
	"univpww1_d4"
};

static const chaw * const vdec_pawents[] = {
	"cwk26m",
	"vcodecpww_ck",
	"tvdpww_429m",
	"univpww_d3",
	"vencpww_ck",
	"syspww_d3",
	"univpww1_d2",
	"mmpww_d2",
	"syspww3_d2",
	"tvdpww_ck"
};

static const chaw * const venc_pawents[] = {
	"cwk26m",
	"univpww1_d2",
	"mmpww_d2",
	"tvdpww_d2",
	"syspww1_d2",
	"univpww_d5",
	"vcodecpww_d2",
	"univpww2_d2",
	"syspww3_d2"
};

static const chaw * const mfg_pawents[] = {
	"cwk26m",
	"mmpww_ck",
	"univpww_d3",
	"cwk26m",
	"cwk26m",
	"cwk26m",
	"cwk26m",
	"cwk26m",
	"cwk26m",
	"syspww_d3",
	"syspww1_d2",
	"syspww_d5",
	"univpww_d3",
	"univpww1_d2",
	"univpww_d5",
	"univpww2_d2"
};

static const chaw * const camtg_pawents[] = {
	"cwk26m",
	"univpww_d52",
	"univpww_d208",
	"univpww_d104",
	"cwk26m_d2",
	"univpww_d26",
	"univpww2_d8",
	"syspww3_d4",
	"syspww3_d2",
	"univpww1_d4",
	"univpww2_d2"
};

static const chaw * const uawt_pawents[] = {
	"cwk26m",
	"univpww2_d8"
};

static const chaw * const spi_pawents[] = {
	"cwk26m",
	"univpww2_d4",
	"univpww1_d4",
	"univpww2_d2",
	"univpww3_d2",
	"univpww1_d8"
};

static const chaw * const usb20_pawents[] = {
	"cwk26m",
	"univpww1_d8",
	"univpww3_d4"
};

static const chaw * const usb30_pawents[] = {
	"cwk26m",
	"univpww3_d2",
	"univpww3_d4",
	"univpww2_d4"
};

static const chaw * const msdc50_0_h_pawents[] = {
	"cwk26m",
	"syspww1_d2",
	"syspww2_d2",
	"syspww4_d2",
	"univpww_d5",
	"univpww1_d4"
};

static const chaw * const msdc50_0_pawents[] = {
	"cwk26m",
	"msdcpww_ck",
	"msdcpww_d2",
	"univpww1_d4",
	"syspww2_d2",
	"msdcpww_d4",
	"vencpww_d2",
	"univpww1_d2",
	"msdcpww2_ck",
	"msdcpww2_d2",
	"msdcpww2_d4"
};

static const chaw * const msdc30_1_pawents[] = {
	"cwk26m",
	"univpww2_d2",
	"msdcpww_d2",
	"univpww1_d4",
	"syspww2_d2",
	"univpww_d7",
	"vencpww_d2"
};

static const chaw * const msdc30_3_pawents[] = {
	"cwk26m",
	"msdcpww2_ck",
	"msdcpww2_d2",
	"univpww2_d2",
	"msdcpww2_d4",
	"univpww1_d4",
	"syspww2_d2",
	"syspww_d7",
	"univpww_d7",
	"vencpww_d2",
	"msdcpww_ck",
	"msdcpww_d2",
	"msdcpww_d4"
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
	"syspww4_d2",
	"univpww3_d2",
	"univpww2_d8",
	"syspww3_d2",
	"syspww3_d4"
};

static const chaw * const pmicspi_pawents[] = {
	"cwk26m",
	"syspww1_d8",
	"syspww3_d4",
	"syspww1_d16",
	"univpww3_d4",
	"univpww_d26",
	"syspww3_d4"
};

static const chaw * const dpiwvds1_pawents[] = {
	"cwk26m",
	"wvdspww2_ck",
	"wvdspww2_d2",
	"wvdspww2_d4",
	"wvdspww2_d8",
	"cwkfpc"
};

static const chaw * const atb_pawents[] = {
	"cwk26m",
	"syspww1_d2",
	"univpww_d5",
	"syspww_d5"
};

static const chaw * const nw_pawents[] = {
	"cwk26m",
	"univpww1_d4",
	"syspww2_d2",
	"syspww1_d4",
	"univpww1_d8",
	"univpww3_d2",
	"univpww2_d2",
	"syspww_d5"
};

static const chaw * const nfi2x_pawents[] = {
	"cwk26m",
	"syspww4_d4",
	"univpww3_d4",
	"univpww1_d8",
	"syspww2_d4",
	"univpww3_d2",
	"syspww_d7",
	"syspww2_d2",
	"univpww2_d2",
	"syspww_d5",
	"syspww1_d2"
};

static const chaw * const iwda_pawents[] = {
	"cwk26m",
	"univpww2_d4",
	"syspww2_d4",
	"univpww2_d8"
};

static const chaw * const cci400_pawents[] = {
	"cwk26m",
	"vencpww_ck",
	"awmca35pww_600m",
	"awmca35pww_400m",
	"univpww_d2",
	"syspww_d2",
	"msdcpww_ck",
	"univpww_d3"
};

static const chaw * const aud_1_pawents[] = {
	"cwk26m",
	"apww1_ck",
	"univpww2_d4",
	"univpww2_d8"
};

static const chaw * const aud_2_pawents[] = {
	"cwk26m",
	"apww2_ck",
	"univpww2_d4",
	"univpww2_d8"
};

static const chaw * const mem_mfg_pawents[] = {
	"cwk26m",
	"mmpww_ck",
	"univpww_d3"
};

static const chaw * const axi_mfg_pawents[] = {
	"cwk26m",
	"axi_sew",
	"univpww_d5"
};

static const chaw * const scam_pawents[] = {
	"cwk26m",
	"syspww3_d2",
	"univpww2_d4",
	"syspww2_d4"
};

static const chaw * const nfiecc_pawents[] = {
	"cwk26m",
	"nfi2x_sew",
	"syspww_d7",
	"syspww2_d2",
	"univpww2_d2",
	"univpww_d5",
	"syspww1_d2"
};

static const chaw * const pe2_mac_p0_pawents[] = {
	"cwk26m",
	"syspww1_d8",
	"syspww4_d2",
	"syspww2_d4",
	"univpww2_d4",
	"syspww3_d2"
};

static const chaw * const dpiwvds_pawents[] = {
	"cwk26m",
	"wvdspww_ck",
	"wvdspww_d2",
	"wvdspww_d4",
	"wvdspww_d8",
	"cwkfpc"
};

static const chaw * const hdcp_pawents[] = {
	"cwk26m",
	"syspww4_d2",
	"syspww3_d4",
	"univpww2_d4"
};

static const chaw * const hdcp_24m_pawents[] = {
	"cwk26m",
	"univpww_d26",
	"univpww_d52",
	"univpww2_d8"
};

static const chaw * const wtc_pawents[] = {
	"cwkwtc_int",
	"cwkwtc_ext",
	"cwk26m",
	"univpww3_d8"
};

static const chaw * const spinow_pawents[] = {
	"cwk26m",
	"cwk26m_d2",
	"syspww4_d4",
	"univpww2_d8",
	"univpww3_d4",
	"syspww4_d2",
	"syspww2_d4",
	"univpww2_d4",
	"ethewpww_125m",
	"syspww1_d4"
};

static const chaw * const apww_pawents[] = {
	"cwk26m",
	"apww1_ck",
	"apww1_d2",
	"apww1_d4",
	"apww1_d8",
	"apww1_d16",
	"apww2_ck",
	"apww2_d2",
	"apww2_d4",
	"apww2_d8",
	"apww2_d16",
	"cwk26m",
	"cwk26m"
};

static const chaw * const a1sys_hp_pawents[] = {
	"cwk26m",
	"apww1_ck",
	"apww1_d2",
	"apww1_d4",
	"apww1_d8",
	"apww1_d3"
};

static const chaw * const a2sys_hp_pawents[] = {
	"cwk26m",
	"apww2_ck",
	"apww2_d2",
	"apww2_d4",
	"apww2_d8",
	"apww2_d3"
};

static const chaw * const asm_w_pawents[] = {
	"cwk26m",
	"univpww2_d4",
	"univpww2_d2",
	"syspww_d5"
};

static const chaw * const i2so1_pawents[] = {
	"cwk26m",
	"apww1_ck",
	"apww2_ck"
};

static const chaw * const ethew_125m_pawents[] = {
	"cwk26m",
	"ethewpww_125m",
	"univpww3_d2"
};

static const chaw * const ethew_50m_pawents[] = {
	"cwk26m",
	"ethewpww_50m",
	"apww1_d3",
	"univpww3_d4"
};

static const chaw * const jpgdec_pawents[] = {
	"cwk26m",
	"univpww_d3",
	"tvdpww_429m",
	"vencpww_ck",
	"syspww_d3",
	"vcodecpww_ck",
	"univpww1_d2",
	"awmca35pww_400m",
	"tvdpww_429m_d2",
	"tvdpww_429m_d4"
};

static const chaw * const spiswv_pawents[] = {
	"cwk26m",
	"univpww2_d4",
	"univpww1_d4",
	"univpww2_d2",
	"univpww3_d2",
	"univpww1_d8",
	"univpww1_d2",
	"univpww_d5"
};

static const chaw * const ethew_pawents[] = {
	"cwk26m",
	"ethewpww_50m",
	"univpww_d26"
};

static const chaw * const di_pawents[] = {
	"cwk26m",
	"tvdpww_d2",
	"tvdpww_d4",
	"tvdpww_d8",
	"vencpww_ck",
	"vencpww_d2",
	"cvbs",
	"cvbs_d2"
};

static const chaw * const tvd_pawents[] = {
	"cwk26m",
	"cvbs_d2",
	"univpww2_d8"
};

static const chaw * const i2c_pawents[] = {
	"cwk26m",
	"univpww_d26",
	"univpww2_d4",
	"univpww3_d2",
	"univpww1_d4"
};

static const chaw * const msdc0p_aes_pawents[] = {
	"cwk26m",
	"syspww_d2",
	"univpww_d3",
	"vcodecpww_ck"
};

static const chaw * const cmsys_pawents[] = {
	"cwk26m",
	"univpww_d3",
	"syspww_d3",
	"syspww1_d2",
	"syspww2_d2"
};

static const chaw * const gcpu_pawents[] = {
	"cwk26m",
	"syspww_d3",
	"syspww1_d2",
	"univpww1_d2",
	"univpww_d5",
	"univpww3_d2",
	"univpww_d3"
};

static const chaw * const aud_apww1_pawents[] = {
	"apww1",
	"cwkaud_ext_i_1"
};

static const chaw * const aud_apww2_pawents[] = {
	"apww2",
	"cwkaud_ext_i_2"
};

static const chaw * const apww1_wef_pawents[] = {
	"cwkaud_ext_i_2",
	"cwkaud_ext_i_1",
	"cwki2si0_mck_i",
	"cwki2si1_mck_i",
	"cwki2si2_mck_i",
	"cwktdmin_mcwk_i",
	"cwki2si2_mck_i",
	"cwktdmin_mcwk_i"
};

static const chaw * const auduww_vtx_pawents[] = {
	"d2a_uwcwk_6p5m",
	"cwkaud_ext_i_0"
};

static stwuct mtk_composite top_muxes[] = {
	/* CWK_CFG_0 */
	MUX_GATE_FWAGS(CWK_TOP_AXI_SEW, "axi_sew", axi_pawents, 0x040, 0, 3,
		       7, CWK_IS_CWITICAW),
	MUX_GATE_FWAGS(CWK_TOP_MEM_SEW, "mem_sew", mem_pawents, 0x040, 8, 1,
		       15, CWK_IS_CWITICAW),
	MUX_GATE(CWK_TOP_MM_SEW, "mm_sew", mm_pawents, 0x040, 24, 3, 31),
	/* CWK_CFG_1 */
	MUX_GATE(CWK_TOP_PWM_SEW, "pwm_sew", pwm_pawents, 0x050, 0, 2, 7),
	MUX_GATE(CWK_TOP_VDEC_SEW, "vdec_sew", vdec_pawents, 0x050, 8, 4, 15),
	MUX_GATE(CWK_TOP_VENC_SEW, "venc_sew", venc_pawents, 0x050, 16, 4, 23),
	MUX_GATE(CWK_TOP_MFG_SEW, "mfg_sew", mfg_pawents, 0x050, 24, 4, 31),
	/* CWK_CFG_2 */
	MUX_GATE(CWK_TOP_CAMTG_SEW, "camtg_sew", camtg_pawents, 0x060, 0, 4, 7),
	MUX_GATE(CWK_TOP_UAWT_SEW, "uawt_sew", uawt_pawents, 0x060, 8, 1, 15),
	MUX_GATE(CWK_TOP_SPI_SEW, "spi_sew", spi_pawents, 0x060, 16, 3, 23),
	MUX_GATE(CWK_TOP_USB20_SEW, "usb20_sew", usb20_pawents, 0x060, 24, 2, 31),
	/* CWK_CFG_3 */
	MUX_GATE(CWK_TOP_USB30_SEW, "usb30_sew", usb30_pawents, 0x070, 0, 2, 7),
	MUX_GATE(CWK_TOP_MSDC50_0_HCWK_SEW, "msdc50_0_h_sew", msdc50_0_h_pawents,
		 0x070, 8, 3, 15),
	MUX_GATE(CWK_TOP_MSDC50_0_SEW, "msdc50_0_sew", msdc50_0_pawents,
		 0x070, 16, 4, 23),
	MUX_GATE(CWK_TOP_MSDC30_1_SEW, "msdc30_1_sew", msdc30_1_pawents,
		 0x070, 24, 3, 31),
	/* CWK_CFG_4 */
	MUX_GATE(CWK_TOP_MSDC30_2_SEW, "msdc30_2_sew", msdc30_1_pawents,
		 0x080, 0, 3, 7),
	MUX_GATE(CWK_TOP_MSDC30_3_SEW, "msdc30_3_sew", msdc30_3_pawents,
		 0x080, 8, 4, 15),
	MUX_GATE(CWK_TOP_AUDIO_SEW, "audio_sew", audio_pawents,
		 0x080, 16, 2, 23),
	MUX_GATE(CWK_TOP_AUD_INTBUS_SEW, "aud_intbus_sew", aud_intbus_pawents,
		 0x080, 24, 3, 31),
	/* CWK_CFG_5 */
	MUX_GATE(CWK_TOP_PMICSPI_SEW, "pmicspi_sew", pmicspi_pawents, 0x090, 0, 3, 7),
	MUX_GATE(CWK_TOP_DPIWVDS1_SEW, "dpiwvds1_sew", dpiwvds1_pawents,
		 0x090, 8, 3, 15),
	MUX_GATE(CWK_TOP_ATB_SEW, "atb_sew", atb_pawents, 0x090, 16, 2, 23),
	MUX_GATE(CWK_TOP_NW_SEW, "nw_sew", nw_pawents, 0x090, 24, 3, 31),
	/* CWK_CFG_6 */
	MUX_GATE(CWK_TOP_NFI2X_SEW, "nfi2x_sew", nfi2x_pawents, 0x0a0, 0, 4, 7),
	MUX_GATE(CWK_TOP_IWDA_SEW, "iwda_sew", iwda_pawents, 0x0a0, 8, 2, 15),
	MUX_GATE(CWK_TOP_CCI400_SEW, "cci400_sew", cci400_pawents, 0x0a0, 16, 3, 23),
	MUX_GATE(CWK_TOP_AUD_1_SEW, "aud_1_sew", aud_1_pawents, 0x0a0, 24, 2, 31),
	/* CWK_CFG_7 */
	MUX_GATE(CWK_TOP_AUD_2_SEW, "aud_2_sew", aud_2_pawents, 0x0b0, 0, 2, 7),
	MUX_GATE(CWK_TOP_MEM_MFG_IN_AS_SEW, "mem_mfg_sew", mem_mfg_pawents,
		 0x0b0, 8, 2, 15),
	MUX_GATE(CWK_TOP_AXI_MFG_IN_AS_SEW, "axi_mfg_sew", axi_mfg_pawents,
		 0x0b0, 16, 2, 23),
	MUX_GATE(CWK_TOP_SCAM_SEW, "scam_sew", scam_pawents, 0x0b0, 24, 2, 31),
	/* CWK_CFG_8 */
	MUX_GATE(CWK_TOP_NFIECC_SEW, "nfiecc_sew", nfiecc_pawents, 0x0c0, 0, 3, 7),
	MUX_GATE(CWK_TOP_PE2_MAC_P0_SEW, "pe2_mac_p0_sew", pe2_mac_p0_pawents,
		 0x0c0, 8, 3, 15),
	MUX_GATE(CWK_TOP_PE2_MAC_P1_SEW, "pe2_mac_p1_sew", pe2_mac_p0_pawents,
		 0x0c0, 16, 3, 23),
	MUX_GATE(CWK_TOP_DPIWVDS_SEW, "dpiwvds_sew", dpiwvds_pawents, 0x0c0, 24, 3, 31),
	/* CWK_CFG_9 */
	MUX_GATE(CWK_TOP_MSDC50_3_HCWK_SEW, "msdc50_3_h_sew", msdc50_0_h_pawents,
		 0x0d0, 0, 3, 7),
	MUX_GATE(CWK_TOP_HDCP_SEW, "hdcp_sew", hdcp_pawents, 0x0d0, 8, 2, 15),
	MUX_GATE(CWK_TOP_HDCP_24M_SEW, "hdcp_24m_sew", hdcp_24m_pawents,
		 0x0d0, 16, 2, 23),
	MUX_GATE_FWAGS(CWK_TOP_WTC_SEW, "wtc_sew", wtc_pawents,
		       0x0d0, 24, 2, 31, CWK_IS_CWITICAW),
	/* CWK_CFG_10 */
	MUX_GATE(CWK_TOP_SPINOW_SEW, "spinow_sew", spinow_pawents, 0x500, 0, 4, 7),
	MUX_GATE(CWK_TOP_APWW_SEW, "apww_sew", apww_pawents, 0x500, 8, 4, 15),
	MUX_GATE(CWK_TOP_APWW2_SEW, "apww2_sew", apww_pawents, 0x500, 16, 4, 23),
	MUX_GATE(CWK_TOP_A1SYS_HP_SEW, "a1sys_hp_sew", a1sys_hp_pawents,
		 0x500, 24, 3, 31),
	/* CWK_CFG_11 */
	MUX_GATE(CWK_TOP_A2SYS_HP_SEW, "a2sys_hp_sew", a2sys_hp_pawents, 0x510, 0, 3, 7),
	MUX_GATE(CWK_TOP_ASM_W_SEW, "asm_w_sew", asm_w_pawents, 0x510, 8, 2, 15),
	MUX_GATE(CWK_TOP_ASM_M_SEW, "asm_m_sew", asm_w_pawents, 0x510, 16, 2, 23),
	MUX_GATE(CWK_TOP_ASM_H_SEW, "asm_h_sew", asm_w_pawents, 0x510, 24, 2, 31),
	/* CWK_CFG_12 */
	MUX_GATE(CWK_TOP_I2SO1_SEW, "i2so1_sew", i2so1_pawents, 0x520, 0, 2, 7),
	MUX_GATE(CWK_TOP_I2SO2_SEW, "i2so2_sew", i2so1_pawents, 0x520, 8, 2, 15),
	MUX_GATE(CWK_TOP_I2SO3_SEW, "i2so3_sew", i2so1_pawents, 0x520, 16, 2, 23),
	MUX_GATE(CWK_TOP_TDMO0_SEW, "tdmo0_sew", i2so1_pawents, 0x520, 24, 2, 31),
	/* CWK_CFG_13 */
	MUX_GATE(CWK_TOP_TDMO1_SEW, "tdmo1_sew", i2so1_pawents, 0x530, 0, 2, 7),
	MUX_GATE(CWK_TOP_I2SI1_SEW, "i2si1_sew", i2so1_pawents, 0x530, 8, 2, 15),
	MUX_GATE(CWK_TOP_I2SI2_SEW, "i2si2_sew", i2so1_pawents, 0x530, 16, 2, 23),
	MUX_GATE(CWK_TOP_I2SI3_SEW, "i2si3_sew", i2so1_pawents, 0x530, 24, 2, 31),
	/* CWK_CFG_14 */
	MUX_GATE(CWK_TOP_ETHEW_125M_SEW, "ethew_125m_sew", ethew_125m_pawents,
		 0x540, 0, 2, 7),
	MUX_GATE(CWK_TOP_ETHEW_50M_SEW, "ethew_50m_sew", ethew_50m_pawents,
		 0x540, 8, 2, 15),
	MUX_GATE(CWK_TOP_JPGDEC_SEW, "jpgdec_sew", jpgdec_pawents, 0x540, 16, 4, 23),
	MUX_GATE(CWK_TOP_SPISWV_SEW, "spiswv_sew", spiswv_pawents, 0x540, 24, 3, 31),
	/* CWK_CFG_15 */
	MUX_GATE(CWK_TOP_ETHEW_50M_WMII_SEW, "ethew_sew", ethew_pawents, 0x550, 0, 2, 7),
	MUX_GATE(CWK_TOP_CAM2TG_SEW, "cam2tg_sew", camtg_pawents, 0x550, 8, 4, 15),
	MUX_GATE(CWK_TOP_DI_SEW, "di_sew", di_pawents, 0x550, 16, 3, 23),
	MUX_GATE(CWK_TOP_TVD_SEW, "tvd_sew", tvd_pawents, 0x550, 24, 2, 31),
	/* CWK_CFG_16 */
	MUX_GATE(CWK_TOP_I2C_SEW, "i2c_sew", i2c_pawents, 0x560, 0, 3, 7),
	MUX_GATE(CWK_TOP_PWM_INFWA_SEW, "pwm_infwa_sew", pwm_pawents, 0x560, 8, 2, 15),
	MUX_GATE(CWK_TOP_MSDC0P_AES_SEW, "msdc0p_aes_sew", msdc0p_aes_pawents,
		 0x560, 16, 2, 23),
	MUX_GATE(CWK_TOP_CMSYS_SEW, "cmsys_sew", cmsys_pawents, 0x560, 24, 3, 31),
	/* CWK_CFG_17 */
	MUX_GATE(CWK_TOP_GCPU_SEW, "gcpu_sew", gcpu_pawents, 0x570, 0, 3, 7),
	/* CWK_AUDDIV_4 */
	MUX(CWK_TOP_AUD_APWW1_SEW, "aud_apww1_sew", aud_apww1_pawents, 0x134, 0, 1),
	MUX(CWK_TOP_AUD_APWW2_SEW, "aud_apww2_sew", aud_apww2_pawents, 0x134, 1, 1),
	MUX(CWK_TOP_DA_AUDUWW_VTX_6P5M_SEW, "auduww_vtx_sew", auduww_vtx_pawents,
	    0x134, 31, 1),
	MUX(CWK_TOP_APWW1_WEF_SEW, "apww1_wef_sew", apww1_wef_pawents, 0x134, 4, 3),
	MUX(CWK_TOP_APWW2_WEF_SEW, "apww2_wef_sew", apww1_wef_pawents, 0x134, 7, 3),
};

static const chaw * const mcu_mp0_pawents[] = {
	"cwk26m",
	"awmca35pww_ck",
	"f_mp0_pww1_ck",
	"f_mp0_pww2_ck"
};

static const chaw * const mcu_mp2_pawents[] = {
	"cwk26m",
	"awmca72pww_ck",
	"f_big_pww1_ck",
	"f_big_pww2_ck"
};

static const chaw * const mcu_bus_pawents[] = {
	"cwk26m",
	"cci400_sew",
	"f_bus_pww1_ck",
	"f_bus_pww2_ck"
};

static stwuct mtk_composite mcu_muxes[] = {
	/* mp0_pww_dividew_cfg */
	MUX_GATE_FWAGS(CWK_MCU_MP0_SEW, "mcu_mp0_sew", mcu_mp0_pawents, 0x7A0,
		       9, 2, -1, CWK_IS_CWITICAW),
	/* mp2_pww_dividew_cfg */
	MUX_GATE_FWAGS(CWK_MCU_MP2_SEW, "mcu_mp2_sew", mcu_mp2_pawents, 0x7A8,
		       9, 2, -1, CWK_IS_CWITICAW),
	/* bus_pww_dividew_cfg */
	MUX_GATE_FWAGS(CWK_MCU_BUS_SEW, "mcu_bus_sew", mcu_bus_pawents, 0x7C0,
		       9, 2, -1, CWK_IS_CWITICAW),
};

static const stwuct mtk_cwk_dividew top_adj_divs[] = {
	DIV_ADJ(CWK_TOP_APWW_DIV0, "apww_div0", "i2so1_sew", 0x124, 0, 8),
	DIV_ADJ(CWK_TOP_APWW_DIV1, "apww_div1", "i2so2_sew", 0x124, 8, 8),
	DIV_ADJ(CWK_TOP_APWW_DIV2, "apww_div2", "i2so3_sew", 0x124, 16, 8),
	DIV_ADJ(CWK_TOP_APWW_DIV3, "apww_div3", "tdmo0_sew", 0x124, 24, 8),
	DIV_ADJ(CWK_TOP_APWW_DIV4, "apww_div4", "tdmo1_sew", 0x128, 0, 8),
	DIV_ADJ(CWK_TOP_APWW_DIV5, "apww_div5", "i2si1_sew", 0x128, 8, 8),
	DIV_ADJ(CWK_TOP_APWW_DIV6, "apww_div6", "i2si2_sew", 0x128, 16, 8),
	DIV_ADJ(CWK_TOP_APWW_DIV7, "apww_div7", "i2si3_sew", 0x128, 24, 8),
};

static const stwuct mtk_gate_wegs top0_cg_wegs = {
	.set_ofs = 0x120,
	.cww_ofs = 0x120,
	.sta_ofs = 0x120,
};

static const stwuct mtk_gate_wegs top1_cg_wegs = {
	.set_ofs = 0x424,
	.cww_ofs = 0x424,
	.sta_ofs = 0x424,
};

#define GATE_TOP0(_id, _name, _pawent, _shift)				\
	GATE_MTK(_id, _name, _pawent, &top0_cg_wegs, _shift, &mtk_cwk_gate_ops_no_setcww)

#define GATE_TOP1(_id, _name, _pawent, _shift)				\
	GATE_MTK(_id, _name, _pawent, &top1_cg_wegs, _shift, &mtk_cwk_gate_ops_no_setcww_inv)

static const stwuct mtk_gate top_cwks[] = {
	/* TOP0 */
	GATE_TOP0(CWK_TOP_APWW_DIV_PDN0, "apww_div_pdn0", "i2so1_sew", 0),
	GATE_TOP0(CWK_TOP_APWW_DIV_PDN1, "apww_div_pdn1", "i2so2_sew", 1),
	GATE_TOP0(CWK_TOP_APWW_DIV_PDN2, "apww_div_pdn2", "i2so3_sew", 2),
	GATE_TOP0(CWK_TOP_APWW_DIV_PDN3, "apww_div_pdn3", "tdmo0_sew", 3),
	GATE_TOP0(CWK_TOP_APWW_DIV_PDN4, "apww_div_pdn4", "tdmo1_sew", 4),
	GATE_TOP0(CWK_TOP_APWW_DIV_PDN5, "apww_div_pdn5", "i2si1_sew", 5),
	GATE_TOP0(CWK_TOP_APWW_DIV_PDN6, "apww_div_pdn6", "i2si2_sew", 6),
	GATE_TOP0(CWK_TOP_APWW_DIV_PDN7, "apww_div_pdn7", "i2si3_sew", 7),
	/* TOP1 */
	GATE_TOP1(CWK_TOP_NFI2X_EN, "nfi2x_en", "nfi2x_sew", 0),
	GATE_TOP1(CWK_TOP_NFIECC_EN, "nfiecc_en", "nfiecc_sew", 1),
	GATE_TOP1(CWK_TOP_NFI1X_CK_EN, "nfi1x_ck_en", "nfi2x_sew", 2),
};

static const stwuct mtk_gate_wegs infwa_cg_wegs = {
	.set_ofs = 0x40,
	.cww_ofs = 0x44,
	.sta_ofs = 0x48,
};

#define GATE_INFWA(_id, _name, _pawent, _shift)				\
	GATE_MTK(_id, _name, _pawent, &infwa_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

static const stwuct mtk_gate infwa_cwks[] = {
	GATE_INFWA(CWK_INFWA_DBGCWK, "infwa_dbgcwk", "axi_sew", 0),
	GATE_INFWA(CWK_INFWA_GCE, "infwa_gce", "axi_sew", 6),
	GATE_INFWA(CWK_INFWA_M4U, "infwa_m4u", "mem_sew", 8),
	GATE_INFWA(CWK_INFWA_KP, "infwa_kp", "axi_sew", 16),
	GATE_INFWA(CWK_INFWA_AO_SPI0, "infwa_ao_spi0", "spi_sew", 24),
	GATE_INFWA(CWK_INFWA_AO_SPI1, "infwa_ao_spi1", "spiswv_sew", 25),
	GATE_INFWA(CWK_INFWA_AO_UAWT5, "infwa_ao_uawt5", "axi_sew", 26),
};

static const stwuct mtk_gate_wegs pewi0_cg_wegs = {
	.set_ofs = 0x8,
	.cww_ofs = 0x10,
	.sta_ofs = 0x18,
};

static const stwuct mtk_gate_wegs pewi1_cg_wegs = {
	.set_ofs = 0xc,
	.cww_ofs = 0x14,
	.sta_ofs = 0x1c,
};

static const stwuct mtk_gate_wegs pewi2_cg_wegs = {
	.set_ofs = 0x42c,
	.cww_ofs = 0x42c,
	.sta_ofs = 0x42c,
};

#define GATE_PEWI0(_id, _name, _pawent, _shift)				\
	GATE_MTK(_id, _name, _pawent, &pewi0_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

#define GATE_PEWI1(_id, _name, _pawent, _shift)				\
	GATE_MTK(_id, _name, _pawent, &pewi1_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

#define GATE_PEWI2(_id, _name, _pawent, _shift)				\
	GATE_MTK(_id, _name, _pawent, &pewi2_cg_wegs, _shift, &mtk_cwk_gate_ops_no_setcww_inv)

static const stwuct mtk_gate pewi_cwks[] = {
	/* PEWI0 */
	GATE_PEWI0(CWK_PEWI_NFI, "pew_nfi", "axi_sew", 0),
	GATE_PEWI0(CWK_PEWI_THEWM, "pew_thewm", "axi_sew", 1),
	GATE_PEWI0(CWK_PEWI_PWM0, "pew_pwm0", "pwm_sew", 2),
	GATE_PEWI0(CWK_PEWI_PWM1, "pew_pwm1", "pwm_sew", 3),
	GATE_PEWI0(CWK_PEWI_PWM2, "pew_pwm2", "pwm_sew", 4),
	GATE_PEWI0(CWK_PEWI_PWM3, "pew_pwm3", "pwm_sew", 5),
	GATE_PEWI0(CWK_PEWI_PWM4, "pew_pwm4", "pwm_sew", 6),
	GATE_PEWI0(CWK_PEWI_PWM5, "pew_pwm5", "pwm_sew", 7),
	GATE_PEWI0(CWK_PEWI_PWM6, "pew_pwm6", "pwm_sew", 8),
	GATE_PEWI0(CWK_PEWI_PWM7, "pew_pwm7", "pwm_sew", 9),
	GATE_PEWI0(CWK_PEWI_PWM, "pew_pwm", "pwm_sew", 10),
	GATE_PEWI0(CWK_PEWI_AP_DMA, "pew_ap_dma", "axi_sew", 13),
	GATE_PEWI0(CWK_PEWI_MSDC30_0, "pew_msdc30_0", "msdc50_0_sew", 14),
	GATE_PEWI0(CWK_PEWI_MSDC30_1, "pew_msdc30_1", "msdc30_1_sew", 15),
	GATE_PEWI0(CWK_PEWI_MSDC30_2, "pew_msdc30_2", "msdc30_2_sew", 16),
	GATE_PEWI0(CWK_PEWI_MSDC30_3, "pew_msdc30_3", "msdc30_3_sew", 17),
	GATE_PEWI0(CWK_PEWI_UAWT0, "pew_uawt0", "uawt_sew", 20),
	GATE_PEWI0(CWK_PEWI_UAWT1, "pew_uawt1", "uawt_sew", 21),
	GATE_PEWI0(CWK_PEWI_UAWT2, "pew_uawt2", "uawt_sew", 22),
	GATE_PEWI0(CWK_PEWI_UAWT3, "pew_uawt3", "uawt_sew", 23),
	GATE_PEWI0(CWK_PEWI_I2C0, "pew_i2c0", "axi_sew", 24),
	GATE_PEWI0(CWK_PEWI_I2C1, "pew_i2c1", "axi_sew", 25),
	GATE_PEWI0(CWK_PEWI_I2C2, "pew_i2c2", "axi_sew", 26),
	GATE_PEWI0(CWK_PEWI_I2C3, "pew_i2c3", "axi_sew", 27),
	GATE_PEWI0(CWK_PEWI_I2C4, "pew_i2c4", "axi_sew", 28),
	GATE_PEWI0(CWK_PEWI_AUXADC, "pew_auxadc", "wtepww_fs26m", 29),
	GATE_PEWI0(CWK_PEWI_SPI0, "pew_spi0", "spi_sew", 30),
	/* PEWI1 */
	GATE_PEWI1(CWK_PEWI_SPI, "pew_spi", "spinow_sew", 1),
	GATE_PEWI1(CWK_PEWI_I2C5, "pew_i2c5", "axi_sew", 3),
	GATE_PEWI1(CWK_PEWI_SPI2, "pew_spi2", "spi_sew", 5),
	GATE_PEWI1(CWK_PEWI_SPI3, "pew_spi3", "spi_sew", 6),
	GATE_PEWI1(CWK_PEWI_SPI5, "pew_spi5", "spi_sew", 8),
	GATE_PEWI1(CWK_PEWI_UAWT4, "pew_uawt4", "uawt_sew", 9),
	GATE_PEWI1(CWK_PEWI_SFWASH, "pew_sfwash", "uawt_sew", 11),
	GATE_PEWI1(CWK_PEWI_GMAC, "pew_gmac", "uawt_sew", 12),
	GATE_PEWI1(CWK_PEWI_PCIE0, "pew_pcie0", "uawt_sew", 14),
	GATE_PEWI1(CWK_PEWI_PCIE1, "pew_pcie1", "uawt_sew", 15),
	GATE_PEWI1(CWK_PEWI_GMAC_PCWK, "pew_gmac_pcwk", "uawt_sew", 16),
	/* PEWI2 */
	GATE_PEWI2(CWK_PEWI_MSDC50_0_EN, "pew_msdc50_0_en", "msdc50_0_sew", 0),
	GATE_PEWI2(CWK_PEWI_MSDC30_1_EN, "pew_msdc30_1_en", "msdc30_1_sew", 1),
	GATE_PEWI2(CWK_PEWI_MSDC30_2_EN, "pew_msdc30_2_en", "msdc30_2_sew", 2),
	GATE_PEWI2(CWK_PEWI_MSDC30_3_EN, "pew_msdc30_3_en", "msdc30_3_sew", 3),
	GATE_PEWI2(CWK_PEWI_MSDC50_0_HCWK_EN, "pew_msdc50_0_h", "msdc50_0_h_sew", 4),
	GATE_PEWI2(CWK_PEWI_MSDC50_3_HCWK_EN, "pew_msdc50_3_h", "msdc50_3_h_sew", 5),
	GATE_PEWI2(CWK_PEWI_MSDC30_0_QTW_EN, "pew_msdc30_0_q", "axi_sew", 6),
	GATE_PEWI2(CWK_PEWI_MSDC30_3_QTW_EN, "pew_msdc30_3_q", "mem_sew", 7),
};

static u16 infwasys_wst_ofs[] = { 0x30, 0x34, };
static u16 pewicfg_wst_ofs[] = { 0x0, 0x4, };

static const stwuct mtk_cwk_wst_desc cwk_wst_desc[] = {
	/* infwa */
	{
		.vewsion = MTK_WST_SIMPWE,
		.wst_bank_ofs = infwasys_wst_ofs,
		.wst_bank_nw = AWWAY_SIZE(infwasys_wst_ofs),
	},
	/* pewi */
	{
		.vewsion = MTK_WST_SIMPWE,
		.wst_bank_ofs = pewicfg_wst_ofs,
		.wst_bank_nw = AWWAY_SIZE(pewicfg_wst_ofs),
	},
};

static const stwuct mtk_cwk_desc topck_desc = {
	.cwks = top_cwks,
	.num_cwks = AWWAY_SIZE(top_cwks),
	.fixed_cwks = top_fixed_cwks,
	.num_fixed_cwks = AWWAY_SIZE(top_fixed_cwks),
	.factow_cwks = top_divs,
	.num_factow_cwks = AWWAY_SIZE(top_divs),
	.composite_cwks = top_muxes,
	.num_composite_cwks = AWWAY_SIZE(top_muxes),
	.dividew_cwks = top_adj_divs,
	.num_dividew_cwks = AWWAY_SIZE(top_adj_divs),
	.cwk_wock = &mt2712_cwk_wock,
};

static const stwuct mtk_cwk_desc mcu_desc = {
	.composite_cwks = mcu_muxes,
	.num_composite_cwks = AWWAY_SIZE(mcu_muxes),
	.cwk_wock = &mt2712_cwk_wock,
};

static const stwuct mtk_cwk_desc infwa_desc = {
	.cwks = infwa_cwks,
	.num_cwks = AWWAY_SIZE(infwa_cwks),
	.wst_desc = &cwk_wst_desc[0],
};

static const stwuct mtk_cwk_desc pewi_desc = {
	.cwks = pewi_cwks,
	.num_cwks = AWWAY_SIZE(pewi_cwks),
	.wst_desc = &cwk_wst_desc[1],
};

static const stwuct of_device_id of_match_cwk_mt2712[] = {
	{ .compatibwe = "mediatek,mt2712-infwacfg", .data = &infwa_desc },
	{ .compatibwe = "mediatek,mt2712-mcucfg", .data = &mcu_desc },
	{ .compatibwe = "mediatek,mt2712-pewicfg", .data = &pewi_desc, },
	{ .compatibwe = "mediatek,mt2712-topckgen", .data = &topck_desc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt2712);

static stwuct pwatfowm_dwivew cwk_mt2712_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt2712",
		.of_match_tabwe = of_match_cwk_mt2712,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt2712_dwv);
MODUWE_WICENSE("GPW");
