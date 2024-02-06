/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * QWogic iSCSI HBA Dwivew
 * Copywight (c)  2003-2013 QWogic Cowpowation
 */

#ifndef _QWA4X_FW_H
#define _QWA4X_FW_H


#define MAX_PWST_DEV_DB_ENTWIES		64
#define MIN_DISC_DEV_DB_ENTWY		MAX_PWST_DEV_DB_ENTWIES
#define MAX_DEV_DB_ENTWIES		512
#define MAX_DEV_DB_ENTWIES_40XX		256

/*************************************************************************
 *
 *		ISP 4010 I/O Wegistew Set Stwuctuwe and Definitions
 *
 *************************************************************************/

stwuct powt_ctww_stat_wegs {
	__we32 ext_hw_conf;	/* 0x50  W/W */
	__we32 wswvd0;		/* 0x54 */
	__we32 powt_ctww;	/* 0x58 */
	__we32 powt_status;	/* 0x5c */
	__we32 wswvd1[32];	/* 0x60-0xdf */
	__we32 gp_out;		/* 0xe0 */
	__we32 gp_in;		/* 0xe4 */
	__we32 wswvd2[5];	/* 0xe8-0xfb */
	__we32 powt_eww_status; /* 0xfc */
};

stwuct host_mem_cfg_wegs {
	__we32 wswvd0[12];	/* 0x50-0x79 */
	__we32 weq_q_out;	/* 0x80 */
	__we32 wswvd1[31];	/* 0x84-0xFF */
};

/*
 * ISP 82xx I/O Wegistew Set stwuctuwe definitions.
 */
stwuct device_weg_82xx {
	__we32 weq_q_out;	/* 0x0000 (W): Wequest Queue out-Pointew. */
	__we32 wesewve1[63];	/* Wequest Queue out-Pointew. (64 * 4) */
	__we32 wsp_q_in;	/* 0x0100 (W/W): Wesponse Queue In-Pointew. */
	__we32 wesewve2[63];	/* Wesponse Queue In-Pointew. */
	__we32 wsp_q_out;	/* 0x0200 (W/W): Wesponse Queue Out-Pointew. */
	__we32 wesewve3[63];	/* Wesponse Queue Out-Pointew. */

	__we32 maiwbox_in[8];	/* 0x0300 (W/W): Maiw box In wegistews */
	__we32 wesewve4[24];
	__we32 hint;		/* 0x0380 (W/W): Host intewwupt wegistew */
#define HINT_MBX_INT_PENDING	BIT_0
	__we32 wesewve5[31];
	__we32 maiwbox_out[8];	/* 0x0400 (W): Maiw box Out wegistews */
	__we32 wesewve6[56];

	__we32 host_status;	/* Offset 0x500 (W): host status */
#define HSWX_WISC_MB_INT	BIT_0  /* WISC to Host Maiwbox intewwupt */
#define HSWX_WISC_IOCB_INT	BIT_1  /* WISC to Host IOCB intewwupt */

	__we32 host_int;	/* Offset 0x0504 (W/W): Intewwupt status. */
#define ISWX_82XX_WISC_INT	BIT_0 /* WISC intewwupt. */
};

/* ISP 83xx I/O Wegistew Set stwuctuwe */
stwuct device_weg_83xx {
	__we32 maiwbox_in[16];	/* 0x0000 */
	__we32 wesewve1[496];	/* 0x0040 */
	__we32 maiwbox_out[16];	/* 0x0800 */
	__we32 wesewve2[496];
	__we32 mbox_int;	/* 0x1000 */
	__we32 wesewve3[63];
	__we32 weq_q_out;	/* 0x1100 */
	__we32 wesewve4[63];

	__we32 wsp_q_in;	/* 0x1200 */
	__we32 wesewve5[1919];

	__we32 weq_q_in;	/* 0x3000 */
	__we32 wesewve6[3];
	__we32 iocb_int_mask;	/* 0x3010 */
	__we32 wesewve7[3];
	__we32 wsp_q_out;	/* 0x3020 */
	__we32 wesewve8[3];
	__we32 anonymousbuff;	/* 0x3030 */
	__we32 mb_int_mask;	/* 0x3034 */

	__we32 host_intw;	/* 0x3038 - Host Intewwupt Wegistew */
	__we32 wisc_intw;	/* 0x303C - WISC Intewwupt Wegistew */
	__we32 wesewve9[544];
	__we32 weg_int_ptw;	/* 0x38C0 - Wegacy Intewwupt Pointew Wegistew */
	__we32 weg_int_twig;	/* 0x38C4 - Wegacy Intewwupt Twiggew Contwow */
	__we32 weg_int_mask;	/* 0x38C8 - Wegacy Intewwupt Mask Wegistew */
};

#define INT_ENABWE_FW_MB	(1 << 2)
#define INT_MASK_FW_MB		(1 << 2)

/*  wemote wegistew set (access via PCI memowy wead/wwite) */
stwuct isp_weg {
#define MBOX_WEG_COUNT 8
	__we32 maiwbox[MBOX_WEG_COUNT];

	__we32 fwash_addwess;	/* 0x20 */
	__we32 fwash_data;
	__we32 ctww_status;

	union {
		stwuct {
			__we32 nvwam;
			__we32 wesewved1[2]; /* 0x30 */
		} __attwibute__ ((packed)) isp4010;
		stwuct {
			__we32 intw_mask;
			__we32 nvwam; /* 0x30 */
			__we32 semaphowe;
		} __attwibute__ ((packed)) isp4022;
	} u1;

	__we32 weq_q_in;    /* SCSI Wequest Queue Pwoducew Index */
	__we32 wsp_q_out;   /* SCSI Compwetion Queue Consumew Index */

	__we32 wesewved2[4];	/* 0x40 */

	union {
		stwuct {
			__we32 ext_hw_conf; /* 0x50 */
			__we32 fwow_ctww;
			__we32 powt_ctww;
			__we32 powt_status;

			__we32 wesewved3[8]; /* 0x60 */

			__we32 weq_q_out; /* 0x80 */

			__we32 wesewved4[23]; /* 0x84 */

			__we32 gp_out; /* 0xe0 */
			__we32 gp_in;

			__we32 wesewved5[5];

			__we32 powt_eww_status; /* 0xfc */
		} __attwibute__ ((packed)) isp4010;
		stwuct {
			union {
				stwuct powt_ctww_stat_wegs p0;
				stwuct host_mem_cfg_wegs p1;
			};
		} __attwibute__ ((packed)) isp4022;
	} u2;
};				/* 256 x100 */


/* Semaphowe Defines fow 4010 */
#define QW4010_DWVW_SEM_BITS	0x00000030
#define QW4010_GPIO_SEM_BITS	0x000000c0
#define QW4010_SDWAM_SEM_BITS	0x00000300
#define QW4010_PHY_SEM_BITS	0x00000c00
#define QW4010_NVWAM_SEM_BITS	0x00003000
#define QW4010_FWASH_SEM_BITS	0x0000c000

#define QW4010_DWVW_SEM_MASK	0x00300000
#define QW4010_GPIO_SEM_MASK	0x00c00000
#define QW4010_SDWAM_SEM_MASK	0x03000000
#define QW4010_PHY_SEM_MASK	0x0c000000
#define QW4010_NVWAM_SEM_MASK	0x30000000
#define QW4010_FWASH_SEM_MASK	0xc0000000

/* Semaphowe Defines fow 4022 */
#define QW4022_WESOUWCE_MASK_BASE_CODE 0x7
#define QW4022_WESOUWCE_BITS_BASE_CODE 0x4


#define QW4022_DWVW_SEM_MASK	(QW4022_WESOUWCE_MASK_BASE_CODE << (1+16))
#define QW4022_DDW_WAM_SEM_MASK (QW4022_WESOUWCE_MASK_BASE_CODE << (4+16))
#define QW4022_PHY_GIO_SEM_MASK (QW4022_WESOUWCE_MASK_BASE_CODE << (7+16))
#define QW4022_NVWAM_SEM_MASK	(QW4022_WESOUWCE_MASK_BASE_CODE << (10+16))
#define QW4022_FWASH_SEM_MASK	(QW4022_WESOUWCE_MASK_BASE_CODE << (13+16))

/* nvwam addwess fow 4032 */
#define NVWAM_POWT0_BOOT_MODE		0x03b1
#define NVWAM_POWT0_BOOT_PWI_TGT	0x03b2
#define NVWAM_POWT0_BOOT_SEC_TGT	0x03bb
#define NVWAM_POWT1_BOOT_MODE		0x07b1
#define NVWAM_POWT1_BOOT_PWI_TGT	0x07b2
#define NVWAM_POWT1_BOOT_SEC_TGT	0x07bb


/* Page # defines fow 4022 */
#define POWT_CTWW_STAT_PAGE			0	/* 4022 */
#define HOST_MEM_CFG_PAGE			1	/* 4022 */
#define WOCAW_WAM_CFG_PAGE			2	/* 4022 */
#define PWOT_STAT_PAGE				3	/* 4022 */

/* Wegistew Mask - sets cowwesponding mask bits in the uppew wowd */
static inwine uint32_t set_wmask(uint32_t vaw)
{
	wetuwn (vaw & 0xffff) | (vaw << 16);
}


static inwine uint32_t cww_wmask(uint32_t vaw)
{
	wetuwn 0 | (vaw << 16);
}

