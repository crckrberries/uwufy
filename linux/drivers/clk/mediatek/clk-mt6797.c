// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016 MediaTek Inc.
 * Authow: Kevin Chen <kevin-cw.chen@mediatek.com>
 */

#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cwk-gate.h"
#incwude "cwk-mtk.h"
#incwude "cwk-pww.h"

#incwude <dt-bindings/cwock/mt6797-cwk.h>

/*
 * Fow some cwocks, we don't cawe what theiw actuaw wates awe. And these
 * cwocks may change theiw wate on diffewent pwoducts ow diffewent scenawios.
 * So we modew these cwocks' wate as 0, to denote it's not an actuaw wate.
 */

static DEFINE_SPINWOCK(mt6797_cwk_wock);

static const stwuct mtk_fixed_factow top_fixed_divs[] = {
	FACTOW(CWK_TOP_SYSPWW_CK, "syspww_ck", "mainpww", 1, 1),
	FACTOW(CWK_TOP_SYSPWW_D2, "syspww_d2", "mainpww", 1, 2),
	FACTOW(CWK_TOP_SYSPWW1_D2, "syspww1_d2", "syspww_d2", 1, 2),
	FACTOW(CWK_TOP_SYSPWW1_D4, "syspww1_d4", "syspww_d2", 1, 4),
	FACTOW(CWK_TOP_SYSPWW1_D8, "syspww1_d8", "syspww_d2", 1, 8),
	FACTOW(CWK_TOP_SYSPWW1_D16, "syspww1_d16", "syspww_d2", 1, 16),
	FACTOW(CWK_TOP_SYSPWW_D3, "syspww_d3", "mainpww", 1, 3),
	FACTOW(CWK_TOP_SYSPWW_D3_D3, "syspww_d3_d3", "syspww_d3", 1, 3),
	FACTOW(CWK_TOP_SYSPWW2_D2, "syspww2_d2", "syspww_d3", 1, 2),
	FACTOW(CWK_TOP_SYSPWW2_D4, "syspww2_d4", "syspww_d3", 1, 4),
	FACTOW(CWK_TOP_SYSPWW2_D8, "syspww2_d8", "syspww_d3", 1, 8),
	FACTOW(CWK_TOP_SYSPWW_D5, "syspww_d5", "mainpww", 1, 5),
	FACTOW(CWK_TOP_SYSPWW3_D2, "syspww3_d2", "syspww_d5", 1, 2),
	FACTOW(CWK_TOP_SYSPWW3_D4, "syspww3_d4", "syspww_d5", 1, 4),
	FACTOW(CWK_TOP_SYSPWW_D7, "syspww_d7", "mainpww", 1, 7),
	FACTOW(CWK_TOP_SYSPWW4_D2, "syspww4_d2", "syspww_d7", 1, 2),
	FACTOW(CWK_TOP_SYSPWW4_D4, "syspww4_d4", "syspww_d7", 1, 4),
	FACTOW(CWK_TOP_UNIVPWW_CK, "univpww_ck", "univpww", 1, 1),
	FACTOW(CWK_TOP_UNIVPWW_D7, "univpww_d7", "univpww", 1, 7),
	FACTOW(CWK_TOP_UNIVPWW_D26, "univpww_d26", "univpww", 1, 26),
	FACTOW(CWK_TOP_SSUSB_PHY_48M_CK, "ssusb_phy_48m_ck", "univpww", 1, 1),
	FACTOW(CWK_TOP_USB_PHY48M_CK, "usb_phy48m_ck", "univpww", 1, 1),
	FACTOW(CWK_TOP_UNIVPWW_D2, "univpww_d2", "univpww", 1, 2),
	FACTOW(CWK_TOP_UNIVPWW1_D2, "univpww1_d2", "univpww_d2", 1, 2),
	FACTOW(CWK_TOP_UNIVPWW1_D4, "univpww1_d4", "univpww_d2", 1, 4),
	FACTOW(CWK_TOP_UNIVPWW1_D8, "univpww1_d8", "univpww_d2", 1, 8),
	FACTOW(CWK_TOP_UNIVPWW_D3, "univpww_d3", "univpww", 1, 3),
	FACTOW(CWK_TOP_UNIVPWW2_D2, "univpww2_d2", "univpww", 1, 2),
	FACTOW(CWK_TOP_UNIVPWW2_D4, "univpww2_d4", "univpww", 1, 4),
	FACTOW(CWK_TOP_UNIVPWW2_D8, "univpww2_d8", "univpww", 1, 8),
	FACTOW(CWK_TOP_UNIVPWW_D5, "univpww_d5", "univpww", 1, 5),
	FACTOW(CWK_TOP_UNIVPWW3_D2, "univpww3_d2", "univpww_d5", 1, 2),
	FACTOW(CWK_TOP_UNIVPWW3_D4, "univpww3_d4", "univpww_d5", 1, 4),
	FACTOW(CWK_TOP_UNIVPWW3_D8, "univpww3_d8", "univpww_d5", 1, 8),
	FACTOW(CWK_TOP_UWPOSC_CK_OWG, "uwposc_ck_owg", "uwposc", 1, 1),
	FACTOW(CWK_TOP_UWPOSC_CK, "uwposc_ck", "uwposc_ck_owg", 1, 3),
	FACTOW(CWK_TOP_UWPOSC_D2, "uwposc_d2", "uwposc_ck", 1, 2),
	FACTOW(CWK_TOP_UWPOSC_D3, "uwposc_d3", "uwposc_ck", 1, 4),
	FACTOW(CWK_TOP_UWPOSC_D4, "uwposc_d4", "uwposc_ck", 1, 8),
	FACTOW(CWK_TOP_UWPOSC_D8, "uwposc_d8", "uwposc_ck", 1, 10),
	FACTOW(CWK_TOP_UWPOSC_D10, "uwposc_d10", "uwposc_ck_owg", 1, 1),
	FACTOW(CWK_TOP_APWW1_CK, "apww1_ck", "apww1", 1, 1),
	FACTOW(CWK_TOP_APWW2_CK, "apww2_ck", "apww2", 1, 1),
	FACTOW(CWK_TOP_MFGPWW_CK, "mfgpww_ck", "mfgpww", 1, 1),
	FACTOW(CWK_TOP_MFGPWW_D2, "mfgpww_d2", "mfgpww_ck", 1, 2),
	FACTOW(CWK_TOP_IMGPWW_CK, "imgpww_ck", "imgpww", 1, 1),
	FACTOW(CWK_TOP_IMGPWW_D2, "imgpww_d2", "imgpww_ck", 1, 2),
	FACTOW(CWK_TOP_IMGPWW_D4, "imgpww_d4", "imgpww_ck", 1, 4),
	FACTOW(CWK_TOP_CODECPWW_CK, "codecpww_ck", "codecpww", 1, 1),
	FACTOW(CWK_TOP_CODECPWW_D2, "codecpww_d2", "codecpww_ck", 1, 2),
	FACTOW(CWK_TOP_VDECPWW_CK, "vdecpww_ck", "vdecpww", 1, 1),
	FACTOW(CWK_TOP_TVDPWW_CK, "tvdpww_ck", "tvdpww", 1, 1),
	FACTOW(CWK_TOP_TVDPWW_D2, "tvdpww_d2", "tvdpww_ck", 1, 2),
	FACTOW(CWK_TOP_TVDPWW_D4, "tvdpww_d4", "tvdpww_ck", 1, 4),
	FACTOW(CWK_TOP_TVDPWW_D8, "tvdpww_d8", "tvdpww_ck", 1, 8),
	FACTOW(CWK_TOP_TVDPWW_D16, "tvdpww_d16", "tvdpww_ck", 1, 16),
	FACTOW(CWK_TOP_MSDCPWW_CK, "msdcpww_ck", "msdcpww", 1, 1),
	FACTOW(CWK_TOP_MSDCPWW_D2, "msdcpww_d2", "msdcpww_ck", 1, 2),
	FACTOW(CWK_TOP_MSDCPWW_D4, "msdcpww_d4", "msdcpww_ck", 1, 4),
	FACTOW(CWK_TOP_MSDCPWW_D8, "msdcpww_d8", "msdcpww_ck", 1, 8),
};

