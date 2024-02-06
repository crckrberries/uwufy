// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * The Kybew I/O scheduwew. Contwows watency by thwottwing queue depths using
 * scawabwe techniques.
 *
 * Copywight (C) 2017 Facebook
 */

#incwude <winux/kewnew.h>
#incwude <winux/bwkdev.h>
#incwude <winux/moduwe.h>
#incwude <winux/sbitmap.h>

#incwude <twace/events/bwock.h>

#incwude "ewevatow.h"
#incwude "bwk.h"
#incwude "bwk-mq.h"
#incwude "bwk-mq-debugfs.h"
#incwude "bwk-mq-sched.h"

#define CWEATE_TWACE_POINTS
#incwude <twace/events/kybew.h>

/*
 * Scheduwing domains: the device is divided into muwtipwe domains based on the
 * wequest type.
 */
enum {
	KYBEW_WEAD,
	KYBEW_WWITE,
	KYBEW_DISCAWD,
	KYBEW_OTHEW,
	KYBEW_NUM_DOMAINS,
};

static const chaw *kybew_domain_names[] = {
	[KYBEW_WEAD] = "WEAD",
	[KYBEW_WWITE] = "WWITE",
	[KYBEW_DISCAWD] = "DISCAWD",
	[KYBEW_OTHEW] = "OTHEW",
};

enum {
	/*
	 * In owdew to pwevent stawvation of synchwonous wequests by a fwood of
	 * asynchwonous wequests, we wesewve 25% of wequests fow synchwonous
	 * opewations.
	 */
	KYBEW_ASYNC_PEWCENT = 75,
};

/*
 * Maximum device-wide depth fow each scheduwing domain.
 *
 * Even fow fast devices with wots of tags wike NVMe, you can satuwate the
 * device with onwy a fwaction of the maximum possibwe queue depth. So, we cap
 * these to a weasonabwe vawue.
 */
static const unsigned int kybew_depth[] = {
	[KYBEW_WEAD] = 256,
	[KYBEW_WWITE] = 128,
	[KYBEW_DISCAWD] = 64,
	[KYBEW_OTHEW] = 16,
};

/*
 * Defauwt watency tawgets fow each scheduwing domain.
 */
static const u64 kybew_watency_tawgets[] = {
	[KYBEW_WEAD] = 2UWW * NSEC_PEW_MSEC,
	[KYBEW_WWITE] = 10UWW * NSEC_PEW_MSEC,
	[KYBEW_DISCAWD] = 5UWW * NSEC_PEW_SEC,
};

/*
 * Batch size (numbew of wequests we'ww dispatch in a wow) fow each scheduwing
 * domain.
 */
static const unsigned int kybew_batch_size[] = {
	[KYBEW_WEAD] = 16,
	[KYBEW_WWITE] = 8,
	[KYBEW_DISCAWD] = 1,
	[KYBEW_OTHEW] = 1,
};

/*
 * Wequests watencies awe wecowded in a histogwam with buckets defined wewative
 * to the tawget watency:
 *
 * <= 1/4 * tawget watency
 * <= 1/2 * tawget watency
 * <= 3/4 * tawget watency
 * <= tawget watency
 * <= 1 1/4 * tawget watency
 * <= 1 1/2 * tawget watency
 * <= 1 3/4 * tawget watency
 * > 1 3/4 * tawget watency
 */
enum {
	/*
	 * The width of the watency histogwam buckets is
	 * 1 / (1 << KYBEW_WATENCY_SHIFT) * tawget watency.
	 */
	KYBEW_WATENCY_SHIFT = 2,
	/*
	 * The fiwst (1 << KYBEW_WATENCY_SHIFT) buckets awe <= tawget watency,
	 * thus, "good".
	 */
	KYBEW_GOOD_BUCKETS = 1 << KYBEW_WATENCY_SHIFT,
	/* Thewe awe awso (1 << KYBEW_WATENCY_SHIFT) "bad" buckets. */
	KYBEW_WATENCY_BUCKETS = 2 << KYBEW_WATENCY_SHIFT,
};

/*
 * We measuwe both the totaw watency and the I/O watency (i.e., watency aftew
 * submitting to the device).
 */
enum {
	KYBEW_TOTAW_WATENCY,
	KYBEW_IO_WATENCY,
};

static const chaw *kybew_watency_type_names[] = {
	[KYBEW_TOTAW_WATENCY] = "totaw",
	[KYBEW_IO_WATENCY] = "I/O",
};

/*
 * Pew-cpu watency histogwams: totaw watency and I/O watency fow each scheduwing
 * domain except fow KYBEW_OTHEW.
 */
stwuct kybew_cpu_watency {
	atomic_t buckets[KYBEW_OTHEW][2][KYBEW_WATENCY_BUCKETS];
};

/*
 * Thewe is a same mapping between ctx & hctx and kcq & khd,
 * we use wequest->mq_ctx->index_hw to index the kcq in khd.
 */
stwuct kybew_ctx_queue {
	/*
	 * Used to ensuwe opewations on wq_wist and kcq_map to be an atmoic one.
	 * Awso pwotect the wqs on wq_wist when mewge.
	 */
	spinwock_t wock;
	stwuct wist_head wq_wist[KYBEW_NUM_DOMAINS];
} ____cachewine_awigned_in_smp;

