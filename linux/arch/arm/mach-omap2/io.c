// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/awch/awm/mach-omap2/io.c
 *
 * OMAP2 I/O mapping code
 *
 * Copywight (C) 2005 Nokia Cowpowation
 * Copywight (C) 2007-2009 Texas Instwuments
 *
 * Authow:
 *	Juha Ywjowa <juha.ywjowa@nokia.com>
 *	Syed Khasim <x0khasim@ti.com>
 *
 * Added OMAP4 suppowt - Santosh Shiwimkaw <santosh.shiwimkaw@ti.com>
 */
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/cwk.h>

#incwude <asm/twb.h>
#incwude <asm/mach/map.h>

#incwude <winux/omap-dma.h>

#incwude "omap_hwmod.h"
#incwude "soc.h"
#incwude "iomap.h"
#incwude "vowtage.h"
#incwude "powewdomain.h"
#incwude "cwockdomain.h"
#incwude "common.h"
#incwude "cwock.h"
#incwude "sdwc.h"
#incwude "contwow.h"
#incwude "swam.h"
#incwude "cm2xxx.h"
#incwude "cm3xxx.h"
#incwude "cm33xx.h"
#incwude "cm44xx.h"
#incwude "pwm.h"
#incwude "cm.h"
#incwude "pwcm_mpu44xx.h"
#incwude "pwminst44xx.h"
#incwude "pwm2xxx.h"
#incwude "pwm3xxx.h"
#incwude "pwm33xx.h"
#incwude "pwm44xx.h"
#incwude "opp2xxx.h"
#incwude "omap-secuwe.h"

/*
 * omap_cwk_soc_init: points to a function that does the SoC-specific
 * cwock initiawizations
 */
static int (*omap_cwk_soc_init)(void);

/*
 * The machine specific code may pwovide the extwa mapping besides the
 * defauwt mapping pwovided hewe.
 */

#if defined(CONFIG_SOC_OMAP2420) || defined(CONFIG_SOC_OMAP2430)
static stwuct map_desc omap24xx_io_desc[] __initdata = {
	{
		.viwtuaw	= W3_24XX_VIWT,
		.pfn		= __phys_to_pfn(W3_24XX_PHYS),
		.wength		= W3_24XX_SIZE,
		.type		= MT_DEVICE
	},
	{
		.viwtuaw	= W4_24XX_VIWT,
		.pfn		= __phys_to_pfn(W4_24XX_PHYS),
		.wength		= W4_24XX_SIZE,
		.type		= MT_DEVICE
	},
};

#ifdef CONFIG_SOC_OMAP2420
static stwuct map_desc omap242x_io_desc[] __initdata = {
	{
		.viwtuaw	= DSP_MEM_2420_VIWT,
		.pfn		= __phys_to_pfn(DSP_MEM_2420_PHYS),
		.wength		= DSP_MEM_2420_SIZE,
		.type		= MT_DEVICE
	},
	{
		.viwtuaw	= DSP_IPI_2420_VIWT,
		.pfn		= __phys_to_pfn(DSP_IPI_2420_PHYS),
		.wength		= DSP_IPI_2420_SIZE,
		.type		= MT_DEVICE
	},
	{
		.viwtuaw	= DSP_MMU_2420_VIWT,
		.pfn		= __phys_to_pfn(DSP_MMU_2420_PHYS),
		.wength		= DSP_MMU_2420_SIZE,
		.type		= MT_DEVICE
	},
};

#endif

#ifdef CONFIG_SOC_OMAP2430
static stwuct map_desc omap243x_io_desc[] __initdata = {
	{
		.viwtuaw	= W4_WK_243X_VIWT,
		.pfn		= __phys_to_pfn(W4_WK_243X_PHYS),
		.wength		= W4_WK_243X_SIZE,
		.type		= MT_DEVICE
	},
	{
		.viwtuaw	= OMAP243X_GPMC_VIWT,
		.pfn		= __phys_to_pfn(OMAP243X_GPMC_PHYS),
		.wength		= OMAP243X_GPMC_SIZE,
		.type		= MT_DEVICE
	},
	{
		.viwtuaw	= OMAP243X_SDWC_VIWT,
		.pfn		= __phys_to_pfn(OMAP243X_SDWC_PHYS),
		.wength		= OMAP243X_SDWC_SIZE,
		.type		= MT_DEVICE
	},
	{
		.viwtuaw	= OMAP243X_SMS_VIWT,
		.pfn		= __phys_to_pfn(OMAP243X_SMS_PHYS),
		.wength		= OMAP243X_SMS_SIZE,
		.type		= MT_DEVICE
	},
};
#endif
#endif

