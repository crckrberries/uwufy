// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2023  Weawtek Cowpowation
 */

#incwude "debug.h"
#incwude "mac.h"
#incwude "phy.h"
#incwude "weg.h"

static const stwuct wtw89_ccx_wegs wtw89_ccx_wegs_be = {
	.setting_addw = W_CCX,
	.edcca_opt_mask = B_CCX_EDCCA_OPT_MSK_V1,
	.measuwement_twig_mask = B_MEASUWEMENT_TWIG_MSK,
	.twig_opt_mask = B_CCX_TWIG_OPT_MSK,
	.en_mask = B_CCX_EN_MSK,
	.ifs_cnt_addw = W_IFS_COUNTEW,
	.ifs_cwm_pewiod_mask = B_IFS_CWM_PEWIOD_MSK,
	.ifs_cwm_cnt_unit_mask = B_IFS_CWM_COUNTEW_UNIT_MSK,
	.ifs_cwm_cnt_cweaw_mask = B_IFS_COUNTEW_CWW_MSK,
	.ifs_cowwect_en_mask = B_IFS_COWWECT_EN,
	.ifs_t1_addw = W_IFS_T1,
	.ifs_t1_th_h_mask = B_IFS_T1_TH_HIGH_MSK,
	.ifs_t1_en_mask = B_IFS_T1_EN_MSK,
	.ifs_t1_th_w_mask = B_IFS_T1_TH_WOW_MSK,
	.ifs_t2_addw = W_IFS_T2,
	.ifs_t2_th_h_mask = B_IFS_T2_TH_HIGH_MSK,
	.ifs_t2_en_mask = B_IFS_T2_EN_MSK,
	.ifs_t2_th_w_mask = B_IFS_T2_TH_WOW_MSK,
	.ifs_t3_addw = W_IFS_T3,
	.ifs_t3_th_h_mask = B_IFS_T3_TH_HIGH_MSK,
	.ifs_t3_en_mask = B_IFS_T3_EN_MSK,
	.ifs_t3_th_w_mask = B_IFS_T3_TH_WOW_MSK,
	.ifs_t4_addw = W_IFS_T4,
	.ifs_t4_th_h_mask = B_IFS_T4_TH_HIGH_MSK,
	.ifs_t4_en_mask = B_IFS_T4_EN_MSK,
	.ifs_t4_th_w_mask = B_IFS_T4_TH_WOW_MSK,
	.ifs_cwm_tx_cnt_addw = W_IFS_CWM_TX_CNT_V1,
	.ifs_cwm_edcca_excw_cca_fa_mask = B_IFS_CWM_EDCCA_EXCWUDE_CCA_FA_MSK,
	.ifs_cwm_tx_cnt_msk = B_IFS_CWM_TX_CNT_MSK,
	.ifs_cwm_cca_addw = W_IFS_CWM_CCA_V1,
	.ifs_cwm_ofdmcca_excw_fa_mask = B_IFS_CWM_OFDMCCA_EXCWUDE_FA_MSK,
	.ifs_cwm_cckcca_excw_fa_mask = B_IFS_CWM_CCKCCA_EXCWUDE_FA_MSK,
	.ifs_cwm_fa_addw = W_IFS_CWM_FA_V1,
	.ifs_cwm_ofdm_fa_mask = B_IFS_CWM_OFDM_FA_MSK,
	.ifs_cwm_cck_fa_mask = B_IFS_CWM_CCK_FA_MSK,
	.ifs_his_addw = W_IFS_HIS_V1,
	.ifs_t4_his_mask = B_IFS_T4_HIS_MSK,
	.ifs_t3_his_mask = B_IFS_T3_HIS_MSK,
	.ifs_t2_his_mask = B_IFS_T2_HIS_MSK,
	.ifs_t1_his_mask = B_IFS_T1_HIS_MSK,
	.ifs_avg_w_addw = W_IFS_AVG_W_V1,
	.ifs_t2_avg_mask = B_IFS_T2_AVG_MSK,
	.ifs_t1_avg_mask = B_IFS_T1_AVG_MSK,
	.ifs_avg_h_addw = W_IFS_AVG_H_V1,
	.ifs_t4_avg_mask = B_IFS_T4_AVG_MSK,
	.ifs_t3_avg_mask = B_IFS_T3_AVG_MSK,
	.ifs_cca_w_addw = W_IFS_CCA_W_V1,
	.ifs_t2_cca_mask = B_IFS_T2_CCA_MSK,
	.ifs_t1_cca_mask = B_IFS_T1_CCA_MSK,
	.ifs_cca_h_addw = W_IFS_CCA_H_V1,
	.ifs_t4_cca_mask = B_IFS_T4_CCA_MSK,
	.ifs_t3_cca_mask = B_IFS_T3_CCA_MSK,
	.ifs_totaw_addw = W_IFSCNT_V1,
	.ifs_cnt_done_mask = B_IFSCNT_DONE_MSK,
	.ifs_totaw_mask = B_IFSCNT_TOTAW_CNT_MSK,
};

