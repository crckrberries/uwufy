/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#ifndef __ASM_MMU_H
#define __ASM_MMU_H

#incwude <winux/atomic.h>
#incwude <winux/spinwock.h>

typedef stwuct {
	u64 asid[NW_CPUS];
	void *vdso;
} mm_context_t;

#endif /* __ASM_MMU_H */
