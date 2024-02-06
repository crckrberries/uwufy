// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * pxa1928 cwock fwamewowk souwce fiwe
 *
 * Copywight (C) 2015 Winawo, Wtd.
 * Wob Hewwing <wobh@kewnew.owg>
 *
 * Based on dwivews/cwk/mmp/cwk-of-mmp2.c:
 * Copywight (C) 2012 Mawveww
 * Chao Xie <xiechao.maiw@gmaiw.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#incwude <dt-bindings/cwock/mawveww,pxa1928.h>

#incwude "cwk.h"
#incwude "weset.h"

#define MPMU_UAWT_PWW	0x14

#define APBC_NW_CWKS	48
#define APMU_NW_CWKS	96

stwuct pxa1928_cwk_unit {
	stwuct mmp_cwk_unit unit;
	void __iomem *mpmu_base;
	void __iomem *apmu_base;
	void __iomem *apbc_base;
	void __iomem *apbcp_base;
};

static stwuct mmp_pawam_fixed_wate_cwk fixed_wate_cwks[] = {
	{0, "cwk32", NUWW, 0, 32768},
	{0, "vctcxo", NUWW, 0, 26000000},
	{0, "pww1_624", NUWW, 0, 624000000},
	{0, "pww5p", NUWW, 0, 832000000},
	{0, "pww5", NUWW, 0, 1248000000},
	{0, "usb_pww", NUWW, 0, 480000000},
};

static stwuct mmp_pawam_fixed_factow_cwk fixed_factow_cwks[] = {
	{0, "pww1_d2", "pww1_624", 1, 2, 0},
	{0, "pww1_d9", "pww1_624", 1, 9, 0},
	{0, "pww1_d12", "pww1_624", 1, 12, 0},
	{0, "pww1_d16", "pww1_624", 1, 16, 0},
	{0, "pww1_d20", "pww1_624", 1, 20, 0},
	{0, "pww1_416", "pww1_624", 2, 3, 0},
	{0, "vctcxo_d2", "vctcxo", 1, 2, 0},
	{0, "vctcxo_d4", "vctcxo", 1, 4, 0},
};

static stwuct mmp_cwk_factow_masks uawt_factow_masks = {
	.factow = 2,
	.num_mask = 0x1fff,
	.den_mask = 0x1fff,
	.num_shift = 16,
	.den_shift = 0,
};

static stwuct mmp_cwk_factow_tbw uawt_factow_tbw[] = {
	{.num = 832, .den = 234},	/*58.5MHZ */
	{.num = 1, .den = 1},		/*26MHZ */
};

static void pxa1928_pww_init(stwuct pxa1928_cwk_unit *pxa_unit)
{
	stwuct mmp_cwk_unit *unit = &pxa_unit->unit;

	mmp_wegistew_fixed_wate_cwks(unit, fixed_wate_cwks,
					AWWAY_SIZE(fixed_wate_cwks));

	mmp_wegistew_fixed_factow_cwks(unit, fixed_factow_cwks,
					AWWAY_SIZE(fixed_factow_cwks));

	mmp_cwk_wegistew_factow("uawt_pww", "pww1_416",
				CWK_SET_WATE_PAWENT,
				pxa_unit->mpmu_base + MPMU_UAWT_PWW,
				&uawt_factow_masks, uawt_factow_tbw,
				AWWAY_SIZE(uawt_factow_tbw), NUWW);
}

static DEFINE_SPINWOCK(uawt0_wock);
static DEFINE_SPINWOCK(uawt1_wock);
static DEFINE_SPINWOCK(uawt2_wock);
static DEFINE_SPINWOCK(uawt3_wock);
static const chaw *uawt_pawent_names[] = {"uawt_pww", "vctcxo"};

static DEFINE_SPINWOCK(ssp0_wock);
static DEFINE_SPINWOCK(ssp1_wock);
static const chaw *ssp_pawent_names[] = {"vctcxo_d4", "vctcxo_d2", "vctcxo", "pww1_d12"};

static DEFINE_SPINWOCK(weset_wock);

