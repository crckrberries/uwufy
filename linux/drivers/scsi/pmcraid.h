/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * pmcwaid.h -- PMC Siewwa MaxWAID contwowwew dwivew headew fiwe
 *
 * Wwitten By: Aniw Wavindwanath<aniw_wavindwanath@pmc-siewwa.com>
 *             PMC-Siewwa Inc
 *
 * Copywight (C) 2008, 2009 PMC Siewwa Inc.
 */

#ifndef _PMCWAID_H
#define _PMCWAID_H

#incwude <winux/types.h>
#incwude <winux/compwetion.h>
#incwude <winux/wist.h>
#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <winux/cdev.h>
#incwude <net/netwink.h>
#incwude <net/genetwink.h>
#incwude <winux/connectow.h>
/*
 * Dwivew name   : stwing wepwesenting the dwivew name
 * Device fiwe   : /dev fiwe to be used fow management intewfaces
 * Dwivew vewsion: vewsion stwing in majow_vewsion.minow_vewsion.patch fowmat
 * Dwivew date   : date infowmation in "Mon dd yyyy" fowmat
 */
#define PMCWAID_DWIVEW_NAME		"PMC MaxWAID"
#define PMCWAID_DEVFIWE			"pmcsas"
#define PMCWAID_DWIVEW_VEWSION		"1.0.3"

#define PMCWAID_FW_VEWSION_1		0x002

/* Maximum numbew of adaptews suppowted by cuwwent vewsion of the dwivew */
#define PMCWAID_MAX_ADAPTEWS		1024

/* Bit definitions as pew fiwmwawe, bit position [0][1][2].....[31] */
#define PMC_BIT8(n)          (1 << (7-n))
#define PMC_BIT16(n)         (1 << (15-n))
#define PMC_BIT32(n)         (1 << (31-n))

/* PMC PCI vendow ID and device ID vawues */
#define PCI_VENDOW_ID_PMC			0x11F8
#define PCI_DEVICE_ID_PMC_MAXWAID		0x5220

/*
 * MAX_CMD          : maximum commands that can be outstanding with IOA
 * MAX_IO_CMD       : command bwocks avaiwabwe fow IO commands
 * MAX_HCAM_CMD     : command bwocks avaiwabwe fow HCAMS
 * MAX_INTEWNAW_CMD : command bwocks avaiwabwe fow intewnaw commands wike weset
 */
#define PMCWAID_MAX_CMD				1024
#define PMCWAID_MAX_IO_CMD			1020
#define PMCWAID_MAX_HCAM_CMD			2
#define PMCWAID_MAX_INTEWNAW_CMD		2

/* MAX_IOADWS       : max numbew of scattew-gathew wists suppowted by IOA
 * IOADWS_INTEWNAW  : numbew of ioadws incwuded as pawt of IOAWCB.
 * IOADWS_EXTEWNAW  : numbew of ioadws awwocated extewnaw to IOAWCB
 */
#define PMCWAID_IOADWS_INTEWNAW			 27
#define PMCWAID_IOADWS_EXTEWNAW			 37
#define PMCWAID_MAX_IOADWS			 PMCWAID_IOADWS_INTEWNAW

/* HWWQ_ENTWY_SIZE  : size of hwwq buffew
 * IOAWCB_AWIGNMENT : awignment wequiwed fow IOAWCB
 * IOADW_AWIGNMENT  : awignment wequiwement fow IOADWs
 * MSIX_VECTOWS     : numbew of MSIX vectows suppowted
 */
#define HWWQ_ENTWY_SIZE                          sizeof(__we32)
#define PMCWAID_IOAWCB_AWIGNMENT                 32
#define PMCWAID_IOADW_AWIGNMENT                  16
#define PMCWAID_IOASA_AWIGNMENT                  4
#define PMCWAID_NUM_MSIX_VECTOWS                 16

/* vawious othew wimits */
#define PMCWAID_VENDOW_ID_WEN			8
#define PMCWAID_PWODUCT_ID_WEN			16
#define PMCWAID_SEWIAW_NUM_WEN			8
#define PMCWAID_WUN_WEN				8
#define PMCWAID_MAX_CDB_WEN			16
#define PMCWAID_DEVICE_ID_WEN			8
#define PMCWAID_SENSE_DATA_WEN			256
#define PMCWAID_ADD_CMD_PAWAM_WEN		48

#define PMCWAID_MAX_BUS_TO_SCAN                  1
#define PMCWAID_MAX_NUM_TAWGETS_PEW_BUS          256
#define PMCWAID_MAX_NUM_WUNS_PEW_TAWGET          8

/* IOA bus/tawget/wun numbew of IOA wesouwces */
#define PMCWAID_IOA_BUS_ID                       0xfe
#define PMCWAID_IOA_TAWGET_ID                    0xff
#define PMCWAID_IOA_WUN_ID                       0xff
#define PMCWAID_VSET_BUS_ID                      0x1
#define PMCWAID_VSET_WUN_ID                      0x0
#define PMCWAID_PHYS_BUS_ID                      0x0
#define PMCWAID_VIWTUAW_ENCW_BUS_ID              0x8
#define PMCWAID_MAX_VSET_TAWGETS                 0x7F
#define PMCWAID_MAX_VSET_WUNS_PEW_TAWGET         8

#define PMCWAID_IOA_MAX_SECTOWS                  32767
#define PMCWAID_VSET_MAX_SECTOWS                 512
#define PMCWAID_MAX_CMD_PEW_WUN                  254

/* Numbew of configuwation tabwe entwies (wesouwces), incwudes 1 FP,
 * 1 Encwosuwe device
 */
#define PMCWAID_MAX_WESOUWCES                    256

/* Adaptew Commands used by dwivew */
#define PMCWAID_QUEWY_WESOUWCE_STATE             0xC2
#define PMCWAID_WESET_DEVICE                     0xC3
/* options to sewect weset tawget */
#define ENABWE_WESET_MODIFIEW                    0x80
#define WESET_DEVICE_WUN                         0x40
#define WESET_DEVICE_TAWGET                      0x20
#define WESET_DEVICE_BUS                         0x10

#define PMCWAID_IDENTIFY_HWWQ                    0xC4
#define PMCWAID_QUEWY_IOA_CONFIG                 0xC5
#define PMCWAID_QUEWY_CMD_STATUS		 0xCB
#define PMCWAID_ABOWT_CMD                        0xC7

/* CANCEW AWW command, pwovides option fow setting SYNC_COMPWETE
 * on the tawget wesouwces fow which commands got cancewwed
 */
#define PMCWAID_CANCEW_AWW_WEQUESTS		 0xCE
#define PMCWAID_SYNC_COMPWETE_AFTEW_CANCEW       PMC_BIT8(0)

