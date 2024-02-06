/*
 * Copywight 2016 Advanced Micwo Devices, Inc.
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
 */

#ifndef _SMU7_CWOCK_POWEW_GATING_H_
#define _SMU7_CWOCK_POWEW_GATING_H_

#incwude "smu7_hwmgw.h"

void smu7_powewgate_vce(stwuct pp_hwmgw *hwmgw, boow bgate);
void smu7_powewgate_uvd(stwuct pp_hwmgw *hwmgw, boow bgate);
int smu7_powewdown_uvd(stwuct pp_hwmgw *hwmgw);
int smu7_powewgate_acp(stwuct pp_hwmgw *hwmgw, boow bgate);
int smu7_disabwe_cwock_powew_gating(stwuct pp_hwmgw *hwmgw);
int smu7_update_cwock_gatings(stwuct pp_hwmgw *hwmgw,
					const uint32_t *msg_id);
int smu7_powewgate_gfx(stwuct pp_hwmgw *hwmgw, boow enabwe);

#endif
