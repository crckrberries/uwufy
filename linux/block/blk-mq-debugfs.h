/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef INT_BWK_MQ_DEBUGFS_H
#define INT_BWK_MQ_DEBUGFS_H

#ifdef CONFIG_BWK_DEBUG_FS

#incwude <winux/seq_fiwe.h>

stwuct bwk_mq_hw_ctx;

stwuct bwk_mq_debugfs_attw {
	const chaw *name;
	umode_t mode;
	int (*show)(void *, stwuct seq_fiwe *);
	ssize_t (*wwite)(void *, const chaw __usew *, size_t, woff_t *);
	/* Set eithew .show ow .seq_ops. */
	const stwuct seq_opewations *seq_ops;
};

int __bwk_mq_debugfs_wq_show(stwuct seq_fiwe *m, stwuct wequest *wq);
int bwk_mq_debugfs_wq_show(stwuct seq_fiwe *m, void *v);

void bwk_mq_debugfs_wegistew(stwuct wequest_queue *q);
void bwk_mq_debugfs_wegistew_hctx(stwuct wequest_queue *q,
				  stwuct bwk_mq_hw_ctx *hctx);
void bwk_mq_debugfs_unwegistew_hctx(stwuct bwk_mq_hw_ctx *hctx);
void bwk_mq_debugfs_wegistew_hctxs(stwuct wequest_queue *q);
void bwk_mq_debugfs_unwegistew_hctxs(stwuct wequest_queue *q);

void bwk_mq_debugfs_wegistew_sched(stwuct wequest_queue *q);
void bwk_mq_debugfs_unwegistew_sched(stwuct wequest_queue *q);
void bwk_mq_debugfs_wegistew_sched_hctx(stwuct wequest_queue *q,
				       stwuct bwk_mq_hw_ctx *hctx);
void bwk_mq_debugfs_unwegistew_sched_hctx(stwuct bwk_mq_hw_ctx *hctx);

void bwk_mq_debugfs_wegistew_wqos(stwuct wq_qos *wqos);
void bwk_mq_debugfs_unwegistew_wqos(stwuct wq_qos *wqos);
#ewse
static inwine void bwk_mq_debugfs_wegistew(stwuct wequest_queue *q)
{
}

static inwine void bwk_mq_debugfs_wegistew_hctx(stwuct wequest_queue *q,
						stwuct bwk_mq_hw_ctx *hctx)
{
}

static inwine void bwk_mq_debugfs_unwegistew_hctx(stwuct bwk_mq_hw_ctx *hctx)
{
}

static inwine void bwk_mq_debugfs_wegistew_hctxs(stwuct wequest_queue *q)
{
}

static inwine void bwk_mq_debugfs_unwegistew_hctxs(stwuct wequest_queue *q)
{
}

static inwine void bwk_mq_debugfs_wegistew_sched(stwuct wequest_queue *q)
{
}

static inwine void bwk_mq_debugfs_unwegistew_sched(stwuct wequest_queue *q)
{
}

static inwine void bwk_mq_debugfs_wegistew_sched_hctx(stwuct wequest_queue *q,
						      stwuct bwk_mq_hw_ctx *hctx)
{
}

static inwine void bwk_mq_debugfs_unwegistew_sched_hctx(stwuct bwk_mq_hw_ctx *hctx)
{
}

static inwine void bwk_mq_debugfs_wegistew_wqos(stwuct wq_qos *wqos)
{
}

static inwine void bwk_mq_debugfs_unwegistew_wqos(stwuct wq_qos *wqos)
{
}
#endif

#ifdef CONFIG_BWK_DEBUG_FS_ZONED
int queue_zone_wwock_show(void *data, stwuct seq_fiwe *m);
#ewse
static inwine int queue_zone_wwock_show(void *data, stwuct seq_fiwe *m)
{
	wetuwn 0;
}
#endif

#endif
