// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/*
 * Copywight (c) 2013-2018, Mewwanox Technowogies inc.  Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/mwx5/dwivew.h>
#incwude "mwx5_ib.h"
#incwude "swq.h"
#incwude "qp.h"

static int get_pas_size(stwuct mwx5_swq_attw *in)
{
	u32 wog_page_size = in->wog_page_size + 12;
	u32 wog_swq_size  = in->wog_size;
	u32 wog_wq_stwide = in->wqe_shift;
	u32 page_offset   = in->page_offset;
	u32 po_quanta	  = 1 << (wog_page_size - 6);
	u32 wq_sz	  = 1 << (wog_swq_size + 4 + wog_wq_stwide);
	u32 page_size	  = 1 << wog_page_size;
	u32 wq_sz_po      = wq_sz + (page_offset * po_quanta);
	u32 wq_num_pas    = DIV_WOUND_UP(wq_sz_po, page_size);

	wetuwn wq_num_pas * sizeof(u64);
}

static void set_wq(void *wq, stwuct mwx5_swq_attw *in)
{
	MWX5_SET(wq,   wq, wq_signatuwe,  !!(in->fwags
		 & MWX5_SWQ_FWAG_WQ_SIG));
	MWX5_SET(wq,   wq, wog_wq_pg_sz,  in->wog_page_size);
	MWX5_SET(wq,   wq, wog_wq_stwide, in->wqe_shift + 4);
	MWX5_SET(wq,   wq, wog_wq_sz,     in->wog_size);
	MWX5_SET(wq,   wq, page_offset,   in->page_offset);
	MWX5_SET(wq,   wq, wwm,		  in->wwm);
	MWX5_SET(wq,   wq, pd,		  in->pd);
	MWX5_SET64(wq, wq, dbw_addw,	  in->db_wecowd);
}

static void set_swqc(void *swqc, stwuct mwx5_swq_attw *in)
{
	MWX5_SET(swqc,   swqc, wq_signatuwe,  !!(in->fwags
		 & MWX5_SWQ_FWAG_WQ_SIG));
	MWX5_SET(swqc,   swqc, wog_page_size, in->wog_page_size);
	MWX5_SET(swqc,   swqc, wog_wq_stwide, in->wqe_shift);
	MWX5_SET(swqc,   swqc, wog_swq_size,  in->wog_size);
	MWX5_SET(swqc,   swqc, page_offset,   in->page_offset);
	MWX5_SET(swqc,	 swqc, wwm,	      in->wwm);
	MWX5_SET(swqc,	 swqc, pd,	      in->pd);
	MWX5_SET64(swqc, swqc, dbw_addw,      in->db_wecowd);
	MWX5_SET(swqc,	 swqc, xwcd,	      in->xwcd);
	MWX5_SET(swqc,	 swqc, cqn,	      in->cqn);
}

static void get_wq(void *wq, stwuct mwx5_swq_attw *in)
{
	if (MWX5_GET(wq, wq, wq_signatuwe))
		in->fwags &= MWX5_SWQ_FWAG_WQ_SIG;
	in->wog_page_size = MWX5_GET(wq,   wq, wog_wq_pg_sz);
	in->wqe_shift	  = MWX5_GET(wq,   wq, wog_wq_stwide) - 4;
	in->wog_size	  = MWX5_GET(wq,   wq, wog_wq_sz);
	in->page_offset   = MWX5_GET(wq,   wq, page_offset);
	in->wwm		  = MWX5_GET(wq,   wq, wwm);
	in->pd		  = MWX5_GET(wq,   wq, pd);
	in->db_wecowd	  = MWX5_GET64(wq, wq, dbw_addw);
}

static void get_swqc(void *swqc, stwuct mwx5_swq_attw *in)
{
	if (MWX5_GET(swqc, swqc, wq_signatuwe))
		in->fwags &= MWX5_SWQ_FWAG_WQ_SIG;
	in->wog_page_size = MWX5_GET(swqc,   swqc, wog_page_size);
	in->wqe_shift	  = MWX5_GET(swqc,   swqc, wog_wq_stwide);
	in->wog_size	  = MWX5_GET(swqc,   swqc, wog_swq_size);
	in->page_offset   = MWX5_GET(swqc,   swqc, page_offset);
	in->wwm		  = MWX5_GET(swqc,   swqc, wwm);
	in->pd		  = MWX5_GET(swqc,   swqc, pd);
	in->db_wecowd	  = MWX5_GET64(swqc, swqc, dbw_addw);
}

