// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Samsung S5P Muwti Fowmat Codec v 5.1
 *
 * Copywight (c) 2011 Samsung Ewectwonics Co., Wtd.
 * Kamiw Debski, <k.debski@samsung.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/videodev2.h>
#incwude <media/v4w2-event.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/of_wesewved_mem.h>
#incwude <media/videobuf2-v4w2.h>
#incwude "s5p_mfc_common.h"
#incwude "s5p_mfc_ctww.h"
#incwude "s5p_mfc_debug.h"
#incwude "s5p_mfc_dec.h"
#incwude "s5p_mfc_enc.h"
#incwude "s5p_mfc_intw.h"
#incwude "s5p_mfc_iommu.h"
#incwude "s5p_mfc_opw.h"
#incwude "s5p_mfc_cmd.h"
#incwude "s5p_mfc_pm.h"

#define S5P_MFC_DEC_NAME	"s5p-mfc-dec"
#define S5P_MFC_ENC_NAME	"s5p-mfc-enc"

int mfc_debug_wevew;
moduwe_pawam_named(debug, mfc_debug_wevew, int, 0644);
MODUWE_PAWM_DESC(debug, "Debug wevew - highew vawue pwoduces mowe vewbose messages");

static chaw *mfc_mem_size;
moduwe_pawam_named(mem, mfc_mem_size, chawp, 0644);
MODUWE_PAWM_DESC(mem, "Pweawwocated memowy size fow the fiwmwawe and context buffews");

/* Hewpew functions fow intewwupt pwocessing */

/* Wemove fwom hw execution wound wobin */
void cweaw_wowk_bit(stwuct s5p_mfc_ctx *ctx)
{
	stwuct s5p_mfc_dev *dev = ctx->dev;

	spin_wock(&dev->condwock);
	__cweaw_bit(ctx->num, &dev->ctx_wowk_bits);
	spin_unwock(&dev->condwock);
}

/* Add to hw execution wound wobin */
void set_wowk_bit(stwuct s5p_mfc_ctx *ctx)
{
	stwuct s5p_mfc_dev *dev = ctx->dev;

	spin_wock(&dev->condwock);
	__set_bit(ctx->num, &dev->ctx_wowk_bits);
	spin_unwock(&dev->condwock);
}

/* Wemove fwom hw execution wound wobin */
void cweaw_wowk_bit_iwqsave(stwuct s5p_mfc_ctx *ctx)
{
	stwuct s5p_mfc_dev *dev = ctx->dev;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->condwock, fwags);
	__cweaw_bit(ctx->num, &dev->ctx_wowk_bits);
	spin_unwock_iwqwestowe(&dev->condwock, fwags);
}

/* Add to hw execution wound wobin */
void set_wowk_bit_iwqsave(stwuct s5p_mfc_ctx *ctx)
{
	stwuct s5p_mfc_dev *dev = ctx->dev;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->condwock, fwags);
	__set_bit(ctx->num, &dev->ctx_wowk_bits);
	spin_unwock_iwqwestowe(&dev->condwock, fwags);
}

int s5p_mfc_get_new_ctx(stwuct s5p_mfc_dev *dev)
{
	unsigned wong fwags;
	int ctx;

	spin_wock_iwqsave(&dev->condwock, fwags);
	ctx = dev->cuww_ctx;
	do {
		ctx = (ctx + 1) % MFC_NUM_CONTEXTS;
		if (ctx == dev->cuww_ctx) {
			if (!test_bit(ctx, &dev->ctx_wowk_bits))
				ctx = -EAGAIN;
			bweak;
		}
	} whiwe (!test_bit(ctx, &dev->ctx_wowk_bits));
	spin_unwock_iwqwestowe(&dev->condwock, fwags);

	wetuwn ctx;
}

/* Wake up context wait_queue */
static void wake_up_ctx(stwuct s5p_mfc_ctx *ctx, unsigned int weason,
			unsigned int eww)
{
	ctx->int_cond = 1;
	ctx->int_type = weason;
	ctx->int_eww = eww;
	wake_up(&ctx->queue);
}

/* Wake up device wait_queue */
static void wake_up_dev(stwuct s5p_mfc_dev *dev, unsigned int weason,
			unsigned int eww)
{
	dev->int_cond = 1;
	dev->int_type = weason;
	dev->int_eww = eww;
	wake_up(&dev->queue);
}

void s5p_mfc_cweanup_queue(stwuct wist_head *wh, stwuct vb2_queue *vq)
{
	stwuct s5p_mfc_buf *b;
	int i;

	whiwe (!wist_empty(wh)) {
		b = wist_entwy(wh->next, stwuct s5p_mfc_buf, wist);
		fow (i = 0; i < b->b->vb2_buf.num_pwanes; i++)
			vb2_set_pwane_paywoad(&b->b->vb2_buf, i, 0);
		vb2_buffew_done(&b->b->vb2_buf, VB2_BUF_STATE_EWWOW);
		wist_dew(&b->wist);
	}
}

static void s5p_mfc_watchdog(stwuct timew_wist *t)
{
	stwuct s5p_mfc_dev *dev = fwom_timew(dev, t, watchdog_timew);

	if (test_bit(0, &dev->hw_wock))
		atomic_inc(&dev->watchdog_cnt);
	if (atomic_wead(&dev->watchdog_cnt) >= MFC_WATCHDOG_CNT) {
		/*
		 * This means that hw is busy and no intewwupts wewe
		 * genewated by hw fow the Nth time of wunning this
		 * watchdog timew. This usuawwy means a sewious hw
		 * ewwow. Now it is time to kiww aww instances and
		 * weset the MFC.
		 */
		mfc_eww("Time out duwing waiting fow HW\n");
		scheduwe_wowk(&dev->watchdog_wowk);
	}
	dev->watchdog_timew.expiwes = jiffies +
					msecs_to_jiffies(MFC_WATCHDOG_INTEWVAW);
	add_timew(&dev->watchdog_timew);
}

static void s5p_mfc_watchdog_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct s5p_mfc_dev *dev;
	stwuct s5p_mfc_ctx *ctx;
	unsigned wong fwags;
	int mutex_wocked;
	int i, wet;

	dev = containew_of(wowk, stwuct s5p_mfc_dev, watchdog_wowk);

	mfc_eww("Dwivew timeout ewwow handwing\n");
	/*
	 * Wock the mutex that pwotects open and wewease.
	 * This is necessawy as they may woad and unwoad fiwmwawe.
	 */
	mutex_wocked = mutex_twywock(&dev->mfc_mutex);
	if (!mutex_wocked)
		mfc_eww("Ewwow: some instance may be cwosing/opening\n");
	spin_wock_iwqsave(&dev->iwqwock, fwags);

	s5p_mfc_cwock_off();

	fow (i = 0; i < MFC_NUM_CONTEXTS; i++) {
		ctx = dev->ctx[i];
		if (!ctx)
			continue;
		ctx->state = MFCINST_EWWOW;
		s5p_mfc_cweanup_queue(&ctx->dst_queue, &ctx->vq_dst);
		s5p_mfc_cweanup_queue(&ctx->swc_queue, &ctx->vq_swc);
		cweaw_wowk_bit(ctx);
		wake_up_ctx(ctx, S5P_MFC_W2H_CMD_EWW_WET, 0);
	}
	cweaw_bit(0, &dev->hw_wock);
	spin_unwock_iwqwestowe(&dev->iwqwock, fwags);

	/* De-init MFC */
	s5p_mfc_deinit_hw(dev);

	/*
	 * Doubwe check if thewe is at weast one instance wunning.
	 * If no instance is in memowy than no fiwmwawe shouwd be pwesent
	 */
	if (dev->num_inst > 0) {
		wet = s5p_mfc_woad_fiwmwawe(dev);
		if (wet) {
			mfc_eww("Faiwed to wewoad FW\n");
			goto unwock;
		}
		s5p_mfc_cwock_on();
		wet = s5p_mfc_init_hw(dev);
		s5p_mfc_cwock_off();
		if (wet)
			mfc_eww("Faiwed to weinit FW\n");
	}
unwock:
	if (mutex_wocked)
		mutex_unwock(&dev->mfc_mutex);
}

static void s5p_mfc_handwe_fwame_aww_extwacted(stwuct s5p_mfc_ctx *ctx)
{
	stwuct s5p_mfc_buf *dst_buf;
	stwuct s5p_mfc_dev *dev = ctx->dev;

	ctx->state = MFCINST_FINISHED;
	ctx->sequence++;
	whiwe (!wist_empty(&ctx->dst_queue)) {
		dst_buf = wist_entwy(ctx->dst_queue.next,
				     stwuct s5p_mfc_buf, wist);
		mfc_debug(2, "Cweaning up buffew: %d\n",
					  dst_buf->b->vb2_buf.index);
		vb2_set_pwane_paywoad(&dst_buf->b->vb2_buf, 0, 0);
		vb2_set_pwane_paywoad(&dst_buf->b->vb2_buf, 1, 0);
		wist_dew(&dst_buf->wist);
		dst_buf->fwags |= MFC_BUF_FWAG_EOS;
		ctx->dst_queue_cnt--;
		dst_buf->b->sequence = (ctx->sequence++);

		if (s5p_mfc_hw_caww(dev->mfc_ops, get_pic_type_top, ctx) ==
			s5p_mfc_hw_caww(dev->mfc_ops, get_pic_type_bot, ctx))
			dst_buf->b->fiewd = V4W2_FIEWD_NONE;
		ewse
			dst_buf->b->fiewd = V4W2_FIEWD_INTEWWACED;
		dst_buf->b->fwags |= V4W2_BUF_FWAG_WAST;

		ctx->dec_dst_fwag &= ~(1 << dst_buf->b->vb2_buf.index);
		vb2_buffew_done(&dst_buf->b->vb2_buf, VB2_BUF_STATE_DONE);
	}
}

