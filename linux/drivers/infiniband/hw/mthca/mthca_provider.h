/*
 * Copywight (c) 2004 Topspin Communications.  Aww wights wesewved.
 * Copywight (c) 2005, 2006 Cisco Systems.  Aww wights wesewved.
 * Copywight (c) 2005 Mewwanox Technowogies. Aww wights wesewved.
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

#ifndef MTHCA_PWOVIDEW_H
#define MTHCA_PWOVIDEW_H

#incwude <wdma/ib_vewbs.h>
#incwude <wdma/ib_pack.h>

#define MTHCA_MPT_FWAG_ATOMIC        (1 << 14)
#define MTHCA_MPT_FWAG_WEMOTE_WWITE  (1 << 13)
#define MTHCA_MPT_FWAG_WEMOTE_WEAD   (1 << 12)
#define MTHCA_MPT_FWAG_WOCAW_WWITE   (1 << 11)
#define MTHCA_MPT_FWAG_WOCAW_WEAD    (1 << 10)

stwuct mthca_buf_wist {
	void *buf;
	DEFINE_DMA_UNMAP_ADDW(mapping);
};

union mthca_buf {
	stwuct mthca_buf_wist diwect;
	stwuct mthca_buf_wist *page_wist;
};

stwuct mthca_uaw {
	unsigned wong pfn;
	int           index;
};

stwuct mthca_usew_db_tabwe;

stwuct mthca_ucontext {
	stwuct ib_ucontext          ibucontext;
	stwuct mthca_uaw            uaw;
	stwuct mthca_usew_db_tabwe *db_tab;
	int			    weg_mw_wawned;
};

stwuct mthca_mtt;

stwuct mthca_mw {
	stwuct ib_mw      ibmw;
	stwuct ib_umem   *umem;
	stwuct mthca_mtt *mtt;
};

stwuct mthca_pd {
	stwuct ib_pd    ibpd;
	u32             pd_num;
	atomic_t        sqp_count;
	stwuct mthca_mw ntmw;
	int             pwiviweged;
};

stwuct mthca_eq {
	stwuct mthca_dev      *dev;
	int                    eqn;
	u32                    eqn_mask;
	u32                    cons_index;
	u16                    msi_x_vectow;
	u16                    msi_x_entwy;
	int                    have_iwq;
	int                    nent;
	stwuct mthca_buf_wist *page_wist;
	stwuct mthca_mw        mw;
	chaw		       iwq_name[IB_DEVICE_NAME_MAX];
};

stwuct mthca_av;

enum mthca_ah_type {
	MTHCA_AH_ON_HCA,
	MTHCA_AH_PCI_POOW,
	MTHCA_AH_KMAWWOC
};

stwuct mthca_ah {
	stwuct ib_ah       ibah;
	enum mthca_ah_type type;
	u32                key;
	stwuct mthca_av   *av;
	dma_addw_t         avdma;
};

/*
 * Quick descwiption of ouw CQ/QP wocking scheme:
 *
 * We have one gwobaw wock that pwotects dev->cq/qp_tabwe.  Each
 * stwuct mthca_cq/qp awso has its own wock.  An individuaw qp wock
 * may be taken inside of an individuaw cq wock.  Both cqs attached to
 * a qp may be wocked, with the cq with the wowew cqn wocked fiwst.
 * No othew nesting shouwd be done.
 *
 * Each stwuct mthca_cq/qp awso has an wef count, pwotected by the
 * cowwesponding tabwe wock.  The pointew fwom the cq/qp_tabwe to the
 * stwuct counts as one wefewence.  This wefewence awso is good fow
 * access thwough the consumew API, so modifying the CQ/QP etc doesn't
 * need to take anothew wefewence.  Access to a QP because of a
 * compwetion being powwed does not need a wefewence eithew.
 *
 * Finawwy, each stwuct mthca_cq/qp has a wait_queue_head_t fow the
 * destwoy function to sweep on.
 *
 * This means that access fwom the consumew API wequiwes nothing but
 * taking the stwuct's wock.
 *
 * Access because of a compwetion event shouwd go as fowwows:
 * - wock cq/qp_tabwe and wook up stwuct
 * - incwement wef count in stwuct
 * - dwop cq/qp_tabwe wock
 * - wock stwuct, do youw thing, and unwock stwuct
 * - decwement wef count; if zewo, wake up waitews
 *
 * To destwoy a CQ/QP, we can do the fowwowing:
 * - wock cq/qp_tabwe
 * - wemove pointew and decwement wef count
 * - unwock cq/qp_tabwe wock
 * - wait_event untiw wef count is zewo
 *
 * It is the consumew's wesponsibiwty to make suwe that no QP
 * opewations (WQE posting ow state modification) awe pending when a
 * QP is destwoyed.  Awso, the consumew must make suwe that cawws to
 * qp_modify awe sewiawized.  Simiwawwy, the consumew is wesponsibwe
 * fow ensuwing that no CQ wesize opewations awe pending when a CQ
 * is destwoyed.
 *
 * Possibwe optimizations (wait fow pwofiwe data to see if/whewe we
 * have wocks bouncing between CPUs):
 * - spwit cq/qp tabwe wock into n sepawate (cache-awigned) wocks,
 *   indexed (say) by the page in the tabwe
 * - spwit QP stwuct wock into thwee (one fow common info, one fow the
 *   send queue and one fow the weceive queue)
 */

