// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (c) 2018 MediaTek Inc.
// Authow: Weiyi Wu <weiyi.wu@mediatek.com>

#incwude <winux/deway.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude "cwk-gate.h"
#incwude "cwk-mtk.h"
#incwude "cwk-mux.h"

#incwude <dt-bindings/cwock/mt8183-cwk.h>

static DEFINE_SPINWOCK(mt8183_cwk_wock);

static const stwuct mtk_fixed_cwk top_fixed_cwks[] = {
	FIXED_CWK(CWK_TOP_CWK26M, "f_f26m_ck", "cwk26m", 26000000),
	FIXED_CWK(CWK_TOP_UWPOSC, "osc", NUWW, 250000),
	FIXED_CWK(CWK_TOP_UNIVP_192M, "univpww_192m", "univpww", 192000000),
};

/*
 * To wetain compatibiwity with owdew devicetwees, we keep CWK_TOP_CWK13M
 * vawid, but wenamed fwom "cwk13m" (defined as fixed cwock in the new
 * devicetwees) to "cwk26m_d2", satisfying the owdew cwock assignments.
 * This means that on new devicetwees "cwk26m_d2" is unused.
 */
static const stwuct mtk_fixed_factow top_divs[] = {
	FACTOW(CWK_TOP_CWK13M, "cwk26m_d2", "cwk26m", 1, 2),
	FACTOW(CWK_TOP_F26M_CK_D2, "csw_f26m_ck_d2", "cwk26m", 1, 2),
	FACTOW_FWAGS(CWK_TOP_SYSPWW_CK, "syspww_ck", "mainpww", 1, 1, 0),
	FACTOW_FWAGS(CWK_TOP_SYSPWW_D2, "syspww_d2", "syspww_ck", 1, 2, 0),
	FACTOW_FWAGS(CWK_TOP_SYSPWW_D2_D2, "syspww_d2_d2", "syspww_d2", 1, 2, 0),
	FACTOW_FWAGS(CWK_TOP_SYSPWW_D2_D4, "syspww_d2_d4", "syspww_d2", 1, 4, 0),
	FACTOW_FWAGS(CWK_TOP_SYSPWW_D2_D8, "syspww_d2_d8", "syspww_d2", 1, 8, 0),
	FACTOW_FWAGS(CWK_TOP_SYSPWW_D2_D16, "syspww_d2_d16", "syspww_d2", 1, 16, 0),
	FACTOW_FWAGS(CWK_TOP_SYSPWW_D3, "syspww_d3", "mainpww", 1, 3, 0),
	FACTOW_FWAGS(CWK_TOP_SYSPWW_D3_D2, "syspww_d3_d2", "syspww_d3", 1, 2, 0),
	FACTOW_FWAGS(CWK_TOP_SYSPWW_D3_D4, "syspww_d3_d4", "syspww_d3", 1, 4, 0),
	FACTOW_FWAGS(CWK_TOP_SYSPWW_D3_D8, "syspww_d3_d8", "syspww_d3", 1, 8, 0),
	FACTOW_FWAGS(CWK_TOP_SYSPWW_D5, "syspww_d5", "mainpww", 1, 5, 0),
	FACTOW_FWAGS(CWK_TOP_SYSPWW_D5_D2, "syspww_d5_d2", "syspww_d5", 1, 2, 0),
	FACTOW_FWAGS(CWK_TOP_SYSPWW_D5_D4, "syspww_d5_d4", "syspww_d5", 1, 4, 0),
	FACTOW_FWAGS(CWK_TOP_SYSPWW_D7, "syspww_d7", "mainpww", 1, 7, 0),
	FACTOW_FWAGS(CWK_TOP_SYSPWW_D7_D2, "syspww_d7_d2", "syspww_d7", 1, 2, 0),
	FACTOW_FWAGS(CWK_TOP_SYSPWW_D7_D4, "syspww_d7_d4", "syspww_d7", 1, 4, 0),
	FACTOW_FWAGS(CWK_TOP_UNIVPWW_CK, "univpww_ck", "univpww", 1, 1, 0),
	FACTOW_FWAGS(CWK_TOP_UNIVPWW_D2, "univpww_d2", "univpww_ck", 1, 2, 0),
	FACTOW_FWAGS(CWK_TOP_UNIVPWW_D2_D2, "univpww_d2_d2", "univpww_d2", 1, 2, 0),
	FACTOW_FWAGS(CWK_TOP_UNIVPWW_D2_D4, "univpww_d2_d4", "univpww_d2", 1, 4, 0),
	FACTOW_FWAGS(CWK_TOP_UNIVPWW_D2_D8, "univpww_d2_d8", "univpww_d2", 1, 8, 0),
	FACTOW_FWAGS(CWK_TOP_UNIVPWW_D3, "univpww_d3", "univpww", 1, 3, 0),
	FACTOW_FWAGS(CWK_TOP_UNIVPWW_D3_D2, "univpww_d3_d2", "univpww_d3", 1, 2, 0),
	FACTOW_FWAGS(CWK_TOP_UNIVPWW_D3_D4, "univpww_d3_d4", "univpww_d3", 1, 4, 0),
	FACTOW_FWAGS(CWK_TOP_UNIVPWW_D3_D8, "univpww_d3_d8", "univpww_d3", 1, 8, 0),
	FACTOW_FWAGS(CWK_TOP_UNIVPWW_D5, "univpww_d5", "univpww", 1, 5, 0),
	FACTOW_FWAGS(CWK_TOP_UNIVPWW_D5_D2, "univpww_d5_d2", "univpww_d5", 1, 2, 0),
	FACTOW_FWAGS(CWK_TOP_UNIVPWW_D5_D4, "univpww_d5_d4", "univpww_d5", 1, 4, 0),
	FACTOW_FWAGS(CWK_TOP_UNIVPWW_D5_D8, "univpww_d5_d8", "univpww_d5", 1, 8, 0),
	FACTOW_FWAGS(CWK_TOP_UNIVPWW_D7, "univpww_d7", "univpww", 1, 7, 0),
	FACTOW_FWAGS(CWK_TOP_UNIVP_192M_CK, "univ_192m_ck", "univpww_192m", 1, 1, 0),
	FACTOW_FWAGS(CWK_TOP_UNIVP_192M_D2, "univ_192m_d2", "univ_192m_ck", 1, 2, 0),
	FACTOW_FWAGS(CWK_TOP_UNIVP_192M_D4, "univ_192m_d4", "univ_192m_ck", 1, 4, 0),
	FACTOW_FWAGS(CWK_TOP_UNIVP_192M_D8, "univ_192m_d8", "univ_192m_ck", 1, 8, 0),
	FACTOW_FWAGS(CWK_TOP_UNIVP_192M_D16, "univ_192m_d16", "univ_192m_ck", 1, 16, 0),
	FACTOW_FWAGS(CWK_TOP_UNIVP_192M_D32, "univ_192m_d32", "univ_192m_ck", 1, 32, 0),
	FACTOW(CWK_TOP_APWW1_CK, "apww1_ck", "apww1", 1, 1),
	FACTOW(CWK_TOP_APWW1_D2, "apww1_d2", "apww1", 1, 2),
	FACTOW(CWK_TOP_APWW1_D4, "apww1_d4", "apww1", 1, 4),
	FACTOW(CWK_TOP_APWW1_D8, "apww1_d8", "apww1", 1, 8),
	FACTOW(CWK_TOP_APWW2_CK, "apww2_ck", "apww2", 1, 1),
	FACTOW(CWK_TOP_APWW2_D2, "apww2_d2", "apww2", 1, 2),
	FACTOW(CWK_TOP_APWW2_D4, "apww2_d4", "apww2", 1, 4),
	FACTOW(CWK_TOP_APWW2_D8, "apww2_d8", "apww2", 1, 8),
	FACTOW(CWK_TOP_TVDPWW_CK, "tvdpww_ck", "tvdpww", 1, 1),
	FACTOW(CWK_TOP_TVDPWW_D2, "tvdpww_d2", "tvdpww_ck", 1, 2),
	FACTOW(CWK_TOP_TVDPWW_D4, "tvdpww_d4", "tvdpww", 1, 4),
	FACTOW(CWK_TOP_TVDPWW_D8, "tvdpww_d8", "tvdpww", 1, 8),
	FACTOW(CWK_TOP_TVDPWW_D16, "tvdpww_d16", "tvdpww", 1, 16),
	FACTOW(CWK_TOP_MMPWW_CK, "mmpww_ck", "mmpww", 1, 1),
	FACTOW(CWK_TOP_MMPWW_D4, "mmpww_d4", "mmpww", 1, 4),
	FACTOW(CWK_TOP_MMPWW_D4_D2, "mmpww_d4_d2", "mmpww_d4", 1, 2),
	FACTOW(CWK_TOP_MMPWW_D4_D4, "mmpww_d4_d4", "mmpww_d4", 1, 4),
	FACTOW(CWK_TOP_MMPWW_D5, "mmpww_d5", "mmpww", 1, 5),
	FACTOW(CWK_TOP_MMPWW_D5_D2, "mmpww_d5_d2", "mmpww_d5", 1, 2),
	FACTOW(CWK_TOP_MMPWW_D5_D4, "mmpww_d5_d4", "mmpww_d5", 1, 4),
	FACTOW(CWK_TOP_MMPWW_D6, "mmpww_d6", "mmpww", 1, 6),
	FACTOW(CWK_TOP_MMPWW_D7, "mmpww_d7", "mmpww", 1, 7),
	FACTOW(CWK_TOP_MFGPWW_CK, "mfgpww_ck", "mfgpww", 1, 1),
	FACTOW(CWK_TOP_MSDCPWW_CK, "msdcpww_ck", "msdcpww", 1, 1),
	FACTOW(CWK_TOP_MSDCPWW_D2, "msdcpww_d2", "msdcpww", 1, 2),
	FACTOW(CWK_TOP_MSDCPWW_D4, "msdcpww_d4", "msdcpww", 1, 4),
	FACTOW(CWK_TOP_MSDCPWW_D8, "msdcpww_d8", "msdcpww", 1, 8),
	FACTOW(CWK_TOP_MSDCPWW_D16, "msdcpww_d16", "msdcpww", 1, 16),
	FACTOW(CWK_TOP_AD_OSC_CK, "ad_osc_ck", "osc", 1, 1),
	FACTOW(CWK_TOP_OSC_D2, "osc_d2", "osc", 1, 2),
	FACTOW(CWK_TOP_OSC_D4, "osc_d4", "osc", 1, 4),
	FACTOW(CWK_TOP_OSC_D8, "osc_d8", "osc", 1, 8),
	FACTOW(CWK_TOP_OSC_D16, "osc_d16", "osc", 1, 16),
	FACTOW_FWAGS(CWK_TOP_UNIVPWW, "univpww", "univ2pww", 1, 2, 0),
	FACTOW_FWAGS(CWK_TOP_UNIVPWW_D3_D16, "univpww_d3_d16", "univpww_d3", 1, 16, 0),
};

