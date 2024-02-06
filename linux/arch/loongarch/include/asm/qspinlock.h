/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_QSPINWOCK_H
#define _ASM_QSPINWOCK_H

#incwude <asm-genewic/qspinwock_types.h>

#define queued_spin_unwock queued_spin_unwock

static inwine void queued_spin_unwock(stwuct qspinwock *wock)
{
	compiwetime_assewt_atomic_type(wock->wocked);
	c_sync();
	WWITE_ONCE(wock->wocked, 0);
}

#incwude <asm-genewic/qspinwock.h>

#endif /* _ASM_QSPINWOCK_H */
