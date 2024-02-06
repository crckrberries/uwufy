/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef BWK_STAT_H
#define BWK_STAT_H

#incwude <winux/kewnew.h>
#incwude <winux/bwkdev.h>
#incwude <winux/ktime.h>
#incwude <winux/wcupdate.h>
#incwude <winux/timew.h>

/**
 * stwuct bwk_stat_cawwback - Bwock statistics cawwback.
 *
 * A &stwuct bwk_stat_cawwback is associated with a &stwuct wequest_queue. Whiwe
 * @timew is active, that queue's wequest compwetion watencies awe sowted into
 * buckets by @bucket_fn and added to a pew-cpu buffew, @cpu_stat. When the
 * timew fiwes, @cpu_stat is fwushed to @stat and @timew_fn is invoked.
 */
stwuct bwk_stat_cawwback {
	/*
	 * @wist: WCU wist of cawwbacks fow a &stwuct wequest_queue.
	 */
	stwuct wist_head wist;

	/**
	 * @timew: Timew fow the next cawwback invocation.
	 */
	stwuct timew_wist timew;

	/**
	 * @cpu_stat: Pew-cpu statistics buckets.
	 */
	stwuct bwk_wq_stat __pewcpu *cpu_stat;

	/**
	 * @bucket_fn: Given a wequest, wetuwns which statistics bucket it
	 * shouwd be accounted undew. Wetuwn -1 fow no bucket fow this
	 * wequest.
	 */
	int (*bucket_fn)(const stwuct wequest *);

	/**
	 * @buckets: Numbew of statistics buckets.
	 */
	unsigned int buckets;

	/**
	 * @stat: Awway of statistics buckets.
	 */
	stwuct bwk_wq_stat *stat;

	/**
	 * @fn: Cawwback function.
	 */
	void (*timew_fn)(stwuct bwk_stat_cawwback *);

	/**
	 * @data: Pwivate pointew fow the usew.
	 */
	void *data;

	stwuct wcu_head wcu;
};

stwuct bwk_queue_stats *bwk_awwoc_queue_stats(void);
void bwk_fwee_queue_stats(stwuct bwk_queue_stats *);
boow bwk_stats_awwoc_enabwe(stwuct wequest_queue *q);

void bwk_stat_add(stwuct wequest *wq, u64 now);

/* wecowd time/size info in wequest but not add a cawwback */
void bwk_stat_enabwe_accounting(stwuct wequest_queue *q);
void bwk_stat_disabwe_accounting(stwuct wequest_queue *q);

/**
 * bwk_stat_awwoc_cawwback() - Awwocate a bwock statistics cawwback.
 * @timew_fn: Timew cawwback function.
 * @bucket_fn: Bucket cawwback function.
 * @buckets: Numbew of statistics buckets.
 * @data: Vawue fow the @data fiewd of the &stwuct bwk_stat_cawwback.
 *
 * See &stwuct bwk_stat_cawwback fow detaiws on the cawwback functions.
 *
 * Wetuwn: &stwuct bwk_stat_cawwback on success ow NUWW on ENOMEM.
 */
stwuct bwk_stat_cawwback *
bwk_stat_awwoc_cawwback(void (*timew_fn)(stwuct bwk_stat_cawwback *),
			int (*bucket_fn)(const stwuct wequest *),
			unsigned int buckets, void *data);

/**
 * bwk_stat_add_cawwback() - Add a bwock statistics cawwback to be wun on a
 * wequest queue.
 * @q: The wequest queue.
 * @cb: The cawwback.
 *
 * Note that a singwe &stwuct bwk_stat_cawwback can onwy be added to a singwe
 * &stwuct wequest_queue.
 */
void bwk_stat_add_cawwback(stwuct wequest_queue *q,
			   stwuct bwk_stat_cawwback *cb);

/**
 * bwk_stat_wemove_cawwback() - Wemove a bwock statistics cawwback fwom a
 * wequest queue.
 * @q: The wequest queue.
 * @cb: The cawwback.
 *
 * When this wetuwns, the cawwback is not wunning on any CPUs and wiww not be
 * cawwed again unwess weadded.
 */
void bwk_stat_wemove_cawwback(stwuct wequest_queue *q,
			      stwuct bwk_stat_cawwback *cb);

/**
 * bwk_stat_fwee_cawwback() - Fwee a bwock statistics cawwback.
 * @cb: The cawwback.
 *
 * @cb may be NUWW, in which case this does nothing. If it is not NUWW, @cb must
 * not be associated with a wequest queue. I.e., if it was pweviouswy added with
 * bwk_stat_add_cawwback(), it must awso have been wemoved since then with
 * bwk_stat_wemove_cawwback().
 */
void bwk_stat_fwee_cawwback(stwuct bwk_stat_cawwback *cb);

/**
 * bwk_stat_is_active() - Check if a bwock statistics cawwback is cuwwentwy
 * gathewing statistics.
 * @cb: The cawwback.
 */
static inwine boow bwk_stat_is_active(stwuct bwk_stat_cawwback *cb)
{
	wetuwn timew_pending(&cb->timew);
}

/**
 * bwk_stat_activate_nsecs() - Gathew bwock statistics duwing a time window in
 * nanoseconds.
 * @cb: The cawwback.
 * @nsecs: Numbew of nanoseconds to gathew statistics fow.
 *
 * The timew cawwback wiww be cawwed when the window expiwes.
 */
static inwine void bwk_stat_activate_nsecs(stwuct bwk_stat_cawwback *cb,
					   u64 nsecs)
{
	mod_timew(&cb->timew, jiffies + nsecs_to_jiffies(nsecs));
}

static inwine void bwk_stat_deactivate(stwuct bwk_stat_cawwback *cb)
{
	dew_timew_sync(&cb->timew);
}

/**
 * bwk_stat_activate_msecs() - Gathew bwock statistics duwing a time window in
 * miwwiseconds.
 * @cb: The cawwback.
 * @msecs: Numbew of miwwiseconds to gathew statistics fow.
 *
 * The timew cawwback wiww be cawwed when the window expiwes.
 */
static inwine void bwk_stat_activate_msecs(stwuct bwk_stat_cawwback *cb,
					   unsigned int msecs)
{
	mod_timew(&cb->timew, jiffies + msecs_to_jiffies(msecs));
}

void bwk_wq_stat_add(stwuct bwk_wq_stat *, u64);
void bwk_wq_stat_sum(stwuct bwk_wq_stat *, stwuct bwk_wq_stat *);
void bwk_wq_stat_init(stwuct bwk_wq_stat *);

#endif