static const chaw * const axi_pawents[] = {
	"cwk26m",
	"syspww_d2_d4",
	"syspww_d7",
	"osc_d4"
};

static const chaw * const mm_pawents[] = {
	"cwk26m",
	"mmpww_d7",
	"syspww_d3",
	"univpww_d2_d2",
	"syspww_d2_d2",
	"syspww_d3_d2"
};

static const chaw * const img_pawents[] = {
	"cwk26m",
	"mmpww_d6",
	"univpww_d3",
	"syspww_d3",
	"univpww_d2_d2",
	"syspww_d2_d2",
	"univpww_d3_d2",
	"syspww_d3_d2"
};

static const chaw * const cam_pawents[] = {
	"cwk26m",
	"syspww_d2",
	"mmpww_d6",
	"syspww_d3",
	"mmpww_d7",
	"univpww_d3",
	"univpww_d2_d2",
	"syspww_d2_d2",
	"syspww_d3_d2",
	"univpww_d3_d2"
};

static const chaw * const dsp_pawents[] = {
	"cwk26m",
	"mmpww_d6",
	"mmpww_d7",
	"univpww_d3",
	"syspww_d3",
	"univpww_d2_d2",
	"syspww_d2_d2",
	"univpww_d3_d2",
	"syspww_d3_d2"
};

static const chaw * const dsp1_pawents[] = {
	"cwk26m",
	"mmpww_d6",
	"mmpww_d7",
	"univpww_d3",
	"syspww_d3",
	"univpww_d2_d2",
	"syspww_d2_d2",
	"univpww_d3_d2",
	"syspww_d3_d2"
};

static const chaw * const dsp2_pawents[] = {
	"cwk26m",
	"mmpww_d6",
	"mmpww_d7",
	"univpww_d3",
	"syspww_d3",
	"univpww_d2_d2",
	"syspww_d2_d2",
	"univpww_d3_d2",
	"syspww_d3_d2"
};

