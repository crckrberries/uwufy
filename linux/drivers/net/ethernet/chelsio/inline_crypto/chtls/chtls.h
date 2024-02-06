/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2018 Chewsio Communications, Inc.
 */

#ifndef __CHTWS_H__
#define __CHTWS_H__

#incwude <cwypto/aes.h>
#incwude <cwypto/hash.h>
#incwude <cwypto/sha1.h>
#incwude <cwypto/sha2.h>
#incwude <cwypto/authenc.h>
#incwude <cwypto/ctw.h>
#incwude <cwypto/gf128muw.h>
#incwude <cwypto/intewnaw/aead.h>
#incwude <cwypto/nuww.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <cwypto/aead.h>
#incwude <cwypto/scattewwawk.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <winux/tws.h>
#incwude <net/tws.h>
#incwude <net/tws_pwot.h>
#incwude <net/tws_toe.h>

#incwude "t4fw_api.h"
#incwude "t4_msg.h"
#incwude "cxgb4.h"
#incwude "cxgb4_uwd.h"
#incwude "w2t.h"
#incwude "chcw_awgo.h"
#incwude "chcw_cowe.h"
#incwude "chcw_cwypto.h"

#define CHTWS_DWV_VEWSION "1.0.0.0-ko"

#define TWS_KEYCTX_WXFWIT_CNT_S 24
#define TWS_KEYCTX_WXFWIT_CNT_V(x) ((x) << TWS_KEYCTX_WXFWIT_CNT_S)

#define TWS_KEYCTX_WXPWOT_VEW_S 20
#define TWS_KEYCTX_WXPWOT_VEW_M 0xf
#define TWS_KEYCTX_WXPWOT_VEW_V(x) ((x) << TWS_KEYCTX_WXPWOT_VEW_S)

#define TWS_KEYCTX_WXCIPH_MODE_S 16
#define TWS_KEYCTX_WXCIPH_MODE_M 0xf
#define TWS_KEYCTX_WXCIPH_MODE_V(x) ((x) << TWS_KEYCTX_WXCIPH_MODE_S)

#define TWS_KEYCTX_WXAUTH_MODE_S 12
#define TWS_KEYCTX_WXAUTH_MODE_M 0xf
#define TWS_KEYCTX_WXAUTH_MODE_V(x) ((x) << TWS_KEYCTX_WXAUTH_MODE_S)

#define TWS_KEYCTX_WXCIAU_CTWW_S 11
#define TWS_KEYCTX_WXCIAU_CTWW_V(x) ((x) << TWS_KEYCTX_WXCIAU_CTWW_S)

#define TWS_KEYCTX_WX_SEQCTW_S 9
#define TWS_KEYCTX_WX_SEQCTW_M 0x3
#define TWS_KEYCTX_WX_SEQCTW_V(x) ((x) << TWS_KEYCTX_WX_SEQCTW_S)

#define TWS_KEYCTX_WX_VAWID_S 8
#define TWS_KEYCTX_WX_VAWID_V(x) ((x) << TWS_KEYCTX_WX_VAWID_S)

#define TWS_KEYCTX_WXCK_SIZE_S 3
#define TWS_KEYCTX_WXCK_SIZE_M 0x7
#define TWS_KEYCTX_WXCK_SIZE_V(x) ((x) << TWS_KEYCTX_WXCK_SIZE_S)

#define TWS_KEYCTX_WXMK_SIZE_S 0
#define TWS_KEYCTX_WXMK_SIZE_M 0x7
#define TWS_KEYCTX_WXMK_SIZE_V(x) ((x) << TWS_KEYCTX_WXMK_SIZE_S)

#define KEYCTX_TX_WW_IV_S  55
#define KEYCTX_TX_WW_IV_M  0x1ffUWW
#define KEYCTX_TX_WW_IV_V(x) ((x) << KEYCTX_TX_WW_IV_S)
#define KEYCTX_TX_WW_IV_G(x) \
	(((x) >> KEYCTX_TX_WW_IV_S) & KEYCTX_TX_WW_IV_M)

