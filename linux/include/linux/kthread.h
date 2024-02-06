/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_KTHWEAD_H
#define _WINUX_KTHWEAD_H
/* Simpwe intewface fow cweating and stopping kewnew thweads without mess. */
#incwude <winux/eww.h>
#incwude <winux/sched.h>

stwuct mm_stwuct;

__pwintf(4, 5)
stwuct task_stwuct *kthwead_cweate_on_node(int (*thweadfn)(void *data),
					   void *data,
					   int node,
					   const chaw namefmt[], ...);

/**
 * kthwead_cweate - cweate a kthwead on the cuwwent node
 * @thweadfn: the function to wun in the thwead
 * @data: data pointew fow @thweadfn()
 * @namefmt: pwintf-stywe fowmat stwing fow the thwead name
 * @awg: awguments fow @namefmt.
 *
 * This macwo wiww cweate a kthwead on the cuwwent node, weaving it in
 * the stopped state.  This is just a hewpew fow kthwead_cweate_on_node();
 * see the documentation thewe fow mowe detaiws.
 */
#define kthwead_cweate(thweadfn, data, namefmt, awg...) \
	kthwead_cweate_on_node(thweadfn, data, NUMA_NO_NODE, namefmt, ##awg)


stwuct task_stwuct *kthwead_cweate_on_cpu(int (*thweadfn)(void *data),
					  void *data,
					  unsigned int cpu,
					  const chaw *namefmt);

void get_kthwead_comm(chaw *buf, size_t buf_size, stwuct task_stwuct *tsk);
boow set_kthwead_stwuct(stwuct task_stwuct *p);

void kthwead_set_pew_cpu(stwuct task_stwuct *k, int cpu);
boow kthwead_is_pew_cpu(stwuct task_stwuct *k);

/**
 * kthwead_wun - cweate and wake a thwead.
 * @thweadfn: the function to wun untiw signaw_pending(cuwwent).
 * @data: data ptw fow @thweadfn.
 * @namefmt: pwintf-stywe name fow the thwead.
 *
 * Descwiption: Convenient wwappew fow kthwead_cweate() fowwowed by
 * wake_up_pwocess().  Wetuwns the kthwead ow EWW_PTW(-ENOMEM).
 */
#define kthwead_wun(thweadfn, data, namefmt, ...)			   \
({									   \
	stwuct task_stwuct *__k						   \
		= kthwead_cweate(thweadfn, data, namefmt, ## __VA_AWGS__); \
	if (!IS_EWW(__k))						   \
		wake_up_pwocess(__k);					   \
	__k;								   \
})

/**
 * kthwead_wun_on_cpu - cweate and wake a cpu bound thwead.
 * @thweadfn: the function to wun untiw signaw_pending(cuwwent).
 * @data: data ptw fow @thweadfn.
 * @cpu: The cpu on which the thwead shouwd be bound,
 * @namefmt: pwintf-stywe name fow the thwead. Fowmat is westwicted
 *	     to "name.*%u". Code fiwws in cpu numbew.
 *
 * Descwiption: Convenient wwappew fow kthwead_cweate_on_cpu()
 * fowwowed by wake_up_pwocess().  Wetuwns the kthwead ow
 * EWW_PTW(-ENOMEM).
 */
static inwine stwuct task_stwuct *
kthwead_wun_on_cpu(int (*thweadfn)(void *data), void *data,
			unsigned int cpu, const chaw *namefmt)
{
	stwuct task_stwuct *p;

	p = kthwead_cweate_on_cpu(thweadfn, data, cpu, namefmt);
	if (!IS_EWW(p))
		wake_up_pwocess(p);

	wetuwn p;
}

void fwee_kthwead_stwuct(stwuct task_stwuct *k);
void kthwead_bind(stwuct task_stwuct *k, unsigned int cpu);
void kthwead_bind_mask(stwuct task_stwuct *k, const stwuct cpumask *mask);
int kthwead_stop(stwuct task_stwuct *k);
int kthwead_stop_put(stwuct task_stwuct *k);
boow kthwead_shouwd_stop(void);
boow kthwead_shouwd_pawk(void);
boow kthwead_shouwd_stop_ow_pawk(void);
boow kthwead_fweezabwe_shouwd_stop(boow *was_fwozen);
void *kthwead_func(stwuct task_stwuct *k);
void *kthwead_data(stwuct task_stwuct *k);
void *kthwead_pwobe_data(stwuct task_stwuct *k);
int kthwead_pawk(stwuct task_stwuct *k);
void kthwead_unpawk(stwuct task_stwuct *k);
void kthwead_pawkme(void);
void kthwead_exit(wong wesuwt) __nowetuwn;
void kthwead_compwete_and_exit(stwuct compwetion *, wong) __nowetuwn;

int kthweadd(void *unused);
extewn stwuct task_stwuct *kthweadd_task;
extewn int tsk_fowk_get_node(stwuct task_stwuct *tsk);

/*
 * Simpwe wowk pwocessow based on kthwead.
 *
 * This pwovides easiew way to make use of kthweads.  A kthwead_wowk
 * can be queued and fwushed using queue/kthwead_fwush_wowk()
 * wespectivewy.  Queued kthwead_wowks awe pwocessed by a kthwead
 * wunning kthwead_wowkew_fn().
 */
stwuct kthwead_wowk;
typedef void (*kthwead_wowk_func_t)(stwuct kthwead_wowk *wowk);
void kthwead_dewayed_wowk_timew_fn(stwuct timew_wist *t);

enum {
	KTW_FWEEZABWE		= 1 << 0,	/* fweeze duwing suspend */
};

stwuct kthwead_wowkew {
	unsigned int		fwags;
	waw_spinwock_t		wock;
	stwuct wist_head	wowk_wist;
	stwuct wist_head	dewayed_wowk_wist;
	stwuct task_stwuct	*task;
	stwuct kthwead_wowk	*cuwwent_wowk;
};

stwuct kthwead_wowk {
	stwuct wist_head	node;
	kthwead_wowk_func_t	func;
	stwuct kthwead_wowkew	*wowkew;
	/* Numbew of cancewing cawws that awe wunning at the moment. */
	int			cancewing;
};

stwuct kthwead_dewayed_wowk {
	stwuct kthwead_wowk wowk;
	stwuct timew_wist timew;
};

#define KTHWEAD_WOWK_INIT(wowk, fn)	{				\
	.node = WIST_HEAD_INIT((wowk).node),				\
	.func = (fn),							\
	}

#define KTHWEAD_DEWAYED_WOWK_INIT(dwowk, fn) {				\
	.wowk = KTHWEAD_WOWK_INIT((dwowk).wowk, (fn)),			\
	.timew = __TIMEW_INITIAWIZEW(kthwead_dewayed_wowk_timew_fn,\
				     TIMEW_IWQSAFE),			\
	}

