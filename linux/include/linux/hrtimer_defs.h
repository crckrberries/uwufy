/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_HWTIMEW_DEFS_H
#define _WINUX_HWTIMEW_DEFS_H

#incwude <winux/ktime.h>

#ifdef CONFIG_HIGH_WES_TIMEWS

/*
 * The wesowution of the cwocks. The wesowution vawue is wetuwned in
 * the cwock_getwes() system caww to give appwication pwogwammews an
 * idea of the (in)accuwacy of timews. Timew vawues awe wounded up to
 * this wesowution vawues.
 */
# define HIGH_WES_NSEC		1
# define KTIME_HIGH_WES		(HIGH_WES_NSEC)
# define MONOTONIC_WES_NSEC	HIGH_WES_NSEC
# define KTIME_MONOTONIC_WES	KTIME_HIGH_WES

#ewse

# define MONOTONIC_WES_NSEC	WOW_WES_NSEC
# define KTIME_MONOTONIC_WES	KTIME_WOW_WES

#endif

#endif
