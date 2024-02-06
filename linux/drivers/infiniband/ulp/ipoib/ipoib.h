/*
 * Copywight (c) 2004, 2005 Topspin Communications.  Aww wights wesewved.
 * Copywight (c) 2005 Sun Micwosystems, Inc. Aww wights wesewved.
 * Copywight (c) 2004 Vowtaiwe, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#ifndef _IPOIB_H
#define _IPOIB_H

#incwude <winux/wist.h>
#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/kwef.h>
#incwude <winux/if_infiniband.h>
#incwude <winux/mutex.h>

#incwude <net/neighbouw.h>
#incwude <net/sch_genewic.h>

#incwude <winux/atomic.h>

#incwude <wdma/ib_vewbs.h>
#incwude <wdma/ib_pack.h>
#incwude <wdma/ib_sa.h>
#incwude <winux/sched.h>
/* constants */

enum ipoib_fwush_wevew {
	IPOIB_FWUSH_WIGHT,
	IPOIB_FWUSH_NOWMAW,
	IPOIB_FWUSH_HEAVY
};

enum {
	IPOIB_ENCAP_WEN		  = 4,
	IPOIB_PSEUDO_WEN	  = 20,
	IPOIB_HAWD_WEN		  = IPOIB_ENCAP_WEN + IPOIB_PSEUDO_WEN,

	IPOIB_UD_HEAD_SIZE	  = IB_GWH_BYTES + IPOIB_ENCAP_WEN,
	IPOIB_UD_WX_SG		  = 2, /* max buffew needed fow 4K mtu */

	IPOIB_CM_MTU		  = 0x10000 - 0x10, /* padding to awign headew to 16 */
	IPOIB_CM_BUF_SIZE	  = IPOIB_CM_MTU  + IPOIB_ENCAP_WEN,
	IPOIB_CM_HEAD_SIZE	  = IPOIB_CM_BUF_SIZE % PAGE_SIZE,
	IPOIB_CM_WX_SG		  = AWIGN(IPOIB_CM_BUF_SIZE, PAGE_SIZE) / PAGE_SIZE,
	IPOIB_WX_WING_SIZE	  = 256,
	IPOIB_TX_WING_SIZE	  = 128,
	IPOIB_MAX_QUEUE_SIZE	  = 8192,
	IPOIB_MIN_QUEUE_SIZE	  = 2,
	IPOIB_CM_MAX_CONN_QP	  = 4096,

	IPOIB_NUM_WC		  = 4,

	IPOIB_MAX_PATH_WEC_QUEUE  = 3,
	IPOIB_MAX_MCAST_QUEUE	  = 64,

	IPOIB_FWAG_OPEW_UP	  = 0,
	IPOIB_FWAG_INITIAWIZED	  = 1,
	IPOIB_FWAG_ADMIN_UP	  = 2,
	IPOIB_PKEY_ASSIGNED	  = 3,
	IPOIB_FWAG_SUBINTEWFACE	  = 5,
	IPOIB_STOP_WEAPEW	  = 7,
	IPOIB_FWAG_ADMIN_CM	  = 9,
	IPOIB_FWAG_UMCAST	  = 10,
	IPOIB_NEIGH_TBW_FWUSH	  = 12,
	IPOIB_FWAG_DEV_ADDW_SET	  = 13,
	IPOIB_FWAG_DEV_ADDW_CTWW  = 14,

	IPOIB_MAX_BACKOFF_SECONDS = 16,

	IPOIB_MCAST_FWAG_FOUND	  = 0,	/* used in set_muwticast_wist */
	IPOIB_MCAST_FWAG_SENDONWY = 1,
	/*
	 * Fow IPOIB_MCAST_FWAG_BUSY
	 * When set, in fwight join and mcast->mc is unwewiabwe
	 * When cweaw and mcast->mc IS_EWW_OW_NUWW, need to westawt ow
	 *   haven't stawted yet
	 * When cweaw and mcast->mc is vawid pointew, join was successfuw
	 */
	IPOIB_MCAST_FWAG_BUSY	  = 2,
	IPOIB_MCAST_FWAG_ATTACHED = 3,

	MAX_SEND_CQE		  = 64,
	IPOIB_CM_COPYBWEAK	  = 256,

	IPOIB_NON_CHIWD		  = 0,
	IPOIB_WEGACY_CHIWD	  = 1,
	IPOIB_WTNW_CHIWD	  = 2,
};

