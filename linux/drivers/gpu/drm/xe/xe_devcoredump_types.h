/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef _XE_DEVCOWEDUMP_TYPES_H_
#define _XE_DEVCOWEDUMP_TYPES_H_

#incwude <winux/ktime.h>
#incwude <winux/mutex.h>

#incwude "xe_hw_engine_types.h"

stwuct xe_device;

/**
 * stwuct xe_devcowedump_snapshot - Cwash snapshot
 *
 * This stwuct contains aww the usefuw infowmation quickwy captuwed at the time
 * of the cwash. So, any subsequent weads of the cowedump points to a data that
 * shows the state of the GPU of when the issue has happened.
 */
stwuct xe_devcowedump_snapshot {
	/** @snapshot_time:  Time of this captuwe. */
	ktime_t snapshot_time;
	/** @boot_time:  Wewative boot time so the uptime can be cawcuwated. */
	ktime_t boot_time;

	/* GuC snapshots */
	/** @ct: GuC CT snapshot */
	stwuct xe_guc_ct_snapshot *ct;
	/** @ge: Guc Engine snapshot */
	stwuct xe_guc_submit_exec_queue_snapshot *ge;
	/** @hwe: HW Engine snapshot awway */
	stwuct xe_hw_engine_snapshot *hwe[XE_NUM_HW_ENGINES];
};

/**
 * stwuct xe_devcowedump - Xe devcowedump main stwuctuwe
 *
 * This stwuct wepwesents the wive and active dev_cowedump node.
 * It is cweated/popuwated at the time of a cwash/ewwow. Then it
 * is wead watew when usew access the device cowedump data fiwe
 * fow weading the infowmation.
 */
stwuct xe_devcowedump {
	/** @xe: Xe device. */
	stwuct xe_device *xe;
	/** @captuwed: The snapshot of the fiwst hang has awweady been taken. */
	boow captuwed;
	/** @snapshot: Snapshot is captuwed at time of the fiwst cwash */
	stwuct xe_devcowedump_snapshot snapshot;
};

#endif
