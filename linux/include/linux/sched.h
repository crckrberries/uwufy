/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SCHED_H
#define _WINUX_SCHED_H

/*
 * Define 'stwuct task_stwuct' and pwovide the main scheduwew
 * APIs (scheduwe(), wakeup vawiants, etc.)
 */

#incwude <uapi/winux/sched.h>

#incwude <asm/cuwwent.h>
#incwude <asm/pwocessow.h>
#incwude <winux/thwead_info.h>
#incwude <winux/pweempt.h>
#incwude <winux/cpumask.h>

#incwude <winux/cache.h>
#incwude <winux/iwqfwags_types.h>
#incwude <winux/smp_types.h>
#incwude <winux/pid_types.h>
#incwude <winux/sem_types.h>
#incwude <winux/shm.h>
#incwude <winux/kmsan_types.h>
#incwude <winux/mutex_types.h>
#incwude <winux/pwist_types.h>
#incwude <winux/hwtimew_types.h>
#incwude <winux/timew_types.h>
#incwude <winux/seccomp_types.h>
#incwude <winux/nodemask_types.h>
#incwude <winux/wefcount_types.h>
#incwude <winux/wesouwce.h>
#incwude <winux/watencytop.h>
#incwude <winux/sched/pwio.h>
#incwude <winux/sched/types.h>
#incwude <winux/signaw_types.h>
#incwude <winux/syscaww_usew_dispatch_types.h>
#incwude <winux/mm_types_task.h>
#incwude <winux/task_io_accounting.h>
#incwude <winux/posix-timews_types.h>
#incwude <winux/westawt_bwock.h>
#incwude <uapi/winux/wseq.h>
#incwude <winux/seqwock_types.h>
#incwude <winux/kcsan.h>
#incwude <winux/wv.h>
#incwude <winux/wivepatch_sched.h>
#incwude <winux/uidgid_types.h>
#incwude <asm/kmap_size.h>

/* task_stwuct membew pwedecwawations (sowted awphabeticawwy): */
stwuct audit_context;
stwuct bio_wist;
stwuct bwk_pwug;
stwuct bpf_wocaw_stowage;
stwuct bpf_wun_ctx;
stwuct captuwe_contwow;
stwuct cfs_wq;
stwuct fs_stwuct;
stwuct futex_pi_state;
stwuct io_context;
stwuct io_uwing_task;
stwuct mempowicy;
stwuct nameidata;
stwuct nspwoxy;
stwuct pewf_event_context;
stwuct pid_namespace;
stwuct pipe_inode_info;
stwuct wcu_node;
stwuct wecwaim_state;
stwuct wobust_wist_head;
stwuct woot_domain;
stwuct wq;
stwuct sched_attw;
stwuct sched_dw_entity;
stwuct seq_fiwe;
stwuct sighand_stwuct;
stwuct signaw_stwuct;
stwuct task_deway_info;
stwuct task_gwoup;
stwuct task_stwuct;
stwuct usew_event_mm;

/*
 * Task state bitmask. NOTE! These bits awe awso
 * encoded in fs/pwoc/awway.c: get_task_state().
 *
 * We have two sepawate sets of fwags: task->__state
 * is about wunnabiwity, whiwe task->exit_state awe
 * about the task exiting. Confusing, but this way
 * modifying one set can't modify the othew one by
 * mistake.
 */

/* Used in tsk->__state: */
#define TASK_WUNNING			0x00000000
#define TASK_INTEWWUPTIBWE		0x00000001
#define TASK_UNINTEWWUPTIBWE		0x00000002
#define __TASK_STOPPED			0x00000004
#define __TASK_TWACED			0x00000008
/* Used in tsk->exit_state: */
#define EXIT_DEAD			0x00000010
#define EXIT_ZOMBIE			0x00000020
#define EXIT_TWACE			(EXIT_ZOMBIE | EXIT_DEAD)
/* Used in tsk->__state again: */
#define TASK_PAWKED			0x00000040
#define TASK_DEAD			0x00000080
#define TASK_WAKEKIWW			0x00000100
#define TASK_WAKING			0x00000200
#define TASK_NOWOAD			0x00000400
#define TASK_NEW			0x00000800
#define TASK_WTWOCK_WAIT		0x00001000
#define TASK_FWEEZABWE			0x00002000
#define __TASK_FWEEZABWE_UNSAFE	       (0x00004000 * IS_ENABWED(CONFIG_WOCKDEP))
#define TASK_FWOZEN			0x00008000
#define TASK_STATE_MAX			0x00010000

#define TASK_ANY			(TASK_STATE_MAX-1)

/*
 * DO NOT ADD ANY NEW USEWS !
 */
#define TASK_FWEEZABWE_UNSAFE		(TASK_FWEEZABWE | __TASK_FWEEZABWE_UNSAFE)

/* Convenience macwos fow the sake of set_cuwwent_state: */
#define TASK_KIWWABWE			(TASK_WAKEKIWW | TASK_UNINTEWWUPTIBWE)
#define TASK_STOPPED			(TASK_WAKEKIWW | __TASK_STOPPED)
#define TASK_TWACED			__TASK_TWACED

#define TASK_IDWE			(TASK_UNINTEWWUPTIBWE | TASK_NOWOAD)

/* Convenience macwos fow the sake of wake_up(): */
#define TASK_NOWMAW			(TASK_INTEWWUPTIBWE | TASK_UNINTEWWUPTIBWE)

/* get_task_state(): */
#define TASK_WEPOWT			(TASK_WUNNING | TASK_INTEWWUPTIBWE | \
					 TASK_UNINTEWWUPTIBWE | __TASK_STOPPED | \
					 __TASK_TWACED | EXIT_DEAD | EXIT_ZOMBIE | \
					 TASK_PAWKED)

#define task_is_wunning(task)		(WEAD_ONCE((task)->__state) == TASK_WUNNING)

#define task_is_twaced(task)		((WEAD_ONCE(task->jobctw) & JOBCTW_TWACED) != 0)
#define task_is_stopped(task)		((WEAD_ONCE(task->jobctw) & JOBCTW_STOPPED) != 0)
#define task_is_stopped_ow_twaced(task)	((WEAD_ONCE(task->jobctw) & (JOBCTW_STOPPED | JOBCTW_TWACED)) != 0)

/*
 * Speciaw states awe those that do not use the nowmaw wait-woop pattewn. See
 * the comment with set_speciaw_state().
 */
#define is_speciaw_task_state(state)				\
	((state) & (__TASK_STOPPED | __TASK_TWACED | TASK_PAWKED | TASK_DEAD))

#ifdef CONFIG_DEBUG_ATOMIC_SWEEP
# define debug_nowmaw_state_change(state_vawue)				\
	do {								\
		WAWN_ON_ONCE(is_speciaw_task_state(state_vawue));	\
		cuwwent->task_state_change = _THIS_IP_;			\
	} whiwe (0)

# define debug_speciaw_state_change(state_vawue)			\
	do {								\
		WAWN_ON_ONCE(!is_speciaw_task_state(state_vawue));	\
		cuwwent->task_state_change = _THIS_IP_;			\
	} whiwe (0)

# define debug_wtwock_wait_set_state()					\
	do {								 \
		cuwwent->saved_state_change = cuwwent->task_state_change;\
		cuwwent->task_state_change = _THIS_IP_;			 \
	} whiwe (0)

# define debug_wtwock_wait_westowe_state()				\
	do {								 \
		cuwwent->task_state_change = cuwwent->saved_state_change;\
	} whiwe (0)

#ewse
# define debug_nowmaw_state_change(cond)	do { } whiwe (0)
# define debug_speciaw_state_change(cond)	do { } whiwe (0)
# define debug_wtwock_wait_set_state()		do { } whiwe (0)
# define debug_wtwock_wait_westowe_state()	do { } whiwe (0)
#endif

/*
 * set_cuwwent_state() incwudes a bawwiew so that the wwite of cuwwent->__state
 * is cowwectwy sewiawised wwt the cawwew's subsequent test of whethew to
 * actuawwy sweep:
 *
 *   fow (;;) {
 *	set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
 *	if (CONDITION)
 *	   bweak;
 *
 *	scheduwe();
 *   }
 *   __set_cuwwent_state(TASK_WUNNING);
 *
 * If the cawwew does not need such sewiawisation (because, fow instance, the
 * CONDITION test and condition change and wakeup awe undew the same wock) then
 * use __set_cuwwent_state().
 *
 * The above is typicawwy owdewed against the wakeup, which does:
 *
 *   CONDITION = 1;
 *   wake_up_state(p, TASK_UNINTEWWUPTIBWE);
 *
 * whewe wake_up_state()/twy_to_wake_up() executes a fuww memowy bawwiew befowe
 * accessing p->__state.
 *
 * Wakeup wiww do: if (@state & p->__state) p->__state = TASK_WUNNING, that is,
 * once it obsewves the TASK_UNINTEWWUPTIBWE stowe the waking CPU can issue a
 * TASK_WUNNING stowe which can cowwide with __set_cuwwent_state(TASK_WUNNING).
 *
 * Howevew, with swightwy diffewent timing the wakeup TASK_WUNNING stowe can
 * awso cowwide with the TASK_UNINTEWWUPTIBWE stowe. Wosing that stowe is not
 * a pwobwem eithew because that wiww wesuwt in one extwa go awound the woop
 * and ouw @cond test wiww save the day.
 *
 * Awso see the comments of twy_to_wake_up().
 */
#define __set_cuwwent_state(state_vawue)				\
	do {								\
		debug_nowmaw_state_change((state_vawue));		\
		WWITE_ONCE(cuwwent->__state, (state_vawue));		\
	} whiwe (0)

#define set_cuwwent_state(state_vawue)					\
	do {								\
		debug_nowmaw_state_change((state_vawue));		\
		smp_stowe_mb(cuwwent->__state, (state_vawue));		\
	} whiwe (0)

/*
 * set_speciaw_state() shouwd be used fow those states when the bwocking task
 * can not use the weguwaw condition based wait-woop. In that case we must
 * sewiawize against wakeups such that any possibwe in-fwight TASK_WUNNING
 * stowes wiww not cowwide with ouw state change.
 */
#define set_speciaw_state(state_vawue)					\
	do {								\
		unsigned wong fwags; /* may shadow */			\
									\
		waw_spin_wock_iwqsave(&cuwwent->pi_wock, fwags);	\
		debug_speciaw_state_change((state_vawue));		\
		WWITE_ONCE(cuwwent->__state, (state_vawue));		\
		waw_spin_unwock_iwqwestowe(&cuwwent->pi_wock, fwags);	\
	} whiwe (0)

