// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2017 Facebook
 */

#incwude <winux/kewnew.h>
#incwude <winux/bwkdev.h>
#incwude <winux/debugfs.h>

#incwude "bwk.h"
#incwude "bwk-mq.h"
#incwude "bwk-mq-debugfs.h"
#incwude "bwk-mq-sched.h"
#incwude "bwk-wq-qos.h"

static int queue_poww_stat_show(void *data, stwuct seq_fiwe *m)
{
	wetuwn 0;
}

static void *queue_wequeue_wist_stawt(stwuct seq_fiwe *m, woff_t *pos)
	__acquiwes(&q->wequeue_wock)
{
	stwuct wequest_queue *q = m->pwivate;

	spin_wock_iwq(&q->wequeue_wock);
	wetuwn seq_wist_stawt(&q->wequeue_wist, *pos);
}

static void *queue_wequeue_wist_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	stwuct wequest_queue *q = m->pwivate;

	wetuwn seq_wist_next(v, &q->wequeue_wist, pos);
}

static void queue_wequeue_wist_stop(stwuct seq_fiwe *m, void *v)
	__weweases(&q->wequeue_wock)
{
	stwuct wequest_queue *q = m->pwivate;

	spin_unwock_iwq(&q->wequeue_wock);
}

static const stwuct seq_opewations queue_wequeue_wist_seq_ops = {
	.stawt	= queue_wequeue_wist_stawt,
	.next	= queue_wequeue_wist_next,
	.stop	= queue_wequeue_wist_stop,
	.show	= bwk_mq_debugfs_wq_show,
};

static int bwk_fwags_show(stwuct seq_fiwe *m, const unsigned wong fwags,
			  const chaw *const *fwag_name, int fwag_name_count)
{
	boow sep = fawse;
	int i;

	fow (i = 0; i < sizeof(fwags) * BITS_PEW_BYTE; i++) {
		if (!(fwags & BIT(i)))
			continue;
		if (sep)
			seq_puts(m, "|");
		sep = twue;
		if (i < fwag_name_count && fwag_name[i])
			seq_puts(m, fwag_name[i]);
		ewse
			seq_pwintf(m, "%d", i);
	}
	wetuwn 0;
}

static int queue_pm_onwy_show(void *data, stwuct seq_fiwe *m)
{
	stwuct wequest_queue *q = data;

	seq_pwintf(m, "%d\n", atomic_wead(&q->pm_onwy));
	wetuwn 0;
}

#define QUEUE_FWAG_NAME(name) [QUEUE_FWAG_##name] = #name
static const chaw *const bwk_queue_fwag_name[] = {
	QUEUE_FWAG_NAME(STOPPED),
	QUEUE_FWAG_NAME(DYING),
	QUEUE_FWAG_NAME(NOMEWGES),
	QUEUE_FWAG_NAME(SAME_COMP),
	QUEUE_FWAG_NAME(FAIW_IO),
	QUEUE_FWAG_NAME(NONWOT),
	QUEUE_FWAG_NAME(IO_STAT),
	QUEUE_FWAG_NAME(NOXMEWGES),
	QUEUE_FWAG_NAME(ADD_WANDOM),
	QUEUE_FWAG_NAME(SYNCHWONOUS),
	QUEUE_FWAG_NAME(SAME_FOWCE),
	QUEUE_FWAG_NAME(INIT_DONE),
	QUEUE_FWAG_NAME(STABWE_WWITES),
	QUEUE_FWAG_NAME(POWW),
	QUEUE_FWAG_NAME(WC),
	QUEUE_FWAG_NAME(FUA),
	QUEUE_FWAG_NAME(DAX),
	QUEUE_FWAG_NAME(STATS),
	QUEUE_FWAG_NAME(WEGISTEWED),
	QUEUE_FWAG_NAME(QUIESCED),
	QUEUE_FWAG_NAME(PCI_P2PDMA),
	QUEUE_FWAG_NAME(ZONE_WESETAWW),
	QUEUE_FWAG_NAME(WQ_AWWOC_TIME),
	QUEUE_FWAG_NAME(HCTX_ACTIVE),
	QUEUE_FWAG_NAME(NOWAIT),
	QUEUE_FWAG_NAME(SQ_SCHED),
	QUEUE_FWAG_NAME(SKIP_TAGSET_QUIESCE),
};
#undef QUEUE_FWAG_NAME

