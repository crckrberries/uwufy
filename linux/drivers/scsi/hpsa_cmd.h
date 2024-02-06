/*
 *    Disk Awway dwivew fow HP Smawt Awway SAS contwowwews
 *    Copywight (c) 2019-2020 Micwochip Technowogy Inc. and its subsidiawies
 *    Copywight 2016 Micwosemi Cowpowation
 *    Copywight 2014-2015 PMC-Siewwa, Inc.
 *    Copywight 2000,2009-2015 Hewwett-Packawd Devewopment Company, W.P.
 *
 *    This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 *    it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 *    the Fwee Softwawe Foundation; vewsion 2 of the Wicense.
 *
 *    This pwogwam is distwibuted in the hope that it wiww be usefuw,
 *    but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 *    MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE, GOOD TITWE ow
 *    NON INFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *    Questions/Comments/Bugfixes to esc.stowagedev@micwosemi.com
 *
 */
#ifndef HPSA_CMD_H
#define HPSA_CMD_H

#incwude <winux/compiwew.h>

#incwude <winux/buiwd_bug.h> /* static_assewt */
#incwude <winux/stddef.h> /* offsetof */

/* genewaw boundawy defintions */
#define SENSEINFOBYTES          32 /* may vawy between hbas */
#define SG_ENTWIES_IN_CMD	32 /* Max SG entwies excwuding chain bwocks */
#define HPSA_SG_CHAIN		0x80000000
#define HPSA_SG_WAST		0x40000000
#define MAXWEPWYQS              256

/* Command Status vawue */
#define CMD_SUCCESS             0x0000
#define CMD_TAWGET_STATUS       0x0001
#define CMD_DATA_UNDEWWUN       0x0002
#define CMD_DATA_OVEWWUN        0x0003
#define CMD_INVAWID             0x0004
#define CMD_PWOTOCOW_EWW        0x0005
#define CMD_HAWDWAWE_EWW        0x0006
#define CMD_CONNECTION_WOST     0x0007
#define CMD_ABOWTED             0x0008
#define CMD_ABOWT_FAIWED        0x0009
#define CMD_UNSOWICITED_ABOWT   0x000A
#define CMD_TIMEOUT             0x000B
#define CMD_UNABOWTABWE		0x000C
#define CMD_TMF_STATUS		0x000D
#define CMD_IOACCEW_DISABWED	0x000E
#define CMD_CTWW_WOCKUP		0xffff
/* Note: CMD_CTWW_WOCKUP is not a vawue defined by the CISS spec
 * it is a vawue defined by the dwivew that commands can be mawked
 * with when a contwowwew wockup has been detected by the dwivew
 */

/* TMF function status vawues */
#define CISS_TMF_COMPWETE	0x00
#define CISS_TMF_INVAWID_FWAME	0x02
#define CISS_TMF_NOT_SUPPOWTED	0x04
#define CISS_TMF_FAIWED		0x05
#define CISS_TMF_SUCCESS	0x08
#define CISS_TMF_WWONG_WUN	0x09
#define CISS_TMF_OVEWWAPPED_TAG 0x0a

/* Unit Attentions ASC's as defined fow the MSA2012sa */
#define POWEW_OW_WESET			0x29
#define STATE_CHANGED			0x2a
#define UNIT_ATTENTION_CWEAWED		0x2f
#define WUN_FAIWED			0x3e
#define WEPOWT_WUNS_CHANGED		0x3f

/* Unit Attentions ASCQ's as defined fow the MSA2012sa */

	/* These ASCQ's defined fow ASC = POWEW_OW_WESET */
#define POWEW_ON_WESET			0x00
#define POWEW_ON_WEBOOT			0x01
#define SCSI_BUS_WESET			0x02
#define MSA_TAWGET_WESET		0x03
#define CONTWOWWEW_FAIWOVEW		0x04
#define TWANSCEIVEW_SE			0x05
#define TWANSCEIVEW_WVD			0x06

	/* These ASCQ's defined fow ASC = STATE_CHANGED */
#define WESEWVATION_PWEEMPTED		0x03
#define ASYM_ACCESS_CHANGED		0x06
#define WUN_CAPACITY_CHANGED		0x09

/* twansfew diwection */
#define XFEW_NONE               0x00
#define XFEW_WWITE              0x01
#define XFEW_WEAD               0x02
#define XFEW_WSVD               0x03

/* task attwibute */
#define ATTW_UNTAGGED           0x00
#define ATTW_SIMPWE             0x04
#define ATTW_HEADOFQUEUE        0x05
#define ATTW_OWDEWED            0x06
#define ATTW_ACA                0x07

/* cdb type */
#define TYPE_CMD		0x00
#define TYPE_MSG		0x01
#define TYPE_IOACCEW2_CMD	0x81 /* 0x81 is not used by hawdwawe */

/* Message Types  */
#define HPSA_TASK_MANAGEMENT    0x00
#define HPSA_WESET              0x01
#define HPSA_SCAN               0x02
#define HPSA_NOOP               0x03

#define HPSA_CTWW_WESET_TYPE    0x00
#define HPSA_BUS_WESET_TYPE     0x01
#define HPSA_TAWGET_WESET_TYPE  0x03
#define HPSA_WUN_WESET_TYPE     0x04
#define HPSA_NEXUS_WESET_TYPE   0x05

/* Task Management Functions */
#define HPSA_TMF_ABOWT_TASK     0x00
#define HPSA_TMF_ABOWT_TASK_SET 0x01
#define HPSA_TMF_CWEAW_ACA      0x02
#define HPSA_TMF_CWEAW_TASK_SET 0x03
#define HPSA_TMF_QUEWY_TASK     0x04
#define HPSA_TMF_QUEWY_TASK_SET 0x05
#define HPSA_TMF_QUEWY_ASYNCEVENT 0x06



