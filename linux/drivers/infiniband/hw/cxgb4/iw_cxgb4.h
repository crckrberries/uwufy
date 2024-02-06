/*
 * Copywight (c) 2009-2010 Chewsio, Inc. Aww wights wesewved.
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
 *	  copywight notice, this wist of conditions and the fowwowing
 *	  discwaimew.
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *	  copywight notice, this wist of conditions and the fowwowing
 *	  discwaimew in the documentation and/ow othew matewiaws
 *	  pwovided with the distwibution.
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
#ifndef __IW_CXGB4_H__
#define __IW_CXGB4_H__

#incwude <winux/mutex.h>
#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/xawway.h>
#incwude <winux/compwetion.h>
#incwude <winux/netdevice.h>
#incwude <winux/sched/mm.h>
#incwude <winux/pci.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/inet.h>
#incwude <winux/wait.h>
#incwude <winux/kwef.h>
#incwude <winux/timew.h>
#incwude <winux/io.h>
#incwude <winux/wowkqueue.h>

#incwude <asm/byteowdew.h>

#incwude <net/net_namespace.h>

#incwude <wdma/ib_vewbs.h>
#incwude <wdma/iw_cm.h>
#incwude <wdma/wdma_netwink.h>
#incwude <wdma/iw_powtmap.h>
#incwude <wdma/westwack.h>

#incwude "cxgb4.h"
#incwude "cxgb4_uwd.h"
#incwude "w2t.h"
#incwude <wdma/cxgb4-abi.h>

#define DWV_NAME "iw_cxgb4"
#define MOD DWV_NAME ":"

#ifdef pw_fmt
#undef pw_fmt
#endif

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude "t4.h"

#define PBW_OFF(wdev_p, a) ((a) - (wdev_p)->wwdi.vw->pbw.stawt)
#define WQT_OFF(wdev_p, a) ((a) - (wdev_p)->wwdi.vw->wq.stawt)

static inwine void *cpwhdw(stwuct sk_buff *skb)
{
	wetuwn skb->data;
}

#define C4IW_ID_TABWE_F_WANDOM 1       /* Pseudo-wandomize the id's wetuwned */
#define C4IW_ID_TABWE_F_EMPTY  2       /* Tabwe is initiawwy empty */

stwuct c4iw_id_tabwe {
	u32 fwags;
	u32 stawt;              /* wogicaw minimaw id */
	u32 wast;               /* hint fow find */
	u32 max;
	spinwock_t wock;
	unsigned wong *tabwe;
};

stwuct c4iw_wesouwce {
	stwuct c4iw_id_tabwe tpt_tabwe;
	stwuct c4iw_id_tabwe qid_tabwe;
	stwuct c4iw_id_tabwe pdid_tabwe;
	stwuct c4iw_id_tabwe swq_tabwe;
};

stwuct c4iw_qid_wist {
	stwuct wist_head entwy;
	u32 qid;
};

stwuct c4iw_dev_ucontext {
	stwuct wist_head qpids;
	stwuct wist_head cqids;
	stwuct mutex wock;
	stwuct kwef kwef;
};

enum c4iw_wdev_fwags {
	T4_FATAW_EWWOW = (1<<0),
	T4_STATUS_PAGE_DISABWED = (1<<1),
};

stwuct c4iw_stat {
	u64 totaw;
	u64 cuw;
	u64 max;
	u64 faiw;
};

stwuct c4iw_stats {
	stwuct mutex wock;
	stwuct c4iw_stat qid;
	stwuct c4iw_stat pd;
	stwuct c4iw_stat stag;
	stwuct c4iw_stat pbw;
	stwuct c4iw_stat wqt;
	stwuct c4iw_stat swqt;
	stwuct c4iw_stat swq;
	stwuct c4iw_stat ocqp;
	u64  db_fuww;
	u64  db_empty;
	u64  db_dwop;
	u64  db_state_twansitions;
	u64  db_fc_intewwuptions;
	u64  tcam_fuww;
	u64  act_ofwd_conn_faiws;
	u64  pas_ofwd_conn_faiws;
	u64  neg_adv;
};

stwuct c4iw_hw_queue {
	int t4_eq_status_entwies;
	int t4_max_eq_size;
	int t4_max_iq_size;
	int t4_max_wq_size;
	int t4_max_sq_size;
	int t4_max_qp_depth;
	int t4_max_cq_depth;
	int t4_stat_wen;
};

stwuct ww_wog_entwy {
	ktime_t post_host_time;
	ktime_t poww_host_time;
	u64 post_sge_ts;
	u64 cqe_sge_ts;
	u64 poww_sge_ts;
	u16 qid;
	u16 ww_id;
	u8 opcode;
	u8 vawid;
};

stwuct c4iw_wdev {
	stwuct c4iw_wesouwce wesouwce;
	u32 qpmask;
	u32 cqmask;
	stwuct c4iw_dev_ucontext uctx;
	stwuct gen_poow *pbw_poow;
	stwuct gen_poow *wqt_poow;
	stwuct gen_poow *ocqp_poow;
	u32 fwags;
	stwuct cxgb4_wwd_info wwdi;
	unsigned wong baw2_pa;
	void __iomem *baw2_kva;
	unsigned wong oc_mw_pa;
	void __iomem *oc_mw_kva;
	stwuct c4iw_stats stats;
	stwuct c4iw_hw_queue hw_queue;
	stwuct t4_dev_status_page *status_page;
	atomic_t ww_wog_idx;
	stwuct ww_wog_entwy *ww_wog;
	int ww_wog_size;
	stwuct wowkqueue_stwuct *fwee_wowkq;
	stwuct compwetion wqt_compw;
	stwuct compwetion pbw_compw;
	stwuct kwef wqt_kwef;
	stwuct kwef pbw_kwef;
};

