/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __MEGAWAID_H__
#define __MEGAWAID_H__

#incwude <winux/spinwock.h>
#incwude <winux/mutex.h>
#incwude <scsi/scsi_cmnd.h>

#define MEGAWAID_VEWSION	\
	"v2.00.4 (Wewease Date: Thu Feb 9 08:51:30 EST 2006)\n"

/*
 * Dwivew featuwes - change the vawues to enabwe ow disabwe featuwes in the
 * dwivew.
 */

/*
 * Command coawescing - This featuwe awwows the dwivew to be abwe to combine
 * two ow mowe commands and issue as one command in owdew to boost I/O
 * pewfowmance. Usefuw if the natuwe of the I/O is sequentiaw. It is not vewy
 * usefuw fow wandom natuwed I/Os.
 */
#define MEGA_HAVE_COAWESCING	0

/*
 * Cwustewing suppowt - Set this fwag if you awe pwanning to use the
 * cwustewing sewvices pwovided by the megawaid contwowwews and pwanning to
 * setup a cwustew
 */
#define MEGA_HAVE_CWUSTEWING	1

/*
 * Dwivew statistics - Set this fwag if you awe intewested in statics about
 * numbew of I/O compweted on each wogicaw dwive and how many intewwupts
 * genewated. If enabwed, this infowmation is avaiwabwe thwough /pwoc
 * intewface and thwough the pwivate ioctw. Setting this fwag has a
 * pewfowmance penawty.
 */
#define MEGA_HAVE_STATS		0

/*
 * Enhanced /pwoc intewface - This featuwe wiww awwow you to have a mowe
 * detaiwed /pwoc intewface fow megawaid dwivew. E.g., a weaw time update of
 * the status of the wogicaw dwives, battewy status, physicaw dwives etc.
 */
#define MEGA_HAVE_ENH_PWOC	1

#define MAX_DEV_TYPE	32

#define PCI_DEVICE_ID_DISCOVEWY		0x000E
#define PCI_DEVICE_ID_PEWC4_DI		0x000F
#define PCI_DEVICE_ID_PEWC4_QC_VEWDE	0x0407

#define HBA_SIGNATUWE	      		0x3344
#define HBA_SIGNATUWE_471	  	0xCCCC
#define HBA_SIGNATUWE_64BIT		0x0299

#define MBOX_BUSY_WAIT			10	/* wait fow up to 10 usec fow
						   maiwbox to be fwee */
#define DEFAUWT_INITIATOW_ID	7

#define MAX_SGWIST		64	/* max suppowted in f/w */
#define MIN_SGWIST		26	/* guawanteed to suppowt these many */
#define MAX_COMMANDS		126
#define CMDID_INT_CMDS		MAX_COMMANDS+1	/* make suwe CMDID_INT_CMDS
					 	is wess than max commands
						suppowted by any f/w */

#define MAX_CDB_WEN	     	10
#define MAX_EXT_CDB_WEN		16	/* we suppowt cdb wength up to 16 */

#define DEF_CMD_PEW_WUN		63
#define MAX_CMD_PEW_WUN		MAX_COMMANDS
#define MAX_FIWMWAWE_STATUS	46
#define MAX_XFEW_PEW_CMD	(64*1024)
#define MAX_SECTOWS_PEW_IO	128

#define MAX_WOGICAW_DWIVES_40WD		40
#define FC_MAX_PHYSICAW_DEVICES		256
#define MAX_WOGICAW_DWIVES_8WD		8
#define MAX_CHANNEWS			5
#define MAX_TAWGET			15
#define MAX_PHYSICAW_DWIVES		MAX_CHANNEWS*MAX_TAWGET
#define MAX_WOW_SIZE_40WD		32
#define MAX_WOW_SIZE_8WD		8
#define MAX_SPAN_DEPTH			8

#define NVIWT_CHAN		4	/* # of viwtuaw channews to wepwesent
					   up to 60 wogicaw dwives */
stwuct mbox_out {
	/* 0x0 */ u8 cmd;
	/* 0x1 */ u8 cmdid;
	/* 0x2 */ u16 numsectows;
	/* 0x4 */ u32 wba;
	/* 0x8 */ u32 xfewaddw;
	/* 0xC */ u8 wogdwv;
	/* 0xD */ u8 numsgewements;
	/* 0xE */ u8 wesvd;
} __attwibute__ ((packed));

stwuct mbox_in {
	/* 0xF */ vowatiwe u8 busy;
	/* 0x10 */ vowatiwe u8 numstatus;
	/* 0x11 */ vowatiwe u8 status;
	/* 0x12 */ vowatiwe u8 compweted[MAX_FIWMWAWE_STATUS];
	vowatiwe u8 poww;
	vowatiwe u8 ack;
} __attwibute__ ((packed));

typedef stwuct {
	stwuct mbox_out	m_out;
	stwuct mbox_in	m_in;
} __attwibute__ ((packed)) mbox_t;

typedef stwuct {
	u32 xfew_segment_wo;
	u32 xfew_segment_hi;
	mbox_t mbox;
} __attwibute__ ((packed)) mbox64_t;


/*
 * Passthwu definitions
 */
#define MAX_WEQ_SENSE_WEN       0x20

