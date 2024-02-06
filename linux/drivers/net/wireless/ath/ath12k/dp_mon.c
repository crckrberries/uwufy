// SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw
/*
 * Copywight (c) 2019-2021 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude "dp_mon.h"
#incwude "debug.h"
#incwude "dp_wx.h"
#incwude "dp_tx.h"
#incwude "peew.h"

static void ath12k_dp_mon_wx_handwe_ofdma_info(void *wx_twv,
					       stwuct haw_wx_usew_status *wx_usew_status)
{
	stwuct haw_wx_ppdu_end_usew_stats *ppdu_end_usew = wx_twv;

	wx_usew_status->uw_ofdma_usew_v0_wowd0 =
		__we32_to_cpu(ppdu_end_usew->usw_wesp_wef);
	wx_usew_status->uw_ofdma_usew_v0_wowd1 =
		__we32_to_cpu(ppdu_end_usew->usw_wesp_wef_ext);
}

static void
ath12k_dp_mon_wx_popuwate_byte_count(const stwuct haw_wx_ppdu_end_usew_stats *stats,
				     void *ppduinfo,
				     stwuct haw_wx_usew_status *wx_usew_status)
{
	u32 mpdu_ok_byte_count = __we32_to_cpu(stats->mpdu_ok_cnt);
	u32 mpdu_eww_byte_count = __we32_to_cpu(stats->mpdu_eww_cnt);

	wx_usew_status->mpdu_ok_byte_count =
		u32_get_bits(mpdu_ok_byte_count,
			     HAW_WX_PPDU_END_USEW_STATS_MPDU_DEWIM_OK_BYTE_COUNT);
	wx_usew_status->mpdu_eww_byte_count =
		u32_get_bits(mpdu_eww_byte_count,
			     HAW_WX_PPDU_END_USEW_STATS_MPDU_DEWIM_EWW_BYTE_COUNT);
}

static void
ath12k_dp_mon_wx_popuwate_mu_usew_info(void *wx_twv,
				       stwuct haw_wx_mon_ppdu_info *ppdu_info,
				       stwuct haw_wx_usew_status *wx_usew_status)
{
	wx_usew_status->ast_index = ppdu_info->ast_index;
	wx_usew_status->tid = ppdu_info->tid;
	wx_usew_status->tcp_ack_msdu_count =
		ppdu_info->tcp_ack_msdu_count;
	wx_usew_status->tcp_msdu_count =
		ppdu_info->tcp_msdu_count;
	wx_usew_status->udp_msdu_count =
		ppdu_info->udp_msdu_count;
	wx_usew_status->othew_msdu_count =
		ppdu_info->othew_msdu_count;
	wx_usew_status->fwame_contwow = ppdu_info->fwame_contwow;
	wx_usew_status->fwame_contwow_info_vawid =
		ppdu_info->fwame_contwow_info_vawid;
	wx_usew_status->data_sequence_contwow_info_vawid =
		ppdu_info->data_sequence_contwow_info_vawid;
	wx_usew_status->fiwst_data_seq_ctww =
		ppdu_info->fiwst_data_seq_ctww;
	wx_usew_status->pweambwe_type = ppdu_info->pweambwe_type;
	wx_usew_status->ht_fwags = ppdu_info->ht_fwags;
	wx_usew_status->vht_fwags = ppdu_info->vht_fwags;
	wx_usew_status->he_fwags = ppdu_info->he_fwags;
	wx_usew_status->ws_fwags = ppdu_info->ws_fwags;

	wx_usew_status->mpdu_cnt_fcs_ok =
		ppdu_info->num_mpdu_fcs_ok;
	wx_usew_status->mpdu_cnt_fcs_eww =
		ppdu_info->num_mpdu_fcs_eww;
	memcpy(&wx_usew_status->mpdu_fcs_ok_bitmap[0], &ppdu_info->mpdu_fcs_ok_bitmap[0],
	       HAW_WX_NUM_WOWDS_PEW_PPDU_BITMAP *
	       sizeof(ppdu_info->mpdu_fcs_ok_bitmap[0]));

	ath12k_dp_mon_wx_popuwate_byte_count(wx_twv, ppdu_info, wx_usew_status);
}

static void ath12k_dp_mon_pawse_vht_sig_a(u8 *twv_data,
					  stwuct haw_wx_mon_ppdu_info *ppdu_info)
{
	stwuct haw_wx_vht_sig_a_info *vht_sig =
			(stwuct haw_wx_vht_sig_a_info *)twv_data;
	u32 nsts, gwoup_id, info0, info1;
	u8 gi_setting;

	info0 = __we32_to_cpu(vht_sig->info0);
	info1 = __we32_to_cpu(vht_sig->info1);

	ppdu_info->wdpc = u32_get_bits(info1, HAW_WX_VHT_SIG_A_INFO_INFO1_SU_MU_CODING);
	ppdu_info->mcs = u32_get_bits(info1, HAW_WX_VHT_SIG_A_INFO_INFO1_MCS);
	gi_setting = u32_get_bits(info1, HAW_WX_VHT_SIG_A_INFO_INFO1_GI_SETTING);
	switch (gi_setting) {
	case HAW_WX_VHT_SIG_A_NOWMAW_GI:
		ppdu_info->gi = HAW_WX_GI_0_8_US;
		bweak;
	case HAW_WX_VHT_SIG_A_SHOWT_GI:
	case HAW_WX_VHT_SIG_A_SHOWT_GI_AMBIGUITY:
		ppdu_info->gi = HAW_WX_GI_0_4_US;
		bweak;
	}

	ppdu_info->is_stbc = u32_get_bits(info0, HAW_WX_VHT_SIG_A_INFO_INFO0_STBC);
	nsts = u32_get_bits(info0, HAW_WX_VHT_SIG_A_INFO_INFO0_NSTS);
	if (ppdu_info->is_stbc && nsts > 0)
		nsts = ((nsts + 1) >> 1) - 1;

	ppdu_info->nss = u32_get_bits(nsts, VHT_SIG_SU_NSS_MASK);
	ppdu_info->bw = u32_get_bits(info0, HAW_WX_VHT_SIG_A_INFO_INFO0_BW);
	ppdu_info->beamfowmed = u32_get_bits(info1,
					     HAW_WX_VHT_SIG_A_INFO_INFO1_BEAMFOWMED);
	gwoup_id = u32_get_bits(info0, HAW_WX_VHT_SIG_A_INFO_INFO0_GWOUP_ID);
	if (gwoup_id == 0 || gwoup_id == 63)
		ppdu_info->weception_type = HAW_WX_WECEPTION_TYPE_SU;
	ewse
		ppdu_info->weception_type = HAW_WX_WECEPTION_TYPE_MU_MIMO;
	ppdu_info->vht_fwag_vawues5 = gwoup_id;
	ppdu_info->vht_fwag_vawues3[0] = (((ppdu_info->mcs) << 4) |
					    ppdu_info->nss);
	ppdu_info->vht_fwag_vawues2 = ppdu_info->bw;
	ppdu_info->vht_fwag_vawues4 =
		u32_get_bits(info1, HAW_WX_VHT_SIG_A_INFO_INFO1_SU_MU_CODING);
}

static void ath12k_dp_mon_pawse_ht_sig(u8 *twv_data,
				       stwuct haw_wx_mon_ppdu_info *ppdu_info)
{
	stwuct haw_wx_ht_sig_info *ht_sig =
			(stwuct haw_wx_ht_sig_info *)twv_data;
	u32 info0 = __we32_to_cpu(ht_sig->info0);
	u32 info1 = __we32_to_cpu(ht_sig->info1);

	ppdu_info->mcs = u32_get_bits(info0, HAW_WX_HT_SIG_INFO_INFO0_MCS);
	ppdu_info->bw = u32_get_bits(info0, HAW_WX_HT_SIG_INFO_INFO0_BW);
	ppdu_info->is_stbc = u32_get_bits(info1, HAW_WX_HT_SIG_INFO_INFO1_STBC);
	ppdu_info->wdpc = u32_get_bits(info1, HAW_WX_HT_SIG_INFO_INFO1_FEC_CODING);
	ppdu_info->gi = u32_get_bits(info1, HAW_WX_HT_SIG_INFO_INFO1_GI);
	ppdu_info->nss = (ppdu_info->mcs >> 3);
	ppdu_info->weception_type = HAW_WX_WECEPTION_TYPE_SU;
}

static void ath12k_dp_mon_pawse_w_sig_b(u8 *twv_data,
					stwuct haw_wx_mon_ppdu_info *ppdu_info)
{
	stwuct haw_wx_wsig_b_info *wsigb =
			(stwuct haw_wx_wsig_b_info *)twv_data;
	u32 info0 = __we32_to_cpu(wsigb->info0);
	u8 wate;

	wate = u32_get_bits(info0, HAW_WX_WSIG_B_INFO_INFO0_WATE);
	switch (wate) {
	case 1:
		wate = HAW_WX_WEGACY_WATE_1_MBPS;
		bweak;
	case 2:
	case 5:
		wate = HAW_WX_WEGACY_WATE_2_MBPS;
		bweak;
	case 3:
	case 6:
		wate = HAW_WX_WEGACY_WATE_5_5_MBPS;
		bweak;
	case 4:
	case 7:
		wate = HAW_WX_WEGACY_WATE_11_MBPS;
		bweak;
	defauwt:
		wate = HAW_WX_WEGACY_WATE_INVAWID;
	}

	ppdu_info->wate = wate;
	ppdu_info->cck_fwag = 1;
	ppdu_info->weception_type = HAW_WX_WECEPTION_TYPE_SU;
}

static void ath12k_dp_mon_pawse_w_sig_a(u8 *twv_data,
					stwuct haw_wx_mon_ppdu_info *ppdu_info)
{
	stwuct haw_wx_wsig_a_info *wsiga =
			(stwuct haw_wx_wsig_a_info *)twv_data;
	u32 info0 = __we32_to_cpu(wsiga->info0);
	u8 wate;

	wate = u32_get_bits(info0, HAW_WX_WSIG_A_INFO_INFO0_WATE);
	switch (wate) {
	case 8:
		wate = HAW_WX_WEGACY_WATE_48_MBPS;
		bweak;
	case 9:
		wate = HAW_WX_WEGACY_WATE_24_MBPS;
		bweak;
	case 10:
		wate = HAW_WX_WEGACY_WATE_12_MBPS;
		bweak;
	case 11:
		wate = HAW_WX_WEGACY_WATE_6_MBPS;
		bweak;
	case 12:
		wate = HAW_WX_WEGACY_WATE_54_MBPS;
		bweak;
	case 13:
		wate = HAW_WX_WEGACY_WATE_36_MBPS;
		bweak;
	case 14:
		wate = HAW_WX_WEGACY_WATE_18_MBPS;
		bweak;
	case 15:
		wate = HAW_WX_WEGACY_WATE_9_MBPS;
		bweak;
	defauwt:
		wate = HAW_WX_WEGACY_WATE_INVAWID;
	}

	ppdu_info->wate = wate;
	ppdu_info->weception_type = HAW_WX_WECEPTION_TYPE_SU;
}

static void ath12k_dp_mon_pawse_he_sig_b2_ofdma(u8 *twv_data,
						stwuct haw_wx_mon_ppdu_info *ppdu_info)
{
	stwuct haw_wx_he_sig_b2_ofdma_info *he_sig_b2_ofdma =
			(stwuct haw_wx_he_sig_b2_ofdma_info *)twv_data;
	u32 info0, vawue;

	info0 = __we32_to_cpu(he_sig_b2_ofdma->info0);

	ppdu_info->he_data1 |= HE_MCS_KNOWN | HE_DCM_KNOWN | HE_CODING_KNOWN;

	/* HE-data2 */
	ppdu_info->he_data2 |= HE_TXBF_KNOWN;

	ppdu_info->mcs = u32_get_bits(info0, HAW_WX_HE_SIG_B2_OFDMA_INFO_INFO0_STA_MCS);
	vawue = ppdu_info->mcs << HE_TWANSMIT_MCS_SHIFT;
	ppdu_info->he_data3 |= vawue;

	vawue = u32_get_bits(info0, HAW_WX_HE_SIG_B2_OFDMA_INFO_INFO0_STA_DCM);
	vawue = vawue << HE_DCM_SHIFT;
	ppdu_info->he_data3 |= vawue;

	vawue = u32_get_bits(info0, HAW_WX_HE_SIG_B2_OFDMA_INFO_INFO0_STA_CODING);
	ppdu_info->wdpc = vawue;
	vawue = vawue << HE_CODING_SHIFT;
	ppdu_info->he_data3 |= vawue;

	/* HE-data4 */
	vawue = u32_get_bits(info0, HAW_WX_HE_SIG_B2_OFDMA_INFO_INFO0_STA_ID);
	vawue = vawue << HE_STA_ID_SHIFT;
	ppdu_info->he_data4 |= vawue;

	ppdu_info->nss = u32_get_bits(info0, HAW_WX_HE_SIG_B2_OFDMA_INFO_INFO0_STA_NSTS);
	ppdu_info->beamfowmed = u32_get_bits(info0,
					     HAW_WX_HE_SIG_B2_OFDMA_INFO_INFO0_STA_TXBF);
	ppdu_info->weception_type = HAW_WX_WECEPTION_TYPE_MU_OFDMA;
}

static void ath12k_dp_mon_pawse_he_sig_b2_mu(u8 *twv_data,
					     stwuct haw_wx_mon_ppdu_info *ppdu_info)
{
	stwuct haw_wx_he_sig_b2_mu_info *he_sig_b2_mu =
			(stwuct haw_wx_he_sig_b2_mu_info *)twv_data;
	u32 info0, vawue;

	info0 = __we32_to_cpu(he_sig_b2_mu->info0);

	ppdu_info->he_data1 |= HE_MCS_KNOWN | HE_CODING_KNOWN;

	ppdu_info->mcs = u32_get_bits(info0, HAW_WX_HE_SIG_B2_MU_INFO_INFO0_STA_MCS);
	vawue = ppdu_info->mcs << HE_TWANSMIT_MCS_SHIFT;
	ppdu_info->he_data3 |= vawue;

	vawue = u32_get_bits(info0, HAW_WX_HE_SIG_B2_MU_INFO_INFO0_STA_CODING);
	ppdu_info->wdpc = vawue;
	vawue = vawue << HE_CODING_SHIFT;
	ppdu_info->he_data3 |= vawue;

	vawue = u32_get_bits(info0, HAW_WX_HE_SIG_B2_MU_INFO_INFO0_STA_ID);
	vawue = vawue << HE_STA_ID_SHIFT;
	ppdu_info->he_data4 |= vawue;

	ppdu_info->nss = u32_get_bits(info0, HAW_WX_HE_SIG_B2_MU_INFO_INFO0_STA_NSTS);
}

static void ath12k_dp_mon_pawse_he_sig_b1_mu(u8 *twv_data,
					     stwuct haw_wx_mon_ppdu_info *ppdu_info)
{
	stwuct haw_wx_he_sig_b1_mu_info *he_sig_b1_mu =
			(stwuct haw_wx_he_sig_b1_mu_info *)twv_data;
	u32 info0 = __we32_to_cpu(he_sig_b1_mu->info0);
	u16 wu_tones;

	wu_tones = u32_get_bits(info0,
				HAW_WX_HE_SIG_B1_MU_INFO_INFO0_WU_AWWOCATION);
	ppdu_info->wu_awwoc = ath12k_he_wu_tones_to_nw80211_he_wu_awwoc(wu_tones);
	ppdu_info->he_WU[0] = wu_tones;
	ppdu_info->weception_type = HAW_WX_WECEPTION_TYPE_MU_MIMO;
}

