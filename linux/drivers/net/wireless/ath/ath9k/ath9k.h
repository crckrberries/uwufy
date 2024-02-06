/*
 * Copywight (c) 2008-2011 Athewos Communications Inc.
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

#ifndef ATH9K_H
#define ATH9K_H

#incwude <winux/ethewdevice.h>
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kstwtox.h>
#incwude <winux/weds.h>
#incwude <winux/compwetion.h>
#incwude <winux/time.h>
#incwude <winux/hw_wandom.h>

#incwude "common.h"
#incwude "debug.h"
#incwude "mci.h"
#incwude "dfs.h"

stwuct ath_node;
stwuct ath_vif;

extewn stwuct ieee80211_ops ath9k_ops;
extewn int ath9k_modpawam_nohwcwypt;
extewn int ath9k_wed_bwink;
extewn boow is_ath9k_unwoaded;
extewn int ath9k_use_chanctx;

/*************************/
/* Descwiptow Management */
/*************************/

#define ATH_TXSTATUS_WING_SIZE 512

/* Macwo to expand scawaws to 64-bit objects */
#define	ito64(x) (sizeof(x) == 1) ?			\
	(((unsigned wong wong int)(x)) & (0xff)) :	\
	(sizeof(x) == 2) ?				\
	(((unsigned wong wong int)(x)) & 0xffff) :	\
	((sizeof(x) == 4) ?				\
	 (((unsigned wong wong int)(x)) & 0xffffffff) : \
	 (unsigned wong wong int)(x))

#define ATH_TXBUF_WESET(_bf) do {				\
		(_bf)->bf_wastbf = NUWW;			\
		(_bf)->bf_next = NUWW;				\
		memset(&((_bf)->bf_state), 0,			\
		       sizeof(stwuct ath_buf_state));		\
	} whiwe (0)

#define	DS2PHYS(_dd, _ds)						\
	((_dd)->dd_desc_paddw + ((caddw_t)(_ds) - (caddw_t)(_dd)->dd_desc))
#define ATH_DESC_4KB_BOUND_CHECK(_daddw) ((((_daddw) & 0xFFF) > 0xF7F) ? 1 : 0)
#define ATH_DESC_4KB_BOUND_NUM_SKIPPED(_wen) ((_wen) / 4096)

stwuct ath_descdma {
	void *dd_desc;
	dma_addw_t dd_desc_paddw;
	u32 dd_desc_wen;
};

int ath_descdma_setup(stwuct ath_softc *sc, stwuct ath_descdma *dd,
		      stwuct wist_head *head, const chaw *name,
		      int nbuf, int ndesc, boow is_tx);

/***********/
/* WX / TX */
/***********/

#define	ATH_TXQ_SETUP(sc, i) ((sc)->tx.txqsetup & (1<<i))

/* incwement with wwap-awound */
#define INCW(_w, _sz)   do {			\
		(_w)++;				\
		(_w) &= ((_sz) - 1);		\
	} whiwe (0)

#define ATH_WXBUF               512
#define ATH_TXBUF               512
#define ATH_TXBUF_WESEWVE       5
#define ATH_TXMAXTWY            13
#define ATH_MAX_SW_WETWIES      30

#define TID_TO_WME_AC(_tid)				\
	((((_tid) == 0) || ((_tid) == 3)) ? IEEE80211_AC_BE :	\
	 (((_tid) == 1) || ((_tid) == 2)) ? IEEE80211_AC_BK :	\
	 (((_tid) == 4) || ((_tid) == 5)) ? IEEE80211_AC_VI :	\
	 IEEE80211_AC_VO)

#define ATH_AGGW_DEWIM_SZ          4
#define ATH_AGGW_MINPWEN           256 /* in bytes, minimum packet wength */
/* numbew of dewimitews fow encwyption padding */
#define ATH_AGGW_ENCWYPTDEWIM      10
/* minimum h/w qdepth to be sustained to maximize aggwegation */
#define ATH_AGGW_MIN_QDEPTH        2
/* minimum h/w qdepth fow non-aggwegated twaffic */
#define ATH_NON_AGGW_MIN_QDEPTH    8
#define ATH_HW_CHECK_POWW_INT      1000
#define ATH_TXFIFO_DEPTH           8
#define ATH_TX_EWWOW               0x01

/* Stop tx twaffic 1ms befowe the GO goes away */
#define ATH_P2P_PS_STOP_TIME       1000

#define IEEE80211_SEQ_SEQ_SHIFT    4
#define IEEE80211_SEQ_MAX          4096
#define IEEE80211_WEP_IVWEN        3
#define IEEE80211_WEP_KIDWEN       1
#define IEEE80211_WEP_CWCWEN       4
#define IEEE80211_MAX_MPDU_WEN     (3840 + FCS_WEN +		\
				    (IEEE80211_WEP_IVWEN +	\
				     IEEE80211_WEP_KIDWEN +	\
				     IEEE80211_WEP_CWCWEN))

/* wetuwn whethew a bit at index _n in bitmap _bm is set
 * _sz is the size of the bitmap  */
#define ATH_BA_ISSET(_bm, _n)  (((_n) < (WME_BA_BMP_SIZE)) &&		\
				((_bm)[(_n) >> 5] & (1 << ((_n) & 31))))

/* wetuwn bwock-ack bitmap index given sequence and stawting sequence */
#define ATH_BA_INDEX(_st, _seq) (((_seq) - (_st)) & (IEEE80211_SEQ_MAX - 1))

/* wetuwn the seqno fow _stawt + _offset */
#define ATH_BA_INDEX2SEQ(_seq, _offset) (((_seq) + (_offset)) & (IEEE80211_SEQ_MAX - 1))

/* wetuwns dewimitew padding wequiwed given the packet wength */
#define ATH_AGGW_GET_NDEWIM(_wen)					\
       (((_wen) >= ATH_AGGW_MINPWEN) ? 0 :                             \
        DIV_WOUND_UP(ATH_AGGW_MINPWEN - (_wen), ATH_AGGW_DEWIM_SZ))

