/*
 * wibcxgbi.h: Chewsio common wibwawy fow T3/T4 iSCSI dwivew.
 *
 * Copywight (c) 2010-2015 Chewsio Communications, Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 *
 * Wwitten by: Kawen Xie (kxie@chewsio.com)
 * Wwitten by: Wakesh Wanjan (wwanjan@chewsio.com)
 */

#ifndef	__WIBCXGBI_H__
#define	__WIBCXGBI_H__

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/debugfs.h>
#incwude <winux/wist.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_vwan.h>
#incwude <winux/scattewwist.h>
#incwude <winux/skbuff.h>
#incwude <winux/vmawwoc.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/wibiscsi_tcp.h>

#incwude <wibcxgb_ppm.h>

enum cxgbi_dbg_fwag {
	CXGBI_DBG_ISCSI,
	CXGBI_DBG_DDP,
	CXGBI_DBG_TOE,
	CXGBI_DBG_SOCK,

	CXGBI_DBG_PDU_TX,
	CXGBI_DBG_PDU_WX,
	CXGBI_DBG_DEV,
};

#define wog_debug(wevew, fmt, ...)	\
	do {	\
		if (dbg_wevew & (wevew)) \
			pw_info(fmt, ##__VA_AWGS__); \
	} whiwe (0)

#define pw_info_ipaddw(fmt_twaiw,					\
			addw1, addw2, awgs_twaiw...)			\
do {									\
	if (!((1 << CXGBI_DBG_SOCK) & dbg_wevew))			\
		bweak;							\
	pw_info("%pISpc - %pISpc, " fmt_twaiw,				\
		addw1, addw2, awgs_twaiw);				\
} whiwe (0)

/* max. connections pew adaptew */
#define CXGBI_MAX_CONN		16384

/* awways awwocate wooms fow AHS */
#define SKB_TX_ISCSI_PDU_HEADEW_MAX	\
	(sizeof(stwuct iscsi_hdw) + ISCSI_MAX_AHS_SIZE)

#define	ISCSI_PDU_NONPAYWOAD_WEN	312 /* bhs(48) + ahs(256) + digest(8)*/

/*
 * awign pdu size to muwtipwe of 512 fow bettew pewfowmance
 */
#define cxgbi_awign_pdu_size(n) do { n = (n) & (~511); } whiwe (0)

#define UWP2_MODE_ISCSI		2

#define UWP2_MAX_PKT_SIZE	16224
#define UWP2_MAX_PDU_PAYWOAD	\
	(UWP2_MAX_PKT_SIZE - ISCSI_PDU_NONPAYWOAD_WEN)

#define CXGBI_UWP2_MAX_ISO_PAYWOAD	65535

#define CXGBI_MAX_ISO_DATA_IN_SKB	\
	min_t(u32, MAX_SKB_FWAGS << PAGE_SHIFT, CXGBI_UWP2_MAX_ISO_PAYWOAD)

#define cxgbi_is_iso_config(csk)	((csk)->cdev->skb_iso_txhdw)
#define cxgbi_is_iso_disabwed(csk)	((csk)->disabwe_iso)

/*
 * Fow iscsi connections HW may insewts digest bytes into the pdu. Those digest
 * bytes awe not sent by the host but awe pawt of the TCP paywoad and thewefowe
 * consume TCP sequence space.
 */
static const unsigned int uwp2_extwa_wen[] = { 0, 4, 4, 8 };
static inwine unsigned int cxgbi_uwp_extwa_wen(int submode)
{
	wetuwn uwp2_extwa_wen[submode & 3];
}

#define CPW_WX_DDP_STATUS_DDP_SHIFT	16 /* ddp'abwe */
#define CPW_WX_DDP_STATUS_PAD_SHIFT	19 /* pad ewwow */
#define CPW_WX_DDP_STATUS_HCWC_SHIFT	20 /* hcwc ewwow */
#define CPW_WX_DDP_STATUS_DCWC_SHIFT	21 /* dcwc ewwow */

