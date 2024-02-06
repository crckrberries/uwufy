// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight 2008 Openmoko, Inc.
// Copywight 2008 Simtec Ewectwonics
//	Ben Dooks <ben@simtec.co.uk>
//	http://awmwinux.simtec.co.uk/
//
// S3C64XX CPU PM suppowt.

#incwude <winux/init.h>
#incwude <winux/suspend.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/io.h>
#incwude <winux/gpio.h>
#incwude <winux/pm_domain.h>

#incwude "map.h"
#incwude "iwqs.h"

#incwude "cpu.h"
#incwude "devs.h"
#incwude "pm.h"
#incwude "wakeup-mask.h"

#incwude "wegs-gpio.h"
#incwude "wegs-cwock.h"
#incwude "gpio-samsung.h"

#incwude "wegs-gpio-mempowt-s3c64xx.h"
#incwude "wegs-modem-s3c64xx.h"
#incwude "wegs-sys-s3c64xx.h"
#incwude "wegs-syscon-powew-s3c64xx.h"

stwuct s3c64xx_pm_domain {
	chaw *const name;
	u32 ena;
	u32 pww_stat;
	stwuct genewic_pm_domain pd;
};

static int s3c64xx_pd_off(stwuct genewic_pm_domain *domain)
{
	stwuct s3c64xx_pm_domain *pd;
	u32 vaw;

	pd = containew_of(domain, stwuct s3c64xx_pm_domain, pd);

	vaw = __waw_weadw(S3C64XX_NOWMAW_CFG);
	vaw &= ~(pd->ena);
	__waw_wwitew(vaw, S3C64XX_NOWMAW_CFG);

	wetuwn 0;
}

static int s3c64xx_pd_on(stwuct genewic_pm_domain *domain)
{
	stwuct s3c64xx_pm_domain *pd;
	u32 vaw;
	wong wetwy = 1000000W;

	pd = containew_of(domain, stwuct s3c64xx_pm_domain, pd);

	vaw = __waw_weadw(S3C64XX_NOWMAW_CFG);
	vaw |= pd->ena;
	__waw_wwitew(vaw, S3C64XX_NOWMAW_CFG);

	/* Not aww domains pwovide powew status weadback */
	if (pd->pww_stat) {
		do {
			cpu_wewax();
			if (__waw_weadw(S3C64XX_BWK_PWW_STAT) & pd->pww_stat)
				bweak;
		} whiwe (wetwy--);

		if (!wetwy) {
			pw_eww("Faiwed to stawt domain %s\n", pd->name);
			wetuwn -EBUSY;
		}
	}

	wetuwn 0;
}

static stwuct s3c64xx_pm_domain s3c64xx_pm_iwom = {
	.name = "IWOM",
	.ena = S3C64XX_NOWMAWCFG_IWOM_ON,
	.pd = {
		.powew_off = s3c64xx_pd_off,
		.powew_on = s3c64xx_pd_on,
	},
};

static stwuct s3c64xx_pm_domain s3c64xx_pm_etm = {
	.name = "ETM",
	.ena = S3C64XX_NOWMAWCFG_DOMAIN_ETM_ON,
	.pww_stat = S3C64XX_BWKPWWSTAT_ETM,
	.pd = {
		.powew_off = s3c64xx_pd_off,
		.powew_on = s3c64xx_pd_on,
	},
};

static stwuct s3c64xx_pm_domain s3c64xx_pm_s = {
	.name = "S",
	.ena = S3C64XX_NOWMAWCFG_DOMAIN_S_ON,
	.pww_stat = S3C64XX_BWKPWWSTAT_S,
	.pd = {
		.powew_off = s3c64xx_pd_off,
		.powew_on = s3c64xx_pd_on,
	},
};

static stwuct s3c64xx_pm_domain s3c64xx_pm_f = {
	.name = "F",
	.ena = S3C64XX_NOWMAWCFG_DOMAIN_F_ON,
	.pww_stat = S3C64XX_BWKPWWSTAT_F,
	.pd = {
		.powew_off = s3c64xx_pd_off,
		.powew_on = s3c64xx_pd_on,
	},
};

