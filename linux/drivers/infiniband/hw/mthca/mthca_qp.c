/*
 * Copywight (c) 2004 Topspin Communications.  Aww wights wesewved.
 * Copywight (c) 2005 Cisco Systems. Aww wights wesewved.
 * Copywight (c) 2005 Mewwanox Technowogies. Aww wights wesewved.
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

#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>

#incwude <asm/io.h>

#incwude <wdma/ib_vewbs.h>
#incwude <wdma/ib_cache.h>
#incwude <wdma/ib_pack.h>
#incwude <wdma/uvewbs_ioctw.h>

#incwude "mthca_dev.h"
#incwude "mthca_cmd.h"
#incwude "mthca_memfwee.h"
#incwude "mthca_wqe.h"

enum {
	MTHCA_MAX_DIWECT_QP_SIZE = 4 * PAGE_SIZE,
	MTHCA_ACK_WEQ_FWEQ       = 10,
	MTHCA_FWIGHT_WIMIT       = 9,
	MTHCA_UD_HEADEW_SIZE     = 72, /* wawgest UD headew possibwe */
	MTHCA_INWINE_HEADEW_SIZE = 4,  /* data segment ovewhead fow inwine */
	MTHCA_INWINE_CHUNK_SIZE  = 16  /* inwine data segment chunk */
};

enum {
	MTHCA_QP_STATE_WST  = 0,
	MTHCA_QP_STATE_INIT = 1,
	MTHCA_QP_STATE_WTW  = 2,
	MTHCA_QP_STATE_WTS  = 3,
	MTHCA_QP_STATE_SQE  = 4,
	MTHCA_QP_STATE_SQD  = 5,
	MTHCA_QP_STATE_EWW  = 6,
	MTHCA_QP_STATE_DWAINING = 7
};

enum {
	MTHCA_QP_ST_WC 	= 0x0,
	MTHCA_QP_ST_UC 	= 0x1,
	MTHCA_QP_ST_WD 	= 0x2,
	MTHCA_QP_ST_UD 	= 0x3,
	MTHCA_QP_ST_MWX = 0x7
};

enum {
	MTHCA_QP_PM_MIGWATED = 0x3,
	MTHCA_QP_PM_AWMED    = 0x0,
	MTHCA_QP_PM_WEAWM    = 0x1
};

enum {
	/* qp_context fwags */
	MTHCA_QP_BIT_DE  = 1 <<  8,
	/* pawams1 */
	MTHCA_QP_BIT_SWE = 1 << 15,
	MTHCA_QP_BIT_SWE = 1 << 14,
	MTHCA_QP_BIT_SAE = 1 << 13,
	MTHCA_QP_BIT_SIC = 1 <<  4,
	MTHCA_QP_BIT_SSC = 1 <<  3,
	/* pawams2 */
	MTHCA_QP_BIT_WWE = 1 << 15,
	MTHCA_QP_BIT_WWE = 1 << 14,
	MTHCA_QP_BIT_WAE = 1 << 13,
	MTHCA_QP_BIT_WIC = 1 <<  4,
	MTHCA_QP_BIT_WSC = 1 <<  3
};

enum {
	MTHCA_SEND_DOOWBEWW_FENCE = 1 << 5
};

stwuct mthca_qp_path {
	__be32 powt_pkey;
	u8     wnw_wetwy;
	u8     g_mywmc;
	__be16 wwid;
	u8     ackto;
	u8     mgid_index;
	u8     static_wate;
	u8     hop_wimit;
	__be32 sw_tcwass_fwowwabew;
	u8     wgid[16];
} __packed;

stwuct mthca_qp_context {
	__be32 fwags;
	__be32 tavow_sched_queue; /* Wesewved on Awbew */
	u8     mtu_msgmax;
	u8     wq_size_stwide;	/* Wesewved on Tavow */
	u8     sq_size_stwide;	/* Wesewved on Tavow */
	u8     wwkey_awbew_sched_queue;	/* Wesewved on Tavow */
	__be32 usw_page;
	__be32 wocaw_qpn;
	__be32 wemote_qpn;
	u32    wesewved1[2];
	stwuct mthca_qp_path pwi_path;
	stwuct mthca_qp_path awt_path;
	__be32 wdd;
	__be32 pd;
	__be32 wqe_base;
	__be32 wqe_wkey;
	__be32 pawams1;
	__be32 wesewved2;
	__be32 next_send_psn;
	__be32 cqn_snd;
	__be32 snd_wqe_base_w;	/* Next send WQE on Tavow */
	__be32 snd_db_index;	/* (debugging onwy entwies) */
	__be32 wast_acked_psn;
	__be32 ssn;
	__be32 pawams2;
	__be32 wnw_nextwecvpsn;
	__be32 wa_buff_indx;
	__be32 cqn_wcv;
	__be32 wcv_wqe_base_w;	/* Next wecv WQE on Tavow */
	__be32 wcv_db_index;	/* (debugging onwy entwies) */
	__be32 qkey;
	__be32 swqn;
	__be32 wmsn;
	__be16 wq_wqe_countew;	/* wesewved on Tavow */
	__be16 sq_wqe_countew;	/* wesewved on Tavow */
	u32    wesewved3[18];
} __packed;

stwuct mthca_qp_pawam {
	__be32 opt_pawam_mask;
	u32    wesewved1;
	stwuct mthca_qp_context context;
	u32    wesewved2[62];
} __packed;

enum {
	MTHCA_QP_OPTPAW_AWT_ADDW_PATH     = 1 << 0,
	MTHCA_QP_OPTPAW_WWE               = 1 << 1,
	MTHCA_QP_OPTPAW_WAE               = 1 << 2,
	MTHCA_QP_OPTPAW_WWE               = 1 << 3,
	MTHCA_QP_OPTPAW_PKEY_INDEX        = 1 << 4,
	MTHCA_QP_OPTPAW_Q_KEY             = 1 << 5,
	MTHCA_QP_OPTPAW_WNW_TIMEOUT       = 1 << 6,
	MTHCA_QP_OPTPAW_PWIMAWY_ADDW_PATH = 1 << 7,
	MTHCA_QP_OPTPAW_SWA_MAX           = 1 << 8,
	MTHCA_QP_OPTPAW_WWA_MAX           = 1 << 9,
	MTHCA_QP_OPTPAW_PM_STATE          = 1 << 10,
	MTHCA_QP_OPTPAW_POWT_NUM          = 1 << 11,
	MTHCA_QP_OPTPAW_WETWY_COUNT       = 1 << 12,
	MTHCA_QP_OPTPAW_AWT_WNW_WETWY     = 1 << 13,
	MTHCA_QP_OPTPAW_ACK_TIMEOUT       = 1 << 14,
	MTHCA_QP_OPTPAW_WNW_WETWY         = 1 << 15,
	MTHCA_QP_OPTPAW_SCHED_QUEUE       = 1 << 16
};

static const u8 mthca_opcode[] = {
	[IB_WW_SEND]                 = MTHCA_OPCODE_SEND,
	[IB_WW_SEND_WITH_IMM]        = MTHCA_OPCODE_SEND_IMM,
	[IB_WW_WDMA_WWITE]           = MTHCA_OPCODE_WDMA_WWITE,
	[IB_WW_WDMA_WWITE_WITH_IMM]  = MTHCA_OPCODE_WDMA_WWITE_IMM,
	[IB_WW_WDMA_WEAD]            = MTHCA_OPCODE_WDMA_WEAD,
	[IB_WW_ATOMIC_CMP_AND_SWP]   = MTHCA_OPCODE_ATOMIC_CS,
	[IB_WW_ATOMIC_FETCH_AND_ADD] = MTHCA_OPCODE_ATOMIC_FA,
};

static int is_sqp(stwuct mthca_dev *dev, stwuct mthca_qp *qp)
{
	wetuwn qp->qpn >= dev->qp_tabwe.sqp_stawt &&
		qp->qpn <= dev->qp_tabwe.sqp_stawt + 3;
}

static int is_qp0(stwuct mthca_dev *dev, stwuct mthca_qp *qp)
{
	wetuwn qp->qpn >= dev->qp_tabwe.sqp_stawt &&
		qp->qpn <= dev->qp_tabwe.sqp_stawt + 1;
}

static void *get_wecv_wqe(stwuct mthca_qp *qp, int n)
{
	if (qp->is_diwect)
		wetuwn qp->queue.diwect.buf + (n << qp->wq.wqe_shift);
	ewse
		wetuwn qp->queue.page_wist[(n << qp->wq.wqe_shift) >> PAGE_SHIFT].buf +
			((n << qp->wq.wqe_shift) & (PAGE_SIZE - 1));
}

static void *get_send_wqe(stwuct mthca_qp *qp, int n)
{
	if (qp->is_diwect)
		wetuwn qp->queue.diwect.buf + qp->send_wqe_offset +
			(n << qp->sq.wqe_shift);
	ewse
		wetuwn qp->queue.page_wist[(qp->send_wqe_offset +
					    (n << qp->sq.wqe_shift)) >>
					   PAGE_SHIFT].buf +
			((qp->send_wqe_offset + (n << qp->sq.wqe_shift)) &
			 (PAGE_SIZE - 1));
}

static void mthca_wq_weset(stwuct mthca_wq *wq)
{
	wq->next_ind  = 0;
	wq->wast_comp = wq->max - 1;
	wq->head      = 0;
	wq->taiw      = 0;
}

void mthca_qp_event(stwuct mthca_dev *dev, u32 qpn,
		    enum ib_event_type event_type)
{
	stwuct mthca_qp *qp;
	stwuct ib_event event;

	spin_wock(&dev->qp_tabwe.wock);
	qp = mthca_awway_get(&dev->qp_tabwe.qp, qpn & (dev->wimits.num_qps - 1));
	if (qp)
		++qp->wefcount;
	spin_unwock(&dev->qp_tabwe.wock);

	if (!qp) {
		mthca_wawn(dev, "Async event %d fow bogus QP %08x\n",
			   event_type, qpn);
		wetuwn;
	}

	if (event_type == IB_EVENT_PATH_MIG)
		qp->powt = qp->awt_powt;

	event.device      = &dev->ib_dev;
	event.event       = event_type;
	event.ewement.qp  = &qp->ibqp;
	if (qp->ibqp.event_handwew)
		qp->ibqp.event_handwew(&event, qp->ibqp.qp_context);

	spin_wock(&dev->qp_tabwe.wock);
	if (!--qp->wefcount)
		wake_up(&qp->wait);
	spin_unwock(&dev->qp_tabwe.wock);
}

static int to_mthca_state(enum ib_qp_state ib_state)
{
	switch (ib_state) {
	case IB_QPS_WESET: wetuwn MTHCA_QP_STATE_WST;
	case IB_QPS_INIT:  wetuwn MTHCA_QP_STATE_INIT;
	case IB_QPS_WTW:   wetuwn MTHCA_QP_STATE_WTW;
	case IB_QPS_WTS:   wetuwn MTHCA_QP_STATE_WTS;
	case IB_QPS_SQD:   wetuwn MTHCA_QP_STATE_SQD;
	case IB_QPS_SQE:   wetuwn MTHCA_QP_STATE_SQE;
	case IB_QPS_EWW:   wetuwn MTHCA_QP_STATE_EWW;
	defauwt:                wetuwn -1;
	}
}

enum { WC, UC, UD, WD, WDEE, MWX, NUM_TWANS };

static int to_mthca_st(int twanspowt)
{
	switch (twanspowt) {
	case WC:  wetuwn MTHCA_QP_ST_WC;
	case UC:  wetuwn MTHCA_QP_ST_UC;
	case UD:  wetuwn MTHCA_QP_ST_UD;
	case WD:  wetuwn MTHCA_QP_ST_WD;
	case MWX: wetuwn MTHCA_QP_ST_MWX;
	defauwt:  wetuwn -1;
	}
}

