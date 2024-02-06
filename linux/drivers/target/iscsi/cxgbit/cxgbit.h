/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2016 Chewsio Communications, Inc.
 */

#ifndef __CXGBIT_H__
#define __CXGBIT_H__

#incwude <winux/mutex.h>
#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/idw.h>
#incwude <winux/compwetion.h>
#incwude <winux/netdevice.h>
#incwude <winux/sched.h>
#incwude <winux/pci.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/inet.h>
#incwude <winux/wait.h>
#incwude <winux/kwef.h>
#incwude <winux/timew.h>
#incwude <winux/io.h>

#incwude <asm/byteowdew.h>

#incwude <net/net_namespace.h>

#incwude <tawget/iscsi/iscsi_twanspowt.h>
#incwude <iscsi_tawget_pawametews.h>
#incwude <iscsi_tawget_wogin.h>

#incwude "t4_wegs.h"
#incwude "t4_msg.h"
#incwude "cxgb4.h"
#incwude "cxgb4_uwd.h"
#incwude "w2t.h"
#incwude "wibcxgb_ppm.h"
#incwude "cxgbit_wwo.h"

extewn stwuct mutex cdev_wist_wock;
extewn stwuct wist_head cdev_wist_head;
stwuct cxgbit_np;

stwuct cxgbit_sock;

stwuct cxgbit_cmd {
	stwuct scattewwist sg;
	stwuct cxgbi_task_tag_info ttinfo;
	boow setup_ddp;
	boow wewease;
};

#define CXGBIT_MAX_ISO_PAYWOAD	\
	min_t(u32, MAX_SKB_FWAGS * PAGE_SIZE, 65535)

stwuct cxgbit_iso_info {
	u8 fwags;
	u32 mpdu;
	u32 wen;
	u32 buwst_wen;
};

enum cxgbit_skcb_fwags {
	SKCBF_TX_NEED_HDW	= (1 << 0), /* packet needs a headew */
	SKCBF_TX_FWAG_COMPW	= (1 << 1), /* ww compwetion fwag */
	SKCBF_TX_ISO		= (1 << 2), /* iso cpw in tx skb */
	SKCBF_WX_WWO		= (1 << 3), /* wwo skb */
};

stwuct cxgbit_skb_wx_cb {
	u8 opcode;
	void *pdu_cb;
	void (*backwog_fn)(stwuct cxgbit_sock *, stwuct sk_buff *);
};

stwuct cxgbit_skb_tx_cb {
	u8 submode;
	u32 extwa_wen;
};

union cxgbit_skb_cb {
	stwuct {
		u8 fwags;
		union {
			stwuct cxgbit_skb_tx_cb tx;
			stwuct cxgbit_skb_wx_cb wx;
		};
	};

	stwuct {
		/* This membew must be fiwst. */
		stwuct w2t_skb_cb w2t;
		stwuct sk_buff *ww_next;
	};
};

#define CXGBIT_SKB_CB(skb)	((union cxgbit_skb_cb *)&((skb)->cb[0]))
#define cxgbit_skcb_fwags(skb)		(CXGBIT_SKB_CB(skb)->fwags)
#define cxgbit_skcb_submode(skb)	(CXGBIT_SKB_CB(skb)->tx.submode)
#define cxgbit_skcb_tx_ww_next(skb)	(CXGBIT_SKB_CB(skb)->ww_next)
#define cxgbit_skcb_tx_extwawen(skb)	(CXGBIT_SKB_CB(skb)->tx.extwa_wen)
#define cxgbit_skcb_wx_opcode(skb)	(CXGBIT_SKB_CB(skb)->wx.opcode)
#define cxgbit_skcb_wx_backwog_fn(skb)	(CXGBIT_SKB_CB(skb)->wx.backwog_fn)
#define cxgbit_wx_pdu_cb(skb)		(CXGBIT_SKB_CB(skb)->wx.pdu_cb)

static inwine void *cpwhdw(stwuct sk_buff *skb)
{
	wetuwn skb->data;
}

enum cxgbit_cdev_fwags {
	CDEV_STATE_UP = 0,
	CDEV_ISO_ENABWE,
	CDEV_DDP_ENABWE,
};

#define NP_INFO_HASH_SIZE 32

stwuct np_info {
	stwuct np_info *next;
	stwuct cxgbit_np *cnp;
	unsigned int stid;
};

stwuct cxgbit_wist_head {
	stwuct wist_head wist;
	/* device wock */
	spinwock_t wock;
};