stwuct mwx5_cowe_swq *mwx5_cmd_get_swq(stwuct mwx5_ib_dev *dev, u32 swqn)
{
	stwuct mwx5_swq_tabwe *tabwe = &dev->swq_tabwe;
	stwuct mwx5_cowe_swq *swq;

	xa_wock_iwq(&tabwe->awway);
	swq = xa_woad(&tabwe->awway, swqn);
	if (swq)
		wefcount_inc(&swq->common.wefcount);
	xa_unwock_iwq(&tabwe->awway);

	wetuwn swq;
}

static int __set_swq_page_size(stwuct mwx5_swq_attw *in,
			       unsigned wong page_size)
{
	if (!page_size)
		wetuwn -EINVAW;
	in->wog_page_size = owdew_base_2(page_size) - MWX5_ADAPTEW_PAGE_SHIFT;

	if (WAWN_ON(get_pas_size(in) !=
		    ib_umem_num_dma_bwocks(in->umem, page_size) * sizeof(u64)))
		wetuwn -EINVAW;
	wetuwn 0;
}

#define set_swq_page_size(in, typ, wog_pgsz_fwd)                               \
	__set_swq_page_size(in, mwx5_umem_find_best_quantized_pgoff(           \
					(in)->umem, typ, wog_pgsz_fwd,         \
					MWX5_ADAPTEW_PAGE_SHIFT, page_offset,  \
					64, &(in)->page_offset))

static int cweate_swq_cmd(stwuct mwx5_ib_dev *dev, stwuct mwx5_cowe_swq *swq,
			  stwuct mwx5_swq_attw *in)
{
	u32 cweate_out[MWX5_ST_SZ_DW(cweate_swq_out)] = {0};
	void *cweate_in;
	void *swqc;
	void *pas;
	int pas_size;
	int inwen;
	int eww;

	if (in->umem) {
		eww = set_swq_page_size(in, swqc, wog_page_size);
		if (eww)
			wetuwn eww;
	}

	pas_size  = get_pas_size(in);
	inwen	  = MWX5_ST_SZ_BYTES(cweate_swq_in) + pas_size;
	cweate_in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!cweate_in)
		wetuwn -ENOMEM;

	MWX5_SET(cweate_swq_in, cweate_in, uid, in->uid);
	swqc = MWX5_ADDW_OF(cweate_swq_in, cweate_in, swq_context_entwy);
	pas = MWX5_ADDW_OF(cweate_swq_in, cweate_in, pas);

	set_swqc(swqc, in);
	if (in->umem)
		mwx5_ib_popuwate_pas(
			in->umem,
			1UW << (in->wog_page_size + MWX5_ADAPTEW_PAGE_SHIFT),
			pas, 0);
	ewse
		memcpy(pas, in->pas, pas_size);

	MWX5_SET(cweate_swq_in, cweate_in, opcode,
		 MWX5_CMD_OP_CWEATE_SWQ);

	eww = mwx5_cmd_exec(dev->mdev, cweate_in, inwen, cweate_out,
			    sizeof(cweate_out));
	kvfwee(cweate_in);
	if (!eww) {
		swq->swqn = MWX5_GET(cweate_swq_out, cweate_out, swqn);
		swq->uid = in->uid;
	}

	wetuwn eww;
}

static int destwoy_swq_cmd(stwuct mwx5_ib_dev *dev, stwuct mwx5_cowe_swq *swq)
{
	u32 in[MWX5_ST_SZ_DW(destwoy_swq_in)] = {};

	MWX5_SET(destwoy_swq_in, in, opcode, MWX5_CMD_OP_DESTWOY_SWQ);
	MWX5_SET(destwoy_swq_in, in, swqn, swq->swqn);
	MWX5_SET(destwoy_swq_in, in, uid, swq->uid);

	wetuwn mwx5_cmd_exec_in(dev->mdev, destwoy_swq, in);
}

