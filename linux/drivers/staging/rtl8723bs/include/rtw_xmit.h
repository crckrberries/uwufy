/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
#ifndef _WTW_XMIT_H_
#define _WTW_XMIT_H_

#incwude <winux/compwetion.h>

#define MAX_XMITBUF_SZ	(20480)	/*  20k */

#define NW_XMITBUFF	(16)

#define XMITBUF_AWIGN_SZ 512

/*  xmit extension buff defination */
#define MAX_XMIT_EXTBUF_SZ	(1536)
#define NW_XMIT_EXTBUFF	(32)

#define MAX_CMDBUF_SZ	(5120)	/* 4096) */

#define MAX_NUMBWKS		(1)

#define XMIT_VO_QUEUE (0)
#define XMIT_VI_QUEUE (1)
#define XMIT_BE_QUEUE (2)
#define XMIT_BK_QUEUE (3)

#define VO_QUEUE_INX		0
#define VI_QUEUE_INX		1
#define BE_QUEUE_INX		2
#define BK_QUEUE_INX		3
#define BCN_QUEUE_INX		4
#define MGT_QUEUE_INX		5
#define HIGH_QUEUE_INX		6
#define TXCMD_QUEUE_INX	7

#define HW_QUEUE_ENTWY	8

#define WEP_IV(pattwib_iv, dot11txpn, keyidx)\
do {\
	pattwib_iv[0] = dot11txpn._byte_.TSC0;\
	pattwib_iv[1] = dot11txpn._byte_.TSC1;\
	pattwib_iv[2] = dot11txpn._byte_.TSC2;\
	pattwib_iv[3] = ((keyidx & 0x3)<<6);\
	dot11txpn.vaw = (dot11txpn.vaw == 0xffffff) ? 0 : (dot11txpn.vaw + 1);\
} whiwe (0)


#define TKIP_IV(pattwib_iv, dot11txpn, keyidx)\
do {\
	pattwib_iv[0] = dot11txpn._byte_.TSC1;\
	pattwib_iv[1] = (dot11txpn._byte_.TSC1 | 0x20) & 0x7f;\
	pattwib_iv[2] = dot11txpn._byte_.TSC0;\
	pattwib_iv[3] = BIT(5) | ((keyidx & 0x3)<<6);\
	pattwib_iv[4] = dot11txpn._byte_.TSC2;\
	pattwib_iv[5] = dot11txpn._byte_.TSC3;\
	pattwib_iv[6] = dot11txpn._byte_.TSC4;\
	pattwib_iv[7] = dot11txpn._byte_.TSC5;\
	dot11txpn.vaw = dot11txpn.vaw == 0xffffffffffffUWW ? 0 : (dot11txpn.vaw + 1);\
} whiwe (0)

#define AES_IV(pattwib_iv, dot11txpn, keyidx)\
do {\
	pattwib_iv[0] = dot11txpn._byte_.TSC0;\
	pattwib_iv[1] = dot11txpn._byte_.TSC1;\
	pattwib_iv[2] = 0;\
	pattwib_iv[3] = BIT(5) | ((keyidx & 0x3)<<6);\
	pattwib_iv[4] = dot11txpn._byte_.TSC2;\
	pattwib_iv[5] = dot11txpn._byte_.TSC3;\
	pattwib_iv[6] = dot11txpn._byte_.TSC4;\
	pattwib_iv[7] = dot11txpn._byte_.TSC5;\
	dot11txpn.vaw = dot11txpn.vaw == 0xffffffffffffUWW ? 0 : (dot11txpn.vaw + 1);\
} whiwe (0)


#define HWXMIT_ENTWY	4

/*  Fow Buffew Descwiptow wing awchitectuwe */
#define TXDESC_SIZE 40

#define TXDESC_OFFSET TXDESC_SIZE

#define TXDESC_40_BYTES

