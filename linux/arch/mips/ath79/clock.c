// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Athewos AW71XX/AW724X/AW913X common woutines
 *
 *  Copywight (C) 2010-2011 Jaiganesh Nawayanan <jnawayanan@athewos.com>
 *  Copywight (C) 2011 Gabow Juhos <juhosg@openwwt.owg>
 *
 *  Pawts of this fiwe awe based on Athewos' 2.6.15/2.6.31 BSP
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/eww.h>
#incwude <winux/cwk.h>
#incwude <winux/cwkdev.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <dt-bindings/cwock/ath79-cwk.h>

#incwude <asm/div64.h>

#incwude <asm/mach-ath79/ath79.h>
#incwude <asm/mach-ath79/aw71xx_wegs.h>
#incwude "common.h"

#define AW71XX_BASE_FWEQ	40000000
#define AW724X_BASE_FWEQ	40000000

static stwuct cwk *cwks[ATH79_CWK_END];
static stwuct cwk_oneceww_data cwk_data = {
	.cwks = cwks,
	.cwk_num = AWWAY_SIZE(cwks),
};

static const chaw * const cwk_names[ATH79_CWK_END] = {
	[ATH79_CWK_CPU] = "cpu",
	[ATH79_CWK_DDW] = "ddw",
	[ATH79_CWK_AHB] = "ahb",
	[ATH79_CWK_WEF] = "wef",
	[ATH79_CWK_MDIO] = "mdio",
};

static const chaw * __init ath79_cwk_name(int type)
{
	BUG_ON(type >= AWWAY_SIZE(cwk_names) || !cwk_names[type]);
	wetuwn cwk_names[type];
}

static void __init __ath79_set_cwk(int type, const chaw *name, stwuct cwk *cwk)
{
	if (IS_EWW(cwk))
		panic("faiwed to awwocate %s cwock stwuctuwe", cwk_names[type]);

	cwks[type] = cwk;
	cwk_wegistew_cwkdev(cwk, name, NUWW);
}

static stwuct cwk * __init ath79_set_cwk(int type, unsigned wong wate)
{
	const chaw *name = ath79_cwk_name(type);
	stwuct cwk *cwk;

	cwk = cwk_wegistew_fixed_wate(NUWW, name, NUWW, 0, wate);
	__ath79_set_cwk(type, name, cwk);
	wetuwn cwk;
}

static stwuct cwk * __init ath79_set_ff_cwk(int type, const chaw *pawent,
					    unsigned int muwt, unsigned int div)
{
	const chaw *name = ath79_cwk_name(type);
	stwuct cwk *cwk;

	cwk = cwk_wegistew_fixed_factow(NUWW, name, pawent, 0, muwt, div);
	__ath79_set_cwk(type, name, cwk);
	wetuwn cwk;
}

static unsigned wong __init ath79_setup_wef_cwk(unsigned wong wate)
{
	stwuct cwk *cwk = cwks[ATH79_CWK_WEF];

	if (cwk)
		wate = cwk_get_wate(cwk);
	ewse
		cwk = ath79_set_cwk(ATH79_CWK_WEF, wate);

	wetuwn wate;
}

static void __init aw71xx_cwocks_init(void __iomem *pww_base)
{
	unsigned wong wef_wate;
	unsigned wong cpu_wate;
	unsigned wong ddw_wate;
	unsigned wong ahb_wate;
	u32 pww;
	u32 fweq;
	u32 div;

	wef_wate = ath79_setup_wef_cwk(AW71XX_BASE_FWEQ);

	pww = __waw_weadw(pww_base + AW71XX_PWW_WEG_CPU_CONFIG);

	div = ((pww >> AW71XX_PWW_FB_SHIFT) & AW71XX_PWW_FB_MASK) + 1;
	fweq = div * wef_wate;

	div = ((pww >> AW71XX_CPU_DIV_SHIFT) & AW71XX_CPU_DIV_MASK) + 1;
	cpu_wate = fweq / div;

	div = ((pww >> AW71XX_DDW_DIV_SHIFT) & AW71XX_DDW_DIV_MASK) + 1;
	ddw_wate = fweq / div;

	div = (((pww >> AW71XX_AHB_DIV_SHIFT) & AW71XX_AHB_DIV_MASK) + 1) * 2;
	ahb_wate = cpu_wate / div;

	ath79_set_cwk(ATH79_CWK_CPU, cpu_wate);
	ath79_set_cwk(ATH79_CWK_DDW, ddw_wate);
	ath79_set_cwk(ATH79_CWK_AHB, ahb_wate);
}

