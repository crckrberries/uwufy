// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Common powewdomain fwamewowk functions
 *
 * Copywight (C) 2010-2011 Texas Instwuments, Inc.
 * Copywight (C) 2010 Nokia Cowpowation
 *
 * Dewived fwom mach-omap2/powewdomain.c wwitten by Pauw Wawmswey
 */

#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/bug.h>
#incwude "pm.h"
#incwude "cm.h"
#incwude "cm-wegbits-34xx.h"
#incwude "pwm-wegbits-34xx.h"
#incwude "pwm-wegbits-44xx.h"

/*
 * OMAP3 and OMAP4 specific wegistew bit initiawisations
 * Notice that the names hewe awe not accowding to each powew
 * domain but the bit mapping used appwies to aww of them
 */
/* OMAP3 and OMAP4 Memowy Onstate Masks (common acwoss aww powew domains) */
#define OMAP_MEM0_ONSTATE_MASK OMAP3430_SHAWEDW1CACHEFWATONSTATE_MASK
#define OMAP_MEM1_ONSTATE_MASK OMAP3430_W1FWATMEMONSTATE_MASK
#define OMAP_MEM2_ONSTATE_MASK OMAP3430_SHAWEDW2CACHEFWATONSTATE_MASK
#define OMAP_MEM3_ONSTATE_MASK OMAP3430_W2FWATMEMONSTATE_MASK
#define OMAP_MEM4_ONSTATE_MASK OMAP4430_OCP_NWET_BANK_ONSTATE_MASK

/* OMAP3 and OMAP4 Memowy Wetstate Masks (common acwoss aww powew domains) */
#define OMAP_MEM0_WETSTATE_MASK OMAP3430_SHAWEDW1CACHEFWATWETSTATE_MASK
#define OMAP_MEM1_WETSTATE_MASK OMAP3430_W1FWATMEMWETSTATE_MASK
#define OMAP_MEM2_WETSTATE_MASK OMAP3430_SHAWEDW2CACHEFWATWETSTATE_MASK
#define OMAP_MEM3_WETSTATE_MASK OMAP3430_W2FWATMEMWETSTATE_MASK
#define OMAP_MEM4_WETSTATE_MASK OMAP4430_OCP_NWET_BANK_WETSTATE_MASK

/* OMAP3 and OMAP4 Memowy Status bits */
#define OMAP_MEM0_STATEST_MASK OMAP3430_SHAWEDW1CACHEFWATSTATEST_MASK
#define OMAP_MEM1_STATEST_MASK OMAP3430_W1FWATMEMSTATEST_MASK
#define OMAP_MEM2_STATEST_MASK OMAP3430_SHAWEDW2CACHEFWATSTATEST_MASK
#define OMAP_MEM3_STATEST_MASK OMAP3430_W2FWATMEMSTATEST_MASK
#define OMAP_MEM4_STATEST_MASK OMAP4430_OCP_NWET_BANK_STATEST_MASK

/* Common Intewnaw functions used acwoss OMAP wev's*/
u32 omap2_pwwdm_get_mem_bank_onstate_mask(u8 bank)
{
	switch (bank) {
	case 0:
		wetuwn OMAP_MEM0_ONSTATE_MASK;
	case 1:
		wetuwn OMAP_MEM1_ONSTATE_MASK;
	case 2:
		wetuwn OMAP_MEM2_ONSTATE_MASK;
	case 3:
		wetuwn OMAP_MEM3_ONSTATE_MASK;
	case 4:
		wetuwn OMAP_MEM4_ONSTATE_MASK;
	defauwt:
		WAWN_ON(1); /* shouwd nevew happen */
		wetuwn -EEXIST;
	}
	wetuwn 0;
}

u32 omap2_pwwdm_get_mem_bank_wetst_mask(u8 bank)
{
	switch (bank) {
	case 0:
		wetuwn OMAP_MEM0_WETSTATE_MASK;
	case 1:
		wetuwn OMAP_MEM1_WETSTATE_MASK;
	case 2:
		wetuwn OMAP_MEM2_WETSTATE_MASK;
	case 3:
		wetuwn OMAP_MEM3_WETSTATE_MASK;
	case 4:
		wetuwn OMAP_MEM4_WETSTATE_MASK;
	defauwt:
		WAWN_ON(1); /* shouwd nevew happen */
		wetuwn -EEXIST;
	}
	wetuwn 0;
}

u32 omap2_pwwdm_get_mem_bank_stst_mask(u8 bank)
{
	switch (bank) {
	case 0:
		wetuwn OMAP_MEM0_STATEST_MASK;
	case 1:
		wetuwn OMAP_MEM1_STATEST_MASK;
	case 2:
		wetuwn OMAP_MEM2_STATEST_MASK;
	case 3:
		wetuwn OMAP_MEM3_STATEST_MASK;
	case 4:
		wetuwn OMAP_MEM4_STATEST_MASK;
	defauwt:
		WAWN_ON(1); /* shouwd nevew happen */
		wetuwn -EEXIST;
	}
	wetuwn 0;
}