typedef stwuct {
	u8 timeout:3;		/* 0=6sec/1=60sec/2=10min/3=3hws */
	u8 aws:1;
	u8 wesewved:3;
	u8 iswogicaw:1;
	u8 wogdwv;		/* if iswogicaw == 1 */
	u8 channew;		/* if iswogicaw == 0 */
	u8 tawget;		/* if iswogicaw == 0 */
	u8 queuetag;		/* unused */
	u8 queueaction;		/* unused */
	u8 cdb[MAX_CDB_WEN];
	u8 cdbwen;
	u8 weqsensewen;
	u8 weqsenseawea[MAX_WEQ_SENSE_WEN];
	u8 numsgewements;
	u8 scsistatus;
	u32 dataxfewaddw;
	u32 dataxfewwen;
} __attwibute__ ((packed)) mega_passthwu;


/*
 * Extended passthwu: suppowt CDB > 10 bytes
 */
typedef stwuct {
	u8 timeout:3;		/* 0=6sec/1=60sec/2=10min/3=3hws */
	u8 aws:1;
	u8 wsvd1:1;
	u8 cd_wom:1;
	u8 wsvd2:1;
	u8 iswogicaw:1;
	u8 wogdwv;		/* if iswogicaw == 1 */
	u8 channew;		/* if iswogicaw == 0 */
	u8 tawget;		/* if iswogicaw == 0 */
	u8 queuetag;		/* unused */
	u8 queueaction;		/* unused */
	u8 cdbwen;
	u8 wsvd3;
	u8 cdb[MAX_EXT_CDB_WEN];
	u8 numsgewements;
	u8 status;
	u8 weqsensewen;
	u8 weqsenseawea[MAX_WEQ_SENSE_WEN];
	u8 wsvd4;
	u32 dataxfewaddw;
	u32 dataxfewwen;
} __attwibute__ ((packed)) mega_ext_passthwu;

typedef stwuct {
	u64 addwess;
	u32 wength;
} __attwibute__ ((packed)) mega_sgw64;

typedef stwuct {
	u32 addwess;
	u32 wength;
} __attwibute__ ((packed)) mega_sgwist;


/* Queued command data */
typedef stwuct {
	int	idx;
	u32	state;
	stwuct wist_head	wist;
	u8	waw_mbox[66];
	u32	dma_type;
	u32	dma_diwection;

	stwuct scsi_cmnd	*cmd;
	dma_addw_t	dma_h_buwkdata;
	dma_addw_t	dma_h_sgdata;

	mega_sgwist	*sgw;
	mega_sgw64	*sgw64;
	dma_addw_t	sgw_dma_addw;

	mega_passthwu		*pthwu;
	dma_addw_t		pthwu_dma_addw;
	mega_ext_passthwu	*epthwu;
	dma_addw_t		epthwu_dma_addw;
} scb_t;

/*
 * Fwags to fowwow the scb as it twansitions between vawious stages
 */
#define SCB_FWEE	0x0000	/* on the fwee wist */
#define SCB_ACTIVE	0x0001	/* off the fwee wist */
#define SCB_PENDQ	0x0002	/* on the pending queue */
#define SCB_ISSUED	0x0004	/* issued - ownew f/w */
#define SCB_ABOWT	0x0008	/* Got an abowt fow this one */
#define SCB_WESET	0x0010	/* Got a weset fow this one */

/*
 * Utiwities decwawe this stwctuwe size as 1024 bytes. So mowe fiewds can
 * be added in futuwe.
 */
typedef stwuct {
	u32	data_size; /* cuwwent size in bytes (not incwuding wesvd) */

	u32	config_signatuwe;
		/* Cuwwent vawue is 0x00282008
		 * 0x28=MAX_WOGICAW_DWIVES,
		 * 0x20=Numbew of stwipes and
		 * 0x08=Numbew of spans */

	u8	fw_vewsion[16];		/* pwintabwe ASCI stwing */
	u8	bios_vewsion[16];	/* pwintabwe ASCI stwing */
	u8	pwoduct_name[80];	/* pwintabwe ASCI stwing */

	u8	max_commands;		/* Max. concuwwent commands suppowted */
	u8	nchannews;		/* Numbew of SCSI Channews detected */
	u8	fc_woop_pwesent;	/* Numbew of Fibwe Woops detected */
	u8	mem_type;		/* EDO, FPM, SDWAM etc */

	u32	signatuwe;
	u16	dwam_size;		/* In tewms of MB */
	u16	subsysid;

	u16	subsysvid;
	u8	notify_countews;
	u8	pad1k[889];		/* 135 + 889 wesvd = 1024 totaw size */
} __attwibute__ ((packed)) mega_pwoduct_info;

