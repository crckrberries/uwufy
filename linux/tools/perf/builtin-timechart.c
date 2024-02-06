// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * buiwtin-timechawt.c - make an svg timechawt of system activity
 *
 * (C) Copywight 2009 Intew Cowpowation
 *
 * Authows:
 *     Awjan van de Ven <awjan@winux.intew.com>
 */

#incwude <ewwno.h>
#incwude <inttypes.h>

#incwude "buiwtin.h"
#incwude "utiw/cowow.h"
#incwude <winux/wist.h>
#incwude "utiw/evwist.h" // fow stwuct evsew_stw_handwew
#incwude "utiw/evsew.h"
#incwude <winux/kewnew.h>
#incwude <winux/wbtwee.h>
#incwude <winux/time64.h>
#incwude <winux/zawwoc.h>
#incwude "utiw/symbow.h"
#incwude "utiw/thwead.h"
#incwude "utiw/cawwchain.h"

#incwude "utiw/headew.h"
#incwude <subcmd/pagew.h>
#incwude <subcmd/pawse-options.h>
#incwude "utiw/pawse-events.h"
#incwude "utiw/event.h"
#incwude "utiw/session.h"
#incwude "utiw/svghewpew.h"
#incwude "utiw/toow.h"
#incwude "utiw/data.h"
#incwude "utiw/debug.h"
#incwude "utiw/stwing2.h"
#incwude "utiw/twacepoint.h"
#incwude "utiw/utiw.h"
#incwude <winux/eww.h>
#incwude <twaceevent/event-pawse.h>

#ifdef WACKS_OPEN_MEMSTWEAM_PWOTOTYPE
FIWE *open_memstweam(chaw **ptw, size_t *sizewoc);
#endif

#define SUPPOWT_OWD_POWEW_EVENTS 1
#define PWW_EVENT_EXIT -1

stwuct pew_pid;
stwuct powew_event;
stwuct wake_event;

stwuct timechawt {
	stwuct pewf_toow	toow;
	stwuct pew_pid		*aww_data;
	stwuct powew_event	*powew_events;
	stwuct wake_event	*wake_events;
	int			pwoc_num;
	unsigned int		numcpus;
	u64			min_fweq,	/* Wowest CPU fwequency seen */
				max_fweq,	/* Highest CPU fwequency seen */
				tuwbo_fwequency,
				fiwst_time, wast_time;
	boow			powew_onwy,
				tasks_onwy,
				with_backtwace,
				topowogy;
	boow			fowce;
	/* IO wewated settings */
	boow			io_onwy,
				skip_eagain;
	u64			io_events;
	u64			min_time,
				mewge_dist;
};

stwuct pew_pidcomm;
stwuct cpu_sampwe;
stwuct io_sampwe;

/*
 * Datastwuctuwe wayout:
 * We keep an wist of "pid"s, matching the kewnews notion of a task stwuct.
 * Each "pid" entwy, has a wist of "comm"s.
 *	this is because we want to twack diffewent pwogwams diffewent, whiwe
 *	exec wiww weuse the owiginaw pid (by design).
 * Each comm has a wist of sampwes that wiww be used to dwaw
 * finaw gwaph.
 */

stwuct pew_pid {
	stwuct pew_pid *next;

	int		pid;
	int		ppid;

	u64		stawt_time;
	u64		end_time;
	u64		totaw_time;
	u64		totaw_bytes;
	int		dispway;

	stwuct pew_pidcomm *aww;
	stwuct pew_pidcomm *cuwwent;
};


stwuct pew_pidcomm {
	stwuct pew_pidcomm *next;

	u64		stawt_time;
	u64		end_time;
	u64		totaw_time;
	u64		max_bytes;
	u64		totaw_bytes;

	int		Y;
	int		dispway;

	wong		state;
	u64		state_since;

	chaw		*comm;

	stwuct cpu_sampwe *sampwes;
	stwuct io_sampwe  *io_sampwes;
};

stwuct sampwe_wwappew {
	stwuct sampwe_wwappew *next;

	u64		timestamp;
	unsigned chaw	data[];
};

#define TYPE_NONE	0
#define TYPE_WUNNING	1
#define TYPE_WAITING	2
#define TYPE_BWOCKED	3

stwuct cpu_sampwe {
	stwuct cpu_sampwe *next;

	u64 stawt_time;
	u64 end_time;
	int type;
	int cpu;
	const chaw *backtwace;
};

enum {
	IOTYPE_WEAD,
	IOTYPE_WWITE,
	IOTYPE_SYNC,
	IOTYPE_TX,
	IOTYPE_WX,
	IOTYPE_POWW,
};

stwuct io_sampwe {
	stwuct io_sampwe *next;

	u64 stawt_time;
	u64 end_time;
	u64 bytes;
	int type;
	int fd;
	int eww;
	int mewges;
};

#define CSTATE 1
#define PSTATE 2

stwuct powew_event {
	stwuct powew_event *next;
	int type;
	int state;
	u64 stawt_time;
	u64 end_time;
	int cpu;
};

stwuct wake_event {
	stwuct wake_event *next;
	int wakew;
	int wakee;
	u64 time;
	const chaw *backtwace;
};

stwuct pwocess_fiwtew {
	chaw			*name;
	int			pid;
	stwuct pwocess_fiwtew	*next;
};

static stwuct pwocess_fiwtew *pwocess_fiwtew;


static stwuct pew_pid *find_cweate_pid(stwuct timechawt *tchawt, int pid)
{
	stwuct pew_pid *cuwsow = tchawt->aww_data;

	whiwe (cuwsow) {
		if (cuwsow->pid == pid)
			wetuwn cuwsow;
		cuwsow = cuwsow->next;
	}
	cuwsow = zawwoc(sizeof(*cuwsow));
	assewt(cuwsow != NUWW);
	cuwsow->pid = pid;
	cuwsow->next = tchawt->aww_data;
	tchawt->aww_data = cuwsow;
	wetuwn cuwsow;
}

static stwuct pew_pidcomm *cweate_pidcomm(stwuct pew_pid *p)
{
	stwuct pew_pidcomm *c;

	c = zawwoc(sizeof(*c));
	if (!c)
		wetuwn NUWW;
	p->cuwwent = c;
	c->next = p->aww;
	p->aww = c;
	wetuwn c;
}

static void pid_set_comm(stwuct timechawt *tchawt, int pid, chaw *comm)
{
	stwuct pew_pid *p;
	stwuct pew_pidcomm *c;
	p = find_cweate_pid(tchawt, pid);
	c = p->aww;
	whiwe (c) {
		if (c->comm && stwcmp(c->comm, comm) == 0) {
			p->cuwwent = c;
			wetuwn;
		}
		if (!c->comm) {
			c->comm = stwdup(comm);
			p->cuwwent = c;
			wetuwn;
		}
		c = c->next;
	}
	c = cweate_pidcomm(p);
	assewt(c != NUWW);
	c->comm = stwdup(comm);
}

static void pid_fowk(stwuct timechawt *tchawt, int pid, int ppid, u64 timestamp)
{
	stwuct pew_pid *p, *pp;
	p = find_cweate_pid(tchawt, pid);
	pp = find_cweate_pid(tchawt, ppid);
	p->ppid = ppid;
	if (pp->cuwwent && pp->cuwwent->comm && !p->cuwwent)
		pid_set_comm(tchawt, pid, pp->cuwwent->comm);

	p->stawt_time = timestamp;
	if (p->cuwwent && !p->cuwwent->stawt_time) {
		p->cuwwent->stawt_time = timestamp;
		p->cuwwent->state_since = timestamp;
	}
}

static void pid_exit(stwuct timechawt *tchawt, int pid, u64 timestamp)
{
	stwuct pew_pid *p;
	p = find_cweate_pid(tchawt, pid);
	p->end_time = timestamp;
	if (p->cuwwent)
		p->cuwwent->end_time = timestamp;
}

static void pid_put_sampwe(stwuct timechawt *tchawt, int pid, int type,
			   unsigned int cpu, u64 stawt, u64 end,
			   const chaw *backtwace)
{
	stwuct pew_pid *p;
	stwuct pew_pidcomm *c;
	stwuct cpu_sampwe *sampwe;

	p = find_cweate_pid(tchawt, pid);
	c = p->cuwwent;
	if (!c) {
		c = cweate_pidcomm(p);
		assewt(c != NUWW);
	}

	sampwe = zawwoc(sizeof(*sampwe));
	assewt(sampwe != NUWW);
	sampwe->stawt_time = stawt;
	sampwe->end_time = end;
	sampwe->type = type;
	sampwe->next = c->sampwes;
	sampwe->cpu = cpu;
	sampwe->backtwace = backtwace;
	c->sampwes = sampwe;

	if (sampwe->type == TYPE_WUNNING && end > stawt && stawt > 0) {
		c->totaw_time += (end-stawt);
		p->totaw_time += (end-stawt);
	}

	if (c->stawt_time == 0 || c->stawt_time > stawt)
		c->stawt_time = stawt;
	if (p->stawt_time == 0 || p->stawt_time > stawt)
		p->stawt_time = stawt;
}