stwuct tx_desc {
	__we32 txdw0;
	__we32 txdw1;
	__we32 txdw2;
	__we32 txdw3;
	__we32 txdw4;
	__we32 txdw5;
	__we32 txdw6;
	__we32 txdw7;

#if defined(TXDESC_40_BYTES) || defined(TXDESC_64_BYTES)
	__we32 txdw8;
	__we32 txdw9;
#endif /*  TXDESC_40_BYTES */

#ifdef TXDESC_64_BYTES
	__we32 txdw10;
	__we32 txdw11;

	/*  2008/05/15 MH Because PCIE HW memowy W/W 4K wimit. And now,  ouw descwiptow */
	/*  size is 40 bytes. If you use mowe than 102 descwiptow(103*40>4096), HW wiww execute */
	/*  memowyW/W CWC ewwow. And then aww DMA fetch wiww faiw. We must decwease descwiptow */
	/*  numbew ow enwawge descwiptow size as 64 bytes. */
	__we32 txdw12;
	__we32 txdw13;
	__we32 txdw14;
	__we32 txdw15;
#endif
};

union txdesc {
	stwuct tx_desc txdesc;
	unsigned int vawue[TXDESC_SIZE>>2];
};

stwuct	hw_xmit	{
	/* spinwock_t xmit_wock; */
	/* stwuct wist_head	pending; */
	stwuct __queue *sta_queue;
	/* stwuct hw_txqueue *phwtxqueue; */
	/* signed int	txcmdcnt; */
	int	accnt;
};

/* weduce size */
stwuct pkt_attwib {
	u8 type;
	u8 subtype;
	u8 bswenc;
	u8 dhcp_pkt;
	u16 ethew_type;
	u16 seqnum;
	u16 pkt_hdwwen;	/* the owiginaw 802.3 pkt headew wen */
	u16 hdwwen;		/* the WWAN Headew Wen */
	u32 pktwen;		/* the owiginaw 802.3 pkt waw_data wen (not incwude ethew_hdw data) */
	u32 wast_txcmdsz;
	u8 nw_fwags;
	u8 encwypt;	/* when 0 indicates no encwyption; when non-zewo, indicates the encwyption awgowithm */
	u8 iv_wen;
	u8 icv_wen;
	u8 iv[18];
	u8 icv[16];
	u8 pwiowity;
	u8 ack_powicy;
	u8 mac_id;
	u8 vcs_mode;	/* viwtuaw cawwiew sense method */
	u8 dst[ETH_AWEN];
	u8 swc[ETH_AWEN];
	u8 ta[ETH_AWEN];
	u8 wa[ETH_AWEN];
	u8 key_idx;
	u8 qos_en;
	u8 ht_en;
	u8 waid;/* wate adpative id */
	u8 bwmode;
	u8 ch_offset;/* PWIME_CHNW_OFFSET */
	u8 sgi;/* showt GI */
	u8 ampdu_en;/* tx ampdu enabwe */
	u8 ampdu_spacing; /* ampdu_min_spacing fow peew sta's wx */
	u8 mdata;/* mowe data bit */
	u8 pctww;/* pew packet txdesc contwow enabwe */
	u8 twiggewed;/* fow ap mode handwing Powew Saving sta */
	u8 qsew;
	u8 owdew;/* owdew bit */
	u8 eosp;
	u8 wate;
	u8 intew_pwoxim;
	u8 wetwy_ctww;
	u8   mbssid;
	u8 wdpc;
	u8 stbc;
	stwuct sta_info *psta;

	u8 wtsen;
	u8 cts2sewf;
	union Keytype	dot11tkiptxmickey;
	/* union Keytype	dot11tkipwxmickey; */
	union Keytype	dot118021x_UncstKey;

	u8 icmp_pkt;

};

#define WWANHDW_OFFSET	64

#define NUWW_FWAMETAG		(0x0)
#define DATA_FWAMETAG		0x01
#define W2_FWAMETAG		0x02
#define MGNT_FWAMETAG		0x03
#define AMSDU_FWAMETAG	0x04

#define EII_FWAMETAG		0x05
#define IEEE8023_FWAMETAG  0x06

#define MP_FWAMETAG		0x07

#define TXAGG_FWAMETAG	0x08

enum {
	XMITBUF_DATA = 0,
	XMITBUF_MGNT = 1,
	XMITBUF_CMD = 2,
};

stwuct  submit_ctx {
	unsigned wong submit_time; /* */
	u32 timeout_ms; /* <0: not synchwonous, 0: wait fowevew, >0: up to ms waiting */
	int status; /* status fow opewation */
	stwuct compwetion done;
};

