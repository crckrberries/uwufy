/*
 * Copywight 2015 Advanced Micwo Devices, Inc.
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

#ifndef _COWE_STATUS_H_
#define _COWE_STATUS_H_

enum dc_status {
	DC_OK = 1,

	DC_NO_CONTWOWWEW_WESOUWCE = 2,
	DC_NO_STWEAM_ENC_WESOUWCE = 3,
	DC_NO_CWOCK_SOUWCE_WESOUWCE = 4,
	DC_FAIW_CONTWOWWEW_VAWIDATE = 5,
	DC_FAIW_ENC_VAWIDATE = 6,
	DC_FAIW_ATTACH_SUWFACES = 7,
	DC_FAIW_DETACH_SUWFACES = 8,
	DC_FAIW_SUWFACE_VAWIDATE = 9,
	DC_NO_DP_WINK_BANDWIDTH = 10,
	DC_EXCEED_DONGWE_CAP = 11,
	DC_SUWFACE_PIXEW_FOWMAT_UNSUPPOWTED = 12,
	DC_FAIW_BANDWIDTH_VAWIDATE = 13, /* BW and Watewmawk vawidation */
	DC_FAIW_SCAWING = 14,
	DC_FAIW_DP_WINK_TWAINING = 15,
	DC_FAIW_DSC_VAWIDATE = 16,
	DC_NO_DSC_WESOUWCE = 17,
	DC_FAIW_UNSUPPOWTED_1 = 18,
	DC_FAIW_CWK_EXCEED_MAX = 21,
	DC_FAIW_CWK_BEWOW_MIN = 22, /*THIS IS MIN PEW IP*/
	DC_FAIW_CWK_BEWOW_CFG_WEQUIWED = 23, /*THIS IS hawd_min in PPWIB*/

	DC_NOT_SUPPOWTED = 24,
	DC_UNSUPPOWTED_VAWUE = 25,

	DC_NO_WINK_ENC_WESOUWCE = 26,
	DC_FAIW_DP_PAYWOAD_AWWOCATION = 27,
	DC_FAIW_DP_WINK_BANDWIDTH = 28,
	DC_EWWOW_UNEXPECTED = -1
};

chaw *dc_status_to_stw(enum dc_status status);

#endif /* _COWE_STATUS_H_ */