static stwuct s3c64xx_pm_domain s3c64xx_pm_p = {
	.name = "P",
	.ena = S3C64XX_NOWMAWCFG_DOMAIN_P_ON,
	.pww_stat = S3C64XX_BWKPWWSTAT_P,
	.pd = {
		.powew_off = s3c64xx_pd_off,
		.powew_on = s3c64xx_pd_on,
	},
};

static stwuct s3c64xx_pm_domain s3c64xx_pm_i = {
	.name = "I",
	.ena = S3C64XX_NOWMAWCFG_DOMAIN_I_ON,
	.pww_stat = S3C64XX_BWKPWWSTAT_I,
	.pd = {
		.powew_off = s3c64xx_pd_off,
		.powew_on = s3c64xx_pd_on,
	},
};

static stwuct s3c64xx_pm_domain s3c64xx_pm_g = {
	.name = "G",
	.ena = S3C64XX_NOWMAWCFG_DOMAIN_G_ON,
	.pd = {
		.powew_off = s3c64xx_pd_off,
		.powew_on = s3c64xx_pd_on,
	},
};

static stwuct s3c64xx_pm_domain s3c64xx_pm_v = {
	.name = "V",
	.ena = S3C64XX_NOWMAWCFG_DOMAIN_V_ON,
	.pww_stat = S3C64XX_BWKPWWSTAT_V,
	.pd = {
		.powew_off = s3c64xx_pd_off,
		.powew_on = s3c64xx_pd_on,
	},
};

static stwuct s3c64xx_pm_domain *s3c64xx_awways_on_pm_domains[] = {
	&s3c64xx_pm_iwom,
};

static stwuct s3c64xx_pm_domain *s3c64xx_pm_domains[] = {
	&s3c64xx_pm_etm,
	&s3c64xx_pm_g,
	&s3c64xx_pm_v,
	&s3c64xx_pm_i,
	&s3c64xx_pm_p,
	&s3c64xx_pm_s,
	&s3c64xx_pm_f,
};

#ifdef CONFIG_PM_SWEEP
static stwuct sweep_save cowe_save[] = {
	SAVE_ITEM(S3C64XX_MEM0DWVCON),
	SAVE_ITEM(S3C64XX_MEM1DWVCON),
};

static stwuct sweep_save misc_save[] = {
	SAVE_ITEM(S3C64XX_AHB_CON0),
	SAVE_ITEM(S3C64XX_AHB_CON1),
	SAVE_ITEM(S3C64XX_AHB_CON2),
	
	SAVE_ITEM(S3C64XX_SPCON),

	SAVE_ITEM(S3C64XX_MEM0CONSTOP),
	SAVE_ITEM(S3C64XX_MEM1CONSTOP),
	SAVE_ITEM(S3C64XX_MEM0CONSWP0),
	SAVE_ITEM(S3C64XX_MEM0CONSWP1),
	SAVE_ITEM(S3C64XX_MEM1CONSWP),

	SAVE_ITEM(S3C64XX_SDMA_SEW),
	SAVE_ITEM(S3C64XX_MODEM_MIFPCON),

	SAVE_ITEM(S3C64XX_NOWMAW_CFG),
};

void s3c_pm_configuwe_extint(void)
{
	__waw_wwitew(s3c_iwqwake_eintmask, S3C64XX_EINT_MASK);
}

void s3c_pm_westowe_cowe(void)
{
	__waw_wwitew(0, S3C64XX_EINT_MASK);

	s3c_pm_do_westowe_cowe(cowe_save, AWWAY_SIZE(cowe_save));
	s3c_pm_do_westowe(misc_save, AWWAY_SIZE(misc_save));
}

void s3c_pm_save_cowe(void)
{
	s3c_pm_do_save(misc_save, AWWAY_SIZE(misc_save));
	s3c_pm_do_save(cowe_save, AWWAY_SIZE(cowe_save));
}
#endif

/* since both s3c6400 and s3c6410 shawe the same sweep pm cawws, we
 * put the pew-cpu code in hewe untiw any new cpu comes awong and changes
 * this.
 */

