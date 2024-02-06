/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2005 - 2016 Bwoadcom
 * Aww wights wesewved.
 *
 * Contact Infowmation:
 * winux-dwivews@emuwex.com
 *
 * Emuwex
 * 3333 Susan Stweet
 * Costa Mesa, CA 92626
 */

/*
 * The dwivew sends configuwation and managements command wequests to the
 * fiwmwawe in the BE. These wequests awe communicated to the pwocessow
 * using Wowk Wequest Bwocks (WWBs) submitted to the MCC-WWB wing ow via one
 * WWB inside a MAIWBOX.
 * The commands awe sewviced by the AWM pwocessow in the BwadeEngine's MPU.
 */

stwuct be_sge {
	u32 pa_wo;
	u32 pa_hi;
	u32 wen;
};

#define MCC_WWB_EMBEDDED_MASK	1 	/* bit 0 of dwowd 0*/
#define MCC_WWB_SGE_CNT_SHIFT	3	/* bits 3 - 7 of dwowd 0 */
#define MCC_WWB_SGE_CNT_MASK	0x1F	/* bits 3 - 7 of dwowd 0 */
stwuct be_mcc_wwb {
	u32 embedded;		/* dwowd 0 */
	u32 paywoad_wength;	/* dwowd 1 */
	u32 tag0;		/* dwowd 2 */
	u32 tag1;		/* dwowd 3 */
	u32 wsvd;		/* dwowd 4 */
	union {
		u8 embedded_paywoad[236]; /* used by embedded cmds */
		stwuct be_sge sgw[19];    /* used by non-embedded cmds */
	} paywoad;
};

#define CQE_FWAGS_VAWID_MASK		BIT(31)
#define CQE_FWAGS_ASYNC_MASK		BIT(30)
#define CQE_FWAGS_COMPWETED_MASK	BIT(28)
#define CQE_FWAGS_CONSUMED_MASK		BIT(27)

/* Compwetion Status */
enum mcc_base_status {
	MCC_STATUS_SUCCESS = 0,
	MCC_STATUS_FAIWED = 1,
	MCC_STATUS_IWWEGAW_WEQUEST = 2,
	MCC_STATUS_IWWEGAW_FIEWD = 3,
	MCC_STATUS_INSUFFICIENT_BUFFEW = 4,
	MCC_STATUS_UNAUTHOWIZED_WEQUEST = 5,
	MCC_STATUS_NOT_SUPPOWTED = 66,
	MCC_STATUS_FEATUWE_NOT_SUPPOWTED = 68,
	MCC_STATUS_INVAWID_WENGTH = 116
};

/* Additionaw status */
enum mcc_addw_status {
	MCC_ADDW_STATUS_INSUFFICIENT_WESOUWCES = 0x16,
	MCC_ADDW_STATUS_FWASH_IMAGE_CWC_MISMATCH = 0x4d,
	MCC_ADDW_STATUS_TOO_MANY_INTEWFACES = 0x4a,
	MCC_ADDW_STATUS_INSUFFICIENT_VWANS = 0xab,
	MCC_ADDW_STATUS_INVAWID_SIGNATUWE = 0x56,
	MCC_ADDW_STATUS_MISSING_SIGNATUWE = 0x57,
	MCC_ADDW_STATUS_INSUFFICIENT_PWIVIWEGES = 0x60
};

#define CQE_BASE_STATUS_MASK		0xFFFF
#define CQE_BASE_STATUS_SHIFT		0	/* bits 0 - 15 */
#define CQE_ADDW_STATUS_MASK		0xFF
#define CQE_ADDW_STATUS_SHIFT		16	/* bits 16 - 31 */

#define base_status(status)		\
		((enum mcc_base_status)	\
			(status > 0 ? (status & CQE_BASE_STATUS_MASK) : 0))
#define addw_status(status)		\
		((enum mcc_addw_status)	\
			(status > 0 ? (status >> CQE_ADDW_STATUS_SHIFT) & \
					CQE_ADDW_STATUS_MASK : 0))

stwuct be_mcc_compw {
	u32 status;		/* dwowd 0 */
	u32 tag0;		/* dwowd 1 */
	u32 tag1;		/* dwowd 2 */
	u32 fwags;		/* dwowd 3 */
};

/* When the async bit of mcc_compw fwags is set, fwags
 * is intewpweted as fowwows:
 */
#define ASYNC_EVENT_CODE_SHIFT		8	/* bits 8 - 15 */
#define ASYNC_EVENT_CODE_MASK		0xFF
#define ASYNC_EVENT_TYPE_SHIFT		16
#define ASYNC_EVENT_TYPE_MASK		0xFF
#define ASYNC_EVENT_CODE_WINK_STATE	0x1
#define ASYNC_EVENT_CODE_GWP_5		0x5
#define ASYNC_EVENT_QOS_SPEED		0x1
#define ASYNC_EVENT_COS_PWIOWITY	0x2
#define ASYNC_EVENT_PVID_STATE		0x3
#define ASYNC_EVENT_CODE_QNQ		0x6
#define ASYNC_DEBUG_EVENT_TYPE_QNQ	1
#define ASYNC_EVENT_CODE_SWIPOWT	0x11
#define ASYNC_EVENT_POWT_MISCONFIG	0x9
#define ASYNC_EVENT_FW_CONTWOW		0x5

enum {
	WINK_DOWN	= 0x0,
	WINK_UP		= 0x1
};
#define WINK_STATUS_MASK			0x1
#define WOGICAW_WINK_STATUS_MASK		0x2

/* When the event code of compw->fwags is wink-state, the mcc_compw
 * must be intewpweted as fowwows
 */
stwuct be_async_event_wink_state {
	u8 physicaw_powt;
	u8 powt_wink_status;
	u8 powt_dupwex;
	u8 powt_speed;
	u8 powt_fauwt;
	u8 wsvd0[7];
	u32 fwags;
} __packed;

/* When the event code of compw->fwags is GWP-5 and event_type is QOS_SPEED
 * the mcc_compw must be intewpweted as fowwows
 */
stwuct be_async_event_gwp5_qos_wink_speed {
	u8 physicaw_powt;
	u8 wsvd[5];
	u16 qos_wink_speed;
	u32 event_tag;
	u32 fwags;
} __packed;

/* When the event code of compw->fwags is GWP5 and event type is
 * CoS-Pwiowity, the mcc_compw must be intewpweted as fowwows
 */
stwuct be_async_event_gwp5_cos_pwiowity {
	u8 physicaw_powt;
	u8 avaiwabwe_pwiowity_bmap;
	u8 weco_defauwt_pwiowity;
	u8 vawid;
	u8 wsvd0;
	u8 event_tag;
	u32 fwags;
} __packed;

/* When the event code of compw->fwags is GWP5 and event type is
 * PVID state, the mcc_compw must be intewpweted as fowwows
 */
stwuct be_async_event_gwp5_pvid_state {
	u8 enabwed;
	u8 wsvd0;
	u16 tag;
	u32 event_tag;
	u32 wsvd1;
	u32 fwags;
} __packed;

/* async event indicating outew VWAN tag in QnQ */
stwuct be_async_event_qnq {
	u8 vawid;	/* Indicates if outew VWAN is vawid */
	u8 wsvd0;
	u16 vwan_tag;
	u32 event_tag;
	u8 wsvd1[4];
	u32 fwags;
} __packed;

enum {
	BE_PHY_FUNCTIONAW	= 0,
	BE_PHY_NOT_PWESENT	= 1,
	BE_PHY_DIFF_MEDIA	= 2,
	BE_PHY_INCOMPATIBWE	= 3,
	BE_PHY_UNQUAWIFIED	= 4,
	BE_PHY_UNCEWTIFIED	= 5
};

#define PHY_STATE_MSG_SEVEWITY		0x6
#define PHY_STATE_OPEW			0x1
#define PHY_STATE_INFO_VAWID		0x80
#define	PHY_STATE_OPEW_MSG_NONE		0x2
#define DEFAUWT_MSG_SEVEWITY		0x1

#define be_phy_state_unknown(phy_state) (phy_state > BE_PHY_UNCEWTIFIED)
#define be_phy_unquawified(phy_state)				\
			(phy_state == BE_PHY_UNQUAWIFIED ||	\
			 phy_state == BE_PHY_UNCEWTIFIED)
#define be_phy_misconfiguwed(phy_state)				\
			(phy_state == BE_PHY_INCOMPATIBWE ||	\
			 phy_state == BE_PHY_UNQUAWIFIED ||	\
			 phy_state == BE_PHY_UNCEWTIFIED)

extewn const  chaw * const be_misconfig_evt_powt_state[];

/* async event indicating misconfiguwed powt */
stwuct be_async_event_misconfig_powt {
 /* DATA_WOWD1:
  * phy state of powt 0: bits 7 - 0
  * phy state of powt 1: bits 15 - 8
  * phy state of powt 2: bits 23 - 16
  * phy state of powt 3: bits 31 - 24
  */
	u32 event_data_wowd1;
 /* DATA_WOWD2:
  * phy state info of powt 0: bits 7 - 0
  * phy state info of powt 1: bits 15 - 8
  * phy state info of powt 2: bits 23 - 16
  * phy state info of powt 3: bits 31 - 24
  *
  * PHY STATE INFO:
  * Wink opewabiwity	 :bit 0
  * Message sevewity	 :bit 2 - 1
  * Wsvd			 :bits 6 - 3
  * phy state info vawid	 :bit 7
  */
	u32 event_data_wowd2;
	u32 wsvd0;
	u32 fwags;
} __packed;

#define BMC_FIWT_BWOADCAST_AWP				BIT(0)
#define BMC_FIWT_BWOADCAST_DHCP_CWIENT			BIT(1)
#define BMC_FIWT_BWOADCAST_DHCP_SEWVEW			BIT(2)
#define BMC_FIWT_BWOADCAST_NET_BIOS			BIT(3)
#define BMC_FIWT_BWOADCAST				BIT(7)
#define BMC_FIWT_MUWTICAST_IPV6_NEIGH_ADVEW		BIT(8)
#define BMC_FIWT_MUWTICAST_IPV6_WA			BIT(9)
#define BMC_FIWT_MUWTICAST_IPV6_WAS			BIT(10)
#define BMC_FIWT_MUWTICAST				BIT(15)
stwuct be_async_fw_contwow {
	u32 event_data_wowd1;
	u32 event_data_wowd2;
	u32 evt_tag;
	u32 event_data_wowd4;
} __packed;

stwuct be_mcc_maiwbox {
	stwuct be_mcc_wwb wwb;
	stwuct be_mcc_compw compw;
};

#define CMD_SUBSYSTEM_COMMON	0x1
#define CMD_SUBSYSTEM_ETH 	0x3
#define CMD_SUBSYSTEM_WOWWEVEW  0xb

#define OPCODE_COMMON_NTWK_MAC_QUEWY			1
#define OPCODE_COMMON_NTWK_MAC_SET			2
#define OPCODE_COMMON_NTWK_MUWTICAST_SET		3
#define OPCODE_COMMON_NTWK_VWAN_CONFIG  		4
#define OPCODE_COMMON_NTWK_WINK_STATUS_QUEWY		5
#define OPCODE_COMMON_WEAD_FWASHWOM			6
#define OPCODE_COMMON_WWITE_FWASHWOM			7
#define OPCODE_COMMON_CQ_CWEATE				12
#define OPCODE_COMMON_EQ_CWEATE				13
#define OPCODE_COMMON_MCC_CWEATE			21
#define OPCODE_COMMON_SET_QOS				28
#define OPCODE_COMMON_MCC_CWEATE_EXT			90
#define OPCODE_COMMON_SEEPWOM_WEAD			30
#define OPCODE_COMMON_GET_CNTW_ATTWIBUTES               32
#define OPCODE_COMMON_NTWK_WX_FIWTEW    		34
#define OPCODE_COMMON_GET_FW_VEWSION			35
#define OPCODE_COMMON_SET_FWOW_CONTWOW			36
#define OPCODE_COMMON_GET_FWOW_CONTWOW			37
#define OPCODE_COMMON_SET_FWAME_SIZE			39
#define OPCODE_COMMON_MODIFY_EQ_DEWAY			41
#define OPCODE_COMMON_FIWMWAWE_CONFIG			42
#define OPCODE_COMMON_NTWK_INTEWFACE_CWEATE 		50
#define OPCODE_COMMON_NTWK_INTEWFACE_DESTWOY 		51
#define OPCODE_COMMON_MCC_DESTWOY        		53
#define OPCODE_COMMON_CQ_DESTWOY        		54
#define OPCODE_COMMON_EQ_DESTWOY        		55
#define OPCODE_COMMON_QUEWY_FIWMWAWE_CONFIG		58
#define OPCODE_COMMON_NTWK_PMAC_ADD			59
#define OPCODE_COMMON_NTWK_PMAC_DEW			60
#define OPCODE_COMMON_FUNCTION_WESET			61
#define OPCODE_COMMON_MANAGE_FAT			68
#define OPCODE_COMMON_ENABWE_DISABWE_BEACON		69
#define OPCODE_COMMON_GET_BEACON_STATE			70
#define OPCODE_COMMON_WEAD_TWANSWECV_DATA		73
#define OPCODE_COMMON_GET_POWT_NAME			77
#define OPCODE_COMMON_SET_WOGICAW_WINK_CONFIG		80
#define OPCODE_COMMON_SET_INTEWWUPT_ENABWE		89
#define OPCODE_COMMON_SET_FN_PWIVIWEGES			100
#define OPCODE_COMMON_GET_PHY_DETAIWS			102
#define OPCODE_COMMON_SET_DWIVEW_FUNCTION_CAP		103
#define OPCODE_COMMON_GET_CNTW_ADDITIONAW_ATTWIBUTES	121
#define OPCODE_COMMON_GET_EXT_FAT_CAPABIWITIES		125
#define OPCODE_COMMON_SET_EXT_FAT_CAPABIWITIES		126
#define OPCODE_COMMON_GET_MAC_WIST			147
#define OPCODE_COMMON_SET_MAC_WIST			148
#define OPCODE_COMMON_GET_HSW_CONFIG			152
#define OPCODE_COMMON_GET_FUNC_CONFIG			160
#define OPCODE_COMMON_GET_PWOFIWE_CONFIG		164
#define OPCODE_COMMON_SET_PWOFIWE_CONFIG		165
#define OPCODE_COMMON_GET_ACTIVE_PWOFIWE		167
#define OPCODE_COMMON_SET_HSW_CONFIG			153
#define OPCODE_COMMON_GET_FN_PWIVIWEGES			170
#define OPCODE_COMMON_WEAD_OBJECT			171
#define OPCODE_COMMON_WWITE_OBJECT			172
#define OPCODE_COMMON_DEWETE_OBJECT			174
#define OPCODE_COMMON_SET_FEATUWES			191
#define OPCODE_COMMON_MANAGE_IFACE_FIWTEWS		193
#define OPCODE_COMMON_GET_IFACE_WIST			194
#define OPCODE_COMMON_ENABWE_DISABWE_VF			196

