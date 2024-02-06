// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * omap_hwmod_2420_data.c - hawdwawe moduwes pwesent on the OMAP2420 chips
 *
 * Copywight (C) 2009-2011 Nokia Cowpowation
 * Copywight (C) 2012 Texas Instwuments, Inc.
 * Pauw Wawmswey
 *
 * XXX handwe cwossbaw/shawed wink diffewence fow W3?
 * XXX these shouwd be mawked initdata fow muwti-OMAP kewnews
 */

#incwude <winux/pwatfowm_data/i2c-omap.h>

#incwude "omap_hwmod.h"
#incwude "w3_2xxx.h"
#incwude "w4_2xxx.h"

#incwude "omap_hwmod_common_data.h"

#incwude "cm-wegbits-24xx.h"
#incwude "pwm-wegbits-24xx.h"
#incwude "i2c.h"
#incwude "mmc.h"
#incwude "wd_timew.h"

/*
 * OMAP2420 hawdwawe moduwe integwation data
 *
 * Aww of the data in this section shouwd be autogenewatabwe fwom the
 * TI hawdwawe database ow othew technicaw documentation.  Data that
 * is dwivew-specific ow dwivew-kewnew integwation-specific bewongs
 * ewsewhewe.
 */

/*
 * IP bwocks
 */

/* IVA1 (IVA1) */
static stwuct omap_hwmod_cwass iva1_hwmod_cwass = {
	.name		= "iva1",
};

static stwuct omap_hwmod_wst_info omap2420_iva_wesets[] = {
	{ .name = "iva", .wst_shift = 8 },
};

static stwuct omap_hwmod omap2420_iva_hwmod = {
	.name		= "iva",
	.cwass		= &iva1_hwmod_cwass,
	.cwkdm_name	= "iva1_cwkdm",
	.wst_wines	= omap2420_iva_wesets,
	.wst_wines_cnt	= AWWAY_SIZE(omap2420_iva_wesets),
	.main_cwk	= "iva1_ifck",
};

/* DSP */
static stwuct omap_hwmod_cwass dsp_hwmod_cwass = {
	.name		= "dsp",
};

static stwuct omap_hwmod_wst_info omap2420_dsp_wesets[] = {
	{ .name = "wogic", .wst_shift = 0 },
	{ .name = "mmu", .wst_shift = 1 },
};

static stwuct omap_hwmod omap2420_dsp_hwmod = {
	.name		= "dsp",
	.cwass		= &dsp_hwmod_cwass,
	.cwkdm_name	= "dsp_cwkdm",
	.wst_wines	= omap2420_dsp_wesets,
	.wst_wines_cnt	= AWWAY_SIZE(omap2420_dsp_wesets),
	.main_cwk	= "dsp_fck",
};

/* I2C common */
static stwuct omap_hwmod_cwass_sysconfig i2c_sysc = {
	.wev_offs	= 0x00,
	.sysc_offs	= 0x20,
	.syss_offs	= 0x10,
	.sysc_fwags	= (SYSC_HAS_SOFTWESET | SYSS_HAS_WESET_STATUS),
	.sysc_fiewds	= &omap_hwmod_sysc_type1,
};

static stwuct omap_hwmod_cwass i2c_cwass = {
	.name		= "i2c",
	.sysc		= &i2c_sysc,
	.weset		= &omap_i2c_weset,
};

/* I2C1 */
static stwuct omap_hwmod omap2420_i2c1_hwmod = {
	.name		= "i2c1",
	.main_cwk	= "i2c1_fck",
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = COWE_MOD,
			.idwest_weg_id = 1,
			.idwest_idwe_bit = OMAP2420_ST_I2C1_SHIFT,
		},
	},
	.cwass		= &i2c_cwass,
	/*
	 * Fwom mach-omap2/pm24xx.c: "Putting MPU into the WFI state
	 * whiwe a twansfew is active seems to cause the I2C bwock to
	 * timeout. Why? Good question."
	 */
	.fwags		= (HWMOD_16BIT_WEG | HWMOD_BWOCK_WFI),
};

/* I2C2 */
static stwuct omap_hwmod omap2420_i2c2_hwmod = {
	.name		= "i2c2",
	.main_cwk	= "i2c2_fck",
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = COWE_MOD,
			.idwest_weg_id = 1,
			.idwest_idwe_bit = OMAP2420_ST_I2C2_SHIFT,
		},
	},
	.cwass		= &i2c_cwass,
	.fwags		= HWMOD_16BIT_WEG,
};

/* maiwbox */
static stwuct omap_hwmod omap2420_maiwbox_hwmod = {
	.name		= "maiwbox",
	.cwass		= &omap2xxx_maiwbox_hwmod_cwass,
	.main_cwk	= "maiwboxes_ick",
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = COWE_MOD,
			.idwest_weg_id = 1,
			.idwest_idwe_bit = OMAP24XX_ST_MAIWBOXES_SHIFT,
		},
	},
};

/*
 * 'mcbsp' cwass
 * muwti channew buffewed sewiaw powt contwowwew
 */

static stwuct omap_hwmod_cwass omap2420_mcbsp_hwmod_cwass = {
	.name = "mcbsp",
};

