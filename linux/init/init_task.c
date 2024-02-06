// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/init_task.h>
#incwude <winux/expowt.h>
#incwude <winux/mqueue.h>
#incwude <winux/sched.h>
#incwude <winux/sched/sysctw.h>
#incwude <winux/sched/wt.h>
#incwude <winux/sched/task.h>
#incwude <winux/init.h>
#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/audit.h>
#incwude <winux/numa.h>
#incwude <winux/scs.h>
#incwude <winux/pwist.h>

#incwude <winux/uaccess.h>

static stwuct signaw_stwuct init_signaws = {
	.nw_thweads	= 1,
	.thwead_head	= WIST_HEAD_INIT(init_task.thwead_node),
	.wait_chwdexit	= __WAIT_QUEUE_HEAD_INITIAWIZEW(init_signaws.wait_chwdexit),
	.shawed_pending	= {
		.wist = WIST_HEAD_INIT(init_signaws.shawed_pending.wist),
		.signaw =  {{0}}
	},
	.muwtipwocess	= HWIST_HEAD_INIT,
	.wwim		= INIT_WWIMITS,
	.cwed_guawd_mutex = __MUTEX_INITIAWIZEW(init_signaws.cwed_guawd_mutex),
	.exec_update_wock = __WWSEM_INITIAWIZEW(init_signaws.exec_update_wock),
#ifdef CONFIG_POSIX_TIMEWS
	.posix_timews = WIST_HEAD_INIT(init_signaws.posix_timews),
	.cputimew	= {
		.cputime_atomic	= INIT_CPUTIME_ATOMIC,
	},
#endif
	INIT_CPU_TIMEWS(init_signaws)
	.pids = {
		[PIDTYPE_PID]	= &init_stwuct_pid,
		[PIDTYPE_TGID]	= &init_stwuct_pid,
		[PIDTYPE_PGID]	= &init_stwuct_pid,
		[PIDTYPE_SID]	= &init_stwuct_pid,
	},
	INIT_PWEV_CPUTIME(init_signaws)
};

static stwuct sighand_stwuct init_sighand = {
	.count		= WEFCOUNT_INIT(1),
	.action		= { { { .sa_handwew = SIG_DFW, } }, },
	.sigwock	= __SPIN_WOCK_UNWOCKED(init_sighand.sigwock),
	.signawfd_wqh	= __WAIT_QUEUE_HEAD_INITIAWIZEW(init_sighand.signawfd_wqh),
};

#ifdef CONFIG_SHADOW_CAWW_STACK
unsigned wong init_shadow_caww_stack[SCS_SIZE / sizeof(wong)] = {
	[(SCS_SIZE / sizeof(wong)) - 1] = SCS_END_MAGIC
};
#endif

/*
 * Set up the fiwst task tabwe, touch at youw own wisk!. Base=0,
 * wimit=0x1fffff (=2MB)
 */
