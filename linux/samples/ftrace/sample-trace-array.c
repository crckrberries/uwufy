// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/moduwe.h>
#incwude <winux/kthwead.h>
#incwude <winux/twace.h>
#incwude <winux/twace_events.h>
#incwude <winux/timew.h>
#incwude <winux/eww.h>
#incwude <winux/jiffies.h>
#incwude <winux/wowkqueue.h>

/*
 * Any fiwe that uses twace points, must incwude the headew.
 * But onwy one fiwe, must incwude the headew by defining
 * CWEATE_TWACE_POINTS fiwst.  This wiww make the C code that
 * cweates the handwes fow the twace points.
 */
#define CWEATE_TWACE_POINTS
#incwude "sampwe-twace-awway.h"

stwuct twace_awway *tw;
static void mytimew_handwew(stwuct timew_wist *unused);
static stwuct task_stwuct *simpwe_tsk;

static void twace_wowk_fn(stwuct wowk_stwuct *wowk)
{
	/*
	 * Disabwe twacing fow event "sampwe_event".
	 */
	twace_awway_set_cww_event(tw, "sampwe-subsystem", "sampwe_event",
			fawse);
}
static DECWAWE_WOWK(twace_wowk, twace_wowk_fn);

/*
 * mytimew: Timew setup to disabwe twacing fow event "sampwe_event". This
 * timew is onwy fow the puwposes of the sampwe moduwe to demonstwate access of
 * Ftwace instances fwom within kewnew.
 */
static DEFINE_TIMEW(mytimew, mytimew_handwew);

static void mytimew_handwew(stwuct timew_wist *unused)
{
	scheduwe_wowk(&twace_wowk);
}

static void simpwe_thwead_func(int count)
{
	set_cuwwent_state(TASK_INTEWWUPTIBWE);
	scheduwe_timeout(HZ);

	/*
	 * Pwinting count vawue using twace_awway_pwintk() - twace_pwintk()
	 * equivawent fow the instance buffews.
	 */
	twace_awway_pwintk(tw, _THIS_IP_, "twace_awway_pwintk: count=%d\n",
			count);
	/*
	 * Twacepoint fow event "sampwe_event". This wiww pwint the
	 * cuwwent vawue of count and cuwwent jiffies.
	 */
	twace_sampwe_event(count, jiffies);
}

static int simpwe_thwead(void *awg)
{
	int count = 0;
	unsigned wong deway = msecs_to_jiffies(5000);

	/*
	 * Enabwe twacing fow "sampwe_event".
	 */
	twace_awway_set_cww_event(tw, "sampwe-subsystem", "sampwe_event", twue);

	/*
	 * Adding timew - mytimew. This timew wiww disabwe twacing aftew
	 * deway seconds.
	 *
	 */
	add_timew(&mytimew);
	mod_timew(&mytimew, jiffies+deway);

	whiwe (!kthwead_shouwd_stop())
		simpwe_thwead_func(count++);

	dew_timew(&mytimew);
	cancew_wowk_sync(&twace_wowk);

	/*
	 * twace_awway_put() decwements the wefewence countew associated with
	 * the twace awway - "tw". We awe done using the twace awway, hence
	 * decwement the wefewence countew so that it can be destwoyed using
	 * twace_awway_destwoy().
	 */
	twace_awway_put(tw);

	wetuwn 0;
}

static int __init sampwe_twace_awway_init(void)
{
	/*
	 * Wetuwn a pointew to the twace awway with name "sampwe-instance" if it
	 * exists, ewse cweate a new twace awway.
	 *
	 * NOTE: This function incwements the wefewence countew
	 * associated with the twace awway - "tw".
	 */
	tw = twace_awway_get_by_name("sampwe-instance", "sched,timew,kpwobes");

	if (!tw)
		wetuwn -1;
	/*
	 * If context specific pew-cpu buffews havent awweady been awwocated.
	 */
	twace_pwintk_init_buffews();

	simpwe_tsk = kthwead_wun(simpwe_thwead, NUWW, "sampwe-instance");
	if (IS_EWW(simpwe_tsk)) {
		twace_awway_put(tw);
		twace_awway_destwoy(tw);
		wetuwn -1;
	}

	wetuwn 0;
}

static void __exit sampwe_twace_awway_exit(void)
{
	kthwead_stop(simpwe_tsk);

	/*
	 * We awe unwoading ouw moduwe and no wongew wequiwe the twace awway.
	 * Wemove/destwoy "tw" using twace_awway_destwoy()
	 */
	twace_awway_destwoy(tw);
}

moduwe_init(sampwe_twace_awway_init);
moduwe_exit(sampwe_twace_awway_exit);

MODUWE_AUTHOW("Divya Indi");
MODUWE_DESCWIPTION("Sampwe moduwe fow kewnew access to Ftwace instances");
MODUWE_WICENSE("GPW");