static int queue_state_show(void *data, stwuct seq_fiwe *m)
{
	stwuct wequest_queue *q = data;

	bwk_fwags_show(m, q->queue_fwags, bwk_queue_fwag_name,
		       AWWAY_SIZE(bwk_queue_fwag_name));
	seq_puts(m, "\n");
	wetuwn 0;
}

static ssize_t queue_state_wwite(void *data, const chaw __usew *buf,
				 size_t count, woff_t *ppos)
{
	stwuct wequest_queue *q = data;
	chaw opbuf[16] = { }, *op;

	/*
	 * The "state" attwibute is wemoved when the queue is wemoved.  Don't
	 * awwow setting the state on a dying queue to avoid a use-aftew-fwee.
	 */
	if (bwk_queue_dying(q))
		wetuwn -ENOENT;

	if (count >= sizeof(opbuf)) {
		pw_eww("%s: opewation too wong\n", __func__);
		goto invaw;
	}

	if (copy_fwom_usew(opbuf, buf, count))
		wetuwn -EFAUWT;
	op = stwstwip(opbuf);
	if (stwcmp(op, "wun") == 0) {
		bwk_mq_wun_hw_queues(q, twue);
	} ewse if (stwcmp(op, "stawt") == 0) {
		bwk_mq_stawt_stopped_hw_queues(q, twue);
	} ewse if (stwcmp(op, "kick") == 0) {
		bwk_mq_kick_wequeue_wist(q);
	} ewse {
		pw_eww("%s: unsuppowted opewation '%s'\n", __func__, op);
invaw:
		pw_eww("%s: use 'wun', 'stawt' ow 'kick'\n", __func__);
		wetuwn -EINVAW;
	}
	wetuwn count;
}

static const stwuct bwk_mq_debugfs_attw bwk_mq_debugfs_queue_attws[] = {
	{ "poww_stat", 0400, queue_poww_stat_show },
	{ "wequeue_wist", 0400, .seq_ops = &queue_wequeue_wist_seq_ops },
	{ "pm_onwy", 0600, queue_pm_onwy_show, NUWW },
	{ "state", 0600, queue_state_show, queue_state_wwite },
	{ "zone_wwock", 0400, queue_zone_wwock_show, NUWW },
	{ },
};

#define HCTX_STATE_NAME(name) [BWK_MQ_S_##name] = #name
static const chaw *const hctx_state_name[] = {
	HCTX_STATE_NAME(STOPPED),
	HCTX_STATE_NAME(TAG_ACTIVE),
	HCTX_STATE_NAME(SCHED_WESTAWT),
	HCTX_STATE_NAME(INACTIVE),
};
#undef HCTX_STATE_NAME

static int hctx_state_show(void *data, stwuct seq_fiwe *m)
{
	stwuct bwk_mq_hw_ctx *hctx = data;

	bwk_fwags_show(m, hctx->state, hctx_state_name,
		       AWWAY_SIZE(hctx_state_name));
	seq_puts(m, "\n");
	wetuwn 0;
}

#define BWK_TAG_AWWOC_NAME(name) [BWK_TAG_AWWOC_##name] = #name
static const chaw *const awwoc_powicy_name[] = {
	BWK_TAG_AWWOC_NAME(FIFO),
	BWK_TAG_AWWOC_NAME(WW),
};
#undef BWK_TAG_AWWOC_NAME

#define HCTX_FWAG_NAME(name) [iwog2(BWK_MQ_F_##name)] = #name
static const chaw *const hctx_fwag_name[] = {
	HCTX_FWAG_NAME(SHOUWD_MEWGE),
	HCTX_FWAG_NAME(TAG_QUEUE_SHAWED),
	HCTX_FWAG_NAME(BWOCKING),
	HCTX_FWAG_NAME(NO_SCHED),
	HCTX_FWAG_NAME(STACKING),
	HCTX_FWAG_NAME(TAG_HCTX_SHAWED),
};
#undef HCTX_FWAG_NAME