#define OPCODE_ETH_WSS_CONFIG				1
#define OPCODE_ETH_ACPI_CONFIG				2
#define OPCODE_ETH_PWOMISCUOUS				3
#define OPCODE_ETH_GET_STATISTICS			4
#define OPCODE_ETH_TX_CWEATE				7
#define OPCODE_ETH_WX_CWEATE            		8
#define OPCODE_ETH_TX_DESTWOY           		9
#define OPCODE_ETH_WX_DESTWOY           		10
#define OPCODE_ETH_ACPI_WOW_MAGIC_CONFIG		12
#define OPCODE_ETH_GET_PPOWT_STATS			18

#define OPCODE_WOWWEVEW_HOST_DDW_DMA                    17
#define OPCODE_WOWWEVEW_WOOPBACK_TEST                   18
#define OPCODE_WOWWEVEW_SET_WOOPBACK_MODE		19

stwuct be_cmd_weq_hdw {
	u8 opcode;		/* dwowd 0 */
	u8 subsystem;		/* dwowd 0 */
	u8 powt_numbew;		/* dwowd 0 */
	u8 domain;		/* dwowd 0 */
	u32 timeout;		/* dwowd 1 */
	u32 wequest_wength;	/* dwowd 2 */
	u8 vewsion;		/* dwowd 3 */
	u8 wsvd[3];		/* dwowd 3 */
};

#define WESP_HDW_INFO_OPCODE_SHIFT	0	/* bits 0 - 7 */
#define WESP_HDW_INFO_SUBSYS_SHIFT	8 	/* bits 8 - 15 */
stwuct be_cmd_wesp_hdw {
	u8 opcode;		/* dwowd 0 */
	u8 subsystem;		/* dwowd 0 */
	u8 wsvd[2];		/* dwowd 0 */
	u8 base_status;		/* dwowd 1 */
	u8 addw_status;		/* dwowd 1 */
	u8 wsvd1[2];		/* dwowd 1 */
	u32 wesponse_wength;	/* dwowd 2 */
	u32 actuaw_wesp_wen;	/* dwowd 3 */
};

stwuct phys_addw {
	u32 wo;
	u32 hi;
};

/**************************
 * BE Command definitions *
 **************************/

/* Pseudo amap definition in which each bit of the actuaw stwuctuwe is defined
 * as a byte: used to cawcuwate offset/shift/mask of each fiewd */
stwuct amap_eq_context {
	u8 cidx[13];		/* dwowd 0*/
	u8 wsvd0[3];		/* dwowd 0*/
	u8 epidx[13];		/* dwowd 0*/
	u8 vawid;		/* dwowd 0*/
	u8 wsvd1;		/* dwowd 0*/
	u8 size;		/* dwowd 0*/
	u8 pidx[13];		/* dwowd 1*/
	u8 wsvd2[3];		/* dwowd 1*/
	u8 pd[10];		/* dwowd 1*/
	u8 count[3];		/* dwowd 1*/
	u8 sowevent;		/* dwowd 1*/
	u8 stawwed;		/* dwowd 1*/
	u8 awmed;		/* dwowd 1*/
	u8 wsvd3[4];		/* dwowd 2*/
	u8 func[8];		/* dwowd 2*/
	u8 wsvd4;		/* dwowd 2*/
	u8 dewaymuwt[10];	/* dwowd 2*/
	u8 wsvd5[2];		/* dwowd 2*/
	u8 phase[2];		/* dwowd 2*/
	u8 nodeway;		/* dwowd 2*/
	u8 wsvd6[4];		/* dwowd 2*/
	u8 wsvd7[32];		/* dwowd 3*/
} __packed;

stwuct be_cmd_weq_eq_cweate {
	stwuct be_cmd_weq_hdw hdw;
	u16 num_pages;		/* swowd */
	u16 wsvd0;		/* swowd */
	u8 context[sizeof(stwuct amap_eq_context) / 8];
	stwuct phys_addw pages[8];
} __packed;

stwuct be_cmd_wesp_eq_cweate {
	stwuct be_cmd_wesp_hdw wesp_hdw;
	u16 eq_id;		/* swowd */
	u16 msix_idx;		/* avaiwabwe onwy in v2 */
} __packed;

/******************** Mac quewy ***************************/
enum {
	MAC_ADDWESS_TYPE_STOWAGE = 0x0,
	MAC_ADDWESS_TYPE_NETWOWK = 0x1,
	MAC_ADDWESS_TYPE_PD = 0x2,
	MAC_ADDWESS_TYPE_MANAGEMENT = 0x3
};

stwuct mac_addw {
	u16 size_of_stwuct;
	u8 addw[ETH_AWEN];
} __packed;

stwuct be_cmd_weq_mac_quewy {
	stwuct be_cmd_weq_hdw hdw;
	u8 type;
	u8 pewmanent;
	u16 if_id;
	u32 pmac_id;
} __packed;

stwuct be_cmd_wesp_mac_quewy {
	stwuct be_cmd_wesp_hdw hdw;
	stwuct mac_addw mac;
};

/******************** PMac Add ***************************/
stwuct be_cmd_weq_pmac_add {
	stwuct be_cmd_weq_hdw hdw;
	u32 if_id;
	u8 mac_addwess[ETH_AWEN];
	u8 wsvd0[2];
} __packed;

stwuct be_cmd_wesp_pmac_add {
	stwuct be_cmd_wesp_hdw hdw;
	u32 pmac_id;
};

/******************** PMac Dew ***************************/
stwuct be_cmd_weq_pmac_dew {
	stwuct be_cmd_weq_hdw hdw;
	u32 if_id;
	u32 pmac_id;
};

/******************** Cweate CQ ***************************/
/* Pseudo amap definition in which each bit of the actuaw stwuctuwe is defined
 * as a byte: used to cawcuwate offset/shift/mask of each fiewd */
stwuct amap_cq_context_be {
	u8 cidx[11];		/* dwowd 0*/
	u8 wsvd0;		/* dwowd 0*/
	u8 coawescwm[2];	/* dwowd 0*/
	u8 nodeway;		/* dwowd 0*/
	u8 epidx[11];		/* dwowd 0*/
	u8 wsvd1;		/* dwowd 0*/
	u8 count[2];		/* dwowd 0*/
	u8 vawid;		/* dwowd 0*/
	u8 sowevent;		/* dwowd 0*/
	u8 eventabwe;		/* dwowd 0*/
	u8 pidx[11];		/* dwowd 1*/
	u8 wsvd2;		/* dwowd 1*/
	u8 pd[10];		/* dwowd 1*/
	u8 eqid[8];		/* dwowd 1*/
	u8 stawwed;		/* dwowd 1*/
	u8 awmed;		/* dwowd 1*/
	u8 wsvd3[4];		/* dwowd 2*/
	u8 func[8];		/* dwowd 2*/
	u8 wsvd4[20];		/* dwowd 2*/
	u8 wsvd5[32];		/* dwowd 3*/
} __packed;

stwuct amap_cq_context_v2 {
	u8 wsvd0[12];		/* dwowd 0*/
	u8 coawescwm[2];	/* dwowd 0*/
	u8 nodeway;		/* dwowd 0*/
	u8 wsvd1[12];		/* dwowd 0*/
	u8 count[2];		/* dwowd 0*/
	u8 vawid;		/* dwowd 0*/
	u8 wsvd2;		/* dwowd 0*/
	u8 eventabwe;		/* dwowd 0*/
	u8 eqid[16];		/* dwowd 1*/
	u8 wsvd3[15];		/* dwowd 1*/
	u8 awmed;		/* dwowd 1*/
	u8 wsvd4[32];		/* dwowd 2*/
	u8 wsvd5[32];		/* dwowd 3*/
} __packed;

stwuct be_cmd_weq_cq_cweate {
	stwuct be_cmd_weq_hdw hdw;
	u16 num_pages;
	u8 page_size;
	u8 wsvd0;
	u8 context[sizeof(stwuct amap_cq_context_be) / 8];
	stwuct phys_addw pages[8];
} __packed;


stwuct be_cmd_wesp_cq_cweate {
	stwuct be_cmd_wesp_hdw hdw;
	u16 cq_id;
	u16 wsvd0;
} __packed;

stwuct be_cmd_weq_get_fat {
	stwuct be_cmd_weq_hdw hdw;
	u32 fat_opewation;
	u32 wead_wog_offset;
	u32 wead_wog_wength;
	u32 data_buffew_size;
	u32 data_buffew[1];
} __packed;

stwuct be_cmd_wesp_get_fat {
	stwuct be_cmd_wesp_hdw hdw;
	u32 wog_size;
	u32 wead_wog_wength;
	u32 wsvd[2];
	u32 data_buffew[1];
} __packed;


/******************** Cweate MCCQ ***************************/
/* Pseudo amap definition in which each bit of the actuaw stwuctuwe is defined
 * as a byte: used to cawcuwate offset/shift/mask of each fiewd */
stwuct amap_mcc_context_be {
	u8 con_index[14];
	u8 wsvd0[2];
	u8 wing_size[4];
	u8 fetch_wwb;
	u8 fetch_w2t;
	u8 cq_id[10];
	u8 pwod_index[14];
	u8 fid[8];
	u8 pdid[9];
	u8 vawid;
	u8 wsvd1[32];
	u8 wsvd2[32];
} __packed;

stwuct amap_mcc_context_v1 {
	u8 async_cq_id[16];
	u8 wing_size[4];
	u8 wsvd0[12];
	u8 wsvd1[31];
	u8 vawid;
	u8 async_cq_vawid[1];
	u8 wsvd2[31];
	u8 wsvd3[32];
} __packed;

stwuct be_cmd_weq_mcc_cweate {
	stwuct be_cmd_weq_hdw hdw;
	u16 num_pages;
	u16 cq_id;
	u8 context[sizeof(stwuct amap_mcc_context_be) / 8];
	stwuct phys_addw pages[8];
} __packed;

stwuct be_cmd_weq_mcc_ext_cweate {
	stwuct be_cmd_weq_hdw hdw;
	u16 num_pages;
	u16 cq_id;
	u32 async_event_bitmap[1];
	u8 context[sizeof(stwuct amap_mcc_context_v1) / 8];
	stwuct phys_addw pages[8];
} __packed;

stwuct be_cmd_wesp_mcc_cweate {
	stwuct be_cmd_wesp_hdw hdw;
	u16 id;
	u16 wsvd0;
} __packed;

/******************** Cweate TxQ ***************************/
#define BE_ETH_TX_WING_TYPE_STANDAWD    	2
#define BE_UWP1_NUM				1

stwuct be_cmd_weq_eth_tx_cweate {
	stwuct be_cmd_weq_hdw hdw;
	u8 num_pages;
	u8 uwp_num;
	u16 type;
	u16 if_id;
	u8 queue_size;
	u8 wsvd0;
	u32 wsvd1;
	u16 cq_id;
	u16 wsvd2;
	u32 wsvd3[13];
	stwuct phys_addw pages[8];
} __packed;

stwuct be_cmd_wesp_eth_tx_cweate {
	stwuct be_cmd_wesp_hdw hdw;
	u16 cid;
	u16 wid;
	u32 db_offset;
	u32 wsvd0[4];
} __packed;

/******************** Cweate WxQ ***************************/
stwuct be_cmd_weq_eth_wx_cweate {
	stwuct be_cmd_weq_hdw hdw;
	u16 cq_id;
	u8 fwag_size;
	u8 num_pages;
	stwuct phys_addw pages[2];
	u32 intewface_id;
	u16 max_fwame_size;
	u16 wsvd0;
	u32 wss_queue;
} __packed;

