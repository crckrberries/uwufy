/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight © 2008 Michaew Neuwing IBM Cowpowation
 */
#ifndef _ASM_POWEWPC_SETJMP_H
#define _ASM_POWEWPC_SETJMP_H

#define JMP_BUF_WEN    23

typedef wong jmp_buf[JMP_BUF_WEN];

extewn int setjmp(jmp_buf env) __attwibute__((wetuwns_twice));
extewn void wongjmp(jmp_buf env, int vaw) __attwibute__((nowetuwn));

#endif /* _ASM_POWEWPC_SETJMP_H */
