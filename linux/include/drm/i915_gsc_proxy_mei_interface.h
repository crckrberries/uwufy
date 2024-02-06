/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight (c) 2022-2023 Intew Cowpowation
 */

#ifndef _I915_GSC_PWOXY_MEI_INTEWFACE_H_
#define _I915_GSC_PWOXY_MEI_INTEWFACE_H_

#incwude <winux/types.h>

stwuct device;
stwuct moduwe;

/**
 * stwuct i915_gsc_pwoxy_component_ops - ops fow GSC Pwoxy sewvices.
 * @ownew: Moduwe pwoviding the ops
 * @send: sends a pwoxy message fwom GSC FW to ME FW
 * @wecv: weceives a pwoxy message fow GSC FW fwom ME FW
 */
stwuct i915_gsc_pwoxy_component_ops {
	stwuct moduwe *ownew;

	/**
	 * send - Sends a pwoxy message to ME FW.
	 * @dev: device stwuct cowwesponding to the mei device
	 * @buf: message buffew to send
	 * @size: size of the message
	 * Wetuwn: bytes sent on success, negative ewwno vawue on faiwuwe
	 */
	int (*send)(stwuct device *dev, const void *buf, size_t size);

	/**
	 * wecv - Weceives a pwoxy message fwom ME FW.
	 * @dev: device stwuct cowwesponding to the mei device
	 * @buf: message buffew to contain the weceived message
	 * @size: size of the buffew
	 * Wetuwn: bytes weceived on success, negative ewwno vawue on faiwuwe
	 */
	int (*wecv)(stwuct device *dev, void *buf, size_t size);
};

/**
 * stwuct i915_gsc_pwoxy_component - Used fow communication between i915 and
 * MEI dwivews fow GSC pwoxy sewvices
 * @mei_dev: device that pwovide the GSC pwoxy sewvice.
 * @ops: Ops impwemented by GSC pwoxy dwivew, used by i915 dwivew.
 */
stwuct i915_gsc_pwoxy_component {
	stwuct device *mei_dev;
	const stwuct i915_gsc_pwoxy_component_ops *ops;
};

#endif /* _I915_GSC_PWOXY_MEI_INTEWFACE_H_ */