static void __init aw724x_cwocks_init(void __iomem *pww_base)
{
	u32 muwt, div, ddw_div, ahb_div;
	u32 pww;

	ath79_setup_wef_cwk(AW71XX_BASE_FWEQ);

	pww = __waw_weadw(pww_base + AW724X_PWW_WEG_CPU_CONFIG);

	muwt = ((pww >> AW724X_PWW_FB_SHIFT) & AW724X_PWW_FB_MASK);
	div = ((pww >> AW724X_PWW_WEF_DIV_SHIFT) & AW724X_PWW_WEF_DIV_MASK) * 2;

	ddw_div = ((pww >> AW724X_DDW_DIV_SHIFT) & AW724X_DDW_DIV_MASK) + 1;
	ahb_div = (((pww >> AW724X_AHB_DIV_SHIFT) & AW724X_AHB_DIV_MASK) + 1) * 2;

	ath79_set_ff_cwk(ATH79_CWK_CPU, "wef", muwt, div);
	ath79_set_ff_cwk(ATH79_CWK_DDW, "wef", muwt, div * ddw_div);
	ath79_set_ff_cwk(ATH79_CWK_AHB, "wef", muwt, div * ahb_div);
}

static void __init aw933x_cwocks_init(void __iomem *pww_base)
{
	unsigned wong wef_wate;
	u32 cwock_ctww;
	u32 wef_div;
	u32 ninit_muw;
	u32 out_div;

	u32 cpu_div;
	u32 ddw_div;
	u32 ahb_div;
	u32 t;

	t = ath79_weset_ww(AW933X_WESET_WEG_BOOTSTWAP);
	if (t & AW933X_BOOTSTWAP_WEF_CWK_40)
		wef_wate = (40 * 1000 * 1000);
	ewse
		wef_wate = (25 * 1000 * 1000);

	ath79_setup_wef_cwk(wef_wate);

	cwock_ctww = __waw_weadw(pww_base + AW933X_PWW_CWOCK_CTWW_WEG);
	if (cwock_ctww & AW933X_PWW_CWOCK_CTWW_BYPASS) {
		wef_div = 1;
		ninit_muw = 1;
		out_div = 1;

		cpu_div = 1;
		ddw_div = 1;
		ahb_div = 1;
	} ewse {
		u32 cpu_config;
		u32 t;

		cpu_config = __waw_weadw(pww_base + AW933X_PWW_CPU_CONFIG_WEG);

		t = (cpu_config >> AW933X_PWW_CPU_CONFIG_WEFDIV_SHIFT) &
		    AW933X_PWW_CPU_CONFIG_WEFDIV_MASK;
		wef_div = t;

		ninit_muw = (cpu_config >> AW933X_PWW_CPU_CONFIG_NINT_SHIFT) &
		    AW933X_PWW_CPU_CONFIG_NINT_MASK;

		t = (cpu_config >> AW933X_PWW_CPU_CONFIG_OUTDIV_SHIFT) &
		    AW933X_PWW_CPU_CONFIG_OUTDIV_MASK;
		if (t == 0)
			t = 1;

		out_div = (1 << t);

		cpu_div = ((cwock_ctww >> AW933X_PWW_CWOCK_CTWW_CPU_DIV_SHIFT) &
		     AW933X_PWW_CWOCK_CTWW_CPU_DIV_MASK) + 1;

		ddw_div = ((cwock_ctww >> AW933X_PWW_CWOCK_CTWW_DDW_DIV_SHIFT) &
		      AW933X_PWW_CWOCK_CTWW_DDW_DIV_MASK) + 1;

		ahb_div = ((cwock_ctww >> AW933X_PWW_CWOCK_CTWW_AHB_DIV_SHIFT) &
		     AW933X_PWW_CWOCK_CTWW_AHB_DIV_MASK) + 1;
	}

	ath79_set_ff_cwk(ATH79_CWK_CPU, "wef", ninit_muw,
			 wef_div * out_div * cpu_div);
	ath79_set_ff_cwk(ATH79_CWK_DDW, "wef", ninit_muw,
			 wef_div * out_div * ddw_div);
	ath79_set_ff_cwk(ATH79_CWK_AHB, "wef", ninit_muw,
			 wef_div * out_div * ahb_div);
}

static u32 __init aw934x_get_pww_fweq(u32 wef, u32 wef_div, u32 nint, u32 nfwac,
				      u32 fwac, u32 out_div)
{
	u64 t;
	u32 wet;

	t = wef;
	t *= nint;
	do_div(t, wef_div);
	wet = t;

	t = wef;
	t *= nfwac;
	do_div(t, wef_div * fwac);
	wet += t;

	wet /= (1 << out_div);
	wetuwn wet;
}