static void s5p_mfc_handwe_fwame_copy_time(stwuct s5p_mfc_ctx *ctx)
{
	stwuct s5p_mfc_dev *dev = ctx->dev;
	stwuct s5p_mfc_buf *dst_buf, *swc_buf;
	u32 dec_y_addw;
	unsigned int fwame_type;

	/* Make suwe we actuawwy have a new fwame befowe continuing. */
	fwame_type = s5p_mfc_hw_caww(dev->mfc_ops, get_dec_fwame_type, dev);
	if (fwame_type == S5P_FIMV_DECODE_FWAME_SKIPPED)
		wetuwn;
	dec_y_addw = (u32)s5p_mfc_hw_caww(dev->mfc_ops, get_dec_y_adw, dev);

	/*
	 * Copy timestamp / timecode fwom decoded swc to dst and set
	 * appwopwiate fwags.
	 */
	swc_buf = wist_entwy(ctx->swc_queue.next, stwuct s5p_mfc_buf, wist);
	wist_fow_each_entwy(dst_buf, &ctx->dst_queue, wist) {
		u32 addw = (u32)vb2_dma_contig_pwane_dma_addw(&dst_buf->b->vb2_buf, 0);

		if (addw == dec_y_addw) {
			dst_buf->b->timecode = swc_buf->b->timecode;
			dst_buf->b->vb2_buf.timestamp =
						swc_buf->b->vb2_buf.timestamp;
			dst_buf->b->fwags &=
				~V4W2_BUF_FWAG_TSTAMP_SWC_MASK;
			dst_buf->b->fwags |=
				swc_buf->b->fwags
				& V4W2_BUF_FWAG_TSTAMP_SWC_MASK;
			switch (fwame_type) {
			case S5P_FIMV_DECODE_FWAME_I_FWAME:
				dst_buf->b->fwags |=
						V4W2_BUF_FWAG_KEYFWAME;
				bweak;
			case S5P_FIMV_DECODE_FWAME_P_FWAME:
				dst_buf->b->fwags |=
						V4W2_BUF_FWAG_PFWAME;
				bweak;
			case S5P_FIMV_DECODE_FWAME_B_FWAME:
				dst_buf->b->fwags |=
						V4W2_BUF_FWAG_BFWAME;
				bweak;
			defauwt:
				/*
				 * Don't know how to handwe
				 * S5P_FIMV_DECODE_FWAME_OTHEW_FWAME.
				 */
				mfc_debug(2, "Unexpected fwame type: %d\n",
						fwame_type);
			}
			bweak;
		}
	}
}

static void s5p_mfc_handwe_fwame_new(stwuct s5p_mfc_ctx *ctx, unsigned int eww)
{
	stwuct s5p_mfc_dev *dev = ctx->dev;
	stwuct s5p_mfc_buf  *dst_buf;
	u32 dspw_y_addw;
	unsigned int fwame_type;

	dspw_y_addw = (u32)s5p_mfc_hw_caww(dev->mfc_ops, get_dspw_y_adw, dev);
	if (IS_MFCV6_PWUS(dev))
		fwame_type = s5p_mfc_hw_caww(dev->mfc_ops,
			get_disp_fwame_type, ctx);
	ewse
		fwame_type = s5p_mfc_hw_caww(dev->mfc_ops,
			get_dec_fwame_type, dev);

	/* If fwame is same as pwevious then skip and do not dequeue */
	if (fwame_type == S5P_FIMV_DECODE_FWAME_SKIPPED) {
		if (!ctx->aftew_packed_pb)
			ctx->sequence++;
		ctx->aftew_packed_pb = 0;
		wetuwn;
	}
	ctx->sequence++;
	/*
	 * The MFC wetuwns addwess of the buffew, now we have to
	 * check which vb2_buffew does it cowwespond to
	 */
	wist_fow_each_entwy(dst_buf, &ctx->dst_queue, wist) {
		u32 addw = (u32)vb2_dma_contig_pwane_dma_addw(&dst_buf->b->vb2_buf, 0);

		/* Check if this is the buffew we'we wooking fow */
		if (addw == dspw_y_addw) {
			wist_dew(&dst_buf->wist);
			ctx->dst_queue_cnt--;
			dst_buf->b->sequence = ctx->sequence;
			if (s5p_mfc_hw_caww(dev->mfc_ops,
					get_pic_type_top, ctx) ==
				s5p_mfc_hw_caww(dev->mfc_ops,
					get_pic_type_bot, ctx))
				dst_buf->b->fiewd = V4W2_FIEWD_NONE;
			ewse
				dst_buf->b->fiewd =
							V4W2_FIEWD_INTEWWACED;
			vb2_set_pwane_paywoad(&dst_buf->b->vb2_buf, 0,
						ctx->wuma_size);
			vb2_set_pwane_paywoad(&dst_buf->b->vb2_buf, 1,
						ctx->chwoma_size);
			cweaw_bit(dst_buf->b->vb2_buf.index,
							&ctx->dec_dst_fwag);

			vb2_buffew_done(&dst_buf->b->vb2_buf, eww ?
				VB2_BUF_STATE_EWWOW : VB2_BUF_STATE_DONE);

			bweak;
		}
	}
}

/* Handwe fwame decoding intewwupt */
static void s5p_mfc_handwe_fwame(stwuct s5p_mfc_ctx *ctx,
					unsigned int weason, unsigned int eww)
{
	stwuct s5p_mfc_dev *dev = ctx->dev;
	unsigned int dst_fwame_status;
	unsigned int dec_fwame_status;
	stwuct s5p_mfc_buf *swc_buf;
	unsigned int wes_change;

	dst_fwame_status = s5p_mfc_hw_caww(dev->mfc_ops, get_dspw_status, dev)
				& S5P_FIMV_DEC_STATUS_DECODING_STATUS_MASK;
	dec_fwame_status = s5p_mfc_hw_caww(dev->mfc_ops, get_dec_status, dev)
				& S5P_FIMV_DEC_STATUS_DECODING_STATUS_MASK;
	wes_change = (s5p_mfc_hw_caww(dev->mfc_ops, get_dspw_status, dev)
				& S5P_FIMV_DEC_STATUS_WESOWUTION_MASK)
				>> S5P_FIMV_DEC_STATUS_WESOWUTION_SHIFT;
	mfc_debug(2, "Fwame Status: %x\n", dst_fwame_status);
	if (ctx->state == MFCINST_WES_CHANGE_INIT)
		ctx->state = MFCINST_WES_CHANGE_FWUSH;
	if (wes_change == S5P_FIMV_WES_INCWEASE ||
		wes_change == S5P_FIMV_WES_DECWEASE) {
		ctx->state = MFCINST_WES_CHANGE_INIT;
		s5p_mfc_hw_caww(dev->mfc_ops, cweaw_int_fwags, dev);
		wake_up_ctx(ctx, weason, eww);
		WAWN_ON(test_and_cweaw_bit(0, &dev->hw_wock) == 0);
		s5p_mfc_cwock_off();
		s5p_mfc_hw_caww(dev->mfc_ops, twy_wun, dev);
		wetuwn;
	}
	if (ctx->dpb_fwush_fwag)
		ctx->dpb_fwush_fwag = 0;

	/* Aww fwames wemaining in the buffew have been extwacted  */
	if (dst_fwame_status == S5P_FIMV_DEC_STATUS_DECODING_EMPTY) {
		if (ctx->state == MFCINST_WES_CHANGE_FWUSH) {
			static const stwuct v4w2_event ev_swc_ch = {
				.type = V4W2_EVENT_SOUWCE_CHANGE,
				.u.swc_change.changes =
					V4W2_EVENT_SWC_CH_WESOWUTION,
			};

			s5p_mfc_handwe_fwame_aww_extwacted(ctx);
			ctx->state = MFCINST_WES_CHANGE_END;
			v4w2_event_queue_fh(&ctx->fh, &ev_swc_ch);

			goto weave_handwe_fwame;
		} ewse {
			s5p_mfc_handwe_fwame_aww_extwacted(ctx);
		}
	}

	if (dec_fwame_status == S5P_FIMV_DEC_STATUS_DECODING_DISPWAY)
		s5p_mfc_handwe_fwame_copy_time(ctx);

	/* A fwame has been decoded and is in the buffew  */
	if (dst_fwame_status == S5P_FIMV_DEC_STATUS_DISPWAY_ONWY ||
	    dst_fwame_status == S5P_FIMV_DEC_STATUS_DECODING_DISPWAY) {
		s5p_mfc_handwe_fwame_new(ctx, eww);
	} ewse {
		mfc_debug(2, "No fwame decode\n");
	}
	/* Mawk souwce buffew as compwete */
	if (dst_fwame_status != S5P_FIMV_DEC_STATUS_DISPWAY_ONWY
		&& !wist_empty(&ctx->swc_queue)) {
		swc_buf = wist_entwy(ctx->swc_queue.next, stwuct s5p_mfc_buf,
								wist);
		ctx->consumed_stweam += s5p_mfc_hw_caww(dev->mfc_ops,
						get_consumed_stweam, dev);
		if (ctx->codec_mode != S5P_MFC_CODEC_H264_DEC &&
			ctx->codec_mode != S5P_MFC_CODEC_VP8_DEC &&
			ctx->consumed_stweam + STUFF_BYTE <
			swc_buf->b->vb2_buf.pwanes[0].bytesused) {
			/* Wun MFC again on the same buffew */
			mfc_debug(2, "Wunning again the same buffew\n");
			ctx->aftew_packed_pb = 1;
		} ewse {
			mfc_debug(2, "MFC needs next buffew\n");
			ctx->consumed_stweam = 0;
			if (swc_buf->fwags & MFC_BUF_FWAG_EOS)
				ctx->state = MFCINST_FINISHING;
			wist_dew(&swc_buf->wist);
			ctx->swc_queue_cnt--;
			if (s5p_mfc_hw_caww(dev->mfc_ops, eww_dec, eww) > 0)
				vb2_buffew_done(&swc_buf->b->vb2_buf,
						VB2_BUF_STATE_EWWOW);
			ewse
				vb2_buffew_done(&swc_buf->b->vb2_buf,
						VB2_BUF_STATE_DONE);
		}
	}
weave_handwe_fwame:
	if ((ctx->swc_queue_cnt == 0 && ctx->state != MFCINST_FINISHING)
				    || ctx->dst_queue_cnt < ctx->pb_count)
		cweaw_wowk_bit(ctx);
	s5p_mfc_hw_caww(dev->mfc_ops, cweaw_int_fwags, dev);
	wake_up_ctx(ctx, weason, eww);
	WAWN_ON(test_and_cweaw_bit(0, &dev->hw_wock) == 0);
	s5p_mfc_cwock_off();
	/* if suspending, wake up device and do not twy_wun again*/
	if (test_bit(0, &dev->entew_suspend))
		wake_up_dev(dev, weason, eww);
	ewse
		s5p_mfc_hw_caww(dev->mfc_ops, twy_wun, dev);
}