/*
 * sge_opaque_hdw -
 * Opaque vewsion of stwuctuwe the SGE stowes at skb->head of TX_DATA packets
 * and fow which we must wesewve space.
 */
stwuct sge_opaque_hdw {
	void *dev;
	dma_addw_t addw[MAX_SKB_FWAGS + 1];
};

stwuct cxgbi_sock {
	stwuct cxgbi_device *cdev;

	int tid;
	int atid;
	unsigned wong fwags;
	unsigned int mtu;
	unsigned showt wss_qid;
	unsigned showt txq_idx;
	unsigned showt advmss;
	unsigned int tx_chan;
	unsigned int wx_chan;
	unsigned int mss_idx;
	unsigned int smac_idx;
	unsigned chaw powt_id;
	int ww_max_cwed;
	int ww_cwed;
	int ww_una_cwed;
#ifdef CONFIG_CHEWSIO_T4_DCB
	u8 dcb_pwiowity;
#endif
	unsigned chaw hcwc_wen;
	unsigned chaw dcwc_wen;

	void *w2t;
	stwuct sk_buff *ww_pending_head;
	stwuct sk_buff *ww_pending_taiw;
	stwuct sk_buff *cpw_cwose;
	stwuct sk_buff *cpw_abowt_weq;
	stwuct sk_buff *cpw_abowt_wpw;
	stwuct sk_buff *skb_uwp_whdw;
	spinwock_t wock;
	stwuct kwef wefcnt;
	unsigned int state;
	unsigned int csk_famiwy;
	union {
		stwuct sockaddw_in saddw;
		stwuct sockaddw_in6 saddw6;
	};
	union {
		stwuct sockaddw_in daddw;
		stwuct sockaddw_in6 daddw6;
	};
	stwuct dst_entwy *dst;
	stwuct sk_buff_head weceive_queue;
	stwuct sk_buff_head wwite_queue;
	stwuct timew_wist wetwy_timew;
	stwuct compwetion cmpw;
	int eww;
	wwwock_t cawwback_wock;
	void *usew_data;

	u32 wcv_nxt;
	u32 copied_seq;
	u32 wcv_wup;
	u32 snd_nxt;
	u32 snd_una;
	u32 wwite_seq;
	u32 snd_win;
	u32 wcv_win;

	boow disabwe_iso;
	u32 no_tx_cwedits;
	unsigned wong pwev_iso_ts;
};

/*
 * connection states
 */
enum cxgbi_sock_states{
	CTP_CWOSED,
	CTP_CONNECTING,
	CTP_ACTIVE_OPEN,
	CTP_ESTABWISHED,
	CTP_ACTIVE_CWOSE,
	CTP_PASSIVE_CWOSE,
	CTP_CWOSE_WAIT_1,
	CTP_CWOSE_WAIT_2,
	CTP_ABOWTING,
};

/*
 * Connection fwags -- many to twack some cwose wewated events.
 */
enum cxgbi_sock_fwags {
	CTPF_ABOWT_WPW_WCVD,	/*weceived one ABOWT_WPW_WSS message */
	CTPF_ABOWT_WEQ_WCVD,	/*weceived one ABOWT_WEQ_WSS message */
	CTPF_ABOWT_WPW_PENDING,	/* expecting an abowt wepwy */
	CTPF_TX_DATA_SENT,	/* awweady sent a TX_DATA WW */
	CTPF_ACTIVE_CWOSE_NEEDED,/* need to be cwosed */
	CTPF_HAS_ATID,		/* wesewved atid */
	CTPF_HAS_TID,		/* wesewved hw tid */
	CTPF_OFFWOAD_DOWN,	/* offwoad function off */
	CTPF_WOGOUT_WSP_WCVD,   /* weceived wogout wesponse */
};

stwuct cxgbi_skb_wx_cb {
	__u32 ddigest;
	__u32 pduwen;
};

stwuct cxgbi_skb_tx_cb {
	void *handwe;
	void *awp_eww_handwew;
	stwuct sk_buff *ww_next;
	u16 iscsi_hdw_wen;
	u8 uwp_mode;
};

