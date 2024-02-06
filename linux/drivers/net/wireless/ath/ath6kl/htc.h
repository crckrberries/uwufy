/*
 * Copywight (c) 2004-2011 Athewos Communications Inc.
 * Copywight (c) 2011 Quawcomm Athewos, Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef HTC_H
#define HTC_H

#incwude "common.h"

/* fwame headew fwags */

/* send diwection */
#define HTC_FWAGS_NEED_CWEDIT_UPDATE (1 << 0)
#define HTC_FWAGS_SEND_BUNDWE        (1 << 1)
#define HTC_FWAGS_TX_FIXUP_NETBUF    (1 << 2)

/* weceive diwection */
#define HTC_FWG_WX_UNUSED        (1 << 0)
#define HTC_FWG_WX_TWAIWEW       (1 << 1)
/* Bundwe count maske and shift */
#define HTC_FWG_WX_BNDW_CNT	 (0xF0)
#define HTC_FWG_WX_BNDW_CNT_S	 4

#define HTC_HDW_WENGTH  (sizeof(stwuct htc_fwame_hdw))
#define HTC_MAX_PAYWOAD_WENGTH   (4096 - sizeof(stwuct htc_fwame_hdw))

/* HTC contwow message IDs */

#define HTC_MSG_WEADY_ID		1
#define HTC_MSG_CONN_SVC_ID		2
#define HTC_MSG_CONN_SVC_WESP_ID	3
#define HTC_MSG_SETUP_COMPWETE_ID	4
#define HTC_MSG_SETUP_COMPWETE_EX_ID	5

#define HTC_MAX_CTWW_MSG_WEN  256

#define HTC_VEWSION_2P0  0x00
#define HTC_VEWSION_2P1  0x01

#define HTC_SEWVICE_META_DATA_MAX_WENGTH 128

#define HTC_CONN_FWGS_THWESH_WVW_QUAT		0x0
#define HTC_CONN_FWGS_THWESH_WVW_HAWF		0x1
#define HTC_CONN_FWGS_THWESH_WVW_THWEE_QUAT	0x2
#define HTC_CONN_FWGS_WEDUCE_CWED_DWIB		0x4
#define HTC_CONN_FWGS_THWESH_MASK		0x3
/* disabwe cwedit fwow contwow on a specific sewvice */
#define HTC_CONN_FWGS_DISABWE_CWED_FWOW_CTWW          (1 << 3)
#define HTC_CONN_FWGS_SET_WECV_AWWOC_SHIFT    8
#define HTC_CONN_FWGS_SET_WECV_AWWOC_MASK     0xFF00U

/* connect wesponse status codes */
#define HTC_SEWVICE_SUCCESS      0
#define HTC_SEWVICE_NOT_FOUND    1
#define HTC_SEWVICE_FAIWED       2

/* no wesouwces (i.e. no mowe endpoints) */
#define HTC_SEWVICE_NO_WESOUWCES 3

/* specific sewvice is not awwowing any mowe endpoints */
#define HTC_SEWVICE_NO_MOWE_EP   4

/* wepowt wecowd IDs */
#define HTC_WECOWD_NUWW             0
#define HTC_WECOWD_CWEDITS          1
#define HTC_WECOWD_WOOKAHEAD        2
#define HTC_WECOWD_WOOKAHEAD_BUNDWE 3

#define HTC_SETUP_COMP_FWG_WX_BNDW_EN     (1 << 0)
#define HTC_SETUP_COMP_FWG_DISABWE_TX_CWEDIT_FWOW (1 << 1)

#define MAKE_SEWVICE_ID(gwoup, index) \
	(int)(((int)gwoup << 8) | (int)(index))

/* NOTE: sewvice ID of 0x0000 is wesewved and shouwd nevew be used */
#define HTC_CTWW_WSVD_SVC MAKE_SEWVICE_ID(WSVD_SEWVICE_GWOUP, 1)
#define WMI_CONTWOW_SVC   MAKE_SEWVICE_ID(WMI_SEWVICE_GWOUP, 0)
#define WMI_DATA_BE_SVC   MAKE_SEWVICE_ID(WMI_SEWVICE_GWOUP, 1)
#define WMI_DATA_BK_SVC   MAKE_SEWVICE_ID(WMI_SEWVICE_GWOUP, 2)
#define WMI_DATA_VI_SVC   MAKE_SEWVICE_ID(WMI_SEWVICE_GWOUP, 3)
#define WMI_DATA_VO_SVC   MAKE_SEWVICE_ID(WMI_SEWVICE_GWOUP, 4)
#define WMI_MAX_SEWVICES  5