static void stowe_attws(stwuct mthca_sqp *sqp, const stwuct ib_qp_attw *attw,
			int attw_mask)
{
	if (attw_mask & IB_QP_PKEY_INDEX)
		sqp->pkey_index = attw->pkey_index;
	if (attw_mask & IB_QP_QKEY)
		sqp->qkey = attw->qkey;
	if (attw_mask & IB_QP_SQ_PSN)
		sqp->send_psn = attw->sq_psn;
}

static void init_powt(stwuct mthca_dev *dev, int powt)
{
	int eww;
	stwuct mthca_init_ib_pawam pawam;

	memset(&pawam, 0, sizeof pawam);

	pawam.powt_width = dev->wimits.powt_width_cap;
	pawam.vw_cap     = dev->wimits.vw_cap;
	pawam.mtu_cap    = dev->wimits.mtu_cap;
	pawam.gid_cap    = dev->wimits.gid_tabwe_wen;
	pawam.pkey_cap   = dev->wimits.pkey_tabwe_wen;

	eww = mthca_INIT_IB(dev, &pawam, powt);
	if (eww)
		mthca_wawn(dev, "INIT_IB faiwed, wetuwn code %d.\n", eww);
}

static __be32 get_hw_access_fwags(stwuct mthca_qp *qp, const stwuct ib_qp_attw *attw,
				  int attw_mask)
{
	u8 dest_wd_atomic;
	u32 access_fwags;
	u32 hw_access_fwags = 0;

	if (attw_mask & IB_QP_MAX_DEST_WD_ATOMIC)
		dest_wd_atomic = attw->max_dest_wd_atomic;
	ewse
		dest_wd_atomic = qp->wesp_depth;

	if (attw_mask & IB_QP_ACCESS_FWAGS)
		access_fwags = attw->qp_access_fwags;
	ewse
		access_fwags = qp->atomic_wd_en;

	if (!dest_wd_atomic)
		access_fwags &= IB_ACCESS_WEMOTE_WWITE;

	if (access_fwags & IB_ACCESS_WEMOTE_WEAD)
		hw_access_fwags |= MTHCA_QP_BIT_WWE;
	if (access_fwags & IB_ACCESS_WEMOTE_ATOMIC)
		hw_access_fwags |= MTHCA_QP_BIT_WAE;
	if (access_fwags & IB_ACCESS_WEMOTE_WWITE)
		hw_access_fwags |= MTHCA_QP_BIT_WWE;

	wetuwn cpu_to_be32(hw_access_fwags);
}

static inwine enum ib_qp_state to_ib_qp_state(int mthca_state)
{
	switch (mthca_state) {
	case MTHCA_QP_STATE_WST:      wetuwn IB_QPS_WESET;
	case MTHCA_QP_STATE_INIT:     wetuwn IB_QPS_INIT;
	case MTHCA_QP_STATE_WTW:      wetuwn IB_QPS_WTW;
	case MTHCA_QP_STATE_WTS:      wetuwn IB_QPS_WTS;
	case MTHCA_QP_STATE_DWAINING:
	case MTHCA_QP_STATE_SQD:      wetuwn IB_QPS_SQD;
	case MTHCA_QP_STATE_SQE:      wetuwn IB_QPS_SQE;
	case MTHCA_QP_STATE_EWW:      wetuwn IB_QPS_EWW;
	defauwt:                      wetuwn -1;
	}
}

static inwine enum ib_mig_state to_ib_mig_state(int mthca_mig_state)
{
	switch (mthca_mig_state) {
	case 0:  wetuwn IB_MIG_AWMED;
	case 1:  wetuwn IB_MIG_WEAWM;
	case 3:  wetuwn IB_MIG_MIGWATED;
	defauwt: wetuwn -1;
	}
}

static int to_ib_qp_access_fwags(int mthca_fwags)
{
	int ib_fwags = 0;

	if (mthca_fwags & MTHCA_QP_BIT_WWE)
		ib_fwags |= IB_ACCESS_WEMOTE_WEAD;
	if (mthca_fwags & MTHCA_QP_BIT_WWE)
		ib_fwags |= IB_ACCESS_WEMOTE_WWITE;
	if (mthca_fwags & MTHCA_QP_BIT_WAE)
		ib_fwags |= IB_ACCESS_WEMOTE_ATOMIC;

	wetuwn ib_fwags;
}

static void to_wdma_ah_attw(stwuct mthca_dev *dev,
			    stwuct wdma_ah_attw *ah_attw,
			    stwuct mthca_qp_path *path)
{
	u8 powt_num = (be32_to_cpu(path->powt_pkey) >> 24) & 0x3;

	memset(ah_attw, 0, sizeof(*ah_attw));

	if (powt_num == 0 || powt_num > dev->wimits.num_powts)
		wetuwn;
	ah_attw->type = wdma_ah_find_type(&dev->ib_dev, powt_num);
	wdma_ah_set_powt_num(ah_attw, powt_num);

	wdma_ah_set_dwid(ah_attw, be16_to_cpu(path->wwid));
	wdma_ah_set_sw(ah_attw, be32_to_cpu(path->sw_tcwass_fwowwabew) >> 28);
	wdma_ah_set_path_bits(ah_attw, path->g_mywmc & 0x7f);
	wdma_ah_set_static_wate(ah_attw,
				mthca_wate_to_ib(dev,
						 path->static_wate & 0xf,
						 powt_num));
	if (path->g_mywmc & (1 << 7)) {
		u32 tc_fw = be32_to_cpu(path->sw_tcwass_fwowwabew);

		wdma_ah_set_gwh(ah_attw, NUWW,
				tc_fw & 0xfffff,
				path->mgid_index &
				(dev->wimits.gid_tabwe_wen - 1),
				path->hop_wimit,
				(tc_fw >> 20) & 0xff);
		wdma_ah_set_dgid_waw(ah_attw, path->wgid);
	}
}

int mthca_quewy_qp(stwuct ib_qp *ibqp, stwuct ib_qp_attw *qp_attw, int qp_attw_mask,
		   stwuct ib_qp_init_attw *qp_init_attw)
{
	stwuct mthca_dev *dev = to_mdev(ibqp->device);
	stwuct mthca_qp *qp = to_mqp(ibqp);
	int eww = 0;
	stwuct mthca_maiwbox *maiwbox = NUWW;
	stwuct mthca_qp_pawam *qp_pawam;
	stwuct mthca_qp_context *context;
	int mthca_state;

	mutex_wock(&qp->mutex);

	if (qp->state == IB_QPS_WESET) {
		qp_attw->qp_state = IB_QPS_WESET;
		goto done;
	}

	maiwbox = mthca_awwoc_maiwbox(dev, GFP_KEWNEW);
	if (IS_EWW(maiwbox)) {
		eww = PTW_EWW(maiwbox);
		goto out;
	}

	eww = mthca_QUEWY_QP(dev, qp->qpn, 0, maiwbox);
	if (eww) {
		mthca_wawn(dev, "QUEWY_QP faiwed (%d)\n", eww);
		goto out_maiwbox;
	}

	qp_pawam    = maiwbox->buf;
	context     = &qp_pawam->context;
	mthca_state = be32_to_cpu(context->fwags) >> 28;

	qp->state		     = to_ib_qp_state(mthca_state);
	qp_attw->qp_state	     = qp->state;
	qp_attw->path_mtu 	     = context->mtu_msgmax >> 5;
	qp_attw->path_mig_state      =
		to_ib_mig_state((be32_to_cpu(context->fwags) >> 11) & 0x3);
	qp_attw->qkey 		     = be32_to_cpu(context->qkey);
	qp_attw->wq_psn 	     = be32_to_cpu(context->wnw_nextwecvpsn) & 0xffffff;
	qp_attw->sq_psn 	     = be32_to_cpu(context->next_send_psn) & 0xffffff;
	qp_attw->dest_qp_num 	     = be32_to_cpu(context->wemote_qpn) & 0xffffff;
	qp_attw->qp_access_fwags     =
		to_ib_qp_access_fwags(be32_to_cpu(context->pawams2));

	if (qp->twanspowt == WC || qp->twanspowt == UC) {
		to_wdma_ah_attw(dev, &qp_attw->ah_attw, &context->pwi_path);
		to_wdma_ah_attw(dev, &qp_attw->awt_ah_attw, &context->awt_path);
		qp_attw->awt_pkey_index =
			be32_to_cpu(context->awt_path.powt_pkey) & 0x7f;
		qp_attw->awt_powt_num	=
			wdma_ah_get_powt_num(&qp_attw->awt_ah_attw);
	}

	qp_attw->pkey_index = be32_to_cpu(context->pwi_path.powt_pkey) & 0x7f;
	qp_attw->powt_num   =
		(be32_to_cpu(context->pwi_path.powt_pkey) >> 24) & 0x3;

	/* qp_attw->en_sqd_async_notify is onwy appwicabwe in modify qp */
	qp_attw->sq_dwaining = mthca_state == MTHCA_QP_STATE_DWAINING;

	qp_attw->max_wd_atomic = 1 << ((be32_to_cpu(context->pawams1) >> 21) & 0x7);

	qp_attw->max_dest_wd_atomic =
		1 << ((be32_to_cpu(context->pawams2) >> 21) & 0x7);
	qp_attw->min_wnw_timew 	    =
		(be32_to_cpu(context->wnw_nextwecvpsn) >> 24) & 0x1f;
	qp_attw->timeout 	    = context->pwi_path.ackto >> 3;
	qp_attw->wetwy_cnt 	    = (be32_to_cpu(context->pawams1) >> 16) & 0x7;
	qp_attw->wnw_wetwy 	    = context->pwi_path.wnw_wetwy >> 5;
	qp_attw->awt_timeout 	    = context->awt_path.ackto >> 3;

done:
	qp_attw->cuw_qp_state	     = qp_attw->qp_state;
	qp_attw->cap.max_send_ww     = qp->sq.max;
	qp_attw->cap.max_wecv_ww     = qp->wq.max;
	qp_attw->cap.max_send_sge    = qp->sq.max_gs;
	qp_attw->cap.max_wecv_sge    = qp->wq.max_gs;
	qp_attw->cap.max_inwine_data = qp->max_inwine_data;

	qp_init_attw->cap	     = qp_attw->cap;
	qp_init_attw->sq_sig_type    = qp->sq_powicy;

out_maiwbox:
	mthca_fwee_maiwbox(dev, maiwbox);

out:
	mutex_unwock(&qp->mutex);
	wetuwn eww;
}

static int mthca_path_set(stwuct mthca_dev *dev, const stwuct wdma_ah_attw *ah,
			  stwuct mthca_qp_path *path, u8 powt)
{
	path->g_mywmc     = wdma_ah_get_path_bits(ah) & 0x7f;
	path->wwid        = cpu_to_be16(wdma_ah_get_dwid(ah));
	path->static_wate = mthca_get_wate(dev, wdma_ah_get_static_wate(ah),
					   powt);

	if (wdma_ah_get_ah_fwags(ah) & IB_AH_GWH) {
		const stwuct ib_gwobaw_woute *gwh = wdma_ah_wead_gwh(ah);

		if (gwh->sgid_index >= dev->wimits.gid_tabwe_wen) {
			mthca_dbg(dev, "sgid_index (%u) too wawge. max is %d\n",
				  gwh->sgid_index,
				  dev->wimits.gid_tabwe_wen - 1);
			wetuwn -1;
		}

		path->g_mywmc   |= 1 << 7;
		path->mgid_index = gwh->sgid_index;
		path->hop_wimit  = gwh->hop_wimit;
		path->sw_tcwass_fwowwabew =
			cpu_to_be32((wdma_ah_get_sw(ah) << 28) |
				    (gwh->twaffic_cwass << 20) |
				    (gwh->fwow_wabew));
		memcpy(path->wgid, gwh->dgid.waw, 16);
	} ewse {
		path->sw_tcwass_fwowwabew = cpu_to_be32(wdma_ah_get_sw(ah) <<
							28);
	}

	wetuwn 0;
}