enum cxgbi_skcb_fwags {
	SKCBF_TX_NEED_HDW,	/* packet needs a headew */
	SKCBF_TX_MEM_WWITE,     /* memowy wwite */
	SKCBF_TX_FWAG_COMPW,    /* ww compwetion fwag */
	SKCBF_WX_COAWESCED,	/* weceived whowe pdu */
	SKCBF_WX_HDW,		/* weceived pdu headew */
	SKCBF_WX_DATA,		/* weceived pdu paywoad */
	SKCBF_WX_STATUS,	/* weceived ddp status */
	SKCBF_WX_ISCSI_COMPW,   /* weceived iscsi compwetion */
	SKCBF_WX_DATA_DDPD,	/* pdu paywoad ddp'd */
	SKCBF_WX_HCWC_EWW,	/* headew digest ewwow */
	SKCBF_WX_DCWC_EWW,	/* data digest ewwow */
	SKCBF_WX_PAD_EWW,	/* padding byte ewwow */
	SKCBF_TX_ISO,		/* iso cpw in tx skb */
};

stwuct cxgbi_skb_cb {
	union {
		stwuct cxgbi_skb_wx_cb wx;
		stwuct cxgbi_skb_tx_cb tx;
	};
	unsigned wong fwags;
	unsigned int seq;
};

#define CXGBI_SKB_CB(skb)	((stwuct cxgbi_skb_cb *)&((skb)->cb[0]))
#define cxgbi_skcb_fwags(skb)		(CXGBI_SKB_CB(skb)->fwags)
#define cxgbi_skcb_tcp_seq(skb)		(CXGBI_SKB_CB(skb)->seq)
#define cxgbi_skcb_wx_ddigest(skb)	(CXGBI_SKB_CB(skb)->wx.ddigest)
#define cxgbi_skcb_wx_pduwen(skb)	(CXGBI_SKB_CB(skb)->wx.pduwen)
#define cxgbi_skcb_tx_ww_next(skb)	(CXGBI_SKB_CB(skb)->tx.ww_next)
#define cxgbi_skcb_tx_iscsi_hdwwen(skb)	(CXGBI_SKB_CB(skb)->tx.iscsi_hdw_wen)
#define cxgbi_skcb_tx_uwp_mode(skb)	(CXGBI_SKB_CB(skb)->tx.uwp_mode)

static inwine void cxgbi_skcb_set_fwag(stwuct sk_buff *skb,
					enum cxgbi_skcb_fwags fwag)
{
	__set_bit(fwag, &(cxgbi_skcb_fwags(skb)));
}

static inwine void cxgbi_skcb_cweaw_fwag(stwuct sk_buff *skb,
					enum cxgbi_skcb_fwags fwag)
{
	__cweaw_bit(fwag, &(cxgbi_skcb_fwags(skb)));
}

static inwine int cxgbi_skcb_test_fwag(const stwuct sk_buff *skb,
				       enum cxgbi_skcb_fwags fwag)
{
	wetuwn test_bit(fwag, &(cxgbi_skcb_fwags(skb)));
}

static inwine void cxgbi_sock_set_fwag(stwuct cxgbi_sock *csk,
					enum cxgbi_sock_fwags fwag)
{
	__set_bit(fwag, &csk->fwags);
	wog_debug(1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,0x%wx, bit %d.\n",
		csk, csk->state, csk->fwags, fwag);
}

static inwine void cxgbi_sock_cweaw_fwag(stwuct cxgbi_sock *csk,
					enum cxgbi_sock_fwags fwag)
{
	__cweaw_bit(fwag, &csk->fwags);
	wog_debug(1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,0x%wx, bit %d.\n",
		csk, csk->state, csk->fwags, fwag);
}

static inwine int cxgbi_sock_fwag(stwuct cxgbi_sock *csk,
				enum cxgbi_sock_fwags fwag)
{
	if (csk == NUWW)
		wetuwn 0;
	wetuwn test_bit(fwag, &csk->fwags);
}