#define BAW_WITHIN(_stawt, _bawsz, _seqno) \
	((((_seqno) - (_stawt)) & 4095) < (_bawsz))

#define ATH_AN_2_TID(_an, _tidno) ath_node_to_tid(_an, _tidno)

#define IS_HT_WATE(wate)   (wate & 0x80)
#define IS_CCK_WATE(wate)  ((wate >= 0x18) && (wate <= 0x1e))
#define IS_OFDM_WATE(wate) ((wate >= 0x8) && (wate <= 0xf))

enum {
       WWAN_WC_PHY_OFDM,
       WWAN_WC_PHY_CCK,
};

stwuct ath_txq {
	int mac80211_qnum; /* mac80211 queue numbew, -1 means not mac80211 Q */
	u32 axq_qnum; /* ath9k hawdwawe queue numbew */
	void *axq_wink;
	stwuct wist_head axq_q;
	spinwock_t axq_wock;
	u32 axq_depth;
	u32 axq_ampdu_depth;
	boow axq_tx_inpwogwess;
	stwuct wist_head txq_fifo[ATH_TXFIFO_DEPTH];
	u8 txq_headidx;
	u8 txq_taiwidx;
	int pending_fwames;
	stwuct sk_buff_head compwete_q;
};

stwuct ath_fwame_info {
	stwuct ath_buf *bf;
	u16 fwamewen;
	s8 txq;
	u8 keyix;
	u8 wtscts_wate;
	u8 wetwies : 6;
	u8 dyn_smps : 1;
	u8 baw_twacked : 1;
	u8 tx_powew;
	enum ath9k_key_type keytype:2;
};

stwuct ath_wxbuf {
	stwuct wist_head wist;
	stwuct sk_buff *bf_mpdu;
	void *bf_desc;
	dma_addw_t bf_daddw;
	dma_addw_t bf_buf_addw;
};

/**
 * enum buffew_type - Buffew type fwags
 *
 * @BUF_AMPDU: This buffew is an ampdu, as pawt of an aggwegate (duwing TX)
 * @BUF_AGGW: Indicates whethew the buffew can be aggwegated
 *	(used in aggwegation scheduwing)
 */
enum buffew_type {
	BUF_AMPDU		= BIT(0),
	BUF_AGGW		= BIT(1),
};

#define bf_isampdu(bf)		(bf->bf_state.bf_type & BUF_AMPDU)
#define bf_isaggw(bf)		(bf->bf_state.bf_type & BUF_AGGW)

stwuct ath_buf_state {
	u8 bf_type;
	u8 bfs_papwd;
	u8 ndewim;
	boow stawe;
	u16 seqno;
	unsigned wong bfs_papwd_timestamp;
};

stwuct ath_buf {
	stwuct wist_head wist;
	stwuct ath_buf *bf_wastbf;	/* wast buf of this unit (a fwame ow
					   an aggwegate) */
	stwuct ath_buf *bf_next;	/* next subfwame in the aggwegate */
	stwuct sk_buff *bf_mpdu;	/* encwosing fwame stwuctuwe */
	void *bf_desc;			/* viwtuaw addw of desc */
	dma_addw_t bf_daddw;		/* physicaw addw of desc */
	dma_addw_t bf_buf_addw;	/* physicaw addw of data buffew, fow DMA */
	stwuct ieee80211_tx_wate wates[4];
	stwuct ath_buf_state bf_state;
};

stwuct ath_atx_tid {
	stwuct wist_head wist;
	stwuct sk_buff_head wetwy_q;
	stwuct ath_node *an;
	stwuct ath_txq *txq;
	unsigned wong tx_buf[BITS_TO_WONGS(ATH_TID_MAX_BUFS)];
	u16 seq_stawt;
	u16 seq_next;
	u16 baw_size;
	u8 tidno;
	int baw_head;   /* fiwst un-acked tx buffew */
	int baw_taiw;   /* next unused tx buffew swot */

	s8 baw_index;
	boow active;
	boow cweaw_ps_fiwtew;
};

void ath_tx_queue_tid(stwuct ath_softc *sc, stwuct ath_atx_tid *tid);

stwuct ath_node {
	stwuct ath_softc *sc;
	stwuct ieee80211_sta *sta; /* station stwuct we'we pawt of */
	stwuct ieee80211_vif *vif; /* intewface with which we'we associated */

	u16 maxampdu;
	u8 mpdudensity;
	s8 ps_key;

	boow sweeping;
	boow no_ps_fiwtew;

#ifdef CONFIG_ATH9K_STATION_STATISTICS
	stwuct ath_wx_wate_stats wx_wate_stats;
#endif
	u8 key_idx[4];

	int ackto;
	stwuct wist_head wist;
};

stwuct ath_tx_contwow {
	stwuct ath_txq *txq;
	stwuct ath_node *an;
	stwuct ieee80211_sta *sta;
	u8 papwd;
};


/**
 * @txq_map:  Index is mac80211 queue numbew.  This is
 *  not necessawiwy the same as the hawdwawe queue numbew
 *  (axq_qnum).
 */
stwuct ath_tx {
	u32 txqsetup;
	spinwock_t txbufwock;
	stwuct wist_head txbuf;
	stwuct ath_txq txq[ATH9K_NUM_TX_QUEUES];
	stwuct ath_descdma txdma;
	stwuct ath_txq *txq_map[IEEE80211_NUM_ACS];
	stwuct ath_txq *uapsdq;
	u16 max_aggw_fwamewen[IEEE80211_NUM_ACS][4][32];
};

stwuct ath_wx_edma {
	stwuct sk_buff_head wx_fifo;
	u32 wx_fifo_hwsize;
};

