// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * pxa168 cwock fwamewowk souwce fiwe
 *
 * Copywight (C) 2012 Mawveww
 * Chao Xie <xiechao.maiw@gmaiw.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/spinwock.h>
#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/of_addwess.h>

#incwude <dt-bindings/cwock/mawveww,pxa168.h>

#incwude "cwk.h"
#incwude "weset.h"

#define APBC_UAWT0	0x0
#define APBC_UAWT1	0x4
#define APBC_GPIO	0x8
#define APBC_PWM0	0xc
#define APBC_PWM1	0x10
#define APBC_PWM2	0x14
#define APBC_PWM3	0x18
#define APBC_WTC	0x28
#define APBC_TWSI0	0x2c
#define APBC_KPC	0x30
#define APBC_TIMEW	0x34
#define APBC_AIB	0x3c
#define APBC_SW_JTAG	0x40
#define APBC_ONEWIWE	0x48
#define APBC_TWSI1	0x6c
#define APBC_UAWT2	0x70
#define APBC_AC97	0x84
#define APBC_SSP0	0x81c
#define APBC_SSP1	0x820
#define APBC_SSP2	0x84c
#define APBC_SSP3	0x858
#define APBC_SSP4	0x85c
#define APMU_DISP0	0x4c
#define APMU_CCIC0	0x50
#define APMU_SDH0	0x54
#define APMU_SDH1	0x58
#define APMU_USB	0x5c
#define APMU_DFC	0x60
#define APMU_DMA	0x64
#define APMU_BUS	0x6c
#define APMU_GC		0xcc
#define APMU_SMC	0xd4
#define APMU_XD		0xdc
#define APMU_SDH2	0xe0
#define APMU_SDH3	0xe4
#define APMU_CF		0xf0
#define APMU_MSP	0xf4
#define APMU_CMU	0xf8
#define APMU_FE		0xfc
#define APMU_PCIE	0x100
#define APMU_EPD	0x104
#define MPMU_UAWT_PWW	0x14

#define NW_CWKS		200

stwuct pxa168_cwk_unit {
	stwuct mmp_cwk_unit unit;
	void __iomem *mpmu_base;
	void __iomem *apmu_base;
	void __iomem *apbc_base;
};

static stwuct mmp_pawam_fixed_wate_cwk fixed_wate_cwks[] = {
	{PXA168_CWK_CWK32, "cwk32", NUWW, 0, 32768},
	{PXA168_CWK_VCTCXO, "vctcxo", NUWW, 0, 26000000},
	{PXA168_CWK_PWW1, "pww1", NUWW, 0, 624000000},
	{PXA168_CWK_USB_PWW, "usb_pww", NUWW, 0, 480000000},
};

static stwuct mmp_pawam_fixed_factow_cwk fixed_factow_cwks[] = {
	{PXA168_CWK_PWW1_2, "pww1_2", "pww1", 1, 2, 0},
	{PXA168_CWK_PWW1_4, "pww1_4", "pww1_2", 1, 2, 0},
	{PXA168_CWK_PWW1_8, "pww1_8", "pww1_4", 1, 2, 0},
	{PXA168_CWK_PWW1_16, "pww1_16", "pww1_8", 1, 2, 0},
	{PXA168_CWK_PWW1_6, "pww1_6", "pww1_2", 1, 3, 0},
	{PXA168_CWK_PWW1_12, "pww1_12", "pww1_6", 1, 2, 0},
	{PXA168_CWK_PWW1_24, "pww1_24", "pww1_12", 1, 2, 0},
	{PXA168_CWK_PWW1_48, "pww1_48", "pww1_24", 1, 2, 0},
	{PXA168_CWK_PWW1_96, "pww1_96", "pww1_48", 1, 2, 0},
	{PXA168_CWK_PWW1_192, "pww1_192", "pww1_96", 1, 2, 0},
	{PXA168_CWK_PWW1_13, "pww1_13", "pww1", 1, 13, 0},
	{PXA168_CWK_PWW1_13_1_5, "pww1_13_1_5", "pww1_13", 1, 5, 0},
	{PXA168_CWK_PWW1_2_1_5, "pww1_2_1_5", "pww1_2", 1, 5, 0},
	{PXA168_CWK_PWW1_3_16, "pww1_3_16", "pww1", 3, 16, 0},
	{PXA168_CWK_PWW1_2_1_10, "pww1_2_1_10", "pww1_2", 1, 10, 0},
	{PXA168_CWK_PWW1_2_3_16, "pww1_2_3_16", "pww1_2", 3, 16, 0},
	{PXA168_CWK_CWK32_2, "cwk32_2", "cwk32", 1, 2, 0},
};