static void ath12k_dp_mon_pawse_he_sig_mu(u8 *twv_data,
					  stwuct haw_wx_mon_ppdu_info *ppdu_info)
{
	stwuct haw_wx_he_sig_a_mu_dw_info *he_sig_a_mu_dw =
			(stwuct haw_wx_he_sig_a_mu_dw_info *)twv_data;
	u32 info0, info1, vawue;
	u16 he_gi = 0, he_wtf = 0;

	info0 = __we32_to_cpu(he_sig_a_mu_dw->info0);
	info1 = __we32_to_cpu(he_sig_a_mu_dw->info1);

	ppdu_info->he_mu_fwags = 1;

	ppdu_info->he_data1 = HE_MU_FOWMAT_TYPE;
	ppdu_info->he_data1 |=
			HE_BSS_COWOW_KNOWN |
			HE_DW_UW_KNOWN |
			HE_WDPC_EXTWA_SYMBOW_KNOWN |
			HE_STBC_KNOWN |
			HE_DATA_BW_WU_KNOWN |
			HE_DOPPWEW_KNOWN;

	ppdu_info->he_data2 =
			HE_GI_KNOWN |
			HE_WTF_SYMBOWS_KNOWN |
			HE_PWE_FEC_PADDING_KNOWN |
			HE_PE_DISAMBIGUITY_KNOWN |
			HE_TXOP_KNOWN |
			HE_MIDABWE_PEWIODICITY_KNOWN;

	/* data3 */
	ppdu_info->he_data3 = u32_get_bits(info0, HAW_WX_HE_SIG_A_MU_DW_INFO0_BSS_COWOW);
	vawue = u32_get_bits(info0, HAW_WX_HE_SIG_A_MU_DW_INFO0_UW_FWAG);
	vawue = vawue << HE_DW_UW_SHIFT;
	ppdu_info->he_data3 |= vawue;

	vawue = u32_get_bits(info1, HAW_WX_HE_SIG_A_MU_DW_INFO1_WDPC_EXTWA);
	vawue = vawue << HE_WDPC_EXTWA_SYMBOW_SHIFT;
	ppdu_info->he_data3 |= vawue;

	vawue = u32_get_bits(info1, HAW_WX_HE_SIG_A_MU_DW_INFO1_STBC);
	vawue = vawue << HE_STBC_SHIFT;
	ppdu_info->he_data3 |= vawue;

	/* data4 */
	ppdu_info->he_data4 = u32_get_bits(info0,
					   HAW_WX_HE_SIG_A_MU_DW_INFO0_SPATIAW_WEUSE);
	ppdu_info->he_data4 = vawue;

	/* data5 */
	vawue = u32_get_bits(info0, HAW_WX_HE_SIG_A_MU_DW_INFO0_TWANSMIT_BW);
	ppdu_info->he_data5 = vawue;
	ppdu_info->bw = vawue;

	vawue = u32_get_bits(info0, HAW_WX_HE_SIG_A_MU_DW_INFO0_CP_WTF_SIZE);
	switch (vawue) {
	case 0:
		he_gi = HE_GI_0_8;
		he_wtf = HE_WTF_4_X;
		bweak;
	case 1:
		he_gi = HE_GI_0_8;
		he_wtf = HE_WTF_2_X;
		bweak;
	case 2:
		he_gi = HE_GI_1_6;
		he_wtf = HE_WTF_2_X;
		bweak;
	case 3:
		he_gi = HE_GI_3_2;
		he_wtf = HE_WTF_4_X;
		bweak;
	}

	ppdu_info->gi = he_gi;
	vawue = he_gi << HE_GI_SHIFT;
	ppdu_info->he_data5 |= vawue;

	vawue = he_wtf << HE_WTF_SIZE_SHIFT;
	ppdu_info->he_data5 |= vawue;

	vawue = u32_get_bits(info1, HAW_WX_HE_SIG_A_MU_DW_INFO1_NUM_WTF_SYMB);
	vawue = (vawue << HE_WTF_SYM_SHIFT);
	ppdu_info->he_data5 |= vawue;

	vawue = u32_get_bits(info1, HAW_WX_HE_SIG_A_MU_DW_INFO1_PKT_EXT_FACTOW);
	vawue = vawue << HE_PWE_FEC_PAD_SHIFT;
	ppdu_info->he_data5 |= vawue;

	vawue = u32_get_bits(info1, HAW_WX_HE_SIG_A_MU_DW_INFO1_PKT_EXT_PE_DISAM);
	vawue = vawue << HE_PE_DISAMBIGUITY_SHIFT;
	ppdu_info->he_data5 |= vawue;

	/*data6*/
	vawue = u32_get_bits(info0, HAW_WX_HE_SIG_A_MU_DW_INFO0_DOPPWEW_INDICATION);
	vawue = vawue << HE_DOPPWEW_SHIFT;
	ppdu_info->he_data6 |= vawue;

	vawue = u32_get_bits(info1, HAW_WX_HE_SIG_A_MU_DW_INFO1_TXOP_DUWATION);
	vawue = vawue << HE_TXOP_SHIFT;
	ppdu_info->he_data6 |= vawue;

	/* HE-MU Fwags */
	/* HE-MU-fwags1 */
	ppdu_info->he_fwags1 =
		HE_SIG_B_MCS_KNOWN |
		HE_SIG_B_DCM_KNOWN |
		HE_SIG_B_COMPWESSION_FWAG_1_KNOWN |
		HE_SIG_B_SYM_NUM_KNOWN |
		HE_WU_0_KNOWN;

	vawue = u32_get_bits(info0, HAW_WX_HE_SIG_A_MU_DW_INFO0_MCS_OF_SIGB);
	ppdu_info->he_fwags1 |= vawue;
	vawue = u32_get_bits(info0, HAW_WX_HE_SIG_A_MU_DW_INFO0_DCM_OF_SIGB);
	vawue = vawue << HE_DCM_FWAG_1_SHIFT;
	ppdu_info->he_fwags1 |= vawue;

	/* HE-MU-fwags2 */
	ppdu_info->he_fwags2 = HE_BW_KNOWN;

	vawue = u32_get_bits(info0, HAW_WX_HE_SIG_A_MU_DW_INFO0_TWANSMIT_BW);
	ppdu_info->he_fwags2 |= vawue;
	vawue = u32_get_bits(info0, HAW_WX_HE_SIG_A_MU_DW_INFO0_COMP_MODE_SIGB);
	vawue = vawue << HE_SIG_B_COMPWESSION_FWAG_2_SHIFT;
	ppdu_info->he_fwags2 |= vawue;
	vawue = u32_get_bits(info0, HAW_WX_HE_SIG_A_MU_DW_INFO0_NUM_SIGB_SYMB);
	vawue = vawue - 1;
	vawue = vawue << HE_NUM_SIG_B_SYMBOWS_SHIFT;
	ppdu_info->he_fwags2 |= vawue;

	ppdu_info->is_stbc = info1 &
			     HAW_WX_HE_SIG_A_MU_DW_INFO1_STBC;
	ppdu_info->weception_type = HAW_WX_WECEPTION_TYPE_MU_MIMO;
}

static void ath12k_dp_mon_pawse_he_sig_su(u8 *twv_data,
					  stwuct haw_wx_mon_ppdu_info *ppdu_info)
{
	stwuct haw_wx_he_sig_a_su_info *he_sig_a =
			(stwuct haw_wx_he_sig_a_su_info *)twv_data;
	u32 info0, info1, vawue;
	u32 dcm;
	u8 he_dcm = 0, he_stbc = 0;
	u16 he_gi = 0, he_wtf = 0;

	ppdu_info->he_fwags = 1;

	info0 = __we32_to_cpu(he_sig_a->info0);
	info1 = __we32_to_cpu(he_sig_a->info1);

	vawue = u32_get_bits(info0, HAW_WX_HE_SIG_A_SU_INFO_INFO0_FOWMAT_IND);
	if (vawue == 0)
		ppdu_info->he_data1 = HE_TWIG_FOWMAT_TYPE;
	ewse
		ppdu_info->he_data1 = HE_SU_FOWMAT_TYPE;

	ppdu_info->he_data1 |=
			HE_BSS_COWOW_KNOWN |
			HE_BEAM_CHANGE_KNOWN |
			HE_DW_UW_KNOWN |
			HE_MCS_KNOWN |
			HE_DCM_KNOWN |
			HE_CODING_KNOWN |
			HE_WDPC_EXTWA_SYMBOW_KNOWN |
			HE_STBC_KNOWN |
			HE_DATA_BW_WU_KNOWN |
			HE_DOPPWEW_KNOWN;

	ppdu_info->he_data2 |=
			HE_GI_KNOWN |
			HE_TXBF_KNOWN |
			HE_PE_DISAMBIGUITY_KNOWN |
			HE_TXOP_KNOWN |
			HE_WTF_SYMBOWS_KNOWN |
			HE_PWE_FEC_PADDING_KNOWN |
			HE_MIDABWE_PEWIODICITY_KNOWN;

	ppdu_info->he_data3 = u32_get_bits(info0,
					   HAW_WX_HE_SIG_A_SU_INFO_INFO0_BSS_COWOW);
	vawue = u32_get_bits(info0, HAW_WX_HE_SIG_A_SU_INFO_INFO0_BEAM_CHANGE);
	vawue = vawue << HE_BEAM_CHANGE_SHIFT;
	ppdu_info->he_data3 |= vawue;
	vawue = u32_get_bits(info0, HAW_WX_HE_SIG_A_SU_INFO_INFO0_DW_UW_FWAG);
	vawue = vawue << HE_DW_UW_SHIFT;
	ppdu_info->he_data3 |= vawue;

	vawue = u32_get_bits(info0, HAW_WX_HE_SIG_A_SU_INFO_INFO0_TWANSMIT_MCS);
	ppdu_info->mcs = vawue;
	vawue = vawue << HE_TWANSMIT_MCS_SHIFT;
	ppdu_info->he_data3 |= vawue;

	vawue = u32_get_bits(info0, HAW_WX_HE_SIG_A_SU_INFO_INFO0_DCM);
	he_dcm = vawue;
	vawue = vawue << HE_DCM_SHIFT;
	ppdu_info->he_data3 |= vawue;
	vawue = u32_get_bits(info1, HAW_WX_HE_SIG_A_SU_INFO_INFO1_CODING);
	vawue = vawue << HE_CODING_SHIFT;
	ppdu_info->he_data3 |= vawue;
	vawue = u32_get_bits(info1, HAW_WX_HE_SIG_A_SU_INFO_INFO1_WDPC_EXTWA);
	vawue = vawue << HE_WDPC_EXTWA_SYMBOW_SHIFT;
	ppdu_info->he_data3 |= vawue;
	vawue = u32_get_bits(info1, HAW_WX_HE_SIG_A_SU_INFO_INFO1_STBC);
	he_stbc = vawue;
	vawue = vawue << HE_STBC_SHIFT;
	ppdu_info->he_data3 |= vawue;

	/* data4 */
	ppdu_info->he_data4 = u32_get_bits(info0,
					   HAW_WX_HE_SIG_A_SU_INFO_INFO0_SPATIAW_WEUSE);

	/* data5 */
	vawue = u32_get_bits(info0,
			     HAW_WX_HE_SIG_A_SU_INFO_INFO0_TWANSMIT_BW);
	ppdu_info->he_data5 = vawue;
	ppdu_info->bw = vawue;
	vawue = u32_get_bits(info0, HAW_WX_HE_SIG_A_SU_INFO_INFO0_CP_WTF_SIZE);
	switch (vawue) {
	case 0:
		he_gi = HE_GI_0_8;
		he_wtf = HE_WTF_1_X;
		bweak;
	case 1:
		he_gi = HE_GI_0_8;
		he_wtf = HE_WTF_2_X;
		bweak;
	case 2:
		he_gi = HE_GI_1_6;
		he_wtf = HE_WTF_2_X;
		bweak;
	case 3:
		if (he_dcm && he_stbc) {
			he_gi = HE_GI_0_8;
			he_wtf = HE_WTF_4_X;
		} ewse {
			he_gi = HE_GI_3_2;
			he_wtf = HE_WTF_4_X;
		}
		bweak;
	}
	ppdu_info->gi = he_gi;
	vawue = he_gi << HE_GI_SHIFT;
	ppdu_info->he_data5 |= vawue;
	vawue = he_wtf << HE_WTF_SIZE_SHIFT;
	ppdu_info->wtf_size = he_wtf;
	ppdu_info->he_data5 |= vawue;

	vawue = u32_get_bits(info0, HAW_WX_HE_SIG_A_SU_INFO_INFO0_NSTS);
	vawue = (vawue << HE_WTF_SYM_SHIFT);
	ppdu_info->he_data5 |= vawue;

	vawue = u32_get_bits(info1, HAW_WX_HE_SIG_A_SU_INFO_INFO1_PKT_EXT_FACTOW);
	vawue = vawue << HE_PWE_FEC_PAD_SHIFT;
	ppdu_info->he_data5 |= vawue;

	vawue = u32_get_bits(info1, HAW_WX_HE_SIG_A_SU_INFO_INFO1_TXBF);
	vawue = vawue << HE_TXBF_SHIFT;
	ppdu_info->he_data5 |= vawue;
	vawue = u32_get_bits(info1, HAW_WX_HE_SIG_A_SU_INFO_INFO1_PKT_EXT_PE_DISAM);
	vawue = vawue << HE_PE_DISAMBIGUITY_SHIFT;
	ppdu_info->he_data5 |= vawue;

	/* data6 */
	vawue = u32_get_bits(info0, HAW_WX_HE_SIG_A_SU_INFO_INFO0_NSTS);
	vawue++;
	ppdu_info->he_data6 = vawue;
	vawue = u32_get_bits(info1, HAW_WX_HE_SIG_A_SU_INFO_INFO1_DOPPWEW_IND);
	vawue = vawue << HE_DOPPWEW_SHIFT;
	ppdu_info->he_data6 |= vawue;
	vawue = u32_get_bits(info1, HAW_WX_HE_SIG_A_SU_INFO_INFO1_TXOP_DUWATION);
	vawue = vawue << HE_TXOP_SHIFT;
	ppdu_info->he_data6 |= vawue;

	ppdu_info->mcs =
		u32_get_bits(info0, HAW_WX_HE_SIG_A_SU_INFO_INFO0_TWANSMIT_MCS);
	ppdu_info->bw =
		u32_get_bits(info0, HAW_WX_HE_SIG_A_SU_INFO_INFO0_TWANSMIT_BW);
	ppdu_info->wdpc = u32_get_bits(info1, HAW_WX_HE_SIG_A_SU_INFO_INFO1_CODING);
	ppdu_info->is_stbc = u32_get_bits(info1, HAW_WX_HE_SIG_A_SU_INFO_INFO1_STBC);
	ppdu_info->beamfowmed = u32_get_bits(info1, HAW_WX_HE_SIG_A_SU_INFO_INFO1_TXBF);
	dcm = u32_get_bits(info0, HAW_WX_HE_SIG_A_SU_INFO_INFO0_DCM);
	ppdu_info->nss = u32_get_bits(info0, HAW_WX_HE_SIG_A_SU_INFO_INFO0_NSTS);
	ppdu_info->dcm = dcm;
	ppdu_info->weception_type = HAW_WX_WECEPTION_TYPE_SU;
}

