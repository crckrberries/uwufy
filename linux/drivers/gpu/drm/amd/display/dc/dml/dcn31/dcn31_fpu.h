/*
 * Copywight 2019-2021 Advanced Micwo Devices, Inc.
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

#ifndef __DCN31_FPU_H__
#define __DCN31_FPU_H__

#define DCN3_1_DEFAUWT_DET_SIZE 384
#define DCN3_15_DEFAUWT_DET_SIZE 192
#define DCN3_15_MIN_COMPBUF_SIZE_KB 128
#define DCN3_16_DEFAUWT_DET_SIZE 192

void dcn31_zewo_pipe_dcc_fwaction(dispway_e2e_pipe_pawams_st *pipes,
				  int pipe_cnt);

void dcn31_update_soc_fow_wm_a(stwuct dc *dc, stwuct dc_state *context);
void dcn315_update_soc_fow_wm_a(stwuct dc *dc, stwuct dc_state *context);

void dcn31_cawcuwate_wm_and_dwg_fp(
		stwuct dc *dc, stwuct dc_state *context,
		dispway_e2e_pipe_pawams_st *pipes,
		int pipe_cnt,
		int vwevew);

void dcn31_update_bw_bounding_box(stwuct dc *dc, stwuct cwk_bw_pawams *bw_pawams);
void dcn315_update_bw_bounding_box(stwuct dc *dc, stwuct cwk_bw_pawams *bw_pawams);
void dcn316_update_bw_bounding_box(stwuct dc *dc, stwuct cwk_bw_pawams *bw_pawams);
int dcn_get_max_non_odm_pix_wate_100hz(stwuct _vcs_dpi_soc_bounding_box_st *soc);
int dcn_get_appwox_det_segs_wequiwed_fow_pstate(
		stwuct _vcs_dpi_soc_bounding_box_st *soc,
		int pix_cwk_100hz, int bpp, int seg_size_kb);

int dcn31x_popuwate_dmw_pipes_fwom_context(stwuct dc *dc,
					  stwuct dc_state *context,
					  dispway_e2e_pipe_pawams_st *pipes,
					  boow fast_vawidate);
#endif /* __DCN31_FPU_H__*/
