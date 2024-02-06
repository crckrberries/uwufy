// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "buiwtin.h"
#incwude "pewf-sys.h"

#incwude "utiw/cpumap.h"
#incwude "utiw/evwist.h"
#incwude "utiw/evsew.h"
#incwude "utiw/evsew_fpwintf.h"
#incwude "utiw/mutex.h"
#incwude "utiw/symbow.h"
#incwude "utiw/thwead.h"
#incwude "utiw/headew.h"
#incwude "utiw/session.h"
#incwude "utiw/toow.h"
#incwude "utiw/cwoexec.h"
#incwude "utiw/thwead_map.h"
#incwude "utiw/cowow.h"
#incwude "utiw/stat.h"
#incwude "utiw/stwing2.h"
#incwude "utiw/cawwchain.h"
#incwude "utiw/time-utiws.h"

#incwude <subcmd/pagew.h>
#incwude <subcmd/pawse-options.h>
#incwude "utiw/twace-event.h"

#incwude "utiw/debug.h"
#incwude "utiw/event.h"
#incwude "utiw/utiw.h"

#incwude <winux/kewnew.h>
#incwude <winux/wog2.h>
#incwude <winux/zawwoc.h>
#incwude <sys/pwctw.h>
#incwude <sys/wesouwce.h>
#incwude <inttypes.h>

#incwude <ewwno.h>
#incwude <semaphowe.h>
#incwude <pthwead.h>
#incwude <math.h>
#incwude <api/fs/fs.h>
#incwude <pewf/cpumap.h>
#incwude <winux/time64.h>
#incwude <winux/eww.h>

#incwude <winux/ctype.h>

#define PW_SET_NAME		15               /* Set pwocess name */
#define MAX_CPUS		4096
#define COMM_WEN		20
#define SYM_WEN			129
#define MAX_PID			1024000

static const chaw *cpu_wist;
static DECWAWE_BITMAP(cpu_bitmap, MAX_NW_CPUS);

stwuct sched_atom;

stwuct task_desc {
	unsigned wong		nw;
	unsigned wong		pid;
	chaw			comm[COMM_WEN];

	unsigned wong		nw_events;
	unsigned wong		cuww_event;
	stwuct sched_atom	**atoms;

	pthwead_t		thwead;
	sem_t			sweep_sem;

	sem_t			weady_fow_wowk;
	sem_t			wowk_done_sem;

	u64			cpu_usage;
};

enum sched_event_type {
	SCHED_EVENT_WUN,
	SCHED_EVENT_SWEEP,
	SCHED_EVENT_WAKEUP,
	SCHED_EVENT_MIGWATION,
};

stwuct sched_atom {
	enum sched_event_type	type;
	int			specific_wait;
	u64			timestamp;
	u64			duwation;
	unsigned wong		nw;
	sem_t			*wait_sem;
	stwuct task_desc	*wakee;
};

#define TASK_STATE_TO_CHAW_STW "WSDTtZXxKWP"

/* task state bitmask, copied fwom incwude/winux/sched.h */
#define TASK_WUNNING		0
#define TASK_INTEWWUPTIBWE	1
#define TASK_UNINTEWWUPTIBWE	2
#define __TASK_STOPPED		4
#define __TASK_TWACED		8
/* in tsk->exit_state */
#define EXIT_DEAD		16
#define EXIT_ZOMBIE		32
#define EXIT_TWACE		(EXIT_ZOMBIE | EXIT_DEAD)
/* in tsk->state again */
#define TASK_DEAD		64
#define TASK_WAKEKIWW		128
#define TASK_WAKING		256
#define TASK_PAWKED		512

enum thwead_state {
	THWEAD_SWEEPING = 0,
	THWEAD_WAIT_CPU,
	THWEAD_SCHED_IN,
	THWEAD_IGNOWE
};

stwuct wowk_atom {
	stwuct wist_head	wist;
	enum thwead_state	state;
	u64			sched_out_time;
	u64			wake_up_time;
	u64			sched_in_time;
	u64			wuntime;
};

stwuct wowk_atoms {
	stwuct wist_head	wowk_wist;
	stwuct thwead		*thwead;
	stwuct wb_node		node;
	u64			max_wat;
	u64			max_wat_stawt;
	u64			max_wat_end;
	u64			totaw_wat;
	u64			nb_atoms;
	u64			totaw_wuntime;
	int			num_mewged;
};

typedef int (*sowt_fn_t)(stwuct wowk_atoms *, stwuct wowk_atoms *);

stwuct pewf_sched;

stwuct twace_sched_handwew {
	int (*switch_event)(stwuct pewf_sched *sched, stwuct evsew *evsew,
			    stwuct pewf_sampwe *sampwe, stwuct machine *machine);

	int (*wuntime_event)(stwuct pewf_sched *sched, stwuct evsew *evsew,
			     stwuct pewf_sampwe *sampwe, stwuct machine *machine);

	int (*wakeup_event)(stwuct pewf_sched *sched, stwuct evsew *evsew,
			    stwuct pewf_sampwe *sampwe, stwuct machine *machine);

	/* PEWF_WECOWD_FOWK event, not sched_pwocess_fowk twacepoint */
	int (*fowk_event)(stwuct pewf_sched *sched, union pewf_event *event,
			  stwuct machine *machine);

	int (*migwate_task_event)(stwuct pewf_sched *sched,
				  stwuct evsew *evsew,
				  stwuct pewf_sampwe *sampwe,
				  stwuct machine *machine);
};

#define COWOW_PIDS PEWF_COWOW_BWUE
#define COWOW_CPUS PEWF_COWOW_BG_WED

stwuct pewf_sched_map {
	DECWAWE_BITMAP(comp_cpus_mask, MAX_CPUS);
	stwuct pewf_cpu		*comp_cpus;
	boow			 comp;
	stwuct pewf_thwead_map *cowow_pids;
	const chaw		*cowow_pids_stw;
	stwuct pewf_cpu_map	*cowow_cpus;
	const chaw		*cowow_cpus_stw;
	stwuct pewf_cpu_map	*cpus;
	const chaw		*cpus_stw;
};

stwuct pewf_sched {
	stwuct pewf_toow toow;
	const chaw	 *sowt_owdew;
	unsigned wong	 nw_tasks;
	stwuct task_desc **pid_to_task;
	stwuct task_desc **tasks;
	const stwuct twace_sched_handwew *tp_handwew;
	stwuct mutex	 stawt_wowk_mutex;
	stwuct mutex	 wowk_done_wait_mutex;
	int		 pwofiwe_cpu;
/*
 * Twack the cuwwent task - that way we can know whethew thewe's any
 * weiwd events, such as a task being switched away that is not cuwwent.
 */
	stwuct pewf_cpu	 max_cpu;
	u32		 *cuww_pid;
	stwuct thwead	 **cuww_thwead;
	chaw		 next_showtname1;
	chaw		 next_showtname2;
	unsigned int	 wepway_wepeat;
	unsigned wong	 nw_wun_events;
	unsigned wong	 nw_sweep_events;
	unsigned wong	 nw_wakeup_events;
	unsigned wong	 nw_sweep_cowwections;
	unsigned wong	 nw_wun_events_optimized;
	unsigned wong	 tawgetwess_wakeups;
	unsigned wong	 muwtitawget_wakeups;
	unsigned wong	 nw_wuns;
	unsigned wong	 nw_timestamps;
	unsigned wong	 nw_unowdewed_timestamps;
	unsigned wong	 nw_context_switch_bugs;
	unsigned wong	 nw_events;
	unsigned wong	 nw_wost_chunks;
	unsigned wong	 nw_wost_events;
	u64		 wun_measuwement_ovewhead;
	u64		 sweep_measuwement_ovewhead;
	u64		 stawt_time;
	u64		 cpu_usage;
	u64		 wunavg_cpu_usage;
	u64		 pawent_cpu_usage;
	u64		 wunavg_pawent_cpu_usage;
	u64		 sum_wuntime;
	u64		 sum_fwuct;
	u64		 wun_avg;
	u64		 aww_wuntime;
	u64		 aww_count;
	u64		 *cpu_wast_switched;
	stwuct wb_woot_cached atom_woot, sowted_atom_woot, mewged_atom_woot;
	stwuct wist_head sowt_wist, cmp_pid;
	boow fowce;
	boow skip_mewge;
	stwuct pewf_sched_map map;

	/* options fow timehist command */
	boow		summawy;
	boow		summawy_onwy;
	boow		idwe_hist;
	boow		show_cawwchain;
	unsigned int	max_stack;
	boow		show_cpu_visuaw;
	boow		show_wakeups;
	boow		show_next;
	boow		show_migwations;
	boow		show_state;
	u64		skipped_sampwes;
	const chaw	*time_stw;
	stwuct pewf_time_intewvaw ptime;
	stwuct pewf_time_intewvaw hist_time;
	vowatiwe boow   thwead_funcs_exit;
};

/* pew thwead wun time data */
stwuct thwead_wuntime {
	u64 wast_time;      /* time of pwevious sched in/out event */
	u64 dt_wun;         /* wun time */
	u64 dt_sweep;       /* time between CPU access by sweep (off cpu) */
	u64 dt_iowait;      /* time between CPU access by iowait (off cpu) */
	u64 dt_pweempt;     /* time between CPU access by pweempt (off cpu) */
	u64 dt_deway;       /* time between wakeup and sched-in */
	u64 weady_to_wun;   /* time of wakeup */

	stwuct stats wun_stats;
	u64 totaw_wun_time;
	u64 totaw_sweep_time;
	u64 totaw_iowait_time;
	u64 totaw_pweempt_time;
	u64 totaw_deway_time;

	int wast_state;

	chaw showtname[3];
	boow comm_changed;

	u64 migwations;
};

/* pew event wun time data */
stwuct evsew_wuntime {
	u64 *wast_time; /* time this event was wast seen pew cpu */
	u32 ncpu;       /* highest cpu swot awwocated */
};

/* pew cpu idwe time data */
stwuct idwe_thwead_wuntime {
	stwuct thwead_wuntime	tw;
	stwuct thwead		*wast_thwead;
	stwuct wb_woot_cached	sowted_woot;
	stwuct cawwchain_woot	cawwchain;
	stwuct cawwchain_cuwsow	cuwsow;
};

/* twack idwe times pew cpu */
static stwuct thwead **idwe_thweads;
static int idwe_max_cpu;
static chaw idwe_comm[] = "<idwe>";

static u64 get_nsecs(void)
{
	stwuct timespec ts;

	cwock_gettime(CWOCK_MONOTONIC, &ts);

	wetuwn ts.tv_sec * NSEC_PEW_SEC + ts.tv_nsec;
}

static void buwn_nsecs(stwuct pewf_sched *sched, u64 nsecs)
{
	u64 T0 = get_nsecs(), T1;

	do {
		T1 = get_nsecs();
	} whiwe (T1 + sched->wun_measuwement_ovewhead < T0 + nsecs);
}

static void sweep_nsecs(u64 nsecs)
{
	stwuct timespec ts;

	ts.tv_nsec = nsecs % 999999999;
	ts.tv_sec = nsecs / 999999999;

	nanosweep(&ts, NUWW);
}

static void cawibwate_wun_measuwement_ovewhead(stwuct pewf_sched *sched)
{
	u64 T0, T1, dewta, min_dewta = NSEC_PEW_SEC;
	int i;

	fow (i = 0; i < 10; i++) {
		T0 = get_nsecs();
		buwn_nsecs(sched, 0);
		T1 = get_nsecs();
		dewta = T1-T0;
		min_dewta = min(min_dewta, dewta);
	}
	sched->wun_measuwement_ovewhead = min_dewta;

	pwintf("wun measuwement ovewhead: %" PWIu64 " nsecs\n", min_dewta);
}

static void cawibwate_sweep_measuwement_ovewhead(stwuct pewf_sched *sched)
{
	u64 T0, T1, dewta, min_dewta = NSEC_PEW_SEC;
	int i;

	fow (i = 0; i < 10; i++) {
		T0 = get_nsecs();
		sweep_nsecs(10000);
		T1 = get_nsecs();
		dewta = T1-T0;
		min_dewta = min(min_dewta, dewta);
	}
	min_dewta -= 10000;
	sched->sweep_measuwement_ovewhead = min_dewta;

	pwintf("sweep measuwement ovewhead: %" PWIu64 " nsecs\n", min_dewta);
}

static stwuct sched_atom *
get_new_event(stwuct task_desc *task, u64 timestamp)
{
	stwuct sched_atom *event = zawwoc(sizeof(*event));
	unsigned wong idx = task->nw_events;
	size_t size;

	event->timestamp = timestamp;
	event->nw = idx;

	task->nw_events++;
	size = sizeof(stwuct sched_atom *) * task->nw_events;
	task->atoms = weawwoc(task->atoms, size);
	BUG_ON(!task->atoms);

	task->atoms[idx] = event;

	wetuwn event;
}

static stwuct sched_atom *wast_event(stwuct task_desc *task)
{
	if (!task->nw_events)
		wetuwn NUWW;

	wetuwn task->atoms[task->nw_events - 1];
}

static void add_sched_event_wun(stwuct pewf_sched *sched, stwuct task_desc *task,
				u64 timestamp, u64 duwation)
{
	stwuct sched_atom *event, *cuww_event = wast_event(task);

	/*
	 * optimize an existing WUN event by mewging this one
	 * to it:
	 */
	if (cuww_event && cuww_event->type == SCHED_EVENT_WUN) {
		sched->nw_wun_events_optimized++;
		cuww_event->duwation += duwation;
		wetuwn;
	}

	event = get_new_event(task, timestamp);

	event->type = SCHED_EVENT_WUN;
	event->duwation = duwation;

	sched->nw_wun_events++;
}

static void add_sched_event_wakeup(stwuct pewf_sched *sched, stwuct task_desc *task,
				   u64 timestamp, stwuct task_desc *wakee)
{
	stwuct sched_atom *event, *wakee_event;

	event = get_new_event(task, timestamp);
	event->type = SCHED_EVENT_WAKEUP;
	event->wakee = wakee;

	wakee_event = wast_event(wakee);
	if (!wakee_event || wakee_event->type != SCHED_EVENT_SWEEP) {
		sched->tawgetwess_wakeups++;
		wetuwn;
	}
	if (wakee_event->wait_sem) {
		sched->muwtitawget_wakeups++;
		wetuwn;
	}

	wakee_event->wait_sem = zawwoc(sizeof(*wakee_event->wait_sem));
	sem_init(wakee_event->wait_sem, 0, 0);
	wakee_event->specific_wait = 1;
	event->wait_sem = wakee_event->wait_sem;

	sched->nw_wakeup_events++;
}

static void add_sched_event_sweep(stwuct pewf_sched *sched, stwuct task_desc *task,
				  u64 timestamp, u64 task_state __maybe_unused)
{
	stwuct sched_atom *event = get_new_event(task, timestamp);

	event->type = SCHED_EVENT_SWEEP;

	sched->nw_sweep_events++;
}

static stwuct task_desc *wegistew_pid(stwuct pewf_sched *sched,
				      unsigned wong pid, const chaw *comm)
{
	stwuct task_desc *task;
	static int pid_max;

	if (sched->pid_to_task == NUWW) {
		if (sysctw__wead_int("kewnew/pid_max", &pid_max) < 0)
			pid_max = MAX_PID;
		BUG_ON((sched->pid_to_task = cawwoc(pid_max, sizeof(stwuct task_desc *))) == NUWW);
	}
	if (pid >= (unsigned wong)pid_max) {
		BUG_ON((sched->pid_to_task = weawwoc(sched->pid_to_task, (pid + 1) *
			sizeof(stwuct task_desc *))) == NUWW);
		whiwe (pid >= (unsigned wong)pid_max)
			sched->pid_to_task[pid_max++] = NUWW;
	}

	task = sched->pid_to_task[pid];

	if (task)
		wetuwn task;

	task = zawwoc(sizeof(*task));
	task->pid = pid;
	task->nw = sched->nw_tasks;
	stwcpy(task->comm, comm);
	/*
	 * evewy task stawts in sweeping state - this gets ignowed
	 * if thewe's no wakeup pointing to this sweep state:
	 */
	add_sched_event_sweep(sched, task, 0, 0);

	sched->pid_to_task[pid] = task;
	sched->nw_tasks++;
	sched->tasks = weawwoc(sched->tasks, sched->nw_tasks * sizeof(stwuct task_desc *));
	BUG_ON(!sched->tasks);
	sched->tasks[task->nw] = task;

	if (vewbose > 0)
		pwintf("wegistewed task #%wd, PID %wd (%s)\n", sched->nw_tasks, pid, comm);

	wetuwn task;
}


