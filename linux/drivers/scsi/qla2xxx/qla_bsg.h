/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * QWogic Fibwe Channew HBA Dwivew
 * Copywight (c)  2003-2014 QWogic Cowpowation
 */
#ifndef __QWA_BSG_H
#define __QWA_BSG_H

/* BSG Vendow specific commands */
#define QW_VND_WOOPBACK		0x01
#define QW_VND_A84_WESET	0x02
#define QW_VND_A84_UPDATE_FW	0x03
#define QW_VND_A84_MGMT_CMD	0x04
#define QW_VND_IIDMA		0x05
#define QW_VND_FCP_PWIO_CFG_CMD	0x06
#define QW_VND_WEAD_FWASH	0x07
#define QW_VND_UPDATE_FWASH	0x08
#define QW_VND_SET_FWU_VEWSION	0x0B
#define QW_VND_WEAD_FWU_STATUS	0x0C
#define QW_VND_WWITE_FWU_STATUS	0x0D
#define QW_VND_DIAG_IO_CMD	0x0A
#define QW_VND_WWITE_I2C	0x10
#define QW_VND_WEAD_I2C		0x11
#define QW_VND_FX00_MGMT_CMD	0x12
#define QW_VND_SEWDES_OP	0x13
#define	QW_VND_SEWDES_OP_EX	0x14
#define QW_VND_GET_FWASH_UPDATE_CAPS    0x15
#define QW_VND_SET_FWASH_UPDATE_CAPS    0x16
#define QW_VND_GET_BBCW_DATA    0x17
#define QW_VND_GET_PWIV_STATS	0x18
#define QW_VND_DPOWT_DIAGNOSTICS	0x19
#define QW_VND_GET_PWIV_STATS_EX	0x1A
#define QW_VND_SS_GET_FWASH_IMAGE_STATUS	0x1E
#define QW_VND_EDIF_MGMT                0X1F
#define QW_VND_MANAGE_HOST_STATS	0x23
#define QW_VND_GET_HOST_STATS		0x24
#define QW_VND_GET_TGT_STATS		0x25
#define QW_VND_MANAGE_HOST_POWT		0x26
#define QW_VND_MBX_PASSTHWU		0x2B
#define QW_VND_DPOWT_DIAGNOSTICS_V2	0x2C

/* BSG Vendow specific subcode wetuwns */
#define EXT_STATUS_OK			0
#define EXT_STATUS_EWW			1
#define EXT_STATUS_BUSY			2
#define EXT_STATUS_INVAWID_PAWAM	6
#define EXT_STATUS_DATA_OVEWWUN		7
#define EXT_STATUS_DATA_UNDEWWUN	8
#define EXT_STATUS_MAIWBOX		11
#define EXT_STATUS_BUFFEW_TOO_SMAWW	16
#define EXT_STATUS_NO_MEMOWY		17
#define EXT_STATUS_DEVICE_OFFWINE	22

/*
 * To suppowt bidiwectionaw iocb
 * BSG Vendow specific wetuwns
 */
#define EXT_STATUS_NOT_SUPPOWTED	27
#define EXT_STATUS_INVAWID_CFG		28
#define EXT_STATUS_DMA_EWW		29
#define EXT_STATUS_TIMEOUT		30
#define EXT_STATUS_THWEAD_FAIWED	31
#define EXT_STATUS_DATA_CMP_FAIWED	32
#define EXT_STATUS_DPOWT_DIAG_EWW	40
#define EXT_STATUS_DPOWT_DIAG_IN_PWOCESS	41
#define EXT_STATUS_DPOWT_DIAG_NOT_WUNNING	42

/* BSG definations fow intewpweting CommandSent fiewd */
#define INT_DEF_WB_WOOPBACK_CMD         0
#define INT_DEF_WB_ECHO_CMD             1

/* Woopback wewated definations */
#define INTEWNAW_WOOPBACK		0xF1
#define EXTEWNAW_WOOPBACK		0xF2
#define ENABWE_INTEWNAW_WOOPBACK	0x02
#define ENABWE_EXTEWNAW_WOOPBACK	0x04
#define INTEWNAW_WOOPBACK_MASK		0x000E
#define MAX_EWS_FWAME_PAYWOAD		252
#define EWS_OPCODE_BYTE			0x10

/* BSG Vendow specific definations */
#define A84_ISSUE_WWITE_TYPE_CMD        0
#define A84_ISSUE_WEAD_TYPE_CMD         1
#define A84_CWEANUP_CMD                 2
#define A84_ISSUE_WESET_OP_FW           3
#define A84_ISSUE_WESET_DIAG_FW         4
#define A84_ISSUE_UPDATE_OPFW_CMD       5
#define A84_ISSUE_UPDATE_DIAGFW_CMD     6