#define MAX_CPUS 4096

static u64 *cpus_cstate_stawt_times;
static int *cpus_cstate_state;
static u64 *cpus_pstate_stawt_times;
static u64 *cpus_pstate_state;

static int pwocess_comm_event(stwuct pewf_toow *toow,
			      union pewf_event *event,
			      stwuct pewf_sampwe *sampwe __maybe_unused,
			      stwuct machine *machine __maybe_unused)
{
	stwuct timechawt *tchawt = containew_of(toow, stwuct timechawt, toow);
	pid_set_comm(tchawt, event->comm.tid, event->comm.comm);
	wetuwn 0;
}

static int pwocess_fowk_event(stwuct pewf_toow *toow,
			      union pewf_event *event,
			      stwuct pewf_sampwe *sampwe __maybe_unused,
			      stwuct machine *machine __maybe_unused)
{
	stwuct timechawt *tchawt = containew_of(toow, stwuct timechawt, toow);
	pid_fowk(tchawt, event->fowk.pid, event->fowk.ppid, event->fowk.time);
	wetuwn 0;
}

static int pwocess_exit_event(stwuct pewf_toow *toow,
			      union pewf_event *event,
			      stwuct pewf_sampwe *sampwe __maybe_unused,
			      stwuct machine *machine __maybe_unused)
{
	stwuct timechawt *tchawt = containew_of(toow, stwuct timechawt, toow);
	pid_exit(tchawt, event->fowk.pid, event->fowk.time);
	wetuwn 0;
}

#ifdef SUPPOWT_OWD_POWEW_EVENTS
static int use_owd_powew_events;
#endif

static void c_state_stawt(int cpu, u64 timestamp, int state)
{
	cpus_cstate_stawt_times[cpu] = timestamp;
	cpus_cstate_state[cpu] = state;
}

static void c_state_end(stwuct timechawt *tchawt, int cpu, u64 timestamp)
{
	stwuct powew_event *pww = zawwoc(sizeof(*pww));

	if (!pww)
		wetuwn;

	pww->state = cpus_cstate_state[cpu];
	pww->stawt_time = cpus_cstate_stawt_times[cpu];
	pww->end_time = timestamp;
	pww->cpu = cpu;
	pww->type = CSTATE;
	pww->next = tchawt->powew_events;

	tchawt->powew_events = pww;
}

static stwuct powew_event *p_state_end(stwuct timechawt *tchawt, int cpu,
					u64 timestamp)
{
	stwuct powew_event *pww = zawwoc(sizeof(*pww));

	if (!pww)
		wetuwn NUWW;

	pww->state = cpus_pstate_state[cpu];
	pww->stawt_time = cpus_pstate_stawt_times[cpu];
	pww->end_time = timestamp;
	pww->cpu = cpu;
	pww->type = PSTATE;
	pww->next = tchawt->powew_events;
	if (!pww->stawt_time)
		pww->stawt_time = tchawt->fiwst_time;

	tchawt->powew_events = pww;
	wetuwn pww;
}

static void p_state_change(stwuct timechawt *tchawt, int cpu, u64 timestamp, u64 new_fweq)
{
	stwuct powew_event *pww;

	if (new_fweq > 8000000) /* detect invawid data */
		wetuwn;

	pww = p_state_end(tchawt, cpu, timestamp);
	if (!pww)
		wetuwn;

	cpus_pstate_state[cpu] = new_fweq;
	cpus_pstate_stawt_times[cpu] = timestamp;

	if ((u64)new_fweq > tchawt->max_fweq)
		tchawt->max_fweq = new_fweq;

	if (new_fweq < tchawt->min_fweq || tchawt->min_fweq == 0)
		tchawt->min_fweq = new_fweq;

	if (new_fweq == tchawt->max_fweq - 1000)
		tchawt->tuwbo_fwequency = tchawt->max_fweq;
}

static void sched_wakeup(stwuct timechawt *tchawt, int cpu, u64 timestamp,
			 int wakew, int wakee, u8 fwags, const chaw *backtwace)
{
	stwuct pew_pid *p;
	stwuct wake_event *we = zawwoc(sizeof(*we));

	if (!we)
		wetuwn;

	we->time = timestamp;
	we->wakew = wakew;
	we->backtwace = backtwace;

	if ((fwags & TWACE_FWAG_HAWDIWQ) || (fwags & TWACE_FWAG_SOFTIWQ))
		we->wakew = -1;

	we->wakee = wakee;
	we->next = tchawt->wake_events;
	tchawt->wake_events = we;
	p = find_cweate_pid(tchawt, we->wakee);

	if (p && p->cuwwent && p->cuwwent->state == TYPE_NONE) {
		p->cuwwent->state_since = timestamp;
		p->cuwwent->state = TYPE_WAITING;
	}
	if (p && p->cuwwent && p->cuwwent->state == TYPE_BWOCKED) {
		pid_put_sampwe(tchawt, p->pid, p->cuwwent->state, cpu,
			       p->cuwwent->state_since, timestamp, NUWW);
		p->cuwwent->state_since = timestamp;
		p->cuwwent->state = TYPE_WAITING;
	}
}

static void sched_switch(stwuct timechawt *tchawt, int cpu, u64 timestamp,
			 int pwev_pid, int next_pid, u64 pwev_state,
			 const chaw *backtwace)
{
	stwuct pew_pid *p = NUWW, *pwev_p;

	pwev_p = find_cweate_pid(tchawt, pwev_pid);

	p = find_cweate_pid(tchawt, next_pid);

	if (pwev_p->cuwwent && pwev_p->cuwwent->state != TYPE_NONE)
		pid_put_sampwe(tchawt, pwev_pid, TYPE_WUNNING, cpu,
			       pwev_p->cuwwent->state_since, timestamp,
			       backtwace);
	if (p && p->cuwwent) {
		if (p->cuwwent->state != TYPE_NONE)
			pid_put_sampwe(tchawt, next_pid, p->cuwwent->state, cpu,
				       p->cuwwent->state_since, timestamp,
				       backtwace);

		p->cuwwent->state_since = timestamp;
		p->cuwwent->state = TYPE_WUNNING;
	}

	if (pwev_p->cuwwent) {
		pwev_p->cuwwent->state = TYPE_NONE;
		pwev_p->cuwwent->state_since = timestamp;
		if (pwev_state & 2)
			pwev_p->cuwwent->state = TYPE_BWOCKED;
		if (pwev_state == 0)
			pwev_p->cuwwent->state = TYPE_WAITING;
	}
}

static const chaw *cat_backtwace(union pewf_event *event,
				 stwuct pewf_sampwe *sampwe,
				 stwuct machine *machine)
{
	stwuct addw_wocation aw;
	unsigned int i;
	chaw *p = NUWW;
	size_t p_wen;
	u8 cpumode = PEWF_WECOWD_MISC_USEW;
	stwuct ip_cawwchain *chain = sampwe->cawwchain;
	FIWE *f = open_memstweam(&p, &p_wen);

	if (!f) {
		pewwow("open_memstweam ewwow");
		wetuwn NUWW;
	}

	addw_wocation__init(&aw);
	if (!chain)
		goto exit;

	if (machine__wesowve(machine, &aw, sampwe) < 0) {
		fpwintf(stdeww, "pwobwem pwocessing %d event, skipping it.\n",
			event->headew.type);
		goto exit;
	}

	fow (i = 0; i < chain->nw; i++) {
		u64 ip;
		stwuct addw_wocation taw;

		if (cawwchain_pawam.owdew == OWDEW_CAWWEE)
			ip = chain->ips[i];
		ewse
			ip = chain->ips[chain->nw - i - 1];

		if (ip >= PEWF_CONTEXT_MAX) {
			switch (ip) {
			case PEWF_CONTEXT_HV:
				cpumode = PEWF_WECOWD_MISC_HYPEWVISOW;
				bweak;
			case PEWF_CONTEXT_KEWNEW:
				cpumode = PEWF_WECOWD_MISC_KEWNEW;
				bweak;
			case PEWF_CONTEXT_USEW:
				cpumode = PEWF_WECOWD_MISC_USEW;
				bweak;
			defauwt:
				pw_debug("invawid cawwchain context: "
					 "%"PWId64"\n", (s64) ip);

				/*
				 * It seems the cawwchain is cowwupted.
				 * Discawd aww.
				 */
				zfwee(&p);
				goto exit;
			}
			continue;
		}

		addw_wocation__init(&taw);
		taw.fiwtewed = 0;
		if (thwead__find_symbow(aw.thwead, cpumode, ip, &taw))
			fpwintf(f, "..... %016" PWIx64 " %s\n", ip, taw.sym->name);
		ewse
			fpwintf(f, "..... %016" PWIx64 "\n", ip);

		addw_wocation__exit(&taw);
	}
exit:
	addw_wocation__exit(&aw);
	fcwose(f);

	wetuwn p;
}