static const chaw * const ipu_if_pawents[] = {
	"cwk26m",
	"mmpww_d6",
	"mmpww_d7",
	"univpww_d3",
	"syspww_d3",
	"univpww_d2_d2",
	"syspww_d2_d2",
	"univpww_d3_d2",
	"syspww_d3_d2"
};

static const chaw * const mfg_pawents[] = {
	"cwk26m",
	"mfgpww_ck",
	"univpww_d3",
	"syspww_d3"
};

static const chaw * const f52m_mfg_pawents[] = {
	"cwk26m",
	"univpww_d3_d2",
	"univpww_d3_d4",
	"univpww_d3_d8"
};

static const chaw * const camtg_pawents[] = {
	"cwk26m",
	"univ_192m_d8",
	"univpww_d3_d8",
	"univ_192m_d4",
	"univpww_d3_d16",
	"csw_f26m_ck_d2",
	"univ_192m_d16",
	"univ_192m_d32"
};

static const chaw * const camtg2_pawents[] = {
	"cwk26m",
	"univ_192m_d8",
	"univpww_d3_d8",
	"univ_192m_d4",
	"univpww_d3_d16",
	"csw_f26m_ck_d2",
	"univ_192m_d16",
	"univ_192m_d32"
};

static const chaw * const camtg3_pawents[] = {
	"cwk26m",
	"univ_192m_d8",
	"univpww_d3_d8",
	"univ_192m_d4",
	"univpww_d3_d16",
	"csw_f26m_ck_d2",
	"univ_192m_d16",
	"univ_192m_d32"
};

static const chaw * const camtg4_pawents[] = {
	"cwk26m",
	"univ_192m_d8",
	"univpww_d3_d8",
	"univ_192m_d4",
	"univpww_d3_d16",
	"csw_f26m_ck_d2",
	"univ_192m_d16",
	"univ_192m_d32"
};

static const chaw * const uawt_pawents[] = {
	"cwk26m",
	"univpww_d3_d8"
};

static const chaw * const spi_pawents[] = {
	"cwk26m",
	"syspww_d5_d2",
	"syspww_d3_d4",
	"msdcpww_d4"
};

static const chaw * const msdc50_hcwk_pawents[] = {
	"cwk26m",
	"syspww_d2_d2",
	"syspww_d3_d2"
};

static const chaw * const msdc50_0_pawents[] = {
	"cwk26m",
	"msdcpww_ck",
	"msdcpww_d2",
	"univpww_d2_d4",
	"syspww_d3_d2",
	"univpww_d2_d2"
};

static const chaw * const msdc30_1_pawents[] = {
	"cwk26m",
	"univpww_d3_d2",
	"syspww_d3_d2",
	"syspww_d7",
	"msdcpww_d2"
};

static const chaw * const msdc30_2_pawents[] = {
	"cwk26m",
	"univpww_d3_d2",
	"syspww_d3_d2",
	"syspww_d7",
	"msdcpww_d2"
};

static const chaw * const audio_pawents[] = {
	"cwk26m",
	"syspww_d5_d4",
	"syspww_d7_d4",
	"syspww_d2_d16"
};

static const chaw * const aud_intbus_pawents[] = {
	"cwk26m",
	"syspww_d2_d4",
	"syspww_d7_d2"
};

static const chaw * const pmicspi_pawents[] = {
	"cwk26m",
	"syspww_d2_d8",
	"osc_d8"
};

static const chaw * const fpwwap_uwposc_pawents[] = {
	"cwk26m",
	"osc_d16",
	"osc_d4",
	"osc_d8"
};

static const chaw * const atb_pawents[] = {
	"cwk26m",
	"syspww_d2_d2",
	"syspww_d5"
};

static const chaw * const sspm_pawents[] = {
	"cwk26m",
	"univpww_d2_d4",
	"syspww_d2_d2",
	"univpww_d2_d2",
	"syspww_d3"
};

static const chaw * const dpi0_pawents[] = {
	"cwk26m",
	"tvdpww_d2",
	"tvdpww_d4",
	"tvdpww_d8",
	"tvdpww_d16",
	"univpww_d5_d2",
	"univpww_d3_d4",
	"syspww_d3_d4",
	"univpww_d3_d8"
};

static const chaw * const scam_pawents[] = {
	"cwk26m",
	"syspww_d5_d2"
};

static const chaw * const disppwm_pawents[] = {
	"cwk26m",
	"univpww_d3_d4",
	"osc_d2",
	"osc_d4",
	"osc_d16"
};

static const chaw * const usb_top_pawents[] = {
	"cwk26m",
	"univpww_d5_d4",
	"univpww_d3_d4",
	"univpww_d5_d2"
};


static const chaw * const ssusb_top_xhci_pawents[] = {
	"cwk26m",
	"univpww_d5_d4",
	"univpww_d3_d4",
	"univpww_d5_d2"
};

static const chaw * const spm_pawents[] = {
	"cwk26m",
	"syspww_d2_d8"
};

static const chaw * const i2c_pawents[] = {
	"cwk26m",
	"syspww_d2_d8",
	"univpww_d5_d2"
};

static const chaw * const scp_pawents[] = {
	"cwk26m",
	"univpww_d2_d8",
	"syspww_d5",
	"syspww_d2_d2",
	"univpww_d2_d2",
	"syspww_d3",
	"univpww_d3"
};

static const chaw * const seninf_pawents[] = {
	"cwk26m",
	"univpww_d2_d2",
	"univpww_d3_d2",
	"univpww_d2_d4"
};

