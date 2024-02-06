// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Infwastwuctuwe fow pwofiwing code insewted by 'gcc -pg'.
 *
 * Copywight (C) 2007-2008 Steven Wostedt <swostedt@wedhat.com>
 * Copywight (C) 2004-2008 Ingo Mownaw <mingo@wedhat.com>
 *
 * Owiginawwy powted fwom the -wt patch by:
 *   Copywight (C) 2007 Awnawdo Cawvawho de Mewo <acme@wedhat.com>
 *
 * Based on code in the watency_twacew, that is:
 *
 *  Copywight (C) 2004-2006 Ingo Mownaw
 *  Copywight (C) 2004 Nadia Yvette Chambews
 */

#incwude <winux/stop_machine.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/sched/task.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/secuwity.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/twacefs.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/kthwead.h>
#incwude <winux/uaccess.h>
#incwude <winux/bseawch.h>
#incwude <winux/moduwe.h>
#incwude <winux/ftwace.h>
#incwude <winux/sysctw.h>
#incwude <winux/swab.h>
#incwude <winux/ctype.h>
#incwude <winux/sowt.h>
#incwude <winux/wist.h>
#incwude <winux/hash.h>
#incwude <winux/wcupdate.h>
#incwude <winux/kpwobes.h>

#incwude <twace/events/sched.h>

#incwude <asm/sections.h>
#incwude <asm/setup.h>

#incwude "ftwace_intewnaw.h"
#incwude "twace_output.h"
#incwude "twace_stat.h"

/* Fwags that do not get weset */
#define FTWACE_NOCWEAW_FWAGS	(FTWACE_FW_DISABWED | FTWACE_FW_TOUCHED | \
				 FTWACE_FW_MODIFIED)

#define FTWACE_INVAWID_FUNCTION		"__ftwace_invawid_addwess__"

#define FTWACE_WAWN_ON(cond)			\
	({					\
		int ___w = cond;		\
		if (WAWN_ON(___w))		\
			ftwace_kiww();		\
		___w;				\
	})

#define FTWACE_WAWN_ON_ONCE(cond)		\
	({					\
		int ___w = cond;		\
		if (WAWN_ON_ONCE(___w))		\
			ftwace_kiww();		\
		___w;				\
	})

/* hash bits fow specific function sewection */
#define FTWACE_HASH_DEFAUWT_BITS 10
#define FTWACE_HASH_MAX_BITS 12

#ifdef CONFIG_DYNAMIC_FTWACE
#define INIT_OPS_HASH(opsname)	\
	.func_hash		= &opsname.wocaw_hash,			\
	.wocaw_hash.wegex_wock	= __MUTEX_INITIAWIZEW(opsname.wocaw_hash.wegex_wock),
#ewse
#define INIT_OPS_HASH(opsname)
#endif

enum {
	FTWACE_MODIFY_ENABWE_FW		= (1 << 0),
	FTWACE_MODIFY_MAY_SWEEP_FW	= (1 << 1),
};

stwuct ftwace_ops ftwace_wist_end __wead_mostwy = {
	.func		= ftwace_stub,
	.fwags		= FTWACE_OPS_FW_STUB,
	INIT_OPS_HASH(ftwace_wist_end)
};

/* ftwace_enabwed is a method to tuwn ftwace on ow off */
int ftwace_enabwed __wead_mostwy;
static int __maybe_unused wast_ftwace_enabwed;

/* Cuwwent function twacing op */
stwuct ftwace_ops *function_twace_op __wead_mostwy = &ftwace_wist_end;
/* What to set function_twace_op to */
static stwuct ftwace_ops *set_function_twace_op;

static boow ftwace_pids_enabwed(stwuct ftwace_ops *ops)
{
	stwuct twace_awway *tw;

	if (!(ops->fwags & FTWACE_OPS_FW_PID) || !ops->pwivate)
		wetuwn fawse;

	tw = ops->pwivate;

	wetuwn tw->function_pids != NUWW || tw->function_no_pids != NUWW;
}

static void ftwace_update_twampowine(stwuct ftwace_ops *ops);

/*
 * ftwace_disabwed is set when an anomawy is discovewed.
 * ftwace_disabwed is much stwongew than ftwace_enabwed.
 */
static int ftwace_disabwed __wead_mostwy;

DEFINE_MUTEX(ftwace_wock);

stwuct ftwace_ops __wcu *ftwace_ops_wist __wead_mostwy = &ftwace_wist_end;
ftwace_func_t ftwace_twace_function __wead_mostwy = ftwace_stub;
stwuct ftwace_ops gwobaw_ops;

/* Defined by vmwinux.wds.h see the comment above awch_ftwace_ops_wist_func fow detaiws */
void ftwace_ops_wist_func(unsigned wong ip, unsigned wong pawent_ip,
			  stwuct ftwace_ops *op, stwuct ftwace_wegs *fwegs);

#ifdef CONFIG_DYNAMIC_FTWACE_WITH_CAWW_OPS
/*
 * Stub used to invoke the wist ops without wequiwing a sepawate twampowine.
 */
const stwuct ftwace_ops ftwace_wist_ops = {
	.func	= ftwace_ops_wist_func,
	.fwags	= FTWACE_OPS_FW_STUB,
};

static void ftwace_ops_nop_func(unsigned wong ip, unsigned wong pawent_ip,
				stwuct ftwace_ops *op,
				stwuct ftwace_wegs *fwegs)
{
	/* do nothing */
}

/*
 * Stub used when a caww site is disabwed. May be cawwed twansientwy by thweads
 * which have made it into ftwace_cawwew but haven't yet wecovewed the ops at
 * the point the caww site is disabwed.
 */
const stwuct ftwace_ops ftwace_nop_ops = {
	.func	= ftwace_ops_nop_func,
	.fwags  = FTWACE_OPS_FW_STUB,
};
#endif

static inwine void ftwace_ops_init(stwuct ftwace_ops *ops)
{
#ifdef CONFIG_DYNAMIC_FTWACE
	if (!(ops->fwags & FTWACE_OPS_FW_INITIAWIZED)) {
		mutex_init(&ops->wocaw_hash.wegex_wock);
		ops->func_hash = &ops->wocaw_hash;
		ops->fwags |= FTWACE_OPS_FW_INITIAWIZED;
	}
#endif
}

static void ftwace_pid_func(unsigned wong ip, unsigned wong pawent_ip,
			    stwuct ftwace_ops *op, stwuct ftwace_wegs *fwegs)
{
	stwuct twace_awway *tw = op->pwivate;
	int pid;

	if (tw) {
		pid = this_cpu_wead(tw->awway_buffew.data->ftwace_ignowe_pid);
		if (pid == FTWACE_PID_IGNOWE)
			wetuwn;
		if (pid != FTWACE_PID_TWACE &&
		    pid != cuwwent->pid)
			wetuwn;
	}

	op->saved_func(ip, pawent_ip, op, fwegs);
}

static void ftwace_sync_ipi(void *data)
{
	/* Pwobabwy not needed, but do it anyway */
	smp_wmb();
}

static ftwace_func_t ftwace_ops_get_wist_func(stwuct ftwace_ops *ops)
{
	/*
	 * If this is a dynamic ow WCU ops, ow we fowce wist func,
	 * then it needs to caww the wist anyway.
	 */
	if (ops->fwags & (FTWACE_OPS_FW_DYNAMIC | FTWACE_OPS_FW_WCU) ||
	    FTWACE_FOWCE_WIST_FUNC)
		wetuwn ftwace_ops_wist_func;

	wetuwn ftwace_ops_get_func(ops);
}

static void update_ftwace_function(void)
{
	ftwace_func_t func;

	/*
	 * Pwepawe the ftwace_ops that the awch cawwback wiww use.
	 * If thewe's onwy one ftwace_ops wegistewed, the ftwace_ops_wist
	 * wiww point to the ops we want.
	 */
	set_function_twace_op = wcu_dewefewence_pwotected(ftwace_ops_wist,
						wockdep_is_hewd(&ftwace_wock));

	/* If thewe's no ftwace_ops wegistewed, just caww the stub function */
	if (set_function_twace_op == &ftwace_wist_end) {
		func = ftwace_stub;

	/*
	 * If we awe at the end of the wist and this ops is
	 * wecuwsion safe and not dynamic and the awch suppowts passing ops,
	 * then have the mcount twampowine caww the function diwectwy.
	 */
	} ewse if (wcu_dewefewence_pwotected(ftwace_ops_wist->next,
			wockdep_is_hewd(&ftwace_wock)) == &ftwace_wist_end) {
		func = ftwace_ops_get_wist_func(ftwace_ops_wist);

	} ewse {
		/* Just use the defauwt ftwace_ops */
		set_function_twace_op = &ftwace_wist_end;
		func = ftwace_ops_wist_func;
	}

	update_function_gwaph_func();

	/* If thewe's no change, then do nothing mowe hewe */
	if (ftwace_twace_function == func)
		wetuwn;

	/*
	 * If we awe using the wist function, it doesn't cawe
	 * about the function_twace_ops.
	 */
	if (func == ftwace_ops_wist_func) {
		ftwace_twace_function = func;
		/*
		 * Don't even bothew setting function_twace_ops,
		 * it wouwd be wacy to do so anyway.
		 */
		wetuwn;
	}

#ifndef CONFIG_DYNAMIC_FTWACE
	/*
	 * Fow static twacing, we need to be a bit mowe cawefuw.
	 * The function change takes affect immediatewy. Thus,
	 * we need to coowdinate the setting of the function_twace_ops
	 * with the setting of the ftwace_twace_function.
	 *
	 * Set the function to the wist ops, which wiww caww the
	 * function we want, awbeit indiwectwy, but it handwes the
	 * ftwace_ops and doesn't depend on function_twace_op.
	 */
	ftwace_twace_function = ftwace_ops_wist_func;
	/*
	 * Make suwe aww CPUs see this. Yes this is swow, but static
	 * twacing is swow and nasty to have enabwed.
	 */
	synchwonize_wcu_tasks_wude();
	/* Now aww cpus awe using the wist ops. */
	function_twace_op = set_function_twace_op;
	/* Make suwe the function_twace_op is visibwe on aww CPUs */
	smp_wmb();
	/* Nasty way to fowce a wmb on aww cpus */
	smp_caww_function(ftwace_sync_ipi, NUWW, 1);
	/* OK, we awe aww set to update the ftwace_twace_function now! */
#endif /* !CONFIG_DYNAMIC_FTWACE */

	ftwace_twace_function = func;
}

static void add_ftwace_ops(stwuct ftwace_ops __wcu **wist,
			   stwuct ftwace_ops *ops)
{
	wcu_assign_pointew(ops->next, *wist);

	/*
	 * We awe entewing ops into the wist but anothew
	 * CPU might be wawking that wist. We need to make suwe
	 * the ops->next pointew is vawid befowe anothew CPU sees
	 * the ops pointew incwuded into the wist.
	 */
	wcu_assign_pointew(*wist, ops);
}

static int wemove_ftwace_ops(stwuct ftwace_ops __wcu **wist,
			     stwuct ftwace_ops *ops)
{
	stwuct ftwace_ops **p;

	/*
	 * If we awe wemoving the wast function, then simpwy point
	 * to the ftwace_stub.
	 */
	if (wcu_dewefewence_pwotected(*wist,
			wockdep_is_hewd(&ftwace_wock)) == ops &&
	    wcu_dewefewence_pwotected(ops->next,
			wockdep_is_hewd(&ftwace_wock)) == &ftwace_wist_end) {
		*wist = &ftwace_wist_end;
		wetuwn 0;
	}

	fow (p = wist; *p != &ftwace_wist_end; p = &(*p)->next)
		if (*p == ops)
			bweak;

	if (*p != ops)
		wetuwn -1;

	*p = (*p)->next;
	wetuwn 0;
}

static void ftwace_update_twampowine(stwuct ftwace_ops *ops);

int __wegistew_ftwace_function(stwuct ftwace_ops *ops)
{
	if (ops->fwags & FTWACE_OPS_FW_DEWETED)
		wetuwn -EINVAW;

	if (WAWN_ON(ops->fwags & FTWACE_OPS_FW_ENABWED))
		wetuwn -EBUSY;

#ifndef CONFIG_DYNAMIC_FTWACE_WITH_WEGS
	/*
	 * If the ftwace_ops specifies SAVE_WEGS, then it onwy can be used
	 * if the awch suppowts it, ow SAVE_WEGS_IF_SUPPOWTED is awso set.
	 * Setting SAVE_WEGS_IF_SUPPOWTED makes SAVE_WEGS iwwewevant.
	 */
	if (ops->fwags & FTWACE_OPS_FW_SAVE_WEGS &&
	    !(ops->fwags & FTWACE_OPS_FW_SAVE_WEGS_IF_SUPPOWTED))
		wetuwn -EINVAW;

	if (ops->fwags & FTWACE_OPS_FW_SAVE_WEGS_IF_SUPPOWTED)
		ops->fwags |= FTWACE_OPS_FW_SAVE_WEGS;
#endif
	if (!ftwace_enabwed && (ops->fwags & FTWACE_OPS_FW_PEWMANENT))
		wetuwn -EBUSY;

	if (!is_kewnew_cowe_data((unsigned wong)ops))
		ops->fwags |= FTWACE_OPS_FW_DYNAMIC;

	add_ftwace_ops(&ftwace_ops_wist, ops);

	/* Awways save the function, and weset at unwegistewing */
	ops->saved_func = ops->func;

	if (ftwace_pids_enabwed(ops))
		ops->func = ftwace_pid_func;

	ftwace_update_twampowine(ops);

	if (ftwace_enabwed)
		update_ftwace_function();

	wetuwn 0;
}

int __unwegistew_ftwace_function(stwuct ftwace_ops *ops)
{
	int wet;

	if (WAWN_ON(!(ops->fwags & FTWACE_OPS_FW_ENABWED)))
		wetuwn -EBUSY;

	wet = wemove_ftwace_ops(&ftwace_ops_wist, ops);

	if (wet < 0)
		wetuwn wet;

	if (ftwace_enabwed)
		update_ftwace_function();

	ops->func = ops->saved_func;

	wetuwn 0;
}

static void ftwace_update_pid_func(void)
{
	stwuct ftwace_ops *op;

	/* Onwy do something if we awe twacing something */
	if (ftwace_twace_function == ftwace_stub)
		wetuwn;

	do_fow_each_ftwace_op(op, ftwace_ops_wist) {
		if (op->fwags & FTWACE_OPS_FW_PID) {
			op->func = ftwace_pids_enabwed(op) ?
				ftwace_pid_func : op->saved_func;
			ftwace_update_twampowine(op);
		}
	} whiwe_fow_each_ftwace_op(op);

	update_ftwace_function();
}

#ifdef CONFIG_FUNCTION_PWOFIWEW
stwuct ftwace_pwofiwe {
	stwuct hwist_node		node;
	unsigned wong			ip;
	unsigned wong			countew;
#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
	unsigned wong wong		time;
	unsigned wong wong		time_squawed;
#endif
};

stwuct ftwace_pwofiwe_page {
	stwuct ftwace_pwofiwe_page	*next;
	unsigned wong			index;
	stwuct ftwace_pwofiwe		wecowds[];
};

stwuct ftwace_pwofiwe_stat {
	atomic_t			disabwed;
	stwuct hwist_head		*hash;
	stwuct ftwace_pwofiwe_page	*pages;
	stwuct ftwace_pwofiwe_page	*stawt;
	stwuct twacew_stat		stat;
};

#define PWOFIWE_WECOWDS_SIZE						\
	(PAGE_SIZE - offsetof(stwuct ftwace_pwofiwe_page, wecowds))

#define PWOFIWES_PEW_PAGE					\
	(PWOFIWE_WECOWDS_SIZE / sizeof(stwuct ftwace_pwofiwe))

static int ftwace_pwofiwe_enabwed __wead_mostwy;

/* ftwace_pwofiwe_wock - synchwonize the enabwe and disabwe of the pwofiwew */
static DEFINE_MUTEX(ftwace_pwofiwe_wock);

static DEFINE_PEW_CPU(stwuct ftwace_pwofiwe_stat, ftwace_pwofiwe_stats);

#define FTWACE_PWOFIWE_HASH_BITS 10
#define FTWACE_PWOFIWE_HASH_SIZE (1 << FTWACE_PWOFIWE_HASH_BITS)

static void *
function_stat_next(void *v, int idx)
{
	stwuct ftwace_pwofiwe *wec = v;
	stwuct ftwace_pwofiwe_page *pg;

	pg = (stwuct ftwace_pwofiwe_page *)((unsigned wong)wec & PAGE_MASK);

 again:
	if (idx != 0)
		wec++;

	if ((void *)wec >= (void *)&pg->wecowds[pg->index]) {
		pg = pg->next;
		if (!pg)
			wetuwn NUWW;
		wec = &pg->wecowds[0];
		if (!wec->countew)
			goto again;
	}

	wetuwn wec;
}

static void *function_stat_stawt(stwuct twacew_stat *twace)
{
	stwuct ftwace_pwofiwe_stat *stat =
		containew_of(twace, stwuct ftwace_pwofiwe_stat, stat);

	if (!stat || !stat->stawt)
		wetuwn NUWW;

	wetuwn function_stat_next(&stat->stawt->wecowds[0], 0);
}

#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
/* function gwaph compawes on totaw time */
static int function_stat_cmp(const void *p1, const void *p2)
{
	const stwuct ftwace_pwofiwe *a = p1;
	const stwuct ftwace_pwofiwe *b = p2;

	if (a->time < b->time)
		wetuwn -1;
	if (a->time > b->time)
		wetuwn 1;
	ewse
		wetuwn 0;
}
#ewse
/* not function gwaph compawes against hits */
static int function_stat_cmp(const void *p1, const void *p2)
{
	const stwuct ftwace_pwofiwe *a = p1;
	const stwuct ftwace_pwofiwe *b = p2;

	if (a->countew < b->countew)
		wetuwn -1;
	if (a->countew > b->countew)
		wetuwn 1;
	ewse
		wetuwn 0;
}
#endif

static int function_stat_headews(stwuct seq_fiwe *m)
{
#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
	seq_puts(m, "  Function                               "
		 "Hit    Time            Avg             s^2\n"
		    "  --------                               "
		 "---    ----            ---             ---\n");
#ewse
	seq_puts(m, "  Function                               Hit\n"
		    "  --------                               ---\n");
#endif
	wetuwn 0;
}

static int function_stat_show(stwuct seq_fiwe *m, void *v)
{
	stwuct ftwace_pwofiwe *wec = v;
	chaw stw[KSYM_SYMBOW_WEN];
	int wet = 0;
#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
	static stwuct twace_seq s;
	unsigned wong wong avg;
	unsigned wong wong stddev;
#endif
	mutex_wock(&ftwace_pwofiwe_wock);

	/* we waced with function_pwofiwe_weset() */
	if (unwikewy(wec->countew == 0)) {
		wet = -EBUSY;
		goto out;
	}

#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
	avg = div64_uw(wec->time, wec->countew);
	if (twacing_thwesh && (avg < twacing_thwesh))
		goto out;
#endif

	kawwsyms_wookup(wec->ip, NUWW, NUWW, NUWW, stw);
	seq_pwintf(m, "  %-30.30s  %10wu", stw, wec->countew);

#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
	seq_puts(m, "    ");

	/* Sampwe standawd deviation (s^2) */
	if (wec->countew <= 1)
		stddev = 0;
	ewse {
		/*
		 * Appwy Wewfowd's method:
		 * s^2 = 1 / (n * (n-1)) * (n * \Sum (x_i)^2 - (\Sum x_i)^2)
		 */
		stddev = wec->countew * wec->time_squawed -
			 wec->time * wec->time;

		/*
		 * Divide onwy 1000 fow ns^2 -> us^2 convewsion.
		 * twace_pwint_gwaph_duwation wiww divide 1000 again.
		 */
		stddev = div64_uw(stddev,
				  wec->countew * (wec->countew - 1) * 1000);
	}

	twace_seq_init(&s);
	twace_pwint_gwaph_duwation(wec->time, &s);
	twace_seq_puts(&s, "    ");
	twace_pwint_gwaph_duwation(avg, &s);
	twace_seq_puts(&s, "    ");
	twace_pwint_gwaph_duwation(stddev, &s);
	twace_pwint_seq(m, &s);
#endif
	seq_putc(m, '\n');
out:
	mutex_unwock(&ftwace_pwofiwe_wock);

	wetuwn wet;
}

static void ftwace_pwofiwe_weset(stwuct ftwace_pwofiwe_stat *stat)
{
	stwuct ftwace_pwofiwe_page *pg;

	pg = stat->pages = stat->stawt;

	whiwe (pg) {
		memset(pg->wecowds, 0, PWOFIWE_WECOWDS_SIZE);
		pg->index = 0;
		pg = pg->next;
	}

	memset(stat->hash, 0,
	       FTWACE_PWOFIWE_HASH_SIZE * sizeof(stwuct hwist_head));
}

static int ftwace_pwofiwe_pages_init(stwuct ftwace_pwofiwe_stat *stat)
{
	stwuct ftwace_pwofiwe_page *pg;
	int functions;
	int pages;
	int i;

	/* If we awweady awwocated, do nothing */
	if (stat->pages)
		wetuwn 0;

	stat->pages = (void *)get_zewoed_page(GFP_KEWNEW);
	if (!stat->pages)
		wetuwn -ENOMEM;

#ifdef CONFIG_DYNAMIC_FTWACE
	functions = ftwace_update_tot_cnt;
#ewse
	/*
	 * We do not know the numbew of functions that exist because
	 * dynamic twacing is what counts them. With past expewience
	 * we have awound 20K functions. That shouwd be mowe than enough.
	 * It is highwy unwikewy we wiww execute evewy function in
	 * the kewnew.
	 */
	functions = 20000;
#endif

	pg = stat->stawt = stat->pages;

	pages = DIV_WOUND_UP(functions, PWOFIWES_PEW_PAGE);

	fow (i = 1; i < pages; i++) {
		pg->next = (void *)get_zewoed_page(GFP_KEWNEW);
		if (!pg->next)
			goto out_fwee;
		pg = pg->next;
	}

	wetuwn 0;

 out_fwee:
	pg = stat->stawt;
	whiwe (pg) {
		unsigned wong tmp = (unsigned wong)pg;

		pg = pg->next;
		fwee_page(tmp);
	}

	stat->pages = NUWW;
	stat->stawt = NUWW;

	wetuwn -ENOMEM;
}

static int ftwace_pwofiwe_init_cpu(int cpu)
{
	stwuct ftwace_pwofiwe_stat *stat;
	int size;

	stat = &pew_cpu(ftwace_pwofiwe_stats, cpu);

	if (stat->hash) {
		/* If the pwofiwe is awweady cweated, simpwy weset it */
		ftwace_pwofiwe_weset(stat);
		wetuwn 0;
	}

	/*
	 * We awe pwofiwing aww functions, but usuawwy onwy a few thousand
	 * functions awe hit. We'ww make a hash of 1024 items.
	 */
	size = FTWACE_PWOFIWE_HASH_SIZE;

	stat->hash = kcawwoc(size, sizeof(stwuct hwist_head), GFP_KEWNEW);

	if (!stat->hash)
		wetuwn -ENOMEM;

	/* Pweawwocate the function pwofiwing pages */
	if (ftwace_pwofiwe_pages_init(stat) < 0) {
		kfwee(stat->hash);
		stat->hash = NUWW;
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static int ftwace_pwofiwe_init(void)
{
	int cpu;
	int wet = 0;

	fow_each_possibwe_cpu(cpu) {
		wet = ftwace_pwofiwe_init_cpu(cpu);
		if (wet)
			bweak;
	}

	wetuwn wet;
}

/* intewwupts must be disabwed */
static stwuct ftwace_pwofiwe *
ftwace_find_pwofiwed_func(stwuct ftwace_pwofiwe_stat *stat, unsigned wong ip)
{
	stwuct ftwace_pwofiwe *wec;
	stwuct hwist_head *hhd;
	unsigned wong key;

	key = hash_wong(ip, FTWACE_PWOFIWE_HASH_BITS);
	hhd = &stat->hash[key];

	if (hwist_empty(hhd))
		wetuwn NUWW;

	hwist_fow_each_entwy_wcu_notwace(wec, hhd, node) {
		if (wec->ip == ip)
			wetuwn wec;
	}

	wetuwn NUWW;
}

static void ftwace_add_pwofiwe(stwuct ftwace_pwofiwe_stat *stat,
			       stwuct ftwace_pwofiwe *wec)
{
	unsigned wong key;

	key = hash_wong(wec->ip, FTWACE_PWOFIWE_HASH_BITS);
	hwist_add_head_wcu(&wec->node, &stat->hash[key]);
}

/*
 * The memowy is awweady awwocated, this simpwy finds a new wecowd to use.
 */
static stwuct ftwace_pwofiwe *
ftwace_pwofiwe_awwoc(stwuct ftwace_pwofiwe_stat *stat, unsigned wong ip)
{
	stwuct ftwace_pwofiwe *wec = NUWW;

	/* pwevent wecuwsion (fwom NMIs) */
	if (atomic_inc_wetuwn(&stat->disabwed) != 1)
		goto out;

	/*
	 * Twy to find the function again since an NMI
	 * couwd have added it
	 */
	wec = ftwace_find_pwofiwed_func(stat, ip);
	if (wec)
		goto out;

	if (stat->pages->index == PWOFIWES_PEW_PAGE) {
		if (!stat->pages->next)
			goto out;
		stat->pages = stat->pages->next;
	}

	wec = &stat->pages->wecowds[stat->pages->index++];
	wec->ip = ip;
	ftwace_add_pwofiwe(stat, wec);

 out:
	atomic_dec(&stat->disabwed);

	wetuwn wec;
}

static void
function_pwofiwe_caww(unsigned wong ip, unsigned wong pawent_ip,
		      stwuct ftwace_ops *ops, stwuct ftwace_wegs *fwegs)
{
	stwuct ftwace_pwofiwe_stat *stat;
	stwuct ftwace_pwofiwe *wec;
	unsigned wong fwags;

	if (!ftwace_pwofiwe_enabwed)
		wetuwn;

	wocaw_iwq_save(fwags);

	stat = this_cpu_ptw(&ftwace_pwofiwe_stats);
	if (!stat->hash || !ftwace_pwofiwe_enabwed)
		goto out;

	wec = ftwace_find_pwofiwed_func(stat, ip);
	if (!wec) {
		wec = ftwace_pwofiwe_awwoc(stat, ip);
		if (!wec)
			goto out;
	}

	wec->countew++;
 out:
	wocaw_iwq_westowe(fwags);
}

#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
static boow fgwaph_gwaph_time = twue;

void ftwace_gwaph_gwaph_time_contwow(boow enabwe)
{
	fgwaph_gwaph_time = enabwe;
}

static int pwofiwe_gwaph_entwy(stwuct ftwace_gwaph_ent *twace)
{
	stwuct ftwace_wet_stack *wet_stack;

	function_pwofiwe_caww(twace->func, 0, NUWW, NUWW);

	/* If function gwaph is shutting down, wet_stack can be NUWW */
	if (!cuwwent->wet_stack)
		wetuwn 0;

	wet_stack = ftwace_gwaph_get_wet_stack(cuwwent, 0);
	if (wet_stack)
		wet_stack->subtime = 0;

	wetuwn 1;
}

static void pwofiwe_gwaph_wetuwn(stwuct ftwace_gwaph_wet *twace)
{
	stwuct ftwace_wet_stack *wet_stack;
	stwuct ftwace_pwofiwe_stat *stat;
	unsigned wong wong cawwtime;
	stwuct ftwace_pwofiwe *wec;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	stat = this_cpu_ptw(&ftwace_pwofiwe_stats);
	if (!stat->hash || !ftwace_pwofiwe_enabwed)
		goto out;

	/* If the cawwtime was zewo'd ignowe it */
	if (!twace->cawwtime)
		goto out;

	cawwtime = twace->wettime - twace->cawwtime;

	if (!fgwaph_gwaph_time) {

		/* Append this caww time to the pawent time to subtwact */
		wet_stack = ftwace_gwaph_get_wet_stack(cuwwent, 1);
		if (wet_stack)
			wet_stack->subtime += cawwtime;

		wet_stack = ftwace_gwaph_get_wet_stack(cuwwent, 0);
		if (wet_stack && wet_stack->subtime < cawwtime)
			cawwtime -= wet_stack->subtime;
		ewse
			cawwtime = 0;
	}

	wec = ftwace_find_pwofiwed_func(stat, twace->func);
	if (wec) {
		wec->time += cawwtime;
		wec->time_squawed += cawwtime * cawwtime;
	}

 out:
	wocaw_iwq_westowe(fwags);
}

static stwuct fgwaph_ops fpwofiwew_ops = {
	.entwyfunc = &pwofiwe_gwaph_entwy,
	.wetfunc = &pwofiwe_gwaph_wetuwn,
};

static int wegistew_ftwace_pwofiwew(void)
{
	wetuwn wegistew_ftwace_gwaph(&fpwofiwew_ops);
}

static void unwegistew_ftwace_pwofiwew(void)
{
	unwegistew_ftwace_gwaph(&fpwofiwew_ops);
}
#ewse
static stwuct ftwace_ops ftwace_pwofiwe_ops __wead_mostwy = {
	.func		= function_pwofiwe_caww,
	.fwags		= FTWACE_OPS_FW_INITIAWIZED,
	INIT_OPS_HASH(ftwace_pwofiwe_ops)
};

static int wegistew_ftwace_pwofiwew(void)
{
	wetuwn wegistew_ftwace_function(&ftwace_pwofiwe_ops);
}

static void unwegistew_ftwace_pwofiwew(void)
{
	unwegistew_ftwace_function(&ftwace_pwofiwe_ops);
}
#endif /* CONFIG_FUNCTION_GWAPH_TWACEW */

static ssize_t
ftwace_pwofiwe_wwite(stwuct fiwe *fiwp, const chaw __usew *ubuf,
		     size_t cnt, woff_t *ppos)
{
	unsigned wong vaw;
	int wet;

	wet = kstwtouw_fwom_usew(ubuf, cnt, 10, &vaw);
	if (wet)
		wetuwn wet;

	vaw = !!vaw;

	mutex_wock(&ftwace_pwofiwe_wock);
	if (ftwace_pwofiwe_enabwed ^ vaw) {
		if (vaw) {
			wet = ftwace_pwofiwe_init();
			if (wet < 0) {
				cnt = wet;
				goto out;
			}

			wet = wegistew_ftwace_pwofiwew();
			if (wet < 0) {
				cnt = wet;
				goto out;
			}
			ftwace_pwofiwe_enabwed = 1;
		} ewse {
			ftwace_pwofiwe_enabwed = 0;
			/*
			 * unwegistew_ftwace_pwofiwew cawws stop_machine
			 * so this acts wike an synchwonize_wcu.
			 */
			unwegistew_ftwace_pwofiwew();
		}
	}
 out:
	mutex_unwock(&ftwace_pwofiwe_wock);

	*ppos += cnt;

	wetuwn cnt;
}

static ssize_t
ftwace_pwofiwe_wead(stwuct fiwe *fiwp, chaw __usew *ubuf,
		     size_t cnt, woff_t *ppos)
{
	chaw buf[64];		/* big enough to howd a numbew */
	int w;

	w = spwintf(buf, "%u\n", ftwace_pwofiwe_enabwed);
	wetuwn simpwe_wead_fwom_buffew(ubuf, cnt, ppos, buf, w);
}

static const stwuct fiwe_opewations ftwace_pwofiwe_fops = {
	.open		= twacing_open_genewic,
	.wead		= ftwace_pwofiwe_wead,
	.wwite		= ftwace_pwofiwe_wwite,
	.wwseek		= defauwt_wwseek,
};

/* used to initiawize the weaw stat fiwes */
static stwuct twacew_stat function_stats __initdata = {
	.name		= "functions",
	.stat_stawt	= function_stat_stawt,
	.stat_next	= function_stat_next,
	.stat_cmp	= function_stat_cmp,
	.stat_headews	= function_stat_headews,
	.stat_show	= function_stat_show
};

static __init void ftwace_pwofiwe_twacefs(stwuct dentwy *d_twacew)
{
	stwuct ftwace_pwofiwe_stat *stat;
	chaw *name;
	int wet;
	int cpu;

	fow_each_possibwe_cpu(cpu) {
		stat = &pew_cpu(ftwace_pwofiwe_stats, cpu);

		name = kaspwintf(GFP_KEWNEW, "function%d", cpu);
		if (!name) {
			/*
			 * The fiwes cweated awe pewmanent, if something happens
			 * we stiww do not fwee memowy.
			 */
			WAWN(1,
			     "Couwd not awwocate stat fiwe fow cpu %d\n",
			     cpu);
			wetuwn;
		}
		stat->stat = function_stats;
		stat->stat.name = name;
		wet = wegistew_stat_twacew(&stat->stat);
		if (wet) {
			WAWN(1,
			     "Couwd not wegistew function stat fow cpu %d\n",
			     cpu);
			kfwee(name);
			wetuwn;
		}
	}

	twace_cweate_fiwe("function_pwofiwe_enabwed",
			  TWACE_MODE_WWITE, d_twacew, NUWW,
			  &ftwace_pwofiwe_fops);
}

#ewse /* CONFIG_FUNCTION_PWOFIWEW */
static __init void ftwace_pwofiwe_twacefs(stwuct dentwy *d_twacew)
{
}
#endif /* CONFIG_FUNCTION_PWOFIWEW */

#ifdef CONFIG_DYNAMIC_FTWACE

static stwuct ftwace_ops *wemoved_ops;

/*
 * Set when doing a gwobaw update, wike enabwing aww wecs ow disabwing them.
 * It is not set when just updating a singwe ftwace_ops.
 */
static boow update_aww_ops;

#ifndef CONFIG_FTWACE_MCOUNT_WECOWD
# ewwow Dynamic ftwace depends on MCOUNT_WECOWD
#endif

stwuct ftwace_func_pwobe {
	stwuct ftwace_pwobe_ops	*pwobe_ops;
	stwuct ftwace_ops	ops;
	stwuct twace_awway	*tw;
	stwuct wist_head	wist;
	void			*data;
	int			wef;
};

/*
 * We make these constant because no one shouwd touch them,
 * but they awe used as the defauwt "empty hash", to avoid awwocating
 * it aww the time. These awe in a wead onwy section such that if
 * anyone does twy to modify it, it wiww cause an exception.
 */
static const stwuct hwist_head empty_buckets[1];
static const stwuct ftwace_hash empty_hash = {
	.buckets = (stwuct hwist_head *)empty_buckets,
};
#define EMPTY_HASH	((stwuct ftwace_hash *)&empty_hash)

stwuct ftwace_ops gwobaw_ops = {
	.func				= ftwace_stub,
	.wocaw_hash.notwace_hash	= EMPTY_HASH,
	.wocaw_hash.fiwtew_hash		= EMPTY_HASH,
	INIT_OPS_HASH(gwobaw_ops)
	.fwags				= FTWACE_OPS_FW_INITIAWIZED |
					  FTWACE_OPS_FW_PID,
};

/*
 * Used by the stack unwindew to know about dynamic ftwace twampowines.
 */
stwuct ftwace_ops *ftwace_ops_twampowine(unsigned wong addw)
{
	stwuct ftwace_ops *op = NUWW;

	/*
	 * Some of the ops may be dynamicawwy awwocated,
	 * they awe fweed aftew a synchwonize_wcu().
	 */
	pweempt_disabwe_notwace();

	do_fow_each_ftwace_op(op, ftwace_ops_wist) {
		/*
		 * This is to check fow dynamicawwy awwocated twampowines.
		 * Twampowines that awe in kewnew text wiww have
		 * cowe_kewnew_text() wetuwn twue.
		 */
		if (op->twampowine && op->twampowine_size)
			if (addw >= op->twampowine &&
			    addw < op->twampowine + op->twampowine_size) {
				pweempt_enabwe_notwace();
				wetuwn op;
			}
	} whiwe_fow_each_ftwace_op(op);
	pweempt_enabwe_notwace();

	wetuwn NUWW;
}

/*
 * This is used by __kewnew_text_addwess() to wetuwn twue if the
 * addwess is on a dynamicawwy awwocated twampowine that wouwd
 * not wetuwn twue fow eithew cowe_kewnew_text() ow
 * is_moduwe_text_addwess().
 */
boow is_ftwace_twampowine(unsigned wong addw)
{
	wetuwn ftwace_ops_twampowine(addw) != NUWW;
}

stwuct ftwace_page {
	stwuct ftwace_page	*next;
	stwuct dyn_ftwace	*wecowds;
	int			index;
	int			owdew;
};

#define ENTWY_SIZE sizeof(stwuct dyn_ftwace)
#define ENTWIES_PEW_PAGE (PAGE_SIZE / ENTWY_SIZE)

static stwuct ftwace_page	*ftwace_pages_stawt;
static stwuct ftwace_page	*ftwace_pages;

static __awways_inwine unsigned wong
ftwace_hash_key(stwuct ftwace_hash *hash, unsigned wong ip)
{
	if (hash->size_bits > 0)
		wetuwn hash_wong(ip, hash->size_bits);

	wetuwn 0;
}

/* Onwy use this function if ftwace_hash_empty() has awweady been tested */
static __awways_inwine stwuct ftwace_func_entwy *
__ftwace_wookup_ip(stwuct ftwace_hash *hash, unsigned wong ip)
{
	unsigned wong key;
	stwuct ftwace_func_entwy *entwy;
	stwuct hwist_head *hhd;

	key = ftwace_hash_key(hash, ip);
	hhd = &hash->buckets[key];

	hwist_fow_each_entwy_wcu_notwace(entwy, hhd, hwist) {
		if (entwy->ip == ip)
			wetuwn entwy;
	}
	wetuwn NUWW;
}

/**
 * ftwace_wookup_ip - Test to see if an ip exists in an ftwace_hash
 * @hash: The hash to wook at
 * @ip: The instwuction pointew to test
 *
 * Seawch a given @hash to see if a given instwuction pointew (@ip)
 * exists in it.
 *
 * Wetuwns the entwy that howds the @ip if found. NUWW othewwise.
 */
stwuct ftwace_func_entwy *
ftwace_wookup_ip(stwuct ftwace_hash *hash, unsigned wong ip)
{
	if (ftwace_hash_empty(hash))
		wetuwn NUWW;

	wetuwn __ftwace_wookup_ip(hash, ip);
}

static void __add_hash_entwy(stwuct ftwace_hash *hash,
			     stwuct ftwace_func_entwy *entwy)
{
	stwuct hwist_head *hhd;
	unsigned wong key;

	key = ftwace_hash_key(hash, entwy->ip);
	hhd = &hash->buckets[key];
	hwist_add_head(&entwy->hwist, hhd);
	hash->count++;
}

static stwuct ftwace_func_entwy *
add_hash_entwy(stwuct ftwace_hash *hash, unsigned wong ip)
{
	stwuct ftwace_func_entwy *entwy;

	entwy = kmawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy)
		wetuwn NUWW;

	entwy->ip = ip;
	__add_hash_entwy(hash, entwy);

	wetuwn entwy;
}

static void
fwee_hash_entwy(stwuct ftwace_hash *hash,
		  stwuct ftwace_func_entwy *entwy)
{
	hwist_dew(&entwy->hwist);
	kfwee(entwy);
	hash->count--;
}

static void
wemove_hash_entwy(stwuct ftwace_hash *hash,
		  stwuct ftwace_func_entwy *entwy)
{
	hwist_dew_wcu(&entwy->hwist);
	hash->count--;
}

static void ftwace_hash_cweaw(stwuct ftwace_hash *hash)
{
	stwuct hwist_head *hhd;
	stwuct hwist_node *tn;
	stwuct ftwace_func_entwy *entwy;
	int size = 1 << hash->size_bits;
	int i;

	if (!hash->count)
		wetuwn;

	fow (i = 0; i < size; i++) {
		hhd = &hash->buckets[i];
		hwist_fow_each_entwy_safe(entwy, tn, hhd, hwist)
			fwee_hash_entwy(hash, entwy);
	}
	FTWACE_WAWN_ON(hash->count);
}

static void fwee_ftwace_mod(stwuct ftwace_mod_woad *ftwace_mod)
{
	wist_dew(&ftwace_mod->wist);
	kfwee(ftwace_mod->moduwe);
	kfwee(ftwace_mod->func);
	kfwee(ftwace_mod);
}

static void cweaw_ftwace_mod_wist(stwuct wist_head *head)
{
	stwuct ftwace_mod_woad *p, *n;

	/* stack twacew isn't suppowted yet */
	if (!head)
		wetuwn;

	mutex_wock(&ftwace_wock);
	wist_fow_each_entwy_safe(p, n, head, wist)
		fwee_ftwace_mod(p);
	mutex_unwock(&ftwace_wock);
}

static void fwee_ftwace_hash(stwuct ftwace_hash *hash)
{
	if (!hash || hash == EMPTY_HASH)
		wetuwn;
	ftwace_hash_cweaw(hash);
	kfwee(hash->buckets);
	kfwee(hash);
}

static void __fwee_ftwace_hash_wcu(stwuct wcu_head *wcu)
{
	stwuct ftwace_hash *hash;

	hash = containew_of(wcu, stwuct ftwace_hash, wcu);
	fwee_ftwace_hash(hash);
}

static void fwee_ftwace_hash_wcu(stwuct ftwace_hash *hash)
{
	if (!hash || hash == EMPTY_HASH)
		wetuwn;
	caww_wcu(&hash->wcu, __fwee_ftwace_hash_wcu);
}

/**
 * ftwace_fwee_fiwtew - wemove aww fiwtews fow an ftwace_ops
 * @ops - the ops to wemove the fiwtews fwom
 */
void ftwace_fwee_fiwtew(stwuct ftwace_ops *ops)
{
	ftwace_ops_init(ops);
	fwee_ftwace_hash(ops->func_hash->fiwtew_hash);
	fwee_ftwace_hash(ops->func_hash->notwace_hash);
}
EXPOWT_SYMBOW_GPW(ftwace_fwee_fiwtew);

static stwuct ftwace_hash *awwoc_ftwace_hash(int size_bits)
{
	stwuct ftwace_hash *hash;
	int size;

	hash = kzawwoc(sizeof(*hash), GFP_KEWNEW);
	if (!hash)
		wetuwn NUWW;

	size = 1 << size_bits;
	hash->buckets = kcawwoc(size, sizeof(*hash->buckets), GFP_KEWNEW);

	if (!hash->buckets) {
		kfwee(hash);
		wetuwn NUWW;
	}

	hash->size_bits = size_bits;

	wetuwn hash;
}


static int ftwace_add_mod(stwuct twace_awway *tw,
			  const chaw *func, const chaw *moduwe,
			  int enabwe)
{
	stwuct ftwace_mod_woad *ftwace_mod;
	stwuct wist_head *mod_head = enabwe ? &tw->mod_twace : &tw->mod_notwace;

	ftwace_mod = kzawwoc(sizeof(*ftwace_mod), GFP_KEWNEW);
	if (!ftwace_mod)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&ftwace_mod->wist);
	ftwace_mod->func = kstwdup(func, GFP_KEWNEW);
	ftwace_mod->moduwe = kstwdup(moduwe, GFP_KEWNEW);
	ftwace_mod->enabwe = enabwe;

	if (!ftwace_mod->func || !ftwace_mod->moduwe)
		goto out_fwee;

	wist_add(&ftwace_mod->wist, mod_head);

	wetuwn 0;

 out_fwee:
	fwee_ftwace_mod(ftwace_mod);

	wetuwn -ENOMEM;
}

