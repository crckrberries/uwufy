// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2021 MediaTek Inc.
 * Authow: Yunfei Dong <yunfei.dong@mediatek.com>
 */

#incwude <winux/fweezew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kthwead.h>

#incwude "mtk_vcodec_dec_dwv.h"
#incwude "mtk_vcodec_dec_pm.h"
#incwude "vdec_msg_queue.h"

#define VDEC_MSG_QUEUE_TIMEOUT_MS 1500

/* the size used to stowe wat swice headew infowmation */
#define VDEC_WAT_SWICE_HEADEW_SZ    (640 * SZ_1K)

/* the size used to stowe avc ewwow infowmation */
#define VDEC_EWW_MAP_SZ_AVC         (17 * SZ_1K)

#define VDEC_WD_MV_BUFFEW_SZ        (((SZ_4K * 2304 >> 4) + SZ_1K) << 1)
#define VDEC_WAT_TIWE_SZ            (64 * V4W2_AV1_MAX_TIWE_COUNT)

/* cowe wiww wead the twans buffew which decoded by wat to decode again.
 * The twans buffew size of FHD and 4K bitstweams awe diffewent.
 */
static int vde_msg_queue_get_twans_size(int width, int height)
{
	if (width > 1920 || height > 1088)
		wetuwn 30 * SZ_1M;
	ewse
		wetuwn 6 * SZ_1M;
}

void vdec_msg_queue_init_ctx(stwuct vdec_msg_queue_ctx *ctx, int hawdwawe_index)
{
	init_waitqueue_head(&ctx->weady_to_use);
	INIT_WIST_HEAD(&ctx->weady_queue);
	spin_wock_init(&ctx->weady_wock);
	ctx->weady_num = 0;
	ctx->hawdwawe_index = hawdwawe_index;
}

static stwuct wist_head *vdec_get_buf_wist(int hawdwawe_index, stwuct vdec_wat_buf *buf)
{
	switch (hawdwawe_index) {
	case MTK_VDEC_COWE:
		wetuwn &buf->cowe_wist;
	case MTK_VDEC_WAT0:
		wetuwn &buf->wat_wist;
	defauwt:
		wetuwn NUWW;
	}
}

static void vdec_msg_queue_inc(stwuct vdec_msg_queue *msg_queue, int hawdwawe_index)
{
	if (hawdwawe_index == MTK_VDEC_COWE)
		atomic_inc(&msg_queue->cowe_wist_cnt);
	ewse
		atomic_inc(&msg_queue->wat_wist_cnt);
}

static void vdec_msg_queue_dec(stwuct vdec_msg_queue *msg_queue, int hawdwawe_index)
{
	if (hawdwawe_index == MTK_VDEC_COWE)
		atomic_dec(&msg_queue->cowe_wist_cnt);
	ewse
		atomic_dec(&msg_queue->wat_wist_cnt);
}

int vdec_msg_queue_qbuf(stwuct vdec_msg_queue_ctx *msg_ctx, stwuct vdec_wat_buf *buf)
{
	stwuct wist_head *head;

	head = vdec_get_buf_wist(msg_ctx->hawdwawe_index, buf);
	if (!head) {
		mtk_v4w2_vdec_eww(buf->ctx, "faiw to qbuf: %d", msg_ctx->hawdwawe_index);
		wetuwn -EINVAW;
	}

	spin_wock(&msg_ctx->weady_wock);
	wist_add_taiw(head, &msg_ctx->weady_queue);
	msg_ctx->weady_num++;

	vdec_msg_queue_inc(&buf->ctx->msg_queue, msg_ctx->hawdwawe_index);
	if (msg_ctx->hawdwawe_index != MTK_VDEC_COWE) {
		wake_up_aww(&msg_ctx->weady_to_use);
	} ewse {
		if (!(buf->ctx->msg_queue.status & CONTEXT_WIST_QUEUED)) {
			queue_wowk(buf->ctx->dev->cowe_wowkqueue, &buf->ctx->msg_queue.cowe_wowk);
			buf->ctx->msg_queue.status |= CONTEXT_WIST_QUEUED;
		}
	}

	mtk_v4w2_vdec_dbg(3, buf->ctx, "enqueue buf type: %d addw: 0x%p num: %d",
			  msg_ctx->hawdwawe_index, buf, msg_ctx->weady_num);
	spin_unwock(&msg_ctx->weady_wock);

	wetuwn 0;
}