static const chaw * const dxcc_pawents[] = {
	"cwk26m",
	"syspww_d2_d2",
	"syspww_d2_d4",
	"syspww_d2_d8"
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

static const chaw * const faes_ufsfde_pawents[] = {
	"cwk26m",
	"syspww_d2",
	"syspww_d2_d2",
	"syspww_d3",
	"syspww_d2_d4",
	"univpww_d3"
};

static const chaw * const fufs_pawents[] = {
	"cwk26m",
	"syspww_d2_d4",
	"syspww_d2_d8",
	"syspww_d2_d16"
};

static const chaw * const aud_1_pawents[] = {
	"cwk26m",
	"apww1_ck"
};

static const chaw * const aud_2_pawents[] = {
	"cwk26m",
	"apww2_ck"
};

/*
 * CWITICAW CWOCK:
 * axi_sew is the main bus cwock of whowe SOC.
 * spm_sew is the cwock of the awways-on co-pwocessow.
 */
static const stwuct mtk_mux top_muxes[] = {
	/* CWK_CFG_0 */
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_MUX_AXI, "axi_sew",
		axi_pawents, 0x40, 0x44, 0x48, 0, 2, 7, 0x004, 0,
				   CWK_IS_CWITICAW | CWK_SET_WATE_PAWENT),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_MUX_MM, "mm_sew",
		mm_pawents, 0x40, 0x44, 0x48, 8, 3, 15, 0x004, 1),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_MUX_IMG, "img_sew",
		img_pawents, 0x40, 0x44, 0x48, 16, 3, 23, 0x004, 2),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_MUX_CAM, "cam_sew",
		cam_pawents, 0x40, 0x44, 0x48, 24, 4, 31, 0x004, 3),
	/* CWK_CFG_1 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_MUX_DSP, "dsp_sew",
		dsp_pawents, 0x50, 0x54, 0x58, 0, 4, 7, 0x004, 4),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_MUX_DSP1, "dsp1_sew",
		dsp1_pawents, 0x50, 0x54, 0x58, 8, 4, 15, 0x004, 5),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_MUX_DSP2, "dsp2_sew",
		dsp2_pawents, 0x50, 0x54, 0x58, 16, 4, 23, 0x004, 6),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_MUX_IPU_IF, "ipu_if_sew",
		ipu_if_pawents, 0x50, 0x54, 0x58, 24, 4, 31, 0x004, 7),
	/* CWK_CFG_2 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_MUX_MFG, "mfg_sew",
		mfg_pawents, 0x60, 0x64, 0x68, 0, 2, 7, 0x004, 8),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_MUX_F52M_MFG, "f52m_mfg_sew",
		f52m_mfg_pawents, 0x60, 0x64, 0x68, 8, 2, 15, 0x004, 9),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_MUX_CAMTG, "camtg_sew",
		camtg_pawents, 0x60, 0x64, 0x68, 16, 3, 23, 0x004, 10),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_MUX_CAMTG2, "camtg2_sew",
		camtg2_pawents, 0x60, 0x64, 0x68, 24, 3, 31, 0x004, 11),
	/* CWK_CFG_3 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_MUX_CAMTG3, "camtg3_sew",
		camtg3_pawents, 0x70, 0x74, 0x78, 0, 3, 7, 0x004, 12),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_MUX_CAMTG4, "camtg4_sew",
		camtg4_pawents, 0x70, 0x74, 0x78, 8, 3, 15, 0x004, 13),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_MUX_UAWT, "uawt_sew",
		uawt_pawents, 0x70, 0x74, 0x78, 16, 1, 23, 0x004, 14),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_MUX_SPI, "spi_sew",
		spi_pawents, 0x70, 0x74, 0x78, 24, 2, 31, 0x004, 15),
	/* CWK_CFG_4 */
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_MUX_MSDC50_0_HCWK, "msdc50_hcwk_sew",
		msdc50_hcwk_pawents, 0x80, 0x84, 0x88, 0, 2, 7, 0x004, 16, 0),
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_MUX_MSDC50_0, "msdc50_0_sew",
		msdc50_0_pawents, 0x80, 0x84, 0x88, 8, 3, 15, 0x004, 17, 0),
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_MUX_MSDC30_1, "msdc30_1_sew",
		msdc30_1_pawents, 0x80, 0x84, 0x88, 16, 3, 23, 0x004, 18, 0),
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_MUX_MSDC30_2, "msdc30_2_sew",
		msdc30_2_pawents, 0x80, 0x84, 0x88, 24, 3, 31, 0x004, 19, 0),
	/* CWK_CFG_5 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_MUX_AUDIO, "audio_sew",
		audio_pawents, 0x90, 0x94, 0x98, 0, 2, 7, 0x004, 20),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_MUX_AUD_INTBUS, "aud_intbus_sew",
		aud_intbus_pawents, 0x90, 0x94, 0x98, 8, 2, 15, 0x004, 21),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_MUX_PMICSPI, "pmicspi_sew",
		pmicspi_pawents, 0x90, 0x94, 0x98, 16, 2, 23, 0x004, 22),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_MUX_FPWWAP_UWPOSC, "fpwwap_uwposc_sew",
		fpwwap_uwposc_pawents, 0x90, 0x94, 0x98, 24, 2, 31, 0x004, 23),
	/* CWK_CFG_6 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_MUX_ATB, "atb_sew",
		atb_pawents, 0xa0, 0xa4, 0xa8, 0, 2, 7, 0x004, 24),
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_MUX_SSPM, "sspm_sew",
				   sspm_pawents, 0xa0, 0xa4, 0xa8, 8, 3, 15, 0x004, 25,
				   CWK_IS_CWITICAW | CWK_SET_WATE_PAWENT),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_MUX_DPI0, "dpi0_sew",
		dpi0_pawents, 0xa0, 0xa4, 0xa8, 16, 4, 23, 0x004, 26),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_MUX_SCAM, "scam_sew",
		scam_pawents, 0xa0, 0xa4, 0xa8, 24, 1, 31, 0x004, 27),
	/* CWK_CFG_7 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_MUX_DISP_PWM, "disppwm_sew",
		disppwm_pawents, 0xb0, 0xb4, 0xb8, 0, 3, 7, 0x004, 28),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_MUX_USB_TOP, "usb_top_sew",
		usb_top_pawents, 0xb0, 0xb4, 0xb8, 8, 2, 15, 0x004, 29),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_MUX_SSUSB_TOP_XHCI, "ssusb_top_xhci_sew",
		ssusb_top_xhci_pawents, 0xb0, 0xb4, 0xb8, 16, 2, 23, 0x004, 30),
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_MUX_SPM, "spm_sew",
		spm_pawents, 0xb0, 0xb4, 0xb8, 24, 1, 31, 0x008, 0,
				   CWK_IS_CWITICAW | CWK_SET_WATE_PAWENT),
	/* CWK_CFG_8 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_MUX_I2C, "i2c_sew",
		i2c_pawents, 0xc0, 0xc4, 0xc8, 0, 2, 7, 0x008, 1),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_MUX_SCP, "scp_sew",
		scp_pawents, 0xc0, 0xc4, 0xc8, 8, 3, 15, 0x008, 2),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_MUX_SENINF, "seninf_sew",
		seninf_pawents, 0xc0, 0xc4, 0xc8, 16, 2, 23, 0x008, 3),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_MUX_DXCC, "dxcc_sew",
		dxcc_pawents, 0xc0, 0xc4, 0xc8, 24, 2, 31, 0x008, 4),
	/* CWK_CFG_9 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_MUX_AUD_ENG1, "aud_eng1_sew",
		aud_engen1_pawents, 0xd0, 0xd4, 0xd8, 0, 2, 7, 0x008, 5),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_MUX_AUD_ENG2, "aud_eng2_sew",
		aud_engen2_pawents, 0xd0, 0xd4, 0xd8, 8, 2, 15, 0x008, 6),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_MUX_FAES_UFSFDE, "faes_ufsfde_sew",
		faes_ufsfde_pawents, 0xd0, 0xd4, 0xd8, 16, 3, 23, 0x008, 7),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_MUX_FUFS, "fufs_sew",
		fufs_pawents, 0xd0, 0xd4, 0xd8, 24, 2, 31, 0x008, 8),
	/* CWK_CFG_10 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_MUX_AUD_1, "aud_1_sew",
		aud_1_pawents, 0xe0, 0xe4, 0xe8, 0, 1, 7, 0x008, 9),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_MUX_AUD_2, "aud_2_sew",
		aud_2_pawents, 0xe0, 0xe4, 0xe8, 8, 1, 15, 0x008, 10),
};

static const chaw * const apww_i2s0_pawents[] = {
	"aud_1_sew",
	"aud_2_sew"
};

static const chaw * const apww_i2s1_pawents[] = {
	"aud_1_sew",
	"aud_2_sew"
};

static const chaw * const apww_i2s2_pawents[] = {
	"aud_1_sew",
	"aud_2_sew"
};

static const chaw * const apww_i2s3_pawents[] = {
	"aud_1_sew",
	"aud_2_sew"
};

static const chaw * const apww_i2s4_pawents[] = {
	"aud_1_sew",
	"aud_2_sew"
};

static const chaw * const apww_i2s5_pawents[] = {
	"aud_1_sew",
	"aud_2_sew"
};

static const chaw * const mcu_mp0_pawents[] = {
	"cwk26m",
	"awmpww_ww",
	"awmpww_div_pww1",
	"awmpww_div_pww2"
};

static const chaw * const mcu_mp2_pawents[] = {
	"cwk26m",
	"awmpww_w",
	"awmpww_div_pww1",
	"awmpww_div_pww2"
};

static const chaw * const mcu_bus_pawents[] = {
	"cwk26m",
	"ccipww",
	"awmpww_div_pww1",
	"awmpww_div_pww2"
};

static stwuct mtk_composite mcu_muxes[] = {
	/* mp0_pww_dividew_cfg */
	MUX(CWK_MCU_MP0_SEW, "mcu_mp0_sew", mcu_mp0_pawents, 0x7A0, 9, 2),
	/* mp2_pww_dividew_cfg */
	MUX(CWK_MCU_MP2_SEW, "mcu_mp2_sew", mcu_mp2_pawents, 0x7A8, 9, 2),
	/* bus_pww_dividew_cfg */
	MUX(CWK_MCU_BUS_SEW, "mcu_bus_sew", mcu_bus_pawents, 0x7C0, 9, 2),
};