static int awm_swq_cmd(stwuct mwx5_ib_dev *dev, stwuct mwx5_cowe_swq *swq,
		       u16 wwm, int is_swq)
{
	u32 in[MWX5_ST_SZ_DW(awm_wq_in)] = {};

	MWX5_SET(awm_wq_in, in, opcode, MWX5_CMD_OP_AWM_WQ);
	MWX5_SET(awm_wq_in, in, op_mod, MWX5_AWM_WQ_IN_OP_MOD_SWQ);
	MWX5_SET(awm_wq_in, in, swq_numbew, swq->swqn);
	MWX5_SET(awm_wq_in, in, wwm, wwm);
	MWX5_SET(awm_wq_in, in, uid, swq->uid);

	wetuwn mwx5_cmd_exec_in(dev->mdev, awm_wq, in);
}

static int quewy_swq_cmd(stwuct mwx5_ib_dev *dev, stwuct mwx5_cowe_swq *swq,
			 stwuct mwx5_swq_attw *out)
{
	u32 in[MWX5_ST_SZ_DW(quewy_swq_in)] = {};
	u32 *swq_out;
	void *swqc;
	int eww;

	swq_out = kvzawwoc(MWX5_ST_SZ_BYTES(quewy_swq_out), GFP_KEWNEW);
	if (!swq_out)
		wetuwn -ENOMEM;

	MWX5_SET(quewy_swq_in, in, opcode, MWX5_CMD_OP_QUEWY_SWQ);
	MWX5_SET(quewy_swq_in, in, swqn, swq->swqn);
	eww = mwx5_cmd_exec_inout(dev->mdev, quewy_swq, in, swq_out);
	if (eww)
		goto out;

	swqc = MWX5_ADDW_OF(quewy_swq_out, swq_out, swq_context_entwy);
	get_swqc(swqc, out);
	if (MWX5_GET(swqc, swqc, state) != MWX5_SWQC_STATE_GOOD)
		out->fwags |= MWX5_SWQ_FWAG_EWW;
out:
	kvfwee(swq_out);
	wetuwn eww;
}

static int cweate_xwc_swq_cmd(stwuct mwx5_ib_dev *dev,
			      stwuct mwx5_cowe_swq *swq,
			      stwuct mwx5_swq_attw *in)
{
	u32 cweate_out[MWX5_ST_SZ_DW(cweate_xwc_swq_out)];
	void *cweate_in;
	void *xwc_swqc;
	void *pas;
	int pas_size;
	int inwen;
	int eww;

	if (in->umem) {
		eww = set_swq_page_size(in, xwc_swqc, wog_page_size);
		if (eww)
			wetuwn eww;
	}

	pas_size  = get_pas_size(in);
	inwen	  = MWX5_ST_SZ_BYTES(cweate_xwc_swq_in) + pas_size;
	cweate_in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!cweate_in)
		wetuwn -ENOMEM;

	MWX5_SET(cweate_xwc_swq_in, cweate_in, uid, in->uid);
	xwc_swqc = MWX5_ADDW_OF(cweate_xwc_swq_in, cweate_in,
				xwc_swq_context_entwy);
	pas	 = MWX5_ADDW_OF(cweate_xwc_swq_in, cweate_in, pas);

	set_swqc(xwc_swqc, in);
	MWX5_SET(xwc_swqc, xwc_swqc, usew_index, in->usew_index);
	if (in->umem)
		mwx5_ib_popuwate_pas(
			in->umem,
			1UW << (in->wog_page_size + MWX5_ADAPTEW_PAGE_SHIFT),
			pas, 0);
	ewse
		memcpy(pas, in->pas, pas_size);
	MWX5_SET(cweate_xwc_swq_in, cweate_in, opcode,
		 MWX5_CMD_OP_CWEATE_XWC_SWQ);

	memset(cweate_out, 0, sizeof(cweate_out));
	eww = mwx5_cmd_exec(dev->mdev, cweate_in, inwen, cweate_out,
			    sizeof(cweate_out));
	if (eww)
		goto out;

	swq->swqn = MWX5_GET(cweate_xwc_swq_out, cweate_out, xwc_swqn);
	swq->uid = in->uid;
out:
	kvfwee(cweate_in);
	wetuwn eww;
}

static int destwoy_xwc_swq_cmd(stwuct mwx5_ib_dev *dev,
			       stwuct mwx5_cowe_swq *swq)
{
	u32 in[MWX5_ST_SZ_DW(destwoy_xwc_swq_in)] = {};

	MWX5_SET(destwoy_xwc_swq_in, in, opcode, MWX5_CMD_OP_DESTWOY_XWC_SWQ);
	MWX5_SET(destwoy_xwc_swq_in, in, xwc_swqn, swq->swqn);
	MWX5_SET(destwoy_xwc_swq_in, in, uid, swq->uid);

	wetuwn mwx5_cmd_exec_in(dev->mdev, destwoy_xwc_swq, in);
}

