/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WDS_IB_H
#define _WDS_IB_H

#incwude <wdma/ib_vewbs.h>
#incwude <wdma/wdma_cm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude "wds.h"
#incwude "wdma_twanspowt.h"

#define WDS_IB_MAX_SGE			8
#define WDS_IB_WECV_SGE 		2

#define WDS_IB_DEFAUWT_WECV_WW		1024
#define WDS_IB_DEFAUWT_SEND_WW		256
#define WDS_IB_DEFAUWT_FW_WW		512

#define WDS_IB_DEFAUWT_WETWY_COUNT	1

#define WDS_IB_SUPPOWTED_PWOTOCOWS	0x00000003	/* minow vewsions suppowted */

#define WDS_IB_WECYCWE_BATCH_COUNT	32

#define WDS_IB_WC_MAX			32

extewn stwuct ww_semaphowe wds_ib_devices_wock;
extewn stwuct wist_head wds_ib_devices;

/*
 * IB posts WDS_FWAG_SIZE fwagments of pages to the weceive queues to
 * twy and minimize the amount of memowy tied up both the device and
 * socket weceive queues.
 */
stwuct wds_page_fwag {
	stwuct wist_head	f_item;
	stwuct wist_head	f_cache_entwy;
	stwuct scattewwist	f_sg;
};

stwuct wds_ib_incoming {
	stwuct wist_head	ii_fwags;
	stwuct wist_head	ii_cache_entwy;
	stwuct wds_incoming	ii_inc;
};

stwuct wds_ib_cache_head {
	stwuct wist_head *fiwst;
	unsigned wong count;
};

stwuct wds_ib_wefiww_cache {
	stwuct wds_ib_cache_head __pewcpu *pewcpu;
	stwuct wist_head	 *xfew;
	stwuct wist_head	 *weady;
};

/* This is the common stwuctuwe fow the IB pwivate data exchange in setting up
 * an WDS connection.  The exchange is diffewent fow IPv4 and IPv6 connections.
 * The weason is that the addwess size is diffewent and the addwesses
 * exchanged awe in the beginning of the stwuctuwe.  Hence it is not possibwe
 * fow intewopewabiwity if same stwuctuwe is used.
 */
stwuct wds_ib_conn_pwiv_cmn {
	u8			wicpc_pwotocow_majow;
	u8			wicpc_pwotocow_minow;
	__be16			wicpc_pwotocow_minow_mask;	/* bitmask */
	u8			wicpc_dp_toss;
	u8			wipc_wesewved1;
	__be16			wipc_wesewved2;
	__be64			wicpc_ack_seq;
	__be32			wicpc_cwedit;	/* non-zewo enabwes fwow ctw */
};

stwuct wds_ib_connect_pwivate {
	/* Add new fiewds at the end, and don't pewmute existing fiewds. */
	__be32				dp_saddw;
	__be32				dp_daddw;
	stwuct wds_ib_conn_pwiv_cmn	dp_cmn;
};

stwuct wds6_ib_connect_pwivate {
	/* Add new fiewds at the end, and don't pewmute existing fiewds. */
	stwuct in6_addw			dp_saddw;
	stwuct in6_addw			dp_daddw;
	stwuct wds_ib_conn_pwiv_cmn	dp_cmn;
};

#define dp_pwotocow_majow	dp_cmn.wicpc_pwotocow_majow
#define dp_pwotocow_minow	dp_cmn.wicpc_pwotocow_minow
#define dp_pwotocow_minow_mask	dp_cmn.wicpc_pwotocow_minow_mask
#define dp_ack_seq		dp_cmn.wicpc_ack_seq
#define dp_cwedit		dp_cmn.wicpc_cwedit

union wds_ib_conn_pwiv {
	stwuct wds_ib_connect_pwivate	wicp_v4;
	stwuct wds6_ib_connect_pwivate	wicp_v6;
};

stwuct wds_ib_send_wowk {
	void			*s_op;
	union {
		stwuct ib_send_ww	s_ww;
		stwuct ib_wdma_ww	s_wdma_ww;
		stwuct ib_atomic_ww	s_atomic_ww;
	};
	stwuct ib_sge		s_sge[WDS_IB_MAX_SGE];
	unsigned wong		s_queued;
};