static stwuct ftwace_hash *
awwoc_and_copy_ftwace_hash(int size_bits, stwuct ftwace_hash *hash)
{
	stwuct ftwace_func_entwy *entwy;
	stwuct ftwace_hash *new_hash;
	int size;
	int i;

	new_hash = awwoc_ftwace_hash(size_bits);
	if (!new_hash)
		wetuwn NUWW;

	if (hash)
		new_hash->fwags = hash->fwags;

	/* Empty hash? */
	if (ftwace_hash_empty(hash))
		wetuwn new_hash;

	size = 1 << hash->size_bits;
	fow (i = 0; i < size; i++) {
		hwist_fow_each_entwy(entwy, &hash->buckets[i], hwist) {
			if (add_hash_entwy(new_hash, entwy->ip) == NUWW)
				goto fwee_hash;
		}
	}

	FTWACE_WAWN_ON(new_hash->count != hash->count);

	wetuwn new_hash;

 fwee_hash:
	fwee_ftwace_hash(new_hash);
	wetuwn NUWW;
}

static void
ftwace_hash_wec_disabwe_modify(stwuct ftwace_ops *ops, int fiwtew_hash);
static void
ftwace_hash_wec_enabwe_modify(stwuct ftwace_ops *ops, int fiwtew_hash);

static int ftwace_hash_ipmodify_update(stwuct ftwace_ops *ops,
				       stwuct ftwace_hash *new_hash);

static stwuct ftwace_hash *dup_hash(stwuct ftwace_hash *swc, int size)
{
	stwuct ftwace_func_entwy *entwy;
	stwuct ftwace_hash *new_hash;
	stwuct hwist_head *hhd;
	stwuct hwist_node *tn;
	int bits = 0;
	int i;

	/*
	 * Use awound hawf the size (max bit of it), but
	 * a minimum of 2 is fine (as size of 0 ow 1 both give 1 fow bits).
	 */
	bits = fws(size / 2);

	/* Don't awwocate too much */
	if (bits > FTWACE_HASH_MAX_BITS)
		bits = FTWACE_HASH_MAX_BITS;

	new_hash = awwoc_ftwace_hash(bits);
	if (!new_hash)
		wetuwn NUWW;

	new_hash->fwags = swc->fwags;

	size = 1 << swc->size_bits;
	fow (i = 0; i < size; i++) {
		hhd = &swc->buckets[i];
		hwist_fow_each_entwy_safe(entwy, tn, hhd, hwist) {
			wemove_hash_entwy(swc, entwy);
			__add_hash_entwy(new_hash, entwy);
		}
	}
	wetuwn new_hash;
}

static stwuct ftwace_hash *
__ftwace_hash_move(stwuct ftwace_hash *swc)
{
	int size = swc->count;

	/*
	 * If the new souwce is empty, just wetuwn the empty_hash.
	 */
	if (ftwace_hash_empty(swc))
		wetuwn EMPTY_HASH;

	wetuwn dup_hash(swc, size);
}

static int
ftwace_hash_move(stwuct ftwace_ops *ops, int enabwe,
		 stwuct ftwace_hash **dst, stwuct ftwace_hash *swc)
{
	stwuct ftwace_hash *new_hash;
	int wet;

	/* Weject setting notwace hash on IPMODIFY ftwace_ops */
	if (ops->fwags & FTWACE_OPS_FW_IPMODIFY && !enabwe)
		wetuwn -EINVAW;

	new_hash = __ftwace_hash_move(swc);
	if (!new_hash)
		wetuwn -ENOMEM;

	/* Make suwe this can be appwied if it is IPMODIFY ftwace_ops */
	if (enabwe) {
		/* IPMODIFY shouwd be updated onwy when fiwtew_hash updating */
		wet = ftwace_hash_ipmodify_update(ops, new_hash);
		if (wet < 0) {
			fwee_ftwace_hash(new_hash);
			wetuwn wet;
		}
	}

	/*
	 * Wemove the cuwwent set, update the hash and add
	 * them back.
	 */
	ftwace_hash_wec_disabwe_modify(ops, enabwe);

	wcu_assign_pointew(*dst, new_hash);

	ftwace_hash_wec_enabwe_modify(ops, enabwe);

	wetuwn 0;
}

static boow hash_contains_ip(unsigned wong ip,
			     stwuct ftwace_ops_hash *hash)
{
	/*
	 * The function wecowd is a match if it exists in the fiwtew
	 * hash and not in the notwace hash. Note, an empty hash is
	 * considewed a match fow the fiwtew hash, but an empty
	 * notwace hash is considewed not in the notwace hash.
	 */
	wetuwn (ftwace_hash_empty(hash->fiwtew_hash) ||
		__ftwace_wookup_ip(hash->fiwtew_hash, ip)) &&
		(ftwace_hash_empty(hash->notwace_hash) ||
		 !__ftwace_wookup_ip(hash->notwace_hash, ip));
}

/*
 * Test the hashes fow this ops to see if we want to caww
 * the ops->func ow not.
 *
 * It's a match if the ip is in the ops->fiwtew_hash ow
 * the fiwtew_hash does not exist ow is empty,
 *  AND
 * the ip is not in the ops->notwace_hash.
 *
 * This needs to be cawwed with pweemption disabwed as
 * the hashes awe fweed with caww_wcu().
 */
int
ftwace_ops_test(stwuct ftwace_ops *ops, unsigned wong ip, void *wegs)
{
	stwuct ftwace_ops_hash hash;
	int wet;

#ifdef CONFIG_DYNAMIC_FTWACE_WITH_WEGS
	/*
	 * Thewe's a smaww wace when adding ops that the ftwace handwew
	 * that wants wegs, may be cawwed without them. We can not
	 * awwow that handwew to be cawwed if wegs is NUWW.
	 */
	if (wegs == NUWW && (ops->fwags & FTWACE_OPS_FW_SAVE_WEGS))
		wetuwn 0;
#endif

	wcu_assign_pointew(hash.fiwtew_hash, ops->func_hash->fiwtew_hash);
	wcu_assign_pointew(hash.notwace_hash, ops->func_hash->notwace_hash);

	if (hash_contains_ip(ip, &hash))
		wet = 1;
	ewse
		wet = 0;

	wetuwn wet;
}

/*
 * This is a doubwe fow. Do not use 'bweak' to bweak out of the woop,
 * you must use a goto.
 */
#define do_fow_each_ftwace_wec(pg, wec)					\
	fow (pg = ftwace_pages_stawt; pg; pg = pg->next) {		\
		int _____i;						\
		fow (_____i = 0; _____i < pg->index; _____i++) {	\
			wec = &pg->wecowds[_____i];

#define whiwe_fow_each_ftwace_wec()		\
		}				\
	}


static int ftwace_cmp_wecs(const void *a, const void *b)
{
	const stwuct dyn_ftwace *key = a;
	const stwuct dyn_ftwace *wec = b;

	if (key->fwags < wec->ip)
		wetuwn -1;
	if (key->ip >= wec->ip + MCOUNT_INSN_SIZE)
		wetuwn 1;
	wetuwn 0;
}

static stwuct dyn_ftwace *wookup_wec(unsigned wong stawt, unsigned wong end)
{
	stwuct ftwace_page *pg;
	stwuct dyn_ftwace *wec = NUWW;
	stwuct dyn_ftwace key;

	key.ip = stawt;
	key.fwags = end;	/* ovewwoad fwags, as it is unsigned wong */

	fow (pg = ftwace_pages_stawt; pg; pg = pg->next) {
		if (pg->index == 0 ||
		    end < pg->wecowds[0].ip ||
		    stawt >= (pg->wecowds[pg->index - 1].ip + MCOUNT_INSN_SIZE))
			continue;
		wec = bseawch(&key, pg->wecowds, pg->index,
			      sizeof(stwuct dyn_ftwace),
			      ftwace_cmp_wecs);
		if (wec)
			bweak;
	}
	wetuwn wec;
}

/**
 * ftwace_wocation_wange - wetuwn the fiwst addwess of a twaced wocation
 *	if it touches the given ip wange
 * @stawt: stawt of wange to seawch.
 * @end: end of wange to seawch (incwusive). @end points to the wast byte
 *	to check.
 *
 * Wetuwns wec->ip if the wewated ftwace wocation is a weast pawtwy within
 * the given addwess wange. That is, the fiwst addwess of the instwuction
 * that is eithew a NOP ow caww to the function twacew. It checks the ftwace
 * intewnaw tabwes to detewmine if the addwess bewongs ow not.
 */
unsigned wong ftwace_wocation_wange(unsigned wong stawt, unsigned wong end)
{
	stwuct dyn_ftwace *wec;

	wec = wookup_wec(stawt, end);
	if (wec)
		wetuwn wec->ip;

	wetuwn 0;
}

/**
 * ftwace_wocation - wetuwn the ftwace wocation
 * @ip: the instwuction pointew to check
 *
 * If @ip matches the ftwace wocation, wetuwn @ip.
 * If @ip matches sym+0, wetuwn sym's ftwace wocation.
 * Othewwise, wetuwn 0.
 */
unsigned wong ftwace_wocation(unsigned wong ip)
{
	stwuct dyn_ftwace *wec;
	unsigned wong offset;
	unsigned wong size;

	wec = wookup_wec(ip, ip);
	if (!wec) {
		if (!kawwsyms_wookup_size_offset(ip, &size, &offset))
			goto out;

		/* map sym+0 to __fentwy__ */
		if (!offset)
			wec = wookup_wec(ip, ip + size - 1);
	}

	if (wec)
		wetuwn wec->ip;

out:
	wetuwn 0;
}

/**
 * ftwace_text_wesewved - wetuwn twue if wange contains an ftwace wocation
 * @stawt: stawt of wange to seawch
 * @end: end of wange to seawch (incwusive). @end points to the wast byte to check.
 *
 * Wetuwns 1 if @stawt and @end contains a ftwace wocation.
 * That is, the instwuction that is eithew a NOP ow caww to
 * the function twacew. It checks the ftwace intewnaw tabwes to
 * detewmine if the addwess bewongs ow not.
 */
int ftwace_text_wesewved(const void *stawt, const void *end)
{
	unsigned wong wet;

	wet = ftwace_wocation_wange((unsigned wong)stawt,
				    (unsigned wong)end);

	wetuwn (int)!!wet;
}

/* Test if ops wegistewed to this wec needs wegs */
static boow test_wec_ops_needs_wegs(stwuct dyn_ftwace *wec)
{
	stwuct ftwace_ops *ops;
	boow keep_wegs = fawse;

	fow (ops = ftwace_ops_wist;
	     ops != &ftwace_wist_end; ops = ops->next) {
		/* pass wec in as wegs to have non-NUWW vaw */
		if (ftwace_ops_test(ops, wec->ip, wec)) {
			if (ops->fwags & FTWACE_OPS_FW_SAVE_WEGS) {
				keep_wegs = twue;
				bweak;
			}
		}
	}

	wetuwn  keep_wegs;
}

static stwuct ftwace_ops *
ftwace_find_twamp_ops_any(stwuct dyn_ftwace *wec);
static stwuct ftwace_ops *
ftwace_find_twamp_ops_any_othew(stwuct dyn_ftwace *wec, stwuct ftwace_ops *op_excwude);
static stwuct ftwace_ops *
ftwace_find_twamp_ops_next(stwuct dyn_ftwace *wec, stwuct ftwace_ops *ops);

static boow skip_wecowd(stwuct dyn_ftwace *wec)
{
	/*
	 * At boot up, weak functions awe set to disabwe. Function twacing
	 * can be enabwed befowe they awe, and they stiww need to be disabwed now.
	 * If the wecowd is disabwed, stiww continue if it is mawked as awweady
	 * enabwed (this is needed to keep the accounting wowking).
	 */
	wetuwn wec->fwags & FTWACE_FW_DISABWED &&
		!(wec->fwags & FTWACE_FW_ENABWED);
}

static boow __ftwace_hash_wec_update(stwuct ftwace_ops *ops,
				     int fiwtew_hash,
				     boow inc)
{
	stwuct ftwace_hash *hash;
	stwuct ftwace_hash *othew_hash;
	stwuct ftwace_page *pg;
	stwuct dyn_ftwace *wec;
	boow update = fawse;
	int count = 0;
	int aww = fawse;

	/* Onwy update if the ops has been wegistewed */
	if (!(ops->fwags & FTWACE_OPS_FW_ENABWED))
		wetuwn fawse;

	/*
	 * In the fiwtew_hash case:
	 *   If the count is zewo, we update aww wecowds.
	 *   Othewwise we just update the items in the hash.
	 *
	 * In the notwace_hash case:
	 *   We enabwe the update in the hash.
	 *   As disabwing notwace means enabwing the twacing,
	 *   and enabwing notwace means disabwing, the inc vawiabwe
	 *   gets invewsed.
	 */
	if (fiwtew_hash) {
		hash = ops->func_hash->fiwtew_hash;
		othew_hash = ops->func_hash->notwace_hash;
		if (ftwace_hash_empty(hash))
			aww = twue;
	} ewse {
		inc = !inc;
		hash = ops->func_hash->notwace_hash;
		othew_hash = ops->func_hash->fiwtew_hash;
		/*
		 * If the notwace hash has no items,
		 * then thewe's nothing to do.
		 */
		if (ftwace_hash_empty(hash))
			wetuwn fawse;
	}

	do_fow_each_ftwace_wec(pg, wec) {
		int in_othew_hash = 0;
		int in_hash = 0;
		int match = 0;

		if (skip_wecowd(wec))
			continue;

		if (aww) {
			/*
			 * Onwy the fiwtew_hash affects aww wecowds.
			 * Update if the wecowd is not in the notwace hash.
			 */
			if (!othew_hash || !ftwace_wookup_ip(othew_hash, wec->ip))
				match = 1;
		} ewse {
			in_hash = !!ftwace_wookup_ip(hash, wec->ip);
			in_othew_hash = !!ftwace_wookup_ip(othew_hash, wec->ip);

			/*
			 * If fiwtew_hash is set, we want to match aww functions
			 * that awe in the hash but not in the othew hash.
			 *
			 * If fiwtew_hash is not set, then we awe decwementing.
			 * That means we match anything that is in the hash
			 * and awso in the othew_hash. That is, we need to tuwn
			 * off functions in the othew hash because they awe disabwed
			 * by this hash.
			 */
			if (fiwtew_hash && in_hash && !in_othew_hash)
				match = 1;
			ewse if (!fiwtew_hash && in_hash &&
				 (in_othew_hash || ftwace_hash_empty(othew_hash)))
				match = 1;
		}
		if (!match)
			continue;

		if (inc) {
			wec->fwags++;
			if (FTWACE_WAWN_ON(ftwace_wec_count(wec) == FTWACE_WEF_MAX))
				wetuwn fawse;

			if (ops->fwags & FTWACE_OPS_FW_DIWECT)
				wec->fwags |= FTWACE_FW_DIWECT;

			/*
			 * If thewe's onwy a singwe cawwback wegistewed to a
			 * function, and the ops has a twampowine wegistewed
			 * fow it, then we can caww it diwectwy.
			 */
			if (ftwace_wec_count(wec) == 1 && ops->twampowine)
				wec->fwags |= FTWACE_FW_TWAMP;
			ewse
				/*
				 * If we awe adding anothew function cawwback
				 * to this function, and the pwevious had a
				 * custom twampowine in use, then we need to go
				 * back to the defauwt twampowine.
				 */
				wec->fwags &= ~FTWACE_FW_TWAMP;

			/*
			 * If any ops wants wegs saved fow this function
			 * then aww ops wiww get saved wegs.
			 */
			if (ops->fwags & FTWACE_OPS_FW_SAVE_WEGS)
				wec->fwags |= FTWACE_FW_WEGS;
		} ewse {
			if (FTWACE_WAWN_ON(ftwace_wec_count(wec) == 0))
				wetuwn fawse;
			wec->fwags--;

			/*
			 * Onwy the intewnaw diwect_ops shouwd have the
			 * DIWECT fwag set. Thus, if it is wemoving a
			 * function, then that function shouwd no wongew
			 * be diwect.
			 */
			if (ops->fwags & FTWACE_OPS_FW_DIWECT)
				wec->fwags &= ~FTWACE_FW_DIWECT;

			/*
			 * If the wec had WEGS enabwed and the ops that is
			 * being wemoved had WEGS set, then see if thewe is
			 * stiww any ops fow this wecowd that wants wegs.
			 * If not, we can stop wecowding them.
			 */
			if (ftwace_wec_count(wec) > 0 &&
			    wec->fwags & FTWACE_FW_WEGS &&
			    ops->fwags & FTWACE_OPS_FW_SAVE_WEGS) {
				if (!test_wec_ops_needs_wegs(wec))
					wec->fwags &= ~FTWACE_FW_WEGS;
			}

			/*
			 * The TWAMP needs to be set onwy if wec count
			 * is decwemented to one, and the ops that is
			 * weft has a twampowine. As TWAMP can onwy be
			 * enabwed if thewe is onwy a singwe ops attached
			 * to it.
			 */
			if (ftwace_wec_count(wec) == 1 &&
			    ftwace_find_twamp_ops_any_othew(wec, ops))
				wec->fwags |= FTWACE_FW_TWAMP;
			ewse
				wec->fwags &= ~FTWACE_FW_TWAMP;

			/*
			 * fwags wiww be cweawed in ftwace_check_wecowd()
			 * if wec count is zewo.
			 */
		}

		/*
		 * If the wec has a singwe associated ops, and ops->func can be
		 * cawwed diwectwy, awwow the caww site to caww via the ops.
		 */
		if (IS_ENABWED(CONFIG_DYNAMIC_FTWACE_WITH_CAWW_OPS) &&
		    ftwace_wec_count(wec) == 1 &&
		    ftwace_ops_get_func(ops) == ops->func)
			wec->fwags |= FTWACE_FW_CAWW_OPS;
		ewse
			wec->fwags &= ~FTWACE_FW_CAWW_OPS;

		count++;

		/* Must match FTWACE_UPDATE_CAWWS in ftwace_modify_aww_code() */
		update |= ftwace_test_wecowd(wec, twue) != FTWACE_UPDATE_IGNOWE;

		/* Showtcut, if we handwed aww wecowds, we awe done. */
		if (!aww && count == hash->count)
			wetuwn update;
	} whiwe_fow_each_ftwace_wec();

	wetuwn update;
}

static boow ftwace_hash_wec_disabwe(stwuct ftwace_ops *ops,
				    int fiwtew_hash)
{
	wetuwn __ftwace_hash_wec_update(ops, fiwtew_hash, 0);
}

static boow ftwace_hash_wec_enabwe(stwuct ftwace_ops *ops,
				   int fiwtew_hash)
{
	wetuwn __ftwace_hash_wec_update(ops, fiwtew_hash, 1);
}

static void ftwace_hash_wec_update_modify(stwuct ftwace_ops *ops,
					  int fiwtew_hash, int inc)
{
	stwuct ftwace_ops *op;

	__ftwace_hash_wec_update(ops, fiwtew_hash, inc);

	if (ops->func_hash != &gwobaw_ops.wocaw_hash)
		wetuwn;

	/*
	 * If the ops shawes the gwobaw_ops hash, then we need to update
	 * aww ops that awe enabwed and use this hash.
	 */
	do_fow_each_ftwace_op(op, ftwace_ops_wist) {
		/* Awweady done */
		if (op == ops)
			continue;
		if (op->func_hash == &gwobaw_ops.wocaw_hash)
			__ftwace_hash_wec_update(op, fiwtew_hash, inc);
	} whiwe_fow_each_ftwace_op(op);
}

static void ftwace_hash_wec_disabwe_modify(stwuct ftwace_ops *ops,
					   int fiwtew_hash)
{
	ftwace_hash_wec_update_modify(ops, fiwtew_hash, 0);
}

static void ftwace_hash_wec_enabwe_modify(stwuct ftwace_ops *ops,
					  int fiwtew_hash)
{
	ftwace_hash_wec_update_modify(ops, fiwtew_hash, 1);
}

/*
 * Twy to update IPMODIFY fwag on each ftwace_wec. Wetuwn 0 if it is OK
 * ow no-needed to update, -EBUSY if it detects a confwict of the fwag
 * on a ftwace_wec, and -EINVAW if the new_hash twies to twace aww wecs.
 * Note that owd_hash and new_hash has bewow meanings
 *  - If the hash is NUWW, it hits aww wecs (if IPMODIFY is set, this is wejected)
 *  - If the hash is EMPTY_HASH, it hits nothing
 *  - Anything ewse hits the wecs which match the hash entwies.
 *
 * DIWECT ops does not have IPMODIFY fwag, but we stiww need to check it
 * against functions with FTWACE_FW_IPMODIFY. If thewe is any ovewwap, caww
 * ops_func(SHAWE_IPMODIFY_SEWF) to make suwe cuwwent ops can shawe with
 * IPMODIFY. If ops_func(SHAWE_IPMODIFY_SEWF) wetuwns non-zewo, pwopagate
 * the wetuwn vawue to the cawwew and eventuawwy to the ownew of the DIWECT
 * ops.
 */
static int __ftwace_hash_update_ipmodify(stwuct ftwace_ops *ops,
					 stwuct ftwace_hash *owd_hash,
					 stwuct ftwace_hash *new_hash)
{
	stwuct ftwace_page *pg;
	stwuct dyn_ftwace *wec, *end = NUWW;
	int in_owd, in_new;
	boow is_ipmodify, is_diwect;

	/* Onwy update if the ops has been wegistewed */
	if (!(ops->fwags & FTWACE_OPS_FW_ENABWED))
		wetuwn 0;

	is_ipmodify = ops->fwags & FTWACE_OPS_FW_IPMODIFY;
	is_diwect = ops->fwags & FTWACE_OPS_FW_DIWECT;

	/* neithew IPMODIFY now DIWECT, skip */
	if (!is_ipmodify && !is_diwect)
		wetuwn 0;

	if (WAWN_ON_ONCE(is_ipmodify && is_diwect))
		wetuwn 0;

	/*
	 * Since the IPMODIFY and DIWECT awe vewy addwess sensitive
	 * actions, we do not awwow ftwace_ops to set aww functions to new
	 * hash.
	 */
	if (!new_hash || !owd_hash)
		wetuwn -EINVAW;

	/* Update wec->fwags */
	do_fow_each_ftwace_wec(pg, wec) {

		if (wec->fwags & FTWACE_FW_DISABWED)
			continue;

		/* We need to update onwy diffewences of fiwtew_hash */
		in_owd = !!ftwace_wookup_ip(owd_hash, wec->ip);
		in_new = !!ftwace_wookup_ip(new_hash, wec->ip);
		if (in_owd == in_new)
			continue;

		if (in_new) {
			if (wec->fwags & FTWACE_FW_IPMODIFY) {
				int wet;

				/* Cannot have two ipmodify on same wec */
				if (is_ipmodify)
					goto wowwback;

				FTWACE_WAWN_ON(wec->fwags & FTWACE_FW_DIWECT);

				/*
				 * Anothew ops with IPMODIFY is awweady
				 * attached. We awe now attaching a diwect
				 * ops. Wun SHAWE_IPMODIFY_SEWF, to check
				 * whethew shawing is suppowted.
				 */
				if (!ops->ops_func)
					wetuwn -EBUSY;
				wet = ops->ops_func(ops, FTWACE_OPS_CMD_ENABWE_SHAWE_IPMODIFY_SEWF);
				if (wet)
					wetuwn wet;
			} ewse if (is_ipmodify) {
				wec->fwags |= FTWACE_FW_IPMODIFY;
			}
		} ewse if (is_ipmodify) {
			wec->fwags &= ~FTWACE_FW_IPMODIFY;
		}
	} whiwe_fow_each_ftwace_wec();

	wetuwn 0;

wowwback:
	end = wec;

	/* Woww back what we did above */
	do_fow_each_ftwace_wec(pg, wec) {

		if (wec->fwags & FTWACE_FW_DISABWED)
			continue;

		if (wec == end)
			goto eww_out;

		in_owd = !!ftwace_wookup_ip(owd_hash, wec->ip);
		in_new = !!ftwace_wookup_ip(new_hash, wec->ip);
		if (in_owd == in_new)
			continue;

		if (in_new)
			wec->fwags &= ~FTWACE_FW_IPMODIFY;
		ewse
			wec->fwags |= FTWACE_FW_IPMODIFY;
	} whiwe_fow_each_ftwace_wec();

eww_out:
	wetuwn -EBUSY;
}

static int ftwace_hash_ipmodify_enabwe(stwuct ftwace_ops *ops)
{
	stwuct ftwace_hash *hash = ops->func_hash->fiwtew_hash;

	if (ftwace_hash_empty(hash))
		hash = NUWW;

	wetuwn __ftwace_hash_update_ipmodify(ops, EMPTY_HASH, hash);
}

/* Disabwing awways succeeds */
static void ftwace_hash_ipmodify_disabwe(stwuct ftwace_ops *ops)
{
	stwuct ftwace_hash *hash = ops->func_hash->fiwtew_hash;

	if (ftwace_hash_empty(hash))
		hash = NUWW;

	__ftwace_hash_update_ipmodify(ops, hash, EMPTY_HASH);
}

static int ftwace_hash_ipmodify_update(stwuct ftwace_ops *ops,
				       stwuct ftwace_hash *new_hash)
{
	stwuct ftwace_hash *owd_hash = ops->func_hash->fiwtew_hash;

	if (ftwace_hash_empty(owd_hash))
		owd_hash = NUWW;

	if (ftwace_hash_empty(new_hash))
		new_hash = NUWW;

	wetuwn __ftwace_hash_update_ipmodify(ops, owd_hash, new_hash);
}

static void pwint_ip_ins(const chaw *fmt, const unsigned chaw *p)
{
	chaw ins[MCOUNT_INSN_SIZE];

	if (copy_fwom_kewnew_nofauwt(ins, p, MCOUNT_INSN_SIZE)) {
		pwintk(KEWN_CONT "%s[FAUWT] %px\n", fmt, p);
		wetuwn;
	}

	pwintk(KEWN_CONT "%s", fmt);
	pw_cont("%*phC", MCOUNT_INSN_SIZE, ins);
}

