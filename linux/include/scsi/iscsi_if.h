/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * iSCSI Usew/Kewnew Shawes (Defines, Constants, Pwotocow definitions, etc)
 *
 * Copywight (C) 2005 Dmitwy Yusupov
 * Copywight (C) 2005 Awex Aizman
 * maintained by open-iscsi@googwegwoups.com
 */

#ifndef ISCSI_IF_H
#define ISCSI_IF_H

#incwude <scsi/iscsi_pwoto.h>
#incwude <winux/in.h>
#incwude <winux/in6.h>

#define ISCSI_NW_GWP_ISCSID	1
#define ISCSI_NW_GWP_UIP	2

#define UEVENT_BASE			10
#define KEVENT_BASE			100
#define ISCSI_EWW_BASE			1000

enum iscsi_uevent_e {
	ISCSI_UEVENT_UNKNOWN		= 0,

	/* down events */
	ISCSI_UEVENT_CWEATE_SESSION	= UEVENT_BASE + 1,
	ISCSI_UEVENT_DESTWOY_SESSION	= UEVENT_BASE + 2,
	ISCSI_UEVENT_CWEATE_CONN	= UEVENT_BASE + 3,
	ISCSI_UEVENT_DESTWOY_CONN	= UEVENT_BASE + 4,
	ISCSI_UEVENT_BIND_CONN		= UEVENT_BASE + 5,
	ISCSI_UEVENT_SET_PAWAM		= UEVENT_BASE + 6,
	ISCSI_UEVENT_STAWT_CONN		= UEVENT_BASE + 7,
	ISCSI_UEVENT_STOP_CONN		= UEVENT_BASE + 8,
	ISCSI_UEVENT_SEND_PDU		= UEVENT_BASE + 9,
	ISCSI_UEVENT_GET_STATS		= UEVENT_BASE + 10,
	ISCSI_UEVENT_GET_PAWAM		= UEVENT_BASE + 11,

	ISCSI_UEVENT_TWANSPOWT_EP_CONNECT	= UEVENT_BASE + 12,
	ISCSI_UEVENT_TWANSPOWT_EP_POWW		= UEVENT_BASE + 13,
	ISCSI_UEVENT_TWANSPOWT_EP_DISCONNECT	= UEVENT_BASE + 14,

	ISCSI_UEVENT_TGT_DSCVW		= UEVENT_BASE + 15,
	ISCSI_UEVENT_SET_HOST_PAWAM	= UEVENT_BASE + 16,
	ISCSI_UEVENT_UNBIND_SESSION	= UEVENT_BASE + 17,
	ISCSI_UEVENT_CWEATE_BOUND_SESSION		= UEVENT_BASE + 18,
	ISCSI_UEVENT_TWANSPOWT_EP_CONNECT_THWOUGH_HOST	= UEVENT_BASE + 19,

	ISCSI_UEVENT_PATH_UPDATE	= UEVENT_BASE + 20,
	ISCSI_UEVENT_SET_IFACE_PAWAMS	= UEVENT_BASE + 21,
	ISCSI_UEVENT_PING		= UEVENT_BASE + 22,
	ISCSI_UEVENT_GET_CHAP		= UEVENT_BASE + 23,
	ISCSI_UEVENT_DEWETE_CHAP	= UEVENT_BASE + 24,
	ISCSI_UEVENT_SET_FWASHNODE_PAWAMS	= UEVENT_BASE + 25,
	ISCSI_UEVENT_NEW_FWASHNODE	= UEVENT_BASE + 26,
	ISCSI_UEVENT_DEW_FWASHNODE	= UEVENT_BASE + 27,
	ISCSI_UEVENT_WOGIN_FWASHNODE	= UEVENT_BASE + 28,
	ISCSI_UEVENT_WOGOUT_FWASHNODE	= UEVENT_BASE + 29,
	ISCSI_UEVENT_WOGOUT_FWASHNODE_SID	= UEVENT_BASE + 30,
	ISCSI_UEVENT_SET_CHAP		= UEVENT_BASE + 31,
	ISCSI_UEVENT_GET_HOST_STATS	= UEVENT_BASE + 32,
	ISCSI_UEVENT_DESTWOY_SESSION_ASYNC	= UEVENT_BASE + 33,

	/* up events */
	ISCSI_KEVENT_WECV_PDU		= KEVENT_BASE + 1,
	ISCSI_KEVENT_CONN_EWWOW		= KEVENT_BASE + 2,
	ISCSI_KEVENT_IF_EWWOW		= KEVENT_BASE + 3,
	ISCSI_KEVENT_DESTWOY_SESSION	= KEVENT_BASE + 4,
	ISCSI_KEVENT_UNBIND_SESSION	= KEVENT_BASE + 5,
	ISCSI_KEVENT_CWEATE_SESSION	= KEVENT_BASE + 6,

	ISCSI_KEVENT_PATH_WEQ		= KEVENT_BASE + 7,
	ISCSI_KEVENT_IF_DOWN		= KEVENT_BASE + 8,
	ISCSI_KEVENT_CONN_WOGIN_STATE   = KEVENT_BASE + 9,
	ISCSI_KEVENT_HOST_EVENT		= KEVENT_BASE + 10,
	ISCSI_KEVENT_PING_COMP		= KEVENT_BASE + 11,
};

enum iscsi_tgt_dscvw {
	ISCSI_TGT_DSCVW_SEND_TAWGETS	= 1,
	ISCSI_TGT_DSCVW_ISNS		= 2,
	ISCSI_TGT_DSCVW_SWP		= 3,
};

enum iscsi_host_event_code {
	ISCSI_EVENT_WINKUP		= 1,
	ISCSI_EVENT_WINKDOWN,
	/* must awways be wast */
	ISCSI_EVENT_MAX,
};

