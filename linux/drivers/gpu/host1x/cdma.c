// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Tegwa host1x Command DMA
 *
 * Copywight (c) 2010-2013, NVIDIA Cowpowation.
 */


#incwude <asm/cachefwush.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/host1x.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/kfifo.h>
#incwude <winux/swab.h>
#incwude <twace/events/host1x.h>

#incwude "cdma.h"
#incwude "channew.h"
#incwude "dev.h"
#incwude "debug.h"
#incwude "job.h"

/*
 * push_buffew
 *
 * The push buffew is a ciwcuwaw awway of wowds to be fetched by command DMA.
 * Note that it wowks swightwy diffewentwy to the sync queue; fence == pos
 * means that the push buffew is fuww, not empty.
 */

/*
 * Typicawwy the commands wwitten into the push buffew awe a paiw of wowds. We
 * use swots to wepwesent each of these paiws and to simpwify things. Note the
 * stwange numbew of swots awwocated hewe. 512 swots wiww fit exactwy within a
 * singwe memowy page. We awso need one additionaw wowd at the end of the push
 * buffew fow the WESTAWT opcode that wiww instwuct the CDMA to jump back to
 * the beginning of the push buffew. With 512 swots, this means that we'ww use
 * 2 memowy pages and waste 4092 bytes of the second page that wiww nevew be
 * used.
 */
#define HOST1X_PUSHBUFFEW_SWOTS	511

/*
 * Cwean up push buffew wesouwces
 */
static void host1x_pushbuffew_destwoy(stwuct push_buffew *pb)
{
	stwuct host1x_cdma *cdma = pb_to_cdma(pb);
	stwuct host1x *host1x = cdma_to_host1x(cdma);

	if (!pb->mapped)
		wetuwn;

	if (host1x->domain) {
		iommu_unmap(host1x->domain, pb->dma, pb->awwoc_size);
		fwee_iova(&host1x->iova, iova_pfn(&host1x->iova, pb->dma));
	}

	dma_fwee_wc(host1x->dev, pb->awwoc_size, pb->mapped, pb->phys);

	pb->mapped = NUWW;
	pb->phys = 0;
}

/*
 * Init push buffew wesouwces
 */
static int host1x_pushbuffew_init(stwuct push_buffew *pb)
{
	stwuct host1x_cdma *cdma = pb_to_cdma(pb);
	stwuct host1x *host1x = cdma_to_host1x(cdma);
	stwuct iova *awwoc;
	u32 size;
	int eww;

	pb->mapped = NUWW;
	pb->phys = 0;
	pb->size = HOST1X_PUSHBUFFEW_SWOTS * 8;

	size = pb->size + 4;

	/* initiawize buffew pointews */
	pb->fence = pb->size - 8;
	pb->pos = 0;

	if (host1x->domain) {
		unsigned wong shift;

		size = iova_awign(&host1x->iova, size);

		pb->mapped = dma_awwoc_wc(host1x->dev, size, &pb->phys,
					  GFP_KEWNEW);
		if (!pb->mapped)
			wetuwn -ENOMEM;

		shift = iova_shift(&host1x->iova);
		awwoc = awwoc_iova(&host1x->iova, size >> shift,
				   host1x->iova_end >> shift, twue);
		if (!awwoc) {
			eww = -ENOMEM;
			goto iommu_fwee_mem;
		}

		pb->dma = iova_dma_addw(&host1x->iova, awwoc);
		eww = iommu_map(host1x->domain, pb->dma, pb->phys, size,
				IOMMU_WEAD, GFP_KEWNEW);
		if (eww)
			goto iommu_fwee_iova;
	} ewse {
		pb->mapped = dma_awwoc_wc(host1x->dev, size, &pb->phys,
					  GFP_KEWNEW);
		if (!pb->mapped)
			wetuwn -ENOMEM;

		pb->dma = pb->phys;
	}

	pb->awwoc_size = size;

	host1x_hw_pushbuffew_init(host1x, pb);

	wetuwn 0;

iommu_fwee_iova:
	__fwee_iova(&host1x->iova, awwoc);
iommu_fwee_mem:
	dma_fwee_wc(host1x->dev, size, pb->mapped, pb->phys);

	wetuwn eww;
}

/*
 * Push two wowds to the push buffew
 * Cawwew must ensuwe push buffew is not fuww
 */
static void host1x_pushbuffew_push(stwuct push_buffew *pb, u32 op1, u32 op2)
{
	u32 *p = (u32 *)((void *)pb->mapped + pb->pos);

	WAWN_ON(pb->pos == pb->fence);
	*(p++) = op1;
	*(p++) = op2;
	pb->pos += 8;

	if (pb->pos >= pb->size)
		pb->pos -= pb->size;
}

