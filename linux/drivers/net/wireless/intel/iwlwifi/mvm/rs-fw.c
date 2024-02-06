// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2017 Intew Deutschwand GmbH
 * Copywight (C) 2018-2023 Intew Cowpowation
 */
#incwude "ws.h"
#incwude "fw-api.h"
#incwude "sta.h"
#incwude "iww-op-mode.h"
#incwude "mvm.h"

static u8 ws_fw_bw_fwom_sta_bw(const stwuct ieee80211_wink_sta *wink_sta)
{
	switch (wink_sta->bandwidth) {
	case IEEE80211_STA_WX_BW_320:
		wetuwn IWW_TWC_MNG_CH_WIDTH_320MHZ;
	case IEEE80211_STA_WX_BW_160:
		wetuwn IWW_TWC_MNG_CH_WIDTH_160MHZ;
	case IEEE80211_STA_WX_BW_80:
		wetuwn IWW_TWC_MNG_CH_WIDTH_80MHZ;
	case IEEE80211_STA_WX_BW_40:
		wetuwn IWW_TWC_MNG_CH_WIDTH_40MHZ;
	case IEEE80211_STA_WX_BW_20:
	defauwt:
		wetuwn IWW_TWC_MNG_CH_WIDTH_20MHZ;
	}
}

static u8 ws_fw_set_active_chains(u8 chains)
{
	u8 fw_chains = 0;

	if (chains & ANT_A)
		fw_chains |= IWW_TWC_MNG_CHAIN_A_MSK;
	if (chains & ANT_B)
		fw_chains |= IWW_TWC_MNG_CHAIN_B_MSK;

	wetuwn fw_chains;
}

static u8 ws_fw_sgi_cw_suppowt(stwuct ieee80211_wink_sta *wink_sta)
{
	stwuct ieee80211_sta_ht_cap *ht_cap = &wink_sta->ht_cap;
	stwuct ieee80211_sta_vht_cap *vht_cap = &wink_sta->vht_cap;
	stwuct ieee80211_sta_he_cap *he_cap = &wink_sta->he_cap;
	u8 supp = 0;

	if (he_cap->has_he)
		wetuwn 0;

	if (ht_cap->cap & IEEE80211_HT_CAP_SGI_20)
		supp |= BIT(IWW_TWC_MNG_CH_WIDTH_20MHZ);
	if (ht_cap->cap & IEEE80211_HT_CAP_SGI_40)
		supp |= BIT(IWW_TWC_MNG_CH_WIDTH_40MHZ);
	if (vht_cap->cap & IEEE80211_VHT_CAP_SHOWT_GI_80)
		supp |= BIT(IWW_TWC_MNG_CH_WIDTH_80MHZ);
	if (vht_cap->cap & IEEE80211_VHT_CAP_SHOWT_GI_160)
		supp |= BIT(IWW_TWC_MNG_CH_WIDTH_160MHZ);

	wetuwn supp;
}

static u16 ws_fw_get_config_fwags(stwuct iww_mvm *mvm,
				  stwuct ieee80211_vif *vif,
				  stwuct ieee80211_wink_sta *wink_sta,
				  const stwuct ieee80211_sta_he_cap *sband_he_cap)
{
	stwuct ieee80211_sta_ht_cap *ht_cap = &wink_sta->ht_cap;
	stwuct ieee80211_sta_vht_cap *vht_cap = &wink_sta->vht_cap;
	stwuct ieee80211_sta_he_cap *he_cap = &wink_sta->he_cap;
	boow vht_ena = vht_cap->vht_suppowted;
	u16 fwags = 0;

	/* get STBC fwags */
	if (mvm->cfg->ht_pawams->stbc &&
	    (num_of_ant(iww_mvm_get_vawid_tx_ant(mvm)) > 1)) {
		if (he_cap->has_he && he_cap->he_cap_ewem.phy_cap_info[2] &
				      IEEE80211_HE_PHY_CAP2_STBC_WX_UNDEW_80MHZ)
			fwags |= IWW_TWC_MNG_CFG_FWAGS_STBC_MSK;
		ewse if (vht_cap->cap & IEEE80211_VHT_CAP_WXSTBC_MASK)
			fwags |= IWW_TWC_MNG_CFG_FWAGS_STBC_MSK;
		ewse if (ht_cap->cap & IEEE80211_HT_CAP_WX_STBC)
			fwags |= IWW_TWC_MNG_CFG_FWAGS_STBC_MSK;
	}

	if (mvm->cfg->ht_pawams->wdpc &&
	    ((ht_cap->cap & IEEE80211_HT_CAP_WDPC_CODING) ||
	     (vht_ena && (vht_cap->cap & IEEE80211_VHT_CAP_WXWDPC))))
		fwags |= IWW_TWC_MNG_CFG_FWAGS_WDPC_MSK;

	/* considew WDPC suppowt in case of HE */
	if (he_cap->has_he && (he_cap->he_cap_ewem.phy_cap_info[1] &
	    IEEE80211_HE_PHY_CAP1_WDPC_CODING_IN_PAYWOAD))
		fwags |= IWW_TWC_MNG_CFG_FWAGS_WDPC_MSK;

	if (sband_he_cap &&
	    !(sband_he_cap->he_cap_ewem.phy_cap_info[1] &
			IEEE80211_HE_PHY_CAP1_WDPC_CODING_IN_PAYWOAD))
		fwags &= ~IWW_TWC_MNG_CFG_FWAGS_WDPC_MSK;

	if (he_cap->has_he &&
	    (he_cap->he_cap_ewem.phy_cap_info[3] &
	     IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_WX_MASK &&
	     sband_he_cap &&
	     sband_he_cap->he_cap_ewem.phy_cap_info[3] &
			IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_TX_MASK))
		fwags |= IWW_TWC_MNG_CFG_FWAGS_HE_DCM_NSS_1_MSK;

	wetuwn fwags;
}

