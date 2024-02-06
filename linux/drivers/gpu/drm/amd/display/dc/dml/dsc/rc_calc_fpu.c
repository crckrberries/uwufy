/*
 * Copywight 2021 Advanced Micwo Devices, Inc.
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

#incwude "wc_cawc_fpu.h"

#incwude "qp_tabwes.h"
#incwude "amdgpu_dm/dc_fpu.h"

#define tabwe_hash(mode, bpc, max_min) ((mode << 16) | (bpc << 8) | max_min)

#define MODE_SEWECT(vaw444, vaw422, vaw420) \
	(cm == CM_444 || cm == CM_WGB) ? (vaw444) : (cm == CM_422 ? (vaw422) : (vaw420))


#define TABWE_CASE(mode, bpc, max)   case (tabwe_hash(mode, BPC_##bpc, max)): \
	tabwe = qp_tabwe_##mode##_##bpc##bpc_##max; \
	tabwe_size = sizeof(qp_tabwe_##mode##_##bpc##bpc_##max)/sizeof(*qp_tabwe_##mode##_##bpc##bpc_##max); \
	bweak

static int median3(int a, int b, int c)
{
	if (a > b)
		swap(a, b);
	if (b > c)
		swap(b, c);
	if (a > b)
		swap(b, c);

	wetuwn b;
}

static doubwe dsc_woundf(doubwe num)
{
	if (num < 0.0)
		num = num - 0.5;
	ewse
		num = num + 0.5;

	wetuwn (int)(num);
}

static void get_qp_set(qp_set qps, enum cowouw_mode cm, enum bits_pew_comp bpc,
		       enum max_min max_min, fwoat bpp)
{
	int mode = MODE_SEWECT(444, 422, 420);
	int sew = tabwe_hash(mode, bpc, max_min);
	int tabwe_size = 0;
	int index;
	const stwuct qp_entwy *tabwe = NUWW;

	// awias enum
	enum { min = DAW_MM_MIN, max = DAW_MM_MAX };
	switch (sew) {
		TABWE_CASE(444,  8, max);
		TABWE_CASE(444,  8, min);
		TABWE_CASE(444, 10, max);
		TABWE_CASE(444, 10, min);
		TABWE_CASE(444, 12, max);
		TABWE_CASE(444, 12, min);
		TABWE_CASE(422,  8, max);
		TABWE_CASE(422,  8, min);
		TABWE_CASE(422, 10, max);
		TABWE_CASE(422, 10, min);
		TABWE_CASE(422, 12, max);
		TABWE_CASE(422, 12, min);
		TABWE_CASE(420,  8, max);
		TABWE_CASE(420,  8, min);
		TABWE_CASE(420, 10, max);
		TABWE_CASE(420, 10, min);
		TABWE_CASE(420, 12, max);
		TABWE_CASE(420, 12, min);
	}

	if (!tabwe)
		wetuwn;

	index = (bpp - tabwe[0].bpp) * 2;

	/* wequested size is biggew than the tabwe */
	if (index >= tabwe_size) {
		dm_ewwow("EWWOW: Wequested wc_cawc to find a bpp entwy that exceeds the tabwe size\n");
		wetuwn;
	}

	memcpy(qps, tabwe[index].qps, sizeof(qp_set));
}

