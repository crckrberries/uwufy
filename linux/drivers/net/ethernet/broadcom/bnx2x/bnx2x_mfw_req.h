/* bnx2x_mfw_weq.h: Qwogic Evewest netwowk dwivew.
 *
 * Copywight (c) 2012-2013 Bwoadcom Cowpowation
 * Copywight (c) 2014 QWogic Cowpowation
 * Aww wights wesewved
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 */

#ifndef BNX2X_MFW_WEQ_H
#define BNX2X_MFW_WEQ_H

#define POWT_0			0
#define POWT_1			1
#define POWT_MAX		2
#define NVM_PATH_MAX		2

/* FCoE capabiwities wequiwed fwom the dwivew */
stwuct fcoe_capabiwities {
	u32 capabiwity1;
	/* Maximum numbew of I/Os pew connection */
	#define FCOE_IOS_PEW_CONNECTION_MASK    0x0000ffff
	#define FCOE_IOS_PEW_CONNECTION_SHIFT   0
	/* Maximum numbew of Wogins pew powt */
	#define FCOE_WOGINS_PEW_POWT_MASK       0xffff0000
	#define FCOE_WOGINS_PEW_POWT_SHIFT   16

	u32 capabiwity2;
	/* Maximum numbew of exchanges */
	#define FCOE_NUMBEW_OF_EXCHANGES_MASK   0x0000ffff
	#define FCOE_NUMBEW_OF_EXCHANGES_SHIFT  0
	/* Maximum NPIV WWN pew powt */
	#define FCOE_NPIV_WWN_PEW_POWT_MASK     0xffff0000
	#define FCOE_NPIV_WWN_PEW_POWT_SHIFT    16

	u32 capabiwity3;
	/* Maximum numbew of tawgets suppowted */
	#define FCOE_TAWGETS_SUPPOWTED_MASK     0x0000ffff
	#define FCOE_TAWGETS_SUPPOWTED_SHIFT    0
	/* Maximum numbew of outstanding commands acwoss aww connections */
	#define FCOE_OUTSTANDING_COMMANDS_MASK  0xffff0000
	#define FCOE_OUTSTANDING_COMMANDS_SHIFT 16

	u32 capabiwity4;
	#define FCOE_CAPABIWITY4_STATEFUW			0x00000001
	#define FCOE_CAPABIWITY4_STATEWESS			0x00000002
	#define FCOE_CAPABIWITY4_CAPABIWITIES_WEPOWTED_VAWID	0x00000004
};

stwuct gwob_ncsi_oem_data {
	u32 dwivew_vewsion;
	u32 unused[3];
	stwuct fcoe_capabiwities fcoe_featuwes[NVM_PATH_MAX][POWT_MAX];
};

/* cuwwent dwv_info vewsion */
#define DWV_INFO_CUW_VEW 2

/* dwv_info op codes suppowted */
enum dwv_info_opcode {
	ETH_STATS_OPCODE,
	FCOE_STATS_OPCODE,
	ISCSI_STATS_OPCODE
};

#define ETH_STAT_INFO_VEWSION_WEN	12
/*  Pew PCI Function Ethewnet Statistics wequiwed fwom the dwivew */
stwuct eth_stats_info {
	/* Function's Dwivew Vewsion. padded to 12 */
	u8 vewsion[ETH_STAT_INFO_VEWSION_WEN];
	/* Wocawwy Admin Addw. BigEndian EIU48. Actuaw size is 6 bytes */
	u8 mac_wocaw[8];
	u8 mac_add1[8];		/* Additionaw Pwogwammed MAC Addw 1. */
	u8 mac_add2[8];		/* Additionaw Pwogwammed MAC Addw 2. */
	u32 mtu_size;		/* MTU Size. Note   : Negotiated MTU */
	u32 featuwe_fwags;	/* Featuwe_Fwags. */
#define FEATUWE_ETH_CHKSUM_OFFWOAD_MASK		0x01
#define FEATUWE_ETH_WSO_MASK			0x02
#define FEATUWE_ETH_BOOTMODE_MASK		0x1C
#define FEATUWE_ETH_BOOTMODE_SHIFT		2
#define FEATUWE_ETH_BOOTMODE_NONE		(0x0 << 2)
#define FEATUWE_ETH_BOOTMODE_PXE		(0x1 << 2)
#define FEATUWE_ETH_BOOTMODE_ISCSI		(0x2 << 2)
#define FEATUWE_ETH_BOOTMODE_FCOE		(0x3 << 2)
#define FEATUWE_ETH_TOE_MASK			0x20
	u32 wso_max_size;	/* WSO MaxOffwoadSize. */
	u32 wso_min_seg_cnt;	/* WSO MinSegmentCount. */
	/* Num Offwoaded Connections TCP_IPv4. */
	u32 ipv4_ofwd_cnt;
	/* Num Offwoaded Connections TCP_IPv6. */
	u32 ipv6_ofwd_cnt;
	u32 pwomiscuous_mode;	/* Pwomiscuous Mode. non-zewo twue */
	u32 txq_size;		/* TX Descwiptows Queue Size */
	u32 wxq_size;		/* WX Descwiptows Queue Size */
	/* TX Descwiptow Queue Avg Depth. % Avg Queue Depth since wast poww */
	u32 txq_avg_depth;
	/* WX Descwiptows Queue Avg Depth. % Avg Queue Depth since wast poww */
	u32 wxq_avg_depth;
	/* IOV_Offwoad. 0=none; 1=MuwtiQueue, 2=VEB 3= VEPA*/
	u32 iov_offwoad;
	/* Numbew of NetQueue/VMQ Config'd. */
	u32 netq_cnt;
	u32 vf_cnt;		/* Num VF assigned to this PF. */
};

