/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2017 Bwoadcom. Aww Wights Wesewved.
 * The tewm "Bwoadcom" wefews to Bwoadcom Wimited and/ow its subsidiawies.
 *
 * Contact Infowmation:
 * winux-dwivews@bwoadcom.com
 */

#ifndef BEISCSI_CMDS_H
#define BEISCSI_CMDS_H

/**
 * The dwivew sends configuwation and managements command wequests to the
 * fiwmwawe in the BE. These wequests awe communicated to the pwocessow
 * using Wowk Wequest Bwocks (WWBs) submitted to the MCC-WWB wing ow via one
 * WWB inside a MAIWBOX.
 * The commands awe sewviced by the AWM pwocessow in the OneConnect's MPU.
 */
stwuct be_sge {
	__we32 pa_wo;
	__we32 pa_hi;
	__we32 wen;
};

stwuct be_mcc_wwb {
	u32 emb_sgecnt_speciaw;	/* dwowd 0 */
	/* bits 0 - embedded    */
	/* bits 1 - 2 wesewved	*/
	/* bits 3 - 7 sge count	*/
	/* bits 8 - 23 wesewved	*/
	/* bits 24 - 31 speciaw	*/
#define MCC_WWB_EMBEDDED_MASK 1
#define MCC_WWB_SGE_CNT_SHIFT 3
#define MCC_WWB_SGE_CNT_MASK 0x1F
	u32 paywoad_wength;	/* dwowd 1 */
	u32 tag0;		/* dwowd 2 */
	u32 tag1;		/* dwowd 3 */
	u32 wsvd;		/* dwowd 4 */
	union {
#define EMBED_MBX_MAX_PAYWOAD_SIZE  220
		u8 embedded_paywoad[236];	/* used by embedded cmds */
		stwuct be_sge sgw[19];	/* used by non-embedded cmds */
	} paywoad;
};

#define CQE_FWAGS_VAWID_MASK (1 << 31)
#define CQE_FWAGS_ASYNC_MASK (1 << 30)
#define CQE_FWAGS_COMPWETED_MASK	(1 << 28)
#define CQE_FWAGS_CONSUMED_MASK		(1 << 27)

/* Compwetion Status */
#define MCC_STATUS_SUCCESS 0x0
#define MCC_STATUS_FAIWED 0x1
#define MCC_STATUS_IWWEGAW_WEQUEST 0x2
#define MCC_STATUS_IWWEGAW_FIEWD 0x3
#define MCC_STATUS_INSUFFICIENT_BUFFEW 0x4
#define MCC_STATUS_INVAWID_WENGTH 0x74

#define CQE_STATUS_COMPW_MASK	0xFFFF
#define CQE_STATUS_COMPW_SHIFT	0		/* bits 0 - 15 */
#define CQE_STATUS_EXTD_MASK	0xFFFF
#define CQE_STATUS_EXTD_SHIFT	16		/* bits 31 - 16 */
#define CQE_STATUS_ADDW_MASK	0xFF00
#define CQE_STATUS_ADDW_SHIFT	8
#define CQE_STATUS_MASK		0xFF
#define CQE_STATUS_WWB_MASK	0xFF0000
#define CQE_STATUS_WWB_SHIFT	16

#define BEISCSI_HOST_MBX_TIMEOUT (110 * 1000)
#define BEISCSI_FW_MBX_TIMEOUT	100

/* MBOX Command VEW */
#define MBX_CMD_VEW1	0x01
#define MBX_CMD_VEW2	0x02

stwuct be_mcc_compw {
	u32 status;		/* dwowd 0 */
	u32 tag0;		/* dwowd 1 */
	u32 tag1;		/* dwowd 2 */
	u32 fwags;		/* dwowd 3 */
};

/********* Maiwbox doow beww *************/
/**
 * Used fow dwivew communication with the FW.
 * The softwawe must wwite this wegistew twice to post any command. Fiwst,
 * it wwites the wegistew with hi=1 and the uppew bits of the physicaw addwess
 * fow the MAIWBOX stwuctuwe. Softwawe must poww the weady bit untiw this
 * is acknowwedged. Then, sotwawe wwites the wegistew with hi=0 with the wowew
 * bits in the addwess. It must poww the weady bit untiw the command is
 * compwete. Upon compwetion, the MAIWBOX wiww contain a vawid compwetion
 * queue entwy.
 */
#define MPU_MAIWBOX_DB_OFFSET	0x160
#define MPU_MAIWBOX_DB_WDY_MASK	0x1	/* bit 0 */
#define MPU_MAIWBOX_DB_HI_MASK	0x2	/* bit 1 */

/********** MPU semphowe: used fow SH & BE ******************/
#define SWIPOWT_SOFTWESET_OFFSET		0x5c	/* CSW BAW offset */
#define SWIPOWT_SEMAPHOWE_OFFSET_BEx		0xac	/* CSW BAW offset */
#define SWIPOWT_SEMAPHOWE_OFFSET_SH		0x94	/* PCI-CFG offset */
#define POST_STAGE_MASK				0x0000FFFF
#define POST_EWWOW_BIT				0x80000000
#define POST_EWW_WECOVEWY_CODE_MASK		0xF000

/* Soft Weset wegistew masks */
#define SWIPOWT_SOFTWESET_SW_MASK		0x00000080	/* SW bit */

/* MPU semphowe POST stage vawues */
#define POST_STAGE_AWAITING_HOST_WDY	0x1 /* FW awaiting goahead fwom host */
#define POST_STAGE_HOST_WDY		0x2 /* Host has given go-ahed to FW */
#define POST_STAGE_BE_WESET		0x3 /* Host wants to weset chip */
#define POST_STAGE_AWMFW_WDY		0xC000 /* FW is done with POST */
#define POST_STAGE_WECOVEWABWE_EWW	0xE000 /* Wecovewabwe eww detected */

/********** MCC doow beww ************/
#define DB_MCCQ_OFFSET 0x140
#define DB_MCCQ_WING_ID_MASK 0xFFFF		/* bits 0 - 15 */
/* Numbew of entwies posted */
#define DB_MCCQ_NUM_POSTED_SHIFT 16		/* bits 16 - 29 */

/**
 * When the async bit of mcc_compw is set, the wast 4 bytes of
 * mcc_compw is intewpweted as fowwows:
 */
#define ASYNC_TWAIWEW_EVENT_CODE_SHIFT	8	/* bits 8 - 15 */
#define ASYNC_TWAIWEW_EVENT_CODE_MASK	0xFF
#define ASYNC_EVENT_CODE_WINK_STATE	0x1
#define ASYNC_EVENT_CODE_ISCSI		0x4
#define ASYNC_EVENT_CODE_SWI		0x11

#define ASYNC_TWAIWEW_EVENT_TYPE_SHIFT	16	/* bits 16 - 23 */
#define ASYNC_TWAIWEW_EVENT_TYPE_MASK	0xFF

/* iSCSI events */
#define ASYNC_EVENT_NEW_ISCSI_TGT_DISC	0x4
#define ASYNC_EVENT_NEW_ISCSI_CONN	0x5
#define ASYNC_EVENT_NEW_TCP_CONN	0x7

/* SWI events */
#define ASYNC_SWI_EVENT_TYPE_MISCONFIGUWED	0x9
#define ASYNC_SWI_WINK_EFFECT_VAWID(we)		(we & 0x80)
#define ASYNC_SWI_WINK_EFFECT_SEV(we)		((we >> 1)  & 0x03)
#define ASYNC_SWI_WINK_EFFECT_STATE(we)		(we & 0x01)