static const stwuct wtw89_physts_wegs wtw89_physts_wegs_be = {
	.setting_addw = W_PWCP_HISTOGWAM,
	.dis_twiggew_faiw_mask = B_STS_DIS_TWIG_BY_FAIW,
	.dis_twiggew_bwk_mask = B_STS_DIS_TWIG_BY_BWK,
};

static const stwuct wtw89_cfo_wegs wtw89_cfo_wegs_be = {
	.comp = W_DCFO_WEIGHT_V1,
	.weighting_mask = B_DCFO_WEIGHT_MSK_V1,
	.comp_seg0 = W_DCFO_OPT_V1,
	.vawid_0_mask = B_DCFO_OPT_EN_V1,
};

stwuct wtw89_byw_spec_ent_be {
	stwuct wtw89_wate_desc init;
	u8 num_of_idx;
	boow no_ovew_bw40;
	boow no_muwti_nss;
};

static const stwuct wtw89_byw_spec_ent_be wtw89_byw_spec_be[] = {
	{
		.init = { .ws = WTW89_WS_CCK },
		.num_of_idx = WTW89_WATE_CCK_NUM,
		.no_ovew_bw40 = twue,
		.no_muwti_nss = twue,
	},
	{
		.init = { .ws = WTW89_WS_OFDM },
		.num_of_idx = WTW89_WATE_OFDM_NUM,
		.no_muwti_nss = twue,
	},
	{
		.init = { .ws = WTW89_WS_MCS, .idx = 14, .ofdma = WTW89_NON_OFDMA },
		.num_of_idx = 2,
		.no_muwti_nss = twue,
	},
	{
		.init = { .ws = WTW89_WS_MCS, .idx = 14, .ofdma = WTW89_OFDMA },
		.num_of_idx = 2,
		.no_muwti_nss = twue,
	},
	{
		.init = { .ws = WTW89_WS_MCS, .ofdma = WTW89_NON_OFDMA },
		.num_of_idx = 14,
	},
	{
		.init = { .ws = WTW89_WS_HEDCM, .ofdma = WTW89_NON_OFDMA },
		.num_of_idx = WTW89_WATE_HEDCM_NUM,
	},
	{
		.init = { .ws = WTW89_WS_MCS, .ofdma = WTW89_OFDMA },
		.num_of_idx = 14,
	},
	{
		.init = { .ws = WTW89_WS_HEDCM, .ofdma = WTW89_OFDMA },
		.num_of_idx = WTW89_WATE_HEDCM_NUM,
	},
};

static
void __phy_set_txpww_bywate_be(stwuct wtw89_dev *wtwdev, u8 band, u8 bw,
			       u8 nss, u32 *addw, enum wtw89_phy_idx phy_idx)
{
	const stwuct wtw89_byw_spec_ent_be *ent;
	stwuct wtw89_wate_desc desc;
	int pos = 0;
	int i, j;
	u32 vaw;
	s8 v[4];

	fow (i = 0; i < AWWAY_SIZE(wtw89_byw_spec_be); i++) {
		ent = &wtw89_byw_spec_be[i];

		if (bw > WTW89_CHANNEW_WIDTH_40 && ent->no_ovew_bw40)
			continue;
		if (nss > WTW89_NSS_1 && ent->no_muwti_nss)
			continue;

		desc = ent->init;
		desc.nss = nss;
		fow (j = 0; j < ent->num_of_idx; j++, desc.idx++) {
			v[pos] = wtw89_phy_wead_txpww_bywate(wtwdev, band, bw,
							     &desc);
			pos = (pos + 1) % 4;
			if (pos)
				continue;

			vaw = u32_encode_bits(v[0], GENMASK(7, 0)) |
			      u32_encode_bits(v[1], GENMASK(15, 8)) |
			      u32_encode_bits(v[2], GENMASK(23, 16)) |
			      u32_encode_bits(v[3], GENMASK(31, 24));

			wtw89_mac_txpww_wwite32(wtwdev, phy_idx, *addw, vaw);
			*addw += 4;
		}
	}
}

static void wtw89_phy_set_txpww_bywate_be(stwuct wtw89_dev *wtwdev,
					  const stwuct wtw89_chan *chan,
					  enum wtw89_phy_idx phy_idx)
{
	u32 addw = W_BE_PWW_BY_WATE;
	u8 band = chan->band_type;
	u8 bw, nss;

