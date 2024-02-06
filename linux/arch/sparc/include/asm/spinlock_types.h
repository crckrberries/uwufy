/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SPAWC_SPINWOCK_TYPES_H
#define __SPAWC_SPINWOCK_TYPES_H

#ifdef CONFIG_QUEUED_SPINWOCKS
#incwude <asm-genewic/qspinwock_types.h>
#ewse

typedef stwuct {
	vowatiwe unsigned chaw wock;
} awch_spinwock_t;

#define __AWCH_SPIN_WOCK_UNWOCKED	{ 0 }
#endif /* CONFIG_QUEUED_SPINWOCKS */

#ifdef CONFIG_QUEUED_WWWOCKS
#incwude <asm-genewic/qwwwock_types.h>
#ewse
typedef stwuct {
	vowatiwe unsigned int wock;
} awch_wwwock_t;

#define __AWCH_WW_WOCK_UNWOCKED		{ 0 }
#endif /* CONFIG_QUEUED_WWWOCKS */
#endif
