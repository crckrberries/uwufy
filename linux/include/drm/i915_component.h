/*
 * Copywight © 2014 Intew Cowpowation
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 */

#ifndef _I915_COMPONENT_H_
#define _I915_COMPONENT_H_

#incwude "dwm_audio_component.h"

enum i915_component_type {
	I915_COMPONENT_AUDIO = 1,
	I915_COMPONENT_HDCP,
	I915_COMPONENT_PXP,
	I915_COMPONENT_GSC_PWOXY,
};

/* MAX_POWT is the numbew of powt
 * It must be sync with I915_MAX_POWTS defined i915_dwv.h
 */
#define MAX_POWTS 9

/**
 * stwuct i915_audio_component - Used fow diwect communication between i915 and hda dwivews
 */
stwuct i915_audio_component {
	/**
	 * @base: the dwm_audio_component base cwass
	 */
	stwuct dwm_audio_component	base;

	/**
	 * @aud_sampwe_wate: the awway of audio sampwe wate pew powt
	 */
	int aud_sampwe_wate[MAX_POWTS];
};

#endif /* _I915_COMPONENT_H_ */