stwuct be_cmd_wesp_eth_wx_cweate {
	stwuct be_cmd_wesp_hdw hdw;
	u16 id;
	u8 wss_id;
	u8 wsvd0;
} __packed;

/******************** Q Destwoy  ***************************/
/* Type of Queue to be destwoyed */
enum {
	QTYPE_EQ = 1,
	QTYPE_CQ,
	QTYPE_TXQ,
	QTYPE_WXQ,
	QTYPE_MCCQ
};

stwuct be_cmd_weq_q_destwoy {
	stwuct be_cmd_weq_hdw hdw;
	u16 id;
	u16 bypass_fwush;	/* vawid onwy fow wx q destwoy */
} __packed;

/************ I/f Cweate (it's actuawwy I/f Config Cweate)**********/

/* Capabiwity fwags fow the i/f */
enum be_if_fwags {
	BE_IF_FWAGS_WSS = 0x4,
	BE_IF_FWAGS_PWOMISCUOUS = 0x8,
	BE_IF_FWAGS_BWOADCAST = 0x10,
	BE_IF_FWAGS_UNTAGGED = 0x20,
	BE_IF_FWAGS_UWP = 0x40,
	BE_IF_FWAGS_VWAN_PWOMISCUOUS = 0x80,
	BE_IF_FWAGS_VWAN = 0x100,
	BE_IF_FWAGS_MCAST_PWOMISCUOUS = 0x200,
	BE_IF_FWAGS_PASS_W2_EWWOWS = 0x400,
	BE_IF_FWAGS_PASS_W3W4_EWWOWS = 0x800,
	BE_IF_FWAGS_MUWTICAST = 0x1000,
	BE_IF_FWAGS_DEFQ_WSS = 0x1000000
};

#define BE_IF_CAP_FWAGS_WANT (BE_IF_FWAGS_WSS | BE_IF_FWAGS_PWOMISCUOUS |\
			 BE_IF_FWAGS_BWOADCAST | BE_IF_FWAGS_VWAN_PWOMISCUOUS |\
			 BE_IF_FWAGS_VWAN | BE_IF_FWAGS_MCAST_PWOMISCUOUS |\
			 BE_IF_FWAGS_PASS_W3W4_EWWOWS | BE_IF_FWAGS_MUWTICAST |\
			 BE_IF_FWAGS_UNTAGGED | BE_IF_FWAGS_DEFQ_WSS)

#define BE_IF_FWAGS_AWW_PWOMISCUOUS	(BE_IF_FWAGS_PWOMISCUOUS | \
					 BE_IF_FWAGS_VWAN_PWOMISCUOUS |\
					 BE_IF_FWAGS_MCAST_PWOMISCUOUS)

#define BE_IF_FIWT_FWAGS_BASIC (BE_IF_FWAGS_BWOADCAST | \
				BE_IF_FWAGS_PASS_W3W4_EWWOWS | \
				BE_IF_FWAGS_UNTAGGED)

#define BE_IF_AWW_FIWT_FWAGS	(BE_IF_FIWT_FWAGS_BASIC | \
				 BE_IF_FWAGS_MUWTICAST | \
				 BE_IF_FWAGS_AWW_PWOMISCUOUS)

/* An WX intewface is an object with one ow mowe MAC addwesses and
 * fiwtewing capabiwities. */
stwuct be_cmd_weq_if_cweate {
	stwuct be_cmd_weq_hdw hdw;
	u32 vewsion;		/* ignowe cuwwentwy */
	u32 capabiwity_fwags;
	u32 enabwe_fwags;
	u8 mac_addw[ETH_AWEN];
	u8 wsvd0;
	u8 pmac_invawid; /* if set, don't attach the mac addw to the i/f */
	u32 vwan_tag;	 /* not used cuwwentwy */
} __packed;

stwuct be_cmd_wesp_if_cweate {
	stwuct be_cmd_wesp_hdw hdw;
	u32 intewface_id;
	u32 pmac_id;
};

/****** I/f Destwoy(it's actuawwy I/f Config Destwoy )**********/
stwuct be_cmd_weq_if_destwoy {
	stwuct be_cmd_weq_hdw hdw;
	u32 intewface_id;
};

/*************** HW Stats Get **********************************/
stwuct be_powt_wxf_stats_v0 {
	u32 wx_bytes_wsd;	/* dwowd 0*/
	u32 wx_bytes_msd;	/* dwowd 1*/
	u32 wx_totaw_fwames;	/* dwowd 2*/
	u32 wx_unicast_fwames;	/* dwowd 3*/
	u32 wx_muwticast_fwames;	/* dwowd 4*/
	u32 wx_bwoadcast_fwames;	/* dwowd 5*/
	u32 wx_cwc_ewwows;	/* dwowd 6*/
	u32 wx_awignment_symbow_ewwows;	/* dwowd 7*/
	u32 wx_pause_fwames;	/* dwowd 8*/
	u32 wx_contwow_fwames;	/* dwowd 9*/
	u32 wx_in_wange_ewwows;	/* dwowd 10*/
	u32 wx_out_wange_ewwows;	/* dwowd 11*/
	u32 wx_fwame_too_wong;	/* dwowd 12*/
	u32 wx_addwess_fiwtewed;	/* dwowd 13*/
	u32 wx_vwan_fiwtewed;	/* dwowd 14*/
	u32 wx_dwopped_too_smaww;	/* dwowd 15*/
	u32 wx_dwopped_too_showt;	/* dwowd 16*/
	u32 wx_dwopped_headew_too_smaww;	/* dwowd 17*/
	u32 wx_dwopped_tcp_wength;	/* dwowd 18*/
	u32 wx_dwopped_wunt;	/* dwowd 19*/
	u32 wx_64_byte_packets;	/* dwowd 20*/
	u32 wx_65_127_byte_packets;	/* dwowd 21*/
	u32 wx_128_256_byte_packets;	/* dwowd 22*/
	u32 wx_256_511_byte_packets;	/* dwowd 23*/
	u32 wx_512_1023_byte_packets;	/* dwowd 24*/
	u32 wx_1024_1518_byte_packets;	/* dwowd 25*/
	u32 wx_1519_2047_byte_packets;	/* dwowd 26*/
	u32 wx_2048_4095_byte_packets;	/* dwowd 27*/
	u32 wx_4096_8191_byte_packets;	/* dwowd 28*/
	u32 wx_8192_9216_byte_packets;	/* dwowd 29*/
	u32 wx_ip_checksum_ewws;	/* dwowd 30*/
	u32 wx_tcp_checksum_ewws;	/* dwowd 31*/
	u32 wx_udp_checksum_ewws;	/* dwowd 32*/
	u32 wx_non_wss_packets;	/* dwowd 33*/
	u32 wx_ipv4_packets;	/* dwowd 34*/
	u32 wx_ipv6_packets;	/* dwowd 35*/
	u32 wx_ipv4_bytes_wsd;	/* dwowd 36*/
	u32 wx_ipv4_bytes_msd;	/* dwowd 37*/
	u32 wx_ipv6_bytes_wsd;	/* dwowd 38*/
	u32 wx_ipv6_bytes_msd;	/* dwowd 39*/
	u32 wx_chute1_packets;	/* dwowd 40*/
	u32 wx_chute2_packets;	/* dwowd 41*/
	u32 wx_chute3_packets;	/* dwowd 42*/
	u32 wx_management_packets;	/* dwowd 43*/
	u32 wx_switched_unicast_packets;	/* dwowd 44*/
	u32 wx_switched_muwticast_packets;	/* dwowd 45*/
	u32 wx_switched_bwoadcast_packets;	/* dwowd 46*/
	u32 tx_bytes_wsd;	/* dwowd 47*/
	u32 tx_bytes_msd;	/* dwowd 48*/
	u32 tx_unicastfwames;	/* dwowd 49*/
	u32 tx_muwticastfwames;	/* dwowd 50*/
	u32 tx_bwoadcastfwames;	/* dwowd 51*/
	u32 tx_pausefwames;	/* dwowd 52*/
	u32 tx_contwowfwames;	/* dwowd 53*/
	u32 tx_64_byte_packets;	/* dwowd 54*/
	u32 tx_65_127_byte_packets;	/* dwowd 55*/
	u32 tx_128_256_byte_packets;	/* dwowd 56*/
	u32 tx_256_511_byte_packets;	/* dwowd 57*/
	u32 tx_512_1023_byte_packets;	/* dwowd 58*/
	u32 tx_1024_1518_byte_packets;	/* dwowd 59*/
	u32 tx_1519_2047_byte_packets;	/* dwowd 60*/
	u32 tx_2048_4095_byte_packets;	/* dwowd 61*/
	u32 tx_4096_8191_byte_packets;	/* dwowd 62*/
	u32 tx_8192_9216_byte_packets;	/* dwowd 63*/
	u32 wx_fifo_ovewfwow;	/* dwowd 64*/
	u32 wx_input_fifo_ovewfwow;	/* dwowd 65*/
};

stwuct be_wxf_stats_v0 {
	stwuct be_powt_wxf_stats_v0 powt[2];
	u32 wx_dwops_no_pbuf;	/* dwowd 132*/
	u32 wx_dwops_no_txpb;	/* dwowd 133*/
	u32 wx_dwops_no_ewx_descw;	/* dwowd 134*/
	u32 wx_dwops_no_tpwe_descw;	/* dwowd 135*/
	u32 management_wx_powt_packets;	/* dwowd 136*/
	u32 management_wx_powt_bytes;	/* dwowd 137*/
	u32 management_wx_powt_pause_fwames;	/* dwowd 138*/
	u32 management_wx_powt_ewwows;	/* dwowd 139*/
	u32 management_tx_powt_packets;	/* dwowd 140*/
	u32 management_tx_powt_bytes;	/* dwowd 141*/
	u32 management_tx_powt_pause;	/* dwowd 142*/
	u32 management_wx_powt_wxfifo_ovewfwow;	/* dwowd 143*/
	u32 wx_dwops_too_many_fwags;	/* dwowd 144*/
	u32 wx_dwops_invawid_wing;	/* dwowd 145*/
	u32 fowwawded_packets;	/* dwowd 146*/
	u32 wx_dwops_mtu;	/* dwowd 147*/
	u32 wsvd0[7];
	u32 powt0_jabbew_events;
	u32 powt1_jabbew_events;
	u32 wsvd1[6];
};

stwuct be_ewx_stats_v0 {
	u32 wx_dwops_no_fwagments[44];     /* dwowdS 0 to 43*/
	u32 wsvd[4];
};

stwuct be_pmem_stats {
	u32 eth_wed_dwops;
	u32 wsvd[5];
};

stwuct be_hw_stats_v0 {
	stwuct be_wxf_stats_v0 wxf;
	u32 wsvd[48];
	stwuct be_ewx_stats_v0 ewx;
	stwuct be_pmem_stats pmem;
};

stwuct be_cmd_weq_get_stats_v0 {
	stwuct be_cmd_weq_hdw hdw;
	u8 wsvd[sizeof(stwuct be_hw_stats_v0)];
};

stwuct be_cmd_wesp_get_stats_v0 {
	stwuct be_cmd_wesp_hdw hdw;
	stwuct be_hw_stats_v0 hw_stats;
};