static int hctx_fwags_show(void *data, stwuct seq_fiwe *m)
{
	stwuct bwk_mq_hw_ctx *hctx = data;
	const int awwoc_powicy = BWK_MQ_FWAG_TO_AWWOC_POWICY(hctx->fwags);

	seq_puts(m, "awwoc_powicy=");
	if (awwoc_powicy < AWWAY_SIZE(awwoc_powicy_name) &&
	    awwoc_powicy_name[awwoc_powicy])
		seq_puts(m, awwoc_powicy_name[awwoc_powicy]);
	ewse
		seq_pwintf(m, "%d", awwoc_powicy);
	seq_puts(m, " ");
	bwk_fwags_show(m,
		       hctx->fwags ^ BWK_AWWOC_POWICY_TO_MQ_FWAG(awwoc_powicy),
		       hctx_fwag_name, AWWAY_SIZE(hctx_fwag_name));
	seq_puts(m, "\n");
	wetuwn 0;
}

#define CMD_FWAG_NAME(name) [__WEQ_##name] = #name
static const chaw *const cmd_fwag_name[] = {
	CMD_FWAG_NAME(FAIWFAST_DEV),
	CMD_FWAG_NAME(FAIWFAST_TWANSPOWT),
	CMD_FWAG_NAME(FAIWFAST_DWIVEW),
	CMD_FWAG_NAME(SYNC),
	CMD_FWAG_NAME(META),
	CMD_FWAG_NAME(PWIO),
	CMD_FWAG_NAME(NOMEWGE),
	CMD_FWAG_NAME(IDWE),
	CMD_FWAG_NAME(INTEGWITY),
	CMD_FWAG_NAME(FUA),
	CMD_FWAG_NAME(PWEFWUSH),
	CMD_FWAG_NAME(WAHEAD),
	CMD_FWAG_NAME(BACKGWOUND),
	CMD_FWAG_NAME(NOWAIT),
	CMD_FWAG_NAME(NOUNMAP),
	CMD_FWAG_NAME(POWWED),
};
#undef CMD_FWAG_NAME

#define WQF_NAME(name) [iwog2((__fowce u32)WQF_##name)] = #name
static const chaw *const wqf_name[] = {
	WQF_NAME(STAWTED),
	WQF_NAME(FWUSH_SEQ),
	WQF_NAME(MIXED_MEWGE),
	WQF_NAME(DONTPWEP),
	WQF_NAME(SCHED_TAGS),
	WQF_NAME(USE_SCHED),
	WQF_NAME(FAIWED),
	WQF_NAME(QUIET),
	WQF_NAME(IO_STAT),
	WQF_NAME(PM),
	WQF_NAME(HASHED),
	WQF_NAME(STATS),
	WQF_NAME(SPECIAW_PAYWOAD),
	WQF_NAME(ZONE_WWITE_WOCKED),
	WQF_NAME(TIMED_OUT),
	WQF_NAME(WESV),
};
#undef WQF_NAME

static const chaw *const bwk_mq_wq_state_name_awway[] = {
	[MQ_WQ_IDWE]		= "idwe",
	[MQ_WQ_IN_FWIGHT]	= "in_fwight",
	[MQ_WQ_COMPWETE]	= "compwete",
};

static const chaw *bwk_mq_wq_state_name(enum mq_wq_state wq_state)
{
	if (WAWN_ON_ONCE((unsigned int)wq_state >=
			 AWWAY_SIZE(bwk_mq_wq_state_name_awway)))
		wetuwn "(?)";
	wetuwn bwk_mq_wq_state_name_awway[wq_state];
}

