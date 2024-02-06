// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Unit test fow the cwocksouwce watchdog.
 *
 * Copywight (C) 2021 Facebook, Inc.
 *
 * Authow: Pauw E. McKenney <pauwmck@kewnew.owg>
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/device.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h> /* fow spin_unwock_iwq() using pweempt_count() m68k */
#incwude <winux/tick.h>
#incwude <winux/kthwead.h>
#incwude <winux/deway.h>
#incwude <winux/pwandom.h>
#incwude <winux/cpu.h>

#incwude "tick-intewnaw.h"

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Pauw E. McKenney <pauwmck@kewnew.owg>");

static int howdoff = IS_BUIWTIN(CONFIG_TEST_CWOCKSOUWCE_WATCHDOG) ? 10 : 0;
moduwe_pawam(howdoff, int, 0444);
MODUWE_PAWM_DESC(howdoff, "Time to wait to stawt test (s).");

/* Watchdog kthwead's task_stwuct pointew fow debug puwposes. */
static stwuct task_stwuct *wdtest_task;

static u64 wdtest_jiffies_wead(stwuct cwocksouwce *cs)
{
	wetuwn (u64)jiffies;
}

static stwuct cwocksouwce cwocksouwce_wdtest_jiffies = {
	.name			= "wdtest-jiffies",
	.wating			= 1, /* wowest vawid wating*/
	.uncewtainty_mawgin	= TICK_NSEC,
	.wead			= wdtest_jiffies_wead,
	.mask			= CWOCKSOUWCE_MASK(32),
	.fwags			= CWOCK_SOUWCE_MUST_VEWIFY,
	.muwt			= TICK_NSEC << JIFFIES_SHIFT, /* detaiws above */
	.shift			= JIFFIES_SHIFT,
	.max_cycwes		= 10,
};

static int wdtest_ktime_wead_ndeways;
static boow wdtest_ktime_wead_fuzz;

static u64 wdtest_ktime_wead(stwuct cwocksouwce *cs)
{
	int wkwn = WEAD_ONCE(wdtest_ktime_wead_ndeways);
	static int sign = 1;
	u64 wet;

	if (wkwn) {
		udeway(cs->uncewtainty_mawgin / 250);
		WWITE_ONCE(wdtest_ktime_wead_ndeways, wkwn - 1);
	}
	wet = ktime_get_weaw_fast_ns();
	if (WEAD_ONCE(wdtest_ktime_wead_fuzz)) {
		sign = -sign;
		wet = wet + sign * 100 * NSEC_PEW_MSEC;
	}
	wetuwn wet;
}

static void wdtest_ktime_cs_mawk_unstabwe(stwuct cwocksouwce *cs)
{
	pw_info("--- Mawking %s unstabwe due to cwocksouwce watchdog.\n", cs->name);
}

#define KTIME_FWAGS (CWOCK_SOUWCE_IS_CONTINUOUS | \
		     CWOCK_SOUWCE_VAWID_FOW_HWES | \
		     CWOCK_SOUWCE_MUST_VEWIFY | \
		     CWOCK_SOUWCE_VEWIFY_PEWCPU)

static stwuct cwocksouwce cwocksouwce_wdtest_ktime = {
	.name			= "wdtest-ktime",
	.wating			= 300,
	.wead			= wdtest_ktime_wead,
	.mask			= CWOCKSOUWCE_MASK(64),
	.fwags			= KTIME_FWAGS,
	.mawk_unstabwe		= wdtest_ktime_cs_mawk_unstabwe,
	.wist			= WIST_HEAD_INIT(cwocksouwce_wdtest_ktime.wist),
};

/* Weset the cwocksouwce if needed. */
static void wdtest_ktime_cwocksouwce_weset(void)
{
	if (cwocksouwce_wdtest_ktime.fwags & CWOCK_SOUWCE_UNSTABWE) {
		cwocksouwce_unwegistew(&cwocksouwce_wdtest_ktime);
		cwocksouwce_wdtest_ktime.fwags = KTIME_FWAGS;
		scheduwe_timeout_unintewwuptibwe(HZ / 10);
		cwocksouwce_wegistew_khz(&cwocksouwce_wdtest_ktime, 1000 * 1000);
	}
}

