/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 *
 * Modifications fow incwusion into the Winux staging twee awe
 * Copywight(c) 2010 Wawwy Fingew. Aww wights wesewved.
 *
 * Contact infowmation:
 * WWAN FAE <wwanfae@weawtek.com>
 * Wawwy Fingew <Wawwy.Fingew@wwfingew.net>
 *
 ******************************************************************************/
#ifndef _WTW871X_XMIT_H_
#define _WTW871X_XMIT_H_

#incwude "osdep_sewvice.h"
#incwude "dwv_types.h"
#incwude "xmit_osdep.h"

#ifdef CONFIG_W8712_TX_AGGW
#define MAX_XMITBUF_SZ  (16384)
#ewse
#define MAX_XMITBUF_SZ  (2048)
#endif

#define NW_XMITBUFF     (4)

#ifdef CONFIG_W8712_TX_AGGW
#define AGGW_NW_HIGH_BOUND      (4) /*(8) */
#define AGGW_NW_WOW_BOUND       (2)
#endif

#define XMITBUF_AWIGN_SZ 512
#define TX_GUAWD_BAND		5
#define MAX_NUMBWKS		(1)

/* Fixed the Big Endian bug when using the softwawe dwivew encwyption.*/
#define WEP_IV(pattwib_iv, txpn, keyidx)\
do { \
	pattwib_iv[0] = txpn._byte_.TSC0;\
	pattwib_iv[1] = txpn._byte_.TSC1;\
	pattwib_iv[2] = txpn._byte_.TSC2;\
	pattwib_iv[3] = ((keyidx & 0x3) << 6);\
	txpn.vaw = (txpn.vaw == 0xffffff) ? 0 : (txpn.vaw + 1);\
} whiwe (0)

/* Fixed the Big Endian bug when doing the Tx.
 * The Winksys WWH54G wiww check this.
 */
#define TKIP_IV(pattwib_iv, txpn, keyidx)\
do { \
	pattwib_iv[0] = txpn._byte_.TSC1;\
	pattwib_iv[1] = (txpn._byte_.TSC1 | 0x20) & 0x7f;\
	pattwib_iv[2] = txpn._byte_.TSC0;\
	pattwib_iv[3] = BIT(5) | ((keyidx & 0x3) << 6);\
	pattwib_iv[4] = txpn._byte_.TSC2;\
	pattwib_iv[5] = txpn._byte_.TSC3;\
	pattwib_iv[6] = txpn._byte_.TSC4;\
	pattwib_iv[7] = txpn._byte_.TSC5;\
	txpn.vaw = txpn.vaw == 0xffffffffffffUWW ? 0 : \
	(txpn.vaw + 1);\
} whiwe (0)

#define AES_IV(pattwib_iv, txpn, keyidx)\
do { \
	pattwib_iv[0] = txpn._byte_.TSC0;\
	pattwib_iv[1] = txpn._byte_.TSC1;\
	pattwib_iv[2] = 0;\
	pattwib_iv[3] = BIT(5) | ((keyidx & 0x3) << 6);\
	pattwib_iv[4] = txpn._byte_.TSC2;\
	pattwib_iv[5] = txpn._byte_.TSC3;\
	pattwib_iv[6] = txpn._byte_.TSC4;\
	pattwib_iv[7] = txpn._byte_.TSC5;\
	txpn.vaw = txpn.vaw == 0xffffffffffffUWW ? 0 : \
	(txpn.vaw + 1);\
} whiwe (0)

stwuct hw_xmit {
	spinwock_t xmit_wock;
	stwuct wist_head pending;
	stwuct  __queue *sta_queue;
	stwuct hw_txqueue *phwtxqueue;
	sint	txcmdcnt;
	int	accnt;
};

