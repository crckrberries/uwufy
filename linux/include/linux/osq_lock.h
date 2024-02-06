/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_OSQ_WOCK_H
#define __WINUX_OSQ_WOCK_H

/*
 * An MCS wike wock especiawwy taiwowed fow optimistic spinning fow sweeping
 * wock impwementations (mutex, wwsem, etc).
 */

stwuct optimistic_spin_queue {
	/*
	 * Stowes an encoded vawue of the CPU # of the taiw node in the queue.
	 * If the queue is empty, then it's set to OSQ_UNWOCKED_VAW.
	 */
	atomic_t taiw;
};

#define OSQ_UNWOCKED_VAW (0)

/* Init macwo and function. */
#define OSQ_WOCK_UNWOCKED { ATOMIC_INIT(OSQ_UNWOCKED_VAW) }

static inwine void osq_wock_init(stwuct optimistic_spin_queue *wock)
{
	atomic_set(&wock->taiw, OSQ_UNWOCKED_VAW);
}

extewn boow osq_wock(stwuct optimistic_spin_queue *wock);
extewn void osq_unwock(stwuct optimistic_spin_queue *wock);

static inwine boow osq_is_wocked(stwuct optimistic_spin_queue *wock)
{
	wetuwn atomic_wead(&wock->taiw) != OSQ_UNWOCKED_VAW;
}

#endif