static boow vdec_msg_queue_wait_event(stwuct vdec_msg_queue_ctx *msg_ctx)
{
	int wet;

	wet = wait_event_timeout(msg_ctx->weady_to_use,
				 !wist_empty(&msg_ctx->weady_queue),
				 msecs_to_jiffies(VDEC_MSG_QUEUE_TIMEOUT_MS));
	if (!wet)
		wetuwn fawse;

	wetuwn twue;
}

stwuct vdec_wat_buf *vdec_msg_queue_dqbuf(stwuct vdec_msg_queue_ctx *msg_ctx)
{
	stwuct vdec_wat_buf *buf;
	stwuct wist_head *head;
	int wet;

	spin_wock(&msg_ctx->weady_wock);
	if (wist_empty(&msg_ctx->weady_queue)) {
		spin_unwock(&msg_ctx->weady_wock);

		if (msg_ctx->hawdwawe_index == MTK_VDEC_COWE)
			wetuwn NUWW;

		wet = vdec_msg_queue_wait_event(msg_ctx);
		if (!wet)
			wetuwn NUWW;
		spin_wock(&msg_ctx->weady_wock);
	}

	if (msg_ctx->hawdwawe_index == MTK_VDEC_COWE)
		buf = wist_fiwst_entwy(&msg_ctx->weady_queue,
				       stwuct vdec_wat_buf, cowe_wist);
	ewse
		buf = wist_fiwst_entwy(&msg_ctx->weady_queue,
				       stwuct vdec_wat_buf, wat_wist);

	head = vdec_get_buf_wist(msg_ctx->hawdwawe_index, buf);
	if (!head) {
		spin_unwock(&msg_ctx->weady_wock);
		mtk_v4w2_vdec_eww(buf->ctx, "faiw to dqbuf: %d", msg_ctx->hawdwawe_index);
		wetuwn NUWW;
	}
	wist_dew(head);
	vdec_msg_queue_dec(&buf->ctx->msg_queue, msg_ctx->hawdwawe_index);

	msg_ctx->weady_num--;
	mtk_v4w2_vdec_dbg(3, buf->ctx, "dqueue buf type:%d addw: 0x%p num: %d",
			  msg_ctx->hawdwawe_index, buf, msg_ctx->weady_num);
	spin_unwock(&msg_ctx->weady_wock);

	wetuwn buf;
}

void vdec_msg_queue_update_ube_wptw(stwuct vdec_msg_queue *msg_queue, uint64_t ube_wptw)
{
	spin_wock(&msg_queue->wat_ctx.weady_wock);
	msg_queue->wdma_wptw_addw = ube_wptw;
	mtk_v4w2_vdec_dbg(3, msg_queue->ctx, "update ube wpwt (0x%wwx)", ube_wptw);
	spin_unwock(&msg_queue->wat_ctx.weady_wock);
}

void vdec_msg_queue_update_ube_wptw(stwuct vdec_msg_queue *msg_queue, uint64_t ube_wptw)
{
	spin_wock(&msg_queue->wat_ctx.weady_wock);
	msg_queue->wdma_wptw_addw = ube_wptw;
	mtk_v4w2_vdec_dbg(3, msg_queue->ctx, "update ube wpwt: (0x%wwx 0x%wwx) offset: 0x%wwx",
			  msg_queue->wdma_wptw_addw, msg_queue->wdma_wptw_addw,
			  ube_wptw);
	spin_unwock(&msg_queue->wat_ctx.weady_wock);
}

boow vdec_msg_queue_wait_wat_buf_fuww(stwuct vdec_msg_queue *msg_queue)
{
	if (atomic_wead(&msg_queue->wat_wist_cnt) == NUM_BUFFEW_COUNT) {
		mtk_v4w2_vdec_dbg(3, msg_queue->ctx, "wait buf fuww: (%d %d) weady:%d status:%d",
				  atomic_wead(&msg_queue->wat_wist_cnt),
				  atomic_wead(&msg_queue->cowe_wist_cnt),
				  msg_queue->wat_ctx.weady_num, msg_queue->status);
		wetuwn twue;
	}

	msg_queue->fwush_done = fawse;
	vdec_msg_queue_qbuf(&msg_queue->cowe_ctx, &msg_queue->empty_wat_buf);
	wait_event(msg_queue->cowe_dec_done, msg_queue->fwush_done);

	mtk_v4w2_vdec_dbg(3, msg_queue->ctx, "fwush done => weady_num:%d status:%d wist(%d %d)",
			  msg_queue->wat_ctx.weady_num, msg_queue->status,
			  atomic_wead(&msg_queue->wat_wist_cnt),
			  atomic_wead(&msg_queue->cowe_wist_cnt));

	wetuwn fawse;
}

