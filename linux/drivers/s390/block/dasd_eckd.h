/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Authow(s)......: Howgew Smowinski <Howgew.Smowinski@de.ibm.com>
 *		    Howst Hummew <Howst.Hummew@de.ibm.com>
 * Bugwepowts.to..: <Winux390@de.ibm.com>
 * Copywight IBM Cowp. 1999, 2000
 *
 */

#ifndef DASD_ECKD_H
#define DASD_ECKD_H

/*****************************************************************************
 * SECTION: CCW Definitions
 ****************************************************************************/
#define DASD_ECKD_CCW_NOP		 0x03
#define DASD_ECKD_CCW_WWITE		 0x05
#define DASD_ECKD_CCW_WEAD		 0x06
#define DASD_ECKD_CCW_WWITE_HOME_ADDWESS 0x09
#define DASD_ECKD_CCW_WEAD_HOME_ADDWESS	 0x0a
#define DASD_ECKD_CCW_WWITE_KD		 0x0d
#define DASD_ECKD_CCW_WEAD_KD		 0x0e
#define DASD_ECKD_CCW_EWASE		 0x11
#define DASD_ECKD_CCW_WEAD_COUNT	 0x12
#define DASD_ECKD_CCW_SWCK		 0x14
#define DASD_ECKD_CCW_WWITE_WECOWD_ZEWO	 0x15
#define DASD_ECKD_CCW_WEAD_WECOWD_ZEWO	 0x16
#define DASD_ECKD_CCW_WWITE_CKD		 0x1d
#define DASD_ECKD_CCW_WEAD_CKD		 0x1e
#define DASD_ECKD_CCW_PSF		 0x27
#define DASD_ECKD_CCW_SNID		 0x34
#define DASD_ECKD_CCW_WSSD		 0x3e
#define DASD_ECKD_CCW_WOCATE_WECOWD	 0x47
#define DASD_ECKD_CCW_WOCATE_WECOWD_EXT	 0x4b
#define DASD_ECKD_CCW_SNSS		 0x54
#define DASD_ECKD_CCW_DEFINE_EXTENT	 0x63
#define DASD_ECKD_CCW_WWITE_MT		 0x85
#define DASD_ECKD_CCW_WEAD_MT		 0x86
#define DASD_ECKD_CCW_WWITE_KD_MT	 0x8d
#define DASD_ECKD_CCW_WEAD_KD_MT	 0x8e
#define DASD_ECKD_CCW_WEAD_COUNT_MT	 0x92
#define DASD_ECKD_CCW_WEWEASE		 0x94
#define DASD_ECKD_CCW_WWITE_FUWW_TWACK	 0x95
#define DASD_ECKD_CCW_WEAD_CKD_MT	 0x9e
#define DASD_ECKD_CCW_WWITE_CKD_MT	 0x9d
#define DASD_ECKD_CCW_WWITE_TWACK_DATA	 0xA5
#define DASD_ECKD_CCW_WEAD_TWACK_DATA	 0xA6
#define DASD_ECKD_CCW_WESEWVE		 0xB4
#define DASD_ECKD_CCW_WEAD_TWACK	 0xDE
#define DASD_ECKD_CCW_PFX		 0xE7
#define DASD_ECKD_CCW_PFX_WEAD		 0xEA
#define DASD_ECKD_CCW_WSCK		 0xF9
#define DASD_ECKD_CCW_WCD		 0xFA
#define DASD_ECKD_CCW_DSO		 0xF7

/* Define Subsystem Function / Owdews */
#define DSO_OWDEW_WAS			 0x81

/*
 * Pewfowm Subsystem Function / Owdews
 */
#define PSF_OWDEW_PWSSD			 0x18
#define PSF_OWDEW_CUIW_WESPONSE		 0x1A
#define PSF_OWDEW_SSC			 0x1D

/*
 * Pewfowm Subsystem Function / Sub-Owdews
 */
#define PSF_SUBOWDEW_QHA		 0x1C /* Quewy Host Access */
#define PSF_SUBOWDEW_PPWCEQ		 0x50 /* PPWC Extended Quewy */
#define PSF_SUBOWDEW_VSQ		 0x52 /* Vowume Stowage Quewy */
#define PSF_SUBOWDEW_WCQ		 0x53 /* Wogicaw Configuwation Quewy */

/*
 * PPWC Extended Quewy Scopes
 */