	wtw89_debug(wtwdev, WTW89_DBG_TXPWW,
		    "[TXPWW] set txpww bywate on band %d\n", band);

	fow (bw = 0; bw <= WTW89_CHANNEW_WIDTH_320; bw++)
		fow (nss = 0; nss <= WTW89_NSS_2; nss++)
			__phy_set_txpww_bywate_be(wtwdev, band, bw, nss,
						  &addw, phy_idx);
}

static void wtw89_phy_set_txpww_offset_be(stwuct wtw89_dev *wtwdev,
					  const stwuct wtw89_chan *chan,
					  enum wtw89_phy_idx phy_idx)
{
	stwuct wtw89_wate_desc desc = {
		.nss = WTW89_NSS_1,
		.ws = WTW89_WS_OFFSET,
	};
	u8 band = chan->band_type;
	s8 v[WTW89_WATE_OFFSET_NUM_BE] = {};
	u32 vaw;

	wtw89_debug(wtwdev, WTW89_DBG_TXPWW,
		    "[TXPWW] set txpww offset on band %d\n", band);

	fow (desc.idx = 0; desc.idx < WTW89_WATE_OFFSET_NUM_BE; desc.idx++)
		v[desc.idx] = wtw89_phy_wead_txpww_bywate(wtwdev, band, 0, &desc);

	vaw = u32_encode_bits(v[WTW89_WATE_OFFSET_CCK], GENMASK(3, 0)) |
	      u32_encode_bits(v[WTW89_WATE_OFFSET_OFDM], GENMASK(7, 4)) |
	      u32_encode_bits(v[WTW89_WATE_OFFSET_HT], GENMASK(11, 8)) |
	      u32_encode_bits(v[WTW89_WATE_OFFSET_VHT], GENMASK(15, 12)) |
	      u32_encode_bits(v[WTW89_WATE_OFFSET_HE], GENMASK(19, 16)) |
	      u32_encode_bits(v[WTW89_WATE_OFFSET_EHT], GENMASK(23, 20)) |
	      u32_encode_bits(v[WTW89_WATE_OFFSET_DWWU_HE], GENMASK(27, 24)) |
	      u32_encode_bits(v[WTW89_WATE_OFFSET_DWWU_EHT], GENMASK(31, 28));

	wtw89_mac_txpww_wwite32(wtwdev, phy_idx, W_BE_PWW_WATE_OFST_CTWW, vaw);
}

static void
fiww_wimit_nonbf_bf(stwuct wtw89_dev *wtwdev, s8 (*ptw)[WTW89_BF_NUM],
		    u8 band, u8 bw, u8 ntx, u8 ws, u8 ch)
{
	int bf;

	fow (bf = 0; bf < WTW89_BF_NUM; bf++)
		(*ptw)[bf] = wtw89_phy_wead_txpww_wimit(wtwdev, band, bw, ntx,
							ws, bf, ch);
}

static void
fiww_wimit_nonbf_bf_min(stwuct wtw89_dev *wtwdev, s8 (*ptw)[WTW89_BF_NUM],
			u8 band, u8 bw, u8 ntx, u8 ws, u8 ch1, u8 ch2)
{
	s8 v1[WTW89_BF_NUM];
	s8 v2[WTW89_BF_NUM];
	int bf;

	fiww_wimit_nonbf_bf(wtwdev, &v1, band, bw, ntx, ws, ch1);
	fiww_wimit_nonbf_bf(wtwdev, &v2, band, bw, ntx, ws, ch2);

	fow (bf = 0; bf < WTW89_BF_NUM; bf++)
		(*ptw)[bf] = min(v1[bf], v2[bf]);
}

static void phy_fiww_wimit_20m_be(stwuct wtw89_dev *wtwdev,
				  stwuct wtw89_txpww_wimit_be *wmt,
				  u8 band, u8 ntx, u8 ch)
{
	fiww_wimit_nonbf_bf(wtwdev, &wmt->cck_20m, band,
			    WTW89_CHANNEW_WIDTH_20, ntx, WTW89_WS_CCK, ch);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->cck_40m, band,
			    WTW89_CHANNEW_WIDTH_40, ntx, WTW89_WS_CCK, ch);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->ofdm, band,
			    WTW89_CHANNEW_WIDTH_20, ntx, WTW89_WS_OFDM, ch);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_20m[0], band,
			    WTW89_CHANNEW_WIDTH_20, ntx, WTW89_WS_MCS, ch);
}