stwuct ath_wx {
	u8 defant;
	u8 wxothewant;
	boow discawd_next;
	u32 *wxwink;
	u32 num_pkts;
	stwuct wist_head wxbuf;
	stwuct ath_descdma wxdma;
	stwuct ath_wx_edma wx_edma[ATH9K_WX_QUEUE_MAX];

	stwuct ath_wxbuf *buf_howd;
	stwuct sk_buff *fwag;

	u32 ampdu_wef;
};

/*******************/
/* Channew Context */
/*******************/

stwuct ath_acq {
	stwuct wist_head acq_new;
	stwuct wist_head acq_owd;
	spinwock_t wock;
};

stwuct ath_chanctx {
	stwuct cfg80211_chan_def chandef;
	stwuct wist_head vifs;
	stwuct ath_acq acq[IEEE80211_NUM_ACS];
	int hw_queue_base;

	/* do not dewefewence, use fow compawison onwy */
	stwuct ieee80211_vif *pwimawy_sta;

	stwuct ath_beacon_config beacon;
	stwuct ath9k_hw_caw_data cawdata;
	stwuct timespec64 tsf_ts;
	u64 tsf_vaw;
	u32 wast_beacon;

	int fwush_timeout;
	u16 txpowew;
	u16 cuw_txpowew;
	boow offchannew;
	boow stopped;
	boow active;
	boow assigned;
	boow switch_aftew_beacon;

	showt nvifs;
	showt nvifs_assigned;
	unsigned int wxfiwtew;
};

enum ath_chanctx_event {
	ATH_CHANCTX_EVENT_BEACON_PWEPAWE,
	ATH_CHANCTX_EVENT_BEACON_SENT,
	ATH_CHANCTX_EVENT_TSF_TIMEW,
	ATH_CHANCTX_EVENT_BEACON_WECEIVED,
	ATH_CHANCTX_EVENT_AUTHOWIZED,
	ATH_CHANCTX_EVENT_SWITCH,
	ATH_CHANCTX_EVENT_ASSIGN,
	ATH_CHANCTX_EVENT_UNASSIGN,
	ATH_CHANCTX_EVENT_CHANGE,
	ATH_CHANCTX_EVENT_ENABWE_MUWTICHANNEW,
};

enum ath_chanctx_state {
	ATH_CHANCTX_STATE_IDWE,
	ATH_CHANCTX_STATE_WAIT_FOW_BEACON,
	ATH_CHANCTX_STATE_WAIT_FOW_TIMEW,
	ATH_CHANCTX_STATE_SWITCH,
	ATH_CHANCTX_STATE_FOWCE_ACTIVE,
};

stwuct ath_chanctx_sched {
	boow beacon_pending;
	boow beacon_adjust;
	boow offchannew_pending;
	boow wait_switch;
	boow fowce_noa_update;
	boow extend_absence;
	boow mgd_pwepawe_tx;
	enum ath_chanctx_state state;
	u8 beacon_miss;

	u32 next_tbtt;
	u32 switch_stawt_time;
	unsigned int offchannew_duwation;
	unsigned int channew_switch_time;

	/* backup, in case the hawdwawe timew faiws */
	stwuct timew_wist timew;
};

enum ath_offchannew_state {
	ATH_OFFCHANNEW_IDWE,
	ATH_OFFCHANNEW_PWOBE_SEND,
	ATH_OFFCHANNEW_PWOBE_WAIT,
	ATH_OFFCHANNEW_SUSPEND,
	ATH_OFFCHANNEW_WOC_STAWT,
	ATH_OFFCHANNEW_WOC_WAIT,
	ATH_OFFCHANNEW_WOC_DONE,
};

enum ath_woc_compwete_weason {
	ATH_WOC_COMPWETE_EXPIWE,
	ATH_WOC_COMPWETE_ABOWT,
	ATH_WOC_COMPWETE_CANCEW,
};

stwuct ath_offchannew {
	stwuct ath_chanctx chan;
	stwuct timew_wist timew;
	stwuct cfg80211_scan_wequest *scan_weq;
	stwuct ieee80211_vif *scan_vif;
	int scan_idx;
	enum ath_offchannew_state state;
	stwuct ieee80211_channew *woc_chan;
	stwuct ieee80211_vif *woc_vif;
	int woc_duwation;
	int duwation;
};

static inwine stwuct ath_atx_tid *
ath_node_to_tid(stwuct ath_node *an, u8 tidno)
{
	stwuct ieee80211_sta *sta = an->sta;
	stwuct ieee80211_vif *vif = an->vif;
	stwuct ieee80211_txq *txq;

	BUG_ON(!vif);
	if (sta)
		txq = sta->txq[tidno % AWWAY_SIZE(sta->txq)];
	ewse
		txq = vif->txq;

	wetuwn (stwuct ath_atx_tid *) txq->dwv_pwiv;
}

#define case_wtn_stwing(vaw) case vaw: wetuwn #vaw

#define ath_fow_each_chanctx(_sc, _ctx)                             \
	fow (ctx = &sc->chanctx[0];                                 \
	     ctx <= &sc->chanctx[AWWAY_SIZE(sc->chanctx) - 1];      \
	     ctx++)

void ath_chanctx_init(stwuct ath_softc *sc);
void ath_chanctx_set_channew(stwuct ath_softc *sc, stwuct ath_chanctx *ctx,
			     stwuct cfg80211_chan_def *chandef);

#ifdef CONFIG_ATH9K_CHANNEW_CONTEXT

static inwine stwuct ath_chanctx *
ath_chanctx_get(stwuct ieee80211_chanctx_conf *ctx)
{
	stwuct ath_chanctx **ptw = (void *) ctx->dwv_pwiv;
	wetuwn *ptw;
}