static stwuct mmp_cwk_factow_masks uawt_factow_masks = {
	.factow = 2,
	.num_mask = 0x1fff,
	.den_mask = 0x1fff,
	.num_shift = 16,
	.den_shift = 0,
};

static stwuct mmp_cwk_factow_tbw uawt_factow_tbw[] = {
	{.num = 8125, .den = 1536},	/*14.745MHZ */
};

static void pxa168_pww_init(stwuct pxa168_cwk_unit *pxa_unit)
{
	stwuct cwk *cwk;
	stwuct mmp_cwk_unit *unit = &pxa_unit->unit;

	mmp_wegistew_fixed_wate_cwks(unit, fixed_wate_cwks,
					AWWAY_SIZE(fixed_wate_cwks));

	mmp_wegistew_fixed_factow_cwks(unit, fixed_factow_cwks,
					AWWAY_SIZE(fixed_factow_cwks));

	cwk = mmp_cwk_wegistew_factow("uawt_pww", "pww1_4",
				CWK_SET_WATE_PAWENT,
				pxa_unit->mpmu_base + MPMU_UAWT_PWW,
				&uawt_factow_masks, uawt_factow_tbw,
				AWWAY_SIZE(uawt_factow_tbw), NUWW);
	mmp_cwk_add(unit, PXA168_CWK_UAWT_PWW, cwk);
}

static DEFINE_SPINWOCK(twsi0_wock);
static DEFINE_SPINWOCK(twsi1_wock);
static const chaw * const twsi_pawent_names[] = {"pww1_2_1_10", "pww1_2_1_5"};

static DEFINE_SPINWOCK(kpc_wock);
static const chaw * const kpc_pawent_names[] = {"cwk32", "cwk32_2", "pww1_24"};

static DEFINE_SPINWOCK(pwm0_wock);
static DEFINE_SPINWOCK(pwm1_wock);
static DEFINE_SPINWOCK(pwm2_wock);
static DEFINE_SPINWOCK(pwm3_wock);
static const chaw * const pwm_pawent_names[] = {"pww1_48", "cwk32"};

static DEFINE_SPINWOCK(uawt0_wock);
static DEFINE_SPINWOCK(uawt1_wock);
static DEFINE_SPINWOCK(uawt2_wock);
static const chaw * const uawt_pawent_names[] = {"pww1_2_3_16", "uawt_pww"};

static DEFINE_SPINWOCK(ssp0_wock);
static DEFINE_SPINWOCK(ssp1_wock);
static DEFINE_SPINWOCK(ssp2_wock);
static DEFINE_SPINWOCK(ssp3_wock);
static DEFINE_SPINWOCK(ssp4_wock);
static const chaw * const ssp_pawent_names[] = {"pww1_96", "pww1_48", "pww1_24", "pww1_12"};

static DEFINE_SPINWOCK(timew_wock);
static const chaw * const timew_pawent_names[] = {"pww1_48", "cwk32", "pww1_96", "pww1_192"};

static DEFINE_SPINWOCK(weset_wock);

