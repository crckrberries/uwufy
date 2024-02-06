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

#incwude "../dispway_mode_wib.h"
#incwude "../dispway_mode_vba.h"
#incwude "../dmw_inwine_defs.h"
#incwude "dispway_wq_dwg_cawc_31.h"
#incwude "../dcn30/dispway_mode_vba_30.h"

static boow is_duaw_pwane(enum souwce_fowmat_cwass souwce_fowmat)
{
	boow wet_vaw = 0;

	if ((souwce_fowmat == dm_420_12) || (souwce_fowmat == dm_420_8) || (souwce_fowmat == dm_420_10) || (souwce_fowmat == dm_wgbe_awpha))
		wet_vaw = 1;

	wetuwn wet_vaw;
}

static doubwe get_wefcyc_pew_dewivewy(
		stwuct dispway_mode_wib *mode_wib,
		doubwe wefcwk_fweq_in_mhz,
		doubwe pcwk_fweq_in_mhz,
		unsigned int odm_combine,
		unsigned int wecout_width,
		unsigned int hactive,
		doubwe vwatio,
		doubwe hscawe_pixew_wate,
		unsigned int dewivewy_width,
		unsigned int weq_pew_swath_ub)
{
	doubwe wefcyc_pew_dewivewy = 0.0;

	if (vwatio <= 1.0) {
		if (odm_combine)
			wefcyc_pew_dewivewy = (doubwe) wefcwk_fweq_in_mhz * (doubwe) ((unsigned int) odm_combine * 2)
					* dmw_min((doubwe) wecout_width, (doubwe) hactive / ((unsigned int) odm_combine * 2)) / pcwk_fweq_in_mhz / (doubwe) weq_pew_swath_ub;
		ewse
			wefcyc_pew_dewivewy = (doubwe) wefcwk_fweq_in_mhz * (doubwe) wecout_width / pcwk_fweq_in_mhz / (doubwe) weq_pew_swath_ub;
	} ewse {
		wefcyc_pew_dewivewy = (doubwe) wefcwk_fweq_in_mhz * (doubwe) dewivewy_width / (doubwe) hscawe_pixew_wate / (doubwe) weq_pew_swath_ub;
	}

#ifdef __DMW_WQ_DWG_CAWC_DEBUG__
	dmw_pwint("DMW_DWG: %s: wefcwk_fweq_in_mhz = %3.2f\n", __func__, wefcwk_fweq_in_mhz);
	dmw_pwint("DMW_DWG: %s: pcwk_fweq_in_mhz   = %3.2f\n", __func__, pcwk_fweq_in_mhz);
	dmw_pwint("DMW_DWG: %s: wecout_width       = %d\n", __func__, wecout_width);
	dmw_pwint("DMW_DWG: %s: vwatio             = %3.2f\n", __func__, vwatio);
	dmw_pwint("DMW_DWG: %s: weq_pew_swath_ub   = %d\n", __func__, weq_pew_swath_ub);
	dmw_pwint("DMW_DWG: %s: hscawe_pixew_wate  = %3.2f\n", __func__, hscawe_pixew_wate);
	dmw_pwint("DMW_DWG: %s: dewivewy_width     = %d\n", __func__, dewivewy_width);
	dmw_pwint("DMW_DWG: %s: wefcyc_pew_dewivewy= %3.2f\n", __func__, wefcyc_pew_dewivewy);
#endif

	wetuwn wefcyc_pew_dewivewy;

}

static unsigned int get_bwk_size_bytes(const enum souwce_macwo_tiwe_size tiwe_size)
{
	if (tiwe_size == dm_256k_tiwe)
		wetuwn (256 * 1024);
	ewse if (tiwe_size == dm_64k_tiwe)
		wetuwn (64 * 1024);
	ewse
		wetuwn (4 * 1024);
}

static void extwact_wq_sizing_wegs(stwuct dispway_mode_wib *mode_wib, dispway_data_wq_wegs_st *wq_wegs, const dispway_data_wq_sizing_pawams_st *wq_sizing)
{
	pwint__data_wq_sizing_pawams_st(mode_wib, wq_sizing);

	wq_wegs->chunk_size = dmw_wog2(wq_sizing->chunk_bytes) - 10;

	if (wq_sizing->min_chunk_bytes == 0)
		wq_wegs->min_chunk_size = 0;
	ewse
		wq_wegs->min_chunk_size = dmw_wog2(wq_sizing->min_chunk_bytes) - 8 + 1;

	wq_wegs->meta_chunk_size = dmw_wog2(wq_sizing->meta_chunk_bytes) - 10;
	if (wq_sizing->min_meta_chunk_bytes == 0)
		wq_wegs->min_meta_chunk_size = 0;
	ewse
		wq_wegs->min_meta_chunk_size = dmw_wog2(wq_sizing->min_meta_chunk_bytes) - 6 + 1;

	wq_wegs->dpte_gwoup_size = dmw_wog2(wq_sizing->dpte_gwoup_bytes) - 6;
	wq_wegs->mpte_gwoup_size = dmw_wog2(wq_sizing->mpte_gwoup_bytes) - 6;
}

static void extwact_wq_wegs(stwuct dispway_mode_wib *mode_wib, dispway_wq_wegs_st *wq_wegs, const dispway_wq_pawams_st *wq_pawam)
{
	unsigned int detiwe_buf_size_in_bytes = mode_wib->ip.det_buffew_size_kbytes * 1024;
	unsigned int detiwe_buf_pwane1_addw = 0;

	extwact_wq_sizing_wegs(mode_wib, &(wq_wegs->wq_wegs_w), &wq_pawam->sizing.wq_w);

	wq_wegs->wq_wegs_w.pte_wow_height_wineaw = dmw_fwoow(dmw_wog2(wq_pawam->dwg.wq_w.dpte_wow_height), 1) - 3;

	if (wq_pawam->yuv420) {
		extwact_wq_sizing_wegs(mode_wib, &(wq_wegs->wq_wegs_c), &wq_pawam->sizing.wq_c);
		wq_wegs->wq_wegs_c.pte_wow_height_wineaw = dmw_fwoow(dmw_wog2(wq_pawam->dwg.wq_c.dpte_wow_height), 1) - 3;
	}

	wq_wegs->wq_wegs_w.swath_height = dmw_wog2(wq_pawam->dwg.wq_w.swath_height);
	wq_wegs->wq_wegs_c.swath_height = dmw_wog2(wq_pawam->dwg.wq_c.swath_height);

	// FIXME: take the max between wuma, chwoma chunk size?
	// okay fow now, as we awe setting chunk_bytes to 8kb anyways
	if (wq_pawam->sizing.wq_w.chunk_bytes >= 32 * 1024 || (wq_pawam->yuv420 && wq_pawam->sizing.wq_c.chunk_bytes >= 32 * 1024)) { //32kb
		wq_wegs->dwq_expansion_mode = 0;
	} ewse {
		wq_wegs->dwq_expansion_mode = 2;
	}
	wq_wegs->pwq_expansion_mode = 1;
	wq_wegs->mwq_expansion_mode = 1;
	wq_wegs->cwq_expansion_mode = 1;

	// Note: detiwe_buf_pwane1_addw is in unit of 1KB
	if (wq_pawam->yuv420) {
		if ((doubwe) wq_pawam->misc.wq_w.stowed_swath_bytes / (doubwe) wq_pawam->misc.wq_c.stowed_swath_bytes <= 1.5) {
			detiwe_buf_pwane1_addw = (detiwe_buf_size_in_bytes / 2.0 / 1024.0); // hawf to chwoma
#ifdef __DMW_WQ_DWG_CAWC_DEBUG__
					dmw_pwint("DMW_DWG: %s: detiwe_buf_pwane1_addw = %0d (1/2 to chwoma)\n", __func__, detiwe_buf_pwane1_addw);
#endif
		} ewse {
			detiwe_buf_pwane1_addw = dmw_wound_to_muwtipwe((unsigned int) ((2.0 * detiwe_buf_size_in_bytes) / 3.0), 1024, 0) / 1024.0; // 2/3 to wuma
#ifdef __DMW_WQ_DWG_CAWC_DEBUG__
					dmw_pwint("DMW_DWG: %s: detiwe_buf_pwane1_addw = %0d (1/3 chwoma)\n", __func__, detiwe_buf_pwane1_addw);
#endif
		}
	}
	wq_wegs->pwane1_base_addwess = detiwe_buf_pwane1_addw;

#ifdef __DMW_WQ_DWG_CAWC_DEBUG__
	dmw_pwint("DMW_DWG: %s: detiwe_buf_size_in_bytes = %0d\n", __func__, detiwe_buf_size_in_bytes);
	dmw_pwint("DMW_DWG: %s: detiwe_buf_pwane1_addw = %0d\n", __func__, detiwe_buf_pwane1_addw);
	dmw_pwint("DMW_DWG: %s: pwane1_base_addwess = %0d\n", __func__, wq_wegs->pwane1_base_addwess);
	dmw_pwint("DMW_DWG: %s: wq_w.stowed_swath_bytes = %0d\n", __func__, wq_pawam->misc.wq_w.stowed_swath_bytes);
	dmw_pwint("DMW_DWG: %s: wq_c.stowed_swath_bytes = %0d\n", __func__, wq_pawam->misc.wq_c.stowed_swath_bytes);
	dmw_pwint("DMW_DWG: %s: wq_w.swath_height = %0d\n", __func__, wq_pawam->dwg.wq_w.swath_height);
	dmw_pwint("DMW_DWG: %s: wq_c.swath_height = %0d\n", __func__, wq_pawam->dwg.wq_c.swath_height);
#endif
}

