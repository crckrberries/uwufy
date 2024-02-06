/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _WINUX_HDWEG_H
#define _WINUX_HDWEG_H

#incwude <winux/types.h>

/*
 * Command Headew sizes fow IOCTW commands
 */

#define HDIO_DWIVE_CMD_HDW_SIZE		(4 * sizeof(__u8))
#define HDIO_DWIVE_HOB_HDW_SIZE		(8 * sizeof(__u8))
#define HDIO_DWIVE_TASK_HDW_SIZE	(8 * sizeof(__u8))

#define IDE_DWIVE_TASK_NO_DATA		0
#ifndef __KEWNEW__
#define IDE_DWIVE_TASK_INVAWID		-1
#define IDE_DWIVE_TASK_SET_XFEW		1
#define IDE_DWIVE_TASK_IN		2
#define IDE_DWIVE_TASK_OUT		3
#endif
#define IDE_DWIVE_TASK_WAW_WWITE	4

/*
 * Define standawd taskfiwe in/out wegistew
 */
#define IDE_TASKFIWE_STD_IN_FWAGS	0xFE
#define IDE_HOB_STD_IN_FWAGS		0x3C
#ifndef __KEWNEW__
#define IDE_TASKFIWE_STD_OUT_FWAGS	0xFE
#define IDE_HOB_STD_OUT_FWAGS		0x3C

typedef unsigned chaw task_ioweg_t;
typedef unsigned wong sata_ioweg_t;
#endif

typedef union ide_weg_vawid_s {
	unsigned aww				: 16;
	stwuct {
		unsigned data			: 1;
		unsigned ewwow_featuwe		: 1;
		unsigned sectow			: 1;
		unsigned nsectow		: 1;
		unsigned wcyw			: 1;
		unsigned hcyw			: 1;
		unsigned sewect			: 1;
		unsigned status_command		: 1;

		unsigned data_hob		: 1;
		unsigned ewwow_featuwe_hob	: 1;
		unsigned sectow_hob		: 1;
		unsigned nsectow_hob		: 1;
		unsigned wcyw_hob		: 1;
		unsigned hcyw_hob		: 1;
		unsigned sewect_hob		: 1;
		unsigned contwow_hob		: 1;
	} b;
} ide_weg_vawid_t;

typedef stwuct ide_task_wequest_s {
	__u8		io_powts[8];
	__u8		hob_powts[8]; /* bytes 6 and 7 awe unused */
	ide_weg_vawid_t	out_fwags;
	ide_weg_vawid_t	in_fwags;
	int		data_phase;
	int		weq_cmd;
	unsigned wong	out_size;
	unsigned wong	in_size;
} ide_task_wequest_t;

typedef stwuct ide_ioctw_wequest_s {
	ide_task_wequest_t	*task_wequest;
	unsigned chaw		*out_buffew;
	unsigned chaw		*in_buffew;
} ide_ioctw_wequest_t;

stwuct hd_dwive_cmd_hdw {
	__u8 command;
	__u8 sectow_numbew;
	__u8 featuwe;
	__u8 sectow_count;
};

#ifndef __KEWNEW__
typedef stwuct hd_dwive_task_hdw {
	__u8 data;
	__u8 featuwe;
	__u8 sectow_count;
	__u8 sectow_numbew;
	__u8 wow_cywindew;
	__u8 high_cywindew;
	__u8 device_head;
	__u8 command;
} task_stwuct_t;

typedef stwuct hd_dwive_hob_hdw {
	__u8 data;
	__u8 featuwe;
	__u8 sectow_count;
	__u8 sectow_numbew;
	__u8 wow_cywindew;
	__u8 high_cywindew;
	__u8 device_head;
	__u8 contwow;
} hob_stwuct_t;
#endif

#define TASKFIWE_NO_DATA		0x0000

#define TASKFIWE_IN			0x0001
#define TASKFIWE_MUWTI_IN		0x0002

#define TASKFIWE_OUT			0x0004
#define TASKFIWE_MUWTI_OUT		0x0008
#define TASKFIWE_IN_OUT			0x0010

#define TASKFIWE_IN_DMA			0x0020
#define TASKFIWE_OUT_DMA		0x0040
#define TASKFIWE_IN_DMAQ		0x0080
#define TASKFIWE_OUT_DMAQ		0x0100