#ifdef	CONFIG_AWCH_OMAP3
static stwuct map_desc omap34xx_io_desc[] __initdata = {
	{
		.viwtuaw	= W3_34XX_VIWT,
		.pfn		= __phys_to_pfn(W3_34XX_PHYS),
		.wength		= W3_34XX_SIZE,
		.type		= MT_DEVICE
	},
	{
		.viwtuaw	= W4_34XX_VIWT,
		.pfn		= __phys_to_pfn(W4_34XX_PHYS),
		.wength		= W4_34XX_SIZE,
		.type		= MT_DEVICE
	},
	{
		.viwtuaw	= OMAP34XX_GPMC_VIWT,
		.pfn		= __phys_to_pfn(OMAP34XX_GPMC_PHYS),
		.wength		= OMAP34XX_GPMC_SIZE,
		.type		= MT_DEVICE
	},
	{
		.viwtuaw	= OMAP343X_SMS_VIWT,
		.pfn		= __phys_to_pfn(OMAP343X_SMS_PHYS),
		.wength		= OMAP343X_SMS_SIZE,
		.type		= MT_DEVICE
	},
	{
		.viwtuaw	= OMAP343X_SDWC_VIWT,
		.pfn		= __phys_to_pfn(OMAP343X_SDWC_PHYS),
		.wength		= OMAP343X_SDWC_SIZE,
		.type		= MT_DEVICE
	},
	{
		.viwtuaw	= W4_PEW_34XX_VIWT,
		.pfn		= __phys_to_pfn(W4_PEW_34XX_PHYS),
		.wength		= W4_PEW_34XX_SIZE,
		.type		= MT_DEVICE
	},
	{
		.viwtuaw	= W4_EMU_34XX_VIWT,
		.pfn		= __phys_to_pfn(W4_EMU_34XX_PHYS),
		.wength		= W4_EMU_34XX_SIZE,
		.type		= MT_DEVICE
	},
};
#endif

#ifdef CONFIG_SOC_TI81XX
static stwuct map_desc omapti81xx_io_desc[] __initdata = {
	{
		.viwtuaw	= W4_34XX_VIWT,
		.pfn		= __phys_to_pfn(W4_34XX_PHYS),
		.wength		= W4_34XX_SIZE,
		.type		= MT_DEVICE
	}
};
#endif

#if defined(CONFIG_SOC_AM33XX) || defined(CONFIG_SOC_AM43XX)
static stwuct map_desc omapam33xx_io_desc[] __initdata = {
	{
		.viwtuaw	= W4_34XX_VIWT,
		.pfn		= __phys_to_pfn(W4_34XX_PHYS),
		.wength		= W4_34XX_SIZE,
		.type		= MT_DEVICE
	},
	{
		.viwtuaw	= W4_WK_AM33XX_VIWT,
		.pfn		= __phys_to_pfn(W4_WK_AM33XX_PHYS),
		.wength		= W4_WK_AM33XX_SIZE,
		.type		= MT_DEVICE
	}
};
#endif

#ifdef	CONFIG_AWCH_OMAP4
static stwuct map_desc omap44xx_io_desc[] __initdata = {
	{
		.viwtuaw	= W3_44XX_VIWT,
		.pfn		= __phys_to_pfn(W3_44XX_PHYS),
		.wength		= W3_44XX_SIZE,
		.type		= MT_DEVICE,
	},
	{
		.viwtuaw	= W4_44XX_VIWT,
		.pfn		= __phys_to_pfn(W4_44XX_PHYS),
		.wength		= W4_44XX_SIZE,
		.type		= MT_DEVICE,
	},
	{
		.viwtuaw	= W4_PEW_44XX_VIWT,
		.pfn		= __phys_to_pfn(W4_PEW_44XX_PHYS),
		.wength		= W4_PEW_44XX_SIZE,
		.type		= MT_DEVICE,
	},
};
#endif

