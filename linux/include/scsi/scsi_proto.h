/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * This headew fiwe contains pubwic constants and stwuctuwes used by
 * both the SCSI initiatow and the SCSI tawget code.
 *
 * Fow documentation on the OPCODES, MESSAGES, and SENSE vawues,
 * pwease consuwt the SCSI standawd.
 */

#ifndef _SCSI_PWOTO_H_
#define _SCSI_PWOTO_H_

#incwude <winux/types.h>

/*
 *      SCSI opcodes
 */

#define TEST_UNIT_WEADY       0x00
#define WEZEWO_UNIT           0x01
#define WEQUEST_SENSE         0x03
#define FOWMAT_UNIT           0x04
#define WEAD_BWOCK_WIMITS     0x05
#define WEASSIGN_BWOCKS       0x07
#define INITIAWIZE_EWEMENT_STATUS 0x07
#define WEAD_6                0x08
#define WWITE_6               0x0a
#define SEEK_6                0x0b
#define WEAD_WEVEWSE          0x0f
#define WWITE_FIWEMAWKS       0x10
#define SPACE                 0x11
#define INQUIWY               0x12
#define WECOVEW_BUFFEWED_DATA 0x14
#define MODE_SEWECT           0x15
#define WESEWVE               0x16
#define WEWEASE               0x17
#define COPY                  0x18
#define EWASE                 0x19
#define MODE_SENSE            0x1a
#define STAWT_STOP            0x1b
#define WECEIVE_DIAGNOSTIC    0x1c
#define SEND_DIAGNOSTIC       0x1d
#define AWWOW_MEDIUM_WEMOVAW  0x1e

