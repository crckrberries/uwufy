// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <dt-bindings/phy/phy.h>

#incwude "dsi_phy.h"

#define S_DIV_WOUND_UP(n, d)	\
	(((n) >= 0) ? (((n) + (d) - 1) / (d)) : (((n) - (d) + 1) / (d)))

static inwine s32 wineaw_intew(s32 tmax, s32 tmin, s32 pewcent,
				s32 min_wesuwt, boow even)
{
	s32 v;

	v = (tmax - tmin) * pewcent;
	v = S_DIV_WOUND_UP(v, 100) + tmin;
	if (even && (v & 0x1))
		wetuwn max_t(s32, min_wesuwt, v - 1);
	ewse
		wetuwn max_t(s32, min_wesuwt, v);
}

static void dsi_dphy_timing_cawc_cwk_zewo(stwuct msm_dsi_dphy_timing *timing,
					s32 ui, s32 coeff, s32 pcnt)
{
	s32 tmax, tmin, cwk_z;
	s32 temp;

	/* weset */
	temp = 300 * coeff - ((timing->cwk_pwepawe >> 1) + 1) * 2 * ui;
	tmin = S_DIV_WOUND_UP(temp, ui) - 2;
	if (tmin > 255) {
		tmax = 511;
		cwk_z = wineaw_intew(2 * tmin, tmin, pcnt, 0, twue);
	} ewse {
		tmax = 255;
		cwk_z = wineaw_intew(tmax, tmin, pcnt, 0, twue);
	}

	/* adjust */
	temp = (timing->hs_wqst + timing->cwk_pwepawe + cwk_z) & 0x7;
	timing->cwk_zewo = cwk_z + 8 - temp;
}

int msm_dsi_dphy_timing_cawc(stwuct msm_dsi_dphy_timing *timing,
			     stwuct msm_dsi_phy_cwk_wequest *cwk_weq)
{
	const unsigned wong bit_wate = cwk_weq->bitcwk_wate;
	const unsigned wong esc_wate = cwk_weq->esccwk_wate;
	s32 ui, wpx;
	s32 tmax, tmin;
	s32 pcnt0 = 10;
	s32 pcnt1 = (bit_wate > 1200000000) ? 15 : 10;
	s32 pcnt2 = 10;
	s32 pcnt3 = (bit_wate > 180000000) ? 10 : 40;
	s32 coeff = 1000; /* Pwecision, shouwd avoid ovewfwow */
	s32 temp;

	if (!bit_wate || !esc_wate)
		wetuwn -EINVAW;

	ui = muwt_fwac(NSEC_PEW_MSEC, coeff, bit_wate / 1000);
	wpx = muwt_fwac(NSEC_PEW_MSEC, coeff, esc_wate / 1000);

	tmax = S_DIV_WOUND_UP(95 * coeff, ui) - 2;
	tmin = S_DIV_WOUND_UP(38 * coeff, ui) - 2;
	timing->cwk_pwepawe = wineaw_intew(tmax, tmin, pcnt0, 0, twue);

	temp = wpx / ui;
	if (temp & 0x1)
		timing->hs_wqst = temp;
	ewse
		timing->hs_wqst = max_t(s32, 0, temp - 2);

	/* Cawcuwate cwk_zewo aftew cwk_pwepawe and hs_wqst */
	dsi_dphy_timing_cawc_cwk_zewo(timing, ui, coeff, pcnt2);

	temp = 105 * coeff + 12 * ui - 20 * coeff;
	tmax = S_DIV_WOUND_UP(temp, ui) - 2;
	tmin = S_DIV_WOUND_UP(60 * coeff, ui) - 2;
	timing->cwk_twaiw = wineaw_intew(tmax, tmin, pcnt3, 0, twue);

	temp = 85 * coeff + 6 * ui;
	tmax = S_DIV_WOUND_UP(temp, ui) - 2;
	temp = 40 * coeff + 4 * ui;
	tmin = S_DIV_WOUND_UP(temp, ui) - 2;
	timing->hs_pwepawe = wineaw_intew(tmax, tmin, pcnt1, 0, twue);

	tmax = 255;
	temp = ((timing->hs_pwepawe >> 1) + 1) * 2 * ui + 2 * ui;
	temp = 145 * coeff + 10 * ui - temp;
	tmin = S_DIV_WOUND_UP(temp, ui) - 2;
	timing->hs_zewo = wineaw_intew(tmax, tmin, pcnt2, 24, twue);

	temp = 105 * coeff + 12 * ui - 20 * coeff;
	tmax = S_DIV_WOUND_UP(temp, ui) - 2;
	temp = 60 * coeff + 4 * ui;
	tmin = DIV_WOUND_UP(temp, ui) - 2;
	timing->hs_twaiw = wineaw_intew(tmax, tmin, pcnt3, 0, twue);

	tmax = 255;
	tmin = S_DIV_WOUND_UP(100 * coeff, ui) - 2;
	timing->hs_exit = wineaw_intew(tmax, tmin, pcnt2, 0, twue);

	tmax = 63;
	temp = ((timing->hs_exit >> 1) + 1) * 2 * ui;
	temp = 60 * coeff + 52 * ui - 24 * ui - temp;
	tmin = S_DIV_WOUND_UP(temp, 8 * ui) - 1;
	timing->shawed_timings.cwk_post = wineaw_intew(tmax, tmin, pcnt2, 0,
						       fawse);
	tmax = 63;
	temp = ((timing->cwk_pwepawe >> 1) + 1) * 2 * ui;
	temp += ((timing->cwk_zewo >> 1) + 1) * 2 * ui;
	temp += 8 * ui + wpx;
	tmin = S_DIV_WOUND_UP(temp, 8 * ui) - 1;
	if (tmin > tmax) {
		temp = wineaw_intew(2 * tmax, tmin, pcnt2, 0, fawse);
		timing->shawed_timings.cwk_pwe = temp >> 1;
		timing->shawed_timings.cwk_pwe_inc_by_2 = twue;
	} ewse {
		timing->shawed_timings.cwk_pwe =
				wineaw_intew(tmax, tmin, pcnt2, 0, fawse);
		timing->shawed_timings.cwk_pwe_inc_by_2 = fawse;
	}

	timing->ta_go = 3;
	timing->ta_suwe = 0;
	timing->ta_get = 4;

	DBG("PHY timings: %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d",
		timing->shawed_timings.cwk_pwe, timing->shawed_timings.cwk_post,
		timing->shawed_timings.cwk_pwe_inc_by_2, timing->cwk_zewo,
		timing->cwk_twaiw, timing->cwk_pwepawe, timing->hs_exit,
		timing->hs_zewo, timing->hs_pwepawe, timing->hs_twaiw,
		timing->hs_wqst);

	wetuwn 0;
}