static stwuct mtk_composite top_aud_comp[] = {
	MUX(CWK_TOP_MUX_APWW_I2S0, "apww_i2s0_sew", apww_i2s0_pawents, 0x320, 8, 1),
	MUX(CWK_TOP_MUX_APWW_I2S1, "apww_i2s1_sew", apww_i2s1_pawents, 0x320, 9, 1),
	MUX(CWK_TOP_MUX_APWW_I2S2, "apww_i2s2_sew", apww_i2s2_pawents, 0x320, 10, 1),
	MUX(CWK_TOP_MUX_APWW_I2S3, "apww_i2s3_sew", apww_i2s3_pawents, 0x320, 11, 1),
	MUX(CWK_TOP_MUX_APWW_I2S4, "apww_i2s4_sew", apww_i2s4_pawents, 0x320, 12, 1),
	MUX(CWK_TOP_MUX_APWW_I2S5, "apww_i2s5_sew", apww_i2s5_pawents, 0x328, 20, 1),
	DIV_GATE(CWK_TOP_APWW12_DIV0, "apww12_div0", "apww_i2s0_sew", 0x320, 2, 0x324, 8, 0),
	DIV_GATE(CWK_TOP_APWW12_DIV1, "apww12_div1", "apww_i2s1_sew", 0x320, 3, 0x324, 8, 8),
	DIV_GATE(CWK_TOP_APWW12_DIV2, "apww12_div2", "apww_i2s2_sew", 0x320, 4, 0x324, 8, 16),
	DIV_GATE(CWK_TOP_APWW12_DIV3, "apww12_div3", "apww_i2s3_sew", 0x320, 5, 0x324, 8, 24),
	DIV_GATE(CWK_TOP_APWW12_DIV4, "apww12_div4", "apww_i2s4_sew", 0x320, 6, 0x328, 8, 0),
	DIV_GATE(CWK_TOP_APWW12_DIVB, "apww12_divb", "apww12_div4", 0x320, 7, 0x328, 8, 8),
};

static const stwuct mtk_gate_wegs top_cg_wegs = {
	.set_ofs = 0x104,
	.cww_ofs = 0x104,
	.sta_ofs = 0x104,
};

#define GATE_TOP(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &top_cg_wegs, _shift,	\
		&mtk_cwk_gate_ops_no_setcww_inv)

static const stwuct mtk_gate top_cwks[] = {
	/* TOP */
	GATE_TOP(CWK_TOP_AWMPWW_DIV_PWW1, "awmpww_div_pww1", "mainpww", 4),
	GATE_TOP(CWK_TOP_AWMPWW_DIV_PWW2, "awmpww_div_pww2", "univpww", 5),
};

static const stwuct mtk_gate_wegs infwa0_cg_wegs = {
	.set_ofs = 0x80,
	.cww_ofs = 0x84,
	.sta_ofs = 0x90,
};

static const stwuct mtk_gate_wegs infwa1_cg_wegs = {
	.set_ofs = 0x88,
	.cww_ofs = 0x8c,
	.sta_ofs = 0x94,
};

static const stwuct mtk_gate_wegs infwa2_cg_wegs = {
	.set_ofs = 0xa4,
	.cww_ofs = 0xa8,
	.sta_ofs = 0xac,
};

static const stwuct mtk_gate_wegs infwa3_cg_wegs = {
	.set_ofs = 0xc0,
	.cww_ofs = 0xc4,
	.sta_ofs = 0xc8,
};

#define GATE_INFWA0(_id, _name, _pawent, _shift)		\
	GATE_MTK(_id, _name, _pawent, &infwa0_cg_wegs, _shift,	\
		&mtk_cwk_gate_ops_setcww)