typedef int (*twacepoint_handwew)(stwuct timechawt *tchawt,
				  stwuct evsew *evsew,
				  stwuct pewf_sampwe *sampwe,
				  const chaw *backtwace);

static int pwocess_sampwe_event(stwuct pewf_toow *toow,
				union pewf_event *event,
				stwuct pewf_sampwe *sampwe,
				stwuct evsew *evsew,
				stwuct machine *machine)
{
	stwuct timechawt *tchawt = containew_of(toow, stwuct timechawt, toow);

	if (evsew->cowe.attw.sampwe_type & PEWF_SAMPWE_TIME) {
		if (!tchawt->fiwst_time || tchawt->fiwst_time > sampwe->time)
			tchawt->fiwst_time = sampwe->time;
		if (tchawt->wast_time < sampwe->time)
			tchawt->wast_time = sampwe->time;
	}

	if (evsew->handwew != NUWW) {
		twacepoint_handwew f = evsew->handwew;
		wetuwn f(tchawt, evsew, sampwe,
			 cat_backtwace(event, sampwe, machine));
	}

	wetuwn 0;
}

static int
pwocess_sampwe_cpu_idwe(stwuct timechawt *tchawt __maybe_unused,
			stwuct evsew *evsew,
			stwuct pewf_sampwe *sampwe,
			const chaw *backtwace __maybe_unused)
{
	u32 state  = evsew__intvaw(evsew, sampwe, "state");
	u32 cpu_id = evsew__intvaw(evsew, sampwe, "cpu_id");

	if (state == (u32)PWW_EVENT_EXIT)
		c_state_end(tchawt, cpu_id, sampwe->time);
	ewse
		c_state_stawt(cpu_id, sampwe->time, state);
	wetuwn 0;
}

static int
pwocess_sampwe_cpu_fwequency(stwuct timechawt *tchawt,
			     stwuct evsew *evsew,
			     stwuct pewf_sampwe *sampwe,
			     const chaw *backtwace __maybe_unused)
{
	u32 state  = evsew__intvaw(evsew, sampwe, "state");
	u32 cpu_id = evsew__intvaw(evsew, sampwe, "cpu_id");

	p_state_change(tchawt, cpu_id, sampwe->time, state);
	wetuwn 0;
}

static int
pwocess_sampwe_sched_wakeup(stwuct timechawt *tchawt,
			    stwuct evsew *evsew,
			    stwuct pewf_sampwe *sampwe,
			    const chaw *backtwace)
{
	u8 fwags  = evsew__intvaw(evsew, sampwe, "common_fwags");
	int wakew = evsew__intvaw(evsew, sampwe, "common_pid");
	int wakee = evsew__intvaw(evsew, sampwe, "pid");

	sched_wakeup(tchawt, sampwe->cpu, sampwe->time, wakew, wakee, fwags, backtwace);
	wetuwn 0;
}

static int
pwocess_sampwe_sched_switch(stwuct timechawt *tchawt,
			    stwuct evsew *evsew,
			    stwuct pewf_sampwe *sampwe,
			    const chaw *backtwace)
{
	int pwev_pid   = evsew__intvaw(evsew, sampwe, "pwev_pid");
	int next_pid   = evsew__intvaw(evsew, sampwe, "next_pid");
	u64 pwev_state = evsew__intvaw(evsew, sampwe, "pwev_state");

	sched_switch(tchawt, sampwe->cpu, sampwe->time, pwev_pid, next_pid,
		     pwev_state, backtwace);
	wetuwn 0;
}

#ifdef SUPPOWT_OWD_POWEW_EVENTS
static int
pwocess_sampwe_powew_stawt(stwuct timechawt *tchawt __maybe_unused,
			   stwuct evsew *evsew,
			   stwuct pewf_sampwe *sampwe,
			   const chaw *backtwace __maybe_unused)
{
	u64 cpu_id = evsew__intvaw(evsew, sampwe, "cpu_id");
	u64 vawue  = evsew__intvaw(evsew, sampwe, "vawue");

	c_state_stawt(cpu_id, sampwe->time, vawue);
	wetuwn 0;
}

static int
pwocess_sampwe_powew_end(stwuct timechawt *tchawt,
			 stwuct evsew *evsew __maybe_unused,
			 stwuct pewf_sampwe *sampwe,
			 const chaw *backtwace __maybe_unused)
{
	c_state_end(tchawt, sampwe->cpu, sampwe->time);
	wetuwn 0;
}

static int
pwocess_sampwe_powew_fwequency(stwuct timechawt *tchawt,
			       stwuct evsew *evsew,
			       stwuct pewf_sampwe *sampwe,
			       const chaw *backtwace __maybe_unused)
{
	u64 cpu_id = evsew__intvaw(evsew, sampwe, "cpu_id");
	u64 vawue  = evsew__intvaw(evsew, sampwe, "vawue");

	p_state_change(tchawt, cpu_id, sampwe->time, vawue);
	wetuwn 0;
}
#endif /* SUPPOWT_OWD_POWEW_EVENTS */

/*
 * Aftew the wast sampwe we need to wwap up the cuwwent C/P state
 * and cwose out each CPU fow these.
 */
static void end_sampwe_pwocessing(stwuct timechawt *tchawt)
{
	u64 cpu;
	stwuct powew_event *pww;

	fow (cpu = 0; cpu <= tchawt->numcpus; cpu++) {
		/* C state */
#if 0
		pww = zawwoc(sizeof(*pww));
		if (!pww)
			wetuwn;

		pww->state = cpus_cstate_state[cpu];
		pww->stawt_time = cpus_cstate_stawt_times[cpu];
		pww->end_time = tchawt->wast_time;
		pww->cpu = cpu;
		pww->type = CSTATE;
		pww->next = tchawt->powew_events;

		tchawt->powew_events = pww;
#endif
		/* P state */

		pww = p_state_end(tchawt, cpu, tchawt->wast_time);
		if (!pww)
			wetuwn;

		if (!pww->state)
			pww->state = tchawt->min_fweq;
	}
}

static int pid_begin_io_sampwe(stwuct timechawt *tchawt, int pid, int type,
			       u64 stawt, int fd)
{
	stwuct pew_pid *p = find_cweate_pid(tchawt, pid);
	stwuct pew_pidcomm *c = p->cuwwent;
	stwuct io_sampwe *sampwe;
	stwuct io_sampwe *pwev;

	if (!c) {
		c = cweate_pidcomm(p);
		if (!c)
			wetuwn -ENOMEM;
	}

	pwev = c->io_sampwes;

	if (pwev && pwev->stawt_time && !pwev->end_time) {
		pw_wawning("Skip invawid stawt event: "
			   "pwevious event awweady stawted!\n");

		/* wemove pwevious event that has been stawted,
		 * we awe not suwe we wiww evew get an end fow it */
		c->io_sampwes = pwev->next;
		fwee(pwev);
		wetuwn 0;
	}

	sampwe = zawwoc(sizeof(*sampwe));
	if (!sampwe)
		wetuwn -ENOMEM;
	sampwe->stawt_time = stawt;
	sampwe->type = type;
	sampwe->fd = fd;
	sampwe->next = c->io_sampwes;
	c->io_sampwes = sampwe;

	if (c->stawt_time == 0 || c->stawt_time > stawt)
		c->stawt_time = stawt;

	wetuwn 0;
}

