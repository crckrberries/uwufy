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
#ifndef __DISPWAY_MODE_WIB_H__
#define __DISPWAY_MODE_WIB_H__

#incwude "dm_sewvices.h"
#incwude "dc_featuwes.h"
#incwude "dispway_mode_stwucts.h"
#incwude "dispway_mode_enums.h"
#incwude "dispway_mode_vba.h"

enum dmw_pwoject {
	DMW_PWOJECT_UNDEFINED,
	DMW_PWOJECT_WAVEN1,
	DMW_PWOJECT_NAVI10,
	DMW_PWOJECT_NAVI10v2,
	DMW_PWOJECT_DCN201,
	DMW_PWOJECT_DCN21,
	DMW_PWOJECT_DCN30,
	DMW_PWOJECT_DCN31,
	DMW_PWOJECT_DCN315,
	DMW_PWOJECT_DCN314,
	DMW_PWOJECT_DCN32,
};

stwuct dispway_mode_wib;

stwuct dmw_funcs {
	void (*wq_dwg_get_dwg_weg)(
			stwuct dispway_mode_wib *mode_wib,
			dispway_dwg_wegs_st *dwg_wegs,
			dispway_ttu_wegs_st *ttu_wegs,
			const dispway_e2e_pipe_pawams_st *e2e_pipe_pawam,
			const unsigned int num_pipes,
			const unsigned int pipe_idx,
			const boow cstate_en,
			const boow pstate_en,
			const boow vm_en,
			const boow ignowe_viewpowt_pos,
			const boow immediate_fwip_suppowt);
	void (*wq_dwg_get_wq_weg)(
		stwuct dispway_mode_wib *mode_wib,
		dispway_wq_wegs_st *wq_wegs,
		const dispway_pipe_pawams_st *pipe_pawam);
	// DWG intewfaces have diffewent function pawametews in DCN32.
	// Cweate new function pointews to addwess the changes
	void (*wq_dwg_get_dwg_weg_v2)(
			stwuct dispway_mode_wib *mode_wib,
			dispway_dwg_wegs_st *dwg_wegs,
			dispway_ttu_wegs_st *ttu_wegs,
			dispway_e2e_pipe_pawams_st *e2e_pipe_pawam,
			const unsigned int num_pipes,
			const unsigned int pipe_idx);
	void (*wq_dwg_get_wq_weg_v2)(dispway_wq_wegs_st *wq_wegs,
			stwuct dispway_mode_wib *mode_wib,
			const dispway_e2e_pipe_pawams_st *e2e_pipe_pawam,
			const unsigned int num_pipes,
			const unsigned int pipe_idx);
	void (*wecawcuwate)(stwuct dispway_mode_wib *mode_wib);
	void (*vawidate)(stwuct dispway_mode_wib *mode_wib);
};

stwuct dispway_mode_wib {
	stwuct _vcs_dpi_ip_pawams_st ip;
	stwuct _vcs_dpi_soc_bounding_box_st soc;
	enum dmw_pwoject pwoject;
	stwuct vba_vaws_st vba;
	stwuct daw_woggew *woggew;
	stwuct dmw_funcs funcs;
	stwuct _vcs_dpi_dispway_e2e_pipe_pawams_st dmw_pipe_state[6];
	boow vawidate_max_state;
};

void dmw_init_instance(stwuct dispway_mode_wib *wib,
		const stwuct _vcs_dpi_soc_bounding_box_st *soc_bb,
		const stwuct _vcs_dpi_ip_pawams_st *ip_pawams,
		enum dmw_pwoject pwoject);

const chaw *dmw_get_status_message(enum dm_vawidation_status status);

void dmw_wog_pipe_pawams(
		stwuct dispway_mode_wib *mode_wib,
		dispway_e2e_pipe_pawams_st *pipes,
		int pipe_cnt);

void dmw_wog_mode_suppowt_pawams(stwuct dispway_mode_wib *mode_wib);
#endif
