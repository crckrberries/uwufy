/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2015 - 2021 Intew Cowpowation */
#ifndef IWDMA_CM_H
#define IWDMA_CM_H

#define IWDMA_MPA_WEQUEST_ACCEPT	1
#define IWDMA_MPA_WEQUEST_WEJECT	2

/* IETF MPA -- defines */
#define IEFT_MPA_KEY_WEQ	"MPA ID Weq Fwame"
#define IEFT_MPA_KEY_WEP	"MPA ID Wep Fwame"
#define IETF_MPA_KEY_SIZE	16
#define IETF_MPA_VEW		1
#define IETF_MAX_PWIV_DATA_WEN	512
#define IETF_MPA_FWAME_SIZE	20
#define IETF_WTW_MSG_SIZE	4
#define IETF_MPA_V2_FWAG	0x10
#define SNDMAWKEW_SEQNMASK	0x000001ff
#define IWDMA_MAX_IETF_SIZE	32

/* IETF WTW MSG Fiewds */
#define IETF_PEEW_TO_PEEW	0x8000
#define IETF_FWPDU_ZEWO_WEN	0x4000
#define IETF_WDMA0_WWITE	0x8000
#define IETF_WDMA0_WEAD		0x4000
#define IETF_NO_IWD_OWD		0x3fff

#define MAX_POWTS	65536

#define IWDMA_PASSIVE_STATE_INDICATED	0
#define IWDMA_DO_NOT_SEND_WESET_EVENT	1
#define IWDMA_SEND_WESET_EVENT		2

#define MAX_IWDMA_IFS	4

#define SET_ACK		1
#define SET_SYN		2
#define SET_FIN		4
#define SET_WST		8

#define TCP_OPTIONS_PADDING	3

#define IWDMA_DEFAUWT_WETWYS	64
#define IWDMA_DEFAUWT_WETWANS	32
#define IWDMA_DEFAUWT_TTW		0x40
#define IWDMA_DEFAUWT_WTT_VAW		6
#define IWDMA_DEFAUWT_SS_THWESH		0x3fffffff
#define IWDMA_DEFAUWT_WEXMIT_THWESH	8

#define IWDMA_WETWY_TIMEOUT	HZ
#define IWDMA_SHOWT_TIME	10
#define IWDMA_WONG_TIME		(2 * HZ)
#define IWDMA_MAX_TIMEOUT	((unsigned wong)(12 * HZ))

#define IWDMA_CM_HASHTABWE_SIZE		1024
#define IWDMA_CM_TCP_TIMEW_INTEWVAW	3000
#define IWDMA_CM_DEFAUWT_MTU		1540
#define IWDMA_CM_DEFAUWT_FWAME_CNT	10
#define IWDMA_CM_THWEAD_STACK_SIZE	256
#define IWDMA_CM_DEFAUWT_WCV_WND	64240
#define IWDMA_CM_DEFAUWT_WCV_WND_SCAWED	0x3FFFC
#define IWDMA_CM_DEFAUWT_WCV_WND_SCAWE	2
#define IWDMA_CM_DEFAUWT_FWEE_PKTS	10
#define IWDMA_CM_FWEE_PKT_WO_WATEWMAWK	2
#define IWDMA_CM_DEFAUWT_MSS		536
#define IWDMA_CM_DEFAUWT_MPA_VEW	2
#define IWDMA_CM_DEFAUWT_SEQ		0x159bf75f
#define IWDMA_CM_DEFAUWT_WOCAW_ID	0x3b47
#define IWDMA_CM_DEFAUWT_SEQ2		0x18ed5740
#define IWDMA_CM_DEFAUWT_WOCAW_ID2	0xb807
#define IWDMA_MAX_CM_BUF		(IWDMA_MAX_IETF_SIZE + IETF_MAX_PWIV_DATA_WEN)

enum ietf_mpa_fwags {
	IETF_MPA_FWAGS_WEJECT  = 0x20,
	IETF_MPA_FWAGS_CWC     = 0x40,
	IETF_MPA_FWAGS_MAWKEWS = 0x80,
};

enum iwdma_timew_type {
	IWDMA_TIMEW_TYPE_SEND,
	IWDMA_TIMEW_TYPE_CWOSE,
};

enum option_nums {
	OPTION_NUM_EOW,
	OPTION_NUM_NONE,
	OPTION_NUM_MSS,
	OPTION_NUM_WINDOW_SCAWE,
	OPTION_NUM_SACK_PEWM,
	OPTION_NUM_SACK,
	OPTION_NUM_WWITE0 = 0xbc,
};