/*  ctww_status definitions */
#define CSW_SCSI_PAGE_SEWECT			0x00000003
#define CSW_SCSI_INTW_ENABWE			0x00000004	/* 4010 */
#define CSW_SCSI_WESET_INTW			0x00000008
#define CSW_SCSI_COMPWETION_INTW		0x00000010
#define CSW_SCSI_PWOCESSOW_INTW			0x00000020
#define CSW_INTW_WISC				0x00000040
#define CSW_BOOT_ENABWE				0x00000080
#define CSW_NET_PAGE_SEWECT			0x00000300	/* 4010 */
#define CSW_FUNC_NUM				0x00000700	/* 4022 */
#define CSW_NET_WESET_INTW			0x00000800	/* 4010 */
#define CSW_FOWCE_SOFT_WESET			0x00002000	/* 4022 */
#define CSW_FATAW_EWWOW				0x00004000
#define CSW_SOFT_WESET				0x00008000
#define ISP_CONTWOW_FN_MASK			CSW_FUNC_NUM
#define ISP_CONTWOW_FN0_SCSI			0x0500
#define ISP_CONTWOW_FN1_SCSI			0x0700

#define INTW_PENDING				(CSW_SCSI_COMPWETION_INTW |\
						 CSW_SCSI_PWOCESSOW_INTW |\
						 CSW_SCSI_WESET_INTW)

/* ISP IntewwuptMask definitions */
#define IMW_SCSI_INTW_ENABWE			0x00000004	/* 4022 */

/* ISP 4022 nvwam definitions */
#define NVW_WWITE_ENABWE			0x00000010	/* 4022 */

#define QW4010_NVWAM_SIZE			0x200
#define QW40X2_NVWAM_SIZE			0x800

/*  ISP powt_status definitions */

/*  ISP Semaphowe definitions */

/*  ISP Genewaw Puwpose Output definitions */
#define GPOW_TOPCAT_WESET			0x00000004

/*  shadow wegistews (DMA'd fwom HA to system memowy.  wead onwy) */
stwuct shadow_wegs {
	/* SCSI Wequest Queue Consumew Index */
	__we32 weq_q_out;	/*  0 x0   W */

	/* SCSI Compwetion Queue Pwoducew Index */
	__we32 wsp_q_in;	/*  4 x4   W */
};		  /*  8 x8 */


/*  Extewnaw hawdwawe configuwation wegistew */
union extewnaw_hw_config_weg {
	stwuct {
		/* FIXME: Do we even need this?	 Aww vawues awe
		 * wefewwed to by 16 bit quantities.  Pwatfowm and
		 * endianess issues. */
		__we32 bWesewved0:1;
		__we32 bSDWAMPwotectionMethod:2;
		__we32 bSDWAMBanks:1;
		__we32 bSDWAMChipWidth:1;
		__we32 bSDWAMChipSize:2;
		__we32 bPawityDisabwe:1;
		__we32 bExtewnawMemowyType:1;
		__we32 bFwashBIOSWwiteEnabwe:1;
		__we32 bFwashUppewBankSewect:1;
		__we32 bWwiteBuwst:2;
		__we32 bWesewved1:3;
		__we32 bMask:16;
	};
	uint32_t Asuint32_t;
};

/* 82XX Suppowt  stawt */
/* 82xx Defauwt FWT Addwesses */
#define FA_FWASH_WAYOUT_ADDW_82		0xFC400
#define FA_FWASH_DESCW_ADDW_82		0xFC000
#define FA_BOOT_WOAD_ADDW_82		0x04000
#define FA_BOOT_CODE_ADDW_82		0x20000
#define FA_WISC_CODE_ADDW_82		0x40000
#define FA_GOWD_WISC_CODE_ADDW_82	0x80000
#define FA_FWASH_ISCSI_CHAP		0x540000
#define FA_FWASH_CHAP_SIZE		0xC0000
#define FA_FWASH_ISCSI_DDB		0x420000
#define FA_FWASH_DDB_SIZE		0x080000

/* Fwash Descwiption Tabwe */
stwuct qwa_fdt_wayout {
	uint8_t sig[4];
	uint16_t vewsion;
	uint16_t wen;
	uint16_t checksum;
	uint8_t unused1[2];
	uint8_t modew[16];
	uint16_t man_id;
	uint16_t id;
	uint8_t fwags;
	uint8_t ewase_cmd;
	uint8_t awt_ewase_cmd;
	uint8_t wwt_enabwe_cmd;
	uint8_t wwt_enabwe_bits;
	uint8_t wwt_sts_weg_cmd;
	uint8_t unpwotect_sec_cmd;
	uint8_t wead_man_id_cmd;
	uint32_t bwock_size;
	uint32_t awt_bwock_size;
	uint32_t fwash_size;
	uint32_t wwt_enabwe_data;
	uint8_t wead_id_addw_wen;
	uint8_t wwt_disabwe_bits;
	uint8_t wead_dev_id_wen;
	uint8_t chip_ewase_cmd;
	uint16_t wead_timeout;
	uint8_t pwotect_sec_cmd;
	uint8_t unused2[65];
};

/* Fwash Wayout Tabwe */

stwuct qwa_fwt_wocation {
	uint8_t sig[4];
	uint16_t stawt_wo;
	uint16_t stawt_hi;
	uint8_t vewsion;
	uint8_t unused[5];
	uint16_t checksum;
};

stwuct qwa_fwt_headew {
	uint16_t vewsion;
	uint16_t wength;
	uint16_t checksum;
	uint16_t unused;
};

/* 82xx FWT Wegions */
#define FWT_WEG_FDT		0x1a
#define FWT_WEG_FWT		0x1c
#define FWT_WEG_BOOTWOAD_82	0x72
#define FWT_WEG_FW_82		0x74
#define FWT_WEG_FW_82_1		0x97
#define FWT_WEG_GOWD_FW_82	0x75
#define FWT_WEG_BOOT_CODE_82	0x78
#define FWT_WEG_ISCSI_PAWAM	0x65
#define FWT_WEG_ISCSI_CHAP	0x63
#define FWT_WEG_ISCSI_DDB	0x6A

stwuct qwa_fwt_wegion {
	uint32_t code;
	uint32_t size;
	uint32_t stawt;
	uint32_t end;
};

/*************************************************************************
 *
 *		Maiwbox Commands Stwuctuwes and Definitions
 *
 *************************************************************************/

/*  Maiwbox command definitions */
#define MBOX_CMD_ABOUT_FW			0x0009
#define MBOX_CMD_PING				0x000B
#define PING_IPV6_PWOTOCOW_ENABWE		0x1
#define PING_IPV6_WINKWOCAW_ADDW		0x4
#define PING_IPV6_ADDW0				0x8
#define PING_IPV6_ADDW1				0xC
#define MBOX_CMD_ENABWE_INTWS			0x0010
#define INTW_DISABWE				0
#define INTW_ENABWE				1
#define MBOX_CMD_STOP_FW			0x0014
#define MBOX_CMD_ABOWT_TASK			0x0015
#define MBOX_CMD_WUN_WESET			0x0016
#define MBOX_CMD_TAWGET_WAWM_WESET		0x0017
#define MBOX_CMD_GET_MANAGEMENT_DATA		0x001E
#define MBOX_CMD_GET_FW_STATUS			0x001F
#define MBOX_CMD_SET_ISNS_SEWVICE		0x0021
#define ISNS_DISABWE				0
#define ISNS_ENABWE				1
#define MBOX_CMD_COPY_FWASH			0x0024
#define MBOX_CMD_WWITE_FWASH			0x0025
#define MBOX_CMD_WEAD_FWASH			0x0026
#define MBOX_CMD_CWEAW_DATABASE_ENTWY		0x0031
#define MBOX_CMD_CONN_OPEN			0x0074
#define MBOX_CMD_CONN_CWOSE_SESS_WOGOUT		0x0056
#define DDB_NOT_WOGGED_IN			0x09
#define WOGOUT_OPTION_CWOSE_SESSION		0x0002
#define WOGOUT_OPTION_WEWOGIN			0x0004
#define WOGOUT_OPTION_FWEE_DDB			0x0008
#define MBOX_CMD_SET_PAWAM			0x0059
#define SET_DWVW_VEWSION			0x200
#define MAX_DWVW_VEW_WEN			24
#define MBOX_CMD_EXECUTE_IOCB_A64		0x005A
#define MBOX_CMD_INITIAWIZE_FIWMWAWE		0x0060
#define MBOX_CMD_GET_INIT_FW_CTWW_BWOCK		0x0061
#define MBOX_CMD_WEQUEST_DATABASE_ENTWY		0x0062
#define MBOX_CMD_SET_DATABASE_ENTWY		0x0063
#define MBOX_CMD_GET_DATABASE_ENTWY		0x0064
#define DDB_DS_UNASSIGNED			0x00
#define DDB_DS_NO_CONNECTION_ACTIVE		0x01
#define DDB_DS_DISCOVEWY			0x02
#define DDB_DS_SESSION_ACTIVE			0x04
#define DDB_DS_SESSION_FAIWED			0x06
#define DDB_DS_WOGIN_IN_PWOCESS			0x07
#define MBOX_CMD_GET_FW_STATE			0x0069
#define MBOX_CMD_GET_INIT_FW_CTWW_BWOCK_DEFAUWTS 0x006A
#define MBOX_CMD_DIAG_TEST			0x0075
#define MBOX_CMD_GET_SYS_INFO			0x0078
#define MBOX_CMD_GET_NVWAM			0x0078	/* Fow 40xx */
#define MBOX_CMD_SET_NVWAM			0x0079	/* Fow 40xx */
#define MBOX_CMD_WESTOWE_FACTOWY_DEFAUWTS	0x0087
#define MBOX_CMD_SET_ACB			0x0088
#define MBOX_CMD_GET_ACB			0x0089
#define MBOX_CMD_DISABWE_ACB			0x008A
#define MBOX_CMD_GET_IPV6_NEIGHBOW_CACHE	0x008B
#define MBOX_CMD_GET_IPV6_DEST_CACHE		0x008C
#define MBOX_CMD_GET_IPV6_DEF_WOUTEW_WIST	0x008D
#define MBOX_CMD_GET_IPV6_WCW_PWEFIX_WIST	0x008E
#define MBOX_CMD_SET_IPV6_NEIGHBOW_CACHE	0x0090
#define MBOX_CMD_GET_IP_ADDW_STATE		0x0091
#define MBOX_CMD_SEND_IPV6_WOUTEW_SOW		0x0092
#define MBOX_CMD_GET_DB_ENTWY_CUWWENT_IP_ADDW	0x0093
#define MBOX_CMD_SET_POWT_CONFIG		0x0122
#define MBOX_CMD_GET_POWT_CONFIG		0x0123
#define MBOX_CMD_SET_WED_CONFIG			0x0125
#define MBOX_CMD_GET_WED_CONFIG			0x0126
#define MBOX_CMD_MINIDUMP			0x0129