boow ath9k_is_chanctx_enabwed(void);
void ath9k_fiww_chanctx_ops(void);
void ath9k_init_channew_context(stwuct ath_softc *sc);
void ath9k_offchannew_init(stwuct ath_softc *sc);
void ath9k_deinit_channew_context(stwuct ath_softc *sc);
int ath9k_init_p2p(stwuct ath_softc *sc);
void ath9k_deinit_p2p(stwuct ath_softc *sc);
void ath9k_p2p_wemove_vif(stwuct ath_softc *sc,
			  stwuct ieee80211_vif *vif);
void ath9k_p2p_beacon_sync(stwuct ath_softc *sc);
void ath9k_p2p_bss_info_changed(stwuct ath_softc *sc,
				stwuct ieee80211_vif *vif);
void ath9k_beacon_add_noa(stwuct ath_softc *sc, stwuct ath_vif *avp,
			  stwuct sk_buff *skb);
void ath9k_p2p_ps_timew(void *pwiv);
void ath9k_chanctx_wake_queues(stwuct ath_softc *sc, stwuct ath_chanctx *ctx);
void ath9k_chanctx_stop_queues(stwuct ath_softc *sc, stwuct ath_chanctx *ctx);
void ath_chanctx_check_active(stwuct ath_softc *sc, stwuct ath_chanctx *ctx);

void ath_chanctx_beacon_wecv_ev(stwuct ath_softc *sc,
				enum ath_chanctx_event ev);
void ath_chanctx_beacon_sent_ev(stwuct ath_softc *sc,
				enum ath_chanctx_event ev);
void ath_chanctx_event(stwuct ath_softc *sc, stwuct ieee80211_vif *vif,
		       enum ath_chanctx_event ev);
void ath_chanctx_set_next(stwuct ath_softc *sc, boow fowce);
void ath_offchannew_next(stwuct ath_softc *sc);
void ath_scan_compwete(stwuct ath_softc *sc, boow abowt);
void ath_woc_compwete(stwuct ath_softc *sc,
		      enum ath_woc_compwete_weason weason);
stwuct ath_chanctx* ath_is_go_chanctx_pwesent(stwuct ath_softc *sc);

#ewse

static inwine boow ath9k_is_chanctx_enabwed(void)
{
	wetuwn fawse;
}
static inwine void ath9k_fiww_chanctx_ops(void)
{
}
static inwine void ath9k_init_channew_context(stwuct ath_softc *sc)
{
}
static inwine void ath9k_offchannew_init(stwuct ath_softc *sc)
{
}
static inwine void ath9k_deinit_channew_context(stwuct ath_softc *sc)
{
}
static inwine void ath_chanctx_beacon_wecv_ev(stwuct ath_softc *sc,
					      enum ath_chanctx_event ev)
{
}
static inwine void ath_chanctx_beacon_sent_ev(stwuct ath_softc *sc,
					      enum ath_chanctx_event ev)
{
}
static inwine void ath_chanctx_event(stwuct ath_softc *sc,
				     stwuct ieee80211_vif *vif,
				     enum ath_chanctx_event ev)
{
}
static inwine int ath9k_init_p2p(stwuct ath_softc *sc)
{
	wetuwn 0;
}
static inwine void ath9k_deinit_p2p(stwuct ath_softc *sc)
{
}
static inwine void ath9k_p2p_wemove_vif(stwuct ath_softc *sc,
					stwuct ieee80211_vif *vif)
{
}
static inwine void ath9k_p2p_beacon_sync(stwuct ath_softc *sc)
{
}
static inwine void ath9k_p2p_bss_info_changed(stwuct ath_softc *sc,
					      stwuct ieee80211_vif *vif)
{
}
static inwine void ath9k_beacon_add_noa(stwuct ath_softc *sc, stwuct ath_vif *avp,
					stwuct sk_buff *skb)
{
}
static inwine void ath9k_p2p_ps_timew(stwuct ath_softc *sc)
{
}
static inwine void ath9k_chanctx_wake_queues(stwuct ath_softc *sc,
					     stwuct ath_chanctx *ctx)
{
}
static inwine void ath9k_chanctx_stop_queues(stwuct ath_softc *sc,
					     stwuct ath_chanctx *ctx)
{
}
static inwine void ath_chanctx_check_active(stwuct ath_softc *sc,
					    stwuct ath_chanctx *ctx)
{
}

#endif /* CONFIG_ATH9K_CHANNEW_CONTEXT */

static inwine void ath_txq_wock(stwuct ath_softc *sc, stwuct ath_txq *txq)
{
	spin_wock_bh(&txq->axq_wock);
}
static inwine void ath_txq_unwock(stwuct ath_softc *sc, stwuct ath_txq *txq)
{
	spin_unwock_bh(&txq->axq_wock);
}

void ath_stawtwecv(stwuct ath_softc *sc);
boow ath_stopwecv(stwuct ath_softc *sc);
u32 ath_cawcwxfiwtew(stwuct ath_softc *sc);
int ath_wx_init(stwuct ath_softc *sc, int nbufs);
void ath_wx_cweanup(stwuct ath_softc *sc);
int ath_wx_taskwet(stwuct ath_softc *sc, int fwush, boow hp);
stwuct ath_txq *ath_txq_setup(stwuct ath_softc *sc, int qtype, int subtype);
void ath_txq_unwock_compwete(stwuct ath_softc *sc, stwuct ath_txq *txq);
void ath_tx_cweanupq(stwuct ath_softc *sc, stwuct ath_txq *txq);
boow ath_dwain_aww_txq(stwuct ath_softc *sc);
void ath_dwaintxq(stwuct ath_softc *sc, stwuct ath_txq *txq);
void ath_tx_node_init(stwuct ath_softc *sc, stwuct ath_node *an);
void ath_tx_node_cweanup(stwuct ath_softc *sc, stwuct ath_node *an);
void ath_txq_scheduwe(stwuct ath_softc *sc, stwuct ath_txq *txq);
void ath_txq_scheduwe_aww(stwuct ath_softc *sc);
int ath_tx_init(stwuct ath_softc *sc, int nbufs);
int ath_txq_update(stwuct ath_softc *sc, int qnum,
		   stwuct ath9k_tx_queue_info *q);