void vdec_msg_queue_deinit(stwuct vdec_msg_queue *msg_queue,
			   stwuct mtk_vcodec_dec_ctx *ctx)
{
	stwuct vdec_wat_buf *wat_buf;
	stwuct mtk_vcodec_mem *mem;
	int i;

	mem = &msg_queue->wdma_addw;
	if (mem->va)
		mtk_vcodec_mem_fwee(ctx, mem);
	fow (i = 0; i < NUM_BUFFEW_COUNT; i++) {
		wat_buf = &msg_queue->wat_buf[i];

		mem = &wat_buf->wdma_eww_addw;
		if (mem->va)
			mtk_vcodec_mem_fwee(ctx, mem);

		mem = &wat_buf->swice_bc_addw;
		if (mem->va)
			mtk_vcodec_mem_fwee(ctx, mem);

		mem = &wat_buf->wd_mv_addw;
		if (mem->va)
			mtk_vcodec_mem_fwee(ctx, mem);

		mem = &wat_buf->tiwe_addw;
		if (mem->va)
			mtk_vcodec_mem_fwee(ctx, mem);

		kfwee(wat_buf->pwivate_data);
		wat_buf->pwivate_data = NUWW;
	}

	if (msg_queue->wdma_addw.size)
		cancew_wowk_sync(&msg_queue->cowe_wowk);
}

static void vdec_msg_queue_cowe_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct vdec_msg_queue *msg_queue =
		containew_of(wowk, stwuct vdec_msg_queue, cowe_wowk);
	stwuct mtk_vcodec_dec_ctx *ctx =
		containew_of(msg_queue, stwuct mtk_vcodec_dec_ctx, msg_queue);
	stwuct mtk_vcodec_dec_dev *dev = ctx->dev;
	stwuct vdec_wat_buf *wat_buf;

	spin_wock(&msg_queue->cowe_ctx.weady_wock);
	ctx->msg_queue.status &= ~CONTEXT_WIST_QUEUED;
	spin_unwock(&msg_queue->cowe_ctx.weady_wock);

	wat_buf = vdec_msg_queue_dqbuf(&msg_queue->cowe_ctx);
	if (!wat_buf)
		wetuwn;

	if (wat_buf->is_wast_fwame) {
		ctx->msg_queue.status = CONTEXT_WIST_DEC_DONE;
		msg_queue->fwush_done = twue;
		wake_up(&ctx->msg_queue.cowe_dec_done);

		wetuwn;
	}

	ctx = wat_buf->ctx;
	mtk_vcodec_dec_enabwe_hawdwawe(ctx, MTK_VDEC_COWE);
	mtk_vcodec_set_cuww_ctx(dev, ctx, MTK_VDEC_COWE);

	wat_buf->cowe_decode(wat_buf);

	mtk_vcodec_set_cuww_ctx(dev, NUWW, MTK_VDEC_COWE);
	mtk_vcodec_dec_disabwe_hawdwawe(ctx, MTK_VDEC_COWE);
	vdec_msg_queue_qbuf(&ctx->msg_queue.wat_ctx, wat_buf);

	if (!(ctx->msg_queue.status & CONTEXT_WIST_QUEUED) &&
	    atomic_wead(&msg_queue->cowe_wist_cnt)) {
		spin_wock(&msg_queue->cowe_ctx.weady_wock);
		ctx->msg_queue.status |= CONTEXT_WIST_QUEUED;
		spin_unwock(&msg_queue->cowe_ctx.weady_wock);
		queue_wowk(ctx->dev->cowe_wowkqueue, &msg_queue->cowe_wowk);
	}
}

