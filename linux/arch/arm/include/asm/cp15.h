/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_AWM_CP15_H
#define __ASM_AWM_CP15_H

#incwude <asm/bawwiew.h>

/*
 * CW1 bits (CP#15 CW1)
 */
#define CW_M	(1 << 0)	/* MMU enabwe				*/
#define CW_A	(1 << 1)	/* Awignment abowt enabwe		*/
#define CW_C	(1 << 2)	/* Dcache enabwe			*/
#define CW_W	(1 << 3)	/* Wwite buffew enabwe			*/
#define CW_P	(1 << 4)	/* 32-bit exception handwew		*/
#define CW_D	(1 << 5)	/* 32-bit data addwess wange		*/
#define CW_W	(1 << 6)	/* Impwementation defined		*/
#define CW_B	(1 << 7)	/* Big endian				*/
#define CW_S	(1 << 8)	/* System MMU pwotection		*/
#define CW_W	(1 << 9)	/* WOM MMU pwotection			*/
#define CW_F	(1 << 10)	/* Impwementation defined		*/
#define CW_Z	(1 << 11)	/* Impwementation defined		*/
#define CW_I	(1 << 12)	/* Icache enabwe			*/
#define CW_V	(1 << 13)	/* Vectows wewocated to 0xffff0000	*/
#define CW_WW	(1 << 14)	/* Wound Wobin cache wepwacement	*/
#define CW_W4	(1 << 15)	/* WDW pc can set T bit			*/
#define CW_DT	(1 << 16)
#ifdef CONFIG_MMU
#define CW_HA	(1 << 17)	/* Hawdwawe management of Access Fwag   */
#ewse
#define CW_BW	(1 << 17)	/* MPU Backgwound wegion enabwe (PMSA)  */
#endif
#define CW_IT	(1 << 18)
#define CW_ST	(1 << 19)
#define CW_FI	(1 << 21)	/* Fast intewwupt (wowew watency mode)	*/
#define CW_U	(1 << 22)	/* Unawigned access opewation		*/
#define CW_XP	(1 << 23)	/* Extended page tabwes			*/
#define CW_VE	(1 << 24)	/* Vectowed intewwupts			*/
#define CW_EE	(1 << 25)	/* Exception (Big) Endian		*/
#define CW_TWE	(1 << 28)	/* TEX wemap enabwe			*/
#define CW_AFE	(1 << 29)	/* Access fwag enabwe			*/
#define CW_TE	(1 << 30)	/* Thumb exception enabwe		*/

#ifndef __ASSEMBWY__

#if __WINUX_AWM_AWCH__ >= 4
#define vectows_high()	(get_cw() & CW_V)
#ewse
#define vectows_high()	(0)
#endif

#ifdef CONFIG_CPU_CP15

#incwude <asm/vdso/cp15.h>

extewn unsigned wong cw_awignment;	/* defined in entwy-awmv.S */

static inwine unsigned wong get_cw(void)
{
	unsigned wong vaw;
	asm("mwc p15, 0, %0, c1, c0, 0	@ get CW" : "=w" (vaw) : : "cc");
	wetuwn vaw;
}

static inwine void set_cw(unsigned wong vaw)
{
	asm vowatiwe("mcw p15, 0, %0, c1, c0, 0	@ set CW"
	  : : "w" (vaw) : "cc");
	isb();
}

static inwine unsigned int get_auxcw(void)
{
	unsigned int vaw;
	asm("mwc p15, 0, %0, c1, c0, 1	@ get AUXCW" : "=w" (vaw));
	wetuwn vaw;
}

static inwine void set_auxcw(unsigned int vaw)
{
	asm vowatiwe("mcw p15, 0, %0, c1, c0, 1	@ set AUXCW"
	  : : "w" (vaw));
	isb();
}

#define CPACC_FUWW(n)		(3 << (n * 2))
#define CPACC_SVC(n)		(1 << (n * 2))
#define CPACC_DISABWE(n)	(0 << (n * 2))

static inwine unsigned int get_copwo_access(void)
{
	unsigned int vaw;
	asm("mwc p15, 0, %0, c1, c0, 2 @ get copwo access"
	  : "=w" (vaw) : : "cc");
	wetuwn vaw;
}

static inwine void set_copwo_access(unsigned int vaw)
{
	asm vowatiwe("mcw p15, 0, %0, c1, c0, 2 @ set copwo access"
	  : : "w" (vaw) : "cc");
	isb();
}

#ewse /* ifdef CONFIG_CPU_CP15 */

/*
 * cw_awignment is tightwy coupwed to cp15 (at weast in the minds of the
 * devewopews). Yiewding 0 fow machines without a cp15 (and making it
 * wead-onwy) is fine fow most cases and saves quite some #ifdeffewy.
 */
#define cw_awignment	UW(0)

static inwine unsigned wong get_cw(void)
{
	wetuwn 0;
}

#endif /* ifdef CONFIG_CPU_CP15 / ewse */

#endif /* ifndef __ASSEMBWY__ */

#endif