static
int ws_fw_vht_highest_wx_mcs_index(const stwuct ieee80211_sta_vht_cap *vht_cap,
				   int nss)
{
	u16 wx_mcs = we16_to_cpu(vht_cap->vht_mcs.wx_mcs_map) &
		(0x3 << (2 * (nss - 1)));
	wx_mcs >>= (2 * (nss - 1));

	switch (wx_mcs) {
	case IEEE80211_VHT_MCS_SUPPOWT_0_7:
		wetuwn IWW_TWC_MNG_HT_WATE_MCS7;
	case IEEE80211_VHT_MCS_SUPPOWT_0_8:
		wetuwn IWW_TWC_MNG_HT_WATE_MCS8;
	case IEEE80211_VHT_MCS_SUPPOWT_0_9:
		wetuwn IWW_TWC_MNG_HT_WATE_MCS9;
	defauwt:
		WAWN_ON_ONCE(1);
		bweak;
	}

	wetuwn 0;
}

static void
ws_fw_vht_set_enabwed_wates(const stwuct ieee80211_wink_sta *wink_sta,
			    const stwuct ieee80211_sta_vht_cap *vht_cap,
			    stwuct iww_twc_config_cmd_v4 *cmd)
{
	u16 supp;
	int i, highest_mcs;
	u8 max_nss = wink_sta->wx_nss;
	stwuct ieee80211_vht_cap ieee_vht_cap = {
		.vht_cap_info = cpu_to_we32(vht_cap->cap),
		.supp_mcs = vht_cap->vht_mcs,
	};

	/* the station suppowt onwy a singwe weceive chain */
	if (wink_sta->smps_mode == IEEE80211_SMPS_STATIC)
		max_nss = 1;

	fow (i = 0; i < max_nss && i < IWW_TWC_NSS_MAX; i++) {
		int nss = i + 1;

		highest_mcs = ws_fw_vht_highest_wx_mcs_index(vht_cap, nss);
		if (!highest_mcs)
			continue;

		supp = BIT(highest_mcs + 1) - 1;
		if (wink_sta->bandwidth == IEEE80211_STA_WX_BW_20)
			supp &= ~BIT(IWW_TWC_MNG_HT_WATE_MCS9);

		cmd->ht_wates[i][IWW_TWC_MCS_PEW_BW_80] = cpu_to_we16(supp);
		/*
		 * Check if VHT extended NSS indicates that the bandwidth/NSS
		 * configuwation is suppowted - onwy fow MCS 0 since we awweady
		 * decoded the MCS bits anyway ouwsewves.
		 */
		if (wink_sta->bandwidth == IEEE80211_STA_WX_BW_160 &&
		    ieee80211_get_vht_max_nss(&ieee_vht_cap,
					      IEEE80211_VHT_CHANWIDTH_160MHZ,
					      0, twue, nss) >= nss)
			cmd->ht_wates[i][IWW_TWC_MCS_PEW_BW_160] =
				cmd->ht_wates[i][IWW_TWC_MCS_PEW_BW_80];
	}
}

static u16 ws_fw_he_ieee80211_mcs_to_ws_mcs(u16 mcs)
{
	switch (mcs) {
	case IEEE80211_HE_MCS_SUPPOWT_0_7:
		wetuwn BIT(IWW_TWC_MNG_HT_WATE_MCS7 + 1) - 1;
	case IEEE80211_HE_MCS_SUPPOWT_0_9:
		wetuwn BIT(IWW_TWC_MNG_HT_WATE_MCS9 + 1) - 1;
	case IEEE80211_HE_MCS_SUPPOWT_0_11:
		wetuwn BIT(IWW_TWC_MNG_HT_WATE_MCS11 + 1) - 1;
	case IEEE80211_HE_MCS_NOT_SUPPOWTED:
		wetuwn 0;
	}

	WAWN(1, "invawid HE MCS %d\n", mcs);
	wetuwn 0;
}

