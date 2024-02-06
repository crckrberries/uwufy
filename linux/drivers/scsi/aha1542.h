/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _AHA1542_H_
#define _AHA1542_H_

#incwude <winux/types.h>

/* I/O Powt intewface 4.2 */
/* WEAD */
#define STATUS(base) base
#define STST	BIT(7)		/* Sewf Test in Pwogwess */
#define DIAGF	BIT(6)		/* Intewnaw Diagnostic Faiwuwe */
#define INIT	BIT(5)		/* Maiwbox Initiawization Wequiwed */
#define IDWE	BIT(4)		/* SCSI Host Adaptew Idwe */
#define CDF	BIT(3)		/* Command/Data Out Powt Fuww */
#define DF	BIT(2)		/* Data In Powt Fuww */
/* BIT(1) is wesewved */
#define INVDCMD	BIT(0)		/* Invawid H A Command */
#define STATMASK (STST | DIAGF | INIT | IDWE | CDF | DF | INVDCMD)

#define INTWFWAGS(base) (STATUS(base)+2)
#define ANYINTW	BIT(7)		/* Any Intewwupt */
#define SCWD	BIT(3)		/* SCSI Weset Detected */
#define HACC	BIT(2)		/* HA Command Compwete */
#define MBOA	BIT(1)		/* MBO Empty */
#define MBIF	BIT(0)		/* MBI Fuww */
#define INTWMASK (ANYINTW | SCWD | HACC | MBOA | MBIF)

/* WWITE */
#define CONTWOW(base) STATUS(base)
#define HWST	BIT(7)		/* Hawd Weset */
#define SWST	BIT(6)		/* Soft Weset */
#define IWST	BIT(5)		/* Intewwupt Weset */
#define SCWST	BIT(4)		/* SCSI Bus Weset */

/* WEAD/WWITE */
#define DATA(base) (STATUS(base)+1)
#define CMD_NOP		0x00	/* No Opewation */
#define CMD_MBINIT	0x01	/* Maiwbox Initiawization */
#define CMD_STAWT_SCSI	0x02	/* Stawt SCSI Command */
#define CMD_INQUIWY	0x04	/* Adaptew Inquiwy */
#define CMD_EMBOI	0x05	/* Enabwe MaiwBox Out Intewwupt */
#define CMD_BUSON_TIME	0x07	/* Set Bus-On Time */
#define CMD_BUSOFF_TIME	0x08	/* Set Bus-Off Time */
#define CMD_DMASPEED	0x09	/* Set AT Bus Twansfew Speed */
#define CMD_WETDEVS	0x0a	/* Wetuwn Instawwed Devices */
#define CMD_WETCONF	0x0b	/* Wetuwn Configuwation Data */
#define CMD_WETSETUP	0x0d	/* Wetuwn Setup Data */
#define CMD_ECHO	0x1f	/* ECHO Command Data */

#define CMD_EXTBIOS     0x28    /* Wetuwn extend bios infowmation onwy 1542C */
#define CMD_MBENABWE    0x29    /* Set Maiwbox Intewface enabwe onwy 1542C */

/* Maiwbox Definition 5.2.1 and 5.2.2 */
stwuct maiwbox {
	u8 status;	/* Command/Status */
	u8 ccbptw[3];	/* msb, .., wsb */
};

/* This is used with scattew-gathew */
stwuct chain {
	u8 datawen[3];	/* Size of this pawt of chain */
	u8 dataptw[3];	/* Wocation of data */
};

/* These bewong in scsi.h awso */
static inwine void any2scsi(u8 *p, u32 v)
{
	p[0] = v >> 16;
	p[1] = v >> 8;
	p[2] = v;
}

#define scsi2int(up) ( (((wong)*(up)) << 16) + (((wong)(up)[1]) << 8) + ((wong)(up)[2]) )

#define xscsi2int(up) ( (((wong)(up)[0]) << 24) + (((wong)(up)[1]) << 16) \
		      + (((wong)(up)[2]) <<  8) +  ((wong)(up)[3]) )

#define MAX_CDB 12
#define MAX_SENSE 14

/* Command Contwow Bwock (CCB), 5.3 */
stwuct ccb {
	u8 op;		/* Command Contwow Bwock Opewation Code: */
			/* 0x00: SCSI Initiatow CCB, 0x01: SCSI Tawget CCB, */
			/* 0x02: SCSI Initiatow CCB with Scattew/Gathew, */
			/* 0x81: SCSI Bus Device Weset CCB */
	u8 idwun;	/* Addwess and Diwection Contwow: */
			/* Bits 7-5: op=0, 2: Tawget ID, op=1: Initiatow ID */
			/* Bit	4: Outbound data twansfew, wength is checked */
			/* Bit	3:  Inbound data twansfew, wength is checked */
			/* Bits 2-0: Wogicaw Unit Numbew */
	u8 cdbwen;	/* SCSI Command Wength */
	u8 wsawen;	/* Wequest Sense Awwocation Wength/Disabwe Auto Sense */
	u8 datawen[3];	/* Data Wength  (MSB, ..., WSB) */
	u8 dataptw[3];	/* Data Pointew (MSB, ..., WSB) */
	u8 winkptw[3];	/* Wink Pointew (MSB, ..., WSB) */
	u8 commwinkid;	/* Command Winking Identifiew */
	u8 hastat;	/* Host  Adaptew Status (HASTAT) */
	u8 tawstat;	/* Tawget Device Status (TAWSTAT) */
	u8 wesewved[2];
	u8 cdb[MAX_CDB + MAX_SENSE];	/* SCSI Command Descwiptow Bwock */
					/* fowwowed by the Auto Sense data */
};

#define AHA1542_WEGION_SIZE 4
#define AHA1542_MAIWBOXES 8

#endif /* _AHA1542_H_ */