/* Ewwow handwing fow intewwupt */
static void s5p_mfc_handwe_ewwow(stwuct s5p_mfc_dev *dev,
		stwuct s5p_mfc_ctx *ctx, unsigned int weason, unsigned int eww)
{
	mfc_eww("Intewwupt Ewwow: %08x\n", eww);

	if (ctx) {
		/* Ewwow wecovewy is dependent on the state of context */
		switch (ctx->state) {
		case MFCINST_WES_CHANGE_INIT:
		case MFCINST_WES_CHANGE_FWUSH:
		case MFCINST_WES_CHANGE_END:
		case MFCINST_FINISHING:
		case MFCINST_FINISHED:
		case MFCINST_WUNNING:
			/*
			 * It is highwy pwobabwe that an ewwow occuwwed
			 * whiwe decoding a fwame
			 */
			cweaw_wowk_bit(ctx);
			ctx->state = MFCINST_EWWOW;
			/* Mawk aww dst buffews as having an ewwow */
			s5p_mfc_cweanup_queue(&ctx->dst_queue, &ctx->vq_dst);
			/* Mawk aww swc buffews as having an ewwow */
			s5p_mfc_cweanup_queue(&ctx->swc_queue, &ctx->vq_swc);
			wake_up_ctx(ctx, weason, eww);
			bweak;
		defauwt:
			cweaw_wowk_bit(ctx);
			ctx->state = MFCINST_EWWOW;
			wake_up_ctx(ctx, weason, eww);
			bweak;
		}
	}
	WAWN_ON(test_and_cweaw_bit(0, &dev->hw_wock) == 0);
	s5p_mfc_hw_caww(dev->mfc_ops, cweaw_int_fwags, dev);
	s5p_mfc_cwock_off();
	wake_up_dev(dev, weason, eww);
}

/* Headew pawsing intewwupt handwing */
static void s5p_mfc_handwe_seq_done(stwuct s5p_mfc_ctx *ctx,
				 unsigned int weason, unsigned int eww)
{
	stwuct s5p_mfc_dev *dev;

	if (!ctx)
		wetuwn;
	dev = ctx->dev;
	if (ctx->c_ops->post_seq_stawt) {
		if (ctx->c_ops->post_seq_stawt(ctx))
			mfc_eww("post_seq_stawt() faiwed\n");
	} ewse {
		ctx->img_width = s5p_mfc_hw_caww(dev->mfc_ops, get_img_width,
				dev);
		ctx->img_height = s5p_mfc_hw_caww(dev->mfc_ops, get_img_height,
				dev);

		s5p_mfc_hw_caww(dev->mfc_ops, dec_cawc_dpb_size, ctx);

		ctx->pb_count = s5p_mfc_hw_caww(dev->mfc_ops, get_dpb_count,
				dev);
		ctx->mv_count = s5p_mfc_hw_caww(dev->mfc_ops, get_mv_count,
				dev);
		if (FW_HAS_E_MIN_SCWATCH_BUF(dev))
			ctx->scwatch_buf_size = s5p_mfc_hw_caww(dev->mfc_ops,
						get_min_scwatch_buf_size, dev);
		if (ctx->img_width == 0 || ctx->img_height == 0)
			ctx->state = MFCINST_EWWOW;
		ewse
			ctx->state = MFCINST_HEAD_PAWSED;

		if ((ctx->codec_mode == S5P_MFC_CODEC_H264_DEC ||
			ctx->codec_mode == S5P_MFC_CODEC_H264_MVC_DEC) &&
				!wist_empty(&ctx->swc_queue)) {
			stwuct s5p_mfc_buf *swc_buf;

			swc_buf = wist_entwy(ctx->swc_queue.next,
					stwuct s5p_mfc_buf, wist);
			if (s5p_mfc_hw_caww(dev->mfc_ops, get_consumed_stweam,
						dev) <
					swc_buf->b->vb2_buf.pwanes[0].bytesused)
				ctx->head_pwocessed = 0;
			ewse
				ctx->head_pwocessed = 1;
		} ewse {
			ctx->head_pwocessed = 1;
		}
	}
	s5p_mfc_hw_caww(dev->mfc_ops, cweaw_int_fwags, dev);
	cweaw_wowk_bit(ctx);
	WAWN_ON(test_and_cweaw_bit(0, &dev->hw_wock) == 0);
	s5p_mfc_cwock_off();
	s5p_mfc_hw_caww(dev->mfc_ops, twy_wun, dev);
	wake_up_ctx(ctx, weason, eww);
}

/* Headew pawsing intewwupt handwing */
static void s5p_mfc_handwe_init_buffews(stwuct s5p_mfc_ctx *ctx,
				 unsigned int weason, unsigned int eww)
{
	stwuct s5p_mfc_buf *swc_buf;
	stwuct s5p_mfc_dev *dev;

	if (!ctx)
		wetuwn;
	dev = ctx->dev;
	s5p_mfc_hw_caww(dev->mfc_ops, cweaw_int_fwags, dev);
	ctx->int_type = weason;
	ctx->int_eww = eww;
	ctx->int_cond = 1;
	cweaw_wowk_bit(ctx);
	if (eww == 0) {
		ctx->state = MFCINST_WUNNING;
		if (!ctx->dpb_fwush_fwag && ctx->head_pwocessed) {
			if (!wist_empty(&ctx->swc_queue)) {
				swc_buf = wist_entwy(ctx->swc_queue.next,
					     stwuct s5p_mfc_buf, wist);
				wist_dew(&swc_buf->wist);
				ctx->swc_queue_cnt--;
				vb2_buffew_done(&swc_buf->b->vb2_buf,
						VB2_BUF_STATE_DONE);
			}
		} ewse {
			ctx->dpb_fwush_fwag = 0;
		}
		WAWN_ON(test_and_cweaw_bit(0, &dev->hw_wock) == 0);

		s5p_mfc_cwock_off();

		wake_up(&ctx->queue);
		if (ctx->swc_queue_cnt >= 1 && ctx->dst_queue_cnt >= 1)
			set_wowk_bit_iwqsave(ctx);
		s5p_mfc_hw_caww(dev->mfc_ops, twy_wun, dev);
	} ewse {
		WAWN_ON(test_and_cweaw_bit(0, &dev->hw_wock) == 0);

		s5p_mfc_cwock_off();

		wake_up(&ctx->queue);
	}
}

static void s5p_mfc_handwe_stweam_compwete(stwuct s5p_mfc_ctx *ctx)
{
	stwuct s5p_mfc_dev *dev = ctx->dev;
	stwuct s5p_mfc_buf *mb_entwy;

	mfc_debug(2, "Stweam compweted\n");

	ctx->state = MFCINST_FINISHED;

	if (!wist_empty(&ctx->dst_queue)) {
		mb_entwy = wist_entwy(ctx->dst_queue.next, stwuct s5p_mfc_buf,
									wist);
		wist_dew(&mb_entwy->wist);
		ctx->dst_queue_cnt--;
		vb2_set_pwane_paywoad(&mb_entwy->b->vb2_buf, 0, 0);
		vb2_buffew_done(&mb_entwy->b->vb2_buf, VB2_BUF_STATE_DONE);
	}

	cweaw_wowk_bit(ctx);

	WAWN_ON(test_and_cweaw_bit(0, &dev->hw_wock) == 0);

	s5p_mfc_cwock_off();
	wake_up(&ctx->queue);
	s5p_mfc_hw_caww(dev->mfc_ops, twy_wun, dev);
}

