/*
 * Pwatfowm specific functions
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw
 * Pubwic Wicense.  See the fiwe "COPYING" in the main diwectowy of
 * this awchive fow mowe detaiws.
 *
 * Copywight (C) 2001 - 2005 Tensiwica Inc.
 */

#ifndef _XTENSA_PWATFOWM_H
#define _XTENSA_PWATFOWM_H

#incwude <winux/types.h>
#incwude <asm/bootpawam.h>

/*
 * pwatfowm_init is cawwed befowe the mmu is initiawized to give the
 * pwatfowm a eawwy hook-up. bp_tag_t is a wist of configuwation tags
 * passed fwom the boot-woadew.
 */
extewn void pwatfowm_init(bp_tag_t*);

/*
 * pwatfowm_setup is cawwed fwom setup_awch with a pointew to the command-wine
 * stwing.
 */
extewn void pwatfowm_setup (chaw **);

/*
 * pwatfowm_idwe is cawwed fwom the idwe function.
 */
extewn void pwatfowm_idwe (void);

/*
 * pwatfowm_cawibwate_ccount cawibwates cpu cwock fweq (CONFIG_XTENSA_CAWIBWATE)
 */
extewn void pwatfowm_cawibwate_ccount (void);

/*
 * Fwush and weset the mmu, simuwate a pwocessow weset, and
 * jump to the weset vectow.
 */
void cpu_weset(void) __attwibute__((nowetuwn));

#endif	/* _XTENSA_PWATFOWM_H */