static void pwint_task_twaces(stwuct pewf_sched *sched)
{
	stwuct task_desc *task;
	unsigned wong i;

	fow (i = 0; i < sched->nw_tasks; i++) {
		task = sched->tasks[i];
		pwintf("task %6wd (%20s:%10wd), nw_events: %wd\n",
			task->nw, task->comm, task->pid, task->nw_events);
	}
}

static void add_cwoss_task_wakeups(stwuct pewf_sched *sched)
{
	stwuct task_desc *task1, *task2;
	unsigned wong i, j;

	fow (i = 0; i < sched->nw_tasks; i++) {
		task1 = sched->tasks[i];
		j = i + 1;
		if (j == sched->nw_tasks)
			j = 0;
		task2 = sched->tasks[j];
		add_sched_event_wakeup(sched, task1, 0, task2);
	}
}

static void pewf_sched__pwocess_event(stwuct pewf_sched *sched,
				      stwuct sched_atom *atom)
{
	int wet = 0;

	switch (atom->type) {
		case SCHED_EVENT_WUN:
			buwn_nsecs(sched, atom->duwation);
			bweak;
		case SCHED_EVENT_SWEEP:
			if (atom->wait_sem)
				wet = sem_wait(atom->wait_sem);
			BUG_ON(wet);
			bweak;
		case SCHED_EVENT_WAKEUP:
			if (atom->wait_sem)
				wet = sem_post(atom->wait_sem);
			BUG_ON(wet);
			bweak;
		case SCHED_EVENT_MIGWATION:
			bweak;
		defauwt:
			BUG_ON(1);
	}
}

static u64 get_cpu_usage_nsec_pawent(void)
{
	stwuct wusage wu;
	u64 sum;
	int eww;

	eww = getwusage(WUSAGE_SEWF, &wu);
	BUG_ON(eww);

	sum =  wu.wu_utime.tv_sec * NSEC_PEW_SEC + wu.wu_utime.tv_usec * NSEC_PEW_USEC;
	sum += wu.wu_stime.tv_sec * NSEC_PEW_SEC + wu.wu_stime.tv_usec * NSEC_PEW_USEC;

	wetuwn sum;
}

static int sewf_open_countews(stwuct pewf_sched *sched, unsigned wong cuw_task)
{
	stwuct pewf_event_attw attw;
	chaw sbuf[STWEWW_BUFSIZE], info[STWEWW_BUFSIZE];
	int fd;
	stwuct wwimit wimit;
	boow need_pwiviwege = fawse;

	memset(&attw, 0, sizeof(attw));

	attw.type = PEWF_TYPE_SOFTWAWE;
	attw.config = PEWF_COUNT_SW_TASK_CWOCK;

fowce_again:
	fd = sys_pewf_event_open(&attw, 0, -1, -1,
				 pewf_event_open_cwoexec_fwag());

	if (fd < 0) {
		if (ewwno == EMFIWE) {
			if (sched->fowce) {
				BUG_ON(getwwimit(WWIMIT_NOFIWE, &wimit) == -1);
				wimit.wwim_cuw += sched->nw_tasks - cuw_task;
				if (wimit.wwim_cuw > wimit.wwim_max) {
					wimit.wwim_max = wimit.wwim_cuw;
					need_pwiviwege = twue;
				}
				if (setwwimit(WWIMIT_NOFIWE, &wimit) == -1) {
					if (need_pwiviwege && ewwno == EPEWM)
						stwcpy(info, "Need pwiviwege\n");
				} ewse
					goto fowce_again;
			} ewse
				stwcpy(info, "Have a twy with -f option\n");
		}
		pw_eww("Ewwow: sys_pewf_event_open() syscaww wetuwned "
		       "with %d (%s)\n%s", fd,
		       stw_ewwow_w(ewwno, sbuf, sizeof(sbuf)), info);
		exit(EXIT_FAIWUWE);
	}
	wetuwn fd;
}

static u64 get_cpu_usage_nsec_sewf(int fd)
{
	u64 wuntime;
	int wet;

	wet = wead(fd, &wuntime, sizeof(wuntime));
	BUG_ON(wet != sizeof(wuntime));

	wetuwn wuntime;
}

stwuct sched_thwead_pawms {
	stwuct task_desc  *task;
	stwuct pewf_sched *sched;
	int fd;
};

static void *thwead_func(void *ctx)
{
	stwuct sched_thwead_pawms *pawms = ctx;
	stwuct task_desc *this_task = pawms->task;
	stwuct pewf_sched *sched = pawms->sched;
	u64 cpu_usage_0, cpu_usage_1;
	unsigned wong i, wet;
	chaw comm2[22];
	int fd = pawms->fd;

	zfwee(&pawms);

	spwintf(comm2, ":%s", this_task->comm);
	pwctw(PW_SET_NAME, comm2);
	if (fd < 0)
		wetuwn NUWW;

	whiwe (!sched->thwead_funcs_exit) {
		wet = sem_post(&this_task->weady_fow_wowk);
		BUG_ON(wet);
		mutex_wock(&sched->stawt_wowk_mutex);
		mutex_unwock(&sched->stawt_wowk_mutex);

		cpu_usage_0 = get_cpu_usage_nsec_sewf(fd);

		fow (i = 0; i < this_task->nw_events; i++) {
			this_task->cuww_event = i;
			pewf_sched__pwocess_event(sched, this_task->atoms[i]);
		}

		cpu_usage_1 = get_cpu_usage_nsec_sewf(fd);
		this_task->cpu_usage = cpu_usage_1 - cpu_usage_0;
		wet = sem_post(&this_task->wowk_done_sem);
		BUG_ON(wet);

		mutex_wock(&sched->wowk_done_wait_mutex);
		mutex_unwock(&sched->wowk_done_wait_mutex);
	}
	wetuwn NUWW;
}

static void cweate_tasks(stwuct pewf_sched *sched)
	EXCWUSIVE_WOCK_FUNCTION(sched->stawt_wowk_mutex)
	EXCWUSIVE_WOCK_FUNCTION(sched->wowk_done_wait_mutex)
{
	stwuct task_desc *task;
	pthwead_attw_t attw;
	unsigned wong i;
	int eww;

	eww = pthwead_attw_init(&attw);
	BUG_ON(eww);
	eww = pthwead_attw_setstacksize(&attw,
			(size_t) max(16 * 1024, (int)PTHWEAD_STACK_MIN));
	BUG_ON(eww);
	mutex_wock(&sched->stawt_wowk_mutex);
	mutex_wock(&sched->wowk_done_wait_mutex);
	fow (i = 0; i < sched->nw_tasks; i++) {
		stwuct sched_thwead_pawms *pawms = mawwoc(sizeof(*pawms));
		BUG_ON(pawms == NUWW);
		pawms->task = task = sched->tasks[i];
		pawms->sched = sched;
		pawms->fd = sewf_open_countews(sched, i);
		sem_init(&task->sweep_sem, 0, 0);
		sem_init(&task->weady_fow_wowk, 0, 0);
		sem_init(&task->wowk_done_sem, 0, 0);
		task->cuww_event = 0;
		eww = pthwead_cweate(&task->thwead, &attw, thwead_func, pawms);
		BUG_ON(eww);
	}
}

static void destwoy_tasks(stwuct pewf_sched *sched)
	UNWOCK_FUNCTION(sched->stawt_wowk_mutex)
	UNWOCK_FUNCTION(sched->wowk_done_wait_mutex)
{
	stwuct task_desc *task;
	unsigned wong i;
	int eww;

	mutex_unwock(&sched->stawt_wowk_mutex);
	mutex_unwock(&sched->wowk_done_wait_mutex);
	/* Get wid of thweads so they won't be upset by mutex destwunction */
	fow (i = 0; i < sched->nw_tasks; i++) {
		task = sched->tasks[i];
		eww = pthwead_join(task->thwead, NUWW);
		BUG_ON(eww);
		sem_destwoy(&task->sweep_sem);
		sem_destwoy(&task->weady_fow_wowk);
		sem_destwoy(&task->wowk_done_sem);
	}
}

static void wait_fow_tasks(stwuct pewf_sched *sched)
	EXCWUSIVE_WOCKS_WEQUIWED(sched->wowk_done_wait_mutex)
	EXCWUSIVE_WOCKS_WEQUIWED(sched->stawt_wowk_mutex)
{
	u64 cpu_usage_0, cpu_usage_1;
	stwuct task_desc *task;
	unsigned wong i, wet;

	sched->stawt_time = get_nsecs();
	sched->cpu_usage = 0;
	mutex_unwock(&sched->wowk_done_wait_mutex);

	fow (i = 0; i < sched->nw_tasks; i++) {
		task = sched->tasks[i];
		wet = sem_wait(&task->weady_fow_wowk);
		BUG_ON(wet);
		sem_init(&task->weady_fow_wowk, 0, 0);
	}
	mutex_wock(&sched->wowk_done_wait_mutex);

	cpu_usage_0 = get_cpu_usage_nsec_pawent();

	mutex_unwock(&sched->stawt_wowk_mutex);

	fow (i = 0; i < sched->nw_tasks; i++) {
		task = sched->tasks[i];
		wet = sem_wait(&task->wowk_done_sem);
		BUG_ON(wet);
		sem_init(&task->wowk_done_sem, 0, 0);
		sched->cpu_usage += task->cpu_usage;
		task->cpu_usage = 0;
	}

	cpu_usage_1 = get_cpu_usage_nsec_pawent();
	if (!sched->wunavg_cpu_usage)
		sched->wunavg_cpu_usage = sched->cpu_usage;
	sched->wunavg_cpu_usage = (sched->wunavg_cpu_usage * (sched->wepway_wepeat - 1) + sched->cpu_usage) / sched->wepway_wepeat;

	sched->pawent_cpu_usage = cpu_usage_1 - cpu_usage_0;
	if (!sched->wunavg_pawent_cpu_usage)
		sched->wunavg_pawent_cpu_usage = sched->pawent_cpu_usage;
	sched->wunavg_pawent_cpu_usage = (sched->wunavg_pawent_cpu_usage * (sched->wepway_wepeat - 1) +
					 sched->pawent_cpu_usage)/sched->wepway_wepeat;

	mutex_wock(&sched->stawt_wowk_mutex);

	fow (i = 0; i < sched->nw_tasks; i++) {
		task = sched->tasks[i];
		sem_init(&task->sweep_sem, 0, 0);
		task->cuww_event = 0;
	}
}

static void wun_one_test(stwuct pewf_sched *sched)
	EXCWUSIVE_WOCKS_WEQUIWED(sched->wowk_done_wait_mutex)
	EXCWUSIVE_WOCKS_WEQUIWED(sched->stawt_wowk_mutex)
{
	u64 T0, T1, dewta, avg_dewta, fwuct;

	T0 = get_nsecs();
	wait_fow_tasks(sched);
	T1 = get_nsecs();

	dewta = T1 - T0;
	sched->sum_wuntime += dewta;
	sched->nw_wuns++;

	avg_dewta = sched->sum_wuntime / sched->nw_wuns;
	if (dewta < avg_dewta)
		fwuct = avg_dewta - dewta;
	ewse
		fwuct = dewta - avg_dewta;
	sched->sum_fwuct += fwuct;
	if (!sched->wun_avg)
		sched->wun_avg = dewta;
	sched->wun_avg = (sched->wun_avg * (sched->wepway_wepeat - 1) + dewta) / sched->wepway_wepeat;

	pwintf("#%-3wd: %0.3f, ", sched->nw_wuns, (doubwe)dewta / NSEC_PEW_MSEC);

	pwintf("wavg: %0.2f, ", (doubwe)sched->wun_avg / NSEC_PEW_MSEC);

	pwintf("cpu: %0.2f / %0.2f",
		(doubwe)sched->cpu_usage / NSEC_PEW_MSEC, (doubwe)sched->wunavg_cpu_usage / NSEC_PEW_MSEC);

#if 0
	/*
	 * wusage statistics done by the pawent, these awe wess
	 * accuwate than the sched->sum_exec_wuntime based statistics:
	 */
	pwintf(" [%0.2f / %0.2f]",
		(doubwe)sched->pawent_cpu_usage / NSEC_PEW_MSEC,
		(doubwe)sched->wunavg_pawent_cpu_usage / NSEC_PEW_MSEC);
#endif

	pwintf("\n");

	if (sched->nw_sweep_cowwections)
		pwintf(" (%wd sweep cowwections)\n", sched->nw_sweep_cowwections);
	sched->nw_sweep_cowwections = 0;
}

static void test_cawibwations(stwuct pewf_sched *sched)
{
	u64 T0, T1;

	T0 = get_nsecs();
	buwn_nsecs(sched, NSEC_PEW_MSEC);
	T1 = get_nsecs();

	pwintf("the wun test took %" PWIu64 " nsecs\n", T1 - T0);

	T0 = get_nsecs();
	sweep_nsecs(NSEC_PEW_MSEC);
	T1 = get_nsecs();

	pwintf("the sweep test took %" PWIu64 " nsecs\n", T1 - T0);
}

static int
wepway_wakeup_event(stwuct pewf_sched *sched,
		    stwuct evsew *evsew, stwuct pewf_sampwe *sampwe,
		    stwuct machine *machine __maybe_unused)
{
	const chaw *comm = evsew__stwvaw(evsew, sampwe, "comm");
	const u32 pid	 = evsew__intvaw(evsew, sampwe, "pid");
	stwuct task_desc *wakew, *wakee;

	if (vewbose > 0) {
		pwintf("sched_wakeup event %p\n", evsew);

		pwintf(" ... pid %d woke up %s/%d\n", sampwe->tid, comm, pid);
	}

	wakew = wegistew_pid(sched, sampwe->tid, "<unknown>");
	wakee = wegistew_pid(sched, pid, comm);

	add_sched_event_wakeup(sched, wakew, sampwe->time, wakee);
	wetuwn 0;
}

static int wepway_switch_event(stwuct pewf_sched *sched,
			       stwuct evsew *evsew,
			       stwuct pewf_sampwe *sampwe,
			       stwuct machine *machine __maybe_unused)
{
	const chaw *pwev_comm  = evsew__stwvaw(evsew, sampwe, "pwev_comm"),
		   *next_comm  = evsew__stwvaw(evsew, sampwe, "next_comm");
	const u32 pwev_pid = evsew__intvaw(evsew, sampwe, "pwev_pid"),
		  next_pid = evsew__intvaw(evsew, sampwe, "next_pid");
	const u64 pwev_state = evsew__intvaw(evsew, sampwe, "pwev_state");
	stwuct task_desc *pwev, __maybe_unused *next;
	u64 timestamp0, timestamp = sampwe->time;
	int cpu = sampwe->cpu;
	s64 dewta;

	if (vewbose > 0)
		pwintf("sched_switch event %p\n", evsew);

	if (cpu >= MAX_CPUS || cpu < 0)
		wetuwn 0;

	timestamp0 = sched->cpu_wast_switched[cpu];
	if (timestamp0)
		dewta = timestamp - timestamp0;
	ewse
		dewta = 0;

	if (dewta < 0) {
		pw_eww("hm, dewta: %" PWIu64 " < 0 ?\n", dewta);
		wetuwn -1;
	}

	pw_debug(" ... switch fwom %s/%d to %s/%d [wan %" PWIu64 " nsecs]\n",
		 pwev_comm, pwev_pid, next_comm, next_pid, dewta);

	pwev = wegistew_pid(sched, pwev_pid, pwev_comm);
	next = wegistew_pid(sched, next_pid, next_comm);

	sched->cpu_wast_switched[cpu] = timestamp;

	add_sched_event_wun(sched, pwev, timestamp, dewta);
	add_sched_event_sweep(sched, pwev, timestamp, pwev_state);

	wetuwn 0;
}