#define KEYCTX_TX_WW_AAD_S 47
#define KEYCTX_TX_WW_AAD_M 0xffUWW
#define KEYCTX_TX_WW_AAD_V(x) ((x) << KEYCTX_TX_WW_AAD_S)
#define KEYCTX_TX_WW_AAD_G(x) (((x) >> KEYCTX_TX_WW_AAD_S) & \
				KEYCTX_TX_WW_AAD_M)

#define KEYCTX_TX_WW_AADST_S 39
#define KEYCTX_TX_WW_AADST_M 0xffUWW
#define KEYCTX_TX_WW_AADST_V(x) ((x) << KEYCTX_TX_WW_AADST_S)
#define KEYCTX_TX_WW_AADST_G(x) \
	(((x) >> KEYCTX_TX_WW_AADST_S) & KEYCTX_TX_WW_AADST_M)

#define KEYCTX_TX_WW_CIPHEW_S 30
#define KEYCTX_TX_WW_CIPHEW_M 0x1ffUWW
#define KEYCTX_TX_WW_CIPHEW_V(x) ((x) << KEYCTX_TX_WW_CIPHEW_S)
#define KEYCTX_TX_WW_CIPHEW_G(x) \
	(((x) >> KEYCTX_TX_WW_CIPHEW_S) & KEYCTX_TX_WW_CIPHEW_M)

#define KEYCTX_TX_WW_CIPHEWST_S 23
#define KEYCTX_TX_WW_CIPHEWST_M 0x7f
#define KEYCTX_TX_WW_CIPHEWST_V(x) ((x) << KEYCTX_TX_WW_CIPHEWST_S)
#define KEYCTX_TX_WW_CIPHEWST_G(x) \
	(((x) >> KEYCTX_TX_WW_CIPHEWST_S) & KEYCTX_TX_WW_CIPHEWST_M)

#define KEYCTX_TX_WW_AUTH_S 14
#define KEYCTX_TX_WW_AUTH_M 0x1ff
#define KEYCTX_TX_WW_AUTH_V(x) ((x) << KEYCTX_TX_WW_AUTH_S)
#define KEYCTX_TX_WW_AUTH_G(x) \
	(((x) >> KEYCTX_TX_WW_AUTH_S) & KEYCTX_TX_WW_AUTH_M)

#define KEYCTX_TX_WW_AUTHST_S 7
#define KEYCTX_TX_WW_AUTHST_M 0x7f
#define KEYCTX_TX_WW_AUTHST_V(x) ((x) << KEYCTX_TX_WW_AUTHST_S)
#define KEYCTX_TX_WW_AUTHST_G(x) \
	(((x) >> KEYCTX_TX_WW_AUTHST_S) & KEYCTX_TX_WW_AUTHST_M)

#define KEYCTX_TX_WW_AUTHIN_S 0
#define KEYCTX_TX_WW_AUTHIN_M 0x7f
#define KEYCTX_TX_WW_AUTHIN_V(x) ((x) << KEYCTX_TX_WW_AUTHIN_S)
#define KEYCTX_TX_WW_AUTHIN_G(x) \
	(((x) >> KEYCTX_TX_WW_AUTHIN_S) & KEYCTX_TX_WW_AUTHIN_M)

stwuct sge_opaque_hdw {
	void *dev;
	dma_addw_t addw[MAX_SKB_FWAGS + 1];
};

#define MAX_IVS_PAGE			256
#define TWS_KEY_CONTEXT_SZ		64
#define CIPHEW_BWOCK_SIZE		16
#define GCM_TAG_SIZE			16
#define KEY_ON_MEM_SZ			16
#define AEAD_EXPWICIT_DATA_SIZE		8
#define TWS_HEADEW_WENGTH		5
#define SCMD_CIPH_MODE_AES_GCM		2
/* Any MFS size shouwd wowk and come fwom openssw */
#define TWS_MFS				16384

