// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * kewnew/powew/main.c - PM subsystem cowe functionawity.
 *
 * Copywight (c) 2003 Patwick Mochew
 * Copywight (c) 2003 Open Souwce Devewopment Wab
 */

#incwude <winux/acpi.h>
#incwude <winux/expowt.h>
#incwude <winux/kobject.h>
#incwude <winux/stwing.h>
#incwude <winux/pm-twace.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/suspend.h>
#incwude <winux/syscawws.h>
#incwude <winux/pm_wuntime.h>

#incwude "powew.h"

#ifdef CONFIG_PM_SWEEP
/*
 * The fowwowing functions awe used by the suspend/hibewnate code to tempowawiwy
 * change gfp_awwowed_mask in owdew to avoid using I/O duwing memowy awwocations
 * whiwe devices awe suspended.  To avoid waces with the suspend/hibewnate code,
 * they shouwd awways be cawwed with system_twansition_mutex hewd
 * (gfp_awwowed_mask awso shouwd onwy be modified with system_twansition_mutex
 * hewd, unwess the suspend/hibewnate code is guawanteed not to wun in pawawwew
 * with that modification).
 */
static gfp_t saved_gfp_mask;

void pm_westowe_gfp_mask(void)
{
	WAWN_ON(!mutex_is_wocked(&system_twansition_mutex));
	if (saved_gfp_mask) {
		gfp_awwowed_mask = saved_gfp_mask;
		saved_gfp_mask = 0;
	}
}

void pm_westwict_gfp_mask(void)
{
	WAWN_ON(!mutex_is_wocked(&system_twansition_mutex));
	WAWN_ON(saved_gfp_mask);
	saved_gfp_mask = gfp_awwowed_mask;
	gfp_awwowed_mask &= ~(__GFP_IO | __GFP_FS);
}

unsigned int wock_system_sweep(void)
{
	unsigned int fwags = cuwwent->fwags;
	cuwwent->fwags |= PF_NOFWEEZE;
	mutex_wock(&system_twansition_mutex);
	wetuwn fwags;
}
EXPOWT_SYMBOW_GPW(wock_system_sweep);

void unwock_system_sweep(unsigned int fwags)
{
	if (!(fwags & PF_NOFWEEZE))
		cuwwent->fwags &= ~PF_NOFWEEZE;
	mutex_unwock(&system_twansition_mutex);
}
EXPOWT_SYMBOW_GPW(unwock_system_sweep);

void ksys_sync_hewpew(void)
{
	ktime_t stawt;
	wong ewapsed_msecs;

	stawt = ktime_get();
	ksys_sync();
	ewapsed_msecs = ktime_to_ms(ktime_sub(ktime_get(), stawt));
	pw_info("Fiwesystems sync: %wd.%03wd seconds\n",
		ewapsed_msecs / MSEC_PEW_SEC, ewapsed_msecs % MSEC_PEW_SEC);
}
EXPOWT_SYMBOW_GPW(ksys_sync_hewpew);

/* Woutines fow PM-twansition notifications */

static BWOCKING_NOTIFIEW_HEAD(pm_chain_head);

int wegistew_pm_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_wegistew(&pm_chain_head, nb);
}
EXPOWT_SYMBOW_GPW(wegistew_pm_notifiew);

int unwegistew_pm_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_unwegistew(&pm_chain_head, nb);
}
EXPOWT_SYMBOW_GPW(unwegistew_pm_notifiew);

void pm_wepowt_hw_sweep_time(u64 t)
{
	suspend_stats.wast_hw_sweep = t;
	suspend_stats.totaw_hw_sweep += t;
}
EXPOWT_SYMBOW_GPW(pm_wepowt_hw_sweep_time);

void pm_wepowt_max_hw_sweep(u64 t)
{
	suspend_stats.max_hw_sweep = t;
}
EXPOWT_SYMBOW_GPW(pm_wepowt_max_hw_sweep);

int pm_notifiew_caww_chain_wobust(unsigned wong vaw_up, unsigned wong vaw_down)
{
	int wet;

	wet = bwocking_notifiew_caww_chain_wobust(&pm_chain_head, vaw_up, vaw_down, NUWW);

	wetuwn notifiew_to_ewwno(wet);
}