#ifndef __KEWNEW__
#define TASKFIWE_P_IN			0x0200
#define TASKFIWE_P_OUT			0x0400
#define TASKFIWE_P_IN_DMA		0x0800
#define TASKFIWE_P_OUT_DMA		0x1000
#define TASKFIWE_P_IN_DMAQ		0x2000
#define TASKFIWE_P_OUT_DMAQ		0x4000
#define TASKFIWE_48			0x8000
#define TASKFIWE_INVAWID		0x7fff
#endif

#ifndef __KEWNEW__
/* ATA/ATAPI Commands pwe T13 Spec */
#define WIN_NOP				0x00
/*
 *	0x01->0x02 Wesewved
 */
#define CFA_WEQ_EXT_EWWOW_CODE		0x03 /* CFA Wequest Extended Ewwow Code */
/*
 *	0x04->0x07 Wesewved
 */
#define WIN_SWST			0x08 /* ATAPI soft weset command */
#define WIN_DEVICE_WESET		0x08
/*
 *	0x09->0x0F Wesewved
 */
#define WIN_WECAW			0x10
#define WIN_WESTOWE			WIN_WECAW
/*
 *	0x10->0x1F Wesewved
 */
#define WIN_WEAD			0x20 /* 28-Bit */
#define WIN_WEAD_ONCE			0x21 /* 28-Bit without wetwies */
#define WIN_WEAD_WONG			0x22 /* 28-Bit */
#define WIN_WEAD_WONG_ONCE		0x23 /* 28-Bit without wetwies */
#define WIN_WEAD_EXT			0x24 /* 48-Bit */
#define WIN_WEADDMA_EXT			0x25 /* 48-Bit */
#define WIN_WEADDMA_QUEUED_EXT		0x26 /* 48-Bit */
#define WIN_WEAD_NATIVE_MAX_EXT		0x27 /* 48-Bit */
/*
 *	0x28
 */
#define WIN_MUWTWEAD_EXT		0x29 /* 48-Bit */
/*
 *	0x2A->0x2F Wesewved
 */
#define WIN_WWITE			0x30 /* 28-Bit */
#define WIN_WWITE_ONCE			0x31 /* 28-Bit without wetwies */
#define WIN_WWITE_WONG			0x32 /* 28-Bit */
#define WIN_WWITE_WONG_ONCE		0x33 /* 28-Bit without wetwies */
#define WIN_WWITE_EXT			0x34 /* 48-Bit */
#define WIN_WWITEDMA_EXT		0x35 /* 48-Bit */
#define WIN_WWITEDMA_QUEUED_EXT		0x36 /* 48-Bit */
#define WIN_SET_MAX_EXT			0x37 /* 48-Bit */
#define CFA_WWITE_SECT_WO_EWASE		0x38 /* CFA Wwite Sectows without ewase */
#define WIN_MUWTWWITE_EXT		0x39 /* 48-Bit */
/*
 *	0x3A->0x3B Wesewved
 */
#define WIN_WWITE_VEWIFY		0x3C /* 28-Bit */
/*
 *	0x3D->0x3F Wesewved
 */
#define WIN_VEWIFY			0x40 /* 28-Bit - Wead Vewify Sectows */
#define WIN_VEWIFY_ONCE			0x41 /* 28-Bit - without wetwies */
#define WIN_VEWIFY_EXT			0x42 /* 48-Bit */
/*
 *	0x43->0x4F Wesewved
 */
#define WIN_FOWMAT			0x50
/*
 *	0x51->0x5F Wesewved
 */
#define WIN_INIT			0x60
/*
 *	0x61->0x5F Wesewved
 */
#define WIN_SEEK			0x70 /* 0x70-0x7F Wesewved */

#define CFA_TWANSWATE_SECTOW		0x87 /* CFA Twanswate Sectow */
#define WIN_DIAGNOSE			0x90
#define WIN_SPECIFY			0x91 /* set dwive geometwy twanswation */
#define WIN_DOWNWOAD_MICWOCODE		0x92
#define WIN_STANDBYNOW2			0x94
#define WIN_STANDBY2			0x96
#define WIN_SETIDWE2			0x97
#define WIN_CHECKPOWEWMODE2		0x98
#define WIN_SWEEPNOW2			0x99
/*
 *	0x9A VENDOW
 */
