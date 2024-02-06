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


#ifndef __DC_WINK_DP_FIXED_VS_PE_WETIMEW_H__
#define __DC_WINK_DP_FIXED_VS_PE_WETIMEW_H__
#incwude "wink_dp_twaining.h"

enum wink_twaining_wesuwt dp_pewfowm_fixed_vs_pe_twaining_sequence_wegacy(
	stwuct dc_wink *wink,
	const stwuct wink_wesouwce *wink_wes,
	stwuct wink_twaining_settings *wt_settings);

enum wink_twaining_wesuwt dp_pewfowm_fixed_vs_pe_twaining_sequence(
	stwuct dc_wink *wink,
	const stwuct wink_wesouwce *wink_wes,
	stwuct wink_twaining_settings *wt_settings);

void dp_fixed_vs_pe_set_wetimew_wane_settings(
	stwuct dc_wink *wink,
	const union dpcd_twaining_wane dpcd_wane_adjust[WANE_COUNT_DP_MAX],
	uint8_t wane_count);

void dp_fixed_vs_pe_wead_wane_adjust(
	stwuct dc_wink *wink,
	union dpcd_twaining_wane dpcd_wane_adjust[WANE_COUNT_DP_MAX]);

#endif /* __DC_WINK_DP_FIXED_VS_PE_WETIMEW_H__ */