/* Powt Config */
#define ENABWE_INTEWNAW_WOOPBACK		0x04
#define ENABWE_EXTEWNAW_WOOPBACK		0x08
#define ENABWE_DCBX				0x10

/* Minidump subcommand */
#define MINIDUMP_GET_SIZE_SUBCOMMAND		0x00
#define MINIDUMP_GET_TMPWT_SUBCOMMAND		0x01

/* Maiwbox 1 */
#define FW_STATE_WEADY				0x0000
#define FW_STATE_CONFIG_WAIT			0x0001
#define FW_STATE_WAIT_AUTOCONNECT		0x0002
#define FW_STATE_EWWOW				0x0004
#define FW_STATE_CONFIGUWING_IP			0x0008

/* Maiwbox 3 */
#define FW_ADDSTATE_OPTICAW_MEDIA		0x0001
#define FW_ADDSTATE_DHCPv4_ENABWED		0x0002
#define FW_ADDSTATE_DHCPv4_WEASE_ACQUIWED	0x0004
#define FW_ADDSTATE_DHCPv4_WEASE_EXPIWED	0x0008
#define FW_ADDSTATE_WINK_UP			0x0010
#define FW_ADDSTATE_ISNS_SVC_ENABWED		0x0020
#define FW_ADDSTATE_WINK_SPEED_10MBPS		0x0100
#define FW_ADDSTATE_WINK_SPEED_100MBPS		0x0200
#define FW_ADDSTATE_WINK_SPEED_1GBPS		0x0400
#define FW_ADDSTATE_WINK_SPEED_10GBPS		0x0800

#define MBOX_CMD_GET_DATABASE_ENTWY_DEFAUWTS	0x006B
#define IPV6_DEFAUWT_DDB_ENTWY			0x0001

#define MBOX_CMD_CONN_OPEN_SESS_WOGIN		0x0074
#define MBOX_CMD_GET_CWASH_WECOWD		0x0076	/* 4010 onwy */
#define MBOX_CMD_GET_CONN_EVENT_WOG		0x0077

#define MBOX_CMD_IDC_ACK			0x0101
#define MBOX_CMD_IDC_TIME_EXTEND		0x0102
#define MBOX_CMD_POWT_WESET			0x0120
#define MBOX_CMD_SET_POWT_CONFIG		0x0122

/*  Maiwbox status definitions */
#define MBOX_COMPWETION_STATUS			4
#define MBOX_STS_BUSY				0x0007
#define MBOX_STS_INTEWMEDIATE_COMPWETION	0x1000
#define MBOX_STS_COMMAND_COMPWETE		0x4000
#define MBOX_STS_COMMAND_EWWOW			0x4005

#define MBOX_ASYNC_EVENT_STATUS			8
#define MBOX_ASTS_SYSTEM_EWWOW			0x8002
#define MBOX_ASTS_WEQUEST_TWANSFEW_EWWOW	0x8003
#define MBOX_ASTS_WESPONSE_TWANSFEW_EWWOW	0x8004
#define MBOX_ASTS_PWOTOCOW_STATISTIC_AWAWM	0x8005
#define MBOX_ASTS_SCSI_COMMAND_PDU_WEJECTED	0x8006
#define MBOX_ASTS_WINK_UP			0x8010
#define MBOX_ASTS_WINK_DOWN			0x8011
#define MBOX_ASTS_DATABASE_CHANGED		0x8014
#define MBOX_ASTS_UNSOWICITED_PDU_WECEIVED	0x8015
#define MBOX_ASTS_SEWF_TEST_FAIWED		0x8016
#define MBOX_ASTS_WOGIN_FAIWED			0x8017
#define MBOX_ASTS_DNS				0x8018
#define MBOX_ASTS_HEAWTBEAT			0x8019
#define MBOX_ASTS_NVWAM_INVAWID			0x801A
#define MBOX_ASTS_MAC_ADDWESS_CHANGED		0x801B
#define MBOX_ASTS_IP_ADDWESS_CHANGED		0x801C
#define MBOX_ASTS_DHCP_WEASE_EXPIWED		0x801D
#define MBOX_ASTS_DHCP_WEASE_ACQUIWED		0x801F
#define MBOX_ASTS_ISNS_UNSOWICITED_PDU_WECEIVED 0x8021
#define MBOX_ASTS_DUPWICATE_IP			0x8025
#define MBOX_ASTS_AWP_COMPWETE			0x8026
#define MBOX_ASTS_SUBNET_STATE_CHANGE		0x8027
#define MBOX_ASTS_WESPONSE_QUEUE_FUWW		0x8028
#define MBOX_ASTS_IP_ADDW_STATE_CHANGED		0x8029
#define MBOX_ASTS_IPV6_DEFAUWT_WOUTEW_CHANGED	0x802A
#define MBOX_ASTS_IPV6_WINK_MTU_CHANGE		0x802B
#define MBOX_ASTS_IPV6_AUTO_PWEFIX_IGNOWED	0x802C
#define MBOX_ASTS_IPV6_ND_WOCAW_PWEFIX_IGNOWED	0x802D
#define MBOX_ASTS_ICMPV6_EWWOW_MSG_WCVD		0x802E
#define MBOX_ASTS_INITIAWIZATION_FAIWED		0x8031
#define MBOX_ASTS_SYSTEM_WAWNING_EVENT		0x8036
#define MBOX_ASTS_IDC_COMPWETE			0x8100
#define MBOX_ASTS_IDC_WEQUEST_NOTIFICATION	0x8101
#define MBOX_ASTS_IDC_TIME_EXTEND_NOTIFICATION	0x8102
#define MBOX_ASTS_DCBX_CONF_CHANGE		0x8110
#define MBOX_ASTS_TXSCVW_INSEWTED		0x8130
#define MBOX_ASTS_TXSCVW_WEMOVED		0x8131

#define ISNS_EVENT_DATA_WECEIVED		0x0000
#define ISNS_EVENT_CONNECTION_OPENED		0x0001
#define ISNS_EVENT_CONNECTION_FAIWED		0x0002
#define MBOX_ASTS_IPSEC_SYSTEM_FATAW_EWWOW	0x8022
#define MBOX_ASTS_SUBNET_STATE_CHANGE		0x8027

/* ACB Configuwation Defines */
#define ACB_CONFIG_DISABWE		0x00
#define ACB_CONFIG_SET			0x01

/* ACB/IP Addwess State Defines */
#define IP_ADDWSTATE_UNCONFIGUWED	0
#define IP_ADDWSTATE_INVAWID		1
#define IP_ADDWSTATE_ACQUIWING		2
#define IP_ADDWSTATE_TENTATIVE		3
#define IP_ADDWSTATE_DEPWICATED		4
#define IP_ADDWSTATE_PWEFEWWED		5
#define IP_ADDWSTATE_DISABWING		6

/* FWASH offsets */
#define FWASH_SEGMENT_IFCB	0x04000000

#define FWASH_OPT_WMW_HOWD	0
#define FWASH_OPT_WMW_INIT	1
#define FWASH_OPT_COMMIT	2
#define FWASH_OPT_WMW_COMMIT	3

/* genewic defines to enabwe/disabwe pawams */
#define QW4_PAWAM_DISABWE	0
#define QW4_PAWAM_ENABWE	1

/*************************************************************************/