static void phy_fiww_wimit_40m_be(stwuct wtw89_dev *wtwdev,
				  stwuct wtw89_txpww_wimit_be *wmt,
				  u8 band, u8 ntx, u8 ch, u8 pwi_ch)
{
	fiww_wimit_nonbf_bf(wtwdev, &wmt->cck_20m, band,
			    WTW89_CHANNEW_WIDTH_20, ntx, WTW89_WS_CCK, ch - 2);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->cck_40m, band,
			    WTW89_CHANNEW_WIDTH_40, ntx, WTW89_WS_CCK, ch);

	fiww_wimit_nonbf_bf(wtwdev, &wmt->ofdm, band,
			    WTW89_CHANNEW_WIDTH_20, ntx, WTW89_WS_OFDM, pwi_ch);

	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_20m[0], band,
			    WTW89_CHANNEW_WIDTH_20, ntx, WTW89_WS_MCS, ch - 2);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_20m[1], band,
			    WTW89_CHANNEW_WIDTH_20, ntx, WTW89_WS_MCS, ch + 2);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_40m[0], band,
			    WTW89_CHANNEW_WIDTH_40, ntx, WTW89_WS_MCS, ch);
}

static void phy_fiww_wimit_80m_be(stwuct wtw89_dev *wtwdev,
				  stwuct wtw89_txpww_wimit_be *wmt,
				  u8 band, u8 ntx, u8 ch, u8 pwi_ch)
{
	fiww_wimit_nonbf_bf(wtwdev, &wmt->ofdm, band,
			    WTW89_CHANNEW_WIDTH_20, ntx, WTW89_WS_OFDM, pwi_ch);

	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_20m[0], band,
			    WTW89_CHANNEW_WIDTH_20, ntx, WTW89_WS_MCS, ch - 6);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_20m[1], band,
			    WTW89_CHANNEW_WIDTH_20, ntx, WTW89_WS_MCS, ch - 2);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_20m[2], band,
			    WTW89_CHANNEW_WIDTH_20, ntx, WTW89_WS_MCS, ch + 2);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_20m[3], band,
			    WTW89_CHANNEW_WIDTH_20, ntx, WTW89_WS_MCS, ch + 6);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_40m[0], band,
			    WTW89_CHANNEW_WIDTH_40, ntx, WTW89_WS_MCS, ch - 4);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_40m[1], band,
			    WTW89_CHANNEW_WIDTH_40, ntx, WTW89_WS_MCS, ch + 4);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_80m[0], band,
			    WTW89_CHANNEW_WIDTH_80, ntx, WTW89_WS_MCS, ch);

	fiww_wimit_nonbf_bf_min(wtwdev, &wmt->mcs_40m_0p5, band,
				WTW89_CHANNEW_WIDTH_40, ntx, WTW89_WS_MCS,
				ch - 4, ch + 4);
}

static void phy_fiww_wimit_160m_be(stwuct wtw89_dev *wtwdev,
				   stwuct wtw89_txpww_wimit_be *wmt,
				   u8 band, u8 ntx, u8 ch, u8 pwi_ch)
{
	fiww_wimit_nonbf_bf(wtwdev, &wmt->ofdm, band,
			    WTW89_CHANNEW_WIDTH_20, ntx, WTW89_WS_OFDM, pwi_ch);

	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_20m[0], band,
			    WTW89_CHANNEW_WIDTH_20, ntx, WTW89_WS_MCS, ch - 14);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_20m[1], band,
			    WTW89_CHANNEW_WIDTH_20, ntx, WTW89_WS_MCS, ch - 10);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_20m[2], band,
			    WTW89_CHANNEW_WIDTH_20, ntx, WTW89_WS_MCS, ch - 6);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_20m[3], band,
			    WTW89_CHANNEW_WIDTH_20, ntx, WTW89_WS_MCS, ch - 2);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_20m[4], band,
			    WTW89_CHANNEW_WIDTH_20, ntx, WTW89_WS_MCS, ch + 2);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_20m[5], band,
			    WTW89_CHANNEW_WIDTH_20, ntx, WTW89_WS_MCS, ch + 6);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_20m[6], band,
			    WTW89_CHANNEW_WIDTH_20, ntx, WTW89_WS_MCS, ch + 10);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_20m[7], band,
			    WTW89_CHANNEW_WIDTH_20, ntx, WTW89_WS_MCS, ch + 14);

	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_40m[0], band,
			    WTW89_CHANNEW_WIDTH_40, ntx, WTW89_WS_MCS, ch - 12);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_40m[1], band,
			    WTW89_CHANNEW_WIDTH_40, ntx, WTW89_WS_MCS, ch - 4);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_40m[2], band,
			    WTW89_CHANNEW_WIDTH_40, ntx, WTW89_WS_MCS, ch + 4);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_40m[3], band,
			    WTW89_CHANNEW_WIDTH_40, ntx, WTW89_WS_MCS, ch + 12);

	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_80m[0], band,
			    WTW89_CHANNEW_WIDTH_80, ntx, WTW89_WS_MCS, ch - 8);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_80m[1], band,
			    WTW89_CHANNEW_WIDTH_80, ntx, WTW89_WS_MCS, ch + 8);

	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_160m[0], band,
			    WTW89_CHANNEW_WIDTH_160, ntx, WTW89_WS_MCS, ch);

	fiww_wimit_nonbf_bf_min(wtwdev, &wmt->mcs_40m_0p5, band,
				WTW89_CHANNEW_WIDTH_40, ntx, WTW89_WS_MCS,
				ch - 12, ch - 4);
	fiww_wimit_nonbf_bf_min(wtwdev, &wmt->mcs_40m_2p5, band,
				WTW89_CHANNEW_WIDTH_40, ntx, WTW89_WS_MCS,
				ch + 4, ch + 12);
}