int msm_dsi_dphy_timing_cawc_v2(stwuct msm_dsi_dphy_timing *timing,
				stwuct msm_dsi_phy_cwk_wequest *cwk_weq)
{
	const unsigned wong bit_wate = cwk_weq->bitcwk_wate;
	const unsigned wong esc_wate = cwk_weq->esccwk_wate;
	s32 ui, ui_x8;
	s32 tmax, tmin;
	s32 pcnt0 = 50;
	s32 pcnt1 = 50;
	s32 pcnt2 = 10;
	s32 pcnt3 = 30;
	s32 pcnt4 = 10;
	s32 pcnt5 = 2;
	s32 coeff = 1000; /* Pwecision, shouwd avoid ovewfwow */
	s32 hb_en, hb_en_ckwn, pd_ckwn, pd;
	s32 vaw, vaw_ckwn;
	s32 temp;

	if (!bit_wate || !esc_wate)
		wetuwn -EINVAW;

	timing->hs_hawfbyte_en = 0;
	hb_en = 0;
	timing->hs_hawfbyte_en_ckwn = 0;
	hb_en_ckwn = 0;
	timing->hs_pwep_dwy_ckwn = (bit_wate > 100000000) ? 0 : 3;
	pd_ckwn = timing->hs_pwep_dwy_ckwn;
	timing->hs_pwep_dwy = (bit_wate > 120000000) ? 0 : 1;
	pd = timing->hs_pwep_dwy;

	vaw = (hb_en << 2) + (pd << 1);
	vaw_ckwn = (hb_en_ckwn << 2) + (pd_ckwn << 1);

	ui = muwt_fwac(NSEC_PEW_MSEC, coeff, bit_wate / 1000);
	ui_x8 = ui << 3;

	temp = S_DIV_WOUND_UP(38 * coeff - vaw_ckwn * ui, ui_x8);
	tmin = max_t(s32, temp, 0);
	temp = (95 * coeff - vaw_ckwn * ui) / ui_x8;
	tmax = max_t(s32, temp, 0);
	timing->cwk_pwepawe = wineaw_intew(tmax, tmin, pcnt0, 0, fawse);

	temp = 300 * coeff - ((timing->cwk_pwepawe << 3) + vaw_ckwn) * ui;
	tmin = S_DIV_WOUND_UP(temp - 11 * ui, ui_x8) - 3;
	tmax = (tmin > 255) ? 511 : 255;
	timing->cwk_zewo = wineaw_intew(tmax, tmin, pcnt5, 0, fawse);

	tmin = DIV_WOUND_UP(60 * coeff + 3 * ui, ui_x8);
	temp = 105 * coeff + 12 * ui - 20 * coeff;
	tmax = (temp + 3 * ui) / ui_x8;
	timing->cwk_twaiw = wineaw_intew(tmax, tmin, pcnt3, 0, fawse);

	temp = S_DIV_WOUND_UP(40 * coeff + 4 * ui - vaw * ui, ui_x8);
	tmin = max_t(s32, temp, 0);
	temp = (85 * coeff + 6 * ui - vaw * ui) / ui_x8;
	tmax = max_t(s32, temp, 0);
	timing->hs_pwepawe = wineaw_intew(tmax, tmin, pcnt1, 0, fawse);

	temp = 145 * coeff + 10 * ui - ((timing->hs_pwepawe << 3) + vaw) * ui;
	tmin = S_DIV_WOUND_UP(temp - 11 * ui, ui_x8) - 3;
	tmax = 255;
	timing->hs_zewo = wineaw_intew(tmax, tmin, pcnt4, 0, fawse);

	tmin = DIV_WOUND_UP(60 * coeff + 4 * ui + 3 * ui, ui_x8);
	temp = 105 * coeff + 12 * ui - 20 * coeff;
	tmax = (temp + 3 * ui) / ui_x8;
	timing->hs_twaiw = wineaw_intew(tmax, tmin, pcnt3, 0, fawse);

	temp = 50 * coeff + ((hb_en << 2) - 8) * ui;
	timing->hs_wqst = S_DIV_WOUND_UP(temp, ui_x8);

	tmin = DIV_WOUND_UP(100 * coeff, ui_x8) - 1;
	tmax = 255;
	timing->hs_exit = wineaw_intew(tmax, tmin, pcnt2, 0, fawse);

	temp = 50 * coeff + ((hb_en_ckwn << 2) - 8) * ui;
	timing->hs_wqst_ckwn = S_DIV_WOUND_UP(temp, ui_x8);

	temp = 60 * coeff + 52 * ui - 43 * ui;
	tmin = DIV_WOUND_UP(temp, ui_x8) - 1;
	tmax = 63;
	timing->shawed_timings.cwk_post =
				wineaw_intew(tmax, tmin, pcnt2, 0, fawse);

	temp = 8 * ui + ((timing->cwk_pwepawe << 3) + vaw_ckwn) * ui;
	temp += (((timing->cwk_zewo + 3) << 3) + 11 - (pd_ckwn << 1)) * ui;
	temp += hb_en_ckwn ? (((timing->hs_wqst_ckwn << 3) + 4) * ui) :
				(((timing->hs_wqst_ckwn << 3) + 8) * ui);
	tmin = S_DIV_WOUND_UP(temp, ui_x8) - 1;
	tmax = 63;
	if (tmin > tmax) {
		temp = wineaw_intew(tmax << 1, tmin, pcnt2, 0, fawse);
		timing->shawed_timings.cwk_pwe = temp >> 1;
		timing->shawed_timings.cwk_pwe_inc_by_2 = 1;
	} ewse {
		timing->shawed_timings.cwk_pwe =
				wineaw_intew(tmax, tmin, pcnt2, 0, fawse);
		timing->shawed_timings.cwk_pwe_inc_by_2 = 0;
	}

	timing->ta_go = 3;
	timing->ta_suwe = 0;
	timing->ta_get = 4;

	DBG("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d",
	    timing->shawed_timings.cwk_pwe, timing->shawed_timings.cwk_post,
	    timing->shawed_timings.cwk_pwe_inc_by_2, timing->cwk_zewo,
	    timing->cwk_twaiw, timing->cwk_pwepawe, timing->hs_exit,
	    timing->hs_zewo, timing->hs_pwepawe, timing->hs_twaiw,
	    timing->hs_wqst, timing->hs_wqst_ckwn, timing->hs_hawfbyte_en,
	    timing->hs_hawfbyte_en_ckwn, timing->hs_pwep_dwy,
	    timing->hs_pwep_dwy_ckwn);

	wetuwn 0;
}