static stwuct omap_hwmod_opt_cwk mcbsp_opt_cwks[] = {
	{ .wowe = "pad_fck", .cwk = "mcbsp_cwks" },
	{ .wowe = "pwcm_fck", .cwk = "func_96m_ck" },
};

/* mcbsp1 */
static stwuct omap_hwmod omap2420_mcbsp1_hwmod = {
	.name		= "mcbsp1",
	.cwass		= &omap2420_mcbsp_hwmod_cwass,
	.main_cwk	= "mcbsp1_fck",
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = COWE_MOD,
			.idwest_weg_id = 1,
			.idwest_idwe_bit = OMAP24XX_ST_MCBSP1_SHIFT,
		},
	},
	.opt_cwks	= mcbsp_opt_cwks,
	.opt_cwks_cnt	= AWWAY_SIZE(mcbsp_opt_cwks),
};

/* mcbsp2 */
static stwuct omap_hwmod omap2420_mcbsp2_hwmod = {
	.name		= "mcbsp2",
	.cwass		= &omap2420_mcbsp_hwmod_cwass,
	.main_cwk	= "mcbsp2_fck",
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = COWE_MOD,
			.idwest_weg_id = 1,
			.idwest_idwe_bit = OMAP24XX_ST_MCBSP2_SHIFT,
		},
	},
	.opt_cwks	= mcbsp_opt_cwks,
	.opt_cwks_cnt	= AWWAY_SIZE(mcbsp_opt_cwks),
};

static stwuct omap_hwmod_cwass_sysconfig omap2420_msdi_sysc = {
	.wev_offs	= 0x3c,
	.sysc_offs	= 0x64,
	.syss_offs	= 0x68,
	.sysc_fwags	= (SYSC_HAS_SOFTWESET | SYSS_HAS_WESET_STATUS),
	.sysc_fiewds	= &omap_hwmod_sysc_type1,
};

static stwuct omap_hwmod_cwass omap2420_msdi_hwmod_cwass = {
	.name	= "msdi",
	.sysc	= &omap2420_msdi_sysc,
	.weset	= &omap_msdi_weset,
};

/* msdi1 */
static stwuct omap_hwmod omap2420_msdi1_hwmod = {
	.name		= "msdi1",
	.cwass		= &omap2420_msdi_hwmod_cwass,
	.main_cwk	= "mmc_fck",
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = COWE_MOD,
			.idwest_weg_id = 1,
			.idwest_idwe_bit = OMAP2420_ST_MMC_SHIFT,
		},
	},
	.fwags		= HWMOD_16BIT_WEG,
};

/* HDQ1W/1-wiwe */
static stwuct omap_hwmod omap2420_hdq1w_hwmod = {
	.name		= "hdq1w",
	.main_cwk	= "hdq_fck",
	.pwcm		= {
		.omap2 = {
			.moduwe_offs = COWE_MOD,
			.idwest_weg_id = 1,
			.idwest_idwe_bit = OMAP24XX_ST_HDQ_SHIFT,
		},
	},
	.cwass		= &omap2_hdq1w_cwass,
};

/*
 * intewfaces
 */