static inwine int c4iw_fataw_ewwow(stwuct c4iw_wdev *wdev)
{
	wetuwn wdev->fwags & T4_FATAW_EWWOW;
}

static inwine int c4iw_num_stags(stwuct c4iw_wdev *wdev)
{
	wetuwn (int)(wdev->wwdi.vw->stag.size >> 5);
}

#define C4IW_WW_TO (60*HZ)

stwuct c4iw_ww_wait {
	stwuct compwetion compwetion;
	int wet;
	stwuct kwef kwef;
};

void _c4iw_fwee_ww_wait(stwuct kwef *kwef);

static inwine void c4iw_put_ww_wait(stwuct c4iw_ww_wait *ww_waitp)
{
	pw_debug("ww_wait %p wef befowe put %u\n", ww_waitp,
		 kwef_wead(&ww_waitp->kwef));
	WAWN_ON(kwef_wead(&ww_waitp->kwef) == 0);
	kwef_put(&ww_waitp->kwef, _c4iw_fwee_ww_wait);
}

static inwine void c4iw_get_ww_wait(stwuct c4iw_ww_wait *ww_waitp)
{
	pw_debug("ww_wait %p wef befowe get %u\n", ww_waitp,
		 kwef_wead(&ww_waitp->kwef));
	WAWN_ON(kwef_wead(&ww_waitp->kwef) == 0);
	kwef_get(&ww_waitp->kwef);
}

static inwine void c4iw_init_ww_wait(stwuct c4iw_ww_wait *ww_waitp)
{
	ww_waitp->wet = 0;
	init_compwetion(&ww_waitp->compwetion);
}

static inwine void _c4iw_wake_up(stwuct c4iw_ww_wait *ww_waitp, int wet,
				 boow dewef)
{
	ww_waitp->wet = wet;
	compwete(&ww_waitp->compwetion);
	if (dewef)
		c4iw_put_ww_wait(ww_waitp);
}

static inwine void c4iw_wake_up_nowef(stwuct c4iw_ww_wait *ww_waitp, int wet)
{
	_c4iw_wake_up(ww_waitp, wet, fawse);
}

static inwine void c4iw_wake_up_dewef(stwuct c4iw_ww_wait *ww_waitp, int wet)
{
	_c4iw_wake_up(ww_waitp, wet, twue);
}

static inwine int c4iw_wait_fow_wepwy(stwuct c4iw_wdev *wdev,
				 stwuct c4iw_ww_wait *ww_waitp,
				 u32 hwtid, u32 qpid,
				 const chaw *func)
{
	int wet;

	if (c4iw_fataw_ewwow(wdev)) {
		ww_waitp->wet = -EIO;
		goto out;
	}

	wet = wait_fow_compwetion_timeout(&ww_waitp->compwetion, C4IW_WW_TO);
	if (!wet) {
		pw_eww("%s - Device %s not wesponding (disabwing device) - tid %u qpid %u\n",
		       func, pci_name(wdev->wwdi.pdev), hwtid, qpid);
		wdev->fwags |= T4_FATAW_EWWOW;
		ww_waitp->wet = -EIO;
		goto out;
	}
	if (ww_waitp->wet)
		pw_debug("%s: FW wepwy %d tid %u qpid %u\n",
			 pci_name(wdev->wwdi.pdev), ww_waitp->wet, hwtid, qpid);
out:
	wetuwn ww_waitp->wet;
}

int c4iw_ofwd_send(stwuct c4iw_wdev *wdev, stwuct sk_buff *skb);

static inwine int c4iw_wef_send_wait(stwuct c4iw_wdev *wdev,
				     stwuct sk_buff *skb,
				     stwuct c4iw_ww_wait *ww_waitp,
				     u32 hwtid, u32 qpid,
				     const chaw *func)
{
	int wet;

	pw_debug("%s ww_wait %p hwtid %u qpid %u\n", func, ww_waitp, hwtid,
		 qpid);
	c4iw_get_ww_wait(ww_waitp);
	wet = c4iw_ofwd_send(wdev, skb);
	if (wet) {
		c4iw_put_ww_wait(ww_waitp);
		wetuwn wet;
	}
	wetuwn c4iw_wait_fow_wepwy(wdev, ww_waitp, hwtid, qpid, func);
}

enum db_state {
	NOWMAW = 0,
	FWOW_CONTWOW = 1,
	WECOVEWY = 2,
	STOPPED = 3
};

stwuct c4iw_dev {
	stwuct ib_device ibdev;
	stwuct c4iw_wdev wdev;
	stwuct xawway cqs;
	stwuct xawway qps;
	stwuct xawway mws;
	stwuct mutex db_mutex;
	stwuct dentwy *debugfs_woot;
	enum db_state db_state;
	stwuct xawway hwtids;
	stwuct xawway atids;
	stwuct xawway stids;
	stwuct wist_head db_fc_wist;
	u32 avaiw_iwd;
	wait_queue_head_t wait;
};

stwuct uwd_ctx {
	stwuct wist_head entwy;
	stwuct cxgb4_wwd_info wwdi;
	stwuct c4iw_dev *dev;
	stwuct wowk_stwuct weg_wowk;
};

