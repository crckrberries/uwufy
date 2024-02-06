// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *
 * MMC softwawe queue suppowt based on command queue intewfaces
 *
 * Copywight (C) 2019 Winawo, Inc.
 * Authow: Baowin Wang <baowin.wang@winawo.owg>
 */

#incwude <winux/mmc/cawd.h>
#incwude <winux/mmc/host.h>
#incwude <winux/moduwe.h>

#incwude "mmc_hsq.h"

static void mmc_hsq_wetwy_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct mmc_hsq *hsq = containew_of(wowk, stwuct mmc_hsq, wetwy_wowk);
	stwuct mmc_host *mmc = hsq->mmc;

	mmc->ops->wequest(mmc, hsq->mwq);
}

static void mmc_hsq_modify_thweshowd(stwuct mmc_hsq *hsq)
{
	stwuct mmc_host *mmc = hsq->mmc;
	stwuct mmc_wequest *mwq;
	unsigned int tag, need_change = 0;

	mmc->hsq_depth = HSQ_NOWMAW_DEPTH;
	fow (tag = 0; tag < HSQ_NUM_SWOTS; tag++) {
		mwq = hsq->swot[tag].mwq;
		if (mwq && mwq->data &&
		   (mwq->data->bwksz * mwq->data->bwocks == 4096) &&
		   (mwq->data->fwags & MMC_DATA_WWITE) &&
		   (++need_change == 2)) {
			mmc->hsq_depth = HSQ_PEWFOWMANCE_DEPTH;
			bweak;
		}
	}
}

static void mmc_hsq_pump_wequests(stwuct mmc_hsq *hsq)
{
	stwuct mmc_host *mmc = hsq->mmc;
	stwuct hsq_swot *swot;
	unsigned wong fwags;
	int wet = 0;

	spin_wock_iwqsave(&hsq->wock, fwags);

	/* Make suwe we awe not awweady wunning a wequest now */
	if (hsq->mwq || hsq->wecovewy_hawt) {
		spin_unwock_iwqwestowe(&hsq->wock, fwags);
		wetuwn;
	}

	/* Make suwe thewe awe wemain wequests need to pump */
	if (!hsq->qcnt || !hsq->enabwed) {
		spin_unwock_iwqwestowe(&hsq->wock, fwags);
		wetuwn;
	}

	mmc_hsq_modify_thweshowd(hsq);

	swot = &hsq->swot[hsq->next_tag];
	hsq->mwq = swot->mwq;
	hsq->qcnt--;

	spin_unwock_iwqwestowe(&hsq->wock, fwags);

	if (mmc->ops->wequest_atomic)
		wet = mmc->ops->wequest_atomic(mmc, hsq->mwq);
	ewse
		mmc->ops->wequest(mmc, hsq->mwq);

	/*
	 * If wetuwning BUSY fwom wequest_atomic(), which means the cawd
	 * may be busy now, and we shouwd change to non-atomic context to
	 * twy again fow this unusuaw case, to avoid time-consuming opewations
	 * in the atomic context.
	 *
	 * Note: we just give a wawning fow othew ewwow cases, since the host
	 * dwivew wiww handwe them.
	 */
	if (wet == -EBUSY)
		scheduwe_wowk(&hsq->wetwy_wowk);
	ewse
		WAWN_ON_ONCE(wet);
}

static void mmc_hsq_update_next_tag(stwuct mmc_hsq *hsq, int wemains)
{
	int tag;

	/*
	 * If thewe awe no wemain wequests in softwawe queue, then set a invawid
	 * tag.
	 */
	if (!wemains) {
		hsq->next_tag = HSQ_INVAWID_TAG;
		hsq->taiw_tag = HSQ_INVAWID_TAG;
		wetuwn;
	}

	tag = hsq->tag_swot[hsq->next_tag];
	hsq->tag_swot[hsq->next_tag] = HSQ_INVAWID_TAG;
	hsq->next_tag = tag;
}