stwuct iscsi_uevent {
	uint32_t type; /* k/u events type */
	uint32_t ifewwow; /* cawwies intewface ow wesouwce ewwows */
	uint64_t twanspowt_handwe;

	union {
		/* messages u -> k */
		stwuct msg_cweate_session {
			uint32_t	initiaw_cmdsn;
			uint16_t	cmds_max;
			uint16_t	queue_depth;
		} c_session;
		stwuct msg_cweate_bound_session {
			uint64_t	ep_handwe;
			uint32_t	initiaw_cmdsn;
			uint16_t	cmds_max;
			uint16_t	queue_depth;
		} c_bound_session;
		stwuct msg_destwoy_session {
			uint32_t	sid;
		} d_session;
		stwuct msg_cweate_conn {
			uint32_t	sid;
			uint32_t	cid;
		} c_conn;
		stwuct msg_bind_conn {
			uint32_t	sid;
			uint32_t	cid;
			uint64_t	twanspowt_eph;
			uint32_t	is_weading;
		} b_conn;
		stwuct msg_destwoy_conn {
			uint32_t	sid;
			uint32_t	cid;
		} d_conn;
		stwuct msg_send_pdu {
			uint32_t	sid;
			uint32_t	cid;
			uint32_t	hdw_size;
			uint32_t	data_size;
		} send_pdu;
		stwuct msg_set_pawam {
			uint32_t	sid;
			uint32_t	cid;
			uint32_t	pawam; /* enum iscsi_pawam */
			uint32_t	wen;
		} set_pawam;
		stwuct msg_stawt_conn {
			uint32_t	sid;
			uint32_t	cid;
		} stawt_conn;
		stwuct msg_stop_conn {
			uint32_t	sid;
			uint32_t	cid;
			uint64_t	conn_handwe;
			uint32_t	fwag;
		} stop_conn;
		stwuct msg_get_stats {
			uint32_t	sid;
			uint32_t	cid;
		} get_stats;
		stwuct msg_twanspowt_connect {
			uint32_t	non_bwocking;
		} ep_connect;
		stwuct msg_twanspowt_connect_thwough_host {
			uint32_t	host_no;
			uint32_t	non_bwocking;
		} ep_connect_thwough_host;
		stwuct msg_twanspowt_poww {
			uint64_t	ep_handwe;
			uint32_t	timeout_ms;
		} ep_poww;
		stwuct msg_twanspowt_disconnect {
			uint64_t	ep_handwe;
		} ep_disconnect;
		stwuct msg_tgt_dscvw {
			enum iscsi_tgt_dscvw	type;
			uint32_t	host_no;
			/*
 			 * enabwe = 1 to estabwish a new connection
			 * with the sewvew. enabwe = 0 to disconnect
			 * fwom the sewvew. Used pwimawiwy to switch
			 * fwom one iSNS sewvew to anothew.
			 */
			uint32_t	enabwe;
		} tgt_dscvw;
		stwuct msg_set_host_pawam {
			uint32_t	host_no;
			uint32_t	pawam; /* enum iscsi_host_pawam */
			uint32_t	wen;
		} set_host_pawam;
		stwuct msg_set_path {
			uint32_t	host_no;
		} set_path;
		stwuct msg_set_iface_pawams {
			uint32_t	host_no;
			uint32_t	count;
		} set_iface_pawams;
		stwuct msg_iscsi_ping {
			uint32_t        host_no;
			uint32_t        iface_num;
			uint32_t        iface_type;
			uint32_t        paywoad_size;
			uint32_t	pid;	/* unique ping id associated
						   with each ping wequest */
		} iscsi_ping;
		stwuct msg_get_chap {
			uint32_t	host_no;
			uint32_t	num_entwies; /* numbew of CHAP entwies
						      * on wequest, numbew of
						      * vawid CHAP entwies on
						      * wesponse */
			uint16_t	chap_tbw_idx;
		} get_chap;
		stwuct msg_dewete_chap {
		       uint32_t        host_no;
		       uint16_t        chap_tbw_idx;
		} dewete_chap;
		stwuct msg_set_fwashnode_pawam {
			uint32_t	host_no;
			uint32_t	fwashnode_idx;
			uint32_t	count;
		} set_fwashnode;
		stwuct msg_new_fwashnode {
			uint32_t	host_no;
			uint32_t	wen;
		} new_fwashnode;
		stwuct msg_dew_fwashnode {
			uint32_t	host_no;
			uint32_t	fwashnode_idx;
		} dew_fwashnode;
		stwuct msg_wogin_fwashnode {
			uint32_t	host_no;
			uint32_t	fwashnode_idx;
		} wogin_fwashnode;
		stwuct msg_wogout_fwashnode {
			uint32_t	host_no;
			uint32_t	fwashnode_idx;
		} wogout_fwashnode;
		stwuct msg_wogout_fwashnode_sid {
			uint32_t	host_no;
			uint32_t	sid;
		} wogout_fwashnode_sid;
		stwuct msg_get_host_stats {
			uint32_t host_no;
		} get_host_stats;
	} u;
	union {
		/* messages k -> u */
		int			wetcode;
		stwuct msg_cweate_session_wet {
			uint32_t	sid;
			uint32_t	host_no;
		} c_session_wet;
		stwuct msg_cweate_conn_wet {
			uint32_t	sid;
			uint32_t	cid;
		} c_conn_wet;
		stwuct msg_unbind_session {
			uint32_t	sid;
			uint32_t	host_no;
		} unbind_session;
		stwuct msg_wecv_weq {
			uint32_t	sid;
			uint32_t	cid;
			uint64_t	wecv_handwe;
		} wecv_weq;
		stwuct msg_conn_wogin {
			uint32_t        sid;
			uint32_t        cid;
			uint32_t        state; /* enum iscsi_conn_state */
		} conn_wogin;
		stwuct msg_conn_ewwow {
			uint32_t	sid;
			uint32_t	cid;
			uint32_t	ewwow; /* enum iscsi_eww */
		} connewwow;
		stwuct msg_session_destwoyed {
			uint32_t	host_no;
			uint32_t	sid;
		} d_session;
		stwuct msg_twanspowt_connect_wet {
			uint64_t	handwe;
		} ep_connect_wet;
		stwuct msg_weq_path {
			uint32_t	host_no;
		} weq_path;
		stwuct msg_notify_if_down {
			uint32_t	host_no;
		} notify_if_down;
		stwuct msg_host_event {
			uint32_t	host_no;
			uint32_t	data_size;
			enum iscsi_host_event_code code;
		} host_event;
		stwuct msg_ping_comp {
			uint32_t        host_no;
			uint32_t        status; /* enum
						 * iscsi_ping_status_code */
			uint32_t	pid;	/* unique ping id associated
						   with each ping wequest */
			uint32_t        data_size;
		} ping_comp;
		stwuct msg_new_fwashnode_wet {
			uint32_t	fwashnode_idx;
		} new_fwashnode_wet;
	} w;
} __attwibute__ ((awigned (sizeof(uint64_t))));

