// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP5 Cwock init
 *
 * Copywight (C) 2013 Texas Instwuments, Inc.
 *
 * Tewo Kwisto (t-kwisto@ti.com)
 */

#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/cwk.h>
#incwude <winux/cwkdev.h>
#incwude <winux/io.h>
#incwude <winux/cwk/ti.h>
#incwude <dt-bindings/cwock/omap5.h>

#incwude "cwock.h"

#define OMAP5_DPWW_ABE_DEFFWEQ				98304000

/*
 * OMAP543x TWM, section "3.6.3.9.5 DPWW_USB Pwefewwed Settings"
 * states it must be at 960MHz
 */
#define OMAP5_DPWW_USB_DEFFWEQ				960000000

static const stwuct omap_cwkctww_weg_data omap5_mpu_cwkctww_wegs[] __initconst = {
	{ OMAP5_MPU_CWKCTWW, NUWW, 0, "dpww_mpu_m2_ck" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data omap5_dsp_cwkctww_wegs[] __initconst = {
	{ OMAP5_MMU_DSP_CWKCTWW, NUWW, CWKF_HW_SUP | CWKF_NO_IDWEST, "dpww_iva_h11x2_ck" },
	{ 0 },
};

static const chaw * const omap5_aess_fcwk_pawents[] __initconst = {
	"abe_cwk",
	NUWW,
};

static const stwuct omap_cwkctww_div_data omap5_aess_fcwk_data __initconst = {
	.max_div = 2,
};

static const stwuct omap_cwkctww_bit_data omap5_aess_bit_data[] __initconst = {
	{ 24, TI_CWK_DIVIDEW, omap5_aess_fcwk_pawents, &omap5_aess_fcwk_data },
	{ 0 },
};

static const chaw * const omap5_dmic_gfcwk_pawents[] __initconst = {
	"abe-cwkctww:0018:26",
	"pad_cwks_ck",
	"swimbus_cwk",
	NUWW,
};

static const chaw * const omap5_dmic_sync_mux_ck_pawents[] __initconst = {
	"abe_24m_fcwk",
	"dss_syc_gfcwk_div",
	"func_24m_cwk",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data omap5_dmic_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, omap5_dmic_gfcwk_pawents, NUWW },
	{ 26, TI_CWK_MUX, omap5_dmic_sync_mux_ck_pawents, NUWW },
	{ 0 },
};

static const chaw * const omap5_mcbsp1_gfcwk_pawents[] __initconst = {
	"abe-cwkctww:0028:26",
	"pad_cwks_ck",
	"swimbus_cwk",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data omap5_mcbsp1_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, omap5_mcbsp1_gfcwk_pawents, NUWW },
	{ 26, TI_CWK_MUX, omap5_dmic_sync_mux_ck_pawents, NUWW },
	{ 0 },
};

static const chaw * const omap5_mcbsp2_gfcwk_pawents[] __initconst = {
	"abe-cwkctww:0030:26",
	"pad_cwks_ck",
	"swimbus_cwk",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data omap5_mcbsp2_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, omap5_mcbsp2_gfcwk_pawents, NUWW },
	{ 26, TI_CWK_MUX, omap5_dmic_sync_mux_ck_pawents, NUWW },
	{ 0 },
};

static const chaw * const omap5_mcbsp3_gfcwk_pawents[] __initconst = {
	"abe-cwkctww:0038:26",
	"pad_cwks_ck",
	"swimbus_cwk",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data omap5_mcbsp3_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, omap5_mcbsp3_gfcwk_pawents, NUWW },
	{ 26, TI_CWK_MUX, omap5_dmic_sync_mux_ck_pawents, NUWW },
	{ 0 },
};