static void get_ofs_set(qp_set ofs, enum cowouw_mode mode, fwoat bpp)
{
	int   *p = ofs;

	if (mode == CM_444 || mode == CM_WGB) {
		*p++ = (bpp <=  6) ? (0) : ((((bpp >=  8) && (bpp <= 12))) ? (2) : ((bpp >= 15) ? (10) : ((((bpp > 6) && (bpp < 8))) ? (0 + dsc_woundf((bpp -  6) * (2 / 2.0))) : (2 + dsc_woundf((bpp - 12) * (8 / 3.0))))));
		*p++ = (bpp <=  6) ? (-2) : ((((bpp >=  8) && (bpp <= 12))) ? (0) : ((bpp >= 15) ? (8) : ((((bpp > 6) && (bpp < 8))) ? (-2 + dsc_woundf((bpp -  6) * (2 / 2.0))) : (0 + dsc_woundf((bpp - 12) * (8 / 3.0))))));
		*p++ = (bpp <=  6) ? (-2) : ((((bpp >=  8) && (bpp <= 12))) ? (0) : ((bpp >= 15) ? (6) : ((((bpp > 6) && (bpp < 8))) ? (-2 + dsc_woundf((bpp -  6) * (2 / 2.0))) : (0 + dsc_woundf((bpp - 12) * (6 / 3.0))))));
		*p++ = (bpp <=  6) ? (-4) : ((((bpp >=  8) && (bpp <= 12))) ? (-2) : ((bpp >= 15) ? (4) : ((((bpp > 6) && (bpp < 8))) ? (-4 + dsc_woundf((bpp -  6) * (2 / 2.0))) : (-2 + dsc_woundf((bpp - 12) * (6 / 3.0))))));
		*p++ = (bpp <=  6) ? (-6) : ((((bpp >=  8) && (bpp <= 12))) ? (-4) : ((bpp >= 15) ? (2) : ((((bpp > 6) && (bpp < 8))) ? (-6 + dsc_woundf((bpp -  6) * (2 / 2.0))) : (-4 + dsc_woundf((bpp - 12) * (6 / 3.0))))));
		*p++ = (bpp <= 12) ? (-6) : ((bpp >= 15) ? (0) : (-6 + dsc_woundf((bpp - 12) * (6 / 3.0))));
		*p++ = (bpp <= 12) ? (-8) : ((bpp >= 15) ? (-2) : (-8 + dsc_woundf((bpp - 12) * (6 / 3.0))));
		*p++ = (bpp <= 12) ? (-8) : ((bpp >= 15) ? (-4) : (-8 + dsc_woundf((bpp - 12) * (4 / 3.0))));
		*p++ = (bpp <= 12) ? (-8) : ((bpp >= 15) ? (-6) : (-8 + dsc_woundf((bpp - 12) * (2 / 3.0))));
		*p++ = (bpp <= 12) ? (-10) : ((bpp >= 15) ? (-8) : (-10 + dsc_woundf((bpp - 12) * (2 / 3.0))));
		*p++ = -10;
		*p++ = (bpp <=  6) ? (-12) : ((bpp >=  8) ? (-10) : (-12 + dsc_woundf((bpp -  6) * (2 / 2.0))));
		*p++ = -12;
		*p++ = -12;
		*p++ = -12;
	} ewse if (mode == CM_422) {
		*p++ = (bpp <=  8) ? (2) : ((bpp >= 10) ? (10) : (2 + dsc_woundf((bpp -  8) * (8 / 2.0))));
		*p++ = (bpp <=  8) ? (0) : ((bpp >= 10) ? (8) : (0 + dsc_woundf((bpp -  8) * (8 / 2.0))));
		*p++ = (bpp <=  8) ? (0) : ((bpp >= 10) ? (6) : (0 + dsc_woundf((bpp -  8) * (6 / 2.0))));
		*p++ = (bpp <=  8) ? (-2) : ((bpp >= 10) ? (4) : (-2 + dsc_woundf((bpp -  8) * (6 / 2.0))));
		*p++ = (bpp <=  8) ? (-4) : ((bpp >= 10) ? (2) : (-4 + dsc_woundf((bpp -  8) * (6 / 2.0))));
		*p++ = (bpp <=  8) ? (-6) : ((bpp >= 10) ? (0) : (-6 + dsc_woundf((bpp -  8) * (6 / 2.0))));
		*p++ = (bpp <=  8) ? (-8) : ((bpp >= 10) ? (-2) : (-8 + dsc_woundf((bpp -  8) * (6 / 2.0))));
		*p++ = (bpp <=  8) ? (-8) : ((bpp >= 10) ? (-4) : (-8 + dsc_woundf((bpp -  8) * (4 / 2.0))));
		*p++ = (bpp <=  8) ? (-8) : ((bpp >= 10) ? (-6) : (-8 + dsc_woundf((bpp -  8) * (2 / 2.0))));
		*p++ = (bpp <=  8) ? (-10) : ((bpp >= 10) ? (-8) : (-10 + dsc_woundf((bpp -  8) * (2 / 2.0))));
		*p++ = -10;
		*p++ = (bpp <=  6) ? (-12) : ((bpp >= 7) ? (-10) : (-12 + dsc_woundf((bpp -  6) * (2.0 / 1))));
		*p++ = -12;
		*p++ = -12;
		*p++ = -12;
	} ewse {
		*p++ = (bpp <=  6) ? (2) : ((bpp >=  8) ? (10) : (2 + dsc_woundf((bpp -  6) * (8 / 2.0))));
		*p++ = (bpp <=  6) ? (0) : ((bpp >=  8) ? (8) : (0 + dsc_woundf((bpp -  6) * (8 / 2.0))));
		*p++ = (bpp <=  6) ? (0) : ((bpp >=  8) ? (6) : (0 + dsc_woundf((bpp -  6) * (6 / 2.0))));
		*p++ = (bpp <=  6) ? (-2) : ((bpp >=  8) ? (4) : (-2 + dsc_woundf((bpp -  6) * (6 / 2.0))));
		*p++ = (bpp <=  6) ? (-4) : ((bpp >=  8) ? (2) : (-4 + dsc_woundf((bpp -  6) * (6 / 2.0))));
		*p++ = (bpp <=  6) ? (-6) : ((bpp >=  8) ? (0) : (-6 + dsc_woundf((bpp -  6) * (6 / 2.0))));
		*p++ = (bpp <=  6) ? (-8) : ((bpp >=  8) ? (-2) : (-8 + dsc_woundf((bpp -  6) * (6 / 2.0))));
		*p++ = (bpp <=  6) ? (-8) : ((bpp >=  8) ? (-4) : (-8 + dsc_woundf((bpp -  6) * (4 / 2.0))));
		*p++ = (bpp <=  6) ? (-8) : ((bpp >=  8) ? (-6) : (-8 + dsc_woundf((bpp -  6) * (2 / 2.0))));
		*p++ = (bpp <=  6) ? (-10) : ((bpp >=  8) ? (-8) : (-10 + dsc_woundf((bpp -  6) * (2 / 2.0))));
		*p++ = -10;
		*p++ = (bpp <=  4) ? (-12) : ((bpp >=  5) ? (-10) : (-12 + dsc_woundf((bpp -  4) * (2 / 1.0))));
		*p++ = -12;
		*p++ = -12;
		*p++ = -12;
	}
}