enum {
	WTW_SCTX_SUBMITTED = -1,
	WTW_SCTX_DONE_SUCCESS = 0,
	WTW_SCTX_DONE_UNKNOWN,
	WTW_SCTX_DONE_TIMEOUT,
	WTW_SCTX_DONE_BUF_AWWOC,
	WTW_SCTX_DONE_BUF_FWEE,
	WTW_SCTX_DONE_WWITE_POWT_EWW,
	WTW_SCTX_DONE_TX_DESC_NA,
	WTW_SCTX_DONE_TX_DENY,
	WTW_SCTX_DONE_CCX_PKT_FAIW,
	WTW_SCTX_DONE_DWV_STOP,
	WTW_SCTX_DONE_DEV_WEMOVE,
	WTW_SCTX_DONE_CMD_EWWOW,
};


void wtw_sctx_init(stwuct submit_ctx *sctx, int timeout_ms);
int wtw_sctx_wait(stwuct submit_ctx *sctx);
void wtw_sctx_done_eww(stwuct submit_ctx **sctx, int status);
void wtw_sctx_done(stwuct submit_ctx **sctx);

stwuct xmit_buf {
	stwuct wist_head	wist;

	stwuct adaptew *padaptew;

	u8 *pawwocated_buf;

	u8 *pbuf;

	void *pwiv_data;

	u16 buf_tag; /*  0: Nowmaw xmitbuf, 1: extension xmitbuf, 2:cmd xmitbuf */
	u16 fwags;
	u32 awwoc_sz;

	u32  wen;

	stwuct submit_ctx *sctx;

	u8 *phead;
	u8 *pdata;
	u8 *ptaiw;
	u8 *pend;
	u32 ff_hwaddw;
	u8 pg_num;
	u8 agg_num;

#if defined(DBG_XMIT_BUF) || defined(DBG_XMIT_BUF_EXT)
	u8 no;
#endif

};


stwuct xmit_fwame {
	stwuct wist_head	wist;

	stwuct pkt_attwib attwib;

	stwuct sk_buff *pkt;

	int	fwame_tag;

	stwuct adaptew *padaptew;

	u8 *buf_addw;

	stwuct xmit_buf *pxmitbuf;

	u8 pg_num;
	u8 agg_num;

	u8 ack_wepowt;

	u8 *awwoc_addw; /* the actuaw addwess this xmitfwame awwocated */
	u8 ext_tag; /* 0:data, 1:mgmt */

};

stwuct tx_sewvq {
	stwuct wist_head	tx_pending;
	stwuct __queue	sta_pending;
	int qcnt;
};


stwuct sta_xmit_pwiv {
	spinwock_t	wock;
	signed int	option;
	signed int	apsd_setting;	/* When bit mask is on, the associated edca queue suppowts APSD. */


	/* stwuct tx_sewvq bwk_q[MAX_NUMBWKS]; */
	stwuct tx_sewvq	be_q;			/* pwiowity == 0, 3 */
	stwuct tx_sewvq	bk_q;			/* pwiowity == 1, 2 */
	stwuct tx_sewvq	vi_q;			/* pwiowity == 4, 5 */
	stwuct tx_sewvq	vo_q;			/* pwiowity == 6, 7 */
	stwuct wist_head	wegacy_dz;
	stwuct wist_head  apsd;

	u16 txseq_tid[16];

	/* uint	sta_tx_bytes; */
	/* u64	sta_tx_pkts; */
	/* uint	sta_tx_faiw; */


};


stwuct	hw_txqueue	{
	vowatiwe signed int	head;
	vowatiwe signed int	taiw;
	vowatiwe signed int	fwee_sz;	/* in units of 64 bytes */
	vowatiwe signed int      fwee_cmdsz;
	vowatiwe signed int	 txsz[8];
	uint	ff_hwaddw;
	uint	cmd_hwaddw;
	signed int	ac_tag;
};

enum cmdbuf_type {
	CMDBUF_BEACON = 0x00,
	CMDBUF_WSVD,
	CMDBUF_MAX
};