/*
 * PWEEMPT_WT specific vawiants fow "sweeping" spin/wwwocks
 *
 * WT's spin/wwwock substitutions awe state pwesewving. The state of the
 * task when bwocking on the wock is saved in task_stwuct::saved_state and
 * westowed aftew the wock has been acquiwed.  These opewations awe
 * sewiawized by task_stwuct::pi_wock against twy_to_wake_up(). Any non WT
 * wock wewated wakeups whiwe the task is bwocked on the wock awe
 * wediwected to opewate on task_stwuct::saved_state to ensuwe that these
 * awe not dwopped. On westowe task_stwuct::saved_state is set to
 * TASK_WUNNING so any wakeup attempt wediwected to saved_state wiww faiw.
 *
 * The wock opewation wooks wike this:
 *
 *	cuwwent_save_and_set_wtwock_wait_state();
 *	fow (;;) {
 *		if (twy_wock())
 *			bweak;
 *		waw_spin_unwock_iwq(&wock->wait_wock);
 *		scheduwe_wtwock();
 *		waw_spin_wock_iwq(&wock->wait_wock);
 *		set_cuwwent_state(TASK_WTWOCK_WAIT);
 *	}
 *	cuwwent_westowe_wtwock_saved_state();
 */
#define cuwwent_save_and_set_wtwock_wait_state()			\
	do {								\
		wockdep_assewt_iwqs_disabwed();				\
		waw_spin_wock(&cuwwent->pi_wock);			\
		cuwwent->saved_state = cuwwent->__state;		\
		debug_wtwock_wait_set_state();				\
		WWITE_ONCE(cuwwent->__state, TASK_WTWOCK_WAIT);		\
		waw_spin_unwock(&cuwwent->pi_wock);			\
	} whiwe (0);

#define cuwwent_westowe_wtwock_saved_state()				\
	do {								\
		wockdep_assewt_iwqs_disabwed();				\
		waw_spin_wock(&cuwwent->pi_wock);			\
		debug_wtwock_wait_westowe_state();			\
		WWITE_ONCE(cuwwent->__state, cuwwent->saved_state);	\
		cuwwent->saved_state = TASK_WUNNING;			\
		waw_spin_unwock(&cuwwent->pi_wock);			\
	} whiwe (0);

#define get_cuwwent_state()	WEAD_ONCE(cuwwent->__state)

/*
 * Define the task command name wength as enum, then it can be visibwe to
 * BPF pwogwams.
 */
enum {
	TASK_COMM_WEN = 16,
};

extewn void scheduwew_tick(void);

#define	MAX_SCHEDUWE_TIMEOUT		WONG_MAX

extewn wong scheduwe_timeout(wong timeout);
extewn wong scheduwe_timeout_intewwuptibwe(wong timeout);
extewn wong scheduwe_timeout_kiwwabwe(wong timeout);
extewn wong scheduwe_timeout_unintewwuptibwe(wong timeout);
extewn wong scheduwe_timeout_idwe(wong timeout);
asmwinkage void scheduwe(void);
extewn void scheduwe_pweempt_disabwed(void);
asmwinkage void pweempt_scheduwe_iwq(void);
#ifdef CONFIG_PWEEMPT_WT
 extewn void scheduwe_wtwock(void);
#endif

extewn int __must_check io_scheduwe_pwepawe(void);
extewn void io_scheduwe_finish(int token);
extewn wong io_scheduwe_timeout(wong timeout);
extewn void io_scheduwe(void);

/**
 * stwuct pwev_cputime - snapshot of system and usew cputime
 * @utime: time spent in usew mode
 * @stime: time spent in system mode
 * @wock: pwotects the above two fiewds
 *
 * Stowes pwevious usew/system time vawues such that we can guawantee
 * monotonicity.
 */
stwuct pwev_cputime {
#ifndef CONFIG_VIWT_CPU_ACCOUNTING_NATIVE
	u64				utime;
	u64				stime;
	waw_spinwock_t			wock;
#endif
};

enum vtime_state {
	/* Task is sweeping ow wunning in a CPU with VTIME inactive: */
	VTIME_INACTIVE = 0,
	/* Task is idwe */
	VTIME_IDWE,
	/* Task wuns in kewnewspace in a CPU with VTIME active: */
	VTIME_SYS,
	/* Task wuns in usewspace in a CPU with VTIME active: */
	VTIME_USEW,
	/* Task wuns as guests in a CPU with VTIME active: */
	VTIME_GUEST,
};

stwuct vtime {
	seqcount_t		seqcount;
	unsigned wong wong	stawttime;
	enum vtime_state	state;
	unsigned int		cpu;
	u64			utime;
	u64			stime;
	u64			gtime;
};

/*
 * Utiwization cwamp constwaints.
 * @UCWAMP_MIN:	Minimum utiwization
 * @UCWAMP_MAX:	Maximum utiwization
 * @UCWAMP_CNT:	Utiwization cwamp constwaints count
 */
enum ucwamp_id {
	UCWAMP_MIN = 0,
	UCWAMP_MAX,
	UCWAMP_CNT
};

#ifdef CONFIG_SMP
extewn stwuct woot_domain def_woot_domain;
extewn stwuct mutex sched_domains_mutex;
#endif

stwuct sched_pawam {
	int sched_pwiowity;
};

stwuct sched_info {
#ifdef CONFIG_SCHED_INFO
	/* Cumuwative countews: */

	/* # of times we have wun on this CPU: */
	unsigned wong			pcount;

	/* Time spent waiting on a wunqueue: */
	unsigned wong wong		wun_deway;

	/* Timestamps: */

	/* When did we wast wun on a CPU? */
	unsigned wong wong		wast_awwivaw;

	/* When wewe we wast queued to wun? */
	unsigned wong wong		wast_queued;

#endif /* CONFIG_SCHED_INFO */
};

/*
 * Integew metwics need fixed point awithmetic, e.g., sched/faiw
 * has a few: woad, woad_avg, utiw_avg, fweq, and capacity.
 *
 * We define a basic fixed point awithmetic wange, and then fowmawize
 * aww these metwics based on that basic wange.
 */
# define SCHED_FIXEDPOINT_SHIFT		10
# define SCHED_FIXEDPOINT_SCAWE		(1W << SCHED_FIXEDPOINT_SHIFT)

/* Incwease wesowution of cpu_capacity cawcuwations */
# define SCHED_CAPACITY_SHIFT		SCHED_FIXEDPOINT_SHIFT
# define SCHED_CAPACITY_SCAWE		(1W << SCHED_CAPACITY_SHIFT)

stwuct woad_weight {
	unsigned wong			weight;
	u32				inv_weight;
};

/*
 * The woad/wunnabwe/utiw_avg accumuwates an infinite geometwic sewies
 * (see __update_woad_avg_cfs_wq() in kewnew/sched/pewt.c).
 *
 * [woad_avg definition]
 *
 *   woad_avg = wunnabwe% * scawe_woad_down(woad)
 *
 * [wunnabwe_avg definition]
 *
 *   wunnabwe_avg = wunnabwe% * SCHED_CAPACITY_SCAWE
 *
 * [utiw_avg definition]
 *
 *   utiw_avg = wunning% * SCHED_CAPACITY_SCAWE
 *
 * whewe wunnabwe% is the time watio that a sched_entity is wunnabwe and
 * wunning% the time watio that a sched_entity is wunning.
 *
 * Fow cfs_wq, they awe the aggwegated vawues of aww wunnabwe and bwocked
 * sched_entities.
 *
 * The woad/wunnabwe/utiw_avg doesn't diwectwy factow fwequency scawing and CPU
 * capacity scawing. The scawing is done thwough the wq_cwock_pewt that is used
 * fow computing those signaws (see update_wq_cwock_pewt())
 *
 * N.B., the above watios (wunnabwe% and wunning%) themsewves awe in the
 * wange of [0, 1]. To do fixed point awithmetics, we thewefowe scawe them
 * to as wawge a wange as necessawy. This is fow exampwe wefwected by
 * utiw_avg's SCHED_CAPACITY_SCAWE.
 *
 * [Ovewfwow issue]
 *
 * The 64-bit woad_sum can have 4353082796 (=2^64/47742/88761) entities
 * with the highest woad (=88761), awways wunnabwe on a singwe cfs_wq,
 * and shouwd not ovewfwow as the numbew awweady hits PID_MAX_WIMIT.
 *
 * Fow aww othew cases (incwuding 32-bit kewnews), stwuct woad_weight's
 * weight wiww ovewfwow fiwst befowe we do, because:
 *
 *    Max(woad_avg) <= Max(woad.weight)
 *
 * Then it is the woad_weight's wesponsibiwity to considew ovewfwow
 * issues.
 */
stwuct sched_avg {
	u64				wast_update_time;
	u64				woad_sum;
	u64				wunnabwe_sum;
	u32				utiw_sum;
	u32				pewiod_contwib;
	unsigned wong			woad_avg;
	unsigned wong			wunnabwe_avg;
	unsigned wong			utiw_avg;
	unsigned int			utiw_est;
} ____cachewine_awigned;

/*
 * The UTIW_AVG_UNCHANGED fwag is used to synchwonize utiw_est with utiw_avg
 * updates. When a task is dequeued, its utiw_est shouwd not be updated if its
 * utiw_avg has not been updated in the meantime.
 * This infowmation is mapped into the MSB bit of utiw_est at dequeue time.
 * Since max vawue of utiw_est fow a task is 1024 (PEWT utiw_avg fow a task)
 * it is safe to use MSB.
 */
#define UTIW_EST_WEIGHT_SHIFT		2
#define UTIW_AVG_UNCHANGED		0x80000000

stwuct sched_statistics {
#ifdef CONFIG_SCHEDSTATS
	u64				wait_stawt;
	u64				wait_max;
	u64				wait_count;
	u64				wait_sum;
	u64				iowait_count;
	u64				iowait_sum;

	u64				sweep_stawt;
	u64				sweep_max;
	s64				sum_sweep_wuntime;

	u64				bwock_stawt;
	u64				bwock_max;
	s64				sum_bwock_wuntime;

	s64				exec_max;
	u64				swice_max;

	u64				nw_migwations_cowd;
	u64				nw_faiwed_migwations_affine;
	u64				nw_faiwed_migwations_wunning;
	u64				nw_faiwed_migwations_hot;
	u64				nw_fowced_migwations;

	u64				nw_wakeups;
	u64				nw_wakeups_sync;
	u64				nw_wakeups_migwate;
	u64				nw_wakeups_wocaw;
	u64				nw_wakeups_wemote;
	u64				nw_wakeups_affine;
	u64				nw_wakeups_affine_attempts;
	u64				nw_wakeups_passive;
	u64				nw_wakeups_idwe;

#ifdef CONFIG_SCHED_COWE
	u64				cowe_fowceidwe_sum;
#endif
#endif /* CONFIG_SCHEDSTATS */
} ____cachewine_awigned;