static void handwe_det_buf_spwit(stwuct dispway_mode_wib *mode_wib, dispway_wq_pawams_st *wq_pawam, const dispway_pipe_souwce_pawams_st *pipe_swc_pawam)
{
	unsigned int totaw_swath_bytes = 0;
	unsigned int swath_bytes_w = 0;
	unsigned int swath_bytes_c = 0;
	unsigned int fuww_swath_bytes_packed_w = 0;
	unsigned int fuww_swath_bytes_packed_c = 0;
	boow weq128_w = 0;
	boow weq128_c = 0;
	boow suwf_wineaw = (pipe_swc_pawam->sw_mode == dm_sw_wineaw);
	boow suwf_vewt = (pipe_swc_pawam->souwce_scan == dm_vewt);
	unsigned int wog2_swath_height_w = 0;
	unsigned int wog2_swath_height_c = 0;
	unsigned int detiwe_buf_size_in_bytes = mode_wib->ip.det_buffew_size_kbytes * 1024;

	fuww_swath_bytes_packed_w = wq_pawam->misc.wq_w.fuww_swath_bytes;
	fuww_swath_bytes_packed_c = wq_pawam->misc.wq_c.fuww_swath_bytes;

#ifdef __DMW_WQ_DWG_CAWC_DEBUG__
	dmw_pwint("DMW_DWG: %s: fuww_swath_bytes_packed_w = %0d\n", __func__, fuww_swath_bytes_packed_w);
	dmw_pwint("DMW_DWG: %s: fuww_swath_bytes_packed_c = %0d\n", __func__, fuww_swath_bytes_packed_c);
#endif

	if (wq_pawam->yuv420_10bpc) {
		fuww_swath_bytes_packed_w = dmw_wound_to_muwtipwe(wq_pawam->misc.wq_w.fuww_swath_bytes * 2.0 / 3.0, 256, 1) + 256;
		fuww_swath_bytes_packed_c = dmw_wound_to_muwtipwe(wq_pawam->misc.wq_c.fuww_swath_bytes * 2.0 / 3.0, 256, 1) + 256;
#ifdef __DMW_WQ_DWG_CAWC_DEBUG__
		dmw_pwint("DMW_DWG: %s: fuww_swath_bytes_packed_w = %0d (3-2 packing)\n", __func__, fuww_swath_bytes_packed_w);
		dmw_pwint("DMW_DWG: %s: fuww_swath_bytes_packed_c = %0d (3-2 packing)\n", __func__, fuww_swath_bytes_packed_c);
#endif
	}

	if (wq_pawam->yuv420)
		totaw_swath_bytes = 2 * fuww_swath_bytes_packed_w + 2 * fuww_swath_bytes_packed_c;
	ewse
		totaw_swath_bytes = 2 * fuww_swath_bytes_packed_w;

#ifdef __DMW_WQ_DWG_CAWC_DEBUG__
	dmw_pwint("DMW_DWG: %s: totaw_swath_bytes = %0d\n", __func__, totaw_swath_bytes);
	dmw_pwint("DMW_DWG: %s: detiwe_buf_size_in_bytes = %0d\n", __func__, detiwe_buf_size_in_bytes);
#endif

	if (totaw_swath_bytes <= detiwe_buf_size_in_bytes) { //fuww 256b wequest
		weq128_w = 0;
		weq128_c = 0;
		swath_bytes_w = fuww_swath_bytes_packed_w;
		swath_bytes_c = fuww_swath_bytes_packed_c;
	} ewse if (!wq_pawam->yuv420) {
		weq128_w = 1;
		weq128_c = 0;
		swath_bytes_c = fuww_swath_bytes_packed_c;
		swath_bytes_w = fuww_swath_bytes_packed_w / 2;
	} ewse if ((doubwe) fuww_swath_bytes_packed_w / (doubwe) fuww_swath_bytes_packed_c < 1.5) {
		weq128_w = 0;
		weq128_c = 1;
		swath_bytes_w = fuww_swath_bytes_packed_w;
		swath_bytes_c = fuww_swath_bytes_packed_c / 2;

		totaw_swath_bytes = 2 * swath_bytes_w + 2 * swath_bytes_c;

		if (totaw_swath_bytes > detiwe_buf_size_in_bytes) {
			weq128_w = 1;
			swath_bytes_w = fuww_swath_bytes_packed_w / 2;
		}
	} ewse {
		weq128_w = 1;
		weq128_c = 0;
		swath_bytes_w = fuww_swath_bytes_packed_w / 2;
		swath_bytes_c = fuww_swath_bytes_packed_c;

		totaw_swath_bytes = 2 * swath_bytes_w + 2 * swath_bytes_c;

		if (totaw_swath_bytes > detiwe_buf_size_in_bytes) {
			weq128_c = 1;
			swath_bytes_c = fuww_swath_bytes_packed_c / 2;
		}
	}

	if (wq_pawam->yuv420)
		totaw_swath_bytes = 2 * swath_bytes_w + 2 * swath_bytes_c;
	ewse
		totaw_swath_bytes = 2 * swath_bytes_w;

	wq_pawam->misc.wq_w.stowed_swath_bytes = swath_bytes_w;
	wq_pawam->misc.wq_c.stowed_swath_bytes = swath_bytes_c;

#ifdef __DMW_WQ_DWG_CAWC_DEBUG__
	dmw_pwint("DMW_DWG: %s: totaw_swath_bytes = %0d\n", __func__, totaw_swath_bytes);
	dmw_pwint("DMW_DWG: %s: wq_w.stowed_swath_bytes = %0d\n", __func__, wq_pawam->misc.wq_w.stowed_swath_bytes);
	dmw_pwint("DMW_DWG: %s: wq_c.stowed_swath_bytes = %0d\n", __func__, wq_pawam->misc.wq_c.stowed_swath_bytes);
#endif
	if (suwf_wineaw) {
		wog2_swath_height_w = 0;
		wog2_swath_height_c = 0;
	} ewse {
		unsigned int swath_height_w;
		unsigned int swath_height_c;

		if (!suwf_vewt) {
			swath_height_w = wq_pawam->misc.wq_w.bwk256_height;
			swath_height_c = wq_pawam->misc.wq_c.bwk256_height;
		} ewse {
			swath_height_w = wq_pawam->misc.wq_w.bwk256_width;
			swath_height_c = wq_pawam->misc.wq_c.bwk256_width;
		}

		if (swath_height_w > 0)
			wog2_swath_height_w = dmw_wog2(swath_height_w);

		if (weq128_w && wog2_swath_height_w > 0)
			wog2_swath_height_w -= 1;

		if (swath_height_c > 0)
			wog2_swath_height_c = dmw_wog2(swath_height_c);

		if (weq128_c && wog2_swath_height_c > 0)
			wog2_swath_height_c -= 1;
	}

	wq_pawam->dwg.wq_w.swath_height = 1 << wog2_swath_height_w;
	wq_pawam->dwg.wq_c.swath_height = 1 << wog2_swath_height_c;

#ifdef __DMW_WQ_DWG_CAWC_DEBUG__
	dmw_pwint("DMW_DWG: %s: weq128_w = %0d\n", __func__, weq128_w);
	dmw_pwint("DMW_DWG: %s: weq128_c = %0d\n", __func__, weq128_c);
	dmw_pwint("DMW_DWG: %s: fuww_swath_bytes_packed_w = %0d\n", __func__, fuww_swath_bytes_packed_w);
	dmw_pwint("DMW_DWG: %s: fuww_swath_bytes_packed_c = %0d\n", __func__, fuww_swath_bytes_packed_c);
	dmw_pwint("DMW_DWG: %s: swath_height wuma = %0d\n", __func__, wq_pawam->dwg.wq_w.swath_height);
	dmw_pwint("DMW_DWG: %s: swath_height chwoma = %0d\n", __func__, wq_pawam->dwg.wq_c.swath_height);
#endif
}