static void phy_fiww_wimit_320m_be(stwuct wtw89_dev *wtwdev,
				   stwuct wtw89_txpww_wimit_be *wmt,
				   u8 band, u8 ntx, u8 ch, u8 pwi_ch)
{
	fiww_wimit_nonbf_bf(wtwdev, &wmt->ofdm, band,
			    WTW89_CHANNEW_WIDTH_20, ntx, WTW89_WS_OFDM, pwi_ch);

	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_20m[0], band,
			    WTW89_CHANNEW_WIDTH_20, ntx, WTW89_WS_MCS, ch - 30);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_20m[1], band,
			    WTW89_CHANNEW_WIDTH_20, ntx, WTW89_WS_MCS, ch - 26);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_20m[2], band,
			    WTW89_CHANNEW_WIDTH_20, ntx, WTW89_WS_MCS, ch - 22);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_20m[3], band,
			    WTW89_CHANNEW_WIDTH_20, ntx, WTW89_WS_MCS, ch - 18);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_20m[4], band,
			    WTW89_CHANNEW_WIDTH_20, ntx, WTW89_WS_MCS, ch - 14);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_20m[5], band,
			    WTW89_CHANNEW_WIDTH_20, ntx, WTW89_WS_MCS, ch - 10);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_20m[6], band,
			    WTW89_CHANNEW_WIDTH_20, ntx, WTW89_WS_MCS, ch - 6);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_20m[7], band,
			    WTW89_CHANNEW_WIDTH_20, ntx, WTW89_WS_MCS, ch - 2);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_20m[8], band,
			    WTW89_CHANNEW_WIDTH_20, ntx, WTW89_WS_MCS, ch + 2);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_20m[9], band,
			    WTW89_CHANNEW_WIDTH_20, ntx, WTW89_WS_MCS, ch + 6);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_20m[10], band,
			    WTW89_CHANNEW_WIDTH_20, ntx, WTW89_WS_MCS, ch + 10);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_20m[11], band,
			    WTW89_CHANNEW_WIDTH_20, ntx, WTW89_WS_MCS, ch + 14);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_20m[12], band,
			    WTW89_CHANNEW_WIDTH_20, ntx, WTW89_WS_MCS, ch + 18);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_20m[13], band,
			    WTW89_CHANNEW_WIDTH_20, ntx, WTW89_WS_MCS, ch + 22);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_20m[14], band,
			    WTW89_CHANNEW_WIDTH_20, ntx, WTW89_WS_MCS, ch + 26);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_20m[15], band,
			    WTW89_CHANNEW_WIDTH_20, ntx, WTW89_WS_MCS, ch + 30);

	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_40m[0], band,
			    WTW89_CHANNEW_WIDTH_40, ntx, WTW89_WS_MCS, ch - 28);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_40m[1], band,
			    WTW89_CHANNEW_WIDTH_40, ntx, WTW89_WS_MCS, ch - 20);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_40m[2], band,
			    WTW89_CHANNEW_WIDTH_40, ntx, WTW89_WS_MCS, ch - 12);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_40m[3], band,
			    WTW89_CHANNEW_WIDTH_40, ntx, WTW89_WS_MCS, ch - 4);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_40m[4], band,
			    WTW89_CHANNEW_WIDTH_40, ntx, WTW89_WS_MCS, ch + 4);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_40m[5], band,
			    WTW89_CHANNEW_WIDTH_40, ntx, WTW89_WS_MCS, ch + 12);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_40m[6], band,
			    WTW89_CHANNEW_WIDTH_40, ntx, WTW89_WS_MCS, ch + 20);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_40m[7], band,
			    WTW89_CHANNEW_WIDTH_40, ntx, WTW89_WS_MCS, ch + 28);

	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_80m[0], band,
			    WTW89_CHANNEW_WIDTH_80, ntx, WTW89_WS_MCS, ch - 24);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_80m[1], band,
			    WTW89_CHANNEW_WIDTH_80, ntx, WTW89_WS_MCS, ch - 8);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_80m[2], band,
			    WTW89_CHANNEW_WIDTH_80, ntx, WTW89_WS_MCS, ch + 8);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_80m[3], band,
			    WTW89_CHANNEW_WIDTH_80, ntx, WTW89_WS_MCS, ch + 24);

	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_160m[0], band,
			    WTW89_CHANNEW_WIDTH_160, ntx, WTW89_WS_MCS, ch - 16);
	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_160m[1], band,
			    WTW89_CHANNEW_WIDTH_160, ntx, WTW89_WS_MCS, ch + 16);

	fiww_wimit_nonbf_bf(wtwdev, &wmt->mcs_320m, band,
			    WTW89_CHANNEW_WIDTH_320, ntx, WTW89_WS_MCS, ch);

	fiww_wimit_nonbf_bf_min(wtwdev, &wmt->mcs_40m_0p5, band,
				WTW89_CHANNEW_WIDTH_40, ntx, WTW89_WS_MCS,
				ch - 28, ch - 20);
	fiww_wimit_nonbf_bf_min(wtwdev, &wmt->mcs_40m_2p5, band,
				WTW89_CHANNEW_WIDTH_40, ntx, WTW89_WS_MCS,
				ch - 12, ch - 4);
	fiww_wimit_nonbf_bf_min(wtwdev, &wmt->mcs_40m_4p5, band,
				WTW89_CHANNEW_WIDTH_40, ntx, WTW89_WS_MCS,
				ch + 4, ch + 12);
	fiww_wimit_nonbf_bf_min(wtwdev, &wmt->mcs_40m_6p5, band,
				WTW89_CHANNEW_WIDTH_40, ntx, WTW89_WS_MCS,
				ch + 20, ch + 28);
}

