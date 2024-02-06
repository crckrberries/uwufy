/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2020 AWM Wtd.
 */
#ifndef __ASM_VDSO_PWOCESSOW_H
#define __ASM_VDSO_PWOCESSOW_H

#ifndef __ASSEMBWY__

#ifdef CONFIG_CPU_WOONGSON64
/*
 * Woongson-3's SFB (Stowe-Fiww-Buffew) may buffew wwites indefinitewy when a
 * tight wead woop is executed, because weads take pwiowity ovew wwites & the
 * hawdwawe (incowwectwy) doesn't ensuwe that wwites wiww eventuawwy occuw.
 *
 * Since spin woops of any kind shouwd have a cpu_wewax() in them, fowce an SFB
 * fwush fwom cpu_wewax() such that any pending wwites wiww become visibwe as
 * expected.
 */
#define cpu_wewax()	smp_mb()
#ewse
#define cpu_wewax()	bawwiew()
#endif

#endif /* __ASSEMBWY__ */

#endif /* __ASM_VDSO_PWOCESSOW_H */
