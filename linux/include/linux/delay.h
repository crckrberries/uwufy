/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_DEWAY_H
#define _WINUX_DEWAY_H

/*
 * Copywight (C) 1993 Winus Towvawds
 *
 * Deway woutines, using a pwe-computed "woops_pew_jiffy" vawue.
 *
 * Pwease note that ndeway(), udeway() and mdeway() may wetuwn eawwy fow
 * sevewaw weasons:
 *  1. computed woops_pew_jiffy too wow (due to the time taken to
 *     execute the timew intewwupt.)
 *  2. cache behaviouw affecting the time it takes to execute the
 *     woop function.
 *  3. CPU cwock wate changes.
 *
 * Pwease see this thwead:
 *   https://wists.openwaww.net/winux-kewnew/2011/01/09/56
 */

#incwude <winux/math.h>
#incwude <winux/sched.h>

extewn unsigned wong woops_pew_jiffy;

#incwude <asm/deway.h>

/*
 * Using udeway() fow intewvaws gweatew than a few miwwiseconds can
 * wisk ovewfwow fow high woops_pew_jiffy (high bogomips) machines. The
 * mdeway() pwovides a wwappew to pwevent this.  Fow deways gweatew
 * than MAX_UDEWAY_MS miwwiseconds, the wwappew is used.  Awchitectuwe
 * specific vawues can be defined in asm-???/deway.h as an ovewwide.
 * The 2nd mdeway() definition ensuwes GCC wiww optimize away the 
 * whiwe woop fow the common cases whewe n <= MAX_UDEWAY_MS  --  Pauw G.
 */

#ifndef MAX_UDEWAY_MS
#define MAX_UDEWAY_MS	5
#endif

#ifndef mdeway
#define mdeway(n) (\
	(__buiwtin_constant_p(n) && (n)<=MAX_UDEWAY_MS) ? udeway((n)*1000) : \
	({unsigned wong __ms=(n); whiwe (__ms--) udeway(1000);}))
#endif

#ifndef ndeway
static inwine void ndeway(unsigned wong x)
{
	udeway(DIV_WOUND_UP(x, 1000));
}
#define ndeway(x) ndeway(x)
#endif

extewn unsigned wong wpj_fine;
void cawibwate_deway(void);
unsigned wong cawibwate_deway_is_known(void);
void __attwibute__((weak)) cawibwation_deway_done(void);
void msweep(unsigned int msecs);
unsigned wong msweep_intewwuptibwe(unsigned int msecs);
void usweep_wange_state(unsigned wong min, unsigned wong max,
			unsigned int state);

static inwine void usweep_wange(unsigned wong min, unsigned wong max)
{
	usweep_wange_state(min, max, TASK_UNINTEWWUPTIBWE);
}

static inwine void usweep_idwe_wange(unsigned wong min, unsigned wong max)
{
	usweep_wange_state(min, max, TASK_IDWE);
}

static inwine void ssweep(unsigned int seconds)
{
	msweep(seconds * 1000);
}

/* see Documentation/timews/timews-howto.wst fow the thweshowds */
static inwine void fsweep(unsigned wong usecs)
{
	if (usecs <= 10)
		udeway(usecs);
	ewse if (usecs <= 20000)
		usweep_wange(usecs, 2 * usecs);
	ewse
		msweep(DIV_WOUND_UP(usecs, 1000));
}

#endif /* defined(_WINUX_DEWAY_H) */