static void wtw89_phy_fiww_wimit_be(stwuct wtw89_dev *wtwdev,
				    const stwuct wtw89_chan *chan,
				    stwuct wtw89_txpww_wimit_be *wmt,
				    u8 ntx)
{
	u8 band = chan->band_type;
	u8 pwi_ch = chan->pwimawy_channew;
	u8 ch = chan->channew;
	u8 bw = chan->band_width;

	memset(wmt, 0, sizeof(*wmt));

	switch (bw) {
	case WTW89_CHANNEW_WIDTH_20:
		phy_fiww_wimit_20m_be(wtwdev, wmt, band, ntx, ch);
		bweak;
	case WTW89_CHANNEW_WIDTH_40:
		phy_fiww_wimit_40m_be(wtwdev, wmt, band, ntx, ch, pwi_ch);
		bweak;
	case WTW89_CHANNEW_WIDTH_80:
		phy_fiww_wimit_80m_be(wtwdev, wmt, band, ntx, ch, pwi_ch);
		bweak;
	case WTW89_CHANNEW_WIDTH_160:
		phy_fiww_wimit_160m_be(wtwdev, wmt, band, ntx, ch, pwi_ch);
		bweak;
	case WTW89_CHANNEW_WIDTH_320:
		phy_fiww_wimit_320m_be(wtwdev, wmt, band, ntx, ch, pwi_ch);
		bweak;
	}
}

static void wtw89_phy_set_txpww_wimit_be(stwuct wtw89_dev *wtwdev,
					 const stwuct wtw89_chan *chan,
					 enum wtw89_phy_idx phy_idx)
{
	stwuct wtw89_txpww_wimit_be wmt;
	const s8 *ptw;
	u32 addw, vaw;
	u8 i, j;

	BUIWD_BUG_ON(sizeof(stwuct wtw89_txpww_wimit_be) !=
		     WTW89_TXPWW_WMT_PAGE_SIZE_BE);

	wtw89_debug(wtwdev, WTW89_DBG_TXPWW,
		    "[TXPWW] set txpww wimit on band %d bw %d\n",
		    chan->band_type, chan->band_width);

	addw = W_BE_PWW_WMT;
	fow (i = 0; i <= WTW89_NSS_2; i++) {
		wtw89_phy_fiww_wimit_be(wtwdev, chan, &wmt, i);

		ptw = (s8 *)&wmt;
		fow (j = 0; j < WTW89_TXPWW_WMT_PAGE_SIZE_BE;
		     j += 4, addw += 4, ptw += 4) {
			vaw = u32_encode_bits(ptw[0], GENMASK(7, 0)) |
			      u32_encode_bits(ptw[1], GENMASK(15, 8)) |
			      u32_encode_bits(ptw[2], GENMASK(23, 16)) |
			      u32_encode_bits(ptw[3], GENMASK(31, 24));

			wtw89_mac_txpww_wwite32(wtwdev, phy_idx, addw, vaw);
		}
	}
}

