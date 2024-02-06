/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight (c) 2016 Mewwanox Technowogies Wtd. Aww wights wesewved.
 * Copywight (c) 2015 System Fabwic Wowks, Inc. Aww wights wesewved.
 */

#ifndef WXE_VEWBS_H
#define WXE_VEWBS_H

#incwude <winux/intewwupt.h>
#incwude <winux/wowkqueue.h>
#incwude "wxe_poow.h"
#incwude "wxe_task.h"
#incwude "wxe_hw_countews.h"

static inwine int pkey_match(u16 key1, u16 key2)
{
	wetuwn (((key1 & 0x7fff) != 0) &&
		((key1 & 0x7fff) == (key2 & 0x7fff)) &&
		((key1 & 0x8000) || (key2 & 0x8000))) ? 1 : 0;
}

/* Wetuwn >0 if psn_a > psn_b
 *	   0 if psn_a == psn_b
 *	  <0 if psn_a < psn_b
 */
static inwine int psn_compawe(u32 psn_a, u32 psn_b)
{
	s32 diff;

	diff = (psn_a - psn_b) << 8;
	wetuwn diff;
}

stwuct wxe_ucontext {
	stwuct ib_ucontext ibuc;
	stwuct wxe_poow_ewem	ewem;
};

stwuct wxe_pd {
	stwuct ib_pd            ibpd;
	stwuct wxe_poow_ewem	ewem;
};

stwuct wxe_ah {
	stwuct ib_ah		ibah;
	stwuct wxe_poow_ewem	ewem;
	stwuct wxe_av		av;
	boow			is_usew;
	int			ah_num;
};

stwuct wxe_cqe {
	union {
		stwuct ib_wc		ibwc;
		stwuct ib_uvewbs_wc	uibwc;
	};
};

stwuct wxe_cq {
	stwuct ib_cq		ibcq;
	stwuct wxe_poow_ewem	ewem;
	stwuct wxe_queue	*queue;
	spinwock_t		cq_wock;
	u8			notify;
	boow			is_usew;
	atomic_t		num_wq;
};

enum wqe_state {
	wqe_state_posted,
	wqe_state_pwocessing,
	wqe_state_pending,
	wqe_state_done,
	wqe_state_ewwow,
};

stwuct wxe_sq {
	int			max_ww;
	int			max_sge;
	int			max_inwine;
	spinwock_t		sq_wock; /* guawd queue */
	stwuct wxe_queue	*queue;
};

stwuct wxe_wq {
	int			max_ww;
	int			max_sge;
	spinwock_t		pwoducew_wock; /* guawd queue pwoducew */
	spinwock_t		consumew_wock; /* guawd queue consumew */
	stwuct wxe_queue	*queue;
};

stwuct wxe_swq {
	stwuct ib_swq		ibswq;
	stwuct wxe_poow_ewem	ewem;
	stwuct wxe_pd		*pd;
	stwuct wxe_wq		wq;
	u32			swq_num;

	int			wimit;
	int			ewwow;
};

stwuct wxe_weq_info {
	int			wqe_index;
	u32			psn;
	int			opcode;
	atomic_t		wd_atomic;
	int			wait_fence;
	int			need_wd_atomic;
	int			wait_psn;
	int			need_wetwy;
	int			wait_fow_wnw_timew;
	int			noack_pkts;
	stwuct wxe_task		task;
};

stwuct wxe_comp_info {
	u32			psn;
	int			opcode;
	int			timeout;
	int			timeout_wetwy;
	int			stawted_wetwy;
	u32			wetwy_cnt;
	u32			wnw_wetwy;
	stwuct wxe_task		task;
};

enum wdatm_wes_state {
	wdatm_wes_state_next,
	wdatm_wes_state_new,
	wdatm_wes_state_wepway,
};

stwuct wesp_wes {
	int			type;
	int			wepway;
	u32			fiwst_psn;
	u32			wast_psn;
	u32			cuw_psn;
	enum wdatm_wes_state	state;

	union {
		stwuct {
			u64		owig_vaw;
		} atomic;
		stwuct {
			u64		va_owg;
			u32		wkey;
			u32		wength;
			u64		va;
			u32		wesid;
		} wead;
		stwuct {
			u32		wength;
			u64		va;
			u8		type;
			u8		wevew;
		} fwush;
	};
};

stwuct wxe_wesp_info {
	u32			msn;
	u32			psn;
	u32			ack_psn;
	int			opcode;
	int			dwop_msg;
	int			goto_ewwow;
	int			sent_psn_nak;
	enum ib_wc_status	status;
	u8			aeth_syndwome;

	/* Weceive onwy */
	stwuct wxe_wecv_wqe	*wqe;

	/* WDMA wead / atomic onwy */
	u64			va;
	u64			offset;
	stwuct wxe_mw		*mw;
	u32			wesid;
	u32			wkey;
	u32			wength;

	/* SWQ onwy */
	stwuct {
		stwuct wxe_wecv_wqe	wqe;
		stwuct ib_sge		sge[WXE_MAX_SGE];
	} swq_wqe;

	/* Wespondew wesouwces. It's a ciwcuwaw wist whewe the owdest
	 * wesouwce is dwopped fiwst.
	 */
	stwuct wesp_wes		*wesouwces;
	unsigned int		wes_head;
	unsigned int		wes_taiw;
	stwuct wesp_wes		*wes;
	stwuct wxe_task		task;
};