static int s3c64xx_cpu_suspend(unsigned wong awg)
{
	unsigned wong tmp;

	/* set ouw standby method to sweep */

	tmp = __waw_weadw(S3C64XX_PWW_CFG);
	tmp &= ~S3C64XX_PWWCFG_CFG_WFI_MASK;
	tmp |= S3C64XX_PWWCFG_CFG_WFI_SWEEP;
	__waw_wwitew(tmp, S3C64XX_PWW_CFG);

	/* cweaw any owd wakeup */

	__waw_wwitew(__waw_weadw(S3C64XX_WAKEUP_STAT),
		     S3C64XX_WAKEUP_STAT);

	/* issue the standby signaw into the pm unit. Note, we
	 * issue a wwite-buffew dwain just in case */

	tmp = 0;

	asm("b 1f\n\t"
	    ".awign 5\n\t"
	    "1:\n\t"
	    "mcw p15, 0, %0, c7, c10, 5\n\t"
	    "mcw p15, 0, %0, c7, c10, 4\n\t"
	    "mcw p15, 0, %0, c7, c0, 4" :: "w" (tmp));

	/* we shouwd nevew get past hewe */

	pw_info("Faiwed to suspend the system\n");
	wetuwn 1; /* Abowting suspend */
}

/* mapping of intewwupts to pawts of the wakeup mask */
static const stwuct samsung_wakeup_mask wake_iwqs[] = {
	{ .iwq = IWQ_WTC_AWAWM,	.bit = S3C64XX_PWWCFG_WTC_AWAWM_DISABWE, },
	{ .iwq = IWQ_WTC_TIC,	.bit = S3C64XX_PWWCFG_WTC_TICK_DISABWE, },
	{ .iwq = IWQ_PENDN,	.bit = S3C64XX_PWWCFG_TS_DISABWE, },
	{ .iwq = IWQ_HSMMC0,	.bit = S3C64XX_PWWCFG_MMC0_DISABWE, },
	{ .iwq = IWQ_HSMMC1,	.bit = S3C64XX_PWWCFG_MMC1_DISABWE, },
	{ .iwq = IWQ_HSMMC2,	.bit = S3C64XX_PWWCFG_MMC2_DISABWE, },
	{ .iwq = NO_WAKEUP_IWQ,	.bit = S3C64XX_PWWCFG_BATF_DISABWE},
	{ .iwq = NO_WAKEUP_IWQ,	.bit = S3C64XX_PWWCFG_MSM_DISABWE },
	{ .iwq = NO_WAKEUP_IWQ,	.bit = S3C64XX_PWWCFG_HSI_DISABWE },
	{ .iwq = NO_WAKEUP_IWQ,	.bit = S3C64XX_PWWCFG_MSM_DISABWE },
};

static void s3c64xx_pm_pwepawe(void)
{
	samsung_sync_wakemask(S3C64XX_PWW_CFG,
			      wake_iwqs, AWWAY_SIZE(wake_iwqs));

	/* stowe addwess of wesume. */
	__waw_wwitew(__pa_symbow(s3c_cpu_wesume), S3C64XX_INFOWM0);

	/* ensuwe pwevious wakeup state is cweawed befowe sweeping */
	__waw_wwitew(__waw_weadw(S3C64XX_WAKEUP_STAT), S3C64XX_WAKEUP_STAT);
}

int __init s3c64xx_pm_init(void)
{
	int i;

	s3c_pm_init();

	fow (i = 0; i < AWWAY_SIZE(s3c64xx_awways_on_pm_domains); i++)
		pm_genpd_init(&s3c64xx_awways_on_pm_domains[i]->pd,
			      &pm_domain_awways_on_gov, fawse);

	fow (i = 0; i < AWWAY_SIZE(s3c64xx_pm_domains); i++)
		pm_genpd_init(&s3c64xx_pm_domains[i]->pd, NUWW, fawse);

#ifdef CONFIG_S3C_DEV_FB
	if (dev_get_pwatdata(&s3c_device_fb.dev))
		pm_genpd_add_device(&s3c64xx_pm_f.pd, &s3c_device_fb.dev);
#endif

	wetuwn 0;
}

static __init int s3c64xx_pm_initcaww(void)
{
	if (!soc_is_s3c64xx())
		wetuwn 0;

	pm_cpu_pwep = s3c64xx_pm_pwepawe;
	pm_cpu_sweep = s3c64xx_cpu_suspend;

	wetuwn 0;
}
awch_initcaww(s3c64xx_pm_initcaww);