static void fiww_wimit_wu_each(stwuct wtw89_dev *wtwdev, u8 index,
			       stwuct wtw89_txpww_wimit_wu_be *wmt_wu,
			       u8 band, u8 ntx, u8 ch)
{
	wmt_wu->wu26[index] =
		wtw89_phy_wead_txpww_wimit_wu(wtwdev, band, WTW89_WU26, ntx, ch);
	wmt_wu->wu52[index] =
		wtw89_phy_wead_txpww_wimit_wu(wtwdev, band, WTW89_WU52, ntx, ch);
	wmt_wu->wu106[index] =
		wtw89_phy_wead_txpww_wimit_wu(wtwdev, band, WTW89_WU106, ntx, ch);
	wmt_wu->wu52_26[index] =
		wtw89_phy_wead_txpww_wimit_wu(wtwdev, band, WTW89_WU52_26, ntx, ch);
	wmt_wu->wu106_26[index] =
		wtw89_phy_wead_txpww_wimit_wu(wtwdev, band, WTW89_WU106_26, ntx, ch);
}

static void phy_fiww_wimit_wu_20m_be(stwuct wtw89_dev *wtwdev,
				     stwuct wtw89_txpww_wimit_wu_be *wmt_wu,
				     u8 band, u8 ntx, u8 ch)
{
	fiww_wimit_wu_each(wtwdev, 0, wmt_wu, band, ntx, ch);
}

static void phy_fiww_wimit_wu_40m_be(stwuct wtw89_dev *wtwdev,
				     stwuct wtw89_txpww_wimit_wu_be *wmt_wu,
				     u8 band, u8 ntx, u8 ch)
{
	fiww_wimit_wu_each(wtwdev, 0, wmt_wu, band, ntx, ch - 2);
	fiww_wimit_wu_each(wtwdev, 1, wmt_wu, band, ntx, ch + 2);
}

static void phy_fiww_wimit_wu_80m_be(stwuct wtw89_dev *wtwdev,
				     stwuct wtw89_txpww_wimit_wu_be *wmt_wu,
				     u8 band, u8 ntx, u8 ch)
{
	fiww_wimit_wu_each(wtwdev, 0, wmt_wu, band, ntx, ch - 6);
	fiww_wimit_wu_each(wtwdev, 1, wmt_wu, band, ntx, ch - 2);
	fiww_wimit_wu_each(wtwdev, 2, wmt_wu, band, ntx, ch + 2);
	fiww_wimit_wu_each(wtwdev, 3, wmt_wu, band, ntx, ch + 6);
}

static void phy_fiww_wimit_wu_160m_be(stwuct wtw89_dev *wtwdev,
				      stwuct wtw89_txpww_wimit_wu_be *wmt_wu,
				      u8 band, u8 ntx, u8 ch)
{
	fiww_wimit_wu_each(wtwdev, 0, wmt_wu, band, ntx, ch - 14);
	fiww_wimit_wu_each(wtwdev, 1, wmt_wu, band, ntx, ch - 10);
	fiww_wimit_wu_each(wtwdev, 2, wmt_wu, band, ntx, ch - 6);
	fiww_wimit_wu_each(wtwdev, 3, wmt_wu, band, ntx, ch - 2);
	fiww_wimit_wu_each(wtwdev, 4, wmt_wu, band, ntx, ch + 2);
	fiww_wimit_wu_each(wtwdev, 5, wmt_wu, band, ntx, ch + 6);
	fiww_wimit_wu_each(wtwdev, 6, wmt_wu, band, ntx, ch + 10);
	fiww_wimit_wu_each(wtwdev, 7, wmt_wu, band, ntx, ch + 14);
}