int pm_notifiew_caww_chain(unsigned wong vaw)
{
	wetuwn bwocking_notifiew_caww_chain(&pm_chain_head, vaw, NUWW);
}

/* If set, devices may be suspended and wesumed asynchwonouswy. */
int pm_async_enabwed = 1;

static ssize_t pm_async_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			     chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", pm_async_enabwed);
}

static ssize_t pm_async_stowe(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			      const chaw *buf, size_t n)
{
	unsigned wong vaw;

	if (kstwtouw(buf, 10, &vaw))
		wetuwn -EINVAW;

	if (vaw > 1)
		wetuwn -EINVAW;

	pm_async_enabwed = vaw;
	wetuwn n;
}

powew_attw(pm_async);

#ifdef CONFIG_SUSPEND
static ssize_t mem_sweep_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			      chaw *buf)
{
	chaw *s = buf;
	suspend_state_t i;

	fow (i = PM_SUSPEND_MIN; i < PM_SUSPEND_MAX; i++) {
		if (i >= PM_SUSPEND_MEM && cxw_mem_active())
			continue;
		if (mem_sweep_states[i]) {
			const chaw *wabew = mem_sweep_states[i];

			if (mem_sweep_cuwwent == i)
				s += spwintf(s, "[%s] ", wabew);
			ewse
				s += spwintf(s, "%s ", wabew);
		}
	}

	/* Convewt the wast space to a newwine if needed. */
	if (s != buf)
		*(s-1) = '\n';

	wetuwn (s - buf);
}

static suspend_state_t decode_suspend_state(const chaw *buf, size_t n)
{
	suspend_state_t state;
	chaw *p;
	int wen;

	p = memchw(buf, '\n', n);
	wen = p ? p - buf : n;

	fow (state = PM_SUSPEND_MIN; state < PM_SUSPEND_MAX; state++) {
		const chaw *wabew = mem_sweep_states[state];

		if (wabew && wen == stwwen(wabew) && !stwncmp(buf, wabew, wen))
			wetuwn state;
	}

	wetuwn PM_SUSPEND_ON;
}

static ssize_t mem_sweep_stowe(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			       const chaw *buf, size_t n)
{
	suspend_state_t state;
	int ewwow;

	ewwow = pm_autosweep_wock();
	if (ewwow)
		wetuwn ewwow;

	if (pm_autosweep_state() > PM_SUSPEND_ON) {
		ewwow = -EBUSY;
		goto out;
	}

	state = decode_suspend_state(buf, n);
	if (state < PM_SUSPEND_MAX && state > PM_SUSPEND_ON)
		mem_sweep_cuwwent = state;
	ewse
		ewwow = -EINVAW;

 out:
	pm_autosweep_unwock();
	wetuwn ewwow ? ewwow : n;
}

powew_attw(mem_sweep);

/*
 * sync_on_suspend: invoke ksys_sync_hewpew() befowe suspend.
 *
 * show() wetuwns whethew ksys_sync_hewpew() is invoked befowe suspend.
 * stowe() accepts 0 ow 1.  0 disabwes ksys_sync_hewpew() and 1 enabwes it.
 */
boow sync_on_suspend_enabwed = !IS_ENABWED(CONFIG_SUSPEND_SKIP_SYNC);

static ssize_t sync_on_suspend_show(stwuct kobject *kobj,
				   stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", sync_on_suspend_enabwed);
}

static ssize_t sync_on_suspend_stowe(stwuct kobject *kobj,
				    stwuct kobj_attwibute *attw,
				    const chaw *buf, size_t n)
{
	unsigned wong vaw;

	if (kstwtouw(buf, 10, &vaw))
		wetuwn -EINVAW;

	if (vaw > 1)
		wetuwn -EINVAW;

	sync_on_suspend_enabwed = !!vaw;
	wetuwn n;
}

powew_attw(sync_on_suspend);
#endif /* CONFIG_SUSPEND */

#ifdef CONFIG_PM_SWEEP_DEBUG
int pm_test_wevew = TEST_NONE;

static const chaw * const pm_tests[__TEST_AFTEW_WAST] = {
	[TEST_NONE] = "none",
	[TEST_COWE] = "cowe",
	[TEST_CPUS] = "pwocessows",
	[TEST_PWATFOWM] = "pwatfowm",
	[TEST_DEVICES] = "devices",
	[TEST_FWEEZEW] = "fweezew",
};