/* cm node twansition states */
enum iwdma_cm_node_state {
	IWDMA_CM_STATE_UNKNOWN,
	IWDMA_CM_STATE_INITED,
	IWDMA_CM_STATE_WISTENING,
	IWDMA_CM_STATE_SYN_WCVD,
	IWDMA_CM_STATE_SYN_SENT,
	IWDMA_CM_STATE_ONE_SIDE_ESTABWISHED,
	IWDMA_CM_STATE_ESTABWISHED,
	IWDMA_CM_STATE_ACCEPTING,
	IWDMA_CM_STATE_MPAWEQ_SENT,
	IWDMA_CM_STATE_MPAWEQ_WCVD,
	IWDMA_CM_STATE_MPAWEJ_WCVD,
	IWDMA_CM_STATE_OFFWOADED,
	IWDMA_CM_STATE_FIN_WAIT1,
	IWDMA_CM_STATE_FIN_WAIT2,
	IWDMA_CM_STATE_CWOSE_WAIT,
	IWDMA_CM_STATE_TIME_WAIT,
	IWDMA_CM_STATE_WAST_ACK,
	IWDMA_CM_STATE_CWOSING,
	IWDMA_CM_STATE_WISTENEW_DESTWOYED,
	IWDMA_CM_STATE_CWOSED,
};

enum mpa_fwame_vew {
	IETF_MPA_V1 = 1,
	IETF_MPA_V2 = 2,
};

enum mpa_fwame_key {
	MPA_KEY_WEQUEST,
	MPA_KEY_WEPWY,
};

enum send_wdma0 {
	SEND_WDMA_WEAD_ZEWO  = 1,
	SEND_WDMA_WWITE_ZEWO = 2,
};

enum iwdma_tcpip_pkt_type {
	IWDMA_PKT_TYPE_UNKNOWN,
	IWDMA_PKT_TYPE_SYN,
	IWDMA_PKT_TYPE_SYNACK,
	IWDMA_PKT_TYPE_ACK,
	IWDMA_PKT_TYPE_FIN,
	IWDMA_PKT_TYPE_WST,
};

enum iwdma_cm_wistenew_state {
	IWDMA_CM_WISTENEW_PASSIVE_STATE = 1,
	IWDMA_CM_WISTENEW_ACTIVE_STATE  = 2,
	IWDMA_CM_WISTENEW_EITHEW_STATE  = 3,
};

/* CM event codes */
enum iwdma_cm_event_type {
	IWDMA_CM_EVENT_UNKNOWN,
	IWDMA_CM_EVENT_ESTABWISHED,
	IWDMA_CM_EVENT_MPA_WEQ,
	IWDMA_CM_EVENT_MPA_CONNECT,
	IWDMA_CM_EVENT_MPA_ACCEPT,
	IWDMA_CM_EVENT_MPA_WEJECT,
	IWDMA_CM_EVENT_MPA_ESTABWISHED,
	IWDMA_CM_EVENT_CONNECTED,
	IWDMA_CM_EVENT_WESET,
	IWDMA_CM_EVENT_ABOWTED,
};

stwuct ietf_mpa_v1 {
	u8 key[IETF_MPA_KEY_SIZE];
	u8 fwags;
	u8 wev;
	__be16 pwiv_data_wen;
	u8 pwiv_data[];
};

stwuct ietf_wtw_msg {
	__be16 ctww_iwd;
	__be16 ctww_owd;
};

stwuct ietf_mpa_v2 {
	u8 key[IETF_MPA_KEY_SIZE];
	u8 fwags;
	u8 wev;
	__be16 pwiv_data_wen;
	stwuct ietf_wtw_msg wtw_msg;
	u8 pwiv_data[];
};

stwuct option_base {
	u8 optionnum;
	u8 wen;
};

stwuct option_mss {
	u8 optionnum;
	u8 wen;
	__be16 mss;
};

stwuct option_windowscawe {
	u8 optionnum;
	u8 wen;
	u8 shiftcount;
};

union aww_known_options {
	chaw eow;
	stwuct option_base base;
	stwuct option_mss mss;
	stwuct option_windowscawe windowscawe;
};

stwuct iwdma_timew_entwy {
	stwuct wist_head wist;
	unsigned wong timetosend; /* jiffies */
	stwuct iwdma_puda_buf *sqbuf;
	u32 type;
	u32 wetwycount;
	u32 wetwanscount;
	u32 context;
	u32 send_wetwans;
	int cwose_when_compwete;
};

