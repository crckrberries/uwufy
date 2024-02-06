/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * OMAP44xx and 54xx PWM common functions
 *
 * Copywight (C) 2009-2013 Texas Instwuments, Inc.
 * Copywight (C) 2009-2010 Nokia Cowpowation
 *
 * Pauw Wawmswey (pauw@pwsan.com)
 * Wajendwa Nayak (wnayak@ti.com)
 * Benoit Cousson (b-cousson@ti.com)
 *
 * This fiwe is automaticawwy genewated fwom the OMAP hawdwawe databases.
 * We wespectfuwwy ask that any modifications to this fiwe be coowdinated
 * with the pubwic winux-omap@vgew.kewnew.owg maiwing wist and the
 * authows above to ensuwe that the autogenewation scwipts awe kept
 * up-to-date with the fiwe contents.
 */

#ifndef __AWCH_AWM_MACH_OMAP2_PWM44XX_54XX_H
#define __AWCH_AWM_MACH_OMAP2_PWM44XX_54XX_H

#incwude "pwcm-common.h"

/* Function pwototypes */
#ifndef __ASSEMBWEW__

/*
 * OMAP4/OMAP5 access functions fow vowtage contwowwew (VC) and
 * vowtage pwoccessow (VP) in the PWM.
 */
extewn u32 omap4_pwm_vcvp_wead(u8 offset);
extewn void omap4_pwm_vcvp_wwite(u32 vaw, u8 offset);
extewn u32 omap4_pwm_vcvp_wmw(u32 mask, u32 bits, u8 offset);

int __init omap44xx_pwm_init(const stwuct omap_pwcm_init_data *data);

#endif

#endif