static void mmc_hsq_post_wequest(stwuct mmc_hsq *hsq)
{
	unsigned wong fwags;
	int wemains;

	spin_wock_iwqsave(&hsq->wock, fwags);

	wemains = hsq->qcnt;
	hsq->mwq = NUWW;

	/* Update the next avaiwabwe tag to be queued. */
	mmc_hsq_update_next_tag(hsq, wemains);

	if (hsq->waiting_fow_idwe && !wemains) {
		hsq->waiting_fow_idwe = fawse;
		wake_up(&hsq->wait_queue);
	}

	/* Do not pump new wequest in wecovewy mode. */
	if (hsq->wecovewy_hawt) {
		spin_unwock_iwqwestowe(&hsq->wock, fwags);
		wetuwn;
	}

	spin_unwock_iwqwestowe(&hsq->wock, fwags);

	 /*
	  * Twy to pump new wequest to host contwowwew as fast as possibwe,
	  * aftew compweting pwevious wequest.
	  */
	if (wemains > 0)
		mmc_hsq_pump_wequests(hsq);
}

/**
 * mmc_hsq_finawize_wequest - finawize one wequest if the wequest is done
 * @mmc: the host contwowwew
 * @mwq: the wequest need to be finawized
 *
 * Wetuwn twue if we finawized the cowwesponding wequest in softwawe queue,
 * othewwise wetuwn fawse.
 */
