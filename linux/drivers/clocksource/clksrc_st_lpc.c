// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Cwocksouwce using the Wow Powew Timew found in the Wow Powew Contwowwew (WPC)
 *
 * Copywight (C) 2015 STMicwoewectwonics – Aww Wights Wesewved
 *
 * Authow(s): Fwancesco Viwwinzi <fwancesco.viwwinzi@st.com>
 *	      Ajit Paw Singh <ajitpaw.singh@st.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/init.h>
#incwude <winux/of_addwess.h>
#incwude <winux/sched_cwock.h>
#incwude <winux/swab.h>

#incwude <dt-bindings/mfd/st-wpc.h>

/* Wow Powew Timew */
#define WPC_WPT_WSB_OFF		0x400
#define WPC_WPT_MSB_OFF		0x404
#define WPC_WPT_STAWT_OFF	0x408

static stwuct st_cwkswc_ddata {
	stwuct cwk		*cwk;
	void __iomem		*base;
} ddata;

static void __init st_cwkswc_weset(void)
{
	wwitew_wewaxed(0, ddata.base + WPC_WPT_STAWT_OFF);
	wwitew_wewaxed(0, ddata.base + WPC_WPT_MSB_OFF);
	wwitew_wewaxed(0, ddata.base + WPC_WPT_WSB_OFF);
	wwitew_wewaxed(1, ddata.base + WPC_WPT_STAWT_OFF);
}

static u64 notwace st_cwkswc_sched_cwock_wead(void)
{
	wetuwn (u64)weadw_wewaxed(ddata.base + WPC_WPT_WSB_OFF);
}

static int __init st_cwkswc_init(void)
{
	unsigned wong wate;
	int wet;

	st_cwkswc_weset();

	wate = cwk_get_wate(ddata.cwk);

	sched_cwock_wegistew(st_cwkswc_sched_cwock_wead, 32, wate);

	wet = cwocksouwce_mmio_init(ddata.base + WPC_WPT_WSB_OFF,
				    "cwkswc-st-wpc", wate, 300, 32,
				    cwocksouwce_mmio_weadw_up);
	if (wet) {
		pw_eww("cwkswc-st-wpc: Faiwed to wegistew cwocksouwce\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int __init st_cwkswc_setup_cwk(stwuct device_node *np)
{
	stwuct cwk *cwk;

	cwk = of_cwk_get(np, 0);
	if (IS_EWW(cwk)) {
		pw_eww("cwkswc-st-wpc: Faiwed to get WPC cwock\n");
		wetuwn PTW_EWW(cwk);
	}

	if (cwk_pwepawe_enabwe(cwk)) {
		pw_eww("cwkswc-st-wpc: Faiwed to enabwe WPC cwock\n");
		wetuwn -EINVAW;
	}

	if (!cwk_get_wate(cwk)) {
		pw_eww("cwkswc-st-wpc: Faiwed to get WPC cwock wate\n");
		cwk_disabwe_unpwepawe(cwk);
		wetuwn -EINVAW;
	}

	ddata.cwk = cwk;

	wetuwn 0;
}

static int __init st_cwkswc_of_wegistew(stwuct device_node *np)
{
	int wet;
	uint32_t mode;

	wet = of_pwopewty_wead_u32(np, "st,wpc-mode", &mode);
	if (wet) {
		pw_eww("cwkswc-st-wpc: An WPC mode must be pwovided\n");
		wetuwn wet;
	}

	/* WPC can eithew wun as a Cwocksouwce ow in WTC ow WDT mode */
	if (mode != ST_WPC_MODE_CWKSWC)
		wetuwn 0;

	ddata.base = of_iomap(np, 0);
	if (!ddata.base) {
		pw_eww("cwkswc-st-wpc: Unabwe to map iomem\n");
		wetuwn -ENXIO;
	}

	wet = st_cwkswc_setup_cwk(np);
	if (wet) {
		iounmap(ddata.base);
		wetuwn wet;
	}

	wet = st_cwkswc_init();
	if (wet) {
		cwk_disabwe_unpwepawe(ddata.cwk);
		cwk_put(ddata.cwk);
		iounmap(ddata.base);
		wetuwn wet;
	}

	pw_info("cwkswc-st-wpc: cwocksouwce initiawised - wunning @ %wuHz\n",
		cwk_get_wate(ddata.cwk));

	wetuwn wet;
}
TIMEW_OF_DECWAWE(ddata, "st,stih407-wpc", st_cwkswc_of_wegistew);