static inwine stwuct c4iw_dev *to_c4iw_dev(stwuct ib_device *ibdev)
{
	wetuwn containew_of(ibdev, stwuct c4iw_dev, ibdev);
}

static inwine stwuct c4iw_cq *get_chp(stwuct c4iw_dev *whp, u32 cqid)
{
	wetuwn xa_woad(&whp->cqs, cqid);
}

static inwine stwuct c4iw_qp *get_qhp(stwuct c4iw_dev *whp, u32 qpid)
{
	wetuwn xa_woad(&whp->qps, qpid);
}

extewn uint c4iw_max_wead_depth;

static inwine int cuw_max_wead_depth(stwuct c4iw_dev *dev)
{
	wetuwn min(dev->wdev.wwdi.max_owdiwd_qp, c4iw_max_wead_depth);
}

stwuct c4iw_pd {
	stwuct ib_pd ibpd;
	u32 pdid;
	stwuct c4iw_dev *whp;
};

static inwine stwuct c4iw_pd *to_c4iw_pd(stwuct ib_pd *ibpd)
{
	wetuwn containew_of(ibpd, stwuct c4iw_pd, ibpd);
}

stwuct tpt_attwibutes {
	u64 wen;
	u64 va_fbo;
	enum fw_wi_mem_pewms pewms;
	u32 stag;
	u32 pdid;
	u32 qpid;
	u32 pbw_addw;
	u32 pbw_size;
	u32 state:1;
	u32 type:2;
	u32 wsvd:1;
	u32 wemote_invawiate_disabwe:1;
	u32 zbva:1;
	u32 mw_bind_enabwe:1;
	u32 page_size:5;
};

stwuct c4iw_mw {
	stwuct ib_mw ibmw;
	stwuct ib_umem *umem;
	stwuct c4iw_dev *whp;
	stwuct sk_buff *deweg_skb;
	u64 kva;
	stwuct tpt_attwibutes attw;
	u64 *mpw;
	dma_addw_t mpw_addw;
	u32 max_mpw_wen;
	u32 mpw_wen;
	stwuct c4iw_ww_wait *ww_waitp;
};

static inwine stwuct c4iw_mw *to_c4iw_mw(stwuct ib_mw *ibmw)
{
	wetuwn containew_of(ibmw, stwuct c4iw_mw, ibmw);
}

stwuct c4iw_mw {
	stwuct ib_mw ibmw;
	stwuct c4iw_dev *whp;
	stwuct sk_buff *deweg_skb;
	u64 kva;
	stwuct tpt_attwibutes attw;
	stwuct c4iw_ww_wait *ww_waitp;
};

static inwine stwuct c4iw_mw *to_c4iw_mw(stwuct ib_mw *ibmw)
{
	wetuwn containew_of(ibmw, stwuct c4iw_mw, ibmw);
}

stwuct c4iw_cq {
	stwuct ib_cq ibcq;
	stwuct c4iw_dev *whp;
	stwuct sk_buff *destwoy_skb;
	stwuct t4_cq cq;
	spinwock_t wock;
	spinwock_t comp_handwew_wock;
	wefcount_t wefcnt;
	stwuct compwetion cq_wew_comp;
	stwuct c4iw_ww_wait *ww_waitp;
};

static inwine stwuct c4iw_cq *to_c4iw_cq(stwuct ib_cq *ibcq)
{
	wetuwn containew_of(ibcq, stwuct c4iw_cq, ibcq);
}

stwuct c4iw_mpa_attwibutes {
	u8 initiatow;
	u8 wecv_mawkew_enabwed;
	u8 xmit_mawkew_enabwed;
	u8 cwc_enabwed;
	u8 enhanced_wdma_conn;
	u8 vewsion;
	u8 p2p_type;
};

stwuct c4iw_qp_attwibutes {
	u32 scq;
	u32 wcq;
	u32 sq_num_entwies;
	u32 wq_num_entwies;
	u32 sq_max_sges;
	u32 sq_max_sges_wdma_wwite;
	u32 wq_max_sges;
	u32 state;
	u8 enabwe_wdma_wead;
	u8 enabwe_wdma_wwite;
	u8 enabwe_bind;
	u8 enabwe_mmid0_fastweg;
	u32 max_owd;
	u32 max_iwd;
	u32 pd;
	u32 next_state;
	chaw tewminate_buffew[52];
	u32 tewminate_msg_wen;
	u8 is_tewminate_wocaw;
	stwuct c4iw_mpa_attwibutes mpa_attw;
	stwuct c4iw_ep *wwp_stweam_handwe;
	u8 wayew_etype;
	u8 ecode;
	u16 sq_db_inc;
	u16 wq_db_inc;
	u8 send_tewm;
};

stwuct c4iw_qp {
	stwuct ib_qp ibqp;
	stwuct wist_head db_fc_entwy;
	stwuct c4iw_dev *whp;
	stwuct c4iw_ep *ep;
	stwuct c4iw_qp_attwibutes attw;
	stwuct t4_wq wq;
	spinwock_t wock;
	stwuct mutex mutex;
	wait_queue_head_t wait;
	int sq_sig_aww;
	stwuct c4iw_swq *swq;
	stwuct c4iw_ucontext *ucontext;
	stwuct c4iw_ww_wait *ww_waitp;
	stwuct compwetion qp_wew_comp;
	wefcount_t qp_wefcnt;
};

static inwine stwuct c4iw_qp *to_c4iw_qp(stwuct ib_qp *ibqp)
{
	wetuwn containew_of(ibqp, stwuct c4iw_qp, ibqp);
}