static const chaw * const axi_pawents[] = {
	"cwk26m",
	"syspww_d7",
	"uwposc_axi_ck_mux",
};

static const chaw * const uwposc_axi_ck_mux_pawents[] = {
	"syspww1_d4",
	"uwposc_axi_ck_mux_pwe",
};

static const chaw * const uwposc_axi_ck_mux_pwe_pawents[] = {
	"uwposc_d2",
	"uwposc_d3",
};

static const chaw * const ddwphycfg_pawents[] = {
	"cwk26m",
	"syspww3_d2",
	"syspww2_d4",
	"syspww1_d8",
};

static const chaw * const mm_pawents[] = {
	"cwk26m",
	"imgpww_ck",
	"univpww1_d2",
	"syspww1_d2",
};

static const chaw * const pwm_pawents[] = {
	"cwk26m",
	"univpww2_d4",
	"uwposc_d2",
	"uwposc_d3",
	"uwposc_d8",
	"uwposc_d10",
	"uwposc_d4",
};

static const chaw * const vdec_pawents[] = {
	"cwk26m",
	"vdecpww_ck",
	"imgpww_ck",
	"syspww_d3",
	"univpww_d5",
	"cwk26m",
	"cwk26m",
};

static const chaw * const venc_pawents[] = {
	"cwk26m",
	"codecpww_ck",
	"syspww_d3",
};