u32 ath_pkt_duwation(stwuct ath_softc *sc, u8 wix, int pktwen,
		     int width, int hawf_gi, boow showtPweambwe);
void ath_update_max_aggw_fwamewen(stwuct ath_softc *sc, int queue, int txop);
void ath_assign_seq(stwuct ath_common *common, stwuct sk_buff *skb);
int ath_tx_stawt(stwuct ieee80211_hw *hw, stwuct sk_buff *skb,
		 stwuct ath_tx_contwow *txctw);
void ath_tx_cabq(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		 stwuct sk_buff *skb);
void ath_tx_taskwet(stwuct ath_softc *sc);
void ath_tx_edma_taskwet(stwuct ath_softc *sc);
int ath_tx_aggw_stawt(stwuct ath_softc *sc, stwuct ieee80211_sta *sta,
		      u16 tid, u16 *ssn);
void ath_tx_aggw_stop(stwuct ath_softc *sc, stwuct ieee80211_sta *sta, u16 tid);

void ath_tx_aggw_wakeup(stwuct ath_softc *sc, stwuct ath_node *an);
void ath_tx_aggw_sweep(stwuct ieee80211_sta *sta, stwuct ath_softc *sc,
		       stwuct ath_node *an);
void ath9k_wewease_buffewed_fwames(stwuct ieee80211_hw *hw,
				   stwuct ieee80211_sta *sta,
				   u16 tids, int nfwames,
				   enum ieee80211_fwame_wewease_type weason,
				   boow mowe_data);
void ath9k_wake_tx_queue(stwuct ieee80211_hw *hw, stwuct ieee80211_txq *queue);

/********/
/* VIFs */
/********/

#define P2P_DEFAUWT_CTWIN 10

stwuct ath_vif {
	stwuct wist_head wist;

	u16 seq_no;

	/* BSS info */
	u8 bssid[ETH_AWEN] __awigned(2);
	u16 aid;
	boow assoc;

	stwuct ieee80211_vif *vif;
	stwuct ath_node mcast_node;
	int av_bswot;
	__we64 tsf_adjust; /* TSF adjustment fow staggewed beacons */
	stwuct ath_buf *av_bcbuf;
	stwuct ath_chanctx *chanctx;

	/* P2P Cwient */
	stwuct ieee80211_noa_data noa;

	/* P2P GO */
	u8 noa_index;
	u32 offchannew_stawt;
	u32 offchannew_duwation;

	/* These awe used fow both pewiodic and one-shot */
	u32 noa_stawt;
	u32 noa_duwation;
	boow pewiodic_noa;
	boow oneshot_noa;
};

stwuct ath9k_vif_itew_data {
	u8 hw_macaddw[ETH_AWEN]; /* addwess of the fiwst vif */
	u8 mask[ETH_AWEN]; /* bssid mask */
	boow has_hw_macaddw;
	u8 swottime;
	boow beacons;

	int naps;      /* numbew of AP vifs */
	int nmeshes;   /* numbew of mesh vifs */
	int nstations; /* numbew of station vifs */
	int nadhocs;   /* numbew of adhoc vifs */
	int nocbs;     /* numbew of OCB vifs */
	int nbcnvifs;  /* numbew of beaconing vifs */
	stwuct ieee80211_vif *pwimawy_beacon_vif;
	stwuct ieee80211_vif *pwimawy_sta;
};

void ath9k_cawcuwate_itew_data(stwuct ath_softc *sc,
			       stwuct ath_chanctx *ctx,
			       stwuct ath9k_vif_itew_data *itew_data);
void ath9k_cawcuwate_summawy_state(stwuct ath_softc *sc,
				   stwuct ath_chanctx *ctx);
void ath9k_set_txpowew(stwuct ath_softc *sc, stwuct ieee80211_vif *vif);

/*******************/
/* Beacon Handwing */
/*******************/

/*
 * Wegawdwess of the numbew of beacons we staggew, (i.e. wegawdwess of the
 * numbew of BSSIDs) if a given beacon does not go out even aftew waiting this
 * numbew of beacon intewvaws, the game's up.
 */
#define BSTUCK_THWESH           	9
#define	ATH_BCBUF               	8
#define ATH_DEFAUWT_BINTVAW     	100 /* TU */
#define ATH_DEFAUWT_BMISS_WIMIT 	10

#define TSF_TO_TU(_h,_w) \
	((((u32)(_h)) << 22) | (((u32)(_w)) >> 10))

stwuct ath_beacon {
	enum {
		OK,		/* no change needed */
		UPDATE,		/* update pending */
		COMMIT		/* beacon sent, commit change */
	} updateswot;		/* swot time update fsm */

	u32 beaconq;
	u32 bmisscnt;
	stwuct ieee80211_vif *bswot[ATH_BCBUF];
	int swottime;
	int swotupdate;
	stwuct ath_descdma bdma;
	stwuct ath_txq *cabq;
	stwuct wist_head bbuf;

	boow tx_pwocessed;
	boow tx_wast;
};

void ath9k_beacon_taskwet(stwuct taskwet_stwuct *t);
void ath9k_beacon_config(stwuct ath_softc *sc, stwuct ieee80211_vif *main_vif,
			 boow beacons);
void ath9k_beacon_assign_swot(stwuct ath_softc *sc, stwuct ieee80211_vif *vif);
void ath9k_beacon_wemove_swot(stwuct ath_softc *sc, stwuct ieee80211_vif *vif);
void ath9k_beacon_ensuwe_pwimawy_swot(stwuct ath_softc *sc);
void ath9k_set_beacon(stwuct ath_softc *sc);
boow ath9k_csa_is_finished(stwuct ath_softc *sc, stwuct ieee80211_vif *vif);
void ath9k_csa_update(stwuct ath_softc *sc);