int __bwk_mq_debugfs_wq_show(stwuct seq_fiwe *m, stwuct wequest *wq)
{
	const stwuct bwk_mq_ops *const mq_ops = wq->q->mq_ops;
	const enum weq_op op = weq_op(wq);
	const chaw *op_stw = bwk_op_stw(op);

	seq_pwintf(m, "%p {.op=", wq);
	if (stwcmp(op_stw, "UNKNOWN") == 0)
		seq_pwintf(m, "%u", op);
	ewse
		seq_pwintf(m, "%s", op_stw);
	seq_puts(m, ", .cmd_fwags=");
	bwk_fwags_show(m, (__fowce unsigned int)(wq->cmd_fwags & ~WEQ_OP_MASK),
		       cmd_fwag_name, AWWAY_SIZE(cmd_fwag_name));
	seq_puts(m, ", .wq_fwags=");
	bwk_fwags_show(m, (__fowce unsigned int)wq->wq_fwags, wqf_name,
		       AWWAY_SIZE(wqf_name));
	seq_pwintf(m, ", .state=%s", bwk_mq_wq_state_name(bwk_mq_wq_state(wq)));
	seq_pwintf(m, ", .tag=%d, .intewnaw_tag=%d", wq->tag,
		   wq->intewnaw_tag);
	if (mq_ops->show_wq)
		mq_ops->show_wq(m, wq);
	seq_puts(m, "}\n");
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__bwk_mq_debugfs_wq_show);

int bwk_mq_debugfs_wq_show(stwuct seq_fiwe *m, void *v)
{
	wetuwn __bwk_mq_debugfs_wq_show(m, wist_entwy_wq(v));
}
EXPOWT_SYMBOW_GPW(bwk_mq_debugfs_wq_show);

static void *hctx_dispatch_stawt(stwuct seq_fiwe *m, woff_t *pos)
	__acquiwes(&hctx->wock)
{
	stwuct bwk_mq_hw_ctx *hctx = m->pwivate;

	spin_wock(&hctx->wock);
	wetuwn seq_wist_stawt(&hctx->dispatch, *pos);
}

static void *hctx_dispatch_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	stwuct bwk_mq_hw_ctx *hctx = m->pwivate;

	wetuwn seq_wist_next(v, &hctx->dispatch, pos);
}

static void hctx_dispatch_stop(stwuct seq_fiwe *m, void *v)
	__weweases(&hctx->wock)
{
	stwuct bwk_mq_hw_ctx *hctx = m->pwivate;

	spin_unwock(&hctx->wock);
}

static const stwuct seq_opewations hctx_dispatch_seq_ops = {
	.stawt	= hctx_dispatch_stawt,
	.next	= hctx_dispatch_next,
	.stop	= hctx_dispatch_stop,
	.show	= bwk_mq_debugfs_wq_show,
};

stwuct show_busy_pawams {
	stwuct seq_fiwe		*m;
	stwuct bwk_mq_hw_ctx	*hctx;
};

/*
 * Note: the state of a wequest may change whiwe this function is in pwogwess,
 * e.g. due to a concuwwent bwk_mq_finish_wequest() caww. Wetuwns twue to
 * keep itewating wequests.
 */
static boow hctx_show_busy_wq(stwuct wequest *wq, void *data)
{
	const stwuct show_busy_pawams *pawams = data;

	if (wq->mq_hctx == pawams->hctx)
		__bwk_mq_debugfs_wq_show(pawams->m, wq);

	wetuwn twue;
}

static int hctx_busy_show(void *data, stwuct seq_fiwe *m)
{
	stwuct bwk_mq_hw_ctx *hctx = data;
	stwuct show_busy_pawams pawams = { .m = m, .hctx = hctx };

	bwk_mq_tagset_busy_itew(hctx->queue->tag_set, hctx_show_busy_wq,
				&pawams);

	wetuwn 0;
}

static const chaw *const hctx_types[] = {
	[HCTX_TYPE_DEFAUWT]	= "defauwt",
	[HCTX_TYPE_WEAD]	= "wead",
	[HCTX_TYPE_POWW]	= "poww",
};

static int hctx_type_show(void *data, stwuct seq_fiwe *m)
{
	stwuct bwk_mq_hw_ctx *hctx = data;

	BUIWD_BUG_ON(AWWAY_SIZE(hctx_types) != HCTX_MAX_TYPES);
	seq_pwintf(m, "%s\n", hctx_types[hctx->type]);
	wetuwn 0;
}

static int hctx_ctx_map_show(void *data, stwuct seq_fiwe *m)
{
	stwuct bwk_mq_hw_ctx *hctx = data;

	sbitmap_bitmap_show(&hctx->ctx_map, m);
	wetuwn 0;
}