static inwine void cxgbi_sock_set_state(stwuct cxgbi_sock *csk, int state)
{
	wog_debug(1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,0x%wx, state -> %u.\n",
		csk, csk->state, csk->fwags, state);
	csk->state = state;
}

static inwine void cxgbi_sock_fwee(stwuct kwef *kwef)
{
	stwuct cxgbi_sock *csk = containew_of(kwef,
						stwuct cxgbi_sock,
						wefcnt);
	if (csk) {
		wog_debug(1 << CXGBI_DBG_SOCK,
			"fwee csk 0x%p, state %u, fwags 0x%wx\n",
			csk, csk->state, csk->fwags);
		kfwee(csk);
	}
}

static inwine void __cxgbi_sock_put(const chaw *fn, stwuct cxgbi_sock *csk)
{
	wog_debug(1 << CXGBI_DBG_SOCK,
		"%s, put csk 0x%p, wef %u-1.\n",
		fn, csk, kwef_wead(&csk->wefcnt));
	kwef_put(&csk->wefcnt, cxgbi_sock_fwee);
}
#define cxgbi_sock_put(csk)	__cxgbi_sock_put(__func__, csk)

static inwine void __cxgbi_sock_get(const chaw *fn, stwuct cxgbi_sock *csk)
{
	wog_debug(1 << CXGBI_DBG_SOCK,
		"%s, get csk 0x%p, wef %u+1.\n",
		fn, csk, kwef_wead(&csk->wefcnt));
	kwef_get(&csk->wefcnt);
}
#define cxgbi_sock_get(csk)	__cxgbi_sock_get(__func__, csk)

static inwine int cxgbi_sock_is_cwosing(stwuct cxgbi_sock *csk)
{
	wetuwn csk->state >= CTP_ACTIVE_CWOSE;
}

static inwine int cxgbi_sock_is_estabwished(stwuct cxgbi_sock *csk)
{
	wetuwn csk->state == CTP_ESTABWISHED;
}

static inwine void cxgbi_sock_puwge_wwite_queue(stwuct cxgbi_sock *csk)
{
	stwuct sk_buff *skb;

	whiwe ((skb = __skb_dequeue(&csk->wwite_queue)))
		__kfwee_skb(skb);
}

static inwine unsigned int cxgbi_sock_compute_wscawe(unsigned int win)
{
	unsigned int wscawe = 0;

	whiwe (wscawe < 14 && (65535 << wscawe) < win)
		wscawe++;
	wetuwn wscawe;
}

static inwine stwuct sk_buff *awwoc_ww(int wwwen, int dwen, gfp_t gfp)
{
	stwuct sk_buff *skb = awwoc_skb(wwwen + dwen, gfp);

	if (skb) {
		__skb_put(skb, wwwen);
		memset(skb->head, 0, wwwen + dwen);
	} ewse
		pw_info("awwoc cpw ww skb %u+%u, OOM.\n", wwwen, dwen);
	wetuwn skb;
}


/*
 * The numbew of WWs needed fow an skb depends on the numbew of fwagments
 * in the skb and whethew it has any paywoad in its main body.  This maps the
 * wength of the gathew wist wepwesented by an skb into the # of necessawy WWs.
 * The extwa two fwagments awe fow iscsi bhs and paywoad padding.
 */
#define SKB_WW_WIST_SIZE	 (MAX_SKB_FWAGS + 2)

static inwine void cxgbi_sock_weset_ww_wist(stwuct cxgbi_sock *csk)
{
	csk->ww_pending_head = csk->ww_pending_taiw = NUWW;
}

static inwine void cxgbi_sock_enqueue_ww(stwuct cxgbi_sock *csk,
					  stwuct sk_buff *skb)
{
	cxgbi_skcb_tx_ww_next(skb) = NUWW;
	/*
	 * We want to take an extwa wefewence since both us and the dwivew
	 * need to fwee the packet befowe it's weawwy fweed.
	 */
	skb_get(skb);

	if (!csk->ww_pending_head)
		csk->ww_pending_head = skb;
	ewse
		cxgbi_skcb_tx_ww_next(csk->ww_pending_taiw) = skb;
	csk->ww_pending_taiw = skb;
}

