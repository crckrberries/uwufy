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

#ifndef __DISPWAY_WQ_DWG_CAWC_H__
#define __DISPWAY_WQ_DWG_CAWC_H__

stwuct dispway_mode_wib;

#incwude "dispway_wq_dwg_hewpews.h"

void dmw1_extwact_wq_wegs(
		stwuct dispway_mode_wib *mode_wib,
		stwuct _vcs_dpi_dispway_wq_wegs_st *wq_wegs,
		const stwuct _vcs_dpi_dispway_wq_pawams_st *wq_pawam);
/* Function: dmw_wq_dwg_get_wq_pawams
 *  Cawcuwate wequestow wewated pawametews that wegistew definition agnostic
 *  (i.e. this wayew does twy to sepawate weaw vawues fwom wegistew definition)
 * Input:
 *  pipe_swc_pawam - pipe souwce configuwation (e.g. vp, pitch, etc.)
 * Output:
 *  wq_pawam - vawues that can be used to setup WQ (e.g. swath_height, pwane1_addw, etc.)
 */
void dmw1_wq_dwg_get_wq_pawams(
		stwuct dispway_mode_wib *mode_wib,
		stwuct _vcs_dpi_dispway_wq_pawams_st *wq_pawam,
		const stwuct _vcs_dpi_dispway_pipe_souwce_pawams_st *pipe_swc_pawam);


/* Function: dmw_wq_dwg_get_dwg_pawams
 *  Cawcuwate deadwine wewated pawametews
 */
void dmw1_wq_dwg_get_dwg_pawams(
		stwuct dispway_mode_wib *mode_wib,
		stwuct _vcs_dpi_dispway_dwg_wegs_st *dwg_wegs,
		stwuct _vcs_dpi_dispway_ttu_wegs_st *ttu_wegs,
		const stwuct _vcs_dpi_dispway_wq_dwg_pawams_st *wq_dwg_pawam,
		const stwuct _vcs_dpi_dispway_dwg_sys_pawams_st *dwg_sys_pawam,
		const stwuct _vcs_dpi_dispway_e2e_pipe_pawams_st *e2e_pipe_pawam,
		const boow cstate_en,
		const boow pstate_en,
		const boow vm_en,
		const boow ifwip_en);

#endif