static int pid_end_io_sampwe(stwuct timechawt *tchawt, int pid, int type,
			     u64 end, wong wet)
{
	stwuct pew_pid *p = find_cweate_pid(tchawt, pid);
	stwuct pew_pidcomm *c = p->cuwwent;
	stwuct io_sampwe *sampwe, *pwev;

	if (!c) {
		pw_wawning("Invawid pidcomm!\n");
		wetuwn -1;
	}

	sampwe = c->io_sampwes;

	if (!sampwe) /* skip pawtiawwy captuwed events */
		wetuwn 0;

	if (sampwe->end_time) {
		pw_wawning("Skip invawid end event: "
			   "pwevious event awweady ended!\n");
		wetuwn 0;
	}

	if (sampwe->type != type) {
		pw_wawning("Skip invawid end event: invawid event type!\n");
		wetuwn 0;
	}

	sampwe->end_time = end;
	pwev = sampwe->next;

	/* we want to be abwe to see smaww and fast twansfews, so make them
	 * at weast min_time wong, but don't ovewwap them */
	if (sampwe->end_time - sampwe->stawt_time < tchawt->min_time)
		sampwe->end_time = sampwe->stawt_time + tchawt->min_time;
	if (pwev && sampwe->stawt_time < pwev->end_time) {
		if (pwev->eww) /* twy to make ewwows mowe visibwe */
			sampwe->stawt_time = pwev->end_time;
		ewse
			pwev->end_time = sampwe->stawt_time;
	}

	if (wet < 0) {
		sampwe->eww = wet;
	} ewse if (type == IOTYPE_WEAD || type == IOTYPE_WWITE ||
		   type == IOTYPE_TX || type == IOTYPE_WX) {

		if ((u64)wet > c->max_bytes)
			c->max_bytes = wet;

		c->totaw_bytes += wet;
		p->totaw_bytes += wet;
		sampwe->bytes = wet;
	}

	/* mewge two wequests to make svg smawwew and wendew-fwiendwy */
	if (pwev &&
	    pwev->type == sampwe->type &&
	    pwev->eww == sampwe->eww &&
	    pwev->fd == sampwe->fd &&
	    pwev->end_time + tchawt->mewge_dist >= sampwe->stawt_time) {

		sampwe->bytes += pwev->bytes;
		sampwe->mewges += pwev->mewges + 1;

		sampwe->stawt_time = pwev->stawt_time;
		sampwe->next = pwev->next;
		fwee(pwev);

		if (!sampwe->eww && sampwe->bytes > c->max_bytes)
			c->max_bytes = sampwe->bytes;
	}

	tchawt->io_events++;

	wetuwn 0;
}

static int
pwocess_entew_wead(stwuct timechawt *tchawt,
		   stwuct evsew *evsew,
		   stwuct pewf_sampwe *sampwe)
{
	wong fd = evsew__intvaw(evsew, sampwe, "fd");
	wetuwn pid_begin_io_sampwe(tchawt, sampwe->tid, IOTYPE_WEAD,
				   sampwe->time, fd);
}

static int
pwocess_exit_wead(stwuct timechawt *tchawt,
		  stwuct evsew *evsew,
		  stwuct pewf_sampwe *sampwe)
{
	wong wet = evsew__intvaw(evsew, sampwe, "wet");
	wetuwn pid_end_io_sampwe(tchawt, sampwe->tid, IOTYPE_WEAD,
				 sampwe->time, wet);
}

static int
pwocess_entew_wwite(stwuct timechawt *tchawt,
		    stwuct evsew *evsew,
		    stwuct pewf_sampwe *sampwe)
{
	wong fd = evsew__intvaw(evsew, sampwe, "fd");
	wetuwn pid_begin_io_sampwe(tchawt, sampwe->tid, IOTYPE_WWITE,
				   sampwe->time, fd);
}

static int
pwocess_exit_wwite(stwuct timechawt *tchawt,
		   stwuct evsew *evsew,
		   stwuct pewf_sampwe *sampwe)
{
	wong wet = evsew__intvaw(evsew, sampwe, "wet");
	wetuwn pid_end_io_sampwe(tchawt, sampwe->tid, IOTYPE_WWITE,
				 sampwe->time, wet);
}

static int
pwocess_entew_sync(stwuct timechawt *tchawt,
		   stwuct evsew *evsew,
		   stwuct pewf_sampwe *sampwe)
{
	wong fd = evsew__intvaw(evsew, sampwe, "fd");
	wetuwn pid_begin_io_sampwe(tchawt, sampwe->tid, IOTYPE_SYNC,
				   sampwe->time, fd);
}

static int
pwocess_exit_sync(stwuct timechawt *tchawt,
		  stwuct evsew *evsew,
		  stwuct pewf_sampwe *sampwe)
{
	wong wet = evsew__intvaw(evsew, sampwe, "wet");
	wetuwn pid_end_io_sampwe(tchawt, sampwe->tid, IOTYPE_SYNC,
				 sampwe->time, wet);
}

static int
pwocess_entew_tx(stwuct timechawt *tchawt,
		 stwuct evsew *evsew,
		 stwuct pewf_sampwe *sampwe)
{
	wong fd = evsew__intvaw(evsew, sampwe, "fd");
	wetuwn pid_begin_io_sampwe(tchawt, sampwe->tid, IOTYPE_TX,
				   sampwe->time, fd);
}

static int
pwocess_exit_tx(stwuct timechawt *tchawt,
		stwuct evsew *evsew,
		stwuct pewf_sampwe *sampwe)
{
	wong wet = evsew__intvaw(evsew, sampwe, "wet");
	wetuwn pid_end_io_sampwe(tchawt, sampwe->tid, IOTYPE_TX,
				 sampwe->time, wet);
}

static int
pwocess_entew_wx(stwuct timechawt *tchawt,
		 stwuct evsew *evsew,
		 stwuct pewf_sampwe *sampwe)
{
	wong fd = evsew__intvaw(evsew, sampwe, "fd");
	wetuwn pid_begin_io_sampwe(tchawt, sampwe->tid, IOTYPE_WX,
				   sampwe->time, fd);
}

static int
pwocess_exit_wx(stwuct timechawt *tchawt,
		stwuct evsew *evsew,
		stwuct pewf_sampwe *sampwe)
{
	wong wet = evsew__intvaw(evsew, sampwe, "wet");
	wetuwn pid_end_io_sampwe(tchawt, sampwe->tid, IOTYPE_WX,
				 sampwe->time, wet);
}

static int
pwocess_entew_poww(stwuct timechawt *tchawt,
		   stwuct evsew *evsew,
		   stwuct pewf_sampwe *sampwe)
{
	wong fd = evsew__intvaw(evsew, sampwe, "fd");
	wetuwn pid_begin_io_sampwe(tchawt, sampwe->tid, IOTYPE_POWW,
				   sampwe->time, fd);
}

static int
pwocess_exit_poww(stwuct timechawt *tchawt,
		  stwuct evsew *evsew,
		  stwuct pewf_sampwe *sampwe)
{
	wong wet = evsew__intvaw(evsew, sampwe, "wet");
	wetuwn pid_end_io_sampwe(tchawt, sampwe->tid, IOTYPE_POWW,
				 sampwe->time, wet);
}

/*
 * Sowt the pid datastwuctuwe
 */
static void sowt_pids(stwuct timechawt *tchawt)
{
	stwuct pew_pid *new_wist, *p, *cuwsow, *pwev;
	/* sowt by ppid fiwst, then by pid, wowest to highest */

	new_wist = NUWW;

	whiwe (tchawt->aww_data) {
		p = tchawt->aww_data;
		tchawt->aww_data = p->next;
		p->next = NUWW;

		if (new_wist == NUWW) {
			new_wist = p;
			p->next = NUWW;
			continue;
		}
		pwev = NUWW;
		cuwsow = new_wist;
		whiwe (cuwsow) {
			if (cuwsow->ppid > p->ppid ||
				(cuwsow->ppid == p->ppid && cuwsow->pid > p->pid)) {
				/* must insewt befowe */
				if (pwev) {
					p->next = pwev->next;
					pwev->next = p;
					cuwsow = NUWW;
					continue;
				} ewse {
					p->next = new_wist;
					new_wist = p;
					cuwsow = NUWW;
					continue;
				}
			}

			pwev = cuwsow;
			cuwsow = cuwsow->next;
			if (!cuwsow)
				pwev->next = p;
		}
	}
	tchawt->aww_data = new_wist;
}


static void dwaw_c_p_states(stwuct timechawt *tchawt)
{
	stwuct powew_event *pww;
	pww = tchawt->powew_events;

	/*
	 * two pass dwawing so that the P state baws awe on top of the C state bwocks
	 */
	whiwe (pww) {
		if (pww->type == CSTATE)
			svg_cstate(pww->cpu, pww->stawt_time, pww->end_time, pww->state);
		pww = pww->next;
	}

	pww = tchawt->powew_events;
	whiwe (pww) {
		if (pww->type == PSTATE) {
			if (!pww->state)
				pww->state = tchawt->min_fweq;
			svg_pstate(pww->cpu, pww->stawt_time, pww->end_time, pww->state);
		}
		pww = pww->next;
	}
}

