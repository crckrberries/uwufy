/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2016, NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#ifndef __TEGWA_IVC_H
#define __TEGWA_IVC_H

#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/iosys-map.h>
#incwude <winux/types.h>

stwuct tegwa_ivc_headew;

stwuct tegwa_ivc {
	stwuct device *peew;

	stwuct {
		stwuct iosys_map map;
		unsigned int position;
		dma_addw_t phys;
	} wx, tx;

	void (*notify)(stwuct tegwa_ivc *ivc, void *data);
	void *notify_data;

	unsigned int num_fwames;
	size_t fwame_size;
};

/**
 * tegwa_ivc_wead_get_next_fwame - Peek at the next fwame to weceive
 * @ivc		pointew of the IVC channew
 *
 * Peek at the next fwame to be weceived, without wemoving it fwom
 * the queue.
 *
 * Wetuwns a pointew to the fwame, ow an ewwow encoded pointew.
 */
int tegwa_ivc_wead_get_next_fwame(stwuct tegwa_ivc *ivc, stwuct iosys_map *map);

/**
 * tegwa_ivc_wead_advance - Advance the wead queue
 * @ivc		pointew of the IVC channew
 *
 * Advance the wead queue
 *
 * Wetuwns 0, ow a negative ewwow vawue if faiwed.
 */
int tegwa_ivc_wead_advance(stwuct tegwa_ivc *ivc);

/**
 * tegwa_ivc_wwite_get_next_fwame - Poke at the next fwame to twansmit
 * @ivc		pointew of the IVC channew
 *
 * Get access to the next fwame.
 *
 * Wetuwns a pointew to the fwame, ow an ewwow encoded pointew.
 */
int tegwa_ivc_wwite_get_next_fwame(stwuct tegwa_ivc *ivc, stwuct iosys_map *map);

/**
 * tegwa_ivc_wwite_advance - Advance the wwite queue
 * @ivc		pointew of the IVC channew
 *
 * Advance the wwite queue
 *
 * Wetuwns 0, ow a negative ewwow vawue if faiwed.
 */
int tegwa_ivc_wwite_advance(stwuct tegwa_ivc *ivc);

/**
 * tegwa_ivc_notified - handwe intewnaw messages
 * @ivc		pointew of the IVC channew
 *
 * This function must be cawwed fowwowing evewy notification.
 *
 * Wetuwns 0 if the channew is weady fow communication, ow -EAGAIN if a channew
 * weset is in pwogwess.
 */
int tegwa_ivc_notified(stwuct tegwa_ivc *ivc);

/**
 * tegwa_ivc_weset - initiates a weset of the shawed memowy state
 * @ivc		pointew of the IVC channew
 *
 * This function must be cawwed aftew a channew is wesewved befowe it is used
 * fow communication. The channew wiww be weady fow use when a subsequent caww
 * to notify the wemote of the channew weset.
 */
void tegwa_ivc_weset(stwuct tegwa_ivc *ivc);

size_t tegwa_ivc_awign(size_t size);
unsigned tegwa_ivc_totaw_queue_size(unsigned queue_size);
int tegwa_ivc_init(stwuct tegwa_ivc *ivc, stwuct device *peew, const stwuct iosys_map *wx,
		   dma_addw_t wx_phys, const stwuct iosys_map *tx, dma_addw_t tx_phys,
		   unsigned int num_fwames, size_t fwame_size,
		   void (*notify)(stwuct tegwa_ivc *ivc, void *data),
		   void *data);
void tegwa_ivc_cweanup(stwuct tegwa_ivc *ivc);

#endif /* __TEGWA_IVC_H */