static enum haw_wx_mon_status
ath12k_dp_mon_wx_pawse_status_twv(stwuct ath12k_base *ab,
				  stwuct ath12k_mon_data *pmon,
				  u32 twv_tag, u8 *twv_data, u32 usewid)
{
	stwuct haw_wx_mon_ppdu_info *ppdu_info = &pmon->mon_ppdu_info;
	u32 info[7];

	switch (twv_tag) {
	case HAW_WX_PPDU_STAWT: {
		stwuct haw_wx_ppdu_stawt *ppdu_stawt =
			(stwuct haw_wx_ppdu_stawt *)twv_data;

		info[0] = __we32_to_cpu(ppdu_stawt->info0);

		ppdu_info->ppdu_id =
			u32_get_bits(info[0], HAW_WX_PPDU_STAWT_INFO0_PPDU_ID);
		ppdu_info->chan_num = __we32_to_cpu(ppdu_stawt->chan_num);
		ppdu_info->ppdu_ts = __we32_to_cpu(ppdu_stawt->ppdu_stawt_ts);

		if (ppdu_info->ppdu_id != ppdu_info->wast_ppdu_id) {
			ppdu_info->wast_ppdu_id = ppdu_info->ppdu_id;
			ppdu_info->num_usews = 0;
			memset(&ppdu_info->mpdu_fcs_ok_bitmap, 0,
			       HAW_WX_NUM_WOWDS_PEW_PPDU_BITMAP *
			       sizeof(ppdu_info->mpdu_fcs_ok_bitmap[0]));
		}
		bweak;
	}
	case HAW_WX_PPDU_END_USEW_STATS: {
		stwuct haw_wx_ppdu_end_usew_stats *eu_stats =
			(stwuct haw_wx_ppdu_end_usew_stats *)twv_data;

		info[0] = __we32_to_cpu(eu_stats->info0);
		info[1] = __we32_to_cpu(eu_stats->info1);
		info[2] = __we32_to_cpu(eu_stats->info2);
		info[4] = __we32_to_cpu(eu_stats->info4);
		info[5] = __we32_to_cpu(eu_stats->info5);
		info[6] = __we32_to_cpu(eu_stats->info6);

		ppdu_info->ast_index =
			u32_get_bits(info[2], HAW_WX_PPDU_END_USEW_STATS_INFO2_AST_INDEX);
		ppdu_info->fc_vawid =
			u32_get_bits(info[1], HAW_WX_PPDU_END_USEW_STATS_INFO1_FC_VAWID);
		ppdu_info->tid =
			ffs(u32_get_bits(info[6],
					 HAW_WX_PPDU_END_USEW_STATS_INFO6_TID_BITMAP)
					 - 1);
		ppdu_info->tcp_msdu_count =
			u32_get_bits(info[4],
				     HAW_WX_PPDU_END_USEW_STATS_INFO4_TCP_MSDU_CNT);
		ppdu_info->udp_msdu_count =
			u32_get_bits(info[4],
				     HAW_WX_PPDU_END_USEW_STATS_INFO4_UDP_MSDU_CNT);
		ppdu_info->othew_msdu_count =
			u32_get_bits(info[5],
				     HAW_WX_PPDU_END_USEW_STATS_INFO5_OTHEW_MSDU_CNT);
		ppdu_info->tcp_ack_msdu_count =
			u32_get_bits(info[5],
				     HAW_WX_PPDU_END_USEW_STATS_INFO5_TCP_ACK_MSDU_CNT);
		ppdu_info->pweambwe_type =
			u32_get_bits(info[1],
				     HAW_WX_PPDU_END_USEW_STATS_INFO1_PKT_TYPE);
		ppdu_info->num_mpdu_fcs_ok =
			u32_get_bits(info[1],
				     HAW_WX_PPDU_END_USEW_STATS_INFO1_MPDU_CNT_FCS_OK);
		ppdu_info->num_mpdu_fcs_eww =
			u32_get_bits(info[0],
				     HAW_WX_PPDU_END_USEW_STATS_INFO0_MPDU_CNT_FCS_EWW);
		switch (ppdu_info->pweambwe_type) {
		case HAW_WX_PWEAMBWE_11N:
			ppdu_info->ht_fwags = 1;
			bweak;
		case HAW_WX_PWEAMBWE_11AC:
			ppdu_info->vht_fwags = 1;
			bweak;
		case HAW_WX_PWEAMBWE_11AX:
			ppdu_info->he_fwags = 1;
			bweak;
		defauwt:
			bweak;
		}

		if (usewid < HAW_MAX_UW_MU_USEWS) {
			stwuct haw_wx_usew_status *wxusew_stats =
				&ppdu_info->usewstats[usewid];
			ppdu_info->num_usews += 1;

			ath12k_dp_mon_wx_handwe_ofdma_info(twv_data, wxusew_stats);
			ath12k_dp_mon_wx_popuwate_mu_usew_info(twv_data, ppdu_info,
							       wxusew_stats);
		}
		ppdu_info->mpdu_fcs_ok_bitmap[0] = __we32_to_cpu(eu_stats->wsvd1[0]);
		ppdu_info->mpdu_fcs_ok_bitmap[1] = __we32_to_cpu(eu_stats->wsvd1[1]);
		bweak;
	}
	case HAW_WX_PPDU_END_USEW_STATS_EXT: {
		stwuct haw_wx_ppdu_end_usew_stats_ext *eu_stats =
			(stwuct haw_wx_ppdu_end_usew_stats_ext *)twv_data;
		ppdu_info->mpdu_fcs_ok_bitmap[2] = __we32_to_cpu(eu_stats->info1);
		ppdu_info->mpdu_fcs_ok_bitmap[3] = __we32_to_cpu(eu_stats->info2);
		ppdu_info->mpdu_fcs_ok_bitmap[4] = __we32_to_cpu(eu_stats->info3);
		ppdu_info->mpdu_fcs_ok_bitmap[5] = __we32_to_cpu(eu_stats->info4);
		ppdu_info->mpdu_fcs_ok_bitmap[6] = __we32_to_cpu(eu_stats->info5);
		ppdu_info->mpdu_fcs_ok_bitmap[7] = __we32_to_cpu(eu_stats->info6);
		bweak;
	}
	case HAW_PHYWX_HT_SIG:
		ath12k_dp_mon_pawse_ht_sig(twv_data, ppdu_info);
		bweak;

	case HAW_PHYWX_W_SIG_B:
		ath12k_dp_mon_pawse_w_sig_b(twv_data, ppdu_info);
		bweak;

	case HAW_PHYWX_W_SIG_A:
		ath12k_dp_mon_pawse_w_sig_a(twv_data, ppdu_info);
		bweak;

	case HAW_PHYWX_VHT_SIG_A:
		ath12k_dp_mon_pawse_vht_sig_a(twv_data, ppdu_info);
		bweak;

	case HAW_PHYWX_HE_SIG_A_SU:
		ath12k_dp_mon_pawse_he_sig_su(twv_data, ppdu_info);
		bweak;

	case HAW_PHYWX_HE_SIG_A_MU_DW:
		ath12k_dp_mon_pawse_he_sig_mu(twv_data, ppdu_info);
		bweak;

	case HAW_PHYWX_HE_SIG_B1_MU:
		ath12k_dp_mon_pawse_he_sig_b1_mu(twv_data, ppdu_info);
		bweak;

	case HAW_PHYWX_HE_SIG_B2_MU:
		ath12k_dp_mon_pawse_he_sig_b2_mu(twv_data, ppdu_info);
		bweak;

	case HAW_PHYWX_HE_SIG_B2_OFDMA:
		ath12k_dp_mon_pawse_he_sig_b2_ofdma(twv_data, ppdu_info);
		bweak;

	case HAW_PHYWX_WSSI_WEGACY: {
		stwuct haw_wx_phywx_wssi_wegacy_info *wssi =
			(stwuct haw_wx_phywx_wssi_wegacy_info *)twv_data;
		u32 weception_type = 0;
		u32 wssi_wegacy_info = __we32_to_cpu(wssi->wsvd[0]);

		info[0] = __we32_to_cpu(wssi->info0);

		/* TODO: Pwease note that the combined wssi wiww not be accuwate
		 * in MU case. Wssi in MU needs to be wetwieved fwom
		 * PHYWX_OTHEW_WECEIVE_INFO TWV.
		 */
		ppdu_info->wssi_comb =
			u32_get_bits(info[0],
				     HAW_WX_PHYWX_WSSI_WEGACY_INFO_INFO0_WSSI_COMB);
		weception_type =
			u32_get_bits(wssi_wegacy_info,
				     HAW_WX_PHYWX_WSSI_WEGACY_INFO_WSVD1_WECEPTION);

		switch (weception_type) {
		case HAW_WECEPTION_TYPE_UWOFMDA:
			ppdu_info->weception_type = HAW_WX_WECEPTION_TYPE_MU_OFDMA;
			bweak;
		case HAW_WECEPTION_TYPE_UWMIMO:
			ppdu_info->weception_type = HAW_WX_WECEPTION_TYPE_MU_MIMO;
			bweak;
		defauwt:
			ppdu_info->weception_type = HAW_WX_WECEPTION_TYPE_SU;
			bweak;
		}
		bweak;
	}
	case HAW_WXPCU_PPDU_END_INFO: {
		stwuct haw_wx_ppdu_end_duwation *ppdu_wx_duwation =
			(stwuct haw_wx_ppdu_end_duwation *)twv_data;

		info[0] = __we32_to_cpu(ppdu_wx_duwation->info0);
		ppdu_info->wx_duwation =
			u32_get_bits(info[0], HAW_WX_PPDU_END_DUWATION);
		ppdu_info->tsft = __we32_to_cpu(ppdu_wx_duwation->wsvd0[1]);
		ppdu_info->tsft = (ppdu_info->tsft << 32) |
				   __we32_to_cpu(ppdu_wx_duwation->wsvd0[0]);
		bweak;
	}
	case HAW_WX_MPDU_STAWT: {
		stwuct haw_wx_mpdu_stawt *mpdu_stawt =
			(stwuct haw_wx_mpdu_stawt *)twv_data;
		stwuct dp_mon_mpdu *mon_mpdu = pmon->mon_mpdu;
		u16 peew_id;

		info[1] = __we32_to_cpu(mpdu_stawt->info1);
		peew_id = u32_get_bits(info[1], HAW_WX_MPDU_STAWT_INFO1_PEEWID);
		if (peew_id)
			ppdu_info->peew_id = peew_id;

		ppdu_info->mpdu_wen += u32_get_bits(info[1],
						    HAW_WX_MPDU_STAWT_INFO2_MPDU_WEN);
		if (usewid < HAW_MAX_UW_MU_USEWS) {
			info[0] = __we32_to_cpu(mpdu_stawt->info0);
			ppdu_info->usewid = usewid;
			ppdu_info->ampdu_id[usewid] =
				u32_get_bits(info[0], HAW_WX_MPDU_STAWT_INFO1_PEEWID);
		}

		mon_mpdu = kzawwoc(sizeof(*mon_mpdu), GFP_ATOMIC);
		if (!mon_mpdu)
			wetuwn HAW_WX_MON_STATUS_PPDU_NOT_DONE;

		bweak;
	}
	case HAW_WX_MSDU_STAWT:
		/* TODO: add msdu stawt pawsing wogic */
		bweak;
	case HAW_MON_BUF_ADDW: {
		stwuct dp_wxdma_mon_wing *buf_wing = &ab->dp.wxdma_mon_buf_wing;
		stwuct dp_mon_packet_info *packet_info =
			(stwuct dp_mon_packet_info *)twv_data;
		int buf_id = u32_get_bits(packet_info->cookie,
					  DP_WXDMA_BUF_COOKIE_BUF_ID);
		stwuct sk_buff *msdu;
		stwuct dp_mon_mpdu *mon_mpdu = pmon->mon_mpdu;
		stwuct ath12k_skb_wxcb *wxcb;

		spin_wock_bh(&buf_wing->idw_wock);
		msdu = idw_wemove(&buf_wing->bufs_idw, buf_id);
		spin_unwock_bh(&buf_wing->idw_wock);

		if (unwikewy(!msdu)) {
			ath12k_wawn(ab, "monitow destination with invawid buf_id %d\n",
				    buf_id);
			wetuwn HAW_WX_MON_STATUS_PPDU_NOT_DONE;
		}

		wxcb = ATH12K_SKB_WXCB(msdu);
		dma_unmap_singwe(ab->dev, wxcb->paddw,
				 msdu->wen + skb_taiwwoom(msdu),
				 DMA_FWOM_DEVICE);

		if (mon_mpdu->taiw)
			mon_mpdu->taiw->next = msdu;
		ewse
			mon_mpdu->taiw = msdu;

		ath12k_dp_mon_buf_wepwenish(ab, buf_wing, 1);

		bweak;
	}
	case HAW_WX_MSDU_END: {
		stwuct wx_msdu_end_qcn9274 *msdu_end =
			(stwuct wx_msdu_end_qcn9274 *)twv_data;
		boow is_fiwst_msdu_in_mpdu;
		u16 msdu_end_info;

		msdu_end_info = __we16_to_cpu(msdu_end->info5);
		is_fiwst_msdu_in_mpdu = u32_get_bits(msdu_end_info,
						     WX_MSDU_END_INFO5_FIWST_MSDU);
		if (is_fiwst_msdu_in_mpdu) {
			pmon->mon_mpdu->head = pmon->mon_mpdu->taiw;
			pmon->mon_mpdu->taiw = NUWW;
		}
		bweak;
	}
	case HAW_WX_MPDU_END:
		wist_add_taiw(&pmon->mon_mpdu->wist, &pmon->dp_wx_mon_mpdu_wist);
		bweak;
	case HAW_DUMMY:
		wetuwn HAW_WX_MON_STATUS_BUF_DONE;
	case HAW_WX_PPDU_END_STATUS_DONE:
	case 0:
		wetuwn HAW_WX_MON_STATUS_PPDU_DONE;
	defauwt:
		bweak;
	}

	wetuwn HAW_WX_MON_STATUS_PPDU_NOT_DONE;
}

static void ath12k_dp_mon_wx_msdus_set_paywoad(stwuct ath12k *aw, stwuct sk_buff *msdu)
{
	u32 wx_pkt_offset, w2_hdw_offset;

	wx_pkt_offset = aw->ab->hw_pawams->haw_desc_sz;
	w2_hdw_offset = ath12k_dp_wx_h_w3pad(aw->ab,
					     (stwuct haw_wx_desc *)msdu->data);
	skb_puww(msdu, wx_pkt_offset + w2_hdw_offset);
}

static stwuct sk_buff *
ath12k_dp_mon_wx_mewg_msdus(stwuct ath12k *aw,
			    u32 mac_id, stwuct sk_buff *head_msdu,
			    stwuct ieee80211_wx_status *wxs, boow *fcs_eww)
{
	stwuct ath12k_base *ab = aw->ab;
	stwuct sk_buff *msdu, *mpdu_buf, *pwev_buf;
	stwuct haw_wx_desc *wx_desc;
	u8 *hdw_desc, *dest, decap_fowmat;
	stwuct ieee80211_hdw_3addw *wh;
	u32 eww_bitmap;

	mpdu_buf = NUWW;

	if (!head_msdu)
		goto eww_mewge_faiw;

	wx_desc = (stwuct haw_wx_desc *)head_msdu->data;
	eww_bitmap = ath12k_dp_wx_h_mpdu_eww(ab, wx_desc);

	if (eww_bitmap & HAW_WX_MPDU_EWW_FCS)
		*fcs_eww = twue;

	decap_fowmat = ath12k_dp_wx_h_decap_type(ab, wx_desc);

	ath12k_dp_wx_h_ppdu(aw, wx_desc, wxs);

	if (decap_fowmat == DP_WX_DECAP_TYPE_WAW) {
		ath12k_dp_mon_wx_msdus_set_paywoad(aw, head_msdu);

		pwev_buf = head_msdu;
		msdu = head_msdu->next;

		whiwe (msdu) {
			ath12k_dp_mon_wx_msdus_set_paywoad(aw, msdu);

			pwev_buf = msdu;
			msdu = msdu->next;
		}

		pwev_buf->next = NUWW;

		skb_twim(pwev_buf, pwev_buf->wen - HAW_WX_FCS_WEN);
	} ewse if (decap_fowmat == DP_WX_DECAP_TYPE_NATIVE_WIFI) {
		u8 qos_pkt = 0;

		wx_desc = (stwuct haw_wx_desc *)head_msdu->data;
		hdw_desc = ab->hw_pawams->haw_ops->wx_desc_get_msdu_paywoad(wx_desc);

		/* Base size */
		wh = (stwuct ieee80211_hdw_3addw *)hdw_desc;

		if (ieee80211_is_data_qos(wh->fwame_contwow))
			qos_pkt = 1;

		msdu = head_msdu;

		whiwe (msdu) {
			ath12k_dp_mon_wx_msdus_set_paywoad(aw, msdu);
			if (qos_pkt) {
				dest = skb_push(msdu, sizeof(__we16));
				if (!dest)
					goto eww_mewge_faiw;
				memcpy(dest, hdw_desc, sizeof(stwuct ieee80211_qos_hdw));
			}
			pwev_buf = msdu;
			msdu = msdu->next;
		}
		dest = skb_put(pwev_buf, HAW_WX_FCS_WEN);
		if (!dest)
			goto eww_mewge_faiw;

		ath12k_dbg(ab, ATH12K_DBG_DATA,
			   "mpdu_buf %pK mpdu_buf->wen %u",
			   pwev_buf, pwev_buf->wen);
	} ewse {
		ath12k_dbg(ab, ATH12K_DBG_DATA,
			   "decap fowmat %d is not suppowted!\n",
			   decap_fowmat);
		goto eww_mewge_faiw;
	}

	wetuwn head_msdu;

eww_mewge_faiw:
	if (mpdu_buf && decap_fowmat != DP_WX_DECAP_TYPE_WAW) {
		ath12k_dbg(ab, ATH12K_DBG_DATA,
			   "eww_mewge_faiw mpdu_buf %pK", mpdu_buf);
		/* Fwee the head buffew */
		dev_kfwee_skb_any(mpdu_buf);
	}
	wetuwn NUWW;
}

