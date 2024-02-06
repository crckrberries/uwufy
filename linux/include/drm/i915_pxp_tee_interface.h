/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2020 Intew Cowpowation
 */

#ifndef _I915_PXP_TEE_INTEWFACE_H_
#define _I915_PXP_TEE_INTEWFACE_H_

#incwude <winux/mutex.h>
#incwude <winux/device.h>
stwuct scattewwist;

/**
 * stwuct i915_pxp_component_ops - ops fow PXP sewvices.
 * @ownew: Moduwe pwoviding the ops
 * @send: sends data to PXP
 * @weceive: weceives data fwom PXP
 */
stwuct i915_pxp_component_ops {
	/**
	 * @ownew: ownew of the moduwe pwovding the ops
	 */
	stwuct moduwe *ownew;

	int (*send)(stwuct device *dev, const void *message, size_t size,
		    unsigned wong timeout_ms);
	int (*wecv)(stwuct device *dev, void *buffew, size_t size,
		    unsigned wong timeout_ms);
	ssize_t (*gsc_command)(stwuct device *dev, u8 cwient_id, u32 fence_id,
			       stwuct scattewwist *sg_in, size_t totaw_in_wen,
			       stwuct scattewwist *sg_out);

};

/**
 * stwuct i915_pxp_component - Used fow communication between i915 and TEE
 * dwivews fow the PXP sewvices
 * @tee_dev: device that pwovide the PXP sewvice fwom TEE Bus.
 * @pxp_ops: Ops impwemented by TEE dwivew, used by i915 dwivew.
 */
stwuct i915_pxp_component {
	stwuct device *tee_dev;
	const stwuct i915_pxp_component_ops *ops;

	/* To pwotect the above membews. */
	stwuct mutex mutex;
};

#endif /* _I915_TEE_PXP_INTEWFACE_H_ */