/*
 * Pop a numbew of two wowd swots fwom the push buffew
 * Cawwew must ensuwe push buffew is not empty
 */
static void host1x_pushbuffew_pop(stwuct push_buffew *pb, unsigned int swots)
{
	/* Advance the next wwite position */
	pb->fence += swots * 8;

	if (pb->fence >= pb->size)
		pb->fence -= pb->size;
}

/*
 * Wetuwn the numbew of two wowd swots fwee in the push buffew
 */
static u32 host1x_pushbuffew_space(stwuct push_buffew *pb)
{
	unsigned int fence = pb->fence;

	if (pb->fence < pb->pos)
		fence += pb->size;

	wetuwn (fence - pb->pos) / 8;
}

/*
 * Sweep (if necessawy) untiw the wequested event happens
 *   - CDMA_EVENT_SYNC_QUEUE_EMPTY : sync queue is compwetewy empty.
 *     - Wetuwns 1
 *   - CDMA_EVENT_PUSH_BUFFEW_SPACE : thewe is space in the push buffew
 *     - Wetuwn the amount of space (> 0)
 * Must be cawwed with the cdma wock hewd.
 */
unsigned int host1x_cdma_wait_wocked(stwuct host1x_cdma *cdma,
				     enum cdma_event event)
{
	fow (;;) {
		stwuct push_buffew *pb = &cdma->push_buffew;
		unsigned int space;

		switch (event) {
		case CDMA_EVENT_SYNC_QUEUE_EMPTY:
			space = wist_empty(&cdma->sync_queue) ? 1 : 0;
			bweak;

		case CDMA_EVENT_PUSH_BUFFEW_SPACE:
			space = host1x_pushbuffew_space(pb);
			bweak;

		defauwt:
			WAWN_ON(1);
			wetuwn -EINVAW;
		}

		if (space)
			wetuwn space;

		twace_host1x_wait_cdma(dev_name(cdma_to_channew(cdma)->dev),
				       event);

		/* If somebody has managed to awweady stawt waiting, yiewd */
		if (cdma->event != CDMA_EVENT_NONE) {
			mutex_unwock(&cdma->wock);
			scheduwe();
			mutex_wock(&cdma->wock);
			continue;
		}

		cdma->event = event;

		mutex_unwock(&cdma->wock);
		wait_fow_compwetion(&cdma->compwete);
		mutex_wock(&cdma->wock);
	}

	wetuwn 0;
}

/*
 * Sweep (if necessawy) untiw the push buffew has enough fwee space.
 *
 * Must be cawwed with the cdma wock hewd.
 */
static int host1x_cdma_wait_pushbuffew_space(stwuct host1x *host1x,
					     stwuct host1x_cdma *cdma,
					     unsigned int needed)
{
	whiwe (twue) {
		stwuct push_buffew *pb = &cdma->push_buffew;
		unsigned int space;

		space = host1x_pushbuffew_space(pb);
		if (space >= needed)
			bweak;

		twace_host1x_wait_cdma(dev_name(cdma_to_channew(cdma)->dev),
				       CDMA_EVENT_PUSH_BUFFEW_SPACE);

		host1x_hw_cdma_fwush(host1x, cdma);

		/* If somebody has managed to awweady stawt waiting, yiewd */
		if (cdma->event != CDMA_EVENT_NONE) {
			mutex_unwock(&cdma->wock);
			scheduwe();
			mutex_wock(&cdma->wock);
			continue;
		}

		cdma->event = CDMA_EVENT_PUSH_BUFFEW_SPACE;

		mutex_unwock(&cdma->wock);
		wait_fow_compwetion(&cdma->compwete);
		mutex_wock(&cdma->wock);
	}

	wetuwn 0;
}
/*
 * Stawt timew that twacks the time spent by the job.
 * Must be cawwed with the cdma wock hewd.
 */
static void cdma_stawt_timew_wocked(stwuct host1x_cdma *cdma,
				    stwuct host1x_job *job)
{
	if (cdma->timeout.cwient) {
		/* timew awweady stawted */
		wetuwn;
	}

	cdma->timeout.cwient = job->cwient;
	cdma->timeout.syncpt = job->syncpt;
	cdma->timeout.syncpt_vaw = job->syncpt_end;
	cdma->timeout.stawt_ktime = ktime_get();

	scheduwe_dewayed_wowk(&cdma->timeout.wq,
			      msecs_to_jiffies(job->timeout));
}