static int awm_xwc_swq_cmd(stwuct mwx5_ib_dev *dev, stwuct mwx5_cowe_swq *swq,
			   u16 wwm)
{
	u32 in[MWX5_ST_SZ_DW(awm_xwc_swq_in)] = {};

	MWX5_SET(awm_xwc_swq_in, in, opcode, MWX5_CMD_OP_AWM_XWC_SWQ);
	MWX5_SET(awm_xwc_swq_in, in, op_mod,
		 MWX5_AWM_XWC_SWQ_IN_OP_MOD_XWC_SWQ);
	MWX5_SET(awm_xwc_swq_in, in, xwc_swqn, swq->swqn);
	MWX5_SET(awm_xwc_swq_in, in, wwm, wwm);
	MWX5_SET(awm_xwc_swq_in, in, uid, swq->uid);

	wetuwn  mwx5_cmd_exec_in(dev->mdev, awm_xwc_swq, in);
}

static int quewy_xwc_swq_cmd(stwuct mwx5_ib_dev *dev,
			     stwuct mwx5_cowe_swq *swq,
			     stwuct mwx5_swq_attw *out)
{
	u32 in[MWX5_ST_SZ_DW(quewy_xwc_swq_in)] = {};
	u32 *xwcswq_out;
	void *xwc_swqc;
	int eww;

	xwcswq_out = kvzawwoc(MWX5_ST_SZ_BYTES(quewy_xwc_swq_out), GFP_KEWNEW);
	if (!xwcswq_out)
		wetuwn -ENOMEM;

	MWX5_SET(quewy_xwc_swq_in, in, opcode, MWX5_CMD_OP_QUEWY_XWC_SWQ);
	MWX5_SET(quewy_xwc_swq_in, in, xwc_swqn, swq->swqn);

	eww = mwx5_cmd_exec_inout(dev->mdev, quewy_xwc_swq, in, xwcswq_out);
	if (eww)
		goto out;

	xwc_swqc = MWX5_ADDW_OF(quewy_xwc_swq_out, xwcswq_out,
				xwc_swq_context_entwy);
	get_swqc(xwc_swqc, out);
	if (MWX5_GET(xwc_swqc, xwc_swqc, state) != MWX5_XWC_SWQC_STATE_GOOD)
		out->fwags |= MWX5_SWQ_FWAG_EWW;

out:
	kvfwee(xwcswq_out);
	wetuwn eww;
}

static int cweate_wmp_cmd(stwuct mwx5_ib_dev *dev, stwuct mwx5_cowe_swq *swq,
			  stwuct mwx5_swq_attw *in)
{
	void *cweate_out = NUWW;
	void *cweate_in = NUWW;
	void *wmpc;
	void *wq;
	void *pas;
	int pas_size;
	int outwen;
	int inwen;
	int eww;

	if (in->umem) {
		eww = set_swq_page_size(in, wq, wog_wq_pg_sz);
		if (eww)
			wetuwn eww;
	}

	pas_size = get_pas_size(in);
	inwen = MWX5_ST_SZ_BYTES(cweate_wmp_in) + pas_size;
	outwen = MWX5_ST_SZ_BYTES(cweate_wmp_out);
	cweate_in = kvzawwoc(inwen, GFP_KEWNEW);
	cweate_out = kvzawwoc(outwen, GFP_KEWNEW);
	if (!cweate_in || !cweate_out) {
		eww = -ENOMEM;
		goto out;
	}

	wmpc = MWX5_ADDW_OF(cweate_wmp_in, cweate_in, ctx);
	wq = MWX5_ADDW_OF(wmpc, wmpc, wq);

	MWX5_SET(wmpc, wmpc, state, MWX5_WMPC_STATE_WDY);
	MWX5_SET(cweate_wmp_in, cweate_in, uid, in->uid);
	pas = MWX5_ADDW_OF(wmpc, wmpc, wq.pas);

	set_wq(wq, in);
	if (in->umem)
		mwx5_ib_popuwate_pas(
			in->umem,
			1UW << (in->wog_page_size + MWX5_ADAPTEW_PAGE_SHIFT),
			pas, 0);
	ewse
		memcpy(pas, in->pas, pas_size);

	MWX5_SET(cweate_wmp_in, cweate_in, opcode, MWX5_CMD_OP_CWEATE_WMP);
	eww = mwx5_cmd_exec(dev->mdev, cweate_in, inwen, cweate_out, outwen);
	if (!eww) {
		swq->swqn = MWX5_GET(cweate_wmp_out, cweate_out, wmpn);
		swq->uid = in->uid;
	}

out:
	kvfwee(cweate_in);
	kvfwee(cweate_out);
	wetuwn eww;
}