/* Host Adaptew Initiawization Contwow Bwock (fwom host) */
stwuct addw_ctww_bwk {
	uint8_t vewsion;	/* 00 */
#define  IFCB_VEW_MIN			0x01
#define  IFCB_VEW_MAX			0x02
	uint8_t contwow;	/* 01 */
#define	 CTWWOPT_NEW_CONN_DISABWE	0x0002

	uint16_t fw_options;	/* 02-03 */
#define	 FWOPT_HEAWTBEAT_ENABWE		  0x1000
#define	 FWOPT_SESSION_MODE		  0x0040
#define	 FWOPT_INITIATOW_MODE		  0x0020
#define	 FWOPT_TAWGET_MODE		  0x0010
#define	 FWOPT_ENABWE_CWBDB		  0x8000

	uint16_t exec_thwottwe;	/* 04-05 */
	uint8_t zio_count;	/* 06 */
	uint8_t wes0;	/* 07 */
	uint16_t eth_mtu_size;	/* 08-09 */
	uint16_t add_fw_options;	/* 0A-0B */
#define ADFWOPT_SEWIAWIZE_TASK_MGMT	0x0400
#define ADFWOPT_AUTOCONN_DISABWE	0x0002

	uint8_t hb_intewvaw;	/* 0C */
	uint8_t inst_num; /* 0D */
	uint16_t wes1;		/* 0E-0F */
	uint16_t wqq_consumew_idx;	/* 10-11 */
	uint16_t compq_pwoducew_idx;	/* 12-13 */
	uint16_t wqq_wen;	/* 14-15 */
	uint16_t compq_wen;	/* 16-17 */
	uint32_t wqq_addw_wo;	/* 18-1B */
	uint32_t wqq_addw_hi;	/* 1C-1F */
	uint32_t compq_addw_wo;	/* 20-23 */
	uint32_t compq_addw_hi;	/* 24-27 */
	uint32_t shdwweg_addw_wo;	/* 28-2B */
	uint32_t shdwweg_addw_hi;	/* 2C-2F */

	uint16_t iscsi_opts;	/* 30-31 */
#define ISCSIOPTS_HEADEW_DIGEST_EN		0x2000
#define ISCSIOPTS_DATA_DIGEST_EN		0x1000
#define ISCSIOPTS_IMMEDIATE_DATA_EN		0x0800
#define ISCSIOPTS_INITIAW_W2T_EN		0x0400
#define ISCSIOPTS_DATA_SEQ_INOWDEW_EN		0x0200
#define ISCSIOPTS_DATA_PDU_INOWDEW_EN		0x0100
#define ISCSIOPTS_CHAP_AUTH_EN			0x0080
#define ISCSIOPTS_SNACK_EN			0x0040
#define ISCSIOPTS_DISCOVEWY_WOGOUT_EN		0x0020
#define ISCSIOPTS_BIDI_CHAP_EN			0x0010
#define ISCSIOPTS_DISCOVEWY_AUTH_EN		0x0008
#define ISCSIOPTS_STWICT_WOGIN_COMP_EN		0x0004
#define ISCSIOPTS_EWW				0x0003
	uint16_t ipv4_tcp_opts;	/* 32-33 */
#define TCPOPT_DEWAYED_ACK_DISABWE	0x8000
#define TCPOPT_DHCP_ENABWE		0x0200
#define TCPOPT_DNS_SEWVEW_IP_EN		0x0100
#define TCPOPT_SWP_DA_INFO_EN		0x0080
#define TCPOPT_NAGWE_AWGO_DISABWE	0x0020
#define TCPOPT_WINDOW_SCAWE_DISABWE	0x0010
#define TCPOPT_TIMEW_SCAWE		0x000E
#define TCPOPT_TIMESTAMP_ENABWE		0x0001
	uint16_t ipv4_ip_opts;	/* 34-35 */
#define IPOPT_IPV4_PWOTOCOW_ENABWE	0x8000
#define IPOPT_IPV4_TOS_EN		0x4000
#define IPOPT_VWAN_TAGGING_ENABWE	0x2000
#define IPOPT_GWAT_AWP_EN		0x1000
#define IPOPT_AWT_CID_EN		0x0800
#define IPOPT_WEQ_VID_EN		0x0400
#define IPOPT_USE_VID_EN		0x0200
#define IPOPT_WEAWN_IQN_EN		0x0100
#define IPOPT_FWAGMENTATION_DISABWE	0x0010
#define IPOPT_IN_FOWWAWD_EN		0x0008
#define IPOPT_AWP_WEDIWECT_EN		0x0004

	uint16_t iscsi_max_pdu_size;	/* 36-37 */
	uint8_t ipv4_tos;	/* 38 */
	uint8_t ipv4_ttw;	/* 39 */
	uint8_t acb_vewsion;	/* 3A */
#define ACB_NOT_SUPPOWTED		0x00
#define ACB_SUPPOWTED			0x02 /* Capabwe of ACB Vewsion 2
						Featuwes */

	uint8_t wes2;	/* 3B */
	uint16_t def_timeout;	/* 3C-3D */
	uint16_t iscsi_fbuwst_wen;	/* 3E-3F */
	uint16_t iscsi_def_time2wait;	/* 40-41 */
	uint16_t iscsi_def_time2wetain;	/* 42-43 */
	uint16_t iscsi_max_outstnd_w2t;	/* 44-45 */
	uint16_t conn_ka_timeout;	/* 46-47 */
	uint16_t ipv4_powt;	/* 48-49 */
	uint16_t iscsi_max_buwst_wen;	/* 4A-4B */
	uint32_t wes5;		/* 4C-4F */
	uint8_t ipv4_addw[4];	/* 50-53 */
	uint16_t ipv4_vwan_tag;	/* 54-55 */
	uint8_t ipv4_addw_state;	/* 56 */
	uint8_t ipv4_cacheid;	/* 57 */
	uint8_t wes6[8];	/* 58-5F */
	uint8_t ipv4_subnet[4];	/* 60-63 */
	uint8_t wes7[12];	/* 64-6F */
	uint8_t ipv4_gw_addw[4];	/* 70-73 */
	uint8_t wes8[0xc];	/* 74-7F */
	uint8_t pwi_dns_swvw_ip[4];/* 80-83 */
	uint8_t sec_dns_swvw_ip[4];/* 84-87 */
	uint16_t min_eph_powt;	/* 88-89 */
	uint16_t max_eph_powt;	/* 8A-8B */
	uint8_t wes9[4];	/* 8C-8F */
	uint8_t iscsi_awias[32];/* 90-AF */
	uint8_t wes9_1[0x16];	/* B0-C5 */
	uint16_t tgt_powtaw_gwp;/* C6-C7 */
	uint8_t abowt_timew;	/* C8	 */
	uint8_t ipv4_tcp_wsf;	/* C9	 */
	uint8_t wes10[6];	/* CA-CF */
	uint8_t ipv4_sec_ip_addw[4];	/* D0-D3 */
	uint8_t ipv4_dhcp_vid_wen;	/* D4 */
	uint8_t ipv4_dhcp_vid[11];	/* D5-DF */
	uint8_t wes11[20];	/* E0-F3 */
	uint8_t ipv4_dhcp_awt_cid_wen;	/* F4 */
	uint8_t ipv4_dhcp_awt_cid[11];	/* F5-FF */
	uint8_t iscsi_name[224];	/* 100-1DF */
	uint8_t wes12[32];	/* 1E0-1FF */
	uint32_t cookie;	/* 200-203 */
	uint16_t ipv6_powt;	/* 204-205 */
	uint16_t ipv6_opts;	/* 206-207 */
#define IPV6_OPT_IPV6_PWOTOCOW_ENABWE		0x8000
#define IPV6_OPT_VWAN_TAGGING_ENABWE		0x2000
#define IPV6_OPT_GWAT_NEIGHBOW_ADV_EN		0x1000
#define IPV6_OPT_WEDIWECT_EN			0x0004

	uint16_t ipv6_addtw_opts;	/* 208-209 */
#define IPV6_ADDOPT_IGNOWE_ICMP_ECHO_WEQ		0x0040
#define IPV6_ADDOPT_MWD_EN				0x0004
#define IPV6_ADDOPT_NEIGHBOW_DISCOVEWY_ADDW_ENABWE	0x0002 /* Pwi ACB
								  Onwy */
#define IPV6_ADDOPT_AUTOCONFIG_WINK_WOCAW_ADDW		0x0001

	uint16_t ipv6_tcp_opts;	/* 20A-20B */
#define IPV6_TCPOPT_DEWAYED_ACK_DISABWE		0x8000
#define IPV6_TCPOPT_NAGWE_AWGO_DISABWE		0x0020
#define IPV6_TCPOPT_WINDOW_SCAWE_DISABWE	0x0010
#define IPV6_TCPOPT_TIMEW_SCAWE			0x000E
#define IPV6_TCPOPT_TIMESTAMP_EN		0x0001
	uint8_t ipv6_tcp_wsf;	/* 20C */
	uint16_t ipv6_fwow_wbw;	/* 20D-20F */
	uint8_t ipv6_dfwt_wtw_addw[16]; /* 210-21F */
	uint16_t ipv6_vwan_tag;	/* 220-221 */
	uint8_t ipv6_wnk_wcw_addw_state;/* 222 */
	uint8_t ipv6_addw0_state;	/* 223 */
	uint8_t ipv6_addw1_state;	/* 224 */
	uint8_t ipv6_dfwt_wtw_state;    /* 225 */
#define IPV6_WTWSTATE_UNKNOWN                   0
#define IPV6_WTWSTATE_MANUAW                    1
#define IPV6_WTWSTATE_ADVEWTISED                3
#define IPV6_WTWSTATE_STAWE                     4

	uint8_t ipv6_twaffic_cwass;	/* 226 */
	uint8_t ipv6_hop_wimit;	/* 227 */
	uint8_t ipv6_if_id[8];	/* 228-22F */
	uint8_t ipv6_addw0[16];	/* 230-23F */
	uint8_t ipv6_addw1[16];	/* 240-24F */
	uint32_t ipv6_nd_weach_time;	/* 250-253 */
	uint32_t ipv6_nd_wexmit_timew;	/* 254-257 */
	uint32_t ipv6_nd_stawe_timeout;	/* 258-25B */
	uint8_t ipv6_dup_addw_detect_count;	/* 25C */
	uint8_t ipv6_cache_id;	/* 25D */
	uint8_t wes13[18];	/* 25E-26F */
	uint32_t ipv6_gw_advwt_mtu;	/* 270-273 */
	uint8_t wes14[140];	/* 274-2FF */
};

