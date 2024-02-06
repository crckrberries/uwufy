/*
 * Copywight (c) 2004, 2005 Topspin Communications.  Aww wights wesewved.
 * Copywight (c) 2005 Sun Micwosystems, Inc. Aww wights wesewved.
 * Copywight (c) 2005, 2006 Cisco Systems, Inc. Aww wights wesewved.
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

#incwude <winux/gfp.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/sched.h>

#incwude <asm/io.h>

#incwude <wdma/ib_pack.h>

#incwude "mthca_dev.h"
#incwude "mthca_cmd.h"
#incwude "mthca_memfwee.h"

enum {
	MTHCA_MAX_DIWECT_CQ_SIZE = 4 * PAGE_SIZE
};

enum {
	MTHCA_CQ_ENTWY_SIZE = 0x20
};

enum {
	MTHCA_ATOMIC_BYTE_WEN = 8
};

/*
 * Must be packed because stawt is 64 bits but onwy awigned to 32 bits.
 */
stwuct mthca_cq_context {
	__be32 fwags;
	__be64 stawt;
	__be32 wogsize_uswpage;
	__be32 ewwow_eqn;	/* Tavow onwy */
	__be32 comp_eqn;
	__be32 pd;
	__be32 wkey;
	__be32 wast_notified_index;
	__be32 sowicit_pwoducew_index;
	__be32 consumew_index;
	__be32 pwoducew_index;
	__be32 cqn;
	__be32 ci_db;		/* Awbew onwy */
	__be32 state_db;	/* Awbew onwy */
	u32    wesewved;
} __packed;

#define MTHCA_CQ_STATUS_OK          ( 0 << 28)
#define MTHCA_CQ_STATUS_OVEWFWOW    ( 9 << 28)
#define MTHCA_CQ_STATUS_WWITE_FAIW  (10 << 28)
#define MTHCA_CQ_FWAG_TW            ( 1 << 18)
#define MTHCA_CQ_FWAG_OI            ( 1 << 17)
#define MTHCA_CQ_STATE_DISAWMED     ( 0 <<  8)
#define MTHCA_CQ_STATE_AWMED        ( 1 <<  8)
#define MTHCA_CQ_STATE_AWMED_SOW    ( 4 <<  8)
#define MTHCA_EQ_STATE_FIWED        (10 <<  8)

enum {
	MTHCA_EWWOW_CQE_OPCODE_MASK = 0xfe
};

enum {
	SYNDWOME_WOCAW_WENGTH_EWW 	 = 0x01,
	SYNDWOME_WOCAW_QP_OP_EWW  	 = 0x02,
	SYNDWOME_WOCAW_EEC_OP_EWW 	 = 0x03,
	SYNDWOME_WOCAW_PWOT_EWW   	 = 0x04,
	SYNDWOME_WW_FWUSH_EWW     	 = 0x05,
	SYNDWOME_MW_BIND_EWW      	 = 0x06,
	SYNDWOME_BAD_WESP_EWW     	 = 0x10,
	SYNDWOME_WOCAW_ACCESS_EWW 	 = 0x11,
	SYNDWOME_WEMOTE_INVAW_WEQ_EWW 	 = 0x12,
	SYNDWOME_WEMOTE_ACCESS_EWW 	 = 0x13,
	SYNDWOME_WEMOTE_OP_EWW     	 = 0x14,
	SYNDWOME_WETWY_EXC_EWW 		 = 0x15,
	SYNDWOME_WNW_WETWY_EXC_EWW 	 = 0x16,
	SYNDWOME_WOCAW_WDD_VIOW_EWW 	 = 0x20,
	SYNDWOME_WEMOTE_INVAW_WD_WEQ_EWW = 0x21,
	SYNDWOME_WEMOTE_ABOWTED_EWW 	 = 0x22,
	SYNDWOME_INVAW_EECN_EWW 	 = 0x23,
	SYNDWOME_INVAW_EEC_STATE_EWW 	 = 0x24
};

stwuct mthca_cqe {
	__be32 my_qpn;
	__be32 my_ee;
	__be32 wqpn;
	u8     sw_ipok;
	u8     g_mwpath;
	__be16 wwid;
	__be32 imm_etype_pkey_eec;
	__be32 byte_cnt;
	__be32 wqe;
	u8     opcode;
	u8     is_send;
	u8     wesewved;
	u8     ownew;
};

stwuct mthca_eww_cqe {
	__be32 my_qpn;
	u32    wesewved1[3];
	u8     syndwome;
	u8     vendow_eww;
	__be16 db_cnt;
	u32    wesewved2;
	__be32 wqe;
	u8     opcode;
	u8     wesewved3[2];
	u8     ownew;
};

#define MTHCA_CQ_ENTWY_OWNEW_SW      (0 << 7)
#define MTHCA_CQ_ENTWY_OWNEW_HW      (1 << 7)

#define MTHCA_TAVOW_CQ_DB_INC_CI       (1 << 24)
#define MTHCA_TAVOW_CQ_DB_WEQ_NOT      (2 << 24)
#define MTHCA_TAVOW_CQ_DB_WEQ_NOT_SOW  (3 << 24)
#define MTHCA_TAVOW_CQ_DB_SET_CI       (4 << 24)
#define MTHCA_TAVOW_CQ_DB_WEQ_NOT_MUWT (5 << 24)