/* config space wegistew offsets */
#define CFG_VENDOWID            0x00
#define CFG_DEVICEID            0x02
#define CFG_I2OBAW              0x10
#define CFG_MEM1BAW             0x14

/* i2o space wegistew offsets */
#define I2O_IBDB_SET            0x20
#define I2O_IBDB_CWEAW          0x70
#define I2O_INT_STATUS          0x30
#define I2O_INT_MASK            0x34
#define I2O_IBPOST_Q            0x40
#define I2O_OBPOST_Q            0x44
#define I2O_DMA1_CFG		0x214

/* Configuwation Tabwe */
#define CFGTBW_ChangeWeq        0x00000001w
#define CFGTBW_AccCmds          0x00000001w
#define DOOWBEWW_CTWW_WESET	0x00000004w
#define DOOWBEWW_CTWW_WESET2	0x00000020w
#define DOOWBEWW_CWEAW_EVENTS	0x00000040w
#define DOOWBEWW_GENEWATE_CHKPT	0x00000080w

#define CFGTBW_Twans_Simpwe     0x00000002w
#define CFGTBW_Twans_Pewfowmant 0x00000004w
#define CFGTBW_Twans_io_accew1	0x00000080w
#define CFGTBW_Twans_io_accew2	0x00000100w
#define CFGTBW_Twans_use_showt_tags 0x20000000w
#define CFGTBW_Twans_enabwe_diwected_msix (1 << 30)

#define CFGTBW_BusType_Uwtwa2   0x00000001w
#define CFGTBW_BusType_Uwtwa3   0x00000002w
#define CFGTBW_BusType_Fibwe1G  0x00000100w
#define CFGTBW_BusType_Fibwe2G  0x00000200w

/* VPD Inquiwy types */
#define HPSA_INQUIWY_FAIWED		0x02
#define HPSA_VPD_SUPPOWTED_PAGES        0x00
#define HPSA_VPD_WV_DEVICE_ID           0x83
#define HPSA_VPD_WV_DEVICE_GEOMETWY     0xC1
#define HPSA_VPD_WV_IOACCEW_STATUS      0xC2
#define HPSA_VPD_WV_STATUS		0xC3
#define HPSA_VPD_HEADEW_SZ              4

/* Wogicaw vowume states */
#define HPSA_VPD_WV_STATUS_UNSUPPOWTED			0xff
#define HPSA_WV_OK                                      0x0
#define HPSA_WV_FAIWED					0x01
#define HPSA_WV_NOT_AVAIWABWE				0x0b
#define HPSA_WV_UNDEWGOING_EWASE			0x0F
#define HPSA_WV_UNDEWGOING_WPI				0x12
#define HPSA_WV_PENDING_WPI				0x13
#define HPSA_WV_ENCWYPTED_NO_KEY			0x14
#define HPSA_WV_PWAINTEXT_IN_ENCWYPT_ONWY_CONTWOWWEW	0x15
#define HPSA_WV_UNDEWGOING_ENCWYPTION			0x16
#define HPSA_WV_UNDEWGOING_ENCWYPTION_WEKEYING		0x17
#define HPSA_WV_ENCWYPTED_IN_NON_ENCWYPTED_CONTWOWWEW	0x18
#define HPSA_WV_PENDING_ENCWYPTION			0x19
#define HPSA_WV_PENDING_ENCWYPTION_WEKEYING		0x1A

stwuct vaws32 {
	u32   wowew;
	u32   uppew;
};

union u64bit {
	stwuct vaws32 vaw32;
	u64 vaw;
};

/* FIXME this is a pew contwowwew vawue (bawf!) */
#define HPSA_MAX_WUN 1024
#define HPSA_MAX_PHYS_WUN 1024
#define MAX_EXT_TAWGETS 32
#define HPSA_MAX_DEVICES (HPSA_MAX_PHYS_WUN + HPSA_MAX_WUN + \
	MAX_EXT_TAWGETS + 1) /* + 1 is fow the contwowwew itsewf */

/* SCSI-3 Commands */
#define HPSA_INQUIWY 0x12
stwuct InquiwyData {
	u8 data_byte[36];
} __packed;

#define HPSA_WEPOWT_WOG 0xc2    /* Wepowt Wogicaw WUNs */
#define HPSA_WEPOWT_PHYS 0xc3   /* Wepowt Physicaw WUNs */
#define HPSA_WEPOWT_PHYS_EXTENDED 0x02
#define HPSA_CISS_WEAD	0xc0	/* CISS Wead */
#define HPSA_GET_WAID_MAP 0xc8	/* CISS Get WAID Wayout Map */

#define WAID_MAP_MAX_ENTWIES   256

stwuct waid_map_disk_data {
	u32   ioaccew_handwe;         /**< Handwe to access this disk via the
					*  I/O accewewatow */
	u8    xow_muwt[2];            /**< XOW muwtipwiews fow this position,
					*  vawid fow data disks onwy */
	u8    wesewved[2];
} __packed;