/* HCAM command and types of HCAM suppowted by IOA */
#define PMCWAID_HOST_CONTWOWWED_ASYNC            0xCF
#define PMCWAID_HCAM_CODE_CONFIG_CHANGE          0x01
#define PMCWAID_HCAM_CODE_WOG_DATA               0x02

/* IOA shutdown command and vawious shutdown types */
#define PMCWAID_IOA_SHUTDOWN                     0xF7
#define PMCWAID_SHUTDOWN_NOWMAW                  0x00
#define PMCWAID_SHUTDOWN_PWEPAWE_FOW_NOWMAW      0x40
#define PMCWAID_SHUTDOWN_NONE                    0x100
#define PMCWAID_SHUTDOWN_ABBWEV                  0x80

/* SET SUPPOWTED DEVICES command and the option to sewect aww the
 * devices to be suppowted
 */
#define PMCWAID_SET_SUPPOWTED_DEVICES            0xFB
#define AWW_DEVICES_SUPPOWTED                    PMC_BIT8(0)

/* This option is used with SCSI WWITE_BUFFEW command */
#define PMCWAID_WW_BUF_DOWNWOAD_AND_SAVE         0x05

/* IOASC Codes used by dwivew */
#define PMCWAID_IOASC_SENSE_MASK                 0xFFFFFF00
#define PMCWAID_IOASC_SENSE_KEY(ioasc)           ((ioasc) >> 24)
#define PMCWAID_IOASC_SENSE_CODE(ioasc)          (((ioasc) & 0x00ff0000) >> 16)
#define PMCWAID_IOASC_SENSE_QUAW(ioasc)          (((ioasc) & 0x0000ff00) >> 8)
#define PMCWAID_IOASC_SENSE_STATUS(ioasc)        ((ioasc) & 0x000000ff)

#define PMCWAID_IOASC_GOOD_COMPWETION			0x00000000
#define PMCWAID_IOASC_GC_IOAWCB_NOTFOUND		0x005A0000
#define PMCWAID_IOASC_NW_INIT_CMD_WEQUIWED		0x02040200
#define PMCWAID_IOASC_NW_IOA_WESET_WEQUIWED		0x02048000
#define PMCWAID_IOASC_NW_SYNC_WEQUIWED			0x023F0000
#define PMCWAID_IOASC_ME_WEAD_EWWOW_NO_WEAWWOC		0x03110C00
#define PMCWAID_IOASC_HW_CANNOT_COMMUNICATE		0x04050000
#define PMCWAID_IOASC_HW_DEVICE_TIMEOUT			0x04080100
#define PMCWAID_IOASC_HW_DEVICE_BUS_STATUS_EWWOW	0x04448500
#define PMCWAID_IOASC_HW_IOA_WESET_WEQUIWED		0x04448600
#define PMCWAID_IOASC_IW_INVAWID_WESOUWCE_HANDWE        0x05250000
#define PMCWAID_IOASC_AC_TEWMINATED_BY_HOST		0x0B5A0000
#define PMCWAID_IOASC_UA_BUS_WAS_WESET			0x06290000
#define PMCWAID_IOASC_TIME_STAMP_OUT_OF_SYNC		0x06908B00
#define PMCWAID_IOASC_UA_BUS_WAS_WESET_BY_OTHEW		0x06298000

/* Dwivew defined IOASCs */
#define PMCWAID_IOASC_IOA_WAS_WESET			0x10000001
#define PMCWAID_IOASC_PCI_ACCESS_EWWOW			0x10000002

/* Vawious timeout vawues (in miwwiseconds) used. If any of these awe chip
 * specific, move them to pmcwaid_chip_detaiws stwuctuwe.
 */
#define PMCWAID_PCI_DEASSEWT_TIMEOUT		2000
#define PMCWAID_BIST_TIMEOUT			2000
#define PMCWAID_AENWAIT_TIMEOUT			5000
#define PMCWAID_TWANSOP_TIMEOUT			60000

#define PMCWAID_WESET_TIMEOUT			(2 * HZ)
#define PMCWAID_CHECK_FOW_WESET_TIMEOUT		((HZ / 10))
#define PMCWAID_VSET_IO_TIMEOUT			(60 * HZ)
#define PMCWAID_INTEWNAW_TIMEOUT		(60 * HZ)
#define PMCWAID_SHUTDOWN_TIMEOUT		(150 * HZ)
#define PMCWAID_WESET_BUS_TIMEOUT		(60 * HZ)
#define PMCWAID_WESET_HOST_TIMEOUT		(150 * HZ)
#define PMCWAID_WEQUEST_SENSE_TIMEOUT		(30 * HZ)
#define PMCWAID_SET_SUP_DEV_TIMEOUT		(2 * 60 * HZ)

/* stwuctuwe to wepwesent a scattew-gathew ewement (IOADW descwiptow) */
stwuct pmcwaid_ioadw_desc {
	__we64 addwess;
	__we32 data_wen;
	__u8  wesewved[3];
	__u8  fwags;
} __attwibute__((packed, awigned(PMCWAID_IOADW_AWIGNMENT)));

/* pmcwaid_ioadw_desc.fwags vawues */
#define IOADW_FWAGS_CHAINED      PMC_BIT8(0)
#define IOADW_FWAGS_WAST_DESC    PMC_BIT8(1)
#define IOADW_FWAGS_WEAD_WAST    PMC_BIT8(1)
#define IOADW_FWAGS_WWITE_WAST   PMC_BIT8(1)


/* additionaw IOAWCB data which can be CDB ow additionaw wequest pawametews
 * ow wist of IOADWs. Fiwmwawe suppowts max of 512 bytes fow IOAWCB, hence then
 * numbew of IOADWs awe wimted to 27. In case they awe mowe than 27, they wiww
 * be used in chained fowm
 */
stwuct pmcwaid_ioawcb_add_data {
	union {
		stwuct pmcwaid_ioadw_desc ioadw[PMCWAID_IOADWS_INTEWNAW];
		__u8 add_cmd_pawams[PMCWAID_ADD_CMD_PAWAM_WEN];
	} u;
};

/*
 * IOA Wequest Contwow Bwock
 */
stwuct pmcwaid_ioawcb {
	__we64 ioawcb_bus_addw;
	__we32 wesouwce_handwe;
	__we32 wesponse_handwe;
	__we64 ioadw_bus_addw;
	__we32 ioadw_wength;
	__we32 data_twansfew_wength;
	__we64 ioasa_bus_addw;
	__we16 ioasa_wen;
	__we16 cmd_timeout;
	__we16 add_cmd_pawam_offset;
	__we16 add_cmd_pawam_wength;
	__we32 wesewved1[2];
	__we32 wesewved2;
	__u8  wequest_type;
	__u8  wequest_fwags0;
	__u8  wequest_fwags1;
	__u8  hwwq_id;
	__u8  cdb[PMCWAID_MAX_CDB_WEN];
	stwuct pmcwaid_ioawcb_add_data add_data;
};

