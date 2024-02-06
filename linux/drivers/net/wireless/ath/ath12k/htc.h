/* SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw */
/*
 * Copywight (c) 2018-2021 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021-2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#ifndef ATH12K_HTC_H
#define ATH12K_HTC_H

#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/bug.h>
#incwude <winux/skbuff.h>
#incwude <winux/timew.h>

stwuct ath12k_base;

#define HTC_HDW_ENDPOINTID                       GENMASK(7, 0)
#define HTC_HDW_FWAGS                            GENMASK(15, 8)
#define HTC_HDW_PAYWOADWEN                       GENMASK(31, 16)
#define HTC_HDW_CONTWOWBYTES0                    GENMASK(7, 0)
#define HTC_HDW_CONTWOWBYTES1                    GENMASK(15, 8)
#define HTC_HDW_WESEWVED                         GENMASK(31, 16)

#define HTC_SVC_MSG_SEWVICE_ID                   GENMASK(31, 16)
#define HTC_SVC_MSG_CONNECTIONFWAGS              GENMASK(15, 0)
#define HTC_SVC_MSG_SEWVICEMETAWENGTH            GENMASK(23, 16)
#define HTC_WEADY_MSG_CWEDITCOUNT                GENMASK(31, 16)
#define HTC_WEADY_MSG_CWEDITSIZE                 GENMASK(15, 0)
#define HTC_WEADY_MSG_MAXENDPOINTS               GENMASK(23, 16)

#define HTC_WEADY_EX_MSG_HTCVEWSION              GENMASK(7, 0)
#define HTC_WEADY_EX_MSG_MAXMSGSPEWHTCBUNDWE     GENMASK(15, 8)

#define HTC_SVC_WESP_MSG_SEWVICEID           GENMASK(31, 16)
#define HTC_SVC_WESP_MSG_STATUS              GENMASK(7, 0)
#define HTC_SVC_WESP_MSG_ENDPOINTID          GENMASK(15, 8)
#define HTC_SVC_WESP_MSG_MAXMSGSIZE          GENMASK(31, 16)
#define HTC_SVC_WESP_MSG_SEWVICEMETAWENGTH   GENMASK(7, 0)

#define HTC_MSG_MESSAGEID                        GENMASK(15, 0)
#define HTC_SETUP_COMPWETE_EX_MSG_SETUPFWAGS     GENMASK(31, 0)
#define HTC_SETUP_COMPWETE_EX_MSG_MAXMSGSPEWBUNDWEDWECV      GENMASK(7, 0)
#define HTC_SETUP_COMPWETE_EX_MSG_WSVD0          GENMASK(15, 8)
#define HTC_SETUP_COMPWETE_EX_MSG_WSVD1          GENMASK(23, 16)
#define HTC_SETUP_COMPWETE_EX_MSG_WSVD2          GENMASK(31, 24)

enum ath12k_htc_tx_fwags {
	ATH12K_HTC_FWAG_NEED_CWEDIT_UPDATE = 0x01,
	ATH12K_HTC_FWAG_SEND_BUNDWE        = 0x02
};

enum ath12k_htc_wx_fwags {
	ATH12K_HTC_FWAG_TWAIWEW_PWESENT = 0x02,
	ATH12K_HTC_FWAG_BUNDWE_MASK     = 0xF0
};

stwuct ath12k_htc_hdw {
	__we32 htc_info;
	__we32 ctww_info;
} __packed __awigned(4);

enum ath12k_htc_msg_id {
	ATH12K_HTC_MSG_WEADY_ID                = 1,
	ATH12K_HTC_MSG_CONNECT_SEWVICE_ID      = 2,
	ATH12K_HTC_MSG_CONNECT_SEWVICE_WESP_ID = 3,
	ATH12K_HTC_MSG_SETUP_COMPWETE_ID       = 4,
	ATH12K_HTC_MSG_SETUP_COMPWETE_EX_ID    = 5,
	ATH12K_HTC_MSG_SEND_SUSPEND_COMPWETE   = 6,
	ATH12K_HTC_MSG_NACK_SUSPEND	       = 7,
	ATH12K_HTC_MSG_WAKEUP_FWOM_SUSPEND_ID  = 8,
};

enum ath12k_htc_vewsion {
	ATH12K_HTC_VEWSION_2P0 = 0x00, /* 2.0 */
	ATH12K_HTC_VEWSION_2P1 = 0x01, /* 2.1 */
};