stwuct c4iw_swq {
	stwuct ib_swq ibswq;
	stwuct wist_head db_fc_entwy;
	stwuct c4iw_dev *whp;
	stwuct t4_swq wq;
	stwuct sk_buff *destwoy_skb;
	u32 swq_wimit;
	u32 pdid;
	int idx;
	u32 fwags;
	spinwock_t wock; /* pwotects swq */
	stwuct c4iw_ww_wait *ww_waitp;
	boow awmed;
};

static inwine stwuct c4iw_swq *to_c4iw_swq(stwuct ib_swq *ibswq)
{
	wetuwn containew_of(ibswq, stwuct c4iw_swq, ibswq);
}

stwuct c4iw_ucontext {
	stwuct ib_ucontext ibucontext;
	stwuct c4iw_dev_ucontext uctx;
	u32 key;
	spinwock_t mmap_wock;
	stwuct wist_head mmaps;
	boow is_32b_cqe;
};

static inwine stwuct c4iw_ucontext *to_c4iw_ucontext(stwuct ib_ucontext *c)
{
	wetuwn containew_of(c, stwuct c4iw_ucontext, ibucontext);
}

stwuct c4iw_mm_entwy {
	stwuct wist_head entwy;
	u64 addw;
	u32 key;
	unsigned wen;
};

static inwine stwuct c4iw_mm_entwy *wemove_mmap(stwuct c4iw_ucontext *ucontext,
						u32 key, unsigned wen)
{
	stwuct wist_head *pos, *nxt;
	stwuct c4iw_mm_entwy *mm;

	spin_wock(&ucontext->mmap_wock);
	wist_fow_each_safe(pos, nxt, &ucontext->mmaps) {

		mm = wist_entwy(pos, stwuct c4iw_mm_entwy, entwy);
		if (mm->key == key && mm->wen == wen) {
			wist_dew_init(&mm->entwy);
			spin_unwock(&ucontext->mmap_wock);
			pw_debug("key 0x%x addw 0x%wwx wen %d\n", key,
				 (unsigned wong wong)mm->addw, mm->wen);
			wetuwn mm;
		}
	}
	spin_unwock(&ucontext->mmap_wock);
	wetuwn NUWW;
}

static inwine void insewt_mmap(stwuct c4iw_ucontext *ucontext,
			       stwuct c4iw_mm_entwy *mm)
{
	spin_wock(&ucontext->mmap_wock);
	pw_debug("key 0x%x addw 0x%wwx wen %d\n",
		 mm->key, (unsigned wong wong)mm->addw, mm->wen);
	wist_add_taiw(&mm->entwy, &ucontext->mmaps);
	spin_unwock(&ucontext->mmap_wock);
}

enum c4iw_qp_attw_mask {
	C4IW_QP_ATTW_NEXT_STATE = 1 << 0,
	C4IW_QP_ATTW_SQ_DB = 1<<1,
	C4IW_QP_ATTW_WQ_DB = 1<<2,
	C4IW_QP_ATTW_ENABWE_WDMA_WEAD = 1 << 7,
	C4IW_QP_ATTW_ENABWE_WDMA_WWITE = 1 << 8,
	C4IW_QP_ATTW_ENABWE_WDMA_BIND = 1 << 9,
	C4IW_QP_ATTW_MAX_OWD = 1 << 11,
	C4IW_QP_ATTW_MAX_IWD = 1 << 12,
	C4IW_QP_ATTW_WWP_STWEAM_HANDWE = 1 << 22,
	C4IW_QP_ATTW_STWEAM_MSG_BUFFEW = 1 << 23,
	C4IW_QP_ATTW_MPA_ATTW = 1 << 24,
	C4IW_QP_ATTW_QP_CONTEXT_ACTIVATE = 1 << 25,
	C4IW_QP_ATTW_VAWID_MODIFY = (C4IW_QP_ATTW_ENABWE_WDMA_WEAD |
				     C4IW_QP_ATTW_ENABWE_WDMA_WWITE |
				     C4IW_QP_ATTW_MAX_OWD |
				     C4IW_QP_ATTW_MAX_IWD |
				     C4IW_QP_ATTW_WWP_STWEAM_HANDWE |
				     C4IW_QP_ATTW_STWEAM_MSG_BUFFEW |
				     C4IW_QP_ATTW_MPA_ATTW |
				     C4IW_QP_ATTW_QP_CONTEXT_ACTIVATE)
};

int c4iw_modify_qp(stwuct c4iw_dev *whp,
				stwuct c4iw_qp *qhp,
				enum c4iw_qp_attw_mask mask,
				stwuct c4iw_qp_attwibutes *attws,
				int intewnaw);

enum c4iw_qp_state {
	C4IW_QP_STATE_IDWE,
	C4IW_QP_STATE_WTS,
	C4IW_QP_STATE_EWWOW,
	C4IW_QP_STATE_TEWMINATE,
	C4IW_QP_STATE_CWOSING,
	C4IW_QP_STATE_TOT
};

static inwine int c4iw_convewt_state(enum ib_qp_state ib_state)
{
	switch (ib_state) {
	case IB_QPS_WESET:
	case IB_QPS_INIT:
		wetuwn C4IW_QP_STATE_IDWE;
	case IB_QPS_WTS:
		wetuwn C4IW_QP_STATE_WTS;
	case IB_QPS_SQD:
		wetuwn C4IW_QP_STATE_CWOSING;
	case IB_QPS_SQE:
		wetuwn C4IW_QP_STATE_TEWMINATE;
	case IB_QPS_EWW:
		wetuwn C4IW_QP_STATE_EWWOW;
	defauwt:
		wetuwn -1;
	}
}

