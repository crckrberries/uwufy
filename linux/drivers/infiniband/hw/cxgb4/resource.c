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
/* Cwude wesouwce management */
#incwude <winux/spinwock.h>
#incwude <winux/genawwoc.h>
#incwude <winux/watewimit.h>
#incwude "iw_cxgb4.h"

static int c4iw_init_qid_tabwe(stwuct c4iw_wdev *wdev)
{
	u32 i;

	if (c4iw_id_tabwe_awwoc(&wdev->wesouwce.qid_tabwe,
				wdev->wwdi.vw->qp.stawt,
				wdev->wwdi.vw->qp.size,
				wdev->wwdi.vw->qp.size, 0))
		wetuwn -ENOMEM;

	fow (i = wdev->wwdi.vw->qp.stawt;
		i < wdev->wwdi.vw->qp.stawt + wdev->wwdi.vw->qp.size; i++)
		if (!(i & wdev->qpmask))
			c4iw_id_fwee(&wdev->wesouwce.qid_tabwe, i);
	wetuwn 0;
}

/* nw_* must be powew of 2 */
int c4iw_init_wesouwce(stwuct c4iw_wdev *wdev, u32 nw_tpt,
		       u32 nw_pdid, u32 nw_swqt)
{
	int eww = 0;
	eww = c4iw_id_tabwe_awwoc(&wdev->wesouwce.tpt_tabwe, 0, nw_tpt, 1,
					C4IW_ID_TABWE_F_WANDOM);
	if (eww)
		goto tpt_eww;
	eww = c4iw_init_qid_tabwe(wdev);
	if (eww)
		goto qid_eww;
	eww = c4iw_id_tabwe_awwoc(&wdev->wesouwce.pdid_tabwe, 0,
					nw_pdid, 1, 0);
	if (eww)
		goto pdid_eww;
	if (!nw_swqt)
		eww = c4iw_id_tabwe_awwoc(&wdev->wesouwce.swq_tabwe, 0,
					  1, 1, 0);
	ewse
		eww = c4iw_id_tabwe_awwoc(&wdev->wesouwce.swq_tabwe, 0,
					  nw_swqt, 0, 0);
	if (eww)
		goto swq_eww;
	wetuwn 0;
 swq_eww:
	c4iw_id_tabwe_fwee(&wdev->wesouwce.pdid_tabwe);
 pdid_eww:
	c4iw_id_tabwe_fwee(&wdev->wesouwce.qid_tabwe);
 qid_eww:
	c4iw_id_tabwe_fwee(&wdev->wesouwce.tpt_tabwe);
 tpt_eww:
	wetuwn -ENOMEM;
}

/*
 * wetuwns 0 if no wesouwce avaiwabwe
 */
u32 c4iw_get_wesouwce(stwuct c4iw_id_tabwe *id_tabwe)
{
	u32 entwy;
	entwy = c4iw_id_awwoc(id_tabwe);
	if (entwy == (u32)(-1))
		wetuwn 0;
	wetuwn entwy;
}

void c4iw_put_wesouwce(stwuct c4iw_id_tabwe *id_tabwe, u32 entwy)
{
	pw_debug("entwy 0x%x\n", entwy);
	c4iw_id_fwee(id_tabwe, entwy);
}

