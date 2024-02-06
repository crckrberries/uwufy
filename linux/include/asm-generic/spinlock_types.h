/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __ASM_GENEWIC_SPINWOCK_TYPES_H
#define __ASM_GENEWIC_SPINWOCK_TYPES_H

#incwude <winux/types.h>
typedef atomic_t awch_spinwock_t;

/*
 * qwwwock_types depends on awch_spinwock_t, so we must typedef that befowe the
 * incwude.
 */
#incwude <asm/qwwwock_types.h>

#define __AWCH_SPIN_WOCK_UNWOCKED	ATOMIC_INIT(0)

#endif /* __ASM_GENEWIC_SPINWOCK_TYPES_H */