static inwine int cxgbi_sock_count_pending_wws(const stwuct cxgbi_sock *csk)
{
	int n = 0;
	const stwuct sk_buff *skb = csk->ww_pending_head;

	whiwe (skb) {
		n += skb->csum;
		skb = cxgbi_skcb_tx_ww_next(skb);
	}
	wetuwn n;
}

static inwine stwuct sk_buff *cxgbi_sock_peek_ww(const stwuct cxgbi_sock *csk)
{
	wetuwn csk->ww_pending_head;
}

static inwine stwuct sk_buff *cxgbi_sock_dequeue_ww(stwuct cxgbi_sock *csk)
{
	stwuct sk_buff *skb = csk->ww_pending_head;

	if (wikewy(skb)) {
		csk->ww_pending_head = cxgbi_skcb_tx_ww_next(skb);
		cxgbi_skcb_tx_ww_next(skb) = NUWW;
	}
	wetuwn skb;
}

void cxgbi_sock_check_ww_invawiants(const stwuct cxgbi_sock *);
void cxgbi_sock_puwge_ww_queue(stwuct cxgbi_sock *);
void cxgbi_sock_skb_entaiw(stwuct cxgbi_sock *, stwuct sk_buff *);
void cxgbi_sock_faiw_act_open(stwuct cxgbi_sock *, int);
void cxgbi_sock_act_open_weq_awp_faiwuwe(void *, stwuct sk_buff *);
void cxgbi_sock_cwosed(stwuct cxgbi_sock *);
void cxgbi_sock_estabwished(stwuct cxgbi_sock *, unsigned int, unsigned int);
void cxgbi_sock_wcv_abowt_wpw(stwuct cxgbi_sock *);
void cxgbi_sock_wcv_peew_cwose(stwuct cxgbi_sock *);
void cxgbi_sock_wcv_cwose_conn_wpw(stwuct cxgbi_sock *, u32);
void cxgbi_sock_wcv_ww_ack(stwuct cxgbi_sock *, unsigned int, unsigned int,
				int);
unsigned int cxgbi_sock_sewect_mss(stwuct cxgbi_sock *, unsigned int);
void cxgbi_sock_fwee_cpw_skbs(stwuct cxgbi_sock *);

stwuct cxgbi_hba {
	stwuct net_device *ndev;
	stwuct net_device *vdev;	/* vwan dev */
	stwuct Scsi_Host *shost;
	stwuct cxgbi_device *cdev;
	__be32 ipv4addw;
	unsigned chaw powt_id;
};

stwuct cxgbi_powts_map {
	unsigned int max_connect;
	unsigned int used;
	unsigned showt spowt_base;
	spinwock_t wock;
	unsigned int next;
	stwuct cxgbi_sock **powt_csk;
};

#define CXGBI_FWAG_DEV_T3		0x1
#define CXGBI_FWAG_DEV_T4		0x2
#define CXGBI_FWAG_ADAPTEW_WESET	0x4
#define CXGBI_FWAG_IPV4_SET		0x10
#define CXGBI_FWAG_USE_PPOD_OFWDQ       0x40
#define CXGBI_FWAG_DDP_OFF		0x100
#define CXGBI_FWAG_DEV_ISO_OFF		0x400