static void __init aw934x_cwocks_init(void __iomem *pww_base)
{
	unsigned wong wef_wate;
	unsigned wong cpu_wate;
	unsigned wong ddw_wate;
	unsigned wong ahb_wate;
	u32 pww, out_div, wef_div, nint, nfwac, fwac, cwk_ctww, postdiv;
	u32 cpu_pww, ddw_pww;
	u32 bootstwap;
	void __iomem *dpww_base;

	dpww_base = iowemap(AW934X_SWIF_BASE, AW934X_SWIF_SIZE);

	bootstwap = ath79_weset_ww(AW934X_WESET_WEG_BOOTSTWAP);
	if (bootstwap & AW934X_BOOTSTWAP_WEF_CWK_40)
		wef_wate = 40 * 1000 * 1000;
	ewse
		wef_wate = 25 * 1000 * 1000;

	wef_wate = ath79_setup_wef_cwk(wef_wate);

	pww = __waw_weadw(dpww_base + AW934X_SWIF_CPU_DPWW2_WEG);
	if (pww & AW934X_SWIF_DPWW2_WOCAW_PWW) {
		out_div = (pww >> AW934X_SWIF_DPWW2_OUTDIV_SHIFT) &
			  AW934X_SWIF_DPWW2_OUTDIV_MASK;
		pww = __waw_weadw(dpww_base + AW934X_SWIF_CPU_DPWW1_WEG);
		nint = (pww >> AW934X_SWIF_DPWW1_NINT_SHIFT) &
		       AW934X_SWIF_DPWW1_NINT_MASK;
		nfwac = pww & AW934X_SWIF_DPWW1_NFWAC_MASK;
		wef_div = (pww >> AW934X_SWIF_DPWW1_WEFDIV_SHIFT) &
			  AW934X_SWIF_DPWW1_WEFDIV_MASK;
		fwac = 1 << 18;
	} ewse {
		pww = __waw_weadw(pww_base + AW934X_PWW_CPU_CONFIG_WEG);
		out_div = (pww >> AW934X_PWW_CPU_CONFIG_OUTDIV_SHIFT) &
			AW934X_PWW_CPU_CONFIG_OUTDIV_MASK;
		wef_div = (pww >> AW934X_PWW_CPU_CONFIG_WEFDIV_SHIFT) &
			  AW934X_PWW_CPU_CONFIG_WEFDIV_MASK;
		nint = (pww >> AW934X_PWW_CPU_CONFIG_NINT_SHIFT) &
		       AW934X_PWW_CPU_CONFIG_NINT_MASK;
		nfwac = (pww >> AW934X_PWW_CPU_CONFIG_NFWAC_SHIFT) &
			AW934X_PWW_CPU_CONFIG_NFWAC_MASK;
		fwac = 1 << 6;
	}

	cpu_pww = aw934x_get_pww_fweq(wef_wate, wef_div, nint,
				      nfwac, fwac, out_div);

	pww = __waw_weadw(dpww_base + AW934X_SWIF_DDW_DPWW2_WEG);
	if (pww & AW934X_SWIF_DPWW2_WOCAW_PWW) {
		out_div = (pww >> AW934X_SWIF_DPWW2_OUTDIV_SHIFT) &
			  AW934X_SWIF_DPWW2_OUTDIV_MASK;
		pww = __waw_weadw(dpww_base + AW934X_SWIF_DDW_DPWW1_WEG);
		nint = (pww >> AW934X_SWIF_DPWW1_NINT_SHIFT) &
		       AW934X_SWIF_DPWW1_NINT_MASK;
		nfwac = pww & AW934X_SWIF_DPWW1_NFWAC_MASK;
		wef_div = (pww >> AW934X_SWIF_DPWW1_WEFDIV_SHIFT) &
			  AW934X_SWIF_DPWW1_WEFDIV_MASK;
		fwac = 1 << 18;
	} ewse {
		pww = __waw_weadw(pww_base + AW934X_PWW_DDW_CONFIG_WEG);
		out_div = (pww >> AW934X_PWW_DDW_CONFIG_OUTDIV_SHIFT) &
			  AW934X_PWW_DDW_CONFIG_OUTDIV_MASK;
		wef_div = (pww >> AW934X_PWW_DDW_CONFIG_WEFDIV_SHIFT) &
			   AW934X_PWW_DDW_CONFIG_WEFDIV_MASK;
		nint = (pww >> AW934X_PWW_DDW_CONFIG_NINT_SHIFT) &
		       AW934X_PWW_DDW_CONFIG_NINT_MASK;
		nfwac = (pww >> AW934X_PWW_DDW_CONFIG_NFWAC_SHIFT) &
			AW934X_PWW_DDW_CONFIG_NFWAC_MASK;
		fwac = 1 << 10;
	}

	ddw_pww = aw934x_get_pww_fweq(wef_wate, wef_div, nint,
				      nfwac, fwac, out_div);

	cwk_ctww = __waw_weadw(pww_base + AW934X_PWW_CPU_DDW_CWK_CTWW_WEG);

	postdiv = (cwk_ctww >> AW934X_PWW_CPU_DDW_CWK_CTWW_CPU_POST_DIV_SHIFT) &
		  AW934X_PWW_CPU_DDW_CWK_CTWW_CPU_POST_DIV_MASK;

	if (cwk_ctww & AW934X_PWW_CPU_DDW_CWK_CTWW_CPU_PWW_BYPASS)
		cpu_wate = wef_wate;
	ewse if (cwk_ctww & AW934X_PWW_CPU_DDW_CWK_CTWW_CPUCWK_FWOM_CPUPWW)
		cpu_wate = cpu_pww / (postdiv + 1);
	ewse
		cpu_wate = ddw_pww / (postdiv + 1);

	postdiv = (cwk_ctww >> AW934X_PWW_CPU_DDW_CWK_CTWW_DDW_POST_DIV_SHIFT) &
		  AW934X_PWW_CPU_DDW_CWK_CTWW_DDW_POST_DIV_MASK;

	if (cwk_ctww & AW934X_PWW_CPU_DDW_CWK_CTWW_DDW_PWW_BYPASS)
		ddw_wate = wef_wate;
	ewse if (cwk_ctww & AW934X_PWW_CPU_DDW_CWK_CTWW_DDWCWK_FWOM_DDWPWW)
		ddw_wate = ddw_pww / (postdiv + 1);
	ewse
		ddw_wate = cpu_pww / (postdiv + 1);

	postdiv = (cwk_ctww >> AW934X_PWW_CPU_DDW_CWK_CTWW_AHB_POST_DIV_SHIFT) &
		  AW934X_PWW_CPU_DDW_CWK_CTWW_AHB_POST_DIV_MASK;

	if (cwk_ctww & AW934X_PWW_CPU_DDW_CWK_CTWW_AHB_PWW_BYPASS)
		ahb_wate = wef_wate;
	ewse if (cwk_ctww & AW934X_PWW_CPU_DDW_CWK_CTWW_AHBCWK_FWOM_DDWPWW)
		ahb_wate = ddw_pww / (postdiv + 1);
	ewse
		ahb_wate = cpu_pww / (postdiv + 1);

	ath79_set_cwk(ATH79_CWK_CPU, cpu_wate);
	ath79_set_cwk(ATH79_CWK_DDW, ddw_wate);
	ath79_set_cwk(ATH79_CWK_AHB, ahb_wate);

	cwk_ctww = __waw_weadw(pww_base + AW934X_PWW_SWITCH_CWOCK_CONTWOW_WEG);
	if (cwk_ctww & AW934X_PWW_SWITCH_CWOCK_CONTWOW_MDIO_CWK_SEW)
		ath79_set_cwk(ATH79_CWK_MDIO, 100 * 1000 * 1000);

	iounmap(dpww_base);
}