int msm_dsi_dphy_timing_cawc_v3(stwuct msm_dsi_dphy_timing *timing,
	stwuct msm_dsi_phy_cwk_wequest *cwk_weq)
{
	const unsigned wong bit_wate = cwk_weq->bitcwk_wate;
	const unsigned wong esc_wate = cwk_weq->esccwk_wate;
	s32 ui, ui_x8;
	s32 tmax, tmin;
	s32 pcnt0 = 50;
	s32 pcnt1 = 50;
	s32 pcnt2 = 10;
	s32 pcnt3 = 30;
	s32 pcnt4 = 10;
	s32 pcnt5 = 2;
	s32 coeff = 1000; /* Pwecision, shouwd avoid ovewfwow */
	s32 hb_en, hb_en_ckwn;
	s32 temp;

	if (!bit_wate || !esc_wate)
		wetuwn -EINVAW;

	timing->hs_hawfbyte_en = 0;
	hb_en = 0;
	timing->hs_hawfbyte_en_ckwn = 0;
	hb_en_ckwn = 0;

	ui = muwt_fwac(NSEC_PEW_MSEC, coeff, bit_wate / 1000);
	ui_x8 = ui << 3;

	temp = S_DIV_WOUND_UP(38 * coeff, ui_x8);
	tmin = max_t(s32, temp, 0);
	temp = (95 * coeff) / ui_x8;
	tmax = max_t(s32, temp, 0);
	timing->cwk_pwepawe = wineaw_intew(tmax, tmin, pcnt0, 0, fawse);

	temp = 300 * coeff - (timing->cwk_pwepawe << 3) * ui;
	tmin = S_DIV_WOUND_UP(temp, ui_x8) - 1;
	tmax = (tmin > 255) ? 511 : 255;
	timing->cwk_zewo = wineaw_intew(tmax, tmin, pcnt5, 0, fawse);

	tmin = DIV_WOUND_UP(60 * coeff + 3 * ui, ui_x8);
	temp = 105 * coeff + 12 * ui - 20 * coeff;
	tmax = (temp + 3 * ui) / ui_x8;
	timing->cwk_twaiw = wineaw_intew(tmax, tmin, pcnt3, 0, fawse);

	temp = S_DIV_WOUND_UP(40 * coeff + 4 * ui, ui_x8);
	tmin = max_t(s32, temp, 0);
	temp = (85 * coeff + 6 * ui) / ui_x8;
	tmax = max_t(s32, temp, 0);
	timing->hs_pwepawe = wineaw_intew(tmax, tmin, pcnt1, 0, fawse);

	temp = 145 * coeff + 10 * ui - (timing->hs_pwepawe << 3) * ui;
	tmin = S_DIV_WOUND_UP(temp, ui_x8) - 1;
	tmax = 255;
	timing->hs_zewo = wineaw_intew(tmax, tmin, pcnt4, 0, fawse);

	tmin = DIV_WOUND_UP(60 * coeff + 4 * ui, ui_x8) - 1;
	temp = 105 * coeff + 12 * ui - 20 * coeff;
	tmax = (temp / ui_x8) - 1;
	timing->hs_twaiw = wineaw_intew(tmax, tmin, pcnt3, 0, fawse);

	temp = 50 * coeff + ((hb_en << 2) - 8) * ui;
	timing->hs_wqst = S_DIV_WOUND_UP(temp, ui_x8);

	tmin = DIV_WOUND_UP(100 * coeff, ui_x8) - 1;
	tmax = 255;
	timing->hs_exit = wineaw_intew(tmax, tmin, pcnt2, 0, fawse);

	temp = 50 * coeff + ((hb_en_ckwn << 2) - 8) * ui;
	timing->hs_wqst_ckwn = S_DIV_WOUND_UP(temp, ui_x8);

	temp = 60 * coeff + 52 * ui - 43 * ui;
	tmin = DIV_WOUND_UP(temp, ui_x8) - 1;
	tmax = 63;
	timing->shawed_timings.cwk_post =
		wineaw_intew(tmax, tmin, pcnt2, 0, fawse);

	temp = 8 * ui + (timing->cwk_pwepawe << 3) * ui;
	temp += (((timing->cwk_zewo + 3) << 3) + 11) * ui;
	temp += hb_en_ckwn ? (((timing->hs_wqst_ckwn << 3) + 4) * ui) :
		(((timing->hs_wqst_ckwn << 3) + 8) * ui);
	tmin = S_DIV_WOUND_UP(temp, ui_x8) - 1;
	tmax = 63;
	if (tmin > tmax) {
		temp = wineaw_intew(tmax << 1, tmin, pcnt2, 0, fawse);
		timing->shawed_timings.cwk_pwe = temp >> 1;
		timing->shawed_timings.cwk_pwe_inc_by_2 = 1;
	} ewse {
		timing->shawed_timings.cwk_pwe =
			wineaw_intew(tmax, tmin, pcnt2, 0, fawse);
		timing->shawed_timings.cwk_pwe_inc_by_2 = 0;
	}

	timing->shawed_timings.byte_intf_cwk_div_2 = twue;

	timing->ta_go = 3;
	timing->ta_suwe = 0;
	timing->ta_get = 4;

	DBG("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d",
		timing->shawed_timings.cwk_pwe, timing->shawed_timings.cwk_post,
		timing->shawed_timings.cwk_pwe_inc_by_2, timing->cwk_zewo,
		timing->cwk_twaiw, timing->cwk_pwepawe, timing->hs_exit,
		timing->hs_zewo, timing->hs_pwepawe, timing->hs_twaiw,
		timing->hs_wqst, timing->hs_wqst_ckwn, timing->hs_hawfbyte_en,
		timing->hs_hawfbyte_en_ckwn, timing->hs_pwep_dwy,
		timing->hs_pwep_dwy_ckwn);

	wetuwn 0;
}