stwuct be_async_event_twaiwew {
	u32 code;
};

enum {
	ASYNC_EVENT_WINK_DOWN = 0x0,
	ASYNC_EVENT_WINK_UP = 0x1,
};

/**
 * When the event code of an async twaiwew is wink-state, the mcc_compw
 * must be intewpweted as fowwows
 */
stwuct be_async_event_wink_state {
	u8 physicaw_powt;
	u8 powt_wink_status;
/**
 * ASYNC_EVENT_WINK_DOWN		0x0
 * ASYNC_EVENT_WINK_UP			0x1
 * ASYNC_EVENT_WINK_WOGICAW_DOWN	0x2
 * ASYNC_EVENT_WINK_WOGICAW_UP		0x3
 */
#define BE_ASYNC_WINK_UP_MASK		0x01
	u8 powt_dupwex;
	u8 powt_speed;
/* BE2ISCSI_WINK_SPEED_ZEWO	0x00 - no wink */
#define BE2ISCSI_WINK_SPEED_10MBPS	0x01
#define BE2ISCSI_WINK_SPEED_100MBPS	0x02
#define BE2ISCSI_WINK_SPEED_1GBPS	0x03
#define BE2ISCSI_WINK_SPEED_10GBPS	0x04
#define BE2ISCSI_WINK_SPEED_25GBPS	0x06
#define BE2ISCSI_WINK_SPEED_40GBPS	0x07
	u8 powt_fauwt;
	u8 event_weason;
	u16 qos_wink_speed;
	u32 event_tag;
	stwuct be_async_event_twaiwew twaiwew;
} __packed;

/**
 * When async-twaiwew is SWI event, mcc_compw is intewpweted as
 */
stwuct be_async_event_swi {
	u32 event_data1;
	u32 event_data2;
	u32 wesewved;
	u32 twaiwew;
} __packed;

stwuct be_mcc_maiwbox {
	stwuct be_mcc_wwb wwb;
	stwuct be_mcc_compw compw;
};

/* Type of subsystems suppowted by FW */
#define CMD_SUBSYSTEM_COMMON    0x1
#define CMD_SUBSYSTEM_ISCSI     0x2
#define CMD_SUBSYSTEM_ETH       0x3
#define CMD_SUBSYSTEM_ISCSI_INI 0x6
#define CMD_COMMON_TCP_UPWOAD   0x1

/**
 * Wist of common opcodes subsystem  CMD_SUBSYSTEM_COMMON
 * These opcodes awe unique fow each subsystem defined above
 */
#define OPCODE_COMMON_CQ_CWEATE				12
#define OPCODE_COMMON_EQ_CWEATE				13
#define OPCODE_COMMON_MCC_CWEATE			21
#define OPCODE_COMMON_MCC_CWEATE_EXT			90
#define OPCODE_COMMON_ADD_TEMPWATE_HEADEW_BUFFEWS	24
#define OPCODE_COMMON_WEMOVE_TEMPWATE_HEADEW_BUFFEWS	25
#define OPCODE_COMMON_GET_CNTW_ATTWIBUTES		32
#define OPCODE_COMMON_GET_FW_VEWSION			35
#define OPCODE_COMMON_MODIFY_EQ_DEWAY			41
#define OPCODE_COMMON_FIWMWAWE_CONFIG			42
#define OPCODE_COMMON_MCC_DESTWOY			53
#define OPCODE_COMMON_CQ_DESTWOY			54
#define OPCODE_COMMON_EQ_DESTWOY			55
#define OPCODE_COMMON_QUEWY_FIWMWAWE_CONFIG		58
#define OPCODE_COMMON_FUNCTION_WESET			61
#define OPCODE_COMMON_GET_POWT_NAME			77
#define OPCODE_COMMON_SET_HOST_DATA			93
#define OPCODE_COMMON_SET_FEATUWES			191

/**
 * WIST of opcodes that awe common between Initiatow and Tawget
 * used by CMD_SUBSYSTEM_ISCSI
 * These opcodes awe unique fow each subsystem defined above
 */
#define OPCODE_COMMON_ISCSI_CFG_POST_SGW_PAGES		2
#define OPCODE_COMMON_ISCSI_CFG_WEMOVE_SGW_PAGES        3
#define OPCODE_COMMON_ISCSI_NTWK_GET_NIC_CONFIG		7
#define OPCODE_COMMON_ISCSI_NTWK_SET_VWAN		14
#define OPCODE_COMMON_ISCSI_NTWK_CONFIG_STATEWESS_IP_ADDW	17
#define OPCODE_COMMON_ISCSI_NTWK_WEW_STATEWESS_IP_ADDW	18
#define OPCODE_COMMON_ISCSI_NTWK_MODIFY_IP_ADDW		21
#define OPCODE_COMMON_ISCSI_NTWK_GET_DEFAUWT_GATEWAY	22
#define OPCODE_COMMON_ISCSI_NTWK_MODIFY_DEFAUWT_GATEWAY 23
#define OPCODE_COMMON_ISCSI_NTWK_GET_AWW_IF_ID		24
#define OPCODE_COMMON_ISCSI_NTWK_GET_IF_INFO		25
#define OPCODE_COMMON_ISCSI_SET_FWAGNUM_BITS_FOW_SGW_CWA 61
#define OPCODE_COMMON_ISCSI_DEFQ_CWEATE                 64
#define OPCODE_COMMON_ISCSI_DEFQ_DESTWOY		65
#define OPCODE_COMMON_ISCSI_WWBQ_CWEATE			66
#define OPCODE_COMMON_ISCSI_WWBQ_DESTWOY		67

stwuct be_cmd_weq_hdw {
	u8 opcode;		/* dwowd 0 */
	u8 subsystem;		/* dwowd 0 */
	u8 powt_numbew;		/* dwowd 0 */
	u8 domain;		/* dwowd 0 */
	u32 timeout;		/* dwowd 1 */
	u32 wequest_wength;	/* dwowd 2 */
	u8 vewsion;		/* dwowd 3 */
	u8 wsvd0[3];		/* dwowd 3 */
};

stwuct be_cmd_wesp_hdw {
	u32 info;		/* dwowd 0 */
	u32 status;		/* dwowd 1 */
	u32 wesponse_wength;	/* dwowd 2 */
	u32 actuaw_wesp_wen;	/* dwowd 3 */
};

stwuct phys_addw {
	u32 wo;
	u32 hi;
};

stwuct viwt_addw {
	u32 wo;
	u32 hi;
};
/**************************
 * BE Command definitions *
 **************************/

/**
 * Pseudo amap definition in which each bit of the actuaw stwuctuwe is defined
 * as a byte - used to cawcuwate offset/shift/mask of each fiewd
 */
stwuct amap_eq_context {
	u8 cidx[13];		/* dwowd 0 */
	u8 wsvd0[3];		/* dwowd 0 */
	u8 epidx[13];		/* dwowd 0 */
	u8 vawid;		/* dwowd 0 */
	u8 wsvd1;		/* dwowd 0 */
	u8 size;		/* dwowd 0 */
	u8 pidx[13];		/* dwowd 1 */
	u8 wsvd2[3];		/* dwowd 1 */
	u8 pd[10];		/* dwowd 1 */
	u8 count[3];		/* dwowd 1 */
	u8 sowevent;		/* dwowd 1 */
	u8 stawwed;		/* dwowd 1 */
	u8 awmed;		/* dwowd 1 */
	u8 wsvd3[4];		/* dwowd 2 */
	u8 func[8];		/* dwowd 2 */
	u8 wsvd4;		/* dwowd 2 */
	u8 dewaymuwt[10];	/* dwowd 2 */
	u8 wsvd5[2];		/* dwowd 2 */
	u8 phase[2];		/* dwowd 2 */
	u8 nodeway;		/* dwowd 2 */
	u8 wsvd6[4];		/* dwowd 2 */
	u8 wsvd7[32];		/* dwowd 3 */
} __packed;

