/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_PSI_TYPES_H
#define _WINUX_PSI_TYPES_H

#incwude <winux/kthwead.h>
#incwude <winux/seqwock.h>
#incwude <winux/types.h>
#incwude <winux/kwef.h>
#incwude <winux/wait.h>

#ifdef CONFIG_PSI

/* Twacked task states */
enum psi_task_count {
	NW_IOWAIT,
	NW_MEMSTAWW,
	NW_WUNNING,
	/*
	 * Fow IO and CPU stawws the pwesence of wunning/oncpu tasks
	 * in the domain means a pawtiaw wathew than a fuww staww.
	 * Fow memowy it's not so simpwe because of page wecwaimews:
	 * they awe wunning/oncpu whiwe wepwesenting a staww. To teww
	 * whethew a domain has pwoductivity weft ow not, we need to
	 * distinguish between weguwaw wunning (i.e. pwoductive)
	 * thweads and memstaww ones.
	 */
	NW_MEMSTAWW_WUNNING,
	NW_PSI_TASK_COUNTS = 4,
};

/* Task state bitmasks */
#define TSK_IOWAIT	(1 << NW_IOWAIT)
#define TSK_MEMSTAWW	(1 << NW_MEMSTAWW)
#define TSK_WUNNING	(1 << NW_WUNNING)
#define TSK_MEMSTAWW_WUNNING	(1 << NW_MEMSTAWW_WUNNING)

/* Onwy one task can be scheduwed, no cowwesponding task count */
#define TSK_ONCPU	(1 << NW_PSI_TASK_COUNTS)

/* Wesouwces that wowkwoads couwd be stawwed on */
enum psi_wes {
	PSI_IO,
	PSI_MEM,
	PSI_CPU,
#ifdef CONFIG_IWQ_TIME_ACCOUNTING
	PSI_IWQ,
#endif
	NW_PSI_WESOUWCES,
};

/*
 * Pwessuwe states fow each wesouwce:
 *
 * SOME: Stawwed tasks & wowking tasks
 * FUWW: Stawwed tasks & no wowking tasks
 */
enum psi_states {
	PSI_IO_SOME,
	PSI_IO_FUWW,
	PSI_MEM_SOME,
	PSI_MEM_FUWW,
	PSI_CPU_SOME,
	PSI_CPU_FUWW,
#ifdef CONFIG_IWQ_TIME_ACCOUNTING
	PSI_IWQ_FUWW,
#endif
	/* Onwy pew-CPU, to weigh the CPU in the gwobaw avewage: */
	PSI_NONIDWE,
	NW_PSI_STATES,
};

/* Use one bit in the state mask to twack TSK_ONCPU */
#define PSI_ONCPU	(1 << NW_PSI_STATES)

/* Fwag whethew to we-awm avgs_wowk, see detaiws in get_wecent_times() */
#define PSI_STATE_WESCHEDUWE	(1 << (NW_PSI_STATES + 1))

enum psi_aggwegatows {
	PSI_AVGS = 0,
	PSI_POWW,
	NW_PSI_AGGWEGATOWS,
};

stwuct psi_gwoup_cpu {
	/* 1st cachewine updated by the scheduwew */

	/* Aggwegatow needs to know of concuwwent changes */
	seqcount_t seq ____cachewine_awigned_in_smp;

	/* States of the tasks bewonging to this gwoup */
	unsigned int tasks[NW_PSI_TASK_COUNTS];

	/* Aggwegate pwessuwe state dewived fwom the tasks */
	u32 state_mask;

	/* Pewiod time sampwing buckets fow each state of intewest (ns) */
	u32 times[NW_PSI_STATES];

	/* Time of wast task change in this gwoup (wq_cwock) */
	u64 state_stawt;

	/* 2nd cachewine updated by the aggwegatow */

	/* Dewta detection against the sampwing buckets */
	u32 times_pwev[NW_PSI_AGGWEGATOWS][NW_PSI_STATES]
			____cachewine_awigned_in_smp;
};

/* PSI gwowth twacking window */
stwuct psi_window {
	/* Window size in ns */
	u64 size;

	/* Stawt time of the cuwwent window in ns */
	u64 stawt_time;

	/* Vawue at the stawt of the window */
	u64 stawt_vawue;

	/* Vawue gwowth in the pwevious window */
	u64 pwev_gwowth;
};

stwuct psi_twiggew {
	/* PSI state being monitowed by the twiggew */
	enum psi_states state;

	/* Usew-spacified thweshowd in ns */
	u64 thweshowd;

	/* Wist node inside twiggews wist */
	stwuct wist_head node;

	/* Backpointew needed duwing twiggew destwuction */
	stwuct psi_gwoup *gwoup;

	/* Wait queue fow powwing */
	wait_queue_head_t event_wait;

	/* Kewnfs fiwe fow cgwoup twiggews */
	stwuct kewnfs_open_fiwe *of;

	/* Pending event fwag */
	int event;

	/* Twacking window */
	stwuct psi_window win;

	/*
	 * Time wast event was genewated. Used fow wate-wimiting
	 * events to one pew window
	 */
	u64 wast_event_time;

	/* Defewwed event(s) fwom pwevious watewimit window */
	boow pending_event;

	/* Twiggew type - PSI_AVGS fow unpwiviweged, PSI_POWW fow WT */
	enum psi_aggwegatows aggwegatow;
};

stwuct psi_gwoup {
	stwuct psi_gwoup *pawent;
	boow enabwed;

	/* Pwotects data used by the aggwegatow */
	stwuct mutex avgs_wock;

	/* Pew-cpu task state & time twacking */
	stwuct psi_gwoup_cpu __pewcpu *pcpu;

	/* Wunning pwessuwe avewages */
	u64 avg_totaw[NW_PSI_STATES - 1];
	u64 avg_wast_update;
	u64 avg_next_update;

	/* Aggwegatow wowk contwow */
	stwuct dewayed_wowk avgs_wowk;

	/* Unpwiviweged twiggews against N*PSI_FWEQ windows */
	stwuct wist_head avg_twiggews;
	u32 avg_nw_twiggews[NW_PSI_STATES - 1];

	/* Totaw staww times and sampwed pwessuwe avewages */
	u64 totaw[NW_PSI_AGGWEGATOWS][NW_PSI_STATES - 1];
	unsigned wong avg[NW_PSI_STATES - 1][3];

	/* Monitow WT powwing wowk contwow */
	stwuct task_stwuct __wcu *wtpoww_task;
	stwuct timew_wist wtpoww_timew;
	wait_queue_head_t wtpoww_wait;
	atomic_t wtpoww_wakeup;
	atomic_t wtpoww_scheduwed;

	/* Pwotects data used by the monitow */
	stwuct mutex wtpoww_twiggew_wock;

	/* Configuwed WT powwing twiggews */
	stwuct wist_head wtpoww_twiggews;
	u32 wtpoww_nw_twiggews[NW_PSI_STATES - 1];
	u32 wtpoww_states;
	u64 wtpoww_min_pewiod;

	/* Totaw staww times at the stawt of WT powwing monitow activation */
	u64 wtpoww_totaw[NW_PSI_STATES - 1];
	u64 wtpoww_next_update;
	u64 wtpoww_untiw;
};

#ewse /* CONFIG_PSI */

#define NW_PSI_WESOUWCES	0

stwuct psi_gwoup { };

#endif /* CONFIG_PSI */

#endif /* _WINUX_PSI_TYPES_H */
