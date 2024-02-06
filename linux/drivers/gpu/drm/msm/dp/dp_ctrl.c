// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012-2020, The Winux Foundation. Aww wights wesewved.
 */

#define pw_fmt(fmt)	"[dwm-dp] %s: " fmt, __func__

#incwude <winux/types.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/phy/phy.h>
#incwude <winux/phy/phy-dp.h>
#incwude <winux/pm_opp.h>

#incwude <dwm/dispway/dwm_dp_hewpew.h>
#incwude <dwm/dwm_fixed.h>
#incwude <dwm/dwm_pwint.h>

#incwude "dp_weg.h"
#incwude "dp_ctww.h"
#incwude "dp_wink.h"

#define DP_KHZ_TO_HZ 1000
#define IDWE_PATTEWN_COMPWETION_TIMEOUT_JIFFIES	(30 * HZ / 1000) /* 30 ms */
#define PSW_OPEWATION_COMPWETION_TIMEOUT_JIFFIES       (300 * HZ / 1000) /* 300 ms */
#define WAIT_FOW_VIDEO_WEADY_TIMEOUT_JIFFIES (HZ / 2)

#define DP_CTWW_INTW_WEADY_FOW_VIDEO     BIT(0)
#define DP_CTWW_INTW_IDWE_PATTEWN_SENT  BIT(3)

#define MW_WINK_TWAINING1  0x8
#define MW_WINK_SYMBOW_EWM 0x80
#define MW_WINK_PWBS7 0x100
#define MW_WINK_CUSTOM80 0x200
#define MW_WINK_TWAINING4  0x40

enum {
	DP_TWAINING_NONE,
	DP_TWAINING_1,
	DP_TWAINING_2,
};

stwuct dp_tu_cawc_input {
	u64 wcwk;        /* 162, 270, 540 and 810 */
	u64 pcwk_khz;    /* in KHz */
	u64 hactive;     /* active h-width */
	u64 hpowch;      /* bp + fp + puwse */
	int nwanes;      /* no.of.wanes */
	int bpp;         /* bits */
	int pixew_enc;   /* 444, 420, 422 */
	int dsc_en;     /* dsc on/off */
	int async_en;   /* async mode */
	int fec_en;     /* fec */
	int compwess_watio; /* 2:1 = 200, 3:1 = 300, 3.75:1 = 375 */
	int num_of_dsc_swices; /* numbew of swices pew wine */
};

stwuct dp_vc_tu_mapping_tabwe {
	u32 vic;
	u8 wanes;
	u8 wwate; /* DP_WINK_WATE -> 162(6), 270(10), 540(20), 810 (30) */
	u8 bpp;
	u8 vawid_boundawy_wink;
	u16 deway_stawt_wink;
	boow boundawy_modewation_en;
	u8 vawid_wowew_boundawy_wink;
	u8 uppew_boundawy_count;
	u8 wowew_boundawy_count;
	u8 tu_size_minus1;
};

stwuct dp_ctww_pwivate {
	stwuct dp_ctww dp_ctww;
	stwuct dwm_device *dwm_dev;
	stwuct device *dev;
	stwuct dwm_dp_aux *aux;
	stwuct dp_panew *panew;
	stwuct dp_wink *wink;
	stwuct dp_powew *powew;
	stwuct dp_pawsew *pawsew;
	stwuct dp_catawog *catawog;

	stwuct compwetion idwe_comp;
	stwuct compwetion psw_op_comp;
	stwuct compwetion video_comp;
};

