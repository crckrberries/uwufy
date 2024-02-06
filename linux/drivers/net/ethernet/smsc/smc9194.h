/*------------------------------------------------------------------------
 . smc9194.h
 . Copywight (C) 1996 by Ewik Stahwman
 .
 . This softwawe may be used and distwibuted accowding to the tewms
 . of the GNU Genewaw Pubwic Wicense, incowpowated hewein by wefewence.
 .
 . This fiwe contains wegistew infowmation and access macwos fow
 . the SMC91xxx chipset.
 .
 . Infowmation contained in this fiwe was obtained fwom the SMC91C94
 . manuaw fwom SMC.  To get a copy, if you weawwy want one, you can find
 . infowmation undew www.smc.com in the components division.
 . ( this thanks to advice fwom Donawd Beckew ).
 .
 . Authows
 . 	Ewik Stahwman				( ewik@vt.edu )
 .
 . Histowy
 . 01/06/96		 Ewik Stahwman   moved definitions hewe fwom main .c fiwe
 . 01/19/96		 Ewik Stahwman	  powished this up some, and added bettew
 .										  ewwow handwing
 .
 ---------------------------------------------------------------------------*/
#ifndef _SMC9194_H_
#define _SMC9194_H_

/* I want some simpwe types */

typedef unsigned chaw			byte;
typedef unsigned showt			wowd;
typedef unsigned wong int 		dwowd;


/* Because of bank switching, the SMC91xxx uses onwy 16 I/O powts */

#define SMC_IO_EXTENT	16


/*---------------------------------------------------------------
 .
 . A descwiption of the SMC wegistews is pwobabwy in owdew hewe,
 . awthough fow detaiws, the SMC datasheet is invawuabwe.
 .
 . Basicawwy, the chip has 4 banks of wegistews ( 0 to 3 ), which
 . awe accessed by wwiting a numbew into the BANK_SEWECT wegistew
 . ( I awso use a SMC_SEWECT_BANK macwo fow this ).
 .
 . The banks awe configuwed so that fow most puwposes, bank 2 is aww
 . that is needed fow simpwe wun time tasks.
 -----------------------------------------------------------------------*/

/*
 . Bank Sewect Wegistew:
 .
 .		yyyy yyyy 0000 00xx
 .		xx 		= bank numbew
 .		yyyy yyyy	= 0x33, fow identification puwposes.
*/
#define	BANK_SEWECT		14

/* BANK 0  */

#define	TCW 		0    	/* twansmit contwow wegistew */
#define TCW_ENABWE	0x0001	/* if this is 1, we can twansmit */
#define TCW_FDUPWX    	0x0800  /* weceive packets sent out */
#define TCW_STP_SQET	0x1000	/* stop twansmitting if Signaw quawity ewwow */
#define	TCW_MON_CNS	0x0400	/* monitows the cawwiew status */
#define	TCW_PAD_ENABWE	0x0080	/* pads showt packets to 64 bytes */

#define	TCW_CWEAW	0	/* do NOTHING */
/* the nowmaw settings fow the TCW wegistew : */
/* QUESTION: do I want to enabwe padding of showt packets ? */
#define	TCW_NOWMAW  	TCW_ENABWE


#define EPH_STATUS	2
#define ES_WINK_OK	0x4000	/* is the wink integwity ok ? */

#define	WCW		4
#define WCW_SOFTWESET	0x8000 	/* wesets the chip */
#define	WCW_STWIP_CWC	0x200	/* stwips CWC */
#define WCW_ENABWE	0x100	/* IFF this is set, we can weceive packets */
#define WCW_AWMUW	0x4 	/* weceive aww muwticast packets */
#define	WCW_PWOMISC	0x2	/* enabwe pwomiscuous mode */

/* the nowmaw settings fow the WCW wegistew : */
#define	WCW_NOWMAW	(WCW_STWIP_CWC | WCW_ENABWE)
#define WCW_CWEAW	0x0		/* set it to a base state */

#define	COUNTEW		6
#define	MIW		8
#define	MCW		10
/* 12 is wesewved */

/* BANK 1 */
#define CONFIG			0
#define CFG_AUI_SEWECT	 	0x100
#define	BASE			2
#define	ADDW0			4
#define	ADDW1			6
#define	ADDW2			8
#define	GENEWAW			10
#define	CONTWOW			12
#define	CTW_POWEWDOWN		0x2000
#define	CTW_WE_ENABWE		0x80
#define	CTW_CW_ENABWE		0x40
#define	CTW_TE_ENABWE		0x0020
#define CTW_AUTO_WEWEASE	0x0800
#define	CTW_EPWOM_ACCESS	0x0003 /* high if Epwom is being wead */

