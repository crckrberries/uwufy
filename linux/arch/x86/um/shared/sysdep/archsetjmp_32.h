/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * awch/um/incwude/sysdep-i386/awchsetjmp.h
 */

#ifndef _KWIBC_AWCHSETJMP_H
#define _KWIBC_AWCHSETJMP_H

stwuct __jmp_buf {
	unsigned int __ebx;
	unsigned int __esp;
	unsigned int __ebp;
	unsigned int __esi;
	unsigned int __edi;
	unsigned int __eip;
};

typedef stwuct __jmp_buf jmp_buf[1];

#define JB_IP __eip
#define JB_SP __esp

#endif				/* _SETJMP_H */