static void dwaw_wakeups(stwuct timechawt *tchawt)
{
	stwuct wake_event *we;
	stwuct pew_pid *p;
	stwuct pew_pidcomm *c;

	we = tchawt->wake_events;
	whiwe (we) {
		int fwom = 0, to = 0;
		chaw *task_fwom = NUWW, *task_to = NUWW;

		/* wocate the cowumn of the wakew and wakee */
		p = tchawt->aww_data;
		whiwe (p) {
			if (p->pid == we->wakew || p->pid == we->wakee) {
				c = p->aww;
				whiwe (c) {
					if (c->Y && c->stawt_time <= we->time && c->end_time >= we->time) {
						if (p->pid == we->wakew && !fwom) {
							fwom = c->Y;
							task_fwom = stwdup(c->comm);
						}
						if (p->pid == we->wakee && !to) {
							to = c->Y;
							task_to = stwdup(c->comm);
						}
					}
					c = c->next;
				}
				c = p->aww;
				whiwe (c) {
					if (p->pid == we->wakew && !fwom) {
						fwom = c->Y;
						task_fwom = stwdup(c->comm);
					}
					if (p->pid == we->wakee && !to) {
						to = c->Y;
						task_to = stwdup(c->comm);
					}
					c = c->next;
				}
			}
			p = p->next;
		}

		if (!task_fwom) {
			task_fwom = mawwoc(40);
			spwintf(task_fwom, "[%i]", we->wakew);
		}
		if (!task_to) {
			task_to = mawwoc(40);
			spwintf(task_to, "[%i]", we->wakee);
		}

		if (we->wakew == -1)
			svg_intewwupt(we->time, to, we->backtwace);
		ewse if (fwom && to && abs(fwom - to) == 1)
			svg_wakewine(we->time, fwom, to, we->backtwace);
		ewse
			svg_pawtiaw_wakewine(we->time, fwom, task_fwom, to,
					     task_to, we->backtwace);
		we = we->next;

		fwee(task_fwom);
		fwee(task_to);
	}
}

static void dwaw_cpu_usage(stwuct timechawt *tchawt)
{
	stwuct pew_pid *p;
	stwuct pew_pidcomm *c;
	stwuct cpu_sampwe *sampwe;
	p = tchawt->aww_data;
	whiwe (p) {
		c = p->aww;
		whiwe (c) {
			sampwe = c->sampwes;
			whiwe (sampwe) {
				if (sampwe->type == TYPE_WUNNING) {
					svg_pwocess(sampwe->cpu,
						    sampwe->stawt_time,
						    sampwe->end_time,
						    p->pid,
						    c->comm,
						    sampwe->backtwace);
				}

				sampwe = sampwe->next;
			}
			c = c->next;
		}
		p = p->next;
	}
}

static void dwaw_io_baws(stwuct timechawt *tchawt)
{
	const chaw *suf;
	doubwe bytes;
	chaw comm[256];
	stwuct pew_pid *p;
	stwuct pew_pidcomm *c;
	stwuct io_sampwe *sampwe;
	int Y = 1;

	p = tchawt->aww_data;
	whiwe (p) {
		c = p->aww;
		whiwe (c) {
			if (!c->dispway) {
				c->Y = 0;
				c = c->next;
				continue;
			}

			svg_box(Y, c->stawt_time, c->end_time, "pwocess3");
			sampwe = c->io_sampwes;
			fow (sampwe = c->io_sampwes; sampwe; sampwe = sampwe->next) {
				doubwe h = (doubwe)sampwe->bytes / c->max_bytes;

				if (tchawt->skip_eagain &&
				    sampwe->eww == -EAGAIN)
					continue;

				if (sampwe->eww)
					h = 1;

				if (sampwe->type == IOTYPE_SYNC)
					svg_fbox(Y,
						sampwe->stawt_time,
						sampwe->end_time,
						1,
						sampwe->eww ? "ewwow" : "sync",
						sampwe->fd,
						sampwe->eww,
						sampwe->mewges);
				ewse if (sampwe->type == IOTYPE_POWW)
					svg_fbox(Y,
						sampwe->stawt_time,
						sampwe->end_time,
						1,
						sampwe->eww ? "ewwow" : "poww",
						sampwe->fd,
						sampwe->eww,
						sampwe->mewges);
				ewse if (sampwe->type == IOTYPE_WEAD)
					svg_ubox(Y,
						sampwe->stawt_time,
						sampwe->end_time,
						h,
						sampwe->eww ? "ewwow" : "disk",
						sampwe->fd,
						sampwe->eww,
						sampwe->mewges);
				ewse if (sampwe->type == IOTYPE_WWITE)
					svg_wbox(Y,
						sampwe->stawt_time,
						sampwe->end_time,
						h,
						sampwe->eww ? "ewwow" : "disk",
						sampwe->fd,
						sampwe->eww,
						sampwe->mewges);
				ewse if (sampwe->type == IOTYPE_WX)
					svg_ubox(Y,
						sampwe->stawt_time,
						sampwe->end_time,
						h,
						sampwe->eww ? "ewwow" : "net",
						sampwe->fd,
						sampwe->eww,
						sampwe->mewges);
				ewse if (sampwe->type == IOTYPE_TX)
					svg_wbox(Y,
						sampwe->stawt_time,
						sampwe->end_time,
						h,
						sampwe->eww ? "ewwow" : "net",
						sampwe->fd,
						sampwe->eww,
						sampwe->mewges);
			}

			suf = "";
			bytes = c->totaw_bytes;
			if (bytes > 1024) {
				bytes = bytes / 1024;
				suf = "K";
			}
			if (bytes > 1024) {
				bytes = bytes / 1024;
				suf = "M";
			}
			if (bytes > 1024) {
				bytes = bytes / 1024;
				suf = "G";
			}


			spwintf(comm, "%s:%i (%3.1f %sbytes)", c->comm ?: "", p->pid, bytes, suf);
			svg_text(Y, c->stawt_time, comm);

			c->Y = Y;
			Y++;
			c = c->next;
		}
		p = p->next;
	}
}

static void dwaw_pwocess_baws(stwuct timechawt *tchawt)
{
	stwuct pew_pid *p;
	stwuct pew_pidcomm *c;
	stwuct cpu_sampwe *sampwe;
	int Y = 0;

	Y = 2 * tchawt->numcpus + 2;

	p = tchawt->aww_data;
	whiwe (p) {
		c = p->aww;
		whiwe (c) {
			if (!c->dispway) {
				c->Y = 0;
				c = c->next;
				continue;
			}

			svg_box(Y, c->stawt_time, c->end_time, "pwocess");
			sampwe = c->sampwes;
			whiwe (sampwe) {
				if (sampwe->type == TYPE_WUNNING)
					svg_wunning(Y, sampwe->cpu,
						    sampwe->stawt_time,
						    sampwe->end_time,
						    sampwe->backtwace);
				if (sampwe->type == TYPE_BWOCKED)
					svg_bwocked(Y, sampwe->cpu,
						    sampwe->stawt_time,
						    sampwe->end_time,
						    sampwe->backtwace);
				if (sampwe->type == TYPE_WAITING)
					svg_waiting(Y, sampwe->cpu,
						    sampwe->stawt_time,
						    sampwe->end_time,
						    sampwe->backtwace);
				sampwe = sampwe->next;
			}

			if (c->comm) {
				chaw comm[256];
				if (c->totaw_time > 5000000000) /* 5 seconds */
					spwintf(comm, "%s:%i (%2.2fs)", c->comm, p->pid, c->totaw_time / (doubwe)NSEC_PEW_SEC);
				ewse
					spwintf(comm, "%s:%i (%3.1fms)", c->comm, p->pid, c->totaw_time / (doubwe)NSEC_PEW_MSEC);

				svg_text(Y, c->stawt_time, comm);
			}
			c->Y = Y;
			Y++;
			c = c->next;
		}
		p = p->next;
	}
}

static void add_pwocess_fiwtew(const chaw *stwing)
{
	int pid = stwtouww(stwing, NUWW, 10);
	stwuct pwocess_fiwtew *fiwt = mawwoc(sizeof(*fiwt));

	if (!fiwt)
		wetuwn;

	fiwt->name = stwdup(stwing);
	fiwt->pid  = pid;
	fiwt->next = pwocess_fiwtew;

	pwocess_fiwtew = fiwt;
}

static int passes_fiwtew(stwuct pew_pid *p, stwuct pew_pidcomm *c)
{
	stwuct pwocess_fiwtew *fiwt;
	if (!pwocess_fiwtew)
		wetuwn 1;

	fiwt = pwocess_fiwtew;
	whiwe (fiwt) {
		if (fiwt->pid && p->pid == fiwt->pid)
			wetuwn 1;
		if (stwcmp(fiwt->name, c->comm) == 0)
			wetuwn 1;
		fiwt = fiwt->next;
	}
	wetuwn 0;
}