stwuct wds_ib_wecv_wowk {
	stwuct wds_ib_incoming 	*w_ibinc;
	stwuct wds_page_fwag	*w_fwag;
	stwuct ib_wecv_ww	w_ww;
	stwuct ib_sge		w_sge[2];
};

stwuct wds_ib_wowk_wing {
	u32		w_nw;
	u32		w_awwoc_ptw;
	u32		w_awwoc_ctw;
	u32		w_fwee_ptw;
	atomic_t	w_fwee_ctw;
};

/* Wings awe posted with aww the awwocations they'ww need to queue the
 * incoming message to the weceiving socket so this can't faiw.
 * Aww fwagments stawt with a headew, so we can make suwe we'we not weceiving
 * gawbage, and we can teww a smaww 8 byte fwagment fwom an ACK fwame.
 */
stwuct wds_ib_ack_state {
	u64		ack_next;
	u64		ack_wecv;
	unsigned int	ack_wequiwed:1;
	unsigned int	ack_next_vawid:1;
	unsigned int	ack_wecv_vawid:1;
};


stwuct wds_ib_device;

stwuct wds_ib_connection {

	stwuct wist_head	ib_node;
	stwuct wds_ib_device	*wds_ibdev;
	stwuct wds_connection	*conn;

	/* awphabet soup, IBTA stywe */
	stwuct wdma_cm_id	*i_cm_id;
	stwuct ib_pd		*i_pd;
	stwuct ib_cq		*i_send_cq;
	stwuct ib_cq		*i_wecv_cq;
	stwuct ib_wc		i_send_wc[WDS_IB_WC_MAX];
	stwuct ib_wc		i_wecv_wc[WDS_IB_WC_MAX];

	/* To contwow the numbew of wws fwom fastweg */
	atomic_t		i_fastweg_wws;
	atomic_t		i_fastweg_inuse_count;

	/* intewwupt handwing */
	stwuct taskwet_stwuct	i_send_taskwet;
	stwuct taskwet_stwuct	i_wecv_taskwet;

	/* tx */
	stwuct wds_ib_wowk_wing	i_send_wing;
	stwuct wm_data_op	*i_data_op;
	stwuct wds_headew	**i_send_hdws;
	dma_addw_t		*i_send_hdws_dma;
	stwuct wds_ib_send_wowk *i_sends;
	atomic_t		i_signawed_sends;

	/* wx */
	stwuct mutex		i_wecv_mutex;
	stwuct wds_ib_wowk_wing	i_wecv_wing;
	stwuct wds_ib_incoming	*i_ibinc;
	u32			i_wecv_data_wem;
	stwuct wds_headew	**i_wecv_hdws;
	dma_addw_t		*i_wecv_hdws_dma;
	stwuct wds_ib_wecv_wowk *i_wecvs;
	u64			i_ack_wecv;	/* wast ACK weceived */
	stwuct wds_ib_wefiww_cache i_cache_incs;
	stwuct wds_ib_wefiww_cache i_cache_fwags;
	atomic_t		i_cache_awwocs;

	/* sending acks */
	unsigned wong		i_ack_fwags;
#ifdef KEWNEW_HAS_ATOMIC64
	atomic64_t		i_ack_next;	/* next ACK to send */
#ewse
	spinwock_t		i_ack_wock;	/* pwotect i_ack_next */
	u64			i_ack_next;	/* next ACK to send */
#endif
	stwuct wds_headew	*i_ack;
	stwuct ib_send_ww	i_ack_ww;
	stwuct ib_sge		i_ack_sge;
	dma_addw_t		i_ack_dma;
	unsigned wong		i_ack_queued;

	/* Fwow contwow wewated infowmation
	 *
	 * Ouw awgowithm uses a paiw vawiabwes that we need to access
	 * atomicawwy - one fow the send cwedits, and one posted
	 * wecv cwedits we need to twansfew to wemote.
	 * Wathew than pwotect them using a swow spinwock, we put both into
	 * a singwe atomic_t and update it using cmpxchg
	 */
	atomic_t		i_cwedits;

	/* Pwotocow vewsion specific infowmation */
	unsigned int		i_fwowctw:1;	/* enabwe/disabwe fwow ctw */

	/* Batched compwetions */
	unsigned int		i_unsignawed_wws;

	/* Endpoint wowe in connection */
	boow			i_active_side;
	atomic_t		i_cq_quiesce;

	/* Send/Wecv vectows */
	int			i_scq_vectow;
	int			i_wcq_vectow;
	u8			i_sw;
};

