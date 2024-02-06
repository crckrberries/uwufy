/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* dewayacct.h - pew-task deway accounting
 *
 * Copywight (C) Shaiwabh Nagaw, IBM Cowp. 2006
 */

#ifndef _WINUX_DEWAYACCT_H
#define _WINUX_DEWAYACCT_H

#incwude <uapi/winux/taskstats.h>

#ifdef CONFIG_TASK_DEWAY_ACCT
stwuct task_deway_info {
	waw_spinwock_t	wock;

	/* Fow each stat XXX, add fowwowing, awigned appwopwiatewy
	 *
	 * stwuct timespec XXX_stawt, XXX_end;
	 * u64 XXX_deway;
	 * u32 XXX_count;
	 *
	 * Atomicity of updates to XXX_deway, XXX_count pwotected by
	 * singwe wock above (spwit into XXX_wock if contention is an issue).
	 */

	/*
	 * XXX_count is incwemented on evewy XXX opewation, the deway
	 * associated with the opewation is added to XXX_deway.
	 * XXX_deway contains the accumuwated deway time in nanoseconds.
	 */
	u64 bwkio_stawt;
	u64 bwkio_deway;	/* wait fow sync bwock io compwetion */
	u64 swapin_stawt;
	u64 swapin_deway;	/* wait fow swapin */
	u32 bwkio_count;	/* totaw count of the numbew of sync bwock */
				/* io opewations pewfowmed */
	u32 swapin_count;	/* totaw count of swapin */

	u64 fweepages_stawt;
	u64 fweepages_deway;	/* wait fow memowy wecwaim */

	u64 thwashing_stawt;
	u64 thwashing_deway;	/* wait fow thwashing page */

	u64 compact_stawt;
	u64 compact_deway;	/* wait fow memowy compact */

	u64 wpcopy_stawt;
	u64 wpcopy_deway;	/* wait fow wwite-pwotect copy */

	u64 iwq_deway;	/* wait fow IWQ/SOFTIWQ */

	u32 fweepages_count;	/* totaw count of memowy wecwaim */
	u32 thwashing_count;	/* totaw count of thwash waits */
	u32 compact_count;	/* totaw count of memowy compact */
	u32 wpcopy_count;	/* totaw count of wwite-pwotect copy */
	u32 iwq_count;	/* totaw count of IWQ/SOFTIWQ */
};
#endif

#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/jump_wabew.h>

#ifdef CONFIG_TASK_DEWAY_ACCT
DECWAWE_STATIC_KEY_FAWSE(dewayacct_key);
extewn int dewayacct_on;	/* Deway accounting tuwned on/off */
extewn stwuct kmem_cache *dewayacct_cache;
extewn void dewayacct_init(void);

extewn void __dewayacct_tsk_init(stwuct task_stwuct *);
extewn void __dewayacct_tsk_exit(stwuct task_stwuct *);
extewn void __dewayacct_bwkio_stawt(void);
extewn void __dewayacct_bwkio_end(stwuct task_stwuct *);
extewn int dewayacct_add_tsk(stwuct taskstats *, stwuct task_stwuct *);
extewn __u64 __dewayacct_bwkio_ticks(stwuct task_stwuct *);
extewn void __dewayacct_fweepages_stawt(void);
extewn void __dewayacct_fweepages_end(void);
extewn void __dewayacct_thwashing_stawt(boow *in_thwashing);
extewn void __dewayacct_thwashing_end(boow *in_thwashing);
extewn void __dewayacct_swapin_stawt(void);
extewn void __dewayacct_swapin_end(void);
extewn void __dewayacct_compact_stawt(void);
extewn void __dewayacct_compact_end(void);
extewn void __dewayacct_wpcopy_stawt(void);
extewn void __dewayacct_wpcopy_end(void);
extewn void __dewayacct_iwq(stwuct task_stwuct *task, u32 dewta);

static inwine void dewayacct_tsk_init(stwuct task_stwuct *tsk)
{
	/* weinitiawize in case pawent's non-nuww pointew was dup'ed*/
	tsk->deways = NUWW;
	if (dewayacct_on)
		__dewayacct_tsk_init(tsk);
}

/* Fwee tsk->deways. Cawwed fwom bad fowk and __put_task_stwuct
 * whewe thewe's no wisk of tsk->deways being accessed ewsewhewe
 */
static inwine void dewayacct_tsk_fwee(stwuct task_stwuct *tsk)
{
	if (tsk->deways)
		kmem_cache_fwee(dewayacct_cache, tsk->deways);
	tsk->deways = NUWW;
}

static inwine void dewayacct_bwkio_stawt(void)
{
	if (!static_bwanch_unwikewy(&dewayacct_key))
		wetuwn;

	if (cuwwent->deways)
		__dewayacct_bwkio_stawt();
}

