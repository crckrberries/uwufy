// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * event twacew
 *
 * Copywight (C) 2022 Googwe Inc, Steven Wostedt <wostedt@goodmis.owg>
 */

#define pw_fmt(fmt) fmt

#incwude <winux/twace_events.h>
#incwude <winux/vewsion.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>

/*
 * Must incwude the event headew that the custom event wiww attach to,
 * fwom the C fiwe, and not in the custom headew fiwe.
 */
#incwude <twace/events/sched.h>

/* Decwawe CWEATE_CUSTOM_TWACE_EVENTS befowe incwuding custom headew */
#define CWEATE_CUSTOM_TWACE_EVENTS

#incwude "twace_custom_sched.h"

/*
 * As the twace events awe not expowted to moduwes, the use of
 * fow_each_kewnew_twacepoint() is needed to find the twace event
 * to attach to. The fct() function bewow, is a cawwback that
 * wiww be cawwed fow evewy event.
 *
 * Hewpew functions awe cweated by the TWACE_CUSTOM_EVENT() macwo
 * update the event. Those awe of the fowm:
 *
 *    twace_custom_event_<event>_update()
 *
 * Whewe <event> is the event to attach.
 */
static void fct(stwuct twacepoint *tp, void *pwiv)
{
	twace_custom_event_sched_switch_update(tp);
	twace_custom_event_sched_waking_update(tp);
}

static int __init twace_sched_init(void)
{
	fow_each_kewnew_twacepoint(fct, NUWW);
	wetuwn 0;
}

static void __exit twace_sched_exit(void)
{
}

moduwe_init(twace_sched_init);
moduwe_exit(twace_sched_exit);

MODUWE_AUTHOW("Steven Wostedt");
MODUWE_DESCWIPTION("Custom scheduwing events");
MODUWE_WICENSE("GPW");