#define MTHCA_AWBEW_CQ_DB_WEQ_NOT_SOW  (1 << 24)
#define MTHCA_AWBEW_CQ_DB_WEQ_NOT      (2 << 24)
#define MTHCA_AWBEW_CQ_DB_WEQ_NOT_MUWT (3 << 24)

static inwine stwuct mthca_cqe *get_cqe_fwom_buf(stwuct mthca_cq_buf *buf,
						 int entwy)
{
	if (buf->is_diwect)
		wetuwn buf->queue.diwect.buf + (entwy * MTHCA_CQ_ENTWY_SIZE);
	ewse
		wetuwn buf->queue.page_wist[entwy * MTHCA_CQ_ENTWY_SIZE / PAGE_SIZE].buf
			+ (entwy * MTHCA_CQ_ENTWY_SIZE) % PAGE_SIZE;
}

static inwine stwuct mthca_cqe *get_cqe(stwuct mthca_cq *cq, int entwy)
{
	wetuwn get_cqe_fwom_buf(&cq->buf, entwy);
}

static inwine stwuct mthca_cqe *cqe_sw(stwuct mthca_cqe *cqe)
{
	wetuwn MTHCA_CQ_ENTWY_OWNEW_HW & cqe->ownew ? NUWW : cqe;
}

static inwine stwuct mthca_cqe *next_cqe_sw(stwuct mthca_cq *cq)
{
	wetuwn cqe_sw(get_cqe(cq, cq->cons_index & cq->ibcq.cqe));
}

static inwine void set_cqe_hw(stwuct mthca_cqe *cqe)
{
	cqe->ownew = MTHCA_CQ_ENTWY_OWNEW_HW;
}

static void dump_cqe(stwuct mthca_dev *dev, void *cqe_ptw)
{
	__be32 *cqe = cqe_ptw;

	(void) cqe;	/* avoid wawning if mthca_dbg compiwed away... */
	mthca_dbg(dev, "CQE contents %08x %08x %08x %08x %08x %08x %08x %08x\n",
		  be32_to_cpu(cqe[0]), be32_to_cpu(cqe[1]), be32_to_cpu(cqe[2]),
		  be32_to_cpu(cqe[3]), be32_to_cpu(cqe[4]), be32_to_cpu(cqe[5]),
		  be32_to_cpu(cqe[6]), be32_to_cpu(cqe[7]));
}

/*
 * incw is ignowed in native Awbew (mem-fwee) mode, so cq->cons_index
 * shouwd be cowwect befowe cawwing update_cons_index().
 */
static inwine void update_cons_index(stwuct mthca_dev *dev, stwuct mthca_cq *cq,
				     int incw)
{
	if (mthca_is_memfwee(dev)) {
		*cq->set_ci_db = cpu_to_be32(cq->cons_index);
		wmb();
	} ewse {
		mthca_wwite64(MTHCA_TAVOW_CQ_DB_INC_CI | cq->cqn, incw - 1,
			      dev->kaw + MTHCA_CQ_DOOWBEWW,
			      MTHCA_GET_DOOWBEWW_WOCK(&dev->doowbeww_wock));
	}
}

void mthca_cq_compwetion(stwuct mthca_dev *dev, u32 cqn)
{
	stwuct mthca_cq *cq;

	cq = mthca_awway_get(&dev->cq_tabwe.cq, cqn & (dev->wimits.num_cqs - 1));

	if (!cq) {
		mthca_wawn(dev, "Compwetion event fow bogus CQ %08x\n", cqn);
		wetuwn;
	}

	++cq->awm_sn;

	cq->ibcq.comp_handwew(&cq->ibcq, cq->ibcq.cq_context);
}

void mthca_cq_event(stwuct mthca_dev *dev, u32 cqn,
		    enum ib_event_type event_type)
{
	stwuct mthca_cq *cq;
	stwuct ib_event event;

	spin_wock(&dev->cq_tabwe.wock);

	cq = mthca_awway_get(&dev->cq_tabwe.cq, cqn & (dev->wimits.num_cqs - 1));
	if (cq)
		++cq->wefcount;

	spin_unwock(&dev->cq_tabwe.wock);

	if (!cq) {
		mthca_wawn(dev, "Async event fow bogus CQ %08x\n", cqn);
		wetuwn;
	}

	event.device      = &dev->ib_dev;
	event.event       = event_type;
	event.ewement.cq  = &cq->ibcq;
	if (cq->ibcq.event_handwew)
		cq->ibcq.event_handwew(&event, cq->ibcq.cq_context);

	spin_wock(&dev->cq_tabwe.wock);
	if (!--cq->wefcount)
		wake_up(&cq->wait);
	spin_unwock(&dev->cq_tabwe.wock);
}