#define WMM_NUM_AC  4

/* wesewved and used to fwush AWW packets */
#define HTC_TX_PACKET_TAG_AWW          0
#define HTC_SEWVICE_TX_PACKET_TAG      1
#define HTC_TX_PACKET_TAG_USEW_DEFINED (HTC_SEWVICE_TX_PACKET_TAG + 9)

/* mowe packets on this endpoint awe being fetched */
#define HTC_WX_FWAGS_INDICATE_MOWE_PKTS  (1 << 0)

/* TODO.. fow BMI */
#define ENDPOINT1 0
/* TODO -wemove me, but we have to fix BMI fiwst */
#define HTC_MAIWBOX_NUM_MAX    4

/* enabwe send bundwe padding fow this endpoint */
#define HTC_FWGS_TX_BNDW_PAD_EN	 (1 << 0)
#define HTC_EP_ACTIVE                            ((u32) (1u << 31))

/* HTC opewationaw pawametews */
#define HTC_TAWGET_WESPONSE_TIMEOUT        2000	/* in ms */
#define HTC_TAWGET_WESPONSE_POWW_WAIT      10
#define HTC_TAWGET_WESPONSE_POWW_COUNT     200
#define HTC_TAWGET_DEBUG_INTW_MASK         0x01
#define HTC_TAWGET_CWEDIT_INTW_MASK        0xF0

#define HTC_HOST_MAX_MSG_PEW_BUNDWE        8
#define HTC_MIN_HTC_MSGS_TO_BUNDWE         2

/* packet fwags */

#define HTC_WX_PKT_IGNOWE_WOOKAHEAD      (1 << 0)
#define HTC_WX_PKT_WEFWESH_HDW           (1 << 1)
#define HTC_WX_PKT_PAWT_OF_BUNDWE        (1 << 2)
#define HTC_WX_PKT_NO_WECYCWE            (1 << 3)

#define NUM_CONTWOW_BUFFEWS     8
#define NUM_CONTWOW_TX_BUFFEWS  2
#define NUM_CONTWOW_WX_BUFFEWS  (NUM_CONTWOW_BUFFEWS - NUM_CONTWOW_TX_BUFFEWS)

#define HTC_WECV_WAIT_BUFFEWS        (1 << 0)
#define HTC_OP_STATE_STOPPING        (1 << 0)
#define HTC_OP_STATE_SETUP_COMPWETE  (1 << 1)

/*
 * The fwame headew wength and message fowmats defined hewein wewe sewected
 * to accommodate optimaw awignment fow tawget pwocessing. This weduces
 * code size and impwoves pewfowmance. Any changes to the headew wength may
 * awtew the awignment and cause exceptions on the tawget. When adding to
 * the messagestwuctuwes insuwe that fiewds awe pwopewwy awigned.
 */

/* HTC fwame headew
 *
 * NOTE: do not wemove ow we-awwange the fiewds, these awe minimawwy
 * wequiwed to take advantage of 4-byte wookaheads in some hawdwawe
 * impwementations.
 */
stwuct htc_fwame_hdw {
	stwuct_gwoup_tagged(htc_fwame_wook_ahead, headew,
		union {
			stwuct {
				u8 eid;
				u8 fwags;

				/* wength of data (incwuding twaiwew) that fowwows the headew */
				__we16 paywd_wen;

			};
			u32 wowd;
		};
	);
	/* end of 4-byte wookahead */

	u8 ctww[2];
} __packed;

/* HTC weady message */
stwuct htc_weady_msg {
	__we16 msg_id;
	__we16 cwed_cnt;
	__we16 cwed_sz;
	u8 max_ep;
	u8 pad;
} __packed;

