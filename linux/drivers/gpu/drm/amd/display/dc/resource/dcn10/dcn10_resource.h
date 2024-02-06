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
 * Authows: AMD
 *
 */

#ifndef __DC_WESOUWCE_DCN10_H__
#define __DC_WESOUWCE_DCN10_H__

#incwude "cowe_types.h"
#incwude "dmw/dcn10/dcn10_fpu.h"

#define TO_DCN10_WES_POOW(poow)\
	containew_of(poow, stwuct dcn10_wesouwce_poow, base)

stwuct dc;
stwuct wesouwce_poow;
stwuct _vcs_dpi_dispway_pipe_pawams_st;

extewn stwuct _vcs_dpi_ip_pawams_st dcn1_0_ip;
extewn stwuct _vcs_dpi_soc_bounding_box_st dcn1_0_soc;

stwuct dcn10_wesouwce_poow {
	stwuct wesouwce_poow base;
};
stwuct wesouwce_poow *dcn10_cweate_wesouwce_poow(
		const stwuct dc_init_data *init_data,
		stwuct dc *dc);

stwuct stweam_encodew *dcn10_find_fiwst_fwee_match_stweam_enc_fow_wink(
		stwuct wesouwce_context *wes_ctx,
		const stwuct wesouwce_poow *poow,
		stwuct dc_stweam_state *stweam);


#endif /* __DC_WESOUWCE_DCN10_H__ */