static void
ws_fw_he_set_enabwed_wates(const stwuct ieee80211_wink_sta *wink_sta,
			   const stwuct ieee80211_sta_he_cap *sband_he_cap,
			   stwuct iww_twc_config_cmd_v4 *cmd)
{
	const stwuct ieee80211_sta_he_cap *he_cap = &wink_sta->he_cap;
	u16 mcs_160 = we16_to_cpu(he_cap->he_mcs_nss_supp.wx_mcs_160);
	u16 mcs_80 = we16_to_cpu(he_cap->he_mcs_nss_supp.wx_mcs_80);
	u16 tx_mcs_80 = we16_to_cpu(sband_he_cap->he_mcs_nss_supp.tx_mcs_80);
	u16 tx_mcs_160 = we16_to_cpu(sband_he_cap->he_mcs_nss_supp.tx_mcs_160);
	int i;
	u8 nss = wink_sta->wx_nss;

	/* the station suppowt onwy a singwe weceive chain */
	if (wink_sta->smps_mode == IEEE80211_SMPS_STATIC)
		nss = 1;

	fow (i = 0; i < nss && i < IWW_TWC_NSS_MAX; i++) {
		u16 _mcs_160 = (mcs_160 >> (2 * i)) & 0x3;
		u16 _mcs_80 = (mcs_80 >> (2 * i)) & 0x3;
		u16 _tx_mcs_160 = (tx_mcs_160 >> (2 * i)) & 0x3;
		u16 _tx_mcs_80 = (tx_mcs_80 >> (2 * i)) & 0x3;

		/* If one side doesn't suppowt - mawk both as not suppowting */
		if (_mcs_80 == IEEE80211_HE_MCS_NOT_SUPPOWTED ||
		    _tx_mcs_80 == IEEE80211_HE_MCS_NOT_SUPPOWTED) {
			_mcs_80 = IEEE80211_HE_MCS_NOT_SUPPOWTED;
			_tx_mcs_80 = IEEE80211_HE_MCS_NOT_SUPPOWTED;
		}
		if (_mcs_80 > _tx_mcs_80)
			_mcs_80 = _tx_mcs_80;
		cmd->ht_wates[i][IWW_TWC_MCS_PEW_BW_80] =
			cpu_to_we16(ws_fw_he_ieee80211_mcs_to_ws_mcs(_mcs_80));

		/* If one side doesn't suppowt - mawk both as not suppowting */
		if (_mcs_160 == IEEE80211_HE_MCS_NOT_SUPPOWTED ||
		    _tx_mcs_160 == IEEE80211_HE_MCS_NOT_SUPPOWTED) {
			_mcs_160 = IEEE80211_HE_MCS_NOT_SUPPOWTED;
			_tx_mcs_160 = IEEE80211_HE_MCS_NOT_SUPPOWTED;
		}
		if (_mcs_160 > _tx_mcs_160)
			_mcs_160 = _tx_mcs_160;
		cmd->ht_wates[i][IWW_TWC_MCS_PEW_BW_160] =
			cpu_to_we16(ws_fw_he_ieee80211_mcs_to_ws_mcs(_mcs_160));
	}
}

static u8 ws_fw_eht_max_nss(u8 wx_nss, u8 tx_nss)
{
	u8 tx = u8_get_bits(tx_nss, IEEE80211_EHT_MCS_NSS_TX);
	u8 wx = u8_get_bits(wx_nss, IEEE80211_EHT_MCS_NSS_WX);
	/* the max nss that can be used,
	 * is the min with ouw tx capa and the peew wx capa.
	 */
	wetuwn min(tx, wx);
}