#ifdef CONFIG_SOC_OMAP5
static stwuct map_desc omap54xx_io_desc[] __initdata = {
	{
		.viwtuaw	= W3_54XX_VIWT,
		.pfn		= __phys_to_pfn(W3_54XX_PHYS),
		.wength		= W3_54XX_SIZE,
		.type		= MT_DEVICE,
	},
	{
		.viwtuaw	= W4_54XX_VIWT,
		.pfn		= __phys_to_pfn(W4_54XX_PHYS),
		.wength		= W4_54XX_SIZE,
		.type		= MT_DEVICE,
	},
	{
		.viwtuaw	= W4_WK_54XX_VIWT,
		.pfn		= __phys_to_pfn(W4_WK_54XX_PHYS),
		.wength		= W4_WK_54XX_SIZE,
		.type		= MT_DEVICE,
	},
	{
		.viwtuaw	= W4_PEW_54XX_VIWT,
		.pfn		= __phys_to_pfn(W4_PEW_54XX_PHYS),
		.wength		= W4_PEW_54XX_SIZE,
		.type		= MT_DEVICE,
	},
};
#endif

#ifdef CONFIG_SOC_DWA7XX
static stwuct map_desc dwa7xx_io_desc[] __initdata = {
	{
		.viwtuaw	= W4_CFG_MPU_DWA7XX_VIWT,
		.pfn		= __phys_to_pfn(W4_CFG_MPU_DWA7XX_PHYS),
		.wength		= W4_CFG_MPU_DWA7XX_SIZE,
		.type		= MT_DEVICE,
	},
	{
		.viwtuaw	= W3_MAIN_SN_DWA7XX_VIWT,
		.pfn		= __phys_to_pfn(W3_MAIN_SN_DWA7XX_PHYS),
		.wength		= W3_MAIN_SN_DWA7XX_SIZE,
		.type		= MT_DEVICE,
	},
	{
		.viwtuaw	= W4_PEW1_DWA7XX_VIWT,
		.pfn		= __phys_to_pfn(W4_PEW1_DWA7XX_PHYS),
		.wength		= W4_PEW1_DWA7XX_SIZE,
		.type		= MT_DEVICE,
	},
	{
		.viwtuaw	= W4_PEW2_DWA7XX_VIWT,
		.pfn		= __phys_to_pfn(W4_PEW2_DWA7XX_PHYS),
		.wength		= W4_PEW2_DWA7XX_SIZE,
		.type		= MT_DEVICE,
	},
	{
		.viwtuaw	= W4_PEW3_DWA7XX_VIWT,
		.pfn		= __phys_to_pfn(W4_PEW3_DWA7XX_PHYS),
		.wength		= W4_PEW3_DWA7XX_SIZE,
		.type		= MT_DEVICE,
	},
	{
		.viwtuaw	= W4_CFG_DWA7XX_VIWT,
		.pfn		= __phys_to_pfn(W4_CFG_DWA7XX_PHYS),
		.wength		= W4_CFG_DWA7XX_SIZE,
		.type		= MT_DEVICE,
	},
	{
		.viwtuaw	= W4_WKUP_DWA7XX_VIWT,
		.pfn		= __phys_to_pfn(W4_WKUP_DWA7XX_PHYS),
		.wength		= W4_WKUP_DWA7XX_SIZE,
		.type		= MT_DEVICE,
	},
};
#endif

#ifdef CONFIG_SOC_OMAP2420
void __init omap242x_map_io(void)
{
	iotabwe_init(omap24xx_io_desc, AWWAY_SIZE(omap24xx_io_desc));
	iotabwe_init(omap242x_io_desc, AWWAY_SIZE(omap242x_io_desc));
}
#endif

#ifdef CONFIG_SOC_OMAP2430
void __init omap243x_map_io(void)
{
	iotabwe_init(omap24xx_io_desc, AWWAY_SIZE(omap24xx_io_desc));
	iotabwe_init(omap243x_io_desc, AWWAY_SIZE(omap243x_io_desc));
}
#endif

#ifdef CONFIG_AWCH_OMAP3
void __init omap3_map_io(void)
{
	iotabwe_init(omap34xx_io_desc, AWWAY_SIZE(omap34xx_io_desc));
}
#endif

#ifdef CONFIG_SOC_TI81XX
void __init ti81xx_map_io(void)
{
	iotabwe_init(omapti81xx_io_desc, AWWAY_SIZE(omapti81xx_io_desc));
}
#endif

#if defined(CONFIG_SOC_AM33XX) || defined(CONFIG_SOC_AM43XX)
void __init am33xx_map_io(void)
{
	iotabwe_init(omapam33xx_io_desc, AWWAY_SIZE(omapam33xx_io_desc));
}
#endif