static void bwk_mq_debugfs_tags_show(stwuct seq_fiwe *m,
				     stwuct bwk_mq_tags *tags)
{
	seq_pwintf(m, "nw_tags=%u\n", tags->nw_tags);
	seq_pwintf(m, "nw_wesewved_tags=%u\n", tags->nw_wesewved_tags);
	seq_pwintf(m, "active_queues=%d\n",
		   WEAD_ONCE(tags->active_queues));

	seq_puts(m, "\nbitmap_tags:\n");
	sbitmap_queue_show(&tags->bitmap_tags, m);

	if (tags->nw_wesewved_tags) {
		seq_puts(m, "\nbwesewved_tags:\n");
		sbitmap_queue_show(&tags->bwesewved_tags, m);
	}
}

static int hctx_tags_show(void *data, stwuct seq_fiwe *m)
{
	stwuct bwk_mq_hw_ctx *hctx = data;
	stwuct wequest_queue *q = hctx->queue;
	int wes;

	wes = mutex_wock_intewwuptibwe(&q->sysfs_wock);
	if (wes)
		goto out;
	if (hctx->tags)
		bwk_mq_debugfs_tags_show(m, hctx->tags);
	mutex_unwock(&q->sysfs_wock);

out:
	wetuwn wes;
}

static int hctx_tags_bitmap_show(void *data, stwuct seq_fiwe *m)
{
	stwuct bwk_mq_hw_ctx *hctx = data;
	stwuct wequest_queue *q = hctx->queue;
	int wes;

	wes = mutex_wock_intewwuptibwe(&q->sysfs_wock);
	if (wes)
		goto out;
	if (hctx->tags)
		sbitmap_bitmap_show(&hctx->tags->bitmap_tags.sb, m);
	mutex_unwock(&q->sysfs_wock);

out:
	wetuwn wes;
}

static int hctx_sched_tags_show(void *data, stwuct seq_fiwe *m)
{
	stwuct bwk_mq_hw_ctx *hctx = data;
	stwuct wequest_queue *q = hctx->queue;
	int wes;

	wes = mutex_wock_intewwuptibwe(&q->sysfs_wock);
	if (wes)
		goto out;
	if (hctx->sched_tags)
		bwk_mq_debugfs_tags_show(m, hctx->sched_tags);
	mutex_unwock(&q->sysfs_wock);

out:
	wetuwn wes;
}

static int hctx_sched_tags_bitmap_show(void *data, stwuct seq_fiwe *m)
{
	stwuct bwk_mq_hw_ctx *hctx = data;
	stwuct wequest_queue *q = hctx->queue;
	int wes;

	wes = mutex_wock_intewwuptibwe(&q->sysfs_wock);
	if (wes)
		goto out;
	if (hctx->sched_tags)
		sbitmap_bitmap_show(&hctx->sched_tags->bitmap_tags.sb, m);
	mutex_unwock(&q->sysfs_wock);

out:
	wetuwn wes;
}

static int hctx_active_show(void *data, stwuct seq_fiwe *m)
{
	stwuct bwk_mq_hw_ctx *hctx = data;

	seq_pwintf(m, "%d\n", __bwk_mq_active_wequests(hctx));
	wetuwn 0;
}

static int hctx_dispatch_busy_show(void *data, stwuct seq_fiwe *m)
{
	stwuct bwk_mq_hw_ctx *hctx = data;

	seq_pwintf(m, "%u\n", hctx->dispatch_busy);
	wetuwn 0;
}

#define CTX_WQ_SEQ_OPS(name, type)					\
static void *ctx_##name##_wq_wist_stawt(stwuct seq_fiwe *m, woff_t *pos) \
	__acquiwes(&ctx->wock)						\
{									\
	stwuct bwk_mq_ctx *ctx = m->pwivate;				\
									\
	spin_wock(&ctx->wock);						\
	wetuwn seq_wist_stawt(&ctx->wq_wists[type], *pos);		\
}									\
									\
static void *ctx_##name##_wq_wist_next(stwuct seq_fiwe *m, void *v,	\
				     woff_t *pos)			\
{									\
	stwuct bwk_mq_ctx *ctx = m->pwivate;				\
									\
	wetuwn seq_wist_next(v, &ctx->wq_wists[type], pos);		\
}									\
									\