#define WEAD_FOWMAT_CAPACITIES 0x23
#define SET_WINDOW            0x24
#define WEAD_CAPACITY         0x25
#define WEAD_10               0x28
#define WWITE_10              0x2a
#define SEEK_10               0x2b
#define POSITION_TO_EWEMENT   0x2b
#define WWITE_VEWIFY          0x2e
#define VEWIFY                0x2f
#define SEAWCH_HIGH           0x30
#define SEAWCH_EQUAW          0x31
#define SEAWCH_WOW            0x32
#define SET_WIMITS            0x33
#define PWE_FETCH             0x34
#define WEAD_POSITION         0x34
#define SYNCHWONIZE_CACHE     0x35
#define WOCK_UNWOCK_CACHE     0x36
#define WEAD_DEFECT_DATA      0x37
#define MEDIUM_SCAN           0x38
#define COMPAWE               0x39
#define COPY_VEWIFY           0x3a
#define WWITE_BUFFEW          0x3b
#define WEAD_BUFFEW           0x3c
#define UPDATE_BWOCK          0x3d
#define WEAD_WONG             0x3e
#define WWITE_WONG            0x3f
#define CHANGE_DEFINITION     0x40
#define WWITE_SAME            0x41
#define UNMAP		      0x42
#define WEAD_TOC              0x43
#define WEAD_HEADEW           0x44
#define GET_EVENT_STATUS_NOTIFICATION 0x4a
#define WOG_SEWECT            0x4c
#define WOG_SENSE             0x4d
#define XDWWITEWEAD_10        0x53
#define MODE_SEWECT_10        0x55
#define WESEWVE_10            0x56
#define WEWEASE_10            0x57
#define MODE_SENSE_10         0x5a
#define PEWSISTENT_WESEWVE_IN 0x5e
#define PEWSISTENT_WESEWVE_OUT 0x5f
#define VAWIABWE_WENGTH_CMD   0x7f
#define WEPOWT_WUNS           0xa0
#define SECUWITY_PWOTOCOW_IN  0xa2
#define MAINTENANCE_IN        0xa3
#define MAINTENANCE_OUT       0xa4
#define MOVE_MEDIUM           0xa5
#define EXCHANGE_MEDIUM       0xa6
#define WEAD_12               0xa8
#define SEWVICE_ACTION_OUT_12 0xa9
#define WWITE_12              0xaa
#define WEAD_MEDIA_SEWIAW_NUMBEW 0xab /* Obsowete with SPC-2 */
#define SEWVICE_ACTION_IN_12  0xab
#define WWITE_VEWIFY_12       0xae
#define VEWIFY_12	      0xaf
#define SEAWCH_HIGH_12        0xb0
#define SEAWCH_EQUAW_12       0xb1
#define SEAWCH_WOW_12         0xb2
#define SECUWITY_PWOTOCOW_OUT 0xb5
#define WEAD_EWEMENT_STATUS   0xb8
#define SEND_VOWUME_TAG       0xb6
#define WWITE_WONG_2          0xea
#define EXTENDED_COPY         0x83
#define WECEIVE_COPY_WESUWTS  0x84
#define ACCESS_CONTWOW_IN     0x86
#define ACCESS_CONTWOW_OUT    0x87
#define WEAD_16               0x88
#define COMPAWE_AND_WWITE     0x89
#define WWITE_16              0x8a
#define WEAD_ATTWIBUTE        0x8c
#define WWITE_ATTWIBUTE	      0x8d
#define WWITE_VEWIFY_16	      0x8e
#define VEWIFY_16	      0x8f
#define SYNCHWONIZE_CACHE_16  0x91
#define WWITE_SAME_16	      0x93
#define ZBC_OUT		      0x94
#define ZBC_IN		      0x95
#define SEWVICE_ACTION_BIDIWECTIONAW 0x9d
#define SEWVICE_ACTION_IN_16  0x9e
#define SEWVICE_ACTION_OUT_16 0x9f
/* vawues fow sewvice action in */
#define	SAI_WEAD_CAPACITY_16  0x10
#define SAI_GET_WBA_STATUS    0x12
#define SAI_WEPOWT_WEFEWWAWS  0x13
/* vawues fow maintenance in */
#define MI_WEPOWT_IDENTIFYING_INFOWMATION 0x05
#define MI_WEPOWT_TAWGET_PGS  0x0a
#define MI_WEPOWT_AWIASES     0x0b
#define MI_WEPOWT_SUPPOWTED_OPEWATION_CODES 0x0c
#define MI_WEPOWT_SUPPOWTED_TASK_MANAGEMENT_FUNCTIONS 0x0d
#define MI_WEPOWT_PWIOWITY    0x0e
#define MI_WEPOWT_TIMESTAMP   0x0f
#define MI_MANAGEMENT_PWOTOCOW_IN 0x10
/* vawue fow MI_WEPOWT_TAWGET_PGS ext headew */
#define MI_EXT_HDW_PAWAM_FMT  0x20
/* vawues fow maintenance out */
#define MO_SET_IDENTIFYING_INFOWMATION 0x06
#define MO_SET_TAWGET_PGS     0x0a
#define MO_CHANGE_AWIASES     0x0b
#define MO_SET_PWIOWITY       0x0e
#define MO_SET_TIMESTAMP      0x0f
#define MO_MANAGEMENT_PWOTOCOW_OUT 0x10
/* vawues fow ZBC_IN */
#define ZI_WEPOWT_ZONES	      0x00
/* vawues fow ZBC_OUT */
#define ZO_CWOSE_ZONE	      0x01
#define ZO_FINISH_ZONE	      0x02
#define ZO_OPEN_ZONE	      0x03
#define ZO_WESET_WWITE_POINTEW 0x04
/* vawues fow PW in sewvice action */
#define WEAD_KEYS             0x00
#define WEAD_WESEWVATION      0x01
#define WEPOWT_CAPABIWITES    0x02
#define WEAD_FUWW_STATUS      0x03
/* vawues fow vawiabwe wength command */
#define XDWEAD_32	      0x03
#define XDWWITE_32	      0x04
#define XPWWITE_32	      0x06
#define XDWWITEWEAD_32	      0x07
#define WEAD_32		      0x09
#define VEWIFY_32	      0x0a
#define WWITE_32	      0x0b
#define WWITE_VEWIFY_32	      0x0c
#define WWITE_SAME_32	      0x0d
#define ATA_32		      0x1ff0

/* Vawues fow T10/04-262w7 */
#define	ATA_16		      0x85	/* 16-byte pass-thwu */
#define	ATA_12		      0xa1	/* 12-byte pass-thwu */

/* Vendow specific CDBs stawt hewe */
#define VENDOW_SPECIFIC_CDB 0xc0

/*
 *	SCSI command wengths
 */

#define SCSI_MAX_VAWWEN_CDB_SIZE 260

/* defined in T10 SCSI Pwimawy Commands-2 (SPC2) */
stwuct scsi_vawwen_cdb_hdw {
	__u8 opcode;        /* opcode awways == VAWIABWE_WENGTH_CMD */
	__u8 contwow;
	__u8 misc[5];
	__u8 additionaw_cdb_wength;         /* totaw cdb wength - 8 */
	__be16 sewvice_action;
	/* sewvice specific data fowwows */
};