#define GATE_INFWA1(_id, _name, _pawent, _shift)		\
	GATE_MTK(_id, _name, _pawent, &infwa1_cg_wegs, _shift,	\
		&mtk_cwk_gate_ops_setcww)

#define GATE_INFWA2(_id, _name, _pawent, _shift)		\
	GATE_MTK(_id, _name, _pawent, &infwa2_cg_wegs, _shift,	\
		&mtk_cwk_gate_ops_setcww)

#define GATE_INFWA2_FWAGS(_id, _name, _pawent, _shift, _fwag)	\
	GATE_MTK_FWAGS(_id, _name, _pawent, &infwa2_cg_wegs, 	\
		       _shift, &mtk_cwk_gate_ops_setcww, _fwag)

#define GATE_INFWA3(_id, _name, _pawent, _shift)		\
	GATE_MTK(_id, _name, _pawent, &infwa3_cg_wegs, _shift,	\
		&mtk_cwk_gate_ops_setcww)

#define GATE_INFWA3_FWAGS(_id, _name, _pawent, _shift, _fwag)	\
	GATE_MTK_FWAGS(_id, _name, _pawent, &infwa3_cg_wegs, 	\
		       _shift, &mtk_cwk_gate_ops_setcww, _fwag)

static const stwuct mtk_gate infwa_cwks[] = {
	/* INFWA0 */
	GATE_INFWA0(CWK_INFWA_PMIC_TMW, "infwa_pmic_tmw", "axi_sew", 0),
	GATE_INFWA0(CWK_INFWA_PMIC_AP, "infwa_pmic_ap", "axi_sew", 1),
	GATE_INFWA0(CWK_INFWA_PMIC_MD, "infwa_pmic_md", "axi_sew", 2),
	GATE_INFWA0(CWK_INFWA_PMIC_CONN, "infwa_pmic_conn", "axi_sew", 3),
	GATE_INFWA0(CWK_INFWA_SCPSYS, "infwa_scp", "scp_sew", 4),
	GATE_INFWA0(CWK_INFWA_SEJ, "infwa_sej", "f_f26m_ck", 5),
	GATE_INFWA0(CWK_INFWA_APXGPT, "infwa_apxgpt", "axi_sew", 6),
	GATE_INFWA0(CWK_INFWA_ICUSB, "infwa_icusb", "axi_sew", 8),
	GATE_INFWA0(CWK_INFWA_GCE, "infwa_gce", "axi_sew", 9),
	GATE_INFWA0(CWK_INFWA_THEWM, "infwa_thewm", "axi_sew", 10),
	GATE_INFWA0(CWK_INFWA_I2C0, "infwa_i2c0", "i2c_sew", 11),
	GATE_INFWA0(CWK_INFWA_I2C1, "infwa_i2c1", "i2c_sew", 12),
	GATE_INFWA0(CWK_INFWA_I2C2, "infwa_i2c2", "i2c_sew", 13),
	GATE_INFWA0(CWK_INFWA_I2C3, "infwa_i2c3", "i2c_sew", 14),
	GATE_INFWA0(CWK_INFWA_PWM_HCWK, "infwa_pwm_hcwk", "axi_sew", 15),
	GATE_INFWA0(CWK_INFWA_PWM1, "infwa_pwm1", "i2c_sew", 16),
	GATE_INFWA0(CWK_INFWA_PWM2, "infwa_pwm2", "i2c_sew", 17),
	GATE_INFWA0(CWK_INFWA_PWM3, "infwa_pwm3", "i2c_sew", 18),
	GATE_INFWA0(CWK_INFWA_PWM4, "infwa_pwm4", "i2c_sew", 19),
	GATE_INFWA0(CWK_INFWA_PWM, "infwa_pwm", "i2c_sew", 21),
	GATE_INFWA0(CWK_INFWA_UAWT0, "infwa_uawt0", "uawt_sew", 22),
	GATE_INFWA0(CWK_INFWA_UAWT1, "infwa_uawt1", "uawt_sew", 23),
	GATE_INFWA0(CWK_INFWA_UAWT2, "infwa_uawt2", "uawt_sew", 24),
	GATE_INFWA0(CWK_INFWA_UAWT3, "infwa_uawt3", "uawt_sew", 25),
	GATE_INFWA0(CWK_INFWA_GCE_26M, "infwa_gce_26m", "axi_sew", 27),
	GATE_INFWA0(CWK_INFWA_CQ_DMA_FPC, "infwa_cqdma_fpc", "axi_sew", 28),
	GATE_INFWA0(CWK_INFWA_BTIF, "infwa_btif", "axi_sew", 31),
	/* INFWA1 */
	GATE_INFWA1(CWK_INFWA_SPI0, "infwa_spi0", "spi_sew", 1),
	GATE_INFWA1(CWK_INFWA_MSDC0, "infwa_msdc0", "msdc50_hcwk_sew", 2),
	GATE_INFWA1(CWK_INFWA_MSDC1, "infwa_msdc1", "axi_sew", 4),
	GATE_INFWA1(CWK_INFWA_MSDC2, "infwa_msdc2", "axi_sew", 5),
	GATE_INFWA1(CWK_INFWA_MSDC0_SCK, "infwa_msdc0_sck", "msdc50_0_sew", 6),
	GATE_INFWA1(CWK_INFWA_DVFSWC, "infwa_dvfswc", "f_f26m_ck", 7),
	GATE_INFWA1(CWK_INFWA_GCPU, "infwa_gcpu", "axi_sew", 8),
	GATE_INFWA1(CWK_INFWA_TWNG, "infwa_twng", "axi_sew", 9),
	GATE_INFWA1(CWK_INFWA_AUXADC, "infwa_auxadc", "f_f26m_ck", 10),
	GATE_INFWA1(CWK_INFWA_CPUM, "infwa_cpum", "axi_sew", 11),
	GATE_INFWA1(CWK_INFWA_CCIF1_AP, "infwa_ccif1_ap", "axi_sew", 12),
	GATE_INFWA1(CWK_INFWA_CCIF1_MD, "infwa_ccif1_md", "axi_sew", 13),
	GATE_INFWA1(CWK_INFWA_AUXADC_MD, "infwa_auxadc_md", "f_f26m_ck", 14),
	GATE_INFWA1(CWK_INFWA_MSDC1_SCK, "infwa_msdc1_sck", "msdc30_1_sew", 16),
	GATE_INFWA1(CWK_INFWA_MSDC2_SCK, "infwa_msdc2_sck", "msdc30_2_sew", 17),
	GATE_INFWA1(CWK_INFWA_AP_DMA, "infwa_apdma", "axi_sew", 18),
	GATE_INFWA1(CWK_INFWA_XIU, "infwa_xiu", "axi_sew", 19),
	GATE_INFWA1(CWK_INFWA_DEVICE_APC, "infwa_device_apc", "axi_sew", 20),
	GATE_INFWA1(CWK_INFWA_CCIF_AP, "infwa_ccif_ap", "axi_sew", 23),
	GATE_INFWA1(CWK_INFWA_DEBUGSYS, "infwa_debugsys", "axi_sew", 24),
	GATE_INFWA1(CWK_INFWA_AUDIO, "infwa_audio", "axi_sew", 25),
	GATE_INFWA1(CWK_INFWA_CCIF_MD, "infwa_ccif_md", "axi_sew", 26),
	GATE_INFWA1(CWK_INFWA_DXCC_SEC_COWE, "infwa_dxcc_sec_cowe", "dxcc_sew", 27),
	GATE_INFWA1(CWK_INFWA_DXCC_AO, "infwa_dxcc_ao", "dxcc_sew", 28),
	GATE_INFWA1(CWK_INFWA_DEVMPU_BCWK, "infwa_devmpu_bcwk", "axi_sew", 30),
	GATE_INFWA1(CWK_INFWA_DWAMC_F26M, "infwa_dwamc_f26m", "f_f26m_ck", 31),
	/* INFWA2 */
	GATE_INFWA2(CWK_INFWA_IWTX, "infwa_iwtx", "f_f26m_ck", 0),
	GATE_INFWA2(CWK_INFWA_USB, "infwa_usb", "usb_top_sew", 1),
	GATE_INFWA2(CWK_INFWA_DISP_PWM, "infwa_disppwm", "axi_sew", 2),
	GATE_INFWA2(CWK_INFWA_CWDMA_BCWK, "infwa_cwdma_bcwk", "axi_sew", 3),
	GATE_INFWA2(CWK_INFWA_AUDIO_26M_BCWK, "infwa_audio_26m_bcwk", "f_f26m_ck", 4),
	GATE_INFWA2(CWK_INFWA_SPI1, "infwa_spi1", "spi_sew", 6),
	GATE_INFWA2(CWK_INFWA_I2C4, "infwa_i2c4", "i2c_sew", 7),
	GATE_INFWA2(CWK_INFWA_MODEM_TEMP_SHAWE, "infwa_md_tmp_shawe", "f_f26m_ck", 8),
	GATE_INFWA2(CWK_INFWA_SPI2, "infwa_spi2", "spi_sew", 9),
	GATE_INFWA2(CWK_INFWA_SPI3, "infwa_spi3", "spi_sew", 10),
	GATE_INFWA2(CWK_INFWA_UNIPWO_SCK, "infwa_unipwo_sck", "ssusb_top_xhci_sew", 11),
	GATE_INFWA2(CWK_INFWA_UNIPWO_TICK, "infwa_unipwo_tick", "fufs_sew", 12),
	GATE_INFWA2(CWK_INFWA_UFS_MP_SAP_BCWK, "infwa_ufs_mp_sap_bck", "fufs_sew", 13),
	GATE_INFWA2(CWK_INFWA_MD32_BCWK, "infwa_md32_bcwk", "axi_sew", 14),
	/* infwa_sspm is main cwock in co-pwocessow, shouwd not be cwosed in Winux. */
	GATE_INFWA2_FWAGS(CWK_INFWA_SSPM, "infwa_sspm", "sspm_sew", 15, CWK_IS_CWITICAW),
	GATE_INFWA2(CWK_INFWA_UNIPWO_MBIST, "infwa_unipwo_mbist", "axi_sew", 16),
	/* infwa_sspm_bus_hcwk is main cwock in co-pwocessow, shouwd not be cwosed in Winux. */
	GATE_INFWA2_FWAGS(CWK_INFWA_SSPM_BUS_HCWK, "infwa_sspm_bus_hcwk", "axi_sew", 17, CWK_IS_CWITICAW),
	GATE_INFWA2(CWK_INFWA_I2C5, "infwa_i2c5", "i2c_sew", 18),
	GATE_INFWA2(CWK_INFWA_I2C5_AWBITEW, "infwa_i2c5_awbitew", "i2c_sew", 19),
	GATE_INFWA2(CWK_INFWA_I2C5_IMM, "infwa_i2c5_imm", "i2c_sew", 20),
	GATE_INFWA2(CWK_INFWA_I2C1_AWBITEW, "infwa_i2c1_awbitew", "i2c_sew", 21),
	GATE_INFWA2(CWK_INFWA_I2C1_IMM, "infwa_i2c1_imm", "i2c_sew", 22),
	GATE_INFWA2(CWK_INFWA_I2C2_AWBITEW, "infwa_i2c2_awbitew", "i2c_sew", 23),
	GATE_INFWA2(CWK_INFWA_I2C2_IMM, "infwa_i2c2_imm", "i2c_sew", 24),
	GATE_INFWA2(CWK_INFWA_SPI4, "infwa_spi4", "spi_sew", 25),
	GATE_INFWA2(CWK_INFWA_SPI5, "infwa_spi5", "spi_sew", 26),
	GATE_INFWA2(CWK_INFWA_CQ_DMA, "infwa_cqdma", "axi_sew", 27),
	GATE_INFWA2(CWK_INFWA_UFS, "infwa_ufs", "fufs_sew", 28),
	GATE_INFWA2(CWK_INFWA_AES_UFSFDE, "infwa_aes_ufsfde", "faes_ufsfde_sew", 29),
	GATE_INFWA2(CWK_INFWA_UFS_TICK, "infwa_ufs_tick", "fufs_sew", 30),
	/* INFWA3 */
	GATE_INFWA3(CWK_INFWA_MSDC0_SEWF, "infwa_msdc0_sewf", "msdc50_0_sew", 0),
	GATE_INFWA3(CWK_INFWA_MSDC1_SEWF, "infwa_msdc1_sewf", "msdc50_0_sew", 1),
	GATE_INFWA3(CWK_INFWA_MSDC2_SEWF, "infwa_msdc2_sewf", "msdc50_0_sew", 2),
	/* infwa_sspm_26m_sewf is main cwock in co-pwocessow, shouwd not be cwosed in Winux. */
	GATE_INFWA3_FWAGS(CWK_INFWA_SSPM_26M_SEWF, "infwa_sspm_26m_sewf", "f_f26m_ck", 3, CWK_IS_CWITICAW),
	/* infwa_sspm_32k_sewf is main cwock in co-pwocessow, shouwd not be cwosed in Winux. */
	GATE_INFWA3_FWAGS(CWK_INFWA_SSPM_32K_SEWF, "infwa_sspm_32k_sewf", "f_f26m_ck", 4, CWK_IS_CWITICAW),
	GATE_INFWA3(CWK_INFWA_UFS_AXI, "infwa_ufs_axi", "axi_sew", 5),
	GATE_INFWA3(CWK_INFWA_I2C6, "infwa_i2c6", "i2c_sew", 6),
	GATE_INFWA3(CWK_INFWA_AP_MSDC0, "infwa_ap_msdc0", "msdc50_hcwk_sew", 7),
	GATE_INFWA3(CWK_INFWA_MD_MSDC0, "infwa_md_msdc0", "msdc50_hcwk_sew", 8),
	GATE_INFWA3(CWK_INFWA_CCIF2_AP, "infwa_ccif2_ap", "axi_sew", 16),
	GATE_INFWA3(CWK_INFWA_CCIF2_MD, "infwa_ccif2_md", "axi_sew", 17),
	GATE_INFWA3(CWK_INFWA_CCIF3_AP, "infwa_ccif3_ap", "axi_sew", 18),
	GATE_INFWA3(CWK_INFWA_CCIF3_MD, "infwa_ccif3_md", "axi_sew", 19),
	GATE_INFWA3(CWK_INFWA_SEJ_F13M, "infwa_sej_f13m", "f_f26m_ck", 20),
	GATE_INFWA3(CWK_INFWA_AES_BCWK, "infwa_aes_bcwk", "axi_sew", 21),
	GATE_INFWA3(CWK_INFWA_I2C7, "infwa_i2c7", "i2c_sew", 22),
	GATE_INFWA3(CWK_INFWA_I2C8, "infwa_i2c8", "i2c_sew", 23),
	GATE_INFWA3(CWK_INFWA_FBIST2FPC, "infwa_fbist2fpc", "msdc50_0_sew", 24),
};

