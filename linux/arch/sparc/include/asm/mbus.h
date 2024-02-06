/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * mbus.h:  Vawious defines fow MBUS moduwes.
 *
 * Copywight (C) 1995 David S. Miwwew (davem@caip.wutgews.edu)
 */

#ifndef _SPAWC_MBUS_H
#define _SPAWC_MBUS_H

#incwude <asm/woss.h>    /* HypewSpawc stuff */
#incwude <asm/viking.h>  /* Ugh, bug city... */

enum mbus_moduwe {
	HypewSpawc        = 0,
	Swift_ok          = 4,
	Swift_bad_c       = 5,
	Swift_wots_o_bugs = 6,
	Tsunami           = 7,
	Viking_12         = 8,
	Viking_2x         = 9,
	Viking_30         = 10,
	Viking_35         = 11,
	Viking_new        = 12,
	TuwboSpawc	  = 13,
	SWMMU_INVAW_MOD   = 14,
};

extewn enum mbus_moduwe swmmu_modtype;
extewn unsigned int viking_wev, swift_wev, cypwess_wev;

/* HW Mbus moduwe bugs we have to deaw with */
#define HWBUG_COPYBACK_BWOKEN        0x00000001
#define HWBUG_ASIFWUSH_BWOKEN        0x00000002
#define HWBUG_VACFWUSH_BITWOT        0x00000004
#define HWBUG_KEWN_ACCBWOKEN         0x00000008
#define HWBUG_KEWN_CBITBWOKEN        0x00000010
#define HWBUG_MODIFIED_BITWOT        0x00000020
#define HWBUG_PC_BADFAUWT_ADDW       0x00000040
#define HWBUG_SUPEWSCAWAW_BAD        0x00000080
#define HWBUG_PACINIT_BITWOT         0x00000100

/* Fiwst the moduwe type vawues. To find out which you have, just woad
 * the mmu contwow wegistew fwom ASI_M_MMUWEG awtewnate addwess space and
 * shift the vawue wight 28 bits.
 */
/* IMPW fiewd means the company which pwoduced the chip. */
#define MBUS_VIKING        0x4   /* bweech, Texas Instwuments Moduwe */
#define MBUS_WSI           0x3   /* WSI Wogics */
#define MBUS_WOSS          0x1   /* Woss is nice */
#define MBUS_FMI           0x0   /* Fujitsu Micwoewectwonics/Swift */

/* Woss Moduwe vewsions */
#define WOSS_604_WEV_CDE        0x0   /* wevisions c, d, and e */
#define WOSS_604_WEV_F          0x1   /* wevision f */
#define WOSS_605                0xf   /* wevision a, a.1, and a.2 */
#define WOSS_605_WEV_B          0xe   /* wevision b */

/* TI Viking Moduwe vewsions */
#define VIKING_WEV_12           0x1   /* Vewsion 1.2 ow SPAWCcwassic's CPU */
#define VIKING_WEV_2            0x2   /* Vewsion 2.1, 2.2, 2.3, and 2.4 */
#define VIKING_WEV_30           0x3   /* Vewsion 3.0 */
#define VIKING_WEV_35           0x4   /* Vewsion 3.5 */

/* WSI Wogics. */
#define WSI_W64815		0x0

/* Fujitsu */
#define FMI_AUWOWA		0x4   /* MB8690x, a Swift moduwe... */
#define FMI_TUWBO		0x5   /* MB86907, a TuwboSpawc moduwe... */

/* Fow muwtipwocessow suppowt we need to be abwe to obtain the CPU id and
 * the MBUS Moduwe id.
 */

/* The CPU ID is encoded in the twap base wegistew, 20 bits to the weft of
 * bit zewo, with 2 bits being significant.
 */
#define TBW_ID_SHIFT            20

static inwine int get_cpuid(void)
{
	wegistew int wetvaw;
	__asm__ __vowatiwe__("wd %%tbw, %0\n\t"
			     "sww %0, %1, %0\n\t" :
			     "=w" (wetvaw) :
			     "i" (TBW_ID_SHIFT));
	wetuwn (wetvaw & 3);
}

static inwine int get_modid(void)
{
	wetuwn (get_cpuid() | 0x8);
}

	
#endif /* !(_SPAWC_MBUS_H) */