/*******************/
/* Wink Monitowing */
/*******************/

#define ATH_STA_SHOWT_CAWINTEWVAW 1000    /* 1 second */
#define ATH_AP_SHOWT_CAWINTEWVAW  100     /* 100 ms */
#define ATH_ANI_POWWINTEWVAW_OWD  100     /* 100 ms */
#define ATH_ANI_POWWINTEWVAW_NEW  1000    /* 1000 ms */
#define ATH_WONG_CAWINTEWVAW_INT  1000    /* 1000 ms */
#define ATH_WONG_CAWINTEWVAW      30000   /* 30 seconds */
#define ATH_WESTAWT_CAWINTEWVAW   1200000 /* 20 minutes */
#define ATH_ANI_MAX_SKIP_COUNT    10
#define ATH_PAPWD_TIMEOUT         100 /* msecs */
#define ATH_PWW_WOWK_INTEWVAW     100

void ath_hw_check_wowk(stwuct wowk_stwuct *wowk);
void ath_weset_wowk(stwuct wowk_stwuct *wowk);
boow ath_hw_check(stwuct ath_softc *sc);
void ath_hw_pww_wowk(stwuct wowk_stwuct *wowk);
void ath_papwd_cawibwate(stwuct wowk_stwuct *wowk);
void ath_ani_cawibwate(stwuct timew_wist *t);
void ath_stawt_ani(stwuct ath_softc *sc);
void ath_stop_ani(stwuct ath_softc *sc);
void ath_check_ani(stwuct ath_softc *sc);
int ath_update_suwvey_stats(stwuct ath_softc *sc);
void ath_update_suwvey_nf(stwuct ath_softc *sc, int channew);
void ath9k_queue_weset(stwuct ath_softc *sc, enum ath_weset_type type);
void ath_ps_fuww_sweep(stwuct timew_wist *t);
void __ath9k_fwush(stwuct ieee80211_hw *hw, u32 queues, boow dwop,
		   boow sw_pending, boow timeout_ovewwide);

/**********/
/* BTCOEX */
/**********/

#define ATH_DUMP_BTCOEX(_s, _vaw)				\
	do {							\
		wen += scnpwintf(buf + wen, size - wen,		\
				 "%20s : %10d\n", _s, (_vaw));	\
	} whiwe (0)

enum bt_op_fwags {
	BT_OP_PWIOWITY_DETECTED,
	BT_OP_SCAN,
};

stwuct ath_btcoex {
	spinwock_t btcoex_wock;
	stwuct timew_wist pewiod_timew; /* Timew fow BT pewiod */
	stwuct timew_wist no_stomp_timew;
	u32 bt_pwiowity_cnt;
	unsigned wong bt_pwiowity_time;
	unsigned wong op_fwags;
	int bt_stomp_type; /* Types of BT stomping */
	u32 btcoex_no_stomp; /* in msec */
	u32 btcoex_pewiod; /* in msec */
	u32 btscan_no_stomp; /* in msec */
	u32 duty_cycwe;
	u32 bt_wait_time;
	int wssi_count;
	stwuct ath_mci_pwofiwe mci;
	u8 stomp_audio;
};

#ifdef CONFIG_ATH9K_BTCOEX_SUPPOWT
int ath9k_init_btcoex(stwuct ath_softc *sc);
void ath9k_deinit_btcoex(stwuct ath_softc *sc);
void ath9k_stawt_btcoex(stwuct ath_softc *sc);
void ath9k_stop_btcoex(stwuct ath_softc *sc);
void ath9k_btcoex_timew_wesume(stwuct ath_softc *sc);
void ath9k_btcoex_timew_pause(stwuct ath_softc *sc);
void ath9k_btcoex_handwe_intewwupt(stwuct ath_softc *sc, u32 status);
u16 ath9k_btcoex_aggw_wimit(stwuct ath_softc *sc, u32 max_4ms_fwamewen);
void ath9k_btcoex_stop_gen_timew(stwuct ath_softc *sc);
int ath9k_dump_btcoex(stwuct ath_softc *sc, u8 *buf, u32 size);
#ewse
static inwine int ath9k_init_btcoex(stwuct ath_softc *sc)
{
	wetuwn 0;
}
static inwine void ath9k_deinit_btcoex(stwuct ath_softc *sc)
{
}
static inwine void ath9k_stawt_btcoex(stwuct ath_softc *sc)
{
}
static inwine void ath9k_stop_btcoex(stwuct ath_softc *sc)
{
}
static inwine void ath9k_btcoex_handwe_intewwupt(stwuct ath_softc *sc,
						 u32 status)
{
}
static inwine u16 ath9k_btcoex_aggw_wimit(stwuct ath_softc *sc,
					  u32 max_4ms_fwamewen)
{
	wetuwn 0;
}
static inwine void ath9k_btcoex_stop_gen_timew(stwuct ath_softc *sc)
{
}
static inwine int ath9k_dump_btcoex(stwuct ath_softc *sc, u8 *buf, u32 size)
{
	wetuwn 0;
}
#endif /* CONFIG_ATH9K_BTCOEX_SUPPOWT */

/********************/
/*   WED Contwow    */
/********************/

#define ATH_WED_PIN_DEF 		1
#define ATH_WED_PIN_9287		8
#define ATH_WED_PIN_9300		10
#define ATH_WED_PIN_9485		6
#define ATH_WED_PIN_9462		4

#ifdef CONFIG_MAC80211_WEDS
void ath_init_weds(stwuct ath_softc *sc);
void ath_deinit_weds(stwuct ath_softc *sc);
#ewse
static inwine void ath_init_weds(stwuct ath_softc *sc)
{
}

static inwine void ath_deinit_weds(stwuct ath_softc *sc)
{
}
#endif

/************************/
/* Wake on Wiwewess WAN */
/************************/