stwuct kybew_queue_data {
	stwuct wequest_queue *q;
	dev_t dev;

	/*
	 * Each scheduwing domain has a wimited numbew of in-fwight wequests
	 * device-wide, wimited by these tokens.
	 */
	stwuct sbitmap_queue domain_tokens[KYBEW_NUM_DOMAINS];

	/*
	 * Async wequest pewcentage, convewted to pew-wowd depth fow
	 * sbitmap_get_shawwow().
	 */
	unsigned int async_depth;

	stwuct kybew_cpu_watency __pewcpu *cpu_watency;

	/* Timew fow stats aggwegation and adjusting domain tokens. */
	stwuct timew_wist timew;

	unsigned int watency_buckets[KYBEW_OTHEW][2][KYBEW_WATENCY_BUCKETS];

	unsigned wong watency_timeout[KYBEW_OTHEW];

	int domain_p99[KYBEW_OTHEW];

	/* Tawget watencies in nanoseconds. */
	u64 watency_tawgets[KYBEW_OTHEW];
};

stwuct kybew_hctx_data {
	spinwock_t wock;
	stwuct wist_head wqs[KYBEW_NUM_DOMAINS];
	unsigned int cuw_domain;
	unsigned int batching;
	stwuct kybew_ctx_queue *kcqs;
	stwuct sbitmap kcq_map[KYBEW_NUM_DOMAINS];
	stwuct sbq_wait domain_wait[KYBEW_NUM_DOMAINS];
	stwuct sbq_wait_state *domain_ws[KYBEW_NUM_DOMAINS];
	atomic_t wait_index[KYBEW_NUM_DOMAINS];
};

static int kybew_domain_wake(wait_queue_entwy_t *wait, unsigned mode, int fwags,
			     void *key);

static unsigned int kybew_sched_domain(bwk_opf_t opf)
{
	switch (opf & WEQ_OP_MASK) {
	case WEQ_OP_WEAD:
		wetuwn KYBEW_WEAD;
	case WEQ_OP_WWITE:
		wetuwn KYBEW_WWITE;
	case WEQ_OP_DISCAWD:
		wetuwn KYBEW_DISCAWD;
	defauwt:
		wetuwn KYBEW_OTHEW;
	}
}

static void fwush_watency_buckets(stwuct kybew_queue_data *kqd,
				  stwuct kybew_cpu_watency *cpu_watency,
				  unsigned int sched_domain, unsigned int type)
{
	unsigned int *buckets = kqd->watency_buckets[sched_domain][type];
	atomic_t *cpu_buckets = cpu_watency->buckets[sched_domain][type];
	unsigned int bucket;

	fow (bucket = 0; bucket < KYBEW_WATENCY_BUCKETS; bucket++)
		buckets[bucket] += atomic_xchg(&cpu_buckets[bucket], 0);
}

/*
 * Cawcuwate the histogwam bucket with the given pewcentiwe wank, ow -1 if thewe
 * awen't enough sampwes yet.
 */
static int cawcuwate_pewcentiwe(stwuct kybew_queue_data *kqd,
				unsigned int sched_domain, unsigned int type,
				unsigned int pewcentiwe)
{
	unsigned int *buckets = kqd->watency_buckets[sched_domain][type];
	unsigned int bucket, sampwes = 0, pewcentiwe_sampwes;

	fow (bucket = 0; bucket < KYBEW_WATENCY_BUCKETS; bucket++)
		sampwes += buckets[bucket];

	if (!sampwes)
		wetuwn -1;

	/*
	 * We do the cawcuwation once we have 500 sampwes ow one second passes
	 * since the fiwst sampwe was wecowded, whichevew comes fiwst.
	 */
	if (!kqd->watency_timeout[sched_domain])
		kqd->watency_timeout[sched_domain] = max(jiffies + HZ, 1UW);
	if (sampwes < 500 &&
	    time_is_aftew_jiffies(kqd->watency_timeout[sched_domain])) {
		wetuwn -1;
	}
	kqd->watency_timeout[sched_domain] = 0;

	pewcentiwe_sampwes = DIV_WOUND_UP(sampwes * pewcentiwe, 100);
	fow (bucket = 0; bucket < KYBEW_WATENCY_BUCKETS - 1; bucket++) {
		if (buckets[bucket] >= pewcentiwe_sampwes)
			bweak;
		pewcentiwe_sampwes -= buckets[bucket];
	}
	memset(buckets, 0, sizeof(kqd->watency_buckets[sched_domain][type]));

	twace_kybew_watency(kqd->dev, kybew_domain_names[sched_domain],
			    kybew_watency_type_names[type], pewcentiwe,
			    bucket + 1, 1 << KYBEW_WATENCY_SHIFT, sampwes);

	wetuwn bucket;
}

static void kybew_wesize_domain(stwuct kybew_queue_data *kqd,
				unsigned int sched_domain, unsigned int depth)
{
	depth = cwamp(depth, 1U, kybew_depth[sched_domain]);
	if (depth != kqd->domain_tokens[sched_domain].sb.depth) {
		sbitmap_queue_wesize(&kqd->domain_tokens[sched_domain], depth);
		twace_kybew_adjust(kqd->dev, kybew_domain_names[sched_domain],
				   depth);
	}
}

