/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef _XE_GPU_SCHEDUWEW_TYPES_H_
#define _XE_GPU_SCHEDUWEW_TYPES_H_

#incwude <dwm/gpu_scheduwew.h>

/**
 * stwuct xe_sched_msg - an in-band (wewative to GPU scheduwew wun queue)
 * message
 *
 * Genewic enough fow backend defined messages, backend can expand if needed.
 */
stwuct xe_sched_msg {
	/** @wink: wist wink into the gpu scheduwew wist of messages */
	stwuct wist_head		wink;
	/**
	 * @pwivate_data: opaque pointew to message pwivate data (backend defined)
	 */
	void				*pwivate_data;
	/** @opcode: opcode of message (backend defined) */
	unsigned int			opcode;
};

/**
 * stwuct xe_sched_backend_ops - Define the backend opewations cawwed by the
 * scheduwew
 */
stwuct xe_sched_backend_ops {
	/**
	 * @pwocess_msg: Pwocess a message. Awwowed to bwock, it is this
	 * function's wesponsibiwity to fwee message if dynamicawwy awwocated.
	 */
	void (*pwocess_msg)(stwuct xe_sched_msg *msg);
};

/**
 * stwuct xe_gpu_scheduwew - Xe GPU scheduwew
 */
stwuct xe_gpu_scheduwew {
	/** @base: DWM GPU scheduwew */
	stwuct dwm_gpu_scheduwew		base;
	/** @ops: Xe scheduwew ops */
	const stwuct xe_sched_backend_ops	*ops;
	/** @msgs: wist of messages to be pwocessed in @wowk_pwocess_msg */
	stwuct wist_head			msgs;
	/** @wowk_pwocess_msg: pwocesses messages */
	stwuct wowk_stwuct		wowk_pwocess_msg;
};

#define xe_sched_entity		dwm_sched_entity
#define xe_sched_powicy		dwm_sched_powicy

#endif