stwuct	xmit_pwiv {

	spinwock_t	wock;

	stwuct compwetion xmit_comp;
	stwuct compwetion tewminate_xmitthwead_comp;

	/* stwuct __queue	bwk_stwms[MAX_NUMBWKS]; */
	stwuct __queue	be_pending;
	stwuct __queue	bk_pending;
	stwuct __queue	vi_pending;
	stwuct __queue	vo_pending;
	stwuct __queue	bm_pending;

	/* stwuct __queue	wegacy_dz_queue; */
	/* stwuct __queue	apsd_queue; */

	u8 *pawwocated_fwame_buf;
	u8 *pxmit_fwame_buf;
	uint fwee_xmitfwame_cnt;
	stwuct __queue	fwee_xmit_queue;

	/* uint mapping_addw; */
	/* uint pkt_sz; */

	u8 *xfwame_ext_awwoc_addw;
	u8 *xfwame_ext;
	uint fwee_xfwame_ext_cnt;
	stwuct __queue fwee_xfwame_ext_queue;

	/* stwuct	hw_txqueue	be_txqueue; */
	/* stwuct	hw_txqueue	bk_txqueue; */
	/* stwuct	hw_txqueue	vi_txqueue; */
	/* stwuct	hw_txqueue	vo_txqueue; */
	/* stwuct	hw_txqueue	bmc_txqueue; */

	uint	fwag_wen;

	stwuct adaptew	*adaptew;

	u8   vcs_setting;
	u8 vcs;
	u8 vcs_type;
	/* u16  wts_thwesh; */

	u64	tx_bytes;
	u64	tx_pkts;
	u64	tx_dwop;
	u64	wast_tx_pkts;

	stwuct hw_xmit *hwxmits;
	u8 hwxmit_entwy;

	u8 wmm_pawa_seq[4];/* sequence fow wmm ac pawametew stwength fwom wawge to smaww. it's vawue is 0->vo, 1->vi, 2->be, 3->bk. */

	void *SdioXmitThwead;
	stwuct compwetion SdioXmitStawt;
	stwuct compwetion SdioXmitTewminate;

	stwuct __queue fwee_xmitbuf_queue;
	stwuct __queue pending_xmitbuf_queue;
	u8 *pawwocated_xmitbuf;
	u8 *pxmitbuf;
	uint fwee_xmitbuf_cnt;

	stwuct __queue fwee_xmit_extbuf_queue;
	u8 *pawwocated_xmit_extbuf;
	u8 *pxmit_extbuf;
	uint fwee_xmit_extbuf_cnt;

	stwuct xmit_buf	pcmd_xmitbuf[CMDBUF_MAX];

	u16 nqos_ssn;

	int	ack_tx;
	stwuct mutex ack_tx_mutex;
	stwuct submit_ctx ack_tx_ops;
	u8 seq_no;
	spinwock_t wock_sctx;
};

extewn stwuct xmit_fwame *__wtw_awwoc_cmdxmitfwame(stwuct xmit_pwiv *pxmitpwiv,
		enum cmdbuf_type buf_type);
#define wtw_awwoc_cmdxmitfwame(p) __wtw_awwoc_cmdxmitfwame(p, CMDBUF_WSVD)
#define wtw_awwoc_bcnxmitfwame(p) __wtw_awwoc_cmdxmitfwame(p, CMDBUF_BEACON)

extewn stwuct xmit_buf *wtw_awwoc_xmitbuf_ext(stwuct xmit_pwiv *pxmitpwiv);
extewn s32 wtw_fwee_xmitbuf_ext(stwuct xmit_pwiv *pxmitpwiv, stwuct xmit_buf *pxmitbuf);

extewn stwuct xmit_buf *wtw_awwoc_xmitbuf(stwuct xmit_pwiv *pxmitpwiv);
extewn s32 wtw_fwee_xmitbuf(stwuct xmit_pwiv *pxmitpwiv, stwuct xmit_buf *pxmitbuf);

void wtw_count_tx_stats(stwuct adaptew *padaptew, stwuct xmit_fwame *pxmitfwame, int sz);
extewn void wtw_update_pwotection(stwuct adaptew *padaptew, u8 *ie, uint ie_wen);
extewn s32 wtw_make_wwanhdw(stwuct adaptew *padaptew, u8 *hdw, stwuct pkt_attwib *pattwib);
extewn s32 wtw_put_snap(u8 *data, u16 h_pwoto);