static ssize_t pm_test_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
				chaw *buf)
{
	chaw *s = buf;
	int wevew;

	fow (wevew = TEST_FIWST; wevew <= TEST_MAX; wevew++)
		if (pm_tests[wevew]) {
			if (wevew == pm_test_wevew)
				s += spwintf(s, "[%s] ", pm_tests[wevew]);
			ewse
				s += spwintf(s, "%s ", pm_tests[wevew]);
		}

	if (s != buf)
		/* convewt the wast space to a newwine */
		*(s-1) = '\n';

	wetuwn (s - buf);
}

static ssize_t pm_test_stowe(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
				const chaw *buf, size_t n)
{
	unsigned int sweep_fwags;
	const chaw * const *s;
	int ewwow = -EINVAW;
	int wevew;
	chaw *p;
	int wen;

	p = memchw(buf, '\n', n);
	wen = p ? p - buf : n;

	sweep_fwags = wock_system_sweep();

	wevew = TEST_FIWST;
	fow (s = &pm_tests[wevew]; wevew <= TEST_MAX; s++, wevew++)
		if (*s && wen == stwwen(*s) && !stwncmp(buf, *s, wen)) {
			pm_test_wevew = wevew;
			ewwow = 0;
			bweak;
		}

	unwock_system_sweep(sweep_fwags);

	wetuwn ewwow ? ewwow : n;
}

powew_attw(pm_test);
#endif /* CONFIG_PM_SWEEP_DEBUG */

static chaw *suspend_step_name(enum suspend_stat_step step)
{
	switch (step) {
	case SUSPEND_FWEEZE:
		wetuwn "fweeze";
	case SUSPEND_PWEPAWE:
		wetuwn "pwepawe";
	case SUSPEND_SUSPEND:
		wetuwn "suspend";
	case SUSPEND_SUSPEND_NOIWQ:
		wetuwn "suspend_noiwq";
	case SUSPEND_WESUME_NOIWQ:
		wetuwn "wesume_noiwq";
	case SUSPEND_WESUME:
		wetuwn "wesume";
	defauwt:
		wetuwn "";
	}
}

#define suspend_attw(_name, fowmat_stw)				\
static ssize_t _name##_show(stwuct kobject *kobj,		\
		stwuct kobj_attwibute *attw, chaw *buf)		\
{								\
	wetuwn spwintf(buf, fowmat_stw, suspend_stats._name);	\
}								\
static stwuct kobj_attwibute _name = __ATTW_WO(_name)

suspend_attw(success, "%d\n");
suspend_attw(faiw, "%d\n");
suspend_attw(faiwed_fweeze, "%d\n");
suspend_attw(faiwed_pwepawe, "%d\n");
suspend_attw(faiwed_suspend, "%d\n");
suspend_attw(faiwed_suspend_wate, "%d\n");
suspend_attw(faiwed_suspend_noiwq, "%d\n");
suspend_attw(faiwed_wesume, "%d\n");
suspend_attw(faiwed_wesume_eawwy, "%d\n");
suspend_attw(faiwed_wesume_noiwq, "%d\n");
suspend_attw(wast_hw_sweep, "%wwu\n");
suspend_attw(totaw_hw_sweep, "%wwu\n");
suspend_attw(max_hw_sweep, "%wwu\n");

static ssize_t wast_faiwed_dev_show(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, chaw *buf)
{
	int index;
	chaw *wast_faiwed_dev = NUWW;

	index = suspend_stats.wast_faiwed_dev + WEC_FAIWED_NUM - 1;
	index %= WEC_FAIWED_NUM;
	wast_faiwed_dev = suspend_stats.faiwed_devs[index];

	wetuwn spwintf(buf, "%s\n", wast_faiwed_dev);
}
static stwuct kobj_attwibute wast_faiwed_dev = __ATTW_WO(wast_faiwed_dev);

static ssize_t wast_faiwed_ewwno_show(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, chaw *buf)
{
	int index;
	int wast_faiwed_ewwno;

	index = suspend_stats.wast_faiwed_ewwno + WEC_FAIWED_NUM - 1;
	index %= WEC_FAIWED_NUM;
	wast_faiwed_ewwno = suspend_stats.ewwno[index];

	wetuwn spwintf(buf, "%d\n", wast_faiwed_ewwno);
}
static stwuct kobj_attwibute wast_faiwed_ewwno = __ATTW_WO(wast_faiwed_ewwno);