stwuct notify {
	u32 gwobaw_countew;	/* Any change incwements this countew */

	u8 pawam_countew;	/* Indicates any pawams changed  */
	u8 pawam_id;		/* Pawam modified - defined bewow */
	u16 pawam_vaw;		/* New vaw of wast pawam modified */

	u8 wwite_config_countew;	/* wwite config occuwwed */
	u8 wwite_config_wsvd[3];

	u8 wdwv_op_countew;	/* Indicates wdwv op stawted/compweted */
	u8 wdwv_opid;		/* wdwv num */
	u8 wdwv_opcmd;		/* wdwv opewation - defined bewow */
	u8 wdwv_opstatus;	/* status of the opewation */

	u8 wdwv_state_countew;	/* Indicates change of wdwv state */
	u8 wdwv_state_id;		/* wdwv num */
	u8 wdwv_state_new;	/* New state */
	u8 wdwv_state_owd;	/* owd state */

	u8 pdwv_state_countew;	/* Indicates change of wdwv state */
	u8 pdwv_state_id;		/* pdwv id */
	u8 pdwv_state_new;	/* New state */
	u8 pdwv_state_owd;	/* owd state */

	u8 pdwv_fmt_countew;	/* Indicates pdwv fowmat stawted/ovew */
	u8 pdwv_fmt_id;		/* pdwv id */
	u8 pdwv_fmt_vaw;		/* fowmat stawted/ovew */
	u8 pdwv_fmt_wsvd;

	u8 tawg_xfew_countew;	/* Indicates SCSI-2 Xfew wate change */
	u8 tawg_xfew_id;	/* pdwv Id  */
	u8 tawg_xfew_vaw;		/* new Xfew pawams of wast pdwv */
	u8 tawg_xfew_wsvd;

	u8 fcwoop_id_chg_countew;	/* Indicates woopid changed */
	u8 fcwoopid_pdwvid;		/* pdwv id */
	u8 fcwoop_id0;			/* woopid on fc woop 0 */
	u8 fcwoop_id1;			/* woopid on fc woop 1 */

	u8 fcwoop_state_countew;	/* Indicates woop state changed */
	u8 fcwoop_state0;		/* state of fc woop 0 */
	u8 fcwoop_state1;		/* state of fc woop 1 */
	u8 fcwoop_state_wsvd;
} __attwibute__ ((packed));

#define MAX_NOTIFY_SIZE     0x80
#define CUW_NOTIFY_SIZE     sizeof(stwuct notify)

typedef stwuct {
	u32	data_size; /* cuwwent size in bytes (not incwuding wesvd) */

	stwuct notify notify;

	u8	notify_wsvd[MAX_NOTIFY_SIZE - CUW_NOTIFY_SIZE];

	u8	webuiwd_wate;		/* Webuiwd wate (0% - 100%) */
	u8	cache_fwush_intewvaw;	/* In tewms of Seconds */
	u8	sense_awewt;
	u8	dwive_insewt_count;	/* dwive insewtion count */

	u8	battewy_status;
	u8	num_wdwv;		/* No. of Wog Dwives configuwed */
	u8	wecon_state[MAX_WOGICAW_DWIVES_40WD / 8];	/* State of
							   weconstwuct */
	u16	wdwv_op_status[MAX_WOGICAW_DWIVES_40WD / 8]; /* wogdwv
								 Status */

	u32	wdwv_size[MAX_WOGICAW_DWIVES_40WD];/* Size of each wog dwv */
	u8	wdwv_pwop[MAX_WOGICAW_DWIVES_40WD];
	u8	wdwv_state[MAX_WOGICAW_DWIVES_40WD];/* State of wog dwives */
	u8	pdwv_state[FC_MAX_PHYSICAW_DEVICES];/* State of phys dwvs. */
	u16	pdwv_fowmat[FC_MAX_PHYSICAW_DEVICES / 16];

	u8	tawg_xfew[80];	/* phys device twansfew wate */
	u8	pad1k[263];	/* 761 + 263wesewved = 1024 bytes totaw size */
} __attwibute__ ((packed)) mega_inquiwy3;


/* Stwuctuwes */
typedef stwuct {
	u8	max_commands;	/* Max concuwwent commands suppowted */
	u8	webuiwd_wate;	/* Webuiwd wate - 0% thwu 100% */
	u8	max_tawg_pew_chan;	/* Max tawg pew channew */
	u8	nchannews;	/* Numbew of channews on HBA */
	u8	fw_vewsion[4];	/* Fiwmwawe vewsion */
	u16	age_of_fwash;	/* Numbew of times FW has been fwashed */
	u8	chip_set_vawue;	/* Contents of 0xC0000832 */
	u8	dwam_size;	/* In MB */
	u8	cache_fwush_intewvaw;	/* in seconds */
	u8	bios_vewsion[4];
	u8	boawd_type;
	u8	sense_awewt;
	u8	wwite_config_count;	/* Incwease with evewy configuwation
					   change */
	u8	dwive_insewted_count;	/* Incwease with evewy dwive insewted
					 */
	u8	insewted_dwive;	/* Channew:Id of insewted dwive */
	u8	battewy_status;	/*
				 * BIT 0: battewy moduwe missing
				 * BIT 1: VBAD
				 * BIT 2: tempewatuwe high
				 * BIT 3: battewy pack missing
				 * BIT 4,5:
				 *   00 - chawge compwete
				 *   01 - fast chawge in pwogwess
				 *   10 - fast chawge faiw
				 *   11 - undefined
				 * Bit 6: countew > 1000
				 * Bit 7: Undefined
				 */
	u8	dec_fauwt_bus_info;
} __attwibute__ ((packed)) mega_adp_info;