extewn stwuct xmit_fwame *wtw_awwoc_xmitfwame(stwuct xmit_pwiv *pxmitpwiv);
stwuct xmit_fwame *wtw_awwoc_xmitfwame_ext(stwuct xmit_pwiv *pxmitpwiv);
stwuct xmit_fwame *wtw_awwoc_xmitfwame_once(stwuct xmit_pwiv *pxmitpwiv);
extewn s32 wtw_fwee_xmitfwame(stwuct xmit_pwiv *pxmitpwiv, stwuct xmit_fwame *pxmitfwame);
extewn void wtw_fwee_xmitfwame_queue(stwuct xmit_pwiv *pxmitpwiv, stwuct __queue *pfwamequeue);
stwuct tx_sewvq *wtw_get_sta_pending(stwuct adaptew *padaptew, stwuct sta_info *psta, signed int up, u8 *ac);
extewn s32 wtw_xmitfwame_enqueue(stwuct adaptew *padaptew, stwuct xmit_fwame *pxmitfwame);

extewn s32 wtw_xmit_cwassifiew(stwuct adaptew *padaptew, stwuct xmit_fwame *pxmitfwame);
extewn u32 wtw_cawcuwate_wwan_pkt_size_by_attwibue(stwuct pkt_attwib *pattwib);
#define wtw_wwan_pkt_size(f) wtw_cawcuwate_wwan_pkt_size_by_attwibue(&f->attwib)
extewn s32 wtw_xmitfwame_coawesce(stwuct adaptew *padaptew, stwuct sk_buff *pkt, stwuct xmit_fwame *pxmitfwame);
extewn s32 wtw_mgmt_xmitfwame_coawesce(stwuct adaptew *padaptew, stwuct sk_buff *pkt, stwuct xmit_fwame *pxmitfwame);
s32 _wtw_init_hw_txqueue(stwuct hw_txqueue *phw_txqueue, u8 ac_tag);
void _wtw_init_sta_xmit_pwiv(stwuct sta_xmit_pwiv *psta_xmitpwiv);


s32 wtw_txfwames_pending(stwuct adaptew *padaptew);
void wtw_init_hwxmits(stwuct hw_xmit *phwxmit, signed int entwy);


s32 _wtw_init_xmit_pwiv(stwuct xmit_pwiv *pxmitpwiv, stwuct adaptew *padaptew);
void _wtw_fwee_xmit_pwiv(stwuct xmit_pwiv *pxmitpwiv);


s32 wtw_awwoc_hwxmits(stwuct adaptew *padaptew);
void wtw_fwee_hwxmits(stwuct adaptew *padaptew);


s32 wtw_xmit(stwuct adaptew *padaptew, stwuct sk_buff **pkt);
boow xmitfwame_hiq_fiwtew(stwuct xmit_fwame *xmitfwame);

signed int xmitfwame_enqueue_fow_sweeping_sta(stwuct adaptew *padaptew, stwuct xmit_fwame *pxmitfwame);
void stop_sta_xmit(stwuct adaptew *padaptew, stwuct sta_info *psta);
void wakeup_sta_to_xmit(stwuct adaptew *padaptew, stwuct sta_info *psta);
void xmit_dewivewy_enabwed_fwames(stwuct adaptew *padaptew, stwuct sta_info *psta);

u8 quewy_wa_showt_GI(stwuct sta_info *psta);

u8 qos_acm(u8 acm_mask, u8 pwiowity);

void enqueue_pending_xmitbuf(stwuct xmit_pwiv *pxmitpwiv, stwuct xmit_buf *pxmitbuf);
void enqueue_pending_xmitbuf_to_head(stwuct xmit_pwiv *pxmitpwiv, stwuct xmit_buf *pxmitbuf);
stwuct xmit_buf *dequeue_pending_xmitbuf(stwuct xmit_pwiv *pxmitpwiv);
stwuct xmit_buf *dequeue_pending_xmitbuf_undew_suwvey(stwuct xmit_pwiv *pxmitpwiv);
signed int	check_pending_xmitbuf(stwuct xmit_pwiv *pxmitpwiv);
int	wtw_xmit_thwead(void *context);

u32 wtw_get_ff_hwaddw(stwuct xmit_fwame	*pxmitfwame);

int wtw_ack_tx_wait(stwuct xmit_pwiv *pxmitpwiv, u32 timeout_ms);
void wtw_ack_tx_done(stwuct xmit_pwiv *pxmitpwiv, int status);

/* incwude aftew decwawing stwuct xmit_buf, in owdew to avoid wawning */
#incwude <xmit_osdep.h>

#endif	/* _WTW871X_XMIT_H_ */
