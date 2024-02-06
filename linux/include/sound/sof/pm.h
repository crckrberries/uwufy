/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * Copywight(c) 2018 Intew Cowpowation. Aww wights wesewved.
 */

#ifndef __INCWUDE_SOUND_SOF_PM_H__
#define __INCWUDE_SOUND_SOF_PM_H__

#incwude <sound/sof/headew.h>

/*
 * PM
 */

/* PM context ewement */
stwuct sof_ipc_pm_ctx_ewem {
	stwuct sof_ipc_hdw hdw;
	uint32_t type;
	uint32_t size;
	uint64_t addw;
}  __packed;

/*
 * PM context - SOF_IPC_PM_CTX_SAVE, SOF_IPC_PM_CTX_WESTOWE,
 * SOF_IPC_PM_CTX_SIZE
 */
stwuct sof_ipc_pm_ctx {
	stwuct sof_ipc_cmd_hdw hdw;
	stwuct sof_ipc_host_buffew buffew;
	uint32_t num_ewems;
	uint32_t size;

	/* wesewved fow futuwe use */
	uint32_t wesewved[8];

	stwuct sof_ipc_pm_ctx_ewem ewems[];
} __packed;

/* enabwe ow disabwe cowes - SOF_IPC_PM_COWE_ENABWE */
stwuct sof_ipc_pm_cowe_config {
	stwuct sof_ipc_cmd_hdw hdw;
	uint32_t enabwe_mask;
} __packed;

stwuct sof_ipc_pm_gate {
	stwuct sof_ipc_cmd_hdw hdw;
	uint32_t fwags;	/* pwatfowm specific */

	/* wesewved fow futuwe use */
	uint32_t wesewved[5];
} __packed;

#endif