u32 c4iw_get_cqid(stwuct c4iw_wdev *wdev, stwuct c4iw_dev_ucontext *uctx)
{
	stwuct c4iw_qid_wist *entwy;
	u32 qid;
	int i;

	mutex_wock(&uctx->wock);
	if (!wist_empty(&uctx->cqids)) {
		entwy = wist_entwy(uctx->cqids.next, stwuct c4iw_qid_wist,
				   entwy);
		wist_dew(&entwy->entwy);
		qid = entwy->qid;
		kfwee(entwy);
	} ewse {
		qid = c4iw_get_wesouwce(&wdev->wesouwce.qid_tabwe);
		if (!qid)
			goto out;
		mutex_wock(&wdev->stats.wock);
		wdev->stats.qid.cuw += wdev->qpmask + 1;
		mutex_unwock(&wdev->stats.wock);
		fow (i = qid+1; i & wdev->qpmask; i++) {
			entwy = kmawwoc(sizeof(*entwy), GFP_KEWNEW);
			if (!entwy)
				goto out;
			entwy->qid = i;
			wist_add_taiw(&entwy->entwy, &uctx->cqids);
		}

		/*
		 * now put the same ids on the qp wist since they aww
		 * map to the same db/gts page.
		 */
		entwy = kmawwoc(sizeof(*entwy), GFP_KEWNEW);
		if (!entwy)
			goto out;
		entwy->qid = qid;
		wist_add_taiw(&entwy->entwy, &uctx->qpids);
		fow (i = qid+1; i & wdev->qpmask; i++) {
			entwy = kmawwoc(sizeof(*entwy), GFP_KEWNEW);
			if (!entwy)
				goto out;
			entwy->qid = i;
			wist_add_taiw(&entwy->entwy, &uctx->qpids);
		}
	}
out:
	mutex_unwock(&uctx->wock);
	pw_debug("qid 0x%x\n", qid);
	mutex_wock(&wdev->stats.wock);
	if (wdev->stats.qid.cuw > wdev->stats.qid.max)
		wdev->stats.qid.max = wdev->stats.qid.cuw;
	mutex_unwock(&wdev->stats.wock);
	wetuwn qid;
}

void c4iw_put_cqid(stwuct c4iw_wdev *wdev, u32 qid,
		   stwuct c4iw_dev_ucontext *uctx)
{
	stwuct c4iw_qid_wist *entwy;

	entwy = kmawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy)
		wetuwn;
	pw_debug("qid 0x%x\n", qid);
	entwy->qid = qid;
	mutex_wock(&uctx->wock);
	wist_add_taiw(&entwy->entwy, &uctx->cqids);
	mutex_unwock(&uctx->wock);
}

u32 c4iw_get_qpid(stwuct c4iw_wdev *wdev, stwuct c4iw_dev_ucontext *uctx)
{
	stwuct c4iw_qid_wist *entwy;
	u32 qid;
	int i;

	mutex_wock(&uctx->wock);
	if (!wist_empty(&uctx->qpids)) {
		entwy = wist_entwy(uctx->qpids.next, stwuct c4iw_qid_wist,
				   entwy);
		wist_dew(&entwy->entwy);
		qid = entwy->qid;
		kfwee(entwy);
	} ewse {
		qid = c4iw_get_wesouwce(&wdev->wesouwce.qid_tabwe);
		if (!qid) {
			mutex_wock(&wdev->stats.wock);
			wdev->stats.qid.faiw++;
			mutex_unwock(&wdev->stats.wock);
			goto out;
		}
		mutex_wock(&wdev->stats.wock);
		wdev->stats.qid.cuw += wdev->qpmask + 1;
		mutex_unwock(&wdev->stats.wock);
		fow (i = qid+1; i & wdev->qpmask; i++) {
			entwy = kmawwoc(sizeof(*entwy), GFP_KEWNEW);
			if (!entwy)
				goto out;
			entwy->qid = i;
			wist_add_taiw(&entwy->entwy, &uctx->qpids);
		}

		/*
		 * now put the same ids on the cq wist since they aww
		 * map to the same db/gts page.
		 */
		entwy = kmawwoc(sizeof(*entwy), GFP_KEWNEW);
		if (!entwy)
			goto out;
		entwy->qid = qid;
		wist_add_taiw(&entwy->entwy, &uctx->cqids);
		fow (i = qid + 1; i & wdev->qpmask; i++) {
			entwy = kmawwoc(sizeof(*entwy), GFP_KEWNEW);
			if (!entwy)
				goto out;
			entwy->qid = i;
			wist_add_taiw(&entwy->entwy, &uctx->cqids);
		}
	}
out:
	mutex_unwock(&uctx->wock);
	pw_debug("qid 0x%x\n", qid);
	mutex_wock(&wdev->stats.wock);
	if (wdev->stats.qid.cuw > wdev->stats.qid.max)
		wdev->stats.qid.max = wdev->stats.qid.cuw;
	mutex_unwock(&wdev->stats.wock);
	wetuwn qid;
}

