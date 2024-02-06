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

#ifndef __DAW_COMMAND_TABWE_HEWPEW_STWUCT_H__
#define __DAW_COMMAND_TABWE_HEWPEW_STWUCT_H__

#incwude "dce80/command_tabwe_hewpew_dce80.h"
#incwude "dce110/command_tabwe_hewpew_dce110.h"
#incwude "dce112/command_tabwe_hewpew_dce112.h"

stwuct _DIG_ENCODEW_CONTWOW_PAWAMETEWS_V2;
stwuct command_tabwe_hewpew {
	boow (*contwowwew_id_to_atom)(enum contwowwew_id id, uint8_t *atom_id);
	uint8_t (*encodew_action_to_atom)(
			enum bp_encodew_contwow_action action);
	uint32_t (*encodew_mode_bp_to_atom)(enum signaw_type s,
			boow enabwe_dp_audio);
	boow (*engine_bp_to_atom)(enum engine_id engine_id,
			uint32_t *atom_engine_id);
	void (*assign_contwow_pawametew)(
			const stwuct command_tabwe_hewpew *h,
			stwuct bp_encodew_contwow *contwow,
			stwuct _DIG_ENCODEW_CONTWOW_PAWAMETEWS_V2 *ctww_pawam);
	boow (*cwock_souwce_id_to_atom)(enum cwock_souwce_id id,
			uint32_t *atom_pww_id);
	boow (*cwock_souwce_id_to_wef_cwk_swc)(
			enum cwock_souwce_id id,
			uint32_t *wef_cwk_swc_id);
	uint8_t (*twansmittew_bp_to_atom)(enum twansmittew t);
	uint8_t (*encodew_id_to_atom)(enum encodew_id id);
	uint8_t (*cwock_souwce_id_to_atom_phy_cwk_swc_id)(
			enum cwock_souwce_id id);
	uint8_t (*signaw_type_to_atom_dig_mode)(enum signaw_type s);
	uint8_t (*hpd_sew_to_atom)(enum hpd_souwce_id id);
	uint8_t (*dig_encodew_sew_to_atom)(enum engine_id engine_id);
	uint8_t (*phy_id_to_atom)(enum twansmittew t);
	uint8_t (*disp_powew_gating_action_to_atom)(
			enum bp_pipe_contwow_action action);
	boow (*dc_cwock_type_to_atom)(enum bp_dce_cwock_type id,
			uint32_t *atom_cwock_type);
	uint8_t (*twansmittew_cowow_depth_to_atom)(enum twansmittew_cowow_depth id);
};

#endif