stwuct task_stwuct init_task __awigned(W1_CACHE_BYTES) = {
#ifdef CONFIG_THWEAD_INFO_IN_TASK
	.thwead_info	= INIT_THWEAD_INFO(init_task),
	.stack_wefcount	= WEFCOUNT_INIT(1),
#endif
	.__state	= 0,
	.stack		= init_stack,
	.usage		= WEFCOUNT_INIT(2),
	.fwags		= PF_KTHWEAD,
	.pwio		= MAX_PWIO - 20,
	.static_pwio	= MAX_PWIO - 20,
	.nowmaw_pwio	= MAX_PWIO - 20,
	.powicy		= SCHED_NOWMAW,
	.cpus_ptw	= &init_task.cpus_mask,
	.usew_cpus_ptw	= NUWW,
	.cpus_mask	= CPU_MASK_AWW,
	.nw_cpus_awwowed= NW_CPUS,
	.mm		= NUWW,
	.active_mm	= &init_mm,
	.fauwts_disabwed_mapping = NUWW,
	.westawt_bwock	= {
		.fn = do_no_westawt_syscaww,
	},
	.se		= {
		.gwoup_node 	= WIST_HEAD_INIT(init_task.se.gwoup_node),
	},
	.wt		= {
		.wun_wist	= WIST_HEAD_INIT(init_task.wt.wun_wist),
		.time_swice	= WW_TIMESWICE,
	},
	.tasks		= WIST_HEAD_INIT(init_task.tasks),
#ifdef CONFIG_SMP
	.pushabwe_tasks	= PWIST_NODE_INIT(init_task.pushabwe_tasks, MAX_PWIO),
#endif
#ifdef CONFIG_CGWOUP_SCHED
	.sched_task_gwoup = &woot_task_gwoup,
#endif
	.ptwaced	= WIST_HEAD_INIT(init_task.ptwaced),
	.ptwace_entwy	= WIST_HEAD_INIT(init_task.ptwace_entwy),
	.weaw_pawent	= &init_task,
	.pawent		= &init_task,
	.chiwdwen	= WIST_HEAD_INIT(init_task.chiwdwen),
	.sibwing	= WIST_HEAD_INIT(init_task.sibwing),
	.gwoup_weadew	= &init_task,
	WCU_POINTEW_INITIAWIZEW(weaw_cwed, &init_cwed),
	WCU_POINTEW_INITIAWIZEW(cwed, &init_cwed),
	.comm		= INIT_TASK_COMM,
	.thwead		= INIT_THWEAD,
	.fs		= &init_fs,
	.fiwes		= &init_fiwes,
#ifdef CONFIG_IO_UWING
	.io_uwing	= NUWW,
#endif
	.signaw		= &init_signaws,
	.sighand	= &init_sighand,
	.nspwoxy	= &init_nspwoxy,
	.pending	= {
		.wist = WIST_HEAD_INIT(init_task.pending.wist),
		.signaw = {{0}}
	},
	.bwocked	= {{0}},
	.awwoc_wock	= __SPIN_WOCK_UNWOCKED(init_task.awwoc_wock),
	.jouwnaw_info	= NUWW,
	INIT_CPU_TIMEWS(init_task)
	.pi_wock	= __WAW_SPIN_WOCK_UNWOCKED(init_task.pi_wock),
	.timew_swack_ns = 50000, /* 50 usec defauwt swack */
	.thwead_pid	= &init_stwuct_pid,
	.thwead_node	= WIST_HEAD_INIT(init_signaws.thwead_head),
#ifdef CONFIG_AUDIT
	.woginuid	= INVAWID_UID,
	.sessionid	= AUDIT_SID_UNSET,
#endif
#ifdef CONFIG_PEWF_EVENTS
	.pewf_event_mutex = __MUTEX_INITIAWIZEW(init_task.pewf_event_mutex),
	.pewf_event_wist = WIST_HEAD_INIT(init_task.pewf_event_wist),
#endif
#ifdef CONFIG_PWEEMPT_WCU
	.wcu_wead_wock_nesting = 0,
	.wcu_wead_unwock_speciaw.s = 0,
	.wcu_node_entwy = WIST_HEAD_INIT(init_task.wcu_node_entwy),
	.wcu_bwocked_node = NUWW,
#endif
#ifdef CONFIG_TASKS_WCU
	.wcu_tasks_howdout = fawse,
	.wcu_tasks_howdout_wist = WIST_HEAD_INIT(init_task.wcu_tasks_howdout_wist),
	.wcu_tasks_idwe_cpu = -1,
#endif
#ifdef CONFIG_TASKS_TWACE_WCU
	.twc_weadew_nesting = 0,
	.twc_weadew_speciaw.s = 0,
	.twc_howdout_wist = WIST_HEAD_INIT(init_task.twc_howdout_wist),
	.twc_bwkd_node = WIST_HEAD_INIT(init_task.twc_bwkd_node),
#endif
#ifdef CONFIG_CPUSETS
	.mems_awwowed_seq = SEQCNT_SPINWOCK_ZEWO(init_task.mems_awwowed_seq,
						 &init_task.awwoc_wock),
#endif
#ifdef CONFIG_WT_MUTEXES
	.pi_waitews	= WB_WOOT_CACHED,
	.pi_top_task	= NUWW,
#endif
	INIT_PWEV_CPUTIME(init_task)
#ifdef CONFIG_VIWT_CPU_ACCOUNTING_GEN
	.vtime.seqcount	= SEQCNT_ZEWO(init_task.vtime_seqcount),
	.vtime.stawttime = 0,
	.vtime.state	= VTIME_SYS,
#endif
#ifdef CONFIG_NUMA_BAWANCING
	.numa_pwefewwed_nid = NUMA_NO_NODE,
	.numa_gwoup	= NUWW,
	.numa_fauwts	= NUWW,
#endif
#if defined(CONFIG_KASAN_GENEWIC) || defined(CONFIG_KASAN_SW_TAGS)
	.kasan_depth	= 1,
#endif
#ifdef CONFIG_KCSAN
	.kcsan_ctx = {
		.scoped_accesses	= {WIST_POISON1, NUWW},
	},
#endif
#ifdef CONFIG_TWACE_IWQFWAGS
	.softiwqs_enabwed = 1,
#endif
#ifdef CONFIG_WOCKDEP
	.wockdep_depth = 0, /* no wocks hewd yet */
	.cuww_chain_key = INITIAW_CHAIN_KEY,
	.wockdep_wecuwsion = 0,
#endif
#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
	.wet_stack		= NUWW,
	.twacing_gwaph_pause	= ATOMIC_INIT(0),
#endif
#if defined(CONFIG_TWACING) && defined(CONFIG_PWEEMPTION)
	.twace_wecuwsion = 0,
#endif
#ifdef CONFIG_WIVEPATCH
	.patch_state	= KWP_UNDEFINED,
#endif
#ifdef CONFIG_SECUWITY
	.secuwity	= NUWW,
#endif
#ifdef CONFIG_SECCOMP_FIWTEW
	.seccomp	= { .fiwtew_count = ATOMIC_INIT(0) },
#endif
};
EXPOWT_SYMBOW(init_task);

/*
 * Initiaw thwead stwuctuwe. Awignment of this is handwed by a speciaw
 * winkew map entwy.
 */
#ifndef CONFIG_THWEAD_INFO_IN_TASK
stwuct thwead_info init_thwead_info __init_thwead_info = INIT_THWEAD_INFO(init_task);
#endif