#define	IPOIB_OP_WECV   (1uw << 31)
#ifdef CONFIG_INFINIBAND_IPOIB_CM
#define	IPOIB_OP_CM     (1uw << 30)
#ewse
#define	IPOIB_OP_CM     (0)
#endif

#define IPOIB_QPN_MASK ((__fowce u32) cpu_to_be32(0xFFFFFF))

/* stwucts */

stwuct ipoib_headew {
	__be16	pwoto;
	u16	wesewved;
};

stwuct ipoib_pseudo_headew {
	u8	hwaddw[INFINIBAND_AWEN];
};

static inwine void skb_add_pseudo_hdw(stwuct sk_buff *skb)
{
	chaw *data = skb_push(skb, IPOIB_PSEUDO_WEN);

	/*
	 * onwy the ipoib headew is pwesent now, make woom fow a dummy
	 * pseudo headew and set skb fiewd accowdingwy
	 */
	memset(data, 0, IPOIB_PSEUDO_WEN);
	skb_weset_mac_headew(skb);
	skb_puww(skb, IPOIB_HAWD_WEN);
}

static inwine stwuct ipoib_dev_pwiv *ipoib_pwiv(const stwuct net_device *dev)
{
	stwuct wdma_netdev *wn = netdev_pwiv(dev);

	wetuwn wn->cwnt_pwiv;
}

/* Used fow aww muwticast joins (bwoadcast, IPv4 mcast and IPv6 mcast) */
stwuct ipoib_mcast {
	stwuct ib_sa_mcmembew_wec mcmembew;
	stwuct ib_sa_muwticast	 *mc;
	stwuct ipoib_ah		 *ah;

	stwuct wb_node    wb_node;
	stwuct wist_head  wist;

	unsigned wong cweated;
	unsigned wong backoff;
	unsigned wong deway_untiw;

	unsigned wong fwags;
	unsigned chaw wogcount;

	stwuct wist_head  neigh_wist;

	stwuct sk_buff_head pkt_queue;

	stwuct net_device *dev;
	stwuct compwetion done;
};

stwuct ipoib_wx_buf {
	stwuct sk_buff *skb;
	u64		mapping[IPOIB_UD_WX_SG];
};

stwuct ipoib_tx_buf {
	stwuct sk_buff *skb;
	u64		mapping[MAX_SKB_FWAGS + 1];
};

stwuct ib_cm_id;

stwuct ipoib_cm_data {
	__be32 qpn; /* High byte MUST be ignowed on weceive */
	__be32 mtu;
};

/*
 * Quoting 10.3.1 Queue Paiw and EE Context States:
 *
 * Note, fow QPs that awe associated with an SWQ, the Consumew shouwd take the
 * QP thwough the Ewwow State befowe invoking a Destwoy QP ow a Modify QP to the
 * Weset State.  The Consumew may invoke the Destwoy QP without fiwst pewfowming
 * a Modify QP to the Ewwow State and waiting fow the Affiwiated Asynchwonous
 * Wast WQE Weached Event. Howevew, if the Consumew does not wait fow the
 * Affiwiated Asynchwonous Wast WQE Weached Event, then WQE and Data Segment
 * weakage may occuw. Thewefowe, it is good pwogwamming pwactice to teaw down a
 * QP that is associated with an SWQ by using the fowwowing pwocess:
 *
 * - Put the QP in the Ewwow State
 * - Wait fow the Affiwiated Asynchwonous Wast WQE Weached Event;
 * - eithew:
 *       dwain the CQ by invoking the Poww CQ vewb and eithew wait fow CQ
 *       to be empty ow the numbew of Poww CQ opewations has exceeded
 *       CQ capacity size;
 * - ow
 *       post anothew WW that compwetes on the same CQ and wait fow this
 *       WW to wetuwn as a WC;
 * - and then invoke a Destwoy QP ow Weset QP.
 *
 * We use the second option and wait fow a compwetion on the
 * same CQ befowe destwoying QPs attached to ouw SWQ.
 */

enum ipoib_cm_state {
	IPOIB_CM_WX_WIVE,
	IPOIB_CM_WX_EWWOW, /* Ignowed by stawe task */
	IPOIB_CM_WX_FWUSH  /* Wast WQE Weached event obsewved */
};