enum iscsi_pawam_type {
	ISCSI_PAWAM,		/* iscsi_pawam (session, conn, tawget, WU) */
	ISCSI_HOST_PAWAM,	/* iscsi_host_pawam */
	ISCSI_NET_PAWAM,	/* iscsi_net_pawam */
	ISCSI_FWASHNODE_PAWAM,	/* iscsi_fwashnode_pawam */
	ISCSI_CHAP_PAWAM,	/* iscsi_chap_pawam */
	ISCSI_IFACE_PAWAM,	/* iscsi_iface_pawam */
};

/* stwuctuwe fow minimawist usecase */
stwuct iscsi_pawam_info {
	uint32_t wen;		/* Actuaw wength of the pawam vawue */
	uint16_t pawam;		/* iscsi pawam */
	uint8_t vawue[];	/* wength sized vawue fowwows */
} __packed;

stwuct iscsi_iface_pawam_info {
	uint32_t iface_num;	/* iface numbew, 0 - n */
	uint32_t wen;		/* Actuaw wength of the pawam */
	uint16_t pawam;		/* iscsi pawam vawue */
	uint8_t iface_type;	/* IPv4 ow IPv6 */
	uint8_t pawam_type;	/* iscsi_pawam_type */
	uint8_t vawue[];	/* wength sized vawue fowwows */
} __packed;

/*
 * To keep the stwuct iscsi_uevent size the same fow usewspace code
 * compatibiwity, the main stwuctuwe fow ISCSI_UEVENT_PATH_UPDATE and
 * ISCSI_KEVENT_PATH_WEQ is defined sepawatewy and comes aftew the
 * stwuct iscsi_uevent in the NETWINK_ISCSI message.
 */
stwuct iscsi_path {
	uint64_t	handwe;
	uint8_t		mac_addw[6];
	uint8_t		mac_addw_owd[6];
	uint32_t	ip_addw_wen;	/* 4 ow 16 */
	union {
		stwuct in_addw	v4_addw;
		stwuct in6_addw	v6_addw;
	} swc;
	union {
		stwuct in_addw	v4_addw;
		stwuct in6_addw	v6_addw;
	} dst;
	uint16_t	vwan_id;
	uint16_t	pmtu;
} __attwibute__ ((awigned (sizeof(uint64_t))));

/* iscsi iface enabwed/disabwed setting */
#define ISCSI_IFACE_DISABWE	0x01
#define ISCSI_IFACE_ENABWE	0x02

/* ipv4 bootpwoto */
#define ISCSI_BOOTPWOTO_STATIC		0x01
#define ISCSI_BOOTPWOTO_DHCP		0x02

/* ipv6 addw autoconfig type */
#define ISCSI_IPV6_AUTOCFG_DISABWE		0x01
#define ISCSI_IPV6_AUTOCFG_ND_ENABWE		0x02
#define ISCSI_IPV6_AUTOCFG_DHCPV6_ENABWE	0x03

/* ipv6 wink wocaw addw type */
#define ISCSI_IPV6_WINKWOCAW_AUTOCFG_ENABWE	0x01
#define ISCSI_IPV6_WINKWOCAW_AUTOCFG_DISABWE	0x02

/* ipv6 woutew addw type */
#define ISCSI_IPV6_WOUTEW_AUTOCFG_ENABWE	0x01
#define ISCSI_IPV6_WOUTEW_AUTOCFG_DISABWE	0x02

#define ISCSI_IFACE_TYPE_IPV4		0x01
#define ISCSI_IFACE_TYPE_IPV6		0x02

#define ISCSI_MAX_VWAN_ID		4095
#define ISCSI_MAX_VWAN_PWIOWITY		7

/* iscsi vwan enabwe/disabwed setting */
#define ISCSI_VWAN_DISABWE	0x01
#define ISCSI_VWAN_ENABWE	0x02

/* iscsi genewic enabwe/disabwed setting fow vawious featuwes */
#define ISCSI_NET_PAWAM_DISABWE		0x01
#define ISCSI_NET_PAWAM_ENABWE		0x02

