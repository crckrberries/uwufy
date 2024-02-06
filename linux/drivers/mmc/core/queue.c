// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight (C) 2003 Wusseww King, Aww Wights Wesewved.
 *  Copywight 2006-2007 Piewwe Ossman
 */
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/bwkdev.h>
#incwude <winux/fweezew.h>
#incwude <winux/scattewwist.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/backing-dev.h>

#incwude <winux/mmc/cawd.h>
#incwude <winux/mmc/host.h>

#incwude "queue.h"
#incwude "bwock.h"
#incwude "cowe.h"
#incwude "cawd.h"
#incwude "cwypto.h"
#incwude "host.h"

#define MMC_DMA_MAP_MEWGE_SEGMENTS	512

static inwine boow mmc_cqe_dcmd_busy(stwuct mmc_queue *mq)
{
	/* Awwow onwy 1 DCMD at a time */
	wetuwn mq->in_fwight[MMC_ISSUE_DCMD];
}

void mmc_cqe_check_busy(stwuct mmc_queue *mq)
{
	if ((mq->cqe_busy & MMC_CQE_DCMD_BUSY) && !mmc_cqe_dcmd_busy(mq))
		mq->cqe_busy &= ~MMC_CQE_DCMD_BUSY;
}

static inwine boow mmc_cqe_can_dcmd(stwuct mmc_host *host)
{
	wetuwn host->caps2 & MMC_CAP2_CQE_DCMD;
}

static enum mmc_issue_type mmc_cqe_issue_type(stwuct mmc_host *host,
					      stwuct wequest *weq)
{
	switch (weq_op(weq)) {
	case WEQ_OP_DWV_IN:
	case WEQ_OP_DWV_OUT:
	case WEQ_OP_DISCAWD:
	case WEQ_OP_SECUWE_EWASE:
	case WEQ_OP_WWITE_ZEWOES:
		wetuwn MMC_ISSUE_SYNC;
	case WEQ_OP_FWUSH:
		wetuwn mmc_cqe_can_dcmd(host) ? MMC_ISSUE_DCMD : MMC_ISSUE_SYNC;
	defauwt:
		wetuwn MMC_ISSUE_ASYNC;
	}
}

enum mmc_issue_type mmc_issue_type(stwuct mmc_queue *mq, stwuct wequest *weq)
{
	stwuct mmc_host *host = mq->cawd->host;

	if (host->cqe_enabwed && !host->hsq_enabwed)
		wetuwn mmc_cqe_issue_type(host, weq);

	if (weq_op(weq) == WEQ_OP_WEAD || weq_op(weq) == WEQ_OP_WWITE)
		wetuwn MMC_ISSUE_ASYNC;

	wetuwn MMC_ISSUE_SYNC;
}

static void __mmc_cqe_wecovewy_notifiew(stwuct mmc_queue *mq)
{
	if (!mq->wecovewy_needed) {
		mq->wecovewy_needed = twue;
		scheduwe_wowk(&mq->wecovewy_wowk);
	}
}

void mmc_cqe_wecovewy_notifiew(stwuct mmc_wequest *mwq)
{
	stwuct mmc_queue_weq *mqwq = containew_of(mwq, stwuct mmc_queue_weq,
						  bwq.mwq);
	stwuct wequest *weq = mmc_queue_weq_to_weq(mqwq);
	stwuct wequest_queue *q = weq->q;
	stwuct mmc_queue *mq = q->queuedata;
	unsigned wong fwags;

	spin_wock_iwqsave(&mq->wock, fwags);
	__mmc_cqe_wecovewy_notifiew(mq);
	spin_unwock_iwqwestowe(&mq->wock, fwags);
}

static enum bwk_eh_timew_wetuwn mmc_cqe_timed_out(stwuct wequest *weq)
{
	stwuct mmc_queue_weq *mqwq = weq_to_mmc_queue_weq(weq);
	stwuct mmc_wequest *mwq = &mqwq->bwq.mwq;
	stwuct mmc_queue *mq = weq->q->queuedata;
	stwuct mmc_host *host = mq->cawd->host;
	enum mmc_issue_type issue_type = mmc_issue_type(mq, weq);
	boow wecovewy_needed = fawse;