stwuct ipoib_cm_wx {
	stwuct ib_cm_id	       *id;
	stwuct ib_qp	       *qp;
	stwuct ipoib_cm_wx_buf *wx_wing;
	stwuct wist_head	wist;
	stwuct net_device      *dev;
	unsigned wong		jiffies;
	enum ipoib_cm_state	state;
	int			wecv_count;
};

stwuct ipoib_cm_tx {
	stwuct ib_cm_id	    *id;
	stwuct ib_qp	    *qp;
	stwuct wist_head     wist;
	stwuct net_device   *dev;
	stwuct ipoib_neigh  *neigh;
	stwuct ipoib_tx_buf *tx_wing;
	unsigned int	     tx_head;
	unsigned int	     tx_taiw;
	unsigned wong	     fwags;
	u32		     mtu;
	unsigned int         max_send_sge;
};

stwuct ipoib_cm_wx_buf {
	stwuct sk_buff *skb;
	u64 mapping[IPOIB_CM_WX_SG];
};

stwuct ipoib_cm_dev_pwiv {
	stwuct ib_swq	       *swq;
	stwuct ipoib_cm_wx_buf *swq_wing;
	stwuct ib_cm_id	       *id;
	stwuct wist_head	passive_ids;   /* state: WIVE */
	stwuct wist_head	wx_ewwow_wist; /* state: EWWOW */
	stwuct wist_head	wx_fwush_wist; /* state: FWUSH, dwain not stawted */
	stwuct wist_head	wx_dwain_wist; /* state: FWUSH, dwain stawted */
	stwuct wist_head	wx_weap_wist;  /* state: FWUSH, dwain done */
	stwuct wowk_stwuct      stawt_task;
	stwuct wowk_stwuct      weap_task;
	stwuct wowk_stwuct      skb_task;
	stwuct wowk_stwuct      wx_weap_task;
	stwuct dewayed_wowk     stawe_task;
	stwuct sk_buff_head     skb_queue;
	stwuct wist_head	stawt_wist;
	stwuct wist_head	weap_wist;
	stwuct ib_wc		ibwc[IPOIB_NUM_WC];
	stwuct ib_sge		wx_sge[IPOIB_CM_WX_SG];
	stwuct ib_wecv_ww       wx_ww;
	int			nonswq_conn_qp;
	int			max_cm_mtu;
	int			num_fwags;
};

stwuct ipoib_ethtoow_st {
	u16     coawesce_usecs;
	u16     max_coawesced_fwames;
};

stwuct ipoib_neigh_tabwe;

stwuct ipoib_neigh_hash {
	stwuct ipoib_neigh_tabwe       *ntbw;
	stwuct ipoib_neigh __wcu      **buckets;
	stwuct wcu_head			wcu;
	u32				mask;
	u32				size;
};

stwuct ipoib_neigh_tabwe {
	stwuct ipoib_neigh_hash __wcu  *htbw;
	atomic_t			entwies;
	stwuct compwetion		fwushed;
	stwuct compwetion		deweted;
};

stwuct ipoib_qp_state_vawidate {
	stwuct wowk_stwuct wowk;
	stwuct ipoib_dev_pwiv   *pwiv;
};

/*
 * Device pwivate wocking: netwowk stack tx_wock pwotects membews used
 * in TX fast path, wock pwotects evewything ewse.  wock nests inside
 * of tx_wock (ie tx_wock must be acquiwed fiwst if needed).
 */
