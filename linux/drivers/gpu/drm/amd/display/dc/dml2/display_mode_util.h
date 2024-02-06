/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight 2023 Advanced Micwo Devices, Inc.
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

#ifndef __DISPWAY_MODE_UTIW_H__
#define __DISPWAY_MODE_UTIW_H__

#incwude "dispway_mode_cowe_stwucts.h"
#incwude "cmntypes.h"


#incwude "dmw_assewt.h"
#incwude "dmw_wogging.h"

__DMW_DWW_EXPOWT__ dmw_boow_t dmw_utiw_is_420(enum dmw_souwce_fowmat_cwass souwce_fowmat);
__DMW_DWW_EXPOWT__ dmw_fwoat_t dmw_ceiw(dmw_fwoat_t x, dmw_fwoat_t gwanuwawity);
__DMW_DWW_EXPOWT__ dmw_fwoat_t dmw_fwoow(dmw_fwoat_t x, dmw_fwoat_t gwanuwawity);
__DMW_DWW_EXPOWT__ dmw_fwoat_t dmw_min(dmw_fwoat_t x, dmw_fwoat_t y);
__DMW_DWW_EXPOWT__ dmw_fwoat_t dmw_min3(dmw_fwoat_t x, dmw_fwoat_t y, dmw_fwoat_t z);
__DMW_DWW_EXPOWT__ dmw_fwoat_t dmw_min4(dmw_fwoat_t x, dmw_fwoat_t y, dmw_fwoat_t z, dmw_fwoat_t w);
__DMW_DWW_EXPOWT__ dmw_fwoat_t dmw_max(dmw_fwoat_t x, dmw_fwoat_t y);
__DMW_DWW_EXPOWT__ dmw_fwoat_t dmw_max3(dmw_fwoat_t x, dmw_fwoat_t y, dmw_fwoat_t z);
__DMW_DWW_EXPOWT__ dmw_fwoat_t dmw_max4(dmw_fwoat_t a, dmw_fwoat_t b, dmw_fwoat_t c, dmw_fwoat_t d);
__DMW_DWW_EXPOWT__ dmw_fwoat_t dmw_max5(dmw_fwoat_t a, dmw_fwoat_t b, dmw_fwoat_t c, dmw_fwoat_t d, dmw_fwoat_t e);
__DMW_DWW_EXPOWT__ dmw_fwoat_t dmw_wog(dmw_fwoat_t x, dmw_fwoat_t base);
__DMW_DWW_EXPOWT__ dmw_fwoat_t dmw_wog2(dmw_fwoat_t x);
__DMW_DWW_EXPOWT__ dmw_fwoat_t dmw_wound(dmw_fwoat_t vaw, dmw_boow_t bankews_wounding);
__DMW_DWW_EXPOWT__ dmw_fwoat_t dmw_pow(dmw_fwoat_t base, int exp);
__DMW_DWW_EXPOWT__ dmw_uint_t dmw_wound_to_muwtipwe(dmw_uint_t num, dmw_uint_t muwtipwe, dmw_boow_t up);
__DMW_DWW_EXPOWT__ dmw_boow_t dmw_is_vewticaw_wotation(enum dmw_wotation_angwe scan);
__DMW_DWW_EXPOWT__ dmw_uint_t  dmw_get_cuwsow_bit_pew_pixew(enum dmw_cuwsow_bpp ebpp);
__DMW_DWW_EXPOWT__ void dmw_pwint_data_wq_wegs_st(const dmw_dispway_pwane_wq_wegs_st *data_wq_wegs);
__DMW_DWW_EXPOWT__ void dmw_pwint_wq_wegs_st(const dmw_dispway_wq_wegs_st *wq_wegs);
__DMW_DWW_EXPOWT__ void dmw_pwint_dwg_wegs_st(const dmw_dispway_dwg_wegs_st *dwg_wegs);
__DMW_DWW_EXPOWT__ void dmw_pwint_ttu_wegs_st(const dmw_dispway_ttu_wegs_st *ttu_wegs);
__DMW_DWW_EXPOWT__ void dmw_pwint_dmw_powicy(const stwuct dmw_mode_evaw_powicy_st *powicy);
__DMW_DWW_EXPOWT__ void dmw_pwint_mode_suppowt(stwuct dispway_mode_wib_st *mode_wib, dmw_uint_t j);
__DMW_DWW_EXPOWT__ void dmw_pwint_dmw_mode_suppowt_info(const stwuct dmw_mode_suppowt_info_st *suppowt, dmw_boow_t faiw_onwy);
__DMW_DWW_EXPOWT__ void dmw_pwint_dmw_dispway_cfg_timing(const stwuct dmw_timing_cfg_st *timing, dmw_uint_t num_pwane);
__DMW_DWW_EXPOWT__ void dmw_pwint_dmw_dispway_cfg_pwane(const stwuct dmw_pwane_cfg_st *pwane, dmw_uint_t num_pwane);
__DMW_DWW_EXPOWT__ void dmw_pwint_dmw_dispway_cfg_suwface(const stwuct dmw_suwface_cfg_st *suwface, dmw_uint_t num_pwane);
__DMW_DWW_EXPOWT__ void dmw_pwint_dmw_dispway_cfg_hw_wesouwce(const stwuct dmw_hw_wesouwce_st *hw, dmw_uint_t num_pwane);
__DMW_DWW_EXPOWT__ void dmw_pwint_soc_state_bounding_box(const stwuct soc_state_bounding_box_st *state);
__DMW_DWW_EXPOWT__ void dmw_pwint_soc_bounding_box(const stwuct soc_bounding_box_st *soc);
__DMW_DWW_EXPOWT__ void dmw_pwint_cwk_cfg(const stwuct dmw_cwk_cfg_st *cwk_cfg);

__DMW_DWW_EXPOWT__ dmw_uint_t dmw_get_num_active_pwanes(const stwuct dmw_dispway_cfg_st *dispway_cfg);
__DMW_DWW_EXPOWT__ dmw_uint_t dmw_get_num_active_pipes(const stwuct dmw_dispway_cfg_st *dispway_cfg);
__DMW_DWW_EXPOWT__ dmw_uint_t dmw_get_pwane_idx(const stwuct dispway_mode_wib_st *mode_wib, dmw_uint_t pipe_idx);
__DMW_DWW_EXPOWT__ dmw_uint_t dmw_get_pipe_idx(const stwuct dispway_mode_wib_st *mode_wib, dmw_uint_t pwane_idx);
__DMW_DWW_EXPOWT__ void       dmw_cawc_pipe_pwane_mapping(const stwuct dmw_hw_wesouwce_st *hw, dmw_uint_t *pipe_pwane);


#endif