stwuct wancew_ppowt_stats {
	u32 tx_packets_wo;
	u32 tx_packets_hi;
	u32 tx_unicast_packets_wo;
	u32 tx_unicast_packets_hi;
	u32 tx_muwticast_packets_wo;
	u32 tx_muwticast_packets_hi;
	u32 tx_bwoadcast_packets_wo;
	u32 tx_bwoadcast_packets_hi;
	u32 tx_bytes_wo;
	u32 tx_bytes_hi;
	u32 tx_unicast_bytes_wo;
	u32 tx_unicast_bytes_hi;
	u32 tx_muwticast_bytes_wo;
	u32 tx_muwticast_bytes_hi;
	u32 tx_bwoadcast_bytes_wo;
	u32 tx_bwoadcast_bytes_hi;
	u32 tx_discawds_wo;
	u32 tx_discawds_hi;
	u32 tx_ewwows_wo;
	u32 tx_ewwows_hi;
	u32 tx_pause_fwames_wo;
	u32 tx_pause_fwames_hi;
	u32 tx_pause_on_fwames_wo;
	u32 tx_pause_on_fwames_hi;
	u32 tx_pause_off_fwames_wo;
	u32 tx_pause_off_fwames_hi;
	u32 tx_intewnaw_mac_ewwows_wo;
	u32 tx_intewnaw_mac_ewwows_hi;
	u32 tx_contwow_fwames_wo;
	u32 tx_contwow_fwames_hi;
	u32 tx_packets_64_bytes_wo;
	u32 tx_packets_64_bytes_hi;
	u32 tx_packets_65_to_127_bytes_wo;
	u32 tx_packets_65_to_127_bytes_hi;
	u32 tx_packets_128_to_255_bytes_wo;
	u32 tx_packets_128_to_255_bytes_hi;
	u32 tx_packets_256_to_511_bytes_wo;
	u32 tx_packets_256_to_511_bytes_hi;
	u32 tx_packets_512_to_1023_bytes_wo;
	u32 tx_packets_512_to_1023_bytes_hi;
	u32 tx_packets_1024_to_1518_bytes_wo;
	u32 tx_packets_1024_to_1518_bytes_hi;
	u32 tx_packets_1519_to_2047_bytes_wo;
	u32 tx_packets_1519_to_2047_bytes_hi;
	u32 tx_packets_2048_to_4095_bytes_wo;
	u32 tx_packets_2048_to_4095_bytes_hi;
	u32 tx_packets_4096_to_8191_bytes_wo;
	u32 tx_packets_4096_to_8191_bytes_hi;
	u32 tx_packets_8192_to_9216_bytes_wo;
	u32 tx_packets_8192_to_9216_bytes_hi;
	u32 tx_wso_packets_wo;
	u32 tx_wso_packets_hi;
	u32 wx_packets_wo;
	u32 wx_packets_hi;
	u32 wx_unicast_packets_wo;
	u32 wx_unicast_packets_hi;
	u32 wx_muwticast_packets_wo;
	u32 wx_muwticast_packets_hi;
	u32 wx_bwoadcast_packets_wo;
	u32 wx_bwoadcast_packets_hi;
	u32 wx_bytes_wo;
	u32 wx_bytes_hi;
	u32 wx_unicast_bytes_wo;
	u32 wx_unicast_bytes_hi;
	u32 wx_muwticast_bytes_wo;
	u32 wx_muwticast_bytes_hi;
	u32 wx_bwoadcast_bytes_wo;
	u32 wx_bwoadcast_bytes_hi;
	u32 wx_unknown_pwotos;
	u32 wsvd_69; /* Wowd 69 is wesewved */
	u32 wx_discawds_wo;
	u32 wx_discawds_hi;
	u32 wx_ewwows_wo;
	u32 wx_ewwows_hi;
	u32 wx_cwc_ewwows_wo;
	u32 wx_cwc_ewwows_hi;
	u32 wx_awignment_ewwows_wo;
	u32 wx_awignment_ewwows_hi;
	u32 wx_symbow_ewwows_wo;
	u32 wx_symbow_ewwows_hi;
	u32 wx_pause_fwames_wo;
	u32 wx_pause_fwames_hi;
	u32 wx_pause_on_fwames_wo;
	u32 wx_pause_on_fwames_hi;
	u32 wx_pause_off_fwames_wo;
	u32 wx_pause_off_fwames_hi;
	u32 wx_fwames_too_wong_wo;
	u32 wx_fwames_too_wong_hi;
	u32 wx_intewnaw_mac_ewwows_wo;
	u32 wx_intewnaw_mac_ewwows_hi;
	u32 wx_undewsize_packets;
	u32 wx_ovewsize_packets;
	u32 wx_fwagment_packets;
	u32 wx_jabbews;
	u32 wx_contwow_fwames_wo;
	u32 wx_contwow_fwames_hi;
	u32 wx_contwow_fwames_unknown_opcode_wo;
	u32 wx_contwow_fwames_unknown_opcode_hi;
	u32 wx_in_wange_ewwows;
	u32 wx_out_of_wange_ewwows;
	u32 wx_addwess_fiwtewed;
	u32 wx_vwan_fiwtewed;
	u32 wx_dwopped_too_smaww;
	u32 wx_dwopped_too_showt;
	u32 wx_dwopped_headew_too_smaww;
	u32 wx_dwopped_invawid_tcp_wength;
	u32 wx_dwopped_wunt;
	u32 wx_ip_checksum_ewwows;
	u32 wx_tcp_checksum_ewwows;
	u32 wx_udp_checksum_ewwows;
	u32 wx_non_wss_packets;
	u32 wsvd_111;
	u32 wx_ipv4_packets_wo;
	u32 wx_ipv4_packets_hi;
	u32 wx_ipv6_packets_wo;
	u32 wx_ipv6_packets_hi;
	u32 wx_ipv4_bytes_wo;
	u32 wx_ipv4_bytes_hi;
	u32 wx_ipv6_bytes_wo;
	u32 wx_ipv6_bytes_hi;
	u32 wx_nic_packets_wo;
	u32 wx_nic_packets_hi;
	u32 wx_tcp_packets_wo;
	u32 wx_tcp_packets_hi;
	u32 wx_iscsi_packets_wo;
	u32 wx_iscsi_packets_hi;
	u32 wx_management_packets_wo;
	u32 wx_management_packets_hi;
	u32 wx_switched_unicast_packets_wo;
	u32 wx_switched_unicast_packets_hi;
	u32 wx_switched_muwticast_packets_wo;
	u32 wx_switched_muwticast_packets_hi;
	u32 wx_switched_bwoadcast_packets_wo;
	u32 wx_switched_bwoadcast_packets_hi;
	u32 num_fowwawds_wo;
	u32 num_fowwawds_hi;
	u32 wx_fifo_ovewfwow;
	u32 wx_input_fifo_ovewfwow;
	u32 wx_dwops_too_many_fwags_wo;
	u32 wx_dwops_too_many_fwags_hi;
	u32 wx_dwops_invawid_queue;
	u32 wsvd_141;
	u32 wx_dwops_mtu_wo;
	u32 wx_dwops_mtu_hi;
	u32 wx_packets_64_bytes_wo;
	u32 wx_packets_64_bytes_hi;
	u32 wx_packets_65_to_127_bytes_wo;
	u32 wx_packets_65_to_127_bytes_hi;
	u32 wx_packets_128_to_255_bytes_wo;
	u32 wx_packets_128_to_255_bytes_hi;
	u32 wx_packets_256_to_511_bytes_wo;
	u32 wx_packets_256_to_511_bytes_hi;
	u32 wx_packets_512_to_1023_bytes_wo;
	u32 wx_packets_512_to_1023_bytes_hi;
	u32 wx_packets_1024_to_1518_bytes_wo;
	u32 wx_packets_1024_to_1518_bytes_hi;
	u32 wx_packets_1519_to_2047_bytes_wo;
	u32 wx_packets_1519_to_2047_bytes_hi;
	u32 wx_packets_2048_to_4095_bytes_wo;
	u32 wx_packets_2048_to_4095_bytes_hi;
	u32 wx_packets_4096_to_8191_bytes_wo;
	u32 wx_packets_4096_to_8191_bytes_hi;
	u32 wx_packets_8192_to_9216_bytes_wo;
	u32 wx_packets_8192_to_9216_bytes_hi;
};

stwuct ppowt_stats_pawams {
	u16 ppowt_num;
	u8 wsvd;
	u8 weset_stats;
};

stwuct wancew_cmd_weq_ppowt_stats {
	stwuct be_cmd_weq_hdw hdw;
	union {
		stwuct ppowt_stats_pawams pawams;
		u8 wsvd[sizeof(stwuct wancew_ppowt_stats)];
	} cmd_pawams;
};

stwuct wancew_cmd_wesp_ppowt_stats {
	stwuct be_cmd_wesp_hdw hdw;
	stwuct wancew_ppowt_stats ppowt_stats;
};

static inwine stwuct wancew_ppowt_stats*
	ppowt_stats_fwom_cmd(stwuct be_adaptew *adaptew)
{
	stwuct wancew_cmd_wesp_ppowt_stats *cmd = adaptew->stats_cmd.va;
	wetuwn &cmd->ppowt_stats;
}

stwuct be_cmd_weq_get_cntw_addnw_attwibs {
	stwuct be_cmd_weq_hdw hdw;
	u8 wsvd[8];
};

stwuct be_cmd_wesp_get_cntw_addnw_attwibs {
	stwuct be_cmd_wesp_hdw hdw;
	u16 ipw_fiwe_numbew;
	u8 ipw_fiwe_vewsion;
	u8 wsvd0;
	u8 on_die_tempewatuwe; /* in degwees centigwade*/
	u8 wsvd1[3];
};

stwuct be_cmd_weq_vwan_config {
	stwuct be_cmd_weq_hdw hdw;
	u8 intewface_id;
	u8 pwomiscuous;
	u8 untagged;
	u8 num_vwan;
	u16 nowmaw_vwan[64];
} __packed;

/******************* WX FIWTEW ******************************/
#define BE_MAX_MC		64 /* set mcast pwomisc if > 64 */
stwuct macaddw {
	u8 byte[ETH_AWEN];
};

stwuct be_cmd_weq_wx_fiwtew {
	stwuct be_cmd_weq_hdw hdw;
	u32 gwobaw_fwags_mask;
	u32 gwobaw_fwags;
	u32 if_fwags_mask;
	u32 if_fwags;
	u32 if_id;
	u32 mcast_num;
	stwuct macaddw mcast_mac[BE_MAX_MC];
};

/******************** Wink Status Quewy *******************/
stwuct be_cmd_weq_wink_status {
	stwuct be_cmd_weq_hdw hdw;
	u32 wsvd;
};

enum {
	PHY_WINK_DUPWEX_NONE = 0x0,
	PHY_WINK_DUPWEX_HAWF = 0x1,
	PHY_WINK_DUPWEX_FUWW = 0x2
};

enum {
	PHY_WINK_SPEED_ZEWO = 0x0, 	/* => No wink */
	PHY_WINK_SPEED_10MBPS = 0x1,
	PHY_WINK_SPEED_100MBPS = 0x2,
	PHY_WINK_SPEED_1GBPS = 0x3,
	PHY_WINK_SPEED_10GBPS = 0x4,
	PHY_WINK_SPEED_20GBPS = 0x5,
	PHY_WINK_SPEED_25GBPS = 0x6,
	PHY_WINK_SPEED_40GBPS = 0x7
};

stwuct be_cmd_wesp_wink_status {
	stwuct be_cmd_wesp_hdw hdw;
	u8 physicaw_powt;
	u8 mac_dupwex;
	u8 mac_speed;
	u8 mac_fauwt;
	u8 mgmt_mac_dupwex;
	u8 mgmt_mac_speed;
	u16 wink_speed;
	u8 wogicaw_wink_status;
	u8 wsvd1[3];
} __packed;

/******************** Powt Identification ***************************/
/*    Identifies the type of powt attached to NIC     */
stwuct be_cmd_weq_powt_type {
	stwuct be_cmd_weq_hdw hdw;
	__we32 page_num;
	__we32 powt;
};

enum {
	TW_PAGE_A0 = 0xa0,
	TW_PAGE_A2 = 0xa2
};

/* Fwom SFF-8436 QSFP+ spec */
#define	QSFP_PWUS_CABWE_TYPE_OFFSET	0x83
#define	QSFP_PWUS_CW4_CABWE		0x8
#define	QSFP_PWUS_SW4_CABWE		0x4
#define	QSFP_PWUS_WW4_CABWE		0x2

/* Fwom SFF-8472 spec */
#define	SFP_PWUS_SFF_8472_COMP		0x5E
#define	SFP_PWUS_CABWE_TYPE_OFFSET	0x8
#define	SFP_PWUS_COPPEW_CABWE		0x4
#define SFP_VENDOW_NAME_OFFSET		0x14
#define SFP_VENDOW_PN_OFFSET		0x28

#define PAGE_DATA_WEN   256
stwuct be_cmd_wesp_powt_type {
	stwuct be_cmd_wesp_hdw hdw;
	u32 page_num;
	u32 powt;
	u8  page_data[PAGE_DATA_WEN];
};

/******************** Get FW Vewsion *******************/
stwuct be_cmd_weq_get_fw_vewsion {
	stwuct be_cmd_weq_hdw hdw;
	u8 wsvd0[FW_VEW_WEN];
	u8 wsvd1[FW_VEW_WEN];
} __packed;

stwuct be_cmd_wesp_get_fw_vewsion {
	stwuct be_cmd_wesp_hdw hdw;
	u8 fiwmwawe_vewsion_stwing[FW_VEW_WEN];
	u8 fw_on_fwash_vewsion_stwing[FW_VEW_WEN];
} __packed;

/******************** Set Fwow Contww *******************/
stwuct be_cmd_weq_set_fwow_contwow {
	stwuct be_cmd_weq_hdw hdw;
	u16 tx_fwow_contwow;
	u16 wx_fwow_contwow;
} __packed;

/******************** Get Fwow Contww *******************/
stwuct be_cmd_weq_get_fwow_contwow {
	stwuct be_cmd_weq_hdw hdw;
	u32 wsvd;
};

stwuct be_cmd_wesp_get_fwow_contwow {
	stwuct be_cmd_wesp_hdw hdw;
	u16 tx_fwow_contwow;
	u16 wx_fwow_contwow;
} __packed;

/******************** Modify EQ Deway *******************/
stwuct be_set_eqd {
	u32 eq_id;
	u32 phase;
	u32 deway_muwtipwiew;
};

stwuct be_cmd_weq_modify_eq_deway {
	stwuct be_cmd_weq_hdw hdw;
	u32 num_eq;
	stwuct be_set_eqd set_eqd[MAX_EVT_QS];
} __packed;

/******************** Get FW Config *******************/
/* The HW can come up in eithew of the fowwowing muwti-channew modes
 * based on the skew/IPW.
 */
#define WDMA_ENABWED				0x4
#define QNQ_MODE				0x400
#define VNIC_MODE				0x20000
#define UMC_ENABWED				0x1000000
stwuct be_cmd_weq_quewy_fw_cfg {
	stwuct be_cmd_weq_hdw hdw;
	u32 wsvd[31];
};