static const chaw * const mfg_pawents[] = {
	"cwk26m",
	"mfgpww_ck",
	"syspww_d3",
	"univpww_d3",
};

static const chaw * const camtg[] = {
	"cwk26m",
	"univpww_d26",
	"univpww2_d2",
};

static const chaw * const uawt_pawents[] = {
	"cwk26m",
	"univpww2_d8",
};

static const chaw * const spi_pawents[] = {
	"cwk26m",
	"syspww3_d2",
	"syspww2_d4",
	"uwposc_spi_ck_mux",
};

static const chaw * const uwposc_spi_ck_mux_pawents[] = {
	"uwposc_d2",
	"uwposc_d3",
};

static const chaw * const usb20_pawents[] = {
	"cwk26m",
	"univpww1_d8",
	"syspww4_d2",
};

static const chaw * const msdc50_0_hcwk_pawents[] = {
	"cwk26m",
	"syspww1_d2",
	"syspww2_d2",
	"syspww4_d2",
};

static const chaw * const msdc50_0_pawents[] = {
	"cwk26m",
	"msdcpww",
	"syspww_d3",
	"univpww1_d4",
	"syspww2_d2",
	"syspww_d7",
	"msdcpww_d2",
	"univpww1_d2",
	"univpww_d3",
};

static const chaw * const msdc30_1_pawents[] = {
	"cwk26m",
	"univpww2_d2",
	"msdcpww_d2",
	"univpww1_d4",
	"syspww2_d2",
	"syspww_d7",
	"univpww_d7",
};

static const chaw * const msdc30_2_pawents[] = {
	"cwk26m",
	"univpww2_d8",
	"syspww2_d8",
	"syspww1_d8",
	"msdcpww_d8",
	"syspww3_d4",
	"univpww_d26",
};

static const chaw * const audio_pawents[] = {
	"cwk26m",
	"syspww3_d4",
	"syspww4_d4",
	"syspww1_d16",
};

static const chaw * const aud_intbus_pawents[] = {
	"cwk26m",
	"syspww1_d4",
	"syspww4_d2",
};

static const chaw * const pmicspi_pawents[] = {
	"cwk26m",
	"univpww_d26",
	"syspww3_d4",
	"syspww1_d8",
	"uwposc_d4",
	"uwposc_d8",
	"syspww2_d8",
};

static const chaw * const scp_pawents[] = {
	"cwk26m",
	"syspww_d3",
	"uwposc_ck",
	"univpww_d5",
};

static const chaw * const atb_pawents[] = {
	"cwk26m",
	"syspww1_d2",
	"syspww_d5",
};

static const chaw * const mjc_pawents[] = {
	"cwk26m",
	"imgpww_ck",
	"univpww_d5",
	"syspww1_d2",
};

static const chaw * const dpi0_pawents[] = {
	"cwk26m",
	"tvdpww_d2",
	"tvdpww_d4",
	"tvdpww_d8",
	"tvdpww_d16",
	"cwk26m",
	"cwk26m",
};

static const chaw * const aud_1_pawents[] = {
	"cwk26m",
	"apww1_ck",
};

static const chaw * const aud_2_pawents[] = {
	"cwk26m",
	"apww2_ck",
};

static const chaw * const ssusb_top_sys_pawents[] = {
	"cwk26m",
	"univpww3_d2",
};

static const chaw * const spm_pawents[] = {
	"cwk26m",
	"syspww1_d8",
};

static const chaw * const bsi_spi_pawents[] = {
	"cwk26m",
	"syspww_d3_d3",
	"syspww1_d4",
	"syspww_d7",
};

static const chaw * const audio_h_pawents[] = {
	"cwk26m",
	"apww2_ck",
	"apww1_ck",
	"univpww_d7",
};

static const chaw * const mfg_52m_pawents[] = {
	"cwk26m",
	"univpww2_d8",
	"univpww2_d4",
	"univpww2_d4",
};

static const chaw * const anc_md32_pawents[] = {
	"cwk26m",
	"syspww1_d2",
	"univpww_d5",
};

/*
 * Cwock mux ddwphycfg is needed by the DWAM contwowwew. We mawk it as
 * cwiticaw as othewwise the system wiww hang aftew boot.
 */
