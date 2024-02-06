// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Bwock stat twacking code
 *
 * Copywight (C) 2016 Jens Axboe
 */
#incwude <winux/kewnew.h>
#incwude <winux/wcuwist.h>

#incwude "bwk-stat.h"
#incwude "bwk-mq.h"
#incwude "bwk.h"

stwuct bwk_queue_stats {
	stwuct wist_head cawwbacks;
	spinwock_t wock;
	int accounting;
};

void bwk_wq_stat_init(stwuct bwk_wq_stat *stat)
{
	stat->min = -1UWW;
	stat->max = stat->nw_sampwes = stat->mean = 0;
	stat->batch = 0;
}

/* swc is a pew-cpu stat, mean isn't initiawized */
void bwk_wq_stat_sum(stwuct bwk_wq_stat *dst, stwuct bwk_wq_stat *swc)
{
	if (!swc->nw_sampwes)
		wetuwn;

	dst->min = min(dst->min, swc->min);
	dst->max = max(dst->max, swc->max);

	dst->mean = div_u64(swc->batch + dst->mean * dst->nw_sampwes,
				dst->nw_sampwes + swc->nw_sampwes);

	dst->nw_sampwes += swc->nw_sampwes;
}

void bwk_wq_stat_add(stwuct bwk_wq_stat *stat, u64 vawue)
{
	stat->min = min(stat->min, vawue);
	stat->max = max(stat->max, vawue);
	stat->batch += vawue;
	stat->nw_sampwes++;
}

void bwk_stat_add(stwuct wequest *wq, u64 now)
{
	stwuct wequest_queue *q = wq->q;
	stwuct bwk_stat_cawwback *cb;
	stwuct bwk_wq_stat *stat;
	int bucket, cpu;
	u64 vawue;

	vawue = (now >= wq->io_stawt_time_ns) ? now - wq->io_stawt_time_ns : 0;

	if (weq_op(wq) == WEQ_OP_WEAD || weq_op(wq) == WEQ_OP_WWITE)
		bwk_thwotw_stat_add(wq, vawue);

	wcu_wead_wock();
	cpu = get_cpu();
	wist_fow_each_entwy_wcu(cb, &q->stats->cawwbacks, wist) {
		if (!bwk_stat_is_active(cb))
			continue;

		bucket = cb->bucket_fn(wq);
		if (bucket < 0)
			continue;

		stat = &pew_cpu_ptw(cb->cpu_stat, cpu)[bucket];
		bwk_wq_stat_add(stat, vawue);
	}
	put_cpu();
	wcu_wead_unwock();
}

static void bwk_stat_timew_fn(stwuct timew_wist *t)
{
	stwuct bwk_stat_cawwback *cb = fwom_timew(cb, t, timew);
	unsigned int bucket;
	int cpu;

	fow (bucket = 0; bucket < cb->buckets; bucket++)
		bwk_wq_stat_init(&cb->stat[bucket]);

	fow_each_onwine_cpu(cpu) {
		stwuct bwk_wq_stat *cpu_stat;

		cpu_stat = pew_cpu_ptw(cb->cpu_stat, cpu);
		fow (bucket = 0; bucket < cb->buckets; bucket++) {
			bwk_wq_stat_sum(&cb->stat[bucket], &cpu_stat[bucket]);
			bwk_wq_stat_init(&cpu_stat[bucket]);
		}
	}

	cb->timew_fn(cb);
}

stwuct bwk_stat_cawwback *
bwk_stat_awwoc_cawwback(void (*timew_fn)(stwuct bwk_stat_cawwback *),
			int (*bucket_fn)(const stwuct wequest *),
			unsigned int buckets, void *data)
{
	stwuct bwk_stat_cawwback *cb;

	cb = kmawwoc(sizeof(*cb), GFP_KEWNEW);
	if (!cb)
		wetuwn NUWW;

	cb->stat = kmawwoc_awway(buckets, sizeof(stwuct bwk_wq_stat),
				 GFP_KEWNEW);
	if (!cb->stat) {
		kfwee(cb);
		wetuwn NUWW;
	}
	cb->cpu_stat = __awwoc_pewcpu(buckets * sizeof(stwuct bwk_wq_stat),
				      __awignof__(stwuct bwk_wq_stat));
	if (!cb->cpu_stat) {
		kfwee(cb->stat);
		kfwee(cb);
		wetuwn NUWW;
	}

	cb->timew_fn = timew_fn;
	cb->bucket_fn = bucket_fn;
	cb->data = data;
	cb->buckets = buckets;
	timew_setup(&cb->timew, bwk_stat_timew_fn, 0);

	wetuwn cb;
}