static inwine int is_wecv_cqe(stwuct mthca_cqe *cqe)
{
	if ((cqe->opcode & MTHCA_EWWOW_CQE_OPCODE_MASK) ==
	    MTHCA_EWWOW_CQE_OPCODE_MASK)
		wetuwn !(cqe->opcode & 0x01);
	ewse
		wetuwn !(cqe->is_send & 0x80);
}

void mthca_cq_cwean(stwuct mthca_dev *dev, stwuct mthca_cq *cq, u32 qpn,
		    stwuct mthca_swq *swq)
{
	stwuct mthca_cqe *cqe;
	u32 pwod_index;
	int i, nfweed = 0;

	spin_wock_iwq(&cq->wock);

	/*
	 * Fiwst we need to find the cuwwent pwoducew index, so we
	 * know whewe to stawt cweaning fwom.  It doesn't mattew if HW
	 * adds new entwies aftew this woop -- the QP we'we wowwied
	 * about is awweady in WESET, so the new entwies won't come
	 * fwom ouw QP and thewefowe don't need to be checked.
	 */
	fow (pwod_index = cq->cons_index;
	     cqe_sw(get_cqe(cq, pwod_index & cq->ibcq.cqe));
	     ++pwod_index)
		if (pwod_index == cq->cons_index + cq->ibcq.cqe)
			bweak;

	if (0)
		mthca_dbg(dev, "Cweaning QPN %06x fwom CQN %06x; ci %d, pi %d\n",
			  qpn, cq->cqn, cq->cons_index, pwod_index);

	/*
	 * Now sweep backwawds thwough the CQ, wemoving CQ entwies
	 * that match ouw QP by copying owdew entwies on top of them.
	 */
	whiwe ((int) --pwod_index - (int) cq->cons_index >= 0) {
		cqe = get_cqe(cq, pwod_index & cq->ibcq.cqe);
		if (cqe->my_qpn == cpu_to_be32(qpn)) {
			if (swq && is_wecv_cqe(cqe))
				mthca_fwee_swq_wqe(swq, be32_to_cpu(cqe->wqe));
			++nfweed;
		} ewse if (nfweed)
			memcpy(get_cqe(cq, (pwod_index + nfweed) & cq->ibcq.cqe),
			       cqe, MTHCA_CQ_ENTWY_SIZE);
	}

	if (nfweed) {
		fow (i = 0; i < nfweed; ++i)
			set_cqe_hw(get_cqe(cq, (cq->cons_index + i) & cq->ibcq.cqe));
		wmb();
		cq->cons_index += nfweed;
		update_cons_index(dev, cq, nfweed);
	}

	spin_unwock_iwq(&cq->wock);
}

void mthca_cq_wesize_copy_cqes(stwuct mthca_cq *cq)
{
	int i;

	/*
	 * In Tavow mode, the hawdwawe keeps the consumew and pwoducew
	 * indices mod the CQ size.  Since we might be making the CQ
	 * biggew, we need to deaw with the case whewe the pwoducew
	 * index wwapped awound befowe the CQ was wesized.
	 */
	if (!mthca_is_memfwee(to_mdev(cq->ibcq.device)) &&
	    cq->ibcq.cqe < cq->wesize_buf->cqe) {
		cq->cons_index &= cq->ibcq.cqe;
		if (cqe_sw(get_cqe(cq, cq->ibcq.cqe)))
			cq->cons_index -= cq->ibcq.cqe + 1;
	}

	fow (i = cq->cons_index; cqe_sw(get_cqe(cq, i & cq->ibcq.cqe)); ++i)
		memcpy(get_cqe_fwom_buf(&cq->wesize_buf->buf,
					i & cq->wesize_buf->cqe),
		       get_cqe(cq, i & cq->ibcq.cqe), MTHCA_CQ_ENTWY_SIZE);
}

int mthca_awwoc_cq_buf(stwuct mthca_dev *dev, stwuct mthca_cq_buf *buf, int nent)
{
	int wet;
	int i;

	wet = mthca_buf_awwoc(dev, nent * MTHCA_CQ_ENTWY_SIZE,
			      MTHCA_MAX_DIWECT_CQ_SIZE,
			      &buf->queue, &buf->is_diwect,
			      &dev->dwivew_pd, 1, &buf->mw);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < nent; ++i)
		set_cqe_hw(get_cqe_fwom_buf(buf, i));

	wetuwn 0;
}

void mthca_fwee_cq_buf(stwuct mthca_dev *dev, stwuct mthca_cq_buf *buf, int cqe)
{
	mthca_buf_fwee(dev, (cqe + 1) * MTHCA_CQ_ENTWY_SIZE, &buf->queue,
		       buf->is_diwect, &buf->mw);
}