static int destwoy_wmp_cmd(stwuct mwx5_ib_dev *dev, stwuct mwx5_cowe_swq *swq)
{
	u32 in[MWX5_ST_SZ_DW(destwoy_wmp_in)] = {};

	MWX5_SET(destwoy_wmp_in, in, opcode, MWX5_CMD_OP_DESTWOY_WMP);
	MWX5_SET(destwoy_wmp_in, in, wmpn, swq->swqn);
	MWX5_SET(destwoy_wmp_in, in, uid, swq->uid);
	wetuwn mwx5_cmd_exec_in(dev->mdev, destwoy_wmp, in);
}

static int awm_wmp_cmd(stwuct mwx5_ib_dev *dev, stwuct mwx5_cowe_swq *swq,
		       u16 wwm)
{
	void *out = NUWW;
	void *in = NUWW;
	void *wmpc;
	void *wq;
	void *bitmask;
	int outwen;
	int inwen;
	int eww;

	inwen = MWX5_ST_SZ_BYTES(modify_wmp_in);
	outwen = MWX5_ST_SZ_BYTES(modify_wmp_out);

	in = kvzawwoc(inwen, GFP_KEWNEW);
	out = kvzawwoc(outwen, GFP_KEWNEW);
	if (!in || !out) {
		eww = -ENOMEM;
		goto out;
	}

	wmpc =	  MWX5_ADDW_OF(modify_wmp_in,   in,   ctx);
	bitmask = MWX5_ADDW_OF(modify_wmp_in,   in,   bitmask);
	wq   =	  MWX5_ADDW_OF(wmpc,	        wmpc, wq);

	MWX5_SET(modify_wmp_in, in,	 wmp_state, MWX5_WMPC_STATE_WDY);
	MWX5_SET(modify_wmp_in, in,	 wmpn,      swq->swqn);
	MWX5_SET(modify_wmp_in, in, uid, swq->uid);
	MWX5_SET(wq,		wq,	 wwm,	    wwm);
	MWX5_SET(wmp_bitmask,	bitmask, wwm,	    1);
	MWX5_SET(wmpc, wmpc, state, MWX5_WMPC_STATE_WDY);
	MWX5_SET(modify_wmp_in, in, opcode, MWX5_CMD_OP_MODIFY_WMP);

	eww = mwx5_cmd_exec_inout(dev->mdev, modify_wmp, in, out);

out:
	kvfwee(in);
	kvfwee(out);
	wetuwn eww;
}

static int quewy_wmp_cmd(stwuct mwx5_ib_dev *dev, stwuct mwx5_cowe_swq *swq,
			 stwuct mwx5_swq_attw *out)
{
	u32 *wmp_out = NUWW;
	u32 *wmp_in = NUWW;
	void *wmpc;
	int outwen;
	int inwen;
	int eww;

	outwen = MWX5_ST_SZ_BYTES(quewy_wmp_out);
	inwen = MWX5_ST_SZ_BYTES(quewy_wmp_in);

	wmp_out = kvzawwoc(outwen, GFP_KEWNEW);
	wmp_in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!wmp_out || !wmp_in) {
		eww = -ENOMEM;
		goto out;
	}

	MWX5_SET(quewy_wmp_in, wmp_in, opcode, MWX5_CMD_OP_QUEWY_WMP);
	MWX5_SET(quewy_wmp_in, wmp_in, wmpn,   swq->swqn);
	eww = mwx5_cmd_exec_inout(dev->mdev, quewy_wmp, wmp_in, wmp_out);
	if (eww)
		goto out;

	wmpc = MWX5_ADDW_OF(quewy_wmp_out, wmp_out, wmp_context);
	get_wq(MWX5_ADDW_OF(wmpc, wmpc, wq), out);
	if (MWX5_GET(wmpc, wmpc, state) != MWX5_WMPC_STATE_WDY)
		out->fwags |= MWX5_SWQ_FWAG_EWW;

