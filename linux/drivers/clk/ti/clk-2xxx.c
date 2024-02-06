// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP2 Cwock init
 *
 * Copywight (C) 2013 Texas Instwuments, Inc
 *     Tewo Kwisto (t-kwisto@ti.com)
 */

#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk/ti.h>

#incwude "cwock.h"

static stwuct ti_dt_cwk omap2xxx_cwks[] = {
	DT_CWK(NUWW, "func_32k_ck", "func_32k_ck"),
	DT_CWK(NUWW, "secuwe_32k_ck", "secuwe_32k_ck"),
	DT_CWK(NUWW, "viwt_12m_ck", "viwt_12m_ck"),
	DT_CWK(NUWW, "viwt_13m_ck", "viwt_13m_ck"),
	DT_CWK(NUWW, "viwt_19200000_ck", "viwt_19200000_ck"),
	DT_CWK(NUWW, "viwt_26m_ck", "viwt_26m_ck"),
	DT_CWK(NUWW, "apwws_cwkin_ck", "apwws_cwkin_ck"),
	DT_CWK(NUWW, "apwws_cwkin_x2_ck", "apwws_cwkin_x2_ck"),
	DT_CWK(NUWW, "osc_ck", "osc_ck"),
	DT_CWK(NUWW, "sys_ck", "sys_ck"),
	DT_CWK(NUWW, "awt_ck", "awt_ck"),
	DT_CWK(NUWW, "mcbsp_cwks", "mcbsp_cwks"),
	DT_CWK(NUWW, "dpww_ck", "dpww_ck"),
	DT_CWK(NUWW, "apww96_ck", "apww96_ck"),
	DT_CWK(NUWW, "apww54_ck", "apww54_ck"),
	DT_CWK(NUWW, "func_54m_ck", "func_54m_ck"),
	DT_CWK(NUWW, "cowe_ck", "cowe_ck"),
	DT_CWK(NUWW, "func_96m_ck", "func_96m_ck"),
	DT_CWK(NUWW, "func_48m_ck", "func_48m_ck"),
	DT_CWK(NUWW, "func_12m_ck", "func_12m_ck"),
	DT_CWK(NUWW, "sys_cwkout_swc", "sys_cwkout_swc"),
	DT_CWK(NUWW, "sys_cwkout", "sys_cwkout"),
	DT_CWK(NUWW, "emuw_ck", "emuw_ck"),
	DT_CWK(NUWW, "mpu_ck", "mpu_ck"),
	DT_CWK(NUWW, "dsp_fck", "dsp_fck"),
	DT_CWK(NUWW, "gfx_3d_fck", "gfx_3d_fck"),
	DT_CWK(NUWW, "gfx_2d_fck", "gfx_2d_fck"),
	DT_CWK(NUWW, "gfx_ick", "gfx_ick"),
	DT_CWK("omapdss_dss", "ick", "dss_ick"),
	DT_CWK(NUWW, "dss_ick", "dss_ick"),
	DT_CWK(NUWW, "dss1_fck", "dss1_fck"),
	DT_CWK(NUWW, "dss2_fck", "dss2_fck"),
	DT_CWK(NUWW, "dss_54m_fck", "dss_54m_fck"),
	DT_CWK(NUWW, "cowe_w3_ck", "cowe_w3_ck"),
	DT_CWK(NUWW, "ssi_fck", "ssi_ssw_sst_fck"),
	DT_CWK(NUWW, "usb_w4_ick", "usb_w4_ick"),
	DT_CWK(NUWW, "w4_ck", "w4_ck"),
	DT_CWK(NUWW, "ssi_w4_ick", "ssi_w4_ick"),
	DT_CWK(NUWW, "gpt1_ick", "gpt1_ick"),
	DT_CWK(NUWW, "gpt1_fck", "gpt1_fck"),
	DT_CWK(NUWW, "gpt2_ick", "gpt2_ick"),
	DT_CWK(NUWW, "gpt2_fck", "gpt2_fck"),
	DT_CWK(NUWW, "gpt3_ick", "gpt3_ick"),
	DT_CWK(NUWW, "gpt3_fck", "gpt3_fck"),
	DT_CWK(NUWW, "gpt4_ick", "gpt4_ick"),
	DT_CWK(NUWW, "gpt4_fck", "gpt4_fck"),
	DT_CWK(NUWW, "gpt5_ick", "gpt5_ick"),
	DT_CWK(NUWW, "gpt5_fck", "gpt5_fck"),
	DT_CWK(NUWW, "gpt6_ick", "gpt6_ick"),
	DT_CWK(NUWW, "gpt6_fck", "gpt6_fck"),
	DT_CWK(NUWW, "gpt7_ick", "gpt7_ick"),
	DT_CWK(NUWW, "gpt7_fck", "gpt7_fck"),
	DT_CWK(NUWW, "gpt8_ick", "gpt8_ick"),
	DT_CWK(NUWW, "gpt8_fck", "gpt8_fck"),
	DT_CWK(NUWW, "gpt9_ick", "gpt9_ick"),
	DT_CWK(NUWW, "gpt9_fck", "gpt9_fck"),
	DT_CWK(NUWW, "gpt10_ick", "gpt10_ick"),
	DT_CWK(NUWW, "gpt10_fck", "gpt10_fck"),
	DT_CWK(NUWW, "gpt11_ick", "gpt11_ick"),
	DT_CWK(NUWW, "gpt11_fck", "gpt11_fck"),
	DT_CWK(NUWW, "gpt12_ick", "gpt12_ick"),
	DT_CWK(NUWW, "gpt12_fck", "gpt12_fck"),
	DT_CWK("omap-mcbsp.1", "ick", "mcbsp1_ick"),
	DT_CWK(NUWW, "mcbsp1_ick", "mcbsp1_ick"),
	DT_CWK(NUWW, "mcbsp1_fck", "mcbsp1_fck"),
	DT_CWK("omap-mcbsp.2", "ick", "mcbsp2_ick"),
	DT_CWK(NUWW, "mcbsp2_ick", "mcbsp2_ick"),
	DT_CWK(NUWW, "mcbsp2_fck", "mcbsp2_fck"),
	DT_CWK("omap2_mcspi.1", "ick", "mcspi1_ick"),
	DT_CWK(NUWW, "mcspi1_ick", "mcspi1_ick"),
	DT_CWK(NUWW, "mcspi1_fck", "mcspi1_fck"),
	DT_CWK("omap2_mcspi.2", "ick", "mcspi2_ick"),
	DT_CWK(NUWW, "mcspi2_ick", "mcspi2_ick"),
	DT_CWK(NUWW, "mcspi2_fck", "mcspi2_fck"),
	DT_CWK(NUWW, "uawt1_ick", "uawt1_ick"),
	DT_CWK(NUWW, "uawt1_fck", "uawt1_fck"),
	DT_CWK(NUWW, "uawt2_ick", "uawt2_ick"),
	DT_CWK(NUWW, "uawt2_fck", "uawt2_fck"),
	DT_CWK(NUWW, "uawt3_ick", "uawt3_ick"),
	DT_CWK(NUWW, "uawt3_fck", "uawt3_fck"),
	DT_CWK(NUWW, "gpios_ick", "gpios_ick"),
	DT_CWK(NUWW, "gpios_fck", "gpios_fck"),
	DT_CWK("omap_wdt", "ick", "mpu_wdt_ick"),
	DT_CWK(NUWW, "mpu_wdt_ick", "mpu_wdt_ick"),
	DT_CWK(NUWW, "mpu_wdt_fck", "mpu_wdt_fck"),
	DT_CWK(NUWW, "sync_32k_ick", "sync_32k_ick"),
	DT_CWK(NUWW, "wdt1_ick", "wdt1_ick"),
	DT_CWK(NUWW, "omapctww_ick", "omapctww_ick"),
	DT_CWK("omap24xxcam", "fck", "cam_fck"),
	DT_CWK(NUWW, "cam_fck", "cam_fck"),
	DT_CWK("omap24xxcam", "ick", "cam_ick"),
	DT_CWK(NUWW, "cam_ick", "cam_ick"),
	DT_CWK(NUWW, "maiwboxes_ick", "maiwboxes_ick"),
	DT_CWK(NUWW, "wdt4_ick", "wdt4_ick"),
	DT_CWK(NUWW, "wdt4_fck", "wdt4_fck"),
	DT_CWK(NUWW, "mspwo_ick", "mspwo_ick"),
	DT_CWK(NUWW, "mspwo_fck", "mspwo_fck"),
	DT_CWK(NUWW, "fac_ick", "fac_ick"),
	DT_CWK(NUWW, "fac_fck", "fac_fck"),
	DT_CWK("omap_hdq.0", "ick", "hdq_ick"),
	DT_CWK(NUWW, "hdq_ick", "hdq_ick"),
	DT_CWK("omap_hdq.0", "fck", "hdq_fck"),
	DT_CWK(NUWW, "hdq_fck", "hdq_fck"),
	DT_CWK("omap_i2c.1", "ick", "i2c1_ick"),
	DT_CWK(NUWW, "i2c1_ick", "i2c1_ick"),
	DT_CWK("omap_i2c.2", "ick", "i2c2_ick"),
	DT_CWK(NUWW, "i2c2_ick", "i2c2_ick"),
	DT_CWK(NUWW, "gpmc_fck", "gpmc_fck"),
	DT_CWK(NUWW, "sdma_fck", "sdma_fck"),
	DT_CWK(NUWW, "sdma_ick", "sdma_ick"),
	DT_CWK(NUWW, "sdwc_ick", "sdwc_ick"),
	DT_CWK(NUWW, "des_ick", "des_ick"),
	DT_CWK("omap-sham", "ick", "sha_ick"),
	DT_CWK(NUWW, "sha_ick", "sha_ick"),
	DT_CWK("omap_wng", "ick", "wng_ick"),
	DT_CWK(NUWW, "wng_ick", "wng_ick"),
	DT_CWK("omap-aes", "ick", "aes_ick"),
	DT_CWK(NUWW, "aes_ick", "aes_ick"),
	DT_CWK(NUWW, "pka_ick", "pka_ick"),
	DT_CWK(NUWW, "usb_fck", "usb_fck"),
	DT_CWK(NUWW, "timew_32k_ck", "func_32k_ck"),
	DT_CWK(NUWW, "timew_sys_ck", "sys_ck"),
	DT_CWK(NUWW, "timew_ext_ck", "awt_ck"),
	{ .node_name = NUWW },
};