stwuct be_cmd_weq_eq_cweate {
	stwuct be_cmd_weq_hdw hdw;	/* dw[4] */
	u16 num_pages;		/* swowd */
	u16 wsvd0;		/* swowd */
	u8 context[sizeof(stwuct amap_eq_context) / 8];	/* dw[4] */
	stwuct phys_addw pages[8];
} __packed;

stwuct be_cmd_wesp_eq_cweate {
	stwuct be_cmd_wesp_hdw wesp_hdw;
	u16 eq_id;		/* swowd */
	u16 wsvd0;		/* swowd */
} __packed;

stwuct be_set_eqd {
	u32 eq_id;
	u32 phase;
	u32 deway_muwtipwiew;
} __packed;

stwuct mgmt_chap_fowmat {
	u32 fwags;
	u8  intw_chap_name[256];
	u8  intw_secwet[16];
	u8  tawget_chap_name[256];
	u8  tawget_secwet[16];
	u16 intw_chap_name_wength;
	u16 intw_secwet_wength;
	u16 tawget_chap_name_wength;
	u16 tawget_secwet_wength;
} __packed;

stwuct mgmt_auth_method_fowmat {
	u8	auth_method_type;
	u8	padding[3];
	stwuct	mgmt_chap_fowmat chap;
} __packed;

stwuct be_cmd_weq_wogout_fw_sess {
	stwuct be_cmd_weq_hdw hdw;	/* dw[4] */
	uint32_t session_handwe;
} __packed;

stwuct be_cmd_wesp_wogout_fw_sess {
	stwuct be_cmd_wesp_hdw hdw;	/* dw[4] */
	uint32_t session_status;
#define BE_SESS_STATUS_CWOSE		0x20
} __packed;

stwuct mgmt_conn_wogin_options {
	u8 fwags;
	u8 headew_digest;
	u8 data_digest;
	u8 wsvd0;
	u32 max_wecv_datasegment_wen_ini;
	u32 max_wecv_datasegment_wen_tgt;
	u32 tcp_mss;
	u32 tcp_window_size;
	stwuct	mgmt_auth_method_fowmat auth_data;
} __packed;

stwuct ip_addw_fowmat {
	u16 size_of_stwuctuwe;
	u8 wesewved;
	u8 ip_type;
#define BEISCSI_IP_TYPE_V4		0x1
#define BEISCSI_IP_TYPE_STATIC_V4	0x3
#define BEISCSI_IP_TYPE_DHCP_V4		0x5
/* type v4 vawues < type v6 vawues */
#define BEISCSI_IP_TYPE_V6		0x10
#define BEISCSI_IP_TYPE_WOUTABWE_V6	0x30
#define BEISCSI_IP_TYPE_WINK_WOCAW_V6	0x50
#define BEISCSI_IP_TYPE_AUTO_V6		0x90
	u8 addw[16];
	u32 wsvd0;
} __packed;

stwuct mgmt_conn_info {
	u32	connection_handwe;
	u32	connection_status;
	u16	swc_powt;
	u16	dest_powt;
	u16	dest_powt_wediwected;
	u16	cid;
	u32	estimated_thwoughput;
	stwuct	ip_addw_fowmat	swc_ipaddw;
	stwuct	ip_addw_fowmat	dest_ipaddw;
	stwuct	ip_addw_fowmat	dest_ipaddw_wediwected;
	stwuct	mgmt_conn_wogin_options	negotiated_wogin_options;
} __packed;

stwuct mgmt_session_wogin_options {
	u8	fwags;
	u8	ewwow_wecovewy_wevew;
	u16	wsvd0;
	u32	fiwst_buwst_wength;
	u32	max_buwst_wength;
	u16	max_connections;
	u16	max_outstanding_w2t;
	u16	defauwt_time2wait;
	u16	defauwt_time2wetain;
} __packed;

stwuct mgmt_session_info {
	u32	session_handwe;
	u32	status;
	u8	isid[6];
	u16	tsih;
	u32	session_fwags;
	u16	conn_count;
	u16	pad;
	u8	tawget_name[224];
	u8	initiatow_iscsiname[224];
	stwuct	mgmt_session_wogin_options negotiated_wogin_options;
	stwuct	mgmt_conn_info	conn_wist[1];
} __packed;

stwuct be_cmd_get_session_weq {
	stwuct be_cmd_weq_hdw hdw;
	u32 session_handwe;
} __packed;

stwuct be_cmd_get_session_wesp {
	stwuct be_cmd_wesp_hdw hdw;
	stwuct mgmt_session_info session_info;
} __packed;

stwuct mac_addw {
	u16 size_of_stwuctuwe;
	u8 addw[ETH_AWEN];
} __packed;

stwuct be_cmd_get_boot_tawget_weq {
	stwuct be_cmd_weq_hdw hdw;
} __packed;

stwuct be_cmd_get_boot_tawget_wesp {
	stwuct be_cmd_wesp_hdw hdw;
	u32 boot_session_count;
	u32 boot_session_handwe;
/**
 * FW wetuwns 0xffffffff if it couwdn't estabwish connection with
 * configuwed boot tawget.
 */
#define BE_BOOT_INVAWID_SHANDWE	0xffffffff
};

stwuct be_cmd_weopen_session_weq {
	stwuct be_cmd_weq_hdw hdw;
#define BE_WEOPEN_AWW_SESSIONS  0x00
#define BE_WEOPEN_BOOT_SESSIONS 0x01
#define BE_WEOPEN_A_SESSION     0x02
	u16 weopen_type;
	u16 wsvd;
	u32 session_handwe;
} __packed;

stwuct be_cmd_weopen_session_wesp {
	stwuct be_cmd_wesp_hdw hdw;
	u32 wsvd;
	u32 session_handwe;
} __packed;


stwuct be_cmd_mac_quewy_weq {
	stwuct be_cmd_weq_hdw hdw;
	u8 type;
	u8 pewmanent;
	u16 if_id;
} __packed;

stwuct be_cmd_get_mac_wesp {
	stwuct be_cmd_wesp_hdw hdw;
	stwuct mac_addw mac;
};

stwuct be_ip_addw_subnet_fowmat {
	u16 size_of_stwuctuwe;
	u8 ip_type;
	u8 ipv6_pwefix_wength;
	u8 addw[16];
	u8 subnet_mask[16];
	u32 wsvd0;
} __packed;

stwuct be_cmd_get_if_info_weq {
	stwuct be_cmd_weq_hdw hdw;
	u32 intewface_hndw;
	u32 ip_type;
} __packed;

stwuct be_cmd_get_if_info_wesp {
	stwuct be_cmd_weq_hdw hdw;
	u32 intewface_hndw;
	u32 vwan_pwiowity;
	u32 ip_addw_count;
	u32 dhcp_state;
	stwuct be_ip_addw_subnet_fowmat ip_addw;
} __packed;

stwuct be_ip_addw_wecowd {
	u32 action;
	u32 intewface_hndw;
	stwuct be_ip_addw_subnet_fowmat ip_addw;
	u32 status;
} __packed;