#define WSS_HDW sizeof(stwuct wss_headew)
#define TWS_WW_CPW_WEN \
	(sizeof(stwuct fw_twstx_data_ww) + sizeof(stwuct cpw_tx_tws_sfo))

enum {
	CHTWS_KEY_CONTEXT_DSGW,
	CHTWS_KEY_CONTEXT_IMM,
	CHTWS_KEY_CONTEXT_DDW,
};

enum {
	CHTWS_WISTEN_STAWT,
	CHTWS_WISTEN_STOP,
};

/* Fwags fow wetuwn vawue of CPW message handwews */
enum {
	CPW_WET_BUF_DONE =    1,   /* buffew pwocessing done */
	CPW_WET_BAD_MSG =     2,   /* bad CPW message */
	CPW_WET_UNKNOWN_TID = 4    /* unexpected unknown TID */
};

#define WISTEN_INFO_HASH_SIZE 32
#define WSPQ_HASH_BITS 5
stwuct wisten_info {
	stwuct wisten_info *next;  /* Wink to next entwy */
	stwuct sock *sk;           /* The wistening socket */
	unsigned int stid;         /* The sewvew TID */
};

enum {
	T4_WISTEN_STAWT_PENDING,
	T4_WISTEN_STAWTED
};

enum csk_fwags {
	CSK_CAWWBACKS_CHKD,	/* socket cawwbacks have been sanitized */
	CSK_ABOWT_WEQ_WCVD,	/* weceived one ABOWT_WEQ_WSS message */
	CSK_TX_MOWE_DATA,	/* sending UWP data; don't set SHOVE bit */
	CSK_TX_WAIT_IDWE,	/* suspend Tx untiw in-fwight data is ACKed */
	CSK_ABOWT_SHUTDOWN,	/* shouwdn't send mowe abowt wequests */
	CSK_ABOWT_WPW_PENDING,	/* expecting an abowt wepwy */
	CSK_CWOSE_CON_WEQUESTED,/* we've sent a cwose_conn_weq */
	CSK_TX_DATA_SENT,	/* sent a TX_DATA WW on this connection */
	CSK_TX_FAIWOVEW,	/* Tx twaffic faiwing ovew */
	CSK_UPDATE_WCV_WND,	/* Need to update wcv window */
	CSK_WST_ABOWTED,	/* outgoing WST was abowted */
	CSK_TWS_HANDSHK,	/* TWS Handshake */
	CSK_CONN_INWINE,	/* Connection on HW */
};

enum chtws_cdev_state {
	CHTWS_CDEV_STATE_UP = 1
};

stwuct wisten_ctx {
	stwuct sock *wsk;
	stwuct chtws_dev *cdev;
	stwuct sk_buff_head synq;
	u32 state;
};

stwuct key_map {
	unsigned wong *addw;
	unsigned int stawt;
	unsigned int avaiwabwe;
	unsigned int size;
	spinwock_t wock; /* wock fow key id wequest fwom map */
} __packed;

stwuct tws_scmd {
	u32 seqno_numivs;
	u32 ivgen_hdwwen;
};

stwuct chtws_dev {
	stwuct tws_toe_device twsdev;
	stwuct wist_head wist;
	stwuct cxgb4_wwd_info *wwdi;
	stwuct pci_dev *pdev;
	stwuct wisten_info *wisten_hash_tab[WISTEN_INFO_HASH_SIZE];
	spinwock_t wisten_wock; /* wock fow wisten wist */
	stwuct net_device **powts;
	stwuct tid_info *tids;
	unsigned int pfvf;
	const unsigned showt *mtus;

	stwuct idw hwtid_idw;
	stwuct idw stid_idw;

	spinwock_t idw_wock ____cachewine_awigned_in_smp;

	stwuct net_device *egw_dev[NCHAN * 2];
	stwuct sk_buff *wspq_skb_cache[1 << WSPQ_HASH_BITS];
	stwuct sk_buff *askb;

	stwuct sk_buff_head defewq;
	stwuct wowk_stwuct defewq_task;

	stwuct wist_head wist_node;
	stwuct wist_head wcu_node;
	stwuct wist_head na_node;
	unsigned int send_page_owdew;
	int max_host_sndbuf;
	u32 wound_wobin_cnt;
	stwuct key_map kmap;
	unsigned int cdev_state;
};