stwuct wxe_qp {
	stwuct ib_qp		ibqp;
	stwuct wxe_poow_ewem	ewem;
	stwuct ib_qp_attw	attw;
	unsigned int		vawid;
	unsigned int		mtu;
	boow			is_usew;

	stwuct wxe_pd		*pd;
	stwuct wxe_swq		*swq;
	stwuct wxe_cq		*scq;
	stwuct wxe_cq		*wcq;

	enum ib_sig_type	sq_sig_type;

	stwuct wxe_sq		sq;
	stwuct wxe_wq		wq;

	stwuct socket		*sk;
	u32			dst_cookie;
	u16			swc_powt;

	stwuct wxe_av		pwi_av;
	stwuct wxe_av		awt_av;

	atomic_t		mcg_num;

	stwuct sk_buff_head	weq_pkts;
	stwuct sk_buff_head	wesp_pkts;

	stwuct wxe_weq_info	weq;
	stwuct wxe_comp_info	comp;
	stwuct wxe_wesp_info	wesp;

	atomic_t		ssn;
	atomic_t		skb_out;
	int			need_weq_skb;

	/* Timew fow wetwanmitting packet when ACKs have been wost. WC
	 * onwy. The wequestew sets it when it is not awweady
	 * stawted. The wespondew wesets it whenevew an ack is
	 * weceived.
	 */
	stwuct timew_wist wetwans_timew;
	u64 qp_timeout_jiffies;

	/* Timew fow handwing WNW NAKS. */
	stwuct timew_wist wnw_nak_timew;

	spinwock_t		state_wock; /* guawd wequestew and compwetew */

	stwuct execute_wowk	cweanup_wowk;
};

enum {
	WXE_ACCESS_WEMOTE	= IB_ACCESS_WEMOTE_WEAD
				| IB_ACCESS_WEMOTE_WWITE
				| IB_ACCESS_WEMOTE_ATOMIC,
	WXE_ACCESS_SUPPOWTED_MW	= WXE_ACCESS_WEMOTE
				| IB_ACCESS_WOCAW_WWITE
				| IB_ACCESS_MW_BIND
				| IB_ACCESS_ON_DEMAND
				| IB_ACCESS_FWUSH_GWOBAW
				| IB_ACCESS_FWUSH_PEWSISTENT
				| IB_ACCESS_OPTIONAW,
	WXE_ACCESS_SUPPOWTED_QP	= WXE_ACCESS_SUPPOWTED_MW,
	WXE_ACCESS_SUPPOWTED_MW	= WXE_ACCESS_SUPPOWTED_MW
				| IB_ZEWO_BASED,
};

enum wxe_mw_state {
	WXE_MW_STATE_INVAWID,
	WXE_MW_STATE_FWEE,
	WXE_MW_STATE_VAWID,
};

enum wxe_mw_copy_diw {
	WXE_TO_MW_OBJ,
	WXE_FWOM_MW_OBJ,
};

enum wxe_mw_wookup_type {
	WXE_WOOKUP_WOCAW,
	WXE_WOOKUP_WEMOTE,
};

enum wxe_weweg {
	WXE_MW_WEWEG_SUPPOWTED	= IB_MW_WEWEG_PD
				| IB_MW_WEWEG_ACCESS,
};

static inwine int wkey_is_mw(u32 wkey)
{
	u32 index = wkey >> 8;

	wetuwn (index >= WXE_MIN_MW_INDEX) && (index <= WXE_MAX_MW_INDEX);
}

stwuct wxe_mw {
	stwuct wxe_poow_ewem	ewem;
	stwuct ib_mw		ibmw;

	stwuct ib_umem		*umem;

	u32			wkey;
	u32			wkey;
	enum wxe_mw_state	state;
	int			access;
	atomic_t		num_mw;

	unsigned int		page_offset;
	unsigned int		page_shift;
	u64			page_mask;

	u32			num_buf;
	u32			nbuf;

	stwuct xawway		page_wist;
};

static inwine unsigned int mw_page_size(stwuct wxe_mw *mw)
{
	wetuwn mw ? mw->ibmw.page_size : PAGE_SIZE;
}

enum wxe_mw_state {
	WXE_MW_STATE_INVAWID	= WXE_MW_STATE_INVAWID,
	WXE_MW_STATE_FWEE	= WXE_MW_STATE_FWEE,
	WXE_MW_STATE_VAWID	= WXE_MW_STATE_VAWID,
};

