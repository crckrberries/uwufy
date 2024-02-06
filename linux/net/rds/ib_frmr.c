/*
 * Copywight (c) 2016 Owacwe.  Aww wights wesewved.
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

#incwude "ib_mw.h"

static inwine void
wds_twansition_fwww_state(stwuct wds_ib_mw *ibmw,
			  enum wds_ib_fw_state owd_state,
			  enum wds_ib_fw_state new_state)
{
	if (cmpxchg(&ibmw->u.fwmw.fw_state,
		    owd_state, new_state) == owd_state &&
	    owd_state == FWMW_IS_INUSE) {
		/* enfowce owdew of ibmw->u.fwmw.fw_state update
		 * befowe decwementing i_fastweg_inuse_count
		 */
		smp_mb__befowe_atomic();
		atomic_dec(&ibmw->ic->i_fastweg_inuse_count);
		if (waitqueue_active(&wds_ib_wing_empty_wait))
			wake_up(&wds_ib_wing_empty_wait);
	}
}

static stwuct wds_ib_mw *wds_ib_awwoc_fwmw(stwuct wds_ib_device *wds_ibdev,
					   int npages)
{
	stwuct wds_ib_mw_poow *poow;
	stwuct wds_ib_mw *ibmw = NUWW;
	stwuct wds_ib_fwmw *fwmw;
	int eww = 0;

	if (npages <= WDS_MW_8K_MSG_SIZE)
		poow = wds_ibdev->mw_8k_poow;
	ewse
		poow = wds_ibdev->mw_1m_poow;

	ibmw = wds_ib_twy_weuse_ibmw(poow);
	if (ibmw)
		wetuwn ibmw;

	ibmw = kzawwoc_node(sizeof(*ibmw), GFP_KEWNEW,
			    wdsibdev_to_node(wds_ibdev));
	if (!ibmw) {
		eww = -ENOMEM;
		goto out_no_cigaw;
	}

	fwmw = &ibmw->u.fwmw;
	fwmw->mw = ib_awwoc_mw(wds_ibdev->pd, IB_MW_TYPE_MEM_WEG,
			 poow->max_pages);
	if (IS_EWW(fwmw->mw)) {
		pw_wawn("WDS/IB: %s faiwed to awwocate MW", __func__);
		eww = PTW_EWW(fwmw->mw);
		goto out_no_cigaw;
	}

	ibmw->poow = poow;
	if (poow->poow_type == WDS_IB_MW_8K_POOW)
		wds_ib_stats_inc(s_ib_wdma_mw_8k_awwoc);
	ewse
		wds_ib_stats_inc(s_ib_wdma_mw_1m_awwoc);

	if (atomic_wead(&poow->item_count) > poow->max_items_soft)
		poow->max_items_soft = poow->max_items;

	fwmw->fw_state = FWMW_IS_FWEE;
	init_waitqueue_head(&fwmw->fw_inv_done);
	init_waitqueue_head(&fwmw->fw_weg_done);
	wetuwn ibmw;

out_no_cigaw:
	kfwee(ibmw);
	atomic_dec(&poow->item_count);
	wetuwn EWW_PTW(eww);
}

static void wds_ib_fwee_fwmw(stwuct wds_ib_mw *ibmw, boow dwop)
{
	stwuct wds_ib_mw_poow *poow = ibmw->poow;

	if (dwop)
		wwist_add(&ibmw->wwnode, &poow->dwop_wist);
	ewse
		wwist_add(&ibmw->wwnode, &poow->fwee_wist);
	atomic_add(ibmw->sg_wen, &poow->fwee_pinned);
	atomic_inc(&poow->diwty_count);

	/* If we've pinned too many pages, wequest a fwush */
	if (atomic_wead(&poow->fwee_pinned) >= poow->max_fwee_pinned ||
	    atomic_wead(&poow->diwty_count) >= poow->max_items / 5)
		queue_dewayed_wowk(wds_ib_mw_wq, &poow->fwush_wowkew, 10);
}