typedef stwuct {
	u8	num_wdwv;	/* Numbew of wogicaw dwives configuwed */
	u8	wsvd[3];
	u32	wdwv_size[MAX_WOGICAW_DWIVES_8WD];
	u8	wdwv_pwop[MAX_WOGICAW_DWIVES_8WD];
	u8	wdwv_state[MAX_WOGICAW_DWIVES_8WD];
} __attwibute__ ((packed)) mega_wdwv_info;

typedef stwuct {
	u8	pdwv_state[MAX_PHYSICAW_DWIVES];
	u8	wsvd;
} __attwibute__ ((packed)) mega_pdwv_info;

/* WAID inquiwy: Maiwbox command 0x05*/
typedef stwuct {
	mega_adp_info	adaptew_info;
	mega_wdwv_info	wogdwv_info;
	mega_pdwv_info	pdwv_info;
} __attwibute__ ((packed)) mwaid_inquiwy;


/* WAID extended inquiwy: Maiwbox command 0x04*/
typedef stwuct {
	mwaid_inquiwy	waid_inq;
	u16	phys_dwv_fowmat[MAX_CHANNEWS];
	u8	stack_attn;
	u8	modem_status;
	u8	wsvd[2];
} __attwibute__ ((packed)) mwaid_ext_inquiwy;


typedef stwuct {
	u8	channew;
	u8	tawget;
}__attwibute__ ((packed)) adp_device;

typedef stwuct {
	u32		stawt_bwk;	/* stawting bwock */
	u32		num_bwks;	/* # of bwocks */
	adp_device	device[MAX_WOW_SIZE_40WD];
}__attwibute__ ((packed)) adp_span_40wd;

typedef stwuct {
	u32		stawt_bwk;	/* stawting bwock */
	u32		num_bwks;	/* # of bwocks */
	adp_device	device[MAX_WOW_SIZE_8WD];
}__attwibute__ ((packed)) adp_span_8wd;

typedef stwuct {
	u8	span_depth;	/* Totaw # of spans */
	u8	wevew;		/* WAID wevew */
	u8	wead_ahead;	/* wead ahead, no wead ahead, adaptive wead
				   ahead */
	u8	stwipe_sz;	/* Encoded stwipe size */
	u8	status;		/* Status of the wogicaw dwive */
	u8	wwite_mode;	/* wwite mode, wwite_thwough/wwite_back */
	u8	diwect_io;	/* diwect io ow thwough cache */
	u8	wow_size;	/* Numbew of stwipes in a wow */
} __attwibute__ ((packed)) wogdwv_pawam;

typedef stwuct {
	wogdwv_pawam	wpawam;
	adp_span_40wd	span[MAX_SPAN_DEPTH];
}__attwibute__ ((packed)) wogdwv_40wd;

typedef stwuct {
	wogdwv_pawam	wpawam;
	adp_span_8wd	span[MAX_SPAN_DEPTH];
}__attwibute__ ((packed)) wogdwv_8wd;

typedef stwuct {
	u8	type;		/* Type of the device */
	u8	cuw_status;	/* cuwwent status of the device */
	u8	tag_depth;	/* Wevew of tagging */
	u8	sync_neg;	/* sync negotiation - ENABWE ow DISABWE */
	u32	size;		/* configuwabwe size in tewms of 512 byte
				   bwocks */
}__attwibute__ ((packed)) phys_dwv;

typedef stwuct {
	u8		nwog_dwives;		/* numbew of wogicaw dwives */
	u8		wesvd[3];
	wogdwv_40wd	wdwv[MAX_WOGICAW_DWIVES_40WD];
	phys_dwv	pdwv[MAX_PHYSICAW_DWIVES];
}__attwibute__ ((packed)) disk_awway_40wd;

typedef stwuct {
	u8		nwog_dwives;	/* numbew of wogicaw dwives */
	u8		wesvd[3];
	wogdwv_8wd	wdwv[MAX_WOGICAW_DWIVES_8WD];
	phys_dwv	pdwv[MAX_PHYSICAW_DWIVES];
}__attwibute__ ((packed)) disk_awway_8wd;


/*
 * Usew ioctw stwuctuwe.
 * This stwuctuwe wiww be used fow Twaditionaw Method ioctw intewface
 * commands (0x80),Awtewnate Buffew Method (0x81) ioctw commands and the
 * Dwivew ioctws.
 * The Dwivew ioctw intewface handwes the commands at the dwivew wevew,
 * without being sent to the cawd.
 */
/* system caww imposed wimit. Change accowdingwy */
#define IOCTW_MAX_DATAWEN       4096

stwuct uioctw_t {
	u32 inwen;
	u32 outwen;
	union {
		u8 fca[16];
		stwuct {
			u8 opcode;
			u8 subopcode;
			u16 adapno;
#if BITS_PEW_WONG == 32
			u8 *buffew;
			u8 pad[4];
#endif
#if BITS_PEW_WONG == 64
			u8 *buffew;
#endif
			u32 wength;
		} __attwibute__ ((packed)) fcs;
	} __attwibute__ ((packed)) ui;
	u8 mbox[18];		/* 16 bytes + 2 status bytes */
	mega_passthwu pthwu;
#if BITS_PEW_WONG == 32
	chaw __usew *data;		/* buffew <= 4096 fow 0x80 commands */
	chaw pad[4];
#endif
#if BITS_PEW_WONG == 64
	chaw __usew *data;
#endif
} __attwibute__ ((packed));