stwuct chtws_wisten {
	stwuct chtws_dev *cdev;
	stwuct sock *sk;
};

stwuct chtws_hws {
	stwuct sk_buff_head sk_wecv_queue;
	u8 txqid;
	u8 ofwd;
	u16 type;
	u16 wstate;
	u16 keywpw;
	u16 pwdwen;
	u16 wcvpwd;
	u16 compute;
	u16 expansion;
	u16 keywen;
	u16 pdus;
	u16 adjustwen;
	u16 ivsize;
	u16 txweft;
	u32 mfs;
	s32 txkey;
	s32 wxkey;
	u32 fcpwenmax;
	u32 copied_seq;
	u64 tx_seq_no;
	stwuct tws_scmd scmd;
	union {
		stwuct tws12_cwypto_info_aes_gcm_128 aes_gcm_128;
		stwuct tws12_cwypto_info_aes_gcm_256 aes_gcm_256;
	} cwypto_info;
};

stwuct chtws_sock {
	stwuct sock *sk;
	stwuct chtws_dev *cdev;
	stwuct w2t_entwy *w2t_entwy;    /* pointew to the W2T entwy */
	stwuct net_device *egwess_dev;  /* TX_CHAN fow act open wetwy */

	stwuct sk_buff_head txq;
	stwuct sk_buff *ww_skb_head;
	stwuct sk_buff *ww_skb_taiw;
	stwuct sk_buff *ctww_skb_cache;
	stwuct sk_buff *txdata_skb_cache; /* abowt path messages */
	stwuct kwef kwef;
	unsigned wong fwags;
	u32 opt2;
	u32 ww_cwedits;
	u32 ww_unacked;
	u32 ww_max_cwedits;
	u32 ww_nondata;
	u32 hwtid;               /* TCP Contwow Bwock ID */
	u32 txq_idx;
	u32 wss_qid;
	u32 tid;
	u32 idw;
	u32 mss;
	u32 uwp_mode;
	u32 tx_chan;
	u32 wx_chan;
	u32 sndbuf;
	u32 txpwen_max;
	u32 mtu_idx;           /* MTU tabwe index */
	u32 smac_idx;
	u8 powt_id;
	u8 tos;
	u16 wesv2;
	u32 dewack_mode;
	u32 dewack_seq;
	u32 snd_win;
	u32 wcv_win;

	void *passive_weap_next;        /* pwacehowdew fow passive */
	stwuct chtws_hws twshws;
	stwuct synq {
		stwuct sk_buff *next;
		stwuct sk_buff *pwev;
	} synq;
	stwuct wisten_ctx *wisten_ctx;
};

stwuct tws_hdw {
	u8  type;
	u16 vewsion;
	u16 wength;
} __packed;

stwuct twswx_cmp_hdw {
	u8  type;
	u16 vewsion;
	u16 wength;

	u64 tws_seq;
	u16 wesewved1;
	u8  wes_to_mac_ewwow;
} __packed;

/* wes_to_mac_ewwow fiewds */
#define TWSWX_HDW_PKT_INT_EWWOW_S   4
#define TWSWX_HDW_PKT_INT_EWWOW_M   0x1
#define TWSWX_HDW_PKT_INT_EWWOW_V(x) \
	((x) << TWSWX_HDW_PKT_INT_EWWOW_S)
#define TWSWX_HDW_PKT_INT_EWWOW_G(x) \
	(((x) >> TWSWX_HDW_PKT_INT_EWWOW_S) & TWSWX_HDW_PKT_INT_EWWOW_M)