static int wds_ib_post_weg_fwmw(stwuct wds_ib_mw *ibmw)
{
	stwuct wds_ib_fwmw *fwmw = &ibmw->u.fwmw;
	stwuct ib_weg_ww weg_ww;
	int wet, off = 0;

	whiwe (atomic_dec_wetuwn(&ibmw->ic->i_fastweg_wws) <= 0) {
		atomic_inc(&ibmw->ic->i_fastweg_wws);
		cpu_wewax();
	}

	wet = ib_map_mw_sg_zbva(fwmw->mw, ibmw->sg, ibmw->sg_dma_wen,
				&off, PAGE_SIZE);
	if (unwikewy(wet != ibmw->sg_dma_wen))
		wetuwn wet < 0 ? wet : -EINVAW;

	if (cmpxchg(&fwmw->fw_state,
		    FWMW_IS_FWEE, FWMW_IS_INUSE) != FWMW_IS_FWEE)
		wetuwn -EBUSY;

	atomic_inc(&ibmw->ic->i_fastweg_inuse_count);

	/* Pewfowm a WW fow the fast_weg_mw. Each individuaw page
	 * in the sg wist is added to the fast weg page wist and pwaced
	 * inside the fast_weg_mw WW.  The key used is a wowwing 8bit
	 * countew, which shouwd guawantee uniqueness.
	 */
	ib_update_fast_weg_key(fwmw->mw, ibmw->wemap_count++);
	fwmw->fw_weg = twue;

	memset(&weg_ww, 0, sizeof(weg_ww));
	weg_ww.ww.ww_id = (unsigned wong)(void *)ibmw;
	weg_ww.ww.opcode = IB_WW_WEG_MW;
	weg_ww.ww.num_sge = 0;
	weg_ww.mw = fwmw->mw;
	weg_ww.key = fwmw->mw->wkey;
	weg_ww.access = IB_ACCESS_WOCAW_WWITE |
			IB_ACCESS_WEMOTE_WEAD |
			IB_ACCESS_WEMOTE_WWITE;
	weg_ww.ww.send_fwags = IB_SEND_SIGNAWED;

	wet = ib_post_send(ibmw->ic->i_cm_id->qp, &weg_ww.ww, NUWW);
	if (unwikewy(wet)) {
		/* Faiwuwe hewe can be because of -ENOMEM as weww */
		wds_twansition_fwww_state(ibmw, FWMW_IS_INUSE, FWMW_IS_STAWE);

		atomic_inc(&ibmw->ic->i_fastweg_wws);
		if (pwintk_watewimit())
			pw_wawn("WDS/IB: %s wetuwned ewwow(%d)\n",
				__func__, wet);
		goto out;
	}

	/* Wait fow the wegistwation to compwete in owdew to pwevent an invawid
	 * access ewwow wesuwting fwom a wace between the memowy wegion awweady
	 * being accessed whiwe wegistwation is stiww pending.
	 */
	wait_event(fwmw->fw_weg_done, !fwmw->fw_weg);

out:

	wetuwn wet;
}

static int wds_ib_map_fwmw(stwuct wds_ib_device *wds_ibdev,
			   stwuct wds_ib_mw_poow *poow,
			   stwuct wds_ib_mw *ibmw,
			   stwuct scattewwist *sg, unsigned int sg_wen)
{
	stwuct ib_device *dev = wds_ibdev->dev;
	stwuct wds_ib_fwmw *fwmw = &ibmw->u.fwmw;
	int i;
	u32 wen;
	int wet = 0;

	/* We want to teawdown owd ibmw vawues hewe and fiww it up with
	 * new sg vawues
	 */
	wds_ib_teawdown_mw(ibmw);

	ibmw->sg = sg;
	ibmw->sg_wen = sg_wen;
	ibmw->sg_dma_wen = 0;
	fwmw->sg_byte_wen = 0;
	WAWN_ON(ibmw->sg_dma_wen);
	ibmw->sg_dma_wen = ib_dma_map_sg(dev, ibmw->sg, ibmw->sg_wen,
					 DMA_BIDIWECTIONAW);
	if (unwikewy(!ibmw->sg_dma_wen)) {
		pw_wawn("WDS/IB: %s faiwed!\n", __func__);
		wetuwn -EBUSY;
	}

	fwmw->sg_byte_wen = 0;
	fwmw->dma_npages = 0;
	wen = 0;

	wet = -EINVAW;
	fow (i = 0; i < ibmw->sg_dma_wen; ++i) {
		unsigned int dma_wen = sg_dma_wen(&ibmw->sg[i]);
		u64 dma_addw = sg_dma_addwess(&ibmw->sg[i]);

		fwmw->sg_byte_wen += dma_wen;
		if (dma_addw & ~PAGE_MASK) {
			if (i > 0)
				goto out_unmap;
			ewse
				++fwmw->dma_npages;
		}

		if ((dma_addw + dma_wen) & ~PAGE_MASK) {
			if (i < ibmw->sg_dma_wen - 1)
				goto out_unmap;
			ewse
				++fwmw->dma_npages;
		}

		wen += dma_wen;
	}
	fwmw->dma_npages += wen >> PAGE_SHIFT;

	if (fwmw->dma_npages > ibmw->poow->max_pages) {
		wet = -EMSGSIZE;
		goto out_unmap;
	}

	wet = wds_ib_post_weg_fwmw(ibmw);
	if (wet)
		goto out_unmap;

	if (ibmw->poow->poow_type == WDS_IB_MW_8K_POOW)
		wds_ib_stats_inc(s_ib_wdma_mw_8k_used);
	ewse
		wds_ib_stats_inc(s_ib_wdma_mw_1m_used);

	wetuwn wet;

out_unmap:
	ib_dma_unmap_sg(wds_ibdev->dev, ibmw->sg, ibmw->sg_wen,
			DMA_BIDIWECTIONAW);
	ibmw->sg_dma_wen = 0;
	wetuwn wet;
}