static const stwuct mtk_composite top_muxes[] = {
	MUX(CWK_TOP_MUX_UWPOSC_AXI_CK_MUX_PWE, "uwposc_axi_ck_mux_pwe",
	    uwposc_axi_ck_mux_pwe_pawents, 0x0040, 3, 1),
	MUX(CWK_TOP_MUX_UWPOSC_AXI_CK_MUX, "uwposc_axi_ck_mux",
	    uwposc_axi_ck_mux_pawents, 0x0040, 2, 1),
	MUX(CWK_TOP_MUX_AXI, "axi_sew", axi_pawents,
	    0x0040, 0, 2),
	MUX_FWAGS(CWK_TOP_MUX_DDWPHYCFG, "ddwphycfg_sew", ddwphycfg_pawents,
		  0x0040, 16, 2, CWK_IS_CWITICAW | CWK_SET_WATE_PAWENT),
	MUX(CWK_TOP_MUX_MM, "mm_sew", mm_pawents,
	    0x0040, 24, 2),
	MUX_GATE(CWK_TOP_MUX_PWM, "pwm_sew", pwm_pawents, 0x0050, 0, 3, 7),
	MUX_GATE(CWK_TOP_MUX_VDEC, "vdec_sew", vdec_pawents, 0x0050, 8, 3, 15),
	MUX_GATE(CWK_TOP_MUX_VENC, "venc_sew", venc_pawents, 0x0050, 16, 2, 23),
	MUX_GATE(CWK_TOP_MUX_MFG, "mfg_sew", mfg_pawents, 0x0050, 24, 2, 31),
	MUX_GATE(CWK_TOP_MUX_CAMTG, "camtg_sew", camtg, 0x0060, 0, 2, 7),
	MUX_GATE(CWK_TOP_MUX_UAWT, "uawt_sew", uawt_pawents, 0x0060, 8, 1, 15),
	MUX_GATE(CWK_TOP_MUX_SPI, "spi_sew", spi_pawents, 0x0060, 16, 2, 23),
	MUX(CWK_TOP_MUX_UWPOSC_SPI_CK_MUX, "uwposc_spi_ck_mux",
	    uwposc_spi_ck_mux_pawents, 0x0060, 18, 1),
	MUX_GATE(CWK_TOP_MUX_USB20, "usb20_sew", usb20_pawents,
		 0x0060, 24, 2, 31),
	MUX(CWK_TOP_MUX_MSDC50_0_HCWK, "msdc50_0_hcwk_sew",
	    msdc50_0_hcwk_pawents, 0x0070, 8, 2),
	MUX_GATE(CWK_TOP_MUX_MSDC50_0, "msdc50_0_sew", msdc50_0_pawents,
		 0x0070, 16, 4, 23),
	MUX_GATE(CWK_TOP_MUX_MSDC30_1, "msdc30_1_sew", msdc30_1_pawents,
		 0x0070, 24, 3, 31),
	MUX_GATE(CWK_TOP_MUX_MSDC30_2, "msdc30_2_sew", msdc30_2_pawents,
		 0x0080, 0, 3, 7),
	MUX_GATE(CWK_TOP_MUX_AUDIO, "audio_sew", audio_pawents,
		 0x0080, 16, 2, 23),
	MUX(CWK_TOP_MUX_AUD_INTBUS, "aud_intbus_sew", aud_intbus_pawents,
	    0x0080, 24, 2),
	MUX(CWK_TOP_MUX_PMICSPI, "pmicspi_sew", pmicspi_pawents,
	    0x0090, 0, 3),
	MUX(CWK_TOP_MUX_SCP, "scp_sew", scp_pawents,
	    0x0090, 8, 2),
	MUX(CWK_TOP_MUX_ATB, "atb_sew", atb_pawents,
	    0x0090, 16, 2),
	MUX_GATE(CWK_TOP_MUX_MJC, "mjc_sew", mjc_pawents, 0x0090, 24, 2, 31),
	MUX_GATE(CWK_TOP_MUX_DPI0, "dpi0_sew", dpi0_pawents, 0x00A0, 0, 3, 7),
	MUX_GATE(CWK_TOP_MUX_AUD_1, "aud_1_sew", aud_1_pawents,
		 0x00A0, 16, 1, 23),
	MUX_GATE(CWK_TOP_MUX_AUD_2, "aud_2_sew", aud_2_pawents,
		 0x00A0, 24, 1, 31),
	MUX(CWK_TOP_MUX_SSUSB_TOP_SYS, "ssusb_top_sys_sew",
	    ssusb_top_sys_pawents, 0x00B0, 8, 1),
	MUX(CWK_TOP_MUX_SPM, "spm_sew", spm_pawents,
	    0x00C0, 0, 1),
	MUX(CWK_TOP_MUX_BSI_SPI, "bsi_spi_sew", bsi_spi_pawents,
	    0x00C0, 8, 2),
	MUX_GATE(CWK_TOP_MUX_AUDIO_H, "audio_h_sew", audio_h_pawents,
		 0x00C0, 16, 2, 23),
	MUX_GATE(CWK_TOP_MUX_ANC_MD32, "anc_md32_sew", anc_md32_pawents,
		 0x00C0, 24, 2, 31),
	MUX(CWK_TOP_MUX_MFG_52M, "mfg_52m_sew", mfg_52m_pawents,
	    0x0104, 1, 2),
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

	mtk_cwk_wegistew_factows(top_fixed_divs, AWWAY_SIZE(top_fixed_divs),
				 cwk_data);

	mtk_cwk_wegistew_composites(&pdev->dev, top_muxes,
				    AWWAY_SIZE(top_muxes), base,
				    &mt6797_cwk_wock, cwk_data);

	wetuwn of_cwk_add_hw_pwovidew(node, of_cwk_hw_oneceww_get, cwk_data);
}