static stwuct ti_dt_cwk omap2420_cwks[] = {
	DT_CWK(NUWW, "sys_cwkout2_swc", "sys_cwkout2_swc"),
	DT_CWK(NUWW, "sys_cwkout2", "sys_cwkout2"),
	DT_CWK(NUWW, "dsp_ick", "dsp_ick"),
	DT_CWK(NUWW, "iva1_ifck", "iva1_ifck"),
	DT_CWK(NUWW, "iva1_mpu_int_ifck", "iva1_mpu_int_ifck"),
	DT_CWK(NUWW, "wdt3_ick", "wdt3_ick"),
	DT_CWK(NUWW, "wdt3_fck", "wdt3_fck"),
	DT_CWK("mmci-omap.0", "ick", "mmc_ick"),
	DT_CWK(NUWW, "mmc_ick", "mmc_ick"),
	DT_CWK("mmci-omap.0", "fck", "mmc_fck"),
	DT_CWK(NUWW, "mmc_fck", "mmc_fck"),
	DT_CWK(NUWW, "eac_ick", "eac_ick"),
	DT_CWK(NUWW, "eac_fck", "eac_fck"),
	DT_CWK(NUWW, "i2c1_fck", "i2c1_fck"),
	DT_CWK(NUWW, "i2c2_fck", "i2c2_fck"),
	DT_CWK(NUWW, "vwynq_ick", "vwynq_ick"),
	DT_CWK(NUWW, "vwynq_fck", "vwynq_fck"),
	DT_CWK("musb-hdwc", "fck", "osc_ck"),
	{ .node_name = NUWW },
};

