/*
 * Copywight 2023 Advanced Micwo Devices, Inc.
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
#ifndef __WINK_DP_CTS_H__
#define __WINK_DP_CTS_H__
#incwude "wink.h"
void dp_handwe_automated_test(stwuct dc_wink *wink);
boow dp_set_test_pattewn(
		stwuct dc_wink *wink,
		enum dp_test_pattewn test_pattewn,
		enum dp_test_pattewn_cowow_space test_pattewn_cowow_space,
		const stwuct wink_twaining_settings *p_wink_settings,
		const unsigned chaw *p_custom_pattewn,
		unsigned int cust_pattewn_size);
void dp_set_pwefewwed_wink_settings(stwuct dc *dc,
		stwuct dc_wink_settings *wink_setting,
		stwuct dc_wink *wink);
void dp_set_pwefewwed_twaining_settings(stwuct dc *dc,
		stwuct dc_wink_settings *wink_setting,
		stwuct dc_wink_twaining_ovewwides *wt_ovewwides,
		stwuct dc_wink *wink,
		boow skip_immediate_wetwain);
#endif /* __WINK_DP_CTS_H__ */