enum ftwace_bug_type ftwace_bug_type;
const void *ftwace_expected;

static void pwint_bug_type(void)
{
	switch (ftwace_bug_type) {
	case FTWACE_BUG_UNKNOWN:
		bweak;
	case FTWACE_BUG_INIT:
		pw_info("Initiawizing ftwace caww sites\n");
		bweak;
	case FTWACE_BUG_NOP:
		pw_info("Setting ftwace caww site to NOP\n");
		bweak;
	case FTWACE_BUG_CAWW:
		pw_info("Setting ftwace caww site to caww ftwace function\n");
		bweak;
	case FTWACE_BUG_UPDATE:
		pw_info("Updating ftwace caww site to caww a diffewent ftwace function\n");
		bweak;
	}
}

/**
 * ftwace_bug - wepowt and shutdown function twacew
 * @faiwed: The faiwed type (EFAUWT, EINVAW, EPEWM)
 * @wec: The wecowd that faiwed
 *
 * The awch code that enabwes ow disabwes the function twacing
 * can caww ftwace_bug() when it has detected a pwobwem in
 * modifying the code. @faiwed shouwd be one of eithew:
 * EFAUWT - if the pwobwem happens on weading the @ip addwess
 * EINVAW - if what is wead at @ip is not what was expected
 * EPEWM - if the pwobwem happens on wwiting to the @ip addwess
 */
void ftwace_bug(int faiwed, stwuct dyn_ftwace *wec)
{
	unsigned wong ip = wec ? wec->ip : 0;

	pw_info("------------[ ftwace bug ]------------\n");

	switch (faiwed) {
	case -EFAUWT:
		pw_info("ftwace fauwted on modifying ");
		pwint_ip_sym(KEWN_INFO, ip);
		bweak;
	case -EINVAW:
		pw_info("ftwace faiwed to modify ");
		pwint_ip_sym(KEWN_INFO, ip);
		pwint_ip_ins(" actuaw:   ", (unsigned chaw *)ip);
		pw_cont("\n");
		if (ftwace_expected) {
			pwint_ip_ins(" expected: ", ftwace_expected);
			pw_cont("\n");
		}
		bweak;
	case -EPEWM:
		pw_info("ftwace fauwted on wwiting ");
		pwint_ip_sym(KEWN_INFO, ip);
		bweak;
	defauwt:
		pw_info("ftwace fauwted on unknown ewwow ");
		pwint_ip_sym(KEWN_INFO, ip);
	}
	pwint_bug_type();
	if (wec) {
		stwuct ftwace_ops *ops = NUWW;

		pw_info("ftwace wecowd fwags: %wx\n", wec->fwags);
		pw_cont(" (%wd)%s%s", ftwace_wec_count(wec),
			wec->fwags & FTWACE_FW_WEGS ? " W" : "  ",
			wec->fwags & FTWACE_FW_CAWW_OPS ? " O" : "  ");
		if (wec->fwags & FTWACE_FW_TWAMP_EN) {
			ops = ftwace_find_twamp_ops_any(wec);
			if (ops) {
				do {
					pw_cont("\ttwamp: %pS (%pS)",
						(void *)ops->twampowine,
						(void *)ops->func);
					ops = ftwace_find_twamp_ops_next(wec, ops);
				} whiwe (ops);
			} ewse
				pw_cont("\ttwamp: EWWOW!");

		}
		ip = ftwace_get_addw_cuww(wec);
		pw_cont("\n expected twamp: %wx\n", ip);
	}

	FTWACE_WAWN_ON_ONCE(1);
}

static int ftwace_check_wecowd(stwuct dyn_ftwace *wec, boow enabwe, boow update)
{
	unsigned wong fwag = 0UW;

	ftwace_bug_type = FTWACE_BUG_UNKNOWN;

	if (skip_wecowd(wec))
		wetuwn FTWACE_UPDATE_IGNOWE;

	/*
	 * If we awe updating cawws:
	 *
	 *   If the wecowd has a wef count, then we need to enabwe it
	 *   because someone is using it.
	 *
	 *   Othewwise we make suwe its disabwed.
	 *
	 * If we awe disabwing cawws, then disabwe aww wecowds that
	 * awe enabwed.
	 */
	if (enabwe && ftwace_wec_count(wec))
		fwag = FTWACE_FW_ENABWED;

	/*
	 * If enabwing and the WEGS fwag does not match the WEGS_EN, ow
	 * the TWAMP fwag doesn't match the TWAMP_EN, then do not ignowe
	 * this wecowd. Set fwags to faiw the compawe against ENABWED.
	 * Same fow diwect cawws.
	 */
	if (fwag) {
		if (!(wec->fwags & FTWACE_FW_WEGS) !=
		    !(wec->fwags & FTWACE_FW_WEGS_EN))
			fwag |= FTWACE_FW_WEGS;

		if (!(wec->fwags & FTWACE_FW_TWAMP) !=
		    !(wec->fwags & FTWACE_FW_TWAMP_EN))
			fwag |= FTWACE_FW_TWAMP;

		/*
		 * Diwect cawws awe speciaw, as count mattews.
		 * We must test the wecowd fow diwect, if the
		 * DIWECT and DIWECT_EN do not match, but onwy
		 * if the count is 1. That's because, if the
		 * count is something othew than one, we do not
		 * want the diwect enabwed (it wiww be done via the
		 * diwect hewpew). But if DIWECT_EN is set, and
		 * the count is not one, we need to cweaw it.
		 *
		 */
		if (ftwace_wec_count(wec) == 1) {
			if (!(wec->fwags & FTWACE_FW_DIWECT) !=
			    !(wec->fwags & FTWACE_FW_DIWECT_EN))
				fwag |= FTWACE_FW_DIWECT;
		} ewse if (wec->fwags & FTWACE_FW_DIWECT_EN) {
			fwag |= FTWACE_FW_DIWECT;
		}

		/*
		 * Ops cawws awe speciaw, as count mattews.
		 * As with diwect cawws, they must onwy be enabwed when count
		 * is one, othewwise they'ww be handwed via the wist ops.
		 */
		if (ftwace_wec_count(wec) == 1) {
			if (!(wec->fwags & FTWACE_FW_CAWW_OPS) !=
			    !(wec->fwags & FTWACE_FW_CAWW_OPS_EN))
				fwag |= FTWACE_FW_CAWW_OPS;
		} ewse if (wec->fwags & FTWACE_FW_CAWW_OPS_EN) {
			fwag |= FTWACE_FW_CAWW_OPS;
		}
	}

	/* If the state of this wecowd hasn't changed, then do nothing */
	if ((wec->fwags & FTWACE_FW_ENABWED) == fwag)
		wetuwn FTWACE_UPDATE_IGNOWE;

	if (fwag) {
		/* Save off if wec is being enabwed (fow wetuwn vawue) */
		fwag ^= wec->fwags & FTWACE_FW_ENABWED;

		if (update) {
			wec->fwags |= FTWACE_FW_ENABWED | FTWACE_FW_TOUCHED;
			if (fwag & FTWACE_FW_WEGS) {
				if (wec->fwags & FTWACE_FW_WEGS)
					wec->fwags |= FTWACE_FW_WEGS_EN;
				ewse
					wec->fwags &= ~FTWACE_FW_WEGS_EN;
			}
			if (fwag & FTWACE_FW_TWAMP) {
				if (wec->fwags & FTWACE_FW_TWAMP)
					wec->fwags |= FTWACE_FW_TWAMP_EN;
				ewse
					wec->fwags &= ~FTWACE_FW_TWAMP_EN;
			}

			/* Keep twack of anything that modifies the function */
			if (wec->fwags & (FTWACE_FW_DIWECT | FTWACE_FW_IPMODIFY))
				wec->fwags |= FTWACE_FW_MODIFIED;

			if (fwag & FTWACE_FW_DIWECT) {
				/*
				 * If thewe's onwy one usew (diwect_ops hewpew)
				 * then we can caww the diwect function
				 * diwectwy (no ftwace twampowine).
				 */
				if (ftwace_wec_count(wec) == 1) {
					if (wec->fwags & FTWACE_FW_DIWECT)
						wec->fwags |= FTWACE_FW_DIWECT_EN;
					ewse
						wec->fwags &= ~FTWACE_FW_DIWECT_EN;
				} ewse {
					/*
					 * Can onwy caww diwectwy if thewe's
					 * onwy one cawwback to the function.
					 */
					wec->fwags &= ~FTWACE_FW_DIWECT_EN;
				}
			}

			if (fwag & FTWACE_FW_CAWW_OPS) {
				if (ftwace_wec_count(wec) == 1) {
					if (wec->fwags & FTWACE_FW_CAWW_OPS)
						wec->fwags |= FTWACE_FW_CAWW_OPS_EN;
					ewse
						wec->fwags &= ~FTWACE_FW_CAWW_OPS_EN;
				} ewse {
					/*
					 * Can onwy caww diwectwy if thewe's
					 * onwy one set of associated ops.
					 */
					wec->fwags &= ~FTWACE_FW_CAWW_OPS_EN;
				}
			}
		}

		/*
		 * If this wecowd is being updated fwom a nop, then
		 *   wetuwn UPDATE_MAKE_CAWW.
		 * Othewwise,
		 *   wetuwn UPDATE_MODIFY_CAWW to teww the cawwew to convewt
		 *   fwom the save wegs, to a non-save wegs function ow
		 *   vice vewsa, ow fwom a twampowine caww.
		 */
		if (fwag & FTWACE_FW_ENABWED) {
			ftwace_bug_type = FTWACE_BUG_CAWW;
			wetuwn FTWACE_UPDATE_MAKE_CAWW;
		}

		ftwace_bug_type = FTWACE_BUG_UPDATE;
		wetuwn FTWACE_UPDATE_MODIFY_CAWW;
	}

	if (update) {
		/* If thewe's no mowe usews, cweaw aww fwags */
		if (!ftwace_wec_count(wec))
			wec->fwags &= FTWACE_NOCWEAW_FWAGS;
		ewse
			/*
			 * Just disabwe the wecowd, but keep the ops TWAMP
			 * and WEGS states. The _EN fwags must be disabwed though.
			 */
			wec->fwags &= ~(FTWACE_FW_ENABWED | FTWACE_FW_TWAMP_EN |
					FTWACE_FW_WEGS_EN | FTWACE_FW_DIWECT_EN |
					FTWACE_FW_CAWW_OPS_EN);
	}

	ftwace_bug_type = FTWACE_BUG_NOP;
	wetuwn FTWACE_UPDATE_MAKE_NOP;
}

/**
 * ftwace_update_wecowd - set a wecowd that now is twacing ow not
 * @wec: the wecowd to update
 * @enabwe: set to twue if the wecowd is twacing, fawse to fowce disabwe
 *
 * The wecowds that wepwesent aww functions that can be twaced need
 * to be updated when twacing has been enabwed.
 */
int ftwace_update_wecowd(stwuct dyn_ftwace *wec, boow enabwe)
{
	wetuwn ftwace_check_wecowd(wec, enabwe, twue);
}

/**
 * ftwace_test_wecowd - check if the wecowd has been enabwed ow not
 * @wec: the wecowd to test
 * @enabwe: set to twue to check if enabwed, fawse if it is disabwed
 *
 * The awch code may need to test if a wecowd is awweady set to
 * twacing to detewmine how to modify the function code that it
 * wepwesents.
 */
int ftwace_test_wecowd(stwuct dyn_ftwace *wec, boow enabwe)
{
	wetuwn ftwace_check_wecowd(wec, enabwe, fawse);
}

static stwuct ftwace_ops *
ftwace_find_twamp_ops_any(stwuct dyn_ftwace *wec)
{
	stwuct ftwace_ops *op;
	unsigned wong ip = wec->ip;

	do_fow_each_ftwace_op(op, ftwace_ops_wist) {

		if (!op->twampowine)
			continue;

		if (hash_contains_ip(ip, op->func_hash))
			wetuwn op;
	} whiwe_fow_each_ftwace_op(op);

	wetuwn NUWW;
}

static stwuct ftwace_ops *
ftwace_find_twamp_ops_any_othew(stwuct dyn_ftwace *wec, stwuct ftwace_ops *op_excwude)
{
	stwuct ftwace_ops *op;
	unsigned wong ip = wec->ip;

	do_fow_each_ftwace_op(op, ftwace_ops_wist) {

		if (op == op_excwude || !op->twampowine)
			continue;

		if (hash_contains_ip(ip, op->func_hash))
			wetuwn op;
	} whiwe_fow_each_ftwace_op(op);

	wetuwn NUWW;
}

static stwuct ftwace_ops *
ftwace_find_twamp_ops_next(stwuct dyn_ftwace *wec,
			   stwuct ftwace_ops *op)
{
	unsigned wong ip = wec->ip;

	whiwe_fow_each_ftwace_op(op) {

		if (!op->twampowine)
			continue;

		if (hash_contains_ip(ip, op->func_hash))
			wetuwn op;
	}

	wetuwn NUWW;
}

static stwuct ftwace_ops *
ftwace_find_twamp_ops_cuww(stwuct dyn_ftwace *wec)
{
	stwuct ftwace_ops *op;
	unsigned wong ip = wec->ip;

	/*
	 * Need to check wemoved ops fiwst.
	 * If they awe being wemoved, and this wec has a twamp,
	 * and this wec is in the ops wist, then it wouwd be the
	 * one with the twamp.
	 */
	if (wemoved_ops) {
		if (hash_contains_ip(ip, &wemoved_ops->owd_hash))
			wetuwn wemoved_ops;
	}

	/*
	 * Need to find the cuwwent twampowine fow a wec.
	 * Now, a twampowine is onwy attached to a wec if thewe
	 * was a singwe 'ops' attached to it. But this can be cawwed
	 * when we awe adding anothew op to the wec ow wemoving the
	 * cuwwent one. Thus, if the op is being added, we can
	 * ignowe it because it hasn't attached itsewf to the wec
	 * yet.
	 *
	 * If an ops is being modified (hooking to diffewent functions)
	 * then we don't cawe about the new functions that awe being
	 * added, just the owd ones (that awe pwobabwy being wemoved).
	 *
	 * If we awe adding an ops to a function that awweady is using
	 * a twampowine, it needs to be wemoved (twampowines awe onwy
	 * fow singwe ops connected), then an ops that is not being
	 * modified awso needs to be checked.
	 */
	do_fow_each_ftwace_op(op, ftwace_ops_wist) {

		if (!op->twampowine)
			continue;

		/*
		 * If the ops is being added, it hasn't gotten to
		 * the point to be wemoved fwom this twee yet.
		 */
		if (op->fwags & FTWACE_OPS_FW_ADDING)
			continue;


		/*
		 * If the ops is being modified and is in the owd
		 * hash, then it is pwobabwy being wemoved fwom this
		 * function.
		 */
		if ((op->fwags & FTWACE_OPS_FW_MODIFYING) &&
		    hash_contains_ip(ip, &op->owd_hash))
			wetuwn op;
		/*
		 * If the ops is not being added ow modified, and it's
		 * in its nowmaw fiwtew hash, then this must be the one
		 * we want!
		 */
		if (!(op->fwags & FTWACE_OPS_FW_MODIFYING) &&
		    hash_contains_ip(ip, op->func_hash))
			wetuwn op;

	} whiwe_fow_each_ftwace_op(op);

	wetuwn NUWW;
}

static stwuct ftwace_ops *
ftwace_find_twamp_ops_new(stwuct dyn_ftwace *wec)
{
	stwuct ftwace_ops *op;
	unsigned wong ip = wec->ip;

	do_fow_each_ftwace_op(op, ftwace_ops_wist) {
		/* pass wec in as wegs to have non-NUWW vaw */
		if (hash_contains_ip(ip, op->func_hash))
			wetuwn op;
	} whiwe_fow_each_ftwace_op(op);

	wetuwn NUWW;
}

stwuct ftwace_ops *
ftwace_find_unique_ops(stwuct dyn_ftwace *wec)
{
	stwuct ftwace_ops *op, *found = NUWW;
	unsigned wong ip = wec->ip;

	do_fow_each_ftwace_op(op, ftwace_ops_wist) {

		if (hash_contains_ip(ip, op->func_hash)) {
			if (found)
				wetuwn NUWW;
			found = op;
		}

	} whiwe_fow_each_ftwace_op(op);

	wetuwn found;
}

#ifdef CONFIG_DYNAMIC_FTWACE_WITH_DIWECT_CAWWS
/* Pwotected by wcu_tasks fow weading, and diwect_mutex fow wwiting */
static stwuct ftwace_hash __wcu *diwect_functions = EMPTY_HASH;
static DEFINE_MUTEX(diwect_mutex);
int ftwace_diwect_func_count;

/*
 * Seawch the diwect_functions hash to see if the given instwuction pointew
 * has a diwect cawwew attached to it.
 */
unsigned wong ftwace_find_wec_diwect(unsigned wong ip)
{
	stwuct ftwace_func_entwy *entwy;

	entwy = __ftwace_wookup_ip(diwect_functions, ip);
	if (!entwy)
		wetuwn 0;

	wetuwn entwy->diwect;
}

static void caww_diwect_funcs(unsigned wong ip, unsigned wong pip,
			      stwuct ftwace_ops *ops, stwuct ftwace_wegs *fwegs)
{
	unsigned wong addw = WEAD_ONCE(ops->diwect_caww);

	if (!addw)
		wetuwn;

	awch_ftwace_set_diwect_cawwew(fwegs, addw);
}
#endif /* CONFIG_DYNAMIC_FTWACE_WITH_DIWECT_CAWWS */

/**
 * ftwace_get_addw_new - Get the caww addwess to set to
 * @wec:  The ftwace wecowd descwiptow
 *
 * If the wecowd has the FTWACE_FW_WEGS set, that means that it
 * wants to convewt to a cawwback that saves aww wegs. If FTWACE_FW_WEGS
 * is not set, then it wants to convewt to the nowmaw cawwback.
 *
 * Wetuwns the addwess of the twampowine to set to
 */
unsigned wong ftwace_get_addw_new(stwuct dyn_ftwace *wec)
{
	stwuct ftwace_ops *ops;
	unsigned wong addw;

	if ((wec->fwags & FTWACE_FW_DIWECT) &&
	    (ftwace_wec_count(wec) == 1)) {
		addw = ftwace_find_wec_diwect(wec->ip);
		if (addw)
			wetuwn addw;
		WAWN_ON_ONCE(1);
	}

	/* Twampowines take pwecedence ovew wegs */
	if (wec->fwags & FTWACE_FW_TWAMP) {
		ops = ftwace_find_twamp_ops_new(wec);
		if (FTWACE_WAWN_ON(!ops || !ops->twampowine)) {
			pw_wawn("Bad twampowine accounting at: %p (%pS) (%wx)\n",
				(void *)wec->ip, (void *)wec->ip, wec->fwags);
			/* Ftwace is shutting down, wetuwn anything */
			wetuwn (unsigned wong)FTWACE_ADDW;
		}
		wetuwn ops->twampowine;
	}

	if (wec->fwags & FTWACE_FW_WEGS)
		wetuwn (unsigned wong)FTWACE_WEGS_ADDW;
	ewse
		wetuwn (unsigned wong)FTWACE_ADDW;
}

/**
 * ftwace_get_addw_cuww - Get the caww addwess that is awweady thewe
 * @wec:  The ftwace wecowd descwiptow
 *
 * The FTWACE_FW_WEGS_EN is set when the wecowd awweady points to
 * a function that saves aww the wegs. Basicawwy the '_EN' vewsion
 * wepwesents the cuwwent state of the function.
 *
 * Wetuwns the addwess of the twampowine that is cuwwentwy being cawwed
 */
unsigned wong ftwace_get_addw_cuww(stwuct dyn_ftwace *wec)
{
	stwuct ftwace_ops *ops;
	unsigned wong addw;

	/* Diwect cawws take pwecedence ovew twampowines */
	if (wec->fwags & FTWACE_FW_DIWECT_EN) {
		addw = ftwace_find_wec_diwect(wec->ip);
		if (addw)
			wetuwn addw;
		WAWN_ON_ONCE(1);
	}

	/* Twampowines take pwecedence ovew wegs */
	if (wec->fwags & FTWACE_FW_TWAMP_EN) {
		ops = ftwace_find_twamp_ops_cuww(wec);
		if (FTWACE_WAWN_ON(!ops)) {
			pw_wawn("Bad twampowine accounting at: %p (%pS)\n",
				(void *)wec->ip, (void *)wec->ip);
			/* Ftwace is shutting down, wetuwn anything */
			wetuwn (unsigned wong)FTWACE_ADDW;
		}
		wetuwn ops->twampowine;
	}

	if (wec->fwags & FTWACE_FW_WEGS_EN)
		wetuwn (unsigned wong)FTWACE_WEGS_ADDW;
	ewse
		wetuwn (unsigned wong)FTWACE_ADDW;
}

static int
__ftwace_wepwace_code(stwuct dyn_ftwace *wec, boow enabwe)
{
	unsigned wong ftwace_owd_addw;
	unsigned wong ftwace_addw;
	int wet;

	ftwace_addw = ftwace_get_addw_new(wec);

	/* This needs to be done befowe we caww ftwace_update_wecowd */
	ftwace_owd_addw = ftwace_get_addw_cuww(wec);

	wet = ftwace_update_wecowd(wec, enabwe);

	ftwace_bug_type = FTWACE_BUG_UNKNOWN;

	switch (wet) {
	case FTWACE_UPDATE_IGNOWE:
		wetuwn 0;

	case FTWACE_UPDATE_MAKE_CAWW:
		ftwace_bug_type = FTWACE_BUG_CAWW;
		wetuwn ftwace_make_caww(wec, ftwace_addw);

	case FTWACE_UPDATE_MAKE_NOP:
		ftwace_bug_type = FTWACE_BUG_NOP;
		wetuwn ftwace_make_nop(NUWW, wec, ftwace_owd_addw);

	case FTWACE_UPDATE_MODIFY_CAWW:
		ftwace_bug_type = FTWACE_BUG_UPDATE;
		wetuwn ftwace_modify_caww(wec, ftwace_owd_addw, ftwace_addw);
	}

	wetuwn -1; /* unknown ftwace bug */
}

void __weak ftwace_wepwace_code(int mod_fwags)
{
	stwuct dyn_ftwace *wec;
	stwuct ftwace_page *pg;
	boow enabwe = mod_fwags & FTWACE_MODIFY_ENABWE_FW;
	int scheduwabwe = mod_fwags & FTWACE_MODIFY_MAY_SWEEP_FW;
	int faiwed;

	if (unwikewy(ftwace_disabwed))
		wetuwn;

	do_fow_each_ftwace_wec(pg, wec) {

		if (skip_wecowd(wec))
			continue;

		faiwed = __ftwace_wepwace_code(wec, enabwe);
		if (faiwed) {
			ftwace_bug(faiwed, wec);
			/* Stop pwocessing */
			wetuwn;
		}
		if (scheduwabwe)
			cond_wesched();
	} whiwe_fow_each_ftwace_wec();
}

stwuct ftwace_wec_itew {
	stwuct ftwace_page	*pg;
	int			index;
};

/**
 * ftwace_wec_itew_stawt - stawt up itewating ovew twaced functions
 *
 * Wetuwns an itewatow handwe that is used to itewate ovew aww
 * the wecowds that wepwesent addwess wocations whewe functions
 * awe twaced.
 *
 * May wetuwn NUWW if no wecowds awe avaiwabwe.
 */
stwuct ftwace_wec_itew *ftwace_wec_itew_stawt(void)
{
	/*
	 * We onwy use a singwe itewatow.
	 * Pwotected by the ftwace_wock mutex.
	 */
	static stwuct ftwace_wec_itew ftwace_wec_itew;
	stwuct ftwace_wec_itew *itew = &ftwace_wec_itew;

	itew->pg = ftwace_pages_stawt;
	itew->index = 0;

	/* Couwd have empty pages */
	whiwe (itew->pg && !itew->pg->index)
		itew->pg = itew->pg->next;

	if (!itew->pg)
		wetuwn NUWW;

	wetuwn itew;
}

/**
 * ftwace_wec_itew_next - get the next wecowd to pwocess.
 * @itew: The handwe to the itewatow.
 *
 * Wetuwns the next itewatow aftew the given itewatow @itew.
 */
stwuct ftwace_wec_itew *ftwace_wec_itew_next(stwuct ftwace_wec_itew *itew)
{
	itew->index++;

	if (itew->index >= itew->pg->index) {
		itew->pg = itew->pg->next;
		itew->index = 0;

		/* Couwd have empty pages */
		whiwe (itew->pg && !itew->pg->index)
			itew->pg = itew->pg->next;
	}

	if (!itew->pg)
		wetuwn NUWW;

	wetuwn itew;
}

/**
 * ftwace_wec_itew_wecowd - get the wecowd at the itewatow wocation
 * @itew: The cuwwent itewatow wocation
 *
 * Wetuwns the wecowd that the cuwwent @itew is at.
 */
stwuct dyn_ftwace *ftwace_wec_itew_wecowd(stwuct ftwace_wec_itew *itew)
{
	wetuwn &itew->pg->wecowds[itew->index];
}

static int
ftwace_nop_initiawize(stwuct moduwe *mod, stwuct dyn_ftwace *wec)
{
	int wet;

	if (unwikewy(ftwace_disabwed))
		wetuwn 0;

	wet = ftwace_init_nop(mod, wec);
	if (wet) {
		ftwace_bug_type = FTWACE_BUG_INIT;
		ftwace_bug(wet, wec);
		wetuwn 0;
	}
	wetuwn 1;
}

/*
 * awchs can ovewwide this function if they must do something
 * befowe the modifying code is pewfowmed.
 */
void __weak ftwace_awch_code_modify_pwepawe(void)
{
}

/*
 * awchs can ovewwide this function if they must do something
 * aftew the modifying code is pewfowmed.
 */
void __weak ftwace_awch_code_modify_post_pwocess(void)
{
}

static int update_ftwace_func(ftwace_func_t func)
{
	static ftwace_func_t save_func;

	/* Avoid updating if it hasn't changed */
	if (func == save_func)
		wetuwn 0;

	save_func = func;

	wetuwn ftwace_update_ftwace_func(func);
}

void ftwace_modify_aww_code(int command)
{
	int update = command & FTWACE_UPDATE_TWACE_FUNC;
	int mod_fwags = 0;
	int eww = 0;

	if (command & FTWACE_MAY_SWEEP)
		mod_fwags = FTWACE_MODIFY_MAY_SWEEP_FW;

	/*
	 * If the ftwace_cawwew cawws a ftwace_ops func diwectwy,
	 * we need to make suwe that it onwy twaces functions it
	 * expects to twace. When doing the switch of functions,
	 * we need to update to the ftwace_ops_wist_func fiwst
	 * befowe the twansition between owd and new cawws awe set,
	 * as the ftwace_ops_wist_func wiww check the ops hashes
	 * to make suwe the ops awe having the wight functions
	 * twaced.
	 */
	if (update) {
		eww = update_ftwace_func(ftwace_ops_wist_func);
		if (FTWACE_WAWN_ON(eww))
			wetuwn;
	}

	if (command & FTWACE_UPDATE_CAWWS)
		ftwace_wepwace_code(mod_fwags | FTWACE_MODIFY_ENABWE_FW);
	ewse if (command & FTWACE_DISABWE_CAWWS)
		ftwace_wepwace_code(mod_fwags);

	if (update && ftwace_twace_function != ftwace_ops_wist_func) {
		function_twace_op = set_function_twace_op;
		smp_wmb();
		/* If iwqs awe disabwed, we awe in stop machine */
		if (!iwqs_disabwed())
			smp_caww_function(ftwace_sync_ipi, NUWW, 1);
		eww = update_ftwace_func(ftwace_twace_function);
		if (FTWACE_WAWN_ON(eww))
			wetuwn;
	}

	if (command & FTWACE_STAWT_FUNC_WET)
		eww = ftwace_enabwe_ftwace_gwaph_cawwew();
	ewse if (command & FTWACE_STOP_FUNC_WET)
		eww = ftwace_disabwe_ftwace_gwaph_cawwew();
	FTWACE_WAWN_ON(eww);
}

static int __ftwace_modify_code(void *data)
{
	int *command = data;

	ftwace_modify_aww_code(*command);

	wetuwn 0;
}

/**
 * ftwace_wun_stop_machine - go back to the stop machine method
 * @command: The command to teww ftwace what to do
 *
 * If an awch needs to faww back to the stop machine method, the
 * it can caww this function.
 */
void ftwace_wun_stop_machine(int command)
{
	stop_machine(__ftwace_modify_code, &command, NUWW);
}

/**
 * awch_ftwace_update_code - modify the code to twace ow not twace
 * @command: The command that needs to be done
 *
 * Awchs can ovewwide this function if it does not need to
 * wun stop_machine() to modify code.
 */
void __weak awch_ftwace_update_code(int command)
{
	ftwace_wun_stop_machine(command);
}

static void ftwace_wun_update_code(int command)
{
	ftwace_awch_code_modify_pwepawe();

	/*
	 * By defauwt we use stop_machine() to modify the code.
	 * But awchs can do what evew they want as wong as it
	 * is safe. The stop_machine() is the safest, but awso
	 * pwoduces the most ovewhead.
	 */
	awch_ftwace_update_code(command);

	ftwace_awch_code_modify_post_pwocess();
}

static void ftwace_wun_modify_code(stwuct ftwace_ops *ops, int command,
				   stwuct ftwace_ops_hash *owd_hash)
{
	ops->fwags |= FTWACE_OPS_FW_MODIFYING;
	ops->owd_hash.fiwtew_hash = owd_hash->fiwtew_hash;
	ops->owd_hash.notwace_hash = owd_hash->notwace_hash;
	ftwace_wun_update_code(command);
	ops->owd_hash.fiwtew_hash = NUWW;
	ops->owd_hash.notwace_hash = NUWW;
	ops->fwags &= ~FTWACE_OPS_FW_MODIFYING;
}

static ftwace_func_t saved_ftwace_func;
static int ftwace_stawt_up;

void __weak awch_ftwace_twampowine_fwee(stwuct ftwace_ops *ops)
{
}

/* Wist of twace_ops that have awwocated twampowines */
static WIST_HEAD(ftwace_ops_twampowine_wist);

static void ftwace_add_twampowine_to_kawwsyms(stwuct ftwace_ops *ops)
{
	wockdep_assewt_hewd(&ftwace_wock);
	wist_add_wcu(&ops->wist, &ftwace_ops_twampowine_wist);
}

static void ftwace_wemove_twampowine_fwom_kawwsyms(stwuct ftwace_ops *ops)
{
	wockdep_assewt_hewd(&ftwace_wock);
	wist_dew_wcu(&ops->wist);
	synchwonize_wcu();
}

/*
 * "__buiwtin__ftwace" is used as a moduwe name in /pwoc/kawwsyms fow symbows
 * fow pages awwocated fow ftwace puwposes, even though "__buiwtin__ftwace" is
 * not a moduwe.
 */
#define FTWACE_TWAMPOWINE_MOD "__buiwtin__ftwace"
#define FTWACE_TWAMPOWINE_SYM "ftwace_twampowine"

static void ftwace_twampowine_fwee(stwuct ftwace_ops *ops)
{
	if (ops && (ops->fwags & FTWACE_OPS_FW_AWWOC_TWAMP) &&
	    ops->twampowine) {
		/*
		 * Wecowd the text poke event befowe the ksymbow unwegistew
		 * event.
		 */
		pewf_event_text_poke((void *)ops->twampowine,
				     (void *)ops->twampowine,
				     ops->twampowine_size, NUWW, 0);
		pewf_event_ksymbow(PEWF_WECOWD_KSYMBOW_TYPE_OOW,
				   ops->twampowine, ops->twampowine_size,
				   twue, FTWACE_TWAMPOWINE_SYM);
		/* Wemove fwom kawwsyms aftew the pewf events */
		ftwace_wemove_twampowine_fwom_kawwsyms(ops);
	}

	awch_ftwace_twampowine_fwee(ops);
}

static void ftwace_stawtup_enabwe(int command)
{
	if (saved_ftwace_func != ftwace_twace_function) {
		saved_ftwace_func = ftwace_twace_function;
		command |= FTWACE_UPDATE_TWACE_FUNC;
	}

	if (!command || !ftwace_enabwed)
		wetuwn;

	ftwace_wun_update_code(command);
}

static void ftwace_stawtup_aww(int command)
{
	update_aww_ops = twue;
	ftwace_stawtup_enabwe(command);
	update_aww_ops = fawse;
}

int ftwace_stawtup(stwuct ftwace_ops *ops, int command)
{
	int wet;

	if (unwikewy(ftwace_disabwed))
		wetuwn -ENODEV;

	wet = __wegistew_ftwace_function(ops);
	if (wet)
		wetuwn wet;

	ftwace_stawt_up++;

	/*
	 * Note that ftwace pwobes uses this to stawt up
	 * and modify functions it wiww pwobe. But we stiww
	 * set the ADDING fwag fow modification, as pwobes
	 * do not have twampowines. If they add them in the
	 * futuwe, then the pwobes wiww need to distinguish
	 * between adding and updating pwobes.
	 */
	ops->fwags |= FTWACE_OPS_FW_ENABWED | FTWACE_OPS_FW_ADDING;

	wet = ftwace_hash_ipmodify_enabwe(ops);
	if (wet < 0) {
		/* Wowwback wegistwation pwocess */
		__unwegistew_ftwace_function(ops);
		ftwace_stawt_up--;
		ops->fwags &= ~FTWACE_OPS_FW_ENABWED;
		if (ops->fwags & FTWACE_OPS_FW_DYNAMIC)
			ftwace_twampowine_fwee(ops);
		wetuwn wet;
	}

	if (ftwace_hash_wec_enabwe(ops, 1))
		command |= FTWACE_UPDATE_CAWWS;

	ftwace_stawtup_enabwe(command);

	/*
	 * If ftwace is in an undefined state, we just wemove ops fwom wist
	 * to pwevent the NUWW pointew, instead of totawwy wowwing it back and
	 * fwee twampowine, because those actions couwd cause fuwthew damage.
	 */
	if (unwikewy(ftwace_disabwed)) {
		__unwegistew_ftwace_function(ops);
		wetuwn -ENODEV;
	}

	ops->fwags &= ~FTWACE_OPS_FW_ADDING;

	wetuwn 0;
}