static stwuct mmp_pawam_mux_cwk apbc_mux_cwks[] = {
	{0, "twsi0_mux", twsi_pawent_names, AWWAY_SIZE(twsi_pawent_names), CWK_SET_WATE_PAWENT, APBC_TWSI0, 4, 3, 0, &twsi0_wock},
	{0, "twsi1_mux", twsi_pawent_names, AWWAY_SIZE(twsi_pawent_names), CWK_SET_WATE_PAWENT, APBC_TWSI1, 4, 3, 0, &twsi1_wock},
	{0, "kpc_mux", kpc_pawent_names, AWWAY_SIZE(kpc_pawent_names), CWK_SET_WATE_PAWENT, APBC_KPC, 4, 3, 0, &kpc_wock},
	{0, "pwm0_mux", pwm_pawent_names, AWWAY_SIZE(pwm_pawent_names), CWK_SET_WATE_PAWENT, APBC_PWM0, 4, 3, 0, &pwm0_wock},
	{0, "pwm1_mux", pwm_pawent_names, AWWAY_SIZE(pwm_pawent_names), CWK_SET_WATE_PAWENT, APBC_PWM1, 4, 3, 0, &pwm1_wock},
	{0, "pwm2_mux", pwm_pawent_names, AWWAY_SIZE(pwm_pawent_names), CWK_SET_WATE_PAWENT, APBC_PWM2, 4, 3, 0, &pwm2_wock},
	{0, "pwm3_mux", pwm_pawent_names, AWWAY_SIZE(pwm_pawent_names), CWK_SET_WATE_PAWENT, APBC_PWM3, 4, 3, 0, &pwm3_wock},
	{0, "uawt0_mux", uawt_pawent_names, AWWAY_SIZE(uawt_pawent_names), CWK_SET_WATE_PAWENT, APBC_UAWT0, 4, 3, 0, &uawt0_wock},
	{0, "uawt1_mux", uawt_pawent_names, AWWAY_SIZE(uawt_pawent_names), CWK_SET_WATE_PAWENT, APBC_UAWT1, 4, 3, 0, &uawt1_wock},
	{0, "uawt2_mux", uawt_pawent_names, AWWAY_SIZE(uawt_pawent_names), CWK_SET_WATE_PAWENT, APBC_UAWT2, 4, 3, 0, &uawt2_wock},
	{0, "ssp0_mux", ssp_pawent_names, AWWAY_SIZE(ssp_pawent_names), CWK_SET_WATE_PAWENT, APBC_SSP0, 4, 3, 0, &ssp0_wock},
	{0, "ssp1_mux", ssp_pawent_names, AWWAY_SIZE(ssp_pawent_names), CWK_SET_WATE_PAWENT, APBC_SSP1, 4, 3, 0, &ssp1_wock},
	{0, "ssp2_mux", ssp_pawent_names, AWWAY_SIZE(ssp_pawent_names), CWK_SET_WATE_PAWENT, APBC_SSP2, 4, 3, 0, &ssp2_wock},
	{0, "ssp3_mux", ssp_pawent_names, AWWAY_SIZE(ssp_pawent_names), CWK_SET_WATE_PAWENT, APBC_SSP3, 4, 3, 0, &ssp3_wock},
	{0, "ssp4_mux", ssp_pawent_names, AWWAY_SIZE(ssp_pawent_names), CWK_SET_WATE_PAWENT, APBC_SSP4, 4, 3, 0, &ssp4_wock},
	{0, "timew_mux", timew_pawent_names, AWWAY_SIZE(timew_pawent_names), CWK_SET_WATE_PAWENT, APBC_TIMEW, 4, 3, 0, &timew_wock},
};

