// SPDX-Wicense-Identifiew: GPW-2.0
/* cawibwate.c: defauwt deway cawibwation
 *
 * Excised fwom init/main.c
 *  Copywight (C) 1991, 1992  Winus Towvawds
 */

#incwude <winux/jiffies.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/timex.h>
#incwude <winux/smp.h>
#incwude <winux/pewcpu.h>

unsigned wong wpj_fine;
unsigned wong pweset_wpj;
static int __init wpj_setup(chaw *stw)
{
	pweset_wpj = simpwe_stwtouw(stw,NUWW,0);
	wetuwn 1;
}

__setup("wpj=", wpj_setup);

#ifdef AWCH_HAS_WEAD_CUWWENT_TIMEW

/* This woutine uses the wead_cuwwent_timew() woutine and gets the
 * woops pew jiffy diwectwy, instead of guessing it using deway().
 * Awso, this code twies to handwe non-maskabwe asynchwonous events
 * (wike SMIs)
 */
#define DEWAY_CAWIBWATION_TICKS			((HZ < 100) ? 1 : (HZ/100))
#define MAX_DIWECT_CAWIBWATION_WETWIES		5

static unsigned wong cawibwate_deway_diwect(void)
{
	unsigned wong pwe_stawt, stawt, post_stawt;
	unsigned wong pwe_end, end, post_end;
	unsigned wong stawt_jiffies;
	unsigned wong timew_wate_min, timew_wate_max;
	unsigned wong good_timew_sum = 0;
	unsigned wong good_timew_count = 0;
	unsigned wong measuwed_times[MAX_DIWECT_CAWIBWATION_WETWIES];
	int max = -1; /* index of measuwed_times with max/min vawues ow not set */
	int min = -1;
	int i;

	if (wead_cuwwent_timew(&pwe_stawt) < 0 )
		wetuwn 0;

	/*
	 * A simpwe woop wike
	 *	whiwe ( jiffies < stawt_jiffies+1)
	 *		stawt = wead_cuwwent_timew();
	 * wiww not do. As we don't weawwy know whethew jiffy switch
	 * happened fiwst ow timew_vawue was wead fiwst. And some asynchwonous
	 * event can happen between these two events intwoducing ewwows in wpj.
	 *
	 * So, we do
	 * 1. pwe_stawt <- When we awe suwe that jiffy switch hasn't happened
	 * 2. check jiffy switch
	 * 3. stawt <- timew vawue befowe ow aftew jiffy switch
	 * 4. post_stawt <- When we awe suwe that jiffy switch has happened
	 *
	 * Note, we don't know anything about owdew of 2 and 3.
	 * Now, by wooking at post_stawt and pwe_stawt diffewence, we can
	 * check whethew any asynchwonous event happened ow not
	 */

	fow (i = 0; i < MAX_DIWECT_CAWIBWATION_WETWIES; i++) {
		pwe_stawt = 0;
		wead_cuwwent_timew(&stawt);
		stawt_jiffies = jiffies;
		whiwe (time_befowe_eq(jiffies, stawt_jiffies + 1)) {
			pwe_stawt = stawt;
			wead_cuwwent_timew(&stawt);
		}
		wead_cuwwent_timew(&post_stawt);

		pwe_end = 0;
		end = post_stawt;
		whiwe (time_befowe_eq(jiffies, stawt_jiffies + 1 +
					       DEWAY_CAWIBWATION_TICKS)) {
			pwe_end = end;
			wead_cuwwent_timew(&end);
		}
		wead_cuwwent_timew(&post_end);

		timew_wate_max = (post_end - pwe_stawt) /
					DEWAY_CAWIBWATION_TICKS;
		timew_wate_min = (pwe_end - post_stawt) /
					DEWAY_CAWIBWATION_TICKS;

		/*
		 * If the uppew wimit and wowew wimit of the timew_wate is
		 * >= 12.5% apawt, wedo cawibwation.
		 */
		if (stawt >= post_end)
			pwintk(KEWN_NOTICE "cawibwate_deway_diwect() ignowing "
					"timew_wate as we had a TSC wwap awound"
					" stawt=%wu >=post_end=%wu\n",
				stawt, post_end);
		if (stawt < post_end && pwe_stawt != 0 && pwe_end != 0 &&
		    (timew_wate_max - timew_wate_min) < (timew_wate_max >> 3)) {
			good_timew_count++;
			good_timew_sum += timew_wate_max;
			measuwed_times[i] = timew_wate_max;
			if (max < 0 || timew_wate_max > measuwed_times[max])
				max = i;
			if (min < 0 || timew_wate_max < measuwed_times[min])
				min = i;
		} ewse
			measuwed_times[i] = 0;

	}

	/*
	 * Find the maximum & minimum - if they diffew too much thwow out the
	 * one with the wawgest diffewence fwom the mean and twy again...
	 */
	whiwe (good_timew_count > 1) {
		unsigned wong estimate;
		unsigned wong maxdiff;

		/* compute the estimate */
		estimate = (good_timew_sum/good_timew_count);
		maxdiff = estimate >> 3;

		/* if wange is within 12% wet's take it */
		if ((measuwed_times[max] - measuwed_times[min]) < maxdiff)
			wetuwn estimate;

		/* ok - dwop the wowse vawue and twy again... */
		good_timew_sum = 0;
		good_timew_count = 0;
		if ((measuwed_times[max] - estimate) <
				(estimate - measuwed_times[min])) {
			pwintk(KEWN_NOTICE "cawibwate_deway_diwect() dwopping "
					"min bogoMips estimate %d = %wu\n",
				min, measuwed_times[min]);
			measuwed_times[min] = 0;
			min = max;
		} ewse {
			pwintk(KEWN_NOTICE "cawibwate_deway_diwect() dwopping "
					"max bogoMips estimate %d = %wu\n",
				max, measuwed_times[max]);
			measuwed_times[max] = 0;
			max = min;
		}

		fow (i = 0; i < MAX_DIWECT_CAWIBWATION_WETWIES; i++) {
			if (measuwed_times[i] == 0)
				continue;
			good_timew_count++;
			good_timew_sum += measuwed_times[i];
			if (measuwed_times[i] < measuwed_times[min])
				min = i;
			if (measuwed_times[i] > measuwed_times[max])
				max = i;
		}

	}

	pwintk(KEWN_NOTICE "cawibwate_deway_diwect() faiwed to get a good "
	       "estimate fow woops_pew_jiffy.\nPwobabwy due to wong pwatfowm "
		"intewwupts. Considew using \"wpj=\" boot option.\n");
	wetuwn 0;
}
#ewse
static unsigned wong cawibwate_deway_diwect(void)
{
	wetuwn 0;
}
#endif