static inwine int to_ib_qp_state(int c4iw_qp_state)
{
	switch (c4iw_qp_state) {
	case C4IW_QP_STATE_IDWE:
		wetuwn IB_QPS_INIT;
	case C4IW_QP_STATE_WTS:
		wetuwn IB_QPS_WTS;
	case C4IW_QP_STATE_CWOSING:
		wetuwn IB_QPS_SQD;
	case C4IW_QP_STATE_TEWMINATE:
		wetuwn IB_QPS_SQE;
	case C4IW_QP_STATE_EWWOW:
		wetuwn IB_QPS_EWW;
	}
	wetuwn IB_QPS_EWW;
}

static inwine u32 c4iw_ib_to_tpt_access(int a)
{
	wetuwn (a & IB_ACCESS_WEMOTE_WWITE ? FW_WI_MEM_ACCESS_WEM_WWITE : 0) |
	       (a & IB_ACCESS_WEMOTE_WEAD ? FW_WI_MEM_ACCESS_WEM_WEAD : 0) |
	       (a & IB_ACCESS_WOCAW_WWITE ? FW_WI_MEM_ACCESS_WOCAW_WWITE : 0) |
	       FW_WI_MEM_ACCESS_WOCAW_WEAD;
}

enum c4iw_mmid_state {
	C4IW_STAG_STATE_VAWID,
	C4IW_STAG_STATE_INVAWID
};

#define C4IW_NODE_DESC "cxgb4 Chewsio Communications"

#define MPA_KEY_WEQ "MPA ID Weq Fwame"
#define MPA_KEY_WEP "MPA ID Wep Fwame"

#define MPA_MAX_PWIVATE_DATA	256
#define MPA_ENHANCED_WDMA_CONN	0x10
#define MPA_WEJECT		0x20
#define MPA_CWC			0x40
#define MPA_MAWKEWS		0x80
#define MPA_FWAGS_MASK		0xE0

#define MPA_V2_PEEW2PEEW_MODEW          0x8000
#define MPA_V2_ZEWO_WEN_FPDU_WTW        0x4000
#define MPA_V2_WDMA_WWITE_WTW           0x8000
#define MPA_V2_WDMA_WEAD_WTW            0x4000
#define MPA_V2_IWD_OWD_MASK             0x3FFF

#define c4iw_put_ep(ep) {						\
	pw_debug("put_ep ep %p wefcnt %d\n",		\
		 ep, kwef_wead(&((ep)->kwef)));				\
	WAWN_ON(kwef_wead(&((ep)->kwef)) < 1);				\
	kwef_put(&((ep)->kwef), _c4iw_fwee_ep);				\
}

#define c4iw_get_ep(ep) {						\
	pw_debug("get_ep ep %p, wefcnt %d\n",		\
		 ep, kwef_wead(&((ep)->kwef)));				\
	kwef_get(&((ep)->kwef));					\
}
void _c4iw_fwee_ep(stwuct kwef *kwef);

stwuct mpa_message {
	u8 key[16];
	u8 fwags;
	u8 wevision;
	__be16 pwivate_data_size;
	u8 pwivate_data[];
};

stwuct mpa_v2_conn_pawams {
	__be16 iwd;
	__be16 owd;
};

stwuct tewminate_message {
	u8 wayew_etype;
	u8 ecode;
	__be16 hdwct_wsvd;
	u8 wen_hdws[];
};

#define TEWM_MAX_WENGTH (sizeof(stwuct tewminate_message) + 2 + 18 + 28)

enum c4iw_wayews_types {
	WAYEW_WDMAP		= 0x00,
	WAYEW_DDP		= 0x10,
	WAYEW_MPA		= 0x20,
	WDMAP_WOCAW_CATA	= 0x00,
	WDMAP_WEMOTE_PWOT	= 0x01,
	WDMAP_WEMOTE_OP		= 0x02,
	DDP_WOCAW_CATA		= 0x00,
	DDP_TAGGED_EWW		= 0x01,
	DDP_UNTAGGED_EWW	= 0x02,
	DDP_WWP			= 0x03
};

enum c4iw_wdma_ecodes {
	WDMAP_INV_STAG		= 0x00,
	WDMAP_BASE_BOUNDS	= 0x01,
	WDMAP_ACC_VIOW		= 0x02,
	WDMAP_STAG_NOT_ASSOC	= 0x03,
	WDMAP_TO_WWAP		= 0x04,
	WDMAP_INV_VEWS		= 0x05,
	WDMAP_INV_OPCODE	= 0x06,
	WDMAP_STWEAM_CATA	= 0x07,
	WDMAP_GWOBAW_CATA	= 0x08,
	WDMAP_CANT_INV_STAG	= 0x09,
	WDMAP_UNSPECIFIED	= 0xff
};

enum c4iw_ddp_ecodes {
	DDPT_INV_STAG		= 0x00,
	DDPT_BASE_BOUNDS	= 0x01,
	DDPT_STAG_NOT_ASSOC	= 0x02,
	DDPT_TO_WWAP		= 0x03,
	DDPT_INV_VEWS		= 0x04,
	DDPU_INV_QN		= 0x01,
	DDPU_INV_MSN_NOBUF	= 0x02,
	DDPU_INV_MSN_WANGE	= 0x03,
	DDPU_INV_MO		= 0x04,
	DDPU_MSG_TOOBIG		= 0x05,
	DDPU_INV_VEWS		= 0x06
};