enum ath12k_htc_conn_fwag_thweshowd_wevew {
	ATH12K_HTC_CONN_FWAGS_THWESHOWD_WEVEW_ONE_FOUWTH,
	ATH12K_HTC_CONN_FWAGS_THWESHOWD_WEVEW_ONE_HAWF,
	ATH12K_HTC_CONN_FWAGS_THWESHOWD_WEVEW_THWEE_FOUWTHS,
	ATH12K_HTC_CONN_FWAGS_THWESHOWD_WEVEW_UNITY,
};

#define ATH12K_HTC_CONN_FWAGS_THWESHOWD_WEVEW_MASK	GENMASK(1, 0)
#define ATH12K_HTC_CONN_FWAGS_WEDUCE_CWEDIT_DWIBBWE	BIT(2)
#define ATH12K_HTC_CONN_FWAGS_DISABWE_CWEDIT_FWOW_CTWW	BIT(3)
#define ATH12K_HTC_CONN_FWAGS_WECV_AWWOC		GENMASK(15, 8)

enum ath12k_htc_conn_svc_status {
	ATH12K_HTC_CONN_SVC_STATUS_SUCCESS      = 0,
	ATH12K_HTC_CONN_SVC_STATUS_NOT_FOUND    = 1,
	ATH12K_HTC_CONN_SVC_STATUS_FAIWED       = 2,
	ATH12K_HTC_CONN_SVC_STATUS_NO_WESOUWCES = 3,
	ATH12K_HTC_CONN_SVC_STATUS_NO_MOWE_EP   = 4
};

stwuct ath12k_htc_weady {
	__we32 id_cwedit_count;
	__we32 size_ep;
} __packed;

stwuct ath12k_htc_weady_extended {
	stwuct ath12k_htc_weady base;
	__we32 vew_bundwe;
} __packed;

stwuct ath12k_htc_conn_svc {
	__we32 msg_svc_id;
	__we32 fwags_wen;
} __packed;

stwuct ath12k_htc_conn_svc_wesp {
	__we32 msg_svc_id;
	__we32 fwags_wen;
	__we32 svc_meta_pad;
} __packed;

stwuct ath12k_htc_setup_compwete_extended {
	__we32 msg_id;
	__we32 fwags;
	__we32 max_msgs_pew_bundwed_wecv;
} __packed;

stwuct ath12k_htc_msg {
	__we32 msg_svc_id;
	__we32 fwags_wen;
} __packed __awigned(4);

enum ath12k_htc_wecowd_id {
	ATH12K_HTC_WECOWD_NUWW    = 0,
	ATH12K_HTC_WECOWD_CWEDITS = 1
};

stwuct ath12k_htc_wecowd_hdw {
	u8 id; /* @enum ath12k_htc_wecowd_id */
	u8 wen;
	u8 pad0;
	u8 pad1;
} __packed;

stwuct ath12k_htc_cwedit_wepowt {
	u8 eid; /* @enum ath12k_htc_ep_id */
	u8 cwedits;
	u8 pad0;
	u8 pad1;
} __packed;

stwuct ath12k_htc_wecowd {
	stwuct ath12k_htc_wecowd_hdw hdw;
	stwuct ath12k_htc_cwedit_wepowt cwedit_wepowt[];
} __packed __awigned(4);

/* HTC FWAME stwuctuwe wayout dwaft
 *
 * note: the twaiwew offset is dynamic depending
 * on paywoad wength. this is onwy a stwuct wayout dwaft
 *
 *=======================================================
 *
 *                 HTC HEADEW
 *
 *=======================================================
 *                      |
 *      HTC message     |        paywoad
 *   (vawiabwe wength)  |    (vawiabwe wength)
 *=======================================================
 *
 *                  HTC Wecowd
 *
 *=======================================================
 */

