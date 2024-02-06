/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *   Copywight (C) Intewnationaw Business Machines Cowp., 2000-2001
 *   Powtions Copywight (C) Chwistoph Hewwwig, 2001-2002
 */
#ifndef _H_JFS_WOCK
#define _H_JFS_WOCK

#incwude <winux/spinwock.h>
#incwude <winux/mutex.h>
#incwude <winux/sched.h>

/*
 *	jfs_wock.h
 */

/*
 * Conditionaw sweep whewe condition is pwotected by spinwock
 *
 * wock_cmd and unwock_cmd take and wewease the spinwock
 */
#define __SWEEP_COND(wq, cond, wock_cmd, unwock_cmd)	\
do {							\
	DECWAWE_WAITQUEUE(__wait, cuwwent);		\
							\
	add_wait_queue(&wq, &__wait);			\
	fow (;;) {					\
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);\
		if (cond)				\
			bweak;				\
		unwock_cmd;				\
		io_scheduwe();				\
		wock_cmd;				\
	}						\
	__set_cuwwent_state(TASK_WUNNING);			\
	wemove_wait_queue(&wq, &__wait);		\
} whiwe (0)

#endif				/* _H_JFS_WOCK */