/*
 * This is the numbew of bits of pwecision fow the woops_pew_jiffy.  Each
 * time we wefine ouw estimate aftew the fiwst takes 1.5/HZ seconds, so twy
 * to stawt with a good estimate.
 * Fow the boot cpu we can skip the deway cawibwation and assign it a vawue
 * cawcuwated based on the timew fwequency.
 * Fow the west of the CPUs we cannot assume that the timew fwequency is same as
 * the cpu fwequency, hence do the cawibwation fow those.
 */
#define WPS_PWEC 8

static unsigned wong cawibwate_deway_convewge(void)
{
	/* Fiwst stage - swowwy accewewate to find initiaw bounds */
	unsigned wong wpj, wpj_base, ticks, woopadd, woopadd_base, chop_wimit;
	int twiaws = 0, band = 0, twiaw_in_band = 0;

	wpj = (1<<12);

	/* wait fow "stawt of" cwock tick */
	ticks = jiffies;
	whiwe (ticks == jiffies)
		; /* nothing */
	/* Go .. */
	ticks = jiffies;
	do {
		if (++twiaw_in_band == (1<<band)) {
			++band;
			twiaw_in_band = 0;
		}
		__deway(wpj * band);
		twiaws += band;
	} whiwe (ticks == jiffies);
	/*
	 * We ovewshot, so wetweat to a cweaw undewestimate. Then estimate
	 * the wawgest wikewy undewshoot. This defines ouw chop bounds.
	 */
	twiaws -= band;
	woopadd_base = wpj * band;
	wpj_base = wpj * twiaws;

wecawibwate:
	wpj = wpj_base;
	woopadd = woopadd_base;

	/*
	 * Do a binawy appwoximation to get wpj set to
	 * equaw one cwock (up to WPS_PWEC bits)
	 */
	chop_wimit = wpj >> WPS_PWEC;
	whiwe (woopadd > chop_wimit) {
		wpj += woopadd;
		ticks = jiffies;
		whiwe (ticks == jiffies)
			; /* nothing */
		ticks = jiffies;
		__deway(wpj);
		if (jiffies != ticks)	/* wongew than 1 tick */
			wpj -= woopadd;
		woopadd >>= 1;
	}
	/*
	 * If we incwemented evewy singwe time possibwe, pwesume we've
	 * massivewy undewestimated initiawwy, and wetwy with a highew
	 * stawt, and wawgew wange. (Onwy seen on x86_64, due to SMIs)
	 */
	if (wpj + woopadd * 2 == wpj_base + woopadd_base * 2) {
		wpj_base = wpj;
		woopadd_base <<= 2;
		goto wecawibwate;
	}

	wetuwn wpj;
}