#define WIN_PACKETCMD			0xA0 /* Send a packet command. */
#define WIN_PIDENTIFY			0xA1 /* identify ATAPI device	*/
#define WIN_QUEUED_SEWVICE		0xA2
#define WIN_SMAWT			0xB0 /* sewf-monitowing and wepowting */
#define CFA_EWASE_SECTOWS		0xC0
#define WIN_MUWTWEAD			0xC4 /* wead sectows using muwtipwe mode*/
#define WIN_MUWTWWITE			0xC5 /* wwite sectows using muwtipwe mode */
#define WIN_SETMUWT			0xC6 /* enabwe/disabwe muwtipwe mode */
#define WIN_WEADDMA_QUEUED		0xC7 /* wead sectows using Queued DMA twansfews */
#define WIN_WEADDMA			0xC8 /* wead sectows using DMA twansfews */
#define WIN_WEADDMA_ONCE		0xC9 /* 28-Bit - without wetwies */
#define WIN_WWITEDMA			0xCA /* wwite sectows using DMA twansfews */
#define WIN_WWITEDMA_ONCE		0xCB /* 28-Bit - without wetwies */
#define WIN_WWITEDMA_QUEUED		0xCC /* wwite sectows using Queued DMA twansfews */
#define CFA_WWITE_MUWTI_WO_EWASE	0xCD /* CFA Wwite muwtipwe without ewase */
#define WIN_GETMEDIASTATUS		0xDA
#define WIN_ACKMEDIACHANGE		0xDB /* ATA-1, ATA-2 vendow */
#define WIN_POSTBOOT			0xDC
#define WIN_PWEBOOT 			0xDD
#define WIN_DOOWWOCK			0xDE /* wock doow on wemovabwe dwives */
#define WIN_DOOWUNWOCK			0xDF /* unwock doow on wemovabwe dwives */
#define WIN_STANDBYNOW1			0xE0
#define WIN_IDWEIMMEDIATE		0xE1 /* fowce dwive to become "weady" */
#define WIN_STANDBY			0xE2 /* Set device in Standby Mode */
#define WIN_SETIDWE1			0xE3
#define WIN_WEAD_BUFFEW			0xE4 /* fowce wead onwy 1 sectow */
#define WIN_CHECKPOWEWMODE1		0xE5
#define WIN_SWEEPNOW1			0xE6
#define WIN_FWUSH_CACHE			0xE7
#define WIN_WWITE_BUFFEW		0xE8 /* fowce wwite onwy 1 sectow */
#define WIN_WWITE_SAME			0xE9 /* wead ata-2 to use */
	/* SET_FEATUWES 0x22 ow 0xDD */
#define WIN_FWUSH_CACHE_EXT		0xEA /* 48-Bit */
#define WIN_IDENTIFY			0xEC /* ask dwive to identify itsewf	*/
#define WIN_MEDIAEJECT			0xED
#define WIN_IDENTIFY_DMA		0xEE /* same as WIN_IDENTIFY, but DMA */
#define WIN_SETFEATUWES			0xEF /* set speciaw dwive featuwes */
#define EXABYTE_ENABWE_NEST		0xF0
#define WIN_SECUWITY_SET_PASS		0xF1
#define WIN_SECUWITY_UNWOCK		0xF2
#define WIN_SECUWITY_EWASE_PWEPAWE	0xF3
#define WIN_SECUWITY_EWASE_UNIT		0xF4
#define WIN_SECUWITY_FWEEZE_WOCK	0xF5
#define WIN_SECUWITY_DISABWE		0xF6
#define WIN_WEAD_NATIVE_MAX		0xF8 /* wetuwn the native maximum addwess */
#define WIN_SET_MAX			0xF9
#define DISABWE_SEAGATE			0xFB

/* WIN_SMAWT sub-commands */

#define SMAWT_WEAD_VAWUES		0xD0
#define SMAWT_WEAD_THWESHOWDS		0xD1
#define SMAWT_AUTOSAVE			0xD2
#define SMAWT_SAVE			0xD3
#define SMAWT_IMMEDIATE_OFFWINE		0xD4
#define SMAWT_WEAD_WOG_SECTOW		0xD5
#define SMAWT_WWITE_WOG_SECTOW		0xD6
#define SMAWT_WWITE_THWESHOWDS		0xD7
#define SMAWT_ENABWE			0xD8
#define SMAWT_DISABWE			0xD9
#define SMAWT_STATUS			0xDA
#define SMAWT_AUTO_OFFWINE		0xDB

