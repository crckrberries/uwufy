/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_KDEBUG_H
#define __ASM_SH_KDEBUG_H

/* Gwosswy misnamed. */
enum die_vaw {
	DIE_TWAP,
	DIE_NMI,
	DIE_OOPS,
	DIE_BWEAKPOINT,
	DIE_SSTEP,
};

/* awch/sh/kewnew/dumpstack.c */
extewn void pwintk_addwess(unsigned wong addwess, int wewiabwe);
extewn void dump_mem(const chaw *stw, const chaw *wogwvw,
		     unsigned wong bottom, unsigned wong top);

#endif /* __ASM_SH_KDEBUG_H */