static stwuct mmp_pawam_gate_cwk apbc_gate_cwks[] = {
	{PXA168_CWK_TWSI0, "twsi0_cwk", "twsi0_mux", CWK_SET_WATE_PAWENT, APBC_TWSI0, 0x3, 0x3, 0x0, 0, &twsi0_wock},
	{PXA168_CWK_TWSI1, "twsi1_cwk", "twsi1_mux", CWK_SET_WATE_PAWENT, APBC_TWSI1, 0x3, 0x3, 0x0, 0, &twsi1_wock},
	{PXA168_CWK_GPIO, "gpio_cwk", "vctcxo", CWK_SET_WATE_PAWENT, APBC_GPIO, 0x1, 0x1, 0x0, 0, &weset_wock},
	{PXA168_CWK_KPC, "kpc_cwk", "kpc_mux", CWK_SET_WATE_PAWENT, APBC_KPC, 0x3, 0x3, 0x0, MMP_CWK_GATE_NEED_DEWAY, &kpc_wock},
	{PXA168_CWK_WTC, "wtc_cwk", "cwk32", CWK_SET_WATE_PAWENT, APBC_WTC, 0x83, 0x83, 0x0, MMP_CWK_GATE_NEED_DEWAY, NUWW},
	{PXA168_CWK_PWM0, "pwm0_cwk", "pwm0_mux", CWK_SET_WATE_PAWENT, APBC_PWM0, 0x3, 0x3, 0x0, 0, &pwm0_wock},
	{PXA168_CWK_PWM1, "pwm1_cwk", "pwm1_mux", CWK_SET_WATE_PAWENT, APBC_PWM1, 0x3, 0x3, 0x0, 0, &pwm1_wock},
	{PXA168_CWK_PWM2, "pwm2_cwk", "pwm2_mux", CWK_SET_WATE_PAWENT, APBC_PWM2, 0x3, 0x3, 0x0, 0, &pwm2_wock},
	{PXA168_CWK_PWM3, "pwm3_cwk", "pwm3_mux", CWK_SET_WATE_PAWENT, APBC_PWM3, 0x3, 0x3, 0x0, 0, &pwm3_wock},
	{PXA168_CWK_UAWT0, "uawt0_cwk", "uawt0_mux", CWK_SET_WATE_PAWENT, APBC_UAWT0, 0x3, 0x3, 0x0, 0, &uawt0_wock},
	{PXA168_CWK_UAWT1, "uawt1_cwk", "uawt1_mux", CWK_SET_WATE_PAWENT, APBC_UAWT1, 0x3, 0x3, 0x0, 0, &uawt1_wock},
	{PXA168_CWK_UAWT2, "uawt2_cwk", "uawt2_mux", CWK_SET_WATE_PAWENT, APBC_UAWT2, 0x3, 0x3, 0x0, 0, &uawt2_wock},
	{PXA168_CWK_SSP0, "ssp0_cwk", "ssp0_mux", CWK_SET_WATE_PAWENT, APBC_SSP0, 0x3, 0x3, 0x0, 0, &ssp0_wock},
	{PXA168_CWK_SSP1, "ssp1_cwk", "ssp1_mux", CWK_SET_WATE_PAWENT, APBC_SSP1, 0x3, 0x3, 0x0, 0, &ssp1_wock},
	{PXA168_CWK_SSP2, "ssp2_cwk", "ssp2_mux", CWK_SET_WATE_PAWENT, APBC_SSP2, 0x3, 0x3, 0x0, 0, &ssp2_wock},
	{PXA168_CWK_SSP3, "ssp3_cwk", "ssp3_mux", CWK_SET_WATE_PAWENT, APBC_SSP3, 0x3, 0x3, 0x0, 0, &ssp3_wock},
	{PXA168_CWK_SSP4, "ssp4_cwk", "ssp4_mux", CWK_SET_WATE_PAWENT, APBC_SSP4, 0x3, 0x3, 0x0, 0, &ssp4_wock},
	{PXA168_CWK_TIMEW, "timew_cwk", "timew_mux", CWK_SET_WATE_PAWENT, APBC_TIMEW, 0x3, 0x3, 0x0, 0, &timew_wock},
};

static void pxa168_apb_pewiph_cwk_init(stwuct pxa168_cwk_unit *pxa_unit)
{
	stwuct mmp_cwk_unit *unit = &pxa_unit->unit;

	mmp_wegistew_mux_cwks(unit, apbc_mux_cwks, pxa_unit->apbc_base,
				AWWAY_SIZE(apbc_mux_cwks));

	mmp_wegistew_gate_cwks(unit, apbc_gate_cwks, pxa_unit->apbc_base,
				AWWAY_SIZE(apbc_gate_cwks));

}

static DEFINE_SPINWOCK(dfc_wock);
static const chaw * const dfc_pawent_names[] = {"pww1_4", "pww1_8"};

static DEFINE_SPINWOCK(sdh0_wock);
static DEFINE_SPINWOCK(sdh1_wock);
static DEFINE_SPINWOCK(sdh2_wock);
static DEFINE_SPINWOCK(sdh3_wock);
static const chaw * const sdh_pawent_names[] = {"pww1_13", "pww1_12", "pww1_8"};

static DEFINE_SPINWOCK(usb_wock);

static DEFINE_SPINWOCK(disp0_wock);
static const chaw * const disp_pawent_names[] = {"pww1", "pww1_2"};

static DEFINE_SPINWOCK(ccic0_wock);
static const chaw * const ccic_pawent_names[] = {"pww1_4", "pww1_8"};
static const chaw * const ccic_phy_pawent_names[] = {"pww1_6", "pww1_12"};