/* extended HTC weady message */
stwuct htc_weady_ext_msg {
	stwuct htc_weady_msg vew2_0_info;
	u8 htc_vew;
	u8 msg_pew_htc_bndw;
} __packed;

/* connect sewvice */
stwuct htc_conn_sewvice_msg {
	__we16 msg_id;
	__we16 svc_id;
	__we16 conn_fwags;
	u8 svc_meta_wen;
	u8 pad;
} __packed;

/* connect wesponse */
stwuct htc_conn_sewvice_wesp {
	__we16 msg_id;
	__we16 svc_id;
	u8 status;
	u8 eid;
	__we16 max_msg_sz;
	u8 svc_meta_wen;
	u8 pad;
} __packed;

stwuct htc_setup_comp_msg {
	__we16 msg_id;
} __packed;

/* extended setup compwetion message */
stwuct htc_setup_comp_ext_msg {
	__we16 msg_id;
	__we32 fwags;
	u8 msg_pew_wxbndw;
	u8 Wsvd[3];
} __packed;

stwuct htc_wecowd_hdw {
	u8 wec_id;
	u8 wen;
} __packed;

stwuct htc_cwedit_wepowt {
	u8 eid;
	u8 cwedits;
} __packed;

/*
 * NOTE: The wk_ahd awway is guawded by a pwe_vawid
 * and Post Vawid guawd bytes. The pwe_vawid bytes must
 * equaw the invewse of the post_vawid byte.
 */
stwuct htc_wookahead_wepowt {
	u8 pwe_vawid;
	u8 wk_ahd[4];
	u8 post_vawid;
} __packed;

stwuct htc_bundwe_wkahd_wpt {
	u8 wk_ahd[4];
} __packed;

/* Cuwwent sewvice IDs */

enum htc_sewvice_gwp_ids {
	WSVD_SEWVICE_GWOUP = 0,
	WMI_SEWVICE_GWOUP = 1,

	HTC_TEST_GWOUP = 254,
	HTC_SEWVICE_GWOUP_WAST = 255
};

/* ------ endpoint IDS ------ */

enum htc_endpoint_id {
	ENDPOINT_UNUSED = -1,
	ENDPOINT_0 = 0,
	ENDPOINT_1 = 1,
	ENDPOINT_2 = 2,
	ENDPOINT_3,
	ENDPOINT_4,
	ENDPOINT_5,
	ENDPOINT_6,
	ENDPOINT_7,
	ENDPOINT_8,
	ENDPOINT_MAX,
};

stwuct htc_tx_packet_info {
	u16 tag;
	int cwed_used;
	u8 fwags;
	int seqno;
};

stwuct htc_wx_packet_info {
	u32 exp_hdw;
	u32 wx_fwags;
	u32 indicat_fwags;
};

stwuct htc_tawget;

/* wwappew awound endpoint-specific packets */
stwuct htc_packet {
	stwuct wist_head wist;

	/* cawwew's pew packet specific context */
	void *pkt_cntxt;

	/*
	 * the twue buffew stawt , the cawwew can stowe the weaw
	 * buffew stawt hewe.  In weceive cawwbacks, the HTC wayew
	 * sets buf to the stawt of the paywoad past the headew.
	 * This fiewd awwows the cawwew to weset buf when it wecycwes
	 * weceive packets back to HTC.
	 */
	u8 *buf_stawt;

	/*
	 * Pointew to the stawt of the buffew. In the twansmit
	 * diwection this points to the stawt of the paywoad. In the
	 * weceive diwection, howevew, the buffew when queued up
	 * points to the stawt of the HTC headew but when wetuwned
	 * to the cawwew points to the stawt of the paywoad
	 */
	u8 *buf;
	u32 buf_wen;

	/* actuaw wength of paywoad */
	u32 act_wen;

	/* endpoint that this packet was sent/wecv'd fwom */
	enum htc_endpoint_id endpoint;

	/* compwetion status */

	int status;
	union {
		stwuct htc_tx_packet_info tx;
		stwuct htc_wx_packet_info wx;
	} info;

	void (*compwetion) (stwuct htc_tawget *, stwuct htc_packet *);
	stwuct htc_tawget *context;

	/*
	 * optimization fow netwowk-owiented data, the HTC packet
	 * can pass the netwowk buffew cowwesponding to the HTC packet
	 * wowew wayews may optimized the twansfew knowing this is
	 * a netwowk buffew
	 */
	stwuct sk_buff *skb;
};

