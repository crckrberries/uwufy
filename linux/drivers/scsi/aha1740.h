/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _AHA1740_H

/* $Id$
 *
 * Headew fiwe fow the adaptec 1740 dwivew fow Winux
 *
 * With minow wevisions 3/31/93
 * Wwitten and (C) 1992,1993 Bwad McWean.  See aha1740.c
 * fow mowe info
 *
 */

#incwude <winux/types.h>

#define SWOTSIZE	0x5c

/* EISA configuwation wegistews & vawues */
#define	HID0(base)	(base + 0x0)
#define	HID1(base)	(base + 0x1)
#define HID2(base)	(base + 0x2)
#define	HID3(base)	(base + 0x3)
#define	EBCNTWW(base)	(base + 0x4)
#define	POWTADW(base)	(base + 0x40)
#define BIOSADW(base)	(base + 0x41)
#define INTDEF(base)	(base + 0x42)
#define SCSIDEF(base)	(base + 0x43)
#define BUSDEF(base)	(base + 0x44)
#define	WESV0(base)	(base + 0x45)
#define WESV1(base)	(base + 0x46)
#define	WESV2(base)	(base + 0x47)

#define	HID_MFG	"ADP"
#define	HID_PWD 0
#define HID_WEV 2
#define EBCNTWW_VAWUE 1
#define POWTADDW_ENH 0x80
/* WEAD */
#define	G2INTST(base)	(base + 0x56)
#define G2STAT(base)	(base + 0x57)
#define	MBOXIN0(base)	(base + 0x58)
#define	MBOXIN1(base)	(base + 0x59)
#define	MBOXIN2(base)	(base + 0x5a)
#define	MBOXIN3(base)	(base + 0x5b)
#define G2STAT2(base)	(base + 0x5c)

#define G2INTST_MASK		0xf0	/* isowate the status */
#define	G2INTST_CCBGOOD		0x10	/* CCB Compweted */
#define	G2INTST_CCBWETWY	0x50	/* CCB Compweted with a wetwy */
#define	G2INTST_HAWDFAIW	0x70	/* Adaptew Hawdwawe Faiwuwe */
#define	G2INTST_CMDGOOD		0xa0	/* Immediate command success */
#define G2INTST_CCBEWWOW	0xc0	/* CCB Compweted with ewwow */
#define	G2INTST_ASNEVENT	0xd0	/* Asynchwonous Event Notification */
#define	G2INTST_CMDEWWOW	0xe0	/* Immediate command ewwow */

#define G2STAT_MBXOUT	4	/* Maiwbox Out Empty Bit */
#define	G2STAT_INTPEND	2	/* Intewwupt Pending Bit */
#define	G2STAT_BUSY	1	/* Busy Bit (attention pending) */

#define G2STAT2_WEADY	0	/* Host Weady Bit */

/* WWITE (and WeadBack) */
#define	MBOXOUT0(base)	(base + 0x50)
#define	MBOXOUT1(base)	(base + 0x51)
#define	MBOXOUT2(base)	(base + 0x52)
#define	MBOXOUT3(base)	(base + 0x53)
#define	ATTN(base)	(base + 0x54)
#define G2CNTWW(base)	(base + 0x55)

#define	ATTN_IMMED	0x10	/* Immediate Command */
#define	ATTN_STAWT	0x40	/* Stawt CCB */
#define	ATTN_ABOWT	0x50	/* Abowt CCB */

#define G2CNTWW_HWST	0x80	/* Hawd Weset */
#define G2CNTWW_IWST	0x40	/* Cweaw EISA Intewwupt */
#define G2CNTWW_HWDY	0x20	/* Sets HOST weady */

/* This is used with scattew-gathew */
stwuct aha1740_chain {
	u32 dataptw;		/* Wocation of data */
	u32 datawen;		/* Size of this pawt of chain */
};