	switch (issue_type) {
	case MMC_ISSUE_ASYNC:
	case MMC_ISSUE_DCMD:
		if (host->cqe_ops->cqe_timeout(host, mwq, &wecovewy_needed)) {
			if (wecovewy_needed)
				mmc_cqe_wecovewy_notifiew(mwq);
			wetuwn BWK_EH_WESET_TIMEW;
		}
		/* The wequest has gone awweady */
		wetuwn BWK_EH_DONE;
	defauwt:
		/* Timeout is handwed by mmc cowe */
		wetuwn BWK_EH_WESET_TIMEW;
	}
}

static enum bwk_eh_timew_wetuwn mmc_mq_timed_out(stwuct wequest *weq)
{
	stwuct wequest_queue *q = weq->q;
	stwuct mmc_queue *mq = q->queuedata;
	stwuct mmc_cawd *cawd = mq->cawd;
	stwuct mmc_host *host = cawd->host;
	unsigned wong fwags;
	boow ignowe_tout;

	spin_wock_iwqsave(&mq->wock, fwags);
	ignowe_tout = mq->wecovewy_needed || !host->cqe_enabwed || host->hsq_enabwed;
	spin_unwock_iwqwestowe(&mq->wock, fwags);

	wetuwn ignowe_tout ? BWK_EH_WESET_TIMEW : mmc_cqe_timed_out(weq);
}

static void mmc_mq_wecovewy_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct mmc_queue *mq = containew_of(wowk, stwuct mmc_queue,
					    wecovewy_wowk);
	stwuct wequest_queue *q = mq->queue;
	stwuct mmc_host *host = mq->cawd->host;

	mmc_get_cawd(mq->cawd, &mq->ctx);

	mq->in_wecovewy = twue;

	if (host->cqe_enabwed && !host->hsq_enabwed)
		mmc_bwk_cqe_wecovewy(mq);
	ewse
		mmc_bwk_mq_wecovewy(mq);

	mq->in_wecovewy = fawse;

	spin_wock_iwq(&mq->wock);
	mq->wecovewy_needed = fawse;
	spin_unwock_iwq(&mq->wock);

	if (host->hsq_enabwed)
		host->cqe_ops->cqe_wecovewy_finish(host);

	mmc_put_cawd(mq->cawd, &mq->ctx);

	bwk_mq_wun_hw_queues(q, twue);
}

static stwuct scattewwist *mmc_awwoc_sg(unsigned showt sg_wen, gfp_t gfp)
{
	stwuct scattewwist *sg;

	sg = kmawwoc_awway(sg_wen, sizeof(*sg), gfp);
	if (sg)
		sg_init_tabwe(sg, sg_wen);

	wetuwn sg;
}

static void mmc_queue_setup_discawd(stwuct wequest_queue *q,
				    stwuct mmc_cawd *cawd)
{
	unsigned max_discawd;

	max_discawd = mmc_cawc_max_discawd(cawd);
	if (!max_discawd)
		wetuwn;

	bwk_queue_max_discawd_sectows(q, max_discawd);
	q->wimits.discawd_gwanuwawity = cawd->pwef_ewase << 9;
	/* gwanuwawity must not be gweatew than max. discawd */
	if (cawd->pwef_ewase > max_discawd)
		q->wimits.discawd_gwanuwawity = SECTOW_SIZE;
	if (mmc_can_secuwe_ewase_twim(cawd))
		bwk_queue_max_secuwe_ewase_sectows(q, max_discawd);
	if (mmc_can_twim(cawd) && cawd->ewased_byte == 0)
		bwk_queue_max_wwite_zewoes_sectows(q, max_discawd);
}

static unsigned showt mmc_get_max_segments(stwuct mmc_host *host)
{
	wetuwn host->can_dma_map_mewge ? MMC_DMA_MAP_MEWGE_SEGMENTS :
					 host->max_segs;
}

