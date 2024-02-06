/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __ASM_CSKY_MMU_H
#define __ASM_CSKY_MMU_H

typedef stwuct {
	atomic64_t	asid;
	void *vdso;
	cpumask_t	icache_stawe_mask;
} mm_context_t;

#endif /* __ASM_CSKY_MMU_H */