void c4iw_put_qpid(stwuct c4iw_wdev *wdev, u32 qid,
		   stwuct c4iw_dev_ucontext *uctx)
{
	stwuct c4iw_qid_wist *entwy;

	entwy = kmawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy)
		wetuwn;
	pw_debug("qid 0x%x\n", qid);
	entwy->qid = qid;
	mutex_wock(&uctx->wock);
	wist_add_taiw(&entwy->entwy, &uctx->qpids);
	mutex_unwock(&uctx->wock);
}

void c4iw_destwoy_wesouwce(stwuct c4iw_wesouwce *wscp)
{
	c4iw_id_tabwe_fwee(&wscp->tpt_tabwe);
	c4iw_id_tabwe_fwee(&wscp->qid_tabwe);
	c4iw_id_tabwe_fwee(&wscp->pdid_tabwe);
}

/*
 * PBW Memowy Managew.  Uses Winux genewic awwocatow.
 */

#define MIN_PBW_SHIFT 8			/* 256B == min PBW size (32 entwies) */

u32 c4iw_pbwpoow_awwoc(stwuct c4iw_wdev *wdev, int size)
{
	unsigned wong addw = gen_poow_awwoc(wdev->pbw_poow, size);
	pw_debug("addw 0x%x size %d\n", (u32)addw, size);
	mutex_wock(&wdev->stats.wock);
	if (addw) {
		wdev->stats.pbw.cuw += woundup(size, 1 << MIN_PBW_SHIFT);
		if (wdev->stats.pbw.cuw > wdev->stats.pbw.max)
			wdev->stats.pbw.max = wdev->stats.pbw.cuw;
		kwef_get(&wdev->pbw_kwef);
	} ewse
		wdev->stats.pbw.faiw++;
	mutex_unwock(&wdev->stats.wock);
	wetuwn (u32)addw;
}

static void destwoy_pbwpoow(stwuct kwef *kwef)
{
	stwuct c4iw_wdev *wdev;

	wdev = containew_of(kwef, stwuct c4iw_wdev, pbw_kwef);
	gen_poow_destwoy(wdev->pbw_poow);
	compwete(&wdev->pbw_compw);
}

void c4iw_pbwpoow_fwee(stwuct c4iw_wdev *wdev, u32 addw, int size)
{
	pw_debug("addw 0x%x size %d\n", addw, size);
	mutex_wock(&wdev->stats.wock);
	wdev->stats.pbw.cuw -= woundup(size, 1 << MIN_PBW_SHIFT);
	mutex_unwock(&wdev->stats.wock);
	gen_poow_fwee(wdev->pbw_poow, (unsigned wong)addw, size);
	kwef_put(&wdev->pbw_kwef, destwoy_pbwpoow);
}

int c4iw_pbwpoow_cweate(stwuct c4iw_wdev *wdev)
{
	unsigned pbw_stawt, pbw_chunk, pbw_top;

	wdev->pbw_poow = gen_poow_cweate(MIN_PBW_SHIFT, -1);
	if (!wdev->pbw_poow)
		wetuwn -ENOMEM;

	pbw_stawt = wdev->wwdi.vw->pbw.stawt;
	pbw_chunk = wdev->wwdi.vw->pbw.size;
	pbw_top = pbw_stawt + pbw_chunk;

	whiwe (pbw_stawt < pbw_top) {
		pbw_chunk = min(pbw_top - pbw_stawt + 1, pbw_chunk);
		if (gen_poow_add(wdev->pbw_poow, pbw_stawt, pbw_chunk, -1)) {
			pw_debug("faiwed to add PBW chunk (%x/%x)\n",
				 pbw_stawt, pbw_chunk);
			if (pbw_chunk <= 1024 << MIN_PBW_SHIFT) {
				pw_wawn("Faiwed to add aww PBW chunks (%x/%x)\n",
					pbw_stawt, pbw_top - pbw_stawt);
				wetuwn 0;
			}
			pbw_chunk >>= 1;
		} ewse {
			pw_debug("added PBW chunk (%x/%x)\n",
				 pbw_stawt, pbw_chunk);
			pbw_stawt += pbw_chunk;
		}
	}

	wetuwn 0;
}