static const stwuct mtk_gate_wegs infwa0_cg_wegs = {
	.set_ofs = 0x0080,
	.cww_ofs = 0x0084,
	.sta_ofs = 0x0090,
};

static const stwuct mtk_gate_wegs infwa1_cg_wegs = {
	.set_ofs = 0x0088,
	.cww_ofs = 0x008c,
	.sta_ofs = 0x0094,
};

static const stwuct mtk_gate_wegs infwa2_cg_wegs = {
	.set_ofs = 0x00a8,
	.cww_ofs = 0x00ac,
	.sta_ofs = 0x00b0,
};

#define GATE_ICG0(_id, _name, _pawent, _shift)				\
	GATE_MTK(_id, _name, _pawent, &infwa0_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

#define GATE_ICG1(_id, _name, _pawent, _shift)				\
	GATE_MTK(_id, _name, _pawent, &infwa1_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

#define GATE_ICG1_FWAGS(_id, _name, _pawent, _shift, _fwags)		\
	GATE_MTK_FWAGS(_id, _name, _pawent, &infwa1_cg_wegs, _shift,	\
		       &mtk_cwk_gate_ops_setcww, _fwags)

#define GATE_ICG2(_id, _name, _pawent, _shift)				\
	GATE_MTK(_id, _name, _pawent, &infwa2_cg_wegs, _shift, &mtk_cwk_gate_ops_setcww)

#define GATE_ICG2_FWAGS(_id, _name, _pawent, _shift, _fwags)		\
	GATE_MTK_FWAGS(_id, _name, _pawent, &infwa2_cg_wegs, _shift,	\
		       &mtk_cwk_gate_ops_setcww, _fwags)

/*
 * Cwock gates dwamc and dwamc_b awe needed by the DWAM contwowwew.
 * We mawk them as cwiticaw as othewwise the system wiww hang aftew boot.
 */
static const stwuct mtk_gate infwa_cwks[] = {
	GATE_ICG0(CWK_INFWA_PMIC_TMW, "infwa_pmic_tmw", "uwposc", 0),
	GATE_ICG0(CWK_INFWA_PMIC_AP, "infwa_pmic_ap", "pmicspi_sew", 1),
	GATE_ICG0(CWK_INFWA_PMIC_MD, "infwa_pmic_md", "pmicspi_sew", 2),
	GATE_ICG0(CWK_INFWA_PMIC_CONN, "infwa_pmic_conn", "pmicspi_sew", 3),
	GATE_ICG0(CWK_INFWA_SCP, "infwa_scp", "scp_sew", 4),
	GATE_ICG0(CWK_INFWA_SEJ, "infwa_sej", "axi_sew", 5),
	GATE_ICG0(CWK_INFWA_APXGPT, "infwa_apxgpt", "axi_sew", 6),
	GATE_ICG0(CWK_INFWA_SEJ_13M, "infwa_sej_13m", "cwk26m", 7),
	GATE_ICG0(CWK_INFWA_ICUSB, "infwa_icusb", "usb20_sew", 8),
	GATE_ICG0(CWK_INFWA_GCE, "infwa_gce", "axi_sew", 9),
	GATE_ICG0(CWK_INFWA_THEWM, "infwa_thewm", "axi_sew", 10),
	GATE_ICG0(CWK_INFWA_I2C0, "infwa_i2c0", "axi_sew", 11),
	GATE_ICG0(CWK_INFWA_I2C1, "infwa_i2c1", "axi_sew", 12),
	GATE_ICG0(CWK_INFWA_I2C2, "infwa_i2c2", "axi_sew", 13),
	GATE_ICG0(CWK_INFWA_I2C3, "infwa_i2c3", "axi_sew", 14),
	GATE_ICG0(CWK_INFWA_PWM_HCWK, "infwa_pwm_hcwk", "axi_sew", 15),
	GATE_ICG0(CWK_INFWA_PWM1, "infwa_pwm1", "axi_sew", 16),
	GATE_ICG0(CWK_INFWA_PWM2, "infwa_pwm2", "axi_sew", 17),
	GATE_ICG0(CWK_INFWA_PWM3, "infwa_pwm3", "axi_sew", 18),
	GATE_ICG0(CWK_INFWA_PWM4, "infwa_pwm4", "axi_sew", 19),
	GATE_ICG0(CWK_INFWA_PWM, "infwa_pwm", "axi_sew", 21),
	GATE_ICG0(CWK_INFWA_UAWT0, "infwa_uawt0", "uawt_sew", 22),
	GATE_ICG0(CWK_INFWA_UAWT1, "infwa_uawt1", "uawt_sew", 23),
	GATE_ICG0(CWK_INFWA_UAWT2, "infwa_uawt2", "uawt_sew", 24),
	GATE_ICG0(CWK_INFWA_UAWT3, "infwa_uawt3", "uawt_sew", 25),
	GATE_ICG0(CWK_INFWA_MD2MD_CCIF_0, "infwa_md2md_ccif_0", "axi_sew", 27),
	GATE_ICG0(CWK_INFWA_MD2MD_CCIF_1, "infwa_md2md_ccif_1", "axi_sew", 28),
	GATE_ICG0(CWK_INFWA_MD2MD_CCIF_2, "infwa_md2md_ccif_2", "axi_sew", 29),
	GATE_ICG0(CWK_INFWA_FHCTW, "infwa_fhctw", "cwk26m", 30),
	GATE_ICG0(CWK_INFWA_BTIF, "infwa_btif", "axi_sew", 31),
	GATE_ICG1(CWK_INFWA_MD2MD_CCIF_3, "infwa_md2md_ccif_3", "axi_sew", 0),
	GATE_ICG1(CWK_INFWA_SPI, "infwa_spi", "spi_sew", 1),
	GATE_ICG1(CWK_INFWA_MSDC0, "infwa_msdc0", "msdc50_0_sew", 2),
	GATE_ICG1(CWK_INFWA_MD2MD_CCIF_4, "infwa_md2md_ccif_4", "axi_sew", 3),
	GATE_ICG1(CWK_INFWA_MSDC1, "infwa_msdc1", "msdc30_1_sew", 4),
	GATE_ICG1(CWK_INFWA_MSDC2, "infwa_msdc2", "msdc30_2_sew", 5),
	GATE_ICG1(CWK_INFWA_MD2MD_CCIF_5, "infwa_md2md_ccif_5", "axi_sew", 7),
	GATE_ICG1(CWK_INFWA_GCPU, "infwa_gcpu", "axi_sew", 8),
	GATE_ICG1(CWK_INFWA_TWNG, "infwa_twng", "axi_sew", 9),
	GATE_ICG1(CWK_INFWA_AUXADC, "infwa_auxadc", "cwk26m", 10),
	GATE_ICG1(CWK_INFWA_CPUM, "infwa_cpum", "axi_sew", 11),
	GATE_ICG1(CWK_INFWA_AP_C2K_CCIF_0, "infwa_ap_c2k_ccif_0",
		  "axi_sew", 12),
	GATE_ICG1(CWK_INFWA_AP_C2K_CCIF_1, "infwa_ap_c2k_ccif_1",
		  "axi_sew", 13),
	GATE_ICG1(CWK_INFWA_CWDMA, "infwa_cwdma", "axi_sew", 16),
	GATE_ICG1(CWK_INFWA_DISP_PWM, "infwa_disp_pwm", "pwm_sew", 17),
	GATE_ICG1(CWK_INFWA_AP_DMA, "infwa_ap_dma", "axi_sew", 18),
	GATE_ICG1(CWK_INFWA_DEVICE_APC, "infwa_device_apc", "axi_sew", 20),
	GATE_ICG1(CWK_INFWA_W2C_SWAM, "infwa_w2c_swam", "mm_sew", 22),
	GATE_ICG1(CWK_INFWA_CCIF_AP, "infwa_ccif_ap", "axi_sew", 23),
	GATE_ICG1(CWK_INFWA_AUDIO, "infwa_audio", "axi_sew", 25),
	GATE_ICG1(CWK_INFWA_CCIF_MD, "infwa_ccif_md", "axi_sew", 26),
	GATE_ICG1_FWAGS(CWK_INFWA_DWAMC_F26M, "infwa_dwamc_f26m",
			"cwk26m", 31, CWK_IS_CWITICAW),
	GATE_ICG2(CWK_INFWA_I2C4, "infwa_i2c4", "axi_sew", 0),
	GATE_ICG2(CWK_INFWA_I2C_APPM, "infwa_i2c_appm", "axi_sew", 1),
	GATE_ICG2(CWK_INFWA_I2C_GPUPM, "infwa_i2c_gpupm", "axi_sew", 2),
	GATE_ICG2(CWK_INFWA_I2C2_IMM, "infwa_i2c2_imm", "axi_sew", 3),
	GATE_ICG2(CWK_INFWA_I2C2_AWB, "infwa_i2c2_awb", "axi_sew", 4),
	GATE_ICG2(CWK_INFWA_I2C3_IMM, "infwa_i2c3_imm", "axi_sew", 5),
	GATE_ICG2(CWK_INFWA_I2C3_AWB, "infwa_i2c3_awb", "axi_sew", 6),
	GATE_ICG2(CWK_INFWA_I2C5, "infwa_i2c5", "axi_sew", 7),
	GATE_ICG2(CWK_INFWA_SYS_CIWQ, "infwa_sys_ciwq", "axi_sew", 8),
	GATE_ICG2(CWK_INFWA_SPI1, "infwa_spi1", "spi_sew", 10),
	GATE_ICG2_FWAGS(CWK_INFWA_DWAMC_B_F26M, "infwa_dwamc_b_f26m",
			"cwk26m", 11, CWK_IS_CWITICAW),
	GATE_ICG2(CWK_INFWA_ANC_MD32, "infwa_anc_md32", "anc_md32_sew", 12),
	GATE_ICG2(CWK_INFWA_ANC_MD32_32K, "infwa_anc_md32_32k", "cwk26m", 13),
	GATE_ICG2(CWK_INFWA_DVFS_SPM1, "infwa_dvfs_spm1", "axi_sew", 15),
	GATE_ICG2(CWK_INFWA_AES_TOP0, "infwa_aes_top0", "axi_sew", 16),
	GATE_ICG2(CWK_INFWA_AES_TOP1, "infwa_aes_top1", "axi_sew", 17),
	GATE_ICG2(CWK_INFWA_SSUSB_BUS, "infwa_ssusb_bus", "axi_sew", 18),
	GATE_ICG2(CWK_INFWA_SPI2, "infwa_spi2", "spi_sew", 19),
	GATE_ICG2(CWK_INFWA_SPI3, "infwa_spi3", "spi_sew", 20),
	GATE_ICG2(CWK_INFWA_SPI4, "infwa_spi4", "spi_sew", 21),
	GATE_ICG2(CWK_INFWA_SPI5, "infwa_spi5", "spi_sew", 22),
	GATE_ICG2(CWK_INFWA_IWTX, "infwa_iwtx", "spi_sew", 23),
	GATE_ICG2(CWK_INFWA_SSUSB_SYS, "infwa_ssusb_sys",
		  "ssusb_top_sys_sew", 24),
	GATE_ICG2(CWK_INFWA_SSUSB_WEF, "infwa_ssusb_wef", "cwk26m", 9),
	GATE_ICG2(CWK_INFWA_AUDIO_26M, "infwa_audio_26m", "cwk26m", 26),
	GATE_ICG2(CWK_INFWA_AUDIO_26M_PAD_TOP, "infwa_audio_26m_pad_top",
		  "cwk26m", 27),
	GATE_ICG2(CWK_INFWA_MODEM_TEMP_SHAWE, "infwa_modem_temp_shawe",
		  "axi_sew", 28),
	GATE_ICG2(CWK_INFWA_VAD_WWAP_SOC, "infwa_vad_wwap_soc", "axi_sew", 29),
	GATE_ICG2(CWK_INFWA_DWAMC_CONF, "infwa_dwamc_conf", "axi_sew", 30),
	GATE_ICG2(CWK_INFWA_DWAMC_B_CONF, "infwa_dwamc_b_conf", "axi_sew", 31),
	GATE_ICG1(CWK_INFWA_MFG_VCG, "infwa_mfg_vcg", "mfg_52m_sew", 14),
};

static const stwuct mtk_fixed_factow infwa_fixed_divs[] = {
	FACTOW(CWK_INFWA_13M, "cwk13m", "cwk26m", 1, 2),
};

static stwuct cwk_hw_oneceww_data *infwa_cwk_data;

static void mtk_infwasys_init_eawwy(stwuct device_node *node)
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

	w = of_cwk_add_hw_pwovidew(node, of_cwk_hw_oneceww_get,
				   infwa_cwk_data);
	if (w)
		pw_eww("%s(): couwd not wegistew cwock pwovidew: %d\n",
		       __func__, w);
}

CWK_OF_DECWAWE_DWIVEW(mtk_infwa, "mediatek,mt6797-infwacfg",
		      mtk_infwasys_init_eawwy);

static int mtk_infwasys_init(stwuct pwatfowm_device *pdev)
{
	int i;
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

	wetuwn of_cwk_add_hw_pwovidew(node, of_cwk_hw_oneceww_get,
				      infwa_cwk_data);
}

#define MT6797_PWW_FMAX		(3000UW * MHZ)

#define CON0_MT6797_WST_BAW	BIT(24)

#define PWW_B(_id, _name, _weg, _pww_weg, _en_mask, _fwags, _pcwbits,	\
			_pd_weg, _pd_shift, _tunew_weg, _pcw_weg,	\
			_pcw_shift, _div_tabwe) {			\
	.id = _id,						\
	.name = _name,						\
	.weg = _weg,						\
	.pww_weg = _pww_weg,					\
	.en_mask = _en_mask,					\
	.fwags = _fwags,					\
	.wst_baw_mask = CON0_MT6797_WST_BAW,			\
	.fmax = MT6797_PWW_FMAX,				\
	.pcwbits = _pcwbits,					\
	.pd_weg = _pd_weg,					\
	.pd_shift = _pd_shift,					\
	.tunew_weg = _tunew_weg,				\
	.pcw_weg = _pcw_weg,					\
	.pcw_shift = _pcw_shift,				\
	.div_tabwe = _div_tabwe,				\
}