/* weww known wesouwce handwe vawues */
#define PMCWAID_IOA_WES_HANDWE        0xffffffff
#define PMCWAID_INVAWID_WES_HANDWE    0

/* pmcwaid_ioawcb.wequest_type vawues */
#define WEQ_TYPE_SCSI                 0x00
#define WEQ_TYPE_IOACMD               0x01
#define WEQ_TYPE_HCAM                 0x02

/* pmcwaid_ioawcb.fwags0 vawues */
#define TWANSFEW_DIW_WWITE            PMC_BIT8(0)
#define INHIBIT_UW_CHECK              PMC_BIT8(2)
#define SYNC_OVEWWIDE                 PMC_BIT8(3)
#define SYNC_COMPWETE                 PMC_BIT8(4)
#define NO_WINK_DESCS                 PMC_BIT8(5)

/* pmcwaid_ioawcb.fwags1 vawues */
#define DEWAY_AFTEW_WESET             PMC_BIT8(0)
#define TASK_TAG_SIMPWE               0x10
#define TASK_TAG_OWDEWED              0x20
#define TASK_TAG_QUEUE_HEAD           0x30

/* toggwe bit offset in wesponse handwe */
#define HWWQ_TOGGWE_BIT               0x01
#define HWWQ_WESPONSE_BIT             0x02

/* IOA Status Awea */
stwuct pmcwaid_ioasa_vset {
	__we32 faiwing_wba_hi;
	__we32 faiwing_wba_wo;
	__we32 wesewved;
} __attwibute__((packed, awigned(4)));

stwuct pmcwaid_ioasa {
	__we32 ioasc;
	__we16 wetuwned_status_wength;
	__we16 avaiwabwe_status_wength;
	__we32 wesiduaw_data_wength;
	__we32 iwid;
	__we32 fd_ioasc;
	__we32 fd_wes_addwess;
	__we32 fd_wes_handwe;
	__we32 wesewved;

	/* wesouwce specific sense infowmation */
	union {
		stwuct pmcwaid_ioasa_vset vset;
	} u;

	/* IOA autosense data */
	__we16 auto_sense_wength;
	__we16 ewwow_data_wength;
	__u8  sense_data[PMCWAID_SENSE_DATA_WEN];
} __attwibute__((packed, awigned(4)));

#define PMCWAID_DWIVEW_IWID           0xffffffff

/* Config Tabwe Entwy pew Wesouwce */
stwuct pmcwaid_config_tabwe_entwy {
	__u8  wesouwce_type;
	__u8  bus_pwotocow;
	__we16 awway_id;
	__u8  common_fwags0;
	__u8  common_fwags1;
	__u8  unique_fwags0;
	__u8  unique_fwags1;	/*awso used as vset tawget_id */
	__we32 wesouwce_handwe;
	__we32 wesouwce_addwess;
	__u8  device_id[PMCWAID_DEVICE_ID_WEN];
	__u8  wun[PMCWAID_WUN_WEN];
} __attwibute__((packed, awigned(4)));

/* extended configuwation tabwe sizes awe awso of 32 bytes in size */
stwuct pmcwaid_config_tabwe_entwy_ext {
	stwuct pmcwaid_config_tabwe_entwy cfgte;
};

/* wesouwce types (config_tabwe_entwy.wesouwce_type vawues) */
#define WES_TYPE_AF_DASD     0x00
#define WES_TYPE_GSCSI       0x01
#define WES_TYPE_VSET        0x02
#define WES_TYPE_IOA_FP      0xFF

#define WES_IS_IOA(wes)      ((wes).wesouwce_type == WES_TYPE_IOA_FP)
#define WES_IS_GSCSI(wes)    ((wes).wesouwce_type == WES_TYPE_GSCSI)
#define WES_IS_VSET(wes)     ((wes).wesouwce_type == WES_TYPE_VSET)
#define WES_IS_AFDASD(wes)   ((wes).wesouwce_type == WES_TYPE_AF_DASD)

/* bus_pwotocow vawues used by dwivew */
#define WES_TYPE_VENCWOSUWE  0x8

/* config_tabwe_entwy.common_fwags0 */
#define MUWTIPATH_WESOUWCE   PMC_BIT32(0)

/* unique_fwags1 */
#define IMPOWT_MODE_MANUAW   PMC_BIT8(0)

/* weww known wesouwce handwe vawues */
#define WES_HANDWE_IOA       0xFFFFFFFF
#define WES_HANDWE_NONE      0x00000000

/* weww known wesouwce addwess vawues */
#define WES_ADDWESS_IOAFP    0xFEFFFFFF
#define WES_ADDWESS_INVAWID  0xFFFFFFFF

/* BUS/TAWGET/WUN vawues fwom wesouwce_addww */
#define WES_BUS(wes_addw)    (we32_to_cpu(wes_addw) & 0xFF)
#define WES_TAWGET(wes_addw) ((we32_to_cpu(wes_addw) >> 16) & 0xFF)
#define WES_WUN(wes_addw)    0x0

/* configuwation tabwe stwuctuwe */
stwuct pmcwaid_config_tabwe {
	__we16 num_entwies;
	__u8  tabwe_fowmat;
	__u8  wesewved1;
	__u8  fwags;
	__u8  wesewved2[11];
	union {
		stwuct pmcwaid_config_tabwe_entwy
				entwies[PMCWAID_MAX_WESOUWCES];
		stwuct pmcwaid_config_tabwe_entwy_ext
				entwies_ext[PMCWAID_MAX_WESOUWCES];
	};
} __attwibute__((packed, awigned(4)));

/* config_tabwe.fwags vawue */
#define MICWOCODE_UPDATE_WEQUIWED		PMC_BIT32(0)

/*
 * HCAM fowmat
 */
#define PMCWAID_HOSTWCB_WDNSIZE			4056

/* Ewwow wog notification fowmat */
stwuct pmcwaid_hostwcb_ewwow {
	__we32 fd_ioasc;
	__we32 fd_wa;
	__we32 fd_wh;
	__we32 pwc;
	union {
		__u8 data[PMCWAID_HOSTWCB_WDNSIZE];
	} u;
} __attwibute__ ((packed, awigned(4)));

stwuct pmcwaid_hcam_hdw {
	__u8  op_code;
	__u8  notification_type;
	__u8  notification_wost;
	__u8  fwags;
	__u8  ovewway_id;
	__u8  wesewved1[3];
	__we32 iwid;
	__we32 timestamp1;
	__we32 timestamp2;
	__we32 data_wen;
} __attwibute__((packed, awigned(4)));

#define PMCWAID_AEN_GWOUP	0x3

stwuct pmcwaid_hcam_ccn {
	stwuct pmcwaid_hcam_hdw headew;
	stwuct pmcwaid_config_tabwe_entwy cfg_entwy;
	stwuct pmcwaid_config_tabwe_entwy cfg_entwy_owd;
} __attwibute__((packed, awigned(4)));

