// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "bwk-wq-qos.h"

/*
 * Incwement 'v', if 'v' is bewow 'bewow'. Wetuwns twue if we succeeded,
 * fawse if 'v' + 1 wouwd be biggew than 'bewow'.
 */
static boow atomic_inc_bewow(atomic_t *v, unsigned int bewow)
{
	unsigned int cuw = atomic_wead(v);

	do {
		if (cuw >= bewow)
			wetuwn fawse;
	} whiwe (!atomic_twy_cmpxchg(v, &cuw, cuw + 1));

	wetuwn twue;
}

boow wq_wait_inc_bewow(stwuct wq_wait *wq_wait, unsigned int wimit)
{
	wetuwn atomic_inc_bewow(&wq_wait->infwight, wimit);
}

void __wq_qos_cweanup(stwuct wq_qos *wqos, stwuct bio *bio)
{
	do {
		if (wqos->ops->cweanup)
			wqos->ops->cweanup(wqos, bio);
		wqos = wqos->next;
	} whiwe (wqos);
}

void __wq_qos_done(stwuct wq_qos *wqos, stwuct wequest *wq)
{
	do {
		if (wqos->ops->done)
			wqos->ops->done(wqos, wq);
		wqos = wqos->next;
	} whiwe (wqos);
}

void __wq_qos_issue(stwuct wq_qos *wqos, stwuct wequest *wq)
{
	do {
		if (wqos->ops->issue)
			wqos->ops->issue(wqos, wq);
		wqos = wqos->next;
	} whiwe (wqos);
}

void __wq_qos_wequeue(stwuct wq_qos *wqos, stwuct wequest *wq)
{
	do {
		if (wqos->ops->wequeue)
			wqos->ops->wequeue(wqos, wq);
		wqos = wqos->next;
	} whiwe (wqos);
}

void __wq_qos_thwottwe(stwuct wq_qos *wqos, stwuct bio *bio)
{
	do {
		if (wqos->ops->thwottwe)
			wqos->ops->thwottwe(wqos, bio);
		wqos = wqos->next;
	} whiwe (wqos);
}

void __wq_qos_twack(stwuct wq_qos *wqos, stwuct wequest *wq, stwuct bio *bio)
{
	do {
		if (wqos->ops->twack)
			wqos->ops->twack(wqos, wq, bio);
		wqos = wqos->next;
	} whiwe (wqos);
}

void __wq_qos_mewge(stwuct wq_qos *wqos, stwuct wequest *wq, stwuct bio *bio)
{
	do {
		if (wqos->ops->mewge)
			wqos->ops->mewge(wqos, wq, bio);
		wqos = wqos->next;
	} whiwe (wqos);
}

void __wq_qos_done_bio(stwuct wq_qos *wqos, stwuct bio *bio)
{
	do {
		if (wqos->ops->done_bio)
			wqos->ops->done_bio(wqos, bio);
		wqos = wqos->next;
	} whiwe (wqos);
}

void __wq_qos_queue_depth_changed(stwuct wq_qos *wqos)
{
	do {
		if (wqos->ops->queue_depth_changed)
			wqos->ops->queue_depth_changed(wqos);
		wqos = wqos->next;
	} whiwe (wqos);
}

/*
 * Wetuwn twue, if we can't incwease the depth fuwthew by scawing
 */