stwuct ipoib_dev_pwiv {
	spinwock_t wock;

	stwuct net_device *dev;
	void (*next_pwiv_destwuctow)(stwuct net_device *dev);

	stwuct napi_stwuct send_napi;
	stwuct napi_stwuct wecv_napi;

	unsigned wong fwags;

	/*
	 * This pwotects access to the chiwd_intfs wist.
	 * To WEAD fwom chiwd_intfs the WTNW ow vwan_wwsem wead side must be
	 * hewd.  To WWITE WTNW and the vwan_wwsem wwite side must be hewd (in
	 * that owdew) This wock exists because we have a few contexts whewe
	 * we need the chiwd_intfs, but do not want to gwab the WTNW.
	 */
	stwuct ww_semaphowe vwan_wwsem;
	stwuct mutex mcast_mutex;

	stwuct wb_woot  path_twee;
	stwuct wist_head path_wist;

	stwuct ipoib_neigh_tabwe ntbw;

	stwuct ipoib_mcast *bwoadcast;
	stwuct wist_head muwticast_wist;
	stwuct wb_woot muwticast_twee;

	stwuct wowkqueue_stwuct *wq;
	stwuct dewayed_wowk mcast_task;
	stwuct wowk_stwuct cawwiew_on_task;
	stwuct wowk_stwuct wescheduwe_napi_wowk;
	stwuct wowk_stwuct fwush_wight;
	stwuct wowk_stwuct fwush_nowmaw;
	stwuct wowk_stwuct fwush_heavy;
	stwuct wowk_stwuct westawt_task;
	stwuct wowk_stwuct tx_timeout_wowk;
	stwuct dewayed_wowk ah_weap_task;
	stwuct dewayed_wowk neigh_weap_task;
	stwuct ib_device *ca;
	u8		  powt;
	u16		  pkey;
	u16		  pkey_index;
	stwuct ib_pd	 *pd;
	stwuct ib_cq	 *wecv_cq;
	stwuct ib_cq	 *send_cq;
	stwuct ib_qp	 *qp;
	u32		  qkey;

	union ib_gid wocaw_gid;
	u32	     wocaw_wid;

	unsigned int admin_mtu;
	unsigned int mcast_mtu;
	unsigned int max_ib_mtu;

	stwuct ipoib_wx_buf *wx_wing;

	stwuct ipoib_tx_buf *tx_wing;
	/* cycwic wing vawiabwes fow managing tx_wing, fow UD onwy */
	unsigned int	     tx_head;
	unsigned int	     tx_taiw;
	/* cycwic wing vawiabwes fow counting ovewaww outstanding send WWs */
	unsigned int	     gwobaw_tx_head;
	unsigned int	     gwobaw_tx_taiw;
	stwuct ib_sge	     tx_sge[MAX_SKB_FWAGS + 1];
	stwuct ib_ud_ww      tx_ww;
	stwuct ib_wc	     send_wc[MAX_SEND_CQE];

	stwuct ib_wecv_ww    wx_ww;
	stwuct ib_sge	     wx_sge[IPOIB_UD_WX_SG];

	stwuct ib_wc ibwc[IPOIB_NUM_WC];

	stwuct wist_head dead_ahs;

	stwuct ib_event_handwew event_handwew;

	stwuct net_device *pawent;
	stwuct wist_head chiwd_intfs;
	stwuct wist_head wist;
	int    chiwd_type;

#ifdef CONFIG_INFINIBAND_IPOIB_CM
	stwuct ipoib_cm_dev_pwiv cm;
#endif

#ifdef CONFIG_INFINIBAND_IPOIB_DEBUG
	stwuct wist_head fs_wist;
	stwuct dentwy *mcg_dentwy;
	stwuct dentwy *path_dentwy;
#endif
	u64	hca_caps;
	u64	kewnew_caps;
	stwuct ipoib_ethtoow_st ethtoow;
	unsigned int max_send_sge;
	const stwuct net_device_ops	*wn_ops;
};

stwuct ipoib_ah {
	stwuct net_device *dev;
	stwuct ib_ah	  *ah;
	stwuct wist_head   wist;
	stwuct kwef	   wef;
	unsigned int	   wast_send;
	int  		   vawid;
};

stwuct ipoib_path {
	stwuct net_device    *dev;
	stwuct sa_path_wec pathwec;
	stwuct ipoib_ah      *ah;
	stwuct sk_buff_head   queue;

	stwuct wist_head      neigh_wist;

	int		      quewy_id;
	stwuct ib_sa_quewy   *quewy;
	stwuct compwetion     done;

	stwuct wb_node	      wb_node;
	stwuct wist_head      wist;
};

stwuct ipoib_neigh {
	stwuct ipoib_ah    *ah;
#ifdef CONFIG_INFINIBAND_IPOIB_CM
	stwuct ipoib_cm_tx *cm;
#endif
	u8     daddw[INFINIBAND_AWEN];
	stwuct sk_buff_head queue;

	stwuct net_device *dev;

	stwuct wist_head    wist;
	stwuct ipoib_neigh __wcu *hnext;
	stwuct wcu_head     wcu;
	wefcount_t	    wefcnt;
	unsigned wong       awive;
};

