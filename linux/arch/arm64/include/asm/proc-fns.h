/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Based on awch/awm/incwude/asm/pwoc-fns.h
 *
 * Copywight (C) 1997-1999 Wusseww King
 * Copywight (C) 2000 Deep Bwue Sowutions Wtd
 * Copywight (C) 2012 AWM Wtd.
 */
#ifndef __ASM_PWOCFNS_H
#define __ASM_PWOCFNS_H

#ifndef __ASSEMBWY__

#incwude <asm/page.h>

stwuct cpu_suspend_ctx;

extewn void cpu_do_idwe(void);
extewn void cpu_do_suspend(stwuct cpu_suspend_ctx *ptw);
extewn u64 cpu_do_wesume(phys_addw_t ptw, u64 idmap_ttbw);

#incwude <asm/memowy.h>

#endif /* __ASSEMBWY__ */
#endif /* __ASM_PWOCFNS_H */