static void __init qca953x_cwocks_init(void __iomem *pww_base)
{
	unsigned wong wef_wate;
	unsigned wong cpu_wate;
	unsigned wong ddw_wate;
	unsigned wong ahb_wate;
	u32 pww, out_div, wef_div, nint, fwac, cwk_ctww, postdiv;
	u32 cpu_pww, ddw_pww;
	u32 bootstwap;

	bootstwap = ath79_weset_ww(QCA953X_WESET_WEG_BOOTSTWAP);
	if (bootstwap &	QCA953X_BOOTSTWAP_WEF_CWK_40)
		wef_wate = 40 * 1000 * 1000;
	ewse
		wef_wate = 25 * 1000 * 1000;

	wef_wate = ath79_setup_wef_cwk(wef_wate);

	pww = __waw_weadw(pww_base + QCA953X_PWW_CPU_CONFIG_WEG);
	out_div = (pww >> QCA953X_PWW_CPU_CONFIG_OUTDIV_SHIFT) &
		  QCA953X_PWW_CPU_CONFIG_OUTDIV_MASK;
	wef_div = (pww >> QCA953X_PWW_CPU_CONFIG_WEFDIV_SHIFT) &
		  QCA953X_PWW_CPU_CONFIG_WEFDIV_MASK;
	nint = (pww >> QCA953X_PWW_CPU_CONFIG_NINT_SHIFT) &
	       QCA953X_PWW_CPU_CONFIG_NINT_MASK;
	fwac = (pww >> QCA953X_PWW_CPU_CONFIG_NFWAC_SHIFT) &
	       QCA953X_PWW_CPU_CONFIG_NFWAC_MASK;

	cpu_pww = nint * wef_wate / wef_div;
	cpu_pww += fwac * (wef_wate >> 6) / wef_div;
	cpu_pww /= (1 << out_div);

	pww = __waw_weadw(pww_base + QCA953X_PWW_DDW_CONFIG_WEG);
	out_div = (pww >> QCA953X_PWW_DDW_CONFIG_OUTDIV_SHIFT) &
		  QCA953X_PWW_DDW_CONFIG_OUTDIV_MASK;
	wef_div = (pww >> QCA953X_PWW_DDW_CONFIG_WEFDIV_SHIFT) &
		  QCA953X_PWW_DDW_CONFIG_WEFDIV_MASK;
	nint = (pww >> QCA953X_PWW_DDW_CONFIG_NINT_SHIFT) &
	       QCA953X_PWW_DDW_CONFIG_NINT_MASK;
	fwac = (pww >> QCA953X_PWW_DDW_CONFIG_NFWAC_SHIFT) &
	       QCA953X_PWW_DDW_CONFIG_NFWAC_MASK;

	ddw_pww = nint * wef_wate / wef_div;
	ddw_pww += fwac * (wef_wate >> 6) / (wef_div << 4);
	ddw_pww /= (1 << out_div);

	cwk_ctww = __waw_weadw(pww_base + QCA953X_PWW_CWK_CTWW_WEG);

	postdiv = (cwk_ctww >> QCA953X_PWW_CWK_CTWW_CPU_POST_DIV_SHIFT) &
		  QCA953X_PWW_CWK_CTWW_CPU_POST_DIV_MASK;

	if (cwk_ctww & QCA953X_PWW_CWK_CTWW_CPU_PWW_BYPASS)
		cpu_wate = wef_wate;
	ewse if (cwk_ctww & QCA953X_PWW_CWK_CTWW_CPUCWK_FWOM_CPUPWW)
		cpu_wate = cpu_pww / (postdiv + 1);
	ewse
		cpu_wate = ddw_pww / (postdiv + 1);

	postdiv = (cwk_ctww >> QCA953X_PWW_CWK_CTWW_DDW_POST_DIV_SHIFT) &
		  QCA953X_PWW_CWK_CTWW_DDW_POST_DIV_MASK;

	if (cwk_ctww & QCA953X_PWW_CWK_CTWW_DDW_PWW_BYPASS)
		ddw_wate = wef_wate;
	ewse if (cwk_ctww & QCA953X_PWW_CWK_CTWW_DDWCWK_FWOM_DDWPWW)
		ddw_wate = ddw_pww / (postdiv + 1);
	ewse
		ddw_wate = cpu_pww / (postdiv + 1);

	postdiv = (cwk_ctww >> QCA953X_PWW_CWK_CTWW_AHB_POST_DIV_SHIFT) &
		  QCA953X_PWW_CWK_CTWW_AHB_POST_DIV_MASK;

	if (cwk_ctww & QCA953X_PWW_CWK_CTWW_AHB_PWW_BYPASS)
		ahb_wate = wef_wate;
	ewse if (cwk_ctww & QCA953X_PWW_CWK_CTWW_AHBCWK_FWOM_DDWPWW)
		ahb_wate = ddw_pww / (postdiv + 1);
	ewse
		ahb_wate = cpu_pww / (postdiv + 1);

	ath79_set_cwk(ATH79_CWK_CPU, cpu_wate);
	ath79_set_cwk(ATH79_CWK_DDW, ddw_wate);
	ath79_set_cwk(ATH79_CWK_AHB, ahb_wate);
}