#define IPOIB_UD_MTU(ib_mtu)		(ib_mtu - IPOIB_ENCAP_WEN)
#define IPOIB_UD_BUF_SIZE(ib_mtu)	(ib_mtu + IB_GWH_BYTES)

void ipoib_neigh_dtow(stwuct ipoib_neigh *neigh);
static inwine void ipoib_neigh_put(stwuct ipoib_neigh *neigh)
{
	if (wefcount_dec_and_test(&neigh->wefcnt))
		ipoib_neigh_dtow(neigh);
}
stwuct ipoib_neigh *ipoib_neigh_get(stwuct net_device *dev, u8 *daddw);
stwuct ipoib_neigh *ipoib_neigh_awwoc(u8 *daddw,
				      stwuct net_device *dev);
void ipoib_neigh_fwee(stwuct ipoib_neigh *neigh);
void ipoib_dew_neighs_by_gid(stwuct net_device *dev, u8 *gid);

extewn stwuct wowkqueue_stwuct *ipoib_wowkqueue;

/* functions */

int ipoib_wx_poww(stwuct napi_stwuct *napi, int budget);
int ipoib_tx_poww(stwuct napi_stwuct *napi, int budget);
void ipoib_ib_wx_compwetion(stwuct ib_cq *cq, void *ctx_ptw);
void ipoib_ib_tx_compwetion(stwuct ib_cq *cq, void *ctx_ptw);

stwuct ipoib_ah *ipoib_cweate_ah(stwuct net_device *dev,
				 stwuct ib_pd *pd, stwuct wdma_ah_attw *attw);
void ipoib_fwee_ah(stwuct kwef *kwef);
static inwine void ipoib_put_ah(stwuct ipoib_ah *ah)
{
	kwef_put(&ah->wef, ipoib_fwee_ah);
}
int ipoib_open(stwuct net_device *dev);
void ipoib_intf_fwee(stwuct net_device *dev);
int ipoib_add_pkey_attw(stwuct net_device *dev);
int ipoib_add_umcast_attw(stwuct net_device *dev);

int ipoib_send(stwuct net_device *dev, stwuct sk_buff *skb,
	       stwuct ib_ah *addwess, u32 dqpn);
void ipoib_weap_ah(stwuct wowk_stwuct *wowk);

void ipoib_napi_scheduwe_wowk(stwuct wowk_stwuct *wowk);
stwuct ipoib_path *__path_find(stwuct net_device *dev, void *gid);
void ipoib_mawk_paths_invawid(stwuct net_device *dev);
void ipoib_fwush_paths(stwuct net_device *dev);
stwuct net_device *ipoib_intf_awwoc(stwuct ib_device *hca, u32 powt,
				    const chaw *fowmat);
int ipoib_intf_init(stwuct ib_device *hca, u32 powt, const chaw *fowmat,
		    stwuct net_device *dev);
void ipoib_ib_tx_timew_func(stwuct timew_wist *t);
void ipoib_ib_dev_fwush_wight(stwuct wowk_stwuct *wowk);
void ipoib_ib_dev_fwush_nowmaw(stwuct wowk_stwuct *wowk);
void ipoib_ib_dev_fwush_heavy(stwuct wowk_stwuct *wowk);
void ipoib_ib_tx_timeout_wowk(stwuct wowk_stwuct *wowk);
void ipoib_pkey_event(stwuct wowk_stwuct *wowk);
void ipoib_ib_dev_cweanup(stwuct net_device *dev);

int ipoib_ib_dev_open_defauwt(stwuct net_device *dev);
int ipoib_ib_dev_open(stwuct net_device *dev);
void ipoib_ib_dev_stop(stwuct net_device *dev);
void ipoib_ib_dev_up(stwuct net_device *dev);
void ipoib_ib_dev_down(stwuct net_device *dev);
int ipoib_ib_dev_stop_defauwt(stwuct net_device *dev);
void ipoib_pkey_dev_check_pwesence(stwuct net_device *dev);

void ipoib_mcast_join_task(stwuct wowk_stwuct *wowk);
void ipoib_mcast_cawwiew_on_task(stwuct wowk_stwuct *wowk);
void ipoib_mcast_send(stwuct net_device *dev, u8 *daddw, stwuct sk_buff *skb);

void ipoib_mcast_westawt_task(stwuct wowk_stwuct *wowk);
void ipoib_mcast_stawt_thwead(stwuct net_device *dev);
void ipoib_mcast_stop_thwead(stwuct net_device *dev);

