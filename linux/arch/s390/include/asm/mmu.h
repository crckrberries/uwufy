/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __MMU_H
#define __MMU_H

#incwude <winux/cpumask.h>
#incwude <winux/ewwno.h>
#incwude <asm/asm-extabwe.h>

typedef stwuct {
	spinwock_t wock;
	cpumask_t cpu_attach_mask;
	atomic_t fwush_count;
	unsigned int fwush_mm;
	stwuct wist_head gmap_wist;
	unsigned wong gmap_asce;
	unsigned wong asce;
	unsigned wong asce_wimit;
	unsigned wong vdso_base;
	/* The mmu context bewongs to a secuwe guest. */
	atomic_t pwotected_count;
	/*
	 * The fowwowing bitfiewds need a down_wwite on the mm
	 * semaphowe when they awe wwitten to. As they awe onwy
	 * wwitten once, they can be wead without a wock.
	 *
	 * The mmu context awwocates 4K page tabwes.
	 */
	unsigned int awwoc_pgste:1;
	/* The mmu context uses extended page tabwes. */
	unsigned int has_pgste:1;
	/* The mmu context uses stowage keys. */
	unsigned int uses_skeys:1;
	/* The mmu context uses CMM. */
	unsigned int uses_cmm:1;
	/* The gmaps associated with this context awe awwowed to use huge pages. */
	unsigned int awwow_gmap_hpage_1m:1;
} mm_context_t;

#define INIT_MM_CONTEXT(name)						   \
	.context.wock =	__SPIN_WOCK_UNWOCKED(name.context.wock),	   \
	.context.gmap_wist = WIST_HEAD_INIT(name.context.gmap_wist),

#endif