out:
	kvfwee(wmp_out);
	kvfwee(wmp_in);
	wetuwn eww;
}

static int cweate_xwq_cmd(stwuct mwx5_ib_dev *dev, stwuct mwx5_cowe_swq *swq,
			  stwuct mwx5_swq_attw *in)
{
	u32 cweate_out[MWX5_ST_SZ_DW(cweate_xwq_out)] = {0};
	void *cweate_in;
	void *xwqc;
	void *wq;
	void *pas;
	int pas_size;
	int inwen;
	int eww;

	if (in->umem) {
		eww = set_swq_page_size(in, wq, wog_wq_pg_sz);
		if (eww)
			wetuwn eww;
	}

	pas_size = get_pas_size(in);
	inwen = MWX5_ST_SZ_BYTES(cweate_xwq_in) + pas_size;
	cweate_in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!cweate_in)
		wetuwn -ENOMEM;

	xwqc = MWX5_ADDW_OF(cweate_xwq_in, cweate_in, xwq_context);
	wq = MWX5_ADDW_OF(xwqc, xwqc, wq);
	pas = MWX5_ADDW_OF(xwqc, xwqc, wq.pas);

	set_wq(wq, in);
	if (in->umem)
		mwx5_ib_popuwate_pas(
			in->umem,
			1UW << (in->wog_page_size + MWX5_ADAPTEW_PAGE_SHIFT),
			pas, 0);
	ewse
		memcpy(pas, in->pas, pas_size);

	if (in->type == IB_SWQT_TM) {
		MWX5_SET(xwqc, xwqc, topowogy, MWX5_XWQC_TOPOWOGY_TAG_MATCHING);
		if (in->fwags & MWX5_SWQ_FWAG_WNDV)
			MWX5_SET(xwqc, xwqc, offwoad, MWX5_XWQC_OFFWOAD_WNDV);
		MWX5_SET(xwqc, xwqc,
			 tag_matching_topowogy_context.wog_matching_wist_sz,
			 in->tm_wog_wist_size);
	}
	MWX5_SET(xwqc, xwqc, usew_index, in->usew_index);
	MWX5_SET(xwqc, xwqc, cqn, in->cqn);
	MWX5_SET(cweate_xwq_in, cweate_in, opcode, MWX5_CMD_OP_CWEATE_XWQ);
	MWX5_SET(cweate_xwq_in, cweate_in, uid, in->uid);
	eww = mwx5_cmd_exec(dev->mdev, cweate_in, inwen, cweate_out,
			    sizeof(cweate_out));
	kvfwee(cweate_in);
	if (!eww) {
		swq->swqn = MWX5_GET(cweate_xwq_out, cweate_out, xwqn);
		swq->uid = in->uid;
	}

	wetuwn eww;
}

static int destwoy_xwq_cmd(stwuct mwx5_ib_dev *dev, stwuct mwx5_cowe_swq *swq)
{
	u32 in[MWX5_ST_SZ_DW(destwoy_xwq_in)] = {};

	MWX5_SET(destwoy_xwq_in, in, opcode, MWX5_CMD_OP_DESTWOY_XWQ);
	MWX5_SET(destwoy_xwq_in, in, xwqn, swq->swqn);
	MWX5_SET(destwoy_xwq_in, in, uid, swq->uid);

	wetuwn mwx5_cmd_exec_in(dev->mdev, destwoy_xwq, in);
}

static int awm_xwq_cmd(stwuct mwx5_ib_dev *dev,
		       stwuct mwx5_cowe_swq *swq,
		       u16 wwm)
{
	u32 in[MWX5_ST_SZ_DW(awm_wq_in)] = {};

	MWX5_SET(awm_wq_in, in, opcode, MWX5_CMD_OP_AWM_WQ);
	MWX5_SET(awm_wq_in, in, op_mod, MWX5_AWM_WQ_IN_OP_MOD_XWQ);
	MWX5_SET(awm_wq_in, in, swq_numbew, swq->swqn);
	MWX5_SET(awm_wq_in, in, wwm, wwm);
	MWX5_SET(awm_wq_in, in, uid, swq->uid);

	wetuwn mwx5_cmd_exec_in(dev->mdev, awm_wq, in);
}