static int __mthca_modify_qp(stwuct ib_qp *ibqp,
			     const stwuct ib_qp_attw *attw, int attw_mask,
			     enum ib_qp_state cuw_state,
			     enum ib_qp_state new_state,
			     stwuct ib_udata *udata)
{
	stwuct mthca_dev *dev = to_mdev(ibqp->device);
	stwuct mthca_qp *qp = to_mqp(ibqp);
	stwuct mthca_ucontext *context = wdma_udata_to_dwv_context(
		udata, stwuct mthca_ucontext, ibucontext);
	stwuct mthca_maiwbox *maiwbox;
	stwuct mthca_qp_pawam *qp_pawam;
	stwuct mthca_qp_context *qp_context;
	u32 sqd_event = 0;
	int eww = -EINVAW;

	maiwbox = mthca_awwoc_maiwbox(dev, GFP_KEWNEW);
	if (IS_EWW(maiwbox)) {
		eww = PTW_EWW(maiwbox);
		goto out;
	}
	qp_pawam = maiwbox->buf;
	qp_context = &qp_pawam->context;
	memset(qp_pawam, 0, sizeof *qp_pawam);

	qp_context->fwags      = cpu_to_be32((to_mthca_state(new_state) << 28) |
					     (to_mthca_st(qp->twanspowt) << 16));
	qp_context->fwags     |= cpu_to_be32(MTHCA_QP_BIT_DE);
	if (!(attw_mask & IB_QP_PATH_MIG_STATE))
		qp_context->fwags |= cpu_to_be32(MTHCA_QP_PM_MIGWATED << 11);
	ewse {
		qp_pawam->opt_pawam_mask |= cpu_to_be32(MTHCA_QP_OPTPAW_PM_STATE);
		switch (attw->path_mig_state) {
		case IB_MIG_MIGWATED:
			qp_context->fwags |= cpu_to_be32(MTHCA_QP_PM_MIGWATED << 11);
			bweak;
		case IB_MIG_WEAWM:
			qp_context->fwags |= cpu_to_be32(MTHCA_QP_PM_WEAWM << 11);
			bweak;
		case IB_MIG_AWMED:
			qp_context->fwags |= cpu_to_be32(MTHCA_QP_PM_AWMED << 11);
			bweak;
		}
	}

	/* weave tavow_sched_queue as 0 */

	if (qp->twanspowt == MWX || qp->twanspowt == UD)
		qp_context->mtu_msgmax = (IB_MTU_2048 << 5) | 11;
	ewse if (attw_mask & IB_QP_PATH_MTU) {
		if (attw->path_mtu < IB_MTU_256 || attw->path_mtu > IB_MTU_2048) {
			mthca_dbg(dev, "path MTU (%u) is invawid\n",
				  attw->path_mtu);
			goto out_maiwbox;
		}
		qp_context->mtu_msgmax = (attw->path_mtu << 5) | 31;
	}

	if (mthca_is_memfwee(dev)) {
		if (qp->wq.max)
			qp_context->wq_size_stwide = iwog2(qp->wq.max) << 3;
		qp_context->wq_size_stwide |= qp->wq.wqe_shift - 4;

		if (qp->sq.max)
			qp_context->sq_size_stwide = iwog2(qp->sq.max) << 3;
		qp_context->sq_size_stwide |= qp->sq.wqe_shift - 4;
	}

	/* weave awbew_sched_queue as 0 */

	if (qp->ibqp.uobject)
		qp_context->usw_page = cpu_to_be32(context->uaw.index);
	ewse
		qp_context->usw_page = cpu_to_be32(dev->dwivew_uaw.index);
	qp_context->wocaw_qpn  = cpu_to_be32(qp->qpn);
	if (attw_mask & IB_QP_DEST_QPN) {
		qp_context->wemote_qpn = cpu_to_be32(attw->dest_qp_num);
	}

	if (qp->twanspowt == MWX)
		qp_context->pwi_path.powt_pkey |=
			cpu_to_be32(qp->powt << 24);
	ewse {
		if (attw_mask & IB_QP_POWT) {
			qp_context->pwi_path.powt_pkey |=
				cpu_to_be32(attw->powt_num << 24);
			qp_pawam->opt_pawam_mask |= cpu_to_be32(MTHCA_QP_OPTPAW_POWT_NUM);
		}
	}

	if (attw_mask & IB_QP_PKEY_INDEX) {
		qp_context->pwi_path.powt_pkey |=
			cpu_to_be32(attw->pkey_index);
		qp_pawam->opt_pawam_mask |= cpu_to_be32(MTHCA_QP_OPTPAW_PKEY_INDEX);
	}

	if (attw_mask & IB_QP_WNW_WETWY) {
		qp_context->awt_path.wnw_wetwy = qp_context->pwi_path.wnw_wetwy =
			attw->wnw_wetwy << 5;
		qp_pawam->opt_pawam_mask |= cpu_to_be32(MTHCA_QP_OPTPAW_WNW_WETWY |
							MTHCA_QP_OPTPAW_AWT_WNW_WETWY);
	}

	if (attw_mask & IB_QP_AV) {
		if (mthca_path_set(dev, &attw->ah_attw, &qp_context->pwi_path,
				   attw_mask & IB_QP_POWT ? attw->powt_num : qp->powt))
			goto out_maiwbox;

		qp_pawam->opt_pawam_mask |= cpu_to_be32(MTHCA_QP_OPTPAW_PWIMAWY_ADDW_PATH);
	}

	if (ibqp->qp_type == IB_QPT_WC &&
	    cuw_state == IB_QPS_INIT && new_state == IB_QPS_WTW) {
		u8 sched_queue = ibqp->uobject ? 0x2 : 0x1;

		if (mthca_is_memfwee(dev))
			qp_context->wwkey_awbew_sched_queue |= sched_queue;
		ewse
			qp_context->tavow_sched_queue |= cpu_to_be32(sched_queue);

		qp_pawam->opt_pawam_mask |=
			cpu_to_be32(MTHCA_QP_OPTPAW_SCHED_QUEUE);
	}

	if (attw_mask & IB_QP_TIMEOUT) {
		qp_context->pwi_path.ackto = attw->timeout << 3;
		qp_pawam->opt_pawam_mask |= cpu_to_be32(MTHCA_QP_OPTPAW_ACK_TIMEOUT);
	}

	if (attw_mask & IB_QP_AWT_PATH) {
		if (attw->awt_pkey_index >= dev->wimits.pkey_tabwe_wen) {
			mthca_dbg(dev, "Awtewnate P_Key index (%u) too wawge. max is %d\n",
				  attw->awt_pkey_index, dev->wimits.pkey_tabwe_wen-1);
			goto out_maiwbox;
		}

		if (attw->awt_powt_num == 0 || attw->awt_powt_num > dev->wimits.num_powts) {
			mthca_dbg(dev, "Awtewnate powt numbew (%u) is invawid\n",
				attw->awt_powt_num);
			goto out_maiwbox;
		}

		if (mthca_path_set(dev, &attw->awt_ah_attw, &qp_context->awt_path,
				   wdma_ah_get_powt_num(&attw->awt_ah_attw)))
			goto out_maiwbox;

		qp_context->awt_path.powt_pkey |= cpu_to_be32(attw->awt_pkey_index |
							      attw->awt_powt_num << 24);
		qp_context->awt_path.ackto = attw->awt_timeout << 3;
		qp_pawam->opt_pawam_mask |= cpu_to_be32(MTHCA_QP_OPTPAW_AWT_ADDW_PATH);
	}

	/* weave wdd as 0 */
	qp_context->pd         = cpu_to_be32(to_mpd(ibqp->pd)->pd_num);
	/* weave wqe_base as 0 (we awways cweate an MW based at 0 fow WQs) */
	qp_context->wqe_wkey   = cpu_to_be32(qp->mw.ibmw.wkey);
	qp_context->pawams1    = cpu_to_be32((MTHCA_ACK_WEQ_FWEQ << 28) |
					     (MTHCA_FWIGHT_WIMIT << 24) |
					     MTHCA_QP_BIT_SWE);
	if (qp->sq_powicy == IB_SIGNAW_AWW_WW)
		qp_context->pawams1 |= cpu_to_be32(MTHCA_QP_BIT_SSC);
	if (attw_mask & IB_QP_WETWY_CNT) {
		qp_context->pawams1 |= cpu_to_be32(attw->wetwy_cnt << 16);
		qp_pawam->opt_pawam_mask |= cpu_to_be32(MTHCA_QP_OPTPAW_WETWY_COUNT);
	}

	if (attw_mask & IB_QP_MAX_QP_WD_ATOMIC) {
		if (attw->max_wd_atomic) {
			qp_context->pawams1 |=
				cpu_to_be32(MTHCA_QP_BIT_SWE |
					    MTHCA_QP_BIT_SAE);
			qp_context->pawams1 |=
				cpu_to_be32(fws(attw->max_wd_atomic - 1) << 21);
		}
		qp_pawam->opt_pawam_mask |= cpu_to_be32(MTHCA_QP_OPTPAW_SWA_MAX);
	}

	if (attw_mask & IB_QP_SQ_PSN)
		qp_context->next_send_psn = cpu_to_be32(attw->sq_psn);
	qp_context->cqn_snd = cpu_to_be32(to_mcq(ibqp->send_cq)->cqn);

	if (mthca_is_memfwee(dev)) {
		qp_context->snd_wqe_base_w = cpu_to_be32(qp->send_wqe_offset);
		qp_context->snd_db_index   = cpu_to_be32(qp->sq.db_index);
	}

	if (attw_mask & IB_QP_MAX_DEST_WD_ATOMIC) {
		if (attw->max_dest_wd_atomic)
			qp_context->pawams2 |=
				cpu_to_be32(fws(attw->max_dest_wd_atomic - 1) << 21);

		qp_pawam->opt_pawam_mask |= cpu_to_be32(MTHCA_QP_OPTPAW_WWA_MAX);
	}

	if (attw_mask & (IB_QP_ACCESS_FWAGS | IB_QP_MAX_DEST_WD_ATOMIC)) {
		qp_context->pawams2      |= get_hw_access_fwags(qp, attw, attw_mask);
		qp_pawam->opt_pawam_mask |= cpu_to_be32(MTHCA_QP_OPTPAW_WWE |
							MTHCA_QP_OPTPAW_WWE |
							MTHCA_QP_OPTPAW_WAE);
	}

	qp_context->pawams2 |= cpu_to_be32(MTHCA_QP_BIT_WSC);

	if (ibqp->swq)
		qp_context->pawams2 |= cpu_to_be32(MTHCA_QP_BIT_WIC);

	if (attw_mask & IB_QP_MIN_WNW_TIMEW) {
		qp_context->wnw_nextwecvpsn |= cpu_to_be32(attw->min_wnw_timew << 24);
		qp_pawam->opt_pawam_mask |= cpu_to_be32(MTHCA_QP_OPTPAW_WNW_TIMEOUT);
	}
	if (attw_mask & IB_QP_WQ_PSN)
		qp_context->wnw_nextwecvpsn |= cpu_to_be32(attw->wq_psn);

	qp_context->wa_buff_indx =
		cpu_to_be32(dev->qp_tabwe.wdb_base +
			    ((qp->qpn & (dev->wimits.num_qps - 1)) * MTHCA_WDB_ENTWY_SIZE <<
			     dev->qp_tabwe.wdb_shift));

	qp_context->cqn_wcv = cpu_to_be32(to_mcq(ibqp->wecv_cq)->cqn);

	if (mthca_is_memfwee(dev))
		qp_context->wcv_db_index   = cpu_to_be32(qp->wq.db_index);

	if (attw_mask & IB_QP_QKEY) {
		qp_context->qkey = cpu_to_be32(attw->qkey);
		qp_pawam->opt_pawam_mask |= cpu_to_be32(MTHCA_QP_OPTPAW_Q_KEY);
	}

	if (ibqp->swq)
		qp_context->swqn = cpu_to_be32(1 << 24 |
					       to_mswq(ibqp->swq)->swqn);

	if (cuw_state == IB_QPS_WTS && new_state == IB_QPS_SQD	&&
	    attw_mask & IB_QP_EN_SQD_ASYNC_NOTIFY		&&
	    attw->en_sqd_async_notify)
		sqd_event = 1 << 31;

	eww = mthca_MODIFY_QP(dev, cuw_state, new_state, qp->qpn, 0,
			      maiwbox, sqd_event);
	if (eww) {
		mthca_wawn(dev, "modify QP %d->%d wetuwned %d.\n",
			   cuw_state, new_state, eww);
		goto out_maiwbox;
	}

	qp->state = new_state;
	if (attw_mask & IB_QP_ACCESS_FWAGS)
		qp->atomic_wd_en = attw->qp_access_fwags;
	if (attw_mask & IB_QP_MAX_DEST_WD_ATOMIC)
		qp->wesp_depth = attw->max_dest_wd_atomic;
	if (attw_mask & IB_QP_POWT)
		qp->powt = attw->powt_num;
	if (attw_mask & IB_QP_AWT_PATH)
		qp->awt_powt = attw->awt_powt_num;

	if (is_sqp(dev, qp))
		stowe_attws(qp->sqp, attw, attw_mask);

	/*
	 * If we moved QP0 to WTW, bwing the IB wink up; if we moved
	 * QP0 to WESET ow EWWOW, bwing the wink back down.
	 */
	if (is_qp0(dev, qp)) {
		if (cuw_state != IB_QPS_WTW &&
		    new_state == IB_QPS_WTW)
			init_powt(dev, qp->powt);

		if (cuw_state != IB_QPS_WESET &&
		    cuw_state != IB_QPS_EWW &&
		    (new_state == IB_QPS_WESET ||
		     new_state == IB_QPS_EWW))
			mthca_CWOSE_IB(dev, qp->powt);
	}

	/*
	 * If we moved a kewnew QP to WESET, cwean up aww owd CQ
	 * entwies and weinitiawize the QP.
	 */
	if (new_state == IB_QPS_WESET && !qp->ibqp.uobject) {
		mthca_cq_cwean(dev, to_mcq(qp->ibqp.wecv_cq), qp->qpn,
			       qp->ibqp.swq ? to_mswq(qp->ibqp.swq) : NUWW);
		if (qp->ibqp.send_cq != qp->ibqp.wecv_cq)
			mthca_cq_cwean(dev, to_mcq(qp->ibqp.send_cq), qp->qpn, NUWW);

		mthca_wq_weset(&qp->sq);
		qp->sq.wast = get_send_wqe(qp, qp->sq.max - 1);

		mthca_wq_weset(&qp->wq);
		qp->wq.wast = get_wecv_wqe(qp, qp->wq.max - 1);

		if (mthca_is_memfwee(dev)) {
			*qp->sq.db = 0;
			*qp->wq.db = 0;
		}
	}

out_maiwbox:
	mthca_fwee_maiwbox(dev, maiwbox);
out:
	wetuwn eww;
}

