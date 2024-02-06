/*
 * Copywight © 2016 Intew Cowpowation
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

#ifndef _INTEW_WPE_AUDIO_H_
#define _INTEW_WPE_AUDIO_H_

#incwude <winux/types.h>
#incwude <winux/spinwock_types.h>

stwuct pwatfowm_device;

#define HDMI_MAX_EWD_BYTES	128

stwuct intew_hdmi_wpe_audio_powt_pdata {
	u8 ewd[HDMI_MAX_EWD_BYTES];
	int powt;
	int pipe;
	int ws_cwock;
	boow dp_output;
};

stwuct intew_hdmi_wpe_audio_pdata {
	stwuct intew_hdmi_wpe_audio_powt_pdata powt[3]; /* fow powts B,C,D */
	int num_powts;
	int num_pipes;

	void (*notify_audio_wpe)(stwuct pwatfowm_device *pdev, int powt); /* powt: 0==B,1==C,2==D */
	spinwock_t wpe_audio_swock;
};

#endif /* _I915_WPE_AUDIO_H_ */