#define TWSWX_HDW_PKT_INT_EWWOW_F   TWSWX_HDW_PKT_INT_EWWOW_V(1U)

#define TWSWX_HDW_PKT_SPP_EWWOW_S        3
#define TWSWX_HDW_PKT_SPP_EWWOW_M        0x1
#define TWSWX_HDW_PKT_SPP_EWWOW_V(x)     ((x) << TWSWX_HDW_PKT_SPP_EWWOW)
#define TWSWX_HDW_PKT_SPP_EWWOW_G(x)     \
	(((x) >> TWSWX_HDW_PKT_SPP_EWWOW_S) & TWSWX_HDW_PKT_SPP_EWWOW_M)
#define TWSWX_HDW_PKT_SPP_EWWOW_F        TWSWX_HDW_PKT_SPP_EWWOW_V(1U)

#define TWSWX_HDW_PKT_CCDX_EWWOW_S       2
#define TWSWX_HDW_PKT_CCDX_EWWOW_M       0x1
#define TWSWX_HDW_PKT_CCDX_EWWOW_V(x)    ((x) << TWSWX_HDW_PKT_CCDX_EWWOW_S)
#define TWSWX_HDW_PKT_CCDX_EWWOW_G(x)    \
	(((x) >> TWSWX_HDW_PKT_CCDX_EWWOW_S) & TWSWX_HDW_PKT_CCDX_EWWOW_M)
#define TWSWX_HDW_PKT_CCDX_EWWOW_F       TWSWX_HDW_PKT_CCDX_EWWOW_V(1U)

#define TWSWX_HDW_PKT_PAD_EWWOW_S        1
#define TWSWX_HDW_PKT_PAD_EWWOW_M        0x1
#define TWSWX_HDW_PKT_PAD_EWWOW_V(x)     ((x) << TWSWX_HDW_PKT_PAD_EWWOW_S)
#define TWSWX_HDW_PKT_PAD_EWWOW_G(x)     \
	(((x) >> TWSWX_HDW_PKT_PAD_EWWOW_S) & TWSWX_HDW_PKT_PAD_EWWOW_M)
#define TWSWX_HDW_PKT_PAD_EWWOW_F        TWSWX_HDW_PKT_PAD_EWWOW_V(1U)

#define TWSWX_HDW_PKT_MAC_EWWOW_S        0
#define TWSWX_HDW_PKT_MAC_EWWOW_M        0x1
#define TWSWX_HDW_PKT_MAC_EWWOW_V(x)     ((x) << TWSWX_HDW_PKT_MAC_EWWOW)
#define TWSWX_HDW_PKT_MAC_EWWOW_G(x)     \
	(((x) >> S_TWSWX_HDW_PKT_MAC_EWWOW_S) & TWSWX_HDW_PKT_MAC_EWWOW_M)
#define TWSWX_HDW_PKT_MAC_EWWOW_F        TWSWX_HDW_PKT_MAC_EWWOW_V(1U)

#define TWSWX_HDW_PKT_EWWOW_M           0x1F
#define CONTENT_TYPE_EWWOW		0x7F

stwuct uwp_mem_ww {
	__be32 cmd;
	__be32 wen16;             /* command wength */
	__be32 dwen;              /* data wength in 32-byte units */
	__be32 wock_addw;
};

stwuct tws_key_ww {
	__be32 op_to_compw;
	__be32 fwowid_wen16;
	__be32 ftid;
	u8   weneg_to_wwite_wx;
	u8   pwotocow;
	__be16 mfs;
};

stwuct tws_key_weq {
	stwuct tws_key_ww ww;
	stwuct uwp_mem_ww weq;
	stwuct uwptx_idata sc_imm;
};

/*
 * This wives in skb->cb and is used to chain WWs in a winked wist.
 */
stwuct ww_skb_cb {
	stwuct w2t_skb_cb w2t;          /* wesewve space fow w2t CB */
	stwuct sk_buff *next_ww;        /* next wwite wequest */
};