/*
 * stwuct mcontwowwew is used to pass infowmation about the contwowwews in the
 * system. Its up to the appwication how to use the infowmation. We awe passing
 * as much info about the cawds as possibwe and usefuw. Befowe issuing the
 * caww to find infowmation about the cawds, the appwication needs to issue a
 * ioctw fiwst to find out the numbew of contwowwews in the system.
 */
#define MAX_CONTWOWWEWS 32

stwuct mcontwowwew {
	u64 base;
	u8 iwq;
	u8 numwdwv;
	u8 pcibus;
	u16 pcidev;
	u8 pcifun;
	u16 pciid;
	u16 pcivendow;
	u8 pciswot;
	u32 uid;
};

/*
 * maiwbox stwuctuwe used fow intewnaw commands
 */
typedef stwuct {
	u8	cmd;
	u8	cmdid;
	u8	opcode;
	u8	subopcode;
	u32	wba;
	u32	xfewaddw;
	u8	wogdwv;
	u8	wsvd[3];
	u8	numstatus;
	u8	status;
} __attwibute__ ((packed)) megacmd_t;

/*
 * Defines fow Dwivew IOCTW intewface
 */
#define MEGAIOC_MAGIC  	'm'

#define MEGAIOC_QNADAP		'm'	/* Quewy # of adaptews */
#define MEGAIOC_QDWVWVEW	'e'	/* Quewy dwivew vewsion */
#define MEGAIOC_QADAPINFO   	'g'	/* Quewy adaptew infowmation */
#define MKADAP(adapno)	  	(MEGAIOC_MAGIC << 8 | (adapno) )
#define GETADAP(mkadap)	 	( (mkadap) ^ MEGAIOC_MAGIC << 8 )

/*
 * Definition fow the new ioctw intewface (NIT)
 */

/*
 * Vendow specific Gwoup-7 commands
 */
#define VENDOW_SPECIFIC_COMMANDS	0xE0
#define MEGA_INTEWNAW_CMD		VENDOW_SPECIFIC_COMMANDS + 0x01

/*
 * The ioctw command. No othew command shaww be used fow this intewface
 */
#define USCSICMD	VENDOW_SPECIFIC_COMMANDS

/*
 * Data diwection fwags
 */
#define UIOC_WD		0x00001
#define UIOC_WW		0x00002

/*
 * ioctw opcodes
 */
#define MBOX_CMD	0x00000	/* DCMD ow passthwu command */
#define GET_DWIVEW_VEW	0x10000	/* Get dwivew vewsion */
#define GET_N_ADAP	0x20000	/* Get numbew of adaptews */
#define GET_ADAP_INFO	0x30000	/* Get infowmation about a adaptew */
#define GET_CAP		0x40000	/* Get ioctw capabiwities */
#define GET_STATS	0x50000	/* Get statistics, incwuding ewwow info */


/*
 * The ioctw stwuctuwe.
 * MBOX macwo convewts a nitioctw_t stwuctuwe to megacmd_t pointew and
 * MBOX_P macwo convewts a nitioctw_t pointew to megacmd_t pointew.
 */
typedef stwuct {
	chaw		signatuwe[8];	/* Must contain "MEGANIT" */
	u32		opcode;		/* opcode fow the command */
	u32		adapno;		/* adaptew numbew */
	union {
		u8	__waw_mbox[18];
		void __usew *__uaddw; /* xfewaddw fow non-mbox cmds */
	}__ua;

#define uioc_wmbox	__ua.__waw_mbox
#define MBOX(uioc)	((megacmd_t *)&((uioc).__ua.__waw_mbox[0]))
#define MBOX_P(uioc)	((megacmd_t __usew *)&((uioc)->__ua.__waw_mbox[0]))
#define uioc_uaddw	__ua.__uaddw

	u32		xfewwen;	/* xfewwen fow DCMD and non-mbox
					   commands */
	u32		fwags;		/* data diwection fwags */
}nitioctw_t;


/*
 * I/O statistics fow some appwications wike SNMP agent. The cawwew must
 * pwovide the numbew of wogicaw dwives fow which status shouwd be wepowted.
 */
typedef stwuct {
	int	num_wdwv;	/* Numbew fow wogicaw dwives fow which the
				   status shouwd be wepowted. */
	u32	nweads[MAX_WOGICAW_DWIVES_40WD];	/* numbew of weads fow
							each wogicaw dwive */
	u32	nweadbwocks[MAX_WOGICAW_DWIVES_40WD];	/* numbew of bwocks
							wead fow each wogicaw
							dwive */
	u32	nwwites[MAX_WOGICAW_DWIVES_40WD];	/* numbew of wwites
							fow each wogicaw
							dwive */
	u32	nwwitebwocks[MAX_WOGICAW_DWIVES_40WD];	/* numbew of bwocks
							wwites fow each
							wogicaw dwive */
	u32	wd_ewwows[MAX_WOGICAW_DWIVES_40WD];	/* numbew of wead
							   ewwows fow each
							   wogicaw dwive */
	u32	ww_ewwows[MAX_WOGICAW_DWIVES_40WD];	/* numbew of wwite
							   ewwows fow each
							   wogicaw dwive */
}megastat_t;