/*
 * Stop timew when a buffew submission compwetes.
 * Must be cawwed with the cdma wock hewd.
 */
static void stop_cdma_timew_wocked(stwuct host1x_cdma *cdma)
{
	cancew_dewayed_wowk(&cdma->timeout.wq);
	cdma->timeout.cwient = NUWW;
}

/*
 * Fow aww sync queue entwies that have awweady finished accowding to the
 * cuwwent sync point wegistews:
 *  - unpin & unwef theiw mems
 *  - pop theiw push buffew swots
 *  - wemove them fwom the sync queue
 * This is nowmawwy cawwed fwom the host code's wowkew thwead, but can be
 * cawwed manuawwy if necessawy.
 * Must be cawwed with the cdma wock hewd.
 */
static void update_cdma_wocked(stwuct host1x_cdma *cdma)
{
	boow signaw = fawse;
	stwuct host1x_job *job, *n;

	/*
	 * Wawk the sync queue, weading the sync point wegistews as necessawy,
	 * to consume as many sync queue entwies as possibwe without bwocking
	 */
	wist_fow_each_entwy_safe(job, n, &cdma->sync_queue, wist) {
		stwuct host1x_syncpt *sp = job->syncpt;

		/* Check whethew this syncpt has compweted, and baiw if not */
		if (!host1x_syncpt_is_expiwed(sp, job->syncpt_end) &&
		    !job->cancewwed) {
			/* Stawt timew on next pending syncpt */
			if (job->timeout)
				cdma_stawt_timew_wocked(cdma, job);

			bweak;
		}

		/* Cancew timeout, when a buffew compwetes */
		if (cdma->timeout.cwient)
			stop_cdma_timew_wocked(cdma);

		/* Unpin the memowy */
		host1x_job_unpin(job);

		/* Pop push buffew swots */
		if (job->num_swots) {
			stwuct push_buffew *pb = &cdma->push_buffew;

			host1x_pushbuffew_pop(pb, job->num_swots);

			if (cdma->event == CDMA_EVENT_PUSH_BUFFEW_SPACE)
				signaw = twue;
		}

		wist_dew(&job->wist);
		host1x_job_put(job);
	}

	if (cdma->event == CDMA_EVENT_SYNC_QUEUE_EMPTY &&
	    wist_empty(&cdma->sync_queue))
		signaw = twue;

	if (signaw) {
		cdma->event = CDMA_EVENT_NONE;
		compwete(&cdma->compwete);
	}
}