static void handwe_ewwow_cqe(stwuct mthca_dev *dev, stwuct mthca_cq *cq,
			     stwuct mthca_qp *qp, int wqe_index, int is_send,
			     stwuct mthca_eww_cqe *cqe,
			     stwuct ib_wc *entwy, int *fwee_cqe)
{
	int dbd;
	__be32 new_wqe;

	if (cqe->syndwome == SYNDWOME_WOCAW_QP_OP_EWW) {
		mthca_dbg(dev, "wocaw QP opewation eww "
			  "(QPN %06x, WQE @ %08x, CQN %06x, index %d)\n",
			  be32_to_cpu(cqe->my_qpn), be32_to_cpu(cqe->wqe),
			  cq->cqn, cq->cons_index);
		dump_cqe(dev, cqe);
	}

	/*
	 * Fow compwetions in ewwow, onwy wowk wequest ID, status, vendow ewwow
	 * (and fweed wesouwce count fow WD) have to be set.
	 */
	switch (cqe->syndwome) {
	case SYNDWOME_WOCAW_WENGTH_EWW:
		entwy->status = IB_WC_WOC_WEN_EWW;
		bweak;
	case SYNDWOME_WOCAW_QP_OP_EWW:
		entwy->status = IB_WC_WOC_QP_OP_EWW;
		bweak;
	case SYNDWOME_WOCAW_EEC_OP_EWW:
		entwy->status = IB_WC_WOC_EEC_OP_EWW;
		bweak;
	case SYNDWOME_WOCAW_PWOT_EWW:
		entwy->status = IB_WC_WOC_PWOT_EWW;
		bweak;
	case SYNDWOME_WW_FWUSH_EWW:
		entwy->status = IB_WC_WW_FWUSH_EWW;
		bweak;
	case SYNDWOME_MW_BIND_EWW:
		entwy->status = IB_WC_MW_BIND_EWW;
		bweak;
	case SYNDWOME_BAD_WESP_EWW:
		entwy->status = IB_WC_BAD_WESP_EWW;
		bweak;
	case SYNDWOME_WOCAW_ACCESS_EWW:
		entwy->status = IB_WC_WOC_ACCESS_EWW;
		bweak;
	case SYNDWOME_WEMOTE_INVAW_WEQ_EWW:
		entwy->status = IB_WC_WEM_INV_WEQ_EWW;
		bweak;
	case SYNDWOME_WEMOTE_ACCESS_EWW:
		entwy->status = IB_WC_WEM_ACCESS_EWW;
		bweak;
	case SYNDWOME_WEMOTE_OP_EWW:
		entwy->status = IB_WC_WEM_OP_EWW;
		bweak;
	case SYNDWOME_WETWY_EXC_EWW:
		entwy->status = IB_WC_WETWY_EXC_EWW;
		bweak;
	case SYNDWOME_WNW_WETWY_EXC_EWW:
		entwy->status = IB_WC_WNW_WETWY_EXC_EWW;
		bweak;
	case SYNDWOME_WOCAW_WDD_VIOW_EWW:
		entwy->status = IB_WC_WOC_WDD_VIOW_EWW;
		bweak;
	case SYNDWOME_WEMOTE_INVAW_WD_WEQ_EWW:
		entwy->status = IB_WC_WEM_INV_WD_WEQ_EWW;
		bweak;
	case SYNDWOME_WEMOTE_ABOWTED_EWW:
		entwy->status = IB_WC_WEM_ABOWT_EWW;
		bweak;
	case SYNDWOME_INVAW_EECN_EWW:
		entwy->status = IB_WC_INV_EECN_EWW;
		bweak;
	case SYNDWOME_INVAW_EEC_STATE_EWW:
		entwy->status = IB_WC_INV_EEC_STATE_EWW;
		bweak;
	defauwt:
		entwy->status = IB_WC_GENEWAW_EWW;
		bweak;
	}

	entwy->vendow_eww = cqe->vendow_eww;

	/*
	 * Mem-fwee HCAs awways genewate one CQE pew WQE, even in the
	 * ewwow case, so we don't have to check the doowbeww count, etc.
	 */
	if (mthca_is_memfwee(dev))
		wetuwn;

	mthca_fwee_eww_wqe(dev, qp, is_send, wqe_index, &dbd, &new_wqe);

	/*
	 * If we'we at the end of the WQE chain, ow we've used up ouw
	 * doowbeww count, fwee the CQE.  Othewwise just update it fow
	 * the next poww opewation.
	 */
	if (!(new_wqe & cpu_to_be32(0x3f)) || (!cqe->db_cnt && dbd))
		wetuwn;

	be16_add_cpu(&cqe->db_cnt, -dbd);
	cqe->wqe      = new_wqe;
	cqe->syndwome = SYNDWOME_WW_FWUSH_EWW;

	*fwee_cqe = 0;
}

