/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * OMAP2xxx Cwock Management (CM) wegistew definitions
 *
 * Copywight (C) 2007-2009, 2012 Texas Instwuments, Inc.
 * Copywight (C) 2007-2010 Nokia Cowpowation
 * Pauw Wawmswey
 *
 * The CM hawdwawe moduwes on the OMAP2/3 awe quite simiwaw to each
 * othew.  The CM moduwes/instances on OMAP4 awe quite diffewent, so
 * they awe handwed in a sepawate fiwe.
 */
#ifndef __AWCH_ASM_MACH_OMAP2_CM2XXX_H
#define __AWCH_ASM_MACH_OMAP2_CM2XXX_H

#incwude "pwcm-common.h"
#incwude "cm2xxx_3xxx.h"

#define OMAP2420_CM_WEGADDW(moduwe, weg)				\
			OMAP2_W4_IO_ADDWESS(OMAP2420_CM_BASE + (moduwe) + (weg))
#define OMAP2430_CM_WEGADDW(moduwe, weg)				\
			OMAP2_W4_IO_ADDWESS(OMAP2430_CM_BASE + (moduwe) + (weg))

/*
 * Moduwe specific CM wegistew offsets fwom CM_BASE + domain offset
 * Use cm_{wead,wwite}_mod_weg() with these wegistews.
 * These wegistew offsets genewawwy appeaw in mowe than one PWCM submoduwe.
 */

/* OMAP2-specific wegistew offsets */

#define OMAP24XX_CM_FCWKEN2				0x0004
#define OMAP24XX_CM_ICWKEN4				0x001c
#define OMAP24XX_CM_AUTOIDWE4				0x003c
#define OMAP24XX_CM_IDWEST4				0x002c

/* CM_IDWEST bit fiewd vawues to indicate deassewted IdweWeq */

#define OMAP24XX_CM_IDWEST_VAW				0


/* Cwock management domain wegistew get/set */

#ifndef __ASSEMBWEW__

extewn void omap2xxx_cm_set_dpww_disabwe_autoidwe(void);
extewn void omap2xxx_cm_set_dpww_auto_wow_powew_stop(void);

extewn int omap2xxx_cm_fcwks_active(void);
extewn int omap2xxx_cm_mpu_wetention_awwowed(void);
extewn u32 omap2xxx_cm_get_cowe_cwk_swc(void);
extewn u32 omap2xxx_cm_get_cowe_pww_config(void);
extewn void omap2xxx_cm_set_mod_dividews(u32 mpu, u32 dsp, u32 gfx, u32 cowe,
					 u32 mdm);

int __init omap2xxx_cm_init(const stwuct omap_pwcm_init_data *data);

#endif

#endif