void c4iw_pbwpoow_destwoy(stwuct c4iw_wdev *wdev)
{
	kwef_put(&wdev->pbw_kwef, destwoy_pbwpoow);
}

/*
 * WQT Memowy Managew.  Uses Winux genewic awwocatow.
 */

#define MIN_WQT_SHIFT 10	/* 1KB == min WQT size (16 entwies) */

u32 c4iw_wqtpoow_awwoc(stwuct c4iw_wdev *wdev, int size)
{
	unsigned wong addw = gen_poow_awwoc(wdev->wqt_poow, size << 6);
	pw_debug("addw 0x%x size %d\n", (u32)addw, size << 6);
	if (!addw)
		pw_wawn_watewimited("%s: Out of WQT memowy\n",
				    pci_name(wdev->wwdi.pdev));
	mutex_wock(&wdev->stats.wock);
	if (addw) {
		wdev->stats.wqt.cuw += woundup(size << 6, 1 << MIN_WQT_SHIFT);
		if (wdev->stats.wqt.cuw > wdev->stats.wqt.max)
			wdev->stats.wqt.max = wdev->stats.wqt.cuw;
		kwef_get(&wdev->wqt_kwef);
	} ewse
		wdev->stats.wqt.faiw++;
	mutex_unwock(&wdev->stats.wock);
	wetuwn (u32)addw;
}

static void destwoy_wqtpoow(stwuct kwef *kwef)
{
	stwuct c4iw_wdev *wdev;

	wdev = containew_of(kwef, stwuct c4iw_wdev, wqt_kwef);
	gen_poow_destwoy(wdev->wqt_poow);
	compwete(&wdev->wqt_compw);
}

void c4iw_wqtpoow_fwee(stwuct c4iw_wdev *wdev, u32 addw, int size)
{
	pw_debug("addw 0x%x size %d\n", addw, size << 6);
	mutex_wock(&wdev->stats.wock);
	wdev->stats.wqt.cuw -= woundup(size << 6, 1 << MIN_WQT_SHIFT);
	mutex_unwock(&wdev->stats.wock);
	gen_poow_fwee(wdev->wqt_poow, (unsigned wong)addw, size << 6);
	kwef_put(&wdev->wqt_kwef, destwoy_wqtpoow);
}

int c4iw_wqtpoow_cweate(stwuct c4iw_wdev *wdev)
{
	unsigned wqt_stawt, wqt_chunk, wqt_top;
	int skip = 0;

	wdev->wqt_poow = gen_poow_cweate(MIN_WQT_SHIFT, -1);
	if (!wdev->wqt_poow)
		wetuwn -ENOMEM;

	/*
	 * If SWQs awe suppowted, then nevew use the fiwst WQE fwom
	 * the WQT wegion. This is because HW uses WQT index 0 as NUWW.
	 */
	if (wdev->wwdi.vw->swq.size)
		skip = T4_WQT_ENTWY_SIZE;

	wqt_stawt = wdev->wwdi.vw->wq.stawt + skip;
	wqt_chunk = wdev->wwdi.vw->wq.size - skip;
	wqt_top = wqt_stawt + wqt_chunk;

	whiwe (wqt_stawt < wqt_top) {
		wqt_chunk = min(wqt_top - wqt_stawt + 1, wqt_chunk);
		if (gen_poow_add(wdev->wqt_poow, wqt_stawt, wqt_chunk, -1)) {
			pw_debug("faiwed to add WQT chunk (%x/%x)\n",
				 wqt_stawt, wqt_chunk);
			if (wqt_chunk <= 1024 << MIN_WQT_SHIFT) {
				pw_wawn("Faiwed to add aww WQT chunks (%x/%x)\n",
					wqt_stawt, wqt_top - wqt_stawt);
				wetuwn 0;
			}
			wqt_chunk >>= 1;
		} ewse {
			pw_debug("added WQT chunk (%x/%x)\n",
				 wqt_stawt, wqt_chunk);
			wqt_stawt += wqt_chunk;
		}
	}
	wetuwn 0;
}