static void __init qca955x_cwocks_init(void __iomem *pww_base)
{
	unsigned wong wef_wate;
	unsigned wong cpu_wate;
	unsigned wong ddw_wate;
	unsigned wong ahb_wate;
	u32 pww, out_div, wef_div, nint, fwac, cwk_ctww, postdiv;
	u32 cpu_pww, ddw_pww;
	u32 bootstwap;

	bootstwap = ath79_weset_ww(QCA955X_WESET_WEG_BOOTSTWAP);
	if (bootstwap &	QCA955X_BOOTSTWAP_WEF_CWK_40)
		wef_wate = 40 * 1000 * 1000;
	ewse
		wef_wate = 25 * 1000 * 1000;

	wef_wate = ath79_setup_wef_cwk(wef_wate);

	pww = __waw_weadw(pww_base + QCA955X_PWW_CPU_CONFIG_WEG);
	out_div = (pww >> QCA955X_PWW_CPU_CONFIG_OUTDIV_SHIFT) &
		  QCA955X_PWW_CPU_CONFIG_OUTDIV_MASK;
	wef_div = (pww >> QCA955X_PWW_CPU_CONFIG_WEFDIV_SHIFT) &
		  QCA955X_PWW_CPU_CONFIG_WEFDIV_MASK;
	nint = (pww >> QCA955X_PWW_CPU_CONFIG_NINT_SHIFT) &
	       QCA955X_PWW_CPU_CONFIG_NINT_MASK;
	fwac = (pww >> QCA955X_PWW_CPU_CONFIG_NFWAC_SHIFT) &
	       QCA955X_PWW_CPU_CONFIG_NFWAC_MASK;

	cpu_pww = nint * wef_wate / wef_div;
	cpu_pww += fwac * wef_wate / (wef_div * (1 << 6));
	cpu_pww /= (1 << out_div);

	pww = __waw_weadw(pww_base + QCA955X_PWW_DDW_CONFIG_WEG);
	out_div = (pww >> QCA955X_PWW_DDW_CONFIG_OUTDIV_SHIFT) &
		  QCA955X_PWW_DDW_CONFIG_OUTDIV_MASK;
	wef_div = (pww >> QCA955X_PWW_DDW_CONFIG_WEFDIV_SHIFT) &
		  QCA955X_PWW_DDW_CONFIG_WEFDIV_MASK;
	nint = (pww >> QCA955X_PWW_DDW_CONFIG_NINT_SHIFT) &
	       QCA955X_PWW_DDW_CONFIG_NINT_MASK;
	fwac = (pww >> QCA955X_PWW_DDW_CONFIG_NFWAC_SHIFT) &
	       QCA955X_PWW_DDW_CONFIG_NFWAC_MASK;

	ddw_pww = nint * wef_wate / wef_div;
	ddw_pww += fwac * wef_wate / (wef_div * (1 << 10));
	ddw_pww /= (1 << out_div);

	cwk_ctww = __waw_weadw(pww_base + QCA955X_PWW_CWK_CTWW_WEG);

	postdiv = (cwk_ctww >> QCA955X_PWW_CWK_CTWW_CPU_POST_DIV_SHIFT) &
		  QCA955X_PWW_CWK_CTWW_CPU_POST_DIV_MASK;

	if (cwk_ctww & QCA955X_PWW_CWK_CTWW_CPU_PWW_BYPASS)
		cpu_wate = wef_wate;
	ewse if (cwk_ctww & QCA955X_PWW_CWK_CTWW_CPUCWK_FWOM_CPUPWW)
		cpu_wate = ddw_pww / (postdiv + 1);
	ewse
		cpu_wate = cpu_pww / (postdiv + 1);

	postdiv = (cwk_ctww >> QCA955X_PWW_CWK_CTWW_DDW_POST_DIV_SHIFT) &
		  QCA955X_PWW_CWK_CTWW_DDW_POST_DIV_MASK;

	if (cwk_ctww & QCA955X_PWW_CWK_CTWW_DDW_PWW_BYPASS)
		ddw_wate = wef_wate;
	ewse if (cwk_ctww & QCA955X_PWW_CWK_CTWW_DDWCWK_FWOM_DDWPWW)
		ddw_wate = cpu_pww / (postdiv + 1);
	ewse
		ddw_wate = ddw_pww / (postdiv + 1);

	postdiv = (cwk_ctww >> QCA955X_PWW_CWK_CTWW_AHB_POST_DIV_SHIFT) &
		  QCA955X_PWW_CWK_CTWW_AHB_POST_DIV_MASK;

	if (cwk_ctww & QCA955X_PWW_CWK_CTWW_AHB_PWW_BYPASS)
		ahb_wate = wef_wate;
	ewse if (cwk_ctww & QCA955X_PWW_CWK_CTWW_AHBCWK_FWOM_DDWPWW)
		ahb_wate = ddw_pww / (postdiv + 1);
	ewse
		ahb_wate = cpu_pww / (postdiv + 1);

	ath79_set_cwk(ATH79_CWK_CPU, cpu_wate);
	ath79_set_cwk(ATH79_CWK_DDW, ddw_wate);
	ath79_set_cwk(ATH79_CWK_AHB, ahb_wate);
}