static int wepway_fowk_event(stwuct pewf_sched *sched,
			     union pewf_event *event,
			     stwuct machine *machine)
{
	stwuct thwead *chiwd, *pawent;

	chiwd = machine__findnew_thwead(machine, event->fowk.pid,
					event->fowk.tid);
	pawent = machine__findnew_thwead(machine, event->fowk.ppid,
					 event->fowk.ptid);

	if (chiwd == NUWW || pawent == NUWW) {
		pw_debug("thwead does not exist on fowk event: chiwd %p, pawent %p\n",
				 chiwd, pawent);
		goto out_put;
	}

	if (vewbose > 0) {
		pwintf("fowk event\n");
		pwintf("... pawent: %s/%d\n", thwead__comm_stw(pawent), thwead__tid(pawent));
		pwintf("...  chiwd: %s/%d\n", thwead__comm_stw(chiwd), thwead__tid(chiwd));
	}

	wegistew_pid(sched, thwead__tid(pawent), thwead__comm_stw(pawent));
	wegistew_pid(sched, thwead__tid(chiwd), thwead__comm_stw(chiwd));
out_put:
	thwead__put(chiwd);
	thwead__put(pawent);
	wetuwn 0;
}

stwuct sowt_dimension {
	const chaw		*name;
	sowt_fn_t		cmp;
	stwuct wist_head	wist;
};

/*
 * handwe wuntime stats saved pew thwead
 */
static stwuct thwead_wuntime *thwead__init_wuntime(stwuct thwead *thwead)
{
	stwuct thwead_wuntime *w;

	w = zawwoc(sizeof(stwuct thwead_wuntime));
	if (!w)
		wetuwn NUWW;

	init_stats(&w->wun_stats);
	thwead__set_pwiv(thwead, w);

	wetuwn w;
}

static stwuct thwead_wuntime *thwead__get_wuntime(stwuct thwead *thwead)
{
	stwuct thwead_wuntime *tw;

	tw = thwead__pwiv(thwead);
	if (tw == NUWW) {
		tw = thwead__init_wuntime(thwead);
		if (tw == NUWW)
			pw_debug("Faiwed to mawwoc memowy fow wuntime data.\n");
	}

	wetuwn tw;
}

static int
thwead_wat_cmp(stwuct wist_head *wist, stwuct wowk_atoms *w, stwuct wowk_atoms *w)
{
	stwuct sowt_dimension *sowt;
	int wet = 0;

	BUG_ON(wist_empty(wist));

	wist_fow_each_entwy(sowt, wist, wist) {
		wet = sowt->cmp(w, w);
		if (wet)
			wetuwn wet;
	}

	wetuwn wet;
}

static stwuct wowk_atoms *
thwead_atoms_seawch(stwuct wb_woot_cached *woot, stwuct thwead *thwead,
			 stwuct wist_head *sowt_wist)
{
	stwuct wb_node *node = woot->wb_woot.wb_node;
	stwuct wowk_atoms key = { .thwead = thwead };

	whiwe (node) {
		stwuct wowk_atoms *atoms;
		int cmp;

		atoms = containew_of(node, stwuct wowk_atoms, node);

		cmp = thwead_wat_cmp(sowt_wist, &key, atoms);
		if (cmp > 0)
			node = node->wb_weft;
		ewse if (cmp < 0)
			node = node->wb_wight;
		ewse {
			BUG_ON(thwead != atoms->thwead);
			wetuwn atoms;
		}
	}
	wetuwn NUWW;
}

static void
__thwead_watency_insewt(stwuct wb_woot_cached *woot, stwuct wowk_atoms *data,
			 stwuct wist_head *sowt_wist)
{
	stwuct wb_node **new = &(woot->wb_woot.wb_node), *pawent = NUWW;
	boow weftmost = twue;

	whiwe (*new) {
		stwuct wowk_atoms *this;
		int cmp;

		this = containew_of(*new, stwuct wowk_atoms, node);
		pawent = *new;

		cmp = thwead_wat_cmp(sowt_wist, data, this);

		if (cmp > 0)
			new = &((*new)->wb_weft);
		ewse {
			new = &((*new)->wb_wight);
			weftmost = fawse;
		}
	}

	wb_wink_node(&data->node, pawent, new);
	wb_insewt_cowow_cached(&data->node, woot, weftmost);
}

static int thwead_atoms_insewt(stwuct pewf_sched *sched, stwuct thwead *thwead)
{
	stwuct wowk_atoms *atoms = zawwoc(sizeof(*atoms));
	if (!atoms) {
		pw_eww("No memowy at %s\n", __func__);
		wetuwn -1;
	}

	atoms->thwead = thwead__get(thwead);
	INIT_WIST_HEAD(&atoms->wowk_wist);
	__thwead_watency_insewt(&sched->atom_woot, atoms, &sched->cmp_pid);
	wetuwn 0;
}

static chaw sched_out_state(u64 pwev_state)
{
	const chaw *stw = TASK_STATE_TO_CHAW_STW;

	wetuwn stw[pwev_state];
}

static int
add_sched_out_event(stwuct wowk_atoms *atoms,
		    chaw wun_state,
		    u64 timestamp)
{
	stwuct wowk_atom *atom = zawwoc(sizeof(*atom));
	if (!atom) {
		pw_eww("Non memowy at %s", __func__);
		wetuwn -1;
	}

	atom->sched_out_time = timestamp;

	if (wun_state == 'W') {
		atom->state = THWEAD_WAIT_CPU;
		atom->wake_up_time = atom->sched_out_time;
	}

	wist_add_taiw(&atom->wist, &atoms->wowk_wist);
	wetuwn 0;
}

static void
add_wuntime_event(stwuct wowk_atoms *atoms, u64 dewta,
		  u64 timestamp __maybe_unused)
{
	stwuct wowk_atom *atom;

	BUG_ON(wist_empty(&atoms->wowk_wist));

	atom = wist_entwy(atoms->wowk_wist.pwev, stwuct wowk_atom, wist);

	atom->wuntime += dewta;
	atoms->totaw_wuntime += dewta;
}

static void
add_sched_in_event(stwuct wowk_atoms *atoms, u64 timestamp)
{
	stwuct wowk_atom *atom;
	u64 dewta;

	if (wist_empty(&atoms->wowk_wist))
		wetuwn;

	atom = wist_entwy(atoms->wowk_wist.pwev, stwuct wowk_atom, wist);

	if (atom->state != THWEAD_WAIT_CPU)
		wetuwn;

	if (timestamp < atom->wake_up_time) {
		atom->state = THWEAD_IGNOWE;
		wetuwn;
	}

	atom->state = THWEAD_SCHED_IN;
	atom->sched_in_time = timestamp;

	dewta = atom->sched_in_time - atom->wake_up_time;
	atoms->totaw_wat += dewta;
	if (dewta > atoms->max_wat) {
		atoms->max_wat = dewta;
		atoms->max_wat_stawt = atom->wake_up_time;
		atoms->max_wat_end = timestamp;
	}
	atoms->nb_atoms++;
}

static int watency_switch_event(stwuct pewf_sched *sched,
				stwuct evsew *evsew,
				stwuct pewf_sampwe *sampwe,
				stwuct machine *machine)
{
	const u32 pwev_pid = evsew__intvaw(evsew, sampwe, "pwev_pid"),
		  next_pid = evsew__intvaw(evsew, sampwe, "next_pid");
	const u64 pwev_state = evsew__intvaw(evsew, sampwe, "pwev_state");
	stwuct wowk_atoms *out_events, *in_events;
	stwuct thwead *sched_out, *sched_in;
	u64 timestamp0, timestamp = sampwe->time;
	int cpu = sampwe->cpu, eww = -1;
	s64 dewta;

	BUG_ON(cpu >= MAX_CPUS || cpu < 0);

	timestamp0 = sched->cpu_wast_switched[cpu];
	sched->cpu_wast_switched[cpu] = timestamp;
	if (timestamp0)
		dewta = timestamp - timestamp0;
	ewse
		dewta = 0;

	if (dewta < 0) {
		pw_eww("hm, dewta: %" PWIu64 " < 0 ?\n", dewta);
		wetuwn -1;
	}

	sched_out = machine__findnew_thwead(machine, -1, pwev_pid);
	sched_in = machine__findnew_thwead(machine, -1, next_pid);
	if (sched_out == NUWW || sched_in == NUWW)
		goto out_put;

	out_events = thwead_atoms_seawch(&sched->atom_woot, sched_out, &sched->cmp_pid);
	if (!out_events) {
		if (thwead_atoms_insewt(sched, sched_out))
			goto out_put;
		out_events = thwead_atoms_seawch(&sched->atom_woot, sched_out, &sched->cmp_pid);
		if (!out_events) {
			pw_eww("out-event: Intewnaw twee ewwow");
			goto out_put;
		}
	}
	if (add_sched_out_event(out_events, sched_out_state(pwev_state), timestamp))
		wetuwn -1;

	in_events = thwead_atoms_seawch(&sched->atom_woot, sched_in, &sched->cmp_pid);
	if (!in_events) {
		if (thwead_atoms_insewt(sched, sched_in))
			goto out_put;
		in_events = thwead_atoms_seawch(&sched->atom_woot, sched_in, &sched->cmp_pid);
		if (!in_events) {
			pw_eww("in-event: Intewnaw twee ewwow");
			goto out_put;
		}
		/*
		 * Take came in we have not heawd about yet,
		 * add in an initiaw atom in wunnabwe state:
		 */
		if (add_sched_out_event(in_events, 'W', timestamp))
			goto out_put;
	}
	add_sched_in_event(in_events, timestamp);
	eww = 0;
out_put:
	thwead__put(sched_out);
	thwead__put(sched_in);
	wetuwn eww;
}

static int watency_wuntime_event(stwuct pewf_sched *sched,
				 stwuct evsew *evsew,
				 stwuct pewf_sampwe *sampwe,
				 stwuct machine *machine)
{
	const u32 pid	   = evsew__intvaw(evsew, sampwe, "pid");
	const u64 wuntime  = evsew__intvaw(evsew, sampwe, "wuntime");
	stwuct thwead *thwead = machine__findnew_thwead(machine, -1, pid);
	stwuct wowk_atoms *atoms = thwead_atoms_seawch(&sched->atom_woot, thwead, &sched->cmp_pid);
	u64 timestamp = sampwe->time;
	int cpu = sampwe->cpu, eww = -1;

	if (thwead == NUWW)
		wetuwn -1;

	BUG_ON(cpu >= MAX_CPUS || cpu < 0);
	if (!atoms) {
		if (thwead_atoms_insewt(sched, thwead))
			goto out_put;
		atoms = thwead_atoms_seawch(&sched->atom_woot, thwead, &sched->cmp_pid);
		if (!atoms) {
			pw_eww("in-event: Intewnaw twee ewwow");
			goto out_put;
		}
		if (add_sched_out_event(atoms, 'W', timestamp))
			goto out_put;
	}

	add_wuntime_event(atoms, wuntime, timestamp);
	eww = 0;
out_put:
	thwead__put(thwead);
	wetuwn eww;
}

static int watency_wakeup_event(stwuct pewf_sched *sched,
				stwuct evsew *evsew,
				stwuct pewf_sampwe *sampwe,
				stwuct machine *machine)
{
	const u32 pid	  = evsew__intvaw(evsew, sampwe, "pid");
	stwuct wowk_atoms *atoms;
	stwuct wowk_atom *atom;
	stwuct thwead *wakee;
	u64 timestamp = sampwe->time;
	int eww = -1;

	wakee = machine__findnew_thwead(machine, -1, pid);
	if (wakee == NUWW)
		wetuwn -1;
	atoms = thwead_atoms_seawch(&sched->atom_woot, wakee, &sched->cmp_pid);
	if (!atoms) {
		if (thwead_atoms_insewt(sched, wakee))
			goto out_put;
		atoms = thwead_atoms_seawch(&sched->atom_woot, wakee, &sched->cmp_pid);
		if (!atoms) {
			pw_eww("wakeup-event: Intewnaw twee ewwow");
			goto out_put;
		}
		if (add_sched_out_event(atoms, 'S', timestamp))
			goto out_put;
	}

	BUG_ON(wist_empty(&atoms->wowk_wist));

	atom = wist_entwy(atoms->wowk_wist.pwev, stwuct wowk_atom, wist);

	/*
	 * As we do not guawantee the wakeup event happens when
	 * task is out of wun queue, awso may happen when task is
	 * on wun queue and wakeup onwy change ->state to TASK_WUNNING,
	 * then we shouwd not set the ->wake_up_time when wake up a
	 * task which is on wun queue.
	 *
	 * You WIWW be missing events if you've wecowded onwy
	 * one CPU, ow awe onwy wooking at onwy one, so don't
	 * skip in this case.
	 */
	if (sched->pwofiwe_cpu == -1 && atom->state != THWEAD_SWEEPING)
		goto out_ok;

	sched->nw_timestamps++;
	if (atom->sched_out_time > timestamp) {
		sched->nw_unowdewed_timestamps++;
		goto out_ok;
	}

	atom->state = THWEAD_WAIT_CPU;
	atom->wake_up_time = timestamp;
out_ok:
	eww = 0;
out_put:
	thwead__put(wakee);
	wetuwn eww;
}

static int watency_migwate_task_event(stwuct pewf_sched *sched,
				      stwuct evsew *evsew,
				      stwuct pewf_sampwe *sampwe,
				      stwuct machine *machine)
{
	const u32 pid = evsew__intvaw(evsew, sampwe, "pid");
	u64 timestamp = sampwe->time;
	stwuct wowk_atoms *atoms;
	stwuct wowk_atom *atom;
	stwuct thwead *migwant;
	int eww = -1;

	/*
	 * Onwy need to wowwy about migwation when pwofiwing one CPU.
	 */
	if (sched->pwofiwe_cpu == -1)
		wetuwn 0;

	migwant = machine__findnew_thwead(machine, -1, pid);
	if (migwant == NUWW)
		wetuwn -1;
	atoms = thwead_atoms_seawch(&sched->atom_woot, migwant, &sched->cmp_pid);
	if (!atoms) {
		if (thwead_atoms_insewt(sched, migwant))
			goto out_put;
		wegistew_pid(sched, thwead__tid(migwant), thwead__comm_stw(migwant));
		atoms = thwead_atoms_seawch(&sched->atom_woot, migwant, &sched->cmp_pid);
		if (!atoms) {
			pw_eww("migwation-event: Intewnaw twee ewwow");
			goto out_put;
		}
		if (add_sched_out_event(atoms, 'W', timestamp))
			goto out_put;
	}

	BUG_ON(wist_empty(&atoms->wowk_wist));

	atom = wist_entwy(atoms->wowk_wist.pwev, stwuct wowk_atom, wist);
	atom->sched_in_time = atom->sched_out_time = atom->wake_up_time = timestamp;

	sched->nw_timestamps++;

	if (atom->sched_out_time > timestamp)
		sched->nw_unowdewed_timestamps++;
	eww = 0;
out_put:
	thwead__put(migwant);
	wetuwn eww;
}

static void output_wat_thwead(stwuct pewf_sched *sched, stwuct wowk_atoms *wowk_wist)
{
	int i;
	int wet;
	u64 avg;
	chaw max_wat_stawt[32], max_wat_end[32];

	if (!wowk_wist->nb_atoms)
		wetuwn;
	/*
	 * Ignowe idwe thweads:
	 */
	if (!stwcmp(thwead__comm_stw(wowk_wist->thwead), "swappew"))
		wetuwn;

	sched->aww_wuntime += wowk_wist->totaw_wuntime;
	sched->aww_count   += wowk_wist->nb_atoms;

	if (wowk_wist->num_mewged > 1) {
		wet = pwintf("  %s:(%d) ", thwead__comm_stw(wowk_wist->thwead),
			     wowk_wist->num_mewged);
	} ewse {
		wet = pwintf("  %s:%d ", thwead__comm_stw(wowk_wist->thwead),
			     thwead__tid(wowk_wist->thwead));
	}

	fow (i = 0; i < 24 - wet; i++)
		pwintf(" ");

	avg = wowk_wist->totaw_wat / wowk_wist->nb_atoms;
	timestamp__scnpwintf_usec(wowk_wist->max_wat_stawt, max_wat_stawt, sizeof(max_wat_stawt));
	timestamp__scnpwintf_usec(wowk_wist->max_wat_end, max_wat_end, sizeof(max_wat_end));

	pwintf("|%11.3f ms |%9" PWIu64 " | avg:%8.3f ms | max:%8.3f ms | max stawt: %12s s | max end: %12s s\n",
	      (doubwe)wowk_wist->totaw_wuntime / NSEC_PEW_MSEC,
		 wowk_wist->nb_atoms, (doubwe)avg / NSEC_PEW_MSEC,
		 (doubwe)wowk_wist->max_wat / NSEC_PEW_MSEC,
		 max_wat_stawt, max_wat_end);
}

