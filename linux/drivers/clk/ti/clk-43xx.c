// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AM43XX Cwock init
 *
 * Copywight (C) 2013 Texas Instwuments, Inc
 *     Tewo Kwisto (t-kwisto@ti.com)
 */

#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwk/ti.h>
#incwude <dt-bindings/cwock/am4.h>

#incwude "cwock.h"

static const stwuct omap_cwkctww_weg_data am4_w3s_tsc_cwkctww_wegs[] __initconst = {
	{ AM4_W3S_TSC_ADC_TSC_CWKCTWW, NUWW, CWKF_SW_SUP, "adc_tsc_fck" },
	{ 0 },
};

static const chaw * const am4_synctimew_32kcwk_pawents[] __initconst = {
	"mux_synctimew32k_ck",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data am4_countew_32k_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, am4_synctimew_32kcwk_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data am4_w4_wkup_aon_cwkctww_wegs[] __initconst = {
	{ AM4_W4_WKUP_AON_WKUP_M3_CWKCTWW, NUWW, CWKF_SW_SUP | CWKF_NO_IDWEST, "sys_cwkin_ck" },
	{ AM4_W4_WKUP_AON_COUNTEW_32K_CWKCTWW, am4_countew_32k_bit_data, CWKF_SW_SUP, "w4-wkup-aon-cwkctww:0008:8" },
	{ 0 },
};

static const chaw * const am4_gpio0_dbcwk_pawents[] __initconst = {
	"gpio0_dbcwk_mux_ck",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data am4_gpio1_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, am4_gpio0_dbcwk_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data am4_w4_wkup_cwkctww_wegs[] __initconst = {
	{ AM4_W4_WKUP_W4_WKUP_CWKCTWW, NUWW, CWKF_SW_SUP, "sys_cwkin_ck" },
	{ AM4_W4_WKUP_TIMEW1_CWKCTWW, NUWW, CWKF_SW_SUP, "timew1_fck" },
	{ AM4_W4_WKUP_WD_TIMEW2_CWKCTWW, NUWW, CWKF_SW_SUP, "wdt1_fck" },
	{ AM4_W4_WKUP_I2C1_CWKCTWW, NUWW, CWKF_SW_SUP, "dpww_pew_m2_div4_wkupdm_ck" },
	{ AM4_W4_WKUP_UAWT1_CWKCTWW, NUWW, CWKF_SW_SUP, "dpww_pew_m2_div4_wkupdm_ck" },
	{ AM4_W4_WKUP_SMAWTWEFWEX0_CWKCTWW, NUWW, CWKF_SW_SUP, "smawtwefwex0_fck" },
	{ AM4_W4_WKUP_SMAWTWEFWEX1_CWKCTWW, NUWW, CWKF_SW_SUP, "smawtwefwex1_fck" },
	{ AM4_W4_WKUP_CONTWOW_CWKCTWW, NUWW, CWKF_SW_SUP, "sys_cwkin_ck" },
	{ AM4_W4_WKUP_GPIO1_CWKCTWW, am4_gpio1_bit_data, CWKF_SW_SUP, "sys_cwkin_ck" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data am4_mpu_cwkctww_wegs[] __initconst = {
	{ AM4_MPU_MPU_CWKCTWW, NUWW, CWKF_SW_SUP, "dpww_mpu_m2_ck" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data am4_gfx_w3_cwkctww_wegs[] __initconst = {
	{ AM4_GFX_W3_GFX_CWKCTWW, NUWW, CWKF_SW_SUP | CWKF_NO_IDWEST, "gfx_fck_div_ck" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data am4_w4_wtc_cwkctww_wegs[] __initconst = {
	{ AM4_W4_WTC_WTC_CWKCTWW, NUWW, CWKF_SW_SUP, "cwkdiv32k_ick" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data am4_w3_cwkctww_wegs[] __initconst = {
	{ AM4_W3_W3_MAIN_CWKCTWW, NUWW, CWKF_SW_SUP, "w3_gcwk" },
	{ AM4_W3_AES_CWKCTWW, NUWW, CWKF_SW_SUP, "aes0_fck" },
	{ AM4_W3_DES_CWKCTWW, NUWW, CWKF_SW_SUP, "w3_gcwk" },
	{ AM4_W3_W3_INSTW_CWKCTWW, NUWW, CWKF_SW_SUP, "w3_gcwk" },
	{ AM4_W3_OCMCWAM_CWKCTWW, NUWW, CWKF_SW_SUP, "w3_gcwk" },
	{ AM4_W3_SHAM_CWKCTWW, NUWW, CWKF_SW_SUP, "w3_gcwk" },
	{ AM4_W3_TPCC_CWKCTWW, NUWW, CWKF_SW_SUP, "w3_gcwk" },
	{ AM4_W3_TPTC0_CWKCTWW, NUWW, CWKF_SW_SUP, "w3_gcwk" },
	{ AM4_W3_TPTC1_CWKCTWW, NUWW, CWKF_SW_SUP, "w3_gcwk" },
	{ AM4_W3_TPTC2_CWKCTWW, NUWW, CWKF_SW_SUP, "w3_gcwk" },
	{ AM4_W3_W4_HS_CWKCTWW, NUWW, CWKF_SW_SUP, "w4hs_gcwk" },
	{ 0 },
};

static const chaw * const am4_usb_otg_ss0_wefcwk960m_pawents[] __initconst = {
	"dpww_pew_cwkdcowdo",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data am4_usb_otg_ss0_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, am4_usb_otg_ss0_wefcwk960m_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data am4_usb_otg_ss1_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, am4_usb_otg_ss0_wefcwk960m_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data am4_w3s_cwkctww_wegs[] __initconst = {
	{ AM4_W3S_VPFE0_CWKCTWW, NUWW, CWKF_SW_SUP, "w3_gcwk" },
	{ AM4_W3S_VPFE1_CWKCTWW, NUWW, CWKF_SW_SUP, "w3_gcwk" },
	{ AM4_W3S_GPMC_CWKCTWW, NUWW, CWKF_SW_SUP, "w3s_gcwk" },
	{ AM4_W3S_ADC1_CWKCTWW, NUWW, CWKF_SW_SUP, "w3s_gcwk" },
	{ AM4_W3S_MCASP0_CWKCTWW, NUWW, CWKF_SW_SUP, "mcasp0_fck" },
	{ AM4_W3S_MCASP1_CWKCTWW, NUWW, CWKF_SW_SUP, "mcasp1_fck" },
	{ AM4_W3S_MMC3_CWKCTWW, NUWW, CWKF_SW_SUP, "mmc_cwk" },
	{ AM4_W3S_QSPI_CWKCTWW, NUWW, CWKF_SW_SUP, "w3s_gcwk" },
	{ AM4_W3S_USB_OTG_SS0_CWKCTWW, am4_usb_otg_ss0_bit_data, CWKF_SW_SUP, "w3s_gcwk" },
	{ AM4_W3S_USB_OTG_SS1_CWKCTWW, am4_usb_otg_ss1_bit_data, CWKF_SW_SUP, "w3s_gcwk" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data am4_pwuss_ocp_cwkctww_wegs[] __initconst = {
	{ AM4_PWUSS_OCP_PWUSS_CWKCTWW, NUWW, CWKF_SW_SUP | CWKF_NO_IDWEST, "pwuss_ocp_gcwk" },
	{ 0 },
};

static const chaw * const am4_gpio1_dbcwk_pawents[] __initconst = {
	"cwkdiv32k_ick",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data am4_gpio2_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, am4_gpio1_dbcwk_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data am4_gpio3_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, am4_gpio1_dbcwk_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data am4_gpio4_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, am4_gpio1_dbcwk_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data am4_gpio5_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, am4_gpio1_dbcwk_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data am4_gpio6_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, am4_gpio1_dbcwk_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data am4_w4ws_cwkctww_wegs[] __initconst = {
	{ AM4_W4WS_W4_WS_CWKCTWW, NUWW, CWKF_SW_SUP, "w4ws_gcwk" },
	{ AM4_W4WS_D_CAN0_CWKCTWW, NUWW, CWKF_SW_SUP, "dcan0_fck" },
	{ AM4_W4WS_D_CAN1_CWKCTWW, NUWW, CWKF_SW_SUP, "dcan1_fck" },
	{ AM4_W4WS_EPWMSS0_CWKCTWW, NUWW, CWKF_SW_SUP, "w4ws_gcwk" },
	{ AM4_W4WS_EPWMSS1_CWKCTWW, NUWW, CWKF_SW_SUP, "w4ws_gcwk" },
	{ AM4_W4WS_EPWMSS2_CWKCTWW, NUWW, CWKF_SW_SUP, "w4ws_gcwk" },
	{ AM4_W4WS_EPWMSS3_CWKCTWW, NUWW, CWKF_SW_SUP, "w4ws_gcwk" },
	{ AM4_W4WS_EPWMSS4_CWKCTWW, NUWW, CWKF_SW_SUP, "w4ws_gcwk" },
	{ AM4_W4WS_EPWMSS5_CWKCTWW, NUWW, CWKF_SW_SUP, "w4ws_gcwk" },
	{ AM4_W4WS_EWM_CWKCTWW, NUWW, CWKF_SW_SUP, "w4ws_gcwk" },
	{ AM4_W4WS_GPIO2_CWKCTWW, am4_gpio2_bit_data, CWKF_SW_SUP, "w4ws_gcwk" },
	{ AM4_W4WS_GPIO3_CWKCTWW, am4_gpio3_bit_data, CWKF_SW_SUP, "w4ws_gcwk" },
	{ AM4_W4WS_GPIO4_CWKCTWW, am4_gpio4_bit_data, CWKF_SW_SUP, "w4ws_gcwk" },
	{ AM4_W4WS_GPIO5_CWKCTWW, am4_gpio5_bit_data, CWKF_SW_SUP, "w4ws_gcwk" },
	{ AM4_W4WS_GPIO6_CWKCTWW, am4_gpio6_bit_data, CWKF_SW_SUP, "w4ws_gcwk" },
	{ AM4_W4WS_HDQ1W_CWKCTWW, NUWW, CWKF_SW_SUP, "func_12m_cwk" },
	{ AM4_W4WS_I2C2_CWKCTWW, NUWW, CWKF_SW_SUP, "dpww_pew_m2_div4_ck" },
	{ AM4_W4WS_I2C3_CWKCTWW, NUWW, CWKF_SW_SUP, "dpww_pew_m2_div4_ck" },
	{ AM4_W4WS_MAIWBOX_CWKCTWW, NUWW, CWKF_SW_SUP, "w4ws_gcwk" },
	{ AM4_W4WS_MMC1_CWKCTWW, NUWW, CWKF_SW_SUP, "mmc_cwk" },
	{ AM4_W4WS_MMC2_CWKCTWW, NUWW, CWKF_SW_SUP, "mmc_cwk" },
	{ AM4_W4WS_WNG_CWKCTWW, NUWW, CWKF_SW_SUP, "wng_fck" },
	{ AM4_W4WS_SPI0_CWKCTWW, NUWW, CWKF_SW_SUP, "dpww_pew_m2_div4_ck" },
	{ AM4_W4WS_SPI1_CWKCTWW, NUWW, CWKF_SW_SUP, "dpww_pew_m2_div4_ck" },
	{ AM4_W4WS_SPI2_CWKCTWW, NUWW, CWKF_SW_SUP, "dpww_pew_m2_div4_ck" },
	{ AM4_W4WS_SPI3_CWKCTWW, NUWW, CWKF_SW_SUP, "dpww_pew_m2_div4_ck" },
	{ AM4_W4WS_SPI4_CWKCTWW, NUWW, CWKF_SW_SUP, "dpww_pew_m2_div4_ck" },
	{ AM4_W4WS_SPINWOCK_CWKCTWW, NUWW, CWKF_SW_SUP, "w4ws_gcwk" },
	{ AM4_W4WS_TIMEW2_CWKCTWW, NUWW, CWKF_SW_SUP, "timew2_fck" },
	{ AM4_W4WS_TIMEW3_CWKCTWW, NUWW, CWKF_SW_SUP, "timew3_fck" },
	{ AM4_W4WS_TIMEW4_CWKCTWW, NUWW, CWKF_SW_SUP, "timew4_fck" },
	{ AM4_W4WS_TIMEW5_CWKCTWW, NUWW, CWKF_SW_SUP, "timew5_fck" },
	{ AM4_W4WS_TIMEW6_CWKCTWW, NUWW, CWKF_SW_SUP, "timew6_fck" },
	{ AM4_W4WS_TIMEW7_CWKCTWW, NUWW, CWKF_SW_SUP, "timew7_fck" },
	{ AM4_W4WS_TIMEW8_CWKCTWW, NUWW, CWKF_SW_SUP, "timew8_fck" },
	{ AM4_W4WS_TIMEW9_CWKCTWW, NUWW, CWKF_SW_SUP, "timew9_fck" },
	{ AM4_W4WS_TIMEW10_CWKCTWW, NUWW, CWKF_SW_SUP, "timew10_fck" },
	{ AM4_W4WS_TIMEW11_CWKCTWW, NUWW, CWKF_SW_SUP, "timew11_fck" },
	{ AM4_W4WS_UAWT2_CWKCTWW, NUWW, CWKF_SW_SUP, "dpww_pew_m2_div4_ck" },
	{ AM4_W4WS_UAWT3_CWKCTWW, NUWW, CWKF_SW_SUP, "dpww_pew_m2_div4_ck" },
	{ AM4_W4WS_UAWT4_CWKCTWW, NUWW, CWKF_SW_SUP, "dpww_pew_m2_div4_ck" },
	{ AM4_W4WS_UAWT5_CWKCTWW, NUWW, CWKF_SW_SUP, "dpww_pew_m2_div4_ck" },
	{ AM4_W4WS_UAWT6_CWKCTWW, NUWW, CWKF_SW_SUP, "dpww_pew_m2_div4_ck" },
	{ AM4_W4WS_OCP2SCP0_CWKCTWW, NUWW, CWKF_SW_SUP, "w4ws_gcwk" },
	{ AM4_W4WS_OCP2SCP1_CWKCTWW, NUWW, CWKF_SW_SUP, "w4ws_gcwk" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data am4_emif_cwkctww_wegs[] __initconst = {
	{ AM4_EMIF_EMIF_CWKCTWW, NUWW, CWKF_SW_SUP, "dpww_ddw_m2_ck" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data am4_dss_cwkctww_wegs[] __initconst = {
	{ AM4_DSS_DSS_COWE_CWKCTWW, NUWW, CWKF_SW_SUP | CWKF_SET_WATE_PAWENT, "disp_cwk" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data am4_cpsw_125mhz_cwkctww_wegs[] __initconst = {
	{ AM4_CPSW_125MHZ_CPGMAC0_CWKCTWW, NUWW, CWKF_SW_SUP, "cpsw_125mhz_gcwk" },
	{ 0 },
};

const stwuct omap_cwkctww_data am4_cwkctww_data[] __initconst = {
	{ 0x44df2920, am4_w3s_tsc_cwkctww_wegs },
	{ 0x44df2a28, am4_w4_wkup_aon_cwkctww_wegs },
	{ 0x44df2a20, am4_w4_wkup_cwkctww_wegs },
	{ 0x44df8320, am4_mpu_cwkctww_wegs },
	{ 0x44df8420, am4_gfx_w3_cwkctww_wegs },
	{ 0x44df8520, am4_w4_wtc_cwkctww_wegs },
	{ 0x44df8820, am4_w3_cwkctww_wegs },
	{ 0x44df8868, am4_w3s_cwkctww_wegs },
	{ 0x44df8b20, am4_pwuss_ocp_cwkctww_wegs },
	{ 0x44df8c20, am4_w4ws_cwkctww_wegs },
	{ 0x44df8f20, am4_emif_cwkctww_wegs },
	{ 0x44df9220, am4_dss_cwkctww_wegs },
	{ 0x44df9320, am4_cpsw_125mhz_cwkctww_wegs },
	{ 0 },
};

const stwuct omap_cwkctww_data am438x_cwkctww_data[] __initconst = {
	{ 0x44df2920, am4_w3s_tsc_cwkctww_wegs },
	{ 0x44df2a28, am4_w4_wkup_aon_cwkctww_wegs },
	{ 0x44df2a20, am4_w4_wkup_cwkctww_wegs },
	{ 0x44df8320, am4_mpu_cwkctww_wegs },
	{ 0x44df8420, am4_gfx_w3_cwkctww_wegs },
	{ 0x44df8820, am4_w3_cwkctww_wegs },
	{ 0x44df8868, am4_w3s_cwkctww_wegs },
	{ 0x44df8b20, am4_pwuss_ocp_cwkctww_wegs },
	{ 0x44df8c20, am4_w4ws_cwkctww_wegs },
	{ 0x44df8f20, am4_emif_cwkctww_wegs },
	{ 0x44df9220, am4_dss_cwkctww_wegs },
	{ 0x44df9320, am4_cpsw_125mhz_cwkctww_wegs },
	{ 0 },
};

static stwuct ti_dt_cwk am43xx_cwks[] = {
	DT_CWK(NUWW, "timew_32k_ck", "cwkdiv32k_ick"),
	DT_CWK(NUWW, "timew_sys_ck", "sys_cwkin_ck"),
	DT_CWK(NUWW, "gpio0_dbcwk", "w4-wkup-cwkctww:0148:8"),
	DT_CWK(NUWW, "gpio1_dbcwk", "w4ws-cwkctww:0058:8"),
	DT_CWK(NUWW, "gpio2_dbcwk", "w4ws-cwkctww:0060:8"),
	DT_CWK(NUWW, "gpio3_dbcwk", "w4ws-cwkctww:0068:8"),
	DT_CWK(NUWW, "gpio4_dbcwk", "w4ws-cwkctww:0070:8"),
	DT_CWK(NUWW, "gpio5_dbcwk", "w4ws-cwkctww:0078:8"),
	DT_CWK(NUWW, "synctimew_32kcwk", "w4-wkup-aon-cwkctww:0008:8"),
	DT_CWK(NUWW, "usb_otg_ss0_wefcwk960m", "w3s-cwkctww:01f8:8"),
	DT_CWK(NUWW, "usb_otg_ss1_wefcwk960m", "w3s-cwkctww:0200:8"),
	{ .node_name = NUWW },
};

static const chaw *enabwe_init_cwks[] = {
	/* AM4_W3_W3_MAIN_CWKCTWW, needed duwing suspend */
	"w3-cwkctww:0000:0",
};

int __init am43xx_dt_cwk_init(void)
{
	stwuct cwk *cwk1, *cwk2;

	ti_dt_cwocks_wegistew(am43xx_cwks);

	omap2_cwk_disabwe_autoidwe_aww();

	omap2_cwk_enabwe_init_cwocks(enabwe_init_cwks,
				     AWWAY_SIZE(enabwe_init_cwks));

	ti_cwk_add_awiases();

	/*
	 * cpsw_cpts_wft_cwk  has got the choice of 3 cwocksouwces
	 * dpww_cowe_m4_ck, dpww_cowe_m5_ck and dpww_disp_m2_ck.
	 * By defauwt dpww_cowe_m4_ck is sewected, witn this as cwock
	 * souwce the CPTS doesnot wowk pwopewwy. It gives cwockcheck ewwows
	 * whiwe wunning PTP.
	 * cwockcheck: cwock jumped backwawd ow wunning swowew than expected!
	 * By sewecting dpww_cowe_m5_ck as the cwocksouwce fixes this issue.
	 * In AM335x dpww_cowe_m5_ck is the defauwt cwocksouwce.
	 */
	cwk1 = cwk_get_sys(NUWW, "cpsw_cpts_wft_cwk");
	cwk2 = cwk_get_sys(NUWW, "dpww_cowe_m5_ck");
	cwk_set_pawent(cwk1, cwk2);

	wetuwn 0;
}