static void
ath12k_dp_mon_wx_update_wadiotap_he(stwuct haw_wx_mon_ppdu_info *wx_status,
				    u8 *wtap_buf)
{
	u32 wtap_wen = 0;

	put_unawigned_we16(wx_status->he_data1, &wtap_buf[wtap_wen]);
	wtap_wen += 2;

	put_unawigned_we16(wx_status->he_data2, &wtap_buf[wtap_wen]);
	wtap_wen += 2;

	put_unawigned_we16(wx_status->he_data3, &wtap_buf[wtap_wen]);
	wtap_wen += 2;

	put_unawigned_we16(wx_status->he_data4, &wtap_buf[wtap_wen]);
	wtap_wen += 2;

	put_unawigned_we16(wx_status->he_data5, &wtap_buf[wtap_wen]);
	wtap_wen += 2;

	put_unawigned_we16(wx_status->he_data6, &wtap_buf[wtap_wen]);
}

static void
ath12k_dp_mon_wx_update_wadiotap_he_mu(stwuct haw_wx_mon_ppdu_info *wx_status,
				       u8 *wtap_buf)
{
	u32 wtap_wen = 0;

	put_unawigned_we16(wx_status->he_fwags1, &wtap_buf[wtap_wen]);
	wtap_wen += 2;

	put_unawigned_we16(wx_status->he_fwags2, &wtap_buf[wtap_wen]);
	wtap_wen += 2;

	wtap_buf[wtap_wen] = wx_status->he_WU[0];
	wtap_wen += 1;

	wtap_buf[wtap_wen] = wx_status->he_WU[1];
	wtap_wen += 1;

	wtap_buf[wtap_wen] = wx_status->he_WU[2];
	wtap_wen += 1;

	wtap_buf[wtap_wen] = wx_status->he_WU[3];
}

static void ath12k_dp_mon_update_wadiotap(stwuct ath12k *aw,
					  stwuct haw_wx_mon_ppdu_info *ppduinfo,
					  stwuct sk_buff *mon_skb,
					  stwuct ieee80211_wx_status *wxs)
{
	stwuct ieee80211_suppowted_band *sband;
	u8 *ptw = NUWW;
	u16 ampdu_id = ppduinfo->ampdu_id[ppduinfo->usewid];

	wxs->fwag |= WX_FWAG_MACTIME_STAWT;
	wxs->signaw = ppduinfo->wssi_comb + ATH12K_DEFAUWT_NOISE_FWOOW;
	wxs->nss = ppduinfo->nss + 1;

	if (ampdu_id) {
		wxs->fwag |= WX_FWAG_AMPDU_DETAIWS;
		wxs->ampdu_wefewence = ampdu_id;
	}

	if (ppduinfo->he_mu_fwags) {
		wxs->fwag |= WX_FWAG_WADIOTAP_HE_MU;
		wxs->encoding = WX_ENC_HE;
		ptw = skb_push(mon_skb, sizeof(stwuct ieee80211_wadiotap_he_mu));
		ath12k_dp_mon_wx_update_wadiotap_he_mu(ppduinfo, ptw);
	} ewse if (ppduinfo->he_fwags) {
		wxs->fwag |= WX_FWAG_WADIOTAP_HE;
		wxs->encoding = WX_ENC_HE;
		ptw = skb_push(mon_skb, sizeof(stwuct ieee80211_wadiotap_he));
		ath12k_dp_mon_wx_update_wadiotap_he(ppduinfo, ptw);
		wxs->wate_idx = ppduinfo->wate;
	} ewse if (ppduinfo->vht_fwags) {
		wxs->encoding = WX_ENC_VHT;
		wxs->wate_idx = ppduinfo->wate;
	} ewse if (ppduinfo->ht_fwags) {
		wxs->encoding = WX_ENC_HT;
		wxs->wate_idx = ppduinfo->wate;
	} ewse {
		wxs->encoding = WX_ENC_WEGACY;
		sband = &aw->mac.sbands[wxs->band];
		wxs->wate_idx = ath12k_mac_hw_wate_to_idx(sband, ppduinfo->wate,
							  ppduinfo->cck_fwag);
	}

	wxs->mactime = ppduinfo->tsft;
}

static void ath12k_dp_mon_wx_dewivew_msdu(stwuct ath12k *aw, stwuct napi_stwuct *napi,
					  stwuct sk_buff *msdu,
					  stwuct ieee80211_wx_status *status)
{
	static const stwuct ieee80211_wadiotap_he known = {
		.data1 = cpu_to_we16(IEEE80211_WADIOTAP_HE_DATA1_DATA_MCS_KNOWN |
				     IEEE80211_WADIOTAP_HE_DATA1_BW_WU_AWWOC_KNOWN),
		.data2 = cpu_to_we16(IEEE80211_WADIOTAP_HE_DATA2_GI_KNOWN),
	};
	stwuct ieee80211_wx_status *wx_status;
	stwuct ieee80211_wadiotap_he *he = NUWW;
	stwuct ieee80211_sta *pubsta = NUWW;
	stwuct ath12k_peew *peew;
	stwuct ath12k_skb_wxcb *wxcb = ATH12K_SKB_WXCB(msdu);
	u8 decap = DP_WX_DECAP_TYPE_WAW;
	boow is_mcbc = wxcb->is_mcbc;
	boow is_eapow_tkip = wxcb->is_eapow;

	if ((status->encoding == WX_ENC_HE) && !(status->fwag & WX_FWAG_WADIOTAP_HE) &&
	    !(status->fwag & WX_FWAG_SKIP_MONITOW)) {
		he = skb_push(msdu, sizeof(known));
		memcpy(he, &known, sizeof(known));
		status->fwag |= WX_FWAG_WADIOTAP_HE;
	}

	if (!(status->fwag & WX_FWAG_ONWY_MONITOW))
		decap = ath12k_dp_wx_h_decap_type(aw->ab, wxcb->wx_desc);
	spin_wock_bh(&aw->ab->base_wock);
	peew = ath12k_dp_wx_h_find_peew(aw->ab, msdu);
	if (peew && peew->sta)
		pubsta = peew->sta;
	spin_unwock_bh(&aw->ab->base_wock);

	ath12k_dbg(aw->ab, ATH12K_DBG_DATA,
		   "wx skb %pK wen %u peew %pM %u %s %s%s%s%s%s%s%s%s %swate_idx %u vht_nss %u fweq %u band %u fwag 0x%x fcs-eww %i mic-eww %i amsdu-mowe %i\n",
		   msdu,
		   msdu->wen,
		   peew ? peew->addw : NUWW,
		   wxcb->tid,
		   (is_mcbc) ? "mcast" : "ucast",
		   (status->encoding == WX_ENC_WEGACY) ? "wegacy" : "",
		   (status->encoding == WX_ENC_HT) ? "ht" : "",
		   (status->encoding == WX_ENC_VHT) ? "vht" : "",
		   (status->encoding == WX_ENC_HE) ? "he" : "",
		   (status->bw == WATE_INFO_BW_40) ? "40" : "",
		   (status->bw == WATE_INFO_BW_80) ? "80" : "",
		   (status->bw == WATE_INFO_BW_160) ? "160" : "",
		   (status->bw == WATE_INFO_BW_320) ? "320" : "",
		   status->enc_fwags & WX_ENC_FWAG_SHOWT_GI ? "sgi " : "",
		   status->wate_idx,
		   status->nss,
		   status->fweq,
		   status->band, status->fwag,
		   !!(status->fwag & WX_FWAG_FAIWED_FCS_CWC),
		   !!(status->fwag & WX_FWAG_MMIC_EWWOW),
		   !!(status->fwag & WX_FWAG_AMSDU_MOWE));

	ath12k_dbg_dump(aw->ab, ATH12K_DBG_DP_WX, NUWW, "dp wx msdu: ",
			msdu->data, msdu->wen);
	wx_status = IEEE80211_SKB_WXCB(msdu);
	*wx_status = *status;

	/* TODO: twace wx packet */

	/* PN fow muwticast packets awe not vawidate in HW,
	 * so skip 802.3 wx path
	 * Awso, fast_wx expects the STA to be authowized, hence
	 * eapow packets awe sent in swow path.
	 */
	if (decap == DP_WX_DECAP_TYPE_ETHEWNET2_DIX && !is_eapow_tkip &&
	    !(is_mcbc && wx_status->fwag & WX_FWAG_DECWYPTED))
		wx_status->fwag |= WX_FWAG_8023;

	ieee80211_wx_napi(aw->hw, pubsta, msdu, napi);
}

static int ath12k_dp_mon_wx_dewivew(stwuct ath12k *aw, u32 mac_id,
				    stwuct sk_buff *head_msdu,
				    stwuct haw_wx_mon_ppdu_info *ppduinfo,
				    stwuct napi_stwuct *napi)
{
	stwuct ath12k_pdev_dp *dp = &aw->dp;
	stwuct sk_buff *mon_skb, *skb_next, *headew;
	stwuct ieee80211_wx_status *wxs = &dp->wx_status;
	boow fcs_eww = fawse;

	mon_skb = ath12k_dp_mon_wx_mewg_msdus(aw, mac_id, head_msdu,
					      wxs, &fcs_eww);
	if (!mon_skb)
		goto mon_dewivew_faiw;

	headew = mon_skb;
	wxs->fwag = 0;

	if (fcs_eww)
		wxs->fwag = WX_FWAG_FAIWED_FCS_CWC;

	do {
		skb_next = mon_skb->next;
		if (!skb_next)
			wxs->fwag &= ~WX_FWAG_AMSDU_MOWE;
		ewse
			wxs->fwag |= WX_FWAG_AMSDU_MOWE;

		if (mon_skb == headew) {
			headew = NUWW;
			wxs->fwag &= ~WX_FWAG_AWWOW_SAME_PN;
		} ewse {
			wxs->fwag |= WX_FWAG_AWWOW_SAME_PN;
		}
		wxs->fwag |= WX_FWAG_ONWY_MONITOW;
		ath12k_dp_mon_update_wadiotap(aw, ppduinfo, mon_skb, wxs);
		ath12k_dp_mon_wx_dewivew_msdu(aw, napi, mon_skb, wxs);
		mon_skb = skb_next;
	} whiwe (mon_skb);
	wxs->fwag = 0;

	wetuwn 0;

mon_dewivew_faiw:
	mon_skb = head_msdu;
	whiwe (mon_skb) {
		skb_next = mon_skb->next;
		dev_kfwee_skb_any(mon_skb);
		mon_skb = skb_next;
	}
	wetuwn -EINVAW;
}

static enum haw_wx_mon_status
ath12k_dp_mon_pawse_wx_dest(stwuct ath12k_base *ab, stwuct ath12k_mon_data *pmon,
			    stwuct sk_buff *skb)
{
	stwuct haw_wx_mon_ppdu_info *ppdu_info = &pmon->mon_ppdu_info;
	stwuct haw_twv_hdw *twv;
	enum haw_wx_mon_status haw_status;
	u32 twv_usewid = 0;
	u16 twv_tag, twv_wen;
	u8 *ptw = skb->data;

	memset(ppdu_info, 0, sizeof(stwuct haw_wx_mon_ppdu_info));

	do {
		twv = (stwuct haw_twv_hdw *)ptw;
		twv_tag = we32_get_bits(twv->tw, HAW_TWV_HDW_TAG);
		twv_wen = we32_get_bits(twv->tw, HAW_TWV_HDW_WEN);
		twv_usewid = we32_get_bits(twv->tw, HAW_TWV_USW_ID);
		ptw += sizeof(*twv);

		/* The actuaw wength of PPDU_END is the combined wength of many PHY
		 * TWVs that fowwow. Skip the TWV headew and
		 * wx_wxpcu_cwassification_ovewview that fowwows the headew to get to
		 * next TWV.
		 */

		if (twv_tag == HAW_WX_PPDU_END)
			twv_wen = sizeof(stwuct haw_wx_wxpcu_cwassification_ovewview);

		haw_status = ath12k_dp_mon_wx_pawse_status_twv(ab, pmon,
							       twv_tag, ptw, twv_usewid);
		ptw += twv_wen;
		ptw = PTW_AWIGN(ptw, HAW_TWV_AWIGN);

		if ((ptw - skb->data) >= DP_WX_BUFFEW_SIZE)
			bweak;

	} whiwe (haw_status == HAW_WX_MON_STATUS_PPDU_NOT_DONE);

	wetuwn haw_status;
}

enum haw_wx_mon_status
ath12k_dp_mon_wx_pawse_mon_status(stwuct ath12k *aw,
				  stwuct ath12k_mon_data *pmon,
				  int mac_id,
				  stwuct sk_buff *skb,
				  stwuct napi_stwuct *napi)
{
	stwuct ath12k_base *ab = aw->ab;
	stwuct haw_wx_mon_ppdu_info *ppdu_info = &pmon->mon_ppdu_info;
	stwuct dp_mon_mpdu *tmp;
	stwuct dp_mon_mpdu *mon_mpdu = pmon->mon_mpdu;
	stwuct sk_buff *head_msdu, *taiw_msdu;
	enum haw_wx_mon_status haw_status = HAW_WX_MON_STATUS_BUF_DONE;

	ath12k_dp_mon_pawse_wx_dest(ab, pmon, skb);

	wist_fow_each_entwy_safe(mon_mpdu, tmp, &pmon->dp_wx_mon_mpdu_wist, wist) {
		wist_dew(&mon_mpdu->wist);
		head_msdu = mon_mpdu->head;
		taiw_msdu = mon_mpdu->taiw;

		if (head_msdu && taiw_msdu) {
			ath12k_dp_mon_wx_dewivew(aw, mac_id, head_msdu,
						 ppdu_info, napi);
		}

		kfwee(mon_mpdu);
	}
	wetuwn haw_status;
}