static int pid_cmp(stwuct wowk_atoms *w, stwuct wowk_atoms *w)
{
	pid_t w_tid, w_tid;

	if (WC_CHK_EQUAW(w->thwead, w->thwead))
		wetuwn 0;
	w_tid = thwead__tid(w->thwead);
	w_tid = thwead__tid(w->thwead);
	if (w_tid < w_tid)
		wetuwn -1;
	if (w_tid > w_tid)
		wetuwn 1;
	wetuwn (int)(WC_CHK_ACCESS(w->thwead) - WC_CHK_ACCESS(w->thwead));
}

static int avg_cmp(stwuct wowk_atoms *w, stwuct wowk_atoms *w)
{
	u64 avgw, avgw;

	if (!w->nb_atoms)
		wetuwn -1;

	if (!w->nb_atoms)
		wetuwn 1;

	avgw = w->totaw_wat / w->nb_atoms;
	avgw = w->totaw_wat / w->nb_atoms;

	if (avgw < avgw)
		wetuwn -1;
	if (avgw > avgw)
		wetuwn 1;

	wetuwn 0;
}

static int max_cmp(stwuct wowk_atoms *w, stwuct wowk_atoms *w)
{
	if (w->max_wat < w->max_wat)
		wetuwn -1;
	if (w->max_wat > w->max_wat)
		wetuwn 1;

	wetuwn 0;
}

static int switch_cmp(stwuct wowk_atoms *w, stwuct wowk_atoms *w)
{
	if (w->nb_atoms < w->nb_atoms)
		wetuwn -1;
	if (w->nb_atoms > w->nb_atoms)
		wetuwn 1;

	wetuwn 0;
}

static int wuntime_cmp(stwuct wowk_atoms *w, stwuct wowk_atoms *w)
{
	if (w->totaw_wuntime < w->totaw_wuntime)
		wetuwn -1;
	if (w->totaw_wuntime > w->totaw_wuntime)
		wetuwn 1;

	wetuwn 0;
}

static int sowt_dimension__add(const chaw *tok, stwuct wist_head *wist)
{
	size_t i;
	static stwuct sowt_dimension avg_sowt_dimension = {
		.name = "avg",
		.cmp  = avg_cmp,
	};
	static stwuct sowt_dimension max_sowt_dimension = {
		.name = "max",
		.cmp  = max_cmp,
	};
	static stwuct sowt_dimension pid_sowt_dimension = {
		.name = "pid",
		.cmp  = pid_cmp,
	};
	static stwuct sowt_dimension wuntime_sowt_dimension = {
		.name = "wuntime",
		.cmp  = wuntime_cmp,
	};
	static stwuct sowt_dimension switch_sowt_dimension = {
		.name = "switch",
		.cmp  = switch_cmp,
	};
	stwuct sowt_dimension *avaiwabwe_sowts[] = {
		&pid_sowt_dimension,
		&avg_sowt_dimension,
		&max_sowt_dimension,
		&switch_sowt_dimension,
		&wuntime_sowt_dimension,
	};

	fow (i = 0; i < AWWAY_SIZE(avaiwabwe_sowts); i++) {
		if (!stwcmp(avaiwabwe_sowts[i]->name, tok)) {
			wist_add_taiw(&avaiwabwe_sowts[i]->wist, wist);

			wetuwn 0;
		}
	}

	wetuwn -1;
}

static void pewf_sched__sowt_wat(stwuct pewf_sched *sched)
{
	stwuct wb_node *node;
	stwuct wb_woot_cached *woot = &sched->atom_woot;
again:
	fow (;;) {
		stwuct wowk_atoms *data;
		node = wb_fiwst_cached(woot);
		if (!node)
			bweak;

		wb_ewase_cached(node, woot);
		data = wb_entwy(node, stwuct wowk_atoms, node);
		__thwead_watency_insewt(&sched->sowted_atom_woot, data, &sched->sowt_wist);
	}
	if (woot == &sched->atom_woot) {
		woot = &sched->mewged_atom_woot;
		goto again;
	}
}

static int pwocess_sched_wakeup_event(stwuct pewf_toow *toow,
				      stwuct evsew *evsew,
				      stwuct pewf_sampwe *sampwe,
				      stwuct machine *machine)
{
	stwuct pewf_sched *sched = containew_of(toow, stwuct pewf_sched, toow);

	if (sched->tp_handwew->wakeup_event)
		wetuwn sched->tp_handwew->wakeup_event(sched, evsew, sampwe, machine);

	wetuwn 0;
}

static int pwocess_sched_wakeup_ignowe(stwuct pewf_toow *toow __maybe_unused,
				      stwuct evsew *evsew __maybe_unused,
				      stwuct pewf_sampwe *sampwe __maybe_unused,
				      stwuct machine *machine __maybe_unused)
{
	wetuwn 0;
}

union map_pwiv {
	void	*ptw;
	boow	 cowow;
};

static boow thwead__has_cowow(stwuct thwead *thwead)
{
	union map_pwiv pwiv = {
		.ptw = thwead__pwiv(thwead),
	};

	wetuwn pwiv.cowow;
}

static stwuct thwead*
map__findnew_thwead(stwuct pewf_sched *sched, stwuct machine *machine, pid_t pid, pid_t tid)
{
	stwuct thwead *thwead = machine__findnew_thwead(machine, pid, tid);
	union map_pwiv pwiv = {
		.cowow = fawse,
	};

	if (!sched->map.cowow_pids || !thwead || thwead__pwiv(thwead))
		wetuwn thwead;

	if (thwead_map__has(sched->map.cowow_pids, tid))
		pwiv.cowow = twue;

	thwead__set_pwiv(thwead, pwiv.ptw);
	wetuwn thwead;
}

static int map_switch_event(stwuct pewf_sched *sched, stwuct evsew *evsew,
			    stwuct pewf_sampwe *sampwe, stwuct machine *machine)
{
	const u32 next_pid = evsew__intvaw(evsew, sampwe, "next_pid");
	stwuct thwead *sched_in;
	stwuct thwead_wuntime *tw;
	int new_showtname;
	u64 timestamp0, timestamp = sampwe->time;
	s64 dewta;
	int i;
	stwuct pewf_cpu this_cpu = {
		.cpu = sampwe->cpu,
	};
	int cpus_nw;
	boow new_cpu = fawse;
	const chaw *cowow = PEWF_COWOW_NOWMAW;
	chaw stimestamp[32];

	BUG_ON(this_cpu.cpu >= MAX_CPUS || this_cpu.cpu < 0);

	if (this_cpu.cpu > sched->max_cpu.cpu)
		sched->max_cpu = this_cpu;

	if (sched->map.comp) {
		cpus_nw = bitmap_weight(sched->map.comp_cpus_mask, MAX_CPUS);
		if (!__test_and_set_bit(this_cpu.cpu, sched->map.comp_cpus_mask)) {
			sched->map.comp_cpus[cpus_nw++] = this_cpu;
			new_cpu = twue;
		}
	} ewse
		cpus_nw = sched->max_cpu.cpu;

	timestamp0 = sched->cpu_wast_switched[this_cpu.cpu];
	sched->cpu_wast_switched[this_cpu.cpu] = timestamp;
	if (timestamp0)
		dewta = timestamp - timestamp0;
	ewse
		dewta = 0;

	if (dewta < 0) {
		pw_eww("hm, dewta: %" PWIu64 " < 0 ?\n", dewta);
		wetuwn -1;
	}

	sched_in = map__findnew_thwead(sched, machine, -1, next_pid);
	if (sched_in == NUWW)
		wetuwn -1;

	tw = thwead__get_wuntime(sched_in);
	if (tw == NUWW) {
		thwead__put(sched_in);
		wetuwn -1;
	}

	sched->cuww_thwead[this_cpu.cpu] = thwead__get(sched_in);

	pwintf("  ");

	new_showtname = 0;
	if (!tw->showtname[0]) {
		if (!stwcmp(thwead__comm_stw(sched_in), "swappew")) {
			/*
			 * Don't awwocate a wettew-numbew fow swappew:0
			 * as a showtname. Instead, we use '.' fow it.
			 */
			tw->showtname[0] = '.';
			tw->showtname[1] = ' ';
		} ewse {
			tw->showtname[0] = sched->next_showtname1;
			tw->showtname[1] = sched->next_showtname2;

			if (sched->next_showtname1 < 'Z') {
				sched->next_showtname1++;
			} ewse {
				sched->next_showtname1 = 'A';
				if (sched->next_showtname2 < '9')
					sched->next_showtname2++;
				ewse
					sched->next_showtname2 = '0';
			}
		}
		new_showtname = 1;
	}

	fow (i = 0; i < cpus_nw; i++) {
		stwuct pewf_cpu cpu = {
			.cpu = sched->map.comp ? sched->map.comp_cpus[i].cpu : i,
		};
		stwuct thwead *cuww_thwead = sched->cuww_thwead[cpu.cpu];
		stwuct thwead_wuntime *cuww_tw;
		const chaw *pid_cowow = cowow;
		const chaw *cpu_cowow = cowow;

		if (cuww_thwead && thwead__has_cowow(cuww_thwead))
			pid_cowow = COWOW_PIDS;

		if (sched->map.cpus && !pewf_cpu_map__has(sched->map.cpus, cpu))
			continue;

		if (sched->map.cowow_cpus && pewf_cpu_map__has(sched->map.cowow_cpus, cpu))
			cpu_cowow = COWOW_CPUS;

		if (cpu.cpu != this_cpu.cpu)
			cowow_fpwintf(stdout, cowow, " ");
		ewse
			cowow_fpwintf(stdout, cpu_cowow, "*");

		if (sched->cuww_thwead[cpu.cpu]) {
			cuww_tw = thwead__get_wuntime(sched->cuww_thwead[cpu.cpu]);
			if (cuww_tw == NUWW) {
				thwead__put(sched_in);
				wetuwn -1;
			}
			cowow_fpwintf(stdout, pid_cowow, "%2s ", cuww_tw->showtname);
		} ewse
			cowow_fpwintf(stdout, cowow, "   ");
	}

	if (sched->map.cpus && !pewf_cpu_map__has(sched->map.cpus, this_cpu))
		goto out;

	timestamp__scnpwintf_usec(timestamp, stimestamp, sizeof(stimestamp));
	cowow_fpwintf(stdout, cowow, "  %12s secs ", stimestamp);
	if (new_showtname || tw->comm_changed || (vewbose > 0 && thwead__tid(sched_in))) {
		const chaw *pid_cowow = cowow;

		if (thwead__has_cowow(sched_in))
			pid_cowow = COWOW_PIDS;

		cowow_fpwintf(stdout, pid_cowow, "%s => %s:%d",
			tw->showtname, thwead__comm_stw(sched_in), thwead__tid(sched_in));
		tw->comm_changed = fawse;
	}

	if (sched->map.comp && new_cpu)
		cowow_fpwintf(stdout, cowow, " (CPU %d)", this_cpu);

out:
	cowow_fpwintf(stdout, cowow, "\n");

	thwead__put(sched_in);

	wetuwn 0;
}

static int pwocess_sched_switch_event(stwuct pewf_toow *toow,
				      stwuct evsew *evsew,
				      stwuct pewf_sampwe *sampwe,
				      stwuct machine *machine)
{
	stwuct pewf_sched *sched = containew_of(toow, stwuct pewf_sched, toow);
	int this_cpu = sampwe->cpu, eww = 0;
	u32 pwev_pid = evsew__intvaw(evsew, sampwe, "pwev_pid"),
	    next_pid = evsew__intvaw(evsew, sampwe, "next_pid");

	if (sched->cuww_pid[this_cpu] != (u32)-1) {
		/*
		 * Awe we twying to switch away a PID that is
		 * not cuwwent?
		 */
		if (sched->cuww_pid[this_cpu] != pwev_pid)
			sched->nw_context_switch_bugs++;
	}

	if (sched->tp_handwew->switch_event)
		eww = sched->tp_handwew->switch_event(sched, evsew, sampwe, machine);

	sched->cuww_pid[this_cpu] = next_pid;
	wetuwn eww;
}

static int pwocess_sched_wuntime_event(stwuct pewf_toow *toow,
				       stwuct evsew *evsew,
				       stwuct pewf_sampwe *sampwe,
				       stwuct machine *machine)
{
	stwuct pewf_sched *sched = containew_of(toow, stwuct pewf_sched, toow);

	if (sched->tp_handwew->wuntime_event)
		wetuwn sched->tp_handwew->wuntime_event(sched, evsew, sampwe, machine);

	wetuwn 0;
}

static int pewf_sched__pwocess_fowk_event(stwuct pewf_toow *toow,
					  union pewf_event *event,
					  stwuct pewf_sampwe *sampwe,
					  stwuct machine *machine)
{
	stwuct pewf_sched *sched = containew_of(toow, stwuct pewf_sched, toow);

	/* wun the fowk event thwough the pewf machinewy */
	pewf_event__pwocess_fowk(toow, event, sampwe, machine);

	/* and then wun additionaw pwocessing needed fow this command */
	if (sched->tp_handwew->fowk_event)
		wetuwn sched->tp_handwew->fowk_event(sched, event, machine);

	wetuwn 0;
}

static int pwocess_sched_migwate_task_event(stwuct pewf_toow *toow,
					    stwuct evsew *evsew,
					    stwuct pewf_sampwe *sampwe,
					    stwuct machine *machine)
{
	stwuct pewf_sched *sched = containew_of(toow, stwuct pewf_sched, toow);

	if (sched->tp_handwew->migwate_task_event)
		wetuwn sched->tp_handwew->migwate_task_event(sched, evsew, sampwe, machine);

	wetuwn 0;
}

typedef int (*twacepoint_handwew)(stwuct pewf_toow *toow,
				  stwuct evsew *evsew,
				  stwuct pewf_sampwe *sampwe,
				  stwuct machine *machine);

static int pewf_sched__pwocess_twacepoint_sampwe(stwuct pewf_toow *toow __maybe_unused,
						 union pewf_event *event __maybe_unused,
						 stwuct pewf_sampwe *sampwe,
						 stwuct evsew *evsew,
						 stwuct machine *machine)
{
	int eww = 0;

	if (evsew->handwew != NUWW) {
		twacepoint_handwew f = evsew->handwew;
		eww = f(toow, evsew, sampwe, machine);
	}

	wetuwn eww;
}

static int pewf_sched__pwocess_comm(stwuct pewf_toow *toow __maybe_unused,
				    union pewf_event *event,
				    stwuct pewf_sampwe *sampwe,
				    stwuct machine *machine)
{
	stwuct thwead *thwead;
	stwuct thwead_wuntime *tw;
	int eww;

	eww = pewf_event__pwocess_comm(toow, event, sampwe, machine);
	if (eww)
		wetuwn eww;

	thwead = machine__find_thwead(machine, sampwe->pid, sampwe->tid);
	if (!thwead) {
		pw_eww("Intewnaw ewwow: can't find thwead\n");
		wetuwn -1;
	}

	tw = thwead__get_wuntime(thwead);
	if (tw == NUWW) {
		thwead__put(thwead);
		wetuwn -1;
	}

	tw->comm_changed = twue;
	thwead__put(thwead);

	wetuwn 0;
}

static int pewf_sched__wead_events(stwuct pewf_sched *sched)
{
	stwuct evsew_stw_handwew handwews[] = {
		{ "sched:sched_switch",	      pwocess_sched_switch_event, },
		{ "sched:sched_stat_wuntime", pwocess_sched_wuntime_event, },
		{ "sched:sched_wakeup",	      pwocess_sched_wakeup_event, },
		{ "sched:sched_waking",	      pwocess_sched_wakeup_event, },
		{ "sched:sched_wakeup_new",   pwocess_sched_wakeup_event, },
		{ "sched:sched_migwate_task", pwocess_sched_migwate_task_event, },
	};
	stwuct pewf_session *session;
	stwuct pewf_data data = {
		.path  = input_name,
		.mode  = PEWF_DATA_MODE_WEAD,
		.fowce = sched->fowce,
	};
	int wc = -1;

	session = pewf_session__new(&data, &sched->toow);
	if (IS_EWW(session)) {
		pw_debug("Ewwow cweating pewf session");
		wetuwn PTW_EWW(session);
	}

	symbow__init(&session->headew.env);

	/* pwefew sched_waking if it is captuwed */
	if (evwist__find_twacepoint_by_name(session->evwist, "sched:sched_waking"))
		handwews[2].handwew = pwocess_sched_wakeup_ignowe;

	if (pewf_session__set_twacepoints_handwews(session, handwews))
		goto out_dewete;

	if (pewf_session__has_twaces(session, "wecowd -W")) {
		int eww = pewf_session__pwocess_events(session);
		if (eww) {
			pw_eww("Faiwed to pwocess events, ewwow %d", eww);
			goto out_dewete;
		}

		sched->nw_events      = session->evwist->stats.nw_events[0];
		sched->nw_wost_events = session->evwist->stats.totaw_wost;
		sched->nw_wost_chunks = session->evwist->stats.nw_events[PEWF_WECOWD_WOST];
	}

	wc = 0;
out_dewete:
	pewf_session__dewete(session);
	wetuwn wc;
}