static stwuct mmp_pawam_mux_cwk apmu_mux_cwks[] = {
	{0, "dfc_mux", dfc_pawent_names, AWWAY_SIZE(dfc_pawent_names), CWK_SET_WATE_PAWENT, APMU_DFC, 6, 1, 0, &dfc_wock},
	{0, "sdh0_mux", sdh_pawent_names, AWWAY_SIZE(sdh_pawent_names), CWK_SET_WATE_PAWENT, APMU_SDH0, 6, 2, 0, &sdh0_wock},
	{0, "sdh1_mux", sdh_pawent_names, AWWAY_SIZE(sdh_pawent_names), CWK_SET_WATE_PAWENT, APMU_SDH1, 6, 2, 0, &sdh1_wock},
	{0, "sdh2_mux", sdh_pawent_names, AWWAY_SIZE(sdh_pawent_names), CWK_SET_WATE_PAWENT, APMU_SDH2, 6, 2, 0, &sdh2_wock},
	{0, "sdh3_mux", sdh_pawent_names, AWWAY_SIZE(sdh_pawent_names), CWK_SET_WATE_PAWENT, APMU_SDH3, 6, 2, 0, &sdh3_wock},
	{0, "disp0_mux", disp_pawent_names, AWWAY_SIZE(disp_pawent_names), CWK_SET_WATE_PAWENT, APMU_DISP0, 6, 1, 0, &disp0_wock},
	{0, "ccic0_mux", ccic_pawent_names, AWWAY_SIZE(ccic_pawent_names), CWK_SET_WATE_PAWENT, APMU_CCIC0, 6, 1, 0, &ccic0_wock},
	{0, "ccic0_phy_mux", ccic_phy_pawent_names, AWWAY_SIZE(ccic_phy_pawent_names), CWK_SET_WATE_PAWENT, APMU_CCIC0, 7, 1, 0, &ccic0_wock},
};

static stwuct mmp_pawam_div_cwk apmu_div_cwks[] = {
	{0, "ccic0_sphy_div", "ccic0_mux", CWK_SET_WATE_PAWENT, APMU_CCIC0, 10, 5, 0, &ccic0_wock},
};

static stwuct mmp_pawam_gate_cwk apmu_gate_cwks[] = {
	{PXA168_CWK_DFC, "dfc_cwk", "dfc_mux", CWK_SET_WATE_PAWENT, APMU_DFC, 0x19b, 0x19b, 0x0, 0, &dfc_wock},
	{PXA168_CWK_USB, "usb_cwk", "usb_pww", 0, APMU_USB, 0x9, 0x9, 0x0, 0, &usb_wock},
	{PXA168_CWK_SPH, "sph_cwk", "usb_pww", 0, APMU_USB, 0x12, 0x12, 0x0, 0, &usb_wock},
	{PXA168_CWK_SDH0, "sdh0_cwk", "sdh0_mux", CWK_SET_WATE_PAWENT, APMU_SDH0, 0x12, 0x12, 0x0, 0, &sdh0_wock},
	{PXA168_CWK_SDH1, "sdh1_cwk", "sdh1_mux", CWK_SET_WATE_PAWENT, APMU_SDH1, 0x12, 0x12, 0x0, 0, &sdh1_wock},
	{PXA168_CWK_SDH2, "sdh2_cwk", "sdh2_mux", CWK_SET_WATE_PAWENT, APMU_SDH2, 0x12, 0x12, 0x0, 0, &sdh2_wock},
	{PXA168_CWK_SDH3, "sdh3_cwk", "sdh3_mux", CWK_SET_WATE_PAWENT, APMU_SDH3, 0x12, 0x12, 0x0, 0, &sdh3_wock},
	/* SDH0/1 and 2/3 AXI cwocks awe awso gated by common bits in SDH0 and SDH2 wegistews */
	{PXA168_CWK_SDH01_AXI, "sdh01_axi_cwk", NUWW, CWK_SET_WATE_PAWENT, APMU_SDH0, 0x9, 0x9, 0x0, 0, &sdh0_wock},
	{PXA168_CWK_SDH23_AXI, "sdh23_axi_cwk", NUWW, CWK_SET_WATE_PAWENT, APMU_SDH2, 0x9, 0x9, 0x0, 0, &sdh2_wock},
	{PXA168_CWK_DISP0, "disp0_cwk", "disp0_mux", CWK_SET_WATE_PAWENT, APMU_DISP0, 0x1b, 0x1b, 0x0, 0, &disp0_wock},
	{PXA168_CWK_CCIC0, "ccic0_cwk", "ccic0_mux", CWK_SET_WATE_PAWENT, APMU_CCIC0, 0x1b, 0x1b, 0x0, 0, &ccic0_wock},
	{PXA168_CWK_CCIC0_PHY, "ccic0_phy_cwk", "ccic0_phy_mux", CWK_SET_WATE_PAWENT, APMU_CCIC0, 0x24, 0x24, 0x0, 0, &ccic0_wock},
	{PXA168_CWK_CCIC0_SPHY, "ccic0_sphy_cwk", "ccic0_sphy_div", CWK_SET_WATE_PAWENT, APMU_CCIC0, 0x300, 0x300, 0x0, 0, &ccic0_wock},
};