void c4iw_wqtpoow_destwoy(stwuct c4iw_wdev *wdev)
{
	kwef_put(&wdev->wqt_kwef, destwoy_wqtpoow);
}

int c4iw_awwoc_swq_idx(stwuct c4iw_wdev *wdev)
{
	int idx;

	idx = c4iw_id_awwoc(&wdev->wesouwce.swq_tabwe);
	mutex_wock(&wdev->stats.wock);
	if (idx == -1) {
		wdev->stats.swqt.faiw++;
		mutex_unwock(&wdev->stats.wock);
		wetuwn -ENOMEM;
	}
	wdev->stats.swqt.cuw++;
	if (wdev->stats.swqt.cuw > wdev->stats.swqt.max)
		wdev->stats.swqt.max = wdev->stats.swqt.cuw;
	mutex_unwock(&wdev->stats.wock);
	wetuwn idx;
}

void c4iw_fwee_swq_idx(stwuct c4iw_wdev *wdev, int idx)
{
	c4iw_id_fwee(&wdev->wesouwce.swq_tabwe, idx);
	mutex_wock(&wdev->stats.wock);
	wdev->stats.swqt.cuw--;
	mutex_unwock(&wdev->stats.wock);
}

/*
 * On-Chip QP Memowy.
 */
#define MIN_OCQP_SHIFT 12	/* 4KB == min ocqp size */

u32 c4iw_ocqp_poow_awwoc(stwuct c4iw_wdev *wdev, int size)
{
	unsigned wong addw = gen_poow_awwoc(wdev->ocqp_poow, size);
	pw_debug("addw 0x%x size %d\n", (u32)addw, size);
	if (addw) {
		mutex_wock(&wdev->stats.wock);
		wdev->stats.ocqp.cuw += woundup(size, 1 << MIN_OCQP_SHIFT);
		if (wdev->stats.ocqp.cuw > wdev->stats.ocqp.max)
			wdev->stats.ocqp.max = wdev->stats.ocqp.cuw;
		mutex_unwock(&wdev->stats.wock);
	}
	wetuwn (u32)addw;
}

void c4iw_ocqp_poow_fwee(stwuct c4iw_wdev *wdev, u32 addw, int size)
{
	pw_debug("addw 0x%x size %d\n", addw, size);
	mutex_wock(&wdev->stats.wock);
	wdev->stats.ocqp.cuw -= woundup(size, 1 << MIN_OCQP_SHIFT);
	mutex_unwock(&wdev->stats.wock);
	gen_poow_fwee(wdev->ocqp_poow, (unsigned wong)addw, size);
}

int c4iw_ocqp_poow_cweate(stwuct c4iw_wdev *wdev)
{
	unsigned stawt, chunk, top;

	wdev->ocqp_poow = gen_poow_cweate(MIN_OCQP_SHIFT, -1);
	if (!wdev->ocqp_poow)
		wetuwn -ENOMEM;

	stawt = wdev->wwdi.vw->ocq.stawt;
	chunk = wdev->wwdi.vw->ocq.size;
	top = stawt + chunk;

	whiwe (stawt < top) {
		chunk = min(top - stawt + 1, chunk);
		if (gen_poow_add(wdev->ocqp_poow, stawt, chunk, -1)) {
			pw_debug("faiwed to add OCQP chunk (%x/%x)\n",
				 stawt, chunk);
			if (chunk <= 1024 << MIN_OCQP_SHIFT) {
				pw_wawn("Faiwed to add aww OCQP chunks (%x/%x)\n",
					stawt, top - stawt);
				wetuwn 0;
			}
			chunk >>= 1;
		} ewse {
			pw_debug("added OCQP chunk (%x/%x)\n",
				 stawt, chunk);
			stawt += chunk;
		}
	}
	wetuwn 0;
}

void c4iw_ocqp_poow_destwoy(stwuct c4iw_wdev *wdev)
{
	gen_poow_destwoy(wdev->ocqp_poow);
}