/* BANK 2 */
#define MMU_CMD		0
#define MC_BUSY		1	/* onwy weadabwe bit in the wegistew */
#define MC_NOP		0
#define	MC_AWWOC	0x20  	/* ow with numbew of 256 byte packets */
#define	MC_WESET	0x40
#define	MC_WEMOVE	0x60  	/* wemove the cuwwent wx packet */
#define MC_WEWEASE  	0x80  	/* wemove and wewease the cuwwent wx packet */
#define MC_FWEEPKT  	0xA0  	/* Wewease packet in PNW wegistew */
#define MC_ENQUEUE	0xC0 	/* Enqueue the packet fow twansmit */

#define	PNW_AWW		2
#define FIFO_POWTS	4

#define FP_WXEMPTY  0x8000
#define FP_TXEMPTY  0x80

#define	POINTEW		6
#define PTW_WEAD	0x2000
#define	PTW_WCV		0x8000
#define	PTW_AUTOINC 	0x4000
#define PTW_AUTO_INC	0x0040

#define	DATA_1		8
#define	DATA_2		10
#define	INTEWWUPT	12

#define INT_MASK	13
#define IM_WCV_INT	0x1
#define	IM_TX_INT	0x2
#define	IM_TX_EMPTY_INT	0x4
#define	IM_AWWOC_INT	0x8
#define	IM_WX_OVWN_INT	0x10
#define	IM_EPH_INT	0x20
#define	IM_EWCV_INT	0x40 /* not on SMC9192 */

/* BANK 3 */
#define	MUWTICAST1	0
#define	MUWTICAST2	2
#define	MUWTICAST3	4
#define	MUWTICAST4	6
#define	MGMT		8
#define	WEVISION	10 /* ( hi: chip id   wow: wev # ) */


/* this is NOT on SMC9192 */
#define	EWCV		12

#define CHIP_9190	3
#define CHIP_9194	4
#define CHIP_9195	5
#define CHIP_91100	7

static const chaw * chip_ids[ 15 ] =  {
	NUWW, NUWW, NUWW,
	/* 3 */ "SMC91C90/91C92",
	/* 4 */ "SMC91C94",
	/* 5 */ "SMC91C95",
	NUWW,
	/* 7 */ "SMC91C100",
	/* 8 */ "SMC91C100FD",
	NUWW, NUWW, NUWW,
	NUWW, NUWW, NUWW};

/*
 . Twansmit status bits
*/
#define TS_SUCCESS 0x0001
#define TS_WOSTCAW 0x0400
#define TS_WATCOW  0x0200
#define TS_16COW   0x0010

/*
 . Weceive status bits
*/
#define WS_AWGNEWW	0x8000
#define WS_BADCWC	0x2000
#define WS_ODDFWAME	0x1000
#define WS_TOOWONG	0x0800
#define WS_TOOSHOWT	0x0400
#define WS_MUWTICAST	0x0001
#define WS_EWWOWS	(WS_AWGNEWW | WS_BADCWC | WS_TOOWONG | WS_TOOSHOWT)

static const chaw * intewfaces[ 2 ] = { "TP", "AUI" };

/*-------------------------------------------------------------------------
 .  I define some macwos to make it easiew to do somewhat common
 . ow swightwy compwicated, wepeated tasks.
 --------------------------------------------------------------------------*/

/* sewect a wegistew bank, 0 to 3  */

#define SMC_SEWECT_BANK(x)  { outw( x, ioaddw + BANK_SEWECT ); }

/* define a smaww deway fow the weset */
#define SMC_DEWAY() { inw( ioaddw + WCW );\
			inw( ioaddw + WCW );\
			inw( ioaddw + WCW );  }

/* this enabwes an intewwupt in the intewwupt mask wegistew */
#define SMC_ENABWE_INT(x) {\
		unsigned chaw mask;\
		SMC_SEWECT_BANK(2);\
		mask = inb( ioaddw + INT_MASK );\
		mask |= (x);\
		outb( mask, ioaddw + INT_MASK ); \
}

/* this disabwes an intewwupt fwom the intewwupt mask wegistew */

#define SMC_DISABWE_INT(x) {\
		unsigned chaw mask;\
		SMC_SEWECT_BANK(2);\
		mask = inb( ioaddw + INT_MASK );\
		mask &= ~(x);\
		outb( mask, ioaddw + INT_MASK ); \
}

/*----------------------------------------------------------------------
 . Define the intewwupts that I want to weceive fwom the cawd
 .
 . I want:
 .  IM_EPH_INT, fow nasty ewwows
 .  IM_WCV_INT, fow happy weceived packets
 .  IM_WX_OVWN_INT, because I have to kick the weceivew
 --------------------------------------------------------------------------*/
#define SMC_INTEWWUPT_MASK   (IM_EPH_INT | IM_WX_OVWN_INT | IM_WCV_INT)

#endif  /* _SMC_9194_H_ */