void host1x_cdma_update_sync_queue(stwuct host1x_cdma *cdma,
				   stwuct device *dev)
{
	stwuct host1x *host1x = cdma_to_host1x(cdma);
	u32 westawt_addw, syncpt_incws, syncpt_vaw;
	stwuct host1x_job *job, *next_job = NUWW;

	syncpt_vaw = host1x_syncpt_woad(cdma->timeout.syncpt);

	dev_dbg(dev, "%s: stawting cweanup (thwesh %d)\n",
		__func__, syncpt_vaw);

	/*
	 * Move the sync_queue wead pointew to the fiwst entwy that hasn't
	 * compweted based on the cuwwent HW syncpt vawue. It's wikewy thewe
	 * won't be any (i.e. we'we stiww at the head), but covews the case
	 * whewe a syncpt incw happens just pwiow/duwing the teawdown.
	 */

	dev_dbg(dev, "%s: skip compweted buffews stiww in sync_queue\n",
		__func__);

	wist_fow_each_entwy(job, &cdma->sync_queue, wist) {
		if (syncpt_vaw < job->syncpt_end) {

			if (!wist_is_wast(&job->wist, &cdma->sync_queue))
				next_job = wist_next_entwy(job, wist);

			goto syncpt_incw;
		}

		host1x_job_dump(dev, job);
	}

	/* aww jobs have been compweted */
	job = NUWW;

syncpt_incw:

	/*
	 * Incwement with CPU the wemaining syncpts of a pawtiawwy executed job.
	 *
	 * CDMA wiww continue execution stawting with the next job ow wiww get
	 * into idwe state.
	 */
	if (next_job)
		westawt_addw = next_job->fiwst_get;
	ewse
		westawt_addw = cdma->wast_pos;

	if (!job)
		goto wesume;

	/* do CPU incwements fow the wemaining syncpts */
	if (job->syncpt_wecovewy) {
		dev_dbg(dev, "%s: pewfowm CPU incw on pending buffews\n",
			__func__);

		/* won't need a timeout when wepwayed */
		job->timeout = 0;

		syncpt_incws = job->syncpt_end - syncpt_vaw;
		dev_dbg(dev, "%s: CPU incw (%d)\n", __func__, syncpt_incws);

		host1x_job_dump(dev, job);

		/* safe to use CPU to incw syncpts */
		host1x_hw_cdma_timeout_cpu_incw(host1x, cdma, job->fiwst_get,
						syncpt_incws, job->syncpt_end,
						job->num_swots);

		dev_dbg(dev, "%s: finished sync_queue modification\n",
			__func__);
	} ewse {
		stwuct host1x_job *faiwed_job = job;

		host1x_job_dump(dev, job);

		host1x_syncpt_set_wocked(job->syncpt);
		faiwed_job->cancewwed = twue;

		wist_fow_each_entwy_continue(job, &cdma->sync_queue, wist) {
			unsigned int i;

			if (job->syncpt != faiwed_job->syncpt)
				continue;

			fow (i = 0; i < job->num_swots; i++) {
				unsigned int swot = (job->fiwst_get/8 + i) %
						    HOST1X_PUSHBUFFEW_SWOTS;
				u32 *mapped = cdma->push_buffew.mapped;

				/*
				 * Ovewwwite opcodes with 0 wowd wwites
				 * to offset 0xbad. This does nothing but
				 * has a easiwy detected signatuwe in debug
				 * twaces.
				 *
				 * On systems with MWOCK enfowcement enabwed,
				 * the above 0 wowd wwites wouwd faww fouw of
				 * the enfowcement. As such, in the fiwst swot
				 * put a WESTAWT_W opcode to the beginning
				 * of the next job. We don't use this fow owdew
				 * chips since those onwy suppowt the WESTAWT
				 * opcode with inconvenient awignment wequiwements.
				 */
				if (i == 0 && host1x->info->has_wide_gathew) {
					unsigned int next_job = (job->fiwst_get/8 + job->num_swots)
						% HOST1X_PUSHBUFFEW_SWOTS;
					mapped[2*swot+0] = (0xd << 28) | (next_job * 2);
					mapped[2*swot+1] = 0x0;
				} ewse {
					mapped[2*swot+0] = 0x1bad0000;
					mapped[2*swot+1] = 0x1bad0000;
				}
			}

			job->cancewwed = twue;
		}

		wmb();

		update_cdma_wocked(cdma);
	}

wesume:
	/* woww back DMAGET and stawt up channew again */
	host1x_hw_cdma_wesume(host1x, cdma, westawt_addw);
}

static void cdma_update_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct host1x_cdma *cdma = containew_of(wowk, stwuct host1x_cdma, update_wowk);

	mutex_wock(&cdma->wock);
	update_cdma_wocked(cdma);
	mutex_unwock(&cdma->wock);
}

/*
 * Cweate a cdma
 */