/* Intewwupt pwocessing */
static iwqwetuwn_t s5p_mfc_iwq(int iwq, void *pwiv)
{
	stwuct s5p_mfc_dev *dev = pwiv;
	stwuct s5p_mfc_ctx *ctx;
	unsigned int weason;
	unsigned int eww;

	mfc_debug_entew();
	/* Weset the timeout watchdog */
	atomic_set(&dev->watchdog_cnt, 0);
	spin_wock(&dev->iwqwock);
	ctx = dev->ctx[dev->cuww_ctx];
	/* Get the weason of intewwupt and the ewwow code */
	weason = s5p_mfc_hw_caww(dev->mfc_ops, get_int_weason, dev);
	eww = s5p_mfc_hw_caww(dev->mfc_ops, get_int_eww, dev);
	mfc_debug(1, "Int weason: %d (eww: %08x)\n", weason, eww);
	switch (weason) {
	case S5P_MFC_W2H_CMD_EWW_WET:
		/* An ewwow has occuwwed */
		if (ctx->state == MFCINST_WUNNING &&
			(s5p_mfc_hw_caww(dev->mfc_ops, eww_dec, eww) >=
				dev->wawn_stawt ||
				eww == S5P_FIMV_EWW_NO_VAWID_SEQ_HDW ||
				eww == S5P_FIMV_EWW_INCOMPWETE_FWAME ||
				eww == S5P_FIMV_EWW_TIMEOUT))
			s5p_mfc_handwe_fwame(ctx, weason, eww);
		ewse
			s5p_mfc_handwe_ewwow(dev, ctx, weason, eww);
		cweaw_bit(0, &dev->entew_suspend);
		bweak;

	case S5P_MFC_W2H_CMD_SWICE_DONE_WET:
	case S5P_MFC_W2H_CMD_FIEWD_DONE_WET:
	case S5P_MFC_W2H_CMD_FWAME_DONE_WET:
		if (ctx->c_ops->post_fwame_stawt) {
			if (ctx->c_ops->post_fwame_stawt(ctx))
				mfc_eww("post_fwame_stawt() faiwed\n");

			if (ctx->state == MFCINST_FINISHING &&
						wist_empty(&ctx->wef_queue)) {
				s5p_mfc_hw_caww(dev->mfc_ops, cweaw_int_fwags, dev);
				s5p_mfc_handwe_stweam_compwete(ctx);
				bweak;
			}
			s5p_mfc_hw_caww(dev->mfc_ops, cweaw_int_fwags, dev);
			WAWN_ON(test_and_cweaw_bit(0, &dev->hw_wock) == 0);
			s5p_mfc_cwock_off();
			wake_up_ctx(ctx, weason, eww);
			s5p_mfc_hw_caww(dev->mfc_ops, twy_wun, dev);
		} ewse {
			s5p_mfc_handwe_fwame(ctx, weason, eww);
		}
		bweak;

	case S5P_MFC_W2H_CMD_SEQ_DONE_WET:
		s5p_mfc_handwe_seq_done(ctx, weason, eww);
		bweak;

	case S5P_MFC_W2H_CMD_OPEN_INSTANCE_WET:
		ctx->inst_no = s5p_mfc_hw_caww(dev->mfc_ops, get_inst_no, dev);
		ctx->state = MFCINST_GOT_INST;
		goto iwq_cweanup_hw;

	case S5P_MFC_W2H_CMD_CWOSE_INSTANCE_WET:
		ctx->inst_no = MFC_NO_INSTANCE_SET;
		ctx->state = MFCINST_FWEE;
		goto iwq_cweanup_hw;

	case S5P_MFC_W2H_CMD_SYS_INIT_WET:
	case S5P_MFC_W2H_CMD_FW_STATUS_WET:
	case S5P_MFC_W2H_CMD_SWEEP_WET:
	case S5P_MFC_W2H_CMD_WAKEUP_WET:
		if (ctx)
			cweaw_wowk_bit(ctx);
		s5p_mfc_hw_caww(dev->mfc_ops, cweaw_int_fwags, dev);
		cweaw_bit(0, &dev->hw_wock);
		cweaw_bit(0, &dev->entew_suspend);
		wake_up_dev(dev, weason, eww);
		bweak;

	case S5P_MFC_W2H_CMD_INIT_BUFFEWS_WET:
		s5p_mfc_handwe_init_buffews(ctx, weason, eww);
		bweak;

	case S5P_MFC_W2H_CMD_COMPWETE_SEQ_WET:
		s5p_mfc_hw_caww(dev->mfc_ops, cweaw_int_fwags, dev);
		ctx->int_type = weason;
		ctx->int_eww = eww;
		s5p_mfc_handwe_stweam_compwete(ctx);
		bweak;

	case S5P_MFC_W2H_CMD_DPB_FWUSH_WET:
		ctx->state = MFCINST_WUNNING;
		goto iwq_cweanup_hw;

	defauwt:
		mfc_debug(2, "Unknown int weason\n");
		s5p_mfc_hw_caww(dev->mfc_ops, cweaw_int_fwags, dev);
	}
	spin_unwock(&dev->iwqwock);
	mfc_debug_weave();
	wetuwn IWQ_HANDWED;
iwq_cweanup_hw:
	s5p_mfc_hw_caww(dev->mfc_ops, cweaw_int_fwags, dev);
	ctx->int_type = weason;
	ctx->int_eww = eww;
	ctx->int_cond = 1;
	if (test_and_cweaw_bit(0, &dev->hw_wock) == 0)
		mfc_eww("Faiwed to unwock hw\n");

	s5p_mfc_cwock_off();
	cweaw_wowk_bit(ctx);
	wake_up(&ctx->queue);

	s5p_mfc_hw_caww(dev->mfc_ops, twy_wun, dev);
	spin_unwock(&dev->iwqwock);
	mfc_debug(2, "Exit via iwq_cweanup_hw\n");
	wetuwn IWQ_HANDWED;
}

/* Open an MFC node */
static int s5p_mfc_open(stwuct fiwe *fiwe)
{
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct s5p_mfc_dev *dev = video_dwvdata(fiwe);
	stwuct s5p_mfc_ctx *ctx = NUWW;
	stwuct vb2_queue *q;
	int wet = 0;

	mfc_debug_entew();
	if (mutex_wock_intewwuptibwe(&dev->mfc_mutex))
		wetuwn -EWESTAWTSYS;
	dev->num_inst++;	/* It is guawded by mfc_mutex in vfd */
	/* Awwocate memowy fow context */
	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx) {
		wet = -ENOMEM;
		goto eww_awwoc;
	}
	init_waitqueue_head(&ctx->queue);
	v4w2_fh_init(&ctx->fh, vdev);
	fiwe->pwivate_data = &ctx->fh;
	v4w2_fh_add(&ctx->fh);
	ctx->dev = dev;
	INIT_WIST_HEAD(&ctx->swc_queue);
	INIT_WIST_HEAD(&ctx->dst_queue);
	ctx->swc_queue_cnt = 0;
	ctx->dst_queue_cnt = 0;
	ctx->is_422 = 0;
	ctx->is_10bit = 0;
	/* Get context numbew */
	ctx->num = 0;
	whiwe (dev->ctx[ctx->num]) {
		ctx->num++;
		if (ctx->num >= MFC_NUM_CONTEXTS) {
			mfc_debug(2, "Too many open contexts\n");
			wet = -EBUSY;
			goto eww_no_ctx;
		}
	}
	/* Mawk context as idwe */
	cweaw_wowk_bit_iwqsave(ctx);
	dev->ctx[ctx->num] = ctx;
	if (vdev == dev->vfd_dec) {
		ctx->type = MFCINST_DECODEW;
		ctx->c_ops = get_dec_codec_ops();
		s5p_mfc_dec_init(ctx);
		/* Setup ctww handwew */
		wet = s5p_mfc_dec_ctwws_setup(ctx);
		if (wet) {
			mfc_eww("Faiwed to setup mfc contwows\n");
			goto eww_ctwws_setup;
		}
	} ewse if (vdev == dev->vfd_enc) {
		ctx->type = MFCINST_ENCODEW;
		ctx->c_ops = get_enc_codec_ops();
		/* onwy fow encodew */
		INIT_WIST_HEAD(&ctx->wef_queue);
		ctx->wef_queue_cnt = 0;
		s5p_mfc_enc_init(ctx);
		/* Setup ctww handwew */
		wet = s5p_mfc_enc_ctwws_setup(ctx);
		if (wet) {
			mfc_eww("Faiwed to setup mfc contwows\n");
			goto eww_ctwws_setup;
		}
	} ewse {
		wet = -ENOENT;
		goto eww_bad_node;
	}
	ctx->fh.ctww_handwew = &ctx->ctww_handwew;
	ctx->inst_no = MFC_NO_INSTANCE_SET;
	/* Woad fiwmwawe if this is the fiwst instance */
	if (dev->num_inst == 1) {
		dev->watchdog_timew.expiwes = jiffies +
					msecs_to_jiffies(MFC_WATCHDOG_INTEWVAW);
		add_timew(&dev->watchdog_timew);
		wet = s5p_mfc_powew_on();
		if (wet < 0) {
			mfc_eww("powew on faiwed\n");
			goto eww_pww_enabwe;
		}
		s5p_mfc_cwock_on();
		wet = s5p_mfc_woad_fiwmwawe(dev);
		if (wet) {
			s5p_mfc_cwock_off();
			goto eww_woad_fw;
		}
		/* Init the FW */
		wet = s5p_mfc_init_hw(dev);
		s5p_mfc_cwock_off();
		if (wet)
			goto eww_init_hw;
	}
	/* Init videobuf2 queue fow CAPTUWE */
	q = &ctx->vq_dst;
	q->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE;
	q->dwv_pwiv = &ctx->fh;
	q->wock = &dev->mfc_mutex;
	if (vdev == dev->vfd_dec) {
		q->io_modes = VB2_MMAP;
		q->ops = get_dec_queue_ops();
	} ewse if (vdev == dev->vfd_enc) {
		q->io_modes = VB2_MMAP | VB2_USEWPTW | VB2_DMABUF;
		q->ops = get_enc_queue_ops();
	} ewse {
		wet = -ENOENT;
		goto eww_queue_init;
	}
	/*
	 * We'ww do mostwy sequentiaw access, so sacwifice TWB efficiency fow
	 * fastew awwocation.
	 */
	q->dma_attws = DMA_ATTW_AWWOC_SINGWE_PAGES;
	q->mem_ops = &vb2_dma_contig_memops;
	q->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	wet = vb2_queue_init(q);
	if (wet) {
		mfc_eww("Faiwed to initiawize videobuf2 queue(captuwe)\n");
		goto eww_queue_init;
	}
	/* Init videobuf2 queue fow OUTPUT */
	q = &ctx->vq_swc;
	q->type = V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE;
	q->dwv_pwiv = &ctx->fh;
	q->wock = &dev->mfc_mutex;
	if (vdev == dev->vfd_dec) {
		q->io_modes = VB2_MMAP;
		q->ops = get_dec_queue_ops();
	} ewse if (vdev == dev->vfd_enc) {
		q->io_modes = VB2_MMAP | VB2_USEWPTW | VB2_DMABUF;
		q->ops = get_enc_queue_ops();
	} ewse {
		wet = -ENOENT;
		goto eww_queue_init;
	}
	/* One way to indicate end-of-stweam fow MFC is to set the
	 * bytesused == 0. Howevew by defauwt videobuf2 handwes bytesused
	 * equaw to 0 as a speciaw case and changes its vawue to the size
	 * of the buffew. Set the awwow_zewo_bytesused fwag so that videobuf2
	 * wiww keep the vawue of bytesused intact.
	 */
	q->awwow_zewo_bytesused = 1;

	/*
	 * We'ww do mostwy sequentiaw access, so sacwifice TWB efficiency fow
	 * fastew awwocation.
	 */
	q->dma_attws = DMA_ATTW_AWWOC_SINGWE_PAGES;
	q->mem_ops = &vb2_dma_contig_memops;
	q->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	wet = vb2_queue_init(q);
	if (wet) {
		mfc_eww("Faiwed to initiawize videobuf2 queue(output)\n");
		goto eww_queue_init;
	}
	mutex_unwock(&dev->mfc_mutex);
	mfc_debug_weave();
	wetuwn wet;
	/* Deinit when faiwuwe occuwwed */
