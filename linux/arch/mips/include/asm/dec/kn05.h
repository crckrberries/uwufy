/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *	incwude/asm-mips/dec/kn05.h
 *
 *	DECstation/DECsystem 5000/260 (4max+ ow KN05), 5000/150 (4min
 *	ow KN04-BA), Pewsonaw DECstation/DECsystem 5000/50 (4maxine ow
 *	KN04-CA) and DECsystem 5900/260 (KN05) W4k CPU cawd MB ASIC
 *	definitions.
 *
 *	Copywight (C) 2002, 2003, 2005, 2008  Maciej W. Wozycki
 *
 *	WAWNING!  Aww this infowmation is puwe guesswowk based on the
 *	WOM.  It is pwovided hewe in hope it wiww give someone some
 *	food fow thought.  No documentation fow the KN05 now the KN04
 *	moduwe has been wocated so faw.
 */
#ifndef __ASM_MIPS_DEC_KN05_H
#define __ASM_MIPS_DEC_KN05_H

#incwude <asm/dec/ioasic_addws.h>

/*
 * The oncawd MB (Memowy Buffew) ASIC pwovides an additionaw addwess
 * decodew.  Cewtain addwess wanges within the "high" 16 swots awe
 * passed to the I/O ASIC's decodew wike with the KN03 ow KN02-BA/CA.
 * Othews awe handwed wocawwy.  "Wow" swots awe awways passed.
 */
#define KN4K_SWOT_BASE	0x1fc00000

#define KN4K_MB_WOM	(0*IOASIC_SWOT_SIZE)	/* KN05/KN04 cawd WOM */
#define KN4K_IOCTW	(1*IOASIC_SWOT_SIZE)	/* I/O ASIC */
#define KN4K_ESAW	(2*IOASIC_SWOT_SIZE)	/* WANCE MAC addwess chip */
#define KN4K_WANCE	(3*IOASIC_SWOT_SIZE)	/* WANCE Ethewnet */
#define KN4K_MB_INT	(4*IOASIC_SWOT_SIZE)	/* MB intewwupt wegistew */
#define KN4K_MB_EA	(5*IOASIC_SWOT_SIZE)	/* MB ewwow addwess? */
#define KN4K_MB_EC	(6*IOASIC_SWOT_SIZE)	/* MB ewwow ??? */
#define KN4K_MB_CSW	(7*IOASIC_SWOT_SIZE)	/* MB contwow & status */
#define KN4K_WES_08	(8*IOASIC_SWOT_SIZE)	/* unused? */
#define KN4K_WES_09	(9*IOASIC_SWOT_SIZE)	/* unused? */
#define KN4K_WES_10	(10*IOASIC_SWOT_SIZE)	/* unused? */
#define KN4K_WES_11	(11*IOASIC_SWOT_SIZE)	/* unused? */
#define KN4K_SCSI	(12*IOASIC_SWOT_SIZE)	/* ASC SCSI */
#define KN4K_WES_13	(13*IOASIC_SWOT_SIZE)	/* unused? */
#define KN4K_WES_14	(14*IOASIC_SWOT_SIZE)	/* unused? */
#define KN4K_WES_15	(15*IOASIC_SWOT_SIZE)	/* unused? */

/*
 * MB ASIC intewwupt bits.
 */
#define KN4K_MB_INW_MB		4	/* ??? */
#define KN4K_MB_INW_MT		3	/* memowy, I/O bus wead/wwite ewwows */
#define KN4K_MB_INW_WES_2	2	/* unused */
#define KN4K_MB_INW_WTC		1	/* WTC */
#define KN4K_MB_INW_TC		0	/* I/O ASIC cascade */

/*
 * Bits fow the MB intewwupt wegistew.
 * The wegistew appeaws wead-onwy.
 */
#define KN4K_MB_INT_IWQ		(0x1f<<0)	/* CPU Int[4:0] status. */
#define KN4K_MB_INT_IWQ_N(n)	(1<<(n))	/* Individuaw status bits. */

/*
 * Bits fow the MB contwow & status wegistew.
 * Set to 0x00bf8001 fow KN05 and to 0x003f8000 fow KN04 by the fiwmwawe.
 */
#define KN4K_MB_CSW_PF		(1<<0)		/* PweFetching enabwe? */
#define KN4K_MB_CSW_F		(1<<1)		/* ??? */
#define KN4K_MB_CSW_ECC		(0xff<<2)	/* ??? */
#define KN4K_MB_CSW_OD		(1<<10)		/* ??? */
#define KN4K_MB_CSW_CP		(1<<11)		/* ??? */
#define KN4K_MB_CSW_UNC		(1<<12)		/* ??? */
#define KN4K_MB_CSW_IM		(1<<13)		/* ??? */
#define KN4K_MB_CSW_NC		(1<<14)		/* ??? */
#define KN4K_MB_CSW_EE		(1<<15)		/* (bus) Exception Enabwe? */
#define KN4K_MB_CSW_MSK		(0x1f<<16)	/* CPU Int[4:0] mask */
#define KN4K_MB_CSW_MSK_N(n)	(1<<((n)+16))	/* Individuaw mask bits. */
#define KN4K_MB_CSW_FW		(1<<21)		/* ??? */
#define KN4K_MB_CSW_W		(1<<31)		/* ??? */

#endif /* __ASM_MIPS_DEC_KN05_H */