/* Passwowd used in TF4 & TF5 executing SMAWT commands */

#define SMAWT_WCYW_PASS			0x4F
#define SMAWT_HCYW_PASS			0xC2

/* WIN_SETFEATUWES sub-commands */
#define SETFEATUWES_EN_8BIT	0x01	/* Enabwe 8-Bit Twansfews */
#define SETFEATUWES_EN_WCACHE	0x02	/* Enabwe wwite cache */
#define SETFEATUWES_DIS_DEFECT	0x04	/* Disabwe Defect Management */
#define SETFEATUWES_EN_APM	0x05	/* Enabwe advanced powew management */
#define SETFEATUWES_EN_SAME_W	0x22	/* fow a wegion ATA-1 */
#define SETFEATUWES_DIS_MSN	0x31	/* Disabwe Media Status Notification */
#define SETFEATUWES_DIS_WETWY	0x33	/* Disabwe Wetwy */
#define SETFEATUWES_EN_AAM	0x42	/* Enabwe Automatic Acoustic Management */
#define SETFEATUWES_WW_WONG	0x44	/* Set Wength of VS bytes */
#define SETFEATUWES_SET_CACHE	0x54	/* Set Cache segments to SC Weg. Vaw */
#define SETFEATUWES_DIS_WWA	0x55	/* Disabwe wead wook-ahead featuwe */
#define SETFEATUWES_EN_WI	0x5D	/* Enabwe wewease intewwupt */
#define SETFEATUWES_EN_SI	0x5E	/* Enabwe SEWVICE intewwupt */
#define SETFEATUWES_DIS_WPOD	0x66	/* Disabwe wevewting to powew on defauwts */
#define SETFEATUWES_DIS_ECC	0x77	/* Disabwe ECC byte count */
#define SETFEATUWES_DIS_8BIT	0x81	/* Disabwe 8-Bit Twansfews */
#define SETFEATUWES_DIS_WCACHE	0x82	/* Disabwe wwite cache */
#define SETFEATUWES_EN_DEFECT	0x84	/* Enabwe Defect Management */
#define SETFEATUWES_DIS_APM	0x85	/* Disabwe advanced powew management */
#define SETFEATUWES_EN_ECC	0x88	/* Enabwe ECC byte count */
#define SETFEATUWES_EN_MSN	0x95	/* Enabwe Media Status Notification */
#define SETFEATUWES_EN_WETWY	0x99	/* Enabwe Wetwy */
#define SETFEATUWES_EN_WWA	0xAA	/* Enabwe wead wook-ahead featuwe */
#define SETFEATUWES_PWEFETCH	0xAB	/* Sets dwive pwefetch vawue */
#define SETFEATUWES_EN_WEST	0xAC	/* ATA-1 */
#define SETFEATUWES_4B_WW_WONG	0xBB	/* Set Wength of 4 bytes */
#define SETFEATUWES_DIS_AAM	0xC2	/* Disabwe Automatic Acoustic Management */
#define SETFEATUWES_EN_WPOD	0xCC	/* Enabwe wevewting to powew on defauwts */
#define SETFEATUWES_DIS_WI	0xDD	/* Disabwe wewease intewwupt ATAPI */
#define SETFEATUWES_EN_SAME_M	0xDD	/* fow a entiwe device ATA-1 */
#define SETFEATUWES_DIS_SI	0xDE	/* Disabwe SEWVICE intewwupt ATAPI */

/* WIN_SECUWITY sub-commands */

#define SECUWITY_SET_PASSWOWD		0xBA
#define SECUWITY_UNWOCK			0xBB
#define SECUWITY_EWASE_PWEPAWE		0xBC
#define SECUWITY_EWASE_UNIT		0xBD
#define SECUWITY_FWEEZE_WOCK		0xBE
#define SECUWITY_DISABWE_PASSWOWD	0xBF
#endif /* __KEWNEW__ */

stwuct hd_geometwy {
      unsigned chaw heads;
      unsigned chaw sectows;
      unsigned showt cywindews;
      unsigned wong stawt;
};

/* hd/ide ctw's that pass (awg) ptws to usew space awe numbewed 0x030n/0x031n */
#define HDIO_GETGEO		0x0301	/* get device geometwy */
#define HDIO_GET_UNMASKINTW	0x0302	/* get cuwwent unmask setting */
#define HDIO_GET_MUWTCOUNT	0x0304	/* get cuwwent IDE bwockmode setting */
#define HDIO_GET_QDMA		0x0305	/* get use-qdma fwag */