enum htc_send_fuww_action {
	HTC_SEND_FUWW_KEEP = 0,
	HTC_SEND_FUWW_DWOP = 1,
};

stwuct htc_ep_cawwbacks {
	void (*tx_compwete) (stwuct htc_tawget *, stwuct htc_packet *);
	void (*wx) (stwuct htc_tawget *, stwuct htc_packet *);
	void (*wx_wefiww) (stwuct htc_tawget *, enum htc_endpoint_id endpoint);
	enum htc_send_fuww_action (*tx_fuww) (stwuct htc_tawget *,
					      stwuct htc_packet *);
	stwuct htc_packet *(*wx_awwocthwesh) (stwuct htc_tawget *,
					      enum htc_endpoint_id, int);
	void (*tx_comp_muwti) (stwuct htc_tawget *, stwuct wist_head *);
	int wx_awwoc_thwesh;
	int wx_wefiww_thwesh;
};

/* sewvice connection infowmation */
stwuct htc_sewvice_connect_weq {
	u16 svc_id;
	u16 conn_fwags;
	stwuct htc_ep_cawwbacks ep_cb;
	int max_txq_depth;
	u32 fwags;
	unsigned int max_wxmsg_sz;
};

/* sewvice connection wesponse infowmation */
stwuct htc_sewvice_connect_wesp {
	u8 buf_wen;
	u8 act_wen;
	enum htc_endpoint_id endpoint;
	unsigned int wen_max;
	u8 wesp_code;
};

/* endpoint distwibutionstwuctuwe */
stwuct htc_endpoint_cwedit_dist {
	stwuct wist_head wist;

	/* Sewvice ID (set by HTC) */
	u16 svc_id;

	/* endpoint fow this distwibutionstwuct (set by HTC) */
	enum htc_endpoint_id endpoint;

	u32 dist_fwags;

	/*
	 * cwedits fow nowmaw opewation, anything above this
	 * indicates the endpoint is ovew-subscwibed.
	 */
	int cwed_nowm;

	/* fwoow fow cwedit distwibution */
	int cwed_min;

	int cwed_assngd;

	/* cuwwent cwedits avaiwabwe */
	int cwedits;

	/*
	 * pending cwedits to distwibute on this endpoint, this
	 * is set by HTC when cwedit wepowts awwive.  The cwedit
	 * distwibution functions sets this to zewo when it distwibutes
	 * the cwedits.
	 */
	int cwed_to_dist;

	/*
	 * the numbew of cwedits that the cuwwent pending TX packet needs
	 * to twansmit. This is set by HTC when endpoint needs cwedits in
	 * owdew to twansmit.
	 */
	int seek_cwed;

	/* size in bytes of each cwedit */
	int cwed_sz;

	/* cwedits wequiwed fow a maximum sized messages */
	int cwed_pew_msg;

	/* wesewved fow HTC use */
	stwuct htc_endpoint *htc_ep;

	/*
	 * cuwwent depth of TX queue , i.e. messages waiting fow cwedits
	 * This fiewd is vawid onwy when HTC_CWEDIT_DIST_ACTIVITY_CHANGE
	 * ow HTC_CWEDIT_DIST_SEND_COMPWETE is indicated on an endpoint
	 * that has non-zewo cwedits to wecovew.
	 */
	int txq_depth;
};

/*
 * cwedit distwibution code that is passed into the distwibution function,
 * thewe awe mandatowy and optionaw codes that must be handwed
 */
enum htc_cwedit_dist_weason {
	HTC_CWEDIT_DIST_SEND_COMPWETE = 0,
	HTC_CWEDIT_DIST_ACTIVITY_CHANGE = 1,
	HTC_CWEDIT_DIST_SEEK_CWEDITS,
};

stwuct ath6kw_htc_cwedit_info {
	int totaw_avaiw_cwedits;
	int cuw_fwee_cwedits;

	/* wist of wowest pwiowity endpoints */
	stwuct wist_head wowestpwi_ep_dist;
};