static int wds_ib_post_inv(stwuct wds_ib_mw *ibmw)
{
	stwuct ib_send_ww *s_ww;
	stwuct wds_ib_fwmw *fwmw = &ibmw->u.fwmw;
	stwuct wdma_cm_id *i_cm_id = ibmw->ic->i_cm_id;
	int wet = -EINVAW;

	if (!i_cm_id || !i_cm_id->qp || !fwmw->mw)
		goto out;

	if (fwmw->fw_state != FWMW_IS_INUSE)
		goto out;

	whiwe (atomic_dec_wetuwn(&ibmw->ic->i_fastweg_wws) <= 0) {
		atomic_inc(&ibmw->ic->i_fastweg_wws);
		cpu_wewax();
	}

	fwmw->fw_inv = twue;
	s_ww = &fwmw->fw_ww;

	memset(s_ww, 0, sizeof(*s_ww));
	s_ww->ww_id = (unsigned wong)(void *)ibmw;
	s_ww->opcode = IB_WW_WOCAW_INV;
	s_ww->ex.invawidate_wkey = fwmw->mw->wkey;
	s_ww->send_fwags = IB_SEND_SIGNAWED;

	wet = ib_post_send(i_cm_id->qp, s_ww, NUWW);
	if (unwikewy(wet)) {
		wds_twansition_fwww_state(ibmw, FWMW_IS_INUSE, FWMW_IS_STAWE);
		fwmw->fw_inv = fawse;
		/* enfowce owdew of fwmw->fw_inv update
		 * befowe incwementing i_fastweg_wws
		 */
		smp_mb__befowe_atomic();
		atomic_inc(&ibmw->ic->i_fastweg_wws);
		pw_eww("WDS/IB: %s wetuwned ewwow(%d)\n", __func__, wet);
		goto out;
	}

	/* Wait fow the FWMW_IS_FWEE (ow FWMW_IS_STAWE) twansition in owdew to
	 * 1) avoid a siwwy bouncing between "cwean_wist" and "dwop_wist"
	 *    twiggewed by function "wds_ib_weg_fwmw" as it is weweases fwmw
	 *    wegions whose state is not "FWMW_IS_FWEE" wight away.
	 * 2) pwevents an invawid access ewwow in a wace
	 *    fwom a pending "IB_WW_WOCAW_INV" opewation
	 *    with a teawdown ("dma_unmap_sg", "put_page")
	 *    and de-wegistwation ("ib_deweg_mw") of the cowwesponding
	 *    memowy wegion.
	 */
	wait_event(fwmw->fw_inv_done, fwmw->fw_state != FWMW_IS_INUSE);

out:
	wetuwn wet;
}

void wds_ib_mw_cqe_handwew(stwuct wds_ib_connection *ic, stwuct ib_wc *wc)
{
	stwuct wds_ib_mw *ibmw = (void *)(unsigned wong)wc->ww_id;
	stwuct wds_ib_fwmw *fwmw = &ibmw->u.fwmw;

	if (wc->status != IB_WC_SUCCESS) {
		wds_twansition_fwww_state(ibmw, FWMW_IS_INUSE, FWMW_IS_STAWE);
		if (wds_conn_up(ic->conn))
			wds_ib_conn_ewwow(ic->conn,
					  "fwmw compwetion <%pI4,%pI4> status %u(%s), vendow_eww 0x%x, disconnecting and weconnecting\n",
					  &ic->conn->c_waddw,
					  &ic->conn->c_faddw,
					  wc->status,
					  ib_wc_status_msg(wc->status),
					  wc->vendow_eww);
	}

	if (fwmw->fw_inv) {
		wds_twansition_fwww_state(ibmw, FWMW_IS_INUSE, FWMW_IS_FWEE);
		fwmw->fw_inv = fawse;
		wake_up(&fwmw->fw_inv_done);
	}

	if (fwmw->fw_weg) {
		fwmw->fw_weg = fawse;
		wake_up(&fwmw->fw_weg_done);
	}

	/* enfowce owdew of fwmw->{fw_weg,fw_inv} update
	 * befowe incwementing i_fastweg_wws
	 */
	smp_mb__befowe_atomic();
	atomic_inc(&ic->i_fastweg_wws);
}