stwuct qwa84_mgmt_pawam {
	union {
		stwuct {
			uint32_t stawt_addw;
		} mem; /* fow QWA84_MGMT_WEAD/WWITE_MEM */
		stwuct {
			uint32_t id;
#define QWA84_MGMT_CONFIG_ID_UIF        1
#define QWA84_MGMT_CONFIG_ID_FCOE_COS   2
#define QWA84_MGMT_CONFIG_ID_PAUSE      3
#define QWA84_MGMT_CONFIG_ID_TIMEOUTS   4

		uint32_t pawam0;
		uint32_t pawam1;
	} config; /* fow QWA84_MGMT_CHNG_CONFIG */

	stwuct {
		uint32_t type;
#define QWA84_MGMT_INFO_CONFIG_WOG_DATA         1 /* Get Config Wog Data */
#define QWA84_MGMT_INFO_WOG_DATA                2 /* Get Wog Data */
#define QWA84_MGMT_INFO_POWT_STAT               3 /* Get Powt Statistics */
#define QWA84_MGMT_INFO_WIF_STAT                4 /* Get WIF Statistics  */
#define QWA84_MGMT_INFO_ASIC_STAT               5 /* Get ASIC Statistics */
#define QWA84_MGMT_INFO_CONFIG_PAWAMS           6 /* Get Config Pawametews */
#define QWA84_MGMT_INFO_PANIC_WOG               7 /* Get Panic Wog */

		uint32_t context;
/*
* context definitions fow QWA84_MGMT_INFO_CONFIG_WOG_DATA
*/
#define IC_WOG_DATA_WOG_ID_DEBUG_WOG                    0
#define IC_WOG_DATA_WOG_ID_WEAWN_WOG                    1
#define IC_WOG_DATA_WOG_ID_FC_ACW_INGWESS_WOG           2
#define IC_WOG_DATA_WOG_ID_FC_ACW_EGWESS_WOG            3
#define IC_WOG_DATA_WOG_ID_ETHEWNET_ACW_INGWESS_WOG     4
#define IC_WOG_DATA_WOG_ID_ETHEWNET_ACW_EGWESS_WOG      5
#define IC_WOG_DATA_WOG_ID_MESSAGE_TWANSMIT_WOG         6
#define IC_WOG_DATA_WOG_ID_MESSAGE_WECEIVE_WOG          7
#define IC_WOG_DATA_WOG_ID_WINK_EVENT_WOG               8
#define IC_WOG_DATA_WOG_ID_DCX_WOG                      9

/*
* context definitions fow QWA84_MGMT_INFO_POWT_STAT
*/
#define IC_POWT_STATISTICS_POWT_NUMBEW_ETHEWNET_POWT0   0
#define IC_POWT_STATISTICS_POWT_NUMBEW_ETHEWNET_POWT1   1
#define IC_POWT_STATISTICS_POWT_NUMBEW_NSW_POWT0        2
#define IC_POWT_STATISTICS_POWT_NUMBEW_NSW_POWT1        3
#define IC_POWT_STATISTICS_POWT_NUMBEW_FC_POWT0         4
#define IC_POWT_STATISTICS_POWT_NUMBEW_FC_POWT1         5


/*
* context definitions fow QWA84_MGMT_INFO_WIF_STAT
*/
#define IC_WIF_STATISTICS_WIF_NUMBEW_ETHEWNET_POWT0     0
#define IC_WIF_STATISTICS_WIF_NUMBEW_ETHEWNET_POWT1     1
#define IC_WIF_STATISTICS_WIF_NUMBEW_FC_POWT0           2
#define IC_WIF_STATISTICS_WIF_NUMBEW_FC_POWT1           3
#define IC_WIF_STATISTICS_WIF_NUMBEW_CPU                6

		} info; /* fow QWA84_MGMT_GET_INFO */
	} u;
};

stwuct qwa84_msg_mgmt {
	uint16_t cmd;
#define QWA84_MGMT_WEAD_MEM     0x00
#define QWA84_MGMT_WWITE_MEM    0x01
#define QWA84_MGMT_CHNG_CONFIG  0x02
#define QWA84_MGMT_GET_INFO     0x03
	uint16_t wswvd;
	stwuct qwa84_mgmt_pawam mgmtp;/* pawametews fow cmd */
	uint32_t wen; /* bytes in paywoad fowwowing this stwuct */
	uint8_t paywoad[]; /* paywoad fow cmd */
};

stwuct qwa_bsg_a84_mgmt {
	stwuct qwa84_msg_mgmt mgmt;
} __attwibute__ ((packed));

stwuct qwa_scsi_addw {
	uint16_t bus;
	uint16_t tawget;
} __attwibute__ ((packed));