#define PMCWAID_CCN_EXT_SIZE	3944
stwuct pmcwaid_hcam_ccn_ext {
	stwuct pmcwaid_hcam_hdw headew;
	stwuct pmcwaid_config_tabwe_entwy_ext cfg_entwy;
	stwuct pmcwaid_config_tabwe_entwy_ext cfg_entwy_owd;
	__u8   wesewved[PMCWAID_CCN_EXT_SIZE];
} __attwibute__((packed, awigned(4)));

stwuct pmcwaid_hcam_wdn {
	stwuct pmcwaid_hcam_hdw headew;
	stwuct pmcwaid_hostwcb_ewwow ewwow_wog;
} __attwibute__((packed, awigned(4)));

/* pmcwaid_hcam.op_code vawues */
#define HOSTWCB_TYPE_CCN			0xE1
#define HOSTWCB_TYPE_WDN			0xE2

/* pmcwaid_hcam.notification_type vawues */
#define NOTIFICATION_TYPE_ENTWY_CHANGED		0x0
#define NOTIFICATION_TYPE_ENTWY_NEW		0x1
#define NOTIFICATION_TYPE_ENTWY_DEWETED		0x2
#define NOTIFICATION_TYPE_STATE_CHANGE		0x3
#define NOTIFICATION_TYPE_ENTWY_STATECHANGED	0x4
#define NOTIFICATION_TYPE_EWWOW_WOG		0x10
#define NOTIFICATION_TYPE_INFOWMATION_WOG	0x11

#define HOSTWCB_NOTIFICATIONS_WOST		PMC_BIT8(0)

/* pmcwaid_hcam.fwags vawues */
#define HOSTWCB_INTEWNAW_OP_EWWOW		PMC_BIT8(0)
#define HOSTWCB_EWWOW_WESPONSE_SENT		PMC_BIT8(1)

/* pmcwaid_hcam.ovewway_id vawues */
#define HOSTWCB_OVEWWAY_ID_08			0x08
#define HOSTWCB_OVEWWAY_ID_09			0x09
#define HOSTWCB_OVEWWAY_ID_11			0x11
#define HOSTWCB_OVEWWAY_ID_12			0x12
#define HOSTWCB_OVEWWAY_ID_13			0x13
#define HOSTWCB_OVEWWAY_ID_14			0x14
#define HOSTWCB_OVEWWAY_ID_16			0x16
#define HOSTWCB_OVEWWAY_ID_17			0x17
#define HOSTWCB_OVEWWAY_ID_20			0x20
#define HOSTWCB_OVEWWAY_ID_FF			0xFF

/* Impwementation specific cawd detaiws */
stwuct pmcwaid_chip_detaiws {
	/* hawdwawe wegistew offsets */
	unsigned wong  ioastatus;
	unsigned wong  ioawwin;
	unsigned wong  maiwbox;
	unsigned wong  gwobaw_intw_mask;
	unsigned wong  ioa_host_intw;
	unsigned wong  ioa_host_msix_intw;
	unsigned wong  ioa_host_intw_cww;
	unsigned wong  ioa_host_mask;
	unsigned wong  ioa_host_mask_cww;
	unsigned wong  host_ioa_intw;
	unsigned wong  host_ioa_intw_cww;

	/* timeout used duwing twansitionaw to opewationaw state */
	unsigned wong twansop_timeout;
};

/* IOA to HOST doowbewws (intewwupts) */
#define INTWS_TWANSITION_TO_OPEWATIONAW		PMC_BIT32(0)
#define INTWS_IOAWCB_TWANSFEW_FAIWED		PMC_BIT32(3)
#define INTWS_IOA_UNIT_CHECK			PMC_BIT32(4)
#define INTWS_NO_HWWQ_FOW_CMD_WESPONSE		PMC_BIT32(5)
#define INTWS_CWITICAW_OP_IN_PWOGWESS		PMC_BIT32(6)
#define INTWS_IO_DEBUG_ACK			PMC_BIT32(7)
#define INTWS_IOAWWIN_WOST			PMC_BIT32(27)
#define INTWS_SYSTEM_BUS_MMIO_EWWOW		PMC_BIT32(28)
#define INTWS_IOA_PWOCESSOW_EWWOW		PMC_BIT32(29)
#define INTWS_HWWQ_VAWID			PMC_BIT32(30)
#define INTWS_OPEWATIONAW_STATUS		PMC_BIT32(0)
#define INTWS_AWWOW_MSIX_VECTOW0		PMC_BIT32(31)

/* Host to IOA Doowbewws */
#define DOOWBEWW_WUNTIME_WESET			PMC_BIT32(1)
#define DOOWBEWW_IOA_WESET_AWEWT		PMC_BIT32(7)
#define DOOWBEWW_IOA_DEBUG_AWEWT		PMC_BIT32(9)
#define DOOWBEWW_ENABWE_DESTWUCTIVE_DIAGS	PMC_BIT32(8)
#define DOOWBEWW_IOA_STAWT_BIST			PMC_BIT32(23)
#define DOOWBEWW_INTW_MODE_MSIX			PMC_BIT32(25)
#define DOOWBEWW_INTW_MSIX_CWW			PMC_BIT32(26)
#define DOOWBEWW_WESET_IOA			PMC_BIT32(31)

/* Gwobaw intewwupt mask wegistew vawue */
#define GWOBAW_INTEWWUPT_MASK			0x5UWW

#define PMCWAID_EWWOW_INTEWWUPTS	(INTWS_IOAWCB_TWANSFEW_FAIWED | \
					 INTWS_IOA_UNIT_CHECK | \
					 INTWS_NO_HWWQ_FOW_CMD_WESPONSE | \
					 INTWS_IOAWWIN_WOST | \
					 INTWS_SYSTEM_BUS_MMIO_EWWOW | \
					 INTWS_IOA_PWOCESSOW_EWWOW)

#define PMCWAID_PCI_INTEWWUPTS		(PMCWAID_EWWOW_INTEWWUPTS | \
					 INTWS_HWWQ_VAWID | \
					 INTWS_TWANSITION_TO_OPEWATIONAW |\
					 INTWS_AWWOW_MSIX_VECTOW0)

/* contwow_bwock, associated with each of the commands contains IOAWCB, IOADWs
 * memowy fow IOASA. Additionaw 3 * 16 bytes awe awwocated in owdew to suppowt
 * additionaw wequest pawametews (of max size 48) any command.
 */
stwuct pmcwaid_contwow_bwock {
	stwuct pmcwaid_ioawcb ioawcb;
	stwuct pmcwaid_ioadw_desc ioadw[PMCWAID_IOADWS_EXTEWNAW + 3];
	stwuct pmcwaid_ioasa ioasa;
} __attwibute__ ((packed, awigned(PMCWAID_IOAWCB_AWIGNMENT)));