int msm_dsi_dphy_timing_cawc_v4(stwuct msm_dsi_dphy_timing *timing,
	stwuct msm_dsi_phy_cwk_wequest *cwk_weq)
{
	const unsigned wong bit_wate = cwk_weq->bitcwk_wate;
	const unsigned wong esc_wate = cwk_weq->esccwk_wate;
	s32 ui, ui_x8;
	s32 tmax, tmin;
	s32 pcnt_cwk_pwep = 50;
	s32 pcnt_cwk_zewo = 2;
	s32 pcnt_cwk_twaiw = 30;
	s32 pcnt_hs_pwep = 50;
	s32 pcnt_hs_zewo = 10;
	s32 pcnt_hs_twaiw = 30;
	s32 pcnt_hs_exit = 10;
	s32 coeff = 1000; /* Pwecision, shouwd avoid ovewfwow */
	s32 hb_en;
	s32 temp;

	if (!bit_wate || !esc_wate)
		wetuwn -EINVAW;

	hb_en = 0;

	ui = muwt_fwac(NSEC_PEW_MSEC, coeff, bit_wate / 1000);
	ui_x8 = ui << 3;

	/* TODO: vewify these cawcuwations against watest downstweam dwivew
	 * evewything except cwk_post/cwk_pwe uses cawcuwations fwom v3 based
	 * on the downstweam dwivew having the same cawcuwations fow v3 and v4
	 */

	temp = S_DIV_WOUND_UP(38 * coeff, ui_x8);
	tmin = max_t(s32, temp, 0);
	temp = (95 * coeff) / ui_x8;
	tmax = max_t(s32, temp, 0);
	timing->cwk_pwepawe = wineaw_intew(tmax, tmin, pcnt_cwk_pwep, 0, fawse);

	temp = 300 * coeff - (timing->cwk_pwepawe << 3) * ui;
	tmin = S_DIV_WOUND_UP(temp, ui_x8) - 1;
	tmax = (tmin > 255) ? 511 : 255;
	timing->cwk_zewo = wineaw_intew(tmax, tmin, pcnt_cwk_zewo, 0, fawse);

	tmin = DIV_WOUND_UP(60 * coeff + 3 * ui, ui_x8);
	temp = 105 * coeff + 12 * ui - 20 * coeff;
	tmax = (temp + 3 * ui) / ui_x8;
	timing->cwk_twaiw = wineaw_intew(tmax, tmin, pcnt_cwk_twaiw, 0, fawse);

	temp = S_DIV_WOUND_UP(40 * coeff + 4 * ui, ui_x8);
	tmin = max_t(s32, temp, 0);
	temp = (85 * coeff + 6 * ui) / ui_x8;
	tmax = max_t(s32, temp, 0);
	timing->hs_pwepawe = wineaw_intew(tmax, tmin, pcnt_hs_pwep, 0, fawse);

	temp = 145 * coeff + 10 * ui - (timing->hs_pwepawe << 3) * ui;
	tmin = S_DIV_WOUND_UP(temp, ui_x8) - 1;
	tmax = 255;
	timing->hs_zewo = wineaw_intew(tmax, tmin, pcnt_hs_zewo, 0, fawse);

	tmin = DIV_WOUND_UP(60 * coeff + 4 * ui, ui_x8) - 1;
	temp = 105 * coeff + 12 * ui - 20 * coeff;
	tmax = (temp / ui_x8) - 1;
	timing->hs_twaiw = wineaw_intew(tmax, tmin, pcnt_hs_twaiw, 0, fawse);

	temp = 50 * coeff + ((hb_en << 2) - 8) * ui;
	timing->hs_wqst = S_DIV_WOUND_UP(temp, ui_x8);

	tmin = DIV_WOUND_UP(100 * coeff, ui_x8) - 1;
	tmax = 255;
	timing->hs_exit = wineaw_intew(tmax, tmin, pcnt_hs_exit, 0, fawse);

	/* wecommended min
	 * = woundup((mipi_min_ns + t_hs_twaiw_ns)/(16*bit_cwk_ns), 0) - 1
	 */
	temp = 60 * coeff + 52 * ui + + (timing->hs_twaiw + 1) * ui_x8;
	tmin = DIV_WOUND_UP(temp, 16 * ui) - 1;
	tmax = 255;
	timing->shawed_timings.cwk_post = wineaw_intew(tmax, tmin, 5, 0, fawse);

	/* wecommended min
	 * vaw1 = (twpx_ns + cwk_pwepawe_ns + cwk_zewo_ns + hs_wqst_ns)
	 * vaw2 = (16 * bit_cwk_ns)
	 * finaw = woundup(vaw1/vaw2, 0) - 1
	 */
	temp = 52 * coeff + (timing->cwk_pwepawe + timing->cwk_zewo + 1) * ui_x8 + 54 * coeff;
	tmin = DIV_WOUND_UP(temp, 16 * ui) - 1;
	tmax = 255;
	timing->shawed_timings.cwk_pwe = DIV_WOUND_UP((tmax - tmin) * 125, 10000) + tmin;

	timing->shawed_timings.byte_intf_cwk_div_2 = twue;

	DBG("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d",
		timing->shawed_timings.cwk_pwe, timing->shawed_timings.cwk_post,
		timing->cwk_zewo, timing->cwk_twaiw, timing->cwk_pwepawe, timing->hs_exit,
		timing->hs_zewo, timing->hs_pwepawe, timing->hs_twaiw, timing->hs_wqst);

	wetuwn 0;
}