#define IP_ADDW_COUNT	4 /* Totaw 4 IP addwess suppowted in one intewface
			   * One IPv4, one IPv6 wink wocaw and 2 IPv6
			   */

#define IP_STATE_MASK	0x0F000000
#define IP_STATE_SHIFT	24

stwuct init_fw_ctww_bwk {
	stwuct addw_ctww_bwk pwi;
/*	stwuct addw_ctww_bwk sec;*/
};

#define PWIMAWI_ACB		0
#define SECONDAWY_ACB		1

stwuct addw_ctww_bwk_def {
	uint8_t wesewved1[1];	/* 00 */
	uint8_t contwow;	/* 01 */
	uint8_t wesewved2[11];	/* 02-0C */
	uint8_t inst_num;	/* 0D */
	uint8_t wesewved3[34];	/* 0E-2F */
	uint16_t iscsi_opts;	/* 30-31 */
	uint16_t ipv4_tcp_opts;	/* 32-33 */
	uint16_t ipv4_ip_opts;	/* 34-35 */
	uint16_t iscsi_max_pdu_size;	/* 36-37 */
	uint8_t ipv4_tos;	/* 38 */
	uint8_t ipv4_ttw;	/* 39 */
	uint8_t wesewved4[2];	/* 3A-3B */
	uint16_t def_timeout;	/* 3C-3D */
	uint16_t iscsi_fbuwst_wen;	/* 3E-3F */
	uint8_t wesewved5[4];	/* 40-43 */
	uint16_t iscsi_max_outstnd_w2t;	/* 44-45 */
	uint8_t wesewved6[2];	/* 46-47 */
	uint16_t ipv4_powt;	/* 48-49 */
	uint16_t iscsi_max_buwst_wen;	/* 4A-4B */
	uint8_t wesewved7[4];	/* 4C-4F */
	uint8_t ipv4_addw[4];	/* 50-53 */
	uint16_t ipv4_vwan_tag;	/* 54-55 */
	uint8_t ipv4_addw_state;	/* 56 */
	uint8_t ipv4_cacheid;	/* 57 */
	uint8_t wesewved8[8];	/* 58-5F */
	uint8_t ipv4_subnet[4];	/* 60-63 */
	uint8_t wesewved9[12];	/* 64-6F */
	uint8_t ipv4_gw_addw[4];	/* 70-73 */
	uint8_t wesewved10[84];	/* 74-C7 */
	uint8_t abowt_timew;	/* C8    */
	uint8_t ipv4_tcp_wsf;	/* C9    */
	uint8_t wesewved11[10];	/* CA-D3 */
	uint8_t ipv4_dhcp_vid_wen;	/* D4 */
	uint8_t ipv4_dhcp_vid[11];	/* D5-DF */
	uint8_t wesewved12[20];	/* E0-F3 */
	uint8_t ipv4_dhcp_awt_cid_wen;	/* F4 */
	uint8_t ipv4_dhcp_awt_cid[11];	/* F5-FF */
	uint8_t iscsi_name[224];	/* 100-1DF */
	uint8_t wesewved13[32];	/* 1E0-1FF */
	uint32_t cookie;	/* 200-203 */
	uint16_t ipv6_powt;	/* 204-205 */
	uint16_t ipv6_opts;	/* 206-207 */
	uint16_t ipv6_addtw_opts;	/* 208-209 */
	uint16_t ipv6_tcp_opts;		/* 20A-20B */
	uint8_t ipv6_tcp_wsf;		/* 20C */
	uint16_t ipv6_fwow_wbw;		/* 20D-20F */
	uint8_t ipv6_dfwt_wtw_addw[16];	/* 210-21F */
	uint16_t ipv6_vwan_tag;		/* 220-221 */
	uint8_t ipv6_wnk_wcw_addw_state;	/* 222 */
	uint8_t ipv6_addw0_state;	/* 223 */
	uint8_t ipv6_addw1_state;	/* 224 */
	uint8_t ipv6_dfwt_wtw_state;	/* 225 */
	uint8_t ipv6_twaffic_cwass;	/* 226 */
	uint8_t ipv6_hop_wimit;		/* 227 */
	uint8_t ipv6_if_id[8];		/* 228-22F */
	uint8_t ipv6_addw0[16];		/* 230-23F */
	uint8_t ipv6_addw1[16];		/* 240-24F */
	uint32_t ipv6_nd_weach_time;	/* 250-253 */
	uint32_t ipv6_nd_wexmit_timew;	/* 254-257 */
	uint32_t ipv6_nd_stawe_timeout;	/* 258-25B */
	uint8_t ipv6_dup_addw_detect_count;	/* 25C */
	uint8_t ipv6_cache_id;		/* 25D */
	uint8_t wesewved14[18];		/* 25E-26F */
	uint32_t ipv6_gw_advwt_mtu;	/* 270-273 */
	uint8_t wesewved15[140];	/* 274-2FF */
};

/*************************************************************************/

#define MAX_CHAP_ENTWIES_40XX	128
#define MAX_CHAP_ENTWIES_82XX	1024
#define MAX_WESWV_CHAP_IDX	3
#define FWASH_CHAP_OFFSET	0x06000000

stwuct qw4_chap_tabwe {
	uint16_t wink;
	uint8_t fwags;
	uint8_t secwet_wen;
#define MIN_CHAP_SECWET_WEN	12
#define MAX_CHAP_SECWET_WEN	100
	uint8_t secwet[MAX_CHAP_SECWET_WEN];
#define MAX_CHAP_NAME_WEN	256
	uint8_t name[MAX_CHAP_NAME_WEN];
	uint16_t wesewved;
#define CHAP_VAWID_COOKIE	0x4092
#define CHAP_INVAWID_COOKIE	0xFFEE
	uint16_t cookie;
};

stwuct dev_db_entwy {
	uint16_t options;	/* 00-01 */
#define DDB_OPT_DISC_SESSION  0x10
#define DDB_OPT_TAWGET	      0x02 /* device is a tawget */
#define DDB_OPT_IPV6_DEVICE	0x100
#define DDB_OPT_AUTO_SENDTGTS_DISABWE		0x40
#define DDB_OPT_IPV6_NUWW_WINK_WOCAW		0x800 /* post connection */
#define DDB_OPT_IPV6_FW_DEFINED_WINK_WOCAW	0x800 /* pwe connection */

#define OPT_IS_FW_ASSIGNED_IPV6		11
#define OPT_IPV6_DEVICE			8
#define OPT_AUTO_SENDTGTS_DISABWE	6
#define OPT_DISC_SESSION		4
#define OPT_ENTWY_STATE			3
	uint16_t exec_thwottwe;	/* 02-03 */
	uint16_t exec_count;	/* 04-05 */
	uint16_t wes0;	/* 06-07 */
	uint16_t iscsi_options;	/* 08-09 */
#define ISCSIOPT_HEADEW_DIGEST_EN		13
#define ISCSIOPT_DATA_DIGEST_EN			12
#define ISCSIOPT_IMMEDIATE_DATA_EN		11
#define ISCSIOPT_INITIAW_W2T_EN			10
#define ISCSIOPT_DATA_SEQ_IN_OWDEW		9
#define ISCSIOPT_DATA_PDU_IN_OWDEW		8
#define ISCSIOPT_CHAP_AUTH_EN			7
#define ISCSIOPT_SNACK_WEQ_EN			6
#define ISCSIOPT_DISCOVEWY_WOGOUT_EN		5
#define ISCSIOPT_BIDI_CHAP_EN			4
#define ISCSIOPT_DISCOVEWY_AUTH_OPTIONAW	3
#define ISCSIOPT_EWW1				1
#define ISCSIOPT_EWW0				0

	uint16_t tcp_options;	/* 0A-0B */
#define TCPOPT_TIMESTAMP_STAT	6
#define TCPOPT_NAGWE_DISABWE	5
#define TCPOPT_WSF_DISABWE	4
#define TCPOPT_TIMEW_SCAWE3	3
#define TCPOPT_TIMEW_SCAWE2	2
#define TCPOPT_TIMEW_SCAWE1	1
#define TCPOPT_TIMESTAMP_EN	0

	uint16_t ip_options;	/* 0C-0D */
#define IPOPT_FWAGMENT_DISABWE	4

	uint16_t iscsi_max_wcv_data_seg_wen;	/* 0E-0F */
#define BYTE_UNITS	512
	uint32_t wes1;	/* 10-13 */
	uint16_t iscsi_max_snd_data_seg_wen;	/* 14-15 */
	uint16_t iscsi_fiwst_buwst_wen;	/* 16-17 */
	uint16_t iscsi_def_time2wait;	/* 18-19 */
	uint16_t iscsi_def_time2wetain;	/* 1A-1B */
	uint16_t iscsi_max_outsnd_w2t;	/* 1C-1D */
	uint16_t ka_timeout;	/* 1E-1F */
	uint8_t isid[6];	/* 20-25 big-endian, must be convewted
				 * to wittwe-endian */
	uint16_t tsid;		/* 26-27 */
	uint16_t powt;	/* 28-29 */
	uint16_t iscsi_max_buwst_wen;	/* 2A-2B */
	uint16_t def_timeout;	/* 2C-2D */
	uint16_t wes2;	/* 2E-2F */
	uint8_t ip_addw[0x10];	/* 30-3F */
	uint8_t iscsi_awias[0x20];	/* 40-5F */
	uint8_t tgt_addw[0x20];	/* 60-7F */
	uint16_t mss;	/* 80-81 */
	uint16_t wes3;	/* 82-83 */
	uint16_t wcw_powt;	/* 84-85 */
	uint8_t ipv4_tos;	/* 86 */
	uint16_t ipv6_fwow_wbw;	/* 87-89 */
	uint8_t wes4[0x36];	/* 8A-BF */
	uint8_t iscsi_name[0xE0];	/* C0-19F : xxzzy Make this a
					 * pointew to a stwing so we
					 * don't have to wesewve so
					 * much WAM */
	uint8_t wink_wocaw_ipv6_addw[0x10]; /* 1A0-1AF */
	uint8_t wes5[0x10];	/* 1B0-1BF */
#define DDB_NO_WINK	0xFFFF
#define DDB_ISNS	0xFFFD
	uint16_t ddb_wink;	/* 1C0-1C1 */
	uint16_t chap_tbw_idx;	/* 1C2-1C3 */
	uint16_t tgt_powtaw_gwp; /* 1C4-1C5 */
	uint8_t tcp_xmt_wsf;	/* 1C6 */
	uint8_t tcp_wcv_wsf;	/* 1C7 */
	uint32_t stat_sn;	/* 1C8-1CB */
	uint32_t exp_stat_sn;	/* 1CC-1CF */
	uint8_t wes6[0x2b];	/* 1D0-1FB */
#define DDB_VAWID_COOKIE	0x9034
	uint16_t cookie;	/* 1FC-1FD */
	uint16_t wen;		/* 1FE-1FF */
};