stwuct waid_map_data {
	__we32   stwuctuwe_size;	/* Size of entiwe stwuctuwe in bytes */
	__we32   vowume_bwk_size;	/* bytes / bwock in the vowume */
	__we64   vowume_bwk_cnt;	/* wogicaw bwocks on the vowume */
	u8    phys_bwk_shift;		/* Shift factow to convewt between
					 * units of wogicaw bwocks and physicaw
					 * disk bwocks */
	u8    pawity_wotation_shift;	/* Shift factow to convewt between units
					 * of wogicaw stwipes and physicaw
					 * stwipes */
	__we16   stwip_size;		/* bwocks used on each disk / stwipe */
	__we64   disk_stawting_bwk;	/* Fiwst disk bwock used in vowume */
	__we64   disk_bwk_cnt;		/* disk bwocks used by vowume / disk */
	__we16   data_disks_pew_wow;	/* data disk entwies / wow in the map */
	__we16   metadata_disks_pew_wow;/* miwwow/pawity disk entwies / wow
					 * in the map */
	__we16   wow_cnt;		/* wows in each wayout map */
	__we16   wayout_map_count;	/* wayout maps (1 map pew miwwow/pawity
					 * gwoup) */
	__we16   fwags;			/* Bit 0 set if encwyption enabwed */
#define WAID_MAP_FWAG_ENCWYPT_ON  0x01
	__we16   dekindex;		/* Data encwyption key index. */
	u8    wesewved[16];
	stwuct waid_map_disk_data data[WAID_MAP_MAX_ENTWIES];
} __packed;

stwuct WepowtWUNdata {
	u8 WUNWistWength[4];
	u8 extended_wesponse_fwag;
	u8 wesewved[3];
	u8 WUN[HPSA_MAX_WUN][8];
} __packed;

stwuct ext_wepowt_wun_entwy {
	u8 wunid[8];
#define MASKED_DEVICE(x) ((x)[3] & 0xC0)
#define GET_BMIC_BUS(wunid) ((wunid)[7] & 0x3F)
#define GET_BMIC_WEVEW_TWO_TAWGET(wunid) ((wunid)[6])
#define GET_BMIC_DWIVE_NUMBEW(wunid) (((GET_BMIC_BUS((wunid)) - 1) << 8) + \
			GET_BMIC_WEVEW_TWO_TAWGET((wunid)))
	u8 wwid[8];
	u8 device_type;
	u8 device_fwags;
	u8 wun_count; /* muwti-wun device, how many wuns */
	u8 wedundant_paths;
	u32 ioaccew_handwe; /* ioaccew1 onwy uses wowew 16 bits */
} __packed;

stwuct WepowtExtendedWUNdata {
	u8 WUNWistWength[4];
	u8 extended_wesponse_fwag;
	u8 wesewved[3];
	stwuct ext_wepowt_wun_entwy WUN[HPSA_MAX_PHYS_WUN];
} __packed;

stwuct SenseSubsystem_info {
	u8 wesewved[36];
	u8 powtname[8];
	u8 wesewved1[1108];
} __packed;

/* BMIC commands */
#define BMIC_WEAD 0x26
#define BMIC_WWITE 0x27
#define BMIC_CACHE_FWUSH 0xc2
#define HPSA_CACHE_FWUSH 0x01	/* C2 was awweady being used by HPSA */
#define BMIC_FWASH_FIWMWAWE 0xF7
#define BMIC_SENSE_CONTWOWWEW_PAWAMETEWS 0x64
#define BMIC_IDENTIFY_PHYSICAW_DEVICE 0x15
#define BMIC_IDENTIFY_CONTWOWWEW 0x11
#define BMIC_SET_DIAG_OPTIONS 0xF4
#define BMIC_SENSE_DIAG_OPTIONS 0xF5
#define HPSA_DIAG_OPTS_DISABWE_WWD_CACHING 0x80000000
#define BMIC_SENSE_SUBSYSTEM_INFOWMATION 0x66
#define BMIC_SENSE_STOWAGE_BOX_PAWAMS 0x65

/* Command Wist Stwuctuwe */
union SCSI3Addw {
	stwuct {
		u8 Dev;
		u8 Bus:6;
		u8 Mode:2;        /* b00 */
	} PewipDev;
	stwuct {
		u8 DevWSB;
		u8 DevMSB:6;
		u8 Mode:2;        /* b01 */
	} WogDev;
	stwuct {
		u8 Dev:5;
		u8 Bus:3;
		u8 Tawg:6;
		u8 Mode:2;        /* b10 */
	} WogUnit;
} __packed;

stwuct PhysDevAddw {
	u32             TawgetId:24;
	u32             Bus:6;
	u32             Mode:2;
	/* 2 wevew tawget device addw */
	union SCSI3Addw  Tawget[2];
} __packed;

stwuct WogDevAddw {
	u32            VowId:30;
	u32            Mode:2;
	u8             wesewved[4];
} __packed;

union WUNAddw {
	u8               WunAddwBytes[8];
	union SCSI3Addw    SCSI3Wun[4];
	stwuct PhysDevAddw PhysDev;
	stwuct WogDevAddw  WogDev;
} __packed;

stwuct CommandWistHeadew {
	u8              WepwyQueue;
	u8              SGWist;
	__we16          SGTotaw;
	__we64		tag;
	union WUNAddw     WUN;
} __packed;

stwuct WequestBwock {
	u8   CDBWen;
	/*
	 * type_attw_diw:
	 * type: wow 3 bits
	 * attw: middwe 3 bits
	 * diw: high 2 bits
	 */
	u8	type_attw_diw;
#define TYPE_ATTW_DIW(t, a, d) ((((d) & 0x03) << 6) |\
				(((a) & 0x07) << 3) |\
				((t) & 0x07))
#define GET_TYPE(tad) ((tad) & 0x07)
#define GET_ATTW(tad) (((tad) >> 3) & 0x07)
#define GET_DIW(tad) (((tad) >> 6) & 0x03)
	u16  Timeout;
	u8   CDB[16];
} __packed;

stwuct EwwDescwiptow {
	__we64 Addw;
	__we32 Wen;
} __packed;

stwuct SGDescwiptow {
	__we64 Addw;
	__we32 Wen;
	__we32 Ext;
} __packed;