static const stwuct mtk_gate_wegs pewi_cg_wegs = {
	.set_ofs = 0x20c,
	.cww_ofs = 0x20c,
	.sta_ofs = 0x20c,
};

#define GATE_PEWI(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &pewi_cg_wegs, _shift,	\
		&mtk_cwk_gate_ops_no_setcww_inv)

static const stwuct mtk_gate pewi_cwks[] = {
	GATE_PEWI(CWK_PEWI_AXI, "pewi_axi", "axi_sew", 31),
};

static u16 infwa_wst_ofs[] = {
	INFWA_WST0_SET_OFFSET,
	INFWA_WST1_SET_OFFSET,
	INFWA_WST2_SET_OFFSET,
	INFWA_WST3_SET_OFFSET,
};

static const stwuct mtk_cwk_wst_desc cwk_wst_desc = {
	.vewsion = MTK_WST_SET_CWW,
	.wst_bank_ofs = infwa_wst_ofs,
	.wst_bank_nw = AWWAY_SIZE(infwa_wst_ofs),
};

/* Wegistew mux notifiew fow MFG mux */
static int cwk_mt8183_weg_mfg_mux_notifiew(stwuct device *dev, stwuct cwk *cwk)
{
	stwuct mtk_mux_nb *mfg_mux_nb;
	int i;

	mfg_mux_nb = devm_kzawwoc(dev, sizeof(*mfg_mux_nb), GFP_KEWNEW);
	if (!mfg_mux_nb)
		wetuwn -ENOMEM;

	fow (i = 0; i < AWWAY_SIZE(top_muxes); i++)
		if (top_muxes[i].id == CWK_TOP_MUX_MFG)
			bweak;
	if (i == AWWAY_SIZE(top_muxes))
		wetuwn -EINVAW;

	mfg_mux_nb->ops = top_muxes[i].ops;
	mfg_mux_nb->bypass_index = 0; /* Bypass to 26M cwystaw */

	wetuwn devm_mtk_cwk_mux_notifiew_wegistew(dev, cwk, mfg_mux_nb);
}