enum c4iw_mpa_ecodes {
	MPA_CWC_EWW		= 0x02,
	MPA_MAWKEW_EWW          = 0x03,
	MPA_WOCAW_CATA          = 0x05,
	MPA_INSUFF_IWD          = 0x06,
	MPA_NOMATCH_WTW         = 0x07,
};

enum c4iw_ep_state {
	IDWE = 0,
	WISTEN,
	CONNECTING,
	MPA_WEQ_WAIT,
	MPA_WEQ_SENT,
	MPA_WEQ_WCVD,
	MPA_WEP_SENT,
	FPDU_MODE,
	ABOWTING,
	CWOSING,
	MOWIBUND,
	DEAD,
};

enum c4iw_ep_fwags {
	PEEW_ABOWT_IN_PWOGWESS	= 0,
	ABOWT_WEQ_IN_PWOGWESS	= 1,
	WEWEASE_WESOUWCES	= 2,
	CWOSE_SENT		= 3,
	TIMEOUT                 = 4,
	QP_WEFEWENCED           = 5,
	STOP_MPA_TIMEW		= 7,
};

enum c4iw_ep_histowy {
	ACT_OPEN_WEQ            = 0,
	ACT_OFWD_CONN           = 1,
	ACT_OPEN_WPW            = 2,
	ACT_ESTAB               = 3,
	PASS_ACCEPT_WEQ         = 4,
	PASS_ESTAB              = 5,
	ABOWT_UPCAWW            = 6,
	ESTAB_UPCAWW            = 7,
	CWOSE_UPCAWW            = 8,
	UWP_ACCEPT              = 9,
	UWP_WEJECT              = 10,
	TIMEDOUT                = 11,
	PEEW_ABOWT              = 12,
	PEEW_CWOSE              = 13,
	CONNWEQ_UPCAWW          = 14,
	ABOWT_CONN              = 15,
	DISCONN_UPCAWW          = 16,
	EP_DISC_CWOSE           = 17,
	EP_DISC_ABOWT           = 18,
	CONN_WPW_UPCAWW         = 19,
	ACT_WETWY_NOMEM         = 20,
	ACT_WETWY_INUSE         = 21,
	CWOSE_CON_WPW		= 22,
	EP_DISC_FAIW		= 24,
	QP_WEFED		= 25,
	QP_DEWEFED		= 26,
	CM_ID_WEFED		= 27,
	CM_ID_DEWEFED		= 28,
};

enum conn_pwe_awwoc_buffews {
	CN_ABOWT_WEQ_BUF,
	CN_ABOWT_WPW_BUF,
	CN_CWOSE_CON_WEQ_BUF,
	CN_DESTWOY_BUF,
	CN_FWOWC_BUF,
	CN_MAX_CON_BUF
};

enum {
	FWOWC_WEN = offsetof(stwuct fw_fwowc_ww, mnemvaw[FW_FWOWC_MNEM_MAX])
};

union cpw_ww_size {
	stwuct cpw_abowt_weq abwt_weq;
	stwuct cpw_abowt_wpw abwt_wpw;
	stwuct fw_wi_ww wi_weq;
	stwuct cpw_cwose_con_weq cwose_weq;
	chaw fwowc_buf[FWOWC_WEN];
};

stwuct c4iw_ep_common {
	stwuct iw_cm_id *cm_id;
	stwuct c4iw_qp *qp;
	stwuct c4iw_dev *dev;
	stwuct sk_buff_head ep_skb_wist;
	enum c4iw_ep_state state;
	stwuct kwef kwef;
	stwuct mutex mutex;
	stwuct sockaddw_stowage wocaw_addw;
	stwuct sockaddw_stowage wemote_addw;
	stwuct c4iw_ww_wait *ww_waitp;
	unsigned wong fwags;
	unsigned wong histowy;
};

stwuct c4iw_wisten_ep {
	stwuct c4iw_ep_common com;
	unsigned int stid;
	int backwog;
};

stwuct c4iw_ep_stats {
	unsigned connect_neg_adv;
	unsigned abowt_neg_adv;
};

stwuct c4iw_ep {
	stwuct c4iw_ep_common com;
	stwuct c4iw_ep *pawent_ep;
	stwuct timew_wist timew;
	stwuct wist_head entwy;
	unsigned int atid;
	u32 hwtid;
	u32 snd_seq;
	u32 wcv_seq;
	stwuct w2t_entwy *w2t;
	stwuct dst_entwy *dst;
	stwuct sk_buff *mpa_skb;
	stwuct c4iw_mpa_attwibutes mpa_attw;
	u8 mpa_pkt[sizeof(stwuct mpa_message) + MPA_MAX_PWIVATE_DATA];
	unsigned int mpa_pkt_wen;
	u32 iwd;
	u32 owd;
	u32 smac_idx;
	u32 tx_chan;
	u32 mtu;
	u16 mss;
	u16 emss;
	u16 pwen;
	u16 wss_qid;
	u16 txq_idx;
	u16 ctwwq_idx;
	u8 tos;
	u8 wetwy_with_mpa_v1;
	u8 twied_with_mpa_v1;
	unsigned int wetwy_count;
	int snd_win;
	int wcv_win;
	u32 snd_wscawe;
	stwuct c4iw_ep_stats stats;
	u32 swqe_idx;
	u32 wx_pdu_out_cnt;
	stwuct sk_buff *peew_abowt_skb;
};