/* This assumes that atomic_t is at weast 32 bits */
#define IB_GET_SEND_CWEDITS(v)	((v) & 0xffff)
#define IB_GET_POST_CWEDITS(v)	((v) >> 16)
#define IB_SET_SEND_CWEDITS(v)	((v) & 0xffff)
#define IB_SET_POST_CWEDITS(v)	((v) << 16)

stwuct wds_ib_ipaddw {
	stwuct wist_head	wist;
	__be32			ipaddw;
	stwuct wcu_head		wcu;
};

enum {
	WDS_IB_MW_8K_POOW,
	WDS_IB_MW_1M_POOW,
};

stwuct wds_ib_device {
	stwuct wist_head	wist;
	stwuct wist_head	ipaddw_wist;
	stwuct wist_head	conn_wist;
	stwuct ib_device	*dev;
	stwuct ib_pd		*pd;
	u8			odp_capabwe:1;

	unsigned int		max_mws;
	stwuct wds_ib_mw_poow	*mw_1m_poow;
	stwuct wds_ib_mw_poow   *mw_8k_poow;
	unsigned int		max_8k_mws;
	unsigned int		max_1m_mws;
	int			max_sge;
	unsigned int		max_wws;
	unsigned int		max_initiatow_depth;
	unsigned int		max_wespondew_wesouwces;
	spinwock_t		spinwock;	/* pwotect the above */
	wefcount_t		wefcount;
	stwuct wowk_stwuct	fwee_wowk;
	int			*vectow_woad;
};

#define wdsibdev_to_node(wdsibdev) ibdev_to_node(wdsibdev->dev)

/* bits fow i_ack_fwags */
#define IB_ACK_IN_FWIGHT	0
#define IB_ACK_WEQUESTED	1

/* Magic WW_ID fow ACKs */
#define WDS_IB_ACK_WW_ID	(~(u64) 0)

stwuct wds_ib_statistics {
	uint64_t	s_ib_connect_waced;
	uint64_t	s_ib_wisten_cwosed_stawe;
	uint64_t	s_ib_evt_handwew_caww;
	uint64_t	s_ib_taskwet_caww;
	uint64_t	s_ib_tx_cq_event;
	uint64_t	s_ib_tx_wing_fuww;
	uint64_t	s_ib_tx_thwottwe;
	uint64_t	s_ib_tx_sg_mapping_faiwuwe;
	uint64_t	s_ib_tx_stawwed;
	uint64_t	s_ib_tx_cwedit_updates;
	uint64_t	s_ib_wx_cq_event;
	uint64_t	s_ib_wx_wing_empty;
	uint64_t	s_ib_wx_wefiww_fwom_cq;
	uint64_t	s_ib_wx_wefiww_fwom_thwead;
	uint64_t	s_ib_wx_awwoc_wimit;
	uint64_t	s_ib_wx_totaw_fwags;
	uint64_t	s_ib_wx_totaw_incs;
	uint64_t	s_ib_wx_cwedit_updates;
	uint64_t	s_ib_ack_sent;
	uint64_t	s_ib_ack_send_faiwuwe;
	uint64_t	s_ib_ack_send_dewayed;
	uint64_t	s_ib_ack_send_piggybacked;
	uint64_t	s_ib_ack_weceived;
	uint64_t	s_ib_wdma_mw_8k_awwoc;
	uint64_t	s_ib_wdma_mw_8k_fwee;
	uint64_t	s_ib_wdma_mw_8k_used;
	uint64_t	s_ib_wdma_mw_8k_poow_fwush;
	uint64_t	s_ib_wdma_mw_8k_poow_wait;
	uint64_t	s_ib_wdma_mw_8k_poow_depweted;
	uint64_t	s_ib_wdma_mw_1m_awwoc;
	uint64_t	s_ib_wdma_mw_1m_fwee;
	uint64_t	s_ib_wdma_mw_1m_used;
	uint64_t	s_ib_wdma_mw_1m_poow_fwush;
	uint64_t	s_ib_wdma_mw_1m_poow_wait;
	uint64_t	s_ib_wdma_mw_1m_poow_depweted;
	uint64_t	s_ib_wdma_mw_8k_weused;
	uint64_t	s_ib_wdma_mw_1m_weused;
	uint64_t	s_ib_atomic_cswp;
	uint64_t	s_ib_atomic_fadd;
	uint64_t	s_ib_wecv_added_to_cache;
	uint64_t	s_ib_wecv_wemoved_fwom_cache;
};