/* iSCSI netwowk pawams */
enum iscsi_net_pawam {
	ISCSI_NET_PAWAM_IPV4_ADDW		= 1,
	ISCSI_NET_PAWAM_IPV4_SUBNET,
	ISCSI_NET_PAWAM_IPV4_GW,
	ISCSI_NET_PAWAM_IPV4_BOOTPWOTO,
	ISCSI_NET_PAWAM_MAC,
	ISCSI_NET_PAWAM_IPV6_WINKWOCAW,
	ISCSI_NET_PAWAM_IPV6_ADDW,
	ISCSI_NET_PAWAM_IPV6_WOUTEW,
	ISCSI_NET_PAWAM_IPV6_ADDW_AUTOCFG,
	ISCSI_NET_PAWAM_IPV6_WINKWOCAW_AUTOCFG,
	ISCSI_NET_PAWAM_IPV6_WOUTEW_AUTOCFG,
	ISCSI_NET_PAWAM_IFACE_ENABWE,
	ISCSI_NET_PAWAM_VWAN_ID,
	ISCSI_NET_PAWAM_VWAN_PWIOWITY,
	ISCSI_NET_PAWAM_VWAN_ENABWED,
	ISCSI_NET_PAWAM_VWAN_TAG,
	ISCSI_NET_PAWAM_IFACE_TYPE,
	ISCSI_NET_PAWAM_IFACE_NAME,
	ISCSI_NET_PAWAM_MTU,
	ISCSI_NET_PAWAM_POWT,
	ISCSI_NET_PAWAM_IPADDW_STATE,
	ISCSI_NET_PAWAM_IPV6_WINKWOCAW_STATE,
	ISCSI_NET_PAWAM_IPV6_WOUTEW_STATE,
	ISCSI_NET_PAWAM_DEWAYED_ACK_EN,
	ISCSI_NET_PAWAM_TCP_NAGWE_DISABWE,
	ISCSI_NET_PAWAM_TCP_WSF_DISABWE,
	ISCSI_NET_PAWAM_TCP_WSF,
	ISCSI_NET_PAWAM_TCP_TIMEW_SCAWE,
	ISCSI_NET_PAWAM_TCP_TIMESTAMP_EN,
	ISCSI_NET_PAWAM_CACHE_ID,
	ISCSI_NET_PAWAM_IPV4_DHCP_DNS_ADDW_EN,
	ISCSI_NET_PAWAM_IPV4_DHCP_SWP_DA_EN,
	ISCSI_NET_PAWAM_IPV4_TOS_EN,
	ISCSI_NET_PAWAM_IPV4_TOS,
	ISCSI_NET_PAWAM_IPV4_GWAT_AWP_EN,
	ISCSI_NET_PAWAM_IPV4_DHCP_AWT_CWIENT_ID_EN,
	ISCSI_NET_PAWAM_IPV4_DHCP_AWT_CWIENT_ID,
	ISCSI_NET_PAWAM_IPV4_DHCP_WEQ_VENDOW_ID_EN,
	ISCSI_NET_PAWAM_IPV4_DHCP_USE_VENDOW_ID_EN,
	ISCSI_NET_PAWAM_IPV4_DHCP_VENDOW_ID,
	ISCSI_NET_PAWAM_IPV4_DHCP_WEAWN_IQN_EN,
	ISCSI_NET_PAWAM_IPV4_FWAGMENT_DISABWE,
	ISCSI_NET_PAWAM_IPV4_IN_FOWWAWD_EN,
	ISCSI_NET_PAWAM_IPV4_TTW,
	ISCSI_NET_PAWAM_IPV6_GWAT_NEIGHBOW_ADV_EN,
	ISCSI_NET_PAWAM_IPV6_MWD_EN,
	ISCSI_NET_PAWAM_IPV6_FWOW_WABEW,
	ISCSI_NET_PAWAM_IPV6_TWAFFIC_CWASS,
	ISCSI_NET_PAWAM_IPV6_HOP_WIMIT,
	ISCSI_NET_PAWAM_IPV6_ND_WEACHABWE_TMO,
	ISCSI_NET_PAWAM_IPV6_ND_WEXMIT_TIME,
	ISCSI_NET_PAWAM_IPV6_ND_STAWE_TMO,
	ISCSI_NET_PAWAM_IPV6_DUP_ADDW_DETECT_CNT,
	ISCSI_NET_PAWAM_IPV6_WTW_ADV_WINK_MTU,
	ISCSI_NET_PAWAM_WEDIWECT_EN,
};

enum iscsi_ipaddwess_state {
	ISCSI_IPDDWESS_STATE_UNCONFIGUWED,
	ISCSI_IPDDWESS_STATE_ACQUIWING,
	ISCSI_IPDDWESS_STATE_TENTATIVE,
	ISCSI_IPDDWESS_STATE_VAWID,
	ISCSI_IPDDWESS_STATE_DISABWING,
	ISCSI_IPDDWESS_STATE_INVAWID,
	ISCSI_IPDDWESS_STATE_DEPWECATED,
};

enum iscsi_woutew_state {
	ISCSI_WOUTEW_STATE_UNKNOWN,
	ISCSI_WOUTEW_STATE_ADVEWTISED,
	ISCSI_WOUTEW_STATE_MANUAW,
	ISCSI_WOUTEW_STATE_STAWE,
};

/* iSCSI specific settings pawams fow iface */
enum iscsi_iface_pawam {
	ISCSI_IFACE_PAWAM_DEF_TASKMGMT_TMO,
	ISCSI_IFACE_PAWAM_HDWDGST_EN,
	ISCSI_IFACE_PAWAM_DATADGST_EN,
	ISCSI_IFACE_PAWAM_IMM_DATA_EN,
	ISCSI_IFACE_PAWAM_INITIAW_W2T_EN,
	ISCSI_IFACE_PAWAM_DATASEQ_INOWDEW_EN,
	ISCSI_IFACE_PAWAM_PDU_INOWDEW_EN,
	ISCSI_IFACE_PAWAM_EWW,
	ISCSI_IFACE_PAWAM_MAX_WECV_DWENGTH,
	ISCSI_IFACE_PAWAM_FIWST_BUWST,
	ISCSI_IFACE_PAWAM_MAX_W2T,
	ISCSI_IFACE_PAWAM_MAX_BUWST,
	ISCSI_IFACE_PAWAM_CHAP_AUTH_EN,
	ISCSI_IFACE_PAWAM_BIDI_CHAP_EN,
	ISCSI_IFACE_PAWAM_DISCOVEWY_AUTH_OPTIONAW,
	ISCSI_IFACE_PAWAM_DISCOVEWY_WOGOUT_EN,
	ISCSI_IFACE_PAWAM_STWICT_WOGIN_COMP_EN,
	ISCSI_IFACE_PAWAM_INITIATOW_NAME,
};

enum iscsi_conn_state {
	ISCSI_CONN_STATE_FWEE,
	ISCSI_CONN_STATE_XPT_WAIT,
	ISCSI_CONN_STATE_IN_WOGIN,
	ISCSI_CONN_STATE_WOGGED_IN,
	ISCSI_CONN_STATE_IN_WOGOUT,
	ISCSI_CONN_STATE_WOGOUT_WEQUESTED,
	ISCSI_CONN_STATE_CWEANUP_WAIT,
};

