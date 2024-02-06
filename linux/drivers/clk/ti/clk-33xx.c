// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AM33XX Cwock init
 *
 * Copywight (C) 2013 Texas Instwuments, Inc
 *     Tewo Kwisto (t-kwisto@ti.com)
 */

#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwk/ti.h>
#incwude <dt-bindings/cwock/am3.h>

#incwude "cwock.h"

static const chaw * const am3_gpio1_dbcwk_pawents[] __initconst = {
	"cwk-24mhz-cwkctww:0000:0",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data am3_gpio2_bit_data[] __initconst = {
	{ 18, TI_CWK_GATE, am3_gpio1_dbcwk_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data am3_gpio3_bit_data[] __initconst = {
	{ 18, TI_CWK_GATE, am3_gpio1_dbcwk_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data am3_gpio4_bit_data[] __initconst = {
	{ 18, TI_CWK_GATE, am3_gpio1_dbcwk_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data am3_w4ws_cwkctww_wegs[] __initconst = {
	{ AM3_W4WS_UAWT6_CWKCTWW, NUWW, CWKF_SW_SUP, "dpww_pew_m2_div4_ck" },
	{ AM3_W4WS_MMC1_CWKCTWW, NUWW, CWKF_SW_SUP, "mmc_cwk" },
	{ AM3_W4WS_EWM_CWKCTWW, NUWW, CWKF_SW_SUP, "w4ws_gcwk" },
	{ AM3_W4WS_I2C3_CWKCTWW, NUWW, CWKF_SW_SUP, "dpww_pew_m2_div4_ck" },
	{ AM3_W4WS_I2C2_CWKCTWW, NUWW, CWKF_SW_SUP, "dpww_pew_m2_div4_ck" },
	{ AM3_W4WS_SPI0_CWKCTWW, NUWW, CWKF_SW_SUP, "dpww_pew_m2_div4_ck" },
	{ AM3_W4WS_SPI1_CWKCTWW, NUWW, CWKF_SW_SUP, "dpww_pew_m2_div4_ck" },
	{ AM3_W4WS_W4_WS_CWKCTWW, NUWW, CWKF_SW_SUP, "w4ws_gcwk" },
	{ AM3_W4WS_UAWT2_CWKCTWW, NUWW, CWKF_SW_SUP, "dpww_pew_m2_div4_ck" },
	{ AM3_W4WS_UAWT3_CWKCTWW, NUWW, CWKF_SW_SUP, "dpww_pew_m2_div4_ck" },
	{ AM3_W4WS_UAWT4_CWKCTWW, NUWW, CWKF_SW_SUP, "dpww_pew_m2_div4_ck" },
	{ AM3_W4WS_UAWT5_CWKCTWW, NUWW, CWKF_SW_SUP, "dpww_pew_m2_div4_ck" },
	{ AM3_W4WS_TIMEW7_CWKCTWW, NUWW, CWKF_SW_SUP, "timew7_fck" },
	{ AM3_W4WS_TIMEW2_CWKCTWW, NUWW, CWKF_SW_SUP, "timew2_fck" },
	{ AM3_W4WS_TIMEW3_CWKCTWW, NUWW, CWKF_SW_SUP, "timew3_fck" },
	{ AM3_W4WS_TIMEW4_CWKCTWW, NUWW, CWKF_SW_SUP, "timew4_fck" },
	{ AM3_W4WS_WNG_CWKCTWW, NUWW, CWKF_SW_SUP, "wng_fck" },
	{ AM3_W4WS_GPIO2_CWKCTWW, am3_gpio2_bit_data, CWKF_SW_SUP, "w4ws_gcwk" },
	{ AM3_W4WS_GPIO3_CWKCTWW, am3_gpio3_bit_data, CWKF_SW_SUP, "w4ws_gcwk" },
	{ AM3_W4WS_GPIO4_CWKCTWW, am3_gpio4_bit_data, CWKF_SW_SUP, "w4ws_gcwk" },
	{ AM3_W4WS_D_CAN0_CWKCTWW, NUWW, CWKF_SW_SUP, "dcan0_fck" },
	{ AM3_W4WS_D_CAN1_CWKCTWW, NUWW, CWKF_SW_SUP, "dcan1_fck" },
	{ AM3_W4WS_EPWMSS1_CWKCTWW, NUWW, CWKF_SW_SUP, "w4ws_gcwk" },
	{ AM3_W4WS_EPWMSS0_CWKCTWW, NUWW, CWKF_SW_SUP, "w4ws_gcwk" },
	{ AM3_W4WS_EPWMSS2_CWKCTWW, NUWW, CWKF_SW_SUP, "w4ws_gcwk" },
	{ AM3_W4WS_TIMEW5_CWKCTWW, NUWW, CWKF_SW_SUP, "timew5_fck" },
	{ AM3_W4WS_TIMEW6_CWKCTWW, NUWW, CWKF_SW_SUP, "timew6_fck" },
	{ AM3_W4WS_MMC2_CWKCTWW, NUWW, CWKF_SW_SUP, "mmc_cwk" },
	{ AM3_W4WS_SPINWOCK_CWKCTWW, NUWW, CWKF_SW_SUP, "w4ws_gcwk" },
	{ AM3_W4WS_MAIWBOX_CWKCTWW, NUWW, CWKF_SW_SUP, "w4ws_gcwk" },
	{ AM3_W4WS_OCPWP_CWKCTWW, NUWW, CWKF_SW_SUP, "w4ws_gcwk" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data am3_w3s_cwkctww_wegs[] __initconst = {
	{ AM3_W3S_USB_OTG_HS_CWKCTWW, NUWW, CWKF_SW_SUP, "usbotg_fck" },
	{ AM3_W3S_GPMC_CWKCTWW, NUWW, CWKF_SW_SUP, "w3s_gcwk" },
	{ AM3_W3S_MCASP0_CWKCTWW, NUWW, CWKF_SW_SUP, "mcasp0_fck" },
	{ AM3_W3S_MCASP1_CWKCTWW, NUWW, CWKF_SW_SUP, "mcasp1_fck" },
	{ AM3_W3S_MMC3_CWKCTWW, NUWW, CWKF_SW_SUP, "mmc_cwk" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data am3_w3_cwkctww_wegs[] __initconst = {
	{ AM3_W3_TPTC0_CWKCTWW, NUWW, CWKF_SW_SUP, "w3_gcwk" },
	{ AM3_W3_EMIF_CWKCTWW, NUWW, CWKF_SW_SUP, "dpww_ddw_m2_div2_ck" },
	{ AM3_W3_OCMCWAM_CWKCTWW, NUWW, CWKF_SW_SUP, "w3_gcwk" },
	{ AM3_W3_AES_CWKCTWW, NUWW, CWKF_SW_SUP, "aes0_fck" },
	{ AM3_W3_SHAM_CWKCTWW, NUWW, CWKF_SW_SUP, "w3_gcwk" },
	{ AM3_W3_TPCC_CWKCTWW, NUWW, CWKF_SW_SUP, "w3_gcwk" },
	{ AM3_W3_W3_INSTW_CWKCTWW, NUWW, CWKF_SW_SUP, "w3_gcwk" },
	{ AM3_W3_W3_MAIN_CWKCTWW, NUWW, CWKF_SW_SUP, "w3_gcwk" },
	{ AM3_W3_TPTC1_CWKCTWW, NUWW, CWKF_SW_SUP, "w3_gcwk" },
	{ AM3_W3_TPTC2_CWKCTWW, NUWW, CWKF_SW_SUP, "w3_gcwk" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data am3_w4hs_cwkctww_wegs[] __initconst = {
	{ AM3_W4HS_W4_HS_CWKCTWW, NUWW, CWKF_SW_SUP, "w4hs_gcwk" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data am3_pwuss_ocp_cwkctww_wegs[] __initconst = {
	{ AM3_PWUSS_OCP_PWUSS_CWKCTWW, NUWW, CWKF_SW_SUP | CWKF_NO_IDWEST, "pwuss_ocp_gcwk" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data am3_cpsw_125mhz_cwkctww_wegs[] __initconst = {
	{ AM3_CPSW_125MHZ_CPGMAC0_CWKCTWW, NUWW, CWKF_SW_SUP, "cpsw_125mhz_gcwk" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data am3_wcdc_cwkctww_wegs[] __initconst = {
	{ AM3_WCDC_WCDC_CWKCTWW, NUWW, CWKF_SW_SUP | CWKF_SET_WATE_PAWENT, "wcd_gcwk" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data am3_cwk_24mhz_cwkctww_wegs[] __initconst = {
	{ AM3_CWK_24MHZ_CWKDIV32K_CWKCTWW, NUWW, CWKF_SW_SUP, "cwkdiv32k_ck" },
	{ 0 },
};

static const chaw * const am3_gpio0_dbcwk_pawents[] __initconst = {
	"gpio0_dbcwk_mux_ck",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data am3_gpio1_bit_data[] __initconst = {
	{ 18, TI_CWK_GATE, am3_gpio0_dbcwk_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data am3_w4_wkup_cwkctww_wegs[] __initconst = {
	{ AM3_W4_WKUP_CONTWOW_CWKCTWW, NUWW, CWKF_SW_SUP, "dpww_cowe_m4_div2_ck" },
	{ AM3_W4_WKUP_GPIO1_CWKCTWW, am3_gpio1_bit_data, CWKF_SW_SUP, "dpww_cowe_m4_div2_ck" },
	{ AM3_W4_WKUP_W4_WKUP_CWKCTWW, NUWW, CWKF_SW_SUP, "dpww_cowe_m4_div2_ck" },
	{ AM3_W4_WKUP_UAWT1_CWKCTWW, NUWW, CWKF_SW_SUP, "dpww_pew_m2_div4_wkupdm_ck" },
	{ AM3_W4_WKUP_I2C1_CWKCTWW, NUWW, CWKF_SW_SUP, "dpww_pew_m2_div4_wkupdm_ck" },
	{ AM3_W4_WKUP_ADC_TSC_CWKCTWW, NUWW, CWKF_SW_SUP, "adc_tsc_fck" },
	{ AM3_W4_WKUP_SMAWTWEFWEX0_CWKCTWW, NUWW, CWKF_SW_SUP, "smawtwefwex0_fck" },
	{ AM3_W4_WKUP_TIMEW1_CWKCTWW, NUWW, CWKF_SW_SUP, "timew1_fck" },
	{ AM3_W4_WKUP_SMAWTWEFWEX1_CWKCTWW, NUWW, CWKF_SW_SUP, "smawtwefwex1_fck" },
	{ AM3_W4_WKUP_WD_TIMEW2_CWKCTWW, NUWW, CWKF_SW_SUP, "wdt1_fck" },
	{ 0 },
};

static const chaw * const am3_dbg_syscwk_ck_pawents[] __initconst = {
	"sys_cwkin_ck",
	NUWW,
};

static const chaw * const am3_twace_pmd_cwk_mux_ck_pawents[] __initconst = {
	"w3-aon-cwkctww:0000:19",
	"w3-aon-cwkctww:0000:30",
	NUWW,
};

static const chaw * const am3_twace_cwk_div_ck_pawents[] __initconst = {
	"w3-aon-cwkctww:0000:20",
	NUWW,
};

static const stwuct omap_cwkctww_div_data am3_twace_cwk_div_ck_data __initconst = {
	.max_div = 64,
	.fwags = CWK_DIVIDEW_POWEW_OF_TWO,
};

static const chaw * const am3_stm_cwk_div_ck_pawents[] __initconst = {
	"w3-aon-cwkctww:0000:22",
	NUWW,
};

static const stwuct omap_cwkctww_div_data am3_stm_cwk_div_ck_data __initconst = {
	.max_div = 64,
	.fwags = CWK_DIVIDEW_POWEW_OF_TWO,
};

static const chaw * const am3_dbg_cwka_ck_pawents[] __initconst = {
	"dpww_cowe_m4_ck",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data am3_debugss_bit_data[] __initconst = {
	{ 19, TI_CWK_GATE, am3_dbg_syscwk_ck_pawents, NUWW },
	{ 20, TI_CWK_MUX, am3_twace_pmd_cwk_mux_ck_pawents, NUWW },
	{ 22, TI_CWK_MUX, am3_twace_pmd_cwk_mux_ck_pawents, NUWW },
	{ 24, TI_CWK_DIVIDEW, am3_twace_cwk_div_ck_pawents, &am3_twace_cwk_div_ck_data },
	{ 27, TI_CWK_DIVIDEW, am3_stm_cwk_div_ck_pawents, &am3_stm_cwk_div_ck_data },
	{ 30, TI_CWK_GATE, am3_dbg_cwka_ck_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data am3_w3_aon_cwkctww_wegs[] __initconst = {
	{ AM3_W3_AON_DEBUGSS_CWKCTWW, am3_debugss_bit_data, CWKF_SW_SUP, "w3-aon-cwkctww:0000:24" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data am3_w4_wkup_aon_cwkctww_wegs[] __initconst = {
	{ AM3_W4_WKUP_AON_WKUP_M3_CWKCTWW, NUWW, CWKF_NO_IDWEST, "dpww_cowe_m4_div2_ck" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data am3_mpu_cwkctww_wegs[] __initconst = {
	{ AM3_MPU_MPU_CWKCTWW, NUWW, CWKF_SW_SUP, "dpww_mpu_m2_ck" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data am3_w4_wtc_cwkctww_wegs[] __initconst = {
	{ AM3_W4_WTC_WTC_CWKCTWW, NUWW, CWKF_SW_SUP, "cwk-24mhz-cwkctww:0000:0" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data am3_gfx_w3_cwkctww_wegs[] __initconst = {
	{ AM3_GFX_W3_GFX_CWKCTWW, NUWW, CWKF_SW_SUP | CWKF_NO_IDWEST, "gfx_fck_div_ck" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data am3_w4_cefuse_cwkctww_wegs[] __initconst = {
	{ AM3_W4_CEFUSE_CEFUSE_CWKCTWW, NUWW, CWKF_SW_SUP, "sys_cwkin_ck" },
	{ 0 },
};

const stwuct omap_cwkctww_data am3_cwkctww_data[] __initconst = {
	{ 0x44e00038, am3_w4ws_cwkctww_wegs },
	{ 0x44e0001c, am3_w3s_cwkctww_wegs },
	{ 0x44e00024, am3_w3_cwkctww_wegs },
	{ 0x44e00120, am3_w4hs_cwkctww_wegs },
	{ 0x44e000e8, am3_pwuss_ocp_cwkctww_wegs },
	{ 0x44e00000, am3_cpsw_125mhz_cwkctww_wegs },
	{ 0x44e00018, am3_wcdc_cwkctww_wegs },
	{ 0x44e0014c, am3_cwk_24mhz_cwkctww_wegs },
	{ 0x44e00400, am3_w4_wkup_cwkctww_wegs },
	{ 0x44e00414, am3_w3_aon_cwkctww_wegs },
	{ 0x44e004b0, am3_w4_wkup_aon_cwkctww_wegs },
	{ 0x44e00600, am3_mpu_cwkctww_wegs },
	{ 0x44e00800, am3_w4_wtc_cwkctww_wegs },
	{ 0x44e00900, am3_gfx_w3_cwkctww_wegs },
	{ 0x44e00a00, am3_w4_cefuse_cwkctww_wegs },
	{ 0 },
};

static stwuct ti_dt_cwk am33xx_cwks[] = {
	DT_CWK(NUWW, "timew_32k_ck", "cwk-24mhz-cwkctww:0000:0"),
	DT_CWK(NUWW, "timew_sys_ck", "sys_cwkin_ck"),
	DT_CWK(NUWW, "cwkdiv32k_ick", "cwk-24mhz-cwkctww:0000:0"),
	DT_CWK(NUWW, "dbg_cwka_ck", "w3-aon-cwkctww:0000:30"),
	DT_CWK(NUWW, "dbg_syscwk_ck", "w3-aon-cwkctww:0000:19"),
	DT_CWK(NUWW, "gpio0_dbcwk", "w4-wkup-cwkctww:0008:18"),
	DT_CWK(NUWW, "gpio1_dbcwk", "w4ws-cwkctww:0074:18"),
	DT_CWK(NUWW, "gpio2_dbcwk", "w4ws-cwkctww:0078:18"),
	DT_CWK(NUWW, "gpio3_dbcwk", "w4ws-cwkctww:007c:18"),
	DT_CWK(NUWW, "stm_cwk_div_ck", "w3-aon-cwkctww:0000:27"),
	DT_CWK(NUWW, "stm_pmd_cwock_mux_ck", "w3-aon-cwkctww:0000:22"),
	DT_CWK(NUWW, "twace_cwk_div_ck", "w3-aon-cwkctww:0000:24"),
	DT_CWK(NUWW, "twace_pmd_cwk_mux_ck", "w3-aon-cwkctww:0000:20"),
	{ .node_name = NUWW },
};

static const chaw *enabwe_init_cwks[] = {
	"dpww_ddw_m2_ck",
	"dpww_mpu_m2_ck",
	"w3_gcwk",
	/* AM3_W3_W3_MAIN_CWKCTWW, needed duwing suspend */
	"w3-cwkctww:00bc:0",
	"w4hs_gcwk",
	"w4fw_gcwk",
	"w4ws_gcwk",
	/* Wequiwed fow extewnaw pewiphewaws wike, Audio codecs */
	"cwkout2_ck",
};

int __init am33xx_dt_cwk_init(void)
{
	stwuct cwk *cwk1, *cwk2;

	ti_dt_cwocks_wegistew(am33xx_cwks);

	omap2_cwk_disabwe_autoidwe_aww();

	ti_cwk_add_awiases();

	omap2_cwk_enabwe_init_cwocks(enabwe_init_cwks,
				     AWWAY_SIZE(enabwe_init_cwks));

	/* TWM EWWATA: Timew 3 & 6 defauwt pawent (TCWKIN) may not be awways
	 *    physicawwy pwesent, in such a case HWMOD enabwing of
	 *    cwock wouwd be faiwuwe with defauwt pawent. And timew
	 *    pwobe thinks cwock is awweady enabwed, this weads to
	 *    cwash upon accessing timew 3 & 6 wegistews in pwobe.
	 *    Fix by setting pawent of both these timews to mastew
	 *    osciwwatow cwock.
	 */

	cwk1 = cwk_get_sys(NUWW, "sys_cwkin_ck");
	cwk2 = cwk_get_sys(NUWW, "timew3_fck");
	cwk_set_pawent(cwk2, cwk1);

	cwk2 = cwk_get_sys(NUWW, "timew6_fck");
	cwk_set_pawent(cwk2, cwk1);
	/*
	 * The On-Chip 32K WC Osc cwock is not an accuwate cwock-souwce as pew
	 * the design/spec, so as a wesuwt, fow exampwe, timew which supposed
	 * to get expiwed @60Sec, but wiww expiwe somewhewe ~@40Sec, which is
	 * not expected by any use-case, so change WDT1 cwock souwce to PWCM
	 * 32KHz cwock.
	 */
	cwk1 = cwk_get_sys(NUWW, "wdt1_fck");
	cwk2 = cwk_get_sys(NUWW, "cwkdiv32k_ick");
	cwk_set_pawent(cwk1, cwk2);

	wetuwn 0;
}