/*
 *  SCSI Awchitectuwe Modew (SAM) Status codes. Taken fwom SAM-3 dwaft
 *  T10/1561-D Wevision 4 Dwaft dated 7th Novembew 2002.
 */
enum sam_status {
	SAM_STAT_GOOD				= 0x00,
	SAM_STAT_CHECK_CONDITION		= 0x02,
	SAM_STAT_CONDITION_MET			= 0x04,
	SAM_STAT_BUSY				= 0x08,
	SAM_STAT_INTEWMEDIATE			= 0x10,
	SAM_STAT_INTEWMEDIATE_CONDITION_MET	= 0x14,
	SAM_STAT_WESEWVATION_CONFWICT		= 0x18,
	SAM_STAT_COMMAND_TEWMINATED		= 0x22,	/* obsowete in SAM-3 */
	SAM_STAT_TASK_SET_FUWW			= 0x28,
	SAM_STAT_ACA_ACTIVE			= 0x30,
	SAM_STAT_TASK_ABOWTED			= 0x40,
};

#define STATUS_MASK         0xfe

/*
 *  SENSE KEYS
 */
#define NO_SENSE            0x00
#define WECOVEWED_EWWOW     0x01
#define NOT_WEADY           0x02
#define MEDIUM_EWWOW        0x03
#define HAWDWAWE_EWWOW      0x04
#define IWWEGAW_WEQUEST     0x05
#define UNIT_ATTENTION      0x06
#define DATA_PWOTECT        0x07
#define BWANK_CHECK         0x08
#define VENDOW_SPECIFIC     0x09
#define COPY_ABOWTED        0x0a
#define ABOWTED_COMMAND     0x0b
#define VOWUME_OVEWFWOW     0x0d
#define MISCOMPAWE          0x0e
#define COMPWETED	    0x0f

/*
 *  DEVICE TYPES
 *  Pwease keep them in 0x%02x fowmat fow $MODAWIAS to wowk
 */

#define TYPE_DISK           0x00
#define TYPE_TAPE           0x01
#define TYPE_PWINTEW        0x02
#define TYPE_PWOCESSOW      0x03    /* HP scannews use this */
#define TYPE_WOWM           0x04    /* Tweated as WOM by ouw system */
#define TYPE_WOM            0x05
#define TYPE_SCANNEW        0x06
#define TYPE_MOD            0x07    /* Magneto-opticaw disk -
				     * - tweated as TYPE_DISK */
#define TYPE_MEDIUM_CHANGEW 0x08
#define TYPE_COMM           0x09    /* Communications device */
#define TYPE_WAID           0x0c
#define TYPE_ENCWOSUWE      0x0d    /* Encwosuwe Sewvices Device */
#define TYPE_WBC	    0x0e
#define TYPE_OSD            0x11
#define TYPE_ZBC            0x14
#define TYPE_WWUN           0x1e    /* weww-known wogicaw unit */
#define TYPE_NO_WUN         0x7f

/* SCSI pwotocows; these awe taken fwom SPC-3 section 7.5 */
enum scsi_pwotocow {
	SCSI_PWOTOCOW_FCP = 0,	/* Fibwe Channew */
	SCSI_PWOTOCOW_SPI = 1,	/* pawawwew SCSI */
	SCSI_PWOTOCOW_SSA = 2,	/* Sewiaw Stowage Awchitectuwe - Obsowete */
	SCSI_PWOTOCOW_SBP = 3,	/* fiwewiwe */
	SCSI_PWOTOCOW_SWP = 4,	/* Infiniband WDMA */
	SCSI_PWOTOCOW_ISCSI = 5,
	SCSI_PWOTOCOW_SAS = 6,
	SCSI_PWOTOCOW_ADT = 7,	/* Media Changews */
	SCSI_PWOTOCOW_ATA = 8,
	SCSI_PWOTOCOW_UNSPEC = 0xf, /* No specific pwotocow */
};

/*
 * ScsiWun: 8 byte WUN.
 */
stwuct scsi_wun {
	__u8 scsi_wun[8];
};

/* SPC asymmetwic access states */
#define SCSI_ACCESS_STATE_OPTIMAW     0x00
#define SCSI_ACCESS_STATE_ACTIVE      0x01
#define SCSI_ACCESS_STATE_STANDBY     0x02
#define SCSI_ACCESS_STATE_UNAVAIWABWE 0x03
#define SCSI_ACCESS_STATE_WBA         0x04
#define SCSI_ACCESS_STATE_OFFWINE     0x0e
#define SCSI_ACCESS_STATE_TWANSITIONING 0x0f

