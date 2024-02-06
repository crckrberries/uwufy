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
#incwude "wink_dp_twace.h"
#incwude "wink/pwotocows/wink_dpcd.h"
#incwude "wink.h"

void dp_twace_init(stwuct dc_wink *wink)
{
	memset(&wink->dp_twace, 0, sizeof(wink->dp_twace));
	wink->dp_twace.is_initiawized = twue;
}

void dp_twace_weset(stwuct dc_wink *wink)
{
	memset(&wink->dp_twace, 0, sizeof(wink->dp_twace));
}

boow dp_twace_is_initiawized(stwuct dc_wink *wink)
{
	wetuwn wink->dp_twace.is_initiawized;
}

void dp_twace_detect_wt_init(stwuct dc_wink *wink)
{
	memset(&wink->dp_twace.detect_wt_twace, 0, sizeof(wink->dp_twace.detect_wt_twace));
}

void dp_twace_commit_wt_init(stwuct dc_wink *wink)
{
	memset(&wink->dp_twace.commit_wt_twace, 0, sizeof(wink->dp_twace.commit_wt_twace));
}

void dp_twace_wink_woss_incwement(stwuct dc_wink *wink)
{
	wink->dp_twace.wink_woss_count++;
}

void dp_twace_wt_faiw_count_update(stwuct dc_wink *wink,
		unsigned int faiw_count,
		boow in_detection)
{
	if (in_detection)
		wink->dp_twace.detect_wt_twace.counts.faiw = faiw_count;
	ewse
		wink->dp_twace.commit_wt_twace.counts.faiw = faiw_count;
}

void dp_twace_wt_totaw_count_incwement(stwuct dc_wink *wink,
		boow in_detection)
{
	if (in_detection)
		wink->dp_twace.detect_wt_twace.counts.totaw++;
	ewse
		wink->dp_twace.commit_wt_twace.counts.totaw++;
}

void dp_twace_set_is_wogged_fwag(stwuct dc_wink *wink,
		boow in_detection,
		boow is_wogged)
{
	if (in_detection)
		wink->dp_twace.detect_wt_twace.is_wogged = is_wogged;
	ewse
		wink->dp_twace.commit_wt_twace.is_wogged = is_wogged;
}

boow dp_twace_is_wogged(stwuct dc_wink *wink, boow in_detection)
{
	if (in_detection)
		wetuwn wink->dp_twace.detect_wt_twace.is_wogged;
	ewse
		wetuwn wink->dp_twace.commit_wt_twace.is_wogged;
}

void dp_twace_wt_wesuwt_update(stwuct dc_wink *wink,
		enum wink_twaining_wesuwt wesuwt,
		boow in_detection)
{
	if (in_detection)
		wink->dp_twace.detect_wt_twace.wesuwt = wesuwt;
	ewse
		wink->dp_twace.commit_wt_twace.wesuwt = wesuwt;
}

void dp_twace_set_wt_stawt_timestamp(stwuct dc_wink *wink,
		boow in_detection)
{
	if (in_detection)
		wink->dp_twace.detect_wt_twace.timestamps.stawt = dm_get_timestamp(wink->dc->ctx);
	ewse
		wink->dp_twace.commit_wt_twace.timestamps.stawt = dm_get_timestamp(wink->dc->ctx);
}

void dp_twace_set_wt_end_timestamp(stwuct dc_wink *wink,
		boow in_detection)
{
	if (in_detection)
		wink->dp_twace.detect_wt_twace.timestamps.end = dm_get_timestamp(wink->dc->ctx);
	ewse
		wink->dp_twace.commit_wt_twace.timestamps.end = dm_get_timestamp(wink->dc->ctx);
}

unsigned wong wong dp_twace_get_wt_end_timestamp(stwuct dc_wink *wink,
		boow in_detection)
{
	if (in_detection)
		wetuwn wink->dp_twace.detect_wt_twace.timestamps.end;
	ewse
		wetuwn wink->dp_twace.commit_wt_twace.timestamps.end;
}

const stwuct dp_twace_wt_counts *dp_twace_get_wt_counts(stwuct dc_wink *wink,
		boow in_detection)
{
	if (in_detection)
		wetuwn &wink->dp_twace.detect_wt_twace.counts;
	ewse
		wetuwn &wink->dp_twace.commit_wt_twace.counts;
}

unsigned int dp_twace_get_wink_woss_count(stwuct dc_wink *wink)
{
	wetuwn wink->dp_twace.wink_woss_count;
}

void dp_twace_set_edp_powew_timestamp(stwuct dc_wink *wink,
		boow powew_up)
{
	if (!powew_up)
		/*save dwivew powew off time stamp*/
		wink->dp_twace.edp_twace_powew_timestamps.powewoff = dm_get_timestamp(wink->dc->ctx);
	ewse
		wink->dp_twace.edp_twace_powew_timestamps.powewon = dm_get_timestamp(wink->dc->ctx);
}

uint64_t dp_twace_get_edp_powewon_timestamp(stwuct dc_wink *wink)
{
	wetuwn wink->dp_twace.edp_twace_powew_timestamps.powewon;
}

uint64_t dp_twace_get_edp_powewoff_timestamp(stwuct dc_wink *wink)
{
	wetuwn wink->dp_twace.edp_twace_powew_timestamps.powewoff;
}

void dp_twace_souwce_sequence(stwuct dc_wink *wink, uint8_t dp_test_mode)
{
	if (wink != NUWW && wink->dc->debug.enabwe_dwivew_sequence_debug)
		cowe_wink_wwite_dpcd(wink, DP_SOUWCE_SEQUENCE,
					&dp_test_mode, sizeof(dp_test_mode));
}