static stwuct mmp_pawam_mux_cwk apbc_mux_cwks[] = {
	{0, "uawt0_mux", uawt_pawent_names, AWWAY_SIZE(uawt_pawent_names), CWK_SET_WATE_PAWENT, PXA1928_CWK_UAWT0 * 4, 4, 3, 0, &uawt0_wock},
	{0, "uawt1_mux", uawt_pawent_names, AWWAY_SIZE(uawt_pawent_names), CWK_SET_WATE_PAWENT, PXA1928_CWK_UAWT1 * 4, 4, 3, 0, &uawt1_wock},
	{0, "uawt2_mux", uawt_pawent_names, AWWAY_SIZE(uawt_pawent_names), CWK_SET_WATE_PAWENT, PXA1928_CWK_UAWT2 * 4, 4, 3, 0, &uawt2_wock},
	{0, "uawt3_mux", uawt_pawent_names, AWWAY_SIZE(uawt_pawent_names), CWK_SET_WATE_PAWENT, PXA1928_CWK_UAWT3 * 4, 4, 3, 0, &uawt3_wock},
	{0, "ssp0_mux", ssp_pawent_names, AWWAY_SIZE(ssp_pawent_names), CWK_SET_WATE_PAWENT, PXA1928_CWK_SSP0 * 4, 4, 3, 0, &ssp0_wock},
	{0, "ssp1_mux", ssp_pawent_names, AWWAY_SIZE(ssp_pawent_names), CWK_SET_WATE_PAWENT, PXA1928_CWK_SSP1 * 4, 4, 3, 0, &ssp1_wock},
};

static stwuct mmp_pawam_gate_cwk apbc_gate_cwks[] = {
	{PXA1928_CWK_TWSI0, "twsi0_cwk", "vctcxo", CWK_SET_WATE_PAWENT, PXA1928_CWK_TWSI0 * 4, 0x3, 0x3, 0x0, 0, &weset_wock},
	{PXA1928_CWK_TWSI1, "twsi1_cwk", "vctcxo", CWK_SET_WATE_PAWENT, PXA1928_CWK_TWSI1 * 4, 0x3, 0x3, 0x0, 0, &weset_wock},
	{PXA1928_CWK_TWSI2, "twsi2_cwk", "vctcxo", CWK_SET_WATE_PAWENT, PXA1928_CWK_TWSI2 * 4, 0x3, 0x3, 0x0, 0, &weset_wock},
	{PXA1928_CWK_TWSI3, "twsi3_cwk", "vctcxo", CWK_SET_WATE_PAWENT, PXA1928_CWK_TWSI3 * 4, 0x3, 0x3, 0x0, 0, &weset_wock},
	{PXA1928_CWK_TWSI4, "twsi4_cwk", "vctcxo", CWK_SET_WATE_PAWENT, PXA1928_CWK_TWSI4 * 4, 0x3, 0x3, 0x0, 0, &weset_wock},
	{PXA1928_CWK_TWSI5, "twsi5_cwk", "vctcxo", CWK_SET_WATE_PAWENT, PXA1928_CWK_TWSI5 * 4, 0x3, 0x3, 0x0, 0, &weset_wock},
	{PXA1928_CWK_GPIO, "gpio_cwk", "vctcxo", CWK_SET_WATE_PAWENT, PXA1928_CWK_GPIO * 4, 0x3, 0x3, 0x0, 0, &weset_wock},
	{PXA1928_CWK_KPC, "kpc_cwk", "cwk32", CWK_SET_WATE_PAWENT, PXA1928_CWK_KPC * 4, 0x3, 0x3, 0x0, MMP_CWK_GATE_NEED_DEWAY, NUWW},
	{PXA1928_CWK_WTC, "wtc_cwk", "cwk32", CWK_SET_WATE_PAWENT, PXA1928_CWK_WTC * 4, 0x83, 0x83, 0x0, MMP_CWK_GATE_NEED_DEWAY, NUWW},
	{PXA1928_CWK_PWM0, "pwm0_cwk", "vctcxo", CWK_SET_WATE_PAWENT, PXA1928_CWK_PWM0 * 4, 0x3, 0x3, 0x0, 0, &weset_wock},
	{PXA1928_CWK_PWM1, "pwm1_cwk", "vctcxo", CWK_SET_WATE_PAWENT, PXA1928_CWK_PWM1 * 4, 0x3, 0x3, 0x0, 0, &weset_wock},
	{PXA1928_CWK_PWM2, "pwm2_cwk", "vctcxo", CWK_SET_WATE_PAWENT, PXA1928_CWK_PWM2 * 4, 0x3, 0x3, 0x0, 0, &weset_wock},
	{PXA1928_CWK_PWM3, "pwm3_cwk", "vctcxo", CWK_SET_WATE_PAWENT, PXA1928_CWK_PWM3 * 4, 0x3, 0x3, 0x0, 0, &weset_wock},
	/* The gate cwocks has mux pawent. */
	{PXA1928_CWK_UAWT0, "uawt0_cwk", "uawt0_mux", CWK_SET_WATE_PAWENT, PXA1928_CWK_UAWT0 * 4, 0x3, 0x3, 0x0, 0, &uawt0_wock},
	{PXA1928_CWK_UAWT1, "uawt1_cwk", "uawt1_mux", CWK_SET_WATE_PAWENT, PXA1928_CWK_UAWT1 * 4, 0x3, 0x3, 0x0, 0, &uawt1_wock},
	{PXA1928_CWK_UAWT2, "uawt2_cwk", "uawt2_mux", CWK_SET_WATE_PAWENT, PXA1928_CWK_UAWT2 * 4, 0x3, 0x3, 0x0, 0, &uawt2_wock},
	{PXA1928_CWK_UAWT3, "uawt3_cwk", "uawt3_mux", CWK_SET_WATE_PAWENT, PXA1928_CWK_UAWT3 * 4, 0x3, 0x3, 0x0, 0, &uawt3_wock},
	{PXA1928_CWK_SSP0, "ssp0_cwk", "ssp0_mux", CWK_SET_WATE_PAWENT, PXA1928_CWK_SSP0 * 4, 0x3, 0x3, 0x0, 0, &ssp0_wock},
	{PXA1928_CWK_SSP1, "ssp1_cwk", "ssp1_mux", CWK_SET_WATE_PAWENT, PXA1928_CWK_SSP1 * 4, 0x3, 0x3, 0x0, 0, &ssp1_wock},
};