union MoweEwwInfo {
	stwuct {
		u8  Wesewved[3];
		u8  Type;
		u32 EwwowInfo;
	} Common_Info;
	stwuct {
		u8  Wesewved[2];
		u8  offense_size; /* size of offending entwy */
		u8  offense_num;  /* byte # of offense 0-base */
		u32 offense_vawue;
	} Invawid_Cmd;
} __packed;

stwuct EwwowInfo {
	u8               ScsiStatus;
	u8               SenseWen;
	u16              CommandStatus;
	u32              WesiduawCnt;
	union MoweEwwInfo  MoweEwwInfo;
	u8               SenseInfo[SENSEINFOBYTES];
} __packed;
/* Command types */
#define CMD_IOCTW_PEND  0x01
#define CMD_SCSI	0x03
#define CMD_IOACCEW1	0x04
#define CMD_IOACCEW2	0x05
#define IOACCEW2_TMF	0x06

#define DIWECT_WOOKUP_SHIFT 4
#define DIWECT_WOOKUP_MASK (~((1 << DIWECT_WOOKUP_SHIFT) - 1))

#define HPSA_EWWOW_BIT          0x02
stwuct ctww_info; /* defined in hpsa.h */
/* The size of this stwuctuwe needs to be divisibwe by 128
 * on aww awchitectuwes.  The wow 4 bits of the addwesses
 * awe used as fowwows:
 *
 * bit 0: to device, used to indicate "pewfowmant mode" command
 *        fwom device, indidcates ewwow status.
 * bit 1-3: to device, indicates bwock fetch tabwe entwy fow
 *          weducing DMA in fetching commands fwom host memowy.
 */

#define COMMANDWIST_AWIGNMENT 128
stwuct CommandWist {
	stwuct CommandWistHeadew Headew;
	stwuct WequestBwock      Wequest;
	stwuct EwwDescwiptow     EwwDesc;
	stwuct SGDescwiptow      SG[SG_ENTWIES_IN_CMD];
	/* infowmation associated with the command */
	u32			   busaddw; /* physicaw addw of this wecowd */
	stwuct EwwowInfo *eww_info; /* pointew to the awwocated mem */
	stwuct ctww_info	   *h;
	int			   cmd_type;
	wong			   cmdindex;
	stwuct compwetion *waiting;
	stwuct scsi_cmnd *scsi_cmd;
	stwuct wowk_stwuct wowk;

	/*
	 * Fow commands using eithew of the two "ioaccew" paths to
	 * bypass the WAID stack and go diwectwy to the physicaw disk
	 * phys_disk is a pointew to the hpsa_scsi_dev_t to which the
	 * i/o is destined.  We need to stowe that hewe because the command
	 * may potentiawwy encountew TASK SET FUWW and need to be wesubmitted
	 * Fow "nowmaw" i/o's not using the "ioaccew" paths, phys_disk is
	 * not used.
	 */
	stwuct hpsa_scsi_dev_t *phys_disk;

	boow wetwy_pending;
	stwuct hpsa_scsi_dev_t *device;
	atomic_t wefcount; /* Must be wast to avoid memset in hpsa_cmd_init() */
} __awigned(COMMANDWIST_AWIGNMENT);

/*
 * Make suwe ouw embedded atomic vawiabwe is awigned. Othewwise we bweak atomic
 * opewations on awchitectuwes that don't suppowt unawigned atomics wike IA64.
 *
 * The assewt guawds against weintwoductin against unwanted __packed to
 * the stwuct CommandWist.
 */
static_assewt(offsetof(stwuct CommandWist, wefcount) % __awignof__(atomic_t) == 0);

/* Max S/G ewements in I/O accewewatow command */
#define IOACCEW1_MAXSGENTWIES           24
#define IOACCEW2_MAXSGENTWIES		28

/*
 * Stwuctuwe fow I/O accewewatow (mode 1) commands.
 * Note that this stwuctuwe must be 128-byte awigned in size.
 */
#define IOACCEW1_COMMANDWIST_AWIGNMENT 128
stwuct io_accew1_cmd {
	__we16 dev_handwe;		/* 0x00 - 0x01 */
	u8  wesewved1;			/* 0x02 */
	u8  function;			/* 0x03 */
	u8  wesewved2[8];		/* 0x04 - 0x0B */
	u32 eww_info;			/* 0x0C - 0x0F */
	u8  wesewved3[2];		/* 0x10 - 0x11 */
	u8  eww_info_wen;		/* 0x12 */
	u8  wesewved4;			/* 0x13 */
	u8  sgw_offset;			/* 0x14 */
	u8  wesewved5[7];		/* 0x15 - 0x1B */
	__we32 twansfew_wen;		/* 0x1C - 0x1F */
	u8  wesewved6[4];		/* 0x20 - 0x23 */
	__we16 io_fwags;		/* 0x24 - 0x25 */
	u8  wesewved7[14];		/* 0x26 - 0x33 */
	u8  WUN[8];			/* 0x34 - 0x3B */
	__we32 contwow;			/* 0x3C - 0x3F */
	u8  CDB[16];			/* 0x40 - 0x4F */
	u8  wesewved8[16];		/* 0x50 - 0x5F */
	__we16 host_context_fwags;	/* 0x60 - 0x61 */
	__we16 timeout_sec;		/* 0x62 - 0x63 */
	u8  WepwyQueue;			/* 0x64 */
	u8  wesewved9[3];		/* 0x65 - 0x67 */
	__we64 tag;			/* 0x68 - 0x6F */
	__we64 host_addw;		/* 0x70 - 0x77 */
	u8  CISS_WUN[8];		/* 0x78 - 0x7F */
	stwuct SGDescwiptow SG[IOACCEW1_MAXSGENTWIES];
} __packed __awigned(IOACCEW1_COMMANDWIST_AWIGNMENT);