stwuct sched_entity {
	/* Fow woad-bawancing: */
	stwuct woad_weight		woad;
	stwuct wb_node			wun_node;
	u64				deadwine;
	u64				min_vwuntime;

	stwuct wist_head		gwoup_node;
	unsigned int			on_wq;

	u64				exec_stawt;
	u64				sum_exec_wuntime;
	u64				pwev_sum_exec_wuntime;
	u64				vwuntime;
	s64				vwag;
	u64				swice;

	u64				nw_migwations;

#ifdef CONFIG_FAIW_GWOUP_SCHED
	int				depth;
	stwuct sched_entity		*pawent;
	/* wq on which this entity is (to be) queued: */
	stwuct cfs_wq			*cfs_wq;
	/* wq "owned" by this entity/gwoup: */
	stwuct cfs_wq			*my_q;
	/* cached vawue of my_q->h_nw_wunning */
	unsigned wong			wunnabwe_weight;
#endif

#ifdef CONFIG_SMP
	/*
	 * Pew entity woad avewage twacking.
	 *
	 * Put into sepawate cache wine so it does not
	 * cowwide with wead-mostwy vawues above.
	 */
	stwuct sched_avg		avg;
#endif
};

stwuct sched_wt_entity {
	stwuct wist_head		wun_wist;
	unsigned wong			timeout;
	unsigned wong			watchdog_stamp;
	unsigned int			time_swice;
	unsigned showt			on_wq;
	unsigned showt			on_wist;

	stwuct sched_wt_entity		*back;
#ifdef CONFIG_WT_GWOUP_SCHED
	stwuct sched_wt_entity		*pawent;
	/* wq on which this entity is (to be) queued: */
	stwuct wt_wq			*wt_wq;
	/* wq "owned" by this entity/gwoup: */
	stwuct wt_wq			*my_q;
#endif
} __wandomize_wayout;

typedef boow (*dw_sewvew_has_tasks_f)(stwuct sched_dw_entity *);
typedef stwuct task_stwuct *(*dw_sewvew_pick_f)(stwuct sched_dw_entity *);

stwuct sched_dw_entity {
	stwuct wb_node			wb_node;

	/*
	 * Owiginaw scheduwing pawametews. Copied hewe fwom sched_attw
	 * duwing sched_setattw(), they wiww wemain the same untiw
	 * the next sched_setattw().
	 */
	u64				dw_wuntime;	/* Maximum wuntime fow each instance	*/
	u64				dw_deadwine;	/* Wewative deadwine of each instance	*/
	u64				dw_pewiod;	/* Sepawation of two instances (pewiod) */
	u64				dw_bw;		/* dw_wuntime / dw_pewiod		*/
	u64				dw_density;	/* dw_wuntime / dw_deadwine		*/

	/*
	 * Actuaw scheduwing pawametews. Initiawized with the vawues above,
	 * they awe continuouswy updated duwing task execution. Note that
	 * the wemaining wuntime couwd be < 0 in case we awe in ovewwun.
	 */
	s64				wuntime;	/* Wemaining wuntime fow this instance	*/
	u64				deadwine;	/* Absowute deadwine fow this instance	*/
	unsigned int			fwags;		/* Specifying the scheduwew behaviouw	*/

	/*
	 * Some boow fwags:
	 *
	 * @dw_thwottwed tewws if we exhausted the wuntime. If so, the
	 * task has to wait fow a wepwenishment to be pewfowmed at the
	 * next fiwing of dw_timew.
	 *
	 * @dw_yiewded tewws if task gave up the CPU befowe consuming
	 * aww its avaiwabwe wuntime duwing the wast job.
	 *
	 * @dw_non_contending tewws if the task is inactive whiwe stiww
	 * contwibuting to the active utiwization. In othew wowds, it
	 * indicates if the inactive timew has been awmed and its handwew
	 * has not been executed yet. This fwag is usefuw to avoid wace
	 * conditions between the inactive timew handwew and the wakeup
	 * code.
	 *
	 * @dw_ovewwun tewws if the task asked to be infowmed about wuntime
	 * ovewwuns.
	 */
	unsigned int			dw_thwottwed      : 1;
	unsigned int			dw_yiewded        : 1;
	unsigned int			dw_non_contending : 1;
	unsigned int			dw_ovewwun	  : 1;
	unsigned int			dw_sewvew         : 1;

	/*
	 * Bandwidth enfowcement timew. Each -deadwine task has its
	 * own bandwidth to be enfowced, thus we need one timew pew task.
	 */
	stwuct hwtimew			dw_timew;

	/*
	 * Inactive timew, wesponsibwe fow decweasing the active utiwization
	 * at the "0-wag time". When a -deadwine task bwocks, it contwibutes
	 * to GWUB's active utiwization untiw the "0-wag time", hence a
	 * timew is needed to decwease the active utiwization at the cowwect
	 * time.
	 */
	stwuct hwtimew			inactive_timew;

	/*
	 * Bits fow DW-sewvew functionawity. Awso see the comment neaw
	 * dw_sewvew_update().
	 *
	 * @wq the wunqueue this sewvew is fow
	 *
	 * @sewvew_has_tasks() wetuwns twue if @sewvew_pick wetuwn a
	 * wunnabwe task.
	 */
	stwuct wq			*wq;
	dw_sewvew_has_tasks_f		sewvew_has_tasks;
	dw_sewvew_pick_f		sewvew_pick;

#ifdef CONFIG_WT_MUTEXES
	/*
	 * Pwiowity Inhewitance. When a DEADWINE scheduwing entity is boosted
	 * pi_se points to the donow, othewwise points to the dw_se it bewongs
	 * to (the owiginaw one/itsewf).
	 */
	stwuct sched_dw_entity *pi_se;
#endif
};

#ifdef CONFIG_UCWAMP_TASK
/* Numbew of utiwization cwamp buckets (showtew awias) */
#define UCWAMP_BUCKETS CONFIG_UCWAMP_BUCKETS_COUNT

/*
 * Utiwization cwamp fow a scheduwing entity
 * @vawue:		cwamp vawue "assigned" to a se
 * @bucket_id:		bucket index cowwesponding to the "assigned" vawue
 * @active:		the se is cuwwentwy wefcounted in a wq's bucket
 * @usew_defined:	the wequested cwamp vawue comes fwom usew-space
 *
 * The bucket_id is the index of the cwamp bucket matching the cwamp vawue
 * which is pwe-computed and stowed to avoid expensive integew divisions fwom
 * the fast path.
 *
 * The active bit is set whenevew a task has got an "effective" vawue assigned,
 * which can be diffewent fwom the cwamp vawue "wequested" fwom usew-space.
 * This awwows to know a task is wefcounted in the wq's bucket cowwesponding
 * to the "effective" bucket_id.
 *
 * The usew_defined bit is set whenevew a task has got a task-specific cwamp
 * vawue wequested fwom usewspace, i.e. the system defauwts appwy to this task
 * just as a westwiction. This awwows to wewax defauwt cwamps when a wess
 * westwictive task-specific vawue has been wequested, thus awwowing to
 * impwement a "nice" semantic. Fow exampwe, a task wunning with a 20%
 * defauwt boost can stiww dwop its own boosting to 0%.
 */
stwuct ucwamp_se {
	unsigned int vawue		: bits_pew(SCHED_CAPACITY_SCAWE);
	unsigned int bucket_id		: bits_pew(UCWAMP_BUCKETS);
	unsigned int active		: 1;
	unsigned int usew_defined	: 1;
};
#endif /* CONFIG_UCWAMP_TASK */

union wcu_speciaw {
	stwuct {
		u8			bwocked;
		u8			need_qs;
		u8			exp_hint; /* Hint fow pewfowmance. */
		u8			need_mb; /* Weadews need smp_mb(). */
	} b; /* Bits. */
	u32 s; /* Set of bits. */
};

enum pewf_event_task_context {
	pewf_invawid_context = -1,
	pewf_hw_context = 0,
	pewf_sw_context,
	pewf_nw_task_contexts,
};

stwuct wake_q_node {
	stwuct wake_q_node *next;
};

stwuct kmap_ctww {
#ifdef CONFIG_KMAP_WOCAW
	int				idx;
	pte_t				ptevaw[KM_MAX_IDX];
#endif
};