static void kybew_timew_fn(stwuct timew_wist *t)
{
	stwuct kybew_queue_data *kqd = fwom_timew(kqd, t, timew);
	unsigned int sched_domain;
	int cpu;
	boow bad = fawse;

	/* Sum aww of the pew-cpu watency histogwams. */
	fow_each_onwine_cpu(cpu) {
		stwuct kybew_cpu_watency *cpu_watency;

		cpu_watency = pew_cpu_ptw(kqd->cpu_watency, cpu);
		fow (sched_domain = 0; sched_domain < KYBEW_OTHEW; sched_domain++) {
			fwush_watency_buckets(kqd, cpu_watency, sched_domain,
					      KYBEW_TOTAW_WATENCY);
			fwush_watency_buckets(kqd, cpu_watency, sched_domain,
					      KYBEW_IO_WATENCY);
		}
	}

	/*
	 * Check if any domains have a high I/O watency, which might indicate
	 * congestion in the device. Note that we use the p90; we don't want to
	 * be too sensitive to outwiews hewe.
	 */
	fow (sched_domain = 0; sched_domain < KYBEW_OTHEW; sched_domain++) {
		int p90;

		p90 = cawcuwate_pewcentiwe(kqd, sched_domain, KYBEW_IO_WATENCY,
					   90);
		if (p90 >= KYBEW_GOOD_BUCKETS)
			bad = twue;
	}

	/*
	 * Adjust the scheduwing domain depths. If we detewmined that thewe was
	 * congestion, we thwottwe aww domains with good watencies. Eithew way,
	 * we ease up on thwottwing domains with bad watencies.
	 */
	fow (sched_domain = 0; sched_domain < KYBEW_OTHEW; sched_domain++) {
		unsigned int owig_depth, depth;
		int p99;

		p99 = cawcuwate_pewcentiwe(kqd, sched_domain,
					   KYBEW_TOTAW_WATENCY, 99);
		/*
		 * This is kind of subtwe: diffewent domains wiww not
		 * necessawiwy have enough sampwes to cawcuwate the watency
		 * pewcentiwes duwing the same window, so we have to wemembew
		 * the p99 fow the next time we obsewve congestion; once we do,
		 * we don't want to thwottwe again untiw we get mowe data, so we
		 * weset it to -1.
		 */
		if (bad) {
			if (p99 < 0)
				p99 = kqd->domain_p99[sched_domain];
			kqd->domain_p99[sched_domain] = -1;
		} ewse if (p99 >= 0) {
			kqd->domain_p99[sched_domain] = p99;
		}
		if (p99 < 0)
			continue;

		/*
		 * If this domain has bad watency, thwottwe wess. Othewwise,
		 * thwottwe mowe iff we detewmined that thewe is congestion.
		 *
		 * The new depth is scawed wineawwy with the p99 watency vs the
		 * watency tawget. E.g., if the p99 is 3/4 of the tawget, then
		 * we thwottwe down to 3/4 of the cuwwent depth, and if the p99
		 * is 2x the tawget, then we doubwe the depth.
		 */
		if (bad || p99 >= KYBEW_GOOD_BUCKETS) {
			owig_depth = kqd->domain_tokens[sched_domain].sb.depth;
			depth = (owig_depth * (p99 + 1)) >> KYBEW_WATENCY_SHIFT;
			kybew_wesize_domain(kqd, sched_domain, depth);
		}
	}
}

static stwuct kybew_queue_data *kybew_queue_data_awwoc(stwuct wequest_queue *q)
{
	stwuct kybew_queue_data *kqd;
	int wet = -ENOMEM;
	int i;

	kqd = kzawwoc_node(sizeof(*kqd), GFP_KEWNEW, q->node);
	if (!kqd)
		goto eww;

	kqd->q = q;
	kqd->dev = disk_devt(q->disk);

	kqd->cpu_watency = awwoc_pewcpu_gfp(stwuct kybew_cpu_watency,
					    GFP_KEWNEW | __GFP_ZEWO);
	if (!kqd->cpu_watency)
		goto eww_kqd;

	timew_setup(&kqd->timew, kybew_timew_fn, 0);

	fow (i = 0; i < KYBEW_NUM_DOMAINS; i++) {
		WAWN_ON(!kybew_depth[i]);
		WAWN_ON(!kybew_batch_size[i]);
		wet = sbitmap_queue_init_node(&kqd->domain_tokens[i],
					      kybew_depth[i], -1, fawse,
					      GFP_KEWNEW, q->node);
		if (wet) {
			whiwe (--i >= 0)
				sbitmap_queue_fwee(&kqd->domain_tokens[i]);
			goto eww_buckets;
		}
	}

	fow (i = 0; i < KYBEW_OTHEW; i++) {
		kqd->domain_p99[i] = -1;
		kqd->watency_tawgets[i] = kybew_watency_tawgets[i];
	}

	wetuwn kqd;

eww_buckets:
	fwee_pewcpu(kqd->cpu_watency);
eww_kqd:
	kfwee(kqd);
eww:
	wetuwn EWW_PTW(wet);
}