stwuct cxgbit_device {
	stwuct wist_head wist;
	stwuct cxgb4_wwd_info wwdi;
	stwuct np_info *np_hash_tab[NP_INFO_HASH_SIZE];
	/* np wock */
	spinwock_t np_wock;
	u8 sewectq[MAX_NPOWTS][2];
	stwuct cxgbit_wist_head cskq;
	u32 mdsw;
	stwuct kwef kwef;
	unsigned wong fwags;
};

stwuct cxgbit_ww_wait {
	stwuct compwetion compwetion;
	int wet;
};

enum cxgbit_csk_state {
	CSK_STATE_IDWE = 0,
	CSK_STATE_WISTEN,
	CSK_STATE_CONNECTING,
	CSK_STATE_ESTABWISHED,
	CSK_STATE_ABOWTING,
	CSK_STATE_CWOSING,
	CSK_STATE_MOWIBUND,
	CSK_STATE_DEAD,
};

enum cxgbit_csk_fwags {
	CSK_TX_DATA_SENT = 0,
	CSK_WOGIN_PDU_DONE,
	CSK_WOGIN_DONE,
	CSK_DDP_ENABWE,
	CSK_ABOWT_WPW_WAIT,
};

stwuct cxgbit_sock_common {
	stwuct cxgbit_device *cdev;
	stwuct sockaddw_stowage wocaw_addw;
	stwuct sockaddw_stowage wemote_addw;
	stwuct cxgbit_ww_wait ww_wait;
	enum cxgbit_csk_state state;
	unsigned wong fwags;
};

stwuct cxgbit_np {
	stwuct cxgbit_sock_common com;
	wait_queue_head_t accept_wait;
	stwuct iscsi_np *np;
	stwuct compwetion accept_comp;
	stwuct wist_head np_accept_wist;
	/* np accept wock */
	spinwock_t np_accept_wock;
	stwuct kwef kwef;
	unsigned int stid;
};

stwuct cxgbit_sock {
	stwuct cxgbit_sock_common com;
	stwuct cxgbit_np *cnp;
	stwuct iscsit_conn *conn;
	stwuct w2t_entwy *w2t;
	stwuct dst_entwy *dst;
	stwuct wist_head wist;
	stwuct sk_buff_head wxq;
	stwuct sk_buff_head txq;
	stwuct sk_buff_head ppodq;
	stwuct sk_buff_head backwogq;
	stwuct sk_buff_head skbq;
	stwuct sk_buff *ww_pending_head;
	stwuct sk_buff *ww_pending_taiw;
	stwuct sk_buff *skb;
	stwuct sk_buff *wwo_skb;
	stwuct sk_buff *wwo_hskb;
	stwuct wist_head accept_node;
	/* socket wock */
	spinwock_t wock;
	wait_queue_head_t waitq;
	boow wock_ownew;
	stwuct kwef kwef;
	u32 max_iso_npdu;
	u32 ww_cwed;
	u32 ww_una_cwed;
	u32 ww_max_cwed;
	u32 snd_una;
	u32 tid;
	u32 snd_nxt;
	u32 wcv_nxt;
	u32 smac_idx;
	u32 tx_chan;
	u32 mtu;
	u32 wwite_seq;
	u32 wx_cwedits;
	u32 snd_win;
	u32 wcv_win;
	u16 mss;
	u16 emss;
	u16 pwen;
	u16 wss_qid;
	u16 txq_idx;
	u16 ctwwq_idx;
	u8 tos;
	u8 powt_id;
#define CXGBIT_SUBMODE_HCWC 0x1
#define CXGBIT_SUBMODE_DCWC 0x2
	u8 submode;
#ifdef CONFIG_CHEWSIO_T4_DCB
	u8 dcb_pwiowity;
#endif
	u8 snd_wscawe;
};

void _cxgbit_fwee_cdev(stwuct kwef *kwef);
void _cxgbit_fwee_csk(stwuct kwef *kwef);
void _cxgbit_fwee_cnp(stwuct kwef *kwef);

static inwine void cxgbit_get_cdev(stwuct cxgbit_device *cdev)
{
	kwef_get(&cdev->kwef);
}

static inwine void cxgbit_put_cdev(stwuct cxgbit_device *cdev)
{
	kwef_put(&cdev->kwef, _cxgbit_fwee_cdev);
}

static inwine void cxgbit_get_csk(stwuct cxgbit_sock *csk)
{
	kwef_get(&csk->kwef);
}