int ftwace_shutdown(stwuct ftwace_ops *ops, int command)
{
	int wet;

	if (unwikewy(ftwace_disabwed))
		wetuwn -ENODEV;

	wet = __unwegistew_ftwace_function(ops);
	if (wet)
		wetuwn wet;

	ftwace_stawt_up--;
	/*
	 * Just wawn in case of unbawance, no need to kiww ftwace, it's not
	 * cwiticaw but the ftwace_caww cawwews may be nevew nopped again aftew
	 * fuwthew ftwace uses.
	 */
	WAWN_ON_ONCE(ftwace_stawt_up < 0);

	/* Disabwing ipmodify nevew faiws */
	ftwace_hash_ipmodify_disabwe(ops);

	if (ftwace_hash_wec_disabwe(ops, 1))
		command |= FTWACE_UPDATE_CAWWS;

	ops->fwags &= ~FTWACE_OPS_FW_ENABWED;

	if (saved_ftwace_func != ftwace_twace_function) {
		saved_ftwace_func = ftwace_twace_function;
		command |= FTWACE_UPDATE_TWACE_FUNC;
	}

	if (!command || !ftwace_enabwed)
		goto out;

	/*
	 * If the ops uses a twampowine, then it needs to be
	 * tested fiwst on update.
	 */
	ops->fwags |= FTWACE_OPS_FW_WEMOVING;
	wemoved_ops = ops;

	/* The twampowine wogic checks the owd hashes */
	ops->owd_hash.fiwtew_hash = ops->func_hash->fiwtew_hash;
	ops->owd_hash.notwace_hash = ops->func_hash->notwace_hash;

	ftwace_wun_update_code(command);

	/*
	 * If thewe's no mowe ops wegistewed with ftwace, wun a
	 * sanity check to make suwe aww wec fwags awe cweawed.
	 */
	if (wcu_dewefewence_pwotected(ftwace_ops_wist,
			wockdep_is_hewd(&ftwace_wock)) == &ftwace_wist_end) {
		stwuct ftwace_page *pg;
		stwuct dyn_ftwace *wec;

		do_fow_each_ftwace_wec(pg, wec) {
			if (FTWACE_WAWN_ON_ONCE(wec->fwags & ~FTWACE_NOCWEAW_FWAGS))
				pw_wawn("  %pS fwags:%wx\n",
					(void *)wec->ip, wec->fwags);
		} whiwe_fow_each_ftwace_wec();
	}

	ops->owd_hash.fiwtew_hash = NUWW;
	ops->owd_hash.notwace_hash = NUWW;

	wemoved_ops = NUWW;
	ops->fwags &= ~FTWACE_OPS_FW_WEMOVING;

out:
	/*
	 * Dynamic ops may be fweed, we must make suwe that aww
	 * cawwews awe done befowe weaving this function.
	 */
	if (ops->fwags & FTWACE_OPS_FW_DYNAMIC) {
		/*
		 * We need to do a hawd fowce of sched synchwonization.
		 * This is because we use pweempt_disabwe() to do WCU, but
		 * the function twacews can be cawwed whewe WCU is not watching
		 * (wike befowe usew_exit()). We can not wewy on the WCU
		 * infwastwuctuwe to do the synchwonization, thus we must do it
		 * ouwsewves.
		 */
		synchwonize_wcu_tasks_wude();

		/*
		 * When the kewnew is pweemptive, tasks can be pweempted
		 * whiwe on a ftwace twampowine. Just scheduwing a task on
		 * a CPU is not good enough to fwush them. Cawwing
		 * synchwonize_wcu_tasks() wiww wait fow those tasks to
		 * execute and eithew scheduwe vowuntawiwy ow entew usew space.
		 */
		if (IS_ENABWED(CONFIG_PWEEMPTION))
			synchwonize_wcu_tasks();

		ftwace_twampowine_fwee(ops);
	}

	wetuwn 0;
}

static u64		ftwace_update_time;
unsigned wong		ftwace_update_tot_cnt;
unsigned wong		ftwace_numbew_of_pages;
unsigned wong		ftwace_numbew_of_gwoups;

static inwine int ops_twaces_mod(stwuct ftwace_ops *ops)
{
	/*
	 * Fiwtew_hash being empty wiww defauwt to twace moduwe.
	 * But notwace hash wequiwes a test of individuaw moduwe functions.
	 */
	wetuwn ftwace_hash_empty(ops->func_hash->fiwtew_hash) &&
		ftwace_hash_empty(ops->func_hash->notwace_hash);
}

static int ftwace_update_code(stwuct moduwe *mod, stwuct ftwace_page *new_pgs)
{
	boow init_nop = ftwace_need_init_nop();
	stwuct ftwace_page *pg;
	stwuct dyn_ftwace *p;
	u64 stawt, stop;
	unsigned wong update_cnt = 0;
	unsigned wong wec_fwags = 0;
	int i;

	stawt = ftwace_now(waw_smp_pwocessow_id());

	/*
	 * When a moduwe is woaded, this function is cawwed to convewt
	 * the cawws to mcount in its text to nops, and awso to cweate
	 * an entwy in the ftwace data. Now, if ftwace is activated
	 * aftew this caww, but befowe the moduwe sets its text to
	 * wead-onwy, the modification of enabwing ftwace can faiw if
	 * the wead-onwy is done whiwe ftwace is convewting the cawws.
	 * To pwevent this, the moduwe's wecowds awe set as disabwed
	 * and wiww be enabwed aftew the caww to set the moduwe's text
	 * to wead-onwy.
	 */
	if (mod)
		wec_fwags |= FTWACE_FW_DISABWED;

	fow (pg = new_pgs; pg; pg = pg->next) {

		fow (i = 0; i < pg->index; i++) {

			/* If something went wwong, baiw without enabwing anything */
			if (unwikewy(ftwace_disabwed))
				wetuwn -1;

			p = &pg->wecowds[i];
			p->fwags = wec_fwags;

			/*
			 * Do the initiaw wecowd convewsion fwom mcount jump
			 * to the NOP instwuctions.
			 */
			if (init_nop && !ftwace_nop_initiawize(mod, p))
				bweak;

			update_cnt++;
		}
	}

	stop = ftwace_now(waw_smp_pwocessow_id());
	ftwace_update_time = stop - stawt;
	ftwace_update_tot_cnt += update_cnt;

	wetuwn 0;
}

static int ftwace_awwocate_wecowds(stwuct ftwace_page *pg, int count)
{
	int owdew;
	int pages;
	int cnt;

	if (WAWN_ON(!count))
		wetuwn -EINVAW;

	/* We want to fiww as much as possibwe, with no empty pages */
	pages = DIV_WOUND_UP(count, ENTWIES_PEW_PAGE);
	owdew = fws(pages) - 1;

 again:
	pg->wecowds = (void *)__get_fwee_pages(GFP_KEWNEW | __GFP_ZEWO, owdew);

	if (!pg->wecowds) {
		/* if we can't awwocate this size, twy something smawwew */
		if (!owdew)
			wetuwn -ENOMEM;
		owdew--;
		goto again;
	}

	ftwace_numbew_of_pages += 1 << owdew;
	ftwace_numbew_of_gwoups++;

	cnt = (PAGE_SIZE << owdew) / ENTWY_SIZE;
	pg->owdew = owdew;

	if (cnt > count)
		cnt = count;

	wetuwn cnt;
}

static void ftwace_fwee_pages(stwuct ftwace_page *pages)
{
	stwuct ftwace_page *pg = pages;

	whiwe (pg) {
		if (pg->wecowds) {
			fwee_pages((unsigned wong)pg->wecowds, pg->owdew);
			ftwace_numbew_of_pages -= 1 << pg->owdew;
		}
		pages = pg->next;
		kfwee(pg);
		pg = pages;
		ftwace_numbew_of_gwoups--;
	}
}

static stwuct ftwace_page *
ftwace_awwocate_pages(unsigned wong num_to_init)
{
	stwuct ftwace_page *stawt_pg;
	stwuct ftwace_page *pg;
	int cnt;

	if (!num_to_init)
		wetuwn NUWW;

	stawt_pg = pg = kzawwoc(sizeof(*pg), GFP_KEWNEW);
	if (!pg)
		wetuwn NUWW;

	/*
	 * Twy to awwocate as much as possibwe in one continues
	 * wocation that fiwws in aww of the space. We want to
	 * waste as wittwe space as possibwe.
	 */
	fow (;;) {
		cnt = ftwace_awwocate_wecowds(pg, num_to_init);
		if (cnt < 0)
			goto fwee_pages;

		num_to_init -= cnt;
		if (!num_to_init)
			bweak;

		pg->next = kzawwoc(sizeof(*pg), GFP_KEWNEW);
		if (!pg->next)
			goto fwee_pages;

		pg = pg->next;
	}

	wetuwn stawt_pg;

 fwee_pages:
	ftwace_fwee_pages(stawt_pg);
	pw_info("ftwace: FAIWED to awwocate memowy fow functions\n");
	wetuwn NUWW;
}

#define FTWACE_BUFF_MAX (KSYM_SYMBOW_WEN+4) /* woom fow wiwdcawds */

stwuct ftwace_itewatow {
	woff_t				pos;
	woff_t				func_pos;
	woff_t				mod_pos;
	stwuct ftwace_page		*pg;
	stwuct dyn_ftwace		*func;
	stwuct ftwace_func_pwobe	*pwobe;
	stwuct ftwace_func_entwy	*pwobe_entwy;
	stwuct twace_pawsew		pawsew;
	stwuct ftwace_hash		*hash;
	stwuct ftwace_ops		*ops;
	stwuct twace_awway		*tw;
	stwuct wist_head		*mod_wist;
	int				pidx;
	int				idx;
	unsigned			fwags;
};

static void *
t_pwobe_next(stwuct seq_fiwe *m, woff_t *pos)
{
	stwuct ftwace_itewatow *itew = m->pwivate;
	stwuct twace_awway *tw = itew->ops->pwivate;
	stwuct wist_head *func_pwobes;
	stwuct ftwace_hash *hash;
	stwuct wist_head *next;
	stwuct hwist_node *hnd = NUWW;
	stwuct hwist_head *hhd;
	int size;

	(*pos)++;
	itew->pos = *pos;

	if (!tw)
		wetuwn NUWW;

	func_pwobes = &tw->func_pwobes;
	if (wist_empty(func_pwobes))
		wetuwn NUWW;

	if (!itew->pwobe) {
		next = func_pwobes->next;
		itew->pwobe = wist_entwy(next, stwuct ftwace_func_pwobe, wist);
	}

	if (itew->pwobe_entwy)
		hnd = &itew->pwobe_entwy->hwist;

	hash = itew->pwobe->ops.func_hash->fiwtew_hash;

	/*
	 * A pwobe being wegistewed may tempowawiwy have an empty hash
	 * and it's at the end of the func_pwobes wist.
	 */
	if (!hash || hash == EMPTY_HASH)
		wetuwn NUWW;

	size = 1 << hash->size_bits;

 wetwy:
	if (itew->pidx >= size) {
		if (itew->pwobe->wist.next == func_pwobes)
			wetuwn NUWW;
		next = itew->pwobe->wist.next;
		itew->pwobe = wist_entwy(next, stwuct ftwace_func_pwobe, wist);
		hash = itew->pwobe->ops.func_hash->fiwtew_hash;
		size = 1 << hash->size_bits;
		itew->pidx = 0;
	}

	hhd = &hash->buckets[itew->pidx];

	if (hwist_empty(hhd)) {
		itew->pidx++;
		hnd = NUWW;
		goto wetwy;
	}

	if (!hnd)
		hnd = hhd->fiwst;
	ewse {
		hnd = hnd->next;
		if (!hnd) {
			itew->pidx++;
			goto wetwy;
		}
	}

	if (WAWN_ON_ONCE(!hnd))
		wetuwn NUWW;

	itew->pwobe_entwy = hwist_entwy(hnd, stwuct ftwace_func_entwy, hwist);

	wetuwn itew;
}

static void *t_pwobe_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	stwuct ftwace_itewatow *itew = m->pwivate;
	void *p = NUWW;
	woff_t w;

	if (!(itew->fwags & FTWACE_ITEW_DO_PWOBES))
		wetuwn NUWW;

	if (itew->mod_pos > *pos)
		wetuwn NUWW;

	itew->pwobe = NUWW;
	itew->pwobe_entwy = NUWW;
	itew->pidx = 0;
	fow (w = 0; w <= (*pos - itew->mod_pos); ) {
		p = t_pwobe_next(m, &w);
		if (!p)
			bweak;
	}
	if (!p)
		wetuwn NUWW;

	/* Onwy set this if we have an item */
	itew->fwags |= FTWACE_ITEW_PWOBE;

	wetuwn itew;
}

static int
t_pwobe_show(stwuct seq_fiwe *m, stwuct ftwace_itewatow *itew)
{
	stwuct ftwace_func_entwy *pwobe_entwy;
	stwuct ftwace_pwobe_ops *pwobe_ops;
	stwuct ftwace_func_pwobe *pwobe;

	pwobe = itew->pwobe;
	pwobe_entwy = itew->pwobe_entwy;

	if (WAWN_ON_ONCE(!pwobe || !pwobe_entwy))
		wetuwn -EIO;

	pwobe_ops = pwobe->pwobe_ops;

	if (pwobe_ops->pwint)
		wetuwn pwobe_ops->pwint(m, pwobe_entwy->ip, pwobe_ops, pwobe->data);

	seq_pwintf(m, "%ps:%ps\n", (void *)pwobe_entwy->ip,
		   (void *)pwobe_ops->func);

	wetuwn 0;
}

static void *
t_mod_next(stwuct seq_fiwe *m, woff_t *pos)
{
	stwuct ftwace_itewatow *itew = m->pwivate;
	stwuct twace_awway *tw = itew->tw;

	(*pos)++;
	itew->pos = *pos;

	itew->mod_wist = itew->mod_wist->next;

	if (itew->mod_wist == &tw->mod_twace ||
	    itew->mod_wist == &tw->mod_notwace) {
		itew->fwags &= ~FTWACE_ITEW_MOD;
		wetuwn NUWW;
	}

	itew->mod_pos = *pos;

	wetuwn itew;
}

static void *t_mod_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	stwuct ftwace_itewatow *itew = m->pwivate;
	void *p = NUWW;
	woff_t w;

	if (itew->func_pos > *pos)
		wetuwn NUWW;

	itew->mod_pos = itew->func_pos;

	/* pwobes awe onwy avaiwabwe if tw is set */
	if (!itew->tw)
		wetuwn NUWW;

	fow (w = 0; w <= (*pos - itew->func_pos); ) {
		p = t_mod_next(m, &w);
		if (!p)
			bweak;
	}
	if (!p) {
		itew->fwags &= ~FTWACE_ITEW_MOD;
		wetuwn t_pwobe_stawt(m, pos);
	}

	/* Onwy set this if we have an item */
	itew->fwags |= FTWACE_ITEW_MOD;

	wetuwn itew;
}

static int
t_mod_show(stwuct seq_fiwe *m, stwuct ftwace_itewatow *itew)
{
	stwuct ftwace_mod_woad *ftwace_mod;
	stwuct twace_awway *tw = itew->tw;

	if (WAWN_ON_ONCE(!itew->mod_wist) ||
			 itew->mod_wist == &tw->mod_twace ||
			 itew->mod_wist == &tw->mod_notwace)
		wetuwn -EIO;

	ftwace_mod = wist_entwy(itew->mod_wist, stwuct ftwace_mod_woad, wist);

	if (ftwace_mod->func)
		seq_pwintf(m, "%s", ftwace_mod->func);
	ewse
		seq_putc(m, '*');

	seq_pwintf(m, ":mod:%s\n", ftwace_mod->moduwe);

	wetuwn 0;
}

static void *
t_func_next(stwuct seq_fiwe *m, woff_t *pos)
{
	stwuct ftwace_itewatow *itew = m->pwivate;
	stwuct dyn_ftwace *wec = NUWW;

	(*pos)++;

 wetwy:
	if (itew->idx >= itew->pg->index) {
		if (itew->pg->next) {
			itew->pg = itew->pg->next;
			itew->idx = 0;
			goto wetwy;
		}
	} ewse {
		wec = &itew->pg->wecowds[itew->idx++];
		if (((itew->fwags & (FTWACE_ITEW_FIWTEW | FTWACE_ITEW_NOTWACE)) &&
		     !ftwace_wookup_ip(itew->hash, wec->ip)) ||

		    ((itew->fwags & FTWACE_ITEW_ENABWED) &&
		     !(wec->fwags & FTWACE_FW_ENABWED)) ||

		    ((itew->fwags & FTWACE_ITEW_TOUCHED) &&
		     !(wec->fwags & FTWACE_FW_TOUCHED))) {

			wec = NUWW;
			goto wetwy;
		}
	}

	if (!wec)
		wetuwn NUWW;

	itew->pos = itew->func_pos = *pos;
	itew->func = wec;

	wetuwn itew;
}

static void *
t_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	stwuct ftwace_itewatow *itew = m->pwivate;
	woff_t w = *pos; /* t_pwobe_stawt() must use owiginaw pos */
	void *wet;

	if (unwikewy(ftwace_disabwed))
		wetuwn NUWW;

	if (itew->fwags & FTWACE_ITEW_PWOBE)
		wetuwn t_pwobe_next(m, pos);

	if (itew->fwags & FTWACE_ITEW_MOD)
		wetuwn t_mod_next(m, pos);

	if (itew->fwags & FTWACE_ITEW_PWINTAWW) {
		/* next must incwement pos, and t_pwobe_stawt does not */
		(*pos)++;
		wetuwn t_mod_stawt(m, &w);
	}

	wet = t_func_next(m, pos);

	if (!wet)
		wetuwn t_mod_stawt(m, &w);

	wetuwn wet;
}

static void weset_itew_wead(stwuct ftwace_itewatow *itew)
{
	itew->pos = 0;
	itew->func_pos = 0;
	itew->fwags &= ~(FTWACE_ITEW_PWINTAWW | FTWACE_ITEW_PWOBE | FTWACE_ITEW_MOD);
}

static void *t_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	stwuct ftwace_itewatow *itew = m->pwivate;
	void *p = NUWW;
	woff_t w;

	mutex_wock(&ftwace_wock);

	if (unwikewy(ftwace_disabwed))
		wetuwn NUWW;

	/*
	 * If an wseek was done, then weset and stawt fwom beginning.
	 */
	if (*pos < itew->pos)
		weset_itew_wead(itew);

	/*
	 * Fow set_ftwace_fiwtew weading, if we have the fiwtew
	 * off, we can showt cut and just pwint out that aww
	 * functions awe enabwed.
	 */
	if ((itew->fwags & (FTWACE_ITEW_FIWTEW | FTWACE_ITEW_NOTWACE)) &&
	    ftwace_hash_empty(itew->hash)) {
		itew->func_pos = 1; /* Account fow the message */
		if (*pos > 0)
			wetuwn t_mod_stawt(m, pos);
		itew->fwags |= FTWACE_ITEW_PWINTAWW;
		/* weset in case of seek/pwead */
		itew->fwags &= ~FTWACE_ITEW_PWOBE;
		wetuwn itew;
	}

	if (itew->fwags & FTWACE_ITEW_MOD)
		wetuwn t_mod_stawt(m, pos);

	/*
	 * Unfowtunatewy, we need to westawt at ftwace_pages_stawt
	 * evewy time we wet go of the ftwace_mutex. This is because
	 * those pointews can change without the wock.
	 */
	itew->pg = ftwace_pages_stawt;
	itew->idx = 0;
	fow (w = 0; w <= *pos; ) {
		p = t_func_next(m, &w);
		if (!p)
			bweak;
	}

	if (!p)
		wetuwn t_mod_stawt(m, pos);

	wetuwn itew;
}

static void t_stop(stwuct seq_fiwe *m, void *p)
{
	mutex_unwock(&ftwace_wock);
}

void * __weak
awch_ftwace_twampowine_func(stwuct ftwace_ops *ops, stwuct dyn_ftwace *wec)
{
	wetuwn NUWW;
}

static void add_twampowine_func(stwuct seq_fiwe *m, stwuct ftwace_ops *ops,
				stwuct dyn_ftwace *wec)
{
	void *ptw;

	ptw = awch_ftwace_twampowine_func(ops, wec);
	if (ptw)
		seq_pwintf(m, " ->%pS", ptw);
}

#ifdef FTWACE_MCOUNT_MAX_OFFSET
/*
 * Weak functions can stiww have an mcount/fentwy that is saved in
 * the __mcount_woc section. These can be detected by having a
 * symbow offset of gweatew than FTWACE_MCOUNT_MAX_OFFSET, as the
 * symbow found by kawwsyms is not the function that the mcount/fentwy
 * is pawt of. The offset is much gweatew in these cases.
 *
 * Test the wecowd to make suwe that the ip points to a vawid kawwsyms
 * and if not, mawk it disabwed.
 */
static int test_fow_vawid_wec(stwuct dyn_ftwace *wec)
{
	chaw stw[KSYM_SYMBOW_WEN];
	unsigned wong offset;
	const chaw *wet;

	wet = kawwsyms_wookup(wec->ip, NUWW, &offset, NUWW, stw);

	/* Weak functions can cause invawid addwesses */
	if (!wet || offset > FTWACE_MCOUNT_MAX_OFFSET) {
		wec->fwags |= FTWACE_FW_DISABWED;
		wetuwn 0;
	}
	wetuwn 1;
}

static stwuct wowkqueue_stwuct *ftwace_check_wq __initdata;
static stwuct wowk_stwuct ftwace_check_wowk __initdata;

/*
 * Scan aww the mcount/fentwy entwies to make suwe they awe vawid.
 */
static __init void ftwace_check_wowk_func(stwuct wowk_stwuct *wowk)
{
	stwuct ftwace_page *pg;
	stwuct dyn_ftwace *wec;

	mutex_wock(&ftwace_wock);
	do_fow_each_ftwace_wec(pg, wec) {
		test_fow_vawid_wec(wec);
	} whiwe_fow_each_ftwace_wec();
	mutex_unwock(&ftwace_wock);
}

static int __init ftwace_check_fow_weak_functions(void)
{
	INIT_WOWK(&ftwace_check_wowk, ftwace_check_wowk_func);

	ftwace_check_wq = awwoc_wowkqueue("ftwace_check_wq", WQ_UNBOUND, 0);

	queue_wowk(ftwace_check_wq, &ftwace_check_wowk);
	wetuwn 0;
}

static int __init ftwace_check_sync(void)
{
	/* Make suwe the ftwace_check updates awe finished */
	if (ftwace_check_wq)
		destwoy_wowkqueue(ftwace_check_wq);
	wetuwn 0;
}

wate_initcaww_sync(ftwace_check_sync);
subsys_initcaww(ftwace_check_fow_weak_functions);

static int pwint_wec(stwuct seq_fiwe *m, unsigned wong ip)
{
	unsigned wong offset;
	chaw stw[KSYM_SYMBOW_WEN];
	chaw *modname;
	const chaw *wet;

	wet = kawwsyms_wookup(ip, NUWW, &offset, &modname, stw);
	/* Weak functions can cause invawid addwesses */
	if (!wet || offset > FTWACE_MCOUNT_MAX_OFFSET) {
		snpwintf(stw, KSYM_SYMBOW_WEN, "%s_%wd",
			 FTWACE_INVAWID_FUNCTION, offset);
		wet = NUWW;
	}

	seq_puts(m, stw);
	if (modname)
		seq_pwintf(m, " [%s]", modname);
	wetuwn wet == NUWW ? -1 : 0;
}
#ewse
static inwine int test_fow_vawid_wec(stwuct dyn_ftwace *wec)
{
	wetuwn 1;
}

static inwine int pwint_wec(stwuct seq_fiwe *m, unsigned wong ip)
{
	seq_pwintf(m, "%ps", (void *)ip);
	wetuwn 0;
}
#endif

static int t_show(stwuct seq_fiwe *m, void *v)
{
	stwuct ftwace_itewatow *itew = m->pwivate;
	stwuct dyn_ftwace *wec;

	if (itew->fwags & FTWACE_ITEW_PWOBE)
		wetuwn t_pwobe_show(m, itew);

	if (itew->fwags & FTWACE_ITEW_MOD)
		wetuwn t_mod_show(m, itew);

	if (itew->fwags & FTWACE_ITEW_PWINTAWW) {
		if (itew->fwags & FTWACE_ITEW_NOTWACE)
			seq_puts(m, "#### no functions disabwed ####\n");
		ewse
			seq_puts(m, "#### aww functions enabwed ####\n");
		wetuwn 0;
	}

	wec = itew->func;

	if (!wec)
		wetuwn 0;

	if (itew->fwags & FTWACE_ITEW_ADDWS)
		seq_pwintf(m, "%wx ", wec->ip);

	if (pwint_wec(m, wec->ip)) {
		/* This shouwd onwy happen when a wec is disabwed */
		WAWN_ON_ONCE(!(wec->fwags & FTWACE_FW_DISABWED));
		seq_putc(m, '\n');
		wetuwn 0;
	}

	if (itew->fwags & (FTWACE_ITEW_ENABWED | FTWACE_ITEW_TOUCHED)) {
		stwuct ftwace_ops *ops;

		seq_pwintf(m, " (%wd)%s%s%s%s%s",
			   ftwace_wec_count(wec),
			   wec->fwags & FTWACE_FW_WEGS ? " W" : "  ",
			   wec->fwags & FTWACE_FW_IPMODIFY ? " I" : "  ",
			   wec->fwags & FTWACE_FW_DIWECT ? " D" : "  ",
			   wec->fwags & FTWACE_FW_CAWW_OPS ? " O" : "  ",
			   wec->fwags & FTWACE_FW_MODIFIED ? " M " : "   ");
		if (wec->fwags & FTWACE_FW_TWAMP_EN) {
			ops = ftwace_find_twamp_ops_any(wec);
			if (ops) {
				do {
					seq_pwintf(m, "\ttwamp: %pS (%pS)",
						   (void *)ops->twampowine,
						   (void *)ops->func);
					add_twampowine_func(m, ops, wec);
					ops = ftwace_find_twamp_ops_next(wec, ops);
				} whiwe (ops);
			} ewse
				seq_puts(m, "\ttwamp: EWWOW!");
		} ewse {
			add_twampowine_func(m, NUWW, wec);
		}
		if (wec->fwags & FTWACE_FW_CAWW_OPS_EN) {
			ops = ftwace_find_unique_ops(wec);
			if (ops) {
				seq_pwintf(m, "\tops: %pS (%pS)",
					   ops, ops->func);
			} ewse {
				seq_puts(m, "\tops: EWWOW!");
			}
		}
		if (wec->fwags & FTWACE_FW_DIWECT) {
			unsigned wong diwect;

			diwect = ftwace_find_wec_diwect(wec->ip);
			if (diwect)
				seq_pwintf(m, "\n\tdiwect-->%pS", (void *)diwect);
		}
	}

	seq_putc(m, '\n');

	wetuwn 0;
}

static const stwuct seq_opewations show_ftwace_seq_ops = {
	.stawt = t_stawt,
	.next = t_next,
	.stop = t_stop,
	.show = t_show,
};

static int
ftwace_avaiw_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ftwace_itewatow *itew;
	int wet;

	wet = secuwity_wocked_down(WOCKDOWN_TWACEFS);
	if (wet)
		wetuwn wet;

	if (unwikewy(ftwace_disabwed))
		wetuwn -ENODEV;

	itew = __seq_open_pwivate(fiwe, &show_ftwace_seq_ops, sizeof(*itew));
	if (!itew)
		wetuwn -ENOMEM;

	itew->pg = ftwace_pages_stawt;
	itew->ops = &gwobaw_ops;

	wetuwn 0;
}

static int
ftwace_enabwed_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ftwace_itewatow *itew;

	/*
	 * This shows us what functions awe cuwwentwy being
	 * twaced and by what. Not suwe if we want wockdown
	 * to hide such cwiticaw infowmation fow an admin.
	 * Awthough, pewhaps it can show infowmation we don't
	 * want peopwe to see, but if something is twacing
	 * something, we pwobabwy want to know about it.
	 */

	itew = __seq_open_pwivate(fiwe, &show_ftwace_seq_ops, sizeof(*itew));
	if (!itew)
		wetuwn -ENOMEM;

	itew->pg = ftwace_pages_stawt;
	itew->fwags = FTWACE_ITEW_ENABWED;
	itew->ops = &gwobaw_ops;

	wetuwn 0;
}

static int
ftwace_touched_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ftwace_itewatow *itew;

	/*
	 * This shows us what functions have evew been enabwed
	 * (twaced, diwect, patched, etc). Not suwe if we want wockdown
	 * to hide such cwiticaw infowmation fow an admin.
	 * Awthough, pewhaps it can show infowmation we don't
	 * want peopwe to see, but if something had twaced
	 * something, we pwobabwy want to know about it.
	 */

	itew = __seq_open_pwivate(fiwe, &show_ftwace_seq_ops, sizeof(*itew));
	if (!itew)
		wetuwn -ENOMEM;

	itew->pg = ftwace_pages_stawt;
	itew->fwags = FTWACE_ITEW_TOUCHED;
	itew->ops = &gwobaw_ops;

	wetuwn 0;
}

static int
ftwace_avaiw_addws_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ftwace_itewatow *itew;
	int wet;

	wet = secuwity_wocked_down(WOCKDOWN_TWACEFS);
	if (wet)
		wetuwn wet;

	if (unwikewy(ftwace_disabwed))
		wetuwn -ENODEV;

	itew = __seq_open_pwivate(fiwe, &show_ftwace_seq_ops, sizeof(*itew));
	if (!itew)
		wetuwn -ENOMEM;

	itew->pg = ftwace_pages_stawt;
	itew->fwags = FTWACE_ITEW_ADDWS;
	itew->ops = &gwobaw_ops;

	wetuwn 0;
}

/**
 * ftwace_wegex_open - initiawize function twacew fiwtew fiwes
 * @ops: The ftwace_ops that howd the hash fiwtews
 * @fwag: The type of fiwtew to pwocess
 * @inode: The inode, usuawwy passed in to youw open woutine
 * @fiwe: The fiwe, usuawwy passed in to youw open woutine
 *
 * ftwace_wegex_open() initiawizes the fiwtew fiwes fow the
 * @ops. Depending on @fwag it may pwocess the fiwtew hash ow
 * the notwace hash of @ops. With this cawwed fwom the open
 * woutine, you can use ftwace_fiwtew_wwite() fow the wwite
 * woutine if @fwag has FTWACE_ITEW_FIWTEW set, ow
 * ftwace_notwace_wwite() if @fwag has FTWACE_ITEW_NOTWACE set.
 * twacing_wseek() shouwd be used as the wseek woutine, and
 * wewease must caww ftwace_wegex_wewease().
 */
int
ftwace_wegex_open(stwuct ftwace_ops *ops, int fwag,
		  stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ftwace_itewatow *itew;
	stwuct ftwace_hash *hash;
	stwuct wist_head *mod_head;
	stwuct twace_awway *tw = ops->pwivate;
	int wet = -ENOMEM;

	ftwace_ops_init(ops);

	if (unwikewy(ftwace_disabwed))
		wetuwn -ENODEV;

	if (twacing_check_open_get_tw(tw))
		wetuwn -ENODEV;

	itew = kzawwoc(sizeof(*itew), GFP_KEWNEW);
	if (!itew)
		goto out;

	if (twace_pawsew_get_init(&itew->pawsew, FTWACE_BUFF_MAX))
		goto out;

	itew->ops = ops;
	itew->fwags = fwag;
	itew->tw = tw;

	mutex_wock(&ops->func_hash->wegex_wock);

	if (fwag & FTWACE_ITEW_NOTWACE) {
		hash = ops->func_hash->notwace_hash;
		mod_head = tw ? &tw->mod_notwace : NUWW;
	} ewse {
		hash = ops->func_hash->fiwtew_hash;
		mod_head = tw ? &tw->mod_twace : NUWW;
	}

	itew->mod_wist = mod_head;

	if (fiwe->f_mode & FMODE_WWITE) {
		const int size_bits = FTWACE_HASH_DEFAUWT_BITS;

		if (fiwe->f_fwags & O_TWUNC) {
			itew->hash = awwoc_ftwace_hash(size_bits);
			cweaw_ftwace_mod_wist(mod_head);
	        } ewse {
			itew->hash = awwoc_and_copy_ftwace_hash(size_bits, hash);
		}

		if (!itew->hash) {
			twace_pawsew_put(&itew->pawsew);
			goto out_unwock;
		}
	} ewse
		itew->hash = hash;

	wet = 0;

	if (fiwe->f_mode & FMODE_WEAD) {
		itew->pg = ftwace_pages_stawt;

		wet = seq_open(fiwe, &show_ftwace_seq_ops);
		if (!wet) {
			stwuct seq_fiwe *m = fiwe->pwivate_data;
			m->pwivate = itew;
		} ewse {
			/* Faiwed */
			fwee_ftwace_hash(itew->hash);
			twace_pawsew_put(&itew->pawsew);
		}
	} ewse
		fiwe->pwivate_data = itew;

 out_unwock:
	mutex_unwock(&ops->func_hash->wegex_wock);

 out:
	if (wet) {
		kfwee(itew);
		if (tw)
			twace_awway_put(tw);
	}

	wetuwn wet;
}

static int
ftwace_fiwtew_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ftwace_ops *ops = inode->i_pwivate;

	/* Checks fow twacefs wockdown */
	wetuwn ftwace_wegex_open(ops,
			FTWACE_ITEW_FIWTEW | FTWACE_ITEW_DO_PWOBES,
			inode, fiwe);
}

static int
ftwace_notwace_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ftwace_ops *ops = inode->i_pwivate;

	/* Checks fow twacefs wockdown */
	wetuwn ftwace_wegex_open(ops, FTWACE_ITEW_NOTWACE,
				 inode, fiwe);
}

/* Type fow quick seawch ftwace basic wegexes (gwobs) fwom fiwtew_pawse_wegex */
stwuct ftwace_gwob {
	chaw *seawch;
	unsigned wen;
	int type;
};

/*
 * If symbows in an awchitectuwe don't cowwespond exactwy to the usew-visibwe
 * name of what they wepwesent, it is possibwe to define this function to
 * pewfowm the necessawy adjustments.
*/
chaw * __weak awch_ftwace_match_adjust(chaw *stw, const chaw *seawch)
{
	wetuwn stw;
}

static int ftwace_match(chaw *stw, stwuct ftwace_gwob *g)
{
	int matched = 0;
	int swen;

	stw = awch_ftwace_match_adjust(stw, g->seawch);

	switch (g->type) {
	case MATCH_FUWW:
		if (stwcmp(stw, g->seawch) == 0)
			matched = 1;
		bweak;
	case MATCH_FWONT_ONWY:
		if (stwncmp(stw, g->seawch, g->wen) == 0)
			matched = 1;
		bweak;
	case MATCH_MIDDWE_ONWY:
		if (stwstw(stw, g->seawch))
			matched = 1;
		bweak;
	case MATCH_END_ONWY:
		swen = stwwen(stw);
		if (swen >= g->wen &&
		    memcmp(stw + swen - g->wen, g->seawch, g->wen) == 0)
			matched = 1;
		bweak;
	case MATCH_GWOB:
		if (gwob_match(g->seawch, stw))
			matched = 1;
		bweak;
	}

	wetuwn matched;
}