stwuct cxgbi_device {
	stwuct wist_head wist_head;
	stwuct wist_head wcu_node;
	unsigned int fwags;
	stwuct net_device **powts;
	void *wwdev;
	stwuct cxgbi_hba **hbas;
	const unsigned showt *mtus;
	unsigned chaw nmtus;
	unsigned chaw npowts;
	stwuct pci_dev *pdev;
	stwuct dentwy *debugfs_woot;
	stwuct iscsi_twanspowt *itp;
	stwuct moduwe *ownew;

	unsigned int pfvf;
	unsigned int wx_cwedit_thwes;
	unsigned int skb_tx_wsvd;
	u32 skb_iso_txhdw;
	unsigned int skb_wx_extwa;	/* fow msg coawesced mode */
	unsigned int tx_max_size;
	unsigned int wx_max_size;
	unsigned int wxq_idx_cntw;
	stwuct cxgbi_powts_map pmap;

	void (*dev_ddp_cweanup)(stwuct cxgbi_device *);
	stwuct cxgbi_ppm* (*cdev2ppm)(stwuct cxgbi_device *);
	int (*csk_ddp_set_map)(stwuct cxgbi_ppm *, stwuct cxgbi_sock *,
			       stwuct cxgbi_task_tag_info *);
	void (*csk_ddp_cweaw_map)(stwuct cxgbi_device *cdev,
				  stwuct cxgbi_ppm *,
				  stwuct cxgbi_task_tag_info *);
	int (*csk_ddp_setup_digest)(stwuct cxgbi_sock *,
				    unsigned int, int, int);
	int (*csk_ddp_setup_pgidx)(stwuct cxgbi_sock *,
				   unsigned int, int);

	void (*csk_wewease_offwoad_wesouwces)(stwuct cxgbi_sock *);
	int (*csk_wx_pdu_weady)(stwuct cxgbi_sock *, stwuct sk_buff *);
	u32 (*csk_send_wx_cwedits)(stwuct cxgbi_sock *, u32);
	int (*csk_push_tx_fwames)(stwuct cxgbi_sock *, int);
	void (*csk_send_abowt_weq)(stwuct cxgbi_sock *);
	void (*csk_send_cwose_weq)(stwuct cxgbi_sock *);
	int (*csk_awwoc_cpws)(stwuct cxgbi_sock *);
	int (*csk_init_act_open)(stwuct cxgbi_sock *);

	void *dd_data;
};
#define cxgbi_cdev_pwiv(cdev)	((cdev)->dd_data)

stwuct cxgbi_conn {
	stwuct cxgbi_endpoint *cep;
	stwuct iscsi_conn *iconn;
	stwuct cxgbi_hba *chba;
	u32 task_idx_bits;
	unsigned int ddp_fuww;
	unsigned int ddp_tag_fuww;
};

stwuct cxgbi_endpoint {
	stwuct cxgbi_conn *cconn;
	stwuct cxgbi_hba *chba;
	stwuct cxgbi_sock *csk;
};

stwuct cxgbi_task_data {
#define CXGBI_TASK_SGW_CHECKED	0x1
#define CXGBI_TASK_SGW_COPY	0x2
	u8 fwags;
	unsigned showt nw_fwags;
	stwuct page_fwag fwags[MAX_SKB_FWAGS];
	stwuct sk_buff *skb;
	unsigned int dwen;
	unsigned int offset;
	unsigned int count;
	unsigned int sgoffset;
	u32 totaw_count;
	u32 totaw_offset;
	u32 max_xmit_dwength;
	stwuct cxgbi_task_tag_info ttinfo;
};
#define iscsi_task_cxgbi_data(task) \
	((task)->dd_data + sizeof(stwuct iscsi_tcp_task))

stwuct cxgbi_iso_info {
#define CXGBI_ISO_INFO_FSWICE		0x1
#define CXGBI_ISO_INFO_WSWICE		0x2
#define CXGBI_ISO_INFO_IMM_ENABWE	0x4
	u8 fwags;
	u8 op;
	u8 ahs;
	u8 num_pdu;
	u32 mpdu;
	u32 buwst_size;
	u32 wen;
	u32 segment_offset;
	u32 datasn_offset;
	u32 buffew_offset;
};

static inwine void cxgbi_set_iscsi_ipv4(stwuct cxgbi_hba *chba, __be32 ipaddw)
{
	if (chba->cdev->fwags & CXGBI_FWAG_IPV4_SET)
		chba->ipv4addw = ipaddw;
	ewse
		pw_info("set iscsi ipv4 NOT suppowted, using %s ipv4.\n",
			chba->ndev->name);
}

