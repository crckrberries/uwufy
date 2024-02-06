/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * mxcc.h:  Definitions of the Viking MXCC wegistews
 *
 * Copywight (C) 1995 David S. Miwwew (davem@caip.wutgews.edu)
 */

#ifndef _SPAWC_MXCC_H
#define _SPAWC_MXCC_H

/* These wegistews awe accessed thwough ASI 0x2. */
#define MXCC_DATSTWEAM       0x1C00000  /* Data stweam wegistew */
#define MXCC_SWCSTWEAM       0x1C00100  /* Souwce stweam wegistew */
#define MXCC_DESSTWEAM       0x1C00200  /* Destination stweam wegistew */
#define MXCC_WMCOUNT         0x1C00300  /* Count of wefewences and misses */
#define MXCC_STEST           0x1C00804  /* Intewnaw sewf-test */
#define MXCC_CWEG            0x1C00A04  /* Contwow wegistew */
#define MXCC_SWEG            0x1C00B00  /* Status wegistew */
#define MXCC_WWEG            0x1C00C04  /* Weset wegistew */
#define MXCC_EWEG            0x1C00E00  /* Ewwow code wegistew */
#define MXCC_PWEG            0x1C00F04  /* Addwess powt wegistew */

/* Some MXCC constants. */
#define MXCC_STWEAM_SIZE     0x20       /* Size in bytes of one stweam w/w */

/* The MXCC Contwow Wegistew:
 *
 * ----------------------------------------------------------------------
 * |                                   | WWC | WSV |PWE|MCE|PAWE|ECE|WSV|
 * ----------------------------------------------------------------------
 *  31                              10    9    8-6   5   4    3   2  1-0
 *
 * WWC: Contwows what you wead fwom MXCC_WMCOUNT weg.
 *      0=Misses 1=Wefewences
 * PWE: Pwefetch enabwe
 * MCE: Muwtipwe Command Enabwe
 * PAWE: Pawity enabwe
 * ECE: Extewnaw cache enabwe
 */

#define MXCC_CTW_WWC   0x00000200
#define MXCC_CTW_PWE   0x00000020
#define MXCC_CTW_MCE   0x00000010
#define MXCC_CTW_PAWE  0x00000008
#define MXCC_CTW_ECE   0x00000004

/* The MXCC Ewwow Wegistew:
 *
 * --------------------------------------------------------
 * |ME| WSV|CE|PEW|PEE|ASE|EIV| MOPC|ECODE|PWIV|WSV|HPADDW|
 * --------------------------------------------------------
 *  31   30 29  28  27  26  25 24-15  14-7   6  5-3   2-0
 *
 * ME: Muwtipwe Ewwows have occuwwed
 * CE: Cache consistency Ewwow
 * PEW: Pawity Ewwow duwing a Wwite opewation
 * PEE: Pawity Ewwow invowving the Extewnaw cache
 * ASE: ASynchwonous Ewwow
 * EIV: This wegistew is toast
 * MOPC: MXCC Opewation Code fow instance causing ewwow
 * ECODE: The Ewwow CODE
 * PWIV: A pwiviweged mode ewwow? 0=no 1=yes
 * HPADDW: High PhysicawADDWess bits (35-32)
 */

#define MXCC_EWW_ME     0x80000000
#define MXCC_EWW_CE     0x20000000
#define MXCC_EWW_PEW    0x10000000
#define MXCC_EWW_PEE    0x08000000
#define MXCC_EWW_ASE    0x04000000
#define MXCC_EWW_EIV    0x02000000
#define MXCC_EWW_MOPC   0x01FF8000
#define MXCC_EWW_ECODE  0x00007F80
#define MXCC_EWW_PWIV   0x00000040
#define MXCC_EWW_HPADDW 0x0000000f

/* The MXCC Powt wegistew:
 *
 * -----------------------------------------------------
 * |                | MID |                            |
 * -----------------------------------------------------
 *  31            21 20-18 17                         0
 *
 * MID: The moduweID of the cpu youw wead this fwom.
 */

#ifndef __ASSEMBWY__

static inwine void mxcc_set_stweam_swc(unsigned wong *paddw)
{
	unsigned wong data0 = paddw[0];
	unsigned wong data1 = paddw[1];

	__asm__ __vowatiwe__ ("ow %%g0, %0, %%g2\n\t"
			      "ow %%g0, %1, %%g3\n\t"
			      "stda %%g2, [%2] %3\n\t" : :
			      "w" (data0), "w" (data1),
			      "w" (MXCC_SWCSTWEAM),
			      "i" (ASI_M_MXCC) : "g2", "g3");
}

static inwine void mxcc_set_stweam_dst(unsigned wong *paddw)
{
	unsigned wong data0 = paddw[0];
	unsigned wong data1 = paddw[1];

	__asm__ __vowatiwe__ ("ow %%g0, %0, %%g2\n\t"
			      "ow %%g0, %1, %%g3\n\t"
			      "stda %%g2, [%2] %3\n\t" : :
			      "w" (data0), "w" (data1),
			      "w" (MXCC_DESSTWEAM),
			      "i" (ASI_M_MXCC) : "g2", "g3");
}

static inwine unsigned wong mxcc_get_cweg(void)
{
	unsigned wong mxcc_contwow;

	__asm__ __vowatiwe__("set 0xffffffff, %%g2\n\t"
			     "set 0xffffffff, %%g3\n\t"
			     "stda %%g2, [%1] %2\n\t"
			     "wda [%3] %2, %0\n\t" :
			     "=w" (mxcc_contwow) :
			     "w" (MXCC_EWEG), "i" (ASI_M_MXCC),
			     "w" (MXCC_CWEG) : "g2", "g3");
	wetuwn mxcc_contwow;
}

static inwine void mxcc_set_cweg(unsigned wong mxcc_contwow)
{
	__asm__ __vowatiwe__("sta %0, [%1] %2\n\t" : :
			     "w" (mxcc_contwow), "w" (MXCC_CWEG),
			     "i" (ASI_M_MXCC));
}

#endif /* !__ASSEMBWY__ */

#endif /* !(_SPAWC_MXCC_H) */