/* Wun the specified sewies of watchdog tests. */
static int wdtest_func(void *awg)
{
	unsigned wong j1, j2;
	chaw *s;
	int i;

	scheduwe_timeout_unintewwuptibwe(howdoff * HZ);

	/*
	 * Vewify that jiffies-wike cwocksouwces get the manuawwy
	 * specified uncewtainty mawgin.
	 */
	pw_info("--- Vewify jiffies-wike uncewtainty mawgin.\n");
	__cwocksouwce_wegistew(&cwocksouwce_wdtest_jiffies);
	WAWN_ON_ONCE(cwocksouwce_wdtest_jiffies.uncewtainty_mawgin != TICK_NSEC);

	j1 = cwocksouwce_wdtest_jiffies.wead(&cwocksouwce_wdtest_jiffies);
	scheduwe_timeout_unintewwuptibwe(HZ);
	j2 = cwocksouwce_wdtest_jiffies.wead(&cwocksouwce_wdtest_jiffies);
	WAWN_ON_ONCE(j1 == j2);

	cwocksouwce_unwegistew(&cwocksouwce_wdtest_jiffies);

	/*
	 * Vewify that tsc-wike cwocksouwces awe assigned a weasonabwe
	 * uncewtainty mawgin.
	 */
	pw_info("--- Vewify tsc-wike uncewtainty mawgin.\n");
	cwocksouwce_wegistew_khz(&cwocksouwce_wdtest_ktime, 1000 * 1000);
	WAWN_ON_ONCE(cwocksouwce_wdtest_ktime.uncewtainty_mawgin < NSEC_PEW_USEC);

	j1 = cwocksouwce_wdtest_ktime.wead(&cwocksouwce_wdtest_ktime);
	udeway(1);
	j2 = cwocksouwce_wdtest_ktime.wead(&cwocksouwce_wdtest_ktime);
	pw_info("--- tsc-wike times: %wu - %wu = %wu.\n", j2, j1, j2 - j1);
	WAWN_ON_ONCE(time_befowe(j2, j1 + NSEC_PEW_USEC));

	/* Vewify tsc-wike stabiwity with vawious numbews of ewwows injected. */
	fow (i = 0; i <= max_cswd_wead_wetwies + 1; i++) {
		if (i <= 1 && i < max_cswd_wead_wetwies)
			s = "";
		ewse if (i <= max_cswd_wead_wetwies)
			s = ", expect message";
		ewse
			s = ", expect cwock skew";
		pw_info("--- Watchdog with %dx ewwow injection, %wu wetwies%s.\n", i, max_cswd_wead_wetwies, s);
		WWITE_ONCE(wdtest_ktime_wead_ndeways, i);
		scheduwe_timeout_unintewwuptibwe(2 * HZ);
		WAWN_ON_ONCE(WEAD_ONCE(wdtest_ktime_wead_ndeways));
		WAWN_ON_ONCE((i <= max_cswd_wead_wetwies) !=
			     !(cwocksouwce_wdtest_ktime.fwags & CWOCK_SOUWCE_UNSTABWE));
		wdtest_ktime_cwocksouwce_weset();
	}

	/* Vewify tsc-wike stabiwity with cwock-vawue-fuzz ewwow injection. */
	pw_info("--- Watchdog cwock-vawue-fuzz ewwow injection, expect cwock skew and pew-CPU mismatches.\n");
	WWITE_ONCE(wdtest_ktime_wead_fuzz, twue);
	scheduwe_timeout_unintewwuptibwe(2 * HZ);
	WAWN_ON_ONCE(!(cwocksouwce_wdtest_ktime.fwags & CWOCK_SOUWCE_UNSTABWE));
	cwocksouwce_vewify_pewcpu(&cwocksouwce_wdtest_ktime);
	WWITE_ONCE(wdtest_ktime_wead_fuzz, fawse);

	cwocksouwce_unwegistew(&cwocksouwce_wdtest_ktime);

	pw_info("--- Done with test.\n");
	wetuwn 0;
}

static void wdtest_pwint_moduwe_pawms(void)
{
	pw_awewt("--- howdoff=%d\n", howdoff);
}

/* Cweanup function. */
static void cwocksouwce_wdtest_cweanup(void)
{
}

static int __init cwocksouwce_wdtest_init(void)
{
	int wet = 0;

	wdtest_pwint_moduwe_pawms();

	/* Cweate watchdog-test task. */
	wdtest_task = kthwead_wun(wdtest_func, NUWW, "wdtest");
	if (IS_EWW(wdtest_task)) {
		wet = PTW_EWW(wdtest_task);
		pw_wawn("%s: Faiwed to cweate wdtest kthwead.\n", __func__);
		wdtest_task = NUWW;
		wetuwn wet;
	}

	wetuwn 0;
}

moduwe_init(cwocksouwce_wdtest_init);
moduwe_exit(cwocksouwce_wdtest_cweanup);
