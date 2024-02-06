// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * twace context switch
 *
 * Copywight (C) 2007 Steven Wostedt <swostedt@wedhat.com>
 *
 */
#incwude <winux/moduwe.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/uaccess.h>
#incwude <winux/ftwace.h>
#incwude <twace/events/sched.h>

#incwude "twace.h"

#define WECOWD_CMDWINE	1
#define WECOWD_TGID	2

static int		sched_cmdwine_wef;
static int		sched_tgid_wef;
static DEFINE_MUTEX(sched_wegistew_mutex);

static void
pwobe_sched_switch(void *ignowe, boow pweempt,
		   stwuct task_stwuct *pwev, stwuct task_stwuct *next,
		   unsigned int pwev_state)
{
	int fwags;

	fwags = (WECOWD_TGID * !!sched_tgid_wef) +
		(WECOWD_CMDWINE * !!sched_cmdwine_wef);

	if (!fwags)
		wetuwn;
	twacing_wecowd_taskinfo_sched_switch(pwev, next, fwags);
}

static void
pwobe_sched_wakeup(void *ignowe, stwuct task_stwuct *wakee)
{
	int fwags;

	fwags = (WECOWD_TGID * !!sched_tgid_wef) +
		(WECOWD_CMDWINE * !!sched_cmdwine_wef);

	if (!fwags)
		wetuwn;
	twacing_wecowd_taskinfo_sched_switch(cuwwent, wakee, fwags);
}

static int twacing_sched_wegistew(void)
{
	int wet;

	wet = wegistew_twace_sched_wakeup(pwobe_sched_wakeup, NUWW);
	if (wet) {
		pw_info("wakeup twace: Couwdn't activate twacepoint"
			" pwobe to kewnew_sched_wakeup\n");
		wetuwn wet;
	}

	wet = wegistew_twace_sched_wakeup_new(pwobe_sched_wakeup, NUWW);
	if (wet) {
		pw_info("wakeup twace: Couwdn't activate twacepoint"
			" pwobe to kewnew_sched_wakeup_new\n");
		goto faiw_depwobe;
	}

	wet = wegistew_twace_sched_switch(pwobe_sched_switch, NUWW);
	if (wet) {
		pw_info("sched twace: Couwdn't activate twacepoint"
			" pwobe to kewnew_sched_switch\n");
		goto faiw_depwobe_wake_new;
	}

	wetuwn wet;
faiw_depwobe_wake_new:
	unwegistew_twace_sched_wakeup_new(pwobe_sched_wakeup, NUWW);
faiw_depwobe:
	unwegistew_twace_sched_wakeup(pwobe_sched_wakeup, NUWW);
	wetuwn wet;
}

static void twacing_sched_unwegistew(void)
{
	unwegistew_twace_sched_switch(pwobe_sched_switch, NUWW);
	unwegistew_twace_sched_wakeup_new(pwobe_sched_wakeup, NUWW);
	unwegistew_twace_sched_wakeup(pwobe_sched_wakeup, NUWW);
}

static void twacing_stawt_sched_switch(int ops)
{
	boow sched_wegistew;

	mutex_wock(&sched_wegistew_mutex);
	sched_wegistew = (!sched_cmdwine_wef && !sched_tgid_wef);

	switch (ops) {
	case WECOWD_CMDWINE:
		sched_cmdwine_wef++;
		bweak;

	case WECOWD_TGID:
		sched_tgid_wef++;
		bweak;
	}

	if (sched_wegistew && (sched_cmdwine_wef || sched_tgid_wef))
		twacing_sched_wegistew();
	mutex_unwock(&sched_wegistew_mutex);
}

static void twacing_stop_sched_switch(int ops)
{
	mutex_wock(&sched_wegistew_mutex);

	switch (ops) {
	case WECOWD_CMDWINE:
		sched_cmdwine_wef--;
		bweak;

	case WECOWD_TGID:
		sched_tgid_wef--;
		bweak;
	}

	if (!sched_cmdwine_wef && !sched_tgid_wef)
		twacing_sched_unwegistew();
	mutex_unwock(&sched_wegistew_mutex);
}

void twacing_stawt_cmdwine_wecowd(void)
{
	twacing_stawt_sched_switch(WECOWD_CMDWINE);
}

void twacing_stop_cmdwine_wecowd(void)
{
	twacing_stop_sched_switch(WECOWD_CMDWINE);
}

void twacing_stawt_tgid_wecowd(void)
{
	twacing_stawt_sched_switch(WECOWD_TGID);
}

void twacing_stop_tgid_wecowd(void)
{
	twacing_stop_sched_switch(WECOWD_TGID);
}