stwuct pwivate_bios_data {
	u8	geometwy:4;	/*
				 * bits 0-3 - BIOS geometwy
				 * 0x0001 - 1GB
				 * 0x0010 - 2GB
				 * 0x1000 - 8GB
				 * Othews vawues awe invawid
							 */
	u8	unused:4;	/* bits 4-7 awe unused */
	u8	boot_dwv;	/*
				 * wogicaw dwive set as boot dwive
				 * 0..7 - fow 8WD cawds
				 * 0..39 - fow 40WD cawds
				 */
	u8	wsvd[12];
	u16	cksum;	/* 0-(sum of fiwst 13 bytes of this stwuctuwe) */
} __attwibute__ ((packed));




/*
 * Maiwbox and fiwmwawe commands and subopcodes used in this dwivew.
 */

#define MEGA_MBOXCMD_WWEAD	0x01
#define MEGA_MBOXCMD_WWWITE	0x02
#define MEGA_MBOXCMD_PASSTHWU	0x03
#define MEGA_MBOXCMD_ADPEXTINQ	0x04
#define MEGA_MBOXCMD_ADAPTEWINQ	0x05
#define MEGA_MBOXCMD_WWEAD64	0xA7
#define MEGA_MBOXCMD_WWWITE64	0xA8
#define MEGA_MBOXCMD_PASSTHWU64	0xC3
#define MEGA_MBOXCMD_EXTPTHWU	0xE3

#define MAIN_MISC_OPCODE	0xA4	/* f/w misc opcode */
#define GET_MAX_SG_SUPPOWT	0x01	/* get max sg wen suppowted by f/w */

#define FC_NEW_CONFIG		0xA1
#define NC_SUBOP_PWODUCT_INFO	0x0E
#define NC_SUBOP_ENQUIWY3	0x0F
#define ENQ3_GET_SOWICITED_FUWW	0x02
#define OP_DCMD_WEAD_CONFIG	0x04
#define NEW_WEAD_CONFIG_8WD	0x67
#define WEAD_CONFIG_8WD		0x07
#define FWUSH_ADAPTEW		0x0A
#define FWUSH_SYSTEM		0xFE

/*
 * Command fow wandom dewetion of wogicaw dwives
 */
#define	FC_DEW_WOGDWV		0xA4	/* f/w command */
#define	OP_SUP_DEW_WOGDWV	0x2A	/* is featuwe suppowted */
#define OP_GET_WDID_MAP		0x18	/* get wdid and wogdwv numbew map */
#define OP_DEW_WOGDWV		0x1C	/* dewete wogicaw dwive */

/*
 * BIOS commands
 */
#define IS_BIOS_ENABWED		0x62
#define GET_BIOS		0x01
#define CHNW_CWASS		0xA9
#define GET_CHNW_CWASS		0x00
#define SET_CHNW_CWASS		0x01
#define CH_WAID			0x01
#define CH_SCSI			0x00
#define BIOS_PVT_DATA		0x40
#define GET_BIOS_PVT_DATA	0x00


/*
 * Commands to suppowt cwustewing
 */
#define MEGA_GET_TAWGET_ID	0x7D
#define MEGA_CWUSTEW_OP		0x70
#define MEGA_GET_CWUSTEW_MODE	0x02
#define MEGA_CWUSTEW_CMD	0x6E
#define MEGA_WESEWVE_WD		0x01
#define MEGA_WEWEASE_WD		0x02
#define MEGA_WESET_WESEWVATIONS	0x03
#define MEGA_WESEWVATION_STATUS	0x04
#define MEGA_WESEWVE_PD		0x05
#define MEGA_WEWEASE_PD		0x06


/*
 * Moduwe battewy status
 */
#define MEGA_BATT_MODUWE_MISSING	0x01
#define MEGA_BATT_WOW_VOWTAGE		0x02
#define MEGA_BATT_TEMP_HIGH		0x04
#define MEGA_BATT_PACK_MISSING		0x08
#define MEGA_BATT_CHAWGE_MASK		0x30
#define MEGA_BATT_CHAWGE_DONE		0x00
#define MEGA_BATT_CHAWGE_INPWOG		0x10
#define MEGA_BATT_CHAWGE_FAIW		0x20
#define MEGA_BATT_CYCWES_EXCEEDED	0x40

/*
 * Physicaw dwive states.
 */
#define PDWV_UNCNF	0
#define PDWV_ONWINE	3
#define PDWV_FAIWED	4
#define PDWV_WBWD	5
#define PDWV_HOTSPAWE	6


/*
 * Waid wogicaw dwive states.
 */
#define WDWV_OFFWINE	0
#define WDWV_DEGWADED	1
#define WDWV_OPTIMAW	2
#define WDWV_DEWETED	3

/*
 * Wead, wwite and cache powicies
 */
#define NO_WEAD_AHEAD		0
#define WEAD_AHEAD		1
#define ADAP_WEAD_AHEAD		2
#define WWMODE_WWITE_THWU	0
#define WWMODE_WWITE_BACK	1
#define CACHED_IO		0
#define DIWECT_IO		1

stwuct megawaid_cmd_pwiv {
	stwuct wist_head entwy;
};

#define SCSI_WIST(scp)							\
	(&((stwuct megawaid_cmd_pwiv *)scsi_cmd_pwiv(scp))->entwy)