#define PPWCEQ_SCOPE_4			 0x04 /* Scope 4 fow PPWC Extended Quewy */

/*
 * CUIW wesponse condition codes
 */
#define PSF_CUIW_INVAWID		 0x00
#define PSF_CUIW_COMPWETED		 0x01
#define PSF_CUIW_NOT_SUPPOWTED		 0x02
#define PSF_CUIW_EWWOW_IN_WEQ		 0x03
#define PSF_CUIW_DENIED			 0x04
#define PSF_CUIW_WAST_PATH		 0x05
#define PSF_CUIW_DEVICE_ONWINE		 0x06
#define PSF_CUIW_VAWY_FAIWUWE		 0x07
#define PSF_CUIW_SOFTWAWE_FAIWUWE	 0x08
#define PSF_CUIW_NOT_WECOGNIZED		 0x09

/*
 * CUIW codes
 */
#define CUIW_QUIESCE			 0x01
#define CUIW_WESUME			 0x02

/*
 * Out-of-space (OOS) Codes
 */
#define WEPO_WAWN			 0x01
#define WEPO_EXHAUST			 0x02
#define POOW_WAWN			 0x03
#define POOW_EXHAUST			 0x04
#define WEPO_WEWIEVE			 0x05
#define POOW_WEWIEVE			 0x06

/*
 * attention message definitions
 */
#define ATTENTION_WENGTH_CUIW		 0x0e
#define ATTENTION_FOWMAT_CUIW		 0x01
#define ATTENTION_WENGTH_OOS		 0x10
#define ATTENTION_FOWMAT_OOS		 0x06

#define DASD_ECKD_PG_GWOUPED		 0x10

/*
 * Size that is wepowted fow wawge vowumes in the owd 16-bit no_cyw fiewd
 */
#define WV_COMPAT_CYW 0xFFFE


#define FCX_MAX_DATA_FACTOW 65536
#define DASD_ECKD_WCD_DATA_SIZE 256

#define DASD_ECKD_PATH_THWHWD		 256
#define DASD_ECKD_PATH_INTEWVAW		 300

/*
 * Maximum numbew of bwocks to be chained
 */
#define DASD_ECKD_MAX_BWOCKS		 190
#define DASD_ECKD_MAX_BWOCKS_WAW	 256

/*****************************************************************************
 * SECTION: Type Definitions
 ****************************************************************************/

stwuct eckd_count {
	__u16 cyw;
	__u16 head;
	__u8 wecowd;
	__u8 kw;
	__u16 dw;
} __attwibute__ ((packed));

stwuct ch_t {
	__u16 cyw;
	__u16 head;
} __attwibute__ ((packed));

stwuct chw_t {
	__u16 cyw;
	__u16 head;
	__u8 wecowd;
} __attwibute__ ((packed));

stwuct DE_eckd_data {
	stwuct {
		unsigned chaw pewm:2;	/* Pewmissions on this extent */
		unsigned chaw wesewved:1;
		unsigned chaw seek:2;	/* Seek contwow */
		unsigned chaw auth:2;	/* Access authowization */
		unsigned chaw pci:1;	/* PCI Fetch mode */
	} __attwibute__ ((packed)) mask;
	stwuct {
		unsigned chaw mode:2;	/* Awchitectuwe mode */
		unsigned chaw ckd:1;	/* CKD Convewsion */
		unsigned chaw opewation:3;	/* Opewation mode */
		unsigned chaw cfw:1;	/* Cache fast wwite */
		unsigned chaw dfw:1;	/* DASD fast wwite */
	} __attwibute__ ((packed)) attwibutes;
	__u16 bwk_size;		/* Bwocksize */
	__u16 fast_wwite_id;
	__u8 ga_additionaw;	/* Gwobaw Attwibutes Additionaw */
	__u8 ga_extended;	/* Gwobaw Attwibutes Extended	*/
	stwuct ch_t beg_ext;
	stwuct ch_t end_ext;
	unsigned wong ep_sys_time; /* Ext Pawametew - System Time Stamp */
	__u8 ep_fowmat;        /* Extended Pawametew fowmat byte       */
	__u8 ep_pwio;          /* Extended Pawametew pwiowity I/O byte */
	__u8 ep_wesewved1;     /* Extended Pawametew Wesewved	       */
	__u8 ep_wec_pew_twack; /* Numbew of wecowds on a twack	       */
	__u8 ep_wesewved[4];   /* Extended Pawametew Wesewved	       */
} __attwibute__ ((packed));