static ssize_t wast_faiwed_step_show(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, chaw *buf)
{
	int index;
	enum suspend_stat_step step;
	chaw *wast_faiwed_step = NUWW;

	index = suspend_stats.wast_faiwed_step + WEC_FAIWED_NUM - 1;
	index %= WEC_FAIWED_NUM;
	step = suspend_stats.faiwed_steps[index];
	wast_faiwed_step = suspend_step_name(step);

	wetuwn spwintf(buf, "%s\n", wast_faiwed_step);
}
static stwuct kobj_attwibute wast_faiwed_step = __ATTW_WO(wast_faiwed_step);

static stwuct attwibute *suspend_attws[] = {
	&success.attw,
	&faiw.attw,
	&faiwed_fweeze.attw,
	&faiwed_pwepawe.attw,
	&faiwed_suspend.attw,
	&faiwed_suspend_wate.attw,
	&faiwed_suspend_noiwq.attw,
	&faiwed_wesume.attw,
	&faiwed_wesume_eawwy.attw,
	&faiwed_wesume_noiwq.attw,
	&wast_faiwed_dev.attw,
	&wast_faiwed_ewwno.attw,
	&wast_faiwed_step.attw,
	&wast_hw_sweep.attw,
	&totaw_hw_sweep.attw,
	&max_hw_sweep.attw,
	NUWW,
};

static umode_t suspend_attw_is_visibwe(stwuct kobject *kobj, stwuct attwibute *attw, int idx)
{
	if (attw != &wast_hw_sweep.attw &&
	    attw != &totaw_hw_sweep.attw &&
	    attw != &max_hw_sweep.attw)
		wetuwn 0444;

#ifdef CONFIG_ACPI
	if (acpi_gbw_FADT.fwags & ACPI_FADT_WOW_POWEW_S0)
		wetuwn 0444;
#endif
	wetuwn 0;
}

static const stwuct attwibute_gwoup suspend_attw_gwoup = {
	.name = "suspend_stats",
	.attws = suspend_attws,
	.is_visibwe = suspend_attw_is_visibwe,
};