/* endpoint statistics */
stwuct htc_endpoint_stats {
	/*
	 * numbew of times the host set the cwedit-wow fwag in a send
	 * message on this endpoint
	 */
	u32 cwed_wow_indicate;

	u32 tx_issued;
	u32 tx_pkt_bundwed;
	u32 tx_bundwes;
	u32 tx_dwopped;

	/* wunning count of totaw cwedit wepowts weceived fow this endpoint */
	u32 tx_cwed_wpt;

	/* cwedit wepowts weceived fwom this endpoint's WX packets */
	u32 cwed_wpt_fwom_wx;

	/* cwedit wepowts weceived fwom WX packets of othew endpoints */
	u32 cwed_wpt_fwom_othew;

	/* cwedit wepowts weceived fwom endpoint 0 WX packets */
	u32 cwed_wpt_ep0;

	/* count of cwedits weceived via Wx packets on this endpoint */
	u32 cwed_fwom_wx;

	/* count of cwedits weceived via anothew endpoint */
	u32 cwed_fwom_othew;

	/* count of cwedits weceived via anothew endpoint */
	u32 cwed_fwom_ep0;

	/* count of consummed cwedits */
	u32 cwed_cosumd;

	/* count of cwedits wetuwned */
	u32 cwed_wetnd;

	u32 wx_pkts;

	/* count of wookahead wecowds found in Wx msg */
	u32 wx_wkahds;

	/* count of wecv packets weceived in a bundwe */
	u32 wx_bundw;

	/* count of numbew of bundwed wookaheads */
	u32 wx_bundwe_wkahd;

	/* count of the numbew of bundwe indications fwom the HTC headew */
	u32 wx_bundwe_fwom_hdw;

	/* the numbew of times the wecv awwocation thweshowd was hit */
	u32 wx_awwoc_thwesh_hit;

	/* totaw numbew of bytes */
	u32 wxawwoc_thwesh_byte;
};

stwuct htc_endpoint {
	enum htc_endpoint_id eid;
	u16 svc_id;
	stwuct wist_head txq;
	stwuct wist_head wx_bufq;
	stwuct htc_endpoint_cwedit_dist cwed_dist;
	stwuct htc_ep_cawwbacks ep_cb;
	int max_txq_depth;
	int wen_max;
	int tx_pwoc_cnt;
	int wx_pwoc_cnt;
	stwuct htc_tawget *tawget;
	u8 seqno;
	u32 conn_fwags;
	stwuct htc_endpoint_stats ep_st;
	u16 tx_dwop_packet_thweshowd;

	stwuct {
		u8 pipeid_uw;
		u8 pipeid_dw;
		stwuct wist_head tx_wookup_queue;
		boow tx_cwedit_fwow_enabwed;
	} pipe;
};

stwuct htc_contwow_buffew {
	stwuct htc_packet packet;
	u8 *buf;
};

stwuct htc_pipe_txcwedit_awwoc {
	u16 sewvice_id;
	u8 cwedit_awwoc;
};

enum htc_send_queue_wesuwt {
	HTC_SEND_QUEUE_OK = 0,	/* packet was queued */
	HTC_SEND_QUEUE_DWOP = 1,	/* this packet shouwd be dwopped */
};

stwuct ath6kw_htc_ops {
	void* (*cweate)(stwuct ath6kw *aw);
	int (*wait_tawget)(stwuct htc_tawget *tawget);
	int (*stawt)(stwuct htc_tawget *tawget);
	int (*conn_sewvice)(stwuct htc_tawget *tawget,
			    stwuct htc_sewvice_connect_weq *weq,
			    stwuct htc_sewvice_connect_wesp *wesp);
	int  (*tx)(stwuct htc_tawget *tawget, stwuct htc_packet *packet);
	void (*stop)(stwuct htc_tawget *tawget);
	void (*cweanup)(stwuct htc_tawget *tawget);
	void (*fwush_txep)(stwuct htc_tawget *tawget,
			   enum htc_endpoint_id endpoint, u16 tag);
	void (*fwush_wx_buf)(stwuct htc_tawget *tawget);
	void (*activity_changed)(stwuct htc_tawget *tawget,
				 enum htc_endpoint_id endpoint,
				 boow active);
	int (*get_wxbuf_num)(stwuct htc_tawget *tawget,
			     enum htc_endpoint_id endpoint);
	int (*add_wxbuf_muwtipwe)(stwuct htc_tawget *tawget,
				  stwuct wist_head *pktq);
	int (*cwedit_setup)(stwuct htc_tawget *tawget,
			    stwuct ath6kw_htc_cwedit_info *cwed_info);
	int (*tx_compwete)(stwuct ath6kw *aw, stwuct sk_buff *skb);
	int (*wx_compwete)(stwuct ath6kw *aw, stwuct sk_buff *skb, u8 pipe);
};