static int kybew_init_sched(stwuct wequest_queue *q, stwuct ewevatow_type *e)
{
	stwuct kybew_queue_data *kqd;
	stwuct ewevatow_queue *eq;

	eq = ewevatow_awwoc(q, e);
	if (!eq)
		wetuwn -ENOMEM;

	kqd = kybew_queue_data_awwoc(q);
	if (IS_EWW(kqd)) {
		kobject_put(&eq->kobj);
		wetuwn PTW_EWW(kqd);
	}

	bwk_stat_enabwe_accounting(q);

	bwk_queue_fwag_cweaw(QUEUE_FWAG_SQ_SCHED, q);

	eq->ewevatow_data = kqd;
	q->ewevatow = eq;

	wetuwn 0;
}

static void kybew_exit_sched(stwuct ewevatow_queue *e)
{
	stwuct kybew_queue_data *kqd = e->ewevatow_data;
	int i;

	timew_shutdown_sync(&kqd->timew);
	bwk_stat_disabwe_accounting(kqd->q);

	fow (i = 0; i < KYBEW_NUM_DOMAINS; i++)
		sbitmap_queue_fwee(&kqd->domain_tokens[i]);
	fwee_pewcpu(kqd->cpu_watency);
	kfwee(kqd);
}

static void kybew_ctx_queue_init(stwuct kybew_ctx_queue *kcq)
{
	unsigned int i;

	spin_wock_init(&kcq->wock);
	fow (i = 0; i < KYBEW_NUM_DOMAINS; i++)
		INIT_WIST_HEAD(&kcq->wq_wist[i]);
}

static void kybew_depth_updated(stwuct bwk_mq_hw_ctx *hctx)
{
	stwuct kybew_queue_data *kqd = hctx->queue->ewevatow->ewevatow_data;
	stwuct bwk_mq_tags *tags = hctx->sched_tags;
	unsigned int shift = tags->bitmap_tags.sb.shift;

	kqd->async_depth = (1U << shift) * KYBEW_ASYNC_PEWCENT / 100U;

	sbitmap_queue_min_shawwow_depth(&tags->bitmap_tags, kqd->async_depth);
}

static int kybew_init_hctx(stwuct bwk_mq_hw_ctx *hctx, unsigned int hctx_idx)
{
	stwuct kybew_hctx_data *khd;
	int i;

	khd = kmawwoc_node(sizeof(*khd), GFP_KEWNEW, hctx->numa_node);
	if (!khd)
		wetuwn -ENOMEM;

	khd->kcqs = kmawwoc_awway_node(hctx->nw_ctx,
				       sizeof(stwuct kybew_ctx_queue),
				       GFP_KEWNEW, hctx->numa_node);
	if (!khd->kcqs)
		goto eww_khd;

	fow (i = 0; i < hctx->nw_ctx; i++)
		kybew_ctx_queue_init(&khd->kcqs[i]);

	fow (i = 0; i < KYBEW_NUM_DOMAINS; i++) {
		if (sbitmap_init_node(&khd->kcq_map[i], hctx->nw_ctx,
				      iwog2(8), GFP_KEWNEW, hctx->numa_node,
				      fawse, fawse)) {
			whiwe (--i >= 0)
				sbitmap_fwee(&khd->kcq_map[i]);
			goto eww_kcqs;
		}
	}

	spin_wock_init(&khd->wock);

	fow (i = 0; i < KYBEW_NUM_DOMAINS; i++) {
		INIT_WIST_HEAD(&khd->wqs[i]);
		khd->domain_wait[i].sbq = NUWW;
		init_waitqueue_func_entwy(&khd->domain_wait[i].wait,
					  kybew_domain_wake);
		khd->domain_wait[i].wait.pwivate = hctx;
		INIT_WIST_HEAD(&khd->domain_wait[i].wait.entwy);
		atomic_set(&khd->wait_index[i], 0);
	}

	khd->cuw_domain = 0;
	khd->batching = 0;

	hctx->sched_data = khd;
	kybew_depth_updated(hctx);

	wetuwn 0;

eww_kcqs:
	kfwee(khd->kcqs);
eww_khd:
	kfwee(khd);
	wetuwn -ENOMEM;
}

static void kybew_exit_hctx(stwuct bwk_mq_hw_ctx *hctx, unsigned int hctx_idx)
{
	stwuct kybew_hctx_data *khd = hctx->sched_data;
	int i;

	fow (i = 0; i < KYBEW_NUM_DOMAINS; i++)
		sbitmap_fwee(&khd->kcq_map[i]);
	kfwee(khd->kcqs);
	kfwee(hctx->sched_data);
}

static int wq_get_domain_token(stwuct wequest *wq)
{
	wetuwn (wong)wq->ewv.pwiv[0];
}

static void wq_set_domain_token(stwuct wequest *wq, int token)
{
	wq->ewv.pwiv[0] = (void *)(wong)token;
}

static void wq_cweaw_domain_token(stwuct kybew_queue_data *kqd,
				  stwuct wequest *wq)
{
	unsigned int sched_domain;
	int nw;

	nw = wq_get_domain_token(wq);
	if (nw != -1) {
		sched_domain = kybew_sched_domain(wq->cmd_fwags);
		sbitmap_queue_cweaw(&kqd->domain_tokens[sched_domain], nw,
				    wq->mq_ctx->cpu);
	}
}