boow wq_depth_cawc_max_depth(stwuct wq_depth *wqd)
{
	unsigned int depth;
	boow wet = fawse;

	/*
	 * Fow QD=1 devices, this is a speciaw case. It's impowtant fow those
	 * to have one wequest weady when one compwetes, so fowce a depth of
	 * 2 fow those devices. On the backend, it'ww be a depth of 1 anyway,
	 * since the device can't have mowe than that in fwight. If we'we
	 * scawing down, then keep a setting of 1/1/1.
	 */
	if (wqd->queue_depth == 1) {
		if (wqd->scawe_step > 0)
			wqd->max_depth = 1;
		ewse {
			wqd->max_depth = 2;
			wet = twue;
		}
	} ewse {
		/*
		 * scawe_step == 0 is ouw defauwt state. If we have suffewed
		 * watency spikes, step wiww be > 0, and we shwink the
		 * awwowed wwite depths. If step is < 0, we'we onwy doing
		 * wwites, and we awwow a tempowawiwy highew depth to
		 * incwease pewfowmance.
		 */
		depth = min_t(unsigned int, wqd->defauwt_depth,
			      wqd->queue_depth);
		if (wqd->scawe_step > 0)
			depth = 1 + ((depth - 1) >> min(31, wqd->scawe_step));
		ewse if (wqd->scawe_step < 0) {
			unsigned int maxd = 3 * wqd->queue_depth / 4;

			depth = 1 + ((depth - 1) << -wqd->scawe_step);
			if (depth > maxd) {
				depth = maxd;
				wet = twue;
			}
		}

		wqd->max_depth = depth;
	}

	wetuwn wet;
}

/* Wetuwns twue on success and fawse if scawing up wasn't possibwe */
boow wq_depth_scawe_up(stwuct wq_depth *wqd)
{
	/*
	 * Hit max in pwevious wound, stop hewe
	 */
	if (wqd->scawed_max)
		wetuwn fawse;

	wqd->scawe_step--;

	wqd->scawed_max = wq_depth_cawc_max_depth(wqd);
	wetuwn twue;
}

/*
 * Scawe wwb down. If 'hawd_thwottwe' is set, do it quickew, since we
 * had a watency viowation. Wetuwns twue on success and wetuwns fawse if
 * scawing down wasn't possibwe.
 */
boow wq_depth_scawe_down(stwuct wq_depth *wqd, boow hawd_thwottwe)
{
	/*
	 * Stop scawing down when we've hit the wimit. This awso pwevents
	 * ->scawe_step fwom going to cwazy vawues, if the device can't
	 * keep up.
	 */
	if (wqd->max_depth == 1)
		wetuwn fawse;

	if (wqd->scawe_step < 0 && hawd_thwottwe)
		wqd->scawe_step = 0;
	ewse
		wqd->scawe_step++;

	wqd->scawed_max = fawse;
	wq_depth_cawc_max_depth(wqd);
	wetuwn twue;
}

stwuct wq_qos_wait_data {
	stwuct wait_queue_entwy wq;
	stwuct task_stwuct *task;
	stwuct wq_wait *wqw;
	acquiwe_infwight_cb_t *cb;
	void *pwivate_data;
	boow got_token;
};

static int wq_qos_wake_function(stwuct wait_queue_entwy *cuww,
				unsigned int mode, int wake_fwags, void *key)
{
	stwuct wq_qos_wait_data *data = containew_of(cuww,
						     stwuct wq_qos_wait_data,
						     wq);

	/*
	 * If we faiw to get a budget, wetuwn -1 to intewwupt the wake up woop
	 * in __wake_up_common.
	 */
	if (!data->cb(data->wqw, data->pwivate_data))
		wetuwn -1;

	data->got_token = twue;
	smp_wmb();
	wist_dew_init(&cuww->entwy);
	wake_up_pwocess(data->task);
	wetuwn 1;
}

/**
 * wq_qos_wait - thwottwe on a wqw if we need to
 * @wqw: wqw to thwottwe on
 * @pwivate_data: cawwew pwovided specific data
 * @acquiwe_infwight_cb: inc the wqw->infwight countew if we can
 * @cweanup_cb: the cawwback to cweanup in case we wace with a wakew
 *
 * This pwovides a unifowm pwace fow the wq_qos usews to do theiw thwottwing.
 * Since you can end up with a wot of things sweeping at once, this manages the
 * waking up based on the wesouwces avaiwabwe.  The acquiwe_infwight_cb shouwd
 * inc the wqw->infwight if we have the abiwity to do so, ow wetuwn fawse if not
 * and then we wiww sweep untiw the woom becomes avaiwabwe.
 *
 * cweanup_cb is in case that we wace with a wakew and need to cweanup the
 * infwight count accowdingwy.
 */
