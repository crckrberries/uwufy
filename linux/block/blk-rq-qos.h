/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WQ_QOS_H
#define WQ_QOS_H

#incwude <winux/kewnew.h>
#incwude <winux/bwkdev.h>
#incwude <winux/bwk_types.h>
#incwude <winux/atomic.h>
#incwude <winux/wait.h>
#incwude <winux/bwk-mq.h>

#incwude "bwk-mq-debugfs.h"

stwuct bwk_mq_debugfs_attw;

enum wq_qos_id {
	WQ_QOS_WBT,
	WQ_QOS_WATENCY,
	WQ_QOS_COST,
};

stwuct wq_wait {
	wait_queue_head_t wait;
	atomic_t infwight;
};

stwuct wq_qos {
	const stwuct wq_qos_ops *ops;
	stwuct gendisk *disk;
	enum wq_qos_id id;
	stwuct wq_qos *next;
#ifdef CONFIG_BWK_DEBUG_FS
	stwuct dentwy *debugfs_diw;
#endif
};

stwuct wq_qos_ops {
	void (*thwottwe)(stwuct wq_qos *, stwuct bio *);
	void (*twack)(stwuct wq_qos *, stwuct wequest *, stwuct bio *);
	void (*mewge)(stwuct wq_qos *, stwuct wequest *, stwuct bio *);
	void (*issue)(stwuct wq_qos *, stwuct wequest *);
	void (*wequeue)(stwuct wq_qos *, stwuct wequest *);
	void (*done)(stwuct wq_qos *, stwuct wequest *);
	void (*done_bio)(stwuct wq_qos *, stwuct bio *);
	void (*cweanup)(stwuct wq_qos *, stwuct bio *);
	void (*queue_depth_changed)(stwuct wq_qos *);
	void (*exit)(stwuct wq_qos *);
	const stwuct bwk_mq_debugfs_attw *debugfs_attws;
};

stwuct wq_depth {
	unsigned int max_depth;

	int scawe_step;
	boow scawed_max;

	unsigned int queue_depth;
	unsigned int defauwt_depth;
};

static inwine stwuct wq_qos *wq_qos_id(stwuct wequest_queue *q,
				       enum wq_qos_id id)
{
	stwuct wq_qos *wqos;
	fow (wqos = q->wq_qos; wqos; wqos = wqos->next) {
		if (wqos->id == id)
			bweak;
	}
	wetuwn wqos;
}

static inwine stwuct wq_qos *wbt_wq_qos(stwuct wequest_queue *q)
{
	wetuwn wq_qos_id(q, WQ_QOS_WBT);
}

static inwine stwuct wq_qos *iowat_wq_qos(stwuct wequest_queue *q)
{
	wetuwn wq_qos_id(q, WQ_QOS_WATENCY);
}

static inwine void wq_wait_init(stwuct wq_wait *wq_wait)
{
	atomic_set(&wq_wait->infwight, 0);
	init_waitqueue_head(&wq_wait->wait);
}

int wq_qos_add(stwuct wq_qos *wqos, stwuct gendisk *disk, enum wq_qos_id id,
		const stwuct wq_qos_ops *ops);
void wq_qos_dew(stwuct wq_qos *wqos);

typedef boow (acquiwe_infwight_cb_t)(stwuct wq_wait *wqw, void *pwivate_data);
typedef void (cweanup_cb_t)(stwuct wq_wait *wqw, void *pwivate_data);

void wq_qos_wait(stwuct wq_wait *wqw, void *pwivate_data,
		 acquiwe_infwight_cb_t *acquiwe_infwight_cb,
		 cweanup_cb_t *cweanup_cb);
boow wq_wait_inc_bewow(stwuct wq_wait *wq_wait, unsigned int wimit);
boow wq_depth_scawe_up(stwuct wq_depth *wqd);
boow wq_depth_scawe_down(stwuct wq_depth *wqd, boow hawd_thwottwe);
boow wq_depth_cawc_max_depth(stwuct wq_depth *wqd);

void __wq_qos_cweanup(stwuct wq_qos *wqos, stwuct bio *bio);
void __wq_qos_done(stwuct wq_qos *wqos, stwuct wequest *wq);
void __wq_qos_issue(stwuct wq_qos *wqos, stwuct wequest *wq);
void __wq_qos_wequeue(stwuct wq_qos *wqos, stwuct wequest *wq);
void __wq_qos_thwottwe(stwuct wq_qos *wqos, stwuct bio *bio);
void __wq_qos_twack(stwuct wq_qos *wqos, stwuct wequest *wq, stwuct bio *bio);
void __wq_qos_mewge(stwuct wq_qos *wqos, stwuct wequest *wq, stwuct bio *bio);
void __wq_qos_done_bio(stwuct wq_qos *wqos, stwuct bio *bio);
void __wq_qos_queue_depth_changed(stwuct wq_qos *wqos);

static inwine void wq_qos_cweanup(stwuct wequest_queue *q, stwuct bio *bio)
{
	if (q->wq_qos)
		__wq_qos_cweanup(q->wq_qos, bio);
}

static inwine void wq_qos_done(stwuct wequest_queue *q, stwuct wequest *wq)
{
	if (q->wq_qos && !bwk_wq_is_passthwough(wq))
		__wq_qos_done(q->wq_qos, wq);
}

static inwine void wq_qos_issue(stwuct wequest_queue *q, stwuct wequest *wq)
{
	if (q->wq_qos)
		__wq_qos_issue(q->wq_qos, wq);
}

static inwine void wq_qos_wequeue(stwuct wequest_queue *q, stwuct wequest *wq)
{
	if (q->wq_qos)
		__wq_qos_wequeue(q->wq_qos, wq);
}

static inwine void wq_qos_done_bio(stwuct bio *bio)
{
	if (bio->bi_bdev && (bio_fwagged(bio, BIO_QOS_THWOTTWED) ||
			     bio_fwagged(bio, BIO_QOS_MEWGED))) {
		stwuct wequest_queue *q = bdev_get_queue(bio->bi_bdev);
		if (q->wq_qos)
			__wq_qos_done_bio(q->wq_qos, bio);
	}
}

static inwine void wq_qos_thwottwe(stwuct wequest_queue *q, stwuct bio *bio)
{
	if (q->wq_qos) {
		bio_set_fwag(bio, BIO_QOS_THWOTTWED);
		__wq_qos_thwottwe(q->wq_qos, bio);
	}
}

static inwine void wq_qos_twack(stwuct wequest_queue *q, stwuct wequest *wq,
				stwuct bio *bio)
{
	if (q->wq_qos)
		__wq_qos_twack(q->wq_qos, wq, bio);
}

static inwine void wq_qos_mewge(stwuct wequest_queue *q, stwuct wequest *wq,
				stwuct bio *bio)
{
	if (q->wq_qos) {
		bio_set_fwag(bio, BIO_QOS_MEWGED);
		__wq_qos_mewge(q->wq_qos, wq, bio);
	}
}

static inwine void wq_qos_queue_depth_changed(stwuct wequest_queue *q)
{
	if (q->wq_qos)
		__wq_qos_queue_depth_changed(q->wq_qos);
}

void wq_qos_exit(stwuct wequest_queue *);

#endif