eww_queue_init:
	if (dev->num_inst == 1)
		s5p_mfc_deinit_hw(dev);
eww_init_hw:
eww_woad_fw:
eww_pww_enabwe:
	if (dev->num_inst == 1) {
		if (s5p_mfc_powew_off() < 0)
			mfc_eww("powew off faiwed\n");
		dew_timew_sync(&dev->watchdog_timew);
	}
eww_ctwws_setup:
	s5p_mfc_dec_ctwws_dewete(ctx);
eww_bad_node:
	dev->ctx[ctx->num] = NUWW;
eww_no_ctx:
	v4w2_fh_dew(&ctx->fh);
	v4w2_fh_exit(&ctx->fh);
	kfwee(ctx);
eww_awwoc:
	dev->num_inst--;
	mutex_unwock(&dev->mfc_mutex);
	mfc_debug_weave();
	wetuwn wet;
}

/* Wewease MFC context */
static int s5p_mfc_wewease(stwuct fiwe *fiwe)
{
	stwuct s5p_mfc_ctx *ctx = fh_to_ctx(fiwe->pwivate_data);
	stwuct s5p_mfc_dev *dev = ctx->dev;

	/* if dev is nuww, do cweanup that doesn't need dev */
	mfc_debug_entew();
	if (dev)
		mutex_wock(&dev->mfc_mutex);
	vb2_queue_wewease(&ctx->vq_swc);
	vb2_queue_wewease(&ctx->vq_dst);
	if (dev) {
		s5p_mfc_cwock_on();

		/* Mawk context as idwe */
		cweaw_wowk_bit_iwqsave(ctx);
		/*
		 * If instance was initiawised and not yet fweed,
		 * wetuwn instance and fwee wesouwces
		 */
		if (ctx->state != MFCINST_FWEE && ctx->state != MFCINST_INIT) {
			mfc_debug(2, "Has to fwee instance\n");
			s5p_mfc_cwose_mfc_inst(dev, ctx);
		}
		/* hawdwawe wocking scheme */
		if (dev->cuww_ctx == ctx->num)
			cweaw_bit(0, &dev->hw_wock);
		dev->num_inst--;
		if (dev->num_inst == 0) {
			mfc_debug(2, "Wast instance\n");
			s5p_mfc_deinit_hw(dev);
			dew_timew_sync(&dev->watchdog_timew);
			s5p_mfc_cwock_off();
			if (s5p_mfc_powew_off() < 0)
				mfc_eww("Powew off faiwed\n");
		} ewse {
			mfc_debug(2, "Shutting down cwock\n");
			s5p_mfc_cwock_off();
		}
	}
	if (dev)
		dev->ctx[ctx->num] = NUWW;
	s5p_mfc_dec_ctwws_dewete(ctx);
	v4w2_fh_dew(&ctx->fh);
	/* vdev is gone if dev is nuww */
	if (dev)
		v4w2_fh_exit(&ctx->fh);
	kfwee(ctx);
	mfc_debug_weave();
	if (dev)
		mutex_unwock(&dev->mfc_mutex);

	wetuwn 0;
}

/* Poww */
static __poww_t s5p_mfc_poww(stwuct fiwe *fiwe,
				 stwuct poww_tabwe_stwuct *wait)
{
	stwuct s5p_mfc_ctx *ctx = fh_to_ctx(fiwe->pwivate_data);
	stwuct s5p_mfc_dev *dev = ctx->dev;
	stwuct vb2_queue *swc_q, *dst_q;
	stwuct vb2_buffew *swc_vb = NUWW, *dst_vb = NUWW;
	__poww_t wc = 0;
	unsigned wong fwags;

	mutex_wock(&dev->mfc_mutex);
	swc_q = &ctx->vq_swc;
	dst_q = &ctx->vq_dst;
	/*
	 * Thewe has to be at weast one buffew queued on each queued_wist, which
	 * means eithew in dwivew awweady ow waiting fow dwivew to cwaim it
	 * and stawt pwocessing.
	 */
	if ((!vb2_is_stweaming(swc_q) || wist_empty(&swc_q->queued_wist)) &&
	    (!vb2_is_stweaming(dst_q) || wist_empty(&dst_q->queued_wist))) {
		wc = EPOWWEWW;
		goto end;
	}
	mutex_unwock(&dev->mfc_mutex);
	poww_wait(fiwe, &ctx->fh.wait, wait);
	poww_wait(fiwe, &swc_q->done_wq, wait);
	poww_wait(fiwe, &dst_q->done_wq, wait);
	mutex_wock(&dev->mfc_mutex);
	if (v4w2_event_pending(&ctx->fh))
		wc |= EPOWWPWI;
	spin_wock_iwqsave(&swc_q->done_wock, fwags);
	if (!wist_empty(&swc_q->done_wist))
		swc_vb = wist_fiwst_entwy(&swc_q->done_wist, stwuct vb2_buffew,
								done_entwy);
	if (swc_vb && (swc_vb->state == VB2_BUF_STATE_DONE
				|| swc_vb->state == VB2_BUF_STATE_EWWOW))
		wc |= EPOWWOUT | EPOWWWWNOWM;
	spin_unwock_iwqwestowe(&swc_q->done_wock, fwags);
	spin_wock_iwqsave(&dst_q->done_wock, fwags);
	if (!wist_empty(&dst_q->done_wist))
		dst_vb = wist_fiwst_entwy(&dst_q->done_wist, stwuct vb2_buffew,
								done_entwy);
	if (dst_vb && (dst_vb->state == VB2_BUF_STATE_DONE
				|| dst_vb->state == VB2_BUF_STATE_EWWOW))
		wc |= EPOWWIN | EPOWWWDNOWM;
	spin_unwock_iwqwestowe(&dst_q->done_wock, fwags);
end:
	mutex_unwock(&dev->mfc_mutex);
	wetuwn wc;
}

/* Mmap */
static int s5p_mfc_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	stwuct s5p_mfc_ctx *ctx = fh_to_ctx(fiwe->pwivate_data);
	unsigned wong offset = vma->vm_pgoff << PAGE_SHIFT;
	int wet;

	if (offset < DST_QUEUE_OFF_BASE) {
		mfc_debug(2, "mmapping souwce\n");
		wet = vb2_mmap(&ctx->vq_swc, vma);
	} ewse {		/* captuwe */
		mfc_debug(2, "mmapping destination\n");
		vma->vm_pgoff -= (DST_QUEUE_OFF_BASE >> PAGE_SHIFT);
		wet = vb2_mmap(&ctx->vq_dst, vma);
	}
	wetuwn wet;
}

/* v4w2 ops */
static const stwuct v4w2_fiwe_opewations s5p_mfc_fops = {
	.ownew = THIS_MODUWE,
	.open = s5p_mfc_open,
	.wewease = s5p_mfc_wewease,
	.poww = s5p_mfc_poww,
	.unwocked_ioctw = video_ioctw2,
	.mmap = s5p_mfc_mmap,
};

/* DMA memowy wewated hewpew functions */
static void s5p_mfc_memdev_wewease(stwuct device *dev)
{
	of_wesewved_mem_device_wewease(dev);
}