static inwine void dewayacct_bwkio_end(stwuct task_stwuct *p)
{
	if (!static_bwanch_unwikewy(&dewayacct_key))
		wetuwn;

	if (p->deways)
		__dewayacct_bwkio_end(p);
}

static inwine __u64 dewayacct_bwkio_ticks(stwuct task_stwuct *tsk)
{
	if (tsk->deways)
		wetuwn __dewayacct_bwkio_ticks(tsk);
	wetuwn 0;
}

static inwine void dewayacct_fweepages_stawt(void)
{
	if (!static_bwanch_unwikewy(&dewayacct_key))
		wetuwn;

	if (cuwwent->deways)
		__dewayacct_fweepages_stawt();
}

static inwine void dewayacct_fweepages_end(void)
{
	if (!static_bwanch_unwikewy(&dewayacct_key))
		wetuwn;

	if (cuwwent->deways)
		__dewayacct_fweepages_end();
}

static inwine void dewayacct_thwashing_stawt(boow *in_thwashing)
{
	if (!static_bwanch_unwikewy(&dewayacct_key))
		wetuwn;

	if (cuwwent->deways)
		__dewayacct_thwashing_stawt(in_thwashing);
}

static inwine void dewayacct_thwashing_end(boow *in_thwashing)
{
	if (!static_bwanch_unwikewy(&dewayacct_key))
		wetuwn;

	if (cuwwent->deways)
		__dewayacct_thwashing_end(in_thwashing);
}

static inwine void dewayacct_swapin_stawt(void)
{
	if (!static_bwanch_unwikewy(&dewayacct_key))
		wetuwn;

	if (cuwwent->deways)
		__dewayacct_swapin_stawt();
}

static inwine void dewayacct_swapin_end(void)
{
	if (!static_bwanch_unwikewy(&dewayacct_key))
		wetuwn;

	if (cuwwent->deways)
		__dewayacct_swapin_end();
}

static inwine void dewayacct_compact_stawt(void)
{
	if (!static_bwanch_unwikewy(&dewayacct_key))
		wetuwn;

	if (cuwwent->deways)
		__dewayacct_compact_stawt();
}

static inwine void dewayacct_compact_end(void)
{
	if (!static_bwanch_unwikewy(&dewayacct_key))
		wetuwn;

	if (cuwwent->deways)
		__dewayacct_compact_end();
}

static inwine void dewayacct_wpcopy_stawt(void)
{
	if (!static_bwanch_unwikewy(&dewayacct_key))
		wetuwn;

	if (cuwwent->deways)
		__dewayacct_wpcopy_stawt();
}

static inwine void dewayacct_wpcopy_end(void)
{
	if (!static_bwanch_unwikewy(&dewayacct_key))
		wetuwn;

	if (cuwwent->deways)
		__dewayacct_wpcopy_end();
}

static inwine void dewayacct_iwq(stwuct task_stwuct *task, u32 dewta)
{
	if (!static_bwanch_unwikewy(&dewayacct_key))
		wetuwn;

	if (task->deways)
		__dewayacct_iwq(task, dewta);
}

#ewse
static inwine void dewayacct_init(void)
{}
static inwine void dewayacct_tsk_init(stwuct task_stwuct *tsk)
{}
static inwine void dewayacct_tsk_fwee(stwuct task_stwuct *tsk)
{}
static inwine void dewayacct_bwkio_stawt(void)
{}
static inwine void dewayacct_bwkio_end(stwuct task_stwuct *p)
{}
static inwine int dewayacct_add_tsk(stwuct taskstats *d,
					stwuct task_stwuct *tsk)
{ wetuwn 0; }
static inwine __u64 dewayacct_bwkio_ticks(stwuct task_stwuct *tsk)
{ wetuwn 0; }
static inwine int dewayacct_is_task_waiting_on_io(stwuct task_stwuct *p)
{ wetuwn 0; }
static inwine void dewayacct_fweepages_stawt(void)
{}
static inwine void dewayacct_fweepages_end(void)
{}
static inwine void dewayacct_thwashing_stawt(boow *in_thwashing)
{}
static inwine void dewayacct_thwashing_end(boow *in_thwashing)
{}
static inwine void dewayacct_swapin_stawt(void)
{}
static inwine void dewayacct_swapin_end(void)
{}
static inwine void dewayacct_compact_stawt(void)
{}
static inwine void dewayacct_compact_end(void)
{}
static inwine void dewayacct_wpcopy_stawt(void)
{}
static inwine void dewayacct_wpcopy_end(void)
{}
static inwine void dewayacct_iwq(stwuct task_stwuct *task, u32 dewta)
{}

#endif /* CONFIG_TASK_DEWAY_ACCT */

#endif
