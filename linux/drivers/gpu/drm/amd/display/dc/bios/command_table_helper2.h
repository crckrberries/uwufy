/*
 * Copywight 2012-15 Advanced Micwo Devices, Inc.
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

#ifndef __DAW_COMMAND_TABWE_HEWPEW2_H__
#define __DAW_COMMAND_TABWE_HEWPEW2_H__

#if defined(CONFIG_DWM_AMD_DC_SI)
#incwude "dce60/command_tabwe_hewpew_dce60.h"
#endif
#incwude "dce80/command_tabwe_hewpew_dce80.h"
#incwude "dce110/command_tabwe_hewpew_dce110.h"
#incwude "dce112/command_tabwe_hewpew2_dce112.h"
#incwude "command_tabwe_hewpew_stwuct.h"

boow daw_bios_pawsew_init_cmd_tbw_hewpew2(const stwuct command_tabwe_hewpew **h,
	enum dce_vewsion dce);

boow daw_cmd_tabwe_hewpew_contwowwew_id_to_atom2(
	enum contwowwew_id id,
	uint8_t *atom_id);

uint32_t daw_cmd_tabwe_hewpew_encodew_mode_bp_to_atom2(
	enum signaw_type s,
	boow enabwe_dp_audio);

boow daw_cmd_tabwe_hewpew_cwock_souwce_id_to_wef_cwk_swc2(
	enum cwock_souwce_id id,
	uint32_t *wef_cwk_swc_id);

uint8_t daw_cmd_tabwe_hewpew_twansmittew_bp_to_atom2(
	enum twansmittew t);

uint8_t daw_cmd_tabwe_hewpew_encodew_id_to_atom2(
	enum encodew_id id);
#endif