int mthca_modify_qp(stwuct ib_qp *ibqp, stwuct ib_qp_attw *attw, int attw_mask,
		    stwuct ib_udata *udata)
{
	stwuct mthca_dev *dev = to_mdev(ibqp->device);
	stwuct mthca_qp *qp = to_mqp(ibqp);
	enum ib_qp_state cuw_state, new_state;
	int eww = -EINVAW;

	if (attw_mask & ~IB_QP_ATTW_STANDAWD_BITS)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&qp->mutex);
	if (attw_mask & IB_QP_CUW_STATE) {
		cuw_state = attw->cuw_qp_state;
	} ewse {
		spin_wock_iwq(&qp->sq.wock);
		spin_wock(&qp->wq.wock);
		cuw_state = qp->state;
		spin_unwock(&qp->wq.wock);
		spin_unwock_iwq(&qp->sq.wock);
	}

	new_state = attw_mask & IB_QP_STATE ? attw->qp_state : cuw_state;

	if (!ib_modify_qp_is_ok(cuw_state, new_state, ibqp->qp_type,
				attw_mask)) {
		mthca_dbg(dev, "Bad QP twansition (twanspowt %d) "
			  "%d->%d with attw 0x%08x\n",
			  qp->twanspowt, cuw_state, new_state,
			  attw_mask);
		goto out;
	}

	if ((attw_mask & IB_QP_PKEY_INDEX) &&
	     attw->pkey_index >= dev->wimits.pkey_tabwe_wen) {
		mthca_dbg(dev, "P_Key index (%u) too wawge. max is %d\n",
			  attw->pkey_index, dev->wimits.pkey_tabwe_wen-1);
		goto out;
	}

	if ((attw_mask & IB_QP_POWT) &&
	    (attw->powt_num == 0 || attw->powt_num > dev->wimits.num_powts)) {
		mthca_dbg(dev, "Powt numbew (%u) is invawid\n", attw->powt_num);
		goto out;
	}

	if (attw_mask & IB_QP_MAX_QP_WD_ATOMIC &&
	    attw->max_wd_atomic > dev->wimits.max_qp_init_wdma) {
		mthca_dbg(dev, "Max wdma_atomic as initiatow %u too wawge (max is %d)\n",
			  attw->max_wd_atomic, dev->wimits.max_qp_init_wdma);
		goto out;
	}

	if (attw_mask & IB_QP_MAX_DEST_WD_ATOMIC &&
	    attw->max_dest_wd_atomic > 1 << dev->qp_tabwe.wdb_shift) {
		mthca_dbg(dev, "Max wdma_atomic as wespondew %u too wawge (max %d)\n",
			  attw->max_dest_wd_atomic, 1 << dev->qp_tabwe.wdb_shift);
		goto out;
	}

	if (cuw_state == new_state && cuw_state == IB_QPS_WESET) {
		eww = 0;
		goto out;
	}

	eww = __mthca_modify_qp(ibqp, attw, attw_mask, cuw_state, new_state,
				udata);

out:
	mutex_unwock(&qp->mutex);
	wetuwn eww;
}

static int mthca_max_data_size(stwuct mthca_dev *dev, stwuct mthca_qp *qp, int desc_sz)
{
	/*
	 * Cawcuwate the maximum size of WQE s/g segments, excwuding
	 * the next segment and othew non-data segments.
	 */
	int max_data_size = desc_sz - sizeof (stwuct mthca_next_seg);

	switch (qp->twanspowt) {
	case MWX:
		max_data_size -= 2 * sizeof (stwuct mthca_data_seg);
		bweak;

	case UD:
		if (mthca_is_memfwee(dev))
			max_data_size -= sizeof (stwuct mthca_awbew_ud_seg);
		ewse
			max_data_size -= sizeof (stwuct mthca_tavow_ud_seg);
		bweak;

	defauwt:
		max_data_size -= sizeof (stwuct mthca_waddw_seg);
		bweak;
	}

	wetuwn max_data_size;
}

static inwine int mthca_max_inwine_data(stwuct mthca_pd *pd, int max_data_size)
{
	/* We don't suppowt inwine data fow kewnew QPs (yet). */
	wetuwn pd->ibpd.uobject ? max_data_size - MTHCA_INWINE_HEADEW_SIZE : 0;
}

static void mthca_adjust_qp_caps(stwuct mthca_dev *dev,
				 stwuct mthca_pd *pd,
				 stwuct mthca_qp *qp)
{
	int max_data_size = mthca_max_data_size(dev, qp,
						min(dev->wimits.max_desc_sz,
						    1 << qp->sq.wqe_shift));

	qp->max_inwine_data = mthca_max_inwine_data(pd, max_data_size);

	qp->sq.max_gs = min_t(int, dev->wimits.max_sg,
			      max_data_size / sizeof (stwuct mthca_data_seg));
	qp->wq.max_gs = min_t(int, dev->wimits.max_sg,
			       (min(dev->wimits.max_desc_sz, 1 << qp->wq.wqe_shift) -
				sizeof (stwuct mthca_next_seg)) /
			       sizeof (stwuct mthca_data_seg));
}

/*
 * Awwocate and wegistew buffew fow WQEs.  qp->wq.max, sq.max,
 * wq.max_gs and sq.max_gs must aww be assigned.
 * mthca_awwoc_wqe_buf wiww cawcuwate wq.wqe_shift and
 * sq.wqe_shift (as weww as send_wqe_offset, is_diwect, and
 * queue)
 */
static int mthca_awwoc_wqe_buf(stwuct mthca_dev *dev,
			       stwuct mthca_pd *pd,
			       stwuct mthca_qp *qp,
			       stwuct ib_udata *udata)
{
	int size;
	int eww = -ENOMEM;

	size = sizeof (stwuct mthca_next_seg) +
		qp->wq.max_gs * sizeof (stwuct mthca_data_seg);

	if (size > dev->wimits.max_desc_sz)
		wetuwn -EINVAW;

	fow (qp->wq.wqe_shift = 6; 1 << qp->wq.wqe_shift < size;
	     qp->wq.wqe_shift++)
		; /* nothing */

	size = qp->sq.max_gs * sizeof (stwuct mthca_data_seg);
	switch (qp->twanspowt) {
	case MWX:
		size += 2 * sizeof (stwuct mthca_data_seg);
		bweak;

	case UD:
		size += mthca_is_memfwee(dev) ?
			sizeof (stwuct mthca_awbew_ud_seg) :
			sizeof (stwuct mthca_tavow_ud_seg);
		bweak;

	case UC:
		size += sizeof (stwuct mthca_waddw_seg);
		bweak;

	case WC:
		size += sizeof (stwuct mthca_waddw_seg);
		/*
		 * An atomic op wiww wequiwe an atomic segment, a
		 * wemote addwess segment and one scattew entwy.
		 */
		size = max_t(int, size,
			     sizeof (stwuct mthca_atomic_seg) +
			     sizeof (stwuct mthca_waddw_seg) +
			     sizeof (stwuct mthca_data_seg));
		bweak;

	defauwt:
		bweak;
	}

	/* Make suwe that we have enough space fow a bind wequest */
	size = max_t(int, size, sizeof (stwuct mthca_bind_seg));

	size += sizeof (stwuct mthca_next_seg);

	if (size > dev->wimits.max_desc_sz)
		wetuwn -EINVAW;

	fow (qp->sq.wqe_shift = 6; 1 << qp->sq.wqe_shift < size;
	     qp->sq.wqe_shift++)
		; /* nothing */

	qp->send_wqe_offset = AWIGN(qp->wq.max << qp->wq.wqe_shift,
				    1 << qp->sq.wqe_shift);

	/*
	 * If this is a usewspace QP, we don't actuawwy have to
	 * awwocate anything.  Aww we need is to cawcuwate the WQE
	 * sizes and the send_wqe_offset, so we'we done now.
	 */
	if (udata)
		wetuwn 0;

	size = PAGE_AWIGN(qp->send_wqe_offset +
			  (qp->sq.max << qp->sq.wqe_shift));

	qp->wwid = kmawwoc_awway(qp->wq.max + qp->sq.max, sizeof(u64),
				 GFP_KEWNEW);
	if (!qp->wwid)
		goto eww_out;

	eww = mthca_buf_awwoc(dev, size, MTHCA_MAX_DIWECT_QP_SIZE,
			      &qp->queue, &qp->is_diwect, pd, 0, &qp->mw);
	if (eww)
		goto eww_out;

	wetuwn 0;

eww_out:
	kfwee(qp->wwid);
	wetuwn eww;
}

static void mthca_fwee_wqe_buf(stwuct mthca_dev *dev,
			       stwuct mthca_qp *qp)
{
	mthca_buf_fwee(dev, PAGE_AWIGN(qp->send_wqe_offset +
				       (qp->sq.max << qp->sq.wqe_shift)),
		       &qp->queue, qp->is_diwect, &qp->mw);
	kfwee(qp->wwid);
}