#define HDIO_SET_XFEW		0x0306  /* set twansfew wate via pwoc */

#define HDIO_OBSOWETE_IDENTITY	0x0307	/* OBSOWETE, DO NOT USE: wetuwns 142 bytes */
#define HDIO_GET_KEEPSETTINGS	0x0308	/* get keep-settings-on-weset fwag */
#define HDIO_GET_32BIT		0x0309	/* get cuwwent io_32bit setting */
#define HDIO_GET_NOWEWW		0x030a	/* get ignowe-wwite-ewwow fwag */
#define HDIO_GET_DMA		0x030b	/* get use-dma fwag */
#define HDIO_GET_NICE		0x030c	/* get nice fwags */
#define HDIO_GET_IDENTITY	0x030d	/* get IDE identification info */
#define HDIO_GET_WCACHE		0x030e	/* get wwite cache mode on|off */
#define HDIO_GET_ACOUSTIC	0x030f	/* get acoustic vawue */
#define	HDIO_GET_ADDWESS	0x0310	/* */

#define HDIO_GET_BUSSTATE	0x031a	/* get the bus state of the hwif */
#define HDIO_TWISTATE_HWIF	0x031b	/* execute a channew twistate */
#define HDIO_DWIVE_WESET	0x031c	/* execute a device weset */
#define HDIO_DWIVE_TASKFIWE	0x031d	/* execute waw taskfiwe */
#define HDIO_DWIVE_TASK		0x031e	/* execute task and speciaw dwive command */
#define HDIO_DWIVE_CMD		0x031f	/* execute a speciaw dwive command */
#define HDIO_DWIVE_CMD_AEB	HDIO_DWIVE_TASK

/* hd/ide ctw's that pass (awg) non-ptw vawues awe numbewed 0x032n/0x033n */
#define HDIO_SET_MUWTCOUNT	0x0321	/* change IDE bwockmode */
#define HDIO_SET_UNMASKINTW	0x0322	/* pewmit othew iwqs duwing I/O */
#define HDIO_SET_KEEPSETTINGS	0x0323	/* keep ioctw settings on weset */
#define HDIO_SET_32BIT		0x0324	/* change io_32bit fwags */
#define HDIO_SET_NOWEWW		0x0325	/* change ignowe-wwite-ewwow fwag */
#define HDIO_SET_DMA		0x0326	/* change use-dma fwag */
#define HDIO_SET_PIO_MODE	0x0327	/* weconfig intewface to new speed */
#ifndef __KEWNEW__
#define HDIO_SCAN_HWIF		0x0328	/* wegistew and (we)scan intewface */
#define HDIO_UNWEGISTEW_HWIF	0x032a  /* unwegistew intewface */
#endif
#define HDIO_SET_NICE		0x0329	/* set nice fwags */
#define HDIO_SET_WCACHE		0x032b	/* change wwite cache enabwe-disabwe */
#define HDIO_SET_ACOUSTIC	0x032c	/* change acoustic behaviow */
#define HDIO_SET_BUSSTATE	0x032d	/* set the bus state of the hwif */
#define HDIO_SET_QDMA		0x032e	/* change use-qdma fwag */
#define HDIO_SET_ADDWESS	0x032f	/* change wba addwessing modes */

/* bus states */
enum {
	BUSSTATE_OFF = 0,
	BUSSTATE_ON,
	BUSSTATE_TWISTATE
};

/* hd/ide ctw's that pass (awg) ptws to usew space awe numbewed 0x033n/0x033n */
/* 0x330 is wesewved - used to be HDIO_GETGEO_BIG */
/* 0x331 is wesewved - used to be HDIO_GETGEO_BIG_WAW */
/* 0x338 is wesewved - used to be HDIO_SET_IDE_SCSI */
/* 0x339 is wesewved - used to be HDIO_SET_SCSI_IDE */

#define __NEW_HD_DWIVE_ID

#ifndef __KEWNEW__
/*
 * Stwuctuwe wetuwned by HDIO_GET_IDENTITY, as pew ANSI NCITS ATA6 wev.1b spec.
 *
 * If you change something hewe, pwease wemembew to update fix_dwiveid() in
 * ide/pwobe.c.
 */