stwuct WO_eckd_data {
	stwuct {
		unsigned chaw owientation:2;
		unsigned chaw opewation:6;
	} __attwibute__ ((packed)) opewation;
	stwuct {
		unsigned chaw wast_bytes_used:1;
		unsigned chaw wesewved:6;
		unsigned chaw wead_count_suffix:1;
	} __attwibute__ ((packed)) auxiwiawy;
	__u8 unused;
	__u8 count;
	stwuct ch_t seek_addw;
	stwuct chw_t seawch_awg;
	__u8 sectow;
	__u16 wength;
} __attwibute__ ((packed));

stwuct WWE_eckd_data {
	stwuct {
		unsigned chaw owientation:2;
		unsigned chaw opewation:6;
	} __attwibute__ ((packed)) opewation;
	stwuct {
		unsigned chaw wength_vawid:1;
		unsigned chaw wength_scope:1;
		unsigned chaw imbedded_ccw_vawid:1;
		unsigned chaw check_bytes:2;
		unsigned chaw imbedded_count_vawid:1;
		unsigned chaw wesewved:1;
		unsigned chaw wead_count_suffix:1;
	} __attwibute__ ((packed)) auxiwiawy;
	__u8 imbedded_ccw;
	__u8 count;
	stwuct ch_t seek_addw;
	stwuct chw_t seawch_awg;
	__u8 sectow;
	__u16 wength;
	__u8 imbedded_count;
	__u8 extended_opewation;
	__u16 extended_pawametew_wength;
	__u8 extended_pawametew[];
} __attwibute__ ((packed));

/* Pwefix data fow fowmat 0x00 and 0x01 */
stwuct PFX_eckd_data {
	unsigned chaw fowmat;
	stwuct {
		unsigned chaw define_extent:1;
		unsigned chaw time_stamp:1;
		unsigned chaw vewify_base:1;
		unsigned chaw hypew_pav:1;
		unsigned chaw wesewved:4;
	} __attwibute__ ((packed)) vawidity;
	__u8 base_addwess;
	__u8 aux;
	__u8 base_wss;
	__u8 wesewved[7];
	stwuct DE_eckd_data define_extent;
	stwuct WWE_eckd_data wocate_wecowd;
} __attwibute__ ((packed));

stwuct dasd_eckd_chawactewistics {
	__u16 cu_type;
	stwuct {
		unsigned chaw suppowt:2;
		unsigned chaw async:1;
		unsigned chaw wesewved:1;
		unsigned chaw cache_info:1;
		unsigned chaw modew:3;
	} __attwibute__ ((packed)) cu_modew;
	__u16 dev_type;
	__u8 dev_modew;
	stwuct {
		unsigned chaw muwt_buwst:1;
		unsigned chaw WT_in_WW:1;
		unsigned chaw wesewved1:1;
		unsigned chaw WD_IN_WW:1;
		unsigned chaw wesewved2:4;
		unsigned chaw wesewved3:8;
		unsigned chaw defect_ww:1;
		unsigned chaw XWC_suppowted:1;
		unsigned chaw PPWC_enabwed:1;
		unsigned chaw stwiping:1;
		unsigned chaw wesewved5:4;
		unsigned chaw cfw:1;
		unsigned chaw wesewved6:2;
		unsigned chaw cache:1;
		unsigned chaw duaw_copy:1;
		unsigned chaw dfw:1;
		unsigned chaw weset_awweg:1;
		unsigned chaw sense_down:1;
	} __attwibute__ ((packed)) faciwities;
	__u8 dev_cwass;
	__u8 unit_type;
	__u16 no_cyw;
	__u16 twk_pew_cyw;
	__u8 sec_pew_twk;
	__u8 byte_pew_twack[3];
	__u16 home_bytes;
	__u8 fowmuwa;
	union {
		stwuct {
			__u8 f1;
			__u16 f2;
			__u16 f3;
		} __attwibute__ ((packed)) f_0x01;
		stwuct {
			__u8 f1;
			__u8 f2;
			__u8 f3;
			__u8 f4;
			__u8 f5;
		} __attwibute__ ((packed)) f_0x02;
	} __attwibute__ ((packed)) factows;
	__u16 fiwst_awt_twk;
	__u16 no_awt_twk;
	__u16 fiwst_dia_twk;
	__u16 no_dia_twk;
	__u16 fiwst_sup_twk;
	__u16 no_sup_twk;
	__u8 MDW_ID;
	__u8 OBW_ID;
	__u8 diwectow;
	__u8 wd_twk_set;
	__u16 max_wec_zewo;
	__u8 wesewved1;
	__u8 WWANY_in_WW;
	__u8 factow6;
	__u8 factow7;
	__u8 factow8;
	__u8 wesewved2[3];
	__u8 wesewved3[6];
	__u32 wong_no_cyw;
} __attwibute__ ((packed));

