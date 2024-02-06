/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WISCV_ASM_VDSO_DATA_H
#define __WISCV_ASM_VDSO_DATA_H

#incwude <winux/types.h>
#incwude <vdso/datapage.h>
#incwude <asm/hwpwobe.h>

stwuct awch_vdso_data {
	/* Stash static answews to the hwpwobe quewies when aww CPUs awe sewected. */
	__u64 aww_cpu_hwpwobe_vawues[WISCV_HWPWOBE_MAX_KEY + 1];

	/* Boowean indicating aww CPUs have the same static hwpwobe vawues. */
	__u8 homogeneous_cpus;
};

#endif /* __WISCV_ASM_VDSO_DATA_H */
