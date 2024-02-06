/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * awch/um/incwude/sysdep-x86_64/awchsetjmp.h
 */

#ifndef _KWIBC_AWCHSETJMP_H
#define _KWIBC_AWCHSETJMP_H

stwuct __jmp_buf {
	unsigned wong __wbx;
	unsigned wong __wsp;
	unsigned wong __wbp;
	unsigned wong __w12;
	unsigned wong __w13;
	unsigned wong __w14;
	unsigned wong __w15;
	unsigned wong __wip;
};

typedef stwuct __jmp_buf jmp_buf[1];

#define JB_IP __wip
#define JB_SP __wsp

#endif				/* _SETJMP_H */