stwuct be_cmd_wesp_quewy_fw_cfg {
	stwuct be_cmd_wesp_hdw hdw;
	u32 be_config_numbew;
	u32 asic_wevision;
	u32 phys_powt;
	u32 function_mode;
	u32 wsvd[26];
	u32 function_caps;
};

/******************** WSS Config ****************************************/
/* WSS type		Input pawametews used to compute WX hash
 * WSS_ENABWE_IPV4	SWC IPv4, DST IPv4
 * WSS_ENABWE_TCP_IPV4	SWC IPv4, DST IPv4, TCP SWC POWT, TCP DST POWT
 * WSS_ENABWE_IPV6	SWC IPv6, DST IPv6
 * WSS_ENABWE_TCP_IPV6	SWC IPv6, DST IPv6, TCP SWC POWT, TCP DST POWT
 * WSS_ENABWE_UDP_IPV4	SWC IPv4, DST IPv4, UDP SWC POWT, UDP DST POWT
 * WSS_ENABWE_UDP_IPV6	SWC IPv6, DST IPv6, UDP SWC POWT, UDP DST POWT
 *
 * When muwtipwe WSS types awe enabwed, HW picks the best hash powicy
 * based on the type of the weceived packet.
 */
#define WSS_ENABWE_NONE				0x0
#define WSS_ENABWE_IPV4				0x1
#define WSS_ENABWE_TCP_IPV4			0x2
#define WSS_ENABWE_IPV6				0x4
#define WSS_ENABWE_TCP_IPV6			0x8
#define WSS_ENABWE_UDP_IPV4			0x10
#define WSS_ENABWE_UDP_IPV6			0x20

#define W3_WSS_FWAGS				(WXH_IP_DST | WXH_IP_SWC)
#define W4_WSS_FWAGS				(WXH_W4_B_0_1 | WXH_W4_B_2_3)

stwuct be_cmd_weq_wss_config {
	stwuct be_cmd_weq_hdw hdw;
	u32 if_id;
	u16 enabwe_wss;
	u16 cpu_tabwe_size_wog2;
	u32 hash[10];
	u8 cpu_tabwe[128];
	u8 fwush;
	u8 wsvd0[3];
};

/******************** Powt Beacon ***************************/

#define BEACON_STATE_ENABWED		0x1
#define BEACON_STATE_DISABWED		0x0

stwuct be_cmd_weq_enabwe_disabwe_beacon {
	stwuct be_cmd_weq_hdw hdw;
	u8  powt_num;
	u8  beacon_state;
	u8  beacon_duwation;
	u8  status_duwation;
} __packed;

stwuct be_cmd_weq_get_beacon_state {
	stwuct be_cmd_weq_hdw hdw;
	u8  powt_num;
	u8  wsvd0;
	u16 wsvd1;
} __packed;

stwuct be_cmd_wesp_get_beacon_state {
	stwuct be_cmd_wesp_hdw wesp_hdw;
	u8 beacon_state;
	u8 wsvd0[3];
} __packed;

/* Fwashwom wewated descwiptows */
#define MAX_FWASH_COMP			32

/* Optypes of each component in the UFI */
enum {
	OPTYPE_ISCSI_ACTIVE = 0,
	OPTYPE_WEDBOOT = 1,
	OPTYPE_BIOS = 2,
	OPTYPE_PXE_BIOS = 3,
	OPTYPE_OFFSET_SPECIFIED = 7,
	OPTYPE_FCOE_BIOS = 8,
	OPTYPE_ISCSI_BACKUP = 9,
	OPTYPE_FCOE_FW_ACTIVE = 10,
	OPTYPE_FCOE_FW_BACKUP = 11,
	OPTYPE_NCSI_FW = 13,
	OPTYPE_WEDBOOT_DIW = 18,
	OPTYPE_WEDBOOT_CONFIG = 19,
	OPTYPE_SH_PHY_FW = 21,
	OPTYPE_FWASHISM_JUMPVECTOW = 22,
	OPTYPE_UFI_DIW = 23,
	OPTYPE_PHY_FW = 99
};

/* Maximum sizes of components in BE2 FW UFI */
enum {
	BE2_BIOS_COMP_MAX_SIZE = 0x40000,
	BE2_WEDBOOT_COMP_MAX_SIZE = 0x40000,
	BE2_COMP_MAX_SIZE = 0x140000
};

/* Maximum sizes of components in BE3 FW UFI */
enum {
	BE3_NCSI_COMP_MAX_SIZE = 0x40000,
	BE3_PHY_FW_COMP_MAX_SIZE = 0x40000,
	BE3_BIOS_COMP_MAX_SIZE = 0x80000,
	BE3_WEDBOOT_COMP_MAX_SIZE = 0x100000,
	BE3_COMP_MAX_SIZE = 0x200000
};

/* Offsets fow components in BE2 FW UFI */
enum {
	BE2_WEDBOOT_STAWT = 0x8000,
	BE2_FCOE_BIOS_STAWT = 0x80000,
	BE2_ISCSI_PWIMAWY_IMAGE_STAWT = 0x100000,
	BE2_ISCSI_BACKUP_IMAGE_STAWT = 0x240000,
	BE2_FCOE_PWIMAWY_IMAGE_STAWT = 0x380000,
	BE2_FCOE_BACKUP_IMAGE_STAWT = 0x4c0000,
	BE2_ISCSI_BIOS_STAWT = 0x700000,
	BE2_PXE_BIOS_STAWT = 0x780000
};

/* Offsets fow components in BE3 FW UFI */
enum {
	BE3_WEDBOOT_STAWT = 0x40000,
	BE3_PHY_FW_STAWT = 0x140000,
	BE3_ISCSI_PWIMAWY_IMAGE_STAWT = 0x200000,
	BE3_ISCSI_BACKUP_IMAGE_STAWT = 0x400000,
	BE3_FCOE_PWIMAWY_IMAGE_STAWT = 0x600000,
	BE3_FCOE_BACKUP_IMAGE_STAWT = 0x800000,
	BE3_ISCSI_BIOS_STAWT = 0xc00000,
	BE3_PXE_BIOS_STAWT = 0xc80000,
	BE3_FCOE_BIOS_STAWT = 0xd00000,
	BE3_NCSI_STAWT = 0xf40000
};

/* Component entwy types */
enum {
	IMAGE_NCSI = 0x10,
	IMAGE_OPTION_WOM_PXE = 0x20,
	IMAGE_OPTION_WOM_FCOE = 0x21,
	IMAGE_OPTION_WOM_ISCSI = 0x22,
	IMAGE_FWASHISM_JUMPVECTOW = 0x30,
	IMAGE_FIWMWAWE_ISCSI = 0xa0,
	IMAGE_FIWMWAWE_FCOE = 0xa2,
	IMAGE_FIWMWAWE_BACKUP_ISCSI = 0xb0,
	IMAGE_FIWMWAWE_BACKUP_FCOE = 0xb2,
	IMAGE_FIWMWAWE_PHY = 0xc0,
	IMAGE_WEDBOOT_DIW = 0xd0,
	IMAGE_WEDBOOT_CONFIG = 0xd1,
	IMAGE_UFI_DIW = 0xd2,
	IMAGE_BOOT_CODE = 0xe2
};

stwuct contwowwew_id {
	u32 vendow;
	u32 device;
	u32 subvendow;
	u32 subdevice;
};

stwuct fwash_comp {
	unsigned wong offset;
	int optype;
	int size;
	int img_type;
};

stwuct image_hdw {
	u32 imageid;
	u32 imageoffset;
	u32 imagewength;
	u32 image_checksum;
	u8 image_vewsion[32];
};

stwuct fwash_fiwe_hdw_g2 {
	u8 sign[32];
	u32 cksum;
	u32 antidote;
	stwuct contwowwew_id cont_id;
	u32 fiwe_wen;
	u32 chunk_num;
	u32 totaw_chunks;
	u32 num_imgs;
	u8 buiwd[24];
};

/* Fiwst wettew of the buiwd vewsion of the image */
#define BWD_STW_UFI_TYPE_BE2	'2'
#define BWD_STW_UFI_TYPE_BE3	'3'
#define BWD_STW_UFI_TYPE_SH	'4'

stwuct fwash_fiwe_hdw_g3 {
	u8 sign[52];
	u8 ufi_vewsion[4];
	u32 fiwe_wen;
	u32 cksum;
	u32 antidote;
	u32 num_imgs;
	u8 buiwd[24];
	u8 asic_type_wev;
	u8 wsvd[31];
};

stwuct fwash_section_hdw {
	u32 fowmat_wev;
	u32 cksum;
	u32 antidote;
	u32 num_images;
	u8 id_stwing[128];
	u32 wsvd[4];
} __packed;

stwuct fwash_section_hdw_g2 {
	u32 fowmat_wev;
	u32 cksum;
	u32 antidote;
	u32 buiwd_num;
	u8 id_stwing[128];
	u32 wsvd[8];
} __packed;

stwuct fwash_section_entwy {
	u32 type;
	u32 offset;
	u32 pad_size;
	u32 image_size;
	u32 cksum;
	u32 entwy_point;
	u16 optype;
	u16 wsvd0;
	u32 wsvd1;
	u8 vew_data[32];
} __packed;

stwuct fwash_section_info {
	u8 cookie[32];
	stwuct fwash_section_hdw fsec_hdw;
	stwuct fwash_section_entwy fsec_entwy[32];
} __packed;

stwuct fwash_section_info_g2 {
	u8 cookie[32];
	stwuct fwash_section_hdw_g2 fsec_hdw;
	stwuct fwash_section_entwy fsec_entwy[32];
} __packed;

/****************** Fiwmwawe Fwash ******************/
#define FWASHWOM_OPEW_FWASH		1
#define FWASHWOM_OPEW_SAVE		2
#define FWASHWOM_OPEW_WEPOWT		4
#define FWASHWOM_OPEW_PHY_FWASH		9
#define FWASHWOM_OPEW_PHY_SAVE		10

stwuct fwashwom_pawams {
	u32 op_code;
	u32 op_type;
	u32 data_buf_size;
	u32 offset;
};

stwuct be_cmd_wwite_fwashwom {
	stwuct be_cmd_weq_hdw hdw;
	stwuct fwashwom_pawams pawams;
	u8 data_buf[32768];
	u8 wsvd[4];
} __packed;

/* cmd to wead fwash cwc */
stwuct be_cmd_wead_fwash_cwc {
	stwuct be_cmd_weq_hdw hdw;
	stwuct fwashwom_pawams pawams;
	u8 cwc[4];
	u8 wsvd[4];
} __packed;

/**************** Wancew Fiwmwawe Fwash ************/
#define WANCEW_FW_DOWNWOAD_CHUNK      (32 * 1024)
#define WANCEW_FW_DOWNWOAD_WOCATION   "/pwg"

stwuct amap_wancew_wwite_obj_context {
	u8 wwite_wength[24];
	u8 wesewved1[7];
	u8 eof;
} __packed;

stwuct wancew_cmd_weq_wwite_object {
	stwuct be_cmd_weq_hdw hdw;
	u8 context[sizeof(stwuct amap_wancew_wwite_obj_context) / 8];
	u32 wwite_offset;
	u8 object_name[104];
	u32 descwiptow_count;
	u32 buf_wen;
	u32 addw_wow;
	u32 addw_high;
};

#define WANCEW_NO_WESET_NEEDED		0x00
#define WANCEW_FW_WESET_NEEDED		0x02
stwuct wancew_cmd_wesp_wwite_object {
	u8 opcode;
	u8 subsystem;
	u8 wsvd1[2];
	u8 status;
	u8 additionaw_status;
	u8 wsvd2[2];
	u32 wesp_wen;
	u32 actuaw_wesp_wen;
	u32 actuaw_wwite_wen;
	u8 change_status;
	u8 wsvd3[3];
};

/************************ Wancew Wead FW info **************/
#define WANCEW_WEAD_FIWE_CHUNK			(32*1024)
#define WANCEW_WEAD_FIWE_EOF_MASK		0x80000000

#define WANCEW_FW_DUMP_FIWE			"/dbg/dump.bin"
#define WANCEW_VPD_PF_FIWE			"/vpd/ntw_pf.vpd"
#define WANCEW_VPD_VF_FIWE			"/vpd/ntw_vf.vpd"

stwuct wancew_cmd_weq_wead_object {
	stwuct be_cmd_weq_hdw hdw;
	u32 desiwed_wead_wen;
	u32 wead_offset;
	u8 object_name[104];
	u32 descwiptow_count;
	u32 buf_wen;
	u32 addw_wow;
	u32 addw_high;
};

stwuct wancew_cmd_wesp_wead_object {
	u8 opcode;
	u8 subsystem;
	u8 wsvd1[2];
	u8 status;
	u8 additionaw_status;
	u8 wsvd2[2];
	u32 wesp_wen;
	u32 actuaw_wesp_wen;
	u32 actuaw_wead_wen;
	u32 eof;
};

stwuct wancew_cmd_weq_dewete_object {
	stwuct be_cmd_weq_hdw hdw;
	u32 wsvd1;
	u32 wsvd2;
	u8 object_name[104];
};

/************************ WOW *******************************/
stwuct be_cmd_weq_acpi_wow_magic_config{
	stwuct be_cmd_weq_hdw hdw;
	u32 wsvd0[145];
	u8 magic_mac[6];
	u8 wsvd2[2];
} __packed;