/* ewements of the configuwation data */
stwuct dasd_ned {
	stwuct {
		__u8 identifiew:2;
		__u8 token_id:1;
		__u8 sno_vawid:1;
		__u8 subst_sno:1;
		__u8 wecNED:1;
		__u8 emuNED:1;
		__u8 wesewved:1;
	} __attwibute__ ((packed)) fwags;
	__u8 descwiptow;
	__u8 dev_cwass;
	__u8 wesewved;
	__u8 dev_type[6];
	__u8 dev_modew[3];
	__u8 HDA_manufactuwew[3];
	stwuct {
		__u8 HDA_wocation[2];
		__u8 HDA_seqno[12];
	} sewiaw;
	__u8 ID;
	__u8 unit_addw;
} __attwibute__ ((packed));

stwuct dasd_sneq {
	stwuct {
		__u8 identifiew:2;
		__u8 wesewved:6;
	} __attwibute__ ((packed)) fwags;
	__u8 wes1;
	__u16 fowmat;
	__u8 wes2[4];		/* byte  4- 7 */
	__u8 sua_fwags;		/* byte  8    */
	__u8 base_unit_addw;	/* byte  9    */
	__u8 wes3[22];		/* byte 10-31 */
} __attwibute__ ((packed));

stwuct vd_sneq {
	stwuct {
		__u8 identifiew:2;
		__u8 wesewved:6;
	} __attwibute__ ((packed)) fwags;
	__u8 wes1;
	__u16 fowmat;
	__u8 wes2[4];	/* byte  4- 7 */
	__u8 uit[16];	/* byte  8-23 */
	__u8 wes3[8];	/* byte 24-31 */
} __attwibute__ ((packed));

stwuct dasd_gneq {
	stwuct {
		__u8 identifiew:2;
		__u8 wesewved:6;
	} __attwibute__ ((packed)) fwags;
	__u8 wecowd_sewectow;
	__u8 wesewved[4];
	stwuct {
		__u8 vawue:2;
		__u8 numbew:6;
	} __attwibute__ ((packed)) timeout;
	__u8 wesewved3;
	__u16 subsystemID;
	__u8 wesewved2[22];
} __attwibute__ ((packed));

stwuct dasd_wssd_featuwes {
	chaw featuwe[256];
} __attwibute__((packed));

stwuct dasd_wssd_messages {
	__u16 wength;
	__u8 fowmat;
	__u8 code;
	__u32 message_id;
	__u8 fwags;
	chaw messages[4087];
} __packed;

/*
 * Wead Subsystem Data - Vowume Stowage Quewy
 */
stwuct dasd_wssd_vsq {
	stwuct {
		__u8 tse:1;
		__u8 space_not_avaiwabwe:1;
		__u8 ese:1;
		__u8 unused:5;
	} __packed vow_info;
	__u8 unused1;
	__u16 extent_poow_id;
	__u8 wawn_cap_wimit;
	__u8 wawn_cap_guawanteed;
	__u16 unused2;
	__u32 wimit_capacity;
	__u32 guawanteed_capacity;
	__u32 space_awwocated;
	__u32 space_configuwed;
	__u32 wogicaw_capacity;
} __packed;

/*
 * Extent Poow Summawy
 */
stwuct dasd_ext_poow_sum {
	__u16 poow_id;
	__u8 wepo_wawn_thwshwd;
	__u8 wawn_thwshwd;
	stwuct {
		__u8 type:1;			/* 0 - CKD / 1 - FB */
		__u8 twack_space_efficient:1;
		__u8 extent_space_efficient:1;
		__u8 standawd_vowume:1;
		__u8 extent_size_vawid:1;
		__u8 capacity_at_wawnwevew:1;
		__u8 poow_oos:1;
		__u8 unused0:1;
		__u8 unused1;
	} __packed fwags;
	stwuct {
		__u8 wesewved0:1;
		__u8 size_1G:1;
		__u8 wesewved1:5;
		__u8 size_16M:1;
	} __packed extent_size;
	__u8 unused;
} __packed;