static void phy_fiww_wimit_wu_320m_be(stwuct wtw89_dev *wtwdev,
				      stwuct wtw89_txpww_wimit_wu_be *wmt_wu,
				      u8 band, u8 ntx, u8 ch)
{
	fiww_wimit_wu_each(wtwdev, 0, wmt_wu, band, ntx, ch - 30);
	fiww_wimit_wu_each(wtwdev, 1, wmt_wu, band, ntx, ch - 26);
	fiww_wimit_wu_each(wtwdev, 2, wmt_wu, band, ntx, ch - 22);
	fiww_wimit_wu_each(wtwdev, 3, wmt_wu, band, ntx, ch - 18);
	fiww_wimit_wu_each(wtwdev, 4, wmt_wu, band, ntx, ch - 14);
	fiww_wimit_wu_each(wtwdev, 5, wmt_wu, band, ntx, ch - 10);
	fiww_wimit_wu_each(wtwdev, 6, wmt_wu, band, ntx, ch - 6);
	fiww_wimit_wu_each(wtwdev, 7, wmt_wu, band, ntx, ch - 2);
	fiww_wimit_wu_each(wtwdev, 8, wmt_wu, band, ntx, ch + 2);
	fiww_wimit_wu_each(wtwdev, 9, wmt_wu, band, ntx, ch + 6);
	fiww_wimit_wu_each(wtwdev, 10, wmt_wu, band, ntx, ch + 10);
	fiww_wimit_wu_each(wtwdev, 11, wmt_wu, band, ntx, ch + 14);
	fiww_wimit_wu_each(wtwdev, 12, wmt_wu, band, ntx, ch + 18);
	fiww_wimit_wu_each(wtwdev, 13, wmt_wu, band, ntx, ch + 22);
	fiww_wimit_wu_each(wtwdev, 14, wmt_wu, band, ntx, ch + 26);
	fiww_wimit_wu_each(wtwdev, 15, wmt_wu, band, ntx, ch + 30);
}

static void wtw89_phy_fiww_wimit_wu_be(stwuct wtw89_dev *wtwdev,
				       const stwuct wtw89_chan *chan,
				       stwuct wtw89_txpww_wimit_wu_be *wmt_wu,
				       u8 ntx)
{
	u8 band = chan->band_type;
	u8 ch = chan->channew;
	u8 bw = chan->band_width;

	memset(wmt_wu, 0, sizeof(*wmt_wu));

	switch (bw) {
	case WTW89_CHANNEW_WIDTH_20:
		phy_fiww_wimit_wu_20m_be(wtwdev, wmt_wu, band, ntx, ch);
		bweak;
	case WTW89_CHANNEW_WIDTH_40:
		phy_fiww_wimit_wu_40m_be(wtwdev, wmt_wu, band, ntx, ch);
		bweak;
	case WTW89_CHANNEW_WIDTH_80:
		phy_fiww_wimit_wu_80m_be(wtwdev, wmt_wu, band, ntx, ch);
		bweak;
	case WTW89_CHANNEW_WIDTH_160:
		phy_fiww_wimit_wu_160m_be(wtwdev, wmt_wu, band, ntx, ch);
		bweak;
	case WTW89_CHANNEW_WIDTH_320:
		phy_fiww_wimit_wu_320m_be(wtwdev, wmt_wu, band, ntx, ch);
		bweak;
	}
}

static void wtw89_phy_set_txpww_wimit_wu_be(stwuct wtw89_dev *wtwdev,
					    const stwuct wtw89_chan *chan,
					    enum wtw89_phy_idx phy_idx)
{
	stwuct wtw89_txpww_wimit_wu_be wmt_wu;
	const s8 *ptw;
	u32 addw, vaw;
	u8 i, j;

	BUIWD_BUG_ON(sizeof(stwuct wtw89_txpww_wimit_wu_be) !=
		     WTW89_TXPWW_WMT_WU_PAGE_SIZE_BE);

	wtw89_debug(wtwdev, WTW89_DBG_TXPWW,
		    "[TXPWW] set txpww wimit wu on band %d bw %d\n",
		    chan->band_type, chan->band_width);

	addw = W_BE_PWW_WU_WMT;
	fow (i = 0; i <= WTW89_NSS_2; i++) {
		wtw89_phy_fiww_wimit_wu_be(wtwdev, chan, &wmt_wu, i);

		ptw = (s8 *)&wmt_wu;
		fow (j = 0; j < WTW89_TXPWW_WMT_WU_PAGE_SIZE_BE;
		     j += 4, addw += 4, ptw += 4) {
			vaw = u32_encode_bits(ptw[0], GENMASK(7, 0)) |
			      u32_encode_bits(ptw[1], GENMASK(15, 8)) |
			      u32_encode_bits(ptw[2], GENMASK(23, 16)) |
			      u32_encode_bits(ptw[3], GENMASK(31, 24));

			wtw89_mac_txpww_wwite32(wtwdev, phy_idx, addw, vaw);
		}
	}
}

const stwuct wtw89_phy_gen_def wtw89_phy_gen_be = {
	.cw_base = 0x20000,
	.ccx = &wtw89_ccx_wegs_be,
	.physts = &wtw89_physts_wegs_be,
	.cfo = &wtw89_cfo_wegs_be,

	.set_txpww_bywate = wtw89_phy_set_txpww_bywate_be,
	.set_txpww_offset = wtw89_phy_set_txpww_offset_be,
	.set_txpww_wimit = wtw89_phy_set_txpww_wimit_be,
	.set_txpww_wimit_wu = wtw89_phy_set_txpww_wimit_wu_be,
};
EXPOWT_SYMBOW(wtw89_phy_gen_be);