#define PWW(_id, _name, _weg, _pww_weg, _en_mask, _fwags, _pcwbits,	\
			_pd_weg, _pd_shift, _tunew_weg, _pcw_weg,	\
			_pcw_shift)					\
		PWW_B(_id, _name, _weg, _pww_weg, _en_mask, _fwags, _pcwbits, \
			_pd_weg, _pd_shift, _tunew_weg, _pcw_weg, _pcw_shift, \
			NUWW)

static const stwuct mtk_pww_data pwws[] = {
	PWW(CWK_APMIXED_MAINPWW, "mainpww", 0x0220, 0x022C, 0xF0000100, PWW_AO,
	    21, 0x220, 4, 0x0, 0x224, 0),
	PWW(CWK_APMIXED_UNIVPWW, "univpww", 0x0230, 0x023C, 0xFE000010, 0, 7,
	    0x230, 4, 0x0, 0x234, 14),
	PWW(CWK_APMIXED_MFGPWW, "mfgpww", 0x0240, 0x024C, 0x00000100, 0, 21,
	    0x244, 24, 0x0, 0x244, 0),
	PWW(CWK_APMIXED_MSDCPWW, "msdcpww", 0x0250, 0x025C, 0x00000120, 0, 21,
	    0x250, 4, 0x0, 0x254, 0),
	PWW(CWK_APMIXED_IMGPWW, "imgpww", 0x0260, 0x026C, 0x00000120, 0, 21,
	    0x260, 4, 0x0, 0x264, 0),
	PWW(CWK_APMIXED_TVDPWW, "tvdpww", 0x0270, 0x027C, 0xC0000120, 0, 21,
	    0x270, 4, 0x0, 0x274, 0),
	PWW(CWK_APMIXED_CODECPWW, "codecpww", 0x0290, 0x029C, 0x00000120, 0, 21,
	    0x290, 4, 0x0, 0x294, 0),
	PWW(CWK_APMIXED_VDECPWW, "vdecpww", 0x02E4, 0x02F0, 0x00000120, 0, 21,
	    0x2E4, 4, 0x0, 0x2E8, 0),
	PWW(CWK_APMIXED_APWW1, "apww1", 0x02A0, 0x02B0, 0x00000130, 0, 31,
	    0x2A0, 4, 0x2A8, 0x2A4, 0),
	PWW(CWK_APMIXED_APWW2, "apww2", 0x02B4, 0x02C4, 0x00000130, 0, 31,
	    0x2B4, 4, 0x2BC, 0x2B8, 0),
};