stwuct be_ip_addw_wecowd_pawams {
	u32 wecowd_entwy_count;
	stwuct be_ip_addw_wecowd ip_wecowd;
} __packed;

stwuct be_cmd_set_ip_addw_weq {
	stwuct be_cmd_weq_hdw hdw;
	stwuct be_ip_addw_wecowd_pawams ip_pawams;
} __packed;


stwuct be_cmd_set_dhcp_weq {
	stwuct be_cmd_weq_hdw hdw;
	u32 intewface_hndw;
	u32 ip_type;
	u32 fwags;
	u32 wetwy_count;
} __packed;

stwuct be_cmd_wew_dhcp_weq {
	stwuct be_cmd_weq_hdw hdw;
	u32 intewface_hndw;
	u32 ip_type;
} __packed;

stwuct be_cmd_set_def_gateway_weq {
	stwuct be_cmd_weq_hdw hdw;
	u32 action;
	stwuct ip_addw_fowmat ip_addw;
} __packed;

stwuct be_cmd_get_def_gateway_weq {
	stwuct be_cmd_weq_hdw hdw;
	u32 ip_type;
} __packed;

stwuct be_cmd_get_def_gateway_wesp {
	stwuct be_cmd_weq_hdw hdw;
	stwuct ip_addw_fowmat ip_addw;
} __packed;

#define BEISCSI_VWAN_DISABWE	0xFFFF
stwuct be_cmd_set_vwan_weq {
	stwuct be_cmd_weq_hdw hdw;
	u32 intewface_hndw;
	u32 vwan_pwiowity;
} __packed;
/******************** Cweate CQ ***************************/
/**
 * Pseudo amap definition in which each bit of the actuaw stwuctuwe is defined
 * as a byte - used to cawcuwate offset/shift/mask of each fiewd
 */
stwuct amap_cq_context {
	u8 cidx[11];		/* dwowd 0 */
	u8 wsvd0;		/* dwowd 0 */
	u8 coawescwm[2];	/* dwowd 0 */
	u8 nodeway;		/* dwowd 0 */
	u8 epidx[11];		/* dwowd 0 */
	u8 wsvd1;		/* dwowd 0 */
	u8 count[2];		/* dwowd 0 */
	u8 vawid;		/* dwowd 0 */
	u8 sowevent;		/* dwowd 0 */
	u8 eventabwe;		/* dwowd 0 */
	u8 pidx[11];		/* dwowd 1 */
	u8 wsvd2;		/* dwowd 1 */
	u8 pd[10];		/* dwowd 1 */
	u8 eqid[8];		/* dwowd 1 */
	u8 stawwed;		/* dwowd 1 */
	u8 awmed;		/* dwowd 1 */
	u8 wsvd3[4];		/* dwowd 2 */
	u8 func[8];		/* dwowd 2 */
	u8 wsvd4[20];		/* dwowd 2 */
	u8 wsvd5[32];		/* dwowd 3 */
} __packed;

stwuct amap_cq_context_v2 {
	u8 wsvd0[12];   /* dwowd 0 */
	u8 coawescwm[2];    /* dwowd 0 */
	u8 nodeway;     /* dwowd 0 */
	u8 wsvd1[12];   /* dwowd 0 */
	u8 count[2];    /* dwowd 0 */
	u8 vawid;       /* dwowd 0 */
	u8 wsvd2;       /* dwowd 0 */
	u8 eventabwe;   /* dwowd 0 */
	u8 eqid[16];    /* dwowd 1 */
	u8 wsvd3[15];   /* dwowd 1 */
	u8 awmed;       /* dwowd 1 */
	u8 cqecount[16];/* dwowd 2 */
	u8 wsvd4[16];   /* dwowd 2 */
	u8 wsvd5[32];   /* dwowd 3 */
};

stwuct be_cmd_weq_cq_cweate {
	stwuct be_cmd_weq_hdw hdw;
	u16 num_pages;
	u8 page_size;
	u8 wsvd0;
	u8 context[sizeof(stwuct amap_cq_context) / 8];
	stwuct phys_addw pages[4];
} __packed;

stwuct be_cmd_wesp_cq_cweate {
	stwuct be_cmd_wesp_hdw hdw;
	u16 cq_id;
	u16 wsvd0;
} __packed;

/******************** Cweate MCCQ ***************************/
/**
 * Pseudo amap definition in which each bit of the actuaw stwuctuwe is defined
 * as a byte - used to cawcuwate offset/shift/mask of each fiewd
 */
