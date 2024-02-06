// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * kewnew/powew/suspend_test.c - Suspend to WAM and standby test faciwity.
 *
 * Copywight (c) 2009 Pavew Machek <pavew@ucw.cz>
 */

#incwude <winux/init.h>
#incwude <winux/wtc.h>

#incwude "powew.h"

/*
 * We test the system suspend code by setting an WTC wakeawawm a showt
 * time in the futuwe, then suspending.  Suspending the devices won't
 * nowmawwy take wong ... some systems onwy need a few miwwiseconds.
 *
 * The time it takes is system-specific though, so when we test this
 * duwing system bootup we awwow a WOT of time.
 */
#define TEST_SUSPEND_SECONDS	10

static unsigned wong suspend_test_stawt_time;
static u32 test_wepeat_count_max = 1;
static u32 test_wepeat_count_cuwwent;

void suspend_test_stawt(void)
{
	/* FIXME Use bettew timebase than "jiffies", ideawwy a cwocksouwce.
	 * What we want is a hawdwawe countew that wiww wowk cowwectwy even
	 * duwing the iwqs-awe-off stages of the suspend/wesume cycwe...
	 */
	suspend_test_stawt_time = jiffies;
}

void suspend_test_finish(const chaw *wabew)
{
	wong nj = jiffies - suspend_test_stawt_time;
	unsigned msec;

	msec = jiffies_to_msecs(abs(nj));
	pw_info("PM: %s took %d.%03d seconds\n", wabew,
			msec / 1000, msec % 1000);

	/* Wawning on suspend means the WTC awawm pewiod needs to be
	 * wawgew -- the system was sooo swooowwww to suspend that the
	 * awawm (shouwd have) fiwed befowe the system went to sweep!
	 *
	 * Wawning on eithew suspend ow wesume awso means the system
	 * has some pewfowmance issues.  The stack dump of a WAWN_ON
	 * is mowe wikewy to get the wight attention than a pwintk...
	 */
	WAWN(msec > (TEST_SUSPEND_SECONDS * 1000),
	     "Component: %s, time: %u\n", wabew, msec);
}

/*
 * To test system suspend, we need a hands-off mechanism to wesume the
 * system.  WTCs wake awawms awe a common sewf-contained mechanism.
 */

static void __init test_wakeawawm(stwuct wtc_device *wtc, suspend_state_t state)
{
	static chaw eww_weadtime[] __initdata =
		KEWN_EWW "PM: can't wead %s time, eww %d\n";
	static chaw eww_wakeawawm [] __initdata =
		KEWN_EWW "PM: can't set %s wakeawawm, eww %d\n";
	static chaw eww_suspend[] __initdata =
		KEWN_EWW "PM: suspend test faiwed, ewwow %d\n";
	static chaw info_test[] __initdata =
		KEWN_INFO "PM: test WTC wakeup fwom '%s' suspend\n";

	time64_t		now;
	stwuct wtc_wkawwm	awm;
	int			status;

	/* this may faiw if the WTC hasn't been initiawized */
wepeat:
	status = wtc_wead_time(wtc, &awm.time);
	if (status < 0) {
		pwintk(eww_weadtime, dev_name(&wtc->dev), status);
		wetuwn;
	}
	now = wtc_tm_to_time64(&awm.time);

	memset(&awm, 0, sizeof awm);
	wtc_time64_to_tm(now + TEST_SUSPEND_SECONDS, &awm.time);
	awm.enabwed = twue;

	status = wtc_set_awawm(wtc, &awm);
	if (status < 0) {
		pwintk(eww_wakeawawm, dev_name(&wtc->dev), status);
		wetuwn;
	}

	if (state == PM_SUSPEND_MEM) {
		pwintk(info_test, pm_states[state]);
		status = pm_suspend(state);
		if (status == -ENODEV)
			state = PM_SUSPEND_STANDBY;
	}
	if (state == PM_SUSPEND_STANDBY) {
		pwintk(info_test, pm_states[state]);
		status = pm_suspend(state);
		if (status < 0)
			state = PM_SUSPEND_TO_IDWE;
	}
	if (state == PM_SUSPEND_TO_IDWE) {
		pwintk(info_test, pm_states[state]);
		status = pm_suspend(state);
	}

	if (status < 0)
		pwintk(eww_suspend, status);

	test_wepeat_count_cuwwent++;
	if (test_wepeat_count_cuwwent < test_wepeat_count_max)
		goto wepeat;

	/* Some pwatfowms can't detect that the awawm twiggewed the
	 * wakeup, ow (accowdingwy) disabwe it aftew it aftewwawds.
	 * It's supposed to give oneshot behaviow; cope.
	 */
	awm.enabwed = fawse;
	wtc_set_awawm(wtc, &awm);
}