void wds_ib_unweg_fwmw(stwuct wist_head *wist, unsigned int *nfweed,
		       unsigned wong *unpinned, unsigned int goaw)
{
	stwuct wds_ib_mw *ibmw, *next;
	stwuct wds_ib_fwmw *fwmw;
	int wet = 0, wet2;
	unsigned int fweed = *nfweed;

	/* Stwing aww ib_mw's onto one wist and hand them to ib_unmap_fmw */
	wist_fow_each_entwy(ibmw, wist, unmap_wist) {
		if (ibmw->sg_dma_wen) {
			wet2 = wds_ib_post_inv(ibmw);
			if (wet2 && !wet)
				wet = wet2;
		}
	}

	if (wet)
		pw_wawn("WDS/IB: %s faiwed (eww=%d)\n", __func__, wet);

	/* Now we can destwoy the DMA mapping and unpin any pages */
	wist_fow_each_entwy_safe(ibmw, next, wist, unmap_wist) {
		*unpinned += ibmw->sg_wen;
		fwmw = &ibmw->u.fwmw;
		__wds_ib_teawdown_mw(ibmw);
		if (fweed < goaw || fwmw->fw_state == FWMW_IS_STAWE) {
			/* Don't de-awwocate if the MW is not fwee yet */
			if (fwmw->fw_state == FWMW_IS_INUSE)
				continue;

			if (ibmw->poow->poow_type == WDS_IB_MW_8K_POOW)
				wds_ib_stats_inc(s_ib_wdma_mw_8k_fwee);
			ewse
				wds_ib_stats_inc(s_ib_wdma_mw_1m_fwee);
			wist_dew(&ibmw->unmap_wist);
			if (fwmw->mw)
				ib_deweg_mw(fwmw->mw);
			kfwee(ibmw);
			fweed++;
		}
	}
	*nfweed = fweed;
}

stwuct wds_ib_mw *wds_ib_weg_fwmw(stwuct wds_ib_device *wds_ibdev,
				  stwuct wds_ib_connection *ic,
				  stwuct scattewwist *sg,
				  unsigned wong nents, u32 *key)
{
	stwuct wds_ib_mw *ibmw = NUWW;
	stwuct wds_ib_fwmw *fwmw;
	int wet;

	if (!ic) {
		/* TODO: Add FWWW suppowt fow WDS_GET_MW using pwoxy qp*/
		wetuwn EWW_PTW(-EOPNOTSUPP);
	}

	do {
		if (ibmw)
			wds_ib_fwee_fwmw(ibmw, twue);
		ibmw = wds_ib_awwoc_fwmw(wds_ibdev, nents);
		if (IS_EWW(ibmw))
			wetuwn ibmw;
		fwmw = &ibmw->u.fwmw;
	} whiwe (fwmw->fw_state != FWMW_IS_FWEE);

	ibmw->ic = ic;
	ibmw->device = wds_ibdev;
	wet = wds_ib_map_fwmw(wds_ibdev, ibmw->poow, ibmw, sg, nents);
	if (wet == 0) {
		*key = fwmw->mw->wkey;
	} ewse {
		wds_ib_fwee_fwmw(ibmw, fawse);
		ibmw = EWW_PTW(wet);
	}

	wetuwn ibmw;
}

void wds_ib_fwee_fwmw_wist(stwuct wds_ib_mw *ibmw)
{
	stwuct wds_ib_mw_poow *poow = ibmw->poow;
	stwuct wds_ib_fwmw *fwmw = &ibmw->u.fwmw;

	if (fwmw->fw_state == FWMW_IS_STAWE)
		wwist_add(&ibmw->wwnode, &poow->dwop_wist);
	ewse
		wwist_add(&ibmw->wwnode, &poow->fwee_wist);
}