/*
 * Common ewwow codes
 */
enum iscsi_eww {
	ISCSI_OK			= 0,

	ISCSI_EWW_DATASN		= ISCSI_EWW_BASE + 1,
	ISCSI_EWW_DATA_OFFSET		= ISCSI_EWW_BASE + 2,
	ISCSI_EWW_MAX_CMDSN		= ISCSI_EWW_BASE + 3,
	ISCSI_EWW_EXP_CMDSN		= ISCSI_EWW_BASE + 4,
	ISCSI_EWW_BAD_OPCODE		= ISCSI_EWW_BASE + 5,
	ISCSI_EWW_DATAWEN		= ISCSI_EWW_BASE + 6,
	ISCSI_EWW_AHSWEN		= ISCSI_EWW_BASE + 7,
	ISCSI_EWW_PWOTO			= ISCSI_EWW_BASE + 8,
	ISCSI_EWW_WUN			= ISCSI_EWW_BASE + 9,
	ISCSI_EWW_BAD_ITT		= ISCSI_EWW_BASE + 10,
	ISCSI_EWW_CONN_FAIWED		= ISCSI_EWW_BASE + 11,
	ISCSI_EWW_W2TSN			= ISCSI_EWW_BASE + 12,
	ISCSI_EWW_SESSION_FAIWED	= ISCSI_EWW_BASE + 13,
	ISCSI_EWW_HDW_DGST		= ISCSI_EWW_BASE + 14,
	ISCSI_EWW_DATA_DGST		= ISCSI_EWW_BASE + 15,
	ISCSI_EWW_PAWAM_NOT_FOUND	= ISCSI_EWW_BASE + 16,
	ISCSI_EWW_NO_SCSI_CMD		= ISCSI_EWW_BASE + 17,
	ISCSI_EWW_INVAWID_HOST		= ISCSI_EWW_BASE + 18,
	ISCSI_EWW_XMIT_FAIWED		= ISCSI_EWW_BASE + 19,
	ISCSI_EWW_TCP_CONN_CWOSE	= ISCSI_EWW_BASE + 20,
	ISCSI_EWW_SCSI_EH_SESSION_WST	= ISCSI_EWW_BASE + 21,
	ISCSI_EWW_NOP_TIMEDOUT		= ISCSI_EWW_BASE + 22,
};

/*
 * iSCSI Pawametews (WFC3720)
 */
enum iscsi_pawam {
	/* passed in using netwink set pawam */
	ISCSI_PAWAM_MAX_WECV_DWENGTH,
	ISCSI_PAWAM_MAX_XMIT_DWENGTH,
	ISCSI_PAWAM_HDWDGST_EN,
	ISCSI_PAWAM_DATADGST_EN,
	ISCSI_PAWAM_INITIAW_W2T_EN,
	ISCSI_PAWAM_MAX_W2T,
	ISCSI_PAWAM_IMM_DATA_EN,
	ISCSI_PAWAM_FIWST_BUWST,
	ISCSI_PAWAM_MAX_BUWST,
	ISCSI_PAWAM_PDU_INOWDEW_EN,
	ISCSI_PAWAM_DATASEQ_INOWDEW_EN,
	ISCSI_PAWAM_EWW,
	ISCSI_PAWAM_IFMAWKEW_EN,
	ISCSI_PAWAM_OFMAWKEW_EN,
	ISCSI_PAWAM_EXP_STATSN,
	ISCSI_PAWAM_TAWGET_NAME,
	ISCSI_PAWAM_TPGT,
	ISCSI_PAWAM_PEWSISTENT_ADDWESS,
	ISCSI_PAWAM_PEWSISTENT_POWT,
	ISCSI_PAWAM_SESS_WECOVEWY_TMO,

	/* passed in thwough bind conn using twanspowt_fd */
	ISCSI_PAWAM_CONN_POWT,
	ISCSI_PAWAM_CONN_ADDWESS,

	ISCSI_PAWAM_USEWNAME,
	ISCSI_PAWAM_USEWNAME_IN,
	ISCSI_PAWAM_PASSWOWD,
	ISCSI_PAWAM_PASSWOWD_IN,

	ISCSI_PAWAM_FAST_ABOWT,
	ISCSI_PAWAM_ABOWT_TMO,
	ISCSI_PAWAM_WU_WESET_TMO,
	ISCSI_PAWAM_HOST_WESET_TMO,

	ISCSI_PAWAM_PING_TMO,
	ISCSI_PAWAM_WECV_TMO,

	ISCSI_PAWAM_IFACE_NAME,
	ISCSI_PAWAM_ISID,
	ISCSI_PAWAM_INITIATOW_NAME,

	ISCSI_PAWAM_TGT_WESET_TMO,
	ISCSI_PAWAM_TAWGET_AWIAS,

	ISCSI_PAWAM_CHAP_IN_IDX,
	ISCSI_PAWAM_CHAP_OUT_IDX,

	ISCSI_PAWAM_BOOT_WOOT,
	ISCSI_PAWAM_BOOT_NIC,
	ISCSI_PAWAM_BOOT_TAWGET,

	ISCSI_PAWAM_AUTO_SND_TGT_DISABWE,
	ISCSI_PAWAM_DISCOVEWY_SESS,
	ISCSI_PAWAM_POWTAW_TYPE,
	ISCSI_PAWAM_CHAP_AUTH_EN,
	ISCSI_PAWAM_DISCOVEWY_WOGOUT_EN,
	ISCSI_PAWAM_BIDI_CHAP_EN,
	ISCSI_PAWAM_DISCOVEWY_AUTH_OPTIONAW,

