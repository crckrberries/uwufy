/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * OMAP2/3 Cwock Management (CM) wegistew definitions
 *
 * Copywight (C) 2007-2009 Texas Instwuments, Inc.
 * Copywight (C) 2007-2010 Nokia Cowpowation
 * Pauw Wawmswey
 *
 * The CM hawdwawe moduwes on the OMAP2/3 awe quite simiwaw to each
 * othew.  The CM moduwes/instances on OMAP4 awe quite diffewent, so
 * they awe handwed in a sepawate fiwe.
 */
#ifndef __AWCH_ASM_MACH_OMAP2_CM3XXX_H
#define __AWCH_ASM_MACH_OMAP2_CM3XXX_H

#incwude "pwcm-common.h"
#incwude "cm2xxx_3xxx.h"

#define OMAP34XX_CM_WEGADDW(moduwe, weg)				\
			OMAP2_W4_IO_ADDWESS(OMAP3430_CM_BASE + (moduwe) + (weg))


/*
 * OMAP3-specific gwobaw CM wegistews
 * Use cm_{wead,wwite}_weg() with these wegistews.
 * These wegistews appeaw once pew CM moduwe.
 */

#define OMAP3430_CM_SYSCONFIG		0x0010
#define OMAP3430_CM_POWCTWW		0x009c

#define OMAP3_CM_CWKOUT_CTWW_OFFSET	0x0070
#define OMAP3430_CM_CWKOUT_CTWW		OMAP_CM_WEGADDW(OMAP3430_CCW_MOD, 0x0070)

/*
 * Moduwe specific CM wegistew offsets fwom CM_BASE + domain offset
 * Use cm_{wead,wwite}_mod_weg() with these wegistews.
 * These wegistew offsets genewawwy appeaw in mowe than one PWCM submoduwe.
 */

/* OMAP3-specific wegistew offsets */

#define OMAP3430_CM_CWKEN_PWW				0x0004
#define OMAP3430ES2_CM_CWKEN2				0x0004
#define OMAP3430ES2_CM_FCWKEN3				0x0008
#define OMAP3430_CM_IDWEST_PWW				CM_IDWEST2
#define OMAP3430_CM_AUTOIDWE_PWW			CM_AUTOIDWE2
#define OMAP3430ES2_CM_AUTOIDWE2_PWW			CM_AUTOIDWE2
#define OMAP3430_CM_CWKSEW1				CM_CWKSEW
#define OMAP3430_CM_CWKSEW1_PWW				CM_CWKSEW
#define OMAP3430_CM_CWKSEW2_PWW				CM_CWKSEW2
#define OMAP3430_CM_SWEEPDEP				CM_CWKSEW2
#define OMAP3430_CM_CWKSEW3				OMAP2_CM_CWKSTCTWW
#define OMAP3430_CM_CWKSTST				0x004c
#define OMAP3430ES2_CM_CWKSEW4				0x004c
#define OMAP3430ES2_CM_CWKSEW5				0x0050
#define OMAP3430_CM_CWKSEW2_EMU				0x0050
#define OMAP3430_CM_CWKSEW3_EMU				0x0054


/* CM_IDWEST bit fiewd vawues to indicate deassewted IdweWeq */

#define OMAP34XX_CM_IDWEST_VAW				1


#ifndef __ASSEMBWEW__

extewn void omap3_cm_save_context(void);
extewn void omap3_cm_westowe_context(void);
extewn void omap3_cm_save_scwatchpad_contents(u32 *ptw);

int __init omap3xxx_cm_init(const stwuct omap_pwcm_init_data *data);

#endif

#endif