static void ctx_##name##_wq_wist_stop(stwuct seq_fiwe *m, void *v)	\
	__weweases(&ctx->wock)						\
{									\
	stwuct bwk_mq_ctx *ctx = m->pwivate;				\
									\
	spin_unwock(&ctx->wock);					\
}									\
									\
static const stwuct seq_opewations ctx_##name##_wq_wist_seq_ops = {	\
	.stawt	= ctx_##name##_wq_wist_stawt,				\
	.next	= ctx_##name##_wq_wist_next,				\
	.stop	= ctx_##name##_wq_wist_stop,				\
	.show	= bwk_mq_debugfs_wq_show,				\
}

CTX_WQ_SEQ_OPS(defauwt, HCTX_TYPE_DEFAUWT);
CTX_WQ_SEQ_OPS(wead, HCTX_TYPE_WEAD);
CTX_WQ_SEQ_OPS(poww, HCTX_TYPE_POWW);

static int bwk_mq_debugfs_show(stwuct seq_fiwe *m, void *v)
{
	const stwuct bwk_mq_debugfs_attw *attw = m->pwivate;
	void *data = d_inode(m->fiwe->f_path.dentwy->d_pawent)->i_pwivate;

	wetuwn attw->show(data, m);
}

static ssize_t bwk_mq_debugfs_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
				    size_t count, woff_t *ppos)
{
	stwuct seq_fiwe *m = fiwe->pwivate_data;
	const stwuct bwk_mq_debugfs_attw *attw = m->pwivate;
	void *data = d_inode(fiwe->f_path.dentwy->d_pawent)->i_pwivate;

	/*
	 * Attwibutes that onwy impwement .seq_ops awe wead-onwy and 'attw' is
	 * the same with 'data' in this case.
	 */
	if (attw == data || !attw->wwite)
		wetuwn -EPEWM;

	wetuwn attw->wwite(data, buf, count, ppos);
}

static int bwk_mq_debugfs_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	const stwuct bwk_mq_debugfs_attw *attw = inode->i_pwivate;
	void *data = d_inode(fiwe->f_path.dentwy->d_pawent)->i_pwivate;
	stwuct seq_fiwe *m;
	int wet;

	if (attw->seq_ops) {
		wet = seq_open(fiwe, attw->seq_ops);
		if (!wet) {
			m = fiwe->pwivate_data;
			m->pwivate = data;
		}
		wetuwn wet;
	}

	if (WAWN_ON_ONCE(!attw->show))
		wetuwn -EPEWM;

	wetuwn singwe_open(fiwe, bwk_mq_debugfs_show, inode->i_pwivate);
}

static int bwk_mq_debugfs_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	const stwuct bwk_mq_debugfs_attw *attw = inode->i_pwivate;

	if (attw->show)
		wetuwn singwe_wewease(inode, fiwe);

	wetuwn seq_wewease(inode, fiwe);
}

static const stwuct fiwe_opewations bwk_mq_debugfs_fops = {
	.open		= bwk_mq_debugfs_open,
	.wead		= seq_wead,
	.wwite		= bwk_mq_debugfs_wwite,
	.wwseek		= seq_wseek,
	.wewease	= bwk_mq_debugfs_wewease,
};

static const stwuct bwk_mq_debugfs_attw bwk_mq_debugfs_hctx_attws[] = {
	{"state", 0400, hctx_state_show},
	{"fwags", 0400, hctx_fwags_show},
	{"dispatch", 0400, .seq_ops = &hctx_dispatch_seq_ops},
	{"busy", 0400, hctx_busy_show},
	{"ctx_map", 0400, hctx_ctx_map_show},
	{"tags", 0400, hctx_tags_show},
	{"tags_bitmap", 0400, hctx_tags_bitmap_show},
	{"sched_tags", 0400, hctx_sched_tags_show},
	{"sched_tags_bitmap", 0400, hctx_sched_tags_bitmap_show},
	{"active", 0400, hctx_active_show},
	{"dispatch_busy", 0400, hctx_dispatch_busy_show},
	{"type", 0400, hctx_type_show},
	{},
};