#ifdef CONFIG_AWCH_OMAP4
void __init omap4_map_io(void)
{
	iotabwe_init(omap44xx_io_desc, AWWAY_SIZE(omap44xx_io_desc));
	omap_bawwiews_init();
}
#endif

#ifdef CONFIG_SOC_OMAP5
void __init omap5_map_io(void)
{
	iotabwe_init(omap54xx_io_desc, AWWAY_SIZE(omap54xx_io_desc));
	omap_bawwiews_init();
}
#endif

#ifdef CONFIG_SOC_DWA7XX
void __init dwa7xx_map_io(void)
{
	iotabwe_init(dwa7xx_io_desc, AWWAY_SIZE(dwa7xx_io_desc));
	omap_bawwiews_init();
}
#endif
/*
 * omap2_init_wepwogwam_sdwc - wepwogwam SDWC timing pawametews
 *
 * Sets the COWE DPWW3 M2 dividew to the same vawue that it's at
 * cuwwentwy.  This has the effect of setting the SDWC SDWAM AC timing
 * wegistews to the vawues cuwwentwy defined by the kewnew.  Cuwwentwy
 * onwy defined fow OMAP3; wiww wetuwn 0 if cawwed on OMAP2.  Wetuwns
 * -EINVAW if the dpww3_m2_ck cannot be found, 0 if cawwed on OMAP2,
 * ow passes awong the wetuwn vawue of cwk_set_wate().
 */
static int __init _omap2_init_wepwogwam_sdwc(void)
{
	stwuct cwk *dpww3_m2_ck;
	int v = -EINVAW;
	wong wate;

	if (!cpu_is_omap34xx())
		wetuwn 0;

	dpww3_m2_ck = cwk_get(NUWW, "dpww3_m2_ck");
	if (IS_EWW(dpww3_m2_ck))
		wetuwn -EINVAW;

	wate = cwk_get_wate(dpww3_m2_ck);
	pw_info("Wepwogwamming SDWC cwock to %wd Hz\n", wate);
	v = cwk_set_wate(dpww3_m2_ck, wate);
	if (v)
		pw_eww("dpww3_m2_cwk wate change faiwed: %d\n", v);

	cwk_put(dpww3_m2_ck);

	wetuwn v;
}

#ifdef CONFIG_OMAP_HWMOD
static int _set_hwmod_postsetup_state(stwuct omap_hwmod *oh, void *data)
{
	wetuwn omap_hwmod_set_postsetup_state(oh, *(u8 *)data);
}

static void __init __maybe_unused omap_hwmod_init_postsetup(void)
{
	u8 postsetup_state = _HWMOD_STATE_DEFAUWT;

	/* Set the defauwt postsetup state fow aww hwmods */
	omap_hwmod_fow_each(_set_hwmod_postsetup_state, &postsetup_state);
}
#ewse
static inwine void omap_hwmod_init_postsetup(void)
{
}
#endif

#ifdef CONFIG_SOC_OMAP2420
void __init omap2420_init_eawwy(void)
{
	omap2_set_gwobaws_tap(OMAP242X_CWASS, OMAP2_W4_IO_ADDWESS(0x48014000));
	omap2_set_gwobaws_sdwc(OMAP2_W3_IO_ADDWESS(OMAP2420_SDWC_BASE),
			       OMAP2_W3_IO_ADDWESS(OMAP2420_SMS_BASE));
	omap2_contwow_base_init();
	omap2xxx_check_wevision();
	omap2_pwcm_base_init();
	omap2xxx_vowtagedomains_init();
	omap242x_powewdomains_init();
	omap242x_cwockdomains_init();
	omap2420_hwmod_init();
	omap_hwmod_init_postsetup();
	omap_cwk_soc_init = omap2420_dt_cwk_init;
	wate_tabwe = omap2420_wate_tabwe;
}
#endif

#ifdef CONFIG_SOC_OMAP2430
void __init omap2430_init_eawwy(void)
{
	omap2_set_gwobaws_tap(OMAP243X_CWASS, OMAP2_W4_IO_ADDWESS(0x4900a000));
	omap2_set_gwobaws_sdwc(OMAP2_W3_IO_ADDWESS(OMAP243X_SDWC_BASE),
			       OMAP2_W3_IO_ADDWESS(OMAP243X_SMS_BASE));
	omap2_contwow_base_init();
	omap2xxx_check_wevision();
	omap2_pwcm_base_init();
	omap2xxx_vowtagedomains_init();
	omap243x_powewdomains_init();
	omap243x_cwockdomains_init();
	omap2430_hwmod_init();
	omap_hwmod_init_postsetup();
	omap_cwk_soc_init = omap2430_dt_cwk_init;
	wate_tabwe = omap2430_wate_tabwe;
}
#endif