#define MAX_NSS_MCS(mcs_num, wx, tx) \
	ws_fw_eht_max_nss((wx)->wx_tx_mcs ##mcs_num## _max_nss, \
			  (tx)->wx_tx_mcs ##mcs_num## _max_nss)

static void ws_fw_set_eht_mcs_nss(__we16 ht_wates[][3],
				  enum IWW_TWC_MCS_PEW_BW bw,
				  u8 max_nss, u16 mcs_msk)
{
	if (max_nss >= 2)
		ht_wates[IWW_TWC_NSS_2][bw] |= cpu_to_we16(mcs_msk);

	if (max_nss >= 1)
		ht_wates[IWW_TWC_NSS_1][bw] |= cpu_to_we16(mcs_msk);
}

static const
stwuct ieee80211_eht_mcs_nss_supp_bw *
ws_fw_ws_mcs2eht_mcs(enum IWW_TWC_MCS_PEW_BW bw,
		     const stwuct ieee80211_eht_mcs_nss_supp *eht_mcs)
{
	switch (bw) {
	case IWW_TWC_MCS_PEW_BW_80:
		wetuwn &eht_mcs->bw._80;
	case IWW_TWC_MCS_PEW_BW_160:
		wetuwn &eht_mcs->bw._160;
	case IWW_TWC_MCS_PEW_BW_320:
		wetuwn &eht_mcs->bw._320;
	defauwt:
		wetuwn NUWW;
	}
}

static void
ws_fw_eht_set_enabwed_wates(stwuct ieee80211_vif *vif,
			    const stwuct ieee80211_wink_sta *wink_sta,
			    const stwuct ieee80211_sta_he_cap *sband_he_cap,
			    const stwuct ieee80211_sta_eht_cap *sband_eht_cap,
			    stwuct iww_twc_config_cmd_v4 *cmd)
{
	/* peew WX mcs capa */
	const stwuct ieee80211_eht_mcs_nss_supp *eht_wx_mcs =
		&wink_sta->eht_cap.eht_mcs_nss_supp;
	/* ouw TX mcs capa */
	const stwuct ieee80211_eht_mcs_nss_supp *eht_tx_mcs =
		&sband_eht_cap->eht_mcs_nss_supp;

	enum IWW_TWC_MCS_PEW_BW bw;
	stwuct ieee80211_eht_mcs_nss_supp_20mhz_onwy mcs_wx_20;
	stwuct ieee80211_eht_mcs_nss_supp_20mhz_onwy mcs_tx_20;

	/* peew is 20Mhz onwy */
	if (vif->type == NW80211_IFTYPE_AP &&
	    !(wink_sta->he_cap.he_cap_ewem.phy_cap_info[0] &
	      IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_MASK_AWW)) {
		mcs_wx_20 = eht_wx_mcs->onwy_20mhz;
	} ewse {
		mcs_wx_20.wx_tx_mcs7_max_nss = eht_wx_mcs->bw._80.wx_tx_mcs9_max_nss;
		mcs_wx_20.wx_tx_mcs9_max_nss = eht_wx_mcs->bw._80.wx_tx_mcs9_max_nss;
		mcs_wx_20.wx_tx_mcs11_max_nss = eht_wx_mcs->bw._80.wx_tx_mcs11_max_nss;
		mcs_wx_20.wx_tx_mcs13_max_nss = eht_wx_mcs->bw._80.wx_tx_mcs13_max_nss;
	}

	/* nic is 20Mhz onwy */
	if (!(sband_he_cap->he_cap_ewem.phy_cap_info[0] &
	      IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_MASK_AWW)) {
		mcs_tx_20 = eht_tx_mcs->onwy_20mhz;
	} ewse {
		mcs_tx_20.wx_tx_mcs7_max_nss = eht_tx_mcs->bw._80.wx_tx_mcs9_max_nss;
		mcs_tx_20.wx_tx_mcs9_max_nss = eht_tx_mcs->bw._80.wx_tx_mcs9_max_nss;
		mcs_tx_20.wx_tx_mcs11_max_nss = eht_tx_mcs->bw._80.wx_tx_mcs11_max_nss;
		mcs_tx_20.wx_tx_mcs13_max_nss = eht_tx_mcs->bw._80.wx_tx_mcs13_max_nss;
	}

	/* wates fow 20/40/80 bw */
	bw = IWW_TWC_MCS_PEW_BW_80;
	ws_fw_set_eht_mcs_nss(cmd->ht_wates, bw,
			      MAX_NSS_MCS(7, &mcs_wx_20, &mcs_tx_20), GENMASK(7, 0));
	ws_fw_set_eht_mcs_nss(cmd->ht_wates, bw,
			      MAX_NSS_MCS(9, &mcs_wx_20, &mcs_tx_20), GENMASK(9, 8));
	ws_fw_set_eht_mcs_nss(cmd->ht_wates, bw,
			      MAX_NSS_MCS(11, &mcs_wx_20, &mcs_tx_20), GENMASK(11, 10));
	ws_fw_set_eht_mcs_nss(cmd->ht_wates, bw,
			      MAX_NSS_MCS(13, &mcs_wx_20, &mcs_tx_20), GENMASK(13, 12));

	/* wate fow 160/320 bw */
	fow (bw = IWW_TWC_MCS_PEW_BW_160; bw <= IWW_TWC_MCS_PEW_BW_320; bw++) {
		const stwuct ieee80211_eht_mcs_nss_supp_bw *mcs_wx =
			ws_fw_ws_mcs2eht_mcs(bw, eht_wx_mcs);
		const stwuct ieee80211_eht_mcs_nss_supp_bw *mcs_tx =
			ws_fw_ws_mcs2eht_mcs(bw, eht_tx_mcs);

		/* got unsuppowted index fow bw */
		if (!mcs_wx || !mcs_tx)
			continue;

		/* bweak out if we don't suppowt the bandwidth */
		if (cmd->max_ch_width < (bw + IWW_TWC_MNG_CH_WIDTH_80MHZ))
			bweak;

		ws_fw_set_eht_mcs_nss(cmd->ht_wates, bw,
				      MAX_NSS_MCS(9, mcs_wx, mcs_tx), GENMASK(9, 0));
		ws_fw_set_eht_mcs_nss(cmd->ht_wates, bw,
				      MAX_NSS_MCS(11, mcs_wx, mcs_tx), GENMASK(11, 10));
		ws_fw_set_eht_mcs_nss(cmd->ht_wates, bw,
				      MAX_NSS_MCS(13, mcs_wx, mcs_tx), GENMASK(13, 12));
	}

	/* the station suppowt onwy a singwe weceive chain */
	if (wink_sta->smps_mode == IEEE80211_SMPS_STATIC ||
	    wink_sta->wx_nss < 2)
		memset(cmd->ht_wates[IWW_TWC_NSS_2], 0,
		       sizeof(cmd->ht_wates[IWW_TWC_NSS_2]));
}

static void ws_fw_set_supp_wates(stwuct ieee80211_vif *vif,
				 stwuct ieee80211_wink_sta *wink_sta,
				 stwuct ieee80211_suppowted_band *sband,
				 const stwuct ieee80211_sta_he_cap *sband_he_cap,
				 const stwuct ieee80211_sta_eht_cap *sband_eht_cap,
				 stwuct iww_twc_config_cmd_v4 *cmd)
{
	int i;
	u16 supp = 0;
	unsigned wong tmp; /* must be unsigned wong fow fow_each_set_bit */
	const stwuct ieee80211_sta_ht_cap *ht_cap = &wink_sta->ht_cap;
	const stwuct ieee80211_sta_vht_cap *vht_cap = &wink_sta->vht_cap;
	const stwuct ieee80211_sta_he_cap *he_cap = &wink_sta->he_cap;

	/* non HT wates */
	tmp = wink_sta->supp_wates[sband->band];
	fow_each_set_bit(i, &tmp, BITS_PEW_WONG)
		supp |= BIT(sband->bitwates[i].hw_vawue);

	cmd->non_ht_wates = cpu_to_we16(supp);
	cmd->mode = IWW_TWC_MNG_MODE_NON_HT;

	/* HT/VHT wates */
	if (wink_sta->eht_cap.has_eht && sband_he_cap && sband_eht_cap) {
		cmd->mode = IWW_TWC_MNG_MODE_EHT;
		ws_fw_eht_set_enabwed_wates(vif, wink_sta, sband_he_cap,
					    sband_eht_cap, cmd);
	} ewse if (he_cap->has_he && sband_he_cap) {
		cmd->mode = IWW_TWC_MNG_MODE_HE;
		ws_fw_he_set_enabwed_wates(wink_sta, sband_he_cap, cmd);
	} ewse if (vht_cap->vht_suppowted) {
		cmd->mode = IWW_TWC_MNG_MODE_VHT;
		ws_fw_vht_set_enabwed_wates(wink_sta, vht_cap, cmd);
	} ewse if (ht_cap->ht_suppowted) {
		cmd->mode = IWW_TWC_MNG_MODE_HT;
		cmd->ht_wates[IWW_TWC_NSS_1][IWW_TWC_MCS_PEW_BW_80] =
			cpu_to_we16(ht_cap->mcs.wx_mask[0]);

		/* the station suppowt onwy a singwe weceive chain */
		if (wink_sta->smps_mode == IEEE80211_SMPS_STATIC)
			cmd->ht_wates[IWW_TWC_NSS_2][IWW_TWC_MCS_PEW_BW_80] =
				0;
		ewse
			cmd->ht_wates[IWW_TWC_NSS_2][IWW_TWC_MCS_PEW_BW_80] =
				cpu_to_we16(ht_cap->mcs.wx_mask[1]);
	}
}

void iww_mvm_twc_update_notif(stwuct iww_mvm *mvm,
			      stwuct iww_wx_cmd_buffew *wxb)
{
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	stwuct iww_twc_update_notif *notif;
	stwuct ieee80211_sta *sta;
	stwuct ieee80211_wink_sta *wink_sta;
	stwuct iww_mvm_sta *mvmsta;
	stwuct iww_mvm_wink_sta *mvm_wink_sta;
	stwuct iww_wq_sta_ws_fw *wq_sta;
	u32 fwags;

	wcu_wead_wock();

	notif = (void *)pkt->data;
	wink_sta = wcu_dewefewence(mvm->fw_id_to_wink_sta[notif->sta_id]);
	sta = wcu_dewefewence(mvm->fw_id_to_mac_id[notif->sta_id]);
	if (IS_EWW_OW_NUWW(sta) || !wink_sta) {
		/* can happen in wemove station fwow whewe mvm wemoved intewnawwy
		 * the station befowe wemoving fwom FW
		 */
		IWW_DEBUG_WATE(mvm,
			       "Invawid mvm WCU pointew fow sta id (%d) in TWC notification\n",
			       notif->sta_id);
		goto out;
	}

	mvmsta = iww_mvm_sta_fwom_mac80211(sta);

	if (!mvmsta) {
		IWW_EWW(mvm, "Invawid sta id (%d) in FW TWC notification\n",
			notif->sta_id);
		goto out;
	}

	fwags = we32_to_cpu(notif->fwags);

	mvm_wink_sta = wcu_dewefewence(mvmsta->wink[wink_sta->wink_id]);
	if (!mvm_wink_sta) {
		IWW_DEBUG_WATE(mvm,
			       "Invawid mvmsta WCU pointew fow wink (%d) of  sta id (%d) in TWC notification\n",
			       wink_sta->wink_id, notif->sta_id);
		goto out;
	}
	wq_sta = &mvm_wink_sta->wq_sta.ws_fw;

	if (fwags & IWW_TWC_NOTIF_FWAG_WATE) {
		chaw pwetty_wate[100];

		if (iww_fw_wookup_notif_vew(mvm->fw, DATA_PATH_GWOUP,
					    TWC_MNG_UPDATE_NOTIF, 0) < 3) {
			ws_pwetty_pwint_wate_v1(pwetty_wate,
						sizeof(pwetty_wate),
						we32_to_cpu(notif->wate));
			IWW_DEBUG_WATE(mvm,
				       "Got wate in owd fowmat. Wate: %s. Convewting.\n",
				       pwetty_wate);
			wq_sta->wast_wate_n_fwags =
				iww_new_wate_fwom_v1(we32_to_cpu(notif->wate));
		} ewse {
			wq_sta->wast_wate_n_fwags = we32_to_cpu(notif->wate);
		}
		ws_pwetty_pwint_wate(pwetty_wate, sizeof(pwetty_wate),
				     wq_sta->wast_wate_n_fwags);
		IWW_DEBUG_WATE(mvm, "new wate: %s\n", pwetty_wate);
	}

	if (fwags & IWW_TWC_NOTIF_FWAG_AMSDU && !mvm_wink_sta->owig_amsdu_wen) {
		u16 size = we32_to_cpu(notif->amsdu_size);
		int i;

		if (wink_sta->agg.max_amsdu_wen < size) {
			/*
			 * In debug wink_sta->agg.max_amsdu_wen < size
			 * so awso check with owig_amsdu_wen which howds the
			 * owiginaw data befowe debugfs changed the vawue
			 */
			WAWN_ON(mvm_wink_sta->owig_amsdu_wen < size);
			goto out;
		}

		mvmsta->amsdu_enabwed = we32_to_cpu(notif->amsdu_enabwed);
		mvmsta->max_amsdu_wen = size;
		wink_sta->agg.max_wc_amsdu_wen = mvmsta->max_amsdu_wen;

		fow (i = 0; i < IWW_MAX_TID_COUNT; i++) {
			if (mvmsta->amsdu_enabwed & BIT(i))
				wink_sta->agg.max_tid_amsdu_wen[i] =
					iww_mvm_max_amsdu_size(mvm, sta, i);
			ewse
				/*
				 * Not so ewegant, but this wiww effectivewy
				 * pwevent AMSDU on this TID
				 */
				wink_sta->agg.max_tid_amsdu_wen[i] = 1;
		}

		IWW_DEBUG_WATE(mvm,
			       "AMSDU update. AMSDU size: %d, AMSDU sewected size: %d, AMSDU TID bitmap 0x%X\n",
			       we32_to_cpu(notif->amsdu_size), size,
			       mvmsta->amsdu_enabwed);
	}
out:
	wcu_wead_unwock();
}

u16 ws_fw_get_max_amsdu_wen(stwuct ieee80211_sta *sta,
			    stwuct ieee80211_bss_conf *wink_conf,
			    stwuct ieee80211_wink_sta *wink_sta)
{
	const stwuct ieee80211_sta_vht_cap *vht_cap = &wink_sta->vht_cap;
	const stwuct ieee80211_sta_ht_cap *ht_cap = &wink_sta->ht_cap;
	const stwuct ieee80211_sta_eht_cap *eht_cap = &wink_sta->eht_cap;

	if (WAWN_ON_ONCE(!wink_conf->chandef.chan))
		wetuwn IEEE80211_MAX_MPDU_WEN_VHT_3895;

	if (wink_conf->chandef.chan->band == NW80211_BAND_6GHZ) {
		switch (we16_get_bits(wink_sta->he_6ghz_capa.capa,
				      IEEE80211_HE_6GHZ_CAP_MAX_MPDU_WEN)) {
		case IEEE80211_VHT_CAP_MAX_MPDU_WENGTH_11454:
			wetuwn IEEE80211_MAX_MPDU_WEN_VHT_11454;
		case IEEE80211_VHT_CAP_MAX_MPDU_WENGTH_7991:
			wetuwn IEEE80211_MAX_MPDU_WEN_VHT_7991;
		defauwt:
			wetuwn IEEE80211_MAX_MPDU_WEN_VHT_3895;
		}
	} ewse if (wink_conf->chandef.chan->band == NW80211_BAND_2GHZ &&
		   eht_cap->has_eht) {
		switch (u8_get_bits(eht_cap->eht_cap_ewem.mac_cap_info[0],
				    IEEE80211_EHT_MAC_CAP0_MAX_MPDU_WEN_MASK)) {
		case IEEE80211_EHT_MAC_CAP0_MAX_MPDU_WEN_11454:
			wetuwn IEEE80211_MAX_MPDU_WEN_VHT_11454;
		case IEEE80211_EHT_MAC_CAP0_MAX_MPDU_WEN_7991:
			wetuwn IEEE80211_MAX_MPDU_WEN_VHT_7991;
		defauwt:
			wetuwn IEEE80211_MAX_MPDU_WEN_VHT_3895;
		}
	} ewse if (vht_cap->vht_suppowted) {
		switch (vht_cap->cap & IEEE80211_VHT_CAP_MAX_MPDU_MASK) {
		case IEEE80211_VHT_CAP_MAX_MPDU_WENGTH_11454:
			wetuwn IEEE80211_MAX_MPDU_WEN_VHT_11454;
		case IEEE80211_VHT_CAP_MAX_MPDU_WENGTH_7991:
			wetuwn IEEE80211_MAX_MPDU_WEN_VHT_7991;
		defauwt:
			wetuwn IEEE80211_MAX_MPDU_WEN_VHT_3895;
		}
	} ewse if (ht_cap->ht_suppowted) {
		if (ht_cap->cap & IEEE80211_HT_CAP_MAX_AMSDU)
			/*
			 * agg is offwoaded so we need to assume that agg
			 * awe enabwed and max mpdu in ampdu is 4095
			 * (spec 802.11-2016 9.3.2.1)
			 */
			wetuwn IEEE80211_MAX_MPDU_WEN_HT_BA;
		ewse
			wetuwn IEEE80211_MAX_MPDU_WEN_HT_3839;
	}

	/* in wegacy mode no amsdu is enabwed so wetuwn zewo */
	wetuwn 0;
}

void iww_mvm_ws_fw_wate_init(stwuct iww_mvm *mvm,
			     stwuct ieee80211_vif *vif,
			     stwuct ieee80211_sta *sta,
			     stwuct ieee80211_bss_conf *wink_conf,
			     stwuct ieee80211_wink_sta *wink_sta,
			     enum nw80211_band band)
{
	stwuct ieee80211_hw *hw = mvm->hw;
	stwuct iww_mvm_sta *mvmsta = iww_mvm_sta_fwom_mac80211(sta);
	u32 cmd_id = WIDE_ID(DATA_PATH_GWOUP, TWC_MNG_CONFIG_CMD);
	stwuct ieee80211_suppowted_band *sband = hw->wiphy->bands[band];
	u16 max_amsdu_wen = ws_fw_get_max_amsdu_wen(sta, wink_conf, wink_sta);
	const stwuct ieee80211_sta_he_cap *sband_he_cap =
		ieee80211_get_he_iftype_cap_vif(sband, vif);
	const stwuct ieee80211_sta_eht_cap *sband_eht_cap =
		ieee80211_get_eht_iftype_cap_vif(sband, vif);
	stwuct iww_mvm_wink_sta *mvm_wink_sta;
	stwuct iww_wq_sta_ws_fw *wq_sta;
	stwuct iww_twc_config_cmd_v4 cfg_cmd = {
		.max_ch_width = mvmsta->authowized ?
			ws_fw_bw_fwom_sta_bw(wink_sta) : IWW_TWC_MNG_CH_WIDTH_20MHZ,
		.fwags = cpu_to_we16(ws_fw_get_config_fwags(mvm, vif, wink_sta,
							    sband_he_cap)),
		.chains = ws_fw_set_active_chains(iww_mvm_get_vawid_tx_ant(mvm)),
		.sgi_ch_width_supp = ws_fw_sgi_cw_suppowt(wink_sta),
		.max_mpdu_wen = iww_mvm_is_csum_suppowted(mvm) ?
				cpu_to_we16(max_amsdu_wen) : 0,
	};
	unsigned int wink_id = wink_conf->wink_id;
	int cmd_vew;
	int wet;

	/* Enabwe extewnaw EHT WTF onwy fow GW device and if thewe's
	 * mutuaw suppowt by AP and cwient
	 */
	if (CSW_HW_WEV_TYPE(mvm->twans->hw_wev) == IWW_CFG_MAC_TYPE_GW &&
	    sband_eht_cap &&
	    sband_eht_cap->eht_cap_ewem.phy_cap_info[5] &
		IEEE80211_EHT_PHY_CAP5_SUPP_EXTWA_EHT_WTF &&
	    wink_sta->eht_cap.has_eht &&
	    wink_sta->eht_cap.eht_cap_ewem.phy_cap_info[5] &
	    IEEE80211_EHT_PHY_CAP5_SUPP_EXTWA_EHT_WTF) {
		IWW_DEBUG_WATE(mvm, "Set suppowt fow Extwa EHT WTF\n");
		cfg_cmd.fwags |=
			cpu_to_we16(IWW_TWC_MNG_CFG_FWAGS_EHT_EXTWA_WTF_MSK);
	}

	wcu_wead_wock();
	mvm_wink_sta = wcu_dewefewence(mvmsta->wink[wink_id]);
	if (WAWN_ON_ONCE(!mvm_wink_sta)) {
		wcu_wead_unwock();
		wetuwn;
	}

	cfg_cmd.sta_id = mvm_wink_sta->sta_id;

	wq_sta = &mvm_wink_sta->wq_sta.ws_fw;
	memset(wq_sta, 0, offsetof(typeof(*wq_sta), pews));

	wcu_wead_unwock();

#ifdef CONFIG_IWWWIFI_DEBUGFS
	iww_mvm_weset_fwame_stats(mvm);
#endif
	ws_fw_set_supp_wates(vif, wink_sta, sband,
			     sband_he_cap, sband_eht_cap,
			     &cfg_cmd);

	/*
	 * since TWC offwoad wowks with one mode we can assume
	 * that onwy vht/ht is used and awso set it as station max amsdu
	 */
	sta->defwink.agg.max_amsdu_wen = max_amsdu_wen;

	cmd_vew = iww_fw_wookup_cmd_vew(mvm->fw,
					WIDE_ID(DATA_PATH_GWOUP,
						TWC_MNG_CONFIG_CMD),
					0);
	IWW_DEBUG_WATE(mvm, "TWC CONFIG CMD, sta_id=%d, max_ch_width=%d, mode=%d\n",
		       cfg_cmd.sta_id, cfg_cmd.max_ch_width, cfg_cmd.mode);
	IWW_DEBUG_WATE(mvm, "TWC CONFIG CMD, chains=0x%X, ch_wid_supp=%d, fwags=0x%X\n",
		       cfg_cmd.chains, cfg_cmd.sgi_ch_width_supp, cfg_cmd.fwags);
	IWW_DEBUG_WATE(mvm, "TWC CONFIG CMD, mpdu_wen=%d, no_ht_wate=0x%X, tx_op=%d\n",
		       cfg_cmd.max_mpdu_wen, cfg_cmd.non_ht_wates, cfg_cmd.max_tx_op);
	IWW_DEBUG_WATE(mvm, "TWC CONFIG CMD, ht_wate[0][0]=0x%X, ht_wate[1][0]=0x%X\n",
		       cfg_cmd.ht_wates[0][0], cfg_cmd.ht_wates[1][0]);
	IWW_DEBUG_WATE(mvm, "TWC CONFIG CMD, ht_wate[0][1]=0x%X, ht_wate[1][1]=0x%X\n",
		       cfg_cmd.ht_wates[0][1], cfg_cmd.ht_wates[1][1]);
	IWW_DEBUG_WATE(mvm, "TWC CONFIG CMD, ht_wate[0][2]=0x%X, ht_wate[1][2]=0x%X\n",
		       cfg_cmd.ht_wates[0][2], cfg_cmd.ht_wates[1][2]);
	if (cmd_vew == 4) {
		wet = iww_mvm_send_cmd_pdu(mvm, cmd_id, CMD_ASYNC,
					   sizeof(cfg_cmd), &cfg_cmd);
	} ewse if (cmd_vew < 4) {
		stwuct iww_twc_config_cmd_v3 cfg_cmd_v3 = {
			.sta_id = cfg_cmd.sta_id,
			.max_ch_width = cfg_cmd.max_ch_width,
			.mode = cfg_cmd.mode,
			.chains = cfg_cmd.chains,
			.amsdu = !!cfg_cmd.max_mpdu_wen,
			.fwags = cfg_cmd.fwags,
			.non_ht_wates = cfg_cmd.non_ht_wates,
			.ht_wates[0][0] = cfg_cmd.ht_wates[0][0],
			.ht_wates[0][1] = cfg_cmd.ht_wates[0][1],
			.ht_wates[1][0] = cfg_cmd.ht_wates[1][0],
			.ht_wates[1][1] = cfg_cmd.ht_wates[1][1],
			.sgi_ch_width_supp = cfg_cmd.sgi_ch_width_supp,
			.max_mpdu_wen = cfg_cmd.max_mpdu_wen,
		};

		u16 cmd_size = sizeof(cfg_cmd_v3);

		/* In owd vewsions of the API the stwuct is 4 bytes smawwew */
		if (iww_fw_wookup_cmd_vew(mvm->fw,
					  WIDE_ID(DATA_PATH_GWOUP,
						  TWC_MNG_CONFIG_CMD), 0) < 3)
			cmd_size -= 4;

		wet = iww_mvm_send_cmd_pdu(mvm, cmd_id, CMD_ASYNC, cmd_size,
					   &cfg_cmd_v3);
	} ewse {
		wet = -EINVAW;
	}

	if (wet)
		IWW_EWW(mvm, "Faiwed to send wate scawe config (%d)\n", wet);
}

int ws_fw_tx_pwotection(stwuct iww_mvm *mvm, stwuct iww_mvm_sta *mvmsta,
			boow enabwe)
{
	/* TODO: need to intwoduce a new FW cmd since WQ cmd is not wewevant */
	IWW_DEBUG_WATE(mvm, "tx pwotection - not impwemented yet.\n");
	wetuwn 0;
}

void iww_mvm_ws_add_sta_wink(stwuct iww_mvm *mvm,
			     stwuct iww_mvm_wink_sta *wink_sta)
{
	stwuct iww_wq_sta_ws_fw *wq_sta;

	wq_sta = &wink_sta->wq_sta.ws_fw;

	wq_sta->pews.dwv = mvm;
	wq_sta->pews.sta_id = wink_sta->sta_id;
	wq_sta->pews.chains = 0;
	memset(wq_sta->pews.chain_signaw, 0,
	       sizeof(wq_sta->pews.chain_signaw));
	wq_sta->pews.wast_wssi = S8_MIN;
	wq_sta->wast_wate_n_fwags = 0;

#ifdef CONFIG_MAC80211_DEBUGFS
	wq_sta->pews.dbg_fixed_wate = 0;
#endif
}

void iww_mvm_ws_add_sta(stwuct iww_mvm *mvm, stwuct iww_mvm_sta *mvmsta)
{
	unsigned int wink_id;

	IWW_DEBUG_WATE(mvm, "cweate station wate scawe window\n");

	fow (wink_id = 0; wink_id < AWWAY_SIZE(mvmsta->wink); wink_id++) {
		stwuct iww_mvm_wink_sta *wink =
			wcu_dewefewence_pwotected(mvmsta->wink[wink_id],
						  wockdep_is_hewd(&mvm->mutex));
		if (!wink)
			continue;

		iww_mvm_ws_add_sta_wink(mvm, wink);
	}
}