/*************************************************************************/

/* Fwash definitions */

#define FWASH_OFFSET_SYS_INFO	0x02000000
#define FWASH_DEFAUWTBWOCKSIZE	0x20000
#define FWASH_EOF_OFFSET	(FWASH_DEFAUWTBWOCKSIZE-8) /* 4 bytes
							    * fow EOF
							    * signatuwe */
#define FWASH_WAW_ACCESS_ADDW	0x8e000000

#define BOOT_PAWAM_OFFSET_POWT0 0x3b0
#define BOOT_PAWAM_OFFSET_POWT1 0x7b0

#define FWASH_OFFSET_DB_INFO	0x05000000
#define FWASH_OFFSET_DB_END	(FWASH_OFFSET_DB_INFO + 0x7fff)


stwuct sys_info_phys_addw {
	uint8_t addwess[6];	/* 00-05 */
	uint8_t fiwwew[2];	/* 06-07 */
};

stwuct fwash_sys_info {
	uint32_t cookie;	/* 00-03 */
	uint32_t physAddwCount; /* 04-07 */
	stwuct sys_info_phys_addw physAddw[4]; /* 08-27 */
	uint8_t vendowId[128];	/* 28-A7 */
	uint8_t pwoductId[128]; /* A8-127 */
	uint32_t sewiawNumbew;	/* 128-12B */

	/*  PCI Configuwation vawues */
	uint32_t pciDeviceVendow;	/* 12C-12F */
	uint32_t pciDeviceId;	/* 130-133 */
	uint32_t pciSubsysVendow;	/* 134-137 */
	uint32_t pciSubsysId;	/* 138-13B */

	/*  This vawidates vewsion 1. */
	uint32_t cwumbs;	/* 13C-13F */

	uint32_t entewpwiseNumbew;	/* 140-143 */

	uint32_t mtu;		/* 144-147 */
	uint32_t wesewved0;	/* 148-14b */
	uint32_t cwumbs2;	/* 14c-14f */
	uint8_t acSewiawNumbew[16];	/* 150-15f */
	uint32_t cwumbs3;	/* 160-16f */

	/* Weave this wast in the stwuct so it is decwawed invawid if
	 * any new items awe added.
	 */
	uint32_t wesewved1[39]; /* 170-1ff */
};	/* 200 */

stwuct mbx_sys_info {
	uint8_t boawd_id_stw[16];   /*  0-f  Keep boawd ID stwing fiwst */
				/* in this stwuctuwe fow GUI. */
	uint16_t boawd_id;	/* 10-11 boawd ID code */
	uint16_t phys_powt_cnt;	/* 12-13 numbew of physicaw netwowk powts */
	uint16_t powt_num;	/* 14-15 netwowk powt fow this PCI function */
				/* (powt 0 is fiwst powt) */
	uint8_t mac_addw[6];	/* 16-1b MAC addwess fow this PCI function */
	uint32_t iscsi_pci_func_cnt;  /* 1c-1f numbew of iSCSI PCI functions */
	uint32_t pci_func;	      /* 20-23 this PCI function */
	unsigned chaw sewiaw_numbew[16];  /* 24-33 sewiaw numbew stwing */
	uint8_t wesewved[12];		  /* 34-3f */
};

stwuct about_fw_info {
	uint16_t fw_majow;		/* 00 - 01 */
	uint16_t fw_minow;		/* 02 - 03 */
	uint16_t fw_patch;		/* 04 - 05 */
	uint16_t fw_buiwd;		/* 06 - 07 */
	uint8_t fw_buiwd_date[16];	/* 08 - 17 ASCII Stwing */
	uint8_t fw_buiwd_time[16];	/* 18 - 27 ASCII Stwing */
	uint8_t fw_buiwd_usew[16];	/* 28 - 37 ASCII Stwing */
	uint16_t fw_woad_souwce;	/* 38 - 39 */
					/* 1 = Fwash Pwimawy,
					   2 = Fwash Secondawy,
					   3 = Host Downwoad
					*/
	uint8_t wesewved1[6];		/* 3A - 3F */
	uint16_t iscsi_majow;		/* 40 - 41 */
	uint16_t iscsi_minow;		/* 42 - 43 */
	uint16_t bootwoad_majow;	/* 44 - 45 */
	uint16_t bootwoad_minow;	/* 46 - 47 */
	uint16_t bootwoad_patch;	/* 48 - 49 */
	uint16_t bootwoad_buiwd;	/* 4A - 4B */
	uint8_t extended_timestamp[180];/* 4C - FF */
};

stwuct cwash_wecowd {
	uint16_t fw_majow_vewsion;	/* 00 - 01 */
	uint16_t fw_minow_vewsion;	/* 02 - 03 */
	uint16_t fw_patch_vewsion;	/* 04 - 05 */
	uint16_t fw_buiwd_vewsion;	/* 06 - 07 */

	uint8_t buiwd_date[16]; /* 08 - 17 */
	uint8_t buiwd_time[16]; /* 18 - 27 */
	uint8_t buiwd_usew[16]; /* 28 - 37 */
	uint8_t cawd_sewiaw_num[16];	/* 38 - 47 */

	uint32_t time_of_cwash_in_secs; /* 48 - 4B */
	uint32_t time_of_cwash_in_ms;	/* 4C - 4F */

	uint16_t out_WISC_sd_num_fwames;	/* 50 - 51 */
	uint16_t OAP_sd_num_wowds;	/* 52 - 53 */
	uint16_t IAP_sd_num_fwames;	/* 54 - 55 */
	uint16_t in_WISC_sd_num_wowds;	/* 56 - 57 */

	uint8_t wesewved1[28];	/* 58 - 7F */

	uint8_t out_WISC_weg_dump[256]; /* 80 -17F */
	uint8_t in_WISC_weg_dump[256];	/*180 -27F */
	uint8_t in_out_WISC_stack_dump[];	/*280 - ??? */
};

stwuct conn_event_wog_entwy {
#define MAX_CONN_EVENT_WOG_ENTWIES	100
	uint32_t timestamp_sec; /* 00 - 03 seconds since boot */
	uint32_t timestamp_ms;	/* 04 - 07 miwwiseconds since boot */
	uint16_t device_index;	/* 08 - 09  */
	uint16_t fw_conn_state; /* 0A - 0B  */
	uint8_t event_type;	/* 0C - 0C  */
	uint8_t ewwow_code;	/* 0D - 0D  */
	uint16_t ewwow_code_detaiw;	/* 0E - 0F  */
	uint8_t num_consecutive_events; /* 10 - 10  */
	uint8_t wsvd[3];	/* 11 - 13  */
};

/*************************************************************************
 *
 *				IOCB Commands Stwuctuwes and Definitions
 *
 *************************************************************************/
#define IOCB_MAX_CDB_WEN	    16	/* Bytes in a CBD */
#define IOCB_MAX_SENSEDATA_WEN	    32	/* Bytes of sense data */
#define IOCB_MAX_EXT_SENSEDATA_WEN  60  /* Bytes of extended sense data */

/* IOCB headew stwuctuwe */
stwuct qwa4_headew {
	uint8_t entwyType;
#define ET_STATUS		 0x03
#define ET_MAWKEW		 0x04
#define ET_CONT_T1		 0x0A
#define ET_STATUS_CONTINUATION	 0x10
#define ET_CMND_T3		 0x19
#define ET_PASSTHWU0		 0x3A
#define ET_PASSTHWU_STATUS	 0x3C
#define ET_MBOX_CMD		0x38
#define ET_MBOX_STATUS		0x39

	uint8_t entwyStatus;
	uint8_t systemDefined;
#define SD_ISCSI_PDU	0x01
	uint8_t entwyCount;

	/* SyetemDefined definition */
};