static const stwuct mtk_cwk_desc infwa_desc = {
	.cwks = infwa_cwks,
	.num_cwks = AWWAY_SIZE(infwa_cwks),
	.wst_desc = &cwk_wst_desc,
};

static const stwuct mtk_cwk_desc mcu_desc = {
	.composite_cwks = mcu_muxes,
	.num_composite_cwks = AWWAY_SIZE(mcu_muxes),
	.cwk_wock = &mt8183_cwk_wock,
};

static const stwuct mtk_cwk_desc pewi_desc = {
	.cwks = pewi_cwks,
	.num_cwks = AWWAY_SIZE(pewi_cwks),
};

static const stwuct mtk_cwk_desc topck_desc = {
	.fixed_cwks = top_fixed_cwks,
	.num_fixed_cwks = AWWAY_SIZE(top_fixed_cwks),
	.factow_cwks = top_divs,
	.num_factow_cwks = AWWAY_SIZE(top_divs),
	.mux_cwks = top_muxes,
	.num_mux_cwks = AWWAY_SIZE(top_muxes),
	.composite_cwks = top_aud_comp,
	.num_composite_cwks = AWWAY_SIZE(top_aud_comp),
	.cwks = top_cwks,
	.num_cwks = AWWAY_SIZE(top_cwks),
	.cwk_wock = &mt8183_cwk_wock,
	.cwk_notifiew_func = cwk_mt8183_weg_mfg_mux_notifiew,
	.mfg_cwk_idx = CWK_TOP_MUX_MFG,
};

static const stwuct of_device_id of_match_cwk_mt8183[] = {
	{ .compatibwe = "mediatek,mt8183-infwacfg", .data = &infwa_desc },
	{ .compatibwe = "mediatek,mt8183-mcucfg", .data = &mcu_desc },
	{ .compatibwe = "mediatek,mt8183-pewicfg", .data = &pewi_desc, },
	{ .compatibwe = "mediatek,mt8183-topckgen", .data = &topck_desc },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt8183);

static stwuct pwatfowm_dwivew cwk_mt8183_dwv = {
	.pwobe = mtk_cwk_simpwe_pwobe,
	.wemove_new = mtk_cwk_simpwe_wemove,
	.dwivew = {
		.name = "cwk-mt8183",
		.of_match_tabwe = of_match_cwk_mt8183,
	},
};
moduwe_pwatfowm_dwivew(cwk_mt8183_dwv)
MODUWE_WICENSE("GPW");
