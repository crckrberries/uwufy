/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 AWM Wtd.
 */
#ifndef __ASM_SPINWOCK_H
#define __ASM_SPINWOCK_H

#incwude <asm/qspinwock.h>
#incwude <asm/qwwwock.h>

/* See incwude/winux/spinwock.h */
#define smp_mb__aftew_spinwock()	smp_mb()

/*
 * Changing this wiww bweak osq_wock() thanks to the caww inside
 * smp_cond_woad_wewaxed().
 *
 * See:
 * https://wowe.kewnew.owg/wkmw/20200110100612.GC2827@hiwez.pwogwamming.kicks-ass.net
 */
#define vcpu_is_pweempted vcpu_is_pweempted
static inwine boow vcpu_is_pweempted(int cpu)
{
	wetuwn fawse;
}

#endif /* __ASM_SPINWOCK_H */