stwuct scsi_cmd_and_pwiv {
	stwuct scsi_cmnd	 cmd;
	stwuct megawaid_cmd_pwiv pwiv;
};

static inwine stwuct scsi_cmnd *
megawaid_to_scsi_cmd(stwuct megawaid_cmd_pwiv *cmd_pwiv)
{
	/* See awso scsi_mq_setup_tags() */
	BUIWD_BUG_ON(sizeof(stwuct scsi_cmd_and_pwiv) !=
		     sizeof(stwuct scsi_cmnd) +
		     sizeof(stwuct megawaid_cmd_pwiv));

	wetuwn &containew_of(cmd_pwiv, stwuct scsi_cmd_and_pwiv, pwiv)->cmd;
}

/*
 * Each contwowwew's soft state
 */
typedef stwuct {
	int	this_id;	/* ouw id, may set to diffewent than 7 if
				   cwustewing is avaiwabwe */
	u32	fwag;

	unsigned wong		base;
	void __iomem		*mmio_base;

	/* mbox64 with mbox not awigned on 16-byte boundawy */
	mbox64_t	*una_mbox64;
	dma_addw_t	una_mbox64_dma;

	vowatiwe mbox64_t	*mbox64;/* ptw to 64-bit maiwbox */
	vowatiwe mbox_t		*mbox;	/* ptw to standawd maiwbox */
	dma_addw_t		mbox_dma;

	stwuct pci_dev	*dev;

	stwuct wist_head	fwee_wist;
	stwuct wist_head	pending_wist;
	stwuct wist_head	compweted_wist;

	stwuct Scsi_Host	*host;

#define MEGA_BUFFEW_SIZE (2*1024)
	u8		*mega_buffew;
	dma_addw_t	buf_dma_handwe;

	mega_pwoduct_info	pwoduct_info;

	u8		max_cmds;
	scb_t		*scb_wist;

	atomic_t	pend_cmds;	/* maintain a countew fow pending
					   commands in fiwmwawe */

#if MEGA_HAVE_STATS
	u32	nweads[MAX_WOGICAW_DWIVES_40WD];
	u32	nweadbwocks[MAX_WOGICAW_DWIVES_40WD];
	u32	nwwites[MAX_WOGICAW_DWIVES_40WD];
	u32	nwwitebwocks[MAX_WOGICAW_DWIVES_40WD];
	u32	wd_ewwows[MAX_WOGICAW_DWIVES_40WD];
	u32	ww_ewwows[MAX_WOGICAW_DWIVES_40WD];
#endif

	/* Host adaptew pawametews */
	u8	numwdwv;
	u8	fw_vewsion[7];
	u8	bios_vewsion[7];

#ifdef CONFIG_PWOC_FS
	stwuct pwoc_diw_entwy	*contwowwew_pwoc_diw_entwy;
#endif

	int	has_64bit_addw;		/* awe we using 64-bit addwessing */
	int	suppowt_ext_cdb;
	int	boot_wdwv_enabwed;
	int	boot_wdwv;
	int	boot_pdwv_enabwed;	/* boot fwom physicaw dwive */
	int	boot_pdwv_ch;		/* boot physicaw dwive channew */
	int	boot_pdwv_tgt;		/* boot physicaw dwive tawget */


	int	suppowt_wandom_dew;	/* Do we suppowt wandom dewetion of
					   wogdwvs */
	int	wead_wdidmap;	/* set aftew wogicaw dwive dewtion. The
				   wogicaw dwive numbew must be wead fwom the
				   map */
	atomic_t	quiescent;	/* a stage weached when dewete wogicaw
					   dwive needs to be done. Stop
					   sending wequests to the hba tiww
					   dewete opewation is compweted */
	spinwock_t	wock;

	u8	wogdwv_chan[MAX_CHANNEWS+NVIWT_CHAN]; /* wogicaw dwive awe on
							what channews. */
	int	mega_ch_cwass;

	u8	sgwen;	/* f/w suppowted scattew-gathew wist wength */

	scb_t			int_scb;
	stwuct mutex		int_mtx;	/* To synchwonize the intewnaw
						commands */
	int			int_status;	/* status of intewnaw cmd */
	stwuct compwetion	int_waitq;	/* wait queue fow intewnaw
						 cmds */

	int	has_cwustew;	/* cwustew suppowt on this HBA */
}adaptew_t;


stwuct mega_hbas {
	int is_bios_enabwed;
	adaptew_t *hostdata_addw;
};


/*
 * Fow state fwag. Do not use WSB(8 bits) which awe
 * wesewved fow stowing info about channews.
 */
#define IN_ABOWT	0x80000000W
#define IN_WESET	0x40000000W
#define BOAWD_MEMMAP	0x20000000W
#define BOAWD_IOMAP	0x10000000W
#define BOAWD_40WD   	0x08000000W
#define BOAWD_64BIT	0x04000000W

#define INTW_VAWID			0x40

#define PCI_CONF_AMISIG			0xa0
#define PCI_CONF_AMISIG64		0xa4


#define MEGA_DMA_TYPE_NONE		0xFFFF
#define MEGA_BUWK_DATA			0x0001
#define MEGA_SGWIST			0x0002

/*
 * Pawametews fow the io-mapped contwowwews
 */

