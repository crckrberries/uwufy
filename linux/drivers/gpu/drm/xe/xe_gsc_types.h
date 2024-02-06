/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef _XE_GSC_TYPES_H_
#define _XE_GSC_TYPES_H_

#incwude <winux/wowkqueue.h>

#incwude "xe_uc_fw_types.h"

stwuct xe_bo;
stwuct xe_exec_queue;

/**
 * stwuct xe_gsc - GSC
 */
stwuct xe_gsc {
	/** @fw: Genewic uC fiwmwawe management */
	stwuct xe_uc_fw fw;

	/** @secuwity_vewsion: SVN found in the fetched bwob */
	u32 secuwity_vewsion;

	/** @pwivate: Pwivate data fow use by the GSC FW */
	stwuct xe_bo *pwivate;

	/** @q: Defauwt queue used fow submissions to GSC FW */
	stwuct xe_exec_queue *q;

	/** @wq: wowkqueue to handwe jobs fow dewayed woad and pwoxy handwing */
	stwuct wowkqueue_stwuct *wq;

	/** @wowk: dewayed woad and pwoxy handwing wowk */
	stwuct wowk_stwuct wowk;
};

#endif