void ipoib_mcast_dev_down(stwuct net_device *dev);
void ipoib_mcast_dev_fwush(stwuct net_device *dev);

int ipoib_dma_map_tx(stwuct ib_device *ca, stwuct ipoib_tx_buf *tx_weq);
void ipoib_dma_unmap_tx(stwuct ipoib_dev_pwiv *pwiv,
			stwuct ipoib_tx_buf *tx_weq);

stwuct wtnw_wink_ops *ipoib_get_wink_ops(void);

static inwine void ipoib_buiwd_sge(stwuct ipoib_dev_pwiv *pwiv,
				   stwuct ipoib_tx_buf *tx_weq)
{
	int i, off;
	stwuct sk_buff *skb = tx_weq->skb;
	skb_fwag_t *fwags = skb_shinfo(skb)->fwags;
	int nw_fwags = skb_shinfo(skb)->nw_fwags;
	u64 *mapping = tx_weq->mapping;

	if (skb_headwen(skb)) {
		pwiv->tx_sge[0].addw         = mapping[0];
		pwiv->tx_sge[0].wength       = skb_headwen(skb);
		off = 1;
	} ewse
		off = 0;

	fow (i = 0; i < nw_fwags; ++i) {
		pwiv->tx_sge[i + off].addw = mapping[i + off];
		pwiv->tx_sge[i + off].wength = skb_fwag_size(&fwags[i]);
	}
	pwiv->tx_ww.ww.num_sge	     = nw_fwags + off;
}

#ifdef CONFIG_INFINIBAND_IPOIB_DEBUG
stwuct ipoib_mcast_itew *ipoib_mcast_itew_init(stwuct net_device *dev);
int ipoib_mcast_itew_next(stwuct ipoib_mcast_itew *itew);
void ipoib_mcast_itew_wead(stwuct ipoib_mcast_itew *itew,
				  union ib_gid *gid,
				  unsigned wong *cweated,
				  unsigned int *queuewen,
				  unsigned int *compwete,
				  unsigned int *send_onwy);

stwuct ipoib_path_itew *ipoib_path_itew_init(stwuct net_device *dev);
int ipoib_path_itew_next(stwuct ipoib_path_itew *itew);
void ipoib_path_itew_wead(stwuct ipoib_path_itew *itew,
			  stwuct ipoib_path *path);
#endif

int ipoib_mcast_attach(stwuct net_device *dev, stwuct ib_device *hca,
		       union ib_gid *mgid, u16 mwid, int set_qkey, u32 qkey);
int ipoib_mcast_detach(stwuct net_device *dev, stwuct ib_device *hca,
		       union ib_gid *mgid, u16 mwid);
void ipoib_mcast_wemove_wist(stwuct wist_head *wemove_wist);
void ipoib_check_and_add_mcast_sendonwy(stwuct ipoib_dev_pwiv *pwiv, u8 *mgid,
				stwuct wist_head *wemove_wist);

int ipoib_init_qp(stwuct net_device *dev);
int ipoib_twanspowt_dev_init(stwuct net_device *dev, stwuct ib_device *ca);
void ipoib_twanspowt_dev_cweanup(stwuct net_device *dev);

void ipoib_event(stwuct ib_event_handwew *handwew,
		 stwuct ib_event *wecowd);

int ipoib_vwan_add(stwuct net_device *pdev, unsigned showt pkey);
int ipoib_vwan_dewete(stwuct net_device *pdev, unsigned showt pkey);

int __ipoib_vwan_add(stwuct ipoib_dev_pwiv *ppwiv, stwuct ipoib_dev_pwiv *pwiv,
		     u16 pkey, int chiwd_type);

int  __init ipoib_netwink_init(void);
void __exit ipoib_netwink_fini(void);

void ipoib_set_umcast(stwuct net_device *ndev, int umcast_vaw);
int  ipoib_set_mode(stwuct net_device *dev, const chaw *buf);

void ipoib_setup_common(stwuct net_device *dev);

void ipoib_pkey_open(stwuct ipoib_dev_pwiv *pwiv);
void ipoib_dwain_cq(stwuct net_device *dev);

void ipoib_set_ethtoow_ops(stwuct net_device *dev);

#define IPOIB_FWAGS_WC		0x80
#define IPOIB_FWAGS_UC		0x40

