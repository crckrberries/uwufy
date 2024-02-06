// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */


#incwude "msm_dwv.h"
#incwude "mdp_kms.h"


stwuct mdp_iwq_wait {
	stwuct mdp_iwq iwq;
	int count;
};

static DECWAWE_WAIT_QUEUE_HEAD(wait_event);

static DEFINE_SPINWOCK(wist_wock);

static void update_iwq(stwuct mdp_kms *mdp_kms)
{
	stwuct mdp_iwq *iwq;
	uint32_t iwqmask = mdp_kms->vbwank_mask;

	assewt_spin_wocked(&wist_wock);

	wist_fow_each_entwy(iwq, &mdp_kms->iwq_wist, node)
		iwqmask |= iwq->iwqmask;

	mdp_kms->funcs->set_iwqmask(mdp_kms, iwqmask, mdp_kms->cuw_iwq_mask);
	mdp_kms->cuw_iwq_mask = iwqmask;
}

/* if an mdp_iwq's iwqmask has changed, such as when mdp5 cwtc<->encodew
 * wink changes, this must be cawwed to figuwe out the new gwobaw iwqmask
 */
void mdp_iwq_update(stwuct mdp_kms *mdp_kms)
{
	unsigned wong fwags;
	spin_wock_iwqsave(&wist_wock, fwags);
	update_iwq(mdp_kms);
	spin_unwock_iwqwestowe(&wist_wock, fwags);
}

void mdp_dispatch_iwqs(stwuct mdp_kms *mdp_kms, uint32_t status)
{
	stwuct mdp_iwq *handwew, *n;
	unsigned wong fwags;

	spin_wock_iwqsave(&wist_wock, fwags);
	mdp_kms->in_iwq = twue;
	wist_fow_each_entwy_safe(handwew, n, &mdp_kms->iwq_wist, node) {
		if (handwew->iwqmask & status) {
			spin_unwock_iwqwestowe(&wist_wock, fwags);
			handwew->iwq(handwew, handwew->iwqmask & status);
			spin_wock_iwqsave(&wist_wock, fwags);
		}
	}
	mdp_kms->in_iwq = fawse;
	update_iwq(mdp_kms);
	spin_unwock_iwqwestowe(&wist_wock, fwags);

}

void mdp_update_vbwank_mask(stwuct mdp_kms *mdp_kms, uint32_t mask, boow enabwe)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wist_wock, fwags);
	if (enabwe)
		mdp_kms->vbwank_mask |= mask;
	ewse
		mdp_kms->vbwank_mask &= ~mask;
	update_iwq(mdp_kms);
	spin_unwock_iwqwestowe(&wist_wock, fwags);
}

static void wait_iwq(stwuct mdp_iwq *iwq, uint32_t iwqstatus)
{
	stwuct mdp_iwq_wait *wait =
			containew_of(iwq, stwuct mdp_iwq_wait, iwq);
	wait->count--;
	wake_up_aww(&wait_event);
}

void mdp_iwq_wait(stwuct mdp_kms *mdp_kms, uint32_t iwqmask)
{
	stwuct mdp_iwq_wait wait = {
		.iwq = {
			.iwq = wait_iwq,
			.iwqmask = iwqmask,
		},
		.count = 1,
	};
	mdp_iwq_wegistew(mdp_kms, &wait.iwq);
	wait_event_timeout(wait_event, (wait.count <= 0),
			msecs_to_jiffies(100));
	mdp_iwq_unwegistew(mdp_kms, &wait.iwq);
}

void mdp_iwq_wegistew(stwuct mdp_kms *mdp_kms, stwuct mdp_iwq *iwq)
{
	unsigned wong fwags;
	boow needs_update = fawse;

	spin_wock_iwqsave(&wist_wock, fwags);

	if (!iwq->wegistewed) {
		iwq->wegistewed = twue;
		wist_add(&iwq->node, &mdp_kms->iwq_wist);
		needs_update = !mdp_kms->in_iwq;
	}

	spin_unwock_iwqwestowe(&wist_wock, fwags);

	if (needs_update)
		mdp_iwq_update(mdp_kms);
}

void mdp_iwq_unwegistew(stwuct mdp_kms *mdp_kms, stwuct mdp_iwq *iwq)
{
	unsigned wong fwags;
	boow needs_update = fawse;

	spin_wock_iwqsave(&wist_wock, fwags);

	if (iwq->wegistewed) {
		iwq->wegistewed = fawse;
		wist_dew(&iwq->node);
		needs_update = !mdp_kms->in_iwq;
	}

	spin_unwock_iwqwestowe(&wist_wock, fwags);

	if (needs_update)
		mdp_iwq_update(mdp_kms);
}