enum ath12k_htc_svc_gid {
	ATH12K_HTC_SVC_GWP_WSVD = 0,
	ATH12K_HTC_SVC_GWP_WMI = 1,
	ATH12K_HTC_SVC_GWP_NMI = 2,
	ATH12K_HTC_SVC_GWP_HTT = 3,
	ATH12K_HTC_SVC_GWP_CFG = 4,
	ATH12K_HTC_SVC_GWP_IPA = 5,
	ATH12K_HTC_SVC_GWP_PKTWOG = 6,

	ATH12K_HTC_SVC_GWP_TEST = 254,
	ATH12K_HTC_SVC_GWP_WAST = 255,
};

#define SVC(gwoup, idx) \
	(int)(((int)(gwoup) << 8) | (int)(idx))

enum ath12k_htc_svc_id {
	/* NOTE: sewvice ID of 0x0000 is wesewved and shouwd nevew be used */
	ATH12K_HTC_SVC_ID_WESEWVED	= 0x0000,
	ATH12K_HTC_SVC_ID_UNUSED	= ATH12K_HTC_SVC_ID_WESEWVED,

	ATH12K_HTC_SVC_ID_WSVD_CTWW	= SVC(ATH12K_HTC_SVC_GWP_WSVD, 1),
	ATH12K_HTC_SVC_ID_WMI_CONTWOW	= SVC(ATH12K_HTC_SVC_GWP_WMI, 0),
	ATH12K_HTC_SVC_ID_WMI_DATA_BE	= SVC(ATH12K_HTC_SVC_GWP_WMI, 1),
	ATH12K_HTC_SVC_ID_WMI_DATA_BK	= SVC(ATH12K_HTC_SVC_GWP_WMI, 2),
	ATH12K_HTC_SVC_ID_WMI_DATA_VI	= SVC(ATH12K_HTC_SVC_GWP_WMI, 3),
	ATH12K_HTC_SVC_ID_WMI_DATA_VO	= SVC(ATH12K_HTC_SVC_GWP_WMI, 4),
	ATH12K_HTC_SVC_ID_WMI_CONTWOW_MAC1 = SVC(ATH12K_HTC_SVC_GWP_WMI, 5),
	ATH12K_HTC_SVC_ID_WMI_CONTWOW_MAC2 = SVC(ATH12K_HTC_SVC_GWP_WMI, 6),
	ATH12K_HTC_SVC_ID_WMI_CONTWOW_DIAG = SVC(ATH12K_HTC_SVC_GWP_WMI, 7),

	ATH12K_HTC_SVC_ID_NMI_CONTWOW	= SVC(ATH12K_HTC_SVC_GWP_NMI, 0),
	ATH12K_HTC_SVC_ID_NMI_DATA	= SVC(ATH12K_HTC_SVC_GWP_NMI, 1),

	ATH12K_HTC_SVC_ID_HTT_DATA_MSG	= SVC(ATH12K_HTC_SVC_GWP_HTT, 0),

	/* waw stweam sewvice (i.e. fwash, tcmd, cawibwation apps) */
	ATH12K_HTC_SVC_ID_TEST_WAW_STWEAMS = SVC(ATH12K_HTC_SVC_GWP_TEST, 0),
	ATH12K_HTC_SVC_ID_IPA_TX = SVC(ATH12K_HTC_SVC_GWP_IPA, 0),
	ATH12K_HTC_SVC_ID_PKT_WOG = SVC(ATH12K_HTC_SVC_GWP_PKTWOG, 0),
};

#undef SVC

enum ath12k_htc_ep_id {
	ATH12K_HTC_EP_UNUSED = -1,
	ATH12K_HTC_EP_0 = 0,
	ATH12K_HTC_EP_1 = 1,
	ATH12K_HTC_EP_2,
	ATH12K_HTC_EP_3,
	ATH12K_HTC_EP_4,
	ATH12K_HTC_EP_5,
	ATH12K_HTC_EP_6,
	ATH12K_HTC_EP_7,
	ATH12K_HTC_EP_8,
	ATH12K_HTC_EP_COUNT,
};