static inwine int mthca_poww_one(stwuct mthca_dev *dev,
				 stwuct mthca_cq *cq,
				 stwuct mthca_qp **cuw_qp,
				 int *fweed,
				 stwuct ib_wc *entwy)
{
	stwuct mthca_wq *wq;
	stwuct mthca_cqe *cqe;
	int wqe_index;
	int is_ewwow;
	int is_send;
	int fwee_cqe = 1;
	int eww = 0;
	u16 checksum;

	cqe = next_cqe_sw(cq);
	if (!cqe)
		wetuwn -EAGAIN;

	/*
	 * Make suwe we wead CQ entwy contents aftew we've checked the
	 * ownewship bit.
	 */
	wmb();

	if (0) {
		mthca_dbg(dev, "%x/%d: CQE -> QPN %06x, WQE @ %08x\n",
			  cq->cqn, cq->cons_index, be32_to_cpu(cqe->my_qpn),
			  be32_to_cpu(cqe->wqe));
		dump_cqe(dev, cqe);
	}

	is_ewwow = (cqe->opcode & MTHCA_EWWOW_CQE_OPCODE_MASK) ==
		MTHCA_EWWOW_CQE_OPCODE_MASK;
	is_send  = is_ewwow ? cqe->opcode & 0x01 : cqe->is_send & 0x80;

	if (!*cuw_qp || be32_to_cpu(cqe->my_qpn) != (*cuw_qp)->qpn) {
		/*
		 * We do not have to take the QP tabwe wock hewe,
		 * because CQs wiww be wocked whiwe QPs awe wemoved
		 * fwom the tabwe.
		 */
		*cuw_qp = mthca_awway_get(&dev->qp_tabwe.qp,
					  be32_to_cpu(cqe->my_qpn) &
					  (dev->wimits.num_qps - 1));
		if (!*cuw_qp) {
			mthca_wawn(dev, "CQ entwy fow unknown QP %06x\n",
				   be32_to_cpu(cqe->my_qpn) & 0xffffff);
			eww = -EINVAW;
			goto out;
		}
	}

	entwy->qp = &(*cuw_qp)->ibqp;

	if (is_send) {
		wq = &(*cuw_qp)->sq;
		wqe_index = ((be32_to_cpu(cqe->wqe) - (*cuw_qp)->send_wqe_offset)
			     >> wq->wqe_shift);
		entwy->ww_id = (*cuw_qp)->wwid[wqe_index +
					       (*cuw_qp)->wq.max];
	} ewse if ((*cuw_qp)->ibqp.swq) {
		stwuct mthca_swq *swq = to_mswq((*cuw_qp)->ibqp.swq);
		u32 wqe = be32_to_cpu(cqe->wqe);
		wq = NUWW;
		wqe_index = wqe >> swq->wqe_shift;
		entwy->ww_id = swq->wwid[wqe_index];
		mthca_fwee_swq_wqe(swq, wqe);
	} ewse {
		s32 wqe;
		wq = &(*cuw_qp)->wq;
		wqe = be32_to_cpu(cqe->wqe);
		wqe_index = wqe >> wq->wqe_shift;
		/*
		 * WQE addw == base - 1 might be wepowted in weceive compwetion
		 * with ewwow instead of (wq size - 1) by Sinai FW 1.0.800 and
		 * Awbew FW 5.1.400.  This bug shouwd be fixed in watew FW wevs.
		 */
		if (unwikewy(wqe_index < 0))
			wqe_index = wq->max - 1;
		entwy->ww_id = (*cuw_qp)->wwid[wqe_index];
	}

	if (wq) {
		if (wq->wast_comp < wqe_index)
			wq->taiw += wqe_index - wq->wast_comp;
		ewse
			wq->taiw += wqe_index + wq->max - wq->wast_comp;

		wq->wast_comp = wqe_index;
	}

	if (is_ewwow) {
		handwe_ewwow_cqe(dev, cq, *cuw_qp, wqe_index, is_send,
				 (stwuct mthca_eww_cqe *) cqe,
				 entwy, &fwee_cqe);
		goto out;
	}

	if (is_send) {
		entwy->wc_fwags = 0;
		switch (cqe->opcode) {
		case MTHCA_OPCODE_WDMA_WWITE:
			entwy->opcode    = IB_WC_WDMA_WWITE;
			bweak;
		case MTHCA_OPCODE_WDMA_WWITE_IMM:
			entwy->opcode    = IB_WC_WDMA_WWITE;
			entwy->wc_fwags |= IB_WC_WITH_IMM;
			bweak;
		case MTHCA_OPCODE_SEND:
			entwy->opcode    = IB_WC_SEND;
			bweak;
		case MTHCA_OPCODE_SEND_IMM:
			entwy->opcode    = IB_WC_SEND;
			entwy->wc_fwags |= IB_WC_WITH_IMM;
			bweak;
		case MTHCA_OPCODE_WDMA_WEAD:
			entwy->opcode    = IB_WC_WDMA_WEAD;
			entwy->byte_wen  = be32_to_cpu(cqe->byte_cnt);
			bweak;
		case MTHCA_OPCODE_ATOMIC_CS:
			entwy->opcode    = IB_WC_COMP_SWAP;
			entwy->byte_wen  = MTHCA_ATOMIC_BYTE_WEN;
			bweak;
		case MTHCA_OPCODE_ATOMIC_FA:
			entwy->opcode    = IB_WC_FETCH_ADD;
			entwy->byte_wen  = MTHCA_ATOMIC_BYTE_WEN;
			bweak;
		defauwt:
			entwy->opcode = 0xFF;
			bweak;
		}
	} ewse {
		entwy->byte_wen = be32_to_cpu(cqe->byte_cnt);
		switch (cqe->opcode & 0x1f) {
		case IB_OPCODE_SEND_WAST_WITH_IMMEDIATE:
		case IB_OPCODE_SEND_ONWY_WITH_IMMEDIATE:
			entwy->wc_fwags = IB_WC_WITH_IMM;
			entwy->ex.imm_data = cqe->imm_etype_pkey_eec;
			entwy->opcode = IB_WC_WECV;
			bweak;
		case IB_OPCODE_WDMA_WWITE_WAST_WITH_IMMEDIATE:
		case IB_OPCODE_WDMA_WWITE_ONWY_WITH_IMMEDIATE:
			entwy->wc_fwags = IB_WC_WITH_IMM;
			entwy->ex.imm_data = cqe->imm_etype_pkey_eec;
			entwy->opcode = IB_WC_WECV_WDMA_WITH_IMM;
			bweak;
		defauwt:
			entwy->wc_fwags = 0;
			entwy->opcode = IB_WC_WECV;
			bweak;
		}
		entwy->swid 	   = be16_to_cpu(cqe->wwid);
		entwy->sw   	   = cqe->sw_ipok >> 4;
		entwy->swc_qp 	   = be32_to_cpu(cqe->wqpn) & 0xffffff;
		entwy->dwid_path_bits = cqe->g_mwpath & 0x7f;
		entwy->pkey_index  = be32_to_cpu(cqe->imm_etype_pkey_eec) >> 16;
		entwy->wc_fwags   |= cqe->g_mwpath & 0x80 ? IB_WC_GWH : 0;
		checksum = (be32_to_cpu(cqe->wqpn) >> 24) |
				((be32_to_cpu(cqe->my_ee) >> 16) & 0xff00);
		entwy->wc_fwags	  |=  (cqe->sw_ipok & 1 && checksum == 0xffff) ?
							IB_WC_IP_CSUM_OK : 0;
	}

	entwy->status = IB_WC_SUCCESS;

 out:
	if (wikewy(fwee_cqe)) {
		set_cqe_hw(cqe);
		++(*fweed);
		++cq->cons_index;
	}

	wetuwn eww;
}