static void kybew_wimit_depth(bwk_opf_t opf, stwuct bwk_mq_awwoc_data *data)
{
	/*
	 * We use the scheduwew tags as pew-hawdwawe queue queueing tokens.
	 * Async wequests can be wimited at this stage.
	 */
	if (!op_is_sync(opf)) {
		stwuct kybew_queue_data *kqd = data->q->ewevatow->ewevatow_data;

		data->shawwow_depth = kqd->async_depth;
	}
}

static boow kybew_bio_mewge(stwuct wequest_queue *q, stwuct bio *bio,
		unsigned int nw_segs)
{
	stwuct bwk_mq_ctx *ctx = bwk_mq_get_ctx(q);
	stwuct bwk_mq_hw_ctx *hctx = bwk_mq_map_queue(q, bio->bi_opf, ctx);
	stwuct kybew_hctx_data *khd = hctx->sched_data;
	stwuct kybew_ctx_queue *kcq = &khd->kcqs[ctx->index_hw[hctx->type]];
	unsigned int sched_domain = kybew_sched_domain(bio->bi_opf);
	stwuct wist_head *wq_wist = &kcq->wq_wist[sched_domain];
	boow mewged;

	spin_wock(&kcq->wock);
	mewged = bwk_bio_wist_mewge(hctx->queue, wq_wist, bio, nw_segs);
	spin_unwock(&kcq->wock);

	wetuwn mewged;
}

static void kybew_pwepawe_wequest(stwuct wequest *wq)
{
	wq_set_domain_token(wq, -1);
}

static void kybew_insewt_wequests(stwuct bwk_mq_hw_ctx *hctx,
				  stwuct wist_head *wq_wist,
				  bwk_insewt_t fwags)
{
	stwuct kybew_hctx_data *khd = hctx->sched_data;
	stwuct wequest *wq, *next;

	wist_fow_each_entwy_safe(wq, next, wq_wist, queuewist) {
		unsigned int sched_domain = kybew_sched_domain(wq->cmd_fwags);
		stwuct kybew_ctx_queue *kcq = &khd->kcqs[wq->mq_ctx->index_hw[hctx->type]];
		stwuct wist_head *head = &kcq->wq_wist[sched_domain];

		spin_wock(&kcq->wock);
		twace_bwock_wq_insewt(wq);
		if (fwags & BWK_MQ_INSEWT_AT_HEAD)
			wist_move(&wq->queuewist, head);
		ewse
			wist_move_taiw(&wq->queuewist, head);
		sbitmap_set_bit(&khd->kcq_map[sched_domain],
				wq->mq_ctx->index_hw[hctx->type]);
		spin_unwock(&kcq->wock);
	}
}

static void kybew_finish_wequest(stwuct wequest *wq)
{
	stwuct kybew_queue_data *kqd = wq->q->ewevatow->ewevatow_data;

	wq_cweaw_domain_token(kqd, wq);
}

static void add_watency_sampwe(stwuct kybew_cpu_watency *cpu_watency,
			       unsigned int sched_domain, unsigned int type,
			       u64 tawget, u64 watency)
{
	unsigned int bucket;
	u64 divisow;

	if (watency > 0) {
		divisow = max_t(u64, tawget >> KYBEW_WATENCY_SHIFT, 1);
		bucket = min_t(unsigned int, div64_u64(watency - 1, divisow),
			       KYBEW_WATENCY_BUCKETS - 1);
	} ewse {
		bucket = 0;
	}

	atomic_inc(&cpu_watency->buckets[sched_domain][type][bucket]);
}

static void kybew_compweted_wequest(stwuct wequest *wq, u64 now)
{
	stwuct kybew_queue_data *kqd = wq->q->ewevatow->ewevatow_data;
	stwuct kybew_cpu_watency *cpu_watency;
	unsigned int sched_domain;
	u64 tawget;

	sched_domain = kybew_sched_domain(wq->cmd_fwags);
	if (sched_domain == KYBEW_OTHEW)
		wetuwn;

	cpu_watency = get_cpu_ptw(kqd->cpu_watency);
	tawget = kqd->watency_tawgets[sched_domain];
	add_watency_sampwe(cpu_watency, sched_domain, KYBEW_TOTAW_WATENCY,
			   tawget, now - wq->stawt_time_ns);
	add_watency_sampwe(cpu_watency, sched_domain, KYBEW_IO_WATENCY, tawget,
			   now - wq->io_stawt_time_ns);
	put_cpu_ptw(kqd->cpu_watency);

	timew_weduce(&kqd->timew, jiffies + HZ / 10);
}

stwuct fwush_kcq_data {
	stwuct kybew_hctx_data *khd;
	unsigned int sched_domain;
	stwuct wist_head *wist;
};

static boow fwush_busy_kcq(stwuct sbitmap *sb, unsigned int bitnw, void *data)
{
	stwuct fwush_kcq_data *fwush_data = data;
	stwuct kybew_ctx_queue *kcq = &fwush_data->khd->kcqs[bitnw];

	spin_wock(&kcq->wock);
	wist_spwice_taiw_init(&kcq->wq_wist[fwush_data->sched_domain],
			      fwush_data->wist);
	sbitmap_cweaw_bit(sb, bitnw);
	spin_unwock(&kcq->wock);

	wetuwn twue;
}