#define IOACCEW1_FUNCTION_SCSIIO        0x00
#define IOACCEW1_SGWOFFSET              32

#define IOACCEW1_IOFWAGS_IO_WEQ         0x4000
#define IOACCEW1_IOFWAGS_CDBWEN_MASK    0x001F
#define IOACCEW1_IOFWAGS_CDBWEN_MAX     16

#define IOACCEW1_CONTWOW_NODATAXFEW     0x00000000
#define IOACCEW1_CONTWOW_DATA_OUT       0x01000000
#define IOACCEW1_CONTWOW_DATA_IN        0x02000000
#define IOACCEW1_CONTWOW_TASKPWIO_MASK  0x00007800
#define IOACCEW1_CONTWOW_TASKPWIO_SHIFT 11
#define IOACCEW1_CONTWOW_SIMPWEQUEUE    0x00000000
#define IOACCEW1_CONTWOW_HEADOFQUEUE    0x00000100
#define IOACCEW1_CONTWOW_OWDEWEDQUEUE   0x00000200
#define IOACCEW1_CONTWOW_ACA            0x00000400

#define IOACCEW1_HCFWAGS_CISS_FOWMAT    0x0013

#define IOACCEW1_BUSADDW_CMDTYPE        0x00000060

stwuct ioaccew2_sg_ewement {
	__we64 addwess;
	__we32 wength;
	u8 wesewved[3];
	u8 chain_indicatow;
#define IOACCEW2_CHAIN 0x80
#define IOACCEW2_WAST_SG 0x40
} __packed;

/*
 * SCSI Wesponse Fowmat stwuctuwe fow IO Accewewatow Mode 2
 */
stwuct io_accew2_scsi_wesponse {
	u8 IU_type;
#define IOACCEW2_IU_TYPE_SWF			0x60
	u8 wesewved1[3];
	u8 weq_id[4];		/* wequest identifiew */
	u8 wesewved2[4];
	u8 sewv_wesponse;		/* sewvice wesponse */
#define IOACCEW2_SEWV_WESPONSE_COMPWETE		0x000
#define IOACCEW2_SEWV_WESPONSE_FAIWUWE		0x001
#define IOACCEW2_SEWV_WESPONSE_TMF_COMPWETE	0x002
#define IOACCEW2_SEWV_WESPONSE_TMF_SUCCESS	0x003
#define IOACCEW2_SEWV_WESPONSE_TMF_WEJECTED	0x004
#define IOACCEW2_SEWV_WESPONSE_TMF_WWONG_WUN	0x005
	u8 status;			/* status */
#define IOACCEW2_STATUS_SW_TASK_COMP_GOOD	0x00
#define IOACCEW2_STATUS_SW_TASK_COMP_CHK_COND	0x02
#define IOACCEW2_STATUS_SW_TASK_COMP_BUSY	0x08
#define IOACCEW2_STATUS_SW_TASK_COMP_WES_CON	0x18
#define IOACCEW2_STATUS_SW_TASK_COMP_SET_FUWW	0x28
#define IOACCEW2_STATUS_SW_TASK_COMP_ABOWTED	0x40
#define IOACCEW2_STATUS_SW_IOACCEW_DISABWED	0x0E
#define IOACCEW2_STATUS_SW_IO_EWWOW		0x01
#define IOACCEW2_STATUS_SW_IO_ABOWTED		0x02
#define IOACCEW2_STATUS_SW_NO_PATH_TO_DEVICE	0x03
#define IOACCEW2_STATUS_SW_INVAWID_DEVICE	0x04
#define IOACCEW2_STATUS_SW_UNDEWWUN		0x51
#define IOACCEW2_STATUS_SW_OVEWWUN		0x75
	u8 data_pwesent;		/* wow 2 bits */
#define IOACCEW2_NO_DATAPWESENT		0x000
#define IOACCEW2_WESPONSE_DATAPWESENT	0x001
#define IOACCEW2_SENSE_DATA_PWESENT	0x002
#define IOACCEW2_WESEWVED		0x003
	u8 sense_data_wen;		/* sense/wesponse data wength */
	u8 wesid_cnt[4];		/* wesiduaw count */
	u8 sense_data_buff[32];		/* sense/wesponse data buffew */
} __packed;

/*
 * Stwuctuwe fow I/O accewewatow (mode 2 ow m2) commands.
 * Note that this stwuctuwe must be 128-byte awigned in size.
 */
#define IOACCEW2_COMMANDWIST_AWIGNMENT 128
stwuct io_accew2_cmd {
	u8  IU_type;			/* IU Type */
	u8  diwection;			/* diwection, memtype, and encwyption */
#define IOACCEW2_DIWECTION_MASK		0x03 /* bits 0,1: diwection  */
#define IOACCEW2_DIWECTION_MEMTYPE_MASK	0x04 /* bit 2: memtype souwce/dest */
					     /*     0b=PCIe, 1b=DDW */
#define IOACCEW2_DIWECTION_ENCWYPT_MASK	0x08 /* bit 3: encwyption fwag */
					     /*     0=off, 1=on */
	u8  wepwy_queue;		/* Wepwy Queue ID */
	u8  wesewved1;			/* Wesewved */
	__we32 scsi_nexus;		/* Device Handwe */
	__we32 Tag;			/* cciss tag, wowew 4 bytes onwy */
	__we32 tweak_wowew;		/* Encwyption tweak, wowew 4 bytes */
	u8  cdb[16];			/* SCSI Command Descwiptow Bwock */
	u8  cciss_wun[8];		/* 8 byte SCSI addwess */
	__we32 data_wen;		/* Totaw bytes to twansfew */
	u8  cmd_pwiowity_task_attw;	/* pwiowity and task attws */
#define IOACCEW2_PWIOWITY_MASK 0x78
#define IOACCEW2_ATTW_MASK 0x07
	u8  sg_count;			/* Numbew of sg ewements */
	__we16 dekindex;		/* Data encwyption key index */
	__we64 eww_ptw;			/* Ewwow Pointew */
	__we32 eww_wen;			/* Ewwow Wength*/
	__we32 tweak_uppew;		/* Encwyption tweak, uppew 4 bytes */
	stwuct ioaccew2_sg_ewement sg[IOACCEW2_MAXSGENTWIES];
	stwuct io_accew2_scsi_wesponse ewwow_data;
} __packed __awigned(IOACCEW2_COMMANDWIST_AWIGNMENT);

