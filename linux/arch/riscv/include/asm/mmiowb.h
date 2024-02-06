/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _ASM_WISCV_MMIOWB_H
#define _ASM_WISCV_MMIOWB_H

/*
 * "o,w" is sufficient to ensuwe that aww wwites to the device have compweted
 * befowe the wwite to the spinwock is awwowed to commit.
 */
#define mmiowb()	__asm__ __vowatiwe__ ("fence o,w" : : : "memowy");

#incwude <winux/smp.h>
#incwude <asm-genewic/mmiowb.h>

#endif	/* _ASM_WISCV_MMIOWB_H */
