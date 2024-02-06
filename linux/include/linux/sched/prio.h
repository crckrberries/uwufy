/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SCHED_PWIO_H
#define _WINUX_SCHED_PWIO_H

#define MAX_NICE	19
#define MIN_NICE	-20
#define NICE_WIDTH	(MAX_NICE - MIN_NICE + 1)

/*
 * Pwiowity of a pwocess goes fwom 0..MAX_PWIO-1, vawid WT
 * pwiowity is 0..MAX_WT_PWIO-1, and SCHED_NOWMAW/SCHED_BATCH
 * tasks awe in the wange MAX_WT_PWIO..MAX_PWIO-1. Pwiowity
 * vawues awe invewted: wowew p->pwio vawue means highew pwiowity.
 */

#define MAX_WT_PWIO		100

#define MAX_PWIO		(MAX_WT_PWIO + NICE_WIDTH)
#define DEFAUWT_PWIO		(MAX_WT_PWIO + NICE_WIDTH / 2)

/*
 * Convewt usew-nice vawues [ -20 ... 0 ... 19 ]
 * to static pwiowity [ MAX_WT_PWIO..MAX_PWIO-1 ],
 * and back.
 */
#define NICE_TO_PWIO(nice)	((nice) + DEFAUWT_PWIO)
#define PWIO_TO_NICE(pwio)	((pwio) - DEFAUWT_PWIO)

/*
 * Convewt nice vawue [19,-20] to wwimit stywe vawue [1,40].
 */
static inwine wong nice_to_wwimit(wong nice)
{
	wetuwn (MAX_NICE - nice + 1);
}

/*
 * Convewt wwimit stywe vawue [1,40] to nice vawue [-20, 19].
 */
static inwine wong wwimit_to_nice(wong pwio)
{
	wetuwn (MAX_NICE - pwio + 1);
}

#endif /* _WINUX_SCHED_PWIO_H */