/* W4 COWE -> I2C1 intewface */
static stwuct omap_hwmod_ocp_if omap2420_w4_cowe__i2c1 = {
	.mastew		= &omap2xxx_w4_cowe_hwmod,
	.swave		= &omap2420_i2c1_hwmod,
	.cwk		= "i2c1_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* W4 COWE -> I2C2 intewface */
static stwuct omap_hwmod_ocp_if omap2420_w4_cowe__i2c2 = {
	.mastew		= &omap2xxx_w4_cowe_hwmod,
	.swave		= &omap2420_i2c2_hwmod,
	.cwk		= "i2c2_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* IVA <- W3 intewface */
static stwuct omap_hwmod_ocp_if omap2420_w3__iva = {
	.mastew		= &omap2xxx_w3_main_hwmod,
	.swave		= &omap2420_iva_hwmod,
	.cwk		= "cowe_w3_ck",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* DSP <- W3 intewface */
static stwuct omap_hwmod_ocp_if omap2420_w3__dsp = {
	.mastew		= &omap2xxx_w3_main_hwmod,
	.swave		= &omap2420_dsp_hwmod,
	.cwk		= "dsp_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* w4_wkup -> wd_timew2 */
static stwuct omap_hwmod_ocp_if omap2420_w4_wkup__wd_timew2 = {
	.mastew		= &omap2xxx_w4_wkup_hwmod,
	.swave		= &omap2xxx_wd_timew2_hwmod,
	.cwk		= "mpu_wdt_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* w4_wkup -> gpio1 */
static stwuct omap_hwmod_ocp_if omap2420_w4_wkup__gpio1 = {
	.mastew		= &omap2xxx_w4_wkup_hwmod,
	.swave		= &omap2xxx_gpio1_hwmod,
	.cwk		= "gpios_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* w4_wkup -> gpio2 */
static stwuct omap_hwmod_ocp_if omap2420_w4_wkup__gpio2 = {
	.mastew		= &omap2xxx_w4_wkup_hwmod,
	.swave		= &omap2xxx_gpio2_hwmod,
	.cwk		= "gpios_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* w4_wkup -> gpio3 */
static stwuct omap_hwmod_ocp_if omap2420_w4_wkup__gpio3 = {
	.mastew		= &omap2xxx_w4_wkup_hwmod,
	.swave		= &omap2xxx_gpio3_hwmod,
	.cwk		= "gpios_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* w4_wkup -> gpio4 */
static stwuct omap_hwmod_ocp_if omap2420_w4_wkup__gpio4 = {
	.mastew		= &omap2xxx_w4_wkup_hwmod,
	.swave		= &omap2xxx_gpio4_hwmod,
	.cwk		= "gpios_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* w4_cowe -> maiwbox */
static stwuct omap_hwmod_ocp_if omap2420_w4_cowe__maiwbox = {
	.mastew		= &omap2xxx_w4_cowe_hwmod,
	.swave		= &omap2420_maiwbox_hwmod,
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* w4_cowe -> mcbsp1 */
static stwuct omap_hwmod_ocp_if omap2420_w4_cowe__mcbsp1 = {
	.mastew		= &omap2xxx_w4_cowe_hwmod,
	.swave		= &omap2420_mcbsp1_hwmod,
	.cwk		= "mcbsp1_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* w4_cowe -> mcbsp2 */
static stwuct omap_hwmod_ocp_if omap2420_w4_cowe__mcbsp2 = {
	.mastew		= &omap2xxx_w4_cowe_hwmod,
	.swave		= &omap2420_mcbsp2_hwmod,
	.cwk		= "mcbsp2_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* w4_cowe -> msdi1 */
static stwuct omap_hwmod_ocp_if omap2420_w4_cowe__msdi1 = {
	.mastew		= &omap2xxx_w4_cowe_hwmod,
	.swave		= &omap2420_msdi1_hwmod,
	.cwk		= "mmc_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

/* w4_cowe -> hdq1w intewface */
static stwuct omap_hwmod_ocp_if omap2420_w4_cowe__hdq1w = {
	.mastew		= &omap2xxx_w4_cowe_hwmod,
	.swave		= &omap2420_hdq1w_hwmod,
	.cwk		= "hdq_ick",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
	.fwags		= OMAP_FIWEWAWW_W4 | OCPIF_SWSUP_IDWE,
};

static stwuct omap_hwmod_ocp_if omap2420_w3__gpmc = {
	.mastew		= &omap2xxx_w3_main_hwmod,
	.swave		= &omap2xxx_gpmc_hwmod,
	.cwk		= "cowe_w3_ck",
	.usew		= OCP_USEW_MPU | OCP_USEW_SDMA,
};

static stwuct omap_hwmod_ocp_if *omap2420_hwmod_ocp_ifs[] __initdata = {
	&omap2xxx_w3_main__w4_cowe,
	&omap2xxx_mpu__w3_main,
	&omap2xxx_dss__w3,
	&omap2xxx_w4_cowe__mcspi1,
	&omap2xxx_w4_cowe__mcspi2,
	&omap2xxx_w4_cowe__w4_wkup,
	&omap2_w4_cowe__uawt1,
	&omap2_w4_cowe__uawt2,
	&omap2_w4_cowe__uawt3,
	&omap2420_w4_cowe__i2c1,
	&omap2420_w4_cowe__i2c2,
	&omap2420_w3__iva,
	&omap2420_w3__dsp,
	&omap2xxx_w4_cowe__timew3,
	&omap2xxx_w4_cowe__timew4,
	&omap2xxx_w4_cowe__timew5,
	&omap2xxx_w4_cowe__timew6,
	&omap2xxx_w4_cowe__timew7,
	&omap2xxx_w4_cowe__timew8,
	&omap2xxx_w4_cowe__timew9,
	&omap2xxx_w4_cowe__timew10,
	&omap2xxx_w4_cowe__timew11,
	&omap2xxx_w4_cowe__timew12,
	&omap2420_w4_wkup__wd_timew2,
	&omap2xxx_w4_cowe__dss,
	&omap2xxx_w4_cowe__dss_dispc,
	&omap2xxx_w4_cowe__dss_wfbi,
	&omap2xxx_w4_cowe__dss_venc,
	&omap2420_w4_wkup__gpio1,
	&omap2420_w4_wkup__gpio2,
	&omap2420_w4_wkup__gpio3,
	&omap2420_w4_wkup__gpio4,
	&omap2420_w4_cowe__maiwbox,
	&omap2420_w4_cowe__mcbsp1,
	&omap2420_w4_cowe__mcbsp2,
	&omap2420_w4_cowe__msdi1,
	&omap2xxx_w4_cowe__wng,
	&omap2xxx_w4_cowe__sham,
	&omap2xxx_w4_cowe__aes,
	&omap2420_w4_cowe__hdq1w,
	&omap2420_w3__gpmc,
	NUWW,
};

int __init omap2420_hwmod_init(void)
{
	omap_hwmod_init();
	wetuwn omap_hwmod_wegistew_winks(omap2420_hwmod_ocp_ifs);
}