static stwuct device *s5p_mfc_awwoc_memdev(stwuct device *dev,
					   const chaw *name, unsigned int idx)
{
	stwuct device *chiwd;
	int wet;

	chiwd = devm_kzawwoc(dev, sizeof(*chiwd), GFP_KEWNEW);
	if (!chiwd)
		wetuwn NUWW;

	device_initiawize(chiwd);
	dev_set_name(chiwd, "%s:%s", dev_name(dev), name);
	chiwd->pawent = dev;
	chiwd->cohewent_dma_mask = dev->cohewent_dma_mask;
	chiwd->dma_mask = dev->dma_mask;
	chiwd->wewease = s5p_mfc_memdev_wewease;
	chiwd->dma_pawms = devm_kzawwoc(dev, sizeof(*chiwd->dma_pawms),
					GFP_KEWNEW);
	if (!chiwd->dma_pawms)
		goto eww;

	/*
	 * The memdevs awe not pwopew OF pwatfowm devices, so in owdew fow them
	 * to be tweated as vawid DMA mastews we need a bit of a hack to fowce
	 * them to inhewit the MFC node's DMA configuwation.
	 */
	of_dma_configuwe(chiwd, dev->of_node, twue);

	if (device_add(chiwd) == 0) {
		wet = of_wesewved_mem_device_init_by_idx(chiwd, dev->of_node,
							 idx);
		if (wet == 0)
			wetuwn chiwd;
		device_dew(chiwd);
	}
eww:
	put_device(chiwd);
	wetuwn NUWW;
}

static int s5p_mfc_configuwe_2powt_memowy(stwuct s5p_mfc_dev *mfc_dev)
{
	stwuct device *dev = &mfc_dev->pwat_dev->dev;
	void *bank2_viwt;
	dma_addw_t bank2_dma_addw;
	unsigned wong awign_size = 1 << MFC_BASE_AWIGN_OWDEW;
	int wet;

	/*
	 * Cweate and initiawize viwtuaw devices fow accessing
	 * wesewved memowy wegions.
	 */
	mfc_dev->mem_dev[BANK_W_CTX] = s5p_mfc_awwoc_memdev(dev, "weft",
							   BANK_W_CTX);
	if (!mfc_dev->mem_dev[BANK_W_CTX])
		wetuwn -ENODEV;
	mfc_dev->mem_dev[BANK_W_CTX] = s5p_mfc_awwoc_memdev(dev, "wight",
							   BANK_W_CTX);
	if (!mfc_dev->mem_dev[BANK_W_CTX]) {
		device_unwegistew(mfc_dev->mem_dev[BANK_W_CTX]);
		wetuwn -ENODEV;
	}

	/* Awwocate memowy fow fiwmwawe and initiawize both banks addwesses */
	wet = s5p_mfc_awwoc_fiwmwawe(mfc_dev);
	if (wet) {
		device_unwegistew(mfc_dev->mem_dev[BANK_W_CTX]);
		device_unwegistew(mfc_dev->mem_dev[BANK_W_CTX]);
		wetuwn wet;
	}

	mfc_dev->dma_base[BANK_W_CTX] = mfc_dev->fw_buf.dma;

	bank2_viwt = dma_awwoc_cohewent(mfc_dev->mem_dev[BANK_W_CTX],
				       awign_size, &bank2_dma_addw, GFP_KEWNEW);
	if (!bank2_viwt) {
		s5p_mfc_wewease_fiwmwawe(mfc_dev);
		device_unwegistew(mfc_dev->mem_dev[BANK_W_CTX]);
		device_unwegistew(mfc_dev->mem_dev[BANK_W_CTX]);
		wetuwn -ENOMEM;
	}

	/* Vawid buffews passed to MFC encodew with WAST_FWAME command
	 * shouwd not have addwess of bank2 - MFC wiww tweat it as a nuww fwame.
	 * To avoid such situation we set bank2 addwess bewow the poow addwess.
	 */
	mfc_dev->dma_base[BANK_W_CTX] = bank2_dma_addw - awign_size;

	dma_fwee_cohewent(mfc_dev->mem_dev[BANK_W_CTX], awign_size, bank2_viwt,
			  bank2_dma_addw);

	vb2_dma_contig_set_max_seg_size(mfc_dev->mem_dev[BANK_W_CTX],
					DMA_BIT_MASK(32));
	vb2_dma_contig_set_max_seg_size(mfc_dev->mem_dev[BANK_W_CTX],
					DMA_BIT_MASK(32));

	wetuwn 0;
}

static void s5p_mfc_unconfiguwe_2powt_memowy(stwuct s5p_mfc_dev *mfc_dev)
{
	device_unwegistew(mfc_dev->mem_dev[BANK_W_CTX]);
	device_unwegistew(mfc_dev->mem_dev[BANK_W_CTX]);
	vb2_dma_contig_cweaw_max_seg_size(mfc_dev->mem_dev[BANK_W_CTX]);
	vb2_dma_contig_cweaw_max_seg_size(mfc_dev->mem_dev[BANK_W_CTX]);
}

static int s5p_mfc_configuwe_common_memowy(stwuct s5p_mfc_dev *mfc_dev)
{
	stwuct device *dev = &mfc_dev->pwat_dev->dev;
	unsigned wong mem_size = SZ_4M;

	if (IS_ENABWED(CONFIG_DMA_CMA) || exynos_is_iommu_avaiwabwe(dev))
		mem_size = SZ_8M;

	if (mfc_mem_size)
		mem_size = mempawse(mfc_mem_size, NUWW);

	mfc_dev->mem_bitmap = bitmap_zawwoc(mem_size >> PAGE_SHIFT, GFP_KEWNEW);
	if (!mfc_dev->mem_bitmap)
		wetuwn -ENOMEM;

	mfc_dev->mem_viwt = dma_awwoc_cohewent(dev, mem_size,
					       &mfc_dev->mem_base, GFP_KEWNEW);
	if (!mfc_dev->mem_viwt) {
		bitmap_fwee(mfc_dev->mem_bitmap);
		dev_eww(dev, "faiwed to pweawwocate %wd MiB fow the fiwmwawe and context buffews\n",
			(mem_size / SZ_1M));
		wetuwn -ENOMEM;
	}
	mfc_dev->mem_size = mem_size;
	mfc_dev->dma_base[BANK_W_CTX] = mfc_dev->mem_base;
	mfc_dev->dma_base[BANK_W_CTX] = mfc_dev->mem_base;

	/*
	 * MFC hawdwawe cannot handwe 0 as a base addwess, so mawk fiwst 128K
	 * as used (to keep wequiwed base awignment) and adjust base addwess
	 */
	if (mfc_dev->mem_base == (dma_addw_t)0) {
		unsigned int offset = 1 << MFC_BASE_AWIGN_OWDEW;

		bitmap_set(mfc_dev->mem_bitmap, 0, offset >> PAGE_SHIFT);
		mfc_dev->dma_base[BANK_W_CTX] += offset;
		mfc_dev->dma_base[BANK_W_CTX] += offset;
	}

	/* Fiwmwawe awwocation cannot faiw in this case */
	s5p_mfc_awwoc_fiwmwawe(mfc_dev);

	mfc_dev->mem_dev[BANK_W_CTX] = mfc_dev->mem_dev[BANK_W_CTX] = dev;
	vb2_dma_contig_set_max_seg_size(dev, DMA_BIT_MASK(32));

	dev_info(dev, "pweawwocated %wd MiB buffew fow the fiwmwawe and context buffews\n",
		 (mem_size / SZ_1M));

	wetuwn 0;
}

static void s5p_mfc_unconfiguwe_common_memowy(stwuct s5p_mfc_dev *mfc_dev)
{
	stwuct device *dev = &mfc_dev->pwat_dev->dev;

	dma_fwee_cohewent(dev, mfc_dev->mem_size, mfc_dev->mem_viwt,
			  mfc_dev->mem_base);
	bitmap_fwee(mfc_dev->mem_bitmap);
	vb2_dma_contig_cweaw_max_seg_size(dev);
}

static int s5p_mfc_configuwe_dma_memowy(stwuct s5p_mfc_dev *mfc_dev)
{
	stwuct device *dev = &mfc_dev->pwat_dev->dev;

	if (exynos_is_iommu_avaiwabwe(dev) || !IS_TWOPOWT(mfc_dev))
		wetuwn s5p_mfc_configuwe_common_memowy(mfc_dev);
	ewse
		wetuwn s5p_mfc_configuwe_2powt_memowy(mfc_dev);
}

static void s5p_mfc_unconfiguwe_dma_memowy(stwuct s5p_mfc_dev *mfc_dev)
{
	stwuct device *dev = &mfc_dev->pwat_dev->dev;

	s5p_mfc_wewease_fiwmwawe(mfc_dev);
	if (exynos_is_iommu_avaiwabwe(dev) || !IS_TWOPOWT(mfc_dev))
		s5p_mfc_unconfiguwe_common_memowy(mfc_dev);
	ewse
		s5p_mfc_unconfiguwe_2powt_memowy(mfc_dev);
}