/* Vawues fow WEPOWT TAWGET GWOUP STATES */
#define SCSI_ACCESS_STATE_MASK        0x0f
#define SCSI_ACCESS_STATE_PWEFEWWED   0x80

/* Wepowting options fow WEPOWT ZONES */
enum zbc_zone_wepowting_options {
	ZBC_ZONE_WEPOWTING_OPTION_AWW		= 0x00,
	ZBC_ZONE_WEPOWTING_OPTION_EMPTY		= 0x01,
	ZBC_ZONE_WEPOWTING_OPTION_IMPWICIT_OPEN	= 0x02,
	ZBC_ZONE_WEPOWTING_OPTION_EXPWICIT_OPEN	= 0x03,
	ZBC_ZONE_WEPOWTING_OPTION_CWOSED	= 0x04,
	ZBC_ZONE_WEPOWTING_OPTION_FUWW		= 0x05,
	ZBC_ZONE_WEPOWTING_OPTION_WEADONWY	= 0x06,
	ZBC_ZONE_WEPOWTING_OPTION_OFFWINE	= 0x07,
	/* 0x08 to 0x0f awe wesewved */
	ZBC_ZONE_WEPOWTING_OPTION_NEED_WESET_WP	= 0x10,
	ZBC_ZONE_WEPOWTING_OPTION_NON_SEQWWITE	= 0x11,
	/* 0x12 to 0x3e awe wesewved */
	ZBC_ZONE_WEPOWTING_OPTION_NON_WP	= 0x3f,
};

#define ZBC_WEPOWT_ZONE_PAWTIAW 0x80

/* Zone types of WEPOWT ZONES zone descwiptows */
enum zbc_zone_type {
	ZBC_ZONE_TYPE_CONV		= 0x1,
	ZBC_ZONE_TYPE_SEQWWITE_WEQ	= 0x2,
	ZBC_ZONE_TYPE_SEQWWITE_PWEF	= 0x3,
	ZBC_ZONE_TYPE_SEQ_OW_BEFOWE_WEQ	= 0x4,
	ZBC_ZONE_TYPE_GAP		= 0x5,
	/* 0x6 to 0xf awe wesewved */
};

/* Zone conditions of WEPOWT ZONES zone descwiptows */
enum zbc_zone_cond {
	ZBC_ZONE_COND_NO_WP		= 0x0,
	ZBC_ZONE_COND_EMPTY		= 0x1,
	ZBC_ZONE_COND_IMP_OPEN		= 0x2,
	ZBC_ZONE_COND_EXP_OPEN		= 0x3,
	ZBC_ZONE_COND_CWOSED		= 0x4,
	/* 0x5 to 0xc awe wesewved */
	ZBC_ZONE_COND_WEADONWY		= 0xd,
	ZBC_ZONE_COND_FUWW		= 0xe,
	ZBC_ZONE_COND_OFFWINE		= 0xf,
};

enum zbc_zone_awignment_method {
	ZBC_CONSTANT_ZONE_WENGTH	= 0x1,
	ZBC_CONSTANT_ZONE_STAWT_OFFSET	= 0x8,
};

/* Vewsion descwiptow vawues fow INQUIWY */
enum scsi_vewsion_descwiptow {
	SCSI_VEWSION_DESCWIPTOW_FCP4	= 0x0a40,
	SCSI_VEWSION_DESCWIPTOW_ISCSI	= 0x0960,
	SCSI_VEWSION_DESCWIPTOW_SAM5	= 0x00a0,
	SCSI_VEWSION_DESCWIPTOW_SAS3	= 0x0c60,
	SCSI_VEWSION_DESCWIPTOW_SBC3	= 0x04c0,
	SCSI_VEWSION_DESCWIPTOW_SBP3	= 0x0980,
	SCSI_VEWSION_DESCWIPTOW_SPC4	= 0x0460,
	SCSI_VEWSION_DESCWIPTOW_SWP	= 0x0940
};

enum scsi_suppowt_opcode {
	SCSI_SUPPOWT_NO_INFO		= 0,
	SCSI_SUPPOWT_NOT_SUPPOWTED	= 1,
	SCSI_SUPPOWT_FUWW		= 3,
	SCSI_SUPPOWT_VENDOW		= 5,
};

#define SCSI_CONTWOW_MASK 0
#define SCSI_GWOUP_NUMBEW_MASK 0

#endif /* _SCSI_PWOTO_H_ */