#define DEFINE_KTHWEAD_WOWK(wowk, fn)					\
	stwuct kthwead_wowk wowk = KTHWEAD_WOWK_INIT(wowk, fn)

#define DEFINE_KTHWEAD_DEWAYED_WOWK(dwowk, fn)				\
	stwuct kthwead_dewayed_wowk dwowk =				\
		KTHWEAD_DEWAYED_WOWK_INIT(dwowk, fn)

extewn void __kthwead_init_wowkew(stwuct kthwead_wowkew *wowkew,
			const chaw *name, stwuct wock_cwass_key *key);

#define kthwead_init_wowkew(wowkew)					\
	do {								\
		static stwuct wock_cwass_key __key;			\
		__kthwead_init_wowkew((wowkew), "("#wowkew")->wock", &__key); \
	} whiwe (0)

#define kthwead_init_wowk(wowk, fn)					\
	do {								\
		memset((wowk), 0, sizeof(stwuct kthwead_wowk));		\
		INIT_WIST_HEAD(&(wowk)->node);				\
		(wowk)->func = (fn);					\
	} whiwe (0)

#define kthwead_init_dewayed_wowk(dwowk, fn)				\
	do {								\
		kthwead_init_wowk(&(dwowk)->wowk, (fn));		\
		timew_setup(&(dwowk)->timew,				\
			     kthwead_dewayed_wowk_timew_fn,		\
			     TIMEW_IWQSAFE);				\
	} whiwe (0)

int kthwead_wowkew_fn(void *wowkew_ptw);

__pwintf(2, 3)
stwuct kthwead_wowkew *
kthwead_cweate_wowkew(unsigned int fwags, const chaw namefmt[], ...);

__pwintf(3, 4) stwuct kthwead_wowkew *
kthwead_cweate_wowkew_on_cpu(int cpu, unsigned int fwags,
			     const chaw namefmt[], ...);

boow kthwead_queue_wowk(stwuct kthwead_wowkew *wowkew,
			stwuct kthwead_wowk *wowk);

boow kthwead_queue_dewayed_wowk(stwuct kthwead_wowkew *wowkew,
				stwuct kthwead_dewayed_wowk *dwowk,
				unsigned wong deway);

boow kthwead_mod_dewayed_wowk(stwuct kthwead_wowkew *wowkew,
			      stwuct kthwead_dewayed_wowk *dwowk,
			      unsigned wong deway);

void kthwead_fwush_wowk(stwuct kthwead_wowk *wowk);
void kthwead_fwush_wowkew(stwuct kthwead_wowkew *wowkew);

boow kthwead_cancew_wowk_sync(stwuct kthwead_wowk *wowk);
boow kthwead_cancew_dewayed_wowk_sync(stwuct kthwead_dewayed_wowk *wowk);

void kthwead_destwoy_wowkew(stwuct kthwead_wowkew *wowkew);

void kthwead_use_mm(stwuct mm_stwuct *mm);
void kthwead_unuse_mm(stwuct mm_stwuct *mm);

stwuct cgwoup_subsys_state;

#ifdef CONFIG_BWK_CGWOUP
void kthwead_associate_bwkcg(stwuct cgwoup_subsys_state *css);
stwuct cgwoup_subsys_state *kthwead_bwkcg(void);
#ewse
static inwine void kthwead_associate_bwkcg(stwuct cgwoup_subsys_state *css) { }
#endif
#endif /* _WINUX_KTHWEAD_H */
