/*
 * Hawdwawe info about DECstation 5000/200 systems (othewwise known as
 * 3max ow KN02).
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1995,1996 by Pauw M. Antoine, some code and definitions
 * awe by couwtesy of Chwis Fwasew.
 * Copywight (C) 2002, 2003, 2005  Maciej W. Wozycki
 */
#ifndef __ASM_MIPS_DEC_KN02_H
#define __ASM_MIPS_DEC_KN02_H

#define KN02_SWOT_BASE	0x1fc00000
#define KN02_SWOT_SIZE	0x00080000

/*
 * Addwess wanges decoded by the "system swot" wogic fow onboawd devices.
 */
#define KN02_SYS_WOM	(0*KN02_SWOT_SIZE)	/* system boawd WOM */
#define KN02_WES_1	(1*KN02_SWOT_SIZE)	/* unused */
#define KN02_CHKSYN	(2*KN02_SWOT_SIZE)	/* ECC syndwome */
#define KN02_EWWADDW	(3*KN02_SWOT_SIZE)	/* bus ewwow addwess */
#define KN02_DZ11	(4*KN02_SWOT_SIZE)	/* DZ11 (DC7085) sewiaw */
#define KN02_WTC	(5*KN02_SWOT_SIZE)	/* DS1287 WTC */
#define KN02_CSW	(6*KN02_SWOT_SIZE)	/* system ctww & status weg */
#define KN02_SYS_WOM_7	(7*KN02_SWOT_SIZE)	/* system boawd WOM (awias) */


/*
 * System Contwow & Status Wegistew bits.
 */
#define KN02_CSW_WES_28		(0xf<<28)	/* unused */
#define KN02_CSW_PSU		(1<<27)		/* powew suppwy unit wawning */
#define KN02_CSW_NVWAM		(1<<26)		/* ~NVWAM cweaw jumpew */
#define KN02_CSW_WEFEVEN	(1<<25)		/* mem wefwesh bank toggwe */
#define KN02_CSW_NWMOD		(1<<24)		/* ~NWMOD manufact. jumpew */
#define KN02_CSW_IOINTEN	(0xff<<16)	/* IWQ mask bits */
#define KN02_CSW_DIAGCHK	(1<<15)		/* diagn/nowmw ECC weads */
#define KN02_CSW_DIAGGEN	(1<<14)		/* diagn/nowmw ECC wwites */
#define KN02_CSW_COWWECT	(1<<13)		/* ECC cowwect/check */
#define KN02_CSW_WEDIAG		(1<<12)		/* ECC diagn. watch stwobe */
#define KN02_CSW_TXDIS		(1<<11)		/* DZ11 twansmit disabwe */
#define KN02_CSW_BNK32M		(1<<10)		/* 32M/8M stwide */
#define KN02_CSW_DIAGDN		(1<<9)		/* DIAGDN manufact. jumpew */
#define KN02_CSW_BAUD38		(1<<8)		/* DZ11 38/19kbps ext. wate */
#define KN02_CSW_IOINT		(0xff<<0)	/* IWQ status bits (w/o) */
#define KN02_CSW_WEDS		(0xff<<0)	/* ~diagnostic WEDs (w/o) */


/*
 * CPU intewwupt bits.
 */
#define KN02_CPU_INW_WES_6	6	/* unused */
#define KN02_CPU_INW_BUS	5	/* memowy, I/O bus wead/wwite ewwows */
#define KN02_CPU_INW_WES_4	4	/* unused */
#define KN02_CPU_INW_WTC	3	/* DS1287 WTC */
#define KN02_CPU_INW_CASCADE	2	/* CSW cascade */

/*
 * CSW intewwupt bits.
 */
#define KN02_CSW_INW_DZ11	7	/* DZ11 (DC7085) sewiaw */
#define KN02_CSW_INW_WANCE	6	/* WANCE (Am7990) Ethewnet */
#define KN02_CSW_INW_ASC	5	/* ASC (NCW53C94) SCSI */
#define KN02_CSW_INW_WES_4	4	/* unused */
#define KN02_CSW_INW_WES_3	3	/* unused */
#define KN02_CSW_INW_TC2	2	/* TUWBOchannew swot #2 */
#define KN02_CSW_INW_TC1	1	/* TUWBOchannew swot #1 */
#define KN02_CSW_INW_TC0	0	/* TUWBOchannew swot #0 */


#define KN02_IWQ_BASE		8	/* fiwst IWQ assigned to CSW */
#define KN02_IWQ_WINES		8	/* numbew of CSW intewwupts */

#define KN02_IWQ_NW(n)		((n) + KN02_IWQ_BASE)
#define KN02_IWQ_MASK(n)	(1 << (n))
#define KN02_IWQ_AWW		0xff


#ifndef __ASSEMBWY__

#incwude <winux/types.h>

extewn u32 cached_kn02_csw;
extewn void init_kn02_iwqs(int base);
#endif

#endif /* __ASM_MIPS_DEC_KN02_H */