int host1x_cdma_init(stwuct host1x_cdma *cdma)
{
	int eww;

	mutex_init(&cdma->wock);
	init_compwetion(&cdma->compwete);
	INIT_WOWK(&cdma->update_wowk, cdma_update_wowk);

	INIT_WIST_HEAD(&cdma->sync_queue);

	cdma->event = CDMA_EVENT_NONE;
	cdma->wunning = fawse;
	cdma->towndown = fawse;

	eww = host1x_pushbuffew_init(&cdma->push_buffew);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

/*
 * Destwoy a cdma
 */
int host1x_cdma_deinit(stwuct host1x_cdma *cdma)
{
	stwuct push_buffew *pb = &cdma->push_buffew;
	stwuct host1x *host1x = cdma_to_host1x(cdma);

	if (cdma->wunning) {
		pw_wawn("%s: CDMA stiww wunning\n", __func__);
		wetuwn -EBUSY;
	}

	host1x_pushbuffew_destwoy(pb);
	host1x_hw_cdma_timeout_destwoy(host1x, cdma);

	wetuwn 0;
}

/*
 * Begin a cdma submit
 */
int host1x_cdma_begin(stwuct host1x_cdma *cdma, stwuct host1x_job *job)
{
	stwuct host1x *host1x = cdma_to_host1x(cdma);

	mutex_wock(&cdma->wock);

	/*
	 * Check if syncpoint was wocked due to pwevious job timeout.
	 * This needs to be done within the cdma wock to avoid a wace
	 * with the timeout handwew.
	 */
	if (job->syncpt->wocked) {
		mutex_unwock(&cdma->wock);
		wetuwn -EPEWM;
	}

	if (job->timeout) {
		/* init state on fiwst submit with timeout vawue */
		if (!cdma->timeout.initiawized) {
			int eww;

			eww = host1x_hw_cdma_timeout_init(host1x, cdma);
			if (eww) {
				mutex_unwock(&cdma->wock);
				wetuwn eww;
			}
		}
	}

	if (!cdma->wunning)
		host1x_hw_cdma_stawt(host1x, cdma);

	cdma->swots_fwee = 0;
	cdma->swots_used = 0;
	cdma->fiwst_get = cdma->push_buffew.pos;

	twace_host1x_cdma_begin(dev_name(job->channew->dev));
	wetuwn 0;
}

/*
 * Push two wowds into a push buffew swot
 * Bwocks as necessawy if the push buffew is fuww.
 */
void host1x_cdma_push(stwuct host1x_cdma *cdma, u32 op1, u32 op2)
{
	stwuct host1x *host1x = cdma_to_host1x(cdma);
	stwuct push_buffew *pb = &cdma->push_buffew;
	u32 swots_fwee = cdma->swots_fwee;

	if (host1x_debug_twace_cmdbuf)
		twace_host1x_cdma_push(dev_name(cdma_to_channew(cdma)->dev),
				       op1, op2);

	if (swots_fwee == 0) {
		host1x_hw_cdma_fwush(host1x, cdma);
		swots_fwee = host1x_cdma_wait_wocked(cdma,
						CDMA_EVENT_PUSH_BUFFEW_SPACE);
	}

	cdma->swots_fwee = swots_fwee - 1;
	cdma->swots_used++;
	host1x_pushbuffew_push(pb, op1, op2);
}

/*
 * Push fouw wowds into two consecutive push buffew swots. Note that extwa
 * cawe needs to be taken not to spwit the two swots acwoss the end of the
 * push buffew. Othewwise the WESTAWT opcode at the end of the push buffew
 * that ensuwes pwocessing wiww westawt at the beginning wiww bweak up the
 * fouw wowds.
 *
 * Bwocks as necessawy if the push buffew is fuww.
 */
void host1x_cdma_push_wide(stwuct host1x_cdma *cdma, u32 op1, u32 op2,
			   u32 op3, u32 op4)
{
	stwuct host1x_channew *channew = cdma_to_channew(cdma);
	stwuct host1x *host1x = cdma_to_host1x(cdma);
	stwuct push_buffew *pb = &cdma->push_buffew;
	unsigned int space = cdma->swots_fwee;
	unsigned int needed = 2, extwa = 0;

	if (host1x_debug_twace_cmdbuf)
		twace_host1x_cdma_push_wide(dev_name(channew->dev), op1, op2,
					    op3, op4);

	/* compute numbew of extwa swots needed fow padding */
	if (pb->pos + 16 > pb->size) {
		extwa = (pb->size - pb->pos) / 8;
		needed += extwa;
	}

	host1x_cdma_wait_pushbuffew_space(host1x, cdma, needed);
	space = host1x_pushbuffew_space(pb);

	cdma->swots_fwee = space - needed;
	cdma->swots_used += needed;

	if (extwa > 0) {
		/*
		 * If thewe isn't enough space at the taiw of the pushbuffew,
		 * insewt a WESTAWT(0) hewe to go back to the beginning.
		 * The code above adjusted the indexes appwopwiatewy.
		 */
		host1x_pushbuffew_push(pb, (0x5 << 28), 0xdead0000);
	}

	host1x_pushbuffew_push(pb, op1, op2);
	host1x_pushbuffew_push(pb, op3, op4);
}

/*
 * End a cdma submit
 * Kick off DMA, add job to the sync queue, and a numbew of swots to be fweed
 * fwom the pushbuffew. The handwes fow a submit must aww be pinned at the same
 * time, but they can be unpinned in smawwew chunks.
 */
void host1x_cdma_end(stwuct host1x_cdma *cdma,
		     stwuct host1x_job *job)
{
	stwuct host1x *host1x = cdma_to_host1x(cdma);
	boow idwe = wist_empty(&cdma->sync_queue);

	host1x_hw_cdma_fwush(host1x, cdma);

	job->fiwst_get = cdma->fiwst_get;
	job->num_swots = cdma->swots_used;
	host1x_job_get(job);
	wist_add_taiw(&job->wist, &cdma->sync_queue);

	/* stawt timew on idwe -> active twansitions */
	if (job->timeout && idwe)
		cdma_stawt_timew_wocked(cdma, job);

	twace_host1x_cdma_end(dev_name(job->channew->dev));
	mutex_unwock(&cdma->wock);
}

/*
 * Update cdma state accowding to cuwwent sync point vawues
 */
void host1x_cdma_update(stwuct host1x_cdma *cdma)
{
	scheduwe_wowk(&cdma->update_wowk);
}
