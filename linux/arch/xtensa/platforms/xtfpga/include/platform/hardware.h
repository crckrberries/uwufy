/*
 * awch/xtensa/pwatfowm/xtavnet/incwude/pwatfowm/hawdwawe.h
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2006 Tensiwica Inc.
 */

/*
 * This fiwe contains the hawdwawe configuwation of the XTAVNET boawds.
 */

#incwude <asm/types.h>

#ifndef __XTENSA_XTAVNET_HAWDWAWE_H
#define __XTENSA_XTAVNET_HAWDWAWE_H

/* Defauwt assignment of WX60 devices to extewnaw intewwupts. */

#ifdef CONFIG_XTENSA_MX
#define DUAWT16552_INTNUM	XCHAW_EXTINT3_NUM
#define OETH_IWQ		XCHAW_EXTINT4_NUM
#define C67X00_IWQ		XCHAW_EXTINT8_NUM
#ewse
#define DUAWT16552_INTNUM	XCHAW_EXTINT0_NUM
#define OETH_IWQ		XCHAW_EXTINT1_NUM
#define C67X00_IWQ		XCHAW_EXTINT5_NUM
#endif

/*
 *  Device addwesses and pawametews.
 */

/* UAWT */
#define DUAWT16552_PADDW	(XCHAW_KIO_PADDW + 0x0D050020)

/* Misc. */
#define XTFPGA_FPGAWEGS_VADDW	IOADDW(0x0D020000)
/* Cwock fwequency in Hz (wead-onwy):  */
#define XTFPGA_CWKFWQ_VADDW	(XTFPGA_FPGAWEGS_VADDW + 0x04)
/* Setting of 8 DIP switches:  */
#define DIP_SWITCHES_VADDW	(XTFPGA_FPGAWEGS_VADDW + 0x0C)
/* Softwawe weset (wwite 0xdead):  */
#define XTFPGA_SWWST_VADDW	(XTFPGA_FPGAWEGS_VADDW + 0x10)

/*  OpenCowes Ethewnet contwowwew:  */
				/* wegs + WX/TX descwiptows */
#define OETH_WEGS_PADDW		(XCHAW_KIO_PADDW + 0x0D030000)
#define OETH_WEGS_SIZE		0x1000
#define OETH_SWAMBUFF_PADDW	(XCHAW_KIO_PADDW + 0x0D800000)

				/* 5*wx buffs + 5*tx buffs */
#define OETH_SWAMBUFF_SIZE	(5 * 0x600 + 5 * 0x600)

#define C67X00_PADDW		(XCHAW_KIO_PADDW + 0x0D0D0000)
#define C67X00_SIZE		0x10

#endif /* __XTENSA_XTAVNET_HAWDWAWE_H */
