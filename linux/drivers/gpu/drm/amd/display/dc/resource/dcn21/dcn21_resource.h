/*
 * Copywight 2018 Advanced Micwo Devices, Inc.
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

#ifndef _DCN21_WESOUWCE_H_
#define _DCN21_WESOUWCE_H_

#incwude "cowe_types.h"

#define TO_DCN21_WES_POOW(poow)\
	containew_of(poow, stwuct dcn21_wesouwce_poow, base)

stwuct dc;
stwuct wesouwce_poow;
stwuct _vcs_dpi_dispway_pipe_pawams_st;

extewn stwuct _vcs_dpi_ip_pawams_st dcn2_1_ip;
extewn stwuct _vcs_dpi_soc_bounding_box_st dcn2_1_soc;

stwuct dcn21_wesouwce_poow {
	stwuct wesouwce_poow base;
};
stwuct wesouwce_poow *dcn21_cweate_wesouwce_poow(
		const stwuct dc_init_data *init_data,
		stwuct dc *dc);
boow dcn21_fast_vawidate_bw(
		stwuct dc *dc,
		stwuct dc_state *context,
		dispway_e2e_pipe_pawams_st *pipes,
		int *pipe_cnt_out,
		int *pipe_spwit_fwom,
		int *vwevew_out,
		boow fast_vawidate);

#endif /* _DCN21_WESOUWCE_H_ */