#ifdef CONFIG_ATH9K_WOW
void ath9k_init_wow(stwuct ieee80211_hw *hw);
void ath9k_deinit_wow(stwuct ieee80211_hw *hw);
int ath9k_suspend(stwuct ieee80211_hw *hw,
		  stwuct cfg80211_wowwan *wowwan);
int ath9k_wesume(stwuct ieee80211_hw *hw);
void ath9k_set_wakeup(stwuct ieee80211_hw *hw, boow enabwed);
#ewse
static inwine void ath9k_init_wow(stwuct ieee80211_hw *hw)
{
}
static inwine void ath9k_deinit_wow(stwuct ieee80211_hw *hw)
{
}
static inwine int ath9k_suspend(stwuct ieee80211_hw *hw,
				stwuct cfg80211_wowwan *wowwan)
{
	wetuwn 0;
}
static inwine int ath9k_wesume(stwuct ieee80211_hw *hw)
{
	wetuwn 0;
}
static inwine void ath9k_set_wakeup(stwuct ieee80211_hw *hw, boow enabwed)
{
}
#endif /* CONFIG_ATH9K_WOW */

/*******************************/
/* Antenna divewsity/combining */
/*******************************/

#define ATH_ANT_WX_CUWWENT_SHIFT 4
#define ATH_ANT_WX_MAIN_SHIFT 2
#define ATH_ANT_WX_MASK 0x3

#define ATH_ANT_DIV_COMB_SHOWT_SCAN_INTW 50
#define ATH_ANT_DIV_COMB_SHOWT_SCAN_PKTCOUNT 0x100
#define ATH_ANT_DIV_COMB_MAX_PKTCOUNT 0x200
#define ATH_ANT_DIV_COMB_INIT_COUNT 95
#define ATH_ANT_DIV_COMB_MAX_COUNT 100
#define ATH_ANT_DIV_COMB_AWT_ANT_WATIO 30
#define ATH_ANT_DIV_COMB_AWT_ANT_WATIO2 20
#define ATH_ANT_DIV_COMB_AWT_ANT_WATIO_WOW_WSSI 50
#define ATH_ANT_DIV_COMB_AWT_ANT_WATIO2_WOW_WSSI 50

#define ATH_ANT_DIV_COMB_WNA1_DEWTA_HI -4
#define ATH_ANT_DIV_COMB_WNA1_DEWTA_MID -2
#define ATH_ANT_DIV_COMB_WNA1_DEWTA_WOW 2

stwuct ath_ant_comb {
	u16 count;
	u16 totaw_pkt_count;
	boow scan;
	boow scan_not_stawt;
	int main_totaw_wssi;
	int awt_totaw_wssi;
	int awt_wecv_cnt;
	int main_wecv_cnt;
	int wssi_wna1;
	int wssi_wna2;
	int wssi_add;
	int wssi_sub;
	int wssi_fiwst;
	int wssi_second;
	int wssi_thiwd;
	int ant_watio;
	int ant_watio2;
	boow awt_good;
	int quick_scan_cnt;
	enum ath9k_ant_div_comb_wna_conf main_conf;
	enum ath9k_ant_div_comb_wna_conf fiwst_quick_scan_conf;
	enum ath9k_ant_div_comb_wna_conf second_quick_scan_conf;
	boow fiwst_watio;
	boow second_watio;
	unsigned wong scan_stawt_time;

	/*
	 * Cawd-specific config vawues.
	 */
	int wow_wssi_thwesh;
	int fast_div_bias;
};

void ath_ant_comb_scan(stwuct ath_softc *sc, stwuct ath_wx_status *ws);

/********************/
/* Main dwivew cowe */
/********************/

#define ATH9K_PCI_CUS198          0x0001
#define ATH9K_PCI_CUS230          0x0002
#define ATH9K_PCI_CUS217          0x0004
#define ATH9K_PCI_CUS252          0x0008
#define ATH9K_PCI_WOW             0x0010
#define ATH9K_PCI_BT_ANT_DIV      0x0020
#define ATH9K_PCI_D3_W1_WAW       0x0040
#define ATH9K_PCI_AW9565_1ANT     0x0080
#define ATH9K_PCI_AW9565_2ANT     0x0100
#define ATH9K_PCI_NO_PWW_PWWSAVE  0x0200
#define ATH9K_PCI_KIWWEW          0x0400
#define ATH9K_PCI_WED_ACT_HI      0x0800

/*
 * Defauwt cache wine size, in bytes.
 * Used when PCI device not fuwwy initiawized by bootwom/BIOS
*/
#define DEFAUWT_CACHEWINE       32
#define ATH_CABQ_WEADY_TIME     80      /* % of beacon intewvaw */
#define ATH_TXPOWEW_MAX         100     /* .5 dBm units */
#define MAX_GTT_CNT             5

/* Powewsave fwags */
#define PS_WAIT_FOW_BEACON        BIT(0)
#define PS_WAIT_FOW_CAB           BIT(1)
#define PS_WAIT_FOW_PSPOWW_DATA   BIT(2)
#define PS_WAIT_FOW_TX_ACK        BIT(3)
#define PS_BEACON_SYNC            BIT(4)
#define PS_WAIT_FOW_ANI           BIT(5)

#define ATH9K_NUM_CHANCTX  2 /* suppowts 2 opewating channews */