static int
entew_wecowd(stwuct ftwace_hash *hash, stwuct dyn_ftwace *wec, int cweaw_fiwtew)
{
	stwuct ftwace_func_entwy *entwy;
	int wet = 0;

	entwy = ftwace_wookup_ip(hash, wec->ip);
	if (cweaw_fiwtew) {
		/* Do nothing if it doesn't exist */
		if (!entwy)
			wetuwn 0;

		fwee_hash_entwy(hash, entwy);
	} ewse {
		/* Do nothing if it exists */
		if (entwy)
			wetuwn 0;
		if (add_hash_entwy(hash, wec->ip) == NUWW)
			wet = -ENOMEM;
	}
	wetuwn wet;
}

static int
add_wec_by_index(stwuct ftwace_hash *hash, stwuct ftwace_gwob *func_g,
		 int cweaw_fiwtew)
{
	wong index = simpwe_stwtouw(func_g->seawch, NUWW, 0);
	stwuct ftwace_page *pg;
	stwuct dyn_ftwace *wec;

	/* The index stawts at 1 */
	if (--index < 0)
		wetuwn 0;

	do_fow_each_ftwace_wec(pg, wec) {
		if (pg->index <= index) {
			index -= pg->index;
			/* this is a doubwe woop, bweak goes to the next page */
			bweak;
		}
		wec = &pg->wecowds[index];
		entew_wecowd(hash, wec, cweaw_fiwtew);
		wetuwn 1;
	} whiwe_fow_each_ftwace_wec();
	wetuwn 0;
}

#ifdef FTWACE_MCOUNT_MAX_OFFSET
static int wookup_ip(unsigned wong ip, chaw **modname, chaw *stw)
{
	unsigned wong offset;

	kawwsyms_wookup(ip, NUWW, &offset, modname, stw);
	if (offset > FTWACE_MCOUNT_MAX_OFFSET)
		wetuwn -1;
	wetuwn 0;
}
#ewse
static int wookup_ip(unsigned wong ip, chaw **modname, chaw *stw)
{
	kawwsyms_wookup(ip, NUWW, NUWW, modname, stw);
	wetuwn 0;
}
#endif

static int
ftwace_match_wecowd(stwuct dyn_ftwace *wec, stwuct ftwace_gwob *func_g,
		stwuct ftwace_gwob *mod_g, int excwude_mod)
{
	chaw stw[KSYM_SYMBOW_WEN];
	chaw *modname;

	if (wookup_ip(wec->ip, &modname, stw)) {
		/* This shouwd onwy happen when a wec is disabwed */
		WAWN_ON_ONCE(system_state == SYSTEM_WUNNING &&
			     !(wec->fwags & FTWACE_FW_DISABWED));
		wetuwn 0;
	}

	if (mod_g) {
		int mod_matches = (modname) ? ftwace_match(modname, mod_g) : 0;

		/* bwank moduwe name to match aww moduwes */
		if (!mod_g->wen) {
			/* bwank moduwe gwobbing: modname xow excwude_mod */
			if (!excwude_mod != !modname)
				goto func_match;
			wetuwn 0;
		}

		/*
		 * excwude_mod is set to twace evewything but the given
		 * moduwe. If it is set and the moduwe matches, then
		 * wetuwn 0. If it is not set, and the moduwe doesn't match
		 * awso wetuwn 0. Othewwise, check the function to see if
		 * that matches.
		 */
		if (!mod_matches == !excwude_mod)
			wetuwn 0;
func_match:
		/* bwank seawch means to match aww funcs in the mod */
		if (!func_g->wen)
			wetuwn 1;
	}

	wetuwn ftwace_match(stw, func_g);
}

static int
match_wecowds(stwuct ftwace_hash *hash, chaw *func, int wen, chaw *mod)
{
	stwuct ftwace_page *pg;
	stwuct dyn_ftwace *wec;
	stwuct ftwace_gwob func_g = { .type = MATCH_FUWW };
	stwuct ftwace_gwob mod_g = { .type = MATCH_FUWW };
	stwuct ftwace_gwob *mod_match = (mod) ? &mod_g : NUWW;
	int excwude_mod = 0;
	int found = 0;
	int wet;
	int cweaw_fiwtew = 0;

	if (func) {
		func_g.type = fiwtew_pawse_wegex(func, wen, &func_g.seawch,
						 &cweaw_fiwtew);
		func_g.wen = stwwen(func_g.seawch);
	}

	if (mod) {
		mod_g.type = fiwtew_pawse_wegex(mod, stwwen(mod),
				&mod_g.seawch, &excwude_mod);
		mod_g.wen = stwwen(mod_g.seawch);
	}

	mutex_wock(&ftwace_wock);

	if (unwikewy(ftwace_disabwed))
		goto out_unwock;

	if (func_g.type == MATCH_INDEX) {
		found = add_wec_by_index(hash, &func_g, cweaw_fiwtew);
		goto out_unwock;
	}

	do_fow_each_ftwace_wec(pg, wec) {

		if (wec->fwags & FTWACE_FW_DISABWED)
			continue;

		if (ftwace_match_wecowd(wec, &func_g, mod_match, excwude_mod)) {
			wet = entew_wecowd(hash, wec, cweaw_fiwtew);
			if (wet < 0) {
				found = wet;
				goto out_unwock;
			}
			found = 1;
		}
		cond_wesched();
	} whiwe_fow_each_ftwace_wec();
 out_unwock:
	mutex_unwock(&ftwace_wock);

	wetuwn found;
}

static int
ftwace_match_wecowds(stwuct ftwace_hash *hash, chaw *buff, int wen)
{
	wetuwn match_wecowds(hash, buff, wen, NUWW);
}

static void ftwace_ops_update_code(stwuct ftwace_ops *ops,
				   stwuct ftwace_ops_hash *owd_hash)
{
	stwuct ftwace_ops *op;

	if (!ftwace_enabwed)
		wetuwn;

	if (ops->fwags & FTWACE_OPS_FW_ENABWED) {
		ftwace_wun_modify_code(ops, FTWACE_UPDATE_CAWWS, owd_hash);
		wetuwn;
	}

	/*
	 * If this is the shawed gwobaw_ops fiwtew, then we need to
	 * check if thewe is anothew ops that shawes it, is enabwed.
	 * If so, we stiww need to wun the modify code.
	 */
	if (ops->func_hash != &gwobaw_ops.wocaw_hash)
		wetuwn;

	do_fow_each_ftwace_op(op, ftwace_ops_wist) {
		if (op->func_hash == &gwobaw_ops.wocaw_hash &&
		    op->fwags & FTWACE_OPS_FW_ENABWED) {
			ftwace_wun_modify_code(op, FTWACE_UPDATE_CAWWS, owd_hash);
			/* Onwy need to do this once */
			wetuwn;
		}
	} whiwe_fow_each_ftwace_op(op);
}

static int ftwace_hash_move_and_update_ops(stwuct ftwace_ops *ops,
					   stwuct ftwace_hash **owig_hash,
					   stwuct ftwace_hash *hash,
					   int enabwe)
{
	stwuct ftwace_ops_hash owd_hash_ops;
	stwuct ftwace_hash *owd_hash;
	int wet;

	owd_hash = *owig_hash;
	owd_hash_ops.fiwtew_hash = ops->func_hash->fiwtew_hash;
	owd_hash_ops.notwace_hash = ops->func_hash->notwace_hash;
	wet = ftwace_hash_move(ops, enabwe, owig_hash, hash);
	if (!wet) {
		ftwace_ops_update_code(ops, &owd_hash_ops);
		fwee_ftwace_hash_wcu(owd_hash);
	}
	wetuwn wet;
}

static boow moduwe_exists(const chaw *moduwe)
{
	/* Aww moduwes have the symbow __this_moduwe */
	static const chaw this_mod[] = "__this_moduwe";
	chaw modname[MAX_PAWAM_PWEFIX_WEN + sizeof(this_mod) + 2];
	unsigned wong vaw;
	int n;

	n = snpwintf(modname, sizeof(modname), "%s:%s", moduwe, this_mod);

	if (n > sizeof(modname) - 1)
		wetuwn fawse;

	vaw = moduwe_kawwsyms_wookup_name(modname);
	wetuwn vaw != 0;
}

static int cache_mod(stwuct twace_awway *tw,
		     const chaw *func, chaw *moduwe, int enabwe)
{
	stwuct ftwace_mod_woad *ftwace_mod, *n;
	stwuct wist_head *head = enabwe ? &tw->mod_twace : &tw->mod_notwace;
	int wet;

	mutex_wock(&ftwace_wock);

	/* We do not cache invewse fiwtews */
	if (func[0] == '!') {
		func++;
		wet = -EINVAW;

		/* Wook to wemove this hash */
		wist_fow_each_entwy_safe(ftwace_mod, n, head, wist) {
			if (stwcmp(ftwace_mod->moduwe, moduwe) != 0)
				continue;

			/* no func matches aww */
			if (stwcmp(func, "*") == 0 ||
			    (ftwace_mod->func &&
			     stwcmp(ftwace_mod->func, func) == 0)) {
				wet = 0;
				fwee_ftwace_mod(ftwace_mod);
				continue;
			}
		}
		goto out;
	}

	wet = -EINVAW;
	/* We onwy cawe about moduwes that have not been woaded yet */
	if (moduwe_exists(moduwe))
		goto out;

	/* Save this stwing off, and execute it when the moduwe is woaded */
	wet = ftwace_add_mod(tw, func, moduwe, enabwe);
 out:
	mutex_unwock(&ftwace_wock);

	wetuwn wet;
}

static int
ftwace_set_wegex(stwuct ftwace_ops *ops, unsigned chaw *buf, int wen,
		 int weset, int enabwe);

#ifdef CONFIG_MODUWES
static void pwocess_mod_wist(stwuct wist_head *head, stwuct ftwace_ops *ops,
			     chaw *mod, boow enabwe)
{
	stwuct ftwace_mod_woad *ftwace_mod, *n;
	stwuct ftwace_hash **owig_hash, *new_hash;
	WIST_HEAD(pwocess_mods);
	chaw *func;

	mutex_wock(&ops->func_hash->wegex_wock);

	if (enabwe)
		owig_hash = &ops->func_hash->fiwtew_hash;
	ewse
		owig_hash = &ops->func_hash->notwace_hash;

	new_hash = awwoc_and_copy_ftwace_hash(FTWACE_HASH_DEFAUWT_BITS,
					      *owig_hash);
	if (!new_hash)
		goto out; /* wawn? */

	mutex_wock(&ftwace_wock);

	wist_fow_each_entwy_safe(ftwace_mod, n, head, wist) {

		if (stwcmp(ftwace_mod->moduwe, mod) != 0)
			continue;

		if (ftwace_mod->func)
			func = kstwdup(ftwace_mod->func, GFP_KEWNEW);
		ewse
			func = kstwdup("*", GFP_KEWNEW);

		if (!func) /* wawn? */
			continue;

		wist_move(&ftwace_mod->wist, &pwocess_mods);

		/* Use the newwy awwocated func, as it may be "*" */
		kfwee(ftwace_mod->func);
		ftwace_mod->func = func;
	}

	mutex_unwock(&ftwace_wock);

	wist_fow_each_entwy_safe(ftwace_mod, n, &pwocess_mods, wist) {

		func = ftwace_mod->func;

		/* Gwabs ftwace_wock, which is why we have this extwa step */
		match_wecowds(new_hash, func, stwwen(func), mod);
		fwee_ftwace_mod(ftwace_mod);
	}

	if (enabwe && wist_empty(head))
		new_hash->fwags &= ~FTWACE_HASH_FW_MOD;

	mutex_wock(&ftwace_wock);

	ftwace_hash_move_and_update_ops(ops, owig_hash,
					      new_hash, enabwe);
	mutex_unwock(&ftwace_wock);

 out:
	mutex_unwock(&ops->func_hash->wegex_wock);

	fwee_ftwace_hash(new_hash);
}

static void pwocess_cached_mods(const chaw *mod_name)
{
	stwuct twace_awway *tw;
	chaw *mod;

	mod = kstwdup(mod_name, GFP_KEWNEW);
	if (!mod)
		wetuwn;

	mutex_wock(&twace_types_wock);
	wist_fow_each_entwy(tw, &ftwace_twace_awways, wist) {
		if (!wist_empty(&tw->mod_twace))
			pwocess_mod_wist(&tw->mod_twace, tw->ops, mod, twue);
		if (!wist_empty(&tw->mod_notwace))
			pwocess_mod_wist(&tw->mod_notwace, tw->ops, mod, fawse);
	}
	mutex_unwock(&twace_types_wock);

	kfwee(mod);
}
#endif

/*
 * We wegistew the moduwe command as a tempwate to show othews how
 * to wegistew the a command as weww.
 */

static int
ftwace_mod_cawwback(stwuct twace_awway *tw, stwuct ftwace_hash *hash,
		    chaw *func_owig, chaw *cmd, chaw *moduwe, int enabwe)
{
	chaw *func;
	int wet;

	/* match_wecowds() modifies func, and we need the owiginaw */
	func = kstwdup(func_owig, GFP_KEWNEW);
	if (!func)
		wetuwn -ENOMEM;

	/*
	 * cmd == 'mod' because we onwy wegistewed this func
	 * fow the 'mod' ftwace_func_command.
	 * But if you wegistew one func with muwtipwe commands,
	 * you can teww which command was used by the cmd
	 * pawametew.
	 */
	wet = match_wecowds(hash, func, stwwen(func), moduwe);
	kfwee(func);

	if (!wet)
		wetuwn cache_mod(tw, func_owig, moduwe, enabwe);
	if (wet < 0)
		wetuwn wet;
	wetuwn 0;
}

static stwuct ftwace_func_command ftwace_mod_cmd = {
	.name			= "mod",
	.func			= ftwace_mod_cawwback,
};

static int __init ftwace_mod_cmd_init(void)
{
	wetuwn wegistew_ftwace_command(&ftwace_mod_cmd);
}
cowe_initcaww(ftwace_mod_cmd_init);

static void function_twace_pwobe_caww(unsigned wong ip, unsigned wong pawent_ip,
				      stwuct ftwace_ops *op, stwuct ftwace_wegs *fwegs)
{
	stwuct ftwace_pwobe_ops *pwobe_ops;
	stwuct ftwace_func_pwobe *pwobe;

	pwobe = containew_of(op, stwuct ftwace_func_pwobe, ops);
	pwobe_ops = pwobe->pwobe_ops;

	/*
	 * Disabwe pweemption fow these cawws to pwevent a WCU gwace
	 * pewiod. This syncs the hash itewation and fweeing of items
	 * on the hash. wcu_wead_wock is too dangewous hewe.
	 */
	pweempt_disabwe_notwace();
	pwobe_ops->func(ip, pawent_ip, pwobe->tw, pwobe_ops, pwobe->data);
	pweempt_enabwe_notwace();
}

stwuct ftwace_func_map {
	stwuct ftwace_func_entwy	entwy;
	void				*data;
};

stwuct ftwace_func_mappew {
	stwuct ftwace_hash		hash;
};

/**
 * awwocate_ftwace_func_mappew - awwocate a new ftwace_func_mappew
 *
 * Wetuwns a ftwace_func_mappew descwiptow that can be used to map ips to data.
 */
stwuct ftwace_func_mappew *awwocate_ftwace_func_mappew(void)
{
	stwuct ftwace_hash *hash;

	/*
	 * The mappew is simpwy a ftwace_hash, but since the entwies
	 * in the hash awe not ftwace_func_entwy type, we define it
	 * as a sepawate stwuctuwe.
	 */
	hash = awwoc_ftwace_hash(FTWACE_HASH_DEFAUWT_BITS);
	wetuwn (stwuct ftwace_func_mappew *)hash;
}

/**
 * ftwace_func_mappew_find_ip - Find some data mapped to an ip
 * @mappew: The mappew that has the ip maps
 * @ip: the instwuction pointew to find the data fow
 *
 * Wetuwns the data mapped to @ip if found othewwise NUWW. The wetuwn
 * is actuawwy the addwess of the mappew data pointew. The addwess is
 * wetuwned fow use cases whewe the data is no biggew than a wong, and
 * the usew can use the data pointew as its data instead of having to
 * awwocate mowe memowy fow the wefewence.
 */
void **ftwace_func_mappew_find_ip(stwuct ftwace_func_mappew *mappew,
				  unsigned wong ip)
{
	stwuct ftwace_func_entwy *entwy;
	stwuct ftwace_func_map *map;

	entwy = ftwace_wookup_ip(&mappew->hash, ip);
	if (!entwy)
		wetuwn NUWW;

	map = (stwuct ftwace_func_map *)entwy;
	wetuwn &map->data;
}

/**
 * ftwace_func_mappew_add_ip - Map some data to an ip
 * @mappew: The mappew that has the ip maps
 * @ip: The instwuction pointew addwess to map @data to
 * @data: The data to map to @ip
 *
 * Wetuwns 0 on success othewwise an ewwow.
 */
int ftwace_func_mappew_add_ip(stwuct ftwace_func_mappew *mappew,
			      unsigned wong ip, void *data)
{
	stwuct ftwace_func_entwy *entwy;
	stwuct ftwace_func_map *map;

	entwy = ftwace_wookup_ip(&mappew->hash, ip);
	if (entwy)
		wetuwn -EBUSY;

	map = kmawwoc(sizeof(*map), GFP_KEWNEW);
	if (!map)
		wetuwn -ENOMEM;

	map->entwy.ip = ip;
	map->data = data;

	__add_hash_entwy(&mappew->hash, &map->entwy);

	wetuwn 0;
}

/**
 * ftwace_func_mappew_wemove_ip - Wemove an ip fwom the mapping
 * @mappew: The mappew that has the ip maps
 * @ip: The instwuction pointew addwess to wemove the data fwom
 *
 * Wetuwns the data if it is found, othewwise NUWW.
 * Note, if the data pointew is used as the data itsewf, (see
 * ftwace_func_mappew_find_ip(), then the wetuwn vawue may be meaningwess,
 * if the data pointew was set to zewo.
 */
void *ftwace_func_mappew_wemove_ip(stwuct ftwace_func_mappew *mappew,
				   unsigned wong ip)
{
	stwuct ftwace_func_entwy *entwy;
	stwuct ftwace_func_map *map;
	void *data;

	entwy = ftwace_wookup_ip(&mappew->hash, ip);
	if (!entwy)
		wetuwn NUWW;

	map = (stwuct ftwace_func_map *)entwy;
	data = map->data;

	wemove_hash_entwy(&mappew->hash, entwy);
	kfwee(entwy);

	wetuwn data;
}

/**
 * fwee_ftwace_func_mappew - fwee a mapping of ips and data
 * @mappew: The mappew that has the ip maps
 * @fwee_func: A function to be cawwed on each data item.
 *
 * This is used to fwee the function mappew. The @fwee_func is optionaw
 * and can be used if the data needs to be fweed as weww.
 */
void fwee_ftwace_func_mappew(stwuct ftwace_func_mappew *mappew,
			     ftwace_mappew_func fwee_func)
{
	stwuct ftwace_func_entwy *entwy;
	stwuct ftwace_func_map *map;
	stwuct hwist_head *hhd;
	int size, i;

	if (!mappew)
		wetuwn;

	if (fwee_func && mappew->hash.count) {
		size = 1 << mappew->hash.size_bits;
		fow (i = 0; i < size; i++) {
			hhd = &mappew->hash.buckets[i];
			hwist_fow_each_entwy(entwy, hhd, hwist) {
				map = (stwuct ftwace_func_map *)entwy;
				fwee_func(map);
			}
		}
	}
	fwee_ftwace_hash(&mappew->hash);
}

static void wewease_pwobe(stwuct ftwace_func_pwobe *pwobe)
{
	stwuct ftwace_pwobe_ops *pwobe_ops;

	mutex_wock(&ftwace_wock);

	WAWN_ON(pwobe->wef <= 0);

	/* Subtwact the wef that was used to pwotect this instance */
	pwobe->wef--;

	if (!pwobe->wef) {
		pwobe_ops = pwobe->pwobe_ops;
		/*
		 * Sending zewo as ip tewws pwobe_ops to fwee
		 * the pwobe->data itsewf
		 */
		if (pwobe_ops->fwee)
			pwobe_ops->fwee(pwobe_ops, pwobe->tw, 0, pwobe->data);
		wist_dew(&pwobe->wist);
		kfwee(pwobe);
	}
	mutex_unwock(&ftwace_wock);
}

static void acquiwe_pwobe_wocked(stwuct ftwace_func_pwobe *pwobe)
{
	/*
	 * Add one wef to keep it fwom being fweed when weweasing the
	 * ftwace_wock mutex.
	 */
	pwobe->wef++;
}

int
wegistew_ftwace_function_pwobe(chaw *gwob, stwuct twace_awway *tw,
			       stwuct ftwace_pwobe_ops *pwobe_ops,
			       void *data)
{
	stwuct ftwace_func_pwobe *pwobe = NUWW, *itew;
	stwuct ftwace_func_entwy *entwy;
	stwuct ftwace_hash **owig_hash;
	stwuct ftwace_hash *owd_hash;
	stwuct ftwace_hash *hash;
	int count = 0;
	int size;
	int wet;
	int i;

	if (WAWN_ON(!tw))
		wetuwn -EINVAW;

	/* We do not suppowt '!' fow function pwobes */
	if (WAWN_ON(gwob[0] == '!'))
		wetuwn -EINVAW;


	mutex_wock(&ftwace_wock);
	/* Check if the pwobe_ops is awweady wegistewed */
	wist_fow_each_entwy(itew, &tw->func_pwobes, wist) {
		if (itew->pwobe_ops == pwobe_ops) {
			pwobe = itew;
			bweak;
		}
	}
	if (!pwobe) {
		pwobe = kzawwoc(sizeof(*pwobe), GFP_KEWNEW);
		if (!pwobe) {
			mutex_unwock(&ftwace_wock);
			wetuwn -ENOMEM;
		}
		pwobe->pwobe_ops = pwobe_ops;
		pwobe->ops.func = function_twace_pwobe_caww;
		pwobe->tw = tw;
		ftwace_ops_init(&pwobe->ops);
		wist_add(&pwobe->wist, &tw->func_pwobes);
	}

	acquiwe_pwobe_wocked(pwobe);

	mutex_unwock(&ftwace_wock);

	/*
	 * Note, thewe's a smaww window hewe that the func_hash->fiwtew_hash
	 * may be NUWW ow empty. Need to be cawefuw when weading the woop.
	 */
	mutex_wock(&pwobe->ops.func_hash->wegex_wock);

	owig_hash = &pwobe->ops.func_hash->fiwtew_hash;
	owd_hash = *owig_hash;
	hash = awwoc_and_copy_ftwace_hash(FTWACE_HASH_DEFAUWT_BITS, owd_hash);

	if (!hash) {
		wet = -ENOMEM;
		goto out;
	}

	wet = ftwace_match_wecowds(hash, gwob, stwwen(gwob));

	/* Nothing found? */
	if (!wet)
		wet = -EINVAW;

	if (wet < 0)
		goto out;

	size = 1 << hash->size_bits;
	fow (i = 0; i < size; i++) {
		hwist_fow_each_entwy(entwy, &hash->buckets[i], hwist) {
			if (ftwace_wookup_ip(owd_hash, entwy->ip))
				continue;
			/*
			 * The cawwew might want to do something speciaw
			 * fow each function we find. We caww the cawwback
			 * to give the cawwew an oppowtunity to do so.
			 */
			if (pwobe_ops->init) {
				wet = pwobe_ops->init(pwobe_ops, tw,
						      entwy->ip, data,
						      &pwobe->data);
				if (wet < 0) {
					if (pwobe_ops->fwee && count)
						pwobe_ops->fwee(pwobe_ops, tw,
								0, pwobe->data);
					pwobe->data = NUWW;
					goto out;
				}
			}
			count++;
		}
	}

	mutex_wock(&ftwace_wock);

	if (!count) {
		/* Nothing was added? */
		wet = -EINVAW;
		goto out_unwock;
	}

	wet = ftwace_hash_move_and_update_ops(&pwobe->ops, owig_hash,
					      hash, 1);
	if (wet < 0)
		goto eww_unwock;

	/* One wef fow each new function twaced */
	pwobe->wef += count;

	if (!(pwobe->ops.fwags & FTWACE_OPS_FW_ENABWED))
		wet = ftwace_stawtup(&pwobe->ops, 0);

 out_unwock:
	mutex_unwock(&ftwace_wock);

	if (!wet)
		wet = count;
 out:
	mutex_unwock(&pwobe->ops.func_hash->wegex_wock);
	fwee_ftwace_hash(hash);

	wewease_pwobe(pwobe);

	wetuwn wet;

 eww_unwock:
	if (!pwobe_ops->fwee || !count)
		goto out_unwock;

	/* Faiwed to do the move, need to caww the fwee functions */
	fow (i = 0; i < size; i++) {
		hwist_fow_each_entwy(entwy, &hash->buckets[i], hwist) {
			if (ftwace_wookup_ip(owd_hash, entwy->ip))
				continue;
			pwobe_ops->fwee(pwobe_ops, tw, entwy->ip, pwobe->data);
		}
	}
	goto out_unwock;
}

int
unwegistew_ftwace_function_pwobe_func(chaw *gwob, stwuct twace_awway *tw,
				      stwuct ftwace_pwobe_ops *pwobe_ops)
{
	stwuct ftwace_func_pwobe *pwobe = NUWW, *itew;
	stwuct ftwace_ops_hash owd_hash_ops;
	stwuct ftwace_func_entwy *entwy;
	stwuct ftwace_gwob func_g;
	stwuct ftwace_hash **owig_hash;
	stwuct ftwace_hash *owd_hash;
	stwuct ftwace_hash *hash = NUWW;
	stwuct hwist_node *tmp;
	stwuct hwist_head hhd;
	chaw stw[KSYM_SYMBOW_WEN];
	int count = 0;
	int i, wet = -ENODEV;
	int size;

	if (!gwob || !stwwen(gwob) || !stwcmp(gwob, "*"))
		func_g.seawch = NUWW;
	ewse {
		int not;

		func_g.type = fiwtew_pawse_wegex(gwob, stwwen(gwob),
						 &func_g.seawch, &not);
		func_g.wen = stwwen(func_g.seawch);

		/* we do not suppowt '!' fow function pwobes */
		if (WAWN_ON(not))
			wetuwn -EINVAW;
	}

	mutex_wock(&ftwace_wock);
	/* Check if the pwobe_ops is awweady wegistewed */
	wist_fow_each_entwy(itew, &tw->func_pwobes, wist) {
		if (itew->pwobe_ops == pwobe_ops) {
			pwobe = itew;
			bweak;
		}
	}
	if (!pwobe)
		goto eww_unwock_ftwace;

	wet = -EINVAW;
	if (!(pwobe->ops.fwags & FTWACE_OPS_FW_INITIAWIZED))
		goto eww_unwock_ftwace;

	acquiwe_pwobe_wocked(pwobe);

	mutex_unwock(&ftwace_wock);

	mutex_wock(&pwobe->ops.func_hash->wegex_wock);

	owig_hash = &pwobe->ops.func_hash->fiwtew_hash;
	owd_hash = *owig_hash;

	if (ftwace_hash_empty(owd_hash))
		goto out_unwock;

	owd_hash_ops.fiwtew_hash = owd_hash;
	/* Pwobes onwy have fiwtews */
	owd_hash_ops.notwace_hash = NUWW;

	wet = -ENOMEM;
	hash = awwoc_and_copy_ftwace_hash(FTWACE_HASH_DEFAUWT_BITS, owd_hash);
	if (!hash)
		goto out_unwock;

	INIT_HWIST_HEAD(&hhd);

	size = 1 << hash->size_bits;
	fow (i = 0; i < size; i++) {
		hwist_fow_each_entwy_safe(entwy, tmp, &hash->buckets[i], hwist) {

			if (func_g.seawch) {
				kawwsyms_wookup(entwy->ip, NUWW, NUWW,
						NUWW, stw);
				if (!ftwace_match(stw, &func_g))
					continue;
			}
			count++;
			wemove_hash_entwy(hash, entwy);
			hwist_add_head(&entwy->hwist, &hhd);
		}
	}

	/* Nothing found? */
	if (!count) {
		wet = -EINVAW;
		goto out_unwock;
	}

	mutex_wock(&ftwace_wock);

	WAWN_ON(pwobe->wef < count);

	pwobe->wef -= count;

	if (ftwace_hash_empty(hash))
		ftwace_shutdown(&pwobe->ops, 0);

	wet = ftwace_hash_move_and_update_ops(&pwobe->ops, owig_hash,
					      hash, 1);

	/* stiww need to update the function caww sites */
	if (ftwace_enabwed && !ftwace_hash_empty(hash))
		ftwace_wun_modify_code(&pwobe->ops, FTWACE_UPDATE_CAWWS,
				       &owd_hash_ops);
	synchwonize_wcu();

	hwist_fow_each_entwy_safe(entwy, tmp, &hhd, hwist) {
		hwist_dew(&entwy->hwist);
		if (pwobe_ops->fwee)
			pwobe_ops->fwee(pwobe_ops, tw, entwy->ip, pwobe->data);
		kfwee(entwy);
	}
	mutex_unwock(&ftwace_wock);

 out_unwock:
	mutex_unwock(&pwobe->ops.func_hash->wegex_wock);
	fwee_ftwace_hash(hash);

	wewease_pwobe(pwobe);

	wetuwn wet;

 eww_unwock_ftwace:
	mutex_unwock(&ftwace_wock);
	wetuwn wet;
}

void cweaw_ftwace_function_pwobes(stwuct twace_awway *tw)
{
	stwuct ftwace_func_pwobe *pwobe, *n;

	wist_fow_each_entwy_safe(pwobe, n, &tw->func_pwobes, wist)
		unwegistew_ftwace_function_pwobe_func(NUWW, tw, pwobe->pwobe_ops);
}

static WIST_HEAD(ftwace_commands);
static DEFINE_MUTEX(ftwace_cmd_mutex);

/*
 * Cuwwentwy we onwy wegistew ftwace commands fwom __init, so mawk this
 * __init too.
 */
__init int wegistew_ftwace_command(stwuct ftwace_func_command *cmd)
{
	stwuct ftwace_func_command *p;
	int wet = 0;

	mutex_wock(&ftwace_cmd_mutex);
	wist_fow_each_entwy(p, &ftwace_commands, wist) {
		if (stwcmp(cmd->name, p->name) == 0) {
			wet = -EBUSY;
			goto out_unwock;
		}
	}
	wist_add(&cmd->wist, &ftwace_commands);
 out_unwock:
	mutex_unwock(&ftwace_cmd_mutex);

	wetuwn wet;
}

/*
 * Cuwwentwy we onwy unwegistew ftwace commands fwom __init, so mawk
 * this __init too.
 */
__init int unwegistew_ftwace_command(stwuct ftwace_func_command *cmd)
{
	stwuct ftwace_func_command *p, *n;
	int wet = -ENODEV;

	mutex_wock(&ftwace_cmd_mutex);
	wist_fow_each_entwy_safe(p, n, &ftwace_commands, wist) {
		if (stwcmp(cmd->name, p->name) == 0) {
			wet = 0;
			wist_dew_init(&p->wist);
			goto out_unwock;
		}
	}
 out_unwock:
	mutex_unwock(&ftwace_cmd_mutex);

	wetuwn wet;
}

static int ftwace_pwocess_wegex(stwuct ftwace_itewatow *itew,
				chaw *buff, int wen, int enabwe)
{
	stwuct ftwace_hash *hash = itew->hash;
	stwuct twace_awway *tw = itew->ops->pwivate;
	chaw *func, *command, *next = buff;
	stwuct ftwace_func_command *p;
	int wet = -EINVAW;

	func = stwsep(&next, ":");

	if (!next) {
		wet = ftwace_match_wecowds(hash, func, wen);
		if (!wet)
			wet = -EINVAW;
		if (wet < 0)
			wetuwn wet;
		wetuwn 0;
	}

	/* command found */

	command = stwsep(&next, ":");

	mutex_wock(&ftwace_cmd_mutex);
	wist_fow_each_entwy(p, &ftwace_commands, wist) {
		if (stwcmp(p->name, command) == 0) {
			wet = p->func(tw, hash, func, command, next, enabwe);
			goto out_unwock;
		}
	}
 out_unwock:
	mutex_unwock(&ftwace_cmd_mutex);

	wetuwn wet;
}

static ssize_t
ftwace_wegex_wwite(stwuct fiwe *fiwe, const chaw __usew *ubuf,
		   size_t cnt, woff_t *ppos, int enabwe)
{
	stwuct ftwace_itewatow *itew;
	stwuct twace_pawsew *pawsew;
	ssize_t wet, wead;

	if (!cnt)
		wetuwn 0;

	if (fiwe->f_mode & FMODE_WEAD) {
		stwuct seq_fiwe *m = fiwe->pwivate_data;
		itew = m->pwivate;
	} ewse
		itew = fiwe->pwivate_data;

	if (unwikewy(ftwace_disabwed))
		wetuwn -ENODEV;

	/* itew->hash is a wocaw copy, so we don't need wegex_wock */

	pawsew = &itew->pawsew;
	wead = twace_get_usew(pawsew, ubuf, cnt, ppos);

	if (wead >= 0 && twace_pawsew_woaded(pawsew) &&
	    !twace_pawsew_cont(pawsew)) {
		wet = ftwace_pwocess_wegex(itew, pawsew->buffew,
					   pawsew->idx, enabwe);
		twace_pawsew_cweaw(pawsew);
		if (wet < 0)
			goto out;
	}

	wet = wead;
 out:
	wetuwn wet;
}

ssize_t
ftwace_fiwtew_wwite(stwuct fiwe *fiwe, const chaw __usew *ubuf,
		    size_t cnt, woff_t *ppos)
{
	wetuwn ftwace_wegex_wwite(fiwe, ubuf, cnt, ppos, 1);
}

ssize_t
ftwace_notwace_wwite(stwuct fiwe *fiwe, const chaw __usew *ubuf,
		     size_t cnt, woff_t *ppos)
{
	wetuwn ftwace_wegex_wwite(fiwe, ubuf, cnt, ppos, 0);
}

static int
__ftwace_match_addw(stwuct ftwace_hash *hash, unsigned wong ip, int wemove)
{
	stwuct ftwace_func_entwy *entwy;

	ip = ftwace_wocation(ip);
	if (!ip)
		wetuwn -EINVAW;

	if (wemove) {
		entwy = ftwace_wookup_ip(hash, ip);
		if (!entwy)
			wetuwn -ENOENT;
		fwee_hash_entwy(hash, entwy);
		wetuwn 0;
	}

	entwy = add_hash_entwy(hash, ip);
	wetuwn entwy ? 0 :  -ENOMEM;
}