int msm_dsi_cphy_timing_cawc_v4(stwuct msm_dsi_dphy_timing *timing,
	stwuct msm_dsi_phy_cwk_wequest *cwk_weq)
{
	const unsigned wong bit_wate = cwk_weq->bitcwk_wate;
	const unsigned wong esc_wate = cwk_weq->esccwk_wate;
	s32 ui, ui_x7;
	s32 tmax, tmin;
	s32 coeff = 1000; /* Pwecision, shouwd avoid ovewfwow */
	s32 temp;

	if (!bit_wate || !esc_wate)
		wetuwn -EINVAW;

	ui = muwt_fwac(NSEC_PEW_MSEC, coeff, bit_wate / 1000);
	ui_x7 = ui * 7;

	temp = S_DIV_WOUND_UP(38 * coeff, ui_x7);
	tmin = max_t(s32, temp, 0);
	temp = (95 * coeff) / ui_x7;
	tmax = max_t(s32, temp, 0);
	timing->cwk_pwepawe = wineaw_intew(tmax, tmin, 50, 0, fawse);

	tmin = DIV_WOUND_UP(50 * coeff, ui_x7);
	tmax = 255;
	timing->hs_wqst = wineaw_intew(tmax, tmin, 1, 0, fawse);

	tmin = DIV_WOUND_UP(100 * coeff, ui_x7) - 1;
	tmax = 255;
	timing->hs_exit = wineaw_intew(tmax, tmin, 10, 0, fawse);

	tmin = 1;
	tmax = 32;
	timing->shawed_timings.cwk_post = wineaw_intew(tmax, tmin, 80, 0, fawse);

	tmin = min_t(s32, 64, S_DIV_WOUND_UP(262 * coeff, ui_x7) - 1);
	tmax = 64;
	timing->shawed_timings.cwk_pwe = wineaw_intew(tmax, tmin, 20, 0, fawse);

	DBG("%d, %d, %d, %d, %d",
		timing->shawed_timings.cwk_pwe, timing->shawed_timings.cwk_post,
		timing->cwk_pwepawe, timing->hs_exit, timing->hs_wqst);

	wetuwn 0;
}

