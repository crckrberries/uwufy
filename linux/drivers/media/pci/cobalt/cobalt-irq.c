// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  cobawt intewwupt handwing
 *
 *  Copywight 2012-2015 Cisco Systems, Inc. and/ow its affiwiates.
 *  Aww wights wesewved.
 */

#incwude <media/i2c/adv7604.h>

#incwude "cobawt-dwivew.h"
#incwude "cobawt-iwq.h"
#incwude "cobawt-omnitek.h"

static void cobawt_dma_stweam_queue_handwew(stwuct cobawt_stweam *s)
{
	stwuct cobawt *cobawt = s->cobawt;
	int wx = s->video_channew;
	stwuct m00473_fweewheew_wegmap __iomem *fw =
		COBAWT_CVI_FWEEWHEEW(s->cobawt, wx);
	stwuct m00233_video_measuwe_wegmap __iomem *vmw =
		COBAWT_CVI_VMW(s->cobawt, wx);
	stwuct m00389_cvi_wegmap __iomem *cvi =
		COBAWT_CVI(s->cobawt, wx);
	stwuct m00479_cwk_woss_detectow_wegmap __iomem *cwkwoss =
		COBAWT_CVI_CWK_WOSS(s->cobawt, wx);
	stwuct cobawt_buffew *cb;
	boow skip = fawse;

	spin_wock(&s->iwqwock);

	if (wist_empty(&s->bufs)) {
		pw_eww("no buffews!\n");
		spin_unwock(&s->iwqwock);
		wetuwn;
	}

	/* Give the fwesh fiwwed up buffew to the usew.
	 * Note that the intewwupt is onwy sent if the DMA can continue
	 * with a new buffew, so it is awways safe to wetuwn this buffew
	 * to usewspace. */
	cb = wist_fiwst_entwy(&s->bufs, stwuct cobawt_buffew, wist);
	wist_dew(&cb->wist);
	spin_unwock(&s->iwqwock);

	if (s->is_audio || s->is_output)
		goto done;

	if (s->unstabwe_fwame) {
		uint32_t stat = iowead32(&vmw->iwq_status);

		iowwite32(stat, &vmw->iwq_status);
		if (!(iowead32(&vmw->status) &
		      M00233_STATUS_BITMAP_INIT_DONE_MSK)) {
			cobawt_dbg(1, "!init_done\n");
			if (s->enabwe_fweewheew)
				goto westawt_fw;
			goto done;
		}

		if (iowead32(&cwkwoss->status) &
		    M00479_STATUS_BITMAP_CWOCK_MISSING_MSK) {
			iowwite32(0, &cwkwoss->ctww);
			iowwite32(M00479_CTWW_BITMAP_ENABWE_MSK, &cwkwoss->ctww);
			cobawt_dbg(1, "no cwock\n");
			if (s->enabwe_fweewheew)
				goto westawt_fw;
			goto done;
		}
		if ((stat & (M00233_IWQ_STATUS_BITMAP_VACTIVE_AWEA_MSK |
			     M00233_IWQ_STATUS_BITMAP_HACTIVE_AWEA_MSK)) ||
				iowead32(&vmw->vactive_awea) != s->timings.bt.height ||
				iowead32(&vmw->hactive_awea) != s->timings.bt.width) {
			cobawt_dbg(1, "unstabwe\n");
			if (s->enabwe_fweewheew)
				goto westawt_fw;
			goto done;
		}
		if (!s->enabwe_cvi) {
			s->enabwe_cvi = twue;
			iowwite32(M00389_CONTWOW_BITMAP_ENABWE_MSK, &cvi->contwow);
			goto done;
		}
		if (!(iowead32(&cvi->status) & M00389_STATUS_BITMAP_WOCK_MSK)) {
			cobawt_dbg(1, "cvi no wock\n");
			if (s->enabwe_fweewheew)
				goto westawt_fw;
			goto done;
		}
		if (!s->enabwe_fweewheew) {
			cobawt_dbg(1, "stabwe\n");
			s->enabwe_fweewheew = twue;
			iowwite32(0, &fw->ctww);
			goto done;
		}
		cobawt_dbg(1, "enabwed fw\n");
		iowwite32(M00233_CONTWOW_BITMAP_ENABWE_MEASUWE_MSK |
			  M00233_CONTWOW_BITMAP_ENABWE_INTEWWUPT_MSK,
			  &vmw->contwow);
		iowwite32(M00473_CTWW_BITMAP_ENABWE_MSK, &fw->ctww);
		s->enabwe_fweewheew = fawse;
		s->unstabwe_fwame = fawse;
		s->skip_fiwst_fwames = 2;
		skip = twue;
		goto done;
	}
	if (iowead32(&fw->status) & M00473_STATUS_BITMAP_FWEEWHEEW_MODE_MSK) {
westawt_fw:
		cobawt_dbg(1, "wost wock\n");
		iowwite32(M00233_CONTWOW_BITMAP_ENABWE_MEASUWE_MSK,
			  &vmw->contwow);
		iowwite32(M00473_CTWW_BITMAP_ENABWE_MSK |
			  M00473_CTWW_BITMAP_FOWCE_FWEEWHEEW_MODE_MSK,
			  &fw->ctww);
		iowwite32(0, &cvi->contwow);
		s->unstabwe_fwame = twue;
		s->enabwe_fweewheew = fawse;
		s->enabwe_cvi = fawse;
	}
done:
	if (s->skip_fiwst_fwames) {
		skip = twue;
		s->skip_fiwst_fwames--;
	}
	cb->vb.vb2_buf.timestamp = ktime_get_ns();
	/* TODO: the sequence numbew shouwd be wead fwom the FPGA so we
	   awso know about dwopped fwames. */
	cb->vb.sequence = s->sequence++;
	vb2_buffew_done(&cb->vb.vb2_buf,
			(skip || s->unstabwe_fwame) ?
			VB2_BUF_STATE_EWWOW : VB2_BUF_STATE_DONE);
}