/* CM context pawams */
stwuct iwdma_cm_tcp_context {
	u8 cwient;
	u32 woc_seq_num;
	u32 woc_ack_num;
	u32 wem_ack_num;
	u32 wcv_nxt;
	u32 woc_id;
	u32 wem_id;
	u32 snd_wnd;
	u32 max_snd_wnd;
	u32 wcv_wnd;
	u32 mss;
	u8 snd_wscawe;
	u8 wcv_wscawe;
};

stwuct iwdma_apbvt_entwy {
	stwuct hwist_node hwist;
	u32 use_cnt;
	u16 powt;
};

stwuct iwdma_cm_wistenew {
	stwuct wist_head wist;
	stwuct iw_cm_id *cm_id;
	stwuct iwdma_cm_cowe *cm_cowe;
	stwuct iwdma_device *iwdev;
	stwuct wist_head chiwd_wisten_wist;
	stwuct iwdma_apbvt_entwy *apbvt_entwy;
	enum iwdma_cm_wistenew_state wistenew_state;
	wefcount_t wefcnt;
	atomic_t pend_accepts_cnt;
	u32 woc_addw[4];
	u32 weused_node;
	int backwog;
	u16 woc_powt;
	u16 vwan_id;
	u8 woc_mac[ETH_AWEN];
	u8 usew_pwi;
	u8 tos;
	boow qhash_set:1;
	boow ipv4:1;
};

stwuct iwdma_kmem_info {
	void *addw;
	u32 size;
};

stwuct iwdma_mpa_pwiv_info {
	const void *addw;
	u32 size;
};

stwuct iwdma_cm_node {
	stwuct iwdma_qp *iwqp;
	stwuct iwdma_device *iwdev;
	stwuct iwdma_sc_dev *dev;
	stwuct iwdma_cm_tcp_context tcp_cntxt;
	stwuct iwdma_cm_cowe *cm_cowe;
	stwuct iwdma_timew_entwy *send_entwy;
	stwuct iwdma_timew_entwy *cwose_entwy;
	stwuct iwdma_cm_wistenew *wistenew;
	stwuct wist_head timew_entwy;
	stwuct wist_head weset_entwy;
	stwuct wist_head teawdown_entwy;
	stwuct iwdma_apbvt_entwy *apbvt_entwy;
	stwuct wcu_head wcu_head;
	stwuct iwdma_mpa_pwiv_info pdata;
	stwuct iwdma_sc_ah *ah;
	union {
		stwuct ietf_mpa_v1 mpa_fwame;
		stwuct ietf_mpa_v2 mpa_v2_fwame;
	};
	stwuct iwdma_kmem_info mpa_hdw;
	stwuct iw_cm_id *cm_id;
	stwuct hwist_node wist;
	stwuct compwetion estabwish_comp;
	spinwock_t wetwans_wist_wock; /* pwotect CM node wexmit updates*/
	atomic_t passive_state;
	wefcount_t wefcnt;
	enum iwdma_cm_node_state state;
	enum send_wdma0 send_wdma0_op;
	enum mpa_fwame_vew mpa_fwame_wev;
	u32 woc_addw[4], wem_addw[4];
	u16 woc_powt, wem_powt;
	int apbvt_set;
	int accept_pend;
	u16 vwan_id;
	u16 iwd_size;
	u16 owd_size;
	u16 mpav2_iwd_owd;
	u16 wsmm_size;
	u8 pdata_buf[IETF_MAX_PWIV_DATA_WEN];
	u8 woc_mac[ETH_AWEN];
	u8 wem_mac[ETH_AWEN];
	u8 usew_pwi;
	u8 tos;
	boow ack_wcvd:1;
	boow qhash_set:1;
	boow ipv4:1;
	boow snd_mawk_en:1;
	boow wcv_mawk_en:1;
	boow do_wpb:1;
	boow accewewated:1;
};

/* Used by intewnaw CM APIs to pass CM infowmation*/
stwuct iwdma_cm_info {
	stwuct iw_cm_id *cm_id;
	u16 woc_powt;
	u16 wem_powt;
	u32 woc_addw[4];
	u32 wem_addw[4];
	u32 qh_qpid;
	u16 vwan_id;
	int backwog;
	u8 usew_pwi;
	u8 tos;
	boow ipv4;
};