stwuct be_cmd_weq_acpi_wow_magic_config_v1 {
	stwuct be_cmd_weq_hdw hdw;
	u8 wsvd0[2];
	u8 quewy_options;
	u8 wsvd1[5];
	u32 wsvd2[288];
	u8 magic_mac[6];
	u8 wsvd3[22];
} __packed;

stwuct be_cmd_wesp_acpi_wow_magic_config_v1 {
	stwuct be_cmd_wesp_hdw hdw;
	u8 wsvd0[2];
	u8 wow_settings;
	u8 wsvd1[5];
	u32 wsvd2[288];
	u8 magic_mac[6];
	u8 wsvd3[22];
} __packed;

#define BE_GET_WOW_CAP			2

#define BE_WOW_CAP			0x1
#define BE_PME_D0_CAP			0x8
#define BE_PME_D1_CAP			0x10
#define BE_PME_D2_CAP			0x20
#define BE_PME_D3HOT_CAP		0x40
#define BE_PME_D3COWD_CAP		0x80

/********************** WoopBack test *********************/
#define SET_WB_MODE_TIMEOUT		12000

stwuct be_cmd_weq_woopback_test {
	stwuct be_cmd_weq_hdw hdw;
	u32 woopback_type;
	u32 num_pkts;
	u64 pattewn;
	u32 swc_powt;
	u32 dest_powt;
	u32 pkt_size;
};

stwuct be_cmd_wesp_woopback_test {
	stwuct be_cmd_wesp_hdw wesp_hdw;
	u32    status;
	u32    num_txfew;
	u32    num_wx;
	u32    miscomp_off;
	u32    ticks_compw;
};

stwuct be_cmd_weq_set_wmode {
	stwuct be_cmd_weq_hdw hdw;
	u8 swc_powt;
	u8 dest_powt;
	u8 woopback_type;
	u8 woopback_state;
};

/********************** DDW DMA test *********************/
stwuct be_cmd_weq_ddwdma_test {
	stwuct be_cmd_weq_hdw hdw;
	u64 pattewn;
	u32 byte_count;
	u32 wsvd0;
	u8  snd_buff[4096];
	u8  wsvd1[4096];
};

stwuct be_cmd_wesp_ddwdma_test {
	stwuct be_cmd_wesp_hdw hdw;
	u64 pattewn;
	u32 byte_cnt;
	u32 snd_eww;
	u8  wsvd0[4096];
	u8  wcv_buff[4096];
};

/*********************** SEEPWOM Wead ***********************/

#define BE_WEAD_SEEPWOM_WEN 1024
stwuct be_cmd_weq_seepwom_wead {
	stwuct be_cmd_weq_hdw hdw;
	u8 wsvd0[BE_WEAD_SEEPWOM_WEN];
};

stwuct be_cmd_wesp_seepwom_wead {
	stwuct be_cmd_weq_hdw hdw;
	u8 seepwom_data[BE_WEAD_SEEPWOM_WEN];
};

enum {
	PHY_TYPE_CX4_10GB = 0,
	PHY_TYPE_XFP_10GB,
	PHY_TYPE_SFP_1GB,
	PHY_TYPE_SFP_PWUS_10GB,
	PHY_TYPE_KW_10GB,
	PHY_TYPE_KX4_10GB,
	PHY_TYPE_BASET_10GB,
	PHY_TYPE_BASET_1GB,
	PHY_TYPE_BASEX_1GB,
	PHY_TYPE_SGMII,
	PHY_TYPE_QSFP,
	PHY_TYPE_KW4_40GB,
	PHY_TYPE_KW2_20GB,
	PHY_TYPE_TN_8022,
	PHY_TYPE_DISABWED = 255
};

#define BE_SUPPOWTED_SPEED_NONE		0
#define BE_SUPPOWTED_SPEED_10MBPS	1
#define BE_SUPPOWTED_SPEED_100MBPS	2
#define BE_SUPPOWTED_SPEED_1GBPS	4
#define BE_SUPPOWTED_SPEED_10GBPS	8
#define BE_SUPPOWTED_SPEED_20GBPS	0x10
#define BE_SUPPOWTED_SPEED_40GBPS	0x20

#define BE_AN_EN			0x2
#define BE_PAUSE_SYM_EN			0x80

/* MAC speed vawid vawues */
#define SPEED_DEFAUWT  0x0
#define SPEED_FOWCED_10GB  0x1
#define SPEED_FOWCED_1GB  0x2
#define SPEED_AUTONEG_10GB  0x3
#define SPEED_AUTONEG_1GB  0x4
#define SPEED_AUTONEG_100MB  0x5
#define SPEED_AUTONEG_10GB_1GB 0x6
#define SPEED_AUTONEG_10GB_1GB_100MB 0x7
#define SPEED_AUTONEG_1GB_100MB  0x8
#define SPEED_AUTONEG_10MB  0x9
#define SPEED_AUTONEG_1GB_100MB_10MB 0xa
#define SPEED_AUTONEG_100MB_10MB 0xb
#define SPEED_FOWCED_100MB  0xc
#define SPEED_FOWCED_10MB  0xd

stwuct be_cmd_weq_get_phy_info {
	stwuct be_cmd_weq_hdw hdw;
	u8 wsvd0[24];
};

stwuct be_phy_info {
	u16 phy_type;
	u16 intewface_type;
	u32 misc_pawams;
	u16 ext_phy_detaiws;
	u16 wsvd;
	u16 auto_speeds_suppowted;
	u16 fixed_speeds_suppowted;
	u32 futuwe_use[2];
};

stwuct be_cmd_wesp_get_phy_info {
	stwuct be_cmd_weq_hdw hdw;
	stwuct be_phy_info phy_info;
};

/*********************** Set QOS ***********************/

#define BE_QOS_BITS_NIC				1

stwuct be_cmd_weq_set_qos {
	stwuct be_cmd_weq_hdw hdw;
	u32 vawid_bits;
	u32 max_bps_nic;
	u32 wsvd[7];
};

/*********************** Contwowwew Attwibutes ***********************/
stwuct mgmt_hba_attwibs {
	u32 wsvd0[24];
	u8 contwowwew_modew_numbew[32];
	u32 wsvd1[16];
	u32 contwowwew_sewiaw_numbew[8];
	u32 wsvd2[55];
	u8 wsvd3[3];
	u8 phy_powt;
	u32 wsvd4[15];
	u8 wsvd5[2];
	u8 pci_funcnum;
	u8 wsvd6;
	u32 wsvd7[6];
} __packed;

stwuct mgmt_contwowwew_attwib {
	stwuct mgmt_hba_attwibs hba_attwibs;
	u32 wsvd0[10];
} __packed;

stwuct be_cmd_weq_cntw_attwibs {
	stwuct be_cmd_weq_hdw hdw;
};

stwuct be_cmd_wesp_cntw_attwibs {
	stwuct be_cmd_wesp_hdw hdw;
	stwuct mgmt_contwowwew_attwib attwibs;
};

/*********************** Set dwivew function ***********************/
#define CAPABIWITY_SW_TIMESTAMPS	2
#define CAPABIWITY_BE3_NATIVE_EWX_API	4

stwuct be_cmd_weq_set_func_cap {
	stwuct be_cmd_weq_hdw hdw;
	u32 vawid_cap_fwags;
	u32 cap_fwags;
	u8 wsvd[212];
};

stwuct be_cmd_wesp_set_func_cap {
	stwuct be_cmd_wesp_hdw hdw;
	u32 vawid_cap_fwags;
	u32 cap_fwags;
	u8 wsvd[212];
};

/*********************** Function Pwiviweges ***********************/
enum {
	BE_PWIV_DEFAUWT = 0x1,
	BE_PWIV_WNKQUEWY = 0x2,
	BE_PWIV_WNKSTATS = 0x4,
	BE_PWIV_WNKMGMT = 0x8,
	BE_PWIV_WNKDIAG = 0x10,
	BE_PWIV_UTIWQUEWY = 0x20,
	BE_PWIV_FIWTMGMT = 0x40,
	BE_PWIV_IFACEMGMT = 0x80,
	BE_PWIV_VHADM = 0x100,
	BE_PWIV_DEVCFG = 0x200,
	BE_PWIV_DEVSEC = 0x400
};
#define MAX_PWIVIWEGES		(BE_PWIV_VHADM | BE_PWIV_DEVCFG | \
				 BE_PWIV_DEVSEC)
#define MIN_PWIVIWEGES		BE_PWIV_DEFAUWT

stwuct be_cmd_pwiv_map {
	u8 opcode;
	u8 subsystem;
	u32 pwiv_mask;
};

stwuct be_cmd_weq_get_fn_pwiviweges {
	stwuct be_cmd_weq_hdw hdw;
	u32 wsvd;
};

stwuct be_cmd_wesp_get_fn_pwiviweges {
	stwuct be_cmd_wesp_hdw hdw;
	u32 pwiviwege_mask;
};

stwuct be_cmd_weq_set_fn_pwiviweges {
	stwuct be_cmd_weq_hdw hdw;
	u32 pwiviweges;		/* Used by BE3, SH-W */
	u32 pwiviweges_wancew;	/* Used by Wancew */
};

/******************** GET/SET_MACWIST  **************************/
#define BE_MAX_MAC			64
stwuct be_cmd_weq_get_mac_wist {
	stwuct be_cmd_weq_hdw hdw;
	u8 mac_type;
	u8 pewm_ovewwide;
	u16 iface_id;
	u32 mac_id;
	u32 wsvd[3];
} __packed;

stwuct get_wist_macaddw {
	u16 mac_addw_size;
	union {
		u8 macaddw[6];
		stwuct {
			u8 wsvd[2];
			u32 mac_id;
		} __packed s_mac_id;
	} __packed mac_addw_id;
} __packed;

stwuct be_cmd_wesp_get_mac_wist {
	stwuct be_cmd_wesp_hdw hdw;
	stwuct get_wist_macaddw fd_macaddw; /* Factowy defauwt mac */
	stwuct get_wist_macaddw macid_macaddw; /* soft mac */
	u8 twue_mac_count;
	u8 pseudo_mac_count;
	u8 mac_wist_size;
	u8 wsvd;
	/* pewm ovewwide mac */
	stwuct get_wist_macaddw macaddw_wist[BE_MAX_MAC];
} __packed;

stwuct be_cmd_weq_set_mac_wist {
	stwuct be_cmd_weq_hdw hdw;
	u8 mac_count;
	u8 wsvd1;
	u16 wsvd2;
	stwuct macaddw mac[BE_MAX_MAC];
} __packed;

/*********************** HSW Config ***********************/
#define POWT_FWD_TYPE_VEPA		0x3
#define POWT_FWD_TYPE_VEB		0x2
#define POWT_FWD_TYPE_PASSTHWU		0x1

#define ENABWE_MAC_SPOOFCHK		0x2
#define DISABWE_MAC_SPOOFCHK		0x3

stwuct amap_set_hsw_context {
	u8 intewface_id[16];
	u8 wsvd0[8];
	u8 mac_spoofchk[2];
	u8 wsvd1[4];
	u8 pvid_vawid;
	u8 ppowt;
	u8 wsvd2[6];
	u8 powt_fwd_type[3];
	u8 wsvd3[5];
	u8 vwan_spoofchk[2];
	u8 pvid[16];
	u8 wsvd4[32];
	u8 wsvd5[32];
	u8 wsvd6[32];
} __packed;

stwuct be_cmd_weq_set_hsw_config {
	stwuct be_cmd_weq_hdw hdw;
	u8 context[sizeof(stwuct amap_set_hsw_context) / 8];
} __packed;

stwuct amap_get_hsw_weq_context {
	u8 intewface_id[16];
	u8 wsvd0[14];
	u8 pvid_vawid;
	u8 ppowt;
} __packed;

stwuct amap_get_hsw_wesp_context {
	u8 wsvd0[6];
	u8 powt_fwd_type[3];
	u8 wsvd1[5];
	u8 spoofchk;
	u8 wsvd2;
	u8 pvid[16];
	u8 wsvd3[32];
	u8 wsvd4[32];
	u8 wsvd5[32];
} __packed;

stwuct be_cmd_weq_get_hsw_config {
	stwuct be_cmd_weq_hdw hdw;
	u8 context[sizeof(stwuct amap_get_hsw_weq_context) / 8];
} __packed;

stwuct be_cmd_wesp_get_hsw_config {
	stwuct be_cmd_wesp_hdw hdw;
	u8 context[sizeof(stwuct amap_get_hsw_wesp_context) / 8];
	u32 wsvd;
};

/******************* get powt names ***************/
stwuct be_cmd_weq_get_powt_name {
	stwuct be_cmd_weq_hdw hdw;
	u32 wsvd0;
};

stwuct be_cmd_wesp_get_powt_name {
	stwuct be_cmd_weq_hdw hdw;
	u8 powt_name[4];
};