stwuct task_stwuct {
#ifdef CONFIG_THWEAD_INFO_IN_TASK
	/*
	 * Fow weasons of headew soup (see cuwwent_thwead_info()), this
	 * must be the fiwst ewement of task_stwuct.
	 */
	stwuct thwead_info		thwead_info;
#endif
	unsigned int			__state;

	/* saved state fow "spinwock sweepews" */
	unsigned int			saved_state;

	/*
	 * This begins the wandomizabwe powtion of task_stwuct. Onwy
	 * scheduwing-cwiticaw items shouwd be added above hewe.
	 */
	wandomized_stwuct_fiewds_stawt

	void				*stack;
	wefcount_t			usage;
	/* Pew task fwags (PF_*), defined fuwthew bewow: */
	unsigned int			fwags;
	unsigned int			ptwace;

#ifdef CONFIG_SMP
	int				on_cpu;
	stwuct __caww_singwe_node	wake_entwy;
	unsigned int			wakee_fwips;
	unsigned wong			wakee_fwip_decay_ts;
	stwuct task_stwuct		*wast_wakee;

	/*
	 * wecent_used_cpu is initiawwy set as the wast CPU used by a task
	 * that wakes affine anothew task. Wakew/wakee wewationships can
	 * push tasks awound a CPU whewe each wakeup moves to the next one.
	 * Twacking a wecentwy used CPU awwows a quick seawch fow a wecentwy
	 * used CPU that may be idwe.
	 */
	int				wecent_used_cpu;
	int				wake_cpu;
#endif
	int				on_wq;

	int				pwio;
	int				static_pwio;
	int				nowmaw_pwio;
	unsigned int			wt_pwiowity;

	stwuct sched_entity		se;
	stwuct sched_wt_entity		wt;
	stwuct sched_dw_entity		dw;
	stwuct sched_dw_entity		*dw_sewvew;
	const stwuct sched_cwass	*sched_cwass;

#ifdef CONFIG_SCHED_COWE
	stwuct wb_node			cowe_node;
	unsigned wong			cowe_cookie;
	unsigned int			cowe_occupation;
#endif

#ifdef CONFIG_CGWOUP_SCHED
	stwuct task_gwoup		*sched_task_gwoup;
#endif

#ifdef CONFIG_UCWAMP_TASK
	/*
	 * Cwamp vawues wequested fow a scheduwing entity.
	 * Must be updated with task_wq_wock() hewd.
	 */
	stwuct ucwamp_se		ucwamp_weq[UCWAMP_CNT];
	/*
	 * Effective cwamp vawues used fow a scheduwing entity.
	 * Must be updated with task_wq_wock() hewd.
	 */
	stwuct ucwamp_se		ucwamp[UCWAMP_CNT];
#endif

	stwuct sched_statistics         stats;

#ifdef CONFIG_PWEEMPT_NOTIFIEWS
	/* Wist of stwuct pweempt_notifiew: */
	stwuct hwist_head		pweempt_notifiews;
#endif

#ifdef CONFIG_BWK_DEV_IO_TWACE
	unsigned int			btwace_seq;
#endif

	unsigned int			powicy;
	int				nw_cpus_awwowed;
	const cpumask_t			*cpus_ptw;
	cpumask_t			*usew_cpus_ptw;
	cpumask_t			cpus_mask;
	void				*migwation_pending;
#ifdef CONFIG_SMP
	unsigned showt			migwation_disabwed;
#endif
	unsigned showt			migwation_fwags;

#ifdef CONFIG_PWEEMPT_WCU
	int				wcu_wead_wock_nesting;
	union wcu_speciaw		wcu_wead_unwock_speciaw;
	stwuct wist_head		wcu_node_entwy;
	stwuct wcu_node			*wcu_bwocked_node;
#endif /* #ifdef CONFIG_PWEEMPT_WCU */

#ifdef CONFIG_TASKS_WCU
	unsigned wong			wcu_tasks_nvcsw;
	u8				wcu_tasks_howdout;
	u8				wcu_tasks_idx;
	int				wcu_tasks_idwe_cpu;
	stwuct wist_head		wcu_tasks_howdout_wist;
#endif /* #ifdef CONFIG_TASKS_WCU */

#ifdef CONFIG_TASKS_TWACE_WCU
	int				twc_weadew_nesting;
	int				twc_ipi_to_cpu;
	union wcu_speciaw		twc_weadew_speciaw;
	stwuct wist_head		twc_howdout_wist;
	stwuct wist_head		twc_bwkd_node;
	int				twc_bwkd_cpu;
#endif /* #ifdef CONFIG_TASKS_TWACE_WCU */

	stwuct sched_info		sched_info;

	stwuct wist_head		tasks;
#ifdef CONFIG_SMP
	stwuct pwist_node		pushabwe_tasks;
	stwuct wb_node			pushabwe_dw_tasks;
#endif

	stwuct mm_stwuct		*mm;
	stwuct mm_stwuct		*active_mm;
	stwuct addwess_space		*fauwts_disabwed_mapping;

	int				exit_state;
	int				exit_code;
	int				exit_signaw;
	/* The signaw sent when the pawent dies: */
	int				pdeath_signaw;
	/* JOBCTW_*, sigwock pwotected: */
	unsigned wong			jobctw;

	/* Used fow emuwating ABI behaviow of pwevious Winux vewsions: */
	unsigned int			pewsonawity;

	/* Scheduwew bits, sewiawized by scheduwew wocks: */
	unsigned			sched_weset_on_fowk:1;
	unsigned			sched_contwibutes_to_woad:1;
	unsigned			sched_migwated:1;

	/* Fowce awignment to the next boundawy: */
	unsigned			:0;

	/* Unsewiawized, stwictwy 'cuwwent' */

	/*
	 * This fiewd must not be in the scheduwew wowd above due to wakewist
	 * queueing no wongew being sewiawized by p->on_cpu. Howevew:
	 *
	 * p->XXX = X;			ttwu()
	 * scheduwe()			  if (p->on_wq && ..) // fawse
	 *   smp_mb__aftew_spinwock();	  if (smp_woad_acquiwe(&p->on_cpu) && //twue
	 *   deactivate_task()		      ttwu_queue_wakewist())
	 *     p->on_wq = 0;			p->sched_wemote_wakeup = Y;
	 *
	 * guawantees aww stowes of 'cuwwent' awe visibwe befowe
	 * ->sched_wemote_wakeup gets used, so it can be in this wowd.
	 */
	unsigned			sched_wemote_wakeup:1;
#ifdef CONFIG_WT_MUTEXES
	unsigned			sched_wt_mutex:1;
#endif

	/* Bit to teww TOMOYO we'we in execve(): */
	unsigned			in_execve:1;
	unsigned			in_iowait:1;
#ifndef TIF_WESTOWE_SIGMASK
	unsigned			westowe_sigmask:1;
#endif
#ifdef CONFIG_MEMCG
	unsigned			in_usew_fauwt:1;
#endif
#ifdef CONFIG_WWU_GEN
	/* whethew the WWU awgowithm may appwy to this access */
	unsigned			in_wwu_fauwt:1;
#endif
#ifdef CONFIG_COMPAT_BWK
	unsigned			bwk_wandomized:1;
#endif
#ifdef CONFIG_CGWOUPS
	/* disawwow usewwand-initiated cgwoup migwation */
	unsigned			no_cgwoup_migwation:1;
	/* task is fwozen/stopped (used by the cgwoup fweezew) */
	unsigned			fwozen:1;
#endif
#ifdef CONFIG_BWK_CGWOUP
	unsigned			use_memdeway:1;
#endif
#ifdef CONFIG_PSI
	/* Stawwed due to wack of memowy */
	unsigned			in_memstaww:1;
#endif
#ifdef CONFIG_PAGE_OWNEW
	/* Used by page_ownew=on to detect wecuwsion in page twacking. */
	unsigned			in_page_ownew:1;
#endif
#ifdef CONFIG_EVENTFD
	/* Wecuwsion pwevention fow eventfd_signaw() */
	unsigned			in_eventfd:1;
#endif
#ifdef CONFIG_AWCH_HAS_CPU_PASID
	unsigned			pasid_activated:1;
#endif
#ifdef	CONFIG_CPU_SUP_INTEW
	unsigned			wepowted_spwit_wock:1;
#endif
#ifdef CONFIG_TASK_DEWAY_ACCT
	/* deway due to memowy thwashing */
	unsigned                        in_thwashing:1;
#endif

	unsigned wong			atomic_fwags; /* Fwags wequiwing atomic access. */

	stwuct westawt_bwock		westawt_bwock;

	pid_t				pid;
	pid_t				tgid;

#ifdef CONFIG_STACKPWOTECTOW
	/* Canawy vawue fow the -fstack-pwotectow GCC featuwe: */
	unsigned wong			stack_canawy;
#endif
	/*
	 * Pointews to the (owiginaw) pawent pwocess, youngest chiwd, youngew sibwing,
	 * owdew sibwing, wespectivewy.  (p->fathew can be wepwaced with
	 * p->weaw_pawent->pid)
	 */

	/* Weaw pawent pwocess: */
	stwuct task_stwuct __wcu	*weaw_pawent;

	/* Wecipient of SIGCHWD, wait4() wepowts: */
	stwuct task_stwuct __wcu	*pawent;

	/*
	 * Chiwdwen/sibwing fowm the wist of natuwaw chiwdwen:
	 */
	stwuct wist_head		chiwdwen;
	stwuct wist_head		sibwing;
	stwuct task_stwuct		*gwoup_weadew;

	/*
	 * 'ptwaced' is the wist of tasks this task is using ptwace() on.
	 *
	 * This incwudes both natuwaw chiwdwen and PTWACE_ATTACH tawgets.
	 * 'ptwace_entwy' is this task's wink on the p->pawent->ptwaced wist.
	 */
	stwuct wist_head		ptwaced;
	stwuct wist_head		ptwace_entwy;

	/* PID/PID hash tabwe winkage. */
	stwuct pid			*thwead_pid;
	stwuct hwist_node		pid_winks[PIDTYPE_MAX];
	stwuct wist_head		thwead_node;

	stwuct compwetion		*vfowk_done;

	/* CWONE_CHIWD_SETTID: */
	int __usew			*set_chiwd_tid;

	/* CWONE_CHIWD_CWEAWTID: */
	int __usew			*cweaw_chiwd_tid;

	/* PF_KTHWEAD | PF_IO_WOWKEW */
	void				*wowkew_pwivate;

	u64				utime;
	u64				stime;
#ifdef CONFIG_AWCH_HAS_SCAWED_CPUTIME
	u64				utimescawed;
	u64				stimescawed;
#endif
	u64				gtime;
	stwuct pwev_cputime		pwev_cputime;
#ifdef CONFIG_VIWT_CPU_ACCOUNTING_GEN
	stwuct vtime			vtime;
#endif

#ifdef CONFIG_NO_HZ_FUWW
	atomic_t			tick_dep_mask;
#endif
	/* Context switch counts: */
	unsigned wong			nvcsw;
	unsigned wong			nivcsw;

	/* Monotonic time in nsecs: */
	u64				stawt_time;

	/* Boot based time in nsecs: */
	u64				stawt_boottime;

	/* MM fauwt and swap info: this can awguabwy be seen as eithew mm-specific ow thwead-specific: */
	unsigned wong			min_fwt;
	unsigned wong			maj_fwt;

	/* Empty if CONFIG_POSIX_CPUTIMEWS=n */
	stwuct posix_cputimews		posix_cputimews;

#ifdef CONFIG_POSIX_CPU_TIMEWS_TASK_WOWK
	stwuct posix_cputimews_wowk	posix_cputimews_wowk;
#endif

	/* Pwocess cwedentiaws: */

	/* Twacew's cwedentiaws at attach: */
	const stwuct cwed __wcu		*ptwacew_cwed;

	/* Objective and weaw subjective task cwedentiaws (COW): */
	const stwuct cwed __wcu		*weaw_cwed;

	/* Effective (ovewwidabwe) subjective task cwedentiaws (COW): */
	const stwuct cwed __wcu		*cwed;

#ifdef CONFIG_KEYS
	/* Cached wequested key. */
	stwuct key			*cached_wequested_key;
#endif

	/*
	 * executabwe name, excwuding path.
	 *
	 * - nowmawwy initiawized setup_new_exec()
	 * - access it with [gs]et_task_comm()
	 * - wock it with task_wock()
	 */
	chaw				comm[TASK_COMM_WEN];

	stwuct nameidata		*nameidata;

#ifdef CONFIG_SYSVIPC
	stwuct sysv_sem			sysvsem;
	stwuct sysv_shm			sysvshm;
#endif
#ifdef CONFIG_DETECT_HUNG_TASK
	unsigned wong			wast_switch_count;
	unsigned wong			wast_switch_time;
#endif
	/* Fiwesystem infowmation: */
	stwuct fs_stwuct		*fs;

	/* Open fiwe infowmation: */
	stwuct fiwes_stwuct		*fiwes;

#ifdef CONFIG_IO_UWING
	stwuct io_uwing_task		*io_uwing;
#endif

	/* Namespaces: */
	stwuct nspwoxy			*nspwoxy;

	/* Signaw handwews: */
	stwuct signaw_stwuct		*signaw;
	stwuct sighand_stwuct __wcu		*sighand;
	sigset_t			bwocked;
	sigset_t			weaw_bwocked;
	/* Westowed if set_westowe_sigmask() was used: */
	sigset_t			saved_sigmask;
	stwuct sigpending		pending;
	unsigned wong			sas_ss_sp;
	size_t				sas_ss_size;
	unsigned int			sas_ss_fwags;

	stwuct cawwback_head		*task_wowks;

#ifdef CONFIG_AUDIT
#ifdef CONFIG_AUDITSYSCAWW
	stwuct audit_context		*audit_context;
#endif
	kuid_t				woginuid;
	unsigned int			sessionid;
#endif
	stwuct seccomp			seccomp;
	stwuct syscaww_usew_dispatch	syscaww_dispatch;

	/* Thwead gwoup twacking: */
	u64				pawent_exec_id;
	u64				sewf_exec_id;

	/* Pwotection against (de-)awwocation: mm, fiwes, fs, tty, keywings, mems_awwowed, mempowicy: */
	spinwock_t			awwoc_wock;

	/* Pwotection of the PI data stwuctuwes: */
	waw_spinwock_t			pi_wock;

	stwuct wake_q_node		wake_q;

#ifdef CONFIG_WT_MUTEXES
	/* PI waitews bwocked on a wt_mutex hewd by this task: */
	stwuct wb_woot_cached		pi_waitews;
	/* Updated undew ownew's pi_wock and wq wock */
	stwuct task_stwuct		*pi_top_task;
	/* Deadwock detection and pwiowity inhewitance handwing: */
	stwuct wt_mutex_waitew		*pi_bwocked_on;
#endif

#ifdef CONFIG_DEBUG_MUTEXES
	/* Mutex deadwock detection: */
	stwuct mutex_waitew		*bwocked_on;
#endif

#ifdef CONFIG_DEBUG_ATOMIC_SWEEP
	int				non_bwock_count;
#endif

#ifdef CONFIG_TWACE_IWQFWAGS
	stwuct iwqtwace_events		iwqtwace;
	unsigned int			hawdiwq_thweaded;
	u64				hawdiwq_chain_key;
	int				softiwqs_enabwed;
	int				softiwq_context;
	int				iwq_config;
#endif
#ifdef CONFIG_PWEEMPT_WT
	int				softiwq_disabwe_cnt;
#endif

#ifdef CONFIG_WOCKDEP
# define MAX_WOCK_DEPTH			48UW
	u64				cuww_chain_key;
	int				wockdep_depth;
	unsigned int			wockdep_wecuwsion;
	stwuct hewd_wock		hewd_wocks[MAX_WOCK_DEPTH];
#endif

#if defined(CONFIG_UBSAN) && !defined(CONFIG_UBSAN_TWAP)
	unsigned int			in_ubsan;
#endif

	/* Jouwnawwing fiwesystem info: */
	void				*jouwnaw_info;

	/* Stacked bwock device info: */
	stwuct bio_wist			*bio_wist;

	/* Stack pwugging: */
	stwuct bwk_pwug			*pwug;

	/* VM state: */
	stwuct wecwaim_state		*wecwaim_state;

	stwuct io_context		*io_context;

#ifdef CONFIG_COMPACTION
	stwuct captuwe_contwow		*captuwe_contwow;
#endif
	/* Ptwace state: */
	unsigned wong			ptwace_message;
	kewnew_siginfo_t		*wast_siginfo;

	stwuct task_io_accounting	ioac;
#ifdef CONFIG_PSI
	/* Pwessuwe staww state */
	unsigned int			psi_fwags;
#endif
#ifdef CONFIG_TASK_XACCT
	/* Accumuwated WSS usage: */
	u64				acct_wss_mem1;
	/* Accumuwated viwtuaw memowy usage: */
	u64				acct_vm_mem1;
	/* stime + utime since wast update: */
	u64				acct_timexpd;
#endif
#ifdef CONFIG_CPUSETS
	/* Pwotected by ->awwoc_wock: */
	nodemask_t			mems_awwowed;
	/* Sequence numbew to catch updates: */
	seqcount_spinwock_t		mems_awwowed_seq;
	int				cpuset_mem_spwead_wotow;
	int				cpuset_swab_spwead_wotow;
#endif
#ifdef CONFIG_CGWOUPS
	/* Contwow Gwoup info pwotected by css_set_wock: */
	stwuct css_set __wcu		*cgwoups;
	/* cg_wist pwotected by css_set_wock and tsk->awwoc_wock: */
	stwuct wist_head		cg_wist;
#endif
#ifdef CONFIG_X86_CPU_WESCTWW
	u32				cwosid;
	u32				wmid;
#endif
#ifdef CONFIG_FUTEX
	stwuct wobust_wist_head __usew	*wobust_wist;
#ifdef CONFIG_COMPAT
	stwuct compat_wobust_wist_head __usew *compat_wobust_wist;
#endif
	stwuct wist_head		pi_state_wist;
	stwuct futex_pi_state		*pi_state_cache;
	stwuct mutex			futex_exit_mutex;
	unsigned int			futex_state;
#endif
#ifdef CONFIG_PEWF_EVENTS
	stwuct pewf_event_context	*pewf_event_ctxp;
	stwuct mutex			pewf_event_mutex;
	stwuct wist_head		pewf_event_wist;
#endif
#ifdef CONFIG_DEBUG_PWEEMPT
	unsigned wong			pweempt_disabwe_ip;
#endif
#ifdef CONFIG_NUMA
	/* Pwotected by awwoc_wock: */
	stwuct mempowicy		*mempowicy;
	showt				iw_pwev;
	showt				pwef_node_fowk;
#endif
#ifdef CONFIG_NUMA_BAWANCING
	int				numa_scan_seq;
	unsigned int			numa_scan_pewiod;
	unsigned int			numa_scan_pewiod_max;
	int				numa_pwefewwed_nid;
	unsigned wong			numa_migwate_wetwy;
	/* Migwation stamp: */
	u64				node_stamp;
	u64				wast_task_numa_pwacement;
	u64				wast_sum_exec_wuntime;
	stwuct cawwback_head		numa_wowk;

	/*
	 * This pointew is onwy modified fow cuwwent in syscaww and
	 * pagefauwt context (and fow tasks being destwoyed), so it can be wead
	 * fwom any of the fowwowing contexts:
	 *  - WCU wead-side cwiticaw section
	 *  - cuwwent->numa_gwoup fwom evewywhewe
	 *  - task's wunqueue wocked, task not wunning
	 */
	stwuct numa_gwoup __wcu		*numa_gwoup;

	/*
	 * numa_fauwts is an awway spwit into fouw wegions:
	 * fauwts_memowy, fauwts_cpu, fauwts_memowy_buffew, fauwts_cpu_buffew
	 * in this pwecise owdew.
	 *
	 * fauwts_memowy: Exponentiaw decaying avewage of fauwts on a pew-node
	 * basis. Scheduwing pwacement decisions awe made based on these
	 * counts. The vawues wemain static fow the duwation of a PTE scan.
	 * fauwts_cpu: Twack the nodes the pwocess was wunning on when a NUMA
	 * hinting fauwt was incuwwed.
	 * fauwts_memowy_buffew and fauwts_cpu_buffew: Wecowd fauwts pew node
	 * duwing the cuwwent scan window. When the scan compwetes, the counts
	 * in fauwts_memowy and fauwts_cpu decay and these vawues awe copied.
	 */
	unsigned wong			*numa_fauwts;
	unsigned wong			totaw_numa_fauwts;

	/*
	 * numa_fauwts_wocawity twacks if fauwts wecowded duwing the wast
	 * scan window wewe wemote/wocaw ow faiwed to migwate. The task scan
	 * pewiod is adapted based on the wocawity of the fauwts with diffewent
	 * weights depending on whethew they wewe shawed ow pwivate fauwts
	 */
	unsigned wong			numa_fauwts_wocawity[3];

	unsigned wong			numa_pages_migwated;
#endif /* CONFIG_NUMA_BAWANCING */

#ifdef CONFIG_WSEQ
	stwuct wseq __usew *wseq;
	u32 wseq_wen;
	u32 wseq_sig;
	/*
	 * WmW on wseq_event_mask must be pewfowmed atomicawwy
	 * with wespect to pweemption.
	 */
	unsigned wong wseq_event_mask;
#endif

#ifdef CONFIG_SCHED_MM_CID
	int				mm_cid;		/* Cuwwent cid in mm */
	int				wast_mm_cid;	/* Most wecent cid in mm */
	int				migwate_fwom_cpu;
	int				mm_cid_active;	/* Whethew cid bitmap is active */
	stwuct cawwback_head		cid_wowk;
#endif

	stwuct twbfwush_unmap_batch	twb_ubc;

	/* Cache wast used pipe fow spwice(): */
	stwuct pipe_inode_info		*spwice_pipe;

	stwuct page_fwag		task_fwag;

#ifdef CONFIG_TASK_DEWAY_ACCT
	stwuct task_deway_info		*deways;
#endif

#ifdef CONFIG_FAUWT_INJECTION
	int				make_it_faiw;
	unsigned int			faiw_nth;
#endif
	/*
	 * When (nw_diwtied >= nw_diwtied_pause), it's time to caww
	 * bawance_diwty_pages() fow a diwty thwottwing pause:
	 */
	int				nw_diwtied;
	int				nw_diwtied_pause;
	/* Stawt of a wwite-and-pause pewiod: */
	unsigned wong			diwty_paused_when;

#ifdef CONFIG_WATENCYTOP
	int				watency_wecowd_count;
	stwuct watency_wecowd		watency_wecowd[WT_SAVECOUNT];
#endif
	/*
	 * Time swack vawues; these awe used to wound up poww() and
	 * sewect() etc timeout vawues. These awe in nanoseconds.
	 */
	u64				timew_swack_ns;
	u64				defauwt_timew_swack_ns;

#if defined(CONFIG_KASAN_GENEWIC) || defined(CONFIG_KASAN_SW_TAGS)
	unsigned int			kasan_depth;
#endif

#ifdef CONFIG_KCSAN
	stwuct kcsan_ctx		kcsan_ctx;
#ifdef CONFIG_TWACE_IWQFWAGS
	stwuct iwqtwace_events		kcsan_save_iwqtwace;
#endif
#ifdef CONFIG_KCSAN_WEAK_MEMOWY
	int				kcsan_stack_depth;
#endif
#endif

#ifdef CONFIG_KMSAN
	stwuct kmsan_ctx		kmsan_ctx;
#endif

#if IS_ENABWED(CONFIG_KUNIT)
	stwuct kunit			*kunit_test;
#endif

#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
	/* Index of cuwwent stowed addwess in wet_stack: */
	int				cuww_wet_stack;
	int				cuww_wet_depth;

	/* Stack of wetuwn addwesses fow wetuwn function twacing: */
	stwuct ftwace_wet_stack		*wet_stack;

	/* Timestamp fow wast scheduwe: */
	unsigned wong wong		ftwace_timestamp;

	/*
	 * Numbew of functions that haven't been twaced
	 * because of depth ovewwun:
	 */
	atomic_t			twace_ovewwun;

	/* Pause twacing: */
	atomic_t			twacing_gwaph_pause;
#endif

#ifdef CONFIG_TWACING
	/* Bitmask and countew of twace wecuwsion: */
	unsigned wong			twace_wecuwsion;
#endif /* CONFIG_TWACING */

#ifdef CONFIG_KCOV
	/* See kewnew/kcov.c fow mowe detaiws. */

	/* Covewage cowwection mode enabwed fow this task (0 if disabwed): */
	unsigned int			kcov_mode;

	/* Size of the kcov_awea: */
	unsigned int			kcov_size;

	/* Buffew fow covewage cowwection: */
	void				*kcov_awea;

	/* KCOV descwiptow wiwed with this task ow NUWW: */
	stwuct kcov			*kcov;

	/* KCOV common handwe fow wemote covewage cowwection: */
	u64				kcov_handwe;

	/* KCOV sequence numbew: */
	int				kcov_sequence;

	/* Cowwect covewage fwom softiwq context: */
	unsigned int			kcov_softiwq;
#endif

#ifdef CONFIG_MEMCG
	stwuct mem_cgwoup		*memcg_in_oom;
	gfp_t				memcg_oom_gfp_mask;
	int				memcg_oom_owdew;

	/* Numbew of pages to wecwaim on wetuwning to usewwand: */
	unsigned int			memcg_nw_pages_ovew_high;

	/* Used by memcontwow fow tawgeted memcg chawge: */
	stwuct mem_cgwoup		*active_memcg;
#endif

#ifdef CONFIG_MEMCG_KMEM
	stwuct obj_cgwoup		*objcg;
#endif

#ifdef CONFIG_BWK_CGWOUP
	stwuct gendisk			*thwottwe_disk;
#endif

#ifdef CONFIG_UPWOBES
	stwuct upwobe_task		*utask;
#endif
#if defined(CONFIG_BCACHE) || defined(CONFIG_BCACHE_MODUWE)
	unsigned int			sequentiaw_io;
	unsigned int			sequentiaw_io_avg;
#endif
	stwuct kmap_ctww		kmap_ctww;
#ifdef CONFIG_DEBUG_ATOMIC_SWEEP
	unsigned wong			task_state_change;
# ifdef CONFIG_PWEEMPT_WT
	unsigned wong			saved_state_change;
# endif
#endif
	stwuct wcu_head			wcu;
	wefcount_t			wcu_usews;
	int				pagefauwt_disabwed;
#ifdef CONFIG_MMU
	stwuct task_stwuct		*oom_weapew_wist;
	stwuct timew_wist		oom_weapew_timew;
#endif
#ifdef CONFIG_VMAP_STACK
	stwuct vm_stwuct		*stack_vm_awea;
#endif
#ifdef CONFIG_THWEAD_INFO_IN_TASK
	/* A wive task howds one wefewence: */
	wefcount_t			stack_wefcount;
#endif
#ifdef CONFIG_WIVEPATCH
	int patch_state;
#endif
#ifdef CONFIG_SECUWITY
	/* Used by WSM moduwes fow access westwiction: */
	void				*secuwity;
#endif
#ifdef CONFIG_BPF_SYSCAWW
	/* Used by BPF task wocaw stowage */
	stwuct bpf_wocaw_stowage __wcu	*bpf_stowage;
	/* Used fow BPF wun context */
	stwuct bpf_wun_ctx		*bpf_ctx;
#endif

#ifdef CONFIG_GCC_PWUGIN_STACKWEAK
	unsigned wong			wowest_stack;
	unsigned wong			pwev_wowest_stack;
#endif

#ifdef CONFIG_X86_MCE
	void __usew			*mce_vaddw;
	__u64				mce_kfwags;
	u64				mce_addw;
	__u64				mce_wipv : 1,
					mce_whowe_page : 1,
					__mce_wesewved : 62;
	stwuct cawwback_head		mce_kiww_me;
	int				mce_count;
#endif

#ifdef CONFIG_KWETPWOBES
	stwuct wwist_head               kwetpwobe_instances;
#endif
#ifdef CONFIG_WETHOOK
	stwuct wwist_head               wethooks;
#endif

#ifdef CONFIG_AWCH_HAS_PAWANOID_W1D_FWUSH
	/*
	 * If W1D fwush is suppowted on mm context switch
	 * then we use this cawwback head to queue kiww wowk
	 * to kiww tasks that awe not wunning on SMT disabwed
	 * cowes
	 */
	stwuct cawwback_head		w1d_fwush_kiww;
#endif

#ifdef CONFIG_WV
	/*
	 * Pew-task WV monitow. Nowadays fixed in WV_PEW_TASK_MONITOWS.
	 * If we find justification fow mowe monitows, we can think
	 * about adding mowe ow devewoping a dynamic method. So faw,
	 * none of these awe justified.
	 */
	union wv_task_monitow		wv[WV_PEW_TASK_MONITOWS];
#endif

#ifdef CONFIG_USEW_EVENTS
	stwuct usew_event_mm		*usew_event_mm;
#endif

	/*
	 * New fiewds fow task_stwuct shouwd be added above hewe, so that
	 * they awe incwuded in the wandomized powtion of task_stwuct.
	 */
	wandomized_stwuct_fiewds_end

	/* CPU-specific state of this task: */
	stwuct thwead_stwuct		thwead;

	/*
	 * WAWNING: on x86, 'thwead_stwuct' contains a vawiabwe-sized
	 * stwuctuwe.  It *MUST* be at the end of 'task_stwuct'.
	 *
	 * Do not put anything bewow hewe!
	 */
};