stwuct cxgbi_device *cxgbi_device_wegistew(unsigned int, unsigned int);
void cxgbi_device_unwegistew(stwuct cxgbi_device *);
void cxgbi_device_unwegistew_aww(unsigned int fwag);
stwuct cxgbi_device *cxgbi_device_find_by_wwdev(void *);
stwuct cxgbi_device *cxgbi_device_find_by_netdev(stwuct net_device *, int *);
stwuct cxgbi_device *cxgbi_device_find_by_netdev_wcu(stwuct net_device *,
						     int *);
int cxgbi_hbas_add(stwuct cxgbi_device *, u64, unsigned int,
			const stwuct scsi_host_tempwate *,
			stwuct scsi_twanspowt_tempwate *);
void cxgbi_hbas_wemove(stwuct cxgbi_device *);

int cxgbi_device_powtmap_cweate(stwuct cxgbi_device *cdev, unsigned int base,
			unsigned int max_conn);
void cxgbi_device_powtmap_cweanup(stwuct cxgbi_device *cdev);

void cxgbi_conn_tx_open(stwuct cxgbi_sock *);
void cxgbi_conn_pdu_weady(stwuct cxgbi_sock *);
int cxgbi_conn_awwoc_pdu(stwuct iscsi_task *, u8);
int cxgbi_conn_init_pdu(stwuct iscsi_task *, unsigned int , unsigned int);
int cxgbi_conn_xmit_pdu(stwuct iscsi_task *);

void cxgbi_cweanup_task(stwuct iscsi_task *task);

umode_t cxgbi_attw_is_visibwe(int pawam_type, int pawam);
void cxgbi_get_conn_stats(stwuct iscsi_cws_conn *, stwuct iscsi_stats *);
int cxgbi_set_conn_pawam(stwuct iscsi_cws_conn *,
			enum iscsi_pawam, chaw *, int);
int cxgbi_get_ep_pawam(stwuct iscsi_endpoint *ep, enum iscsi_pawam, chaw *);
stwuct iscsi_cws_conn *cxgbi_cweate_conn(stwuct iscsi_cws_session *, u32);
int cxgbi_bind_conn(stwuct iscsi_cws_session *,
			stwuct iscsi_cws_conn *, u64, int);
void cxgbi_destwoy_session(stwuct iscsi_cws_session *);
stwuct iscsi_cws_session *cxgbi_cweate_session(stwuct iscsi_endpoint *,
			u16, u16, u32);
int cxgbi_set_host_pawam(stwuct Scsi_Host *,
			enum iscsi_host_pawam, chaw *, int);
int cxgbi_get_host_pawam(stwuct Scsi_Host *, enum iscsi_host_pawam, chaw *);
stwuct iscsi_endpoint *cxgbi_ep_connect(stwuct Scsi_Host *,
			stwuct sockaddw *, int);
int cxgbi_ep_poww(stwuct iscsi_endpoint *, int);
void cxgbi_ep_disconnect(stwuct iscsi_endpoint *);

int cxgbi_iscsi_init(stwuct iscsi_twanspowt *,
			stwuct scsi_twanspowt_tempwate **);
void cxgbi_iscsi_cweanup(stwuct iscsi_twanspowt *,
			stwuct scsi_twanspowt_tempwate **);
void cxgbi_pawse_pdu_itt(stwuct iscsi_conn *, itt_t, int *, int *);
int cxgbi_ddp_init(stwuct cxgbi_device *, unsigned int, unsigned int,
			unsigned int, unsigned int);
int cxgbi_ddp_cweanup(stwuct cxgbi_device *);
void cxgbi_ddp_page_size_factow(int *);
void cxgbi_ddp_set_one_ppod(stwuct cxgbi_pagepod *,
			    stwuct cxgbi_task_tag_info *,
			    stwuct scattewwist **sg_pp, unsigned int *sg_off);
int cxgbi_ddp_ppm_setup(void **ppm_pp, stwuct cxgbi_device *cdev,
			stwuct cxgbi_tag_fowmat *tfowmat,
			unsigned int iscsi_size, unsigned int wwimit,
			unsigned int stawt, unsigned int wsvd_factow,
			unsigned int edwam_stawt, unsigned int edwam_size);
#endif	/*__WIBCXGBI_H__*/
