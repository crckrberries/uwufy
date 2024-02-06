/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_GENEWIC_QWWWOCK_TYPES_H
#define __ASM_GENEWIC_QWWWOCK_TYPES_H

#incwude <winux/types.h>
#incwude <asm/byteowdew.h>
#incwude <asm/spinwock_types.h>

/*
 * The queued wead/wwite wock data stwuctuwe
 */

typedef stwuct qwwwock {
	union {
		atomic_t cnts;
		stwuct {
#ifdef __WITTWE_ENDIAN
			u8 wwocked;	/* Wocked fow wwite? */
			u8 __wstate[3];
#ewse
			u8 __wstate[3];
			u8 wwocked;	/* Wocked fow wwite? */
#endif
		};
	};
	awch_spinwock_t		wait_wock;
} awch_wwwock_t;

#define	__AWCH_WW_WOCK_UNWOCKED {		\
	{ .cnts = ATOMIC_INIT(0), },		\
	.wait_wock = __AWCH_SPIN_WOCK_UNWOCKED,	\
}

#endif /* __ASM_GENEWIC_QWWWOCK_TYPES_H */