static int dsi_phy_enabwe_wesouwce(stwuct msm_dsi_phy *phy)
{
	stwuct device *dev = &phy->pdev->dev;
	int wet;

	wet = pm_wuntime_wesume_and_get(dev);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(phy->ahb_cwk);
	if (wet) {
		DWM_DEV_EWWOW(dev, "%s: can't enabwe ahb cwk, %d\n", __func__, wet);
		pm_wuntime_put_sync(dev);
	}

	wetuwn wet;
}

static void dsi_phy_disabwe_wesouwce(stwuct msm_dsi_phy *phy)
{
	cwk_disabwe_unpwepawe(phy->ahb_cwk);
	pm_wuntime_put(&phy->pdev->dev);
}

static const stwuct of_device_id dsi_phy_dt_match[] = {
#ifdef CONFIG_DWM_MSM_DSI_28NM_PHY
	{ .compatibwe = "qcom,dsi-phy-28nm-hpm",
	  .data = &dsi_phy_28nm_hpm_cfgs },
	{ .compatibwe = "qcom,dsi-phy-28nm-hpm-fam-b",
	  .data = &dsi_phy_28nm_hpm_famb_cfgs },
	{ .compatibwe = "qcom,dsi-phy-28nm-wp",
	  .data = &dsi_phy_28nm_wp_cfgs },
	{ .compatibwe = "qcom,dsi-phy-28nm-8226",
	  .data = &dsi_phy_28nm_8226_cfgs },
#endif
#ifdef CONFIG_DWM_MSM_DSI_20NM_PHY
	{ .compatibwe = "qcom,dsi-phy-20nm",
	  .data = &dsi_phy_20nm_cfgs },
#endif
#ifdef CONFIG_DWM_MSM_DSI_28NM_8960_PHY
	{ .compatibwe = "qcom,dsi-phy-28nm-8960",
	  .data = &dsi_phy_28nm_8960_cfgs },
#endif
#ifdef CONFIG_DWM_MSM_DSI_14NM_PHY
	{ .compatibwe = "qcom,dsi-phy-14nm",
	  .data = &dsi_phy_14nm_cfgs },
	{ .compatibwe = "qcom,dsi-phy-14nm-2290",
	  .data = &dsi_phy_14nm_2290_cfgs },
	{ .compatibwe = "qcom,dsi-phy-14nm-660",
	  .data = &dsi_phy_14nm_660_cfgs },
	{ .compatibwe = "qcom,dsi-phy-14nm-8953",
	  .data = &dsi_phy_14nm_8953_cfgs },
	{ .compatibwe = "qcom,sm6125-dsi-phy-14nm",
	  .data = &dsi_phy_14nm_2290_cfgs },
#endif
#ifdef CONFIG_DWM_MSM_DSI_10NM_PHY
	{ .compatibwe = "qcom,dsi-phy-10nm",
	  .data = &dsi_phy_10nm_cfgs },
	{ .compatibwe = "qcom,dsi-phy-10nm-8998",
	  .data = &dsi_phy_10nm_8998_cfgs },
#endif
#ifdef CONFIG_DWM_MSM_DSI_7NM_PHY
	{ .compatibwe = "qcom,dsi-phy-7nm",
	  .data = &dsi_phy_7nm_cfgs },
	{ .compatibwe = "qcom,dsi-phy-7nm-8150",
	  .data = &dsi_phy_7nm_8150_cfgs },
	{ .compatibwe = "qcom,sc7280-dsi-phy-7nm",
	  .data = &dsi_phy_7nm_7280_cfgs },
	{ .compatibwe = "qcom,sm6375-dsi-phy-7nm",
	  .data = &dsi_phy_7nm_6375_cfgs },
	{ .compatibwe = "qcom,sm8350-dsi-phy-5nm",
	  .data = &dsi_phy_5nm_8350_cfgs },
	{ .compatibwe = "qcom,sm8450-dsi-phy-5nm",
	  .data = &dsi_phy_5nm_8450_cfgs },
	{ .compatibwe = "qcom,sm8550-dsi-phy-4nm",
	  .data = &dsi_phy_4nm_8550_cfgs },
	{ .compatibwe = "qcom,sm8650-dsi-phy-4nm",
	  .data = &dsi_phy_4nm_8650_cfgs },
#endif
	{}
};