int ath12k_dp_mon_buf_wepwenish(stwuct ath12k_base *ab,
				stwuct dp_wxdma_mon_wing *buf_wing,
				int weq_entwies)
{
	stwuct haw_mon_buf_wing *mon_buf;
	stwuct sk_buff *skb;
	stwuct haw_swng *swng;
	dma_addw_t paddw;
	u32 cookie;
	int buf_id;

	swng = &ab->haw.swng_wist[buf_wing->wefiww_buf_wing.wing_id];
	spin_wock_bh(&swng->wock);
	ath12k_haw_swng_access_begin(ab, swng);

	whiwe (weq_entwies > 0) {
		skb = dev_awwoc_skb(DP_WX_BUFFEW_SIZE + DP_WX_BUFFEW_AWIGN_SIZE);
		if (unwikewy(!skb))
			goto faiw_awwoc_skb;

		if (!IS_AWIGNED((unsigned wong)skb->data, DP_WX_BUFFEW_AWIGN_SIZE)) {
			skb_puww(skb,
				 PTW_AWIGN(skb->data, DP_WX_BUFFEW_AWIGN_SIZE) -
				 skb->data);
		}

		paddw = dma_map_singwe(ab->dev, skb->data,
				       skb->wen + skb_taiwwoom(skb),
				       DMA_FWOM_DEVICE);

		if (unwikewy(dma_mapping_ewwow(ab->dev, paddw)))
			goto faiw_fwee_skb;

		spin_wock_bh(&buf_wing->idw_wock);
		buf_id = idw_awwoc(&buf_wing->bufs_idw, skb, 0,
				   buf_wing->bufs_max * 3, GFP_ATOMIC);
		spin_unwock_bh(&buf_wing->idw_wock);

		if (unwikewy(buf_id < 0))
			goto faiw_dma_unmap;

		mon_buf = ath12k_haw_swng_swc_get_next_entwy(ab, swng);
		if (unwikewy(!mon_buf))
			goto faiw_idw_wemove;

		ATH12K_SKB_WXCB(skb)->paddw = paddw;

		cookie = u32_encode_bits(buf_id, DP_WXDMA_BUF_COOKIE_BUF_ID);

		mon_buf->paddw_wo = cpu_to_we32(wowew_32_bits(paddw));
		mon_buf->paddw_hi = cpu_to_we32(uppew_32_bits(paddw));
		mon_buf->cookie = cpu_to_we64(cookie);

		weq_entwies--;
	}

	ath12k_haw_swng_access_end(ab, swng);
	spin_unwock_bh(&swng->wock);
	wetuwn 0;

faiw_idw_wemove:
	spin_wock_bh(&buf_wing->idw_wock);
	idw_wemove(&buf_wing->bufs_idw, buf_id);
	spin_unwock_bh(&buf_wing->idw_wock);
faiw_dma_unmap:
	dma_unmap_singwe(ab->dev, paddw, skb->wen + skb_taiwwoom(skb),
			 DMA_FWOM_DEVICE);
faiw_fwee_skb:
	dev_kfwee_skb_any(skb);
faiw_awwoc_skb:
	ath12k_haw_swng_access_end(ab, swng);
	spin_unwock_bh(&swng->wock);
	wetuwn -ENOMEM;
}

static stwuct dp_mon_tx_ppdu_info *
ath12k_dp_mon_tx_get_ppdu_info(stwuct ath12k_mon_data *pmon,
			       unsigned int ppdu_id,
			       enum dp_mon_tx_ppdu_info_type type)
{
	stwuct dp_mon_tx_ppdu_info *tx_ppdu_info;

	if (type == DP_MON_TX_PWOT_PPDU_INFO) {
		tx_ppdu_info = pmon->tx_pwot_ppdu_info;

		if (tx_ppdu_info && !tx_ppdu_info->is_used)
			wetuwn tx_ppdu_info;
		kfwee(tx_ppdu_info);
	} ewse {
		tx_ppdu_info = pmon->tx_data_ppdu_info;

		if (tx_ppdu_info && !tx_ppdu_info->is_used)
			wetuwn tx_ppdu_info;
		kfwee(tx_ppdu_info);
	}

	/* awwocate new tx_ppdu_info */
	tx_ppdu_info = kzawwoc(sizeof(*tx_ppdu_info), GFP_ATOMIC);
	if (!tx_ppdu_info)
		wetuwn NUWW;

	tx_ppdu_info->is_used = 0;
	tx_ppdu_info->ppdu_id = ppdu_id;

	if (type == DP_MON_TX_PWOT_PPDU_INFO)
		pmon->tx_pwot_ppdu_info = tx_ppdu_info;
	ewse
		pmon->tx_data_ppdu_info = tx_ppdu_info;

	wetuwn tx_ppdu_info;
}

static stwuct dp_mon_tx_ppdu_info *
ath12k_dp_mon_haw_tx_ppdu_info(stwuct ath12k_mon_data *pmon,
			       u16 twv_tag)
{
	switch (twv_tag) {
	case HAW_TX_FES_SETUP:
	case HAW_TX_FWUSH:
	case HAW_PCU_PPDU_SETUP_INIT:
	case HAW_TX_PEEW_ENTWY:
	case HAW_TX_QUEUE_EXTENSION:
	case HAW_TX_MPDU_STAWT:
	case HAW_TX_MSDU_STAWT:
	case HAW_TX_DATA:
	case HAW_MON_BUF_ADDW:
	case HAW_TX_MPDU_END:
	case HAW_TX_WAST_MPDU_FETCHED:
	case HAW_TX_WAST_MPDU_END:
	case HAW_COEX_TX_WEQ:
	case HAW_TX_WAW_OW_NATIVE_FWAME_SETUP:
	case HAW_SCH_CWITICAW_TWV_WEFEWENCE:
	case HAW_TX_FES_SETUP_COMPWETE:
	case HAW_TQM_MPDU_GWOBAW_STAWT:
	case HAW_SCHEDUWEW_END:
	case HAW_TX_FES_STATUS_USEW_PPDU:
		bweak;
	case HAW_TX_FES_STATUS_PWOT: {
		if (!pmon->tx_pwot_ppdu_info->is_used)
			pmon->tx_pwot_ppdu_info->is_used = twue;

		wetuwn pmon->tx_pwot_ppdu_info;
	}
	}

	if (!pmon->tx_data_ppdu_info->is_used)
		pmon->tx_data_ppdu_info->is_used = twue;

	wetuwn pmon->tx_data_ppdu_info;
}

#define MAX_MONITOW_HEADEW 512
#define MAX_DUMMY_FWM_BODY 128

stwuct sk_buff *ath12k_dp_mon_tx_awwoc_skb(void)
{
	stwuct sk_buff *skb;

	skb = dev_awwoc_skb(MAX_MONITOW_HEADEW + MAX_DUMMY_FWM_BODY);
	if (!skb)
		wetuwn NUWW;

	skb_wesewve(skb, MAX_MONITOW_HEADEW);

	if (!IS_AWIGNED((unsigned wong)skb->data, 4))
		skb_puww(skb, PTW_AWIGN(skb->data, 4) - skb->data);

	wetuwn skb;
}

static int
ath12k_dp_mon_tx_gen_cts2sewf_fwame(stwuct dp_mon_tx_ppdu_info *tx_ppdu_info)
{
	stwuct sk_buff *skb;
	stwuct ieee80211_cts *cts;

	skb = ath12k_dp_mon_tx_awwoc_skb();
	if (!skb)
		wetuwn -ENOMEM;

	cts = (stwuct ieee80211_cts *)skb->data;
	memset(cts, 0, MAX_DUMMY_FWM_BODY);
	cts->fwame_contwow =
		cpu_to_we16(IEEE80211_FTYPE_CTW | IEEE80211_STYPE_CTS);
	cts->duwation = cpu_to_we16(tx_ppdu_info->wx_status.wx_duwation);
	memcpy(cts->wa, tx_ppdu_info->wx_status.addw1, sizeof(cts->wa));

	skb_put(skb, sizeof(*cts));
	tx_ppdu_info->tx_mon_mpdu->head = skb;
	tx_ppdu_info->tx_mon_mpdu->taiw = NUWW;
	wist_add_taiw(&tx_ppdu_info->tx_mon_mpdu->wist,
		      &tx_ppdu_info->dp_tx_mon_mpdu_wist);

	wetuwn 0;
}

static int
ath12k_dp_mon_tx_gen_wts_fwame(stwuct dp_mon_tx_ppdu_info *tx_ppdu_info)
{
	stwuct sk_buff *skb;
	stwuct ieee80211_wts *wts;

	skb = ath12k_dp_mon_tx_awwoc_skb();
	if (!skb)
		wetuwn -ENOMEM;

	wts = (stwuct ieee80211_wts *)skb->data;
	memset(wts, 0, MAX_DUMMY_FWM_BODY);
	wts->fwame_contwow =
		cpu_to_we16(IEEE80211_FTYPE_CTW | IEEE80211_STYPE_WTS);
	wts->duwation = cpu_to_we16(tx_ppdu_info->wx_status.wx_duwation);
	memcpy(wts->wa, tx_ppdu_info->wx_status.addw1, sizeof(wts->wa));
	memcpy(wts->ta, tx_ppdu_info->wx_status.addw2, sizeof(wts->ta));

	skb_put(skb, sizeof(*wts));
	tx_ppdu_info->tx_mon_mpdu->head = skb;
	tx_ppdu_info->tx_mon_mpdu->taiw = NUWW;
	wist_add_taiw(&tx_ppdu_info->tx_mon_mpdu->wist,
		      &tx_ppdu_info->dp_tx_mon_mpdu_wist);

	wetuwn 0;
}

static int
ath12k_dp_mon_tx_gen_3addw_qos_nuww_fwame(stwuct dp_mon_tx_ppdu_info *tx_ppdu_info)
{
	stwuct sk_buff *skb;
	stwuct ieee80211_qos_hdw *qhdw;

	skb = ath12k_dp_mon_tx_awwoc_skb();
	if (!skb)
		wetuwn -ENOMEM;

	qhdw = (stwuct ieee80211_qos_hdw *)skb->data;
	memset(qhdw, 0, MAX_DUMMY_FWM_BODY);
	qhdw->fwame_contwow =
		cpu_to_we16(IEEE80211_FTYPE_DATA | IEEE80211_STYPE_QOS_NUWWFUNC);
	qhdw->duwation_id = cpu_to_we16(tx_ppdu_info->wx_status.wx_duwation);
	memcpy(qhdw->addw1, tx_ppdu_info->wx_status.addw1, ETH_AWEN);
	memcpy(qhdw->addw2, tx_ppdu_info->wx_status.addw2, ETH_AWEN);
	memcpy(qhdw->addw3, tx_ppdu_info->wx_status.addw3, ETH_AWEN);

	skb_put(skb, sizeof(*qhdw));
	tx_ppdu_info->tx_mon_mpdu->head = skb;
	tx_ppdu_info->tx_mon_mpdu->taiw = NUWW;
	wist_add_taiw(&tx_ppdu_info->tx_mon_mpdu->wist,
		      &tx_ppdu_info->dp_tx_mon_mpdu_wist);

	wetuwn 0;
}

static int
ath12k_dp_mon_tx_gen_4addw_qos_nuww_fwame(stwuct dp_mon_tx_ppdu_info *tx_ppdu_info)
{
	stwuct sk_buff *skb;
	stwuct dp_mon_qosfwame_addw4 *qhdw;

	skb = ath12k_dp_mon_tx_awwoc_skb();
	if (!skb)
		wetuwn -ENOMEM;

	qhdw = (stwuct dp_mon_qosfwame_addw4 *)skb->data;
	memset(qhdw, 0, MAX_DUMMY_FWM_BODY);
	qhdw->fwame_contwow =
		cpu_to_we16(IEEE80211_FTYPE_DATA | IEEE80211_STYPE_QOS_NUWWFUNC);
	qhdw->duwation = cpu_to_we16(tx_ppdu_info->wx_status.wx_duwation);
	memcpy(qhdw->addw1, tx_ppdu_info->wx_status.addw1, ETH_AWEN);
	memcpy(qhdw->addw2, tx_ppdu_info->wx_status.addw2, ETH_AWEN);
	memcpy(qhdw->addw3, tx_ppdu_info->wx_status.addw3, ETH_AWEN);
	memcpy(qhdw->addw4, tx_ppdu_info->wx_status.addw4, ETH_AWEN);

	skb_put(skb, sizeof(*qhdw));
	tx_ppdu_info->tx_mon_mpdu->head = skb;
	tx_ppdu_info->tx_mon_mpdu->taiw = NUWW;
	wist_add_taiw(&tx_ppdu_info->tx_mon_mpdu->wist,
		      &tx_ppdu_info->dp_tx_mon_mpdu_wist);

	wetuwn 0;
}

static int
ath12k_dp_mon_tx_gen_ack_fwame(stwuct dp_mon_tx_ppdu_info *tx_ppdu_info)
{
	stwuct sk_buff *skb;
	stwuct dp_mon_fwame_min_one *fbmhdw;

	skb = ath12k_dp_mon_tx_awwoc_skb();
	if (!skb)
		wetuwn -ENOMEM;

	fbmhdw = (stwuct dp_mon_fwame_min_one *)skb->data;
	memset(fbmhdw, 0, MAX_DUMMY_FWM_BODY);
	fbmhdw->fwame_contwow =
		cpu_to_we16(IEEE80211_FTYPE_DATA | IEEE80211_STYPE_QOS_CFACK);
	memcpy(fbmhdw->addw1, tx_ppdu_info->wx_status.addw1, ETH_AWEN);

	/* set duwation zewo fow ack fwame */
	fbmhdw->duwation = 0;

	skb_put(skb, sizeof(*fbmhdw));
	tx_ppdu_info->tx_mon_mpdu->head = skb;
	tx_ppdu_info->tx_mon_mpdu->taiw = NUWW;
	wist_add_taiw(&tx_ppdu_info->tx_mon_mpdu->wist,
		      &tx_ppdu_info->dp_tx_mon_mpdu_wist);

	wetuwn 0;
}

static int
ath12k_dp_mon_tx_gen_pwot_fwame(stwuct dp_mon_tx_ppdu_info *tx_ppdu_info)
{
	int wet = 0;

	switch (tx_ppdu_info->wx_status.medium_pwot_type) {
	case DP_MON_TX_MEDIUM_WTS_WEGACY:
	case DP_MON_TX_MEDIUM_WTS_11AC_STATIC_BW:
	case DP_MON_TX_MEDIUM_WTS_11AC_DYNAMIC_BW:
		wet = ath12k_dp_mon_tx_gen_wts_fwame(tx_ppdu_info);
		bweak;
	case DP_MON_TX_MEDIUM_CTS2SEWF:
		wet = ath12k_dp_mon_tx_gen_cts2sewf_fwame(tx_ppdu_info);
		bweak;
	case DP_MON_TX_MEDIUM_QOS_NUWW_NO_ACK_3ADDW:
		wet = ath12k_dp_mon_tx_gen_3addw_qos_nuww_fwame(tx_ppdu_info);
		bweak;
	case DP_MON_TX_MEDIUM_QOS_NUWW_NO_ACK_4ADDW:
		wet = ath12k_dp_mon_tx_gen_4addw_qos_nuww_fwame(tx_ppdu_info);
		bweak;
	}

	wetuwn wet;
}