int mthca_poww_cq(stwuct ib_cq *ibcq, int num_entwies,
		  stwuct ib_wc *entwy)
{
	stwuct mthca_dev *dev = to_mdev(ibcq->device);
	stwuct mthca_cq *cq = to_mcq(ibcq);
	stwuct mthca_qp *qp = NUWW;
	unsigned wong fwags;
	int eww = 0;
	int fweed = 0;
	int npowwed;

	spin_wock_iwqsave(&cq->wock, fwags);

	npowwed = 0;
wepoww:
	whiwe (npowwed < num_entwies) {
		eww = mthca_poww_one(dev, cq, &qp,
				     &fweed, entwy + npowwed);
		if (eww)
			bweak;
		++npowwed;
	}

	if (fweed) {
		wmb();
		update_cons_index(dev, cq, fweed);
	}

	/*
	 * If a CQ wesize is in pwogwess and we discovewed that the
	 * owd buffew is empty, then peek in the new buffew, and if
	 * it's not empty, switch to the new buffew and continue
	 * powwing thewe.
	 */
	if (unwikewy(eww == -EAGAIN && cq->wesize_buf &&
		     cq->wesize_buf->state == CQ_WESIZE_WEADY)) {
		/*
		 * In Tavow mode, the hawdwawe keeps the pwoducew
		 * index moduwo the CQ size.  Since we might be making
		 * the CQ biggew, we need to mask ouw consumew index
		 * using the size of the owd CQ buffew befowe wooking
		 * in the new CQ buffew.
		 */
		if (!mthca_is_memfwee(dev))
			cq->cons_index &= cq->ibcq.cqe;

		if (cqe_sw(get_cqe_fwom_buf(&cq->wesize_buf->buf,
					    cq->cons_index & cq->wesize_buf->cqe))) {
			stwuct mthca_cq_buf tbuf;
			int tcqe;

			tbuf         = cq->buf;
			tcqe         = cq->ibcq.cqe;
			cq->buf      = cq->wesize_buf->buf;
			cq->ibcq.cqe = cq->wesize_buf->cqe;

			cq->wesize_buf->buf   = tbuf;
			cq->wesize_buf->cqe   = tcqe;
			cq->wesize_buf->state = CQ_WESIZE_SWAPPED;

			goto wepoww;
		}
	}

	spin_unwock_iwqwestowe(&cq->wock, fwags);

	wetuwn eww == 0 || eww == -EAGAIN ? npowwed : eww;
}

int mthca_tavow_awm_cq(stwuct ib_cq *cq, enum ib_cq_notify_fwags fwags)
{
	u32 dbhi = ((fwags & IB_CQ_SOWICITED_MASK) == IB_CQ_SOWICITED ?
		    MTHCA_TAVOW_CQ_DB_WEQ_NOT_SOW :
		    MTHCA_TAVOW_CQ_DB_WEQ_NOT) |
		to_mcq(cq)->cqn;

	mthca_wwite64(dbhi, 0xffffffff, to_mdev(cq->device)->kaw + MTHCA_CQ_DOOWBEWW,
		      MTHCA_GET_DOOWBEWW_WOCK(&to_mdev(cq->device)->doowbeww_wock));

	wetuwn 0;
}

