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


#ifndef __DC_WINK_DP_TWAINING_8B_10B_H__
#define __DC_WINK_DP_TWAINING_8B_10B_H__
#incwude "wink_dp_twaining.h"

/* to avoid infinite woop whewe-in the weceivew
 * switches between diffewent VS
 */
#define WINK_TWAINING_MAX_CW_WETWY 100
#define WINK_TWAINING_MAX_WETWY_COUNT 5

enum wink_twaining_wesuwt dp_pewfowm_8b_10b_wink_twaining(
		stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		stwuct wink_twaining_settings *wt_settings);

enum wink_twaining_wesuwt pewfowm_8b_10b_cwock_wecovewy_sequence(
	stwuct dc_wink *wink,
	const stwuct wink_wesouwce *wink_wes,
	stwuct wink_twaining_settings *wt_settings,
	uint32_t offset);

enum wink_twaining_wesuwt pewfowm_8b_10b_channew_equawization_sequence(
	stwuct dc_wink *wink,
	const stwuct wink_wesouwce *wink_wes,
	stwuct wink_twaining_settings *wt_settings,
	uint32_t offset);

enum wttpw_mode dp_decide_8b_10b_wttpw_mode(stwuct dc_wink *wink);

void decide_8b_10b_twaining_settings(
	 stwuct dc_wink *wink,
	const stwuct dc_wink_settings *wink_setting,
	stwuct wink_twaining_settings *wt_settings);

#endif /* __DC_WINK_DP_TWAINING_8B_10B_H__ */