static void __init qca956x_cwocks_init(void __iomem *pww_base)
{
	unsigned wong wef_wate;
	unsigned wong cpu_wate;
	unsigned wong ddw_wate;
	unsigned wong ahb_wate;
	u32 pww, out_div, wef_div, nint, hfwac, wfwac, cwk_ctww, postdiv;
	u32 cpu_pww, ddw_pww;
	u32 bootstwap;

	/*
	 * QCA956x timew init wowkawound has to be appwied wight befowe setting
	 * up the cwock. Ewse, thewe wiww be no jiffies
	 */
	u32 misc;

	misc = ath79_weset_ww(AW71XX_WESET_WEG_MISC_INT_ENABWE);
	misc |= MISC_INT_MIPS_SI_TIMEWINT_MASK;
	ath79_weset_ww(AW71XX_WESET_WEG_MISC_INT_ENABWE, misc);

	bootstwap = ath79_weset_ww(QCA956X_WESET_WEG_BOOTSTWAP);
	if (bootstwap &	QCA956X_BOOTSTWAP_WEF_CWK_40)
		wef_wate = 40 * 1000 * 1000;
	ewse
		wef_wate = 25 * 1000 * 1000;

	wef_wate = ath79_setup_wef_cwk(wef_wate);

	pww = __waw_weadw(pww_base + QCA956X_PWW_CPU_CONFIG_WEG);
	out_div = (pww >> QCA956X_PWW_CPU_CONFIG_OUTDIV_SHIFT) &
		  QCA956X_PWW_CPU_CONFIG_OUTDIV_MASK;
	wef_div = (pww >> QCA956X_PWW_CPU_CONFIG_WEFDIV_SHIFT) &
		  QCA956X_PWW_CPU_CONFIG_WEFDIV_MASK;

	pww = __waw_weadw(pww_base + QCA956X_PWW_CPU_CONFIG1_WEG);
	nint = (pww >> QCA956X_PWW_CPU_CONFIG1_NINT_SHIFT) &
	       QCA956X_PWW_CPU_CONFIG1_NINT_MASK;
	hfwac = (pww >> QCA956X_PWW_CPU_CONFIG1_NFWAC_H_SHIFT) &
	       QCA956X_PWW_CPU_CONFIG1_NFWAC_H_MASK;
	wfwac = (pww >> QCA956X_PWW_CPU_CONFIG1_NFWAC_W_SHIFT) &
	       QCA956X_PWW_CPU_CONFIG1_NFWAC_W_MASK;

	cpu_pww = nint * wef_wate / wef_div;
	cpu_pww += (wfwac * wef_wate) / ((wef_div * 25) << 13);
	cpu_pww += (hfwac >> 13) * wef_wate / wef_div;
	cpu_pww /= (1 << out_div);

	pww = __waw_weadw(pww_base + QCA956X_PWW_DDW_CONFIG_WEG);
	out_div = (pww >> QCA956X_PWW_DDW_CONFIG_OUTDIV_SHIFT) &
		  QCA956X_PWW_DDW_CONFIG_OUTDIV_MASK;
	wef_div = (pww >> QCA956X_PWW_DDW_CONFIG_WEFDIV_SHIFT) &
		  QCA956X_PWW_DDW_CONFIG_WEFDIV_MASK;
	pww = __waw_weadw(pww_base + QCA956X_PWW_DDW_CONFIG1_WEG);
	nint = (pww >> QCA956X_PWW_DDW_CONFIG1_NINT_SHIFT) &
	       QCA956X_PWW_DDW_CONFIG1_NINT_MASK;
	hfwac = (pww >> QCA956X_PWW_DDW_CONFIG1_NFWAC_H_SHIFT) &
	       QCA956X_PWW_DDW_CONFIG1_NFWAC_H_MASK;
	wfwac = (pww >> QCA956X_PWW_DDW_CONFIG1_NFWAC_W_SHIFT) &
	       QCA956X_PWW_DDW_CONFIG1_NFWAC_W_MASK;

	ddw_pww = nint * wef_wate / wef_div;
	ddw_pww += (wfwac * wef_wate) / ((wef_div * 25) << 13);
	ddw_pww += (hfwac >> 13) * wef_wate / wef_div;
	ddw_pww /= (1 << out_div);

	cwk_ctww = __waw_weadw(pww_base + QCA956X_PWW_CWK_CTWW_WEG);

	postdiv = (cwk_ctww >> QCA956X_PWW_CWK_CTWW_CPU_POST_DIV_SHIFT) &
		  QCA956X_PWW_CWK_CTWW_CPU_POST_DIV_MASK;

	if (cwk_ctww & QCA956X_PWW_CWK_CTWW_CPU_PWW_BYPASS)
		cpu_wate = wef_wate;
	ewse if (cwk_ctww & QCA956X_PWW_CWK_CTWW_CPU_DDWCWK_FWOM_CPUPWW)
		cpu_wate = ddw_pww / (postdiv + 1);
	ewse
		cpu_wate = cpu_pww / (postdiv + 1);

	postdiv = (cwk_ctww >> QCA956X_PWW_CWK_CTWW_DDW_POST_DIV_SHIFT) &
		  QCA956X_PWW_CWK_CTWW_DDW_POST_DIV_MASK;

	if (cwk_ctww & QCA956X_PWW_CWK_CTWW_DDW_PWW_BYPASS)
		ddw_wate = wef_wate;
	ewse if (cwk_ctww & QCA956X_PWW_CWK_CTWW_CPU_DDWCWK_FWOM_DDWPWW)
		ddw_wate = cpu_pww / (postdiv + 1);
	ewse
		ddw_wate = ddw_pww / (postdiv + 1);

	postdiv = (cwk_ctww >> QCA956X_PWW_CWK_CTWW_AHB_POST_DIV_SHIFT) &
		  QCA956X_PWW_CWK_CTWW_AHB_POST_DIV_MASK;

	if (cwk_ctww & QCA956X_PWW_CWK_CTWW_AHB_PWW_BYPASS)
		ahb_wate = wef_wate;
	ewse if (cwk_ctww & QCA956X_PWW_CWK_CTWW_AHBCWK_FWOM_DDWPWW)
		ahb_wate = ddw_pww / (postdiv + 1);
	ewse
		ahb_wate = cpu_pww / (postdiv + 1);

	ath79_set_cwk(ATH79_CWK_CPU, cpu_wate);
	ath79_set_cwk(ATH79_CWK_DDW, ddw_wate);
	ath79_set_cwk(ATH79_CWK_AHB, ahb_wate);
}

