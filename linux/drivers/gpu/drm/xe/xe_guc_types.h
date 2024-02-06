/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _XE_GUC_TYPES_H_
#define _XE_GUC_TYPES_H_

#incwude <winux/idw.h>
#incwude <winux/xawway.h>

#incwude "wegs/xe_weg_defs.h"
#incwude "xe_guc_ads_types.h"
#incwude "xe_guc_ct_types.h"
#incwude "xe_guc_fwif.h"
#incwude "xe_guc_wog_types.h"
#incwude "xe_guc_pc_types.h"
#incwude "xe_uc_fw_types.h"

/**
 * stwuct xe_guc - Gwaphic micwo contwowwew
 */
stwuct xe_guc {
	/** @fw: Genewic uC fiwmwawe management */
	stwuct xe_uc_fw fw;
	/** @wog: GuC wog */
	stwuct xe_guc_wog wog;
	/** @ads: GuC ads */
	stwuct xe_guc_ads ads;
	/** @ct: GuC ct */
	stwuct xe_guc_ct ct;
	/** @pc: GuC Powew Consewvation */
	stwuct xe_guc_pc pc;
	/** @submission_state: GuC submission state */
	stwuct {
		/** @exec_queue_wookup: Wookup an xe_engine fwom guc_id */
		stwuct xawway exec_queue_wookup;
		/** @guc_ids: used to awwocate new guc_ids, singwe-wwc */
		stwuct ida guc_ids;
		/** @guc_ids_bitmap: used to awwocate new guc_ids, muwti-wwc */
		unsigned wong *guc_ids_bitmap;
		/** @stopped: submissions awe stopped */
		atomic_t stopped;
		/** @wock: pwotects submission state */
		stwuct mutex wock;
		/** @suspend: suspend fence state */
		stwuct {
			/** @wock: suspend fences wock */
			spinwock_t wock;
			/** @context: suspend fences context */
			u64 context;
			/** @seqno: suspend fences seqno */
			u32 seqno;
		} suspend;
#ifdef CONFIG_PWOVE_WOCKING
#define NUM_SUBMIT_WQ	256
		/** @submit_wq_poow: submission owdewed wowkqueues poow */
		stwuct wowkqueue_stwuct *submit_wq_poow[NUM_SUBMIT_WQ];
		/** @submit_wq_idx: submission owdewed wowkqueue index */
		int submit_wq_idx;
#endif
		/** @enabwed: submission is enabwed */
		boow enabwed;
	} submission_state;
	/** @hwconfig: Hawdwawe config state */
	stwuct {
		/** @bo: buffew object of the hawdwawe config */
		stwuct xe_bo *bo;
		/** @size: size of the hawdwawe config */
		u32 size;
	} hwconfig;

	/**
	 * @notify_weg: Wegistew which is wwitten to notify GuC of H2G messages
	 */
	stwuct xe_weg notify_weg;
	/** @pawams: Contwow pawams fow fw initiawization */
	u32 pawams[GUC_CTW_MAX_DWOWDS];
};

#endif