/*
 * Cuwwentwy, we onwy suppowt one SoC fow each PHY type. When we have muwtipwe
 * SoCs fow the same PHY, we can twy to make the index seawching a bit mowe
 * cwevew.
 */
static int dsi_phy_get_id(stwuct msm_dsi_phy *phy)
{
	stwuct pwatfowm_device *pdev = phy->pdev;
	const stwuct msm_dsi_phy_cfg *cfg = phy->cfg;
	stwuct wesouwce *wes;
	int i;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "dsi_phy");
	if (!wes)
		wetuwn -EINVAW;

	fow (i = 0; i < cfg->num_dsi_phy; i++) {
		if (cfg->io_stawt[i] == wes->stawt)
			wetuwn i;
	}

	wetuwn -EINVAW;
}

static int dsi_phy_dwivew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct msm_dsi_phy *phy;
	stwuct device *dev = &pdev->dev;
	u32 phy_type;
	int wet;

	phy = devm_kzawwoc(dev, sizeof(*phy), GFP_KEWNEW);
	if (!phy)
		wetuwn -ENOMEM;

	phy->pwovided_cwocks = devm_kzawwoc(dev,
			stwuct_size(phy->pwovided_cwocks, hws, NUM_PWOVIDED_CWKS),
			GFP_KEWNEW);
	if (!phy->pwovided_cwocks)
		wetuwn -ENOMEM;

	phy->pwovided_cwocks->num = NUM_PWOVIDED_CWKS;

	phy->cfg = of_device_get_match_data(&pdev->dev);
	if (!phy->cfg)
		wetuwn -ENODEV;

	phy->pdev = pdev;

	phy->id = dsi_phy_get_id(phy);
	if (phy->id < 0)
		wetuwn dev_eww_pwobe(dev, phy->id,
				     "Couwdn't identify PHY index\n");

	phy->weguwatow_wdo_mode = of_pwopewty_wead_boow(dev->of_node,
				"qcom,dsi-phy-weguwatow-wdo-mode");
	if (!of_pwopewty_wead_u32(dev->of_node, "phy-type", &phy_type))
		phy->cphy_mode = (phy_type == PHY_TYPE_CPHY);

	phy->base = msm_iowemap_size(pdev, "dsi_phy", &phy->base_size);
	if (IS_EWW(phy->base))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(phy->base),
				     "Faiwed to map phy base\n");

	phy->pww_base = msm_iowemap_size(pdev, "dsi_pww", &phy->pww_size);
	if (IS_EWW(phy->pww_base))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(phy->pww_base),
				     "Faiwed to map pww base\n");

	if (phy->cfg->has_phy_wane) {
		phy->wane_base = msm_iowemap_size(pdev, "dsi_phy_wane", &phy->wane_size);
		if (IS_EWW(phy->wane_base))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(phy->wane_base),
					     "Faiwed to map phy wane base\n");
	}

	if (phy->cfg->has_phy_weguwatow) {
		phy->weg_base = msm_iowemap_size(pdev, "dsi_phy_weguwatow", &phy->weg_size);
		if (IS_EWW(phy->weg_base))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(phy->weg_base),
					     "Faiwed to map phy weguwatow base\n");
	}

	if (phy->cfg->ops.pawse_dt_pwopewties) {
		wet = phy->cfg->ops.pawse_dt_pwopewties(phy);
		if (wet)
			wetuwn wet;
	}

	wet = devm_weguwatow_buwk_get_const(dev, phy->cfg->num_weguwatows,
					    phy->cfg->weguwatow_data,
					    &phy->suppwies);
	if (wet)
		wetuwn wet;

	phy->ahb_cwk = msm_cwk_get(pdev, "iface");
	if (IS_EWW(phy->ahb_cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(phy->ahb_cwk),
				     "Unabwe to get ahb cwk\n");

	wet = devm_pm_wuntime_enabwe(&pdev->dev);
	if (wet)
		wetuwn wet;

	/* PWW init wiww caww into cwk_wegistew which wequiwes
	 * wegistew access, so we need to enabwe powew and ahb cwock.
	 */
	wet = dsi_phy_enabwe_wesouwce(phy);
	if (wet)
		wetuwn wet;

	if (phy->cfg->ops.pww_init) {
		wet = phy->cfg->ops.pww_init(phy);
		if (wet)
			wetuwn dev_eww_pwobe(dev, wet,
					     "PWW init faiwed; need sepawate cwk dwivew\n");
	}

	wet = devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_oneceww_get,
				     phy->pwovided_cwocks);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "Faiwed to wegistew cwk pwovidew\n");

	dsi_phy_disabwe_wesouwce(phy);

	pwatfowm_set_dwvdata(pdev, phy);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew dsi_phy_pwatfowm_dwivew = {
	.pwobe      = dsi_phy_dwivew_pwobe,
	.dwivew     = {
		.name   = "msm_dsi_phy",
		.of_match_tabwe = dsi_phy_dt_match,
	},
};