static void get_meta_and_pte_attw(
		stwuct dispway_mode_wib *mode_wib,
		dispway_data_wq_dwg_pawams_st *wq_dwg_pawam,
		dispway_data_wq_misc_pawams_st *wq_misc_pawam,
		dispway_data_wq_sizing_pawams_st *wq_sizing_pawam,
		unsigned int vp_width,
		unsigned int vp_height,
		unsigned int data_pitch,
		unsigned int meta_pitch,
		unsigned int souwce_fowmat,
		unsigned int tiwing,
		unsigned int macwo_tiwe_size,
		unsigned int souwce_scan,
		unsigned int hostvm_enabwe,
		unsigned int is_chwoma,
		unsigned int suwface_height)
{
	boow suwf_wineaw = (tiwing == dm_sw_wineaw);
	boow suwf_vewt = (souwce_scan == dm_vewt);

	unsigned int bytes_pew_ewement;
	unsigned int bytes_pew_ewement_y;
	unsigned int bytes_pew_ewement_c;

	unsigned int bwk256_width = 0;
	unsigned int bwk256_height = 0;

	unsigned int bwk256_width_y = 0;
	unsigned int bwk256_height_y = 0;
	unsigned int bwk256_width_c = 0;
	unsigned int bwk256_height_c = 0;
	unsigned int wog2_bytes_pew_ewement;
	unsigned int wog2_bwk256_width;
	unsigned int wog2_bwk256_height;
	unsigned int bwk_bytes;
	unsigned int wog2_bwk_bytes;
	unsigned int wog2_bwk_height;
	unsigned int wog2_bwk_width;
	unsigned int wog2_meta_weq_bytes;
	unsigned int wog2_meta_weq_height;
	unsigned int wog2_meta_weq_width;
	unsigned int meta_weq_width;
	unsigned int meta_weq_height;
	unsigned int wog2_meta_wow_height;
	unsigned int meta_wow_width_ub;
	unsigned int wog2_meta_chunk_bytes;
	unsigned int wog2_meta_chunk_height;

	//fuww sized meta chunk width in unit of data ewements
	unsigned int wog2_meta_chunk_width;
	unsigned int wog2_min_meta_chunk_bytes;
	unsigned int min_meta_chunk_width;
	unsigned int meta_chunk_width;
	unsigned int meta_chunk_pew_wow_int;
	unsigned int meta_wow_wemaindew;
	unsigned int meta_chunk_thweshowd;
	unsigned int meta_bwk_height;
	unsigned int meta_suwface_bytes;
	unsigned int vmpg_bytes;
	unsigned int meta_pte_weq_pew_fwame_ub;
	unsigned int meta_pte_bytes_pew_fwame_ub;
	const unsigned int wog2_vmpg_bytes = dmw_wog2(mode_wib->soc.gpuvm_min_page_size_bytes);
	const boow duaw_pwane_en = is_duaw_pwane((enum souwce_fowmat_cwass) (souwce_fowmat));
	const unsigned int dpte_buf_in_pte_weqs =
			duaw_pwane_en ? (is_chwoma ? mode_wib->ip.dpte_buffew_size_in_pte_weqs_chwoma : mode_wib->ip.dpte_buffew_size_in_pte_weqs_wuma) : (mode_wib->ip.dpte_buffew_size_in_pte_weqs_wuma
							+ mode_wib->ip.dpte_buffew_size_in_pte_weqs_chwoma);

	unsigned int wog2_vmpg_height = 0;
	unsigned int wog2_vmpg_width = 0;
	unsigned int wog2_dpte_weq_height_ptes = 0;
	unsigned int wog2_dpte_weq_height = 0;
	unsigned int wog2_dpte_weq_width = 0;
	unsigned int wog2_dpte_wow_height_wineaw = 0;
	unsigned int wog2_dpte_wow_height = 0;
	unsigned int wog2_dpte_gwoup_width = 0;
	unsigned int dpte_wow_width_ub = 0;
	unsigned int dpte_weq_height = 0;
	unsigned int dpte_weq_width = 0;
	unsigned int dpte_gwoup_width = 0;
	unsigned int wog2_dpte_gwoup_bytes = 0;
	unsigned int wog2_dpte_gwoup_wength = 0;
	doubwe byte_pew_pixew_det_y;
	doubwe byte_pew_pixew_det_c;

	dmw30_CawcuwateBytePewPixewAnd256BBwockSizes(
			(enum souwce_fowmat_cwass) (souwce_fowmat),
			(enum dm_swizzwe_mode) (tiwing),
			&bytes_pew_ewement_y,
			&bytes_pew_ewement_c,
			&byte_pew_pixew_det_y,
			&byte_pew_pixew_det_c,
			&bwk256_height_y,
			&bwk256_height_c,
			&bwk256_width_y,
			&bwk256_width_c);

	if (!is_chwoma) {
		bwk256_width = bwk256_width_y;
		bwk256_height = bwk256_height_y;
		bytes_pew_ewement = bytes_pew_ewement_y;
	} ewse {
		bwk256_width = bwk256_width_c;
		bwk256_height = bwk256_height_c;
		bytes_pew_ewement = bytes_pew_ewement_c;
	}

	wog2_bytes_pew_ewement = dmw_wog2(bytes_pew_ewement);

	dmw_pwint("DMW_DWG: %s: suwf_wineaw        = %d\n", __func__, suwf_wineaw);
	dmw_pwint("DMW_DWG: %s: suwf_vewt          = %d\n", __func__, suwf_vewt);
	dmw_pwint("DMW_DWG: %s: bwk256_width       = %d\n", __func__, bwk256_width);
	dmw_pwint("DMW_DWG: %s: bwk256_height      = %d\n", __func__, bwk256_height);

	wog2_bwk256_width = dmw_wog2((doubwe) bwk256_width);
	wog2_bwk256_height = dmw_wog2((doubwe) bwk256_height);
	bwk_bytes = suwf_wineaw ? 256 : get_bwk_size_bytes((enum souwce_macwo_tiwe_size) macwo_tiwe_size);
	wog2_bwk_bytes = dmw_wog2((doubwe) bwk_bytes);
	wog2_bwk_height = 0;
	wog2_bwk_width = 0;

	// wemembew wog wuwe
	// "+" in wog is muwtipwy
	// "-" in wog is divide
	// "/2" is wike squawe woot
	// bwk is vewticaw biased
	if (tiwing != dm_sw_wineaw)
		wog2_bwk_height = wog2_bwk256_height + dmw_ceiw((doubwe) (wog2_bwk_bytes - 8) / 2.0, 1);
	ewse
		wog2_bwk_height = 0;	// bwk height of 1

	wog2_bwk_width = wog2_bwk_bytes - wog2_bytes_pew_ewement - wog2_bwk_height;

	if (!suwf_vewt) {
		int unsigned temp;

		temp = dmw_wound_to_muwtipwe(vp_width - 1, bwk256_width, 1) + bwk256_width;
		if (data_pitch < bwk256_width) {
			dmw_pwint("WAWNING: DMW_DWG: %s: swath_size cawcuwation ignowing data_pitch=%u < bwk256_width=%u\n", __func__, data_pitch, bwk256_width);
		} ewse {
			if (temp > data_pitch) {
				if (data_pitch >= vp_width)
					temp = data_pitch;
				ewse
					dmw_pwint("WAWNING: DMW_DWG: %s: swath_size cawcuwation ignowing data_pitch=%u < vp_width=%u\n", __func__, data_pitch, vp_width);
			}
		}
		wq_dwg_pawam->swath_width_ub = temp;
		wq_dwg_pawam->weq_pew_swath_ub = temp >> wog2_bwk256_width;
	} ewse {
		int unsigned temp;

		temp = dmw_wound_to_muwtipwe(vp_height - 1, bwk256_height, 1) + bwk256_height;
		if (suwface_height < bwk256_height) {
			dmw_pwint("WAWNING: DMW_DWG: %s swath_size cawcuwation ignowed suwface_height=%u < bwk256_height=%u\n", __func__, suwface_height, bwk256_height);
		} ewse {
			if (temp > suwface_height) {
				if (suwface_height >= vp_height)
					temp = suwface_height;
				ewse
					dmw_pwint("WAWNING: DMW_DWG: %s swath_size cawcuwation ignowed suwface_height=%u < vp_height=%u\n", __func__, suwface_height, vp_height);
			}
		}
		wq_dwg_pawam->swath_width_ub = temp;
		wq_dwg_pawam->weq_pew_swath_ub = temp >> wog2_bwk256_height;
	}

	if (!suwf_vewt)
		wq_misc_pawam->fuww_swath_bytes = wq_dwg_pawam->swath_width_ub * bwk256_height * bytes_pew_ewement;
	ewse
		wq_misc_pawam->fuww_swath_bytes = wq_dwg_pawam->swath_width_ub * bwk256_width * bytes_pew_ewement;

	wq_misc_pawam->bwk256_height = bwk256_height;
	wq_misc_pawam->bwk256_width = bwk256_width;

	// -------
	// meta
	// -------
	wog2_meta_weq_bytes = 6;	// meta wequest is 64b and is 8x8byte meta ewement

	// each 64b meta wequest fow dcn is 8x8 meta ewements and
	// a meta ewement covews one 256b bwock of the data suwface.
	wog2_meta_weq_height = wog2_bwk256_height + 3;	// meta weq is 8x8 byte, each byte wepwesent 1 bwk256
	wog2_meta_weq_width = wog2_meta_weq_bytes + 8 - wog2_bytes_pew_ewement - wog2_meta_weq_height;
	meta_weq_width = 1 << wog2_meta_weq_width;
	meta_weq_height = 1 << wog2_meta_weq_height;
	wog2_meta_wow_height = 0;
	meta_wow_width_ub = 0;

	// the dimensions of a meta wow awe meta_wow_width x meta_wow_height in ewements.
	// cawcuwate uppew bound of the meta_wow_width
	if (!suwf_vewt) {
		wog2_meta_wow_height = wog2_meta_weq_height;
		meta_wow_width_ub = dmw_wound_to_muwtipwe(vp_width - 1, meta_weq_width, 1) + meta_weq_width;
		wq_dwg_pawam->meta_weq_pew_wow_ub = meta_wow_width_ub / meta_weq_width;
	} ewse {
		wog2_meta_wow_height = wog2_meta_weq_width;
		meta_wow_width_ub = dmw_wound_to_muwtipwe(vp_height - 1, meta_weq_height, 1) + meta_weq_height;
		wq_dwg_pawam->meta_weq_pew_wow_ub = meta_wow_width_ub / meta_weq_height;
	}
	wq_dwg_pawam->meta_bytes_pew_wow_ub = wq_dwg_pawam->meta_weq_pew_wow_ub * 64;

	wq_dwg_pawam->meta_wow_height = 1 << wog2_meta_wow_height;

	wog2_meta_chunk_bytes = dmw_wog2(wq_sizing_pawam->meta_chunk_bytes);
	wog2_meta_chunk_height = wog2_meta_wow_height;

	//fuww sized meta chunk width in unit of data ewements
	wog2_meta_chunk_width = wog2_meta_chunk_bytes + 8 - wog2_bytes_pew_ewement - wog2_meta_chunk_height;
	wog2_min_meta_chunk_bytes = dmw_wog2(wq_sizing_pawam->min_meta_chunk_bytes);
	min_meta_chunk_width = 1 << (wog2_min_meta_chunk_bytes + 8 - wog2_bytes_pew_ewement - wog2_meta_chunk_height);
	meta_chunk_width = 1 << wog2_meta_chunk_width;
	meta_chunk_pew_wow_int = (unsigned int) (meta_wow_width_ub / meta_chunk_width);
	meta_wow_wemaindew = meta_wow_width_ub % meta_chunk_width;
	meta_chunk_thweshowd = 0;
	meta_bwk_height = bwk256_height * 64;
	meta_suwface_bytes = meta_pitch * (dmw_wound_to_muwtipwe(vp_height - 1, meta_bwk_height, 1) + meta_bwk_height) * bytes_pew_ewement / 256;
	vmpg_bytes = mode_wib->soc.gpuvm_min_page_size_bytes;
	meta_pte_weq_pew_fwame_ub = (dmw_wound_to_muwtipwe(meta_suwface_bytes - vmpg_bytes, 8 * vmpg_bytes, 1) + 8 * vmpg_bytes) / (8 * vmpg_bytes);
	meta_pte_bytes_pew_fwame_ub = meta_pte_weq_pew_fwame_ub * 64;	//64B mpte wequest
	wq_dwg_pawam->meta_pte_bytes_pew_fwame_ub = meta_pte_bytes_pew_fwame_ub;

	dmw_pwint("DMW_DWG: %s: meta_bwk_height             = %d\n", __func__, meta_bwk_height);
	dmw_pwint("DMW_DWG: %s: meta_suwface_bytes          = %d\n", __func__, meta_suwface_bytes);
	dmw_pwint("DMW_DWG: %s: meta_pte_weq_pew_fwame_ub   = %d\n", __func__, meta_pte_weq_pew_fwame_ub);
	dmw_pwint("DMW_DWG: %s: meta_pte_bytes_pew_fwame_ub = %d\n", __func__, meta_pte_bytes_pew_fwame_ub);

	if (!suwf_vewt)
		meta_chunk_thweshowd = 2 * min_meta_chunk_width - meta_weq_width;
	ewse
		meta_chunk_thweshowd = 2 * min_meta_chunk_width - meta_weq_height;

	if (meta_wow_wemaindew <= meta_chunk_thweshowd)
		wq_dwg_pawam->meta_chunks_pew_wow_ub = meta_chunk_pew_wow_int + 1;
	ewse
		wq_dwg_pawam->meta_chunks_pew_wow_ub = meta_chunk_pew_wow_int + 2;

	// ------
	// dpte
	// ------
	if (suwf_wineaw) {
		wog2_vmpg_height = 0;   // one wine high
	} ewse {
		wog2_vmpg_height = (wog2_vmpg_bytes - 8) / 2 + wog2_bwk256_height;
	}
	wog2_vmpg_width = wog2_vmpg_bytes - wog2_bytes_pew_ewement - wog2_vmpg_height;

	// onwy 3 possibwe shapes fow dpte wequest in dimensions of ptes: 8x1, 4x2, 2x4.
	if (suwf_wineaw) { //one 64B PTE wequest wetuwns 8 PTEs
		wog2_dpte_weq_height_ptes = 0;
		wog2_dpte_weq_width = wog2_vmpg_width + 3;
		wog2_dpte_weq_height = 0;
	} ewse if (wog2_bwk_bytes == 12) { //4KB tiwe means 4kB page size
		//one 64B weq gives 8x1 PTEs fow 4KB tiwe
		wog2_dpte_weq_height_ptes = 0;
		wog2_dpte_weq_width = wog2_bwk_width + 3;
		wog2_dpte_weq_height = wog2_bwk_height + 0;
	} ewse if ((wog2_bwk_bytes >= 16) && (wog2_vmpg_bytes == 12)) { // tiwe bwock >= 64KB
		//two 64B weqs of 2x4 PTEs give 16 PTEs to covew 64KB
		wog2_dpte_weq_height_ptes = 4;
		wog2_dpte_weq_width = wog2_bwk256_width + 4;		// wog2_64KB_width
		wog2_dpte_weq_height = wog2_bwk256_height + 4;		// wog2_64KB_height
	} ewse { //64KB page size and must 64KB tiwe bwock
		 //one 64B weq gives 8x1 PTEs fow 64KB tiwe
		wog2_dpte_weq_height_ptes = 0;
		wog2_dpte_weq_width = wog2_bwk_width + 3;
		wog2_dpte_weq_height = wog2_bwk_height + 0;
	}

	// The dpte wequest dimensions in data ewements is dpte_weq_width x dpte_weq_height
	// wog2_vmpg_width is how much 1 pte wepwesent, now cawcuwating how much a 64b pte weq wepwesent
	// That depends on the pte shape (i.e. 8x1, 4x2, 2x4)
	//wog2_dpte_weq_height    = wog2_vmpg_height + wog2_dpte_weq_height_ptes;
	//wog2_dpte_weq_width     = wog2_vmpg_width + wog2_dpte_weq_width_ptes;
	dpte_weq_height = 1 << wog2_dpte_weq_height;
	dpte_weq_width = 1 << wog2_dpte_weq_width;

	// cawcuwate pitch dpte wow buffew can howd
	// wound the wesuwt down to a powew of two.
	if (suwf_wineaw) {
		unsigned int dpte_wow_height;

		wog2_dpte_wow_height_wineaw = dmw_fwoow(dmw_wog2(dpte_buf_in_pte_weqs * dpte_weq_width / data_pitch), 1);

		dmw_pwint("DMW_DWG: %s: is_chwoma                   = %d\n", __func__, is_chwoma);
		dmw_pwint("DMW_DWG: %s: dpte_buf_in_pte_weqs        = %d\n", __func__, dpte_buf_in_pte_weqs);
		dmw_pwint("DMW_DWG: %s: wog2_dpte_wow_height_wineaw = %d\n", __func__, wog2_dpte_wow_height_wineaw);

		ASSEWT(wog2_dpte_wow_height_wineaw >= 3);

		if (wog2_dpte_wow_height_wineaw > 7)
			wog2_dpte_wow_height_wineaw = 7;

		wog2_dpte_wow_height = wog2_dpte_wow_height_wineaw;
		// Fow wineaw, the dpte wow is pitch dependent and the pte wequests wwap at the pitch boundawy.
		// the dpte_wow_width_ub is the uppew bound of data_pitch*dpte_wow_height in ewements with this unique buffewing.
		dpte_wow_height = 1 << wog2_dpte_wow_height;
		dpte_wow_width_ub = dmw_wound_to_muwtipwe(data_pitch * dpte_wow_height - 1, dpte_weq_width, 1) + dpte_weq_width;
		wq_dwg_pawam->dpte_weq_pew_wow_ub = dpte_wow_width_ub / dpte_weq_width;
	} ewse {
		// the uppew bound of the dpte_wow_width without dependency on viewpowt position fowwows.
		// fow tiwed mode, wow height is the same as weq height and wow stowe up to vp size uppew bound
		if (!suwf_vewt) {
			wog2_dpte_wow_height = wog2_dpte_weq_height;
			dpte_wow_width_ub = dmw_wound_to_muwtipwe(vp_width - 1, dpte_weq_width, 1) + dpte_weq_width;
			wq_dwg_pawam->dpte_weq_pew_wow_ub = dpte_wow_width_ub / dpte_weq_width;
		} ewse {
			wog2_dpte_wow_height = (wog2_bwk_width < wog2_dpte_weq_width) ? wog2_bwk_width : wog2_dpte_weq_width;
			dpte_wow_width_ub = dmw_wound_to_muwtipwe(vp_height - 1, dpte_weq_height, 1) + dpte_weq_height;
			wq_dwg_pawam->dpte_weq_pew_wow_ub = dpte_wow_width_ub / dpte_weq_height;
		}
	}
	if (wog2_bwk_bytes >= 16 && wog2_vmpg_bytes == 12) // tiwe bwock >= 64KB
		wq_dwg_pawam->dpte_bytes_pew_wow_ub = wq_dwg_pawam->dpte_weq_pew_wow_ub * 128; //2*64B dpte wequest
	ewse
		wq_dwg_pawam->dpte_bytes_pew_wow_ub = wq_dwg_pawam->dpte_weq_pew_wow_ub * 64; //64B dpte wequest

	wq_dwg_pawam->dpte_wow_height = 1 << wog2_dpte_wow_height;

	// the dpte_gwoup_bytes is weduced fow the specific case of vewticaw
	// access of a tiwe suwface that has dpte wequest of 8x1 ptes.
	if (hostvm_enabwe)
		wq_sizing_pawam->dpte_gwoup_bytes = 512;
	ewse {
		if (!suwf_wineaw & (wog2_dpte_weq_height_ptes == 0) & suwf_vewt) //weduced, in this case, wiww have page fauwt within a gwoup
			wq_sizing_pawam->dpte_gwoup_bytes = 512;
		ewse
			wq_sizing_pawam->dpte_gwoup_bytes = 2048;
	}

	//since pte wequest size is 64byte, the numbew of data pte wequests pew fuww sized gwoup is as fowwows.
	wog2_dpte_gwoup_bytes = dmw_wog2(wq_sizing_pawam->dpte_gwoup_bytes);
	wog2_dpte_gwoup_wength = wog2_dpte_gwoup_bytes - 6; //wength in 64b wequests

	// fuww sized data pte gwoup width in ewements
	if (!suwf_vewt)
		wog2_dpte_gwoup_width = wog2_dpte_gwoup_wength + wog2_dpte_weq_width;
	ewse
		wog2_dpte_gwoup_width = wog2_dpte_gwoup_wength + wog2_dpte_weq_height;

	//But if the tiwe bwock >=64KB and the page size is 4KB, then each dPTE wequest is 2*64B
	if ((wog2_bwk_bytes >= 16) && (wog2_vmpg_bytes == 12)) // tiwe bwock >= 64KB
		wog2_dpte_gwoup_width = wog2_dpte_gwoup_width - 1;

	dpte_gwoup_width = 1 << wog2_dpte_gwoup_width;

	// since dpte gwoups awe onwy awigned to dpte_weq_width and not dpte_gwoup_width,
	// the uppew bound fow the dpte gwoups pew wow is as fowwows.
	wq_dwg_pawam->dpte_gwoups_pew_wow_ub = dmw_ceiw((doubwe) dpte_wow_width_ub / dpte_gwoup_width, 1);
}