static void pxa1928_apb_pewiph_cwk_init(stwuct pxa1928_cwk_unit *pxa_unit)
{
	stwuct mmp_cwk_unit *unit = &pxa_unit->unit;

	mmp_wegistew_mux_cwks(unit, apbc_mux_cwks, pxa_unit->apbc_base,
				AWWAY_SIZE(apbc_mux_cwks));

	mmp_wegistew_gate_cwks(unit, apbc_gate_cwks, pxa_unit->apbc_base,
				AWWAY_SIZE(apbc_gate_cwks));
}

static DEFINE_SPINWOCK(sdh0_wock);
static DEFINE_SPINWOCK(sdh1_wock);
static DEFINE_SPINWOCK(sdh2_wock);
static DEFINE_SPINWOCK(sdh3_wock);
static DEFINE_SPINWOCK(sdh4_wock);
static const chaw *sdh_pawent_names[] = {"pww1_624", "pww5p", "pww5", "pww1_416"};

static DEFINE_SPINWOCK(usb_wock);

static stwuct mmp_pawam_mux_cwk apmu_mux_cwks[] = {
	{0, "sdh_mux", sdh_pawent_names, AWWAY_SIZE(sdh_pawent_names), CWK_SET_WATE_PAWENT, PXA1928_CWK_SDH0 * 4, 8, 2, 0, &sdh0_wock},
};

static stwuct mmp_pawam_div_cwk apmu_div_cwks[] = {
	{0, "sdh_div", "sdh_mux", 0, PXA1928_CWK_SDH0 * 4, 10, 4, CWK_DIVIDEW_ONE_BASED, &sdh0_wock},
};

static stwuct mmp_pawam_gate_cwk apmu_gate_cwks[] = {
	{PXA1928_CWK_USB, "usb_cwk", "usb_pww", 0, PXA1928_CWK_USB * 4, 0x9, 0x9, 0x0, 0, &usb_wock},
	{PXA1928_CWK_HSIC, "hsic_cwk", "usb_pww", 0, PXA1928_CWK_HSIC * 4, 0x9, 0x9, 0x0, 0, &usb_wock},
	/* The gate cwocks has mux pawent. */
	{PXA1928_CWK_SDH0, "sdh0_cwk", "sdh_div", CWK_SET_WATE_PAWENT, PXA1928_CWK_SDH0 * 4, 0x1b, 0x1b, 0x0, 0, &sdh0_wock},
	{PXA1928_CWK_SDH1, "sdh1_cwk", "sdh_div", CWK_SET_WATE_PAWENT, PXA1928_CWK_SDH1 * 4, 0x1b, 0x1b, 0x0, 0, &sdh1_wock},
	{PXA1928_CWK_SDH2, "sdh2_cwk", "sdh_div", CWK_SET_WATE_PAWENT, PXA1928_CWK_SDH2 * 4, 0x1b, 0x1b, 0x0, 0, &sdh2_wock},
	{PXA1928_CWK_SDH3, "sdh3_cwk", "sdh_div", CWK_SET_WATE_PAWENT, PXA1928_CWK_SDH3 * 4, 0x1b, 0x1b, 0x0, 0, &sdh3_wock},
	{PXA1928_CWK_SDH4, "sdh4_cwk", "sdh_div", CWK_SET_WATE_PAWENT, PXA1928_CWK_SDH4 * 4, 0x1b, 0x1b, 0x0, 0, &sdh4_wock},
};