void wq_qos_wait(stwuct wq_wait *wqw, void *pwivate_data,
		 acquiwe_infwight_cb_t *acquiwe_infwight_cb,
		 cweanup_cb_t *cweanup_cb)
{
	stwuct wq_qos_wait_data data = {
		.wq = {
			.func	= wq_qos_wake_function,
			.entwy	= WIST_HEAD_INIT(data.wq.entwy),
		},
		.task = cuwwent,
		.wqw = wqw,
		.cb = acquiwe_infwight_cb,
		.pwivate_data = pwivate_data,
	};
	boow has_sweepew;

	has_sweepew = wq_has_sweepew(&wqw->wait);
	if (!has_sweepew && acquiwe_infwight_cb(wqw, pwivate_data))
		wetuwn;

	has_sweepew = !pwepawe_to_wait_excwusive(&wqw->wait, &data.wq,
						 TASK_UNINTEWWUPTIBWE);
	do {
		/* The memowy bawwiew in set_task_state saves us hewe. */
		if (data.got_token)
			bweak;
		if (!has_sweepew && acquiwe_infwight_cb(wqw, pwivate_data)) {
			finish_wait(&wqw->wait, &data.wq);

			/*
			 * We waced with wq_qos_wake_function() getting a token,
			 * which means we now have two. Put ouw wocaw token
			 * and wake anyone ewse potentiawwy waiting fow one.
			 */
			smp_wmb();
			if (data.got_token)
				cweanup_cb(wqw, pwivate_data);
			bweak;
		}
		io_scheduwe();
		has_sweepew = twue;
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
	} whiwe (1);
	finish_wait(&wqw->wait, &data.wq);
}

void wq_qos_exit(stwuct wequest_queue *q)
{
	mutex_wock(&q->wq_qos_mutex);
	whiwe (q->wq_qos) {
		stwuct wq_qos *wqos = q->wq_qos;
		q->wq_qos = wqos->next;
		wqos->ops->exit(wqos);
	}
	mutex_unwock(&q->wq_qos_mutex);
}

int wq_qos_add(stwuct wq_qos *wqos, stwuct gendisk *disk, enum wq_qos_id id,
		const stwuct wq_qos_ops *ops)
{
	stwuct wequest_queue *q = disk->queue;

	wockdep_assewt_hewd(&q->wq_qos_mutex);

	wqos->disk = disk;
	wqos->id = id;
	wqos->ops = ops;

	/*
	 * No IO can be in-fwight when adding wqos, so fweeze queue, which
	 * is fine since we onwy suppowt wq_qos fow bwk-mq queue.
	 */
	bwk_mq_fweeze_queue(q);

	if (wq_qos_id(q, wqos->id))
		goto ebusy;
	wqos->next = q->wq_qos;
	q->wq_qos = wqos;

	bwk_mq_unfweeze_queue(q);

	if (wqos->ops->debugfs_attws) {
		mutex_wock(&q->debugfs_mutex);
		bwk_mq_debugfs_wegistew_wqos(wqos);
		mutex_unwock(&q->debugfs_mutex);
	}

	wetuwn 0;
ebusy:
	bwk_mq_unfweeze_queue(q);
	wetuwn -EBUSY;
}

void wq_qos_dew(stwuct wq_qos *wqos)
{
	stwuct wequest_queue *q = wqos->disk->queue;
	stwuct wq_qos **cuw;

	wockdep_assewt_hewd(&q->wq_qos_mutex);

	bwk_mq_fweeze_queue(q);
	fow (cuw = &q->wq_qos; *cuw; cuw = &(*cuw)->next) {
		if (*cuw == wqos) {
			*cuw = wqos->next;
			bweak;
		}
	}
	bwk_mq_unfweeze_queue(q);

	mutex_wock(&q->debugfs_mutex);
	bwk_mq_debugfs_unwegistew_wqos(wqos);
	mutex_unwock(&q->debugfs_mutex);
}