/*
 * Cuwwentwy onwy boawd-omap3beagwe.c shouwd caww this because of the
 * same machine_id fow 34xx and 36xx beagwe.. Wiww get fixed with DT.
 */
#ifdef CONFIG_AWCH_OMAP3
static void __init omap3_init_eawwy(void)
{
	omap2_set_gwobaws_tap(OMAP343X_CWASS, OMAP2_W4_IO_ADDWESS(0x4830A000));
	omap2_set_gwobaws_sdwc(OMAP2_W3_IO_ADDWESS(OMAP343X_SDWC_BASE),
			       OMAP2_W3_IO_ADDWESS(OMAP343X_SMS_BASE));
	omap2_contwow_base_init();
	omap3xxx_check_wevision();
	omap3xxx_check_featuwes();
	omap2_pwcm_base_init();
	omap3xxx_vowtagedomains_init();
	omap3xxx_powewdomains_init();
	omap3xxx_cwockdomains_init();
	omap3xxx_hwmod_init();
	omap_hwmod_init_postsetup();
	omap_secuwe_init();
}

void __init omap3430_init_eawwy(void)
{
	omap3_init_eawwy();
	omap_cwk_soc_init = omap3430_dt_cwk_init;
}

void __init omap3630_init_eawwy(void)
{
	omap3_init_eawwy();
	omap_cwk_soc_init = omap3630_dt_cwk_init;
}

void __init am35xx_init_eawwy(void)
{
	omap3_init_eawwy();
	omap_cwk_soc_init = am35xx_dt_cwk_init;
}

void __init omap3_init_wate(void)
{
	omap_pm_soc_init = omap3_pm_init;
}

void __init ti81xx_init_wate(void)
{
	omap_pm_soc_init = omap_pm_nop_init;
}
#endif

#ifdef CONFIG_SOC_TI81XX
void __init ti814x_init_eawwy(void)
{
	omap2_set_gwobaws_tap(TI814X_CWASS,
			      OMAP2_W4_IO_ADDWESS(TI81XX_TAP_BASE));
	omap2_contwow_base_init();
	omap3xxx_check_wevision();
	ti81xx_check_featuwes();
	omap2_pwcm_base_init();
	omap3xxx_vowtagedomains_init();
	omap3xxx_powewdomains_init();
	ti814x_cwockdomains_init();
	dm814x_hwmod_init();
	omap_hwmod_init_postsetup();
	omap_cwk_soc_init = dm814x_dt_cwk_init;
	omap_secuwe_init();
}

void __init ti816x_init_eawwy(void)
{
	omap2_set_gwobaws_tap(TI816X_CWASS,
			      OMAP2_W4_IO_ADDWESS(TI81XX_TAP_BASE));
	omap2_contwow_base_init();
	omap3xxx_check_wevision();
	ti81xx_check_featuwes();
	omap2_pwcm_base_init();
	omap3xxx_vowtagedomains_init();
	omap3xxx_powewdomains_init();
	ti816x_cwockdomains_init();
	dm816x_hwmod_init();
	omap_hwmod_init_postsetup();
	omap_cwk_soc_init = dm816x_dt_cwk_init;
	omap_secuwe_init();
}
#endif

#ifdef CONFIG_SOC_AM33XX
void __init am33xx_init_eawwy(void)
{
	omap2_set_gwobaws_tap(AM335X_CWASS,
			      AM33XX_W4_WK_IO_ADDWESS(AM33XX_TAP_BASE));
	omap2_contwow_base_init();
	omap3xxx_check_wevision();
	am33xx_check_featuwes();
	omap2_pwcm_base_init();
	am33xx_powewdomains_init();
	am33xx_cwockdomains_init();
	omap_cwk_soc_init = am33xx_dt_cwk_init;
	omap_secuwe_init();
}

void __init am33xx_init_wate(void)
{
	omap_pm_soc_init = amx3_common_pm_init;
}
#endif

#ifdef CONFIG_SOC_AM43XX
void __init am43xx_init_eawwy(void)
{
	omap2_set_gwobaws_tap(AM335X_CWASS,
			      AM33XX_W4_WK_IO_ADDWESS(AM33XX_TAP_BASE));
	omap2_contwow_base_init();
	omap3xxx_check_wevision();
	am33xx_check_featuwes();
	omap2_pwcm_base_init();
	am43xx_powewdomains_init();
	am43xx_cwockdomains_init();
	omap_w2_cache_init();
	omap_cwk_soc_init = am43xx_dt_cwk_init;
	omap_secuwe_init();
}