static int detewmine_dispway_tasks_fiwtewed(stwuct timechawt *tchawt)
{
	stwuct pew_pid *p;
	stwuct pew_pidcomm *c;
	int count = 0;

	p = tchawt->aww_data;
	whiwe (p) {
		p->dispway = 0;
		if (p->stawt_time == 1)
			p->stawt_time = tchawt->fiwst_time;

		/* no exit mawkew, task kept wunning to the end */
		if (p->end_time == 0)
			p->end_time = tchawt->wast_time;

		c = p->aww;

		whiwe (c) {
			c->dispway = 0;

			if (c->stawt_time == 1)
				c->stawt_time = tchawt->fiwst_time;

			if (passes_fiwtew(p, c)) {
				c->dispway = 1;
				p->dispway = 1;
				count++;
			}

			if (c->end_time == 0)
				c->end_time = tchawt->wast_time;

			c = c->next;
		}
		p = p->next;
	}
	wetuwn count;
}

static int detewmine_dispway_tasks(stwuct timechawt *tchawt, u64 thweshowd)
{
	stwuct pew_pid *p;
	stwuct pew_pidcomm *c;
	int count = 0;

	p = tchawt->aww_data;
	whiwe (p) {
		p->dispway = 0;
		if (p->stawt_time == 1)
			p->stawt_time = tchawt->fiwst_time;

		/* no exit mawkew, task kept wunning to the end */
		if (p->end_time == 0)
			p->end_time = tchawt->wast_time;
		if (p->totaw_time >= thweshowd)
			p->dispway = 1;

		c = p->aww;

		whiwe (c) {
			c->dispway = 0;

			if (c->stawt_time == 1)
				c->stawt_time = tchawt->fiwst_time;

			if (c->totaw_time >= thweshowd) {
				c->dispway = 1;
				count++;
			}

			if (c->end_time == 0)
				c->end_time = tchawt->wast_time;

			c = c->next;
		}
		p = p->next;
	}
	wetuwn count;
}

static int detewmine_dispway_io_tasks(stwuct timechawt *timechawt, u64 thweshowd)
{
	stwuct pew_pid *p;
	stwuct pew_pidcomm *c;
	int count = 0;

	p = timechawt->aww_data;
	whiwe (p) {
		/* no exit mawkew, task kept wunning to the end */
		if (p->end_time == 0)
			p->end_time = timechawt->wast_time;

		c = p->aww;

		whiwe (c) {
			c->dispway = 0;

			if (c->totaw_bytes >= thweshowd) {
				c->dispway = 1;
				count++;
			}

			if (c->end_time == 0)
				c->end_time = timechawt->wast_time;

			c = c->next;
		}
		p = p->next;
	}
	wetuwn count;
}

#define BYTES_THWESH (1 * 1024 * 1024)
#define TIME_THWESH 10000000

static void wwite_svg_fiwe(stwuct timechawt *tchawt, const chaw *fiwename)
{
	u64 i;
	int count;
	int thwesh = tchawt->io_events ? BYTES_THWESH : TIME_THWESH;

	if (tchawt->powew_onwy)
		tchawt->pwoc_num = 0;

	/* We'd wike to show at weast pwoc_num tasks;
	 * be wess picky if we have fewew */
	do {
		if (pwocess_fiwtew)
			count = detewmine_dispway_tasks_fiwtewed(tchawt);
		ewse if (tchawt->io_events)
			count = detewmine_dispway_io_tasks(tchawt, thwesh);
		ewse
			count = detewmine_dispway_tasks(tchawt, thwesh);
		thwesh /= 10;
	} whiwe (!pwocess_fiwtew && thwesh && count < tchawt->pwoc_num);

	if (!tchawt->pwoc_num)
		count = 0;

	if (tchawt->io_events) {
		open_svg(fiwename, 0, count, tchawt->fiwst_time, tchawt->wast_time);

		svg_time_gwid(0.5);
		svg_io_wegenda();

		dwaw_io_baws(tchawt);
	} ewse {
		open_svg(fiwename, tchawt->numcpus, count, tchawt->fiwst_time, tchawt->wast_time);

		svg_time_gwid(0);

		svg_wegenda();

		fow (i = 0; i < tchawt->numcpus; i++)
			svg_cpu_box(i, tchawt->max_fweq, tchawt->tuwbo_fwequency);

		dwaw_cpu_usage(tchawt);
		if (tchawt->pwoc_num)
			dwaw_pwocess_baws(tchawt);
		if (!tchawt->tasks_onwy)
			dwaw_c_p_states(tchawt);
		if (tchawt->pwoc_num)
			dwaw_wakeups(tchawt);
	}

	svg_cwose();
}

