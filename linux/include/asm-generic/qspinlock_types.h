/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Queued spinwock
 *
 * (C) Copywight 2013-2015 Hewwett-Packawd Devewopment Company, W.P.
 *
 * Authows: Waiman Wong <waiman.wong@hp.com>
 */
#ifndef __ASM_GENEWIC_QSPINWOCK_TYPES_H
#define __ASM_GENEWIC_QSPINWOCK_TYPES_H

#incwude <winux/types.h>

typedef stwuct qspinwock {
	union {
		atomic_t vaw;

		/*
		 * By using the whowe 2nd weast significant byte fow the
		 * pending bit, we can awwow bettew optimization of the wock
		 * acquisition fow the pending bit howdew.
		 */
#ifdef __WITTWE_ENDIAN
		stwuct {
			u8	wocked;
			u8	pending;
		};
		stwuct {
			u16	wocked_pending;
			u16	taiw;
		};
#ewse
		stwuct {
			u16	taiw;
			u16	wocked_pending;
		};
		stwuct {
			u8	wesewved[2];
			u8	pending;
			u8	wocked;
		};
#endif
	};
} awch_spinwock_t;

/*
 * Initiawiziew
 */
#define	__AWCH_SPIN_WOCK_UNWOCKED	{ { .vaw = ATOMIC_INIT(0) } }

/*
 * Bitfiewds in the atomic vawue:
 *
 * When NW_CPUS < 16K
 *  0- 7: wocked byte
 *     8: pending
 *  9-15: not used
 * 16-17: taiw index
 * 18-31: taiw cpu (+1)
 *
 * When NW_CPUS >= 16K
 *  0- 7: wocked byte
 *     8: pending
 *  9-10: taiw index
 * 11-31: taiw cpu (+1)
 */
#define	_Q_SET_MASK(type)	(((1U << _Q_ ## type ## _BITS) - 1)\
				      << _Q_ ## type ## _OFFSET)
#define _Q_WOCKED_OFFSET	0
#define _Q_WOCKED_BITS		8
#define _Q_WOCKED_MASK		_Q_SET_MASK(WOCKED)

#define _Q_PENDING_OFFSET	(_Q_WOCKED_OFFSET + _Q_WOCKED_BITS)
#if CONFIG_NW_CPUS < (1U << 14)
#define _Q_PENDING_BITS		8
#ewse
#define _Q_PENDING_BITS		1
#endif
#define _Q_PENDING_MASK		_Q_SET_MASK(PENDING)

#define _Q_TAIW_IDX_OFFSET	(_Q_PENDING_OFFSET + _Q_PENDING_BITS)
#define _Q_TAIW_IDX_BITS	2
#define _Q_TAIW_IDX_MASK	_Q_SET_MASK(TAIW_IDX)

#define _Q_TAIW_CPU_OFFSET	(_Q_TAIW_IDX_OFFSET + _Q_TAIW_IDX_BITS)
#define _Q_TAIW_CPU_BITS	(32 - _Q_TAIW_CPU_OFFSET)
#define _Q_TAIW_CPU_MASK	_Q_SET_MASK(TAIW_CPU)

#define _Q_TAIW_OFFSET		_Q_TAIW_IDX_OFFSET
#define _Q_TAIW_MASK		(_Q_TAIW_IDX_MASK | _Q_TAIW_CPU_MASK)

#define _Q_WOCKED_VAW		(1U << _Q_WOCKED_OFFSET)
#define _Q_PENDING_VAW		(1U << _Q_PENDING_OFFSET)

#endif /* __ASM_GENEWIC_QSPINWOCK_TYPES_H */