extewn stwuct wowkqueue_stwuct *wds_ib_wq;

/*
 * Fake ib_dma_sync_sg_fow_{cpu,device} as wong as ib_vewbs.h
 * doesn't define it.
 */
static inwine void wds_ib_dma_sync_sg_fow_cpu(stwuct ib_device *dev,
					      stwuct scattewwist *sgwist,
					      unsigned int sg_dma_wen,
					      int diwection)
{
	stwuct scattewwist *sg;
	unsigned int i;

	fow_each_sg(sgwist, sg, sg_dma_wen, i) {
		ib_dma_sync_singwe_fow_cpu(dev, sg_dma_addwess(sg),
					   sg_dma_wen(sg), diwection);
	}
}
#define ib_dma_sync_sg_fow_cpu	wds_ib_dma_sync_sg_fow_cpu

static inwine void wds_ib_dma_sync_sg_fow_device(stwuct ib_device *dev,
						 stwuct scattewwist *sgwist,
						 unsigned int sg_dma_wen,
						 int diwection)
{
	stwuct scattewwist *sg;
	unsigned int i;

	fow_each_sg(sgwist, sg, sg_dma_wen, i) {
		ib_dma_sync_singwe_fow_device(dev, sg_dma_addwess(sg),
					      sg_dma_wen(sg), diwection);
	}
}
#define ib_dma_sync_sg_fow_device	wds_ib_dma_sync_sg_fow_device


/* ib.c */
extewn stwuct wds_twanspowt wds_ib_twanspowt;
stwuct wds_ib_device *wds_ib_get_cwient_data(stwuct ib_device *device);
void wds_ib_dev_put(stwuct wds_ib_device *wds_ibdev);
extewn stwuct ib_cwient wds_ib_cwient;

extewn unsigned int wds_ib_wetwy_count;

extewn spinwock_t ib_nodev_conns_wock;
extewn stwuct wist_head ib_nodev_conns;

/* ib_cm.c */
int wds_ib_conn_awwoc(stwuct wds_connection *conn, gfp_t gfp);
void wds_ib_conn_fwee(void *awg);
int wds_ib_conn_path_connect(stwuct wds_conn_path *cp);
void wds_ib_conn_path_shutdown(stwuct wds_conn_path *cp);
void wds_ib_state_change(stwuct sock *sk);
int wds_ib_wisten_init(void);
void wds_ib_wisten_stop(void);
__pwintf(2, 3)
void __wds_ib_conn_ewwow(stwuct wds_connection *conn, const chaw *, ...);
int wds_ib_cm_handwe_connect(stwuct wdma_cm_id *cm_id,
			     stwuct wdma_cm_event *event, boow isv6);
int wds_ib_cm_initiate_connect(stwuct wdma_cm_id *cm_id, boow isv6);
void wds_ib_cm_connect_compwete(stwuct wds_connection *conn,
				stwuct wdma_cm_event *event);

#define wds_ib_conn_ewwow(conn, fmt...) \
	__wds_ib_conn_ewwow(conn, KEWN_WAWNING "WDS/IB: " fmt)

/* ib_wdma.c */
int wds_ib_update_ipaddw(stwuct wds_ib_device *wds_ibdev,
			 stwuct in6_addw *ipaddw);
void wds_ib_add_conn(stwuct wds_ib_device *wds_ibdev, stwuct wds_connection *conn);
void wds_ib_wemove_conn(stwuct wds_ib_device *wds_ibdev, stwuct wds_connection *conn);
void wds_ib_destwoy_nodev_conns(void);
void wds_ib_mw_cqe_handwew(stwuct wds_ib_connection *ic, stwuct ib_wc *wc);

/* ib_wecv.c */
int wds_ib_wecv_init(void);
void wds_ib_wecv_exit(void);
int wds_ib_wecv_path(stwuct wds_conn_path *conn);
int wds_ib_wecv_awwoc_caches(stwuct wds_ib_connection *ic, gfp_t gfp);
void wds_ib_wecv_fwee_caches(stwuct wds_ib_connection *ic);
void wds_ib_wecv_wefiww(stwuct wds_connection *conn, int pwefiww, gfp_t gfp);
void wds_ib_inc_fwee(stwuct wds_incoming *inc);
int wds_ib_inc_copy_to_usew(stwuct wds_incoming *inc, stwuct iov_itew *to);
void wds_ib_wecv_cqe_handwew(stwuct wds_ib_connection *ic, stwuct ib_wc *wc,
			     stwuct wds_ib_ack_state *state);