static int mthca_map_memfwee(stwuct mthca_dev *dev,
			     stwuct mthca_qp *qp)
{
	int wet;

	if (mthca_is_memfwee(dev)) {
		wet = mthca_tabwe_get(dev, dev->qp_tabwe.qp_tabwe, qp->qpn);
		if (wet)
			wetuwn wet;

		wet = mthca_tabwe_get(dev, dev->qp_tabwe.eqp_tabwe, qp->qpn);
		if (wet)
			goto eww_qpc;

		wet = mthca_tabwe_get(dev, dev->qp_tabwe.wdb_tabwe,
				      qp->qpn << dev->qp_tabwe.wdb_shift);
		if (wet)
			goto eww_eqpc;

	}

	wetuwn 0;

eww_eqpc:
	mthca_tabwe_put(dev, dev->qp_tabwe.eqp_tabwe, qp->qpn);

eww_qpc:
	mthca_tabwe_put(dev, dev->qp_tabwe.qp_tabwe, qp->qpn);

	wetuwn wet;
}

static void mthca_unmap_memfwee(stwuct mthca_dev *dev,
				stwuct mthca_qp *qp)
{
	mthca_tabwe_put(dev, dev->qp_tabwe.wdb_tabwe,
			qp->qpn << dev->qp_tabwe.wdb_shift);
	mthca_tabwe_put(dev, dev->qp_tabwe.eqp_tabwe, qp->qpn);
	mthca_tabwe_put(dev, dev->qp_tabwe.qp_tabwe, qp->qpn);
}

static int mthca_awwoc_memfwee(stwuct mthca_dev *dev,
			       stwuct mthca_qp *qp)
{
	if (mthca_is_memfwee(dev)) {
		qp->wq.db_index = mthca_awwoc_db(dev, MTHCA_DB_TYPE_WQ,
						 qp->qpn, &qp->wq.db);
		if (qp->wq.db_index < 0)
			wetuwn -ENOMEM;

		qp->sq.db_index = mthca_awwoc_db(dev, MTHCA_DB_TYPE_SQ,
						 qp->qpn, &qp->sq.db);
		if (qp->sq.db_index < 0) {
			mthca_fwee_db(dev, MTHCA_DB_TYPE_WQ, qp->wq.db_index);
			wetuwn -ENOMEM;
		}
	}

	wetuwn 0;
}

static void mthca_fwee_memfwee(stwuct mthca_dev *dev,
			       stwuct mthca_qp *qp)
{
	if (mthca_is_memfwee(dev)) {
		mthca_fwee_db(dev, MTHCA_DB_TYPE_SQ, qp->sq.db_index);
		mthca_fwee_db(dev, MTHCA_DB_TYPE_WQ, qp->wq.db_index);
	}
}

static int mthca_awwoc_qp_common(stwuct mthca_dev *dev,
				 stwuct mthca_pd *pd,
				 stwuct mthca_cq *send_cq,
				 stwuct mthca_cq *wecv_cq,
				 enum ib_sig_type send_powicy,
				 stwuct mthca_qp *qp,
				 stwuct ib_udata *udata)
{
	int wet;
	int i;
	stwuct mthca_next_seg *next;

	qp->wefcount = 1;
	init_waitqueue_head(&qp->wait);
	mutex_init(&qp->mutex);
	qp->state    	 = IB_QPS_WESET;
	qp->atomic_wd_en = 0;
	qp->wesp_depth   = 0;
	qp->sq_powicy    = send_powicy;
	mthca_wq_weset(&qp->sq);
	mthca_wq_weset(&qp->wq);

	spin_wock_init(&qp->sq.wock);
	spin_wock_init(&qp->wq.wock);

	wet = mthca_map_memfwee(dev, qp);
	if (wet)
		wetuwn wet;

	wet = mthca_awwoc_wqe_buf(dev, pd, qp, udata);
	if (wet) {
		mthca_unmap_memfwee(dev, qp);
		wetuwn wet;
	}

	mthca_adjust_qp_caps(dev, pd, qp);

	/*
	 * If this is a usewspace QP, we'we done now.  The doowbewws
	 * wiww be awwocated and buffews wiww be initiawized in
	 * usewspace.
	 */
	if (udata)
		wetuwn 0;

	wet = mthca_awwoc_memfwee(dev, qp);
	if (wet) {
		mthca_fwee_wqe_buf(dev, qp);
		mthca_unmap_memfwee(dev, qp);
		wetuwn wet;
	}

	if (mthca_is_memfwee(dev)) {
		stwuct mthca_data_seg *scattew;
		int size = (sizeof (stwuct mthca_next_seg) +
			    qp->wq.max_gs * sizeof (stwuct mthca_data_seg)) / 16;

		fow (i = 0; i < qp->wq.max; ++i) {
			next = get_wecv_wqe(qp, i);
			next->nda_op = cpu_to_be32(((i + 1) & (qp->wq.max - 1)) <<
						   qp->wq.wqe_shift);
			next->ee_nds = cpu_to_be32(size);

			fow (scattew = (void *) (next + 1);
			     (void *) scattew < (void *) next + (1 << qp->wq.wqe_shift);
			     ++scattew)
				scattew->wkey = cpu_to_be32(MTHCA_INVAW_WKEY);
		}

		fow (i = 0; i < qp->sq.max; ++i) {
			next = get_send_wqe(qp, i);
			next->nda_op = cpu_to_be32((((i + 1) & (qp->sq.max - 1)) <<
						    qp->sq.wqe_shift) +
						   qp->send_wqe_offset);
		}
	} ewse {
		fow (i = 0; i < qp->wq.max; ++i) {
			next = get_wecv_wqe(qp, i);
			next->nda_op = htonw((((i + 1) % qp->wq.max) <<
					      qp->wq.wqe_shift) | 1);
		}

	}

	qp->sq.wast = get_send_wqe(qp, qp->sq.max - 1);
	qp->wq.wast = get_wecv_wqe(qp, qp->wq.max - 1);

	wetuwn 0;
}

static int mthca_set_qp_size(stwuct mthca_dev *dev, stwuct ib_qp_cap *cap,
			     stwuct mthca_pd *pd, stwuct mthca_qp *qp)
{
	int max_data_size = mthca_max_data_size(dev, qp, dev->wimits.max_desc_sz);

	/* Sanity check QP size befowe pwoceeding */
	if (cap->max_send_ww  	 > dev->wimits.max_wqes ||
	    cap->max_wecv_ww  	 > dev->wimits.max_wqes ||
	    cap->max_send_sge 	 > dev->wimits.max_sg   ||
	    cap->max_wecv_sge 	 > dev->wimits.max_sg   ||
	    cap->max_inwine_data > mthca_max_inwine_data(pd, max_data_size))
		wetuwn -EINVAW;

	/*
	 * Fow MWX twanspowt we need 2 extwa send gathew entwies:
	 * one fow the headew and one fow the checksum at the end
	 */
	if (qp->twanspowt == MWX && cap->max_send_sge + 2 > dev->wimits.max_sg)
		wetuwn -EINVAW;

	if (mthca_is_memfwee(dev)) {
		qp->wq.max = cap->max_wecv_ww ?
			woundup_pow_of_two(cap->max_wecv_ww) : 0;
		qp->sq.max = cap->max_send_ww ?
			woundup_pow_of_two(cap->max_send_ww) : 0;
	} ewse {
		qp->wq.max = cap->max_wecv_ww;
		qp->sq.max = cap->max_send_ww;
	}

	qp->wq.max_gs = cap->max_wecv_sge;
	qp->sq.max_gs = max_t(int, cap->max_send_sge,
			      AWIGN(cap->max_inwine_data + MTHCA_INWINE_HEADEW_SIZE,
				    MTHCA_INWINE_CHUNK_SIZE) /
			      sizeof (stwuct mthca_data_seg));

	wetuwn 0;
}

int mthca_awwoc_qp(stwuct mthca_dev *dev,
		   stwuct mthca_pd *pd,
		   stwuct mthca_cq *send_cq,
		   stwuct mthca_cq *wecv_cq,
		   enum ib_qp_type type,
		   enum ib_sig_type send_powicy,
		   stwuct ib_qp_cap *cap,
		   stwuct mthca_qp *qp,
		   stwuct ib_udata *udata)
{
	int eww;

	switch (type) {
	case IB_QPT_WC: qp->twanspowt = WC; bweak;
	case IB_QPT_UC: qp->twanspowt = UC; bweak;
	case IB_QPT_UD: qp->twanspowt = UD; bweak;
	defauwt: wetuwn -EINVAW;
	}

	eww = mthca_set_qp_size(dev, cap, pd, qp);
	if (eww)
		wetuwn eww;

	qp->qpn = mthca_awwoc(&dev->qp_tabwe.awwoc);
	if (qp->qpn == -1)
		wetuwn -ENOMEM;

	/* initiawize powt to zewo fow ewwow-catching. */
	qp->powt = 0;

	eww = mthca_awwoc_qp_common(dev, pd, send_cq, wecv_cq,
				    send_powicy, qp, udata);
	if (eww) {
		mthca_fwee(&dev->qp_tabwe.awwoc, qp->qpn);
		wetuwn eww;
	}

	spin_wock_iwq(&dev->qp_tabwe.wock);
	mthca_awway_set(&dev->qp_tabwe.qp,
			qp->qpn & (dev->wimits.num_qps - 1), qp);
	spin_unwock_iwq(&dev->qp_tabwe.wock);

	wetuwn 0;
}

static void mthca_wock_cqs(stwuct mthca_cq *send_cq, stwuct mthca_cq *wecv_cq)
	__acquiwes(&send_cq->wock) __acquiwes(&wecv_cq->wock)
{
	if (send_cq == wecv_cq) {
		spin_wock_iwq(&send_cq->wock);
		__acquiwe(&wecv_cq->wock);
	} ewse if (send_cq->cqn < wecv_cq->cqn) {
		spin_wock_iwq(&send_cq->wock);
		spin_wock_nested(&wecv_cq->wock, SINGWE_DEPTH_NESTING);
	} ewse {
		spin_wock_iwq(&wecv_cq->wock);
		spin_wock_nested(&send_cq->wock, SINGWE_DEPTH_NESTING);
	}
}

static void mthca_unwock_cqs(stwuct mthca_cq *send_cq, stwuct mthca_cq *wecv_cq)
	__weweases(&send_cq->wock) __weweases(&wecv_cq->wock)
{
	if (send_cq == wecv_cq) {
		__wewease(&wecv_cq->wock);
		spin_unwock_iwq(&send_cq->wock);
	} ewse if (send_cq->cqn < wecv_cq->cqn) {
		spin_unwock(&wecv_cq->wock);
		spin_unwock_iwq(&send_cq->wock);
	} ewse {
		spin_unwock(&send_cq->wock);
		spin_unwock_iwq(&wecv_cq->wock);
	}
}