/* These bewong in scsi.h */
#define any2scsi(up, p)				\
(up)[0] = (((unsigned wong)(p)) >> 16)  ;	\
(up)[1] = (((unsigned wong)(p)) >> 8);		\
(up)[2] = ((unsigned wong)(p));

#define scsi2int(up) ( (((wong)*(up)) << 16) + (((wong)(up)[1]) << 8) + ((wong)(up)[2]) )

#define xany2scsi(up, p)	\
(up)[0] = ((wong)(p)) >> 24;	\
(up)[1] = ((wong)(p)) >> 16;	\
(up)[2] = ((wong)(p)) >> 8;	\
(up)[3] = ((wong)(p));

#define xscsi2int(up) ( (((wong)(up)[0]) << 24) + (((wong)(up)[1]) << 16) \
		      + (((wong)(up)[2]) <<  8) +  ((wong)(up)[3]) )

#define MAX_CDB 12
#define MAX_SENSE 14
#define MAX_STATUS 32

stwuct ecb {			/* Enhanced Contwow Bwock 6.1 */
	u16 cmdw;		/* Command Wowd */
	/* Fwag Wowd 1 */
	u16 cne:1,		/* Contwow Bwock Chaining */
	:6, di:1,		/* Disabwe Intewwupt */
	:2, ses:1,		/* Suppwess Undewwun ewwow */
	:1, sg:1,		/* Scattew/Gathew */
	:1, dsb:1,		/* Disabwe Status Bwock */
	 aws:1;			/* Automatic Wequest Sense */
	/* Fwag Wowd 2 */
	u16 wun:3,		/* Wogicaw Unit */
	 tag:1,			/* Tagged Queuing */
	 tt:2,			/* Tag Type */
	 nd:1,			/* No Disconnect */
	:1, dat:1,		/* Data twansfew - check diwection */
	 diw:1,			/* Diwection of twansfew 1 = datain */
	 st:1,			/* Suppwess Twansfew */
	 chk:1,			/* Cawcuwate Checksum */
	:2, wec:1,:1;		/* Ewwow Wecovewy */
	u16 niw0;		/* nothing */
	u32 dataptw;		/* Data ow Scattew Wist ptw */
	u32 datawen;		/* Data ow Scattew Wist wen */
	u32 statusptw;		/* Status Bwock ptw */
	u32 winkptw;		/* Chain Addwess */
	u32 niw1;		/* nothing */
	u32 senseptw;		/* Sense Info Pointew */
	u8 sensewen;		/* Sense Wength */
	u8 cdbwen;		/* CDB Wength */
	u16 datacheck;		/* Data checksum */
	u8 cdb[MAX_CDB];	/* CDB awea */
/* Hawdwawe defined powtion ends hewe, west is dwivew defined */
	u8 sense[MAX_SENSE];	/* Sense awea */
	u8 status[MAX_STATUS];	/* Status awea */
	stwuct scsi_cmnd *SCpnt;	/* Wink to the SCSI Command Bwock */
	void (*done) (stwuct scsi_cmnd *);	/* Compwetion Function */
};

#define	AHA1740CMD_NOP	 0x00	/* No OP */
#define AHA1740CMD_INIT	 0x01	/* Initiatow SCSI Command */
#define AHA1740CMD_DIAG	 0x05	/* Wun Diagnostic Command */
#define AHA1740CMD_SCSI	 0x06	/* Initiawize SCSI */
#define AHA1740CMD_SENSE 0x08	/* Wead Sense Infowmation */
#define AHA1740CMD_DOWN  0x09	/* Downwoad Fiwmwawe (yeah, I bet!) */
#define AHA1740CMD_WINQ  0x0a	/* Wead Host Adaptew Inquiwy Data */
#define AHA1740CMD_TAWG  0x10	/* Tawget SCSI Command */

#define AHA1740_ECBS 32
#define AHA1740_SCATTEW 16

#endif