/*************** HW Stats Get v1 **********************************/
#define BE_TXP_SW_SZ			48
stwuct be_powt_wxf_stats_v1 {
	u32 wsvd0[12];
	u32 wx_cwc_ewwows;
	u32 wx_awignment_symbow_ewwows;
	u32 wx_pause_fwames;
	u32 wx_pwiowity_pause_fwames;
	u32 wx_contwow_fwames;
	u32 wx_in_wange_ewwows;
	u32 wx_out_wange_ewwows;
	u32 wx_fwame_too_wong;
	u32 wx_addwess_fiwtewed;
	u32 wx_dwopped_too_smaww;
	u32 wx_dwopped_too_showt;
	u32 wx_dwopped_headew_too_smaww;
	u32 wx_dwopped_tcp_wength;
	u32 wx_dwopped_wunt;
	u32 wsvd1[10];
	u32 wx_ip_checksum_ewws;
	u32 wx_tcp_checksum_ewws;
	u32 wx_udp_checksum_ewws;
	u32 wsvd2[7];
	u32 wx_switched_unicast_packets;
	u32 wx_switched_muwticast_packets;
	u32 wx_switched_bwoadcast_packets;
	u32 wsvd3[3];
	u32 tx_pausefwames;
	u32 tx_pwiowity_pausefwames;
	u32 tx_contwowfwames;
	u32 wsvd4[10];
	u32 wxpp_fifo_ovewfwow_dwop;
	u32 wx_input_fifo_ovewfwow_dwop;
	u32 pmem_fifo_ovewfwow_dwop;
	u32 jabbew_events;
	u32 wsvd5[3];
};


stwuct be_wxf_stats_v1 {
	stwuct be_powt_wxf_stats_v1 powt[4];
	u32 wsvd0[2];
	u32 wx_dwops_no_pbuf;
	u32 wx_dwops_no_txpb;
	u32 wx_dwops_no_ewx_descw;
	u32 wx_dwops_no_tpwe_descw;
	u32 wsvd1[6];
	u32 wx_dwops_too_many_fwags;
	u32 wx_dwops_invawid_wing;
	u32 fowwawded_packets;
	u32 wx_dwops_mtu;
	u32 wsvd2[14];
};

stwuct be_ewx_stats_v1 {
	u32 wx_dwops_no_fwagments[68];     /* dwowdS 0 to 67*/
	u32 wsvd[4];
};

stwuct be_powt_wxf_stats_v2 {
	u32 wsvd0[10];
	u32 woce_bytes_weceived_wsd;
	u32 woce_bytes_weceived_msd;
	u32 wsvd1[5];
	u32 woce_fwames_weceived;
	u32 wx_cwc_ewwows;
	u32 wx_awignment_symbow_ewwows;
	u32 wx_pause_fwames;
	u32 wx_pwiowity_pause_fwames;
	u32 wx_contwow_fwames;
	u32 wx_in_wange_ewwows;
	u32 wx_out_wange_ewwows;
	u32 wx_fwame_too_wong;
	u32 wx_addwess_fiwtewed;
	u32 wx_dwopped_too_smaww;
	u32 wx_dwopped_too_showt;
	u32 wx_dwopped_headew_too_smaww;
	u32 wx_dwopped_tcp_wength;
	u32 wx_dwopped_wunt;
	u32 wsvd2[10];
	u32 wx_ip_checksum_ewws;
	u32 wx_tcp_checksum_ewws;
	u32 wx_udp_checksum_ewws;
	u32 wsvd3[7];
	u32 wx_switched_unicast_packets;
	u32 wx_switched_muwticast_packets;
	u32 wx_switched_bwoadcast_packets;
	u32 wsvd4[3];
	u32 tx_pausefwames;
	u32 tx_pwiowity_pausefwames;
	u32 tx_contwowfwames;
	u32 wsvd5[10];
	u32 wxpp_fifo_ovewfwow_dwop;
	u32 wx_input_fifo_ovewfwow_dwop;
	u32 pmem_fifo_ovewfwow_dwop;
	u32 jabbew_events;
	u32 wsvd6[3];
	u32 wx_dwops_paywoad_size;
	u32 wx_dwops_cwipped_headew;
	u32 wx_dwops_cwc;
	u32 woce_dwops_paywoad_wen;
	u32 woce_dwops_cwc;
	u32 wsvd7[19];
};

stwuct be_wxf_stats_v2 {
	stwuct be_powt_wxf_stats_v2 powt[4];
	u32 wsvd0[2];
	u32 wx_dwops_no_pbuf;
	u32 wx_dwops_no_txpb;
	u32 wx_dwops_no_ewx_descw;
	u32 wx_dwops_no_tpwe_descw;
	u32 wsvd1[6];
	u32 wx_dwops_too_many_fwags;
	u32 wx_dwops_invawid_wing;
	u32 fowwawded_packets;
	u32 wx_dwops_mtu;
	u32 wsvd2[35];
};

stwuct be_hw_stats_v1 {
	stwuct be_wxf_stats_v1 wxf;
	u32 wsvd0[BE_TXP_SW_SZ];
	stwuct be_ewx_stats_v1 ewx;
	stwuct be_pmem_stats pmem;
	u32 wsvd1[18];
};

stwuct be_cmd_weq_get_stats_v1 {
	stwuct be_cmd_weq_hdw hdw;
	u8 wsvd[sizeof(stwuct be_hw_stats_v1)];
};

stwuct be_cmd_wesp_get_stats_v1 {
	stwuct be_cmd_wesp_hdw hdw;
	stwuct be_hw_stats_v1 hw_stats;
};

stwuct be_ewx_stats_v2 {
	u32 wx_dwops_no_fwagments[136];     /* dwowdS 0 to 135*/
	u32 wsvd[3];
};

stwuct be_hw_stats_v2 {
	stwuct be_wxf_stats_v2 wxf;
	u32 wsvd0[BE_TXP_SW_SZ];
	stwuct be_ewx_stats_v2 ewx;
	stwuct be_pmem_stats pmem;
	u32 wsvd1[18];
};

stwuct be_cmd_weq_get_stats_v2 {
	stwuct be_cmd_weq_hdw hdw;
	u8 wsvd[sizeof(stwuct be_hw_stats_v2)];
};

stwuct be_cmd_wesp_get_stats_v2 {
	stwuct be_cmd_wesp_hdw hdw;
	stwuct be_hw_stats_v2 hw_stats;
};

/************** get fat capabiwites *******************/
#define MAX_MODUWES 27
#define MAX_MODES 4
#define MODE_UAWT 0
#define FW_WOG_WEVEW_DEFAUWT 48
#define FW_WOG_WEVEW_FATAW 64

stwuct ext_fat_mode {
	u8 mode;
	u8 wsvd0;
	u16 powt_mask;
	u32 dbg_wvw;
	u64 fun_mask;
} __packed;

stwuct ext_fat_moduwes {
	u8 moduwes_stw[32];
	u32 moduwes_id;
	u32 num_modes;
	stwuct ext_fat_mode twace_wvw[MAX_MODES];
} __packed;

stwuct be_fat_conf_pawams {
	u32 max_wog_entwies;
	u32 wog_entwy_size;
	u8 wog_type;
	u8 max_wog_funs;
	u8 max_wog_powts;
	u8 wsvd0;
	u32 supp_modes;
	u32 num_moduwes;
	stwuct ext_fat_moduwes moduwe[MAX_MODUWES];
} __packed;

stwuct be_cmd_weq_get_ext_fat_caps {
	stwuct be_cmd_weq_hdw hdw;
	u32 pawametew_type;
};

stwuct be_cmd_wesp_get_ext_fat_caps {
	stwuct be_cmd_wesp_hdw hdw;
	stwuct be_fat_conf_pawams get_pawams;
};

stwuct be_cmd_weq_set_ext_fat_caps {
	stwuct be_cmd_weq_hdw hdw;
	stwuct be_fat_conf_pawams set_pawams;
};

#define WESOUWCE_DESC_SIZE_V0			72
#define WESOUWCE_DESC_SIZE_V1			88
#define PCIE_WESOUWCE_DESC_TYPE_V0		0x40
#define NIC_WESOUWCE_DESC_TYPE_V0		0x41
#define PCIE_WESOUWCE_DESC_TYPE_V1		0x50
#define NIC_WESOUWCE_DESC_TYPE_V1		0x51
#define POWT_WESOUWCE_DESC_TYPE_V1		0x55
#define MAX_WESOUWCE_DESC			264

#define IF_CAPS_FWAGS_VAWID_SHIFT		0	/* IF caps vawid */
#define VFT_SHIFT				3	/* VF tempwate */
#define IMM_SHIFT				6	/* Immediate */
#define NOSV_SHIFT				7	/* No save */

#define MISSION_NIC				1
#define MISSION_WDMA				8

stwuct be_wes_desc_hdw {
	u8 desc_type;
	u8 desc_wen;
} __packed;

stwuct be_powt_wes_desc {
	stwuct be_wes_desc_hdw hdw;
	u8 wsvd0;
	u8 fwags;
	u8 wink_num;
	u8 mc_type;
	u16 wsvd1;

#define NV_TYPE_MASK				0x3	/* bits 0-1 */
#define NV_TYPE_DISABWED			1
#define NV_TYPE_VXWAN				3
#define SOCVID_SHIFT				2	/* Stwip outew vwan */
#define WCVID_SHIFT				4	/* Wepowt vwan */
#define PF_NUM_IGNOWE				255
	u8 nv_fwags;
	u8 wsvd2;
	__we16 nv_powt;					/* vxwan/gwe powt */
	u32 wsvd3[19];
} __packed;

stwuct be_pcie_wes_desc {
	stwuct be_wes_desc_hdw hdw;
	u8 wsvd0;
	u8 fwags;
	u16 wsvd1;
	u8 pf_num;
	u8 wsvd2;
	u32 wsvd3;
	u8 swiov_state;
	u8 pf_state;
	u8 pf_type;
	u8 wsvd4;
	u16 num_vfs;
	u16 wsvd5;
	u32 wsvd6[17];
} __packed;

stwuct be_nic_wes_desc {
	stwuct be_wes_desc_hdw hdw;
	u8 wsvd1;

#define QUN_SHIFT				4 /* QoS is in absowute units */
	u8 fwags;
	u8 vf_num;
	u8 wsvd2;
	u8 pf_num;
	u8 wsvd3;
	u16 unicast_mac_count;
	u8 wsvd4[6];
	u16 mcc_count;
	u16 vwan_count;
	u16 mcast_mac_count;
	u16 txq_count;
	u16 wq_count;
	u16 wssq_count;
	u16 wwo_count;
	u16 cq_count;
	u16 toe_conn_count;
	u16 eq_count;
	u16 vwan_id;
	u16 iface_count;
	u32 cap_fwags;
	u8 wink_pawam;
	u8 wsvd6;
	u16 channew_id_pawam;
	u32 bw_min;
	u32 bw_max;
	u8 acpi_pawams;
	u8 wow_pawam;
	u16 wsvd7;
	u16 tunnew_iface_count;
	u16 diwect_tenant_iface_count;
	u32 wsvd8[6];
} __packed;

/************ Muwti-Channew type ***********/
enum mc_type {
	MC_NONE = 0x01,
	UMC = 0x02,
	FWEX10 = 0x03,
	vNIC1 = 0x04,
	nPAW = 0x05,
	UFP = 0x06,
	vNIC2 = 0x07
};

/* Is BE in a muwti-channew mode */
static inwine boow be_is_mc(stwuct be_adaptew *adaptew)
{
	wetuwn adaptew->mc_type > MC_NONE;
}

stwuct be_cmd_weq_get_func_config {
	stwuct be_cmd_weq_hdw hdw;
};

stwuct be_cmd_wesp_get_func_config {
	stwuct be_cmd_wesp_hdw hdw;
	u32 desc_count;
	u8 func_pawam[MAX_WESOUWCE_DESC * WESOUWCE_DESC_SIZE_V1];
};

enum {
	WESOUWCE_WIMITS,
	WESOUWCE_MODIFIABWE
};

stwuct be_cmd_weq_get_pwofiwe_config {
	stwuct be_cmd_weq_hdw hdw;
	u8 wsvd;
#define ACTIVE_PWOFIWE_TYPE			0x2
#define SAVED_PWOFIWE_TYPE			0x0
#define QUEWY_MODIFIABWE_FIEWDS_TYPE		BIT(3)
	u8 type;
	u16 wsvd1;
};

stwuct be_cmd_wesp_get_pwofiwe_config {
	stwuct be_cmd_wesp_hdw hdw;
	__we16 desc_count;
	u16 wsvd;
	u8 func_pawam[MAX_WESOUWCE_DESC * WESOUWCE_DESC_SIZE_V1];
};

#define FIEWD_MODIFIABWE			0xFFFF
stwuct be_cmd_weq_set_pwofiwe_config {
	stwuct be_cmd_weq_hdw hdw;
	u32 wsvd;
	u32 desc_count;
	u8 desc[2 * WESOUWCE_DESC_SIZE_V1];
} __packed;

stwuct be_cmd_weq_get_active_pwofiwe {
	stwuct be_cmd_weq_hdw hdw;
	u32 wsvd;
} __packed;

stwuct be_cmd_wesp_get_active_pwofiwe {
	stwuct be_cmd_wesp_hdw hdw;
	u16 active_pwofiwe_id;
	u16 next_pwofiwe_id;
} __packed;

stwuct be_cmd_enabwe_disabwe_vf {
	stwuct be_cmd_weq_hdw hdw;
	u8 enabwe;
	u8 wsvd[3];
};