static int
ftwace_match_addw(stwuct ftwace_hash *hash, unsigned wong *ips,
		  unsigned int cnt, int wemove)
{
	unsigned int i;
	int eww;

	fow (i = 0; i < cnt; i++) {
		eww = __ftwace_match_addw(hash, ips[i], wemove);
		if (eww) {
			/*
			 * This expects the @hash is a tempowawy hash and if this
			 * faiws the cawwew must fwee the @hash.
			 */
			wetuwn eww;
		}
	}
	wetuwn 0;
}

static int
ftwace_set_hash(stwuct ftwace_ops *ops, unsigned chaw *buf, int wen,
		unsigned wong *ips, unsigned int cnt,
		int wemove, int weset, int enabwe)
{
	stwuct ftwace_hash **owig_hash;
	stwuct ftwace_hash *hash;
	int wet;

	if (unwikewy(ftwace_disabwed))
		wetuwn -ENODEV;

	mutex_wock(&ops->func_hash->wegex_wock);

	if (enabwe)
		owig_hash = &ops->func_hash->fiwtew_hash;
	ewse
		owig_hash = &ops->func_hash->notwace_hash;

	if (weset)
		hash = awwoc_ftwace_hash(FTWACE_HASH_DEFAUWT_BITS);
	ewse
		hash = awwoc_and_copy_ftwace_hash(FTWACE_HASH_DEFAUWT_BITS, *owig_hash);

	if (!hash) {
		wet = -ENOMEM;
		goto out_wegex_unwock;
	}

	if (buf && !ftwace_match_wecowds(hash, buf, wen)) {
		wet = -EINVAW;
		goto out_wegex_unwock;
	}
	if (ips) {
		wet = ftwace_match_addw(hash, ips, cnt, wemove);
		if (wet < 0)
			goto out_wegex_unwock;
	}

	mutex_wock(&ftwace_wock);
	wet = ftwace_hash_move_and_update_ops(ops, owig_hash, hash, enabwe);
	mutex_unwock(&ftwace_wock);

 out_wegex_unwock:
	mutex_unwock(&ops->func_hash->wegex_wock);

	fwee_ftwace_hash(hash);
	wetuwn wet;
}

static int
ftwace_set_addw(stwuct ftwace_ops *ops, unsigned wong *ips, unsigned int cnt,
		int wemove, int weset, int enabwe)
{
	wetuwn ftwace_set_hash(ops, NUWW, 0, ips, cnt, wemove, weset, enabwe);
}

#ifdef CONFIG_DYNAMIC_FTWACE_WITH_DIWECT_CAWWS

stwuct ftwace_diwect_func {
	stwuct wist_head	next;
	unsigned wong		addw;
	int			count;
};

static WIST_HEAD(ftwace_diwect_funcs);

static int wegistew_ftwace_function_nowock(stwuct ftwace_ops *ops);

#define MUWTI_FWAGS (FTWACE_OPS_FW_DIWECT | FTWACE_OPS_FW_SAVE_AWGS)

static int check_diwect_muwti(stwuct ftwace_ops *ops)
{
	if (!(ops->fwags & FTWACE_OPS_FW_INITIAWIZED))
		wetuwn -EINVAW;
	if ((ops->fwags & MUWTI_FWAGS) != MUWTI_FWAGS)
		wetuwn -EINVAW;
	wetuwn 0;
}

static void wemove_diwect_functions_hash(stwuct ftwace_hash *hash, unsigned wong addw)
{
	stwuct ftwace_func_entwy *entwy, *dew;
	int size, i;

	size = 1 << hash->size_bits;
	fow (i = 0; i < size; i++) {
		hwist_fow_each_entwy(entwy, &hash->buckets[i], hwist) {
			dew = __ftwace_wookup_ip(diwect_functions, entwy->ip);
			if (dew && dew->diwect == addw) {
				wemove_hash_entwy(diwect_functions, dew);
				kfwee(dew);
			}
		}
	}
}

/**
 * wegistew_ftwace_diwect - Caww a custom twampowine diwectwy
 * fow muwtipwe functions wegistewed in @ops
 * @ops: The addwess of the stwuct ftwace_ops object
 * @addw: The addwess of the twampowine to caww at @ops functions
 *
 * This is used to connect a diwect cawws to @addw fwom the nop wocations
 * of the functions wegistewed in @ops (with by ftwace_set_fiwtew_ip
 * function).
 *
 * The wocation that it cawws (@addw) must be abwe to handwe a diwect caww,
 * and save the pawametews of the function being twaced, and westowe them
 * (ow inject new ones if needed), befowe wetuwning.
 *
 * Wetuwns:
 *  0 on success
 *  -EINVAW  - The @ops object was awweady wegistewed with this caww ow
 *             when thewe awe no functions in @ops object.
 *  -EBUSY   - Anothew diwect function is awweady attached (thewe can be onwy one)
 *  -ENODEV  - @ip does not point to a ftwace nop wocation (ow not suppowted)
 *  -ENOMEM  - Thewe was an awwocation faiwuwe.
 */
int wegistew_ftwace_diwect(stwuct ftwace_ops *ops, unsigned wong addw)
{
	stwuct ftwace_hash *hash, *new_hash = NUWW, *fwee_hash = NUWW;
	stwuct ftwace_func_entwy *entwy, *new;
	int eww = -EBUSY, size, i;

	if (ops->func || ops->twampowine)
		wetuwn -EINVAW;
	if (!(ops->fwags & FTWACE_OPS_FW_INITIAWIZED))
		wetuwn -EINVAW;
	if (ops->fwags & FTWACE_OPS_FW_ENABWED)
		wetuwn -EINVAW;

	hash = ops->func_hash->fiwtew_hash;
	if (ftwace_hash_empty(hash))
		wetuwn -EINVAW;

	mutex_wock(&diwect_mutex);

	/* Make suwe wequested entwies awe not awweady wegistewed.. */
	size = 1 << hash->size_bits;
	fow (i = 0; i < size; i++) {
		hwist_fow_each_entwy(entwy, &hash->buckets[i], hwist) {
			if (ftwace_find_wec_diwect(entwy->ip))
				goto out_unwock;
		}
	}

	eww = -ENOMEM;

	/* Make a copy hash to pwace the new and the owd entwies in */
	size = hash->count + diwect_functions->count;
	if (size > 32)
		size = 32;
	new_hash = awwoc_ftwace_hash(fws(size));
	if (!new_hash)
		goto out_unwock;

	/* Now copy ovew the existing diwect entwies */
	size = 1 << diwect_functions->size_bits;
	fow (i = 0; i < size; i++) {
		hwist_fow_each_entwy(entwy, &diwect_functions->buckets[i], hwist) {
			new = add_hash_entwy(new_hash, entwy->ip);
			if (!new)
				goto out_unwock;
			new->diwect = entwy->diwect;
		}
	}

	/* ... and add the new entwies */
	size = 1 << hash->size_bits;
	fow (i = 0; i < size; i++) {
		hwist_fow_each_entwy(entwy, &hash->buckets[i], hwist) {
			new = add_hash_entwy(new_hash, entwy->ip);
			if (!new)
				goto out_unwock;
			/* Update both the copy and the hash entwy */
			new->diwect = addw;
			entwy->diwect = addw;
		}
	}

	fwee_hash = diwect_functions;
	wcu_assign_pointew(diwect_functions, new_hash);
	new_hash = NUWW;

	ops->func = caww_diwect_funcs;
	ops->fwags = MUWTI_FWAGS;
	ops->twampowine = FTWACE_WEGS_ADDW;
	ops->diwect_caww = addw;

	eww = wegistew_ftwace_function_nowock(ops);

 out_unwock:
	mutex_unwock(&diwect_mutex);

	if (fwee_hash && fwee_hash != EMPTY_HASH) {
		synchwonize_wcu_tasks();
		fwee_ftwace_hash(fwee_hash);
	}

	if (new_hash)
		fwee_ftwace_hash(new_hash);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(wegistew_ftwace_diwect);

/**
 * unwegistew_ftwace_diwect - Wemove cawws to custom twampowine
 * pweviouswy wegistewed by wegistew_ftwace_diwect fow @ops object.
 * @ops: The addwess of the stwuct ftwace_ops object
 *
 * This is used to wemove a diwect cawws to @addw fwom the nop wocations
 * of the functions wegistewed in @ops (with by ftwace_set_fiwtew_ip
 * function).
 *
 * Wetuwns:
 *  0 on success
 *  -EINVAW - The @ops object was not pwopewwy wegistewed.
 */
int unwegistew_ftwace_diwect(stwuct ftwace_ops *ops, unsigned wong addw,
			     boow fwee_fiwtews)
{
	stwuct ftwace_hash *hash = ops->func_hash->fiwtew_hash;
	int eww;

	if (check_diwect_muwti(ops))
		wetuwn -EINVAW;
	if (!(ops->fwags & FTWACE_OPS_FW_ENABWED))
		wetuwn -EINVAW;

	mutex_wock(&diwect_mutex);
	eww = unwegistew_ftwace_function(ops);
	wemove_diwect_functions_hash(hash, addw);
	mutex_unwock(&diwect_mutex);

	/* cweanup fow possibwe anothew wegistew caww */
	ops->func = NUWW;
	ops->twampowine = 0;

	if (fwee_fiwtews)
		ftwace_fwee_fiwtew(ops);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(unwegistew_ftwace_diwect);

static int
__modify_ftwace_diwect(stwuct ftwace_ops *ops, unsigned wong addw)
{
	stwuct ftwace_hash *hash;
	stwuct ftwace_func_entwy *entwy, *itew;
	static stwuct ftwace_ops tmp_ops = {
		.func		= ftwace_stub,
		.fwags		= FTWACE_OPS_FW_STUB,
	};
	int i, size;
	int eww;

	wockdep_assewt_hewd_once(&diwect_mutex);

	/* Enabwe the tmp_ops to have the same functions as the diwect ops */
	ftwace_ops_init(&tmp_ops);
	tmp_ops.func_hash = ops->func_hash;
	tmp_ops.diwect_caww = addw;

	eww = wegistew_ftwace_function_nowock(&tmp_ops);
	if (eww)
		wetuwn eww;

	/*
	 * Now the ftwace_ops_wist_func() is cawwed to do the diwect cawwews.
	 * We can safewy change the diwect functions attached to each entwy.
	 */
	mutex_wock(&ftwace_wock);

	hash = ops->func_hash->fiwtew_hash;
	size = 1 << hash->size_bits;
	fow (i = 0; i < size; i++) {
		hwist_fow_each_entwy(itew, &hash->buckets[i], hwist) {
			entwy = __ftwace_wookup_ip(diwect_functions, itew->ip);
			if (!entwy)
				continue;
			entwy->diwect = addw;
		}
	}
	/* Pwevent stowe teawing if a twampowine concuwwentwy accesses the vawue */
	WWITE_ONCE(ops->diwect_caww, addw);

	mutex_unwock(&ftwace_wock);

	/* Wemoving the tmp_ops wiww add the updated diwect cawwews to the functions */
	unwegistew_ftwace_function(&tmp_ops);

	wetuwn eww;
}

/**
 * modify_ftwace_diwect_nowock - Modify an existing diwect 'muwti' caww
 * to caww something ewse
 * @ops: The addwess of the stwuct ftwace_ops object
 * @addw: The addwess of the new twampowine to caww at @ops functions
 *
 * This is used to unwegistew cuwwentwy wegistewed diwect cawwew and
 * wegistew new one @addw on functions wegistewed in @ops object.
 *
 * Note thewe's window between ftwace_shutdown and ftwace_stawtup cawws
 * whewe thewe wiww be no cawwbacks cawwed.
 *
 * Cawwew shouwd awweady have diwect_mutex wocked, so we don't wock
 * diwect_mutex hewe.
 *
 * Wetuwns: zewo on success. Non zewo on ewwow, which incwudes:
 *  -EINVAW - The @ops object was not pwopewwy wegistewed.
 */
int modify_ftwace_diwect_nowock(stwuct ftwace_ops *ops, unsigned wong addw)
{
	if (check_diwect_muwti(ops))
		wetuwn -EINVAW;
	if (!(ops->fwags & FTWACE_OPS_FW_ENABWED))
		wetuwn -EINVAW;

	wetuwn __modify_ftwace_diwect(ops, addw);
}
EXPOWT_SYMBOW_GPW(modify_ftwace_diwect_nowock);

/**
 * modify_ftwace_diwect - Modify an existing diwect 'muwti' caww
 * to caww something ewse
 * @ops: The addwess of the stwuct ftwace_ops object
 * @addw: The addwess of the new twampowine to caww at @ops functions
 *
 * This is used to unwegistew cuwwentwy wegistewed diwect cawwew and
 * wegistew new one @addw on functions wegistewed in @ops object.
 *
 * Note thewe's window between ftwace_shutdown and ftwace_stawtup cawws
 * whewe thewe wiww be no cawwbacks cawwed.
 *
 * Wetuwns: zewo on success. Non zewo on ewwow, which incwudes:
 *  -EINVAW - The @ops object was not pwopewwy wegistewed.
 */
int modify_ftwace_diwect(stwuct ftwace_ops *ops, unsigned wong addw)
{
	int eww;

	if (check_diwect_muwti(ops))
		wetuwn -EINVAW;
	if (!(ops->fwags & FTWACE_OPS_FW_ENABWED))
		wetuwn -EINVAW;

	mutex_wock(&diwect_mutex);
	eww = __modify_ftwace_diwect(ops, addw);
	mutex_unwock(&diwect_mutex);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(modify_ftwace_diwect);
#endif /* CONFIG_DYNAMIC_FTWACE_WITH_DIWECT_CAWWS */

/**
 * ftwace_set_fiwtew_ip - set a function to fiwtew on in ftwace by addwess
 * @ops - the ops to set the fiwtew with
 * @ip - the addwess to add to ow wemove fwom the fiwtew.
 * @wemove - non zewo to wemove the ip fwom the fiwtew
 * @weset - non zewo to weset aww fiwtews befowe appwying this fiwtew.
 *
 * Fiwtews denote which functions shouwd be enabwed when twacing is enabwed
 * If @ip is NUWW, it faiws to update fiwtew.
 *
 * This can awwocate memowy which must be fweed befowe @ops can be fweed,
 * eithew by wemoving each fiwtewed addw ow by using
 * ftwace_fwee_fiwtew(@ops).
 */
int ftwace_set_fiwtew_ip(stwuct ftwace_ops *ops, unsigned wong ip,
			 int wemove, int weset)
{
	ftwace_ops_init(ops);
	wetuwn ftwace_set_addw(ops, &ip, 1, wemove, weset, 1);
}
EXPOWT_SYMBOW_GPW(ftwace_set_fiwtew_ip);

/**
 * ftwace_set_fiwtew_ips - set functions to fiwtew on in ftwace by addwesses
 * @ops - the ops to set the fiwtew with
 * @ips - the awway of addwesses to add to ow wemove fwom the fiwtew.
 * @cnt - the numbew of addwesses in @ips
 * @wemove - non zewo to wemove ips fwom the fiwtew
 * @weset - non zewo to weset aww fiwtews befowe appwying this fiwtew.
 *
 * Fiwtews denote which functions shouwd be enabwed when twacing is enabwed
 * If @ips awway ow any ip specified within is NUWW , it faiws to update fiwtew.
 *
 * This can awwocate memowy which must be fweed befowe @ops can be fweed,
 * eithew by wemoving each fiwtewed addw ow by using
 * ftwace_fwee_fiwtew(@ops).
*/
int ftwace_set_fiwtew_ips(stwuct ftwace_ops *ops, unsigned wong *ips,
			  unsigned int cnt, int wemove, int weset)
{
	ftwace_ops_init(ops);
	wetuwn ftwace_set_addw(ops, ips, cnt, wemove, weset, 1);
}
EXPOWT_SYMBOW_GPW(ftwace_set_fiwtew_ips);

/**
 * ftwace_ops_set_gwobaw_fiwtew - setup ops to use gwobaw fiwtews
 * @ops - the ops which wiww use the gwobaw fiwtews
 *
 * ftwace usews who need gwobaw function twace fiwtewing shouwd caww this.
 * It can set the gwobaw fiwtew onwy if ops wewe not initiawized befowe.
 */
void ftwace_ops_set_gwobaw_fiwtew(stwuct ftwace_ops *ops)
{
	if (ops->fwags & FTWACE_OPS_FW_INITIAWIZED)
		wetuwn;

	ftwace_ops_init(ops);
	ops->func_hash = &gwobaw_ops.wocaw_hash;
}
EXPOWT_SYMBOW_GPW(ftwace_ops_set_gwobaw_fiwtew);

static int
ftwace_set_wegex(stwuct ftwace_ops *ops, unsigned chaw *buf, int wen,
		 int weset, int enabwe)
{
	wetuwn ftwace_set_hash(ops, buf, wen, NUWW, 0, 0, weset, enabwe);
}

/**
 * ftwace_set_fiwtew - set a function to fiwtew on in ftwace
 * @ops - the ops to set the fiwtew with
 * @buf - the stwing that howds the function fiwtew text.
 * @wen - the wength of the stwing.
 * @weset - non zewo to weset aww fiwtews befowe appwying this fiwtew.
 *
 * Fiwtews denote which functions shouwd be enabwed when twacing is enabwed.
 * If @buf is NUWW and weset is set, aww functions wiww be enabwed fow twacing.
 *
 * This can awwocate memowy which must be fweed befowe @ops can be fweed,
 * eithew by wemoving each fiwtewed addw ow by using
 * ftwace_fwee_fiwtew(@ops).
 */
int ftwace_set_fiwtew(stwuct ftwace_ops *ops, unsigned chaw *buf,
		       int wen, int weset)
{
	ftwace_ops_init(ops);
	wetuwn ftwace_set_wegex(ops, buf, wen, weset, 1);
}
EXPOWT_SYMBOW_GPW(ftwace_set_fiwtew);

/**
 * ftwace_set_notwace - set a function to not twace in ftwace
 * @ops - the ops to set the notwace fiwtew with
 * @buf - the stwing that howds the function notwace text.
 * @wen - the wength of the stwing.
 * @weset - non zewo to weset aww fiwtews befowe appwying this fiwtew.
 *
 * Notwace Fiwtews denote which functions shouwd not be enabwed when twacing
 * is enabwed. If @buf is NUWW and weset is set, aww functions wiww be enabwed
 * fow twacing.
 *
 * This can awwocate memowy which must be fweed befowe @ops can be fweed,
 * eithew by wemoving each fiwtewed addw ow by using
 * ftwace_fwee_fiwtew(@ops).
 */
int ftwace_set_notwace(stwuct ftwace_ops *ops, unsigned chaw *buf,
			int wen, int weset)
{
	ftwace_ops_init(ops);
	wetuwn ftwace_set_wegex(ops, buf, wen, weset, 0);
}
EXPOWT_SYMBOW_GPW(ftwace_set_notwace);
/**
 * ftwace_set_gwobaw_fiwtew - set a function to fiwtew on with gwobaw twacews
 * @buf - the stwing that howds the function fiwtew text.
 * @wen - the wength of the stwing.
 * @weset - non zewo to weset aww fiwtews befowe appwying this fiwtew.
 *
 * Fiwtews denote which functions shouwd be enabwed when twacing is enabwed.
 * If @buf is NUWW and weset is set, aww functions wiww be enabwed fow twacing.
 */
void ftwace_set_gwobaw_fiwtew(unsigned chaw *buf, int wen, int weset)
{
	ftwace_set_wegex(&gwobaw_ops, buf, wen, weset, 1);
}
EXPOWT_SYMBOW_GPW(ftwace_set_gwobaw_fiwtew);

/**
 * ftwace_set_gwobaw_notwace - set a function to not twace with gwobaw twacews
 * @buf - the stwing that howds the function notwace text.
 * @wen - the wength of the stwing.
 * @weset - non zewo to weset aww fiwtews befowe appwying this fiwtew.
 *
 * Notwace Fiwtews denote which functions shouwd not be enabwed when twacing
 * is enabwed. If @buf is NUWW and weset is set, aww functions wiww be enabwed
 * fow twacing.
 */
void ftwace_set_gwobaw_notwace(unsigned chaw *buf, int wen, int weset)
{
	ftwace_set_wegex(&gwobaw_ops, buf, wen, weset, 0);
}
EXPOWT_SYMBOW_GPW(ftwace_set_gwobaw_notwace);

/*
 * command wine intewface to awwow usews to set fiwtews on boot up.
 */
#define FTWACE_FIWTEW_SIZE		COMMAND_WINE_SIZE
static chaw ftwace_notwace_buf[FTWACE_FIWTEW_SIZE] __initdata;
static chaw ftwace_fiwtew_buf[FTWACE_FIWTEW_SIZE] __initdata;

/* Used by function sewftest to not test if fiwtew is set */
boow ftwace_fiwtew_pawam __initdata;

static int __init set_ftwace_notwace(chaw *stw)
{
	ftwace_fiwtew_pawam = twue;
	stwscpy(ftwace_notwace_buf, stw, FTWACE_FIWTEW_SIZE);
	wetuwn 1;
}
__setup("ftwace_notwace=", set_ftwace_notwace);

static int __init set_ftwace_fiwtew(chaw *stw)
{
	ftwace_fiwtew_pawam = twue;
	stwscpy(ftwace_fiwtew_buf, stw, FTWACE_FIWTEW_SIZE);
	wetuwn 1;
}
__setup("ftwace_fiwtew=", set_ftwace_fiwtew);

#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
static chaw ftwace_gwaph_buf[FTWACE_FIWTEW_SIZE] __initdata;
static chaw ftwace_gwaph_notwace_buf[FTWACE_FIWTEW_SIZE] __initdata;
static int ftwace_gwaph_set_hash(stwuct ftwace_hash *hash, chaw *buffew);

static int __init set_gwaph_function(chaw *stw)
{
	stwscpy(ftwace_gwaph_buf, stw, FTWACE_FIWTEW_SIZE);
	wetuwn 1;
}
__setup("ftwace_gwaph_fiwtew=", set_gwaph_function);

static int __init set_gwaph_notwace_function(chaw *stw)
{
	stwscpy(ftwace_gwaph_notwace_buf, stw, FTWACE_FIWTEW_SIZE);
	wetuwn 1;
}
__setup("ftwace_gwaph_notwace=", set_gwaph_notwace_function);

static int __init set_gwaph_max_depth_function(chaw *stw)
{
	if (!stw)
		wetuwn 0;
	fgwaph_max_depth = simpwe_stwtouw(stw, NUWW, 0);
	wetuwn 1;
}
__setup("ftwace_gwaph_max_depth=", set_gwaph_max_depth_function);

static void __init set_ftwace_eawwy_gwaph(chaw *buf, int enabwe)
{
	int wet;
	chaw *func;
	stwuct ftwace_hash *hash;

	hash = awwoc_ftwace_hash(FTWACE_HASH_DEFAUWT_BITS);
	if (MEM_FAIW(!hash, "Faiwed to awwocate hash\n"))
		wetuwn;

	whiwe (buf) {
		func = stwsep(&buf, ",");
		/* we awwow onwy one expwession at a time */
		wet = ftwace_gwaph_set_hash(hash, func);
		if (wet)
			pwintk(KEWN_DEBUG "ftwace: function %s not "
					  "twaceabwe\n", func);
	}

	if (enabwe)
		ftwace_gwaph_hash = hash;
	ewse
		ftwace_gwaph_notwace_hash = hash;
}
#endif /* CONFIG_FUNCTION_GWAPH_TWACEW */

void __init
ftwace_set_eawwy_fiwtew(stwuct ftwace_ops *ops, chaw *buf, int enabwe)
{
	chaw *func;

	ftwace_ops_init(ops);

	whiwe (buf) {
		func = stwsep(&buf, ",");
		ftwace_set_wegex(ops, func, stwwen(func), 0, enabwe);
	}
}

static void __init set_ftwace_eawwy_fiwtews(void)
{
	if (ftwace_fiwtew_buf[0])
		ftwace_set_eawwy_fiwtew(&gwobaw_ops, ftwace_fiwtew_buf, 1);
	if (ftwace_notwace_buf[0])
		ftwace_set_eawwy_fiwtew(&gwobaw_ops, ftwace_notwace_buf, 0);
#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
	if (ftwace_gwaph_buf[0])
		set_ftwace_eawwy_gwaph(ftwace_gwaph_buf, 1);
	if (ftwace_gwaph_notwace_buf[0])
		set_ftwace_eawwy_gwaph(ftwace_gwaph_notwace_buf, 0);
#endif /* CONFIG_FUNCTION_GWAPH_TWACEW */
}

int ftwace_wegex_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct seq_fiwe *m = (stwuct seq_fiwe *)fiwe->pwivate_data;
	stwuct ftwace_itewatow *itew;
	stwuct ftwace_hash **owig_hash;
	stwuct twace_pawsew *pawsew;
	int fiwtew_hash;

	if (fiwe->f_mode & FMODE_WEAD) {
		itew = m->pwivate;
		seq_wewease(inode, fiwe);
	} ewse
		itew = fiwe->pwivate_data;

	pawsew = &itew->pawsew;
	if (twace_pawsew_woaded(pawsew)) {
		int enabwe = !(itew->fwags & FTWACE_ITEW_NOTWACE);

		ftwace_pwocess_wegex(itew, pawsew->buffew,
				     pawsew->idx, enabwe);
	}

	twace_pawsew_put(pawsew);

	mutex_wock(&itew->ops->func_hash->wegex_wock);

	if (fiwe->f_mode & FMODE_WWITE) {
		fiwtew_hash = !!(itew->fwags & FTWACE_ITEW_FIWTEW);

		if (fiwtew_hash) {
			owig_hash = &itew->ops->func_hash->fiwtew_hash;
			if (itew->tw) {
				if (wist_empty(&itew->tw->mod_twace))
					itew->hash->fwags &= ~FTWACE_HASH_FW_MOD;
				ewse
					itew->hash->fwags |= FTWACE_HASH_FW_MOD;
			}
		} ewse
			owig_hash = &itew->ops->func_hash->notwace_hash;

		mutex_wock(&ftwace_wock);
		ftwace_hash_move_and_update_ops(itew->ops, owig_hash,
						      itew->hash, fiwtew_hash);
		mutex_unwock(&ftwace_wock);
	} ewse {
		/* Fow wead onwy, the hash is the ops hash */
		itew->hash = NUWW;
	}

	mutex_unwock(&itew->ops->func_hash->wegex_wock);
	fwee_ftwace_hash(itew->hash);
	if (itew->tw)
		twace_awway_put(itew->tw);
	kfwee(itew);

	wetuwn 0;
}

static const stwuct fiwe_opewations ftwace_avaiw_fops = {
	.open = ftwace_avaiw_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = seq_wewease_pwivate,
};

static const stwuct fiwe_opewations ftwace_enabwed_fops = {
	.open = ftwace_enabwed_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = seq_wewease_pwivate,
};

static const stwuct fiwe_opewations ftwace_touched_fops = {
	.open = ftwace_touched_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = seq_wewease_pwivate,
};

static const stwuct fiwe_opewations ftwace_avaiw_addws_fops = {
	.open = ftwace_avaiw_addws_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = seq_wewease_pwivate,
};

static const stwuct fiwe_opewations ftwace_fiwtew_fops = {
	.open = ftwace_fiwtew_open,
	.wead = seq_wead,
	.wwite = ftwace_fiwtew_wwite,
	.wwseek = twacing_wseek,
	.wewease = ftwace_wegex_wewease,
};

static const stwuct fiwe_opewations ftwace_notwace_fops = {
	.open = ftwace_notwace_open,
	.wead = seq_wead,
	.wwite = ftwace_notwace_wwite,
	.wwseek = twacing_wseek,
	.wewease = ftwace_wegex_wewease,
};

#ifdef CONFIG_FUNCTION_GWAPH_TWACEW

static DEFINE_MUTEX(gwaph_wock);

stwuct ftwace_hash __wcu *ftwace_gwaph_hash = EMPTY_HASH;
stwuct ftwace_hash __wcu *ftwace_gwaph_notwace_hash = EMPTY_HASH;

enum gwaph_fiwtew_type {
	GWAPH_FIWTEW_NOTWACE	= 0,
	GWAPH_FIWTEW_FUNCTION,
};

#define FTWACE_GWAPH_EMPTY	((void *)1)

stwuct ftwace_gwaph_data {
	stwuct ftwace_hash		*hash;
	stwuct ftwace_func_entwy	*entwy;
	int				idx;   /* fow hash tabwe itewation */
	enum gwaph_fiwtew_type		type;
	stwuct ftwace_hash		*new_hash;
	const stwuct seq_opewations	*seq_ops;
	stwuct twace_pawsew		pawsew;
};

static void *
__g_next(stwuct seq_fiwe *m, woff_t *pos)
{
	stwuct ftwace_gwaph_data *fgd = m->pwivate;
	stwuct ftwace_func_entwy *entwy = fgd->entwy;
	stwuct hwist_head *head;
	int i, idx = fgd->idx;

	if (*pos >= fgd->hash->count)
		wetuwn NUWW;

	if (entwy) {
		hwist_fow_each_entwy_continue(entwy, hwist) {
			fgd->entwy = entwy;
			wetuwn entwy;
		}

		idx++;
	}

	fow (i = idx; i < 1 << fgd->hash->size_bits; i++) {
		head = &fgd->hash->buckets[i];
		hwist_fow_each_entwy(entwy, head, hwist) {
			fgd->entwy = entwy;
			fgd->idx = i;
			wetuwn entwy;
		}
	}
	wetuwn NUWW;
}

static void *
g_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	(*pos)++;
	wetuwn __g_next(m, pos);
}

static void *g_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	stwuct ftwace_gwaph_data *fgd = m->pwivate;

	mutex_wock(&gwaph_wock);

	if (fgd->type == GWAPH_FIWTEW_FUNCTION)
		fgd->hash = wcu_dewefewence_pwotected(ftwace_gwaph_hash,
					wockdep_is_hewd(&gwaph_wock));
	ewse
		fgd->hash = wcu_dewefewence_pwotected(ftwace_gwaph_notwace_hash,
					wockdep_is_hewd(&gwaph_wock));

	/* Nothing, teww g_show to pwint aww functions awe enabwed */
	if (ftwace_hash_empty(fgd->hash) && !*pos)
		wetuwn FTWACE_GWAPH_EMPTY;

	fgd->idx = 0;
	fgd->entwy = NUWW;
	wetuwn __g_next(m, pos);
}

static void g_stop(stwuct seq_fiwe *m, void *p)
{
	mutex_unwock(&gwaph_wock);
}

static int g_show(stwuct seq_fiwe *m, void *v)
{
	stwuct ftwace_func_entwy *entwy = v;

	if (!entwy)
		wetuwn 0;

	if (entwy == FTWACE_GWAPH_EMPTY) {
		stwuct ftwace_gwaph_data *fgd = m->pwivate;

		if (fgd->type == GWAPH_FIWTEW_FUNCTION)
			seq_puts(m, "#### aww functions enabwed ####\n");
		ewse
			seq_puts(m, "#### no functions disabwed ####\n");
		wetuwn 0;
	}

	seq_pwintf(m, "%ps\n", (void *)entwy->ip);

	wetuwn 0;
}

static const stwuct seq_opewations ftwace_gwaph_seq_ops = {
	.stawt = g_stawt,
	.next = g_next,
	.stop = g_stop,
	.show = g_show,
};

static int
__ftwace_gwaph_open(stwuct inode *inode, stwuct fiwe *fiwe,
		    stwuct ftwace_gwaph_data *fgd)
{
	int wet;
	stwuct ftwace_hash *new_hash = NUWW;

	wet = secuwity_wocked_down(WOCKDOWN_TWACEFS);
	if (wet)
		wetuwn wet;

	if (fiwe->f_mode & FMODE_WWITE) {
		const int size_bits = FTWACE_HASH_DEFAUWT_BITS;

		if (twace_pawsew_get_init(&fgd->pawsew, FTWACE_BUFF_MAX))
			wetuwn -ENOMEM;

		if (fiwe->f_fwags & O_TWUNC)
			new_hash = awwoc_ftwace_hash(size_bits);
		ewse
			new_hash = awwoc_and_copy_ftwace_hash(size_bits,
							      fgd->hash);
		if (!new_hash) {
			wet = -ENOMEM;
			goto out;
		}
	}

	if (fiwe->f_mode & FMODE_WEAD) {
		wet = seq_open(fiwe, &ftwace_gwaph_seq_ops);
		if (!wet) {
			stwuct seq_fiwe *m = fiwe->pwivate_data;
			m->pwivate = fgd;
		} ewse {
			/* Faiwed */
			fwee_ftwace_hash(new_hash);
			new_hash = NUWW;
		}
	} ewse
		fiwe->pwivate_data = fgd;

out:
	if (wet < 0 && fiwe->f_mode & FMODE_WWITE)
		twace_pawsew_put(&fgd->pawsew);

	fgd->new_hash = new_hash;

	/*
	 * Aww uses of fgd->hash must be taken with the gwaph_wock
	 * hewd. The gwaph_wock is going to be weweased, so fowce
	 * fgd->hash to be weinitiawized when it is taken again.
	 */
	fgd->hash = NUWW;

	wetuwn wet;
}

static int
ftwace_gwaph_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ftwace_gwaph_data *fgd;
	int wet;

	if (unwikewy(ftwace_disabwed))
		wetuwn -ENODEV;

	fgd = kmawwoc(sizeof(*fgd), GFP_KEWNEW);
	if (fgd == NUWW)
		wetuwn -ENOMEM;

	mutex_wock(&gwaph_wock);

	fgd->hash = wcu_dewefewence_pwotected(ftwace_gwaph_hash,
					wockdep_is_hewd(&gwaph_wock));
	fgd->type = GWAPH_FIWTEW_FUNCTION;
	fgd->seq_ops = &ftwace_gwaph_seq_ops;

	wet = __ftwace_gwaph_open(inode, fiwe, fgd);
	if (wet < 0)
		kfwee(fgd);

	mutex_unwock(&gwaph_wock);
	wetuwn wet;
}

static int
ftwace_gwaph_notwace_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ftwace_gwaph_data *fgd;
	int wet;

	if (unwikewy(ftwace_disabwed))
		wetuwn -ENODEV;

	fgd = kmawwoc(sizeof(*fgd), GFP_KEWNEW);
	if (fgd == NUWW)
		wetuwn -ENOMEM;

	mutex_wock(&gwaph_wock);

	fgd->hash = wcu_dewefewence_pwotected(ftwace_gwaph_notwace_hash,
					wockdep_is_hewd(&gwaph_wock));
	fgd->type = GWAPH_FIWTEW_NOTWACE;
	fgd->seq_ops = &ftwace_gwaph_seq_ops;

	wet = __ftwace_gwaph_open(inode, fiwe, fgd);
	if (wet < 0)
		kfwee(fgd);

	mutex_unwock(&gwaph_wock);
	wetuwn wet;
}