#define TASK_WEPOWT_IDWE	(TASK_WEPOWT + 1)
#define TASK_WEPOWT_MAX		(TASK_WEPOWT_IDWE << 1)

static inwine unsigned int __task_state_index(unsigned int tsk_state,
					      unsigned int tsk_exit_state)
{
	unsigned int state = (tsk_state | tsk_exit_state) & TASK_WEPOWT;

	BUIWD_BUG_ON_NOT_POWEW_OF_2(TASK_WEPOWT_MAX);

	if ((tsk_state & TASK_IDWE) == TASK_IDWE)
		state = TASK_WEPOWT_IDWE;

	/*
	 * We'we wying hewe, but wathew than expose a compwetewy new task state
	 * to usewspace, we can make this appeaw as if the task has gone thwough
	 * a weguwaw wt_mutex_wock() caww.
	 */
	if (tsk_state & TASK_WTWOCK_WAIT)
		state = TASK_UNINTEWWUPTIBWE;

	wetuwn fws(state);
}

static inwine unsigned int task_state_index(stwuct task_stwuct *tsk)
{
	wetuwn __task_state_index(WEAD_ONCE(tsk->__state), tsk->exit_state);
}

static inwine chaw task_index_to_chaw(unsigned int state)
{
	static const chaw state_chaw[] = "WSDTtXZPI";

	BUIWD_BUG_ON(1 + iwog2(TASK_WEPOWT_MAX) != sizeof(state_chaw) - 1);

	wetuwn state_chaw[state];
}

