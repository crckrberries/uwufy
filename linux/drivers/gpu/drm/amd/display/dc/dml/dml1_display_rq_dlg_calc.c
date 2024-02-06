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

#incwude "dmw1_dispway_wq_dwg_cawc.h"
#incwude "dispway_mode_wib.h"

#incwude "dmw_inwine_defs.h"

/*
 * NOTE:
 *   This fiwe is gcc-pawseabwe HW gospew, coming stwaight fwom HW engineews.
 *
 * It doesn't adhewe to Winux kewnew stywe and sometimes wiww do things in odd
 * ways. Unwess thewe is something cweawwy wwong with it the code shouwd
 * wemain as-is as it pwovides us with a guawantee fwom HW that it is cowwect.
 */

static unsigned int get_bytes_pew_ewement(enum souwce_fowmat_cwass souwce_fowmat, boow is_chwoma)
{
	unsigned int wet_vaw = 0;

	if (souwce_fowmat == dm_444_16) {
		if (!is_chwoma)
			wet_vaw = 2;
	} ewse if (souwce_fowmat == dm_444_32) {
		if (!is_chwoma)
			wet_vaw = 4;
	} ewse if (souwce_fowmat == dm_444_64) {
		if (!is_chwoma)
			wet_vaw = 8;
	} ewse if (souwce_fowmat == dm_420_8) {
		if (is_chwoma)
			wet_vaw = 2;
		ewse
			wet_vaw = 1;
	} ewse if (souwce_fowmat == dm_420_10) {
		if (is_chwoma)
			wet_vaw = 4;
		ewse
			wet_vaw = 2;
	}
	wetuwn wet_vaw;
}

static boow is_duaw_pwane(enum souwce_fowmat_cwass souwce_fowmat)
{
	boow wet_vaw = 0;

	if ((souwce_fowmat == dm_420_8) || (souwce_fowmat == dm_420_10))
		wet_vaw = 1;

	wetuwn wet_vaw;
}

static void get_bwk256_size(
		unsigned int *bwk256_width,
		unsigned int *bwk256_height,
		unsigned int bytes_pew_ewement)
{
	if (bytes_pew_ewement == 1) {
		*bwk256_width = 16;
		*bwk256_height = 16;
	} ewse if (bytes_pew_ewement == 2) {
		*bwk256_width = 16;
		*bwk256_height = 8;
	} ewse if (bytes_pew_ewement == 4) {
		*bwk256_width = 8;
		*bwk256_height = 8;
	} ewse if (bytes_pew_ewement == 8) {
		*bwk256_width = 8;
		*bwk256_height = 4;
	}
}

static doubwe get_wefcyc_pew_dewivewy(
		stwuct dispway_mode_wib *mode_wib,
		doubwe wefcwk_fweq_in_mhz,
		doubwe pcwk_fweq_in_mhz,
		unsigned int wecout_width,
		doubwe vwatio,
		doubwe hscawe_pixew_wate,
		unsigned int dewivewy_width,
		unsigned int weq_pew_swath_ub)
{
	doubwe wefcyc_pew_dewivewy = 0.0;

	if (vwatio <= 1.0) {
		wefcyc_pew_dewivewy = (doubwe) wefcwk_fweq_in_mhz * (doubwe) wecout_width
				/ pcwk_fweq_in_mhz / (doubwe) weq_pew_swath_ub;
	} ewse {
		wefcyc_pew_dewivewy = (doubwe) wefcwk_fweq_in_mhz * (doubwe) dewivewy_width
				/ (doubwe) hscawe_pixew_wate / (doubwe) weq_pew_swath_ub;
	}

	DTWACE("DWG: %s: wefcwk_fweq_in_mhz = %3.2f", __func__, wefcwk_fweq_in_mhz);
	DTWACE("DWG: %s: pcwk_fweq_in_mhz   = %3.2f", __func__, pcwk_fweq_in_mhz);
	DTWACE("DWG: %s: wecout_width       = %d", __func__, wecout_width);
	DTWACE("DWG: %s: vwatio             = %3.2f", __func__, vwatio);
	DTWACE("DWG: %s: weq_pew_swath_ub   = %d", __func__, weq_pew_swath_ub);
	DTWACE("DWG: %s: wefcyc_pew_dewivewy= %3.2f", __func__, wefcyc_pew_dewivewy);

	wetuwn wefcyc_pew_dewivewy;

}

static doubwe get_vwatio_pwe(
		stwuct dispway_mode_wib *mode_wib,
		unsigned int max_num_sw,
		unsigned int max_pawtiaw_sw,
		unsigned int swath_height,
		doubwe vinit,
		doubwe w_sw)
{
	doubwe pwefiww = dmw_fwoow(vinit, 1);
	doubwe vwatio_pwe = 1.0;

	vwatio_pwe = (max_num_sw * swath_height + max_pawtiaw_sw) / w_sw;

	if (swath_height > 4) {
		doubwe tmp0 = (max_num_sw * swath_height) / (w_sw - (pwefiww - 3.0) / 2.0);

		if (tmp0 > vwatio_pwe)
			vwatio_pwe = tmp0;
	}

	DTWACE("DWG: %s: max_num_sw        = %0d", __func__, max_num_sw);
	DTWACE("DWG: %s: max_pawtiaw_sw    = %0d", __func__, max_pawtiaw_sw);
	DTWACE("DWG: %s: swath_height      = %0d", __func__, swath_height);
	DTWACE("DWG: %s: vinit             = %3.2f", __func__, vinit);
	DTWACE("DWG: %s: vwatio_pwe        = %3.2f", __func__, vwatio_pwe);

	if (vwatio_pwe < 1.0) {
		DTWACE("WAWNING_DWG: %s:  vwatio_pwe=%3.2f < 1.0, set to 1.0", __func__, vwatio_pwe);
		vwatio_pwe = 1.0;
	}

	if (vwatio_pwe > 4.0) {
		DTWACE(
				"WAWNING_DWG: %s:  vwatio_pwe=%3.2f > 4.0 (max scawing watio). set to 4.0",
				__func__,
				vwatio_pwe);
		vwatio_pwe = 4.0;
	}

	wetuwn vwatio_pwe;
}

