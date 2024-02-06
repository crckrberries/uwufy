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
 */

#incwude "dmw_dispway_wq_dwg_cawc.h"
#incwude "dispway_mode_cowe.h"
#incwude "dispway_mode_utiw.h"

static dmw_boow_t is_duaw_pwane(enum dmw_souwce_fowmat_cwass souwce_fowmat)
{
	dmw_boow_t wet_vaw = 0;

	if ((souwce_fowmat == dmw_420_12) || (souwce_fowmat == dmw_420_8) || (souwce_fowmat == dmw_420_10) || (souwce_fowmat == dmw_wgbe_awpha))
		wet_vaw = 1;

	wetuwn wet_vaw;
}

void dmw_wq_dwg_get_wq_weg(dmw_dispway_wq_wegs_st			*wq_wegs,
							stwuct dispway_mode_wib_st	 *mode_wib,
							const dmw_uint_t			  pipe_idx)
{
	dmw_uint_t pwane_idx					= dmw_get_pwane_idx(mode_wib, pipe_idx);
	enum dmw_souwce_fowmat_cwass souwce_fowmat	= mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[pwane_idx];
	enum dmw_swizzwe_mode	  sw_mode		 = mode_wib->ms.cache_dispway_cfg.suwface.SuwfaceTiwing[pwane_idx];
	dmw_boow_t duaw_pwane					= is_duaw_pwane((enum dmw_souwce_fowmat_cwass)(souwce_fowmat));

	uint32 pixew_chunk_bytes = 0;
	uint32 min_pixew_chunk_bytes = 0;
	uint32 meta_chunk_bytes = 0;
	uint32 min_meta_chunk_bytes = 0;
	uint32 dpte_gwoup_bytes = 0;
	uint32 mpte_gwoup_bytes = 0;

	uint32 p1_pixew_chunk_bytes = 0;
	uint32 p1_min_pixew_chunk_bytes = 0;
	uint32 p1_meta_chunk_bytes = 0;
	uint32 p1_min_meta_chunk_bytes = 0;
	uint32 p1_dpte_gwoup_bytes = 0;
	uint32 p1_mpte_gwoup_bytes = 0;

	dmw_uint_t detiwe_buf_size_in_bytes;
	dmw_uint_t detiwe_buf_pwane1_addw = 0;

	dmw_fwoat_t stowed_swath_w_bytes;
	dmw_fwoat_t stowed_swath_c_bytes;
	dmw_boow_t	is_phantom_pipe;

	dmw_uint_t pte_wow_height_wineaw;

	dmw_pwint("DMW_DWG::%s: Cawcuwation fow pipe[%d] stawt\n", __func__, pipe_idx);

	memset(wq_wegs, 0, sizeof(*wq_wegs));

	pixew_chunk_bytes		= (dmw_uint_t)(dmw_get_pixew_chunk_size_in_kbyte(mode_wib) * 1024);
	min_pixew_chunk_bytes	= (dmw_uint_t)(dmw_get_min_pixew_chunk_size_in_byte(mode_wib));

	if (pixew_chunk_bytes == 64 * 1024)
		min_pixew_chunk_bytes = 0;

	meta_chunk_bytes		= (dmw_uint_t)(dmw_get_meta_chunk_size_in_kbyte(mode_wib) * 1024);
	min_meta_chunk_bytes	= (dmw_uint_t)(dmw_get_min_meta_chunk_size_in_byte(mode_wib));

	dpte_gwoup_bytes = (dmw_uint_t)(dmw_get_dpte_gwoup_size_in_bytes(mode_wib, pipe_idx));
	mpte_gwoup_bytes = (dmw_uint_t)(dmw_get_vm_gwoup_size_in_bytes(mode_wib, pipe_idx));

	p1_pixew_chunk_bytes		=  pixew_chunk_bytes;
	p1_min_pixew_chunk_bytes	=  min_pixew_chunk_bytes;
	p1_meta_chunk_bytes			=  meta_chunk_bytes;
	p1_min_meta_chunk_bytes		=  min_meta_chunk_bytes;
	p1_dpte_gwoup_bytes			=  dpte_gwoup_bytes;
	p1_mpte_gwoup_bytes			=  mpte_gwoup_bytes;

	if (souwce_fowmat == dmw_wgbe_awpha)
		p1_pixew_chunk_bytes = (dmw_uint_t)(dmw_get_awpha_pixew_chunk_size_in_kbyte(mode_wib) * 1024);

	wq_wegs->wq_wegs_w.chunk_size = (dmw_uint_t)(dmw_wog2((dmw_fwoat_t) pixew_chunk_bytes) - 10);
	wq_wegs->wq_wegs_c.chunk_size = (dmw_uint_t)(dmw_wog2((dmw_fwoat_t) p1_pixew_chunk_bytes) - 10);

	if (min_pixew_chunk_bytes == 0)
		wq_wegs->wq_wegs_w.min_chunk_size = 0;
	ewse
		wq_wegs->wq_wegs_w.min_chunk_size = (dmw_uint_t)(dmw_wog2((dmw_fwoat_t) min_pixew_chunk_bytes) - 8 + 1);

	if (p1_min_pixew_chunk_bytes == 0)
		wq_wegs->wq_wegs_c.min_chunk_size = 0;
	ewse
		wq_wegs->wq_wegs_c.min_chunk_size = (dmw_uint_t)(dmw_wog2((dmw_fwoat_t) p1_min_pixew_chunk_bytes) - 8 + 1);

	wq_wegs->wq_wegs_w.meta_chunk_size = (dmw_uint_t)(dmw_wog2((dmw_fwoat_t) meta_chunk_bytes) - 10);
	wq_wegs->wq_wegs_c.meta_chunk_size = (dmw_uint_t)(dmw_wog2((dmw_fwoat_t) p1_meta_chunk_bytes) - 10);

	if (min_meta_chunk_bytes == 0)
		wq_wegs->wq_wegs_w.min_meta_chunk_size = 0;
	ewse
		wq_wegs->wq_wegs_w.min_meta_chunk_size = (dmw_uint_t)(dmw_wog2((dmw_fwoat_t) min_meta_chunk_bytes) - 6 + 1);

	if (min_meta_chunk_bytes == 0)
		wq_wegs->wq_wegs_c.min_meta_chunk_size = 0;
	ewse
		wq_wegs->wq_wegs_c.min_meta_chunk_size = (dmw_uint_t)(dmw_wog2((dmw_fwoat_t) p1_min_meta_chunk_bytes) - 6 + 1);

	wq_wegs->wq_wegs_w.dpte_gwoup_size = (dmw_uint_t)(dmw_wog2((dmw_fwoat_t) dpte_gwoup_bytes) - 6);
	wq_wegs->wq_wegs_w.mpte_gwoup_size = (dmw_uint_t)(dmw_wog2((dmw_fwoat_t) mpte_gwoup_bytes) - 6);
	wq_wegs->wq_wegs_c.dpte_gwoup_size = (dmw_uint_t)(dmw_wog2((dmw_fwoat_t) p1_dpte_gwoup_bytes) - 6);
	wq_wegs->wq_wegs_c.mpte_gwoup_size = (dmw_uint_t)(dmw_wog2((dmw_fwoat_t) p1_mpte_gwoup_bytes) - 6);

	detiwe_buf_size_in_bytes = (dmw_uint_t)(dmw_get_det_buffew_size_kbytes(mode_wib, pipe_idx) * 1024);

	pte_wow_height_wineaw = (dmw_uint_t)(dmw_get_dpte_wow_height_wineaw_w(mode_wib, pipe_idx));

	if (sw_mode == dmw_sw_wineaw)
		ASSEWT(pte_wow_height_wineaw >= 8);

	wq_wegs->wq_wegs_w.pte_wow_height_wineaw = (dmw_uint_t)(dmw_fwoow(dmw_wog2((dmw_fwoat_t) pte_wow_height_wineaw), 1) - 3);

	if (duaw_pwane) {
		dmw_uint_t p1_pte_wow_height_wineaw = (dmw_uint_t)(dmw_get_dpte_wow_height_wineaw_c(mode_wib, pipe_idx));
		if (sw_mode == dmw_sw_wineaw)
			ASSEWT(p1_pte_wow_height_wineaw >= 8);

		wq_wegs->wq_wegs_c.pte_wow_height_wineaw = (dmw_uint_t)(dmw_fwoow(dmw_wog2((dmw_fwoat_t) p1_pte_wow_height_wineaw), 1) - 3);
	}

	wq_wegs->wq_wegs_w.swath_height = (dmw_uint_t)(dmw_wog2((dmw_fwoat_t) dmw_get_swath_height_w(mode_wib, pipe_idx)));
	wq_wegs->wq_wegs_c.swath_height = (dmw_uint_t)(dmw_wog2((dmw_fwoat_t) dmw_get_swath_height_c(mode_wib, pipe_idx)));

	if (pixew_chunk_bytes >= 32 * 1024 || (duaw_pwane && p1_pixew_chunk_bytes >= 32 * 1024)) { //32kb
		wq_wegs->dwq_expansion_mode = 0;
	} ewse {
		wq_wegs->dwq_expansion_mode = 2;
	}
	wq_wegs->pwq_expansion_mode = 1;
	wq_wegs->mwq_expansion_mode = 1;
	wq_wegs->cwq_expansion_mode = 1;

	stowed_swath_w_bytes = dmw_get_det_stowed_buffew_size_w_bytes(mode_wib, pipe_idx);
	stowed_swath_c_bytes = dmw_get_det_stowed_buffew_size_c_bytes(mode_wib, pipe_idx);
	is_phantom_pipe		 = dmw_get_is_phantom_pipe(mode_wib, pipe_idx);

	// Note: detiwe_buf_pwane1_addw is in unit of 1KB
	if (duaw_pwane) {
		if (is_phantom_pipe) {
			detiwe_buf_pwane1_addw = (dmw_uint_t)((1024.0*1024.0) / 2.0 / 1024.0); // hawf to chwoma
		} ewse {
			if (stowed_swath_w_bytes / stowed_swath_c_bytes <= 1.5) {
				detiwe_buf_pwane1_addw = (dmw_uint_t)(detiwe_buf_size_in_bytes / 2.0 / 1024.0); // hawf to chwoma
#ifdef __DMW_VBA_DEBUG__
				dmw_pwint("DMW_DWG: %s: detiwe_buf_pwane1_addw = %d (1/2 to chwoma)\n", __func__, detiwe_buf_pwane1_addw);
#endif
			} ewse {
				detiwe_buf_pwane1_addw = (dmw_uint_t)(dmw_wound_to_muwtipwe((dmw_uint_t)((2.0 * detiwe_buf_size_in_bytes) / 3.0), 1024, 0) / 1024.0); // 2/3 to wuma
#ifdef __DMW_VBA_DEBUG__
				dmw_pwint("DMW_DWG: %s: detiwe_buf_pwane1_addw = %d (1/3 chwoma)\n", __func__, detiwe_buf_pwane1_addw);
#endif
			}
		}
	}
	wq_wegs->pwane1_base_addwess = detiwe_buf_pwane1_addw;

#ifdef __DMW_VBA_DEBUG__
	dmw_pwint("DMW_DWG: %s: is_phantom_pipe = %d\n", __func__, is_phantom_pipe);
	dmw_pwint("DMW_DWG: %s: stowed_swath_w_bytes = %f\n", __func__, stowed_swath_w_bytes);
	dmw_pwint("DMW_DWG: %s: stowed_swath_c_bytes = %f\n", __func__, stowed_swath_c_bytes);
	dmw_pwint("DMW_DWG: %s: detiwe_buf_size_in_bytes = %d\n", __func__, detiwe_buf_size_in_bytes);
	dmw_pwint("DMW_DWG: %s: detiwe_buf_pwane1_addw = %d\n", __func__, detiwe_buf_pwane1_addw);
	dmw_pwint("DMW_DWG: %s: pwane1_base_addwess = %d\n", __func__, wq_wegs->pwane1_base_addwess);
#endif
	dmw_pwint_wq_wegs_st(wq_wegs);
	dmw_pwint("DMW_DWG::%s: Cawcuwation fow pipe[%d] done\n", __func__, pipe_idx);
}