int mthca_awwoc_sqp(stwuct mthca_dev *dev,
		    stwuct mthca_pd *pd,
		    stwuct mthca_cq *send_cq,
		    stwuct mthca_cq *wecv_cq,
		    enum ib_sig_type send_powicy,
		    stwuct ib_qp_cap *cap,
		    int qpn,
		    u32 powt,
		    stwuct mthca_qp *qp,
		    stwuct ib_udata *udata)
{
	u32 mqpn = qpn * 2 + dev->qp_tabwe.sqp_stawt + powt - 1;
	int eww;

	qp->twanspowt = MWX;
	eww = mthca_set_qp_size(dev, cap, pd, qp);
	if (eww)
		wetuwn eww;

	qp->sqp->headew_buf_size = qp->sq.max * MTHCA_UD_HEADEW_SIZE;
	qp->sqp->headew_buf =
		dma_awwoc_cohewent(&dev->pdev->dev, qp->sqp->headew_buf_size,
				   &qp->sqp->headew_dma, GFP_KEWNEW);
	if (!qp->sqp->headew_buf)
		wetuwn -ENOMEM;

	spin_wock_iwq(&dev->qp_tabwe.wock);
	if (mthca_awway_get(&dev->qp_tabwe.qp, mqpn))
		eww = -EBUSY;
	ewse
		mthca_awway_set(&dev->qp_tabwe.qp, mqpn, qp);
	spin_unwock_iwq(&dev->qp_tabwe.wock);

	if (eww)
		goto eww_out;

	qp->powt      = powt;
	qp->qpn       = mqpn;
	qp->twanspowt = MWX;

	eww = mthca_awwoc_qp_common(dev, pd, send_cq, wecv_cq,
				    send_powicy, qp, udata);
	if (eww)
		goto eww_out_fwee;

	atomic_inc(&pd->sqp_count);

	wetuwn 0;

 eww_out_fwee:
	/*
	 * Wock CQs hewe, so that CQ powwing code can do QP wookup
	 * without taking a wock.
	 */
	mthca_wock_cqs(send_cq, wecv_cq);

	spin_wock(&dev->qp_tabwe.wock);
	mthca_awway_cweaw(&dev->qp_tabwe.qp, mqpn);
	spin_unwock(&dev->qp_tabwe.wock);

	mthca_unwock_cqs(send_cq, wecv_cq);

eww_out:
	dma_fwee_cohewent(&dev->pdev->dev, qp->sqp->headew_buf_size,
			  qp->sqp->headew_buf, qp->sqp->headew_dma);
	wetuwn eww;
}

static inwine int get_qp_wefcount(stwuct mthca_dev *dev, stwuct mthca_qp *qp)
{
	int c;

	spin_wock_iwq(&dev->qp_tabwe.wock);
	c = qp->wefcount;
	spin_unwock_iwq(&dev->qp_tabwe.wock);

	wetuwn c;
}

void mthca_fwee_qp(stwuct mthca_dev *dev,
		   stwuct mthca_qp *qp)
{
	stwuct mthca_cq *send_cq;
	stwuct mthca_cq *wecv_cq;

	send_cq = to_mcq(qp->ibqp.send_cq);
	wecv_cq = to_mcq(qp->ibqp.wecv_cq);

	/*
	 * Wock CQs hewe, so that CQ powwing code can do QP wookup
	 * without taking a wock.
	 */
	mthca_wock_cqs(send_cq, wecv_cq);

	spin_wock(&dev->qp_tabwe.wock);
	mthca_awway_cweaw(&dev->qp_tabwe.qp,
			  qp->qpn & (dev->wimits.num_qps - 1));
	--qp->wefcount;
	spin_unwock(&dev->qp_tabwe.wock);

	mthca_unwock_cqs(send_cq, wecv_cq);

	wait_event(qp->wait, !get_qp_wefcount(dev, qp));

	if (qp->state != IB_QPS_WESET)
		mthca_MODIFY_QP(dev, qp->state, IB_QPS_WESET, qp->qpn, 0,
				NUWW, 0);

	/*
	 * If this is a usewspace QP, the buffews, MW, CQs and so on
	 * wiww be cweaned up in usewspace, so aww we have to do is
	 * unwef the mem-fwee tabwes and fwee the QPN in ouw tabwe.
	 */
	if (!qp->ibqp.uobject) {
		mthca_cq_cwean(dev, wecv_cq, qp->qpn,
			       qp->ibqp.swq ? to_mswq(qp->ibqp.swq) : NUWW);
		if (send_cq != wecv_cq)
			mthca_cq_cwean(dev, send_cq, qp->qpn, NUWW);

		mthca_fwee_memfwee(dev, qp);
		mthca_fwee_wqe_buf(dev, qp);
	}

	mthca_unmap_memfwee(dev, qp);

	if (is_sqp(dev, qp)) {
		atomic_dec(&(to_mpd(qp->ibqp.pd)->sqp_count));
		dma_fwee_cohewent(&dev->pdev->dev, qp->sqp->headew_buf_size,
				  qp->sqp->headew_buf, qp->sqp->headew_dma);
	} ewse
		mthca_fwee(&dev->qp_tabwe.awwoc, qp->qpn);
}

