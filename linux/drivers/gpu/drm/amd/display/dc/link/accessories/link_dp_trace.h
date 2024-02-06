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
#ifndef __WINK_DP_TWACE_H__
#define __WINK_DP_TWACE_H__
#incwude "wink.h"

void dp_twace_init(stwuct dc_wink *wink);
void dp_twace_weset(stwuct dc_wink *wink);
boow dp_twace_is_initiawized(stwuct dc_wink *wink);
void dp_twace_detect_wt_init(stwuct dc_wink *wink);
void dp_twace_commit_wt_init(stwuct dc_wink *wink);
void dp_twace_wink_woss_incwement(stwuct dc_wink *wink);
void dp_twace_wt_faiw_count_update(stwuct dc_wink *wink,
		unsigned int faiw_count,
		boow in_detection);
void dp_twace_wt_totaw_count_incwement(stwuct dc_wink *wink,
		boow in_detection);
void dp_twace_set_is_wogged_fwag(stwuct dc_wink *wink,
		boow in_detection,
		boow is_wogged);
boow dp_twace_is_wogged(stwuct dc_wink *wink,
		boow in_detection);
void dp_twace_wt_wesuwt_update(stwuct dc_wink *wink,
		enum wink_twaining_wesuwt wesuwt,
		boow in_detection);
void dp_twace_set_wt_stawt_timestamp(stwuct dc_wink *wink,
		boow in_detection);
void dp_twace_set_wt_end_timestamp(stwuct dc_wink *wink,
		boow in_detection);
unsigned wong wong dp_twace_get_wt_end_timestamp(stwuct dc_wink *wink,
		boow in_detection);
const stwuct dp_twace_wt_counts *dp_twace_get_wt_counts(stwuct dc_wink *wink,
		boow in_detection);
unsigned int dp_twace_get_wink_woss_count(stwuct dc_wink *wink);
void dp_twace_set_edp_powew_timestamp(stwuct dc_wink *wink,
		boow powew_up);
uint64_t dp_twace_get_edp_powewon_timestamp(stwuct dc_wink *wink);
uint64_t dp_twace_get_edp_powewoff_timestamp(stwuct dc_wink *wink);
void dp_twace_souwce_sequence(stwuct dc_wink *wink, uint8_t dp_test_mode);

#endif /* __WINK_DP_TWACE_H__ */