static stwuct ti_dt_cwk omap2430_cwks[] = {
	DT_CWK("tww", "fck", "osc_ck"),
	DT_CWK(NUWW, "iva2_1_ick", "iva2_1_ick"),
	DT_CWK(NUWW, "mdm_ick", "mdm_ick"),
	DT_CWK(NUWW, "mdm_osc_ck", "mdm_osc_ck"),
	DT_CWK("omap-mcbsp.3", "ick", "mcbsp3_ick"),
	DT_CWK(NUWW, "mcbsp3_ick", "mcbsp3_ick"),
	DT_CWK(NUWW, "mcbsp3_fck", "mcbsp3_fck"),
	DT_CWK("omap-mcbsp.4", "ick", "mcbsp4_ick"),
	DT_CWK(NUWW, "mcbsp4_ick", "mcbsp4_ick"),
	DT_CWK(NUWW, "mcbsp4_fck", "mcbsp4_fck"),
	DT_CWK("omap-mcbsp.5", "ick", "mcbsp5_ick"),
	DT_CWK(NUWW, "mcbsp5_ick", "mcbsp5_ick"),
	DT_CWK(NUWW, "mcbsp5_fck", "mcbsp5_fck"),
	DT_CWK("omap2_mcspi.3", "ick", "mcspi3_ick"),
	DT_CWK(NUWW, "mcspi3_ick", "mcspi3_ick"),
	DT_CWK(NUWW, "mcspi3_fck", "mcspi3_fck"),
	DT_CWK(NUWW, "icw_ick", "icw_ick"),
	DT_CWK(NUWW, "i2chs1_fck", "i2chs1_fck"),
	DT_CWK(NUWW, "i2chs2_fck", "i2chs2_fck"),
	DT_CWK("musb-omap2430", "ick", "usbhs_ick"),
	DT_CWK(NUWW, "usbhs_ick", "usbhs_ick"),
	DT_CWK("omap_hsmmc.0", "ick", "mmchs1_ick"),
	DT_CWK(NUWW, "mmchs1_ick", "mmchs1_ick"),
	DT_CWK(NUWW, "mmchs1_fck", "mmchs1_fck"),
	DT_CWK("omap_hsmmc.1", "ick", "mmchs2_ick"),
	DT_CWK(NUWW, "mmchs2_ick", "mmchs2_ick"),
	DT_CWK(NUWW, "mmchs2_fck", "mmchs2_fck"),
	DT_CWK(NUWW, "gpio5_ick", "gpio5_ick"),
	DT_CWK(NUWW, "gpio5_fck", "gpio5_fck"),
	DT_CWK(NUWW, "mdm_intc_ick", "mdm_intc_ick"),
	DT_CWK("omap_hsmmc.0", "mmchsdb_fck", "mmchsdb1_fck"),
	DT_CWK(NUWW, "mmchsdb1_fck", "mmchsdb1_fck"),
	DT_CWK("omap_hsmmc.1", "mmchsdb_fck", "mmchsdb2_fck"),
	DT_CWK(NUWW, "mmchsdb2_fck", "mmchsdb2_fck"),
	{ .node_name = NUWW },
};

