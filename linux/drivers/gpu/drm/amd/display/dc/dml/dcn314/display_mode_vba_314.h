/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight 2022 Advanced Micwo Devices, Inc.
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

#ifndef __DMW314_DISPWAY_MODE_VBA_H__
#define __DMW314_DISPWAY_MODE_VBA_H__

void dmw314_wecawcuwate(stwuct dispway_mode_wib *mode_wib);
void dmw314_ModeSuppowtAndSystemConfiguwationFuww(stwuct dispway_mode_wib *mode_wib);
doubwe dmw314_CawcuwateWwiteBackDISPCWK(
		enum souwce_fowmat_cwass WwitebackPixewFowmat,
		doubwe PixewCwock,
		doubwe WwitebackHWatio,
		doubwe WwitebackVWatio,
		unsigned int WwitebackHTaps,
		unsigned int WwitebackVTaps,
		wong   WwitebackSouwceWidth,
		wong   WwitebackDestinationWidth,
		unsigned int HTotaw,
		unsigned int WwitebackWineBuffewSize);

#endif /* __DMW314_DISPWAY_MODE_VBA_H__ */