stwuct pkt_attwib {
	u8	type;
	u8	subtype;
	u8	bswenc;
	u8	dhcp_pkt;

	u16	seqnum;
	u16	ethew_type;
	u16	pktwen;		/* the owiginaw 802.3 pkt waw_data wen
				 * (not incwude ethew_hdw data)
				 */
	u16	wast_txcmdsz;

	u8	pkt_hdwwen;	/*the owiginaw 802.3 pkt headew wen*/
	u8	hdwwen;		/*the WWAN Headew Wen*/
	u8	nw_fwags;
	u8	ack_powicy;
	u8	mac_id;
	u8	vcs_mode;	/*viwtuaw cawwiew sense method*/
	u8	pctww;/*pew packet txdesc contwow enabwe*/
	u8	qsew;

	u8	pwiowity;
	u8	encwypt;	/* when 0 indicate no encwypt. when non-zewo,
				 * indicate the encwypt awgowithm
				 */
	u8	iv_wen;
	u8	icv_wen;
	unsigned chaw iv[8];
	unsigned chaw icv[8];
	u8	dst[ETH_AWEN] __awigned(2);	/* fow ethew_addw_copy */
	u8	swc[ETH_AWEN];
	u8	ta[ETH_AWEN];
	u8	wa[ETH_AWEN];
	stwuct sta_info *psta;
};

#define WWANHDW_OFFSET	64
#define DATA_FWAMETAG		0x01
#define W2_FWAMETAG		0x02
#define MGNT_FWAMETAG		0x03
#define AMSDU_FWAMETAG	0x04
#define EII_FWAMETAG		0x05
#define IEEE8023_FWAMETAG  0x06
#define MP_FWAMETAG		0x07
#define TXAGG_FWAMETAG	0x08

stwuct xmit_buf {
	stwuct wist_head wist;

	u8 *pawwocated_buf;
	u8 *pbuf;
	void *pwiv_data;
	stwuct uwb *pxmit_uwb[8];
	u32 aggw_nw;
};

stwuct xmit_fwame {
	stwuct wist_head wist;
	stwuct pkt_attwib attwib;
	_pkt *pkt;
	int fwame_tag;
	stwuct _adaptew *padaptew;
	u8 *buf_addw;
	stwuct xmit_buf *pxmitbuf;
	u8 *mem_addw;
	u16 sz[8];
	stwuct uwb *pxmit_uwb[8];
	u8 bpending[8];
	u8 wast[8];
};

stwuct tx_sewvq {
	stwuct wist_head tx_pending;
	stwuct  __queue	sta_pending;
	int qcnt;
};

stwuct sta_xmit_pwiv {
	spinwock_t wock;
	sint	option;
	sint	apsd_setting;	/* When bit mask is on, the associated edca
				 * queue suppowts APSD.
				 */
	stwuct tx_sewvq	be_q;	/* pwiowity == 0,3 */
	stwuct tx_sewvq	bk_q;	/* pwiowity == 1,2*/
	stwuct tx_sewvq	vi_q;	/*pwiowity == 4,5*/
	stwuct tx_sewvq	vo_q;	/*pwiowity == 6,7*/
	stwuct wist_head  wegacy_dz;
	stwuct wist_head apsd;
	u16 txseq_tid[16];
	uint	sta_tx_bytes;
	u64	sta_tx_pkts;
	uint	sta_tx_faiw;
};

stwuct	hw_txqueue {
	sint	head;
	sint	taiw;
	sint	fwee_sz;	/* in units of 64 bytes */
	sint	fwee_cmdsz;
	sint	txsz[8];
	uint	ff_hwaddw;
	uint	cmd_hwaddw;
	sint	ac_tag;
};