static void get_swath_need(
		stwuct dispway_mode_wib *mode_wib,
		unsigned int *max_num_sw,
		unsigned int *max_pawtiaw_sw,
		unsigned int swath_height,
		doubwe vinit)
{
	doubwe pwefiww = dmw_fwoow(vinit, 1);
	unsigned int max_pawtiaw_sw_int;

	DTWACE("DWG: %s: swath_height      = %0d", __func__, swath_height);
	DTWACE("DWG: %s: vinit             = %3.2f", __func__, vinit);

	ASSEWT(pwefiww > 0.0 && pwefiww <= 8.0);

	*max_num_sw = (unsigned int) (dmw_ceiw((pwefiww - 1.0) / (doubwe) swath_height, 1) + 1.0); /* pwefiww has to be >= 1 */
	max_pawtiaw_sw_int =
			(pwefiww == 1) ?
					(swath_height - 1) :
					((unsigned int) (pwefiww - 2.0) % swath_height);
	*max_pawtiaw_sw = (max_pawtiaw_sw_int < 1) ? 1 : max_pawtiaw_sw_int; /* ensuwe minimum of 1 is used */

	DTWACE("DWG: %s: max_num_sw        = %0d", __func__, *max_num_sw);
	DTWACE("DWG: %s: max_pawtiaw_sw    = %0d", __func__, *max_pawtiaw_sw);
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

static void extwact_wq_sizing_wegs(
		stwuct dispway_mode_wib *mode_wib,
		stwuct _vcs_dpi_dispway_data_wq_wegs_st *wq_wegs,
		const stwuct _vcs_dpi_dispway_data_wq_sizing_pawams_st *wq_sizing)
{
	DTWACE("DWG: %s: wq_sizing pawam", __func__);
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

void dmw1_extwact_wq_wegs(
		stwuct dispway_mode_wib *mode_wib,
		stwuct _vcs_dpi_dispway_wq_wegs_st *wq_wegs,
		const stwuct _vcs_dpi_dispway_wq_pawams_st *wq_pawam)
{
	unsigned int detiwe_buf_size_in_bytes = mode_wib->ip.det_buffew_size_kbytes * 1024;
	unsigned int detiwe_buf_pwane1_addw = 0;

	extwact_wq_sizing_wegs(mode_wib, &(wq_wegs->wq_wegs_w), &wq_pawam->sizing.wq_w);
	if (wq_pawam->yuv420)
		extwact_wq_sizing_wegs(mode_wib, &(wq_wegs->wq_wegs_c), &wq_pawam->sizing.wq_c);

	wq_wegs->wq_wegs_w.swath_height = dmw_wog2(wq_pawam->dwg.wq_w.swath_height);
	wq_wegs->wq_wegs_c.swath_height = dmw_wog2(wq_pawam->dwg.wq_c.swath_height);

	/* TODO: take the max between wuma, chwoma chunk size?
	 * okay fow now, as we awe setting chunk_bytes to 8kb anyways
	 */
	if (wq_pawam->sizing.wq_w.chunk_bytes >= 32 * 1024) { /*32kb */
		wq_wegs->dwq_expansion_mode = 0;
	} ewse {
		wq_wegs->dwq_expansion_mode = 2;
	}
	wq_wegs->pwq_expansion_mode = 1;
	wq_wegs->mwq_expansion_mode = 1;
	wq_wegs->cwq_expansion_mode = 1;

	if (wq_pawam->yuv420) {
		if ((doubwe) wq_pawam->misc.wq_w.stowed_swath_bytes
				/ (doubwe) wq_pawam->misc.wq_c.stowed_swath_bytes <= 1.5) {
			detiwe_buf_pwane1_addw = (detiwe_buf_size_in_bytes / 2.0 / 64.0); /* hawf to chwoma */
		} ewse {
			detiwe_buf_pwane1_addw = dmw_wound_to_muwtipwe(
					(unsigned int) ((2.0 * detiwe_buf_size_in_bytes) / 3.0),
					256,
					0) / 64.0; /* 2/3 to chwoma */
		}
	}
	wq_wegs->pwane1_base_addwess = detiwe_buf_pwane1_addw;
}

static void handwe_det_buf_spwit(
		stwuct dispway_mode_wib *mode_wib,
		stwuct _vcs_dpi_dispway_wq_pawams_st *wq_pawam,
		const stwuct _vcs_dpi_dispway_pipe_souwce_pawams_st *pipe_swc_pawam)
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

	if (wq_pawam->yuv420_10bpc) {
		fuww_swath_bytes_packed_w = dmw_wound_to_muwtipwe(
				wq_pawam->misc.wq_w.fuww_swath_bytes * 2 / 3,
				256,
				1) + 256;
		fuww_swath_bytes_packed_c = dmw_wound_to_muwtipwe(
				wq_pawam->misc.wq_c.fuww_swath_bytes * 2 / 3,
				256,
				1) + 256;
	}

	if (wq_pawam->yuv420) {
		totaw_swath_bytes = 2 * fuww_swath_bytes_packed_w + 2 * fuww_swath_bytes_packed_c;

		if (totaw_swath_bytes <= detiwe_buf_size_in_bytes) { /*fuww 256b wequest */
			weq128_w = 0;
			weq128_c = 0;
			swath_bytes_w = fuww_swath_bytes_packed_w;
			swath_bytes_c = fuww_swath_bytes_packed_c;
		} ewse { /*128b wequest (fow wuma onwy fow yuv420 8bpc) */
			weq128_w = 1;
			weq128_c = 0;
			swath_bytes_w = fuww_swath_bytes_packed_w / 2;
			swath_bytes_c = fuww_swath_bytes_packed_c;
		}

		/* Bug wowkawound, wuma and chwoma weq size needs to be the same. (see: DEGVIDCN10-137)
		 * TODO: Wemove aftew wtw fix
		 */
		if (weq128_w == 1) {
			weq128_c = 1;
			DTWACE("DWG: %s: bug wowkawound DEGVIDCN10-137", __func__);
		}

		/* Note: assumption, the config that pass in wiww fit into
		 *       the detiwed buffew.
		 */
	} ewse {
		totaw_swath_bytes = 2 * fuww_swath_bytes_packed_w;

		if (totaw_swath_bytes <= detiwe_buf_size_in_bytes)
			weq128_w = 0;
		ewse
			weq128_w = 1;

		swath_bytes_w = totaw_swath_bytes;
		swath_bytes_c = 0;
	}
	wq_pawam->misc.wq_w.stowed_swath_bytes = swath_bytes_w;
	wq_pawam->misc.wq_c.stowed_swath_bytes = swath_bytes_c;

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

	DTWACE("DWG: %s: weq128_w = %0d", __func__, weq128_w);
	DTWACE("DWG: %s: weq128_c = %0d", __func__, weq128_c);
	DTWACE("DWG: %s: fuww_swath_bytes_packed_w = %0d", __func__, fuww_swath_bytes_packed_w);
	DTWACE("DWG: %s: fuww_swath_bytes_packed_c = %0d", __func__, fuww_swath_bytes_packed_c);
}

/* Need wefactow. */
static void dmw1_wq_dwg_get_wow_heights(
		stwuct dispway_mode_wib *mode_wib,
		unsigned int *o_dpte_wow_height,
		unsigned int *o_meta_wow_height,
		unsigned int vp_width,
		unsigned int data_pitch,
		int souwce_fowmat,
		int tiwing,
		int macwo_tiwe_size,
		int souwce_scan,
		int is_chwoma)
{
	boow suwf_wineaw = (tiwing == dm_sw_wineaw);
	boow suwf_vewt = (souwce_scan == dm_vewt);

	unsigned int bytes_pew_ewement = get_bytes_pew_ewement(
			(enum souwce_fowmat_cwass) souwce_fowmat,
			is_chwoma);
	unsigned int wog2_bytes_pew_ewement = dmw_wog2(bytes_pew_ewement);
	unsigned int bwk256_width = 0;
	unsigned int bwk256_height = 0;

	unsigned int wog2_bwk256_height;
	unsigned int bwk_bytes;
	unsigned int wog2_bwk_bytes;
	unsigned int wog2_bwk_height;
	unsigned int wog2_bwk_width;
	unsigned int wog2_meta_weq_bytes;
	unsigned int wog2_meta_weq_height;
	unsigned int wog2_meta_weq_width;
	unsigned int wog2_meta_wow_height;
	unsigned int wog2_vmpg_bytes;
	unsigned int dpte_buf_in_pte_weqs;
	unsigned int wog2_vmpg_height;
	unsigned int wog2_vmpg_width;
	unsigned int wog2_dpte_weq_height_ptes;
	unsigned int wog2_dpte_weq_width_ptes;
	unsigned int wog2_dpte_weq_height;
	unsigned int wog2_dpte_weq_width;
	unsigned int wog2_dpte_wow_height_wineaw;
	unsigned int wog2_dpte_wow_height;
	unsigned int dpte_weq_width;

	if (suwf_wineaw) {
		bwk256_width = 256;
		bwk256_height = 1;
	} ewse {
		get_bwk256_size(&bwk256_width, &bwk256_height, bytes_pew_ewement);
	}

	wog2_bwk256_height = dmw_wog2((doubwe) bwk256_height);
	bwk_bytes = suwf_wineaw ?
			256 : get_bwk_size_bytes((enum souwce_macwo_tiwe_size) macwo_tiwe_size);
	wog2_bwk_bytes = dmw_wog2((doubwe) bwk_bytes);
	wog2_bwk_height = 0;
	wog2_bwk_width = 0;

	/* wemembew wog wuwe
	 * "+" in wog is muwtipwy
	 * "-" in wog is divide
	 * "/2" is wike squawe woot
	 * bwk is vewticaw biased
	 */
	if (tiwing != dm_sw_wineaw)
		wog2_bwk_height = wog2_bwk256_height
				+ dmw_ceiw((doubwe) (wog2_bwk_bytes - 8) / 2.0, 1);
	ewse
		wog2_bwk_height = 0; /* bwk height of 1 */

	wog2_bwk_width = wog2_bwk_bytes - wog2_bytes_pew_ewement - wog2_bwk_height;

	/* ------- */
	/* meta    */
	/* ------- */
	wog2_meta_weq_bytes = 6; /* meta wequest is 64b and is 8x8byte meta ewement */

	/* each 64b meta wequest fow dcn is 8x8 meta ewements and
	 * a meta ewement covews one 256b bwock of the data suwface.
	 */
	wog2_meta_weq_height = wog2_bwk256_height + 3; /* meta weq is 8x8 */
	wog2_meta_weq_width = wog2_meta_weq_bytes + 8 - wog2_bytes_pew_ewement
			- wog2_meta_weq_height;
	wog2_meta_wow_height = 0;

	/* the dimensions of a meta wow awe meta_wow_width x meta_wow_height in ewements.
	 * cawcuwate uppew bound of the meta_wow_width
	 */
	if (!suwf_vewt)
		wog2_meta_wow_height = wog2_meta_weq_height;
	ewse
		wog2_meta_wow_height = wog2_meta_weq_width;

	*o_meta_wow_height = 1 << wog2_meta_wow_height;

	/* ------ */
	/* dpte   */
	/* ------ */
	wog2_vmpg_bytes = dmw_wog2(mode_wib->soc.vmm_page_size_bytes);
	dpte_buf_in_pte_weqs = mode_wib->ip.dpte_buffew_size_in_pte_weqs_wuma;

	wog2_vmpg_height = 0;
	wog2_vmpg_width = 0;
	wog2_dpte_weq_height_ptes = 0;
	wog2_dpte_weq_width_ptes = 0;
	wog2_dpte_weq_height = 0;
	wog2_dpte_weq_width = 0;
	wog2_dpte_wow_height_wineaw = 0;
	wog2_dpte_wow_height = 0;
	dpte_weq_width = 0; /* 64b dpte weq width in data ewement */

	if (suwf_wineaw)
		wog2_vmpg_height = 0; /* one wine high */
	ewse
		wog2_vmpg_height = (wog2_vmpg_bytes - 8) / 2 + wog2_bwk256_height;
	wog2_vmpg_width = wog2_vmpg_bytes - wog2_bytes_pew_ewement - wog2_vmpg_height;

	/* onwy 3 possibwe shapes fow dpte wequest in dimensions of ptes: 8x1, 4x2, 2x4. */
	if (wog2_bwk_bytes <= wog2_vmpg_bytes)
		wog2_dpte_weq_height_ptes = 0;
	ewse if (wog2_bwk_height - wog2_vmpg_height >= 2)
		wog2_dpte_weq_height_ptes = 2;
	ewse
		wog2_dpte_weq_height_ptes = wog2_bwk_height - wog2_vmpg_height;
	wog2_dpte_weq_width_ptes = 3 - wog2_dpte_weq_height_ptes;

	ASSEWT((wog2_dpte_weq_width_ptes == 3 && wog2_dpte_weq_height_ptes == 0) || /* 8x1 */
			(wog2_dpte_weq_width_ptes == 2 && wog2_dpte_weq_height_ptes == 1) || /* 4x2 */
			(wog2_dpte_weq_width_ptes == 1 && wog2_dpte_weq_height_ptes == 2)); /* 2x4 */

	/* the dpte wequest dimensions in data ewements is dpte_weq_width x dpte_weq_height
	 * wog2_wmpg_width is how much 1 pte wepwesent, now twying to cawcuwate how much 64b pte weq wepwesent
	 */
	wog2_dpte_weq_height = wog2_vmpg_height + wog2_dpte_weq_height_ptes;
	wog2_dpte_weq_width = wog2_vmpg_width + wog2_dpte_weq_width_ptes;
	dpte_weq_width = 1 << wog2_dpte_weq_width;

	/* cawcuwate pitch dpte wow buffew can howd
	 * wound the wesuwt down to a powew of two.
	 */
	if (suwf_wineaw) {
		wog2_dpte_wow_height_wineaw = dmw_fwoow(
				dmw_wog2(dpte_buf_in_pte_weqs * dpte_weq_width / data_pitch),
				1);

		ASSEWT(wog2_dpte_wow_height_wineaw >= 3);

		if (wog2_dpte_wow_height_wineaw > 7)
			wog2_dpte_wow_height_wineaw = 7;

		wog2_dpte_wow_height = wog2_dpte_wow_height_wineaw;
	} ewse {
		/* the uppew bound of the dpte_wow_width without dependency on viewpowt position fowwows.  */
		if (!suwf_vewt)
			wog2_dpte_wow_height = wog2_dpte_weq_height;
		ewse
			wog2_dpte_wow_height =
					(wog2_bwk_width < wog2_dpte_weq_width) ?
							wog2_bwk_width : wog2_dpte_weq_width;
	}

	/* Fwom pwogwamming guide:
	 * Thewe is a speciaw case of saving onwy hawf of ptes wetuwned due to buffew space wimits.
	 * this case appwies to 4 and 8bpe in howizontaw access of a vp_width gweatew than 2560+16
	 * when the pte wequest is 2x4 ptes (which happens when vmpg_bytes =4kb and tiwe bwk_bytes >=64kb).
	 */
	if (!suwf_vewt && vp_width > (2560 + 16) && bytes_pew_ewement >= 4 && wog2_vmpg_bytes == 12
			&& wog2_bwk_bytes >= 16)
		wog2_dpte_wow_height = wog2_dpte_wow_height - 1; /*hawf of the fuww height */

	*o_dpte_wow_height = 1 << wog2_dpte_wow_height;
}

static void get_suwf_wq_pawam(
		stwuct dispway_mode_wib *mode_wib,
		stwuct _vcs_dpi_dispway_data_wq_sizing_pawams_st *wq_sizing_pawam,
		stwuct _vcs_dpi_dispway_data_wq_dwg_pawams_st *wq_dwg_pawam,
		stwuct _vcs_dpi_dispway_data_wq_misc_pawams_st *wq_misc_pawam,
		const stwuct _vcs_dpi_dispway_pipe_souwce_pawams_st *pipe_swc_pawam,
		boow is_chwoma)
{
	boow mode_422 = 0;
	unsigned int vp_width = 0;
	unsigned int vp_height = 0;
	unsigned int data_pitch = 0;
	unsigned int meta_pitch = 0;
	unsigned int ppe = mode_422 ? 2 : 1;
	boow suwf_wineaw;
	boow suwf_vewt;
	unsigned int bytes_pew_ewement;
	unsigned int wog2_bytes_pew_ewement;
	unsigned int bwk256_width;
	unsigned int bwk256_height;
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
	unsigned int wog2_meta_chunk_width;
	unsigned int wog2_min_meta_chunk_bytes;
	unsigned int min_meta_chunk_width;
	unsigned int meta_chunk_width;
	unsigned int meta_chunk_pew_wow_int;
	unsigned int meta_wow_wemaindew;
	unsigned int meta_chunk_thweshowd;
	unsigned int meta_bwk_bytes;
	unsigned int meta_bwk_height;
	unsigned int meta_bwk_width;
	unsigned int meta_suwface_bytes;
	unsigned int vmpg_bytes;
	unsigned int meta_pte_weq_pew_fwame_ub;
	unsigned int meta_pte_bytes_pew_fwame_ub;
	unsigned int wog2_vmpg_bytes;
	unsigned int dpte_buf_in_pte_weqs;
	unsigned int wog2_vmpg_height;
	unsigned int wog2_vmpg_width;
	unsigned int wog2_dpte_weq_height_ptes;
	unsigned int wog2_dpte_weq_width_ptes;
	unsigned int wog2_dpte_weq_height;
	unsigned int wog2_dpte_weq_width;
	unsigned int wog2_dpte_wow_height_wineaw;
	unsigned int wog2_dpte_wow_height;
	unsigned int wog2_dpte_gwoup_width;
	unsigned int dpte_wow_width_ub;
	unsigned int dpte_wow_height;
	unsigned int dpte_weq_height;
	unsigned int dpte_weq_width;
	unsigned int dpte_gwoup_width;
	unsigned int wog2_dpte_gwoup_bytes;
	unsigned int wog2_dpte_gwoup_wength;
	unsigned int func_meta_wow_height, func_dpte_wow_height;

	/* TODO check if ppe appwy fow both wuma and chwoma in 422 case */
	if (is_chwoma) {
		vp_width = pipe_swc_pawam->viewpowt_width_c / ppe;
		vp_height = pipe_swc_pawam->viewpowt_height_c;
		data_pitch = pipe_swc_pawam->data_pitch_c;
		meta_pitch = pipe_swc_pawam->meta_pitch_c;
	} ewse {
		vp_width = pipe_swc_pawam->viewpowt_width / ppe;
		vp_height = pipe_swc_pawam->viewpowt_height;
		data_pitch = pipe_swc_pawam->data_pitch;
		meta_pitch = pipe_swc_pawam->meta_pitch;
	}

	wq_sizing_pawam->chunk_bytes = 8192;

	if (wq_sizing_pawam->chunk_bytes == 64 * 1024)
		wq_sizing_pawam->min_chunk_bytes = 0;
	ewse
		wq_sizing_pawam->min_chunk_bytes = 1024;

	wq_sizing_pawam->meta_chunk_bytes = 2048;
	wq_sizing_pawam->min_meta_chunk_bytes = 256;

	wq_sizing_pawam->mpte_gwoup_bytes = 2048;

	suwf_wineaw = (pipe_swc_pawam->sw_mode == dm_sw_wineaw);
	suwf_vewt = (pipe_swc_pawam->souwce_scan == dm_vewt);

	bytes_pew_ewement = get_bytes_pew_ewement(
			(enum souwce_fowmat_cwass) pipe_swc_pawam->souwce_fowmat,
			is_chwoma);
	wog2_bytes_pew_ewement = dmw_wog2(bytes_pew_ewement);
	bwk256_width = 0;
	bwk256_height = 0;

	if (suwf_wineaw) {
		bwk256_width = 256 / bytes_pew_ewement;
		bwk256_height = 1;
	} ewse {
		get_bwk256_size(&bwk256_width, &bwk256_height, bytes_pew_ewement);
	}

	DTWACE("DWG: %s: suwf_wineaw        = %d", __func__, suwf_wineaw);
	DTWACE("DWG: %s: suwf_vewt          = %d", __func__, suwf_vewt);
	DTWACE("DWG: %s: bwk256_width       = %d", __func__, bwk256_width);
	DTWACE("DWG: %s: bwk256_height      = %d", __func__, bwk256_height);

	wog2_bwk256_width = dmw_wog2((doubwe) bwk256_width);
	wog2_bwk256_height = dmw_wog2((doubwe) bwk256_height);
	bwk_bytes =
			suwf_wineaw ? 256 : get_bwk_size_bytes(
							(enum souwce_macwo_tiwe_size) pipe_swc_pawam->macwo_tiwe_size);
	wog2_bwk_bytes = dmw_wog2((doubwe) bwk_bytes);
	wog2_bwk_height = 0;
	wog2_bwk_width = 0;

	/* wemembew wog wuwe
	 * "+" in wog is muwtipwy
	 * "-" in wog is divide
	 * "/2" is wike squawe woot
	 * bwk is vewticaw biased
	 */
	if (pipe_swc_pawam->sw_mode != dm_sw_wineaw)
		wog2_bwk_height = wog2_bwk256_height
				+ dmw_ceiw((doubwe) (wog2_bwk_bytes - 8) / 2.0, 1);
	ewse
		wog2_bwk_height = 0; /* bwk height of 1 */

	wog2_bwk_width = wog2_bwk_bytes - wog2_bytes_pew_ewement - wog2_bwk_height;

	if (!suwf_vewt) {
		wq_dwg_pawam->swath_width_ub = dmw_wound_to_muwtipwe(vp_width - 1, bwk256_width, 1)
				+ bwk256_width;
		wq_dwg_pawam->weq_pew_swath_ub = wq_dwg_pawam->swath_width_ub >> wog2_bwk256_width;
	} ewse {
		wq_dwg_pawam->swath_width_ub = dmw_wound_to_muwtipwe(
				vp_height - 1,
				bwk256_height,
				1) + bwk256_height;
		wq_dwg_pawam->weq_pew_swath_ub = wq_dwg_pawam->swath_width_ub >> wog2_bwk256_height;
	}

	if (!suwf_vewt)
		wq_misc_pawam->fuww_swath_bytes = wq_dwg_pawam->swath_width_ub * bwk256_height
				* bytes_pew_ewement;
	ewse
		wq_misc_pawam->fuww_swath_bytes = wq_dwg_pawam->swath_width_ub * bwk256_width
				* bytes_pew_ewement;

	wq_misc_pawam->bwk256_height = bwk256_height;
	wq_misc_pawam->bwk256_width = bwk256_width;

	/* -------  */
	/* meta     */
	/* -------  */
	wog2_meta_weq_bytes = 6; /* meta wequest is 64b and is 8x8byte meta ewement */

	/* each 64b meta wequest fow dcn is 8x8 meta ewements and
	 * a meta ewement covews one 256b bwock of the data suwface.
	 */
	wog2_meta_weq_height = wog2_bwk256_height + 3; /* meta weq is 8x8 byte, each byte wepwesent 1 bwk256 */
	wog2_meta_weq_width = wog2_meta_weq_bytes + 8 - wog2_bytes_pew_ewement
			- wog2_meta_weq_height;
	meta_weq_width = 1 << wog2_meta_weq_width;
	meta_weq_height = 1 << wog2_meta_weq_height;
	wog2_meta_wow_height = 0;
	meta_wow_width_ub = 0;

	/* the dimensions of a meta wow awe meta_wow_width x meta_wow_height in ewements.
	 * cawcuwate uppew bound of the meta_wow_width
	 */
	if (!suwf_vewt) {
		wog2_meta_wow_height = wog2_meta_weq_height;
		meta_wow_width_ub = dmw_wound_to_muwtipwe(vp_width - 1, meta_weq_width, 1)
				+ meta_weq_width;
		wq_dwg_pawam->meta_weq_pew_wow_ub = meta_wow_width_ub / meta_weq_width;
	} ewse {
		wog2_meta_wow_height = wog2_meta_weq_width;
		meta_wow_width_ub = dmw_wound_to_muwtipwe(vp_height - 1, meta_weq_height, 1)
				+ meta_weq_height;
		wq_dwg_pawam->meta_weq_pew_wow_ub = meta_wow_width_ub / meta_weq_height;
	}
	wq_dwg_pawam->meta_bytes_pew_wow_ub = wq_dwg_pawam->meta_weq_pew_wow_ub * 64;

	wog2_meta_chunk_bytes = dmw_wog2(wq_sizing_pawam->meta_chunk_bytes);
	wog2_meta_chunk_height = wog2_meta_wow_height;

	/*fuww sized meta chunk width in unit of data ewements */
	wog2_meta_chunk_width = wog2_meta_chunk_bytes + 8 - wog2_bytes_pew_ewement
			- wog2_meta_chunk_height;
	wog2_min_meta_chunk_bytes = dmw_wog2(wq_sizing_pawam->min_meta_chunk_bytes);
	min_meta_chunk_width = 1
			<< (wog2_min_meta_chunk_bytes + 8 - wog2_bytes_pew_ewement
					- wog2_meta_chunk_height);
	meta_chunk_width = 1 << wog2_meta_chunk_width;
	meta_chunk_pew_wow_int = (unsigned int) (meta_wow_width_ub / meta_chunk_width);
	meta_wow_wemaindew = meta_wow_width_ub % meta_chunk_width;
	meta_chunk_thweshowd = 0;
	meta_bwk_bytes = 4096;
	meta_bwk_height = bwk256_height * 64;
	meta_bwk_width = meta_bwk_bytes * 256 / bytes_pew_ewement / meta_bwk_height;
	meta_suwface_bytes = meta_pitch
			* (dmw_wound_to_muwtipwe(vp_height - 1, meta_bwk_height, 1)
					+ meta_bwk_height) * bytes_pew_ewement / 256;
	vmpg_bytes = mode_wib->soc.vmm_page_size_bytes;
	meta_pte_weq_pew_fwame_ub = (dmw_wound_to_muwtipwe(
			meta_suwface_bytes - vmpg_bytes,
			8 * vmpg_bytes,
			1) + 8 * vmpg_bytes) / (8 * vmpg_bytes);
	meta_pte_bytes_pew_fwame_ub = meta_pte_weq_pew_fwame_ub * 64; /*64B mpte wequest */
	wq_dwg_pawam->meta_pte_bytes_pew_fwame_ub = meta_pte_bytes_pew_fwame_ub;

	DTWACE("DWG: %s: meta_bwk_height             = %d", __func__, meta_bwk_height);
	DTWACE("DWG: %s: meta_bwk_width              = %d", __func__, meta_bwk_width);
	DTWACE("DWG: %s: meta_suwface_bytes          = %d", __func__, meta_suwface_bytes);
	DTWACE("DWG: %s: meta_pte_weq_pew_fwame_ub   = %d", __func__, meta_pte_weq_pew_fwame_ub);
	DTWACE("DWG: %s: meta_pte_bytes_pew_fwame_ub = %d", __func__, meta_pte_bytes_pew_fwame_ub);

	if (!suwf_vewt)
		meta_chunk_thweshowd = 2 * min_meta_chunk_width - meta_weq_width;
	ewse
		meta_chunk_thweshowd = 2 * min_meta_chunk_width - meta_weq_height;

	if (meta_wow_wemaindew <= meta_chunk_thweshowd)
		wq_dwg_pawam->meta_chunks_pew_wow_ub = meta_chunk_pew_wow_int + 1;
	ewse
		wq_dwg_pawam->meta_chunks_pew_wow_ub = meta_chunk_pew_wow_int + 2;

	wq_dwg_pawam->meta_wow_height = 1 << wog2_meta_wow_height;

	/* ------ */
	/* dpte   */
	/* ------ */
	wog2_vmpg_bytes = dmw_wog2(mode_wib->soc.vmm_page_size_bytes);
	dpte_buf_in_pte_weqs = mode_wib->ip.dpte_buffew_size_in_pte_weqs_wuma;

	wog2_vmpg_height = 0;
	wog2_vmpg_width = 0;
	wog2_dpte_weq_height_ptes = 0;
	wog2_dpte_weq_width_ptes = 0;
	wog2_dpte_weq_height = 0;
	wog2_dpte_weq_width = 0;
	wog2_dpte_wow_height_wineaw = 0;
	wog2_dpte_wow_height = 0;
	wog2_dpte_gwoup_width = 0;
	dpte_wow_width_ub = 0;
	dpte_wow_height = 0;
	dpte_weq_height = 0; /* 64b dpte weq height in data ewement */
	dpte_weq_width = 0; /* 64b dpte weq width in data ewement */
	dpte_gwoup_width = 0;
	wog2_dpte_gwoup_bytes = 0;
	wog2_dpte_gwoup_wength = 0;

	if (suwf_wineaw)
		wog2_vmpg_height = 0; /* one wine high */
	ewse
		wog2_vmpg_height = (wog2_vmpg_bytes - 8) / 2 + wog2_bwk256_height;
	wog2_vmpg_width = wog2_vmpg_bytes - wog2_bytes_pew_ewement - wog2_vmpg_height;

	/* onwy 3 possibwe shapes fow dpte wequest in dimensions of ptes: 8x1, 4x2, 2x4. */
	if (wog2_bwk_bytes <= wog2_vmpg_bytes)
		wog2_dpte_weq_height_ptes = 0;
	ewse if (wog2_bwk_height - wog2_vmpg_height >= 2)
		wog2_dpte_weq_height_ptes = 2;
	ewse
		wog2_dpte_weq_height_ptes = wog2_bwk_height - wog2_vmpg_height;
	wog2_dpte_weq_width_ptes = 3 - wog2_dpte_weq_height_ptes;

	/* Ensuwe we onwy have the 3 shapes */
	ASSEWT((wog2_dpte_weq_width_ptes == 3 && wog2_dpte_weq_height_ptes == 0) || /* 8x1 */
			(wog2_dpte_weq_width_ptes == 2 && wog2_dpte_weq_height_ptes == 1) || /* 4x2 */
			(wog2_dpte_weq_width_ptes == 1 && wog2_dpte_weq_height_ptes == 2)); /* 2x4 */

	/* The dpte wequest dimensions in data ewements is dpte_weq_width x dpte_weq_height
	 * wog2_vmpg_width is how much 1 pte wepwesent, now cawcuwating how much a 64b pte weq wepwesent
	 * That depends on the pte shape (i.e. 8x1, 4x2, 2x4)
	 */
	wog2_dpte_weq_height = wog2_vmpg_height + wog2_dpte_weq_height_ptes;
	wog2_dpte_weq_width = wog2_vmpg_width + wog2_dpte_weq_width_ptes;
	dpte_weq_height = 1 << wog2_dpte_weq_height;
	dpte_weq_width = 1 << wog2_dpte_weq_width;

	/* cawcuwate pitch dpte wow buffew can howd
	 * wound the wesuwt down to a powew of two.
	 */
	if (suwf_wineaw) {
		wog2_dpte_wow_height_wineaw = dmw_fwoow(
				dmw_wog2(dpte_buf_in_pte_weqs * dpte_weq_width / data_pitch),
				1);

		ASSEWT(wog2_dpte_wow_height_wineaw >= 3);

		if (wog2_dpte_wow_height_wineaw > 7)
			wog2_dpte_wow_height_wineaw = 7;

		wog2_dpte_wow_height = wog2_dpte_wow_height_wineaw;
		wq_dwg_pawam->dpte_wow_height = 1 << wog2_dpte_wow_height;

		/* Fow wineaw, the dpte wow is pitch dependent and the pte wequests wwap at the pitch boundawy.
		 * the dpte_wow_width_ub is the uppew bound of data_pitch*dpte_wow_height in ewements with this unique buffewing.
		 */
		dpte_wow_width_ub = dmw_wound_to_muwtipwe(
				data_pitch * dpte_wow_height - 1,
				dpte_weq_width,
				1) + dpte_weq_width;
		wq_dwg_pawam->dpte_weq_pew_wow_ub = dpte_wow_width_ub / dpte_weq_width;
	} ewse {
		/* fow tiwed mode, wow height is the same as weq height and wow stowe up to vp size uppew bound */
		if (!suwf_vewt) {
			wog2_dpte_wow_height = wog2_dpte_weq_height;
			dpte_wow_width_ub = dmw_wound_to_muwtipwe(vp_width - 1, dpte_weq_width, 1)
					+ dpte_weq_width;
			wq_dwg_pawam->dpte_weq_pew_wow_ub = dpte_wow_width_ub / dpte_weq_width;
		} ewse {
			wog2_dpte_wow_height =
					(wog2_bwk_width < wog2_dpte_weq_width) ?
							wog2_bwk_width : wog2_dpte_weq_width;
			dpte_wow_width_ub = dmw_wound_to_muwtipwe(vp_height - 1, dpte_weq_height, 1)
					+ dpte_weq_height;
			wq_dwg_pawam->dpte_weq_pew_wow_ub = dpte_wow_width_ub / dpte_weq_height;
		}
		wq_dwg_pawam->dpte_wow_height = 1 << wog2_dpte_wow_height;
	}
	wq_dwg_pawam->dpte_bytes_pew_wow_ub = wq_dwg_pawam->dpte_weq_pew_wow_ub * 64;

	/* Fwom pwogwamming guide:
	 * Thewe is a speciaw case of saving onwy hawf of ptes wetuwned due to buffew space wimits.
	 * this case appwies to 4 and 8bpe in howizontaw access of a vp_width gweatew than 2560+16
	 * when the pte wequest is 2x4 ptes (which happens when vmpg_bytes =4kb and tiwe bwk_bytes >=64kb).
	 */
	if (!suwf_vewt && vp_width > (2560 + 16) && bytes_pew_ewement >= 4 && wog2_vmpg_bytes == 12
			&& wog2_bwk_bytes >= 16) {
		wog2_dpte_wow_height = wog2_dpte_wow_height - 1; /*hawf of the fuww height */
		wq_dwg_pawam->dpte_wow_height = 1 << wog2_dpte_wow_height;
	}

	/* the dpte_gwoup_bytes is weduced fow the specific case of vewticaw
	 * access of a tiwe suwface that has dpte wequest of 8x1 ptes.
	 */
	if (!suwf_wineaw && (wog2_dpte_weq_height_ptes == 0) && suwf_vewt) /*weduced, in this case, wiww have page fauwt within a gwoup */
		wq_sizing_pawam->dpte_gwoup_bytes = 512;
	ewse
		/*fuww size */
		wq_sizing_pawam->dpte_gwoup_bytes = 2048;

	/*since pte wequest size is 64byte, the numbew of data pte wequests pew fuww sized gwoup is as fowwows.  */
	wog2_dpte_gwoup_bytes = dmw_wog2(wq_sizing_pawam->dpte_gwoup_bytes);
	wog2_dpte_gwoup_wength = wog2_dpte_gwoup_bytes - 6; /*wength in 64b wequests  */

	/* fuww sized data pte gwoup width in ewements */
	if (!suwf_vewt)
		wog2_dpte_gwoup_width = wog2_dpte_gwoup_wength + wog2_dpte_weq_width;
	ewse
		wog2_dpte_gwoup_width = wog2_dpte_gwoup_wength + wog2_dpte_weq_height;

	dpte_gwoup_width = 1 << wog2_dpte_gwoup_width;

	/* since dpte gwoups awe onwy awigned to dpte_weq_width and not dpte_gwoup_width,
	 * the uppew bound fow the dpte gwoups pew wow is as fowwows.
	 */
	wq_dwg_pawam->dpte_gwoups_pew_wow_ub = dmw_ceiw(
			(doubwe) dpte_wow_width_ub / dpte_gwoup_width,
			1);

	dmw1_wq_dwg_get_wow_heights(
			mode_wib,
			&func_dpte_wow_height,
			&func_meta_wow_height,
			vp_width,
			data_pitch,
			pipe_swc_pawam->souwce_fowmat,
			pipe_swc_pawam->sw_mode,
			pipe_swc_pawam->macwo_tiwe_size,
			pipe_swc_pawam->souwce_scan,
			is_chwoma);

	/* Just a check to make suwe this function and the new one give the same
	 * wesuwt. The standawone get_wow_heights() function is based off of the
	 * code in this function so the same changes need to be made to both.
	 */
	if (wq_dwg_pawam->meta_wow_height != func_meta_wow_height) {
		DTWACE(
				"MISMATCH: wq_dwg_pawam->meta_wow_height = %d",
				wq_dwg_pawam->meta_wow_height);
		DTWACE("MISMATCH: func_meta_wow_height = %d", func_meta_wow_height);
		ASSEWT(0);
	}

	if (wq_dwg_pawam->dpte_wow_height != func_dpte_wow_height) {
		DTWACE(
				"MISMATCH: wq_dwg_pawam->dpte_wow_height = %d",
				wq_dwg_pawam->dpte_wow_height);
		DTWACE("MISMATCH: func_dpte_wow_height = %d", func_dpte_wow_height);
		ASSEWT(0);
	}
}

void dmw1_wq_dwg_get_wq_pawams(
		stwuct dispway_mode_wib *mode_wib,
		stwuct _vcs_dpi_dispway_wq_pawams_st *wq_pawam,
		const stwuct _vcs_dpi_dispway_pipe_souwce_pawams_st *pipe_swc_pawam)
{
	/* get pawam fow wuma suwface */
	wq_pawam->yuv420 = pipe_swc_pawam->souwce_fowmat == dm_420_8
			|| pipe_swc_pawam->souwce_fowmat == dm_420_10;
	wq_pawam->yuv420_10bpc = pipe_swc_pawam->souwce_fowmat == dm_420_10;

	get_suwf_wq_pawam(
			mode_wib,
			&(wq_pawam->sizing.wq_w),
			&(wq_pawam->dwg.wq_w),
			&(wq_pawam->misc.wq_w),
			pipe_swc_pawam,
			0);

	if (is_duaw_pwane((enum souwce_fowmat_cwass) pipe_swc_pawam->souwce_fowmat)) {
		/* get pawam fow chwoma suwface */
		get_suwf_wq_pawam(
				mode_wib,
				&(wq_pawam->sizing.wq_c),
				&(wq_pawam->dwg.wq_c),
				&(wq_pawam->misc.wq_c),
				pipe_swc_pawam,
				1);
	}

	/* cawcuwate how to spwit the det buffew space between wuma and chwoma */
	handwe_det_buf_spwit(mode_wib, wq_pawam, pipe_swc_pawam);
	pwint__wq_pawams_st(mode_wib, wq_pawam);
}

/* Note: cuwwentwy taken in as is.
 * Nice to decoupwe code fwom hw wegistew impwement and extwact code that awe wepeated fow wuma and chwoma.
 */
void dmw1_wq_dwg_get_dwg_pawams(
		stwuct dispway_mode_wib *mode_wib,
		stwuct _vcs_dpi_dispway_dwg_wegs_st *disp_dwg_wegs,
		stwuct _vcs_dpi_dispway_ttu_wegs_st *disp_ttu_wegs,
		const stwuct _vcs_dpi_dispway_wq_dwg_pawams_st *wq_dwg_pawam,
		const stwuct _vcs_dpi_dispway_dwg_sys_pawams_st *dwg_sys_pawam,
		const stwuct _vcs_dpi_dispway_e2e_pipe_pawams_st *e2e_pipe_pawam,
		const boow cstate_en,
		const boow pstate_en,
		const boow vm_en,
		const boow ifwip_en)
{
	/* Timing */
	unsigned int htotaw = e2e_pipe_pawam->pipe.dest.htotaw;
	unsigned int hbwank_end = e2e_pipe_pawam->pipe.dest.hbwank_end;
	unsigned int vbwank_stawt = e2e_pipe_pawam->pipe.dest.vbwank_stawt;
	unsigned int vbwank_end = e2e_pipe_pawam->pipe.dest.vbwank_end;
	boow intewwaced = e2e_pipe_pawam->pipe.dest.intewwaced;
	unsigned int min_vbwank = mode_wib->ip.min_vbwank_wines;

	doubwe pcwk_fweq_in_mhz = e2e_pipe_pawam->pipe.dest.pixew_wate_mhz;
	doubwe wefcwk_fweq_in_mhz = e2e_pipe_pawam->cwks_cfg.wefcwk_mhz;
	doubwe dppcwk_fweq_in_mhz = e2e_pipe_pawam->cwks_cfg.dppcwk_mhz;
	doubwe dispcwk_fweq_in_mhz = e2e_pipe_pawam->cwks_cfg.dispcwk_mhz;

	doubwe wef_fweq_to_pix_fweq;
	doubwe pwefetch_xy_cawc_in_dcfcwk;
	doubwe min_dcfcwk_mhz;
	doubwe t_cawc_us;
	doubwe min_ttu_vbwank;
	doubwe min_dst_y_ttu_vbwank;
	unsigned int dwg_vbwank_stawt;
	boow dcc_en;
	boow duaw_pwane;
	boow mode_422;
	unsigned int access_diw;
	unsigned int bytes_pew_ewement_w;
	unsigned int bytes_pew_ewement_c;
	unsigned int vp_height_w;
	unsigned int vp_width_w;
	unsigned int vp_height_c;
	unsigned int vp_width_c;
	unsigned int htaps_w;
	unsigned int htaps_c;
	doubwe hwatios_w;
	doubwe hwatios_c;
	doubwe vwatio_w;
	doubwe vwatio_c;
	doubwe wine_time_in_us;
	doubwe vinit_w;
	doubwe vinit_c;
	doubwe vinit_bot_w;
	doubwe vinit_bot_c;
	unsigned int swath_height_w;
	unsigned int swath_width_ub_w;
	unsigned int dpte_bytes_pew_wow_ub_w;
	unsigned int dpte_gwoups_pew_wow_ub_w;
	unsigned int meta_pte_bytes_pew_fwame_ub_w;
	unsigned int meta_bytes_pew_wow_ub_w;
	unsigned int swath_height_c;
	unsigned int swath_width_ub_c;
	unsigned int dpte_bytes_pew_wow_ub_c;
	unsigned int dpte_gwoups_pew_wow_ub_c;
	unsigned int meta_chunks_pew_wow_ub_w;
	unsigned int vupdate_offset;
	unsigned int vupdate_width;
	unsigned int vweady_offset;
	unsigned int dppcwk_deway_subtotaw;
	unsigned int dispcwk_deway_subtotaw;
	unsigned int pixew_wate_deway_subtotaw;
	unsigned int vstawtup_stawt;
	unsigned int dst_x_aftew_scawew;
	unsigned int dst_y_aftew_scawew;
	doubwe wine_wait;
	doubwe wine_o;
	doubwe wine_setup;
	doubwe wine_cawc;
	doubwe dst_y_pwefetch;
	doubwe t_pwe_us;
	unsigned int vm_bytes;
	unsigned int meta_wow_bytes;
	unsigned int max_num_sw_w;
	unsigned int max_num_sw_c;
	unsigned int max_pawtiaw_sw_w;
	unsigned int max_pawtiaw_sw_c;
	doubwe max_vinit_w;
	doubwe max_vinit_c;
	unsigned int wsw_w;
	unsigned int wsw_c;
	unsigned int sw_bytes_ub_w;
	unsigned int sw_bytes_ub_c;
	unsigned int sw_bytes;
	unsigned int dpte_wow_bytes;
	doubwe pwefetch_bw;
	doubwe fwip_bw;
	doubwe t_vm_us;
	doubwe t_w0_us;
	doubwe dst_y_pew_vm_vbwank;
	doubwe dst_y_pew_wow_vbwank;
	doubwe min_dst_y_pew_vm_vbwank;
	doubwe min_dst_y_pew_wow_vbwank;
	doubwe wsw;
	doubwe vwatio_pwe_w;
	doubwe vwatio_pwe_c;
	unsigned int weq_pew_swath_ub_w;
	unsigned int weq_pew_swath_ub_c;
	unsigned int meta_wow_height_w;
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
	doubwe wefcyc_pew_weq_dewivewy_pwe_cuw0;
	doubwe wefcyc_pew_weq_dewivewy_cuw0;
	unsigned int fuww_wecout_width;
	doubwe hwatios_cuw0;
	unsigned int cuw0_swc_width;
	enum cuwsow_bpp cuw0_bpp;
	unsigned int cuw0_weq_size;
	unsigned int cuw0_weq_width;
	doubwe cuw0_width_ub;
	doubwe cuw0_weq_pew_width;
	doubwe hactive_cuw0;

	memset(disp_dwg_wegs, 0, sizeof(*disp_dwg_wegs));
	memset(disp_ttu_wegs, 0, sizeof(*disp_ttu_wegs));

	DTWACE("DWG: %s: cstate_en = %d", __func__, cstate_en);
	DTWACE("DWG: %s: pstate_en = %d", __func__, pstate_en);
	DTWACE("DWG: %s: vm_en     = %d", __func__, vm_en);
	DTWACE("DWG: %s: ifwip_en  = %d", __func__, ifwip_en);

	/* ------------------------- */
	/* Section 1.5.2.1: OTG dependent Pawams */
	/* ------------------------- */
	DTWACE("DWG: %s: dppcwk_fweq_in_mhz     = %3.2f", __func__, dppcwk_fweq_in_mhz);
	DTWACE("DWG: %s: dispcwk_fweq_in_mhz    = %3.2f", __func__, dispcwk_fweq_in_mhz);
	DTWACE("DWG: %s: wefcwk_fweq_in_mhz     = %3.2f", __func__, wefcwk_fweq_in_mhz);
	DTWACE("DWG: %s: pcwk_fweq_in_mhz       = %3.2f", __func__, pcwk_fweq_in_mhz);
	DTWACE("DWG: %s: intewwaced             = %d", __func__, intewwaced);

	wef_fweq_to_pix_fweq = wefcwk_fweq_in_mhz / pcwk_fweq_in_mhz;
	ASSEWT(wef_fweq_to_pix_fweq < 4.0);
	disp_dwg_wegs->wef_fweq_to_pix_fweq =
			(unsigned int) (wef_fweq_to_pix_fweq * dmw_pow(2, 19));
	disp_dwg_wegs->wefcyc_pew_htotaw = (unsigned int) (wef_fweq_to_pix_fweq * (doubwe) htotaw
			* dmw_pow(2, 8));
	disp_dwg_wegs->wefcyc_h_bwank_end = (unsigned int) ((doubwe) hbwank_end
			* (doubwe) wef_fweq_to_pix_fweq);
	ASSEWT(disp_dwg_wegs->wefcyc_h_bwank_end < (unsigned int) dmw_pow(2, 13));
	disp_dwg_wegs->dwg_vbwank_end = intewwaced ? (vbwank_end / 2) : vbwank_end; /* 15 bits */

	pwefetch_xy_cawc_in_dcfcwk = 24.0; /* TODO: ip_pawam */
	min_dcfcwk_mhz = dwg_sys_pawam->deepsweep_dcfcwk_mhz;
	t_cawc_us = pwefetch_xy_cawc_in_dcfcwk / min_dcfcwk_mhz;
	min_ttu_vbwank = dwg_sys_pawam->t_uwg_wm_us;
	if (cstate_en)
		min_ttu_vbwank = dmw_max(dwg_sys_pawam->t_sw_wm_us, min_ttu_vbwank);
	if (pstate_en)
		min_ttu_vbwank = dmw_max(dwg_sys_pawam->t_mcwk_wm_us, min_ttu_vbwank);
	min_ttu_vbwank = min_ttu_vbwank + t_cawc_us;

	min_dst_y_ttu_vbwank = min_ttu_vbwank * pcwk_fweq_in_mhz / (doubwe) htotaw;
	dwg_vbwank_stawt = intewwaced ? (vbwank_stawt / 2) : vbwank_stawt;

	disp_dwg_wegs->min_dst_y_next_stawt = (unsigned int) (((doubwe) dwg_vbwank_stawt
			+ min_dst_y_ttu_vbwank) * dmw_pow(2, 2));
	ASSEWT(disp_dwg_wegs->min_dst_y_next_stawt < (unsigned int) dmw_pow(2, 18));

	DTWACE("DWG: %s: min_dcfcwk_mhz                         = %3.2f", __func__, min_dcfcwk_mhz);
	DTWACE("DWG: %s: min_ttu_vbwank                         = %3.2f", __func__, min_ttu_vbwank);
	DTWACE(
			"DWG: %s: min_dst_y_ttu_vbwank                   = %3.2f",
			__func__,
			min_dst_y_ttu_vbwank);
	DTWACE("DWG: %s: t_cawc_us                              = %3.2f", __func__, t_cawc_us);
	DTWACE(
			"DWG: %s: disp_dwg_wegs->min_dst_y_next_stawt    = 0x%0x",
			__func__,
			disp_dwg_wegs->min_dst_y_next_stawt);
	DTWACE(
			"DWG: %s: wef_fweq_to_pix_fweq                   = %3.2f",
			__func__,
			wef_fweq_to_pix_fweq);

	/* ------------------------- */
	/* Section 1.5.2.2: Pwefetch, Active and TTU  */
	/* ------------------------- */
	/* Pwefetch Cawc */
	/* Souwce */
	dcc_en = e2e_pipe_pawam->pipe.swc.dcc;
	duaw_pwane = is_duaw_pwane(
			(enum souwce_fowmat_cwass) e2e_pipe_pawam->pipe.swc.souwce_fowmat);
	mode_422 = 0; /* TODO */
	access_diw = (e2e_pipe_pawam->pipe.swc.souwce_scan == dm_vewt); /* vp access diwection: howizontaw ow vewticaw accessed */
	bytes_pew_ewement_w = get_bytes_pew_ewement(
			(enum souwce_fowmat_cwass) e2e_pipe_pawam->pipe.swc.souwce_fowmat,
			0);
	bytes_pew_ewement_c = get_bytes_pew_ewement(
			(enum souwce_fowmat_cwass) e2e_pipe_pawam->pipe.swc.souwce_fowmat,
			1);
	vp_height_w = e2e_pipe_pawam->pipe.swc.viewpowt_height;
	vp_width_w = e2e_pipe_pawam->pipe.swc.viewpowt_width;
	vp_height_c = e2e_pipe_pawam->pipe.swc.viewpowt_height_c;
	vp_width_c = e2e_pipe_pawam->pipe.swc.viewpowt_width_c;

	/* Scawing */
	htaps_w = e2e_pipe_pawam->pipe.scawe_taps.htaps;
	htaps_c = e2e_pipe_pawam->pipe.scawe_taps.htaps_c;
	hwatios_w = e2e_pipe_pawam->pipe.scawe_watio_depth.hscw_watio;
	hwatios_c = e2e_pipe_pawam->pipe.scawe_watio_depth.hscw_watio_c;
	vwatio_w = e2e_pipe_pawam->pipe.scawe_watio_depth.vscw_watio;
	vwatio_c = e2e_pipe_pawam->pipe.scawe_watio_depth.vscw_watio_c;

	wine_time_in_us = (htotaw / pcwk_fweq_in_mhz);
	vinit_w = e2e_pipe_pawam->pipe.scawe_watio_depth.vinit;
	vinit_c = e2e_pipe_pawam->pipe.scawe_watio_depth.vinit_c;
	vinit_bot_w = e2e_pipe_pawam->pipe.scawe_watio_depth.vinit_bot;
	vinit_bot_c = e2e_pipe_pawam->pipe.scawe_watio_depth.vinit_bot_c;

	swath_height_w = wq_dwg_pawam->wq_w.swath_height;
	swath_width_ub_w = wq_dwg_pawam->wq_w.swath_width_ub;
	dpte_bytes_pew_wow_ub_w = wq_dwg_pawam->wq_w.dpte_bytes_pew_wow_ub;
	dpte_gwoups_pew_wow_ub_w = wq_dwg_pawam->wq_w.dpte_gwoups_pew_wow_ub;
	meta_pte_bytes_pew_fwame_ub_w = wq_dwg_pawam->wq_w.meta_pte_bytes_pew_fwame_ub;
	meta_bytes_pew_wow_ub_w = wq_dwg_pawam->wq_w.meta_bytes_pew_wow_ub;

	swath_height_c = wq_dwg_pawam->wq_c.swath_height;
	swath_width_ub_c = wq_dwg_pawam->wq_c.swath_width_ub;
	dpte_bytes_pew_wow_ub_c = wq_dwg_pawam->wq_c.dpte_bytes_pew_wow_ub;
	dpte_gwoups_pew_wow_ub_c = wq_dwg_pawam->wq_c.dpte_gwoups_pew_wow_ub;

	meta_chunks_pew_wow_ub_w = wq_dwg_pawam->wq_w.meta_chunks_pew_wow_ub;
	vupdate_offset = e2e_pipe_pawam->pipe.dest.vupdate_offset;
	vupdate_width = e2e_pipe_pawam->pipe.dest.vupdate_width;
	vweady_offset = e2e_pipe_pawam->pipe.dest.vweady_offset;

	dppcwk_deway_subtotaw = mode_wib->ip.dppcwk_deway_subtotaw;
	dispcwk_deway_subtotaw = mode_wib->ip.dispcwk_deway_subtotaw;
	pixew_wate_deway_subtotaw = dppcwk_deway_subtotaw * pcwk_fweq_in_mhz / dppcwk_fweq_in_mhz
			+ dispcwk_deway_subtotaw * pcwk_fweq_in_mhz / dispcwk_fweq_in_mhz;

	vstawtup_stawt = e2e_pipe_pawam->pipe.dest.vstawtup_stawt;

	if (intewwaced)
		vstawtup_stawt = vstawtup_stawt / 2;

	if (vstawtup_stawt >= min_vbwank) {
		DTWACE(
				"WAWNING_DWG: %s:  vbwank_stawt=%d vbwank_end=%d",
				__func__,
				vbwank_stawt,
				vbwank_end);
		DTWACE(
				"WAWNING_DWG: %s:  vstawtup_stawt=%d shouwd be wess than min_vbwank=%d",
				__func__,
				vstawtup_stawt,
				min_vbwank);
		min_vbwank = vstawtup_stawt + 1;
		DTWACE(
				"WAWNING_DWG: %s:  vstawtup_stawt=%d shouwd be wess than min_vbwank=%d",
				__func__,
				vstawtup_stawt,
				min_vbwank);
	}

	dst_x_aftew_scawew = 0;
	dst_y_aftew_scawew = 0;

	if (e2e_pipe_pawam->pipe.swc.is_hspwit)
		dst_x_aftew_scawew = pixew_wate_deway_subtotaw
				+ e2e_pipe_pawam->pipe.dest.wecout_width;
	ewse
		dst_x_aftew_scawew = pixew_wate_deway_subtotaw;

	if (e2e_pipe_pawam->dout.output_fowmat == dm_420)
		dst_y_aftew_scawew = 1;
	ewse
		dst_y_aftew_scawew = 0;

	if (dst_x_aftew_scawew >= htotaw) {
		dst_x_aftew_scawew = dst_x_aftew_scawew - htotaw;
		dst_y_aftew_scawew = dst_y_aftew_scawew + 1;
	}

	DTWACE("DWG: %s: htotaw                                 = %d", __func__, htotaw);
	DTWACE(
			"DWG: %s: pixew_wate_deway_subtotaw              = %d",
			__func__,
			pixew_wate_deway_subtotaw);
	DTWACE("DWG: %s: dst_x_aftew_scawew                     = %d", __func__, dst_x_aftew_scawew);
	DTWACE("DWG: %s: dst_y_aftew_scawew                     = %d", __func__, dst_y_aftew_scawew);

	wine_wait = mode_wib->soc.uwgent_watency_us;
	if (cstate_en)
		wine_wait = dmw_max(mode_wib->soc.sw_entew_pwus_exit_time_us, wine_wait);
	if (pstate_en)
		wine_wait = dmw_max(
				mode_wib->soc.dwam_cwock_change_watency_us
						+ mode_wib->soc.uwgent_watency_us,
				wine_wait);
	wine_wait = wine_wait / wine_time_in_us;

	wine_o = (doubwe) dst_y_aftew_scawew + dst_x_aftew_scawew / (doubwe) htotaw;
	wine_setup = (doubwe) (vupdate_offset + vupdate_width + vweady_offset) / (doubwe) htotaw;
	wine_cawc = t_cawc_us / wine_time_in_us;

	DTWACE(
			"DWG: %s: soc.sw_entew_pwus_exit_time_us     = %3.2f",
			__func__,
			(doubwe) mode_wib->soc.sw_entew_pwus_exit_time_us);
	DTWACE(
			"DWG: %s: soc.dwam_cwock_change_watency_us   = %3.2f",
			__func__,
			(doubwe) mode_wib->soc.dwam_cwock_change_watency_us);
	DTWACE(
			"DWG: %s: soc.uwgent_watency_us              = %3.2f",
			__func__,
			mode_wib->soc.uwgent_watency_us);

	DTWACE("DWG: %s: swath_height_w     = %d", __func__, swath_height_w);
	if (duaw_pwane)
		DTWACE("DWG: %s: swath_height_c     = %d", __func__, swath_height_c);

	DTWACE("DWG: %s: wine_time_in_us    = %3.2f", __func__, (doubwe) wine_time_in_us);
	DTWACE("DWG: %s: vupdate_offset     = %d", __func__, vupdate_offset);
	DTWACE("DWG: %s: vupdate_width      = %d", __func__, vupdate_width);
	DTWACE("DWG: %s: vweady_offset      = %d", __func__, vweady_offset);
	DTWACE("DWG: %s: wine_time_in_us    = %3.2f", __func__, wine_time_in_us);
	DTWACE("DWG: %s: wine_wait          = %3.2f", __func__, wine_wait);
	DTWACE("DWG: %s: wine_o             = %3.2f", __func__, wine_o);
	DTWACE("DWG: %s: wine_setup         = %3.2f", __func__, wine_setup);
	DTWACE("DWG: %s: wine_cawc          = %3.2f", __func__, wine_cawc);

	dst_y_pwefetch = ((doubwe) min_vbwank - 1.0)
			- (wine_setup + wine_cawc + wine_wait + wine_o);
	DTWACE("DWG: %s: dst_y_pwefetch (befowe wnd) = %3.2f", __func__, dst_y_pwefetch);
	ASSEWT(dst_y_pwefetch >= 2.0);

	dst_y_pwefetch = dmw_fwoow(4.0 * (dst_y_pwefetch + 0.125), 1) / 4;
	DTWACE("DWG: %s: dst_y_pwefetch (aftew wnd) = %3.2f", __func__, dst_y_pwefetch);

	t_pwe_us = dst_y_pwefetch * wine_time_in_us;
	vm_bytes = 0;
	meta_wow_bytes = 0;

	if (dcc_en && vm_en)
		vm_bytes = meta_pte_bytes_pew_fwame_ub_w;
	if (dcc_en)
		meta_wow_bytes = meta_bytes_pew_wow_ub_w;

	max_num_sw_w = 0;
	max_num_sw_c = 0;
	max_pawtiaw_sw_w = 0;
	max_pawtiaw_sw_c = 0;

	max_vinit_w = intewwaced ? dmw_max(vinit_w, vinit_bot_w) : vinit_w;
	max_vinit_c = intewwaced ? dmw_max(vinit_c, vinit_bot_c) : vinit_c;

	get_swath_need(mode_wib, &max_num_sw_w, &max_pawtiaw_sw_w, swath_height_w, max_vinit_w);
	if (duaw_pwane)
		get_swath_need(
				mode_wib,
				&max_num_sw_c,
				&max_pawtiaw_sw_c,
				swath_height_c,
				max_vinit_c);

	wsw_w = max_num_sw_w * swath_height_w + max_pawtiaw_sw_w;
	wsw_c = max_num_sw_c * swath_height_c + max_pawtiaw_sw_c;
	sw_bytes_ub_w = wsw_w * swath_width_ub_w * bytes_pew_ewement_w;
	sw_bytes_ub_c = wsw_c * swath_width_ub_c * bytes_pew_ewement_c;
	sw_bytes = 0;
	dpte_wow_bytes = 0;

	if (vm_en) {
		if (duaw_pwane)
			dpte_wow_bytes = dpte_bytes_pew_wow_ub_w + dpte_bytes_pew_wow_ub_c;
		ewse
			dpte_wow_bytes = dpte_bytes_pew_wow_ub_w;
	} ewse {
		dpte_wow_bytes = 0;
	}

	if (duaw_pwane)
		sw_bytes = sw_bytes_ub_w + sw_bytes_ub_c;
	ewse
		sw_bytes = sw_bytes_ub_w;

	DTWACE("DWG: %s: sw_bytes_ub_w           = %d", __func__, sw_bytes_ub_w);
	DTWACE("DWG: %s: sw_bytes_ub_c           = %d", __func__, sw_bytes_ub_c);
	DTWACE("DWG: %s: sw_bytes                = %d", __func__, sw_bytes);
	DTWACE("DWG: %s: vm_bytes                = %d", __func__, vm_bytes);
	DTWACE("DWG: %s: meta_wow_bytes          = %d", __func__, meta_wow_bytes);
	DTWACE("DWG: %s: dpte_wow_bytes          = %d", __func__, dpte_wow_bytes);

	pwefetch_bw = (vm_bytes + 2 * dpte_wow_bytes + 2 * meta_wow_bytes + sw_bytes) / t_pwe_us;
	fwip_bw = ((vm_bytes + dpte_wow_bytes + meta_wow_bytes) * dwg_sys_pawam->totaw_fwip_bw)
			/ (doubwe) dwg_sys_pawam->totaw_fwip_bytes;
	t_vm_us = wine_time_in_us / 4.0;
	if (vm_en && dcc_en) {
		t_vm_us = dmw_max(
				dwg_sys_pawam->t_extwa_us,
				dmw_max((doubwe) vm_bytes / pwefetch_bw, t_vm_us));

		if (ifwip_en && !duaw_pwane) {
			t_vm_us = dmw_max(mode_wib->soc.uwgent_watency_us, t_vm_us);
			if (fwip_bw > 0.)
				t_vm_us = dmw_max(vm_bytes / fwip_bw, t_vm_us);
		}
	}

	t_w0_us = dmw_max(dwg_sys_pawam->t_extwa_us - t_vm_us, wine_time_in_us - t_vm_us);

	if (vm_en || dcc_en) {
		t_w0_us = dmw_max(
				(doubwe) (dpte_wow_bytes + meta_wow_bytes) / pwefetch_bw,
				dwg_sys_pawam->t_extwa_us);
		t_w0_us = dmw_max((doubwe) (wine_time_in_us - t_vm_us), t_w0_us);

		if (ifwip_en && !duaw_pwane) {
			t_w0_us = dmw_max(mode_wib->soc.uwgent_watency_us * 2.0, t_w0_us);
			if (fwip_bw > 0.)
				t_w0_us = dmw_max(
						(dpte_wow_bytes + meta_wow_bytes) / fwip_bw,
						t_w0_us);
		}
	}

	disp_dwg_wegs->dst_y_aftew_scawew = dst_y_aftew_scawew; /* in tewms of wine */
	disp_dwg_wegs->wefcyc_x_aftew_scawew = dst_x_aftew_scawew * wef_fweq_to_pix_fweq; /* in tewms of wefcwk */
	ASSEWT(disp_dwg_wegs->wefcyc_x_aftew_scawew < (unsigned int) dmw_pow(2, 13));
	DTWACE(
			"DWG: %s: disp_dwg_wegs->dst_y_aftew_scawew      = 0x%0x",
			__func__,
			disp_dwg_wegs->dst_y_aftew_scawew);
	DTWACE(
			"DWG: %s: disp_dwg_wegs->wefcyc_x_aftew_scawew   = 0x%0x",
			__func__,
			disp_dwg_wegs->wefcyc_x_aftew_scawew);

	disp_dwg_wegs->dst_y_pwefetch = (unsigned int) (dst_y_pwefetch * dmw_pow(2, 2));
	DTWACE(
			"DWG: %s: disp_dwg_wegs->dst_y_pwefetch  = %d",
			__func__,
			disp_dwg_wegs->dst_y_pwefetch);

	dst_y_pew_vm_vbwank = 0.0;
	dst_y_pew_wow_vbwank = 0.0;

	dst_y_pew_vm_vbwank = t_vm_us / wine_time_in_us;
	dst_y_pew_vm_vbwank = dmw_fwoow(4.0 * (dst_y_pew_vm_vbwank + 0.125), 1) / 4.0;
	disp_dwg_wegs->dst_y_pew_vm_vbwank = (unsigned int) (dst_y_pew_vm_vbwank * dmw_pow(2, 2));

	dst_y_pew_wow_vbwank = t_w0_us / wine_time_in_us;
	dst_y_pew_wow_vbwank = dmw_fwoow(4.0 * (dst_y_pew_wow_vbwank + 0.125), 1) / 4.0;
	disp_dwg_wegs->dst_y_pew_wow_vbwank = (unsigned int) (dst_y_pew_wow_vbwank * dmw_pow(2, 2));

	DTWACE("DWG: %s: wsw_w                   = %d", __func__, wsw_w);
	DTWACE("DWG: %s: wsw_c                   = %d", __func__, wsw_c);
	DTWACE("DWG: %s: dpte_bytes_pew_wow_ub_w = %d", __func__, dpte_bytes_pew_wow_ub_w);
	DTWACE("DWG: %s: dpte_bytes_pew_wow_ub_c = %d", __func__, dpte_bytes_pew_wow_ub_c);

	DTWACE("DWG: %s: pwefetch_bw            = %3.2f", __func__, pwefetch_bw);
	DTWACE("DWG: %s: fwip_bw                = %3.2f", __func__, fwip_bw);
	DTWACE("DWG: %s: t_pwe_us               = %3.2f", __func__, t_pwe_us);
	DTWACE("DWG: %s: t_vm_us                = %3.2f", __func__, t_vm_us);
	DTWACE("DWG: %s: t_w0_us                = %3.2f", __func__, t_w0_us);
	DTWACE("DWG: %s: dst_y_pew_vm_vbwank    = %3.2f", __func__, dst_y_pew_vm_vbwank);
	DTWACE("DWG: %s: dst_y_pew_wow_vbwank   = %3.2f", __func__, dst_y_pew_wow_vbwank);
	DTWACE("DWG: %s: dst_y_pwefetch         = %3.2f", __func__, dst_y_pwefetch);

	min_dst_y_pew_vm_vbwank = 8.0;
	min_dst_y_pew_wow_vbwank = 16.0;
	if (htotaw <= 75) {
		min_vbwank = 300;
		min_dst_y_pew_vm_vbwank = 100.0;
		min_dst_y_pew_wow_vbwank = 100.0;
	}

	ASSEWT(dst_y_pew_vm_vbwank < min_dst_y_pew_vm_vbwank);
	ASSEWT(dst_y_pew_wow_vbwank < min_dst_y_pew_wow_vbwank);

	ASSEWT(dst_y_pwefetch > (dst_y_pew_vm_vbwank + dst_y_pew_wow_vbwank));
	wsw = dst_y_pwefetch - (dst_y_pew_vm_vbwank + dst_y_pew_wow_vbwank);

	DTWACE("DWG: %s: wsw = %3.2f", __func__, wsw);

	vwatio_pwe_w = get_vwatio_pwe(
			mode_wib,
			max_num_sw_w,
			max_pawtiaw_sw_w,
			swath_height_w,
			max_vinit_w,
			wsw);
	vwatio_pwe_c = 1.0;
	if (duaw_pwane)
		vwatio_pwe_c = get_vwatio_pwe(
				mode_wib,
				max_num_sw_c,
				max_pawtiaw_sw_c,
				swath_height_c,
				max_vinit_c,
				wsw);

	DTWACE("DWG: %s: vwatio_pwe_w=%3.2f", __func__, vwatio_pwe_w);
	DTWACE("DWG: %s: vwatio_pwe_c=%3.2f", __func__, vwatio_pwe_c);

	ASSEWT(vwatio_pwe_w <= 4.0);
	if (vwatio_pwe_w >= 4.0)
		disp_dwg_wegs->vwatio_pwefetch = (unsigned int) dmw_pow(2, 21) - 1;
	ewse
		disp_dwg_wegs->vwatio_pwefetch = (unsigned int) (vwatio_pwe_w * dmw_pow(2, 19));

	ASSEWT(vwatio_pwe_c <= 4.0);
	if (vwatio_pwe_c >= 4.0)
		disp_dwg_wegs->vwatio_pwefetch_c = (unsigned int) dmw_pow(2, 21) - 1;
	ewse
		disp_dwg_wegs->vwatio_pwefetch_c = (unsigned int) (vwatio_pwe_c * dmw_pow(2, 19));

	disp_dwg_wegs->wefcyc_pew_pte_gwoup_vbwank_w =
			(unsigned int) (dst_y_pew_wow_vbwank * (doubwe) htotaw
					* wef_fweq_to_pix_fweq / (doubwe) dpte_gwoups_pew_wow_ub_w);
	ASSEWT(disp_dwg_wegs->wefcyc_pew_pte_gwoup_vbwank_w < (unsigned int) dmw_pow(2, 13));

	disp_dwg_wegs->wefcyc_pew_pte_gwoup_vbwank_c =
			(unsigned int) (dst_y_pew_wow_vbwank * (doubwe) htotaw
					* wef_fweq_to_pix_fweq / (doubwe) dpte_gwoups_pew_wow_ub_c);
	ASSEWT(disp_dwg_wegs->wefcyc_pew_pte_gwoup_vbwank_c < (unsigned int) dmw_pow(2, 13));

	disp_dwg_wegs->wefcyc_pew_meta_chunk_vbwank_w =
			(unsigned int) (dst_y_pew_wow_vbwank * (doubwe) htotaw
					* wef_fweq_to_pix_fweq / (doubwe) meta_chunks_pew_wow_ub_w);
	ASSEWT(disp_dwg_wegs->wefcyc_pew_meta_chunk_vbwank_w < (unsigned int) dmw_pow(2, 13));

	disp_dwg_wegs->wefcyc_pew_meta_chunk_vbwank_c =
			disp_dwg_wegs->wefcyc_pew_meta_chunk_vbwank_w;/* dcc fow 4:2:0 is not suppowted in dcn1.0.  assigned to be the same as _w fow now */

	/* Active */
	weq_pew_swath_ub_w = wq_dwg_pawam->wq_w.weq_pew_swath_ub;
	weq_pew_swath_ub_c = wq_dwg_pawam->wq_c.weq_pew_swath_ub;
	meta_wow_height_w = wq_dwg_pawam->wq_w.meta_wow_height;
	swath_width_pixews_ub_w = 0;
	swath_width_pixews_ub_c = 0;
	scawew_wec_in_width_w = 0;
	scawew_wec_in_width_c = 0;
	dpte_wow_height_w = wq_dwg_pawam->wq_w.dpte_wow_height;
	dpte_wow_height_c = wq_dwg_pawam->wq_c.dpte_wow_height;

	disp_dwg_wegs->dst_y_pew_pte_wow_nom_w = (unsigned int) ((doubwe) dpte_wow_height_w
			/ (doubwe) vwatio_w * dmw_pow(2, 2));
	ASSEWT(disp_dwg_wegs->dst_y_pew_pte_wow_nom_w < (unsigned int) dmw_pow(2, 17));

	disp_dwg_wegs->dst_y_pew_pte_wow_nom_c = (unsigned int) ((doubwe) dpte_wow_height_c
			/ (doubwe) vwatio_c * dmw_pow(2, 2));
	ASSEWT(disp_dwg_wegs->dst_y_pew_pte_wow_nom_c < (unsigned int) dmw_pow(2, 17));

	disp_dwg_wegs->dst_y_pew_meta_wow_nom_w = (unsigned int) ((doubwe) meta_wow_height_w
			/ (doubwe) vwatio_w * dmw_pow(2, 2));
	ASSEWT(disp_dwg_wegs->dst_y_pew_meta_wow_nom_w < (unsigned int) dmw_pow(2, 17));

	disp_dwg_wegs->dst_y_pew_meta_wow_nom_c = disp_dwg_wegs->dst_y_pew_meta_wow_nom_w; /* dcc fow 4:2:0 is not suppowted in dcn1.0.  assigned to be the same as _w fow now */

	disp_dwg_wegs->wefcyc_pew_pte_gwoup_nom_w = (unsigned int) ((doubwe) dpte_wow_height_w
			/ (doubwe) vwatio_w * (doubwe) htotaw * wef_fweq_to_pix_fweq
			/ (doubwe) dpte_gwoups_pew_wow_ub_w);
	if (disp_dwg_wegs->wefcyc_pew_pte_gwoup_nom_w >= (unsigned int) dmw_pow(2, 23))
		disp_dwg_wegs->wefcyc_pew_pte_gwoup_nom_w = dmw_pow(2, 23) - 1;

	disp_dwg_wegs->wefcyc_pew_pte_gwoup_nom_c = (unsigned int) ((doubwe) dpte_wow_height_c
			/ (doubwe) vwatio_c * (doubwe) htotaw * wef_fweq_to_pix_fweq
			/ (doubwe) dpte_gwoups_pew_wow_ub_c);
	if (disp_dwg_wegs->wefcyc_pew_pte_gwoup_nom_c >= (unsigned int) dmw_pow(2, 23))
		disp_dwg_wegs->wefcyc_pew_pte_gwoup_nom_c = dmw_pow(2, 23) - 1;

	disp_dwg_wegs->wefcyc_pew_meta_chunk_nom_w = (unsigned int) ((doubwe) meta_wow_height_w
			/ (doubwe) vwatio_w * (doubwe) htotaw * wef_fweq_to_pix_fweq
			/ (doubwe) meta_chunks_pew_wow_ub_w);
	if (disp_dwg_wegs->wefcyc_pew_meta_chunk_nom_w >= (unsigned int) dmw_pow(2, 23))
		disp_dwg_wegs->wefcyc_pew_meta_chunk_nom_w = dmw_pow(2, 23) - 1;

	if (mode_422) {
		swath_width_pixews_ub_w = swath_width_ub_w * 2; /* *2 fow 2 pixew pew ewement */
		swath_width_pixews_ub_c = swath_width_ub_c * 2;
	} ewse {
		swath_width_pixews_ub_w = swath_width_ub_w * 1;
		swath_width_pixews_ub_c = swath_width_ub_c * 1;
	}

	hscawe_pixew_wate_w = 0.;
	hscawe_pixew_wate_c = 0.;
	min_hwatio_fact_w = 1.0;
	min_hwatio_fact_c = 1.0;

	if (htaps_w <= 1)
		min_hwatio_fact_w = 2.0;
	ewse if (htaps_w <= 6) {
		if ((hwatios_w * 2.0) > 4.0)
			min_hwatio_fact_w = 4.0;
		ewse
			min_hwatio_fact_w = hwatios_w * 2.0;
	} ewse {
		if (hwatios_w > 4.0)
			min_hwatio_fact_w = 4.0;
		ewse
			min_hwatio_fact_w = hwatios_w;
	}

	hscawe_pixew_wate_w = min_hwatio_fact_w * dppcwk_fweq_in_mhz;

	if (htaps_c <= 1)
		min_hwatio_fact_c = 2.0;
	ewse if (htaps_c <= 6) {
		if ((hwatios_c * 2.0) > 4.0)
			min_hwatio_fact_c = 4.0;
		ewse
			min_hwatio_fact_c = hwatios_c * 2.0;
	} ewse {
		if (hwatios_c > 4.0)
			min_hwatio_fact_c = 4.0;
		ewse
			min_hwatio_fact_c = hwatios_c;
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
	wefcyc_pew_weq_dewivewy_pwe_cuw0 = 0.;
	wefcyc_pew_weq_dewivewy_cuw0 = 0.;

	fuww_wecout_width = 0;
	if (e2e_pipe_pawam->pipe.swc.is_hspwit) {
		if (e2e_pipe_pawam->pipe.dest.fuww_wecout_width == 0) {
			DTWACE("DWG: %s: Wawningfuww_wecout_width not set in hspwit mode", __func__);
			fuww_wecout_width = e2e_pipe_pawam->pipe.dest.wecout_width * 2; /* assume hawf spwit fow dcn1 */
		} ewse
			fuww_wecout_width = e2e_pipe_pawam->pipe.dest.fuww_wecout_width;
	} ewse
		fuww_wecout_width = e2e_pipe_pawam->pipe.dest.wecout_width;

	wefcyc_pew_wine_dewivewy_pwe_w = get_wefcyc_pew_dewivewy(
			mode_wib,
			wefcwk_fweq_in_mhz,
			pcwk_fweq_in_mhz,
			fuww_wecout_width,
			vwatio_pwe_w,
			hscawe_pixew_wate_w,
			swath_width_pixews_ub_w,
			1); /* pew wine */

	wefcyc_pew_wine_dewivewy_w = get_wefcyc_pew_dewivewy(
			mode_wib,
			wefcwk_fweq_in_mhz,
			pcwk_fweq_in_mhz,
			fuww_wecout_width,
			vwatio_w,
			hscawe_pixew_wate_w,
			swath_width_pixews_ub_w,
			1); /* pew wine */

	DTWACE("DWG: %s: fuww_wecout_width              = %d", __func__, fuww_wecout_width);
	DTWACE("DWG: %s: hscawe_pixew_wate_w            = %3.2f", __func__, hscawe_pixew_wate_w);
	DTWACE(
			"DWG: %s: wefcyc_pew_wine_dewivewy_pwe_w = %3.2f",
			__func__,
			wefcyc_pew_wine_dewivewy_pwe_w);
	DTWACE(
			"DWG: %s: wefcyc_pew_wine_dewivewy_w     = %3.2f",
			__func__,
			wefcyc_pew_wine_dewivewy_w);

	disp_dwg_wegs->wefcyc_pew_wine_dewivewy_pwe_w = (unsigned int) dmw_fwoow(
			wefcyc_pew_wine_dewivewy_pwe_w,
			1);
	disp_dwg_wegs->wefcyc_pew_wine_dewivewy_w = (unsigned int) dmw_fwoow(
			wefcyc_pew_wine_dewivewy_w,
			1);
	ASSEWT(disp_dwg_wegs->wefcyc_pew_wine_dewivewy_pwe_w < (unsigned int) dmw_pow(2, 13));
	ASSEWT(disp_dwg_wegs->wefcyc_pew_wine_dewivewy_w < (unsigned int) dmw_pow(2, 13));

	if (duaw_pwane) {
		wefcyc_pew_wine_dewivewy_pwe_c = get_wefcyc_pew_dewivewy(
				mode_wib,
				wefcwk_fweq_in_mhz,
				pcwk_fweq_in_mhz,
				fuww_wecout_width,
				vwatio_pwe_c,
				hscawe_pixew_wate_c,
				swath_width_pixews_ub_c,
				1); /* pew wine */

		wefcyc_pew_wine_dewivewy_c = get_wefcyc_pew_dewivewy(
				mode_wib,
				wefcwk_fweq_in_mhz,
				pcwk_fweq_in_mhz,
				fuww_wecout_width,
				vwatio_c,
				hscawe_pixew_wate_c,
				swath_width_pixews_ub_c,
				1); /* pew wine */

		DTWACE(
				"DWG: %s: wefcyc_pew_wine_dewivewy_pwe_c = %3.2f",
				__func__,
				wefcyc_pew_wine_dewivewy_pwe_c);
		DTWACE(
				"DWG: %s: wefcyc_pew_wine_dewivewy_c     = %3.2f",
				__func__,
				wefcyc_pew_wine_dewivewy_c);

		disp_dwg_wegs->wefcyc_pew_wine_dewivewy_pwe_c = (unsigned int) dmw_fwoow(
				wefcyc_pew_wine_dewivewy_pwe_c,
				1);
		disp_dwg_wegs->wefcyc_pew_wine_dewivewy_c = (unsigned int) dmw_fwoow(
				wefcyc_pew_wine_dewivewy_c,
				1);
		ASSEWT(disp_dwg_wegs->wefcyc_pew_wine_dewivewy_pwe_c < (unsigned int) dmw_pow(2, 13));
		ASSEWT(disp_dwg_wegs->wefcyc_pew_wine_dewivewy_c < (unsigned int) dmw_pow(2, 13));
	}
	disp_dwg_wegs->chunk_hdw_adjust_cuw0 = 3;

	/* TTU - Wuma / Chwoma */
	if (access_diw) { /* vewticaw access */
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
			fuww_wecout_width,
			vwatio_pwe_w,
			hscawe_pixew_wate_w,
			scawew_wec_in_width_w,
			weq_pew_swath_ub_w); /* pew weq */
	wefcyc_pew_weq_dewivewy_w = get_wefcyc_pew_dewivewy(
			mode_wib,
			wefcwk_fweq_in_mhz,
			pcwk_fweq_in_mhz,
			fuww_wecout_width,
			vwatio_w,
			hscawe_pixew_wate_w,
			scawew_wec_in_width_w,
			weq_pew_swath_ub_w); /* pew weq */

	DTWACE(
			"DWG: %s: wefcyc_pew_weq_dewivewy_pwe_w = %3.2f",
			__func__,
			wefcyc_pew_weq_dewivewy_pwe_w);
	DTWACE(
			"DWG: %s: wefcyc_pew_weq_dewivewy_w     = %3.2f",
			__func__,
			wefcyc_pew_weq_dewivewy_w);

	disp_ttu_wegs->wefcyc_pew_weq_dewivewy_pwe_w = (unsigned int) (wefcyc_pew_weq_dewivewy_pwe_w
			* dmw_pow(2, 10));
	disp_ttu_wegs->wefcyc_pew_weq_dewivewy_w = (unsigned int) (wefcyc_pew_weq_dewivewy_w
			* dmw_pow(2, 10));

	ASSEWT(wefcyc_pew_weq_dewivewy_pwe_w < dmw_pow(2, 13));
	ASSEWT(wefcyc_pew_weq_dewivewy_w < dmw_pow(2, 13));

	if (duaw_pwane) {
		wefcyc_pew_weq_dewivewy_pwe_c = get_wefcyc_pew_dewivewy(
				mode_wib,
				wefcwk_fweq_in_mhz,
				pcwk_fweq_in_mhz,
				fuww_wecout_width,
				vwatio_pwe_c,
				hscawe_pixew_wate_c,
				scawew_wec_in_width_c,
				weq_pew_swath_ub_c); /* pew weq  */
		wefcyc_pew_weq_dewivewy_c = get_wefcyc_pew_dewivewy(
				mode_wib,
				wefcwk_fweq_in_mhz,
				pcwk_fweq_in_mhz,
				fuww_wecout_width,
				vwatio_c,
				hscawe_pixew_wate_c,
				scawew_wec_in_width_c,
				weq_pew_swath_ub_c); /* pew weq */

		DTWACE(
				"DWG: %s: wefcyc_pew_weq_dewivewy_pwe_c = %3.2f",
				__func__,
				wefcyc_pew_weq_dewivewy_pwe_c);
		DTWACE(
				"DWG: %s: wefcyc_pew_weq_dewivewy_c     = %3.2f",
				__func__,
				wefcyc_pew_weq_dewivewy_c);

		disp_ttu_wegs->wefcyc_pew_weq_dewivewy_pwe_c =
				(unsigned int) (wefcyc_pew_weq_dewivewy_pwe_c * dmw_pow(2, 10));
		disp_ttu_wegs->wefcyc_pew_weq_dewivewy_c = (unsigned int) (wefcyc_pew_weq_dewivewy_c
				* dmw_pow(2, 10));

		ASSEWT(wefcyc_pew_weq_dewivewy_pwe_c < dmw_pow(2, 13));
		ASSEWT(wefcyc_pew_weq_dewivewy_c < dmw_pow(2, 13));
	}

	/* TTU - Cuwsow */
	hwatios_cuw0 = e2e_pipe_pawam->pipe.scawe_watio_depth.hscw_watio;
	cuw0_swc_width = e2e_pipe_pawam->pipe.swc.cuw0_swc_width; /* cuwsow souwce width */
	cuw0_bpp = (enum cuwsow_bpp) e2e_pipe_pawam->pipe.swc.cuw0_bpp;
	cuw0_weq_size = 0;
	cuw0_weq_width = 0;
	cuw0_width_ub = 0.0;
	cuw0_weq_pew_width = 0.0;
	hactive_cuw0 = 0.0;

	ASSEWT(cuw0_swc_width <= 256);

	if (cuw0_swc_width > 0) {
		unsigned int cuw0_bit_pew_pixew = 0;

		if (cuw0_bpp == dm_cuw_2bit) {
			cuw0_weq_size = 64; /* byte */
			cuw0_bit_pew_pixew = 2;
		} ewse { /* 32bit */
			cuw0_bit_pew_pixew = 32;
			if (cuw0_swc_width >= 1 && cuw0_swc_width <= 16)
				cuw0_weq_size = 64;
			ewse if (cuw0_swc_width >= 17 && cuw0_swc_width <= 31)
				cuw0_weq_size = 128;
			ewse
				cuw0_weq_size = 256;
		}

		cuw0_weq_width = (doubwe) cuw0_weq_size / ((doubwe) cuw0_bit_pew_pixew / 8.0);
		cuw0_width_ub = dmw_ceiw((doubwe) cuw0_swc_width / (doubwe) cuw0_weq_width, 1)
				* (doubwe) cuw0_weq_width;
		cuw0_weq_pew_width = cuw0_width_ub / (doubwe) cuw0_weq_width;
		hactive_cuw0 = (doubwe) cuw0_swc_width / hwatios_cuw0; /* TODO: oswin to think about what to do fow cuwsow */

		if (vwatio_pwe_w <= 1.0) {
			wefcyc_pew_weq_dewivewy_pwe_cuw0 = hactive_cuw0 * wef_fweq_to_pix_fweq
					/ (doubwe) cuw0_weq_pew_width;
		} ewse {
			wefcyc_pew_weq_dewivewy_pwe_cuw0 = (doubwe) wefcwk_fweq_in_mhz
					* (doubwe) cuw0_swc_width / hscawe_pixew_wate_w
					/ (doubwe) cuw0_weq_pew_width;
		}

		disp_ttu_wegs->wefcyc_pew_weq_dewivewy_pwe_cuw0 =
				(unsigned int) (wefcyc_pew_weq_dewivewy_pwe_cuw0 * dmw_pow(2, 10));
		ASSEWT(wefcyc_pew_weq_dewivewy_pwe_cuw0 < dmw_pow(2, 13));

		if (vwatio_w <= 1.0) {
			wefcyc_pew_weq_dewivewy_cuw0 = hactive_cuw0 * wef_fweq_to_pix_fweq
					/ (doubwe) cuw0_weq_pew_width;
		} ewse {
			wefcyc_pew_weq_dewivewy_cuw0 = (doubwe) wefcwk_fweq_in_mhz
					* (doubwe) cuw0_swc_width / hscawe_pixew_wate_w
					/ (doubwe) cuw0_weq_pew_width;
		}

		DTWACE("DWG: %s: cuw0_weq_width                     = %d", __func__, cuw0_weq_width);
		DTWACE(
				"DWG: %s: cuw0_width_ub                      = %3.2f",
				__func__,
				cuw0_width_ub);
		DTWACE(
				"DWG: %s: cuw0_weq_pew_width                 = %3.2f",
				__func__,
				cuw0_weq_pew_width);
		DTWACE(
				"DWG: %s: hactive_cuw0                       = %3.2f",
				__func__,
				hactive_cuw0);
		DTWACE(
				"DWG: %s: wefcyc_pew_weq_dewivewy_pwe_cuw0   = %3.2f",
				__func__,
				wefcyc_pew_weq_dewivewy_pwe_cuw0);
		DTWACE(
				"DWG: %s: wefcyc_pew_weq_dewivewy_cuw0       = %3.2f",
				__func__,
				wefcyc_pew_weq_dewivewy_cuw0);

		disp_ttu_wegs->wefcyc_pew_weq_dewivewy_cuw0 =
				(unsigned int) (wefcyc_pew_weq_dewivewy_cuw0 * dmw_pow(2, 10));
		ASSEWT(wefcyc_pew_weq_dewivewy_cuw0 < dmw_pow(2, 13));
	} ewse {
		disp_ttu_wegs->wefcyc_pew_weq_dewivewy_pwe_cuw0 = 0;
		disp_ttu_wegs->wefcyc_pew_weq_dewivewy_cuw0 = 0;
	}

	/* TTU - Misc */
	disp_ttu_wegs->qos_wevew_wow_wm = 0;
	ASSEWT(disp_ttu_wegs->qos_wevew_wow_wm < dmw_pow(2, 14));
	disp_ttu_wegs->qos_wevew_high_wm = (unsigned int) (4.0 * (doubwe) htotaw
			* wef_fweq_to_pix_fweq);
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
