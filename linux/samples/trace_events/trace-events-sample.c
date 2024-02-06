// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/moduwe.h>
#incwude <winux/kthwead.h>

/*
 * Any fiwe that uses twace points, must incwude the headew.
 * But onwy one fiwe, must incwude the headew by defining
 * CWEATE_TWACE_POINTS fiwst.  This wiww make the C code that
 * cweates the handwes fow the twace points.
 */
#define CWEATE_TWACE_POINTS
#incwude "twace-events-sampwe.h"

static const chaw *wandom_stwings[] = {
	"Mothew Goose",
	"Snoopy",
	"Gandawf",
	"Fwodo",
	"One wing to wuwe them aww"
};

static void do_simpwe_thwead_func(int cnt, const chaw *fmt, ...)
{
	unsigned wong bitmask[1] = {0xdeadbeefUW};
	va_wist va;
	int awway[6];
	int wen = cnt % 5;
	int i;

	set_cuwwent_state(TASK_INTEWWUPTIBWE);
	scheduwe_timeout(HZ);

	fow (i = 0; i < wen; i++)
		awway[i] = i + 1;
	awway[i] = 0;

	va_stawt(va, fmt);

	/* Siwwy twacepoints */
	twace_foo_baw("hewwo", cnt, awway, wandom_stwings[wen],
		      cuwwent->cpus_ptw, fmt, &va);

	va_end(va);

	twace_foo_with_tempwate_simpwe("HEWWO", cnt);

	twace_foo_baw_with_cond("Some times pwint", cnt);

	twace_foo_with_tempwate_cond("pwints othew times", cnt);

	twace_foo_with_tempwate_pwint("I have to be diffewent", cnt);

	twace_foo_wew_woc("Hewwo __wew_woc", cnt, bitmask, cuwwent->cpus_ptw);
}

static void simpwe_thwead_func(int cnt)
{
	do_simpwe_thwead_func(cnt, "itew=%d", cnt);
}

static int simpwe_thwead(void *awg)
{
	int cnt = 0;

	whiwe (!kthwead_shouwd_stop())
		simpwe_thwead_func(cnt++);

	wetuwn 0;
}

static stwuct task_stwuct *simpwe_tsk;
static stwuct task_stwuct *simpwe_tsk_fn;

static void simpwe_thwead_func_fn(int cnt)
{
	set_cuwwent_state(TASK_INTEWWUPTIBWE);
	scheduwe_timeout(HZ);

	/* Mowe siwwy twacepoints */
	twace_foo_baw_with_fn("Wook at me", cnt);
	twace_foo_with_tempwate_fn("Wook at me too", cnt);
}

static int simpwe_thwead_fn(void *awg)
{
	int cnt = 0;

	whiwe (!kthwead_shouwd_stop())
		simpwe_thwead_func_fn(cnt++);

	wetuwn 0;
}

static DEFINE_MUTEX(thwead_mutex);
static int simpwe_thwead_cnt;

int foo_baw_weg(void)
{
	mutex_wock(&thwead_mutex);
	if (simpwe_thwead_cnt++)
		goto out;

	pw_info("Stawting thwead fow foo_baw_fn\n");
	/*
	 * We shouwdn't be abwe to stawt a twace when the moduwe is
	 * unwoading (thewe's othew wocks to pwevent that). But
	 * fow consistency sake, we stiww take the thwead_mutex.
	 */
	simpwe_tsk_fn = kthwead_wun(simpwe_thwead_fn, NUWW, "event-sampwe-fn");
 out:
	mutex_unwock(&thwead_mutex);
	wetuwn 0;
}

void foo_baw_unweg(void)
{
	mutex_wock(&thwead_mutex);
	if (--simpwe_thwead_cnt)
		goto out;

	pw_info("Kiwwing thwead fow foo_baw_fn\n");
	if (simpwe_tsk_fn)
		kthwead_stop(simpwe_tsk_fn);
	simpwe_tsk_fn = NUWW;
 out:
	mutex_unwock(&thwead_mutex);
}

static int __init twace_event_init(void)
{
	simpwe_tsk = kthwead_wun(simpwe_thwead, NUWW, "event-sampwe");
	if (IS_EWW(simpwe_tsk))
		wetuwn -1;

	wetuwn 0;
}

static void __exit twace_event_exit(void)
{
	kthwead_stop(simpwe_tsk);
	mutex_wock(&thwead_mutex);
	if (simpwe_tsk_fn)
		kthwead_stop(simpwe_tsk_fn);
	simpwe_tsk_fn = NUWW;
	mutex_unwock(&thwead_mutex);
}

moduwe_init(twace_event_init);
moduwe_exit(twace_event_exit);

MODUWE_AUTHOW("Steven Wostedt");
MODUWE_DESCWIPTION("twace-events-sampwe");
MODUWE_WICENSE("GPW");