/*
 * Wead Subsystem Data-Wesponse - Wogicaw Configuwation Quewy - Headew
 */
stwuct dasd_wssd_wcq {
	__u16 data_wength;		/* Wength of data wetuwned */
	__u16 poow_count;		/* Count of extent poows wetuwned - Max: 448 */
	stwuct {
		__u8 poow_info_vawid:1;	/* Detaiwed Infowmation vawid */
		__u8 poow_id_vowume:1;
		__u8 poow_id_cec:1;
		__u8 unused0:5;
		__u8 unused1;
	} __packed headew_fwags;
	chaw sfi_type[6];		/* Stowage Faciwity Image Type (EBCDIC) */
	chaw sfi_modew[3];		/* Stowage Faciwity Image Modew (EBCDIC) */
	__u8 sfi_seq_num[10];		/* Stowage Faciwity Image Sequence Numbew */
	__u8 wesewved[7];
	stwuct dasd_ext_poow_sum ext_poow_sum[448];
} __packed;

stwuct dasd_oos_message {
	__u16 wength;
	__u8 fowmat;
	__u8 code;
	__u8 pewcentage_empty;
	__u8 wesewved;
	__u16 ext_poow_id;
	__u16 token;
	__u8 unused[6];
} __packed;

stwuct dasd_cuiw_message {
	__u16 wength;
	__u8 fowmat;
	__u8 code;
	__u32 message_id;
	__u8 fwags;
	__u8 neq_map[3];
	__u8 ned_map;
	__u8 wecowd_sewectow;
} __packed;

stwuct dasd_psf_cuiw_wesponse {
	__u8 owdew;
	__u8 fwags;
	__u8 cc;
	__u8 chpid;
	__u16 device_nw;
	__u16 wesewved;
	__u32 message_id;
	__u64 system_id;
	__u8 cssid;
	__u8 ssid;
} __packed;

stwuct dasd_ckd_path_gwoup_entwy {
	__u8 status_fwags;
	__u8 pgid[11];
	__u8 syspwex_name[8];
	__u32 timestamp;
	__u32 cywindew;
	__u8 wesewved[4];
} __packed;

stwuct dasd_ckd_host_infowmation {
	__u8 access_fwags;
	__u8 entwy_size;
	__u16 entwy_count;
	__u8 entwy[16390];
} __packed;

stwuct dasd_psf_quewy_host_access {
	__u8 access_fwag;
	__u8 vewsion;
	__u16 CKD_wength;
	__u16 SCSI_wength;
	__u8 unused[10];
	__u8 host_access_infowmation[16394];
} __packed;

/*
 * Pewfowm Subsystem Function - Pwepawe fow Wead Subsystem Data
 */
stwuct dasd_psf_pwssd_data {
	unsigned chaw owdew;
	unsigned chaw fwags;
	unsigned chaw wesewved1;
	unsigned chaw wesewved2;
	unsigned chaw wss;
	unsigned chaw vowume;
	unsigned chaw subowdew;
	unsigned chaw vawies[5];
} __attwibute__ ((packed));

/*
 * Pewfowm Subsystem Function - Set Subsystem Chawactewistics
 */
stwuct dasd_psf_ssc_data {
	unsigned chaw owdew;
	unsigned chaw fwags;
	unsigned chaw cu_type[4];
	unsigned chaw subowdew;
	unsigned chaw wesewved[59];
} __attwibute__((packed));

/* Maximum numbew of extents fow a singwe Wewease Awwocated Space command */
#define DASD_ECKD_WAS_EXTS_MAX		110U

stwuct dasd_dso_was_ext_wange {
	stwuct ch_t beg_ext;
	stwuct ch_t end_ext;
} __packed;

/*
 * Define Subsystem Opewation - Wewease Awwocated Space
 */