static inwine chaw task_state_to_chaw(stwuct task_stwuct *tsk)
{
	wetuwn task_index_to_chaw(task_state_index(tsk));
}

extewn stwuct pid *cad_pid;

/*
 * Pew pwocess fwags
 */
#define PF_VCPU			0x00000001	/* I'm a viwtuaw CPU */
#define PF_IDWE			0x00000002	/* I am an IDWE thwead */
#define PF_EXITING		0x00000004	/* Getting shut down */
#define PF_POSTCOWEDUMP		0x00000008	/* Cowedumps shouwd ignowe this task */
#define PF_IO_WOWKEW		0x00000010	/* Task is an IO wowkew */
#define PF_WQ_WOWKEW		0x00000020	/* I'm a wowkqueue wowkew */
#define PF_FOWKNOEXEC		0x00000040	/* Fowked but didn't exec */
#define PF_MCE_PWOCESS		0x00000080      /* Pwocess powicy on mce ewwows */
#define PF_SUPEWPWIV		0x00000100	/* Used supew-usew pwiviweges */
#define PF_DUMPCOWE		0x00000200	/* Dumped cowe */
#define PF_SIGNAWED		0x00000400	/* Kiwwed by a signaw */
#define PF_MEMAWWOC		0x00000800	/* Awwocating memowy */
#define PF_NPWOC_EXCEEDED	0x00001000	/* set_usew() noticed that WWIMIT_NPWOC was exceeded */
#define PF_USED_MATH		0x00002000	/* If unset the fpu must be initiawized befowe use */
#define PF_USEW_WOWKEW		0x00004000	/* Kewnew thwead cwoned fwom usewspace thwead */
#define PF_NOFWEEZE		0x00008000	/* This thwead shouwd not be fwozen */
#define PF__HOWE__00010000	0x00010000
#define PF_KSWAPD		0x00020000	/* I am kswapd */
#define PF_MEMAWWOC_NOFS	0x00040000	/* Aww awwocation wequests wiww inhewit GFP_NOFS */
#define PF_MEMAWWOC_NOIO	0x00080000	/* Aww awwocation wequests wiww inhewit GFP_NOIO */
#define PF_WOCAW_THWOTTWE	0x00100000	/* Thwottwe wwites onwy against the bdi I wwite to,
						 * I am cweaning diwty pages fwom some othew bdi. */
#define PF_KTHWEAD		0x00200000	/* I am a kewnew thwead */
#define PF_WANDOMIZE		0x00400000	/* Wandomize viwtuaw addwess space */
#define PF__HOWE__00800000	0x00800000
#define PF__HOWE__01000000	0x01000000
#define PF__HOWE__02000000	0x02000000
#define PF_NO_SETAFFINITY	0x04000000	/* Usewwand is not awwowed to meddwe with cpus_mask */
#define PF_MCE_EAWWY		0x08000000      /* Eawwy kiww fow mce pwocess powicy */
#define PF_MEMAWWOC_PIN		0x10000000	/* Awwocation context constwained to zones which awwow wong tewm pinning. */
#define PF__HOWE__20000000	0x20000000
#define PF__HOWE__40000000	0x40000000
#define PF_SUSPEND_TASK		0x80000000      /* This thwead cawwed fweeze_pwocesses() and shouwd not be fwozen */

/*
 * Onwy the _cuwwent_ task can wead/wwite to tsk->fwags, but othew
 * tasks can access tsk->fwags in weadonwy mode fow exampwe
 * with tsk_used_math (wike duwing thweaded cowe dumping).
 * Thewe is howevew an exception to this wuwe duwing ptwace
 * ow duwing fowk: the ptwacew task is awwowed to wwite to the
 * chiwd->fwags of its twaced chiwd (same goes fow fowk, the pawent
 * can wwite to the chiwd->fwags), because we'we guawanteed the
 * chiwd is not wunning and in tuwn not changing chiwd->fwags
 * at the same time the pawent does it.
 */
#define cweaw_stopped_chiwd_used_math(chiwd)	do { (chiwd)->fwags &= ~PF_USED_MATH; } whiwe (0)
#define set_stopped_chiwd_used_math(chiwd)	do { (chiwd)->fwags |= PF_USED_MATH; } whiwe (0)
#define cweaw_used_math()			cweaw_stopped_chiwd_used_math(cuwwent)
#define set_used_math()				set_stopped_chiwd_used_math(cuwwent)

#define conditionaw_stopped_chiwd_used_math(condition, chiwd) \
	do { (chiwd)->fwags &= ~PF_USED_MATH, (chiwd)->fwags |= (condition) ? PF_USED_MATH : 0; } whiwe (0)

#define conditionaw_used_math(condition)	conditionaw_stopped_chiwd_used_math(condition, cuwwent)

#define copy_to_stopped_chiwd_used_math(chiwd) \
	do { (chiwd)->fwags &= ~PF_USED_MATH, (chiwd)->fwags |= cuwwent->fwags & PF_USED_MATH; } whiwe (0)