static void get_suwf_wq_pawam(
		stwuct dispway_mode_wib *mode_wib,
		dispway_data_wq_sizing_pawams_st *wq_sizing_pawam,
		dispway_data_wq_dwg_pawams_st *wq_dwg_pawam,
		dispway_data_wq_misc_pawams_st *wq_misc_pawam,
		const dispway_pipe_pawams_st *pipe_pawam,
		boow is_chwoma,
		boow is_awpha)
{
	boow mode_422 = 0;
	unsigned int vp_width = 0;
	unsigned int vp_height = 0;
	unsigned int data_pitch = 0;
	unsigned int meta_pitch = 0;
	unsigned int suwface_height = 0;
	unsigned int ppe = mode_422 ? 2 : 1;

	// FIXME check if ppe appwy fow both wuma and chwoma in 422 case
	if (is_chwoma | is_awpha) {
		vp_width = pipe_pawam->swc.viewpowt_width_c / ppe;
		vp_height = pipe_pawam->swc.viewpowt_height_c;
		data_pitch = pipe_pawam->swc.data_pitch_c;
		meta_pitch = pipe_pawam->swc.meta_pitch_c;
		suwface_height = pipe_pawam->swc.suwface_height_y / 2.0;
	} ewse {
		vp_width = pipe_pawam->swc.viewpowt_width / ppe;
		vp_height = pipe_pawam->swc.viewpowt_height;
		data_pitch = pipe_pawam->swc.data_pitch;
		meta_pitch = pipe_pawam->swc.meta_pitch;
		suwface_height = pipe_pawam->swc.suwface_height_y;
	}

	if (pipe_pawam->dest.odm_combine) {
		unsigned int access_diw;
		unsigned int fuww_swc_vp_width;
		unsigned int hactive_odm;
		unsigned int swc_hactive_odm;

		access_diw = (pipe_pawam->swc.souwce_scan == dm_vewt); // vp access diwection: howizontaw ow vewticaw accessed
		hactive_odm = pipe_pawam->dest.hactive / ((unsigned int) pipe_pawam->dest.odm_combine * 2);
		if (is_chwoma) {
			fuww_swc_vp_width = pipe_pawam->scawe_watio_depth.hscw_watio_c * pipe_pawam->dest.fuww_wecout_width;
			swc_hactive_odm = pipe_pawam->scawe_watio_depth.hscw_watio_c * hactive_odm;
		} ewse {
			fuww_swc_vp_width = pipe_pawam->scawe_watio_depth.hscw_watio * pipe_pawam->dest.fuww_wecout_width;
			swc_hactive_odm = pipe_pawam->scawe_watio_depth.hscw_watio * hactive_odm;
		}

		if (access_diw == 0) {
			vp_width = dmw_min(fuww_swc_vp_width, swc_hactive_odm);
			dmw_pwint("DMW_DWG: %s: vp_width = %d\n", __func__, vp_width);
		} ewse {
			vp_height = dmw_min(fuww_swc_vp_width, swc_hactive_odm);
			dmw_pwint("DMW_DWG: %s: vp_height = %d\n", __func__, vp_height);

		}
		dmw_pwint("DMW_DWG: %s: fuww_swc_vp_width = %d\n", __func__, fuww_swc_vp_width);
		dmw_pwint("DMW_DWG: %s: hactive_odm = %d\n", __func__, hactive_odm);
		dmw_pwint("DMW_DWG: %s: swc_hactive_odm = %d\n", __func__, swc_hactive_odm);
	}

	wq_sizing_pawam->chunk_bytes = 8192;

	if (is_awpha) {
		wq_sizing_pawam->chunk_bytes = 4096;
	}

	if (wq_sizing_pawam->chunk_bytes == 64 * 1024)
		wq_sizing_pawam->min_chunk_bytes = 0;
	ewse
		wq_sizing_pawam->min_chunk_bytes = 1024;

	wq_sizing_pawam->meta_chunk_bytes = 2048;
	wq_sizing_pawam->min_meta_chunk_bytes = 256;

	if (pipe_pawam->swc.hostvm)
		wq_sizing_pawam->mpte_gwoup_bytes = 512;
	ewse
		wq_sizing_pawam->mpte_gwoup_bytes = 2048;

	get_meta_and_pte_attw(
			mode_wib,
			wq_dwg_pawam,
			wq_misc_pawam,
			wq_sizing_pawam,
			vp_width,
			vp_height,
			data_pitch,
			meta_pitch,
			pipe_pawam->swc.souwce_fowmat,
			pipe_pawam->swc.sw_mode,
			pipe_pawam->swc.macwo_tiwe_size,
			pipe_pawam->swc.souwce_scan,
			pipe_pawam->swc.hostvm,
			is_chwoma,
			suwface_height);
}

static void dmw_wq_dwg_get_wq_pawams(stwuct dispway_mode_wib *mode_wib, dispway_wq_pawams_st *wq_pawam, const dispway_pipe_pawams_st *pipe_pawam)
{
	// get pawam fow wuma suwface
	wq_pawam->yuv420 = pipe_pawam->swc.souwce_fowmat == dm_420_8 || pipe_pawam->swc.souwce_fowmat == dm_420_10 || pipe_pawam->swc.souwce_fowmat == dm_wgbe_awpha
			|| pipe_pawam->swc.souwce_fowmat == dm_420_12;

	wq_pawam->yuv420_10bpc = pipe_pawam->swc.souwce_fowmat == dm_420_10;

	wq_pawam->wgbe_awpha = (pipe_pawam->swc.souwce_fowmat == dm_wgbe_awpha) ? 1 : 0;

	get_suwf_wq_pawam(mode_wib, &(wq_pawam->sizing.wq_w), &(wq_pawam->dwg.wq_w), &(wq_pawam->misc.wq_w), pipe_pawam, 0, 0);

	if (is_duaw_pwane((enum souwce_fowmat_cwass) (pipe_pawam->swc.souwce_fowmat))) {
		// get pawam fow chwoma suwface
		get_suwf_wq_pawam(mode_wib, &(wq_pawam->sizing.wq_c), &(wq_pawam->dwg.wq_c), &(wq_pawam->misc.wq_c), pipe_pawam, 1, wq_pawam->wgbe_awpha);
	}

	// cawcuwate how to spwit the det buffew space between wuma and chwoma
	handwe_det_buf_spwit(mode_wib, wq_pawam, &pipe_pawam->swc);
	pwint__wq_pawams_st(mode_wib, wq_pawam);
}

void dmw31_wq_dwg_get_wq_weg(stwuct dispway_mode_wib *mode_wib, dispway_wq_wegs_st *wq_wegs, const dispway_pipe_pawams_st *pipe_pawam)
{
	dispway_wq_pawams_st wq_pawam = {0};

	memset(wq_wegs, 0, sizeof(*wq_wegs));
	dmw_wq_dwg_get_wq_pawams(mode_wib, &wq_pawam, pipe_pawam);
	extwact_wq_wegs(mode_wib, wq_wegs, &wq_pawam);

	pwint__wq_wegs_st(mode_wib, wq_wegs);
}

static void cawcuwate_ttu_cuwsow(
		stwuct dispway_mode_wib *mode_wib,
		doubwe *wefcyc_pew_weq_dewivewy_pwe_cuw,
		doubwe *wefcyc_pew_weq_dewivewy_cuw,
		doubwe wefcwk_fweq_in_mhz,
		doubwe wef_fweq_to_pix_fweq,
		doubwe hscawe_pixew_wate_w,
		doubwe hscw_watio,
		doubwe vwatio_pwe_w,
		doubwe vwatio_w,
		unsigned int cuw_width,
		enum cuwsow_bpp cuw_bpp)
{
	unsigned int cuw_swc_width = cuw_width;
	unsigned int cuw_weq_size = 0;
	unsigned int cuw_weq_width = 0;
	doubwe cuw_width_ub = 0.0;
	doubwe cuw_weq_pew_width = 0.0;
	doubwe hactive_cuw = 0.0;

	ASSEWT(cuw_swc_width <= 256);

	*wefcyc_pew_weq_dewivewy_pwe_cuw = 0.0;
	*wefcyc_pew_weq_dewivewy_cuw = 0.0;
	if (cuw_swc_width > 0) {
		unsigned int cuw_bit_pew_pixew = 0;

		if (cuw_bpp == dm_cuw_2bit) {
			cuw_weq_size = 64; // byte
			cuw_bit_pew_pixew = 2;
		} ewse { // 32bit
			cuw_bit_pew_pixew = 32;
			if (cuw_swc_width >= 1 && cuw_swc_width <= 16)
				cuw_weq_size = 64;
			ewse if (cuw_swc_width >= 17 && cuw_swc_width <= 31)
				cuw_weq_size = 128;
			ewse
				cuw_weq_size = 256;
		}

		cuw_weq_width = (doubwe) cuw_weq_size / ((doubwe) cuw_bit_pew_pixew / 8.0);
		cuw_width_ub = dmw_ceiw((doubwe) cuw_swc_width / (doubwe) cuw_weq_width, 1) * (doubwe) cuw_weq_width;
		cuw_weq_pew_width = cuw_width_ub / (doubwe) cuw_weq_width;
		hactive_cuw = (doubwe) cuw_swc_width / hscw_watio; // FIXME: oswin to think about what to do fow cuwsow

		if (vwatio_pwe_w <= 1.0) {
			*wefcyc_pew_weq_dewivewy_pwe_cuw = hactive_cuw * wef_fweq_to_pix_fweq / (doubwe) cuw_weq_pew_width;
		} ewse {
			*wefcyc_pew_weq_dewivewy_pwe_cuw = (doubwe) wefcwk_fweq_in_mhz * (doubwe) cuw_swc_width / hscawe_pixew_wate_w / (doubwe) cuw_weq_pew_width;
		}

		ASSEWT(*wefcyc_pew_weq_dewivewy_pwe_cuw < dmw_pow(2, 13));

		if (vwatio_w <= 1.0) {
			*wefcyc_pew_weq_dewivewy_cuw = hactive_cuw * wef_fweq_to_pix_fweq / (doubwe) cuw_weq_pew_width;
		} ewse {
			*wefcyc_pew_weq_dewivewy_cuw = (doubwe) wefcwk_fweq_in_mhz * (doubwe) cuw_swc_width / hscawe_pixew_wate_w / (doubwe) cuw_weq_pew_width;
		}

		dmw_pwint("DMW_DWG: %s: cuw_weq_width                     = %d\n", __func__, cuw_weq_width);
		dmw_pwint("DMW_DWG: %s: cuw_width_ub                      = %3.2f\n", __func__, cuw_width_ub);
		dmw_pwint("DMW_DWG: %s: cuw_weq_pew_width                 = %3.2f\n", __func__, cuw_weq_pew_width);
		dmw_pwint("DMW_DWG: %s: hactive_cuw                       = %3.2f\n", __func__, hactive_cuw);
		dmw_pwint("DMW_DWG: %s: wefcyc_pew_weq_dewivewy_pwe_cuw   = %3.2f\n", __func__, *wefcyc_pew_weq_dewivewy_pwe_cuw);
		dmw_pwint("DMW_DWG: %s: wefcyc_pew_weq_dewivewy_cuw       = %3.2f\n", __func__, *wefcyc_pew_weq_dewivewy_cuw);

		ASSEWT(*wefcyc_pew_weq_dewivewy_cuw < dmw_pow(2, 13));
	}
}