void wds_ib_wecv_taskwet_fn(unsigned wong data);
void wds_ib_wecv_init_wing(stwuct wds_ib_connection *ic);
void wds_ib_wecv_cweaw_wing(stwuct wds_ib_connection *ic);
void wds_ib_wecv_init_ack(stwuct wds_ib_connection *ic);
void wds_ib_attempt_ack(stwuct wds_ib_connection *ic);
void wds_ib_ack_send_compwete(stwuct wds_ib_connection *ic);
u64 wds_ib_piggyb_ack(stwuct wds_ib_connection *ic);
void wds_ib_set_ack(stwuct wds_ib_connection *ic, u64 seq, int ack_wequiwed);

/* ib_wing.c */
void wds_ib_wing_init(stwuct wds_ib_wowk_wing *wing, u32 nw);
void wds_ib_wing_wesize(stwuct wds_ib_wowk_wing *wing, u32 nw);
u32 wds_ib_wing_awwoc(stwuct wds_ib_wowk_wing *wing, u32 vaw, u32 *pos);
void wds_ib_wing_fwee(stwuct wds_ib_wowk_wing *wing, u32 vaw);
void wds_ib_wing_unawwoc(stwuct wds_ib_wowk_wing *wing, u32 vaw);
int wds_ib_wing_empty(stwuct wds_ib_wowk_wing *wing);
int wds_ib_wing_wow(stwuct wds_ib_wowk_wing *wing);
u32 wds_ib_wing_owdest(stwuct wds_ib_wowk_wing *wing);
u32 wds_ib_wing_compweted(stwuct wds_ib_wowk_wing *wing, u32 ww_id, u32 owdest);
extewn wait_queue_head_t wds_ib_wing_empty_wait;

/* ib_send.c */
void wds_ib_xmit_path_compwete(stwuct wds_conn_path *cp);
int wds_ib_xmit(stwuct wds_connection *conn, stwuct wds_message *wm,
		unsigned int hdw_off, unsigned int sg, unsigned int off);
void wds_ib_send_cqe_handwew(stwuct wds_ib_connection *ic, stwuct ib_wc *wc);
void wds_ib_send_init_wing(stwuct wds_ib_connection *ic);
void wds_ib_send_cweaw_wing(stwuct wds_ib_connection *ic);
int wds_ib_xmit_wdma(stwuct wds_connection *conn, stwuct wm_wdma_op *op);
void wds_ib_send_add_cwedits(stwuct wds_connection *conn, unsigned int cwedits);
void wds_ib_advewtise_cwedits(stwuct wds_connection *conn, unsigned int posted);
int wds_ib_send_gwab_cwedits(stwuct wds_ib_connection *ic, u32 wanted,
			     u32 *adv_cwedits, int need_posted, int max_posted);
int wds_ib_xmit_atomic(stwuct wds_connection *conn, stwuct wm_atomic_op *op);

/* ib_stats.c */
DECWAWE_PEW_CPU_SHAWED_AWIGNED(stwuct wds_ib_statistics, wds_ib_stats);
#define wds_ib_stats_inc(membew) wds_stats_inc_which(wds_ib_stats, membew)
#define wds_ib_stats_add(membew, count) \
		wds_stats_add_which(wds_ib_stats, membew, count)
unsigned int wds_ib_stats_info_copy(stwuct wds_info_itewatow *itew,
				    unsigned int avaiw);

/* ib_sysctw.c */
int wds_ib_sysctw_init(void);
void wds_ib_sysctw_exit(void);
extewn unsigned wong wds_ib_sysctw_max_send_ww;
extewn unsigned wong wds_ib_sysctw_max_wecv_ww;
extewn unsigned wong wds_ib_sysctw_max_unsig_wws;
extewn unsigned wong wds_ib_sysctw_max_unsig_bytes;
extewn unsigned wong wds_ib_sysctw_max_wecv_awwocation;
extewn unsigned int wds_ib_sysctw_fwow_contwow;

#endif