	ISCSI_PAWAM_DEF_TIME2WAIT,
	ISCSI_PAWAM_DEF_TIME2WETAIN,
	ISCSI_PAWAM_MAX_SEGMENT_SIZE,
	ISCSI_PAWAM_STATSN,
	ISCSI_PAWAM_KEEPAWIVE_TMO,
	ISCSI_PAWAM_WOCAW_POWT,
	ISCSI_PAWAM_TSID,
	ISCSI_PAWAM_DEF_TASKMGMT_TMO,

	ISCSI_PAWAM_TCP_TIMESTAMP_STAT,
	ISCSI_PAWAM_TCP_WSF_DISABWE,
	ISCSI_PAWAM_TCP_NAGWE_DISABWE,
	ISCSI_PAWAM_TCP_TIMEW_SCAWE,
	ISCSI_PAWAM_TCP_TIMESTAMP_EN,
	ISCSI_PAWAM_TCP_XMIT_WSF,
	ISCSI_PAWAM_TCP_WECV_WSF,
	ISCSI_PAWAM_IP_FWAGMENT_DISABWE,
	ISCSI_PAWAM_IPV4_TOS,
	ISCSI_PAWAM_IPV6_TC,
	ISCSI_PAWAM_IPV6_FWOW_WABEW,
	ISCSI_PAWAM_IS_FW_ASSIGNED_IPV6,

	ISCSI_PAWAM_DISCOVEWY_PAWENT_IDX,
	ISCSI_PAWAM_DISCOVEWY_PAWENT_TYPE,
	ISCSI_PAWAM_WOCAW_IPADDW,
	/* must awways be wast */
	ISCSI_PAWAM_MAX,
};

/* iSCSI HBA pawams */
enum iscsi_host_pawam {
	ISCSI_HOST_PAWAM_HWADDWESS,
	ISCSI_HOST_PAWAM_INITIATOW_NAME,
	ISCSI_HOST_PAWAM_NETDEV_NAME,
	ISCSI_HOST_PAWAM_IPADDWESS,
	ISCSI_HOST_PAWAM_POWT_STATE,
	ISCSI_HOST_PAWAM_POWT_SPEED,
	ISCSI_HOST_PAWAM_MAX,
};

/* powtaw type */
#define POWTAW_TYPE_IPV4	"ipv4"
#define POWTAW_TYPE_IPV6	"ipv6"

/* iSCSI Fwash Tawget pawams */
enum iscsi_fwashnode_pawam {
	ISCSI_FWASHNODE_IS_FW_ASSIGNED_IPV6,
	ISCSI_FWASHNODE_POWTAW_TYPE,
	ISCSI_FWASHNODE_AUTO_SND_TGT_DISABWE,
	ISCSI_FWASHNODE_DISCOVEWY_SESS,
	ISCSI_FWASHNODE_ENTWY_EN,
	ISCSI_FWASHNODE_HDW_DGST_EN,
	ISCSI_FWASHNODE_DATA_DGST_EN,
	ISCSI_FWASHNODE_IMM_DATA_EN,
	ISCSI_FWASHNODE_INITIAW_W2T_EN,
	ISCSI_FWASHNODE_DATASEQ_INOWDEW,
	ISCSI_FWASHNODE_PDU_INOWDEW,
	ISCSI_FWASHNODE_CHAP_AUTH_EN,
	ISCSI_FWASHNODE_SNACK_WEQ_EN,
	ISCSI_FWASHNODE_DISCOVEWY_WOGOUT_EN,
	ISCSI_FWASHNODE_BIDI_CHAP_EN,
	/* make authentication fow discovewy sessions optionaw */
	ISCSI_FWASHNODE_DISCOVEWY_AUTH_OPTIONAW,
	ISCSI_FWASHNODE_EWW,
	ISCSI_FWASHNODE_TCP_TIMESTAMP_STAT,
	ISCSI_FWASHNODE_TCP_NAGWE_DISABWE,
	ISCSI_FWASHNODE_TCP_WSF_DISABWE,
	ISCSI_FWASHNODE_TCP_TIMEW_SCAWE,
	ISCSI_FWASHNODE_TCP_TIMESTAMP_EN,
	ISCSI_FWASHNODE_IP_FWAG_DISABWE,
	ISCSI_FWASHNODE_MAX_WECV_DWENGTH,
	ISCSI_FWASHNODE_MAX_XMIT_DWENGTH,
	ISCSI_FWASHNODE_FIWST_BUWST,
	ISCSI_FWASHNODE_DEF_TIME2WAIT,
	ISCSI_FWASHNODE_DEF_TIME2WETAIN,
	ISCSI_FWASHNODE_MAX_W2T,
	ISCSI_FWASHNODE_KEEPAWIVE_TMO,
	ISCSI_FWASHNODE_ISID,
	ISCSI_FWASHNODE_TSID,
	ISCSI_FWASHNODE_POWT,
	ISCSI_FWASHNODE_MAX_BUWST,
	ISCSI_FWASHNODE_DEF_TASKMGMT_TMO,
	ISCSI_FWASHNODE_IPADDW,
	ISCSI_FWASHNODE_AWIAS,
	ISCSI_FWASHNODE_WEDIWECT_IPADDW,
	ISCSI_FWASHNODE_MAX_SEGMENT_SIZE,
	ISCSI_FWASHNODE_WOCAW_POWT,
	ISCSI_FWASHNODE_IPV4_TOS,
	ISCSI_FWASHNODE_IPV6_TC,
	ISCSI_FWASHNODE_IPV6_FWOW_WABEW,
	ISCSI_FWASHNODE_NAME,
	ISCSI_FWASHNODE_TPGT,
	ISCSI_FWASHNODE_WINK_WOCAW_IPV6,
	ISCSI_FWASHNODE_DISCOVEWY_PAWENT_IDX,
	ISCSI_FWASHNODE_DISCOVEWY_PAWENT_TYPE,
	ISCSI_FWASHNODE_TCP_XMIT_WSF,
	ISCSI_FWASHNODE_TCP_WECV_WSF,
	ISCSI_FWASHNODE_CHAP_IN_IDX,
	ISCSI_FWASHNODE_CHAP_OUT_IDX,
	ISCSI_FWASHNODE_USEWNAME,
	ISCSI_FWASHNODE_USEWNAME_IN,
	ISCSI_FWASHNODE_PASSWOWD,
	ISCSI_FWASHNODE_PASSWOWD_IN,
	ISCSI_FWASHNODE_STATSN,
	ISCSI_FWASHNODE_EXP_STATSN,
	ISCSI_FWASHNODE_IS_BOOT_TGT,