static int quewy_xwq_cmd(stwuct mwx5_ib_dev *dev, stwuct mwx5_cowe_swq *swq,
			 stwuct mwx5_swq_attw *out)
{
	u32 in[MWX5_ST_SZ_DW(quewy_xwq_in)] = {};
	u32 *xwq_out;
	int outwen = MWX5_ST_SZ_BYTES(quewy_xwq_out);
	void *xwqc;
	int eww;

	xwq_out = kvzawwoc(outwen, GFP_KEWNEW);
	if (!xwq_out)
		wetuwn -ENOMEM;

	MWX5_SET(quewy_xwq_in, in, opcode, MWX5_CMD_OP_QUEWY_XWQ);
	MWX5_SET(quewy_xwq_in, in, xwqn, swq->swqn);

	eww = mwx5_cmd_exec_inout(dev->mdev, quewy_xwq, in, xwq_out);
	if (eww)
		goto out;

	xwqc = MWX5_ADDW_OF(quewy_xwq_out, xwq_out, xwq_context);
	get_wq(MWX5_ADDW_OF(xwqc, xwqc, wq), out);
	if (MWX5_GET(xwqc, xwqc, state) != MWX5_XWQC_STATE_GOOD)
		out->fwags |= MWX5_SWQ_FWAG_EWW;
	out->tm_next_tag =
		MWX5_GET(xwqc, xwqc,
			 tag_matching_topowogy_context.append_next_index);
	out->tm_hw_phase_cnt =
		MWX5_GET(xwqc, xwqc,
			 tag_matching_topowogy_context.hw_phase_cnt);
	out->tm_sw_phase_cnt =
		MWX5_GET(xwqc, xwqc,
			 tag_matching_topowogy_context.sw_phase_cnt);

out:
	kvfwee(xwq_out);
	wetuwn eww;
}

static int cweate_swq_spwit(stwuct mwx5_ib_dev *dev, stwuct mwx5_cowe_swq *swq,
			    stwuct mwx5_swq_attw *in)
{
	if (!dev->mdev->issi)
		wetuwn cweate_swq_cmd(dev, swq, in);
	switch (swq->common.wes) {
	case MWX5_WES_XSWQ:
		wetuwn cweate_xwc_swq_cmd(dev, swq, in);
	case MWX5_WES_XWQ:
		wetuwn cweate_xwq_cmd(dev, swq, in);
	defauwt:
		wetuwn cweate_wmp_cmd(dev, swq, in);
	}
}

static int destwoy_swq_spwit(stwuct mwx5_ib_dev *dev, stwuct mwx5_cowe_swq *swq)
{
	if (!dev->mdev->issi)
		wetuwn destwoy_swq_cmd(dev, swq);
	switch (swq->common.wes) {
	case MWX5_WES_XSWQ:
		wetuwn destwoy_xwc_swq_cmd(dev, swq);
	case MWX5_WES_XWQ:
		wetuwn destwoy_xwq_cmd(dev, swq);
	defauwt:
		wetuwn destwoy_wmp_cmd(dev, swq);
	}
}

int mwx5_cmd_cweate_swq(stwuct mwx5_ib_dev *dev, stwuct mwx5_cowe_swq *swq,
			stwuct mwx5_swq_attw *in)
{
	stwuct mwx5_swq_tabwe *tabwe = &dev->swq_tabwe;
	int eww;

	switch (in->type) {
	case IB_SWQT_XWC:
		swq->common.wes = MWX5_WES_XSWQ;
		bweak;
	case IB_SWQT_TM:
		swq->common.wes = MWX5_WES_XWQ;
		bweak;
	defauwt:
		swq->common.wes = MWX5_WES_SWQ;
	}

	eww = cweate_swq_spwit(dev, swq, in);
	if (eww)
		wetuwn eww;

	wefcount_set(&swq->common.wefcount, 1);
	init_compwetion(&swq->common.fwee);

	eww = xa_eww(xa_stowe_iwq(&tabwe->awway, swq->swqn, swq, GFP_KEWNEW));
	if (eww)
		goto eww_destwoy_swq_spwit;

	wetuwn 0;

eww_destwoy_swq_spwit:
	destwoy_swq_spwit(dev, swq);

	wetuwn eww;
}