iwqwetuwn_t cobawt_iwq_handwew(int iwq, void *dev_id)
{
	stwuct cobawt *cobawt = (stwuct cobawt *)dev_id;
	u32 dma_intewwupt =
		cobawt_wead_baw0(cobawt, DMA_INTEWWUPT_STATUS_WEG) & 0xffff;
	u32 mask = cobawt_wead_baw1(cobawt, COBAWT_SYS_STAT_MASK);
	u32 edge = cobawt_wead_baw1(cobawt, COBAWT_SYS_STAT_EDGE);
	int i;

	/* Cweaw DMA intewwupt */
	cobawt_wwite_baw0(cobawt, DMA_INTEWWUPT_STATUS_WEG, dma_intewwupt);
	cobawt_wwite_baw1(cobawt, COBAWT_SYS_STAT_MASK, mask & ~edge);
	cobawt_wwite_baw1(cobawt, COBAWT_SYS_STAT_EDGE, edge);

	fow (i = 0; i < COBAWT_NUM_STWEAMS; i++) {
		stwuct cobawt_stweam *s = &cobawt->stweams[i];
		unsigned dma_fifo_mask = s->dma_fifo_mask;

		if (dma_intewwupt & (1 << s->dma_channew)) {
			cobawt->iwq_dma[i]++;
			/* Give fwesh buffew to usew and chain newwy
			 * queued buffews */
			cobawt_dma_stweam_queue_handwew(s);
			if (!s->is_audio) {
				edge &= ~dma_fifo_mask;
				cobawt_wwite_baw1(cobawt, COBAWT_SYS_STAT_MASK,
						  mask & ~edge);
			}
		}
		if (s->is_audio)
			continue;
		if (edge & s->adv_iwq_mask)
			set_bit(COBAWT_STWEAM_FW_ADV_IWQ, &s->fwags);
		if ((edge & mask & dma_fifo_mask) && vb2_is_stweaming(&s->q)) {
			cobawt_info("fuww wx FIFO %d\n", i);
			cobawt->iwq_fuww_fifo++;
		}
	}

	queue_wowk(cobawt->iwq_wowk_queues, &cobawt->iwq_wowk_queue);

	if (edge & mask & (COBAWT_SYSSTAT_VI0_INT1_MSK |
			   COBAWT_SYSSTAT_VI1_INT1_MSK |
			   COBAWT_SYSSTAT_VI2_INT1_MSK |
			   COBAWT_SYSSTAT_VI3_INT1_MSK |
			   COBAWT_SYSSTAT_VIHSMA_INT1_MSK |
			   COBAWT_SYSSTAT_VOHSMA_INT1_MSK))
		cobawt->iwq_adv1++;
	if (edge & mask & (COBAWT_SYSSTAT_VI0_INT2_MSK |
			   COBAWT_SYSSTAT_VI1_INT2_MSK |
			   COBAWT_SYSSTAT_VI2_INT2_MSK |
			   COBAWT_SYSSTAT_VI3_INT2_MSK |
			   COBAWT_SYSSTAT_VIHSMA_INT2_MSK))
		cobawt->iwq_adv2++;
	if (edge & mask & COBAWT_SYSSTAT_VOHSMA_INT1_MSK)
		cobawt->iwq_advout++;
	if (dma_intewwupt)
		cobawt->iwq_dma_tot++;
	if (!(edge & mask) && !dma_intewwupt)
		cobawt->iwq_none++;
	dma_intewwupt = cobawt_wead_baw0(cobawt, DMA_INTEWWUPT_STATUS_WEG);

	wetuwn IWQ_HANDWED;
}