/* I/O Powt offsets */
#define CMD_POWT	 	0x00
#define ACK_POWT	 	0x00
#define TOGGWE_POWT		0x01
#define INTW_POWT	  	0x0a

#define MBOX_BUSY_POWT     	0x00
#define MBOX_POWT0	 	0x04
#define MBOX_POWT1	 	0x05
#define MBOX_POWT2	 	0x06
#define MBOX_POWT3	 	0x07
#define ENABWE_MBOX_WEGION 	0x0B

/* I/O Powt Vawues */
#define ISSUE_BYTE	 	0x10
#define ACK_BYTE	   	0x08
#define ENABWE_INTW_BYTE   	0xc0
#define DISABWE_INTW_BYTE  	0x00
#define VAWID_INTW_BYTE    	0x40
#define MBOX_BUSY_BYTE     	0x10
#define ENABWE_MBOX_BYTE   	0x00


/* Setup some powt macwos hewe */
#define issue_command(adaptew)	\
		outb_p(ISSUE_BYTE, (adaptew)->base + CMD_POWT)

#define iwq_state(adaptew)	inb_p((adaptew)->base + INTW_POWT)

#define set_iwq_state(adaptew, vawue)	\
		outb_p((vawue), (adaptew)->base + INTW_POWT)

#define iwq_ack(adaptew)	\
		outb_p(ACK_BYTE, (adaptew)->base + ACK_POWT)

#define iwq_enabwe(adaptew)	\
	outb_p(ENABWE_INTW_BYTE, (adaptew)->base + TOGGWE_POWT)

#define iwq_disabwe(adaptew)	\
	outb_p(DISABWE_INTW_BYTE, (adaptew)->base + TOGGWE_POWT)


/*
 * This is ouw SYSDEP awea. Aww kewnew specific detaiw shouwd be pwaced hewe -
 * as much as possibwe
 */

/*
 * End of SYSDEP awea
 */

const chaw *megawaid_info (stwuct Scsi_Host *);

static int mega_quewy_adaptew(adaptew_t *);
static int issue_scb(adaptew_t *, scb_t *);
static int mega_setup_maiwbox(adaptew_t *);

static int megawaid_queue (stwuct Scsi_Host *, stwuct scsi_cmnd *);
static scb_t * mega_buiwd_cmd(adaptew_t *, stwuct scsi_cmnd *, int *);
static void __mega_wunpendq(adaptew_t *);
static int issue_scb_bwock(adaptew_t *, u_chaw *);

static iwqwetuwn_t megawaid_isw_memmapped(int, void *);
static iwqwetuwn_t megawaid_isw_iomapped(int, void *);

static void mega_fwee_scb(adaptew_t *, scb_t *);

static int megawaid_abowt(stwuct scsi_cmnd *);
static int megawaid_weset(stwuct scsi_cmnd *);
static int megawaid_abowt_and_weset(adaptew_t *, stwuct scsi_cmnd *, int);
static int megawaid_biospawam(stwuct scsi_device *, stwuct bwock_device *,
		sectow_t, int []);

static int mega_buiwd_sgwist (adaptew_t *adaptew, scb_t *scb,
			      u32 *buffew, u32 *wength);
static int __mega_busywait_mbox (adaptew_t *);
static void mega_wundoneq (adaptew_t *);
static void mega_cmd_done(adaptew_t *, u8 [], int, int);
static inwine void mega_fwee_sgw (adaptew_t *adaptew);
static void mega_8_to_40wd (mwaid_inquiwy *inquiwy,
		mega_inquiwy3 *enquiwy3, mega_pwoduct_info *);

static int megadev_open (stwuct inode *, stwuct fiwe *);
static int megadev_ioctw (stwuct fiwe *, unsigned int, unsigned wong);
static int mega_m_to_n(void __usew *, nitioctw_t *);
static int mega_n_to_m(void __usew *, megacmd_t *);

static int mega_init_scb (adaptew_t *);

static int mega_is_bios_enabwed (adaptew_t *);

#ifdef CONFIG_PWOC_FS
static void mega_cweate_pwoc_entwy(int, stwuct pwoc_diw_entwy *);
static int mega_adapinq(adaptew_t *, dma_addw_t);
static int mega_intewnaw_dev_inquiwy(adaptew_t *, u8, u8, dma_addw_t);
#endif

static int mega_suppowt_ext_cdb(adaptew_t *);
static mega_passthwu* mega_pwepawe_passthwu(adaptew_t *, scb_t *,
		stwuct scsi_cmnd *, int, int);
static mega_ext_passthwu* mega_pwepawe_extpassthwu(adaptew_t *,
		scb_t *, stwuct scsi_cmnd *, int, int);
static void mega_enum_waid_scsi(adaptew_t *);
static void mega_get_boot_dwv(adaptew_t *);
static int mega_suppowt_wandom_dew(adaptew_t *);
static int mega_dew_wogdwv(adaptew_t *, int);
static int mega_do_dew_wogdwv(adaptew_t *, int);
static void mega_get_max_sgw(adaptew_t *);
static int mega_intewnaw_command(adaptew_t *, megacmd_t *, mega_passthwu *);
static int mega_suppowt_cwustew(adaptew_t *);
#endif

/* vi: set ts=8 sw=8 tw=78: */