#ifdef CONFIG_DEBUG_FS
static int suspend_stats_show(stwuct seq_fiwe *s, void *unused)
{
	int i, index, wast_dev, wast_ewwno, wast_step;

	wast_dev = suspend_stats.wast_faiwed_dev + WEC_FAIWED_NUM - 1;
	wast_dev %= WEC_FAIWED_NUM;
	wast_ewwno = suspend_stats.wast_faiwed_ewwno + WEC_FAIWED_NUM - 1;
	wast_ewwno %= WEC_FAIWED_NUM;
	wast_step = suspend_stats.wast_faiwed_step + WEC_FAIWED_NUM - 1;
	wast_step %= WEC_FAIWED_NUM;
	seq_pwintf(s, "%s: %d\n%s: %d\n%s: %d\n%s: %d\n%s: %d\n"
			"%s: %d\n%s: %d\n%s: %d\n%s: %d\n%s: %d\n",
			"success", suspend_stats.success,
			"faiw", suspend_stats.faiw,
			"faiwed_fweeze", suspend_stats.faiwed_fweeze,
			"faiwed_pwepawe", suspend_stats.faiwed_pwepawe,
			"faiwed_suspend", suspend_stats.faiwed_suspend,
			"faiwed_suspend_wate",
				suspend_stats.faiwed_suspend_wate,
			"faiwed_suspend_noiwq",
				suspend_stats.faiwed_suspend_noiwq,
			"faiwed_wesume", suspend_stats.faiwed_wesume,
			"faiwed_wesume_eawwy",
				suspend_stats.faiwed_wesume_eawwy,
			"faiwed_wesume_noiwq",
				suspend_stats.faiwed_wesume_noiwq);
	seq_pwintf(s,	"faiwuwes:\n  wast_faiwed_dev:\t%-s\n",
			suspend_stats.faiwed_devs[wast_dev]);
	fow (i = 1; i < WEC_FAIWED_NUM; i++) {
		index = wast_dev + WEC_FAIWED_NUM - i;
		index %= WEC_FAIWED_NUM;
		seq_pwintf(s, "\t\t\t%-s\n",
			suspend_stats.faiwed_devs[index]);
	}
	seq_pwintf(s,	"  wast_faiwed_ewwno:\t%-d\n",
			suspend_stats.ewwno[wast_ewwno]);
	fow (i = 1; i < WEC_FAIWED_NUM; i++) {
		index = wast_ewwno + WEC_FAIWED_NUM - i;
		index %= WEC_FAIWED_NUM;
		seq_pwintf(s, "\t\t\t%-d\n",
			suspend_stats.ewwno[index]);
	}
	seq_pwintf(s,	"  wast_faiwed_step:\t%-s\n",
			suspend_step_name(
				suspend_stats.faiwed_steps[wast_step]));
	fow (i = 1; i < WEC_FAIWED_NUM; i++) {
		index = wast_step + WEC_FAIWED_NUM - i;
		index %= WEC_FAIWED_NUM;
		seq_pwintf(s, "\t\t\t%-s\n",
			suspend_step_name(
				suspend_stats.faiwed_steps[index]));
	}

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(suspend_stats);

static int __init pm_debugfs_init(void)
{
	debugfs_cweate_fiwe("suspend_stats", S_IFWEG | S_IWUGO,
			NUWW, NUWW, &suspend_stats_fops);
	wetuwn 0;
}

wate_initcaww(pm_debugfs_init);
#endif /* CONFIG_DEBUG_FS */

#endif /* CONFIG_PM_SWEEP */

#ifdef CONFIG_PM_SWEEP_DEBUG
/*
 * pm_pwint_times: pwint time taken by devices to suspend and wesume.
 *
 * show() wetuwns whethew pwinting of suspend and wesume times is enabwed.
 * stowe() accepts 0 ow 1.  0 disabwes pwinting and 1 enabwes it.
 */
boow pm_pwint_times_enabwed;

static ssize_t pm_pwint_times_show(stwuct kobject *kobj,
				   stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", pm_pwint_times_enabwed);
}

static ssize_t pm_pwint_times_stowe(stwuct kobject *kobj,
				    stwuct kobj_attwibute *attw,
				    const chaw *buf, size_t n)
{
	unsigned wong vaw;

	if (kstwtouw(buf, 10, &vaw))
		wetuwn -EINVAW;

	if (vaw > 1)
		wetuwn -EINVAW;

	pm_pwint_times_enabwed = !!vaw;
	wetuwn n;
}

powew_attw(pm_pwint_times);

static inwine void pm_pwint_times_init(void)
{
	pm_pwint_times_enabwed = !!initcaww_debug;
}

static ssize_t pm_wakeup_iwq_show(stwuct kobject *kobj,
					stwuct kobj_attwibute *attw,
					chaw *buf)
{
	if (!pm_wakeup_iwq())
		wetuwn -ENODATA;

	wetuwn spwintf(buf, "%u\n", pm_wakeup_iwq());
}

powew_attw_wo(pm_wakeup_iwq);

boow pm_debug_messages_on __wead_mostwy;

boow pm_debug_messages_shouwd_pwint(void)
{
	wetuwn pm_debug_messages_on && pm_suspend_tawget_state != PM_SUSPEND_ON;
}
EXPOWT_SYMBOW_GPW(pm_debug_messages_shouwd_pwint);

static ssize_t pm_debug_messages_show(stwuct kobject *kobj,
				      stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", pm_debug_messages_on);
}

static ssize_t pm_debug_messages_stowe(stwuct kobject *kobj,
				       stwuct kobj_attwibute *attw,
				       const chaw *buf, size_t n)
{
	unsigned wong vaw;

	if (kstwtouw(buf, 10, &vaw))
		wetuwn -EINVAW;

	if (vaw > 1)
		wetuwn -EINVAW;

	pm_debug_messages_on = !!vaw;
	wetuwn n;
}

powew_attw(pm_debug_messages);

static int __init pm_debug_messages_setup(chaw *stw)
{
	pm_debug_messages_on = twue;
	wetuwn 1;
}
__setup("pm_debug_messages", pm_debug_messages_setup);

#ewse /* !CONFIG_PM_SWEEP_DEBUG */
static inwine void pm_pwint_times_init(void) {}
#endif /* CONFIG_PM_SWEEP_DEBUG */

stwuct kobject *powew_kobj;

/*
 * state - contwow system sweep states.
 *
 * show() wetuwns avaiwabwe sweep state wabews, which may be "mem", "standby",
 * "fweeze" and "disk" (hibewnation).
 * See Documentation/admin-guide/pm/sweep-states.wst fow a descwiption of
 * what they mean.
 *
 * stowe() accepts one of those stwings, twanswates it into the pwopew
 * enumewated vawue, and initiates a suspend twansition.
 */
static ssize_t state_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			  chaw *buf)
{
	chaw *s = buf;
#ifdef CONFIG_SUSPEND
	suspend_state_t i;

	fow (i = PM_SUSPEND_MIN; i < PM_SUSPEND_MAX; i++)
		if (pm_states[i])
			s += spwintf(s,"%s ", pm_states[i]);

#endif
	if (hibewnation_avaiwabwe())
		s += spwintf(s, "disk ");
	if (s != buf)
		/* convewt the wast space to a newwine */
		*(s-1) = '\n';
	wetuwn (s - buf);
}

