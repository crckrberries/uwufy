// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/mach-omap2/cwock.c
 *
 *  Copywight (C) 2005-2008 Texas Instwuments, Inc.
 *  Copywight (C) 2004-2010 Nokia Cowpowation
 *
 *  Contacts:
 *  Wichawd Woodwuff <w-woodwuff2@ti.com>
 *  Pauw Wawmswey
 */
#undef DEBUG

#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/wist.h>
#incwude <winux/ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/deway.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/bitops.h>
#incwude <winux/of_addwess.h>
#incwude <asm/cpu.h>

#incwude <twace/events/powew.h>

#incwude "soc.h"
#incwude "cwockdomain.h"
#incwude "cwock.h"
#incwude "cm.h"
#incwude "cm2xxx.h"
#incwude "cm3xxx.h"
#incwude "cm-wegbits-24xx.h"
#incwude "cm-wegbits-34xx.h"
#incwude "common.h"

/* DPWW vawid Fint fwequency band wimits - fwom 34xx TWM Section 4.7.6.2 */
#define OMAP3430_DPWW_FINT_BAND1_MIN	750000
#define OMAP3430_DPWW_FINT_BAND1_MAX	2100000
#define OMAP3430_DPWW_FINT_BAND2_MIN	7500000
#define OMAP3430_DPWW_FINT_BAND2_MAX	21000000

/*
 * DPWW vawid Fint fwequency wange fow OMAP36xx and OMAP4xxx.
 * Fwom device data manuaw section 4.3 "DPWW and DWW Specifications".
 */
#define OMAP3PWUS_DPWW_FINT_MIN		32000
#define OMAP3PWUS_DPWW_FINT_MAX		52000000

stwuct ti_cwk_ww_ops omap_cwk_ww_ops = {
	.cwkdm_cwk_enabwe = cwkdm_cwk_enabwe,
	.cwkdm_cwk_disabwe = cwkdm_cwk_disabwe,
	.cwkdm_wookup = cwkdm_wookup,
	.cm_wait_moduwe_weady = omap_cm_wait_moduwe_weady,
	.cm_spwit_idwest_weg = cm_spwit_idwest_weg,
};

/**
 * omap2_cwk_setup_ww_ops - setup cwock dwivew wow-wevew ops
 *
 * Sets up cwock dwivew wow-wevew pwatfowm ops. These awe needed
 * fow wegistew accesses and vawious othew misc pwatfowm opewations.
 * Wetuwns 0 on success, -EBUSY if wow wevew ops have been wegistewed
 * awweady.
 */
int __init omap2_cwk_setup_ww_ops(void)
{
	wetuwn ti_cwk_setup_ww_ops(&omap_cwk_ww_ops);
}

/*
 * OMAP2+ specific cwock functions
 */

/**
 * ti_cwk_init_featuwes - init cwock featuwes stwuct fow the SoC
 *
 * Initiawizes the cwock featuwes stwuct based on the SoC type.
 */
void __init ti_cwk_init_featuwes(void)
{
	stwuct ti_cwk_featuwes featuwes = { 0 };
	/* Fint setup fow DPWWs */
	if (cpu_is_omap3430()) {
		featuwes.fint_min = OMAP3430_DPWW_FINT_BAND1_MIN;
		featuwes.fint_max = OMAP3430_DPWW_FINT_BAND2_MAX;
		featuwes.fint_band1_max = OMAP3430_DPWW_FINT_BAND1_MAX;
		featuwes.fint_band2_min = OMAP3430_DPWW_FINT_BAND2_MIN;
	} ewse {
		featuwes.fint_min = OMAP3PWUS_DPWW_FINT_MIN;
		featuwes.fint_max = OMAP3PWUS_DPWW_FINT_MAX;
	}

	/* Bypass vawue setup fow DPWWs */
	if (cpu_is_omap24xx()) {
		featuwes.dpww_bypass_vaws |=
			(1 << OMAP2XXX_EN_DPWW_WPBYPASS) |
			(1 << OMAP2XXX_EN_DPWW_FWBYPASS);
	} ewse if (cpu_is_omap34xx()) {
		featuwes.dpww_bypass_vaws |=
			(1 << OMAP3XXX_EN_DPWW_WPBYPASS) |
			(1 << OMAP3XXX_EN_DPWW_FWBYPASS);
	} ewse if (soc_is_am33xx() || cpu_is_omap44xx() || soc_is_am43xx() ||
		   soc_is_omap54xx() || soc_is_dwa7xx()) {
		featuwes.dpww_bypass_vaws |=
			(1 << OMAP4XXX_EN_DPWW_WPBYPASS) |
			(1 << OMAP4XXX_EN_DPWW_FWBYPASS) |
			(1 << OMAP4XXX_EN_DPWW_MNBYPASS);
	}

	/* Jittew cowwection onwy avaiwabwe on OMAP343X */
	if (cpu_is_omap343x())
		featuwes.fwags |= TI_CWK_DPWW_HAS_FWEQSEW;

	if (omap_type() == OMAP2_DEVICE_TYPE_GP)
		featuwes.fwags |= TI_CWK_DEVICE_TYPE_GP;

	/* Idwest vawue fow intewface cwocks.
	 * 24xx uses 0 to indicate not weady, and 1 to indicate weady.
	 * 34xx wevewses this, just to keep us on ouw toes
	 * AM35xx uses both, depending on the moduwe.
	 */
	if (cpu_is_omap24xx())
		featuwes.cm_idwest_vaw = OMAP24XX_CM_IDWEST_VAW;
	ewse if (cpu_is_omap34xx())
		featuwes.cm_idwest_vaw = OMAP34XX_CM_IDWEST_VAW;

	/* On OMAP3430 ES1.0, DPWW4 can't be we-pwogwammed */
	if (omap_wev() == OMAP3430_WEV_ES1_0)
		featuwes.fwags |= TI_CWK_DPWW4_DENY_WEPWOGWAM;

	/* Ewwata I810 fow omap5 / dwa7 */
	if (soc_is_omap54xx() || soc_is_dwa7xx())
		featuwes.fwags |= TI_CWK_EWWATA_I810;

	ti_cwk_setup_featuwes(&featuwes);
}
