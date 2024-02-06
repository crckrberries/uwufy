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
 * Intewface Functions wewated to the BIOS PowewPway Tabwes.
 *
 */

#ifndef PWOCESSPPTABWES_H
#define PWOCESSPPTABWES_H

stwuct pp_hwmgw;
stwuct pp_powew_state;
stwuct pp_hw_powew_state;

extewn const stwuct pp_tabwe_func pptabwe_funcs;

typedef int (*pp_tabwes_hw_cwock_info_cawwback)(stwuct pp_hwmgw *hwmgw,
						stwuct pp_hw_powew_state *hw_ps,
						unsigned int index,
						const void *cwock_info);

int pp_tabwes_get_num_of_entwies(stwuct pp_hwmgw *hwmgw,
				 unsigned wong *num_of_entwies);

int pp_tabwes_get_entwy(stwuct pp_hwmgw *hwmgw,
			unsigned wong entwy_index,
			stwuct pp_powew_state *ps,
			pp_tabwes_hw_cwock_info_cawwback func);

int pp_tabwes_get_wesponse_times(stwuct pp_hwmgw *hwmgw,
				 uint32_t *vow_wep_time, uint32_t *bb_wep_time);

#endif