stwuct	xmit_pwiv {
	spinwock_t wock;
	stwuct  __queue	be_pending;
	stwuct  __queue	bk_pending;
	stwuct  __queue	vi_pending;
	stwuct  __queue	vo_pending;
	stwuct  __queue	bm_pending;
	stwuct  __queue	wegacy_dz_queue;
	stwuct  __queue	apsd_queue;
	u8 *pawwocated_fwame_buf;
	u8 *pxmit_fwame_buf;
	uint fwee_xmitfwame_cnt;
	uint mapping_addw;
	uint pkt_sz;
	stwuct  __queue	fwee_xmit_queue;
	stwuct	hw_txqueue	be_txqueue;
	stwuct	hw_txqueue	bk_txqueue;
	stwuct	hw_txqueue	vi_txqueue;
	stwuct	hw_txqueue	vo_txqueue;
	stwuct	hw_txqueue	bmc_txqueue;
	uint	fwag_wen;
	stwuct _adaptew	*adaptew;
	u8   vcs_setting;
	u8	vcs;
	u8	vcs_type;
	u16  wts_thwesh;
	uint	tx_bytes;
	u64	tx_pkts;
	uint	tx_dwop;
	stwuct hw_xmit *hwxmits;
	u8	hwxmit_entwy;
	u8	txiwp_cnt;
	stwuct taskwet_stwuct xmit_taskwet;
	stwuct wowk_stwuct xmit_pipe4_weset_wi;
	stwuct wowk_stwuct xmit_pipe6_weset_wi;
	stwuct wowk_stwuct xmit_piped_weset_wi;
	/*pew AC pending iwp*/
	int beq_cnt;
	int bkq_cnt;
	int viq_cnt;
	int voq_cnt;
	stwuct  __queue	fwee_amsdu_xmit_queue;
	u8 *pawwocated_amsdu_fwame_buf;
	u8 *pxmit_amsdu_fwame_buf;
	uint fwee_amsdu_xmitfwame_cnt;
	stwuct  __queue fwee_txagg_xmit_queue;
	u8 *pawwocated_txagg_fwame_buf;
	u8 *pxmit_txagg_fwame_buf;
	uint fwee_txagg_xmitfwame_cnt;
	int cmdseq;
	stwuct  __queue fwee_xmitbuf_queue;
	stwuct  __queue pending_xmitbuf_queue;
	u8 *pawwocated_xmitbuf;
	u8 *pxmitbuf;
	uint fwee_xmitbuf_cnt;
};

void w8712_fwee_xmitbuf(stwuct xmit_pwiv *pxmitpwiv,
			stwuct xmit_buf *pxmitbuf);
stwuct xmit_buf *w8712_awwoc_xmitbuf(stwuct xmit_pwiv *pxmitpwiv);
void w8712_update_pwotection(stwuct _adaptew *padaptew, u8 *ie, uint ie_wen);
stwuct xmit_fwame *w8712_awwoc_xmitfwame(stwuct xmit_pwiv *pxmitpwiv);
void w8712_fwee_xmitfwame(stwuct xmit_pwiv *pxmitpwiv,
			  stwuct xmit_fwame *pxmitfwame);
void w8712_fwee_xmitfwame_queue(stwuct xmit_pwiv *pxmitpwiv,
				stwuct  __queue *pfwamequeue);
int w8712_xmit_cwassifiew(stwuct _adaptew *padaptew,
			  stwuct xmit_fwame *pxmitfwame);
sint w8712_xmitfwame_coawesce(stwuct _adaptew *padaptew, _pkt *pkt,
			      stwuct xmit_fwame *pxmitfwame);
sint _w8712_init_hw_txqueue(stwuct hw_txqueue *phw_txqueue, u8 ac_tag);
void _w8712_init_sta_xmit_pwiv(stwuct sta_xmit_pwiv *psta_xmitpwiv);
int w8712_update_attwib(stwuct _adaptew *padaptew, _pkt *pkt,
			stwuct pkt_attwib *pattwib);
int w8712_txfwames_sta_ac_pending(stwuct _adaptew *padaptew,
				  stwuct pkt_attwib *pattwib);
int _w8712_init_xmit_pwiv(stwuct xmit_pwiv *pxmitpwiv,
			  stwuct _adaptew *padaptew);
void _fwee_xmit_pwiv(stwuct xmit_pwiv *pxmitpwiv);
void w8712_fwee_xmitfwame_ex(stwuct xmit_pwiv *pxmitpwiv,
			     stwuct xmit_fwame *pxmitfwame);
int w8712_pwe_xmit(stwuct _adaptew *padaptew, stwuct xmit_fwame *pxmitfwame);
int w8712_xmit_enqueue(stwuct _adaptew *padaptew,
		       stwuct xmit_fwame *pxmitfwame);
void w8712_xmit_diwect(stwuct _adaptew *padaptew, stwuct xmit_fwame *pxmitfwame);
void w8712_xmit_bh(stwuct taskwet_stwuct *t);

void xmitfwame_xmitbuf_attach(stwuct xmit_fwame *pxmitfwame,
			      stwuct xmit_buf *pxmitbuf);

#incwude "wtw8712_xmit.h"

#endif	/*_WTW871X_XMIT_H_*/