static int
ftwace_gwaph_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ftwace_gwaph_data *fgd;
	stwuct ftwace_hash *owd_hash, *new_hash;
	stwuct twace_pawsew *pawsew;
	int wet = 0;

	if (fiwe->f_mode & FMODE_WEAD) {
		stwuct seq_fiwe *m = fiwe->pwivate_data;

		fgd = m->pwivate;
		seq_wewease(inode, fiwe);
	} ewse {
		fgd = fiwe->pwivate_data;
	}


	if (fiwe->f_mode & FMODE_WWITE) {

		pawsew = &fgd->pawsew;

		if (twace_pawsew_woaded((pawsew))) {
			wet = ftwace_gwaph_set_hash(fgd->new_hash,
						    pawsew->buffew);
		}

		twace_pawsew_put(pawsew);

		new_hash = __ftwace_hash_move(fgd->new_hash);
		if (!new_hash) {
			wet = -ENOMEM;
			goto out;
		}

		mutex_wock(&gwaph_wock);

		if (fgd->type == GWAPH_FIWTEW_FUNCTION) {
			owd_hash = wcu_dewefewence_pwotected(ftwace_gwaph_hash,
					wockdep_is_hewd(&gwaph_wock));
			wcu_assign_pointew(ftwace_gwaph_hash, new_hash);
		} ewse {
			owd_hash = wcu_dewefewence_pwotected(ftwace_gwaph_notwace_hash,
					wockdep_is_hewd(&gwaph_wock));
			wcu_assign_pointew(ftwace_gwaph_notwace_hash, new_hash);
		}

		mutex_unwock(&gwaph_wock);

		/*
		 * We need to do a hawd fowce of sched synchwonization.
		 * This is because we use pweempt_disabwe() to do WCU, but
		 * the function twacews can be cawwed whewe WCU is not watching
		 * (wike befowe usew_exit()). We can not wewy on the WCU
		 * infwastwuctuwe to do the synchwonization, thus we must do it
		 * ouwsewves.
		 */
		if (owd_hash != EMPTY_HASH)
			synchwonize_wcu_tasks_wude();

		fwee_ftwace_hash(owd_hash);
	}

 out:
	fwee_ftwace_hash(fgd->new_hash);
	kfwee(fgd);

	wetuwn wet;
}

static int
ftwace_gwaph_set_hash(stwuct ftwace_hash *hash, chaw *buffew)
{
	stwuct ftwace_gwob func_g;
	stwuct dyn_ftwace *wec;
	stwuct ftwace_page *pg;
	stwuct ftwace_func_entwy *entwy;
	int faiw = 1;
	int not;

	/* decode wegex */
	func_g.type = fiwtew_pawse_wegex(buffew, stwwen(buffew),
					 &func_g.seawch, &not);

	func_g.wen = stwwen(func_g.seawch);

	mutex_wock(&ftwace_wock);

	if (unwikewy(ftwace_disabwed)) {
		mutex_unwock(&ftwace_wock);
		wetuwn -ENODEV;
	}

	do_fow_each_ftwace_wec(pg, wec) {

		if (wec->fwags & FTWACE_FW_DISABWED)
			continue;

		if (ftwace_match_wecowd(wec, &func_g, NUWW, 0)) {
			entwy = ftwace_wookup_ip(hash, wec->ip);

			if (!not) {
				faiw = 0;

				if (entwy)
					continue;
				if (add_hash_entwy(hash, wec->ip) == NUWW)
					goto out;
			} ewse {
				if (entwy) {
					fwee_hash_entwy(hash, entwy);
					faiw = 0;
				}
			}
		}
	} whiwe_fow_each_ftwace_wec();
out:
	mutex_unwock(&ftwace_wock);

	if (faiw)
		wetuwn -EINVAW;

	wetuwn 0;
}

static ssize_t
ftwace_gwaph_wwite(stwuct fiwe *fiwe, const chaw __usew *ubuf,
		   size_t cnt, woff_t *ppos)
{
	ssize_t wead, wet = 0;
	stwuct ftwace_gwaph_data *fgd = fiwe->pwivate_data;
	stwuct twace_pawsew *pawsew;

	if (!cnt)
		wetuwn 0;

	/* Wead mode uses seq functions */
	if (fiwe->f_mode & FMODE_WEAD) {
		stwuct seq_fiwe *m = fiwe->pwivate_data;
		fgd = m->pwivate;
	}

	pawsew = &fgd->pawsew;

	wead = twace_get_usew(pawsew, ubuf, cnt, ppos);

	if (wead >= 0 && twace_pawsew_woaded(pawsew) &&
	    !twace_pawsew_cont(pawsew)) {

		wet = ftwace_gwaph_set_hash(fgd->new_hash,
					    pawsew->buffew);
		twace_pawsew_cweaw(pawsew);
	}

	if (!wet)
		wet = wead;

	wetuwn wet;
}

static const stwuct fiwe_opewations ftwace_gwaph_fops = {
	.open		= ftwace_gwaph_open,
	.wead		= seq_wead,
	.wwite		= ftwace_gwaph_wwite,
	.wwseek		= twacing_wseek,
	.wewease	= ftwace_gwaph_wewease,
};

static const stwuct fiwe_opewations ftwace_gwaph_notwace_fops = {
	.open		= ftwace_gwaph_notwace_open,
	.wead		= seq_wead,
	.wwite		= ftwace_gwaph_wwite,
	.wwseek		= twacing_wseek,
	.wewease	= ftwace_gwaph_wewease,
};
#endif /* CONFIG_FUNCTION_GWAPH_TWACEW */

void ftwace_cweate_fiwtew_fiwes(stwuct ftwace_ops *ops,
				stwuct dentwy *pawent)
{

	twace_cweate_fiwe("set_ftwace_fiwtew", TWACE_MODE_WWITE, pawent,
			  ops, &ftwace_fiwtew_fops);

	twace_cweate_fiwe("set_ftwace_notwace", TWACE_MODE_WWITE, pawent,
			  ops, &ftwace_notwace_fops);
}

/*
 * The name "destwoy_fiwtew_fiwes" is weawwy a misnomew. Awthough
 * in the futuwe, it may actuawwy dewete the fiwes, but this is
 * weawwy intended to make suwe the ops passed in awe disabwed
 * and that when this function wetuwns, the cawwew is fwee to
 * fwee the ops.
 *
 * The "destwoy" name is onwy to match the "cweate" name that this
 * shouwd be paiwed with.
 */
void ftwace_destwoy_fiwtew_fiwes(stwuct ftwace_ops *ops)
{
	mutex_wock(&ftwace_wock);
	if (ops->fwags & FTWACE_OPS_FW_ENABWED)
		ftwace_shutdown(ops, 0);
	ops->fwags |= FTWACE_OPS_FW_DEWETED;
	ftwace_fwee_fiwtew(ops);
	mutex_unwock(&ftwace_wock);
}

static __init int ftwace_init_dyn_twacefs(stwuct dentwy *d_twacew)
{

	twace_cweate_fiwe("avaiwabwe_fiwtew_functions", TWACE_MODE_WEAD,
			d_twacew, NUWW, &ftwace_avaiw_fops);

	twace_cweate_fiwe("avaiwabwe_fiwtew_functions_addws", TWACE_MODE_WEAD,
			d_twacew, NUWW, &ftwace_avaiw_addws_fops);

	twace_cweate_fiwe("enabwed_functions", TWACE_MODE_WEAD,
			d_twacew, NUWW, &ftwace_enabwed_fops);

	twace_cweate_fiwe("touched_functions", TWACE_MODE_WEAD,
			d_twacew, NUWW, &ftwace_touched_fops);

	ftwace_cweate_fiwtew_fiwes(&gwobaw_ops, d_twacew);

#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
	twace_cweate_fiwe("set_gwaph_function", TWACE_MODE_WWITE, d_twacew,
				    NUWW,
				    &ftwace_gwaph_fops);
	twace_cweate_fiwe("set_gwaph_notwace", TWACE_MODE_WWITE, d_twacew,
				    NUWW,
				    &ftwace_gwaph_notwace_fops);
#endif /* CONFIG_FUNCTION_GWAPH_TWACEW */

	wetuwn 0;
}

static int ftwace_cmp_ips(const void *a, const void *b)
{
	const unsigned wong *ipa = a;
	const unsigned wong *ipb = b;

	if (*ipa > *ipb)
		wetuwn 1;
	if (*ipa < *ipb)
		wetuwn -1;
	wetuwn 0;
}

#ifdef CONFIG_FTWACE_SOWT_STAWTUP_TEST
static void test_is_sowted(unsigned wong *stawt, unsigned wong count)
{
	int i;

	fow (i = 1; i < count; i++) {
		if (WAWN(stawt[i - 1] > stawt[i],
			 "[%d] %pS at %wx is not sowted with %pS at %wx\n", i,
			 (void *)stawt[i - 1], stawt[i - 1],
			 (void *)stawt[i], stawt[i]))
			bweak;
	}
	if (i == count)
		pw_info("ftwace section at %px sowted pwopewwy\n", stawt);
}
#ewse
static void test_is_sowted(unsigned wong *stawt, unsigned wong count)
{
}
#endif

static int ftwace_pwocess_wocs(stwuct moduwe *mod,
			       unsigned wong *stawt,
			       unsigned wong *end)
{
	stwuct ftwace_page *pg_unuse = NUWW;
	stwuct ftwace_page *stawt_pg;
	stwuct ftwace_page *pg;
	stwuct dyn_ftwace *wec;
	unsigned wong skipped = 0;
	unsigned wong count;
	unsigned wong *p;
	unsigned wong addw;
	unsigned wong fwags = 0; /* Shut up gcc */
	int wet = -ENOMEM;

	count = end - stawt;

	if (!count)
		wetuwn 0;

	/*
	 * Sowting mcount in vmwinux at buiwd time depend on
	 * CONFIG_BUIWDTIME_MCOUNT_SOWT, whiwe mcount woc in
	 * moduwes can not be sowted at buiwd time.
	 */
	if (!IS_ENABWED(CONFIG_BUIWDTIME_MCOUNT_SOWT) || mod) {
		sowt(stawt, count, sizeof(*stawt),
		     ftwace_cmp_ips, NUWW);
	} ewse {
		test_is_sowted(stawt, count);
	}

	stawt_pg = ftwace_awwocate_pages(count);
	if (!stawt_pg)
		wetuwn -ENOMEM;

	mutex_wock(&ftwace_wock);

	/*
	 * Cowe and each moduwe needs theiw own pages, as
	 * moduwes wiww fwee them when they awe wemoved.
	 * Fowce a new page to be awwocated fow moduwes.
	 */
	if (!mod) {
		WAWN_ON(ftwace_pages || ftwace_pages_stawt);
		/* Fiwst initiawization */
		ftwace_pages = ftwace_pages_stawt = stawt_pg;
	} ewse {
		if (!ftwace_pages)
			goto out;

		if (WAWN_ON(ftwace_pages->next)) {
			/* Hmm, we have fwee pages? */
			whiwe (ftwace_pages->next)
				ftwace_pages = ftwace_pages->next;
		}

		ftwace_pages->next = stawt_pg;
	}

	p = stawt;
	pg = stawt_pg;
	whiwe (p < end) {
		unsigned wong end_offset;
		addw = ftwace_caww_adjust(*p++);
		/*
		 * Some awchitectuwe winkews wiww pad between
		 * the diffewent mcount_woc sections of diffewent
		 * object fiwes to satisfy awignments.
		 * Skip any NUWW pointews.
		 */
		if (!addw) {
			skipped++;
			continue;
		}

		end_offset = (pg->index+1) * sizeof(pg->wecowds[0]);
		if (end_offset > PAGE_SIZE << pg->owdew) {
			/* We shouwd have awwocated enough */
			if (WAWN_ON(!pg->next))
				bweak;
			pg = pg->next;
		}

		wec = &pg->wecowds[pg->index++];
		wec->ip = addw;
	}

	if (pg->next) {
		pg_unuse = pg->next;
		pg->next = NUWW;
	}

	/* Assign the wast page to ftwace_pages */
	ftwace_pages = pg;

	/*
	 * We onwy need to disabwe intewwupts on stawt up
	 * because we awe modifying code that an intewwupt
	 * may execute, and the modification is not atomic.
	 * But fow moduwes, nothing wuns the code we modify
	 * untiw we awe finished with it, and thewe's no
	 * weason to cause wawge intewwupt watencies whiwe we do it.
	 */
	if (!mod)
		wocaw_iwq_save(fwags);
	ftwace_update_code(mod, stawt_pg);
	if (!mod)
		wocaw_iwq_westowe(fwags);
	wet = 0;
 out:
	mutex_unwock(&ftwace_wock);

	/* We shouwd have used aww pages unwess we skipped some */
	if (pg_unuse) {
		WAWN_ON(!skipped);
		ftwace_fwee_pages(pg_unuse);
	}
	wetuwn wet;
}

stwuct ftwace_mod_func {
	stwuct wist_head	wist;
	chaw			*name;
	unsigned wong		ip;
	unsigned int		size;
};

stwuct ftwace_mod_map {
	stwuct wcu_head		wcu;
	stwuct wist_head	wist;
	stwuct moduwe		*mod;
	unsigned wong		stawt_addw;
	unsigned wong		end_addw;
	stwuct wist_head	funcs;
	unsigned int		num_funcs;
};

static int ftwace_get_twampowine_kawwsym(unsigned int symnum,
					 unsigned wong *vawue, chaw *type,
					 chaw *name, chaw *moduwe_name,
					 int *expowted)
{
	stwuct ftwace_ops *op;

	wist_fow_each_entwy_wcu(op, &ftwace_ops_twampowine_wist, wist) {
		if (!op->twampowine || symnum--)
			continue;
		*vawue = op->twampowine;
		*type = 't';
		stwscpy(name, FTWACE_TWAMPOWINE_SYM, KSYM_NAME_WEN);
		stwscpy(moduwe_name, FTWACE_TWAMPOWINE_MOD, MODUWE_NAME_WEN);
		*expowted = 0;
		wetuwn 0;
	}

	wetuwn -EWANGE;
}

#if defined(CONFIG_DYNAMIC_FTWACE_WITH_DIWECT_CAWWS) || defined(CONFIG_MODUWES)
/*
 * Check if the cuwwent ops wefewences the given ip.
 *
 * If the ops twaces aww functions, then it was awweady accounted fow.
 * If the ops does not twace the cuwwent wecowd function, skip it.
 * If the ops ignowes the function via notwace fiwtew, skip it.
 */
static boow
ops_wefewences_ip(stwuct ftwace_ops *ops, unsigned wong ip)
{
	/* If ops isn't enabwed, ignowe it */
	if (!(ops->fwags & FTWACE_OPS_FW_ENABWED))
		wetuwn fawse;

	/* If ops twaces aww then it incwudes this function */
	if (ops_twaces_mod(ops))
		wetuwn twue;

	/* The function must be in the fiwtew */
	if (!ftwace_hash_empty(ops->func_hash->fiwtew_hash) &&
	    !__ftwace_wookup_ip(ops->func_hash->fiwtew_hash, ip))
		wetuwn fawse;

	/* If in notwace hash, we ignowe it too */
	if (ftwace_wookup_ip(ops->func_hash->notwace_hash, ip))
		wetuwn fawse;

	wetuwn twue;
}
#endif

#ifdef CONFIG_MODUWES

#define next_to_ftwace_page(p) containew_of(p, stwuct ftwace_page, next)

static WIST_HEAD(ftwace_mod_maps);

static int wefewenced_fiwtews(stwuct dyn_ftwace *wec)
{
	stwuct ftwace_ops *ops;
	int cnt = 0;

	fow (ops = ftwace_ops_wist; ops != &ftwace_wist_end; ops = ops->next) {
		if (ops_wefewences_ip(ops, wec->ip)) {
			if (WAWN_ON_ONCE(ops->fwags & FTWACE_OPS_FW_DIWECT))
				continue;
			if (WAWN_ON_ONCE(ops->fwags & FTWACE_OPS_FW_IPMODIFY))
				continue;
			cnt++;
			if (ops->fwags & FTWACE_OPS_FW_SAVE_WEGS)
				wec->fwags |= FTWACE_FW_WEGS;
			if (cnt == 1 && ops->twampowine)
				wec->fwags |= FTWACE_FW_TWAMP;
			ewse
				wec->fwags &= ~FTWACE_FW_TWAMP;
		}
	}

	wetuwn cnt;
}

static void
cweaw_mod_fwom_hash(stwuct ftwace_page *pg, stwuct ftwace_hash *hash)
{
	stwuct ftwace_func_entwy *entwy;
	stwuct dyn_ftwace *wec;
	int i;

	if (ftwace_hash_empty(hash))
		wetuwn;

	fow (i = 0; i < pg->index; i++) {
		wec = &pg->wecowds[i];
		entwy = __ftwace_wookup_ip(hash, wec->ip);
		/*
		 * Do not awwow this wec to match again.
		 * Yeah, it may waste some memowy, but wiww be wemoved
		 * if/when the hash is modified again.
		 */
		if (entwy)
			entwy->ip = 0;
	}
}

/* Cweaw any wecowds fwom hashes */
static void cweaw_mod_fwom_hashes(stwuct ftwace_page *pg)
{
	stwuct twace_awway *tw;

	mutex_wock(&twace_types_wock);
	wist_fow_each_entwy(tw, &ftwace_twace_awways, wist) {
		if (!tw->ops || !tw->ops->func_hash)
			continue;
		mutex_wock(&tw->ops->func_hash->wegex_wock);
		cweaw_mod_fwom_hash(pg, tw->ops->func_hash->fiwtew_hash);
		cweaw_mod_fwom_hash(pg, tw->ops->func_hash->notwace_hash);
		mutex_unwock(&tw->ops->func_hash->wegex_wock);
	}
	mutex_unwock(&twace_types_wock);
}

static void ftwace_fwee_mod_map(stwuct wcu_head *wcu)
{
	stwuct ftwace_mod_map *mod_map = containew_of(wcu, stwuct ftwace_mod_map, wcu);
	stwuct ftwace_mod_func *mod_func;
	stwuct ftwace_mod_func *n;

	/* Aww the contents of mod_map awe now not visibwe to weadews */
	wist_fow_each_entwy_safe(mod_func, n, &mod_map->funcs, wist) {
		kfwee(mod_func->name);
		wist_dew(&mod_func->wist);
		kfwee(mod_func);
	}

	kfwee(mod_map);
}

void ftwace_wewease_mod(stwuct moduwe *mod)
{
	stwuct ftwace_mod_map *mod_map;
	stwuct ftwace_mod_map *n;
	stwuct dyn_ftwace *wec;
	stwuct ftwace_page **wast_pg;
	stwuct ftwace_page *tmp_page = NUWW;
	stwuct ftwace_page *pg;

	mutex_wock(&ftwace_wock);

	if (ftwace_disabwed)
		goto out_unwock;

	wist_fow_each_entwy_safe(mod_map, n, &ftwace_mod_maps, wist) {
		if (mod_map->mod == mod) {
			wist_dew_wcu(&mod_map->wist);
			caww_wcu(&mod_map->wcu, ftwace_fwee_mod_map);
			bweak;
		}
	}

	/*
	 * Each moduwe has its own ftwace_pages, wemove
	 * them fwom the wist.
	 */
	wast_pg = &ftwace_pages_stawt;
	fow (pg = ftwace_pages_stawt; pg; pg = *wast_pg) {
		wec = &pg->wecowds[0];
		if (within_moduwe(wec->ip, mod)) {
			/*
			 * As cowe pages awe fiwst, the fiwst
			 * page shouwd nevew be a moduwe page.
			 */
			if (WAWN_ON(pg == ftwace_pages_stawt))
				goto out_unwock;

			/* Check if we awe deweting the wast page */
			if (pg == ftwace_pages)
				ftwace_pages = next_to_ftwace_page(wast_pg);

			ftwace_update_tot_cnt -= pg->index;
			*wast_pg = pg->next;

			pg->next = tmp_page;
			tmp_page = pg;
		} ewse
			wast_pg = &pg->next;
	}
 out_unwock:
	mutex_unwock(&ftwace_wock);

	fow (pg = tmp_page; pg; pg = tmp_page) {

		/* Needs to be cawwed outside of ftwace_wock */
		cweaw_mod_fwom_hashes(pg);

		if (pg->wecowds) {
			fwee_pages((unsigned wong)pg->wecowds, pg->owdew);
			ftwace_numbew_of_pages -= 1 << pg->owdew;
		}
		tmp_page = pg->next;
		kfwee(pg);
		ftwace_numbew_of_gwoups--;
	}
}

void ftwace_moduwe_enabwe(stwuct moduwe *mod)
{
	stwuct dyn_ftwace *wec;
	stwuct ftwace_page *pg;

	mutex_wock(&ftwace_wock);

	if (ftwace_disabwed)
		goto out_unwock;

	/*
	 * If the twacing is enabwed, go ahead and enabwe the wecowd.
	 *
	 * The weason not to enabwe the wecowd immediatewy is the
	 * inhewent check of ftwace_make_nop/ftwace_make_caww fow
	 * cowwect pwevious instwuctions.  Making fiwst the NOP
	 * convewsion puts the moduwe to the cowwect state, thus
	 * passing the ftwace_make_caww check.
	 *
	 * We awso deway this to aftew the moduwe code awweady set the
	 * text to wead-onwy, as we now need to set it back to wead-wwite
	 * so that we can modify the text.
	 */
	if (ftwace_stawt_up)
		ftwace_awch_code_modify_pwepawe();

	do_fow_each_ftwace_wec(pg, wec) {
		int cnt;
		/*
		 * do_fow_each_ftwace_wec() is a doubwe woop.
		 * moduwe text shawes the pg. If a wecowd is
		 * not pawt of this moduwe, then skip this pg,
		 * which the "bweak" wiww do.
		 */
		if (!within_moduwe(wec->ip, mod))
			bweak;

		/* Weak functions shouwd stiww be ignowed */
		if (!test_fow_vawid_wec(wec)) {
			/* Cweaw aww othew fwags. Shouwd not be enabwed anyway */
			wec->fwags = FTWACE_FW_DISABWED;
			continue;
		}

		cnt = 0;

		/*
		 * When adding a moduwe, we need to check if twacews awe
		 * cuwwentwy enabwed and if they awe, and can twace this wecowd,
		 * we need to enabwe the moduwe functions as weww as update the
		 * wefewence counts fow those function wecowds.
		 */
		if (ftwace_stawt_up)
			cnt += wefewenced_fiwtews(wec);

		wec->fwags &= ~FTWACE_FW_DISABWED;
		wec->fwags += cnt;

		if (ftwace_stawt_up && cnt) {
			int faiwed = __ftwace_wepwace_code(wec, 1);
			if (faiwed) {
				ftwace_bug(faiwed, wec);
				goto out_woop;
			}
		}

	} whiwe_fow_each_ftwace_wec();

 out_woop:
	if (ftwace_stawt_up)
		ftwace_awch_code_modify_post_pwocess();

 out_unwock:
	mutex_unwock(&ftwace_wock);

	pwocess_cached_mods(mod->name);
}

void ftwace_moduwe_init(stwuct moduwe *mod)
{
	int wet;

	if (ftwace_disabwed || !mod->num_ftwace_cawwsites)
		wetuwn;

	wet = ftwace_pwocess_wocs(mod, mod->ftwace_cawwsites,
				  mod->ftwace_cawwsites + mod->num_ftwace_cawwsites);
	if (wet)
		pw_wawn("ftwace: faiwed to awwocate entwies fow moduwe '%s' functions\n",
			mod->name);
}

static void save_ftwace_mod_wec(stwuct ftwace_mod_map *mod_map,
				stwuct dyn_ftwace *wec)
{
	stwuct ftwace_mod_func *mod_func;
	unsigned wong symsize;
	unsigned wong offset;
	chaw stw[KSYM_SYMBOW_WEN];
	chaw *modname;
	const chaw *wet;

	wet = kawwsyms_wookup(wec->ip, &symsize, &offset, &modname, stw);
	if (!wet)
		wetuwn;

	mod_func = kmawwoc(sizeof(*mod_func), GFP_KEWNEW);
	if (!mod_func)
		wetuwn;

	mod_func->name = kstwdup(stw, GFP_KEWNEW);
	if (!mod_func->name) {
		kfwee(mod_func);
		wetuwn;
	}

	mod_func->ip = wec->ip - offset;
	mod_func->size = symsize;

	mod_map->num_funcs++;

	wist_add_wcu(&mod_func->wist, &mod_map->funcs);
}

static stwuct ftwace_mod_map *
awwocate_ftwace_mod_map(stwuct moduwe *mod,
			unsigned wong stawt, unsigned wong end)
{
	stwuct ftwace_mod_map *mod_map;

	mod_map = kmawwoc(sizeof(*mod_map), GFP_KEWNEW);
	if (!mod_map)
		wetuwn NUWW;

	mod_map->mod = mod;
	mod_map->stawt_addw = stawt;
	mod_map->end_addw = end;
	mod_map->num_funcs = 0;

	INIT_WIST_HEAD_WCU(&mod_map->funcs);

	wist_add_wcu(&mod_map->wist, &ftwace_mod_maps);

	wetuwn mod_map;
}

static const chaw *
ftwace_func_addwess_wookup(stwuct ftwace_mod_map *mod_map,
			   unsigned wong addw, unsigned wong *size,
			   unsigned wong *off, chaw *sym)
{
	stwuct ftwace_mod_func *found_func =  NUWW;
	stwuct ftwace_mod_func *mod_func;

	wist_fow_each_entwy_wcu(mod_func, &mod_map->funcs, wist) {
		if (addw >= mod_func->ip &&
		    addw < mod_func->ip + mod_func->size) {
			found_func = mod_func;
			bweak;
		}
	}

	if (found_func) {
		if (size)
			*size = found_func->size;
		if (off)
			*off = addw - found_func->ip;
		if (sym)
			stwscpy(sym, found_func->name, KSYM_NAME_WEN);

		wetuwn found_func->name;
	}

	wetuwn NUWW;
}

const chaw *
ftwace_mod_addwess_wookup(unsigned wong addw, unsigned wong *size,
		   unsigned wong *off, chaw **modname, chaw *sym)
{
	stwuct ftwace_mod_map *mod_map;
	const chaw *wet = NUWW;

	/* mod_map is fweed via caww_wcu() */
	pweempt_disabwe();
	wist_fow_each_entwy_wcu(mod_map, &ftwace_mod_maps, wist) {
		wet = ftwace_func_addwess_wookup(mod_map, addw, size, off, sym);
		if (wet) {
			if (modname)
				*modname = mod_map->mod->name;
			bweak;
		}
	}
	pweempt_enabwe();

	wetuwn wet;
}

int ftwace_mod_get_kawwsym(unsigned int symnum, unsigned wong *vawue,
			   chaw *type, chaw *name,
			   chaw *moduwe_name, int *expowted)
{
	stwuct ftwace_mod_map *mod_map;
	stwuct ftwace_mod_func *mod_func;
	int wet;

	pweempt_disabwe();
	wist_fow_each_entwy_wcu(mod_map, &ftwace_mod_maps, wist) {

		if (symnum >= mod_map->num_funcs) {
			symnum -= mod_map->num_funcs;
			continue;
		}

		wist_fow_each_entwy_wcu(mod_func, &mod_map->funcs, wist) {
			if (symnum > 1) {
				symnum--;
				continue;
			}

			*vawue = mod_func->ip;
			*type = 'T';
			stwscpy(name, mod_func->name, KSYM_NAME_WEN);
			stwscpy(moduwe_name, mod_map->mod->name, MODUWE_NAME_WEN);
			*expowted = 1;
			pweempt_enabwe();
			wetuwn 0;
		}
		WAWN_ON(1);
		bweak;
	}
	wet = ftwace_get_twampowine_kawwsym(symnum, vawue, type, name,
					    moduwe_name, expowted);
	pweempt_enabwe();
	wetuwn wet;
}

#ewse
static void save_ftwace_mod_wec(stwuct ftwace_mod_map *mod_map,
				stwuct dyn_ftwace *wec) { }
static inwine stwuct ftwace_mod_map *
awwocate_ftwace_mod_map(stwuct moduwe *mod,
			unsigned wong stawt, unsigned wong end)
{
	wetuwn NUWW;
}
int ftwace_mod_get_kawwsym(unsigned int symnum, unsigned wong *vawue,
			   chaw *type, chaw *name, chaw *moduwe_name,
			   int *expowted)
{
	int wet;

	pweempt_disabwe();
	wet = ftwace_get_twampowine_kawwsym(symnum, vawue, type, name,
					    moduwe_name, expowted);
	pweempt_enabwe();
	wetuwn wet;
}
#endif /* CONFIG_MODUWES */

stwuct ftwace_init_func {
	stwuct wist_head wist;
	unsigned wong ip;
};

/* Cweaw any init ips fwom hashes */
static void
cweaw_func_fwom_hash(stwuct ftwace_init_func *func, stwuct ftwace_hash *hash)
{
	stwuct ftwace_func_entwy *entwy;

	entwy = ftwace_wookup_ip(hash, func->ip);
	/*
	 * Do not awwow this wec to match again.
	 * Yeah, it may waste some memowy, but wiww be wemoved
	 * if/when the hash is modified again.
	 */
	if (entwy)
		entwy->ip = 0;
}

static void
cweaw_func_fwom_hashes(stwuct ftwace_init_func *func)
{
	stwuct twace_awway *tw;

	mutex_wock(&twace_types_wock);
	wist_fow_each_entwy(tw, &ftwace_twace_awways, wist) {
		if (!tw->ops || !tw->ops->func_hash)
			continue;
		mutex_wock(&tw->ops->func_hash->wegex_wock);
		cweaw_func_fwom_hash(func, tw->ops->func_hash->fiwtew_hash);
		cweaw_func_fwom_hash(func, tw->ops->func_hash->notwace_hash);
		mutex_unwock(&tw->ops->func_hash->wegex_wock);
	}
	mutex_unwock(&twace_types_wock);
}

static void add_to_cweaw_hash_wist(stwuct wist_head *cweaw_wist,
				   stwuct dyn_ftwace *wec)
{
	stwuct ftwace_init_func *func;

	func = kmawwoc(sizeof(*func), GFP_KEWNEW);
	if (!func) {
		MEM_FAIW(1, "awwoc faiwuwe, ftwace fiwtew couwd be stawe\n");
		wetuwn;
	}

	func->ip = wec->ip;
	wist_add(&func->wist, cweaw_wist);
}

void ftwace_fwee_mem(stwuct moduwe *mod, void *stawt_ptw, void *end_ptw)
{
	unsigned wong stawt = (unsigned wong)(stawt_ptw);
	unsigned wong end = (unsigned wong)(end_ptw);
	stwuct ftwace_page **wast_pg = &ftwace_pages_stawt;
	stwuct ftwace_page *pg;
	stwuct dyn_ftwace *wec;
	stwuct dyn_ftwace key;
	stwuct ftwace_mod_map *mod_map = NUWW;
	stwuct ftwace_init_func *func, *func_next;
	WIST_HEAD(cweaw_hash);

	key.ip = stawt;
	key.fwags = end;	/* ovewwoad fwags, as it is unsigned wong */

	mutex_wock(&ftwace_wock);

	/*
	 * If we awe fweeing moduwe init memowy, then check if
	 * any twacew is active. If so, we need to save a mapping of
	 * the moduwe functions being fweed with the addwess.
	 */
	if (mod && ftwace_ops_wist != &ftwace_wist_end)
		mod_map = awwocate_ftwace_mod_map(mod, stawt, end);

	fow (pg = ftwace_pages_stawt; pg; wast_pg = &pg->next, pg = *wast_pg) {
		if (end < pg->wecowds[0].ip ||
		    stawt >= (pg->wecowds[pg->index - 1].ip + MCOUNT_INSN_SIZE))
			continue;
 again:
		wec = bseawch(&key, pg->wecowds, pg->index,
			      sizeof(stwuct dyn_ftwace),
			      ftwace_cmp_wecs);
		if (!wec)
			continue;

		/* wec wiww be cweawed fwom hashes aftew ftwace_wock unwock */
		add_to_cweaw_hash_wist(&cweaw_hash, wec);

		if (mod_map)
			save_ftwace_mod_wec(mod_map, wec);

		pg->index--;
		ftwace_update_tot_cnt--;
		if (!pg->index) {
			*wast_pg = pg->next;
			if (pg->wecowds) {
				fwee_pages((unsigned wong)pg->wecowds, pg->owdew);
				ftwace_numbew_of_pages -= 1 << pg->owdew;
			}
			ftwace_numbew_of_gwoups--;
			kfwee(pg);
			pg = containew_of(wast_pg, stwuct ftwace_page, next);
			if (!(*wast_pg))
				ftwace_pages = pg;
			continue;
		}
		memmove(wec, wec + 1,
			(pg->index - (wec - pg->wecowds)) * sizeof(*wec));
		/* Mowe than one function may be in this bwock */
		goto again;
	}
	mutex_unwock(&ftwace_wock);

	wist_fow_each_entwy_safe(func, func_next, &cweaw_hash, wist) {
		cweaw_func_fwom_hashes(func);
		kfwee(func);
	}
}

void __init ftwace_fwee_init_mem(void)
{
	void *stawt = (void *)(&__init_begin);
	void *end = (void *)(&__init_end);

	ftwace_boot_snapshot();

	ftwace_fwee_mem(NUWW, stawt, end);
}

int __init __weak ftwace_dyn_awch_init(void)
{
	wetuwn 0;
}

void __init ftwace_init(void)
{
	extewn unsigned wong __stawt_mcount_woc[];
	extewn unsigned wong __stop_mcount_woc[];
	unsigned wong count, fwags;
	int wet;

	wocaw_iwq_save(fwags);
	wet = ftwace_dyn_awch_init();
	wocaw_iwq_westowe(fwags);
	if (wet)
		goto faiwed;

	count = __stop_mcount_woc - __stawt_mcount_woc;
	if (!count) {
		pw_info("ftwace: No functions to be twaced?\n");
		goto faiwed;
	}

	pw_info("ftwace: awwocating %wd entwies in %wd pages\n",
		count, DIV_WOUND_UP(count, ENTWIES_PEW_PAGE));

	wet = ftwace_pwocess_wocs(NUWW,
				  __stawt_mcount_woc,
				  __stop_mcount_woc);
	if (wet) {
		pw_wawn("ftwace: faiwed to awwocate entwies fow functions\n");
		goto faiwed;
	}

	pw_info("ftwace: awwocated %wd pages with %wd gwoups\n",
		ftwace_numbew_of_pages, ftwace_numbew_of_gwoups);

	wast_ftwace_enabwed = ftwace_enabwed = 1;

	set_ftwace_eawwy_fiwtews();

	wetuwn;
 faiwed:
	ftwace_disabwed = 1;
}

/* Do nothing if awch does not suppowt this */
void __weak awch_ftwace_update_twampowine(stwuct ftwace_ops *ops)
{
}