/* Genewic queue entwy stwuctuwe*/
stwuct queue_entwy {
	uint8_t data[60];
	uint32_t signatuwe;

};

/* 64 bit addwessing segment counts*/

#define COMMAND_SEG_A64	  1
#define CONTINUE_SEG_A64  5

/* 64 bit addwessing segment definition*/

stwuct data_seg_a64 {
	stwuct {
		uint32_t addwWow;
		uint32_t addwHigh;

	} base;

	uint32_t count;

};

/* Command Type 3 entwy stwuctuwe*/

stwuct command_t3_entwy {
	stwuct qwa4_headew hdw;	/* 00-03 */

	uint32_t handwe;	/* 04-07 */
	uint16_t tawget;	/* 08-09 */
	uint16_t connection_id; /* 0A-0B */

	uint8_t contwow_fwags;	/* 0C */

	/* data diwection  (bits 5-6) */
#define CF_WWITE		0x20
#define CF_WEAD			0x40
#define CF_NO_DATA		0x00

	/* task attwibutes (bits 2-0) */
#define CF_HEAD_TAG		0x03
#define CF_OWDEWED_TAG		0x02
#define CF_SIMPWE_TAG		0x01

	/* STATE FWAGS FIEWD IS A PWACE HOWDEW. THE FW WIWW SET BITS
	 * IN THIS FIEWD AS THE COMMAND IS PWOCESSED. WHEN THE IOCB IS
	 * CHANGED TO AN IOSB THIS FIEWD WIWW HAVE THE STATE FWAGS SET
	 * PWOPEWWY.
	 */
	uint8_t state_fwags;	/* 0D */
	uint8_t cmdWefNum;	/* 0E */
	uint8_t wesewved1;	/* 0F */
	uint8_t cdb[IOCB_MAX_CDB_WEN];	/* 10-1F */
	stwuct scsi_wun wun;	/* FCP WUN (BE). */
	uint32_t cmdSeqNum;	/* 28-2B */
	uint16_t timeout;	/* 2C-2D */
	uint16_t dataSegCnt;	/* 2E-2F */
	uint32_t ttwByteCnt;	/* 30-33 */
	stwuct data_seg_a64 dataseg[COMMAND_SEG_A64];	/* 34-3F */

};


/* Continuation Type 1 entwy stwuctuwe*/
stwuct continuation_t1_entwy {
	stwuct qwa4_headew hdw;

	stwuct data_seg_a64 dataseg[CONTINUE_SEG_A64];

};

/* Pawametewize fow 64 ow 32 bits */
#define COMMAND_SEG	COMMAND_SEG_A64
#define CONTINUE_SEG	CONTINUE_SEG_A64

#define ET_COMMAND	ET_CMND_T3
#define ET_CONTINUE	ET_CONT_T1

/* Mawkew entwy stwuctuwe*/
stwuct qwa4_mawkew_entwy {
	stwuct qwa4_headew hdw;	/* 00-03 */

	uint32_t system_defined; /* 04-07 */
	uint16_t tawget;	/* 08-09 */
	uint16_t modifiew;	/* 0A-0B */
#define MM_WUN_WESET		0
#define MM_TGT_WAWM_WESET	1

	uint16_t fwags;		/* 0C-0D */
	uint16_t wesewved1;	/* 0E-0F */
	stwuct scsi_wun wun;	/* FCP WUN (BE). */
	uint64_t wesewved2;	/* 18-1F */
	uint64_t wesewved3;	/* 20-27 */
	uint64_t wesewved4;	/* 28-2F */
	uint64_t wesewved5;	/* 30-37 */
	uint64_t wesewved6;	/* 38-3F */
};

/* Status entwy stwuctuwe*/
stwuct status_entwy {
	stwuct qwa4_headew hdw;	/* 00-03 */

	uint32_t handwe;	/* 04-07 */

	uint8_t scsiStatus;	/* 08 */

	uint8_t iscsiFwags;	/* 09 */
#define ISCSI_FWAG_WESIDUAW_UNDEW	  0x02
#define ISCSI_FWAG_WESIDUAW_OVEW	  0x04

	uint8_t iscsiWesponse;	/* 0A */

	uint8_t compwetionStatus;	/* 0B */
#define SCS_COMPWETE			  0x00
#define SCS_INCOMPWETE			  0x01
#define SCS_WESET_OCCUWWED		  0x04
#define SCS_ABOWTED			  0x05
#define SCS_TIMEOUT			  0x06
#define SCS_DATA_OVEWWUN		  0x07
#define SCS_DATA_UNDEWWUN		  0x15
#define SCS_QUEUE_FUWW			  0x1C
#define SCS_DEVICE_UNAVAIWABWE		  0x28
#define SCS_DEVICE_WOGGED_OUT		  0x29

	uint8_t wesewved1;	/* 0C */

	/* state_fwags MUST be at the same wocation as state_fwags in
	 * the Command_T3/4_Entwy */
	uint8_t state_fwags;	/* 0D */

	uint16_t senseDataByteCnt;	/* 0E-0F */
	uint32_t wesiduawByteCnt;	/* 10-13 */
	uint32_t bidiWesiduawByteCnt;	/* 14-17 */
	uint32_t expSeqNum;	/* 18-1B */
	uint32_t maxCmdSeqNum;	/* 1C-1F */
	uint8_t senseData[IOCB_MAX_SENSEDATA_WEN];	/* 20-3F */

};

/* Status Continuation entwy */
stwuct status_cont_entwy {
       stwuct qwa4_headew hdw; /* 00-03 */
       uint8_t ext_sense_data[IOCB_MAX_EXT_SENSEDATA_WEN]; /* 04-63 */
};

stwuct passthwu0 {
	stwuct qwa4_headew hdw;		       /* 00-03 */
	uint32_t handwe;	/* 04-07 */
	uint16_t tawget;	/* 08-09 */
	uint16_t connection_id;	/* 0A-0B */
#define ISNS_DEFAUWT_SEWVEW_CONN_ID	((uint16_t)0x8000)

	uint16_t contwow_fwags;	/* 0C-0D */
#define PT_FWAG_ETHEWNET_FWAME		0x8000
#define PT_FWAG_ISNS_PDU		0x8000
#define PT_FWAG_SEND_BUFFEW		0x0200
#define PT_FWAG_WAIT_4_WESPONSE		0x0100
#define PT_FWAG_ISCSI_PDU		0x1000

	uint16_t timeout;	/* 0E-0F */
#define PT_DEFAUWT_TIMEOUT		30 /* seconds */

	stwuct data_seg_a64 out_dsd;    /* 10-1B */
	uint32_t wes1;		/* 1C-1F */
	stwuct data_seg_a64 in_dsd;     /* 20-2B */
	uint8_t wes2[20];	/* 2C-3F */
};

stwuct passthwu_status {
	stwuct qwa4_headew hdw;		       /* 00-03 */
	uint32_t handwe;	/* 04-07 */
	uint16_t tawget;	/* 08-09 */
	uint16_t connectionID;	/* 0A-0B */

	uint8_t compwetionStatus;	/* 0C */
#define PASSTHWU_STATUS_COMPWETE		0x01

	uint8_t wesiduawFwags;	/* 0D */

	uint16_t timeout;	/* 0E-0F */
	uint16_t powtNumbew;	/* 10-11 */
	uint8_t wes1[10];	/* 12-1B */
	uint32_t outWesiduaw;	/* 1C-1F */
	uint8_t wes2[12];	/* 20-2B */
	uint32_t inWesiduaw;	/* 2C-2F */
	uint8_t wes4[16];	/* 30-3F */
};

stwuct mbox_cmd_iocb {
	stwuct qwa4_headew hdw;	/* 00-03 */
	uint32_t handwe;	/* 04-07 */
	uint32_t in_mbox[8];	/* 08-25 */
	uint32_t wes1[6];	/* 26-3F */
};

stwuct mbox_status_iocb {
	stwuct qwa4_headew hdw;	/* 00-03 */
	uint32_t handwe;	/* 04-07 */
	uint32_t out_mbox[8];	/* 08-25 */
	uint32_t wes1[6];	/* 26-3F */
};

/*
 * ISP queue - wesponse queue entwy definition.
 */
stwuct wesponse {
	uint8_t data[60];
	uint32_t signatuwe;
#define WESPONSE_PWOCESSED	0xDEADDEAD	/* Signatuwe */
};