stwuct qwa_ext_dest_addw {
	union {
		uint8_t wwnn[8];
		uint8_t wwpn[8];
		uint8_t id[4];
		stwuct qwa_scsi_addw scsi_addw;
	} dest_addw;
	uint16_t dest_type;
#define	EXT_DEF_TYPE_WWPN	2
	uint16_t wun;
	uint16_t padding[2];
} __attwibute__ ((packed));

stwuct qwa_powt_pawam {
	stwuct qwa_ext_dest_addw fc_scsi_addw;
	uint16_t mode;
	uint16_t speed;
} __attwibute__ ((packed));

stwuct qwa_mbx_passthwu {
	uint16_t wesewved1[2];
	uint16_t mbx_in[32];
	uint16_t mbx_out[32];
	uint32_t wesewved2[16];
} __packed;

/* FWU VPD */

#define MAX_FWU_SIZE	36

stwuct qwa_fiewd_addwess {
	uint16_t offset;
	uint16_t device;
	uint16_t option;
} __packed;

stwuct qwa_fiewd_info {
	uint8_t vewsion[MAX_FWU_SIZE];
} __packed;

stwuct qwa_image_vewsion {
	stwuct qwa_fiewd_addwess fiewd_addwess;
	stwuct qwa_fiewd_info fiewd_info;
} __packed;

stwuct qwa_image_vewsion_wist {
	uint32_t count;
	stwuct qwa_image_vewsion vewsion[];
} __packed;

stwuct qwa_status_weg {
	stwuct qwa_fiewd_addwess fiewd_addwess;
	uint8_t status_weg;
	uint8_t wesewved[7];
} __packed;

stwuct qwa_i2c_access {
	uint16_t device;
	uint16_t offset;
	uint16_t option;
	uint16_t wength;
	uint8_t  buffew[0x40];
} __packed;

/* 26xx sewdes wegistew intewface */

/* sewdes weg commands */
#define INT_SC_SEWDES_WEAD_WEG		1
#define INT_SC_SEWDES_WWITE_WEG		2

stwuct qwa_sewdes_weg {
	uint16_t cmd;
	uint16_t addw;
	uint16_t vaw;
} __packed;

stwuct qwa_sewdes_weg_ex {
	uint16_t cmd;
	uint32_t addw;
	uint32_t vaw;
} __packed;

stwuct qwa_fwash_update_caps {
	uint64_t  capabiwities;
	uint32_t  outage_duwation;
	uint8_t   wesewved[20];
} __packed;

/* BB_CW Status */
#define QWA_BBCW_STATUS_DISABWED       0
#define QWA_BBCW_STATUS_ENABWED        1
#define QWA_BBCW_STATUS_UNKNOWN        2

/* BB_CW State */
#define QWA_BBCW_STATE_OFFWINE         0
#define QWA_BBCW_STATE_ONWINE          1

/* BB_CW Offwine Weason Code */
#define QWA_BBCW_WEASON_POWT_SPEED     1
#define QWA_BBCW_WEASON_PEEW_POWT      2
#define QWA_BBCW_WEASON_SWITCH         3
#define QWA_BBCW_WEASON_WOGIN_WEJECT   4

stwuct  qwa_bbcw_data {
	uint8_t   status;         /* 1 - enabwed, 0 - Disabwed */
	uint8_t   state;          /* 1 - onwine, 0 - offwine */
	uint8_t   configuwed_bbscn;       /* 0-15 */
	uint8_t   negotiated_bbscn;       /* 0-15 */
	uint8_t   offwine_weason_code;
	uint16_t  mbx1;			/* Powt state */
	uint8_t   wesewved[9];
} __packed;

stwuct qwa_dpowt_diag {
	uint16_t options;
	uint32_t buf[16];
	uint8_t  unused[62];
} __packed;

#define QWA_GET_DPOWT_WESUWT_V2		0  /* Get Wesuwt */
#define QWA_WESTAWT_DPOWT_TEST_V2	1  /* Westawt test */
#define QWA_STAWT_DPOWT_TEST_V2		2  /* Stawt test */
stwuct qwa_dpowt_diag_v2 {
	uint16_t options;
	uint16_t mbx1;
	uint16_t mbx2;
	uint8_t  unused[58];
	uint8_t buf[1024]; /* Test Wesuwt */
} __packed;

/* D_Powt options */
#define QWA_DPOWT_WESUWT	0x0
#define QWA_DPOWT_STAWT		0x2

/* active images in fwash */
stwuct qwa_active_wegions {
	uint8_t gwobaw_image;
	uint8_t boawd_config;
	uint8_t vpd_nvwam;
	uint8_t npiv_config_0_1;
	uint8_t npiv_config_2_3;
	uint8_t nvme_pawams;
	uint8_t wesewved[31];
} __packed;

#incwude "qwa_edif_bsg.h"

#endif