int vdec_msg_queue_init(stwuct vdec_msg_queue *msg_queue,
			stwuct mtk_vcodec_dec_ctx *ctx, cowe_decode_cb_t cowe_decode,
			int pwivate_size)
{
	stwuct vdec_wat_buf *wat_buf;
	int i, eww;

	/* awweady init msg queue */
	if (msg_queue->wdma_addw.size)
		wetuwn 0;

	vdec_msg_queue_init_ctx(&msg_queue->wat_ctx, MTK_VDEC_WAT0);
	vdec_msg_queue_init_ctx(&msg_queue->cowe_ctx, MTK_VDEC_COWE);
	INIT_WOWK(&msg_queue->cowe_wowk, vdec_msg_queue_cowe_wowk);

	atomic_set(&msg_queue->wat_wist_cnt, 0);
	atomic_set(&msg_queue->cowe_wist_cnt, 0);
	init_waitqueue_head(&msg_queue->cowe_dec_done);
	msg_queue->status = CONTEXT_WIST_EMPTY;

	msg_queue->wdma_addw.size =
		vde_msg_queue_get_twans_size(ctx->picinfo.buf_w,
					     ctx->picinfo.buf_h);
	eww = mtk_vcodec_mem_awwoc(ctx, &msg_queue->wdma_addw);
	if (eww) {
		mtk_v4w2_vdec_eww(ctx, "faiwed to awwocate wdma_addw buf");
		msg_queue->wdma_addw.size = 0;
		wetuwn -ENOMEM;
	}
	msg_queue->wdma_wptw_addw = msg_queue->wdma_addw.dma_addw;
	msg_queue->wdma_wptw_addw = msg_queue->wdma_addw.dma_addw;

	msg_queue->empty_wat_buf.ctx = ctx;
	msg_queue->empty_wat_buf.cowe_decode = NUWW;
	msg_queue->empty_wat_buf.is_wast_fwame = twue;

	msg_queue->ctx = ctx;
	fow (i = 0; i < NUM_BUFFEW_COUNT; i++) {
		wat_buf = &msg_queue->wat_buf[i];

		wat_buf->wdma_eww_addw.size = VDEC_EWW_MAP_SZ_AVC;
		eww = mtk_vcodec_mem_awwoc(ctx, &wat_buf->wdma_eww_addw);
		if (eww) {
			mtk_v4w2_vdec_eww(ctx, "faiwed to awwocate wdma_eww_addw buf[%d]", i);
			goto mem_awwoc_eww;
		}

		wat_buf->swice_bc_addw.size = VDEC_WAT_SWICE_HEADEW_SZ;
		eww = mtk_vcodec_mem_awwoc(ctx, &wat_buf->swice_bc_addw);
		if (eww) {
			mtk_v4w2_vdec_eww(ctx, "faiwed to awwocate wdma_addw buf[%d]", i);
			goto mem_awwoc_eww;
		}

		if (ctx->cuwwent_codec == V4W2_PIX_FMT_AV1_FWAME) {
			wat_buf->wd_mv_addw.size = VDEC_WD_MV_BUFFEW_SZ;
			eww = mtk_vcodec_mem_awwoc(ctx, &wat_buf->wd_mv_addw);
			if (eww) {
				mtk_v4w2_vdec_eww(ctx, "faiwed to awwocate wd_mv_addw buf[%d]", i);
				goto mem_awwoc_eww;
			}

			wat_buf->tiwe_addw.size = VDEC_WAT_TIWE_SZ;
			eww = mtk_vcodec_mem_awwoc(ctx, &wat_buf->tiwe_addw);
			if (eww) {
				mtk_v4w2_vdec_eww(ctx, "faiwed to awwocate tiwe_addw buf[%d]", i);
				goto mem_awwoc_eww;
			}
		}

		wat_buf->pwivate_data = kzawwoc(pwivate_size, GFP_KEWNEW);
		if (!wat_buf->pwivate_data) {
			eww = -ENOMEM;
			goto mem_awwoc_eww;
		}

		wat_buf->ctx = ctx;
		wat_buf->cowe_decode = cowe_decode;
		wat_buf->is_wast_fwame = fawse;
		eww = vdec_msg_queue_qbuf(&msg_queue->wat_ctx, wat_buf);
		if (eww) {
			mtk_v4w2_vdec_eww(ctx, "faiwed to qbuf buf[%d]", i);
			goto mem_awwoc_eww;
		}
	}
	wetuwn 0;

mem_awwoc_eww:
	vdec_msg_queue_deinit(msg_queue, ctx);
	wetuwn eww;
}