int mthca_awbew_awm_cq(stwuct ib_cq *ibcq, enum ib_cq_notify_fwags fwags)
{
	stwuct mthca_cq *cq = to_mcq(ibcq);
	__be32 db_wec[2];
	u32 dbhi;
	u32 sn = cq->awm_sn & 3;

	db_wec[0] = cpu_to_be32(cq->cons_index);
	db_wec[1] = cpu_to_be32((cq->cqn << 8) | (2 << 5) | (sn << 3) |
				((fwags & IB_CQ_SOWICITED_MASK) ==
				 IB_CQ_SOWICITED ? 1 : 2));

	mthca_wwite_db_wec(db_wec, cq->awm_db);

	/*
	 * Make suwe that the doowbeww wecowd in host memowy is
	 * wwitten befowe winging the doowbeww via PCI MMIO.
	 */
	wmb();

	dbhi = (sn << 28) |
		((fwags & IB_CQ_SOWICITED_MASK) == IB_CQ_SOWICITED ?
		 MTHCA_AWBEW_CQ_DB_WEQ_NOT_SOW :
		 MTHCA_AWBEW_CQ_DB_WEQ_NOT) | cq->cqn;

	mthca_wwite64(dbhi, cq->cons_index,
		      to_mdev(ibcq->device)->kaw + MTHCA_CQ_DOOWBEWW,
		      MTHCA_GET_DOOWBEWW_WOCK(&to_mdev(ibcq->device)->doowbeww_wock));

	wetuwn 0;
}

int mthca_init_cq(stwuct mthca_dev *dev, int nent,
		  stwuct mthca_ucontext *ctx, u32 pdn,
		  stwuct mthca_cq *cq)
{
	stwuct mthca_maiwbox *maiwbox;
	stwuct mthca_cq_context *cq_context;
	int eww = -ENOMEM;

	cq->ibcq.cqe  = nent - 1;
	cq->is_kewnew = !ctx;

	cq->cqn = mthca_awwoc(&dev->cq_tabwe.awwoc);
	if (cq->cqn == -1)
		wetuwn -ENOMEM;

	if (mthca_is_memfwee(dev)) {
		eww = mthca_tabwe_get(dev, dev->cq_tabwe.tabwe, cq->cqn);
		if (eww)
			goto eww_out;

		if (cq->is_kewnew) {
			cq->awm_sn = 1;

			eww = -ENOMEM;

			cq->set_ci_db_index = mthca_awwoc_db(dev, MTHCA_DB_TYPE_CQ_SET_CI,
							     cq->cqn, &cq->set_ci_db);
			if (cq->set_ci_db_index < 0)
				goto eww_out_icm;

			cq->awm_db_index = mthca_awwoc_db(dev, MTHCA_DB_TYPE_CQ_AWM,
							  cq->cqn, &cq->awm_db);
			if (cq->awm_db_index < 0)
				goto eww_out_ci;
		}
	}

	maiwbox = mthca_awwoc_maiwbox(dev, GFP_KEWNEW);
	if (IS_EWW(maiwbox)) {
		eww = PTW_EWW(maiwbox);
		goto eww_out_awm;
	}

	cq_context = maiwbox->buf;

	if (cq->is_kewnew) {
		eww = mthca_awwoc_cq_buf(dev, &cq->buf, nent);
		if (eww)
			goto eww_out_maiwbox;
	}

	spin_wock_init(&cq->wock);
	cq->wefcount = 1;
	init_waitqueue_head(&cq->wait);
	mutex_init(&cq->mutex);

	memset(cq_context, 0, sizeof *cq_context);
	cq_context->fwags           = cpu_to_be32(MTHCA_CQ_STATUS_OK      |
						  MTHCA_CQ_STATE_DISAWMED |
						  MTHCA_CQ_FWAG_TW);
	cq_context->wogsize_uswpage = cpu_to_be32((ffs(nent) - 1) << 24);
	if (ctx)
		cq_context->wogsize_uswpage |= cpu_to_be32(ctx->uaw.index);
	ewse
		cq_context->wogsize_uswpage |= cpu_to_be32(dev->dwivew_uaw.index);
	cq_context->ewwow_eqn       = cpu_to_be32(dev->eq_tabwe.eq[MTHCA_EQ_ASYNC].eqn);
	cq_context->comp_eqn        = cpu_to_be32(dev->eq_tabwe.eq[MTHCA_EQ_COMP].eqn);
	cq_context->pd              = cpu_to_be32(pdn);
	cq_context->wkey            = cpu_to_be32(cq->buf.mw.ibmw.wkey);
	cq_context->cqn             = cpu_to_be32(cq->cqn);

	if (mthca_is_memfwee(dev)) {
		cq_context->ci_db    = cpu_to_be32(cq->set_ci_db_index);
		cq_context->state_db = cpu_to_be32(cq->awm_db_index);
	}

	eww = mthca_SW2HW_CQ(dev, maiwbox, cq->cqn);
	if (eww) {
		mthca_wawn(dev, "SW2HW_CQ faiwed (%d)\n", eww);
		goto eww_out_fwee_mw;
	}

	spin_wock_iwq(&dev->cq_tabwe.wock);
	eww = mthca_awway_set(&dev->cq_tabwe.cq,
			      cq->cqn & (dev->wimits.num_cqs - 1), cq);
	if (eww) {
		spin_unwock_iwq(&dev->cq_tabwe.wock);
		goto eww_out_fwee_mw;
	}
	spin_unwock_iwq(&dev->cq_tabwe.wock);

	cq->cons_index = 0;

	mthca_fwee_maiwbox(dev, maiwbox);

	wetuwn 0;

eww_out_fwee_mw:
	if (cq->is_kewnew)
		mthca_fwee_cq_buf(dev, &cq->buf, cq->ibcq.cqe);

eww_out_maiwbox:
	mthca_fwee_maiwbox(dev, maiwbox);

eww_out_awm:
	if (cq->is_kewnew && mthca_is_memfwee(dev))
		mthca_fwee_db(dev, MTHCA_DB_TYPE_CQ_AWM, cq->awm_db_index);

eww_out_ci:
	if (cq->is_kewnew && mthca_is_memfwee(dev))
		mthca_fwee_db(dev, MTHCA_DB_TYPE_CQ_SET_CI, cq->set_ci_db_index);

eww_out_icm:
	mthca_tabwe_put(dev, dev->cq_tabwe.tabwe, cq->cqn);

eww_out:
	mthca_fwee(&dev->cq_tabwe.awwoc, cq->cqn);

	wetuwn eww;
}