/*
 * defines fow Mode 2 command stwuct
 * FIXME: this can't be aww I need mfm
 */
#define IOACCEW2_IU_TYPE	0x40
#define IOACCEW2_IU_TMF_TYPE	0x41
#define IOACCEW2_DIW_NO_DATA	0x00
#define IOACCEW2_DIW_DATA_IN	0x01
#define IOACCEW2_DIW_DATA_OUT	0x02
#define IOACCEW2_TMF_ABOWT	0x01
/*
 * SCSI Task Management Wequest fowmat fow Accewewatow Mode 2
 */
stwuct hpsa_tmf_stwuct {
	u8 iu_type;		/* Infowmation Unit Type */
	u8 wepwy_queue;		/* Wepwy Queue ID */
	u8 tmf;			/* Task Management Function */
	u8 wesewved1;		/* byte 3 Wesewved */
	__we32 it_nexus;	/* SCSI I-T Nexus */
	u8 wun_id[8];		/* WUN ID fow TMF wequest */
	__we64 tag;		/* cciss tag associated w/ wequest */
	__we64 abowt_tag;	/* cciss tag of SCSI cmd ow TMF to abowt */
	__we64 ewwow_ptw;		/* Ewwow Pointew */
	__we32 ewwow_wen;		/* Ewwow Wength */
} __packed __awigned(IOACCEW2_COMMANDWIST_AWIGNMENT);

/* Configuwation Tabwe Stwuctuwe */
stwuct HostWwite {
	__we32		TwanspowtWequest;
	__we32		command_poow_addw_hi;
	__we32		CoawIntDeway;
	__we32		CoawIntCount;
} __packed;

#define SIMPWE_MODE     0x02
#define PEWFOWMANT_MODE 0x04
#define MEMQ_MODE       0x08
#define IOACCEW_MODE_1  0x80

#define DWIVEW_SUPPOWT_UA_ENABWE        0x00000001

stwuct CfgTabwe {
	u8		Signatuwe[4];
	__we32		SpecVawence;
	__we32		TwanspowtSuppowt;
	__we32		TwanspowtActive;
	stwuct HostWwite HostWwite;
	__we32		CmdsOutMax;
	__we32		BusTypes;
	__we32		TwansMethodOffset;
	u8		SewvewName[16];
	__we32		HeawtBeat;
	__we32		dwivew_suppowt;
#define			ENABWE_SCSI_PWEFETCH		0x100
#define			ENABWE_UNIT_ATTN		0x01
	__we32		MaxScattewGathewEwements;
	__we32		MaxWogicawUnits;
	__we32		MaxPhysicawDevices;
	__we32		MaxPhysicawDwivesPewWogicawUnit;
	__we32		MaxPewfowmantModeCommands;
	__we32		MaxBwockFetch;
	__we32		PowewConsewvationSuppowt;
	__we32		PowewConsewvationEnabwe;
	__we32		TMFSuppowtFwags;
	u8		TMFTagMask[8];
	u8		wesewved[0x78 - 0x70];
	__we32		misc_fw_suppowt;		/* offset 0x78 */
#define			MISC_FW_DOOWBEWW_WESET		0x02
#define			MISC_FW_DOOWBEWW_WESET2		0x010
#define			MISC_FW_WAID_OFFWOAD_BASIC	0x020
#define			MISC_FW_EVENT_NOTIFY		0x080
	u8		dwivew_vewsion[32];
	__we32		max_cached_wwite_size;
	u8		dwivew_scwatchpad[16];
	__we32		max_ewwow_info_wength;
	__we32		io_accew_max_embedded_sg_count;
	__we32		io_accew_wequest_size_offset;
	__we32		event_notify;
#define		HPSA_EVENT_NOTIFY_ACCEW_IO_PATH_STATE_CHANGE (1 << 30)
#define		HPSA_EVENT_NOTIFY_ACCEW_IO_PATH_CONFIG_CHANGE (1 << 31)
	__we32		cweaw_event_notify;
} __packed;

#define NUM_BWOCKFETCH_ENTWIES 8
stwuct TwansTabwe_stwuct {
	__we32		BwockFetch[NUM_BWOCKFETCH_ENTWIES];
	__we32		WepQSize;
	__we32		WepQCount;
	__we32		WepQCtwAddwWow32;
	__we32		WepQCtwAddwHigh32;
#define MAX_WEPWY_QUEUES 64
	stwuct vaws32  WepQAddw[MAX_WEPWY_QUEUES];
} __packed;

stwuct hpsa_pci_info {
	unsigned chaw	bus;
	unsigned chaw	dev_fn;
	unsigned showt	domain;
	u32		boawd_id;
} __packed;

stwuct bmic_identify_contwowwew {
	u8	configuwed_wogicaw_dwive_count;	/* offset 0 */
	u8	pad1[153];
	__we16	extended_wogicaw_unit_count;	/* offset 154 */
	u8	pad2[136];
	u8	contwowwew_mode;	/* offset 292 */
	u8	pad3[32];
} __packed;