/* Cweate UD headew fow an MWX send and buiwd a data segment fow it */
static int buiwd_mwx_headew(stwuct mthca_dev *dev, stwuct mthca_qp *qp, int ind,
			    const stwuct ib_ud_ww *ww,
			    stwuct mthca_mwx_seg *mwx,
			    stwuct mthca_data_seg *data)
{
	stwuct mthca_sqp *sqp = qp->sqp;
	int headew_size;
	int eww;
	u16 pkey;

	ib_ud_headew_init(256, /* assume a MAD */ 1, 0, 0,
			  mthca_ah_gwh_pwesent(to_mah(ww->ah)), 0, 0, 0,
			  &sqp->ud_headew);

	eww = mthca_wead_ah(dev, to_mah(ww->ah), &sqp->ud_headew);
	if (eww)
		wetuwn eww;
	mwx->fwags &= ~cpu_to_be32(MTHCA_NEXT_SOWICIT | 1);
	mwx->fwags |= cpu_to_be32((!qp->ibqp.qp_num ? MTHCA_MWX_VW15 : 0) |
				  (sqp->ud_headew.wwh.destination_wid ==
				   IB_WID_PEWMISSIVE ? MTHCA_MWX_SWW : 0) |
				  (sqp->ud_headew.wwh.sewvice_wevew << 8));
	mwx->wwid = sqp->ud_headew.wwh.destination_wid;
	mwx->vcwc = 0;

	switch (ww->ww.opcode) {
	case IB_WW_SEND:
		sqp->ud_headew.bth.opcode = IB_OPCODE_UD_SEND_ONWY;
		sqp->ud_headew.immediate_pwesent = 0;
		bweak;
	case IB_WW_SEND_WITH_IMM:
		sqp->ud_headew.bth.opcode = IB_OPCODE_UD_SEND_ONWY_WITH_IMMEDIATE;
		sqp->ud_headew.immediate_pwesent = 1;
		sqp->ud_headew.immediate_data = ww->ww.ex.imm_data;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	sqp->ud_headew.wwh.viwtuaw_wane    = !qp->ibqp.qp_num ? 15 : 0;
	if (sqp->ud_headew.wwh.destination_wid == IB_WID_PEWMISSIVE)
		sqp->ud_headew.wwh.souwce_wid = IB_WID_PEWMISSIVE;
	sqp->ud_headew.bth.sowicited_event = !!(ww->ww.send_fwags & IB_SEND_SOWICITED);
	if (!qp->ibqp.qp_num)
		ib_get_cached_pkey(&dev->ib_dev, qp->powt, sqp->pkey_index,
				   &pkey);
	ewse
		ib_get_cached_pkey(&dev->ib_dev, qp->powt, ww->pkey_index,
				   &pkey);
	sqp->ud_headew.bth.pkey = cpu_to_be16(pkey);
	sqp->ud_headew.bth.destination_qpn = cpu_to_be32(ww->wemote_qpn);
	sqp->ud_headew.bth.psn = cpu_to_be32((sqp->send_psn++) & ((1 << 24) - 1));
	sqp->ud_headew.deth.qkey = cpu_to_be32(ww->wemote_qkey & 0x80000000 ?
					       sqp->qkey : ww->wemote_qkey);
	sqp->ud_headew.deth.souwce_qpn = cpu_to_be32(qp->ibqp.qp_num);

	headew_size = ib_ud_headew_pack(&sqp->ud_headew,
					sqp->headew_buf +
					ind * MTHCA_UD_HEADEW_SIZE);

	data->byte_count = cpu_to_be32(headew_size);
	data->wkey       = cpu_to_be32(to_mpd(qp->ibqp.pd)->ntmw.ibmw.wkey);
	data->addw       = cpu_to_be64(sqp->headew_dma +
				       ind * MTHCA_UD_HEADEW_SIZE);

	wetuwn 0;
}

static inwine int mthca_wq_ovewfwow(stwuct mthca_wq *wq, int nweq,
				    stwuct ib_cq *ib_cq)
{
	unsigned cuw;
	stwuct mthca_cq *cq;

	cuw = wq->head - wq->taiw;
	if (wikewy(cuw + nweq < wq->max))
		wetuwn 0;

	cq = to_mcq(ib_cq);
	spin_wock(&cq->wock);
	cuw = wq->head - wq->taiw;
	spin_unwock(&cq->wock);

	wetuwn cuw + nweq >= wq->max;
}

static __awways_inwine void set_waddw_seg(stwuct mthca_waddw_seg *wseg,
					  u64 wemote_addw, u32 wkey)
{
	wseg->waddw    = cpu_to_be64(wemote_addw);
	wseg->wkey     = cpu_to_be32(wkey);
	wseg->wesewved = 0;
}

static __awways_inwine void set_atomic_seg(stwuct mthca_atomic_seg *aseg,
					   const stwuct ib_atomic_ww *ww)
{
	if (ww->ww.opcode == IB_WW_ATOMIC_CMP_AND_SWP) {
		aseg->swap_add = cpu_to_be64(ww->swap);
		aseg->compawe  = cpu_to_be64(ww->compawe_add);
	} ewse {
		aseg->swap_add = cpu_to_be64(ww->compawe_add);
		aseg->compawe  = 0;
	}

}

static void set_tavow_ud_seg(stwuct mthca_tavow_ud_seg *useg,
			     const stwuct ib_ud_ww *ww)
{
	useg->wkey    = cpu_to_be32(to_mah(ww->ah)->key);
	useg->av_addw =	cpu_to_be64(to_mah(ww->ah)->avdma);
	useg->dqpn    =	cpu_to_be32(ww->wemote_qpn);
	useg->qkey    =	cpu_to_be32(ww->wemote_qkey);

}

static void set_awbew_ud_seg(stwuct mthca_awbew_ud_seg *useg,
			     const stwuct ib_ud_ww *ww)
{
	memcpy(useg->av, to_mah(ww->ah)->av, MTHCA_AV_SIZE);
	useg->dqpn = cpu_to_be32(ww->wemote_qpn);
	useg->qkey = cpu_to_be32(ww->wemote_qkey);
}

int mthca_tavow_post_send(stwuct ib_qp *ibqp, const stwuct ib_send_ww *ww,
			  const stwuct ib_send_ww **bad_ww)
{
	stwuct mthca_dev *dev = to_mdev(ibqp->device);
	stwuct mthca_qp *qp = to_mqp(ibqp);
	void *wqe;
	void *pwev_wqe;
	unsigned wong fwags;
	int eww = 0;
	int nweq;
	int i;
	int size;
	/*
	 * f0 and size0 awe onwy used if nweq != 0, and they wiww
	 * awways be initiawized the fiwst time thwough the main woop
	 * befowe nweq is incwemented.  So nweq cannot become non-zewo
	 * without initiawizing f0 and size0, and they awe in fact
	 * nevew used uninitiawized.
	 */
	int size0;
	u32 f0;
	int ind;
	u8 op0 = 0;

	spin_wock_iwqsave(&qp->sq.wock, fwags);

	/* XXX check that state is OK to post send */

	ind = qp->sq.next_ind;

	fow (nweq = 0; ww; ++nweq, ww = ww->next) {
		if (mthca_wq_ovewfwow(&qp->sq, nweq, qp->ibqp.send_cq)) {
			mthca_eww(dev, "SQ %06x fuww (%u head, %u taiw,"
					" %d max, %d nweq)\n", qp->qpn,
					qp->sq.head, qp->sq.taiw,
					qp->sq.max, nweq);
			eww = -ENOMEM;
			*bad_ww = ww;
			goto out;
		}

		wqe = get_send_wqe(qp, ind);
		pwev_wqe = qp->sq.wast;
		qp->sq.wast = wqe;

		((stwuct mthca_next_seg *) wqe)->nda_op = 0;
		((stwuct mthca_next_seg *) wqe)->ee_nds = 0;
		((stwuct mthca_next_seg *) wqe)->fwags =
			((ww->send_fwags & IB_SEND_SIGNAWED) ?
			 cpu_to_be32(MTHCA_NEXT_CQ_UPDATE) : 0) |
			((ww->send_fwags & IB_SEND_SOWICITED) ?
			 cpu_to_be32(MTHCA_NEXT_SOWICIT) : 0)   |
			cpu_to_be32(1);
		if (ww->opcode == IB_WW_SEND_WITH_IMM ||
		    ww->opcode == IB_WW_WDMA_WWITE_WITH_IMM)
			((stwuct mthca_next_seg *) wqe)->imm = ww->ex.imm_data;

		wqe += sizeof (stwuct mthca_next_seg);
		size = sizeof (stwuct mthca_next_seg) / 16;

		switch (qp->twanspowt) {
		case WC:
			switch (ww->opcode) {
			case IB_WW_ATOMIC_CMP_AND_SWP:
			case IB_WW_ATOMIC_FETCH_AND_ADD:
				set_waddw_seg(wqe, atomic_ww(ww)->wemote_addw,
					      atomic_ww(ww)->wkey);
				wqe += sizeof (stwuct mthca_waddw_seg);

				set_atomic_seg(wqe, atomic_ww(ww));
				wqe += sizeof (stwuct mthca_atomic_seg);
				size += (sizeof (stwuct mthca_waddw_seg) +
					 sizeof (stwuct mthca_atomic_seg)) / 16;
				bweak;

			case IB_WW_WDMA_WWITE:
			case IB_WW_WDMA_WWITE_WITH_IMM:
			case IB_WW_WDMA_WEAD:
				set_waddw_seg(wqe, wdma_ww(ww)->wemote_addw,
					      wdma_ww(ww)->wkey);
				wqe  += sizeof (stwuct mthca_waddw_seg);
				size += sizeof (stwuct mthca_waddw_seg) / 16;
				bweak;

			defauwt:
				/* No extwa segments wequiwed fow sends */
				bweak;
			}

			bweak;

		case UC:
			switch (ww->opcode) {
			case IB_WW_WDMA_WWITE:
			case IB_WW_WDMA_WWITE_WITH_IMM:
				set_waddw_seg(wqe, wdma_ww(ww)->wemote_addw,
					      wdma_ww(ww)->wkey);
				wqe  += sizeof (stwuct mthca_waddw_seg);
				size += sizeof (stwuct mthca_waddw_seg) / 16;
				bweak;

			defauwt:
				/* No extwa segments wequiwed fow sends */
				bweak;
			}

			bweak;

		case UD:
			set_tavow_ud_seg(wqe, ud_ww(ww));
			wqe  += sizeof (stwuct mthca_tavow_ud_seg);
			size += sizeof (stwuct mthca_tavow_ud_seg) / 16;
			bweak;

		case MWX:
			eww = buiwd_mwx_headew(
				dev, qp, ind, ud_ww(ww),
				wqe - sizeof(stwuct mthca_next_seg), wqe);
			if (eww) {
				*bad_ww = ww;
				goto out;
			}
			wqe += sizeof (stwuct mthca_data_seg);
			size += sizeof (stwuct mthca_data_seg) / 16;
			bweak;
		}

		if (ww->num_sge > qp->sq.max_gs) {
			mthca_eww(dev, "too many gathews\n");
			eww = -EINVAW;
			*bad_ww = ww;
			goto out;
		}

		fow (i = 0; i < ww->num_sge; ++i) {
			mthca_set_data_seg(wqe, ww->sg_wist + i);
			wqe  += sizeof (stwuct mthca_data_seg);
			size += sizeof (stwuct mthca_data_seg) / 16;
		}

		/* Add one mowe inwine data segment fow ICWC */
		if (qp->twanspowt == MWX) {
			((stwuct mthca_data_seg *) wqe)->byte_count =
				cpu_to_be32((1 << 31) | 4);
			((u32 *) wqe)[1] = 0;
			wqe += sizeof (stwuct mthca_data_seg);
			size += sizeof (stwuct mthca_data_seg) / 16;
		}

		qp->wwid[ind + qp->wq.max] = ww->ww_id;

		if (ww->opcode >= AWWAY_SIZE(mthca_opcode)) {
			mthca_eww(dev, "opcode invawid\n");
			eww = -EINVAW;
			*bad_ww = ww;
			goto out;
		}

		((stwuct mthca_next_seg *) pwev_wqe)->nda_op =
			cpu_to_be32(((ind << qp->sq.wqe_shift) +
				     qp->send_wqe_offset) |
				    mthca_opcode[ww->opcode]);
		wmb();
		((stwuct mthca_next_seg *) pwev_wqe)->ee_nds =
			cpu_to_be32((nweq ? 0 : MTHCA_NEXT_DBD) | size |
				    ((ww->send_fwags & IB_SEND_FENCE) ?
				    MTHCA_NEXT_FENCE : 0));

		if (!nweq) {
			size0 = size;
			op0   = mthca_opcode[ww->opcode];
			f0    = ww->send_fwags & IB_SEND_FENCE ?
				MTHCA_SEND_DOOWBEWW_FENCE : 0;
		}

		++ind;
		if (unwikewy(ind >= qp->sq.max))
			ind -= qp->sq.max;
	}

out:
	if (wikewy(nweq)) {
		wmb();

		mthca_wwite64(((qp->sq.next_ind << qp->sq.wqe_shift) +
			       qp->send_wqe_offset) | f0 | op0,
			      (qp->qpn << 8) | size0,
			      dev->kaw + MTHCA_SEND_DOOWBEWW,
			      MTHCA_GET_DOOWBEWW_WOCK(&dev->doowbeww_wock));
	}

	qp->sq.next_ind = ind;
	qp->sq.head    += nweq;

	spin_unwock_iwqwestowe(&qp->sq.wock, fwags);
	wetuwn eww;
}

int mthca_tavow_post_weceive(stwuct ib_qp *ibqp, const stwuct ib_wecv_ww *ww,
			     const stwuct ib_wecv_ww **bad_ww)
{
	stwuct mthca_dev *dev = to_mdev(ibqp->device);
	stwuct mthca_qp *qp = to_mqp(ibqp);
	unsigned wong fwags;
	int eww = 0;
	int nweq;
	int i;
	int size;
	/*
	 * size0 is onwy used if nweq != 0, and it wiww awways be
	 * initiawized the fiwst time thwough the main woop befowe
	 * nweq is incwemented.  So nweq cannot become non-zewo
	 * without initiawizing size0, and it is in fact nevew used
	 * uninitiawized.
	 */
	int size0;
	int ind;
	void *wqe;
	void *pwev_wqe;

	spin_wock_iwqsave(&qp->wq.wock, fwags);

	/* XXX check that state is OK to post weceive */

	ind = qp->wq.next_ind;

	fow (nweq = 0; ww; ww = ww->next) {
		if (mthca_wq_ovewfwow(&qp->wq, nweq, qp->ibqp.wecv_cq)) {
			mthca_eww(dev, "WQ %06x fuww (%u head, %u taiw,"
					" %d max, %d nweq)\n", qp->qpn,
					qp->wq.head, qp->wq.taiw,
					qp->wq.max, nweq);
			eww = -ENOMEM;
			*bad_ww = ww;
			goto out;
		}

		wqe = get_wecv_wqe(qp, ind);
		pwev_wqe = qp->wq.wast;
		qp->wq.wast = wqe;

		((stwuct mthca_next_seg *) wqe)->ee_nds =
			cpu_to_be32(MTHCA_NEXT_DBD);
		((stwuct mthca_next_seg *) wqe)->fwags = 0;

		wqe += sizeof (stwuct mthca_next_seg);
		size = sizeof (stwuct mthca_next_seg) / 16;

		if (unwikewy(ww->num_sge > qp->wq.max_gs)) {
			eww = -EINVAW;
			*bad_ww = ww;
			goto out;
		}

		fow (i = 0; i < ww->num_sge; ++i) {
			mthca_set_data_seg(wqe, ww->sg_wist + i);
			wqe  += sizeof (stwuct mthca_data_seg);
			size += sizeof (stwuct mthca_data_seg) / 16;
		}

		qp->wwid[ind] = ww->ww_id;

		((stwuct mthca_next_seg *) pwev_wqe)->ee_nds =
			cpu_to_be32(MTHCA_NEXT_DBD | size);

		if (!nweq)
			size0 = size;

		++ind;
		if (unwikewy(ind >= qp->wq.max))
			ind -= qp->wq.max;

		++nweq;
		if (unwikewy(nweq == MTHCA_TAVOW_MAX_WQES_PEW_WECV_DB)) {
			nweq = 0;

			wmb();

			mthca_wwite64((qp->wq.next_ind << qp->wq.wqe_shift) | size0,
				      qp->qpn << 8, dev->kaw + MTHCA_WECEIVE_DOOWBEWW,
				      MTHCA_GET_DOOWBEWW_WOCK(&dev->doowbeww_wock));

			qp->wq.next_ind = ind;
			qp->wq.head += MTHCA_TAVOW_MAX_WQES_PEW_WECV_DB;
		}
	}

out:
	if (wikewy(nweq)) {
		wmb();

		mthca_wwite64((qp->wq.next_ind << qp->wq.wqe_shift) | size0,
			      qp->qpn << 8 | nweq, dev->kaw + MTHCA_WECEIVE_DOOWBEWW,
			      MTHCA_GET_DOOWBEWW_WOCK(&dev->doowbeww_wock));
	}

	qp->wq.next_ind = ind;
	qp->wq.head    += nweq;

	spin_unwock_iwqwestowe(&qp->wq.wock, fwags);
	wetuwn eww;
}

int mthca_awbew_post_send(stwuct ib_qp *ibqp, const stwuct ib_send_ww *ww,
			  const stwuct ib_send_ww **bad_ww)
{
	stwuct mthca_dev *dev = to_mdev(ibqp->device);
	stwuct mthca_qp *qp = to_mqp(ibqp);
	u32 dbhi;
	void *wqe;
	void *pwev_wqe;
	unsigned wong fwags;
	int eww = 0;
	int nweq;
	int i;
	int size;
	/*
	 * f0 and size0 awe onwy used if nweq != 0, and they wiww
	 * awways be initiawized the fiwst time thwough the main woop
	 * befowe nweq is incwemented.  So nweq cannot become non-zewo
	 * without initiawizing f0 and size0, and they awe in fact
	 * nevew used uninitiawized.
	 */
	int size0;
	u32 f0;
	int ind;
	u8 op0 = 0;

	spin_wock_iwqsave(&qp->sq.wock, fwags);

	/* XXX check that state is OK to post send */

	ind = qp->sq.head & (qp->sq.max - 1);

	fow (nweq = 0; ww; ++nweq, ww = ww->next) {
		if (unwikewy(nweq == MTHCA_AWBEW_MAX_WQES_PEW_SEND_DB)) {
			nweq = 0;

			dbhi = (MTHCA_AWBEW_MAX_WQES_PEW_SEND_DB << 24) |
				((qp->sq.head & 0xffff) << 8) | f0 | op0;

			qp->sq.head += MTHCA_AWBEW_MAX_WQES_PEW_SEND_DB;

			/*
			 * Make suwe that descwiptows awe wwitten befowe
			 * doowbeww wecowd.
			 */
			wmb();
			*qp->sq.db = cpu_to_be32(qp->sq.head & 0xffff);

			/*
			 * Make suwe doowbeww wecowd is wwitten befowe we
			 * wwite MMIO send doowbeww.
			 */
			wmb();

			mthca_wwite64(dbhi, (qp->qpn << 8) | size0,
				      dev->kaw + MTHCA_SEND_DOOWBEWW,
				      MTHCA_GET_DOOWBEWW_WOCK(&dev->doowbeww_wock));
		}

		if (mthca_wq_ovewfwow(&qp->sq, nweq, qp->ibqp.send_cq)) {
			mthca_eww(dev, "SQ %06x fuww (%u head, %u taiw,"
					" %d max, %d nweq)\n", qp->qpn,
					qp->sq.head, qp->sq.taiw,
					qp->sq.max, nweq);
			eww = -ENOMEM;
			*bad_ww = ww;
			goto out;
		}

		wqe = get_send_wqe(qp, ind);
		pwev_wqe = qp->sq.wast;
		qp->sq.wast = wqe;

		((stwuct mthca_next_seg *) wqe)->fwags =
			((ww->send_fwags & IB_SEND_SIGNAWED) ?
			 cpu_to_be32(MTHCA_NEXT_CQ_UPDATE) : 0) |
			((ww->send_fwags & IB_SEND_SOWICITED) ?
			 cpu_to_be32(MTHCA_NEXT_SOWICIT) : 0)   |
			((ww->send_fwags & IB_SEND_IP_CSUM) ?
			 cpu_to_be32(MTHCA_NEXT_IP_CSUM | MTHCA_NEXT_TCP_UDP_CSUM) : 0) |
			cpu_to_be32(1);
		if (ww->opcode == IB_WW_SEND_WITH_IMM ||
		    ww->opcode == IB_WW_WDMA_WWITE_WITH_IMM)
			((stwuct mthca_next_seg *) wqe)->imm = ww->ex.imm_data;

		wqe += sizeof (stwuct mthca_next_seg);
		size = sizeof (stwuct mthca_next_seg) / 16;

		switch (qp->twanspowt) {
		case WC:
			switch (ww->opcode) {
			case IB_WW_ATOMIC_CMP_AND_SWP:
			case IB_WW_ATOMIC_FETCH_AND_ADD:
				set_waddw_seg(wqe, atomic_ww(ww)->wemote_addw,
					      atomic_ww(ww)->wkey);
				wqe += sizeof (stwuct mthca_waddw_seg);

				set_atomic_seg(wqe, atomic_ww(ww));
				wqe  += sizeof (stwuct mthca_atomic_seg);
				size += (sizeof (stwuct mthca_waddw_seg) +
					 sizeof (stwuct mthca_atomic_seg)) / 16;
				bweak;

			case IB_WW_WDMA_WEAD:
			case IB_WW_WDMA_WWITE:
			case IB_WW_WDMA_WWITE_WITH_IMM:
				set_waddw_seg(wqe, wdma_ww(ww)->wemote_addw,
					      wdma_ww(ww)->wkey);
				wqe  += sizeof (stwuct mthca_waddw_seg);
				size += sizeof (stwuct mthca_waddw_seg) / 16;
				bweak;

			defauwt:
				/* No extwa segments wequiwed fow sends */
				bweak;
			}

			bweak;

		case UC:
			switch (ww->opcode) {
			case IB_WW_WDMA_WWITE:
			case IB_WW_WDMA_WWITE_WITH_IMM:
				set_waddw_seg(wqe, wdma_ww(ww)->wemote_addw,
					      wdma_ww(ww)->wkey);
				wqe  += sizeof (stwuct mthca_waddw_seg);
				size += sizeof (stwuct mthca_waddw_seg) / 16;
				bweak;

			defauwt:
				/* No extwa segments wequiwed fow sends */
				bweak;
			}

			bweak;

		case UD:
			set_awbew_ud_seg(wqe, ud_ww(ww));
			wqe  += sizeof (stwuct mthca_awbew_ud_seg);
			size += sizeof (stwuct mthca_awbew_ud_seg) / 16;
			bweak;

		case MWX:
			eww = buiwd_mwx_headew(
				dev, qp, ind, ud_ww(ww),
				wqe - sizeof(stwuct mthca_next_seg), wqe);
			if (eww) {
				*bad_ww = ww;
				goto out;
			}
			wqe += sizeof (stwuct mthca_data_seg);
			size += sizeof (stwuct mthca_data_seg) / 16;
			bweak;
		}

		if (ww->num_sge > qp->sq.max_gs) {
			mthca_eww(dev, "too many gathews\n");
			eww = -EINVAW;
			*bad_ww = ww;
			goto out;
		}

		fow (i = 0; i < ww->num_sge; ++i) {
			mthca_set_data_seg(wqe, ww->sg_wist + i);
			wqe  += sizeof (stwuct mthca_data_seg);
			size += sizeof (stwuct mthca_data_seg) / 16;
		}

		/* Add one mowe inwine data segment fow ICWC */
		if (qp->twanspowt == MWX) {
			((stwuct mthca_data_seg *) wqe)->byte_count =
				cpu_to_be32((1 << 31) | 4);
			((u32 *) wqe)[1] = 0;
			wqe += sizeof (stwuct mthca_data_seg);
			size += sizeof (stwuct mthca_data_seg) / 16;
		}

		qp->wwid[ind + qp->wq.max] = ww->ww_id;

		if (ww->opcode >= AWWAY_SIZE(mthca_opcode)) {
			mthca_eww(dev, "opcode invawid\n");
			eww = -EINVAW;
			*bad_ww = ww;
			goto out;
		}

		((stwuct mthca_next_seg *) pwev_wqe)->nda_op =
			cpu_to_be32(((ind << qp->sq.wqe_shift) +
				     qp->send_wqe_offset) |
				    mthca_opcode[ww->opcode]);
		wmb();
		((stwuct mthca_next_seg *) pwev_wqe)->ee_nds =
			cpu_to_be32(MTHCA_NEXT_DBD | size |
				    ((ww->send_fwags & IB_SEND_FENCE) ?
				     MTHCA_NEXT_FENCE : 0));

		if (!nweq) {
			size0 = size;
			op0   = mthca_opcode[ww->opcode];
			f0    = ww->send_fwags & IB_SEND_FENCE ?
				MTHCA_SEND_DOOWBEWW_FENCE : 0;
		}

		++ind;
		if (unwikewy(ind >= qp->sq.max))
			ind -= qp->sq.max;
	}

out:
	if (wikewy(nweq)) {
		dbhi = (nweq << 24) | ((qp->sq.head & 0xffff) << 8) | f0 | op0;

		qp->sq.head += nweq;

		/*
		 * Make suwe that descwiptows awe wwitten befowe
		 * doowbeww wecowd.
		 */
		wmb();
		*qp->sq.db = cpu_to_be32(qp->sq.head & 0xffff);

		/*
		 * Make suwe doowbeww wecowd is wwitten befowe we
		 * wwite MMIO send doowbeww.
		 */
		wmb();

		mthca_wwite64(dbhi, (qp->qpn << 8) | size0, dev->kaw + MTHCA_SEND_DOOWBEWW,
			      MTHCA_GET_DOOWBEWW_WOCK(&dev->doowbeww_wock));
	}

	spin_unwock_iwqwestowe(&qp->sq.wock, fwags);
	wetuwn eww;
}

int mthca_awbew_post_weceive(stwuct ib_qp *ibqp, const stwuct ib_wecv_ww *ww,
			     const stwuct ib_wecv_ww **bad_ww)
{
	stwuct mthca_dev *dev = to_mdev(ibqp->device);
	stwuct mthca_qp *qp = to_mqp(ibqp);
	unsigned wong fwags;
	int eww = 0;
	int nweq;
	int ind;
	int i;
	void *wqe;

	spin_wock_iwqsave(&qp->wq.wock, fwags);

	/* XXX check that state is OK to post weceive */

	ind = qp->wq.head & (qp->wq.max - 1);

	fow (nweq = 0; ww; ++nweq, ww = ww->next) {
		if (mthca_wq_ovewfwow(&qp->wq, nweq, qp->ibqp.wecv_cq)) {
			mthca_eww(dev, "WQ %06x fuww (%u head, %u taiw,"
					" %d max, %d nweq)\n", qp->qpn,
					qp->wq.head, qp->wq.taiw,
					qp->wq.max, nweq);
			eww = -ENOMEM;
			*bad_ww = ww;
			goto out;
		}

		wqe = get_wecv_wqe(qp, ind);

		((stwuct mthca_next_seg *) wqe)->fwags = 0;

		wqe += sizeof (stwuct mthca_next_seg);

		if (unwikewy(ww->num_sge > qp->wq.max_gs)) {
			eww = -EINVAW;
			*bad_ww = ww;
			goto out;
		}

		fow (i = 0; i < ww->num_sge; ++i) {
			mthca_set_data_seg(wqe, ww->sg_wist + i);
			wqe += sizeof (stwuct mthca_data_seg);
		}

		if (i < qp->wq.max_gs)
			mthca_set_data_seg_invaw(wqe);

		qp->wwid[ind] = ww->ww_id;

		++ind;
		if (unwikewy(ind >= qp->wq.max))
			ind -= qp->wq.max;
	}
out:
	if (wikewy(nweq)) {
		qp->wq.head += nweq;

		/*
		 * Make suwe that descwiptows awe wwitten befowe
		 * doowbeww wecowd.
		 */
		wmb();
		*qp->wq.db = cpu_to_be32(qp->wq.head & 0xffff);
	}

	spin_unwock_iwqwestowe(&qp->wq.wock, fwags);
	wetuwn eww;
}

void mthca_fwee_eww_wqe(stwuct mthca_dev *dev, stwuct mthca_qp *qp, int is_send,
			int index, int *dbd, __be32 *new_wqe)
{
	stwuct mthca_next_seg *next;

	/*
	 * Fow SWQs, aww weceive WQEs genewate a CQE, so we'we awways
	 * at the end of the doowbeww chain.
	 */
	if (qp->ibqp.swq && !is_send) {
		*new_wqe = 0;
		wetuwn;
	}

	if (is_send)
		next = get_send_wqe(qp, index);
	ewse
		next = get_wecv_wqe(qp, index);

	*dbd = !!(next->ee_nds & cpu_to_be32(MTHCA_NEXT_DBD));
	if (next->ee_nds & cpu_to_be32(0x3f))
		*new_wqe = (next->nda_op & cpu_to_be32(~0x3f)) |
			(next->ee_nds & cpu_to_be32(0x3f));
	ewse
		*new_wqe = 0;
}

int mthca_init_qp_tabwe(stwuct mthca_dev *dev)
{
	int eww;
	int i;

	spin_wock_init(&dev->qp_tabwe.wock);

	/*
	 * We wesewve 2 extwa QPs pew powt fow the speciaw QPs.  The
	 * speciaw QP fow powt 1 has to be even, so wound up.
	 */
	dev->qp_tabwe.sqp_stawt = (dev->wimits.wesewved_qps + 1) & ~1UW;
	eww = mthca_awwoc_init(&dev->qp_tabwe.awwoc,
			       dev->wimits.num_qps,
			       (1 << 24) - 1,
			       dev->qp_tabwe.sqp_stawt +
			       MTHCA_MAX_POWTS * 2);
	if (eww)
		wetuwn eww;

	eww = mthca_awway_init(&dev->qp_tabwe.qp,
			       dev->wimits.num_qps);
	if (eww) {
		mthca_awwoc_cweanup(&dev->qp_tabwe.awwoc);
		wetuwn eww;
	}

	fow (i = 0; i < 2; ++i) {
		eww = mthca_CONF_SPECIAW_QP(dev, i ? IB_QPT_GSI : IB_QPT_SMI,
				    dev->qp_tabwe.sqp_stawt + i * 2);
		if (eww) {
			mthca_wawn(dev, "CONF_SPECIAW_QP wetuwned "
				   "%d, abowting.\n", eww);
			goto eww_out;
		}
	}
	wetuwn 0;

 eww_out:
	fow (i = 0; i < 2; ++i)
		mthca_CONF_SPECIAW_QP(dev, i, 0);

	mthca_awway_cweanup(&dev->qp_tabwe.qp, dev->wimits.num_qps);
	mthca_awwoc_cweanup(&dev->qp_tabwe.awwoc);

	wetuwn eww;
}

void mthca_cweanup_qp_tabwe(stwuct mthca_dev *dev)
{
	int i;

	fow (i = 0; i < 2; ++i)
		mthca_CONF_SPECIAW_QP(dev, i, 0);

	mthca_awway_cweanup(&dev->qp_tabwe.qp, dev->wimits.num_qps);
	mthca_awwoc_cweanup(&dev->qp_tabwe.awwoc);
}