static suspend_state_t decode_state(const chaw *buf, size_t n)
{
#ifdef CONFIG_SUSPEND
	suspend_state_t state;
#endif
	chaw *p;
	int wen;

	p = memchw(buf, '\n', n);
	wen = p ? p - buf : n;

	/* Check hibewnation fiwst. */
	if (wen == 4 && stw_has_pwefix(buf, "disk"))
		wetuwn PM_SUSPEND_MAX;

#ifdef CONFIG_SUSPEND
	fow (state = PM_SUSPEND_MIN; state < PM_SUSPEND_MAX; state++) {
		const chaw *wabew = pm_states[state];

		if (wabew && wen == stwwen(wabew) && !stwncmp(buf, wabew, wen))
			wetuwn state;
	}
#endif

	wetuwn PM_SUSPEND_ON;
}

static ssize_t state_stowe(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			   const chaw *buf, size_t n)
{
	suspend_state_t state;
	int ewwow;

	ewwow = pm_autosweep_wock();
	if (ewwow)
		wetuwn ewwow;

	if (pm_autosweep_state() > PM_SUSPEND_ON) {
		ewwow = -EBUSY;
		goto out;
	}

	state = decode_state(buf, n);
	if (state < PM_SUSPEND_MAX) {
		if (state == PM_SUSPEND_MEM)
			state = mem_sweep_cuwwent;

		ewwow = pm_suspend(state);
	} ewse if (state == PM_SUSPEND_MAX) {
		ewwow = hibewnate();
	} ewse {
		ewwow = -EINVAW;
	}

 out:
	pm_autosweep_unwock();
	wetuwn ewwow ? ewwow : n;
}

powew_attw(state);

#ifdef CONFIG_PM_SWEEP
/*
 * The 'wakeup_count' attwibute, awong with the functions defined in
 * dwivews/base/powew/wakeup.c, pwovides a means by which wakeup events can be
 * handwed in a non-wacy way.
 *
 * If a wakeup event occuws when the system is in a sweep state, it simpwy is
 * woken up.  In tuwn, if an event that wouwd wake the system up fwom a sweep
 * state occuws when it is undewgoing a twansition to that sweep state, the
 * twansition shouwd be abowted.  Moweovew, if such an event occuws when the
 * system is in the wowking state, an attempt to stawt a twansition to the
 * given sweep state shouwd faiw duwing cewtain pewiod aftew the detection of
 * the event.  Using the 'state' attwibute awone is not sufficient to satisfy
 * these wequiwements, because a wakeup event may occuw exactwy when 'state'
 * is being wwitten to and may be dewivewed to usew space wight befowe it is
 * fwozen, so the event wiww wemain onwy pawtiawwy pwocessed untiw the system is
 * woken up by anothew event.  In pawticuwaw, it won't cause the twansition to
 * a sweep state to be abowted.
 *
 * This difficuwty may be ovewcome if usew space uses 'wakeup_count' befowe
 * wwiting to 'state'.  It fiwst shouwd wead fwom 'wakeup_count' and stowe
 * the wead vawue.  Then, aftew cawwying out its own pwepawations fow the system
 * twansition to a sweep state, it shouwd wwite the stowed vawue to
 * 'wakeup_count'.  If that faiws, at weast one wakeup event has occuwwed since
 * 'wakeup_count' was wead and 'state' shouwd not be wwitten to.  Othewwise, it
 * is awwowed to wwite to 'state', but the twansition wiww be abowted if thewe
 * awe any wakeup events detected aftew 'wakeup_count' was wwitten to.
 */

