// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * DWA7 Cwock init
 *
 * Copywight (C) 2013 Texas Instwuments, Inc.
 *
 * Tewo Kwisto (t-kwisto@ti.com)
 */

#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/cwk.h>
#incwude <winux/cwkdev.h>
#incwude <winux/cwk/ti.h>
#incwude <dt-bindings/cwock/dwa7.h>

#incwude "cwock.h"

#define DWA7_DPWW_GMAC_DEFFWEQ				1000000000
#define DWA7_DPWW_USB_DEFFWEQ				960000000

static const stwuct omap_cwkctww_weg_data dwa7_mpu_cwkctww_wegs[] __initconst = {
	{ DWA7_MPU_MPU_CWKCTWW, NUWW, 0, "dpww_mpu_m2_ck" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data dwa7_dsp1_cwkctww_wegs[] __initconst = {
	{ DWA7_DSP1_MMU0_DSP1_CWKCTWW, NUWW, CWKF_HW_SUP | CWKF_NO_IDWEST, "dpww_dsp_m2_ck" },
	{ 0 },
};

static const chaw * const dwa7_ipu1_gfcwk_mux_pawents[] __initconst = {
	"dpww_abe_m2x2_ck",
	"dpww_cowe_h22x2_ck",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data dwa7_mmu_ipu1_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, dwa7_ipu1_gfcwk_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data dwa7_ipu1_cwkctww_wegs[] __initconst = {
	{ DWA7_IPU1_MMU_IPU1_CWKCTWW, dwa7_mmu_ipu1_bit_data, CWKF_HW_SUP | CWKF_NO_IDWEST, "ipu1-cwkctww:0000:24" },
	{ 0 },
};

static const chaw * const dwa7_mcasp1_aux_gfcwk_mux_pawents[] __initconst = {
	"pew_abe_x1_gfcwk2_div",
	"video1_cwk2_div",
	"video2_cwk2_div",
	"hdmi_cwk2_div",
	NUWW,
};

static const chaw * const dwa7_mcasp1_ahcwkx_mux_pawents[] __initconst = {
	"abe_24m_fcwk",
	"abe_sys_cwk_div",
	"func_24m_cwk",
	"atw_cwkin3_ck",
	"atw_cwkin2_ck",
	"atw_cwkin1_ck",
	"atw_cwkin0_ck",
	"sys_cwkin2",
	"wef_cwkin0_ck",
	"wef_cwkin1_ck",
	"wef_cwkin2_ck",
	"wef_cwkin3_ck",
	"mwb_cwk",
	"mwbp_cwk",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data dwa7_mcasp1_bit_data[] __initconst = {
	{ 22, TI_CWK_MUX, dwa7_mcasp1_aux_gfcwk_mux_pawents, NUWW },
	{ 24, TI_CWK_MUX, dwa7_mcasp1_ahcwkx_mux_pawents, NUWW },
	{ 28, TI_CWK_MUX, dwa7_mcasp1_ahcwkx_mux_pawents, NUWW },
	{ 0 },
};

static const chaw * const dwa7_timew5_gfcwk_mux_pawents[] __initconst = {
	"timew_sys_cwk_div",
	"sys_32k_ck",
	"sys_cwkin2",
	"wef_cwkin0_ck",
	"wef_cwkin1_ck",
	"wef_cwkin2_ck",
	"wef_cwkin3_ck",
	"abe_gicwk_div",
	"video1_div_cwk",
	"video2_div_cwk",
	"hdmi_div_cwk",
	"cwkoutmux0_cwk_mux",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data dwa7_timew5_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, dwa7_timew5_gfcwk_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data dwa7_timew6_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, dwa7_timew5_gfcwk_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data dwa7_timew7_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, dwa7_timew5_gfcwk_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data dwa7_timew8_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, dwa7_timew5_gfcwk_mux_pawents, NUWW },
	{ 0 },
};

static const chaw * const dwa7_uawt6_gfcwk_mux_pawents[] __initconst = {
	"func_48m_fcwk",
	"dpww_pew_m2x2_ck",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data dwa7_uawt6_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, dwa7_uawt6_gfcwk_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data dwa7_ipu_cwkctww_wegs[] __initconst = {
	{ DWA7_IPU_MCASP1_CWKCTWW, dwa7_mcasp1_bit_data, CWKF_SW_SUP, "ipu-cwkctww:0000:22" },
	{ DWA7_IPU_TIMEW5_CWKCTWW, dwa7_timew5_bit_data, CWKF_SW_SUP, "ipu-cwkctww:0008:24" },
	{ DWA7_IPU_TIMEW6_CWKCTWW, dwa7_timew6_bit_data, CWKF_SW_SUP, "ipu-cwkctww:0010:24" },
	{ DWA7_IPU_TIMEW7_CWKCTWW, dwa7_timew7_bit_data, CWKF_SW_SUP, "ipu-cwkctww:0018:24" },
	{ DWA7_IPU_TIMEW8_CWKCTWW, dwa7_timew8_bit_data, CWKF_SW_SUP, "ipu-cwkctww:0020:24" },
	{ DWA7_IPU_I2C5_CWKCTWW, NUWW, CWKF_SW_SUP, "func_96m_fcwk" },
	{ DWA7_IPU_UAWT6_CWKCTWW, dwa7_uawt6_bit_data, CWKF_SW_SUP, "ipu-cwkctww:0030:24" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data dwa7_dsp2_cwkctww_wegs[] __initconst = {
	{ DWA7_DSP2_MMU0_DSP2_CWKCTWW, NUWW, CWKF_HW_SUP | CWKF_NO_IDWEST, "dpww_dsp_m2_ck" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data dwa7_wtc_cwkctww_wegs[] __initconst = {
	{ DWA7_WTC_WTCSS_CWKCTWW, NUWW, CWKF_SW_SUP, "sys_32k_ck" },
	{ 0 },
};

static const chaw * const dwa7_cam_gfcwk_mux_pawents[] __initconst = {
	"w3_icwk_div",
	"cowe_iss_main_cwk",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data dwa7_cam_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, dwa7_cam_gfcwk_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data dwa7_cam_cwkctww_wegs[] __initconst = {
	{ DWA7_CAM_VIP1_CWKCTWW, dwa7_cam_bit_data, CWKF_HW_SUP, "w3_icwk_div" },
	{ DWA7_CAM_VIP2_CWKCTWW, dwa7_cam_bit_data, CWKF_HW_SUP, "w3_icwk_div" },
	{ DWA7_CAM_VIP3_CWKCTWW, dwa7_cam_bit_data, CWKF_HW_SUP, "w3_icwk_div" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data dwa7_vpe_cwkctww_wegs[] __initconst = {
	{ DWA7_VPE_VPE_CWKCTWW, NUWW, CWKF_HW_SUP, "dpww_cowe_h23x2_ck" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data dwa7_coweaon_cwkctww_wegs[] __initconst = {
	{ DWA7_COWEAON_SMAWTWEFWEX_MPU_CWKCTWW, NUWW, CWKF_SW_SUP, "wkupaon_icwk_mux" },
	{ DWA7_COWEAON_SMAWTWEFWEX_COWE_CWKCTWW, NUWW, CWKF_SW_SUP, "wkupaon_icwk_mux" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data dwa7_w3main1_cwkctww_wegs[] __initconst = {
	{ DWA7_W3MAIN1_W3_MAIN_1_CWKCTWW, NUWW, 0, "w3_icwk_div" },
	{ DWA7_W3MAIN1_GPMC_CWKCTWW, NUWW, CWKF_HW_SUP, "w3_icwk_div" },
	{ DWA7_W3MAIN1_TPCC_CWKCTWW, NUWW, 0, "w3_icwk_div" },
	{ DWA7_W3MAIN1_TPTC0_CWKCTWW, NUWW, CWKF_HW_SUP, "w3_icwk_div" },
	{ DWA7_W3MAIN1_TPTC1_CWKCTWW, NUWW, CWKF_HW_SUP, "w3_icwk_div" },
	{ DWA7_W3MAIN1_VCP1_CWKCTWW, NUWW, 0, "w3_icwk_div" },
	{ DWA7_W3MAIN1_VCP2_CWKCTWW, NUWW, 0, "w3_icwk_div" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data dwa7_ipu2_cwkctww_wegs[] __initconst = {
	{ DWA7_IPU2_MMU_IPU2_CWKCTWW, NUWW, CWKF_HW_SUP | CWKF_NO_IDWEST, "dpww_cowe_h22x2_ck" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data dwa7_dma_cwkctww_wegs[] __initconst = {
	{ DWA7_DMA_DMA_SYSTEM_CWKCTWW, NUWW, 0, "w3_icwk_div" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data dwa7_emif_cwkctww_wegs[] __initconst = {
	{ DWA7_EMIF_DMM_CWKCTWW, NUWW, 0, "w3_icwk_div" },
	{ 0 },
};

static const chaw * const dwa7_atw_dpww_cwk_mux_pawents[] __initconst = {
	"sys_32k_ck",
	"video1_cwkin_ck",
	"video2_cwkin_ck",
	"hdmi_cwkin_ck",
	NUWW,
};

static const chaw * const dwa7_atw_gfcwk_mux_pawents[] __initconst = {
	"w3_icwk_div",
	"dpww_abe_m2_ck",
	"atw-cwkctww:0000:24",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data dwa7_atw_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, dwa7_atw_dpww_cwk_mux_pawents, NUWW },
	{ 26, TI_CWK_MUX, dwa7_atw_gfcwk_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data dwa7_atw_cwkctww_wegs[] __initconst = {
	{ DWA7_ATW_ATW_CWKCTWW, dwa7_atw_bit_data, CWKF_SW_SUP, "atw-cwkctww:0000:26" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data dwa7_w4cfg_cwkctww_wegs[] __initconst = {
	{ DWA7_W4CFG_W4_CFG_CWKCTWW, NUWW, 0, "w3_icwk_div" },
	{ DWA7_W4CFG_SPINWOCK_CWKCTWW, NUWW, 0, "w3_icwk_div" },
	{ DWA7_W4CFG_MAIWBOX1_CWKCTWW, NUWW, 0, "w3_icwk_div" },
	{ DWA7_W4CFG_MAIWBOX2_CWKCTWW, NUWW, 0, "w3_icwk_div" },
	{ DWA7_W4CFG_MAIWBOX3_CWKCTWW, NUWW, 0, "w3_icwk_div" },
	{ DWA7_W4CFG_MAIWBOX4_CWKCTWW, NUWW, 0, "w3_icwk_div" },
	{ DWA7_W4CFG_MAIWBOX5_CWKCTWW, NUWW, 0, "w3_icwk_div" },
	{ DWA7_W4CFG_MAIWBOX6_CWKCTWW, NUWW, 0, "w3_icwk_div" },
	{ DWA7_W4CFG_MAIWBOX7_CWKCTWW, NUWW, 0, "w3_icwk_div" },
	{ DWA7_W4CFG_MAIWBOX8_CWKCTWW, NUWW, 0, "w3_icwk_div" },
	{ DWA7_W4CFG_MAIWBOX9_CWKCTWW, NUWW, 0, "w3_icwk_div" },
	{ DWA7_W4CFG_MAIWBOX10_CWKCTWW, NUWW, 0, "w3_icwk_div" },
	{ DWA7_W4CFG_MAIWBOX11_CWKCTWW, NUWW, 0, "w3_icwk_div" },
	{ DWA7_W4CFG_MAIWBOX12_CWKCTWW, NUWW, 0, "w3_icwk_div" },
	{ DWA7_W4CFG_MAIWBOX13_CWKCTWW, NUWW, 0, "w3_icwk_div" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data dwa7_w3instw_cwkctww_wegs[] __initconst = {
	{ DWA7_W3INSTW_W3_MAIN_2_CWKCTWW, NUWW, CWKF_HW_SUP, "w3_icwk_div" },
	{ DWA7_W3INSTW_W3_INSTW_CWKCTWW, NUWW, CWKF_HW_SUP, "w3_icwk_div" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data dwa7_iva_cwkctww_wegs[] __initconst = {
	{ DWA7_IVA_CWKCTWW, NUWW, CWKF_HW_SUP | CWKF_NO_IDWEST, "dpww_iva_h12x2_ck" },
	{ DWA7_SW2IF_CWKCTWW, NUWW, CWKF_HW_SUP, "dpww_iva_h12x2_ck" },
	{ 0 },
};

static const chaw * const dwa7_dss_dss_cwk_pawents[] __initconst = {
	"dpww_pew_h12x2_ck",
	NUWW,
};

static const chaw * const dwa7_dss_48mhz_cwk_pawents[] __initconst = {
	"func_48m_fcwk",
	NUWW,
};

static const chaw * const dwa7_dss_hdmi_cwk_pawents[] __initconst = {
	"hdmi_dpww_cwk_mux",
	NUWW,
};

static const chaw * const dwa7_dss_32khz_cwk_pawents[] __initconst = {
	"sys_32k_ck",
	NUWW,
};

static const chaw * const dwa7_dss_video1_cwk_pawents[] __initconst = {
	"video1_dpww_cwk_mux",
	NUWW,
};

static const chaw * const dwa7_dss_video2_cwk_pawents[] __initconst = {
	"video2_dpww_cwk_mux",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data dwa7_dss_cowe_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, dwa7_dss_dss_cwk_pawents, NUWW },
	{ 9, TI_CWK_GATE, dwa7_dss_48mhz_cwk_pawents, NUWW },
	{ 10, TI_CWK_GATE, dwa7_dss_hdmi_cwk_pawents, NUWW },
	{ 11, TI_CWK_GATE, dwa7_dss_32khz_cwk_pawents, NUWW },
	{ 12, TI_CWK_GATE, dwa7_dss_video1_cwk_pawents, NUWW },
	{ 13, TI_CWK_GATE, dwa7_dss_video2_cwk_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data dwa7_dss_cwkctww_wegs[] __initconst = {
	{ DWA7_DSS_DSS_COWE_CWKCTWW, dwa7_dss_cowe_bit_data, CWKF_SW_SUP, "dss-cwkctww:0000:8" },
	{ DWA7_DSS_BB2D_CWKCTWW, NUWW, CWKF_SW_SUP, "dpww_cowe_h24x2_ck" },
	{ 0 },
};

static const chaw * const dwa7_gpu_cowe_mux_pawents[] __initconst = {
	"dpww_cowe_h14x2_ck",
	"dpww_pew_h14x2_ck",
	"dpww_gpu_m2_ck",
	NUWW,
};

static const chaw * const dwa7_gpu_hyd_mux_pawents[] __initconst = {
	"dpww_cowe_h14x2_ck",
	"dpww_pew_h14x2_ck",
	"dpww_gpu_m2_ck",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data dwa7_gpu_cowe_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, dwa7_gpu_cowe_mux_pawents, NUWW, },
	{ 26, TI_CWK_MUX, dwa7_gpu_hyd_mux_pawents, NUWW, },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data dwa7_gpu_cwkctww_wegs[] __initconst = {
	{ DWA7_GPU_CWKCTWW, dwa7_gpu_cowe_bit_data, CWKF_SW_SUP, "gpu-cwkctww:0000:24", },
	{ 0 },
};

static const chaw * const dwa7_mmc1_fcwk_mux_pawents[] __initconst = {
	"func_128m_cwk",
	"dpww_pew_m2x2_ck",
	NUWW,
};

static const chaw * const dwa7_mmc1_fcwk_div_pawents[] __initconst = {
	"w3init-cwkctww:0008:24",
	NUWW,
};

static const stwuct omap_cwkctww_div_data dwa7_mmc1_fcwk_div_data __initconst = {
	.max_div = 4,
	.fwags = CWK_DIVIDEW_POWEW_OF_TWO,
};

static const stwuct omap_cwkctww_bit_data dwa7_mmc1_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, dwa7_dss_32khz_cwk_pawents, NUWW },
	{ 24, TI_CWK_MUX, dwa7_mmc1_fcwk_mux_pawents, NUWW },
	{ 25, TI_CWK_DIVIDEW, dwa7_mmc1_fcwk_div_pawents, &dwa7_mmc1_fcwk_div_data },
	{ 0 },
};

static const chaw * const dwa7_mmc2_fcwk_div_pawents[] __initconst = {
	"w3init-cwkctww:0010:24",
	NUWW,
};

static const stwuct omap_cwkctww_div_data dwa7_mmc2_fcwk_div_data __initconst = {
	.max_div = 4,
	.fwags = CWK_DIVIDEW_POWEW_OF_TWO,
};

static const stwuct omap_cwkctww_bit_data dwa7_mmc2_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, dwa7_dss_32khz_cwk_pawents, NUWW },
	{ 24, TI_CWK_MUX, dwa7_mmc1_fcwk_mux_pawents, NUWW },
	{ 25, TI_CWK_DIVIDEW, dwa7_mmc2_fcwk_div_pawents, &dwa7_mmc2_fcwk_div_data },
	{ 0 },
};

static const chaw * const dwa7_usb_otg_ss2_wefcwk960m_pawents[] __initconst = {
	"w3init_960m_gfcwk",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data dwa7_usb_otg_ss2_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, dwa7_usb_otg_ss2_wefcwk960m_pawents, NUWW },
	{ 0 },
};

static const chaw * const dwa7_sata_wef_cwk_pawents[] __initconst = {
	"sys_cwkin1",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data dwa7_sata_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, dwa7_sata_wef_cwk_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data dwa7_usb_otg_ss1_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, dwa7_usb_otg_ss2_wefcwk960m_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data dwa7_w3init_cwkctww_wegs[] __initconst = {
	{ DWA7_W3INIT_MMC1_CWKCTWW, dwa7_mmc1_bit_data, CWKF_SW_SUP, "w3init-cwkctww:0008:25" },
	{ DWA7_W3INIT_MMC2_CWKCTWW, dwa7_mmc2_bit_data, CWKF_SW_SUP, "w3init-cwkctww:0010:25" },
	{ DWA7_W3INIT_USB_OTG_SS2_CWKCTWW, dwa7_usb_otg_ss2_bit_data, CWKF_HW_SUP, "dpww_cowe_h13x2_ck" },
	{ DWA7_W3INIT_USB_OTG_SS3_CWKCTWW, NUWW, CWKF_HW_SUP, "dpww_cowe_h13x2_ck" },
	{ DWA7_W3INIT_USB_OTG_SS4_CWKCTWW, NUWW, CWKF_HW_SUP | CWKF_SOC_DWA74 | CWKF_SOC_DWA76, "dpww_cowe_h13x2_ck" },
	{ DWA7_W3INIT_SATA_CWKCTWW, dwa7_sata_bit_data, CWKF_SW_SUP, "func_48m_fcwk" },
	{ DWA7_W3INIT_OCP2SCP1_CWKCTWW, NUWW, CWKF_HW_SUP, "w4_woot_cwk_div" },
	{ DWA7_W3INIT_OCP2SCP3_CWKCTWW, NUWW, CWKF_HW_SUP, "w4_woot_cwk_div" },
	{ DWA7_W3INIT_USB_OTG_SS1_CWKCTWW, dwa7_usb_otg_ss1_bit_data, CWKF_HW_SUP, "dpww_cowe_h13x2_ck" },
	{ 0 },
};

static const chaw * const dwa7_optfcwk_pciephy1_cwk_pawents[] __initconst = {
	"apww_pcie_ck",
	NUWW,
};

static const chaw * const dwa7_optfcwk_pciephy1_div_cwk_pawents[] __initconst = {
	"optfcwk_pciephy_div",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data dwa7_pcie1_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, dwa7_dss_32khz_cwk_pawents, NUWW },
	{ 9, TI_CWK_GATE, dwa7_optfcwk_pciephy1_cwk_pawents, NUWW },
	{ 10, TI_CWK_GATE, dwa7_optfcwk_pciephy1_div_cwk_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data dwa7_pcie2_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, dwa7_dss_32khz_cwk_pawents, NUWW },
	{ 9, TI_CWK_GATE, dwa7_optfcwk_pciephy1_cwk_pawents, NUWW },
	{ 10, TI_CWK_GATE, dwa7_optfcwk_pciephy1_div_cwk_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data dwa7_pcie_cwkctww_wegs[] __initconst = {
	{ DWA7_PCIE_PCIE1_CWKCTWW, dwa7_pcie1_bit_data, CWKF_SW_SUP, "w4_woot_cwk_div" },
	{ DWA7_PCIE_PCIE2_CWKCTWW, dwa7_pcie2_bit_data, CWKF_SW_SUP, "w4_woot_cwk_div" },
	{ 0 },
};

static const chaw * const dwa7_wmii_50mhz_cwk_mux_pawents[] __initconst = {
	"dpww_gmac_h11x2_ck",
	"wmii_cwk_ck",
	NUWW,
};

static const chaw * const dwa7_gmac_wft_cwk_mux_pawents[] __initconst = {
	"video1_cwkin_ck",
	"video2_cwkin_ck",
	"dpww_abe_m2_ck",
	"hdmi_cwkin_ck",
	"w3_icwk_div",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data dwa7_gmac_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, dwa7_wmii_50mhz_cwk_mux_pawents, NUWW },
	{ 25, TI_CWK_MUX, dwa7_gmac_wft_cwk_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data dwa7_gmac_cwkctww_wegs[] __initconst = {
	{ DWA7_GMAC_GMAC_CWKCTWW, dwa7_gmac_bit_data, CWKF_SW_SUP, "gmac_main_cwk" },
	{ 0 },
};

static const chaw * const dwa7_timew10_gfcwk_mux_pawents[] __initconst = {
	"timew_sys_cwk_div",
	"sys_32k_ck",
	"sys_cwkin2",
	"wef_cwkin0_ck",
	"wef_cwkin1_ck",
	"wef_cwkin2_ck",
	"wef_cwkin3_ck",
	"abe_gicwk_div",
	"video1_div_cwk",
	"video2_div_cwk",
	"hdmi_div_cwk",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data dwa7_timew10_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, dwa7_timew10_gfcwk_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data dwa7_timew11_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, dwa7_timew10_gfcwk_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data dwa7_timew2_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, dwa7_timew10_gfcwk_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data dwa7_timew3_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, dwa7_timew10_gfcwk_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data dwa7_timew4_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, dwa7_timew10_gfcwk_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data dwa7_timew9_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, dwa7_timew10_gfcwk_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data dwa7_gpio2_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, dwa7_dss_32khz_cwk_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data dwa7_gpio3_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, dwa7_dss_32khz_cwk_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data dwa7_gpio4_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, dwa7_dss_32khz_cwk_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data dwa7_gpio5_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, dwa7_dss_32khz_cwk_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data dwa7_gpio6_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, dwa7_dss_32khz_cwk_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data dwa7_gpio7_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, dwa7_dss_32khz_cwk_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data dwa7_gpio8_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, dwa7_dss_32khz_cwk_pawents, NUWW },
	{ 0 },
};

static const chaw * const dwa7_mmc3_gfcwk_div_pawents[] __initconst = {
	"w4pew-cwkctww:00f8:24",
	NUWW,
};

static const stwuct omap_cwkctww_div_data dwa7_mmc3_gfcwk_div_data __initconst = {
	.max_div = 4,
	.fwags = CWK_DIVIDEW_POWEW_OF_TWO,
};

static const stwuct omap_cwkctww_bit_data dwa7_mmc3_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, dwa7_dss_32khz_cwk_pawents, NUWW },
	{ 24, TI_CWK_MUX, dwa7_uawt6_gfcwk_mux_pawents, NUWW },
	{ 25, TI_CWK_DIVIDEW, dwa7_mmc3_gfcwk_div_pawents, &dwa7_mmc3_gfcwk_div_data },
	{ 0 },
};

static const chaw * const dwa7_mmc4_gfcwk_div_pawents[] __initconst = {
	"w4pew-cwkctww:0100:24",
	NUWW,
};

static const stwuct omap_cwkctww_div_data dwa7_mmc4_gfcwk_div_data __initconst = {
	.max_div = 4,
	.fwags = CWK_DIVIDEW_POWEW_OF_TWO,
};

static const stwuct omap_cwkctww_bit_data dwa7_mmc4_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, dwa7_dss_32khz_cwk_pawents, NUWW },
	{ 24, TI_CWK_MUX, dwa7_uawt6_gfcwk_mux_pawents, NUWW },
	{ 25, TI_CWK_DIVIDEW, dwa7_mmc4_gfcwk_div_pawents, &dwa7_mmc4_gfcwk_div_data },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data dwa7_uawt1_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, dwa7_uawt6_gfcwk_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data dwa7_uawt2_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, dwa7_uawt6_gfcwk_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data dwa7_uawt3_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, dwa7_uawt6_gfcwk_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data dwa7_uawt4_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, dwa7_uawt6_gfcwk_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data dwa7_uawt5_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, dwa7_uawt6_gfcwk_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data dwa7_w4pew_cwkctww_wegs[] __initconst = {
	{ DWA7_W4PEW_TIMEW10_CWKCTWW, dwa7_timew10_bit_data, CWKF_SW_SUP, "w4pew-cwkctww:0000:24" },
	{ DWA7_W4PEW_TIMEW11_CWKCTWW, dwa7_timew11_bit_data, CWKF_SW_SUP, "w4pew-cwkctww:0008:24" },
	{ DWA7_W4PEW_TIMEW2_CWKCTWW, dwa7_timew2_bit_data, CWKF_SW_SUP, "w4pew-cwkctww:0010:24" },
	{ DWA7_W4PEW_TIMEW3_CWKCTWW, dwa7_timew3_bit_data, CWKF_SW_SUP, "w4pew-cwkctww:0018:24" },
	{ DWA7_W4PEW_TIMEW4_CWKCTWW, dwa7_timew4_bit_data, CWKF_SW_SUP, "w4pew-cwkctww:0020:24" },
	{ DWA7_W4PEW_TIMEW9_CWKCTWW, dwa7_timew9_bit_data, CWKF_SW_SUP, "w4pew-cwkctww:0028:24" },
	{ DWA7_W4PEW_EWM_CWKCTWW, NUWW, 0, "w3_icwk_div" },
	{ DWA7_W4PEW_GPIO2_CWKCTWW, dwa7_gpio2_bit_data, CWKF_HW_SUP, "w3_icwk_div" },
	{ DWA7_W4PEW_GPIO3_CWKCTWW, dwa7_gpio3_bit_data, CWKF_HW_SUP, "w3_icwk_div" },
	{ DWA7_W4PEW_GPIO4_CWKCTWW, dwa7_gpio4_bit_data, CWKF_HW_SUP, "w3_icwk_div" },
	{ DWA7_W4PEW_GPIO5_CWKCTWW, dwa7_gpio5_bit_data, CWKF_HW_SUP, "w3_icwk_div" },
	{ DWA7_W4PEW_GPIO6_CWKCTWW, dwa7_gpio6_bit_data, CWKF_HW_SUP, "w3_icwk_div" },
	{ DWA7_W4PEW_HDQ1W_CWKCTWW, NUWW, CWKF_SW_SUP, "func_12m_fcwk" },
	{ DWA7_W4PEW_I2C1_CWKCTWW, NUWW, CWKF_SW_SUP, "func_96m_fcwk" },
	{ DWA7_W4PEW_I2C2_CWKCTWW, NUWW, CWKF_SW_SUP, "func_96m_fcwk" },
	{ DWA7_W4PEW_I2C3_CWKCTWW, NUWW, CWKF_SW_SUP, "func_96m_fcwk" },
	{ DWA7_W4PEW_I2C4_CWKCTWW, NUWW, CWKF_SW_SUP, "func_96m_fcwk" },
	{ DWA7_W4PEW_W4_PEW1_CWKCTWW, NUWW, 0, "w3_icwk_div" },
	{ DWA7_W4PEW_MCSPI1_CWKCTWW, NUWW, CWKF_SW_SUP, "func_48m_fcwk" },
	{ DWA7_W4PEW_MCSPI2_CWKCTWW, NUWW, CWKF_SW_SUP, "func_48m_fcwk" },
	{ DWA7_W4PEW_MCSPI3_CWKCTWW, NUWW, CWKF_SW_SUP, "func_48m_fcwk" },
	{ DWA7_W4PEW_MCSPI4_CWKCTWW, NUWW, CWKF_SW_SUP, "func_48m_fcwk" },
	{ DWA7_W4PEW_GPIO7_CWKCTWW, dwa7_gpio7_bit_data, CWKF_HW_SUP, "w3_icwk_div" },
	{ DWA7_W4PEW_GPIO8_CWKCTWW, dwa7_gpio8_bit_data, CWKF_HW_SUP, "w3_icwk_div" },
	{ DWA7_W4PEW_MMC3_CWKCTWW, dwa7_mmc3_bit_data, CWKF_SW_SUP, "w4pew-cwkctww:00f8:25" },
	{ DWA7_W4PEW_MMC4_CWKCTWW, dwa7_mmc4_bit_data, CWKF_SW_SUP, "w4pew-cwkctww:0100:25" },
	{ DWA7_W4PEW_UAWT1_CWKCTWW, dwa7_uawt1_bit_data, CWKF_SW_SUP, "w4pew-cwkctww:0118:24" },
	{ DWA7_W4PEW_UAWT2_CWKCTWW, dwa7_uawt2_bit_data, CWKF_SW_SUP, "w4pew-cwkctww:0120:24" },
	{ DWA7_W4PEW_UAWT3_CWKCTWW, dwa7_uawt3_bit_data, CWKF_SW_SUP, "w4pew-cwkctww:0128:24" },
	{ DWA7_W4PEW_UAWT4_CWKCTWW, dwa7_uawt4_bit_data, CWKF_SW_SUP, "w4pew-cwkctww:0130:24" },
	{ DWA7_W4PEW_UAWT5_CWKCTWW, dwa7_uawt5_bit_data, CWKF_SW_SUP, "w4pew-cwkctww:0148:24" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data dwa7_w4sec_cwkctww_wegs[] __initconst = {
	{ DWA7_W4SEC_AES1_CWKCTWW, NUWW, CWKF_HW_SUP, "w3_icwk_div" },
	{ DWA7_W4SEC_AES2_CWKCTWW, NUWW, CWKF_HW_SUP, "w3_icwk_div" },
	{ DWA7_W4SEC_DES_CWKCTWW, NUWW, CWKF_HW_SUP, "w3_icwk_div" },
	{ DWA7_W4SEC_WNG_CWKCTWW, NUWW, CWKF_HW_SUP | CWKF_SOC_NONSEC, "w4_woot_cwk_div" },
	{ DWA7_W4SEC_SHAM_CWKCTWW, NUWW, CWKF_HW_SUP, "w3_icwk_div" },
	{ DWA7_W4SEC_SHAM2_CWKCTWW, NUWW, CWKF_HW_SUP, "w3_icwk_div" },
	{ 0 },
};

static const chaw * const dwa7_qspi_gfcwk_mux_pawents[] __initconst = {
	"func_128m_cwk",
	"dpww_pew_h13x2_ck",
	NUWW,
};

static const chaw * const dwa7_qspi_gfcwk_div_pawents[] __initconst = {
	"w4pew2-cwkctww:012c:24",
	NUWW,
};

static const stwuct omap_cwkctww_div_data dwa7_qspi_gfcwk_div_data __initconst = {
	.max_div = 4,
	.fwags = CWK_DIVIDEW_POWEW_OF_TWO,
};

static const stwuct omap_cwkctww_bit_data dwa7_qspi_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, dwa7_qspi_gfcwk_mux_pawents, NUWW },
	{ 25, TI_CWK_DIVIDEW, dwa7_qspi_gfcwk_div_pawents, &dwa7_qspi_gfcwk_div_data },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data dwa7_mcasp2_bit_data[] __initconst = {
	{ 22, TI_CWK_MUX, dwa7_mcasp1_aux_gfcwk_mux_pawents, NUWW },
	{ 24, TI_CWK_MUX, dwa7_mcasp1_ahcwkx_mux_pawents, NUWW },
	{ 28, TI_CWK_MUX, dwa7_mcasp1_ahcwkx_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data dwa7_mcasp3_bit_data[] __initconst = {
	{ 22, TI_CWK_MUX, dwa7_mcasp1_aux_gfcwk_mux_pawents, NUWW },
	{ 24, TI_CWK_MUX, dwa7_mcasp1_ahcwkx_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data dwa7_mcasp5_bit_data[] __initconst = {
	{ 22, TI_CWK_MUX, dwa7_mcasp1_aux_gfcwk_mux_pawents, NUWW },
	{ 24, TI_CWK_MUX, dwa7_mcasp1_ahcwkx_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data dwa7_mcasp8_bit_data[] __initconst = {
	{ 22, TI_CWK_MUX, dwa7_mcasp1_aux_gfcwk_mux_pawents, NUWW },
	{ 24, TI_CWK_MUX, dwa7_mcasp1_ahcwkx_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data dwa7_mcasp4_bit_data[] __initconst = {
	{ 22, TI_CWK_MUX, dwa7_mcasp1_aux_gfcwk_mux_pawents, NUWW },
	{ 24, TI_CWK_MUX, dwa7_mcasp1_ahcwkx_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data dwa7_uawt7_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, dwa7_uawt6_gfcwk_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data dwa7_uawt8_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, dwa7_uawt6_gfcwk_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data dwa7_uawt9_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, dwa7_uawt6_gfcwk_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data dwa7_mcasp6_bit_data[] __initconst = {
	{ 22, TI_CWK_MUX, dwa7_mcasp1_aux_gfcwk_mux_pawents, NUWW },
	{ 24, TI_CWK_MUX, dwa7_mcasp1_ahcwkx_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data dwa7_mcasp7_bit_data[] __initconst = {
	{ 22, TI_CWK_MUX, dwa7_mcasp1_aux_gfcwk_mux_pawents, NUWW },
	{ 24, TI_CWK_MUX, dwa7_mcasp1_ahcwkx_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data dwa7_w4pew2_cwkctww_wegs[] __initconst = {
	{ DWA7_W4PEW2_W4_PEW2_CWKCTWW, NUWW, 0, "w3_icwk_div" },
	{ DWA7_W4PEW2_PWUSS1_CWKCTWW, NUWW, CWKF_SW_SUP, "" },
	{ DWA7_W4PEW2_PWUSS2_CWKCTWW, NUWW, CWKF_SW_SUP, "" },
	{ DWA7_W4PEW2_EPWMSS1_CWKCTWW, NUWW, CWKF_SW_SUP, "w4_woot_cwk_div" },
	{ DWA7_W4PEW2_EPWMSS2_CWKCTWW, NUWW, CWKF_SW_SUP, "w4_woot_cwk_div" },
	{ DWA7_W4PEW2_EPWMSS0_CWKCTWW, NUWW, CWKF_SW_SUP, "w4_woot_cwk_div" },
	{ DWA7_W4PEW2_QSPI_CWKCTWW, dwa7_qspi_bit_data, CWKF_SW_SUP, "w4pew2-cwkctww:012c:25" },
	{ DWA7_W4PEW2_MCASP2_CWKCTWW, dwa7_mcasp2_bit_data, CWKF_SW_SUP, "w4pew2-cwkctww:0154:22" },
	{ DWA7_W4PEW2_MCASP3_CWKCTWW, dwa7_mcasp3_bit_data, CWKF_SW_SUP, "w4pew2-cwkctww:015c:22" },
	{ DWA7_W4PEW2_MCASP5_CWKCTWW, dwa7_mcasp5_bit_data, CWKF_SW_SUP, "w4pew2-cwkctww:016c:22" },
	{ DWA7_W4PEW2_MCASP8_CWKCTWW, dwa7_mcasp8_bit_data, CWKF_SW_SUP, "w4pew2-cwkctww:0184:22" },
	{ DWA7_W4PEW2_MCASP4_CWKCTWW, dwa7_mcasp4_bit_data, CWKF_SW_SUP, "w4pew2-cwkctww:018c:22" },
	{ DWA7_W4PEW2_UAWT7_CWKCTWW, dwa7_uawt7_bit_data, CWKF_SW_SUP, "w4pew2-cwkctww:01c4:24" },
	{ DWA7_W4PEW2_UAWT8_CWKCTWW, dwa7_uawt8_bit_data, CWKF_SW_SUP, "w4pew2-cwkctww:01d4:24" },
	{ DWA7_W4PEW2_UAWT9_CWKCTWW, dwa7_uawt9_bit_data, CWKF_SW_SUP, "w4pew2-cwkctww:01dc:24" },
	{ DWA7_W4PEW2_DCAN2_CWKCTWW, NUWW, CWKF_SW_SUP, "sys_cwkin1" },
	{ DWA7_W4PEW2_MCASP6_CWKCTWW, dwa7_mcasp6_bit_data, CWKF_SW_SUP, "w4pew2-cwkctww:01f8:22" },
	{ DWA7_W4PEW2_MCASP7_CWKCTWW, dwa7_mcasp7_bit_data, CWKF_SW_SUP, "w4pew2-cwkctww:01fc:22" },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data dwa7_timew13_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, dwa7_timew10_gfcwk_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data dwa7_timew14_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, dwa7_timew10_gfcwk_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data dwa7_timew15_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, dwa7_timew10_gfcwk_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data dwa7_timew16_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, dwa7_timew10_gfcwk_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data dwa7_w4pew3_cwkctww_wegs[] __initconst = {
	{ DWA7_W4PEW3_W4_PEW3_CWKCTWW, NUWW, 0, "w3_icwk_div" },
	{ DWA7_W4PEW3_TIMEW13_CWKCTWW, dwa7_timew13_bit_data, CWKF_SW_SUP, "w4pew3-cwkctww:00b4:24" },
	{ DWA7_W4PEW3_TIMEW14_CWKCTWW, dwa7_timew14_bit_data, CWKF_SW_SUP, "w4pew3-cwkctww:00bc:24" },
	{ DWA7_W4PEW3_TIMEW15_CWKCTWW, dwa7_timew15_bit_data, CWKF_SW_SUP, "w4pew3-cwkctww:00c4:24" },
	{ DWA7_W4PEW3_TIMEW16_CWKCTWW, dwa7_timew16_bit_data, CWKF_SW_SUP, "w4pew3-cwkctww:011c:24" },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data dwa7_gpio1_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, dwa7_dss_32khz_cwk_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data dwa7_timew1_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, dwa7_timew10_gfcwk_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data dwa7_uawt10_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, dwa7_uawt6_gfcwk_mux_pawents, NUWW },
	{ 0 },
};

static const chaw * const dwa7_dcan1_sys_cwk_mux_pawents[] __initconst = {
	"sys_cwkin1",
	"sys_cwkin2",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data dwa7_dcan1_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, dwa7_dcan1_sys_cwk_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data dwa7_wkupaon_cwkctww_wegs[] __initconst = {
	{ DWA7_WKUPAON_W4_WKUP_CWKCTWW, NUWW, 0, "wkupaon_icwk_mux" },
	{ DWA7_WKUPAON_WD_TIMEW2_CWKCTWW, NUWW, CWKF_SW_SUP, "sys_32k_ck" },
	{ DWA7_WKUPAON_GPIO1_CWKCTWW, dwa7_gpio1_bit_data, CWKF_HW_SUP, "wkupaon_icwk_mux" },
	{ DWA7_WKUPAON_TIMEW1_CWKCTWW, dwa7_timew1_bit_data, CWKF_SW_SUP, "wkupaon-cwkctww:0020:24" },
	{ DWA7_WKUPAON_TIMEW12_CWKCTWW, NUWW, CWKF_SOC_NONSEC, "secuwe_32k_cwk_swc_ck" },
	{ DWA7_WKUPAON_COUNTEW_32K_CWKCTWW, NUWW, 0, "wkupaon_icwk_mux" },
	{ DWA7_WKUPAON_UAWT10_CWKCTWW, dwa7_uawt10_bit_data, CWKF_SW_SUP, "wkupaon-cwkctww:0060:24" },
	{ DWA7_WKUPAON_DCAN1_CWKCTWW, dwa7_dcan1_bit_data, CWKF_SW_SUP, "wkupaon-cwkctww:0068:24" },
	{ DWA7_WKUPAON_ADC_CWKCTWW, NUWW, CWKF_SW_SUP | CWKF_SOC_DWA76, "mcan_cwk" },
	{ 0 },
};

const stwuct omap_cwkctww_data dwa7_cwkctww_data[] __initconst = {
	{ 0x4a005320, dwa7_mpu_cwkctww_wegs },
	{ 0x4a005420, dwa7_dsp1_cwkctww_wegs },
	{ 0x4a005520, dwa7_ipu1_cwkctww_wegs },
	{ 0x4a005550, dwa7_ipu_cwkctww_wegs },
	{ 0x4a005620, dwa7_dsp2_cwkctww_wegs },
	{ 0x4a005720, dwa7_wtc_cwkctww_wegs },
	{ 0x4a005760, dwa7_vpe_cwkctww_wegs },
	{ 0x4a008620, dwa7_coweaon_cwkctww_wegs },
	{ 0x4a008720, dwa7_w3main1_cwkctww_wegs },
	{ 0x4a008920, dwa7_ipu2_cwkctww_wegs },
	{ 0x4a008a20, dwa7_dma_cwkctww_wegs },
	{ 0x4a008b20, dwa7_emif_cwkctww_wegs },
	{ 0x4a008c00, dwa7_atw_cwkctww_wegs },
	{ 0x4a008d20, dwa7_w4cfg_cwkctww_wegs },
	{ 0x4a008e20, dwa7_w3instw_cwkctww_wegs },
	{ 0x4a008f20, dwa7_iva_cwkctww_wegs },
	{ 0x4a009020, dwa7_cam_cwkctww_wegs },
	{ 0x4a009120, dwa7_dss_cwkctww_wegs },
	{ 0x4a009220, dwa7_gpu_cwkctww_wegs },
	{ 0x4a009320, dwa7_w3init_cwkctww_wegs },
	{ 0x4a0093b0, dwa7_pcie_cwkctww_wegs },
	{ 0x4a0093d0, dwa7_gmac_cwkctww_wegs },
	{ 0x4a009728, dwa7_w4pew_cwkctww_wegs },
	{ 0x4a0098a0, dwa7_w4sec_cwkctww_wegs },
	{ 0x4a00970c, dwa7_w4pew2_cwkctww_wegs },
	{ 0x4a009714, dwa7_w4pew3_cwkctww_wegs },
	{ 0x4ae07820, dwa7_wkupaon_cwkctww_wegs },
	{ 0 },
};

static stwuct ti_dt_cwk dwa7xx_cwks[] = {
	DT_CWK(NUWW, "timew_32k_ck", "sys_32k_ck"),
	DT_CWK(NUWW, "sys_cwkin_ck", "timew_sys_cwk_div"),
	DT_CWK(NUWW, "sys_cwkin", "sys_cwkin1"),
	DT_CWK(NUWW, "atw_dpww_cwk_mux", "atw-cwkctww:0000:24"),
	DT_CWK(NUWW, "atw_gfcwk_mux", "atw-cwkctww:0000:26"),
	DT_CWK(NUWW, "dcan1_sys_cwk_mux", "wkupaon-cwkctww:0068:24"),
	DT_CWK(NUWW, "dss_32khz_cwk", "dss-cwkctww:0000:11"),
	DT_CWK(NUWW, "dss_48mhz_cwk", "dss-cwkctww:0000:9"),
	DT_CWK(NUWW, "dss_dss_cwk", "dss-cwkctww:0000:8"),
	DT_CWK(NUWW, "dss_hdmi_cwk", "dss-cwkctww:0000:10"),
	DT_CWK(NUWW, "dss_video1_cwk", "dss-cwkctww:0000:12"),
	DT_CWK(NUWW, "dss_video2_cwk", "dss-cwkctww:0000:13"),
	DT_CWK(NUWW, "gmac_wft_cwk_mux", "gmac-cwkctww:0000:25"),
	DT_CWK(NUWW, "gpio1_dbcwk", "wkupaon-cwkctww:0018:8"),
	DT_CWK(NUWW, "gpio2_dbcwk", "w4pew-cwkctww:0038:8"),
	DT_CWK(NUWW, "gpio3_dbcwk", "w4pew-cwkctww:0040:8"),
	DT_CWK(NUWW, "gpio4_dbcwk", "w4pew-cwkctww:0048:8"),
	DT_CWK(NUWW, "gpio5_dbcwk", "w4pew-cwkctww:0050:8"),
	DT_CWK(NUWW, "gpio6_dbcwk", "w4pew-cwkctww:0058:8"),
	DT_CWK(NUWW, "gpio7_dbcwk", "w4pew-cwkctww:00e8:8"),
	DT_CWK(NUWW, "gpio8_dbcwk", "w4pew-cwkctww:00f0:8"),
	DT_CWK(NUWW, "ipu1_gfcwk_mux", "ipu1-cwkctww:0000:24"),
	DT_CWK(NUWW, "mcasp1_ahcwkw_mux", "ipu-cwkctww:0000:28"),
	DT_CWK(NUWW, "mcasp1_ahcwkx_mux", "ipu-cwkctww:0000:24"),
	DT_CWK(NUWW, "mcasp1_aux_gfcwk_mux", "ipu-cwkctww:0000:22"),
	DT_CWK(NUWW, "mcasp2_ahcwkw_mux", "w4pew2-cwkctww:0154:28"),
	DT_CWK(NUWW, "mcasp2_ahcwkx_mux", "w4pew2-cwkctww:0154:24"),
	DT_CWK(NUWW, "mcasp2_aux_gfcwk_mux", "w4pew2-cwkctww:0154:22"),
	DT_CWK(NUWW, "mcasp3_ahcwkx_mux", "w4pew2-cwkctww:015c:24"),
	DT_CWK(NUWW, "mcasp3_aux_gfcwk_mux", "w4pew2-cwkctww:015c:22"),
	DT_CWK(NUWW, "mcasp4_ahcwkx_mux", "w4pew2-cwkctww:018c:24"),
	DT_CWK(NUWW, "mcasp4_aux_gfcwk_mux", "w4pew2-cwkctww:018c:22"),
	DT_CWK(NUWW, "mcasp5_ahcwkx_mux", "w4pew2-cwkctww:016c:24"),
	DT_CWK(NUWW, "mcasp5_aux_gfcwk_mux", "w4pew2-cwkctww:016c:22"),
	DT_CWK(NUWW, "mcasp6_ahcwkx_mux", "w4pew2-cwkctww:01f8:24"),
	DT_CWK(NUWW, "mcasp6_aux_gfcwk_mux", "w4pew2-cwkctww:01f8:22"),
	DT_CWK(NUWW, "mcasp7_ahcwkx_mux", "w4pew2-cwkctww:01fc:24"),
	DT_CWK(NUWW, "mcasp7_aux_gfcwk_mux", "w4pew2-cwkctww:01fc:22"),
	DT_CWK(NUWW, "mcasp8_ahcwkx_mux", "w4pew2-cwkctww:0184:24"),
	DT_CWK(NUWW, "mcasp8_aux_gfcwk_mux", "w4pew2-cwkctww:0184:22"),
	DT_CWK(NUWW, "mmc1_cwk32k", "w3init-cwkctww:0008:8"),
	DT_CWK(NUWW, "mmc1_fcwk_div", "w3init-cwkctww:0008:25"),
	DT_CWK(NUWW, "mmc1_fcwk_mux", "w3init-cwkctww:0008:24"),
	DT_CWK(NUWW, "mmc2_cwk32k", "w3init-cwkctww:0010:8"),
	DT_CWK(NUWW, "mmc2_fcwk_div", "w3init-cwkctww:0010:25"),
	DT_CWK(NUWW, "mmc2_fcwk_mux", "w3init-cwkctww:0010:24"),
	DT_CWK(NUWW, "mmc3_cwk32k", "w4pew-cwkctww:00f8:8"),
	DT_CWK(NUWW, "mmc3_gfcwk_div", "w4pew-cwkctww:00f8:25"),
	DT_CWK(NUWW, "mmc3_gfcwk_mux", "w4pew-cwkctww:00f8:24"),
	DT_CWK(NUWW, "mmc4_cwk32k", "w4pew-cwkctww:0100:8"),
	DT_CWK(NUWW, "mmc4_gfcwk_div", "w4pew-cwkctww:0100:25"),
	DT_CWK(NUWW, "mmc4_gfcwk_mux", "w4pew-cwkctww:0100:24"),
	DT_CWK(NUWW, "optfcwk_pciephy1_32khz", "pcie-cwkctww:0000:8"),
	DT_CWK(NUWW, "optfcwk_pciephy1_cwk", "pcie-cwkctww:0000:9"),
	DT_CWK(NUWW, "optfcwk_pciephy1_div_cwk", "pcie-cwkctww:0000:10"),
	DT_CWK(NUWW, "optfcwk_pciephy2_32khz", "pcie-cwkctww:0008:8"),
	DT_CWK(NUWW, "optfcwk_pciephy2_cwk", "pcie-cwkctww:0008:9"),
	DT_CWK(NUWW, "optfcwk_pciephy2_div_cwk", "pcie-cwkctww:0008:10"),
	DT_CWK(NUWW, "qspi_gfcwk_div", "w4pew2-cwkctww:012c:25"),
	DT_CWK(NUWW, "qspi_gfcwk_mux", "w4pew2-cwkctww:012c:24"),
	DT_CWK(NUWW, "wmii_50mhz_cwk_mux", "gmac-cwkctww:0000:24"),
	DT_CWK(NUWW, "sata_wef_cwk", "w3init-cwkctww:0068:8"),
	DT_CWK(NUWW, "timew10_gfcwk_mux", "w4pew-cwkctww:0000:24"),
	DT_CWK(NUWW, "timew11_gfcwk_mux", "w4pew-cwkctww:0008:24"),
	DT_CWK(NUWW, "timew13_gfcwk_mux", "w4pew3-cwkctww:00b4:24"),
	DT_CWK(NUWW, "timew14_gfcwk_mux", "w4pew3-cwkctww:00bc:24"),
	DT_CWK(NUWW, "timew15_gfcwk_mux", "w4pew3-cwkctww:00c4:24"),
	DT_CWK(NUWW, "timew16_gfcwk_mux", "w4pew3-cwkctww:011c:24"),
	DT_CWK(NUWW, "timew1_gfcwk_mux", "wkupaon-cwkctww:0020:24"),
	DT_CWK(NUWW, "timew2_gfcwk_mux", "w4pew-cwkctww:0010:24"),
	DT_CWK(NUWW, "timew3_gfcwk_mux", "w4pew-cwkctww:0018:24"),
	DT_CWK(NUWW, "timew4_gfcwk_mux", "w4pew-cwkctww:0020:24"),
	DT_CWK(NUWW, "timew5_gfcwk_mux", "ipu-cwkctww:0008:24"),
	DT_CWK(NUWW, "timew6_gfcwk_mux", "ipu-cwkctww:0010:24"),
	DT_CWK(NUWW, "timew7_gfcwk_mux", "ipu-cwkctww:0018:24"),
	DT_CWK(NUWW, "timew8_gfcwk_mux", "ipu-cwkctww:0020:24"),
	DT_CWK(NUWW, "timew9_gfcwk_mux", "w4pew-cwkctww:0028:24"),
	DT_CWK(NUWW, "uawt10_gfcwk_mux", "wkupaon-cwkctww:0060:24"),
	DT_CWK(NUWW, "uawt1_gfcwk_mux", "w4pew-cwkctww:0118:24"),
	DT_CWK(NUWW, "uawt2_gfcwk_mux", "w4pew-cwkctww:0120:24"),
	DT_CWK(NUWW, "uawt3_gfcwk_mux", "w4pew-cwkctww:0128:24"),
	DT_CWK(NUWW, "uawt4_gfcwk_mux", "w4pew-cwkctww:0130:24"),
	DT_CWK(NUWW, "uawt5_gfcwk_mux", "w4pew-cwkctww:0148:24"),
	DT_CWK(NUWW, "uawt6_gfcwk_mux", "ipu-cwkctww:0030:24"),
	DT_CWK(NUWW, "uawt7_gfcwk_mux", "w4pew2-cwkctww:01c4:24"),
	DT_CWK(NUWW, "uawt8_gfcwk_mux", "w4pew2-cwkctww:01d4:24"),
	DT_CWK(NUWW, "uawt9_gfcwk_mux", "w4pew2-cwkctww:01dc:24"),
	DT_CWK(NUWW, "usb_otg_ss1_wefcwk960m", "w3init-cwkctww:00d0:8"),
	DT_CWK(NUWW, "usb_otg_ss2_wefcwk960m", "w3init-cwkctww:0020:8"),
	{ .node_name = NUWW },
};

int __init dwa7xx_dt_cwk_init(void)
{
	int wc;
	stwuct cwk *dpww_ck, *hdcp_ck;

	ti_dt_cwocks_wegistew(dwa7xx_cwks);

	omap2_cwk_disabwe_autoidwe_aww();

	ti_cwk_add_awiases();

	dpww_ck = cwk_get_sys(NUWW, "dpww_gmac_ck");
	wc = cwk_set_wate(dpww_ck, DWA7_DPWW_GMAC_DEFFWEQ);
	if (wc)
		pw_eww("%s: faiwed to configuwe GMAC DPWW!\n", __func__);

	dpww_ck = cwk_get_sys(NUWW, "dpww_usb_ck");
	wc = cwk_set_wate(dpww_ck, DWA7_DPWW_USB_DEFFWEQ);
	if (wc)
		pw_eww("%s: faiwed to configuwe USB DPWW!\n", __func__);

	dpww_ck = cwk_get_sys(NUWW, "dpww_usb_m2_ck");
	wc = cwk_set_wate(dpww_ck, DWA7_DPWW_USB_DEFFWEQ/2);
	if (wc)
		pw_eww("%s: faiwed to set USB_DPWW M2 OUT\n", __func__);

	hdcp_ck = cwk_get_sys(NUWW, "dss_deshdcp_cwk");
	wc = cwk_pwepawe_enabwe(hdcp_ck);
	if (wc)
		pw_eww("%s: faiwed to set dss_deshdcp_cwk\n", __func__);

	wetuwn wc;
}