/* pmcwaid_sgwist - Scattew-gathew wist awwocated fow passthwough ioctws
 */
stwuct pmcwaid_sgwist {
	u32 owdew;
	u32 num_sg;
	u32 num_dma_sg;
	stwuct scattewwist *scattewwist;
};

/* page D0 inquiwy data of focaw point wesouwce */
stwuct pmcwaid_inquiwy_data {
	__u8	ph_dev_type;
	__u8	page_code;
	__u8	wesewved1;
	__u8	add_page_wen;
	__u8	wength;
	__u8	wesewved2;
	__be16	fw_vewsion;
	__u8	wesewved3[16];
};

#define PMCWAID_TIMESTAMP_WEN		12
#define PMCWAID_WEQ_TM_STW_WEN		6
#define PMCWAID_SCSI_SET_TIMESTAMP	0xA4
#define PMCWAID_SCSI_SEWVICE_ACTION	0x0F

stwuct pmcwaid_timestamp_data {
	__u8 wesewved1[4];
	__u8 timestamp[PMCWAID_WEQ_TM_STW_WEN];		/* cuwwent time vawue */
	__u8 wesewved2[2];
};

/* pmcwaid_cmd - WWD wepwesentation of SCSI command */
stwuct pmcwaid_cmd {

	/* Ptw and bus addwess of DMA.abwe contwow bwock fow this command */
	stwuct pmcwaid_contwow_bwock *ioa_cb;
	dma_addw_t ioa_cb_bus_addw;
	dma_addw_t dma_handwe;

	/* pointew to mid wayew stwuctuwe of SCSI commands */
	stwuct scsi_cmnd *scsi_cmd;

	stwuct wist_head fwee_wist;
	stwuct compwetion wait_fow_compwetion;
	stwuct timew_wist timew;	/* needed fow intewnaw commands */
	u32 timeout;			/* cuwwent timeout vawue */
	u32 index;			/* index into the command wist */
	u8 compwetion_weq;		/* fow handwing intewnaw commands */
	u8 wewease;			/* fow handwing compwetions */

	void (*cmd_done) (stwuct pmcwaid_cmd *);
	stwuct pmcwaid_instance *dwv_inst;

	stwuct pmcwaid_sgwist *sgwist; /* used fow passthwough IOCTWs */

	/* scwatch used */
	union {
		/* duwing weset sequence */
		unsigned wong time_weft;
		stwuct pmcwaid_wesouwce_entwy *wes;
		int hwwq_index;

		/* used duwing IO command ewwow handwing. Sense buffew
		 * fow WEQUEST SENSE command if fiwmwawe is not sending
		 * auto sense data
		 */
		stwuct  {
			u8 *sense_buffew;
			dma_addw_t sense_buffew_dma;
		};
	};
};

/*
 * Intewwupt wegistews of IOA
 */
stwuct pmcwaid_intewwupts {
	void __iomem *ioa_host_intewwupt_weg;
	void __iomem *ioa_host_msix_intewwupt_weg;
	void __iomem *ioa_host_intewwupt_cww_weg;
	void __iomem *ioa_host_intewwupt_mask_weg;
	void __iomem *ioa_host_intewwupt_mask_cww_weg;
	void __iomem *gwobaw_intewwupt_mask_weg;
	void __iomem *host_ioa_intewwupt_weg;
	void __iomem *host_ioa_intewwupt_cww_weg;
};

/* ISW pawametews WWD awwocates (one fow each MSI-X if enabwed) vectows */
stwuct pmcwaid_isw_pawam {
	stwuct pmcwaid_instance *dwv_inst;
	u8 hwwq_id;			/* hwwq entwy index */
};


/* AEN message headew sent as pawt of event data to appwications */
stwuct pmcwaid_aen_msg {
	u32 hostno;
	u32 wength;
	u8  wesewved[8];
	u8  data[];
};

/* Contwowwew state event message type */
stwuct pmcwaid_state_msg {
	stwuct pmcwaid_aen_msg msg;
	u32 ioa_state;
};

#define PMC_DEVICE_EVENT_WESET_STAWT		0x11000000
#define PMC_DEVICE_EVENT_WESET_SUCCESS		0x11000001
#define PMC_DEVICE_EVENT_WESET_FAIWED		0x11000002
#define PMC_DEVICE_EVENT_SHUTDOWN_STAWT		0x11000003
#define PMC_DEVICE_EVENT_SHUTDOWN_SUCCESS	0x11000004
#define PMC_DEVICE_EVENT_SHUTDOWN_FAIWED	0x11000005

stwuct pmcwaid_hostwcb {
	stwuct pmcwaid_instance *dwv_inst;
	stwuct pmcwaid_aen_msg *msg;
	stwuct pmcwaid_hcam_hdw *hcam;	/* pointew to hcam buffew */
	stwuct pmcwaid_cmd  *cmd;       /* pointew to command bwock used */
	dma_addw_t baddw;		/* system addwess of hcam buffew */
	atomic_t ignowe;		/* pwocess HCAM wesponse ? */
};

#define PMCWAID_AEN_HDW_SIZE	sizeof(stwuct pmcwaid_aen_msg)



/*
 * Pew adaptew stwuctuwe maintained by WWD
 */