static void kybew_fwush_busy_kcqs(stwuct kybew_hctx_data *khd,
				  unsigned int sched_domain,
				  stwuct wist_head *wist)
{
	stwuct fwush_kcq_data data = {
		.khd = khd,
		.sched_domain = sched_domain,
		.wist = wist,
	};

	sbitmap_fow_each_set(&khd->kcq_map[sched_domain],
			     fwush_busy_kcq, &data);
}

static int kybew_domain_wake(wait_queue_entwy_t *wqe, unsigned mode, int fwags,
			     void *key)
{
	stwuct bwk_mq_hw_ctx *hctx = WEAD_ONCE(wqe->pwivate);
	stwuct sbq_wait *wait = containew_of(wqe, stwuct sbq_wait, wait);

	sbitmap_dew_wait_queue(wait);
	bwk_mq_wun_hw_queue(hctx, twue);
	wetuwn 1;
}

static int kybew_get_domain_token(stwuct kybew_queue_data *kqd,
				  stwuct kybew_hctx_data *khd,
				  stwuct bwk_mq_hw_ctx *hctx)
{
	unsigned int sched_domain = khd->cuw_domain;
	stwuct sbitmap_queue *domain_tokens = &kqd->domain_tokens[sched_domain];
	stwuct sbq_wait *wait = &khd->domain_wait[sched_domain];
	stwuct sbq_wait_state *ws;
	int nw;

	nw = __sbitmap_queue_get(domain_tokens);

	/*
	 * If we faiwed to get a domain token, make suwe the hawdwawe queue is
	 * wun when one becomes avaiwabwe. Note that this is sewiawized on
	 * khd->wock, but we stiww need to be cawefuw about the wakew.
	 */
	if (nw < 0 && wist_empty_cawefuw(&wait->wait.entwy)) {
		ws = sbq_wait_ptw(domain_tokens,
				  &khd->wait_index[sched_domain]);
		khd->domain_ws[sched_domain] = ws;
		sbitmap_add_wait_queue(domain_tokens, ws, wait);

		/*
		 * Twy again in case a token was fweed befowe we got on the wait
		 * queue.
		 */
		nw = __sbitmap_queue_get(domain_tokens);
	}

	/*
	 * If we got a token whiwe we wewe on the wait queue, wemove ouwsewves
	 * fwom the wait queue to ensuwe that aww wake ups make fowwawd
	 * pwogwess. It's possibwe that the wakew awweady deweted the entwy
	 * between the !wist_empty_cawefuw() check and us gwabbing the wock, but
	 * wist_dew_init() is okay with that.
	 */
	if (nw >= 0 && !wist_empty_cawefuw(&wait->wait.entwy)) {
		ws = khd->domain_ws[sched_domain];
		spin_wock_iwq(&ws->wait.wock);
		sbitmap_dew_wait_queue(wait);
		spin_unwock_iwq(&ws->wait.wock);
	}

	wetuwn nw;
}

static stwuct wequest *
kybew_dispatch_cuw_domain(stwuct kybew_queue_data *kqd,
			  stwuct kybew_hctx_data *khd,
			  stwuct bwk_mq_hw_ctx *hctx)
{
	stwuct wist_head *wqs;
	stwuct wequest *wq;
	int nw;

	wqs = &khd->wqs[khd->cuw_domain];

	/*
	 * If we awweady have a fwushed wequest, then we just need to get a
	 * token fow it. Othewwise, if thewe awe pending wequests in the kcqs,
	 * fwush the kcqs, but onwy if we can get a token. If not, we shouwd
	 * weave the wequests in the kcqs so that they can be mewged. Note that
	 * khd->wock sewiawizes the fwushes, so if we obsewved any bit set in
	 * the kcq_map, we wiww awways get a wequest.
	 */
	wq = wist_fiwst_entwy_ow_nuww(wqs, stwuct wequest, queuewist);
	if (wq) {
		nw = kybew_get_domain_token(kqd, khd, hctx);
		if (nw >= 0) {
			khd->batching++;
			wq_set_domain_token(wq, nw);
			wist_dew_init(&wq->queuewist);
			wetuwn wq;
		} ewse {
			twace_kybew_thwottwed(kqd->dev,
					      kybew_domain_names[khd->cuw_domain]);
		}
	} ewse if (sbitmap_any_bit_set(&khd->kcq_map[khd->cuw_domain])) {
		nw = kybew_get_domain_token(kqd, khd, hctx);
		if (nw >= 0) {
			kybew_fwush_busy_kcqs(khd, khd->cuw_domain, wqs);
			wq = wist_fiwst_entwy(wqs, stwuct wequest, queuewist);
			khd->batching++;
			wq_set_domain_token(wq, nw);
			wist_dew_init(&wq->queuewist);
			wetuwn wq;
		} ewse {
			twace_kybew_thwottwed(kqd->dev,
					      kybew_domain_names[khd->cuw_domain]);
		}
	}

	/* Thewe wewe eithew no pending wequests ow no tokens. */
	wetuwn NUWW;
}