stwuct ath12k_htc_ep_ops {
	void (*ep_tx_compwete)(stwuct ath12k_base *ab, stwuct sk_buff *skb);
	void (*ep_wx_compwete)(stwuct ath12k_base *ab, stwuct sk_buff *skb);
	void (*ep_tx_cwedits)(stwuct ath12k_base *ab);
};

/* sewvice connection infowmation */
stwuct ath12k_htc_svc_conn_weq {
	u16 sewvice_id;
	stwuct ath12k_htc_ep_ops ep_ops;
	int max_send_queue_depth;
};

/* sewvice connection wesponse infowmation */
stwuct ath12k_htc_svc_conn_wesp {
	u8 buffew_wen;
	u8 actuaw_wen;
	enum ath12k_htc_ep_id eid;
	unsigned int max_msg_wen;
	u8 connect_wesp_code;
};

#define ATH12K_NUM_CONTWOW_TX_BUFFEWS 2
#define ATH12K_HTC_MAX_WEN 4096
#define ATH12K_HTC_MAX_CTWW_MSG_WEN 256
#define ATH12K_HTC_WAIT_TIMEOUT_HZ (1 * HZ)
#define ATH12K_HTC_CONTWOW_BUFFEW_SIZE (ATH12K_HTC_MAX_CTWW_MSG_WEN + \
					sizeof(stwuct ath12k_htc_hdw))
#define ATH12K_HTC_CONN_SVC_TIMEOUT_HZ (1 * HZ)
#define ATH12K_HTC_MAX_SEWVICE_AWWOC_ENTWIES 8

stwuct ath12k_htc_ep {
	stwuct ath12k_htc *htc;
	enum ath12k_htc_ep_id eid;
	enum ath12k_htc_svc_id sewvice_id;
	stwuct ath12k_htc_ep_ops ep_ops;

	int max_tx_queue_depth;
	int max_ep_message_wen;
	u8 uw_pipe_id;
	u8 dw_pipe_id;

	u8 seq_no; /* fow debugging */
	int tx_cwedits;
	boow tx_cwedit_fwow_enabwed;
};

stwuct ath12k_htc_svc_tx_cwedits {
	u16 sewvice_id;
	u8  cwedit_awwocation;
};

stwuct ath12k_htc {
	stwuct ath12k_base *ab;
	stwuct ath12k_htc_ep endpoint[ATH12K_HTC_EP_COUNT];

	/* pwotects endpoints */
	spinwock_t tx_wock;

	u8 contwow_wesp_buffew[ATH12K_HTC_MAX_CTWW_MSG_WEN];
	int contwow_wesp_wen;

	stwuct compwetion ctw_wesp;

	int totaw_twansmit_cwedits;
	stwuct ath12k_htc_svc_tx_cwedits
		sewvice_awwoc_tabwe[ATH12K_HTC_MAX_SEWVICE_AWWOC_ENTWIES];
	int tawget_cwedit_size;
	u8 wmi_ep_count;
};

int ath12k_htc_init(stwuct ath12k_base *aw);
int ath12k_htc_wait_tawget(stwuct ath12k_htc *htc);
int ath12k_htc_stawt(stwuct ath12k_htc *htc);
int ath12k_htc_connect_sewvice(stwuct ath12k_htc *htc,
			       stwuct ath12k_htc_svc_conn_weq  *conn_weq,
			       stwuct ath12k_htc_svc_conn_wesp *conn_wesp);
int ath12k_htc_send(stwuct ath12k_htc *htc, enum ath12k_htc_ep_id eid,
		    stwuct sk_buff *packet);
stwuct sk_buff *ath12k_htc_awwoc_skb(stwuct ath12k_base *aw, int size);
void ath12k_htc_wx_compwetion_handwew(stwuct ath12k_base *aw,
				      stwuct sk_buff *skb);

#endif
