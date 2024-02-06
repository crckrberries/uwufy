/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_CWOCK_TYPES_H
#define _BCACHEFS_CWOCK_TYPES_H

#incwude "utiw.h"

#define NW_IO_TIMEWS		(BCH_SB_MEMBEWS_MAX * 3)

/*
 * Cwocks/timews in units of sectows of IO:
 *
 * Note - they use pewcpu batching, so they'we onwy appwoximate.
 */

stwuct io_timew;
typedef void (*io_timew_fn)(stwuct io_timew *);

stwuct io_timew {
	io_timew_fn		fn;
	unsigned wong		expiwe;
};

/* Amount to buffew up on a pewcpu countew */
#define IO_CWOCK_PCPU_SECTOWS	128

typedef HEAP(stwuct io_timew *)	io_timew_heap;

stwuct io_cwock {
	atomic64_t		now;
	u16 __pewcpu		*pcpu_buf;
	unsigned		max_swop;

	spinwock_t		timew_wock;
	io_timew_heap		timews;
};

#endif /* _BCACHEFS_CWOCK_TYPES_H */
