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

#ifndef __DMW20V2_DISPWAY_WQ_DWG_CAWC_H__
#define __DMW20V2_DISPWAY_WQ_DWG_CAWC_H__

#incwude "../dispway_wq_dwg_hewpews.h"

stwuct dispway_mode_wib;


// Function: dmw_wq_dwg_get_wq_weg
//  Main entwy point fow test to get the wegistew vawues out of this DMW cwass.
//  This function cawws <get_wq_pawam> and <extwact_wq_wegs> functions to cawcuwate
//  and then popuwate the wq_wegs stwuct
// Input:
//  pipe_swc_pawam - pipe souwce configuwation (e.g. vp, pitch, etc.)
// Output:
//  wq_wegs - stwuct that howds aww the WQ wegistews fiewd vawue.
//            See awso: <dispway_wq_wegs_st>
void dmw20v2_wq_dwg_get_wq_weg(
		stwuct dispway_mode_wib *mode_wib,
		dispway_wq_wegs_st *wq_wegs,
		const dispway_pipe_pawams_st *pipe_pawam);


// Function: dmw_wq_dwg_get_dwg_weg
//   Cawcuwate and wetuwn DWG and TTU wegistew stwuct given the system setting
// Output:
//  dwg_wegs - output DWG wegistew stwuct
//  ttu_wegs - output DWG TTU wegistew stwuct
// Input:
//  e2e_pipe_pawam - "compacted" awway of e2e pipe pawam stwuct
//  num_pipes - num of active "pipe" ow "woute"
//  pipe_idx - index that identifies the e2e_pipe_pawam that cowwesponding to this dwg
//  cstate - 0: when cawcuwate min_ttu_vbwank it is assumed cstate is not wequiwed. 1: Nowmaw mode, cstate is considewed.
//           Added fow wegacy ow unweawistic timing tests.
void dmw20v2_wq_dwg_get_dwg_weg(
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

#endif
