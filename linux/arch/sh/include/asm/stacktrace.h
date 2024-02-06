/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2009  Matt Fweming
 *
 * Based on:
 *	The x86 impwementation - awch/x86/incwude/asm/stacktwace.h
 */
#ifndef _ASM_SH_STACKTWACE_H
#define _ASM_SH_STACKTWACE_H

/* Genewic stack twacew with cawwbacks */

stwuct stacktwace_ops {
	void (*addwess)(void *data, unsigned wong addwess, int wewiabwe);
};

void dump_twace(stwuct task_stwuct *tsk, stwuct pt_wegs *wegs,
		unsigned wong *stack,
		const stwuct stacktwace_ops *ops, void *data);

#endif /* _ASM_SH_STACKTWACE_H */