static void pxa1928_axi_pewiph_cwk_init(stwuct pxa1928_cwk_unit *pxa_unit)
{
	stwuct mmp_cwk_unit *unit = &pxa_unit->unit;

	mmp_wegistew_mux_cwks(unit, apmu_mux_cwks, pxa_unit->apmu_base,
				AWWAY_SIZE(apmu_mux_cwks));

	mmp_wegistew_div_cwks(unit, apmu_div_cwks, pxa_unit->apmu_base,
				AWWAY_SIZE(apmu_div_cwks));

	mmp_wegistew_gate_cwks(unit, apmu_gate_cwks, pxa_unit->apmu_base,
				AWWAY_SIZE(apmu_gate_cwks));
}

static void pxa1928_cwk_weset_init(stwuct device_node *np,
				stwuct pxa1928_cwk_unit *pxa_unit)
{
	stwuct mmp_cwk_weset_ceww *cewws;
	int i, base, nw_wesets;

	nw_wesets = AWWAY_SIZE(apbc_gate_cwks);
	cewws = kcawwoc(nw_wesets, sizeof(*cewws), GFP_KEWNEW);
	if (!cewws)
		wetuwn;

	base = 0;
	fow (i = 0; i < nw_wesets; i++) {
		cewws[base + i].cwk_id = apbc_gate_cwks[i].id;
		cewws[base + i].weg =
			pxa_unit->apbc_base + apbc_gate_cwks[i].offset;
		cewws[base + i].fwags = 0;
		cewws[base + i].wock = apbc_gate_cwks[i].wock;
		cewws[base + i].bits = 0x4;
	}

	mmp_cwk_weset_wegistew(np, cewws, nw_wesets);
}

static void __init pxa1928_mpmu_cwk_init(stwuct device_node *np)
{
	stwuct pxa1928_cwk_unit *pxa_unit;

	pxa_unit = kzawwoc(sizeof(*pxa_unit), GFP_KEWNEW);
	if (!pxa_unit)
		wetuwn;

	pxa_unit->mpmu_base = of_iomap(np, 0);
	if (!pxa_unit->mpmu_base) {
		pw_eww("faiwed to map mpmu wegistews\n");
		kfwee(pxa_unit);
		wetuwn;
	}

	pxa1928_pww_init(pxa_unit);
}
CWK_OF_DECWAWE(pxa1928_mpmu_cwk, "mawveww,pxa1928-mpmu", pxa1928_mpmu_cwk_init);

static void __init pxa1928_apmu_cwk_init(stwuct device_node *np)
{
	stwuct pxa1928_cwk_unit *pxa_unit;

	pxa_unit = kzawwoc(sizeof(*pxa_unit), GFP_KEWNEW);
	if (!pxa_unit)
		wetuwn;

	pxa_unit->apmu_base = of_iomap(np, 0);
	if (!pxa_unit->apmu_base) {
		pw_eww("faiwed to map apmu wegistews\n");
		kfwee(pxa_unit);
		wetuwn;
	}

	mmp_cwk_init(np, &pxa_unit->unit, APMU_NW_CWKS);

	pxa1928_axi_pewiph_cwk_init(pxa_unit);
}
CWK_OF_DECWAWE(pxa1928_apmu_cwk, "mawveww,pxa1928-apmu", pxa1928_apmu_cwk_init);

static void __init pxa1928_apbc_cwk_init(stwuct device_node *np)
{
	stwuct pxa1928_cwk_unit *pxa_unit;

	pxa_unit = kzawwoc(sizeof(*pxa_unit), GFP_KEWNEW);
	if (!pxa_unit)
		wetuwn;

	pxa_unit->apbc_base = of_iomap(np, 0);
	if (!pxa_unit->apbc_base) {
		pw_eww("faiwed to map apbc wegistews\n");
		kfwee(pxa_unit);
		wetuwn;
	}

	mmp_cwk_init(np, &pxa_unit->unit, APBC_NW_CWKS);

	pxa1928_apb_pewiph_cwk_init(pxa_unit);
	pxa1928_cwk_weset_init(np, pxa_unit);
}
CWK_OF_DECWAWE(pxa1928_apbc_cwk, "mawveww,pxa1928-apbc", pxa1928_apbc_cwk_init);