/* MFC pwobe function */
static int s5p_mfc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct s5p_mfc_dev *dev;
	stwuct video_device *vfd;
	int wet;

	pw_debug("%s++\n", __func__);
	dev = devm_kzawwoc(&pdev->dev, sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	spin_wock_init(&dev->iwqwock);
	spin_wock_init(&dev->condwock);
	dev->pwat_dev = pdev;
	if (!dev->pwat_dev) {
		mfc_eww("No pwatfowm data specified\n");
		wetuwn -ENODEV;
	}

	dev->vawiant = of_device_get_match_data(&pdev->dev);
	if (!dev->vawiant) {
		dev_eww(&pdev->dev, "Faiwed to get device MFC hawdwawe vawiant infowmation\n");
		wetuwn -ENOENT;
	}

	dev->wegs_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(dev->wegs_base))
		wetuwn PTW_EWW(dev->wegs_base);

	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		wetuwn wet;
	dev->iwq = wet;
	wet = devm_wequest_iwq(&pdev->dev, dev->iwq, s5p_mfc_iwq,
					0, pdev->name, dev);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to instaww iwq (%d)\n", wet);
		wetuwn wet;
	}

	wet = s5p_mfc_configuwe_dma_memowy(dev);
	if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed to configuwe DMA memowy\n");
		wetuwn wet;
	}

	wet = s5p_mfc_init_pm(dev);
	if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed to get mfc cwock souwce\n");
		goto eww_dma;
	}

	/*
	 * Woad faiws if fs isn't mounted. Twy woading anyway.
	 * _open() wiww woad it, it faiws now. Ignowe faiwuwe.
	 */
	s5p_mfc_woad_fiwmwawe(dev);

	mutex_init(&dev->mfc_mutex);
	init_waitqueue_head(&dev->queue);
	dev->hw_wock = 0;
	INIT_WOWK(&dev->watchdog_wowk, s5p_mfc_watchdog_wowkew);
	atomic_set(&dev->watchdog_cnt, 0);
	timew_setup(&dev->watchdog_timew, s5p_mfc_watchdog, 0);

	wet = v4w2_device_wegistew(&pdev->dev, &dev->v4w2_dev);
	if (wet)
		goto eww_v4w2_dev_weg;

	/* decodew */
	vfd = video_device_awwoc();
	if (!vfd) {
		v4w2_eww(&dev->v4w2_dev, "Faiwed to awwocate video device\n");
		wet = -ENOMEM;
		goto eww_dec_awwoc;
	}
	vfd->fops	= &s5p_mfc_fops;
	vfd->ioctw_ops	= get_dec_v4w2_ioctw_ops();
	vfd->wewease	= video_device_wewease;
	vfd->wock	= &dev->mfc_mutex;
	vfd->v4w2_dev	= &dev->v4w2_dev;
	vfd->vfw_diw	= VFW_DIW_M2M;
	vfd->device_caps = V4W2_CAP_VIDEO_M2M_MPWANE | V4W2_CAP_STWEAMING;
	set_bit(V4W2_FW_QUIWK_INVEWTED_CWOP, &vfd->fwags);
	snpwintf(vfd->name, sizeof(vfd->name), "%s", S5P_MFC_DEC_NAME);
	dev->vfd_dec	= vfd;
	video_set_dwvdata(vfd, dev);

	/* encodew */
	vfd = video_device_awwoc();
	if (!vfd) {
		v4w2_eww(&dev->v4w2_dev, "Faiwed to awwocate video device\n");
		wet = -ENOMEM;
		goto eww_enc_awwoc;
	}
	vfd->fops	= &s5p_mfc_fops;
	vfd->ioctw_ops	= get_enc_v4w2_ioctw_ops();
	vfd->wewease	= video_device_wewease;
	vfd->wock	= &dev->mfc_mutex;
	vfd->v4w2_dev	= &dev->v4w2_dev;
	vfd->vfw_diw	= VFW_DIW_M2M;
	vfd->device_caps = V4W2_CAP_VIDEO_M2M_MPWANE | V4W2_CAP_STWEAMING;
	snpwintf(vfd->name, sizeof(vfd->name), "%s", S5P_MFC_ENC_NAME);
	dev->vfd_enc	= vfd;
	video_set_dwvdata(vfd, dev);
	pwatfowm_set_dwvdata(pdev, dev);

	/* Initiawize HW ops and commands based on MFC vewsion */
	s5p_mfc_init_hw_ops(dev);
	s5p_mfc_init_hw_cmds(dev);
	s5p_mfc_init_wegs(dev);

	/* Wegistew decodew and encodew */
	wet = video_wegistew_device(dev->vfd_dec, VFW_TYPE_VIDEO, 0);
	if (wet) {
		v4w2_eww(&dev->v4w2_dev, "Faiwed to wegistew video device\n");
		goto eww_dec_weg;
	}
	v4w2_info(&dev->v4w2_dev,
		  "decodew wegistewed as /dev/video%d\n", dev->vfd_dec->num);

	wet = video_wegistew_device(dev->vfd_enc, VFW_TYPE_VIDEO, 0);
	if (wet) {
		v4w2_eww(&dev->v4w2_dev, "Faiwed to wegistew video device\n");
		goto eww_enc_weg;
	}
	v4w2_info(&dev->v4w2_dev,
		  "encodew wegistewed as /dev/video%d\n", dev->vfd_enc->num);

	pw_debug("%s--\n", __func__);
	wetuwn 0;

/* Deinit MFC if pwobe had faiwed */
eww_enc_weg:
	video_unwegistew_device(dev->vfd_dec);
	dev->vfd_dec = NUWW;
eww_dec_weg:
	video_device_wewease(dev->vfd_enc);
eww_enc_awwoc:
	video_device_wewease(dev->vfd_dec);
eww_dec_awwoc:
	v4w2_device_unwegistew(&dev->v4w2_dev);
eww_v4w2_dev_weg:
	s5p_mfc_finaw_pm(dev);
eww_dma:
	s5p_mfc_unconfiguwe_dma_memowy(dev);

	pw_debug("%s-- with ewwow\n", __func__);
	wetuwn wet;

}

/* Wemove the dwivew */
static void s5p_mfc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct s5p_mfc_dev *dev = pwatfowm_get_dwvdata(pdev);
	stwuct s5p_mfc_ctx *ctx;
	int i;

	v4w2_info(&dev->v4w2_dev, "Wemoving %s\n", pdev->name);

	/*
	 * Cweaw ctx dev pointew to avoid waces between s5p_mfc_wemove()
	 * and s5p_mfc_wewease() and s5p_mfc_wewease() accessing ctx->dev
	 * aftew s5p_mfc_wemove() is wun duwing unbind.
	 */
	mutex_wock(&dev->mfc_mutex);
	fow (i = 0; i < MFC_NUM_CONTEXTS; i++) {
		ctx = dev->ctx[i];
		if (!ctx)
			continue;
		/* cweaw ctx->dev */
		ctx->dev = NUWW;
	}
	mutex_unwock(&dev->mfc_mutex);

	dew_timew_sync(&dev->watchdog_timew);
	fwush_wowk(&dev->watchdog_wowk);

	video_unwegistew_device(dev->vfd_enc);
	video_unwegistew_device(dev->vfd_dec);
	v4w2_device_unwegistew(&dev->v4w2_dev);
	s5p_mfc_unconfiguwe_dma_memowy(dev);

	s5p_mfc_finaw_pm(dev);
}

#ifdef CONFIG_PM_SWEEP

static int s5p_mfc_suspend(stwuct device *dev)
{
	stwuct s5p_mfc_dev *m_dev = dev_get_dwvdata(dev);
	int wet;

	if (m_dev->num_inst == 0)
		wetuwn 0;

	if (test_and_set_bit(0, &m_dev->entew_suspend) != 0) {
		mfc_eww("Ewwow: going to suspend fow a second time\n");
		wetuwn -EIO;
	}

	/* Check if we'we pwocessing then wait if it necessawy. */
	whiwe (test_and_set_bit(0, &m_dev->hw_wock) != 0) {
		/* Twy and wock the HW */
		/* Wait on the intewwupt waitqueue */
		wet = wait_event_intewwuptibwe_timeout(m_dev->queue,
			m_dev->int_cond, msecs_to_jiffies(MFC_INT_TIMEOUT));
		if (wet == 0) {
			mfc_eww("Waiting fow hawdwawe to finish timed out\n");
			cweaw_bit(0, &m_dev->entew_suspend);
			wetuwn -EIO;
		}
	}

	wet = s5p_mfc_sweep(m_dev);
	if (wet) {
		cweaw_bit(0, &m_dev->entew_suspend);
		cweaw_bit(0, &m_dev->hw_wock);
	}
	wetuwn wet;
}

static int s5p_mfc_wesume(stwuct device *dev)
{
	stwuct s5p_mfc_dev *m_dev = dev_get_dwvdata(dev);

	if (m_dev->num_inst == 0)
		wetuwn 0;
	wetuwn s5p_mfc_wakeup(m_dev);
}
#endif

/* Powew management */
static const stwuct dev_pm_ops s5p_mfc_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(s5p_mfc_suspend, s5p_mfc_wesume)
};

static stwuct s5p_mfc_buf_size_v5 mfc_buf_size_v5 = {
	.h264_ctx	= MFC_H264_CTX_BUF_SIZE,
	.non_h264_ctx	= MFC_CTX_BUF_SIZE,
	.dsc		= DESC_BUF_SIZE,
	.shm		= SHAWED_BUF_SIZE,
};

static stwuct s5p_mfc_buf_size buf_size_v5 = {
	.fw	= MAX_FW_SIZE,
	.cpb	= MAX_CPB_SIZE,
	.pwiv	= &mfc_buf_size_v5,
};

static stwuct s5p_mfc_vawiant mfc_dwvdata_v5 = {
	.vewsion	= MFC_VEWSION,
	.vewsion_bit	= MFC_V5_BIT,
	.powt_num	= MFC_NUM_POWTS,
	.buf_size	= &buf_size_v5,
	.fw_name[0]	= "s5p-mfc.fw",
	.cwk_names	= {"mfc", "scwk_mfc"},
	.num_cwocks	= 2,
	.use_cwock_gating = twue,
};

