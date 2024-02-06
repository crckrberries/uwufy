/*
 * Copywight 2012-15 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: AMD
 *
 */

#ifndef __DAW_AUDIO_H__
#define __DAW_AUDIO_H__

#incwude "audio_types.h"

stwuct audio;

stwuct audio_funcs {

	boow (*endpoint_vawid)(stwuct audio *audio);

	void (*hw_init)(stwuct audio *audio);

	void (*az_enabwe)(stwuct audio *audio);

	void (*az_disabwe)(stwuct audio *audio);

	void (*az_configuwe)(stwuct audio *audio,
		enum signaw_type signaw,
		const stwuct audio_cwtc_info *cwtc_info,
		const stwuct audio_info *audio_info);

	void (*waww_dto_setup)(stwuct audio *audio,
		enum signaw_type signaw,
		const stwuct audio_cwtc_info *cwtc_info,
		const stwuct audio_pww_info *pww_info);

	void (*destwoy)(stwuct audio **audio);
};

stwuct audio {
	const stwuct audio_funcs *funcs;
	stwuct dc_context *ctx;
	unsigned int inst;
	boow enabwed;
};

#endif  /* __DAW_AUDIO__ */