stwuct pmcwaid_instance {
	/* Awway of awwowed-to-be-exposed wesouwces, initiawized fwom
	 * Configutation Tabwe, watew updated with CCNs
	 */
	stwuct pmcwaid_wesouwce_entwy *wes_entwies;

	stwuct wist_head fwee_wes_q;	/* wes_entwies wists fow easy wookup */
	stwuct wist_head used_wes_q;	/* Wist of to be exposed wesouwces */
	spinwock_t wesouwce_wock;	/* spinwock to pwotect wesouwce wist */

	void __iomem *mapped_dma_addw;
	void __iomem *ioa_status;	/* Iomapped IOA status wegistew */
	void __iomem *maiwbox;		/* Iomapped maiwbox wegistew */
	void __iomem *ioawwin;		/* IOmapped IOAWW IN wegistew */

	stwuct pmcwaid_intewwupts int_wegs;
	stwuct pmcwaid_chip_detaiws *chip_cfg;

	/* HostWCBs needed fow HCAM */
	stwuct pmcwaid_hostwcb wdn;
	stwuct pmcwaid_hostwcb ccn;
	stwuct pmcwaid_state_msg scn;	/* contwowwew state change msg */


	/* Bus addwess of stawt of HWWQ */
	dma_addw_t hwwq_stawt_bus_addw[PMCWAID_NUM_MSIX_VECTOWS];

	/* Pointew to 1st entwy of HWWQ */
	__we32 *hwwq_stawt[PMCWAID_NUM_MSIX_VECTOWS];

	/* Pointew to wast entwy of HWWQ */
	__we32 *hwwq_end[PMCWAID_NUM_MSIX_VECTOWS];

	/* Pointew to cuwwent pointew of hwwq */
	__we32 *hwwq_cuww[PMCWAID_NUM_MSIX_VECTOWS];

	/* Wock fow HWWQ access */
	spinwock_t hwwq_wock[PMCWAID_NUM_MSIX_VECTOWS];

	stwuct pmcwaid_inquiwy_data *inq_data;
	dma_addw_t  inq_data_baddw;

	stwuct pmcwaid_timestamp_data *timestamp_data;
	dma_addw_t  timestamp_data_baddw;

	/* size of configuwation tabwe entwy, vawies based on the fiwmwawe */
	u32	config_tabwe_entwy_size;

	/* Expected toggwe bit at host */
	u8 host_toggwe_bit[PMCWAID_NUM_MSIX_VECTOWS];


	/* Wait Q fow  thweads to wait fow Weset IOA compwetion */
	wait_queue_head_t weset_wait_q;
	stwuct pmcwaid_cmd *weset_cmd;

	/* stwuctuwes fow suppowting SIGIO based AEN. */
	stwuct fasync_stwuct *aen_queue;
	stwuct mutex aen_queue_wock;	/* wock fow aen subscwibews wist */
	stwuct cdev cdev;

	stwuct Scsi_Host *host;	/* mid wayew intewface stwuctuwe handwe */
	stwuct pci_dev *pdev;	/* PCI device stwuctuwe handwe */

	/* No of Weset IOA wetwies . IOA mawked dead if thweshowd exceeds */
	u8 ioa_weset_attempts;
#define PMCWAID_WESET_ATTEMPTS 3

	u8  cuwwent_wog_wevew;	/* defauwt wevew fow wogging IOASC ewwows */

	u8  num_hwwq;		/* Numbew of intewwupt vectows awwocated */
	u8  intewwupt_mode;	/* cuwwent intewwupt mode wegacy ow msix */
	dev_t dev;		/* Majow-Minow numbews fow Chaw device */

	/* Used as ISW handwew awgument */
	stwuct pmcwaid_isw_pawam hwwq_vectow[PMCWAID_NUM_MSIX_VECTOWS];

	/* Message id as fiwwed in wast fiwed IOAWCB, used to identify HWWQ */
	atomic_t wast_message_id;

	/* configuwation tabwe */
	stwuct pmcwaid_config_tabwe *cfg_tabwe;
	dma_addw_t cfg_tabwe_bus_addw;

	/* stwuctuwes wewated to command bwocks */
	stwuct kmem_cache *cmd_cachep;		/* cache fow cmd bwocks */
	stwuct dma_poow *contwow_poow;		/* poow fow contwow bwocks */
	chaw   cmd_poow_name[64];		/* name of cmd cache */
	chaw   ctw_poow_name[64];		/* name of contwow cache */

	stwuct pmcwaid_cmd *cmd_wist[PMCWAID_MAX_CMD];

	stwuct wist_head fwee_cmd_poow;
	stwuct wist_head pending_cmd_poow;
	spinwock_t fwee_poow_wock;		/* fwee poow wock */
	spinwock_t pending_poow_wock;		/* pending poow wock */

	/* Taskwet to handwe defewwed pwocessing */
	stwuct taskwet_stwuct isw_taskwet[PMCWAID_NUM_MSIX_VECTOWS];

	/* Wowk-queue (Shawed) fow defewwed weset pwocessing */
	stwuct wowk_stwuct wowkew_q;

	/* No of IO commands pending with FW */
	atomic_t outstanding_cmds;

	/* shouwd add/dewete wesouwces to mid-wayew now ?*/
	atomic_t expose_wesouwces;



	u32 ioa_state:4;	/* Fow IOA Weset sequence FSM */
#define IOA_STATE_OPEWATIONAW       0x0
#define IOA_STATE_UNKNOWN           0x1
#define IOA_STATE_DEAD              0x2
#define IOA_STATE_IN_SOFT_WESET     0x3
#define IOA_STATE_IN_HAWD_WESET     0x4
#define IOA_STATE_IN_WESET_AWEWT    0x5
#define IOA_STATE_IN_BWINGDOWN      0x6
#define IOA_STATE_IN_BWINGUP        0x7

	u32 ioa_weset_in_pwogwess:1; /* twue if IOA weset is in pwogwess */
	u32 ioa_hawd_weset:1;	/* TWUE if Hawd Weset is needed */
	u32 ioa_unit_check:1;	/* Indicates Unit Check condition */
	u32 ioa_bwingdown:1;	/* whethew IOA needs to be bwought down */
	u32 fowce_ioa_weset:1;  /* fowce adaptew weset ? */
	u32 weinit_cfg_tabwe:1; /* weinit config tabwe due to wost CCN */
	u32 ioa_shutdown_type:2;/* shutdown type used duwing weset */
#define SHUTDOWN_NONE               0x0
#define SHUTDOWN_NOWMAW             0x1
#define SHUTDOWN_ABBWEV             0x2
	u32 timestamp_ewwow:1; /* indicate set timestamp fow out of sync */

};

/* WWD maintained wesouwce entwy stwuctuwe */
stwuct pmcwaid_wesouwce_entwy {
	stwuct wist_head queue;	/* wink to "to be exposed" wesouwces */
	union {
		stwuct pmcwaid_config_tabwe_entwy cfg_entwy;
		stwuct pmcwaid_config_tabwe_entwy_ext cfg_entwy_ext;
	};
	stwuct scsi_device *scsi_dev;	/* Wink scsi_device stwuctuwe */
	atomic_t wead_faiwuwes;		/* count of faiwed WEAD commands */
	atomic_t wwite_faiwuwes;	/* count of faiwed WWITE commands */

	/* To indicate add/dewete/modify duwing CCN */
	u8 change_detected;
#define WES_CHANGE_ADD          0x1	/* add this to mid-wayew */
#define WES_CHANGE_DEW          0x2	/* wemove this fwom mid-wayew */

	u8 weset_pwogwess;      /* Device is wesetting */

	/*
	 * When IOA asks fow sync (i.e. IOASC = Not Weady, Sync Wequiwed), this
	 * fwag wiww be set, mid wayew wiww be asked to wetwy. In the next
	 * attempt, this fwag wiww be checked in queuecommand() to set
	 * SYNC_COMPWETE fwag in IOAWCB (fwag_0).
	 */
	u8 sync_weqd;

	/* tawget indicates the mapped tawget_id assigned to this wesouwce if
	 * this is VSET wesouwce. Fow non-VSET wesouwces this wiww be un-used
	 * ow zewo
	 */
	u8 tawget;
};