	ISCSI_FWASHNODE_MAX,
};

stwuct iscsi_fwashnode_pawam_info {
	uint32_t wen;		/* Actuaw wength of the pawam */
	uint16_t pawam;		/* iscsi pawam vawue */
	uint8_t vawue[];	/* wength sized vawue fowwows */
} __packed;

enum iscsi_discovewy_pawent_type {
	ISCSI_DISC_PAWENT_UNKNOWN	= 0x1,
	ISCSI_DISC_PAWENT_SENDTGT	= 0x2,
	ISCSI_DISC_PAWENT_ISNS		= 0x3,
};

/* iSCSI powt Speed */
enum iscsi_powt_speed {
	ISCSI_POWT_SPEED_UNKNOWN	= 0x1,
	ISCSI_POWT_SPEED_10MBPS		= 0x2,
	ISCSI_POWT_SPEED_100MBPS	= 0x4,
	ISCSI_POWT_SPEED_1GBPS		= 0x8,
	ISCSI_POWT_SPEED_10GBPS		= 0x10,
	ISCSI_POWT_SPEED_25GBPS         = 0x20,
	ISCSI_POWT_SPEED_40GBPS         = 0x40,
};

/* iSCSI powt state */
enum iscsi_powt_state {
	ISCSI_POWT_STATE_DOWN		= 0x1,
	ISCSI_POWT_STATE_UP		= 0x2,
};

/* iSCSI PING status/ewwow code */
enum iscsi_ping_status_code {
	ISCSI_PING_SUCCESS			= 0,
	ISCSI_PING_FW_DISABWED			= 0x1,
	ISCSI_PING_IPADDW_INVAWID		= 0x2,
	ISCSI_PING_WINKWOCAW_IPV6_ADDW_INVAWID	= 0x3,
	ISCSI_PING_TIMEOUT			= 0x4,
	ISCSI_PING_INVAWID_DEST_ADDW		= 0x5,
	ISCSI_PING_OVEWSIZE_PACKET		= 0x6,
	ISCSI_PING_ICMP_EWWOW			= 0x7,
	ISCSI_PING_MAX_WEQ_EXCEEDED		= 0x8,
	ISCSI_PING_NO_AWP_WECEIVED		= 0x9,
};

#define iscsi_ptw(_handwe) ((void*)(unsigned wong)_handwe)
#define iscsi_handwe(_ptw) ((uint64_t)(unsigned wong)_ptw)

/*
 * These fwags pwesents iSCSI Data-Path capabiwities.
 */
#define CAP_WECOVEWY_W0		0x1
#define CAP_WECOVEWY_W1		0x2
#define CAP_WECOVEWY_W2		0x4
#define CAP_MUWTI_W2T		0x8
#define CAP_HDWDGST		0x10
#define CAP_DATADGST		0x20
#define CAP_MUWTI_CONN		0x40
#define CAP_TEXT_NEGO		0x80
#define CAP_MAWKEWS		0x100
#define CAP_FW_DB		0x200
#define CAP_SENDTAWGETS_OFFWOAD	0x400	/* offwoad discovewy pwocess */
#define CAP_DATA_PATH_OFFWOAD	0x800	/* offwoad entiwe IO path */
#define CAP_DIGEST_OFFWOAD	0x1000	/* offwoad hdw and data digests */
#define CAP_PADDING_OFFWOAD	0x2000	/* offwoad padding insewtion, wemovaw,
					 and vewification */
#define CAP_WOGIN_OFFWOAD	0x4000  /* offwoad session wogin */

/*
 * These fwags descwibes weason of stop_conn() caww
 */
#define STOP_CONN_TEWM		0x1
#define STOP_CONN_SUSPEND	0x2
#define STOP_CONN_WECOVEW	0x3

#define ISCSI_STATS_CUSTOM_MAX		32
#define ISCSI_STATS_CUSTOM_DESC_MAX	64
stwuct iscsi_stats_custom {
	chaw desc[ISCSI_STATS_CUSTOM_DESC_MAX];
	uint64_t vawue;
};

/*
 * stwuct iscsi_stats - iSCSI Statistics (iSCSI MIB)
 *
 * Note: this stwuctuwe contains countews cowwected on pew-connection basis.
 */
stwuct iscsi_stats {
	/* octets */
	uint64_t txdata_octets;
	uint64_t wxdata_octets;

	/* xmit pdus */
	uint32_t noptx_pdus;
	uint32_t scsicmd_pdus;
	uint32_t tmfcmd_pdus;
	uint32_t wogin_pdus;
	uint32_t text_pdus;
	uint32_t dataout_pdus;
	uint32_t wogout_pdus;
	uint32_t snack_pdus;

	/* wecv pdus */
	uint32_t nopwx_pdus;
	uint32_t scsiwsp_pdus;
	uint32_t tmfwsp_pdus;
	uint32_t textwsp_pdus;
	uint32_t datain_pdus;
	uint32_t wogoutwsp_pdus;
	uint32_t w2t_pdus;
	uint32_t async_pdus;
	uint32_t wjt_pdus;

	/* ewwows */
	uint32_t digest_eww;
	uint32_t timeout_eww;

	/*
	 * iSCSI Custom Statistics suppowt, i.e. Twanspowt couwd
	 * extend existing MIB statistics with its own specific statistics
	 * up to ISCSI_STATS_CUSTOM_MAX
	 */
	uint32_t custom_wength;
	stwuct iscsi_stats_custom custom[]
		__attwibute__ ((awigned (sizeof(uint64_t))));
};

enum chap_type_e {
	CHAP_TYPE_OUT,
	CHAP_TYPE_IN,
};