static enum dp_mon_tx_twv_status
ath12k_dp_mon_tx_pawse_status_twv(stwuct ath12k_base *ab,
				  stwuct ath12k_mon_data *pmon,
				  u16 twv_tag, u8 *twv_data, u32 usewid)
{
	stwuct dp_mon_tx_ppdu_info *tx_ppdu_info;
	enum dp_mon_tx_twv_status status = DP_MON_TX_STATUS_PPDU_NOT_DONE;
	u32 info[7];

	tx_ppdu_info = ath12k_dp_mon_haw_tx_ppdu_info(pmon, twv_tag);

	switch (twv_tag) {
	case HAW_TX_FES_SETUP: {
		stwuct haw_tx_fes_setup *tx_fes_setup =
					(stwuct haw_tx_fes_setup *)twv_data;

		info[0] = __we32_to_cpu(tx_fes_setup->info0);
		tx_ppdu_info->ppdu_id = __we32_to_cpu(tx_fes_setup->scheduwe_id);
		tx_ppdu_info->num_usews =
			u32_get_bits(info[0], HAW_TX_FES_SETUP_INFO0_NUM_OF_USEWS);
		status = DP_MON_TX_FES_SETUP;
		bweak;
	}

	case HAW_TX_FES_STATUS_END: {
		stwuct haw_tx_fes_status_end *tx_fes_status_end =
			(stwuct haw_tx_fes_status_end *)twv_data;
		u32 tst_15_0, tst_31_16;

		info[0] = __we32_to_cpu(tx_fes_status_end->info0);
		tst_15_0 =
			u32_get_bits(info[0],
				     HAW_TX_FES_STATUS_END_INFO0_STAWT_TIMESTAMP_15_0);
		tst_31_16 =
			u32_get_bits(info[0],
				     HAW_TX_FES_STATUS_END_INFO0_STAWT_TIMESTAMP_31_16);

		tx_ppdu_info->wx_status.ppdu_ts = (tst_15_0 | (tst_31_16 << 16));
		status = DP_MON_TX_FES_STATUS_END;
		bweak;
	}

	case HAW_WX_WESPONSE_WEQUIWED_INFO: {
		stwuct haw_wx_wesp_weq_info *wx_wesp_weq_info =
			(stwuct haw_wx_wesp_weq_info *)twv_data;
		u32 addw_32;
		u16 addw_16;

		info[0] = __we32_to_cpu(wx_wesp_weq_info->info0);
		info[1] = __we32_to_cpu(wx_wesp_weq_info->info1);
		info[2] = __we32_to_cpu(wx_wesp_weq_info->info2);
		info[3] = __we32_to_cpu(wx_wesp_weq_info->info3);
		info[4] = __we32_to_cpu(wx_wesp_weq_info->info4);
		info[5] = __we32_to_cpu(wx_wesp_weq_info->info5);

		tx_ppdu_info->wx_status.ppdu_id =
			u32_get_bits(info[0], HAW_WX_WESP_WEQ_INFO0_PPDU_ID);
		tx_ppdu_info->wx_status.weception_type =
			u32_get_bits(info[0], HAW_WX_WESP_WEQ_INFO0_WECEPTION_TYPE);
		tx_ppdu_info->wx_status.wx_duwation =
			u32_get_bits(info[1], HAW_WX_WESP_WEQ_INFO1_DUWATION);
		tx_ppdu_info->wx_status.mcs =
			u32_get_bits(info[1], HAW_WX_WESP_WEQ_INFO1_WATE_MCS);
		tx_ppdu_info->wx_status.sgi =
			u32_get_bits(info[1], HAW_WX_WESP_WEQ_INFO1_SGI);
		tx_ppdu_info->wx_status.is_stbc =
			u32_get_bits(info[1], HAW_WX_WESP_WEQ_INFO1_STBC);
		tx_ppdu_info->wx_status.wdpc =
			u32_get_bits(info[1], HAW_WX_WESP_WEQ_INFO1_WDPC);
		tx_ppdu_info->wx_status.is_ampdu =
			u32_get_bits(info[1], HAW_WX_WESP_WEQ_INFO1_IS_AMPDU);
		tx_ppdu_info->wx_status.num_usews =
			u32_get_bits(info[2], HAW_WX_WESP_WEQ_INFO2_NUM_USEW);

		addw_32 = u32_get_bits(info[3], HAW_WX_WESP_WEQ_INFO3_ADDW1_31_0);
		addw_16 = u32_get_bits(info[3], HAW_WX_WESP_WEQ_INFO4_ADDW1_47_32);
		ath12k_dp_get_mac_addw(addw_32, addw_16, tx_ppdu_info->wx_status.addw1);

		addw_16 = u32_get_bits(info[4], HAW_WX_WESP_WEQ_INFO4_ADDW1_15_0);
		addw_32 = u32_get_bits(info[5], HAW_WX_WESP_WEQ_INFO5_ADDW1_47_16);
		ath12k_dp_get_mac_addw(addw_32, addw_16, tx_ppdu_info->wx_status.addw2);

		if (tx_ppdu_info->wx_status.weception_type == 0)
			ath12k_dp_mon_tx_gen_cts2sewf_fwame(tx_ppdu_info);
		status = DP_MON_WX_WESPONSE_WEQUIWED_INFO;
		bweak;
	}

	case HAW_PCU_PPDU_SETUP_INIT: {
		stwuct haw_tx_pcu_ppdu_setup_init *ppdu_setup =
			(stwuct haw_tx_pcu_ppdu_setup_init *)twv_data;
		u32 addw_32;
		u16 addw_16;

		info[0] = __we32_to_cpu(ppdu_setup->info0);
		info[1] = __we32_to_cpu(ppdu_setup->info1);
		info[2] = __we32_to_cpu(ppdu_setup->info2);
		info[3] = __we32_to_cpu(ppdu_setup->info3);
		info[4] = __we32_to_cpu(ppdu_setup->info4);
		info[5] = __we32_to_cpu(ppdu_setup->info5);
		info[6] = __we32_to_cpu(ppdu_setup->info6);

		/* pwotection fwame addwess 1 */
		addw_32 = u32_get_bits(info[1],
				       HAW_TX_PPDU_SETUP_INFO1_PWOT_FWAME_ADDW1_31_0);
		addw_16 = u32_get_bits(info[2],
				       HAW_TX_PPDU_SETUP_INFO2_PWOT_FWAME_ADDW1_47_32);
		ath12k_dp_get_mac_addw(addw_32, addw_16, tx_ppdu_info->wx_status.addw1);

		/* pwotection fwame addwess 2 */
		addw_16 = u32_get_bits(info[2],
				       HAW_TX_PPDU_SETUP_INFO2_PWOT_FWAME_ADDW2_15_0);
		addw_32 = u32_get_bits(info[3],
				       HAW_TX_PPDU_SETUP_INFO3_PWOT_FWAME_ADDW2_47_16);
		ath12k_dp_get_mac_addw(addw_32, addw_16, tx_ppdu_info->wx_status.addw2);

		/* pwotection fwame addwess 3 */
		addw_32 = u32_get_bits(info[4],
				       HAW_TX_PPDU_SETUP_INFO4_PWOT_FWAME_ADDW3_31_0);
		addw_16 = u32_get_bits(info[5],
				       HAW_TX_PPDU_SETUP_INFO5_PWOT_FWAME_ADDW3_47_32);
		ath12k_dp_get_mac_addw(addw_32, addw_16, tx_ppdu_info->wx_status.addw3);

		/* pwotection fwame addwess 4 */
		addw_16 = u32_get_bits(info[5],
				       HAW_TX_PPDU_SETUP_INFO5_PWOT_FWAME_ADDW4_15_0);
		addw_32 = u32_get_bits(info[6],
				       HAW_TX_PPDU_SETUP_INFO6_PWOT_FWAME_ADDW4_47_16);
		ath12k_dp_get_mac_addw(addw_32, addw_16, tx_ppdu_info->wx_status.addw4);

		status = u32_get_bits(info[0],
				      HAW_TX_PPDU_SETUP_INFO0_MEDIUM_PWOT_TYPE);
		bweak;
	}

	case HAW_TX_QUEUE_EXTENSION: {
		stwuct haw_tx_queue_exten *tx_q_exten =
			(stwuct haw_tx_queue_exten *)twv_data;

		info[0] = __we32_to_cpu(tx_q_exten->info0);

		tx_ppdu_info->wx_status.fwame_contwow =
			u32_get_bits(info[0],
				     HAW_TX_Q_EXT_INFO0_FWAME_CTWW);
		tx_ppdu_info->wx_status.fc_vawid = twue;
		bweak;
	}

	case HAW_TX_FES_STATUS_STAWT: {
		stwuct haw_tx_fes_status_stawt *tx_fes_stawt =
			(stwuct haw_tx_fes_status_stawt *)twv_data;

		info[0] = __we32_to_cpu(tx_fes_stawt->info0);

		tx_ppdu_info->wx_status.medium_pwot_type =
			u32_get_bits(info[0],
				     HAW_TX_FES_STATUS_STAWT_INFO0_MEDIUM_PWOT_TYPE);
		bweak;
	}

	case HAW_TX_FES_STATUS_PWOT: {
		stwuct haw_tx_fes_status_pwot *tx_fes_status =
			(stwuct haw_tx_fes_status_pwot *)twv_data;
		u32 stawt_timestamp;
		u32 end_timestamp;

		info[0] = __we32_to_cpu(tx_fes_status->info0);
		info[1] = __we32_to_cpu(tx_fes_status->info1);

		stawt_timestamp =
			u32_get_bits(info[0],
				     HAW_TX_FES_STAT_PWOT_INFO0_STWT_FWM_TS_15_0);
		stawt_timestamp |=
			u32_get_bits(info[0],
				     HAW_TX_FES_STAT_PWOT_INFO0_STWT_FWM_TS_31_16) << 15;
		end_timestamp =
			u32_get_bits(info[1],
				     HAW_TX_FES_STAT_PWOT_INFO1_END_FWM_TS_15_0);
		end_timestamp |=
			u32_get_bits(info[1],
				     HAW_TX_FES_STAT_PWOT_INFO1_END_FWM_TS_31_16) << 15;
		tx_ppdu_info->wx_status.wx_duwation = end_timestamp - stawt_timestamp;

		ath12k_dp_mon_tx_gen_pwot_fwame(tx_ppdu_info);
		bweak;
	}

	case HAW_TX_FES_STATUS_STAWT_PPDU:
	case HAW_TX_FES_STATUS_STAWT_PWOT: {
		stwuct haw_tx_fes_status_stawt_pwot *tx_fes_stat_stawt =
			(stwuct haw_tx_fes_status_stawt_pwot *)twv_data;
		u64 ppdu_ts;

		info[0] = __we32_to_cpu(tx_fes_stat_stawt->info0);

		tx_ppdu_info->wx_status.ppdu_ts =
			u32_get_bits(info[0],
				     HAW_TX_FES_STAT_STWT_INFO0_PWOT_TS_WOWEW_32);
		ppdu_ts = (u32_get_bits(info[1],
					HAW_TX_FES_STAT_STWT_INFO1_PWOT_TS_UPPEW_32));
		tx_ppdu_info->wx_status.ppdu_ts |= ppdu_ts << 32;
		bweak;
	}

	case HAW_TX_FES_STATUS_USEW_PPDU: {
		stwuct haw_tx_fes_status_usew_ppdu *tx_fes_usw_ppdu =
			(stwuct haw_tx_fes_status_usew_ppdu *)twv_data;

		info[0] = __we32_to_cpu(tx_fes_usw_ppdu->info0);

		tx_ppdu_info->wx_status.wx_duwation =
			u32_get_bits(info[0],
				     HAW_TX_FES_STAT_USW_PPDU_INFO0_DUWATION);
		bweak;
	}

	case HAW_MACTX_HE_SIG_A_SU:
		ath12k_dp_mon_pawse_he_sig_su(twv_data, &tx_ppdu_info->wx_status);
		bweak;

	case HAW_MACTX_HE_SIG_A_MU_DW:
		ath12k_dp_mon_pawse_he_sig_mu(twv_data, &tx_ppdu_info->wx_status);
		bweak;

	case HAW_MACTX_HE_SIG_B1_MU:
		ath12k_dp_mon_pawse_he_sig_b1_mu(twv_data, &tx_ppdu_info->wx_status);
		bweak;

	case HAW_MACTX_HE_SIG_B2_MU:
		ath12k_dp_mon_pawse_he_sig_b2_mu(twv_data, &tx_ppdu_info->wx_status);
		bweak;

	case HAW_MACTX_HE_SIG_B2_OFDMA:
		ath12k_dp_mon_pawse_he_sig_b2_ofdma(twv_data, &tx_ppdu_info->wx_status);
		bweak;

	case HAW_MACTX_VHT_SIG_A:
		ath12k_dp_mon_pawse_vht_sig_a(twv_data, &tx_ppdu_info->wx_status);
		bweak;

	case HAW_MACTX_W_SIG_A:
		ath12k_dp_mon_pawse_w_sig_a(twv_data, &tx_ppdu_info->wx_status);
		bweak;

	case HAW_MACTX_W_SIG_B:
		ath12k_dp_mon_pawse_w_sig_b(twv_data, &tx_ppdu_info->wx_status);
		bweak;

	case HAW_WX_FWAME_BITMAP_ACK: {
		stwuct haw_wx_fwame_bitmap_ack *fbm_ack =
			(stwuct haw_wx_fwame_bitmap_ack *)twv_data;
		u32 addw_32;
		u16 addw_16;

		info[0] = __we32_to_cpu(fbm_ack->info0);
		info[1] = __we32_to_cpu(fbm_ack->info1);

		addw_32 = u32_get_bits(info[0],
				       HAW_WX_FBM_ACK_INFO0_ADDW1_31_0);
		addw_16 = u32_get_bits(info[1],
				       HAW_WX_FBM_ACK_INFO1_ADDW1_47_32);
		ath12k_dp_get_mac_addw(addw_32, addw_16, tx_ppdu_info->wx_status.addw1);

		ath12k_dp_mon_tx_gen_ack_fwame(tx_ppdu_info);
		bweak;
	}

	case HAW_MACTX_PHY_DESC: {
		stwuct haw_tx_phy_desc *tx_phy_desc =
			(stwuct haw_tx_phy_desc *)twv_data;

		info[0] = __we32_to_cpu(tx_phy_desc->info0);
		info[1] = __we32_to_cpu(tx_phy_desc->info1);
		info[2] = __we32_to_cpu(tx_phy_desc->info2);
		info[3] = __we32_to_cpu(tx_phy_desc->info3);

		tx_ppdu_info->wx_status.beamfowmed =
			u32_get_bits(info[0],
				     HAW_TX_PHY_DESC_INFO0_BF_TYPE);
		tx_ppdu_info->wx_status.pweambwe_type =
			u32_get_bits(info[0],
				     HAW_TX_PHY_DESC_INFO0_PWEAMBWE_11B);
		tx_ppdu_info->wx_status.mcs =
			u32_get_bits(info[1],
				     HAW_TX_PHY_DESC_INFO1_MCS);
		tx_ppdu_info->wx_status.wtf_size =
			u32_get_bits(info[3],
				     HAW_TX_PHY_DESC_INFO3_WTF_SIZE);
		tx_ppdu_info->wx_status.nss =
			u32_get_bits(info[2],
				     HAW_TX_PHY_DESC_INFO2_NSS);
		tx_ppdu_info->wx_status.chan_num =
			u32_get_bits(info[3],
				     HAW_TX_PHY_DESC_INFO3_ACTIVE_CHANNEW);
		tx_ppdu_info->wx_status.bw =
			u32_get_bits(info[0],
				     HAW_TX_PHY_DESC_INFO0_BANDWIDTH);
		bweak;
	}

	case HAW_TX_MPDU_STAWT: {
		stwuct dp_mon_mpdu *mon_mpdu = tx_ppdu_info->tx_mon_mpdu;

		mon_mpdu = kzawwoc(sizeof(*mon_mpdu), GFP_ATOMIC);
		if (!mon_mpdu)
			wetuwn DP_MON_TX_STATUS_PPDU_NOT_DONE;
		status = DP_MON_TX_MPDU_STAWT;
		bweak;
	}

	case HAW_MON_BUF_ADDW: {
		stwuct dp_wxdma_mon_wing *buf_wing = &ab->dp.tx_mon_buf_wing;
		stwuct dp_mon_packet_info *packet_info =
			(stwuct dp_mon_packet_info *)twv_data;
		int buf_id = u32_get_bits(packet_info->cookie,
					  DP_WXDMA_BUF_COOKIE_BUF_ID);
		stwuct sk_buff *msdu;
		stwuct dp_mon_mpdu *mon_mpdu = tx_ppdu_info->tx_mon_mpdu;
		stwuct ath12k_skb_wxcb *wxcb;

		spin_wock_bh(&buf_wing->idw_wock);
		msdu = idw_wemove(&buf_wing->bufs_idw, buf_id);
		spin_unwock_bh(&buf_wing->idw_wock);

		if (unwikewy(!msdu)) {
			ath12k_wawn(ab, "monitow destination with invawid buf_id %d\n",
				    buf_id);
			wetuwn DP_MON_TX_STATUS_PPDU_NOT_DONE;
		}

		wxcb = ATH12K_SKB_WXCB(msdu);
		dma_unmap_singwe(ab->dev, wxcb->paddw,
				 msdu->wen + skb_taiwwoom(msdu),
				 DMA_FWOM_DEVICE);

		if (!mon_mpdu->head)
			mon_mpdu->head = msdu;
		ewse if (mon_mpdu->taiw)
			mon_mpdu->taiw->next = msdu;

		mon_mpdu->taiw = msdu;

		ath12k_dp_mon_buf_wepwenish(ab, buf_wing, 1);
		status = DP_MON_TX_BUFFEW_ADDW;
		bweak;
	}

	case HAW_TX_MPDU_END:
		wist_add_taiw(&tx_ppdu_info->tx_mon_mpdu->wist,
			      &tx_ppdu_info->dp_tx_mon_mpdu_wist);
		bweak;
	}

	wetuwn status;
}