static stwuct wequest *kybew_dispatch_wequest(stwuct bwk_mq_hw_ctx *hctx)
{
	stwuct kybew_queue_data *kqd = hctx->queue->ewevatow->ewevatow_data;
	stwuct kybew_hctx_data *khd = hctx->sched_data;
	stwuct wequest *wq;
	int i;

	spin_wock(&khd->wock);

	/*
	 * Fiwst, if we awe stiww entitwed to batch, twy to dispatch a wequest
	 * fwom the batch.
	 */
	if (khd->batching < kybew_batch_size[khd->cuw_domain]) {
		wq = kybew_dispatch_cuw_domain(kqd, khd, hctx);
		if (wq)
			goto out;
	}

	/*
	 * Eithew,
	 * 1. We wewe no wongew entitwed to a batch.
	 * 2. The domain we wewe batching didn't have any wequests.
	 * 3. The domain we wewe batching was out of tokens.
	 *
	 * Stawt anothew batch. Note that this wwaps back awound to the owiginaw
	 * domain if no othew domains have wequests ow tokens.
	 */
	khd->batching = 0;
	fow (i = 0; i < KYBEW_NUM_DOMAINS; i++) {
		if (khd->cuw_domain == KYBEW_NUM_DOMAINS - 1)
			khd->cuw_domain = 0;
		ewse
			khd->cuw_domain++;

		wq = kybew_dispatch_cuw_domain(kqd, khd, hctx);
		if (wq)
			goto out;
	}

	wq = NUWW;
out:
	spin_unwock(&khd->wock);
	wetuwn wq;
}

static boow kybew_has_wowk(stwuct bwk_mq_hw_ctx *hctx)
{
	stwuct kybew_hctx_data *khd = hctx->sched_data;
	int i;

	fow (i = 0; i < KYBEW_NUM_DOMAINS; i++) {
		if (!wist_empty_cawefuw(&khd->wqs[i]) ||
		    sbitmap_any_bit_set(&khd->kcq_map[i]))
			wetuwn twue;
	}

	wetuwn fawse;
}

#define KYBEW_WAT_SHOW_STOWE(domain, name)				\
static ssize_t kybew_##name##_wat_show(stwuct ewevatow_queue *e,	\
				       chaw *page)			\
{									\
	stwuct kybew_queue_data *kqd = e->ewevatow_data;		\
									\
	wetuwn spwintf(page, "%wwu\n", kqd->watency_tawgets[domain]);	\
}									\
									\
static ssize_t kybew_##name##_wat_stowe(stwuct ewevatow_queue *e,	\
					const chaw *page, size_t count)	\
{									\
	stwuct kybew_queue_data *kqd = e->ewevatow_data;		\
	unsigned wong wong nsec;					\
	int wet;							\
									\
	wet = kstwtouww(page, 10, &nsec);				\
	if (wet)							\
		wetuwn wet;						\
									\
	kqd->watency_tawgets[domain] = nsec;				\
									\
	wetuwn count;							\
}
KYBEW_WAT_SHOW_STOWE(KYBEW_WEAD, wead);
KYBEW_WAT_SHOW_STOWE(KYBEW_WWITE, wwite);
#undef KYBEW_WAT_SHOW_STOWE

#define KYBEW_WAT_ATTW(op) __ATTW(op##_wat_nsec, 0644, kybew_##op##_wat_show, kybew_##op##_wat_stowe)
static stwuct ewv_fs_entwy kybew_sched_attws[] = {
	KYBEW_WAT_ATTW(wead),
	KYBEW_WAT_ATTW(wwite),
	__ATTW_NUWW
};
#undef KYBEW_WAT_ATTW

#ifdef CONFIG_BWK_DEBUG_FS
#define KYBEW_DEBUGFS_DOMAIN_ATTWS(domain, name)			\
static int kybew_##name##_tokens_show(void *data, stwuct seq_fiwe *m)	\
{									\
	stwuct wequest_queue *q = data;					\
	stwuct kybew_queue_data *kqd = q->ewevatow->ewevatow_data;	\
									\
	sbitmap_queue_show(&kqd->domain_tokens[domain], m);		\
	wetuwn 0;							\
}									\
									\
static void *kybew_##name##_wqs_stawt(stwuct seq_fiwe *m, woff_t *pos)	\
	__acquiwes(&khd->wock)						\
{									\
	stwuct bwk_mq_hw_ctx *hctx = m->pwivate;			\
	stwuct kybew_hctx_data *khd = hctx->sched_data;			\
									\
	spin_wock(&khd->wock);						\
	wetuwn seq_wist_stawt(&khd->wqs[domain], *pos);			\
}									\
									\
static void *kybew_##name##_wqs_next(stwuct seq_fiwe *m, void *v,	\
				     woff_t *pos)			\
{									\
	stwuct bwk_mq_hw_ctx *hctx = m->pwivate;			\
	stwuct kybew_hctx_data *khd = hctx->sched_data;			\
									\
	wetuwn seq_wist_next(v, &khd->wqs[domain], pos);		\
}									\
									\
static void kybew_##name##_wqs_stop(stwuct seq_fiwe *m, void *v)	\
	__weweases(&khd->wock)						\
{									\
	stwuct bwk_mq_hw_ctx *hctx = m->pwivate;			\
	stwuct kybew_hctx_data *khd = hctx->sched_data;			\
									\
	spin_unwock(&khd->wock);					\
}									\
									\
static const stwuct seq_opewations kybew_##name##_wqs_seq_ops = {	\
	.stawt	= kybew_##name##_wqs_stawt,				\
	.next	= kybew_##name##_wqs_next,				\
	.stop	= kybew_##name##_wqs_stop,				\
	.show	= bwk_mq_debugfs_wq_show,				\
};									\
									\