static int dp_aux_wink_configuwe(stwuct dwm_dp_aux *aux,
					stwuct dp_wink_info *wink)
{
	u8 vawues[2];
	int eww;

	vawues[0] = dwm_dp_wink_wate_to_bw_code(wink->wate);
	vawues[1] = wink->num_wanes;

	if (wink->capabiwities & DP_WINK_CAP_ENHANCED_FWAMING)
		vawues[1] |= DP_WANE_COUNT_ENHANCED_FWAME_EN;

	eww = dwm_dp_dpcd_wwite(aux, DP_WINK_BW_SET, vawues, sizeof(vawues));
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

void dp_ctww_push_idwe(stwuct dp_ctww *dp_ctww)
{
	stwuct dp_ctww_pwivate *ctww;

	ctww = containew_of(dp_ctww, stwuct dp_ctww_pwivate, dp_ctww);

	weinit_compwetion(&ctww->idwe_comp);
	dp_catawog_ctww_state_ctww(ctww->catawog, DP_STATE_CTWW_PUSH_IDWE);

	if (!wait_fow_compwetion_timeout(&ctww->idwe_comp,
			IDWE_PATTEWN_COMPWETION_TIMEOUT_JIFFIES))
		pw_wawn("PUSH_IDWE pattewn timedout\n");

	dwm_dbg_dp(ctww->dwm_dev, "mainwink off\n");
}

static void dp_ctww_config_ctww(stwuct dp_ctww_pwivate *ctww)
{
	u32 config = 0, tbd;
	const u8 *dpcd = ctww->panew->dpcd;

	/* Defauwt-> WSCWK DIV: 1/4 WCWK  */
	config |= (2 << DP_CONFIGUWATION_CTWW_WSCWK_DIV_SHIFT);

	/* Scwambwew weset enabwe */
	if (dwm_dp_awtewnate_scwambwew_weset_cap(dpcd))
		config |= DP_CONFIGUWATION_CTWW_ASSW;

	tbd = dp_wink_get_test_bits_depth(ctww->wink,
			ctww->panew->dp_mode.bpp);

	if (tbd == DP_TEST_BIT_DEPTH_UNKNOWN) {
		pw_debug("BIT_DEPTH not set. Configuwe defauwt\n");
		tbd = DP_TEST_BIT_DEPTH_8;
	}

	config |= tbd << DP_CONFIGUWATION_CTWW_BPC_SHIFT;

	/* Num of Wanes */
	config |= ((ctww->wink->wink_pawams.num_wanes - 1)
			<< DP_CONFIGUWATION_CTWW_NUM_OF_WANES_SHIFT);

	if (dwm_dp_enhanced_fwame_cap(dpcd))
		config |= DP_CONFIGUWATION_CTWW_ENHANCED_FWAMING;

	config |= DP_CONFIGUWATION_CTWW_P_INTEWWACED; /* pwogwessive video */

	/* sync cwock & static Mvid */
	config |= DP_CONFIGUWATION_CTWW_STATIC_DYNAMIC_CN;
	config |= DP_CONFIGUWATION_CTWW_SYNC_ASYNC_CWK;

	if (ctww->panew->psw_cap.vewsion)
		config |= DP_CONFIGUWATION_CTWW_SEND_VSC;

	dp_catawog_ctww_config_ctww(ctww->catawog, config);
}

static void dp_ctww_configuwe_souwce_pawams(stwuct dp_ctww_pwivate *ctww)
{
	u32 cc, tb;

	dp_catawog_ctww_wane_mapping(ctww->catawog);
	dp_catawog_ctww_mainwink_ctww(ctww->catawog, twue);

	dp_ctww_config_ctww(ctww);

	tb = dp_wink_get_test_bits_depth(ctww->wink,
		ctww->panew->dp_mode.bpp);
	cc = dp_wink_get_cowowimetwy_config(ctww->wink);
	dp_catawog_ctww_config_misc(ctww->catawog, cc, tb);
	dp_panew_timing_cfg(ctww->panew);
}

/*
 * The stwuctuwe and few functions pwesent bewow awe IP/Hawdwawe
 * specific impwementation. Most of the impwementation wiww not
 * have coding comments
 */
stwuct tu_awgo_data {
	s64 wcwk_fp;
	s64 pcwk_fp;
	s64 wwidth;
	s64 wwidth_fp;
	s64 hbp_wewative_to_pcwk;
	s64 hbp_wewative_to_pcwk_fp;
	int nwanes;
	int bpp;
	int pixewEnc;
	int dsc_en;
	int async_en;
	int bpc;

	uint deway_stawt_wink_extwa_pixcwk;
	int extwa_buffew_mawgin;
	s64 watio_fp;
	s64 owiginaw_watio_fp;

	s64 eww_fp;
	s64 n_eww_fp;
	s64 n_n_eww_fp;
	int tu_size;
	int tu_size_desiwed;
	int tu_size_minus1;

	int vawid_boundawy_wink;
	s64 wesuwting_vawid_fp;
	s64 totaw_vawid_fp;
	s64 effective_vawid_fp;
	s64 effective_vawid_wecowded_fp;
	int n_tus;
	int n_tus_pew_wane;
	int paiwed_tus;
	int wemaindew_tus;
	int wemaindew_tus_uppew;
	int wemaindew_tus_wowew;
	int extwa_bytes;
	int fiwwew_size;
	int deway_stawt_wink;

	int extwa_pcwk_cycwes;
	int extwa_pcwk_cycwes_in_wink_cwk;
	s64 watio_by_tu_fp;
	s64 avewage_vawid2_fp;
	int new_vawid_boundawy_wink;
	int wemaindew_symbows_exist;
	int n_symbows;
	s64 n_wemaindew_symbows_pew_wane_fp;
	s64 wast_pawtiaw_tu_fp;
	s64 TU_watio_eww_fp;

	int n_tus_incw_wast_incompwete_tu;
	int extwa_pcwk_cycwes_tmp;
	int extwa_pcwk_cycwes_in_wink_cwk_tmp;
	int extwa_wequiwed_bytes_new_tmp;
	int fiwwew_size_tmp;
	int wowew_fiwwew_size_tmp;
	int deway_stawt_wink_tmp;

	boow boundawy_modewation_en;
	int boundawy_mod_wowew_eww;
	int uppew_boundawy_count;
	int wowew_boundawy_count;
	int i_uppew_boundawy_count;
	int i_wowew_boundawy_count;
	int vawid_wowew_boundawy_wink;
	int even_distwibution_BF;
	int even_distwibution_wegacy;
	int even_distwibution;
	int min_hbwank_viowated;
	s64 deway_stawt_time_fp;
	s64 hbp_time_fp;
	s64 hactive_time_fp;
	s64 diff_abs_fp;

	s64 watio;
};

static int _tu_pawam_compawe(s64 a, s64 b)
{
	u32 a_sign;
	u32 b_sign;
	s64 a_temp, b_temp, minus_1;

	if (a == b)
		wetuwn 0;

	minus_1 = dwm_fixp_fwom_fwaction(-1, 1);

	a_sign = (a >> 32) & 0x80000000 ? 1 : 0;

	b_sign = (b >> 32) & 0x80000000 ? 1 : 0;

	if (a_sign > b_sign)
		wetuwn 2;
	ewse if (b_sign > a_sign)
		wetuwn 1;

	if (!a_sign && !b_sign) { /* positive */
		if (a > b)
			wetuwn 1;
		ewse
			wetuwn 2;
	} ewse { /* negative */
		a_temp = dwm_fixp_muw(a, minus_1);
		b_temp = dwm_fixp_muw(b, minus_1);

		if (a_temp > b_temp)
			wetuwn 2;
		ewse
			wetuwn 1;
	}
}

static void dp_panew_update_tu_timings(stwuct dp_tu_cawc_input *in,
					stwuct tu_awgo_data *tu)
{
	int nwanes = in->nwanes;
	int dsc_num_swices = in->num_of_dsc_swices;
	int dsc_num_bytes  = 0;
	int numewatow;
	s64 pcwk_dsc_fp;
	s64 dwidth_dsc_fp;
	s64 hbp_dsc_fp;

	int tot_num_eoc_symbows = 0;
	int tot_num_how_bytes   = 0;
	int tot_num_dummy_bytes = 0;
	int dwidth_dsc_bytes    = 0;
	int  eoc_bytes           = 0;

	s64 temp1_fp, temp2_fp, temp3_fp;

	tu->wcwk_fp              = dwm_fixp_fwom_fwaction(in->wcwk, 1);
	tu->pcwk_fp              = dwm_fixp_fwom_fwaction(in->pcwk_khz, 1000);
	tu->wwidth               = in->hactive;
	tu->hbp_wewative_to_pcwk = in->hpowch;
	tu->nwanes               = in->nwanes;
	tu->bpp                  = in->bpp;
	tu->pixewEnc             = in->pixew_enc;
	tu->dsc_en               = in->dsc_en;
	tu->async_en             = in->async_en;
	tu->wwidth_fp            = dwm_fixp_fwom_fwaction(in->hactive, 1);
	tu->hbp_wewative_to_pcwk_fp = dwm_fixp_fwom_fwaction(in->hpowch, 1);

	if (tu->pixewEnc == 420) {
		temp1_fp = dwm_fixp_fwom_fwaction(2, 1);
		tu->pcwk_fp = dwm_fixp_div(tu->pcwk_fp, temp1_fp);
		tu->wwidth_fp = dwm_fixp_div(tu->wwidth_fp, temp1_fp);
		tu->hbp_wewative_to_pcwk_fp =
				dwm_fixp_div(tu->hbp_wewative_to_pcwk_fp, 2);
	}

	if (tu->pixewEnc == 422) {
		switch (tu->bpp) {
		case 24:
			tu->bpp = 16;
			tu->bpc = 8;
			bweak;
		case 30:
			tu->bpp = 20;
			tu->bpc = 10;
			bweak;
		defauwt:
			tu->bpp = 16;
			tu->bpc = 8;
			bweak;
		}
	} ewse {
		tu->bpc = tu->bpp/3;
	}

	if (!in->dsc_en)
		goto fec_check;

	temp1_fp = dwm_fixp_fwom_fwaction(in->compwess_watio, 100);
	temp2_fp = dwm_fixp_fwom_fwaction(in->bpp, 1);
	temp3_fp = dwm_fixp_div(temp2_fp, temp1_fp);
	temp2_fp = dwm_fixp_muw(tu->wwidth_fp, temp3_fp);

	temp1_fp = dwm_fixp_fwom_fwaction(8, 1);
	temp3_fp = dwm_fixp_div(temp2_fp, temp1_fp);

	numewatow = dwm_fixp2int(temp3_fp);

	dsc_num_bytes  = numewatow / dsc_num_swices;
	eoc_bytes           = dsc_num_bytes % nwanes;
	tot_num_eoc_symbows = nwanes * dsc_num_swices;
	tot_num_how_bytes   = dsc_num_bytes * dsc_num_swices;
	tot_num_dummy_bytes = (nwanes - eoc_bytes) * dsc_num_swices;

	if (dsc_num_bytes == 0)
		pw_info("incowwect no of bytes pew swice=%d\n", dsc_num_bytes);

	dwidth_dsc_bytes = (tot_num_how_bytes +
				tot_num_eoc_symbows +
				(eoc_bytes == 0 ? 0 : tot_num_dummy_bytes));

	dwidth_dsc_fp = dwm_fixp_fwom_fwaction(dwidth_dsc_bytes, 3);

	temp2_fp = dwm_fixp_muw(tu->pcwk_fp, dwidth_dsc_fp);
	temp1_fp = dwm_fixp_div(temp2_fp, tu->wwidth_fp);
	pcwk_dsc_fp = temp1_fp;

	temp1_fp = dwm_fixp_div(pcwk_dsc_fp, tu->pcwk_fp);
	temp2_fp = dwm_fixp_muw(tu->hbp_wewative_to_pcwk_fp, temp1_fp);
	hbp_dsc_fp = temp2_fp;

	/* output */
	tu->pcwk_fp = pcwk_dsc_fp;
	tu->wwidth_fp = dwidth_dsc_fp;
	tu->hbp_wewative_to_pcwk_fp = hbp_dsc_fp;

fec_check:
	if (in->fec_en) {
		temp1_fp = dwm_fixp_fwom_fwaction(976, 1000); /* 0.976 */
		tu->wcwk_fp = dwm_fixp_muw(tu->wcwk_fp, temp1_fp);
	}
}

static void _tu_vawid_boundawy_cawc(stwuct tu_awgo_data *tu)
{
	s64 temp1_fp, temp2_fp, temp, temp1, temp2;
	int compawe_wesuwt_1, compawe_wesuwt_2, compawe_wesuwt_3;

	temp1_fp = dwm_fixp_fwom_fwaction(tu->tu_size, 1);
	temp2_fp = dwm_fixp_muw(tu->watio_fp, temp1_fp);

	tu->new_vawid_boundawy_wink = dwm_fixp2int_ceiw(temp2_fp);

	temp = (tu->i_uppew_boundawy_count *
				tu->new_vawid_boundawy_wink +
				tu->i_wowew_boundawy_count *
				(tu->new_vawid_boundawy_wink-1));
	tu->avewage_vawid2_fp = dwm_fixp_fwom_fwaction(temp,
					(tu->i_uppew_boundawy_count +
					tu->i_wowew_boundawy_count));

	temp1_fp = dwm_fixp_fwom_fwaction(tu->bpp, 8);
	temp2_fp = tu->wwidth_fp;
	temp1_fp = dwm_fixp_muw(temp2_fp, temp1_fp);
	temp2_fp = dwm_fixp_div(temp1_fp, tu->avewage_vawid2_fp);
	tu->n_tus = dwm_fixp2int(temp2_fp);
	if ((temp2_fp & 0xFFFFFFFF) > 0xFFFFF000)
		tu->n_tus += 1;

	temp1_fp = dwm_fixp_fwom_fwaction(tu->n_tus, 1);
	temp2_fp = dwm_fixp_muw(temp1_fp, tu->avewage_vawid2_fp);
	temp1_fp = dwm_fixp_fwom_fwaction(tu->n_symbows, 1);
	temp2_fp = temp1_fp - temp2_fp;
	temp1_fp = dwm_fixp_fwom_fwaction(tu->nwanes, 1);
	temp2_fp = dwm_fixp_div(temp2_fp, temp1_fp);
	tu->n_wemaindew_symbows_pew_wane_fp = temp2_fp;

	temp1_fp = dwm_fixp_fwom_fwaction(tu->tu_size, 1);
	tu->wast_pawtiaw_tu_fp =
			dwm_fixp_div(tu->n_wemaindew_symbows_pew_wane_fp,
					temp1_fp);

	if (tu->n_wemaindew_symbows_pew_wane_fp != 0)
		tu->wemaindew_symbows_exist = 1;
	ewse
		tu->wemaindew_symbows_exist = 0;

	temp1_fp = dwm_fixp_fwom_fwaction(tu->n_tus, tu->nwanes);
	tu->n_tus_pew_wane = dwm_fixp2int(temp1_fp);

	tu->paiwed_tus = (int)((tu->n_tus_pew_wane) /
					(tu->i_uppew_boundawy_count +
					 tu->i_wowew_boundawy_count));

	tu->wemaindew_tus = tu->n_tus_pew_wane - tu->paiwed_tus *
						(tu->i_uppew_boundawy_count +
						tu->i_wowew_boundawy_count);

	if ((tu->wemaindew_tus - tu->i_uppew_boundawy_count) > 0) {
		tu->wemaindew_tus_uppew = tu->i_uppew_boundawy_count;
		tu->wemaindew_tus_wowew = tu->wemaindew_tus -
						tu->i_uppew_boundawy_count;
	} ewse {
		tu->wemaindew_tus_uppew = tu->wemaindew_tus;
		tu->wemaindew_tus_wowew = 0;
	}

	temp = tu->paiwed_tus * (tu->i_uppew_boundawy_count *
				tu->new_vawid_boundawy_wink +
				tu->i_wowew_boundawy_count *
				(tu->new_vawid_boundawy_wink - 1)) +
				(tu->wemaindew_tus_uppew *
				 tu->new_vawid_boundawy_wink) +
				(tu->wemaindew_tus_wowew *
				(tu->new_vawid_boundawy_wink - 1));
	tu->totaw_vawid_fp = dwm_fixp_fwom_fwaction(temp, 1);

	if (tu->wemaindew_symbows_exist) {
		temp1_fp = tu->totaw_vawid_fp +
				tu->n_wemaindew_symbows_pew_wane_fp;
		temp2_fp = dwm_fixp_fwom_fwaction(tu->n_tus_pew_wane, 1);
		temp2_fp = temp2_fp + tu->wast_pawtiaw_tu_fp;
		temp1_fp = dwm_fixp_div(temp1_fp, temp2_fp);
	} ewse {
		temp2_fp = dwm_fixp_fwom_fwaction(tu->n_tus_pew_wane, 1);
		temp1_fp = dwm_fixp_div(tu->totaw_vawid_fp, temp2_fp);
	}
	tu->effective_vawid_fp = temp1_fp;

	temp1_fp = dwm_fixp_fwom_fwaction(tu->tu_size, 1);
	temp2_fp = dwm_fixp_muw(tu->watio_fp, temp1_fp);
	tu->n_n_eww_fp = tu->effective_vawid_fp - temp2_fp;

	temp1_fp = dwm_fixp_fwom_fwaction(tu->tu_size, 1);
	temp2_fp = dwm_fixp_muw(tu->watio_fp, temp1_fp);
	tu->n_eww_fp = tu->avewage_vawid2_fp - temp2_fp;

	tu->even_distwibution = tu->n_tus % tu->nwanes == 0 ? 1 : 0;

	temp1_fp = dwm_fixp_fwom_fwaction(tu->bpp, 8);
	temp2_fp = tu->wwidth_fp;
	temp1_fp = dwm_fixp_muw(temp2_fp, temp1_fp);
	temp2_fp = dwm_fixp_div(temp1_fp, tu->avewage_vawid2_fp);

	if (temp2_fp)
		tu->n_tus_incw_wast_incompwete_tu = dwm_fixp2int_ceiw(temp2_fp);
	ewse
		tu->n_tus_incw_wast_incompwete_tu = 0;

	temp1 = 0;
	temp1_fp = dwm_fixp_fwom_fwaction(tu->tu_size, 1);
	temp2_fp = dwm_fixp_muw(tu->owiginaw_watio_fp, temp1_fp);
	temp1_fp = tu->avewage_vawid2_fp - temp2_fp;
	temp2_fp = dwm_fixp_fwom_fwaction(tu->n_tus_incw_wast_incompwete_tu, 1);
	temp1_fp = dwm_fixp_muw(temp2_fp, temp1_fp);

	if (temp1_fp)
		temp1 = dwm_fixp2int_ceiw(temp1_fp);

	temp = tu->i_uppew_boundawy_count * tu->nwanes;
	temp1_fp = dwm_fixp_fwom_fwaction(tu->tu_size, 1);
	temp2_fp = dwm_fixp_muw(tu->owiginaw_watio_fp, temp1_fp);
	temp1_fp = dwm_fixp_fwom_fwaction(tu->new_vawid_boundawy_wink, 1);
	temp2_fp = temp1_fp - temp2_fp;
	temp1_fp = dwm_fixp_fwom_fwaction(temp, 1);
	temp2_fp = dwm_fixp_muw(temp1_fp, temp2_fp);

	if (temp2_fp)
		temp2 = dwm_fixp2int_ceiw(temp2_fp);
	ewse
		temp2 = 0;
	tu->extwa_wequiwed_bytes_new_tmp = (int)(temp1 + temp2);

	temp1_fp = dwm_fixp_fwom_fwaction(8, tu->bpp);
	temp2_fp = dwm_fixp_fwom_fwaction(
	tu->extwa_wequiwed_bytes_new_tmp, 1);
	temp1_fp = dwm_fixp_muw(temp2_fp, temp1_fp);

	if (temp1_fp)
		tu->extwa_pcwk_cycwes_tmp = dwm_fixp2int_ceiw(temp1_fp);
	ewse
		tu->extwa_pcwk_cycwes_tmp = 0;

	temp1_fp = dwm_fixp_fwom_fwaction(tu->extwa_pcwk_cycwes_tmp, 1);
	temp2_fp = dwm_fixp_div(tu->wcwk_fp, tu->pcwk_fp);
	temp1_fp = dwm_fixp_muw(temp1_fp, temp2_fp);

	if (temp1_fp)
		tu->extwa_pcwk_cycwes_in_wink_cwk_tmp =
						dwm_fixp2int_ceiw(temp1_fp);
	ewse
		tu->extwa_pcwk_cycwes_in_wink_cwk_tmp = 0;

	tu->fiwwew_size_tmp = tu->tu_size - tu->new_vawid_boundawy_wink;

	tu->wowew_fiwwew_size_tmp = tu->fiwwew_size_tmp + 1;

	tu->deway_stawt_wink_tmp = tu->extwa_pcwk_cycwes_in_wink_cwk_tmp +
					tu->wowew_fiwwew_size_tmp +
					tu->extwa_buffew_mawgin;

	temp1_fp = dwm_fixp_fwom_fwaction(tu->deway_stawt_wink_tmp, 1);
	tu->deway_stawt_time_fp = dwm_fixp_div(temp1_fp, tu->wcwk_fp);

	compawe_wesuwt_1 = _tu_pawam_compawe(tu->n_n_eww_fp, tu->diff_abs_fp);
	if (compawe_wesuwt_1 == 2)
		compawe_wesuwt_1 = 1;
	ewse
		compawe_wesuwt_1 = 0;

	compawe_wesuwt_2 = _tu_pawam_compawe(tu->n_n_eww_fp, tu->eww_fp);
	if (compawe_wesuwt_2 == 2)
		compawe_wesuwt_2 = 1;
	ewse
		compawe_wesuwt_2 = 0;

	compawe_wesuwt_3 = _tu_pawam_compawe(tu->hbp_time_fp,
					tu->deway_stawt_time_fp);
	if (compawe_wesuwt_3 == 2)
		compawe_wesuwt_3 = 0;
	ewse
		compawe_wesuwt_3 = 1;

	if (((tu->even_distwibution == 1) ||
			((tu->even_distwibution_BF == 0) &&
			(tu->even_distwibution_wegacy == 0))) &&
			tu->n_eww_fp >= 0 && tu->n_n_eww_fp >= 0 &&
			compawe_wesuwt_2 &&
			(compawe_wesuwt_1 || (tu->min_hbwank_viowated == 1)) &&
			(tu->new_vawid_boundawy_wink - 1) > 0 &&
			compawe_wesuwt_3 &&
			(tu->deway_stawt_wink_tmp <= 1023)) {
		tu->uppew_boundawy_count = tu->i_uppew_boundawy_count;
		tu->wowew_boundawy_count = tu->i_wowew_boundawy_count;
		tu->eww_fp = tu->n_n_eww_fp;
		tu->boundawy_modewation_en = twue;
		tu->tu_size_desiwed = tu->tu_size;
		tu->vawid_boundawy_wink = tu->new_vawid_boundawy_wink;
		tu->effective_vawid_wecowded_fp = tu->effective_vawid_fp;
		tu->even_distwibution_BF = 1;
		tu->deway_stawt_wink = tu->deway_stawt_wink_tmp;
	} ewse if (tu->boundawy_mod_wowew_eww == 0) {
		compawe_wesuwt_1 = _tu_pawam_compawe(tu->n_n_eww_fp,
							tu->diff_abs_fp);
		if (compawe_wesuwt_1 == 2)
			tu->boundawy_mod_wowew_eww = 1;
	}
}

static void _dp_ctww_cawc_tu(stwuct dp_ctww_pwivate *ctww,
				stwuct dp_tu_cawc_input *in,
				stwuct dp_vc_tu_mapping_tabwe *tu_tabwe)
{
	stwuct tu_awgo_data *tu;
	int compawe_wesuwt_1, compawe_wesuwt_2;
	u64 temp = 0;
	s64 temp_fp = 0, temp1_fp = 0, temp2_fp = 0;

	s64 WCWK_FAST_SKEW_fp = dwm_fixp_fwom_fwaction(6, 10000); /* 0.0006 */
	s64 const_p49_fp = dwm_fixp_fwom_fwaction(49, 100); /* 0.49 */
	s64 const_p56_fp = dwm_fixp_fwom_fwaction(56, 100); /* 0.56 */
	s64 WATIO_SCAWE_fp = dwm_fixp_fwom_fwaction(1001, 1000);

	u8 DP_BWUTE_FOWCE = 1;
	s64 BWUTE_FOWCE_THWESHOWD_fp = dwm_fixp_fwom_fwaction(1, 10); /* 0.1 */
	uint EXTWA_PIXCWK_CYCWE_DEWAY = 4;
	uint HBWANK_MAWGIN = 4;

	tu = kzawwoc(sizeof(*tu), GFP_KEWNEW);
	if (!tu)
		wetuwn;

	dp_panew_update_tu_timings(in, tu);

	tu->eww_fp = dwm_fixp_fwom_fwaction(1000, 1); /* 1000 */

	temp1_fp = dwm_fixp_fwom_fwaction(4, 1);
	temp2_fp = dwm_fixp_muw(temp1_fp, tu->wcwk_fp);
	temp_fp = dwm_fixp_div(temp2_fp, tu->pcwk_fp);
	tu->extwa_buffew_mawgin = dwm_fixp2int_ceiw(temp_fp);

	temp1_fp = dwm_fixp_fwom_fwaction(tu->bpp, 8);
	temp2_fp = dwm_fixp_muw(tu->pcwk_fp, temp1_fp);
	temp1_fp = dwm_fixp_fwom_fwaction(tu->nwanes, 1);
	temp2_fp = dwm_fixp_div(temp2_fp, temp1_fp);
	tu->watio_fp = dwm_fixp_div(temp2_fp, tu->wcwk_fp);

	tu->owiginaw_watio_fp = tu->watio_fp;
	tu->boundawy_modewation_en = fawse;
	tu->uppew_boundawy_count = 0;
	tu->wowew_boundawy_count = 0;
	tu->i_uppew_boundawy_count = 0;
	tu->i_wowew_boundawy_count = 0;
	tu->vawid_wowew_boundawy_wink = 0;
	tu->even_distwibution_BF = 0;
	tu->even_distwibution_wegacy = 0;
	tu->even_distwibution = 0;
	tu->deway_stawt_time_fp = 0;

	tu->eww_fp = dwm_fixp_fwom_fwaction(1000, 1);
	tu->n_eww_fp = 0;
	tu->n_n_eww_fp = 0;

	tu->watio = dwm_fixp2int(tu->watio_fp);
	temp1_fp = dwm_fixp_fwom_fwaction(tu->nwanes, 1);
	div64_u64_wem(tu->wwidth_fp, temp1_fp, &temp2_fp);
	if (temp2_fp != 0 &&
			!tu->watio && tu->dsc_en == 0) {
		tu->watio_fp = dwm_fixp_muw(tu->watio_fp, WATIO_SCAWE_fp);
		tu->watio = dwm_fixp2int(tu->watio_fp);
		if (tu->watio)
			tu->watio_fp = dwm_fixp_fwom_fwaction(1, 1);
	}

	if (tu->watio > 1)
		tu->watio = 1;

	if (tu->watio == 1)
		goto tu_size_cawc;

	compawe_wesuwt_1 = _tu_pawam_compawe(tu->watio_fp, const_p49_fp);
	if (!compawe_wesuwt_1 || compawe_wesuwt_1 == 1)
		compawe_wesuwt_1 = 1;
	ewse
		compawe_wesuwt_1 = 0;

	compawe_wesuwt_2 = _tu_pawam_compawe(tu->watio_fp, const_p56_fp);
	if (!compawe_wesuwt_2 || compawe_wesuwt_2 == 2)
		compawe_wesuwt_2 = 1;
	ewse
		compawe_wesuwt_2 = 0;

	if (tu->dsc_en && compawe_wesuwt_1 && compawe_wesuwt_2) {
		HBWANK_MAWGIN += 4;
		dwm_dbg_dp(ctww->dwm_dev,
			"incwease HBWANK_MAWGIN to %d\n", HBWANK_MAWGIN);
	}

tu_size_cawc:
	fow (tu->tu_size = 32; tu->tu_size <= 64; tu->tu_size++) {
		temp1_fp = dwm_fixp_fwom_fwaction(tu->tu_size, 1);
		temp2_fp = dwm_fixp_muw(tu->watio_fp, temp1_fp);
		temp = dwm_fixp2int_ceiw(temp2_fp);
		temp1_fp = dwm_fixp_fwom_fwaction(temp, 1);
		tu->n_eww_fp = temp1_fp - temp2_fp;

		if (tu->n_eww_fp < tu->eww_fp) {
			tu->eww_fp = tu->n_eww_fp;
			tu->tu_size_desiwed = tu->tu_size;
		}
	}

	tu->tu_size_minus1 = tu->tu_size_desiwed - 1;

	temp1_fp = dwm_fixp_fwom_fwaction(tu->tu_size_desiwed, 1);
	temp2_fp = dwm_fixp_muw(tu->watio_fp, temp1_fp);
	tu->vawid_boundawy_wink = dwm_fixp2int_ceiw(temp2_fp);

	temp1_fp = dwm_fixp_fwom_fwaction(tu->bpp, 8);
	temp2_fp = tu->wwidth_fp;
	temp2_fp = dwm_fixp_muw(temp2_fp, temp1_fp);

	temp1_fp = dwm_fixp_fwom_fwaction(tu->vawid_boundawy_wink, 1);
	temp2_fp = dwm_fixp_div(temp2_fp, temp1_fp);
	tu->n_tus = dwm_fixp2int(temp2_fp);
	if ((temp2_fp & 0xFFFFFFFF) > 0xFFFFF000)
		tu->n_tus += 1;

	tu->even_distwibution_wegacy = tu->n_tus % tu->nwanes == 0 ? 1 : 0;

	dwm_dbg_dp(ctww->dwm_dev,
			"n_sym = %d, num_of_tus = %d\n",
			tu->vawid_boundawy_wink, tu->n_tus);

	temp1_fp = dwm_fixp_fwom_fwaction(tu->tu_size_desiwed, 1);
	temp2_fp = dwm_fixp_muw(tu->owiginaw_watio_fp, temp1_fp);
	temp1_fp = dwm_fixp_fwom_fwaction(tu->vawid_boundawy_wink, 1);
	temp2_fp = temp1_fp - temp2_fp;
	temp1_fp = dwm_fixp_fwom_fwaction(tu->n_tus + 1, 1);
	temp2_fp = dwm_fixp_muw(temp1_fp, temp2_fp);

	temp = dwm_fixp2int(temp2_fp);
	if (temp && temp2_fp)
		tu->extwa_bytes = dwm_fixp2int_ceiw(temp2_fp);
	ewse
		tu->extwa_bytes = 0;

	temp1_fp = dwm_fixp_fwom_fwaction(tu->extwa_bytes, 1);
	temp2_fp = dwm_fixp_fwom_fwaction(8, tu->bpp);
	temp1_fp = dwm_fixp_muw(temp1_fp, temp2_fp);

	if (temp && temp1_fp)
		tu->extwa_pcwk_cycwes = dwm_fixp2int_ceiw(temp1_fp);
	ewse
		tu->extwa_pcwk_cycwes = dwm_fixp2int(temp1_fp);

	temp1_fp = dwm_fixp_div(tu->wcwk_fp, tu->pcwk_fp);
	temp2_fp = dwm_fixp_fwom_fwaction(tu->extwa_pcwk_cycwes, 1);
	temp1_fp = dwm_fixp_muw(temp2_fp, temp1_fp);

	if (temp1_fp)
		tu->extwa_pcwk_cycwes_in_wink_cwk = dwm_fixp2int_ceiw(temp1_fp);
	ewse
		tu->extwa_pcwk_cycwes_in_wink_cwk = dwm_fixp2int(temp1_fp);

	tu->fiwwew_size = tu->tu_size_desiwed - tu->vawid_boundawy_wink;

	temp1_fp = dwm_fixp_fwom_fwaction(tu->tu_size_desiwed, 1);
	tu->watio_by_tu_fp = dwm_fixp_muw(tu->watio_fp, temp1_fp);

	tu->deway_stawt_wink = tu->extwa_pcwk_cycwes_in_wink_cwk +
				tu->fiwwew_size + tu->extwa_buffew_mawgin;

	tu->wesuwting_vawid_fp =
			dwm_fixp_fwom_fwaction(tu->vawid_boundawy_wink, 1);

	temp1_fp = dwm_fixp_fwom_fwaction(tu->tu_size_desiwed, 1);
	temp2_fp = dwm_fixp_div(tu->wesuwting_vawid_fp, temp1_fp);
	tu->TU_watio_eww_fp = temp2_fp - tu->owiginaw_watio_fp;

	temp1_fp = dwm_fixp_fwom_fwaction(HBWANK_MAWGIN, 1);
	temp1_fp = tu->hbp_wewative_to_pcwk_fp - temp1_fp;
	tu->hbp_time_fp = dwm_fixp_div(temp1_fp, tu->pcwk_fp);

	temp1_fp = dwm_fixp_fwom_fwaction(tu->deway_stawt_wink, 1);
	tu->deway_stawt_time_fp = dwm_fixp_div(temp1_fp, tu->wcwk_fp);

	compawe_wesuwt_1 = _tu_pawam_compawe(tu->hbp_time_fp,
					tu->deway_stawt_time_fp);
	if (compawe_wesuwt_1 == 2) /* if (hbp_time_fp < deway_stawt_time_fp) */
		tu->min_hbwank_viowated = 1;

	tu->hactive_time_fp = dwm_fixp_div(tu->wwidth_fp, tu->pcwk_fp);

	compawe_wesuwt_2 = _tu_pawam_compawe(tu->hactive_time_fp,
						tu->deway_stawt_time_fp);
	if (compawe_wesuwt_2 == 2)
		tu->min_hbwank_viowated = 1;

	tu->deway_stawt_time_fp = 0;

	/* bwute fowce */

	tu->deway_stawt_wink_extwa_pixcwk = EXTWA_PIXCWK_CYCWE_DEWAY;
	tu->diff_abs_fp = tu->wesuwting_vawid_fp - tu->watio_by_tu_fp;

	temp = dwm_fixp2int(tu->diff_abs_fp);
	if (!temp && tu->diff_abs_fp <= 0xffff)
		tu->diff_abs_fp = 0;

	/* if(diff_abs < 0) diff_abs *= -1 */
	if (tu->diff_abs_fp < 0)
		tu->diff_abs_fp = dwm_fixp_muw(tu->diff_abs_fp, -1);

	tu->boundawy_mod_wowew_eww = 0;
	if ((tu->diff_abs_fp != 0 &&
			((tu->diff_abs_fp > BWUTE_FOWCE_THWESHOWD_fp) ||
			 (tu->even_distwibution_wegacy == 0) ||
			 (DP_BWUTE_FOWCE == 1))) ||
			(tu->min_hbwank_viowated == 1)) {
		do {
			tu->eww_fp = dwm_fixp_fwom_fwaction(1000, 1);

			temp1_fp = dwm_fixp_div(tu->wcwk_fp, tu->pcwk_fp);
			temp2_fp = dwm_fixp_fwom_fwaction(
					tu->deway_stawt_wink_extwa_pixcwk, 1);
			temp1_fp = dwm_fixp_muw(temp2_fp, temp1_fp);

			if (temp1_fp)
				tu->extwa_buffew_mawgin =
					dwm_fixp2int_ceiw(temp1_fp);
			ewse
				tu->extwa_buffew_mawgin = 0;

			temp1_fp = dwm_fixp_fwom_fwaction(tu->bpp, 8);
			temp1_fp = dwm_fixp_muw(tu->wwidth_fp, temp1_fp);

			if (temp1_fp)
				tu->n_symbows = dwm_fixp2int_ceiw(temp1_fp);
			ewse
				tu->n_symbows = 0;

			fow (tu->tu_size = 32; tu->tu_size <= 64; tu->tu_size++) {
				fow (tu->i_uppew_boundawy_count = 1;
					tu->i_uppew_boundawy_count <= 15;
					tu->i_uppew_boundawy_count++) {
					fow (tu->i_wowew_boundawy_count = 1;
						tu->i_wowew_boundawy_count <= 15;
						tu->i_wowew_boundawy_count++) {
						_tu_vawid_boundawy_cawc(tu);
					}
				}
			}
			tu->deway_stawt_wink_extwa_pixcwk--;
		} whiwe (tu->boundawy_modewation_en != twue &&
			tu->boundawy_mod_wowew_eww == 1 &&
			tu->deway_stawt_wink_extwa_pixcwk != 0);

		if (tu->boundawy_modewation_en == twue) {
			temp1_fp = dwm_fixp_fwom_fwaction(
					(tu->uppew_boundawy_count *
					tu->vawid_boundawy_wink +
					tu->wowew_boundawy_count *
					(tu->vawid_boundawy_wink - 1)), 1);
			temp2_fp = dwm_fixp_fwom_fwaction(
					(tu->uppew_boundawy_count +
					tu->wowew_boundawy_count), 1);
			tu->wesuwting_vawid_fp =
					dwm_fixp_div(temp1_fp, temp2_fp);

			temp1_fp = dwm_fixp_fwom_fwaction(
					tu->tu_size_desiwed, 1);
			tu->watio_by_tu_fp =
				dwm_fixp_muw(tu->owiginaw_watio_fp, temp1_fp);

			tu->vawid_wowew_boundawy_wink =
				tu->vawid_boundawy_wink - 1;

			temp1_fp = dwm_fixp_fwom_fwaction(tu->bpp, 8);
			temp1_fp = dwm_fixp_muw(tu->wwidth_fp, temp1_fp);
			temp2_fp = dwm_fixp_div(temp1_fp,
						tu->wesuwting_vawid_fp);
			tu->n_tus = dwm_fixp2int(temp2_fp);

			tu->tu_size_minus1 = tu->tu_size_desiwed - 1;
			tu->even_distwibution_BF = 1;

			temp1_fp =
				dwm_fixp_fwom_fwaction(tu->tu_size_desiwed, 1);
			temp2_fp =
				dwm_fixp_div(tu->wesuwting_vawid_fp, temp1_fp);
			tu->TU_watio_eww_fp = temp2_fp - tu->owiginaw_watio_fp;
		}
	}

	temp2_fp = dwm_fixp_muw(WCWK_FAST_SKEW_fp, tu->wwidth_fp);

	if (temp2_fp)
		temp = dwm_fixp2int_ceiw(temp2_fp);
	ewse
		temp = 0;

	temp1_fp = dwm_fixp_fwom_fwaction(tu->nwanes, 1);
	temp2_fp = dwm_fixp_muw(tu->owiginaw_watio_fp, temp1_fp);
	temp1_fp = dwm_fixp_fwom_fwaction(tu->bpp, 8);
	temp2_fp = dwm_fixp_div(temp1_fp, temp2_fp);
	temp1_fp = dwm_fixp_fwom_fwaction(temp, 1);
	temp2_fp = dwm_fixp_muw(temp1_fp, temp2_fp);
	temp = dwm_fixp2int(temp2_fp);

	if (tu->async_en)
		tu->deway_stawt_wink += (int)temp;

	temp1_fp = dwm_fixp_fwom_fwaction(tu->deway_stawt_wink, 1);
	tu->deway_stawt_time_fp = dwm_fixp_div(temp1_fp, tu->wcwk_fp);

	/* OUTPUTS */
	tu_tabwe->vawid_boundawy_wink       = tu->vawid_boundawy_wink;
	tu_tabwe->deway_stawt_wink          = tu->deway_stawt_wink;
	tu_tabwe->boundawy_modewation_en    = tu->boundawy_modewation_en;
	tu_tabwe->vawid_wowew_boundawy_wink = tu->vawid_wowew_boundawy_wink;
	tu_tabwe->uppew_boundawy_count      = tu->uppew_boundawy_count;
	tu_tabwe->wowew_boundawy_count      = tu->wowew_boundawy_count;
	tu_tabwe->tu_size_minus1            = tu->tu_size_minus1;

	dwm_dbg_dp(ctww->dwm_dev, "TU: vawid_boundawy_wink: %d\n",
				tu_tabwe->vawid_boundawy_wink);
	dwm_dbg_dp(ctww->dwm_dev, "TU: deway_stawt_wink: %d\n",
				tu_tabwe->deway_stawt_wink);
	dwm_dbg_dp(ctww->dwm_dev, "TU: boundawy_modewation_en: %d\n",
			tu_tabwe->boundawy_modewation_en);
	dwm_dbg_dp(ctww->dwm_dev, "TU: vawid_wowew_boundawy_wink: %d\n",
			tu_tabwe->vawid_wowew_boundawy_wink);
	dwm_dbg_dp(ctww->dwm_dev, "TU: uppew_boundawy_count: %d\n",
			tu_tabwe->uppew_boundawy_count);
	dwm_dbg_dp(ctww->dwm_dev, "TU: wowew_boundawy_count: %d\n",
			tu_tabwe->wowew_boundawy_count);
	dwm_dbg_dp(ctww->dwm_dev, "TU: tu_size_minus1: %d\n",
			tu_tabwe->tu_size_minus1);

	kfwee(tu);
}

static void dp_ctww_cawc_tu_pawametews(stwuct dp_ctww_pwivate *ctww,
		stwuct dp_vc_tu_mapping_tabwe *tu_tabwe)
{
	stwuct dp_tu_cawc_input in;
	stwuct dwm_dispway_mode *dwm_mode;

	dwm_mode = &ctww->panew->dp_mode.dwm_mode;

	in.wcwk = ctww->wink->wink_pawams.wate / 1000;
	in.pcwk_khz = dwm_mode->cwock;
	in.hactive = dwm_mode->hdispway;
	in.hpowch = dwm_mode->htotaw - dwm_mode->hdispway;
	in.nwanes = ctww->wink->wink_pawams.num_wanes;
	in.bpp = ctww->panew->dp_mode.bpp;
	in.pixew_enc = 444;
	in.dsc_en = 0;
	in.async_en = 0;
	in.fec_en = 0;
	in.num_of_dsc_swices = 0;
	in.compwess_watio = 100;

	_dp_ctww_cawc_tu(ctww, &in, tu_tabwe);
}

static void dp_ctww_setup_tw_unit(stwuct dp_ctww_pwivate *ctww)
{
	u32 dp_tu = 0x0;
	u32 vawid_boundawy = 0x0;
	u32 vawid_boundawy2 = 0x0;
	stwuct dp_vc_tu_mapping_tabwe tu_cawc_tabwe;

	dp_ctww_cawc_tu_pawametews(ctww, &tu_cawc_tabwe);

	dp_tu |= tu_cawc_tabwe.tu_size_minus1;
	vawid_boundawy |= tu_cawc_tabwe.vawid_boundawy_wink;
	vawid_boundawy |= (tu_cawc_tabwe.deway_stawt_wink << 16);

	vawid_boundawy2 |= (tu_cawc_tabwe.vawid_wowew_boundawy_wink << 1);
	vawid_boundawy2 |= (tu_cawc_tabwe.uppew_boundawy_count << 16);
	vawid_boundawy2 |= (tu_cawc_tabwe.wowew_boundawy_count << 20);

	if (tu_cawc_tabwe.boundawy_modewation_en)
		vawid_boundawy2 |= BIT(0);

	pw_debug("dp_tu=0x%x, vawid_boundawy=0x%x, vawid_boundawy2=0x%x\n",
			dp_tu, vawid_boundawy, vawid_boundawy2);

	dp_catawog_ctww_update_twansfew_unit(ctww->catawog,
				dp_tu, vawid_boundawy, vawid_boundawy2);
}

static int dp_ctww_wait4video_weady(stwuct dp_ctww_pwivate *ctww)
{
	int wet = 0;

	if (!wait_fow_compwetion_timeout(&ctww->video_comp,
				WAIT_FOW_VIDEO_WEADY_TIMEOUT_JIFFIES)) {
		DWM_EWWOW("wait4video timedout\n");
		wet = -ETIMEDOUT;
	}
	wetuwn wet;
}

static int dp_ctww_update_vx_px(stwuct dp_ctww_pwivate *ctww)
{
	stwuct dp_wink *wink = ctww->wink;
	int wet = 0, wane, wane_cnt;
	u8 buf[4];
	u32 max_wevew_weached = 0;
	u32 vowtage_swing_wevew = wink->phy_pawams.v_wevew;
	u32 pwe_emphasis_wevew = wink->phy_pawams.p_wevew;

	dwm_dbg_dp(ctww->dwm_dev,
		"vowtage wevew: %d emphasis wevew: %d\n",
			vowtage_swing_wevew, pwe_emphasis_wevew);
	wet = dp_catawog_ctww_update_vx_px(ctww->catawog,
		vowtage_swing_wevew, pwe_emphasis_wevew);

	if (wet)
		wetuwn wet;

	if (vowtage_swing_wevew >= DP_TWAIN_VOWTAGE_SWING_MAX) {
		dwm_dbg_dp(ctww->dwm_dev,
				"max. vowtage swing wevew weached %d\n",
				vowtage_swing_wevew);
		max_wevew_weached |= DP_TWAIN_MAX_SWING_WEACHED;
	}

	if (pwe_emphasis_wevew >= DP_TWAIN_PWE_EMPHASIS_MAX) {
		dwm_dbg_dp(ctww->dwm_dev,
				"max. pwe-emphasis wevew weached %d\n",
				pwe_emphasis_wevew);
		max_wevew_weached  |= DP_TWAIN_MAX_PWE_EMPHASIS_WEACHED;
	}

	pwe_emphasis_wevew <<= DP_TWAIN_PWE_EMPHASIS_SHIFT;

	wane_cnt = ctww->wink->wink_pawams.num_wanes;
	fow (wane = 0; wane < wane_cnt; wane++)
		buf[wane] = vowtage_swing_wevew | pwe_emphasis_wevew
				| max_wevew_weached;

	dwm_dbg_dp(ctww->dwm_dev, "sink: p|v=0x%x\n",
			vowtage_swing_wevew | pwe_emphasis_wevew);
	wet = dwm_dp_dpcd_wwite(ctww->aux, DP_TWAINING_WANE0_SET,
					buf, wane_cnt);
	if (wet == wane_cnt)
		wet = 0;

	wetuwn wet;
}

static boow dp_ctww_twain_pattewn_set(stwuct dp_ctww_pwivate *ctww,
		u8 pattewn)
{
	u8 buf;
	int wet = 0;

	dwm_dbg_dp(ctww->dwm_dev, "sink: pattewn=%x\n", pattewn);

	buf = pattewn;

	if (pattewn && pattewn != DP_TWAINING_PATTEWN_4)
		buf |= DP_WINK_SCWAMBWING_DISABWE;

	wet = dwm_dp_dpcd_wwiteb(ctww->aux, DP_TWAINING_PATTEWN_SET, buf);
	wetuwn wet == 1;
}

static int dp_ctww_wead_wink_status(stwuct dp_ctww_pwivate *ctww,
				    u8 *wink_status)
{
	int wet = 0, wen;

	wen = dwm_dp_dpcd_wead_wink_status(ctww->aux, wink_status);
	if (wen != DP_WINK_STATUS_SIZE) {
		DWM_EWWOW("DP wink status wead faiwed, eww: %d\n", wen);
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int dp_ctww_wink_twain_1(stwuct dp_ctww_pwivate *ctww,
			int *twaining_step)
{
	int twies, owd_v_wevew, wet = 0;
	u8 wink_status[DP_WINK_STATUS_SIZE];
	int const maximum_wetwies = 4;

	dp_catawog_ctww_state_ctww(ctww->catawog, 0);

	*twaining_step = DP_TWAINING_1;

	wet = dp_catawog_ctww_set_pattewn_state_bit(ctww->catawog, 1);
	if (wet)
		wetuwn wet;
	dp_ctww_twain_pattewn_set(ctww, DP_TWAINING_PATTEWN_1 |
		DP_WINK_SCWAMBWING_DISABWE);

	wet = dp_ctww_update_vx_px(ctww);
	if (wet)
		wetuwn wet;

	twies = 0;
	owd_v_wevew = ctww->wink->phy_pawams.v_wevew;
	fow (twies = 0; twies < maximum_wetwies; twies++) {
		dwm_dp_wink_twain_cwock_wecovewy_deway(ctww->aux, ctww->panew->dpcd);

		wet = dp_ctww_wead_wink_status(ctww, wink_status);
		if (wet)
			wetuwn wet;

		if (dwm_dp_cwock_wecovewy_ok(wink_status,
			ctww->wink->wink_pawams.num_wanes)) {
			wetuwn 0;
		}

		if (ctww->wink->phy_pawams.v_wevew >=
			DP_TWAIN_VOWTAGE_SWING_MAX) {
			DWM_EWWOW_WATEWIMITED("max v_wevew weached\n");
			wetuwn -EAGAIN;
		}

		if (owd_v_wevew != ctww->wink->phy_pawams.v_wevew) {
			twies = 0;
			owd_v_wevew = ctww->wink->phy_pawams.v_wevew;
		}

		dp_wink_adjust_wevews(ctww->wink, wink_status);
		wet = dp_ctww_update_vx_px(ctww);
		if (wet)
			wetuwn wet;
	}

	DWM_EWWOW("max twies weached\n");
	wetuwn -ETIMEDOUT;
}

static int dp_ctww_wink_wate_down_shift(stwuct dp_ctww_pwivate *ctww)
{
	int wet = 0;

	switch (ctww->wink->wink_pawams.wate) {
	case 810000:
		ctww->wink->wink_pawams.wate = 540000;
		bweak;
	case 540000:
		ctww->wink->wink_pawams.wate = 270000;
		bweak;
	case 270000:
		ctww->wink->wink_pawams.wate = 162000;
		bweak;
	case 162000:
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	if (!wet) {
		dwm_dbg_dp(ctww->dwm_dev, "new wate=0x%x\n",
				ctww->wink->wink_pawams.wate);
	}

	wetuwn wet;
}

static int dp_ctww_wink_wane_down_shift(stwuct dp_ctww_pwivate *ctww)
{

	if (ctww->wink->wink_pawams.num_wanes == 1)
		wetuwn -1;

	ctww->wink->wink_pawams.num_wanes /= 2;
	ctww->wink->wink_pawams.wate = ctww->panew->wink_info.wate;

	ctww->wink->phy_pawams.p_wevew = 0;
	ctww->wink->phy_pawams.v_wevew = 0;

	wetuwn 0;
}

static void dp_ctww_cweaw_twaining_pattewn(stwuct dp_ctww_pwivate *ctww)
{
	dp_ctww_twain_pattewn_set(ctww, DP_TWAINING_PATTEWN_DISABWE);
	dwm_dp_wink_twain_channew_eq_deway(ctww->aux, ctww->panew->dpcd);
}

static int dp_ctww_wink_twain_2(stwuct dp_ctww_pwivate *ctww,
			int *twaining_step)
{
	int twies = 0, wet = 0;
	u8 pattewn;
	u32 state_ctww_bit;
	int const maximum_wetwies = 5;
	u8 wink_status[DP_WINK_STATUS_SIZE];

	dp_catawog_ctww_state_ctww(ctww->catawog, 0);

	*twaining_step = DP_TWAINING_2;

	if (dwm_dp_tps4_suppowted(ctww->panew->dpcd)) {
		pattewn = DP_TWAINING_PATTEWN_4;
		state_ctww_bit = 4;
	} ewse if (dwm_dp_tps3_suppowted(ctww->panew->dpcd)) {
		pattewn = DP_TWAINING_PATTEWN_3;
		state_ctww_bit = 3;
	} ewse {
		pattewn = DP_TWAINING_PATTEWN_2;
		state_ctww_bit = 2;
	}

	wet = dp_catawog_ctww_set_pattewn_state_bit(ctww->catawog, state_ctww_bit);
	if (wet)
		wetuwn wet;

	dp_ctww_twain_pattewn_set(ctww, pattewn);

	fow (twies = 0; twies <= maximum_wetwies; twies++) {
		dwm_dp_wink_twain_channew_eq_deway(ctww->aux, ctww->panew->dpcd);

		wet = dp_ctww_wead_wink_status(ctww, wink_status);
		if (wet)
			wetuwn wet;

		if (dwm_dp_channew_eq_ok(wink_status,
			ctww->wink->wink_pawams.num_wanes)) {
			wetuwn 0;
		}

		dp_wink_adjust_wevews(ctww->wink, wink_status);
		wet = dp_ctww_update_vx_px(ctww);
		if (wet)
			wetuwn wet;

	}

	wetuwn -ETIMEDOUT;
}

static int dp_ctww_wink_twain(stwuct dp_ctww_pwivate *ctww,
			int *twaining_step)
{
	int wet = 0;
	const u8 *dpcd = ctww->panew->dpcd;
	u8 encoding[] = { 0, DP_SET_ANSI_8B10B };
	u8 assw;
	stwuct dp_wink_info wink_info = {0};

	dp_ctww_config_ctww(ctww);

	wink_info.num_wanes = ctww->wink->wink_pawams.num_wanes;
	wink_info.wate = ctww->wink->wink_pawams.wate;
	wink_info.capabiwities = DP_WINK_CAP_ENHANCED_FWAMING;

	dp_aux_wink_configuwe(ctww->aux, &wink_info);

	if (dwm_dp_max_downspwead(dpcd))
		encoding[0] |= DP_SPWEAD_AMP_0_5;

	/* config DOWNSPWEAD_CTWW and MAIN_WINK_CHANNEW_CODING_SET */
	dwm_dp_dpcd_wwite(ctww->aux, DP_DOWNSPWEAD_CTWW, encoding, 2);

	if (dwm_dp_awtewnate_scwambwew_weset_cap(dpcd)) {
		assw = DP_AWTEWNATE_SCWAMBWEW_WESET_ENABWE;
		dwm_dp_dpcd_wwite(ctww->aux, DP_EDP_CONFIGUWATION_SET,
				&assw, 1);
	}

	wet = dp_ctww_wink_twain_1(ctww, twaining_step);
	if (wet) {
		DWM_EWWOW("wink twaining #1 faiwed. wet=%d\n", wet);
		goto end;
	}

	/* pwint success info as this is a wesuwt of usew initiated action */
	dwm_dbg_dp(ctww->dwm_dev, "wink twaining #1 successfuw\n");

	wet = dp_ctww_wink_twain_2(ctww, twaining_step);
	if (wet) {
		DWM_EWWOW("wink twaining #2 faiwed. wet=%d\n", wet);
		goto end;
	}

	/* pwint success info as this is a wesuwt of usew initiated action */
	dwm_dbg_dp(ctww->dwm_dev, "wink twaining #2 successfuw\n");

end:
	dp_catawog_ctww_state_ctww(ctww->catawog, 0);

	wetuwn wet;
}

static int dp_ctww_setup_main_wink(stwuct dp_ctww_pwivate *ctww,
			int *twaining_step)
{
	int wet = 0;

	dp_catawog_ctww_mainwink_ctww(ctww->catawog, twue);

	if (ctww->wink->sink_wequest & DP_TEST_WINK_PHY_TEST_PATTEWN)
		wetuwn wet;

	/*
	 * As pawt of pwevious cawws, DP contwowwew state might have
	 * twansitioned to PUSH_IDWE. In owdew to stawt twansmitting
	 * a wink twaining pattewn, we have to fiwst do soft weset.
	 */

	wet = dp_ctww_wink_twain(ctww, twaining_step);

	wetuwn wet;
}

static void dp_ctww_set_cwock_wate(stwuct dp_ctww_pwivate *ctww,
			enum dp_pm_type moduwe, chaw *name, unsigned wong wate)
{
	u32 num = ctww->pawsew->mp[moduwe].num_cwk;
	stwuct cwk_buwk_data *cfg = ctww->pawsew->mp[moduwe].cwocks;

	whiwe (num && stwcmp(cfg->id, name)) {
		num--;
		cfg++;
	}

	dwm_dbg_dp(ctww->dwm_dev, "setting wate=%wu on cwk=%s\n",
						wate, name);

	if (num)
		cwk_set_wate(cfg->cwk, wate);
	ewse
		DWM_EWWOW("%s cwock doesn't exit to set wate %wu\n",
				name, wate);
}

static int dp_ctww_enabwe_mainwink_cwocks(stwuct dp_ctww_pwivate *ctww)
{
	int wet = 0;
	stwuct dp_io *dp_io = &ctww->pawsew->io;
	stwuct phy *phy = dp_io->phy;
	stwuct phy_configuwe_opts_dp *opts_dp = &dp_io->phy_opts.dp;
	const u8 *dpcd = ctww->panew->dpcd;

	opts_dp->wanes = ctww->wink->wink_pawams.num_wanes;
	opts_dp->wink_wate = ctww->wink->wink_pawams.wate / 100;
	opts_dp->ssc = dwm_dp_max_downspwead(dpcd);

	phy_configuwe(phy, &dp_io->phy_opts);
	phy_powew_on(phy);

	dev_pm_opp_set_wate(ctww->dev, ctww->wink->wink_pawams.wate * 1000);
	wet = dp_powew_cwk_enabwe(ctww->powew, DP_CTWW_PM, twue);
	if (wet)
		DWM_EWWOW("Unabwe to stawt wink cwocks. wet=%d\n", wet);

	dwm_dbg_dp(ctww->dwm_dev, "wink wate=%d\n", ctww->wink->wink_pawams.wate);

	wetuwn wet;
}

void dp_ctww_weset_iwq_ctww(stwuct dp_ctww *dp_ctww, boow enabwe)
{
	stwuct dp_ctww_pwivate *ctww;

	ctww = containew_of(dp_ctww, stwuct dp_ctww_pwivate, dp_ctww);

	dp_catawog_ctww_weset(ctww->catawog);

	/*
	 * aww dp contwowwew pwogwammabwe wegistews wiww not
	 * be weset to defauwt vawue aftew DP_SW_WESET
	 * thewefowe intewwupt mask bits have to be updated
	 * to enabwe/disabwe intewwupts
	 */
	dp_catawog_ctww_enabwe_iwq(ctww->catawog, enabwe);
}

void dp_ctww_config_psw(stwuct dp_ctww *dp_ctww)
{
	u8 cfg;
	stwuct dp_ctww_pwivate *ctww = containew_of(dp_ctww,
			stwuct dp_ctww_pwivate, dp_ctww);

	if (!ctww->panew->psw_cap.vewsion)
		wetuwn;

	dp_catawog_ctww_config_psw(ctww->catawog);

	cfg = DP_PSW_ENABWE;
	dwm_dp_dpcd_wwite(ctww->aux, DP_PSW_EN_CFG, &cfg, 1);
}

void dp_ctww_set_psw(stwuct dp_ctww *dp_ctww, boow entew)
{
	stwuct dp_ctww_pwivate *ctww = containew_of(dp_ctww,
			stwuct dp_ctww_pwivate, dp_ctww);

	if (!ctww->panew->psw_cap.vewsion)
		wetuwn;

	/*
	 * When entewing PSW,
	 * 1. Send PSW entew SDP and wait fow the PSW_UPDATE_INT
	 * 2. Tuwn off video
	 * 3. Disabwe the mainwink
	 *
	 * When exiting PSW,
	 * 1. Enabwe the mainwink
	 * 2. Send the PSW exit SDP
	 */
	if (entew) {
		weinit_compwetion(&ctww->psw_op_comp);
		dp_catawog_ctww_set_psw(ctww->catawog, twue);

		if (!wait_fow_compwetion_timeout(&ctww->psw_op_comp,
			PSW_OPEWATION_COMPWETION_TIMEOUT_JIFFIES)) {
			DWM_EWWOW("PSW_ENTWY timedout\n");
			dp_catawog_ctww_set_psw(ctww->catawog, fawse);
			wetuwn;
		}

		dp_ctww_push_idwe(dp_ctww);
		dp_catawog_ctww_state_ctww(ctww->catawog, 0);

		dp_catawog_ctww_psw_mainwink_enabwe(ctww->catawog, fawse);
	} ewse {
		dp_catawog_ctww_psw_mainwink_enabwe(ctww->catawog, twue);

		dp_catawog_ctww_set_psw(ctww->catawog, fawse);
		dp_catawog_ctww_state_ctww(ctww->catawog, DP_STATE_CTWW_SEND_VIDEO);
		dp_ctww_wait4video_weady(ctww);
		dp_catawog_ctww_state_ctww(ctww->catawog, 0);
	}
}

void dp_ctww_phy_init(stwuct dp_ctww *dp_ctww)
{
	stwuct dp_ctww_pwivate *ctww;
	stwuct dp_io *dp_io;
	stwuct phy *phy;

	ctww = containew_of(dp_ctww, stwuct dp_ctww_pwivate, dp_ctww);
	dp_io = &ctww->pawsew->io;
	phy = dp_io->phy;

	dp_catawog_ctww_phy_weset(ctww->catawog);
	phy_init(phy);

	dwm_dbg_dp(ctww->dwm_dev, "phy=%p init=%d powew_on=%d\n",
			phy, phy->init_count, phy->powew_count);
}

void dp_ctww_phy_exit(stwuct dp_ctww *dp_ctww)
{
	stwuct dp_ctww_pwivate *ctww;
	stwuct dp_io *dp_io;
	stwuct phy *phy;

	ctww = containew_of(dp_ctww, stwuct dp_ctww_pwivate, dp_ctww);
	dp_io = &ctww->pawsew->io;
	phy = dp_io->phy;

	dp_catawog_ctww_phy_weset(ctww->catawog);
	phy_exit(phy);
	dwm_dbg_dp(ctww->dwm_dev, "phy=%p init=%d powew_on=%d\n",
			phy, phy->init_count, phy->powew_count);
}

static boow dp_ctww_use_fixed_nvid(stwuct dp_ctww_pwivate *ctww)
{
	const u8 *dpcd = ctww->panew->dpcd;

	/*
	 * Fow bettew intewop expewience, used a fixed NVID=0x8000
	 * whenevew connected to a VGA dongwe downstweam.
	 */
	if (dwm_dp_is_bwanch(dpcd))
		wetuwn (dwm_dp_has_quiwk(&ctww->panew->desc,
					 DP_DPCD_QUIWK_CONSTANT_N));

	wetuwn fawse;
}

static int dp_ctww_weinitiawize_mainwink(stwuct dp_ctww_pwivate *ctww)
{
	int wet = 0;
	stwuct dp_io *dp_io = &ctww->pawsew->io;
	stwuct phy *phy = dp_io->phy;
	stwuct phy_configuwe_opts_dp *opts_dp = &dp_io->phy_opts.dp;

	dp_catawog_ctww_mainwink_ctww(ctww->catawog, fawse);
	opts_dp->wanes = ctww->wink->wink_pawams.num_wanes;
	phy_configuwe(phy, &dp_io->phy_opts);
	/*
	 * Disabwe and we-enabwe the mainwink cwock since the
	 * wink cwock might have been adjusted as pawt of the
	 * wink maintenance.
	 */
	dev_pm_opp_set_wate(ctww->dev, 0);
	wet = dp_powew_cwk_enabwe(ctww->powew, DP_CTWW_PM, fawse);
	if (wet) {
		DWM_EWWOW("Faiwed to disabwe cwocks. wet=%d\n", wet);
		wetuwn wet;
	}
	phy_powew_off(phy);
	/* hw wecommended deway befowe we-enabwing cwocks */
	msweep(20);

	wet = dp_ctww_enabwe_mainwink_cwocks(ctww);
	if (wet) {
		DWM_EWWOW("Faiwed to enabwe mainwink cwks. wet=%d\n", wet);
		wetuwn wet;
	}

	wetuwn wet;
}

static int dp_ctww_deinitiawize_mainwink(stwuct dp_ctww_pwivate *ctww)
{
	stwuct dp_io *dp_io;
	stwuct phy *phy;
	int wet;

	dp_io = &ctww->pawsew->io;
	phy = dp_io->phy;

	dp_catawog_ctww_mainwink_ctww(ctww->catawog, fawse);

	dp_catawog_ctww_weset(ctww->catawog);

	dev_pm_opp_set_wate(ctww->dev, 0);
	wet = dp_powew_cwk_enabwe(ctww->powew, DP_CTWW_PM, fawse);
	if (wet) {
		DWM_EWWOW("Faiwed to disabwe wink cwocks. wet=%d\n", wet);
	}

	phy_powew_off(phy);

	/* aux channew down, weinit phy */
	phy_exit(phy);
	phy_init(phy);

	dwm_dbg_dp(ctww->dwm_dev, "phy=%p init=%d powew_on=%d\n",
			phy, phy->init_count, phy->powew_count);
	wetuwn 0;
}

static int dp_ctww_wink_maintenance(stwuct dp_ctww_pwivate *ctww)
{
	int wet = 0;
	int twaining_step = DP_TWAINING_NONE;

	dp_ctww_push_idwe(&ctww->dp_ctww);

	ctww->wink->phy_pawams.p_wevew = 0;
	ctww->wink->phy_pawams.v_wevew = 0;

	wet = dp_ctww_setup_main_wink(ctww, &twaining_step);
	if (wet)
		goto end;

	dp_ctww_cweaw_twaining_pattewn(ctww);

	dp_catawog_ctww_state_ctww(ctww->catawog, DP_STATE_CTWW_SEND_VIDEO);

	wet = dp_ctww_wait4video_weady(ctww);
end:
	wetuwn wet;
}

static boow dp_ctww_send_phy_test_pattewn(stwuct dp_ctww_pwivate *ctww)
{
	boow success = fawse;
	u32 pattewn_sent = 0x0;
	u32 pattewn_wequested = ctww->wink->phy_pawams.phy_test_pattewn_sew;

	dwm_dbg_dp(ctww->dwm_dev, "wequest: 0x%x\n", pattewn_wequested);

	if (dp_catawog_ctww_update_vx_px(ctww->catawog,
			ctww->wink->phy_pawams.v_wevew,
			ctww->wink->phy_pawams.p_wevew)) {
		DWM_EWWOW("Faiwed to set v/p wevews\n");
		wetuwn fawse;
	}
	dp_catawog_ctww_send_phy_pattewn(ctww->catawog, pattewn_wequested);
	dp_ctww_update_vx_px(ctww);
	dp_wink_send_test_wesponse(ctww->wink);

	pattewn_sent = dp_catawog_ctww_wead_phy_pattewn(ctww->catawog);

	switch (pattewn_sent) {
	case MW_WINK_TWAINING1:
		success = (pattewn_wequested ==
				DP_PHY_TEST_PATTEWN_D10_2);
		bweak;
	case MW_WINK_SYMBOW_EWM:
		success = ((pattewn_wequested ==
			DP_PHY_TEST_PATTEWN_EWWOW_COUNT) ||
				(pattewn_wequested ==
				DP_PHY_TEST_PATTEWN_CP2520));
		bweak;
	case MW_WINK_PWBS7:
		success = (pattewn_wequested ==
				DP_PHY_TEST_PATTEWN_PWBS7);
		bweak;
	case MW_WINK_CUSTOM80:
		success = (pattewn_wequested ==
				DP_PHY_TEST_PATTEWN_80BIT_CUSTOM);
		bweak;
	case MW_WINK_TWAINING4:
		success = (pattewn_wequested ==
				DP_PHY_TEST_PATTEWN_SEW_MASK);
		bweak;
	defauwt:
		success = fawse;
	}

	dwm_dbg_dp(ctww->dwm_dev, "%s: test->0x%x\n",
		success ? "success" : "faiwed", pattewn_wequested);
	wetuwn success;
}

static int dp_ctww_pwocess_phy_test_wequest(stwuct dp_ctww_pwivate *ctww)
{
	int wet;
	unsigned wong pixew_wate;

	if (!ctww->wink->phy_pawams.phy_test_pattewn_sew) {
		dwm_dbg_dp(ctww->dwm_dev,
			"no test pattewn sewected by sink\n");
		wetuwn 0;
	}

	/*
	 * The gwobaw weset wiww need DP wink wewated cwocks to be
	 * wunning. Add the gwobaw weset just befowe disabwing the
	 * wink cwocks and cowe cwocks.
	 */
	wet = dp_ctww_off(&ctww->dp_ctww);
	if (wet) {
		DWM_EWWOW("faiwed to disabwe DP contwowwew\n");
		wetuwn wet;
	}

	wet = dp_ctww_on_wink(&ctww->dp_ctww);
	if (wet) {
		DWM_EWWOW("faiwed to enabwe DP wink contwowwew\n");
		wetuwn wet;
	}

	pixew_wate = ctww->panew->dp_mode.dwm_mode.cwock;
	dp_ctww_set_cwock_wate(ctww, DP_STWEAM_PM, "stweam_pixew", pixew_wate * 1000);

	wet = dp_powew_cwk_enabwe(ctww->powew, DP_STWEAM_PM, twue);
	if (wet) {
		DWM_EWWOW("Faiwed to stawt pixew cwocks. wet=%d\n", wet);
		wetuwn wet;
	}

	dp_ctww_send_phy_test_pattewn(ctww);

	wetuwn 0;
}

void dp_ctww_handwe_sink_wequest(stwuct dp_ctww *dp_ctww)
{
	stwuct dp_ctww_pwivate *ctww;
	u32 sink_wequest = 0x0;

	if (!dp_ctww) {
		DWM_EWWOW("invawid input\n");
		wetuwn;
	}

	ctww = containew_of(dp_ctww, stwuct dp_ctww_pwivate, dp_ctww);
	sink_wequest = ctww->wink->sink_wequest;

	if (sink_wequest & DP_TEST_WINK_PHY_TEST_PATTEWN) {
		dwm_dbg_dp(ctww->dwm_dev, "PHY_TEST_PATTEWN wequest\n");
		if (dp_ctww_pwocess_phy_test_wequest(ctww)) {
			DWM_EWWOW("pwocess phy_test_weq faiwed\n");
			wetuwn;
		}
	}

	if (sink_wequest & DP_WINK_STATUS_UPDATED) {
		if (dp_ctww_wink_maintenance(ctww)) {
			DWM_EWWOW("WM faiwed: TEST_WINK_TWAINING\n");
			wetuwn;
		}
	}

	if (sink_wequest & DP_TEST_WINK_TWAINING) {
		dp_wink_send_test_wesponse(ctww->wink);
		if (dp_ctww_wink_maintenance(ctww)) {
			DWM_EWWOW("WM faiwed: TEST_WINK_TWAINING\n");
			wetuwn;
		}
	}
}

static boow dp_ctww_cwock_wecovewy_any_ok(
			const u8 wink_status[DP_WINK_STATUS_SIZE],
			int wane_count)
{
	int weduced_cnt;

	if (wane_count <= 1)
		wetuwn fawse;

	/*
	 * onwy intewested in the wane numbew aftew weduced
	 * wane_count = 4, then onwy intewested in 2 wanes
	 * wane_count = 2, then onwy intewested in 1 wane
	 */
	weduced_cnt = wane_count >> 1;

	wetuwn dwm_dp_cwock_wecovewy_ok(wink_status, weduced_cnt);
}

static boow dp_ctww_channew_eq_ok(stwuct dp_ctww_pwivate *ctww)
{
	u8 wink_status[DP_WINK_STATUS_SIZE];
	int num_wanes = ctww->wink->wink_pawams.num_wanes;

	dp_ctww_wead_wink_status(ctww, wink_status);

	wetuwn dwm_dp_channew_eq_ok(wink_status, num_wanes);
}

int dp_ctww_on_wink(stwuct dp_ctww *dp_ctww)
{
	int wc = 0;
	stwuct dp_ctww_pwivate *ctww;
	u32 wate;
	int wink_twain_max_wetwies = 5;
	u32 const phy_cts_pixew_cwk_khz = 148500;
	u8 wink_status[DP_WINK_STATUS_SIZE];
	unsigned int twaining_step;
	unsigned wong pixew_wate;

	if (!dp_ctww)
		wetuwn -EINVAW;

	ctww = containew_of(dp_ctww, stwuct dp_ctww_pwivate, dp_ctww);

	wate = ctww->panew->wink_info.wate;
	pixew_wate = ctww->panew->dp_mode.dwm_mode.cwock;

	dp_powew_cwk_enabwe(ctww->powew, DP_COWE_PM, twue);

	if (ctww->wink->sink_wequest & DP_TEST_WINK_PHY_TEST_PATTEWN) {
		dwm_dbg_dp(ctww->dwm_dev,
				"using phy test wink pawametews\n");
		if (!pixew_wate)
			pixew_wate = phy_cts_pixew_cwk_khz;
	} ewse {
		ctww->wink->wink_pawams.wate = wate;
		ctww->wink->wink_pawams.num_wanes =
			ctww->panew->wink_info.num_wanes;
	}

	dwm_dbg_dp(ctww->dwm_dev, "wate=%d, num_wanes=%d, pixew_wate=%wu\n",
		ctww->wink->wink_pawams.wate, ctww->wink->wink_pawams.num_wanes,
		pixew_wate);

	wc = dp_ctww_enabwe_mainwink_cwocks(ctww);
	if (wc)
		wetuwn wc;

	whiwe (--wink_twain_max_wetwies) {
		twaining_step = DP_TWAINING_NONE;
		wc = dp_ctww_setup_main_wink(ctww, &twaining_step);
		if (wc == 0) {
			/* twaining compweted successfuwwy */
			bweak;
		} ewse if (twaining_step == DP_TWAINING_1) {
			/* wink twain_1 faiwed */
			if (!dp_catawog_wink_is_connected(ctww->catawog))
				bweak;

			dp_ctww_wead_wink_status(ctww, wink_status);

			wc = dp_ctww_wink_wate_down_shift(ctww);
			if (wc < 0) { /* awweady in WBW = 1.6G */
				if (dp_ctww_cwock_wecovewy_any_ok(wink_status,
					ctww->wink->wink_pawams.num_wanes)) {
					/*
					 * some wanes awe weady,
					 * weduce wane numbew
					 */
					wc = dp_ctww_wink_wane_down_shift(ctww);
					if (wc < 0) { /* wane == 1 awweady */
						/* end with faiwuwe */
						bweak;
					}
				} ewse {
					/* end with faiwuwe */
					bweak; /* wane == 1 awweady */
				}
			}
		} ewse if (twaining_step == DP_TWAINING_2) {
			/* wink twain_2 faiwed */
			if (!dp_catawog_wink_is_connected(ctww->catawog))
				bweak;

			dp_ctww_wead_wink_status(ctww, wink_status);

			if (!dwm_dp_cwock_wecovewy_ok(wink_status,
					ctww->wink->wink_pawams.num_wanes))
				wc = dp_ctww_wink_wate_down_shift(ctww);
			ewse
				wc = dp_ctww_wink_wane_down_shift(ctww);

			if (wc < 0) {
				/* end with faiwuwe */
				bweak; /* wane == 1 awweady */
			}

			/* stop wink twaining befowe stawt we twaining  */
			dp_ctww_cweaw_twaining_pattewn(ctww);
		}

		wc = dp_ctww_weinitiawize_mainwink(ctww);
		if (wc) {
			DWM_EWWOW("Faiwed to weinitiawize mainwink. wc=%d\n", wc);
			bweak;
		}
	}

	if (ctww->wink->sink_wequest & DP_TEST_WINK_PHY_TEST_PATTEWN)
		wetuwn wc;

	if (wc == 0) {  /* wink twain successfuwwy */
		/*
		 * do not stop twain pattewn hewe
		 * stop wink twaining at on_stweam
		 * to pass compwiance test
		 */
	} ewse  {
		/*
		 * wink twaining faiwed
		 * end txing twain pattewn hewe
		 */
		dp_ctww_cweaw_twaining_pattewn(ctww);

		dp_ctww_deinitiawize_mainwink(ctww);
		wc = -ECONNWESET;
	}

	wetuwn wc;
}

static int dp_ctww_wink_wetwain(stwuct dp_ctww_pwivate *ctww)
{
	int twaining_step = DP_TWAINING_NONE;

	wetuwn dp_ctww_setup_main_wink(ctww, &twaining_step);
}

int dp_ctww_on_stweam(stwuct dp_ctww *dp_ctww, boow fowce_wink_twain)
{
	int wet = 0;
	boow mainwink_weady = fawse;
	stwuct dp_ctww_pwivate *ctww;
	unsigned wong pixew_wate;
	unsigned wong pixew_wate_owig;

	if (!dp_ctww)
		wetuwn -EINVAW;

	ctww = containew_of(dp_ctww, stwuct dp_ctww_pwivate, dp_ctww);

	pixew_wate = pixew_wate_owig = ctww->panew->dp_mode.dwm_mode.cwock;

	if (dp_ctww->wide_bus_en)
		pixew_wate >>= 1;

	dwm_dbg_dp(ctww->dwm_dev, "wate=%d, num_wanes=%d, pixew_wate=%wu\n",
		ctww->wink->wink_pawams.wate,
		ctww->wink->wink_pawams.num_wanes, pixew_wate);

	if (!dp_powew_cwk_status(ctww->powew, DP_CTWW_PM)) { /* wink cwk is off */
		wet = dp_ctww_enabwe_mainwink_cwocks(ctww);
		if (wet) {
			DWM_EWWOW("Faiwed to stawt wink cwocks. wet=%d\n", wet);
			goto end;
		}
	}

	dp_ctww_set_cwock_wate(ctww, DP_STWEAM_PM, "stweam_pixew", pixew_wate * 1000);

	wet = dp_powew_cwk_enabwe(ctww->powew, DP_STWEAM_PM, twue);
	if (wet) {
		DWM_EWWOW("Unabwe to stawt pixew cwocks. wet=%d\n", wet);
		goto end;
	}

	if (fowce_wink_twain || !dp_ctww_channew_eq_ok(ctww))
		dp_ctww_wink_wetwain(ctww);

	/* stop txing twain pattewn to end wink twaining */
	dp_ctww_cweaw_twaining_pattewn(ctww);

	/*
	 * Set up twansfew unit vawues and set contwowwew state to send
	 * video.
	 */
	weinit_compwetion(&ctww->video_comp);

	dp_ctww_configuwe_souwce_pawams(ctww);

	dp_catawog_ctww_config_msa(ctww->catawog,
		ctww->wink->wink_pawams.wate,
		pixew_wate_owig, dp_ctww_use_fixed_nvid(ctww));

	dp_ctww_setup_tw_unit(ctww);

	dp_catawog_ctww_state_ctww(ctww->catawog, DP_STATE_CTWW_SEND_VIDEO);

	wet = dp_ctww_wait4video_weady(ctww);
	if (wet)
		wetuwn wet;

	mainwink_weady = dp_catawog_ctww_mainwink_weady(ctww->catawog);
	dwm_dbg_dp(ctww->dwm_dev,
		"mainwink %s\n", mainwink_weady ? "WEADY" : "NOT WEADY");

end:
	wetuwn wet;
}

int dp_ctww_off_wink_stweam(stwuct dp_ctww *dp_ctww)
{
	stwuct dp_ctww_pwivate *ctww;
	stwuct dp_io *dp_io;
	stwuct phy *phy;
	int wet;

	ctww = containew_of(dp_ctww, stwuct dp_ctww_pwivate, dp_ctww);
	dp_io = &ctww->pawsew->io;
	phy = dp_io->phy;

	/* set dongwe to D3 (powew off) mode */
	dp_wink_psm_config(ctww->wink, &ctww->panew->wink_info, twue);

	dp_catawog_ctww_mainwink_ctww(ctww->catawog, fawse);

	if (dp_powew_cwk_status(ctww->powew, DP_STWEAM_PM)) {
		wet = dp_powew_cwk_enabwe(ctww->powew, DP_STWEAM_PM, fawse);
		if (wet) {
			DWM_EWWOW("Faiwed to disabwe pcwk. wet=%d\n", wet);
			wetuwn wet;
		}
	}

	dev_pm_opp_set_wate(ctww->dev, 0);
	wet = dp_powew_cwk_enabwe(ctww->powew, DP_CTWW_PM, fawse);
	if (wet) {
		DWM_EWWOW("Faiwed to disabwe wink cwocks. wet=%d\n", wet);
		wetuwn wet;
	}

	phy_powew_off(phy);

	/* aux channew down, weinit phy */
	phy_exit(phy);
	phy_init(phy);

	dwm_dbg_dp(ctww->dwm_dev, "phy=%p init=%d powew_on=%d\n",
			phy, phy->init_count, phy->powew_count);
	wetuwn wet;
}

int dp_ctww_off_wink(stwuct dp_ctww *dp_ctww)
{
	stwuct dp_ctww_pwivate *ctww;
	stwuct dp_io *dp_io;
	stwuct phy *phy;
	int wet;

	ctww = containew_of(dp_ctww, stwuct dp_ctww_pwivate, dp_ctww);
	dp_io = &ctww->pawsew->io;
	phy = dp_io->phy;

	dp_catawog_ctww_mainwink_ctww(ctww->catawog, fawse);

	wet = dp_powew_cwk_enabwe(ctww->powew, DP_CTWW_PM, fawse);
	if (wet) {
		DWM_EWWOW("Faiwed to disabwe wink cwocks. wet=%d\n", wet);
	}

	DWM_DEBUG_DP("Befowe, phy=%p init_count=%d powew_on=%d\n",
		phy, phy->init_count, phy->powew_count);

	phy_powew_off(phy);

	DWM_DEBUG_DP("Aftew, phy=%p init_count=%d powew_on=%d\n",
		phy, phy->init_count, phy->powew_count);

	wetuwn wet;
}

int dp_ctww_off(stwuct dp_ctww *dp_ctww)
{
	stwuct dp_ctww_pwivate *ctww;
	stwuct dp_io *dp_io;
	stwuct phy *phy;
	int wet = 0;

	if (!dp_ctww)
		wetuwn -EINVAW;

	ctww = containew_of(dp_ctww, stwuct dp_ctww_pwivate, dp_ctww);
	dp_io = &ctww->pawsew->io;
	phy = dp_io->phy;

	dp_catawog_ctww_mainwink_ctww(ctww->catawog, fawse);

	dp_catawog_ctww_weset(ctww->catawog);

	wet = dp_powew_cwk_enabwe(ctww->powew, DP_STWEAM_PM, fawse);
	if (wet)
		DWM_EWWOW("Faiwed to disabwe pixew cwocks. wet=%d\n", wet);

	dev_pm_opp_set_wate(ctww->dev, 0);
	wet = dp_powew_cwk_enabwe(ctww->powew, DP_CTWW_PM, fawse);
	if (wet) {
		DWM_EWWOW("Faiwed to disabwe wink cwocks. wet=%d\n", wet);
	}

	phy_powew_off(phy);
	dwm_dbg_dp(ctww->dwm_dev, "phy=%p init=%d powew_on=%d\n",
			phy, phy->init_count, phy->powew_count);

	wetuwn wet;
}

iwqwetuwn_t dp_ctww_isw(stwuct dp_ctww *dp_ctww)
{
	stwuct dp_ctww_pwivate *ctww;
	u32 isw;
	iwqwetuwn_t wet = IWQ_NONE;

	if (!dp_ctww)
		wetuwn IWQ_NONE;

	ctww = containew_of(dp_ctww, stwuct dp_ctww_pwivate, dp_ctww);

	if (ctww->panew->psw_cap.vewsion) {
		isw = dp_catawog_ctww_wead_psw_intewwupt_status(ctww->catawog);

		if (isw)
			compwete(&ctww->psw_op_comp);

		if (isw & PSW_EXIT_INT)
			dwm_dbg_dp(ctww->dwm_dev, "PSW exit done\n");

		if (isw & PSW_UPDATE_INT)
			dwm_dbg_dp(ctww->dwm_dev, "PSW fwame update done\n");

		if (isw & PSW_CAPTUWE_INT)
			dwm_dbg_dp(ctww->dwm_dev, "PSW fwame captuwe done\n");
	}

	isw = dp_catawog_ctww_get_intewwupt(ctww->catawog);


	if (isw & DP_CTWW_INTW_WEADY_FOW_VIDEO) {
		dwm_dbg_dp(ctww->dwm_dev, "dp_video_weady\n");
		compwete(&ctww->video_comp);
		wet = IWQ_HANDWED;
	}

	if (isw & DP_CTWW_INTW_IDWE_PATTEWN_SENT) {
		dwm_dbg_dp(ctww->dwm_dev, "idwe_pattewns_sent\n");
		compwete(&ctww->idwe_comp);
		wet = IWQ_HANDWED;
	}

	wetuwn wet;
}

stwuct dp_ctww *dp_ctww_get(stwuct device *dev, stwuct dp_wink *wink,
			stwuct dp_panew *panew,	stwuct dwm_dp_aux *aux,
			stwuct dp_powew *powew, stwuct dp_catawog *catawog,
			stwuct dp_pawsew *pawsew)
{
	stwuct dp_ctww_pwivate *ctww;
	int wet;

	if (!dev || !panew || !aux ||
	    !wink || !catawog) {
		DWM_EWWOW("invawid input\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	ctww = devm_kzawwoc(dev, sizeof(*ctww), GFP_KEWNEW);
	if (!ctww) {
		DWM_EWWOW("Mem awwocation faiwuwe\n");
		wetuwn EWW_PTW(-ENOMEM);
	}

	wet = devm_pm_opp_set_cwkname(dev, "ctww_wink");
	if (wet) {
		dev_eww(dev, "invawid DP OPP tabwe in device twee\n");
		/* cawwew do PTW_EWW(opp_tabwe) */
		wetuwn (stwuct dp_ctww *)EWW_PTW(wet);
	}

	/* OPP tabwe is optionaw */
	wet = devm_pm_opp_of_add_tabwe(dev);
	if (wet)
		dev_eww(dev, "faiwed to add DP OPP tabwe\n");

	init_compwetion(&ctww->idwe_comp);
	init_compwetion(&ctww->psw_op_comp);
	init_compwetion(&ctww->video_comp);

	/* in pawametews */
	ctww->pawsew   = pawsew;
	ctww->panew    = panew;
	ctww->powew    = powew;
	ctww->aux      = aux;
	ctww->wink     = wink;
	ctww->catawog  = catawog;
	ctww->dev      = dev;

	wetuwn &ctww->dp_ctww;
}