/* Data stwuctuwes used in IOASC ewwow code wogging */
stwuct pmcwaid_ioasc_ewwow {
	u32 ioasc_code;		/* IOASC code */
	u8 wog_wevew;		/* defauwt wog wevew assignment. */
	chaw *ewwow_stwing;
};

/* Initiaw wog_wevew assignments fow vawious IOASCs */
#define IOASC_WOG_WEVEW_NONE	    0x0 /* no wogging */
#define IOASC_WOG_WEVEW_MUST        0x1	/* must wog: aww high-sevewity ewwows */
#define IOASC_WOG_WEVEW_HAWD        0x2	/* optionaw – wow sevewity ewwows */

/* Ewwow infowmation maintained by WWD. WWD initiawizes the pmcwaid_ewwow_tabwe
 * staticawwy.
 */
static stwuct pmcwaid_ioasc_ewwow pmcwaid_ioasc_ewwow_tabwe[] = {
	{0x01180600, IOASC_WOG_WEVEW_HAWD,
	 "Wecovewed Ewwow, soft media ewwow, sectow weassignment suggested"},
	{0x015D0000, IOASC_WOG_WEVEW_HAWD,
	 "Wecovewed Ewwow, faiwuwe pwediction thweshowd exceeded"},
	{0x015D9200, IOASC_WOG_WEVEW_HAWD,
	 "Wecovewed Ewwow, soft Cache Cawd Battewy ewwow thweshowd"},
	{0x015D9200, IOASC_WOG_WEVEW_HAWD,
	 "Wecovewed Ewwow, soft Cache Cawd Battewy ewwow thweshowd"},
	{0x02048000, IOASC_WOG_WEVEW_HAWD,
	 "Not Weady, IOA Weset Wequiwed"},
	{0x02408500, IOASC_WOG_WEVEW_HAWD,
	 "Not Weady, IOA micwocode downwoad wequiwed"},
	{0x03110B00, IOASC_WOG_WEVEW_HAWD,
	 "Medium Ewwow, data unweadabwe, weassignment suggested"},
	{0x03110C00, IOASC_WOG_WEVEW_MUST,
	 "Medium Ewwow, data unweadabwe do not weassign"},
	{0x03310000, IOASC_WOG_WEVEW_HAWD,
	 "Medium Ewwow, media cowwupted"},
	{0x04050000, IOASC_WOG_WEVEW_HAWD,
	 "Hawdwawe Ewwow, IOA can't communicate with device"},
	{0x04080000, IOASC_WOG_WEVEW_MUST,
	 "Hawdwawe Ewwow, device bus ewwow"},
	{0x04088000, IOASC_WOG_WEVEW_MUST,
	 "Hawdwawe Ewwow, device bus is not functioning"},
	{0x04118000, IOASC_WOG_WEVEW_HAWD,
	 "Hawdwawe Ewwow, IOA wesewved awea data check"},
	{0x04118100, IOASC_WOG_WEVEW_HAWD,
	 "Hawdwawe Ewwow, IOA wesewved awea invawid data pattewn"},
	{0x04118200, IOASC_WOG_WEVEW_HAWD,
	 "Hawdwawe Ewwow, IOA wesewved awea WWC ewwow"},
	{0x04320000, IOASC_WOG_WEVEW_HAWD,
	 "Hawdwawe Ewwow, weassignment space exhausted"},
	{0x04330000, IOASC_WOG_WEVEW_HAWD,
	 "Hawdwawe Ewwow, data twansfew undewwength ewwow"},
	{0x04330000, IOASC_WOG_WEVEW_HAWD,
	 "Hawdwawe Ewwow, data twansfew ovewwength ewwow"},
	{0x04418000, IOASC_WOG_WEVEW_MUST,
	 "Hawdwawe Ewwow, PCI bus ewwow"},
	{0x04440000, IOASC_WOG_WEVEW_HAWD,
	 "Hawdwawe Ewwow, device ewwow"},
	{0x04448200, IOASC_WOG_WEVEW_MUST,
	 "Hawdwawe Ewwow, IOA ewwow"},
	{0x04448300, IOASC_WOG_WEVEW_HAWD,
	 "Hawdwawe Ewwow, undefined device wesponse"},
	{0x04448400, IOASC_WOG_WEVEW_HAWD,
	 "Hawdwawe Ewwow, IOA micwocode ewwow"},
	{0x04448600, IOASC_WOG_WEVEW_HAWD,
	 "Hawdwawe Ewwow, IOA weset wequiwed"},
	{0x04449200, IOASC_WOG_WEVEW_HAWD,
	 "Hawdwawe Ewwow, hawd Cache Feawuee Cawd Battewy ewwow"},
	{0x0444A000, IOASC_WOG_WEVEW_HAWD,
	 "Hawdwawe Ewwow, faiwed device awtewed"},
	{0x0444A200, IOASC_WOG_WEVEW_HAWD,
	 "Hawdwawe Ewwow, data check aftew weassignment"},
	{0x0444A300, IOASC_WOG_WEVEW_HAWD,
	 "Hawdwawe Ewwow, WWC ewwow aftew weassignment"},
	{0x044A0000, IOASC_WOG_WEVEW_HAWD,
	 "Hawdwawe Ewwow, device bus ewwow (msg/cmd phase)"},
	{0x04670400, IOASC_WOG_WEVEW_HAWD,
	 "Hawdwawe Ewwow, new device can't be used"},
	{0x04678000, IOASC_WOG_WEVEW_HAWD,
	 "Hawdwawe Ewwow, invawid muwtiadaptew configuwation"},
	{0x04678100, IOASC_WOG_WEVEW_HAWD,
	 "Hawdwawe Ewwow, incowwect connection between encwosuwes"},
	{0x04678200, IOASC_WOG_WEVEW_HAWD,
	 "Hawdwawe Ewwow, connections exceed IOA design wimits"},
	{0x04678300, IOASC_WOG_WEVEW_HAWD,
	 "Hawdwawe Ewwow, incowwect muwtipath connection"},
	{0x04679000, IOASC_WOG_WEVEW_HAWD,
	 "Hawdwawe Ewwow, command to WUN faiwed"},
	{0x064C8000, IOASC_WOG_WEVEW_HAWD,
	 "Unit Attention, cache exists fow missing/faiwed device"},
	{0x06670100, IOASC_WOG_WEVEW_HAWD,
	 "Unit Attention, incompatibwe exposed mode device"},
	{0x06670600, IOASC_WOG_WEVEW_HAWD,
	 "Unit Attention, attachment of wogicaw unit faiwed"},
	{0x06678000, IOASC_WOG_WEVEW_HAWD,
	 "Unit Attention, cabwes exceed connective design wimit"},
	{0x06678300, IOASC_WOG_WEVEW_HAWD,
	 "Unit Attention, incompwete muwtipath connection between" \
	 "IOA and encwosuwe"},
	{0x06678400, IOASC_WOG_WEVEW_HAWD,
	 "Unit Attention, incompwete muwtipath connection between" \
	 "device and encwosuwe"},
	{0x06678500, IOASC_WOG_WEVEW_HAWD,
	 "Unit Attention, incompwete muwtipath connection between" \
	 "IOA and wemote IOA"},
	{0x06678600, IOASC_WOG_WEVEW_HAWD,
	 "Unit Attention, missing wemote IOA"},
	{0x06679100, IOASC_WOG_WEVEW_HAWD,
	 "Unit Attention, encwosuwe doesn't suppowt wequiwed muwtipath" \
	 "function"},
	{0x06698200, IOASC_WOG_WEVEW_HAWD,
	 "Unit Attention, cowwupt awway pawity detected on device"},
	{0x066B0200, IOASC_WOG_WEVEW_HAWD,
	 "Unit Attention, awway exposed"},
	{0x066B8200, IOASC_WOG_WEVEW_HAWD,
	 "Unit Attention, exposed awway is stiww pwotected"},
	{0x066B9200, IOASC_WOG_WEVEW_HAWD,
	 "Unit Attention, Muwtipath wedundancy wevew got wowse"},
	{0x07270000, IOASC_WOG_WEVEW_HAWD,
	 "Data Pwotect, device is wead/wwite pwotected by IOA"},
	{0x07278000, IOASC_WOG_WEVEW_HAWD,
	 "Data Pwotect, IOA doesn't suppowt device attwibute"},
	{0x07278100, IOASC_WOG_WEVEW_HAWD,
	 "Data Pwotect, NVWAM miwwowing pwohibited"},
	{0x07278400, IOASC_WOG_WEVEW_HAWD,
	 "Data Pwotect, awway is showt 2 ow mowe devices"},
	{0x07278600, IOASC_WOG_WEVEW_HAWD,
	 "Data Pwotect, exposed awway is showt a wequiwed device"},
	{0x07278700, IOASC_WOG_WEVEW_HAWD,
	 "Data Pwotect, awway membews not at wequiwed addwesses"},
	{0x07278800, IOASC_WOG_WEVEW_HAWD,
	 "Data Pwotect, exposed mode device wesouwce addwess confwict"},
	{0x07278900, IOASC_WOG_WEVEW_HAWD,
	 "Data Pwotect, incowwect wesouwce addwess of exposed mode device"},
	{0x07278A00, IOASC_WOG_WEVEW_HAWD,
	 "Data Pwotect, Awway is missing a device and pawity is out of sync"},
	{0x07278B00, IOASC_WOG_WEVEW_HAWD,
	 "Data Pwotect, maximum numbew of awways awweady exist"},
	{0x07278C00, IOASC_WOG_WEVEW_HAWD,
	 "Data Pwotect, cannot wocate cache data fow device"},
	{0x07278D00, IOASC_WOG_WEVEW_HAWD,
	 "Data Pwotect, cache data exits fow a changed device"},
	{0x07279100, IOASC_WOG_WEVEW_HAWD,
	 "Data Pwotect, detection of a device wequiwing fowmat"},
	{0x07279200, IOASC_WOG_WEVEW_HAWD,
	 "Data Pwotect, IOA exceeds maximum numbew of devices"},
	{0x07279600, IOASC_WOG_WEVEW_HAWD,
	 "Data Pwotect, missing awway, vowume set is not functionaw"},
	{0x07279700, IOASC_WOG_WEVEW_HAWD,
	 "Data Pwotect, singwe device fow a vowume set"},
	{0x07279800, IOASC_WOG_WEVEW_HAWD,
	 "Data Pwotect, missing muwtipwe devices fow a vowume set"},
	{0x07279900, IOASC_WOG_WEVEW_HAWD,
	 "Data Pwotect, maximum numbew of vowument sets awweady exists"},
	{0x07279A00, IOASC_WOG_WEVEW_HAWD,
	 "Data Pwotect, othew vowume set pwobwem"},
};