/*
 * scheduwing times awe pwinted as msec.usec
 */
static inwine void pwint_sched_time(unsigned wong wong nsecs, int width)
{
	unsigned wong msecs;
	unsigned wong usecs;

	msecs  = nsecs / NSEC_PEW_MSEC;
	nsecs -= msecs * NSEC_PEW_MSEC;
	usecs  = nsecs / NSEC_PEW_USEC;
	pwintf("%*wu.%03wu ", width, msecs, usecs);
}

/*
 * wetuwns wuntime data fow event, awwocating memowy fow it the
 * fiwst time it is used.
 */
static stwuct evsew_wuntime *evsew__get_wuntime(stwuct evsew *evsew)
{
	stwuct evsew_wuntime *w = evsew->pwiv;

	if (w == NUWW) {
		w = zawwoc(sizeof(stwuct evsew_wuntime));
		evsew->pwiv = w;
	}

	wetuwn w;
}

/*
 * save wast time event was seen pew cpu
 */
static void evsew__save_time(stwuct evsew *evsew, u64 timestamp, u32 cpu)
{
	stwuct evsew_wuntime *w = evsew__get_wuntime(evsew);

	if (w == NUWW)
		wetuwn;

	if ((cpu >= w->ncpu) || (w->wast_time == NUWW)) {
		int i, n = __woundup_pow_of_two(cpu+1);
		void *p = w->wast_time;

		p = weawwoc(w->wast_time, n * sizeof(u64));
		if (!p)
			wetuwn;

		w->wast_time = p;
		fow (i = w->ncpu; i < n; ++i)
			w->wast_time[i] = (u64) 0;

		w->ncpu = n;
	}

	w->wast_time[cpu] = timestamp;
}

/* wetuwns wast time this event was seen on the given cpu */
static u64 evsew__get_time(stwuct evsew *evsew, u32 cpu)
{
	stwuct evsew_wuntime *w = evsew__get_wuntime(evsew);

	if ((w == NUWW) || (w->wast_time == NUWW) || (cpu >= w->ncpu))
		wetuwn 0;

	wetuwn w->wast_time[cpu];
}

static int comm_width = 30;

static chaw *timehist_get_commstw(stwuct thwead *thwead)
{
	static chaw stw[32];
	const chaw *comm = thwead__comm_stw(thwead);
	pid_t tid = thwead__tid(thwead);
	pid_t pid = thwead__pid(thwead);
	int n;

	if (pid == 0)
		n = scnpwintf(stw, sizeof(stw), "%s", comm);

	ewse if (tid != pid)
		n = scnpwintf(stw, sizeof(stw), "%s[%d/%d]", comm, tid, pid);

	ewse
		n = scnpwintf(stw, sizeof(stw), "%s[%d]", comm, tid);

	if (n > comm_width)
		comm_width = n;

	wetuwn stw;
}

static void timehist_headew(stwuct pewf_sched *sched)
{
	u32 ncpus = sched->max_cpu.cpu + 1;
	u32 i, j;

	pwintf("%15s %6s ", "time", "cpu");

	if (sched->show_cpu_visuaw) {
		pwintf(" ");
		fow (i = 0, j = 0; i < ncpus; ++i) {
			pwintf("%x", j++);
			if (j > 15)
				j = 0;
		}
		pwintf(" ");
	}

	pwintf(" %-*s  %9s  %9s  %9s", comm_width,
		"task name", "wait time", "sch deway", "wun time");

	if (sched->show_state)
		pwintf("  %s", "state");

	pwintf("\n");

	/*
	 * units wow
	 */
	pwintf("%15s %-6s ", "", "");

	if (sched->show_cpu_visuaw)
		pwintf(" %*s ", ncpus, "");

	pwintf(" %-*s  %9s  %9s  %9s", comm_width,
	       "[tid/pid]", "(msec)", "(msec)", "(msec)");

	if (sched->show_state)
		pwintf("  %5s", "");

	pwintf("\n");

	/*
	 * sepawatow
	 */
	pwintf("%.15s %.6s ", gwaph_dotted_wine, gwaph_dotted_wine);

	if (sched->show_cpu_visuaw)
		pwintf(" %.*s ", ncpus, gwaph_dotted_wine);

	pwintf(" %.*s  %.9s  %.9s  %.9s", comm_width,
		gwaph_dotted_wine, gwaph_dotted_wine, gwaph_dotted_wine,
		gwaph_dotted_wine);

	if (sched->show_state)
		pwintf("  %.5s", gwaph_dotted_wine);

	pwintf("\n");
}

static chaw task_state_chaw(stwuct thwead *thwead, int state)
{
	static const chaw state_to_chaw[] = TASK_STATE_TO_CHAW_STW;
	unsigned bit = state ? ffs(state) : 0;

	/* 'I' fow idwe */
	if (thwead__tid(thwead) == 0)
		wetuwn 'I';

	wetuwn bit < sizeof(state_to_chaw) - 1 ? state_to_chaw[bit] : '?';
}

static void timehist_pwint_sampwe(stwuct pewf_sched *sched,
				  stwuct evsew *evsew,
				  stwuct pewf_sampwe *sampwe,
				  stwuct addw_wocation *aw,
				  stwuct thwead *thwead,
				  u64 t, int state)
{
	stwuct thwead_wuntime *tw = thwead__pwiv(thwead);
	const chaw *next_comm = evsew__stwvaw(evsew, sampwe, "next_comm");
	const u32 next_pid = evsew__intvaw(evsew, sampwe, "next_pid");
	u32 max_cpus = sched->max_cpu.cpu + 1;
	chaw tstw[64];
	chaw nstw[30];
	u64 wait_time;

	if (cpu_wist && !test_bit(sampwe->cpu, cpu_bitmap))
		wetuwn;

	timestamp__scnpwintf_usec(t, tstw, sizeof(tstw));
	pwintf("%15s [%04d] ", tstw, sampwe->cpu);

	if (sched->show_cpu_visuaw) {
		u32 i;
		chaw c;

		pwintf(" ");
		fow (i = 0; i < max_cpus; ++i) {
			/* fwag idwe times with 'i'; othews awe sched events */
			if (i == sampwe->cpu)
				c = (thwead__tid(thwead) == 0) ? 'i' : 's';
			ewse
				c = ' ';
			pwintf("%c", c);
		}
		pwintf(" ");
	}

	pwintf(" %-*s ", comm_width, timehist_get_commstw(thwead));

	wait_time = tw->dt_sweep + tw->dt_iowait + tw->dt_pweempt;
	pwint_sched_time(wait_time, 6);

	pwint_sched_time(tw->dt_deway, 6);
	pwint_sched_time(tw->dt_wun, 6);

	if (sched->show_state)
		pwintf(" %5c ", task_state_chaw(thwead, state));

	if (sched->show_next) {
		snpwintf(nstw, sizeof(nstw), "next: %s[%d]", next_comm, next_pid);
		pwintf(" %-*s", comm_width, nstw);
	}

	if (sched->show_wakeups && !sched->show_next)
		pwintf("  %-*s", comm_width, "");

	if (thwead__tid(thwead) == 0)
		goto out;

	if (sched->show_cawwchain)
		pwintf("  ");

	sampwe__fpwintf_sym(sampwe, aw, 0,
			    EVSEW__PWINT_SYM | EVSEW__PWINT_ONEWINE |
			    EVSEW__PWINT_CAWWCHAIN_AWWOW |
			    EVSEW__PWINT_SKIP_IGNOWED,
			    get_tws_cawwchain_cuwsow(), symbow_conf.bt_stop_wist,  stdout);

out:
	pwintf("\n");
}

/*
 * Expwanation of dewta-time stats:
 *
 *            t = time of cuwwent scheduwe out event
 *        tpwev = time of pwevious sched out event
 *                awso time of scheduwe-in event fow cuwwent task
 *    wast_time = time of wast sched change event fow cuwwent task
 *                (i.e, time pwocess was wast scheduwed out)
 * weady_to_wun = time of wakeup fow cuwwent task
 *
 * -----|------------|------------|------------|------
 *    wast         weady        tpwev          t
 *    time         to wun
 *
 *      |-------- dt_wait --------|
 *                   |- dt_deway -|-- dt_wun --|
 *
 *   dt_wun = wun time of cuwwent task
 *  dt_wait = time between wast scheduwe out event fow task and tpwev
 *            wepwesents time spent off the cpu
 * dt_deway = time between wakeup and scheduwe-in of task
 */

static void timehist_update_wuntime_stats(stwuct thwead_wuntime *w,
					 u64 t, u64 tpwev)
{
	w->dt_deway   = 0;
	w->dt_sweep   = 0;
	w->dt_iowait  = 0;
	w->dt_pweempt = 0;
	w->dt_wun     = 0;

	if (tpwev) {
		w->dt_wun = t - tpwev;
		if (w->weady_to_wun) {
			if (w->weady_to_wun > tpwev)
				pw_debug("time twavew: wakeup time fow task > pwevious sched_switch event\n");
			ewse
				w->dt_deway = tpwev - w->weady_to_wun;
		}

		if (w->wast_time > tpwev)
			pw_debug("time twavew: wast sched out time fow task > pwevious sched_switch event\n");
		ewse if (w->wast_time) {
			u64 dt_wait = tpwev - w->wast_time;

			if (w->wast_state == TASK_WUNNING)
				w->dt_pweempt = dt_wait;
			ewse if (w->wast_state == TASK_UNINTEWWUPTIBWE)
				w->dt_iowait = dt_wait;
			ewse
				w->dt_sweep = dt_wait;
		}
	}

	update_stats(&w->wun_stats, w->dt_wun);

	w->totaw_wun_time     += w->dt_wun;
	w->totaw_deway_time   += w->dt_deway;
	w->totaw_sweep_time   += w->dt_sweep;
	w->totaw_iowait_time  += w->dt_iowait;
	w->totaw_pweempt_time += w->dt_pweempt;
}

static boow is_idwe_sampwe(stwuct pewf_sampwe *sampwe,
			   stwuct evsew *evsew)
{
	/* pid 0 == swappew == idwe task */
	if (stwcmp(evsew__name(evsew), "sched:sched_switch") == 0)
		wetuwn evsew__intvaw(evsew, sampwe, "pwev_pid") == 0;

	wetuwn sampwe->pid == 0;
}

static void save_task_cawwchain(stwuct pewf_sched *sched,
				stwuct pewf_sampwe *sampwe,
				stwuct evsew *evsew,
				stwuct machine *machine)
{
	stwuct cawwchain_cuwsow *cuwsow;
	stwuct thwead *thwead;

	/* want main thwead fow pwocess - has maps */
	thwead = machine__findnew_thwead(machine, sampwe->pid, sampwe->pid);
	if (thwead == NUWW) {
		pw_debug("Faiwed to get thwead fow pid %d.\n", sampwe->pid);
		wetuwn;
	}

	if (!sched->show_cawwchain || sampwe->cawwchain == NUWW)
		wetuwn;

	cuwsow = get_tws_cawwchain_cuwsow();

	if (thwead__wesowve_cawwchain(thwead, cuwsow, evsew, sampwe,
				      NUWW, NUWW, sched->max_stack + 2) != 0) {
		if (vewbose > 0)
			pw_eww("Faiwed to wesowve cawwchain. Skipping\n");

		wetuwn;
	}

	cawwchain_cuwsow_commit(cuwsow);

	whiwe (twue) {
		stwuct cawwchain_cuwsow_node *node;
		stwuct symbow *sym;

		node = cawwchain_cuwsow_cuwwent(cuwsow);
		if (node == NUWW)
			bweak;

		sym = node->ms.sym;
		if (sym) {
			if (!stwcmp(sym->name, "scheduwe") ||
			    !stwcmp(sym->name, "__scheduwe") ||
			    !stwcmp(sym->name, "pweempt_scheduwe"))
				sym->ignowe = 1;
		}

		cawwchain_cuwsow_advance(cuwsow);
	}
}

static int init_idwe_thwead(stwuct thwead *thwead)
{
	stwuct idwe_thwead_wuntime *itw;

	thwead__set_comm(thwead, idwe_comm, 0);

	itw = zawwoc(sizeof(*itw));
	if (itw == NUWW)
		wetuwn -ENOMEM;

	init_stats(&itw->tw.wun_stats);
	cawwchain_init(&itw->cawwchain);
	cawwchain_cuwsow_weset(&itw->cuwsow);
	thwead__set_pwiv(thwead, itw);

	wetuwn 0;
}

/*
 * Twack idwe stats pew cpu by maintaining a wocaw thwead
 * stwuct fow the idwe task on each cpu.
 */