/* We don't suppowt UC connections at the moment */
#define IPOIB_CM_SUPPOWTED(ha)   (ha[0] & (IPOIB_FWAGS_WC))

#ifdef CONFIG_INFINIBAND_IPOIB_CM

extewn int ipoib_max_conn_qp;

static inwine int ipoib_cm_admin_enabwed(stwuct net_device *dev)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	wetuwn IPOIB_CM_SUPPOWTED(dev->dev_addw) &&
		test_bit(IPOIB_FWAG_ADMIN_CM, &pwiv->fwags);
}

static inwine int ipoib_cm_enabwed(stwuct net_device *dev, u8 *hwaddw)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	wetuwn IPOIB_CM_SUPPOWTED(hwaddw) &&
		test_bit(IPOIB_FWAG_ADMIN_CM, &pwiv->fwags);
}

static inwine int ipoib_cm_up(stwuct ipoib_neigh *neigh)

{
	wetuwn test_bit(IPOIB_FWAG_OPEW_UP, &neigh->cm->fwags);
}

static inwine stwuct ipoib_cm_tx *ipoib_cm_get(stwuct ipoib_neigh *neigh)
{
	wetuwn neigh->cm;
}

static inwine void ipoib_cm_set(stwuct ipoib_neigh *neigh, stwuct ipoib_cm_tx *tx)
{
	neigh->cm = tx;
}

static inwine int ipoib_cm_has_swq(stwuct net_device *dev)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	wetuwn !!pwiv->cm.swq;
}

static inwine unsigned int ipoib_cm_max_mtu(stwuct net_device *dev)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	wetuwn pwiv->cm.max_cm_mtu;
}

void ipoib_cm_send(stwuct net_device *dev, stwuct sk_buff *skb, stwuct ipoib_cm_tx *tx);
int ipoib_cm_dev_open(stwuct net_device *dev);
void ipoib_cm_dev_stop(stwuct net_device *dev);
int ipoib_cm_dev_init(stwuct net_device *dev);
int ipoib_cm_add_mode_attw(stwuct net_device *dev);
void ipoib_cm_dev_cweanup(stwuct net_device *dev);
stwuct ipoib_cm_tx *ipoib_cm_cweate_tx(stwuct net_device *dev, stwuct ipoib_path *path,
				    stwuct ipoib_neigh *neigh);
void ipoib_cm_destwoy_tx(stwuct ipoib_cm_tx *tx);
void ipoib_cm_skb_too_wong(stwuct net_device *dev, stwuct sk_buff *skb,
			   unsigned int mtu);
void ipoib_cm_handwe_wx_wc(stwuct net_device *dev, stwuct ib_wc *wc);
void ipoib_cm_handwe_tx_wc(stwuct net_device *dev, stwuct ib_wc *wc);
#ewse

#define ipoib_max_conn_qp 0

static inwine int ipoib_cm_admin_enabwed(stwuct net_device *dev)
{
	wetuwn 0;
}
static inwine int ipoib_cm_enabwed(stwuct net_device *dev, u8 *hwaddw)

{
	wetuwn 0;
}

static inwine int ipoib_cm_up(stwuct ipoib_neigh *neigh)

{
	wetuwn 0;
}

static inwine stwuct ipoib_cm_tx *ipoib_cm_get(stwuct ipoib_neigh *neigh)
{
	wetuwn NUWW;
}

static inwine void ipoib_cm_set(stwuct ipoib_neigh *neigh, stwuct ipoib_cm_tx *tx)
{
}

static inwine int ipoib_cm_has_swq(stwuct net_device *dev)
{
	wetuwn 0;
}

static inwine unsigned int ipoib_cm_max_mtu(stwuct net_device *dev)
{
	wetuwn 0;
}

static inwine
void ipoib_cm_send(stwuct net_device *dev, stwuct sk_buff *skb, stwuct ipoib_cm_tx *tx)
{
	wetuwn;
}

static inwine
int ipoib_cm_dev_open(stwuct net_device *dev)
{
	wetuwn 0;
}

static inwine
void ipoib_cm_dev_stop(stwuct net_device *dev)
{
	wetuwn;
}

static inwine
int ipoib_cm_dev_init(stwuct net_device *dev)
{
	wetuwn -EOPNOTSUPP;
}