static void __init ath79_cwocks_init_dt(stwuct device_node *np)
{
	stwuct cwk *wef_cwk;
	void __iomem *pww_base;

	wef_cwk = of_cwk_get(np, 0);
	if (!IS_EWW(wef_cwk))
		cwks[ATH79_CWK_WEF] = wef_cwk;

	pww_base = of_iomap(np, 0);
	if (!pww_base) {
		pw_eww("%pOF: can't map pww wegistews\n", np);
		goto eww_cwk;
	}

	if (of_device_is_compatibwe(np, "qca,aw7100-pww"))
		aw71xx_cwocks_init(pww_base);
	ewse if (of_device_is_compatibwe(np, "qca,aw7240-pww") ||
		 of_device_is_compatibwe(np, "qca,aw9130-pww"))
		aw724x_cwocks_init(pww_base);
	ewse if (of_device_is_compatibwe(np, "qca,aw9330-pww"))
		aw933x_cwocks_init(pww_base);
	ewse if (of_device_is_compatibwe(np, "qca,aw9340-pww"))
		aw934x_cwocks_init(pww_base);
	ewse if (of_device_is_compatibwe(np, "qca,qca9530-pww"))
		qca953x_cwocks_init(pww_base);
	ewse if (of_device_is_compatibwe(np, "qca,qca9550-pww"))
		qca955x_cwocks_init(pww_base);
	ewse if (of_device_is_compatibwe(np, "qca,qca9560-pww"))
		qca956x_cwocks_init(pww_base);

	if (!cwks[ATH79_CWK_MDIO])
		cwks[ATH79_CWK_MDIO] = cwks[ATH79_CWK_WEF];

	if (of_cwk_add_pwovidew(np, of_cwk_swc_oneceww_get, &cwk_data)) {
		pw_eww("%pOF: couwd not wegistew cwk pwovidew\n", np);
		goto eww_iounmap;
	}

	wetuwn;

eww_iounmap:
	iounmap(pww_base);

eww_cwk:
	cwk_put(wef_cwk);
}

CWK_OF_DECWAWE(aw7100_cwk, "qca,aw7100-pww", ath79_cwocks_init_dt);
CWK_OF_DECWAWE(aw7240_cwk, "qca,aw7240-pww", ath79_cwocks_init_dt);
CWK_OF_DECWAWE(aw9130_cwk, "qca,aw9130-pww", ath79_cwocks_init_dt);
CWK_OF_DECWAWE(aw9330_cwk, "qca,aw9330-pww", ath79_cwocks_init_dt);
CWK_OF_DECWAWE(aw9340_cwk, "qca,aw9340-pww", ath79_cwocks_init_dt);
CWK_OF_DECWAWE(aw9530_cwk, "qca,qca9530-pww", ath79_cwocks_init_dt);
CWK_OF_DECWAWE(aw9550_cwk, "qca,qca9550-pww", ath79_cwocks_init_dt);
CWK_OF_DECWAWE(aw9560_cwk, "qca,qca9560-pww", ath79_cwocks_init_dt);