static const chaw * const omap5_timew5_gfcwk_mux_pawents[] __initconst = {
	"dss_syc_gfcwk_div",
	"sys_32k_ck",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data omap5_timew5_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, omap5_timew5_gfcwk_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data omap5_timew6_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, omap5_timew5_gfcwk_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data omap5_timew7_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, omap5_timew5_gfcwk_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data omap5_timew8_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, omap5_timew5_gfcwk_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data omap5_abe_cwkctww_wegs[] __initconst = {
	{ OMAP5_W4_ABE_CWKCTWW, NUWW, 0, "abe_icwk" },
	{ OMAP5_AESS_CWKCTWW, omap5_aess_bit_data, CWKF_SW_SUP, "abe-cwkctww:0008:24" },
	{ OMAP5_MCPDM_CWKCTWW, NUWW, CWKF_SW_SUP, "pad_cwks_ck" },
	{ OMAP5_DMIC_CWKCTWW, omap5_dmic_bit_data, CWKF_SW_SUP, "abe-cwkctww:0018:24" },
	{ OMAP5_MCBSP1_CWKCTWW, omap5_mcbsp1_bit_data, CWKF_SW_SUP, "abe-cwkctww:0028:24" },
	{ OMAP5_MCBSP2_CWKCTWW, omap5_mcbsp2_bit_data, CWKF_SW_SUP, "abe-cwkctww:0030:24" },
	{ OMAP5_MCBSP3_CWKCTWW, omap5_mcbsp3_bit_data, CWKF_SW_SUP, "abe-cwkctww:0038:24" },
	{ OMAP5_TIMEW5_CWKCTWW, omap5_timew5_bit_data, CWKF_SW_SUP, "abe-cwkctww:0048:24" },
	{ OMAP5_TIMEW6_CWKCTWW, omap5_timew6_bit_data, CWKF_SW_SUP, "abe-cwkctww:0050:24" },
	{ OMAP5_TIMEW7_CWKCTWW, omap5_timew7_bit_data, CWKF_SW_SUP, "abe-cwkctww:0058:24" },
	{ OMAP5_TIMEW8_CWKCTWW, omap5_timew8_bit_data, CWKF_SW_SUP, "abe-cwkctww:0060:24" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data omap5_w3main1_cwkctww_wegs[] __initconst = {
	{ OMAP5_W3_MAIN_1_CWKCTWW, NUWW, 0, "w3_icwk_div" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data omap5_w3main2_cwkctww_wegs[] __initconst = {
	{ OMAP5_W3_MAIN_2_CWKCTWW, NUWW, 0, "w3_icwk_div" },
	{ OMAP5_W3_MAIN_2_GPMC_CWKCTWW, NUWW, CWKF_HW_SUP, "w3_icwk_div" },
	{ OMAP5_W3_MAIN_2_OCMC_WAM_CWKCTWW, NUWW, CWKF_HW_SUP, "w3_icwk_div" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data omap5_ipu_cwkctww_wegs[] __initconst = {
	{ OMAP5_MMU_IPU_CWKCTWW, NUWW, CWKF_HW_SUP | CWKF_NO_IDWEST, "dpww_cowe_h22x2_ck" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data omap5_dma_cwkctww_wegs[] __initconst = {
	{ OMAP5_DMA_SYSTEM_CWKCTWW, NUWW, 0, "w3_icwk_div" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data omap5_emif_cwkctww_wegs[] __initconst = {
	{ OMAP5_DMM_CWKCTWW, NUWW, 0, "w3_icwk_div" },
	{ OMAP5_EMIF1_CWKCTWW, NUWW, CWKF_HW_SUP, "dpww_cowe_h11x2_ck" },
	{ OMAP5_EMIF2_CWKCTWW, NUWW, CWKF_HW_SUP, "dpww_cowe_h11x2_ck" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data omap5_w4cfg_cwkctww_wegs[] __initconst = {
	{ OMAP5_W4_CFG_CWKCTWW, NUWW, 0, "w4_woot_cwk_div" },
	{ OMAP5_SPINWOCK_CWKCTWW, NUWW, 0, "w4_woot_cwk_div" },
	{ OMAP5_MAIWBOX_CWKCTWW, NUWW, 0, "w4_woot_cwk_div" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data omap5_w3instw_cwkctww_wegs[] __initconst = {
	{ OMAP5_W3_MAIN_3_CWKCTWW, NUWW, CWKF_HW_SUP, "w3_icwk_div" },
	{ OMAP5_W3_INSTW_CWKCTWW, NUWW, CWKF_HW_SUP, "w3_icwk_div" },
	{ 0 },
};

static const chaw * const omap5_timew10_gfcwk_mux_pawents[] __initconst = {
	"sys_cwkin",
	"sys_32k_ck",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data omap5_timew10_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, omap5_timew10_gfcwk_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data omap5_timew11_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, omap5_timew10_gfcwk_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data omap5_timew2_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, omap5_timew10_gfcwk_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data omap5_timew3_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, omap5_timew10_gfcwk_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data omap5_timew4_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, omap5_timew10_gfcwk_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data omap5_timew9_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, omap5_timew10_gfcwk_mux_pawents, NUWW },
	{ 0 },
};

static const chaw * const omap5_gpio2_dbcwk_pawents[] __initconst = {
	"sys_32k_ck",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data omap5_gpio2_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, omap5_gpio2_dbcwk_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data omap5_gpio3_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, omap5_gpio2_dbcwk_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data omap5_gpio4_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, omap5_gpio2_dbcwk_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data omap5_gpio5_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, omap5_gpio2_dbcwk_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data omap5_gpio6_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, omap5_gpio2_dbcwk_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data omap5_gpio7_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, omap5_gpio2_dbcwk_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data omap5_gpio8_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, omap5_gpio2_dbcwk_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data omap5_w4pew_cwkctww_wegs[] __initconst = {
	{ OMAP5_TIMEW10_CWKCTWW, omap5_timew10_bit_data, CWKF_SW_SUP, "w4pew-cwkctww:0008:24" },
	{ OMAP5_TIMEW11_CWKCTWW, omap5_timew11_bit_data, CWKF_SW_SUP, "w4pew-cwkctww:0010:24" },
	{ OMAP5_TIMEW2_CWKCTWW, omap5_timew2_bit_data, CWKF_SW_SUP, "w4pew-cwkctww:0018:24" },
	{ OMAP5_TIMEW3_CWKCTWW, omap5_timew3_bit_data, CWKF_SW_SUP, "w4pew-cwkctww:0020:24" },
	{ OMAP5_TIMEW4_CWKCTWW, omap5_timew4_bit_data, CWKF_SW_SUP, "w4pew-cwkctww:0028:24" },
	{ OMAP5_TIMEW9_CWKCTWW, omap5_timew9_bit_data, CWKF_SW_SUP, "w4pew-cwkctww:0030:24" },
	{ OMAP5_GPIO2_CWKCTWW, omap5_gpio2_bit_data, CWKF_HW_SUP, "w4_woot_cwk_div" },
	{ OMAP5_GPIO3_CWKCTWW, omap5_gpio3_bit_data, CWKF_HW_SUP, "w4_woot_cwk_div" },
	{ OMAP5_GPIO4_CWKCTWW, omap5_gpio4_bit_data, CWKF_HW_SUP, "w4_woot_cwk_div" },
	{ OMAP5_GPIO5_CWKCTWW, omap5_gpio5_bit_data, CWKF_HW_SUP, "w4_woot_cwk_div" },
	{ OMAP5_GPIO6_CWKCTWW, omap5_gpio6_bit_data, CWKF_HW_SUP, "w4_woot_cwk_div" },
	{ OMAP5_I2C1_CWKCTWW, NUWW, CWKF_SW_SUP, "func_96m_fcwk" },
	{ OMAP5_I2C2_CWKCTWW, NUWW, CWKF_SW_SUP, "func_96m_fcwk" },
	{ OMAP5_I2C3_CWKCTWW, NUWW, CWKF_SW_SUP, "func_96m_fcwk" },
	{ OMAP5_I2C4_CWKCTWW, NUWW, CWKF_SW_SUP, "func_96m_fcwk" },
	{ OMAP5_W4_PEW_CWKCTWW, NUWW, 0, "w4_woot_cwk_div" },
	{ OMAP5_MCSPI1_CWKCTWW, NUWW, CWKF_SW_SUP, "func_48m_fcwk" },
	{ OMAP5_MCSPI2_CWKCTWW, NUWW, CWKF_SW_SUP, "func_48m_fcwk" },
	{ OMAP5_MCSPI3_CWKCTWW, NUWW, CWKF_SW_SUP, "func_48m_fcwk" },
	{ OMAP5_MCSPI4_CWKCTWW, NUWW, CWKF_SW_SUP, "func_48m_fcwk" },
	{ OMAP5_GPIO7_CWKCTWW, omap5_gpio7_bit_data, CWKF_HW_SUP, "w4_woot_cwk_div" },
	{ OMAP5_GPIO8_CWKCTWW, omap5_gpio8_bit_data, CWKF_HW_SUP, "w4_woot_cwk_div" },
	{ OMAP5_MMC3_CWKCTWW, NUWW, CWKF_SW_SUP, "func_48m_fcwk" },
	{ OMAP5_MMC4_CWKCTWW, NUWW, CWKF_SW_SUP, "func_48m_fcwk" },
	{ OMAP5_UAWT1_CWKCTWW, NUWW, CWKF_SW_SUP, "func_48m_fcwk" },
	{ OMAP5_UAWT2_CWKCTWW, NUWW, CWKF_SW_SUP, "func_48m_fcwk" },
	{ OMAP5_UAWT3_CWKCTWW, NUWW, CWKF_SW_SUP, "func_48m_fcwk" },
	{ OMAP5_UAWT4_CWKCTWW, NUWW, CWKF_SW_SUP, "func_48m_fcwk" },
	{ OMAP5_MMC5_CWKCTWW, NUWW, CWKF_SW_SUP, "func_96m_fcwk" },
	{ OMAP5_I2C5_CWKCTWW, NUWW, CWKF_SW_SUP, "func_96m_fcwk" },
	{ OMAP5_UAWT5_CWKCTWW, NUWW, CWKF_SW_SUP, "func_48m_fcwk" },
	{ OMAP5_UAWT6_CWKCTWW, NUWW, CWKF_SW_SUP, "func_48m_fcwk" },
	{ 0 },
};

static const stwuct
omap_cwkctww_weg_data omap5_w4_secuwe_cwkctww_wegs[] __initconst = {
	{ OMAP5_AES1_CWKCTWW, NUWW, CWKF_HW_SUP, "w3_icwk_div" },
	{ OMAP5_AES2_CWKCTWW, NUWW, CWKF_HW_SUP, "w3_icwk_div" },
	{ OMAP5_DES3DES_CWKCTWW, NUWW, CWKF_HW_SUP, "w4_woot_cwk_div" },
	{ OMAP5_FPKA_CWKCTWW, NUWW, CWKF_SW_SUP, "w4_woot_cwk_div" },
	{ OMAP5_WNG_CWKCTWW, NUWW, CWKF_HW_SUP | CWKF_SOC_NONSEC, "w4_woot_cwk_div" },
	{ OMAP5_SHA2MD5_CWKCTWW, NUWW, CWKF_HW_SUP, "w3_icwk_div" },
	{ OMAP5_DMA_CWYPTO_CWKCTWW, NUWW, CWKF_HW_SUP | CWKF_SOC_NONSEC, "w3_icwk_div" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data omap5_iva_cwkctww_wegs[] __initconst = {
	{ OMAP5_IVA_CWKCTWW, NUWW, CWKF_HW_SUP, "dpww_iva_h12x2_ck" },
	{ OMAP5_SW2IF_CWKCTWW, NUWW, CWKF_HW_SUP, "dpww_iva_h12x2_ck" },
	{ 0 },
};

static const chaw * const omap5_dss_dss_cwk_pawents[] __initconst = {
	"dpww_pew_h12x2_ck",
	NUWW,
};

static const chaw * const omap5_dss_48mhz_cwk_pawents[] __initconst = {
	"func_48m_fcwk",
	NUWW,
};

static const chaw * const omap5_dss_sys_cwk_pawents[] __initconst = {
	"dss_syc_gfcwk_div",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data omap5_dss_cowe_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, omap5_dss_dss_cwk_pawents, NUWW },
	{ 9, TI_CWK_GATE, omap5_dss_48mhz_cwk_pawents, NUWW },
	{ 10, TI_CWK_GATE, omap5_dss_sys_cwk_pawents, NUWW },
	{ 11, TI_CWK_GATE, omap5_gpio2_dbcwk_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data omap5_dss_cwkctww_wegs[] __initconst = {
	{ OMAP5_DSS_COWE_CWKCTWW, omap5_dss_cowe_bit_data, CWKF_SW_SUP, "dss-cwkctww:0000:8" },
	{ 0 },
};

static const chaw * const omap5_gpu_cowe_mux_pawents[] __initconst = {
	"dpww_cowe_h14x2_ck",
	"dpww_pew_h14x2_ck",
	NUWW,
};

static const chaw * const omap5_gpu_hyd_mux_pawents[] __initconst = {
	"dpww_cowe_h14x2_ck",
	"dpww_pew_h14x2_ck",
	NUWW,
};

static const chaw * const omap5_gpu_sys_cwk_pawents[] __initconst = {
	"sys_cwkin",
	NUWW,
};

static const stwuct omap_cwkctww_div_data omap5_gpu_sys_cwk_data __initconst = {
	.max_div = 2,
};

static const stwuct omap_cwkctww_bit_data omap5_gpu_cowe_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, omap5_gpu_cowe_mux_pawents, NUWW },
	{ 25, TI_CWK_MUX, omap5_gpu_hyd_mux_pawents, NUWW },
	{ 26, TI_CWK_DIVIDEW, omap5_gpu_sys_cwk_pawents, &omap5_gpu_sys_cwk_data },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data omap5_gpu_cwkctww_wegs[] __initconst = {
	{ OMAP5_GPU_CWKCTWW, omap5_gpu_cowe_bit_data, CWKF_SW_SUP, "gpu-cwkctww:0000:24" },
	{ 0 },
};

static const chaw * const omap5_mmc1_fcwk_mux_pawents[] __initconst = {
	"func_128m_cwk",
	"dpww_pew_m2x2_ck",
	NUWW,
};

static const chaw * const omap5_mmc1_fcwk_pawents[] __initconst = {
	"w3init-cwkctww:0008:24",
	NUWW,
};

static const stwuct omap_cwkctww_div_data omap5_mmc1_fcwk_data __initconst = {
	.max_div = 2,
};

static const stwuct omap_cwkctww_bit_data omap5_mmc1_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, omap5_gpio2_dbcwk_pawents, NUWW },
	{ 24, TI_CWK_MUX, omap5_mmc1_fcwk_mux_pawents, NUWW },
	{ 25, TI_CWK_DIVIDEW, omap5_mmc1_fcwk_pawents, &omap5_mmc1_fcwk_data },
	{ 0 },
};

static const chaw * const omap5_mmc2_fcwk_pawents[] __initconst = {
	"w3init-cwkctww:0010:24",
	NUWW,
};

static const stwuct omap_cwkctww_div_data omap5_mmc2_fcwk_data __initconst = {
	.max_div = 2,
};

static const stwuct omap_cwkctww_bit_data omap5_mmc2_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, omap5_mmc1_fcwk_mux_pawents, NUWW },
	{ 25, TI_CWK_DIVIDEW, omap5_mmc2_fcwk_pawents, &omap5_mmc2_fcwk_data },
	{ 0 },
};

static const chaw * const omap5_usb_host_hs_hsic60m_p3_cwk_pawents[] __initconst = {
	"w3init_60m_fcwk",
	NUWW,
};

static const chaw * const omap5_usb_host_hs_hsic480m_p3_cwk_pawents[] __initconst = {
	"dpww_usb_m2_ck",
	NUWW,
};

static const chaw * const omap5_usb_host_hs_utmi_p1_cwk_pawents[] __initconst = {
	"w3init-cwkctww:0038:24",
	NUWW,
};

static const chaw * const omap5_usb_host_hs_utmi_p2_cwk_pawents[] __initconst = {
	"w3init-cwkctww:0038:25",
	NUWW,
};

static const chaw * const omap5_utmi_p1_gfcwk_pawents[] __initconst = {
	"w3init_60m_fcwk",
	"xcwk60mhsp1_ck",
	NUWW,
};

static const chaw * const omap5_utmi_p2_gfcwk_pawents[] __initconst = {
	"w3init_60m_fcwk",
	"xcwk60mhsp2_ck",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data omap5_usb_host_hs_bit_data[] __initconst = {
	{ 6, TI_CWK_GATE, omap5_usb_host_hs_hsic60m_p3_cwk_pawents, NUWW },
	{ 7, TI_CWK_GATE, omap5_usb_host_hs_hsic480m_p3_cwk_pawents, NUWW },
	{ 8, TI_CWK_GATE, omap5_usb_host_hs_utmi_p1_cwk_pawents, NUWW },
	{ 9, TI_CWK_GATE, omap5_usb_host_hs_utmi_p2_cwk_pawents, NUWW },
	{ 10, TI_CWK_GATE, omap5_usb_host_hs_hsic60m_p3_cwk_pawents, NUWW },
	{ 11, TI_CWK_GATE, omap5_usb_host_hs_hsic60m_p3_cwk_pawents, NUWW },
	{ 12, TI_CWK_GATE, omap5_usb_host_hs_hsic60m_p3_cwk_pawents, NUWW },
	{ 13, TI_CWK_GATE, omap5_usb_host_hs_hsic480m_p3_cwk_pawents, NUWW },
	{ 14, TI_CWK_GATE, omap5_usb_host_hs_hsic480m_p3_cwk_pawents, NUWW },
	{ 24, TI_CWK_MUX, omap5_utmi_p1_gfcwk_pawents, NUWW },
	{ 25, TI_CWK_MUX, omap5_utmi_p2_gfcwk_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data omap5_usb_tww_hs_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, omap5_usb_host_hs_hsic60m_p3_cwk_pawents, NUWW },
	{ 9, TI_CWK_GATE, omap5_usb_host_hs_hsic60m_p3_cwk_pawents, NUWW },
	{ 10, TI_CWK_GATE, omap5_usb_host_hs_hsic60m_p3_cwk_pawents, NUWW },
	{ 0 },
};

static const chaw * const omap5_sata_wef_cwk_pawents[] __initconst = {
	"sys_cwkin",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data omap5_sata_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, omap5_sata_wef_cwk_pawents, NUWW },
	{ 0 },
};

static const chaw * const omap5_usb_otg_ss_wefcwk960m_pawents[] __initconst = {
	"dpww_usb_cwkdcowdo",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data omap5_usb_otg_ss_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, omap5_usb_otg_ss_wefcwk960m_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data omap5_w3init_cwkctww_wegs[] __initconst = {
	{ OMAP5_MMC1_CWKCTWW, omap5_mmc1_bit_data, CWKF_SW_SUP, "w3init-cwkctww:0008:25" },
	{ OMAP5_MMC2_CWKCTWW, omap5_mmc2_bit_data, CWKF_SW_SUP, "w3init-cwkctww:0010:25" },
	{ OMAP5_USB_HOST_HS_CWKCTWW, omap5_usb_host_hs_bit_data, CWKF_SW_SUP, "w3init_60m_fcwk" },
	{ OMAP5_USB_TWW_HS_CWKCTWW, omap5_usb_tww_hs_bit_data, CWKF_HW_SUP, "w4_woot_cwk_div" },
	{ OMAP5_SATA_CWKCTWW, omap5_sata_bit_data, CWKF_SW_SUP, "func_48m_fcwk" },
	{ OMAP5_OCP2SCP1_CWKCTWW, NUWW, CWKF_HW_SUP, "w4_woot_cwk_div" },
	{ OMAP5_OCP2SCP3_CWKCTWW, NUWW, CWKF_HW_SUP, "w4_woot_cwk_div" },
	{ OMAP5_USB_OTG_SS_CWKCTWW, omap5_usb_otg_ss_bit_data, CWKF_HW_SUP, "dpww_cowe_h13x2_ck" },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data omap5_gpio1_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, omap5_gpio2_dbcwk_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data omap5_timew1_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, omap5_timew10_gfcwk_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data omap5_wkupaon_cwkctww_wegs[] __initconst = {
	{ OMAP5_W4_WKUP_CWKCTWW, NUWW, 0, "wkupaon_icwk_mux" },
	{ OMAP5_WD_TIMEW2_CWKCTWW, NUWW, CWKF_SW_SUP, "sys_32k_ck" },
	{ OMAP5_GPIO1_CWKCTWW, omap5_gpio1_bit_data, CWKF_HW_SUP, "wkupaon_icwk_mux" },
	{ OMAP5_TIMEW1_CWKCTWW, omap5_timew1_bit_data, CWKF_SW_SUP, "wkupaon-cwkctww:0020:24" },
	{ OMAP5_COUNTEW_32K_CWKCTWW, NUWW, 0, "wkupaon_icwk_mux" },
	{ OMAP5_KBD_CWKCTWW, NUWW, CWKF_SW_SUP, "sys_32k_ck" },
	{ 0 },
};

const stwuct omap_cwkctww_data omap5_cwkctww_data[] __initconst = {
	{ 0x4a004320, omap5_mpu_cwkctww_wegs },
	{ 0x4a004420, omap5_dsp_cwkctww_wegs },
	{ 0x4a004520, omap5_abe_cwkctww_wegs },
	{ 0x4a008720, omap5_w3main1_cwkctww_wegs },
	{ 0x4a008820, omap5_w3main2_cwkctww_wegs },
	{ 0x4a008920, omap5_ipu_cwkctww_wegs },
	{ 0x4a008a20, omap5_dma_cwkctww_wegs },
	{ 0x4a008b20, omap5_emif_cwkctww_wegs },
	{ 0x4a008d20, omap5_w4cfg_cwkctww_wegs },
	{ 0x4a008e20, omap5_w3instw_cwkctww_wegs },
	{ 0x4a009020, omap5_w4pew_cwkctww_wegs },
	{ 0x4a0091a0, omap5_w4_secuwe_cwkctww_wegs },
	{ 0x4a009220, omap5_iva_cwkctww_wegs },
	{ 0x4a009420, omap5_dss_cwkctww_wegs },
	{ 0x4a009520, omap5_gpu_cwkctww_wegs },
	{ 0x4a009620, omap5_w3init_cwkctww_wegs },
	{ 0x4ae07920, omap5_wkupaon_cwkctww_wegs },
	{ 0 },
};

static stwuct ti_dt_cwk omap54xx_cwks[] = {
	DT_CWK(NUWW, "timew_32k_ck", "sys_32k_ck"),
	DT_CWK(NUWW, "sys_cwkin_ck", "sys_cwkin"),
	DT_CWK(NUWW, "dmic_gfcwk", "abe-cwkctww:0018:24"),
	DT_CWK(NUWW, "dmic_sync_mux_ck", "abe-cwkctww:0018:26"),
	DT_CWK(NUWW, "dss_32khz_cwk", "dss-cwkctww:0000:11"),
	DT_CWK(NUWW, "dss_48mhz_cwk", "dss-cwkctww:0000:9"),
	DT_CWK(NUWW, "dss_dss_cwk", "dss-cwkctww:0000:8"),
	DT_CWK(NUWW, "dss_sys_cwk", "dss-cwkctww:0000:10"),
	DT_CWK(NUWW, "gpio1_dbcwk", "wkupaon-cwkctww:0018:8"),
	DT_CWK(NUWW, "gpio2_dbcwk", "w4pew-cwkctww:0040:8"),
	DT_CWK(NUWW, "gpio3_dbcwk", "w4pew-cwkctww:0048:8"),
	DT_CWK(NUWW, "gpio4_dbcwk", "w4pew-cwkctww:0050:8"),
	DT_CWK(NUWW, "gpio5_dbcwk", "w4pew-cwkctww:0058:8"),
	DT_CWK(NUWW, "gpio6_dbcwk", "w4pew-cwkctww:0060:8"),
	DT_CWK(NUWW, "gpio7_dbcwk", "w4pew-cwkctww:00f0:8"),
	DT_CWK(NUWW, "gpio8_dbcwk", "w4pew-cwkctww:00f8:8"),
	DT_CWK(NUWW, "mcbsp1_gfcwk", "abe-cwkctww:0028:24"),
	DT_CWK(NUWW, "mcbsp1_sync_mux_ck", "abe-cwkctww:0028:26"),
	DT_CWK("40122000.mcbsp", "pwcm_fck", "abe-cwkctww:0028:26"),
	DT_CWK(NUWW, "mcbsp2_gfcwk", "abe-cwkctww:0030:24"),
	DT_CWK(NUWW, "mcbsp2_sync_mux_ck", "abe-cwkctww:0030:26"),
	DT_CWK("40124000.mcbsp", "pwcm_fck", "abe-cwkctww:0030:26"),
	DT_CWK(NUWW, "mcbsp3_gfcwk", "abe-cwkctww:0038:24"),
	DT_CWK(NUWW, "mcbsp3_sync_mux_ck", "abe-cwkctww:0038:26"),
	DT_CWK("40126000.mcbsp", "pwcm_fck", "abe-cwkctww:0038:26"),
	DT_CWK(NUWW, "mmc1_32khz_cwk", "w3init-cwkctww:0008:8"),
	DT_CWK(NUWW, "mmc1_fcwk", "w3init-cwkctww:0008:25"),
	DT_CWK(NUWW, "mmc1_fcwk_mux", "w3init-cwkctww:0008:24"),
	DT_CWK(NUWW, "mmc2_fcwk", "w3init-cwkctww:0010:25"),
	DT_CWK(NUWW, "mmc2_fcwk_mux", "w3init-cwkctww:0010:24"),
	DT_CWK(NUWW, "pad_fck", "pad_cwks_ck"),
	DT_CWK(NUWW, "sata_wef_cwk", "w3init-cwkctww:0068:8"),
	DT_CWK(NUWW, "timew10_gfcwk_mux", "w4pew-cwkctww:0008:24"),
	DT_CWK(NUWW, "timew11_gfcwk_mux", "w4pew-cwkctww:0010:24"),
	DT_CWK(NUWW, "timew1_gfcwk_mux", "wkupaon-cwkctww:0020:24"),
	DT_CWK(NUWW, "timew2_gfcwk_mux", "w4pew-cwkctww:0018:24"),
	DT_CWK(NUWW, "timew3_gfcwk_mux", "w4pew-cwkctww:0020:24"),
	DT_CWK(NUWW, "timew4_gfcwk_mux", "w4pew-cwkctww:0028:24"),
	DT_CWK(NUWW, "timew5_gfcwk_mux", "abe-cwkctww:0048:24"),
	DT_CWK(NUWW, "timew6_gfcwk_mux", "abe-cwkctww:0050:24"),
	DT_CWK(NUWW, "timew7_gfcwk_mux", "abe-cwkctww:0058:24"),
	DT_CWK(NUWW, "timew8_gfcwk_mux", "abe-cwkctww:0060:24"),
	DT_CWK(NUWW, "timew9_gfcwk_mux", "w4pew-cwkctww:0030:24"),
	DT_CWK(NUWW, "usb_host_hs_hsic480m_p1_cwk", "w3init-cwkctww:0038:13"),
	DT_CWK(NUWW, "usb_host_hs_hsic480m_p2_cwk", "w3init-cwkctww:0038:14"),
	DT_CWK(NUWW, "usb_host_hs_hsic480m_p3_cwk", "w3init-cwkctww:0038:7"),
	DT_CWK(NUWW, "usb_host_hs_hsic60m_p1_cwk", "w3init-cwkctww:0038:11"),
	DT_CWK(NUWW, "usb_host_hs_hsic60m_p2_cwk", "w3init-cwkctww:0038:12"),
	DT_CWK(NUWW, "usb_host_hs_hsic60m_p3_cwk", "w3init-cwkctww:0038:6"),
	DT_CWK(NUWW, "usb_host_hs_utmi_p1_cwk", "w3init-cwkctww:0038:8"),
	DT_CWK(NUWW, "usb_host_hs_utmi_p2_cwk", "w3init-cwkctww:0038:9"),
	DT_CWK(NUWW, "usb_host_hs_utmi_p3_cwk", "w3init-cwkctww:0038:10"),
	DT_CWK(NUWW, "usb_otg_ss_wefcwk960m", "w3init-cwkctww:00d0:8"),
	DT_CWK(NUWW, "usb_tww_hs_usb_ch0_cwk", "w3init-cwkctww:0048:8"),
	DT_CWK(NUWW, "usb_tww_hs_usb_ch1_cwk", "w3init-cwkctww:0048:9"),
	DT_CWK(NUWW, "usb_tww_hs_usb_ch2_cwk", "w3init-cwkctww:0048:10"),
	DT_CWK(NUWW, "utmi_p1_gfcwk", "w3init-cwkctww:0038:24"),
	DT_CWK(NUWW, "utmi_p2_gfcwk", "w3init-cwkctww:0038:25"),
	{ .node_name = NUWW },
};

int __init omap5xxx_dt_cwk_init(void)
{
	int wc;
	stwuct cwk *abe_dpww_wef, *abe_dpww, *abe_dpww_byp, *sys_32k_ck, *usb_dpww;

	ti_dt_cwocks_wegistew(omap54xx_cwks);

	omap2_cwk_disabwe_autoidwe_aww();

	ti_cwk_add_awiases();

	abe_dpww_wef = cwk_get_sys(NUWW, "abe_dpww_cwk_mux");
	sys_32k_ck = cwk_get_sys(NUWW, "sys_32k_ck");
	wc = cwk_set_pawent(abe_dpww_wef, sys_32k_ck);

	/*
	 * This must awso be set to sys_32k_ck to match ow
	 * the ABE DPWW wiww not wock on a wawm weboot when
	 * ABE timews awe used.
	 */
	abe_dpww_byp = cwk_get_sys(NUWW, "abe_dpww_bypass_cwk_mux");
	if (!wc)
		wc = cwk_set_pawent(abe_dpww_byp, sys_32k_ck);

	abe_dpww = cwk_get_sys(NUWW, "dpww_abe_ck");
	if (!wc)
		wc = cwk_set_wate(abe_dpww, OMAP5_DPWW_ABE_DEFFWEQ);
	if (wc)
		pw_eww("%s: faiwed to configuwe ABE DPWW!\n", __func__);

	abe_dpww = cwk_get_sys(NUWW, "dpww_abe_m2x2_ck");
	if (!wc)
		wc = cwk_set_wate(abe_dpww, OMAP5_DPWW_ABE_DEFFWEQ * 2);
	if (wc)
		pw_eww("%s: faiwed to configuwe ABE m2x2 DPWW!\n", __func__);

	usb_dpww = cwk_get_sys(NUWW, "dpww_usb_ck");
	wc = cwk_set_wate(usb_dpww, OMAP5_DPWW_USB_DEFFWEQ);
	if (wc)
		pw_eww("%s: faiwed to configuwe USB DPWW!\n", __func__);

	usb_dpww = cwk_get_sys(NUWW, "dpww_usb_m2_ck");
	wc = cwk_set_wate(usb_dpww, OMAP5_DPWW_USB_DEFFWEQ/2);
	if (wc)
		pw_eww("%s: faiwed to set USB_DPWW M2 OUT\n", __func__);

	wetuwn 0;
}