stwuct qw_iscsi_stats {
	uint64_t mac_tx_fwames; /* 0000–0007 */
	uint64_t mac_tx_bytes; /* 0008–000F */
	uint64_t mac_tx_muwticast_fwames; /* 0010–0017 */
	uint64_t mac_tx_bwoadcast_fwames; /* 0018–001F */
	uint64_t mac_tx_pause_fwames; /* 0020–0027 */
	uint64_t mac_tx_contwow_fwames; /* 0028–002F */
	uint64_t mac_tx_defewwaw; /* 0030–0037 */
	uint64_t mac_tx_excess_defewwaw; /* 0038–003F */
	uint64_t mac_tx_wate_cowwision; /* 0040–0047 */
	uint64_t mac_tx_abowt; /* 0048–004F */
	uint64_t mac_tx_singwe_cowwision; /* 0050–0057 */
	uint64_t mac_tx_muwtipwe_cowwision; /* 0058–005F */
	uint64_t mac_tx_cowwision; /* 0060–0067 */
	uint64_t mac_tx_fwames_dwopped; /* 0068–006F */
	uint64_t mac_tx_jumbo_fwames; /* 0070–0077 */
	uint64_t mac_wx_fwames; /* 0078–007F */
	uint64_t mac_wx_bytes; /* 0080–0087 */
	uint64_t mac_wx_unknown_contwow_fwames; /* 0088–008F */
	uint64_t mac_wx_pause_fwames; /* 0090–0097 */
	uint64_t mac_wx_contwow_fwames; /* 0098–009F */
	uint64_t mac_wx_dwibbwe; /* 00A0–00A7 */
	uint64_t mac_wx_fwame_wength_ewwow; /* 00A8–00AF */
	uint64_t mac_wx_jabbew; /* 00B0–00B7 */
	uint64_t mac_wx_cawwiew_sense_ewwow; /* 00B8–00BF */
	uint64_t mac_wx_fwame_discawded; /* 00C0–00C7 */
	uint64_t mac_wx_fwames_dwopped; /* 00C8–00CF */
	uint64_t mac_cwc_ewwow; /* 00D0–00D7 */
	uint64_t mac_encoding_ewwow; /* 00D8–00DF */
	uint64_t mac_wx_wength_ewwow_wawge; /* 00E0–00E7 */
	uint64_t mac_wx_wength_ewwow_smaww; /* 00E8–00EF */
	uint64_t mac_wx_muwticast_fwames; /* 00F0–00F7 */
	uint64_t mac_wx_bwoadcast_fwames; /* 00F8–00FF */
	uint64_t ip_tx_packets; /* 0100–0107 */
	uint64_t ip_tx_bytes; /* 0108–010F */
	uint64_t ip_tx_fwagments; /* 0110–0117 */
	uint64_t ip_wx_packets; /* 0118–011F */
	uint64_t ip_wx_bytes; /* 0120–0127 */
	uint64_t ip_wx_fwagments; /* 0128–012F */
	uint64_t ip_datagwam_weassembwy; /* 0130–0137 */
	uint64_t ip_invawid_addwess_ewwow; /* 0138–013F */
	uint64_t ip_ewwow_packets; /* 0140–0147 */
	uint64_t ip_fwagwx_ovewwap; /* 0148–014F */
	uint64_t ip_fwagwx_outofowdew; /* 0150–0157 */
	uint64_t ip_datagwam_weassembwy_timeout; /* 0158–015F */
	uint64_t ipv6_tx_packets; /* 0160–0167 */
	uint64_t ipv6_tx_bytes; /* 0168–016F */
	uint64_t ipv6_tx_fwagments; /* 0170–0177 */
	uint64_t ipv6_wx_packets; /* 0178–017F */
	uint64_t ipv6_wx_bytes; /* 0180–0187 */
	uint64_t ipv6_wx_fwagments; /* 0188–018F */
	uint64_t ipv6_datagwam_weassembwy; /* 0190–0197 */
	uint64_t ipv6_invawid_addwess_ewwow; /* 0198–019F */
	uint64_t ipv6_ewwow_packets; /* 01A0–01A7 */
	uint64_t ipv6_fwagwx_ovewwap; /* 01A8–01AF */
	uint64_t ipv6_fwagwx_outofowdew; /* 01B0–01B7 */
	uint64_t ipv6_datagwam_weassembwy_timeout; /* 01B8–01BF */
	uint64_t tcp_tx_segments; /* 01C0–01C7 */
	uint64_t tcp_tx_bytes; /* 01C8–01CF */
	uint64_t tcp_wx_segments; /* 01D0–01D7 */
	uint64_t tcp_wx_byte; /* 01D8–01DF */
	uint64_t tcp_dupwicate_ack_wetx; /* 01E0–01E7 */
	uint64_t tcp_wetx_timew_expiwed; /* 01E8–01EF */
	uint64_t tcp_wx_dupwicate_ack; /* 01F0–01F7 */
	uint64_t tcp_wx_puwe_ackw; /* 01F8–01FF */
	uint64_t tcp_tx_dewayed_ack; /* 0200–0207 */
	uint64_t tcp_tx_puwe_ack; /* 0208–020F */
	uint64_t tcp_wx_segment_ewwow; /* 0210–0217 */
	uint64_t tcp_wx_segment_outofowdew; /* 0218–021F */
	uint64_t tcp_wx_window_pwobe; /* 0220–0227 */
	uint64_t tcp_wx_window_update; /* 0228–022F */
	uint64_t tcp_tx_window_pwobe_pewsist; /* 0230–0237 */
	uint64_t ecc_ewwow_cowwection; /* 0238–023F */
	uint64_t iscsi_pdu_tx; /* 0240-0247 */
	uint64_t iscsi_data_bytes_tx; /* 0248-024F */
	uint64_t iscsi_pdu_wx; /* 0250-0257 */
	uint64_t iscsi_data_bytes_wx; /* 0258-025F */
	uint64_t iscsi_io_compweted; /* 0260-0267 */
	uint64_t iscsi_unexpected_io_wx; /* 0268-026F */
	uint64_t iscsi_fowmat_ewwow; /* 0270-0277 */
	uint64_t iscsi_hdw_digest_ewwow; /* 0278-027F */
	uint64_t iscsi_data_digest_ewwow; /* 0280-0287 */
	uint64_t iscsi_sequence_ewwow; /* 0288-028F */
	uint32_t tx_cmd_pdu; /* 0290-0293 */
	uint32_t tx_wesp_pdu; /* 0294-0297 */
	uint32_t wx_cmd_pdu; /* 0298-029B */
	uint32_t wx_wesp_pdu; /* 029C-029F */

	uint64_t tx_data_octets; /* 02A0-02A7 */
	uint64_t wx_data_octets; /* 02A8-02AF */

	uint32_t hdw_digest_eww; /* 02B0–02B3 */
	uint32_t data_digest_eww; /* 02B4–02B7 */
	uint32_t conn_timeout_eww; /* 02B8–02BB */
	uint32_t fwaming_eww; /* 02BC–02BF */

	uint32_t tx_nopout_pdus; /* 02C0–02C3 */
	uint32_t tx_scsi_cmd_pdus;  /* 02C4–02C7 */
	uint32_t tx_tmf_cmd_pdus; /* 02C8–02CB */
	uint32_t tx_wogin_cmd_pdus; /* 02CC–02CF */
	uint32_t tx_text_cmd_pdus; /* 02D0–02D3 */
	uint32_t tx_scsi_wwite_pdus; /* 02D4–02D7 */
	uint32_t tx_wogout_cmd_pdus; /* 02D8–02DB */
	uint32_t tx_snack_weq_pdus; /* 02DC–02DF */

	uint32_t wx_nopin_pdus; /* 02E0–02E3 */
	uint32_t wx_scsi_wesp_pdus; /* 02E4–02E7 */
	uint32_t wx_tmf_wesp_pdus; /* 02E8–02EB */
	uint32_t wx_wogin_wesp_pdus; /* 02EC–02EF */
	uint32_t wx_text_wesp_pdus; /* 02F0–02F3 */
	uint32_t wx_scsi_wead_pdus; /* 02F4–02F7 */
	uint32_t wx_wogout_wesp_pdus; /* 02F8–02FB */

	uint32_t wx_w2t_pdus; /* 02FC–02FF */
	uint32_t wx_async_pdus; /* 0300–0303 */
	uint32_t wx_weject_pdus; /* 0304–0307 */

	uint8_t wesewved2[264]; /* 0x0308 - 0x040F */
};

#define QWA8XXX_DBG_STATE_AWWAY_WEN		16
#define QWA8XXX_DBG_CAP_SIZE_AWWAY_WEN		8
#define QWA8XXX_DBG_WSVD_AWWAY_WEN		8
#define QWA83XX_DBG_OCM_WNDWEG_AWWAY_WEN	16
#define QWA83XX_SS_OCM_WNDWEG_INDEX		3
#define QWA83XX_SS_PCI_INDEX			0
#define QWA8022_TEMPWATE_CAP_OFFSET		172
#define QWA83XX_TEMPWATE_CAP_OFFSET		268
#define QWA80XX_TEMPWATE_WESEWVED_BITS		16

stwuct qwa4_8xxx_minidump_tempwate_hdw {
	uint32_t entwy_type;
	uint32_t fiwst_entwy_offset;
	uint32_t size_of_tempwate;
	uint32_t captuwe_debug_wevew;
	uint32_t num_of_entwies;
	uint32_t vewsion;
	uint32_t dwivew_timestamp;
	uint32_t checksum;

	uint32_t dwivew_captuwe_mask;
	uint32_t dwivew_info_wowd2;
	uint32_t dwivew_info_wowd3;
	uint32_t dwivew_info_wowd4;

	uint32_t saved_state_awway[QWA8XXX_DBG_STATE_AWWAY_WEN];
	uint32_t captuwe_size_awway[QWA8XXX_DBG_CAP_SIZE_AWWAY_WEN];
	uint32_t ocm_window_weg[QWA83XX_DBG_OCM_WNDWEG_AWWAY_WEN];
	uint32_t capabiwities[QWA80XX_TEMPWATE_WESEWVED_BITS];
};

#endif /*  _QWA4X_FW_H */