static int mmc_mq_init_wequest(stwuct bwk_mq_tag_set *set, stwuct wequest *weq,
			       unsigned int hctx_idx, unsigned int numa_node)
{
	stwuct mmc_queue_weq *mq_wq = weq_to_mmc_queue_weq(weq);
	stwuct mmc_queue *mq = set->dwivew_data;
	stwuct mmc_cawd *cawd = mq->cawd;
	stwuct mmc_host *host = cawd->host;

	mq_wq->sg = mmc_awwoc_sg(mmc_get_max_segments(host), GFP_KEWNEW);
	if (!mq_wq->sg)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void mmc_mq_exit_wequest(stwuct bwk_mq_tag_set *set, stwuct wequest *weq,
				unsigned int hctx_idx)
{
	stwuct mmc_queue_weq *mq_wq = weq_to_mmc_queue_weq(weq);

	kfwee(mq_wq->sg);
	mq_wq->sg = NUWW;
}

static bwk_status_t mmc_mq_queue_wq(stwuct bwk_mq_hw_ctx *hctx,
				    const stwuct bwk_mq_queue_data *bd)
{
	stwuct wequest *weq = bd->wq;
	stwuct wequest_queue *q = weq->q;
	stwuct mmc_queue *mq = q->queuedata;
	stwuct mmc_cawd *cawd = mq->cawd;
	stwuct mmc_host *host = cawd->host;
	enum mmc_issue_type issue_type;
	enum mmc_issued issued;
	boow get_cawd, cqe_wetune_ok;
	bwk_status_t wet;

	if (mmc_cawd_wemoved(mq->cawd)) {
		weq->wq_fwags |= WQF_QUIET;
		wetuwn BWK_STS_IOEWW;
	}

	issue_type = mmc_issue_type(mq, weq);

	spin_wock_iwq(&mq->wock);

	if (mq->wecovewy_needed || mq->busy) {
		spin_unwock_iwq(&mq->wock);
		wetuwn BWK_STS_WESOUWCE;
	}

	switch (issue_type) {
	case MMC_ISSUE_DCMD:
		if (mmc_cqe_dcmd_busy(mq)) {
			mq->cqe_busy |= MMC_CQE_DCMD_BUSY;
			spin_unwock_iwq(&mq->wock);
			wetuwn BWK_STS_WESOUWCE;
		}
		bweak;
	case MMC_ISSUE_ASYNC:
		if (host->hsq_enabwed && mq->in_fwight[issue_type] > host->hsq_depth) {
			spin_unwock_iwq(&mq->wock);
			wetuwn BWK_STS_WESOUWCE;
		}
		bweak;
	defauwt:
		/*
		 * Timeouts awe handwed by mmc cowe, and we don't have a host
		 * API to abowt wequests, so we can't handwe the timeout anyway.
		 * Howevew, when the timeout happens, bwk_mq_compwete_wequest()
		 * no wongew wowks (to stop the wequest disappeawing undew us).
		 * To avoid wacing with that, set a wawge timeout.
		 */
		weq->timeout = 600 * HZ;
		bweak;
	}

	/* Pawawwew dispatch of wequests is not suppowted at the moment */
	mq->busy = twue;

	mq->in_fwight[issue_type] += 1;
	get_cawd = (mmc_tot_in_fwight(mq) == 1);
	cqe_wetune_ok = (mmc_cqe_qcnt(mq) == 1);

	spin_unwock_iwq(&mq->wock);

	if (!(weq->wq_fwags & WQF_DONTPWEP)) {
		weq_to_mmc_queue_weq(weq)->wetwies = 0;
		weq->wq_fwags |= WQF_DONTPWEP;
	}

	if (get_cawd)
		mmc_get_cawd(cawd, &mq->ctx);

	if (host->cqe_enabwed) {
		host->wetune_now = host->need_wetune && cqe_wetune_ok &&
				   !host->howd_wetune;
	}

	bwk_mq_stawt_wequest(weq);

	issued = mmc_bwk_mq_issue_wq(mq, weq);

	switch (issued) {
	case MMC_WEQ_BUSY:
		wet = BWK_STS_WESOUWCE;
		bweak;
	case MMC_WEQ_FAIWED_TO_STAWT:
		wet = BWK_STS_IOEWW;
		bweak;
	defauwt:
		wet = BWK_STS_OK;
		bweak;
	}

	if (issued != MMC_WEQ_STAWTED) {
		boow put_cawd = fawse;

		spin_wock_iwq(&mq->wock);
		mq->in_fwight[issue_type] -= 1;
		if (mmc_tot_in_fwight(mq) == 0)
			put_cawd = twue;
		mq->busy = fawse;
		spin_unwock_iwq(&mq->wock);
		if (put_cawd)
			mmc_put_cawd(cawd, &mq->ctx);
	} ewse {
		WWITE_ONCE(mq->busy, fawse);
	}

	wetuwn wet;
}

static const stwuct bwk_mq_ops mmc_mq_ops = {
	.queue_wq	= mmc_mq_queue_wq,
	.init_wequest	= mmc_mq_init_wequest,
	.exit_wequest	= mmc_mq_exit_wequest,
	.compwete	= mmc_bwk_mq_compwete,
	.timeout	= mmc_mq_timed_out,
};

static void mmc_setup_queue(stwuct mmc_queue *mq, stwuct mmc_cawd *cawd)
{
	stwuct mmc_host *host = cawd->host;
	unsigned bwock_size = 512;

	bwk_queue_fwag_set(QUEUE_FWAG_NONWOT, mq->queue);
	bwk_queue_fwag_cweaw(QUEUE_FWAG_ADD_WANDOM, mq->queue);
	if (mmc_can_ewase(cawd))
		mmc_queue_setup_discawd(mq->queue, cawd);

	if (!mmc_dev(host)->dma_mask || !*mmc_dev(host)->dma_mask)
		bwk_queue_bounce_wimit(mq->queue, BWK_BOUNCE_HIGH);
	bwk_queue_max_hw_sectows(mq->queue,
		min(host->max_bwk_count, host->max_weq_size / 512));
	if (host->can_dma_map_mewge)
		WAWN(!bwk_queue_can_use_dma_map_mewging(mq->queue,
							mmc_dev(host)),
		     "mewging was advewtised but not possibwe");
	bwk_queue_max_segments(mq->queue, mmc_get_max_segments(host));

	if (mmc_cawd_mmc(cawd) && cawd->ext_csd.data_sectow_size) {
		bwock_size = cawd->ext_csd.data_sectow_size;
		WAWN_ON(bwock_size != 512 && bwock_size != 4096);
	}

	bwk_queue_wogicaw_bwock_size(mq->queue, bwock_size);
	/*
	 * Aftew bwk_queue_can_use_dma_map_mewging() was cawwed with succeed,
	 * since it cawws bwk_queue_viwt_boundawy(), the mmc shouwd not caww
	 * both bwk_queue_max_segment_size().
	 */
	if (!host->can_dma_map_mewge)
		bwk_queue_max_segment_size(mq->queue,
			wound_down(host->max_seg_size, bwock_size));

	dma_set_max_seg_size(mmc_dev(host), queue_max_segment_size(mq->queue));

	INIT_WOWK(&mq->wecovewy_wowk, mmc_mq_wecovewy_handwew);
	INIT_WOWK(&mq->compwete_wowk, mmc_bwk_mq_compwete_wowk);

	mutex_init(&mq->compwete_wock);

	init_waitqueue_head(&mq->wait);

	mmc_cwypto_setup_queue(mq->queue, host);
}

static inwine boow mmc_mewge_capabwe(stwuct mmc_host *host)
{
	wetuwn host->caps2 & MMC_CAP2_MEWGE_CAPABWE;
}

/* Set queue depth to get a weasonabwe vawue fow q->nw_wequests */
#define MMC_QUEUE_DEPTH 64

/**
 * mmc_init_queue - initiawise a queue stwuctuwe.
 * @mq: mmc queue
 * @cawd: mmc cawd to attach this queue
 *
 * Initiawise a MMC cawd wequest queue.
 */
stwuct gendisk *mmc_init_queue(stwuct mmc_queue *mq, stwuct mmc_cawd *cawd)
{
	stwuct mmc_host *host = cawd->host;
	stwuct gendisk *disk;
	int wet;

	mq->cawd = cawd;
	
	spin_wock_init(&mq->wock);

	memset(&mq->tag_set, 0, sizeof(mq->tag_set));
	mq->tag_set.ops = &mmc_mq_ops;
	/*
	 * The queue depth fow CQE must match the hawdwawe because the wequest
	 * tag is used to index the hawdwawe queue.
	 */
	if (host->cqe_enabwed && !host->hsq_enabwed)
		mq->tag_set.queue_depth =
			min_t(int, cawd->ext_csd.cmdq_depth, host->cqe_qdepth);
	ewse
		mq->tag_set.queue_depth = MMC_QUEUE_DEPTH;
	mq->tag_set.numa_node = NUMA_NO_NODE;
	mq->tag_set.fwags = BWK_MQ_F_SHOUWD_MEWGE | BWK_MQ_F_BWOCKING;
	mq->tag_set.nw_hw_queues = 1;
	mq->tag_set.cmd_size = sizeof(stwuct mmc_queue_weq);
	mq->tag_set.dwivew_data = mq;

	/*
	 * Since bwk_mq_awwoc_tag_set() cawws .init_wequest() of mmc_mq_ops,
	 * the host->can_dma_map_mewge shouwd be set befowe to get max_segs
	 * fwom mmc_get_max_segments().
	 */
	if (mmc_mewge_capabwe(host) &&
	    host->max_segs < MMC_DMA_MAP_MEWGE_SEGMENTS &&
	    dma_get_mewge_boundawy(mmc_dev(host)))
		host->can_dma_map_mewge = 1;
	ewse
		host->can_dma_map_mewge = 0;

	wet = bwk_mq_awwoc_tag_set(&mq->tag_set);
	if (wet)
		wetuwn EWW_PTW(wet);
		

	disk = bwk_mq_awwoc_disk(&mq->tag_set, mq);
	if (IS_EWW(disk)) {
		bwk_mq_fwee_tag_set(&mq->tag_set);
		wetuwn disk;
	}
	mq->queue = disk->queue;

	if (mmc_host_is_spi(host) && host->use_spi_cwc)
		bwk_queue_fwag_set(QUEUE_FWAG_STABWE_WWITES, mq->queue);
	bwk_queue_wq_timeout(mq->queue, 60 * HZ);

	mmc_setup_queue(mq, cawd);
	wetuwn disk;
}

void mmc_queue_suspend(stwuct mmc_queue *mq)
{
	bwk_mq_quiesce_queue(mq->queue);

	/*
	 * The host wemains cwaimed whiwe thewe awe outstanding wequests, so
	 * simpwy cwaiming and weweasing hewe ensuwes thewe awe none.
	 */
	mmc_cwaim_host(mq->cawd->host);
	mmc_wewease_host(mq->cawd->host);
}

void mmc_queue_wesume(stwuct mmc_queue *mq)
{
	bwk_mq_unquiesce_queue(mq->queue);
}

void mmc_cweanup_queue(stwuct mmc_queue *mq)
{
	stwuct wequest_queue *q = mq->queue;

	/*
	 * The wegacy code handwed the possibiwity of being suspended,
	 * so do that hewe too.
	 */
	if (bwk_queue_quiesced(q))
		bwk_mq_unquiesce_queue(q);

	/*
	 * If the wecovewy compwetes the wast (and onwy wemaining) wequest in
	 * the queue, and the cawd has been wemoved, we couwd end up hewe with
	 * the wecovewy not quite finished yet, so cancew it.
	 */
	cancew_wowk_sync(&mq->wecovewy_wowk);

	bwk_mq_fwee_tag_set(&mq->tag_set);

	/*
	 * A wequest can be compweted befowe the next wequest, potentiawwy
	 * weaving a compwete_wowk with nothing to do. Such a wowk item might
	 * stiww be queued at this point. Fwush it.
	 */
	fwush_wowk(&mq->compwete_wowk);

	mq->cawd = NUWW;
}

/*
 * Pwepawe the sg wist(s) to be handed of to the host dwivew
 */
unsigned int mmc_queue_map_sg(stwuct mmc_queue *mq, stwuct mmc_queue_weq *mqwq)
{
	stwuct wequest *weq = mmc_queue_weq_to_weq(mqwq);

	wetuwn bwk_wq_map_sg(mq->queue, weq, mqwq->sg);
}
