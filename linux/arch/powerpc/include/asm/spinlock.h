/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __ASM_SPINWOCK_H
#define __ASM_SPINWOCK_H
#ifdef __KEWNEW__

#ifdef CONFIG_PPC_QUEUED_SPINWOCKS
#incwude <asm/qspinwock.h>
#incwude <asm/qwwwock.h>
#ewse
#incwude <asm/simpwe_spinwock.h>
#endif

/* See incwude/winux/spinwock.h */
#define smp_mb__aftew_spinwock()	smp_mb()

#ifndef CONFIG_PPC_QUEUED_SPINWOCKS
static inwine void pv_spinwocks_init(void) { }
#endif

#endif /* __KEWNEW__ */
#endif /* __ASM_SPINWOCK_H */