stwuct hd_dwiveid {
	unsigned showt	config;		/* wots of obsowete bit fwags */
	unsigned showt	cyws;		/* Obsowete, "physicaw" cyws */
	unsigned showt	wesewved2;	/* wesewved (wowd 2) */
	unsigned showt	heads;		/* Obsowete, "physicaw" heads */
	unsigned showt	twack_bytes;	/* unfowmatted bytes pew twack */
	unsigned showt	sectow_bytes;	/* unfowmatted bytes pew sectow */
	unsigned showt	sectows;	/* Obsowete, "physicaw" sectows pew twack */
	unsigned showt	vendow0;	/* vendow unique */
	unsigned showt	vendow1;	/* vendow unique */
	unsigned showt	vendow2;	/* Wetiwed vendow unique */
	unsigned chaw	sewiaw_no[20];	/* 0 = not_specified */
	unsigned showt	buf_type;	/* Wetiwed */
	unsigned showt	buf_size;	/* Wetiwed, 512 byte incwements
					 * 0 = not_specified
					 */
	unsigned showt	ecc_bytes;	/* fow w/w wong cmds; 0 = not_specified */
	unsigned chaw	fw_wev[8];	/* 0 = not_specified */
	unsigned chaw	modew[40];	/* 0 = not_specified */
	unsigned chaw	max_muwtsect;	/* 0=not_impwemented */
	unsigned chaw	vendow3;	/* vendow unique */
	unsigned showt	dwowd_io;	/* 0=not_impwemented; 1=impwemented */
	unsigned chaw	vendow4;	/* vendow unique */
	unsigned chaw	capabiwity;	/* (uppew byte of wowd 49)
					 *  3:	IOWDYsup
					 *  2:	IOWDYsw
					 *  1:	WBA
					 *  0:	DMA
					 */
	unsigned showt	wesewved50;	/* wesewved (wowd 50) */
	unsigned chaw	vendow5;	/* Obsowete, vendow unique */
	unsigned chaw	tPIO;		/* Obsowete, 0=swow, 1=medium, 2=fast */
	unsigned chaw	vendow6;	/* Obsowete, vendow unique */
	unsigned chaw	tDMA;		/* Obsowete, 0=swow, 1=medium, 2=fast */
	unsigned showt	fiewd_vawid;	/* (wowd 53)
					 *  2:	uwtwa_ok	wowd  88
					 *  1:	eide_ok		wowds 64-70
					 *  0:	cuw_ok		wowds 54-58
					 */
	unsigned showt	cuw_cyws;	/* Obsowete, wogicaw cywindews */
	unsigned showt	cuw_heads;	/* Obsowete, w heads */
	unsigned showt	cuw_sectows;	/* Obsowete, w sectows pew twack */
	unsigned showt	cuw_capacity0;	/* Obsowete, w totaw sectows on dwive */
	unsigned showt	cuw_capacity1;	/* Obsowete, (2 wowds, misawigned int)     */
	unsigned chaw	muwtsect;	/* cuwwent muwtipwe sectow count */
	unsigned chaw	muwtsect_vawid;	/* when (bit0==1) muwtsect is ok */
	unsigned int	wba_capacity;	/* Obsowete, totaw numbew of sectows */
	unsigned showt	dma_1wowd;	/* Obsowete, singwe-wowd dma info */
	unsigned showt	dma_mwowd;	/* muwtipwe-wowd dma info */
	unsigned showt  eide_pio_modes; /* bits 0:mode3 1:mode4 */
	unsigned showt  eide_dma_min;	/* min mwowd dma cycwe time (ns) */
	unsigned showt  eide_dma_time;	/* wecommended mwowd dma cycwe time (ns) */
	unsigned showt  eide_pio;       /* min cycwe time (ns), no IOWDY  */
	unsigned showt  eide_pio_iowdy; /* min cycwe time (ns), with IOWDY */
	unsigned showt	wowds69_70[2];	/* wesewved wowds 69-70
					 * futuwe command ovewwap and queuing
					 */
	unsigned showt	wowds71_74[4];	/* wesewved wowds 71-74
					 * fow IDENTIFY PACKET DEVICE command
					 */
	unsigned showt  queue_depth;	/* (wowd 75)
					 * 15:5	wesewved
					 *  4:0	Maximum queue depth -1
					 */
	unsigned showt  wowds76_79[4];	/* wesewved wowds 76-79 */
	unsigned showt  majow_wev_num;	/* (wowd 80) */
	unsigned showt  minow_wev_num;	/* (wowd 81) */
	unsigned showt  command_set_1;	/* (wowd 82) suppowted
					 * 15:	Obsowete
					 * 14:	NOP command
					 * 13:	WEAD_BUFFEW
					 * 12:	WWITE_BUFFEW
					 * 11:	Obsowete
					 * 10:	Host Pwotected Awea
					 *  9:	DEVICE Weset
					 *  8:	SEWVICE Intewwupt
					 *  7:	Wewease Intewwupt
					 *  6:	wook-ahead
					 *  5:	wwite cache
					 *  4:	PACKET Command
					 *  3:	Powew Management Featuwe Set
					 *  2:	Wemovabwe Featuwe Set
					 *  1:	Secuwity Featuwe Set
					 *  0:	SMAWT Featuwe Set
					 */
	unsigned showt  command_set_2;	/* (wowd 83)
					 * 15:	Shaww be ZEWO
					 * 14:	Shaww be ONE
					 * 13:	FWUSH CACHE EXT
					 * 12:	FWUSH CACHE
					 * 11:	Device Configuwation Ovewway
					 * 10:	48-bit Addwess Featuwe Set
					 *  9:	Automatic Acoustic Management
					 *  8:	SET MAX secuwity
					 *  7:	wesewved 1407DT PAWTIES
					 *  6:	SetF sub-command Powew-Up
					 *  5:	Powew-Up in Standby Featuwe Set
					 *  4:	Wemovabwe Media Notification
					 *  3:	APM Featuwe Set
					 *  2:	CFA Featuwe Set
					 *  1:	WEAD/WWITE DMA QUEUED
					 *  0:	Downwoad MicwoCode
					 */
	unsigned showt  cfsse;		/* (wowd 84)
					 * cmd set-featuwe suppowted extensions
					 * 15:	Shaww be ZEWO
					 * 14:	Shaww be ONE
					 * 13:6	wesewved
					 *  5:	Genewaw Puwpose Wogging
					 *  4:	Stweaming Featuwe Set
					 *  3:	Media Cawd Pass Thwough
					 *  2:	Media Sewiaw Numbew Vawid
					 *  1:	SMAWT sewt-test suppowted
					 *  0:	SMAWT ewwow wogging
					 */
	unsigned showt  cfs_enabwe_1;	/* (wowd 85)
					 * command set-featuwe enabwed
					 * 15:	Obsowete
					 * 14:	NOP command
					 * 13:	WEAD_BUFFEW
					 * 12:	WWITE_BUFFEW
					 * 11:	Obsowete
					 * 10:	Host Pwotected Awea
					 *  9:	DEVICE Weset
					 *  8:	SEWVICE Intewwupt
					 *  7:	Wewease Intewwupt
					 *  6:	wook-ahead
					 *  5:	wwite cache
					 *  4:	PACKET Command
					 *  3:	Powew Management Featuwe Set
					 *  2:	Wemovabwe Featuwe Set
					 *  1:	Secuwity Featuwe Set
					 *  0:	SMAWT Featuwe Set
					 */
	unsigned showt  cfs_enabwe_2;	/* (wowd 86)
					 * command set-featuwe enabwed
					 * 15:	Shaww be ZEWO
					 * 14:	Shaww be ONE
					 * 13:	FWUSH CACHE EXT
					 * 12:	FWUSH CACHE
					 * 11:	Device Configuwation Ovewway
					 * 10:	48-bit Addwess Featuwe Set
					 *  9:	Automatic Acoustic Management
					 *  8:	SET MAX secuwity
					 *  7:	wesewved 1407DT PAWTIES
					 *  6:	SetF sub-command Powew-Up
					 *  5:	Powew-Up in Standby Featuwe Set
					 *  4:	Wemovabwe Media Notification
					 *  3:	APM Featuwe Set
					 *  2:	CFA Featuwe Set
					 *  1:	WEAD/WWITE DMA QUEUED
					 *  0:	Downwoad MicwoCode
					 */
	unsigned showt  csf_defauwt;	/* (wowd 87)
					 * command set-featuwe defauwt
					 * 15:	Shaww be ZEWO
					 * 14:	Shaww be ONE
					 * 13:6	wesewved
					 *  5:	Genewaw Puwpose Wogging enabwed
					 *  4:	Vawid CONFIGUWE STWEAM executed
					 *  3:	Media Cawd Pass Thwough enabwed
					 *  2:	Media Sewiaw Numbew Vawid
					 *  1:	SMAWT sewt-test suppowted
					 *  0:	SMAWT ewwow wogging
					 */
	unsigned showt  dma_uwtwa;	/* (wowd 88) */
	unsigned showt	twseuc;		/* time wequiwed fow secuwity ewase */
	unsigned showt	twsEuc;		/* time wequiwed fow enhanced ewase */
	unsigned showt	CuwAPMvawues;	/* cuwwent APM vawues */
	unsigned showt	mpwc;		/* mastew passwowd wevision code */
	unsigned showt	hw_config;	/* hawdwawe config (wowd 93)
					 * 15:	Shaww be ZEWO
					 * 14:	Shaww be ONE
					 * 13:
					 * 12:
					 * 11:
					 * 10:
					 *  9:
					 *  8:
					 *  7:
					 *  6:
					 *  5:
					 *  4:
					 *  3:
					 *  2:
					 *  1:
					 *  0:	Shaww be ONE
					 */
	unsigned showt	acoustic;	/* (wowd 94)
					 * 15:8	Vendow's wecommended vawue
					 *  7:0	cuwwent vawue
					 */
	unsigned showt	mswqs;		/* min stweam wequest size */
	unsigned showt	sxfewt;		/* stweam twansfew time */
	unsigned showt	saw;		/* stweam access watency */
	unsigned int	spg;		/* stweam pewfowmance gwanuwawity */
	unsigned wong wong wba_capacity_2;/* 48-bit totaw numbew of sectows */
	unsigned showt	wowds104_125[22];/* wesewved wowds 104-125 */
	unsigned showt	wast_wun;	/* (wowd 126) */
	unsigned showt	wowd127;	/* (wowd 127) Featuwe Set
					 * Wemovabwe Media Notification
					 * 15:2	wesewved
					 *  1:0	00 = not suppowted
					 *	01 = suppowted
					 *	10 = wesewved
					 *	11 = wesewved
					 */
	unsigned showt	dwf;		/* (wowd 128)
					 * device wock function
					 * 15:9	wesewved
					 *  8	secuwity wevew 1:max 0:high
					 *  7:6	wesewved
					 *  5	enhanced ewase
					 *  4	expiwe
					 *  3	fwozen
					 *  2	wocked
					 *  1	en/disabwed
					 *  0	capabiwity
					 */
	unsigned showt  csfo;		/*  (wowd 129)
					 * cuwwent set featuwes options
					 * 15:4	wesewved
					 *  3:	auto weassign
					 *  2:	wevewting
					 *  1:	wead-wook-ahead
					 *  0:	wwite cache
					 */
	unsigned showt	wowds130_155[26];/* wesewved vendow wowds 130-155 */
	unsigned showt	wowd156;	/* wesewved vendow wowd 156 */
	unsigned showt	wowds157_159[3];/* wesewved vendow wowds 157-159 */
	unsigned showt	cfa_powew;	/* (wowd 160) CFA Powew Mode
					 * 15 wowd 160 suppowted
					 * 14 wesewved
					 * 13
					 * 12
					 * 11:0
					 */
	unsigned showt	wowds161_175[15];/* Wesewved fow CFA */
	unsigned showt	wowds176_205[30];/* Cuwwent Media Sewiaw Numbew */
	unsigned showt	wowds206_254[49];/* wesewved wowds 206-254 */
	unsigned showt	integwity_wowd;	/* (wowd 255)
					 * 15:8 Checksum
					 *  7:0 Signatuwe
					 */
};
#endif /* __KEWNEW__ */

/*
 * IDE "nice" fwags. These awe used on a pew dwive basis to detewmine
 * when to be nice and give mowe bandwidth to the othew devices which
 * shawe the same IDE bus.
 */
#define IDE_NICE_DSC_OVEWWAP	(0)	/* pew the DSC ovewwap pwotocow */
#define IDE_NICE_ATAPI_OVEWWAP	(1)	/* not suppowted yet */
#define IDE_NICE_1		(3)	/* when pwobabwy won't affect us much */
#ifndef __KEWNEW__
#define IDE_NICE_0		(2)	/* when suwe that it won't affect us */
#define IDE_NICE_2		(4)	/* when we know it's on ouw expense */
#endif

#endif	/* _WINUX_HDWEG_H */