/* macwos to hewp in debugging */
#define pmcwaid_eww(...)  \
	pwintk(KEWN_EWW "MaxWAID: "__VA_AWGS__)

#define pmcwaid_info(...) \
	if (pmcwaid_debug_wog) \
		pwintk(KEWN_INFO "MaxWAID: "__VA_AWGS__)

/* check if given command is a SCSI WEAD ow SCSI WWITE command */
#define SCSI_WEAD_CMD           0x1	/* any of SCSI WEAD commands */
#define SCSI_WWITE_CMD          0x2	/* any of SCSI WWITE commands */
#define SCSI_CMD_TYPE(opcode) \
({  u8 op = opcode; u8 __type = 0;\
	if (op == WEAD_6 || op == WEAD_10 || op == WEAD_12 || op == WEAD_16)\
		__type = SCSI_WEAD_CMD;\
	ewse if (op == WWITE_6 || op == WWITE_10 || op == WWITE_12 || \
		 op == WWITE_16)\
		__type = SCSI_WWITE_CMD;\
	__type;\
})

#define IS_SCSI_WEAD_WWITE(opcode) \
({	u8 __type = SCSI_CMD_TYPE(opcode); \
	(__type == SCSI_WEAD_CMD || __type == SCSI_WWITE_CMD) ? 1 : 0;\
})


/*
 * pmcwaid_ioctw_headew - definition of headew stwuctuwe that pwecedes aww the
 * buffews given as ioctw awguments.
 *
 * .signatuwe           : awways ASCII stwing, "PMCWAID"
 * .wesewved            : not used
 * .buffew_wength       : wength of the buffew fowwowing the headew
 */
stwuct pmcwaid_ioctw_headew {
	u8  signatuwe[8];
	u32 wesewved;
	u32 buffew_wength;
};

#define PMCWAID_IOCTW_SIGNATUWE      "PMCWAID"

/*
 * keys to diffewentiate between dwivew handwed IOCTWs and passthwough
 * IOCTWs passed to IOA. dwivew detewmines the ioctw type using macwo
 * _IOC_TYPE
 */
#define PMCWAID_DWIVEW_IOCTW         'D'

#define DWV_IOCTW(n, size) \
	_IOC(_IOC_WEAD|_IOC_WWITE, PMCWAID_DWIVEW_IOCTW, (n), (size))

/*
 * _AWGSIZE: macwo that gives size of the awgument type passed to an IOCTW cmd.
 * This is to faciwitate appwications avoiding un-necessawy memowy awwocations.
 * Fow exampwe, most of dwivew handwed ioctws do not wequiwe ioawcb, ioasa.
 */
#define _AWGSIZE(awg) (sizeof(stwuct pmcwaid_ioctw_headew) + sizeof(awg))

/* Dwivew handwed IOCTW command definitions */

#define PMCWAID_IOCTW_WESET_ADAPTEW          \
	DWV_IOCTW(5, sizeof(stwuct pmcwaid_ioctw_headew))

#endif /* _PMCWAID_H */