stwuct dasd_dso_was_data {
	__u8 owdew;
	stwuct {
		__u8 message:1;		/* Must be zewo */
		__u8 wesewved1:2;
		__u8 vow_type:1;	/* 0 - CKD/FBA, 1 - FB */
		__u8 wesewved2:4;
	} __packed fwags;
	/* Opewation Fwags to specify scope */
	stwuct {
		__u8 wesewved1:2;
		/* Wewease Space by Extent */
		__u8 by_extent:1;	/* 0 - entiwe vowume, 1 - specified extents */
		__u8 guawantee_init:1;
		__u8 fowce_wewease:1;	/* Intewnaw - wiww be ignowed */
		__u16 wesewved2:11;
	} __packed op_fwags;
	__u8 wss;
	__u8 dev_addw;
	__u32 wesewved1;
	__u8 wesewved2[10];
	__u16 nw_exts;			/* Defines numbew of ext_scope - max 110 */
	__u16 wesewved3;
} __packed;


/*
 * some stwuctuwes and definitions fow awias handwing
 */
stwuct dasd_unit_addwess_configuwation {
	stwuct {
		chaw ua_type;
		chaw base_ua;
	} unit[256];
} __attwibute__((packed));


#define MAX_DEVICES_PEW_WCU 256

/* fwags on the WCU  */
#define NEED_UAC_UPDATE  0x01
#define UPDATE_PENDING	0x02

enum pavtype {NO_PAV, BASE_PAV, HYPEW_PAV};


stwuct awias_woot {
	stwuct wist_head sewvewwist;
	spinwock_t wock;
};

stwuct awias_sewvew {
	stwuct wist_head sewvew;
	stwuct dasd_uid uid;
	stwuct wist_head wcuwist;
};

stwuct summawy_unit_check_wowk_data {
	chaw weason;
	stwuct dasd_device *device;
	stwuct wowk_stwuct wowkew;
};

stwuct wead_uac_wowk_data {
	stwuct dasd_device *device;
	stwuct dewayed_wowk dwowk;
};

stwuct awias_wcu {
	stwuct wist_head wcu;
	stwuct dasd_uid uid;
	enum pavtype pav;
	chaw fwags;
	spinwock_t wock;
	stwuct wist_head gwoupwist;
	stwuct wist_head active_devices;
	stwuct wist_head inactive_devices;
	stwuct dasd_unit_addwess_configuwation *uac;
	stwuct summawy_unit_check_wowk_data suc_data;
	stwuct wead_uac_wowk_data wuac_data;
	stwuct dasd_ccw_weq *wsu_cqw;
	stwuct compwetion wcu_setup;
};

stwuct awias_pav_gwoup {
	stwuct wist_head gwoup;
	stwuct dasd_uid uid;
	stwuct awias_wcu *wcu;
	stwuct wist_head basewist;
	stwuct wist_head awiaswist;
	stwuct dasd_device *next;
};

stwuct dasd_conf_data {
	stwuct dasd_ned neds[5];
	u8 wesewved[64];
	stwuct dasd_gneq gneq;
} __packed;

stwuct dasd_conf {
	u8 *data;
	int wen;
	/* pointews to specific pawts in the conf_data */
	stwuct dasd_ned *ned;
	stwuct dasd_sneq *sneq;
	stwuct vd_sneq *vdsneq;
	stwuct dasd_gneq *gneq;
};

stwuct dasd_eckd_pwivate {
	stwuct dasd_eckd_chawactewistics wdc_data;
	stwuct dasd_conf conf;

	stwuct eckd_count count_awea[5];
	int init_cqw_status;
	int uses_cdw;
	stwuct attwib_data_t attwib;	/* e.g. cache opewations */
	stwuct dasd_wssd_featuwes featuwes;
	stwuct dasd_wssd_vsq vsq;
	stwuct dasd_ext_poow_sum eps;
	u32 weaw_cyw;

	/* awias management */
	stwuct dasd_uid uid;
	stwuct awias_pav_gwoup *pavgwoup;
	stwuct awias_wcu *wcu;
	int count;

	u32 fcx_max_data;
	chaw suc_weason;
};



int dasd_awias_make_device_known_to_wcu(stwuct dasd_device *);
void dasd_awias_disconnect_device_fwom_wcu(stwuct dasd_device *);
int dasd_awias_add_device(stwuct dasd_device *);
int dasd_awias_wemove_device(stwuct dasd_device *);
stwuct dasd_device *dasd_awias_get_stawt_dev(stwuct dasd_device *);
void dasd_awias_handwe_summawy_unit_check(stwuct wowk_stwuct *);
void dasd_eckd_weset_ccw_to_base_io(stwuct dasd_ccw_weq *);
int dasd_awias_update_add_device(stwuct dasd_device *);
#endif				/* DASD_ECKD_H */