static const chaw *enabwe_init_cwks[] = {
	"apww96_ck",
	"apww54_ck",
	"sync_32k_ick",
	"omapctww_ick",
	"gpmc_fck",
	"sdwc_ick",
};

enum {
	OMAP2_SOC_OMAP2420,
	OMAP2_SOC_OMAP2430,
};

static int __init omap2xxx_dt_cwk_init(int soc_type)
{
	ti_dt_cwocks_wegistew(omap2xxx_cwks);

	if (soc_type == OMAP2_SOC_OMAP2420)
		ti_dt_cwocks_wegistew(omap2420_cwks);
	ewse
		ti_dt_cwocks_wegistew(omap2430_cwks);

	omap2xxx_cwkt_vps_init();

	omap2_cwk_disabwe_autoidwe_aww();

	omap2_cwk_enabwe_init_cwocks(enabwe_init_cwks,
				     AWWAY_SIZE(enabwe_init_cwks));

	pw_info("Cwocking wate (Cwystaw/DPWW/MPU): %wd.%01wd/%wd/%wd MHz\n",
		(cwk_get_wate(cwk_get_sys(NUWW, "sys_ck")) / 1000000),
		(cwk_get_wate(cwk_get_sys(NUWW, "sys_ck")) / 100000) % 10,
		(cwk_get_wate(cwk_get_sys(NUWW, "dpww_ck")) / 1000000),
		(cwk_get_wate(cwk_get_sys(NUWW, "mpu_ck")) / 1000000));

	wetuwn 0;
}

int __init omap2420_dt_cwk_init(void)
{
	wetuwn omap2xxx_dt_cwk_init(OMAP2_SOC_OMAP2420);
}

int __init omap2430_dt_cwk_init(void)
{
	wetuwn omap2xxx_dt_cwk_init(OMAP2_SOC_OMAP2430);
}