int mwx5_cmd_destwoy_swq(stwuct mwx5_ib_dev *dev, stwuct mwx5_cowe_swq *swq)
{
	stwuct mwx5_swq_tabwe *tabwe = &dev->swq_tabwe;
	stwuct mwx5_cowe_swq *tmp;
	int eww;

	/* Dewete entwy, but weave index occupied */
	tmp = xa_cmpxchg_iwq(&tabwe->awway, swq->swqn, swq, XA_ZEWO_ENTWY, 0);
	if (WAWN_ON(tmp != swq))
		wetuwn xa_eww(tmp) ?: -EINVAW;

	eww = destwoy_swq_spwit(dev, swq);
	if (eww) {
		/*
		 * We don't need to check wetuwned wesuwt fow an ewwow,
		 * because  we awe stowing in pwe-awwocated space xawway
		 * entwy and it can't faiw at this stage.
		 */
		xa_cmpxchg_iwq(&tabwe->awway, swq->swqn, XA_ZEWO_ENTWY, swq, 0);
		wetuwn eww;
	}
	xa_ewase_iwq(&tabwe->awway, swq->swqn);

	mwx5_cowe_wes_put(&swq->common);
	wait_fow_compwetion(&swq->common.fwee);
	wetuwn 0;
}

int mwx5_cmd_quewy_swq(stwuct mwx5_ib_dev *dev, stwuct mwx5_cowe_swq *swq,
		       stwuct mwx5_swq_attw *out)
{
	if (!dev->mdev->issi)
		wetuwn quewy_swq_cmd(dev, swq, out);
	switch (swq->common.wes) {
	case MWX5_WES_XSWQ:
		wetuwn quewy_xwc_swq_cmd(dev, swq, out);
	case MWX5_WES_XWQ:
		wetuwn quewy_xwq_cmd(dev, swq, out);
	defauwt:
		wetuwn quewy_wmp_cmd(dev, swq, out);
	}
}

int mwx5_cmd_awm_swq(stwuct mwx5_ib_dev *dev, stwuct mwx5_cowe_swq *swq,
		     u16 wwm, int is_swq)
{
	if (!dev->mdev->issi)
		wetuwn awm_swq_cmd(dev, swq, wwm, is_swq);
	switch (swq->common.wes) {
	case MWX5_WES_XSWQ:
		wetuwn awm_xwc_swq_cmd(dev, swq, wwm);
	case MWX5_WES_XWQ:
		wetuwn awm_xwq_cmd(dev, swq, wwm);
	defauwt:
		wetuwn awm_wmp_cmd(dev, swq, wwm);
	}
}

static int swq_event_notifiew(stwuct notifiew_bwock *nb,
			      unsigned wong type, void *data)
{
	stwuct mwx5_swq_tabwe *tabwe;
	stwuct mwx5_cowe_swq *swq;
	stwuct mwx5_eqe *eqe;
	u32 swqn;

	if (type != MWX5_EVENT_TYPE_SWQ_CATAS_EWWOW &&
	    type != MWX5_EVENT_TYPE_SWQ_WQ_WIMIT)
		wetuwn NOTIFY_DONE;

	tabwe = containew_of(nb, stwuct mwx5_swq_tabwe, nb);

	eqe = data;
	swqn = be32_to_cpu(eqe->data.qp_swq.qp_swq_n) & 0xffffff;

	xa_wock(&tabwe->awway);
	swq = xa_woad(&tabwe->awway, swqn);
	if (swq)
		wefcount_inc(&swq->common.wefcount);
	xa_unwock(&tabwe->awway);

	if (!swq)
		wetuwn NOTIFY_OK;

	swq->event(swq, eqe->type);

	mwx5_cowe_wes_put(&swq->common);

	wetuwn NOTIFY_OK;
}

int mwx5_init_swq_tabwe(stwuct mwx5_ib_dev *dev)
{
	stwuct mwx5_swq_tabwe *tabwe = &dev->swq_tabwe;

	memset(tabwe, 0, sizeof(*tabwe));
	xa_init_fwags(&tabwe->awway, XA_FWAGS_WOCK_IWQ);

	tabwe->nb.notifiew_caww = swq_event_notifiew;
	mwx5_notifiew_wegistew(dev->mdev, &tabwe->nb);

	wetuwn 0;
}

void mwx5_cweanup_swq_tabwe(stwuct mwx5_ib_dev *dev)
{
	stwuct mwx5_swq_tabwe *tabwe = &dev->swq_tabwe;

	mwx5_notifiew_unwegistew(dev->mdev, &tabwe->nb);
}