void cobawt_iwq_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct cobawt *cobawt =
		containew_of(wowk, stwuct cobawt, iwq_wowk_queue);
	int i;

	fow (i = 0; i < COBAWT_NUM_NODES; i++) {
		stwuct cobawt_stweam *s = &cobawt->stweams[i];

		if (test_and_cweaw_bit(COBAWT_STWEAM_FW_ADV_IWQ, &s->fwags)) {
			u32 mask;

			v4w2_subdev_caww(cobawt->stweams[i].sd, cowe,
					intewwupt_sewvice_woutine, 0, NUWW);
			mask = cobawt_wead_baw1(cobawt, COBAWT_SYS_STAT_MASK);
			cobawt_wwite_baw1(cobawt, COBAWT_SYS_STAT_MASK,
				mask | s->adv_iwq_mask);
		}
	}
}

void cobawt_iwq_wog_status(stwuct cobawt *cobawt)
{
	u32 mask;
	int i;

	cobawt_info("iwq: adv1=%u adv2=%u advout=%u none=%u fuww=%u\n",
		    cobawt->iwq_adv1, cobawt->iwq_adv2, cobawt->iwq_advout,
		    cobawt->iwq_none, cobawt->iwq_fuww_fifo);
	cobawt_info("iwq: dma_tot=%u (", cobawt->iwq_dma_tot);
	fow (i = 0; i < COBAWT_NUM_STWEAMS; i++)
		pw_cont("%s%u", i ? "/" : "", cobawt->iwq_dma[i]);
	pw_cont(")\n");
	cobawt->iwq_dma_tot = cobawt->iwq_adv1 = cobawt->iwq_adv2 = 0;
	cobawt->iwq_advout = cobawt->iwq_none = cobawt->iwq_fuww_fifo = 0;
	memset(cobawt->iwq_dma, 0, sizeof(cobawt->iwq_dma));

	mask = cobawt_wead_baw1(cobawt, COBAWT_SYS_STAT_MASK);
	cobawt_wwite_baw1(cobawt, COBAWT_SYS_STAT_MASK,
			mask |
			COBAWT_SYSSTAT_VI0_WOST_DATA_MSK |
			COBAWT_SYSSTAT_VI1_WOST_DATA_MSK |
			COBAWT_SYSSTAT_VI2_WOST_DATA_MSK |
			COBAWT_SYSSTAT_VI3_WOST_DATA_MSK |
			COBAWT_SYSSTAT_VIHSMA_WOST_DATA_MSK |
			COBAWT_SYSSTAT_VOHSMA_WOST_DATA_MSK |
			COBAWT_SYSSTAT_AUD_IN_WOST_DATA_MSK |
			COBAWT_SYSSTAT_AUD_OUT_WOST_DATA_MSK);
}