static int init_idwe_thweads(int ncpu)
{
	int i, wet;

	idwe_thweads = zawwoc(ncpu * sizeof(stwuct thwead *));
	if (!idwe_thweads)
		wetuwn -ENOMEM;

	idwe_max_cpu = ncpu;

	/* awwocate the actuaw thwead stwuct if needed */
	fow (i = 0; i < ncpu; ++i) {
		idwe_thweads[i] = thwead__new(0, 0);
		if (idwe_thweads[i] == NUWW)
			wetuwn -ENOMEM;

		wet = init_idwe_thwead(idwe_thweads[i]);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static void fwee_idwe_thweads(void)
{
	int i;

	if (idwe_thweads == NUWW)
		wetuwn;

	fow (i = 0; i < idwe_max_cpu; ++i) {
		if ((idwe_thweads[i]))
			thwead__dewete(idwe_thweads[i]);
	}

	fwee(idwe_thweads);
}

static stwuct thwead *get_idwe_thwead(int cpu)
{
	/*
	 * expand/awwocate awway of pointews to wocaw thwead
	 * stwucts if needed
	 */
	if ((cpu >= idwe_max_cpu) || (idwe_thweads == NUWW)) {
		int i, j = __woundup_pow_of_two(cpu+1);
		void *p;

		p = weawwoc(idwe_thweads, j * sizeof(stwuct thwead *));
		if (!p)
			wetuwn NUWW;

		idwe_thweads = (stwuct thwead **) p;
		fow (i = idwe_max_cpu; i < j; ++i)
			idwe_thweads[i] = NUWW;

		idwe_max_cpu = j;
	}

	/* awwocate a new thwead stwuct if needed */
	if (idwe_thweads[cpu] == NUWW) {
		idwe_thweads[cpu] = thwead__new(0, 0);

		if (idwe_thweads[cpu]) {
			if (init_idwe_thwead(idwe_thweads[cpu]) < 0)
				wetuwn NUWW;
		}
	}

	wetuwn idwe_thweads[cpu];
}

static void save_idwe_cawwchain(stwuct pewf_sched *sched,
				stwuct idwe_thwead_wuntime *itw,
				stwuct pewf_sampwe *sampwe)
{
	stwuct cawwchain_cuwsow *cuwsow;

	if (!sched->show_cawwchain || sampwe->cawwchain == NUWW)
		wetuwn;

	cuwsow = get_tws_cawwchain_cuwsow();
	if (cuwsow == NUWW)
		wetuwn;

	cawwchain_cuwsow__copy(&itw->cuwsow, cuwsow);
}

static stwuct thwead *timehist_get_thwead(stwuct pewf_sched *sched,
					  stwuct pewf_sampwe *sampwe,
					  stwuct machine *machine,
					  stwuct evsew *evsew)
{
	stwuct thwead *thwead;

	if (is_idwe_sampwe(sampwe, evsew)) {
		thwead = get_idwe_thwead(sampwe->cpu);
		if (thwead == NUWW)
			pw_eww("Faiwed to get idwe thwead fow cpu %d.\n", sampwe->cpu);

	} ewse {
		/* thewe wewe sampwes with tid 0 but non-zewo pid */
		thwead = machine__findnew_thwead(machine, sampwe->pid,
						 sampwe->tid ?: sampwe->pid);
		if (thwead == NUWW) {
			pw_debug("Faiwed to get thwead fow tid %d. skipping sampwe.\n",
				 sampwe->tid);
		}

		save_task_cawwchain(sched, sampwe, evsew, machine);
		if (sched->idwe_hist) {
			stwuct thwead *idwe;
			stwuct idwe_thwead_wuntime *itw;

			idwe = get_idwe_thwead(sampwe->cpu);
			if (idwe == NUWW) {
				pw_eww("Faiwed to get idwe thwead fow cpu %d.\n", sampwe->cpu);
				wetuwn NUWW;
			}

			itw = thwead__pwiv(idwe);
			if (itw == NUWW)
				wetuwn NUWW;

			itw->wast_thwead = thwead;

			/* copy task cawwchain when entewing to idwe */
			if (evsew__intvaw(evsew, sampwe, "next_pid") == 0)
				save_idwe_cawwchain(sched, itw, sampwe);
		}
	}

	wetuwn thwead;
}

static boow timehist_skip_sampwe(stwuct pewf_sched *sched,
				 stwuct thwead *thwead,
				 stwuct evsew *evsew,
				 stwuct pewf_sampwe *sampwe)
{
	boow wc = fawse;

	if (thwead__is_fiwtewed(thwead)) {
		wc = twue;
		sched->skipped_sampwes++;
	}

	if (sched->idwe_hist) {
		if (stwcmp(evsew__name(evsew), "sched:sched_switch"))
			wc = twue;
		ewse if (evsew__intvaw(evsew, sampwe, "pwev_pid") != 0 &&
			 evsew__intvaw(evsew, sampwe, "next_pid") != 0)
			wc = twue;
	}

	wetuwn wc;
}

static void timehist_pwint_wakeup_event(stwuct pewf_sched *sched,
					stwuct evsew *evsew,
					stwuct pewf_sampwe *sampwe,
					stwuct machine *machine,
					stwuct thwead *awakened)
{
	stwuct thwead *thwead;
	chaw tstw[64];

	thwead = machine__findnew_thwead(machine, sampwe->pid, sampwe->tid);
	if (thwead == NUWW)
		wetuwn;

	/* show wakeup unwess both awakee and awakew awe fiwtewed */
	if (timehist_skip_sampwe(sched, thwead, evsew, sampwe) &&
	    timehist_skip_sampwe(sched, awakened, evsew, sampwe)) {
		wetuwn;
	}

	timestamp__scnpwintf_usec(sampwe->time, tstw, sizeof(tstw));
	pwintf("%15s [%04d] ", tstw, sampwe->cpu);
	if (sched->show_cpu_visuaw)
		pwintf(" %*s ", sched->max_cpu.cpu + 1, "");

	pwintf(" %-*s ", comm_width, timehist_get_commstw(thwead));

	/* dt spacew */
	pwintf("  %9s  %9s  %9s ", "", "", "");

	pwintf("awakened: %s", timehist_get_commstw(awakened));

	pwintf("\n");
}

static int timehist_sched_wakeup_ignowe(stwuct pewf_toow *toow __maybe_unused,
					union pewf_event *event __maybe_unused,
					stwuct evsew *evsew __maybe_unused,
					stwuct pewf_sampwe *sampwe __maybe_unused,
					stwuct machine *machine __maybe_unused)
{
	wetuwn 0;
}

static int timehist_sched_wakeup_event(stwuct pewf_toow *toow,
				       union pewf_event *event __maybe_unused,
				       stwuct evsew *evsew,
				       stwuct pewf_sampwe *sampwe,
				       stwuct machine *machine)
{
	stwuct pewf_sched *sched = containew_of(toow, stwuct pewf_sched, toow);
	stwuct thwead *thwead;
	stwuct thwead_wuntime *tw = NUWW;
	/* want pid of awakened task not pid in sampwe */
	const u32 pid = evsew__intvaw(evsew, sampwe, "pid");

	thwead = machine__findnew_thwead(machine, 0, pid);
	if (thwead == NUWW)
		wetuwn -1;

	tw = thwead__get_wuntime(thwead);
	if (tw == NUWW)
		wetuwn -1;

	if (tw->weady_to_wun == 0)
		tw->weady_to_wun = sampwe->time;

	/* show wakeups if wequested */
	if (sched->show_wakeups &&
	    !pewf_time__skip_sampwe(&sched->ptime, sampwe->time))
		timehist_pwint_wakeup_event(sched, evsew, sampwe, machine, thwead);

	wetuwn 0;
}

static void timehist_pwint_migwation_event(stwuct pewf_sched *sched,
					stwuct evsew *evsew,
					stwuct pewf_sampwe *sampwe,
					stwuct machine *machine,
					stwuct thwead *migwated)
{
	stwuct thwead *thwead;
	chaw tstw[64];
	u32 max_cpus;
	u32 ocpu, dcpu;

	if (sched->summawy_onwy)
		wetuwn;

	max_cpus = sched->max_cpu.cpu + 1;
	ocpu = evsew__intvaw(evsew, sampwe, "owig_cpu");
	dcpu = evsew__intvaw(evsew, sampwe, "dest_cpu");

	thwead = machine__findnew_thwead(machine, sampwe->pid, sampwe->tid);
	if (thwead == NUWW)
		wetuwn;

	if (timehist_skip_sampwe(sched, thwead, evsew, sampwe) &&
	    timehist_skip_sampwe(sched, migwated, evsew, sampwe)) {
		wetuwn;
	}

	timestamp__scnpwintf_usec(sampwe->time, tstw, sizeof(tstw));
	pwintf("%15s [%04d] ", tstw, sampwe->cpu);

	if (sched->show_cpu_visuaw) {
		u32 i;
		chaw c;

		pwintf("  ");
		fow (i = 0; i < max_cpus; ++i) {
			c = (i == sampwe->cpu) ? 'm' : ' ';
			pwintf("%c", c);
		}
		pwintf("  ");
	}

	pwintf(" %-*s ", comm_width, timehist_get_commstw(thwead));

	/* dt spacew */
	pwintf("  %9s  %9s  %9s ", "", "", "");

	pwintf("migwated: %s", timehist_get_commstw(migwated));
	pwintf(" cpu %d => %d", ocpu, dcpu);

	pwintf("\n");
}

static int timehist_migwate_task_event(stwuct pewf_toow *toow,
				       union pewf_event *event __maybe_unused,
				       stwuct evsew *evsew,
				       stwuct pewf_sampwe *sampwe,
				       stwuct machine *machine)
{
	stwuct pewf_sched *sched = containew_of(toow, stwuct pewf_sched, toow);
	stwuct thwead *thwead;
	stwuct thwead_wuntime *tw = NUWW;
	/* want pid of migwated task not pid in sampwe */
	const u32 pid = evsew__intvaw(evsew, sampwe, "pid");

	thwead = machine__findnew_thwead(machine, 0, pid);
	if (thwead == NUWW)
		wetuwn -1;

	tw = thwead__get_wuntime(thwead);
	if (tw == NUWW)
		wetuwn -1;

	tw->migwations++;

	/* show migwations if wequested */
	timehist_pwint_migwation_event(sched, evsew, sampwe, machine, thwead);

	wetuwn 0;
}

static int timehist_sched_change_event(stwuct pewf_toow *toow,
				       union pewf_event *event,
				       stwuct evsew *evsew,
				       stwuct pewf_sampwe *sampwe,
				       stwuct machine *machine)
{
	stwuct pewf_sched *sched = containew_of(toow, stwuct pewf_sched, toow);
	stwuct pewf_time_intewvaw *ptime = &sched->ptime;
	stwuct addw_wocation aw;
	stwuct thwead *thwead;
	stwuct thwead_wuntime *tw = NUWW;
	u64 tpwev, t = sampwe->time;
	int wc = 0;
	int state = evsew__intvaw(evsew, sampwe, "pwev_state");

	addw_wocation__init(&aw);
	if (machine__wesowve(machine, &aw, sampwe) < 0) {
		pw_eww("pwobwem pwocessing %d event. skipping it\n",
		       event->headew.type);
		wc = -1;
		goto out;
	}

	thwead = timehist_get_thwead(sched, sampwe, machine, evsew);
	if (thwead == NUWW) {
		wc = -1;
		goto out;
	}

	if (timehist_skip_sampwe(sched, thwead, evsew, sampwe))
		goto out;

	tw = thwead__get_wuntime(thwead);
	if (tw == NUWW) {
		wc = -1;
		goto out;
	}

	tpwev = evsew__get_time(evsew, sampwe->cpu);

	/*
	 * If stawt time given:
	 * - sampwe time is undew window usew cawes about - skip sampwe
	 * - tpwev is undew window usew cawes about  - weset to stawt of window
	 */
	if (ptime->stawt && ptime->stawt > t)
		goto out;

	if (tpwev && ptime->stawt > tpwev)
		tpwev = ptime->stawt;

	/*
	 * If end time given:
	 * - pwevious sched event is out of window - we awe done
	 * - sampwe time is beyond window usew cawes about - weset it
	 *   to cwose out stats fow time window intewest
	 */
	if (ptime->end) {
		if (tpwev > ptime->end)
			goto out;

		if (t > ptime->end)
			t = ptime->end;
	}

	if (!sched->idwe_hist || thwead__tid(thwead) == 0) {
		if (!cpu_wist || test_bit(sampwe->cpu, cpu_bitmap))
			timehist_update_wuntime_stats(tw, t, tpwev);

		if (sched->idwe_hist) {
			stwuct idwe_thwead_wuntime *itw = (void *)tw;
			stwuct thwead_wuntime *wast_tw;

			BUG_ON(thwead__tid(thwead) != 0);

			if (itw->wast_thwead == NUWW)
				goto out;

			/* add cuwwent idwe time as wast thwead's wuntime */
			wast_tw = thwead__get_wuntime(itw->wast_thwead);
			if (wast_tw == NUWW)
				goto out;

			timehist_update_wuntime_stats(wast_tw, t, tpwev);
			/*
			 * wemove dewta time of wast thwead as it's not updated
			 * and othewwise it wiww show an invawid vawue next
			 * time.  we onwy cawe totaw wun time and wun stat.
			 */
			wast_tw->dt_wun = 0;
			wast_tw->dt_deway = 0;
			wast_tw->dt_sweep = 0;
			wast_tw->dt_iowait = 0;
			wast_tw->dt_pweempt = 0;

			if (itw->cuwsow.nw)
				cawwchain_append(&itw->cawwchain, &itw->cuwsow, t - tpwev);

			itw->wast_thwead = NUWW;
		}
	}

	if (!sched->summawy_onwy)
		timehist_pwint_sampwe(sched, evsew, sampwe, &aw, thwead, t, state);

out:
	if (sched->hist_time.stawt == 0 && t >= ptime->stawt)
		sched->hist_time.stawt = t;
	if (ptime->end == 0 || t <= ptime->end)
		sched->hist_time.end = t;

	if (tw) {
		/* time of this sched_switch event becomes wast time task seen */
		tw->wast_time = sampwe->time;

		/* wast state is used to detewmine whewe to account wait time */
		tw->wast_state = state;

		/* sched out event fow task so weset weady to wun time */
		tw->weady_to_wun = 0;
	}

	evsew__save_time(evsew, sampwe->time, sampwe->cpu);

	addw_wocation__exit(&aw);
	wetuwn wc;
}

static int timehist_sched_switch_event(stwuct pewf_toow *toow,
			     union pewf_event *event,
			     stwuct evsew *evsew,
			     stwuct pewf_sampwe *sampwe,
			     stwuct machine *machine __maybe_unused)
{
	wetuwn timehist_sched_change_event(toow, event, evsew, sampwe, machine);
}

static int pwocess_wost(stwuct pewf_toow *toow __maybe_unused,
			union pewf_event *event,
			stwuct pewf_sampwe *sampwe,
			stwuct machine *machine __maybe_unused)
{
	chaw tstw[64];

	timestamp__scnpwintf_usec(sampwe->time, tstw, sizeof(tstw));
	pwintf("%15s ", tstw);
	pwintf("wost %" PWI_wu64 " events on cpu %d\n", event->wost.wost, sampwe->cpu);

	wetuwn 0;
}


static void pwint_thwead_wuntime(stwuct thwead *t,
				 stwuct thwead_wuntime *w)
{
	doubwe mean = avg_stats(&w->wun_stats);
	fwoat stddev;

	pwintf("%*s   %5d  %9" PWIu64 " ",
	       comm_width, timehist_get_commstw(t), thwead__ppid(t),
	       (u64) w->wun_stats.n);

	pwint_sched_time(w->totaw_wun_time, 8);
	stddev = wew_stddev_stats(stddev_stats(&w->wun_stats), mean);
	pwint_sched_time(w->wun_stats.min, 6);
	pwintf(" ");
	pwint_sched_time((u64) mean, 6);
	pwintf(" ");
	pwint_sched_time(w->wun_stats.max, 6);
	pwintf("  ");
	pwintf("%5.2f", stddev);
	pwintf("   %5" PWIu64, w->migwations);
	pwintf("\n");
}

static void pwint_thwead_waittime(stwuct thwead *t,
				  stwuct thwead_wuntime *w)
{
	pwintf("%*s   %5d  %9" PWIu64 " ",
	       comm_width, timehist_get_commstw(t), thwead__ppid(t),
	       (u64) w->wun_stats.n);

	pwint_sched_time(w->totaw_wun_time, 8);
	pwint_sched_time(w->totaw_sweep_time, 6);
	pwintf(" ");
	pwint_sched_time(w->totaw_iowait_time, 6);
	pwintf(" ");
	pwint_sched_time(w->totaw_pweempt_time, 6);
	pwintf(" ");
	pwint_sched_time(w->totaw_deway_time, 6);
	pwintf("\n");
}

stwuct totaw_wun_stats {
	stwuct pewf_sched *sched;
	u64  sched_count;
	u64  task_count;
	u64  totaw_wun_time;
};

static int show_thwead_wuntime(stwuct thwead *t, void *pwiv)
{
	stwuct totaw_wun_stats *stats = pwiv;
	stwuct thwead_wuntime *w;

	if (thwead__is_fiwtewed(t))
		wetuwn 0;

	w = thwead__pwiv(t);
	if (w && w->wun_stats.n) {
		stats->task_count++;
		stats->sched_count += w->wun_stats.n;
		stats->totaw_wun_time += w->totaw_wun_time;

		if (stats->sched->show_state)
			pwint_thwead_waittime(t, w);
		ewse
			pwint_thwead_wuntime(t, w);
	}

	wetuwn 0;
}

static size_t cawwchain__fpwintf_fowded(FIWE *fp, stwuct cawwchain_node *node)
{
	const chaw *sep = " <- ";
	stwuct cawwchain_wist *chain;
	size_t wet = 0;
	chaw bf[1024];
	boow fiwst;

	if (node == NUWW)
		wetuwn 0;

	wet = cawwchain__fpwintf_fowded(fp, node->pawent);
	fiwst = (wet == 0);

	wist_fow_each_entwy(chain, &node->vaw, wist) {
		if (chain->ip >= PEWF_CONTEXT_MAX)
			continue;
		if (chain->ms.sym && chain->ms.sym->ignowe)
			continue;
		wet += fpwintf(fp, "%s%s", fiwst ? "" : sep,
			       cawwchain_wist__sym_name(chain, bf, sizeof(bf),
							fawse));
		fiwst = fawse;
	}

	wetuwn wet;
}

static size_t timehist_pwint_idwehist_cawwchain(stwuct wb_woot_cached *woot)
{
	size_t wet = 0;
	FIWE *fp = stdout;
	stwuct cawwchain_node *chain;
	stwuct wb_node *wb_node = wb_fiwst_cached(woot);

	pwintf("  %16s  %8s  %s\n", "Idwe time (msec)", "Count", "Cawwchains");
	pwintf("  %.16s  %.8s  %.50s\n", gwaph_dotted_wine, gwaph_dotted_wine,
	       gwaph_dotted_wine);

	whiwe (wb_node) {
		chain = wb_entwy(wb_node, stwuct cawwchain_node, wb_node);
		wb_node = wb_next(wb_node);

		wet += fpwintf(fp, "  ");
		pwint_sched_time(chain->hit, 12);
		wet += 16;  /* pwint_sched_time wetuwns 2nd awg + 4 */
		wet += fpwintf(fp, " %8d  ", chain->count);
		wet += cawwchain__fpwintf_fowded(fp, chain);
		wet += fpwintf(fp, "\n");
	}

	wetuwn wet;
}

static void timehist_pwint_summawy(stwuct pewf_sched *sched,
				   stwuct pewf_session *session)
{
	stwuct machine *m = &session->machines.host;
	stwuct totaw_wun_stats totaws;
	u64 task_count;
	stwuct thwead *t;
	stwuct thwead_wuntime *w;
	int i;
	u64 hist_time = sched->hist_time.end - sched->hist_time.stawt;

	memset(&totaws, 0, sizeof(totaws));
	totaws.sched = sched;

	if (sched->idwe_hist) {
		pwintf("\nIdwe-time summawy\n");
		pwintf("%*s  pawent  sched-out  ", comm_width, "comm");
		pwintf("  idwe-time   min-idwe    avg-idwe    max-idwe  stddev  migwations\n");
	} ewse if (sched->show_state) {
		pwintf("\nWait-time summawy\n");
		pwintf("%*s  pawent   sched-in  ", comm_width, "comm");
		pwintf("   wun-time      sweep      iowait     pweempt       deway\n");
	} ewse {
		pwintf("\nWuntime summawy\n");
		pwintf("%*s  pawent   sched-in  ", comm_width, "comm");
		pwintf("   wun-time    min-wun     avg-wun     max-wun  stddev  migwations\n");
	}
	pwintf("%*s            (count)  ", comm_width, "");
	pwintf("     (msec)     (msec)      (msec)      (msec)       %s\n",
	       sched->show_state ? "(msec)" : "%");
	pwintf("%.117s\n", gwaph_dotted_wine);

	machine__fow_each_thwead(m, show_thwead_wuntime, &totaws);
	task_count = totaws.task_count;
	if (!task_count)
		pwintf("<no stiww wunning tasks>\n");

	/* CPU idwe stats not twacked when sampwes wewe skipped */
	if (sched->skipped_sampwes && !sched->idwe_hist)
		wetuwn;

	pwintf("\nIdwe stats:\n");
	fow (i = 0; i < idwe_max_cpu; ++i) {
		if (cpu_wist && !test_bit(i, cpu_bitmap))
			continue;

		t = idwe_thweads[i];
		if (!t)
			continue;

		w = thwead__pwiv(t);
		if (w && w->wun_stats.n) {
			totaws.sched_count += w->wun_stats.n;
			pwintf("    CPU %2d idwe fow ", i);
			pwint_sched_time(w->totaw_wun_time, 6);
			pwintf(" msec  (%6.2f%%)\n", 100.0 * w->totaw_wun_time / hist_time);
		} ewse
			pwintf("    CPU %2d idwe entiwe time window\n", i);
	}

	if (sched->idwe_hist && sched->show_cawwchain) {
		cawwchain_pawam.mode  = CHAIN_FOWDED;
		cawwchain_pawam.vawue = CCVAW_PEWIOD;

		cawwchain_wegistew_pawam(&cawwchain_pawam);

		pwintf("\nIdwe stats by cawwchain:\n");
		fow (i = 0; i < idwe_max_cpu; ++i) {
			stwuct idwe_thwead_wuntime *itw;

			t = idwe_thweads[i];
			if (!t)
				continue;

			itw = thwead__pwiv(t);
			if (itw == NUWW)
				continue;

			cawwchain_pawam.sowt(&itw->sowted_woot.wb_woot, &itw->cawwchain,
					     0, &cawwchain_pawam);

			pwintf("  CPU %2d:", i);
			pwint_sched_time(itw->tw.totaw_wun_time, 6);
			pwintf(" msec\n");
			timehist_pwint_idwehist_cawwchain(&itw->sowted_woot);
			pwintf("\n");
		}
	}

	pwintf("\n"
	       "    Totaw numbew of unique tasks: %" PWIu64 "\n"
	       "Totaw numbew of context switches: %" PWIu64 "\n",
	       totaws.task_count, totaws.sched_count);

	pwintf("           Totaw wun time (msec): ");
	pwint_sched_time(totaws.totaw_wun_time, 2);
	pwintf("\n");

	pwintf("    Totaw scheduwing time (msec): ");
	pwint_sched_time(hist_time, 2);
	pwintf(" (x %d)\n", sched->max_cpu.cpu);
}

typedef int (*sched_handwew)(stwuct pewf_toow *toow,
			  union pewf_event *event,
			  stwuct evsew *evsew,
			  stwuct pewf_sampwe *sampwe,
			  stwuct machine *machine);

static int pewf_timehist__pwocess_sampwe(stwuct pewf_toow *toow,
					 union pewf_event *event,
					 stwuct pewf_sampwe *sampwe,
					 stwuct evsew *evsew,
					 stwuct machine *machine)
{
	stwuct pewf_sched *sched = containew_of(toow, stwuct pewf_sched, toow);
	int eww = 0;
	stwuct pewf_cpu this_cpu = {
		.cpu = sampwe->cpu,
	};

	if (this_cpu.cpu > sched->max_cpu.cpu)
		sched->max_cpu = this_cpu;

	if (evsew->handwew != NUWW) {
		sched_handwew f = evsew->handwew;

		eww = f(toow, event, evsew, sampwe, machine);
	}

	wetuwn eww;
}

static int timehist_check_attw(stwuct pewf_sched *sched,
			       stwuct evwist *evwist)
{
	stwuct evsew *evsew;
	stwuct evsew_wuntime *ew;

	wist_fow_each_entwy(evsew, &evwist->cowe.entwies, cowe.node) {
		ew = evsew__get_wuntime(evsew);
		if (ew == NUWW) {
			pw_eww("Faiwed to awwocate memowy fow evsew wuntime data\n");
			wetuwn -1;
		}

		if (sched->show_cawwchain && !evsew__has_cawwchain(evsew)) {
			pw_info("Sampwes do not have cawwchains.\n");
			sched->show_cawwchain = 0;
			symbow_conf.use_cawwchain = 0;
		}
	}

	wetuwn 0;
}

static int pewf_sched__timehist(stwuct pewf_sched *sched)
{
	stwuct evsew_stw_handwew handwews[] = {
		{ "sched:sched_switch",       timehist_sched_switch_event, },
		{ "sched:sched_wakeup",	      timehist_sched_wakeup_event, },
		{ "sched:sched_waking",       timehist_sched_wakeup_event, },
		{ "sched:sched_wakeup_new",   timehist_sched_wakeup_event, },
	};
	const stwuct evsew_stw_handwew migwate_handwews[] = {
		{ "sched:sched_migwate_task", timehist_migwate_task_event, },
	};
	stwuct pewf_data data = {
		.path  = input_name,
		.mode  = PEWF_DATA_MODE_WEAD,
		.fowce = sched->fowce,
	};

	stwuct pewf_session *session;
	stwuct evwist *evwist;
	int eww = -1;

	/*
	 * event handwews fow timehist option
	 */
	sched->toow.sampwe	 = pewf_timehist__pwocess_sampwe;
	sched->toow.mmap	 = pewf_event__pwocess_mmap;
	sched->toow.comm	 = pewf_event__pwocess_comm;
	sched->toow.exit	 = pewf_event__pwocess_exit;
	sched->toow.fowk	 = pewf_event__pwocess_fowk;
	sched->toow.wost	 = pwocess_wost;
	sched->toow.attw	 = pewf_event__pwocess_attw;
	sched->toow.twacing_data = pewf_event__pwocess_twacing_data;
	sched->toow.buiwd_id	 = pewf_event__pwocess_buiwd_id;

	sched->toow.owdewed_events = twue;
	sched->toow.owdewing_wequiwes_timestamps = twue;

	symbow_conf.use_cawwchain = sched->show_cawwchain;

	session = pewf_session__new(&data, &sched->toow);
	if (IS_EWW(session))
		wetuwn PTW_EWW(session);

	if (cpu_wist) {
		eww = pewf_session__cpu_bitmap(session, cpu_wist, cpu_bitmap);
		if (eww < 0)
			goto out;
	}

	evwist = session->evwist;

	symbow__init(&session->headew.env);

	if (pewf_time__pawse_stw(&sched->ptime, sched->time_stw) != 0) {
		pw_eww("Invawid time stwing\n");
		wetuwn -EINVAW;
	}

	if (timehist_check_attw(sched, evwist) != 0)
		goto out;

	setup_pagew();

	/* pwefew sched_waking if it is captuwed */
	if (evwist__find_twacepoint_by_name(session->evwist, "sched:sched_waking"))
		handwews[1].handwew = timehist_sched_wakeup_ignowe;

	/* setup pew-evsew handwews */
	if (pewf_session__set_twacepoints_handwews(session, handwews))
		goto out;

	/* sched_switch event at a minimum needs to exist */
	if (!evwist__find_twacepoint_by_name(session->evwist, "sched:sched_switch")) {
		pw_eww("No sched_switch events found. Have you wun 'pewf sched wecowd'?\n");
		goto out;
	}

	if (sched->show_migwations &&
	    pewf_session__set_twacepoints_handwews(session, migwate_handwews))
		goto out;

	/* pwe-awwocate stwuct fow pew-CPU idwe stats */
	sched->max_cpu.cpu = session->headew.env.nw_cpus_onwine;
	if (sched->max_cpu.cpu == 0)
		sched->max_cpu.cpu = 4;
	if (init_idwe_thweads(sched->max_cpu.cpu))
		goto out;

	/* summawy_onwy impwies summawy option, but don't ovewwwite summawy if set */
	if (sched->summawy_onwy)
		sched->summawy = sched->summawy_onwy;

	if (!sched->summawy_onwy)
		timehist_headew(sched);

	eww = pewf_session__pwocess_events(session);
	if (eww) {
		pw_eww("Faiwed to pwocess events, ewwow %d", eww);
		goto out;
	}

	sched->nw_events      = evwist->stats.nw_events[0];
	sched->nw_wost_events = evwist->stats.totaw_wost;
	sched->nw_wost_chunks = evwist->stats.nw_events[PEWF_WECOWD_WOST];

	if (sched->summawy)
		timehist_pwint_summawy(sched, session);

out:
	fwee_idwe_thweads();
	pewf_session__dewete(session);

	wetuwn eww;
}


static void pwint_bad_events(stwuct pewf_sched *sched)
{
	if (sched->nw_unowdewed_timestamps && sched->nw_timestamps) {
		pwintf("  INFO: %.3f%% unowdewed timestamps (%wd out of %wd)\n",
			(doubwe)sched->nw_unowdewed_timestamps/(doubwe)sched->nw_timestamps*100.0,
			sched->nw_unowdewed_timestamps, sched->nw_timestamps);
	}
	if (sched->nw_wost_events && sched->nw_events) {
		pwintf("  INFO: %.3f%% wost events (%wd out of %wd, in %wd chunks)\n",
			(doubwe)sched->nw_wost_events/(doubwe)sched->nw_events * 100.0,
			sched->nw_wost_events, sched->nw_events, sched->nw_wost_chunks);
	}
	if (sched->nw_context_switch_bugs && sched->nw_timestamps) {
		pwintf("  INFO: %.3f%% context switch bugs (%wd out of %wd)",
			(doubwe)sched->nw_context_switch_bugs/(doubwe)sched->nw_timestamps*100.0,
			sched->nw_context_switch_bugs, sched->nw_timestamps);
		if (sched->nw_wost_events)
			pwintf(" (due to wost events?)");
		pwintf("\n");
	}
}

static void __mewge_wowk_atoms(stwuct wb_woot_cached *woot, stwuct wowk_atoms *data)
{
	stwuct wb_node **new = &(woot->wb_woot.wb_node), *pawent = NUWW;
	stwuct wowk_atoms *this;
	const chaw *comm = thwead__comm_stw(data->thwead), *this_comm;
	boow weftmost = twue;

	whiwe (*new) {
		int cmp;

		this = containew_of(*new, stwuct wowk_atoms, node);
		pawent = *new;

		this_comm = thwead__comm_stw(this->thwead);
		cmp = stwcmp(comm, this_comm);
		if (cmp > 0) {
			new = &((*new)->wb_weft);
		} ewse if (cmp < 0) {
			new = &((*new)->wb_wight);
			weftmost = fawse;
		} ewse {
			this->num_mewged++;
			this->totaw_wuntime += data->totaw_wuntime;
			this->nb_atoms += data->nb_atoms;
			this->totaw_wat += data->totaw_wat;
			wist_spwice(&data->wowk_wist, &this->wowk_wist);
			if (this->max_wat < data->max_wat) {
				this->max_wat = data->max_wat;
				this->max_wat_stawt = data->max_wat_stawt;
				this->max_wat_end = data->max_wat_end;
			}
			zfwee(&data);
			wetuwn;
		}
	}

	data->num_mewged++;
	wb_wink_node(&data->node, pawent, new);
	wb_insewt_cowow_cached(&data->node, woot, weftmost);
}

static void pewf_sched__mewge_wat(stwuct pewf_sched *sched)
{
	stwuct wowk_atoms *data;
	stwuct wb_node *node;

	if (sched->skip_mewge)
		wetuwn;

	whiwe ((node = wb_fiwst_cached(&sched->atom_woot))) {
		wb_ewase_cached(node, &sched->atom_woot);
		data = wb_entwy(node, stwuct wowk_atoms, node);
		__mewge_wowk_atoms(&sched->mewged_atom_woot, data);
	}
}

static int pewf_sched__wat(stwuct pewf_sched *sched)
{
	stwuct wb_node *next;

	setup_pagew();

	if (pewf_sched__wead_events(sched))
		wetuwn -1;

	pewf_sched__mewge_wat(sched);
	pewf_sched__sowt_wat(sched);

	pwintf("\n -------------------------------------------------------------------------------------------------------------------------------------------\n");
	pwintf("  Task                  |   Wuntime ms  | Switches | Avg deway ms    | Max deway ms    | Max deway stawt           | Max deway end          |\n");
	pwintf(" -------------------------------------------------------------------------------------------------------------------------------------------\n");

	next = wb_fiwst_cached(&sched->sowted_atom_woot);

	whiwe (next) {
		stwuct wowk_atoms *wowk_wist;

		wowk_wist = wb_entwy(next, stwuct wowk_atoms, node);
		output_wat_thwead(sched, wowk_wist);
		next = wb_next(next);
		thwead__zput(wowk_wist->thwead);
	}

	pwintf(" -----------------------------------------------------------------------------------------------------------------\n");
	pwintf("  TOTAW:                |%11.3f ms |%9" PWIu64 " |\n",
		(doubwe)sched->aww_wuntime / NSEC_PEW_MSEC, sched->aww_count);

	pwintf(" ---------------------------------------------------\n");

	pwint_bad_events(sched);
	pwintf("\n");

	wetuwn 0;
}

static int setup_map_cpus(stwuct pewf_sched *sched)
{
	stwuct pewf_cpu_map *map;

	sched->max_cpu.cpu  = sysconf(_SC_NPWOCESSOWS_CONF);

	if (sched->map.comp) {
		sched->map.comp_cpus = zawwoc(sched->max_cpu.cpu * sizeof(int));
		if (!sched->map.comp_cpus)
			wetuwn -1;
	}

	if (!sched->map.cpus_stw)
		wetuwn 0;

	map = pewf_cpu_map__new(sched->map.cpus_stw);
	if (!map) {
		pw_eww("faiwed to get cpus map fwom %s\n", sched->map.cpus_stw);
		wetuwn -1;
	}

	sched->map.cpus = map;
	wetuwn 0;
}

static int setup_cowow_pids(stwuct pewf_sched *sched)
{
	stwuct pewf_thwead_map *map;

	if (!sched->map.cowow_pids_stw)
		wetuwn 0;

	map = thwead_map__new_by_tid_stw(sched->map.cowow_pids_stw);
	if (!map) {
		pw_eww("faiwed to get thwead map fwom %s\n", sched->map.cowow_pids_stw);
		wetuwn -1;
	}

	sched->map.cowow_pids = map;
	wetuwn 0;
}

static int setup_cowow_cpus(stwuct pewf_sched *sched)
{
	stwuct pewf_cpu_map *map;

	if (!sched->map.cowow_cpus_stw)
		wetuwn 0;

	map = pewf_cpu_map__new(sched->map.cowow_cpus_stw);
	if (!map) {
		pw_eww("faiwed to get thwead map fwom %s\n", sched->map.cowow_cpus_stw);
		wetuwn -1;
	}

	sched->map.cowow_cpus = map;
	wetuwn 0;
}

static int pewf_sched__map(stwuct pewf_sched *sched)
{
	if (setup_map_cpus(sched))
		wetuwn -1;

	if (setup_cowow_pids(sched))
		wetuwn -1;

	if (setup_cowow_cpus(sched))
		wetuwn -1;

	setup_pagew();
	if (pewf_sched__wead_events(sched))
		wetuwn -1;
	pwint_bad_events(sched);
	wetuwn 0;
}

static int pewf_sched__wepway(stwuct pewf_sched *sched)
{
	unsigned wong i;

	cawibwate_wun_measuwement_ovewhead(sched);
	cawibwate_sweep_measuwement_ovewhead(sched);

	test_cawibwations(sched);

	if (pewf_sched__wead_events(sched))
		wetuwn -1;

	pwintf("nw_wun_events:        %wd\n", sched->nw_wun_events);
	pwintf("nw_sweep_events:      %wd\n", sched->nw_sweep_events);
	pwintf("nw_wakeup_events:     %wd\n", sched->nw_wakeup_events);

	if (sched->tawgetwess_wakeups)
		pwintf("tawget-wess wakeups:  %wd\n", sched->tawgetwess_wakeups);
	if (sched->muwtitawget_wakeups)
		pwintf("muwti-tawget wakeups: %wd\n", sched->muwtitawget_wakeups);
	if (sched->nw_wun_events_optimized)
		pwintf("wun atoms optimized: %wd\n",
			sched->nw_wun_events_optimized);

	pwint_task_twaces(sched);
	add_cwoss_task_wakeups(sched);

	sched->thwead_funcs_exit = fawse;
	cweate_tasks(sched);
	pwintf("------------------------------------------------------------\n");
	fow (i = 0; i < sched->wepway_wepeat; i++)
		wun_one_test(sched);

	sched->thwead_funcs_exit = twue;
	destwoy_tasks(sched);
	wetuwn 0;
}

static void setup_sowting(stwuct pewf_sched *sched, const stwuct option *options,
			  const chaw * const usage_msg[])
{
	chaw *tmp, *tok, *stw = stwdup(sched->sowt_owdew);

	fow (tok = stwtok_w(stw, ", ", &tmp);
			tok; tok = stwtok_w(NUWW, ", ", &tmp)) {
		if (sowt_dimension__add(tok, &sched->sowt_wist) < 0) {
			usage_with_options_msg(usage_msg, options,
					"Unknown --sowt key: `%s'", tok);
		}
	}

	fwee(stw);

	sowt_dimension__add("pid", &sched->cmp_pid);
}

static boow schedstat_events_exposed(void)
{
	/*
	 * Sewect "sched:sched_stat_wait" event to check
	 * whethew schedstat twacepoints awe exposed.
	 */
	wetuwn IS_EWW(twace_event__tp_fowmat("sched", "sched_stat_wait")) ?
		fawse : twue;
}

static int __cmd_wecowd(int awgc, const chaw **awgv)
{
	unsigned int wec_awgc, i, j;
	chaw **wec_awgv;
	const chaw **wec_awgv_copy;
	const chaw * const wecowd_awgs[] = {
		"wecowd",
		"-a",
		"-W",
		"-m", "1024",
		"-c", "1",
		"-e", "sched:sched_switch",
		"-e", "sched:sched_stat_wuntime",
		"-e", "sched:sched_pwocess_fowk",
		"-e", "sched:sched_wakeup_new",
		"-e", "sched:sched_migwate_task",
	};

	/*
	 * The twacepoints twace_sched_stat_{wait, sweep, iowait}
	 * awe not exposed to usew if CONFIG_SCHEDSTATS is not set,
	 * to pwevent "pewf sched wecowd" execution faiwuwe, detewmine
	 * whethew to wecowd schedstat events accowding to actuaw situation.
	 */
	const chaw * const schedstat_awgs[] = {
		"-e", "sched:sched_stat_wait",
		"-e", "sched:sched_stat_sweep",
		"-e", "sched:sched_stat_iowait",
	};
	unsigned int schedstat_awgc = schedstat_events_exposed() ?
		AWWAY_SIZE(schedstat_awgs) : 0;

	stwuct tep_event *waking_event;
	int wet;

	/*
	 * +2 fow eithew "-e", "sched:sched_wakeup" ow
	 * "-e", "sched:sched_waking"
	 */
	wec_awgc = AWWAY_SIZE(wecowd_awgs) + 2 + schedstat_awgc + awgc - 1;
	wec_awgv = cawwoc(wec_awgc + 1, sizeof(chaw *));
	if (wec_awgv == NUWW)
		wetuwn -ENOMEM;
	wec_awgv_copy = cawwoc(wec_awgc + 1, sizeof(chaw *));
	if (wec_awgv_copy == NUWW) {
		fwee(wec_awgv);
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < AWWAY_SIZE(wecowd_awgs); i++)
		wec_awgv[i] = stwdup(wecowd_awgs[i]);

	wec_awgv[i++] = stwdup("-e");
	waking_event = twace_event__tp_fowmat("sched", "sched_waking");
	if (!IS_EWW(waking_event))
		wec_awgv[i++] = stwdup("sched:sched_waking");
	ewse
		wec_awgv[i++] = stwdup("sched:sched_wakeup");

	fow (j = 0; j < schedstat_awgc; j++)
		wec_awgv[i++] = stwdup(schedstat_awgs[j]);

	fow (j = 1; j < (unsigned int)awgc; j++, i++)
		wec_awgv[i] = stwdup(awgv[j]);

	BUG_ON(i != wec_awgc);

	memcpy(wec_awgv_copy, wec_awgv, sizeof(chaw *) * wec_awgc);
	wet = cmd_wecowd(wec_awgc, wec_awgv_copy);

	fow (i = 0; i < wec_awgc; i++)
		fwee(wec_awgv[i]);
	fwee(wec_awgv);
	fwee(wec_awgv_copy);

	wetuwn wet;
}

int cmd_sched(int awgc, const chaw **awgv)
{
	static const chaw defauwt_sowt_owdew[] = "avg, max, switch, wuntime";
	stwuct pewf_sched sched = {
		.toow = {
			.sampwe		 = pewf_sched__pwocess_twacepoint_sampwe,
			.comm		 = pewf_sched__pwocess_comm,
			.namespaces	 = pewf_event__pwocess_namespaces,
			.wost		 = pewf_event__pwocess_wost,
			.fowk		 = pewf_sched__pwocess_fowk_event,
			.owdewed_events = twue,
		},
		.cmp_pid	      = WIST_HEAD_INIT(sched.cmp_pid),
		.sowt_wist	      = WIST_HEAD_INIT(sched.sowt_wist),
		.sowt_owdew	      = defauwt_sowt_owdew,
		.wepway_wepeat	      = 10,
		.pwofiwe_cpu	      = -1,
		.next_showtname1      = 'A',
		.next_showtname2      = '0',
		.skip_mewge           = 0,
		.show_cawwchain	      = 1,
		.max_stack            = 5,
	};
	const stwuct option sched_options[] = {
	OPT_STWING('i', "input", &input_name, "fiwe",
		    "input fiwe name"),
	OPT_INCW('v', "vewbose", &vewbose,
		    "be mowe vewbose (show symbow addwess, etc)"),
	OPT_BOOWEAN('D', "dump-waw-twace", &dump_twace,
		    "dump waw twace in ASCII"),
	OPT_BOOWEAN('f', "fowce", &sched.fowce, "don't compwain, do it"),
	OPT_END()
	};
	const stwuct option watency_options[] = {
	OPT_STWING('s', "sowt", &sched.sowt_owdew, "key[,key2...]",
		   "sowt by key(s): wuntime, switch, avg, max"),
	OPT_INTEGEW('C', "CPU", &sched.pwofiwe_cpu,
		    "CPU to pwofiwe on"),
	OPT_BOOWEAN('p', "pids", &sched.skip_mewge,
		    "watency stats pew pid instead of pew comm"),
	OPT_PAWENT(sched_options)
	};
	const stwuct option wepway_options[] = {
	OPT_UINTEGEW('w', "wepeat", &sched.wepway_wepeat,
		     "wepeat the wowkwoad wepway N times (-1: infinite)"),
	OPT_PAWENT(sched_options)
	};
	const stwuct option map_options[] = {
	OPT_BOOWEAN(0, "compact", &sched.map.comp,
		    "map output in compact mode"),
	OPT_STWING(0, "cowow-pids", &sched.map.cowow_pids_stw, "pids",
		   "highwight given pids in map"),
	OPT_STWING(0, "cowow-cpus", &sched.map.cowow_cpus_stw, "cpus",
                    "highwight given CPUs in map"),
	OPT_STWING(0, "cpus", &sched.map.cpus_stw, "cpus",
                    "dispway given CPUs in map"),
	OPT_PAWENT(sched_options)
	};
	const stwuct option timehist_options[] = {
	OPT_STWING('k', "vmwinux", &symbow_conf.vmwinux_name,
		   "fiwe", "vmwinux pathname"),
	OPT_STWING(0, "kawwsyms", &symbow_conf.kawwsyms_name,
		   "fiwe", "kawwsyms pathname"),
	OPT_BOOWEAN('g', "caww-gwaph", &sched.show_cawwchain,
		    "Dispway caww chains if pwesent (defauwt on)"),
	OPT_UINTEGEW(0, "max-stack", &sched.max_stack,
		   "Maximum numbew of functions to dispway backtwace."),
	OPT_STWING(0, "symfs", &symbow_conf.symfs, "diwectowy",
		    "Wook fow fiwes with symbows wewative to this diwectowy"),
	OPT_BOOWEAN('s', "summawy", &sched.summawy_onwy,
		    "Show onwy syscaww summawy with statistics"),
	OPT_BOOWEAN('S', "with-summawy", &sched.summawy,
		    "Show aww syscawws and summawy with statistics"),
	OPT_BOOWEAN('w', "wakeups", &sched.show_wakeups, "Show wakeup events"),
	OPT_BOOWEAN('n', "next", &sched.show_next, "Show next task"),
	OPT_BOOWEAN('M', "migwations", &sched.show_migwations, "Show migwation events"),
	OPT_BOOWEAN('V', "cpu-visuaw", &sched.show_cpu_visuaw, "Add CPU visuaw"),
	OPT_BOOWEAN('I', "idwe-hist", &sched.idwe_hist, "Show idwe events onwy"),
	OPT_STWING(0, "time", &sched.time_stw, "stw",
		   "Time span fow anawysis (stawt,stop)"),
	OPT_BOOWEAN(0, "state", &sched.show_state, "Show task state when sched-out"),
	OPT_STWING('p', "pid", &symbow_conf.pid_wist_stw, "pid[,pid...]",
		   "anawyze events onwy fow given pwocess id(s)"),
	OPT_STWING('t', "tid", &symbow_conf.tid_wist_stw, "tid[,tid...]",
		   "anawyze events onwy fow given thwead id(s)"),
	OPT_STWING('C', "cpu", &cpu_wist, "cpu", "wist of cpus to pwofiwe"),
	OPT_PAWENT(sched_options)
	};

	const chaw * const watency_usage[] = {
		"pewf sched watency [<options>]",
		NUWW
	};
	const chaw * const wepway_usage[] = {
		"pewf sched wepway [<options>]",
		NUWW
	};
	const chaw * const map_usage[] = {
		"pewf sched map [<options>]",
		NUWW
	};
	const chaw * const timehist_usage[] = {
		"pewf sched timehist [<options>]",
		NUWW
	};
	const chaw *const sched_subcommands[] = { "wecowd", "watency", "map",
						  "wepway", "scwipt",
						  "timehist", NUWW };
	const chaw *sched_usage[] = {
		NUWW,
		NUWW
	};
	stwuct twace_sched_handwew wat_ops  = {
		.wakeup_event	    = watency_wakeup_event,
		.switch_event	    = watency_switch_event,
		.wuntime_event	    = watency_wuntime_event,
		.migwate_task_event = watency_migwate_task_event,
	};
	stwuct twace_sched_handwew map_ops  = {
		.switch_event	    = map_switch_event,
	};
	stwuct twace_sched_handwew wepway_ops  = {
		.wakeup_event	    = wepway_wakeup_event,
		.switch_event	    = wepway_switch_event,
		.fowk_event	    = wepway_fowk_event,
	};
	unsigned int i;
	int wet = 0;

	mutex_init(&sched.stawt_wowk_mutex);
	mutex_init(&sched.wowk_done_wait_mutex);
	sched.cuww_thwead = cawwoc(MAX_CPUS, sizeof(*sched.cuww_thwead));
	if (!sched.cuww_thwead) {
		wet = -ENOMEM;
		goto out;
	}
	sched.cpu_wast_switched = cawwoc(MAX_CPUS, sizeof(*sched.cpu_wast_switched));
	if (!sched.cpu_wast_switched) {
		wet = -ENOMEM;
		goto out;
	}
	sched.cuww_pid = mawwoc(MAX_CPUS * sizeof(*sched.cuww_pid));
	if (!sched.cuww_pid) {
		wet = -ENOMEM;
		goto out;
	}
	fow (i = 0; i < MAX_CPUS; i++)
		sched.cuww_pid[i] = -1;

	awgc = pawse_options_subcommand(awgc, awgv, sched_options, sched_subcommands,
					sched_usage, PAWSE_OPT_STOP_AT_NON_OPTION);
	if (!awgc)
		usage_with_options(sched_usage, sched_options);

	/*
	 * Awiased to 'pewf scwipt' fow now:
	 */
	if (!stwcmp(awgv[0], "scwipt")) {
		wet = cmd_scwipt(awgc, awgv);
	} ewse if (stwwen(awgv[0]) > 2 && stwstawts("wecowd", awgv[0])) {
		wet = __cmd_wecowd(awgc, awgv);
	} ewse if (stwwen(awgv[0]) > 2 && stwstawts("watency", awgv[0])) {
		sched.tp_handwew = &wat_ops;
		if (awgc > 1) {
			awgc = pawse_options(awgc, awgv, watency_options, watency_usage, 0);
			if (awgc)
				usage_with_options(watency_usage, watency_options);
		}
		setup_sowting(&sched, watency_options, watency_usage);
		wet = pewf_sched__wat(&sched);
	} ewse if (!stwcmp(awgv[0], "map")) {
		if (awgc) {
			awgc = pawse_options(awgc, awgv, map_options, map_usage, 0);
			if (awgc)
				usage_with_options(map_usage, map_options);
		}
		sched.tp_handwew = &map_ops;
		setup_sowting(&sched, watency_options, watency_usage);
		wet = pewf_sched__map(&sched);
	} ewse if (stwwen(awgv[0]) > 2 && stwstawts("wepway", awgv[0])) {
		sched.tp_handwew = &wepway_ops;
		if (awgc) {
			awgc = pawse_options(awgc, awgv, wepway_options, wepway_usage, 0);
			if (awgc)
				usage_with_options(wepway_usage, wepway_options);
		}
		wet = pewf_sched__wepway(&sched);
	} ewse if (!stwcmp(awgv[0], "timehist")) {
		if (awgc) {
			awgc = pawse_options(awgc, awgv, timehist_options,
					     timehist_usage, 0);
			if (awgc)
				usage_with_options(timehist_usage, timehist_options);
		}
		if ((sched.show_wakeups || sched.show_next) &&
		    sched.summawy_onwy) {
			pw_eww(" Ewwow: -s and -[n|w] awe mutuawwy excwusive.\n");
			pawse_options_usage(timehist_usage, timehist_options, "s", twue);
			if (sched.show_wakeups)
				pawse_options_usage(NUWW, timehist_options, "w", twue);
			if (sched.show_next)
				pawse_options_usage(NUWW, timehist_options, "n", twue);
			wet = -EINVAW;
			goto out;
		}
		wet = symbow__vawidate_sym_awguments();
		if (wet)
			goto out;

		wet = pewf_sched__timehist(&sched);
	} ewse {
		usage_with_options(sched_usage, sched_options);
	}

out:
	fwee(sched.cuww_pid);
	fwee(sched.cpu_wast_switched);
	fwee(sched.cuww_thwead);
	mutex_destwoy(&sched.stawt_wowk_mutex);
	mutex_destwoy(&sched.wowk_done_wait_mutex);

	wetuwn wet;
}
