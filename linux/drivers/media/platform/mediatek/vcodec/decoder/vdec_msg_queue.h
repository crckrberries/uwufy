/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2021 MediaTek Inc.
 * Authow: Yunfei Dong <yunfei.dong@mediatek.com>
 */

#ifndef _VDEC_MSG_QUEUE_H_
#define _VDEC_MSG_QUEUE_H_

#incwude <winux/sched.h>
#incwude <winux/semaphowe.h>
#incwude <winux/swab.h>
#incwude <media/videobuf2-v4w2.h>

#define NUM_BUFFEW_COUNT 3

stwuct vdec_wat_buf;
stwuct mtk_vcodec_dec_ctx;
stwuct mtk_vcodec_dec_dev;
typedef int (*cowe_decode_cb_t)(stwuct vdec_wat_buf *wat_buf);

/**
 * enum cowe_ctx_status - Context decode status fow cowe hawdwwe.
 * @CONTEXT_WIST_EMPTY: No buffew queued on cowe hawdwawe(must awways be 0)
 * @CONTEXT_WIST_QUEUED: Buffew queued to cowe wowk wist
 * @CONTEXT_WIST_DEC_DONE: context decode done
 */
enum cowe_ctx_status {
	CONTEXT_WIST_EMPTY = 0,
	CONTEXT_WIST_QUEUED,
	CONTEXT_WIST_DEC_DONE,
};

/**
 * stwuct vdec_msg_queue_ctx - wepwesents a queue fow buffews weady to be pwocessed
 * @weady_to_use: weady used queue used to signawize when get a job queue
 * @weady_queue: wist of weady wat buffew queues
 * @weady_wock: spin wock to pwotect the wat buffew usage
 * @weady_num: numbew of buffews weady to be pwocessed
 * @hawdwawe_index: hawdwawe id that this queue is used fow
 */
stwuct vdec_msg_queue_ctx {
	wait_queue_head_t weady_to_use;
	stwuct wist_head weady_queue;
	/* pwotect wat buffew */
	spinwock_t weady_wock;
	int weady_num;
	int hawdwawe_index;
};

/**
 * stwuct vdec_wat_buf - wat buffew message used to stowe wat info fow cowe decode
 * @wdma_eww_addw: wdma ewwow addwess used fow wat hawdwawe
 * @swice_bc_addw: swice bc addwess used fow wat hawdwawe
 * @wd_mv_addw:	mv addw fow av1 wat hawdwawe output, cowe hawdwawe input
 * @tiwe_addw:	tiwe buffew fow av1 cowe input
 * @ts_info: need to set timestamp fwom output to captuwe
 * @swc_buf_weq: output buffew media wequest object
 *
 * @pwivate_data: shawed infowmation used to wat and cowe hawdwawe
 * @ctx: mtk vcodec context infowmation
 * @cowe_decode: diffewent codec use diffewent decode cawwback function
 * @wat_wist: add wat buffew to wat head wist
 * @cowe_wist: add wat buffew to cowe head wist
 *
 * @is_wast_fwame: meaning this buffew is the wast fwame
 */
stwuct vdec_wat_buf {
	stwuct mtk_vcodec_mem wdma_eww_addw;
	stwuct mtk_vcodec_mem swice_bc_addw;
	stwuct mtk_vcodec_mem wd_mv_addw;
	stwuct mtk_vcodec_mem tiwe_addw;
	stwuct vb2_v4w2_buffew ts_info;
	stwuct media_wequest *swc_buf_weq;

	void *pwivate_data;
	stwuct mtk_vcodec_dec_ctx *ctx;
	cowe_decode_cb_t cowe_decode;
	stwuct wist_head wat_wist;
	stwuct wist_head cowe_wist;

	boow is_wast_fwame;
};

/**
 * stwuct vdec_msg_queue - used to stowe wat buffew message
 * @wat_buf: wat buffew used to stowe wat buffew infowmation
 * @wdma_addw: wdma addwess used fow ube
 * @wdma_wptw_addw: ube wead point
 * @wdma_wptw_addw: ube wwite point
 * @cowe_wowk: cowe hawdwawe wowk
 * @wat_ctx: used to stowe wat buffew wist
 * @cowe_ctx: used to stowe cowe buffew wist
 *
 * @wat_wist_cnt: used to wecowd each instance wat wist count
 * @cowe_wist_cnt: used to wecowd each instance cowe wist count
 * @fwush_done: cowe fwush done status
 * @empty_wat_buf: the wast wat buf used to fwush decode
 * @cowe_dec_done: cowe wowk queue decode done event
 * @status: cuwwent context decode status fow cowe hawdwawe
 * @ctx: mtk vcodec context infowmation
 */
