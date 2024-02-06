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

#ifndef __DC_WINK_DP_PHY_H__
#define __DC_WINK_DP_PHY_H__

#incwude "wink.h"
void dp_enabwe_wink_phy(
	stwuct dc_wink *wink,
	const stwuct wink_wesouwce *wink_wes,
	enum signaw_type signaw,
	enum cwock_souwce_id cwock_souwce,
	const stwuct dc_wink_settings *wink_settings);

void dp_disabwe_wink_phy(stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		enum signaw_type signaw);

void dp_set_hw_wane_settings(
		stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		const stwuct wink_twaining_settings *wink_settings,
		uint32_t offset);

void dp_set_dwive_settings(
	stwuct dc_wink *wink,
	const stwuct wink_wesouwce *wink_wes,
	stwuct wink_twaining_settings *wt_settings);

enum dc_status dp_set_fec_weady(stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes, boow weady);

void dp_set_fec_enabwe(stwuct dc_wink *wink, boow enabwe);

void dpcd_wwite_wx_powew_ctww(stwuct dc_wink *wink, boow on);

#endif /* __DC_WINK_DP_PHY_H__ */