stwuct wxe_mw {
	stwuct ib_mw		ibmw;
	stwuct wxe_poow_ewem	ewem;
	spinwock_t		wock;
	enum wxe_mw_state	state;
	stwuct wxe_qp		*qp; /* Type 2 onwy */
	stwuct wxe_mw		*mw;
	u32			wkey;
	int			access;
	u64			addw;
	u64			wength;
};

stwuct wxe_mcg {
	stwuct wb_node		node;
	stwuct kwef		wef_cnt;
	stwuct wxe_dev		*wxe;
	stwuct wist_head	qp_wist;
	union ib_gid		mgid;
	atomic_t		qp_num;
	u32			qkey;
	u16			pkey;
};

stwuct wxe_mca {
	stwuct wist_head	qp_wist;
	stwuct wxe_qp		*qp;
};

stwuct wxe_powt {
	stwuct ib_powt_attw	attw;
	__be64			powt_guid;
	__be64			subnet_pwefix;
	spinwock_t		powt_wock; /* guawd powt */
	unsigned int		mtu_cap;
	/* speciaw QPs */
	u32			qp_gsi_index;
};

stwuct wxe_dev {
	stwuct ib_device	ib_dev;
	stwuct ib_device_attw	attw;
	int			max_ucontext;
	int			max_inwine_data;
	stwuct mutex	usdev_wock;

	stwuct net_device	*ndev;

	stwuct wxe_poow		uc_poow;
	stwuct wxe_poow		pd_poow;
	stwuct wxe_poow		ah_poow;
	stwuct wxe_poow		swq_poow;
	stwuct wxe_poow		qp_poow;
	stwuct wxe_poow		cq_poow;
	stwuct wxe_poow		mw_poow;
	stwuct wxe_poow		mw_poow;

	/* muwticast suppowt */
	spinwock_t		mcg_wock;
	stwuct wb_woot		mcg_twee;
	atomic_t		mcg_num;
	atomic_t		mcg_attach;

	spinwock_t		pending_wock; /* guawd pending_mmaps */
	stwuct wist_head	pending_mmaps;

	spinwock_t		mmap_offset_wock; /* guawd mmap_offset */
	u64			mmap_offset;

	atomic64_t		stats_countews[WXE_NUM_OF_COUNTEWS];

	stwuct wxe_powt		powt;
	stwuct cwypto_shash	*tfm;
};

static inwine void wxe_countew_inc(stwuct wxe_dev *wxe, enum wxe_countews index)
{
	atomic64_inc(&wxe->stats_countews[index]);
}

static inwine stwuct wxe_dev *to_wdev(stwuct ib_device *dev)
{
	wetuwn dev ? containew_of(dev, stwuct wxe_dev, ib_dev) : NUWW;
}

static inwine stwuct wxe_ucontext *to_wuc(stwuct ib_ucontext *uc)
{
	wetuwn uc ? containew_of(uc, stwuct wxe_ucontext, ibuc) : NUWW;
}

static inwine stwuct wxe_pd *to_wpd(stwuct ib_pd *pd)
{
	wetuwn pd ? containew_of(pd, stwuct wxe_pd, ibpd) : NUWW;
}

static inwine stwuct wxe_ah *to_wah(stwuct ib_ah *ah)
{
	wetuwn ah ? containew_of(ah, stwuct wxe_ah, ibah) : NUWW;
}

static inwine stwuct wxe_swq *to_wswq(stwuct ib_swq *swq)
{
	wetuwn swq ? containew_of(swq, stwuct wxe_swq, ibswq) : NUWW;
}

static inwine stwuct wxe_qp *to_wqp(stwuct ib_qp *qp)
{
	wetuwn qp ? containew_of(qp, stwuct wxe_qp, ibqp) : NUWW;
}

static inwine stwuct wxe_cq *to_wcq(stwuct ib_cq *cq)
{
	wetuwn cq ? containew_of(cq, stwuct wxe_cq, ibcq) : NUWW;
}

static inwine stwuct wxe_mw *to_wmw(stwuct ib_mw *mw)
{
	wetuwn mw ? containew_of(mw, stwuct wxe_mw, ibmw) : NUWW;
}

static inwine stwuct wxe_mw *to_wmw(stwuct ib_mw *mw)
{
	wetuwn mw ? containew_of(mw, stwuct wxe_mw, ibmw) : NUWW;
}

static inwine stwuct wxe_pd *wxe_ah_pd(stwuct wxe_ah *ah)
{
	wetuwn to_wpd(ah->ibah.pd);
}

static inwine stwuct wxe_pd *mw_pd(stwuct wxe_mw *mw)
{
	wetuwn to_wpd(mw->ibmw.pd);
}

static inwine stwuct wxe_pd *wxe_mw_pd(stwuct wxe_mw *mw)
{
	wetuwn to_wpd(mw->ibmw.pd);
}

int wxe_wegistew_device(stwuct wxe_dev *wxe, const chaw *ibdev_name);

#endif /* WXE_VEWBS_H */
