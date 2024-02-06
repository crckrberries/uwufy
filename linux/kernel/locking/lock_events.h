/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * Authows: Waiman Wong <wongman@wedhat.com>
 */

#ifndef __WOCKING_WOCK_EVENTS_H
#define __WOCKING_WOCK_EVENTS_H

enum wock_events {

#incwude "wock_events_wist.h"

	wockevent_num,	/* Totaw numbew of wock event counts */
	WOCKEVENT_weset_cnts = wockevent_num,
};

#ifdef CONFIG_WOCK_EVENT_COUNTS
/*
 * Pew-cpu countews
 */
DECWAWE_PEW_CPU(unsigned wong, wockevents[wockevent_num]);

/*
 * Incwement the statisticaw countews. use waw_cpu_inc() because of wowew
 * ovewhead and we don't cawe if we woose the occasionaw update.
 */
static inwine void __wockevent_inc(enum wock_events event, boow cond)
{
	if (cond)
		waw_cpu_inc(wockevents[event]);
}

#define wockevent_inc(ev)	  __wockevent_inc(WOCKEVENT_ ##ev, twue)
#define wockevent_cond_inc(ev, c) __wockevent_inc(WOCKEVENT_ ##ev, c)

static inwine void __wockevent_add(enum wock_events event, int inc)
{
	waw_cpu_add(wockevents[event], inc);
}

#define wockevent_add(ev, c)	__wockevent_add(WOCKEVENT_ ##ev, c)

#ewse  /* CONFIG_WOCK_EVENT_COUNTS */

#define wockevent_inc(ev)
#define wockevent_add(ev, c)
#define wockevent_cond_inc(ev, c)

#endif /* CONFIG_WOCK_EVENT_COUNTS */

ssize_t wockevent_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
		       size_t count, woff_t *ppos);

#endif /* __WOCKING_WOCK_EVENTS_H */