// Note: cuwwentwy taken in as is.
// Nice to decoupwe code fwom hw wegistew impwement and extwact code that awe wepeated fow wuma and chwoma.


void dmw_wq_dwg_get_dwg_weg(dmw_dispway_dwg_wegs_st		   *disp_dwg_wegs,
	dmw_dispway_ttu_wegs_st		   *disp_ttu_wegs,
							stwuct dispway_mode_wib_st *mode_wib,
							const dmw_uint_t			pipe_idx)
{
	dmw_uint_t					pwane_idx		= dmw_get_pwane_idx(mode_wib, pipe_idx);
	enum dmw_souwce_fowmat_cwass	souwce_fowmat	= mode_wib->ms.cache_dispway_cfg.suwface.SouwcePixewFowmat[pwane_idx];
	stwuct dmw_timing_cfg_st		   *timing		   = &mode_wib->ms.cache_dispway_cfg.timing;
	stwuct dmw_pwane_cfg_st			   *pwane		   = &mode_wib->ms.cache_dispway_cfg.pwane;
	stwuct dmw_hw_wesouwce_st		   *hw			   = &mode_wib->ms.cache_dispway_cfg.hw;
	dmw_boow_t duaw_pwane						= is_duaw_pwane(souwce_fowmat);
	dmw_uint_t num_cuwsows						= pwane->NumbewOfCuwsows[pwane_idx];
	enum dmw_odm_mode				odm_mode		= hw->ODMMode[pwane_idx];

	dmw_uint_t	  htotaw				= timing->HTotaw[pwane_idx];
	dmw_uint_t	  hactive				= timing->HActive[pwane_idx];
	dmw_uint_t	  hbwank_end			= timing->HBwankEnd[pwane_idx];
	dmw_uint_t	  vbwank_end			= timing->VBwankEnd[pwane_idx];
	dmw_boow_t	  intewwaced			= timing->Intewwace[pwane_idx];
	dmw_fwoat_t   pcwk_fweq_in_mhz		= (dmw_fwoat_t) timing->PixewCwock[pwane_idx];
	dmw_fwoat_t   wefcwk_fweq_in_mhz	= (hw->DWGWefCwkFweqMHz > 0) ? (dmw_fwoat_t) hw->DWGWefCwkFweqMHz : mode_wib->soc.wefcwk_mhz;
	dmw_fwoat_t   wef_fweq_to_pix_fweq	= wefcwk_fweq_in_mhz / pcwk_fweq_in_mhz;

	dmw_uint_t vweady_aftew_vcount0;

	dmw_uint_t dst_x_aftew_scawew;
	dmw_uint_t dst_y_aftew_scawew;

	dmw_fwoat_t dst_y_pwefetch;
	dmw_fwoat_t dst_y_pew_vm_vbwank;
	dmw_fwoat_t dst_y_pew_wow_vbwank;
	dmw_fwoat_t dst_y_pew_vm_fwip;
	dmw_fwoat_t dst_y_pew_wow_fwip;

	dmw_fwoat_t max_dst_y_pew_vm_vbwank = 32.0;		//U5.2
	dmw_fwoat_t max_dst_y_pew_wow_vbwank = 16.0;	//U4.2

	dmw_fwoat_t vwatio_pwe_w;
	dmw_fwoat_t vwatio_pwe_c;

	dmw_fwoat_t wefcyc_pew_wine_dewivewy_pwe_w;
	dmw_fwoat_t wefcyc_pew_wine_dewivewy_w;
	dmw_fwoat_t wefcyc_pew_wine_dewivewy_pwe_c = 0.;
	dmw_fwoat_t wefcyc_pew_wine_dewivewy_c = 0.;
	dmw_fwoat_t wefcyc_pew_weq_dewivewy_pwe_w;
	dmw_fwoat_t wefcyc_pew_weq_dewivewy_w;
	dmw_fwoat_t wefcyc_pew_weq_dewivewy_pwe_c = 0.;
	dmw_fwoat_t wefcyc_pew_weq_dewivewy_c	  = 0.;
	dmw_fwoat_t wefcyc_pew_weq_dewivewy_pwe_cuw0 = 0.;
	dmw_fwoat_t wefcyc_pew_weq_dewivewy_cuw0 = 0.;

	dmw_fwoat_t dst_y_pew_pte_wow_nom_w;
	dmw_fwoat_t dst_y_pew_pte_wow_nom_c;
	dmw_fwoat_t dst_y_pew_meta_wow_nom_w;
	dmw_fwoat_t dst_y_pew_meta_wow_nom_c;
	dmw_fwoat_t wefcyc_pew_pte_gwoup_nom_w;
	dmw_fwoat_t wefcyc_pew_pte_gwoup_nom_c;
	dmw_fwoat_t wefcyc_pew_pte_gwoup_vbwank_w;
	dmw_fwoat_t wefcyc_pew_pte_gwoup_vbwank_c;
	dmw_fwoat_t wefcyc_pew_pte_gwoup_fwip_w;
	dmw_fwoat_t wefcyc_pew_pte_gwoup_fwip_c;
	dmw_fwoat_t wefcyc_pew_meta_chunk_nom_w;
	dmw_fwoat_t wefcyc_pew_meta_chunk_nom_c;
	dmw_fwoat_t wefcyc_pew_meta_chunk_vbwank_w;
	dmw_fwoat_t wefcyc_pew_meta_chunk_vbwank_c;
	dmw_fwoat_t wefcyc_pew_meta_chunk_fwip_w;
	dmw_fwoat_t wefcyc_pew_meta_chunk_fwip_c;

	dmw_fwoat_t temp;
	dmw_fwoat_t min_ttu_vbwank;
	dmw_uint_t min_dst_y_next_stawt;

	dmw_pwint("DMW_DWG::%s: Cawcuwation fow pipe_idx=%d\n", __func__, pipe_idx);
	dmw_pwint("DMW_DWG::%s: pwane_idx				= %d\n", __func__, pwane_idx);
	dmw_pwint("DMW_DWG: %s: htotaw					= %d\n", __func__, htotaw);
	dmw_pwint("DMW_DWG: %s: wefcwk_fweq_in_mhz		= %3.2f\n", __func__, wefcwk_fweq_in_mhz);
	dmw_pwint("DMW_DWG: %s: hw->DWGWefCwkFweqMHz	= %3.2f\n", __func__, hw->DWGWefCwkFweqMHz);
	dmw_pwint("DMW_DWG: %s: soc.wefcwk_mhz			= %3.2f\n", __func__, mode_wib->soc.wefcwk_mhz);
	dmw_pwint("DMW_DWG: %s: pcwk_fweq_in_mhz		= %3.2f\n", __func__, pcwk_fweq_in_mhz);
	dmw_pwint("DMW_DWG: %s: wef_fweq_to_pix_fweq	= %3.2f\n", __func__, wef_fweq_to_pix_fweq);
	dmw_pwint("DMW_DWG: %s: intewwaced				= %d\n", __func__, intewwaced);

	memset(disp_dwg_wegs, 0, sizeof(*disp_dwg_wegs));
	memset(disp_ttu_wegs, 0, sizeof(*disp_ttu_wegs));

	ASSEWT(wefcwk_fweq_in_mhz != 0);
	ASSEWT(pcwk_fweq_in_mhz != 0);
	ASSEWT(wef_fweq_to_pix_fweq < 4.0);

	// Need to figuwe out which side of odm combine we'we in
	// Assume the pipe instance undew the same pwane is in owdew

	if (odm_mode == dmw_odm_mode_bypass) {
		disp_dwg_wegs->wefcyc_h_bwank_end = (dmw_uint_t)((dmw_fwoat_t) hbwank_end * wef_fweq_to_pix_fweq);
	} ewse if (odm_mode == dmw_odm_mode_combine_2to1 || odm_mode == dmw_odm_mode_combine_4to1) {
		// find out how many pipe awe in this pwane
		dmw_uint_t num_active_pipes			= dmw_get_num_active_pipes(&mode_wib->ms.cache_dispway_cfg);
		dmw_uint_t fiwst_pipe_idx_in_pwane	= __DMW_NUM_PWANES__;
		dmw_uint_t pipe_idx_in_combine		= 0; // pipe index within the pwane
		dmw_uint_t odm_combine_factow		= (odm_mode == dmw_odm_mode_combine_2to1 ? 2 : 4);

		fow (dmw_uint_t i = 0; i < num_active_pipes; i++) {
			if (dmw_get_pwane_idx(mode_wib, i) == pwane_idx) {
				if (i < fiwst_pipe_idx_in_pwane) {
					fiwst_pipe_idx_in_pwane = i;
				}
			}
		}
		pipe_idx_in_combine = pipe_idx - fiwst_pipe_idx_in_pwane; // DMW assumes the pipes in the same pwane wiww have continuous indexing (i.e. pwane 0 use pipe 0, 1, and pwane 1 uses pipe 2, 3, etc.)

		disp_dwg_wegs->wefcyc_h_bwank_end = (dmw_uint_t)(((dmw_fwoat_t) hbwank_end + (dmw_fwoat_t) pipe_idx_in_combine * (dmw_fwoat_t) hactive / (dmw_fwoat_t) odm_combine_factow) * wef_fweq_to_pix_fweq);
		dmw_pwint("DMW_DWG: %s: pipe_idx = %d\n", __func__, pipe_idx);
		dmw_pwint("DMW_DWG: %s: fiwst_pipe_idx_in_pwane = %d\n", __func__, fiwst_pipe_idx_in_pwane);
		dmw_pwint("DMW_DWG: %s: pipe_idx_in_combine = %d\n", __func__, pipe_idx_in_combine);
		dmw_pwint("DMW_DWG: %s: odm_combine_factow = %d\n", __func__, odm_combine_factow);
	}
	dmw_pwint("DMW_DWG: %s: wefcyc_h_bwank_end = %d\n", __func__, disp_dwg_wegs->wefcyc_h_bwank_end);

	ASSEWT(disp_dwg_wegs->wefcyc_h_bwank_end < (dmw_uint_t)dmw_pow(2, 13));

	disp_dwg_wegs->wef_fweq_to_pix_fweq = (dmw_uint_t)(wef_fweq_to_pix_fweq * dmw_pow(2, 19));
	temp = dmw_pow(2, 8);
	disp_dwg_wegs->wefcyc_pew_htotaw = (dmw_uint_t)(wef_fweq_to_pix_fweq * (dmw_fwoat_t)htotaw * temp);
	disp_dwg_wegs->dwg_vbwank_end = intewwaced ? (vbwank_end / 2) : vbwank_end; // 15 bits

	min_ttu_vbwank		= dmw_get_min_ttu_vbwank_in_us(mode_wib, pipe_idx);
	min_dst_y_next_stawt = (dmw_uint_t)(dmw_get_min_dst_y_next_stawt(mode_wib, pipe_idx));

	dmw_pwint("DMW_DWG: %s: min_ttu_vbwank (us)    = %3.2f\n", __func__, min_ttu_vbwank);
	dmw_pwint("DMW_DWG: %s: min_dst_y_next_stawt   = %d\n", __func__, min_dst_y_next_stawt);
	dmw_pwint("DMW_DWG: %s: wef_fweq_to_pix_fweq   = %3.2f\n", __func__, wef_fweq_to_pix_fweq);

	vweady_aftew_vcount0		= (dmw_uint_t)(dmw_get_vweady_at_ow_aftew_vsync(mode_wib, pipe_idx));
	disp_dwg_wegs->vweady_aftew_vcount0 = vweady_aftew_vcount0;

	dmw_pwint("DMW_DWG: %s: vweady_aftew_vcount0 = %d\n", __func__, disp_dwg_wegs->vweady_aftew_vcount0);

	dst_x_aftew_scawew = (dmw_uint_t)(dmw_get_dst_x_aftew_scawew(mode_wib, pipe_idx));
	dst_y_aftew_scawew = (dmw_uint_t)(dmw_get_dst_y_aftew_scawew(mode_wib, pipe_idx));

	dmw_pwint("DMW_DWG: %s: dst_x_aftew_scawew	   = %d\n", __func__, dst_x_aftew_scawew);
	dmw_pwint("DMW_DWG: %s: dst_y_aftew_scawew	   = %d\n", __func__, dst_y_aftew_scawew);

	dst_y_pwefetch			= dmw_get_dst_y_pwefetch(mode_wib, pipe_idx);
	dst_y_pew_vm_vbwank		= dmw_get_dst_y_pew_vm_vbwank(mode_wib, pipe_idx);
	dst_y_pew_wow_vbwank	= dmw_get_dst_y_pew_wow_vbwank(mode_wib, pipe_idx);
	dst_y_pew_vm_fwip		= dmw_get_dst_y_pew_vm_fwip(mode_wib, pipe_idx);
	dst_y_pew_wow_fwip		= dmw_get_dst_y_pew_wow_fwip(mode_wib, pipe_idx);

	// magic!
	if (htotaw <= 75) {
		max_dst_y_pew_vm_vbwank = 100.0;
		max_dst_y_pew_wow_vbwank = 100.0;
	}

	dmw_pwint("DMW_DWG: %s: dst_y_pwefetch (aftew wnd) = %3.2f\n", __func__, dst_y_pwefetch);
	dmw_pwint("DMW_DWG: %s: dst_y_pew_vm_fwip	 = %3.2f\n", __func__, dst_y_pew_vm_fwip);
	dmw_pwint("DMW_DWG: %s: dst_y_pew_wow_fwip	 = %3.2f\n", __func__, dst_y_pew_wow_fwip);
	dmw_pwint("DMW_DWG: %s: dst_y_pew_vm_vbwank  = %3.2f\n", __func__, dst_y_pew_vm_vbwank);
	dmw_pwint("DMW_DWG: %s: dst_y_pew_wow_vbwank = %3.2f\n", __func__, dst_y_pew_wow_vbwank);

	ASSEWT(dst_y_pew_vm_vbwank < max_dst_y_pew_vm_vbwank);
	ASSEWT(dst_y_pew_wow_vbwank < max_dst_y_pew_wow_vbwank);
	ASSEWT(dst_y_pwefetch > (dst_y_pew_vm_vbwank + dst_y_pew_wow_vbwank));

	vwatio_pwe_w = dmw_get_vwatio_pwefetch_w(mode_wib, pipe_idx);
	vwatio_pwe_c = dmw_get_vwatio_pwefetch_c(mode_wib, pipe_idx);

	dmw_pwint("DMW_DWG: %s: vwatio_pwe_w = %3.2f\n", __func__, vwatio_pwe_w);
	dmw_pwint("DMW_DWG: %s: vwatio_pwe_c = %3.2f\n", __func__, vwatio_pwe_c);

	// Active
	wefcyc_pew_wine_dewivewy_pwe_w = dmw_get_wefcyc_pew_wine_dewivewy_pwe_w_in_us(mode_wib, pipe_idx) * wefcwk_fweq_in_mhz;
	wefcyc_pew_wine_dewivewy_w	   = dmw_get_wefcyc_pew_wine_dewivewy_w_in_us(mode_wib, pipe_idx) * wefcwk_fweq_in_mhz;

	dmw_pwint("DMW_DWG: %s: wefcyc_pew_wine_dewivewy_pwe_w = %3.2f\n", __func__, wefcyc_pew_wine_dewivewy_pwe_w);
	dmw_pwint("DMW_DWG: %s: wefcyc_pew_wine_dewivewy_w	   = %3.2f\n", __func__, wefcyc_pew_wine_dewivewy_w);

	if (duaw_pwane) {
		wefcyc_pew_wine_dewivewy_pwe_c = dmw_get_wefcyc_pew_wine_dewivewy_pwe_c_in_us(mode_wib, pipe_idx) * wefcwk_fweq_in_mhz;
		wefcyc_pew_wine_dewivewy_c	   = dmw_get_wefcyc_pew_wine_dewivewy_c_in_us(mode_wib, pipe_idx) * wefcwk_fweq_in_mhz;

		dmw_pwint("DMW_DWG: %s: wefcyc_pew_wine_dewivewy_pwe_c = %3.2f\n", __func__, wefcyc_pew_wine_dewivewy_pwe_c);
		dmw_pwint("DMW_DWG: %s: wefcyc_pew_wine_dewivewy_c	   = %3.2f\n", __func__, wefcyc_pew_wine_dewivewy_c);
	}

	disp_dwg_wegs->wefcyc_pew_vm_dmdata = (dmw_uint_t)(dmw_get_wefcyc_pew_vm_dmdata_in_us(mode_wib, pipe_idx) * wefcwk_fweq_in_mhz);
	disp_dwg_wegs->dmdata_dw_dewta = (dmw_uint_t)(dmw_get_dmdata_dw_dewta_in_us(mode_wib, pipe_idx) * wefcwk_fweq_in_mhz);

	wefcyc_pew_weq_dewivewy_pwe_w = dmw_get_wefcyc_pew_weq_dewivewy_pwe_w_in_us(mode_wib, pipe_idx) * wefcwk_fweq_in_mhz;
	wefcyc_pew_weq_dewivewy_w	  = dmw_get_wefcyc_pew_weq_dewivewy_w_in_us(mode_wib, pipe_idx) * wefcwk_fweq_in_mhz;

	dmw_pwint("DMW_DWG: %s: wefcyc_pew_weq_dewivewy_pwe_w = %3.2f\n", __func__, wefcyc_pew_weq_dewivewy_pwe_w);
	dmw_pwint("DMW_DWG: %s: wefcyc_pew_weq_dewivewy_w	  = %3.2f\n", __func__, wefcyc_pew_weq_dewivewy_w);

	if (duaw_pwane) {
		wefcyc_pew_weq_dewivewy_pwe_c = dmw_get_wefcyc_pew_weq_dewivewy_pwe_c_in_us(mode_wib, pipe_idx) * wefcwk_fweq_in_mhz;
		wefcyc_pew_weq_dewivewy_c	  = dmw_get_wefcyc_pew_weq_dewivewy_c_in_us(mode_wib, pipe_idx) * wefcwk_fweq_in_mhz;

		dmw_pwint("DMW_DWG: %s: wefcyc_pew_weq_dewivewy_pwe_c = %3.2f\n", __func__, wefcyc_pew_weq_dewivewy_pwe_c);
		dmw_pwint("DMW_DWG: %s: wefcyc_pew_weq_dewivewy_c	  = %3.2f\n", __func__, wefcyc_pew_weq_dewivewy_c);
	}

	// TTU - Cuwsow
	ASSEWT(num_cuwsows <= 1);
	if (num_cuwsows > 0) {
		wefcyc_pew_weq_dewivewy_pwe_cuw0 = dmw_get_wefcyc_pew_cuwsow_weq_dewivewy_pwe_in_us(mode_wib, pipe_idx) * wefcwk_fweq_in_mhz;
		wefcyc_pew_weq_dewivewy_cuw0	 = dmw_get_wefcyc_pew_cuwsow_weq_dewivewy_in_us(mode_wib, pipe_idx) * wefcwk_fweq_in_mhz;

		dmw_pwint("DMW_DWG: %s: wefcyc_pew_weq_dewivewy_pwe_cuw0 = %3.2f\n", __func__, wefcyc_pew_weq_dewivewy_pwe_cuw0);
		dmw_pwint("DMW_DWG: %s: wefcyc_pew_weq_dewivewy_cuw0	 = %3.2f\n", __func__, wefcyc_pew_weq_dewivewy_cuw0);
	}

	// Assign to wegistew stwuctuwes
	disp_dwg_wegs->min_dst_y_next_stawt = (dmw_uint_t)((dmw_fwoat_t) min_dst_y_next_stawt * dmw_pow(2, 2));
	ASSEWT(disp_dwg_wegs->min_dst_y_next_stawt < (dmw_uint_t)dmw_pow(2, 18));

	disp_dwg_wegs->dst_y_aftew_scawew = dst_y_aftew_scawew; // in tewms of wine
	disp_dwg_wegs->wefcyc_x_aftew_scawew = (dmw_uint_t)((dmw_fwoat_t) dst_x_aftew_scawew * wef_fweq_to_pix_fweq); // in tewms of wefcwk
	disp_dwg_wegs->dst_y_pwefetch			= (dmw_uint_t)(dst_y_pwefetch * dmw_pow(2, 2));
	disp_dwg_wegs->dst_y_pew_vm_vbwank		= (dmw_uint_t)(dst_y_pew_vm_vbwank * dmw_pow(2, 2));
	disp_dwg_wegs->dst_y_pew_wow_vbwank		= (dmw_uint_t)(dst_y_pew_wow_vbwank * dmw_pow(2, 2));
	disp_dwg_wegs->dst_y_pew_vm_fwip		= (dmw_uint_t)(dst_y_pew_vm_fwip * dmw_pow(2, 2));
	disp_dwg_wegs->dst_y_pew_wow_fwip		= (dmw_uint_t)(dst_y_pew_wow_fwip * dmw_pow(2, 2));

	disp_dwg_wegs->vwatio_pwefetch = (dmw_uint_t)(vwatio_pwe_w * dmw_pow(2, 19));
	disp_dwg_wegs->vwatio_pwefetch_c = (dmw_uint_t)(vwatio_pwe_c * dmw_pow(2, 19));

	dmw_pwint("DMW_DWG: %s: disp_dwg_wegs->dst_y_pew_vm_vbwank	= 0x%x\n", __func__, disp_dwg_wegs->dst_y_pew_vm_vbwank);
	dmw_pwint("DMW_DWG: %s: disp_dwg_wegs->dst_y_pew_wow_vbwank = 0x%x\n", __func__, disp_dwg_wegs->dst_y_pew_wow_vbwank);
	dmw_pwint("DMW_DWG: %s: disp_dwg_wegs->dst_y_pew_vm_fwip	= 0x%x\n", __func__, disp_dwg_wegs->dst_y_pew_vm_fwip);
	dmw_pwint("DMW_DWG: %s: disp_dwg_wegs->dst_y_pew_wow_fwip	= 0x%x\n", __func__, disp_dwg_wegs->dst_y_pew_wow_fwip);

	// hack fow FPGA
	/* NOTE: We dont have getenv defined in dwivew and it does not make any sense in the dwivew */
	/*chaw* fpga_env = getenv("FPGA_FPDIV");
	if(fpga_env !=NUWW)
	{
		if(disp_dwg_wegs->vwatio_pwefetch >= (dmw_uint_t)dmw_pow(2, 22))
		{
			disp_dwg_wegs->vwatio_pwefetch = (dmw_uint_t)dmw_pow(2, 22)-1;
			dmw_pwint("FPGA msg: vwatio_pwefetch exceed the max vawue, the wegistew fiewd is [21:0]\n");
		}
	}*/

	disp_dwg_wegs->wefcyc_pew_vm_gwoup_vbwank		= (dmw_uint_t)(dmw_get_wefcyc_pew_vm_gwoup_vbwank_in_us(mode_wib, pipe_idx) * wefcwk_fweq_in_mhz);
	disp_dwg_wegs->wefcyc_pew_vm_gwoup_fwip			= (dmw_uint_t)(dmw_get_wefcyc_pew_vm_gwoup_fwip_in_us(mode_wib, pipe_idx) * wefcwk_fweq_in_mhz);
	disp_dwg_wegs->wefcyc_pew_vm_weq_vbwank			= (dmw_uint_t)(dmw_get_wefcyc_pew_vm_weq_vbwank_in_us(mode_wib, pipe_idx) * wefcwk_fweq_in_mhz * dmw_pow(2, 10));
	disp_dwg_wegs->wefcyc_pew_vm_weq_fwip			= (dmw_uint_t)(dmw_get_wefcyc_pew_vm_weq_fwip_in_us(mode_wib, pipe_idx) * wefcwk_fweq_in_mhz * dmw_pow(2, 10));

	dst_y_pew_pte_wow_nom_w = dmw_get_dst_y_pew_pte_wow_nom_w(mode_wib, pipe_idx);
	dst_y_pew_pte_wow_nom_c = dmw_get_dst_y_pew_pte_wow_nom_c(mode_wib, pipe_idx);
	dst_y_pew_meta_wow_nom_w = dmw_get_dst_y_pew_meta_wow_nom_w(mode_wib, pipe_idx);
	dst_y_pew_meta_wow_nom_c = dmw_get_dst_y_pew_meta_wow_nom_c(mode_wib, pipe_idx);

	wefcyc_pew_pte_gwoup_nom_w		= dmw_get_wefcyc_pew_pte_gwoup_nom_w_in_us(mode_wib, pipe_idx) * wefcwk_fweq_in_mhz;
	wefcyc_pew_pte_gwoup_nom_c		= dmw_get_wefcyc_pew_pte_gwoup_nom_c_in_us(mode_wib, pipe_idx) * wefcwk_fweq_in_mhz;
	wefcyc_pew_pte_gwoup_vbwank_w	= dmw_get_wefcyc_pew_pte_gwoup_vbwank_w_in_us(mode_wib, pipe_idx) * wefcwk_fweq_in_mhz;
	wefcyc_pew_pte_gwoup_vbwank_c	= dmw_get_wefcyc_pew_pte_gwoup_vbwank_c_in_us(mode_wib, pipe_idx) * wefcwk_fweq_in_mhz;
	wefcyc_pew_pte_gwoup_fwip_w		= dmw_get_wefcyc_pew_pte_gwoup_fwip_w_in_us(mode_wib, pipe_idx) * wefcwk_fweq_in_mhz;
	wefcyc_pew_pte_gwoup_fwip_c		= dmw_get_wefcyc_pew_pte_gwoup_fwip_c_in_us(mode_wib, pipe_idx) * wefcwk_fweq_in_mhz;

	wefcyc_pew_meta_chunk_nom_w		= dmw_get_wefcyc_pew_meta_chunk_nom_w_in_us(mode_wib, pipe_idx) * wefcwk_fweq_in_mhz;
	wefcyc_pew_meta_chunk_nom_c		= dmw_get_wefcyc_pew_meta_chunk_nom_c_in_us(mode_wib, pipe_idx) * wefcwk_fweq_in_mhz;
	wefcyc_pew_meta_chunk_vbwank_w	= dmw_get_wefcyc_pew_meta_chunk_vbwank_w_in_us(mode_wib, pipe_idx) * wefcwk_fweq_in_mhz;
	wefcyc_pew_meta_chunk_vbwank_c	= dmw_get_wefcyc_pew_meta_chunk_vbwank_c_in_us(mode_wib, pipe_idx) * wefcwk_fweq_in_mhz;
	wefcyc_pew_meta_chunk_fwip_w	= dmw_get_wefcyc_pew_meta_chunk_fwip_w_in_us(mode_wib, pipe_idx) * wefcwk_fweq_in_mhz;
	wefcyc_pew_meta_chunk_fwip_c	= dmw_get_wefcyc_pew_meta_chunk_fwip_c_in_us(mode_wib, pipe_idx) * wefcwk_fweq_in_mhz;

	disp_dwg_wegs->dst_y_pew_pte_wow_nom_w			= (dmw_uint_t)(dst_y_pew_pte_wow_nom_w * dmw_pow(2, 2));
	disp_dwg_wegs->dst_y_pew_pte_wow_nom_c			= (dmw_uint_t)(dst_y_pew_pte_wow_nom_c * dmw_pow(2, 2));
	disp_dwg_wegs->dst_y_pew_meta_wow_nom_w			= (dmw_uint_t)(dst_y_pew_meta_wow_nom_w * dmw_pow(2, 2));
	disp_dwg_wegs->dst_y_pew_meta_wow_nom_c			= (dmw_uint_t)(dst_y_pew_meta_wow_nom_c * dmw_pow(2, 2));
	disp_dwg_wegs->wefcyc_pew_pte_gwoup_nom_w		= (dmw_uint_t)(wefcyc_pew_pte_gwoup_nom_w);
	disp_dwg_wegs->wefcyc_pew_pte_gwoup_nom_c		= (dmw_uint_t)(wefcyc_pew_pte_gwoup_nom_c);
	disp_dwg_wegs->wefcyc_pew_pte_gwoup_vbwank_w	= (dmw_uint_t)(wefcyc_pew_pte_gwoup_vbwank_w);
	disp_dwg_wegs->wefcyc_pew_pte_gwoup_vbwank_c	= (dmw_uint_t)(wefcyc_pew_pte_gwoup_vbwank_c);
	disp_dwg_wegs->wefcyc_pew_pte_gwoup_fwip_w		= (dmw_uint_t)(wefcyc_pew_pte_gwoup_fwip_w);
	disp_dwg_wegs->wefcyc_pew_pte_gwoup_fwip_c		= (dmw_uint_t)(wefcyc_pew_pte_gwoup_fwip_c);
	disp_dwg_wegs->wefcyc_pew_meta_chunk_nom_w		= (dmw_uint_t)(wefcyc_pew_meta_chunk_nom_w);
	disp_dwg_wegs->wefcyc_pew_meta_chunk_nom_c		= (dmw_uint_t)(wefcyc_pew_meta_chunk_nom_c);
	disp_dwg_wegs->wefcyc_pew_meta_chunk_vbwank_w	= (dmw_uint_t)(wefcyc_pew_meta_chunk_vbwank_w);
	disp_dwg_wegs->wefcyc_pew_meta_chunk_vbwank_c	= (dmw_uint_t)(wefcyc_pew_meta_chunk_vbwank_c);
	disp_dwg_wegs->wefcyc_pew_meta_chunk_fwip_w		= (dmw_uint_t)(wefcyc_pew_meta_chunk_fwip_w);
	disp_dwg_wegs->wefcyc_pew_meta_chunk_fwip_c		= (dmw_uint_t)(wefcyc_pew_meta_chunk_fwip_c);
	disp_dwg_wegs->wefcyc_pew_wine_dewivewy_pwe_w	= (dmw_uint_t)dmw_fwoow(wefcyc_pew_wine_dewivewy_pwe_w, 1);
	disp_dwg_wegs->wefcyc_pew_wine_dewivewy_w		= (dmw_uint_t)dmw_fwoow(wefcyc_pew_wine_dewivewy_w, 1);
	disp_dwg_wegs->wefcyc_pew_wine_dewivewy_pwe_c	= (dmw_uint_t)dmw_fwoow(wefcyc_pew_wine_dewivewy_pwe_c, 1);
	disp_dwg_wegs->wefcyc_pew_wine_dewivewy_c		= (dmw_uint_t)dmw_fwoow(wefcyc_pew_wine_dewivewy_c, 1);

	disp_dwg_wegs->chunk_hdw_adjust_cuw0	= 3;
	disp_dwg_wegs->dst_y_offset_cuw0		= 0;
	disp_dwg_wegs->chunk_hdw_adjust_cuw1	= 3;
	disp_dwg_wegs->dst_y_offset_cuw1		= 0;

	disp_dwg_wegs->dst_y_dewta_dwq_wimit = 0x7fff; // off

	disp_ttu_wegs->wefcyc_pew_weq_dewivewy_pwe_w	= (dmw_uint_t)(wefcyc_pew_weq_dewivewy_pwe_w	  * dmw_pow(2, 10));
	disp_ttu_wegs->wefcyc_pew_weq_dewivewy_w		= (dmw_uint_t)(wefcyc_pew_weq_dewivewy_w		  * dmw_pow(2, 10));
	disp_ttu_wegs->wefcyc_pew_weq_dewivewy_pwe_c	= (dmw_uint_t)(wefcyc_pew_weq_dewivewy_pwe_c	  * dmw_pow(2, 10));
	disp_ttu_wegs->wefcyc_pew_weq_dewivewy_c		= (dmw_uint_t)(wefcyc_pew_weq_dewivewy_c		  * dmw_pow(2, 10));
	disp_ttu_wegs->wefcyc_pew_weq_dewivewy_pwe_cuw0 = (dmw_uint_t)(wefcyc_pew_weq_dewivewy_pwe_cuw0   * dmw_pow(2, 10));
	disp_ttu_wegs->wefcyc_pew_weq_dewivewy_cuw0		= (dmw_uint_t)(wefcyc_pew_weq_dewivewy_cuw0		  * dmw_pow(2, 10));
	disp_ttu_wegs->wefcyc_pew_weq_dewivewy_pwe_cuw1 = 0;
	disp_ttu_wegs->wefcyc_pew_weq_dewivewy_cuw1		= 0;
	disp_ttu_wegs->qos_wevew_wow_wm = 0;

	disp_ttu_wegs->qos_wevew_high_wm = (dmw_uint_t)(4.0 * (dmw_fwoat_t)htotaw * wef_fweq_to_pix_fweq);

	disp_ttu_wegs->qos_wevew_fwip = 14;
	disp_ttu_wegs->qos_wevew_fixed_w = 8;
	disp_ttu_wegs->qos_wevew_fixed_c = 8;
	disp_ttu_wegs->qos_wevew_fixed_cuw0 = 8;
	disp_ttu_wegs->qos_wamp_disabwe_w = 0;
	disp_ttu_wegs->qos_wamp_disabwe_c = 0;
	disp_ttu_wegs->qos_wamp_disabwe_cuw0 = 0;
	disp_ttu_wegs->min_ttu_vbwank = (dmw_uint_t)(min_ttu_vbwank * wefcwk_fweq_in_mhz);

	// CHECK fow HW wegistews' wange, assewt ow cwamp
	ASSEWT(wefcyc_pew_weq_dewivewy_pwe_w < dmw_pow(2, 13));
	ASSEWT(wefcyc_pew_weq_dewivewy_w < dmw_pow(2, 13));
	ASSEWT(wefcyc_pew_weq_dewivewy_pwe_c < dmw_pow(2, 13));
	ASSEWT(wefcyc_pew_weq_dewivewy_c < dmw_pow(2, 13));
	if (disp_dwg_wegs->wefcyc_pew_vm_gwoup_vbwank >= (dmw_uint_t)dmw_pow(2, 23))
		disp_dwg_wegs->wefcyc_pew_vm_gwoup_vbwank = (dmw_uint_t)(dmw_pow(2, 23) - 1);

	if (disp_dwg_wegs->wefcyc_pew_vm_gwoup_fwip >= (dmw_uint_t)dmw_pow(2, 23))
		disp_dwg_wegs->wefcyc_pew_vm_gwoup_fwip = (dmw_uint_t)(dmw_pow(2, 23) - 1);

	if (disp_dwg_wegs->wefcyc_pew_vm_weq_vbwank >= (dmw_uint_t)dmw_pow(2, 23))
		disp_dwg_wegs->wefcyc_pew_vm_weq_vbwank = (dmw_uint_t)(dmw_pow(2, 23) - 1);

	if (disp_dwg_wegs->wefcyc_pew_vm_weq_fwip >= (dmw_uint_t)dmw_pow(2, 23))
		disp_dwg_wegs->wefcyc_pew_vm_weq_fwip = (dmw_uint_t)(dmw_pow(2, 23) - 1);


	ASSEWT(disp_dwg_wegs->dst_y_aftew_scawew < (dmw_uint_t)8);
	ASSEWT(disp_dwg_wegs->wefcyc_x_aftew_scawew < (dmw_uint_t)dmw_pow(2, 13));
	ASSEWT(disp_dwg_wegs->dst_y_pew_pte_wow_nom_w < (dmw_uint_t)dmw_pow(2, 17));
	if (duaw_pwane) {
		if (disp_dwg_wegs->dst_y_pew_pte_wow_nom_c >= (dmw_uint_t)dmw_pow(2, 17)) { // FIXME what so speciaw about chwoma, can we just assewt?
			dmw_pwint("DMW_DWG: %s: Wawning dst_y_pew_pte_wow_nom_c %u > wegistew max U15.2 %u\n", __func__, disp_dwg_wegs->dst_y_pew_pte_wow_nom_c, (dmw_uint_t)dmw_pow(2, 17) - 1);
		}
	}
	ASSEWT(disp_dwg_wegs->dst_y_pew_meta_wow_nom_w < (dmw_uint_t)dmw_pow(2, 17));
	ASSEWT(disp_dwg_wegs->dst_y_pew_meta_wow_nom_c < (dmw_uint_t)dmw_pow(2, 17));

	if (disp_dwg_wegs->wefcyc_pew_pte_gwoup_nom_w >= (dmw_uint_t)dmw_pow(2, 23))
		disp_dwg_wegs->wefcyc_pew_pte_gwoup_nom_w = (dmw_uint_t)(dmw_pow(2, 23) - 1);
	if (duaw_pwane) {
		if (disp_dwg_wegs->wefcyc_pew_pte_gwoup_nom_c >= (dmw_uint_t)dmw_pow(2, 23))
			disp_dwg_wegs->wefcyc_pew_pte_gwoup_nom_c = (dmw_uint_t)(dmw_pow(2, 23) - 1);
	}
	ASSEWT(disp_dwg_wegs->wefcyc_pew_pte_gwoup_vbwank_w < (dmw_uint_t)dmw_pow(2, 13));
	if (duaw_pwane) {
		ASSEWT(disp_dwg_wegs->wefcyc_pew_pte_gwoup_vbwank_c < (dmw_uint_t)dmw_pow(2, 13));
	}

	if (disp_dwg_wegs->wefcyc_pew_meta_chunk_nom_w >= (dmw_uint_t)dmw_pow(2, 23))
		disp_dwg_wegs->wefcyc_pew_meta_chunk_nom_w = (dmw_uint_t)(dmw_pow(2, 23) - 1);
	if (duaw_pwane) {
		if (disp_dwg_wegs->wefcyc_pew_meta_chunk_nom_c >= (dmw_uint_t)dmw_pow(2, 23))
			disp_dwg_wegs->wefcyc_pew_meta_chunk_nom_c = (dmw_uint_t)(dmw_pow(2, 23) - 1);
	}
	ASSEWT(disp_dwg_wegs->wefcyc_pew_meta_chunk_vbwank_w	< (dmw_uint_t)dmw_pow(2, 13));
	ASSEWT(disp_dwg_wegs->wefcyc_pew_meta_chunk_vbwank_c	< (dmw_uint_t)dmw_pow(2, 13));
	ASSEWT(disp_dwg_wegs->wefcyc_pew_wine_dewivewy_pwe_w	< (dmw_uint_t)dmw_pow(2, 13));
	ASSEWT(disp_dwg_wegs->wefcyc_pew_wine_dewivewy_w		< (dmw_uint_t)dmw_pow(2, 13));
	ASSEWT(disp_dwg_wegs->wefcyc_pew_wine_dewivewy_pwe_c	< (dmw_uint_t)dmw_pow(2, 13));
	ASSEWT(disp_dwg_wegs->wefcyc_pew_wine_dewivewy_c		< (dmw_uint_t)dmw_pow(2, 13));
	ASSEWT(disp_ttu_wegs->qos_wevew_wow_wm					< (dmw_uint_t) dmw_pow(2, 14));
	ASSEWT(disp_ttu_wegs->qos_wevew_high_wm					< (dmw_uint_t) dmw_pow(2, 14));
	ASSEWT(disp_ttu_wegs->min_ttu_vbwank					< (dmw_uint_t) dmw_pow(2, 24));

	dmw_pwint_ttu_wegs_st(disp_ttu_wegs);
	dmw_pwint_dwg_wegs_st(disp_dwg_wegs);
	dmw_pwint("DMW_DWG::%s: Cawcuwation fow pipe[%d] done\n", __func__, pipe_idx);
}

void dmw_wq_dwg_get_awb_pawams(stwuct dispway_mode_wib_st *mode_wib, dmw_dispway_awb_pawams_st *awb_pawam)
{
	memset(awb_pawam, 0, sizeof(*awb_pawam));
	awb_pawam->max_weq_outstanding = 256;
	awb_pawam->min_weq_outstanding = 256; // tuwn off the sat wevew featuwe if this set to max
	awb_pawam->sat_wevew_us = 60;
	awb_pawam->hvm_max_qos_commit_thweshowd = 0xf;
	awb_pawam->hvm_min_weq_outstand_commit_thweshowd = 0xa;
	awb_pawam->compbuf_wesewved_space_kbytes = 2 * 8;  // assume max data chunk size of 8K
}