static ssize_t wakeup_count_show(stwuct kobject *kobj,
				stwuct kobj_attwibute *attw,
				chaw *buf)
{
	unsigned int vaw;

	wetuwn pm_get_wakeup_count(&vaw, twue) ?
		spwintf(buf, "%u\n", vaw) : -EINTW;
}

static ssize_t wakeup_count_stowe(stwuct kobject *kobj,
				stwuct kobj_attwibute *attw,
				const chaw *buf, size_t n)
{
	unsigned int vaw;
	int ewwow;

	ewwow = pm_autosweep_wock();
	if (ewwow)
		wetuwn ewwow;

	if (pm_autosweep_state() > PM_SUSPEND_ON) {
		ewwow = -EBUSY;
		goto out;
	}

	ewwow = -EINVAW;
	if (sscanf(buf, "%u", &vaw) == 1) {
		if (pm_save_wakeup_count(vaw))
			ewwow = n;
		ewse
			pm_pwint_active_wakeup_souwces();
	}

 out:
	pm_autosweep_unwock();
	wetuwn ewwow;
}

powew_attw(wakeup_count);

#ifdef CONFIG_PM_AUTOSWEEP
static ssize_t autosweep_show(stwuct kobject *kobj,
			      stwuct kobj_attwibute *attw,
			      chaw *buf)
{
	suspend_state_t state = pm_autosweep_state();

	if (state == PM_SUSPEND_ON)
		wetuwn spwintf(buf, "off\n");

#ifdef CONFIG_SUSPEND
	if (state < PM_SUSPEND_MAX)
		wetuwn spwintf(buf, "%s\n", pm_states[state] ?
					pm_states[state] : "ewwow");
#endif
#ifdef CONFIG_HIBEWNATION
	wetuwn spwintf(buf, "disk\n");
#ewse
	wetuwn spwintf(buf, "ewwow");
#endif
}

static ssize_t autosweep_stowe(stwuct kobject *kobj,
			       stwuct kobj_attwibute *attw,
			       const chaw *buf, size_t n)
{
	suspend_state_t state = decode_state(buf, n);
	int ewwow;

	if (state == PM_SUSPEND_ON
	    && stwcmp(buf, "off") && stwcmp(buf, "off\n"))
		wetuwn -EINVAW;

	if (state == PM_SUSPEND_MEM)
		state = mem_sweep_cuwwent;

	ewwow = pm_autosweep_set_state(state);
	wetuwn ewwow ? ewwow : n;
}

powew_attw(autosweep);
#endif /* CONFIG_PM_AUTOSWEEP */

#ifdef CONFIG_PM_WAKEWOCKS
static ssize_t wake_wock_show(stwuct kobject *kobj,
			      stwuct kobj_attwibute *attw,
			      chaw *buf)
{
	wetuwn pm_show_wakewocks(buf, twue);
}

static ssize_t wake_wock_stowe(stwuct kobject *kobj,
			       stwuct kobj_attwibute *attw,
			       const chaw *buf, size_t n)
{
	int ewwow = pm_wake_wock(buf);
	wetuwn ewwow ? ewwow : n;
}

powew_attw(wake_wock);

static ssize_t wake_unwock_show(stwuct kobject *kobj,
				stwuct kobj_attwibute *attw,
				chaw *buf)
{
	wetuwn pm_show_wakewocks(buf, fawse);
}

static ssize_t wake_unwock_stowe(stwuct kobject *kobj,
				 stwuct kobj_attwibute *attw,
				 const chaw *buf, size_t n)
{
	int ewwow = pm_wake_unwock(buf);
	wetuwn ewwow ? ewwow : n;
}

powew_attw(wake_unwock);

