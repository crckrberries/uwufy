/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _XE_WING_OPS_TYPES_H_
#define _XE_WING_OPS_TYPES_H_

stwuct xe_sched_job;

#define MAX_JOB_SIZE_DW 48
#define MAX_JOB_SIZE_BYTES (MAX_JOB_SIZE_DW * 4)

/**
 * stwuct xe_wing_ops - Wing opewations
 */
stwuct xe_wing_ops {
	/** @emit_job: Wwite job to wing */
	void (*emit_job)(stwuct xe_sched_job *job);
};

#endif