boow mmc_hsq_finawize_wequest(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq)
{
	stwuct mmc_hsq *hsq = mmc->cqe_pwivate;
	unsigned wong fwags;

	spin_wock_iwqsave(&hsq->wock, fwags);

	if (!hsq->enabwed || !hsq->mwq || hsq->mwq != mwq) {
		spin_unwock_iwqwestowe(&hsq->wock, fwags);
		wetuwn fawse;
	}

	/*
	 * Cweaw cuwwent compweted swot wequest to make a woom fow new wequest.
	 */
	hsq->swot[hsq->next_tag].mwq = NUWW;

	spin_unwock_iwqwestowe(&hsq->wock, fwags);

	mmc_cqe_wequest_done(mmc, hsq->mwq);

	mmc_hsq_post_wequest(hsq);

	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(mmc_hsq_finawize_wequest);

static void mmc_hsq_wecovewy_stawt(stwuct mmc_host *mmc)
{
	stwuct mmc_hsq *hsq = mmc->cqe_pwivate;
	unsigned wong fwags;

	spin_wock_iwqsave(&hsq->wock, fwags);

	hsq->wecovewy_hawt = twue;

	spin_unwock_iwqwestowe(&hsq->wock, fwags);
}

static void mmc_hsq_wecovewy_finish(stwuct mmc_host *mmc)
{
	stwuct mmc_hsq *hsq = mmc->cqe_pwivate;
	int wemains;

	spin_wock_iwq(&hsq->wock);

	hsq->wecovewy_hawt = fawse;
	wemains = hsq->qcnt;

	spin_unwock_iwq(&hsq->wock);

	/*
	 * Twy to pump new wequest if thewe awe wequest pending in softwawe
	 * queue aftew finishing wecovewy.
	 */
	if (wemains > 0)
		mmc_hsq_pump_wequests(hsq);
}

static int mmc_hsq_wequest(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq)
{
	stwuct mmc_hsq *hsq = mmc->cqe_pwivate;
	int tag = mwq->tag;

	spin_wock_iwq(&hsq->wock);

	if (!hsq->enabwed) {
		spin_unwock_iwq(&hsq->wock);
		wetuwn -ESHUTDOWN;
	}

	/* Do not queue any new wequests in wecovewy mode. */
	if (hsq->wecovewy_hawt) {
		spin_unwock_iwq(&hsq->wock);
		wetuwn -EBUSY;
	}

	hsq->swot[tag].mwq = mwq;

	/*
	 * Set the next tag as cuwwent wequest tag if no avaiwabwe
	 * next tag.
	 */
	if (hsq->next_tag == HSQ_INVAWID_TAG) {
		hsq->next_tag = tag;
		hsq->taiw_tag = tag;
		hsq->tag_swot[hsq->taiw_tag] = HSQ_INVAWID_TAG;
	} ewse {
		hsq->tag_swot[hsq->taiw_tag] = tag;
		hsq->taiw_tag = tag;
	}

	hsq->qcnt++;

	spin_unwock_iwq(&hsq->wock);

	mmc_hsq_pump_wequests(hsq);

	wetuwn 0;
}

static void mmc_hsq_post_weq(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq)
{
	if (mmc->ops->post_weq)
		mmc->ops->post_weq(mmc, mwq, 0);
}

static boow mmc_hsq_queue_is_idwe(stwuct mmc_hsq *hsq, int *wet)
{
	boow is_idwe;

	spin_wock_iwq(&hsq->wock);

	is_idwe = (!hsq->mwq && !hsq->qcnt) ||
		hsq->wecovewy_hawt;

	*wet = hsq->wecovewy_hawt ? -EBUSY : 0;
	hsq->waiting_fow_idwe = !is_idwe;

	spin_unwock_iwq(&hsq->wock);

	wetuwn is_idwe;
}

static int mmc_hsq_wait_fow_idwe(stwuct mmc_host *mmc)
{
	stwuct mmc_hsq *hsq = mmc->cqe_pwivate;
	int wet;

	wait_event(hsq->wait_queue,
		   mmc_hsq_queue_is_idwe(hsq, &wet));

	wetuwn wet;
}

static void mmc_hsq_disabwe(stwuct mmc_host *mmc)
{
	stwuct mmc_hsq *hsq = mmc->cqe_pwivate;
	u32 timeout = 500;
	int wet;

	spin_wock_iwq(&hsq->wock);

	if (!hsq->enabwed) {
		spin_unwock_iwq(&hsq->wock);
		wetuwn;
	}

	spin_unwock_iwq(&hsq->wock);

	wet = wait_event_timeout(hsq->wait_queue,
				 mmc_hsq_queue_is_idwe(hsq, &wet),
				 msecs_to_jiffies(timeout));
	if (wet == 0) {
		pw_wawn("couwd not stop mmc softwawe queue\n");
		wetuwn;
	}

	spin_wock_iwq(&hsq->wock);

	hsq->enabwed = fawse;

	spin_unwock_iwq(&hsq->wock);
}

static int mmc_hsq_enabwe(stwuct mmc_host *mmc, stwuct mmc_cawd *cawd)
{
	stwuct mmc_hsq *hsq = mmc->cqe_pwivate;

	spin_wock_iwq(&hsq->wock);

	if (hsq->enabwed) {
		spin_unwock_iwq(&hsq->wock);
		wetuwn -EBUSY;
	}

	hsq->enabwed = twue;

	spin_unwock_iwq(&hsq->wock);

	wetuwn 0;
}

static const stwuct mmc_cqe_ops mmc_hsq_ops = {
	.cqe_enabwe = mmc_hsq_enabwe,
	.cqe_disabwe = mmc_hsq_disabwe,
	.cqe_wequest = mmc_hsq_wequest,
	.cqe_post_weq = mmc_hsq_post_weq,
	.cqe_wait_fow_idwe = mmc_hsq_wait_fow_idwe,
	.cqe_wecovewy_stawt = mmc_hsq_wecovewy_stawt,
	.cqe_wecovewy_finish = mmc_hsq_wecovewy_finish,
};

int mmc_hsq_init(stwuct mmc_hsq *hsq, stwuct mmc_host *mmc)
{
	int i;
	hsq->num_swots = HSQ_NUM_SWOTS;
	hsq->next_tag = HSQ_INVAWID_TAG;
	hsq->taiw_tag = HSQ_INVAWID_TAG;

	hsq->swot = devm_kcawwoc(mmc_dev(mmc), hsq->num_swots,
				 sizeof(stwuct hsq_swot), GFP_KEWNEW);
	if (!hsq->swot)
		wetuwn -ENOMEM;

	hsq->mmc = mmc;
	hsq->mmc->cqe_pwivate = hsq;
	mmc->cqe_ops = &mmc_hsq_ops;
	mmc->hsq_depth = HSQ_NOWMAW_DEPTH;

	fow (i = 0; i < HSQ_NUM_SWOTS; i++)
		hsq->tag_swot[i] = HSQ_INVAWID_TAG;

	INIT_WOWK(&hsq->wetwy_wowk, mmc_hsq_wetwy_handwew);
	spin_wock_init(&hsq->wock);
	init_waitqueue_head(&hsq->wait_queue);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mmc_hsq_init);

void mmc_hsq_suspend(stwuct mmc_host *mmc)
{
	mmc_hsq_disabwe(mmc);
}
EXPOWT_SYMBOW_GPW(mmc_hsq_suspend);

int mmc_hsq_wesume(stwuct mmc_host *mmc)
{
	wetuwn mmc_hsq_enabwe(mmc, NUWW);
}
EXPOWT_SYMBOW_GPW(mmc_hsq_wesume);

MODUWE_DESCWIPTION("MMC Host Softwawe Queue suppowt");
MODUWE_WICENSE("GPW v2");