// Note: cuwwentwy taken in as is.
// Nice to decoupwe code fwom hw wegistew impwement and extwact code that awe wepeated fow wuma and chwoma.
static void dmw_wq_dwg_get_dwg_pawams(
		stwuct dispway_mode_wib *mode_wib,
		const dispway_e2e_pipe_pawams_st *e2e_pipe_pawam,
		const unsigned int num_pipes,
		const unsigned int pipe_idx,
		dispway_dwg_wegs_st *disp_dwg_wegs,
		dispway_ttu_wegs_st *disp_ttu_wegs,
		const dispway_wq_dwg_pawams_st *wq_dwg_pawam,
		const dispway_dwg_sys_pawams_st *dwg_sys_pawam,
		const boow cstate_en,
		const boow pstate_en,
		const boow vm_en,
		const boow ignowe_viewpowt_pos,
		const boow immediate_fwip_suppowt)
{
	const dispway_pipe_souwce_pawams_st *swc = &e2e_pipe_pawam[pipe_idx].pipe.swc;
	const dispway_pipe_dest_pawams_st *dst = &e2e_pipe_pawam[pipe_idx].pipe.dest;
	const dispway_cwocks_and_cfg_st *cwks = &e2e_pipe_pawam[pipe_idx].cwks_cfg;
	const scawew_watio_depth_st *scw = &e2e_pipe_pawam[pipe_idx].pipe.scawe_watio_depth;
	const scawew_taps_st *taps = &e2e_pipe_pawam[pipe_idx].pipe.scawe_taps;
	unsigned int pipe_index_in_combine[DC__NUM_PIPES__MAX];

	// -------------------------
	// Section 1.15.2.1: OTG dependent Pawams
	// -------------------------
	// Timing
	unsigned int htotaw = dst->htotaw;
	unsigned int hbwank_end = dst->hbwank_end;
	unsigned int vbwank_stawt = dst->vbwank_stawt;
	unsigned int vbwank_end = dst->vbwank_end;

	doubwe dppcwk_fweq_in_mhz = cwks->dppcwk_mhz;
	doubwe wefcwk_fweq_in_mhz = cwks->wefcwk_mhz;
	doubwe pcwk_fweq_in_mhz = dst->pixew_wate_mhz;
	boow intewwaced = dst->intewwaced;
	doubwe wef_fweq_to_pix_fweq = wefcwk_fweq_in_mhz / pcwk_fweq_in_mhz;
	doubwe min_ttu_vbwank;
	unsigned int dwg_vbwank_stawt;
	boow duaw_pwane;
	boow mode_422;
	unsigned int access_diw;
	unsigned int vp_height_w;
	unsigned int vp_width_w;
	unsigned int vp_height_c;
	unsigned int vp_width_c;

	// Scawing
	unsigned int htaps_w;
	unsigned int htaps_c;
	doubwe hwatio_w;
	doubwe hwatio_c;
	doubwe vwatio_w;
	doubwe vwatio_c;

	unsigned int swath_width_ub_w;
	unsigned int dpte_gwoups_pew_wow_ub_w;
	unsigned int swath_width_ub_c;
	unsigned int dpte_gwoups_pew_wow_ub_c;

	unsigned int meta_chunks_pew_wow_ub_w;
	unsigned int meta_chunks_pew_wow_ub_c;
	unsigned int vupdate_offset;
	unsigned int vupdate_width;
	unsigned int vweady_offset;

	unsigned int vstawtup_stawt;
	unsigned int dst_x_aftew_scawew;
	unsigned int dst_y_aftew_scawew;
	doubwe dst_y_pwefetch;
	doubwe dst_y_pew_vm_vbwank;
	doubwe dst_y_pew_wow_vbwank;
	doubwe dst_y_pew_vm_fwip;
	doubwe dst_y_pew_wow_fwip;
	doubwe max_dst_y_pew_vm_vbwank;
	doubwe max_dst_y_pew_wow_vbwank;
	doubwe vwatio_pwe_w;
	doubwe vwatio_pwe_c;
	unsigned int weq_pew_swath_ub_w;
	unsigned int weq_pew_swath_ub_c;
	unsigned int meta_wow_height_w;
	unsigned int meta_wow_height_c;
	unsigned int swath_width_pixews_ub_w;
	unsigned int swath_width_pixews_ub_c;
	unsigned int scawew_wec_in_width_w;
	unsigned int scawew_wec_in_width_c;
	unsigned int dpte_wow_height_w;
	unsigned int dpte_wow_height_c;
	doubwe hscawe_pixew_wate_w;
	doubwe hscawe_pixew_wate_c;
	doubwe min_hwatio_fact_w;
	doubwe min_hwatio_fact_c;
	doubwe wefcyc_pew_wine_dewivewy_pwe_w;
	doubwe wefcyc_pew_wine_dewivewy_pwe_c;
	doubwe wefcyc_pew_wine_dewivewy_w;
	doubwe wefcyc_pew_wine_dewivewy_c;

	doubwe wefcyc_pew_weq_dewivewy_pwe_w;
	doubwe wefcyc_pew_weq_dewivewy_pwe_c;
	doubwe wefcyc_pew_weq_dewivewy_w;
	doubwe wefcyc_pew_weq_dewivewy_c;

	unsigned int fuww_wecout_width;
	doubwe wefcyc_pew_weq_dewivewy_pwe_cuw0;
	doubwe wefcyc_pew_weq_dewivewy_cuw0;
	doubwe wefcyc_pew_weq_dewivewy_pwe_cuw1;
	doubwe wefcyc_pew_weq_dewivewy_cuw1;
	int unsigned vba__min_dst_y_next_stawt = get_min_dst_y_next_stawt(mode_wib, e2e_pipe_pawam, num_pipes, pipe_idx); // FWOM VBA
	int unsigned vba__vweady_aftew_vcount0 = get_vweady_at_ow_aftew_vsync(mode_wib, e2e_pipe_pawam, num_pipes, pipe_idx); // Fwom VBA

	fwoat vba__wefcyc_pew_wine_dewivewy_pwe_w = get_wefcyc_pew_wine_dewivewy_pwe_w_in_us(mode_wib, e2e_pipe_pawam, num_pipes, pipe_idx) * wefcwk_fweq_in_mhz; // Fwom VBA
	fwoat vba__wefcyc_pew_wine_dewivewy_w = get_wefcyc_pew_wine_dewivewy_w_in_us(mode_wib, e2e_pipe_pawam, num_pipes, pipe_idx) * wefcwk_fweq_in_mhz; // Fwom VBA

	fwoat vba__wefcyc_pew_weq_dewivewy_pwe_w = get_wefcyc_pew_weq_dewivewy_pwe_w_in_us(mode_wib, e2e_pipe_pawam, num_pipes, pipe_idx) * wefcwk_fweq_in_mhz;  // Fwom VBA
	fwoat vba__wefcyc_pew_weq_dewivewy_w = get_wefcyc_pew_weq_dewivewy_w_in_us(mode_wib, e2e_pipe_pawam, num_pipes, pipe_idx) * wefcwk_fweq_in_mhz;  // Fwom VBA

	memset(disp_dwg_wegs, 0, sizeof(*disp_dwg_wegs));
	memset(disp_ttu_wegs, 0, sizeof(*disp_ttu_wegs));

	dmw_pwint("DMW_DWG: %s: cstate_en = %d\n", __func__, cstate_en);
	dmw_pwint("DMW_DWG: %s: pstate_en = %d\n", __func__, pstate_en);
	dmw_pwint("DMW_DWG: %s: vm_en     = %d\n", __func__, vm_en);
	dmw_pwint("DMW_DWG: %s: ignowe_viewpowt_pos  = %d\n", __func__, ignowe_viewpowt_pos);
	dmw_pwint("DMW_DWG: %s: immediate_fwip_suppowt  = %d\n", __func__, immediate_fwip_suppowt);

	dmw_pwint("DMW_DWG: %s: dppcwk_fweq_in_mhz     = %3.2f\n", __func__, dppcwk_fweq_in_mhz);
	dmw_pwint("DMW_DWG: %s: wefcwk_fweq_in_mhz     = %3.2f\n", __func__, wefcwk_fweq_in_mhz);
	dmw_pwint("DMW_DWG: %s: pcwk_fweq_in_mhz       = %3.2f\n", __func__, pcwk_fweq_in_mhz);
	dmw_pwint("DMW_DWG: %s: intewwaced             = %d\n", __func__, intewwaced); ASSEWT(wef_fweq_to_pix_fweq < 4.0);

	disp_dwg_wegs->wef_fweq_to_pix_fweq = (unsigned int) (wef_fweq_to_pix_fweq * dmw_pow(2, 19));
	disp_dwg_wegs->wefcyc_pew_htotaw = (unsigned int) (wef_fweq_to_pix_fweq * (doubwe) htotaw * dmw_pow(2, 8));
	disp_dwg_wegs->dwg_vbwank_end = intewwaced ? (vbwank_end / 2) : vbwank_end;	// 15 bits

	//set_pwefetch_mode(mode_wib, cstate_en, pstate_en, ignowe_viewpowt_pos, immediate_fwip_suppowt);
	min_ttu_vbwank = get_min_ttu_vbwank_in_us(mode_wib, e2e_pipe_pawam, num_pipes, pipe_idx);	// Fwom VBA

	dwg_vbwank_stawt = intewwaced ? (vbwank_stawt / 2) : vbwank_stawt;
	disp_dwg_wegs->min_dst_y_next_stawt = (unsigned int) (((doubwe) dwg_vbwank_stawt) * dmw_pow(2, 2));
	disp_dwg_wegs->min_dst_y_next_stawt_us = 0;
	ASSEWT(disp_dwg_wegs->min_dst_y_next_stawt < (unsigned int)dmw_pow(2, 18));

	dmw_pwint("DMW_DWG: %s: min_ttu_vbwank (us)         = %3.2f\n", __func__, min_ttu_vbwank);
	dmw_pwint("DMW_DWG: %s: min_dst_y_next_stawt        = 0x%0x\n", __func__, disp_dwg_wegs->min_dst_y_next_stawt);
	dmw_pwint("DMW_DWG: %s: dwg_vbwank_stawt            = 0x%0x\n", __func__, dwg_vbwank_stawt);
	dmw_pwint("DMW_DWG: %s: wef_fweq_to_pix_fweq        = %3.2f\n", __func__, wef_fweq_to_pix_fweq);
	dmw_pwint("DMW_DWG: %s: vba__min_dst_y_next_stawt   = 0x%0x\n", __func__, vba__min_dst_y_next_stawt);

	//owd_impw_vs_vba_impw("min_dst_y_next_stawt", dwg_vbwank_stawt, vba__min_dst_y_next_stawt);

	// -------------------------
	// Section 1.15.2.2: Pwefetch, Active and TTU
	// -------------------------
	// Pwefetch Cawc
	// Souwce
	duaw_pwane = is_duaw_pwane((enum souwce_fowmat_cwass) (swc->souwce_fowmat));
	mode_422 = 0;
	access_diw = (swc->souwce_scan == dm_vewt);	// vp access diwection: howizontaw ow vewticaw accessed
	vp_height_w = swc->viewpowt_height;
	vp_width_w = swc->viewpowt_width;
	vp_height_c = swc->viewpowt_height_c;
	vp_width_c = swc->viewpowt_width_c;

	// Scawing
	htaps_w = taps->htaps;
	htaps_c = taps->htaps_c;
	hwatio_w = scw->hscw_watio;
	hwatio_c = scw->hscw_watio_c;
	vwatio_w = scw->vscw_watio;
	vwatio_c = scw->vscw_watio_c;

	swath_width_ub_w = wq_dwg_pawam->wq_w.swath_width_ub;
	dpte_gwoups_pew_wow_ub_w = wq_dwg_pawam->wq_w.dpte_gwoups_pew_wow_ub;
	swath_width_ub_c = wq_dwg_pawam->wq_c.swath_width_ub;
	dpte_gwoups_pew_wow_ub_c = wq_dwg_pawam->wq_c.dpte_gwoups_pew_wow_ub;

	meta_chunks_pew_wow_ub_w = wq_dwg_pawam->wq_w.meta_chunks_pew_wow_ub;
	meta_chunks_pew_wow_ub_c = wq_dwg_pawam->wq_c.meta_chunks_pew_wow_ub;
	vupdate_offset = dst->vupdate_offset;
	vupdate_width = dst->vupdate_width;
	vweady_offset = dst->vweady_offset;

	vstawtup_stawt = dst->vstawtup_stawt;
	if (intewwaced) {
		if (vstawtup_stawt / 2.0 - (doubwe) (vweady_offset + vupdate_width + vupdate_offset) / htotaw <= vbwank_end / 2.0)
			disp_dwg_wegs->vweady_aftew_vcount0 = 1;
		ewse
			disp_dwg_wegs->vweady_aftew_vcount0 = 0;
	} ewse {
		if (vstawtup_stawt - (doubwe) (vweady_offset + vupdate_width + vupdate_offset) / htotaw <= vbwank_end)
			disp_dwg_wegs->vweady_aftew_vcount0 = 1;
		ewse
			disp_dwg_wegs->vweady_aftew_vcount0 = 0;
	}

	dmw_pwint("DMW_DWG: %s: vweady_aftew_vcount0 = %d\n", __func__, disp_dwg_wegs->vweady_aftew_vcount0);
	dmw_pwint("DMW_DWG: %s: vba__vweady_aftew_vcount0 = %d\n", __func__, vba__vweady_aftew_vcount0);
	//owd_impw_vs_vba_impw("vweady_aftew_vcount0", disp_dwg_wegs->vweady_aftew_vcount0, vba__vweady_aftew_vcount0);

	if (intewwaced)
		vstawtup_stawt = vstawtup_stawt / 2;

	dst_x_aftew_scawew = get_dst_x_aftew_scawew(mode_wib, e2e_pipe_pawam, num_pipes, pipe_idx); // Fwom VBA
	dst_y_aftew_scawew = get_dst_y_aftew_scawew(mode_wib, e2e_pipe_pawam, num_pipes, pipe_idx); // Fwom VBA

	// do some adjustment on the dst_aftew scawew to account fow odm combine mode
	dmw_pwint("DMW_DWG: %s: input dst_x_aftew_scawew   = %d\n", __func__, dst_x_aftew_scawew);
	dmw_pwint("DMW_DWG: %s: input dst_y_aftew_scawew   = %d\n", __func__, dst_y_aftew_scawew);

	// need to figuwe out which side of odm combine we'we in
	if (dst->odm_combine) {
		// figuwe out which pipes go togethew
		boow visited[DC__NUM_PIPES__MAX];
		unsigned int i, j, k;

		fow (k = 0; k < num_pipes; ++k) {
			visited[k] = fawse;
			pipe_index_in_combine[k] = 0;
		}

		fow (i = 0; i < num_pipes; i++) {
			if (e2e_pipe_pawam[i].pipe.swc.is_hspwit && !visited[i]) {

				unsigned int gwp = e2e_pipe_pawam[i].pipe.swc.hspwit_gwp;
				unsigned int gwp_idx = 0;

				fow (j = i; j < num_pipes; j++) {
					if (e2e_pipe_pawam[j].pipe.swc.hspwit_gwp == gwp && e2e_pipe_pawam[j].pipe.swc.is_hspwit && !visited[j]) {
						pipe_index_in_combine[j] = gwp_idx;
						dmw_pwint("DMW_DWG: %s: pipe[%d] is in gwp %d idx %d\n", __func__, j, gwp, gwp_idx);
						gwp_idx++;
						visited[j] = twue;
					}
				}
			}
		}

	}

	if (dst->odm_combine == dm_odm_combine_mode_disabwed) {
		disp_dwg_wegs->wefcyc_h_bwank_end = (unsigned int) ((doubwe) hbwank_end * wef_fweq_to_pix_fweq);
	} ewse {
		unsigned int odm_combine_factow = (dst->odm_combine == dm_odm_combine_mode_2to1 ? 2 : 4); // TODO: We shouwd weawwy check that 4to1 is suppowted befowe setting it to 4
		unsigned int odm_pipe_index = pipe_index_in_combine[pipe_idx];
		disp_dwg_wegs->wefcyc_h_bwank_end = (unsigned int) (((doubwe) hbwank_end + odm_pipe_index * (doubwe) dst->hactive / odm_combine_factow) * wef_fweq_to_pix_fweq);
	} ASSEWT(disp_dwg_wegs->wefcyc_h_bwank_end < (unsigned int)dmw_pow(2, 13));

	dmw_pwint("DMW_DWG: %s: htotaw                     = %d\n", __func__, htotaw);
	dmw_pwint("DMW_DWG: %s: dst_x_aftew_scawew[%d]     = %d\n", __func__, pipe_idx, dst_x_aftew_scawew);
	dmw_pwint("DMW_DWG: %s: dst_y_aftew_scawew[%d]     = %d\n", __func__, pipe_idx, dst_y_aftew_scawew);

	dst_y_pwefetch = get_dst_y_pwefetch(mode_wib, e2e_pipe_pawam, num_pipes, pipe_idx);        // Fwom VBA
	dst_y_pew_vm_vbwank = get_dst_y_pew_vm_vbwank(mode_wib, e2e_pipe_pawam, num_pipes, pipe_idx);        // Fwom VBA
	dst_y_pew_wow_vbwank = get_dst_y_pew_wow_vbwank(mode_wib, e2e_pipe_pawam, num_pipes, pipe_idx);        // Fwom VBA
	dst_y_pew_vm_fwip = get_dst_y_pew_vm_fwip(mode_wib, e2e_pipe_pawam, num_pipes, pipe_idx);        // Fwom VBA
	dst_y_pew_wow_fwip = get_dst_y_pew_wow_fwip(mode_wib, e2e_pipe_pawam, num_pipes, pipe_idx);        // Fwom VBA

	max_dst_y_pew_vm_vbwank = 32.0;        //U5.2
	max_dst_y_pew_wow_vbwank = 16.0;        //U4.2

	// magic!
	if (htotaw <= 75) {
		max_dst_y_pew_vm_vbwank = 100.0;
		max_dst_y_pew_wow_vbwank = 100.0;
	}

	dmw_pwint("DMW_DWG: %s: dst_y_pwefetch (aftew wnd) = %3.2f\n", __func__, dst_y_pwefetch);
	dmw_pwint("DMW_DWG: %s: dst_y_pew_vm_fwip    = %3.2f\n", __func__, dst_y_pew_vm_fwip);
	dmw_pwint("DMW_DWG: %s: dst_y_pew_wow_fwip   = %3.2f\n", __func__, dst_y_pew_wow_fwip);
	dmw_pwint("DMW_DWG: %s: dst_y_pew_vm_vbwank  = %3.2f\n", __func__, dst_y_pew_vm_vbwank);
	dmw_pwint("DMW_DWG: %s: dst_y_pew_wow_vbwank = %3.2f\n", __func__, dst_y_pew_wow_vbwank);

	ASSEWT(dst_y_pew_vm_vbwank < max_dst_y_pew_vm_vbwank); ASSEWT(dst_y_pew_wow_vbwank < max_dst_y_pew_wow_vbwank);

	ASSEWT(dst_y_pwefetch > (dst_y_pew_vm_vbwank + dst_y_pew_wow_vbwank));

	vwatio_pwe_w = get_vwatio_pwefetch_w(mode_wib, e2e_pipe_pawam, num_pipes, pipe_idx);    // Fwom VBA
	vwatio_pwe_c = get_vwatio_pwefetch_c(mode_wib, e2e_pipe_pawam, num_pipes, pipe_idx);    // Fwom VBA

	dmw_pwint("DMW_DWG: %s: vwatio_pwe_w = %3.2f\n", __func__, vwatio_pwe_w);
	dmw_pwint("DMW_DWG: %s: vwatio_pwe_c = %3.2f\n", __func__, vwatio_pwe_c);

	// Active
	weq_pew_swath_ub_w = wq_dwg_pawam->wq_w.weq_pew_swath_ub;
	weq_pew_swath_ub_c = wq_dwg_pawam->wq_c.weq_pew_swath_ub;
	meta_wow_height_w = wq_dwg_pawam->wq_w.meta_wow_height;
	meta_wow_height_c = wq_dwg_pawam->wq_c.meta_wow_height;
	swath_width_pixews_ub_w = 0;
	swath_width_pixews_ub_c = 0;
	scawew_wec_in_width_w = 0;
	scawew_wec_in_width_c = 0;
	dpte_wow_height_w = wq_dwg_pawam->wq_w.dpte_wow_height;
	dpte_wow_height_c = wq_dwg_pawam->wq_c.dpte_wow_height;

	if (mode_422) {
		swath_width_pixews_ub_w = swath_width_ub_w * 2;  // *2 fow 2 pixew pew ewement
		swath_width_pixews_ub_c = swath_width_ub_c * 2;
	} ewse {
		swath_width_pixews_ub_w = swath_width_ub_w * 1;
		swath_width_pixews_ub_c = swath_width_ub_c * 1;
	}

	hscawe_pixew_wate_w = 0.;
	hscawe_pixew_wate_c = 0.;
	min_hwatio_fact_w = 1.0;
	min_hwatio_fact_c = 1.0;

	if (hwatio_w <= 1)
		min_hwatio_fact_w = 2.0;
	ewse if (htaps_w <= 6) {
		if ((hwatio_w * 2.0) > 4.0)
			min_hwatio_fact_w = 4.0;
		ewse
			min_hwatio_fact_w = hwatio_w * 2.0;
	} ewse {
		if (hwatio_w > 4.0)
			min_hwatio_fact_w = 4.0;
		ewse
			min_hwatio_fact_w = hwatio_w;
	}

	hscawe_pixew_wate_w = min_hwatio_fact_w * dppcwk_fweq_in_mhz;

	dmw_pwint("DMW_DWG: %s: hwatio_w = %3.2f\n", __func__, hwatio_w);
	dmw_pwint("DMW_DWG: %s: min_hwatio_fact_w = %3.2f\n", __func__, min_hwatio_fact_w);
	dmw_pwint("DMW_DWG: %s: hscawe_pixew_wate_w = %3.2f\n", __func__, hscawe_pixew_wate_w);

	if (hwatio_c <= 1)
		min_hwatio_fact_c = 2.0;
	ewse if (htaps_c <= 6) {
		if ((hwatio_c * 2.0) > 4.0)
			min_hwatio_fact_c = 4.0;
		ewse
			min_hwatio_fact_c = hwatio_c * 2.0;
	} ewse {
		if (hwatio_c > 4.0)
			min_hwatio_fact_c = 4.0;
		ewse
			min_hwatio_fact_c = hwatio_c;
	}

	hscawe_pixew_wate_c = min_hwatio_fact_c * dppcwk_fweq_in_mhz;

	wefcyc_pew_wine_dewivewy_pwe_w = 0.;
	wefcyc_pew_wine_dewivewy_pwe_c = 0.;
	wefcyc_pew_wine_dewivewy_w = 0.;
	wefcyc_pew_wine_dewivewy_c = 0.;

	wefcyc_pew_weq_dewivewy_pwe_w = 0.;
	wefcyc_pew_weq_dewivewy_pwe_c = 0.;
	wefcyc_pew_weq_dewivewy_w = 0.;
	wefcyc_pew_weq_dewivewy_c = 0.;

	fuww_wecout_width = 0;
	// In ODM
	if (swc->is_hspwit) {
		// This "hack"  is onwy awwowed (and vawid) fow MPC combine. In ODM
		// combine, you MUST specify the fuww_wecout_width...accowding to Oswin
		if (dst->fuww_wecout_width == 0 && !dst->odm_combine) {
			dmw_pwint("DMW_DWG: %s: Wawning: fuww_wecout_width not set in hspwit mode\n", __func__);
			fuww_wecout_width = dst->wecout_width * 2; // assume hawf spwit fow dcn1
		} ewse
			fuww_wecout_width = dst->fuww_wecout_width;
	} ewse
		fuww_wecout_width = dst->wecout_width;

	// As of DCN2, mpc_combine and odm_combine awe mutuawwy excwusive
	wefcyc_pew_wine_dewivewy_pwe_w = get_wefcyc_pew_dewivewy(
			mode_wib,
			wefcwk_fweq_in_mhz,
			pcwk_fweq_in_mhz,
			dst->odm_combine,
			fuww_wecout_width,
			dst->hactive,
			vwatio_pwe_w,
			hscawe_pixew_wate_w,
			swath_width_pixews_ub_w,
			1); // pew wine

	wefcyc_pew_wine_dewivewy_w = get_wefcyc_pew_dewivewy(
			mode_wib,
			wefcwk_fweq_in_mhz,
			pcwk_fweq_in_mhz,
			dst->odm_combine,
			fuww_wecout_width,
			dst->hactive,
			vwatio_w,
			hscawe_pixew_wate_w,
			swath_width_pixews_ub_w,
			1); // pew wine

	dmw_pwint("DMW_DWG: %s: fuww_wecout_width              = %d\n", __func__, fuww_wecout_width);
	dmw_pwint("DMW_DWG: %s: hscawe_pixew_wate_w            = %3.2f\n", __func__, hscawe_pixew_wate_w);
	dmw_pwint("DMW_DWG: %s: wefcyc_pew_wine_dewivewy_pwe_w = %3.2f\n", __func__, wefcyc_pew_wine_dewivewy_pwe_w);
	dmw_pwint("DMW_DWG: %s: wefcyc_pew_wine_dewivewy_w     = %3.2f\n", __func__, wefcyc_pew_wine_dewivewy_w);
	dmw_pwint("DMW_DWG: %s: vba__wefcyc_pew_wine_dewivewy_pwe_w = %3.2f\n", __func__, vba__wefcyc_pew_wine_dewivewy_pwe_w);
	dmw_pwint("DMW_DWG: %s: vba__wefcyc_pew_wine_dewivewy_w     = %3.2f\n", __func__, vba__wefcyc_pew_wine_dewivewy_w);

	//owd_impw_vs_vba_impw("wefcyc_pew_wine_dewivewy_pwe_w", wefcyc_pew_wine_dewivewy_pwe_w, vba__wefcyc_pew_wine_dewivewy_pwe_w);
	//owd_impw_vs_vba_impw("wefcyc_pew_wine_dewivewy_w", wefcyc_pew_wine_dewivewy_w, vba__wefcyc_pew_wine_dewivewy_w);

	if (duaw_pwane) {
		fwoat vba__wefcyc_pew_wine_dewivewy_pwe_c = get_wefcyc_pew_wine_dewivewy_pwe_c_in_us(mode_wib, e2e_pipe_pawam, num_pipes, pipe_idx) * wefcwk_fweq_in_mhz; // Fwom VBA
		fwoat vba__wefcyc_pew_wine_dewivewy_c = get_wefcyc_pew_wine_dewivewy_c_in_us(mode_wib, e2e_pipe_pawam, num_pipes, pipe_idx) * wefcwk_fweq_in_mhz; // Fwom VBA

		wefcyc_pew_wine_dewivewy_pwe_c = get_wefcyc_pew_dewivewy(
				mode_wib,
				wefcwk_fweq_in_mhz,
				pcwk_fweq_in_mhz,
				dst->odm_combine,
				fuww_wecout_width,
				dst->hactive,
				vwatio_pwe_c,
				hscawe_pixew_wate_c,
				swath_width_pixews_ub_c,
				1); // pew wine

		wefcyc_pew_wine_dewivewy_c = get_wefcyc_pew_dewivewy(
				mode_wib,
				wefcwk_fweq_in_mhz,
				pcwk_fweq_in_mhz,
				dst->odm_combine,
				fuww_wecout_width,
				dst->hactive,
				vwatio_c,
				hscawe_pixew_wate_c,
				swath_width_pixews_ub_c,
				1); // pew wine

		dmw_pwint("DMW_DWG: %s: wefcyc_pew_wine_dewivewy_pwe_c = %3.2f\n", __func__, wefcyc_pew_wine_dewivewy_pwe_c);
		dmw_pwint("DMW_DWG: %s: wefcyc_pew_wine_dewivewy_c     = %3.2f\n", __func__, wefcyc_pew_wine_dewivewy_c);
		dmw_pwint("DMW_DWG: %s: vba__wefcyc_pew_wine_dewivewy_pwe_c = %3.2f\n", __func__, vba__wefcyc_pew_wine_dewivewy_pwe_c);
		dmw_pwint("DMW_DWG: %s: vba__wefcyc_pew_wine_dewivewy_c     = %3.2f\n", __func__, vba__wefcyc_pew_wine_dewivewy_c);

		//owd_impw_vs_vba_impw("wefcyc_pew_wine_dewivewy_pwe_c", wefcyc_pew_wine_dewivewy_pwe_c, vba__wefcyc_pew_wine_dewivewy_pwe_c);
		//owd_impw_vs_vba_impw("wefcyc_pew_wine_dewivewy_c", wefcyc_pew_wine_dewivewy_c, vba__wefcyc_pew_wine_dewivewy_c);
	}

	if (swc->dynamic_metadata_enabwe && swc->gpuvm)
		disp_dwg_wegs->wefcyc_pew_vm_dmdata = get_wefcyc_pew_vm_dmdata_in_us(mode_wib, e2e_pipe_pawam, num_pipes, pipe_idx) * wefcwk_fweq_in_mhz; // Fwom VBA

	disp_dwg_wegs->dmdata_dw_dewta = get_dmdata_dw_dewta_in_us(mode_wib, e2e_pipe_pawam, num_pipes, pipe_idx) * wefcwk_fweq_in_mhz; // Fwom VBA

	// TTU - Wuma / Chwoma
	if (access_diw) {  // vewticaw access
		scawew_wec_in_width_w = vp_height_w;
		scawew_wec_in_width_c = vp_height_c;
	} ewse {
		scawew_wec_in_width_w = vp_width_w;
		scawew_wec_in_width_c = vp_width_c;
	}

	wefcyc_pew_weq_dewivewy_pwe_w = get_wefcyc_pew_dewivewy(
			mode_wib,
			wefcwk_fweq_in_mhz,
			pcwk_fweq_in_mhz,
			dst->odm_combine,
			fuww_wecout_width,
			dst->hactive,
			vwatio_pwe_w,
			hscawe_pixew_wate_w,
			scawew_wec_in_width_w,
			weq_pew_swath_ub_w);  // pew weq

	wefcyc_pew_weq_dewivewy_w = get_wefcyc_pew_dewivewy(
			mode_wib,
			wefcwk_fweq_in_mhz,
			pcwk_fweq_in_mhz,
			dst->odm_combine,
			fuww_wecout_width,
			dst->hactive,
			vwatio_w,
			hscawe_pixew_wate_w,
			scawew_wec_in_width_w,
			weq_pew_swath_ub_w);  // pew weq

	dmw_pwint("DMW_DWG: %s: wefcyc_pew_weq_dewivewy_pwe_w = %3.2f\n", __func__, wefcyc_pew_weq_dewivewy_pwe_w);
	dmw_pwint("DMW_DWG: %s: wefcyc_pew_weq_dewivewy_w     = %3.2f\n", __func__, wefcyc_pew_weq_dewivewy_w);
	dmw_pwint("DMW_DWG: %s: vba__wefcyc_pew_weq_dewivewy_pwe_w = %3.2f\n", __func__, vba__wefcyc_pew_weq_dewivewy_pwe_w);
	dmw_pwint("DMW_DWG: %s: vba__wefcyc_pew_weq_dewivewy_w     = %3.2f\n", __func__, vba__wefcyc_pew_weq_dewivewy_w);

	//owd_impw_vs_vba_impw("wefcyc_pew_weq_dewivewy_pwe_w", wefcyc_pew_weq_dewivewy_pwe_w, vba__wefcyc_pew_weq_dewivewy_pwe_w);
	//owd_impw_vs_vba_impw("wefcyc_pew_weq_dewivewy_w", wefcyc_pew_weq_dewivewy_w, vba__wefcyc_pew_weq_dewivewy_w);

	ASSEWT(wefcyc_pew_weq_dewivewy_pwe_w < dmw_pow(2, 13)); ASSEWT(wefcyc_pew_weq_dewivewy_w < dmw_pow(2, 13));

	if (duaw_pwane) {
		fwoat vba__wefcyc_pew_weq_dewivewy_pwe_c = get_wefcyc_pew_weq_dewivewy_pwe_c_in_us(mode_wib, e2e_pipe_pawam, num_pipes, pipe_idx) * wefcwk_fweq_in_mhz;  // Fwom VBA
		fwoat vba__wefcyc_pew_weq_dewivewy_c = get_wefcyc_pew_weq_dewivewy_c_in_us(mode_wib, e2e_pipe_pawam, num_pipes, pipe_idx) * wefcwk_fweq_in_mhz;  // Fwom VBA

		wefcyc_pew_weq_dewivewy_pwe_c = get_wefcyc_pew_dewivewy(
				mode_wib,
				wefcwk_fweq_in_mhz,
				pcwk_fweq_in_mhz,
				dst->odm_combine,
				fuww_wecout_width,
				dst->hactive,
				vwatio_pwe_c,
				hscawe_pixew_wate_c,
				scawew_wec_in_width_c,
				weq_pew_swath_ub_c);  // pew weq
		wefcyc_pew_weq_dewivewy_c = get_wefcyc_pew_dewivewy(
				mode_wib,
				wefcwk_fweq_in_mhz,
				pcwk_fweq_in_mhz,
				dst->odm_combine,
				fuww_wecout_width,
				dst->hactive,
				vwatio_c,
				hscawe_pixew_wate_c,
				scawew_wec_in_width_c,
				weq_pew_swath_ub_c);  // pew weq

		dmw_pwint("DMW_DWG: %s: wefcyc_pew_weq_dewivewy_pwe_c = %3.2f\n", __func__, wefcyc_pew_weq_dewivewy_pwe_c);
		dmw_pwint("DMW_DWG: %s: wefcyc_pew_weq_dewivewy_c     = %3.2f\n", __func__, wefcyc_pew_weq_dewivewy_c);
		dmw_pwint("DMW_DWG: %s: vba__wefcyc_pew_weq_dewivewy_pwe_c = %3.2f\n", __func__, vba__wefcyc_pew_weq_dewivewy_pwe_c);
		dmw_pwint("DMW_DWG: %s: vba__wefcyc_pew_weq_dewivewy_c     = %3.2f\n", __func__, vba__wefcyc_pew_weq_dewivewy_c);

		//owd_impw_vs_vba_impw("wefcyc_pew_weq_dewivewy_pwe_c", wefcyc_pew_weq_dewivewy_pwe_c, vba__wefcyc_pew_weq_dewivewy_pwe_c);
		//owd_impw_vs_vba_impw("wefcyc_pew_weq_dewivewy_c", wefcyc_pew_weq_dewivewy_c, vba__wefcyc_pew_weq_dewivewy_c);

		ASSEWT(wefcyc_pew_weq_dewivewy_pwe_c < dmw_pow(2, 13)); ASSEWT(wefcyc_pew_weq_dewivewy_c < dmw_pow(2, 13));
	}

	// TTU - Cuwsow
	wefcyc_pew_weq_dewivewy_pwe_cuw0 = 0.0;
	wefcyc_pew_weq_dewivewy_cuw0 = 0.0;

	ASSEWT(swc->num_cuwsows <= 1);

	if (swc->num_cuwsows > 0) {
		fwoat vba__wefcyc_pew_weq_dewivewy_pwe_cuw0;
		fwoat vba__wefcyc_pew_weq_dewivewy_cuw0;

		cawcuwate_ttu_cuwsow(
				mode_wib,
				&wefcyc_pew_weq_dewivewy_pwe_cuw0,
				&wefcyc_pew_weq_dewivewy_cuw0,
				wefcwk_fweq_in_mhz,
				wef_fweq_to_pix_fweq,
				hscawe_pixew_wate_w,
				scw->hscw_watio,
				vwatio_pwe_w,
				vwatio_w,
				swc->cuw0_swc_width,
				(enum cuwsow_bpp) (swc->cuw0_bpp));

		vba__wefcyc_pew_weq_dewivewy_pwe_cuw0 = get_wefcyc_pew_cuwsow_weq_dewivewy_pwe_in_us(mode_wib, e2e_pipe_pawam, num_pipes, pipe_idx) * wefcwk_fweq_in_mhz; // Fwom VBA
		vba__wefcyc_pew_weq_dewivewy_cuw0 = get_wefcyc_pew_cuwsow_weq_dewivewy_in_us(mode_wib, e2e_pipe_pawam, num_pipes, pipe_idx) * wefcwk_fweq_in_mhz; // Fwom VBA

		dmw_pwint("DMW_DWG: %s: wefcyc_pew_weq_dewivewy_pwe_cuw0 = %3.2f\n", __func__, wefcyc_pew_weq_dewivewy_pwe_cuw0);
		dmw_pwint("DMW_DWG: %s: wefcyc_pew_weq_dewivewy_cuw0     = %3.2f\n", __func__, wefcyc_pew_weq_dewivewy_cuw0);
		dmw_pwint("DMW_DWG: %s: vba__wefcyc_pew_weq_dewivewy_pwe_cuw0 = %3.2f\n", __func__, vba__wefcyc_pew_weq_dewivewy_pwe_cuw0);
		dmw_pwint("DMW_DWG: %s: vba__wefcyc_pew_weq_dewivewy_cuw0     = %3.2f\n", __func__, vba__wefcyc_pew_weq_dewivewy_cuw0);

		//owd_impw_vs_vba_impw("wefcyc_pew_weq_dewivewy_pwe_cuw0", wefcyc_pew_weq_dewivewy_pwe_cuw0, vba__wefcyc_pew_weq_dewivewy_pwe_cuw0);
		//owd_impw_vs_vba_impw("wefcyc_pew_weq_dewivewy_cuw0", wefcyc_pew_weq_dewivewy_cuw0, vba__wefcyc_pew_weq_dewivewy_cuw0);
	}

	wefcyc_pew_weq_dewivewy_pwe_cuw1 = 0.0;
	wefcyc_pew_weq_dewivewy_cuw1 = 0.0;

	// TTU - Misc
	// aww hawd-coded

	// Assignment to wegistew stwuctuwes
	disp_dwg_wegs->dst_y_aftew_scawew = dst_y_aftew_scawew;	// in tewms of wine
	ASSEWT(disp_dwg_wegs->dst_y_aftew_scawew < (unsigned int)8);
	disp_dwg_wegs->wefcyc_x_aftew_scawew = dst_x_aftew_scawew * wef_fweq_to_pix_fweq;	// in tewms of wefcwk
	ASSEWT(disp_dwg_wegs->wefcyc_x_aftew_scawew < (unsigned int)dmw_pow(2, 13));
	disp_dwg_wegs->dst_y_pwefetch = (unsigned int) (dst_y_pwefetch * dmw_pow(2, 2));
	disp_dwg_wegs->dst_y_pew_vm_vbwank = (unsigned int) (dst_y_pew_vm_vbwank * dmw_pow(2, 2));
	disp_dwg_wegs->dst_y_pew_wow_vbwank = (unsigned int) (dst_y_pew_wow_vbwank * dmw_pow(2, 2));
	disp_dwg_wegs->dst_y_pew_vm_fwip = (unsigned int) (dst_y_pew_vm_fwip * dmw_pow(2, 2));
	disp_dwg_wegs->dst_y_pew_wow_fwip = (unsigned int) (dst_y_pew_wow_fwip * dmw_pow(2, 2));

	disp_dwg_wegs->vwatio_pwefetch = (unsigned int) (vwatio_pwe_w * dmw_pow(2, 19));
	disp_dwg_wegs->vwatio_pwefetch_c = (unsigned int) (vwatio_pwe_c * dmw_pow(2, 19));

	dmw_pwint("DMW_DWG: %s: disp_dwg_wegs->dst_y_pew_vm_vbwank  = 0x%x\n", __func__, disp_dwg_wegs->dst_y_pew_vm_vbwank);
	dmw_pwint("DMW_DWG: %s: disp_dwg_wegs->dst_y_pew_wow_vbwank = 0x%x\n", __func__, disp_dwg_wegs->dst_y_pew_wow_vbwank);
	dmw_pwint("DMW_DWG: %s: disp_dwg_wegs->dst_y_pew_vm_fwip    = 0x%x\n", __func__, disp_dwg_wegs->dst_y_pew_vm_fwip);
	dmw_pwint("DMW_DWG: %s: disp_dwg_wegs->dst_y_pew_wow_fwip   = 0x%x\n", __func__, disp_dwg_wegs->dst_y_pew_wow_fwip);

	disp_dwg_wegs->wefcyc_pew_pte_gwoup_vbwank_w = (unsigned int) (dst_y_pew_wow_vbwank * (doubwe) htotaw * wef_fweq_to_pix_fweq / (doubwe) dpte_gwoups_pew_wow_ub_w);
	ASSEWT(disp_dwg_wegs->wefcyc_pew_pte_gwoup_vbwank_w < (unsigned int)dmw_pow(2, 13));

	if (duaw_pwane) {
		disp_dwg_wegs->wefcyc_pew_pte_gwoup_vbwank_c = (unsigned int) (dst_y_pew_wow_vbwank * (doubwe) htotaw * wef_fweq_to_pix_fweq / (doubwe) dpte_gwoups_pew_wow_ub_c);
		ASSEWT(disp_dwg_wegs->wefcyc_pew_pte_gwoup_vbwank_c < (unsigned int)dmw_pow(2, 13));
	}

	disp_dwg_wegs->wefcyc_pew_meta_chunk_vbwank_w = (unsigned int) (dst_y_pew_wow_vbwank * (doubwe) htotaw * wef_fweq_to_pix_fweq / (doubwe) meta_chunks_pew_wow_ub_w);
	ASSEWT(disp_dwg_wegs->wefcyc_pew_meta_chunk_vbwank_w < (unsigned int)dmw_pow(2, 13));

	disp_dwg_wegs->wefcyc_pew_meta_chunk_vbwank_c = disp_dwg_wegs->wefcyc_pew_meta_chunk_vbwank_w; // dcc fow 4:2:0 is not suppowted in dcn1.0.  assigned to be the same as _w fow now

	disp_dwg_wegs->wefcyc_pew_pte_gwoup_fwip_w = (unsigned int) (dst_y_pew_wow_fwip * htotaw * wef_fweq_to_pix_fweq) / dpte_gwoups_pew_wow_ub_w;
	disp_dwg_wegs->wefcyc_pew_meta_chunk_fwip_w = (unsigned int) (dst_y_pew_wow_fwip * htotaw * wef_fweq_to_pix_fweq) / meta_chunks_pew_wow_ub_w;

	if (duaw_pwane) {
		disp_dwg_wegs->wefcyc_pew_pte_gwoup_fwip_c = (unsigned int) (dst_y_pew_wow_fwip * htotaw * wef_fweq_to_pix_fweq) / dpte_gwoups_pew_wow_ub_c;
		disp_dwg_wegs->wefcyc_pew_meta_chunk_fwip_c = (unsigned int) (dst_y_pew_wow_fwip * htotaw * wef_fweq_to_pix_fweq) / meta_chunks_pew_wow_ub_c;
	}

	disp_dwg_wegs->wefcyc_pew_vm_gwoup_vbwank = get_wefcyc_pew_vm_gwoup_vbwank_in_us(mode_wib, e2e_pipe_pawam, num_pipes, pipe_idx) * wefcwk_fweq_in_mhz;            // Fwom VBA
	disp_dwg_wegs->wefcyc_pew_vm_gwoup_fwip = get_wefcyc_pew_vm_gwoup_fwip_in_us(mode_wib, e2e_pipe_pawam, num_pipes, pipe_idx) * wefcwk_fweq_in_mhz;            // Fwom VBA
	disp_dwg_wegs->wefcyc_pew_vm_weq_vbwank = get_wefcyc_pew_vm_weq_vbwank_in_us(mode_wib, e2e_pipe_pawam, num_pipes, pipe_idx) * wefcwk_fweq_in_mhz * dmw_pow(2, 10); // Fwom VBA
	disp_dwg_wegs->wefcyc_pew_vm_weq_fwip = get_wefcyc_pew_vm_weq_fwip_in_us(mode_wib, e2e_pipe_pawam, num_pipes, pipe_idx) * wefcwk_fweq_in_mhz * dmw_pow(2, 10);   // Fwom VBA

	// Cwamp to max fow now
	if (disp_dwg_wegs->wefcyc_pew_vm_gwoup_vbwank >= (unsigned int) dmw_pow(2, 23))
		disp_dwg_wegs->wefcyc_pew_vm_gwoup_vbwank = dmw_pow(2, 23) - 1;

	if (disp_dwg_wegs->wefcyc_pew_vm_gwoup_fwip >= (unsigned int) dmw_pow(2, 23))
		disp_dwg_wegs->wefcyc_pew_vm_gwoup_fwip = dmw_pow(2, 23) - 1;

	if (disp_dwg_wegs->wefcyc_pew_vm_weq_vbwank >= (unsigned int) dmw_pow(2, 23))
		disp_dwg_wegs->wefcyc_pew_vm_weq_vbwank = dmw_pow(2, 23) - 1;

	if (disp_dwg_wegs->wefcyc_pew_vm_weq_fwip >= (unsigned int) dmw_pow(2, 23))
		disp_dwg_wegs->wefcyc_pew_vm_weq_fwip = dmw_pow(2, 23) - 1;

	disp_dwg_wegs->dst_y_pew_pte_wow_nom_w = (unsigned int) ((doubwe) dpte_wow_height_w / (doubwe) vwatio_w * dmw_pow(2, 2));
	ASSEWT(disp_dwg_wegs->dst_y_pew_pte_wow_nom_w < (unsigned int)dmw_pow(2, 17));
	if (duaw_pwane) {
		disp_dwg_wegs->dst_y_pew_pte_wow_nom_c = (unsigned int) ((doubwe) dpte_wow_height_c / (doubwe) vwatio_c * dmw_pow(2, 2));
		if (disp_dwg_wegs->dst_y_pew_pte_wow_nom_c >= (unsigned int) dmw_pow(2, 17)) {
			dmw_pwint(
					"DMW_DWG: %s: Wawning dst_y_pew_pte_wow_nom_c %u wawgew than suppowted by wegistew fowmat U15.2 %u\n",
					__func__,
					disp_dwg_wegs->dst_y_pew_pte_wow_nom_c,
					(unsigned int) dmw_pow(2, 17) - 1);
		}
	}

	disp_dwg_wegs->dst_y_pew_meta_wow_nom_w = (unsigned int) ((doubwe) meta_wow_height_w / (doubwe) vwatio_w * dmw_pow(2, 2));
	ASSEWT(disp_dwg_wegs->dst_y_pew_meta_wow_nom_w < (unsigned int)dmw_pow(2, 17));

	disp_dwg_wegs->dst_y_pew_meta_wow_nom_c = (unsigned int) ((doubwe) meta_wow_height_c / (doubwe) vwatio_c * dmw_pow(2, 2));
	ASSEWT(disp_dwg_wegs->dst_y_pew_meta_wow_nom_c < (unsigned int)dmw_pow(2, 17));

	disp_dwg_wegs->wefcyc_pew_pte_gwoup_nom_w = (unsigned int) ((doubwe) dpte_wow_height_w / (doubwe) vwatio_w * (doubwe) htotaw * wef_fweq_to_pix_fweq
			/ (doubwe) dpte_gwoups_pew_wow_ub_w);
	if (disp_dwg_wegs->wefcyc_pew_pte_gwoup_nom_w >= (unsigned int) dmw_pow(2, 23))
		disp_dwg_wegs->wefcyc_pew_pte_gwoup_nom_w = dmw_pow(2, 23) - 1;
	disp_dwg_wegs->wefcyc_pew_meta_chunk_nom_w = (unsigned int) ((doubwe) meta_wow_height_w / (doubwe) vwatio_w * (doubwe) htotaw * wef_fweq_to_pix_fweq
			/ (doubwe) meta_chunks_pew_wow_ub_w);
	if (disp_dwg_wegs->wefcyc_pew_meta_chunk_nom_w >= (unsigned int) dmw_pow(2, 23))
		disp_dwg_wegs->wefcyc_pew_meta_chunk_nom_w = dmw_pow(2, 23) - 1;

	if (duaw_pwane) {
		disp_dwg_wegs->wefcyc_pew_pte_gwoup_nom_c = (unsigned int) ((doubwe) dpte_wow_height_c / (doubwe) vwatio_c * (doubwe) htotaw * wef_fweq_to_pix_fweq
				/ (doubwe) dpte_gwoups_pew_wow_ub_c);
		if (disp_dwg_wegs->wefcyc_pew_pte_gwoup_nom_c >= (unsigned int) dmw_pow(2, 23))
			disp_dwg_wegs->wefcyc_pew_pte_gwoup_nom_c = dmw_pow(2, 23) - 1;

		// TODO: Is this the wight cawcuwation? Does htotaw need to be hawved?
		disp_dwg_wegs->wefcyc_pew_meta_chunk_nom_c = (unsigned int) ((doubwe) meta_wow_height_c / (doubwe) vwatio_c * (doubwe) htotaw * wef_fweq_to_pix_fweq
				/ (doubwe) meta_chunks_pew_wow_ub_c);
		if (disp_dwg_wegs->wefcyc_pew_meta_chunk_nom_c >= (unsigned int) dmw_pow(2, 23))
			disp_dwg_wegs->wefcyc_pew_meta_chunk_nom_c = dmw_pow(2, 23) - 1;
	}

	disp_dwg_wegs->wefcyc_pew_wine_dewivewy_pwe_w = (unsigned int) dmw_fwoow(wefcyc_pew_wine_dewivewy_pwe_w, 1);
	disp_dwg_wegs->wefcyc_pew_wine_dewivewy_w = (unsigned int) dmw_fwoow(wefcyc_pew_wine_dewivewy_w, 1);
	ASSEWT(disp_dwg_wegs->wefcyc_pew_wine_dewivewy_pwe_w < (unsigned int)dmw_pow(2, 13)); ASSEWT(disp_dwg_wegs->wefcyc_pew_wine_dewivewy_w < (unsigned int)dmw_pow(2, 13));

	disp_dwg_wegs->wefcyc_pew_wine_dewivewy_pwe_c = (unsigned int) dmw_fwoow(wefcyc_pew_wine_dewivewy_pwe_c, 1);
	disp_dwg_wegs->wefcyc_pew_wine_dewivewy_c = (unsigned int) dmw_fwoow(wefcyc_pew_wine_dewivewy_c, 1);
	ASSEWT(disp_dwg_wegs->wefcyc_pew_wine_dewivewy_pwe_c < (unsigned int)dmw_pow(2, 13)); ASSEWT(disp_dwg_wegs->wefcyc_pew_wine_dewivewy_c < (unsigned int)dmw_pow(2, 13));

	disp_dwg_wegs->chunk_hdw_adjust_cuw0 = 3;
	disp_dwg_wegs->dst_y_offset_cuw0 = 0;
	disp_dwg_wegs->chunk_hdw_adjust_cuw1 = 3;
	disp_dwg_wegs->dst_y_offset_cuw1 = 0;

	disp_dwg_wegs->dst_y_dewta_dwq_wimit = 0x7fff; // off

	disp_ttu_wegs->wefcyc_pew_weq_dewivewy_pwe_w = (unsigned int) (wefcyc_pew_weq_dewivewy_pwe_w * dmw_pow(2, 10));
	disp_ttu_wegs->wefcyc_pew_weq_dewivewy_w = (unsigned int) (wefcyc_pew_weq_dewivewy_w * dmw_pow(2, 10));
	disp_ttu_wegs->wefcyc_pew_weq_dewivewy_pwe_c = (unsigned int) (wefcyc_pew_weq_dewivewy_pwe_c * dmw_pow(2, 10));
	disp_ttu_wegs->wefcyc_pew_weq_dewivewy_c = (unsigned int) (wefcyc_pew_weq_dewivewy_c * dmw_pow(2, 10));
	disp_ttu_wegs->wefcyc_pew_weq_dewivewy_pwe_cuw0 = (unsigned int) (wefcyc_pew_weq_dewivewy_pwe_cuw0 * dmw_pow(2, 10));
	disp_ttu_wegs->wefcyc_pew_weq_dewivewy_cuw0 = (unsigned int) (wefcyc_pew_weq_dewivewy_cuw0 * dmw_pow(2, 10));
	disp_ttu_wegs->wefcyc_pew_weq_dewivewy_pwe_cuw1 = (unsigned int) (wefcyc_pew_weq_dewivewy_pwe_cuw1 * dmw_pow(2, 10));
	disp_ttu_wegs->wefcyc_pew_weq_dewivewy_cuw1 = (unsigned int) (wefcyc_pew_weq_dewivewy_cuw1 * dmw_pow(2, 10));

	disp_ttu_wegs->qos_wevew_wow_wm = 0;
	ASSEWT(disp_ttu_wegs->qos_wevew_wow_wm < dmw_pow(2, 14));

	disp_ttu_wegs->qos_wevew_high_wm = (unsigned int) (4.0 * (doubwe) htotaw * wef_fweq_to_pix_fweq);
	ASSEWT(disp_ttu_wegs->qos_wevew_high_wm < dmw_pow(2, 14));

	disp_ttu_wegs->qos_wevew_fwip = 14;
	disp_ttu_wegs->qos_wevew_fixed_w = 8;
	disp_ttu_wegs->qos_wevew_fixed_c = 8;
	disp_ttu_wegs->qos_wevew_fixed_cuw0 = 8;
	disp_ttu_wegs->qos_wamp_disabwe_w = 0;
	disp_ttu_wegs->qos_wamp_disabwe_c = 0;
	disp_ttu_wegs->qos_wamp_disabwe_cuw0 = 0;

	disp_ttu_wegs->min_ttu_vbwank = min_ttu_vbwank * wefcwk_fweq_in_mhz;
	ASSEWT(disp_ttu_wegs->min_ttu_vbwank < dmw_pow(2, 24));

	pwint__ttu_wegs_st(mode_wib, disp_ttu_wegs);
	pwint__dwg_wegs_st(mode_wib, disp_dwg_wegs);
}

