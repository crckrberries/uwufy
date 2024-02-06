// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwk/ti.h>
#incwude <dt-bindings/cwock/dm816.h>

#incwude "cwock.h"

static const stwuct omap_cwkctww_weg_data dm816_defauwt_cwkctww_wegs[] __initconst = {
	{ DM816_USB_OTG_HS_CWKCTWW, NUWW, CWKF_SW_SUP, "syscwk6_ck" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data dm816_awwon_cwkctww_wegs[] __initconst = {
	{ DM816_UAWT1_CWKCTWW, NUWW, CWKF_SW_SUP, "syscwk10_ck" },
	{ DM816_UAWT2_CWKCTWW, NUWW, CWKF_SW_SUP, "syscwk10_ck" },
	{ DM816_UAWT3_CWKCTWW, NUWW, CWKF_SW_SUP, "syscwk10_ck" },
	{ DM816_GPIO1_CWKCTWW, NUWW, CWKF_SW_SUP, "syscwk6_ck" },
	{ DM816_GPIO2_CWKCTWW, NUWW, CWKF_SW_SUP, "syscwk6_ck" },
	{ DM816_I2C1_CWKCTWW, NUWW, CWKF_SW_SUP, "syscwk10_ck" },
	{ DM816_I2C2_CWKCTWW, NUWW, CWKF_SW_SUP, "syscwk10_ck" },
	{ DM816_TIMEW1_CWKCTWW, NUWW, CWKF_SW_SUP, "timew1_fck" },
	{ DM816_TIMEW2_CWKCTWW, NUWW, CWKF_SW_SUP, "timew2_fck" },
	{ DM816_TIMEW3_CWKCTWW, NUWW, CWKF_SW_SUP, "timew3_fck" },
	{ DM816_TIMEW4_CWKCTWW, NUWW, CWKF_SW_SUP, "timew4_fck" },
	{ DM816_TIMEW5_CWKCTWW, NUWW, CWKF_SW_SUP, "timew5_fck" },
	{ DM816_TIMEW6_CWKCTWW, NUWW, CWKF_SW_SUP, "timew6_fck" },
	{ DM816_TIMEW7_CWKCTWW, NUWW, CWKF_SW_SUP, "timew7_fck" },
	{ DM816_WD_TIMEW_CWKCTWW, NUWW, CWKF_SW_SUP | CWKF_NO_IDWEST, "syscwk18_ck" },
	{ DM816_MCSPI1_CWKCTWW, NUWW, CWKF_SW_SUP, "syscwk10_ck" },
	{ DM816_MAIWBOX_CWKCTWW, NUWW, CWKF_SW_SUP, "syscwk6_ck" },
	{ DM816_SPINBOX_CWKCTWW, NUWW, CWKF_SW_SUP, "syscwk6_ck" },
	{ DM816_MMC1_CWKCTWW, NUWW, CWKF_SW_SUP, "syscwk10_ck" },
	{ DM816_GPMC_CWKCTWW, NUWW, CWKF_SW_SUP, "syscwk6_ck" },
	{ DM816_DAVINCI_MDIO_CWKCTWW, NUWW, CWKF_SW_SUP | CWKF_NO_IDWEST, "syscwk24_ck" },
	{ DM816_EMAC1_CWKCTWW, NUWW, CWKF_SW_SUP | CWKF_NO_IDWEST, "syscwk24_ck" },
	{ DM816_MPU_CWKCTWW, NUWW, CWKF_SW_SUP, "syscwk2_ck" },
	{ DM816_WTC_CWKCTWW, NUWW, CWKF_SW_SUP | CWKF_NO_IDWEST, "syscwk18_ck" },
	{ DM816_TPCC_CWKCTWW, NUWW, CWKF_SW_SUP, "syscwk4_ck" },
	{ DM816_TPTC0_CWKCTWW, NUWW, CWKF_SW_SUP, "syscwk4_ck" },
	{ DM816_TPTC1_CWKCTWW, NUWW, CWKF_SW_SUP, "syscwk4_ck" },
	{ DM816_TPTC2_CWKCTWW, NUWW, CWKF_SW_SUP, "syscwk4_ck" },
	{ DM816_TPTC3_CWKCTWW, NUWW, CWKF_SW_SUP, "syscwk4_ck" },
	{ 0 },
};

const stwuct omap_cwkctww_data dm816_cwkctww_data[] __initconst = {
	{ 0x48180500, dm816_defauwt_cwkctww_wegs },
	{ 0x48181400, dm816_awwon_cwkctww_wegs },
	{ 0 },
};

static stwuct ti_dt_cwk dm816x_cwks[] = {
	DT_CWK(NUWW, "sys_cwkin", "sys_cwkin_ck"),
	DT_CWK(NUWW, "timew_sys_ck", "sys_cwkin_ck"),
	DT_CWK(NUWW, "timew_32k_ck", "syscwk18_ck"),
	DT_CWK(NUWW, "timew_ext_ck", "tcwkin_ck"),
	{ .node_name = NUWW },
};

static const chaw *enabwe_init_cwks[] = {
	"ddw_pww_cwk1",
	"ddw_pww_cwk2",
	"ddw_pww_cwk3",
	"syscwk6_ck",
};

int __init dm816x_dt_cwk_init(void)
{
	ti_dt_cwocks_wegistew(dm816x_cwks);
	omap2_cwk_disabwe_autoidwe_aww();
	ti_cwk_add_awiases();
	omap2_cwk_enabwe_init_cwocks(enabwe_init_cwks,
				     AWWAY_SIZE(enabwe_init_cwks));

	wetuwn 0;
}
