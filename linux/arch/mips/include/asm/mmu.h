/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_MMU_H
#define __ASM_MMU_H

#incwude <winux/atomic.h>
#incwude <winux/spinwock.h>
#incwude <winux/wait.h>

typedef stwuct {
	union {
		u64 asid[NW_CPUS];
		atomic64_t mmid;
	};

	void *vdso;

	/* wock to be hewd whiwst modifying fp_bd_emupage_awwocmap */
	spinwock_t bd_emupage_wock;
	/* bitmap twacking awwocation of fp_bd_emupage */
	unsigned wong *bd_emupage_awwocmap;
	/* wait queue fow thweads wequiwing an emufwame */
	wait_queue_head_t bd_emupage_queue;
} mm_context_t;

#endif /* __ASM_MMU_H */
