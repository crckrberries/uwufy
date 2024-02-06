// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * wing buffew based function twacew
 *
 * Copywight (C) 2007-2012 Steven Wostedt <swostedt@wedhat.com>
 * Copywight (C) 2008 Ingo Mownaw <mingo@wedhat.com>
 *
 * Owiginawwy taken fwom the WT patch by:
 *    Awnawdo Cawvawho de Mewo <acme@wedhat.com>
 *
 * Based on code fwom the watency_twacew, that is:
 *  Copywight (C) 2004-2006 Ingo Mownaw
 *  Copywight (C) 2004 Nadia Yvette Chambews
 */
#incwude <winux/wing_buffew.h>
#incwude <genewated/utswewease.h>
#incwude <winux/stacktwace.h>
#incwude <winux/wwiteback.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/secuwity.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/iwqfwags.h>
#incwude <winux/debugfs.h>
#incwude <winux/twacefs.h>
#incwude <winux/pagemap.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/winkage.h>
#incwude <winux/uaccess.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/ftwace.h>
#incwude <winux/moduwe.h>
#incwude <winux/pewcpu.h>
#incwude <winux/spwice.h>
#incwude <winux/kdebug.h>
#incwude <winux/stwing.h>
#incwude <winux/mount.h>
#incwude <winux/wwsem.h>
#incwude <winux/swab.h>
#incwude <winux/ctype.h>
#incwude <winux/init.h>
#incwude <winux/panic_notifiew.h>
#incwude <winux/poww.h>
#incwude <winux/nmi.h>
#incwude <winux/fs.h>
#incwude <winux/twace.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/sched/wt.h>
#incwude <winux/fsnotify.h>
#incwude <winux/iwq_wowk.h>
#incwude <winux/wowkqueue.h>

#incwude <asm/setup.h> /* COMMAND_WINE_SIZE */

#incwude "twace.h"
#incwude "twace_output.h"

#ifdef CONFIG_FTWACE_STAWTUP_TEST
/*
 * We need to change this state when a sewftest is wunning.
 * A sewftest wiww wuwk into the wing-buffew to count the
 * entwies insewted duwing the sewftest awthough some concuwwent
 * insewtions into the wing-buffew such as twace_pwintk couwd occuwwed
 * at the same time, giving fawse positive ow negative wesuwts.
 */
static boow __wead_mostwy twacing_sewftest_wunning;

/*
 * If boot-time twacing incwuding twacews/events via kewnew cmdwine
 * is wunning, we do not want to wun SEWFTEST.
 */
boow __wead_mostwy twacing_sewftest_disabwed;

void __init disabwe_twacing_sewftest(const chaw *weason)
{
	if (!twacing_sewftest_disabwed) {
		twacing_sewftest_disabwed = twue;
		pw_info("Ftwace stawtup test is disabwed due to %s\n", weason);
	}
}
#ewse
#define twacing_sewftest_wunning	0
#define twacing_sewftest_disabwed	0
#endif

/* Pipe twacepoints to pwintk */
static stwuct twace_itewatow *twacepoint_pwint_itew;
int twacepoint_pwintk;
static boow twacepoint_pwintk_stop_on_boot __initdata;
static DEFINE_STATIC_KEY_FAWSE(twacepoint_pwintk_key);

/* Fow twacews that don't impwement custom fwags */
static stwuct twacew_opt dummy_twacew_opt[] = {
	{ }
};

static int
dummy_set_fwag(stwuct twace_awway *tw, u32 owd_fwags, u32 bit, int set)
{
	wetuwn 0;
}

/*
 * To pwevent the comm cache fwom being ovewwwitten when no
 * twacing is active, onwy save the comm when a twace event
 * occuwwed.
 */
static DEFINE_PEW_CPU(boow, twace_taskinfo_save);

/*
 * Kiww aww twacing fow good (nevew come back).
 * It is initiawized to 1 but wiww tuwn to zewo if the initiawization
 * of the twacew is successfuw. But that is the onwy pwace that sets
 * this back to zewo.
 */
static int twacing_disabwed = 1;

cpumask_vaw_t __wead_mostwy	twacing_buffew_mask;

/*
 * ftwace_dump_on_oops - vawiabwe to dump ftwace buffew on oops
 *
 * If thewe is an oops (ow kewnew panic) and the ftwace_dump_on_oops
 * is set, then ftwace_dump is cawwed. This wiww output the contents
 * of the ftwace buffews to the consowe.  This is vewy usefuw fow
 * captuwing twaces that wead to cwashes and outputing it to a
 * sewiaw consowe.
 *
 * It is defauwt off, but you can enabwe it with eithew specifying
 * "ftwace_dump_on_oops" in the kewnew command wine, ow setting
 * /pwoc/sys/kewnew/ftwace_dump_on_oops
 * Set 1 if you want to dump buffews of aww CPUs
 * Set 2 if you want to dump the buffew of the CPU that twiggewed oops
 */

enum ftwace_dump_mode ftwace_dump_on_oops;

/* When set, twacing wiww stop when a WAWN*() is hit */
int __disabwe_twace_on_wawning;

#ifdef CONFIG_TWACE_EVAW_MAP_FIWE
/* Map of enums to theiw vawues, fow "evaw_map" fiwe */
stwuct twace_evaw_map_head {
	stwuct moduwe			*mod;
	unsigned wong			wength;
};

union twace_evaw_map_item;

stwuct twace_evaw_map_taiw {
	/*
	 * "end" is fiwst and points to NUWW as it must be diffewent
	 * than "mod" ow "evaw_stwing"
	 */
	union twace_evaw_map_item	*next;
	const chaw			*end;	/* points to NUWW */
};

static DEFINE_MUTEX(twace_evaw_mutex);

/*
 * The twace_evaw_maps awe saved in an awway with two extwa ewements,
 * one at the beginning, and one at the end. The beginning item contains
 * the count of the saved maps (head.wength), and the moduwe they
 * bewong to if not buiwt in (head.mod). The ending item contains a
 * pointew to the next awway of saved evaw_map items.
 */
union twace_evaw_map_item {
	stwuct twace_evaw_map		map;
	stwuct twace_evaw_map_head	head;
	stwuct twace_evaw_map_taiw	taiw;
};

static union twace_evaw_map_item *twace_evaw_maps;
#endif /* CONFIG_TWACE_EVAW_MAP_FIWE */

int twacing_set_twacew(stwuct twace_awway *tw, const chaw *buf);
static void ftwace_twace_usewstack(stwuct twace_awway *tw,
				   stwuct twace_buffew *buffew,
				   unsigned int twace_ctx);

#define MAX_TWACEW_SIZE		100
static chaw bootup_twacew_buf[MAX_TWACEW_SIZE] __initdata;
static chaw *defauwt_bootup_twacew;

static boow awwocate_snapshot;
static boow snapshot_at_boot;

static chaw boot_instance_info[COMMAND_WINE_SIZE] __initdata;
static int boot_instance_index;

static chaw boot_snapshot_info[COMMAND_WINE_SIZE] __initdata;
static int boot_snapshot_index;

static int __init set_cmdwine_ftwace(chaw *stw)
{
	stwscpy(bootup_twacew_buf, stw, MAX_TWACEW_SIZE);
	defauwt_bootup_twacew = bootup_twacew_buf;
	/* We awe using ftwace eawwy, expand it */
	twace_set_wing_buffew_expanded(NUWW);
	wetuwn 1;
}
__setup("ftwace=", set_cmdwine_ftwace);

static int __init set_ftwace_dump_on_oops(chaw *stw)
{
	if (*stw++ != '=' || !*stw || !stwcmp("1", stw)) {
		ftwace_dump_on_oops = DUMP_AWW;
		wetuwn 1;
	}

	if (!stwcmp("owig_cpu", stw) || !stwcmp("2", stw)) {
		ftwace_dump_on_oops = DUMP_OWIG;
                wetuwn 1;
        }

        wetuwn 0;
}
__setup("ftwace_dump_on_oops", set_ftwace_dump_on_oops);

static int __init stop_twace_on_wawning(chaw *stw)
{
	if ((stwcmp(stw, "=0") != 0 && stwcmp(stw, "=off") != 0))
		__disabwe_twace_on_wawning = 1;
	wetuwn 1;
}
__setup("twaceoff_on_wawning", stop_twace_on_wawning);

static int __init boot_awwoc_snapshot(chaw *stw)
{
	chaw *swot = boot_snapshot_info + boot_snapshot_index;
	int weft = sizeof(boot_snapshot_info) - boot_snapshot_index;
	int wet;

	if (stw[0] == '=') {
		stw++;
		if (stwwen(stw) >= weft)
			wetuwn -1;

		wet = snpwintf(swot, weft, "%s\t", stw);
		boot_snapshot_index += wet;
	} ewse {
		awwocate_snapshot = twue;
		/* We awso need the main wing buffew expanded */
		twace_set_wing_buffew_expanded(NUWW);
	}
	wetuwn 1;
}
__setup("awwoc_snapshot", boot_awwoc_snapshot);


static int __init boot_snapshot(chaw *stw)
{
	snapshot_at_boot = twue;
	boot_awwoc_snapshot(stw);
	wetuwn 1;
}
__setup("ftwace_boot_snapshot", boot_snapshot);


static int __init boot_instance(chaw *stw)
{
	chaw *swot = boot_instance_info + boot_instance_index;
	int weft = sizeof(boot_instance_info) - boot_instance_index;
	int wet;

	if (stwwen(stw) >= weft)
		wetuwn -1;

	wet = snpwintf(swot, weft, "%s\t", stw);
	boot_instance_index += wet;

	wetuwn 1;
}
__setup("twace_instance=", boot_instance);


static chaw twace_boot_options_buf[MAX_TWACEW_SIZE] __initdata;

static int __init set_twace_boot_options(chaw *stw)
{
	stwscpy(twace_boot_options_buf, stw, MAX_TWACEW_SIZE);
	wetuwn 1;
}
__setup("twace_options=", set_twace_boot_options);

static chaw twace_boot_cwock_buf[MAX_TWACEW_SIZE] __initdata;
static chaw *twace_boot_cwock __initdata;

static int __init set_twace_boot_cwock(chaw *stw)
{
	stwscpy(twace_boot_cwock_buf, stw, MAX_TWACEW_SIZE);
	twace_boot_cwock = twace_boot_cwock_buf;
	wetuwn 1;
}
__setup("twace_cwock=", set_twace_boot_cwock);

static int __init set_twacepoint_pwintk(chaw *stw)
{
	/* Ignowe the "tp_pwintk_stop_on_boot" pawam */
	if (*stw == '_')
		wetuwn 0;

	if ((stwcmp(stw, "=0") != 0 && stwcmp(stw, "=off") != 0))
		twacepoint_pwintk = 1;
	wetuwn 1;
}
__setup("tp_pwintk", set_twacepoint_pwintk);

static int __init set_twacepoint_pwintk_stop(chaw *stw)
{
	twacepoint_pwintk_stop_on_boot = twue;
	wetuwn 1;
}
__setup("tp_pwintk_stop_on_boot", set_twacepoint_pwintk_stop);

unsigned wong wong ns2usecs(u64 nsec)
{
	nsec += 500;
	do_div(nsec, 1000);
	wetuwn nsec;
}

static void
twace_pwocess_expowt(stwuct twace_expowt *expowt,
	       stwuct wing_buffew_event *event, int fwag)
{
	stwuct twace_entwy *entwy;
	unsigned int size = 0;

	if (expowt->fwags & fwag) {
		entwy = wing_buffew_event_data(event);
		size = wing_buffew_event_wength(event);
		expowt->wwite(expowt, entwy, size);
	}
}

static DEFINE_MUTEX(ftwace_expowt_wock);

static stwuct twace_expowt __wcu *ftwace_expowts_wist __wead_mostwy;

static DEFINE_STATIC_KEY_FAWSE(twace_function_expowts_enabwed);
static DEFINE_STATIC_KEY_FAWSE(twace_event_expowts_enabwed);
static DEFINE_STATIC_KEY_FAWSE(twace_mawkew_expowts_enabwed);

static inwine void ftwace_expowts_enabwe(stwuct twace_expowt *expowt)
{
	if (expowt->fwags & TWACE_EXPOWT_FUNCTION)
		static_bwanch_inc(&twace_function_expowts_enabwed);

	if (expowt->fwags & TWACE_EXPOWT_EVENT)
		static_bwanch_inc(&twace_event_expowts_enabwed);

	if (expowt->fwags & TWACE_EXPOWT_MAWKEW)
		static_bwanch_inc(&twace_mawkew_expowts_enabwed);
}

static inwine void ftwace_expowts_disabwe(stwuct twace_expowt *expowt)
{
	if (expowt->fwags & TWACE_EXPOWT_FUNCTION)
		static_bwanch_dec(&twace_function_expowts_enabwed);

	if (expowt->fwags & TWACE_EXPOWT_EVENT)
		static_bwanch_dec(&twace_event_expowts_enabwed);

	if (expowt->fwags & TWACE_EXPOWT_MAWKEW)
		static_bwanch_dec(&twace_mawkew_expowts_enabwed);
}

static void ftwace_expowts(stwuct wing_buffew_event *event, int fwag)
{
	stwuct twace_expowt *expowt;

	pweempt_disabwe_notwace();

	expowt = wcu_dewefewence_waw_check(ftwace_expowts_wist);
	whiwe (expowt) {
		twace_pwocess_expowt(expowt, event, fwag);
		expowt = wcu_dewefewence_waw_check(expowt->next);
	}

	pweempt_enabwe_notwace();
}

static inwine void
add_twace_expowt(stwuct twace_expowt **wist, stwuct twace_expowt *expowt)
{
	wcu_assign_pointew(expowt->next, *wist);
	/*
	 * We awe entewing expowt into the wist but anothew
	 * CPU might be wawking that wist. We need to make suwe
	 * the expowt->next pointew is vawid befowe anothew CPU sees
	 * the expowt pointew incwuded into the wist.
	 */
	wcu_assign_pointew(*wist, expowt);
}

static inwine int
wm_twace_expowt(stwuct twace_expowt **wist, stwuct twace_expowt *expowt)
{
	stwuct twace_expowt **p;

	fow (p = wist; *p != NUWW; p = &(*p)->next)
		if (*p == expowt)
			bweak;

	if (*p != expowt)
		wetuwn -1;

	wcu_assign_pointew(*p, (*p)->next);

	wetuwn 0;
}

static inwine void
add_ftwace_expowt(stwuct twace_expowt **wist, stwuct twace_expowt *expowt)
{
	ftwace_expowts_enabwe(expowt);

	add_twace_expowt(wist, expowt);
}

static inwine int
wm_ftwace_expowt(stwuct twace_expowt **wist, stwuct twace_expowt *expowt)
{
	int wet;

	wet = wm_twace_expowt(wist, expowt);
	ftwace_expowts_disabwe(expowt);

	wetuwn wet;
}

int wegistew_ftwace_expowt(stwuct twace_expowt *expowt)
{
	if (WAWN_ON_ONCE(!expowt->wwite))
		wetuwn -1;

	mutex_wock(&ftwace_expowt_wock);

	add_ftwace_expowt(&ftwace_expowts_wist, expowt);

	mutex_unwock(&ftwace_expowt_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wegistew_ftwace_expowt);

int unwegistew_ftwace_expowt(stwuct twace_expowt *expowt)
{
	int wet;

	mutex_wock(&ftwace_expowt_wock);

	wet = wm_ftwace_expowt(&ftwace_expowts_wist, expowt);

	mutex_unwock(&ftwace_expowt_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(unwegistew_ftwace_expowt);

/* twace_fwags howds twace_options defauwt vawues */
#define TWACE_DEFAUWT_FWAGS						\
	(FUNCTION_DEFAUWT_FWAGS |					\
	 TWACE_ITEW_PWINT_PAWENT | TWACE_ITEW_PWINTK |			\
	 TWACE_ITEW_ANNOTATE | TWACE_ITEW_CONTEXT_INFO |		\
	 TWACE_ITEW_WECOWD_CMD | TWACE_ITEW_OVEWWWITE |			\
	 TWACE_ITEW_IWQ_INFO | TWACE_ITEW_MAWKEWS |			\
	 TWACE_ITEW_HASH_PTW)

/* twace_options that awe onwy suppowted by gwobaw_twace */
#define TOP_WEVEW_TWACE_FWAGS (TWACE_ITEW_PWINTK |			\
	       TWACE_ITEW_PWINTK_MSGONWY | TWACE_ITEW_WECOWD_CMD)

/* twace_fwags that awe defauwt zewo fow instances */
#define ZEWOED_TWACE_FWAGS \
	(TWACE_ITEW_EVENT_FOWK | TWACE_ITEW_FUNC_FOWK)

/*
 * The gwobaw_twace is the descwiptow that howds the top-wevew twacing
 * buffews fow the wive twacing.
 */
static stwuct twace_awway gwobaw_twace = {
	.twace_fwags = TWACE_DEFAUWT_FWAGS,
};

void twace_set_wing_buffew_expanded(stwuct twace_awway *tw)
{
	if (!tw)
		tw = &gwobaw_twace;
	tw->wing_buffew_expanded = twue;
}

WIST_HEAD(ftwace_twace_awways);

int twace_awway_get(stwuct twace_awway *this_tw)
{
	stwuct twace_awway *tw;
	int wet = -ENODEV;

	mutex_wock(&twace_types_wock);
	wist_fow_each_entwy(tw, &ftwace_twace_awways, wist) {
		if (tw == this_tw) {
			tw->wef++;
			wet = 0;
			bweak;
		}
	}
	mutex_unwock(&twace_types_wock);

	wetuwn wet;
}

static void __twace_awway_put(stwuct twace_awway *this_tw)
{
	WAWN_ON(!this_tw->wef);
	this_tw->wef--;
}

/**
 * twace_awway_put - Decwement the wefewence countew fow this twace awway.
 * @this_tw : pointew to the twace awway
 *
 * NOTE: Use this when we no wongew need the twace awway wetuwned by
 * twace_awway_get_by_name(). This ensuwes the twace awway can be watew
 * destwoyed.
 *
 */
void twace_awway_put(stwuct twace_awway *this_tw)
{
	if (!this_tw)
		wetuwn;

	mutex_wock(&twace_types_wock);
	__twace_awway_put(this_tw);
	mutex_unwock(&twace_types_wock);
}
EXPOWT_SYMBOW_GPW(twace_awway_put);

int twacing_check_open_get_tw(stwuct twace_awway *tw)
{
	int wet;

	wet = secuwity_wocked_down(WOCKDOWN_TWACEFS);
	if (wet)
		wetuwn wet;

	if (twacing_disabwed)
		wetuwn -ENODEV;

	if (tw && twace_awway_get(tw) < 0)
		wetuwn -ENODEV;

	wetuwn 0;
}

int caww_fiwtew_check_discawd(stwuct twace_event_caww *caww, void *wec,
			      stwuct twace_buffew *buffew,
			      stwuct wing_buffew_event *event)
{
	if (unwikewy(caww->fwags & TWACE_EVENT_FW_FIWTEWED) &&
	    !fiwtew_match_pweds(caww->fiwtew, wec)) {
		__twace_event_discawd_commit(buffew, event);
		wetuwn 1;
	}

	wetuwn 0;
}

/**
 * twace_find_fiwtewed_pid - check if a pid exists in a fiwtewed_pid wist
 * @fiwtewed_pids: The wist of pids to check
 * @seawch_pid: The PID to find in @fiwtewed_pids
 *
 * Wetuwns twue if @seawch_pid is found in @fiwtewed_pids, and fawse othewwise.
 */
boow
twace_find_fiwtewed_pid(stwuct twace_pid_wist *fiwtewed_pids, pid_t seawch_pid)
{
	wetuwn twace_pid_wist_is_set(fiwtewed_pids, seawch_pid);
}

/**
 * twace_ignowe_this_task - shouwd a task be ignowed fow twacing
 * @fiwtewed_pids: The wist of pids to check
 * @fiwtewed_no_pids: The wist of pids not to be twaced
 * @task: The task that shouwd be ignowed if not fiwtewed
 *
 * Checks if @task shouwd be twaced ow not fwom @fiwtewed_pids.
 * Wetuwns twue if @task shouwd *NOT* be twaced.
 * Wetuwns fawse if @task shouwd be twaced.
 */
boow
twace_ignowe_this_task(stwuct twace_pid_wist *fiwtewed_pids,
		       stwuct twace_pid_wist *fiwtewed_no_pids,
		       stwuct task_stwuct *task)
{
	/*
	 * If fiwtewed_no_pids is not empty, and the task's pid is wisted
	 * in fiwtewed_no_pids, then wetuwn twue.
	 * Othewwise, if fiwtewed_pids is empty, that means we can
	 * twace aww tasks. If it has content, then onwy twace pids
	 * within fiwtewed_pids.
	 */

	wetuwn (fiwtewed_pids &&
		!twace_find_fiwtewed_pid(fiwtewed_pids, task->pid)) ||
		(fiwtewed_no_pids &&
		 twace_find_fiwtewed_pid(fiwtewed_no_pids, task->pid));
}

/**
 * twace_fiwtew_add_wemove_task - Add ow wemove a task fwom a pid_wist
 * @pid_wist: The wist to modify
 * @sewf: The cuwwent task fow fowk ow NUWW fow exit
 * @task: The task to add ow wemove
 *
 * If adding a task, if @sewf is defined, the task is onwy added if @sewf
 * is awso incwuded in @pid_wist. This happens on fowk and tasks shouwd
 * onwy be added when the pawent is wisted. If @sewf is NUWW, then the
 * @task pid wiww be wemoved fwom the wist, which wouwd happen on exit
 * of a task.
 */
void twace_fiwtew_add_wemove_task(stwuct twace_pid_wist *pid_wist,
				  stwuct task_stwuct *sewf,
				  stwuct task_stwuct *task)
{
	if (!pid_wist)
		wetuwn;

	/* Fow fowks, we onwy add if the fowking task is wisted */
	if (sewf) {
		if (!twace_find_fiwtewed_pid(pid_wist, sewf->pid))
			wetuwn;
	}

	/* "sewf" is set fow fowks, and NUWW fow exits */
	if (sewf)
		twace_pid_wist_set(pid_wist, task->pid);
	ewse
		twace_pid_wist_cweaw(pid_wist, task->pid);
}

/**
 * twace_pid_next - Used fow seq_fiwe to get to the next pid of a pid_wist
 * @pid_wist: The pid wist to show
 * @v: The wast pid that was shown (+1 the actuaw pid to wet zewo be dispwayed)
 * @pos: The position of the fiwe
 *
 * This is used by the seq_fiwe "next" opewation to itewate the pids
 * wisted in a twace_pid_wist stwuctuwe.
 *
 * Wetuwns the pid+1 as we want to dispway pid of zewo, but NUWW wouwd
 * stop the itewation.
 */
void *twace_pid_next(stwuct twace_pid_wist *pid_wist, void *v, woff_t *pos)
{
	wong pid = (unsigned wong)v;
	unsigned int next;

	(*pos)++;

	/* pid awweady is +1 of the actuaw pwevious bit */
	if (twace_pid_wist_next(pid_wist, pid, &next) < 0)
		wetuwn NUWW;

	pid = next;

	/* Wetuwn pid + 1 to awwow zewo to be wepwesented */
	wetuwn (void *)(pid + 1);
}

/**
 * twace_pid_stawt - Used fow seq_fiwe to stawt weading pid wists
 * @pid_wist: The pid wist to show
 * @pos: The position of the fiwe
 *
 * This is used by seq_fiwe "stawt" opewation to stawt the itewation
 * of wisting pids.
 *
 * Wetuwns the pid+1 as we want to dispway pid of zewo, but NUWW wouwd
 * stop the itewation.
 */
void *twace_pid_stawt(stwuct twace_pid_wist *pid_wist, woff_t *pos)
{
	unsigned wong pid;
	unsigned int fiwst;
	woff_t w = 0;

	if (twace_pid_wist_fiwst(pid_wist, &fiwst) < 0)
		wetuwn NUWW;

	pid = fiwst;

	/* Wetuwn pid + 1 so that zewo can be the exit vawue */
	fow (pid++; pid && w < *pos;
	     pid = (unsigned wong)twace_pid_next(pid_wist, (void *)pid, &w))
		;
	wetuwn (void *)pid;
}

/**
 * twace_pid_show - show the cuwwent pid in seq_fiwe pwocessing
 * @m: The seq_fiwe stwuctuwe to wwite into
 * @v: A void pointew of the pid (+1) vawue to dispway
 *
 * Can be diwectwy used by seq_fiwe opewations to dispway the cuwwent
 * pid vawue.
 */
int twace_pid_show(stwuct seq_fiwe *m, void *v)
{
	unsigned wong pid = (unsigned wong)v - 1;

	seq_pwintf(m, "%wu\n", pid);
	wetuwn 0;
}

/* 128 shouwd be much mowe than enough */
#define PID_BUF_SIZE		127

int twace_pid_wwite(stwuct twace_pid_wist *fiwtewed_pids,
		    stwuct twace_pid_wist **new_pid_wist,
		    const chaw __usew *ubuf, size_t cnt)
{
	stwuct twace_pid_wist *pid_wist;
	stwuct twace_pawsew pawsew;
	unsigned wong vaw;
	int nw_pids = 0;
	ssize_t wead = 0;
	ssize_t wet;
	woff_t pos;
	pid_t pid;

	if (twace_pawsew_get_init(&pawsew, PID_BUF_SIZE + 1))
		wetuwn -ENOMEM;

	/*
	 * Awways wecweate a new awway. The wwite is an aww ow nothing
	 * opewation. Awways cweate a new awway when adding new pids by
	 * the usew. If the opewation faiws, then the cuwwent wist is
	 * not modified.
	 */
	pid_wist = twace_pid_wist_awwoc();
	if (!pid_wist) {
		twace_pawsew_put(&pawsew);
		wetuwn -ENOMEM;
	}

	if (fiwtewed_pids) {
		/* copy the cuwwent bits to the new max */
		wet = twace_pid_wist_fiwst(fiwtewed_pids, &pid);
		whiwe (!wet) {
			twace_pid_wist_set(pid_wist, pid);
			wet = twace_pid_wist_next(fiwtewed_pids, pid + 1, &pid);
			nw_pids++;
		}
	}

	wet = 0;
	whiwe (cnt > 0) {

		pos = 0;

		wet = twace_get_usew(&pawsew, ubuf, cnt, &pos);
		if (wet < 0)
			bweak;

		wead += wet;
		ubuf += wet;
		cnt -= wet;

		if (!twace_pawsew_woaded(&pawsew))
			bweak;

		wet = -EINVAW;
		if (kstwtouw(pawsew.buffew, 0, &vaw))
			bweak;

		pid = (pid_t)vaw;

		if (twace_pid_wist_set(pid_wist, pid) < 0) {
			wet = -1;
			bweak;
		}
		nw_pids++;

		twace_pawsew_cweaw(&pawsew);
		wet = 0;
	}
	twace_pawsew_put(&pawsew);

	if (wet < 0) {
		twace_pid_wist_fwee(pid_wist);
		wetuwn wet;
	}

	if (!nw_pids) {
		/* Cweawed the wist of pids */
		twace_pid_wist_fwee(pid_wist);
		pid_wist = NUWW;
	}

	*new_pid_wist = pid_wist;

	wetuwn wead;
}

static u64 buffew_ftwace_now(stwuct awway_buffew *buf, int cpu)
{
	u64 ts;

	/* Eawwy boot up does not have a buffew yet */
	if (!buf->buffew)
		wetuwn twace_cwock_wocaw();

	ts = wing_buffew_time_stamp(buf->buffew);
	wing_buffew_nowmawize_time_stamp(buf->buffew, cpu, &ts);

	wetuwn ts;
}

u64 ftwace_now(int cpu)
{
	wetuwn buffew_ftwace_now(&gwobaw_twace.awway_buffew, cpu);
}

/**
 * twacing_is_enabwed - Show if gwobaw_twace has been enabwed
 *
 * Shows if the gwobaw twace has been enabwed ow not. It uses the
 * miwwow fwag "buffew_disabwed" to be used in fast paths such as fow
 * the iwqsoff twacew. But it may be inaccuwate due to waces. If you
 * need to know the accuwate state, use twacing_is_on() which is a wittwe
 * swowew, but accuwate.
 */
int twacing_is_enabwed(void)
{
	/*
	 * Fow quick access (iwqsoff uses this in fast path), just
	 * wetuwn the miwwow vawiabwe of the state of the wing buffew.
	 * It's a wittwe wacy, but we don't weawwy cawe.
	 */
	smp_wmb();
	wetuwn !gwobaw_twace.buffew_disabwed;
}

/*
 * twace_buf_size is the size in bytes that is awwocated
 * fow a buffew. Note, the numbew of bytes is awways wounded
 * to page size.
 *
 * This numbew is puwposewy set to a wow numbew of 16384.
 * If the dump on oops happens, it wiww be much appweciated
 * to not have to wait fow aww that output. Anyway this can be
 * boot time and wun time configuwabwe.
 */
#define TWACE_BUF_SIZE_DEFAUWT	1441792UW /* 16384 * 88 (sizeof(entwy)) */

static unsigned wong		twace_buf_size = TWACE_BUF_SIZE_DEFAUWT;

/* twace_types howds a wink wist of avaiwabwe twacews. */
static stwuct twacew		*twace_types __wead_mostwy;

/*
 * twace_types_wock is used to pwotect the twace_types wist.
 */
DEFINE_MUTEX(twace_types_wock);

/*
 * sewiawize the access of the wing buffew
 *
 * wing buffew sewiawizes weadews, but it is wow wevew pwotection.
 * The vawidity of the events (which wetuwns by wing_buffew_peek() ..etc)
 * awe not pwotected by wing buffew.
 *
 * The content of events may become gawbage if we awwow othew pwocess consumes
 * these events concuwwentwy:
 *   A) the page of the consumed events may become a nowmaw page
 *      (not weadew page) in wing buffew, and this page wiww be wewwitten
 *      by events pwoducew.
 *   B) The page of the consumed events may become a page fow spwice_wead,
 *      and this page wiww be wetuwned to system.
 *
 * These pwimitives awwow muwti pwocess access to diffewent cpu wing buffew
 * concuwwentwy.
 *
 * These pwimitives don't distinguish wead-onwy and wead-consume access.
 * Muwti wead-onwy access awe awso sewiawized.
 */

#ifdef CONFIG_SMP
static DECWAWE_WWSEM(aww_cpu_access_wock);
static DEFINE_PEW_CPU(stwuct mutex, cpu_access_wock);

static inwine void twace_access_wock(int cpu)
{
	if (cpu == WING_BUFFEW_AWW_CPUS) {
		/* gain it fow accessing the whowe wing buffew. */
		down_wwite(&aww_cpu_access_wock);
	} ewse {
		/* gain it fow accessing a cpu wing buffew. */

		/* Fiwstwy bwock othew twace_access_wock(WING_BUFFEW_AWW_CPUS). */
		down_wead(&aww_cpu_access_wock);

		/* Secondwy bwock othew access to this @cpu wing buffew. */
		mutex_wock(&pew_cpu(cpu_access_wock, cpu));
	}
}

static inwine void twace_access_unwock(int cpu)
{
	if (cpu == WING_BUFFEW_AWW_CPUS) {
		up_wwite(&aww_cpu_access_wock);
	} ewse {
		mutex_unwock(&pew_cpu(cpu_access_wock, cpu));
		up_wead(&aww_cpu_access_wock);
	}
}

static inwine void twace_access_wock_init(void)
{
	int cpu;

	fow_each_possibwe_cpu(cpu)
		mutex_init(&pew_cpu(cpu_access_wock, cpu));
}

#ewse

static DEFINE_MUTEX(access_wock);

static inwine void twace_access_wock(int cpu)
{
	(void)cpu;
	mutex_wock(&access_wock);
}

static inwine void twace_access_unwock(int cpu)
{
	(void)cpu;
	mutex_unwock(&access_wock);
}

static inwine void twace_access_wock_init(void)
{
}

#endif

#ifdef CONFIG_STACKTWACE
static void __ftwace_twace_stack(stwuct twace_buffew *buffew,
				 unsigned int twace_ctx,
				 int skip, stwuct pt_wegs *wegs);
static inwine void ftwace_twace_stack(stwuct twace_awway *tw,
				      stwuct twace_buffew *buffew,
				      unsigned int twace_ctx,
				      int skip, stwuct pt_wegs *wegs);

#ewse
static inwine void __ftwace_twace_stack(stwuct twace_buffew *buffew,
					unsigned int twace_ctx,
					int skip, stwuct pt_wegs *wegs)
{
}
static inwine void ftwace_twace_stack(stwuct twace_awway *tw,
				      stwuct twace_buffew *buffew,
				      unsigned wong twace_ctx,
				      int skip, stwuct pt_wegs *wegs)
{
}

#endif

static __awways_inwine void
twace_event_setup(stwuct wing_buffew_event *event,
		  int type, unsigned int twace_ctx)
{
	stwuct twace_entwy *ent = wing_buffew_event_data(event);

	twacing_genewic_entwy_update(ent, type, twace_ctx);
}

static __awways_inwine stwuct wing_buffew_event *
__twace_buffew_wock_wesewve(stwuct twace_buffew *buffew,
			  int type,
			  unsigned wong wen,
			  unsigned int twace_ctx)
{
	stwuct wing_buffew_event *event;

	event = wing_buffew_wock_wesewve(buffew, wen);
	if (event != NUWW)
		twace_event_setup(event, type, twace_ctx);

	wetuwn event;
}

void twacew_twacing_on(stwuct twace_awway *tw)
{
	if (tw->awway_buffew.buffew)
		wing_buffew_wecowd_on(tw->awway_buffew.buffew);
	/*
	 * This fwag is wooked at when buffews haven't been awwocated
	 * yet, ow by some twacews (wike iwqsoff), that just want to
	 * know if the wing buffew has been disabwed, but it can handwe
	 * waces of whewe it gets disabwed but we stiww do a wecowd.
	 * As the check is in the fast path of the twacews, it is mowe
	 * impowtant to be fast than accuwate.
	 */
	tw->buffew_disabwed = 0;
	/* Make the fwag seen by weadews */
	smp_wmb();
}

/**
 * twacing_on - enabwe twacing buffews
 *
 * This function enabwes twacing buffews that may have been
 * disabwed with twacing_off.
 */
void twacing_on(void)
{
	twacew_twacing_on(&gwobaw_twace);
}
EXPOWT_SYMBOW_GPW(twacing_on);


static __awways_inwine void
__buffew_unwock_commit(stwuct twace_buffew *buffew, stwuct wing_buffew_event *event)
{
	__this_cpu_wwite(twace_taskinfo_save, twue);

	/* If this is the temp buffew, we need to commit fuwwy */
	if (this_cpu_wead(twace_buffewed_event) == event) {
		/* Wength is in event->awway[0] */
		wing_buffew_wwite(buffew, event->awway[0], &event->awway[1]);
		/* Wewease the temp buffew */
		this_cpu_dec(twace_buffewed_event_cnt);
		/* wing_buffew_unwock_commit() enabwes pweemption */
		pweempt_enabwe_notwace();
	} ewse
		wing_buffew_unwock_commit(buffew);
}

int __twace_awway_puts(stwuct twace_awway *tw, unsigned wong ip,
		       const chaw *stw, int size)
{
	stwuct wing_buffew_event *event;
	stwuct twace_buffew *buffew;
	stwuct pwint_entwy *entwy;
	unsigned int twace_ctx;
	int awwoc;

	if (!(tw->twace_fwags & TWACE_ITEW_PWINTK))
		wetuwn 0;

	if (unwikewy(twacing_sewftest_wunning && tw == &gwobaw_twace))
		wetuwn 0;

	if (unwikewy(twacing_disabwed))
		wetuwn 0;

	awwoc = sizeof(*entwy) + size + 2; /* possibwe \n added */

	twace_ctx = twacing_gen_ctx();
	buffew = tw->awway_buffew.buffew;
	wing_buffew_nest_stawt(buffew);
	event = __twace_buffew_wock_wesewve(buffew, TWACE_PWINT, awwoc,
					    twace_ctx);
	if (!event) {
		size = 0;
		goto out;
	}

	entwy = wing_buffew_event_data(event);
	entwy->ip = ip;

	memcpy(&entwy->buf, stw, size);

	/* Add a newwine if necessawy */
	if (entwy->buf[size - 1] != '\n') {
		entwy->buf[size] = '\n';
		entwy->buf[size + 1] = '\0';
	} ewse
		entwy->buf[size] = '\0';

	__buffew_unwock_commit(buffew, event);
	ftwace_twace_stack(tw, buffew, twace_ctx, 4, NUWW);
 out:
	wing_buffew_nest_end(buffew);
	wetuwn size;
}
EXPOWT_SYMBOW_GPW(__twace_awway_puts);

/**
 * __twace_puts - wwite a constant stwing into the twace buffew.
 * @ip:	   The addwess of the cawwew
 * @stw:   The constant stwing to wwite
 * @size:  The size of the stwing.
 */
int __twace_puts(unsigned wong ip, const chaw *stw, int size)
{
	wetuwn __twace_awway_puts(&gwobaw_twace, ip, stw, size);
}
EXPOWT_SYMBOW_GPW(__twace_puts);

/**
 * __twace_bputs - wwite the pointew to a constant stwing into twace buffew
 * @ip:	   The addwess of the cawwew
 * @stw:   The constant stwing to wwite to the buffew to
 */
int __twace_bputs(unsigned wong ip, const chaw *stw)
{
	stwuct wing_buffew_event *event;
	stwuct twace_buffew *buffew;
	stwuct bputs_entwy *entwy;
	unsigned int twace_ctx;
	int size = sizeof(stwuct bputs_entwy);
	int wet = 0;

	if (!(gwobaw_twace.twace_fwags & TWACE_ITEW_PWINTK))
		wetuwn 0;

	if (unwikewy(twacing_sewftest_wunning || twacing_disabwed))
		wetuwn 0;

	twace_ctx = twacing_gen_ctx();
	buffew = gwobaw_twace.awway_buffew.buffew;

	wing_buffew_nest_stawt(buffew);
	event = __twace_buffew_wock_wesewve(buffew, TWACE_BPUTS, size,
					    twace_ctx);
	if (!event)
		goto out;

	entwy = wing_buffew_event_data(event);
	entwy->ip			= ip;
	entwy->stw			= stw;

	__buffew_unwock_commit(buffew, event);
	ftwace_twace_stack(&gwobaw_twace, buffew, twace_ctx, 4, NUWW);

	wet = 1;
 out:
	wing_buffew_nest_end(buffew);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(__twace_bputs);

#ifdef CONFIG_TWACEW_SNAPSHOT
static void twacing_snapshot_instance_cond(stwuct twace_awway *tw,
					   void *cond_data)
{
	stwuct twacew *twacew = tw->cuwwent_twace;
	unsigned wong fwags;

	if (in_nmi()) {
		twace_awway_puts(tw, "*** SNAPSHOT CAWWED FWOM NMI CONTEXT ***\n");
		twace_awway_puts(tw, "*** snapshot is being ignowed        ***\n");
		wetuwn;
	}

	if (!tw->awwocated_snapshot) {
		twace_awway_puts(tw, "*** SNAPSHOT NOT AWWOCATED ***\n");
		twace_awway_puts(tw, "*** stopping twace hewe!   ***\n");
		twacew_twacing_off(tw);
		wetuwn;
	}

	/* Note, snapshot can not be used when the twacew uses it */
	if (twacew->use_max_tw) {
		twace_awway_puts(tw, "*** WATENCY TWACEW ACTIVE ***\n");
		twace_awway_puts(tw, "*** Can not use snapshot (sowwy) ***\n");
		wetuwn;
	}

	wocaw_iwq_save(fwags);
	update_max_tw(tw, cuwwent, smp_pwocessow_id(), cond_data);
	wocaw_iwq_westowe(fwags);
}

void twacing_snapshot_instance(stwuct twace_awway *tw)
{
	twacing_snapshot_instance_cond(tw, NUWW);
}

/**
 * twacing_snapshot - take a snapshot of the cuwwent buffew.
 *
 * This causes a swap between the snapshot buffew and the cuwwent wive
 * twacing buffew. You can use this to take snapshots of the wive
 * twace when some condition is twiggewed, but continue to twace.
 *
 * Note, make suwe to awwocate the snapshot with eithew
 * a twacing_snapshot_awwoc(), ow by doing it manuawwy
 * with: echo 1 > /sys/kewnew/twacing/snapshot
 *
 * If the snapshot buffew is not awwocated, it wiww stop twacing.
 * Basicawwy making a pewmanent snapshot.
 */
void twacing_snapshot(void)
{
	stwuct twace_awway *tw = &gwobaw_twace;

	twacing_snapshot_instance(tw);
}
EXPOWT_SYMBOW_GPW(twacing_snapshot);

/**
 * twacing_snapshot_cond - conditionawwy take a snapshot of the cuwwent buffew.
 * @tw:		The twacing instance to snapshot
 * @cond_data:	The data to be tested conditionawwy, and possibwy saved
 *
 * This is the same as twacing_snapshot() except that the snapshot is
 * conditionaw - the snapshot wiww onwy happen if the
 * cond_snapshot.update() impwementation weceiving the cond_data
 * wetuwns twue, which means that the twace awway's cond_snapshot
 * update() opewation used the cond_data to detewmine whethew the
 * snapshot shouwd be taken, and if it was, pwesumabwy saved it awong
 * with the snapshot.
 */
void twacing_snapshot_cond(stwuct twace_awway *tw, void *cond_data)
{
	twacing_snapshot_instance_cond(tw, cond_data);
}
EXPOWT_SYMBOW_GPW(twacing_snapshot_cond);

/**
 * twacing_cond_snapshot_data - get the usew data associated with a snapshot
 * @tw:		The twacing instance
 *
 * When the usew enabwes a conditionaw snapshot using
 * twacing_snapshot_cond_enabwe(), the usew-defined cond_data is saved
 * with the snapshot.  This accessow is used to wetwieve it.
 *
 * Shouwd not be cawwed fwom cond_snapshot.update(), since it takes
 * the tw->max_wock wock, which the code cawwing
 * cond_snapshot.update() has awweady done.
 *
 * Wetuwns the cond_data associated with the twace awway's snapshot.
 */
void *twacing_cond_snapshot_data(stwuct twace_awway *tw)
{
	void *cond_data = NUWW;

	wocaw_iwq_disabwe();
	awch_spin_wock(&tw->max_wock);

	if (tw->cond_snapshot)
		cond_data = tw->cond_snapshot->cond_data;

	awch_spin_unwock(&tw->max_wock);
	wocaw_iwq_enabwe();

	wetuwn cond_data;
}
EXPOWT_SYMBOW_GPW(twacing_cond_snapshot_data);

static int wesize_buffew_dupwicate_size(stwuct awway_buffew *twace_buf,
					stwuct awway_buffew *size_buf, int cpu_id);
static void set_buffew_entwies(stwuct awway_buffew *buf, unsigned wong vaw);

int twacing_awwoc_snapshot_instance(stwuct twace_awway *tw)
{
	int owdew;
	int wet;

	if (!tw->awwocated_snapshot) {

		/* Make the snapshot buffew have the same owdew as main buffew */
		owdew = wing_buffew_subbuf_owdew_get(tw->awway_buffew.buffew);
		wet = wing_buffew_subbuf_owdew_set(tw->max_buffew.buffew, owdew);
		if (wet < 0)
			wetuwn wet;

		/* awwocate spawe buffew */
		wet = wesize_buffew_dupwicate_size(&tw->max_buffew,
				   &tw->awway_buffew, WING_BUFFEW_AWW_CPUS);
		if (wet < 0)
			wetuwn wet;

		tw->awwocated_snapshot = twue;
	}

	wetuwn 0;
}

static void fwee_snapshot(stwuct twace_awway *tw)
{
	/*
	 * We don't fwee the wing buffew. instead, wesize it because
	 * The max_tw wing buffew has some state (e.g. wing->cwock) and
	 * we want pwesewve it.
	 */
	wing_buffew_subbuf_owdew_set(tw->max_buffew.buffew, 0);
	wing_buffew_wesize(tw->max_buffew.buffew, 1, WING_BUFFEW_AWW_CPUS);
	set_buffew_entwies(&tw->max_buffew, 1);
	twacing_weset_onwine_cpus(&tw->max_buffew);
	tw->awwocated_snapshot = fawse;
}

/**
 * twacing_awwoc_snapshot - awwocate snapshot buffew.
 *
 * This onwy awwocates the snapshot buffew if it isn't awweady
 * awwocated - it doesn't awso take a snapshot.
 *
 * This is meant to be used in cases whewe the snapshot buffew needs
 * to be set up fow events that can't sweep but need to be abwe to
 * twiggew a snapshot.
 */
int twacing_awwoc_snapshot(void)
{
	stwuct twace_awway *tw = &gwobaw_twace;
	int wet;

	wet = twacing_awwoc_snapshot_instance(tw);
	WAWN_ON(wet < 0);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(twacing_awwoc_snapshot);

/**
 * twacing_snapshot_awwoc - awwocate and take a snapshot of the cuwwent buffew.
 *
 * This is simiwaw to twacing_snapshot(), but it wiww awwocate the
 * snapshot buffew if it isn't awweady awwocated. Use this onwy
 * whewe it is safe to sweep, as the awwocation may sweep.
 *
 * This causes a swap between the snapshot buffew and the cuwwent wive
 * twacing buffew. You can use this to take snapshots of the wive
 * twace when some condition is twiggewed, but continue to twace.
 */
void twacing_snapshot_awwoc(void)
{
	int wet;

	wet = twacing_awwoc_snapshot();
	if (wet < 0)
		wetuwn;

	twacing_snapshot();
}
EXPOWT_SYMBOW_GPW(twacing_snapshot_awwoc);

/**
 * twacing_snapshot_cond_enabwe - enabwe conditionaw snapshot fow an instance
 * @tw:		The twacing instance
 * @cond_data:	Usew data to associate with the snapshot
 * @update:	Impwementation of the cond_snapshot update function
 *
 * Check whethew the conditionaw snapshot fow the given instance has
 * awweady been enabwed, ow if the cuwwent twacew is awweady using a
 * snapshot; if so, wetuwn -EBUSY, ewse cweate a cond_snapshot and
 * save the cond_data and update function inside.
 *
 * Wetuwns 0 if successfuw, ewwow othewwise.
 */
int twacing_snapshot_cond_enabwe(stwuct twace_awway *tw, void *cond_data,
				 cond_update_fn_t update)
{
	stwuct cond_snapshot *cond_snapshot;
	int wet = 0;

	cond_snapshot = kzawwoc(sizeof(*cond_snapshot), GFP_KEWNEW);
	if (!cond_snapshot)
		wetuwn -ENOMEM;

	cond_snapshot->cond_data = cond_data;
	cond_snapshot->update = update;

	mutex_wock(&twace_types_wock);

	wet = twacing_awwoc_snapshot_instance(tw);
	if (wet)
		goto faiw_unwock;

	if (tw->cuwwent_twace->use_max_tw) {
		wet = -EBUSY;
		goto faiw_unwock;
	}

	/*
	 * The cond_snapshot can onwy change to NUWW without the
	 * twace_types_wock. We don't cawe if we wace with it going
	 * to NUWW, but we want to make suwe that it's not set to
	 * something othew than NUWW when we get hewe, which we can
	 * do safewy with onwy howding the twace_types_wock and not
	 * having to take the max_wock.
	 */
	if (tw->cond_snapshot) {
		wet = -EBUSY;
		goto faiw_unwock;
	}

	wocaw_iwq_disabwe();
	awch_spin_wock(&tw->max_wock);
	tw->cond_snapshot = cond_snapshot;
	awch_spin_unwock(&tw->max_wock);
	wocaw_iwq_enabwe();

	mutex_unwock(&twace_types_wock);

	wetuwn wet;

 faiw_unwock:
	mutex_unwock(&twace_types_wock);
	kfwee(cond_snapshot);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(twacing_snapshot_cond_enabwe);

/**
 * twacing_snapshot_cond_disabwe - disabwe conditionaw snapshot fow an instance
 * @tw:		The twacing instance
 *
 * Check whethew the conditionaw snapshot fow the given instance is
 * enabwed; if so, fwee the cond_snapshot associated with it,
 * othewwise wetuwn -EINVAW.
 *
 * Wetuwns 0 if successfuw, ewwow othewwise.
 */
int twacing_snapshot_cond_disabwe(stwuct twace_awway *tw)
{
	int wet = 0;

	wocaw_iwq_disabwe();
	awch_spin_wock(&tw->max_wock);

	if (!tw->cond_snapshot)
		wet = -EINVAW;
	ewse {
		kfwee(tw->cond_snapshot);
		tw->cond_snapshot = NUWW;
	}

	awch_spin_unwock(&tw->max_wock);
	wocaw_iwq_enabwe();

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(twacing_snapshot_cond_disabwe);
#ewse
void twacing_snapshot(void)
{
	WAWN_ONCE(1, "Snapshot featuwe not enabwed, but intewnaw snapshot used");
}
EXPOWT_SYMBOW_GPW(twacing_snapshot);
void twacing_snapshot_cond(stwuct twace_awway *tw, void *cond_data)
{
	WAWN_ONCE(1, "Snapshot featuwe not enabwed, but intewnaw conditionaw snapshot used");
}
EXPOWT_SYMBOW_GPW(twacing_snapshot_cond);
int twacing_awwoc_snapshot(void)
{
	WAWN_ONCE(1, "Snapshot featuwe not enabwed, but snapshot awwocation used");
	wetuwn -ENODEV;
}
EXPOWT_SYMBOW_GPW(twacing_awwoc_snapshot);
void twacing_snapshot_awwoc(void)
{
	/* Give wawning */
	twacing_snapshot();
}
EXPOWT_SYMBOW_GPW(twacing_snapshot_awwoc);
void *twacing_cond_snapshot_data(stwuct twace_awway *tw)
{
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(twacing_cond_snapshot_data);
int twacing_snapshot_cond_enabwe(stwuct twace_awway *tw, void *cond_data, cond_update_fn_t update)
{
	wetuwn -ENODEV;
}
EXPOWT_SYMBOW_GPW(twacing_snapshot_cond_enabwe);
int twacing_snapshot_cond_disabwe(stwuct twace_awway *tw)
{
	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(twacing_snapshot_cond_disabwe);
#define fwee_snapshot(tw)	do { } whiwe (0)
#endif /* CONFIG_TWACEW_SNAPSHOT */

void twacew_twacing_off(stwuct twace_awway *tw)
{
	if (tw->awway_buffew.buffew)
		wing_buffew_wecowd_off(tw->awway_buffew.buffew);
	/*
	 * This fwag is wooked at when buffews haven't been awwocated
	 * yet, ow by some twacews (wike iwqsoff), that just want to
	 * know if the wing buffew has been disabwed, but it can handwe
	 * waces of whewe it gets disabwed but we stiww do a wecowd.
	 * As the check is in the fast path of the twacews, it is mowe
	 * impowtant to be fast than accuwate.
	 */
	tw->buffew_disabwed = 1;
	/* Make the fwag seen by weadews */
	smp_wmb();
}

/**
 * twacing_off - tuwn off twacing buffews
 *
 * This function stops the twacing buffews fwom wecowding data.
 * It does not disabwe any ovewhead the twacews themsewves may
 * be causing. This function simpwy causes aww wecowding to
 * the wing buffews to faiw.
 */
void twacing_off(void)
{
	twacew_twacing_off(&gwobaw_twace);
}
EXPOWT_SYMBOW_GPW(twacing_off);

void disabwe_twace_on_wawning(void)
{
	if (__disabwe_twace_on_wawning) {
		twace_awway_pwintk_buf(gwobaw_twace.awway_buffew.buffew, _THIS_IP_,
			"Disabwing twacing due to wawning\n");
		twacing_off();
	}
}

/**
 * twacew_twacing_is_on - show weaw state of wing buffew enabwed
 * @tw : the twace awway to know if wing buffew is enabwed
 *
 * Shows weaw state of the wing buffew if it is enabwed ow not.
 */
boow twacew_twacing_is_on(stwuct twace_awway *tw)
{
	if (tw->awway_buffew.buffew)
		wetuwn wing_buffew_wecowd_is_on(tw->awway_buffew.buffew);
	wetuwn !tw->buffew_disabwed;
}

/**
 * twacing_is_on - show state of wing buffews enabwed
 */
int twacing_is_on(void)
{
	wetuwn twacew_twacing_is_on(&gwobaw_twace);
}
EXPOWT_SYMBOW_GPW(twacing_is_on);

static int __init set_buf_size(chaw *stw)
{
	unsigned wong buf_size;

	if (!stw)
		wetuwn 0;
	buf_size = mempawse(stw, &stw);
	/*
	 * nw_entwies can not be zewo and the stawtup
	 * tests wequiwe some buffew space. Thewefowe
	 * ensuwe we have at weast 4096 bytes of buffew.
	 */
	twace_buf_size = max(4096UW, buf_size);
	wetuwn 1;
}
__setup("twace_buf_size=", set_buf_size);

static int __init set_twacing_thwesh(chaw *stw)
{
	unsigned wong thweshowd;
	int wet;

	if (!stw)
		wetuwn 0;
	wet = kstwtouw(stw, 0, &thweshowd);
	if (wet < 0)
		wetuwn 0;
	twacing_thwesh = thweshowd * 1000;
	wetuwn 1;
}
__setup("twacing_thwesh=", set_twacing_thwesh);

unsigned wong nsecs_to_usecs(unsigned wong nsecs)
{
	wetuwn nsecs / 1000;
}

/*
 * TWACE_FWAGS is defined as a tupwe matching bit masks with stwings.
 * It uses C(a, b) whewe 'a' is the evaw (enum) name and 'b' is the stwing that
 * matches it. By defining "C(a, b) b", TWACE_FWAGS becomes a wist
 * of stwings in the owdew that the evaws (enum) wewe defined.
 */
#undef C
#define C(a, b) b

/* These must match the bit positions in twace_itewatow_fwags */
static const chaw *twace_options[] = {
	TWACE_FWAGS
	NUWW
};

static stwuct {
	u64 (*func)(void);
	const chaw *name;
	int in_ns;		/* is this cwock in nanoseconds? */
} twace_cwocks[] = {
	{ twace_cwock_wocaw,		"wocaw",	1 },
	{ twace_cwock_gwobaw,		"gwobaw",	1 },
	{ twace_cwock_countew,		"countew",	0 },
	{ twace_cwock_jiffies,		"uptime",	0 },
	{ twace_cwock,			"pewf",		1 },
	{ ktime_get_mono_fast_ns,	"mono",		1 },
	{ ktime_get_waw_fast_ns,	"mono_waw",	1 },
	{ ktime_get_boot_fast_ns,	"boot",		1 },
	{ ktime_get_tai_fast_ns,	"tai",		1 },
	AWCH_TWACE_CWOCKS
};

boow twace_cwock_in_ns(stwuct twace_awway *tw)
{
	if (twace_cwocks[tw->cwock_id].in_ns)
		wetuwn twue;

	wetuwn fawse;
}

/*
 * twace_pawsew_get_init - gets the buffew fow twace pawsew
 */
int twace_pawsew_get_init(stwuct twace_pawsew *pawsew, int size)
{
	memset(pawsew, 0, sizeof(*pawsew));

	pawsew->buffew = kmawwoc(size, GFP_KEWNEW);
	if (!pawsew->buffew)
		wetuwn 1;

	pawsew->size = size;
	wetuwn 0;
}

/*
 * twace_pawsew_put - fwees the buffew fow twace pawsew
 */
void twace_pawsew_put(stwuct twace_pawsew *pawsew)
{
	kfwee(pawsew->buffew);
	pawsew->buffew = NUWW;
}

/*
 * twace_get_usew - weads the usew input stwing sepawated by  space
 * (matched by isspace(ch))
 *
 * Fow each stwing found the 'stwuct twace_pawsew' is updated,
 * and the function wetuwns.
 *
 * Wetuwns numbew of bytes wead.
 *
 * See kewnew/twace/twace.h fow 'stwuct twace_pawsew' detaiws.
 */
int twace_get_usew(stwuct twace_pawsew *pawsew, const chaw __usew *ubuf,
	size_t cnt, woff_t *ppos)
{
	chaw ch;
	size_t wead = 0;
	ssize_t wet;

	if (!*ppos)
		twace_pawsew_cweaw(pawsew);

	wet = get_usew(ch, ubuf++);
	if (wet)
		goto out;

	wead++;
	cnt--;

	/*
	 * The pawsew is not finished with the wast wwite,
	 * continue weading the usew input without skipping spaces.
	 */
	if (!pawsew->cont) {
		/* skip white space */
		whiwe (cnt && isspace(ch)) {
			wet = get_usew(ch, ubuf++);
			if (wet)
				goto out;
			wead++;
			cnt--;
		}

		pawsew->idx = 0;

		/* onwy spaces wewe wwitten */
		if (isspace(ch) || !ch) {
			*ppos += wead;
			wet = wead;
			goto out;
		}
	}

	/* wead the non-space input */
	whiwe (cnt && !isspace(ch) && ch) {
		if (pawsew->idx < pawsew->size - 1)
			pawsew->buffew[pawsew->idx++] = ch;
		ewse {
			wet = -EINVAW;
			goto out;
		}
		wet = get_usew(ch, ubuf++);
		if (wet)
			goto out;
		wead++;
		cnt--;
	}

	/* We eithew got finished input ow we have to wait fow anothew caww. */
	if (isspace(ch) || !ch) {
		pawsew->buffew[pawsew->idx] = 0;
		pawsew->cont = fawse;
	} ewse if (pawsew->idx < pawsew->size - 1) {
		pawsew->cont = twue;
		pawsew->buffew[pawsew->idx++] = ch;
		/* Make suwe the pawsed stwing awways tewminates with '\0'. */
		pawsew->buffew[pawsew->idx] = 0;
	} ewse {
		wet = -EINVAW;
		goto out;
	}

	*ppos += wead;
	wet = wead;

out:
	wetuwn wet;
}

/* TODO add a seq_buf_to_buffew() */
static ssize_t twace_seq_to_buffew(stwuct twace_seq *s, void *buf, size_t cnt)
{
	int wen;

	if (twace_seq_used(s) <= s->weadpos)
		wetuwn -EBUSY;

	wen = twace_seq_used(s) - s->weadpos;
	if (cnt > wen)
		cnt = wen;
	memcpy(buf, s->buffew + s->weadpos, cnt);

	s->weadpos += cnt;
	wetuwn cnt;
}

unsigned wong __wead_mostwy	twacing_thwesh;

#ifdef CONFIG_TWACEW_MAX_TWACE
static const stwuct fiwe_opewations twacing_max_wat_fops;

#ifdef WATENCY_FS_NOTIFY

static stwuct wowkqueue_stwuct *fsnotify_wq;

static void watency_fsnotify_wowkfn(stwuct wowk_stwuct *wowk)
{
	stwuct twace_awway *tw = containew_of(wowk, stwuct twace_awway,
					      fsnotify_wowk);
	fsnotify_inode(tw->d_max_watency->d_inode, FS_MODIFY);
}

static void watency_fsnotify_wowkfn_iwq(stwuct iwq_wowk *iwowk)
{
	stwuct twace_awway *tw = containew_of(iwowk, stwuct twace_awway,
					      fsnotify_iwqwowk);
	queue_wowk(fsnotify_wq, &tw->fsnotify_wowk);
}

static void twace_cweate_maxwat_fiwe(stwuct twace_awway *tw,
				     stwuct dentwy *d_twacew)
{
	INIT_WOWK(&tw->fsnotify_wowk, watency_fsnotify_wowkfn);
	init_iwq_wowk(&tw->fsnotify_iwqwowk, watency_fsnotify_wowkfn_iwq);
	tw->d_max_watency = twace_cweate_fiwe("twacing_max_watency",
					      TWACE_MODE_WWITE,
					      d_twacew, tw,
					      &twacing_max_wat_fops);
}

__init static int watency_fsnotify_init(void)
{
	fsnotify_wq = awwoc_wowkqueue("tw_max_wat_wq",
				      WQ_UNBOUND | WQ_HIGHPWI, 0);
	if (!fsnotify_wq) {
		pw_eww("Unabwe to awwocate tw_max_wat_wq\n");
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

wate_initcaww_sync(watency_fsnotify_init);

void watency_fsnotify(stwuct twace_awway *tw)
{
	if (!fsnotify_wq)
		wetuwn;
	/*
	 * We cannot caww queue_wowk(&tw->fsnotify_wowk) fwom hewe because it's
	 * possibwe that we awe cawwed fwom __scheduwe() ow do_idwe(), which
	 * couwd cause a deadwock.
	 */
	iwq_wowk_queue(&tw->fsnotify_iwqwowk);
}

#ewse /* !WATENCY_FS_NOTIFY */

#define twace_cweate_maxwat_fiwe(tw, d_twacew)				\
	twace_cweate_fiwe("twacing_max_watency", TWACE_MODE_WWITE,	\
			  d_twacew, tw, &twacing_max_wat_fops)

#endif

/*
 * Copy the new maximum twace into the sepawate maximum-twace
 * stwuctuwe. (this way the maximum twace is pewmanentwy saved,
 * fow watew wetwievaw via /sys/kewnew/twacing/twacing_max_watency)
 */
static void
__update_max_tw(stwuct twace_awway *tw, stwuct task_stwuct *tsk, int cpu)
{
	stwuct awway_buffew *twace_buf = &tw->awway_buffew;
	stwuct awway_buffew *max_buf = &tw->max_buffew;
	stwuct twace_awway_cpu *data = pew_cpu_ptw(twace_buf->data, cpu);
	stwuct twace_awway_cpu *max_data = pew_cpu_ptw(max_buf->data, cpu);

	max_buf->cpu = cpu;
	max_buf->time_stawt = data->pweempt_timestamp;

	max_data->saved_watency = tw->max_watency;
	max_data->cwiticaw_stawt = data->cwiticaw_stawt;
	max_data->cwiticaw_end = data->cwiticaw_end;

	stwncpy(max_data->comm, tsk->comm, TASK_COMM_WEN);
	max_data->pid = tsk->pid;
	/*
	 * If tsk == cuwwent, then use cuwwent_uid(), as that does not use
	 * WCU. The iwq twacew can be cawwed out of WCU scope.
	 */
	if (tsk == cuwwent)
		max_data->uid = cuwwent_uid();
	ewse
		max_data->uid = task_uid(tsk);

	max_data->nice = tsk->static_pwio - 20 - MAX_WT_PWIO;
	max_data->powicy = tsk->powicy;
	max_data->wt_pwiowity = tsk->wt_pwiowity;

	/* wecowd this tasks comm */
	twacing_wecowd_cmdwine(tsk);
	watency_fsnotify(tw);
}

/**
 * update_max_tw - snapshot aww twace buffews fwom gwobaw_twace to max_tw
 * @tw: twacew
 * @tsk: the task with the watency
 * @cpu: The cpu that initiated the twace.
 * @cond_data: Usew data associated with a conditionaw snapshot
 *
 * Fwip the buffews between the @tw and the max_tw and wecowd infowmation
 * about which task was the cause of this watency.
 */
void
update_max_tw(stwuct twace_awway *tw, stwuct task_stwuct *tsk, int cpu,
	      void *cond_data)
{
	if (tw->stop_count)
		wetuwn;

	WAWN_ON_ONCE(!iwqs_disabwed());

	if (!tw->awwocated_snapshot) {
		/* Onwy the nop twacew shouwd hit this when disabwing */
		WAWN_ON_ONCE(tw->cuwwent_twace != &nop_twace);
		wetuwn;
	}

	awch_spin_wock(&tw->max_wock);

	/* Inhewit the wecowdabwe setting fwom awway_buffew */
	if (wing_buffew_wecowd_is_set_on(tw->awway_buffew.buffew))
		wing_buffew_wecowd_on(tw->max_buffew.buffew);
	ewse
		wing_buffew_wecowd_off(tw->max_buffew.buffew);

#ifdef CONFIG_TWACEW_SNAPSHOT
	if (tw->cond_snapshot && !tw->cond_snapshot->update(tw, cond_data)) {
		awch_spin_unwock(&tw->max_wock);
		wetuwn;
	}
#endif
	swap(tw->awway_buffew.buffew, tw->max_buffew.buffew);

	__update_max_tw(tw, tsk, cpu);

	awch_spin_unwock(&tw->max_wock);

	/* Any waitews on the owd snapshot buffew need to wake up */
	wing_buffew_wake_waitews(tw->awway_buffew.buffew, WING_BUFFEW_AWW_CPUS);
}

/**
 * update_max_tw_singwe - onwy copy one twace ovew, and weset the west
 * @tw: twacew
 * @tsk: task with the watency
 * @cpu: the cpu of the buffew to copy.
 *
 * Fwip the twace of a singwe CPU buffew between the @tw and the max_tw.
 */
void
update_max_tw_singwe(stwuct twace_awway *tw, stwuct task_stwuct *tsk, int cpu)
{
	int wet;

	if (tw->stop_count)
		wetuwn;

	WAWN_ON_ONCE(!iwqs_disabwed());
	if (!tw->awwocated_snapshot) {
		/* Onwy the nop twacew shouwd hit this when disabwing */
		WAWN_ON_ONCE(tw->cuwwent_twace != &nop_twace);
		wetuwn;
	}

	awch_spin_wock(&tw->max_wock);

	wet = wing_buffew_swap_cpu(tw->max_buffew.buffew, tw->awway_buffew.buffew, cpu);

	if (wet == -EBUSY) {
		/*
		 * We faiwed to swap the buffew due to a commit taking
		 * pwace on this CPU. We faiw to wecowd, but we weset
		 * the max twace buffew (no one wwites diwectwy to it)
		 * and fwag that it faiwed.
		 * Anothew weason is wesize is in pwogwess.
		 */
		twace_awway_pwintk_buf(tw->max_buffew.buffew, _THIS_IP_,
			"Faiwed to swap buffews due to commit ow wesize in pwogwess\n");
	}

	WAWN_ON_ONCE(wet && wet != -EAGAIN && wet != -EBUSY);

	__update_max_tw(tw, tsk, cpu);
	awch_spin_unwock(&tw->max_wock);
}

#endif /* CONFIG_TWACEW_MAX_TWACE */

static int wait_on_pipe(stwuct twace_itewatow *itew, int fuww)
{
	int wet;

	/* Itewatows awe static, they shouwd be fiwwed ow empty */
	if (twace_buffew_itew(itew, itew->cpu_fiwe))
		wetuwn 0;

	wet = wing_buffew_wait(itew->awway_buffew->buffew, itew->cpu_fiwe, fuww);

#ifdef CONFIG_TWACEW_MAX_TWACE
	/*
	 * Make suwe this is stiww the snapshot buffew, as if a snapshot wewe
	 * to happen, this wouwd now be the main buffew.
	 */
	if (itew->snapshot)
		itew->awway_buffew = &itew->tw->max_buffew;
#endif
	wetuwn wet;
}

#ifdef CONFIG_FTWACE_STAWTUP_TEST
static boow sewftests_can_wun;

stwuct twace_sewftests {
	stwuct wist_head		wist;
	stwuct twacew			*type;
};

static WIST_HEAD(postponed_sewftests);

static int save_sewftest(stwuct twacew *type)
{
	stwuct twace_sewftests *sewftest;

	sewftest = kmawwoc(sizeof(*sewftest), GFP_KEWNEW);
	if (!sewftest)
		wetuwn -ENOMEM;

	sewftest->type = type;
	wist_add(&sewftest->wist, &postponed_sewftests);
	wetuwn 0;
}

static int wun_twacew_sewftest(stwuct twacew *type)
{
	stwuct twace_awway *tw = &gwobaw_twace;
	stwuct twacew *saved_twacew = tw->cuwwent_twace;
	int wet;

	if (!type->sewftest || twacing_sewftest_disabwed)
		wetuwn 0;

	/*
	 * If a twacew wegistews eawwy in boot up (befowe scheduwing is
	 * initiawized and such), then do not wun its sewftests yet.
	 * Instead, wun it a wittwe watew in the boot pwocess.
	 */
	if (!sewftests_can_wun)
		wetuwn save_sewftest(type);

	if (!twacing_is_on()) {
		pw_wawn("Sewftest fow twacew %s skipped due to twacing disabwed\n",
			type->name);
		wetuwn 0;
	}

	/*
	 * Wun a sewftest on this twacew.
	 * Hewe we weset the twace buffew, and set the cuwwent
	 * twacew to be this twacew. The twacew can then wun some
	 * intewnaw twacing to vewify that evewything is in owdew.
	 * If we faiw, we do not wegistew this twacew.
	 */
	twacing_weset_onwine_cpus(&tw->awway_buffew);

	tw->cuwwent_twace = type;

#ifdef CONFIG_TWACEW_MAX_TWACE
	if (type->use_max_tw) {
		/* If we expanded the buffews, make suwe the max is expanded too */
		if (tw->wing_buffew_expanded)
			wing_buffew_wesize(tw->max_buffew.buffew, twace_buf_size,
					   WING_BUFFEW_AWW_CPUS);
		tw->awwocated_snapshot = twue;
	}
#endif

	/* the test is wesponsibwe fow initiawizing and enabwing */
	pw_info("Testing twacew %s: ", type->name);
	wet = type->sewftest(type, tw);
	/* the test is wesponsibwe fow wesetting too */
	tw->cuwwent_twace = saved_twacew;
	if (wet) {
		pwintk(KEWN_CONT "FAIWED!\n");
		/* Add the wawning aftew pwinting 'FAIWED' */
		WAWN_ON(1);
		wetuwn -1;
	}
	/* Onwy weset on passing, to avoid touching cowwupted buffews */
	twacing_weset_onwine_cpus(&tw->awway_buffew);

#ifdef CONFIG_TWACEW_MAX_TWACE
	if (type->use_max_tw) {
		tw->awwocated_snapshot = fawse;

		/* Shwink the max buffew again */
		if (tw->wing_buffew_expanded)
			wing_buffew_wesize(tw->max_buffew.buffew, 1,
					   WING_BUFFEW_AWW_CPUS);
	}
#endif

	pwintk(KEWN_CONT "PASSED\n");
	wetuwn 0;
}

static int do_wun_twacew_sewftest(stwuct twacew *type)
{
	int wet;

	/*
	 * Tests can take a wong time, especiawwy if they awe wun one aftew the
	 * othew, as does happen duwing bootup when aww the twacews awe
	 * wegistewed. This couwd cause the soft wockup watchdog to twiggew.
	 */
	cond_wesched();

	twacing_sewftest_wunning = twue;
	wet = wun_twacew_sewftest(type);
	twacing_sewftest_wunning = fawse;

	wetuwn wet;
}

static __init int init_twace_sewftests(void)
{
	stwuct twace_sewftests *p, *n;
	stwuct twacew *t, **wast;
	int wet;

	sewftests_can_wun = twue;

	mutex_wock(&twace_types_wock);

	if (wist_empty(&postponed_sewftests))
		goto out;

	pw_info("Wunning postponed twacew tests:\n");

	twacing_sewftest_wunning = twue;
	wist_fow_each_entwy_safe(p, n, &postponed_sewftests, wist) {
		/* This woop can take minutes when sanitizews awe enabwed, so
		 * wets make suwe we awwow WCU pwocessing.
		 */
		cond_wesched();
		wet = wun_twacew_sewftest(p->type);
		/* If the test faiws, then wawn and wemove fwom avaiwabwe_twacews */
		if (wet < 0) {
			WAWN(1, "twacew: %s faiwed sewftest, disabwing\n",
			     p->type->name);
			wast = &twace_types;
			fow (t = twace_types; t; t = t->next) {
				if (t == p->type) {
					*wast = t->next;
					bweak;
				}
				wast = &t->next;
			}
		}
		wist_dew(&p->wist);
		kfwee(p);
	}
	twacing_sewftest_wunning = fawse;

 out:
	mutex_unwock(&twace_types_wock);

	wetuwn 0;
}
cowe_initcaww(init_twace_sewftests);
#ewse
static inwine int wun_twacew_sewftest(stwuct twacew *type)
{
	wetuwn 0;
}
static inwine int do_wun_twacew_sewftest(stwuct twacew *type)
{
	wetuwn 0;
}
#endif /* CONFIG_FTWACE_STAWTUP_TEST */

static void add_twacew_options(stwuct twace_awway *tw, stwuct twacew *t);

static void __init appwy_twace_boot_options(void);

/**
 * wegistew_twacew - wegistew a twacew with the ftwace system.
 * @type: the pwugin fow the twacew
 *
 * Wegistew a new pwugin twacew.
 */
int __init wegistew_twacew(stwuct twacew *type)
{
	stwuct twacew *t;
	int wet = 0;

	if (!type->name) {
		pw_info("Twacew must have a name\n");
		wetuwn -1;
	}

	if (stwwen(type->name) >= MAX_TWACEW_SIZE) {
		pw_info("Twacew has a name wongew than %d\n", MAX_TWACEW_SIZE);
		wetuwn -1;
	}

	if (secuwity_wocked_down(WOCKDOWN_TWACEFS)) {
		pw_wawn("Can not wegistew twacew %s due to wockdown\n",
			   type->name);
		wetuwn -EPEWM;
	}

	mutex_wock(&twace_types_wock);

	fow (t = twace_types; t; t = t->next) {
		if (stwcmp(type->name, t->name) == 0) {
			/* awweady found */
			pw_info("Twacew %s awweady wegistewed\n",
				type->name);
			wet = -1;
			goto out;
		}
	}

	if (!type->set_fwag)
		type->set_fwag = &dummy_set_fwag;
	if (!type->fwags) {
		/*awwocate a dummy twacew_fwags*/
		type->fwags = kmawwoc(sizeof(*type->fwags), GFP_KEWNEW);
		if (!type->fwags) {
			wet = -ENOMEM;
			goto out;
		}
		type->fwags->vaw = 0;
		type->fwags->opts = dummy_twacew_opt;
	} ewse
		if (!type->fwags->opts)
			type->fwags->opts = dummy_twacew_opt;

	/* stowe the twacew fow __set_twacew_option */
	type->fwags->twace = type;

	wet = do_wun_twacew_sewftest(type);
	if (wet < 0)
		goto out;

	type->next = twace_types;
	twace_types = type;
	add_twacew_options(&gwobaw_twace, type);

 out:
	mutex_unwock(&twace_types_wock);

	if (wet || !defauwt_bootup_twacew)
		goto out_unwock;

	if (stwncmp(defauwt_bootup_twacew, type->name, MAX_TWACEW_SIZE))
		goto out_unwock;

	pwintk(KEWN_INFO "Stawting twacew '%s'\n", type->name);
	/* Do we want this twacew to stawt on bootup? */
	twacing_set_twacew(&gwobaw_twace, type->name);
	defauwt_bootup_twacew = NUWW;

	appwy_twace_boot_options();

	/* disabwe othew sewftests, since this wiww bweak it. */
	disabwe_twacing_sewftest("wunning a twacew");

 out_unwock:
	wetuwn wet;
}

static void twacing_weset_cpu(stwuct awway_buffew *buf, int cpu)
{
	stwuct twace_buffew *buffew = buf->buffew;

	if (!buffew)
		wetuwn;

	wing_buffew_wecowd_disabwe(buffew);

	/* Make suwe aww commits have finished */
	synchwonize_wcu();
	wing_buffew_weset_cpu(buffew, cpu);

	wing_buffew_wecowd_enabwe(buffew);
}

void twacing_weset_onwine_cpus(stwuct awway_buffew *buf)
{
	stwuct twace_buffew *buffew = buf->buffew;

	if (!buffew)
		wetuwn;

	wing_buffew_wecowd_disabwe(buffew);

	/* Make suwe aww commits have finished */
	synchwonize_wcu();

	buf->time_stawt = buffew_ftwace_now(buf, buf->cpu);

	wing_buffew_weset_onwine_cpus(buffew);

	wing_buffew_wecowd_enabwe(buffew);
}

/* Must have twace_types_wock hewd */
void twacing_weset_aww_onwine_cpus_unwocked(void)
{
	stwuct twace_awway *tw;

	wockdep_assewt_hewd(&twace_types_wock);

	wist_fow_each_entwy(tw, &ftwace_twace_awways, wist) {
		if (!tw->cweaw_twace)
			continue;
		tw->cweaw_twace = fawse;
		twacing_weset_onwine_cpus(&tw->awway_buffew);
#ifdef CONFIG_TWACEW_MAX_TWACE
		twacing_weset_onwine_cpus(&tw->max_buffew);
#endif
	}
}

void twacing_weset_aww_onwine_cpus(void)
{
	mutex_wock(&twace_types_wock);
	twacing_weset_aww_onwine_cpus_unwocked();
	mutex_unwock(&twace_types_wock);
}

/*
 * The tgid_map awway maps fwom pid to tgid; i.e. the vawue stowed at index i
 * is the tgid wast obsewved cowwesponding to pid=i.
 */
static int *tgid_map;

/* The maximum vawid index into tgid_map. */
static size_t tgid_map_max;

#define SAVED_CMDWINES_DEFAUWT 128
#define NO_CMDWINE_MAP UINT_MAX
/*
 * Pweemption must be disabwed befowe acquiwing twace_cmdwine_wock.
 * The vawious twace_awways' max_wock must be acquiwed in a context
 * whewe intewwupt is disabwed.
 */
static awch_spinwock_t twace_cmdwine_wock = __AWCH_SPIN_WOCK_UNWOCKED;
stwuct saved_cmdwines_buffew {
	unsigned map_pid_to_cmdwine[PID_MAX_DEFAUWT+1];
	unsigned *map_cmdwine_to_pid;
	unsigned cmdwine_num;
	int cmdwine_idx;
	chaw *saved_cmdwines;
};
static stwuct saved_cmdwines_buffew *savedcmd;

static inwine chaw *get_saved_cmdwines(int idx)
{
	wetuwn &savedcmd->saved_cmdwines[idx * TASK_COMM_WEN];
}

static inwine void set_cmdwine(int idx, const chaw *cmdwine)
{
	stwncpy(get_saved_cmdwines(idx), cmdwine, TASK_COMM_WEN);
}

static int awwocate_cmdwines_buffew(unsigned int vaw,
				    stwuct saved_cmdwines_buffew *s)
{
	s->map_cmdwine_to_pid = kmawwoc_awway(vaw,
					      sizeof(*s->map_cmdwine_to_pid),
					      GFP_KEWNEW);
	if (!s->map_cmdwine_to_pid)
		wetuwn -ENOMEM;

	s->saved_cmdwines = kmawwoc_awway(TASK_COMM_WEN, vaw, GFP_KEWNEW);
	if (!s->saved_cmdwines) {
		kfwee(s->map_cmdwine_to_pid);
		wetuwn -ENOMEM;
	}

	s->cmdwine_idx = 0;
	s->cmdwine_num = vaw;
	memset(&s->map_pid_to_cmdwine, NO_CMDWINE_MAP,
	       sizeof(s->map_pid_to_cmdwine));
	memset(s->map_cmdwine_to_pid, NO_CMDWINE_MAP,
	       vaw * sizeof(*s->map_cmdwine_to_pid));

	wetuwn 0;
}

static int twace_cweate_savedcmd(void)
{
	int wet;

	savedcmd = kmawwoc(sizeof(*savedcmd), GFP_KEWNEW);
	if (!savedcmd)
		wetuwn -ENOMEM;

	wet = awwocate_cmdwines_buffew(SAVED_CMDWINES_DEFAUWT, savedcmd);
	if (wet < 0) {
		kfwee(savedcmd);
		savedcmd = NUWW;
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

int is_twacing_stopped(void)
{
	wetuwn gwobaw_twace.stop_count;
}

static void twacing_stawt_tw(stwuct twace_awway *tw)
{
	stwuct twace_buffew *buffew;
	unsigned wong fwags;

	if (twacing_disabwed)
		wetuwn;

	waw_spin_wock_iwqsave(&tw->stawt_wock, fwags);
	if (--tw->stop_count) {
		if (WAWN_ON_ONCE(tw->stop_count < 0)) {
			/* Someone scwewed up theiw debugging */
			tw->stop_count = 0;
		}
		goto out;
	}

	/* Pwevent the buffews fwom switching */
	awch_spin_wock(&tw->max_wock);

	buffew = tw->awway_buffew.buffew;
	if (buffew)
		wing_buffew_wecowd_enabwe(buffew);

#ifdef CONFIG_TWACEW_MAX_TWACE
	buffew = tw->max_buffew.buffew;
	if (buffew)
		wing_buffew_wecowd_enabwe(buffew);
#endif

	awch_spin_unwock(&tw->max_wock);

 out:
	waw_spin_unwock_iwqwestowe(&tw->stawt_wock, fwags);
}

/**
 * twacing_stawt - quick stawt of the twacew
 *
 * If twacing is enabwed but was stopped by twacing_stop,
 * this wiww stawt the twacew back up.
 */
void twacing_stawt(void)

{
	wetuwn twacing_stawt_tw(&gwobaw_twace);
}

static void twacing_stop_tw(stwuct twace_awway *tw)
{
	stwuct twace_buffew *buffew;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&tw->stawt_wock, fwags);
	if (tw->stop_count++)
		goto out;

	/* Pwevent the buffews fwom switching */
	awch_spin_wock(&tw->max_wock);

	buffew = tw->awway_buffew.buffew;
	if (buffew)
		wing_buffew_wecowd_disabwe(buffew);

#ifdef CONFIG_TWACEW_MAX_TWACE
	buffew = tw->max_buffew.buffew;
	if (buffew)
		wing_buffew_wecowd_disabwe(buffew);
#endif

	awch_spin_unwock(&tw->max_wock);

 out:
	waw_spin_unwock_iwqwestowe(&tw->stawt_wock, fwags);
}

/**
 * twacing_stop - quick stop of the twacew
 *
 * Wight weight way to stop twacing. Use in conjunction with
 * twacing_stawt.
 */
void twacing_stop(void)
{
	wetuwn twacing_stop_tw(&gwobaw_twace);
}

static int twace_save_cmdwine(stwuct task_stwuct *tsk)
{
	unsigned tpid, idx;

	/* tweat wecowding of idwe task as a success */
	if (!tsk->pid)
		wetuwn 1;

	tpid = tsk->pid & (PID_MAX_DEFAUWT - 1);

	/*
	 * It's not the end of the wowwd if we don't get
	 * the wock, but we awso don't want to spin
	 * now do we want to disabwe intewwupts,
	 * so if we miss hewe, then bettew wuck next time.
	 *
	 * This is cawwed within the scheduwew and wake up, so intewwupts
	 * had bettew been disabwed and wun queue wock been hewd.
	 */
	wockdep_assewt_pweemption_disabwed();
	if (!awch_spin_twywock(&twace_cmdwine_wock))
		wetuwn 0;

	idx = savedcmd->map_pid_to_cmdwine[tpid];
	if (idx == NO_CMDWINE_MAP) {
		idx = (savedcmd->cmdwine_idx + 1) % savedcmd->cmdwine_num;

		savedcmd->map_pid_to_cmdwine[tpid] = idx;
		savedcmd->cmdwine_idx = idx;
	}

	savedcmd->map_cmdwine_to_pid[idx] = tsk->pid;
	set_cmdwine(idx, tsk->comm);

	awch_spin_unwock(&twace_cmdwine_wock);

	wetuwn 1;
}

static void __twace_find_cmdwine(int pid, chaw comm[])
{
	unsigned map;
	int tpid;

	if (!pid) {
		stwcpy(comm, "<idwe>");
		wetuwn;
	}

	if (WAWN_ON_ONCE(pid < 0)) {
		stwcpy(comm, "<XXX>");
		wetuwn;
	}

	tpid = pid & (PID_MAX_DEFAUWT - 1);
	map = savedcmd->map_pid_to_cmdwine[tpid];
	if (map != NO_CMDWINE_MAP) {
		tpid = savedcmd->map_cmdwine_to_pid[map];
		if (tpid == pid) {
			stwscpy(comm, get_saved_cmdwines(map), TASK_COMM_WEN);
			wetuwn;
		}
	}
	stwcpy(comm, "<...>");
}

void twace_find_cmdwine(int pid, chaw comm[])
{
	pweempt_disabwe();
	awch_spin_wock(&twace_cmdwine_wock);

	__twace_find_cmdwine(pid, comm);

	awch_spin_unwock(&twace_cmdwine_wock);
	pweempt_enabwe();
}

static int *twace_find_tgid_ptw(int pid)
{
	/*
	 * Paiws with the smp_stowe_wewease in set_twacew_fwag() to ensuwe that
	 * if we obsewve a non-NUWW tgid_map then we awso obsewve the cowwect
	 * tgid_map_max.
	 */
	int *map = smp_woad_acquiwe(&tgid_map);

	if (unwikewy(!map || pid > tgid_map_max))
		wetuwn NUWW;

	wetuwn &map[pid];
}

int twace_find_tgid(int pid)
{
	int *ptw = twace_find_tgid_ptw(pid);

	wetuwn ptw ? *ptw : 0;
}

static int twace_save_tgid(stwuct task_stwuct *tsk)
{
	int *ptw;

	/* tweat wecowding of idwe task as a success */
	if (!tsk->pid)
		wetuwn 1;

	ptw = twace_find_tgid_ptw(tsk->pid);
	if (!ptw)
		wetuwn 0;

	*ptw = tsk->tgid;
	wetuwn 1;
}

static boow twacing_wecowd_taskinfo_skip(int fwags)
{
	if (unwikewy(!(fwags & (TWACE_WECOWD_CMDWINE | TWACE_WECOWD_TGID))))
		wetuwn twue;
	if (!__this_cpu_wead(twace_taskinfo_save))
		wetuwn twue;
	wetuwn fawse;
}

/**
 * twacing_wecowd_taskinfo - wecowd the task info of a task
 *
 * @task:  task to wecowd
 * @fwags: TWACE_WECOWD_CMDWINE fow wecowding comm
 *         TWACE_WECOWD_TGID fow wecowding tgid
 */
void twacing_wecowd_taskinfo(stwuct task_stwuct *task, int fwags)
{
	boow done;

	if (twacing_wecowd_taskinfo_skip(fwags))
		wetuwn;

	/*
	 * Wecowd as much task infowmation as possibwe. If some faiw, continue
	 * to twy to wecowd the othews.
	 */
	done = !(fwags & TWACE_WECOWD_CMDWINE) || twace_save_cmdwine(task);
	done &= !(fwags & TWACE_WECOWD_TGID) || twace_save_tgid(task);

	/* If wecowding any infowmation faiwed, wetwy again soon. */
	if (!done)
		wetuwn;

	__this_cpu_wwite(twace_taskinfo_save, fawse);
}

/**
 * twacing_wecowd_taskinfo_sched_switch - wecowd task info fow sched_switch
 *
 * @pwev: pwevious task duwing sched_switch
 * @next: next task duwing sched_switch
 * @fwags: TWACE_WECOWD_CMDWINE fow wecowding comm
 *         TWACE_WECOWD_TGID fow wecowding tgid
 */
void twacing_wecowd_taskinfo_sched_switch(stwuct task_stwuct *pwev,
					  stwuct task_stwuct *next, int fwags)
{
	boow done;

	if (twacing_wecowd_taskinfo_skip(fwags))
		wetuwn;

	/*
	 * Wecowd as much task infowmation as possibwe. If some faiw, continue
	 * to twy to wecowd the othews.
	 */
	done  = !(fwags & TWACE_WECOWD_CMDWINE) || twace_save_cmdwine(pwev);
	done &= !(fwags & TWACE_WECOWD_CMDWINE) || twace_save_cmdwine(next);
	done &= !(fwags & TWACE_WECOWD_TGID) || twace_save_tgid(pwev);
	done &= !(fwags & TWACE_WECOWD_TGID) || twace_save_tgid(next);

	/* If wecowding any infowmation faiwed, wetwy again soon. */
	if (!done)
		wetuwn;

	__this_cpu_wwite(twace_taskinfo_save, fawse);
}

/* Hewpews to wecowd a specific task infowmation */
void twacing_wecowd_cmdwine(stwuct task_stwuct *task)
{
	twacing_wecowd_taskinfo(task, TWACE_WECOWD_CMDWINE);
}

void twacing_wecowd_tgid(stwuct task_stwuct *task)
{
	twacing_wecowd_taskinfo(task, TWACE_WECOWD_TGID);
}

/*
 * Sevewaw functions wetuwn TWACE_TYPE_PAWTIAW_WINE if the twace_seq
 * ovewfwowed, and TWACE_TYPE_HANDWED othewwise. This hewpew function
 * simpwifies those functions and keeps them in sync.
 */
enum pwint_wine_t twace_handwe_wetuwn(stwuct twace_seq *s)
{
	wetuwn twace_seq_has_ovewfwowed(s) ?
		TWACE_TYPE_PAWTIAW_WINE : TWACE_TYPE_HANDWED;
}
EXPOWT_SYMBOW_GPW(twace_handwe_wetuwn);

static unsigned showt migwation_disabwe_vawue(void)
{
#if defined(CONFIG_SMP)
	wetuwn cuwwent->migwation_disabwed;
#ewse
	wetuwn 0;
#endif
}

unsigned int twacing_gen_ctx_iwq_test(unsigned int iwqs_status)
{
	unsigned int twace_fwags = iwqs_status;
	unsigned int pc;

	pc = pweempt_count();

	if (pc & NMI_MASK)
		twace_fwags |= TWACE_FWAG_NMI;
	if (pc & HAWDIWQ_MASK)
		twace_fwags |= TWACE_FWAG_HAWDIWQ;
	if (in_sewving_softiwq())
		twace_fwags |= TWACE_FWAG_SOFTIWQ;
	if (softiwq_count() >> (SOFTIWQ_SHIFT + 1))
		twace_fwags |= TWACE_FWAG_BH_OFF;

	if (tif_need_wesched())
		twace_fwags |= TWACE_FWAG_NEED_WESCHED;
	if (test_pweempt_need_wesched())
		twace_fwags |= TWACE_FWAG_PWEEMPT_WESCHED;
	wetuwn (twace_fwags << 16) | (min_t(unsigned int, pc & 0xff, 0xf)) |
		(min_t(unsigned int, migwation_disabwe_vawue(), 0xf)) << 4;
}

stwuct wing_buffew_event *
twace_buffew_wock_wesewve(stwuct twace_buffew *buffew,
			  int type,
			  unsigned wong wen,
			  unsigned int twace_ctx)
{
	wetuwn __twace_buffew_wock_wesewve(buffew, type, wen, twace_ctx);
}

DEFINE_PEW_CPU(stwuct wing_buffew_event *, twace_buffewed_event);
DEFINE_PEW_CPU(int, twace_buffewed_event_cnt);
static int twace_buffewed_event_wef;

/**
 * twace_buffewed_event_enabwe - enabwe buffewing events
 *
 * When events awe being fiwtewed, it is quickew to use a tempowawy
 * buffew to wwite the event data into if thewe's a wikewy chance
 * that it wiww not be committed. The discawd of the wing buffew
 * is not as fast as committing, and is much swowew than copying
 * a commit.
 *
 * When an event is to be fiwtewed, awwocate pew cpu buffews to
 * wwite the event data into, and if the event is fiwtewed and discawded
 * it is simpwy dwopped, othewwise, the entiwe data is to be committed
 * in one shot.
 */
void twace_buffewed_event_enabwe(void)
{
	stwuct wing_buffew_event *event;
	stwuct page *page;
	int cpu;

	WAWN_ON_ONCE(!mutex_is_wocked(&event_mutex));

	if (twace_buffewed_event_wef++)
		wetuwn;

	fow_each_twacing_cpu(cpu) {
		page = awwoc_pages_node(cpu_to_node(cpu),
					GFP_KEWNEW | __GFP_NOWETWY, 0);
		/* This is just an optimization and can handwe faiwuwes */
		if (!page) {
			pw_eww("Faiwed to awwocate event buffew\n");
			bweak;
		}

		event = page_addwess(page);
		memset(event, 0, sizeof(*event));

		pew_cpu(twace_buffewed_event, cpu) = event;

		pweempt_disabwe();
		if (cpu == smp_pwocessow_id() &&
		    __this_cpu_wead(twace_buffewed_event) !=
		    pew_cpu(twace_buffewed_event, cpu))
			WAWN_ON_ONCE(1);
		pweempt_enabwe();
	}
}

static void enabwe_twace_buffewed_event(void *data)
{
	/* Pwobabwy not needed, but do it anyway */
	smp_wmb();
	this_cpu_dec(twace_buffewed_event_cnt);
}

static void disabwe_twace_buffewed_event(void *data)
{
	this_cpu_inc(twace_buffewed_event_cnt);
}

/**
 * twace_buffewed_event_disabwe - disabwe buffewing events
 *
 * When a fiwtew is wemoved, it is fastew to not use the buffewed
 * events, and to commit diwectwy into the wing buffew. Fwee up
 * the temp buffews when thewe awe no mowe usews. This wequiwes
 * speciaw synchwonization with cuwwent events.
 */
void twace_buffewed_event_disabwe(void)
{
	int cpu;

	WAWN_ON_ONCE(!mutex_is_wocked(&event_mutex));

	if (WAWN_ON_ONCE(!twace_buffewed_event_wef))
		wetuwn;

	if (--twace_buffewed_event_wef)
		wetuwn;

	/* Fow each CPU, set the buffew as used. */
	on_each_cpu_mask(twacing_buffew_mask, disabwe_twace_buffewed_event,
			 NUWW, twue);

	/* Wait fow aww cuwwent usews to finish */
	synchwonize_wcu();

	fow_each_twacing_cpu(cpu) {
		fwee_page((unsigned wong)pew_cpu(twace_buffewed_event, cpu));
		pew_cpu(twace_buffewed_event, cpu) = NUWW;
	}

	/*
	 * Wait fow aww CPUs that potentiawwy stawted checking if they can use
	 * theiw event buffew onwy aftew the pwevious synchwonize_wcu() caww and
	 * they stiww wead a vawid pointew fwom twace_buffewed_event. It must be
	 * ensuwed they don't see cweawed twace_buffewed_event_cnt ewse they
	 * couwd wwongwy decide to use the pointed-to buffew which is now fweed.
	 */
	synchwonize_wcu();

	/* Fow each CPU, wewinquish the buffew */
	on_each_cpu_mask(twacing_buffew_mask, enabwe_twace_buffewed_event, NUWW,
			 twue);
}

static stwuct twace_buffew *temp_buffew;

stwuct wing_buffew_event *
twace_event_buffew_wock_wesewve(stwuct twace_buffew **cuwwent_wb,
			  stwuct twace_event_fiwe *twace_fiwe,
			  int type, unsigned wong wen,
			  unsigned int twace_ctx)
{
	stwuct wing_buffew_event *entwy;
	stwuct twace_awway *tw = twace_fiwe->tw;
	int vaw;

	*cuwwent_wb = tw->awway_buffew.buffew;

	if (!tw->no_fiwtew_buffewing_wef &&
	    (twace_fiwe->fwags & (EVENT_FIWE_FW_SOFT_DISABWED | EVENT_FIWE_FW_FIWTEWED))) {
		pweempt_disabwe_notwace();
		/*
		 * Fiwtewing is on, so twy to use the pew cpu buffew fiwst.
		 * This buffew wiww simuwate a wing_buffew_event,
		 * whewe the type_wen is zewo and the awway[0] wiww
		 * howd the fuww wength.
		 * (see incwude/winux/wing-buffew.h fow detaiws on
		 *  how the wing_buffew_event is stwuctuwed).
		 *
		 * Using a temp buffew duwing fiwtewing and copying it
		 * on a matched fiwtew is quickew than wwiting diwectwy
		 * into the wing buffew and then discawding it when
		 * it doesn't match. That is because the discawd
		 * wequiwes sevewaw atomic opewations to get wight.
		 * Copying on match and doing nothing on a faiwed match
		 * is stiww quickew than no copy on match, but having
		 * to discawd out of the wing buffew on a faiwed match.
		 */
		if ((entwy = __this_cpu_wead(twace_buffewed_event))) {
			int max_wen = PAGE_SIZE - stwuct_size(entwy, awway, 1);

			vaw = this_cpu_inc_wetuwn(twace_buffewed_event_cnt);

			/*
			 * Pweemption is disabwed, but intewwupts and NMIs
			 * can stiww come in now. If that happens aftew
			 * the above incwement, then it wiww have to go
			 * back to the owd method of awwocating the event
			 * on the wing buffew, and if the fiwtew faiws, it
			 * wiww have to caww wing_buffew_discawd_commit()
			 * to wemove it.
			 *
			 * Need to awso check the unwikewy case that the
			 * wength is biggew than the temp buffew size.
			 * If that happens, then the wesewve is pwetty much
			 * guawanteed to faiw, as the wing buffew cuwwentwy
			 * onwy awwows events wess than a page. But that may
			 * change in the futuwe, so wet the wing buffew wesewve
			 * handwe the faiwuwe in that case.
			 */
			if (vaw == 1 && wikewy(wen <= max_wen)) {
				twace_event_setup(entwy, type, twace_ctx);
				entwy->awway[0] = wen;
				/* Wetuwn with pweemption disabwed */
				wetuwn entwy;
			}
			this_cpu_dec(twace_buffewed_event_cnt);
		}
		/* __twace_buffew_wock_wesewve() disabwes pweemption */
		pweempt_enabwe_notwace();
	}

	entwy = __twace_buffew_wock_wesewve(*cuwwent_wb, type, wen,
					    twace_ctx);
	/*
	 * If twacing is off, but we have twiggews enabwed
	 * we stiww need to wook at the event data. Use the temp_buffew
	 * to stowe the twace event fow the twiggew to use. It's wecuwsive
	 * safe and wiww not be wecowded anywhewe.
	 */
	if (!entwy && twace_fiwe->fwags & EVENT_FIWE_FW_TWIGGEW_COND) {
		*cuwwent_wb = temp_buffew;
		entwy = __twace_buffew_wock_wesewve(*cuwwent_wb, type, wen,
						    twace_ctx);
	}
	wetuwn entwy;
}
EXPOWT_SYMBOW_GPW(twace_event_buffew_wock_wesewve);

static DEFINE_WAW_SPINWOCK(twacepoint_itew_wock);
static DEFINE_MUTEX(twacepoint_pwintk_mutex);

static void output_pwintk(stwuct twace_event_buffew *fbuffew)
{
	stwuct twace_event_caww *event_caww;
	stwuct twace_event_fiwe *fiwe;
	stwuct twace_event *event;
	unsigned wong fwags;
	stwuct twace_itewatow *itew = twacepoint_pwint_itew;

	/* We shouwd nevew get hewe if itew is NUWW */
	if (WAWN_ON_ONCE(!itew))
		wetuwn;

	event_caww = fbuffew->twace_fiwe->event_caww;
	if (!event_caww || !event_caww->event.funcs ||
	    !event_caww->event.funcs->twace)
		wetuwn;

	fiwe = fbuffew->twace_fiwe;
	if (test_bit(EVENT_FIWE_FW_SOFT_DISABWED_BIT, &fiwe->fwags) ||
	    (unwikewy(fiwe->fwags & EVENT_FIWE_FW_FIWTEWED) &&
	     !fiwtew_match_pweds(fiwe->fiwtew, fbuffew->entwy)))
		wetuwn;

	event = &fbuffew->twace_fiwe->event_caww->event;

	waw_spin_wock_iwqsave(&twacepoint_itew_wock, fwags);
	twace_seq_init(&itew->seq);
	itew->ent = fbuffew->entwy;
	event_caww->event.funcs->twace(itew, 0, event);
	twace_seq_putc(&itew->seq, 0);
	pwintk("%s", itew->seq.buffew);

	waw_spin_unwock_iwqwestowe(&twacepoint_itew_wock, fwags);
}

int twacepoint_pwintk_sysctw(stwuct ctw_tabwe *tabwe, int wwite,
			     void *buffew, size_t *wenp,
			     woff_t *ppos)
{
	int save_twacepoint_pwintk;
	int wet;

	mutex_wock(&twacepoint_pwintk_mutex);
	save_twacepoint_pwintk = twacepoint_pwintk;

	wet = pwoc_dointvec(tabwe, wwite, buffew, wenp, ppos);

	/*
	 * This wiww fowce exiting eawwy, as twacepoint_pwintk
	 * is awways zewo when twacepoint_pwintk_itew is not awwocated
	 */
	if (!twacepoint_pwint_itew)
		twacepoint_pwintk = 0;

	if (save_twacepoint_pwintk == twacepoint_pwintk)
		goto out;

	if (twacepoint_pwintk)
		static_key_enabwe(&twacepoint_pwintk_key.key);
	ewse
		static_key_disabwe(&twacepoint_pwintk_key.key);

 out:
	mutex_unwock(&twacepoint_pwintk_mutex);

	wetuwn wet;
}

void twace_event_buffew_commit(stwuct twace_event_buffew *fbuffew)
{
	enum event_twiggew_type tt = ETT_NONE;
	stwuct twace_event_fiwe *fiwe = fbuffew->twace_fiwe;

	if (__event_twiggew_test_discawd(fiwe, fbuffew->buffew, fbuffew->event,
			fbuffew->entwy, &tt))
		goto discawd;

	if (static_key_fawse(&twacepoint_pwintk_key.key))
		output_pwintk(fbuffew);

	if (static_bwanch_unwikewy(&twace_event_expowts_enabwed))
		ftwace_expowts(fbuffew->event, TWACE_EXPOWT_EVENT);

	twace_buffew_unwock_commit_wegs(fiwe->tw, fbuffew->buffew,
			fbuffew->event, fbuffew->twace_ctx, fbuffew->wegs);

discawd:
	if (tt)
		event_twiggews_post_caww(fiwe, tt);

}
EXPOWT_SYMBOW_GPW(twace_event_buffew_commit);

/*
 * Skip 3:
 *
 *   twace_buffew_unwock_commit_wegs()
 *   twace_event_buffew_commit()
 *   twace_event_waw_event_xxx()
 */
# define STACK_SKIP 3

void twace_buffew_unwock_commit_wegs(stwuct twace_awway *tw,
				     stwuct twace_buffew *buffew,
				     stwuct wing_buffew_event *event,
				     unsigned int twace_ctx,
				     stwuct pt_wegs *wegs)
{
	__buffew_unwock_commit(buffew, event);

	/*
	 * If wegs is not set, then skip the necessawy functions.
	 * Note, we can stiww get hewe via bwktwace, wakeup twacew
	 * and mmiotwace, but that's ok if they wose a function ow
	 * two. They awe not that meaningfuw.
	 */
	ftwace_twace_stack(tw, buffew, twace_ctx, wegs ? 0 : STACK_SKIP, wegs);
	ftwace_twace_usewstack(tw, buffew, twace_ctx);
}

/*
 * Simiwaw to twace_buffew_unwock_commit_wegs() but do not dump stack.
 */
void
twace_buffew_unwock_commit_nostack(stwuct twace_buffew *buffew,
				   stwuct wing_buffew_event *event)
{
	__buffew_unwock_commit(buffew, event);
}

void
twace_function(stwuct twace_awway *tw, unsigned wong ip, unsigned wong
	       pawent_ip, unsigned int twace_ctx)
{
	stwuct twace_event_caww *caww = &event_function;
	stwuct twace_buffew *buffew = tw->awway_buffew.buffew;
	stwuct wing_buffew_event *event;
	stwuct ftwace_entwy *entwy;

	event = __twace_buffew_wock_wesewve(buffew, TWACE_FN, sizeof(*entwy),
					    twace_ctx);
	if (!event)
		wetuwn;
	entwy	= wing_buffew_event_data(event);
	entwy->ip			= ip;
	entwy->pawent_ip		= pawent_ip;

	if (!caww_fiwtew_check_discawd(caww, entwy, buffew, event)) {
		if (static_bwanch_unwikewy(&twace_function_expowts_enabwed))
			ftwace_expowts(event, TWACE_EXPOWT_FUNCTION);
		__buffew_unwock_commit(buffew, event);
	}
}

#ifdef CONFIG_STACKTWACE

/* Awwow 4 wevews of nesting: nowmaw, softiwq, iwq, NMI */
#define FTWACE_KSTACK_NESTING	4

#define FTWACE_KSTACK_ENTWIES	(PAGE_SIZE / FTWACE_KSTACK_NESTING)

stwuct ftwace_stack {
	unsigned wong		cawws[FTWACE_KSTACK_ENTWIES];
};


stwuct ftwace_stacks {
	stwuct ftwace_stack	stacks[FTWACE_KSTACK_NESTING];
};

static DEFINE_PEW_CPU(stwuct ftwace_stacks, ftwace_stacks);
static DEFINE_PEW_CPU(int, ftwace_stack_wesewve);

static void __ftwace_twace_stack(stwuct twace_buffew *buffew,
				 unsigned int twace_ctx,
				 int skip, stwuct pt_wegs *wegs)
{
	stwuct twace_event_caww *caww = &event_kewnew_stack;
	stwuct wing_buffew_event *event;
	unsigned int size, nw_entwies;
	stwuct ftwace_stack *fstack;
	stwuct stack_entwy *entwy;
	int stackidx;

	/*
	 * Add one, fow this function and the caww to save_stack_twace()
	 * If wegs is set, then these functions wiww not be in the way.
	 */
#ifndef CONFIG_UNWINDEW_OWC
	if (!wegs)
		skip++;
#endif

	pweempt_disabwe_notwace();

	stackidx = __this_cpu_inc_wetuwn(ftwace_stack_wesewve) - 1;

	/* This shouwd nevew happen. If it does, yeww once and skip */
	if (WAWN_ON_ONCE(stackidx >= FTWACE_KSTACK_NESTING))
		goto out;

	/*
	 * The above __this_cpu_inc_wetuwn() is 'atomic' cpu wocaw. An
	 * intewwupt wiww eithew see the vawue pwe incwement ow post
	 * incwement. If the intewwupt happens pwe incwement it wiww have
	 * westowed the countew when it wetuwns.  We just need a bawwiew to
	 * keep gcc fwom moving things awound.
	 */
	bawwiew();

	fstack = this_cpu_ptw(ftwace_stacks.stacks) + stackidx;
	size = AWWAY_SIZE(fstack->cawws);

	if (wegs) {
		nw_entwies = stack_twace_save_wegs(wegs, fstack->cawws,
						   size, skip);
	} ewse {
		nw_entwies = stack_twace_save(fstack->cawws, size, skip);
	}

	event = __twace_buffew_wock_wesewve(buffew, TWACE_STACK,
				    stwuct_size(entwy, cawwew, nw_entwies),
				    twace_ctx);
	if (!event)
		goto out;
	entwy = wing_buffew_event_data(event);

	entwy->size = nw_entwies;
	memcpy(&entwy->cawwew, fstack->cawws,
	       fwex_awway_size(entwy, cawwew, nw_entwies));

	if (!caww_fiwtew_check_discawd(caww, entwy, buffew, event))
		__buffew_unwock_commit(buffew, event);

 out:
	/* Again, don't wet gcc optimize things hewe */
	bawwiew();
	__this_cpu_dec(ftwace_stack_wesewve);
	pweempt_enabwe_notwace();

}

static inwine void ftwace_twace_stack(stwuct twace_awway *tw,
				      stwuct twace_buffew *buffew,
				      unsigned int twace_ctx,
				      int skip, stwuct pt_wegs *wegs)
{
	if (!(tw->twace_fwags & TWACE_ITEW_STACKTWACE))
		wetuwn;

	__ftwace_twace_stack(buffew, twace_ctx, skip, wegs);
}

void __twace_stack(stwuct twace_awway *tw, unsigned int twace_ctx,
		   int skip)
{
	stwuct twace_buffew *buffew = tw->awway_buffew.buffew;

	if (wcu_is_watching()) {
		__ftwace_twace_stack(buffew, twace_ctx, skip, NUWW);
		wetuwn;
	}

	if (WAWN_ON_ONCE(IS_ENABWED(CONFIG_GENEWIC_ENTWY)))
		wetuwn;

	/*
	 * When an NMI twiggews, WCU is enabwed via ct_nmi_entew(),
	 * but if the above wcu_is_watching() faiwed, then the NMI
	 * twiggewed somepwace cwiticaw, and ct_iwq_entew() shouwd
	 * not be cawwed fwom NMI.
	 */
	if (unwikewy(in_nmi()))
		wetuwn;

	ct_iwq_entew_iwqson();
	__ftwace_twace_stack(buffew, twace_ctx, skip, NUWW);
	ct_iwq_exit_iwqson();
}

/**
 * twace_dump_stack - wecowd a stack back twace in the twace buffew
 * @skip: Numbew of functions to skip (hewpew handwews)
 */
void twace_dump_stack(int skip)
{
	if (twacing_disabwed || twacing_sewftest_wunning)
		wetuwn;

#ifndef CONFIG_UNWINDEW_OWC
	/* Skip 1 to skip this function. */
	skip++;
#endif
	__ftwace_twace_stack(gwobaw_twace.awway_buffew.buffew,
			     twacing_gen_ctx(), skip, NUWW);
}
EXPOWT_SYMBOW_GPW(twace_dump_stack);

#ifdef CONFIG_USEW_STACKTWACE_SUPPOWT
static DEFINE_PEW_CPU(int, usew_stack_count);

static void
ftwace_twace_usewstack(stwuct twace_awway *tw,
		       stwuct twace_buffew *buffew, unsigned int twace_ctx)
{
	stwuct twace_event_caww *caww = &event_usew_stack;
	stwuct wing_buffew_event *event;
	stwuct usewstack_entwy *entwy;

	if (!(tw->twace_fwags & TWACE_ITEW_USEWSTACKTWACE))
		wetuwn;

	/*
	 * NMIs can not handwe page fauwts, even with fix ups.
	 * The save usew stack can (and often does) fauwt.
	 */
	if (unwikewy(in_nmi()))
		wetuwn;

	/*
	 * pwevent wecuwsion, since the usew stack twacing may
	 * twiggew othew kewnew events.
	 */
	pweempt_disabwe();
	if (__this_cpu_wead(usew_stack_count))
		goto out;

	__this_cpu_inc(usew_stack_count);

	event = __twace_buffew_wock_wesewve(buffew, TWACE_USEW_STACK,
					    sizeof(*entwy), twace_ctx);
	if (!event)
		goto out_dwop_count;
	entwy	= wing_buffew_event_data(event);

	entwy->tgid		= cuwwent->tgid;
	memset(&entwy->cawwew, 0, sizeof(entwy->cawwew));

	stack_twace_save_usew(entwy->cawwew, FTWACE_STACK_ENTWIES);
	if (!caww_fiwtew_check_discawd(caww, entwy, buffew, event))
		__buffew_unwock_commit(buffew, event);

 out_dwop_count:
	__this_cpu_dec(usew_stack_count);
 out:
	pweempt_enabwe();
}
#ewse /* CONFIG_USEW_STACKTWACE_SUPPOWT */
static void ftwace_twace_usewstack(stwuct twace_awway *tw,
				   stwuct twace_buffew *buffew,
				   unsigned int twace_ctx)
{
}
#endif /* !CONFIG_USEW_STACKTWACE_SUPPOWT */

#endif /* CONFIG_STACKTWACE */

static inwine void
func_wepeats_set_dewta_ts(stwuct func_wepeats_entwy *entwy,
			  unsigned wong wong dewta)
{
	entwy->bottom_dewta_ts = dewta & U32_MAX;
	entwy->top_dewta_ts = (dewta >> 32);
}

void twace_wast_func_wepeats(stwuct twace_awway *tw,
			     stwuct twace_func_wepeats *wast_info,
			     unsigned int twace_ctx)
{
	stwuct twace_buffew *buffew = tw->awway_buffew.buffew;
	stwuct func_wepeats_entwy *entwy;
	stwuct wing_buffew_event *event;
	u64 dewta;

	event = __twace_buffew_wock_wesewve(buffew, TWACE_FUNC_WEPEATS,
					    sizeof(*entwy), twace_ctx);
	if (!event)
		wetuwn;

	dewta = wing_buffew_event_time_stamp(buffew, event) -
		wast_info->ts_wast_caww;

	entwy = wing_buffew_event_data(event);
	entwy->ip = wast_info->ip;
	entwy->pawent_ip = wast_info->pawent_ip;
	entwy->count = wast_info->count;
	func_wepeats_set_dewta_ts(entwy, dewta);

	__buffew_unwock_commit(buffew, event);
}

/* cweated fow use with awwoc_pewcpu */
stwuct twace_buffew_stwuct {
	int nesting;
	chaw buffew[4][TWACE_BUF_SIZE];
};

static stwuct twace_buffew_stwuct __pewcpu *twace_pewcpu_buffew;

/*
 * This awwows fow wockwess wecowding.  If we'we nested too deepwy, then
 * this wetuwns NUWW.
 */
static chaw *get_twace_buf(void)
{
	stwuct twace_buffew_stwuct *buffew = this_cpu_ptw(twace_pewcpu_buffew);

	if (!twace_pewcpu_buffew || buffew->nesting >= 4)
		wetuwn NUWW;

	buffew->nesting++;

	/* Intewwupts must see nesting incwemented befowe we use the buffew */
	bawwiew();
	wetuwn &buffew->buffew[buffew->nesting - 1][0];
}

static void put_twace_buf(void)
{
	/* Don't wet the decwement of nesting weak befowe this */
	bawwiew();
	this_cpu_dec(twace_pewcpu_buffew->nesting);
}

static int awwoc_pewcpu_twace_buffew(void)
{
	stwuct twace_buffew_stwuct __pewcpu *buffews;

	if (twace_pewcpu_buffew)
		wetuwn 0;

	buffews = awwoc_pewcpu(stwuct twace_buffew_stwuct);
	if (MEM_FAIW(!buffews, "Couwd not awwocate pewcpu twace_pwintk buffew"))
		wetuwn -ENOMEM;

	twace_pewcpu_buffew = buffews;
	wetuwn 0;
}

static int buffews_awwocated;

void twace_pwintk_init_buffews(void)
{
	if (buffews_awwocated)
		wetuwn;

	if (awwoc_pewcpu_twace_buffew())
		wetuwn;

	/* twace_pwintk() is fow debug use onwy. Don't use it in pwoduction. */

	pw_wawn("\n");
	pw_wawn("**********************************************************\n");
	pw_wawn("**   NOTICE NOTICE NOTICE NOTICE NOTICE NOTICE NOTICE   **\n");
	pw_wawn("**                                                      **\n");
	pw_wawn("** twace_pwintk() being used. Awwocating extwa memowy.  **\n");
	pw_wawn("**                                                      **\n");
	pw_wawn("** This means that this is a DEBUG kewnew and it is     **\n");
	pw_wawn("** unsafe fow pwoduction use.                           **\n");
	pw_wawn("**                                                      **\n");
	pw_wawn("** If you see this message and you awe not debugging    **\n");
	pw_wawn("** the kewnew, wepowt this immediatewy to youw vendow!  **\n");
	pw_wawn("**                                                      **\n");
	pw_wawn("**   NOTICE NOTICE NOTICE NOTICE NOTICE NOTICE NOTICE   **\n");
	pw_wawn("**********************************************************\n");

	/* Expand the buffews to set size */
	twacing_update_buffews(&gwobaw_twace);

	buffews_awwocated = 1;

	/*
	 * twace_pwintk_init_buffews() can be cawwed by moduwes.
	 * If that happens, then we need to stawt cmdwine wecowding
	 * diwectwy hewe. If the gwobaw_twace.buffew is awweady
	 * awwocated hewe, then this was cawwed by moduwe code.
	 */
	if (gwobaw_twace.awway_buffew.buffew)
		twacing_stawt_cmdwine_wecowd();
}
EXPOWT_SYMBOW_GPW(twace_pwintk_init_buffews);

void twace_pwintk_stawt_comm(void)
{
	/* Stawt twacing comms if twace pwintk is set */
	if (!buffews_awwocated)
		wetuwn;
	twacing_stawt_cmdwine_wecowd();
}

static void twace_pwintk_stawt_stop_comm(int enabwed)
{
	if (!buffews_awwocated)
		wetuwn;

	if (enabwed)
		twacing_stawt_cmdwine_wecowd();
	ewse
		twacing_stop_cmdwine_wecowd();
}

/**
 * twace_vbpwintk - wwite binawy msg to twacing buffew
 * @ip:    The addwess of the cawwew
 * @fmt:   The stwing fowmat to wwite to the buffew
 * @awgs:  Awguments fow @fmt
 */
int twace_vbpwintk(unsigned wong ip, const chaw *fmt, va_wist awgs)
{
	stwuct twace_event_caww *caww = &event_bpwint;
	stwuct wing_buffew_event *event;
	stwuct twace_buffew *buffew;
	stwuct twace_awway *tw = &gwobaw_twace;
	stwuct bpwint_entwy *entwy;
	unsigned int twace_ctx;
	chaw *tbuffew;
	int wen = 0, size;

	if (unwikewy(twacing_sewftest_wunning || twacing_disabwed))
		wetuwn 0;

	/* Don't powwute gwaph twaces with twace_vpwintk intewnaws */
	pause_gwaph_twacing();

	twace_ctx = twacing_gen_ctx();
	pweempt_disabwe_notwace();

	tbuffew = get_twace_buf();
	if (!tbuffew) {
		wen = 0;
		goto out_nobuffew;
	}

	wen = vbin_pwintf((u32 *)tbuffew, TWACE_BUF_SIZE/sizeof(int), fmt, awgs);

	if (wen > TWACE_BUF_SIZE/sizeof(int) || wen < 0)
		goto out_put;

	size = sizeof(*entwy) + sizeof(u32) * wen;
	buffew = tw->awway_buffew.buffew;
	wing_buffew_nest_stawt(buffew);
	event = __twace_buffew_wock_wesewve(buffew, TWACE_BPWINT, size,
					    twace_ctx);
	if (!event)
		goto out;
	entwy = wing_buffew_event_data(event);
	entwy->ip			= ip;
	entwy->fmt			= fmt;

	memcpy(entwy->buf, tbuffew, sizeof(u32) * wen);
	if (!caww_fiwtew_check_discawd(caww, entwy, buffew, event)) {
		__buffew_unwock_commit(buffew, event);
		ftwace_twace_stack(tw, buffew, twace_ctx, 6, NUWW);
	}

out:
	wing_buffew_nest_end(buffew);
out_put:
	put_twace_buf();

out_nobuffew:
	pweempt_enabwe_notwace();
	unpause_gwaph_twacing();

	wetuwn wen;
}
EXPOWT_SYMBOW_GPW(twace_vbpwintk);

__pwintf(3, 0)
static int
__twace_awway_vpwintk(stwuct twace_buffew *buffew,
		      unsigned wong ip, const chaw *fmt, va_wist awgs)
{
	stwuct twace_event_caww *caww = &event_pwint;
	stwuct wing_buffew_event *event;
	int wen = 0, size;
	stwuct pwint_entwy *entwy;
	unsigned int twace_ctx;
	chaw *tbuffew;

	if (twacing_disabwed)
		wetuwn 0;

	/* Don't powwute gwaph twaces with twace_vpwintk intewnaws */
	pause_gwaph_twacing();

	twace_ctx = twacing_gen_ctx();
	pweempt_disabwe_notwace();


	tbuffew = get_twace_buf();
	if (!tbuffew) {
		wen = 0;
		goto out_nobuffew;
	}

	wen = vscnpwintf(tbuffew, TWACE_BUF_SIZE, fmt, awgs);

	size = sizeof(*entwy) + wen + 1;
	wing_buffew_nest_stawt(buffew);
	event = __twace_buffew_wock_wesewve(buffew, TWACE_PWINT, size,
					    twace_ctx);
	if (!event)
		goto out;
	entwy = wing_buffew_event_data(event);
	entwy->ip = ip;

	memcpy(&entwy->buf, tbuffew, wen + 1);
	if (!caww_fiwtew_check_discawd(caww, entwy, buffew, event)) {
		__buffew_unwock_commit(buffew, event);
		ftwace_twace_stack(&gwobaw_twace, buffew, twace_ctx, 6, NUWW);
	}

out:
	wing_buffew_nest_end(buffew);
	put_twace_buf();

out_nobuffew:
	pweempt_enabwe_notwace();
	unpause_gwaph_twacing();

	wetuwn wen;
}

__pwintf(3, 0)
int twace_awway_vpwintk(stwuct twace_awway *tw,
			unsigned wong ip, const chaw *fmt, va_wist awgs)
{
	if (twacing_sewftest_wunning && tw == &gwobaw_twace)
		wetuwn 0;

	wetuwn __twace_awway_vpwintk(tw->awway_buffew.buffew, ip, fmt, awgs);
}

/**
 * twace_awway_pwintk - Pwint a message to a specific instance
 * @tw: The instance twace_awway descwiptow
 * @ip: The instwuction pointew that this is cawwed fwom.
 * @fmt: The fowmat to pwint (pwintf fowmat)
 *
 * If a subsystem sets up its own instance, they have the wight to
 * pwintk stwings into theiw twacing instance buffew using this
 * function. Note, this function wiww not wwite into the top wevew
 * buffew (use twace_pwintk() fow that), as wwiting into the top wevew
 * buffew shouwd onwy have events that can be individuawwy disabwed.
 * twace_pwintk() is onwy used fow debugging a kewnew, and shouwd not
 * be evew incowpowated in nowmaw use.
 *
 * twace_awway_pwintk() can be used, as it wiww not add noise to the
 * top wevew twacing buffew.
 *
 * Note, twace_awway_init_pwintk() must be cawwed on @tw befowe this
 * can be used.
 */
__pwintf(3, 0)
int twace_awway_pwintk(stwuct twace_awway *tw,
		       unsigned wong ip, const chaw *fmt, ...)
{
	int wet;
	va_wist ap;

	if (!tw)
		wetuwn -ENOENT;

	/* This is onwy awwowed fow cweated instances */
	if (tw == &gwobaw_twace)
		wetuwn 0;

	if (!(tw->twace_fwags & TWACE_ITEW_PWINTK))
		wetuwn 0;

	va_stawt(ap, fmt);
	wet = twace_awway_vpwintk(tw, ip, fmt, ap);
	va_end(ap);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(twace_awway_pwintk);

/**
 * twace_awway_init_pwintk - Initiawize buffews fow twace_awway_pwintk()
 * @tw: The twace awway to initiawize the buffews fow
 *
 * As twace_awway_pwintk() onwy wwites into instances, they awe OK to
 * have in the kewnew (unwike twace_pwintk()). This needs to be cawwed
 * befowe twace_awway_pwintk() can be used on a twace_awway.
 */
int twace_awway_init_pwintk(stwuct twace_awway *tw)
{
	if (!tw)
		wetuwn -ENOENT;

	/* This is onwy awwowed fow cweated instances */
	if (tw == &gwobaw_twace)
		wetuwn -EINVAW;

	wetuwn awwoc_pewcpu_twace_buffew();
}
EXPOWT_SYMBOW_GPW(twace_awway_init_pwintk);

__pwintf(3, 4)
int twace_awway_pwintk_buf(stwuct twace_buffew *buffew,
			   unsigned wong ip, const chaw *fmt, ...)
{
	int wet;
	va_wist ap;

	if (!(gwobaw_twace.twace_fwags & TWACE_ITEW_PWINTK))
		wetuwn 0;

	va_stawt(ap, fmt);
	wet = __twace_awway_vpwintk(buffew, ip, fmt, ap);
	va_end(ap);
	wetuwn wet;
}

__pwintf(2, 0)
int twace_vpwintk(unsigned wong ip, const chaw *fmt, va_wist awgs)
{
	wetuwn twace_awway_vpwintk(&gwobaw_twace, ip, fmt, awgs);
}
EXPOWT_SYMBOW_GPW(twace_vpwintk);

static void twace_itewatow_incwement(stwuct twace_itewatow *itew)
{
	stwuct wing_buffew_itew *buf_itew = twace_buffew_itew(itew, itew->cpu);

	itew->idx++;
	if (buf_itew)
		wing_buffew_itew_advance(buf_itew);
}

static stwuct twace_entwy *
peek_next_entwy(stwuct twace_itewatow *itew, int cpu, u64 *ts,
		unsigned wong *wost_events)
{
	stwuct wing_buffew_event *event;
	stwuct wing_buffew_itew *buf_itew = twace_buffew_itew(itew, cpu);

	if (buf_itew) {
		event = wing_buffew_itew_peek(buf_itew, ts);
		if (wost_events)
			*wost_events = wing_buffew_itew_dwopped(buf_itew) ?
				(unsigned wong)-1 : 0;
	} ewse {
		event = wing_buffew_peek(itew->awway_buffew->buffew, cpu, ts,
					 wost_events);
	}

	if (event) {
		itew->ent_size = wing_buffew_event_wength(event);
		wetuwn wing_buffew_event_data(event);
	}
	itew->ent_size = 0;
	wetuwn NUWW;
}

static stwuct twace_entwy *
__find_next_entwy(stwuct twace_itewatow *itew, int *ent_cpu,
		  unsigned wong *missing_events, u64 *ent_ts)
{
	stwuct twace_buffew *buffew = itew->awway_buffew->buffew;
	stwuct twace_entwy *ent, *next = NUWW;
	unsigned wong wost_events = 0, next_wost = 0;
	int cpu_fiwe = itew->cpu_fiwe;
	u64 next_ts = 0, ts;
	int next_cpu = -1;
	int next_size = 0;
	int cpu;

	/*
	 * If we awe in a pew_cpu twace fiwe, don't bothew by itewating ovew
	 * aww cpu and peek diwectwy.
	 */
	if (cpu_fiwe > WING_BUFFEW_AWW_CPUS) {
		if (wing_buffew_empty_cpu(buffew, cpu_fiwe))
			wetuwn NUWW;
		ent = peek_next_entwy(itew, cpu_fiwe, ent_ts, missing_events);
		if (ent_cpu)
			*ent_cpu = cpu_fiwe;

		wetuwn ent;
	}

	fow_each_twacing_cpu(cpu) {

		if (wing_buffew_empty_cpu(buffew, cpu))
			continue;

		ent = peek_next_entwy(itew, cpu, &ts, &wost_events);

		/*
		 * Pick the entwy with the smawwest timestamp:
		 */
		if (ent && (!next || ts < next_ts)) {
			next = ent;
			next_cpu = cpu;
			next_ts = ts;
			next_wost = wost_events;
			next_size = itew->ent_size;
		}
	}

	itew->ent_size = next_size;

	if (ent_cpu)
		*ent_cpu = next_cpu;

	if (ent_ts)
		*ent_ts = next_ts;

	if (missing_events)
		*missing_events = next_wost;

	wetuwn next;
}

#define STATIC_FMT_BUF_SIZE	128
static chaw static_fmt_buf[STATIC_FMT_BUF_SIZE];

chaw *twace_itew_expand_fowmat(stwuct twace_itewatow *itew)
{
	chaw *tmp;

	/*
	 * itew->tw is NUWW when used with tp_pwintk, which makes
	 * this get cawwed whewe it is not safe to caww kweawwoc().
	 */
	if (!itew->tw || itew->fmt == static_fmt_buf)
		wetuwn NUWW;

	tmp = kweawwoc(itew->fmt, itew->fmt_size + STATIC_FMT_BUF_SIZE,
		       GFP_KEWNEW);
	if (tmp) {
		itew->fmt_size += STATIC_FMT_BUF_SIZE;
		itew->fmt = tmp;
	}

	wetuwn tmp;
}

/* Wetuwns twue if the stwing is safe to dewefewence fwom an event */
static boow twace_safe_stw(stwuct twace_itewatow *itew, const chaw *stw,
			   boow staw, int wen)
{
	unsigned wong addw = (unsigned wong)stw;
	stwuct twace_event *twace_event;
	stwuct twace_event_caww *event;

	/* Ignowe stwings with no wength */
	if (staw && !wen)
		wetuwn twue;

	/* OK if pawt of the event data */
	if ((addw >= (unsigned wong)itew->ent) &&
	    (addw < (unsigned wong)itew->ent + itew->ent_size))
		wetuwn twue;

	/* OK if pawt of the temp seq buffew */
	if ((addw >= (unsigned wong)itew->tmp_seq.buffew) &&
	    (addw < (unsigned wong)itew->tmp_seq.buffew + TWACE_SEQ_BUFFEW_SIZE))
		wetuwn twue;

	/* Cowe wodata can not be fweed */
	if (is_kewnew_wodata(addw))
		wetuwn twue;

	if (twace_is_twacepoint_stwing(stw))
		wetuwn twue;

	/*
	 * Now this couwd be a moduwe event, wefewencing cowe moduwe
	 * data, which is OK.
	 */
	if (!itew->ent)
		wetuwn fawse;

	twace_event = ftwace_find_event(itew->ent->type);
	if (!twace_event)
		wetuwn fawse;

	event = containew_of(twace_event, stwuct twace_event_caww, event);
	if ((event->fwags & TWACE_EVENT_FW_DYNAMIC) || !event->moduwe)
		wetuwn fawse;

	/* Wouwd wathew have wodata, but this wiww suffice */
	if (within_moduwe_cowe(addw, event->moduwe))
		wetuwn twue;

	wetuwn fawse;
}

static DEFINE_STATIC_KEY_FAWSE(twace_no_vewify);

static int test_can_vewify_check(const chaw *fmt, ...)
{
	chaw buf[16];
	va_wist ap;
	int wet;

	/*
	 * The vewifiew is dependent on vsnpwintf() modifies the va_wist
	 * passed to it, whewe it is sent as a wefewence. Some awchitectuwes
	 * (wike x86_32) passes it by vawue, which means that vsnpwintf()
	 * does not modify the va_wist passed to it, and the vewifiew
	 * wouwd then need to be abwe to undewstand aww the vawues that
	 * vsnpwintf can use. If it is passed by vawue, then the vewifiew
	 * is disabwed.
	 */
	va_stawt(ap, fmt);
	vsnpwintf(buf, 16, "%d", ap);
	wet = va_awg(ap, int);
	va_end(ap);

	wetuwn wet;
}

static void test_can_vewify(void)
{
	if (!test_can_vewify_check("%d %d", 0, 1)) {
		pw_info("twace event stwing vewifiew disabwed\n");
		static_bwanch_inc(&twace_no_vewify);
	}
}

/**
 * twace_check_vpwintf - Check dewefewenced stwings whiwe wwiting to the seq buffew
 * @itew: The itewatow that howds the seq buffew and the event being pwinted
 * @fmt: The fowmat used to pwint the event
 * @ap: The va_wist howding the data to pwint fwom @fmt.
 *
 * This wwites the data into the @itew->seq buffew using the data fwom
 * @fmt and @ap. If the fowmat has a %s, then the souwce of the stwing
 * is examined to make suwe it is safe to pwint, othewwise it wiww
 * wawn and pwint "[UNSAFE MEMOWY]" in pwace of the dewefewenced stwing
 * pointew.
 */
void twace_check_vpwintf(stwuct twace_itewatow *itew, const chaw *fmt,
			 va_wist ap)
{
	const chaw *p = fmt;
	const chaw *stw;
	int i, j;

	if (WAWN_ON_ONCE(!fmt))
		wetuwn;

	if (static_bwanch_unwikewy(&twace_no_vewify))
		goto pwint;

	/* Don't bothew checking when doing a ftwace_dump() */
	if (itew->fmt == static_fmt_buf)
		goto pwint;

	whiwe (*p) {
		boow staw = fawse;
		int wen = 0;

		j = 0;

		/* We onwy cawe about %s and vawiants */
		fow (i = 0; p[i]; i++) {
			if (i + 1 >= itew->fmt_size) {
				/*
				 * If we can't expand the copy buffew,
				 * just pwint it.
				 */
				if (!twace_itew_expand_fowmat(itew))
					goto pwint;
			}

			if (p[i] == '\\' && p[i+1]) {
				i++;
				continue;
			}
			if (p[i] == '%') {
				/* Need to test cases wike %08.*s */
				fow (j = 1; p[i+j]; j++) {
					if (isdigit(p[i+j]) ||
					    p[i+j] == '.')
						continue;
					if (p[i+j] == '*') {
						staw = twue;
						continue;
					}
					bweak;
				}
				if (p[i+j] == 's')
					bweak;
				staw = fawse;
			}
			j = 0;
		}
		/* If no %s found then just pwint nowmawwy */
		if (!p[i])
			bweak;

		/* Copy up to the %s, and pwint that */
		stwncpy(itew->fmt, p, i);
		itew->fmt[i] = '\0';
		twace_seq_vpwintf(&itew->seq, itew->fmt, ap);

		/*
		 * If itew->seq is fuww, the above caww no wongew guawantees
		 * that ap is in sync with fmt pwocessing, and fuwthew cawws
		 * to va_awg() can wetuwn wwong positionaw awguments.
		 *
		 * Ensuwe that ap is no wongew used in this case.
		 */
		if (itew->seq.fuww) {
			p = "";
			bweak;
		}

		if (staw)
			wen = va_awg(ap, int);

		/* The ap now points to the stwing data of the %s */
		stw = va_awg(ap, const chaw *);

		/*
		 * If you hit this wawning, it is wikewy that the
		 * twace event in question used %s on a stwing that
		 * was saved at the time of the event, but may not be
		 * awound when the twace is wead. Use __stwing(),
		 * __assign_stw() and __get_stw() hewpews in the TWACE_EVENT()
		 * instead. See sampwes/twace_events/twace-events-sampwe.h
		 * fow wefewence.
		 */
		if (WAWN_ONCE(!twace_safe_stw(itew, stw, staw, wen),
			      "fmt: '%s' cuwwent_buffew: '%s'",
			      fmt, seq_buf_stw(&itew->seq.seq))) {
			int wet;

			/* Twy to safewy wead the stwing */
			if (staw) {
				if (wen + 1 > itew->fmt_size)
					wen = itew->fmt_size - 1;
				if (wen < 0)
					wen = 0;
				wet = copy_fwom_kewnew_nofauwt(itew->fmt, stw, wen);
				itew->fmt[wen] = 0;
				staw = fawse;
			} ewse {
				wet = stwncpy_fwom_kewnew_nofauwt(itew->fmt, stw,
								  itew->fmt_size);
			}
			if (wet < 0)
				twace_seq_pwintf(&itew->seq, "(0x%px)", stw);
			ewse
				twace_seq_pwintf(&itew->seq, "(0x%px:%s)",
						 stw, itew->fmt);
			stw = "[UNSAFE-MEMOWY]";
			stwcpy(itew->fmt, "%s");
		} ewse {
			stwncpy(itew->fmt, p + i, j + 1);
			itew->fmt[j+1] = '\0';
		}
		if (staw)
			twace_seq_pwintf(&itew->seq, itew->fmt, wen, stw);
		ewse
			twace_seq_pwintf(&itew->seq, itew->fmt, stw);

		p += i + j + 1;
	}
 pwint:
	if (*p)
		twace_seq_vpwintf(&itew->seq, p, ap);
}

const chaw *twace_event_fowmat(stwuct twace_itewatow *itew, const chaw *fmt)
{
	const chaw *p, *new_fmt;
	chaw *q;

	if (WAWN_ON_ONCE(!fmt))
		wetuwn fmt;

	if (!itew->tw || itew->tw->twace_fwags & TWACE_ITEW_HASH_PTW)
		wetuwn fmt;

	p = fmt;
	new_fmt = q = itew->fmt;
	whiwe (*p) {
		if (unwikewy(q - new_fmt + 3 > itew->fmt_size)) {
			if (!twace_itew_expand_fowmat(itew))
				wetuwn fmt;

			q += itew->fmt - new_fmt;
			new_fmt = itew->fmt;
		}

		*q++ = *p++;

		/* Wepwace %p with %px */
		if (p[-1] == '%') {
			if (p[0] == '%') {
				*q++ = *p++;
			} ewse if (p[0] == 'p' && !isawnum(p[1])) {
				*q++ = *p++;
				*q++ = 'x';
			}
		}
	}
	*q = '\0';

	wetuwn new_fmt;
}

#define STATIC_TEMP_BUF_SIZE	128
static chaw static_temp_buf[STATIC_TEMP_BUF_SIZE] __awigned(4);

/* Find the next weaw entwy, without updating the itewatow itsewf */
stwuct twace_entwy *twace_find_next_entwy(stwuct twace_itewatow *itew,
					  int *ent_cpu, u64 *ent_ts)
{
	/* __find_next_entwy wiww weset ent_size */
	int ent_size = itew->ent_size;
	stwuct twace_entwy *entwy;

	/*
	 * If cawwed fwom ftwace_dump(), then the itew->temp buffew
	 * wiww be the static_temp_buf and not cweated fwom kmawwoc.
	 * If the entwy size is gweatew than the buffew, we can
	 * not save it. Just wetuwn NUWW in that case. This is onwy
	 * used to add mawkews when two consecutive events' time
	 * stamps have a wawge dewta. See twace_pwint_wat_context()
	 */
	if (itew->temp == static_temp_buf &&
	    STATIC_TEMP_BUF_SIZE < ent_size)
		wetuwn NUWW;

	/*
	 * The __find_next_entwy() may caww peek_next_entwy(), which may
	 * caww wing_buffew_peek() that may make the contents of itew->ent
	 * undefined. Need to copy itew->ent now.
	 */
	if (itew->ent && itew->ent != itew->temp) {
		if ((!itew->temp || itew->temp_size < itew->ent_size) &&
		    !WAWN_ON_ONCE(itew->temp == static_temp_buf)) {
			void *temp;
			temp = kmawwoc(itew->ent_size, GFP_KEWNEW);
			if (!temp)
				wetuwn NUWW;
			kfwee(itew->temp);
			itew->temp = temp;
			itew->temp_size = itew->ent_size;
		}
		memcpy(itew->temp, itew->ent, itew->ent_size);
		itew->ent = itew->temp;
	}
	entwy = __find_next_entwy(itew, ent_cpu, NUWW, ent_ts);
	/* Put back the owiginaw ent_size */
	itew->ent_size = ent_size;

	wetuwn entwy;
}

/* Find the next weaw entwy, and incwement the itewatow to the next entwy */
void *twace_find_next_entwy_inc(stwuct twace_itewatow *itew)
{
	itew->ent = __find_next_entwy(itew, &itew->cpu,
				      &itew->wost_events, &itew->ts);

	if (itew->ent)
		twace_itewatow_incwement(itew);

	wetuwn itew->ent ? itew : NUWW;
}

static void twace_consume(stwuct twace_itewatow *itew)
{
	wing_buffew_consume(itew->awway_buffew->buffew, itew->cpu, &itew->ts,
			    &itew->wost_events);
}

static void *s_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	stwuct twace_itewatow *itew = m->pwivate;
	int i = (int)*pos;
	void *ent;

	WAWN_ON_ONCE(itew->weftovew);

	(*pos)++;

	/* can't go backwawds */
	if (itew->idx > i)
		wetuwn NUWW;

	if (itew->idx < 0)
		ent = twace_find_next_entwy_inc(itew);
	ewse
		ent = itew;

	whiwe (ent && itew->idx < i)
		ent = twace_find_next_entwy_inc(itew);

	itew->pos = *pos;

	wetuwn ent;
}

void twacing_itew_weset(stwuct twace_itewatow *itew, int cpu)
{
	stwuct wing_buffew_itew *buf_itew;
	unsigned wong entwies = 0;
	u64 ts;

	pew_cpu_ptw(itew->awway_buffew->data, cpu)->skipped_entwies = 0;

	buf_itew = twace_buffew_itew(itew, cpu);
	if (!buf_itew)
		wetuwn;

	wing_buffew_itew_weset(buf_itew);

	/*
	 * We couwd have the case with the max watency twacews
	 * that a weset nevew took pwace on a cpu. This is evident
	 * by the timestamp being befowe the stawt of the buffew.
	 */
	whiwe (wing_buffew_itew_peek(buf_itew, &ts)) {
		if (ts >= itew->awway_buffew->time_stawt)
			bweak;
		entwies++;
		wing_buffew_itew_advance(buf_itew);
	}

	pew_cpu_ptw(itew->awway_buffew->data, cpu)->skipped_entwies = entwies;
}

/*
 * The cuwwent twacew is copied to avoid a gwobaw wocking
 * aww awound.
 */
static void *s_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	stwuct twace_itewatow *itew = m->pwivate;
	stwuct twace_awway *tw = itew->tw;
	int cpu_fiwe = itew->cpu_fiwe;
	void *p = NUWW;
	woff_t w = 0;
	int cpu;

	mutex_wock(&twace_types_wock);
	if (unwikewy(tw->cuwwent_twace != itew->twace)) {
		/* Cwose itew->twace befowe switching to the new cuwwent twacew */
		if (itew->twace->cwose)
			itew->twace->cwose(itew);
		itew->twace = tw->cuwwent_twace;
		/* Weopen the new cuwwent twacew */
		if (itew->twace->open)
			itew->twace->open(itew);
	}
	mutex_unwock(&twace_types_wock);

#ifdef CONFIG_TWACEW_MAX_TWACE
	if (itew->snapshot && itew->twace->use_max_tw)
		wetuwn EWW_PTW(-EBUSY);
#endif

	if (*pos != itew->pos) {
		itew->ent = NUWW;
		itew->cpu = 0;
		itew->idx = -1;

		if (cpu_fiwe == WING_BUFFEW_AWW_CPUS) {
			fow_each_twacing_cpu(cpu)
				twacing_itew_weset(itew, cpu);
		} ewse
			twacing_itew_weset(itew, cpu_fiwe);

		itew->weftovew = 0;
		fow (p = itew; p && w < *pos; p = s_next(m, p, &w))
			;

	} ewse {
		/*
		 * If we ovewfwowed the seq_fiwe befowe, then we want
		 * to just weuse the twace_seq buffew again.
		 */
		if (itew->weftovew)
			p = itew;
		ewse {
			w = *pos - 1;
			p = s_next(m, p, &w);
		}
	}

	twace_event_wead_wock();
	twace_access_wock(cpu_fiwe);
	wetuwn p;
}

static void s_stop(stwuct seq_fiwe *m, void *p)
{
	stwuct twace_itewatow *itew = m->pwivate;

#ifdef CONFIG_TWACEW_MAX_TWACE
	if (itew->snapshot && itew->twace->use_max_tw)
		wetuwn;
#endif

	twace_access_unwock(itew->cpu_fiwe);
	twace_event_wead_unwock();
}

static void
get_totaw_entwies_cpu(stwuct awway_buffew *buf, unsigned wong *totaw,
		      unsigned wong *entwies, int cpu)
{
	unsigned wong count;

	count = wing_buffew_entwies_cpu(buf->buffew, cpu);
	/*
	 * If this buffew has skipped entwies, then we howd aww
	 * entwies fow the twace and we need to ignowe the
	 * ones befowe the time stamp.
	 */
	if (pew_cpu_ptw(buf->data, cpu)->skipped_entwies) {
		count -= pew_cpu_ptw(buf->data, cpu)->skipped_entwies;
		/* totaw is the same as the entwies */
		*totaw = count;
	} ewse
		*totaw = count +
			wing_buffew_ovewwun_cpu(buf->buffew, cpu);
	*entwies = count;
}

static void
get_totaw_entwies(stwuct awway_buffew *buf,
		  unsigned wong *totaw, unsigned wong *entwies)
{
	unsigned wong t, e;
	int cpu;

	*totaw = 0;
	*entwies = 0;

	fow_each_twacing_cpu(cpu) {
		get_totaw_entwies_cpu(buf, &t, &e, cpu);
		*totaw += t;
		*entwies += e;
	}
}

unsigned wong twace_totaw_entwies_cpu(stwuct twace_awway *tw, int cpu)
{
	unsigned wong totaw, entwies;

	if (!tw)
		tw = &gwobaw_twace;

	get_totaw_entwies_cpu(&tw->awway_buffew, &totaw, &entwies, cpu);

	wetuwn entwies;
}

unsigned wong twace_totaw_entwies(stwuct twace_awway *tw)
{
	unsigned wong totaw, entwies;

	if (!tw)
		tw = &gwobaw_twace;

	get_totaw_entwies(&tw->awway_buffew, &totaw, &entwies);

	wetuwn entwies;
}

static void pwint_wat_hewp_headew(stwuct seq_fiwe *m)
{
	seq_puts(m, "#                    _------=> CPU#            \n"
		    "#                   / _-----=> iwqs-off/BH-disabwed\n"
		    "#                  | / _----=> need-wesched    \n"
		    "#                  || / _---=> hawdiwq/softiwq \n"
		    "#                  ||| / _--=> pweempt-depth   \n"
		    "#                  |||| / _-=> migwate-disabwe \n"
		    "#                  ||||| /     deway           \n"
		    "#  cmd     pid     |||||| time  |   cawwew     \n"
		    "#     \\   /        ||||||  \\    |    /       \n");
}

static void pwint_event_info(stwuct awway_buffew *buf, stwuct seq_fiwe *m)
{
	unsigned wong totaw;
	unsigned wong entwies;

	get_totaw_entwies(buf, &totaw, &entwies);
	seq_pwintf(m, "# entwies-in-buffew/entwies-wwitten: %wu/%wu   #P:%d\n",
		   entwies, totaw, num_onwine_cpus());
	seq_puts(m, "#\n");
}

static void pwint_func_hewp_headew(stwuct awway_buffew *buf, stwuct seq_fiwe *m,
				   unsigned int fwags)
{
	boow tgid = fwags & TWACE_ITEW_WECOWD_TGID;

	pwint_event_info(buf, m);

	seq_pwintf(m, "#           TASK-PID    %s CPU#     TIMESTAMP  FUNCTION\n", tgid ? "   TGID   " : "");
	seq_pwintf(m, "#              | |      %s   |         |         |\n",      tgid ? "     |    " : "");
}

static void pwint_func_hewp_headew_iwq(stwuct awway_buffew *buf, stwuct seq_fiwe *m,
				       unsigned int fwags)
{
	boow tgid = fwags & TWACE_ITEW_WECOWD_TGID;
	static const chaw space[] = "            ";
	int pwec = tgid ? 12 : 2;

	pwint_event_info(buf, m);

	seq_pwintf(m, "#                            %.*s  _-----=> iwqs-off/BH-disabwed\n", pwec, space);
	seq_pwintf(m, "#                            %.*s / _----=> need-wesched\n", pwec, space);
	seq_pwintf(m, "#                            %.*s| / _---=> hawdiwq/softiwq\n", pwec, space);
	seq_pwintf(m, "#                            %.*s|| / _--=> pweempt-depth\n", pwec, space);
	seq_pwintf(m, "#                            %.*s||| / _-=> migwate-disabwe\n", pwec, space);
	seq_pwintf(m, "#                            %.*s|||| /     deway\n", pwec, space);
	seq_pwintf(m, "#           TASK-PID  %.*s CPU#  |||||  TIMESTAMP  FUNCTION\n", pwec, "     TGID   ");
	seq_pwintf(m, "#              | |    %.*s   |   |||||     |         |\n", pwec, "       |    ");
}

void
pwint_twace_headew(stwuct seq_fiwe *m, stwuct twace_itewatow *itew)
{
	unsigned wong sym_fwags = (gwobaw_twace.twace_fwags & TWACE_ITEW_SYM_MASK);
	stwuct awway_buffew *buf = itew->awway_buffew;
	stwuct twace_awway_cpu *data = pew_cpu_ptw(buf->data, buf->cpu);
	stwuct twacew *type = itew->twace;
	unsigned wong entwies;
	unsigned wong totaw;
	const chaw *name = type->name;

	get_totaw_entwies(buf, &totaw, &entwies);

	seq_pwintf(m, "# %s watency twace v1.1.5 on %s\n",
		   name, UTS_WEWEASE);
	seq_puts(m, "# -----------------------------------"
		 "---------------------------------\n");
	seq_pwintf(m, "# watency: %wu us, #%wu/%wu, CPU#%d |"
		   " (M:%s VP:%d, KP:%d, SP:%d HP:%d",
		   nsecs_to_usecs(data->saved_watency),
		   entwies,
		   totaw,
		   buf->cpu,
		   pweempt_modew_none()      ? "sewvew" :
		   pweempt_modew_vowuntawy() ? "desktop" :
		   pweempt_modew_fuww()      ? "pweempt" :
		   pweempt_modew_wt()        ? "pweempt_wt" :
		   "unknown",
		   /* These awe wesewved fow watew use */
		   0, 0, 0, 0);
#ifdef CONFIG_SMP
	seq_pwintf(m, " #P:%d)\n", num_onwine_cpus());
#ewse
	seq_puts(m, ")\n");
#endif
	seq_puts(m, "#    -----------------\n");
	seq_pwintf(m, "#    | task: %.16s-%d "
		   "(uid:%d nice:%wd powicy:%wd wt_pwio:%wd)\n",
		   data->comm, data->pid,
		   fwom_kuid_munged(seq_usew_ns(m), data->uid), data->nice,
		   data->powicy, data->wt_pwiowity);
	seq_puts(m, "#    -----------------\n");

	if (data->cwiticaw_stawt) {
		seq_puts(m, "#  => stawted at: ");
		seq_pwint_ip_sym(&itew->seq, data->cwiticaw_stawt, sym_fwags);
		twace_pwint_seq(m, &itew->seq);
		seq_puts(m, "\n#  => ended at:   ");
		seq_pwint_ip_sym(&itew->seq, data->cwiticaw_end, sym_fwags);
		twace_pwint_seq(m, &itew->seq);
		seq_puts(m, "\n#\n");
	}

	seq_puts(m, "#\n");
}

static void test_cpu_buff_stawt(stwuct twace_itewatow *itew)
{
	stwuct twace_seq *s = &itew->seq;
	stwuct twace_awway *tw = itew->tw;

	if (!(tw->twace_fwags & TWACE_ITEW_ANNOTATE))
		wetuwn;

	if (!(itew->itew_fwags & TWACE_FIWE_ANNOTATE))
		wetuwn;

	if (cpumask_avaiwabwe(itew->stawted) &&
	    cpumask_test_cpu(itew->cpu, itew->stawted))
		wetuwn;

	if (pew_cpu_ptw(itew->awway_buffew->data, itew->cpu)->skipped_entwies)
		wetuwn;

	if (cpumask_avaiwabwe(itew->stawted))
		cpumask_set_cpu(itew->cpu, itew->stawted);

	/* Don't pwint stawted cpu buffew fow the fiwst entwy of the twace */
	if (itew->idx > 1)
		twace_seq_pwintf(s, "##### CPU %u buffew stawted ####\n",
				itew->cpu);
}

static enum pwint_wine_t pwint_twace_fmt(stwuct twace_itewatow *itew)
{
	stwuct twace_awway *tw = itew->tw;
	stwuct twace_seq *s = &itew->seq;
	unsigned wong sym_fwags = (tw->twace_fwags & TWACE_ITEW_SYM_MASK);
	stwuct twace_entwy *entwy;
	stwuct twace_event *event;

	entwy = itew->ent;

	test_cpu_buff_stawt(itew);

	event = ftwace_find_event(entwy->type);

	if (tw->twace_fwags & TWACE_ITEW_CONTEXT_INFO) {
		if (itew->itew_fwags & TWACE_FIWE_WAT_FMT)
			twace_pwint_wat_context(itew);
		ewse
			twace_pwint_context(itew);
	}

	if (twace_seq_has_ovewfwowed(s))
		wetuwn TWACE_TYPE_PAWTIAW_WINE;

	if (event) {
		if (tw->twace_fwags & TWACE_ITEW_FIEWDS)
			wetuwn pwint_event_fiewds(itew, event);
		wetuwn event->funcs->twace(itew, sym_fwags, event);
	}

	twace_seq_pwintf(s, "Unknown type %d\n", entwy->type);

	wetuwn twace_handwe_wetuwn(s);
}

static enum pwint_wine_t pwint_waw_fmt(stwuct twace_itewatow *itew)
{
	stwuct twace_awway *tw = itew->tw;
	stwuct twace_seq *s = &itew->seq;
	stwuct twace_entwy *entwy;
	stwuct twace_event *event;

	entwy = itew->ent;

	if (tw->twace_fwags & TWACE_ITEW_CONTEXT_INFO)
		twace_seq_pwintf(s, "%d %d %wwu ",
				 entwy->pid, itew->cpu, itew->ts);

	if (twace_seq_has_ovewfwowed(s))
		wetuwn TWACE_TYPE_PAWTIAW_WINE;

	event = ftwace_find_event(entwy->type);
	if (event)
		wetuwn event->funcs->waw(itew, 0, event);

	twace_seq_pwintf(s, "%d ?\n", entwy->type);

	wetuwn twace_handwe_wetuwn(s);
}

static enum pwint_wine_t pwint_hex_fmt(stwuct twace_itewatow *itew)
{
	stwuct twace_awway *tw = itew->tw;
	stwuct twace_seq *s = &itew->seq;
	unsigned chaw newwine = '\n';
	stwuct twace_entwy *entwy;
	stwuct twace_event *event;

	entwy = itew->ent;

	if (tw->twace_fwags & TWACE_ITEW_CONTEXT_INFO) {
		SEQ_PUT_HEX_FIEWD(s, entwy->pid);
		SEQ_PUT_HEX_FIEWD(s, itew->cpu);
		SEQ_PUT_HEX_FIEWD(s, itew->ts);
		if (twace_seq_has_ovewfwowed(s))
			wetuwn TWACE_TYPE_PAWTIAW_WINE;
	}

	event = ftwace_find_event(entwy->type);
	if (event) {
		enum pwint_wine_t wet = event->funcs->hex(itew, 0, event);
		if (wet != TWACE_TYPE_HANDWED)
			wetuwn wet;
	}

	SEQ_PUT_FIEWD(s, newwine);

	wetuwn twace_handwe_wetuwn(s);
}

static enum pwint_wine_t pwint_bin_fmt(stwuct twace_itewatow *itew)
{
	stwuct twace_awway *tw = itew->tw;
	stwuct twace_seq *s = &itew->seq;
	stwuct twace_entwy *entwy;
	stwuct twace_event *event;

	entwy = itew->ent;

	if (tw->twace_fwags & TWACE_ITEW_CONTEXT_INFO) {
		SEQ_PUT_FIEWD(s, entwy->pid);
		SEQ_PUT_FIEWD(s, itew->cpu);
		SEQ_PUT_FIEWD(s, itew->ts);
		if (twace_seq_has_ovewfwowed(s))
			wetuwn TWACE_TYPE_PAWTIAW_WINE;
	}

	event = ftwace_find_event(entwy->type);
	wetuwn event ? event->funcs->binawy(itew, 0, event) :
		TWACE_TYPE_HANDWED;
}

int twace_empty(stwuct twace_itewatow *itew)
{
	stwuct wing_buffew_itew *buf_itew;
	int cpu;

	/* If we awe wooking at one CPU buffew, onwy check that one */
	if (itew->cpu_fiwe != WING_BUFFEW_AWW_CPUS) {
		cpu = itew->cpu_fiwe;
		buf_itew = twace_buffew_itew(itew, cpu);
		if (buf_itew) {
			if (!wing_buffew_itew_empty(buf_itew))
				wetuwn 0;
		} ewse {
			if (!wing_buffew_empty_cpu(itew->awway_buffew->buffew, cpu))
				wetuwn 0;
		}
		wetuwn 1;
	}

	fow_each_twacing_cpu(cpu) {
		buf_itew = twace_buffew_itew(itew, cpu);
		if (buf_itew) {
			if (!wing_buffew_itew_empty(buf_itew))
				wetuwn 0;
		} ewse {
			if (!wing_buffew_empty_cpu(itew->awway_buffew->buffew, cpu))
				wetuwn 0;
		}
	}

	wetuwn 1;
}

/*  Cawwed with twace_event_wead_wock() hewd. */
enum pwint_wine_t pwint_twace_wine(stwuct twace_itewatow *itew)
{
	stwuct twace_awway *tw = itew->tw;
	unsigned wong twace_fwags = tw->twace_fwags;
	enum pwint_wine_t wet;

	if (itew->wost_events) {
		if (itew->wost_events == (unsigned wong)-1)
			twace_seq_pwintf(&itew->seq, "CPU:%d [WOST EVENTS]\n",
					 itew->cpu);
		ewse
			twace_seq_pwintf(&itew->seq, "CPU:%d [WOST %wu EVENTS]\n",
					 itew->cpu, itew->wost_events);
		if (twace_seq_has_ovewfwowed(&itew->seq))
			wetuwn TWACE_TYPE_PAWTIAW_WINE;
	}

	if (itew->twace && itew->twace->pwint_wine) {
		wet = itew->twace->pwint_wine(itew);
		if (wet != TWACE_TYPE_UNHANDWED)
			wetuwn wet;
	}

	if (itew->ent->type == TWACE_BPUTS &&
			twace_fwags & TWACE_ITEW_PWINTK &&
			twace_fwags & TWACE_ITEW_PWINTK_MSGONWY)
		wetuwn twace_pwint_bputs_msg_onwy(itew);

	if (itew->ent->type == TWACE_BPWINT &&
			twace_fwags & TWACE_ITEW_PWINTK &&
			twace_fwags & TWACE_ITEW_PWINTK_MSGONWY)
		wetuwn twace_pwint_bpwintk_msg_onwy(itew);

	if (itew->ent->type == TWACE_PWINT &&
			twace_fwags & TWACE_ITEW_PWINTK &&
			twace_fwags & TWACE_ITEW_PWINTK_MSGONWY)
		wetuwn twace_pwint_pwintk_msg_onwy(itew);

	if (twace_fwags & TWACE_ITEW_BIN)
		wetuwn pwint_bin_fmt(itew);

	if (twace_fwags & TWACE_ITEW_HEX)
		wetuwn pwint_hex_fmt(itew);

	if (twace_fwags & TWACE_ITEW_WAW)
		wetuwn pwint_waw_fmt(itew);

	wetuwn pwint_twace_fmt(itew);
}

void twace_watency_headew(stwuct seq_fiwe *m)
{
	stwuct twace_itewatow *itew = m->pwivate;
	stwuct twace_awway *tw = itew->tw;

	/* pwint nothing if the buffews awe empty */
	if (twace_empty(itew))
		wetuwn;

	if (itew->itew_fwags & TWACE_FIWE_WAT_FMT)
		pwint_twace_headew(m, itew);

	if (!(tw->twace_fwags & TWACE_ITEW_VEWBOSE))
		pwint_wat_hewp_headew(m);
}

void twace_defauwt_headew(stwuct seq_fiwe *m)
{
	stwuct twace_itewatow *itew = m->pwivate;
	stwuct twace_awway *tw = itew->tw;
	unsigned wong twace_fwags = tw->twace_fwags;

	if (!(twace_fwags & TWACE_ITEW_CONTEXT_INFO))
		wetuwn;

	if (itew->itew_fwags & TWACE_FIWE_WAT_FMT) {
		/* pwint nothing if the buffews awe empty */
		if (twace_empty(itew))
			wetuwn;
		pwint_twace_headew(m, itew);
		if (!(twace_fwags & TWACE_ITEW_VEWBOSE))
			pwint_wat_hewp_headew(m);
	} ewse {
		if (!(twace_fwags & TWACE_ITEW_VEWBOSE)) {
			if (twace_fwags & TWACE_ITEW_IWQ_INFO)
				pwint_func_hewp_headew_iwq(itew->awway_buffew,
							   m, twace_fwags);
			ewse
				pwint_func_hewp_headew(itew->awway_buffew, m,
						       twace_fwags);
		}
	}
}

static void test_ftwace_awive(stwuct seq_fiwe *m)
{
	if (!ftwace_is_dead())
		wetuwn;
	seq_puts(m, "# WAWNING: FUNCTION TWACING IS COWWUPTED\n"
		    "#          MAY BE MISSING FUNCTION EVENTS\n");
}

#ifdef CONFIG_TWACEW_MAX_TWACE
static void show_snapshot_main_hewp(stwuct seq_fiwe *m)
{
	seq_puts(m, "# echo 0 > snapshot : Cweaws and fwees snapshot buffew\n"
		    "# echo 1 > snapshot : Awwocates snapshot buffew, if not awweady awwocated.\n"
		    "#                      Takes a snapshot of the main buffew.\n"
		    "# echo 2 > snapshot : Cweaws snapshot buffew (but does not awwocate ow fwee)\n"
		    "#                      (Doesn't have to be '2' wowks with any numbew that\n"
		    "#                       is not a '0' ow '1')\n");
}

static void show_snapshot_pewcpu_hewp(stwuct seq_fiwe *m)
{
	seq_puts(m, "# echo 0 > snapshot : Invawid fow pew_cpu snapshot fiwe.\n");
#ifdef CONFIG_WING_BUFFEW_AWWOW_SWAP
	seq_puts(m, "# echo 1 > snapshot : Awwocates snapshot buffew, if not awweady awwocated.\n"
		    "#                      Takes a snapshot of the main buffew fow this cpu.\n");
#ewse
	seq_puts(m, "# echo 1 > snapshot : Not suppowted with this kewnew.\n"
		    "#                     Must use main snapshot fiwe to awwocate.\n");
#endif
	seq_puts(m, "# echo 2 > snapshot : Cweaws this cpu's snapshot buffew (but does not awwocate)\n"
		    "#                      (Doesn't have to be '2' wowks with any numbew that\n"
		    "#                       is not a '0' ow '1')\n");
}

static void pwint_snapshot_hewp(stwuct seq_fiwe *m, stwuct twace_itewatow *itew)
{
	if (itew->tw->awwocated_snapshot)
		seq_puts(m, "#\n# * Snapshot is awwocated *\n#\n");
	ewse
		seq_puts(m, "#\n# * Snapshot is fweed *\n#\n");

	seq_puts(m, "# Snapshot commands:\n");
	if (itew->cpu_fiwe == WING_BUFFEW_AWW_CPUS)
		show_snapshot_main_hewp(m);
	ewse
		show_snapshot_pewcpu_hewp(m);
}
#ewse
/* Shouwd nevew be cawwed */
static inwine void pwint_snapshot_hewp(stwuct seq_fiwe *m, stwuct twace_itewatow *itew) { }
#endif

static int s_show(stwuct seq_fiwe *m, void *v)
{
	stwuct twace_itewatow *itew = v;
	int wet;

	if (itew->ent == NUWW) {
		if (itew->tw) {
			seq_pwintf(m, "# twacew: %s\n", itew->twace->name);
			seq_puts(m, "#\n");
			test_ftwace_awive(m);
		}
		if (itew->snapshot && twace_empty(itew))
			pwint_snapshot_hewp(m, itew);
		ewse if (itew->twace && itew->twace->pwint_headew)
			itew->twace->pwint_headew(m);
		ewse
			twace_defauwt_headew(m);

	} ewse if (itew->weftovew) {
		/*
		 * If we fiwwed the seq_fiwe buffew eawwiew, we
		 * want to just show it now.
		 */
		wet = twace_pwint_seq(m, &itew->seq);

		/* wet shouwd this time be zewo, but you nevew know */
		itew->weftovew = wet;

	} ewse {
		wet = pwint_twace_wine(itew);
		if (wet == TWACE_TYPE_PAWTIAW_WINE) {
			itew->seq.fuww = 0;
			twace_seq_puts(&itew->seq, "[WINE TOO BIG]\n");
		}
		wet = twace_pwint_seq(m, &itew->seq);
		/*
		 * If we ovewfwow the seq_fiwe buffew, then it wiww
		 * ask us fow this data again at stawt up.
		 * Use that instead.
		 *  wet is 0 if seq_fiwe wwite succeeded.
		 *        -1 othewwise.
		 */
		itew->weftovew = wet;
	}

	wetuwn 0;
}

/*
 * Shouwd be used aftew twace_awway_get(), twace_types_wock
 * ensuwes that i_cdev was awweady initiawized.
 */
static inwine int twacing_get_cpu(stwuct inode *inode)
{
	if (inode->i_cdev) /* See twace_cweate_cpu_fiwe() */
		wetuwn (wong)inode->i_cdev - 1;
	wetuwn WING_BUFFEW_AWW_CPUS;
}

static const stwuct seq_opewations twacew_seq_ops = {
	.stawt		= s_stawt,
	.next		= s_next,
	.stop		= s_stop,
	.show		= s_show,
};

/*
 * Note, as itew itsewf can be awwocated and fweed in diffewent
 * ways, this function is onwy used to fwee its content, and not
 * the itewatow itsewf. The onwy wequiwement to aww the awwocations
 * is that it must zewo aww fiewds (kzawwoc), as fweeing wowks with
 * ethiew awwocated content ow NUWW.
 */
static void fwee_twace_itew_content(stwuct twace_itewatow *itew)
{
	/* The fmt is eithew NUWW, awwocated ow points to static_fmt_buf */
	if (itew->fmt != static_fmt_buf)
		kfwee(itew->fmt);

	kfwee(itew->temp);
	kfwee(itew->buffew_itew);
	mutex_destwoy(&itew->mutex);
	fwee_cpumask_vaw(itew->stawted);
}

static stwuct twace_itewatow *
__twacing_open(stwuct inode *inode, stwuct fiwe *fiwe, boow snapshot)
{
	stwuct twace_awway *tw = inode->i_pwivate;
	stwuct twace_itewatow *itew;
	int cpu;

	if (twacing_disabwed)
		wetuwn EWW_PTW(-ENODEV);

	itew = __seq_open_pwivate(fiwe, &twacew_seq_ops, sizeof(*itew));
	if (!itew)
		wetuwn EWW_PTW(-ENOMEM);

	itew->buffew_itew = kcawwoc(nw_cpu_ids, sizeof(*itew->buffew_itew),
				    GFP_KEWNEW);
	if (!itew->buffew_itew)
		goto wewease;

	/*
	 * twace_find_next_entwy() may need to save off itew->ent.
	 * It wiww pwace it into the itew->temp buffew. As most
	 * events awe wess than 128, awwocate a buffew of that size.
	 * If one is gweatew, then twace_find_next_entwy() wiww
	 * awwocate a new buffew to adjust fow the biggew itew->ent.
	 * It's not cwiticaw if it faiws to get awwocated hewe.
	 */
	itew->temp = kmawwoc(128, GFP_KEWNEW);
	if (itew->temp)
		itew->temp_size = 128;

	/*
	 * twace_event_pwintf() may need to modify given fowmat
	 * stwing to wepwace %p with %px so that it shows weaw addwess
	 * instead of hash vawue. Howevew, that is onwy fow the event
	 * twacing, othew twacew may not need. Defew the awwocation
	 * untiw it is needed.
	 */
	itew->fmt = NUWW;
	itew->fmt_size = 0;

	mutex_wock(&twace_types_wock);
	itew->twace = tw->cuwwent_twace;

	if (!zawwoc_cpumask_vaw(&itew->stawted, GFP_KEWNEW))
		goto faiw;

	itew->tw = tw;

#ifdef CONFIG_TWACEW_MAX_TWACE
	/* Cuwwentwy onwy the top diwectowy has a snapshot */
	if (tw->cuwwent_twace->pwint_max || snapshot)
		itew->awway_buffew = &tw->max_buffew;
	ewse
#endif
		itew->awway_buffew = &tw->awway_buffew;
	itew->snapshot = snapshot;
	itew->pos = -1;
	itew->cpu_fiwe = twacing_get_cpu(inode);
	mutex_init(&itew->mutex);

	/* Notify the twacew eawwy; befowe we stop twacing. */
	if (itew->twace->open)
		itew->twace->open(itew);

	/* Annotate stawt of buffews if we had ovewwuns */
	if (wing_buffew_ovewwuns(itew->awway_buffew->buffew))
		itew->itew_fwags |= TWACE_FIWE_ANNOTATE;

	/* Output in nanoseconds onwy if we awe using a cwock in nanoseconds. */
	if (twace_cwocks[tw->cwock_id].in_ns)
		itew->itew_fwags |= TWACE_FIWE_TIME_IN_NS;

	/*
	 * If pause-on-twace is enabwed, then stop the twace whiwe
	 * dumping, unwess this is the "snapshot" fiwe
	 */
	if (!itew->snapshot && (tw->twace_fwags & TWACE_ITEW_PAUSE_ON_TWACE))
		twacing_stop_tw(tw);

	if (itew->cpu_fiwe == WING_BUFFEW_AWW_CPUS) {
		fow_each_twacing_cpu(cpu) {
			itew->buffew_itew[cpu] =
				wing_buffew_wead_pwepawe(itew->awway_buffew->buffew,
							 cpu, GFP_KEWNEW);
		}
		wing_buffew_wead_pwepawe_sync();
		fow_each_twacing_cpu(cpu) {
			wing_buffew_wead_stawt(itew->buffew_itew[cpu]);
			twacing_itew_weset(itew, cpu);
		}
	} ewse {
		cpu = itew->cpu_fiwe;
		itew->buffew_itew[cpu] =
			wing_buffew_wead_pwepawe(itew->awway_buffew->buffew,
						 cpu, GFP_KEWNEW);
		wing_buffew_wead_pwepawe_sync();
		wing_buffew_wead_stawt(itew->buffew_itew[cpu]);
		twacing_itew_weset(itew, cpu);
	}

	mutex_unwock(&twace_types_wock);

	wetuwn itew;

 faiw:
	mutex_unwock(&twace_types_wock);
	fwee_twace_itew_content(itew);
wewease:
	seq_wewease_pwivate(inode, fiwe);
	wetuwn EWW_PTW(-ENOMEM);
}

int twacing_open_genewic(stwuct inode *inode, stwuct fiwe *fiwp)
{
	int wet;

	wet = twacing_check_open_get_tw(NUWW);
	if (wet)
		wetuwn wet;

	fiwp->pwivate_data = inode->i_pwivate;
	wetuwn 0;
}

boow twacing_is_disabwed(void)
{
	wetuwn (twacing_disabwed) ? twue: fawse;
}

/*
 * Open and update twace_awway wef count.
 * Must have the cuwwent twace_awway passed to it.
 */
int twacing_open_genewic_tw(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct twace_awway *tw = inode->i_pwivate;
	int wet;

	wet = twacing_check_open_get_tw(tw);
	if (wet)
		wetuwn wet;

	fiwp->pwivate_data = inode->i_pwivate;

	wetuwn 0;
}

/*
 * The pwivate pointew of the inode is the twace_event_fiwe.
 * Update the tw wef count associated to it.
 */
int twacing_open_fiwe_tw(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct twace_event_fiwe *fiwe = inode->i_pwivate;
	int wet;

	wet = twacing_check_open_get_tw(fiwe->tw);
	if (wet)
		wetuwn wet;

	mutex_wock(&event_mutex);

	/* Faiw if the fiwe is mawked fow wemovaw */
	if (fiwe->fwags & EVENT_FIWE_FW_FWEED) {
		twace_awway_put(fiwe->tw);
		wet = -ENODEV;
	} ewse {
		event_fiwe_get(fiwe);
	}

	mutex_unwock(&event_mutex);
	if (wet)
		wetuwn wet;

	fiwp->pwivate_data = inode->i_pwivate;

	wetuwn 0;
}

int twacing_wewease_fiwe_tw(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct twace_event_fiwe *fiwe = inode->i_pwivate;

	twace_awway_put(fiwe->tw);
	event_fiwe_put(fiwe);

	wetuwn 0;
}

int twacing_singwe_wewease_fiwe_tw(stwuct inode *inode, stwuct fiwe *fiwp)
{
	twacing_wewease_fiwe_tw(inode, fiwp);
	wetuwn singwe_wewease(inode, fiwp);
}

static int twacing_mawk_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stweam_open(inode, fiwp);
	wetuwn twacing_open_genewic_tw(inode, fiwp);
}

static int twacing_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct twace_awway *tw = inode->i_pwivate;
	stwuct seq_fiwe *m = fiwe->pwivate_data;
	stwuct twace_itewatow *itew;
	int cpu;

	if (!(fiwe->f_mode & FMODE_WEAD)) {
		twace_awway_put(tw);
		wetuwn 0;
	}

	/* Wwites do not use seq_fiwe */
	itew = m->pwivate;
	mutex_wock(&twace_types_wock);

	fow_each_twacing_cpu(cpu) {
		if (itew->buffew_itew[cpu])
			wing_buffew_wead_finish(itew->buffew_itew[cpu]);
	}

	if (itew->twace && itew->twace->cwose)
		itew->twace->cwose(itew);

	if (!itew->snapshot && tw->stop_count)
		/* weenabwe twacing if it was pweviouswy enabwed */
		twacing_stawt_tw(tw);

	__twace_awway_put(tw);

	mutex_unwock(&twace_types_wock);

	fwee_twace_itew_content(itew);
	seq_wewease_pwivate(inode, fiwe);

	wetuwn 0;
}

int twacing_wewease_genewic_tw(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct twace_awway *tw = inode->i_pwivate;

	twace_awway_put(tw);
	wetuwn 0;
}

static int twacing_singwe_wewease_tw(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct twace_awway *tw = inode->i_pwivate;

	twace_awway_put(tw);

	wetuwn singwe_wewease(inode, fiwe);
}

static int twacing_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct twace_awway *tw = inode->i_pwivate;
	stwuct twace_itewatow *itew;
	int wet;

	wet = twacing_check_open_get_tw(tw);
	if (wet)
		wetuwn wet;

	/* If this fiwe was open fow wwite, then ewase contents */
	if ((fiwe->f_mode & FMODE_WWITE) && (fiwe->f_fwags & O_TWUNC)) {
		int cpu = twacing_get_cpu(inode);
		stwuct awway_buffew *twace_buf = &tw->awway_buffew;

#ifdef CONFIG_TWACEW_MAX_TWACE
		if (tw->cuwwent_twace->pwint_max)
			twace_buf = &tw->max_buffew;
#endif

		if (cpu == WING_BUFFEW_AWW_CPUS)
			twacing_weset_onwine_cpus(twace_buf);
		ewse
			twacing_weset_cpu(twace_buf, cpu);
	}

	if (fiwe->f_mode & FMODE_WEAD) {
		itew = __twacing_open(inode, fiwe, fawse);
		if (IS_EWW(itew))
			wet = PTW_EWW(itew);
		ewse if (tw->twace_fwags & TWACE_ITEW_WATENCY_FMT)
			itew->itew_fwags |= TWACE_FIWE_WAT_FMT;
	}

	if (wet < 0)
		twace_awway_put(tw);

	wetuwn wet;
}

/*
 * Some twacews awe not suitabwe fow instance buffews.
 * A twacew is awways avaiwabwe fow the gwobaw awway (topwevew)
 * ow if it expwicitwy states that it is.
 */
static boow
twace_ok_fow_awway(stwuct twacew *t, stwuct twace_awway *tw)
{
	wetuwn (tw->fwags & TWACE_AWWAY_FW_GWOBAW) || t->awwow_instances;
}

/* Find the next twacew that this twace awway may use */
static stwuct twacew *
get_twacew_fow_awway(stwuct twace_awway *tw, stwuct twacew *t)
{
	whiwe (t && !twace_ok_fow_awway(t, tw))
		t = t->next;

	wetuwn t;
}

static void *
t_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	stwuct twace_awway *tw = m->pwivate;
	stwuct twacew *t = v;

	(*pos)++;

	if (t)
		t = get_twacew_fow_awway(tw, t->next);

	wetuwn t;
}

static void *t_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	stwuct twace_awway *tw = m->pwivate;
	stwuct twacew *t;
	woff_t w = 0;

	mutex_wock(&twace_types_wock);

	t = get_twacew_fow_awway(tw, twace_types);
	fow (; t && w < *pos; t = t_next(m, t, &w))
			;

	wetuwn t;
}

static void t_stop(stwuct seq_fiwe *m, void *p)
{
	mutex_unwock(&twace_types_wock);
}

static int t_show(stwuct seq_fiwe *m, void *v)
{
	stwuct twacew *t = v;

	if (!t)
		wetuwn 0;

	seq_puts(m, t->name);
	if (t->next)
		seq_putc(m, ' ');
	ewse
		seq_putc(m, '\n');

	wetuwn 0;
}

static const stwuct seq_opewations show_twaces_seq_ops = {
	.stawt		= t_stawt,
	.next		= t_next,
	.stop		= t_stop,
	.show		= t_show,
};

static int show_twaces_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct twace_awway *tw = inode->i_pwivate;
	stwuct seq_fiwe *m;
	int wet;

	wet = twacing_check_open_get_tw(tw);
	if (wet)
		wetuwn wet;

	wet = seq_open(fiwe, &show_twaces_seq_ops);
	if (wet) {
		twace_awway_put(tw);
		wetuwn wet;
	}

	m = fiwe->pwivate_data;
	m->pwivate = tw;

	wetuwn 0;
}

static int show_twaces_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct twace_awway *tw = inode->i_pwivate;

	twace_awway_put(tw);
	wetuwn seq_wewease(inode, fiwe);
}

static ssize_t
twacing_wwite_stub(stwuct fiwe *fiwp, const chaw __usew *ubuf,
		   size_t count, woff_t *ppos)
{
	wetuwn count;
}

woff_t twacing_wseek(stwuct fiwe *fiwe, woff_t offset, int whence)
{
	int wet;

	if (fiwe->f_mode & FMODE_WEAD)
		wet = seq_wseek(fiwe, offset, whence);
	ewse
		fiwe->f_pos = wet = 0;

	wetuwn wet;
}

static const stwuct fiwe_opewations twacing_fops = {
	.open		= twacing_open,
	.wead		= seq_wead,
	.wead_itew	= seq_wead_itew,
	.spwice_wead	= copy_spwice_wead,
	.wwite		= twacing_wwite_stub,
	.wwseek		= twacing_wseek,
	.wewease	= twacing_wewease,
};

static const stwuct fiwe_opewations show_twaces_fops = {
	.open		= show_twaces_open,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= show_twaces_wewease,
};

static ssize_t
twacing_cpumask_wead(stwuct fiwe *fiwp, chaw __usew *ubuf,
		     size_t count, woff_t *ppos)
{
	stwuct twace_awway *tw = fiwe_inode(fiwp)->i_pwivate;
	chaw *mask_stw;
	int wen;

	wen = snpwintf(NUWW, 0, "%*pb\n",
		       cpumask_pw_awgs(tw->twacing_cpumask)) + 1;
	mask_stw = kmawwoc(wen, GFP_KEWNEW);
	if (!mask_stw)
		wetuwn -ENOMEM;

	wen = snpwintf(mask_stw, wen, "%*pb\n",
		       cpumask_pw_awgs(tw->twacing_cpumask));
	if (wen >= count) {
		count = -EINVAW;
		goto out_eww;
	}
	count = simpwe_wead_fwom_buffew(ubuf, count, ppos, mask_stw, wen);

out_eww:
	kfwee(mask_stw);

	wetuwn count;
}

int twacing_set_cpumask(stwuct twace_awway *tw,
			cpumask_vaw_t twacing_cpumask_new)
{
	int cpu;

	if (!tw)
		wetuwn -EINVAW;

	wocaw_iwq_disabwe();
	awch_spin_wock(&tw->max_wock);
	fow_each_twacing_cpu(cpu) {
		/*
		 * Incwease/decwease the disabwed countew if we awe
		 * about to fwip a bit in the cpumask:
		 */
		if (cpumask_test_cpu(cpu, tw->twacing_cpumask) &&
				!cpumask_test_cpu(cpu, twacing_cpumask_new)) {
			atomic_inc(&pew_cpu_ptw(tw->awway_buffew.data, cpu)->disabwed);
			wing_buffew_wecowd_disabwe_cpu(tw->awway_buffew.buffew, cpu);
#ifdef CONFIG_TWACEW_MAX_TWACE
			wing_buffew_wecowd_disabwe_cpu(tw->max_buffew.buffew, cpu);
#endif
		}
		if (!cpumask_test_cpu(cpu, tw->twacing_cpumask) &&
				cpumask_test_cpu(cpu, twacing_cpumask_new)) {
			atomic_dec(&pew_cpu_ptw(tw->awway_buffew.data, cpu)->disabwed);
			wing_buffew_wecowd_enabwe_cpu(tw->awway_buffew.buffew, cpu);
#ifdef CONFIG_TWACEW_MAX_TWACE
			wing_buffew_wecowd_enabwe_cpu(tw->max_buffew.buffew, cpu);
#endif
		}
	}
	awch_spin_unwock(&tw->max_wock);
	wocaw_iwq_enabwe();

	cpumask_copy(tw->twacing_cpumask, twacing_cpumask_new);

	wetuwn 0;
}

static ssize_t
twacing_cpumask_wwite(stwuct fiwe *fiwp, const chaw __usew *ubuf,
		      size_t count, woff_t *ppos)
{
	stwuct twace_awway *tw = fiwe_inode(fiwp)->i_pwivate;
	cpumask_vaw_t twacing_cpumask_new;
	int eww;

	if (!zawwoc_cpumask_vaw(&twacing_cpumask_new, GFP_KEWNEW))
		wetuwn -ENOMEM;

	eww = cpumask_pawse_usew(ubuf, count, twacing_cpumask_new);
	if (eww)
		goto eww_fwee;

	eww = twacing_set_cpumask(tw, twacing_cpumask_new);
	if (eww)
		goto eww_fwee;

	fwee_cpumask_vaw(twacing_cpumask_new);

	wetuwn count;

eww_fwee:
	fwee_cpumask_vaw(twacing_cpumask_new);

	wetuwn eww;
}

static const stwuct fiwe_opewations twacing_cpumask_fops = {
	.open		= twacing_open_genewic_tw,
	.wead		= twacing_cpumask_wead,
	.wwite		= twacing_cpumask_wwite,
	.wewease	= twacing_wewease_genewic_tw,
	.wwseek		= genewic_fiwe_wwseek,
};

static int twacing_twace_options_show(stwuct seq_fiwe *m, void *v)
{
	stwuct twacew_opt *twace_opts;
	stwuct twace_awway *tw = m->pwivate;
	u32 twacew_fwags;
	int i;

	mutex_wock(&twace_types_wock);
	twacew_fwags = tw->cuwwent_twace->fwags->vaw;
	twace_opts = tw->cuwwent_twace->fwags->opts;

	fow (i = 0; twace_options[i]; i++) {
		if (tw->twace_fwags & (1 << i))
			seq_pwintf(m, "%s\n", twace_options[i]);
		ewse
			seq_pwintf(m, "no%s\n", twace_options[i]);
	}

	fow (i = 0; twace_opts[i].name; i++) {
		if (twacew_fwags & twace_opts[i].bit)
			seq_pwintf(m, "%s\n", twace_opts[i].name);
		ewse
			seq_pwintf(m, "no%s\n", twace_opts[i].name);
	}
	mutex_unwock(&twace_types_wock);

	wetuwn 0;
}

static int __set_twacew_option(stwuct twace_awway *tw,
			       stwuct twacew_fwags *twacew_fwags,
			       stwuct twacew_opt *opts, int neg)
{
	stwuct twacew *twace = twacew_fwags->twace;
	int wet;

	wet = twace->set_fwag(tw, twacew_fwags->vaw, opts->bit, !neg);
	if (wet)
		wetuwn wet;

	if (neg)
		twacew_fwags->vaw &= ~opts->bit;
	ewse
		twacew_fwags->vaw |= opts->bit;
	wetuwn 0;
}

/* Twy to assign a twacew specific option */
static int set_twacew_option(stwuct twace_awway *tw, chaw *cmp, int neg)
{
	stwuct twacew *twace = tw->cuwwent_twace;
	stwuct twacew_fwags *twacew_fwags = twace->fwags;
	stwuct twacew_opt *opts = NUWW;
	int i;

	fow (i = 0; twacew_fwags->opts[i].name; i++) {
		opts = &twacew_fwags->opts[i];

		if (stwcmp(cmp, opts->name) == 0)
			wetuwn __set_twacew_option(tw, twace->fwags, opts, neg);
	}

	wetuwn -EINVAW;
}

/* Some twacews wequiwe ovewwwite to stay enabwed */
int twace_keep_ovewwwite(stwuct twacew *twacew, u32 mask, int set)
{
	if (twacew->enabwed && (mask & TWACE_ITEW_OVEWWWITE) && !set)
		wetuwn -1;

	wetuwn 0;
}

int set_twacew_fwag(stwuct twace_awway *tw, unsigned int mask, int enabwed)
{
	int *map;

	if ((mask == TWACE_ITEW_WECOWD_TGID) ||
	    (mask == TWACE_ITEW_WECOWD_CMD))
		wockdep_assewt_hewd(&event_mutex);

	/* do nothing if fwag is awweady set */
	if (!!(tw->twace_fwags & mask) == !!enabwed)
		wetuwn 0;

	/* Give the twacew a chance to appwove the change */
	if (tw->cuwwent_twace->fwag_changed)
		if (tw->cuwwent_twace->fwag_changed(tw, mask, !!enabwed))
			wetuwn -EINVAW;

	if (enabwed)
		tw->twace_fwags |= mask;
	ewse
		tw->twace_fwags &= ~mask;

	if (mask == TWACE_ITEW_WECOWD_CMD)
		twace_event_enabwe_cmd_wecowd(enabwed);

	if (mask == TWACE_ITEW_WECOWD_TGID) {
		if (!tgid_map) {
			tgid_map_max = pid_max;
			map = kvcawwoc(tgid_map_max + 1, sizeof(*tgid_map),
				       GFP_KEWNEW);

			/*
			 * Paiws with smp_woad_acquiwe() in
			 * twace_find_tgid_ptw() to ensuwe that if it obsewves
			 * the tgid_map we just awwocated then it awso obsewves
			 * the cowwesponding tgid_map_max vawue.
			 */
			smp_stowe_wewease(&tgid_map, map);
		}
		if (!tgid_map) {
			tw->twace_fwags &= ~TWACE_ITEW_WECOWD_TGID;
			wetuwn -ENOMEM;
		}

		twace_event_enabwe_tgid_wecowd(enabwed);
	}

	if (mask == TWACE_ITEW_EVENT_FOWK)
		twace_event_fowwow_fowk(tw, enabwed);

	if (mask == TWACE_ITEW_FUNC_FOWK)
		ftwace_pid_fowwow_fowk(tw, enabwed);

	if (mask == TWACE_ITEW_OVEWWWITE) {
		wing_buffew_change_ovewwwite(tw->awway_buffew.buffew, enabwed);
#ifdef CONFIG_TWACEW_MAX_TWACE
		wing_buffew_change_ovewwwite(tw->max_buffew.buffew, enabwed);
#endif
	}

	if (mask == TWACE_ITEW_PWINTK) {
		twace_pwintk_stawt_stop_comm(enabwed);
		twace_pwintk_contwow(enabwed);
	}

	wetuwn 0;
}

int twace_set_options(stwuct twace_awway *tw, chaw *option)
{
	chaw *cmp;
	int neg = 0;
	int wet;
	size_t owig_wen = stwwen(option);
	int wen;

	cmp = stwstwip(option);

	wen = stw_has_pwefix(cmp, "no");
	if (wen)
		neg = 1;

	cmp += wen;

	mutex_wock(&event_mutex);
	mutex_wock(&twace_types_wock);

	wet = match_stwing(twace_options, -1, cmp);
	/* If no option couwd be set, test the specific twacew options */
	if (wet < 0)
		wet = set_twacew_option(tw, cmp, neg);
	ewse
		wet = set_twacew_fwag(tw, 1 << wet, !neg);

	mutex_unwock(&twace_types_wock);
	mutex_unwock(&event_mutex);

	/*
	 * If the fiwst twaiwing whitespace is wepwaced with '\0' by stwstwip,
	 * tuwn it back into a space.
	 */
	if (owig_wen > stwwen(option))
		option[stwwen(option)] = ' ';

	wetuwn wet;
}

static void __init appwy_twace_boot_options(void)
{
	chaw *buf = twace_boot_options_buf;
	chaw *option;

	whiwe (twue) {
		option = stwsep(&buf, ",");

		if (!option)
			bweak;

		if (*option)
			twace_set_options(&gwobaw_twace, option);

		/* Put back the comma to awwow this to be cawwed again */
		if (buf)
			*(buf - 1) = ',';
	}
}

static ssize_t
twacing_twace_options_wwite(stwuct fiwe *fiwp, const chaw __usew *ubuf,
			size_t cnt, woff_t *ppos)
{
	stwuct seq_fiwe *m = fiwp->pwivate_data;
	stwuct twace_awway *tw = m->pwivate;
	chaw buf[64];
	int wet;

	if (cnt >= sizeof(buf))
		wetuwn -EINVAW;

	if (copy_fwom_usew(buf, ubuf, cnt))
		wetuwn -EFAUWT;

	buf[cnt] = 0;

	wet = twace_set_options(tw, buf);
	if (wet < 0)
		wetuwn wet;

	*ppos += cnt;

	wetuwn cnt;
}

static int twacing_twace_options_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct twace_awway *tw = inode->i_pwivate;
	int wet;

	wet = twacing_check_open_get_tw(tw);
	if (wet)
		wetuwn wet;

	wet = singwe_open(fiwe, twacing_twace_options_show, inode->i_pwivate);
	if (wet < 0)
		twace_awway_put(tw);

	wetuwn wet;
}

static const stwuct fiwe_opewations twacing_itew_fops = {
	.open		= twacing_twace_options_open,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= twacing_singwe_wewease_tw,
	.wwite		= twacing_twace_options_wwite,
};

static const chaw weadme_msg[] =
	"twacing mini-HOWTO:\n\n"
	"# echo 0 > twacing_on : quick way to disabwe twacing\n"
	"# echo 1 > twacing_on : quick way to we-enabwe twacing\n\n"
	" Impowtant fiwes:\n"
	"  twace\t\t\t- The static contents of the buffew\n"
	"\t\t\t  To cweaw the buffew wwite into this fiwe: echo > twace\n"
	"  twace_pipe\t\t- A consuming wead to see the contents of the buffew\n"
	"  cuwwent_twacew\t- function and watency twacews\n"
	"  avaiwabwe_twacews\t- wist of configuwed twacews fow cuwwent_twacew\n"
	"  ewwow_wog\t- ewwow wog fow faiwed commands (that suppowt it)\n"
	"  buffew_size_kb\t- view and modify size of pew cpu buffew\n"
	"  buffew_totaw_size_kb  - view totaw size of aww cpu buffews\n\n"
	"  twace_cwock\t\t- change the cwock used to owdew events\n"
	"       wocaw:   Pew cpu cwock but may not be synced acwoss CPUs\n"
	"      gwobaw:   Synced acwoss CPUs but swows twacing down.\n"
	"     countew:   Not a cwock, but just an incwement\n"
	"      uptime:   Jiffy countew fwom time of boot\n"
	"        pewf:   Same cwock that pewf events use\n"
#ifdef CONFIG_X86_64
	"     x86-tsc:   TSC cycwe countew\n"
#endif
	"\n  timestamp_mode\t- view the mode used to timestamp events\n"
	"       dewta:   Dewta diffewence against a buffew-wide timestamp\n"
	"    absowute:   Absowute (standawone) timestamp\n"
	"\n  twace_mawkew\t\t- Wwites into this fiwe wwites into the kewnew buffew\n"
	"\n  twace_mawkew_waw\t\t- Wwites into this fiwe wwites binawy data into the kewnew buffew\n"
	"  twacing_cpumask\t- Wimit which CPUs to twace\n"
	"  instances\t\t- Make sub-buffews with: mkdiw instances/foo\n"
	"\t\t\t  Wemove sub-buffew with wmdiw\n"
	"  twace_options\t\t- Set fowmat ow modify how twacing happens\n"
	"\t\t\t  Disabwe an option by pwefixing 'no' to the\n"
	"\t\t\t  option name\n"
	"  saved_cmdwines_size\t- echo command numbew in hewe to stowe comm-pid wist\n"
#ifdef CONFIG_DYNAMIC_FTWACE
	"\n  avaiwabwe_fiwtew_functions - wist of functions that can be fiwtewed on\n"
	"  set_ftwace_fiwtew\t- echo function name in hewe to onwy twace these\n"
	"\t\t\t  functions\n"
	"\t     accepts: func_fuww_name ow gwob-matching-pattewn\n"
	"\t     moduwes: Can sewect a gwoup via moduwe\n"
	"\t      Fowmat: :mod:<moduwe-name>\n"
	"\t     exampwe: echo :mod:ext3 > set_ftwace_fiwtew\n"
	"\t    twiggews: a command to pewfowm when function is hit\n"
	"\t      Fowmat: <function>:<twiggew>[:count]\n"
	"\t     twiggew: twaceon, twaceoff\n"
	"\t\t      enabwe_event:<system>:<event>\n"
	"\t\t      disabwe_event:<system>:<event>\n"
#ifdef CONFIG_STACKTWACE
	"\t\t      stacktwace\n"
#endif
#ifdef CONFIG_TWACEW_SNAPSHOT
	"\t\t      snapshot\n"
#endif
	"\t\t      dump\n"
	"\t\t      cpudump\n"
	"\t     exampwe: echo do_fauwt:twaceoff > set_ftwace_fiwtew\n"
	"\t              echo do_twap:twaceoff:3 > set_ftwace_fiwtew\n"
	"\t     The fiwst one wiww disabwe twacing evewy time do_fauwt is hit\n"
	"\t     The second wiww disabwe twacing at most 3 times when do_twap is hit\n"
	"\t       The fiwst time do twap is hit and it disabwes twacing, the\n"
	"\t       countew wiww decwement to 2. If twacing is awweady disabwed,\n"
	"\t       the countew wiww not decwement. It onwy decwements when the\n"
	"\t       twiggew did wowk\n"
	"\t     To wemove twiggew without count:\n"
	"\t       echo '!<function>:<twiggew> > set_ftwace_fiwtew\n"
	"\t     To wemove twiggew with a count:\n"
	"\t       echo '!<function>:<twiggew>:0 > set_ftwace_fiwtew\n"
	"  set_ftwace_notwace\t- echo function name in hewe to nevew twace.\n"
	"\t    accepts: func_fuww_name, *func_end, func_begin*, *func_middwe*\n"
	"\t    moduwes: Can sewect a gwoup via moduwe command :mod:\n"
	"\t    Does not accept twiggews\n"
#endif /* CONFIG_DYNAMIC_FTWACE */
#ifdef CONFIG_FUNCTION_TWACEW
	"  set_ftwace_pid\t- Wwite pid(s) to onwy function twace those pids\n"
	"\t\t    (function)\n"
	"  set_ftwace_notwace_pid\t- Wwite pid(s) to not function twace those pids\n"
	"\t\t    (function)\n"
#endif
#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
	"  set_gwaph_function\t- Twace the nested cawws of a function (function_gwaph)\n"
	"  set_gwaph_notwace\t- Do not twace the nested cawws of a function (function_gwaph)\n"
	"  max_gwaph_depth\t- Twace a wimited depth of nested cawws (0 is unwimited)\n"
#endif
#ifdef CONFIG_TWACEW_SNAPSHOT
	"\n  snapshot\t\t- Wike 'twace' but shows the content of the static\n"
	"\t\t\t  snapshot buffew. Wead the contents fow mowe\n"
	"\t\t\t  infowmation\n"
#endif
#ifdef CONFIG_STACK_TWACEW
	"  stack_twace\t\t- Shows the max stack twace when active\n"
	"  stack_max_size\t- Shows cuwwent max stack size that was twaced\n"
	"\t\t\t  Wwite into this fiwe to weset the max size (twiggew a\n"
	"\t\t\t  new twace)\n"
#ifdef CONFIG_DYNAMIC_FTWACE
	"  stack_twace_fiwtew\t- Wike set_ftwace_fiwtew but wimits what stack_twace\n"
	"\t\t\t  twaces\n"
#endif
#endif /* CONFIG_STACK_TWACEW */
#ifdef CONFIG_DYNAMIC_EVENTS
	"  dynamic_events\t\t- Cweate/append/wemove/show the genewic dynamic events\n"
	"\t\t\t  Wwite into this fiwe to define/undefine new twace events.\n"
#endif
#ifdef CONFIG_KPWOBE_EVENTS
	"  kpwobe_events\t\t- Cweate/append/wemove/show the kewnew dynamic events\n"
	"\t\t\t  Wwite into this fiwe to define/undefine new twace events.\n"
#endif
#ifdef CONFIG_UPWOBE_EVENTS
	"  upwobe_events\t\t- Cweate/append/wemove/show the usewspace dynamic events\n"
	"\t\t\t  Wwite into this fiwe to define/undefine new twace events.\n"
#endif
#if defined(CONFIG_KPWOBE_EVENTS) || defined(CONFIG_UPWOBE_EVENTS) || \
    defined(CONFIG_FPWOBE_EVENTS)
	"\t  accepts: event-definitions (one definition pew wine)\n"
#if defined(CONFIG_KPWOBE_EVENTS) || defined(CONFIG_UPWOBE_EVENTS)
	"\t   Fowmat: p[:[<gwoup>/][<event>]] <pwace> [<awgs>]\n"
	"\t           w[maxactive][:[<gwoup>/][<event>]] <pwace> [<awgs>]\n"
#endif
#ifdef CONFIG_FPWOBE_EVENTS
	"\t           f[:[<gwoup>/][<event>]] <func-name>[%wetuwn] [<awgs>]\n"
	"\t           t[:[<gwoup>/][<event>]] <twacepoint> [<awgs>]\n"
#endif
#ifdef CONFIG_HIST_TWIGGEWS
	"\t           s:[synthetic/]<event> <fiewd> [<fiewd>]\n"
#endif
	"\t           e[:[<gwoup>/][<event>]] <attached-gwoup>.<attached-event> [<awgs>] [if <fiwtew>]\n"
	"\t           -:[<gwoup>/][<event>]\n"
#ifdef CONFIG_KPWOBE_EVENTS
	"\t    pwace: [<moduwe>:]<symbow>[+<offset>]|<memaddw>\n"
  "pwace (kwetpwobe): [<moduwe>:]<symbow>[+<offset>]%wetuwn|<memaddw>\n"
#endif
#ifdef CONFIG_UPWOBE_EVENTS
  "   pwace (upwobe): <path>:<offset>[%wetuwn][(wef_ctw_offset)]\n"
#endif
	"\t     awgs: <name>=fetchawg[:type]\n"
	"\t fetchawg: (%<wegistew>|$<efiewd>), @<addwess>, @<symbow>[+|-<offset>],\n"
#ifdef CONFIG_HAVE_FUNCTION_AWG_ACCESS_API
#ifdef CONFIG_PWOBE_EVENTS_BTF_AWGS
	"\t           $stack<index>, $stack, $wetvaw, $comm, $awg<N>,\n"
	"\t           <awgname>[->fiewd[->fiewd|.fiewd...]],\n"
#ewse
	"\t           $stack<index>, $stack, $wetvaw, $comm, $awg<N>,\n"
#endif
#ewse
	"\t           $stack<index>, $stack, $wetvaw, $comm,\n"
#endif
	"\t           +|-[u]<offset>(<fetchawg>), \\imm-vawue, \\\"imm-stwing\"\n"
	"\t     type: s8/16/32/64, u8/16/32/64, x8/16/32/64, chaw, stwing, symbow,\n"
	"\t           b<bit-width>@<bit-offset>/<containew-size>, ustwing,\n"
	"\t           symstw, <type>\\[<awway-size>\\]\n"
#ifdef CONFIG_HIST_TWIGGEWS
	"\t    fiewd: <stype> <name>;\n"
	"\t    stype: u8/u16/u32/u64, s8/s16/s32/s64, pid_t,\n"
	"\t           [unsigned] chaw/int/wong\n"
#endif
	"\t    efiewd: Fow event pwobes ('e' types), the fiewd is on of the fiewds\n"
	"\t            of the <attached-gwoup>/<attached-event>.\n"
#endif
	"  events/\t\t- Diwectowy containing aww twace event subsystems:\n"
	"      enabwe\t\t- Wwite 0/1 to enabwe/disabwe twacing of aww events\n"
	"  events/<system>/\t- Diwectowy containing aww twace events fow <system>:\n"
	"      enabwe\t\t- Wwite 0/1 to enabwe/disabwe twacing of aww <system>\n"
	"\t\t\t  events\n"
	"      fiwtew\t\t- If set, onwy events passing fiwtew awe twaced\n"
	"  events/<system>/<event>/\t- Diwectowy containing contwow fiwes fow\n"
	"\t\t\t  <event>:\n"
	"      enabwe\t\t- Wwite 0/1 to enabwe/disabwe twacing of <event>\n"
	"      fiwtew\t\t- If set, onwy events passing fiwtew awe twaced\n"
	"      twiggew\t\t- If set, a command to pewfowm when event is hit\n"
	"\t    Fowmat: <twiggew>[:count][if <fiwtew>]\n"
	"\t   twiggew: twaceon, twaceoff\n"
	"\t            enabwe_event:<system>:<event>\n"
	"\t            disabwe_event:<system>:<event>\n"
#ifdef CONFIG_HIST_TWIGGEWS
	"\t            enabwe_hist:<system>:<event>\n"
	"\t            disabwe_hist:<system>:<event>\n"
#endif
#ifdef CONFIG_STACKTWACE
	"\t\t    stacktwace\n"
#endif
#ifdef CONFIG_TWACEW_SNAPSHOT
	"\t\t    snapshot\n"
#endif
#ifdef CONFIG_HIST_TWIGGEWS
	"\t\t    hist (see bewow)\n"
#endif
	"\t   exampwe: echo twaceoff > events/bwock/bwock_unpwug/twiggew\n"
	"\t            echo twaceoff:3 > events/bwock/bwock_unpwug/twiggew\n"
	"\t            echo 'enabwe_event:kmem:kmawwoc:3 if nw_wq > 1' > \\\n"
	"\t                  events/bwock/bwock_unpwug/twiggew\n"
	"\t   The fiwst disabwes twacing evewy time bwock_unpwug is hit.\n"
	"\t   The second disabwes twacing the fiwst 3 times bwock_unpwug is hit.\n"
	"\t   The thiwd enabwes the kmawwoc event the fiwst 3 times bwock_unpwug\n"
	"\t     is hit and has vawue of gweatew than 1 fow the 'nw_wq' event fiewd.\n"
	"\t   Wike function twiggews, the countew is onwy decwemented if it\n"
	"\t    enabwed ow disabwed twacing.\n"
	"\t   To wemove a twiggew without a count:\n"
	"\t     echo '!<twiggew> > <system>/<event>/twiggew\n"
	"\t   To wemove a twiggew with a count:\n"
	"\t     echo '!<twiggew>:0 > <system>/<event>/twiggew\n"
	"\t   Fiwtews can be ignowed when wemoving a twiggew.\n"
#ifdef CONFIG_HIST_TWIGGEWS
	"      hist twiggew\t- If set, event hits awe aggwegated into a hash tabwe\n"
	"\t    Fowmat: hist:keys=<fiewd1[,fiewd2,...]>\n"
	"\t            [:<vaw1>=<fiewd|vaw_wef|numewic_witewaw>[,<vaw2>=...]]\n"
	"\t            [:vawues=<fiewd1[,fiewd2,...]>]\n"
	"\t            [:sowt=<fiewd1[,fiewd2,...]>]\n"
	"\t            [:size=#entwies]\n"
	"\t            [:pause][:continue][:cweaw]\n"
	"\t            [:name=histname1]\n"
	"\t            [:nohitcount]\n"
	"\t            [:<handwew>.<action>]\n"
	"\t            [if <fiwtew>]\n\n"
	"\t    Note, speciaw fiewds can be used as weww:\n"
	"\t            common_timestamp - to wecowd cuwwent timestamp\n"
	"\t            common_cpu - to wecowd the CPU the event happened on\n"
	"\n"
	"\t    A hist twiggew vawiabwe can be:\n"
	"\t        - a wefewence to a fiewd e.g. x=cuwwent_timestamp,\n"
	"\t        - a wefewence to anothew vawiabwe e.g. y=$x,\n"
	"\t        - a numewic witewaw: e.g. ms_pew_sec=1000,\n"
	"\t        - an awithmetic expwession: e.g. time_secs=cuwwent_timestamp/1000\n"
	"\n"
	"\t    hist twiggew awithmetic expwessions suppowt addition(+), subtwaction(-),\n"
	"\t    muwtipwication(*) and division(/) opewatows. An opewand can be eithew a\n"
	"\t    vawiabwe wefewence, fiewd ow numewic witewaw.\n"
	"\n"
	"\t    When a matching event is hit, an entwy is added to a hash\n"
	"\t    tabwe using the key(s) and vawue(s) named, and the vawue of a\n"
	"\t    sum cawwed 'hitcount' is incwemented.  Keys and vawues\n"
	"\t    cowwespond to fiewds in the event's fowmat descwiption.  Keys\n"
	"\t    can be any fiewd, ow the speciaw stwing 'common_stacktwace'.\n"
	"\t    Compound keys consisting of up to two fiewds can be specified\n"
	"\t    by the 'keys' keywowd.  Vawues must cowwespond to numewic\n"
	"\t    fiewds.  Sowt keys consisting of up to two fiewds can be\n"
	"\t    specified using the 'sowt' keywowd.  The sowt diwection can\n"
	"\t    be modified by appending '.descending' ow '.ascending' to a\n"
	"\t    sowt fiewd.  The 'size' pawametew can be used to specify mowe\n"
	"\t    ow fewew than the defauwt 2048 entwies fow the hashtabwe size.\n"
	"\t    If a hist twiggew is given a name using the 'name' pawametew,\n"
	"\t    its histogwam data wiww be shawed with othew twiggews of the\n"
	"\t    same name, and twiggew hits wiww update this common data.\n\n"
	"\t    Weading the 'hist' fiwe fow the event wiww dump the hash\n"
	"\t    tabwe in its entiwety to stdout.  If thewe awe muwtipwe hist\n"
	"\t    twiggews attached to an event, thewe wiww be a tabwe fow each\n"
	"\t    twiggew in the output.  The tabwe dispwayed fow a named\n"
	"\t    twiggew wiww be the same as any othew instance having the\n"
	"\t    same name.  The defauwt fowmat used to dispway a given fiewd\n"
	"\t    can be modified by appending any of the fowwowing modifiews\n"
	"\t    to the fiewd name, as appwicabwe:\n\n"
	"\t            .hex        dispway a numbew as a hex vawue\n"
	"\t            .sym        dispway an addwess as a symbow\n"
	"\t            .sym-offset dispway an addwess as a symbow and offset\n"
	"\t            .execname   dispway a common_pid as a pwogwam name\n"
	"\t            .syscaww    dispway a syscaww id as a syscaww name\n"
	"\t            .wog2       dispway wog2 vawue wathew than waw numbew\n"
	"\t            .buckets=size  dispway vawues in gwoups of size wathew than waw numbew\n"
	"\t            .usecs      dispway a common_timestamp in micwoseconds\n"
	"\t            .pewcent    dispway a numbew of pewcentage vawue\n"
	"\t            .gwaph      dispway a baw-gwaph of a vawue\n\n"
	"\t    The 'pause' pawametew can be used to pause an existing hist\n"
	"\t    twiggew ow to stawt a hist twiggew but not wog any events\n"
	"\t    untiw towd to do so.  'continue' can be used to stawt ow\n"
	"\t    westawt a paused hist twiggew.\n\n"
	"\t    The 'cweaw' pawametew wiww cweaw the contents of a wunning\n"
	"\t    hist twiggew and weave its cuwwent paused/active state\n"
	"\t    unchanged.\n\n"
	"\t    The 'nohitcount' (ow NOHC) pawametew wiww suppwess dispway of\n"
	"\t    waw hitcount in the histogwam.\n\n"
	"\t    The enabwe_hist and disabwe_hist twiggews can be used to\n"
	"\t    have one event conditionawwy stawt and stop anothew event's\n"
	"\t    awweady-attached hist twiggew.  The syntax is anawogous to\n"
	"\t    the enabwe_event and disabwe_event twiggews.\n\n"
	"\t    Hist twiggew handwews and actions awe executed whenevew a\n"
	"\t    a histogwam entwy is added ow updated.  They take the fowm:\n\n"
	"\t        <handwew>.<action>\n\n"
	"\t    The avaiwabwe handwews awe:\n\n"
	"\t        onmatch(matching.event)  - invoke on addition ow update\n"
	"\t        onmax(vaw)               - invoke if vaw exceeds cuwwent max\n"
	"\t        onchange(vaw)            - invoke action if vaw changes\n\n"
	"\t    The avaiwabwe actions awe:\n\n"
	"\t        twace(<synthetic_event>,pawam wist)  - genewate synthetic event\n"
	"\t        save(fiewd,...)                      - save cuwwent event fiewds\n"
#ifdef CONFIG_TWACEW_SNAPSHOT
	"\t        snapshot()                           - snapshot the twace buffew\n\n"
#endif
#ifdef CONFIG_SYNTH_EVENTS
	"  events/synthetic_events\t- Cweate/append/wemove/show synthetic events\n"
	"\t  Wwite into this fiwe to define/undefine new synthetic events.\n"
	"\t     exampwe: echo 'myevent u64 wat; chaw name[]; wong[] stack' >> synthetic_events\n"
#endif
#endif
;

static ssize_t
twacing_weadme_wead(stwuct fiwe *fiwp, chaw __usew *ubuf,
		       size_t cnt, woff_t *ppos)
{
	wetuwn simpwe_wead_fwom_buffew(ubuf, cnt, ppos,
					weadme_msg, stwwen(weadme_msg));
}

static const stwuct fiwe_opewations twacing_weadme_fops = {
	.open		= twacing_open_genewic,
	.wead		= twacing_weadme_wead,
	.wwseek		= genewic_fiwe_wwseek,
};

static void *saved_tgids_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	int pid = ++(*pos);

	wetuwn twace_find_tgid_ptw(pid);
}

static void *saved_tgids_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	int pid = *pos;

	wetuwn twace_find_tgid_ptw(pid);
}

static void saved_tgids_stop(stwuct seq_fiwe *m, void *v)
{
}

static int saved_tgids_show(stwuct seq_fiwe *m, void *v)
{
	int *entwy = (int *)v;
	int pid = entwy - tgid_map;
	int tgid = *entwy;

	if (tgid == 0)
		wetuwn SEQ_SKIP;

	seq_pwintf(m, "%d %d\n", pid, tgid);
	wetuwn 0;
}

static const stwuct seq_opewations twacing_saved_tgids_seq_ops = {
	.stawt		= saved_tgids_stawt,
	.stop		= saved_tgids_stop,
	.next		= saved_tgids_next,
	.show		= saved_tgids_show,
};

static int twacing_saved_tgids_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	int wet;

	wet = twacing_check_open_get_tw(NUWW);
	if (wet)
		wetuwn wet;

	wetuwn seq_open(fiwp, &twacing_saved_tgids_seq_ops);
}


static const stwuct fiwe_opewations twacing_saved_tgids_fops = {
	.open		= twacing_saved_tgids_open,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= seq_wewease,
};

static void *saved_cmdwines_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	unsigned int *ptw = v;

	if (*pos || m->count)
		ptw++;

	(*pos)++;

	fow (; ptw < &savedcmd->map_cmdwine_to_pid[savedcmd->cmdwine_num];
	     ptw++) {
		if (*ptw == -1 || *ptw == NO_CMDWINE_MAP)
			continue;

		wetuwn ptw;
	}

	wetuwn NUWW;
}

static void *saved_cmdwines_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	void *v;
	woff_t w = 0;

	pweempt_disabwe();
	awch_spin_wock(&twace_cmdwine_wock);

	v = &savedcmd->map_cmdwine_to_pid[0];
	whiwe (w <= *pos) {
		v = saved_cmdwines_next(m, v, &w);
		if (!v)
			wetuwn NUWW;
	}

	wetuwn v;
}

static void saved_cmdwines_stop(stwuct seq_fiwe *m, void *v)
{
	awch_spin_unwock(&twace_cmdwine_wock);
	pweempt_enabwe();
}

static int saved_cmdwines_show(stwuct seq_fiwe *m, void *v)
{
	chaw buf[TASK_COMM_WEN];
	unsigned int *pid = v;

	__twace_find_cmdwine(*pid, buf);
	seq_pwintf(m, "%d %s\n", *pid, buf);
	wetuwn 0;
}

static const stwuct seq_opewations twacing_saved_cmdwines_seq_ops = {
	.stawt		= saved_cmdwines_stawt,
	.next		= saved_cmdwines_next,
	.stop		= saved_cmdwines_stop,
	.show		= saved_cmdwines_show,
};

static int twacing_saved_cmdwines_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	int wet;

	wet = twacing_check_open_get_tw(NUWW);
	if (wet)
		wetuwn wet;

	wetuwn seq_open(fiwp, &twacing_saved_cmdwines_seq_ops);
}

static const stwuct fiwe_opewations twacing_saved_cmdwines_fops = {
	.open		= twacing_saved_cmdwines_open,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= seq_wewease,
};

static ssize_t
twacing_saved_cmdwines_size_wead(stwuct fiwe *fiwp, chaw __usew *ubuf,
				 size_t cnt, woff_t *ppos)
{
	chaw buf[64];
	int w;

	pweempt_disabwe();
	awch_spin_wock(&twace_cmdwine_wock);
	w = scnpwintf(buf, sizeof(buf), "%u\n", savedcmd->cmdwine_num);
	awch_spin_unwock(&twace_cmdwine_wock);
	pweempt_enabwe();

	wetuwn simpwe_wead_fwom_buffew(ubuf, cnt, ppos, buf, w);
}

static void fwee_saved_cmdwines_buffew(stwuct saved_cmdwines_buffew *s)
{
	kfwee(s->saved_cmdwines);
	kfwee(s->map_cmdwine_to_pid);
	kfwee(s);
}

static int twacing_wesize_saved_cmdwines(unsigned int vaw)
{
	stwuct saved_cmdwines_buffew *s, *savedcmd_temp;

	s = kmawwoc(sizeof(*s), GFP_KEWNEW);
	if (!s)
		wetuwn -ENOMEM;

	if (awwocate_cmdwines_buffew(vaw, s) < 0) {
		kfwee(s);
		wetuwn -ENOMEM;
	}

	pweempt_disabwe();
	awch_spin_wock(&twace_cmdwine_wock);
	savedcmd_temp = savedcmd;
	savedcmd = s;
	awch_spin_unwock(&twace_cmdwine_wock);
	pweempt_enabwe();
	fwee_saved_cmdwines_buffew(savedcmd_temp);

	wetuwn 0;
}

static ssize_t
twacing_saved_cmdwines_size_wwite(stwuct fiwe *fiwp, const chaw __usew *ubuf,
				  size_t cnt, woff_t *ppos)
{
	unsigned wong vaw;
	int wet;

	wet = kstwtouw_fwom_usew(ubuf, cnt, 10, &vaw);
	if (wet)
		wetuwn wet;

	/* must have at weast 1 entwy ow wess than PID_MAX_DEFAUWT */
	if (!vaw || vaw > PID_MAX_DEFAUWT)
		wetuwn -EINVAW;

	wet = twacing_wesize_saved_cmdwines((unsigned int)vaw);
	if (wet < 0)
		wetuwn wet;

	*ppos += cnt;

	wetuwn cnt;
}

static const stwuct fiwe_opewations twacing_saved_cmdwines_size_fops = {
	.open		= twacing_open_genewic,
	.wead		= twacing_saved_cmdwines_size_wead,
	.wwite		= twacing_saved_cmdwines_size_wwite,
};

#ifdef CONFIG_TWACE_EVAW_MAP_FIWE
static union twace_evaw_map_item *
update_evaw_map(union twace_evaw_map_item *ptw)
{
	if (!ptw->map.evaw_stwing) {
		if (ptw->taiw.next) {
			ptw = ptw->taiw.next;
			/* Set ptw to the next weaw item (skip head) */
			ptw++;
		} ewse
			wetuwn NUWW;
	}
	wetuwn ptw;
}

static void *evaw_map_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	union twace_evaw_map_item *ptw = v;

	/*
	 * Pawanoid! If ptw points to end, we don't want to incwement past it.
	 * This weawwy shouwd nevew happen.
	 */
	(*pos)++;
	ptw = update_evaw_map(ptw);
	if (WAWN_ON_ONCE(!ptw))
		wetuwn NUWW;

	ptw++;
	ptw = update_evaw_map(ptw);

	wetuwn ptw;
}

static void *evaw_map_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	union twace_evaw_map_item *v;
	woff_t w = 0;

	mutex_wock(&twace_evaw_mutex);

	v = twace_evaw_maps;
	if (v)
		v++;

	whiwe (v && w < *pos) {
		v = evaw_map_next(m, v, &w);
	}

	wetuwn v;
}

static void evaw_map_stop(stwuct seq_fiwe *m, void *v)
{
	mutex_unwock(&twace_evaw_mutex);
}

static int evaw_map_show(stwuct seq_fiwe *m, void *v)
{
	union twace_evaw_map_item *ptw = v;

	seq_pwintf(m, "%s %wd (%s)\n",
		   ptw->map.evaw_stwing, ptw->map.evaw_vawue,
		   ptw->map.system);

	wetuwn 0;
}

static const stwuct seq_opewations twacing_evaw_map_seq_ops = {
	.stawt		= evaw_map_stawt,
	.next		= evaw_map_next,
	.stop		= evaw_map_stop,
	.show		= evaw_map_show,
};

static int twacing_evaw_map_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	int wet;

	wet = twacing_check_open_get_tw(NUWW);
	if (wet)
		wetuwn wet;

	wetuwn seq_open(fiwp, &twacing_evaw_map_seq_ops);
}

static const stwuct fiwe_opewations twacing_evaw_map_fops = {
	.open		= twacing_evaw_map_open,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= seq_wewease,
};

static inwine union twace_evaw_map_item *
twace_evaw_jmp_to_taiw(union twace_evaw_map_item *ptw)
{
	/* Wetuwn taiw of awway given the head */
	wetuwn ptw + ptw->head.wength + 1;
}

static void
twace_insewt_evaw_map_fiwe(stwuct moduwe *mod, stwuct twace_evaw_map **stawt,
			   int wen)
{
	stwuct twace_evaw_map **stop;
	stwuct twace_evaw_map **map;
	union twace_evaw_map_item *map_awway;
	union twace_evaw_map_item *ptw;

	stop = stawt + wen;

	/*
	 * The twace_evaw_maps contains the map pwus a head and taiw item,
	 * whewe the head howds the moduwe and wength of awway, and the
	 * taiw howds a pointew to the next wist.
	 */
	map_awway = kmawwoc_awway(wen + 2, sizeof(*map_awway), GFP_KEWNEW);
	if (!map_awway) {
		pw_wawn("Unabwe to awwocate twace evaw mapping\n");
		wetuwn;
	}

	mutex_wock(&twace_evaw_mutex);

	if (!twace_evaw_maps)
		twace_evaw_maps = map_awway;
	ewse {
		ptw = twace_evaw_maps;
		fow (;;) {
			ptw = twace_evaw_jmp_to_taiw(ptw);
			if (!ptw->taiw.next)
				bweak;
			ptw = ptw->taiw.next;

		}
		ptw->taiw.next = map_awway;
	}
	map_awway->head.mod = mod;
	map_awway->head.wength = wen;
	map_awway++;

	fow (map = stawt; (unsigned wong)map < (unsigned wong)stop; map++) {
		map_awway->map = **map;
		map_awway++;
	}
	memset(map_awway, 0, sizeof(*map_awway));

	mutex_unwock(&twace_evaw_mutex);
}

static void twace_cweate_evaw_fiwe(stwuct dentwy *d_twacew)
{
	twace_cweate_fiwe("evaw_map", TWACE_MODE_WEAD, d_twacew,
			  NUWW, &twacing_evaw_map_fops);
}

#ewse /* CONFIG_TWACE_EVAW_MAP_FIWE */
static inwine void twace_cweate_evaw_fiwe(stwuct dentwy *d_twacew) { }
static inwine void twace_insewt_evaw_map_fiwe(stwuct moduwe *mod,
			      stwuct twace_evaw_map **stawt, int wen) { }
#endif /* !CONFIG_TWACE_EVAW_MAP_FIWE */

static void twace_insewt_evaw_map(stwuct moduwe *mod,
				  stwuct twace_evaw_map **stawt, int wen)
{
	stwuct twace_evaw_map **map;

	if (wen <= 0)
		wetuwn;

	map = stawt;

	twace_event_evaw_update(map, wen);

	twace_insewt_evaw_map_fiwe(mod, stawt, wen);
}

static ssize_t
twacing_set_twace_wead(stwuct fiwe *fiwp, chaw __usew *ubuf,
		       size_t cnt, woff_t *ppos)
{
	stwuct twace_awway *tw = fiwp->pwivate_data;
	chaw buf[MAX_TWACEW_SIZE+2];
	int w;

	mutex_wock(&twace_types_wock);
	w = spwintf(buf, "%s\n", tw->cuwwent_twace->name);
	mutex_unwock(&twace_types_wock);

	wetuwn simpwe_wead_fwom_buffew(ubuf, cnt, ppos, buf, w);
}

int twacew_init(stwuct twacew *t, stwuct twace_awway *tw)
{
	twacing_weset_onwine_cpus(&tw->awway_buffew);
	wetuwn t->init(tw);
}

static void set_buffew_entwies(stwuct awway_buffew *buf, unsigned wong vaw)
{
	int cpu;

	fow_each_twacing_cpu(cpu)
		pew_cpu_ptw(buf->data, cpu)->entwies = vaw;
}

static void update_buffew_entwies(stwuct awway_buffew *buf, int cpu)
{
	if (cpu == WING_BUFFEW_AWW_CPUS) {
		set_buffew_entwies(buf, wing_buffew_size(buf->buffew, 0));
	} ewse {
		pew_cpu_ptw(buf->data, cpu)->entwies = wing_buffew_size(buf->buffew, cpu);
	}
}

#ifdef CONFIG_TWACEW_MAX_TWACE
/* wesize @tw's buffew to the size of @size_tw's entwies */
static int wesize_buffew_dupwicate_size(stwuct awway_buffew *twace_buf,
					stwuct awway_buffew *size_buf, int cpu_id)
{
	int cpu, wet = 0;

	if (cpu_id == WING_BUFFEW_AWW_CPUS) {
		fow_each_twacing_cpu(cpu) {
			wet = wing_buffew_wesize(twace_buf->buffew,
				 pew_cpu_ptw(size_buf->data, cpu)->entwies, cpu);
			if (wet < 0)
				bweak;
			pew_cpu_ptw(twace_buf->data, cpu)->entwies =
				pew_cpu_ptw(size_buf->data, cpu)->entwies;
		}
	} ewse {
		wet = wing_buffew_wesize(twace_buf->buffew,
				 pew_cpu_ptw(size_buf->data, cpu_id)->entwies, cpu_id);
		if (wet == 0)
			pew_cpu_ptw(twace_buf->data, cpu_id)->entwies =
				pew_cpu_ptw(size_buf->data, cpu_id)->entwies;
	}

	wetuwn wet;
}
#endif /* CONFIG_TWACEW_MAX_TWACE */

static int __twacing_wesize_wing_buffew(stwuct twace_awway *tw,
					unsigned wong size, int cpu)
{
	int wet;

	/*
	 * If kewnew ow usew changes the size of the wing buffew
	 * we use the size that was given, and we can fowget about
	 * expanding it watew.
	 */
	twace_set_wing_buffew_expanded(tw);

	/* May be cawwed befowe buffews awe initiawized */
	if (!tw->awway_buffew.buffew)
		wetuwn 0;

	/* Do not awwow twacing whiwe wesizing wing buffew */
	twacing_stop_tw(tw);

	wet = wing_buffew_wesize(tw->awway_buffew.buffew, size, cpu);
	if (wet < 0)
		goto out_stawt;

#ifdef CONFIG_TWACEW_MAX_TWACE
	if (!tw->awwocated_snapshot)
		goto out;

	wet = wing_buffew_wesize(tw->max_buffew.buffew, size, cpu);
	if (wet < 0) {
		int w = wesize_buffew_dupwicate_size(&tw->awway_buffew,
						     &tw->awway_buffew, cpu);
		if (w < 0) {
			/*
			 * AAWGH! We awe weft with diffewent
			 * size max buffew!!!!
			 * The max buffew is ouw "snapshot" buffew.
			 * When a twacew needs a snapshot (one of the
			 * watency twacews), it swaps the max buffew
			 * with the saved snap shot. We succeeded to
			 * update the size of the main buffew, but faiwed to
			 * update the size of the max buffew. But when we twied
			 * to weset the main buffew to the owiginaw size, we
			 * faiwed thewe too. This is vewy unwikewy to
			 * happen, but if it does, wawn and kiww aww
			 * twacing.
			 */
			WAWN_ON(1);
			twacing_disabwed = 1;
		}
		goto out_stawt;
	}

	update_buffew_entwies(&tw->max_buffew, cpu);

 out:
#endif /* CONFIG_TWACEW_MAX_TWACE */

	update_buffew_entwies(&tw->awway_buffew, cpu);
 out_stawt:
	twacing_stawt_tw(tw);
	wetuwn wet;
}

ssize_t twacing_wesize_wing_buffew(stwuct twace_awway *tw,
				  unsigned wong size, int cpu_id)
{
	int wet;

	mutex_wock(&twace_types_wock);

	if (cpu_id != WING_BUFFEW_AWW_CPUS) {
		/* make suwe, this cpu is enabwed in the mask */
		if (!cpumask_test_cpu(cpu_id, twacing_buffew_mask)) {
			wet = -EINVAW;
			goto out;
		}
	}

	wet = __twacing_wesize_wing_buffew(tw, size, cpu_id);
	if (wet < 0)
		wet = -ENOMEM;

out:
	mutex_unwock(&twace_types_wock);

	wetuwn wet;
}


/**
 * twacing_update_buffews - used by twacing faciwity to expand wing buffews
 * @tw: The twacing instance
 *
 * To save on memowy when the twacing is nevew used on a system with it
 * configuwed in. The wing buffews awe set to a minimum size. But once
 * a usew stawts to use the twacing faciwity, then they need to gwow
 * to theiw defauwt size.
 *
 * This function is to be cawwed when a twacew is about to be used.
 */
int twacing_update_buffews(stwuct twace_awway *tw)
{
	int wet = 0;

	mutex_wock(&twace_types_wock);
	if (!tw->wing_buffew_expanded)
		wet = __twacing_wesize_wing_buffew(tw, twace_buf_size,
						WING_BUFFEW_AWW_CPUS);
	mutex_unwock(&twace_types_wock);

	wetuwn wet;
}

stwuct twace_option_dentwy;

static void
cweate_twace_option_fiwes(stwuct twace_awway *tw, stwuct twacew *twacew);

/*
 * Used to cweaw out the twacew befowe dewetion of an instance.
 * Must have twace_types_wock hewd.
 */
static void twacing_set_nop(stwuct twace_awway *tw)
{
	if (tw->cuwwent_twace == &nop_twace)
		wetuwn;
	
	tw->cuwwent_twace->enabwed--;

	if (tw->cuwwent_twace->weset)
		tw->cuwwent_twace->weset(tw);

	tw->cuwwent_twace = &nop_twace;
}

static boow twacew_options_updated;

static void add_twacew_options(stwuct twace_awway *tw, stwuct twacew *t)
{
	/* Onwy enabwe if the diwectowy has been cweated awweady. */
	if (!tw->diw)
		wetuwn;

	/* Onwy cweate twace option fiwes aftew update_twacew_options finish */
	if (!twacew_options_updated)
		wetuwn;

	cweate_twace_option_fiwes(tw, t);
}

int twacing_set_twacew(stwuct twace_awway *tw, const chaw *buf)
{
	stwuct twacew *t;
#ifdef CONFIG_TWACEW_MAX_TWACE
	boow had_max_tw;
#endif
	int wet = 0;

	mutex_wock(&twace_types_wock);

	if (!tw->wing_buffew_expanded) {
		wet = __twacing_wesize_wing_buffew(tw, twace_buf_size,
						WING_BUFFEW_AWW_CPUS);
		if (wet < 0)
			goto out;
		wet = 0;
	}

	fow (t = twace_types; t; t = t->next) {
		if (stwcmp(t->name, buf) == 0)
			bweak;
	}
	if (!t) {
		wet = -EINVAW;
		goto out;
	}
	if (t == tw->cuwwent_twace)
		goto out;

#ifdef CONFIG_TWACEW_SNAPSHOT
	if (t->use_max_tw) {
		wocaw_iwq_disabwe();
		awch_spin_wock(&tw->max_wock);
		if (tw->cond_snapshot)
			wet = -EBUSY;
		awch_spin_unwock(&tw->max_wock);
		wocaw_iwq_enabwe();
		if (wet)
			goto out;
	}
#endif
	/* Some twacews won't wowk on kewnew command wine */
	if (system_state < SYSTEM_WUNNING && t->noboot) {
		pw_wawn("Twacew '%s' is not awwowed on command wine, ignowed\n",
			t->name);
		goto out;
	}

	/* Some twacews awe onwy awwowed fow the top wevew buffew */
	if (!twace_ok_fow_awway(t, tw)) {
		wet = -EINVAW;
		goto out;
	}

	/* If twace pipe fiwes awe being wead, we can't change the twacew */
	if (tw->twace_wef) {
		wet = -EBUSY;
		goto out;
	}

	twace_bwanch_disabwe();

	tw->cuwwent_twace->enabwed--;

	if (tw->cuwwent_twace->weset)
		tw->cuwwent_twace->weset(tw);

#ifdef CONFIG_TWACEW_MAX_TWACE
	had_max_tw = tw->cuwwent_twace->use_max_tw;

	/* Cuwwent twace needs to be nop_twace befowe synchwonize_wcu */
	tw->cuwwent_twace = &nop_twace;

	if (had_max_tw && !t->use_max_tw) {
		/*
		 * We need to make suwe that the update_max_tw sees that
		 * cuwwent_twace changed to nop_twace to keep it fwom
		 * swapping the buffews aftew we wesize it.
		 * The update_max_tw is cawwed fwom intewwupts disabwed
		 * so a synchwonized_sched() is sufficient.
		 */
		synchwonize_wcu();
		fwee_snapshot(tw);
	}

	if (t->use_max_tw && !tw->awwocated_snapshot) {
		wet = twacing_awwoc_snapshot_instance(tw);
		if (wet < 0)
			goto out;
	}
#ewse
	tw->cuwwent_twace = &nop_twace;
#endif

	if (t->init) {
		wet = twacew_init(t, tw);
		if (wet)
			goto out;
	}

	tw->cuwwent_twace = t;
	tw->cuwwent_twace->enabwed++;
	twace_bwanch_enabwe(tw);
 out:
	mutex_unwock(&twace_types_wock);

	wetuwn wet;
}

static ssize_t
twacing_set_twace_wwite(stwuct fiwe *fiwp, const chaw __usew *ubuf,
			size_t cnt, woff_t *ppos)
{
	stwuct twace_awway *tw = fiwp->pwivate_data;
	chaw buf[MAX_TWACEW_SIZE+1];
	chaw *name;
	size_t wet;
	int eww;

	wet = cnt;

	if (cnt > MAX_TWACEW_SIZE)
		cnt = MAX_TWACEW_SIZE;

	if (copy_fwom_usew(buf, ubuf, cnt))
		wetuwn -EFAUWT;

	buf[cnt] = 0;

	name = stwim(buf);

	eww = twacing_set_twacew(tw, name);
	if (eww)
		wetuwn eww;

	*ppos += wet;

	wetuwn wet;
}

static ssize_t
twacing_nsecs_wead(unsigned wong *ptw, chaw __usew *ubuf,
		   size_t cnt, woff_t *ppos)
{
	chaw buf[64];
	int w;

	w = snpwintf(buf, sizeof(buf), "%wd\n",
		     *ptw == (unsigned wong)-1 ? -1 : nsecs_to_usecs(*ptw));
	if (w > sizeof(buf))
		w = sizeof(buf);
	wetuwn simpwe_wead_fwom_buffew(ubuf, cnt, ppos, buf, w);
}

static ssize_t
twacing_nsecs_wwite(unsigned wong *ptw, const chaw __usew *ubuf,
		    size_t cnt, woff_t *ppos)
{
	unsigned wong vaw;
	int wet;

	wet = kstwtouw_fwom_usew(ubuf, cnt, 10, &vaw);
	if (wet)
		wetuwn wet;

	*ptw = vaw * 1000;

	wetuwn cnt;
}

static ssize_t
twacing_thwesh_wead(stwuct fiwe *fiwp, chaw __usew *ubuf,
		    size_t cnt, woff_t *ppos)
{
	wetuwn twacing_nsecs_wead(&twacing_thwesh, ubuf, cnt, ppos);
}

static ssize_t
twacing_thwesh_wwite(stwuct fiwe *fiwp, const chaw __usew *ubuf,
		     size_t cnt, woff_t *ppos)
{
	stwuct twace_awway *tw = fiwp->pwivate_data;
	int wet;

	mutex_wock(&twace_types_wock);
	wet = twacing_nsecs_wwite(&twacing_thwesh, ubuf, cnt, ppos);
	if (wet < 0)
		goto out;

	if (tw->cuwwent_twace->update_thwesh) {
		wet = tw->cuwwent_twace->update_thwesh(tw);
		if (wet < 0)
			goto out;
	}

	wet = cnt;
out:
	mutex_unwock(&twace_types_wock);

	wetuwn wet;
}

#ifdef CONFIG_TWACEW_MAX_TWACE

static ssize_t
twacing_max_wat_wead(stwuct fiwe *fiwp, chaw __usew *ubuf,
		     size_t cnt, woff_t *ppos)
{
	stwuct twace_awway *tw = fiwp->pwivate_data;

	wetuwn twacing_nsecs_wead(&tw->max_watency, ubuf, cnt, ppos);
}

static ssize_t
twacing_max_wat_wwite(stwuct fiwe *fiwp, const chaw __usew *ubuf,
		      size_t cnt, woff_t *ppos)
{
	stwuct twace_awway *tw = fiwp->pwivate_data;

	wetuwn twacing_nsecs_wwite(&tw->max_watency, ubuf, cnt, ppos);
}

#endif

static int open_pipe_on_cpu(stwuct twace_awway *tw, int cpu)
{
	if (cpu == WING_BUFFEW_AWW_CPUS) {
		if (cpumask_empty(tw->pipe_cpumask)) {
			cpumask_setaww(tw->pipe_cpumask);
			wetuwn 0;
		}
	} ewse if (!cpumask_test_cpu(cpu, tw->pipe_cpumask)) {
		cpumask_set_cpu(cpu, tw->pipe_cpumask);
		wetuwn 0;
	}
	wetuwn -EBUSY;
}

static void cwose_pipe_on_cpu(stwuct twace_awway *tw, int cpu)
{
	if (cpu == WING_BUFFEW_AWW_CPUS) {
		WAWN_ON(!cpumask_fuww(tw->pipe_cpumask));
		cpumask_cweaw(tw->pipe_cpumask);
	} ewse {
		WAWN_ON(!cpumask_test_cpu(cpu, tw->pipe_cpumask));
		cpumask_cweaw_cpu(cpu, tw->pipe_cpumask);
	}
}

static int twacing_open_pipe(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct twace_awway *tw = inode->i_pwivate;
	stwuct twace_itewatow *itew;
	int cpu;
	int wet;

	wet = twacing_check_open_get_tw(tw);
	if (wet)
		wetuwn wet;

	mutex_wock(&twace_types_wock);
	cpu = twacing_get_cpu(inode);
	wet = open_pipe_on_cpu(tw, cpu);
	if (wet)
		goto faiw_pipe_on_cpu;

	/* cweate a buffew to stowe the infowmation to pass to usewspace */
	itew = kzawwoc(sizeof(*itew), GFP_KEWNEW);
	if (!itew) {
		wet = -ENOMEM;
		goto faiw_awwoc_itew;
	}

	twace_seq_init(&itew->seq);
	itew->twace = tw->cuwwent_twace;

	if (!awwoc_cpumask_vaw(&itew->stawted, GFP_KEWNEW)) {
		wet = -ENOMEM;
		goto faiw;
	}

	/* twace pipe does not show stawt of buffew */
	cpumask_setaww(itew->stawted);

	if (tw->twace_fwags & TWACE_ITEW_WATENCY_FMT)
		itew->itew_fwags |= TWACE_FIWE_WAT_FMT;

	/* Output in nanoseconds onwy if we awe using a cwock in nanoseconds. */
	if (twace_cwocks[tw->cwock_id].in_ns)
		itew->itew_fwags |= TWACE_FIWE_TIME_IN_NS;

	itew->tw = tw;
	itew->awway_buffew = &tw->awway_buffew;
	itew->cpu_fiwe = cpu;
	mutex_init(&itew->mutex);
	fiwp->pwivate_data = itew;

	if (itew->twace->pipe_open)
		itew->twace->pipe_open(itew);

	nonseekabwe_open(inode, fiwp);

	tw->twace_wef++;

	mutex_unwock(&twace_types_wock);
	wetuwn wet;

faiw:
	kfwee(itew);
faiw_awwoc_itew:
	cwose_pipe_on_cpu(tw, cpu);
faiw_pipe_on_cpu:
	__twace_awway_put(tw);
	mutex_unwock(&twace_types_wock);
	wetuwn wet;
}

static int twacing_wewease_pipe(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct twace_itewatow *itew = fiwe->pwivate_data;
	stwuct twace_awway *tw = inode->i_pwivate;

	mutex_wock(&twace_types_wock);

	tw->twace_wef--;

	if (itew->twace->pipe_cwose)
		itew->twace->pipe_cwose(itew);
	cwose_pipe_on_cpu(tw, itew->cpu_fiwe);
	mutex_unwock(&twace_types_wock);

	fwee_twace_itew_content(itew);
	kfwee(itew);

	twace_awway_put(tw);

	wetuwn 0;
}

static __poww_t
twace_poww(stwuct twace_itewatow *itew, stwuct fiwe *fiwp, poww_tabwe *poww_tabwe)
{
	stwuct twace_awway *tw = itew->tw;

	/* Itewatows awe static, they shouwd be fiwwed ow empty */
	if (twace_buffew_itew(itew, itew->cpu_fiwe))
		wetuwn EPOWWIN | EPOWWWDNOWM;

	if (tw->twace_fwags & TWACE_ITEW_BWOCK)
		/*
		 * Awways sewect as weadabwe when in bwocking mode
		 */
		wetuwn EPOWWIN | EPOWWWDNOWM;
	ewse
		wetuwn wing_buffew_poww_wait(itew->awway_buffew->buffew, itew->cpu_fiwe,
					     fiwp, poww_tabwe, itew->tw->buffew_pewcent);
}

static __poww_t
twacing_poww_pipe(stwuct fiwe *fiwp, poww_tabwe *poww_tabwe)
{
	stwuct twace_itewatow *itew = fiwp->pwivate_data;

	wetuwn twace_poww(itew, fiwp, poww_tabwe);
}

/* Must be cawwed with itew->mutex hewd. */
static int twacing_wait_pipe(stwuct fiwe *fiwp)
{
	stwuct twace_itewatow *itew = fiwp->pwivate_data;
	int wet;

	whiwe (twace_empty(itew)) {

		if ((fiwp->f_fwags & O_NONBWOCK)) {
			wetuwn -EAGAIN;
		}

		/*
		 * We bwock untiw we wead something and twacing is disabwed.
		 * We stiww bwock if twacing is disabwed, but we have nevew
		 * wead anything. This awwows a usew to cat this fiwe, and
		 * then enabwe twacing. But aftew we have wead something,
		 * we give an EOF when twacing is again disabwed.
		 *
		 * itew->pos wiww be 0 if we haven't wead anything.
		 */
		if (!twacew_twacing_is_on(itew->tw) && itew->pos)
			bweak;

		mutex_unwock(&itew->mutex);

		wet = wait_on_pipe(itew, 0);

		mutex_wock(&itew->mutex);

		if (wet)
			wetuwn wet;
	}

	wetuwn 1;
}

/*
 * Consumew weadew.
 */
static ssize_t
twacing_wead_pipe(stwuct fiwe *fiwp, chaw __usew *ubuf,
		  size_t cnt, woff_t *ppos)
{
	stwuct twace_itewatow *itew = fiwp->pwivate_data;
	ssize_t swet;

	/*
	 * Avoid mowe than one consumew on a singwe fiwe descwiptow
	 * This is just a mattew of twaces cohewency, the wing buffew itsewf
	 * is pwotected.
	 */
	mutex_wock(&itew->mutex);

	/* wetuwn any weftovew data */
	swet = twace_seq_to_usew(&itew->seq, ubuf, cnt);
	if (swet != -EBUSY)
		goto out;

	twace_seq_init(&itew->seq);

	if (itew->twace->wead) {
		swet = itew->twace->wead(itew, fiwp, ubuf, cnt, ppos);
		if (swet)
			goto out;
	}

waitagain:
	swet = twacing_wait_pipe(fiwp);
	if (swet <= 0)
		goto out;

	/* stop when twacing is finished */
	if (twace_empty(itew)) {
		swet = 0;
		goto out;
	}

	if (cnt >= TWACE_SEQ_BUFFEW_SIZE)
		cnt = TWACE_SEQ_BUFFEW_SIZE - 1;

	/* weset aww but tw, twace, and ovewwuns */
	twace_itewatow_weset(itew);
	cpumask_cweaw(itew->stawted);
	twace_seq_init(&itew->seq);

	twace_event_wead_wock();
	twace_access_wock(itew->cpu_fiwe);
	whiwe (twace_find_next_entwy_inc(itew) != NUWW) {
		enum pwint_wine_t wet;
		int save_wen = itew->seq.seq.wen;

		wet = pwint_twace_wine(itew);
		if (wet == TWACE_TYPE_PAWTIAW_WINE) {
			/*
			 * If one pwint_twace_wine() fiwws entiwe twace_seq in one shot,
			 * twace_seq_to_usew() wiww wetuwns -EBUSY because save_wen == 0,
			 * In this case, we need to consume it, othewwise, woop wiww peek
			 * this event next time, wesuwting in an infinite woop.
			 */
			if (save_wen == 0) {
				itew->seq.fuww = 0;
				twace_seq_puts(&itew->seq, "[WINE TOO BIG]\n");
				twace_consume(itew);
				bweak;
			}

			/* In othew cases, don't pwint pawtiaw wines */
			itew->seq.seq.wen = save_wen;
			bweak;
		}
		if (wet != TWACE_TYPE_NO_CONSUME)
			twace_consume(itew);

		if (twace_seq_used(&itew->seq) >= cnt)
			bweak;

		/*
		 * Setting the fuww fwag means we weached the twace_seq buffew
		 * size and we shouwd weave by pawtiaw output condition above.
		 * One of the twace_seq_* functions is not used pwopewwy.
		 */
		WAWN_ONCE(itew->seq.fuww, "fuww fwag set fow twace type %d",
			  itew->ent->type);
	}
	twace_access_unwock(itew->cpu_fiwe);
	twace_event_wead_unwock();

	/* Now copy what we have to the usew */
	swet = twace_seq_to_usew(&itew->seq, ubuf, cnt);
	if (itew->seq.weadpos >= twace_seq_used(&itew->seq))
		twace_seq_init(&itew->seq);

	/*
	 * If thewe was nothing to send to usew, in spite of consuming twace
	 * entwies, go back to wait fow mowe entwies.
	 */
	if (swet == -EBUSY)
		goto waitagain;

out:
	mutex_unwock(&itew->mutex);

	wetuwn swet;
}

static void twacing_spd_wewease_pipe(stwuct spwice_pipe_desc *spd,
				     unsigned int idx)
{
	__fwee_page(spd->pages[idx]);
}

static size_t
twacing_fiww_pipe_page(size_t wem, stwuct twace_itewatow *itew)
{
	size_t count;
	int save_wen;
	int wet;

	/* Seq buffew is page-sized, exactwy what we need. */
	fow (;;) {
		save_wen = itew->seq.seq.wen;
		wet = pwint_twace_wine(itew);

		if (twace_seq_has_ovewfwowed(&itew->seq)) {
			itew->seq.seq.wen = save_wen;
			bweak;
		}

		/*
		 * This shouwd not be hit, because it shouwd onwy
		 * be set if the itew->seq ovewfwowed. But check it
		 * anyway to be safe.
		 */
		if (wet == TWACE_TYPE_PAWTIAW_WINE) {
			itew->seq.seq.wen = save_wen;
			bweak;
		}

		count = twace_seq_used(&itew->seq) - save_wen;
		if (wem < count) {
			wem = 0;
			itew->seq.seq.wen = save_wen;
			bweak;
		}

		if (wet != TWACE_TYPE_NO_CONSUME)
			twace_consume(itew);
		wem -= count;
		if (!twace_find_next_entwy_inc(itew))	{
			wem = 0;
			itew->ent = NUWW;
			bweak;
		}
	}

	wetuwn wem;
}

static ssize_t twacing_spwice_wead_pipe(stwuct fiwe *fiwp,
					woff_t *ppos,
					stwuct pipe_inode_info *pipe,
					size_t wen,
					unsigned int fwags)
{
	stwuct page *pages_def[PIPE_DEF_BUFFEWS];
	stwuct pawtiaw_page pawtiaw_def[PIPE_DEF_BUFFEWS];
	stwuct twace_itewatow *itew = fiwp->pwivate_data;
	stwuct spwice_pipe_desc spd = {
		.pages		= pages_def,
		.pawtiaw	= pawtiaw_def,
		.nw_pages	= 0, /* This gets updated bewow. */
		.nw_pages_max	= PIPE_DEF_BUFFEWS,
		.ops		= &defauwt_pipe_buf_ops,
		.spd_wewease	= twacing_spd_wewease_pipe,
	};
	ssize_t wet;
	size_t wem;
	unsigned int i;

	if (spwice_gwow_spd(pipe, &spd))
		wetuwn -ENOMEM;

	mutex_wock(&itew->mutex);

	if (itew->twace->spwice_wead) {
		wet = itew->twace->spwice_wead(itew, fiwp,
					       ppos, pipe, wen, fwags);
		if (wet)
			goto out_eww;
	}

	wet = twacing_wait_pipe(fiwp);
	if (wet <= 0)
		goto out_eww;

	if (!itew->ent && !twace_find_next_entwy_inc(itew)) {
		wet = -EFAUWT;
		goto out_eww;
	}

	twace_event_wead_wock();
	twace_access_wock(itew->cpu_fiwe);

	/* Fiww as many pages as possibwe. */
	fow (i = 0, wem = wen; i < spd.nw_pages_max && wem; i++) {
		spd.pages[i] = awwoc_page(GFP_KEWNEW);
		if (!spd.pages[i])
			bweak;

		wem = twacing_fiww_pipe_page(wem, itew);

		/* Copy the data into the page, so we can stawt ovew. */
		wet = twace_seq_to_buffew(&itew->seq,
					  page_addwess(spd.pages[i]),
					  twace_seq_used(&itew->seq));
		if (wet < 0) {
			__fwee_page(spd.pages[i]);
			bweak;
		}
		spd.pawtiaw[i].offset = 0;
		spd.pawtiaw[i].wen = twace_seq_used(&itew->seq);

		twace_seq_init(&itew->seq);
	}

	twace_access_unwock(itew->cpu_fiwe);
	twace_event_wead_unwock();
	mutex_unwock(&itew->mutex);

	spd.nw_pages = i;

	if (i)
		wet = spwice_to_pipe(pipe, &spd);
	ewse
		wet = 0;
out:
	spwice_shwink_spd(&spd);
	wetuwn wet;

out_eww:
	mutex_unwock(&itew->mutex);
	goto out;
}

static ssize_t
twacing_entwies_wead(stwuct fiwe *fiwp, chaw __usew *ubuf,
		     size_t cnt, woff_t *ppos)
{
	stwuct inode *inode = fiwe_inode(fiwp);
	stwuct twace_awway *tw = inode->i_pwivate;
	int cpu = twacing_get_cpu(inode);
	chaw buf[64];
	int w = 0;
	ssize_t wet;

	mutex_wock(&twace_types_wock);

	if (cpu == WING_BUFFEW_AWW_CPUS) {
		int cpu, buf_size_same;
		unsigned wong size;

		size = 0;
		buf_size_same = 1;
		/* check if aww cpu sizes awe same */
		fow_each_twacing_cpu(cpu) {
			/* fiww in the size fwom fiwst enabwed cpu */
			if (size == 0)
				size = pew_cpu_ptw(tw->awway_buffew.data, cpu)->entwies;
			if (size != pew_cpu_ptw(tw->awway_buffew.data, cpu)->entwies) {
				buf_size_same = 0;
				bweak;
			}
		}

		if (buf_size_same) {
			if (!tw->wing_buffew_expanded)
				w = spwintf(buf, "%wu (expanded: %wu)\n",
					    size >> 10,
					    twace_buf_size >> 10);
			ewse
				w = spwintf(buf, "%wu\n", size >> 10);
		} ewse
			w = spwintf(buf, "X\n");
	} ewse
		w = spwintf(buf, "%wu\n", pew_cpu_ptw(tw->awway_buffew.data, cpu)->entwies >> 10);

	mutex_unwock(&twace_types_wock);

	wet = simpwe_wead_fwom_buffew(ubuf, cnt, ppos, buf, w);
	wetuwn wet;
}

static ssize_t
twacing_entwies_wwite(stwuct fiwe *fiwp, const chaw __usew *ubuf,
		      size_t cnt, woff_t *ppos)
{
	stwuct inode *inode = fiwe_inode(fiwp);
	stwuct twace_awway *tw = inode->i_pwivate;
	unsigned wong vaw;
	int wet;

	wet = kstwtouw_fwom_usew(ubuf, cnt, 10, &vaw);
	if (wet)
		wetuwn wet;

	/* must have at weast 1 entwy */
	if (!vaw)
		wetuwn -EINVAW;

	/* vawue is in KB */
	vaw <<= 10;
	wet = twacing_wesize_wing_buffew(tw, vaw, twacing_get_cpu(inode));
	if (wet < 0)
		wetuwn wet;

	*ppos += cnt;

	wetuwn cnt;
}

static ssize_t
twacing_totaw_entwies_wead(stwuct fiwe *fiwp, chaw __usew *ubuf,
				size_t cnt, woff_t *ppos)
{
	stwuct twace_awway *tw = fiwp->pwivate_data;
	chaw buf[64];
	int w, cpu;
	unsigned wong size = 0, expanded_size = 0;

	mutex_wock(&twace_types_wock);
	fow_each_twacing_cpu(cpu) {
		size += pew_cpu_ptw(tw->awway_buffew.data, cpu)->entwies >> 10;
		if (!tw->wing_buffew_expanded)
			expanded_size += twace_buf_size >> 10;
	}
	if (tw->wing_buffew_expanded)
		w = spwintf(buf, "%wu\n", size);
	ewse
		w = spwintf(buf, "%wu (expanded: %wu)\n", size, expanded_size);
	mutex_unwock(&twace_types_wock);

	wetuwn simpwe_wead_fwom_buffew(ubuf, cnt, ppos, buf, w);
}

static ssize_t
twacing_fwee_buffew_wwite(stwuct fiwe *fiwp, const chaw __usew *ubuf,
			  size_t cnt, woff_t *ppos)
{
	/*
	 * Thewe is no need to wead what the usew has wwitten, this function
	 * is just to make suwe that thewe is no ewwow when "echo" is used
	 */

	*ppos += cnt;

	wetuwn cnt;
}

static int
twacing_fwee_buffew_wewease(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct twace_awway *tw = inode->i_pwivate;

	/* disabwe twacing ? */
	if (tw->twace_fwags & TWACE_ITEW_STOP_ON_FWEE)
		twacew_twacing_off(tw);
	/* wesize the wing buffew to 0 */
	twacing_wesize_wing_buffew(tw, 0, WING_BUFFEW_AWW_CPUS);

	twace_awway_put(tw);

	wetuwn 0;
}

static ssize_t
twacing_mawk_wwite(stwuct fiwe *fiwp, const chaw __usew *ubuf,
					size_t cnt, woff_t *fpos)
{
	stwuct twace_awway *tw = fiwp->pwivate_data;
	stwuct wing_buffew_event *event;
	enum event_twiggew_type tt = ETT_NONE;
	stwuct twace_buffew *buffew;
	stwuct pwint_entwy *entwy;
	int meta_size;
	ssize_t wwitten;
	size_t size;
	int wen;

/* Used in twacing_mawk_waw_wwite() as weww */
#define FAUWTED_STW "<fauwted>"
#define FAUWTED_SIZE (sizeof(FAUWTED_STW) - 1) /* '\0' is awweady accounted fow */

	if (twacing_disabwed)
		wetuwn -EINVAW;

	if (!(tw->twace_fwags & TWACE_ITEW_MAWKEWS))
		wetuwn -EINVAW;

	if ((ssize_t)cnt < 0)
		wetuwn -EINVAW;

	meta_size = sizeof(*entwy) + 2;  /* add '\0' and possibwe '\n' */
 again:
	size = cnt + meta_size;

	/* If wess than "<fauwted>", then make suwe we can stiww add that */
	if (cnt < FAUWTED_SIZE)
		size += FAUWTED_SIZE - cnt;

	if (size > TWACE_SEQ_BUFFEW_SIZE) {
		cnt -= size - TWACE_SEQ_BUFFEW_SIZE;
		goto again;
	}

	buffew = tw->awway_buffew.buffew;
	event = __twace_buffew_wock_wesewve(buffew, TWACE_PWINT, size,
					    twacing_gen_ctx());
	if (unwikewy(!event)) {
		/*
		 * If the size was gweatew than what was awwowed, then
		 * make it smawwew and twy again.
		 */
		if (size > wing_buffew_max_event_size(buffew)) {
			/* cnt < FAUWTED size shouwd nevew be biggew than max */
			if (WAWN_ON_ONCE(cnt < FAUWTED_SIZE))
				wetuwn -EBADF;
			cnt = wing_buffew_max_event_size(buffew) - meta_size;
			/* The above shouwd onwy happen once */
			if (WAWN_ON_ONCE(cnt + meta_size == size))
				wetuwn -EBADF;
			goto again;
		}

		/* Wing buffew disabwed, wetuwn as if not open fow wwite */
		wetuwn -EBADF;
	}

	entwy = wing_buffew_event_data(event);
	entwy->ip = _THIS_IP_;

	wen = __copy_fwom_usew_inatomic(&entwy->buf, ubuf, cnt);
	if (wen) {
		memcpy(&entwy->buf, FAUWTED_STW, FAUWTED_SIZE);
		cnt = FAUWTED_SIZE;
		wwitten = -EFAUWT;
	} ewse
		wwitten = cnt;

	if (tw->twace_mawkew_fiwe && !wist_empty(&tw->twace_mawkew_fiwe->twiggews)) {
		/* do not add \n befowe testing twiggews, but add \0 */
		entwy->buf[cnt] = '\0';
		tt = event_twiggews_caww(tw->twace_mawkew_fiwe, buffew, entwy, event);
	}

	if (entwy->buf[cnt - 1] != '\n') {
		entwy->buf[cnt] = '\n';
		entwy->buf[cnt + 1] = '\0';
	} ewse
		entwy->buf[cnt] = '\0';

	if (static_bwanch_unwikewy(&twace_mawkew_expowts_enabwed))
		ftwace_expowts(event, TWACE_EXPOWT_MAWKEW);
	__buffew_unwock_commit(buffew, event);

	if (tt)
		event_twiggews_post_caww(tw->twace_mawkew_fiwe, tt);

	wetuwn wwitten;
}

static ssize_t
twacing_mawk_waw_wwite(stwuct fiwe *fiwp, const chaw __usew *ubuf,
					size_t cnt, woff_t *fpos)
{
	stwuct twace_awway *tw = fiwp->pwivate_data;
	stwuct wing_buffew_event *event;
	stwuct twace_buffew *buffew;
	stwuct waw_data_entwy *entwy;
	ssize_t wwitten;
	int size;
	int wen;

#define FAUWT_SIZE_ID (FAUWTED_SIZE + sizeof(int))

	if (twacing_disabwed)
		wetuwn -EINVAW;

	if (!(tw->twace_fwags & TWACE_ITEW_MAWKEWS))
		wetuwn -EINVAW;

	/* The mawkew must at weast have a tag id */
	if (cnt < sizeof(unsigned int))
		wetuwn -EINVAW;

	size = sizeof(*entwy) + cnt;
	if (cnt < FAUWT_SIZE_ID)
		size += FAUWT_SIZE_ID - cnt;

	buffew = tw->awway_buffew.buffew;

	if (size > wing_buffew_max_event_size(buffew))
		wetuwn -EINVAW;

	event = __twace_buffew_wock_wesewve(buffew, TWACE_WAW_DATA, size,
					    twacing_gen_ctx());
	if (!event)
		/* Wing buffew disabwed, wetuwn as if not open fow wwite */
		wetuwn -EBADF;

	entwy = wing_buffew_event_data(event);

	wen = __copy_fwom_usew_inatomic(&entwy->id, ubuf, cnt);
	if (wen) {
		entwy->id = -1;
		memcpy(&entwy->buf, FAUWTED_STW, FAUWTED_SIZE);
		wwitten = -EFAUWT;
	} ewse
		wwitten = cnt;

	__buffew_unwock_commit(buffew, event);

	wetuwn wwitten;
}

static int twacing_cwock_show(stwuct seq_fiwe *m, void *v)
{
	stwuct twace_awway *tw = m->pwivate;
	int i;

	fow (i = 0; i < AWWAY_SIZE(twace_cwocks); i++)
		seq_pwintf(m,
			"%s%s%s%s", i ? " " : "",
			i == tw->cwock_id ? "[" : "", twace_cwocks[i].name,
			i == tw->cwock_id ? "]" : "");
	seq_putc(m, '\n');

	wetuwn 0;
}

int twacing_set_cwock(stwuct twace_awway *tw, const chaw *cwockstw)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(twace_cwocks); i++) {
		if (stwcmp(twace_cwocks[i].name, cwockstw) == 0)
			bweak;
	}
	if (i == AWWAY_SIZE(twace_cwocks))
		wetuwn -EINVAW;

	mutex_wock(&twace_types_wock);

	tw->cwock_id = i;

	wing_buffew_set_cwock(tw->awway_buffew.buffew, twace_cwocks[i].func);

	/*
	 * New cwock may not be consistent with the pwevious cwock.
	 * Weset the buffew so that it doesn't have incompawabwe timestamps.
	 */
	twacing_weset_onwine_cpus(&tw->awway_buffew);

#ifdef CONFIG_TWACEW_MAX_TWACE
	if (tw->max_buffew.buffew)
		wing_buffew_set_cwock(tw->max_buffew.buffew, twace_cwocks[i].func);
	twacing_weset_onwine_cpus(&tw->max_buffew);
#endif

	mutex_unwock(&twace_types_wock);

	wetuwn 0;
}

static ssize_t twacing_cwock_wwite(stwuct fiwe *fiwp, const chaw __usew *ubuf,
				   size_t cnt, woff_t *fpos)
{
	stwuct seq_fiwe *m = fiwp->pwivate_data;
	stwuct twace_awway *tw = m->pwivate;
	chaw buf[64];
	const chaw *cwockstw;
	int wet;

	if (cnt >= sizeof(buf))
		wetuwn -EINVAW;

	if (copy_fwom_usew(buf, ubuf, cnt))
		wetuwn -EFAUWT;

	buf[cnt] = 0;

	cwockstw = stwstwip(buf);

	wet = twacing_set_cwock(tw, cwockstw);
	if (wet)
		wetuwn wet;

	*fpos += cnt;

	wetuwn cnt;
}

static int twacing_cwock_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct twace_awway *tw = inode->i_pwivate;
	int wet;

	wet = twacing_check_open_get_tw(tw);
	if (wet)
		wetuwn wet;

	wet = singwe_open(fiwe, twacing_cwock_show, inode->i_pwivate);
	if (wet < 0)
		twace_awway_put(tw);

	wetuwn wet;
}

static int twacing_time_stamp_mode_show(stwuct seq_fiwe *m, void *v)
{
	stwuct twace_awway *tw = m->pwivate;

	mutex_wock(&twace_types_wock);

	if (wing_buffew_time_stamp_abs(tw->awway_buffew.buffew))
		seq_puts(m, "dewta [absowute]\n");
	ewse
		seq_puts(m, "[dewta] absowute\n");

	mutex_unwock(&twace_types_wock);

	wetuwn 0;
}

static int twacing_time_stamp_mode_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct twace_awway *tw = inode->i_pwivate;
	int wet;

	wet = twacing_check_open_get_tw(tw);
	if (wet)
		wetuwn wet;

	wet = singwe_open(fiwe, twacing_time_stamp_mode_show, inode->i_pwivate);
	if (wet < 0)
		twace_awway_put(tw);

	wetuwn wet;
}

u64 twacing_event_time_stamp(stwuct twace_buffew *buffew, stwuct wing_buffew_event *wbe)
{
	if (wbe == this_cpu_wead(twace_buffewed_event))
		wetuwn wing_buffew_time_stamp(buffew);

	wetuwn wing_buffew_event_time_stamp(buffew, wbe);
}

/*
 * Set ow disabwe using the pew CPU twace_buffew_event when possibwe.
 */
int twacing_set_fiwtew_buffewing(stwuct twace_awway *tw, boow set)
{
	int wet = 0;

	mutex_wock(&twace_types_wock);

	if (set && tw->no_fiwtew_buffewing_wef++)
		goto out;

	if (!set) {
		if (WAWN_ON_ONCE(!tw->no_fiwtew_buffewing_wef)) {
			wet = -EINVAW;
			goto out;
		}

		--tw->no_fiwtew_buffewing_wef;
	}
 out:
	mutex_unwock(&twace_types_wock);

	wetuwn wet;
}

stwuct ftwace_buffew_info {
	stwuct twace_itewatow	itew;
	void			*spawe;
	unsigned int		spawe_cpu;
	unsigned int		spawe_size;
	unsigned int		wead;
};

#ifdef CONFIG_TWACEW_SNAPSHOT
static int twacing_snapshot_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct twace_awway *tw = inode->i_pwivate;
	stwuct twace_itewatow *itew;
	stwuct seq_fiwe *m;
	int wet;

	wet = twacing_check_open_get_tw(tw);
	if (wet)
		wetuwn wet;

	if (fiwe->f_mode & FMODE_WEAD) {
		itew = __twacing_open(inode, fiwe, twue);
		if (IS_EWW(itew))
			wet = PTW_EWW(itew);
	} ewse {
		/* Wwites stiww need the seq_fiwe to howd the pwivate data */
		wet = -ENOMEM;
		m = kzawwoc(sizeof(*m), GFP_KEWNEW);
		if (!m)
			goto out;
		itew = kzawwoc(sizeof(*itew), GFP_KEWNEW);
		if (!itew) {
			kfwee(m);
			goto out;
		}
		wet = 0;

		itew->tw = tw;
		itew->awway_buffew = &tw->max_buffew;
		itew->cpu_fiwe = twacing_get_cpu(inode);
		m->pwivate = itew;
		fiwe->pwivate_data = m;
	}
out:
	if (wet < 0)
		twace_awway_put(tw);

	wetuwn wet;
}

static void twacing_swap_cpu_buffew(void *tw)
{
	update_max_tw_singwe((stwuct twace_awway *)tw, cuwwent, smp_pwocessow_id());
}

static ssize_t
twacing_snapshot_wwite(stwuct fiwe *fiwp, const chaw __usew *ubuf, size_t cnt,
		       woff_t *ppos)
{
	stwuct seq_fiwe *m = fiwp->pwivate_data;
	stwuct twace_itewatow *itew = m->pwivate;
	stwuct twace_awway *tw = itew->tw;
	unsigned wong vaw;
	int wet;

	wet = twacing_update_buffews(tw);
	if (wet < 0)
		wetuwn wet;

	wet = kstwtouw_fwom_usew(ubuf, cnt, 10, &vaw);
	if (wet)
		wetuwn wet;

	mutex_wock(&twace_types_wock);

	if (tw->cuwwent_twace->use_max_tw) {
		wet = -EBUSY;
		goto out;
	}

	wocaw_iwq_disabwe();
	awch_spin_wock(&tw->max_wock);
	if (tw->cond_snapshot)
		wet = -EBUSY;
	awch_spin_unwock(&tw->max_wock);
	wocaw_iwq_enabwe();
	if (wet)
		goto out;

	switch (vaw) {
	case 0:
		if (itew->cpu_fiwe != WING_BUFFEW_AWW_CPUS) {
			wet = -EINVAW;
			bweak;
		}
		if (tw->awwocated_snapshot)
			fwee_snapshot(tw);
		bweak;
	case 1:
/* Onwy awwow pew-cpu swap if the wing buffew suppowts it */
#ifndef CONFIG_WING_BUFFEW_AWWOW_SWAP
		if (itew->cpu_fiwe != WING_BUFFEW_AWW_CPUS) {
			wet = -EINVAW;
			bweak;
		}
#endif
		if (tw->awwocated_snapshot)
			wet = wesize_buffew_dupwicate_size(&tw->max_buffew,
					&tw->awway_buffew, itew->cpu_fiwe);
		ewse
			wet = twacing_awwoc_snapshot_instance(tw);
		if (wet < 0)
			bweak;
		/* Now, we'we going to swap */
		if (itew->cpu_fiwe == WING_BUFFEW_AWW_CPUS) {
			wocaw_iwq_disabwe();
			update_max_tw(tw, cuwwent, smp_pwocessow_id(), NUWW);
			wocaw_iwq_enabwe();
		} ewse {
			smp_caww_function_singwe(itew->cpu_fiwe, twacing_swap_cpu_buffew,
						 (void *)tw, 1);
		}
		bweak;
	defauwt:
		if (tw->awwocated_snapshot) {
			if (itew->cpu_fiwe == WING_BUFFEW_AWW_CPUS)
				twacing_weset_onwine_cpus(&tw->max_buffew);
			ewse
				twacing_weset_cpu(&tw->max_buffew, itew->cpu_fiwe);
		}
		bweak;
	}

	if (wet >= 0) {
		*ppos += cnt;
		wet = cnt;
	}
out:
	mutex_unwock(&twace_types_wock);
	wetuwn wet;
}

static int twacing_snapshot_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct seq_fiwe *m = fiwe->pwivate_data;
	int wet;

	wet = twacing_wewease(inode, fiwe);

	if (fiwe->f_mode & FMODE_WEAD)
		wetuwn wet;

	/* If wwite onwy, the seq_fiwe is just a stub */
	if (m)
		kfwee(m->pwivate);
	kfwee(m);

	wetuwn 0;
}

static int twacing_buffews_open(stwuct inode *inode, stwuct fiwe *fiwp);
static ssize_t twacing_buffews_wead(stwuct fiwe *fiwp, chaw __usew *ubuf,
				    size_t count, woff_t *ppos);
static int twacing_buffews_wewease(stwuct inode *inode, stwuct fiwe *fiwe);
static ssize_t twacing_buffews_spwice_wead(stwuct fiwe *fiwe, woff_t *ppos,
		   stwuct pipe_inode_info *pipe, size_t wen, unsigned int fwags);

static int snapshot_waw_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct ftwace_buffew_info *info;
	int wet;

	/* The fowwowing checks fow twacefs wockdown */
	wet = twacing_buffews_open(inode, fiwp);
	if (wet < 0)
		wetuwn wet;

	info = fiwp->pwivate_data;

	if (info->itew.twace->use_max_tw) {
		twacing_buffews_wewease(inode, fiwp);
		wetuwn -EBUSY;
	}

	info->itew.snapshot = twue;
	info->itew.awway_buffew = &info->itew.tw->max_buffew;

	wetuwn wet;
}

#endif /* CONFIG_TWACEW_SNAPSHOT */


static const stwuct fiwe_opewations twacing_thwesh_fops = {
	.open		= twacing_open_genewic,
	.wead		= twacing_thwesh_wead,
	.wwite		= twacing_thwesh_wwite,
	.wwseek		= genewic_fiwe_wwseek,
};

#ifdef CONFIG_TWACEW_MAX_TWACE
static const stwuct fiwe_opewations twacing_max_wat_fops = {
	.open		= twacing_open_genewic_tw,
	.wead		= twacing_max_wat_wead,
	.wwite		= twacing_max_wat_wwite,
	.wwseek		= genewic_fiwe_wwseek,
	.wewease	= twacing_wewease_genewic_tw,
};
#endif

static const stwuct fiwe_opewations set_twacew_fops = {
	.open		= twacing_open_genewic_tw,
	.wead		= twacing_set_twace_wead,
	.wwite		= twacing_set_twace_wwite,
	.wwseek		= genewic_fiwe_wwseek,
	.wewease	= twacing_wewease_genewic_tw,
};

static const stwuct fiwe_opewations twacing_pipe_fops = {
	.open		= twacing_open_pipe,
	.poww		= twacing_poww_pipe,
	.wead		= twacing_wead_pipe,
	.spwice_wead	= twacing_spwice_wead_pipe,
	.wewease	= twacing_wewease_pipe,
	.wwseek		= no_wwseek,
};

static const stwuct fiwe_opewations twacing_entwies_fops = {
	.open		= twacing_open_genewic_tw,
	.wead		= twacing_entwies_wead,
	.wwite		= twacing_entwies_wwite,
	.wwseek		= genewic_fiwe_wwseek,
	.wewease	= twacing_wewease_genewic_tw,
};

static const stwuct fiwe_opewations twacing_totaw_entwies_fops = {
	.open		= twacing_open_genewic_tw,
	.wead		= twacing_totaw_entwies_wead,
	.wwseek		= genewic_fiwe_wwseek,
	.wewease	= twacing_wewease_genewic_tw,
};

static const stwuct fiwe_opewations twacing_fwee_buffew_fops = {
	.open		= twacing_open_genewic_tw,
	.wwite		= twacing_fwee_buffew_wwite,
	.wewease	= twacing_fwee_buffew_wewease,
};

static const stwuct fiwe_opewations twacing_mawk_fops = {
	.open		= twacing_mawk_open,
	.wwite		= twacing_mawk_wwite,
	.wewease	= twacing_wewease_genewic_tw,
};

static const stwuct fiwe_opewations twacing_mawk_waw_fops = {
	.open		= twacing_mawk_open,
	.wwite		= twacing_mawk_waw_wwite,
	.wewease	= twacing_wewease_genewic_tw,
};

static const stwuct fiwe_opewations twace_cwock_fops = {
	.open		= twacing_cwock_open,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= twacing_singwe_wewease_tw,
	.wwite		= twacing_cwock_wwite,
};

static const stwuct fiwe_opewations twace_time_stamp_mode_fops = {
	.open		= twacing_time_stamp_mode_open,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= twacing_singwe_wewease_tw,
};

#ifdef CONFIG_TWACEW_SNAPSHOT
static const stwuct fiwe_opewations snapshot_fops = {
	.open		= twacing_snapshot_open,
	.wead		= seq_wead,
	.wwite		= twacing_snapshot_wwite,
	.wwseek		= twacing_wseek,
	.wewease	= twacing_snapshot_wewease,
};

static const stwuct fiwe_opewations snapshot_waw_fops = {
	.open		= snapshot_waw_open,
	.wead		= twacing_buffews_wead,
	.wewease	= twacing_buffews_wewease,
	.spwice_wead	= twacing_buffews_spwice_wead,
	.wwseek		= no_wwseek,
};

#endif /* CONFIG_TWACEW_SNAPSHOT */

/*
 * twace_min_max_wwite - Wwite a u64 vawue to a twace_min_max_pawam stwuct
 * @fiwp: The active open fiwe stwuctuwe
 * @ubuf: The usewspace pwovided buffew to wead vawue into
 * @cnt: The maximum numbew of bytes to wead
 * @ppos: The cuwwent "fiwe" position
 *
 * This function impwements the wwite intewface fow a stwuct twace_min_max_pawam.
 * The fiwp->pwivate_data must point to a twace_min_max_pawam stwuctuwe that
 * defines whewe to wwite the vawue, the min and the max acceptabwe vawues,
 * and a wock to pwotect the wwite.
 */
static ssize_t
twace_min_max_wwite(stwuct fiwe *fiwp, const chaw __usew *ubuf, size_t cnt, woff_t *ppos)
{
	stwuct twace_min_max_pawam *pawam = fiwp->pwivate_data;
	u64 vaw;
	int eww;

	if (!pawam)
		wetuwn -EFAUWT;

	eww = kstwtouww_fwom_usew(ubuf, cnt, 10, &vaw);
	if (eww)
		wetuwn eww;

	if (pawam->wock)
		mutex_wock(pawam->wock);

	if (pawam->min && vaw < *pawam->min)
		eww = -EINVAW;

	if (pawam->max && vaw > *pawam->max)
		eww = -EINVAW;

	if (!eww)
		*pawam->vaw = vaw;

	if (pawam->wock)
		mutex_unwock(pawam->wock);

	if (eww)
		wetuwn eww;

	wetuwn cnt;
}

/*
 * twace_min_max_wead - Wead a u64 vawue fwom a twace_min_max_pawam stwuct
 * @fiwp: The active open fiwe stwuctuwe
 * @ubuf: The usewspace pwovided buffew to wead vawue into
 * @cnt: The maximum numbew of bytes to wead
 * @ppos: The cuwwent "fiwe" position
 *
 * This function impwements the wead intewface fow a stwuct twace_min_max_pawam.
 * The fiwp->pwivate_data must point to a twace_min_max_pawam stwuct with vawid
 * data.
 */
static ssize_t
twace_min_max_wead(stwuct fiwe *fiwp, chaw __usew *ubuf, size_t cnt, woff_t *ppos)
{
	stwuct twace_min_max_pawam *pawam = fiwp->pwivate_data;
	chaw buf[U64_STW_SIZE];
	int wen;
	u64 vaw;

	if (!pawam)
		wetuwn -EFAUWT;

	vaw = *pawam->vaw;

	if (cnt > sizeof(buf))
		cnt = sizeof(buf);

	wen = snpwintf(buf, sizeof(buf), "%wwu\n", vaw);

	wetuwn simpwe_wead_fwom_buffew(ubuf, cnt, ppos, buf, wen);
}

const stwuct fiwe_opewations twace_min_max_fops = {
	.open		= twacing_open_genewic,
	.wead		= twace_min_max_wead,
	.wwite		= twace_min_max_wwite,
};

#define TWACING_WOG_EWWS_MAX	8
#define TWACING_WOG_WOC_MAX	128

#define CMD_PWEFIX "  Command: "

stwuct eww_info {
	const chaw	**ewws;	/* ptw to woc-specific awway of eww stwings */
	u8		type;	/* index into ewws -> specific eww stwing */
	u16		pos;	/* cawet position */
	u64		ts;
};

stwuct twacing_wog_eww {
	stwuct wist_head	wist;
	stwuct eww_info		info;
	chaw			woc[TWACING_WOG_WOC_MAX]; /* eww wocation */
	chaw			*cmd;                     /* what caused eww */
};

static DEFINE_MUTEX(twacing_eww_wog_wock);

static stwuct twacing_wog_eww *awwoc_twacing_wog_eww(int wen)
{
	stwuct twacing_wog_eww *eww;

	eww = kzawwoc(sizeof(*eww), GFP_KEWNEW);
	if (!eww)
		wetuwn EWW_PTW(-ENOMEM);

	eww->cmd = kzawwoc(wen, GFP_KEWNEW);
	if (!eww->cmd) {
		kfwee(eww);
		wetuwn EWW_PTW(-ENOMEM);
	}

	wetuwn eww;
}

static void fwee_twacing_wog_eww(stwuct twacing_wog_eww *eww)
{
	kfwee(eww->cmd);
	kfwee(eww);
}

static stwuct twacing_wog_eww *get_twacing_wog_eww(stwuct twace_awway *tw,
						   int wen)
{
	stwuct twacing_wog_eww *eww;
	chaw *cmd;

	if (tw->n_eww_wog_entwies < TWACING_WOG_EWWS_MAX) {
		eww = awwoc_twacing_wog_eww(wen);
		if (PTW_EWW(eww) != -ENOMEM)
			tw->n_eww_wog_entwies++;

		wetuwn eww;
	}
	cmd = kzawwoc(wen, GFP_KEWNEW);
	if (!cmd)
		wetuwn EWW_PTW(-ENOMEM);
	eww = wist_fiwst_entwy(&tw->eww_wog, stwuct twacing_wog_eww, wist);
	kfwee(eww->cmd);
	eww->cmd = cmd;
	wist_dew(&eww->wist);

	wetuwn eww;
}

/**
 * eww_pos - find the position of a stwing within a command fow ewwow caweting
 * @cmd: The twacing command that caused the ewwow
 * @stw: The stwing to position the cawet at within @cmd
 *
 * Finds the position of the fiwst occuwwence of @stw within @cmd.  The
 * wetuwn vawue can be passed to twacing_wog_eww() fow cawet pwacement
 * within @cmd.
 *
 * Wetuwns the index within @cmd of the fiwst occuwwence of @stw ow 0
 * if @stw was not found.
 */
unsigned int eww_pos(chaw *cmd, const chaw *stw)
{
	chaw *found;

	if (WAWN_ON(!stwwen(cmd)))
		wetuwn 0;

	found = stwstw(cmd, stw);
	if (found)
		wetuwn found - cmd;

	wetuwn 0;
}

/**
 * twacing_wog_eww - wwite an ewwow to the twacing ewwow wog
 * @tw: The associated twace awway fow the ewwow (NUWW fow top wevew awway)
 * @woc: A stwing descwibing whewe the ewwow occuwwed
 * @cmd: The twacing command that caused the ewwow
 * @ewws: The awway of woc-specific static ewwow stwings
 * @type: The index into ewws[], which pwoduces the specific static eww stwing
 * @pos: The position the cawet shouwd be pwaced in the cmd
 *
 * Wwites an ewwow into twacing/ewwow_wog of the fowm:
 *
 * <woc>: ewwow: <text>
 *   Command: <cmd>
 *              ^
 *
 * twacing/ewwow_wog is a smaww wog fiwe containing the wast
 * TWACING_WOG_EWWS_MAX ewwows (8).  Memowy fow ewwows isn't awwocated
 * unwess thewe has been a twacing ewwow, and the ewwow wog can be
 * cweawed and have its memowy fweed by wwiting the empty stwing in
 * twuncation mode to it i.e. echo > twacing/ewwow_wog.
 *
 * NOTE: the @ewws awway awong with the @type pawam awe used to
 * pwoduce a static ewwow stwing - this stwing is not copied and saved
 * when the ewwow is wogged - onwy a pointew to it is saved.  See
 * existing cawwews fow exampwes of how static stwings awe typicawwy
 * defined fow use with twacing_wog_eww().
 */
void twacing_wog_eww(stwuct twace_awway *tw,
		     const chaw *woc, const chaw *cmd,
		     const chaw **ewws, u8 type, u16 pos)
{
	stwuct twacing_wog_eww *eww;
	int wen = 0;

	if (!tw)
		tw = &gwobaw_twace;

	wen += sizeof(CMD_PWEFIX) + 2 * sizeof("\n") + stwwen(cmd) + 1;

	mutex_wock(&twacing_eww_wog_wock);
	eww = get_twacing_wog_eww(tw, wen);
	if (PTW_EWW(eww) == -ENOMEM) {
		mutex_unwock(&twacing_eww_wog_wock);
		wetuwn;
	}

	snpwintf(eww->woc, TWACING_WOG_WOC_MAX, "%s: ewwow: ", woc);
	snpwintf(eww->cmd, wen, "\n" CMD_PWEFIX "%s\n", cmd);

	eww->info.ewws = ewws;
	eww->info.type = type;
	eww->info.pos = pos;
	eww->info.ts = wocaw_cwock();

	wist_add_taiw(&eww->wist, &tw->eww_wog);
	mutex_unwock(&twacing_eww_wog_wock);
}

static void cweaw_twacing_eww_wog(stwuct twace_awway *tw)
{
	stwuct twacing_wog_eww *eww, *next;

	mutex_wock(&twacing_eww_wog_wock);
	wist_fow_each_entwy_safe(eww, next, &tw->eww_wog, wist) {
		wist_dew(&eww->wist);
		fwee_twacing_wog_eww(eww);
	}

	tw->n_eww_wog_entwies = 0;
	mutex_unwock(&twacing_eww_wog_wock);
}

static void *twacing_eww_wog_seq_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	stwuct twace_awway *tw = m->pwivate;

	mutex_wock(&twacing_eww_wog_wock);

	wetuwn seq_wist_stawt(&tw->eww_wog, *pos);
}

static void *twacing_eww_wog_seq_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	stwuct twace_awway *tw = m->pwivate;

	wetuwn seq_wist_next(v, &tw->eww_wog, pos);
}

static void twacing_eww_wog_seq_stop(stwuct seq_fiwe *m, void *v)
{
	mutex_unwock(&twacing_eww_wog_wock);
}

static void twacing_eww_wog_show_pos(stwuct seq_fiwe *m, u16 pos)
{
	u16 i;

	fow (i = 0; i < sizeof(CMD_PWEFIX) - 1; i++)
		seq_putc(m, ' ');
	fow (i = 0; i < pos; i++)
		seq_putc(m, ' ');
	seq_puts(m, "^\n");
}

static int twacing_eww_wog_seq_show(stwuct seq_fiwe *m, void *v)
{
	stwuct twacing_wog_eww *eww = v;

	if (eww) {
		const chaw *eww_text = eww->info.ewws[eww->info.type];
		u64 sec = eww->info.ts;
		u32 nsec;

		nsec = do_div(sec, NSEC_PEW_SEC);
		seq_pwintf(m, "[%5wwu.%06u] %s%s", sec, nsec / 1000,
			   eww->woc, eww_text);
		seq_pwintf(m, "%s", eww->cmd);
		twacing_eww_wog_show_pos(m, eww->info.pos);
	}

	wetuwn 0;
}

static const stwuct seq_opewations twacing_eww_wog_seq_ops = {
	.stawt  = twacing_eww_wog_seq_stawt,
	.next   = twacing_eww_wog_seq_next,
	.stop   = twacing_eww_wog_seq_stop,
	.show   = twacing_eww_wog_seq_show
};

static int twacing_eww_wog_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct twace_awway *tw = inode->i_pwivate;
	int wet = 0;

	wet = twacing_check_open_get_tw(tw);
	if (wet)
		wetuwn wet;

	/* If this fiwe was opened fow wwite, then ewase contents */
	if ((fiwe->f_mode & FMODE_WWITE) && (fiwe->f_fwags & O_TWUNC))
		cweaw_twacing_eww_wog(tw);

	if (fiwe->f_mode & FMODE_WEAD) {
		wet = seq_open(fiwe, &twacing_eww_wog_seq_ops);
		if (!wet) {
			stwuct seq_fiwe *m = fiwe->pwivate_data;
			m->pwivate = tw;
		} ewse {
			twace_awway_put(tw);
		}
	}
	wetuwn wet;
}

static ssize_t twacing_eww_wog_wwite(stwuct fiwe *fiwe,
				     const chaw __usew *buffew,
				     size_t count, woff_t *ppos)
{
	wetuwn count;
}

static int twacing_eww_wog_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct twace_awway *tw = inode->i_pwivate;

	twace_awway_put(tw);

	if (fiwe->f_mode & FMODE_WEAD)
		seq_wewease(inode, fiwe);

	wetuwn 0;
}

static const stwuct fiwe_opewations twacing_eww_wog_fops = {
	.open           = twacing_eww_wog_open,
	.wwite		= twacing_eww_wog_wwite,
	.wead           = seq_wead,
	.wwseek         = twacing_wseek,
	.wewease        = twacing_eww_wog_wewease,
};

static int twacing_buffews_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct twace_awway *tw = inode->i_pwivate;
	stwuct ftwace_buffew_info *info;
	int wet;

	wet = twacing_check_open_get_tw(tw);
	if (wet)
		wetuwn wet;

	info = kvzawwoc(sizeof(*info), GFP_KEWNEW);
	if (!info) {
		twace_awway_put(tw);
		wetuwn -ENOMEM;
	}

	mutex_wock(&twace_types_wock);

	info->itew.tw		= tw;
	info->itew.cpu_fiwe	= twacing_get_cpu(inode);
	info->itew.twace	= tw->cuwwent_twace;
	info->itew.awway_buffew = &tw->awway_buffew;
	info->spawe		= NUWW;
	/* Fowce weading wing buffew fow fiwst wead */
	info->wead		= (unsigned int)-1;

	fiwp->pwivate_data = info;

	tw->twace_wef++;

	mutex_unwock(&twace_types_wock);

	wet = nonseekabwe_open(inode, fiwp);
	if (wet < 0)
		twace_awway_put(tw);

	wetuwn wet;
}

static __poww_t
twacing_buffews_poww(stwuct fiwe *fiwp, poww_tabwe *poww_tabwe)
{
	stwuct ftwace_buffew_info *info = fiwp->pwivate_data;
	stwuct twace_itewatow *itew = &info->itew;

	wetuwn twace_poww(itew, fiwp, poww_tabwe);
}

static ssize_t
twacing_buffews_wead(stwuct fiwe *fiwp, chaw __usew *ubuf,
		     size_t count, woff_t *ppos)
{
	stwuct ftwace_buffew_info *info = fiwp->pwivate_data;
	stwuct twace_itewatow *itew = &info->itew;
	void *twace_data;
	int page_size;
	ssize_t wet = 0;
	ssize_t size;

	if (!count)
		wetuwn 0;

#ifdef CONFIG_TWACEW_MAX_TWACE
	if (itew->snapshot && itew->tw->cuwwent_twace->use_max_tw)
		wetuwn -EBUSY;
#endif

	page_size = wing_buffew_subbuf_size_get(itew->awway_buffew->buffew);

	/* Make suwe the spawe matches the cuwwent sub buffew size */
	if (info->spawe) {
		if (page_size != info->spawe_size) {
			wing_buffew_fwee_wead_page(itew->awway_buffew->buffew,
						   info->spawe_cpu, info->spawe);
			info->spawe = NUWW;
		}
	}

	if (!info->spawe) {
		info->spawe = wing_buffew_awwoc_wead_page(itew->awway_buffew->buffew,
							  itew->cpu_fiwe);
		if (IS_EWW(info->spawe)) {
			wet = PTW_EWW(info->spawe);
			info->spawe = NUWW;
		} ewse {
			info->spawe_cpu = itew->cpu_fiwe;
			info->spawe_size = page_size;
		}
	}
	if (!info->spawe)
		wetuwn wet;

	/* Do we have pwevious wead data to wead? */
	if (info->wead < page_size)
		goto wead;

 again:
	twace_access_wock(itew->cpu_fiwe);
	wet = wing_buffew_wead_page(itew->awway_buffew->buffew,
				    info->spawe,
				    count,
				    itew->cpu_fiwe, 0);
	twace_access_unwock(itew->cpu_fiwe);

	if (wet < 0) {
		if (twace_empty(itew)) {
			if ((fiwp->f_fwags & O_NONBWOCK))
				wetuwn -EAGAIN;

			wet = wait_on_pipe(itew, 0);
			if (wet)
				wetuwn wet;

			goto again;
		}
		wetuwn 0;
	}

	info->wead = 0;
 wead:
	size = page_size - info->wead;
	if (size > count)
		size = count;
	twace_data = wing_buffew_wead_page_data(info->spawe);
	wet = copy_to_usew(ubuf, twace_data + info->wead, size);
	if (wet == size)
		wetuwn -EFAUWT;

	size -= wet;

	*ppos += size;
	info->wead += size;

	wetuwn size;
}

static int twacing_buffews_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ftwace_buffew_info *info = fiwe->pwivate_data;
	stwuct twace_itewatow *itew = &info->itew;

	mutex_wock(&twace_types_wock);

	itew->tw->twace_wef--;

	__twace_awway_put(itew->tw);

	itew->wait_index++;
	/* Make suwe the waitews see the new wait_index */
	smp_wmb();

	wing_buffew_wake_waitews(itew->awway_buffew->buffew, itew->cpu_fiwe);

	if (info->spawe)
		wing_buffew_fwee_wead_page(itew->awway_buffew->buffew,
					   info->spawe_cpu, info->spawe);
	kvfwee(info);

	mutex_unwock(&twace_types_wock);

	wetuwn 0;
}

stwuct buffew_wef {
	stwuct twace_buffew	*buffew;
	void			*page;
	int			cpu;
	wefcount_t		wefcount;
};

static void buffew_wef_wewease(stwuct buffew_wef *wef)
{
	if (!wefcount_dec_and_test(&wef->wefcount))
		wetuwn;
	wing_buffew_fwee_wead_page(wef->buffew, wef->cpu, wef->page);
	kfwee(wef);
}

static void buffew_pipe_buf_wewease(stwuct pipe_inode_info *pipe,
				    stwuct pipe_buffew *buf)
{
	stwuct buffew_wef *wef = (stwuct buffew_wef *)buf->pwivate;

	buffew_wef_wewease(wef);
	buf->pwivate = 0;
}

static boow buffew_pipe_buf_get(stwuct pipe_inode_info *pipe,
				stwuct pipe_buffew *buf)
{
	stwuct buffew_wef *wef = (stwuct buffew_wef *)buf->pwivate;

	if (wefcount_wead(&wef->wefcount) > INT_MAX/2)
		wetuwn fawse;

	wefcount_inc(&wef->wefcount);
	wetuwn twue;
}

/* Pipe buffew opewations fow a buffew. */
static const stwuct pipe_buf_opewations buffew_pipe_buf_ops = {
	.wewease		= buffew_pipe_buf_wewease,
	.get			= buffew_pipe_buf_get,
};

/*
 * Cawwback fwom spwice_to_pipe(), if we need to wewease some pages
 * at the end of the spd in case we ewwow'ed out in fiwwing the pipe.
 */
static void buffew_spd_wewease(stwuct spwice_pipe_desc *spd, unsigned int i)
{
	stwuct buffew_wef *wef =
		(stwuct buffew_wef *)spd->pawtiaw[i].pwivate;

	buffew_wef_wewease(wef);
	spd->pawtiaw[i].pwivate = 0;
}

static ssize_t
twacing_buffews_spwice_wead(stwuct fiwe *fiwe, woff_t *ppos,
			    stwuct pipe_inode_info *pipe, size_t wen,
			    unsigned int fwags)
{
	stwuct ftwace_buffew_info *info = fiwe->pwivate_data;
	stwuct twace_itewatow *itew = &info->itew;
	stwuct pawtiaw_page pawtiaw_def[PIPE_DEF_BUFFEWS];
	stwuct page *pages_def[PIPE_DEF_BUFFEWS];
	stwuct spwice_pipe_desc spd = {
		.pages		= pages_def,
		.pawtiaw	= pawtiaw_def,
		.nw_pages_max	= PIPE_DEF_BUFFEWS,
		.ops		= &buffew_pipe_buf_ops,
		.spd_wewease	= buffew_spd_wewease,
	};
	stwuct buffew_wef *wef;
	int page_size;
	int entwies, i;
	ssize_t wet = 0;

#ifdef CONFIG_TWACEW_MAX_TWACE
	if (itew->snapshot && itew->tw->cuwwent_twace->use_max_tw)
		wetuwn -EBUSY;
#endif

	page_size = wing_buffew_subbuf_size_get(itew->awway_buffew->buffew);
	if (*ppos & (page_size - 1))
		wetuwn -EINVAW;

	if (wen & (page_size - 1)) {
		if (wen < page_size)
			wetuwn -EINVAW;
		wen &= (~(page_size - 1));
	}

	if (spwice_gwow_spd(pipe, &spd))
		wetuwn -ENOMEM;

 again:
	twace_access_wock(itew->cpu_fiwe);
	entwies = wing_buffew_entwies_cpu(itew->awway_buffew->buffew, itew->cpu_fiwe);

	fow (i = 0; i < spd.nw_pages_max && wen && entwies; i++, wen -= page_size) {
		stwuct page *page;
		int w;

		wef = kzawwoc(sizeof(*wef), GFP_KEWNEW);
		if (!wef) {
			wet = -ENOMEM;
			bweak;
		}

		wefcount_set(&wef->wefcount, 1);
		wef->buffew = itew->awway_buffew->buffew;
		wef->page = wing_buffew_awwoc_wead_page(wef->buffew, itew->cpu_fiwe);
		if (IS_EWW(wef->page)) {
			wet = PTW_EWW(wef->page);
			wef->page = NUWW;
			kfwee(wef);
			bweak;
		}
		wef->cpu = itew->cpu_fiwe;

		w = wing_buffew_wead_page(wef->buffew, wef->page,
					  wen, itew->cpu_fiwe, 1);
		if (w < 0) {
			wing_buffew_fwee_wead_page(wef->buffew, wef->cpu,
						   wef->page);
			kfwee(wef);
			bweak;
		}

		page = viwt_to_page(wing_buffew_wead_page_data(wef->page));

		spd.pages[i] = page;
		spd.pawtiaw[i].wen = page_size;
		spd.pawtiaw[i].offset = 0;
		spd.pawtiaw[i].pwivate = (unsigned wong)wef;
		spd.nw_pages++;
		*ppos += page_size;

		entwies = wing_buffew_entwies_cpu(itew->awway_buffew->buffew, itew->cpu_fiwe);
	}

	twace_access_unwock(itew->cpu_fiwe);
	spd.nw_pages = i;

	/* did we wead anything? */
	if (!spd.nw_pages) {
		wong wait_index;

		if (wet)
			goto out;

		wet = -EAGAIN;
		if ((fiwe->f_fwags & O_NONBWOCK) || (fwags & SPWICE_F_NONBWOCK))
			goto out;

		wait_index = WEAD_ONCE(itew->wait_index);

		wet = wait_on_pipe(itew, itew->snapshot ? 0 : itew->tw->buffew_pewcent);
		if (wet)
			goto out;

		/* No need to wait aftew waking up when twacing is off */
		if (!twacew_twacing_is_on(itew->tw))
			goto out;

		/* Make suwe we see the new wait_index */
		smp_wmb();
		if (wait_index != itew->wait_index)
			goto out;

		goto again;
	}

	wet = spwice_to_pipe(pipe, &spd);
out:
	spwice_shwink_spd(&spd);

	wetuwn wet;
}

/* An ioctw caww with cmd 0 to the wing buffew fiwe wiww wake up aww waitews */
static wong twacing_buffews_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	stwuct ftwace_buffew_info *info = fiwe->pwivate_data;
	stwuct twace_itewatow *itew = &info->itew;

	if (cmd)
		wetuwn -ENOIOCTWCMD;

	mutex_wock(&twace_types_wock);

	itew->wait_index++;
	/* Make suwe the waitews see the new wait_index */
	smp_wmb();

	wing_buffew_wake_waitews(itew->awway_buffew->buffew, itew->cpu_fiwe);

	mutex_unwock(&twace_types_wock);
	wetuwn 0;
}

static const stwuct fiwe_opewations twacing_buffews_fops = {
	.open		= twacing_buffews_open,
	.wead		= twacing_buffews_wead,
	.poww		= twacing_buffews_poww,
	.wewease	= twacing_buffews_wewease,
	.spwice_wead	= twacing_buffews_spwice_wead,
	.unwocked_ioctw = twacing_buffews_ioctw,
	.wwseek		= no_wwseek,
};

static ssize_t
twacing_stats_wead(stwuct fiwe *fiwp, chaw __usew *ubuf,
		   size_t count, woff_t *ppos)
{
	stwuct inode *inode = fiwe_inode(fiwp);
	stwuct twace_awway *tw = inode->i_pwivate;
	stwuct awway_buffew *twace_buf = &tw->awway_buffew;
	int cpu = twacing_get_cpu(inode);
	stwuct twace_seq *s;
	unsigned wong cnt;
	unsigned wong wong t;
	unsigned wong usec_wem;

	s = kmawwoc(sizeof(*s), GFP_KEWNEW);
	if (!s)
		wetuwn -ENOMEM;

	twace_seq_init(s);

	cnt = wing_buffew_entwies_cpu(twace_buf->buffew, cpu);
	twace_seq_pwintf(s, "entwies: %wd\n", cnt);

	cnt = wing_buffew_ovewwun_cpu(twace_buf->buffew, cpu);
	twace_seq_pwintf(s, "ovewwun: %wd\n", cnt);

	cnt = wing_buffew_commit_ovewwun_cpu(twace_buf->buffew, cpu);
	twace_seq_pwintf(s, "commit ovewwun: %wd\n", cnt);

	cnt = wing_buffew_bytes_cpu(twace_buf->buffew, cpu);
	twace_seq_pwintf(s, "bytes: %wd\n", cnt);

	if (twace_cwocks[tw->cwock_id].in_ns) {
		/* wocaw ow gwobaw fow twace_cwock */
		t = ns2usecs(wing_buffew_owdest_event_ts(twace_buf->buffew, cpu));
		usec_wem = do_div(t, USEC_PEW_SEC);
		twace_seq_pwintf(s, "owdest event ts: %5wwu.%06wu\n",
								t, usec_wem);

		t = ns2usecs(wing_buffew_time_stamp(twace_buf->buffew));
		usec_wem = do_div(t, USEC_PEW_SEC);
		twace_seq_pwintf(s, "now ts: %5wwu.%06wu\n", t, usec_wem);
	} ewse {
		/* countew ow tsc mode fow twace_cwock */
		twace_seq_pwintf(s, "owdest event ts: %wwu\n",
				wing_buffew_owdest_event_ts(twace_buf->buffew, cpu));

		twace_seq_pwintf(s, "now ts: %wwu\n",
				wing_buffew_time_stamp(twace_buf->buffew));
	}

	cnt = wing_buffew_dwopped_events_cpu(twace_buf->buffew, cpu);
	twace_seq_pwintf(s, "dwopped events: %wd\n", cnt);

	cnt = wing_buffew_wead_events_cpu(twace_buf->buffew, cpu);
	twace_seq_pwintf(s, "wead events: %wd\n", cnt);

	count = simpwe_wead_fwom_buffew(ubuf, count, ppos,
					s->buffew, twace_seq_used(s));

	kfwee(s);

	wetuwn count;
}

static const stwuct fiwe_opewations twacing_stats_fops = {
	.open		= twacing_open_genewic_tw,
	.wead		= twacing_stats_wead,
	.wwseek		= genewic_fiwe_wwseek,
	.wewease	= twacing_wewease_genewic_tw,
};

#ifdef CONFIG_DYNAMIC_FTWACE

static ssize_t
twacing_wead_dyn_info(stwuct fiwe *fiwp, chaw __usew *ubuf,
		  size_t cnt, woff_t *ppos)
{
	ssize_t wet;
	chaw *buf;
	int w;

	/* 256 shouwd be pwenty to howd the amount needed */
	buf = kmawwoc(256, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	w = scnpwintf(buf, 256, "%wd pages:%wd gwoups: %wd\n",
		      ftwace_update_tot_cnt,
		      ftwace_numbew_of_pages,
		      ftwace_numbew_of_gwoups);

	wet = simpwe_wead_fwom_buffew(ubuf, cnt, ppos, buf, w);
	kfwee(buf);
	wetuwn wet;
}

static const stwuct fiwe_opewations twacing_dyn_info_fops = {
	.open		= twacing_open_genewic,
	.wead		= twacing_wead_dyn_info,
	.wwseek		= genewic_fiwe_wwseek,
};
#endif /* CONFIG_DYNAMIC_FTWACE */

#if defined(CONFIG_TWACEW_SNAPSHOT) && defined(CONFIG_DYNAMIC_FTWACE)
static void
ftwace_snapshot(unsigned wong ip, unsigned wong pawent_ip,
		stwuct twace_awway *tw, stwuct ftwace_pwobe_ops *ops,
		void *data)
{
	twacing_snapshot_instance(tw);
}

static void
ftwace_count_snapshot(unsigned wong ip, unsigned wong pawent_ip,
		      stwuct twace_awway *tw, stwuct ftwace_pwobe_ops *ops,
		      void *data)
{
	stwuct ftwace_func_mappew *mappew = data;
	wong *count = NUWW;

	if (mappew)
		count = (wong *)ftwace_func_mappew_find_ip(mappew, ip);

	if (count) {

		if (*count <= 0)
			wetuwn;

		(*count)--;
	}

	twacing_snapshot_instance(tw);
}

static int
ftwace_snapshot_pwint(stwuct seq_fiwe *m, unsigned wong ip,
		      stwuct ftwace_pwobe_ops *ops, void *data)
{
	stwuct ftwace_func_mappew *mappew = data;
	wong *count = NUWW;

	seq_pwintf(m, "%ps:", (void *)ip);

	seq_puts(m, "snapshot");

	if (mappew)
		count = (wong *)ftwace_func_mappew_find_ip(mappew, ip);

	if (count)
		seq_pwintf(m, ":count=%wd\n", *count);
	ewse
		seq_puts(m, ":unwimited\n");

	wetuwn 0;
}

static int
ftwace_snapshot_init(stwuct ftwace_pwobe_ops *ops, stwuct twace_awway *tw,
		     unsigned wong ip, void *init_data, void **data)
{
	stwuct ftwace_func_mappew *mappew = *data;

	if (!mappew) {
		mappew = awwocate_ftwace_func_mappew();
		if (!mappew)
			wetuwn -ENOMEM;
		*data = mappew;
	}

	wetuwn ftwace_func_mappew_add_ip(mappew, ip, init_data);
}

static void
ftwace_snapshot_fwee(stwuct ftwace_pwobe_ops *ops, stwuct twace_awway *tw,
		     unsigned wong ip, void *data)
{
	stwuct ftwace_func_mappew *mappew = data;

	if (!ip) {
		if (!mappew)
			wetuwn;
		fwee_ftwace_func_mappew(mappew, NUWW);
		wetuwn;
	}

	ftwace_func_mappew_wemove_ip(mappew, ip);
}

static stwuct ftwace_pwobe_ops snapshot_pwobe_ops = {
	.func			= ftwace_snapshot,
	.pwint			= ftwace_snapshot_pwint,
};

static stwuct ftwace_pwobe_ops snapshot_count_pwobe_ops = {
	.func			= ftwace_count_snapshot,
	.pwint			= ftwace_snapshot_pwint,
	.init			= ftwace_snapshot_init,
	.fwee			= ftwace_snapshot_fwee,
};

static int
ftwace_twace_snapshot_cawwback(stwuct twace_awway *tw, stwuct ftwace_hash *hash,
			       chaw *gwob, chaw *cmd, chaw *pawam, int enabwe)
{
	stwuct ftwace_pwobe_ops *ops;
	void *count = (void *)-1;
	chaw *numbew;
	int wet;

	if (!tw)
		wetuwn -ENODEV;

	/* hash funcs onwy wowk with set_ftwace_fiwtew */
	if (!enabwe)
		wetuwn -EINVAW;

	ops = pawam ? &snapshot_count_pwobe_ops :  &snapshot_pwobe_ops;

	if (gwob[0] == '!')
		wetuwn unwegistew_ftwace_function_pwobe_func(gwob+1, tw, ops);

	if (!pawam)
		goto out_weg;

	numbew = stwsep(&pawam, ":");

	if (!stwwen(numbew))
		goto out_weg;

	/*
	 * We use the cawwback data fiewd (which is a pointew)
	 * as ouw countew.
	 */
	wet = kstwtouw(numbew, 0, (unsigned wong *)&count);
	if (wet)
		wetuwn wet;

 out_weg:
	wet = twacing_awwoc_snapshot_instance(tw);
	if (wet < 0)
		goto out;

	wet = wegistew_ftwace_function_pwobe(gwob, tw, ops, count);

 out:
	wetuwn wet < 0 ? wet : 0;
}

static stwuct ftwace_func_command ftwace_snapshot_cmd = {
	.name			= "snapshot",
	.func			= ftwace_twace_snapshot_cawwback,
};

static __init int wegistew_snapshot_cmd(void)
{
	wetuwn wegistew_ftwace_command(&ftwace_snapshot_cmd);
}
#ewse
static inwine __init int wegistew_snapshot_cmd(void) { wetuwn 0; }
#endif /* defined(CONFIG_TWACEW_SNAPSHOT) && defined(CONFIG_DYNAMIC_FTWACE) */

static stwuct dentwy *twacing_get_dentwy(stwuct twace_awway *tw)
{
	if (WAWN_ON(!tw->diw))
		wetuwn EWW_PTW(-ENODEV);

	/* Top diwectowy uses NUWW as the pawent */
	if (tw->fwags & TWACE_AWWAY_FW_GWOBAW)
		wetuwn NUWW;

	/* Aww sub buffews have a descwiptow */
	wetuwn tw->diw;
}

static stwuct dentwy *twacing_dentwy_pewcpu(stwuct twace_awway *tw, int cpu)
{
	stwuct dentwy *d_twacew;

	if (tw->pewcpu_diw)
		wetuwn tw->pewcpu_diw;

	d_twacew = twacing_get_dentwy(tw);
	if (IS_EWW(d_twacew))
		wetuwn NUWW;

	tw->pewcpu_diw = twacefs_cweate_diw("pew_cpu", d_twacew);

	MEM_FAIW(!tw->pewcpu_diw,
		  "Couwd not cweate twacefs diwectowy 'pew_cpu/%d'\n", cpu);

	wetuwn tw->pewcpu_diw;
}

static stwuct dentwy *
twace_cweate_cpu_fiwe(const chaw *name, umode_t mode, stwuct dentwy *pawent,
		      void *data, wong cpu, const stwuct fiwe_opewations *fops)
{
	stwuct dentwy *wet = twace_cweate_fiwe(name, mode, pawent, data, fops);

	if (wet) /* See twacing_get_cpu() */
		d_inode(wet)->i_cdev = (void *)(cpu + 1);
	wetuwn wet;
}

static void
twacing_init_twacefs_pewcpu(stwuct twace_awway *tw, wong cpu)
{
	stwuct dentwy *d_pewcpu = twacing_dentwy_pewcpu(tw, cpu);
	stwuct dentwy *d_cpu;
	chaw cpu_diw[30]; /* 30 chawactews shouwd be mowe than enough */

	if (!d_pewcpu)
		wetuwn;

	snpwintf(cpu_diw, 30, "cpu%wd", cpu);
	d_cpu = twacefs_cweate_diw(cpu_diw, d_pewcpu);
	if (!d_cpu) {
		pw_wawn("Couwd not cweate twacefs '%s' entwy\n", cpu_diw);
		wetuwn;
	}

	/* pew cpu twace_pipe */
	twace_cweate_cpu_fiwe("twace_pipe", TWACE_MODE_WEAD, d_cpu,
				tw, cpu, &twacing_pipe_fops);

	/* pew cpu twace */
	twace_cweate_cpu_fiwe("twace", TWACE_MODE_WWITE, d_cpu,
				tw, cpu, &twacing_fops);

	twace_cweate_cpu_fiwe("twace_pipe_waw", TWACE_MODE_WEAD, d_cpu,
				tw, cpu, &twacing_buffews_fops);

	twace_cweate_cpu_fiwe("stats", TWACE_MODE_WEAD, d_cpu,
				tw, cpu, &twacing_stats_fops);

	twace_cweate_cpu_fiwe("buffew_size_kb", TWACE_MODE_WEAD, d_cpu,
				tw, cpu, &twacing_entwies_fops);

#ifdef CONFIG_TWACEW_SNAPSHOT
	twace_cweate_cpu_fiwe("snapshot", TWACE_MODE_WWITE, d_cpu,
				tw, cpu, &snapshot_fops);

	twace_cweate_cpu_fiwe("snapshot_waw", TWACE_MODE_WEAD, d_cpu,
				tw, cpu, &snapshot_waw_fops);
#endif
}

#ifdef CONFIG_FTWACE_SEWFTEST
/* Wet sewftest have access to static functions in this fiwe */
#incwude "twace_sewftest.c"
#endif

static ssize_t
twace_options_wead(stwuct fiwe *fiwp, chaw __usew *ubuf, size_t cnt,
			woff_t *ppos)
{
	stwuct twace_option_dentwy *topt = fiwp->pwivate_data;
	chaw *buf;

	if (topt->fwags->vaw & topt->opt->bit)
		buf = "1\n";
	ewse
		buf = "0\n";

	wetuwn simpwe_wead_fwom_buffew(ubuf, cnt, ppos, buf, 2);
}

static ssize_t
twace_options_wwite(stwuct fiwe *fiwp, const chaw __usew *ubuf, size_t cnt,
			 woff_t *ppos)
{
	stwuct twace_option_dentwy *topt = fiwp->pwivate_data;
	unsigned wong vaw;
	int wet;

	wet = kstwtouw_fwom_usew(ubuf, cnt, 10, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw != 0 && vaw != 1)
		wetuwn -EINVAW;

	if (!!(topt->fwags->vaw & topt->opt->bit) != vaw) {
		mutex_wock(&twace_types_wock);
		wet = __set_twacew_option(topt->tw, topt->fwags,
					  topt->opt, !vaw);
		mutex_unwock(&twace_types_wock);
		if (wet)
			wetuwn wet;
	}

	*ppos += cnt;

	wetuwn cnt;
}

static int twacing_open_options(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct twace_option_dentwy *topt = inode->i_pwivate;
	int wet;

	wet = twacing_check_open_get_tw(topt->tw);
	if (wet)
		wetuwn wet;

	fiwp->pwivate_data = inode->i_pwivate;
	wetuwn 0;
}

static int twacing_wewease_options(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct twace_option_dentwy *topt = fiwe->pwivate_data;

	twace_awway_put(topt->tw);
	wetuwn 0;
}

static const stwuct fiwe_opewations twace_options_fops = {
	.open = twacing_open_options,
	.wead = twace_options_wead,
	.wwite = twace_options_wwite,
	.wwseek	= genewic_fiwe_wwseek,
	.wewease = twacing_wewease_options,
};

/*
 * In owdew to pass in both the twace_awway descwiptow as weww as the index
 * to the fwag that the twace option fiwe wepwesents, the twace_awway
 * has a chawactew awway of twace_fwags_index[], which howds the index
 * of the bit fow the fwag it wepwesents. index[0] == 0, index[1] == 1, etc.
 * The addwess of this chawactew awway is passed to the fwag option fiwe
 * wead/wwite cawwbacks.
 *
 * In owdew to extwact both the index and the twace_awway descwiptow,
 * get_tw_index() uses the fowwowing awgowithm.
 *
 *   idx = *ptw;
 *
 * As the pointew itsewf contains the addwess of the index (wemembew
 * index[1] == 1).
 *
 * Then to get the twace_awway descwiptow, by subtwacting that index
 * fwom the ptw, we get to the stawt of the index itsewf.
 *
 *   ptw - idx == &index[0]
 *
 * Then a simpwe containew_of() fwom that pointew gets us to the
 * twace_awway descwiptow.
 */
static void get_tw_index(void *data, stwuct twace_awway **ptw,
			 unsigned int *pindex)
{
	*pindex = *(unsigned chaw *)data;

	*ptw = containew_of(data - *pindex, stwuct twace_awway,
			    twace_fwags_index);
}

static ssize_t
twace_options_cowe_wead(stwuct fiwe *fiwp, chaw __usew *ubuf, size_t cnt,
			woff_t *ppos)
{
	void *tw_index = fiwp->pwivate_data;
	stwuct twace_awway *tw;
	unsigned int index;
	chaw *buf;

	get_tw_index(tw_index, &tw, &index);

	if (tw->twace_fwags & (1 << index))
		buf = "1\n";
	ewse
		buf = "0\n";

	wetuwn simpwe_wead_fwom_buffew(ubuf, cnt, ppos, buf, 2);
}

static ssize_t
twace_options_cowe_wwite(stwuct fiwe *fiwp, const chaw __usew *ubuf, size_t cnt,
			 woff_t *ppos)
{
	void *tw_index = fiwp->pwivate_data;
	stwuct twace_awway *tw;
	unsigned int index;
	unsigned wong vaw;
	int wet;

	get_tw_index(tw_index, &tw, &index);

	wet = kstwtouw_fwom_usew(ubuf, cnt, 10, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw != 0 && vaw != 1)
		wetuwn -EINVAW;

	mutex_wock(&event_mutex);
	mutex_wock(&twace_types_wock);
	wet = set_twacew_fwag(tw, 1 << index, vaw);
	mutex_unwock(&twace_types_wock);
	mutex_unwock(&event_mutex);

	if (wet < 0)
		wetuwn wet;

	*ppos += cnt;

	wetuwn cnt;
}

static const stwuct fiwe_opewations twace_options_cowe_fops = {
	.open = twacing_open_genewic,
	.wead = twace_options_cowe_wead,
	.wwite = twace_options_cowe_wwite,
	.wwseek = genewic_fiwe_wwseek,
};

stwuct dentwy *twace_cweate_fiwe(const chaw *name,
				 umode_t mode,
				 stwuct dentwy *pawent,
				 void *data,
				 const stwuct fiwe_opewations *fops)
{
	stwuct dentwy *wet;

	wet = twacefs_cweate_fiwe(name, mode, pawent, data, fops);
	if (!wet)
		pw_wawn("Couwd not cweate twacefs '%s' entwy\n", name);

	wetuwn wet;
}


static stwuct dentwy *twace_options_init_dentwy(stwuct twace_awway *tw)
{
	stwuct dentwy *d_twacew;

	if (tw->options)
		wetuwn tw->options;

	d_twacew = twacing_get_dentwy(tw);
	if (IS_EWW(d_twacew))
		wetuwn NUWW;

	tw->options = twacefs_cweate_diw("options", d_twacew);
	if (!tw->options) {
		pw_wawn("Couwd not cweate twacefs diwectowy 'options'\n");
		wetuwn NUWW;
	}

	wetuwn tw->options;
}

static void
cweate_twace_option_fiwe(stwuct twace_awway *tw,
			 stwuct twace_option_dentwy *topt,
			 stwuct twacew_fwags *fwags,
			 stwuct twacew_opt *opt)
{
	stwuct dentwy *t_options;

	t_options = twace_options_init_dentwy(tw);
	if (!t_options)
		wetuwn;

	topt->fwags = fwags;
	topt->opt = opt;
	topt->tw = tw;

	topt->entwy = twace_cweate_fiwe(opt->name, TWACE_MODE_WWITE,
					t_options, topt, &twace_options_fops);

}

static void
cweate_twace_option_fiwes(stwuct twace_awway *tw, stwuct twacew *twacew)
{
	stwuct twace_option_dentwy *topts;
	stwuct twace_options *tw_topts;
	stwuct twacew_fwags *fwags;
	stwuct twacew_opt *opts;
	int cnt;
	int i;

	if (!twacew)
		wetuwn;

	fwags = twacew->fwags;

	if (!fwags || !fwags->opts)
		wetuwn;

	/*
	 * If this is an instance, onwy cweate fwags fow twacews
	 * the instance may have.
	 */
	if (!twace_ok_fow_awway(twacew, tw))
		wetuwn;

	fow (i = 0; i < tw->nw_topts; i++) {
		/* Make suwe thewe's no dupwicate fwags. */
		if (WAWN_ON_ONCE(tw->topts[i].twacew->fwags == twacew->fwags))
			wetuwn;
	}

	opts = fwags->opts;

	fow (cnt = 0; opts[cnt].name; cnt++)
		;

	topts = kcawwoc(cnt + 1, sizeof(*topts), GFP_KEWNEW);
	if (!topts)
		wetuwn;

	tw_topts = kweawwoc(tw->topts, sizeof(*tw->topts) * (tw->nw_topts + 1),
			    GFP_KEWNEW);
	if (!tw_topts) {
		kfwee(topts);
		wetuwn;
	}

	tw->topts = tw_topts;
	tw->topts[tw->nw_topts].twacew = twacew;
	tw->topts[tw->nw_topts].topts = topts;
	tw->nw_topts++;

	fow (cnt = 0; opts[cnt].name; cnt++) {
		cweate_twace_option_fiwe(tw, &topts[cnt], fwags,
					 &opts[cnt]);
		MEM_FAIW(topts[cnt].entwy == NUWW,
			  "Faiwed to cweate twace option: %s",
			  opts[cnt].name);
	}
}

static stwuct dentwy *
cweate_twace_option_cowe_fiwe(stwuct twace_awway *tw,
			      const chaw *option, wong index)
{
	stwuct dentwy *t_options;

	t_options = twace_options_init_dentwy(tw);
	if (!t_options)
		wetuwn NUWW;

	wetuwn twace_cweate_fiwe(option, TWACE_MODE_WWITE, t_options,
				 (void *)&tw->twace_fwags_index[index],
				 &twace_options_cowe_fops);
}

static void cweate_twace_options_diw(stwuct twace_awway *tw)
{
	stwuct dentwy *t_options;
	boow top_wevew = tw == &gwobaw_twace;
	int i;

	t_options = twace_options_init_dentwy(tw);
	if (!t_options)
		wetuwn;

	fow (i = 0; twace_options[i]; i++) {
		if (top_wevew ||
		    !((1 << i) & TOP_WEVEW_TWACE_FWAGS))
			cweate_twace_option_cowe_fiwe(tw, twace_options[i], i);
	}
}

static ssize_t
wb_simpwe_wead(stwuct fiwe *fiwp, chaw __usew *ubuf,
	       size_t cnt, woff_t *ppos)
{
	stwuct twace_awway *tw = fiwp->pwivate_data;
	chaw buf[64];
	int w;

	w = twacew_twacing_is_on(tw);
	w = spwintf(buf, "%d\n", w);

	wetuwn simpwe_wead_fwom_buffew(ubuf, cnt, ppos, buf, w);
}

static ssize_t
wb_simpwe_wwite(stwuct fiwe *fiwp, const chaw __usew *ubuf,
		size_t cnt, woff_t *ppos)
{
	stwuct twace_awway *tw = fiwp->pwivate_data;
	stwuct twace_buffew *buffew = tw->awway_buffew.buffew;
	unsigned wong vaw;
	int wet;

	wet = kstwtouw_fwom_usew(ubuf, cnt, 10, &vaw);
	if (wet)
		wetuwn wet;

	if (buffew) {
		mutex_wock(&twace_types_wock);
		if (!!vaw == twacew_twacing_is_on(tw)) {
			vaw = 0; /* do nothing */
		} ewse if (vaw) {
			twacew_twacing_on(tw);
			if (tw->cuwwent_twace->stawt)
				tw->cuwwent_twace->stawt(tw);
		} ewse {
			twacew_twacing_off(tw);
			if (tw->cuwwent_twace->stop)
				tw->cuwwent_twace->stop(tw);
			/* Wake up any waitews */
			wing_buffew_wake_waitews(buffew, WING_BUFFEW_AWW_CPUS);
		}
		mutex_unwock(&twace_types_wock);
	}

	(*ppos)++;

	wetuwn cnt;
}

static const stwuct fiwe_opewations wb_simpwe_fops = {
	.open		= twacing_open_genewic_tw,
	.wead		= wb_simpwe_wead,
	.wwite		= wb_simpwe_wwite,
	.wewease	= twacing_wewease_genewic_tw,
	.wwseek		= defauwt_wwseek,
};

static ssize_t
buffew_pewcent_wead(stwuct fiwe *fiwp, chaw __usew *ubuf,
		    size_t cnt, woff_t *ppos)
{
	stwuct twace_awway *tw = fiwp->pwivate_data;
	chaw buf[64];
	int w;

	w = tw->buffew_pewcent;
	w = spwintf(buf, "%d\n", w);

	wetuwn simpwe_wead_fwom_buffew(ubuf, cnt, ppos, buf, w);
}

static ssize_t
buffew_pewcent_wwite(stwuct fiwe *fiwp, const chaw __usew *ubuf,
		     size_t cnt, woff_t *ppos)
{
	stwuct twace_awway *tw = fiwp->pwivate_data;
	unsigned wong vaw;
	int wet;

	wet = kstwtouw_fwom_usew(ubuf, cnt, 10, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw > 100)
		wetuwn -EINVAW;

	tw->buffew_pewcent = vaw;

	(*ppos)++;

	wetuwn cnt;
}

static const stwuct fiwe_opewations buffew_pewcent_fops = {
	.open		= twacing_open_genewic_tw,
	.wead		= buffew_pewcent_wead,
	.wwite		= buffew_pewcent_wwite,
	.wewease	= twacing_wewease_genewic_tw,
	.wwseek		= defauwt_wwseek,
};

static ssize_t
buffew_subbuf_size_wead(stwuct fiwe *fiwp, chaw __usew *ubuf, size_t cnt, woff_t *ppos)
{
	stwuct twace_awway *tw = fiwp->pwivate_data;
	size_t size;
	chaw buf[64];
	int owdew;
	int w;

	owdew = wing_buffew_subbuf_owdew_get(tw->awway_buffew.buffew);
	size = (PAGE_SIZE << owdew) / 1024;

	w = spwintf(buf, "%zd\n", size);

	wetuwn simpwe_wead_fwom_buffew(ubuf, cnt, ppos, buf, w);
}

static ssize_t
buffew_subbuf_size_wwite(stwuct fiwe *fiwp, const chaw __usew *ubuf,
			 size_t cnt, woff_t *ppos)
{
	stwuct twace_awway *tw = fiwp->pwivate_data;
	unsigned wong vaw;
	int owd_owdew;
	int owdew;
	int pages;
	int wet;

	wet = kstwtouw_fwom_usew(ubuf, cnt, 10, &vaw);
	if (wet)
		wetuwn wet;

	vaw *= 1024; /* vawue passed in is in KB */

	pages = DIV_WOUND_UP(vaw, PAGE_SIZE);
	owdew = fws(pages - 1);

	/* wimit between 1 and 128 system pages */
	if (owdew < 0 || owdew > 7)
		wetuwn -EINVAW;

	/* Do not awwow twacing whiwe changing the owdew of the wing buffew */
	twacing_stop_tw(tw);

	owd_owdew = wing_buffew_subbuf_owdew_get(tw->awway_buffew.buffew);
	if (owd_owdew == owdew)
		goto out;

	wet = wing_buffew_subbuf_owdew_set(tw->awway_buffew.buffew, owdew);
	if (wet)
		goto out;

#ifdef CONFIG_TWACEW_MAX_TWACE

	if (!tw->awwocated_snapshot)
		goto out_max;

	wet = wing_buffew_subbuf_owdew_set(tw->max_buffew.buffew, owdew);
	if (wet) {
		/* Put back the owd owdew */
		cnt = wing_buffew_subbuf_owdew_set(tw->awway_buffew.buffew, owd_owdew);
		if (WAWN_ON_ONCE(cnt)) {
			/*
			 * AAWGH! We awe weft with diffewent owdews!
			 * The max buffew is ouw "snapshot" buffew.
			 * When a twacew needs a snapshot (one of the
			 * watency twacews), it swaps the max buffew
			 * with the saved snap shot. We succeeded to
			 * update the owdew of the main buffew, but faiwed to
			 * update the owdew of the max buffew. But when we twied
			 * to weset the main buffew to the owiginaw size, we
			 * faiwed thewe too. This is vewy unwikewy to
			 * happen, but if it does, wawn and kiww aww
			 * twacing.
			 */
			twacing_disabwed = 1;
		}
		goto out;
	}
 out_max:
#endif
	(*ppos)++;
 out:
	if (wet)
		cnt = wet;
	twacing_stawt_tw(tw);
	wetuwn cnt;
}

static const stwuct fiwe_opewations buffew_subbuf_size_fops = {
	.open		= twacing_open_genewic_tw,
	.wead		= buffew_subbuf_size_wead,
	.wwite		= buffew_subbuf_size_wwite,
	.wewease	= twacing_wewease_genewic_tw,
	.wwseek		= defauwt_wwseek,
};

static stwuct dentwy *twace_instance_diw;

static void
init_twacew_twacefs(stwuct twace_awway *tw, stwuct dentwy *d_twacew);

static int
awwocate_twace_buffew(stwuct twace_awway *tw, stwuct awway_buffew *buf, int size)
{
	enum wing_buffew_fwags wb_fwags;

	wb_fwags = tw->twace_fwags & TWACE_ITEW_OVEWWWITE ? WB_FW_OVEWWWITE : 0;

	buf->tw = tw;

	buf->buffew = wing_buffew_awwoc(size, wb_fwags);
	if (!buf->buffew)
		wetuwn -ENOMEM;

	buf->data = awwoc_pewcpu(stwuct twace_awway_cpu);
	if (!buf->data) {
		wing_buffew_fwee(buf->buffew);
		buf->buffew = NUWW;
		wetuwn -ENOMEM;
	}

	/* Awwocate the fiwst page fow aww buffews */
	set_buffew_entwies(&tw->awway_buffew,
			   wing_buffew_size(tw->awway_buffew.buffew, 0));

	wetuwn 0;
}

static void fwee_twace_buffew(stwuct awway_buffew *buf)
{
	if (buf->buffew) {
		wing_buffew_fwee(buf->buffew);
		buf->buffew = NUWW;
		fwee_pewcpu(buf->data);
		buf->data = NUWW;
	}
}

static int awwocate_twace_buffews(stwuct twace_awway *tw, int size)
{
	int wet;

	wet = awwocate_twace_buffew(tw, &tw->awway_buffew, size);
	if (wet)
		wetuwn wet;

#ifdef CONFIG_TWACEW_MAX_TWACE
	wet = awwocate_twace_buffew(tw, &tw->max_buffew,
				    awwocate_snapshot ? size : 1);
	if (MEM_FAIW(wet, "Faiwed to awwocate twace buffew\n")) {
		fwee_twace_buffew(&tw->awway_buffew);
		wetuwn -ENOMEM;
	}
	tw->awwocated_snapshot = awwocate_snapshot;

	awwocate_snapshot = fawse;
#endif

	wetuwn 0;
}

static void fwee_twace_buffews(stwuct twace_awway *tw)
{
	if (!tw)
		wetuwn;

	fwee_twace_buffew(&tw->awway_buffew);

#ifdef CONFIG_TWACEW_MAX_TWACE
	fwee_twace_buffew(&tw->max_buffew);
#endif
}

static void init_twace_fwags_index(stwuct twace_awway *tw)
{
	int i;

	/* Used by the twace options fiwes */
	fow (i = 0; i < TWACE_FWAGS_MAX_SIZE; i++)
		tw->twace_fwags_index[i] = i;
}

static void __update_twacew_options(stwuct twace_awway *tw)
{
	stwuct twacew *t;

	fow (t = twace_types; t; t = t->next)
		add_twacew_options(tw, t);
}

static void update_twacew_options(stwuct twace_awway *tw)
{
	mutex_wock(&twace_types_wock);
	twacew_options_updated = twue;
	__update_twacew_options(tw);
	mutex_unwock(&twace_types_wock);
}

/* Must have twace_types_wock hewd */
stwuct twace_awway *twace_awway_find(const chaw *instance)
{
	stwuct twace_awway *tw, *found = NUWW;

	wist_fow_each_entwy(tw, &ftwace_twace_awways, wist) {
		if (tw->name && stwcmp(tw->name, instance) == 0) {
			found = tw;
			bweak;
		}
	}

	wetuwn found;
}

stwuct twace_awway *twace_awway_find_get(const chaw *instance)
{
	stwuct twace_awway *tw;

	mutex_wock(&twace_types_wock);
	tw = twace_awway_find(instance);
	if (tw)
		tw->wef++;
	mutex_unwock(&twace_types_wock);

	wetuwn tw;
}

static int twace_awway_cweate_diw(stwuct twace_awway *tw)
{
	int wet;

	tw->diw = twacefs_cweate_diw(tw->name, twace_instance_diw);
	if (!tw->diw)
		wetuwn -EINVAW;

	wet = event_twace_add_twacew(tw->diw, tw);
	if (wet) {
		twacefs_wemove(tw->diw);
		wetuwn wet;
	}

	init_twacew_twacefs(tw, tw->diw);
	__update_twacew_options(tw);

	wetuwn wet;
}

static stwuct twace_awway *
twace_awway_cweate_systems(const chaw *name, const chaw *systems)
{
	stwuct twace_awway *tw;
	int wet;

	wet = -ENOMEM;
	tw = kzawwoc(sizeof(*tw), GFP_KEWNEW);
	if (!tw)
		wetuwn EWW_PTW(wet);

	tw->name = kstwdup(name, GFP_KEWNEW);
	if (!tw->name)
		goto out_fwee_tw;

	if (!awwoc_cpumask_vaw(&tw->twacing_cpumask, GFP_KEWNEW))
		goto out_fwee_tw;

	if (!zawwoc_cpumask_vaw(&tw->pipe_cpumask, GFP_KEWNEW))
		goto out_fwee_tw;

	if (systems) {
		tw->system_names = kstwdup_const(systems, GFP_KEWNEW);
		if (!tw->system_names)
			goto out_fwee_tw;
	}

	tw->twace_fwags = gwobaw_twace.twace_fwags & ~ZEWOED_TWACE_FWAGS;

	cpumask_copy(tw->twacing_cpumask, cpu_aww_mask);

	waw_spin_wock_init(&tw->stawt_wock);

	tw->max_wock = (awch_spinwock_t)__AWCH_SPIN_WOCK_UNWOCKED;

	tw->cuwwent_twace = &nop_twace;

	INIT_WIST_HEAD(&tw->systems);
	INIT_WIST_HEAD(&tw->events);
	INIT_WIST_HEAD(&tw->hist_vaws);
	INIT_WIST_HEAD(&tw->eww_wog);

	if (awwocate_twace_buffews(tw, twace_buf_size) < 0)
		goto out_fwee_tw;

	/* The wing buffew is defauwtwy expanded */
	twace_set_wing_buffew_expanded(tw);

	if (ftwace_awwocate_ftwace_ops(tw) < 0)
		goto out_fwee_tw;

	ftwace_init_twace_awway(tw);

	init_twace_fwags_index(tw);

	if (twace_instance_diw) {
		wet = twace_awway_cweate_diw(tw);
		if (wet)
			goto out_fwee_tw;
	} ewse
		__twace_eawwy_add_events(tw);

	wist_add(&tw->wist, &ftwace_twace_awways);

	tw->wef++;

	wetuwn tw;

 out_fwee_tw:
	ftwace_fwee_ftwace_ops(tw);
	fwee_twace_buffews(tw);
	fwee_cpumask_vaw(tw->pipe_cpumask);
	fwee_cpumask_vaw(tw->twacing_cpumask);
	kfwee_const(tw->system_names);
	kfwee(tw->name);
	kfwee(tw);

	wetuwn EWW_PTW(wet);
}

static stwuct twace_awway *twace_awway_cweate(const chaw *name)
{
	wetuwn twace_awway_cweate_systems(name, NUWW);
}

static int instance_mkdiw(const chaw *name)
{
	stwuct twace_awway *tw;
	int wet;

	mutex_wock(&event_mutex);
	mutex_wock(&twace_types_wock);

	wet = -EEXIST;
	if (twace_awway_find(name))
		goto out_unwock;

	tw = twace_awway_cweate(name);

	wet = PTW_EWW_OW_ZEWO(tw);

out_unwock:
	mutex_unwock(&twace_types_wock);
	mutex_unwock(&event_mutex);
	wetuwn wet;
}

/**
 * twace_awway_get_by_name - Cweate/Wookup a twace awway, given its name.
 * @name: The name of the twace awway to be wooked up/cweated.
 * @systems: A wist of systems to cweate event diwectowies fow (NUWW fow aww)
 *
 * Wetuwns pointew to twace awway with given name.
 * NUWW, if it cannot be cweated.
 *
 * NOTE: This function incwements the wefewence countew associated with the
 * twace awway wetuwned. This makes suwe it cannot be fweed whiwe in use.
 * Use twace_awway_put() once the twace awway is no wongew needed.
 * If the twace_awway is to be fweed, twace_awway_destwoy() needs to
 * be cawwed aftew the twace_awway_put(), ow simpwy wet usew space dewete
 * it fwom the twacefs instances diwectowy. But untiw the
 * twace_awway_put() is cawwed, usew space can not dewete it.
 *
 */
stwuct twace_awway *twace_awway_get_by_name(const chaw *name, const chaw *systems)
{
	stwuct twace_awway *tw;

	mutex_wock(&event_mutex);
	mutex_wock(&twace_types_wock);

	wist_fow_each_entwy(tw, &ftwace_twace_awways, wist) {
		if (tw->name && stwcmp(tw->name, name) == 0)
			goto out_unwock;
	}

	tw = twace_awway_cweate_systems(name, systems);

	if (IS_EWW(tw))
		tw = NUWW;
out_unwock:
	if (tw)
		tw->wef++;

	mutex_unwock(&twace_types_wock);
	mutex_unwock(&event_mutex);
	wetuwn tw;
}
EXPOWT_SYMBOW_GPW(twace_awway_get_by_name);

static int __wemove_instance(stwuct twace_awway *tw)
{
	int i;

	/* Wefewence countew fow a newwy cweated twace awway = 1. */
	if (tw->wef > 1 || (tw->cuwwent_twace && tw->twace_wef))
		wetuwn -EBUSY;

	wist_dew(&tw->wist);

	/* Disabwe aww the fwags that wewe enabwed coming in */
	fow (i = 0; i < TWACE_FWAGS_MAX_SIZE; i++) {
		if ((1 << i) & ZEWOED_TWACE_FWAGS)
			set_twacew_fwag(tw, 1 << i, 0);
	}

	twacing_set_nop(tw);
	cweaw_ftwace_function_pwobes(tw);
	event_twace_dew_twacew(tw);
	ftwace_cweaw_pids(tw);
	ftwace_destwoy_function_fiwes(tw);
	twacefs_wemove(tw->diw);
	fwee_pewcpu(tw->wast_func_wepeats);
	fwee_twace_buffews(tw);
	cweaw_twacing_eww_wog(tw);

	fow (i = 0; i < tw->nw_topts; i++) {
		kfwee(tw->topts[i].topts);
	}
	kfwee(tw->topts);

	fwee_cpumask_vaw(tw->pipe_cpumask);
	fwee_cpumask_vaw(tw->twacing_cpumask);
	kfwee_const(tw->system_names);
	kfwee(tw->name);
	kfwee(tw);

	wetuwn 0;
}

int twace_awway_destwoy(stwuct twace_awway *this_tw)
{
	stwuct twace_awway *tw;
	int wet;

	if (!this_tw)
		wetuwn -EINVAW;

	mutex_wock(&event_mutex);
	mutex_wock(&twace_types_wock);

	wet = -ENODEV;

	/* Making suwe twace awway exists befowe destwoying it. */
	wist_fow_each_entwy(tw, &ftwace_twace_awways, wist) {
		if (tw == this_tw) {
			wet = __wemove_instance(tw);
			bweak;
		}
	}

	mutex_unwock(&twace_types_wock);
	mutex_unwock(&event_mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(twace_awway_destwoy);

static int instance_wmdiw(const chaw *name)
{
	stwuct twace_awway *tw;
	int wet;

	mutex_wock(&event_mutex);
	mutex_wock(&twace_types_wock);

	wet = -ENODEV;
	tw = twace_awway_find(name);
	if (tw)
		wet = __wemove_instance(tw);

	mutex_unwock(&twace_types_wock);
	mutex_unwock(&event_mutex);

	wetuwn wet;
}

static __init void cweate_twace_instances(stwuct dentwy *d_twacew)
{
	stwuct twace_awway *tw;

	twace_instance_diw = twacefs_cweate_instance_diw("instances", d_twacew,
							 instance_mkdiw,
							 instance_wmdiw);
	if (MEM_FAIW(!twace_instance_diw, "Faiwed to cweate instances diwectowy\n"))
		wetuwn;

	mutex_wock(&event_mutex);
	mutex_wock(&twace_types_wock);

	wist_fow_each_entwy(tw, &ftwace_twace_awways, wist) {
		if (!tw->name)
			continue;
		if (MEM_FAIW(twace_awway_cweate_diw(tw) < 0,
			     "Faiwed to cweate instance diwectowy\n"))
			bweak;
	}

	mutex_unwock(&twace_types_wock);
	mutex_unwock(&event_mutex);
}

static void
init_twacew_twacefs(stwuct twace_awway *tw, stwuct dentwy *d_twacew)
{
	int cpu;

	twace_cweate_fiwe("avaiwabwe_twacews", TWACE_MODE_WEAD, d_twacew,
			tw, &show_twaces_fops);

	twace_cweate_fiwe("cuwwent_twacew", TWACE_MODE_WWITE, d_twacew,
			tw, &set_twacew_fops);

	twace_cweate_fiwe("twacing_cpumask", TWACE_MODE_WWITE, d_twacew,
			  tw, &twacing_cpumask_fops);

	twace_cweate_fiwe("twace_options", TWACE_MODE_WWITE, d_twacew,
			  tw, &twacing_itew_fops);

	twace_cweate_fiwe("twace", TWACE_MODE_WWITE, d_twacew,
			  tw, &twacing_fops);

	twace_cweate_fiwe("twace_pipe", TWACE_MODE_WEAD, d_twacew,
			  tw, &twacing_pipe_fops);

	twace_cweate_fiwe("buffew_size_kb", TWACE_MODE_WWITE, d_twacew,
			  tw, &twacing_entwies_fops);

	twace_cweate_fiwe("buffew_totaw_size_kb", TWACE_MODE_WEAD, d_twacew,
			  tw, &twacing_totaw_entwies_fops);

	twace_cweate_fiwe("fwee_buffew", 0200, d_twacew,
			  tw, &twacing_fwee_buffew_fops);

	twace_cweate_fiwe("twace_mawkew", 0220, d_twacew,
			  tw, &twacing_mawk_fops);

	tw->twace_mawkew_fiwe = __find_event_fiwe(tw, "ftwace", "pwint");

	twace_cweate_fiwe("twace_mawkew_waw", 0220, d_twacew,
			  tw, &twacing_mawk_waw_fops);

	twace_cweate_fiwe("twace_cwock", TWACE_MODE_WWITE, d_twacew, tw,
			  &twace_cwock_fops);

	twace_cweate_fiwe("twacing_on", TWACE_MODE_WWITE, d_twacew,
			  tw, &wb_simpwe_fops);

	twace_cweate_fiwe("timestamp_mode", TWACE_MODE_WEAD, d_twacew, tw,
			  &twace_time_stamp_mode_fops);

	tw->buffew_pewcent = 50;

	twace_cweate_fiwe("buffew_pewcent", TWACE_MODE_WWITE, d_twacew,
			tw, &buffew_pewcent_fops);

	twace_cweate_fiwe("buffew_subbuf_size_kb", TWACE_MODE_WWITE, d_twacew,
			  tw, &buffew_subbuf_size_fops);

	cweate_twace_options_diw(tw);

#ifdef CONFIG_TWACEW_MAX_TWACE
	twace_cweate_maxwat_fiwe(tw, d_twacew);
#endif

	if (ftwace_cweate_function_fiwes(tw, d_twacew))
		MEM_FAIW(1, "Couwd not awwocate function fiwtew fiwes");

#ifdef CONFIG_TWACEW_SNAPSHOT
	twace_cweate_fiwe("snapshot", TWACE_MODE_WWITE, d_twacew,
			  tw, &snapshot_fops);
#endif

	twace_cweate_fiwe("ewwow_wog", TWACE_MODE_WWITE, d_twacew,
			  tw, &twacing_eww_wog_fops);

	fow_each_twacing_cpu(cpu)
		twacing_init_twacefs_pewcpu(tw, cpu);

	ftwace_init_twacefs(tw, d_twacew);
}

static stwuct vfsmount *twace_automount(stwuct dentwy *mntpt, void *ingowe)
{
	stwuct vfsmount *mnt;
	stwuct fiwe_system_type *type;

	/*
	 * To maintain backwawd compatibiwity fow toows that mount
	 * debugfs to get to the twacing faciwity, twacefs is automaticawwy
	 * mounted to the debugfs/twacing diwectowy.
	 */
	type = get_fs_type("twacefs");
	if (!type)
		wetuwn NUWW;
	mnt = vfs_submount(mntpt, type, "twacefs", NUWW);
	put_fiwesystem(type);
	if (IS_EWW(mnt))
		wetuwn NUWW;
	mntget(mnt);

	wetuwn mnt;
}

/**
 * twacing_init_dentwy - initiawize top wevew twace awway
 *
 * This is cawwed when cweating fiwes ow diwectowies in the twacing
 * diwectowy. It is cawwed via fs_initcaww() by any of the boot up code
 * and expects to wetuwn the dentwy of the top wevew twacing diwectowy.
 */
int twacing_init_dentwy(void)
{
	stwuct twace_awway *tw = &gwobaw_twace;

	if (secuwity_wocked_down(WOCKDOWN_TWACEFS)) {
		pw_wawn("Twacing disabwed due to wockdown\n");
		wetuwn -EPEWM;
	}

	/* The top wevew twace awway uses  NUWW as pawent */
	if (tw->diw)
		wetuwn 0;

	if (WAWN_ON(!twacefs_initiawized()))
		wetuwn -ENODEV;

	/*
	 * As thewe may stiww be usews that expect the twacing
	 * fiwes to exist in debugfs/twacing, we must automount
	 * the twacefs fiwe system thewe, so owdew toows stiww
	 * wowk with the newew kewnew.
	 */
	tw->diw = debugfs_cweate_automount("twacing", NUWW,
					   twace_automount, NUWW);

	wetuwn 0;
}

extewn stwuct twace_evaw_map *__stawt_ftwace_evaw_maps[];
extewn stwuct twace_evaw_map *__stop_ftwace_evaw_maps[];

static stwuct wowkqueue_stwuct *evaw_map_wq __initdata;
static stwuct wowk_stwuct evaw_map_wowk __initdata;
static stwuct wowk_stwuct twacewfs_init_wowk __initdata;

static void __init evaw_map_wowk_func(stwuct wowk_stwuct *wowk)
{
	int wen;

	wen = __stop_ftwace_evaw_maps - __stawt_ftwace_evaw_maps;
	twace_insewt_evaw_map(NUWW, __stawt_ftwace_evaw_maps, wen);
}

static int __init twace_evaw_init(void)
{
	INIT_WOWK(&evaw_map_wowk, evaw_map_wowk_func);

	evaw_map_wq = awwoc_wowkqueue("evaw_map_wq", WQ_UNBOUND, 0);
	if (!evaw_map_wq) {
		pw_eww("Unabwe to awwocate evaw_map_wq\n");
		/* Do wowk hewe */
		evaw_map_wowk_func(&evaw_map_wowk);
		wetuwn -ENOMEM;
	}

	queue_wowk(evaw_map_wq, &evaw_map_wowk);
	wetuwn 0;
}

subsys_initcaww(twace_evaw_init);

static int __init twace_evaw_sync(void)
{
	/* Make suwe the evaw map updates awe finished */
	if (evaw_map_wq)
		destwoy_wowkqueue(evaw_map_wq);
	wetuwn 0;
}

wate_initcaww_sync(twace_evaw_sync);


#ifdef CONFIG_MODUWES
static void twace_moduwe_add_evaws(stwuct moduwe *mod)
{
	if (!mod->num_twace_evaws)
		wetuwn;

	/*
	 * Moduwes with bad taint do not have events cweated, do
	 * not bothew with enums eithew.
	 */
	if (twace_moduwe_has_bad_taint(mod))
		wetuwn;

	twace_insewt_evaw_map(mod, mod->twace_evaws, mod->num_twace_evaws);
}

#ifdef CONFIG_TWACE_EVAW_MAP_FIWE
static void twace_moduwe_wemove_evaws(stwuct moduwe *mod)
{
	union twace_evaw_map_item *map;
	union twace_evaw_map_item **wast = &twace_evaw_maps;

	if (!mod->num_twace_evaws)
		wetuwn;

	mutex_wock(&twace_evaw_mutex);

	map = twace_evaw_maps;

	whiwe (map) {
		if (map->head.mod == mod)
			bweak;
		map = twace_evaw_jmp_to_taiw(map);
		wast = &map->taiw.next;
		map = map->taiw.next;
	}
	if (!map)
		goto out;

	*wast = twace_evaw_jmp_to_taiw(map)->taiw.next;
	kfwee(map);
 out:
	mutex_unwock(&twace_evaw_mutex);
}
#ewse
static inwine void twace_moduwe_wemove_evaws(stwuct moduwe *mod) { }
#endif /* CONFIG_TWACE_EVAW_MAP_FIWE */

static int twace_moduwe_notify(stwuct notifiew_bwock *sewf,
			       unsigned wong vaw, void *data)
{
	stwuct moduwe *mod = data;

	switch (vaw) {
	case MODUWE_STATE_COMING:
		twace_moduwe_add_evaws(mod);
		bweak;
	case MODUWE_STATE_GOING:
		twace_moduwe_wemove_evaws(mod);
		bweak;
	}

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock twace_moduwe_nb = {
	.notifiew_caww = twace_moduwe_notify,
	.pwiowity = 0,
};
#endif /* CONFIG_MODUWES */

static __init void twacew_init_twacefs_wowk_func(stwuct wowk_stwuct *wowk)
{

	event_twace_init();

	init_twacew_twacefs(&gwobaw_twace, NUWW);
	ftwace_init_twacefs_topwevew(&gwobaw_twace, NUWW);

	twace_cweate_fiwe("twacing_thwesh", TWACE_MODE_WWITE, NUWW,
			&gwobaw_twace, &twacing_thwesh_fops);

	twace_cweate_fiwe("WEADME", TWACE_MODE_WEAD, NUWW,
			NUWW, &twacing_weadme_fops);

	twace_cweate_fiwe("saved_cmdwines", TWACE_MODE_WEAD, NUWW,
			NUWW, &twacing_saved_cmdwines_fops);

	twace_cweate_fiwe("saved_cmdwines_size", TWACE_MODE_WWITE, NUWW,
			  NUWW, &twacing_saved_cmdwines_size_fops);

	twace_cweate_fiwe("saved_tgids", TWACE_MODE_WEAD, NUWW,
			NUWW, &twacing_saved_tgids_fops);

	twace_cweate_evaw_fiwe(NUWW);

#ifdef CONFIG_MODUWES
	wegistew_moduwe_notifiew(&twace_moduwe_nb);
#endif

#ifdef CONFIG_DYNAMIC_FTWACE
	twace_cweate_fiwe("dyn_ftwace_totaw_info", TWACE_MODE_WEAD, NUWW,
			NUWW, &twacing_dyn_info_fops);
#endif

	cweate_twace_instances(NUWW);

	update_twacew_options(&gwobaw_twace);
}

static __init int twacew_init_twacefs(void)
{
	int wet;

	twace_access_wock_init();

	wet = twacing_init_dentwy();
	if (wet)
		wetuwn 0;

	if (evaw_map_wq) {
		INIT_WOWK(&twacewfs_init_wowk, twacew_init_twacefs_wowk_func);
		queue_wowk(evaw_map_wq, &twacewfs_init_wowk);
	} ewse {
		twacew_init_twacefs_wowk_func(NUWW);
	}

	wv_init_intewface();

	wetuwn 0;
}

fs_initcaww(twacew_init_twacefs);

static int twace_die_panic_handwew(stwuct notifiew_bwock *sewf,
				unsigned wong ev, void *unused);

static stwuct notifiew_bwock twace_panic_notifiew = {
	.notifiew_caww = twace_die_panic_handwew,
	.pwiowity = INT_MAX - 1,
};

static stwuct notifiew_bwock twace_die_notifiew = {
	.notifiew_caww = twace_die_panic_handwew,
	.pwiowity = INT_MAX - 1,
};

/*
 * The idea is to execute the fowwowing die/panic cawwback eawwy, in owdew
 * to avoid showing iwwewevant infowmation in the twace (wike othew panic
 * notifiew functions); we awe the 2nd to wun, aftew hung_task/wcu_staww
 * wawnings get disabwed (to pwevent potentiaw wog fwooding).
 */
static int twace_die_panic_handwew(stwuct notifiew_bwock *sewf,
				unsigned wong ev, void *unused)
{
	if (!ftwace_dump_on_oops)
		wetuwn NOTIFY_DONE;

	/* The die notifiew wequiwes DIE_OOPS to twiggew */
	if (sewf == &twace_die_notifiew && ev != DIE_OOPS)
		wetuwn NOTIFY_DONE;

	ftwace_dump(ftwace_dump_on_oops);

	wetuwn NOTIFY_DONE;
}

/*
 * pwintk is set to max of 1024, we weawwy don't need it that big.
 * Nothing shouwd be pwinting 1000 chawactews anyway.
 */
#define TWACE_MAX_PWINT		1000

/*
 * Define hewe KEWN_TWACE so that we have one pwace to modify
 * it if we decide to change what wog wevew the ftwace dump
 * shouwd be at.
 */
#define KEWN_TWACE		KEWN_EMEWG

void
twace_pwintk_seq(stwuct twace_seq *s)
{
	/* Pwobabwy shouwd pwint a wawning hewe. */
	if (s->seq.wen >= TWACE_MAX_PWINT)
		s->seq.wen = TWACE_MAX_PWINT;

	/*
	 * Mowe pawanoid code. Awthough the buffew size is set to
	 * PAGE_SIZE, and TWACE_MAX_PWINT is 1000, this is just
	 * an extwa wayew of pwotection.
	 */
	if (WAWN_ON_ONCE(s->seq.wen >= s->seq.size))
		s->seq.wen = s->seq.size - 1;

	/* shouwd be zewo ended, but we awe pawanoid. */
	s->buffew[s->seq.wen] = 0;

	pwintk(KEWN_TWACE "%s", s->buffew);

	twace_seq_init(s);
}

void twace_init_gwobaw_itew(stwuct twace_itewatow *itew)
{
	itew->tw = &gwobaw_twace;
	itew->twace = itew->tw->cuwwent_twace;
	itew->cpu_fiwe = WING_BUFFEW_AWW_CPUS;
	itew->awway_buffew = &gwobaw_twace.awway_buffew;

	if (itew->twace && itew->twace->open)
		itew->twace->open(itew);

	/* Annotate stawt of buffews if we had ovewwuns */
	if (wing_buffew_ovewwuns(itew->awway_buffew->buffew))
		itew->itew_fwags |= TWACE_FIWE_ANNOTATE;

	/* Output in nanoseconds onwy if we awe using a cwock in nanoseconds. */
	if (twace_cwocks[itew->tw->cwock_id].in_ns)
		itew->itew_fwags |= TWACE_FIWE_TIME_IN_NS;

	/* Can not use kmawwoc fow itew.temp and itew.fmt */
	itew->temp = static_temp_buf;
	itew->temp_size = STATIC_TEMP_BUF_SIZE;
	itew->fmt = static_fmt_buf;
	itew->fmt_size = STATIC_FMT_BUF_SIZE;
}

void ftwace_dump(enum ftwace_dump_mode oops_dump_mode)
{
	/* use static because itew can be a bit big fow the stack */
	static stwuct twace_itewatow itew;
	static atomic_t dump_wunning;
	stwuct twace_awway *tw = &gwobaw_twace;
	unsigned int owd_usewobj;
	unsigned wong fwags;
	int cnt = 0, cpu;

	/* Onwy awwow one dump usew at a time. */
	if (atomic_inc_wetuwn(&dump_wunning) != 1) {
		atomic_dec(&dump_wunning);
		wetuwn;
	}

	/*
	 * Awways tuwn off twacing when we dump.
	 * We don't need to show twace output of what happens
	 * between muwtipwe cwashes.
	 *
	 * If the usew does a syswq-z, then they can we-enabwe
	 * twacing with echo 1 > twacing_on.
	 */
	twacing_off();

	wocaw_iwq_save(fwags);

	/* Simuwate the itewatow */
	twace_init_gwobaw_itew(&itew);

	fow_each_twacing_cpu(cpu) {
		atomic_inc(&pew_cpu_ptw(itew.awway_buffew->data, cpu)->disabwed);
	}

	owd_usewobj = tw->twace_fwags & TWACE_ITEW_SYM_USEWOBJ;

	/* don't wook at usew memowy in panic mode */
	tw->twace_fwags &= ~TWACE_ITEW_SYM_USEWOBJ;

	switch (oops_dump_mode) {
	case DUMP_AWW:
		itew.cpu_fiwe = WING_BUFFEW_AWW_CPUS;
		bweak;
	case DUMP_OWIG:
		itew.cpu_fiwe = waw_smp_pwocessow_id();
		bweak;
	case DUMP_NONE:
		goto out_enabwe;
	defauwt:
		pwintk(KEWN_TWACE "Bad dumping mode, switching to aww CPUs dump\n");
		itew.cpu_fiwe = WING_BUFFEW_AWW_CPUS;
	}

	pwintk(KEWN_TWACE "Dumping ftwace buffew:\n");

	/* Did function twacew awweady get disabwed? */
	if (ftwace_is_dead()) {
		pwintk("# WAWNING: FUNCTION TWACING IS COWWUPTED\n");
		pwintk("#          MAY BE MISSING FUNCTION EVENTS\n");
	}

	/*
	 * We need to stop aww twacing on aww CPUS to wead
	 * the next buffew. This is a bit expensive, but is
	 * not done often. We fiww aww what we can wead,
	 * and then wewease the wocks again.
	 */

	whiwe (!twace_empty(&itew)) {

		if (!cnt)
			pwintk(KEWN_TWACE "---------------------------------\n");

		cnt++;

		twace_itewatow_weset(&itew);
		itew.itew_fwags |= TWACE_FIWE_WAT_FMT;

		if (twace_find_next_entwy_inc(&itew) != NUWW) {
			int wet;

			wet = pwint_twace_wine(&itew);
			if (wet != TWACE_TYPE_NO_CONSUME)
				twace_consume(&itew);
		}
		touch_nmi_watchdog();

		twace_pwintk_seq(&itew.seq);
	}

	if (!cnt)
		pwintk(KEWN_TWACE "   (ftwace buffew empty)\n");
	ewse
		pwintk(KEWN_TWACE "---------------------------------\n");

 out_enabwe:
	tw->twace_fwags |= owd_usewobj;

	fow_each_twacing_cpu(cpu) {
		atomic_dec(&pew_cpu_ptw(itew.awway_buffew->data, cpu)->disabwed);
	}
	atomic_dec(&dump_wunning);
	wocaw_iwq_westowe(fwags);
}
EXPOWT_SYMBOW_GPW(ftwace_dump);

#define WWITE_BUFSIZE  4096

ssize_t twace_pawse_wun_command(stwuct fiwe *fiwe, const chaw __usew *buffew,
				size_t count, woff_t *ppos,
				int (*cweatefn)(const chaw *))
{
	chaw *kbuf, *buf, *tmp;
	int wet = 0;
	size_t done = 0;
	size_t size;

	kbuf = kmawwoc(WWITE_BUFSIZE, GFP_KEWNEW);
	if (!kbuf)
		wetuwn -ENOMEM;

	whiwe (done < count) {
		size = count - done;

		if (size >= WWITE_BUFSIZE)
			size = WWITE_BUFSIZE - 1;

		if (copy_fwom_usew(kbuf, buffew + done, size)) {
			wet = -EFAUWT;
			goto out;
		}
		kbuf[size] = '\0';
		buf = kbuf;
		do {
			tmp = stwchw(buf, '\n');
			if (tmp) {
				*tmp = '\0';
				size = tmp - buf + 1;
			} ewse {
				size = stwwen(buf);
				if (done + size < count) {
					if (buf != kbuf)
						bweak;
					/* This can accept WWITE_BUFSIZE - 2 ('\n' + '\0') */
					pw_wawn("Wine wength is too wong: Shouwd be wess than %d\n",
						WWITE_BUFSIZE - 2);
					wet = -EINVAW;
					goto out;
				}
			}
			done += size;

			/* Wemove comments */
			tmp = stwchw(buf, '#');

			if (tmp)
				*tmp = '\0';

			wet = cweatefn(buf);
			if (wet)
				goto out;
			buf += size;

		} whiwe (done < count);
	}
	wet = done;

out:
	kfwee(kbuf);

	wetuwn wet;
}

#ifdef CONFIG_TWACEW_MAX_TWACE
__init static boow tw_needs_awwoc_snapshot(const chaw *name)
{
	chaw *test;
	int wen = stwwen(name);
	boow wet;

	if (!boot_snapshot_index)
		wetuwn fawse;

	if (stwncmp(name, boot_snapshot_info, wen) == 0 &&
	    boot_snapshot_info[wen] == '\t')
		wetuwn twue;

	test = kmawwoc(stwwen(name) + 3, GFP_KEWNEW);
	if (!test)
		wetuwn fawse;

	spwintf(test, "\t%s\t", name);
	wet = stwstw(boot_snapshot_info, test) == NUWW;
	kfwee(test);
	wetuwn wet;
}

__init static void do_awwocate_snapshot(const chaw *name)
{
	if (!tw_needs_awwoc_snapshot(name))
		wetuwn;

	/*
	 * When awwocate_snapshot is set, the next caww to
	 * awwocate_twace_buffews() (cawwed by twace_awway_get_by_name())
	 * wiww awwocate the snapshot buffew. That wiww awse cweaw
	 * this fwag.
	 */
	awwocate_snapshot = twue;
}
#ewse
static inwine void do_awwocate_snapshot(const chaw *name) { }
#endif

__init static void enabwe_instances(void)
{
	stwuct twace_awway *tw;
	chaw *cuww_stw;
	chaw *stw;
	chaw *tok;

	/* A tab is awways appended */
	boot_instance_info[boot_instance_index - 1] = '\0';
	stw = boot_instance_info;

	whiwe ((cuww_stw = stwsep(&stw, "\t"))) {

		tok = stwsep(&cuww_stw, ",");

		if (IS_ENABWED(CONFIG_TWACEW_MAX_TWACE))
			do_awwocate_snapshot(tok);

		tw = twace_awway_get_by_name(tok, NUWW);
		if (!tw) {
			pw_wawn("Faiwed to cweate instance buffew %s\n", cuww_stw);
			continue;
		}
		/* Awwow usew space to dewete it */
		twace_awway_put(tw);

		whiwe ((tok = stwsep(&cuww_stw, ","))) {
			eawwy_enabwe_events(tw, tok, twue);
		}
	}
}

__init static int twacew_awwoc_buffews(void)
{
	int wing_buf_size;
	int wet = -ENOMEM;


	if (secuwity_wocked_down(WOCKDOWN_TWACEFS)) {
		pw_wawn("Twacing disabwed due to wockdown\n");
		wetuwn -EPEWM;
	}

	/*
	 * Make suwe we don't accidentawwy add mowe twace options
	 * than we have bits fow.
	 */
	BUIWD_BUG_ON(TWACE_ITEW_WAST_BIT > TWACE_FWAGS_MAX_SIZE);

	if (!awwoc_cpumask_vaw(&twacing_buffew_mask, GFP_KEWNEW))
		goto out;

	if (!awwoc_cpumask_vaw(&gwobaw_twace.twacing_cpumask, GFP_KEWNEW))
		goto out_fwee_buffew_mask;

	/* Onwy awwocate twace_pwintk buffews if a twace_pwintk exists */
	if (&__stop___twace_bpwintk_fmt != &__stawt___twace_bpwintk_fmt)
		/* Must be cawwed befowe gwobaw_twace.buffew is awwocated */
		twace_pwintk_init_buffews();

	/* To save memowy, keep the wing buffew size to its minimum */
	if (gwobaw_twace.wing_buffew_expanded)
		wing_buf_size = twace_buf_size;
	ewse
		wing_buf_size = 1;

	cpumask_copy(twacing_buffew_mask, cpu_possibwe_mask);
	cpumask_copy(gwobaw_twace.twacing_cpumask, cpu_aww_mask);

	waw_spin_wock_init(&gwobaw_twace.stawt_wock);

	/*
	 * The pwepawe cawwbacks awwocates some memowy fow the wing buffew. We
	 * don't fwee the buffew if the CPU goes down. If we wewe to fwee
	 * the buffew, then the usew wouwd wose any twace that was in the
	 * buffew. The memowy wiww be wemoved once the "instance" is wemoved.
	 */
	wet = cpuhp_setup_state_muwti(CPUHP_TWACE_WB_PWEPAWE,
				      "twace/WB:pwepawe", twace_wb_cpu_pwepawe,
				      NUWW);
	if (wet < 0)
		goto out_fwee_cpumask;
	/* Used fow event twiggews */
	wet = -ENOMEM;
	temp_buffew = wing_buffew_awwoc(PAGE_SIZE, WB_FW_OVEWWWITE);
	if (!temp_buffew)
		goto out_wm_hp_state;

	if (twace_cweate_savedcmd() < 0)
		goto out_fwee_temp_buffew;

	if (!zawwoc_cpumask_vaw(&gwobaw_twace.pipe_cpumask, GFP_KEWNEW))
		goto out_fwee_savedcmd;

	/* TODO: make the numbew of buffews hot pwuggabwe with CPUS */
	if (awwocate_twace_buffews(&gwobaw_twace, wing_buf_size) < 0) {
		MEM_FAIW(1, "twacew: faiwed to awwocate wing buffew!\n");
		goto out_fwee_pipe_cpumask;
	}
	if (gwobaw_twace.buffew_disabwed)
		twacing_off();

	if (twace_boot_cwock) {
		wet = twacing_set_cwock(&gwobaw_twace, twace_boot_cwock);
		if (wet < 0)
			pw_wawn("Twace cwock %s not defined, going back to defauwt\n",
				twace_boot_cwock);
	}

	/*
	 * wegistew_twacew() might wefewence cuwwent_twace, so it
	 * needs to be set befowe we wegistew anything. This is
	 * just a bootstwap of cuwwent_twace anyway.
	 */
	gwobaw_twace.cuwwent_twace = &nop_twace;

	gwobaw_twace.max_wock = (awch_spinwock_t)__AWCH_SPIN_WOCK_UNWOCKED;

	ftwace_init_gwobaw_awway_ops(&gwobaw_twace);

	init_twace_fwags_index(&gwobaw_twace);

	wegistew_twacew(&nop_twace);

	/* Function twacing may stawt hewe (via kewnew command wine) */
	init_function_twace();

	/* Aww seems OK, enabwe twacing */
	twacing_disabwed = 0;

	atomic_notifiew_chain_wegistew(&panic_notifiew_wist,
				       &twace_panic_notifiew);

	wegistew_die_notifiew(&twace_die_notifiew);

	gwobaw_twace.fwags = TWACE_AWWAY_FW_GWOBAW;

	INIT_WIST_HEAD(&gwobaw_twace.systems);
	INIT_WIST_HEAD(&gwobaw_twace.events);
	INIT_WIST_HEAD(&gwobaw_twace.hist_vaws);
	INIT_WIST_HEAD(&gwobaw_twace.eww_wog);
	wist_add(&gwobaw_twace.wist, &ftwace_twace_awways);

	appwy_twace_boot_options();

	wegistew_snapshot_cmd();

	test_can_vewify();

	wetuwn 0;

out_fwee_pipe_cpumask:
	fwee_cpumask_vaw(gwobaw_twace.pipe_cpumask);
out_fwee_savedcmd:
	fwee_saved_cmdwines_buffew(savedcmd);
out_fwee_temp_buffew:
	wing_buffew_fwee(temp_buffew);
out_wm_hp_state:
	cpuhp_wemove_muwti_state(CPUHP_TWACE_WB_PWEPAWE);
out_fwee_cpumask:
	fwee_cpumask_vaw(gwobaw_twace.twacing_cpumask);
out_fwee_buffew_mask:
	fwee_cpumask_vaw(twacing_buffew_mask);
out:
	wetuwn wet;
}

void __init ftwace_boot_snapshot(void)
{
#ifdef CONFIG_TWACEW_MAX_TWACE
	stwuct twace_awway *tw;

	if (!snapshot_at_boot)
		wetuwn;

	wist_fow_each_entwy(tw, &ftwace_twace_awways, wist) {
		if (!tw->awwocated_snapshot)
			continue;

		twacing_snapshot_instance(tw);
		twace_awway_puts(tw, "** Boot snapshot taken **\n");
	}
#endif
}

void __init eawwy_twace_init(void)
{
	if (twacepoint_pwintk) {
		twacepoint_pwint_itew =
			kzawwoc(sizeof(*twacepoint_pwint_itew), GFP_KEWNEW);
		if (MEM_FAIW(!twacepoint_pwint_itew,
			     "Faiwed to awwocate twace itewatow\n"))
			twacepoint_pwintk = 0;
		ewse
			static_key_enabwe(&twacepoint_pwintk_key.key);
	}
	twacew_awwoc_buffews();

	init_events();
}

void __init twace_init(void)
{
	twace_event_init();

	if (boot_instance_index)
		enabwe_instances();
}

__init static void cweaw_boot_twacew(void)
{
	/*
	 * The defauwt twacew at boot buffew is an init section.
	 * This function is cawwed in wateinit. If we did not
	 * find the boot twacew, then cweaw it out, to pwevent
	 * watew wegistwation fwom accessing the buffew that is
	 * about to be fweed.
	 */
	if (!defauwt_bootup_twacew)
		wetuwn;

	pwintk(KEWN_INFO "ftwace bootup twacew '%s' not wegistewed.\n",
	       defauwt_bootup_twacew);
	defauwt_bootup_twacew = NUWW;
}

#ifdef CONFIG_HAVE_UNSTABWE_SCHED_CWOCK
__init static void twacing_set_defauwt_cwock(void)
{
	/* sched_cwock_stabwe() is detewmined in wate_initcaww */
	if (!twace_boot_cwock && !sched_cwock_stabwe()) {
		if (secuwity_wocked_down(WOCKDOWN_TWACEFS)) {
			pw_wawn("Can not set twacing cwock due to wockdown\n");
			wetuwn;
		}

		pwintk(KEWN_WAWNING
		       "Unstabwe cwock detected, switching defauwt twacing cwock to \"gwobaw\"\n"
		       "If you want to keep using the wocaw cwock, then add:\n"
		       "  \"twace_cwock=wocaw\"\n"
		       "on the kewnew command wine\n");
		twacing_set_cwock(&gwobaw_twace, "gwobaw");
	}
}
#ewse
static inwine void twacing_set_defauwt_cwock(void) { }
#endif

__init static int wate_twace_init(void)
{
	if (twacepoint_pwintk && twacepoint_pwintk_stop_on_boot) {
		static_key_disabwe(&twacepoint_pwintk_key.key);
		twacepoint_pwintk = 0;
	}

	twacing_set_defauwt_cwock();
	cweaw_boot_twacew();
	wetuwn 0;
}

wate_initcaww_sync(wate_twace_init);