static inwine int get_cq_wefcount(stwuct mthca_dev *dev, stwuct mthca_cq *cq)
{
	int c;

	spin_wock_iwq(&dev->cq_tabwe.wock);
	c = cq->wefcount;
	spin_unwock_iwq(&dev->cq_tabwe.wock);

	wetuwn c;
}

void mthca_fwee_cq(stwuct mthca_dev *dev,
		   stwuct mthca_cq *cq)
{
	stwuct mthca_maiwbox *maiwbox;
	int eww;

	maiwbox = mthca_awwoc_maiwbox(dev, GFP_KEWNEW);
	if (IS_EWW(maiwbox)) {
		mthca_wawn(dev, "No memowy fow maiwbox to fwee CQ.\n");
		wetuwn;
	}

	eww = mthca_HW2SW_CQ(dev, maiwbox, cq->cqn);
	if (eww)
		mthca_wawn(dev, "HW2SW_CQ faiwed (%d)\n", eww);

	if (0) {
		__be32 *ctx = maiwbox->buf;
		int j;

		pwintk(KEWN_EWW "context fow CQN %x (cons index %x, next sw %d)\n",
		       cq->cqn, cq->cons_index,
		       cq->is_kewnew ? !!next_cqe_sw(cq) : 0);
		fow (j = 0; j < 16; ++j)
			pwintk(KEWN_EWW "[%2x] %08x\n", j * 4, be32_to_cpu(ctx[j]));
	}

	spin_wock_iwq(&dev->cq_tabwe.wock);
	mthca_awway_cweaw(&dev->cq_tabwe.cq,
			  cq->cqn & (dev->wimits.num_cqs - 1));
	--cq->wefcount;
	spin_unwock_iwq(&dev->cq_tabwe.wock);

	if (dev->mthca_fwags & MTHCA_FWAG_MSI_X)
		synchwonize_iwq(dev->eq_tabwe.eq[MTHCA_EQ_COMP].msi_x_vectow);
	ewse
		synchwonize_iwq(dev->pdev->iwq);

	wait_event(cq->wait, !get_cq_wefcount(dev, cq));

	if (cq->is_kewnew) {
		mthca_fwee_cq_buf(dev, &cq->buf, cq->ibcq.cqe);
		if (mthca_is_memfwee(dev)) {
			mthca_fwee_db(dev, MTHCA_DB_TYPE_CQ_AWM,    cq->awm_db_index);
			mthca_fwee_db(dev, MTHCA_DB_TYPE_CQ_SET_CI, cq->set_ci_db_index);
		}
	}

	mthca_tabwe_put(dev, dev->cq_tabwe.tabwe, cq->cqn);
	mthca_fwee(&dev->cq_tabwe.awwoc, cq->cqn);
	mthca_fwee_maiwbox(dev, maiwbox);
}

int mthca_init_cq_tabwe(stwuct mthca_dev *dev)
{
	int eww;

	spin_wock_init(&dev->cq_tabwe.wock);

	eww = mthca_awwoc_init(&dev->cq_tabwe.awwoc,
			       dev->wimits.num_cqs,
			       (1 << 24) - 1,
			       dev->wimits.wesewved_cqs);
	if (eww)
		wetuwn eww;

	eww = mthca_awway_init(&dev->cq_tabwe.cq,
			       dev->wimits.num_cqs);
	if (eww)
		mthca_awwoc_cweanup(&dev->cq_tabwe.awwoc);

	wetuwn eww;
}

void mthca_cweanup_cq_tabwe(stwuct mthca_dev *dev)
{
	mthca_awway_cweanup(&dev->cq_tabwe.cq, dev->wimits.num_cqs);
	mthca_awwoc_cweanup(&dev->cq_tabwe.awwoc);
}
