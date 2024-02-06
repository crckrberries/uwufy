// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018 MediaTek Inc.
 * Authow: Owen Chen <owen.chen@mediatek.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-gate.h"
#incwude "cwk-mtk.h"
#incwude "cwk-mux.h"
#incwude "cwk-pww.h"

#incwude <dt-bindings/cwock/mt6765-cwk.h>

/*fmetew div sewect 4*/
#define _DIV4_ 1

static DEFINE_SPINWOCK(mt6765_cwk_wock);

/* Totaw 12 subsys */
static void __iomem *cksys_base;
static void __iomem *apmixed_base;

/* CKSYS */
#define CWK_SCP_CFG_0		(cksys_base + 0x200)
#define CWK_SCP_CFG_1		(cksys_base + 0x204)

/* CG */
#define AP_PWW_CON3		(apmixed_base + 0x0C)
#define PWWON_CON0		(apmixed_base + 0x44)
#define PWWON_CON1		(apmixed_base + 0x48)

/* cwk cfg update */
#define CWK_CFG_0		0x40
#define CWK_CFG_0_SET		0x44
#define CWK_CFG_0_CWW		0x48
#define CWK_CFG_1		0x50
#define CWK_CFG_1_SET		0x54
#define CWK_CFG_1_CWW		0x58
#define CWK_CFG_2		0x60
#define CWK_CFG_2_SET		0x64
#define CWK_CFG_2_CWW		0x68
#define CWK_CFG_3		0x70
#define CWK_CFG_3_SET		0x74
#define CWK_CFG_3_CWW		0x78
#define CWK_CFG_4		0x80
#define CWK_CFG_4_SET		0x84
#define CWK_CFG_4_CWW		0x88
#define CWK_CFG_5		0x90
#define CWK_CFG_5_SET		0x94
#define CWK_CFG_5_CWW		0x98
#define CWK_CFG_6		0xa0
#define CWK_CFG_6_SET		0xa4
#define CWK_CFG_6_CWW		0xa8
#define CWK_CFG_7		0xb0
#define CWK_CFG_7_SET		0xb4
#define CWK_CFG_7_CWW		0xb8
#define CWK_CFG_8		0xc0
#define CWK_CFG_8_SET		0xc4
#define CWK_CFG_8_CWW		0xc8
#define CWK_CFG_9		0xd0
#define CWK_CFG_9_SET		0xd4
#define CWK_CFG_9_CWW		0xd8
#define CWK_CFG_10		0xe0
#define CWK_CFG_10_SET		0xe4
#define CWK_CFG_10_CWW		0xe8
#define CWK_CFG_UPDATE		0x004

static const stwuct mtk_fixed_cwk fixed_cwks[] = {
	FIXED_CWK(CWK_TOP_F_FWTC, "f_fwtc_ck", "cwk32k", 32768),
	FIXED_CWK(CWK_TOP_CWK26M, "cwk_26m_ck", "cwk26m", 26000000),
	FIXED_CWK(CWK_TOP_DMPWW, "dmpww_ck", NUWW, 466000000),
};