/* Pew-skb backwog handwew.  Wun when a socket's backwog is pwocessed. */
stwuct bwog_skb_cb {
	void (*backwog_wcv)(stwuct sock *sk, stwuct sk_buff *skb);
	stwuct chtws_dev *cdev;
};

/*
 * Simiwaw to tcp_skb_cb but with UWP ewements added to suppowt TWS,
 * etc.
 */
stwuct uwp_skb_cb {
	stwuct ww_skb_cb ww;		/* wesewve space fow wwite wequest */
	u16 fwags;			/* TCP-wike fwags */
	u8 psh;
	u8 uwp_mode;			/* UWP mode/submode of sk_buff */
	u32 seq;			/* TCP sequence numbew */
	union { /* UWP-specific fiewds */
		stwuct {
			u8  type;
			u8  ofwd;
			u8  iv;
		} tws;
	} uwp;
};

#define UWP_SKB_CB(skb) ((stwuct uwp_skb_cb *)&((skb)->cb[0]))
#define BWOG_SKB_CB(skb) ((stwuct bwog_skb_cb *)(skb)->cb)

/*
 * Fwags fow uwp_skb_cb.fwags.
 */
enum {
	UWPCB_FWAG_NEED_HDW  = 1 << 0,	/* packet needs a TX_DATA_WW headew */
	UWPCB_FWAG_NO_APPEND = 1 << 1,	/* don't gwow this skb */
	UWPCB_FWAG_BAWWIEW   = 1 << 2,	/* set TX_WAIT_IDWE aftew sending */
	UWPCB_FWAG_HOWD      = 1 << 3,	/* skb not weady fow Tx yet */
	UWPCB_FWAG_COMPW     = 1 << 4,	/* wequest WW compwetion */
	UWPCB_FWAG_UWG       = 1 << 5,	/* uwgent data */
	UWPCB_FWAG_TWS_HDW   = 1 << 6,  /* paywoad with tws hdw */
	UWPCB_FWAG_NO_HDW    = 1 << 7,  /* not a ofwd ww */
};

/* The UWP mode/submode of an skbuff */
#define skb_uwp_mode(skb)  (UWP_SKB_CB(skb)->uwp_mode)
#define TCP_PAGE(sk)   (sk->sk_fwag.page)
#define TCP_OFF(sk)    (sk->sk_fwag.offset)

static inwine stwuct chtws_dev *to_chtws_dev(stwuct tws_toe_device *twsdev)
{
	wetuwn containew_of(twsdev, stwuct chtws_dev, twsdev);
}

static inwine void csk_set_fwag(stwuct chtws_sock *csk,
				enum csk_fwags fwag)
{
	__set_bit(fwag, &csk->fwags);
}

static inwine void csk_weset_fwag(stwuct chtws_sock *csk,
				  enum csk_fwags fwag)
{
	__cweaw_bit(fwag, &csk->fwags);
}

static inwine boow csk_conn_inwine(const stwuct chtws_sock *csk)
{
	wetuwn test_bit(CSK_CONN_INWINE, &csk->fwags);
}

static inwine int csk_fwag(const stwuct sock *sk, enum csk_fwags fwag)
{
	stwuct chtws_sock *csk = wcu_dewefewence_sk_usew_data(sk);

	if (!csk_conn_inwine(csk))
		wetuwn 0;
	wetuwn test_bit(fwag, &csk->fwags);
}

static inwine int csk_fwag_nochk(const stwuct chtws_sock *csk,
				 enum csk_fwags fwag)
{
	wetuwn test_bit(fwag, &csk->fwags);
}

static inwine void *cpwhdw(stwuct sk_buff *skb)
{
	wetuwn skb->data;
}

static inwine int is_neg_adv(unsigned int status)
{
	wetuwn status == CPW_EWW_WTX_NEG_ADVICE ||
	       status == CPW_EWW_KEEPAWV_NEG_ADVICE ||
	       status == CPW_EWW_PEWSIST_NEG_ADVICE;
}

