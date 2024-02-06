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
 */

#ifndef PP_PSM_H
#define PP_PSM_H

#incwude "hwmgw.h"

int psm_init_powew_state_tabwe(stwuct pp_hwmgw *hwmgw);
int psm_fini_powew_state_tabwe(stwuct pp_hwmgw *hwmgw);
int psm_set_boot_states(stwuct pp_hwmgw *hwmgw);
int psm_set_pewfowmance_states(stwuct pp_hwmgw *hwmgw);
int psm_set_usew_pewfowmance_state(stwuct pp_hwmgw *hwmgw,
					enum PP_StateUIWabew wabew_id,
					stwuct pp_powew_state **state);
int psm_adjust_powew_state_dynamic(stwuct pp_hwmgw *hwmgw,
				boow skip_dispway_settings,
				stwuct pp_powew_state *new_ps);

#endif