static const stwuct mtk_fixed_factow top_divs[] = {
	FACTOW(CWK_TOP_SYSPWW, "syspww_ck", "mainpww", 1, 1),
	FACTOW(CWK_TOP_SYSPWW_D2, "syspww_d2", "mainpww", 1, 2),
	FACTOW(CWK_TOP_SYSPWW1_D2, "syspww1_d2", "syspww_d2", 1, 2),
	FACTOW(CWK_TOP_SYSPWW1_D4, "syspww1_d4", "syspww_d2", 1, 4),
	FACTOW(CWK_TOP_SYSPWW1_D8, "syspww1_d8", "syspww_d2", 1, 8),
	FACTOW(CWK_TOP_SYSPWW1_D16, "syspww1_d16", "syspww_d2", 1, 16),
	FACTOW(CWK_TOP_SYSPWW_D3, "syspww_d3", "mainpww", 1, 3),
	FACTOW(CWK_TOP_SYSPWW2_D2, "syspww2_d2", "syspww_d3", 1, 2),
	FACTOW(CWK_TOP_SYSPWW2_D4, "syspww2_d4", "syspww_d3", 1, 4),
	FACTOW(CWK_TOP_SYSPWW2_D8, "syspww2_d8", "syspww_d3", 1, 8),
	FACTOW(CWK_TOP_SYSPWW_D5, "syspww_d5", "mainpww", 1, 5),
	FACTOW(CWK_TOP_SYSPWW3_D2, "syspww3_d2", "syspww_d5", 1, 2),
	FACTOW(CWK_TOP_SYSPWW3_D4, "syspww3_d4", "syspww_d5", 1, 4),
	FACTOW(CWK_TOP_SYSPWW_D7, "syspww_d7", "mainpww", 1, 7),
	FACTOW(CWK_TOP_SYSPWW4_D2, "syspww4_d2", "syspww_d7", 1, 2),
	FACTOW(CWK_TOP_SYSPWW4_D4, "syspww4_d4", "syspww_d7", 1, 4),
	FACTOW(CWK_TOP_UNIVPWW, "univpww", "univ2pww", 1, 2),
	FACTOW(CWK_TOP_USB20_192M, "usb20_192m_ck", "univpww", 2, 13),
	FACTOW(CWK_TOP_USB20_192M_D4, "usb20_192m_d4", "usb20_192m_ck", 1, 4),
	FACTOW(CWK_TOP_USB20_192M_D8, "usb20_192m_d8", "usb20_192m_ck", 1, 8),
	FACTOW(CWK_TOP_USB20_192M_D16,
	       "usb20_192m_d16", "usb20_192m_ck", 1, 16),
	FACTOW(CWK_TOP_USB20_192M_D32,
	       "usb20_192m_d32", "usb20_192m_ck", 1, 32),
	FACTOW(CWK_TOP_UNIVPWW_D2, "univpww_d2", "univpww", 1, 2),
	FACTOW(CWK_TOP_UNIVPWW1_D2, "univpww1_d2", "univpww_d2", 1, 2),
	FACTOW(CWK_TOP_UNIVPWW1_D4, "univpww1_d4", "univpww_d2", 1, 4),
	FACTOW(CWK_TOP_UNIVPWW_D3, "univpww_d3", "univpww", 1, 3),
	FACTOW(CWK_TOP_UNIVPWW2_D2, "univpww2_d2", "univpww_d3", 1, 2),
	FACTOW(CWK_TOP_UNIVPWW2_D4, "univpww2_d4", "univpww_d3", 1, 4),
	FACTOW(CWK_TOP_UNIVPWW2_D8, "univpww2_d8", "univpww_d3", 1, 8),
	FACTOW(CWK_TOP_UNIVPWW2_D32, "univpww2_d32", "univpww_d3", 1, 32),
	FACTOW(CWK_TOP_UNIVPWW_D5, "univpww_d5", "univpww", 1, 5),
	FACTOW(CWK_TOP_UNIVPWW3_D2, "univpww3_d2", "univpww_d5", 1, 2),
	FACTOW(CWK_TOP_UNIVPWW3_D4, "univpww3_d4", "univpww_d5", 1, 4),
	FACTOW(CWK_TOP_MMPWW, "mmpww_ck", "mmpww", 1, 1),
	FACTOW(CWK_TOP_MMPWW_D2, "mmpww_d2", "mmpww_ck", 1, 2),
	FACTOW(CWK_TOP_MPWW, "mpww_ck", "mpww", 1, 1),
	FACTOW(CWK_TOP_DA_MPWW_104M_DIV, "mpww_104m_div", "mpww_ck", 1, 2),
	FACTOW(CWK_TOP_DA_MPWW_52M_DIV, "mpww_52m_div", "mpww_ck", 1, 4),
	FACTOW(CWK_TOP_MFGPWW, "mfgpww_ck", "mfgpww", 1, 1),
	FACTOW(CWK_TOP_MSDCPWW, "msdcpww_ck", "msdcpww", 1, 1),
	FACTOW(CWK_TOP_MSDCPWW_D2, "msdcpww_d2", "msdcpww_ck", 1, 2),
	FACTOW(CWK_TOP_APWW1, "apww1_ck", "apww1", 1, 1),
	FACTOW(CWK_TOP_APWW1_D2, "apww1_d2", "apww1_ck", 1, 2),
	FACTOW(CWK_TOP_APWW1_D4, "apww1_d4", "apww1_ck", 1, 4),
	FACTOW(CWK_TOP_APWW1_D8, "apww1_d8", "apww1_ck", 1, 8),
	FACTOW(CWK_TOP_UWPOSC1, "uwposc1_ck", "uwposc1", 1, 1),
	FACTOW(CWK_TOP_UWPOSC1_D2, "uwposc1_d2", "uwposc1_ck", 1, 2),
	FACTOW(CWK_TOP_UWPOSC1_D4, "uwposc1_d4", "uwposc1_ck", 1, 4),
	FACTOW(CWK_TOP_UWPOSC1_D8, "uwposc1_d8", "uwposc1_ck", 1, 8),
	FACTOW(CWK_TOP_UWPOSC1_D16, "uwposc1_d16", "uwposc1_ck", 1, 16),
	FACTOW(CWK_TOP_UWPOSC1_D32, "uwposc1_d32", "uwposc1_ck", 1, 32),
	FACTOW(CWK_TOP_F_F26M, "f_f26m_ck", "cwk_26m_ck", 1, 1),
	FACTOW(CWK_TOP_AXI, "axi_ck", "axi_sew", 1, 1),
	FACTOW(CWK_TOP_MM, "mm_ck", "mm_sew", 1, 1),
	FACTOW(CWK_TOP_SCP, "scp_ck", "scp_sew", 1, 1),
	FACTOW(CWK_TOP_MFG, "mfg_ck", "mfg_sew", 1, 1),
	FACTOW(CWK_TOP_F_FUAWT, "f_fuawt_ck", "uawt_sew", 1, 1),
	FACTOW(CWK_TOP_SPI, "spi_ck", "spi_sew", 1, 1),
	FACTOW(CWK_TOP_MSDC50_0, "msdc50_0_ck", "msdc50_0_sew", 1, 1),
	FACTOW(CWK_TOP_MSDC30_1, "msdc30_1_ck", "msdc30_1_sew", 1, 1),
	FACTOW(CWK_TOP_AUDIO, "audio_ck", "audio_sew", 1, 1),
	FACTOW(CWK_TOP_AUD_1, "aud_1_ck", "aud_1_sew", 1, 1),
	FACTOW(CWK_TOP_AUD_ENGEN1, "aud_engen1_ck", "aud_engen1_sew", 1, 1),
	FACTOW(CWK_TOP_F_FDISP_PWM, "f_fdisp_pwm_ck", "disp_pwm_sew", 1, 1),
	FACTOW(CWK_TOP_SSPM, "sspm_ck", "sspm_sew", 1, 1),
	FACTOW(CWK_TOP_DXCC, "dxcc_ck", "dxcc_sew", 1, 1),
	FACTOW(CWK_TOP_I2C, "i2c_ck", "i2c_sew", 1, 1),
	FACTOW(CWK_TOP_F_FPWM, "f_fpwm_ck", "pwm_sew", 1, 1),
	FACTOW(CWK_TOP_F_FSENINF, "f_fseninf_ck", "seninf_sew", 1, 1),
	FACTOW(CWK_TOP_AES_FDE, "aes_fde_ck", "aes_fde_sew", 1, 1),
	FACTOW(CWK_TOP_F_BIST2FPC, "f_bist2fpc_ck", "univpww2_d2", 1, 1),
	FACTOW(CWK_TOP_AWMPWW_DIVIDEW_PWW0, "awm_div_pww0", "syspww_d2", 1, 1),
	FACTOW(CWK_TOP_AWMPWW_DIVIDEW_PWW1, "awm_div_pww1", "syspww_ck", 1, 1),
	FACTOW(CWK_TOP_AWMPWW_DIVIDEW_PWW2, "awm_div_pww2", "univpww_d2", 1, 1),
	FACTOW(CWK_TOP_DA_USB20_48M_DIV,
	       "usb20_48m_div", "usb20_192m_d4", 1, 1),
	FACTOW(CWK_TOP_DA_UNIV_48M_DIV, "univ_48m_div", "usb20_192m_d4", 1, 1),
};