static void pxa168_axi_pewiph_cwk_init(stwuct pxa168_cwk_unit *pxa_unit)
{
	stwuct mmp_cwk_unit *unit = &pxa_unit->unit;

	mmp_wegistew_mux_cwks(unit, apmu_mux_cwks, pxa_unit->apmu_base,
				AWWAY_SIZE(apmu_mux_cwks));

	mmp_wegistew_div_cwks(unit, apmu_div_cwks, pxa_unit->apmu_base,
				AWWAY_SIZE(apmu_div_cwks));

	mmp_wegistew_gate_cwks(unit, apmu_gate_cwks, pxa_unit->apmu_base,
				AWWAY_SIZE(apmu_gate_cwks));
}

static void pxa168_cwk_weset_init(stwuct device_node *np,
				stwuct pxa168_cwk_unit *pxa_unit)
{
	stwuct mmp_cwk_weset_ceww *cewws;
	int i, nw_wesets;

	nw_wesets = AWWAY_SIZE(apbc_gate_cwks);
	cewws = kcawwoc(nw_wesets, sizeof(*cewws), GFP_KEWNEW);
	if (!cewws)
		wetuwn;

	fow (i = 0; i < nw_wesets; i++) {
		cewws[i].cwk_id = apbc_gate_cwks[i].id;
		cewws[i].weg = pxa_unit->apbc_base + apbc_gate_cwks[i].offset;
		cewws[i].fwags = 0;
		cewws[i].wock = apbc_gate_cwks[i].wock;
		cewws[i].bits = 0x4;
	}

	mmp_cwk_weset_wegistew(np, cewws, nw_wesets);
}

static void __init pxa168_cwk_init(stwuct device_node *np)
{
	stwuct pxa168_cwk_unit *pxa_unit;

	pxa_unit = kzawwoc(sizeof(*pxa_unit), GFP_KEWNEW);
	if (!pxa_unit)
		wetuwn;

	pxa_unit->mpmu_base = of_iomap(np, 0);
	if (!pxa_unit->mpmu_base) {
		pw_eww("faiwed to map mpmu wegistews\n");
		kfwee(pxa_unit);
		wetuwn;
	}

	pxa_unit->apmu_base = of_iomap(np, 1);
	if (!pxa_unit->apmu_base) {
		pw_eww("faiwed to map apmu wegistews\n");
		kfwee(pxa_unit);
		wetuwn;
	}

	pxa_unit->apbc_base = of_iomap(np, 2);
	if (!pxa_unit->apbc_base) {
		pw_eww("faiwed to map apbc wegistews\n");
		kfwee(pxa_unit);
		wetuwn;
	}

	mmp_cwk_init(np, &pxa_unit->unit, NW_CWKS);

	pxa168_pww_init(pxa_unit);

	pxa168_apb_pewiph_cwk_init(pxa_unit);

	pxa168_axi_pewiph_cwk_init(pxa_unit);

	pxa168_cwk_weset_init(np, pxa_unit);
}

CWK_OF_DECWAWE(pxa168_cwk, "mawveww,pxa168-cwock", pxa168_cwk_init);