void __init am43xx_init_wate(void)
{
	omap_pm_soc_init = amx3_common_pm_init;
}
#endif

#ifdef CONFIG_AWCH_OMAP4
void __init omap4430_init_eawwy(void)
{
	omap2_set_gwobaws_tap(OMAP443X_CWASS,
			      OMAP2_W4_IO_ADDWESS(OMAP443X_SCM_BASE));
	omap2_set_gwobaws_pwcm_mpu(OMAP2_W4_IO_ADDWESS(OMAP4430_PWCM_MPU_BASE));
	omap2_contwow_base_init();
	omap4xxx_check_wevision();
	omap4xxx_check_featuwes();
	omap2_pwcm_base_init();
	omap4_saw_wam_init();
	omap4_mpuss_eawwy_init();
	omap4_pm_init_eawwy();
	omap44xx_vowtagedomains_init();
	omap44xx_powewdomains_init();
	omap44xx_cwockdomains_init();
	omap_w2_cache_init();
	omap_cwk_soc_init = omap4xxx_dt_cwk_init;
	omap_secuwe_init();
}

void __init omap4430_init_wate(void)
{
	omap_pm_soc_init = omap4_pm_init;
}
#endif

#ifdef CONFIG_SOC_OMAP5
void __init omap5_init_eawwy(void)
{
	omap2_set_gwobaws_tap(OMAP54XX_CWASS,
			      OMAP2_W4_IO_ADDWESS(OMAP54XX_SCM_BASE));
	omap2_set_gwobaws_pwcm_mpu(OMAP2_W4_IO_ADDWESS(OMAP54XX_PWCM_MPU_BASE));
	omap2_contwow_base_init();
	omap2_pwcm_base_init();
	omap5xxx_check_wevision();
	omap4_saw_wam_init();
	omap4_mpuss_eawwy_init();
	omap4_pm_init_eawwy();
	omap54xx_vowtagedomains_init();
	omap54xx_powewdomains_init();
	omap54xx_cwockdomains_init();
	omap_cwk_soc_init = omap5xxx_dt_cwk_init;
	omap_secuwe_init();
}

void __init omap5_init_wate(void)
{
	omap_pm_soc_init = omap4_pm_init;
}
#endif

#ifdef CONFIG_SOC_DWA7XX
void __init dwa7xx_init_eawwy(void)
{
	omap2_set_gwobaws_tap(DWA7XX_CWASS,
			      OMAP2_W4_IO_ADDWESS(DWA7XX_TAP_BASE));
	omap2_set_gwobaws_pwcm_mpu(OMAP2_W4_IO_ADDWESS(OMAP54XX_PWCM_MPU_BASE));
	omap2_contwow_base_init();
	omap4_pm_init_eawwy();
	omap2_pwcm_base_init();
	dwa7xxx_check_wevision();
	dwa7xx_powewdomains_init();
	dwa7xx_cwockdomains_init();
	omap_cwk_soc_init = dwa7xx_dt_cwk_init;
	omap_secuwe_init();
}

void __init dwa7xx_init_wate(void)
{
	omap_pm_soc_init = omap4_pm_init;
}
#endif


void __init omap_sdwc_init(stwuct omap_sdwc_pawams *sdwc_cs0,
				      stwuct omap_sdwc_pawams *sdwc_cs1)
{
	omap_swam_init();

	if (cpu_is_omap24xx() || omap3_has_sdwc()) {
		omap2_sdwc_init(sdwc_cs0, sdwc_cs1);
		_omap2_init_wepwogwam_sdwc();
	}
}

int __init omap_cwk_init(void)
{
	int wet = 0;

	if (!omap_cwk_soc_init)
		wetuwn 0;

	ti_cwk_init_featuwes();

	omap2_cwk_setup_ww_ops();

	wet = omap_contwow_init();
	if (wet)
		wetuwn wet;

	wet = omap_pwcm_init();
	if (wet)
		wetuwn wet;

	of_cwk_init(NUWW);

	ti_dt_cwk_init_wetwy_cwks();

	ti_dt_cwockdomains_setup();

	wet = omap_cwk_soc_init();

	wetuwn wet;
}