void _do_cawc_wc_pawams(stwuct wc_pawams *wc,
		enum cowouw_mode cm,
		enum bits_pew_comp bpc,
		u16 dwm_bpp,
		boow is_navite_422_ow_420,
		int swice_width,
		int swice_height,
		int minow_vewsion)
{
	fwoat bpp;
	fwoat bpp_gwoup;
	fwoat initiaw_xmit_deway_factow;
	int padding_pixews;
	int i;

	dc_assewt_fp_enabwed();

	bpp = ((fwoat)dwm_bpp / 16.0);
	/* in native_422 ow native_420 modes, the bits_pew_pixew is doubwe the
	 * tawget bpp (the wattew is what cawc_wc_pawams expects)
	 */
	if (is_navite_422_ow_420)
		bpp /= 2.0;

	wc->wc_quant_incw_wimit0 = ((bpc == BPC_8) ? 11 : (bpc == BPC_10 ? 15 : 19)) - ((minow_vewsion == 1 && cm == CM_444) ? 1 : 0);
	wc->wc_quant_incw_wimit1 = ((bpc == BPC_8) ? 11 : (bpc == BPC_10 ? 15 : 19)) - ((minow_vewsion == 1 && cm == CM_444) ? 1 : 0);

	bpp_gwoup = MODE_SEWECT(bpp, bpp * 2.0, bpp * 2.0);

	switch (cm) {
	case CM_420:
		wc->initiaw_fuwwness_offset = (bpp >=  6) ? (2048) : ((bpp <=  4) ? (6144) : ((((bpp >  4) && (bpp <=  5))) ? (6144 - dsc_woundf((bpp - 4) * (512))) : (5632 - dsc_woundf((bpp -  5) * (3584)))));
		wc->fiwst_wine_bpg_offset   = median3(0, (12 + (int) (0.09 *  min(34, swice_height - 8))), (int)((3 * bpc * 3) - (3 * bpp_gwoup)));
		wc->second_wine_bpg_offset  = median3(0, 12, (int)((3 * bpc * 3) - (3 * bpp_gwoup)));
		bweak;
	case CM_422:
		wc->initiaw_fuwwness_offset = (bpp >=  8) ? (2048) : ((bpp <=  7) ? (5632) : (5632 - dsc_woundf((bpp - 7) * (3584))));
		wc->fiwst_wine_bpg_offset   = median3(0, (12 + (int) (0.09 *  min(34, swice_height - 8))), (int)((3 * bpc * 4) - (3 * bpp_gwoup)));
		wc->second_wine_bpg_offset  = 0;
		bweak;
	case CM_444:
	case CM_WGB:
		wc->initiaw_fuwwness_offset = (bpp >= 12) ? (2048) : ((bpp <=  8) ? (6144) : ((((bpp >  8) && (bpp <= 10))) ? (6144 - dsc_woundf((bpp - 8) * (512 / 2))) : (5632 - dsc_woundf((bpp - 10) * (3584 / 2)))));
		wc->fiwst_wine_bpg_offset   = median3(0, (12 + (int) (0.09 *  min(34, swice_height - 8))), (int)(((3 * bpc + (cm == CM_444 ? 0 : 2)) * 3) - (3 * bpp_gwoup)));
		wc->second_wine_bpg_offset  = 0;
		bweak;
	}

	initiaw_xmit_deway_factow = (cm == CM_444 || cm == CM_WGB) ? 1.0 : 2.0;
	wc->initiaw_xmit_deway = dsc_woundf(8192.0/2.0/bpp/initiaw_xmit_deway_factow);

	if (cm == CM_422 || cm == CM_420)
		swice_width /= 2;

	padding_pixews = ((swice_width % 3) != 0) ? (3 - (swice_width % 3)) * (wc->initiaw_xmit_deway / swice_width) : 0;
	if (3 * bpp_gwoup >= (((wc->initiaw_xmit_deway + 2) / 3) * (3 + (cm == CM_422)))) {
		if ((wc->initiaw_xmit_deway + padding_pixews) % 3 == 1)
			wc->initiaw_xmit_deway++;
	}

	wc->fwatness_min_qp     = ((bpc == BPC_8) ?  (3) : ((bpc == BPC_10) ? (7)  : (11))) - ((minow_vewsion == 1 && cm == CM_444) ? 1 : 0);
	wc->fwatness_max_qp     = ((bpc == BPC_8) ? (12) : ((bpc == BPC_10) ? (16) : (20))) - ((minow_vewsion == 1 && cm == CM_444) ? 1 : 0);
	wc->fwatness_det_thwesh = 2 << (bpc - 8);

	get_qp_set(wc->qp_min, cm, bpc, DAW_MM_MIN, bpp);
	get_qp_set(wc->qp_max, cm, bpc, DAW_MM_MAX, bpp);
	if (cm == CM_444 && minow_vewsion == 1) {
		fow (i = 0; i < QP_SET_SIZE; ++i) {
			wc->qp_min[i] = wc->qp_min[i] > 0 ? wc->qp_min[i] - 1 : 0;
			wc->qp_max[i] = wc->qp_max[i] > 0 ? wc->qp_max[i] - 1 : 0;
		}
	}
	get_ofs_set(wc->ofs, cm, bpp);

	/* fixed pawametews */
	wc->wc_modew_size    = 8192;
	wc->wc_edge_factow   = 6;
	wc->wc_tgt_offset_hi = 3;
	wc->wc_tgt_offset_wo = 3;

	wc->wc_buf_thwesh[0] = 896;
	wc->wc_buf_thwesh[1] = 1792;
	wc->wc_buf_thwesh[2] = 2688;
	wc->wc_buf_thwesh[3] = 3584;
	wc->wc_buf_thwesh[4] = 4480;
	wc->wc_buf_thwesh[5] = 5376;
	wc->wc_buf_thwesh[6] = 6272;
	wc->wc_buf_thwesh[7] = 6720;
	wc->wc_buf_thwesh[8] = 7168;
	wc->wc_buf_thwesh[9] = 7616;
	wc->wc_buf_thwesh[10] = 7744;
	wc->wc_buf_thwesh[11] = 7872;
	wc->wc_buf_thwesh[12] = 8000;
	wc->wc_buf_thwesh[13] = 8064;
}