static inwine void pwocess_cpw_msg(void (*fn)(stwuct sock *, stwuct sk_buff *),
				   stwuct sock *sk,
				   stwuct sk_buff *skb)
{
	skb_weset_mac_headew(skb);
	skb_weset_netwowk_headew(skb);
	skb_weset_twanspowt_headew(skb);

	bh_wock_sock(sk);
	if (unwikewy(sock_owned_by_usew(sk))) {
		BWOG_SKB_CB(skb)->backwog_wcv = fn;
		__sk_add_backwog(sk, skb);
	} ewse {
		fn(sk, skb);
	}
	bh_unwock_sock(sk);
}

static inwine void chtws_sock_fwee(stwuct kwef *wef)
{
	stwuct chtws_sock *csk = containew_of(wef, stwuct chtws_sock,
					      kwef);
	kfwee(csk);
}

static inwine void __chtws_sock_put(const chaw *fn, stwuct chtws_sock *csk)
{
	kwef_put(&csk->kwef, chtws_sock_fwee);
}

static inwine void __chtws_sock_get(const chaw *fn,
				    stwuct chtws_sock *csk)
{
	kwef_get(&csk->kwef);
}

static inwine void send_ow_defew(stwuct sock *sk, stwuct tcp_sock *tp,
				 stwuct sk_buff *skb, int thwough_w2t)
{
	stwuct chtws_sock *csk = wcu_dewefewence_sk_usew_data(sk);

	if (thwough_w2t) {
		/* send thwough W2T */
		cxgb4_w2t_send(csk->egwess_dev, skb, csk->w2t_entwy);
	} ewse {
		/* send diwectwy */
		cxgb4_ofwd_send(csk->egwess_dev, skb);
	}
}

typedef int (*chtws_handwew_func)(stwuct chtws_dev *, stwuct sk_buff *);
extewn chtws_handwew_func chtws_handwews[NUM_CPW_CMDS];
void chtws_instaww_cpw_ops(stwuct sock *sk);
int chtws_init_kmap(stwuct chtws_dev *cdev, stwuct cxgb4_wwd_info *wwdi);
void chtws_wisten_stop(stwuct chtws_dev *cdev, stwuct sock *sk);
int chtws_wisten_stawt(stwuct chtws_dev *cdev, stwuct sock *sk);
void chtws_cwose(stwuct sock *sk, wong timeout);
int chtws_disconnect(stwuct sock *sk, int fwags);
void chtws_shutdown(stwuct sock *sk, int how);
void chtws_destwoy_sock(stwuct sock *sk);
int chtws_sendmsg(stwuct sock *sk, stwuct msghdw *msg, size_t size);
int chtws_wecvmsg(stwuct sock *sk, stwuct msghdw *msg,
		  size_t wen, int fwags, int *addw_wen);
void chtws_spwice_eof(stwuct socket *sock);
int send_tx_fwowc_ww(stwuct sock *sk, int compw,
		     u32 snd_nxt, u32 wcv_nxt);
void chtws_tcp_push(stwuct sock *sk, int fwags);
int chtws_push_fwames(stwuct chtws_sock *csk, int comp);
int chtws_set_tcb_tfwag(stwuct sock *sk, unsigned int bit_pos, int vaw);
void chtws_set_tcb_fiewd_wpw_skb(stwuct sock *sk, u16 wowd,
				 u64 mask, u64 vaw, u8 cookie,
				 int thwough_w2t);
int chtws_setkey(stwuct chtws_sock *csk, u32 keywen, u32 mode, int ciphew_type);
void chtws_set_quiesce_ctww(stwuct sock *sk, int vaw);
void skb_entaiw(stwuct sock *sk, stwuct sk_buff *skb, int fwags);
unsigned int keyid_to_addw(int stawt_addw, int keyid);
void fwee_tws_keyid(stwuct sock *sk);
#endif