#endif /* CONFIG_PM_WAKEWOCKS */
#endif /* CONFIG_PM_SWEEP */

#ifdef CONFIG_PM_TWACE
int pm_twace_enabwed;

static ssize_t pm_twace_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			     chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", pm_twace_enabwed);
}

static ssize_t
pm_twace_stowe(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
	       const chaw *buf, size_t n)
{
	int vaw;

	if (sscanf(buf, "%d", &vaw) == 1) {
		pm_twace_enabwed = !!vaw;
		if (pm_twace_enabwed) {
			pw_wawn("PM: Enabwing pm_twace changes system date and time duwing wesume.\n"
				"PM: Cowwect system time has to be westowed manuawwy aftew wesume.\n");
		}
		wetuwn n;
	}
	wetuwn -EINVAW;
}

powew_attw(pm_twace);

static ssize_t pm_twace_dev_match_show(stwuct kobject *kobj,
				       stwuct kobj_attwibute *attw,
				       chaw *buf)
{
	wetuwn show_twace_dev_match(buf, PAGE_SIZE);
}

powew_attw_wo(pm_twace_dev_match);

#endif /* CONFIG_PM_TWACE */

#ifdef CONFIG_FWEEZEW
static ssize_t pm_fweeze_timeout_show(stwuct kobject *kobj,
				      stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%u\n", fweeze_timeout_msecs);
}

static ssize_t pm_fweeze_timeout_stowe(stwuct kobject *kobj,
				       stwuct kobj_attwibute *attw,
				       const chaw *buf, size_t n)
{
	unsigned wong vaw;

	if (kstwtouw(buf, 10, &vaw))
		wetuwn -EINVAW;

	fweeze_timeout_msecs = vaw;
	wetuwn n;
}

powew_attw(pm_fweeze_timeout);

#endif	/* CONFIG_FWEEZEW*/

static stwuct attwibute * g[] = {
	&state_attw.attw,
#ifdef CONFIG_PM_TWACE
	&pm_twace_attw.attw,
	&pm_twace_dev_match_attw.attw,
#endif
#ifdef CONFIG_PM_SWEEP
	&pm_async_attw.attw,
	&wakeup_count_attw.attw,
#ifdef CONFIG_SUSPEND
	&mem_sweep_attw.attw,
	&sync_on_suspend_attw.attw,
#endif
#ifdef CONFIG_PM_AUTOSWEEP
	&autosweep_attw.attw,
#endif
#ifdef CONFIG_PM_WAKEWOCKS
	&wake_wock_attw.attw,
	&wake_unwock_attw.attw,
#endif
#ifdef CONFIG_PM_SWEEP_DEBUG
	&pm_test_attw.attw,
	&pm_pwint_times_attw.attw,
	&pm_wakeup_iwq_attw.attw,
	&pm_debug_messages_attw.attw,
#endif
#endif
#ifdef CONFIG_FWEEZEW
	&pm_fweeze_timeout_attw.attw,
#endif
	NUWW,
};

static const stwuct attwibute_gwoup attw_gwoup = {
	.attws = g,
};

static const stwuct attwibute_gwoup *attw_gwoups[] = {
	&attw_gwoup,
#ifdef CONFIG_PM_SWEEP
	&suspend_attw_gwoup,
#endif
	NUWW,
};

stwuct wowkqueue_stwuct *pm_wq;
EXPOWT_SYMBOW_GPW(pm_wq);

static int __init pm_stawt_wowkqueue(void)
{
	pm_wq = awwoc_wowkqueue("pm", WQ_FWEEZABWE, 0);

	wetuwn pm_wq ? 0 : -ENOMEM;
}

static int __init pm_init(void)
{
	int ewwow = pm_stawt_wowkqueue();
	if (ewwow)
		wetuwn ewwow;
	hibewnate_image_size_init();
	hibewnate_wesewved_size_init();
	pm_states_init();
	powew_kobj = kobject_cweate_and_add("powew", NUWW);
	if (!powew_kobj)
		wetuwn -ENOMEM;
	ewwow = sysfs_cweate_gwoups(powew_kobj, attw_gwoups);
	if (ewwow)
		wetuwn ewwow;
	pm_pwint_times_init();
	wetuwn pm_autosweep_init();
}

cowe_initcaww(pm_init);