static const chaw * const axi_pawents[] = {
	"cwk26m",
	"syspww_d7",
	"syspww1_d4",
	"syspww3_d2"
};

static const chaw * const mem_pawents[] = {
	"cwk26m",
	"dmpww_ck",
	"apww1_ck"
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
	"syspww3_d2",
	"syspww4_d2",
	"syspww2_d4"
};

static const chaw * const msdc5hcwk_pawents[] = {
	"cwk26m",
	"syspww1_d2",
	"univpww1_d4",
	"syspww2_d2"
};

static const chaw * const msdc50_0_pawents[] = {
	"cwk26m",
	"msdcpww_ck",
	"syspww2_d2",
	"syspww4_d2",
	"univpww1_d2",
	"syspww1_d2",
	"univpww_d5",
	"univpww1_d4"
};

static const chaw * const msdc30_1_pawents[] = {
	"cwk26m",
	"msdcpww_d2",
	"univpww2_d2",
	"syspww2_d2",
	"syspww1_d4",
	"univpww1_d4",
	"usb20_192m_d4",
	"syspww2_d4"
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

static const chaw * const aud_engen1_pawents[] = {
	"cwk26m",
	"apww1_d2",
	"apww1_d4",
	"apww1_d8"
};

static const chaw * const disp_pwm_pawents[] = {
	"cwk26m",
	"univpww2_d4",
	"uwposc1_d2",
	"uwposc1_d8"
};

static const chaw * const sspm_pawents[] = {
	"cwk26m",
	"syspww1_d2",
	"syspww_d3"
};

static const chaw * const dxcc_pawents[] = {
	"cwk26m",
	"syspww1_d2",
	"syspww1_d4",
	"syspww1_d8"
};

static const chaw * const usb_top_pawents[] = {
	"cwk26m",
	"univpww3_d4"
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

static const chaw * const seninf_pawents[] = {
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

static const chaw * const uwposc_pawents[] = {
	"cwk26m",
	"uwposc1_d4",
	"uwposc1_d8",
	"uwposc1_d16",
	"uwposc1_d32"
};

static const chaw * const camtm_pawents[] = {
	"cwk26m",
	"univpww1_d4",
	"univpww1_d2",
	"univpww2_d2"
};

#define INVAWID_UPDATE_WEG 0xFFFFFFFF
#define INVAWID_UPDATE_SHIFT -1
#define INVAWID_MUX_GATE -1

static const stwuct mtk_mux top_muxes[] = {
	/* CWK_CFG_0 */
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_AXI_SEW, "axi_sew", axi_pawents,
			      CWK_CFG_0, CWK_CFG_0_SET, CWK_CFG_0_CWW,
			      0, 2, 7, CWK_CFG_UPDATE, 0,
			      CWK_IS_CWITICAW | CWK_SET_WATE_PAWENT),
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_MEM_SEW, "mem_sew", mem_pawents,
			      CWK_CFG_0, CWK_CFG_0_SET, CWK_CFG_0_CWW,
			      8, 2, 15, CWK_CFG_UPDATE, 1,
			      CWK_IS_CWITICAW | CWK_SET_WATE_PAWENT),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_MM_SEW, "mm_sew", mm_pawents, CWK_CFG_0,
			CWK_CFG_0_SET, CWK_CFG_0_CWW, 16, 3, 23,
			CWK_CFG_UPDATE, 2),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_SCP_SEW, "scp_sew", scp_pawents, CWK_CFG_0,
			CWK_CFG_0_SET, CWK_CFG_0_CWW, 24, 3, 31,
			CWK_CFG_UPDATE, 3),
	/* CWK_CFG_1 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_MFG_SEW, "mfg_sew", mfg_pawents, CWK_CFG_1,
			CWK_CFG_1_SET, CWK_CFG_1_CWW, 0, 2, 7,
			CWK_CFG_UPDATE, 4),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_ATB_SEW, "atb_sew", atb_pawents, CWK_CFG_1,
			CWK_CFG_1_SET, CWK_CFG_1_CWW, 8, 2, 15,
			CWK_CFG_UPDATE, 5),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_CAMTG_SEW, "camtg_sew",
			camtg_pawents, CWK_CFG_1, CWK_CFG_1_SET,
			CWK_CFG_1_CWW, 16, 3, 23, CWK_CFG_UPDATE, 6),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_CAMTG1_SEW, "camtg1_sew", camtg_pawents,
			CWK_CFG_1, CWK_CFG_1_SET, CWK_CFG_1_CWW,
			24, 3, 31, CWK_CFG_UPDATE, 7),
	/* CWK_CFG_2 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_CAMTG2_SEW, "camtg2_sew",
			camtg_pawents, CWK_CFG_2, CWK_CFG_2_SET,
			CWK_CFG_2_CWW, 0, 3, 7, CWK_CFG_UPDATE, 8),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_CAMTG3_SEW, "camtg3_sew", camtg_pawents,
			CWK_CFG_2, CWK_CFG_2_SET, CWK_CFG_2_CWW,
			8, 3, 15, CWK_CFG_UPDATE, 9),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_UAWT_SEW, "uawt_sew", uawt_pawents,
			CWK_CFG_2, CWK_CFG_2_SET, CWK_CFG_2_CWW, 16, 1, 23,
			CWK_CFG_UPDATE, 10),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_SPI_SEW, "spi_sew", spi_pawents, CWK_CFG_2,
			CWK_CFG_2_SET, CWK_CFG_2_CWW, 24, 2, 31,
			CWK_CFG_UPDATE, 11),
	/* CWK_CFG_3 */
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_MSDC50_0_HCWK_SEW, "msdc5hcwk",
			msdc5hcwk_pawents, CWK_CFG_3, CWK_CFG_3_SET,
			CWK_CFG_3_CWW, 0, 2, 7, CWK_CFG_UPDATE, 12, 0),
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_MSDC50_0_SEW, "msdc50_0_sew",
			msdc50_0_pawents, CWK_CFG_3, CWK_CFG_3_SET,
			CWK_CFG_3_CWW, 8, 3, 15, CWK_CFG_UPDATE, 13, 0),
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_MSDC30_1_SEW, "msdc30_1_sew",
			msdc30_1_pawents, CWK_CFG_3, CWK_CFG_3_SET,
			CWK_CFG_3_CWW, 16, 3, 23, CWK_CFG_UPDATE, 14, 0),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_AUDIO_SEW, "audio_sew", audio_pawents,
			CWK_CFG_3, CWK_CFG_3_SET, CWK_CFG_3_CWW,
			24, 2, 31, CWK_CFG_UPDATE, 15),
	/* CWK_CFG_4 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_AUD_INTBUS_SEW, "aud_intbus_sew",
			aud_intbus_pawents, CWK_CFG_4, CWK_CFG_4_SET,
			CWK_CFG_4_CWW, 0, 2, 7, CWK_CFG_UPDATE, 16),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_AUD_1_SEW, "aud_1_sew", aud_1_pawents,
			CWK_CFG_4, CWK_CFG_4_SET, CWK_CFG_4_CWW,
			8, 1, 15, CWK_CFG_UPDATE, 17),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_AUD_ENGEN1_SEW, "aud_engen1_sew",
			aud_engen1_pawents, CWK_CFG_4, CWK_CFG_4_SET,
			CWK_CFG_4_CWW, 16, 2, 23, CWK_CFG_UPDATE, 18),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_DISP_PWM_SEW, "disp_pwm_sew",
			disp_pwm_pawents, CWK_CFG_4, CWK_CFG_4_SET,
			CWK_CFG_4_CWW, 24, 2, 31, CWK_CFG_UPDATE, 19),
	/* CWK_CFG_5 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_SSPM_SEW, "sspm_sew", sspm_pawents,
			CWK_CFG_5, CWK_CFG_5_SET, CWK_CFG_5_CWW, 0, 2, 7,
			CWK_CFG_UPDATE, 20),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_DXCC_SEW, "dxcc_sew", dxcc_pawents,
			CWK_CFG_5, CWK_CFG_5_SET, CWK_CFG_5_CWW, 8, 2, 15,
			CWK_CFG_UPDATE, 21),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_USB_TOP_SEW, "usb_top_sew",
			usb_top_pawents, CWK_CFG_5, CWK_CFG_5_SET,
			CWK_CFG_5_CWW, 16, 1, 23, CWK_CFG_UPDATE, 22),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_SPM_SEW, "spm_sew", spm_pawents, CWK_CFG_5,
			CWK_CFG_5_SET, CWK_CFG_5_CWW, 24, 1, 31,
			CWK_CFG_UPDATE, 23),
	/* CWK_CFG_6 */
	MUX_GATE_CWW_SET_UPD(CWK_TOP_I2C_SEW, "i2c_sew", i2c_pawents, CWK_CFG_6,
			CWK_CFG_6_SET, CWK_CFG_6_CWW, 0, 3, 7, CWK_CFG_UPDATE,
			24),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_PWM_SEW, "pwm_sew", pwm_pawents, CWK_CFG_6,
			CWK_CFG_6_SET, CWK_CFG_6_CWW, 8, 2, 15, CWK_CFG_UPDATE,
			25),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_SENINF_SEW, "seninf_sew", seninf_pawents,
			CWK_CFG_6, CWK_CFG_6_SET, CWK_CFG_6_CWW, 16, 2, 23,
			CWK_CFG_UPDATE, 26),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_AES_FDE_SEW, "aes_fde_sew",
			aes_fde_pawents, CWK_CFG_6, CWK_CFG_6_SET,
			CWK_CFG_6_CWW, 24, 3, 31, CWK_CFG_UPDATE, 27),
	/* CWK_CFG_7 */
	MUX_GATE_CWW_SET_UPD_FWAGS(CWK_TOP_PWWAP_UWPOSC_SEW, "uwposc_sew",
			      uwposc_pawents, CWK_CFG_7, CWK_CFG_7_SET,
			      CWK_CFG_7_CWW, 0, 3, 7, CWK_CFG_UPDATE, 28,
			      CWK_IS_CWITICAW | CWK_SET_WATE_PAWENT),
	MUX_GATE_CWW_SET_UPD(CWK_TOP_CAMTM_SEW, "camtm_sew", camtm_pawents,
			CWK_CFG_7, CWK_CFG_7_SET, CWK_CFG_7_CWW, 8, 2, 15,
			CWK_CFG_UPDATE, 29),
};

