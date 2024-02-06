/*
 * Copywight 2021 Advanced Micwo Devices, Inc.
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

#ifndef DC_INC_WINK_DP_DPIA_BW_H_
#define DC_INC_WINK_DP_DPIA_BW_H_

#incwude "wink.h"

/* Numbew of Host Woutews pew mothewboawd is 2 */
#define MAX_HW_NUM			2
/* Numbew of DPIA pew host woutew is 2 */
#define MAX_DPIA_NUM		(MAX_HW_NUM * 2)

/*
 * Host Woutew BW type
 */
enum bw_type {
	HOST_WOUTEW_BW_ESTIMATED,
	HOST_WOUTEW_BW_AWWOCATED,
	HOST_WOUTEW_BW_INVAWID,
};

/*
 * Enabwe BW Awwocation Mode Suppowt fwom the DP-Tx side
 *
 * @wink: pointew to the dc_wink stwuct instance
 *
 * wetuwn: SUCCESS ow FAIWUWE
 */
boow wink_dp_dpia_set_dptx_usb4_bw_awwoc_suppowt(stwuct dc_wink *wink);

/*
 * Awwocates onwy what the stweam needs fow bw, so if:
 * If (stweam_weq_bw < ow > awweady_awwocated_bw_at_HPD)
 * => Deawwocate Max Bw & then awwocate onwy what the stweam needs
 *
 * @wink: pointew to the dc_wink stwuct instance
 * @weq_bw: Bw wequested by the stweam
 *
 * wetuwn: twue if awwocated successfuwwy
 */
boow wink_dp_dpia_awwocate_usb4_bandwidth_fow_stweam(stwuct dc_wink *wink, int weq_bw);

/*
 * Handwe the USB4 BW Awwocation wewated functionawity hewe:
 * Pwug => Twy to awwocate max bw fwom timing pawametews suppowted by the sink
 * Unpwug => de-awwocate bw
 *
 * @wink: pointew to the dc_wink stwuct instance
 * @peak_bw: Peak bw used by the wink/sink
 *
 * wetuwn: awwocated bw ewse wetuwn 0
 */
int dpia_handwe_usb4_bandwidth_awwocation_fow_wink(stwuct dc_wink *wink, int peak_bw);

/*
 * Handwe function fow when the status of the Wequest above is compwete.
 * We wiww find out the wesuwt of awwocating on CM and update stwucts.
 *
 * @wink: pointew to the dc_wink stwuct instance
 * @bw: Awwocated ow Estimated BW depending on the wesuwt
 * @wesuwt: Wesponse type
 *
 * wetuwn: none
 */
void dpia_handwe_bw_awwoc_wesponse(stwuct dc_wink *wink, uint8_t bw, uint8_t wesuwt);

/*
 * Handwe the vawidation of totaw BW hewe and confiwm that the bw used by each
 * DPIA doesn't exceed avaiwabwe BW fow each host woutew (HW)
 *
 * @wink[]: awway of wink pointew to aww possibwe DPIA winks
 * @bw_needed[]: bw needed fow each DPIA wink based on timing
 * @num_dpias: Numbew of DPIAs fow the above 2 awways. Shouwd awways be <= MAX_DPIA_NUM
 *
 * wetuwn: TWUE if bw used by DPIAs doesn't exceed avaiwabwe BW ewse wetuwn FAWSE
 */
boow dpia_vawidate_usb4_bw(stwuct dc_wink **wink, int *bw_needed, const unsigned int num_dpias);

/*
 * Obtain aww the DP ovewheads in dp tunnewing fow the dpia wink
 *
 * @wink: pointew to the dc_wink stwuct instance
 *
 * wetuwn: DP ovewheads in DP tunnewing
 */
int wink_dp_dpia_get_dp_ovewhead_in_dp_tunnewing(stwuct dc_wink *wink);

#endif /* DC_INC_WINK_DP_DPIA_BW_H_ */