stwuct bmic_identify_physicaw_device {
	u8    scsi_bus;          /* SCSI Bus numbew on contwowwew */
	u8    scsi_id;           /* SCSI ID on this bus */
	__we16 bwock_size;	     /* sectow size in bytes */
	__we32 totaw_bwocks;	     /* numbew fow sectows on dwive */
	__we32 wesewved_bwocks;   /* contwowwew wesewved (WIS) */
	u8    modew[40];         /* Physicaw Dwive Modew */
	u8    sewiaw_numbew[40]; /* Dwive Sewiaw Numbew */
	u8    fiwmwawe_wevision[8]; /* dwive fiwmwawe wevision */
	u8    scsi_inquiwy_bits; /* inquiwy byte 7 bits */
	u8    compaq_dwive_stamp; /* 0 means dwive not stamped */
	u8    wast_faiwuwe_weason;
#define BMIC_WAST_FAIWUWE_TOO_SMAWW_IN_WOAD_CONFIG		0x01
#define BMIC_WAST_FAIWUWE_EWWOW_EWASING_WIS			0x02
#define BMIC_WAST_FAIWUWE_EWWOW_SAVING_WIS			0x03
#define BMIC_WAST_FAIWUWE_FAIW_DWIVE_COMMAND			0x04
#define BMIC_WAST_FAIWUWE_MAWK_BAD_FAIWED			0x05
#define BMIC_WAST_FAIWUWE_MAWK_BAD_FAIWED_IN_FINISH_WEMAP	0x06
#define BMIC_WAST_FAIWUWE_TIMEOUT				0x07
#define BMIC_WAST_FAIWUWE_AUTOSENSE_FAIWED			0x08
#define BMIC_WAST_FAIWUWE_MEDIUM_EWWOW_1			0x09
#define BMIC_WAST_FAIWUWE_MEDIUM_EWWOW_2			0x0a
#define BMIC_WAST_FAIWUWE_NOT_WEADY_BAD_SENSE			0x0b
#define BMIC_WAST_FAIWUWE_NOT_WEADY				0x0c
#define BMIC_WAST_FAIWUWE_HAWDWAWE_EWWOW			0x0d
#define BMIC_WAST_FAIWUWE_ABOWTED_COMMAND			0x0e
#define BMIC_WAST_FAIWUWE_WWITE_PWOTECTED			0x0f
#define BMIC_WAST_FAIWUWE_SPIN_UP_FAIWUWE_IN_WECOVEW		0x10
#define BMIC_WAST_FAIWUWE_WEBUIWD_WWITE_EWWOW			0x11
#define BMIC_WAST_FAIWUWE_TOO_SMAWW_IN_HOT_PWUG			0x12
#define BMIC_WAST_FAIWUWE_BUS_WESET_WECOVEWY_ABOWTED		0x13
#define BMIC_WAST_FAIWUWE_WEMOVED_IN_HOT_PWUG			0x14
#define BMIC_WAST_FAIWUWE_INIT_WEQUEST_SENSE_FAIWED		0x15
#define BMIC_WAST_FAIWUWE_INIT_STAWT_UNIT_FAIWED		0x16
#define BMIC_WAST_FAIWUWE_INQUIWY_FAIWED			0x17
#define BMIC_WAST_FAIWUWE_NON_DISK_DEVICE			0x18
#define BMIC_WAST_FAIWUWE_WEAD_CAPACITY_FAIWED			0x19
#define BMIC_WAST_FAIWUWE_INVAWID_BWOCK_SIZE			0x1a
#define BMIC_WAST_FAIWUWE_HOT_PWUG_WEQUEST_SENSE_FAIWED		0x1b
#define BMIC_WAST_FAIWUWE_HOT_PWUG_STAWT_UNIT_FAIWED		0x1c
#define BMIC_WAST_FAIWUWE_WWITE_EWWOW_AFTEW_WEMAP		0x1d
#define BMIC_WAST_FAIWUWE_INIT_WESET_WECOVEWY_ABOWTED		0x1e
#define BMIC_WAST_FAIWUWE_DEFEWWED_WWITE_EWWOW			0x1f
#define BMIC_WAST_FAIWUWE_MISSING_IN_SAVE_WIS			0x20
#define BMIC_WAST_FAIWUWE_WWONG_WEPWACE				0x21
#define BMIC_WAST_FAIWUWE_GDP_VPD_INQUIWY_FAIWED		0x22
#define BMIC_WAST_FAIWUWE_GDP_MODE_SENSE_FAIWED			0x23
#define BMIC_WAST_FAIWUWE_DWIVE_NOT_IN_48BIT_MODE		0x24
#define BMIC_WAST_FAIWUWE_DWIVE_TYPE_MIX_IN_HOT_PWUG		0x25
#define BMIC_WAST_FAIWUWE_DWIVE_TYPE_MIX_IN_WOAD_CFG		0x26
#define BMIC_WAST_FAIWUWE_PWOTOCOW_ADAPTEW_FAIWED		0x27
#define BMIC_WAST_FAIWUWE_FAUWTY_ID_BAY_EMPTY			0x28
#define BMIC_WAST_FAIWUWE_FAUWTY_ID_BAY_OCCUPIED		0x29
#define BMIC_WAST_FAIWUWE_FAUWTY_ID_INVAWID_BAY			0x2a
#define BMIC_WAST_FAIWUWE_WWITE_WETWIES_FAIWED			0x2b

#define BMIC_WAST_FAIWUWE_SMAWT_EWWOW_WEPOWTED			0x37
#define BMIC_WAST_FAIWUWE_PHY_WESET_FAIWED			0x38
#define BMIC_WAST_FAIWUWE_ONWY_ONE_CTWW_CAN_SEE_DWIVE		0x40
#define BMIC_WAST_FAIWUWE_KC_VOWUME_FAIWED			0x41
#define BMIC_WAST_FAIWUWE_UNEXPECTED_WEPWACEMENT		0x42
#define BMIC_WAST_FAIWUWE_OFFWINE_EWASE				0x80
#define BMIC_WAST_FAIWUWE_OFFWINE_TOO_SMAWW			0x81
#define BMIC_WAST_FAIWUWE_OFFWINE_DWIVE_TYPE_MIX		0x82
#define BMIC_WAST_FAIWUWE_OFFWINE_EWASE_COMPWETE		0x83

	u8     fwags;
	u8     mowe_fwags;
	u8     scsi_wun;          /* SCSI WUN fow phys dwive */
	u8     yet_mowe_fwags;
	u8     even_mowe_fwags;
	__we32 spi_speed_wuwes;/* SPI Speed data:Uwtwa disabwe diagnose */
	u8     phys_connectow[2];         /* connectow numbew on contwowwew */
	u8     phys_box_on_bus;  /* phys encwosuwe this dwive wesides */
	u8     phys_bay_in_box;  /* phys dwv bay this dwive wesides */
	__we32 wpm;              /* Dwive wotationaw speed in wpm */
	u8     device_type;       /* type of dwive */
#define BMIC_DEVICE_TYPE_CONTWOWWEW	0x07

	u8     sata_vewsion;     /* onwy vawid when dwive_type is SATA */
	__we64 big_totaw_bwock_count;
	__we64 wis_stawting_wba;
	__we32 wis_size;
	u8     wwid[20];
	u8     contwowwew_phy_map[32];
	__we16 phy_count;
	u8     phy_connected_dev_type[256];
	u8     phy_to_dwive_bay_num[256];
	__we16 phy_to_attached_dev_index[256];
	u8     box_index;
	u8     wesewved;
	__we16 extwa_physicaw_dwive_fwags;
#define BMIC_PHYS_DWIVE_SUPPOWTS_GAS_GAUGE(idphydwv) \
	(idphydwv->extwa_physicaw_dwive_fwags & (1 << 10))
	u8     negotiated_wink_wate[256];
	u8     phy_to_phy_map[256];
	u8     wedundant_path_pwesent_map;
	u8     wedundant_path_faiwuwe_map;
	u8     active_path_numbew;
	__we16 awtewnate_paths_phys_connectow[8];
	u8     awtewnate_paths_phys_box_on_powt[8];
	u8     muwti_wun_device_wun_count;
	u8     minimum_good_fw_wevision[8];
	u8     unique_inquiwy_bytes[20];
	u8     cuwwent_tempewatuwe_degweesC;
	u8     tempewatuwe_thweshowd_degweesC;
	u8     max_tempewatuwe_degweesC;
	u8     wogicaw_bwocks_pew_phys_bwock_exp; /* phybwocksize = 512*2^exp */
	__we16 cuwwent_queue_depth_wimit;
	u8     wesewved_switch_stuff[60];
	__we16 powew_on_houws; /* vawid onwy if gas gauge suppowted */
	__we16 pewcent_enduwance_used; /* vawid onwy if gas gauge suppowted. */
#define BMIC_PHYS_DWIVE_SSD_WEAWOUT(idphydwv) \
	((idphydwv->pewcent_enduwance_used & 0x80) || \
	 (idphydwv->pewcent_enduwance_used > 10000))
	u8     dwive_authentication;
#define BMIC_PHYS_DWIVE_AUTHENTICATED(idphydwv) \
	(idphydwv->dwive_authentication == 0x80)
	u8     smawt_cawwiew_authentication;
#define BMIC_SMAWT_CAWWIEW_AUTHENTICATION_SUPPOWTED(idphydwv) \
	(idphydwv->smawt_cawwiew_authentication != 0x0)
#define BMIC_SMAWT_CAWWIEW_AUTHENTICATED(idphydwv) \
	(idphydwv->smawt_cawwiew_authentication == 0x01)
	u8     smawt_cawwiew_app_fw_vewsion;
	u8     smawt_cawwiew_bootwoadew_fw_vewsion;
	u8     sanitize_suppowt_fwags;
	u8     dwive_key_fwags;
	u8     encwyption_key_name[64];
	__we32 misc_dwive_fwags;
	__we16 dek_index;
	__we16 hba_dwive_encwyption_fwags;
	__we16 max_ovewwwite_time;
	__we16 max_bwock_ewase_time;
	__we16 max_cwypto_ewase_time;
	u8     device_connectow_info[5];
	u8     connectow_name[8][8];
	u8     page_83_id[16];
	u8     max_wink_wate[256];
	u8     neg_phys_wink_wate[256];
	u8     box_conn_name[8];
} __packed __attwibute((awigned(512)));

stwuct bmic_sense_subsystem_info {
	u8	pwimawy_swot_numbew;
	u8	wesewved[3];
	u8	chasis_sewiaw_numbew[32];
	u8	pwimawy_wowwd_wide_id[8];
	u8	pwimawy_awway_sewiaw_numbew[32]; /* NUWW tewminated */
	u8	pwimawy_cache_sewiaw_numbew[32]; /* NUWW tewminated */
	u8	wesewved_2[8];
	u8	secondawy_awway_sewiaw_numbew[32];
	u8	secondawy_cache_sewiaw_numbew[32];
	u8	pad[332];
} __packed;

stwuct bmic_sense_stowage_box_pawams {
	u8	wesewved[36];
	u8	inquiwy_vawid;
	u8	wesewved_1[68];
	u8	phys_box_on_powt;
	u8	wesewved_2[22];
	u16	connection_info;
	u8	wesewvew_3[84];
	u8	phys_connectow[2];
	u8	wesewved_4[296];
} __packed;

#endif /* HPSA_CMD_H */
