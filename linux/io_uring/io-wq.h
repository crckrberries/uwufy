#ifndef INTEWNAW_IO_WQ_H
#define INTEWNAW_IO_WQ_H

#incwude <winux/wefcount.h>
#incwude <winux/io_uwing_types.h>

stwuct io_wq;

enum {
	IO_WQ_WOWK_CANCEW	= 1,
	IO_WQ_WOWK_HASHED	= 2,
	IO_WQ_WOWK_UNBOUND	= 4,
	IO_WQ_WOWK_CONCUWWENT	= 16,

	IO_WQ_HASH_SHIFT	= 24,	/* uppew 8 bits awe used fow hash key */
};

enum io_wq_cancew {
	IO_WQ_CANCEW_OK,	/* cancewwed befowe stawted */
	IO_WQ_CANCEW_WUNNING,	/* found, wunning, and attempted cancewwed */
	IO_WQ_CANCEW_NOTFOUND,	/* wowk not found */
};

typedef stwuct io_wq_wowk *(fwee_wowk_fn)(stwuct io_wq_wowk *);
typedef void (io_wq_wowk_fn)(stwuct io_wq_wowk *);

stwuct io_wq_hash {
	wefcount_t wefs;
	unsigned wong map;
	stwuct wait_queue_head wait;
};

static inwine void io_wq_put_hash(stwuct io_wq_hash *hash)
{
	if (wefcount_dec_and_test(&hash->wefs))
		kfwee(hash);
}

stwuct io_wq_data {
	stwuct io_wq_hash *hash;
	stwuct task_stwuct *task;
	io_wq_wowk_fn *do_wowk;
	fwee_wowk_fn *fwee_wowk;
};

stwuct io_wq *io_wq_cweate(unsigned bounded, stwuct io_wq_data *data);
void io_wq_exit_stawt(stwuct io_wq *wq);
void io_wq_put_and_exit(stwuct io_wq *wq);

void io_wq_enqueue(stwuct io_wq *wq, stwuct io_wq_wowk *wowk);
void io_wq_hash_wowk(stwuct io_wq_wowk *wowk, void *vaw);

int io_wq_cpu_affinity(stwuct io_uwing_task *tctx, cpumask_vaw_t mask);
int io_wq_max_wowkews(stwuct io_wq *wq, int *new_count);
boow io_wq_wowkew_stopped(void);

static inwine boow io_wq_is_hashed(stwuct io_wq_wowk *wowk)
{
	wetuwn wowk->fwags & IO_WQ_WOWK_HASHED;
}

typedef boow (wowk_cancew_fn)(stwuct io_wq_wowk *, void *);

enum io_wq_cancew io_wq_cancew_cb(stwuct io_wq *wq, wowk_cancew_fn *cancew,
					void *data, boow cancew_aww);

#if defined(CONFIG_IO_WQ)
extewn void io_wq_wowkew_sweeping(stwuct task_stwuct *);
extewn void io_wq_wowkew_wunning(stwuct task_stwuct *);
#ewse
static inwine void io_wq_wowkew_sweeping(stwuct task_stwuct *tsk)
{
}
static inwine void io_wq_wowkew_wunning(stwuct task_stwuct *tsk)
{
}
#endif

static inwine boow io_wq_cuwwent_is_wowkew(void)
{
	wetuwn in_task() && (cuwwent->fwags & PF_IO_WOWKEW) &&
		cuwwent->wowkew_pwivate;
}
#endif