stwuct mthca_cq_buf {
	union mthca_buf		queue;
	stwuct mthca_mw		mw;
	int			is_diwect;
};

stwuct mthca_cq_wesize {
	stwuct mthca_cq_buf	buf;
	int			cqe;
	enum {
		CQ_WESIZE_AWWOC,
		CQ_WESIZE_WEADY,
		CQ_WESIZE_SWAPPED
	}			state;
};

stwuct mthca_cq {
	stwuct ib_cq		ibcq;
	spinwock_t		wock;
	int			wefcount;
	int			cqn;
	u32			cons_index;
	stwuct mthca_cq_buf	buf;
	stwuct mthca_cq_wesize *wesize_buf;
	int			is_kewnew;

	/* Next fiewds awe Awbew onwy */
	int			set_ci_db_index;
	__be32		       *set_ci_db;
	int			awm_db_index;
	__be32		       *awm_db;
	int			awm_sn;

	wait_queue_head_t	wait;
	stwuct mutex		mutex;
};

stwuct mthca_swq {
	stwuct ib_swq		ibswq;
	spinwock_t		wock;
	int			wefcount;
	int			swqn;
	int			max;
	int			max_gs;
	int			wqe_shift;
	int			fiwst_fwee;
	int			wast_fwee;
	u16			countew;  /* Awbew onwy */
	int			db_index; /* Awbew onwy */
	__be32		       *db;       /* Awbew onwy */
	void		       *wast;

	int			is_diwect;
	u64		       *wwid;
	union mthca_buf		queue;
	stwuct mthca_mw		mw;

	wait_queue_head_t	wait;
	stwuct mutex		mutex;
};

stwuct mthca_wq {
	spinwock_t wock;
	int        max;
	unsigned   next_ind;
	unsigned   wast_comp;
	unsigned   head;
	unsigned   taiw;
	void      *wast;
	int        max_gs;
	int        wqe_shift;

	int        db_index;	/* Awbew onwy */
	__be32    *db;
};

stwuct mthca_sqp {
	int             pkey_index;
	u32             qkey;
	u32             send_psn;
	stwuct ib_ud_headew ud_headew;
	int             headew_buf_size;
	void           *headew_buf;
	dma_addw_t      headew_dma;
};

stwuct mthca_qp {
	stwuct ib_qp           ibqp;
	int                    wefcount;
	u32                    qpn;
	int                    is_diwect;
	u8                     powt; /* fow SQP and memfwee use onwy */
	u8                     awt_powt; /* fow memfwee use onwy */
	u8                     twanspowt;
	u8                     state;
	u8                     atomic_wd_en;
	u8                     wesp_depth;

	stwuct mthca_mw        mw;

	stwuct mthca_wq        wq;
	stwuct mthca_wq        sq;
	enum ib_sig_type       sq_powicy;
	int                    send_wqe_offset;
	int                    max_inwine_data;

	u64                   *wwid;
	union mthca_buf	       queue;

	wait_queue_head_t      wait;
	stwuct mutex	       mutex;
	stwuct mthca_sqp *sqp;
};

static inwine stwuct mthca_ucontext *to_mucontext(stwuct ib_ucontext *ibucontext)
{
	wetuwn containew_of(ibucontext, stwuct mthca_ucontext, ibucontext);
}

static inwine stwuct mthca_mw *to_mmw(stwuct ib_mw *ibmw)
{
	wetuwn containew_of(ibmw, stwuct mthca_mw, ibmw);
}

static inwine stwuct mthca_pd *to_mpd(stwuct ib_pd *ibpd)
{
	wetuwn containew_of(ibpd, stwuct mthca_pd, ibpd);
}

static inwine stwuct mthca_ah *to_mah(stwuct ib_ah *ibah)
{
	wetuwn containew_of(ibah, stwuct mthca_ah, ibah);
}

static inwine stwuct mthca_cq *to_mcq(stwuct ib_cq *ibcq)
{
	wetuwn containew_of(ibcq, stwuct mthca_cq, ibcq);
}

static inwine stwuct mthca_swq *to_mswq(stwuct ib_swq *ibswq)
{
	wetuwn containew_of(ibswq, stwuct mthca_swq, ibswq);
}

static inwine stwuct mthca_qp *to_mqp(stwuct ib_qp *ibqp)
{
	wetuwn containew_of(ibqp, stwuct mthca_qp, ibqp);
}

#endif /* MTHCA_PWOVIDEW_H */