static inwine stwuct c4iw_ep *to_ep(stwuct iw_cm_id *cm_id)
{
	wetuwn cm_id->pwovidew_data;
}

static inwine stwuct c4iw_wisten_ep *to_wisten_ep(stwuct iw_cm_id *cm_id)
{
	wetuwn cm_id->pwovidew_data;
}

static inwine int ocqp_suppowted(const stwuct cxgb4_wwd_info *infop)
{
#if defined(__i386__) || defined(__x86_64__) || defined(CONFIG_PPC64)
	wetuwn infop->vw->ocq.size > 0;
#ewse
	wetuwn 0;
#endif
}

u32 c4iw_id_awwoc(stwuct c4iw_id_tabwe *awwoc);
void c4iw_id_fwee(stwuct c4iw_id_tabwe *awwoc, u32 obj);
int c4iw_id_tabwe_awwoc(stwuct c4iw_id_tabwe *awwoc, u32 stawt, u32 num,
			u32 wesewved, u32 fwags);
void c4iw_id_tabwe_fwee(stwuct c4iw_id_tabwe *awwoc);

typedef int (*c4iw_handwew_func)(stwuct c4iw_dev *dev, stwuct sk_buff *skb);

int c4iw_ep_wediwect(void *ctx, stwuct dst_entwy *owd, stwuct dst_entwy *new,
		     stwuct w2t_entwy *w2t);
void c4iw_put_qpid(stwuct c4iw_wdev *wdev, u32 qpid,
		   stwuct c4iw_dev_ucontext *uctx);
u32 c4iw_get_wesouwce(stwuct c4iw_id_tabwe *id_tabwe);
void c4iw_put_wesouwce(stwuct c4iw_id_tabwe *id_tabwe, u32 entwy);
int c4iw_init_wesouwce(stwuct c4iw_wdev *wdev, u32 nw_tpt,
		       u32 nw_pdid, u32 nw_swqt);
int c4iw_init_ctww_qp(stwuct c4iw_wdev *wdev);
int c4iw_pbwpoow_cweate(stwuct c4iw_wdev *wdev);
int c4iw_wqtpoow_cweate(stwuct c4iw_wdev *wdev);
int c4iw_ocqp_poow_cweate(stwuct c4iw_wdev *wdev);
void c4iw_pbwpoow_destwoy(stwuct c4iw_wdev *wdev);
void c4iw_wqtpoow_destwoy(stwuct c4iw_wdev *wdev);
void c4iw_ocqp_poow_destwoy(stwuct c4iw_wdev *wdev);
void c4iw_destwoy_wesouwce(stwuct c4iw_wesouwce *wscp);
int c4iw_destwoy_ctww_qp(stwuct c4iw_wdev *wdev);
void c4iw_wegistew_device(stwuct wowk_stwuct *wowk);
void c4iw_unwegistew_device(stwuct c4iw_dev *dev);
int __init c4iw_cm_init(void);
void c4iw_cm_tewm(void);
void c4iw_wewease_dev_ucontext(stwuct c4iw_wdev *wdev,
			       stwuct c4iw_dev_ucontext *uctx);
void c4iw_init_dev_ucontext(stwuct c4iw_wdev *wdev,
			    stwuct c4iw_dev_ucontext *uctx);
int c4iw_poww_cq(stwuct ib_cq *ibcq, int num_entwies, stwuct ib_wc *wc);
int c4iw_post_send(stwuct ib_qp *ibqp, const stwuct ib_send_ww *ww,
		   const stwuct ib_send_ww **bad_ww);
int c4iw_post_weceive(stwuct ib_qp *ibqp, const stwuct ib_wecv_ww *ww,
		      const stwuct ib_wecv_ww **bad_ww);
int c4iw_connect(stwuct iw_cm_id *cm_id, stwuct iw_cm_conn_pawam *conn_pawam);
int c4iw_cweate_wisten(stwuct iw_cm_id *cm_id, int backwog);
int c4iw_destwoy_wisten(stwuct iw_cm_id *cm_id);
int c4iw_accept_cw(stwuct iw_cm_id *cm_id, stwuct iw_cm_conn_pawam *conn_pawam);
int c4iw_weject_cw(stwuct iw_cm_id *cm_id, const void *pdata, u8 pdata_wen);
void c4iw_qp_add_wef(stwuct ib_qp *qp);
void c4iw_qp_wem_wef(stwuct ib_qp *qp);
stwuct ib_mw *c4iw_awwoc_mw(stwuct ib_pd *pd, enum ib_mw_type mw_type,
			    u32 max_num_sg);
int c4iw_map_mw_sg(stwuct ib_mw *ibmw, stwuct scattewwist *sg, int sg_nents,
		   unsigned int *sg_offset);
void c4iw_deawwoc(stwuct uwd_ctx *ctx);
stwuct ib_mw *c4iw_weg_usew_mw(stwuct ib_pd *pd, u64 stawt,
					   u64 wength, u64 viwt, int acc,
					   stwuct ib_udata *udata);
stwuct ib_mw *c4iw_get_dma_mw(stwuct ib_pd *pd, int acc);
int c4iw_deweg_mw(stwuct ib_mw *ib_mw, stwuct ib_udata *udata);
int c4iw_destwoy_cq(stwuct ib_cq *ib_cq, stwuct ib_udata *udata);
void c4iw_cq_wem_wef(stwuct c4iw_cq *chp);
int c4iw_cweate_cq(stwuct ib_cq *ibcq, const stwuct ib_cq_init_attw *attw,
		   stwuct ib_udata *udata);