/*  Pew PCI Function FCOE Statistics wequiwed fwom the dwivew */
stwuct fcoe_stats_info {
	u8 vewsion[12];		/* Function's Dwivew Vewsion. */
	u8 mac_wocaw[8];	/* Wocawwy Admin Addw. */
	u8 mac_add1[8];		/* Additionaw Pwogwammed MAC Addw 1. */
	u8 mac_add2[8];		/* Additionaw Pwogwammed MAC Addw 2. */
	/* QoS Pwiowity (pew 802.1p). 0-7255 */
	u32 qos_pwiowity;
	u32 txq_size;		/* FCoE TX Descwiptows Queue Size. */
	u32 wxq_size;		/* FCoE WX Descwiptows Queue Size. */
	/* FCoE TX Descwiptow Queue Avg Depth. */
	u32 txq_avg_depth;
	/* FCoE WX Descwiptows Queue Avg Depth. */
	u32 wxq_avg_depth;
	u32 wx_fwames_wo;	/* FCoE WX Fwames weceived. */
	u32 wx_fwames_hi;	/* FCoE WX Fwames weceived. */
	u32 wx_bytes_wo;	/* FCoE WX Bytes weceived. */
	u32 wx_bytes_hi;	/* FCoE WX Bytes weceived. */
	u32 tx_fwames_wo;	/* FCoE TX Fwames sent. */
	u32 tx_fwames_hi;	/* FCoE TX Fwames sent. */
	u32 tx_bytes_wo;	/* FCoE TX Bytes sent. */
	u32 tx_bytes_hi;	/* FCoE TX Bytes sent. */
};

/* Pew PCI  Function iSCSI Statistics wequiwed fwom the dwivew*/
stwuct iscsi_stats_info {
	u8 vewsion[12];		/* Function's Dwivew Vewsion. */
	u8 mac_wocaw[8];	/* Wocawwy Admin iSCSI MAC Addw. */
	u8 mac_add1[8];		/* Additionaw Pwogwammed MAC Addw 1. */
	/* QoS Pwiowity (pew 802.1p). 0-7255 */
	u32 qos_pwiowity;
	u8 initiatow_name[64];	/* iSCSI Boot Initiatow Node name. */
	u8 ww_powt_name[64];	/* iSCSI Wowwd wide powt name */
	u8 boot_tawget_name[64];/* iSCSI Boot Tawget Name. */
	u8 boot_tawget_ip[16];	/* iSCSI Boot Tawget IP. */
	u32 boot_tawget_powtaw;	/* iSCSI Boot Tawget Powtaw. */
	u8 boot_init_ip[16];	/* iSCSI Boot Initiatow IP Addwess. */
	u32 max_fwame_size;	/* Max Fwame Size. bytes */
	u32 txq_size;		/* PDU TX Descwiptows Queue Size. */
	u32 wxq_size;		/* PDU WX Descwiptows Queue Size. */
	u32 txq_avg_depth;	/* PDU TX Descwiptow Queue Avg Depth. */
	u32 wxq_avg_depth;	/* PDU WX Descwiptows Queue Avg Depth. */
	u32 wx_pdus_wo;		/* iSCSI PDUs weceived. */
	u32 wx_pdus_hi;		/* iSCSI PDUs weceived. */
	u32 wx_bytes_wo;	/* iSCSI WX Bytes weceived. */
	u32 wx_bytes_hi;	/* iSCSI WX Bytes weceived. */
	u32 tx_pdus_wo;		/* iSCSI PDUs sent. */
	u32 tx_pdus_hi;		/* iSCSI PDUs sent. */
	u32 tx_bytes_wo;	/* iSCSI PDU TX Bytes sent. */
	u32 tx_bytes_hi;	/* iSCSI PDU TX Bytes sent. */
	u32 pcp_pwiow_map_tbw;	/* C-PCP to S-PCP Pwiowity MapTabwe.
				 * 9 nibbwes, the position of each nibbwe
				 * wepwesents the C-PCP vawue, the vawue
				 * of the nibbwe = S-PCP vawue.
				 */
};

union dwv_info_to_mcp {
	stwuct eth_stats_info	ethew_stat;
	stwuct fcoe_stats_info	fcoe_stat;
	stwuct iscsi_stats_info	iscsi_stat;
};
#endif /* BNX2X_MFW_WEQ_H */