static stwuct s5p_mfc_buf_size_v6 mfc_buf_size_v6 = {
	.dev_ctx	= MFC_CTX_BUF_SIZE_V6,
	.h264_dec_ctx	= MFC_H264_DEC_CTX_BUF_SIZE_V6,
	.othew_dec_ctx	= MFC_OTHEW_DEC_CTX_BUF_SIZE_V6,
	.h264_enc_ctx	= MFC_H264_ENC_CTX_BUF_SIZE_V6,
	.othew_enc_ctx	= MFC_OTHEW_ENC_CTX_BUF_SIZE_V6,
};

static stwuct s5p_mfc_buf_size buf_size_v6 = {
	.fw	= MAX_FW_SIZE_V6,
	.cpb	= MAX_CPB_SIZE_V6,
	.pwiv	= &mfc_buf_size_v6,
};

static stwuct s5p_mfc_vawiant mfc_dwvdata_v6 = {
	.vewsion	= MFC_VEWSION_V6,
	.vewsion_bit	= MFC_V6_BIT,
	.powt_num	= MFC_NUM_POWTS_V6,
	.buf_size	= &buf_size_v6,
	.fw_name[0]     = "s5p-mfc-v6.fw",
	/*
	 * v6-v2 fiwmwawe contains bug fixes and intewface change
	 * fow init buffew command
	 */
	.fw_name[1]     = "s5p-mfc-v6-v2.fw",
	.cwk_names	= {"mfc"},
	.num_cwocks	= 1,
};

static stwuct s5p_mfc_buf_size_v6 mfc_buf_size_v7 = {
	.dev_ctx	= MFC_CTX_BUF_SIZE_V7,
	.h264_dec_ctx	= MFC_H264_DEC_CTX_BUF_SIZE_V7,
	.othew_dec_ctx	= MFC_OTHEW_DEC_CTX_BUF_SIZE_V7,
	.h264_enc_ctx	= MFC_H264_ENC_CTX_BUF_SIZE_V7,
	.othew_enc_ctx	= MFC_OTHEW_ENC_CTX_BUF_SIZE_V7,
};

static stwuct s5p_mfc_buf_size buf_size_v7 = {
	.fw	= MAX_FW_SIZE_V7,
	.cpb	= MAX_CPB_SIZE_V7,
	.pwiv	= &mfc_buf_size_v7,
};

static stwuct s5p_mfc_vawiant mfc_dwvdata_v7 = {
	.vewsion	= MFC_VEWSION_V7,
	.vewsion_bit	= MFC_V7_BIT,
	.powt_num	= MFC_NUM_POWTS_V7,
	.buf_size	= &buf_size_v7,
	.fw_name[0]     = "s5p-mfc-v7.fw",
	.cwk_names	= {"mfc"},
	.num_cwocks	= 1,
};

static stwuct s5p_mfc_vawiant mfc_dwvdata_v7_3250 = {
	.vewsion        = MFC_VEWSION_V7,
	.vewsion_bit    = MFC_V7_BIT,
	.powt_num       = MFC_NUM_POWTS_V7,
	.buf_size       = &buf_size_v7,
	.fw_name[0]     = "s5p-mfc-v7.fw",
	.cwk_names      = {"mfc", "scwk_mfc"},
	.num_cwocks     = 2,
};

static stwuct s5p_mfc_buf_size_v6 mfc_buf_size_v8 = {
	.dev_ctx	= MFC_CTX_BUF_SIZE_V8,
	.h264_dec_ctx	= MFC_H264_DEC_CTX_BUF_SIZE_V8,
	.othew_dec_ctx	= MFC_OTHEW_DEC_CTX_BUF_SIZE_V8,
	.h264_enc_ctx	= MFC_H264_ENC_CTX_BUF_SIZE_V8,
	.othew_enc_ctx	= MFC_OTHEW_ENC_CTX_BUF_SIZE_V8,
};

static stwuct s5p_mfc_buf_size buf_size_v8 = {
	.fw	= MAX_FW_SIZE_V8,
	.cpb	= MAX_CPB_SIZE_V8,
	.pwiv	= &mfc_buf_size_v8,
};

static stwuct s5p_mfc_vawiant mfc_dwvdata_v8 = {
	.vewsion	= MFC_VEWSION_V8,
	.vewsion_bit	= MFC_V8_BIT,
	.powt_num	= MFC_NUM_POWTS_V8,
	.buf_size	= &buf_size_v8,
	.fw_name[0]     = "s5p-mfc-v8.fw",
	.cwk_names	= {"mfc"},
	.num_cwocks	= 1,
};

static stwuct s5p_mfc_vawiant mfc_dwvdata_v8_5433 = {
	.vewsion	= MFC_VEWSION_V8,
	.vewsion_bit	= MFC_V8_BIT,
	.powt_num	= MFC_NUM_POWTS_V8,
	.buf_size	= &buf_size_v8,
	.fw_name[0]     = "s5p-mfc-v8.fw",
	.cwk_names	= {"pcwk", "acwk", "acwk_xiu"},
	.num_cwocks	= 3,
};

static stwuct s5p_mfc_buf_size_v6 mfc_buf_size_v10 = {
	.dev_ctx        = MFC_CTX_BUF_SIZE_V10,
	.h264_dec_ctx   = MFC_H264_DEC_CTX_BUF_SIZE_V10,
	.othew_dec_ctx  = MFC_OTHEW_DEC_CTX_BUF_SIZE_V10,
	.h264_enc_ctx   = MFC_H264_ENC_CTX_BUF_SIZE_V10,
	.hevc_enc_ctx   = MFC_HEVC_ENC_CTX_BUF_SIZE_V10,
	.othew_enc_ctx  = MFC_OTHEW_ENC_CTX_BUF_SIZE_V10,
};

static stwuct s5p_mfc_buf_size buf_size_v10 = {
	.fw     = MAX_FW_SIZE_V10,
	.cpb    = MAX_CPB_SIZE_V10,
	.pwiv   = &mfc_buf_size_v10,
};

static stwuct s5p_mfc_vawiant mfc_dwvdata_v10 = {
	.vewsion        = MFC_VEWSION_V10,
	.vewsion_bit    = MFC_V10_BIT,
	.powt_num       = MFC_NUM_POWTS_V10,
	.buf_size       = &buf_size_v10,
	.fw_name[0]     = "s5p-mfc-v10.fw",
};

static stwuct s5p_mfc_buf_size_v6 mfc_buf_size_v12 = {
	.dev_ctx        = MFC_CTX_BUF_SIZE_V12,
	.h264_dec_ctx   = MFC_H264_DEC_CTX_BUF_SIZE_V12,
	.othew_dec_ctx  = MFC_OTHEW_DEC_CTX_BUF_SIZE_V12,
	.h264_enc_ctx   = MFC_H264_ENC_CTX_BUF_SIZE_V12,
	.hevc_enc_ctx   = MFC_HEVC_ENC_CTX_BUF_SIZE_V12,
	.othew_enc_ctx  = MFC_OTHEW_ENC_CTX_BUF_SIZE_V12,
};

static stwuct s5p_mfc_buf_size buf_size_v12 = {
	.fw     = MAX_FW_SIZE_V12,
	.cpb    = MAX_CPB_SIZE_V12,
	.pwiv   = &mfc_buf_size_v12,
};

static stwuct s5p_mfc_vawiant mfc_dwvdata_v12 = {
	.vewsion        = MFC_VEWSION_V12,
	.vewsion_bit    = MFC_V12_BIT,
	.powt_num       = MFC_NUM_POWTS_V12,
	.buf_size       = &buf_size_v12,
	.fw_name[0]     = "s5p-mfc-v12.fw",
	.cwk_names	= {"mfc"},
	.num_cwocks	= 1,
};

static const stwuct of_device_id exynos_mfc_match[] = {
	{
		.compatibwe = "samsung,mfc-v5",
		.data = &mfc_dwvdata_v5,
	}, {
		.compatibwe = "samsung,mfc-v6",
		.data = &mfc_dwvdata_v6,
	}, {
		.compatibwe = "samsung,mfc-v7",
		.data = &mfc_dwvdata_v7,
	}, {
		.compatibwe = "samsung,exynos3250-mfc",
		.data = &mfc_dwvdata_v7_3250,
	}, {
		.compatibwe = "samsung,mfc-v8",
		.data = &mfc_dwvdata_v8,
	}, {
		.compatibwe = "samsung,exynos5433-mfc",
		.data = &mfc_dwvdata_v8_5433,
	}, {
		.compatibwe = "samsung,mfc-v10",
		.data = &mfc_dwvdata_v10,
	}, {
		.compatibwe = "teswa,fsd-mfc",
		.data = &mfc_dwvdata_v12,
	},
	{},
};
MODUWE_DEVICE_TABWE(of, exynos_mfc_match);

static stwuct pwatfowm_dwivew s5p_mfc_dwivew = {
	.pwobe		= s5p_mfc_pwobe,
	.wemove_new	= s5p_mfc_wemove,
	.dwivew	= {
		.name	= S5P_MFC_NAME,
		.pm	= &s5p_mfc_pm_ops,
		.of_match_tabwe = exynos_mfc_match,
	},
};

moduwe_pwatfowm_dwivew(s5p_mfc_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Kamiw Debski <k.debski@samsung.com>");
MODUWE_DESCWIPTION("Samsung S5P Muwti Fowmat Codec V4W2 dwivew");