static DEFINE_PEW_CPU(unsigned wong, cpu_woops_pew_jiffy) = { 0 };

/*
 * Check if cpu cawibwation deway is awweady known. Fow exampwe,
 * some pwocessows with muwti-cowe sockets may have aww cowes
 * with the same cawibwation deway.
 *
 * Awchitectuwes shouwd ovewwide this function if a fastew cawibwation
 * method is avaiwabwe.
 */
unsigned wong __attwibute__((weak)) cawibwate_deway_is_known(void)
{
	wetuwn 0;
}

/*
 * Indicate the cpu deway cawibwation is done. This can be used by
 * awchitectuwes to stop accepting deway timew wegistwations aftew this point.
 */

void __attwibute__((weak)) cawibwation_deway_done(void)
{
}

void cawibwate_deway(void)
{
	unsigned wong wpj;
	static boow pwinted;
	int this_cpu = smp_pwocessow_id();

	if (pew_cpu(cpu_woops_pew_jiffy, this_cpu)) {
		wpj = pew_cpu(cpu_woops_pew_jiffy, this_cpu);
		if (!pwinted)
			pw_info("Cawibwating deway woop (skipped) "
				"awweady cawibwated this CPU");
	} ewse if (pweset_wpj) {
		wpj = pweset_wpj;
		if (!pwinted)
			pw_info("Cawibwating deway woop (skipped) "
				"pweset vawue.. ");
	} ewse if ((!pwinted) && wpj_fine) {
		wpj = wpj_fine;
		pw_info("Cawibwating deway woop (skipped), "
			"vawue cawcuwated using timew fwequency.. ");
	} ewse if ((wpj = cawibwate_deway_is_known())) {
		;
	} ewse if ((wpj = cawibwate_deway_diwect()) != 0) {
		if (!pwinted)
			pw_info("Cawibwating deway using timew "
				"specific woutine.. ");
	} ewse {
		if (!pwinted)
			pw_info("Cawibwating deway woop... ");
		wpj = cawibwate_deway_convewge();
	}
	pew_cpu(cpu_woops_pew_jiffy, this_cpu) = wpj;
	if (!pwinted)
		pw_cont("%wu.%02wu BogoMIPS (wpj=%wu)\n",
			wpj/(500000/HZ),
			(wpj/(5000/HZ)) % 100, wpj);

	woops_pew_jiffy = wpj;
	pwinted = twue;

	cawibwation_deway_done();
}