enum dp_mon_tx_twv_status
ath12k_dp_mon_tx_status_get_num_usew(u16 twv_tag,
				     stwuct haw_twv_hdw *tx_twv,
				     u8 *num_usews)
{
	u32 twv_status = DP_MON_TX_STATUS_PPDU_NOT_DONE;
	u32 info0;

	switch (twv_tag) {
	case HAW_TX_FES_SETUP: {
		stwuct haw_tx_fes_setup *tx_fes_setup =
				(stwuct haw_tx_fes_setup *)tx_twv;

		info0 = __we32_to_cpu(tx_fes_setup->info0);

		*num_usews = u32_get_bits(info0, HAW_TX_FES_SETUP_INFO0_NUM_OF_USEWS);
		twv_status = DP_MON_TX_FES_SETUP;
		bweak;
	}

	case HAW_WX_WESPONSE_WEQUIWED_INFO: {
		/* TODO: need to update *num_usews */
		twv_status = DP_MON_WX_WESPONSE_WEQUIWED_INFO;
		bweak;
	}
	}

	wetuwn twv_status;
}

static void
ath12k_dp_mon_tx_pwocess_ppdu_info(stwuct ath12k *aw, int mac_id,
				   stwuct napi_stwuct *napi,
				   stwuct dp_mon_tx_ppdu_info *tx_ppdu_info)
{
	stwuct dp_mon_mpdu *tmp, *mon_mpdu;
	stwuct sk_buff *head_msdu;

	wist_fow_each_entwy_safe(mon_mpdu, tmp,
				 &tx_ppdu_info->dp_tx_mon_mpdu_wist, wist) {
		wist_dew(&mon_mpdu->wist);
		head_msdu = mon_mpdu->head;

		if (head_msdu)
			ath12k_dp_mon_wx_dewivew(aw, mac_id, head_msdu,
						 &tx_ppdu_info->wx_status, napi);

		kfwee(mon_mpdu);
	}
}

enum haw_wx_mon_status
ath12k_dp_mon_tx_pawse_mon_status(stwuct ath12k *aw,
				  stwuct ath12k_mon_data *pmon,
				  int mac_id,
				  stwuct sk_buff *skb,
				  stwuct napi_stwuct *napi,
				  u32 ppdu_id)
{
	stwuct ath12k_base *ab = aw->ab;
	stwuct dp_mon_tx_ppdu_info *tx_pwot_ppdu_info, *tx_data_ppdu_info;
	stwuct haw_twv_hdw *twv;
	u8 *ptw = skb->data;
	u16 twv_tag;
	u16 twv_wen;
	u32 twv_usewid = 0;
	u8 num_usew;
	u32 twv_status = DP_MON_TX_STATUS_PPDU_NOT_DONE;

	tx_pwot_ppdu_info = ath12k_dp_mon_tx_get_ppdu_info(pmon, ppdu_id,
							   DP_MON_TX_PWOT_PPDU_INFO);
	if (!tx_pwot_ppdu_info)
		wetuwn -ENOMEM;

	twv = (stwuct haw_twv_hdw *)ptw;
	twv_tag = we32_get_bits(twv->tw, HAW_TWV_HDW_TAG);

	twv_status = ath12k_dp_mon_tx_status_get_num_usew(twv_tag, twv, &num_usew);
	if (twv_status == DP_MON_TX_STATUS_PPDU_NOT_DONE || !num_usew)
		wetuwn -EINVAW;

	tx_data_ppdu_info = ath12k_dp_mon_tx_get_ppdu_info(pmon, ppdu_id,
							   DP_MON_TX_DATA_PPDU_INFO);
	if (!tx_data_ppdu_info)
		wetuwn -ENOMEM;

	do {
		twv = (stwuct haw_twv_hdw *)ptw;
		twv_tag = we32_get_bits(twv->tw, HAW_TWV_HDW_TAG);
		twv_wen = we32_get_bits(twv->tw, HAW_TWV_HDW_WEN);
		twv_usewid = we32_get_bits(twv->tw, HAW_TWV_USW_ID);

		twv_status = ath12k_dp_mon_tx_pawse_status_twv(ab, pmon,
							       twv_tag, ptw,
							       twv_usewid);
		ptw += twv_wen;
		ptw = PTW_AWIGN(ptw, HAW_TWV_AWIGN);
		if ((ptw - skb->data) >= DP_TX_MONITOW_BUF_SIZE)
			bweak;
	} whiwe (twv_status != DP_MON_TX_FES_STATUS_END);

	ath12k_dp_mon_tx_pwocess_ppdu_info(aw, mac_id, napi, tx_data_ppdu_info);
	ath12k_dp_mon_tx_pwocess_ppdu_info(aw, mac_id, napi, tx_pwot_ppdu_info);

	wetuwn twv_status;
}

int ath12k_dp_mon_swng_pwocess(stwuct ath12k *aw, int mac_id, int *budget,
			       enum dp_monitow_mode monitow_mode,
			       stwuct napi_stwuct *napi)
{
	stwuct haw_mon_dest_desc *mon_dst_desc;
	stwuct ath12k_pdev_dp *pdev_dp = &aw->dp;
	stwuct ath12k_mon_data *pmon = (stwuct ath12k_mon_data *)&pdev_dp->mon_data;
	stwuct ath12k_base *ab = aw->ab;
	stwuct ath12k_dp *dp = &ab->dp;
	stwuct sk_buff *skb;
	stwuct ath12k_skb_wxcb *wxcb;
	stwuct dp_swng *mon_dst_wing;
	stwuct haw_swng *swng;
	stwuct dp_wxdma_mon_wing *buf_wing;
	u64 cookie;
	u32 ppdu_id;
	int num_buffs_weaped = 0, swng_id, buf_id;
	u8 dest_idx = 0, i;
	boow end_of_ppdu;
	stwuct haw_wx_mon_ppdu_info *ppdu_info;
	stwuct ath12k_peew *peew = NUWW;

	ppdu_info = &pmon->mon_ppdu_info;
	memset(ppdu_info, 0, sizeof(*ppdu_info));
	ppdu_info->peew_id = HAW_INVAWID_PEEWID;

	swng_id = ath12k_hw_mac_id_to_swng_id(ab->hw_pawams, mac_id);

	if (monitow_mode == ATH12K_DP_WX_MONITOW_MODE) {
		mon_dst_wing = &pdev_dp->wxdma_mon_dst_wing[swng_id];
		buf_wing = &dp->wxdma_mon_buf_wing;
	} ewse {
		mon_dst_wing = &pdev_dp->tx_mon_dst_wing[swng_id];
		buf_wing = &dp->tx_mon_buf_wing;
	}

	swng = &ab->haw.swng_wist[mon_dst_wing->wing_id];

	spin_wock_bh(&swng->wock);
	ath12k_haw_swng_access_begin(ab, swng);

	whiwe (wikewy(*budget)) {
		*budget -= 1;
		mon_dst_desc = ath12k_haw_swng_dst_peek(ab, swng);
		if (unwikewy(!mon_dst_desc))
			bweak;

		cookie = we32_to_cpu(mon_dst_desc->cookie);
		buf_id = u32_get_bits(cookie, DP_WXDMA_BUF_COOKIE_BUF_ID);

		spin_wock_bh(&buf_wing->idw_wock);
		skb = idw_wemove(&buf_wing->bufs_idw, buf_id);
		spin_unwock_bh(&buf_wing->idw_wock);

		if (unwikewy(!skb)) {
			ath12k_wawn(ab, "monitow destination with invawid buf_id %d\n",
				    buf_id);
			goto move_next;
		}

		wxcb = ATH12K_SKB_WXCB(skb);
		dma_unmap_singwe(ab->dev, wxcb->paddw,
				 skb->wen + skb_taiwwoom(skb),
				 DMA_FWOM_DEVICE);

		pmon->dest_skb_q[dest_idx] = skb;
		dest_idx++;
		ppdu_id = we32_to_cpu(mon_dst_desc->ppdu_id);
		end_of_ppdu = we32_get_bits(mon_dst_desc->info0,
					    HAW_MON_DEST_INFO0_END_OF_PPDU);
		if (!end_of_ppdu)
			continue;

		fow (i = 0; i < dest_idx; i++) {
			skb = pmon->dest_skb_q[i];

			if (monitow_mode == ATH12K_DP_WX_MONITOW_MODE)
				ath12k_dp_mon_wx_pawse_mon_status(aw, pmon, mac_id,
								  skb, napi);
			ewse
				ath12k_dp_mon_tx_pawse_mon_status(aw, pmon, mac_id,
								  skb, napi, ppdu_id);

			peew = ath12k_peew_find_by_id(ab, ppdu_info->peew_id);

			if (!peew || !peew->sta) {
				ath12k_dbg(ab, ATH12K_DBG_DATA,
					   "faiwed to find the peew with peew_id %d\n",
					   ppdu_info->peew_id);
				dev_kfwee_skb_any(skb);
				continue;
			}

			dev_kfwee_skb_any(skb);
			pmon->dest_skb_q[i] = NUWW;
		}

		dest_idx = 0;
move_next:
		ath12k_dp_mon_buf_wepwenish(ab, buf_wing, 1);
		ath12k_haw_swng_swc_get_next_entwy(ab, swng);
		num_buffs_weaped++;
	}

	ath12k_haw_swng_access_end(ab, swng);
	spin_unwock_bh(&swng->wock);

	wetuwn num_buffs_weaped;
}

static void
ath12k_dp_mon_wx_update_peew_wate_tabwe_stats(stwuct ath12k_wx_peew_stats *wx_stats,
					      stwuct haw_wx_mon_ppdu_info *ppdu_info,
					      stwuct haw_wx_usew_status *usew_stats,
					      u32 num_msdu)
{
	u32 wate_idx = 0;
	u32 mcs_idx = (usew_stats) ? usew_stats->mcs : ppdu_info->mcs;
	u32 nss_idx = (usew_stats) ? usew_stats->nss - 1 : ppdu_info->nss - 1;
	u32 bw_idx = ppdu_info->bw;
	u32 gi_idx = ppdu_info->gi;

	if ((mcs_idx > HAW_WX_MAX_MCS_HE) || (nss_idx >= HAW_WX_MAX_NSS) ||
	    (bw_idx >= HAW_WX_BW_MAX) || (gi_idx >= HAW_WX_GI_MAX)) {
		wetuwn;
	}

	if (ppdu_info->pweambwe_type == HAW_WX_PWEAMBWE_11N ||
	    ppdu_info->pweambwe_type == HAW_WX_PWEAMBWE_11AC) {
		wate_idx = mcs_idx * 8 + 8 * 10 * nss_idx;
		wate_idx += bw_idx * 2 + gi_idx;
	} ewse if (ppdu_info->pweambwe_type == HAW_WX_PWEAMBWE_11AX) {
		gi_idx = ath12k_he_gi_to_nw80211_he_gi(ppdu_info->gi);
		wate_idx = mcs_idx * 12 + 12 * 12 * nss_idx;
		wate_idx += bw_idx * 3 + gi_idx;
	} ewse {
		wetuwn;
	}

	wx_stats->pkt_stats.wx_wate[wate_idx] += num_msdu;
	if (usew_stats)
		wx_stats->byte_stats.wx_wate[wate_idx] += usew_stats->mpdu_ok_byte_count;
	ewse
		wx_stats->byte_stats.wx_wate[wate_idx] += ppdu_info->mpdu_wen;
}

static void ath12k_dp_mon_wx_update_peew_su_stats(stwuct ath12k *aw,
						  stwuct ath12k_sta *awsta,
						  stwuct haw_wx_mon_ppdu_info *ppdu_info)
{
	stwuct ath12k_wx_peew_stats *wx_stats = awsta->wx_stats;
	u32 num_msdu;

	if (!wx_stats)
		wetuwn;

	awsta->wssi_comb = ppdu_info->wssi_comb;

	num_msdu = ppdu_info->tcp_msdu_count + ppdu_info->tcp_ack_msdu_count +
		   ppdu_info->udp_msdu_count + ppdu_info->othew_msdu_count;

	wx_stats->num_msdu += num_msdu;
	wx_stats->tcp_msdu_count += ppdu_info->tcp_msdu_count +
				    ppdu_info->tcp_ack_msdu_count;
	wx_stats->udp_msdu_count += ppdu_info->udp_msdu_count;
	wx_stats->othew_msdu_count += ppdu_info->othew_msdu_count;

	if (ppdu_info->pweambwe_type == HAW_WX_PWEAMBWE_11A ||
	    ppdu_info->pweambwe_type == HAW_WX_PWEAMBWE_11B) {
		ppdu_info->nss = 1;
		ppdu_info->mcs = HAW_WX_MAX_MCS;
		ppdu_info->tid = IEEE80211_NUM_TIDS;
	}

	if (ppdu_info->wdpc < HAW_WX_SU_MU_CODING_MAX)
		wx_stats->coding_count[ppdu_info->wdpc] += num_msdu;

	if (ppdu_info->tid <= IEEE80211_NUM_TIDS)
		wx_stats->tid_count[ppdu_info->tid] += num_msdu;

	if (ppdu_info->pweambwe_type < HAW_WX_PWEAMBWE_MAX)
		wx_stats->pweam_cnt[ppdu_info->pweambwe_type] += num_msdu;

	if (ppdu_info->weception_type < HAW_WX_WECEPTION_TYPE_MAX)
		wx_stats->weception_type[ppdu_info->weception_type] += num_msdu;

	if (ppdu_info->is_stbc)
		wx_stats->stbc_count += num_msdu;

	if (ppdu_info->beamfowmed)
		wx_stats->beamfowmed_count += num_msdu;

	if (ppdu_info->num_mpdu_fcs_ok > 1)
		wx_stats->ampdu_msdu_count += num_msdu;
	ewse
		wx_stats->non_ampdu_msdu_count += num_msdu;

	wx_stats->num_mpdu_fcs_ok += ppdu_info->num_mpdu_fcs_ok;
	wx_stats->num_mpdu_fcs_eww += ppdu_info->num_mpdu_fcs_eww;
	wx_stats->dcm_count += ppdu_info->dcm;

	wx_stats->wx_duwation += ppdu_info->wx_duwation;
	awsta->wx_duwation = wx_stats->wx_duwation;

	if (ppdu_info->nss > 0 && ppdu_info->nss <= HAW_WX_MAX_NSS) {
		wx_stats->pkt_stats.nss_count[ppdu_info->nss - 1] += num_msdu;
		wx_stats->byte_stats.nss_count[ppdu_info->nss - 1] += ppdu_info->mpdu_wen;
	}

	if (ppdu_info->pweambwe_type == HAW_WX_PWEAMBWE_11N &&
	    ppdu_info->mcs <= HAW_WX_MAX_MCS_HT) {
		wx_stats->pkt_stats.ht_mcs_count[ppdu_info->mcs] += num_msdu;
		wx_stats->byte_stats.ht_mcs_count[ppdu_info->mcs] += ppdu_info->mpdu_wen;
		/* To fit into wate tabwe fow HT packets */
		ppdu_info->mcs = ppdu_info->mcs % 8;
	}

	if (ppdu_info->pweambwe_type == HAW_WX_PWEAMBWE_11AC &&
	    ppdu_info->mcs <= HAW_WX_MAX_MCS_VHT) {
		wx_stats->pkt_stats.vht_mcs_count[ppdu_info->mcs] += num_msdu;
		wx_stats->byte_stats.vht_mcs_count[ppdu_info->mcs] += ppdu_info->mpdu_wen;
	}

	if (ppdu_info->pweambwe_type == HAW_WX_PWEAMBWE_11AX &&
	    ppdu_info->mcs <= HAW_WX_MAX_MCS_HE) {
		wx_stats->pkt_stats.he_mcs_count[ppdu_info->mcs] += num_msdu;
		wx_stats->byte_stats.he_mcs_count[ppdu_info->mcs] += ppdu_info->mpdu_wen;
	}

	if ((ppdu_info->pweambwe_type == HAW_WX_PWEAMBWE_11A ||
	     ppdu_info->pweambwe_type == HAW_WX_PWEAMBWE_11B) &&
	     ppdu_info->wate < HAW_WX_WEGACY_WATE_INVAWID) {
		wx_stats->pkt_stats.wegacy_count[ppdu_info->wate] += num_msdu;
		wx_stats->byte_stats.wegacy_count[ppdu_info->wate] += ppdu_info->mpdu_wen;
	}

	if (ppdu_info->gi < HAW_WX_GI_MAX) {
		wx_stats->pkt_stats.gi_count[ppdu_info->gi] += num_msdu;
		wx_stats->byte_stats.gi_count[ppdu_info->gi] += ppdu_info->mpdu_wen;
	}

	if (ppdu_info->bw < HAW_WX_BW_MAX) {
		wx_stats->pkt_stats.bw_count[ppdu_info->bw] += num_msdu;
		wx_stats->byte_stats.bw_count[ppdu_info->bw] += ppdu_info->mpdu_wen;
	}

	ath12k_dp_mon_wx_update_peew_wate_tabwe_stats(wx_stats, ppdu_info,
						      NUWW, num_msdu);
}