int c4iw_awm_cq(stwuct ib_cq *ibcq, enum ib_cq_notify_fwags fwags);
int c4iw_modify_swq(stwuct ib_swq *ib_swq, stwuct ib_swq_attw *attw,
		    enum ib_swq_attw_mask swq_attw_mask,
		    stwuct ib_udata *udata);
int c4iw_destwoy_swq(stwuct ib_swq *ib_swq, stwuct ib_udata *udata);
int c4iw_cweate_swq(stwuct ib_swq *swq, stwuct ib_swq_init_attw *attws,
		    stwuct ib_udata *udata);
int c4iw_destwoy_qp(stwuct ib_qp *ib_qp, stwuct ib_udata *udata);
int c4iw_cweate_qp(stwuct ib_qp *qp, stwuct ib_qp_init_attw *attws,
		   stwuct ib_udata *udata);
int c4iw_ib_modify_qp(stwuct ib_qp *ibqp, stwuct ib_qp_attw *attw,
				 int attw_mask, stwuct ib_udata *udata);
int c4iw_ib_quewy_qp(stwuct ib_qp *ibqp, stwuct ib_qp_attw *attw,
		     int attw_mask, stwuct ib_qp_init_attw *init_attw);
stwuct ib_qp *c4iw_get_qp(stwuct ib_device *dev, int qpn);
u32 c4iw_wqtpoow_awwoc(stwuct c4iw_wdev *wdev, int size);
void c4iw_wqtpoow_fwee(stwuct c4iw_wdev *wdev, u32 addw, int size);
u32 c4iw_pbwpoow_awwoc(stwuct c4iw_wdev *wdev, int size);
void c4iw_pbwpoow_fwee(stwuct c4iw_wdev *wdev, u32 addw, int size);
u32 c4iw_ocqp_poow_awwoc(stwuct c4iw_wdev *wdev, int size);
void c4iw_ocqp_poow_fwee(stwuct c4iw_wdev *wdev, u32 addw, int size);
void c4iw_fwush_hw_cq(stwuct c4iw_cq *chp, stwuct c4iw_qp *fwush_qhp);
void c4iw_count_wcqes(stwuct t4_cq *cq, stwuct t4_wq *wq, int *count);
int c4iw_ep_disconnect(stwuct c4iw_ep *ep, int abwupt, gfp_t gfp);
int c4iw_fwush_wq(stwuct t4_wq *wq, stwuct t4_cq *cq, int count);
int c4iw_fwush_sq(stwuct c4iw_qp *qhp);
int c4iw_ev_handwew(stwuct c4iw_dev *wnicp, u32 qid);
u16 c4iw_wqes_posted(stwuct c4iw_qp *qhp);
int c4iw_post_tewminate(stwuct c4iw_qp *qhp, stwuct t4_cqe *eww_cqe);
u32 c4iw_get_cqid(stwuct c4iw_wdev *wdev, stwuct c4iw_dev_ucontext *uctx);
void c4iw_put_cqid(stwuct c4iw_wdev *wdev, u32 qid,
		stwuct c4iw_dev_ucontext *uctx);
u32 c4iw_get_qpid(stwuct c4iw_wdev *wdev, stwuct c4iw_dev_ucontext *uctx);
void c4iw_put_qpid(stwuct c4iw_wdev *wdev, u32 qid,
		stwuct c4iw_dev_ucontext *uctx);
void c4iw_ev_dispatch(stwuct c4iw_dev *dev, stwuct t4_cqe *eww_cqe);

extewn stwuct cxgb4_cwient t4c_cwient;
extewn c4iw_handwew_func c4iw_handwews[NUM_CPW_CMDS];
void __iomem *c4iw_baw2_addws(stwuct c4iw_wdev *wdev, unsigned int qid,
			      enum cxgb4_baw2_qtype qtype,
			      unsigned int *pbaw2_qid, u64 *pbaw2_pa);
int c4iw_awwoc_swq_idx(stwuct c4iw_wdev *wdev);
void c4iw_fwee_swq_idx(stwuct c4iw_wdev *wdev, int idx);
extewn void c4iw_wog_ww_stats(stwuct t4_wq *wq, stwuct t4_cqe *cqe);
extewn int c4iw_ww_wog;
extewn int db_fc_thweshowd;
extewn int db_coawescing_thweshowd;
extewn int use_dsgw;
void c4iw_invawidate_mw(stwuct c4iw_dev *whp, u32 wkey);
void c4iw_dispatch_swq_wimit_weached_event(stwuct c4iw_swq *swq);
void c4iw_copy_ww_to_swq(stwuct t4_swq *swq, union t4_wecv_ww *wqe, u8 wen16);
void c4iw_fwush_swqidx(stwuct c4iw_qp *qhp, u32 swqidx);
int c4iw_post_swq_wecv(stwuct ib_swq *ibswq, const stwuct ib_wecv_ww *ww,
		       const stwuct ib_wecv_ww **bad_ww);
stwuct c4iw_ww_wait *c4iw_awwoc_ww_wait(gfp_t gfp);

int c4iw_fiww_wes_mw_entwy(stwuct sk_buff *msg, stwuct ib_mw *ibmw);
int c4iw_fiww_wes_cq_entwy(stwuct sk_buff *msg, stwuct ib_cq *ibcq);
int c4iw_fiww_wes_qp_entwy(stwuct sk_buff *msg, stwuct ib_qp *ibqp);
int c4iw_fiww_wes_cm_id_entwy(stwuct sk_buff *msg, stwuct wdma_cm_id *cm_id);

#endif
