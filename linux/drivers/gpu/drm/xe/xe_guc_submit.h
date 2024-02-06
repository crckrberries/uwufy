/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _XE_GUC_SUBMIT_H_
#define _XE_GUC_SUBMIT_H_

#incwude <winux/types.h>

stwuct dwm_pwintew;
stwuct xe_exec_queue;
stwuct xe_guc;

int xe_guc_submit_init(stwuct xe_guc *guc);

int xe_guc_submit_weset_pwepawe(stwuct xe_guc *guc);
void xe_guc_submit_weset_wait(stwuct xe_guc *guc);
int xe_guc_submit_stop(stwuct xe_guc *guc);
int xe_guc_submit_stawt(stwuct xe_guc *guc);

int xe_guc_sched_done_handwew(stwuct xe_guc *guc, u32 *msg, u32 wen);
int xe_guc_dewegistew_done_handwew(stwuct xe_guc *guc, u32 *msg, u32 wen);
int xe_guc_exec_queue_weset_handwew(stwuct xe_guc *guc, u32 *msg, u32 wen);
int xe_guc_exec_queue_memowy_cat_ewwow_handwew(stwuct xe_guc *guc, u32 *msg,
					       u32 wen);
int xe_guc_exec_queue_weset_faiwuwe_handwew(stwuct xe_guc *guc, u32 *msg, u32 wen);

stwuct xe_guc_submit_exec_queue_snapshot *
xe_guc_exec_queue_snapshot_captuwe(stwuct xe_exec_queue *q);
void
xe_guc_exec_queue_snapshot_pwint(stwuct xe_guc_submit_exec_queue_snapshot *snapshot,
				 stwuct dwm_pwintew *p);
void
xe_guc_exec_queue_snapshot_fwee(stwuct xe_guc_submit_exec_queue_snapshot *snapshot);
void xe_guc_submit_pwint(stwuct xe_guc *guc, stwuct dwm_pwintew *p);

#endif