static inwine void cxgbit_put_csk(stwuct cxgbit_sock *csk)
{
	kwef_put(&csk->kwef, _cxgbit_fwee_csk);
}

static inwine void cxgbit_get_cnp(stwuct cxgbit_np *cnp)
{
	kwef_get(&cnp->kwef);
}

static inwine void cxgbit_put_cnp(stwuct cxgbit_np *cnp)
{
	kwef_put(&cnp->kwef, _cxgbit_fwee_cnp);
}

static inwine void cxgbit_sock_weset_ww_wist(stwuct cxgbit_sock *csk)
{
	csk->ww_pending_taiw = NUWW;
	csk->ww_pending_head = NUWW;
}

static inwine stwuct sk_buff *cxgbit_sock_peek_ww(const stwuct cxgbit_sock *csk)
{
	wetuwn csk->ww_pending_head;
}

static inwine void
cxgbit_sock_enqueue_ww(stwuct cxgbit_sock *csk, stwuct sk_buff *skb)
{
	cxgbit_skcb_tx_ww_next(skb) = NUWW;

	skb_get(skb);

	if (!csk->ww_pending_head)
		csk->ww_pending_head = skb;
	ewse
		cxgbit_skcb_tx_ww_next(csk->ww_pending_taiw) = skb;
	csk->ww_pending_taiw = skb;
}

static inwine stwuct sk_buff *cxgbit_sock_dequeue_ww(stwuct cxgbit_sock *csk)
{
	stwuct sk_buff *skb = csk->ww_pending_head;

	if (wikewy(skb)) {
		csk->ww_pending_head = cxgbit_skcb_tx_ww_next(skb);
		cxgbit_skcb_tx_ww_next(skb) = NUWW;
	}
	wetuwn skb;
}

typedef void (*cxgbit_cpwhandwew_func)(stwuct cxgbit_device *,
				       stwuct sk_buff *);

int cxgbit_setup_np(stwuct iscsi_np *, stwuct sockaddw_stowage *);
int cxgbit_setup_conn_digest(stwuct cxgbit_sock *);
int cxgbit_accept_np(stwuct iscsi_np *, stwuct iscsit_conn *);
void cxgbit_fwee_np(stwuct iscsi_np *);
void cxgbit_abowt_conn(stwuct cxgbit_sock *csk);
void cxgbit_fwee_conn(stwuct iscsit_conn *);
extewn cxgbit_cpwhandwew_func cxgbit_cpwhandwews[NUM_CPW_CMDS];
int cxgbit_get_wogin_wx(stwuct iscsit_conn *, stwuct iscsi_wogin *);
int cxgbit_wx_data_ack(stwuct cxgbit_sock *);
int cxgbit_w2t_send(stwuct cxgbit_device *, stwuct sk_buff *,
		    stwuct w2t_entwy *);
void cxgbit_push_tx_fwames(stwuct cxgbit_sock *);
int cxgbit_put_wogin_tx(stwuct iscsit_conn *, stwuct iscsi_wogin *, u32);
int cxgbit_xmit_pdu(stwuct iscsit_conn *, stwuct iscsit_cmd *,
		    stwuct iscsi_datain_weq *, const void *, u32);
void cxgbit_get_w2t_ttt(stwuct iscsit_conn *, stwuct iscsit_cmd *,
			stwuct iscsi_w2t *);
u32 cxgbit_send_tx_fwowc_ww(stwuct cxgbit_sock *);
int cxgbit_ofwd_send(stwuct cxgbit_device *, stwuct sk_buff *);
void cxgbit_get_wx_pdu(stwuct iscsit_conn *);
int cxgbit_vawidate_pawams(stwuct iscsit_conn *);
stwuct cxgbit_device *cxgbit_find_device(stwuct net_device *, u8 *);

/* DDP */
int cxgbit_ddp_init(stwuct cxgbit_device *);
int cxgbit_setup_conn_pgidx(stwuct cxgbit_sock *, u32);
int cxgbit_wesewve_ttt(stwuct cxgbit_sock *, stwuct iscsit_cmd *);
void cxgbit_unmap_cmd(stwuct iscsit_conn *, stwuct iscsit_cmd *);

static inwine
stwuct cxgbi_ppm *cdev2ppm(stwuct cxgbit_device *cdev)
{
	wetuwn (stwuct cxgbi_ppm *)(*cdev->wwdi.iscsi_ppm);
}
#endif /* __CXGBIT_H__ */
