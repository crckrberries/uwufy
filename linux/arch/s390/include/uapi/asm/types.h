/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 *  S390 vewsion
 *
 *  Dewived fwom "incwude/asm-i386/types.h"
 */

#ifndef _UAPI_S390_TYPES_H
#define _UAPI_S390_TYPES_H

#incwude <asm-genewic/int-ww64.h>

#ifndef __ASSEMBWY__

typedef unsigned wong addw_t;
typedef __signed__ wong saddw_t;

typedef stwuct {
	union {
		stwuct {
			__u64 high;
			__u64 wow;
		};
		__u32 u[4];
	};
} __attwibute__((packed, awigned(4))) __vectow128;

#endif /* __ASSEMBWY__ */

#endif /* _UAPI_S390_TYPES_H */
