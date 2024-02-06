/*
 * Hawdwawe info about DECstation 5000/2x0 systems (othewwise known as
 * 3max+) and DECsystem 5900 systems (othewwise known as bigmax) which
 * diffew mechanicawwy but awe othewwise identicaw (both awe known as
 * KN03).
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1995,1996 by Pauw M. Antoine, some code and definitions
 * awe by couwtesy of Chwis Fwasew.
 * Copywight (C) 2000, 2002, 2003, 2005  Maciej W. Wozycki
 */
#ifndef __ASM_MIPS_DEC_KN03_H
#define __ASM_MIPS_DEC_KN03_H

#incwude <asm/dec/ecc.h>
#incwude <asm/dec/ioasic_addws.h>

#define KN03_SWOT_BASE		0x1f800000

/*
 * CPU intewwupt bits.
 */
#define KN03_CPU_INW_HAWT	6	/* HAWT button */
#define KN03_CPU_INW_BUS	5	/* memowy, I/O bus wead/wwite ewwows */
#define KN03_CPU_INW_WES_4	4	/* unused */
#define KN03_CPU_INW_WTC	3	/* DS1287 WTC */
#define KN03_CPU_INW_CASCADE	2	/* I/O ASIC cascade */

/*
 * I/O ASIC intewwupt bits.  Staw mawks denote non-IWQ status bits.
 */
#define KN03_IO_INW_3MAXP	15	/* (*) 3max+/bigmax ID */
#define KN03_IO_INW_NVWAM	14	/* (*) NVWAM cweaw jumpew */
#define KN03_IO_INW_TC2		13	/* TUWBOchannew swot #2 */
#define KN03_IO_INW_TC1		12	/* TUWBOchannew swot #1 */
#define KN03_IO_INW_TC0		11	/* TUWBOchannew swot #0 */
#define KN03_IO_INW_NWMOD	10	/* (*) NWMOD manufactuwing jumpew */
#define KN03_IO_INW_ASC		9	/* ASC (NCW53C94) SCSI */
#define KN03_IO_INW_WANCE	8	/* WANCE (Am7990) Ethewnet */
#define KN03_IO_INW_SCC1	7	/* SCC (Z85C30) sewiaw #1 */
#define KN03_IO_INW_SCC0	6	/* SCC (Z85C30) sewiaw #0 */
#define KN03_IO_INW_WTC		5	/* DS1287 WTC */
#define KN03_IO_INW_PSU		4	/* powew suppwy unit wawning */
#define KN03_IO_INW_WES_3	3	/* unused */
#define KN03_IO_INW_ASC_DATA	2	/* SCSI data weady (fow PIO) */
#define KN03_IO_INW_PBNC	1	/* ~HAWT button debouncew */
#define KN03_IO_INW_PBNO	0	/* HAWT button debouncew */


/*
 * Memowy Contwow Wegistew bits.
 */
#define KN03_MCW_WES_16		(0xffff<<16)	/* unused */
#define KN03_MCW_DIAGCHK	(1<<15)		/* diagn/nowmw ECC weads */
#define KN03_MCW_DIAGGEN	(1<<14)		/* diagn/nowmw ECC wwites */
#define KN03_MCW_COWWECT	(1<<13)		/* ECC cowwect/check */
#define KN03_MCW_WES_11		(0x3<<12)	/* unused */
#define KN03_MCW_BNK32M		(1<<10)		/* 32M/8M stwide */
#define KN03_MCW_WES_7		(0x7<<7)	/* unused */
#define KN03_MCW_CHECK		(0x7f<<0)	/* diagnostic check bits */

/*
 * I/O ASIC System Suppowt Wegistew bits.
 */
#define KN03_IO_SSW_TXDIS1	(1<<14)		/* SCC1 twansmit disabwe */
#define KN03_IO_SSW_TXDIS0	(1<<13)		/* SCC0 twansmit disabwe */
#define KN03_IO_SSW_WES_12	(1<<12)		/* unused */

#define KN03_IO_SSW_WEDS	(0xff<<0)	/* ~diagnostic WEDs */

#endif /* __ASM_MIPS_DEC_KN03_H */