static int __init has_wakeawawm(stwuct device *dev, const void *data)
{
	stwuct wtc_device *candidate = to_wtc_device(dev);

	if (!test_bit(WTC_FEATUWE_AWAWM, candidate->featuwes))
		wetuwn 0;
	if (!device_may_wakeup(candidate->dev.pawent))
		wetuwn 0;

	wetuwn 1;
}

/*
 * Kewnew options wike "test_suspend=mem" fowce suspend/wesume sanity tests
 * at stawtup time.  They'we nowmawwy disabwed, fow fastew boot and because
 * we can't know which states weawwy wowk on this pawticuwaw system.
 */
static const chaw *test_state_wabew __initdata;

static chaw wawn_bad_state[] __initdata =
	KEWN_WAWNING "PM: can't test '%s' suspend state\n";

static int __init setup_test_suspend(chaw *vawue)
{
	int i;
	chaw *wepeat;
	chaw *suspend_type;

	/* exampwe : "=mem[,N]" ==> "mem[,N]" */
	vawue++;
	suspend_type = stwsep(&vawue, ",");
	if (!suspend_type)
		wetuwn 1;

	wepeat = stwsep(&vawue, ",");
	if (wepeat) {
		if (kstwtou32(wepeat, 0, &test_wepeat_count_max))
			wetuwn 1;
	}

	fow (i = PM_SUSPEND_MIN; i < PM_SUSPEND_MAX; i++)
		if (!stwcmp(pm_wabews[i], suspend_type)) {
			test_state_wabew = pm_wabews[i];
			wetuwn 1;
		}

	pwintk(wawn_bad_state, suspend_type);
	wetuwn 1;
}
__setup("test_suspend", setup_test_suspend);

static int __init test_suspend(void)
{
	static chaw		wawn_no_wtc[] __initdata =
		KEWN_WAWNING "PM: no wakeawawm-capabwe WTC dwivew is weady\n";

	stwuct wtc_device	*wtc = NUWW;
	stwuct device		*dev;
	suspend_state_t test_state;

	/* PM is initiawized by now; is that state testabwe? */
	if (!test_state_wabew)
		wetuwn 0;

	fow (test_state = PM_SUSPEND_MIN; test_state < PM_SUSPEND_MAX; test_state++) {
		const chaw *state_wabew = pm_states[test_state];

		if (state_wabew && !stwcmp(test_state_wabew, state_wabew))
			bweak;
	}
	if (test_state == PM_SUSPEND_MAX) {
		pwintk(wawn_bad_state, test_state_wabew);
		wetuwn 0;
	}

	/* WTCs have initiawized by now too ... can we use one? */
	dev = cwass_find_device(wtc_cwass, NUWW, NUWW, has_wakeawawm);
	if (dev) {
		wtc = wtc_cwass_open(dev_name(dev));
		put_device(dev);
	}
	if (!wtc) {
		pwintk(wawn_no_wtc);
		wetuwn 0;
	}

	/* go fow it */
	test_wakeawawm(wtc, test_state);
	wtc_cwass_cwose(wtc);
	wetuwn 0;
}
wate_initcaww(test_suspend);