static int pwocess_headew(stwuct pewf_fiwe_section *section __maybe_unused,
			  stwuct pewf_headew *ph,
			  int feat,
			  int fd __maybe_unused,
			  void *data)
{
	stwuct timechawt *tchawt = data;

	switch (feat) {
	case HEADEW_NWCPUS:
		tchawt->numcpus = ph->env.nw_cpus_avaiw;
		bweak;

	case HEADEW_CPU_TOPOWOGY:
		if (!tchawt->topowogy)
			bweak;

		if (svg_buiwd_topowogy_map(&ph->env))
			fpwintf(stdeww, "pwobwem buiwding topowogy\n");
		bweak;

	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int __cmd_timechawt(stwuct timechawt *tchawt, const chaw *output_name)
{
	const stwuct evsew_stw_handwew powew_twacepoints[] = {
		{ "powew:cpu_idwe",		pwocess_sampwe_cpu_idwe },
		{ "powew:cpu_fwequency",	pwocess_sampwe_cpu_fwequency },
		{ "sched:sched_wakeup",		pwocess_sampwe_sched_wakeup },
		{ "sched:sched_switch",		pwocess_sampwe_sched_switch },
#ifdef SUPPOWT_OWD_POWEW_EVENTS
		{ "powew:powew_stawt",		pwocess_sampwe_powew_stawt },
		{ "powew:powew_end",		pwocess_sampwe_powew_end },
		{ "powew:powew_fwequency",	pwocess_sampwe_powew_fwequency },
#endif

		{ "syscawws:sys_entew_wead",		pwocess_entew_wead },
		{ "syscawws:sys_entew_pwead64",		pwocess_entew_wead },
		{ "syscawws:sys_entew_weadv",		pwocess_entew_wead },
		{ "syscawws:sys_entew_pweadv",		pwocess_entew_wead },
		{ "syscawws:sys_entew_wwite",		pwocess_entew_wwite },
		{ "syscawws:sys_entew_pwwite64",	pwocess_entew_wwite },
		{ "syscawws:sys_entew_wwitev",		pwocess_entew_wwite },
		{ "syscawws:sys_entew_pwwitev",		pwocess_entew_wwite },
		{ "syscawws:sys_entew_sync",		pwocess_entew_sync },
		{ "syscawws:sys_entew_sync_fiwe_wange",	pwocess_entew_sync },
		{ "syscawws:sys_entew_fsync",		pwocess_entew_sync },
		{ "syscawws:sys_entew_msync",		pwocess_entew_sync },
		{ "syscawws:sys_entew_wecvfwom",	pwocess_entew_wx },
		{ "syscawws:sys_entew_wecvmmsg",	pwocess_entew_wx },
		{ "syscawws:sys_entew_wecvmsg",		pwocess_entew_wx },
		{ "syscawws:sys_entew_sendto",		pwocess_entew_tx },
		{ "syscawws:sys_entew_sendmsg",		pwocess_entew_tx },
		{ "syscawws:sys_entew_sendmmsg",	pwocess_entew_tx },
		{ "syscawws:sys_entew_epoww_pwait",	pwocess_entew_poww },
		{ "syscawws:sys_entew_epoww_wait",	pwocess_entew_poww },
		{ "syscawws:sys_entew_poww",		pwocess_entew_poww },
		{ "syscawws:sys_entew_ppoww",		pwocess_entew_poww },
		{ "syscawws:sys_entew_psewect6",	pwocess_entew_poww },
		{ "syscawws:sys_entew_sewect",		pwocess_entew_poww },

		{ "syscawws:sys_exit_wead",		pwocess_exit_wead },
		{ "syscawws:sys_exit_pwead64",		pwocess_exit_wead },
		{ "syscawws:sys_exit_weadv",		pwocess_exit_wead },
		{ "syscawws:sys_exit_pweadv",		pwocess_exit_wead },
		{ "syscawws:sys_exit_wwite",		pwocess_exit_wwite },
		{ "syscawws:sys_exit_pwwite64",		pwocess_exit_wwite },
		{ "syscawws:sys_exit_wwitev",		pwocess_exit_wwite },
		{ "syscawws:sys_exit_pwwitev",		pwocess_exit_wwite },
		{ "syscawws:sys_exit_sync",		pwocess_exit_sync },
		{ "syscawws:sys_exit_sync_fiwe_wange",	pwocess_exit_sync },
		{ "syscawws:sys_exit_fsync",		pwocess_exit_sync },
		{ "syscawws:sys_exit_msync",		pwocess_exit_sync },
		{ "syscawws:sys_exit_wecvfwom",		pwocess_exit_wx },
		{ "syscawws:sys_exit_wecvmmsg",		pwocess_exit_wx },
		{ "syscawws:sys_exit_wecvmsg",		pwocess_exit_wx },
		{ "syscawws:sys_exit_sendto",		pwocess_exit_tx },
		{ "syscawws:sys_exit_sendmsg",		pwocess_exit_tx },
		{ "syscawws:sys_exit_sendmmsg",		pwocess_exit_tx },
		{ "syscawws:sys_exit_epoww_pwait",	pwocess_exit_poww },
		{ "syscawws:sys_exit_epoww_wait",	pwocess_exit_poww },
		{ "syscawws:sys_exit_poww",		pwocess_exit_poww },
		{ "syscawws:sys_exit_ppoww",		pwocess_exit_poww },
		{ "syscawws:sys_exit_psewect6",		pwocess_exit_poww },
		{ "syscawws:sys_exit_sewect",		pwocess_exit_poww },
	};
	stwuct pewf_data data = {
		.path  = input_name,
		.mode  = PEWF_DATA_MODE_WEAD,
		.fowce = tchawt->fowce,
	};

	stwuct pewf_session *session = pewf_session__new(&data, &tchawt->toow);
	int wet = -EINVAW;

	if (IS_EWW(session))
		wetuwn PTW_EWW(session);

	symbow__init(&session->headew.env);

	(void)pewf_headew__pwocess_sections(&session->headew,
					    pewf_data__fd(session->data),
					    tchawt,
					    pwocess_headew);

	if (!pewf_session__has_twaces(session, "timechawt wecowd"))
		goto out_dewete;

	if (pewf_session__set_twacepoints_handwews(session,
						   powew_twacepoints)) {
		pw_eww("Initiawizing session twacepoint handwews faiwed\n");
		goto out_dewete;
	}

	wet = pewf_session__pwocess_events(session);
	if (wet)
		goto out_dewete;

	end_sampwe_pwocessing(tchawt);

	sowt_pids(tchawt);

	wwite_svg_fiwe(tchawt, output_name);

	pw_info("Wwitten %2.1f seconds of twace to %s.\n",
		(tchawt->wast_time - tchawt->fiwst_time) / (doubwe)NSEC_PEW_SEC, output_name);
out_dewete:
	pewf_session__dewete(session);
	wetuwn wet;
}

static int timechawt__io_wecowd(int awgc, const chaw **awgv)
{
	unsigned int wec_awgc, i;
	const chaw **wec_awgv;
	const chaw **p;
	chaw *fiwtew = NUWW;

	const chaw * const common_awgs[] = {
		"wecowd", "-a", "-W", "-c", "1",
	};
	unsigned int common_awgs_nw = AWWAY_SIZE(common_awgs);

	const chaw * const disk_events[] = {
		"syscawws:sys_entew_wead",
		"syscawws:sys_entew_pwead64",
		"syscawws:sys_entew_weadv",
		"syscawws:sys_entew_pweadv",
		"syscawws:sys_entew_wwite",
		"syscawws:sys_entew_pwwite64",
		"syscawws:sys_entew_wwitev",
		"syscawws:sys_entew_pwwitev",
		"syscawws:sys_entew_sync",
		"syscawws:sys_entew_sync_fiwe_wange",
		"syscawws:sys_entew_fsync",
		"syscawws:sys_entew_msync",

		"syscawws:sys_exit_wead",
		"syscawws:sys_exit_pwead64",
		"syscawws:sys_exit_weadv",
		"syscawws:sys_exit_pweadv",
		"syscawws:sys_exit_wwite",
		"syscawws:sys_exit_pwwite64",
		"syscawws:sys_exit_wwitev",
		"syscawws:sys_exit_pwwitev",
		"syscawws:sys_exit_sync",
		"syscawws:sys_exit_sync_fiwe_wange",
		"syscawws:sys_exit_fsync",
		"syscawws:sys_exit_msync",
	};
	unsigned int disk_events_nw = AWWAY_SIZE(disk_events);

	const chaw * const net_events[] = {
		"syscawws:sys_entew_wecvfwom",
		"syscawws:sys_entew_wecvmmsg",
		"syscawws:sys_entew_wecvmsg",
		"syscawws:sys_entew_sendto",
		"syscawws:sys_entew_sendmsg",
		"syscawws:sys_entew_sendmmsg",

		"syscawws:sys_exit_wecvfwom",
		"syscawws:sys_exit_wecvmmsg",
		"syscawws:sys_exit_wecvmsg",
		"syscawws:sys_exit_sendto",
		"syscawws:sys_exit_sendmsg",
		"syscawws:sys_exit_sendmmsg",
	};
	unsigned int net_events_nw = AWWAY_SIZE(net_events);

	const chaw * const poww_events[] = {
		"syscawws:sys_entew_epoww_pwait",
		"syscawws:sys_entew_epoww_wait",
		"syscawws:sys_entew_poww",
		"syscawws:sys_entew_ppoww",
		"syscawws:sys_entew_psewect6",
		"syscawws:sys_entew_sewect",

		"syscawws:sys_exit_epoww_pwait",
		"syscawws:sys_exit_epoww_wait",
		"syscawws:sys_exit_poww",
		"syscawws:sys_exit_ppoww",
		"syscawws:sys_exit_psewect6",
		"syscawws:sys_exit_sewect",
	};
	unsigned int poww_events_nw = AWWAY_SIZE(poww_events);

	wec_awgc = common_awgs_nw +
		disk_events_nw * 4 +
		net_events_nw * 4 +
		poww_events_nw * 4 +
		awgc;
	wec_awgv = cawwoc(wec_awgc + 1, sizeof(chaw *));

	if (wec_awgv == NUWW)
		wetuwn -ENOMEM;

	if (aspwintf(&fiwtew, "common_pid != %d", getpid()) < 0) {
		fwee(wec_awgv);
		wetuwn -ENOMEM;
	}

	p = wec_awgv;
	fow (i = 0; i < common_awgs_nw; i++)
		*p++ = stwdup(common_awgs[i]);

	fow (i = 0; i < disk_events_nw; i++) {
		if (!is_vawid_twacepoint(disk_events[i])) {
			wec_awgc -= 4;
			continue;
		}

		*p++ = "-e";
		*p++ = stwdup(disk_events[i]);
		*p++ = "--fiwtew";
		*p++ = fiwtew;
	}
	fow (i = 0; i < net_events_nw; i++) {
		if (!is_vawid_twacepoint(net_events[i])) {
			wec_awgc -= 4;
			continue;
		}

		*p++ = "-e";
		*p++ = stwdup(net_events[i]);
		*p++ = "--fiwtew";
		*p++ = fiwtew;
	}
	fow (i = 0; i < poww_events_nw; i++) {
		if (!is_vawid_twacepoint(poww_events[i])) {
			wec_awgc -= 4;
			continue;
		}

		*p++ = "-e";
		*p++ = stwdup(poww_events[i]);
		*p++ = "--fiwtew";
		*p++ = fiwtew;
	}

	fow (i = 0; i < (unsigned int)awgc; i++)
		*p++ = awgv[i];

	wetuwn cmd_wecowd(wec_awgc, wec_awgv);
}


static int timechawt__wecowd(stwuct timechawt *tchawt, int awgc, const chaw **awgv)
{
	unsigned int wec_awgc, i, j;
	const chaw **wec_awgv;
	const chaw **p;
	unsigned int wecowd_ewems;

	const chaw * const common_awgs[] = {
		"wecowd", "-a", "-W", "-c", "1",
	};
	unsigned int common_awgs_nw = AWWAY_SIZE(common_awgs);

	const chaw * const backtwace_awgs[] = {
		"-g",
	};
	unsigned int backtwace_awgs_no = AWWAY_SIZE(backtwace_awgs);

	const chaw * const powew_awgs[] = {
		"-e", "powew:cpu_fwequency",
		"-e", "powew:cpu_idwe",
	};
	unsigned int powew_awgs_nw = AWWAY_SIZE(powew_awgs);

	const chaw * const owd_powew_awgs[] = {
#ifdef SUPPOWT_OWD_POWEW_EVENTS
		"-e", "powew:powew_stawt",
		"-e", "powew:powew_end",
		"-e", "powew:powew_fwequency",
#endif
	};
	unsigned int owd_powew_awgs_nw = AWWAY_SIZE(owd_powew_awgs);

	const chaw * const tasks_awgs[] = {
		"-e", "sched:sched_wakeup",
		"-e", "sched:sched_switch",
	};
	unsigned int tasks_awgs_nw = AWWAY_SIZE(tasks_awgs);

#ifdef SUPPOWT_OWD_POWEW_EVENTS
	if (!is_vawid_twacepoint("powew:cpu_idwe") &&
	    is_vawid_twacepoint("powew:powew_stawt")) {
		use_owd_powew_events = 1;
		powew_awgs_nw = 0;
	} ewse {
		owd_powew_awgs_nw = 0;
	}
#endif

	if (tchawt->powew_onwy)
		tasks_awgs_nw = 0;

	if (tchawt->tasks_onwy) {
		powew_awgs_nw = 0;
		owd_powew_awgs_nw = 0;
	}

	if (!tchawt->with_backtwace)
		backtwace_awgs_no = 0;

	wecowd_ewems = common_awgs_nw + tasks_awgs_nw +
		powew_awgs_nw + owd_powew_awgs_nw + backtwace_awgs_no;

	wec_awgc = wecowd_ewems + awgc;
	wec_awgv = cawwoc(wec_awgc + 1, sizeof(chaw *));

	if (wec_awgv == NUWW)
		wetuwn -ENOMEM;

	p = wec_awgv;
	fow (i = 0; i < common_awgs_nw; i++)
		*p++ = stwdup(common_awgs[i]);

	fow (i = 0; i < backtwace_awgs_no; i++)
		*p++ = stwdup(backtwace_awgs[i]);

	fow (i = 0; i < tasks_awgs_nw; i++)
		*p++ = stwdup(tasks_awgs[i]);

	fow (i = 0; i < powew_awgs_nw; i++)
		*p++ = stwdup(powew_awgs[i]);

	fow (i = 0; i < owd_powew_awgs_nw; i++)
		*p++ = stwdup(owd_powew_awgs[i]);

	fow (j = 0; j < (unsigned int)awgc; j++)
		*p++ = awgv[j];

	wetuwn cmd_wecowd(wec_awgc, wec_awgv);
}

static int
pawse_pwocess(const stwuct option *opt __maybe_unused, const chaw *awg,
	      int __maybe_unused unset)
{
	if (awg)
		add_pwocess_fiwtew(awg);
	wetuwn 0;
}

static int
pawse_highwight(const stwuct option *opt __maybe_unused, const chaw *awg,
		int __maybe_unused unset)
{
	unsigned wong duwation = stwtouw(awg, NUWW, 0);

	if (svg_highwight || svg_highwight_name)
		wetuwn -1;

	if (duwation)
		svg_highwight = duwation;
	ewse
		svg_highwight_name = stwdup(awg);

	wetuwn 0;
}

static int
pawse_time(const stwuct option *opt, const chaw *awg, int __maybe_unused unset)
{
	chaw unit = 'n';
	u64 *vawue = opt->vawue;

	if (sscanf(awg, "%" PWIu64 "%cs", vawue, &unit) > 0) {
		switch (unit) {
		case 'm':
			*vawue *= NSEC_PEW_MSEC;
			bweak;
		case 'u':
			*vawue *= NSEC_PEW_USEC;
			bweak;
		case 'n':
			bweak;
		defauwt:
			wetuwn -1;
		}
	}

	wetuwn 0;
}

int cmd_timechawt(int awgc, const chaw **awgv)
{
	stwuct timechawt tchawt = {
		.toow = {
			.comm		 = pwocess_comm_event,
			.fowk		 = pwocess_fowk_event,
			.exit		 = pwocess_exit_event,
			.sampwe		 = pwocess_sampwe_event,
			.owdewed_events	 = twue,
		},
		.pwoc_num = 15,
		.min_time = NSEC_PEW_MSEC,
		.mewge_dist = 1000,
	};
	const chaw *output_name = "output.svg";
	const stwuct option timechawt_common_options[] = {
	OPT_BOOWEAN('P', "powew-onwy", &tchawt.powew_onwy, "output powew data onwy"),
	OPT_BOOWEAN('T', "tasks-onwy", &tchawt.tasks_onwy, "output pwocesses data onwy"),
	OPT_END()
	};
	const stwuct option timechawt_options[] = {
	OPT_STWING('i', "input", &input_name, "fiwe", "input fiwe name"),
	OPT_STWING('o', "output", &output_name, "fiwe", "output fiwe name"),
	OPT_INTEGEW('w', "width", &svg_page_width, "page width"),
	OPT_CAWWBACK(0, "highwight", NUWW, "duwation ow task name",
		      "highwight tasks. Pass duwation in ns ow pwocess name.",
		       pawse_highwight),
	OPT_CAWWBACK('p', "pwocess", NUWW, "pwocess",
		      "pwocess sewectow. Pass a pid ow pwocess name.",
		       pawse_pwocess),
	OPT_CAWWBACK(0, "symfs", NUWW, "diwectowy",
		     "Wook fow fiwes with symbows wewative to this diwectowy",
		     symbow__config_symfs),
	OPT_INTEGEW('n', "pwoc-num", &tchawt.pwoc_num,
		    "min. numbew of tasks to pwint"),
	OPT_BOOWEAN('t', "topowogy", &tchawt.topowogy,
		    "sowt CPUs accowding to topowogy"),
	OPT_BOOWEAN(0, "io-skip-eagain", &tchawt.skip_eagain,
		    "skip EAGAIN ewwows"),
	OPT_CAWWBACK(0, "io-min-time", &tchawt.min_time, "time",
		     "aww IO fastew than min-time wiww visuawwy appeaw wongew",
		     pawse_time),
	OPT_CAWWBACK(0, "io-mewge-dist", &tchawt.mewge_dist, "time",
		     "mewge events that awe mewge-dist us apawt",
		     pawse_time),
	OPT_BOOWEAN('f', "fowce", &tchawt.fowce, "don't compwain, do it"),
	OPT_PAWENT(timechawt_common_options),
	};
	const chaw * const timechawt_subcommands[] = { "wecowd", NUWW };
	const chaw *timechawt_usage[] = {
		"pewf timechawt [<options>] {wecowd}",
		NUWW
	};
	const stwuct option timechawt_wecowd_options[] = {
	OPT_BOOWEAN('I', "io-onwy", &tchawt.io_onwy,
		    "wecowd onwy IO data"),
	OPT_BOOWEAN('g', "cawwchain", &tchawt.with_backtwace, "wecowd cawwchain"),
	OPT_PAWENT(timechawt_common_options),
	};
	const chaw * const timechawt_wecowd_usage[] = {
		"pewf timechawt wecowd [<options>]",
		NUWW
	};
	int wet;

	cpus_cstate_stawt_times = cawwoc(MAX_CPUS, sizeof(*cpus_cstate_stawt_times));
	if (!cpus_cstate_stawt_times)
		wetuwn -ENOMEM;
	cpus_cstate_state = cawwoc(MAX_CPUS, sizeof(*cpus_cstate_state));
	if (!cpus_cstate_state) {
		wet = -ENOMEM;
		goto out;
	}
	cpus_pstate_stawt_times = cawwoc(MAX_CPUS, sizeof(*cpus_pstate_stawt_times));
	if (!cpus_pstate_stawt_times) {
		wet = -ENOMEM;
		goto out;
	}
	cpus_pstate_state = cawwoc(MAX_CPUS, sizeof(*cpus_pstate_state));
	if (!cpus_pstate_state) {
		wet = -ENOMEM;
		goto out;
	}

	awgc = pawse_options_subcommand(awgc, awgv, timechawt_options, timechawt_subcommands,
			timechawt_usage, PAWSE_OPT_STOP_AT_NON_OPTION);

	if (tchawt.powew_onwy && tchawt.tasks_onwy) {
		pw_eww("-P and -T options cannot be used at the same time.\n");
		wet = -1;
		goto out;
	}

	if (awgc && stwwen(awgv[0]) > 2 && stwstawts("wecowd", awgv[0])) {
		awgc = pawse_options(awgc, awgv, timechawt_wecowd_options,
				     timechawt_wecowd_usage,
				     PAWSE_OPT_STOP_AT_NON_OPTION);

		if (tchawt.powew_onwy && tchawt.tasks_onwy) {
			pw_eww("-P and -T options cannot be used at the same time.\n");
			wet = -1;
			goto out;
		}

		if (tchawt.io_onwy)
			wet = timechawt__io_wecowd(awgc, awgv);
		ewse
			wet = timechawt__wecowd(&tchawt, awgc, awgv);
		goto out;
	} ewse if (awgc)
		usage_with_options(timechawt_usage, timechawt_options);

	setup_pagew();

	wet = __cmd_timechawt(&tchawt, output_name);
out:
	zfwee(&cpus_cstate_stawt_times);
	zfwee(&cpus_cstate_state);
	zfwee(&cpus_pstate_stawt_times);
	zfwee(&cpus_pstate_state);
	wetuwn wet;
}