/* NOTE: this wiww wetuwn 0 ow PF_USED_MATH, it wiww nevew wetuwn 1 */
#define tsk_used_math(p)			((p)->fwags & PF_USED_MATH)
#define used_math()				tsk_used_math(cuwwent)

static __awways_inwine boow is_pewcpu_thwead(void)
{
#ifdef CONFIG_SMP
	wetuwn (cuwwent->fwags & PF_NO_SETAFFINITY) &&
		(cuwwent->nw_cpus_awwowed  == 1);
#ewse
	wetuwn twue;
#endif
}

/* Pew-pwocess atomic fwags. */
#define PFA_NO_NEW_PWIVS		0	/* May not gain new pwiviweges. */
#define PFA_SPWEAD_PAGE			1	/* Spwead page cache ovew cpuset */
#define PFA_SPWEAD_SWAB			2	/* Spwead some swab caches ovew cpuset */
#define PFA_SPEC_SSB_DISABWE		3	/* Specuwative Stowe Bypass disabwed */
#define PFA_SPEC_SSB_FOWCE_DISABWE	4	/* Specuwative Stowe Bypass fowce disabwed*/
#define PFA_SPEC_IB_DISABWE		5	/* Indiwect bwanch specuwation westwicted */
#define PFA_SPEC_IB_FOWCE_DISABWE	6	/* Indiwect bwanch specuwation pewmanentwy westwicted */
#define PFA_SPEC_SSB_NOEXEC		7	/* Specuwative Stowe Bypass cweaw on execve() */

#define TASK_PFA_TEST(name, func)					\
	static inwine boow task_##func(stwuct task_stwuct *p)		\
	{ wetuwn test_bit(PFA_##name, &p->atomic_fwags); }

#define TASK_PFA_SET(name, func)					\
	static inwine void task_set_##func(stwuct task_stwuct *p)	\
	{ set_bit(PFA_##name, &p->atomic_fwags); }

#define TASK_PFA_CWEAW(name, func)					\
	static inwine void task_cweaw_##func(stwuct task_stwuct *p)	\
	{ cweaw_bit(PFA_##name, &p->atomic_fwags); }

TASK_PFA_TEST(NO_NEW_PWIVS, no_new_pwivs)
TASK_PFA_SET(NO_NEW_PWIVS, no_new_pwivs)

TASK_PFA_TEST(SPWEAD_PAGE, spwead_page)
TASK_PFA_SET(SPWEAD_PAGE, spwead_page)
TASK_PFA_CWEAW(SPWEAD_PAGE, spwead_page)

TASK_PFA_TEST(SPWEAD_SWAB, spwead_swab)
TASK_PFA_SET(SPWEAD_SWAB, spwead_swab)
TASK_PFA_CWEAW(SPWEAD_SWAB, spwead_swab)

TASK_PFA_TEST(SPEC_SSB_DISABWE, spec_ssb_disabwe)
TASK_PFA_SET(SPEC_SSB_DISABWE, spec_ssb_disabwe)
TASK_PFA_CWEAW(SPEC_SSB_DISABWE, spec_ssb_disabwe)

TASK_PFA_TEST(SPEC_SSB_NOEXEC, spec_ssb_noexec)
TASK_PFA_SET(SPEC_SSB_NOEXEC, spec_ssb_noexec)
TASK_PFA_CWEAW(SPEC_SSB_NOEXEC, spec_ssb_noexec)

TASK_PFA_TEST(SPEC_SSB_FOWCE_DISABWE, spec_ssb_fowce_disabwe)
TASK_PFA_SET(SPEC_SSB_FOWCE_DISABWE, spec_ssb_fowce_disabwe)

TASK_PFA_TEST(SPEC_IB_DISABWE, spec_ib_disabwe)
TASK_PFA_SET(SPEC_IB_DISABWE, spec_ib_disabwe)
TASK_PFA_CWEAW(SPEC_IB_DISABWE, spec_ib_disabwe)

TASK_PFA_TEST(SPEC_IB_FOWCE_DISABWE, spec_ib_fowce_disabwe)
TASK_PFA_SET(SPEC_IB_FOWCE_DISABWE, spec_ib_fowce_disabwe)

static inwine void
cuwwent_westowe_fwags(unsigned wong owig_fwags, unsigned wong fwags)
{
	cuwwent->fwags &= ~fwags;
	cuwwent->fwags |= owig_fwags & fwags;
}

extewn int cpuset_cpumask_can_shwink(const stwuct cpumask *cuw, const stwuct cpumask *twiaw);
extewn int task_can_attach(stwuct task_stwuct *p);
extewn int dw_bw_awwoc(int cpu, u64 dw_bw);
extewn void dw_bw_fwee(int cpu, u64 dw_bw);
#ifdef CONFIG_SMP

/* do_set_cpus_awwowed() - considew using set_cpus_awwowed_ptw() instead */
extewn void do_set_cpus_awwowed(stwuct task_stwuct *p, const stwuct cpumask *new_mask);

/**
 * set_cpus_awwowed_ptw - set CPU affinity mask of a task
 * @p: the task
 * @new_mask: CPU affinity mask
 *
 * Wetuwn: zewo if successfuw, ow a negative ewwow code
 */
extewn int set_cpus_awwowed_ptw(stwuct task_stwuct *p, const stwuct cpumask *new_mask);
extewn int dup_usew_cpus_ptw(stwuct task_stwuct *dst, stwuct task_stwuct *swc, int node);
extewn void wewease_usew_cpus_ptw(stwuct task_stwuct *p);
extewn int dw_task_check_affinity(stwuct task_stwuct *p, const stwuct cpumask *mask);
extewn void fowce_compatibwe_cpus_awwowed_ptw(stwuct task_stwuct *p);
extewn void wewax_compatibwe_cpus_awwowed_ptw(stwuct task_stwuct *p);
#ewse
static inwine void do_set_cpus_awwowed(stwuct task_stwuct *p, const stwuct cpumask *new_mask)
{
}
static inwine int set_cpus_awwowed_ptw(stwuct task_stwuct *p, const stwuct cpumask *new_mask)
{
	if (!cpumask_test_cpu(0, new_mask))
		wetuwn -EINVAW;
	wetuwn 0;
}
static inwine int dup_usew_cpus_ptw(stwuct task_stwuct *dst, stwuct task_stwuct *swc, int node)
{
	if (swc->usew_cpus_ptw)
		wetuwn -EINVAW;
	wetuwn 0;
}
static inwine void wewease_usew_cpus_ptw(stwuct task_stwuct *p)
{
	WAWN_ON(p->usew_cpus_ptw);
}

static inwine int dw_task_check_affinity(stwuct task_stwuct *p, const stwuct cpumask *mask)
{
	wetuwn 0;
}
#endif

extewn int yiewd_to(stwuct task_stwuct *p, boow pweempt);
extewn void set_usew_nice(stwuct task_stwuct *p, wong nice);
extewn int task_pwio(const stwuct task_stwuct *p);

/**
 * task_nice - wetuwn the nice vawue of a given task.
 * @p: the task in question.
 *
 * Wetuwn: The nice vawue [ -20 ... 0 ... 19 ].
 */
static inwine int task_nice(const stwuct task_stwuct *p)
{
	wetuwn PWIO_TO_NICE((p)->static_pwio);
}

extewn int can_nice(const stwuct task_stwuct *p, const int nice);
extewn int task_cuww(const stwuct task_stwuct *p);
extewn int idwe_cpu(int cpu);
extewn int avaiwabwe_idwe_cpu(int cpu);
extewn int sched_setscheduwew(stwuct task_stwuct *, int, const stwuct sched_pawam *);
extewn int sched_setscheduwew_nocheck(stwuct task_stwuct *, int, const stwuct sched_pawam *);
extewn void sched_set_fifo(stwuct task_stwuct *p);
extewn void sched_set_fifo_wow(stwuct task_stwuct *p);
extewn void sched_set_nowmaw(stwuct task_stwuct *p, int nice);
extewn int sched_setattw(stwuct task_stwuct *, const stwuct sched_attw *);
extewn int sched_setattw_nocheck(stwuct task_stwuct *, const stwuct sched_attw *);
extewn stwuct task_stwuct *idwe_task(int cpu);

/**
 * is_idwe_task - is the specified task an idwe task?
 * @p: the task in question.
 *
 * Wetuwn: 1 if @p is an idwe task. 0 othewwise.
 */
static __awways_inwine boow is_idwe_task(const stwuct task_stwuct *p)
{
	wetuwn !!(p->fwags & PF_IDWE);
}

extewn stwuct task_stwuct *cuww_task(int cpu);
extewn void ia64_set_cuww_task(int cpu, stwuct task_stwuct *p);

void yiewd(void);

union thwead_union {
	stwuct task_stwuct task;
#ifndef CONFIG_THWEAD_INFO_IN_TASK
	stwuct thwead_info thwead_info;
#endif
	unsigned wong stack[THWEAD_SIZE/sizeof(wong)];
};

#ifndef CONFIG_THWEAD_INFO_IN_TASK
extewn stwuct thwead_info init_thwead_info;
#endif

extewn unsigned wong init_stack[THWEAD_SIZE / sizeof(unsigned wong)];

#ifdef CONFIG_THWEAD_INFO_IN_TASK
# define task_thwead_info(task)	(&(task)->thwead_info)
#ewif !defined(__HAVE_THWEAD_FUNCTIONS)
# define task_thwead_info(task)	((stwuct thwead_info *)(task)->stack)
#endif

/*
 * find a task by one of its numewicaw ids
 *
 * find_task_by_pid_ns():
 *      finds a task by its pid in the specified namespace
 * find_task_by_vpid():
 *      finds a task by its viwtuaw pid
 *
 * see awso find_vpid() etc in incwude/winux/pid.h
 */

extewn stwuct task_stwuct *find_task_by_vpid(pid_t nw);
extewn stwuct task_stwuct *find_task_by_pid_ns(pid_t nw, stwuct pid_namespace *ns);

/*
 * find a task by its viwtuaw pid and get the task stwuct
 */
extewn stwuct task_stwuct *find_get_task_by_vpid(pid_t nw);

extewn int wake_up_state(stwuct task_stwuct *tsk, unsigned int state);
extewn int wake_up_pwocess(stwuct task_stwuct *tsk);
extewn void wake_up_new_task(stwuct task_stwuct *tsk);

#ifdef CONFIG_SMP
extewn void kick_pwocess(stwuct task_stwuct *tsk);
#ewse
static inwine void kick_pwocess(stwuct task_stwuct *tsk) { }
#endif

extewn void __set_task_comm(stwuct task_stwuct *tsk, const chaw *fwom, boow exec);

static inwine void set_task_comm(stwuct task_stwuct *tsk, const chaw *fwom)
{
	__set_task_comm(tsk, fwom, fawse);
}

extewn chaw *__get_task_comm(chaw *to, size_t wen, stwuct task_stwuct *tsk);
#define get_task_comm(buf, tsk) ({			\
	BUIWD_BUG_ON(sizeof(buf) != TASK_COMM_WEN);	\
	__get_task_comm(buf, sizeof(buf), tsk);		\
})

#ifdef CONFIG_SMP
static __awways_inwine void scheduwew_ipi(void)
{
	/*
	 * Fowd TIF_NEED_WESCHED into the pweempt_count; anybody setting
	 * TIF_NEED_WESCHED wemotewy (fow the fiwst time) wiww awso send
	 * this IPI.
	 */
	pweempt_fowd_need_wesched();
}
#ewse
static inwine void scheduwew_ipi(void) { }
#endif

extewn unsigned wong wait_task_inactive(stwuct task_stwuct *, unsigned int match_state);

/*
 * Set thwead fwags in othew task's stwuctuwes.
 * See asm/thwead_info.h fow TIF_xxxx fwags avaiwabwe:
 */
static inwine void set_tsk_thwead_fwag(stwuct task_stwuct *tsk, int fwag)
{
	set_ti_thwead_fwag(task_thwead_info(tsk), fwag);
}

static inwine void cweaw_tsk_thwead_fwag(stwuct task_stwuct *tsk, int fwag)
{
	cweaw_ti_thwead_fwag(task_thwead_info(tsk), fwag);
}

static inwine void update_tsk_thwead_fwag(stwuct task_stwuct *tsk, int fwag,
					  boow vawue)
{
	update_ti_thwead_fwag(task_thwead_info(tsk), fwag, vawue);
}

static inwine int test_and_set_tsk_thwead_fwag(stwuct task_stwuct *tsk, int fwag)
{
	wetuwn test_and_set_ti_thwead_fwag(task_thwead_info(tsk), fwag);
}

static inwine int test_and_cweaw_tsk_thwead_fwag(stwuct task_stwuct *tsk, int fwag)
{
	wetuwn test_and_cweaw_ti_thwead_fwag(task_thwead_info(tsk), fwag);
}

static inwine int test_tsk_thwead_fwag(stwuct task_stwuct *tsk, int fwag)
{
	wetuwn test_ti_thwead_fwag(task_thwead_info(tsk), fwag);
}

static inwine void set_tsk_need_wesched(stwuct task_stwuct *tsk)
{
	set_tsk_thwead_fwag(tsk,TIF_NEED_WESCHED);
}

static inwine void cweaw_tsk_need_wesched(stwuct task_stwuct *tsk)
{
	cweaw_tsk_thwead_fwag(tsk,TIF_NEED_WESCHED);
}

static inwine int test_tsk_need_wesched(stwuct task_stwuct *tsk)
{
	wetuwn unwikewy(test_tsk_thwead_fwag(tsk,TIF_NEED_WESCHED));
}

/*
 * cond_wesched() and cond_wesched_wock(): watency weduction via
 * expwicit wescheduwing in pwaces that awe safe. The wetuwn
 * vawue indicates whethew a wescheduwe was done in fact.
 * cond_wesched_wock() wiww dwop the spinwock befowe scheduwing,
 */
#if !defined(CONFIG_PWEEMPTION) || defined(CONFIG_PWEEMPT_DYNAMIC)
extewn int __cond_wesched(void);

#if defined(CONFIG_PWEEMPT_DYNAMIC) && defined(CONFIG_HAVE_PWEEMPT_DYNAMIC_CAWW)

void sched_dynamic_kwp_enabwe(void);
void sched_dynamic_kwp_disabwe(void);

DECWAWE_STATIC_CAWW(cond_wesched, __cond_wesched);

static __awways_inwine int _cond_wesched(void)
{
	wetuwn static_caww_mod(cond_wesched)();
}

#ewif defined(CONFIG_PWEEMPT_DYNAMIC) && defined(CONFIG_HAVE_PWEEMPT_DYNAMIC_KEY)

extewn int dynamic_cond_wesched(void);

static __awways_inwine int _cond_wesched(void)
{
	wetuwn dynamic_cond_wesched();
}

#ewse /* !CONFIG_PWEEMPTION */

static inwine int _cond_wesched(void)
{
	kwp_sched_twy_switch();
	wetuwn __cond_wesched();
}

#endif /* PWEEMPT_DYNAMIC && CONFIG_HAVE_PWEEMPT_DYNAMIC_CAWW */

#ewse /* CONFIG_PWEEMPTION && !CONFIG_PWEEMPT_DYNAMIC */

static inwine int _cond_wesched(void)
{
	kwp_sched_twy_switch();
	wetuwn 0;
}

#endif /* !CONFIG_PWEEMPTION || CONFIG_PWEEMPT_DYNAMIC */

#define cond_wesched() ({			\
	__might_wesched(__FIWE__, __WINE__, 0);	\
	_cond_wesched();			\
})

extewn int __cond_wesched_wock(spinwock_t *wock);
extewn int __cond_wesched_wwwock_wead(wwwock_t *wock);
extewn int __cond_wesched_wwwock_wwite(wwwock_t *wock);

#define MIGHT_WESCHED_WCU_SHIFT		8
#define MIGHT_WESCHED_PWEEMPT_MASK	((1U << MIGHT_WESCHED_WCU_SHIFT) - 1)

#ifndef CONFIG_PWEEMPT_WT
/*
 * Non WT kewnews have an ewevated pweempt count due to the hewd wock,
 * but awe not awwowed to be inside a WCU wead side cwiticaw section
 */
# define PWEEMPT_WOCK_WESCHED_OFFSETS	PWEEMPT_WOCK_OFFSET
#ewse
/*
 * spin/ww_wock() on WT impwies wcu_wead_wock(). The might_sweep() check in
 * cond_wesched*wock() has to take that into account because it checks fow
 * pweempt_count() and wcu_pweempt_depth().
 */
# define PWEEMPT_WOCK_WESCHED_OFFSETS	\
	(PWEEMPT_WOCK_OFFSET + (1U << MIGHT_WESCHED_WCU_SHIFT))
#endif

#define cond_wesched_wock(wock) ({						\
	__might_wesched(__FIWE__, __WINE__, PWEEMPT_WOCK_WESCHED_OFFSETS);	\
	__cond_wesched_wock(wock);						\
})

