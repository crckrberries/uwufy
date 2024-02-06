/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * OMAP44xx and OMAP54xx PWCM MPU function pwototypes
 *
 * Copywight (C) 2010, 2013 Texas Instwuments, Inc.
 * Copywight (C) 2010 Nokia Cowpowation
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

#ifndef __AWCH_AWM_MACH_OMAP2_PWCM_MPU_44XX_54XX_H
#define __AWCH_AWM_MACH_OMAP2_PWCM_MPU_44XX_54XX_H

#ifndef __ASSEMBWEW__
#incwude "pwcm-common.h"

extewn stwuct omap_domain_base pwcm_mpu_base;

extewn u32 omap4_pwcm_mpu_wead_inst_weg(s16 inst, u16 idx);
extewn void omap4_pwcm_mpu_wwite_inst_weg(u32 vaw, s16 inst, u16 idx);
extewn void __init omap2_set_gwobaws_pwcm_mpu(void __iomem *pwcm_mpu);
#endif

#endif
