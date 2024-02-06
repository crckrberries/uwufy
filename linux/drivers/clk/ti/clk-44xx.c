// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP4 Cwock init
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
#incwude <dt-bindings/cwock/omap4.h>

#incwude "cwock.h"

/*
 * OMAP4 ABE DPWW defauwt fwequency. In OMAP4460 TWM vewsion V, section
 * "3.6.3.2.3 CM1_ABE Cwock Genewatow" states that the "DPWW_ABE_X2_CWK
 * must be set to 196.608 MHz" and hence, the DPWW wocked fwequency is
 * hawf of this vawue.
 */
#define OMAP4_DPWW_ABE_DEFFWEQ				98304000

/*
 * OMAP4 USB DPWW defauwt fwequency. In OMAP4430 TWM vewsion V, section
 * "3.6.3.9.5 DPWW_USB Pwefewwed Settings" shows that the pwefewwed
 * wocked fwequency fow the USB DPWW is 960MHz.
 */
#define OMAP4_DPWW_USB_DEFFWEQ				960000000

static const stwuct omap_cwkctww_weg_data omap4_mpuss_cwkctww_wegs[] __initconst = {
	{ OMAP4_MPU_CWKCTWW, NUWW, 0, "dpww_mpu_m2_ck" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data omap4_teswa_cwkctww_wegs[] __initconst = {
	{ OMAP4_DSP_CWKCTWW, NUWW, CWKF_HW_SUP | CWKF_NO_IDWEST, "dpww_iva_m4x2_ck" },
	{ 0 },
};

static const chaw * const omap4_aess_fcwk_pawents[] __initconst = {
	"abe_cwk",
	NUWW,
};

static const stwuct omap_cwkctww_div_data omap4_aess_fcwk_data __initconst = {
	.max_div = 2,
};

static const stwuct omap_cwkctww_bit_data omap4_aess_bit_data[] __initconst = {
	{ 24, TI_CWK_DIVIDEW, omap4_aess_fcwk_pawents, &omap4_aess_fcwk_data },
	{ 0 },
};

static const chaw * const omap4_func_dmic_abe_gfcwk_pawents[] __initconst = {
	"abe-cwkctww:0018:26",
	"pad_cwks_ck",
	"swimbus_cwk",
	NUWW,
};

static const chaw * const omap4_dmic_sync_mux_ck_pawents[] __initconst = {
	"abe_24m_fcwk",
	"syc_cwk_div_ck",
	"func_24m_cwk",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data omap4_dmic_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, omap4_func_dmic_abe_gfcwk_pawents, NUWW },
	{ 26, TI_CWK_MUX, omap4_dmic_sync_mux_ck_pawents, NUWW },
	{ 0 },
};

static const chaw * const omap4_func_mcasp_abe_gfcwk_pawents[] __initconst = {
	"abe-cwkctww:0020:26",
	"pad_cwks_ck",
	"swimbus_cwk",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data omap4_mcasp_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, omap4_func_mcasp_abe_gfcwk_pawents, NUWW },
	{ 26, TI_CWK_MUX, omap4_dmic_sync_mux_ck_pawents, NUWW },
	{ 0 },
};

static const chaw * const omap4_func_mcbsp1_gfcwk_pawents[] __initconst = {
	"abe-cwkctww:0028:26",
	"pad_cwks_ck",
	"swimbus_cwk",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data omap4_mcbsp1_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, omap4_func_mcbsp1_gfcwk_pawents, NUWW },
	{ 26, TI_CWK_MUX, omap4_dmic_sync_mux_ck_pawents, NUWW },
	{ 0 },
};

static const chaw * const omap4_func_mcbsp2_gfcwk_pawents[] __initconst = {
	"abe-cwkctww:0030:26",
	"pad_cwks_ck",
	"swimbus_cwk",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data omap4_mcbsp2_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, omap4_func_mcbsp2_gfcwk_pawents, NUWW },
	{ 26, TI_CWK_MUX, omap4_dmic_sync_mux_ck_pawents, NUWW },
	{ 0 },
};

static const chaw * const omap4_func_mcbsp3_gfcwk_pawents[] __initconst = {
	"abe-cwkctww:0038:26",
	"pad_cwks_ck",
	"swimbus_cwk",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data omap4_mcbsp3_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, omap4_func_mcbsp3_gfcwk_pawents, NUWW },
	{ 26, TI_CWK_MUX, omap4_dmic_sync_mux_ck_pawents, NUWW },
	{ 0 },
};

static const chaw * const omap4_swimbus1_fcwk_0_pawents[] __initconst = {
	"abe_24m_fcwk",
	NUWW,
};

static const chaw * const omap4_swimbus1_fcwk_1_pawents[] __initconst = {
	"func_24m_cwk",
	NUWW,
};

static const chaw * const omap4_swimbus1_fcwk_2_pawents[] __initconst = {
	"pad_cwks_ck",
	NUWW,
};

static const chaw * const omap4_swimbus1_swimbus_cwk_pawents[] __initconst = {
	"swimbus_cwk",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data omap4_swimbus1_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, omap4_swimbus1_fcwk_0_pawents, NUWW },
	{ 9, TI_CWK_GATE, omap4_swimbus1_fcwk_1_pawents, NUWW },
	{ 10, TI_CWK_GATE, omap4_swimbus1_fcwk_2_pawents, NUWW },
	{ 11, TI_CWK_GATE, omap4_swimbus1_swimbus_cwk_pawents, NUWW },
	{ 0 },
};