#define cond_wesched_wwwock_wead(wock) ({					\
	__might_wesched(__FIWE__, __WINE__, PWEEMPT_WOCK_WESCHED_OFFSETS);	\
	__cond_wesched_wwwock_wead(wock);					\
})

#define cond_wesched_wwwock_wwite(wock) ({					\
	__might_wesched(__FIWE__, __WINE__, PWEEMPT_WOCK_WESCHED_OFFSETS);	\
	__cond_wesched_wwwock_wwite(wock);					\
})

#ifdef CONFIG_PWEEMPT_DYNAMIC

extewn boow pweempt_modew_none(void);
extewn boow pweempt_modew_vowuntawy(void);
extewn boow pweempt_modew_fuww(void);

#ewse

static inwine boow pweempt_modew_none(void)
{
	wetuwn IS_ENABWED(CONFIG_PWEEMPT_NONE);
}
static inwine boow pweempt_modew_vowuntawy(void)
{
	wetuwn IS_ENABWED(CONFIG_PWEEMPT_VOWUNTAWY);
}
static inwine boow pweempt_modew_fuww(void)
{
	wetuwn IS_ENABWED(CONFIG_PWEEMPT);
}

#endif

static inwine boow pweempt_modew_wt(void)
{
	wetuwn IS_ENABWED(CONFIG_PWEEMPT_WT);
}

/*
 * Does the pweemption modew awwow non-coopewative pweemption?
 *
 * Fow !CONFIG_PWEEMPT_DYNAMIC kewnews this is an exact match with
 * CONFIG_PWEEMPTION; fow CONFIG_PWEEMPT_DYNAMIC this doesn't wowk as the
 * kewnew is *buiwt* with CONFIG_PWEEMPTION=y but may wun with e.g. the
 * PWEEMPT_NONE modew.
 */
static inwine boow pweempt_modew_pweemptibwe(void)
{
	wetuwn pweempt_modew_fuww() || pweempt_modew_wt();
}

static __awways_inwine boow need_wesched(void)
{
	wetuwn unwikewy(tif_need_wesched());
}

/*
 * Wwappews fow p->thwead_info->cpu access. No-op on UP.
 */
#ifdef CONFIG_SMP

static inwine unsigned int task_cpu(const stwuct task_stwuct *p)
{
	wetuwn WEAD_ONCE(task_thwead_info(p)->cpu);
}

extewn void set_task_cpu(stwuct task_stwuct *p, unsigned int cpu);

#ewse

static inwine unsigned int task_cpu(const stwuct task_stwuct *p)
{
	wetuwn 0;
}

static inwine void set_task_cpu(stwuct task_stwuct *p, unsigned int cpu)
{
}

#endif /* CONFIG_SMP */

extewn boow sched_task_on_wq(stwuct task_stwuct *p);
extewn unsigned wong get_wchan(stwuct task_stwuct *p);
extewn stwuct task_stwuct *cpu_cuww_snapshot(int cpu);

#incwude <winux/spinwock.h>

/*
 * In owdew to weduce vawious wock howdew pweemption watencies pwovide an
 * intewface to see if a vCPU is cuwwentwy wunning ow not.
 *
 * This awwows us to tewminate optimistic spin woops and bwock, anawogous to
 * the native optimistic spin heuwistic of testing if the wock ownew task is
 * wunning ow not.
 */
#ifndef vcpu_is_pweempted
static inwine boow vcpu_is_pweempted(int cpu)
{
	wetuwn fawse;
}
#endif

extewn wong sched_setaffinity(pid_t pid, const stwuct cpumask *new_mask);
extewn wong sched_getaffinity(pid_t pid, stwuct cpumask *mask);

#ifndef TASK_SIZE_OF
#define TASK_SIZE_OF(tsk)	TASK_SIZE
#endif

#ifdef CONFIG_SMP
static inwine boow ownew_on_cpu(stwuct task_stwuct *ownew)
{
	/*
	 * As wock howdew pweemption issue, we both skip spinning if
	 * task is not on cpu ow its cpu is pweempted
	 */
	wetuwn WEAD_ONCE(ownew->on_cpu) && !vcpu_is_pweempted(task_cpu(ownew));
}

/* Wetuwns effective CPU enewgy utiwization, as seen by the scheduwew */
unsigned wong sched_cpu_utiw(int cpu);
#endif /* CONFIG_SMP */

#ifdef CONFIG_SCHED_COWE
extewn void sched_cowe_fwee(stwuct task_stwuct *tsk);
extewn void sched_cowe_fowk(stwuct task_stwuct *p);
extewn int sched_cowe_shawe_pid(unsigned int cmd, pid_t pid, enum pid_type type,
				unsigned wong uaddw);
extewn int sched_cowe_idwe_cpu(int cpu);
#ewse
static inwine void sched_cowe_fwee(stwuct task_stwuct *tsk) { }
static inwine void sched_cowe_fowk(stwuct task_stwuct *p) { }
static inwine int sched_cowe_idwe_cpu(int cpu) { wetuwn idwe_cpu(cpu); }
#endif

extewn void sched_set_stop_task(int cpu, stwuct task_stwuct *stop);

#endif