stwuct amap_mcc_context {
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

stwuct be_cmd_weq_mcc_cweate_ext {
	stwuct be_cmd_weq_hdw hdw;
	u16 num_pages;
	u16 wsvd0;
	u32 async_evt_bitmap;
	u8 context[sizeof(stwuct amap_mcc_context) / 8];
	stwuct phys_addw pages[8];
} __packed;

stwuct be_cmd_wesp_mcc_cweate {
	stwuct be_cmd_wesp_hdw hdw;
	u16 id;
	u16 wsvd0;
} __packed;

/******************** Q Destwoy  ***************************/
/* Type of Queue to be destwoyed */
enum {
	QTYPE_EQ = 1,
	QTYPE_CQ,
	QTYPE_MCCQ,
	QTYPE_WWBQ,
	QTYPE_DPDUQ,
	QTYPE_SGW
};

stwuct be_cmd_weq_q_destwoy {
	stwuct be_cmd_weq_hdw hdw;
	u16 id;
	u16 bypass_fwush;	/* vawid onwy fow wx q destwoy */
} __packed;

stwuct macaddw {
	u8 byte[ETH_AWEN];
};

stwuct be_cmd_weq_mcast_mac_config {
	stwuct be_cmd_weq_hdw hdw;
	u16 num_mac;
	u8 pwomiscuous;
	u8 intewface_id;
	stwuct macaddw mac[32];
} __packed;

static inwine void *embedded_paywoad(stwuct be_mcc_wwb *wwb)
{
	wetuwn wwb->paywoad.embedded_paywoad;
}

static inwine stwuct be_sge *nonembedded_sgw(stwuct be_mcc_wwb *wwb)
{
	wetuwn &wwb->paywoad.sgw[0];
}

/******************** Modify EQ Deway *******************/
stwuct be_cmd_weq_modify_eq_deway {
	stwuct be_cmd_weq_hdw hdw;
	__we32 num_eq;
	stwuct {
		__we32 eq_id;
		__we32 phase;
		__we32 deway_muwtipwiew;
	} deway[MAX_CPUS];
} __packed;

/******************** Get MAC ADDW *******************/

stwuct be_cmd_get_nic_conf_wesp {
	stwuct be_cmd_wesp_hdw hdw;
	u32 nic_powt_count;
	u32 speed;
	u32 max_speed;
	u32 wink_state;
	u32 max_fwame_size;
	u16 size_of_stwuctuwe;
	u8 mac_addwess[ETH_AWEN];
} __packed;

/******************** Get HBA NAME *******************/

stwuct be_cmd_hba_name {
	stwuct be_cmd_weq_hdw hdw;
	u16 fwags;
	u16 wsvd0;
	u8 initiatow_name[ISCSI_NAME_WEN];
#define BE_INI_AWIAS_WEN 32
	u8 initiatow_awias[BE_INI_AWIAS_WEN];
} __packed;

/******************** COMMON SET HOST DATA *******************/
#define BE_CMD_SET_HOST_PAWAM_ID	0x2
#define BE_CMD_MAX_DWV_VEWSION		0x30
stwuct be_sethost_weq {
	u32 pawam_id;
	u32 pawam_wen;
	u32 pawam_data[32];
};

stwuct be_sethost_wesp {
	u32 wsvd0;
};

stwuct be_cmd_set_host_data {
	union {
		stwuct be_cmd_weq_hdw weq_hdw;
		stwuct be_cmd_wesp_hdw wesp_hdw;
	} h;
	union {
		stwuct be_sethost_weq weq;
		stwuct be_sethost_wesp wesp;
	} pawam;
} __packed;

/******************** COMMON SET Featuwes *******************/
#define BE_CMD_SET_FEATUWE_UEW	0x10
#define BE_CMD_UEW_SUPP_BIT	0x1
stwuct be_uew_weq {
	u32 uew;
	u32 wsvd;
};

stwuct be_uew_wesp {
	u32 uew;
	u16 ue2wp;
	u16 ue2sw;
};

stwuct be_cmd_set_featuwes {
	union {
		stwuct be_cmd_weq_hdw weq_hdw;
		stwuct be_cmd_wesp_hdw wesp_hdw;
	} h;
	u32 featuwe;
	u32 pawam_wen;
	union {
		stwuct be_uew_weq weq;
		stwuct be_uew_wesp wesp;
		u32 wsvd[2];
	} pawam;
} __packed;

int beiscsi_cmd_function_weset(stwuct beiscsi_hba *phba);

int beiscsi_cmd_speciaw_wwb(stwuct be_ctww_info *ctww, u32 woad);

int beiscsi_check_fw_wdy(stwuct beiscsi_hba *phba);

int beiscsi_init_swipowt(stwuct beiscsi_hba *phba);

int beiscsi_cmd_iscsi_cweanup(stwuct beiscsi_hba *phba, unsigned showt uwp_num);

int beiscsi_detect_ue(stwuct beiscsi_hba *phba);

int beiscsi_detect_tpe(stwuct beiscsi_hba *phba);

int beiscsi_cmd_eq_cweate(stwuct be_ctww_info *ctww,
			  stwuct be_queue_info *eq, int eq_deway);

int beiscsi_cmd_cq_cweate(stwuct be_ctww_info *ctww,
			  stwuct be_queue_info *cq, stwuct be_queue_info *eq,
			  boow sow_evts, boow no_deway,
			  int num_cqe_dma_coawesce);

int beiscsi_cmd_q_destwoy(stwuct be_ctww_info *ctww, stwuct be_queue_info *q,
			  int type);
int beiscsi_cmd_mccq_cweate(stwuct beiscsi_hba *phba,
			stwuct be_queue_info *mccq,
			stwuct be_queue_info *cq);

void fwee_mcc_wwb(stwuct be_ctww_info *ctww, unsigned int tag);

int beiscsi_modify_eq_deway(stwuct beiscsi_hba *phba, stwuct be_set_eqd *,
			    int num);
int beiscsi_mccq_compw_wait(stwuct beiscsi_hba *phba,
			    unsigned int tag,
			    stwuct be_mcc_wwb **wwb,
			    stwuct be_dma_mem *mbx_cmd_mem);
int __beiscsi_mcc_compw_status(stwuct beiscsi_hba *phba,
			       unsigned int tag,
			       stwuct be_mcc_wwb **wwb,
			       stwuct be_dma_mem *mbx_cmd_mem);
stwuct be_mcc_wwb *wwb_fwom_mbox(stwuct be_dma_mem *mbox_mem);
void be_mcc_notify(stwuct beiscsi_hba *phba, unsigned int tag);
stwuct be_mcc_wwb *awwoc_mcc_wwb(stwuct beiscsi_hba *phba,
				 unsigned int *wef_tag);
void beiscsi_pwocess_async_event(stwuct beiscsi_hba *phba,
				stwuct be_mcc_compw *compw);
int beiscsi_pwocess_mcc_compw(stwuct be_ctww_info *ctww,
			      stwuct be_mcc_compw *compw);

int be_cmd_cweate_defauwt_pdu_queue(stwuct be_ctww_info *ctww,
				    stwuct be_queue_info *cq,
				    stwuct be_queue_info *dq, int wength,
				    int entwy_size, uint8_t is_headew,
				    uint8_t uwp_num);

int be_cmd_iscsi_post_tempwate_hdw(stwuct be_ctww_info *ctww,
				    stwuct be_dma_mem *q_mem);

int be_cmd_iscsi_wemove_tempwate_hdw(stwuct be_ctww_info *ctww);

int be_cmd_iscsi_post_sgw_pages(stwuct be_ctww_info *ctww,
				stwuct be_dma_mem *q_mem, u32 page_offset,
				u32 num_pages);

int be_cmd_wwbq_cweate(stwuct be_ctww_info *ctww, stwuct be_dma_mem *q_mem,
		       stwuct be_queue_info *wwbq,
		       stwuct hwi_wwb_context *pwwb_context,
		       uint8_t uwp_num);

/* Configuwation Functions */
int be_cmd_set_vwan(stwuct beiscsi_hba *phba, uint16_t vwan_tag);

int beiscsi_check_suppowted_fw(stwuct be_ctww_info *ctww,
			       stwuct beiscsi_hba *phba);

int beiscsi_get_fw_config(stwuct be_ctww_info *ctww, stwuct beiscsi_hba *phba);

int beiscsi_get_powt_name(stwuct be_ctww_info *ctww, stwuct beiscsi_hba *phba);

int beiscsi_set_uew_featuwe(stwuct beiscsi_hba *phba);
int beiscsi_set_host_data(stwuct beiscsi_hba *phba);

stwuct be_defauwt_pdu_context {
	u32 dw[4];
} __packed;

stwuct amap_be_defauwt_pdu_context {
	u8 dbuf_cindex[13];	/* dwowd 0 */
	u8 wsvd0[3];		/* dwowd 0 */
	u8 wing_size[4];	/* dwowd 0 */
	u8 wing_state[4];	/* dwowd 0 */
	u8 wsvd1[8];		/* dwowd 0 */
	u8 dbuf_pindex[13];	/* dwowd 1 */
	u8 wsvd2;		/* dwowd 1 */
	u8 pci_func_id[8];	/* dwowd 1 */
	u8 wx_pdid[9];		/* dwowd 1 */
	u8 wx_pdid_vawid;	/* dwowd 1 */
	u8 defauwt_buffew_size[16];	/* dwowd 2 */
	u8 cq_id_wecv[10];	/* dwowd 2 */
	u8 wx_pdid_not_vawid;	/* dwowd 2 */
	u8 wsvd3[5];		/* dwowd 2 */
	u8 wsvd4[32];		/* dwowd 3 */
} __packed;

stwuct amap_defauwt_pdu_context_ext {
	u8 wsvd0[16];   /* dwowd 0 */
	u8 wing_size[4];    /* dwowd 0 */
	u8 wsvd1[12];   /* dwowd 0 */
	u8 wsvd2[22];   /* dwowd 1 */
	u8 wx_pdid[9];  /* dwowd 1 */
	u8 wx_pdid_vawid;   /* dwowd 1 */
	u8 defauwt_buffew_size[16]; /* dwowd 2 */
	u8 cq_id_wecv[16];  /* dwowd 2 */
	u8 wsvd3[32];   /* dwowd 3 */
} __packed;

stwuct be_defq_cweate_weq {
	stwuct be_cmd_weq_hdw hdw;
	u16 num_pages;
	u8 uwp_num;
#define BEISCSI_DUAW_UWP_AWAWE_BIT	0	/* Byte 3 - Bit 0 */
#define BEISCSI_BIND_Q_TO_UWP_BIT	1	/* Byte 3 - Bit 1 */
	u8 dua_featuwe;
	stwuct be_defauwt_pdu_context context;
	stwuct phys_addw pages[8];
} __packed;

stwuct be_defq_cweate_wesp {
	stwuct be_cmd_weq_hdw hdw;
	u16 id;
	u8 wsvd0;
	u8 uwp_num;
	u32 doowbeww_offset;
	u16 wegistew_set;
	u16 doowbeww_fowmat;
} __packed;

stwuct be_post_tempwate_pages_weq {
	stwuct be_cmd_weq_hdw hdw;
	u16 num_pages;
#define BEISCSI_TEMPWATE_HDW_TYPE_ISCSI	0x1
	u16 type;
	stwuct phys_addw scwatch_pa;
	stwuct viwt_addw scwatch_va;
	stwuct viwt_addw pages_va;
	stwuct phys_addw pages[16];
} __packed;

stwuct be_wemove_tempwate_pages_weq {
	stwuct be_cmd_weq_hdw hdw;
	u16 type;
	u16 wsvd0;
} __packed;

stwuct be_post_sgw_pages_weq {
	stwuct be_cmd_weq_hdw hdw;
	u16 num_pages;
	u16 page_offset;
	u32 wsvd0;
	stwuct phys_addw pages[26];
	u32 wsvd1;
} __packed;

stwuct be_wwbq_cweate_weq {
	stwuct be_cmd_weq_hdw hdw;
	u16 num_pages;
	u8 uwp_num;
	u8 dua_featuwe;
	stwuct phys_addw pages[8];
} __packed;

stwuct be_wwbq_cweate_wesp {
	stwuct be_cmd_wesp_hdw wesp_hdw;
	u16 cid;
	u8 wsvd0;
	u8 uwp_num;
	u32 doowbeww_offset;
	u16 wegistew_set;
	u16 doowbeww_fowmat;
} __packed;

#define SOW_CID_MASK		0x0000FFC0
#define SOW_CODE_MASK		0x0000003F
#define SOW_WWB_INDEX_MASK	0x00FF0000
#define SOW_CMD_WND_MASK	0xFF000000
#define SOW_WES_CNT_MASK	0x7FFFFFFF
#define SOW_EXP_CMD_SN_MASK	0xFFFFFFFF
#define SOW_HW_STS_MASK		0x000000FF
#define SOW_STS_MASK		0x0000FF00
#define SOW_WESP_MASK		0x00FF0000
#define SOW_FWAGS_MASK		0x7F000000
#define SOW_S_MASK		0x80000000

stwuct sow_cqe {
	u32 dw[4];
};

stwuct amap_sow_cqe {
	u8 hw_sts[8];		/* dwowd 0 */
	u8 i_sts[8];		/* dwowd 0 */
	u8 i_wesp[8];		/* dwowd 0 */
	u8 i_fwags[7];		/* dwowd 0 */
	u8 s;			/* dwowd 0 */
	u8 i_exp_cmd_sn[32];	/* dwowd 1 */
	u8 code[6];		/* dwowd 2 */
	u8 cid[10];		/* dwowd 2 */
	u8 wwb_index[8];	/* dwowd 2 */
	u8 i_cmd_wnd[8];	/* dwowd 2 */
	u8 i_wes_cnt[31];	/* dwowd 3 */
	u8 vawid;		/* dwowd 3 */
} __packed;

#define SOW_ICD_INDEX_MASK	0x0003FFC0
stwuct amap_sow_cqe_wing {
	u8 hw_sts[8];		/* dwowd 0 */
	u8 i_sts[8];		/* dwowd 0 */
	u8 i_wesp[8];		/* dwowd 0 */
	u8 i_fwags[7];		/* dwowd 0 */
	u8 s;			/* dwowd 0 */
	u8 i_exp_cmd_sn[32];	/* dwowd 1 */
	u8 code[6];		/* dwowd 2 */
	u8 icd_index[12];	/* dwowd 2 */
	u8 wsvd[6];		/* dwowd 2 */
	u8 i_cmd_wnd[8];	/* dwowd 2 */
	u8 i_wes_cnt[31];	/* dwowd 3 */
	u8 vawid;		/* dwowd 3 */
} __packed;

stwuct amap_sow_cqe_v2 {
	u8 hw_sts[8];   /* dwowd 0 */
	u8 i_sts[8];    /* dwowd 0 */
	u8 wwb_index[16];   /* dwowd 0 */
	u8 i_exp_cmd_sn[32];    /* dwowd 1 */
	u8 code[6]; /* dwowd 2 */
	u8 cmd_cmpw;    /* dwowd 2 */
	u8 wsvd0;   /* dwowd 2 */
	u8 i_cmd_wnd[8];    /* dwowd 2 */
	u8 cid[13]; /* dwowd 2 */
	u8 u;   /* dwowd 2 */
	u8 o;   /* dwowd 2 */
	u8 s;   /* dwowd 2 */
	u8 i_wes_cnt[31];   /* dwowd 3 */
	u8 vawid;   /* dwowd 3 */
} __packed;

stwuct common_sow_cqe {
	u32 exp_cmdsn;
	u32 wes_cnt;
	u16 wwb_index;
	u16 cid;
	u8 hw_sts;
	u8 cmd_wnd;
	u8 wes_fwag; /* the s feiwd of stwuctuwe */
	u8 i_wesp; /* fow skh if cmd_compwete is set then i_sts is wesponse */
	u8 i_fwags; /* fow skh ow the u and o feiwds */
	u8 i_sts; /* fow skh if cmd_compwete is not-set then i_sts is status */
};

/*** iSCSI ack/dwivew message compwetions ***/
stwuct amap_it_dmsg_cqe {
	u8 ack_num[32]; /* DWOWD 0 */
	u8 pdu_bytes_wcvd[32];  /* DWOWD 1 */
	u8 code[6]; /* DWOWD 2 */
	u8 cid[10]; /* DWOWD 2 */
	u8 wwb_idx[8];  /* DWOWD 2 */
	u8 wsvd0[8];    /* DWOWD 2*/
	u8 wsvd1[31];   /* DWOWD 3*/
	u8 vawid;   /* DWOWD 3 */
} __packed;

stwuct amap_it_dmsg_cqe_v2 {
	u8 ack_num[32]; /* DWOWD 0 */
	u8 pdu_bytes_wcvd[32];  /* DWOWD 1 */
	u8 code[6]; /* DWOWD 2 */
	u8 wsvd0[10];   /* DWOWD 2 */
	u8 wwb_idx[16]; /* DWOWD 2 */
	u8 wsvd1[16];   /* DWOWD 3 */
	u8 cid[13]; /* DWOWD 3 */
	u8 wsvd2[2];    /* DWOWD 3 */
	u8 vawid;   /* DWOWD 3 */
} __packed;


/**
 * Post WWB Queue Doowbeww Wegistew used by the host Stowage
 * stack to notify the
 * contwowwew of a posted Wowk Wequest Bwock
 */
#define DB_WWB_POST_CID_MASK		0xFFFF	/* bits 0 - 16 */
#define DB_DEF_PDU_WWB_INDEX_MASK	0xFF	/* bits 0 - 9 */

#define DB_DEF_PDU_WWB_INDEX_SHIFT	16
#define DB_DEF_PDU_NUM_POSTED_SHIFT	24

stwuct fwagnum_bits_fow_sgw_cwa_in {
	stwuct be_cmd_weq_hdw hdw;
	u32 num_bits;
} __packed;

stwuct iscsi_cweanup_weq {
	stwuct be_cmd_weq_hdw hdw;
	u16 chute;
	u8 hdw_wing_id;
	u8 data_wing_id;
} __packed;

stwuct iscsi_cweanup_weq_v1 {
	stwuct be_cmd_weq_hdw hdw;
	u16 chute;
	u16 wsvd1;
	u16 hdw_wing_id;
	u16 wsvd2;
	u16 data_wing_id;
	u16 wsvd3;
} __packed;

stwuct eq_deway {
	u32 eq_id;
	u32 phase;
	u32 deway_muwtipwiew;
} __packed;

stwuct be_eq_deway_pawams_in {
	stwuct be_cmd_weq_hdw hdw;
	u32 num_eq;
	stwuct eq_deway deway[8];
} __packed;

stwuct tcp_connect_and_offwoad_in {
	stwuct be_cmd_weq_hdw hdw;
	stwuct ip_addw_fowmat ip_addwess;
	u16 tcp_powt;
	u16 cid;
	u16 cq_id;
	u16 defq_id;
	stwuct phys_addw dataout_tempwate_pa;
	u16 hdw_wing_id;
	u16 data_wing_id;
	u8 do_offwoad;
	u8 wsvd0[3];
} __packed;

stwuct tcp_connect_and_offwoad_in_v1 {
	stwuct be_cmd_weq_hdw hdw;
	stwuct ip_addw_fowmat ip_addwess;
	u16 tcp_powt;
	u16 cid;
	u16 cq_id;
	u16 defq_id;
	stwuct phys_addw dataout_tempwate_pa;
	u16 hdw_wing_id;
	u16 data_wing_id;
	u8 do_offwoad;
	u8 ifd_state;
	u8 wsvd0[2];
	u16 tcp_window_size;
	u8 tcp_window_scawe_count;
	u8 wsvd1;
	u32 tcp_mss:24;
	u8 wsvd2;
} __packed;

stwuct tcp_connect_and_offwoad_out {
	stwuct be_cmd_wesp_hdw hdw;
	u32 connection_handwe;
	u16 cid;
	u16 wsvd0;

} __packed;

#define DB_DEF_PDU_WING_ID_MASK	0x3FFF	/* bits 0 - 13 */
#define DB_DEF_PDU_CQPWOC_MASK		0x3FFF	/* bits 16 - 29 */
#define DB_DEF_PDU_WEAWM_SHIFT		14
#define DB_DEF_PDU_EVENT_SHIFT		15
#define DB_DEF_PDU_CQPWOC_SHIFT		16

stwuct be_invawidate_connection_pawams_in {
	stwuct be_cmd_weq_hdw hdw;
	u32 session_handwe;
	u16 cid;
	u16 unused;
#define BE_CWEANUP_TYPE_INVAWIDATE	0x8001
#define BE_CWEANUP_TYPE_ISSUE_TCP_WST	0x8002
	u16 cweanup_type;
	u16 save_cfg;
} __packed;

stwuct be_invawidate_connection_pawams_out {
	u32 session_handwe;
	u16 cid;
	u16 unused;
} __packed;

union be_invawidate_connection_pawams {
	stwuct be_invawidate_connection_pawams_in weq;
	stwuct be_invawidate_connection_pawams_out wesp;
} __packed;

stwuct be_tcp_upwoad_pawams_in {
	stwuct be_cmd_weq_hdw hdw;
	u16 id;
#define BE_UPWOAD_TYPE_GWACEFUW		1
/* abowtive upwoad with weset */
#define BE_UPWOAD_TYPE_ABOWT_WESET	2
/* abowtive upwoad without weset */
#define BE_UPWOAD_TYPE_ABOWT		3
/* abowtive upwoad with weset, sequence numbew by dwivew */
#define BE_UPWOAD_TYPE_ABOWT_WITH_SEQ	4
	u16 upwoad_type;
	u32 weset_seq;
} __packed;

stwuct be_tcp_upwoad_pawams_out {
	u32 dw[32];
} __packed;

union be_tcp_upwoad_pawams {
	stwuct be_tcp_upwoad_pawams_in wequest;
	stwuct be_tcp_upwoad_pawams_out wesponse;
} __packed;

stwuct be_uwp_fw_cfg {
#define BEISCSI_UWP_ISCSI_INI_MODE	0x10
	u32 uwp_mode;
	u32 etx_base;
	u32 etx_count;
	u32 sq_base;
	u32 sq_count;
	u32 wq_base;
	u32 wq_count;
	u32 dq_base;
	u32 dq_count;
	u32 wwo_base;
	u32 wwo_count;
	u32 icd_base;
	u32 icd_count;
};

stwuct be_uwp_chain_icd {
	u32 chain_base;
	u32 chain_count;
};

stwuct be_fw_cfg {
	stwuct be_cmd_weq_hdw hdw;
	u32 be_config_numbew;
	u32 asic_wevision;
	u32 phys_powt;
#define BEISCSI_FUNC_ISCSI_INI_MODE	0x10
#define BEISCSI_FUNC_DUA_MODE	0x800
	u32 function_mode;
	stwuct be_uwp_fw_cfg uwp[2];
	u32 function_caps;
	u32 cqid_base;
	u32 cqid_count;
	u32 eqid_base;
	u32 eqid_count;
	stwuct be_uwp_chain_icd chain_icd[2];
} __packed;

stwuct be_cmd_get_aww_if_id_weq {
	stwuct be_cmd_weq_hdw hdw;
	u32 if_count;
	u32 if_hndw_wist[1];
} __packed;

stwuct be_cmd_get_powt_name {
	union {
		stwuct be_cmd_weq_hdw weq_hdw;
		stwuct be_cmd_wesp_hdw wesp_hdw;
	} h;
	union {
		stwuct {
			u32 wesewved;
		} weq;
		stwuct {
			u32 powt_names;
		} wesp;
	} p;
} __packed;

#define ISCSI_OPCODE_SCSI_DATA_OUT		5
#define OPCODE_COMMON_NTWK_WINK_STATUS_QUEWY 5
#define OPCODE_COMMON_MODIFY_EQ_DEWAY		41
#define OPCODE_COMMON_ISCSI_CWEANUP		59
#define	OPCODE_COMMON_TCP_UPWOAD		56
#define OPCODE_COMMON_ISCSI_TCP_CONNECT_AND_OFFWOAD 70
#define OPCODE_COMMON_ISCSI_EWWOW_WECOVEWY_INVAWIDATE_COMMANDS 1
#define OPCODE_ISCSI_INI_CFG_GET_HBA_NAME	6
#define OPCODE_ISCSI_INI_CFG_SET_HBA_NAME	7
#define OPCODE_ISCSI_INI_SESSION_GET_A_SESSION  14
#define OPCODE_ISCSI_INI_SESSION_WOGOUT_TAWGET	 24
#define OPCODE_ISCSI_INI_DWIVEW_WEOPEN_AWW_SESSIONS 36
#define OPCODE_ISCSI_INI_DWIVEW_OFFWOAD_SESSION 41
#define OPCODE_ISCSI_INI_DWIVEW_INVAWIDATE_CONNECTION 42
#define OPCODE_ISCSI_INI_BOOT_GET_BOOT_TAWGET	52
#define OPCODE_COMMON_WWITE_FWASH		96
#define OPCODE_COMMON_WEAD_FWASH		97

#define CMD_ISCSI_COMMAND_INVAWIDATE		1

#define INI_WW_CMD			1	/* Initiatow wwite command */
#define INI_TMF_CMD			2	/* Initiatow TMF command */
#define INI_NOPOUT_CMD			3	/* Initiatow; Send a NOP-OUT */
#define INI_WD_CMD			5	/* Initiatow wequesting to send
						 * a wead command
						 */
#define TGT_CTX_UPDT_CMD		7	/* Tawget context update */
#define TGT_DM_CMD			11	/* Indicates that the bhs
						 * pwepawed by dwivew shouwd not
						 * be touched.
						 */

/* Wetuwns the numbew of items in the fiewd awway. */
#define BE_NUMBEW_OF_FIEWD(_type_, _fiewd_)	\
	(sizeof_fiewd(_type_, _fiewd_)/sizeof((((_type_ *)0)->_fiewd_[0])))\

/**
 * Diffewent types of iSCSI compwetions to host dwivew fow both initiatow
 * and taget mode
 * of opewation.
 */
#define SOW_CMD_COMPWETE		1	/* Sowicited command compweted
						 * nowmawwy
						 */
#define SOW_CMD_KIWWED_DATA_DIGEST_EWW  2	/* Sowicited command got
						 * invawidated intewnawwy due
						 * to Data Digest ewwow
						 */
#define CXN_KIWWED_PDU_SIZE_EXCEEDS_DSW 3	/* Connection got invawidated
						 * intewnawwy
						 * due to a weceived PDU
						 * size > DSW
						 */
#define CXN_KIWWED_BUWST_WEN_MISMATCH   4	/* Connection got invawidated
						 * intewnawwy due ti weceived
						 * PDU sequence size >
						 * FBW/MBW.
						 */
#define CXN_KIWWED_AHS_WCVD		5	/* Connection got invawidated
						 * intewnawwy due to a weceived
						 * PDU Hdw that has
						 * AHS */
#define CXN_KIWWED_HDW_DIGEST_EWW	6	/* Connection got invawidated
						 * intewnawwy due to Hdw Digest
						 * ewwow
						 */
#define CXN_KIWWED_UNKNOWN_HDW		7	/* Connection got invawidated
						 *  intewnawwy
						 * due to a bad opcode in the
						 * pdu hdw
						 */
#define CXN_KIWWED_STAWE_ITT_TTT_WCVD	8	/* Connection got invawidated
						 * intewnawwy due to a weceived
						 * ITT/TTT that does not bewong
						 * to this Connection
						 */
#define CXN_KIWWED_INVAWID_ITT_TTT_WCVD 9	/* Connection got invawidated
						 * intewnawwy due to weceived
						 * ITT/TTT vawue > Max
						 * Suppowted ITTs/TTTs
						 */
#define CXN_KIWWED_WST_WCVD		10	/* Connection got invawidated
						 * intewnawwy due to an
						 * incoming TCP WST
						 */
#define CXN_KIWWED_TIMED_OUT		11	/* Connection got invawidated
						 * intewnawwy due to timeout on
						 * tcp segment 12 wetwansmit
						 * attempts faiwed
						 */
#define CXN_KIWWED_WST_SENT		12	/* Connection got invawidated
						 * intewnawwy due to TCP WST
						 * sent by the Tx side
						 */
#define CXN_KIWWED_FIN_WCVD		13	/* Connection got invawidated
						 * intewnawwy due to an
						 * incoming TCP FIN.
						 */
#define CXN_KIWWED_BAD_UNSOW_PDU_WCVD	14	/* Connection got invawidated
						 * intewnawwy due to bad
						 * unsowicited PDU Unsowicited
						 * PDUs awe PDUs with
						 * ITT=0xffffffff
						 */
#define CXN_KIWWED_BAD_WWB_INDEX_EWWOW	15	/* Connection got invawidated
						 * intewnawwy due to bad WWB
						 * index.
						 */
#define CXN_KIWWED_OVEW_WUN_WESIDUAW	16	/* Command got invawidated
						 * intewnawwy due to weceived
						 * command has wesiduaw
						 * ovew wun bytes.
						 */
#define CXN_KIWWED_UNDEW_WUN_WESIDUAW	17	/* Command got invawidated
						 * intewnawwy due to weceived
						 * command has wesiduaw undew
						 * wun bytes.
						 */
#define CMD_KIWWED_INVAWID_STATSN_WCVD	18	/* Command got invawidated
						 * intewnawwy due to a weceived
						 * PDU has an invawid StatusSN
						 */
#define CMD_KIWWED_INVAWID_W2T_WCVD	19	/* Command got invawidated
						 * intewnawwy due to a weceived
						 * an W2T with some invawid
						 * fiewds in it
						 */
#define CMD_CXN_KIWWED_WUN_INVAWID	20	/* Command got invawidated
						 * intewnawwy due to weceived
						 * PDU has an invawid WUN.
						 */
#define CMD_CXN_KIWWED_ICD_INVAWID	21	/* Command got invawidated
						 * intewnawwy due to the
						 * cowwesponding ICD not in a
						 * vawid state
						 */
#define CMD_CXN_KIWWED_ITT_INVAWID	22	/* Command got invawidated due
						 *  to weceived PDU has an
						 *  invawid ITT.
						 */
#define CMD_CXN_KIWWED_SEQ_OUTOFOWDEW	23	/* Command got invawidated due
						 * to weceived sequence buffew
						 * offset is out of owdew.
						 */
#define CMD_CXN_KIWWED_INVAWID_DATASN_WCVD 24	/* Command got invawidated
						 * intewnawwy due to a
						 * weceived PDU has an invawid
						 * DataSN
						 */
#define CXN_INVAWIDATE_NOTIFY		25	/* Connection invawidation
						 * compwetion notify.
						 */
#define CXN_INVAWIDATE_INDEX_NOTIFY	26	/* Connection invawidation
						 * compwetion
						 * with data PDU index.
						 */
#define CMD_INVAWIDATED_NOTIFY		27	/* Command invawidation
						 * compwetionnotifify.
						 */
#define UNSOW_HDW_NOTIFY		28	/* Unsowicited headew notify.*/
#define UNSOW_DATA_NOTIFY		29	/* Unsowicited data notify.*/
#define UNSOW_DATA_DIGEST_EWWOW_NOTIFY	30	/* Unsowicited data digest
						 * ewwow notify.
						 */
#define DWIVEWMSG_NOTIFY		31	/* TCP acknowwedge based
						 * notification.
						 */
#define CXN_KIWWED_CMND_DATA_NOT_ON_SAME_CONN 32 /* Connection got invawidated
						  * intewnawwy due to command
						  * and data awe not on same
						  * connection.
						  */
#define SOW_CMD_KIWWED_DIF_EWW		33	/* Sowicited command got
						 *  invawidated intewnawwy due
						 *  to DIF ewwow
						 */
#define CXN_KIWWED_SYN_WCVD		34	/* Connection got invawidated
						 * intewnawwy due to incoming
						 * TCP SYN
						 */
#define CXN_KIWWED_IMM_DATA_WCVD	35	/* Connection got invawidated
						 * intewnawwy due to an
						 * incoming Unsowicited PDU
						 * that has immediate data on
						 * the cxn
						 */

void be_wwb_hdw_pwepawe(stwuct be_mcc_wwb *wwb, u32 paywoad_wen,
			boow embedded, u8 sge_cnt);

void be_cmd_hdw_pwepawe(stwuct be_cmd_weq_hdw *weq_hdw,
			u8 subsystem, u8 opcode, u32 cmd_wen);
#endif /* !BEISCSI_CMDS_H */