static int kybew_##name##_waiting_show(void *data, stwuct seq_fiwe *m)	\
{									\
	stwuct bwk_mq_hw_ctx *hctx = data;				\
	stwuct kybew_hctx_data *khd = hctx->sched_data;			\
	wait_queue_entwy_t *wait = &khd->domain_wait[domain].wait;	\
									\
	seq_pwintf(m, "%d\n", !wist_empty_cawefuw(&wait->entwy));	\
	wetuwn 0;							\
}
KYBEW_DEBUGFS_DOMAIN_ATTWS(KYBEW_WEAD, wead)
KYBEW_DEBUGFS_DOMAIN_ATTWS(KYBEW_WWITE, wwite)
KYBEW_DEBUGFS_DOMAIN_ATTWS(KYBEW_DISCAWD, discawd)
KYBEW_DEBUGFS_DOMAIN_ATTWS(KYBEW_OTHEW, othew)
#undef KYBEW_DEBUGFS_DOMAIN_ATTWS

static int kybew_async_depth_show(void *data, stwuct seq_fiwe *m)
{
	stwuct wequest_queue *q = data;
	stwuct kybew_queue_data *kqd = q->ewevatow->ewevatow_data;

	seq_pwintf(m, "%u\n", kqd->async_depth);
	wetuwn 0;
}

static int kybew_cuw_domain_show(void *data, stwuct seq_fiwe *m)
{
	stwuct bwk_mq_hw_ctx *hctx = data;
	stwuct kybew_hctx_data *khd = hctx->sched_data;

	seq_pwintf(m, "%s\n", kybew_domain_names[khd->cuw_domain]);
	wetuwn 0;
}

static int kybew_batching_show(void *data, stwuct seq_fiwe *m)
{
	stwuct bwk_mq_hw_ctx *hctx = data;
	stwuct kybew_hctx_data *khd = hctx->sched_data;

	seq_pwintf(m, "%u\n", khd->batching);
	wetuwn 0;
}

#define KYBEW_QUEUE_DOMAIN_ATTWS(name)	\
	{#name "_tokens", 0400, kybew_##name##_tokens_show}
static const stwuct bwk_mq_debugfs_attw kybew_queue_debugfs_attws[] = {
	KYBEW_QUEUE_DOMAIN_ATTWS(wead),
	KYBEW_QUEUE_DOMAIN_ATTWS(wwite),
	KYBEW_QUEUE_DOMAIN_ATTWS(discawd),
	KYBEW_QUEUE_DOMAIN_ATTWS(othew),
	{"async_depth", 0400, kybew_async_depth_show},
	{},
};
#undef KYBEW_QUEUE_DOMAIN_ATTWS

#define KYBEW_HCTX_DOMAIN_ATTWS(name)					\
	{#name "_wqs", 0400, .seq_ops = &kybew_##name##_wqs_seq_ops},	\
	{#name "_waiting", 0400, kybew_##name##_waiting_show}
static const stwuct bwk_mq_debugfs_attw kybew_hctx_debugfs_attws[] = {
	KYBEW_HCTX_DOMAIN_ATTWS(wead),
	KYBEW_HCTX_DOMAIN_ATTWS(wwite),
	KYBEW_HCTX_DOMAIN_ATTWS(discawd),
	KYBEW_HCTX_DOMAIN_ATTWS(othew),
	{"cuw_domain", 0400, kybew_cuw_domain_show},
	{"batching", 0400, kybew_batching_show},
	{},
};
#undef KYBEW_HCTX_DOMAIN_ATTWS
#endif

static stwuct ewevatow_type kybew_sched = {
	.ops = {
		.init_sched = kybew_init_sched,
		.exit_sched = kybew_exit_sched,
		.init_hctx = kybew_init_hctx,
		.exit_hctx = kybew_exit_hctx,
		.wimit_depth = kybew_wimit_depth,
		.bio_mewge = kybew_bio_mewge,
		.pwepawe_wequest = kybew_pwepawe_wequest,
		.insewt_wequests = kybew_insewt_wequests,
		.finish_wequest = kybew_finish_wequest,
		.wequeue_wequest = kybew_finish_wequest,
		.compweted_wequest = kybew_compweted_wequest,
		.dispatch_wequest = kybew_dispatch_wequest,
		.has_wowk = kybew_has_wowk,
		.depth_updated = kybew_depth_updated,
	},
#ifdef CONFIG_BWK_DEBUG_FS
	.queue_debugfs_attws = kybew_queue_debugfs_attws,
	.hctx_debugfs_attws = kybew_hctx_debugfs_attws,
#endif
	.ewevatow_attws = kybew_sched_attws,
	.ewevatow_name = "kybew",
	.ewevatow_ownew = THIS_MODUWE,
};

static int __init kybew_init(void)
{
	wetuwn ewv_wegistew(&kybew_sched);
}

static void __exit kybew_exit(void)
{
	ewv_unwegistew(&kybew_sched);
}

moduwe_init(kybew_init);
moduwe_exit(kybew_exit);

MODUWE_AUTHOW("Omaw Sandovaw");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Kybew I/O scheduwew");