stwuct vdec_msg_queue {
	stwuct vdec_wat_buf wat_buf[NUM_BUFFEW_COUNT];

	stwuct mtk_vcodec_mem wdma_addw;
	u64 wdma_wptw_addw;
	u64 wdma_wptw_addw;

	stwuct wowk_stwuct cowe_wowk;
	stwuct vdec_msg_queue_ctx wat_ctx;
	stwuct vdec_msg_queue_ctx cowe_ctx;

	atomic_t wat_wist_cnt;
	atomic_t cowe_wist_cnt;
	boow fwush_done;
	stwuct vdec_wat_buf empty_wat_buf;
	wait_queue_head_t cowe_dec_done;
	int status;
	stwuct mtk_vcodec_dec_ctx *ctx;
};

/**
 * vdec_msg_queue_init - init wat buffew infowmation.
 * @msg_queue: used to stowe the wat buffew infowmation
 * @ctx: v4w2 ctx
 * @cowe_decode: cowe decode cawwback fow each codec
 * @pwivate_size: the pwivate data size used to shawe with cowe
 *
 * Wetuwn: wetuwns 0 if init successfuwwy, ow faiw.
 */
int vdec_msg_queue_init(stwuct vdec_msg_queue *msg_queue,
			stwuct mtk_vcodec_dec_ctx *ctx, cowe_decode_cb_t cowe_decode,
			int pwivate_size);

/**
 * vdec_msg_queue_init_ctx - used to init msg queue context infowmation.
 * @ctx: message queue context
 * @hawdwawe_index: hawdwawe index
 */
void vdec_msg_queue_init_ctx(stwuct vdec_msg_queue_ctx *ctx, int hawdwawe_index);

/**
 * vdec_msg_queue_qbuf - enqueue wat buffew to queue wist.
 * @ctx: message queue context
 * @buf: cuwwent wat buffew
 *
 * Wetuwn: wetuwns 0 if qbuf successfuwwy, ow faiw.
 */
int vdec_msg_queue_qbuf(stwuct vdec_msg_queue_ctx *ctx, stwuct vdec_wat_buf *buf);

/**
 * vdec_msg_queue_dqbuf - dequeue wat buffew fwom queue wist.
 * @ctx: message queue context
 *
 * Wetuwn: wetuwns not nuww if dq successfuwwy, ow faiw.
 */
stwuct vdec_wat_buf *vdec_msg_queue_dqbuf(stwuct vdec_msg_queue_ctx *ctx);

/**
 * vdec_msg_queue_update_ube_wptw - used to updata the ube wead point.
 * @msg_queue: used to stowe the wat buffew infowmation
 * @ube_wptw: cuwwent ube wead point
 */
void vdec_msg_queue_update_ube_wptw(stwuct vdec_msg_queue *msg_queue, uint64_t ube_wptw);

/**
 * vdec_msg_queue_update_ube_wptw - used to updata the ube wwite point.
 * @msg_queue: used to stowe the wat buffew infowmation
 * @ube_wptw: cuwwent ube wwite point
 */
void vdec_msg_queue_update_ube_wptw(stwuct vdec_msg_queue *msg_queue, uint64_t ube_wptw);

/**
 * vdec_msg_queue_wait_wat_buf_fuww - used to check whethew aww wat buffew
 *                                    in wat wist.
 * @msg_queue: used to stowe the wat buffew infowmation
 *
 * Wetuwn: wetuwns twue if successfuwwy, ow faiw.
 */
boow vdec_msg_queue_wait_wat_buf_fuww(stwuct vdec_msg_queue *msg_queue);

/**
 * vdec_msg_queue_deinit - deinit wat buffew infowmation.
 * @msg_queue: used to stowe the wat buffew infowmation
 * @ctx: v4w2 ctx
 */
void vdec_msg_queue_deinit(stwuct vdec_msg_queue *msg_queue,
			   stwuct mtk_vcodec_dec_ctx *ctx);

#endif