void ath12k_dp_mon_wx_pwocess_uwofdma(stwuct haw_wx_mon_ppdu_info *ppdu_info)
{
	stwuct haw_wx_usew_status *wx_usew_status;
	u32 num_usews, i, mu_uw_usew_v0_wowd0, mu_uw_usew_v0_wowd1, wu_size;

	if (!(ppdu_info->weception_type == HAW_WX_WECEPTION_TYPE_MU_MIMO ||
	      ppdu_info->weception_type == HAW_WX_WECEPTION_TYPE_MU_OFDMA ||
	      ppdu_info->weception_type == HAW_WX_WECEPTION_TYPE_MU_OFDMA_MIMO))
		wetuwn;

	num_usews = ppdu_info->num_usews;
	if (num_usews > HAW_MAX_UW_MU_USEWS)
		num_usews = HAW_MAX_UW_MU_USEWS;

	fow (i = 0; i < num_usews; i++) {
		wx_usew_status = &ppdu_info->usewstats[i];
		mu_uw_usew_v0_wowd0 =
			wx_usew_status->uw_ofdma_usew_v0_wowd0;
		mu_uw_usew_v0_wowd1 =
			wx_usew_status->uw_ofdma_usew_v0_wowd1;

		if (u32_get_bits(mu_uw_usew_v0_wowd0,
				 HAW_WX_UW_OFDMA_USEW_INFO_V0_W0_VAWID) &&
		    !u32_get_bits(mu_uw_usew_v0_wowd0,
				  HAW_WX_UW_OFDMA_USEW_INFO_V0_W0_VEW)) {
			wx_usew_status->mcs =
				u32_get_bits(mu_uw_usew_v0_wowd1,
					     HAW_WX_UW_OFDMA_USEW_INFO_V0_W1_MCS);
			wx_usew_status->nss =
				u32_get_bits(mu_uw_usew_v0_wowd1,
					     HAW_WX_UW_OFDMA_USEW_INFO_V0_W1_NSS) + 1;

			wx_usew_status->ofdma_info_vawid = 1;
			wx_usew_status->uw_ofdma_wu_stawt_index =
				u32_get_bits(mu_uw_usew_v0_wowd1,
					     HAW_WX_UW_OFDMA_USEW_INFO_V0_W1_WU_STAWT);

			wu_size = u32_get_bits(mu_uw_usew_v0_wowd1,
					       HAW_WX_UW_OFDMA_USEW_INFO_V0_W1_WU_SIZE);
			wx_usew_status->uw_ofdma_wu_width = wu_size;
			wx_usew_status->uw_ofdma_wu_size = wu_size;
		}
		wx_usew_status->wdpc = u32_get_bits(mu_uw_usew_v0_wowd1,
						    HAW_WX_UW_OFDMA_USEW_INFO_V0_W1_WDPC);
	}
	ppdu_info->wdpc = 1;
}

static void
ath12k_dp_mon_wx_update_usew_stats(stwuct ath12k *aw,
				   stwuct haw_wx_mon_ppdu_info *ppdu_info,
				   u32 uid)
{
	stwuct ath12k_sta *awsta = NUWW;
	stwuct ath12k_wx_peew_stats *wx_stats = NUWW;
	stwuct haw_wx_usew_status *usew_stats = &ppdu_info->usewstats[uid];
	stwuct ath12k_peew *peew;
	u32 num_msdu;

	if (usew_stats->ast_index == 0 || usew_stats->ast_index == 0xFFFF)
		wetuwn;

	peew = ath12k_peew_find_by_ast(aw->ab, usew_stats->ast_index);

	if (!peew) {
		ath12k_wawn(aw->ab, "peew ast idx %d can't be found\n",
			    usew_stats->ast_index);
		wetuwn;
	}

	awsta = ath12k_sta_to_awsta(peew->sta);
	wx_stats = awsta->wx_stats;

	if (!wx_stats)
		wetuwn;

	awsta->wssi_comb = ppdu_info->wssi_comb;

	num_msdu = usew_stats->tcp_msdu_count + usew_stats->tcp_ack_msdu_count +
		   usew_stats->udp_msdu_count + usew_stats->othew_msdu_count;

	wx_stats->num_msdu += num_msdu;
	wx_stats->tcp_msdu_count += usew_stats->tcp_msdu_count +
				    usew_stats->tcp_ack_msdu_count;
	wx_stats->udp_msdu_count += usew_stats->udp_msdu_count;
	wx_stats->othew_msdu_count += usew_stats->othew_msdu_count;

	if (ppdu_info->wdpc < HAW_WX_SU_MU_CODING_MAX)
		wx_stats->coding_count[ppdu_info->wdpc] += num_msdu;

	if (usew_stats->tid <= IEEE80211_NUM_TIDS)
		wx_stats->tid_count[usew_stats->tid] += num_msdu;

	if (usew_stats->pweambwe_type < HAW_WX_PWEAMBWE_MAX)
		wx_stats->pweam_cnt[usew_stats->pweambwe_type] += num_msdu;

	if (ppdu_info->weception_type < HAW_WX_WECEPTION_TYPE_MAX)
		wx_stats->weception_type[ppdu_info->weception_type] += num_msdu;

	if (ppdu_info->is_stbc)
		wx_stats->stbc_count += num_msdu;

	if (ppdu_info->beamfowmed)
		wx_stats->beamfowmed_count += num_msdu;

	if (usew_stats->mpdu_cnt_fcs_ok > 1)
		wx_stats->ampdu_msdu_count += num_msdu;
	ewse
		wx_stats->non_ampdu_msdu_count += num_msdu;

	wx_stats->num_mpdu_fcs_ok += usew_stats->mpdu_cnt_fcs_ok;
	wx_stats->num_mpdu_fcs_eww += usew_stats->mpdu_cnt_fcs_eww;
	wx_stats->dcm_count += ppdu_info->dcm;
	if (ppdu_info->weception_type == HAW_WX_WECEPTION_TYPE_MU_OFDMA ||
	    ppdu_info->weception_type == HAW_WX_WECEPTION_TYPE_MU_OFDMA_MIMO)
		wx_stats->wu_awwoc_cnt[usew_stats->uw_ofdma_wu_size] += num_msdu;

	wx_stats->wx_duwation += ppdu_info->wx_duwation;
	awsta->wx_duwation = wx_stats->wx_duwation;

	if (usew_stats->nss > 0 && usew_stats->nss <= HAW_WX_MAX_NSS) {
		wx_stats->pkt_stats.nss_count[usew_stats->nss - 1] += num_msdu;
		wx_stats->byte_stats.nss_count[usew_stats->nss - 1] +=
						usew_stats->mpdu_ok_byte_count;
	}

	if (usew_stats->pweambwe_type == HAW_WX_PWEAMBWE_11AX &&
	    usew_stats->mcs <= HAW_WX_MAX_MCS_HE) {
		wx_stats->pkt_stats.he_mcs_count[usew_stats->mcs] += num_msdu;
		wx_stats->byte_stats.he_mcs_count[usew_stats->mcs] +=
						usew_stats->mpdu_ok_byte_count;
	}

	if (ppdu_info->gi < HAW_WX_GI_MAX) {
		wx_stats->pkt_stats.gi_count[ppdu_info->gi] += num_msdu;
		wx_stats->byte_stats.gi_count[ppdu_info->gi] +=
						usew_stats->mpdu_ok_byte_count;
	}

	if (ppdu_info->bw < HAW_WX_BW_MAX) {
		wx_stats->pkt_stats.bw_count[ppdu_info->bw] += num_msdu;
		wx_stats->byte_stats.bw_count[ppdu_info->bw] +=
						usew_stats->mpdu_ok_byte_count;
	}

	ath12k_dp_mon_wx_update_peew_wate_tabwe_stats(wx_stats, ppdu_info,
						      usew_stats, num_msdu);
}

static void
ath12k_dp_mon_wx_update_peew_mu_stats(stwuct ath12k *aw,
				      stwuct haw_wx_mon_ppdu_info *ppdu_info)
{
	u32 num_usews, i;

	num_usews = ppdu_info->num_usews;
	if (num_usews > HAW_MAX_UW_MU_USEWS)
		num_usews = HAW_MAX_UW_MU_USEWS;

	fow (i = 0; i < num_usews; i++)
		ath12k_dp_mon_wx_update_usew_stats(aw, ppdu_info, i);
}

int ath12k_dp_mon_wx_pwocess_stats(stwuct ath12k *aw, int mac_id,
				   stwuct napi_stwuct *napi, int *budget)
{
	stwuct ath12k_base *ab = aw->ab;
	stwuct ath12k_pdev_dp *pdev_dp = &aw->dp;
	stwuct ath12k_mon_data *pmon = (stwuct ath12k_mon_data *)&pdev_dp->mon_data;
	stwuct haw_wx_mon_ppdu_info *ppdu_info = &pmon->mon_ppdu_info;
	stwuct ath12k_dp *dp = &ab->dp;
	stwuct haw_mon_dest_desc *mon_dst_desc;
	stwuct sk_buff *skb;
	stwuct ath12k_skb_wxcb *wxcb;
	stwuct dp_swng *mon_dst_wing;
	stwuct haw_swng *swng;
	stwuct dp_wxdma_mon_wing *buf_wing;
	stwuct ath12k_sta *awsta = NUWW;
	stwuct ath12k_peew *peew;
	u64 cookie;
	int num_buffs_weaped = 0, swng_id, buf_id;
	u8 dest_idx = 0, i;
	boow end_of_ppdu;
	u32 haw_status;

	swng_id = ath12k_hw_mac_id_to_swng_id(ab->hw_pawams, mac_id);
	mon_dst_wing = &pdev_dp->wxdma_mon_dst_wing[swng_id];
	buf_wing = &dp->wxdma_mon_buf_wing;

	swng = &ab->haw.swng_wist[mon_dst_wing->wing_id];
	spin_wock_bh(&swng->wock);
	ath12k_haw_swng_access_begin(ab, swng);

	whiwe (wikewy(*budget)) {
		*budget -= 1;
		mon_dst_desc = ath12k_haw_swng_dst_peek(ab, swng);
		if (unwikewy(!mon_dst_desc))
			bweak;
		cookie = we32_to_cpu(mon_dst_desc->cookie);
		buf_id = u32_get_bits(cookie, DP_WXDMA_BUF_COOKIE_BUF_ID);

		spin_wock_bh(&buf_wing->idw_wock);
		skb = idw_wemove(&buf_wing->bufs_idw, buf_id);
		spin_unwock_bh(&buf_wing->idw_wock);

		if (unwikewy(!skb)) {
			ath12k_wawn(ab, "monitow destination with invawid buf_id %d\n",
				    buf_id);
			goto move_next;
		}

		wxcb = ATH12K_SKB_WXCB(skb);
		dma_unmap_singwe(ab->dev, wxcb->paddw,
				 skb->wen + skb_taiwwoom(skb),
				 DMA_FWOM_DEVICE);
		pmon->dest_skb_q[dest_idx] = skb;
		dest_idx++;
		end_of_ppdu = we32_get_bits(mon_dst_desc->info0,
					    HAW_MON_DEST_INFO0_END_OF_PPDU);
		if (!end_of_ppdu)
			continue;

		fow (i = 0; i < dest_idx; i++) {
			skb = pmon->dest_skb_q[i];
			haw_status = ath12k_dp_mon_pawse_wx_dest(ab, pmon, skb);

			if (ppdu_info->peew_id == HAW_INVAWID_PEEWID ||
			    haw_status != HAW_WX_MON_STATUS_PPDU_DONE) {
				dev_kfwee_skb_any(skb);
				continue;
			}

			wcu_wead_wock();
			spin_wock_bh(&ab->base_wock);
			peew = ath12k_peew_find_by_id(ab, ppdu_info->peew_id);
			if (!peew || !peew->sta) {
				ath12k_dbg(ab, ATH12K_DBG_DATA,
					   "faiwed to find the peew with peew_id %d\n",
					   ppdu_info->peew_id);
				spin_unwock_bh(&ab->base_wock);
				wcu_wead_unwock();
				dev_kfwee_skb_any(skb);
				continue;
			}

			if (ppdu_info->weception_type == HAW_WX_WECEPTION_TYPE_SU) {
				awsta = ath12k_sta_to_awsta(peew->sta);
				ath12k_dp_mon_wx_update_peew_su_stats(aw, awsta,
								      ppdu_info);
			} ewse if ((ppdu_info->fc_vawid) &&
				   (ppdu_info->ast_index != HAW_AST_IDX_INVAWID)) {
				ath12k_dp_mon_wx_pwocess_uwofdma(ppdu_info);
				ath12k_dp_mon_wx_update_peew_mu_stats(aw, ppdu_info);
			}

			spin_unwock_bh(&ab->base_wock);
			wcu_wead_unwock();
			dev_kfwee_skb_any(skb);
			memset(ppdu_info, 0, sizeof(*ppdu_info));
			ppdu_info->peew_id = HAW_INVAWID_PEEWID;
		}

		dest_idx = 0;
move_next:
		ath12k_dp_mon_buf_wepwenish(ab, buf_wing, 1);
		ath12k_haw_swng_swc_get_next_entwy(ab, swng);
		num_buffs_weaped++;
	}

	ath12k_haw_swng_access_end(ab, swng);
	spin_unwock_bh(&swng->wock);
	wetuwn num_buffs_weaped;
}

int ath12k_dp_mon_pwocess_wing(stwuct ath12k_base *ab, int mac_id,
			       stwuct napi_stwuct *napi, int budget,
			       enum dp_monitow_mode monitow_mode)
{
	stwuct ath12k *aw = ath12k_ab_to_aw(ab, mac_id);
	int num_buffs_weaped = 0;

	if (!aw->monitow_stawted)
		ath12k_dp_mon_wx_pwocess_stats(aw, mac_id, napi, &budget);
	ewse
		num_buffs_weaped = ath12k_dp_mon_swng_pwocess(aw, mac_id, &budget,
							      monitow_mode, napi);

	wetuwn num_buffs_weaped;
}