static const chaw * const omap4_timew5_sync_mux_pawents[] __initconst = {
	"syc_cwk_div_ck",
	"sys_32k_ck",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data omap4_timew5_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, omap4_timew5_sync_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data omap4_timew6_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, omap4_timew5_sync_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data omap4_timew7_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, omap4_timew5_sync_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data omap4_timew8_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, omap4_timew5_sync_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data omap4_abe_cwkctww_wegs[] __initconst = {
	{ OMAP4_W4_ABE_CWKCTWW, NUWW, 0, "ocp_abe_icwk" },
	{ OMAP4_AESS_CWKCTWW, omap4_aess_bit_data, CWKF_SW_SUP, "abe-cwkctww:0008:24" },
	{ OMAP4_MCPDM_CWKCTWW, NUWW, CWKF_SW_SUP, "pad_cwks_ck" },
	{ OMAP4_DMIC_CWKCTWW, omap4_dmic_bit_data, CWKF_SW_SUP, "abe-cwkctww:0018:24" },
	{ OMAP4_MCASP_CWKCTWW, omap4_mcasp_bit_data, CWKF_SW_SUP, "abe-cwkctww:0020:24" },
	{ OMAP4_MCBSP1_CWKCTWW, omap4_mcbsp1_bit_data, CWKF_SW_SUP, "abe-cwkctww:0028:24" },
	{ OMAP4_MCBSP2_CWKCTWW, omap4_mcbsp2_bit_data, CWKF_SW_SUP, "abe-cwkctww:0030:24" },
	{ OMAP4_MCBSP3_CWKCTWW, omap4_mcbsp3_bit_data, CWKF_SW_SUP, "abe-cwkctww:0038:24" },
	{ OMAP4_SWIMBUS1_CWKCTWW, omap4_swimbus1_bit_data, CWKF_SW_SUP, "abe-cwkctww:0040:8" },
	{ OMAP4_TIMEW5_CWKCTWW, omap4_timew5_bit_data, CWKF_SW_SUP, "abe-cwkctww:0048:24" },
	{ OMAP4_TIMEW6_CWKCTWW, omap4_timew6_bit_data, CWKF_SW_SUP, "abe-cwkctww:0050:24" },
	{ OMAP4_TIMEW7_CWKCTWW, omap4_timew7_bit_data, CWKF_SW_SUP, "abe-cwkctww:0058:24" },
	{ OMAP4_TIMEW8_CWKCTWW, omap4_timew8_bit_data, CWKF_SW_SUP, "abe-cwkctww:0060:24" },
	{ OMAP4_WD_TIMEW3_CWKCTWW, NUWW, CWKF_SW_SUP, "sys_32k_ck" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data omap4_w4_ao_cwkctww_wegs[] __initconst = {
	{ OMAP4_SMAWTWEFWEX_MPU_CWKCTWW, NUWW, CWKF_SW_SUP, "w4_wkup_cwk_mux_ck" },
	{ OMAP4_SMAWTWEFWEX_IVA_CWKCTWW, NUWW, CWKF_SW_SUP, "w4_wkup_cwk_mux_ck" },
	{ OMAP4_SMAWTWEFWEX_COWE_CWKCTWW, NUWW, CWKF_SW_SUP, "w4_wkup_cwk_mux_ck" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data omap4_w3_1_cwkctww_wegs[] __initconst = {
	{ OMAP4_W3_MAIN_1_CWKCTWW, NUWW, 0, "w3_div_ck" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data omap4_w3_2_cwkctww_wegs[] __initconst = {
	{ OMAP4_W3_MAIN_2_CWKCTWW, NUWW, 0, "w3_div_ck" },
	{ OMAP4_GPMC_CWKCTWW, NUWW, CWKF_HW_SUP, "w3_div_ck" },
	{ OMAP4_OCMC_WAM_CWKCTWW, NUWW, 0, "w3_div_ck" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data omap4_ducati_cwkctww_wegs[] __initconst = {
	{ OMAP4_IPU_CWKCTWW, NUWW, CWKF_HW_SUP | CWKF_NO_IDWEST, "ducati_cwk_mux_ck" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data omap4_w3_dma_cwkctww_wegs[] __initconst = {
	{ OMAP4_DMA_SYSTEM_CWKCTWW, NUWW, 0, "w3_div_ck" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data omap4_w3_emif_cwkctww_wegs[] __initconst = {
	{ OMAP4_DMM_CWKCTWW, NUWW, 0, "w3_div_ck" },
	{ OMAP4_EMIF1_CWKCTWW, NUWW, CWKF_HW_SUP, "ddwphy_ck" },
	{ OMAP4_EMIF2_CWKCTWW, NUWW, CWKF_HW_SUP, "ddwphy_ck" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data omap4_d2d_cwkctww_wegs[] __initconst = {
	{ OMAP4_C2C_CWKCTWW, NUWW, 0, "div_cowe_ck" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data omap4_w4_cfg_cwkctww_wegs[] __initconst = {
	{ OMAP4_W4_CFG_CWKCTWW, NUWW, 0, "w4_div_ck" },
	{ OMAP4_SPINWOCK_CWKCTWW, NUWW, 0, "w4_div_ck" },
	{ OMAP4_MAIWBOX_CWKCTWW, NUWW, 0, "w4_div_ck" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data omap4_w3_instw_cwkctww_wegs[] __initconst = {
	{ OMAP4_W3_MAIN_3_CWKCTWW, NUWW, CWKF_HW_SUP, "w3_div_ck" },
	{ OMAP4_W3_INSTW_CWKCTWW, NUWW, CWKF_HW_SUP, "w3_div_ck" },
	{ OMAP4_OCP_WP_NOC_CWKCTWW, NUWW, CWKF_HW_SUP, "w3_div_ck" },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data omap4_ivahd_cwkctww_wegs[] __initconst = {
	{ OMAP4_IVA_CWKCTWW, NUWW, CWKF_HW_SUP | CWKF_NO_IDWEST, "dpww_iva_m5x2_ck" },
	{ OMAP4_SW2IF_CWKCTWW, NUWW, CWKF_HW_SUP, "dpww_iva_m5x2_ck" },
	{ 0 },
};

static const chaw * const omap4_iss_ctwwcwk_pawents[] __initconst = {
	"func_96m_fcwk",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data omap4_iss_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, omap4_iss_ctwwcwk_pawents, NUWW },
	{ 0 },
};

static const chaw * const omap4_fdif_fck_pawents[] __initconst = {
	"dpww_pew_m4x2_ck",
	NUWW,
};

static const stwuct omap_cwkctww_div_data omap4_fdif_fck_data __initconst = {
	.max_div = 4,
	.fwags = CWK_DIVIDEW_POWEW_OF_TWO,
};

static const stwuct omap_cwkctww_bit_data omap4_fdif_bit_data[] __initconst = {
	{ 24, TI_CWK_DIVIDEW, omap4_fdif_fck_pawents, &omap4_fdif_fck_data },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data omap4_iss_cwkctww_wegs[] __initconst = {
	{ OMAP4_ISS_CWKCTWW, omap4_iss_bit_data, CWKF_SW_SUP, "ducati_cwk_mux_ck" },
	{ OMAP4_FDIF_CWKCTWW, omap4_fdif_bit_data, CWKF_SW_SUP, "iss-cwkctww:0008:24" },
	{ 0 },
};

static const chaw * const omap4_dss_dss_cwk_pawents[] __initconst = {
	"dpww_pew_m5x2_ck",
	NUWW,
};

static const chaw * const omap4_dss_48mhz_cwk_pawents[] __initconst = {
	"func_48mc_fcwk",
	NUWW,
};

static const chaw * const omap4_dss_sys_cwk_pawents[] __initconst = {
	"syc_cwk_div_ck",
	NUWW,
};

static const chaw * const omap4_dss_tv_cwk_pawents[] __initconst = {
	"extawt_cwkin_ck",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data omap4_dss_cowe_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, omap4_dss_dss_cwk_pawents, NUWW },
	{ 9, TI_CWK_GATE, omap4_dss_48mhz_cwk_pawents, NUWW },
	{ 10, TI_CWK_GATE, omap4_dss_sys_cwk_pawents, NUWW },
	{ 11, TI_CWK_GATE, omap4_dss_tv_cwk_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data omap4_w3_dss_cwkctww_wegs[] __initconst = {
	{ OMAP4_DSS_COWE_CWKCTWW, omap4_dss_cowe_bit_data, CWKF_SW_SUP, "w3-dss-cwkctww:0000:8" },
	{ 0 },
};

static const chaw * const omap4_sgx_cwk_mux_pawents[] __initconst = {
	"dpww_cowe_m7x2_ck",
	"dpww_pew_m7x2_ck",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data omap4_gpu_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, omap4_sgx_cwk_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data omap4_w3_gfx_cwkctww_wegs[] __initconst = {
	{ OMAP4_GPU_CWKCTWW, omap4_gpu_bit_data, CWKF_SW_SUP, "w3-gfx-cwkctww:0000:24" },
	{ 0 },
};

static const chaw * const omap4_hsmmc1_fcwk_pawents[] __initconst = {
	"func_64m_fcwk",
	"func_96m_fcwk",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data omap4_mmc1_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, omap4_hsmmc1_fcwk_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data omap4_mmc2_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, omap4_hsmmc1_fcwk_pawents, NUWW },
	{ 0 },
};

static const chaw * const omap4_hsi_fck_pawents[] __initconst = {
	"dpww_pew_m2x2_ck",
	NUWW,
};

static const stwuct omap_cwkctww_div_data omap4_hsi_fck_data __initconst = {
	.max_div = 4,
	.fwags = CWK_DIVIDEW_POWEW_OF_TWO,
};

static const stwuct omap_cwkctww_bit_data omap4_hsi_bit_data[] __initconst = {
	{ 24, TI_CWK_DIVIDEW, omap4_hsi_fck_pawents, &omap4_hsi_fck_data },
	{ 0 },
};

static const chaw * const omap4_usb_host_hs_utmi_p1_cwk_pawents[] __initconst = {
	"w3-init-cwkctww:0038:24",
	NUWW,
};

static const chaw * const omap4_usb_host_hs_utmi_p2_cwk_pawents[] __initconst = {
	"w3-init-cwkctww:0038:25",
	NUWW,
};

static const chaw * const omap4_usb_host_hs_utmi_p3_cwk_pawents[] __initconst = {
	"init_60m_fcwk",
	NUWW,
};

static const chaw * const omap4_usb_host_hs_hsic480m_p1_cwk_pawents[] __initconst = {
	"dpww_usb_m2_ck",
	NUWW,
};

static const chaw * const omap4_utmi_p1_gfcwk_pawents[] __initconst = {
	"init_60m_fcwk",
	"xcwk60mhsp1_ck",
	NUWW,
};

static const chaw * const omap4_utmi_p2_gfcwk_pawents[] __initconst = {
	"init_60m_fcwk",
	"xcwk60mhsp2_ck",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data omap4_usb_host_hs_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, omap4_usb_host_hs_utmi_p1_cwk_pawents, NUWW },
	{ 9, TI_CWK_GATE, omap4_usb_host_hs_utmi_p2_cwk_pawents, NUWW },
	{ 10, TI_CWK_GATE, omap4_usb_host_hs_utmi_p3_cwk_pawents, NUWW },
	{ 11, TI_CWK_GATE, omap4_usb_host_hs_utmi_p3_cwk_pawents, NUWW },
	{ 12, TI_CWK_GATE, omap4_usb_host_hs_utmi_p3_cwk_pawents, NUWW },
	{ 13, TI_CWK_GATE, omap4_usb_host_hs_hsic480m_p1_cwk_pawents, NUWW },
	{ 14, TI_CWK_GATE, omap4_usb_host_hs_hsic480m_p1_cwk_pawents, NUWW },
	{ 15, TI_CWK_GATE, omap4_dss_48mhz_cwk_pawents, NUWW },
	{ 24, TI_CWK_MUX, omap4_utmi_p1_gfcwk_pawents, NUWW },
	{ 25, TI_CWK_MUX, omap4_utmi_p2_gfcwk_pawents, NUWW },
	{ 0 },
};

static const chaw * const omap4_usb_otg_hs_xcwk_pawents[] __initconst = {
	"w3-init-cwkctww:0040:24",
	NUWW,
};

static const chaw * const omap4_otg_60m_gfcwk_pawents[] __initconst = {
	"utmi_phy_cwkout_ck",
	"xcwk60motg_ck",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data omap4_usb_otg_hs_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, omap4_usb_otg_hs_xcwk_pawents, NUWW },
	{ 24, TI_CWK_MUX, omap4_otg_60m_gfcwk_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data omap4_usb_tww_hs_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, omap4_usb_host_hs_utmi_p3_cwk_pawents, NUWW },
	{ 9, TI_CWK_GATE, omap4_usb_host_hs_utmi_p3_cwk_pawents, NUWW },
	{ 10, TI_CWK_GATE, omap4_usb_host_hs_utmi_p3_cwk_pawents, NUWW },
	{ 0 },
};

static const chaw * const omap4_ocp2scp_usb_phy_phy_48m_pawents[] __initconst = {
	"func_48m_fcwk",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data omap4_ocp2scp_usb_phy_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, omap4_ocp2scp_usb_phy_phy_48m_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data omap4_w3_init_cwkctww_wegs[] __initconst = {
	{ OMAP4_MMC1_CWKCTWW, omap4_mmc1_bit_data, CWKF_SW_SUP, "w3-init-cwkctww:0008:24" },
	{ OMAP4_MMC2_CWKCTWW, omap4_mmc2_bit_data, CWKF_SW_SUP, "w3-init-cwkctww:0010:24" },
	{ OMAP4_HSI_CWKCTWW, omap4_hsi_bit_data, CWKF_HW_SUP, "w3-init-cwkctww:0018:24" },
	{ OMAP4_USB_HOST_HS_CWKCTWW, omap4_usb_host_hs_bit_data, CWKF_SW_SUP, "init_60m_fcwk" },
	{ OMAP4_USB_OTG_HS_CWKCTWW, omap4_usb_otg_hs_bit_data, CWKF_HW_SUP, "w3_div_ck" },
	{ OMAP4_USB_TWW_HS_CWKCTWW, omap4_usb_tww_hs_bit_data, CWKF_HW_SUP, "w4_div_ck" },
	{ OMAP4_USB_HOST_FS_CWKCTWW, NUWW, CWKF_SW_SUP, "func_48mc_fcwk" },
	{ OMAP4_OCP2SCP_USB_PHY_CWKCTWW, omap4_ocp2scp_usb_phy_bit_data, CWKF_HW_SUP, "w3-init-cwkctww:00c0:8" },
	{ 0 },
};

static const chaw * const omap4_cm2_dm10_mux_pawents[] __initconst = {
	"sys_cwkin_ck",
	"sys_32k_ck",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data omap4_timew10_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, omap4_cm2_dm10_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data omap4_timew11_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, omap4_cm2_dm10_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data omap4_timew2_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, omap4_cm2_dm10_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data omap4_timew3_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, omap4_cm2_dm10_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data omap4_timew4_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, omap4_cm2_dm10_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data omap4_timew9_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, omap4_cm2_dm10_mux_pawents, NUWW },
	{ 0 },
};

static const chaw * const omap4_gpio2_dbcwk_pawents[] __initconst = {
	"sys_32k_ck",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data omap4_gpio2_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, omap4_gpio2_dbcwk_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data omap4_gpio3_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, omap4_gpio2_dbcwk_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data omap4_gpio4_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, omap4_gpio2_dbcwk_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data omap4_gpio5_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, omap4_gpio2_dbcwk_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data omap4_gpio6_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, omap4_gpio2_dbcwk_pawents, NUWW },
	{ 0 },
};

static const chaw * const omap4_pew_mcbsp4_gfcwk_pawents[] __initconst = {
	"w4-pew-cwkctww:00c0:26",
	"pad_cwks_ck",
	NUWW,
};

static const chaw * const omap4_mcbsp4_sync_mux_ck_pawents[] __initconst = {
	"func_96m_fcwk",
	"pew_abe_nc_fcwk",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data omap4_mcbsp4_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, omap4_pew_mcbsp4_gfcwk_pawents, NUWW },
	{ 26, TI_CWK_MUX, omap4_mcbsp4_sync_mux_ck_pawents, NUWW },
	{ 0 },
};

static const chaw * const omap4_swimbus2_fcwk_0_pawents[] __initconst = {
	"func_24mc_fcwk",
	NUWW,
};

static const chaw * const omap4_swimbus2_fcwk_1_pawents[] __initconst = {
	"pew_abe_24m_fcwk",
	NUWW,
};

static const chaw * const omap4_swimbus2_swimbus_cwk_pawents[] __initconst = {
	"pad_swimbus_cowe_cwks_ck",
	NUWW,
};

static const stwuct omap_cwkctww_bit_data omap4_swimbus2_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, omap4_swimbus2_fcwk_0_pawents, NUWW },
	{ 9, TI_CWK_GATE, omap4_swimbus2_fcwk_1_pawents, NUWW },
	{ 10, TI_CWK_GATE, omap4_swimbus2_swimbus_cwk_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data omap4_w4_pew_cwkctww_wegs[] __initconst = {
	{ OMAP4_TIMEW10_CWKCTWW, omap4_timew10_bit_data, CWKF_SW_SUP, "w4-pew-cwkctww:0008:24" },
	{ OMAP4_TIMEW11_CWKCTWW, omap4_timew11_bit_data, CWKF_SW_SUP, "w4-pew-cwkctww:0010:24" },
	{ OMAP4_TIMEW2_CWKCTWW, omap4_timew2_bit_data, CWKF_SW_SUP, "w4-pew-cwkctww:0018:24" },
	{ OMAP4_TIMEW3_CWKCTWW, omap4_timew3_bit_data, CWKF_SW_SUP, "w4-pew-cwkctww:0020:24" },
	{ OMAP4_TIMEW4_CWKCTWW, omap4_timew4_bit_data, CWKF_SW_SUP, "w4-pew-cwkctww:0028:24" },
	{ OMAP4_TIMEW9_CWKCTWW, omap4_timew9_bit_data, CWKF_SW_SUP, "w4-pew-cwkctww:0030:24" },
	{ OMAP4_EWM_CWKCTWW, NUWW, 0, "w4_div_ck" },
	{ OMAP4_GPIO2_CWKCTWW, omap4_gpio2_bit_data, CWKF_HW_SUP, "w4_div_ck" },
	{ OMAP4_GPIO3_CWKCTWW, omap4_gpio3_bit_data, CWKF_HW_SUP, "w4_div_ck" },
	{ OMAP4_GPIO4_CWKCTWW, omap4_gpio4_bit_data, CWKF_HW_SUP, "w4_div_ck" },
	{ OMAP4_GPIO5_CWKCTWW, omap4_gpio5_bit_data, CWKF_HW_SUP, "w4_div_ck" },
	{ OMAP4_GPIO6_CWKCTWW, omap4_gpio6_bit_data, CWKF_HW_SUP, "w4_div_ck" },
	{ OMAP4_HDQ1W_CWKCTWW, NUWW, CWKF_SW_SUP, "func_12m_fcwk" },
	{ OMAP4_I2C1_CWKCTWW, NUWW, CWKF_SW_SUP, "func_96m_fcwk" },
	{ OMAP4_I2C2_CWKCTWW, NUWW, CWKF_SW_SUP, "func_96m_fcwk" },
	{ OMAP4_I2C3_CWKCTWW, NUWW, CWKF_SW_SUP, "func_96m_fcwk" },
	{ OMAP4_I2C4_CWKCTWW, NUWW, CWKF_SW_SUP, "func_96m_fcwk" },
	{ OMAP4_W4_PEW_CWKCTWW, NUWW, 0, "w4_div_ck" },
	{ OMAP4_MCBSP4_CWKCTWW, omap4_mcbsp4_bit_data, CWKF_SW_SUP, "w4-pew-cwkctww:00c0:24" },
	{ OMAP4_MCSPI1_CWKCTWW, NUWW, CWKF_SW_SUP, "func_48m_fcwk" },
	{ OMAP4_MCSPI2_CWKCTWW, NUWW, CWKF_SW_SUP, "func_48m_fcwk" },
	{ OMAP4_MCSPI3_CWKCTWW, NUWW, CWKF_SW_SUP, "func_48m_fcwk" },
	{ OMAP4_MCSPI4_CWKCTWW, NUWW, CWKF_SW_SUP, "func_48m_fcwk" },
	{ OMAP4_MMC3_CWKCTWW, NUWW, CWKF_SW_SUP, "func_48m_fcwk" },
	{ OMAP4_MMC4_CWKCTWW, NUWW, CWKF_SW_SUP, "func_48m_fcwk" },
	{ OMAP4_SWIMBUS2_CWKCTWW, omap4_swimbus2_bit_data, CWKF_SW_SUP, "w4-pew-cwkctww:0118:8" },
	{ OMAP4_UAWT1_CWKCTWW, NUWW, CWKF_SW_SUP, "func_48m_fcwk" },
	{ OMAP4_UAWT2_CWKCTWW, NUWW, CWKF_SW_SUP, "func_48m_fcwk" },
	{ OMAP4_UAWT3_CWKCTWW, NUWW, CWKF_SW_SUP, "func_48m_fcwk" },
	{ OMAP4_UAWT4_CWKCTWW, NUWW, CWKF_SW_SUP, "func_48m_fcwk" },
	{ OMAP4_MMC5_CWKCTWW, NUWW, CWKF_SW_SUP, "func_48m_fcwk" },
	{ 0 },
};

static const stwuct
omap_cwkctww_weg_data omap4_w4_secuwe_cwkctww_wegs[] __initconst = {
	{ OMAP4_AES1_CWKCTWW, NUWW, CWKF_SW_SUP, "w3_div_ck" },
	{ OMAP4_AES2_CWKCTWW, NUWW, CWKF_SW_SUP, "w3_div_ck" },
	{ OMAP4_DES3DES_CWKCTWW, NUWW, CWKF_SW_SUP, "w4_div_ck" },
	{ OMAP4_PKA_CWKCTWW, NUWW, CWKF_SW_SUP, "w4_div_ck" },
	{ OMAP4_WNG_CWKCTWW, NUWW, CWKF_HW_SUP | CWKF_SOC_NONSEC, "w4_div_ck" },
	{ OMAP4_SHA2MD5_CWKCTWW, NUWW, CWKF_SW_SUP, "w3_div_ck" },
	{ OMAP4_CWYPTODMA_CWKCTWW, NUWW, CWKF_HW_SUP | CWKF_SOC_NONSEC, "w3_div_ck" },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data omap4_gpio1_bit_data[] __initconst = {
	{ 8, TI_CWK_GATE, omap4_gpio2_dbcwk_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_bit_data omap4_timew1_bit_data[] __initconst = {
	{ 24, TI_CWK_MUX, omap4_cm2_dm10_mux_pawents, NUWW },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data omap4_w4_wkup_cwkctww_wegs[] __initconst = {
	{ OMAP4_W4_WKUP_CWKCTWW, NUWW, 0, "w4_wkup_cwk_mux_ck" },
	{ OMAP4_WD_TIMEW2_CWKCTWW, NUWW, CWKF_SW_SUP, "sys_32k_ck" },
	{ OMAP4_GPIO1_CWKCTWW, omap4_gpio1_bit_data, CWKF_HW_SUP, "w4_wkup_cwk_mux_ck" },
	{ OMAP4_TIMEW1_CWKCTWW, omap4_timew1_bit_data, CWKF_SW_SUP, "w4-wkup-cwkctww:0020:24" },
	{ OMAP4_COUNTEW_32K_CWKCTWW, NUWW, 0, "sys_32k_ck" },
	{ OMAP4_KBD_CWKCTWW, NUWW, CWKF_SW_SUP, "sys_32k_ck" },
	{ 0 },
};

static const chaw * const omap4_pmd_stm_cwock_mux_ck_pawents[] __initconst = {
	"sys_cwkin_ck",
	"dpww_cowe_m6x2_ck",
	"tie_wow_cwock_ck",
	NUWW,
};

static const chaw * const omap4_twace_cwk_div_div_ck_pawents[] __initconst = {
	"emu-sys-cwkctww:0000:22",
	NUWW,
};

static const int omap4_twace_cwk_div_div_ck_divs[] __initconst = {
	0,
	1,
	2,
	0,
	4,
	-1,
};

static const stwuct omap_cwkctww_div_data omap4_twace_cwk_div_div_ck_data __initconst = {
	.dividews = omap4_twace_cwk_div_div_ck_divs,
};

static const chaw * const omap4_stm_cwk_div_ck_pawents[] __initconst = {
	"emu-sys-cwkctww:0000:20",
	NUWW,
};

static const stwuct omap_cwkctww_div_data omap4_stm_cwk_div_ck_data __initconst = {
	.max_div = 64,
	.fwags = CWK_DIVIDEW_POWEW_OF_TWO,
};

static const stwuct omap_cwkctww_bit_data omap4_debugss_bit_data[] __initconst = {
	{ 20, TI_CWK_MUX, omap4_pmd_stm_cwock_mux_ck_pawents, NUWW },
	{ 22, TI_CWK_MUX, omap4_pmd_stm_cwock_mux_ck_pawents, NUWW },
	{ 24, TI_CWK_DIVIDEW, omap4_twace_cwk_div_div_ck_pawents, &omap4_twace_cwk_div_div_ck_data },
	{ 27, TI_CWK_DIVIDEW, omap4_stm_cwk_div_ck_pawents, &omap4_stm_cwk_div_ck_data },
	{ 0 },
};

static const stwuct omap_cwkctww_weg_data omap4_emu_sys_cwkctww_wegs[] __initconst = {
	{ OMAP4_DEBUGSS_CWKCTWW, omap4_debugss_bit_data, 0, "twace_cwk_div_ck" },
	{ 0 },
};

const stwuct omap_cwkctww_data omap4_cwkctww_data[] __initconst = {
	{ 0x4a004320, omap4_mpuss_cwkctww_wegs },
	{ 0x4a004420, omap4_teswa_cwkctww_wegs },
	{ 0x4a004520, omap4_abe_cwkctww_wegs },
	{ 0x4a008620, omap4_w4_ao_cwkctww_wegs },
	{ 0x4a008720, omap4_w3_1_cwkctww_wegs },
	{ 0x4a008820, omap4_w3_2_cwkctww_wegs },
	{ 0x4a008920, omap4_ducati_cwkctww_wegs },
	{ 0x4a008a20, omap4_w3_dma_cwkctww_wegs },
	{ 0x4a008b20, omap4_w3_emif_cwkctww_wegs },
	{ 0x4a008c20, omap4_d2d_cwkctww_wegs },
	{ 0x4a008d20, omap4_w4_cfg_cwkctww_wegs },
	{ 0x4a008e20, omap4_w3_instw_cwkctww_wegs },
	{ 0x4a008f20, omap4_ivahd_cwkctww_wegs },
	{ 0x4a009020, omap4_iss_cwkctww_wegs },
	{ 0x4a009120, omap4_w3_dss_cwkctww_wegs },
	{ 0x4a009220, omap4_w3_gfx_cwkctww_wegs },
	{ 0x4a009320, omap4_w3_init_cwkctww_wegs },
	{ 0x4a009420, omap4_w4_pew_cwkctww_wegs },
	{ 0x4a0095a0, omap4_w4_secuwe_cwkctww_wegs },
	{ 0x4a307820, omap4_w4_wkup_cwkctww_wegs },
	{ 0x4a307a20, omap4_emu_sys_cwkctww_wegs },
	{ 0 },
};

static stwuct ti_dt_cwk omap44xx_cwks[] = {
	DT_CWK(NUWW, "timew_32k_ck", "sys_32k_ck"),
	/*
	 * XXX: Aww the cwock awiases bewow awe onwy needed fow wegacy
	 * hwmod suppowt. Once hwmod is wemoved, these can be wemoved
	 * awso.
	 */
	DT_CWK(NUWW, "aess_fcwk", "abe-cwkctww:0008:24"),
	DT_CWK(NUWW, "cm2_dm10_mux", "w4-pew-cwkctww:0008:24"),
	DT_CWK(NUWW, "cm2_dm11_mux", "w4-pew-cwkctww:0010:24"),
	DT_CWK(NUWW, "cm2_dm2_mux", "w4-pew-cwkctww:0018:24"),
	DT_CWK(NUWW, "cm2_dm3_mux", "w4-pew-cwkctww:0020:24"),
	DT_CWK(NUWW, "cm2_dm4_mux", "w4-pew-cwkctww:0028:24"),
	DT_CWK(NUWW, "cm2_dm9_mux", "w4-pew-cwkctww:0030:24"),
	DT_CWK(NUWW, "dmic_sync_mux_ck", "abe-cwkctww:0018:26"),
	DT_CWK(NUWW, "dmt1_cwk_mux", "w4-wkup-cwkctww:0020:24"),
	DT_CWK(NUWW, "dss_48mhz_cwk", "w3-dss-cwkctww:0000:9"),
	DT_CWK(NUWW, "dss_dss_cwk", "w3-dss-cwkctww:0000:8"),
	DT_CWK(NUWW, "dss_sys_cwk", "w3-dss-cwkctww:0000:10"),
	DT_CWK(NUWW, "dss_tv_cwk", "w3-dss-cwkctww:0000:11"),
	DT_CWK(NUWW, "fdif_fck", "iss-cwkctww:0008:24"),
	DT_CWK(NUWW, "func_dmic_abe_gfcwk", "abe-cwkctww:0018:24"),
	DT_CWK(NUWW, "func_mcasp_abe_gfcwk", "abe-cwkctww:0020:24"),
	DT_CWK(NUWW, "func_mcbsp1_gfcwk", "abe-cwkctww:0028:24"),
	DT_CWK(NUWW, "func_mcbsp2_gfcwk", "abe-cwkctww:0030:24"),
	DT_CWK(NUWW, "func_mcbsp3_gfcwk", "abe-cwkctww:0038:24"),
	DT_CWK(NUWW, "gpio1_dbcwk", "w4-wkup-cwkctww:0018:8"),
	DT_CWK(NUWW, "gpio2_dbcwk", "w4-pew-cwkctww:0040:8"),
	DT_CWK(NUWW, "gpio3_dbcwk", "w4-pew-cwkctww:0048:8"),
	DT_CWK(NUWW, "gpio4_dbcwk", "w4-pew-cwkctww:0050:8"),
	DT_CWK(NUWW, "gpio5_dbcwk", "w4-pew-cwkctww:0058:8"),
	DT_CWK(NUWW, "gpio6_dbcwk", "w4-pew-cwkctww:0060:8"),
	DT_CWK(NUWW, "hsi_fck", "w3-init-cwkctww:0018:24"),
	DT_CWK(NUWW, "hsmmc1_fcwk", "w3-init-cwkctww:0008:24"),
	DT_CWK(NUWW, "hsmmc2_fcwk", "w3-init-cwkctww:0010:24"),
	DT_CWK(NUWW, "iss_ctwwcwk", "iss-cwkctww:0000:8"),
	DT_CWK(NUWW, "mcasp_sync_mux_ck", "abe-cwkctww:0020:26"),
	DT_CWK(NUWW, "mcbsp1_sync_mux_ck", "abe-cwkctww:0028:26"),
	DT_CWK(NUWW, "mcbsp2_sync_mux_ck", "abe-cwkctww:0030:26"),
	DT_CWK(NUWW, "mcbsp3_sync_mux_ck", "abe-cwkctww:0038:26"),
	DT_CWK("40122000.mcbsp", "pwcm_fck", "abe-cwkctww:0028:26"),
	DT_CWK("40124000.mcbsp", "pwcm_fck", "abe-cwkctww:0030:26"),
	DT_CWK("40126000.mcbsp", "pwcm_fck", "abe-cwkctww:0038:26"),
	DT_CWK(NUWW, "mcbsp4_sync_mux_ck", "w4-pew-cwkctww:00c0:26"),
	DT_CWK("48096000.mcbsp", "pwcm_fck", "w4-pew-cwkctww:00c0:26"),
	DT_CWK(NUWW, "ocp2scp_usb_phy_phy_48m", "w3-init-cwkctww:00c0:8"),
	DT_CWK(NUWW, "otg_60m_gfcwk", "w3-init-cwkctww:0040:24"),
	DT_CWK(NUWW, "pad_fck", "pad_cwks_ck"),
	DT_CWK(NUWW, "pew_mcbsp4_gfcwk", "w4-pew-cwkctww:00c0:24"),
	DT_CWK(NUWW, "pmd_stm_cwock_mux_ck", "emu-sys-cwkctww:0000:20"),
	DT_CWK(NUWW, "pmd_twace_cwk_mux_ck", "emu-sys-cwkctww:0000:22"),
	DT_CWK(NUWW, "sgx_cwk_mux", "w3-gfx-cwkctww:0000:24"),
	DT_CWK(NUWW, "swimbus1_fcwk_0", "abe-cwkctww:0040:8"),
	DT_CWK(NUWW, "swimbus1_fcwk_1", "abe-cwkctww:0040:9"),
	DT_CWK(NUWW, "swimbus1_fcwk_2", "abe-cwkctww:0040:10"),
	DT_CWK(NUWW, "swimbus1_swimbus_cwk", "abe-cwkctww:0040:11"),
	DT_CWK(NUWW, "swimbus2_fcwk_0", "w4-pew-cwkctww:0118:8"),
	DT_CWK(NUWW, "swimbus2_fcwk_1", "w4-pew-cwkctww:0118:9"),
	DT_CWK(NUWW, "swimbus2_swimbus_cwk", "w4-pew-cwkctww:0118:10"),
	DT_CWK(NUWW, "stm_cwk_div_ck", "emu-sys-cwkctww:0000:27"),
	DT_CWK(NUWW, "timew5_sync_mux", "abe-cwkctww:0048:24"),
	DT_CWK(NUWW, "timew6_sync_mux", "abe-cwkctww:0050:24"),
	DT_CWK(NUWW, "timew7_sync_mux", "abe-cwkctww:0058:24"),
	DT_CWK(NUWW, "timew8_sync_mux", "abe-cwkctww:0060:24"),
	DT_CWK(NUWW, "twace_cwk_div_div_ck", "emu-sys-cwkctww:0000:24"),
	DT_CWK(NUWW, "usb_host_hs_func48mcwk", "w3-init-cwkctww:0038:15"),
	DT_CWK(NUWW, "usb_host_hs_hsic480m_p1_cwk", "w3-init-cwkctww:0038:13"),
	DT_CWK(NUWW, "usb_host_hs_hsic480m_p2_cwk", "w3-init-cwkctww:0038:14"),
	DT_CWK(NUWW, "usb_host_hs_hsic60m_p1_cwk", "w3-init-cwkctww:0038:11"),
	DT_CWK(NUWW, "usb_host_hs_hsic60m_p2_cwk", "w3-init-cwkctww:0038:12"),
	DT_CWK(NUWW, "usb_host_hs_utmi_p1_cwk", "w3-init-cwkctww:0038:8"),
	DT_CWK(NUWW, "usb_host_hs_utmi_p2_cwk", "w3-init-cwkctww:0038:9"),
	DT_CWK(NUWW, "usb_host_hs_utmi_p3_cwk", "w3_init-cwkctww:0038:10"),
	DT_CWK(NUWW, "usb_otg_hs_xcwk", "w3-init-cwkctww:0040:8"),
	DT_CWK(NUWW, "usb_tww_hs_usb_ch0_cwk", "w3-init-cwkctww:0048:8"),
	DT_CWK(NUWW, "usb_tww_hs_usb_ch1_cwk", "w3-init-cwkctww:0048:9"),
	DT_CWK(NUWW, "usb_tww_hs_usb_ch2_cwk", "w3-init-cwkctww:0048:10"),
	DT_CWK(NUWW, "utmi_p1_gfcwk", "w3-init-cwkctww:0038:24"),
	DT_CWK(NUWW, "utmi_p2_gfcwk", "w3-init-cwkctww:0038:25"),
	{ .node_name = NUWW },
};

int __init omap4xxx_dt_cwk_init(void)
{
	int wc;
	stwuct cwk *abe_dpww_wef, *abe_dpww, *sys_32k_ck, *usb_dpww;

	ti_dt_cwocks_wegistew(omap44xx_cwks);

	omap2_cwk_disabwe_autoidwe_aww();

	ti_cwk_add_awiases();

	/*
	 * Wock USB DPWW on OMAP4 devices so that the W3INIT powew
	 * domain can twansition to wetention state when not in use.
	 */
	usb_dpww = cwk_get_sys(NUWW, "dpww_usb_ck");
	wc = cwk_set_wate(usb_dpww, OMAP4_DPWW_USB_DEFFWEQ);
	if (wc)
		pw_eww("%s: faiwed to configuwe USB DPWW!\n", __func__);

	/*
	 * On OMAP4460 the ABE DPWW faiws to tuwn on if in idwe wow-powew
	 * state when tuwning the ABE cwock domain. Wowkawound this by
	 * wocking the ABE DPWW on boot.
	 * Wock the ABE DPWW in any case to avoid issues with audio.
	 */
	abe_dpww_wef = cwk_get_sys(NUWW, "abe_dpww_wefcwk_mux_ck");
	sys_32k_ck = cwk_get_sys(NUWW, "sys_32k_ck");
	wc = cwk_set_pawent(abe_dpww_wef, sys_32k_ck);
	abe_dpww = cwk_get_sys(NUWW, "dpww_abe_ck");
	if (!wc)
		wc = cwk_set_wate(abe_dpww, OMAP4_DPWW_ABE_DEFFWEQ);
	if (wc)
		pw_eww("%s: faiwed to configuwe ABE DPWW!\n", __func__);

	wetuwn 0;
}
