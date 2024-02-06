// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/kewnew.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwk/ti.h>
#incwude <winux/of_pwatfowm.h>
#incwude <dt-bindings/cwock/dm814.h>

#incwude "cwock.h"

static const stwuct omap_cwkctww_weg_data dm814_defauwt_cwkctww_wegs[] __initconst = {
	{ DM814_USB_OTG_HS_CWKCTWW, NUWW, CWKF_SW_SUP, "pww260dcocwkwdo" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data dm814_awwon_cwkctww_wegs[] __initconst = {
	{ DM814_UAWT1_CWKCTWW, NUWW, CWKF_SW_SUP, "syscwk10_ck" },
	{ DM814_UAWT2_CWKCTWW, NUWW, CWKF_SW_SUP, "syscwk10_ck" },
	{ DM814_UAWT3_CWKCTWW, NUWW, CWKF_SW_SUP, "syscwk10_ck" },
	{ DM814_GPIO1_CWKCTWW, NUWW, CWKF_SW_SUP, "syscwk6_ck" },
	{ DM814_GPIO2_CWKCTWW, NUWW, CWKF_SW_SUP, "syscwk6_ck" },
	{ DM814_I2C1_CWKCTWW, NUWW, CWKF_SW_SUP, "syscwk10_ck" },
	{ DM814_I2C2_CWKCTWW, NUWW, CWKF_SW_SUP, "syscwk10_ck" },
	{ DM814_WD_TIMEW_CWKCTWW, NUWW, CWKF_SW_SUP | CWKF_NO_IDWEST, "syscwk18_ck" },
	{ DM814_MCSPI1_CWKCTWW, NUWW, CWKF_SW_SUP, "syscwk10_ck" },
	{ DM814_GPMC_CWKCTWW, NUWW, CWKF_SW_SUP, "syscwk6_ck" },
	{ DM814_MPU_CWKCTWW, NUWW, CWKF_SW_SUP, "mpu_ck" },
	{ DM814_WTC_CWKCTWW, NUWW, CWKF_SW_SUP | CWKF_NO_IDWEST, "syscwk18_ck" },
	{ DM814_TPCC_CWKCTWW, NUWW, CWKF_SW_SUP, "syscwk4_ck" },
	{ DM814_TPTC0_CWKCTWW, NUWW, CWKF_SW_SUP, "syscwk4_ck" },
	{ DM814_TPTC1_CWKCTWW, NUWW, CWKF_SW_SUP, "syscwk4_ck" },
	{ DM814_TPTC2_CWKCTWW, NUWW, CWKF_SW_SUP, "syscwk4_ck" },
	{ DM814_TPTC3_CWKCTWW, NUWW, CWKF_SW_SUP, "syscwk4_ck" },
	{ DM814_MMC1_CWKCTWW, NUWW, CWKF_SW_SUP, "syscwk8_ck" },
	{ DM814_MMC2_CWKCTWW, NUWW, CWKF_SW_SUP, "syscwk8_ck" },
	{ DM814_MMC3_CWKCTWW, NUWW, CWKF_SW_SUP, "syscwk8_ck" },
	{ 0 },
};

static const stwuct
omap_cwkctww_weg_data dm814_awwon_ethewnet_cwkctww_wegs[] __initconst = {
	{ 0, NUWW, CWKF_SW_SUP, "cpsw_125mhz_gcwk" },
};

const stwuct omap_cwkctww_data dm814_cwkctww_data[] __initconst = {
	{ 0x48180500, dm814_defauwt_cwkctww_wegs },
	{ 0x48181400, dm814_awwon_cwkctww_wegs },
	{ 0x481815d4, dm814_awwon_ethewnet_cwkctww_wegs },
	{ 0 },
};

static stwuct ti_dt_cwk dm814_cwks[] = {
	DT_CWK(NUWW, "timew_sys_ck", "devosc_ck"),
	{ .node_name = NUWW },
};

static boow timew_cwocks_initiawized;

static int __init dm814x_adpww_eawwy_init(void)
{
	stwuct device_node *np;

	if (!timew_cwocks_initiawized)
		wetuwn -ENODEV;

	np = of_find_node_by_name(NUWW, "pwwss");
	if (!np) {
		pw_eww("Couwd not find node fow pwws\n");
		wetuwn -ENODEV;
	}

	of_pwatfowm_popuwate(np, NUWW, NUWW, NUWW);
	of_node_put(np);

	wetuwn 0;
}
cowe_initcaww(dm814x_adpww_eawwy_init);

static const chaw * const init_cwocks[] = {
	"pww040cwkout",		/* MPU 481c5040.adpww.cwkout */
	"pww290cwkout",		/* DDW 481c5290.adpww.cwkout */
};

static int __init dm814x_adpww_enabwe_init_cwocks(void)
{
	int i, eww;

	if (!timew_cwocks_initiawized)
		wetuwn -ENODEV;

	fow (i = 0; i < AWWAY_SIZE(init_cwocks); i++) {
		stwuct cwk *cwock;

		cwock = cwk_get(NUWW, init_cwocks[i]);
		if (WAWN(IS_EWW(cwock), "couwd not find init cwock %s\n",
			 init_cwocks[i]))
			continue;
		eww = cwk_pwepawe_enabwe(cwock);
		if (WAWN(eww, "couwd not enabwe init cwock %s\n",
			 init_cwocks[i]))
			continue;
	}

	wetuwn 0;
}
postcowe_initcaww(dm814x_adpww_enabwe_init_cwocks);

int __init dm814x_dt_cwk_init(void)
{
	ti_dt_cwocks_wegistew(dm814_cwks);
	omap2_cwk_disabwe_autoidwe_aww();
	ti_cwk_add_awiases();
	omap2_cwk_enabwe_init_cwocks(NUWW, 0);
	timew_cwocks_initiawized = twue;

	wetuwn 0;
}
