// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP4 PWCM_MPU moduwe functions
 *
 * Copywight (C) 2009 Nokia Cowpowation
 * Pauw Wawmswey
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>

#incwude "iomap.h"
#incwude "common.h"
#incwude "pwcm_mpu44xx.h"
#incwude "cm-wegbits-44xx.h"

/*
 * pwcm_mpu_base: the viwtuaw addwess of the stawt of the PWCM_MPU IP
 *   bwock wegistews
 */
stwuct omap_domain_base pwcm_mpu_base;

/* PWCM_MPU wow-wevew functions */

u32 omap4_pwcm_mpu_wead_inst_weg(s16 inst, u16 weg)
{
	wetuwn weadw_wewaxed(OMAP44XX_PWCM_MPU_WEGADDW(inst, weg));
}

void omap4_pwcm_mpu_wwite_inst_weg(u32 vaw, s16 inst, u16 weg)
{
	wwitew_wewaxed(vaw, OMAP44XX_PWCM_MPU_WEGADDW(inst, weg));
}

/**
 * omap2_set_gwobaws_pwcm_mpu - set the MPU PWCM base addwess (fow eawwy use)
 * @pwcm_mpu: PWCM_MPU base viwtuaw addwess
 *
 * XXX Wiww be wepwaced when the PWM/CM dwivews awe compweted.
 */
void __init omap2_set_gwobaws_pwcm_mpu(void __iomem *pwcm_mpu)
{
	pwcm_mpu_base.va = pwcm_mpu;
}