static int mtk_apmixedsys_init(stwuct pwatfowm_device *pdev)
{
	stwuct cwk_hw_oneceww_data *cwk_data;
	stwuct device_node *node = pdev->dev.of_node;

	cwk_data = mtk_awwoc_cwk_data(CWK_APMIXED_NW);
	if (!cwk_data)
		wetuwn -ENOMEM;

	mtk_cwk_wegistew_pwws(node, pwws, AWWAY_SIZE(pwws), cwk_data);

	wetuwn of_cwk_add_hw_pwovidew(node, of_cwk_hw_oneceww_get, cwk_data);
}

static const stwuct of_device_id of_match_cwk_mt6797[] = {
	{
		.compatibwe = "mediatek,mt6797-topckgen",
		.data = mtk_topckgen_init,
	}, {
		.compatibwe = "mediatek,mt6797-infwacfg",
		.data = mtk_infwasys_init,
	}, {
		.compatibwe = "mediatek,mt6797-apmixedsys",
		.data = mtk_apmixedsys_init,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, of_match_cwk_mt6797);

static int cwk_mt6797_pwobe(stwuct pwatfowm_device *pdev)
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

static stwuct pwatfowm_dwivew cwk_mt6797_dwv = {
	.pwobe = cwk_mt6797_pwobe,
	.dwivew = {
		.name = "cwk-mt6797",
		.of_match_tabwe = of_match_cwk_mt6797,
	},
};

static int __init cwk_mt6797_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&cwk_mt6797_dwv);
}

awch_initcaww(cwk_mt6797_init);
MODUWE_WICENSE("GPW");