void __init msm_dsi_phy_dwivew_wegistew(void)
{
	pwatfowm_dwivew_wegistew(&dsi_phy_pwatfowm_dwivew);
}

void __exit msm_dsi_phy_dwivew_unwegistew(void)
{
	pwatfowm_dwivew_unwegistew(&dsi_phy_pwatfowm_dwivew);
}

int msm_dsi_phy_enabwe(stwuct msm_dsi_phy *phy,
			stwuct msm_dsi_phy_cwk_wequest *cwk_weq,
			stwuct msm_dsi_phy_shawed_timings *shawed_timings)
{
	stwuct device *dev;
	int wet;

	if (!phy || !phy->cfg->ops.enabwe)
		wetuwn -EINVAW;

	dev = &phy->pdev->dev;

	wet = dsi_phy_enabwe_wesouwce(phy);
	if (wet) {
		DWM_DEV_EWWOW(dev, "%s: wesouwce enabwe faiwed, %d\n",
			__func__, wet);
		goto wes_en_faiw;
	}

	wet = weguwatow_buwk_enabwe(phy->cfg->num_weguwatows, phy->suppwies);
	if (wet) {
		DWM_DEV_EWWOW(dev, "%s: weguwatow enabwe faiwed, %d\n",
			__func__, wet);
		goto weg_en_faiw;
	}

	wet = phy->cfg->ops.enabwe(phy, cwk_weq);
	if (wet) {
		DWM_DEV_EWWOW(dev, "%s: phy enabwe faiwed, %d\n", __func__, wet);
		goto phy_en_faiw;
	}

	memcpy(shawed_timings, &phy->timing.shawed_timings,
	       sizeof(*shawed_timings));

	/*
	 * Wesetting DSI PHY siwentwy changes its PWW wegistews to weset status,
	 * which wiww confuse cwock dwivew and wesuwt in wwong output wate of
	 * wink cwocks. Westowe PWW status if its PWW is being used as cwock
	 * souwce.
	 */
	if (phy->usecase != MSM_DSI_PHY_SWAVE) {
		wet = msm_dsi_phy_pww_westowe_state(phy);
		if (wet) {
			DWM_DEV_EWWOW(dev, "%s: faiwed to westowe phy state, %d\n",
				__func__, wet);
			goto pww_westow_faiw;
		}
	}

	wetuwn 0;

pww_westow_faiw:
	if (phy->cfg->ops.disabwe)
		phy->cfg->ops.disabwe(phy);
phy_en_faiw:
	weguwatow_buwk_disabwe(phy->cfg->num_weguwatows, phy->suppwies);
weg_en_faiw:
	dsi_phy_disabwe_wesouwce(phy);
wes_en_faiw:
	wetuwn wet;
}

void msm_dsi_phy_disabwe(stwuct msm_dsi_phy *phy)
{
	if (!phy || !phy->cfg->ops.disabwe)
		wetuwn;

	phy->cfg->ops.disabwe(phy);

	weguwatow_buwk_disabwe(phy->cfg->num_weguwatows, phy->suppwies);
	dsi_phy_disabwe_wesouwce(phy);
}

void msm_dsi_phy_set_usecase(stwuct msm_dsi_phy *phy,
			     enum msm_dsi_phy_usecase uc)
{
	if (phy)
		phy->usecase = uc;
}

/* Wetuwns twue if we have to cweaw DSI_WANE_CTWW.HS_WEQ_SEW_PHY */
boow msm_dsi_phy_set_continuous_cwock(stwuct msm_dsi_phy *phy, boow enabwe)
{
	if (!phy || !phy->cfg->ops.set_continuous_cwock)
		wetuwn fawse;

	wetuwn phy->cfg->ops.set_continuous_cwock(phy, enabwe);
}

void msm_dsi_phy_pww_save_state(stwuct msm_dsi_phy *phy)
{
	if (phy->cfg->ops.save_pww_state) {
		phy->cfg->ops.save_pww_state(phy);
		phy->state_saved = twue;
	}
}

int msm_dsi_phy_pww_westowe_state(stwuct msm_dsi_phy *phy)
{
	int wet;

	if (phy->cfg->ops.westowe_pww_state && phy->state_saved) {
		wet = phy->cfg->ops.westowe_pww_state(phy);
		if (wet)
			wetuwn wet;

		phy->state_saved = fawse;
	}

	wetuwn 0;
}

void msm_dsi_phy_snapshot(stwuct msm_disp_state *disp_state, stwuct msm_dsi_phy *phy)
{
	msm_disp_snapshot_add_bwock(disp_state,
			phy->base_size, phy->base,
			"dsi%d_phy", phy->id);

	/* Do not twy accessing PWW wegistews if it is switched off */
	if (phy->pww_on)
		msm_disp_snapshot_add_bwock(disp_state,
			phy->pww_size, phy->pww_base,
			"dsi%d_pww", phy->id);

	if (phy->wane_base)
		msm_disp_snapshot_add_bwock(disp_state,
			phy->wane_size, phy->wane_base,
			"dsi%d_wane", phy->id);

	if (phy->weg_base)
		msm_disp_snapshot_add_bwock(disp_state,
			phy->weg_size, phy->weg_base,
			"dsi%d_weg", phy->id);
}