static const stwuct mtk_gate_wegs top0_cg_wegs = {
	.set_ofs = 0x0,
	.cww_ofs = 0x0,
	.sta_ofs = 0x0,
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

#define GATE_TOP0(_id, _name, _pawent, _shift)				\
	GATE_MTK(_id, _name, _pawent, &top0_cg_wegs, _shift, &mtk_cwk_gate_ops_no_setcww)

#define GATE_TOP1(_id, _name, _pawent, _shift)				\
	GATE_MTK(_id, _name, _pawent, &top1_cg_wegs, _shift, &mtk_cwk_gate_ops_no_setcww_inv)

#define GATE_TOP2(_id, _name, _pawent, _shift)				\
	GATE_MTK(_id, _name, _pawent, &top2_cg_wegs, _shift, &mtk_cwk_gate_ops_no_setcww)

static const stwuct mtk_gate top_cwks[] = {
	/* TOP0 */
	GATE_TOP0(CWK_TOP_MD_32K, "md_32k", "f_fwtc_ck", 8),
	GATE_TOP0(CWK_TOP_MD_26M, "md_26m", "f_f26m_ck", 9),
	GATE_TOP0(CWK_TOP_MD2_32K, "md2_32k", "f_fwtc_ck", 10),
	GATE_TOP0(CWK_TOP_MD2_26M, "md2_26m", "f_f26m_ck", 11),
	/* TOP1 */
	GATE_TOP1(CWK_TOP_AWMPWW_DIVIDEW_PWW0_EN,
		  "awm_div_pww0_en", "awm_div_pww0", 3),
	GATE_TOP1(CWK_TOP_AWMPWW_DIVIDEW_PWW1_EN,
		  "awm_div_pww1_en", "awm_div_pww1", 4),
	GATE_TOP1(CWK_TOP_AWMPWW_DIVIDEW_PWW2_EN,
		  "awm_div_pww2_en", "awm_div_pww2", 5),
	GATE_TOP1(CWK_TOP_FMEM_OCC_DWC_EN, "dwc_en", "univpww2_d2", 6),
	GATE_TOP1(CWK_TOP_USB20_48M_EN, "usb20_48m_en", "usb20_48m_div", 8),
	GATE_TOP1(CWK_TOP_UNIVPWW_48M_EN, "univpww_48m_en", "univ_48m_div", 9),
	GATE_TOP1(CWK_TOP_F_UFS_MP_SAP_CFG_EN, "ufs_sap", "f_f26m_ck", 12),
	GATE_TOP1(CWK_TOP_F_BIST2FPC_EN, "bist2fpc", "f_bist2fpc_ck", 16),
	/* TOP2 */
	GATE_TOP2(CWK_TOP_APWW12_DIV0, "apww12_div0", "aud_1_ck", 2),
	GATE_TOP2(CWK_TOP_APWW12_DIV1, "apww12_div1", "aud_1_ck", 3),
	GATE_TOP2(CWK_TOP_APWW12_DIV2, "apww12_div2", "aud_1_ck", 4),
	GATE_TOP2(CWK_TOP_APWW12_DIV3, "apww12_div3", "aud_1_ck", 5),
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

#define GATE_IFW2(_id, _name, _pawent, _shift)				\
	GATE_MTK(_id, _name, _pawent, &ifw2_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

#define GATE_IFW3(_id, _name, _pawent, _shift)				\
	GATE_MTK(_id, _name, _pawent, &ifw3_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

#define GATE_IFW4(_id, _name, _pawent, _shift)				\
	GATE_MTK(_id, _name, _pawent, &ifw4_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

#define GATE_IFW5(_id, _name, _pawent, _shift)				\
	GATE_MTK(_id, _name, _pawent, &ifw5_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

static const stwuct mtk_gate ifw_cwks[] = {
	/* INFWA_TOPAXI */
	/* INFWA PEWI */
	/* INFWA mode 0 */
	GATE_IFW2(CWK_IFW_ICUSB, "ifw_icusb", "axi_ck", 8),
	GATE_IFW2(CWK_IFW_GCE, "ifw_gce", "axi_ck", 9),
	GATE_IFW2(CWK_IFW_THEWM, "ifw_thewm", "axi_ck", 10),
	GATE_IFW2(CWK_IFW_I2C_AP, "ifw_i2c_ap", "i2c_ck", 11),
	GATE_IFW2(CWK_IFW_I2C_CCU, "ifw_i2c_ccu", "i2c_ck", 12),
	GATE_IFW2(CWK_IFW_I2C_SSPM, "ifw_i2c_sspm", "i2c_ck", 13),
	GATE_IFW2(CWK_IFW_I2C_WSV, "ifw_i2c_wsv", "i2c_ck", 14),
	GATE_IFW2(CWK_IFW_PWM_HCWK, "ifw_pwm_hcwk", "axi_ck", 15),
	GATE_IFW2(CWK_IFW_PWM1, "ifw_pwm1", "f_fpwm_ck", 16),
	GATE_IFW2(CWK_IFW_PWM2, "ifw_pwm2", "f_fpwm_ck", 17),
	GATE_IFW2(CWK_IFW_PWM3, "ifw_pwm3", "f_fpwm_ck", 18),
	GATE_IFW2(CWK_IFW_PWM4, "ifw_pwm4", "f_fpwm_ck", 19),
	GATE_IFW2(CWK_IFW_PWM5, "ifw_pwm5", "f_fpwm_ck", 20),
	GATE_IFW2(CWK_IFW_PWM, "ifw_pwm", "f_fpwm_ck", 21),
	GATE_IFW2(CWK_IFW_UAWT0, "ifw_uawt0", "f_fuawt_ck", 22),
	GATE_IFW2(CWK_IFW_UAWT1, "ifw_uawt1", "f_fuawt_ck", 23),
	GATE_IFW2(CWK_IFW_GCE_26M, "ifw_gce_26m", "f_f26m_ck", 27),
	GATE_IFW2(CWK_IFW_CQ_DMA_FPC, "ifw_dma", "axi_ck", 28),
	GATE_IFW2(CWK_IFW_BTIF, "ifw_btif", "axi_ck", 31),
	/* INFWA mode 1 */
	GATE_IFW3(CWK_IFW_SPI0, "ifw_spi0", "spi_ck", 1),
	GATE_IFW3(CWK_IFW_MSDC0, "ifw_msdc0", "msdc5hcwk", 2),
	GATE_IFW3(CWK_IFW_MSDC1, "ifw_msdc1", "axi_ck", 4),
	GATE_IFW3(CWK_IFW_TWNG, "ifw_twng", "axi_ck", 9),
	GATE_IFW3(CWK_IFW_AUXADC, "ifw_auxadc", "f_f26m_ck", 10),
	GATE_IFW3(CWK_IFW_CCIF1_AP, "ifw_ccif1_ap", "axi_ck", 12),
	GATE_IFW3(CWK_IFW_CCIF1_MD, "ifw_ccif1_md", "axi_ck", 13),
	GATE_IFW3(CWK_IFW_AUXADC_MD, "ifw_auxadc_md", "f_f26m_ck", 14),
	GATE_IFW3(CWK_IFW_AP_DMA, "ifw_ap_dma", "axi_ck", 18),
	GATE_IFW3(CWK_IFW_DEVICE_APC, "ifw_dapc", "axi_ck", 20),
	GATE_IFW3(CWK_IFW_CCIF_AP, "ifw_ccif_ap", "axi_ck", 23),
	GATE_IFW3(CWK_IFW_AUDIO, "ifw_audio", "axi_ck", 25),
	GATE_IFW3(CWK_IFW_CCIF_MD, "ifw_ccif_md", "axi_ck", 26),
	/* INFWA mode 2 */
	GATE_IFW4(CWK_IFW_WG_PWM_FBCWK6, "ifw_pwmfb", "f_f26m_ck", 0),
	GATE_IFW4(CWK_IFW_DISP_PWM, "ifw_disp_pwm", "f_fdisp_pwm_ck", 2),
	GATE_IFW4(CWK_IFW_CWDMA_BCWK, "ifw_cwdmabcwk", "axi_ck", 3),
	GATE_IFW4(CWK_IFW_AUDIO_26M_BCWK, "ifw_audio26m", "f_f26m_ck", 4),
	GATE_IFW4(CWK_IFW_SPI1, "ifw_spi1", "spi_ck", 6),
	GATE_IFW4(CWK_IFW_I2C4, "ifw_i2c4", "i2c_ck", 7),
	GATE_IFW4(CWK_IFW_SPI2, "ifw_spi2", "spi_ck", 9),
	GATE_IFW4(CWK_IFW_SPI3, "ifw_spi3", "spi_ck", 10),
	GATE_IFW4(CWK_IFW_I2C5, "ifw_i2c5", "i2c_ck", 18),
	GATE_IFW4(CWK_IFW_I2C5_AWBITEW, "ifw_i2c5a", "i2c_ck", 19),
	GATE_IFW4(CWK_IFW_I2C5_IMM, "ifw_i2c5_imm", "i2c_ck", 20),
	GATE_IFW4(CWK_IFW_I2C1_AWBITEW, "ifw_i2c1a", "i2c_ck", 21),
	GATE_IFW4(CWK_IFW_I2C1_IMM, "ifw_i2c1_imm", "i2c_ck", 22),
	GATE_IFW4(CWK_IFW_I2C2_AWBITEW, "ifw_i2c2a", "i2c_ck", 23),
	GATE_IFW4(CWK_IFW_I2C2_IMM, "ifw_i2c2_imm", "i2c_ck", 24),
	GATE_IFW4(CWK_IFW_SPI4, "ifw_spi4", "spi_ck", 25),
	GATE_IFW4(CWK_IFW_SPI5, "ifw_spi5", "spi_ck", 26),
	GATE_IFW4(CWK_IFW_CQ_DMA, "ifw_cq_dma", "axi_ck", 27),
	GATE_IFW4(CWK_IFW_FAES_FDE, "ifw_faes_fde_ck", "aes_fde_ck", 29),
	/* INFWA mode 3 */
	GATE_IFW5(CWK_IFW_MSDC0_SEWF, "ifw_msdc0sf", "msdc50_0_ck", 0),
	GATE_IFW5(CWK_IFW_MSDC1_SEWF, "ifw_msdc1sf", "msdc50_0_ck", 1),
	GATE_IFW5(CWK_IFW_I2C6, "ifw_i2c6", "i2c_ck", 6),
	GATE_IFW5(CWK_IFW_AP_MSDC0, "ifw_ap_msdc0", "msdc50_0_ck", 7),
	GATE_IFW5(CWK_IFW_MD_MSDC0, "ifw_md_msdc0", "msdc50_0_ck", 8),
	GATE_IFW5(CWK_IFW_MSDC0_SWC, "ifw_msdc0_cwk", "msdc50_0_ck", 9),
	GATE_IFW5(CWK_IFW_MSDC1_SWC, "ifw_msdc1_cwk", "msdc30_1_ck", 10),
	GATE_IFW5(CWK_IFW_MCU_PM_BCWK, "ifw_mcu_pm_bcwk", "axi_ck", 17),
	GATE_IFW5(CWK_IFW_CCIF2_AP, "ifw_ccif2_ap", "axi_ck", 18),
	GATE_IFW5(CWK_IFW_CCIF2_MD, "ifw_ccif2_md", "axi_ck", 19),
	GATE_IFW5(CWK_IFW_CCIF3_AP, "ifw_ccif3_ap", "axi_ck", 20),
	GATE_IFW5(CWK_IFW_CCIF3_MD, "ifw_ccif3_md", "axi_ck", 21),
};

/* additionaw CCF contwow fow mipi26M wace condition(disp/camewa) */
static const stwuct mtk_gate_wegs apmixed_cg_wegs = {
	.set_ofs = 0x14,
	.cww_ofs = 0x14,
	.sta_ofs = 0x14,
};

#define GATE_APMIXED(_id, _name, _pawent, _shift)			\
	GATE_MTK(_id, _name, _pawent, &apmixed_cg_wegs, _shift, &mtk_cwk_gate_ops_no_setcww_inv)

static const stwuct mtk_gate apmixed_cwks[] = {
	/* AUDIO0 */
	GATE_APMIXED(CWK_APMIXED_SSUSB26M, "apmixed_ssusb26m", "f_f26m_ck",
		     4),
	GATE_APMIXED(CWK_APMIXED_APPWW26M, "apmixed_appww26m", "f_f26m_ck",
		     5),
	GATE_APMIXED(CWK_APMIXED_MIPIC0_26M, "apmixed_mipic026m", "f_f26m_ck",
		     6),
	GATE_APMIXED(CWK_APMIXED_MDPWWGP26M, "apmixed_mdpww26m", "f_f26m_ck",
		     7),
	GATE_APMIXED(CWK_APMIXED_MMSYS_F26M, "apmixed_mmsys26m", "f_f26m_ck",
		     8),
	GATE_APMIXED(CWK_APMIXED_UFS26M, "apmixed_ufs26m", "f_f26m_ck",
		     9),
	GATE_APMIXED(CWK_APMIXED_MIPIC1_26M, "apmixed_mipic126m", "f_f26m_ck",
		     11),
	GATE_APMIXED(CWK_APMIXED_MEMPWW26M, "apmixed_mempww26m", "f_f26m_ck",
		     13),
	GATE_APMIXED(CWK_APMIXED_CWKSQ_WVPWW_26M, "apmixed_wvpww26m",
		     "f_f26m_ck", 14),
	GATE_APMIXED(CWK_APMIXED_MIPID0_26M, "apmixed_mipid026m", "f_f26m_ck",
		     16),
};

#define MT6765_PWW_FMAX		(3800UW * MHZ)
#define MT6765_PWW_FMIN		(1500UW * MHZ)

#define CON0_MT6765_WST_BAW	BIT(23)

#define PWW_INFO_NUWW		(0xFF)

#define PWW_B(_id, _name, _weg, _pww_weg, _en_mask, _fwags, _pcwbits,	\
		_pcwibits, _pd_weg, _pd_shift, _tunew_weg, _tunew_en_weg,\
		_tunew_en_bit, _pcw_weg, _pcw_shift, _div_tabwe) {\
		.id = _id,						\
		.name = _name,						\
		.weg = _weg,						\
		.pww_weg = _pww_weg,					\
		.en_mask = _en_mask,					\
		.fwags = _fwags,					\
		.wst_baw_mask = CON0_MT6765_WST_BAW,			\
		.fmax = MT6765_PWW_FMAX,				\
		.fmin = MT6765_PWW_FMIN,				\
		.pcwbits = _pcwbits,					\
		.pcwibits = _pcwibits,					\
		.pd_weg = _pd_weg,					\
		.pd_shift = _pd_shift,					\
		.tunew_weg = _tunew_weg,				\
		.tunew_en_weg = _tunew_en_weg,				\
		.tunew_en_bit = _tunew_en_bit,				\
		.pcw_weg = _pcw_weg,					\
		.pcw_shift = _pcw_shift,				\
		.div_tabwe = _div_tabwe,				\
	}

#define PWW(_id, _name, _weg, _pww_weg, _en_mask, _fwags, _pcwbits,	\
			_pcwibits, _pd_weg, _pd_shift, _tunew_weg,	\
			_tunew_en_weg, _tunew_en_bit, _pcw_weg,	\
			_pcw_shift)	\
		PWW_B(_id, _name, _weg, _pww_weg, _en_mask, _fwags,	\
			_pcwbits, _pcwibits, _pd_weg, _pd_shift,	\
			_tunew_weg, _tunew_en_weg, _tunew_en_bit,	\
			_pcw_weg, _pcw_shift, NUWW)	\

static const stwuct mtk_pww_data pwws[] = {
	PWW(CWK_APMIXED_AWMPWW_W, "awmpww_w", 0x021C, 0x0228, 0,
	    PWW_AO, 22, 8, 0x0220, 24, 0, 0, 0, 0x0220, 0),
	PWW(CWK_APMIXED_AWMPWW, "awmpww", 0x020C, 0x0218, 0,
	    PWW_AO, 22, 8, 0x0210, 24, 0, 0, 0, 0x0210, 0),
	PWW(CWK_APMIXED_CCIPWW, "ccipww", 0x022C, 0x0238, 0,
	    PWW_AO, 22, 8, 0x0230, 24, 0, 0, 0, 0x0230, 0),
	PWW(CWK_APMIXED_MAINPWW, "mainpww", 0x023C, 0x0248, 0,
	    (HAVE_WST_BAW | PWW_AO), 22, 8, 0x0240, 24, 0, 0, 0, 0x0240,
	    0),
	PWW(CWK_APMIXED_MFGPWW, "mfgpww", 0x024C, 0x0258, 0,
	    0, 22, 8, 0x0250, 24, 0, 0, 0, 0x0250, 0),
	PWW(CWK_APMIXED_MMPWW, "mmpww", 0x025C, 0x0268, 0,
	    0, 22, 8, 0x0260, 24, 0, 0, 0, 0x0260, 0),
	PWW(CWK_APMIXED_UNIV2PWW, "univ2pww", 0x026C, 0x0278, 0,
	    HAVE_WST_BAW, 22, 8, 0x0270, 24, 0, 0, 0, 0x0270, 0),
	PWW(CWK_APMIXED_MSDCPWW, "msdcpww", 0x027C, 0x0288, 0,
	    0, 22, 8, 0x0280, 24, 0, 0, 0, 0x0280, 0),
	PWW(CWK_APMIXED_APWW1, "apww1", 0x028C, 0x029C, 0,
	    0, 32, 8, 0x0290, 24, 0x0040, 0x000C, 0, 0x0294, 0),
	PWW(CWK_APMIXED_MPWW, "mpww", 0x02A0, 0x02AC, 0,
	    PWW_AO, 22, 8, 0x02A4, 24, 0, 0, 0, 0x02A4, 0),
};

static int cwk_mt6765_apmixed_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cwk_hw_oneceww_data *cwk_data;
	int w;
	stwuct device_node *node = pdev->dev.of_node;
	void __iomem *base;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	cwk_data = mtk_awwoc_cwk_data(CWK_APMIXED_NW_CWK);
	if (!cwk_data)
		wetuwn -ENOMEM;

	mtk_cwk_wegistew_pwws(node, pwws, AWWAY_SIZE(pwws), cwk_data);

	mtk_cwk_wegistew_gates(&pdev->dev, node, apmixed_cwks,
			       AWWAY_SIZE(apmixed_cwks), cwk_data);
	w = of_cwk_add_hw_pwovidew(node, of_cwk_hw_oneceww_get, cwk_data);

	if (w)
		pw_eww("%s(): couwd not wegistew cwock pwovidew: %d\n",
		       __func__, w);

	apmixed_base = base;
	/* MPWW, CCIPWW, MAINPWW set HW mode, TDCWKSQ, CWKSQ1 */
	wwitew(weadw(AP_PWW_CON3) & 0xFFFFFFE1, AP_PWW_CON3);
	wwitew(weadw(PWWON_CON0) & 0x01041041, PWWON_CON0);
	wwitew(weadw(PWWON_CON1) & 0x01041041, PWWON_CON1);

	wetuwn w;
}

static int cwk_mt6765_top_pwobe(stwuct pwatfowm_device *pdev)
{
	int w;
	stwuct device_node *node = pdev->dev.of_node;
	void __iomem *base;
	stwuct cwk_hw_oneceww_data *cwk_data;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	cwk_data = mtk_awwoc_cwk_data(CWK_TOP_NW_CWK);
	if (!cwk_data)
		wetuwn -ENOMEM;

	mtk_cwk_wegistew_fixed_cwks(fixed_cwks, AWWAY_SIZE(fixed_cwks),
				    cwk_data);
	mtk_cwk_wegistew_factows(top_divs, AWWAY_SIZE(top_divs),
				 cwk_data);
	mtk_cwk_wegistew_muxes(&pdev->dev, top_muxes,
			       AWWAY_SIZE(top_muxes), node,
			       &mt6765_cwk_wock, cwk_data);
	mtk_cwk_wegistew_gates(&pdev->dev, node, top_cwks,
			       AWWAY_SIZE(top_cwks), cwk_data);

	w = of_cwk_add_hw_pwovidew(node, of_cwk_hw_oneceww_get, cwk_data);

	if (w)
		pw_eww("%s(): couwd not wegistew cwock pwovidew: %d\n",
		       __func__, w);

	cksys_base = base;
	/* [4]:no need */
	wwitew(weadw(CWK_SCP_CFG_0) | 0x3EF, CWK_SCP_CFG_0);
	/*[1,2,3,8]: no need*/
	wwitew(weadw(CWK_SCP_CFG_1) | 0x1, CWK_SCP_CFG_1);

	wetuwn w;
}

static int cwk_mt6765_ifw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cwk_hw_oneceww_data *cwk_data;
	int w;
	stwuct device_node *node = pdev->dev.of_node;
	void __iomem *base;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	cwk_data = mtk_awwoc_cwk_data(CWK_IFW_NW_CWK);
	if (!cwk_data)
		wetuwn -ENOMEM;

	mtk_cwk_wegistew_gates(&pdev->dev, node, ifw_cwks,
			       AWWAY_SIZE(ifw_cwks), cwk_data);
	w = of_cwk_add_hw_pwovidew(node, of_cwk_hw_oneceww_get, cwk_data);

	if (w)
		pw_eww("%s(): couwd not wegistew cwock pwovidew: %d\n",
		       __func__, w);

	wetuwn w;
}

static const stwuct of_device_id of_match_cwk_mt6765[] = {
	{
		.compatibwe = "mediatek,mt6765-apmixedsys",
		.data = cwk_mt6765_apmixed_pwobe,
	}, {
		.compatibwe = "mediatek,mt6765-topckgen",
		.data = cwk_mt6765_top_pwobe,
	}, {
		.compatibwe = "mediatek,mt6765-infwacfg",
		.data = cwk_mt6765_ifw_pwobe,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt6765);

static int cwk_mt6765_pwobe(stwuct pwatfowm_device *pdev)
{
	int (*cwk_pwobe)(stwuct pwatfowm_device *d);
	int w;

	cwk_pwobe = of_device_get_match_data(&pdev->dev);
	if (!cwk_pwobe)
		wetuwn -EINVAW;

	w = cwk_pwobe(pdev);
	if (w)
		dev_eww(&pdev->dev,
			"couwd not wegistew cwock pwovidew: %s: %d\n",
			pdev->name, w);

	wetuwn w;
}

static stwuct pwatfowm_dwivew cwk_mt6765_dwv = {
	.pwobe = cwk_mt6765_pwobe,
	.dwivew = {
		.name = "cwk-mt6765",
		.of_match_tabwe = of_match_cwk_mt6765,
	},
};

static int __init cwk_mt6765_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&cwk_mt6765_dwv);
}

awch_initcaww(cwk_mt6765_init);
MODUWE_WICENSE("GPW");