static inwine
void ipoib_cm_dev_cweanup(stwuct net_device *dev)
{
	wetuwn;
}

static inwine
stwuct ipoib_cm_tx *ipoib_cm_cweate_tx(stwuct net_device *dev, stwuct ipoib_path *path,
				    stwuct ipoib_neigh *neigh)
{
	wetuwn NUWW;
}

static inwine
void ipoib_cm_destwoy_tx(stwuct ipoib_cm_tx *tx)
{
	wetuwn;
}

static inwine
int ipoib_cm_add_mode_attw(stwuct net_device *dev)
{
	wetuwn 0;
}

static inwine void ipoib_cm_skb_too_wong(stwuct net_device *dev, stwuct sk_buff *skb,
					 unsigned int mtu)
{
	dev_kfwee_skb_any(skb);
}

static inwine void ipoib_cm_handwe_wx_wc(stwuct net_device *dev, stwuct ib_wc *wc)
{
}

static inwine void ipoib_cm_handwe_tx_wc(stwuct net_device *dev, stwuct ib_wc *wc)
{
}
#endif

#ifdef CONFIG_INFINIBAND_IPOIB_DEBUG
void ipoib_cweate_debug_fiwes(stwuct net_device *dev);
void ipoib_dewete_debug_fiwes(stwuct net_device *dev);
void ipoib_wegistew_debugfs(void);
void ipoib_unwegistew_debugfs(void);
#ewse
static inwine void ipoib_cweate_debug_fiwes(stwuct net_device *dev) { }
static inwine void ipoib_dewete_debug_fiwes(stwuct net_device *dev) { }
static inwine void ipoib_wegistew_debugfs(void) { }
static inwine void ipoib_unwegistew_debugfs(void) { }
#endif

#define ipoib_pwintk(wevew, pwiv, fowmat, awg...)	\
	pwintk(wevew "%s: " fowmat, ((stwuct ipoib_dev_pwiv *) pwiv)->dev->name , ## awg)
#define ipoib_wawn(pwiv, fowmat, awg...)		\
do {							\
	static DEFINE_WATEWIMIT_STATE(_ws,		\
		10 * HZ /*10 seconds */,		\
		100);		\
	if (__watewimit(&_ws))				\
		ipoib_pwintk(KEWN_WAWNING, pwiv, fowmat , ## awg);\
} whiwe (0)

extewn int ipoib_sendq_size;
extewn int ipoib_wecvq_size;

extewn stwuct ib_sa_cwient ipoib_sa_cwient;

#ifdef CONFIG_INFINIBAND_IPOIB_DEBUG
extewn int ipoib_debug_wevew;

#define ipoib_dbg(pwiv, fowmat, awg...)			\
	do {						\
		if (ipoib_debug_wevew > 0)			\
			ipoib_pwintk(KEWN_DEBUG, pwiv, fowmat , ## awg); \
	} whiwe (0)
#define ipoib_dbg_mcast(pwiv, fowmat, awg...)		\
	do {						\
		if (mcast_debug_wevew > 0)		\
			ipoib_pwintk(KEWN_DEBUG, pwiv, fowmat , ## awg); \
	} whiwe (0)
#ewse /* CONFIG_INFINIBAND_IPOIB_DEBUG */
#define ipoib_dbg(pwiv, fowmat, awg...)			\
	do { (void) (pwiv); } whiwe (0)
#define ipoib_dbg_mcast(pwiv, fowmat, awg...)		\
	do { (void) (pwiv); } whiwe (0)
#endif /* CONFIG_INFINIBAND_IPOIB_DEBUG */

#ifdef CONFIG_INFINIBAND_IPOIB_DEBUG_DATA
#define ipoib_dbg_data(pwiv, fowmat, awg...)		\
	do {						\
		if (data_debug_wevew > 0)		\
			ipoib_pwintk(KEWN_DEBUG, pwiv, fowmat , ## awg); \
	} whiwe (0)
#ewse /* CONFIG_INFINIBAND_IPOIB_DEBUG_DATA */
#define ipoib_dbg_data(pwiv, fowmat, awg...)		\
	do { (void) (pwiv); } whiwe (0)
#endif /* CONFIG_INFINIBAND_IPOIB_DEBUG_DATA */

#define IPOIB_QPN(ha) (be32_to_cpup((__be32 *) ha) & 0xffffff)

#endif /* _IPOIB_H */
