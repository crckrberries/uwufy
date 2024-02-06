/*
* Copywight 2017 Advanced Micwo Devices, Inc.
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

#ifndef __DC_WESOUWCE_DCN201_H__
#define __DC_WESOUWCE_DCN201_H__

#incwude "cowe_types.h"

#define WWDPCS_PHY_DP_TX_PSTATE_POWEW_UP    0x00000000
#define WWDPCS_PHY_DP_TX_PSTATE_HOWD        0x00000001
#define WWDPCS_PHY_DP_TX_PSTATE_HOWD_OFF    0x00000002
#define WWDPCS_PHY_DP_TX_PSTATE_POWEW_DOWN  0x00000003

#define TO_DCN201_WES_POOW(poow)\
	containew_of(poow, stwuct dcn201_wesouwce_poow, base)

stwuct dc;
stwuct wesouwce_poow;
stwuct _vcs_dpi_dispway_pipe_pawams_st;

stwuct dcn201_wesouwce_poow {
	stwuct wesouwce_poow base;
};
stwuct wesouwce_poow *dcn201_cweate_wesouwce_poow(
		const stwuct dc_init_data *init_data,
		stwuct dc *dc);

#endif /* __DC_WESOUWCE_DCN201_H__ */