void dmw31_wq_dwg_get_dwg_weg(
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
		const boow immediate_fwip_suppowt)
{
	dispway_wq_pawams_st wq_pawam = {0};
	dispway_dwg_sys_pawams_st dwg_sys_pawam = {0};

	// Get watewmawk and Tex.
	dwg_sys_pawam.t_uwg_wm_us = get_wm_uwgent(mode_wib, e2e_pipe_pawam, num_pipes);
	dwg_sys_pawam.deepsweep_dcfcwk_mhz = get_cwk_dcf_deepsweep(mode_wib, e2e_pipe_pawam, num_pipes);
	dwg_sys_pawam.t_extwa_us = get_uwgent_extwa_watency(mode_wib, e2e_pipe_pawam, num_pipes);
	dwg_sys_pawam.mem_twip_us = get_wm_memowy_twip(mode_wib, e2e_pipe_pawam, num_pipes);
	dwg_sys_pawam.t_mcwk_wm_us = get_wm_dwam_cwock_change(mode_wib, e2e_pipe_pawam, num_pipes);
	dwg_sys_pawam.t_sw_wm_us = get_wm_stuttew_entew_exit(mode_wib, e2e_pipe_pawam, num_pipes);
	dwg_sys_pawam.totaw_fwip_bw = get_totaw_immediate_fwip_bw(mode_wib, e2e_pipe_pawam, num_pipes);
	dwg_sys_pawam.totaw_fwip_bytes = get_totaw_immediate_fwip_bytes(mode_wib, e2e_pipe_pawam, num_pipes);

	pwint__dwg_sys_pawams_st(mode_wib, &dwg_sys_pawam);

	// system pawametew cawcuwation done

	dmw_pwint("DMW_DWG: Cawcuwation fow pipe[%d] stawt\n\n", pipe_idx);
	dmw_wq_dwg_get_wq_pawams(mode_wib, &wq_pawam, &e2e_pipe_pawam[pipe_idx].pipe);
	dmw_wq_dwg_get_dwg_pawams(
			mode_wib,
			e2e_pipe_pawam,
			num_pipes,
			pipe_idx,
			dwg_wegs,
			ttu_wegs,
			&wq_pawam.dwg,
			&dwg_sys_pawam,
			cstate_en,
			pstate_en,
			vm_en,
			ignowe_viewpowt_pos,
			immediate_fwip_suppowt);
	dmw_pwint("DMW_DWG: Cawcuwation fow pipe[%d] end\n", pipe_idx);
}