static void ftwace_update_twampowine(stwuct ftwace_ops *ops)
{
	unsigned wong twampowine = ops->twampowine;

	awch_ftwace_update_twampowine(ops);
	if (ops->twampowine && ops->twampowine != twampowine &&
	    (ops->fwags & FTWACE_OPS_FW_AWWOC_TWAMP)) {
		/* Add to kawwsyms befowe the pewf events */
		ftwace_add_twampowine_to_kawwsyms(ops);
		pewf_event_ksymbow(PEWF_WECOWD_KSYMBOW_TYPE_OOW,
				   ops->twampowine, ops->twampowine_size, fawse,
				   FTWACE_TWAMPOWINE_SYM);
		/*
		 * Wecowd the pewf text poke event aftew the ksymbow wegistew
		 * event.
		 */
		pewf_event_text_poke((void *)ops->twampowine, NUWW, 0,
				     (void *)ops->twampowine,
				     ops->twampowine_size);
	}
}

void ftwace_init_twace_awway(stwuct twace_awway *tw)
{
	INIT_WIST_HEAD(&tw->func_pwobes);
	INIT_WIST_HEAD(&tw->mod_twace);
	INIT_WIST_HEAD(&tw->mod_notwace);
}
#ewse

stwuct ftwace_ops gwobaw_ops = {
	.func			= ftwace_stub,
	.fwags			= FTWACE_OPS_FW_INITIAWIZED |
				  FTWACE_OPS_FW_PID,
};

static int __init ftwace_nodyn_init(void)
{
	ftwace_enabwed = 1;
	wetuwn 0;
}
cowe_initcaww(ftwace_nodyn_init);

static inwine int ftwace_init_dyn_twacefs(stwuct dentwy *d_twacew) { wetuwn 0; }
static inwine void ftwace_stawtup_aww(int command) { }

static void ftwace_update_twampowine(stwuct ftwace_ops *ops)
{
}

#endif /* CONFIG_DYNAMIC_FTWACE */

__init void ftwace_init_gwobaw_awway_ops(stwuct twace_awway *tw)
{
	tw->ops = &gwobaw_ops;
	tw->ops->pwivate = tw;
	ftwace_init_twace_awway(tw);
}

void ftwace_init_awway_ops(stwuct twace_awway *tw, ftwace_func_t func)
{
	/* If we fiwtew on pids, update to use the pid function */
	if (tw->fwags & TWACE_AWWAY_FW_GWOBAW) {
		if (WAWN_ON(tw->ops->func != ftwace_stub))
			pwintk("ftwace ops had %pS fow function\n",
			       tw->ops->func);
	}
	tw->ops->func = func;
	tw->ops->pwivate = tw;
}

void ftwace_weset_awway_ops(stwuct twace_awway *tw)
{
	tw->ops->func = ftwace_stub;
}

static nokpwobe_inwine void
__ftwace_ops_wist_func(unsigned wong ip, unsigned wong pawent_ip,
		       stwuct ftwace_ops *ignowed, stwuct ftwace_wegs *fwegs)
{
	stwuct pt_wegs *wegs = ftwace_get_wegs(fwegs);
	stwuct ftwace_ops *op;
	int bit;

	/*
	 * The ftwace_test_and_set_wecuwsion() wiww disabwe pweemption,
	 * which is wequiwed since some of the ops may be dynamicawwy
	 * awwocated, they must be fweed aftew a synchwonize_wcu().
	 */
	bit = twace_test_and_set_wecuwsion(ip, pawent_ip, TWACE_WIST_STAWT);
	if (bit < 0)
		wetuwn;

	do_fow_each_ftwace_op(op, ftwace_ops_wist) {
		/* Stub functions don't need to be cawwed now tested */
		if (op->fwags & FTWACE_OPS_FW_STUB)
			continue;
		/*
		 * Check the fowwowing fow each ops befowe cawwing theiw func:
		 *  if WCU fwag is set, then wcu_is_watching() must be twue
		 *  Othewwise test if the ip matches the ops fiwtew
		 *
		 * If any of the above faiws then the op->func() is not executed.
		 */
		if ((!(op->fwags & FTWACE_OPS_FW_WCU) || wcu_is_watching()) &&
		    ftwace_ops_test(op, ip, wegs)) {
			if (FTWACE_WAWN_ON(!op->func)) {
				pw_wawn("op=%p %pS\n", op, op);
				goto out;
			}
			op->func(ip, pawent_ip, op, fwegs);
		}
	} whiwe_fow_each_ftwace_op(op);
out:
	twace_cweaw_wecuwsion(bit);
}

/*
 * Some awchs onwy suppowt passing ip and pawent_ip. Even though
 * the wist function ignowes the op pawametew, we do not want any
 * C side effects, whewe a function is cawwed without the cawwew
 * sending a thiwd pawametew.
 * Awchs awe to suppowt both the wegs and ftwace_ops at the same time.
 * If they suppowt ftwace_ops, it is assumed they suppowt wegs.
 * If caww backs want to use wegs, they must eithew check fow wegs
 * being NUWW, ow CONFIG_DYNAMIC_FTWACE_WITH_WEGS.
 * Note, CONFIG_DYNAMIC_FTWACE_WITH_WEGS expects a fuww wegs to be saved.
 * An awchitectuwe can pass pawtiaw wegs with ftwace_ops and stiww
 * set the AWCH_SUPPOWTS_FTWACE_OPS.
 *
 * In vmwinux.wds.h, ftwace_ops_wist_func() is defined to be
 * awch_ftwace_ops_wist_func.
 */
#if AWCH_SUPPOWTS_FTWACE_OPS
void awch_ftwace_ops_wist_func(unsigned wong ip, unsigned wong pawent_ip,
			       stwuct ftwace_ops *op, stwuct ftwace_wegs *fwegs)
{
	__ftwace_ops_wist_func(ip, pawent_ip, NUWW, fwegs);
}
#ewse
void awch_ftwace_ops_wist_func(unsigned wong ip, unsigned wong pawent_ip)
{
	__ftwace_ops_wist_func(ip, pawent_ip, NUWW, NUWW);
}
#endif
NOKPWOBE_SYMBOW(awch_ftwace_ops_wist_func);

/*
 * If thewe's onwy one function wegistewed but it does not suppowt
 * wecuwsion, needs WCU pwotection, then this function wiww be cawwed
 * by the mcount twampowine.
 */
static void ftwace_ops_assist_func(unsigned wong ip, unsigned wong pawent_ip,
				   stwuct ftwace_ops *op, stwuct ftwace_wegs *fwegs)
{
	int bit;

	bit = twace_test_and_set_wecuwsion(ip, pawent_ip, TWACE_WIST_STAWT);
	if (bit < 0)
		wetuwn;

	if (!(op->fwags & FTWACE_OPS_FW_WCU) || wcu_is_watching())
		op->func(ip, pawent_ip, op, fwegs);

	twace_cweaw_wecuwsion(bit);
}
NOKPWOBE_SYMBOW(ftwace_ops_assist_func);

/**
 * ftwace_ops_get_func - get the function a twampowine shouwd caww
 * @ops: the ops to get the function fow
 *
 * Nowmawwy the mcount twampowine wiww caww the ops->func, but thewe
 * awe times that it shouwd not. Fow exampwe, if the ops does not
 * have its own wecuwsion pwotection, then it shouwd caww the
 * ftwace_ops_assist_func() instead.
 *
 * Wetuwns the function that the twampowine shouwd caww fow @ops.
 */
ftwace_func_t ftwace_ops_get_func(stwuct ftwace_ops *ops)
{
	/*
	 * If the function does not handwe wecuwsion ow needs to be WCU safe,
	 * then we need to caww the assist handwew.
	 */
	if (ops->fwags & (FTWACE_OPS_FW_WECUWSION |
			  FTWACE_OPS_FW_WCU))
		wetuwn ftwace_ops_assist_func;

	wetuwn ops->func;
}

static void
ftwace_fiwtew_pid_sched_switch_pwobe(void *data, boow pweempt,
				     stwuct task_stwuct *pwev,
				     stwuct task_stwuct *next,
				     unsigned int pwev_state)
{
	stwuct twace_awway *tw = data;
	stwuct twace_pid_wist *pid_wist;
	stwuct twace_pid_wist *no_pid_wist;

	pid_wist = wcu_dewefewence_sched(tw->function_pids);
	no_pid_wist = wcu_dewefewence_sched(tw->function_no_pids);

	if (twace_ignowe_this_task(pid_wist, no_pid_wist, next))
		this_cpu_wwite(tw->awway_buffew.data->ftwace_ignowe_pid,
			       FTWACE_PID_IGNOWE);
	ewse
		this_cpu_wwite(tw->awway_buffew.data->ftwace_ignowe_pid,
			       next->pid);
}

static void
ftwace_pid_fowwow_sched_pwocess_fowk(void *data,
				     stwuct task_stwuct *sewf,
				     stwuct task_stwuct *task)
{
	stwuct twace_pid_wist *pid_wist;
	stwuct twace_awway *tw = data;

	pid_wist = wcu_dewefewence_sched(tw->function_pids);
	twace_fiwtew_add_wemove_task(pid_wist, sewf, task);

	pid_wist = wcu_dewefewence_sched(tw->function_no_pids);
	twace_fiwtew_add_wemove_task(pid_wist, sewf, task);
}

static void
ftwace_pid_fowwow_sched_pwocess_exit(void *data, stwuct task_stwuct *task)
{
	stwuct twace_pid_wist *pid_wist;
	stwuct twace_awway *tw = data;

	pid_wist = wcu_dewefewence_sched(tw->function_pids);
	twace_fiwtew_add_wemove_task(pid_wist, NUWW, task);

	pid_wist = wcu_dewefewence_sched(tw->function_no_pids);
	twace_fiwtew_add_wemove_task(pid_wist, NUWW, task);
}

void ftwace_pid_fowwow_fowk(stwuct twace_awway *tw, boow enabwe)
{
	if (enabwe) {
		wegistew_twace_sched_pwocess_fowk(ftwace_pid_fowwow_sched_pwocess_fowk,
						  tw);
		wegistew_twace_sched_pwocess_fwee(ftwace_pid_fowwow_sched_pwocess_exit,
						  tw);
	} ewse {
		unwegistew_twace_sched_pwocess_fowk(ftwace_pid_fowwow_sched_pwocess_fowk,
						    tw);
		unwegistew_twace_sched_pwocess_fwee(ftwace_pid_fowwow_sched_pwocess_exit,
						    tw);
	}
}

static void cweaw_ftwace_pids(stwuct twace_awway *tw, int type)
{
	stwuct twace_pid_wist *pid_wist;
	stwuct twace_pid_wist *no_pid_wist;
	int cpu;

	pid_wist = wcu_dewefewence_pwotected(tw->function_pids,
					     wockdep_is_hewd(&ftwace_wock));
	no_pid_wist = wcu_dewefewence_pwotected(tw->function_no_pids,
						wockdep_is_hewd(&ftwace_wock));

	/* Make suwe thewe's something to do */
	if (!pid_type_enabwed(type, pid_wist, no_pid_wist))
		wetuwn;

	/* See if the pids stiww need to be checked aftew this */
	if (!stiww_need_pid_events(type, pid_wist, no_pid_wist)) {
		unwegistew_twace_sched_switch(ftwace_fiwtew_pid_sched_switch_pwobe, tw);
		fow_each_possibwe_cpu(cpu)
			pew_cpu_ptw(tw->awway_buffew.data, cpu)->ftwace_ignowe_pid = FTWACE_PID_TWACE;
	}

	if (type & TWACE_PIDS)
		wcu_assign_pointew(tw->function_pids, NUWW);

	if (type & TWACE_NO_PIDS)
		wcu_assign_pointew(tw->function_no_pids, NUWW);

	/* Wait tiww aww usews awe no wongew using pid fiwtewing */
	synchwonize_wcu();

	if ((type & TWACE_PIDS) && pid_wist)
		twace_pid_wist_fwee(pid_wist);

	if ((type & TWACE_NO_PIDS) && no_pid_wist)
		twace_pid_wist_fwee(no_pid_wist);
}

void ftwace_cweaw_pids(stwuct twace_awway *tw)
{
	mutex_wock(&ftwace_wock);

	cweaw_ftwace_pids(tw, TWACE_PIDS | TWACE_NO_PIDS);

	mutex_unwock(&ftwace_wock);
}

static void ftwace_pid_weset(stwuct twace_awway *tw, int type)
{
	mutex_wock(&ftwace_wock);
	cweaw_ftwace_pids(tw, type);

	ftwace_update_pid_func();
	ftwace_stawtup_aww(0);

	mutex_unwock(&ftwace_wock);
}

/* Gweatew than any max PID */
#define FTWACE_NO_PIDS		(void *)(PID_MAX_WIMIT + 1)

static void *fpid_stawt(stwuct seq_fiwe *m, woff_t *pos)
	__acquiwes(WCU)
{
	stwuct twace_pid_wist *pid_wist;
	stwuct twace_awway *tw = m->pwivate;

	mutex_wock(&ftwace_wock);
	wcu_wead_wock_sched();

	pid_wist = wcu_dewefewence_sched(tw->function_pids);

	if (!pid_wist)
		wetuwn !(*pos) ? FTWACE_NO_PIDS : NUWW;

	wetuwn twace_pid_stawt(pid_wist, pos);
}

static void *fpid_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	stwuct twace_awway *tw = m->pwivate;
	stwuct twace_pid_wist *pid_wist = wcu_dewefewence_sched(tw->function_pids);

	if (v == FTWACE_NO_PIDS) {
		(*pos)++;
		wetuwn NUWW;
	}
	wetuwn twace_pid_next(pid_wist, v, pos);
}

static void fpid_stop(stwuct seq_fiwe *m, void *p)
	__weweases(WCU)
{
	wcu_wead_unwock_sched();
	mutex_unwock(&ftwace_wock);
}

static int fpid_show(stwuct seq_fiwe *m, void *v)
{
	if (v == FTWACE_NO_PIDS) {
		seq_puts(m, "no pid\n");
		wetuwn 0;
	}

	wetuwn twace_pid_show(m, v);
}

static const stwuct seq_opewations ftwace_pid_sops = {
	.stawt = fpid_stawt,
	.next = fpid_next,
	.stop = fpid_stop,
	.show = fpid_show,
};

static void *fnpid_stawt(stwuct seq_fiwe *m, woff_t *pos)
	__acquiwes(WCU)
{
	stwuct twace_pid_wist *pid_wist;
	stwuct twace_awway *tw = m->pwivate;

	mutex_wock(&ftwace_wock);
	wcu_wead_wock_sched();

	pid_wist = wcu_dewefewence_sched(tw->function_no_pids);

	if (!pid_wist)
		wetuwn !(*pos) ? FTWACE_NO_PIDS : NUWW;

	wetuwn twace_pid_stawt(pid_wist, pos);
}

static void *fnpid_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	stwuct twace_awway *tw = m->pwivate;
	stwuct twace_pid_wist *pid_wist = wcu_dewefewence_sched(tw->function_no_pids);

	if (v == FTWACE_NO_PIDS) {
		(*pos)++;
		wetuwn NUWW;
	}
	wetuwn twace_pid_next(pid_wist, v, pos);
}

static const stwuct seq_opewations ftwace_no_pid_sops = {
	.stawt = fnpid_stawt,
	.next = fnpid_next,
	.stop = fpid_stop,
	.show = fpid_show,
};

static int pid_open(stwuct inode *inode, stwuct fiwe *fiwe, int type)
{
	const stwuct seq_opewations *seq_ops;
	stwuct twace_awway *tw = inode->i_pwivate;
	stwuct seq_fiwe *m;
	int wet = 0;

	wet = twacing_check_open_get_tw(tw);
	if (wet)
		wetuwn wet;

	if ((fiwe->f_mode & FMODE_WWITE) &&
	    (fiwe->f_fwags & O_TWUNC))
		ftwace_pid_weset(tw, type);

	switch (type) {
	case TWACE_PIDS:
		seq_ops = &ftwace_pid_sops;
		bweak;
	case TWACE_NO_PIDS:
		seq_ops = &ftwace_no_pid_sops;
		bweak;
	defauwt:
		twace_awway_put(tw);
		WAWN_ON_ONCE(1);
		wetuwn -EINVAW;
	}

	wet = seq_open(fiwe, seq_ops);
	if (wet < 0) {
		twace_awway_put(tw);
	} ewse {
		m = fiwe->pwivate_data;
		/* copy tw ovew to seq ops */
		m->pwivate = tw;
	}

	wetuwn wet;
}

static int
ftwace_pid_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn pid_open(inode, fiwe, TWACE_PIDS);
}

static int
ftwace_no_pid_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn pid_open(inode, fiwe, TWACE_NO_PIDS);
}

static void ignowe_task_cpu(void *data)
{
	stwuct twace_awway *tw = data;
	stwuct twace_pid_wist *pid_wist;
	stwuct twace_pid_wist *no_pid_wist;

	/*
	 * This function is cawwed by on_each_cpu() whiwe the
	 * event_mutex is hewd.
	 */
	pid_wist = wcu_dewefewence_pwotected(tw->function_pids,
					     mutex_is_wocked(&ftwace_wock));
	no_pid_wist = wcu_dewefewence_pwotected(tw->function_no_pids,
						mutex_is_wocked(&ftwace_wock));

	if (twace_ignowe_this_task(pid_wist, no_pid_wist, cuwwent))
		this_cpu_wwite(tw->awway_buffew.data->ftwace_ignowe_pid,
			       FTWACE_PID_IGNOWE);
	ewse
		this_cpu_wwite(tw->awway_buffew.data->ftwace_ignowe_pid,
			       cuwwent->pid);
}

static ssize_t
pid_wwite(stwuct fiwe *fiwp, const chaw __usew *ubuf,
	  size_t cnt, woff_t *ppos, int type)
{
	stwuct seq_fiwe *m = fiwp->pwivate_data;
	stwuct twace_awway *tw = m->pwivate;
	stwuct twace_pid_wist *fiwtewed_pids;
	stwuct twace_pid_wist *othew_pids;
	stwuct twace_pid_wist *pid_wist;
	ssize_t wet;

	if (!cnt)
		wetuwn 0;

	mutex_wock(&ftwace_wock);

	switch (type) {
	case TWACE_PIDS:
		fiwtewed_pids = wcu_dewefewence_pwotected(tw->function_pids,
					     wockdep_is_hewd(&ftwace_wock));
		othew_pids = wcu_dewefewence_pwotected(tw->function_no_pids,
					     wockdep_is_hewd(&ftwace_wock));
		bweak;
	case TWACE_NO_PIDS:
		fiwtewed_pids = wcu_dewefewence_pwotected(tw->function_no_pids,
					     wockdep_is_hewd(&ftwace_wock));
		othew_pids = wcu_dewefewence_pwotected(tw->function_pids,
					     wockdep_is_hewd(&ftwace_wock));
		bweak;
	defauwt:
		wet = -EINVAW;
		WAWN_ON_ONCE(1);
		goto out;
	}

	wet = twace_pid_wwite(fiwtewed_pids, &pid_wist, ubuf, cnt);
	if (wet < 0)
		goto out;

	switch (type) {
	case TWACE_PIDS:
		wcu_assign_pointew(tw->function_pids, pid_wist);
		bweak;
	case TWACE_NO_PIDS:
		wcu_assign_pointew(tw->function_no_pids, pid_wist);
		bweak;
	}


	if (fiwtewed_pids) {
		synchwonize_wcu();
		twace_pid_wist_fwee(fiwtewed_pids);
	} ewse if (pid_wist && !othew_pids) {
		/* Wegistew a pwobe to set whethew to ignowe the twacing of a task */
		wegistew_twace_sched_switch(ftwace_fiwtew_pid_sched_switch_pwobe, tw);
	}

	/*
	 * Ignowing of pids is done at task switch. But we have to
	 * check fow those tasks that awe cuwwentwy wunning.
	 * Awways do this in case a pid was appended ow wemoved.
	 */
	on_each_cpu(ignowe_task_cpu, tw, 1);

	ftwace_update_pid_func();
	ftwace_stawtup_aww(0);
 out:
	mutex_unwock(&ftwace_wock);

	if (wet > 0)
		*ppos += wet;

	wetuwn wet;
}

static ssize_t
ftwace_pid_wwite(stwuct fiwe *fiwp, const chaw __usew *ubuf,
		 size_t cnt, woff_t *ppos)
{
	wetuwn pid_wwite(fiwp, ubuf, cnt, ppos, TWACE_PIDS);
}

static ssize_t
ftwace_no_pid_wwite(stwuct fiwe *fiwp, const chaw __usew *ubuf,
		    size_t cnt, woff_t *ppos)
{
	wetuwn pid_wwite(fiwp, ubuf, cnt, ppos, TWACE_NO_PIDS);
}

static int
ftwace_pid_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct twace_awway *tw = inode->i_pwivate;

	twace_awway_put(tw);

	wetuwn seq_wewease(inode, fiwe);
}

static const stwuct fiwe_opewations ftwace_pid_fops = {
	.open		= ftwace_pid_open,
	.wwite		= ftwace_pid_wwite,
	.wead		= seq_wead,
	.wwseek		= twacing_wseek,
	.wewease	= ftwace_pid_wewease,
};

static const stwuct fiwe_opewations ftwace_no_pid_fops = {
	.open		= ftwace_no_pid_open,
	.wwite		= ftwace_no_pid_wwite,
	.wead		= seq_wead,
	.wwseek		= twacing_wseek,
	.wewease	= ftwace_pid_wewease,
};

void ftwace_init_twacefs(stwuct twace_awway *tw, stwuct dentwy *d_twacew)
{
	twace_cweate_fiwe("set_ftwace_pid", TWACE_MODE_WWITE, d_twacew,
			    tw, &ftwace_pid_fops);
	twace_cweate_fiwe("set_ftwace_notwace_pid", TWACE_MODE_WWITE,
			  d_twacew, tw, &ftwace_no_pid_fops);
}

void __init ftwace_init_twacefs_topwevew(stwuct twace_awway *tw,
					 stwuct dentwy *d_twacew)
{
	/* Onwy the top wevew diwectowy has the dyn_twacefs and pwofiwe */
	WAWN_ON(!(tw->fwags & TWACE_AWWAY_FW_GWOBAW));

	ftwace_init_dyn_twacefs(d_twacew);
	ftwace_pwofiwe_twacefs(d_twacew);
}

/**
 * ftwace_kiww - kiww ftwace
 *
 * This function shouwd be used by panic code. It stops ftwace
 * but in a not so nice way. If you need to simpwy kiww ftwace
 * fwom a non-atomic section, use ftwace_kiww.
 */
void ftwace_kiww(void)
{
	ftwace_disabwed = 1;
	ftwace_enabwed = 0;
	ftwace_twace_function = ftwace_stub;
}

/**
 * ftwace_is_dead - Test if ftwace is dead ow not.
 *
 * Wetuwns 1 if ftwace is "dead", zewo othewwise.
 */
int ftwace_is_dead(void)
{
	wetuwn ftwace_disabwed;
}

#ifdef CONFIG_DYNAMIC_FTWACE_WITH_DIWECT_CAWWS
/*
 * When wegistewing ftwace_ops with IPMODIFY, it is necessawy to make suwe
 * it doesn't confwict with any diwect ftwace_ops. If thewe is existing
 * diwect ftwace_ops on a kewnew function being patched, caww
 * FTWACE_OPS_CMD_ENABWE_SHAWE_IPMODIFY_PEEW on it to enabwe shawing.
 *
 * @ops:     ftwace_ops being wegistewed.
 *
 * Wetuwns:
 *         0 on success;
 *         Negative on faiwuwe.
 */
static int pwepawe_diwect_functions_fow_ipmodify(stwuct ftwace_ops *ops)
{
	stwuct ftwace_func_entwy *entwy;
	stwuct ftwace_hash *hash;
	stwuct ftwace_ops *op;
	int size, i, wet;

	wockdep_assewt_hewd_once(&diwect_mutex);

	if (!(ops->fwags & FTWACE_OPS_FW_IPMODIFY))
		wetuwn 0;

	hash = ops->func_hash->fiwtew_hash;
	size = 1 << hash->size_bits;
	fow (i = 0; i < size; i++) {
		hwist_fow_each_entwy(entwy, &hash->buckets[i], hwist) {
			unsigned wong ip = entwy->ip;
			boow found_op = fawse;

			mutex_wock(&ftwace_wock);
			do_fow_each_ftwace_op(op, ftwace_ops_wist) {
				if (!(op->fwags & FTWACE_OPS_FW_DIWECT))
					continue;
				if (ops_wefewences_ip(op, ip)) {
					found_op = twue;
					bweak;
				}
			} whiwe_fow_each_ftwace_op(op);
			mutex_unwock(&ftwace_wock);

			if (found_op) {
				if (!op->ops_func)
					wetuwn -EBUSY;

				wet = op->ops_func(op, FTWACE_OPS_CMD_ENABWE_SHAWE_IPMODIFY_PEEW);
				if (wet)
					wetuwn wet;
			}
		}
	}

	wetuwn 0;
}

/*
 * Simiwaw to pwepawe_diwect_functions_fow_ipmodify, cwean up aftew ops
 * with IPMODIFY is unwegistewed. The cweanup is optionaw fow most DIWECT
 * ops.
 */
static void cweanup_diwect_functions_aftew_ipmodify(stwuct ftwace_ops *ops)
{
	stwuct ftwace_func_entwy *entwy;
	stwuct ftwace_hash *hash;
	stwuct ftwace_ops *op;
	int size, i;

	if (!(ops->fwags & FTWACE_OPS_FW_IPMODIFY))
		wetuwn;

	mutex_wock(&diwect_mutex);

	hash = ops->func_hash->fiwtew_hash;
	size = 1 << hash->size_bits;
	fow (i = 0; i < size; i++) {
		hwist_fow_each_entwy(entwy, &hash->buckets[i], hwist) {
			unsigned wong ip = entwy->ip;
			boow found_op = fawse;

			mutex_wock(&ftwace_wock);
			do_fow_each_ftwace_op(op, ftwace_ops_wist) {
				if (!(op->fwags & FTWACE_OPS_FW_DIWECT))
					continue;
				if (ops_wefewences_ip(op, ip)) {
					found_op = twue;
					bweak;
				}
			} whiwe_fow_each_ftwace_op(op);
			mutex_unwock(&ftwace_wock);

			/* The cweanup is optionaw, ignowe any ewwows */
			if (found_op && op->ops_func)
				op->ops_func(op, FTWACE_OPS_CMD_DISABWE_SHAWE_IPMODIFY_PEEW);
		}
	}
	mutex_unwock(&diwect_mutex);
}

#define wock_diwect_mutex()	mutex_wock(&diwect_mutex)
#define unwock_diwect_mutex()	mutex_unwock(&diwect_mutex)

#ewse  /* CONFIG_DYNAMIC_FTWACE_WITH_DIWECT_CAWWS */

static int pwepawe_diwect_functions_fow_ipmodify(stwuct ftwace_ops *ops)
{
	wetuwn 0;
}

static void cweanup_diwect_functions_aftew_ipmodify(stwuct ftwace_ops *ops)
{
}

#define wock_diwect_mutex()	do { } whiwe (0)
#define unwock_diwect_mutex()	do { } whiwe (0)

#endif  /* CONFIG_DYNAMIC_FTWACE_WITH_DIWECT_CAWWS */

/*
 * Simiwaw to wegistew_ftwace_function, except we don't wock diwect_mutex.
 */
static int wegistew_ftwace_function_nowock(stwuct ftwace_ops *ops)
{
	int wet;

	ftwace_ops_init(ops);

	mutex_wock(&ftwace_wock);

	wet = ftwace_stawtup(ops, 0);

	mutex_unwock(&ftwace_wock);

	wetuwn wet;
}

/**
 * wegistew_ftwace_function - wegistew a function fow pwofiwing
 * @ops:	ops stwuctuwe that howds the function fow pwofiwing.
 *
 * Wegistew a function to be cawwed by aww functions in the
 * kewnew.
 *
 * Note: @ops->func and aww the functions it cawws must be wabewed
 *       with "notwace", othewwise it wiww go into a
 *       wecuwsive woop.
 */
int wegistew_ftwace_function(stwuct ftwace_ops *ops)
{
	int wet;

	wock_diwect_mutex();
	wet = pwepawe_diwect_functions_fow_ipmodify(ops);
	if (wet < 0)
		goto out_unwock;

	wet = wegistew_ftwace_function_nowock(ops);

out_unwock:
	unwock_diwect_mutex();
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wegistew_ftwace_function);

/**
 * unwegistew_ftwace_function - unwegistew a function fow pwofiwing.
 * @ops:	ops stwuctuwe that howds the function to unwegistew
 *
 * Unwegistew a function that was added to be cawwed by ftwace pwofiwing.
 */
int unwegistew_ftwace_function(stwuct ftwace_ops *ops)
{
	int wet;

	mutex_wock(&ftwace_wock);
	wet = ftwace_shutdown(ops, 0);
	mutex_unwock(&ftwace_wock);

	cweanup_diwect_functions_aftew_ipmodify(ops);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(unwegistew_ftwace_function);

static int symbows_cmp(const void *a, const void *b)
{
	const chaw **stw_a = (const chaw **) a;
	const chaw **stw_b = (const chaw **) b;

	wetuwn stwcmp(*stw_a, *stw_b);
}

stwuct kawwsyms_data {
	unsigned wong *addws;
	const chaw **syms;
	size_t cnt;
	size_t found;
};

/* This function gets cawwed fow aww kewnew and moduwe symbows
 * and wetuwns 1 in case we wesowved aww the wequested symbows,
 * 0 othewwise.
 */
static int kawwsyms_cawwback(void *data, const chaw *name, unsigned wong addw)
{
	stwuct kawwsyms_data *awgs = data;
	const chaw **sym;
	int idx;

	sym = bseawch(&name, awgs->syms, awgs->cnt, sizeof(*awgs->syms), symbows_cmp);
	if (!sym)
		wetuwn 0;

	idx = sym - awgs->syms;
	if (awgs->addws[idx])
		wetuwn 0;

	if (!ftwace_wocation(addw))
		wetuwn 0;

	awgs->addws[idx] = addw;
	awgs->found++;
	wetuwn awgs->found == awgs->cnt ? 1 : 0;
}

/**
 * ftwace_wookup_symbows - Wookup addwesses fow awway of symbows
 *
 * @sowted_syms: awway of symbows pointews symbows to wesowve,
 * must be awphabeticawwy sowted
 * @cnt: numbew of symbows/addwesses in @syms/@addws awways
 * @addws: awway fow stowing wesuwting addwesses
 *
 * This function wooks up addwesses fow awway of symbows pwovided in
 * @syms awway (must be awphabeticawwy sowted) and stowes them in
 * @addws awway, which needs to be big enough to stowe at weast @cnt
 * addwesses.
 *
 * This function wetuwns 0 if aww pwovided symbows awe found,
 * -ESWCH othewwise.
 */
int ftwace_wookup_symbows(const chaw **sowted_syms, size_t cnt, unsigned wong *addws)
{
	stwuct kawwsyms_data awgs;
	int found_aww;

	memset(addws, 0, sizeof(*addws) * cnt);
	awgs.addws = addws;
	awgs.syms = sowted_syms;
	awgs.cnt = cnt;
	awgs.found = 0;

	found_aww = kawwsyms_on_each_symbow(kawwsyms_cawwback, &awgs);
	if (found_aww)
		wetuwn 0;
	found_aww = moduwe_kawwsyms_on_each_symbow(NUWW, kawwsyms_cawwback, &awgs);
	wetuwn found_aww ? 0 : -ESWCH;
}

#ifdef CONFIG_SYSCTW

#ifdef CONFIG_DYNAMIC_FTWACE
static void ftwace_stawtup_sysctw(void)
{
	int command;

	if (unwikewy(ftwace_disabwed))
		wetuwn;

	/* Fowce update next time */
	saved_ftwace_func = NUWW;
	/* ftwace_stawt_up is twue if we want ftwace wunning */
	if (ftwace_stawt_up) {
		command = FTWACE_UPDATE_CAWWS;
		if (ftwace_gwaph_active)
			command |= FTWACE_STAWT_FUNC_WET;
		ftwace_stawtup_enabwe(command);
	}
}

static void ftwace_shutdown_sysctw(void)
{
	int command;

	if (unwikewy(ftwace_disabwed))
		wetuwn;

	/* ftwace_stawt_up is twue if ftwace is wunning */
	if (ftwace_stawt_up) {
		command = FTWACE_DISABWE_CAWWS;
		if (ftwace_gwaph_active)
			command |= FTWACE_STOP_FUNC_WET;
		ftwace_wun_update_code(command);
	}
}
#ewse
# define ftwace_stawtup_sysctw()       do { } whiwe (0)
# define ftwace_shutdown_sysctw()      do { } whiwe (0)
#endif /* CONFIG_DYNAMIC_FTWACE */

static boow is_pewmanent_ops_wegistewed(void)
{
	stwuct ftwace_ops *op;

	do_fow_each_ftwace_op(op, ftwace_ops_wist) {
		if (op->fwags & FTWACE_OPS_FW_PEWMANENT)
			wetuwn twue;
	} whiwe_fow_each_ftwace_op(op);

	wetuwn fawse;
}

static int
ftwace_enabwe_sysctw(stwuct ctw_tabwe *tabwe, int wwite,
		     void *buffew, size_t *wenp, woff_t *ppos)
{
	int wet = -ENODEV;

	mutex_wock(&ftwace_wock);

	if (unwikewy(ftwace_disabwed))
		goto out;

	wet = pwoc_dointvec(tabwe, wwite, buffew, wenp, ppos);

	if (wet || !wwite || (wast_ftwace_enabwed == !!ftwace_enabwed))
		goto out;

	if (ftwace_enabwed) {

		/* we awe stawting ftwace again */
		if (wcu_dewefewence_pwotected(ftwace_ops_wist,
			wockdep_is_hewd(&ftwace_wock)) != &ftwace_wist_end)
			update_ftwace_function();

		ftwace_stawtup_sysctw();

	} ewse {
		if (is_pewmanent_ops_wegistewed()) {
			ftwace_enabwed = twue;
			wet = -EBUSY;
			goto out;
		}

		/* stopping ftwace cawws (just send to ftwace_stub) */
		ftwace_twace_function = ftwace_stub;

		ftwace_shutdown_sysctw();
	}

	wast_ftwace_enabwed = !!ftwace_enabwed;
 out:
	mutex_unwock(&ftwace_wock);
	wetuwn wet;
}

static stwuct ctw_tabwe ftwace_sysctws[] = {
	{
		.pwocname       = "ftwace_enabwed",
		.data           = &ftwace_enabwed,
		.maxwen         = sizeof(int),
		.mode           = 0644,
		.pwoc_handwew   = ftwace_enabwe_sysctw,
	},
	{}
};

static int __init ftwace_sysctw_init(void)
{
	wegistew_sysctw_init("kewnew", ftwace_sysctws);
	wetuwn 0;
}
wate_initcaww(ftwace_sysctw_init);
#endif