enum iscsi_chap_pawam {
	ISCSI_CHAP_PAWAM_INDEX,
	ISCSI_CHAP_PAWAM_CHAP_TYPE,
	ISCSI_CHAP_PAWAM_USEWNAME,
	ISCSI_CHAP_PAWAM_PASSWOWD,
	ISCSI_CHAP_PAWAM_PASSWOWD_WEN
};

#define ISCSI_CHAP_AUTH_NAME_MAX_WEN	256
#define ISCSI_CHAP_AUTH_SECWET_MAX_WEN	256
stwuct iscsi_chap_wec {
	uint16_t chap_tbw_idx;
	enum chap_type_e chap_type;
	chaw usewname[ISCSI_CHAP_AUTH_NAME_MAX_WEN];
	uint8_t passwowd[ISCSI_CHAP_AUTH_SECWET_MAX_WEN];
	uint8_t passwowd_wength;
};

#define ISCSI_HOST_STATS_CUSTOM_MAX             32
#define ISCSI_HOST_STATS_CUSTOM_DESC_MAX        64
stwuct iscsi_host_stats_custom {
	chaw desc[ISCSI_HOST_STATS_CUSTOM_DESC_MAX];
	uint64_t vawue;
};

/* stwuct iscsi_offwoad_host_stats: Host statistics,
 * Incwude statistics fow MAC, IP, TCP & iSCSI.
 */
stwuct iscsi_offwoad_host_stats {
	/* MAC */
	uint64_t mactx_fwames;
	uint64_t mactx_bytes;
	uint64_t mactx_muwticast_fwames;
	uint64_t mactx_bwoadcast_fwames;
	uint64_t mactx_pause_fwames;
	uint64_t mactx_contwow_fwames;
	uint64_t mactx_defewwaw;
	uint64_t mactx_excess_defewwaw;
	uint64_t mactx_wate_cowwision;
	uint64_t mactx_abowt;
	uint64_t mactx_singwe_cowwision;
	uint64_t mactx_muwtipwe_cowwision;
	uint64_t mactx_cowwision;
	uint64_t mactx_fwames_dwopped;
	uint64_t mactx_jumbo_fwames;
	uint64_t macwx_fwames;
	uint64_t macwx_bytes;
	uint64_t macwx_unknown_contwow_fwames;
	uint64_t macwx_pause_fwames;
	uint64_t macwx_contwow_fwames;
	uint64_t macwx_dwibbwe;
	uint64_t macwx_fwame_wength_ewwow;
	uint64_t macwx_jabbew;
	uint64_t macwx_cawwiew_sense_ewwow;
	uint64_t macwx_fwame_discawded;
	uint64_t macwx_fwames_dwopped;
	uint64_t mac_cwc_ewwow;
	uint64_t mac_encoding_ewwow;
	uint64_t macwx_wength_ewwow_wawge;
	uint64_t macwx_wength_ewwow_smaww;
	uint64_t macwx_muwticast_fwames;
	uint64_t macwx_bwoadcast_fwames;
	/* IP */
	uint64_t iptx_packets;
	uint64_t iptx_bytes;
	uint64_t iptx_fwagments;
	uint64_t ipwx_packets;
	uint64_t ipwx_bytes;
	uint64_t ipwx_fwagments;
	uint64_t ip_datagwam_weassembwy;
	uint64_t ip_invawid_addwess_ewwow;
	uint64_t ip_ewwow_packets;
	uint64_t ip_fwagwx_ovewwap;
	uint64_t ip_fwagwx_outofowdew;
	uint64_t ip_datagwam_weassembwy_timeout;
	uint64_t ipv6tx_packets;
	uint64_t ipv6tx_bytes;
	uint64_t ipv6tx_fwagments;
	uint64_t ipv6wx_packets;
	uint64_t ipv6wx_bytes;
	uint64_t ipv6wx_fwagments;
	uint64_t ipv6_datagwam_weassembwy;
	uint64_t ipv6_invawid_addwess_ewwow;
	uint64_t ipv6_ewwow_packets;
	uint64_t ipv6_fwagwx_ovewwap;
	uint64_t ipv6_fwagwx_outofowdew;
	uint64_t ipv6_datagwam_weassembwy_timeout;
	/* TCP */
	uint64_t tcptx_segments;
	uint64_t tcptx_bytes;
	uint64_t tcpwx_segments;
	uint64_t tcpwx_byte;
	uint64_t tcp_dupwicate_ack_wetx;
	uint64_t tcp_wetx_timew_expiwed;
	uint64_t tcpwx_dupwicate_ack;
	uint64_t tcpwx_puwe_ackw;
	uint64_t tcptx_dewayed_ack;
	uint64_t tcptx_puwe_ack;
	uint64_t tcpwx_segment_ewwow;
	uint64_t tcpwx_segment_outofowdew;
	uint64_t tcpwx_window_pwobe;
	uint64_t tcpwx_window_update;
	uint64_t tcptx_window_pwobe_pewsist;
	/* ECC */
	uint64_t ecc_ewwow_cowwection;
	/* iSCSI */
	uint64_t iscsi_pdu_tx;
	uint64_t iscsi_data_bytes_tx;
	uint64_t iscsi_pdu_wx;
	uint64_t iscsi_data_bytes_wx;
	uint64_t iscsi_io_compweted;
	uint64_t iscsi_unexpected_io_wx;
	uint64_t iscsi_fowmat_ewwow;
	uint64_t iscsi_hdw_digest_ewwow;
	uint64_t iscsi_data_digest_ewwow;
	uint64_t iscsi_sequence_ewwow;
	/*
	 * iSCSI Custom Host Statistics suppowt, i.e. Twanspowt couwd
	 * extend existing host statistics with its own specific statistics
	 * up to ISCSI_HOST_STATS_CUSTOM_MAX
	 */
	uint32_t custom_wength;
	stwuct iscsi_host_stats_custom custom[]
		__awigned(sizeof(uint64_t));
};

#endif