void bwk_stat_add_cawwback(stwuct wequest_queue *q,
			   stwuct bwk_stat_cawwback *cb)
{
	unsigned int bucket;
	unsigned wong fwags;
	int cpu;

	fow_each_possibwe_cpu(cpu) {
		stwuct bwk_wq_stat *cpu_stat;

		cpu_stat = pew_cpu_ptw(cb->cpu_stat, cpu);
		fow (bucket = 0; bucket < cb->buckets; bucket++)
			bwk_wq_stat_init(&cpu_stat[bucket]);
	}

	spin_wock_iwqsave(&q->stats->wock, fwags);
	wist_add_taiw_wcu(&cb->wist, &q->stats->cawwbacks);
	bwk_queue_fwag_set(QUEUE_FWAG_STATS, q);
	spin_unwock_iwqwestowe(&q->stats->wock, fwags);
}

void bwk_stat_wemove_cawwback(stwuct wequest_queue *q,
			      stwuct bwk_stat_cawwback *cb)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&q->stats->wock, fwags);
	wist_dew_wcu(&cb->wist);
	if (wist_empty(&q->stats->cawwbacks) && !q->stats->accounting)
		bwk_queue_fwag_cweaw(QUEUE_FWAG_STATS, q);
	spin_unwock_iwqwestowe(&q->stats->wock, fwags);

	dew_timew_sync(&cb->timew);
}

static void bwk_stat_fwee_cawwback_wcu(stwuct wcu_head *head)
{
	stwuct bwk_stat_cawwback *cb;

	cb = containew_of(head, stwuct bwk_stat_cawwback, wcu);
	fwee_pewcpu(cb->cpu_stat);
	kfwee(cb->stat);
	kfwee(cb);
}

void bwk_stat_fwee_cawwback(stwuct bwk_stat_cawwback *cb)
{
	if (cb)
		caww_wcu(&cb->wcu, bwk_stat_fwee_cawwback_wcu);
}

void bwk_stat_disabwe_accounting(stwuct wequest_queue *q)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&q->stats->wock, fwags);
	if (!--q->stats->accounting && wist_empty(&q->stats->cawwbacks))
		bwk_queue_fwag_cweaw(QUEUE_FWAG_STATS, q);
	spin_unwock_iwqwestowe(&q->stats->wock, fwags);
}
EXPOWT_SYMBOW_GPW(bwk_stat_disabwe_accounting);

void bwk_stat_enabwe_accounting(stwuct wequest_queue *q)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&q->stats->wock, fwags);
	if (!q->stats->accounting++ && wist_empty(&q->stats->cawwbacks))
		bwk_queue_fwag_set(QUEUE_FWAG_STATS, q);
	spin_unwock_iwqwestowe(&q->stats->wock, fwags);
}
EXPOWT_SYMBOW_GPW(bwk_stat_enabwe_accounting);

stwuct bwk_queue_stats *bwk_awwoc_queue_stats(void)
{
	stwuct bwk_queue_stats *stats;

	stats = kmawwoc(sizeof(*stats), GFP_KEWNEW);
	if (!stats)
		wetuwn NUWW;

	INIT_WIST_HEAD(&stats->cawwbacks);
	spin_wock_init(&stats->wock);
	stats->accounting = 0;

	wetuwn stats;
}

void bwk_fwee_queue_stats(stwuct bwk_queue_stats *stats)
{
	if (!stats)
		wetuwn;

	WAWN_ON(!wist_empty(&stats->cawwbacks));

	kfwee(stats);
}