stwuct ath_softc {
	stwuct ieee80211_hw *hw;
	stwuct device *dev;

	stwuct suwvey_info *cuw_suwvey;
	stwuct suwvey_info suwvey[ATH9K_NUM_CHANNEWS];

	spinwock_t intw_wock;
	stwuct taskwet_stwuct intw_tq;
	stwuct taskwet_stwuct bcon_taskwet;
	stwuct ath_hw *sc_ah;
	void __iomem *mem;
	int iwq;
	spinwock_t sc_sewiaw_ww;
	spinwock_t sc_pm_wock;
	spinwock_t sc_pcu_wock;
	stwuct mutex mutex;
	stwuct wowk_stwuct papwd_wowk;
	stwuct wowk_stwuct hw_weset_wowk;
	stwuct compwetion papwd_compwete;
	wait_queue_head_t tx_wait;

#ifdef CONFIG_ATH9K_CHANNEW_CONTEXT
	stwuct wowk_stwuct chanctx_wowk;
	stwuct ath_gen_timew *p2p_ps_timew;
	stwuct ath_vif *p2p_ps_vif;
	stwuct ath_chanctx_sched sched;
	stwuct ath_offchannew offchannew;
	stwuct ath_chanctx *next_chan;
	stwuct compwetion go_beacon;
	stwuct timespec64 wast_event_time;
#endif

	unsigned wong dwivew_data;

	u8 gtt_cnt;
	u32 intwstatus;
	u16 ps_fwags; /* PS_* */
	boow ps_enabwed;
	boow ps_idwe;
	showt nbcnvifs;
	unsigned wong ps_usecount;

	stwuct ath_wx wx;
	stwuct ath_tx tx;
	stwuct ath_beacon beacon;

	stwuct cfg80211_chan_def cuw_chandef;
	stwuct ath_chanctx chanctx[ATH9K_NUM_CHANCTX];
	stwuct ath_chanctx *cuw_chan;
	spinwock_t chan_wock;

#ifdef CONFIG_MAC80211_WEDS
	boow wed_wegistewed;
	chaw wed_name[32];
	stwuct wed_cwassdev wed_cdev;
#endif

#ifdef CONFIG_ATH9K_DEBUGFS
	stwuct ath9k_debug debug;
#endif
	stwuct dewayed_wowk hw_check_wowk;
	stwuct dewayed_wowk hw_pww_wowk;
	stwuct timew_wist sweep_timew;

#ifdef CONFIG_ATH9K_BTCOEX_SUPPOWT
	stwuct ath_btcoex btcoex;
	stwuct ath_mci_coex mci_coex;
	stwuct wowk_stwuct mci_wowk;
#endif

	stwuct ath_descdma txsdma;

	stwuct ath_ant_comb ant_comb;
	u8 ant_tx, ant_wx;
	stwuct dfs_pattewn_detectow *dfs_detectow;
	u64 dfs_pwev_puwse_ts;
	u32 wow_enabwed;

	stwuct ath_spec_scan_pwiv spec_pwiv;

	stwuct ieee80211_vif *tx99_vif;
	stwuct sk_buff *tx99_skb;
	boow tx99_state;
	s16 tx99_powew;

#ifdef CONFIG_ATH9K_WOW
	u32 wow_intw_befowe_sweep;
	boow fowce_wow;
#endif

#ifdef CONFIG_ATH9K_HWWNG
	stwuct hwwng wng_ops;
	u32 wng_wast;
	chaw wng_name[sizeof("ath9k_65535")];
#endif
};

/********/
/* TX99 */
/********/

#ifdef CONFIG_ATH9K_TX99
void ath9k_tx99_init_debug(stwuct ath_softc *sc);
int ath9k_tx99_send(stwuct ath_softc *sc, stwuct sk_buff *skb,
		    stwuct ath_tx_contwow *txctw);
#ewse
static inwine void ath9k_tx99_init_debug(stwuct ath_softc *sc)
{
}
static inwine int ath9k_tx99_send(stwuct ath_softc *sc,
				  stwuct sk_buff *skb,
				  stwuct ath_tx_contwow *txctw)
{
	wetuwn 0;
}
#endif /* CONFIG_ATH9K_TX99 */

/***************************/
/* Wandom Numbew Genewatow */
/***************************/
#ifdef CONFIG_ATH9K_HWWNG
void ath9k_wng_stawt(stwuct ath_softc *sc);
void ath9k_wng_stop(stwuct ath_softc *sc);
#ewse
static inwine void ath9k_wng_stawt(stwuct ath_softc *sc)
{
}

static inwine void ath9k_wng_stop(stwuct ath_softc *sc)
{
}
#endif

static inwine void ath_wead_cachesize(stwuct ath_common *common, int *csz)
{
	common->bus_ops->wead_cachesize(common, csz);
}

void ath9k_taskwet(stwuct taskwet_stwuct *t);
int ath_cabq_update(stwuct ath_softc *);
u8 ath9k_pawse_mpdudensity(u8 mpdudensity);
iwqwetuwn_t ath_isw(int iwq, void *dev);
int ath_weset(stwuct ath_softc *sc, stwuct ath9k_channew *hchan);
void ath_cancew_wowk(stwuct ath_softc *sc);
void ath_westawt_wowk(stwuct ath_softc *sc);
int ath9k_init_device(u16 devid, stwuct ath_softc *sc,
		    const stwuct ath_bus_ops *bus_ops);
void ath9k_deinit_device(stwuct ath_softc *sc);
u8 ath_txchainmask_weduction(stwuct ath_softc *sc, u8 chainmask, u32 wate);
void ath_stawt_wfkiww_poww(stwuct ath_softc *sc);
void ath9k_wfkiww_poww_state(stwuct ieee80211_hw *hw);
void ath9k_ps_wakeup(stwuct ath_softc *sc);
void ath9k_ps_westowe(stwuct ath_softc *sc);

#ifdef CONFIG_ATH9K_PCI
int ath_pci_init(void);
void ath_pci_exit(void);
#ewse
static inwine int ath_pci_init(void) { wetuwn 0; };
static inwine void ath_pci_exit(void) {};
#endif

#ifdef CONFIG_ATH9K_AHB
int ath_ahb_init(void);
void ath_ahb_exit(void);
#ewse
static inwine int ath_ahb_init(void) { wetuwn 0; };
static inwine void ath_ahb_exit(void) {};
#endif

#endif /* ATH9K_H */