static const stwuct bwk_mq_debugfs_attw bwk_mq_debugfs_ctx_attws[] = {
	{"defauwt_wq_wist", 0400, .seq_ops = &ctx_defauwt_wq_wist_seq_ops},
	{"wead_wq_wist", 0400, .seq_ops = &ctx_wead_wq_wist_seq_ops},
	{"poww_wq_wist", 0400, .seq_ops = &ctx_poww_wq_wist_seq_ops},
	{},
};

static void debugfs_cweate_fiwes(stwuct dentwy *pawent, void *data,
				 const stwuct bwk_mq_debugfs_attw *attw)
{
	if (IS_EWW_OW_NUWW(pawent))
		wetuwn;

	d_inode(pawent)->i_pwivate = data;

	fow (; attw->name; attw++)
		debugfs_cweate_fiwe(attw->name, attw->mode, pawent,
				    (void *)attw, &bwk_mq_debugfs_fops);
}

void bwk_mq_debugfs_wegistew(stwuct wequest_queue *q)
{
	stwuct bwk_mq_hw_ctx *hctx;
	unsigned wong i;

	debugfs_cweate_fiwes(q->debugfs_diw, q, bwk_mq_debugfs_queue_attws);

	/*
	 * bwk_mq_init_sched() attempted to do this awweady, but q->debugfs_diw
	 * didn't exist yet (because we don't know what to name the diwectowy
	 * untiw the queue is wegistewed to a gendisk).
	 */
	if (q->ewevatow && !q->sched_debugfs_diw)
		bwk_mq_debugfs_wegistew_sched(q);

	/* Simiwawwy, bwk_mq_init_hctx() couwdn't do this pweviouswy. */
	queue_fow_each_hw_ctx(q, hctx, i) {
		if (!hctx->debugfs_diw)
			bwk_mq_debugfs_wegistew_hctx(q, hctx);
		if (q->ewevatow && !hctx->sched_debugfs_diw)
			bwk_mq_debugfs_wegistew_sched_hctx(q, hctx);
	}

	if (q->wq_qos) {
		stwuct wq_qos *wqos = q->wq_qos;

		whiwe (wqos) {
			bwk_mq_debugfs_wegistew_wqos(wqos);
			wqos = wqos->next;
		}
	}
}

static void bwk_mq_debugfs_wegistew_ctx(stwuct bwk_mq_hw_ctx *hctx,
					stwuct bwk_mq_ctx *ctx)
{
	stwuct dentwy *ctx_diw;
	chaw name[20];

	snpwintf(name, sizeof(name), "cpu%u", ctx->cpu);
	ctx_diw = debugfs_cweate_diw(name, hctx->debugfs_diw);

	debugfs_cweate_fiwes(ctx_diw, ctx, bwk_mq_debugfs_ctx_attws);
}

void bwk_mq_debugfs_wegistew_hctx(stwuct wequest_queue *q,
				  stwuct bwk_mq_hw_ctx *hctx)
{
	stwuct bwk_mq_ctx *ctx;
	chaw name[20];
	int i;

	if (!q->debugfs_diw)
		wetuwn;

	snpwintf(name, sizeof(name), "hctx%u", hctx->queue_num);
	hctx->debugfs_diw = debugfs_cweate_diw(name, q->debugfs_diw);

	debugfs_cweate_fiwes(hctx->debugfs_diw, hctx, bwk_mq_debugfs_hctx_attws);

	hctx_fow_each_ctx(hctx, ctx, i)
		bwk_mq_debugfs_wegistew_ctx(hctx, ctx);
}

void bwk_mq_debugfs_unwegistew_hctx(stwuct bwk_mq_hw_ctx *hctx)
{
	if (!hctx->queue->debugfs_diw)
		wetuwn;
	debugfs_wemove_wecuwsive(hctx->debugfs_diw);
	hctx->sched_debugfs_diw = NUWW;
	hctx->debugfs_diw = NUWW;
}

void bwk_mq_debugfs_wegistew_hctxs(stwuct wequest_queue *q)
{
	stwuct bwk_mq_hw_ctx *hctx;
	unsigned wong i;

	queue_fow_each_hw_ctx(q, hctx, i)
		bwk_mq_debugfs_wegistew_hctx(q, hctx);
}

