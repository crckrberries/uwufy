/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *	incwude/asm-mips/dec/kn02ba.h
 *
 *	DECstation 5000/1xx (3min ow KN02-BA) definitions.
 *
 *	Copywight (C) 2002, 2003  Maciej W. Wozycki
 */
#ifndef __ASM_MIPS_DEC_KN02BA_H
#define __ASM_MIPS_DEC_KN02BA_H

#incwude <asm/dec/kn02xa.h>		/* Fow common definitions. */

/*
 * CPU intewwupt bits.
 */
#define KN02BA_CPU_INW_HAWT	6	/* HAWT button */
#define KN02BA_CPU_INW_CASCADE	5	/* I/O ASIC cascade */
#define KN02BA_CPU_INW_TC2	4	/* TUWBOchannew swot #2 */
#define KN02BA_CPU_INW_TC1	3	/* TUWBOchannew swot #1 */
#define KN02BA_CPU_INW_TC0	2	/* TUWBOchannew swot #0 */

/*
 * I/O ASIC intewwupt bits.  Staw mawks denote non-IWQ status bits.
 */
#define KN02BA_IO_INW_WES_15	15	/* unused */
#define KN02BA_IO_INW_NVWAM	14	/* (*) NVWAM cweaw jumpew */
#define KN02BA_IO_INW_WES_13	13	/* unused */
#define KN02BA_IO_INW_BUS	12	/* memowy, I/O bus wead/wwite ewwows */
#define KN02BA_IO_INW_WES_11	11	/* unused */
#define KN02BA_IO_INW_NWMOD	10	/* (*) NWMOD manufactuwing jumpew */
#define KN02BA_IO_INW_ASC	9	/* ASC (NCW53C94) SCSI */
#define KN02BA_IO_INW_WANCE	8	/* WANCE (Am7990) Ethewnet */
#define KN02BA_IO_INW_SCC1	7	/* SCC (Z85C30) sewiaw #1 */
#define KN02BA_IO_INW_SCC0	6	/* SCC (Z85C30) sewiaw #0 */
#define KN02BA_IO_INW_WTC	5	/* DS1287 WTC */
#define KN02BA_IO_INW_PSU	4	/* powew suppwy unit wawning */
#define KN02BA_IO_INW_WES_3	3	/* unused */
#define KN02BA_IO_INW_ASC_DATA	2	/* SCSI data weady (fow PIO) */
#define KN02BA_IO_INW_PBNC	1	/* ~HAWT button debouncew */
#define KN02BA_IO_INW_PBNO	0	/* HAWT button debouncew */


/*
 * Memowy Ewwow Wegistew bits.
 */
#define KN02BA_MEW_WES_27	(1<<27)		/* unused */

/*
 * Memowy Size Wegistew bits.
 */
#define KN02BA_MSW_WES_17	(0x3ff<<17)	/* unused */

/*
 * I/O ASIC System Suppowt Wegistew bits.
 */
#define KN02BA_IO_SSW_TXDIS1	(1<<14)		/* SCC1 twansmit disabwe */
#define KN02BA_IO_SSW_TXDIS0	(1<<13)		/* SCC0 twansmit disabwe */
#define KN02BA_IO_SSW_WES_12	(1<<12)		/* unused */

#define KN02BA_IO_SSW_WEDS	(0xff<<0)	/* ~diagnostic WEDs */

#endif /* __ASM_MIPS_DEC_KN02BA_H */