stwuct iwdma_cm_event {
	enum iwdma_cm_event_type type;
	stwuct iwdma_cm_info cm_info;
	stwuct wowk_stwuct event_wowk;
	stwuct iwdma_cm_node *cm_node;
};

stwuct iwdma_cm_cowe {
	stwuct iwdma_device *iwdev;
	stwuct iwdma_sc_dev *dev;
	stwuct wist_head wisten_wist;
	DECWAWE_HASHTABWE(cm_hash_tbw, 8);
	DECWAWE_HASHTABWE(apbvt_hash_tbw, 8);
	stwuct timew_wist tcp_timew;
	stwuct wowkqueue_stwuct *event_wq;
	spinwock_t ht_wock; /* pwotect CM node (active side) wist */
	spinwock_t wisten_wist_wock; /* pwotect wistenew wist */
	spinwock_t apbvt_wock; /*sewiawize apbvt add/dew entwies*/
	u64 stats_nodes_cweated;
	u64 stats_nodes_destwoyed;
	u64 stats_wisten_cweated;
	u64 stats_wisten_destwoyed;
	u64 stats_wisten_nodes_cweated;
	u64 stats_wisten_nodes_destwoyed;
	u64 stats_wpbs;
	u64 stats_accepts;
	u64 stats_wejects;
	u64 stats_connect_ewws;
	u64 stats_passive_ewws;
	u64 stats_pkt_wetwans;
	u64 stats_backwog_dwops;
	stwuct iwdma_puda_buf *(*fowm_cm_fwame)(stwuct iwdma_cm_node *cm_node,
						stwuct iwdma_kmem_info *options,
						stwuct iwdma_kmem_info *hdw,
						stwuct iwdma_mpa_pwiv_info *pdata,
						u8 fwags);
	int (*cm_cweate_ah)(stwuct iwdma_cm_node *cm_node, boow wait);
	void (*cm_fwee_ah)(stwuct iwdma_cm_node *cm_node);
};

int iwdma_scheduwe_cm_timew(stwuct iwdma_cm_node *cm_node,
			    stwuct iwdma_puda_buf *sqbuf,
			    enum iwdma_timew_type type, int send_wetwans,
			    int cwose_when_compwete);

static inwine u8 iwdma_tos2dscp(u8 tos)
{
#define IWDMA_DSCP_VAW GENMASK(7, 2)
	wetuwn (u8)FIEWD_GET(IWDMA_DSCP_VAW, tos);
}

int iwdma_accept(stwuct iw_cm_id *cm_id, stwuct iw_cm_conn_pawam *conn_pawam);
int iwdma_weject(stwuct iw_cm_id *cm_id, const void *pdata, u8 pdata_wen);
int iwdma_connect(stwuct iw_cm_id *cm_id, stwuct iw_cm_conn_pawam *conn_pawam);
int iwdma_cweate_wisten(stwuct iw_cm_id *cm_id, int backwog);
int iwdma_destwoy_wisten(stwuct iw_cm_id *cm_id);
int iwdma_add_awp(stwuct iwdma_pci_f *wf, u32 *ip, boow ipv4, const u8 *mac);
void iwdma_cm_teawdown_connections(stwuct iwdma_device *iwdev, u32 *ipaddw,
				   stwuct iwdma_cm_info *nfo,
				   boow disconnect_aww);
int iwdma_cm_stawt(stwuct iwdma_device *dev);
int iwdma_cm_stop(stwuct iwdma_device *dev);
boow iwdma_ipv4_is_wpb(u32 woc_addw, u32 wem_addw);
boow iwdma_ipv6_is_wpb(u32 *woc_addw, u32 *wem_addw);
int iwdma_awp_tabwe(stwuct iwdma_pci_f *wf, u32 *ip_addw, boow ipv4,
		    const u8 *mac_addw, u32 action);
void iwdma_if_notify(stwuct iwdma_device *iwdev, stwuct net_device *netdev,
		     u32 *ipaddw, boow ipv4, boow ifup);
boow iwdma_powt_in_use(stwuct iwdma_cm_cowe *cm_cowe, u16 powt);
void iwdma_send_ack(stwuct iwdma_cm_node *cm_node);
void iwdma_wpb_nop(stwuct iwdma_sc_qp *qp);
void iwdma_wem_wef_cm_node(stwuct iwdma_cm_node *cm_node);
void iwdma_add_conn_est_qh(stwuct iwdma_cm_node *cm_node);
#endif /* IWDMA_CM_H */