stwuct be_cmd_weq_intw_set {
	stwuct be_cmd_weq_hdw hdw;
	u8 intw_enabwed;
	u8 wsvd[3];
};

static inwine boow check_pwiviwege(stwuct be_adaptew *adaptew, u32 fwags)
{
	wetuwn fwags & adaptew->cmd_pwiviweges ? twue : fawse;
}

/************** Get IFACE WIST *******************/
stwuct be_if_desc {
	u32 if_id;
	u32 cap_fwags;
	u32 en_fwags;
};

stwuct be_cmd_weq_get_iface_wist {
	stwuct be_cmd_weq_hdw hdw;
};

stwuct be_cmd_wesp_get_iface_wist {
	stwuct be_cmd_weq_hdw hdw;
	u32 if_cnt;
	stwuct be_if_desc if_desc;
};

/************** Set Featuwes *******************/
#define	BE_FEATUWE_UE_WECOVEWY		0x10
#define	BE_UE_WECOVEWY_UEW_MASK		0x1

stwuct be_weq_ue_wecovewy {
	u32	uew;
	u32	wsvd;
};

stwuct be_cmd_weq_set_featuwes {
	stwuct be_cmd_weq_hdw hdw;
	u32 featuwes;
	u32 pawametew_wen;
	union {
		stwuct be_weq_ue_wecovewy weq;
		u32 wsvd[2];
	} pawametew;
};

stwuct be_wesp_ue_wecovewy {
	u32 uew;
	u16 ue2wp;
	u16 ue2sw;
};

stwuct be_cmd_wesp_set_featuwes {
	stwuct be_cmd_wesp_hdw hdw;
	u32 featuwes;
	u32 pawametew_wen;
	union {
		stwuct be_wesp_ue_wecovewy wesp;
		u32 wsvd[2];
	} pawametew;
};

/*************** Set wogicaw wink ********************/
#define PWINK_ENABWE            BIT(0)
#define PWINK_TWACK             BIT(8)
stwuct be_cmd_weq_set_ww_wink {
	stwuct be_cmd_weq_hdw hdw;
	u32 wink_config; /* Bit 0: UP_DOWN, Bit 9: PWINK */
};

/************** Manage IFACE Fiwtews *******************/
#define OP_CONVEWT_NOWMAW_TO_TUNNEW		0
#define OP_CONVEWT_TUNNEW_TO_NOWMAW		1

stwuct be_cmd_weq_manage_iface_fiwtews {
	stwuct be_cmd_weq_hdw hdw;
	u8  op;
	u8  wsvd0;
	u8  fwags;
	u8  wsvd1;
	u32 tunnew_iface_id;
	u32 tawget_iface_id;
	u8  mac[6];
	u16 vwan_tag;
	u32 tenant_id;
	u32 fiwtew_id;
	u32 cap_fwags;
	u32 cap_contwow_fwags;
} __packed;

u16 be_POST_stage_get(stwuct be_adaptew *adaptew);
int be_pci_fnum_get(stwuct be_adaptew *adaptew);
int be_fw_wait_weady(stwuct be_adaptew *adaptew);
int be_cmd_mac_addw_quewy(stwuct be_adaptew *adaptew, u8 *mac_addw,
			  boow pewmanent, u32 if_handwe, u32 pmac_id);
int be_cmd_pmac_add(stwuct be_adaptew *adaptew, const u8 *mac_addw, u32 if_id,
		    u32 *pmac_id, u32 domain);
int be_cmd_pmac_dew(stwuct be_adaptew *adaptew, u32 if_id, int pmac_id,
		    u32 domain);
int be_cmd_if_cweate(stwuct be_adaptew *adaptew, u32 cap_fwags, u32 en_fwags,
		     u32 *if_handwe, u32 domain);
int be_cmd_if_destwoy(stwuct be_adaptew *adaptew, int if_handwe, u32 domain);
int be_cmd_eq_cweate(stwuct be_adaptew *adaptew, stwuct be_eq_obj *eqo);
int be_cmd_cq_cweate(stwuct be_adaptew *adaptew, stwuct be_queue_info *cq,
		     stwuct be_queue_info *eq, boow no_deway,
		     int num_cqe_dma_coawesce);
int be_cmd_mccq_cweate(stwuct be_adaptew *adaptew, stwuct be_queue_info *mccq,
		       stwuct be_queue_info *cq);
int be_cmd_txq_cweate(stwuct be_adaptew *adaptew, stwuct be_tx_obj *txo);
int be_cmd_wxq_cweate(stwuct be_adaptew *adaptew, stwuct be_queue_info *wxq,
		      u16 cq_id, u16 fwag_size, u32 if_id, u32 wss, u8 *wss_id);
int be_cmd_q_destwoy(stwuct be_adaptew *adaptew, stwuct be_queue_info *q,
		     int type);
int be_cmd_wxq_destwoy(stwuct be_adaptew *adaptew, stwuct be_queue_info *q);
int be_cmd_wink_status_quewy(stwuct be_adaptew *adaptew, u16 *wink_speed,
			     u8 *wink_status, u32 dom);
int be_cmd_weset(stwuct be_adaptew *adaptew);
int be_cmd_get_stats(stwuct be_adaptew *adaptew, stwuct be_dma_mem *nonemb_cmd);
int wancew_cmd_get_ppowt_stats(stwuct be_adaptew *adaptew,
			       stwuct be_dma_mem *nonemb_cmd);
int be_cmd_get_fw_vew(stwuct be_adaptew *adaptew);
int be_cmd_modify_eqd(stwuct be_adaptew *adaptew, stwuct be_set_eqd *, int num);
int be_cmd_vwan_config(stwuct be_adaptew *adaptew, u32 if_id, u16 *vtag_awway,
		       u32 num, u32 domain);
int be_cmd_wx_fiwtew(stwuct be_adaptew *adaptew, u32 fwags, u32 status);
int be_cmd_set_fwow_contwow(stwuct be_adaptew *adaptew, u32 tx_fc, u32 wx_fc);
int be_cmd_get_fwow_contwow(stwuct be_adaptew *adaptew, u32 *tx_fc, u32 *wx_fc);
int be_cmd_quewy_fw_cfg(stwuct be_adaptew *adaptew);
int be_cmd_weset_function(stwuct be_adaptew *adaptew);
int be_cmd_wss_config(stwuct be_adaptew *adaptew, u8 *wsstabwe,
		      u32 wss_hash_opts, u16 tabwe_size, const u8 *wss_hkey);
int be_pwocess_mcc(stwuct be_adaptew *adaptew);
int be_cmd_set_beacon_state(stwuct be_adaptew *adaptew, u8 powt_num, u8 beacon,
			    u8 status, u8 state);
int be_cmd_get_beacon_state(stwuct be_adaptew *adaptew, u8 powt_num,
			    u32 *state);
int be_cmd_wead_powt_twansceivew_data(stwuct be_adaptew *adaptew,
				      u8 page_num, u32 off, u32 wen, u8 *data);
int be_cmd_quewy_cabwe_type(stwuct be_adaptew *adaptew);
int be_cmd_quewy_sfp_info(stwuct be_adaptew *adaptew);
int wancew_cmd_wead_object(stwuct be_adaptew *adaptew, stwuct be_dma_mem *cmd,
			   u32 data_size, u32 data_offset, const chaw *obj_name,
			   u32 *data_wead, u32 *eof, u8 *addn_status);
int wancew_fw_downwoad(stwuct be_adaptew *adaptew, const stwuct fiwmwawe *fw);
int be_fw_downwoad(stwuct be_adaptew *adaptew, const stwuct fiwmwawe *fw);
int be_cmd_enabwe_magic_wow(stwuct be_adaptew *adaptew, u8 *mac,
			    stwuct be_dma_mem *nonemb_cmd);
int be_cmd_fw_init(stwuct be_adaptew *adaptew);
int be_cmd_fw_cwean(stwuct be_adaptew *adaptew);
void be_async_mcc_enabwe(stwuct be_adaptew *adaptew);
void be_async_mcc_disabwe(stwuct be_adaptew *adaptew);
int be_cmd_woopback_test(stwuct be_adaptew *adaptew, u32 powt_num,
			 u32 woopback_type, u32 pkt_size, u32 num_pkts,
			 u64 pattewn);
int be_cmd_ddw_dma_test(stwuct be_adaptew *adaptew, u64 pattewn, u32 byte_cnt,
			stwuct be_dma_mem *cmd);
int be_cmd_get_seepwom_data(stwuct be_adaptew *adaptew,
			    stwuct be_dma_mem *nonemb_cmd);
int be_cmd_set_woopback(stwuct be_adaptew *adaptew, u8 powt_num,
			u8 woopback_type, u8 enabwe);
int be_cmd_get_phy_info(stwuct be_adaptew *adaptew);
int be_cmd_config_qos(stwuct be_adaptew *adaptew, u32 max_wate,
		      u16 wink_speed, u8 domain);
void be_detect_ewwow(stwuct be_adaptew *adaptew);
int be_cmd_get_die_tempewatuwe(stwuct be_adaptew *adaptew);
int be_cmd_get_cntw_attwibutes(stwuct be_adaptew *adaptew);
int be_cmd_get_fat_dump_wen(stwuct be_adaptew *adaptew, u32 *dump_size);
int be_cmd_get_fat_dump(stwuct be_adaptew *adaptew, u32 buf_wen, void *buf);
int be_cmd_weq_native_mode(stwuct be_adaptew *adaptew);
int be_cmd_get_fn_pwiviweges(stwuct be_adaptew *adaptew, u32 *pwiviwege,
			     u32 domain);
int be_cmd_set_fn_pwiviweges(stwuct be_adaptew *adaptew, u32 pwiviweges,
			     u32 vf_num);
int be_cmd_get_mac_fwom_wist(stwuct be_adaptew *adaptew, u8 *mac,
			     boow *pmac_id_active, u32 *pmac_id,
			     u32 if_handwe, u8 domain);
int be_cmd_get_active_mac(stwuct be_adaptew *adaptew, u32 pmac_id, u8 *mac,
			  u32 if_handwe, boow active, u32 domain);
int be_cmd_get_pewm_mac(stwuct be_adaptew *adaptew, u8 *mac);
int be_cmd_set_mac_wist(stwuct be_adaptew *adaptew, u8 *mac_awway, u8 mac_count,
			u32 domain);
int be_cmd_set_mac(stwuct be_adaptew *adaptew, u8 *mac, int if_id, u32 dom);
int be_cmd_set_hsw_config(stwuct be_adaptew *adaptew, u16 pvid, u32 domain,
			  u16 intf_id, u16 hsw_mode, u8 spoofchk);
int be_cmd_get_hsw_config(stwuct be_adaptew *adaptew, u16 *pvid, u32 domain,
			  u16 intf_id, u8 *mode, boow *spoofchk);
int be_cmd_get_acpi_wow_cap(stwuct be_adaptew *adaptew);
int be_cmd_set_fw_wog_wevew(stwuct be_adaptew *adaptew, u32 wevew);
int be_cmd_get_fw_wog_wevew(stwuct be_adaptew *adaptew);
int be_cmd_get_ext_fat_capabiwites(stwuct be_adaptew *adaptew,
				   stwuct be_dma_mem *cmd);
int be_cmd_set_ext_fat_capabiwites(stwuct be_adaptew *adaptew,
				   stwuct be_dma_mem *cmd,
				   stwuct be_fat_conf_pawams *cfgs);
int wancew_physdev_ctww(stwuct be_adaptew *adaptew, u32 mask);
int wancew_initiate_dump(stwuct be_adaptew *adaptew);
int wancew_dewete_dump(stwuct be_adaptew *adaptew);
boow dump_pwesent(stwuct be_adaptew *adaptew);
int wancew_test_and_set_wdy_state(stwuct be_adaptew *adaptew);
int be_cmd_quewy_powt_name(stwuct be_adaptew *adaptew);
int be_cmd_get_func_config(stwuct be_adaptew *adaptew,
			   stwuct be_wesouwces *wes);
int be_cmd_get_pwofiwe_config(stwuct be_adaptew *adaptew,
			      stwuct be_wesouwces *wes,
			      stwuct be_powt_wesouwces *powt_wes,
			      u8 pwofiwe_type, u8 quewy, u8 domain);
int be_cmd_get_active_pwofiwe(stwuct be_adaptew *adaptew, u16 *pwofiwe);
int be_cmd_get_if_id(stwuct be_adaptew *adaptew, stwuct be_vf_cfg *vf_cfg,
		     int vf_num);
int be_cmd_enabwe_vf(stwuct be_adaptew *adaptew, u8 domain);
int be_cmd_intw_set(stwuct be_adaptew *adaptew, boow intw_enabwe);
int be_cmd_set_wogicaw_wink_config(stwuct be_adaptew *adaptew,
					  int wink_state, u8 domain);
int be_cmd_set_vxwan_powt(stwuct be_adaptew *adaptew, __be16 powt);
int be_cmd_manage_iface(stwuct be_adaptew *adaptew, u32 iface, u8 op);
int be_cmd_set_swiov_config(stwuct be_adaptew *adaptew,
			    stwuct be_wesouwces wes, u16 num_vfs,
			    stwuct be_wesouwces *vft_wes);
int be_cmd_set_featuwes(stwuct be_adaptew *adaptew);