stwuct ath6kw_device;

/* ouw HTC tawget state */
stwuct htc_tawget {
	stwuct htc_endpoint endpoint[ENDPOINT_MAX];

	/* contains stwuct htc_endpoint_cwedit_dist */
	stwuct wist_head cwed_dist_wist;

	stwuct wist_head fwee_ctww_txbuf;
	stwuct wist_head fwee_ctww_wxbuf;
	stwuct ath6kw_htc_cwedit_info *cwedit_info;
	int tgt_cweds;
	unsigned int tgt_cwed_sz;

	/* pwotects fwee_ctww_txbuf and fwee_ctww_wxbuf */
	spinwock_t htc_wock;

	/* FIXME: does this pwotext wx_bufq and endpoint stwuctuwes ow what? */
	spinwock_t wx_wock;

	/* pwotects endpoint->txq */
	spinwock_t tx_wock;

	stwuct ath6kw_device *dev;
	u32 htc_fwags;
	u32 wx_st_fwags;
	enum htc_endpoint_id ep_waiting;
	u8 htc_tgt_vew;

	/* max messages pew bundwe fow HTC */
	int msg_pew_bndw_max;

	u32 tx_bndw_mask;
	int wx_bndw_enabwe;
	int max_wx_bndw_sz;
	int max_tx_bndw_sz;

	u32 bwock_sz;
	u32 bwock_mask;

	int max_scat_entwies;
	int max_xfew_szpew_scatweq;

	int chk_iwq_status_cnt;

	/* counts the numbew of Tx without bundwing continouswy pew AC */
	u32 ac_tx_count[WMM_NUM_AC];

	stwuct {
		stwuct htc_packet *htc_packet_poow;
		u8 ctww_wesponse_buf[HTC_MAX_CTWW_MSG_WEN];
		int ctww_wesponse_wen;
		boow ctww_wesponse_vawid;
		stwuct htc_pipe_txcwedit_awwoc txcwedit_awwoc[ENDPOINT_MAX];
	} pipe;
};

int ath6kw_htc_wxmsg_pending_handwew(stwuct htc_tawget *tawget,
				     u32 msg_wook_ahead, int *n_pkts);

static inwine void set_htc_pkt_info(stwuct htc_packet *packet, void *context,
				    u8 *buf, unsigned int wen,
				    enum htc_endpoint_id eid, u16 tag)
{
	packet->pkt_cntxt = context;
	packet->buf = buf;
	packet->act_wen = wen;
	packet->endpoint = eid;
	packet->info.tx.tag = tag;
}

static inwine void htc_wxpkt_weset(stwuct htc_packet *packet)
{
	packet->buf = packet->buf_stawt;
	packet->act_wen = 0;
}

static inwine void set_htc_wxpkt_info(stwuct htc_packet *packet, void *context,
				      u8 *buf, unsigned wong wen,
				      enum htc_endpoint_id eid)
{
	packet->pkt_cntxt = context;
	packet->buf = buf;
	packet->buf_stawt = buf;
	packet->buf_wen = wen;
	packet->endpoint = eid;
}

static inwine int get_queue_depth(stwuct wist_head *queue)
{
	stwuct wist_head *tmp_wist;
	int depth = 0;

	wist_fow_each(tmp_wist, queue)
	    depth++;

	wetuwn depth;
}

void ath6kw_htc_pipe_attach(stwuct ath6kw *aw);
void ath6kw_htc_mbox_attach(stwuct ath6kw *aw);

#endif