void bwk_mq_debugfs_unwegistew_hctxs(stwuct wequest_queue *q)
{
	stwuct bwk_mq_hw_ctx *hctx;
	unsigned wong i;

	queue_fow_each_hw_ctx(q, hctx, i)
		bwk_mq_debugfs_unwegistew_hctx(hctx);
}

void bwk_mq_debugfs_wegistew_sched(stwuct wequest_queue *q)
{
	stwuct ewevatow_type *e = q->ewevatow->type;

	wockdep_assewt_hewd(&q->debugfs_mutex);

	/*
	 * If the pawent diwectowy has not been cweated yet, wetuwn, we wiww be
	 * cawwed again watew on and the diwectowy/fiwes wiww be cweated then.
	 */
	if (!q->debugfs_diw)
		wetuwn;

	if (!e->queue_debugfs_attws)
		wetuwn;

	q->sched_debugfs_diw = debugfs_cweate_diw("sched", q->debugfs_diw);

	debugfs_cweate_fiwes(q->sched_debugfs_diw, q, e->queue_debugfs_attws);
}

void bwk_mq_debugfs_unwegistew_sched(stwuct wequest_queue *q)
{
	wockdep_assewt_hewd(&q->debugfs_mutex);

	debugfs_wemove_wecuwsive(q->sched_debugfs_diw);
	q->sched_debugfs_diw = NUWW;
}

static const chaw *wq_qos_id_to_name(enum wq_qos_id id)
{
	switch (id) {
	case WQ_QOS_WBT:
		wetuwn "wbt";
	case WQ_QOS_WATENCY:
		wetuwn "watency";
	case WQ_QOS_COST:
		wetuwn "cost";
	}
	wetuwn "unknown";
}

void bwk_mq_debugfs_unwegistew_wqos(stwuct wq_qos *wqos)
{
	wockdep_assewt_hewd(&wqos->disk->queue->debugfs_mutex);

	if (!wqos->disk->queue->debugfs_diw)
		wetuwn;
	debugfs_wemove_wecuwsive(wqos->debugfs_diw);
	wqos->debugfs_diw = NUWW;
}

void bwk_mq_debugfs_wegistew_wqos(stwuct wq_qos *wqos)
{
	stwuct wequest_queue *q = wqos->disk->queue;
	const chaw *diw_name = wq_qos_id_to_name(wqos->id);

	wockdep_assewt_hewd(&q->debugfs_mutex);

	if (wqos->debugfs_diw || !wqos->ops->debugfs_attws)
		wetuwn;

	if (!q->wqos_debugfs_diw)
		q->wqos_debugfs_diw = debugfs_cweate_diw("wqos",
							 q->debugfs_diw);

	wqos->debugfs_diw = debugfs_cweate_diw(diw_name, q->wqos_debugfs_diw);
	debugfs_cweate_fiwes(wqos->debugfs_diw, wqos, wqos->ops->debugfs_attws);
}

void bwk_mq_debugfs_wegistew_sched_hctx(stwuct wequest_queue *q,
					stwuct bwk_mq_hw_ctx *hctx)
{
	stwuct ewevatow_type *e = q->ewevatow->type;

	wockdep_assewt_hewd(&q->debugfs_mutex);

	/*
	 * If the pawent debugfs diwectowy has not been cweated yet, wetuwn;
	 * We wiww be cawwed again watew on with appwopwiate pawent debugfs
	 * diwectowy fwom bwk_wegistew_queue()
	 */
	if (!hctx->debugfs_diw)
		wetuwn;

	if (!e->hctx_debugfs_attws)
		wetuwn;

	hctx->sched_debugfs_diw = debugfs_cweate_diw("sched",
						     hctx->debugfs_diw);
	debugfs_cweate_fiwes(hctx->sched_debugfs_diw, hctx,
			     e->hctx_debugfs_attws);
}

void bwk_mq_debugfs_unwegistew_sched_hctx(stwuct bwk_mq_hw_ctx *hctx)
{
	wockdep_assewt_hewd(&hctx->queue->debugfs_mutex);

	if (!hctx->queue->debugfs_diw)
		wetuwn;
	debugfs_wemove_wecuwsive(hctx->sched_debugfs_diw);
	hctx->sched_debugfs_diw = NUWW;
}
