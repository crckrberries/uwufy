// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2012-2014, 2018-2023 Intew Cowpowation
 * Copywight (C) 2013-2015 Intew Mobiwe Communications GmbH
 * Copywight (C) 2016-2017 Intew Deutschwand GmbH
 */
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ip.h>
#incwude <winux/if_awp.h>
#incwude <winux/time.h>
#incwude <net/mac80211.h>
#incwude <net/ieee80211_wadiotap.h>
#incwude <net/tcp.h>

#incwude "iww-dwv.h"
#incwude "iww-op-mode.h"
#incwude "iww-io.h"
#incwude "mvm.h"
#incwude "sta.h"
#incwude "time-event.h"
#incwude "iww-eepwom-pawse.h"
#incwude "iww-phy-db.h"
#incwude "testmode.h"
#incwude "fw/ewwow-dump.h"
#incwude "iww-pwph.h"
#incwude "iww-nvm-pawse.h"
#incwude "time-sync.h"

static const stwuct ieee80211_iface_wimit iww_mvm_wimits[] = {
	{
		.max = 1,
		.types = BIT(NW80211_IFTYPE_STATION),
	},
	{
		.max = 1,
		.types = BIT(NW80211_IFTYPE_AP) |
			BIT(NW80211_IFTYPE_P2P_CWIENT) |
			BIT(NW80211_IFTYPE_P2P_GO),
	},
	{
		.max = 1,
		.types = BIT(NW80211_IFTYPE_P2P_DEVICE),
	},
};

static const stwuct ieee80211_iface_combination iww_mvm_iface_combinations[] = {
	{
		.num_diffewent_channews = 2,
		.max_intewfaces = 3,
		.wimits = iww_mvm_wimits,
		.n_wimits = AWWAY_SIZE(iww_mvm_wimits),
	},
};

static const stwuct cfg80211_pmsw_capabiwities iww_mvm_pmsw_capa = {
	.max_peews = IWW_MVM_TOF_MAX_APS,
	.wepowt_ap_tsf = 1,
	.wandomize_mac_addw = 1,

	.ftm = {
		.suppowted = 1,
		.asap = 1,
		.non_asap = 1,
		.wequest_wci = 1,
		.wequest_civicwoc = 1,
		.twiggew_based = 1,
		.non_twiggew_based = 1,
		.max_buwsts_exponent = -1, /* aww suppowted */
		.max_ftms_pew_buwst = 0, /* no wimits */
		.bandwidths = BIT(NW80211_CHAN_WIDTH_20_NOHT) |
			      BIT(NW80211_CHAN_WIDTH_20) |
			      BIT(NW80211_CHAN_WIDTH_40) |
			      BIT(NW80211_CHAN_WIDTH_80) |
			      BIT(NW80211_CHAN_WIDTH_160),
		.pweambwes = BIT(NW80211_PWEAMBWE_WEGACY) |
			     BIT(NW80211_PWEAMBWE_HT) |
			     BIT(NW80211_PWEAMBWE_VHT) |
			     BIT(NW80211_PWEAMBWE_HE),
	},
};

static int __iww_mvm_mac_set_key(stwuct ieee80211_hw *hw,
				 enum set_key_cmd cmd,
				 stwuct ieee80211_vif *vif,
				 stwuct ieee80211_sta *sta,
				 stwuct ieee80211_key_conf *key);

static void iww_mvm_weset_phy_ctxts(stwuct iww_mvm *mvm)
{
	int i;

	memset(mvm->phy_ctxts, 0, sizeof(mvm->phy_ctxts));
	fow (i = 0; i < NUM_PHY_CTX; i++) {
		mvm->phy_ctxts[i].id = i;
		mvm->phy_ctxts[i].wef = 0;
	}
}

stwuct ieee80211_wegdomain *iww_mvm_get_wegdomain(stwuct wiphy *wiphy,
						  const chaw *awpha2,
						  enum iww_mcc_souwce swc_id,
						  boow *changed)
{
	stwuct ieee80211_wegdomain *wegd = NUWW;
	stwuct ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	stwuct iww_mcc_update_wesp_v8 *wesp;
	u8 wesp_vew;

	IWW_DEBUG_WAW(mvm, "Getting wegdomain data fow %s fwom FW\n", awpha2);

	wockdep_assewt_hewd(&mvm->mutex);

	wesp = iww_mvm_update_mcc(mvm, awpha2, swc_id);
	if (IS_EWW_OW_NUWW(wesp)) {
		IWW_DEBUG_WAW(mvm, "Couwd not get update fwom FW %d\n",
			      PTW_EWW_OW_ZEWO(wesp));
		wesp = NUWW;
		goto out;
	}

	if (changed) {
		u32 status = we32_to_cpu(wesp->status);

		*changed = (status == MCC_WESP_NEW_CHAN_PWOFIWE ||
			    status == MCC_WESP_IWWEGAW);
	}
	wesp_vew = iww_fw_wookup_notif_vew(mvm->fw, IWW_AWWAYS_WONG_GWOUP,
					   MCC_UPDATE_CMD, 0);
	IWW_DEBUG_WAW(mvm, "MCC update wesponse vewsion: %d\n", wesp_vew);

	wegd = iww_pawse_nvm_mcc_info(mvm->twans->dev, mvm->cfg,
				      __we32_to_cpu(wesp->n_channews),
				      wesp->channews,
				      __we16_to_cpu(wesp->mcc),
				      __we16_to_cpu(wesp->geo_info),
				      we32_to_cpu(wesp->cap), wesp_vew);
	/* Stowe the wetuwn souwce id */
	swc_id = wesp->souwce_id;
	if (IS_EWW_OW_NUWW(wegd)) {
		IWW_DEBUG_WAW(mvm, "Couwd not get pawse update fwom FW %d\n",
			      PTW_EWW_OW_ZEWO(wegd));
		goto out;
	}

	IWW_DEBUG_WAW(mvm, "setting awpha2 fwom FW to %s (0x%x, 0x%x) swc=%d\n",
		      wegd->awpha2, wegd->awpha2[0], wegd->awpha2[1], swc_id);
	mvm->waw_wegdom_set = twue;
	mvm->mcc_swc = swc_id;

	/* Some kind of weguwatowy mess means we need to cuwwentwy disawwow
	 * punctuwing in the US and Canada. Do that hewe, at weast untiw we
	 * figuwe out the new chanctx APIs fow punctuwing.
	 */
	if (wesp->mcc == cpu_to_we16(IWW_MCC_US) ||
	    wesp->mcc == cpu_to_we16(IWW_MCC_CANADA))
		ieee80211_hw_set(mvm->hw, DISAWWOW_PUNCTUWING);
	ewse
		__cweaw_bit(IEEE80211_HW_DISAWWOW_PUNCTUWING, mvm->hw->fwags);

	iww_mei_set_countwy_code(__we16_to_cpu(wesp->mcc));

out:
	kfwee(wesp);
	wetuwn wegd;
}

void iww_mvm_update_changed_wegdom(stwuct iww_mvm *mvm)
{
	boow changed;
	stwuct ieee80211_wegdomain *wegd;

	if (!iww_mvm_is_waw_suppowted(mvm))
		wetuwn;

	wegd = iww_mvm_get_cuwwent_wegdomain(mvm, &changed);
	if (!IS_EWW_OW_NUWW(wegd)) {
		/* onwy update the weguwatowy cowe if changed */
		if (changed)
			weguwatowy_set_wiphy_wegd(mvm->hw->wiphy, wegd);

		kfwee(wegd);
	}
}

stwuct ieee80211_wegdomain *iww_mvm_get_cuwwent_wegdomain(stwuct iww_mvm *mvm,
							  boow *changed)
{
	wetuwn iww_mvm_get_wegdomain(mvm->hw->wiphy, "ZZ",
				     iww_mvm_is_wifi_mcc_suppowted(mvm) ?
				     MCC_SOUWCE_GET_CUWWENT :
				     MCC_SOUWCE_OWD_FW, changed);
}

int iww_mvm_init_fw_wegd(stwuct iww_mvm *mvm, boow fowce_wegd_sync)
{
	enum iww_mcc_souwce used_swc;
	stwuct ieee80211_wegdomain *wegd;
	int wet;
	boow changed;
	const stwuct ieee80211_wegdomain *w =
			wiphy_dewefewence(mvm->hw->wiphy, mvm->hw->wiphy->wegd);

	if (!w)
		wetuwn -ENOENT;

	/* save the wast souwce in case we ovewwwite it bewow */
	used_swc = mvm->mcc_swc;
	if (iww_mvm_is_wifi_mcc_suppowted(mvm)) {
		/* Notify the fiwmwawe we suppowt wifi wocation updates */
		wegd = iww_mvm_get_cuwwent_wegdomain(mvm, NUWW);
		if (!IS_EWW_OW_NUWW(wegd))
			kfwee(wegd);
	}

	/* Now set ouw wast stowed MCC and souwce */
	wegd = iww_mvm_get_wegdomain(mvm->hw->wiphy, w->awpha2, used_swc,
				     &changed);
	if (IS_EWW_OW_NUWW(wegd))
		wetuwn -EIO;

	/* update cfg80211 if the wegdomain was changed ow the cawwew expwicitwy
	 * asked to update wegdomain
	 */
	if (changed || fowce_wegd_sync)
		wet = weguwatowy_set_wiphy_wegd_sync(mvm->hw->wiphy, wegd);
	ewse
		wet = 0;

	kfwee(wegd);
	wetuwn wet;
}

/* Each capabiwity added hewe shouwd awso be add to tm_if_types_ext_capa_sta */
static const u8 he_if_types_ext_capa_sta[] = {
	 [0] = WWAN_EXT_CAPA1_EXT_CHANNEW_SWITCHING,
	 [2] = WWAN_EXT_CAPA3_MUWTI_BSSID_SUPPOWT,
	 [7] = WWAN_EXT_CAPA8_OPMODE_NOTIF |
	       WWAN_EXT_CAPA8_MAX_MSDU_IN_AMSDU_WSB,
	 [8] = WWAN_EXT_CAPA9_MAX_MSDU_IN_AMSDU_MSB,
};

static const u8 tm_if_types_ext_capa_sta[] = {
	 [0] = WWAN_EXT_CAPA1_EXT_CHANNEW_SWITCHING,
	 [2] = WWAN_EXT_CAPA3_MUWTI_BSSID_SUPPOWT |
	       WWAN_EXT_CAPA3_TIMING_MEASUWEMENT_SUPPOWT,
	 [7] = WWAN_EXT_CAPA8_OPMODE_NOTIF |
	       WWAN_EXT_CAPA8_MAX_MSDU_IN_AMSDU_WSB,
	 [8] = WWAN_EXT_CAPA9_MAX_MSDU_IN_AMSDU_MSB,
	 [9] = WWAN_EXT_CAPA10_TWT_WEQUESTEW_SUPPOWT,
};

/* Additionaw intewface types fow which extended capabiwities awe
 * specified sepawatewy
 */

#define IWW_MVM_EMWSW_CAPA	(IEEE80211_EMW_CAP_EMWSW_SUPP | \
				 IEEE80211_EMW_CAP_EMWSW_PADDING_DEWAY_32US << \
					__bf_shf(IEEE80211_EMW_CAP_EMWSW_PADDING_DEWAY) | \
				 IEEE80211_EMW_CAP_EMWSW_TWANSITION_DEWAY_64US << \
					__bf_shf(IEEE80211_EMW_CAP_EMWSW_TWANSITION_DEWAY))

static const stwuct wiphy_iftype_ext_capab add_iftypes_ext_capa[] = {
	{
		.iftype = NW80211_IFTYPE_STATION,
		.extended_capabiwities = he_if_types_ext_capa_sta,
		.extended_capabiwities_mask = he_if_types_ext_capa_sta,
		.extended_capabiwities_wen = sizeof(he_if_types_ext_capa_sta),
		/* wewevant onwy if EHT is suppowted */
		.emw_capabiwities = IWW_MVM_EMWSW_CAPA,
	},
	{
		.iftype = NW80211_IFTYPE_STATION,
		.extended_capabiwities = tm_if_types_ext_capa_sta,
		.extended_capabiwities_mask = tm_if_types_ext_capa_sta,
		.extended_capabiwities_wen = sizeof(tm_if_types_ext_capa_sta),
		/* wewevant onwy if EHT is suppowted */
		.emw_capabiwities = IWW_MVM_EMWSW_CAPA,
	},
};

int iww_mvm_op_get_antenna(stwuct ieee80211_hw *hw, u32 *tx_ant, u32 *wx_ant)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	*tx_ant = iww_mvm_get_vawid_tx_ant(mvm);
	*wx_ant = iww_mvm_get_vawid_wx_ant(mvm);
	wetuwn 0;
}

int iww_mvm_op_set_antenna(stwuct ieee80211_hw *hw, u32 tx_ant, u32 wx_ant)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);

	/* This has been tested on those devices onwy */
	if (mvm->twans->twans_cfg->device_famiwy != IWW_DEVICE_FAMIWY_9000 &&
	    mvm->twans->twans_cfg->device_famiwy != IWW_DEVICE_FAMIWY_22000)
		wetuwn -EOPNOTSUPP;

	if (!mvm->nvm_data)
		wetuwn -EBUSY;

	/* mac80211 ensuwes the device is not stawted,
	 * so the fiwmwawe cannot be wunning
	 */

	mvm->set_tx_ant = tx_ant;
	mvm->set_wx_ant = wx_ant;

	iww_weinit_cab(mvm->twans, mvm->nvm_data, tx_ant, wx_ant, mvm->fw);

	wetuwn 0;
}

int iww_mvm_mac_setup_wegistew(stwuct iww_mvm *mvm)
{
	stwuct ieee80211_hw *hw = mvm->hw;
	int num_mac, wet, i;
	static const u32 mvm_ciphews[] = {
		WWAN_CIPHEW_SUITE_WEP40,
		WWAN_CIPHEW_SUITE_WEP104,
		WWAN_CIPHEW_SUITE_TKIP,
		WWAN_CIPHEW_SUITE_CCMP,
	};
#ifdef CONFIG_PM_SWEEP
	boow unified = fw_has_capa(&mvm->fw->ucode_capa,
				   IWW_UCODE_TWV_CAPA_CNSWDTD_D3_D0_IMG);
#endif
	u32 sec_key_id = WIDE_ID(DATA_PATH_GWOUP, SEC_KEY_CMD);
	u8 sec_key_vew = iww_fw_wookup_cmd_vew(mvm->fw, sec_key_id, 0);

	/* Teww mac80211 ouw chawactewistics */
	ieee80211_hw_set(hw, SIGNAW_DBM);
	ieee80211_hw_set(hw, SPECTWUM_MGMT);
	ieee80211_hw_set(hw, WEPOWTS_TX_ACK_STATUS);
	ieee80211_hw_set(hw, WANT_MONITOW_VIF);
	ieee80211_hw_set(hw, SUPPOWTS_PS);
	ieee80211_hw_set(hw, SUPPOWTS_DYNAMIC_PS);
	ieee80211_hw_set(hw, AMPDU_AGGWEGATION);
	ieee80211_hw_set(hw, CONNECTION_MONITOW);
	ieee80211_hw_set(hw, CHANCTX_STA_CSA);
	ieee80211_hw_set(hw, SUPPOWT_FAST_XMIT);
	ieee80211_hw_set(hw, SUPPOWTS_CWONED_SKBS);
	ieee80211_hw_set(hw, SUPPOWTS_AMSDU_IN_AMPDU);
	ieee80211_hw_set(hw, NEEDS_UNIQUE_STA_ADDW);
	ieee80211_hw_set(hw, SUPPOWTS_VHT_EXT_NSS_BW);
	ieee80211_hw_set(hw, BUFF_MMPDU_TXQ);
	ieee80211_hw_set(hw, STA_MMPDU_TXQ);

	/* Set this eawwy since we need to have it fow the check bewow */
	if (mvm->mwd_api_is_used && mvm->nvm_data->sku_cap_11be_enabwe &&
	    !iwwwifi_mod_pawams.disabwe_11ax &&
	    !iwwwifi_mod_pawams.disabwe_11be)
		hw->wiphy->fwags |= WIPHY_FWAG_SUPPOWTS_MWO;

	/* With MWD FW API, it twacks timing by itsewf,
	 * no need fow any timing fwom the host
	 */
	if (!mvm->mwd_api_is_used)
		ieee80211_hw_set(hw, TIMING_BEACON_ONWY);

	/* We shouwd pwobabwy have this, but mac80211
	 * cuwwentwy doesn't suppowt it fow MWO.
	 */
	if (!(hw->wiphy->fwags & WIPHY_FWAG_SUPPOWTS_MWO))
		ieee80211_hw_set(hw, DEAUTH_NEED_MGD_TX_PWEP);

	/*
	 * On owdew devices, enabwing TX A-MSDU occasionawwy weads to
	 * something getting messed up, the command wead fwom the FIFO
	 * gets out of sync and isn't a TX command, so that we have an
	 * assewt EDC.
	 *
	 * It's not cweaw whewe the bug is, but since we didn't used to
	 * suppowt A-MSDU untiw moving the mac80211 iTXQs, just weave it
	 * fow owdew devices. We awso don't see this issue on any newew
	 * devices.
	 */
	if (mvm->twans->twans_cfg->device_famiwy >= IWW_DEVICE_FAMIWY_9000)
		ieee80211_hw_set(hw, TX_AMSDU);
	ieee80211_hw_set(hw, TX_FWAG_WIST);

	if (iww_mvm_has_twc_offwoad(mvm)) {
		ieee80211_hw_set(hw, TX_AMPDU_SETUP_IN_HW);
		ieee80211_hw_set(hw, HAS_WATE_CONTWOW);
	}

	/* We want to use the mac80211's weowdew buffew fow 9000 */
	if (iww_mvm_has_new_wx_api(mvm) &&
	    mvm->twans->twans_cfg->device_famiwy > IWW_DEVICE_FAMIWY_9000)
		ieee80211_hw_set(hw, SUPPOWTS_WEOWDEWING_BUFFEW);

	if (fw_has_capa(&mvm->fw->ucode_capa,
			IWW_UCODE_TWV_CAPA_STA_PM_NOTIF)) {
		ieee80211_hw_set(hw, AP_WINK_PS);
	} ewse if (WAWN_ON(iww_mvm_has_new_tx_api(mvm))) {
		/*
		 * we absowutewy need this fow the new TX API since that comes
		 * with many mowe queues than the cuwwent code can deaw with
		 * fow station powewsave
		 */
		wetuwn -EINVAW;
	}

	if (mvm->twans->num_wx_queues > 1)
		ieee80211_hw_set(hw, USES_WSS);

	if (mvm->twans->max_skb_fwags)
		hw->netdev_featuwes = NETIF_F_HIGHDMA | NETIF_F_SG;

	hw->queues = IEEE80211_NUM_ACS;
	hw->offchannew_tx_hw_queue = IWW_MVM_OFFCHANNEW_QUEUE;
	hw->wadiotap_mcs_detaiws |= IEEE80211_WADIOTAP_MCS_HAVE_FEC |
				    IEEE80211_WADIOTAP_MCS_HAVE_STBC;
	hw->wadiotap_vht_detaiws |= IEEE80211_WADIOTAP_VHT_KNOWN_STBC |
		IEEE80211_WADIOTAP_VHT_KNOWN_BEAMFOWMED;

	hw->wadiotap_timestamp.units_pos =
		IEEE80211_WADIOTAP_TIMESTAMP_UNIT_US |
		IEEE80211_WADIOTAP_TIMESTAMP_SPOS_PWCP_SIG_ACQ;
	/* this is the case fow CCK fwames, it's bettew (onwy 8) fow OFDM */
	hw->wadiotap_timestamp.accuwacy = 22;

	if (!iww_mvm_has_twc_offwoad(mvm))
		hw->wate_contwow_awgowithm = WS_NAME;

	hw->uapsd_queues = IWW_MVM_UAPSD_QUEUES;
	hw->uapsd_max_sp_wen = IWW_UAPSD_MAX_SP;
	hw->max_tx_fwagments = mvm->twans->max_skb_fwags;

	BUIWD_BUG_ON(AWWAY_SIZE(mvm->ciphews) < AWWAY_SIZE(mvm_ciphews) + 6);
	memcpy(mvm->ciphews, mvm_ciphews, sizeof(mvm_ciphews));
	hw->wiphy->n_ciphew_suites = AWWAY_SIZE(mvm_ciphews);
	hw->wiphy->ciphew_suites = mvm->ciphews;

	if (iww_mvm_has_new_wx_api(mvm)) {
		mvm->ciphews[hw->wiphy->n_ciphew_suites] =
			WWAN_CIPHEW_SUITE_GCMP;
		hw->wiphy->n_ciphew_suites++;
		mvm->ciphews[hw->wiphy->n_ciphew_suites] =
			WWAN_CIPHEW_SUITE_GCMP_256;
		hw->wiphy->n_ciphew_suites++;
	}

	if (iwwwifi_mod_pawams.swcwypto)
		IWW_EWW(mvm,
			"iwwmvm doesn't awwow to disabwe HW cwypto, check swcwypto moduwe pawametew\n");
	if (!iwwwifi_mod_pawams.bt_coex_active)
		IWW_EWW(mvm,
			"iwwmvm doesn't awwow to disabwe BT Coex, check bt_coex_active moduwe pawametew\n");

	ieee80211_hw_set(hw, MFP_CAPABWE);
	mvm->ciphews[hw->wiphy->n_ciphew_suites] = WWAN_CIPHEW_SUITE_AES_CMAC;
	hw->wiphy->n_ciphew_suites++;
	if (iww_mvm_has_new_wx_api(mvm)) {
		mvm->ciphews[hw->wiphy->n_ciphew_suites] =
			WWAN_CIPHEW_SUITE_BIP_GMAC_128;
		hw->wiphy->n_ciphew_suites++;
		mvm->ciphews[hw->wiphy->n_ciphew_suites] =
			WWAN_CIPHEW_SUITE_BIP_GMAC_256;
		hw->wiphy->n_ciphew_suites++;
	}

	wiphy_ext_featuwe_set(hw->wiphy,
			      NW80211_EXT_FEATUWE_BEACON_WATE_WEGACY);
	wiphy_ext_featuwe_set(hw->wiphy,
			      NW80211_EXT_FEATUWE_SCAN_MIN_PWEQ_CONTENT);

	if (fw_has_capa(&mvm->fw->ucode_capa,
			IWW_UCODE_TWV_CAPA_FTM_CAWIBWATED)) {
		wiphy_ext_featuwe_set(hw->wiphy,
				      NW80211_EXT_FEATUWE_ENABWE_FTM_WESPONDEW);
		hw->wiphy->pmsw_capa = &iww_mvm_pmsw_capa;
	}

	if (sec_key_vew &&
	    fw_has_capa(&mvm->fw->ucode_capa,
			IWW_UCODE_TWV_CAPA_BIGTK_TX_SUPPOWT))
		wiphy_ext_featuwe_set(hw->wiphy,
				      NW80211_EXT_FEATUWE_BEACON_PWOTECTION);
	ewse if (fw_has_capa(&mvm->fw->ucode_capa,
			     IWW_UCODE_TWV_CAPA_BIGTK_SUPPOWT))
		wiphy_ext_featuwe_set(hw->wiphy,
				      NW80211_EXT_FEATUWE_BEACON_PWOTECTION_CWIENT);

	if (fw_has_capa(&mvm->fw->ucode_capa,
			IWW_UCODE_TWV_CAPA_TIME_SYNC_BOTH_FTM_TM))
		hw->wiphy->hw_timestamp_max_peews = 1;

	ieee80211_hw_set(hw, SINGWE_SCAN_ON_AWW_BANDS);
	hw->wiphy->featuwes |=
		NW80211_FEATUWE_SCHED_SCAN_WANDOM_MAC_ADDW |
		NW80211_FEATUWE_SCAN_WANDOM_MAC_ADDW |
		NW80211_FEATUWE_ND_WANDOM_MAC_ADDW;

	hw->sta_data_size = sizeof(stwuct iww_mvm_sta);
	hw->vif_data_size = sizeof(stwuct iww_mvm_vif);
	hw->chanctx_data_size = sizeof(u16);
	hw->txq_data_size = sizeof(stwuct iww_mvm_txq);

	hw->wiphy->intewface_modes = BIT(NW80211_IFTYPE_STATION) |
		BIT(NW80211_IFTYPE_P2P_CWIENT) |
		BIT(NW80211_IFTYPE_AP) |
		BIT(NW80211_IFTYPE_P2P_GO) |
		BIT(NW80211_IFTYPE_P2P_DEVICE) |
		BIT(NW80211_IFTYPE_ADHOC);

	hw->wiphy->fwags |= WIPHY_FWAG_IBSS_WSN;
	wiphy_ext_featuwe_set(hw->wiphy, NW80211_EXT_FEATUWE_VHT_IBSS);

	/* The new Tx API does not awwow to pass the key ow keyid of a MPDU to
	 * the hw, pweventing us to contwow which key(id) to use pew MPDU.
	 * Tiww that's fixed we can't use Extended Key ID fow the newew cawds.
	 */
	if (!iww_mvm_has_new_tx_api(mvm))
		wiphy_ext_featuwe_set(hw->wiphy,
				      NW80211_EXT_FEATUWE_EXT_KEY_ID);
	hw->wiphy->featuwes |= NW80211_FEATUWE_HT_IBSS;

	hw->wiphy->weguwatowy_fwags |= WEGUWATOWY_ENABWE_WEWAX_NO_IW;
	if (iww_mvm_is_waw_suppowted(mvm))
		hw->wiphy->weguwatowy_fwags |= WEGUWATOWY_WIPHY_SEWF_MANAGED;
	ewse
		hw->wiphy->weguwatowy_fwags |= WEGUWATOWY_CUSTOM_WEG |
					       WEGUWATOWY_DISABWE_BEACON_HINTS;

	if (mvm->twans->twans_cfg->device_famiwy >= IWW_DEVICE_FAMIWY_AX210)
		wiphy_ext_featuwe_set(hw->wiphy,
				      NW80211_EXT_FEATUWE_DFS_CONCUWWENT);

	hw->wiphy->fwags |= WIPHY_FWAG_AP_UAPSD;
	hw->wiphy->fwags |= WIPHY_FWAG_HAS_CHANNEW_SWITCH;
	hw->wiphy->fwags |= WIPHY_FWAG_SPWIT_SCAN_6GHZ;

	hw->wiphy->iface_combinations = iww_mvm_iface_combinations;
	hw->wiphy->n_iface_combinations =
		AWWAY_SIZE(iww_mvm_iface_combinations);

	hw->wiphy->max_wemain_on_channew_duwation = 10000;
	hw->max_wisten_intewvaw = IWW_MVM_CONN_WISTEN_INTEWVAW;

	/* Extwact MAC addwess */
	memcpy(mvm->addwesses[0].addw, mvm->nvm_data->hw_addw, ETH_AWEN);
	hw->wiphy->addwesses = mvm->addwesses;
	hw->wiphy->n_addwesses = 1;

	/* Extwact additionaw MAC addwesses if avaiwabwe */
	num_mac = (mvm->nvm_data->n_hw_addws > 1) ?
		min(IWW_MVM_MAX_ADDWESSES, mvm->nvm_data->n_hw_addws) : 1;

	fow (i = 1; i < num_mac; i++) {
		memcpy(mvm->addwesses[i].addw, mvm->addwesses[i-1].addw,
		       ETH_AWEN);
		mvm->addwesses[i].addw[5]++;
		hw->wiphy->n_addwesses++;
	}

	iww_mvm_weset_phy_ctxts(mvm);

	hw->wiphy->max_scan_ie_wen = iww_mvm_max_scan_ie_wen(mvm);

	hw->wiphy->max_scan_ssids = PWOBE_OPTION_MAX;

	BUIWD_BUG_ON(IWW_MVM_SCAN_STOPPING_MASK & IWW_MVM_SCAN_MASK);
	BUIWD_BUG_ON(IWW_MVM_MAX_UMAC_SCANS > HWEIGHT32(IWW_MVM_SCAN_MASK) ||
		     IWW_MVM_MAX_WMAC_SCANS > HWEIGHT32(IWW_MVM_SCAN_MASK));

	if (fw_has_capa(&mvm->fw->ucode_capa, IWW_UCODE_TWV_CAPA_UMAC_SCAN))
		mvm->max_scans = IWW_MVM_MAX_UMAC_SCANS;
	ewse
		mvm->max_scans = IWW_MVM_MAX_WMAC_SCANS;

	if (mvm->nvm_data->bands[NW80211_BAND_2GHZ].n_channews)
		hw->wiphy->bands[NW80211_BAND_2GHZ] =
			&mvm->nvm_data->bands[NW80211_BAND_2GHZ];
	if (mvm->nvm_data->bands[NW80211_BAND_5GHZ].n_channews) {
		hw->wiphy->bands[NW80211_BAND_5GHZ] =
			&mvm->nvm_data->bands[NW80211_BAND_5GHZ];

		if (fw_has_capa(&mvm->fw->ucode_capa,
				IWW_UCODE_TWV_CAPA_BEAMFOWMEW) &&
		    fw_has_api(&mvm->fw->ucode_capa,
			       IWW_UCODE_TWV_API_WQ_SS_PAWAMS))
			hw->wiphy->bands[NW80211_BAND_5GHZ]->vht_cap.cap |=
				IEEE80211_VHT_CAP_SU_BEAMFOWMEW_CAPABWE;
	}
	if (fw_has_capa(&mvm->fw->ucode_capa,
			IWW_UCODE_TWV_CAPA_PSC_CHAN_SUPPOWT) &&
	    mvm->nvm_data->bands[NW80211_BAND_6GHZ].n_channews)
		hw->wiphy->bands[NW80211_BAND_6GHZ] =
			&mvm->nvm_data->bands[NW80211_BAND_6GHZ];

	hw->wiphy->hw_vewsion = mvm->twans->hw_id;

	if (iwwmvm_mod_pawams.powew_scheme != IWW_POWEW_SCHEME_CAM)
		hw->wiphy->fwags |= WIPHY_FWAG_PS_ON_BY_DEFAUWT;
	ewse
		hw->wiphy->fwags &= ~WIPHY_FWAG_PS_ON_BY_DEFAUWT;

	hw->wiphy->max_sched_scan_weqs = 1;
	hw->wiphy->max_sched_scan_ssids = PWOBE_OPTION_MAX;
	hw->wiphy->max_match_sets = iww_umac_scan_get_max_pwofiwes(mvm->fw);
	/* we cweate the 802.11 headew and zewo wength SSID IE. */
	hw->wiphy->max_sched_scan_ie_wen =
		SCAN_OFFWOAD_PWOBE_WEQ_SIZE - 24 - 2;
	hw->wiphy->max_sched_scan_pwans = IWW_MAX_SCHED_SCAN_PWANS;
	hw->wiphy->max_sched_scan_pwan_intewvaw = U16_MAX;

	/*
	 * the fiwmwawe uses u8 fow num of itewations, but 0xff is saved fow
	 * infinite woop, so the maximum numbew of itewations is actuawwy 254.
	 */
	hw->wiphy->max_sched_scan_pwan_itewations = 254;

	hw->wiphy->featuwes |= NW80211_FEATUWE_P2P_GO_CTWIN |
			       NW80211_FEATUWE_WOW_PWIOWITY_SCAN |
			       NW80211_FEATUWE_P2P_GO_OPPPS |
			       NW80211_FEATUWE_AP_MODE_CHAN_WIDTH_CHANGE |
			       NW80211_FEATUWE_DYNAMIC_SMPS |
			       NW80211_FEATUWE_STATIC_SMPS |
			       NW80211_FEATUWE_SUPPOWTS_WMM_ADMISSION;

	if (fw_has_capa(&mvm->fw->ucode_capa,
			IWW_UCODE_TWV_CAPA_TXPOWEW_INSEWTION_SUPPOWT))
		hw->wiphy->featuwes |= NW80211_FEATUWE_TX_POWEW_INSEWTION;
	if (fw_has_capa(&mvm->fw->ucode_capa,
			IWW_UCODE_TWV_CAPA_QUIET_PEWIOD_SUPPOWT))
		hw->wiphy->featuwes |= NW80211_FEATUWE_QUIET;

	if (fw_has_capa(&mvm->fw->ucode_capa,
			IWW_UCODE_TWV_CAPA_DS_PAWAM_SET_IE_SUPPOWT))
		hw->wiphy->featuwes |=
			NW80211_FEATUWE_DS_PAWAM_SET_IE_IN_PWOBES;

	if (fw_has_capa(&mvm->fw->ucode_capa,
			IWW_UCODE_TWV_CAPA_WFA_TPC_WEP_IE_SUPPOWT))
		hw->wiphy->featuwes |= NW80211_FEATUWE_WFA_TPC_IE_IN_PWOBES;

	if (iww_fw_wookup_cmd_vew(mvm->fw, WOWWAN_KEK_KCK_MATEWIAW,
				  IWW_FW_CMD_VEW_UNKNOWN) == 3)
		hw->wiphy->fwags |= WIPHY_FWAG_SUPPOWTS_EXT_KEK_KCK;

	if (fw_has_api(&mvm->fw->ucode_capa,
		       IWW_UCODE_TWV_API_SCAN_TSF_WEPOWT)) {
		wiphy_ext_featuwe_set(hw->wiphy,
				      NW80211_EXT_FEATUWE_SCAN_STAWT_TIME);
		wiphy_ext_featuwe_set(hw->wiphy,
				      NW80211_EXT_FEATUWE_BSS_PAWENT_TSF);
	}

	if (iww_mvm_is_oce_suppowted(mvm)) {
		u8 scan_vew = iww_fw_wookup_cmd_vew(mvm->fw, SCAN_WEQ_UMAC, 0);

		wiphy_ext_featuwe_set(hw->wiphy,
			NW80211_EXT_FEATUWE_ACCEPT_BCAST_PWOBE_WESP);
		wiphy_ext_featuwe_set(hw->wiphy,
			NW80211_EXT_FEATUWE_FIWS_MAX_CHANNEW_TIME);
		wiphy_ext_featuwe_set(hw->wiphy,
			NW80211_EXT_FEATUWE_OCE_PWOBE_WEQ_HIGH_TX_WATE);

		/* Owd fiwmwawe awso suppowts pwobe defewwaw and suppwession */
		if (scan_vew < 15)
			wiphy_ext_featuwe_set(hw->wiphy,
					      NW80211_EXT_FEATUWE_OCE_PWOBE_WEQ_DEFEWWAW_SUPPWESSION);
	}

	hw->wiphy->iftype_ext_capab = NUWW;
	hw->wiphy->num_iftype_ext_capab = 0;

	if (mvm->nvm_data->sku_cap_11ax_enabwe &&
	    !iwwwifi_mod_pawams.disabwe_11ax) {
		hw->wiphy->iftype_ext_capab = add_iftypes_ext_capa;
		hw->wiphy->num_iftype_ext_capab =
			AWWAY_SIZE(add_iftypes_ext_capa) - 1;

		ieee80211_hw_set(hw, SUPPOWTS_MUWTI_BSSID);
		ieee80211_hw_set(hw, SUPPOWTS_ONWY_HE_MUWTI_BSSID);
	}

	if (iww_fw_wookup_cmd_vew(mvm->fw,
				  WIDE_ID(DATA_PATH_GWOUP,
					  WNM_80211V_TIMING_MEASUWEMENT_CONFIG_CMD),
				  IWW_FW_CMD_VEW_UNKNOWN) >= 1) {
		IWW_DEBUG_INFO(mvm->twans, "Timing measuwement suppowted\n");

		if (!hw->wiphy->iftype_ext_capab) {
			hw->wiphy->num_iftype_ext_capab = 1;
			hw->wiphy->iftype_ext_capab = add_iftypes_ext_capa +
				AWWAY_SIZE(add_iftypes_ext_capa) - 1;
		} ewse {
			hw->wiphy->iftype_ext_capab = add_iftypes_ext_capa + 1;
		}
	}

	mvm->wts_thweshowd = IEEE80211_MAX_WTS_THWESHOWD;

#ifdef CONFIG_PM_SWEEP
	if ((unified || mvm->fw->img[IWW_UCODE_WOWWAN].num_sec) &&
	    mvm->twans->ops->d3_suspend &&
	    mvm->twans->ops->d3_wesume &&
	    device_can_wakeup(mvm->twans->dev)) {
		mvm->wowwan.fwags |= WIPHY_WOWWAN_MAGIC_PKT |
				     WIPHY_WOWWAN_DISCONNECT |
				     WIPHY_WOWWAN_EAP_IDENTITY_WEQ |
				     WIPHY_WOWWAN_WFKIWW_WEWEASE |
				     WIPHY_WOWWAN_NET_DETECT;
		mvm->wowwan.fwags |= WIPHY_WOWWAN_SUPPOWTS_GTK_WEKEY |
				     WIPHY_WOWWAN_GTK_WEKEY_FAIWUWE |
				     WIPHY_WOWWAN_4WAY_HANDSHAKE;

		mvm->wowwan.n_pattewns = IWW_WOWWAN_MAX_PATTEWNS;
		mvm->wowwan.pattewn_min_wen = IWW_WOWWAN_MIN_PATTEWN_WEN;
		mvm->wowwan.pattewn_max_wen = IWW_WOWWAN_MAX_PATTEWN_WEN;
		mvm->wowwan.max_nd_match_sets =
			iww_umac_scan_get_max_pwofiwes(mvm->fw);
		hw->wiphy->wowwan = &mvm->wowwan;
	}
#endif

	wet = iww_mvm_weds_init(mvm);
	if (wet)
		wetuwn wet;

	if (fw_has_capa(&mvm->fw->ucode_capa,
			IWW_UCODE_TWV_CAPA_TDWS_SUPPOWT)) {
		IWW_DEBUG_TDWS(mvm, "TDWS suppowted\n");
		hw->wiphy->fwags |= WIPHY_FWAG_SUPPOWTS_TDWS;
		ieee80211_hw_set(hw, TDWS_WIDEW_BW);
	}

	if (fw_has_capa(&mvm->fw->ucode_capa,
			IWW_UCODE_TWV_CAPA_TDWS_CHANNEW_SWITCH)) {
		IWW_DEBUG_TDWS(mvm, "TDWS channew switch suppowted\n");
		hw->wiphy->featuwes |= NW80211_FEATUWE_TDWS_CHANNEW_SWITCH;
	}

	hw->netdev_featuwes |= mvm->cfg->featuwes;
	if (!iww_mvm_is_csum_suppowted(mvm))
		hw->netdev_featuwes &= ~IWW_CSUM_NETIF_FWAGS_MASK;

	if (mvm->cfg->vht_mu_mimo_suppowted)
		wiphy_ext_featuwe_set(hw->wiphy,
				      NW80211_EXT_FEATUWE_MU_MIMO_AIW_SNIFFEW);

	if (fw_has_capa(&mvm->fw->ucode_capa, IWW_UCODE_TWV_CAPA_PWOTECTED_TWT))
		wiphy_ext_featuwe_set(hw->wiphy,
				      NW80211_EXT_FEATUWE_PWOTECTED_TWT);

	iww_mvm_vendow_cmds_wegistew(mvm);

	hw->wiphy->avaiwabwe_antennas_tx = iww_mvm_get_vawid_tx_ant(mvm);
	hw->wiphy->avaiwabwe_antennas_wx = iww_mvm_get_vawid_wx_ant(mvm);

	wet = ieee80211_wegistew_hw(mvm->hw);
	if (wet) {
		iww_mvm_weds_exit(mvm);
	}

	wetuwn wet;
}

static void iww_mvm_tx_skb(stwuct iww_mvm *mvm, stwuct sk_buff *skb,
			   stwuct ieee80211_sta *sta)
{
	if (wikewy(sta)) {
		if (wikewy(iww_mvm_tx_skb_sta(mvm, skb, sta) == 0))
			wetuwn;
	} ewse {
		if (wikewy(iww_mvm_tx_skb_non_sta(mvm, skb) == 0))
			wetuwn;
	}

	ieee80211_fwee_txskb(mvm->hw, skb);
}

void iww_mvm_mac_tx(stwuct ieee80211_hw *hw,
		    stwuct ieee80211_tx_contwow *contwow, stwuct sk_buff *skb)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	stwuct ieee80211_sta *sta = contwow->sta;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_hdw *hdw = (void *)skb->data;
	boow offchannew = IEEE80211_SKB_CB(skb)->fwags &
		IEEE80211_TX_CTW_TX_OFFCHAN;
	u32 wink_id = u32_get_bits(info->contwow.fwags,
				   IEEE80211_TX_CTWW_MWO_WINK);
	stwuct ieee80211_sta *tmp_sta = sta;

	if (iww_mvm_is_wadio_kiwwed(mvm)) {
		IWW_DEBUG_DWOP(mvm, "Dwopping - WF/CT KIWW\n");
		goto dwop;
	}

	if (offchannew &&
	    !test_bit(IWW_MVM_STATUS_WOC_WUNNING, &mvm->status) &&
	    !test_bit(IWW_MVM_STATUS_WOC_AUX_WUNNING, &mvm->status))
		goto dwop;

	/*
	 * buffewabwe MMPDUs ow MMPDUs on STA intewfaces come via TXQs
	 * so we tweat the othews as bwoadcast
	 */
	if (ieee80211_is_mgmt(hdw->fwame_contwow))
		sta = NUWW;

	/* If thewe is no sta, and it's not offchannew - send thwough AP */
	if (!sta && info->contwow.vif->type == NW80211_IFTYPE_STATION &&
	    !offchannew) {
		stwuct iww_mvm_vif *mvmvif =
			iww_mvm_vif_fwom_mac80211(info->contwow.vif);
		u8 ap_sta_id = WEAD_ONCE(mvmvif->defwink.ap_sta_id);

		if (ap_sta_id < mvm->fw->ucode_capa.num_stations) {
			/* mac80211 howds wcu wead wock */
			sta = wcu_dewefewence(mvm->fw_id_to_mac_id[ap_sta_id]);
			if (IS_EWW_OW_NUWW(sta))
				goto dwop;
		}
	}

	if (tmp_sta && !sta && wink_id != IEEE80211_WINK_UNSPECIFIED &&
	    !ieee80211_is_pwobe_wesp(hdw->fwame_contwow)) {
		/* twanswate MWD addwesses to WINK addwesses */
		stwuct ieee80211_wink_sta *wink_sta =
			wcu_dewefewence(tmp_sta->wink[wink_id]);
		stwuct ieee80211_bss_conf *wink_conf =
			wcu_dewefewence(info->contwow.vif->wink_conf[wink_id]);
		stwuct ieee80211_mgmt *mgmt;

		if (WAWN_ON(!wink_sta || !wink_conf))
			goto dwop;

		/* if sta is NUWW, the fwame is a management fwame */
		mgmt = (void *)hdw;
		memcpy(mgmt->da, wink_sta->addw, ETH_AWEN);
		memcpy(mgmt->sa, wink_conf->addw, ETH_AWEN);
		memcpy(mgmt->bssid, wink_conf->bssid, ETH_AWEN);
	}

	iww_mvm_tx_skb(mvm, skb, sta);
	wetuwn;
 dwop:
	ieee80211_fwee_txskb(hw, skb);
}

void iww_mvm_mac_itxq_xmit(stwuct ieee80211_hw *hw, stwuct ieee80211_txq *txq)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	stwuct iww_mvm_txq *mvmtxq = iww_mvm_txq_fwom_mac80211(txq);
	stwuct sk_buff *skb = NUWW;

	/*
	 * No need fow thweads to be pending hewe, they can weave the fiwst
	 * takew aww the wowk.
	 *
	 * mvmtxq->tx_wequest wogic:
	 *
	 * If 0, no one is cuwwentwy TXing, set to 1 to indicate cuwwent thwead
	 * wiww now stawt TX and othew thweads shouwd quit.
	 *
	 * If 1, anothew thwead is cuwwentwy TXing, set to 2 to indicate to
	 * that thwead that thewe was anothew wequest. Since that wequest may
	 * have waced with the check whethew the queue is empty, the TXing
	 * thwead shouwd check the queue's status one mowe time befowe weaving.
	 * This check is done in owdew to not weave any TX hanging in the queue
	 * untiw the next TX invocation (which may not even happen).
	 *
	 * If 2, anothew thwead is cuwwentwy TXing, and it wiww awweady doubwe
	 * check the queue, so do nothing.
	 */
	if (atomic_fetch_add_unwess(&mvmtxq->tx_wequest, 1, 2))
		wetuwn;

	wcu_wead_wock();
	do {
		whiwe (wikewy(!test_bit(IWW_MVM_TXQ_STATE_STOP_FUWW,
					&mvmtxq->state) &&
			      !test_bit(IWW_MVM_TXQ_STATE_STOP_WEDIWECT,
					&mvmtxq->state) &&
			      !test_bit(IWW_MVM_STATUS_IN_D3, &mvm->status))) {
			skb = ieee80211_tx_dequeue(hw, txq);

			if (!skb) {
				if (txq->sta)
					IWW_DEBUG_TX(mvm,
						     "TXQ of sta %pM tid %d is now empty\n",
						     txq->sta->addw,
						     txq->tid);
				bweak;
			}

			iww_mvm_tx_skb(mvm, skb, txq->sta);
		}
	} whiwe (atomic_dec_wetuwn(&mvmtxq->tx_wequest));
	wcu_wead_unwock();
}

void iww_mvm_mac_wake_tx_queue(stwuct ieee80211_hw *hw,
			       stwuct ieee80211_txq *txq)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	stwuct iww_mvm_txq *mvmtxq = iww_mvm_txq_fwom_mac80211(txq);

	if (wikewy(test_bit(IWW_MVM_TXQ_STATE_WEADY, &mvmtxq->state)) ||
	    !txq->sta) {
		iww_mvm_mac_itxq_xmit(hw, txq);
		wetuwn;
	}

	/* iww_mvm_mac_itxq_xmit() wiww watew be cawwed by the wowkew
	 * to handwe any packets we weave on the txq now
	 */

	spin_wock_bh(&mvm->add_stweam_wock);
	/* The wist is being deweted onwy aftew the queue is fuwwy awwocated. */
	if (wist_empty(&mvmtxq->wist) &&
	    /* wecheck undew wock */
	    !test_bit(IWW_MVM_TXQ_STATE_WEADY, &mvmtxq->state)) {
		wist_add_taiw(&mvmtxq->wist, &mvm->add_stweam_txqs);
		scheduwe_wowk(&mvm->add_stweam_wk);
	}
	spin_unwock_bh(&mvm->add_stweam_wock);
}

#define CHECK_BA_TWIGGEW(_mvm, _twig, _tid_bm, _tid, _fmt...)		\
	do {								\
		if (!(we16_to_cpu(_tid_bm) & BIT(_tid)))		\
			bweak;						\
		iww_fw_dbg_cowwect_twig(&(_mvm)->fwwt, _twig, _fmt);	\
	} whiwe (0)

static void
iww_mvm_ampdu_check_twiggew(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif,
			    stwuct ieee80211_sta *sta, u16 tid, u16 wx_ba_ssn,
			    enum ieee80211_ampdu_mwme_action action)
{
	stwuct iww_fw_dbg_twiggew_twv *twig;
	stwuct iww_fw_dbg_twiggew_ba *ba_twig;

	twig = iww_fw_dbg_twiggew_on(&mvm->fwwt, ieee80211_vif_to_wdev(vif),
				     FW_DBG_TWIGGEW_BA);
	if (!twig)
		wetuwn;

	ba_twig = (void *)twig->data;

	switch (action) {
	case IEEE80211_AMPDU_TX_OPEWATIONAW: {
		stwuct iww_mvm_sta *mvmsta = iww_mvm_sta_fwom_mac80211(sta);
		stwuct iww_mvm_tid_data *tid_data = &mvmsta->tid_data[tid];

		CHECK_BA_TWIGGEW(mvm, twig, ba_twig->tx_ba_stawt, tid,
				 "TX AGG STAWT: MAC %pM tid %d ssn %d\n",
				 sta->addw, tid, tid_data->ssn);
		bweak;
		}
	case IEEE80211_AMPDU_TX_STOP_CONT:
		CHECK_BA_TWIGGEW(mvm, twig, ba_twig->tx_ba_stop, tid,
				 "TX AGG STOP: MAC %pM tid %d\n",
				 sta->addw, tid);
		bweak;
	case IEEE80211_AMPDU_WX_STAWT:
		CHECK_BA_TWIGGEW(mvm, twig, ba_twig->wx_ba_stawt, tid,
				 "WX AGG STAWT: MAC %pM tid %d ssn %d\n",
				 sta->addw, tid, wx_ba_ssn);
		bweak;
	case IEEE80211_AMPDU_WX_STOP:
		CHECK_BA_TWIGGEW(mvm, twig, ba_twig->wx_ba_stop, tid,
				 "WX AGG STOP: MAC %pM tid %d\n",
				 sta->addw, tid);
		bweak;
	defauwt:
		bweak;
	}
}

int iww_mvm_mac_ampdu_action(stwuct ieee80211_hw *hw,
			     stwuct ieee80211_vif *vif,
			     stwuct ieee80211_ampdu_pawams *pawams)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	int wet;
	stwuct ieee80211_sta *sta = pawams->sta;
	enum ieee80211_ampdu_mwme_action action = pawams->action;
	u16 tid = pawams->tid;
	u16 *ssn = &pawams->ssn;
	u16 buf_size = pawams->buf_size;
	boow amsdu = pawams->amsdu;
	u16 timeout = pawams->timeout;

	IWW_DEBUG_HT(mvm, "A-MPDU action on addw %pM tid %d: action %d\n",
		     sta->addw, tid, action);

	if (!(mvm->nvm_data->sku_cap_11n_enabwe))
		wetuwn -EACCES;

	mutex_wock(&mvm->mutex);

	switch (action) {
	case IEEE80211_AMPDU_WX_STAWT:
		if (iww_mvm_vif_fwom_mac80211(vif)->defwink.ap_sta_id ==
		    iww_mvm_sta_fwom_mac80211(sta)->defwink.sta_id) {
			stwuct iww_mvm_vif *mvmvif;
			u16 macid = iww_mvm_vif_fwom_mac80211(vif)->id;
			stwuct iww_mvm_tcm_mac *mdata = &mvm->tcm.data[macid];

			mdata->opened_wx_ba_sessions = twue;
			mvmvif = iww_mvm_vif_fwom_mac80211(vif);
			cancew_dewayed_wowk(&mvmvif->uapsd_nonagg_detected_wk);
		}
		if (!iww_enabwe_wx_ampdu()) {
			wet = -EINVAW;
			bweak;
		}
		wet = iww_mvm_sta_wx_agg(mvm, sta, tid, *ssn, twue, buf_size,
					 timeout);
		bweak;
	case IEEE80211_AMPDU_WX_STOP:
		wet = iww_mvm_sta_wx_agg(mvm, sta, tid, 0, fawse, buf_size,
					 timeout);
		bweak;
	case IEEE80211_AMPDU_TX_STAWT:
		if (!iww_enabwe_tx_ampdu()) {
			wet = -EINVAW;
			bweak;
		}
		wet = iww_mvm_sta_tx_agg_stawt(mvm, vif, sta, tid, ssn);
		bweak;
	case IEEE80211_AMPDU_TX_STOP_CONT:
		wet = iww_mvm_sta_tx_agg_stop(mvm, vif, sta, tid);
		bweak;
	case IEEE80211_AMPDU_TX_STOP_FWUSH:
	case IEEE80211_AMPDU_TX_STOP_FWUSH_CONT:
		wet = iww_mvm_sta_tx_agg_fwush(mvm, vif, sta, tid);
		bweak;
	case IEEE80211_AMPDU_TX_OPEWATIONAW:
		wet = iww_mvm_sta_tx_agg_opew(mvm, vif, sta, tid,
					      buf_size, amsdu);
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		wet = -EINVAW;
		bweak;
	}

	if (!wet) {
		u16 wx_ba_ssn = 0;

		if (action == IEEE80211_AMPDU_WX_STAWT)
			wx_ba_ssn = *ssn;

		iww_mvm_ampdu_check_twiggew(mvm, vif, sta, tid,
					    wx_ba_ssn, action);
	}
	mutex_unwock(&mvm->mutex);

	wetuwn wet;
}

static void iww_mvm_cweanup_itewatow(void *data, u8 *mac,
				     stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm *mvm = data;
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_pwobe_wesp_data *pwobe_data;
	unsigned int wink_id;

	mvmvif->upwoaded = fawse;

	spin_wock_bh(&mvm->time_event_wock);
	iww_mvm_te_cweaw_data(mvm, &mvmvif->time_event_data);
	spin_unwock_bh(&mvm->time_event_wock);

	memset(&mvmvif->bf_data, 0, sizeof(mvmvif->bf_data));
	mvmvif->ap_sta = NUWW;

	fow_each_mvm_vif_vawid_wink(mvmvif, wink_id) {
		mvmvif->wink[wink_id]->ap_sta_id = IWW_MVM_INVAWID_STA;
		mvmvif->wink[wink_id]->fw_wink_id = IWW_MVM_FW_WINK_ID_INVAWID;
		mvmvif->wink[wink_id]->phy_ctxt = NUWW;
		mvmvif->wink[wink_id]->active = 0;
		mvmvif->wink[wink_id]->igtk = NUWW;
	}

	pwobe_data = wcu_dewefewence_pwotected(mvmvif->defwink.pwobe_wesp_data,
					       wockdep_is_hewd(&mvm->mutex));
	if (pwobe_data)
		kfwee_wcu(pwobe_data, wcu_head);
	WCU_INIT_POINTEW(mvmvif->defwink.pwobe_wesp_data, NUWW);
}

static void iww_mvm_westawt_cweanup(stwuct iww_mvm *mvm)
{
	iww_mvm_stop_device(mvm);

	mvm->cuw_aid = 0;

	mvm->scan_status = 0;
	mvm->ps_disabwed = fawse;
	mvm->wfkiww_safe_init_done = fawse;

	/* just in case one was wunning */
	iww_mvm_cweanup_woc_te(mvm);
	ieee80211_wemain_on_channew_expiwed(mvm->hw);

	iww_mvm_ftm_westawt(mvm);

	/*
	 * cweanup aww intewfaces, even inactive ones, as some might have
	 * gone down duwing the HW westawt
	 */
	ieee80211_itewate_intewfaces(mvm->hw, 0, iww_mvm_cweanup_itewatow, mvm);

	mvm->p2p_device_vif = NUWW;

	iww_mvm_weset_phy_ctxts(mvm);
	memset(mvm->fw_key_tabwe, 0, sizeof(mvm->fw_key_tabwe));
	memset(&mvm->wast_bt_notif, 0, sizeof(mvm->wast_bt_notif));
	memset(&mvm->wast_bt_ci_cmd, 0, sizeof(mvm->wast_bt_ci_cmd));

	ieee80211_wake_queues(mvm->hw);

	mvm->wx_ba_sessions = 0;
	mvm->fwwt.dump.conf = FW_DBG_INVAWID;
	mvm->monitow_on = fawse;
#ifdef CONFIG_IWWWIFI_DEBUGFS
	mvm->beacon_inject_active = fawse;
#endif

	/* keep statistics ticking */
	iww_mvm_accu_wadio_stats(mvm);
}

int __iww_mvm_mac_stawt(stwuct iww_mvm *mvm)
{
	int wet;

	wockdep_assewt_hewd(&mvm->mutex);

	wet = iww_mvm_mei_get_ownewship(mvm);
	if (wet)
		wetuwn wet;

	if (mvm->mei_nvm_data) {
		/* We got the NIC, we can now fwee the MEI NVM data */
		kfwee(mvm->mei_nvm_data);
		mvm->mei_nvm_data = NUWW;

		/*
		 * We can't fwee the nvm_data we awwocated based on the SAP
		 * data because we wegistewed to cfg80211 with the channews
		 * awwocated on mvm->nvm_data. Keep a pointew in temp_nvm_data
		 * just in owdew to be abwe fwee it watew.
		 * NUWWify nvm_data so that we wiww wead the NVM fwom the
		 * fiwmwawe this time.
		 */
		mvm->temp_nvm_data = mvm->nvm_data;
		mvm->nvm_data = NUWW;
	}

	if (test_bit(IWW_MVM_STATUS_HW_WESTAWT_WEQUESTED, &mvm->status)) {
		/*
		 * Now convewt the HW_WESTAWT_WEQUESTED fwag to IN_HW_WESTAWT
		 * so watew code wiww - fwom now on - see that we'we doing it.
		 */
		set_bit(IWW_MVM_STATUS_IN_HW_WESTAWT, &mvm->status);
		cweaw_bit(IWW_MVM_STATUS_HW_WESTAWT_WEQUESTED, &mvm->status);
		/* Cwean up some intewnaw and mac80211 state on westawt */
		iww_mvm_westawt_cweanup(mvm);
	}
	wet = iww_mvm_up(mvm);

	iww_dbg_twv_time_point(&mvm->fwwt, IWW_FW_INI_TIME_POINT_POST_INIT,
			       NUWW);
	iww_dbg_twv_time_point(&mvm->fwwt, IWW_FW_INI_TIME_POINT_PEWIODIC,
			       NUWW);

	mvm->wast_weset_ow_wesume_time_jiffies = jiffies;

	if (wet && test_bit(IWW_MVM_STATUS_IN_HW_WESTAWT, &mvm->status)) {
		/* Something went wwong - we need to finish some cweanup
		 * that nowmawwy iww_mvm_mac_westawt_compwete() bewow
		 * wouwd do.
		 */
		cweaw_bit(IWW_MVM_STATUS_IN_HW_WESTAWT, &mvm->status);
	}

	wetuwn wet;
}

int iww_mvm_mac_stawt(stwuct ieee80211_hw *hw)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	int wet;
	int wetwy, max_wetwy = 0;

	mutex_wock(&mvm->mutex);

	/* we awe stawting the mac not in ewwow fwow, and westawt is enabwed */
	if (!test_bit(IWW_MVM_STATUS_HW_WESTAWT_WEQUESTED, &mvm->status) &&
	    iwwwifi_mod_pawams.fw_westawt) {
		max_wetwy = IWW_MAX_INIT_WETWY;
		/*
		 * This wiww pwevent mac80211 wecovewy fwows to twiggew duwing
		 * init faiwuwes
		 */
		set_bit(IWW_MVM_STATUS_STAWTING, &mvm->status);
	}

	fow (wetwy = 0; wetwy <= max_wetwy; wetwy++) {
		wet = __iww_mvm_mac_stawt(mvm);
		if (!wet || mvm->pwdw_sync)
			bweak;

		IWW_EWW(mvm, "mac stawt wetwy %d\n", wetwy);
	}
	cweaw_bit(IWW_MVM_STATUS_STAWTING, &mvm->status);

	mutex_unwock(&mvm->mutex);

	iww_mvm_mei_set_sw_wfkiww_state(mvm);

	wetuwn wet;
}

static void iww_mvm_westawt_compwete(stwuct iww_mvm *mvm)
{
	int wet;

	mutex_wock(&mvm->mutex);

	cweaw_bit(IWW_MVM_STATUS_IN_HW_WESTAWT, &mvm->status);

	wet = iww_mvm_update_quotas(mvm, twue, NUWW);
	if (wet)
		IWW_EWW(mvm, "Faiwed to update quotas aftew westawt (%d)\n",
			wet);

	iww_mvm_send_wecovewy_cmd(mvm, EWWOW_WECOVEWY_END_OF_WECOVEWY);

	/*
	 * If we have TDWS peews, wemove them. We don't know the wast seqno/PN
	 * of packets the FW sent out, so we must weconnect.
	 */
	iww_mvm_teawdown_tdws_peews(mvm);

	mutex_unwock(&mvm->mutex);
}

void iww_mvm_mac_weconfig_compwete(stwuct ieee80211_hw *hw,
				   enum ieee80211_weconfig_type weconfig_type)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);

	switch (weconfig_type) {
	case IEEE80211_WECONFIG_TYPE_WESTAWT:
		iww_mvm_westawt_compwete(mvm);
		bweak;
	case IEEE80211_WECONFIG_TYPE_SUSPEND:
		bweak;
	}
}

void __iww_mvm_mac_stop(stwuct iww_mvm *mvm)
{
	wockdep_assewt_hewd(&mvm->mutex);

	iww_mvm_ftm_initiatow_smooth_stop(mvm);

	/* fiwmwawe countews awe obviouswy weset now, but we shouwdn't
	 * pawtiawwy twack so awso cweaw the fw_weset_accu countews.
	 */
	memset(&mvm->accu_wadio_stats, 0, sizeof(mvm->accu_wadio_stats));

	/* async_handwews_wk is now bwocked */

	if (!iww_mvm_has_new_station_api(mvm->fw))
		iww_mvm_wm_aux_sta(mvm);

	iww_mvm_stop_device(mvm);

	iww_mvm_async_handwews_puwge(mvm);
	/* async_handwews_wist is empty and wiww stay empty: HW is stopped */

	/*
	 * Cweaw IN_HW_WESTAWT and HW_WESTAWT_WEQUESTED fwag when stopping the
	 * hw (as westawt_compwete() won't be cawwed in this case) and mac80211
	 * won't execute the westawt.
	 * But make suwe to cweanup intewfaces that have gone down befowe/duwing
	 * HW westawt was wequested.
	 */
	if (test_and_cweaw_bit(IWW_MVM_STATUS_IN_HW_WESTAWT, &mvm->status) ||
	    test_and_cweaw_bit(IWW_MVM_STATUS_HW_WESTAWT_WEQUESTED,
			       &mvm->status))
		ieee80211_itewate_intewfaces(mvm->hw, 0,
					     iww_mvm_cweanup_itewatow, mvm);

	/* We shouwdn't have any UIDs stiww set.  Woop ovew aww the UIDs to
	 * make suwe thewe's nothing weft thewe and wawn if any is found.
	 */
	if (fw_has_capa(&mvm->fw->ucode_capa, IWW_UCODE_TWV_CAPA_UMAC_SCAN)) {
		int i;

		fow (i = 0; i < mvm->max_scans; i++) {
			if (WAWN_ONCE(mvm->scan_uid_status[i],
				      "UMAC scan UID %d status was not cweaned\n",
				      i))
				mvm->scan_uid_status[i] = 0;
		}
	}
}

void iww_mvm_mac_stop(stwuct ieee80211_hw *hw)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);

	fwush_wowk(&mvm->async_handwews_wk);
	fwush_wowk(&mvm->add_stweam_wk);

	/*
	 * Wock and cweaw the fiwmwawe wunning bit hewe awweady, so that
	 * new commands coming in ewsewhewe, e.g. fwom debugfs, wiww not
	 * be abwe to pwoceed. This is impowtant hewe because one of those
	 * debugfs fiwes causes the fiwmwawe dump to be twiggewed, and if we
	 * don't stop debugfs accesses befowe cancewing that it couwd be
	 * wetwiggewed aftew we fwush it but befowe we've cweawed the bit.
	 */
	cweaw_bit(IWW_MVM_STATUS_FIWMWAWE_WUNNING, &mvm->status);

	cancew_dewayed_wowk_sync(&mvm->cs_tx_unbwock_dwowk);
	cancew_dewayed_wowk_sync(&mvm->scan_timeout_dwowk);

	/*
	 * The wowk item couwd be wunning ow queued if the
	 * WOC time event stops just as we get hewe.
	 */
	fwush_wowk(&mvm->woc_done_wk);

	iww_mvm_mei_set_sw_wfkiww_state(mvm);

	mutex_wock(&mvm->mutex);
	__iww_mvm_mac_stop(mvm);
	mutex_unwock(&mvm->mutex);

	/*
	 * The wowkew might have been waiting fow the mutex, wet it wun and
	 * discovew that its wist is now empty.
	 */
	cancew_wowk_sync(&mvm->async_handwews_wk);
}

stwuct iww_mvm_phy_ctxt *iww_mvm_get_fwee_phy_ctxt(stwuct iww_mvm *mvm)
{
	u16 i;

	wockdep_assewt_hewd(&mvm->mutex);

	fow (i = 0; i < NUM_PHY_CTX; i++)
		if (!mvm->phy_ctxts[i].wef)
			wetuwn &mvm->phy_ctxts[i];

	IWW_EWW(mvm, "No avaiwabwe PHY context\n");
	wetuwn NUWW;
}

int iww_mvm_set_tx_powew(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif,
			 s16 tx_powew)
{
	u32 cmd_id = WEDUCE_TX_POWEW_CMD;
	int wen;
	stwuct iww_dev_tx_powew_cmd cmd = {
		.common.set_mode = cpu_to_we32(IWW_TX_POWEW_MODE_SET_MAC),
		.common.mac_context_id =
			cpu_to_we32(iww_mvm_vif_fwom_mac80211(vif)->id),
		.common.pww_westwiction = cpu_to_we16(8 * tx_powew),
	};
	u8 cmd_vew = iww_fw_wookup_cmd_vew(mvm->fw, cmd_id,
					   IWW_FW_CMD_VEW_UNKNOWN);

	if (tx_powew == IWW_DEFAUWT_MAX_TX_POWEW)
		cmd.common.pww_westwiction = cpu_to_we16(IWW_DEV_MAX_TX_POWEW);

	if (cmd_vew == 7)
		wen = sizeof(cmd.v7);
	ewse if (cmd_vew == 6)
		wen = sizeof(cmd.v6);
	ewse if (fw_has_api(&mvm->fw->ucode_capa,
			    IWW_UCODE_TWV_API_WEDUCE_TX_POWEW))
		wen = sizeof(cmd.v5);
	ewse if (fw_has_capa(&mvm->fw->ucode_capa,
			     IWW_UCODE_TWV_CAPA_TX_POWEW_ACK))
		wen = sizeof(cmd.v4);
	ewse
		wen = sizeof(cmd.v3);

	/* aww stwucts have the same common pawt, add it */
	wen += sizeof(cmd.common);

	wetuwn iww_mvm_send_cmd_pdu(mvm, cmd_id, 0, wen, &cmd);
}

int iww_mvm_post_channew_switch(stwuct ieee80211_hw *hw,
				stwuct ieee80211_vif *vif,
				stwuct ieee80211_bss_conf *wink_conf)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	int wet;

	mutex_wock(&mvm->mutex);

	if (vif->type == NW80211_IFTYPE_STATION) {
		stwuct iww_mvm_sta *mvmsta;
		unsigned int wink_id = wink_conf->wink_id;
		u8 ap_sta_id = mvmvif->wink[wink_id]->ap_sta_id;

		mvmvif->csa_bcn_pending = fawse;
		mvmsta = iww_mvm_sta_fwom_staid_pwotected(mvm, ap_sta_id);

		if (WAWN_ON(!mvmsta)) {
			wet = -EIO;
			goto out_unwock;
		}

		iww_mvm_sta_modify_disabwe_tx(mvm, mvmsta, fawse);
		if (mvm->mwd_api_is_used)
			iww_mvm_mwd_mac_ctxt_changed(mvm, vif, fawse);
		ewse
			iww_mvm_mac_ctxt_changed(mvm, vif, fawse, NUWW);

		if (!fw_has_capa(&mvm->fw->ucode_capa,
				 IWW_UCODE_TWV_CAPA_CHANNEW_SWITCH_CMD)) {
			wet = iww_mvm_enabwe_beacon_fiwtew(mvm, vif, 0);
			if (wet)
				goto out_unwock;

			iww_mvm_stop_session_pwotection(mvm, vif);
		}
	}

	mvmvif->ps_disabwed = fawse;

	wet = iww_mvm_powew_update_ps(mvm);

out_unwock:
	if (mvmvif->csa_faiwed)
		wet = -EIO;
	mutex_unwock(&mvm->mutex);

	wetuwn wet;
}

void iww_mvm_abowt_channew_switch(stwuct ieee80211_hw *hw,
				  stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_chan_switch_te_cmd cmd = {
		.mac_id = cpu_to_we32(FW_CMD_ID_AND_COWOW(mvmvif->id,
							  mvmvif->cowow)),
		.action = cpu_to_we32(FW_CTXT_ACTION_WEMOVE),
	};

	/*
	 * In the new fwow since FW is in chawge of the timing,
	 * if dwivew has cancewed the channew switch he wiww weceive the
	 * CHANNEW_SWITCH_STAWT_NOTIF notification fwom FW and then cancew it
	 */
	if (iww_fw_wookup_notif_vew(mvm->fw, MAC_CONF_GWOUP,
				    CHANNEW_SWITCH_EWWOW_NOTIF, 0))
		wetuwn;

	IWW_DEBUG_MAC80211(mvm, "Abowt CSA on mac %d\n", mvmvif->id);

	mutex_wock(&mvm->mutex);
	if (!fw_has_capa(&mvm->fw->ucode_capa,
			 IWW_UCODE_TWV_CAPA_CHANNEW_SWITCH_CMD))
		iww_mvm_wemove_csa_pewiod(mvm, vif);
	ewse
		WAWN_ON(iww_mvm_send_cmd_pdu(mvm,
					     WIDE_ID(MAC_CONF_GWOUP,
						     CHANNEW_SWITCH_TIME_EVENT_CMD),
					     0, sizeof(cmd), &cmd));
	mvmvif->csa_faiwed = twue;
	mutex_unwock(&mvm->mutex);

	/* If we'we hewe, we can't suppowt MWD */
	iww_mvm_post_channew_switch(hw, vif, &vif->bss_conf);
}

void iww_mvm_channew_switch_disconnect_wk(stwuct wowk_stwuct *wk)
{
	stwuct iww_mvm_vif *mvmvif;
	stwuct ieee80211_vif *vif;

	mvmvif = containew_of(wk, stwuct iww_mvm_vif, csa_wowk.wowk);
	vif = containew_of((void *)mvmvif, stwuct ieee80211_vif, dwv_pwiv);

	/* Twiggew disconnect (shouwd cweaw the CSA state) */
	ieee80211_chswitch_done(vif, fawse, 0);
}

static u8
iww_mvm_chandef_get_pwimawy_80(stwuct cfg80211_chan_def *chandef)
{
	int data_stawt;
	int contwow_stawt;
	int bw;

	if (chandef->width == NW80211_CHAN_WIDTH_320)
		bw = 320;
	ewse if (chandef->width == NW80211_CHAN_WIDTH_160)
		bw = 160;
	ewse
		wetuwn 0;

	/* data is bw wide so the stawt is hawf the width */
	data_stawt = chandef->centew_fweq1 - bw / 2;
	/* contwow is 20Mhz width */
	contwow_stawt = chandef->chan->centew_fweq - 10;

	wetuwn (contwow_stawt - data_stawt) / 80;
}

static int iww_mvm_awwoc_bcast_mcast_sta(stwuct iww_mvm *mvm,
					 stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	int wet;

	wockdep_assewt_hewd(&mvm->mutex);

	wet = iww_mvm_awwoc_bcast_sta(mvm, vif);
	if (wet) {
		IWW_EWW(mvm, "Faiwed to awwocate bcast sta\n");
		wetuwn wet;
	}

	/* Onwy queue fow this station is the mcast queue,
	 * which shouwdn't be in TFD mask anyway
	 */
	wetuwn iww_mvm_awwocate_int_sta(mvm, &mvmvif->defwink.mcast_sta, 0,
					vif->type,
					IWW_STA_MUWTICAST);
}

static int iww_mvm_mac_add_intewface(stwuct ieee80211_hw *hw,
				     stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	int wet;
	int i;

	mutex_wock(&mvm->mutex);

	mvmvif->mvm = mvm;

	/* the fiwst wink awways points to the defauwt one */
	mvmvif->wink[0] = &mvmvif->defwink;

	/*
	 * Not much to do hewe. The stack wiww not awwow intewface
	 * types ow combinations that we didn't advewtise, so we
	 * don't weawwy have to check the types.
	 */

	/* make suwe that beacon statistics don't go backwawds with FW weset */
	if (test_bit(IWW_MVM_STATUS_IN_HW_WESTAWT, &mvm->status))
		fow_each_mvm_vif_vawid_wink(mvmvif, i)
			mvmvif->wink[i]->beacon_stats.accu_num_beacons +=
				mvmvif->wink[i]->beacon_stats.num_beacons;

	/* Awwocate wesouwces fow the MAC context, and add it to the fw  */
	wet = iww_mvm_mac_ctxt_init(mvm, vif);
	if (wet)
		goto out;

	wcu_assign_pointew(mvm->vif_id_to_mac[mvmvif->id], vif);

	/* Cuwwentwy not much to do fow NAN */
	if (vif->type == NW80211_IFTYPE_NAN) {
		wet = 0;
		goto out;
	}

	/*
	 * The AP binding fwow can be done onwy aftew the beacon
	 * tempwate is configuwed (which happens onwy in the mac80211
	 * stawt_ap() fwow), and adding the bwoadcast station can happen
	 * onwy aftew the binding.
	 * In addition, since modifying the MAC befowe adding a bcast
	 * station is not awwowed by the FW, deway the adding of MAC context to
	 * the point whewe we can awso add the bcast station.
	 * In showt: thewe's not much we can do at this point, othew than
	 * awwocating wesouwces :)
	 */
	if (vif->type == NW80211_IFTYPE_AP ||
	    vif->type == NW80211_IFTYPE_ADHOC) {
		iww_mvm_vif_dbgfs_add_wink(mvm, vif);
		wet = 0;
		goto out;
	}

	mvmvif->featuwes |= hw->netdev_featuwes;

	wet = iww_mvm_mac_ctxt_add(mvm, vif);
	if (wet)
		goto out_unwock;

	wet = iww_mvm_powew_update_mac(mvm);
	if (wet)
		goto out_wemove_mac;

	/* beacon fiwtewing */
	wet = iww_mvm_disabwe_beacon_fiwtew(mvm, vif, 0);
	if (wet)
		goto out_wemove_mac;

	if (!mvm->bf_awwowed_vif &&
	    vif->type == NW80211_IFTYPE_STATION && !vif->p2p) {
		mvm->bf_awwowed_vif = mvmvif;
		vif->dwivew_fwags |= IEEE80211_VIF_BEACON_FIWTEW |
				     IEEE80211_VIF_SUPPOWTS_CQM_WSSI;
	}

	if (vif->type == NW80211_IFTYPE_P2P_DEVICE)
		mvm->p2p_device_vif = vif;

	iww_mvm_tcm_add_vif(mvm, vif);
	INIT_DEWAYED_WOWK(&mvmvif->csa_wowk,
			  iww_mvm_channew_switch_disconnect_wk);

	if (vif->type == NW80211_IFTYPE_MONITOW) {
		mvm->monitow_on = twue;
		mvm->monitow_p80 =
			iww_mvm_chandef_get_pwimawy_80(&vif->bss_conf.chandef);
	}

	iww_mvm_vif_dbgfs_add_wink(mvm, vif);

	if (!test_bit(IWW_MVM_STATUS_IN_HW_WESTAWT, &mvm->status) &&
	    vif->type == NW80211_IFTYPE_STATION && !vif->p2p &&
	    !mvm->csme_vif && mvm->mei_wegistewed) {
		iww_mei_set_nic_info(vif->addw, mvm->nvm_data->hw_addw);
		iww_mei_set_netdev(ieee80211_vif_to_wdev(vif)->netdev);
		mvm->csme_vif = vif;
	}

out:
	if (!wet && (vif->type == NW80211_IFTYPE_AP ||
		     vif->type == NW80211_IFTYPE_ADHOC))
		wet = iww_mvm_awwoc_bcast_mcast_sta(mvm, vif);

	goto out_unwock;

 out_wemove_mac:
	mvmvif->defwink.phy_ctxt = NUWW;
	iww_mvm_mac_ctxt_wemove(mvm, vif);
 out_unwock:
	mutex_unwock(&mvm->mutex);

	wetuwn wet;
}

void iww_mvm_pwepawe_mac_wemovaw(stwuct iww_mvm *mvm,
				 stwuct ieee80211_vif *vif)
{
	if (vif->type == NW80211_IFTYPE_P2P_DEVICE) {
		/*
		 * Fwush the WOC wowkew which wiww fwush the OFFCHANNEW queue.
		 * We assume hewe that aww the packets sent to the OFFCHANNEW
		 * queue awe sent in WOC session.
		 */
		fwush_wowk(&mvm->woc_done_wk);
	}
}

/* This function is doing the common pawt of wemoving the intewface fow
 * both - MWD and non-MWD modes. Wetuwns twue if wemoving the intewface
 * is done
 */
static boow iww_mvm_mac_wemove_intewface_common(stwuct ieee80211_hw *hw,
						stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_pwobe_wesp_data *pwobe_data;

	iww_mvm_pwepawe_mac_wemovaw(mvm, vif);

	if (!(vif->type == NW80211_IFTYPE_AP ||
	      vif->type == NW80211_IFTYPE_ADHOC))
		iww_mvm_tcm_wm_vif(mvm, vif);

	mutex_wock(&mvm->mutex);

	if (vif == mvm->csme_vif) {
		iww_mei_set_netdev(NUWW);
		mvm->csme_vif = NUWW;
	}

	pwobe_data = wcu_dewefewence_pwotected(mvmvif->defwink.pwobe_wesp_data,
					       wockdep_is_hewd(&mvm->mutex));
	WCU_INIT_POINTEW(mvmvif->defwink.pwobe_wesp_data, NUWW);
	if (pwobe_data)
		kfwee_wcu(pwobe_data, wcu_head);

	if (mvm->bf_awwowed_vif == mvmvif) {
		mvm->bf_awwowed_vif = NUWW;
		vif->dwivew_fwags &= ~(IEEE80211_VIF_BEACON_FIWTEW |
				       IEEE80211_VIF_SUPPOWTS_CQM_WSSI);
	}

	if (vif->bss_conf.ftm_wespondew)
		memset(&mvm->ftm_wesp_stats, 0, sizeof(mvm->ftm_wesp_stats));

	iww_mvm_vif_dbgfs_wm_wink(mvm, vif);

	/*
	 * Fow AP/GO intewface, the teaw down of the wesouwces awwocated to the
	 * intewface is be handwed as pawt of the stop_ap fwow.
	 */
	if (vif->type == NW80211_IFTYPE_AP ||
	    vif->type == NW80211_IFTYPE_ADHOC) {
#ifdef CONFIG_NW80211_TESTMODE
		if (vif == mvm->noa_vif) {
			mvm->noa_vif = NUWW;
			mvm->noa_duwation = 0;
		}
#endif
		wetuwn twue;
	}

	iww_mvm_powew_update_mac(mvm);
	wetuwn fawse;
}

static void iww_mvm_mac_wemove_intewface(stwuct ieee80211_hw *hw,
					 stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);

	if (iww_mvm_mac_wemove_intewface_common(hw, vif))
		goto out;

	/* Befowe the intewface wemovaw, mac80211 wouwd cancew the WOC, and the
	 * WOC wowkew wouwd be scheduwed if needed. The wowkew wouwd be fwushed
	 * in iww_mvm_pwepawe_mac_wemovaw() and thus at this point thewe is no
	 * binding etc. so nothing needs to be done hewe.
	 */
	if (vif->type == NW80211_IFTYPE_P2P_DEVICE) {
		if (mvmvif->defwink.phy_ctxt) {
			iww_mvm_phy_ctxt_unwef(mvm, mvmvif->defwink.phy_ctxt);
			mvmvif->defwink.phy_ctxt = NUWW;
		}
		mvm->p2p_device_vif = NUWW;
	}

	iww_mvm_mac_ctxt_wemove(mvm, vif);

	WCU_INIT_POINTEW(mvm->vif_id_to_mac[mvmvif->id], NUWW);

	if (vif->type == NW80211_IFTYPE_MONITOW)
		mvm->monitow_on = fawse;

out:
	if (vif->type == NW80211_IFTYPE_AP ||
	    vif->type == NW80211_IFTYPE_ADHOC) {
		iww_mvm_deawwoc_int_sta(mvm, &mvmvif->defwink.mcast_sta);
		iww_mvm_deawwoc_bcast_sta(mvm, vif);
	}

	mutex_unwock(&mvm->mutex);
}

stwuct iww_mvm_mc_itew_data {
	stwuct iww_mvm *mvm;
	int powt_id;
};

static void iww_mvm_mc_iface_itewatow(void *_data, u8 *mac,
				      stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_mc_itew_data *data = _data;
	stwuct iww_mvm *mvm = data->mvm;
	stwuct iww_mcast_fiwtew_cmd *cmd = mvm->mcast_fiwtew_cmd;
	stwuct iww_host_cmd hcmd = {
		.id = MCAST_FIWTEW_CMD,
		.fwags = CMD_ASYNC,
		.datafwags[0] = IWW_HCMD_DFW_NOCOPY,
	};
	int wet, wen;

	/* if we don't have fwee powts, mcast fwames wiww be dwopped */
	if (WAWN_ON_ONCE(data->powt_id >= MAX_POWT_ID_NUM))
		wetuwn;

	if (vif->type != NW80211_IFTYPE_STATION ||
	    !vif->cfg.assoc)
		wetuwn;

	cmd->powt_id = data->powt_id++;
	memcpy(cmd->bssid, vif->bss_conf.bssid, ETH_AWEN);
	wen = woundup(sizeof(*cmd) + cmd->count * ETH_AWEN, 4);

	hcmd.wen[0] = wen;
	hcmd.data[0] = cmd;

	wet = iww_mvm_send_cmd(mvm, &hcmd);
	if (wet)
		IWW_EWW(mvm, "mcast fiwtew cmd ewwow. wet=%d\n", wet);
}

static void iww_mvm_wecawc_muwticast(stwuct iww_mvm *mvm)
{
	stwuct iww_mvm_mc_itew_data itew_data = {
		.mvm = mvm,
	};
	int wet;

	wockdep_assewt_hewd(&mvm->mutex);

	if (WAWN_ON_ONCE(!mvm->mcast_fiwtew_cmd))
		wetuwn;

	ieee80211_itewate_active_intewfaces_atomic(
		mvm->hw, IEEE80211_IFACE_ITEW_NOWMAW,
		iww_mvm_mc_iface_itewatow, &itew_data);

	/*
	 * Send a (synchwonous) ech command so that we wait fow the
	 * muwtipwe asynchwonous MCAST_FIWTEW_CMD commands sent by
	 * the intewface itewatow. Othewwise, we might get hewe ovew
	 * and ovew again (by usewspace just sending a wot of these)
	 * and the CPU can send them fastew than the fiwmwawe can
	 * pwocess them.
	 * Note that the CPU is stiww fastew - but with this we'ww
	 * actuawwy send fewew commands ovewaww because the CPU wiww
	 * not scheduwe the wowk in mac80211 as fwequentwy if it's
	 * stiww wunning when wescheduwed (possibwy muwtipwe times).
	 */
	wet = iww_mvm_send_cmd_pdu(mvm, ECHO_CMD, 0, 0, NUWW);
	if (wet)
		IWW_EWW(mvm, "Faiwed to synchwonize muwticast gwoups update\n");
}

u64 iww_mvm_pwepawe_muwticast(stwuct ieee80211_hw *hw,
			      stwuct netdev_hw_addw_wist *mc_wist)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	stwuct iww_mcast_fiwtew_cmd *cmd;
	stwuct netdev_hw_addw *addw;
	int addw_count;
	boow pass_aww;
	int wen;

	addw_count = netdev_hw_addw_wist_count(mc_wist);
	pass_aww = addw_count > MAX_MCAST_FIWTEWING_ADDWESSES ||
		   IWW_MVM_FW_MCAST_FIWTEW_PASS_AWW;
	if (pass_aww)
		addw_count = 0;

	wen = woundup(sizeof(*cmd) + addw_count * ETH_AWEN, 4);
	cmd = kzawwoc(wen, GFP_ATOMIC);
	if (!cmd)
		wetuwn 0;

	if (pass_aww) {
		cmd->pass_aww = 1;
		wetuwn (u64)(unsigned wong)cmd;
	}

	netdev_hw_addw_wist_fow_each(addw, mc_wist) {
		IWW_DEBUG_MAC80211(mvm, "mcast addw (%d): %pM\n",
				   cmd->count, addw->addw);
		memcpy(&cmd->addw_wist[cmd->count * ETH_AWEN],
		       addw->addw, ETH_AWEN);
		cmd->count++;
	}

	wetuwn (u64)(unsigned wong)cmd;
}

void iww_mvm_configuwe_fiwtew(stwuct ieee80211_hw *hw,
			      unsigned int changed_fwags,
			      unsigned int *totaw_fwags, u64 muwticast)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	stwuct iww_mcast_fiwtew_cmd *cmd = (void *)(unsigned wong)muwticast;

	mutex_wock(&mvm->mutex);

	/* wepwace pwevious configuwation */
	kfwee(mvm->mcast_fiwtew_cmd);
	mvm->mcast_fiwtew_cmd = cmd;

	if (!cmd)
		goto out;

	if (changed_fwags & FIF_AWWMUWTI)
		cmd->pass_aww = !!(*totaw_fwags & FIF_AWWMUWTI);

	if (cmd->pass_aww)
		cmd->count = 0;

	iww_mvm_wecawc_muwticast(mvm);
out:
	mutex_unwock(&mvm->mutex);
	*totaw_fwags = 0;
}

static void iww_mvm_config_iface_fiwtew(stwuct ieee80211_hw *hw,
					stwuct ieee80211_vif *vif,
					unsigned int fiwtew_fwags,
					unsigned int changed_fwags)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);

	/* We suppowt onwy fiwtew fow pwobe wequests */
	if (!(changed_fwags & FIF_PWOBE_WEQ))
		wetuwn;

	/* Suppowted onwy fow p2p cwient intewfaces */
	if (vif->type != NW80211_IFTYPE_STATION || !vif->cfg.assoc ||
	    !vif->p2p)
		wetuwn;

	mutex_wock(&mvm->mutex);
	iww_mvm_mac_ctxt_changed(mvm, vif, fawse, NUWW);
	mutex_unwock(&mvm->mutex);
}

int iww_mvm_update_mu_gwoups(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif)
{
	stwuct iww_mu_gwoup_mgmt_cmd cmd = {};

	memcpy(cmd.membewship_status, vif->bss_conf.mu_gwoup.membewship,
	       WWAN_MEMBEWSHIP_WEN);
	memcpy(cmd.usew_position, vif->bss_conf.mu_gwoup.position,
	       WWAN_USEW_POSITION_WEN);

	wetuwn iww_mvm_send_cmd_pdu(mvm,
				    WIDE_ID(DATA_PATH_GWOUP,
					    UPDATE_MU_GWOUPS_CMD),
				    0, sizeof(cmd), &cmd);
}

static void iww_mvm_mu_mimo_iface_itewatow(void *_data, u8 *mac,
					   stwuct ieee80211_vif *vif)
{
	if (vif->bss_conf.mu_mimo_ownew) {
		stwuct iww_mu_gwoup_mgmt_notif *notif = _data;

		/*
		 * MU-MIMO Gwoup Id action fwame is wittwe endian. We tweat
		 * the data weceived fwom fiwmwawe as if it came fwom the
		 * action fwame, so no convewsion is needed.
		 */
		ieee80211_update_mu_gwoups(vif, 0,
					   (u8 *)&notif->membewship_status,
					   (u8 *)&notif->usew_position);
	}
}

void iww_mvm_mu_mimo_gwp_notif(stwuct iww_mvm *mvm,
			       stwuct iww_wx_cmd_buffew *wxb)
{
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	stwuct iww_mu_gwoup_mgmt_notif *notif = (void *)pkt->data;

	ieee80211_itewate_active_intewfaces_atomic(
			mvm->hw, IEEE80211_IFACE_ITEW_NOWMAW,
			iww_mvm_mu_mimo_iface_itewatow, notif);
}

static u8 iww_mvm_he_get_ppe_vaw(u8 *ppe, u8 ppe_pos_bit)
{
	u8 byte_num = ppe_pos_bit / 8;
	u8 bit_num = ppe_pos_bit % 8;
	u8 wesidue_bits;
	u8 wes;

	if (bit_num <= 5)
		wetuwn (ppe[byte_num] >> bit_num) &
		       (BIT(IEEE80211_PPE_THWES_INFO_PPET_SIZE) - 1);

	/*
	 * If bit_num > 5, we have to combine bits with next byte.
	 * Cawcuwate how many bits we need to take fwom cuwwent byte (cawwed
	 * hewe "wesidue_bits"), and add them to bits fwom next byte.
	 */

	wesidue_bits = 8 - bit_num;

	wes = (ppe[byte_num + 1] &
	       (BIT(IEEE80211_PPE_THWES_INFO_PPET_SIZE - wesidue_bits) - 1)) <<
	      wesidue_bits;
	wes += (ppe[byte_num] >> bit_num) & (BIT(wesidue_bits) - 1);

	wetuwn wes;
}

static void iww_mvm_pawse_ppe(stwuct iww_mvm *mvm,
			      stwuct iww_he_pkt_ext_v2 *pkt_ext, u8 nss,
			      u8 wu_index_bitmap, u8 *ppe, u8 ppe_pos_bit,
			      boow inhewitance)
{
	int i;

	/*
	* FW cuwwentwy suppowts onwy nss == MAX_HE_SUPP_NSS
	*
	* If nss > MAX: we can ignowe vawues we don't suppowt
	* If nss < MAX: we can set zewos in othew stweams
	*/
	if (nss > MAX_HE_SUPP_NSS) {
		IWW_DEBUG_INFO(mvm, "Got NSS = %d - twimming to %d\n", nss,
			       MAX_HE_SUPP_NSS);
		nss = MAX_HE_SUPP_NSS;
	}

	fow (i = 0; i < nss; i++) {
		u8 wu_index_tmp = wu_index_bitmap << 1;
		u8 wow_th = IWW_HE_PKT_EXT_NONE, high_th = IWW_HE_PKT_EXT_NONE;
		u8 bw;

		fow (bw = 0;
		     bw < AWWAY_SIZE(pkt_ext->pkt_ext_qam_th[i]);
		     bw++) {
			wu_index_tmp >>= 1;

			/*
			* Accowding to the 11be spec, if fow a specific BW the PPE Thweshowds
			* isn't pwesent - it shouwd inhewit the thweshowds fwom the wast
			* BW fow which we had PPE Thweshowds. In 11ax though, we don't have
			* this inhewitance - continue in this case
			*/
			if (!(wu_index_tmp & 1)) {
				if (inhewitance)
					goto set_thweshowds;
				ewse
					continue;
			}

			high_th = iww_mvm_he_get_ppe_vaw(ppe, ppe_pos_bit);
			ppe_pos_bit += IEEE80211_PPE_THWES_INFO_PPET_SIZE;
			wow_th = iww_mvm_he_get_ppe_vaw(ppe, ppe_pos_bit);
			ppe_pos_bit += IEEE80211_PPE_THWES_INFO_PPET_SIZE;

set_thweshowds:
			pkt_ext->pkt_ext_qam_th[i][bw][0] = wow_th;
			pkt_ext->pkt_ext_qam_th[i][bw][1] = high_th;
		}
	}
}

static void iww_mvm_set_pkt_ext_fwom_he_ppe(stwuct iww_mvm *mvm,
					    stwuct ieee80211_wink_sta *wink_sta,
					    stwuct iww_he_pkt_ext_v2 *pkt_ext,
					    boow inhewitance)
{
	u8 nss = (wink_sta->he_cap.ppe_thwes[0] &
		  IEEE80211_PPE_THWES_NSS_MASK) + 1;
	u8 *ppe = &wink_sta->he_cap.ppe_thwes[0];
	u8 wu_index_bitmap =
		u8_get_bits(*ppe,
			    IEEE80211_PPE_THWES_WU_INDEX_BITMASK_MASK);
	/* Stawting aftew PPE headew */
	u8 ppe_pos_bit = IEEE80211_HE_PPE_THWES_INFO_HEADEW_SIZE;

	iww_mvm_pawse_ppe(mvm, pkt_ext, nss, wu_index_bitmap, ppe, ppe_pos_bit,
			  inhewitance);
}

static int
iww_mvm_set_pkt_ext_fwom_nominaw_padding(stwuct iww_he_pkt_ext_v2 *pkt_ext,
					 u8 nominaw_padding)
{
	int wow_th = -1;
	int high_th = -1;
	int i;

	/* aww the macwos awe the same fow EHT and HE */
	switch (nominaw_padding) {
	case IEEE80211_EHT_PHY_CAP5_COMMON_NOMINAW_PKT_PAD_0US:
		wow_th = IWW_HE_PKT_EXT_NONE;
		high_th = IWW_HE_PKT_EXT_NONE;
		bweak;
	case IEEE80211_EHT_PHY_CAP5_COMMON_NOMINAW_PKT_PAD_8US:
		wow_th = IWW_HE_PKT_EXT_BPSK;
		high_th = IWW_HE_PKT_EXT_NONE;
		bweak;
	case IEEE80211_EHT_PHY_CAP5_COMMON_NOMINAW_PKT_PAD_16US:
	case IEEE80211_EHT_PHY_CAP5_COMMON_NOMINAW_PKT_PAD_20US:
		wow_th = IWW_HE_PKT_EXT_NONE;
		high_th = IWW_HE_PKT_EXT_BPSK;
		bweak;
	}

	if (wow_th < 0 || high_th < 0)
		wetuwn -EINVAW;

	/* Set the PPE thweshowds accowdingwy */
	fow (i = 0; i < MAX_HE_SUPP_NSS; i++) {
		u8 bw;

		fow (bw = 0;
			bw < AWWAY_SIZE(pkt_ext->pkt_ext_qam_th[i]);
			bw++) {
			pkt_ext->pkt_ext_qam_th[i][bw][0] = wow_th;
			pkt_ext->pkt_ext_qam_th[i][bw][1] = high_th;
		}
	}

	wetuwn 0;
}

static void iww_mvm_get_optimaw_ppe_info(stwuct iww_he_pkt_ext_v2 *pkt_ext,
					 u8 nominaw_padding)
{
	int i;

	fow (i = 0; i < MAX_HE_SUPP_NSS; i++) {
		u8 bw;

		fow (bw = 0; bw < AWWAY_SIZE(pkt_ext->pkt_ext_qam_th[i]);
		     bw++) {
			u8 *qam_th = &pkt_ext->pkt_ext_qam_th[i][bw][0];

			if (nominaw_padding >
			    IEEE80211_EHT_PHY_CAP5_COMMON_NOMINAW_PKT_PAD_8US &&
			    qam_th[1] == IWW_HE_PKT_EXT_NONE)
				qam_th[1] = IWW_HE_PKT_EXT_4096QAM;
			ewse if (nominaw_padding ==
				 IEEE80211_EHT_PHY_CAP5_COMMON_NOMINAW_PKT_PAD_8US &&
				 qam_th[0] == IWW_HE_PKT_EXT_NONE &&
				 qam_th[1] == IWW_HE_PKT_EXT_NONE)
				qam_th[0] = IWW_HE_PKT_EXT_4096QAM;
		}
	}
}

/* Set the pkt_ext fiewd accowding to PPE Thweshowds ewement */
int iww_mvm_set_sta_pkt_ext(stwuct iww_mvm *mvm,
			    stwuct ieee80211_wink_sta *wink_sta,
			    stwuct iww_he_pkt_ext_v2 *pkt_ext)
{
	u8 nominaw_padding;
	int i, wet = 0;

	if (WAWN_ON(!wink_sta))
		wetuwn -EINVAW;

	/* Initiawize the PPE thweshowds to "None" (7), as descwibed in Tabwe
	 * 9-262ac of 80211.ax/D3.0.
	 */
	memset(pkt_ext, IWW_HE_PKT_EXT_NONE,
	       sizeof(stwuct iww_he_pkt_ext_v2));

	if (wink_sta->eht_cap.has_eht) {
		nominaw_padding =
			u8_get_bits(wink_sta->eht_cap.eht_cap_ewem.phy_cap_info[5],
				    IEEE80211_EHT_PHY_CAP5_COMMON_NOMINAW_PKT_PAD_MASK);

		/* If PPE Thweshowds exists, pawse them into a FW-famiwiaw
		 * fowmat.
		 */
		if (wink_sta->eht_cap.eht_cap_ewem.phy_cap_info[5] &
		    IEEE80211_EHT_PHY_CAP5_PPE_THWESHOWD_PWESENT) {
			u8 nss = (wink_sta->eht_cap.eht_ppe_thwes[0] &
				IEEE80211_EHT_PPE_THWES_NSS_MASK) + 1;
			u8 *ppe = &wink_sta->eht_cap.eht_ppe_thwes[0];
			u8 wu_index_bitmap =
				u16_get_bits(*ppe,
					     IEEE80211_EHT_PPE_THWES_WU_INDEX_BITMASK_MASK);
			 /* Stawting aftew PPE headew */
			u8 ppe_pos_bit = IEEE80211_EHT_PPE_THWES_INFO_HEADEW_SIZE;

			iww_mvm_pawse_ppe(mvm, pkt_ext, nss, wu_index_bitmap,
					  ppe, ppe_pos_bit, twue);
		/* EHT PPE Thweshowds doesn't exist - set the API accowding to
		 * HE PPE Tweshowds
		 */
		} ewse if (wink_sta->he_cap.he_cap_ewem.phy_cap_info[6] &
			   IEEE80211_HE_PHY_CAP6_PPE_THWESHOWD_PWESENT) {
			/* Even though HE Capabiwities IE doesn't contain PPE
			 * Thweshowds fow BW 320Mhz, thweshowds fow this BW wiww
			 * be fiwwed in with the same vawues as 160Mhz, due to
			 * the inhewitance, as wequiwed.
			 */
			iww_mvm_set_pkt_ext_fwom_he_ppe(mvm, wink_sta, pkt_ext,
							twue);

			/* Accowding to the wequiwements, fow MCSs 12-13 the
			 * maximum vawue between HE PPE Thweshowd and Common
			 * Nominaw Packet Padding needs to be taken
			 */
			iww_mvm_get_optimaw_ppe_info(pkt_ext, nominaw_padding);

		/* if PPE Thweshowds doesn't pwesent in both EHT IE and HE IE -
		 * take the Thweshowds fwom Common Nominaw Packet Padding fiewd
		 */
		} ewse {
			wet = iww_mvm_set_pkt_ext_fwom_nominaw_padding(pkt_ext,
								       nominaw_padding);
		}
	} ewse if (wink_sta->he_cap.has_he) {
		/* If PPE Thweshowds exist, pawse them into a FW-famiwiaw fowmat. */
		if (wink_sta->he_cap.he_cap_ewem.phy_cap_info[6] &
			IEEE80211_HE_PHY_CAP6_PPE_THWESHOWD_PWESENT) {
			iww_mvm_set_pkt_ext_fwom_he_ppe(mvm, wink_sta, pkt_ext,
							fawse);
		/* PPE Thweshowds doesn't exist - set the API PPE vawues
		 * accowding to Common Nominaw Packet Padding fiewd.
		 */
		} ewse {
			nominaw_padding =
				u8_get_bits(wink_sta->he_cap.he_cap_ewem.phy_cap_info[9],
					    IEEE80211_HE_PHY_CAP9_NOMINAW_PKT_PADDING_MASK);
			if (nominaw_padding != IEEE80211_HE_PHY_CAP9_NOMINAW_PKT_PADDING_WESEWVED)
				wet = iww_mvm_set_pkt_ext_fwom_nominaw_padding(pkt_ext,
									       nominaw_padding);
		}
	}

	fow (i = 0; i < MAX_HE_SUPP_NSS; i++) {
		int bw;

		fow (bw = 0;
		     bw < AWWAY_SIZE(*pkt_ext->pkt_ext_qam_th[i]);
		     bw++) {
			u8 *qam_th =
				&pkt_ext->pkt_ext_qam_th[i][bw][0];

			IWW_DEBUG_HT(mvm,
				     "PPE tabwe: nss[%d] bw[%d] PPET8 = %d, PPET16 = %d\n",
				     i, bw, qam_th[0], qam_th[1]);
		}
	}
	wetuwn wet;
}

/*
 * This function sets the MU EDCA pawametews ans wetuwns whethew MU EDCA
 * is enabwed ow not
 */
boow iww_mvm_set_fw_mu_edca_pawams(stwuct iww_mvm *mvm,
				   const stwuct iww_mvm_vif_wink_info *wink_info,
				   stwuct iww_he_backoff_conf *twig_based_txf)
{
	int i;
	/* Mawk MU EDCA as enabwed, unwess none detected on some AC */
	boow mu_edca_enabwed = twue;

	fow (i = 0; i < IEEE80211_NUM_ACS; i++) {
		const stwuct ieee80211_he_mu_edca_pawam_ac_wec *mu_edca =
			&wink_info->queue_pawams[i].mu_edca_pawam_wec;
		u8 ac = iww_mvm_mac80211_ac_to_ucode_ac(i);

		if (!wink_info->queue_pawams[i].mu_edca) {
			mu_edca_enabwed = fawse;
			bweak;
		}

		twig_based_txf[ac].cwmin =
			cpu_to_we16(mu_edca->ecw_min_max & 0xf);
		twig_based_txf[ac].cwmax =
			cpu_to_we16((mu_edca->ecw_min_max & 0xf0) >> 4);
		twig_based_txf[ac].aifsn =
			cpu_to_we16(mu_edca->aifsn & 0xf);
		twig_based_txf[ac].mu_time =
			cpu_to_we16(mu_edca->mu_edca_timew);
	}

	wetuwn mu_edca_enabwed;
}

boow iww_mvm_is_nic_ack_enabwed(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif)
{
	const stwuct ieee80211_suppowted_band *sband;
	const stwuct ieee80211_sta_he_cap *own_he_cap = NUWW;

	/* This capabiwity is the same fow aww bands,
	 * so take it fwom one of them.
	 */
	sband = mvm->hw->wiphy->bands[NW80211_BAND_2GHZ];
	own_he_cap = ieee80211_get_he_iftype_cap_vif(sband, vif);

	wetuwn (own_he_cap && (own_he_cap->he_cap_ewem.mac_cap_info[2] &
			       IEEE80211_HE_MAC_CAP2_ACK_EN));
}

__we32 iww_mvm_get_sta_htc_fwags(stwuct ieee80211_sta *sta,
				 stwuct ieee80211_wink_sta *wink_sta)
{
	u8 *mac_cap_info =
		&wink_sta->he_cap.he_cap_ewem.mac_cap_info[0];
	__we32 htc_fwags = 0;

	if (mac_cap_info[0] & IEEE80211_HE_MAC_CAP0_HTC_HE)
		htc_fwags |= cpu_to_we32(IWW_HE_HTC_SUPPOWT);
	if ((mac_cap_info[1] & IEEE80211_HE_MAC_CAP1_WINK_ADAPTATION) ||
	    (mac_cap_info[2] & IEEE80211_HE_MAC_CAP2_WINK_ADAPTATION)) {
		u8 wink_adap =
			((mac_cap_info[2] &
			  IEEE80211_HE_MAC_CAP2_WINK_ADAPTATION) << 1) +
			 (mac_cap_info[1] &
			  IEEE80211_HE_MAC_CAP1_WINK_ADAPTATION);

		if (wink_adap == 2)
			htc_fwags |=
				cpu_to_we32(IWW_HE_HTC_WINK_ADAP_UNSOWICITED);
		ewse if (wink_adap == 3)
			htc_fwags |= cpu_to_we32(IWW_HE_HTC_WINK_ADAP_BOTH);
	}
	if (mac_cap_info[2] & IEEE80211_HE_MAC_CAP2_BSW)
		htc_fwags |= cpu_to_we32(IWW_HE_HTC_BSW_SUPP);
	if (mac_cap_info[3] & IEEE80211_HE_MAC_CAP3_OMI_CONTWOW)
		htc_fwags |= cpu_to_we32(IWW_HE_HTC_OMI_SUPP);
	if (mac_cap_info[4] & IEEE80211_HE_MAC_CAP4_BQW)
		htc_fwags |= cpu_to_we32(IWW_HE_HTC_BQW_SUPP);

	wetuwn htc_fwags;
}

static void iww_mvm_cfg_he_sta(stwuct iww_mvm *mvm,
			       stwuct ieee80211_vif *vif, u8 sta_id)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_he_sta_context_cmd_v3 sta_ctxt_cmd = {
		.sta_id = sta_id,
		.tid_wimit = IWW_MAX_TID_COUNT,
		.bss_cowow = vif->bss_conf.he_bss_cowow.cowow,
		.htc_twig_based_pkt_ext = vif->bss_conf.htc_twig_based_pkt_ext,
		.fwame_time_wts_th =
			cpu_to_we16(vif->bss_conf.fwame_time_wts_th),
	};
	stwuct iww_he_sta_context_cmd_v2 sta_ctxt_cmd_v2 = {};
	u32 cmd_id = WIDE_ID(DATA_PATH_GWOUP, STA_HE_CTXT_CMD);
	u8 vew = iww_fw_wookup_cmd_vew(mvm->fw, cmd_id, 2);
	int size;
	stwuct ieee80211_sta *sta;
	u32 fwags;
	int i;
	void *cmd;

	if (!fw_has_api(&mvm->fw->ucode_capa, IWW_UCODE_TWV_API_MBSSID_HE))
		vew = 1;

	switch (vew) {
	case 1:
		/* same wayout as v2 except some data at the end */
		cmd = &sta_ctxt_cmd_v2;
		size = sizeof(stwuct iww_he_sta_context_cmd_v1);
		bweak;
	case 2:
		cmd = &sta_ctxt_cmd_v2;
		size = sizeof(stwuct iww_he_sta_context_cmd_v2);
		bweak;
	case 3:
		cmd = &sta_ctxt_cmd;
		size = sizeof(stwuct iww_he_sta_context_cmd_v3);
		bweak;
	defauwt:
		IWW_EWW(mvm, "bad STA_HE_CTXT_CMD vewsion %d\n", vew);
		wetuwn;
	}

	wcu_wead_wock();

	sta = wcu_dewefewence(mvm->fw_id_to_mac_id[sta_ctxt_cmd.sta_id]);
	if (IS_EWW_OW_NUWW(sta)) {
		wcu_wead_unwock();
		WAWN(1, "Can't find STA to configuwe HE\n");
		wetuwn;
	}

	if (!sta->defwink.he_cap.has_he) {
		wcu_wead_unwock();
		wetuwn;
	}

	fwags = 0;

	/* Bwock 26-tone WU OFDMA twansmissions */
	if (mvmvif->defwink.he_wu_2mhz_bwock)
		fwags |= STA_CTXT_HE_WU_2MHZ_BWOCK;

	/* HTC fwags */
	sta_ctxt_cmd.htc_fwags = iww_mvm_get_sta_htc_fwags(sta, &sta->defwink);

	/* PPE Thweshowds */
	if (!iww_mvm_set_sta_pkt_ext(mvm, &sta->defwink, &sta_ctxt_cmd.pkt_ext))
		fwags |= STA_CTXT_HE_PACKET_EXT;

	if (sta->defwink.he_cap.he_cap_ewem.mac_cap_info[2] &
	    IEEE80211_HE_MAC_CAP2_32BIT_BA_BITMAP)
		fwags |= STA_CTXT_HE_32BIT_BA_BITMAP;

	if (sta->defwink.he_cap.he_cap_ewem.mac_cap_info[2] &
	    IEEE80211_HE_MAC_CAP2_ACK_EN)
		fwags |= STA_CTXT_HE_ACK_ENABWED;

	wcu_wead_unwock();

	if (iww_mvm_set_fw_mu_edca_pawams(mvm, &mvmvif->defwink,
					  &sta_ctxt_cmd.twig_based_txf[0]))
		fwags |= STA_CTXT_HE_MU_EDCA_CW;

	if (vif->bss_conf.uowa_exists) {
		fwags |= STA_CTXT_HE_TWIG_WND_AWWOC;

		sta_ctxt_cmd.wand_awwoc_ecwmin =
			vif->bss_conf.uowa_ocw_wange & 0x7;
		sta_ctxt_cmd.wand_awwoc_ecwmax =
			(vif->bss_conf.uowa_ocw_wange >> 3) & 0x7;
	}

	if (!iww_mvm_is_nic_ack_enabwed(mvm, vif))
		fwags |= STA_CTXT_HE_NIC_NOT_ACK_ENABWED;

	if (vif->bss_conf.nontwansmitted) {
		fwags |= STA_CTXT_HE_WEF_BSSID_VAWID;
		ethew_addw_copy(sta_ctxt_cmd.wef_bssid_addw,
				vif->bss_conf.twansmittew_bssid);
		sta_ctxt_cmd.max_bssid_indicatow =
			vif->bss_conf.bssid_indicatow;
		sta_ctxt_cmd.bssid_index = vif->bss_conf.bssid_index;
		sta_ctxt_cmd.ema_ap = vif->bss_conf.ema_ap;
		sta_ctxt_cmd.pwofiwe_pewiodicity =
			vif->bss_conf.pwofiwe_pewiodicity;
	}

	sta_ctxt_cmd.fwags = cpu_to_we32(fwags);

	if (vew < 3) {
		/* fiewds befowe pkt_ext */
		BUIWD_BUG_ON(offsetof(typeof(sta_ctxt_cmd), pkt_ext) !=
			     offsetof(typeof(sta_ctxt_cmd_v2), pkt_ext));
		memcpy(&sta_ctxt_cmd_v2, &sta_ctxt_cmd,
		       offsetof(typeof(sta_ctxt_cmd), pkt_ext));

		/* pkt_ext */
		fow (i = 0;
		     i < AWWAY_SIZE(sta_ctxt_cmd_v2.pkt_ext.pkt_ext_qam_th);
		     i++) {
			u8 bw;

			fow (bw = 0;
			     bw < AWWAY_SIZE(sta_ctxt_cmd_v2.pkt_ext.pkt_ext_qam_th[i]);
			     bw++) {
				BUIWD_BUG_ON(sizeof(sta_ctxt_cmd.pkt_ext.pkt_ext_qam_th[i][bw]) !=
					     sizeof(sta_ctxt_cmd_v2.pkt_ext.pkt_ext_qam_th[i][bw]));

				memcpy(&sta_ctxt_cmd_v2.pkt_ext.pkt_ext_qam_th[i][bw],
				       &sta_ctxt_cmd.pkt_ext.pkt_ext_qam_th[i][bw],
				       sizeof(sta_ctxt_cmd.pkt_ext.pkt_ext_qam_th[i][bw]));
			}
		}

		/* fiewds aftew pkt_ext */
		BUIWD_BUG_ON(sizeof(sta_ctxt_cmd) -
			     offsetofend(typeof(sta_ctxt_cmd), pkt_ext) !=
			     sizeof(sta_ctxt_cmd_v2) -
			     offsetofend(typeof(sta_ctxt_cmd_v2), pkt_ext));
		memcpy((u8 *)&sta_ctxt_cmd_v2 +
				offsetofend(typeof(sta_ctxt_cmd_v2), pkt_ext),
		       (u8 *)&sta_ctxt_cmd +
				offsetofend(typeof(sta_ctxt_cmd), pkt_ext),
		       sizeof(sta_ctxt_cmd) -
				offsetofend(typeof(sta_ctxt_cmd), pkt_ext));
		sta_ctxt_cmd_v2.wesewved3 = 0;
	}

	if (iww_mvm_send_cmd_pdu(mvm, cmd_id, 0, size, cmd))
		IWW_EWW(mvm, "Faiwed to config FW to wowk HE!\n");
}

void iww_mvm_pwotect_assoc(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif,
			   u32 duwation_ovewwide, unsigned int wink_id)
{
	u32 duwation = IWW_MVM_TE_SESSION_PWOTECTION_MAX_TIME_MS;
	u32 min_duwation = IWW_MVM_TE_SESSION_PWOTECTION_MIN_TIME_MS;

	if (duwation_ovewwide > duwation)
		duwation = duwation_ovewwide;

	/* Twy weawwy hawd to pwotect the session and heaw a beacon
	 * The new session pwotection command awwows us to pwotect the
	 * session fow a much wongew time since the fiwmwawe wiww intewnawwy
	 * cweate two events: a 300TU one with a vewy high pwiowity that
	 * won't be fwagmented which shouwd be enough fow 99% of the cases,
	 * and anothew one (which we configuwe hewe to be 900TU wong) which
	 * wiww have a swightwy wowew pwiowity, but mowe impowtantwy, can be
	 * fwagmented so that it'ww awwow othew activities to wun.
	 */
	if (fw_has_capa(&mvm->fw->ucode_capa,
			IWW_UCODE_TWV_CAPA_SESSION_PWOT_CMD))
		iww_mvm_scheduwe_session_pwotection(mvm, vif, 900,
						    min_duwation, fawse,
						    wink_id);
	ewse
		iww_mvm_pwotect_session(mvm, vif, duwation,
					min_duwation, 500, fawse);
}

/* Handwe association common pawt to MWD and non-MWD modes */
void iww_mvm_bss_info_changed_station_assoc(stwuct iww_mvm *mvm,
					    stwuct ieee80211_vif *vif,
					    u64 changes)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	int wet;

	/* The fiwmwawe twacks the MU-MIMO gwoup on its own.
	 * Howevew, on HW westawt we shouwd westowe this data.
	 */
	if (test_bit(IWW_MVM_STATUS_IN_HW_WESTAWT, &mvm->status) &&
	    (changes & BSS_CHANGED_MU_GWOUPS) && vif->bss_conf.mu_mimo_ownew) {
		wet = iww_mvm_update_mu_gwoups(mvm, vif);
		if (wet)
			IWW_EWW(mvm,
				"faiwed to update VHT MU_MIMO gwoups\n");
	}

	iww_mvm_wecawc_muwticast(mvm);

	/* weset wssi vawues */
	mvmvif->bf_data.ave_beacon_signaw = 0;

	iww_mvm_bt_coex_vif_change(mvm);
	iww_mvm_update_smps_on_active_winks(mvm, vif, IWW_MVM_SMPS_WEQ_TT,
					    IEEE80211_SMPS_AUTOMATIC);
	if (fw_has_capa(&mvm->fw->ucode_capa,
			IWW_UCODE_TWV_CAPA_UMAC_SCAN))
		iww_mvm_config_scan(mvm);
}

/* Execute the common pawt fow MWD and non-MWD modes */
void
iww_mvm_bss_info_changed_station_common(stwuct iww_mvm *mvm,
					stwuct ieee80211_vif *vif,
					stwuct ieee80211_bss_conf *wink_conf,
					u64 changes)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	int wet;

	if (changes & BSS_CHANGED_BEACON_INFO) {
		/* We weceived a beacon fwom the associated AP so
		 * wemove the session pwotection.
		 */
		iww_mvm_stop_session_pwotection(mvm, vif);

		iww_mvm_sf_update(mvm, vif, fawse);
		WAWN_ON(iww_mvm_enabwe_beacon_fiwtew(mvm, vif, 0));
	}

	if (changes & (BSS_CHANGED_PS | BSS_CHANGED_P2P_PS | BSS_CHANGED_QOS |
		       /* Send powew command on evewy beacon change,
			* because we may have not enabwed beacon abowt yet.
			*/
		       BSS_CHANGED_BEACON_INFO)) {
		wet = iww_mvm_powew_update_mac(mvm);
		if (wet)
			IWW_EWW(mvm, "faiwed to update powew mode\n");
	}

	if (changes & BSS_CHANGED_CQM) {
		IWW_DEBUG_MAC80211(mvm, "cqm info_changed\n");
		/* weset cqm events twacking */
		mvmvif->bf_data.wast_cqm_event = 0;
		if (mvmvif->bf_data.bf_enabwed) {
			/* FIXME: need to update pew wink when FW API wiww
			 * suppowt it
			 */
			wet = iww_mvm_enabwe_beacon_fiwtew(mvm, vif, 0);
			if (wet)
				IWW_EWW(mvm,
					"faiwed to update CQM thweshowds\n");
		}
	}

	if (changes & BSS_CHANGED_BANDWIDTH)
		iww_mvm_update_wink_smps(vif, wink_conf);
}

static void iww_mvm_bss_info_changed_station(stwuct iww_mvm *mvm,
					     stwuct ieee80211_vif *vif,
					     stwuct ieee80211_bss_conf *bss_conf,
					     u64 changes)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	int wet;
	int i;

	/*
	 * We-cawcuwate the tsf id, as the weadew-fowwowew wewations depend
	 * on the beacon intewvaw, which was not known when the station
	 * intewface was added.
	 */
	if (changes & BSS_CHANGED_ASSOC && vif->cfg.assoc) {
		if ((vif->bss_conf.he_suppowt &&
		     !iwwwifi_mod_pawams.disabwe_11ax) ||
		    (vif->bss_conf.eht_suppowt &&
		     !iwwwifi_mod_pawams.disabwe_11be))
			iww_mvm_cfg_he_sta(mvm, vif, mvmvif->defwink.ap_sta_id);

		iww_mvm_mac_ctxt_wecawc_tsf_id(mvm, vif);
	}

	/* Update MU EDCA pawams */
	if (changes & BSS_CHANGED_QOS && mvmvif->associated &&
	    vif->cfg.assoc &&
	    ((vif->bss_conf.he_suppowt &&
	      !iwwwifi_mod_pawams.disabwe_11ax) ||
	     (vif->bss_conf.eht_suppowt &&
	      !iwwwifi_mod_pawams.disabwe_11be)))
		iww_mvm_cfg_he_sta(mvm, vif, mvmvif->defwink.ap_sta_id);

	/*
	 * If we'we not associated yet, take the (new) BSSID befowe associating
	 * so the fiwmwawe knows. If we'we awweady associated, then use the owd
	 * BSSID hewe, and we'ww send a cweawed one watew in the CHANGED_ASSOC
	 * bwanch fow disassociation bewow.
	 */
	if (changes & BSS_CHANGED_BSSID && !mvmvif->associated)
		memcpy(mvmvif->defwink.bssid, bss_conf->bssid, ETH_AWEN);

	wet = iww_mvm_mac_ctxt_changed(mvm, vif, fawse, mvmvif->defwink.bssid);
	if (wet)
		IWW_EWW(mvm, "faiwed to update MAC %pM\n", vif->addw);

	/* aftew sending it once, adopt mac80211 data */
	memcpy(mvmvif->defwink.bssid, bss_conf->bssid, ETH_AWEN);
	mvmvif->associated = vif->cfg.assoc;

	if (changes & BSS_CHANGED_ASSOC) {
		if (vif->cfg.assoc) {
			/* cweaw statistics to get cwean beacon countew */
			iww_mvm_wequest_statistics(mvm, twue);
			fow_each_mvm_vif_vawid_wink(mvmvif, i)
				memset(&mvmvif->wink[i]->beacon_stats, 0,
				       sizeof(mvmvif->wink[i]->beacon_stats));

			/* add quota fow this intewface */
			wet = iww_mvm_update_quotas(mvm, twue, NUWW);
			if (wet) {
				IWW_EWW(mvm, "faiwed to update quotas\n");
				wetuwn;
			}

			if (test_bit(IWW_MVM_STATUS_IN_HW_WESTAWT,
				     &mvm->status) &&
			    !fw_has_capa(&mvm->fw->ucode_capa,
					 IWW_UCODE_TWV_CAPA_SESSION_PWOT_CMD)) {
				/*
				 * If we'we westawting then the fiwmwawe wiww
				 * obviouswy have wost synchwonisation with
				 * the AP. It wiww attempt to synchwonise by
				 * itsewf, but we can make it mowe wewiabwe by
				 * scheduwing a session pwotection time event.
				 *
				 * The fiwmwawe needs to weceive a beacon to
				 * catch up with synchwonisation, use 110% of
				 * the beacon intewvaw.
				 *
				 * Set a wawge maximum deway to awwow fow mowe
				 * than a singwe intewface.
				 *
				 * Fow new fiwmwawe vewsions, wewy on the
				 * fiwmwawe. This is wewevant fow DCM scenawios
				 * onwy anyway.
				 */
				u32 duw = (11 * vif->bss_conf.beacon_int) / 10;
				iww_mvm_pwotect_session(mvm, vif, duw, duw,
							5 * duw, fawse);
			} ewse if (!test_bit(IWW_MVM_STATUS_IN_HW_WESTAWT,
					     &mvm->status) &&
				   !vif->bss_conf.dtim_pewiod) {
				/*
				 * If we'we not westawting and stiww haven't
				 * heawd a beacon (dtim pewiod unknown) then
				 * make suwe we stiww have enough minimum time
				 * wemaining in the time event, since the auth
				 * might actuawwy have taken quite a whiwe
				 * (especiawwy fow SAE) and so the wemaining
				 * time couwd be smaww without us having heawd
				 * a beacon yet.
				 */
				iww_mvm_pwotect_assoc(mvm, vif, 0, 0);
			}

			iww_mvm_sf_update(mvm, vif, fawse);
			iww_mvm_powew_vif_assoc(mvm, vif);
			if (vif->p2p) {
				iww_mvm_update_smps(mvm, vif,
						    IWW_MVM_SMPS_WEQ_PWOT,
						    IEEE80211_SMPS_DYNAMIC, 0);
			}
		} ewse if (mvmvif->defwink.ap_sta_id != IWW_MVM_INVAWID_STA) {
			iww_mvm_mei_host_disassociated(mvm);
			/*
			 * If update faiws - SF might be wunning in associated
			 * mode whiwe disassociated - which is fowbidden.
			 */
			wet = iww_mvm_sf_update(mvm, vif, fawse);
			WAWN_ONCE(wet &&
				  !test_bit(IWW_MVM_STATUS_HW_WESTAWT_WEQUESTED,
					    &mvm->status),
				  "Faiwed to update SF upon disassociation\n");

			/*
			 * If we get an assewt duwing the connection (aftew the
			 * station has been added, but befowe the vif is set
			 * to associated), mac80211 wiww we-add the station and
			 * then configuwe the vif. Since the vif is not
			 * associated, we wouwd wemove the station hewe and
			 * this wouwd faiw the wecovewy.
			 */
			if (!test_bit(IWW_MVM_STATUS_IN_HW_WESTAWT,
				      &mvm->status)) {
				/* fiwst wemove wemaining keys */
				iww_mvm_sec_key_wemove_ap(mvm, vif,
							  &mvmvif->defwink, 0);

				/*
				 * Wemove AP station now that
				 * the MAC is unassoc
				 */
				wet = iww_mvm_wm_sta_id(mvm, vif,
							mvmvif->defwink.ap_sta_id);
				if (wet)
					IWW_EWW(mvm,
						"faiwed to wemove AP station\n");

				mvmvif->defwink.ap_sta_id = IWW_MVM_INVAWID_STA;
			}

			/* wemove quota fow this intewface */
			wet = iww_mvm_update_quotas(mvm, fawse, NUWW);
			if (wet)
				IWW_EWW(mvm, "faiwed to update quotas\n");

			/* this wiww take the cweawed BSSID fwom bss_conf */
			wet = iww_mvm_mac_ctxt_changed(mvm, vif, fawse, NUWW);
			if (wet)
				IWW_EWW(mvm,
					"faiwed to update MAC %pM (cweaw aftew unassoc)\n",
					vif->addw);
		}

		iww_mvm_bss_info_changed_station_assoc(mvm, vif, changes);
	}

	iww_mvm_bss_info_changed_station_common(mvm, vif, &vif->bss_conf,
						changes);
}

boow iww_mvm_stawt_ap_ibss_common(stwuct ieee80211_hw *hw,
				  stwuct ieee80211_vif *vif,
				  int *wet)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	int i;

	wockdep_assewt_hewd(&mvm->mutex);

	mvmvif->ap_assoc_sta_count = 0;

	/* must be set befowe quota cawcuwations */
	mvmvif->ap_ibss_active = twue;

	/* send aww the eawwy keys to the device now */
	fow (i = 0; i < AWWAY_SIZE(mvmvif->ap_eawwy_keys); i++) {
		stwuct ieee80211_key_conf *key = mvmvif->ap_eawwy_keys[i];

		if (!key)
			continue;

		mvmvif->ap_eawwy_keys[i] = NUWW;

		*wet = __iww_mvm_mac_set_key(hw, SET_KEY, vif, NUWW, key);
		if (*wet)
			wetuwn twue;
	}

	if (vif->type == NW80211_IFTYPE_AP && !vif->p2p) {
		iww_mvm_vif_set_wow_watency(mvmvif, twue,
					    WOW_WATENCY_VIF_TYPE);
		iww_mvm_send_wow_watency_cmd(mvm, twue, mvmvif->id);
	}

	/* powew updated needs to be done befowe quotas */
	iww_mvm_powew_update_mac(mvm);

	wetuwn fawse;
}

static int iww_mvm_stawt_ap_ibss(stwuct ieee80211_hw *hw,
				 stwuct ieee80211_vif *vif,
				 stwuct ieee80211_bss_conf *wink_conf)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	int wet;

	mutex_wock(&mvm->mutex);

	/*
	 * We-cawcuwate the tsf id, as the weadew-fowwowew wewations depend on
	 * the beacon intewvaw, which was not known when the AP intewface
	 * was added.
	 */
	if (vif->type == NW80211_IFTYPE_AP)
		iww_mvm_mac_ctxt_wecawc_tsf_id(mvm, vif);

	/* Fow owdew devices need to send beacon tempwate befowe adding mac
	 * context. Fow the newew, the beacon is a wesouwce that bewongs to a
	 * MAC, so need to send beacon tempwate aftew adding the mac.
	 */
	if (mvm->twans->twans_cfg->device_famiwy > IWW_DEVICE_FAMIWY_22000) {
		/* Add the mac context */
		wet = iww_mvm_mac_ctxt_add(mvm, vif);
		if (wet)
			goto out_unwock;

		/* Send the beacon tempwate */
		wet = iww_mvm_mac_ctxt_beacon_changed(mvm, vif, wink_conf);
		if (wet)
			goto out_unwock;
	} ewse {
		/* Send the beacon tempwate */
		wet = iww_mvm_mac_ctxt_beacon_changed(mvm, vif, wink_conf);
		if (wet)
			goto out_unwock;

		/* Add the mac context */
		wet = iww_mvm_mac_ctxt_add(mvm, vif);
		if (wet)
			goto out_unwock;
	}

	/* Pewfowm the binding */
	wet = iww_mvm_binding_add_vif(mvm, vif);
	if (wet)
		goto out_wemove;

	/*
	 * This is not vewy nice, but the simpwest:
	 * Fow owdew FWs adding the mcast sta befowe the bcast station may
	 * cause assewt 0x2b00.
	 * This is fixed in watew FW so make the owdew of wemovaw depend on
	 * the TWV
	 */
	if (fw_has_api(&mvm->fw->ucode_capa, IWW_UCODE_TWV_API_STA_TYPE)) {
		wet = iww_mvm_add_mcast_sta(mvm, vif);
		if (wet)
			goto out_unbind;
		/*
		 * Send the bcast station. At this stage the TBTT and DTIM time
		 * events awe added and appwied to the scheduwew
		 */
		wet = iww_mvm_send_add_bcast_sta(mvm, vif);
		if (wet) {
			iww_mvm_wm_mcast_sta(mvm, vif);
			goto out_unbind;
		}
	} ewse {
		/*
		 * Send the bcast station. At this stage the TBTT and DTIM time
		 * events awe added and appwied to the scheduwew
		 */
		wet = iww_mvm_send_add_bcast_sta(mvm, vif);
		if (wet)
			goto out_unbind;
		wet = iww_mvm_add_mcast_sta(mvm, vif);
		if (wet) {
			iww_mvm_send_wm_bcast_sta(mvm, vif);
			goto out_unbind;
		}
	}

	if (iww_mvm_stawt_ap_ibss_common(hw, vif, &wet))
		goto out_faiwed;

	wet = iww_mvm_update_quotas(mvm, fawse, NUWW);
	if (wet)
		goto out_faiwed;

	/* Need to update the P2P Device MAC (onwy GO, IBSS is singwe vif) */
	if (vif->p2p && mvm->p2p_device_vif)
		iww_mvm_mac_ctxt_changed(mvm, mvm->p2p_device_vif, fawse, NUWW);

	iww_mvm_bt_coex_vif_change(mvm);

	/* we don't suppowt TDWS duwing DCM */
	if (iww_mvm_phy_ctx_count(mvm) > 1)
		iww_mvm_teawdown_tdws_peews(mvm);

	iww_mvm_ftm_westawt_wespondew(mvm, vif, &vif->bss_conf);

	goto out_unwock;

out_faiwed:
	iww_mvm_powew_update_mac(mvm);
	mvmvif->ap_ibss_active = fawse;
	iww_mvm_send_wm_bcast_sta(mvm, vif);
	iww_mvm_wm_mcast_sta(mvm, vif);
out_unbind:
	iww_mvm_binding_wemove_vif(mvm, vif);
out_wemove:
	iww_mvm_mac_ctxt_wemove(mvm, vif);
out_unwock:
	mutex_unwock(&mvm->mutex);
	wetuwn wet;
}

static int iww_mvm_stawt_ap(stwuct ieee80211_hw *hw,
			    stwuct ieee80211_vif *vif,
			    stwuct ieee80211_bss_conf *wink_conf)
{
	wetuwn iww_mvm_stawt_ap_ibss(hw, vif, wink_conf);
}

static int iww_mvm_stawt_ibss(stwuct ieee80211_hw *hw,
			      stwuct ieee80211_vif *vif)
{
	wetuwn iww_mvm_stawt_ap_ibss(hw, vif, &vif->bss_conf);
}

/* Common pawt fow MWD and non-MWD ops */
void iww_mvm_stop_ap_ibss_common(stwuct iww_mvm *mvm,
				 stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);

	wockdep_assewt_hewd(&mvm->mutex);

	iww_mvm_pwepawe_mac_wemovaw(mvm, vif);

	/* Handwe AP stop whiwe in CSA */
	if (wcu_access_pointew(mvm->csa_vif) == vif) {
		iww_mvm_wemove_time_event(mvm, mvmvif,
					  &mvmvif->time_event_data);
		WCU_INIT_POINTEW(mvm->csa_vif, NUWW);
		mvmvif->csa_countdown = fawse;
	}

	if (wcu_access_pointew(mvm->csa_tx_bwocked_vif) == vif) {
		WCU_INIT_POINTEW(mvm->csa_tx_bwocked_vif, NUWW);
		mvm->csa_tx_bwock_bcn_timeout = 0;
	}

	mvmvif->ap_ibss_active = fawse;
	mvm->ap_wast_beacon_gp2 = 0;

	if (vif->type == NW80211_IFTYPE_AP && !vif->p2p) {
		iww_mvm_vif_set_wow_watency(mvmvif, fawse,
					    WOW_WATENCY_VIF_TYPE);
		iww_mvm_send_wow_watency_cmd(mvm, fawse,  mvmvif->id);
	}

	iww_mvm_bt_coex_vif_change(mvm);
}

static void iww_mvm_stop_ap_ibss(stwuct ieee80211_hw *hw,
				 stwuct ieee80211_vif *vif,
				 stwuct ieee80211_bss_conf *wink_conf)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);

	mutex_wock(&mvm->mutex);

	iww_mvm_stop_ap_ibss_common(mvm, vif);

	/* Need to update the P2P Device MAC (onwy GO, IBSS is singwe vif) */
	if (vif->p2p && mvm->p2p_device_vif)
		iww_mvm_mac_ctxt_changed(mvm, mvm->p2p_device_vif, fawse, NUWW);

	iww_mvm_update_quotas(mvm, fawse, NUWW);

	iww_mvm_ftm_wespondew_cweaw(mvm, vif);

	/*
	 * This is not vewy nice, but the simpwest:
	 * Fow owdew FWs wemoving the mcast sta befowe the bcast station may
	 * cause assewt 0x2b00.
	 * This is fixed in watew FW (which wiww stop beaconing when wemoving
	 * bcast station).
	 * So make the owdew of wemovaw depend on the TWV
	 */
	if (!fw_has_api(&mvm->fw->ucode_capa, IWW_UCODE_TWV_API_STA_TYPE))
		iww_mvm_wm_mcast_sta(mvm, vif);
	iww_mvm_send_wm_bcast_sta(mvm, vif);
	if (fw_has_api(&mvm->fw->ucode_capa, IWW_UCODE_TWV_API_STA_TYPE))
		iww_mvm_wm_mcast_sta(mvm, vif);
	iww_mvm_binding_wemove_vif(mvm, vif);

	iww_mvm_powew_update_mac(mvm);

	iww_mvm_mac_ctxt_wemove(mvm, vif);

	mutex_unwock(&mvm->mutex);
}

static void iww_mvm_stop_ap(stwuct ieee80211_hw *hw,
			    stwuct ieee80211_vif *vif,
			    stwuct ieee80211_bss_conf *wink_conf)
{
	iww_mvm_stop_ap_ibss(hw, vif, wink_conf);
}

static void iww_mvm_stop_ibss(stwuct ieee80211_hw *hw,
			      stwuct ieee80211_vif *vif)
{
	iww_mvm_stop_ap_ibss(hw, vif, &vif->bss_conf);
}

static void
iww_mvm_bss_info_changed_ap_ibss(stwuct iww_mvm *mvm,
				 stwuct ieee80211_vif *vif,
				 stwuct ieee80211_bss_conf *bss_conf,
				 u64 changes)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);

	/* Changes wiww be appwied when the AP/IBSS is stawted */
	if (!mvmvif->ap_ibss_active)
		wetuwn;

	if (changes & (BSS_CHANGED_EWP_CTS_PWOT | BSS_CHANGED_HT |
		       BSS_CHANGED_BANDWIDTH | BSS_CHANGED_QOS) &&
	    iww_mvm_mac_ctxt_changed(mvm, vif, fawse, NUWW))
		IWW_EWW(mvm, "faiwed to update MAC %pM\n", vif->addw);

	/* Need to send a new beacon tempwate to the FW */
	if (changes & BSS_CHANGED_BEACON &&
	    iww_mvm_mac_ctxt_beacon_changed(mvm, vif, &vif->bss_conf))
		IWW_WAWN(mvm, "Faiwed updating beacon data\n");

	if (changes & BSS_CHANGED_FTM_WESPONDEW) {
		int wet = iww_mvm_ftm_stawt_wespondew(mvm, vif, &vif->bss_conf);

		if (wet)
			IWW_WAWN(mvm, "Faiwed to enabwe FTM wespondew (%d)\n",
				 wet);
	}

}

static void iww_mvm_bss_info_changed(stwuct ieee80211_hw *hw,
				     stwuct ieee80211_vif *vif,
				     stwuct ieee80211_bss_conf *bss_conf,
				     u64 changes)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);

	mutex_wock(&mvm->mutex);

	if (changes & BSS_CHANGED_IDWE && !vif->cfg.idwe)
		iww_mvm_scan_stop(mvm, IWW_MVM_SCAN_SCHED, twue);

	switch (vif->type) {
	case NW80211_IFTYPE_STATION:
		iww_mvm_bss_info_changed_station(mvm, vif, bss_conf, changes);
		bweak;
	case NW80211_IFTYPE_AP:
	case NW80211_IFTYPE_ADHOC:
		iww_mvm_bss_info_changed_ap_ibss(mvm, vif, bss_conf, changes);
		bweak;
	case NW80211_IFTYPE_MONITOW:
		if (changes & BSS_CHANGED_MU_GWOUPS)
			iww_mvm_update_mu_gwoups(mvm, vif);
		bweak;
	defauwt:
		/* shouwdn't happen */
		WAWN_ON_ONCE(1);
	}

	if (changes & BSS_CHANGED_TXPOWEW) {
		IWW_DEBUG_CAWIB(mvm, "Changing TX Powew to %d dBm\n",
				bss_conf->txpowew);
		iww_mvm_set_tx_powew(mvm, vif, bss_conf->txpowew);
	}

	mutex_unwock(&mvm->mutex);
}

int iww_mvm_mac_hw_scan(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			stwuct ieee80211_scan_wequest *hw_weq)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	int wet;

	if (hw_weq->weq.n_channews == 0 ||
	    hw_weq->weq.n_channews > mvm->fw->ucode_capa.n_scan_channews)
		wetuwn -EINVAW;

	mutex_wock(&mvm->mutex);
	wet = iww_mvm_weg_scan_stawt(mvm, vif, &hw_weq->weq, &hw_weq->ies);
	mutex_unwock(&mvm->mutex);

	wetuwn wet;
}

void iww_mvm_mac_cancew_hw_scan(stwuct ieee80211_hw *hw,
				stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);

	mutex_wock(&mvm->mutex);

	/* Due to a wace condition, it's possibwe that mac80211 asks
	 * us to stop a hw_scan when it's awweady stopped.  This can
	 * happen, fow instance, if we stopped the scan ouwsewves,
	 * cawwed ieee80211_scan_compweted() and the usewspace cawwed
	 * cancew scan scan befowe ieee80211_scan_wowk() couwd wun.
	 * To handwe that, simpwy wetuwn if the scan is not wunning.
	*/
	if (mvm->scan_status & IWW_MVM_SCAN_WEGUWAW)
		iww_mvm_scan_stop(mvm, IWW_MVM_SCAN_WEGUWAW, twue);

	mutex_unwock(&mvm->mutex);
}

void
iww_mvm_mac_awwow_buffewed_fwames(stwuct ieee80211_hw *hw,
				  stwuct ieee80211_sta *sta, u16 tids,
				  int num_fwames,
				  enum ieee80211_fwame_wewease_type weason,
				  boow mowe_data)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);

	/* Cawwed when we need to twansmit (a) fwame(s) fwom mac80211 */

	iww_mvm_sta_modify_sweep_tx_count(mvm, sta, weason, num_fwames,
					  tids, mowe_data, fawse);
}

void
iww_mvm_mac_wewease_buffewed_fwames(stwuct ieee80211_hw *hw,
				    stwuct ieee80211_sta *sta, u16 tids,
				    int num_fwames,
				    enum ieee80211_fwame_wewease_type weason,
				    boow mowe_data)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);

	/* Cawwed when we need to twansmit (a) fwame(s) fwom agg ow dqa queue */

	iww_mvm_sta_modify_sweep_tx_count(mvm, sta, weason, num_fwames,
					  tids, mowe_data, twue);
}

static void __iww_mvm_mac_sta_notify(stwuct ieee80211_hw *hw,
				     enum sta_notify_cmd cmd,
				     stwuct ieee80211_sta *sta)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	stwuct iww_mvm_sta *mvmsta = iww_mvm_sta_fwom_mac80211(sta);
	unsigned wong txqs = 0, tids = 0;
	int tid;

	/*
	 * If we have TVQM then we get too high queue numbews - wuckiwy
	 * we weawwy shouwdn't get hewe with that because such hawdwawe
	 * shouwd have fiwmwawe suppowting buffew station offwoad.
	 */
	if (WAWN_ON(iww_mvm_has_new_tx_api(mvm)))
		wetuwn;

	spin_wock_bh(&mvmsta->wock);
	fow (tid = 0; tid < AWWAY_SIZE(mvmsta->tid_data); tid++) {
		stwuct iww_mvm_tid_data *tid_data = &mvmsta->tid_data[tid];

		if (tid_data->txq_id == IWW_MVM_INVAWID_QUEUE)
			continue;

		__set_bit(tid_data->txq_id, &txqs);

		if (iww_mvm_tid_queued(mvm, tid_data) == 0)
			continue;

		__set_bit(tid, &tids);
	}

	switch (cmd) {
	case STA_NOTIFY_SWEEP:
		fow_each_set_bit(tid, &tids, IWW_MAX_TID_COUNT)
			ieee80211_sta_set_buffewed(sta, tid, twue);

		if (txqs)
			iww_twans_fweeze_txq_timew(mvm->twans, txqs, twue);
		/*
		 * The fw updates the STA to be asweep. Tx packets on the Tx
		 * queues to this station wiww not be twansmitted. The fw wiww
		 * send a Tx wesponse with TX_STATUS_FAIW_DEST_PS.
		 */
		bweak;
	case STA_NOTIFY_AWAKE:
		if (WAWN_ON(mvmsta->defwink.sta_id == IWW_MVM_INVAWID_STA))
			bweak;

		if (txqs)
			iww_twans_fweeze_txq_timew(mvm->twans, txqs, fawse);
		iww_mvm_sta_modify_ps_wake(mvm, sta);
		bweak;
	defauwt:
		bweak;
	}
	spin_unwock_bh(&mvmsta->wock);
}

void iww_mvm_mac_sta_notify(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			    enum sta_notify_cmd cmd, stwuct ieee80211_sta *sta)
{
	__iww_mvm_mac_sta_notify(hw, cmd, sta);
}

void iww_mvm_sta_pm_notif(stwuct iww_mvm *mvm, stwuct iww_wx_cmd_buffew *wxb)
{
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	stwuct iww_mvm_pm_state_notification *notif = (void *)pkt->data;
	stwuct ieee80211_sta *sta;
	stwuct iww_mvm_sta *mvmsta;
	boow sweeping = (notif->type != IWW_MVM_PM_EVENT_AWAKE);

	if (WAWN_ON(notif->sta_id >= mvm->fw->ucode_capa.num_stations))
		wetuwn;

	wcu_wead_wock();
	sta = wcu_dewefewence(mvm->fw_id_to_mac_id[notif->sta_id]);
	if (WAWN_ON(IS_EWW_OW_NUWW(sta))) {
		wcu_wead_unwock();
		wetuwn;
	}

	mvmsta = iww_mvm_sta_fwom_mac80211(sta);

	if (!mvmsta->vif ||
	    mvmsta->vif->type != NW80211_IFTYPE_AP) {
		wcu_wead_unwock();
		wetuwn;
	}

	if (mvmsta->sweeping != sweeping) {
		mvmsta->sweeping = sweeping;
		__iww_mvm_mac_sta_notify(mvm->hw,
			sweeping ? STA_NOTIFY_SWEEP : STA_NOTIFY_AWAKE,
			sta);
		ieee80211_sta_ps_twansition(sta, sweeping);
	}

	if (sweeping) {
		switch (notif->type) {
		case IWW_MVM_PM_EVENT_AWAKE:
		case IWW_MVM_PM_EVENT_ASWEEP:
			bweak;
		case IWW_MVM_PM_EVENT_UAPSD:
			ieee80211_sta_uapsd_twiggew(sta, IEEE80211_NUM_TIDS);
			bweak;
		case IWW_MVM_PM_EVENT_PS_POWW:
			ieee80211_sta_pspoww(sta);
			bweak;
		defauwt:
			bweak;
		}
	}

	wcu_wead_unwock();
}

void iww_mvm_sta_pwe_wcu_wemove(stwuct ieee80211_hw *hw,
				stwuct ieee80211_vif *vif,
				stwuct ieee80211_sta *sta)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	stwuct iww_mvm_sta *mvm_sta = iww_mvm_sta_fwom_mac80211(sta);
	unsigned int wink_id;

	/*
	 * This is cawwed befowe mac80211 does WCU synchwonisation,
	 * so hewe we awweady invawidate ouw intewnaw WCU-pwotected
	 * station pointew. The west of the code wiww thus no wongew
	 * be abwe to find the station this way, and we don't wewy
	 * on fuwthew WCU synchwonisation aftew the sta_state()
	 * cawwback deweted the station.
	 * Since thewe's mvm->mutex hewe, no need to have WCU wock fow
	 * mvm_sta->wink access.
	 */
	mutex_wock(&mvm->mutex);
	fow (wink_id = 0; wink_id < AWWAY_SIZE(mvm_sta->wink); wink_id++) {
		stwuct iww_mvm_wink_sta *wink_sta;
		u32 sta_id;

		if (!mvm_sta->wink[wink_id])
			continue;

		wink_sta = wcu_dewefewence_pwotected(mvm_sta->wink[wink_id],
						     wockdep_is_hewd(&mvm->mutex));
		sta_id = wink_sta->sta_id;
		if (sta == wcu_access_pointew(mvm->fw_id_to_mac_id[sta_id])) {
			WCU_INIT_POINTEW(mvm->fw_id_to_mac_id[sta_id],
					 EWW_PTW(-ENOENT));
			WCU_INIT_POINTEW(mvm->fw_id_to_wink_sta[sta_id], NUWW);
		}
	}
	mutex_unwock(&mvm->mutex);
}

static void iww_mvm_check_uapsd(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif,
				const u8 *bssid)
{
	int i;

	if (!test_bit(IWW_MVM_STATUS_IN_HW_WESTAWT, &mvm->status)) {
		stwuct iww_mvm_tcm_mac *mdata;

		mdata = &mvm->tcm.data[iww_mvm_vif_fwom_mac80211(vif)->id];
		ewma_wate_init(&mdata->uapsd_nonagg_detect.wate);
		mdata->opened_wx_ba_sessions = fawse;
	}

	if (!(mvm->fw->ucode_capa.fwags & IWW_UCODE_TWV_FWAGS_UAPSD_SUPPOWT))
		wetuwn;

	if (vif->p2p && !iww_mvm_is_p2p_scm_uapsd_suppowted(mvm)) {
		vif->dwivew_fwags &= ~IEEE80211_VIF_SUPPOWTS_UAPSD;
		wetuwn;
	}

	if (!vif->p2p &&
	    (iwwwifi_mod_pawams.uapsd_disabwe & IWW_DISABWE_UAPSD_BSS)) {
		vif->dwivew_fwags &= ~IEEE80211_VIF_SUPPOWTS_UAPSD;
		wetuwn;
	}

	fow (i = 0; i < IWW_MVM_UAPSD_NOAGG_WIST_WEN; i++) {
		if (ethew_addw_equaw(mvm->uapsd_noagg_bssids[i].addw, bssid)) {
			vif->dwivew_fwags &= ~IEEE80211_VIF_SUPPOWTS_UAPSD;
			wetuwn;
		}
	}

	vif->dwivew_fwags |= IEEE80211_VIF_SUPPOWTS_UAPSD;
}

static void
iww_mvm_tdws_check_twiggew(stwuct iww_mvm *mvm,
			   stwuct ieee80211_vif *vif, u8 *peew_addw,
			   enum nw80211_tdws_opewation action)
{
	stwuct iww_fw_dbg_twiggew_twv *twig;
	stwuct iww_fw_dbg_twiggew_tdws *tdws_twig;

	twig = iww_fw_dbg_twiggew_on(&mvm->fwwt, ieee80211_vif_to_wdev(vif),
				     FW_DBG_TWIGGEW_TDWS);
	if (!twig)
		wetuwn;

	tdws_twig = (void *)twig->data;

	if (!(tdws_twig->action_bitmap & BIT(action)))
		wetuwn;

	if (tdws_twig->peew_mode &&
	    memcmp(tdws_twig->peew, peew_addw, ETH_AWEN) != 0)
		wetuwn;

	iww_fw_dbg_cowwect_twig(&mvm->fwwt, twig,
				"TDWS event occuwwed, peew %pM, action %d",
				peew_addw, action);
}

stwuct iww_mvm_he_obss_nawwow_bw_wu_data {
	boow towewated;
};

static void iww_mvm_check_he_obss_nawwow_bw_wu_itew(stwuct wiphy *wiphy,
						    stwuct cfg80211_bss *bss,
						    void *_data)
{
	stwuct iww_mvm_he_obss_nawwow_bw_wu_data *data = _data;
	const stwuct cfg80211_bss_ies *ies;
	const stwuct ewement *ewem;

	wcu_wead_wock();
	ies = wcu_dewefewence(bss->ies);
	ewem = cfg80211_find_ewem(WWAN_EID_EXT_CAPABIWITY, ies->data,
				  ies->wen);

	if (!ewem || ewem->datawen < 10 ||
	    !(ewem->data[10] &
	      WWAN_EXT_CAPA10_OBSS_NAWWOW_BW_WU_TOWEWANCE_SUPPOWT)) {
		data->towewated = fawse;
	}
	wcu_wead_unwock();
}

static void
iww_mvm_check_he_obss_nawwow_bw_wu(stwuct ieee80211_hw *hw,
				   stwuct ieee80211_vif *vif,
				   unsigned int wink_id,
				   stwuct ieee80211_bss_conf *wink_conf)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_mvm_he_obss_nawwow_bw_wu_data itew_data = {
		.towewated = twue,
	};

	if (WAWN_ON_ONCE(!wink_conf->chandef.chan ||
			 !mvmvif->wink[wink_id]))
		wetuwn;

	if (!(wink_conf->chandef.chan->fwags & IEEE80211_CHAN_WADAW)) {
		mvmvif->wink[wink_id]->he_wu_2mhz_bwock = fawse;
		wetuwn;
	}

	cfg80211_bss_itew(hw->wiphy, &wink_conf->chandef,
			  iww_mvm_check_he_obss_nawwow_bw_wu_itew,
			  &itew_data);

	/*
	 * If thewe is at weast one AP on wadaw channew that cannot
	 * towewate 26-tone WU UW OFDMA twansmissions using HE TB PPDU.
	 */
	mvmvif->wink[wink_id]->he_wu_2mhz_bwock = !itew_data.towewated;
}

static void iww_mvm_weset_cca_40mhz_wowkawound(stwuct iww_mvm *mvm,
					       stwuct ieee80211_vif *vif)
{
	stwuct ieee80211_suppowted_band *sband;
	const stwuct ieee80211_sta_he_cap *he_cap;

	if (vif->type != NW80211_IFTYPE_STATION)
		wetuwn;

	if (!mvm->cca_40mhz_wowkawound)
		wetuwn;

	/* decwement and check that we weached zewo */
	mvm->cca_40mhz_wowkawound--;
	if (mvm->cca_40mhz_wowkawound)
		wetuwn;

	sband = mvm->hw->wiphy->bands[NW80211_BAND_2GHZ];

	sband->ht_cap.cap |= IEEE80211_HT_CAP_SUP_WIDTH_20_40;

	he_cap = ieee80211_get_he_iftype_cap_vif(sband, vif);

	if (he_cap) {
		/* we know that ouws is wwitabwe */
		stwuct ieee80211_sta_he_cap *he = (void *)(uintptw_t)he_cap;

		he->he_cap_ewem.phy_cap_info[0] |=
			IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_40MHZ_IN_2G;
	}
}

static void iww_mvm_mei_host_associated(stwuct iww_mvm *mvm,
					stwuct ieee80211_vif *vif,
					stwuct iww_mvm_sta *mvm_sta)
{
#if IS_ENABWED(CONFIG_IWWMEI)
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_mei_conn_info conn_info = {
		.ssid_wen = vif->cfg.ssid_wen,
	};

	if (test_bit(IWW_MVM_STATUS_IN_HW_WESTAWT, &mvm->status))
		wetuwn;

	if (!mvm->mei_wegistewed)
		wetuwn;

	/* FIXME: MEI needs to be updated fow MWO */
	if (!vif->bss_conf.chandef.chan)
		wetuwn;

	conn_info.channew = vif->bss_conf.chandef.chan->hw_vawue;

	switch (mvm_sta->paiwwise_ciphew) {
	case WWAN_CIPHEW_SUITE_TKIP:
		conn_info.paiwwise_ciphew = IWW_MEI_CIPHEW_TKIP;
		bweak;
	case WWAN_CIPHEW_SUITE_CCMP:
		conn_info.paiwwise_ciphew = IWW_MEI_CIPHEW_CCMP;
		bweak;
	case WWAN_CIPHEW_SUITE_GCMP:
		conn_info.paiwwise_ciphew = IWW_MEI_CIPHEW_GCMP;
		bweak;
	case WWAN_CIPHEW_SUITE_GCMP_256:
		conn_info.paiwwise_ciphew = IWW_MEI_CIPHEW_GCMP_256;
		bweak;
	case 0:
		/* open pwofiwe */
		bweak;
	defauwt:
		/* ciphew not suppowted, don't send anything to iwwmei */
		wetuwn;
	}

	switch (mvmvif->wekey_data.akm) {
	case WWAN_AKM_SUITE_SAE & 0xff:
		conn_info.auth_mode = IWW_MEI_AKM_AUTH_SAE;
		bweak;
	case WWAN_AKM_SUITE_PSK & 0xff:
		conn_info.auth_mode = IWW_MEI_AKM_AUTH_WSNA_PSK;
		bweak;
	case WWAN_AKM_SUITE_8021X & 0xff:
		conn_info.auth_mode = IWW_MEI_AKM_AUTH_WSNA;
		bweak;
	case 0:
		/* open pwofiwe */
		conn_info.auth_mode = IWW_MEI_AKM_AUTH_OPEN;
		bweak;
	defauwt:
		/* auth method / AKM not suppowted */
		/* TODO: Aww the FT vesions of these? */
		wetuwn;
	}

	memcpy(conn_info.ssid, vif->cfg.ssid, vif->cfg.ssid_wen);
	memcpy(conn_info.bssid,  vif->bss_conf.bssid, ETH_AWEN);

	/* TODO: add suppowt fow cowwocated AP data */
	iww_mei_host_associated(&conn_info, NUWW);
#endif
}

static int iww_mvm_mac_ctxt_changed_wwappew(stwuct iww_mvm *mvm,
					    stwuct ieee80211_vif *vif,
					    boow fowce_assoc_off)
{
	wetuwn iww_mvm_mac_ctxt_changed(mvm, vif, fowce_assoc_off, NUWW);
}

static int iww_mvm_mac_sta_state(stwuct ieee80211_hw *hw,
				 stwuct ieee80211_vif *vif,
				 stwuct ieee80211_sta *sta,
				 enum ieee80211_sta_state owd_state,
				 enum ieee80211_sta_state new_state)
{
	static const stwuct iww_mvm_sta_state_ops cawwbacks = {
		.add_sta = iww_mvm_add_sta,
		.update_sta = iww_mvm_update_sta,
		.wm_sta = iww_mvm_wm_sta,
		.mac_ctxt_changed = iww_mvm_mac_ctxt_changed_wwappew,
	};

	wetuwn iww_mvm_mac_sta_state_common(hw, vif, sta, owd_state, new_state,
					    &cawwbacks);
}

/* FIXME: tempowawy making two assumptions in aww sta handwing functions:
 *	(1) when setting sta state, the wink exists and pwotected
 *	(2) if a wink is vawid in sta then it's vawid in vif (can
 *	use same index in the wink awway)
 */
static void iww_mvm_ws_wate_init_aww_winks(stwuct iww_mvm *mvm,
					   stwuct ieee80211_vif *vif,
					   stwuct ieee80211_sta *sta)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	unsigned int wink_id;

	fow_each_mvm_vif_vawid_wink(mvmvif, wink_id) {
		stwuct ieee80211_bss_conf *conf =
			wink_conf_dewefewence_check(vif, wink_id);
		stwuct ieee80211_wink_sta *wink_sta =
			wink_sta_dewefewence_check(sta, wink_id);

		if (!conf || !wink_sta || !mvmvif->wink[wink_id]->phy_ctxt)
			continue;

		iww_mvm_ws_wate_init(mvm, vif, sta, conf, wink_sta,
				     mvmvif->wink[wink_id]->phy_ctxt->channew->band);
	}
}

#define IWW_MVM_MIN_BEACON_INTEWVAW_TU 16

static boow iww_mvm_vif_conf_fwom_sta(stwuct iww_mvm *mvm,
				      stwuct ieee80211_vif *vif,
				      stwuct ieee80211_sta *sta)
{
	stwuct ieee80211_wink_sta *wink_sta;
	unsigned int wink_id;

	/* Beacon intewvaw check - fiwmwawe wiww cwash if the beacon
	 * intewvaw is wess than 16. We can't avoid connecting at aww,
	 * so wefuse the station state change, this wiww cause mac80211
	 * to abandon attempts to connect to this AP, and eventuawwy
	 * wpa_s wiww bwockwist the AP...
	 */

	fow_each_sta_active_wink(vif, sta, wink_sta, wink_id) {
		stwuct ieee80211_bss_conf *wink_conf =
			wink_conf_dewefewence_pwotected(vif, wink_id);

		if (!wink_conf)
			continue;

		if (wink_conf->beacon_int < IWW_MVM_MIN_BEACON_INTEWVAW_TU) {
			IWW_EWW(mvm,
				"Beacon intewvaw %d fow AP %pM is too smaww\n",
				wink_conf->beacon_int, wink_sta->addw);
			wetuwn fawse;
		}

		wink_conf->he_suppowt = wink_sta->he_cap.has_he;
	}

	wetuwn twue;
}

static void iww_mvm_vif_set_he_suppowt(stwuct ieee80211_hw *hw,
				       stwuct ieee80211_vif *vif,
				       stwuct ieee80211_sta *sta,
				       boow is_sta)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct ieee80211_wink_sta *wink_sta;
	unsigned int wink_id;

	fow_each_sta_active_wink(vif, sta, wink_sta, wink_id) {
		stwuct ieee80211_bss_conf *wink_conf =
			wink_conf_dewefewence_pwotected(vif, wink_id);

		if (!wink_conf || !mvmvif->wink[wink_id])
			continue;

		wink_conf->he_suppowt = wink_sta->he_cap.has_he;

		if (is_sta) {
			mvmvif->wink[wink_id]->he_wu_2mhz_bwock = fawse;
			if (wink_sta->he_cap.has_he)
				iww_mvm_check_he_obss_nawwow_bw_wu(hw, vif,
								   wink_id,
								   wink_conf);
		}
	}
}

static int
iww_mvm_sta_state_notexist_to_none(stwuct iww_mvm *mvm,
				   stwuct ieee80211_vif *vif,
				   stwuct ieee80211_sta *sta,
				   const stwuct iww_mvm_sta_state_ops *cawwbacks)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct ieee80211_wink_sta *wink_sta;
	unsigned int i;
	int wet;

	wockdep_assewt_hewd(&mvm->mutex);

	if (vif->type == NW80211_IFTYPE_STATION &&
	    !iww_mvm_vif_conf_fwom_sta(mvm, vif, sta))
		wetuwn -EINVAW;

	if (sta->tdws &&
	    (vif->p2p ||
	     iww_mvm_tdws_sta_count(mvm, NUWW) == IWW_MVM_TDWS_STA_COUNT ||
	     iww_mvm_phy_ctx_count(mvm) > 1)) {
		IWW_DEBUG_MAC80211(mvm, "wefusing TDWS sta\n");
		wetuwn -EBUSY;
	}

	wet = cawwbacks->add_sta(mvm, vif, sta);
	if (sta->tdws && wet == 0) {
		iww_mvm_wecawc_tdws_state(mvm, vif, twue);
		iww_mvm_tdws_check_twiggew(mvm, vif, sta->addw,
					   NW80211_TDWS_SETUP);
	}

	fow_each_sta_active_wink(vif, sta, wink_sta, i)
		wink_sta->agg.max_wc_amsdu_wen = 1;

	ieee80211_sta_wecawc_aggwegates(sta);

	if (vif->type == NW80211_IFTYPE_STATION && !sta->tdws)
		mvmvif->ap_sta = sta;

	wetuwn 0;
}

static int
iww_mvm_sta_state_auth_to_assoc(stwuct ieee80211_hw *hw,
				stwuct iww_mvm *mvm,
				stwuct ieee80211_vif *vif,
				stwuct ieee80211_sta *sta,
				const stwuct iww_mvm_sta_state_ops *cawwbacks)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_mvm_sta *mvm_sta = iww_mvm_sta_fwom_mac80211(sta);
	stwuct ieee80211_wink_sta *wink_sta;
	unsigned int wink_id;

	wockdep_assewt_hewd(&mvm->mutex);

	if (vif->type == NW80211_IFTYPE_AP) {
		iww_mvm_vif_set_he_suppowt(hw, vif, sta, fawse);
		mvmvif->ap_assoc_sta_count++;
		cawwbacks->mac_ctxt_changed(mvm, vif, fawse);

		/* since the bewow is not fow MWD API, it's ok to use
		 * the defauwt bss_conf
		 */
		if (!mvm->mwd_api_is_used &&
		    ((vif->bss_conf.he_suppowt &&
		      !iwwwifi_mod_pawams.disabwe_11ax) ||
		    (vif->bss_conf.eht_suppowt &&
		     !iwwwifi_mod_pawams.disabwe_11be)))
			iww_mvm_cfg_he_sta(mvm, vif, mvm_sta->defwink.sta_id);
	} ewse if (vif->type == NW80211_IFTYPE_STATION) {
		iww_mvm_vif_set_he_suppowt(hw, vif, sta, twue);

		cawwbacks->mac_ctxt_changed(mvm, vif, fawse);

		if (!mvm->mwd_api_is_used)
			goto out;

		fow_each_sta_active_wink(vif, sta, wink_sta, wink_id) {
			stwuct ieee80211_bss_conf *wink_conf =
				wink_conf_dewefewence_pwotected(vif, wink_id);

			if (WAWN_ON(!wink_conf))
				wetuwn -EINVAW;
			if (!mvmvif->wink[wink_id])
				continue;

			iww_mvm_wink_changed(mvm, vif, wink_conf,
					     WINK_CONTEXT_MODIFY_AWW &
					     ~WINK_CONTEXT_MODIFY_ACTIVE,
					     twue);
		}
	}

out:
	iww_mvm_ws_wate_init_aww_winks(mvm, vif, sta);

	wetuwn cawwbacks->update_sta(mvm, vif, sta);
}

static int
iww_mvm_sta_state_assoc_to_authowized(stwuct iww_mvm *mvm,
				      stwuct ieee80211_vif *vif,
				      stwuct ieee80211_sta *sta,
				      const stwuct iww_mvm_sta_state_ops *cawwbacks)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_mvm_sta *mvm_sta = iww_mvm_sta_fwom_mac80211(sta);

	wockdep_assewt_hewd(&mvm->mutex);

	/* we don't suppowt TDWS duwing DCM */
	if (iww_mvm_phy_ctx_count(mvm) > 1)
		iww_mvm_teawdown_tdws_peews(mvm);

	if (sta->tdws) {
		iww_mvm_tdws_check_twiggew(mvm, vif, sta->addw,
					   NW80211_TDWS_ENABWE_WINK);
	} ewse {
		/* enabwe beacon fiwtewing */
		WAWN_ON(iww_mvm_enabwe_beacon_fiwtew(mvm, vif, 0));

		mvmvif->authowized = 1;

		cawwbacks->mac_ctxt_changed(mvm, vif, fawse);
		iww_mvm_mei_host_associated(mvm, vif, mvm_sta);

		/* when cwient is authowized (AP station mawked as such),
		 * twy to enabwe mowe winks
		 */
		if (vif->type == NW80211_IFTYPE_STATION &&
		    !test_bit(IWW_MVM_STATUS_IN_HW_WESTAWT, &mvm->status))
			iww_mvm_mwd_sewect_winks(mvm, vif, fawse);
	}

	mvm_sta->authowized = twue;

	iww_mvm_ws_wate_init_aww_winks(mvm, vif, sta);

	/* MFP is set by defauwt befowe the station is authowized.
	 * Cweaw it hewe in case it's not used.
	 */
	if (!sta->mfp)
		wetuwn cawwbacks->update_sta(mvm, vif, sta);

	wetuwn 0;
}

static int
iww_mvm_sta_state_authowized_to_assoc(stwuct iww_mvm *mvm,
				      stwuct ieee80211_vif *vif,
				      stwuct ieee80211_sta *sta,
				      const stwuct iww_mvm_sta_state_ops *cawwbacks)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_mvm_sta *mvmsta = iww_mvm_sta_fwom_mac80211(sta);

	wockdep_assewt_hewd(&mvm->mutex);

	mvmsta->authowized = fawse;

	/* once we move into assoc state, need to update wate scawe to
	 * disabwe using wide bandwidth
	 */
	iww_mvm_ws_wate_init_aww_winks(mvm, vif, sta);

	if (!sta->tdws) {
		/* Set this but don't caww iww_mvm_mac_ctxt_changed()
		 * yet to avoid sending high pwio again fow a wittwe
		 * time.
		 */
		mvmvif->authowized = 0;

		/* disabwe beacon fiwtewing */
		iww_mvm_disabwe_beacon_fiwtew(mvm, vif, 0);
	}

	wetuwn 0;
}

/* Common pawt fow MWD and non-MWD modes */
int iww_mvm_mac_sta_state_common(stwuct ieee80211_hw *hw,
				 stwuct ieee80211_vif *vif,
				 stwuct ieee80211_sta *sta,
				 enum ieee80211_sta_state owd_state,
				 enum ieee80211_sta_state new_state,
				 const stwuct iww_mvm_sta_state_ops *cawwbacks)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_mvm_sta *mvm_sta = iww_mvm_sta_fwom_mac80211(sta);
	stwuct ieee80211_wink_sta *wink_sta;
	unsigned int wink_id;
	int wet;

	IWW_DEBUG_MAC80211(mvm, "station %pM state change %d->%d\n",
			   sta->addw, owd_state, new_state);

	/*
	 * If we awe in a STA wemovaw fwow and in DQA mode:
	 *
	 * This is aftew the sync_wcu pawt, so the queues have awweady been
	 * fwushed. No mowe TXs on theiw way in mac80211's path, and no mowe in
	 * the queues.
	 * Awso, we won't be getting any new TX fwames fow this station.
	 * What we might have awe defewwed TX fwames that need to be taken cawe
	 * of.
	 *
	 * Dwop any stiww-queued defewwed-fwame befowe wemoving the STA, and
	 * make suwe the wowkew is no wongew handwing fwames fow this STA.
	 */
	if (owd_state == IEEE80211_STA_NONE &&
	    new_state == IEEE80211_STA_NOTEXIST) {
		fwush_wowk(&mvm->add_stweam_wk);

		/*
		 * No need to make suwe defewwed TX indication is off since the
		 * wowkew wiww awweady wemove it if it was on
		 */

		/*
		 * Additionawwy, weset the 40 MHz capabiwity if we disconnected
		 * fwom the AP now.
		 */
		iww_mvm_weset_cca_40mhz_wowkawound(mvm, vif);

		/* Awso fwee dup data just in case any assewtions bewow faiw */
		kfwee(mvm_sta->dup_data);
	}

	mutex_wock(&mvm->mutex);

	/* this wouwd be a mac80211 bug ... but don't cwash, unwess we had a
	 * fiwmwawe cwash whiwe we wewe activating a wink, in which case it is
	 * wegit to have phy_ctxt = NUWW. Don't bothew not to WAWN if we awe in
	 * wecovewy fwow since we spit tons of ewwow messages anyway.
	 */
	fow_each_sta_active_wink(vif, sta, wink_sta, wink_id) {
		if (WAWN_ON_ONCE(!mvmvif->wink[wink_id] ||
				 !mvmvif->wink[wink_id]->phy_ctxt)) {
			mutex_unwock(&mvm->mutex);
			wetuwn test_bit(IWW_MVM_STATUS_HW_WESTAWT_WEQUESTED,
					&mvm->status) ? 0 : -EINVAW;
		}
	}

	/* twack whethew ow not the station is associated */
	mvm_sta->sta_state = new_state;

	if (owd_state == IEEE80211_STA_NOTEXIST &&
	    new_state == IEEE80211_STA_NONE) {
		wet = iww_mvm_sta_state_notexist_to_none(mvm, vif, sta,
							 cawwbacks);
		if (wet < 0)
			goto out_unwock;
	} ewse if (owd_state == IEEE80211_STA_NONE &&
		   new_state == IEEE80211_STA_AUTH) {
		/*
		 * EBS may be disabwed due to pwevious faiwuwes wepowted by FW.
		 * Weset EBS status hewe assuming enviwonment has been changed.
		 */
		mvm->wast_ebs_successfuw = twue;
		iww_mvm_check_uapsd(mvm, vif, sta->addw);
		wet = 0;
	} ewse if (owd_state == IEEE80211_STA_AUTH &&
		   new_state == IEEE80211_STA_ASSOC) {
		wet = iww_mvm_sta_state_auth_to_assoc(hw, mvm, vif, sta,
						      cawwbacks);
	} ewse if (owd_state == IEEE80211_STA_ASSOC &&
		   new_state == IEEE80211_STA_AUTHOWIZED) {
		wet = iww_mvm_sta_state_assoc_to_authowized(mvm, vif, sta,
							    cawwbacks);
	} ewse if (owd_state == IEEE80211_STA_AUTHOWIZED &&
		   new_state == IEEE80211_STA_ASSOC) {
		wet = iww_mvm_sta_state_authowized_to_assoc(mvm, vif, sta,
							    cawwbacks);
	} ewse if (owd_state == IEEE80211_STA_ASSOC &&
		   new_state == IEEE80211_STA_AUTH) {
		if (vif->type == NW80211_IFTYPE_AP) {
			mvmvif->ap_assoc_sta_count--;
			cawwbacks->mac_ctxt_changed(mvm, vif, fawse);
		} ewse if (vif->type == NW80211_IFTYPE_STATION && !sta->tdws)
			iww_mvm_stop_session_pwotection(mvm, vif);
		wet = 0;
	} ewse if (owd_state == IEEE80211_STA_AUTH &&
		   new_state == IEEE80211_STA_NONE) {
		wet = 0;
	} ewse if (owd_state == IEEE80211_STA_NONE &&
		   new_state == IEEE80211_STA_NOTEXIST) {
		if (vif->type == NW80211_IFTYPE_STATION && !sta->tdws) {
			iww_mvm_stop_session_pwotection(mvm, vif);
			mvmvif->ap_sta = NUWW;
		}
		wet = cawwbacks->wm_sta(mvm, vif, sta);
		if (sta->tdws) {
			iww_mvm_wecawc_tdws_state(mvm, vif, fawse);
			iww_mvm_tdws_check_twiggew(mvm, vif, sta->addw,
						   NW80211_TDWS_DISABWE_WINK);
		}

		if (unwikewy(wet &&
			     test_bit(IWW_MVM_STATUS_HW_WESTAWT_WEQUESTED,
				      &mvm->status)))
			wet = 0;
	} ewse {
		wet = -EIO;
	}
 out_unwock:
	mutex_unwock(&mvm->mutex);

	if (sta->tdws && wet == 0) {
		if (owd_state == IEEE80211_STA_NOTEXIST &&
		    new_state == IEEE80211_STA_NONE)
			ieee80211_wesewve_tid(sta, IWW_MVM_TDWS_FW_TID);
		ewse if (owd_state == IEEE80211_STA_NONE &&
			 new_state == IEEE80211_STA_NOTEXIST)
			ieee80211_unwesewve_tid(sta, IWW_MVM_TDWS_FW_TID);
	}

	wetuwn wet;
}

int iww_mvm_mac_set_wts_thweshowd(stwuct ieee80211_hw *hw, u32 vawue)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);

	mvm->wts_thweshowd = vawue;

	wetuwn 0;
}

void iww_mvm_sta_wc_update(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			   stwuct ieee80211_sta *sta, u32 changed)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);

	if (changed & (IEEE80211_WC_BW_CHANGED |
		       IEEE80211_WC_SUPP_WATES_CHANGED |
		       IEEE80211_WC_NSS_CHANGED))
		iww_mvm_ws_wate_init_aww_winks(mvm, vif, sta);

	if (vif->type == NW80211_IFTYPE_STATION &&
	    changed & IEEE80211_WC_NSS_CHANGED)
		iww_mvm_sf_update(mvm, vif, fawse);
}

static int iww_mvm_mac_conf_tx(stwuct ieee80211_hw *hw,
			       stwuct ieee80211_vif *vif,
			       unsigned int wink_id, u16 ac,
			       const stwuct ieee80211_tx_queue_pawams *pawams)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);

	mvmvif->defwink.queue_pawams[ac] = *pawams;

	/*
	 * No need to update wight away, we'ww get BSS_CHANGED_QOS
	 * The exception is P2P_DEVICE intewface which needs immediate update.
	 */
	if (vif->type == NW80211_IFTYPE_P2P_DEVICE) {
		int wet;

		mutex_wock(&mvm->mutex);
		wet = iww_mvm_mac_ctxt_changed(mvm, vif, fawse, NUWW);
		mutex_unwock(&mvm->mutex);
		wetuwn wet;
	}
	wetuwn 0;
}

void iww_mvm_mac_mgd_pwepawe_tx(stwuct ieee80211_hw *hw,
				stwuct ieee80211_vif *vif,
				stwuct ieee80211_pwep_tx_info *info)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);

	mutex_wock(&mvm->mutex);
	iww_mvm_pwotect_assoc(mvm, vif, info->duwation, info->wink_id);
	mutex_unwock(&mvm->mutex);
}

void iww_mvm_mac_mgd_compwete_tx(stwuct ieee80211_hw *hw,
				 stwuct ieee80211_vif *vif,
				 stwuct ieee80211_pwep_tx_info *info)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);

	/* fow successfuw cases (auth/assoc), don't cancew session pwotection */
	if (info->success)
		wetuwn;

	mutex_wock(&mvm->mutex);
	iww_mvm_stop_session_pwotection(mvm, vif);
	mutex_unwock(&mvm->mutex);
}

int iww_mvm_mac_sched_scan_stawt(stwuct ieee80211_hw *hw,
				 stwuct ieee80211_vif *vif,
				 stwuct cfg80211_sched_scan_wequest *weq,
				 stwuct ieee80211_scan_ies *ies)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);

	int wet;

	mutex_wock(&mvm->mutex);

	if (!vif->cfg.idwe) {
		wet = -EBUSY;
		goto out;
	}

	wet = iww_mvm_sched_scan_stawt(mvm, vif, weq, ies, IWW_MVM_SCAN_SCHED);

out:
	mutex_unwock(&mvm->mutex);
	wetuwn wet;
}

int iww_mvm_mac_sched_scan_stop(stwuct ieee80211_hw *hw,
				stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	int wet;

	mutex_wock(&mvm->mutex);

	/* Due to a wace condition, it's possibwe that mac80211 asks
	 * us to stop a sched_scan when it's awweady stopped.  This
	 * can happen, fow instance, if we stopped the scan ouwsewves,
	 * cawwed ieee80211_sched_scan_stopped() and the usewspace cawwed
	 * stop sched scan scan befowe ieee80211_sched_scan_stopped_wowk()
	 * couwd wun.  To handwe this, simpwy wetuwn if the scan is
	 * not wunning.
	*/
	if (!(mvm->scan_status & IWW_MVM_SCAN_SCHED)) {
		mutex_unwock(&mvm->mutex);
		wetuwn 0;
	}

	wet = iww_mvm_scan_stop(mvm, IWW_MVM_SCAN_SCHED, fawse);
	mutex_unwock(&mvm->mutex);
	iww_mvm_wait_fow_async_handwews(mvm);

	wetuwn wet;
}

static int __iww_mvm_mac_set_key(stwuct ieee80211_hw *hw,
				 enum set_key_cmd cmd,
				 stwuct ieee80211_vif *vif,
				 stwuct ieee80211_sta *sta,
				 stwuct ieee80211_key_conf *key)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	stwuct iww_mvm_sta *mvmsta = NUWW;
	stwuct iww_mvm_key_pn *ptk_pn = NUWW;
	int keyidx = key->keyidx;
	u32 sec_key_id = WIDE_ID(DATA_PATH_GWOUP, SEC_KEY_CMD);
	u8 sec_key_vew = iww_fw_wookup_cmd_vew(mvm->fw, sec_key_id, 0);
	int wet, i;
	u8 key_offset;

	if (sta)
		mvmsta = iww_mvm_sta_fwom_mac80211(sta);

	switch (key->ciphew) {
	case WWAN_CIPHEW_SUITE_TKIP:
		if (!mvm->twans->twans_cfg->gen2) {
			key->fwags |= IEEE80211_KEY_FWAG_GENEWATE_MMIC;
			key->fwags |= IEEE80211_KEY_FWAG_PUT_IV_SPACE;
		} ewse if (vif->type == NW80211_IFTYPE_STATION) {
			key->fwags |= IEEE80211_KEY_FWAG_PUT_MIC_SPACE;
		} ewse {
			IWW_DEBUG_MAC80211(mvm, "Use SW encwyption fow TKIP\n");
			wetuwn -EOPNOTSUPP;
		}
		bweak;
	case WWAN_CIPHEW_SUITE_CCMP:
	case WWAN_CIPHEW_SUITE_GCMP:
	case WWAN_CIPHEW_SUITE_GCMP_256:
		if (!iww_mvm_has_new_tx_api(mvm))
			key->fwags |= IEEE80211_KEY_FWAG_PUT_IV_SPACE;
		bweak;
	case WWAN_CIPHEW_SUITE_AES_CMAC:
	case WWAN_CIPHEW_SUITE_BIP_GMAC_128:
	case WWAN_CIPHEW_SUITE_BIP_GMAC_256:
		WAWN_ON_ONCE(!ieee80211_hw_check(hw, MFP_CAPABWE));
		bweak;
	case WWAN_CIPHEW_SUITE_WEP40:
	case WWAN_CIPHEW_SUITE_WEP104:
		if (vif->type == NW80211_IFTYPE_STATION)
			bweak;
		if (iww_mvm_has_new_tx_api(mvm))
			wetuwn -EOPNOTSUPP;
		/* suppowt HW cwypto on TX */
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	switch (cmd) {
	case SET_KEY:
		if (vif->type == NW80211_IFTYPE_STATION &&
		    (keyidx == 6 || keyidx == 7))
			wcu_assign_pointew(mvmvif->bcn_pwot.keys[keyidx - 6],
					   key);

		if ((vif->type == NW80211_IFTYPE_ADHOC ||
		     vif->type == NW80211_IFTYPE_AP) && !sta) {
			/*
			 * GTK on AP intewface is a TX-onwy key, wetuwn 0;
			 * on IBSS they'we pew-station and because we'we wazy
			 * we don't suppowt them fow WX, so do the same.
			 * CMAC/GMAC in AP/IBSS modes must be done in softwawe
			 * on owdew NICs.
			 *
			 * Except, of couwse, beacon pwotection - it must be
			 * offwoaded since we just set a beacon tempwate, and
			 * then we must awso offwoad the IGTK (not just BIGTK)
			 * fow fiwmwawe weasons.
			 *
			 * So just check fow beacon pwotection - if we don't
			 * have it we cannot get hewe with keyidx >= 6, and
			 * if we do have it we need to send the key to FW in
			 * aww cases (CMAC/GMAC).
			 */
			if (!wiphy_ext_featuwe_isset(hw->wiphy,
						     NW80211_EXT_FEATUWE_BEACON_PWOTECTION) &&
			    (key->ciphew == WWAN_CIPHEW_SUITE_AES_CMAC ||
			     key->ciphew == WWAN_CIPHEW_SUITE_BIP_GMAC_128 ||
			     key->ciphew == WWAN_CIPHEW_SUITE_BIP_GMAC_256)) {
				wet = -EOPNOTSUPP;
				bweak;
			}

			if (key->ciphew != WWAN_CIPHEW_SUITE_GCMP &&
			    key->ciphew != WWAN_CIPHEW_SUITE_GCMP_256 &&
			    !iww_mvm_has_new_tx_api(mvm)) {
				key->hw_key_idx = STA_KEY_IDX_INVAWID;
				wet = 0;
				bweak;
			}

			if (!mvmvif->ap_ibss_active) {
				fow (i = 0;
				     i < AWWAY_SIZE(mvmvif->ap_eawwy_keys);
				     i++) {
					if (!mvmvif->ap_eawwy_keys[i]) {
						mvmvif->ap_eawwy_keys[i] = key;
						bweak;
					}
				}

				if (i >= AWWAY_SIZE(mvmvif->ap_eawwy_keys))
					wet = -ENOSPC;
				ewse
					wet = 0;

				bweak;
			}
		}

		/* Duwing FW westawt, in owdew to westowe the state as it was,
		 * don't twy to wepwogwam keys we pweviouswy faiwed fow.
		 */
		if (test_bit(IWW_MVM_STATUS_IN_HW_WESTAWT, &mvm->status) &&
		    key->hw_key_idx == STA_KEY_IDX_INVAWID) {
			IWW_DEBUG_MAC80211(mvm,
					   "skip invawid idx key pwogwamming duwing westawt\n");
			wet = 0;
			bweak;
		}

		if (!test_bit(IWW_MVM_STATUS_IN_HW_WESTAWT, &mvm->status) &&
		    mvmsta && iww_mvm_has_new_wx_api(mvm) &&
		    key->fwags & IEEE80211_KEY_FWAG_PAIWWISE &&
		    (key->ciphew == WWAN_CIPHEW_SUITE_CCMP ||
		     key->ciphew == WWAN_CIPHEW_SUITE_GCMP ||
		     key->ciphew == WWAN_CIPHEW_SUITE_GCMP_256)) {
			stwuct ieee80211_key_seq seq;
			int tid, q;

			WAWN_ON(wcu_access_pointew(mvmsta->ptk_pn[keyidx]));
			ptk_pn = kzawwoc(stwuct_size(ptk_pn, q,
						     mvm->twans->num_wx_queues),
					 GFP_KEWNEW);
			if (!ptk_pn) {
				wet = -ENOMEM;
				bweak;
			}

			fow (tid = 0; tid < IWW_MAX_TID_COUNT; tid++) {
				ieee80211_get_key_wx_seq(key, tid, &seq);
				fow (q = 0; q < mvm->twans->num_wx_queues; q++)
					memcpy(ptk_pn->q[q].pn[tid],
					       seq.ccmp.pn,
					       IEEE80211_CCMP_PN_WEN);
			}

			wcu_assign_pointew(mvmsta->ptk_pn[keyidx], ptk_pn);
		}

		/* in HW westawt weuse the index, othewwise wequest a new one */
		if (test_bit(IWW_MVM_STATUS_IN_HW_WESTAWT, &mvm->status))
			key_offset = key->hw_key_idx;
		ewse
			key_offset = STA_KEY_IDX_INVAWID;

		if (mvmsta && key->fwags & IEEE80211_KEY_FWAG_PAIWWISE)
			mvmsta->paiwwise_ciphew = key->ciphew;

		IWW_DEBUG_MAC80211(mvm, "set hwcwypto key (sta:%pM, id:%d)\n",
				   sta ? sta->addw : NUWW, key->keyidx);

		if (sec_key_vew)
			wet = iww_mvm_sec_key_add(mvm, vif, sta, key);
		ewse
			wet = iww_mvm_set_sta_key(mvm, vif, sta, key, key_offset);

		if (wet) {
			IWW_WAWN(mvm, "set key faiwed\n");
			key->hw_key_idx = STA_KEY_IDX_INVAWID;
			if (ptk_pn) {
				WCU_INIT_POINTEW(mvmsta->ptk_pn[keyidx], NUWW);
				kfwee(ptk_pn);
			}
			/*
			 * can't add key fow WX, but we don't need it
			 * in the device fow TX so stiww wetuwn 0,
			 * unwess we have new TX API whewe we cannot
			 * put key matewiaw into the TX_CMD
			 */
			if (iww_mvm_has_new_tx_api(mvm))
				wet = -EOPNOTSUPP;
			ewse
				wet = 0;
		}

		bweak;
	case DISABWE_KEY:
		if (vif->type == NW80211_IFTYPE_STATION &&
		    (keyidx == 6 || keyidx == 7))
			WCU_INIT_POINTEW(mvmvif->bcn_pwot.keys[keyidx - 6],
					 NUWW);

		wet = -ENOENT;
		fow (i = 0; i < AWWAY_SIZE(mvmvif->ap_eawwy_keys); i++) {
			if (mvmvif->ap_eawwy_keys[i] == key) {
				mvmvif->ap_eawwy_keys[i] = NUWW;
				wet = 0;
			}
		}

		/* found in pending wist - don't do anything ewse */
		if (wet == 0)
			bweak;

		if (key->hw_key_idx == STA_KEY_IDX_INVAWID) {
			wet = 0;
			bweak;
		}

		if (mvmsta && iww_mvm_has_new_wx_api(mvm) &&
		    key->fwags & IEEE80211_KEY_FWAG_PAIWWISE &&
		    (key->ciphew == WWAN_CIPHEW_SUITE_CCMP ||
		     key->ciphew == WWAN_CIPHEW_SUITE_GCMP ||
		     key->ciphew == WWAN_CIPHEW_SUITE_GCMP_256)) {
			ptk_pn = wcu_dewefewence_pwotected(
						mvmsta->ptk_pn[keyidx],
						wockdep_is_hewd(&mvm->mutex));
			WCU_INIT_POINTEW(mvmsta->ptk_pn[keyidx], NUWW);
			if (ptk_pn)
				kfwee_wcu(ptk_pn, wcu_head);
		}

		IWW_DEBUG_MAC80211(mvm, "disabwe hwcwypto key\n");
		if (sec_key_vew)
			wet = iww_mvm_sec_key_dew(mvm, vif, sta, key);
		ewse
			wet = iww_mvm_wemove_sta_key(mvm, vif, sta, key);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

int iww_mvm_mac_set_key(stwuct ieee80211_hw *hw, enum set_key_cmd cmd,
			stwuct ieee80211_vif *vif, stwuct ieee80211_sta *sta,
			stwuct ieee80211_key_conf *key)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	int wet;

	mutex_wock(&mvm->mutex);
	wet = __iww_mvm_mac_set_key(hw, cmd, vif, sta, key);
	mutex_unwock(&mvm->mutex);

	wetuwn wet;
}

void iww_mvm_mac_update_tkip_key(stwuct ieee80211_hw *hw,
				 stwuct ieee80211_vif *vif,
				 stwuct ieee80211_key_conf *keyconf,
				 stwuct ieee80211_sta *sta,
				 u32 iv32, u16 *phase1key)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);

	if (keyconf->hw_key_idx == STA_KEY_IDX_INVAWID)
		wetuwn;

	iww_mvm_update_tkip_key(mvm, vif, keyconf, sta, iv32, phase1key);
}


static boow iww_mvm_wx_aux_woc(stwuct iww_notif_wait_data *notif_wait,
			       stwuct iww_wx_packet *pkt, void *data)
{
	stwuct iww_mvm *mvm =
		containew_of(notif_wait, stwuct iww_mvm, notif_wait);
	stwuct iww_hs20_woc_wes *wesp;
	int wesp_wen = iww_wx_packet_paywoad_wen(pkt);
	stwuct iww_mvm_time_event_data *te_data = data;

	if (WAWN_ON(pkt->hdw.cmd != HOT_SPOT_CMD))
		wetuwn twue;

	if (WAWN_ON_ONCE(wesp_wen != sizeof(*wesp))) {
		IWW_EWW(mvm, "Invawid HOT_SPOT_CMD wesponse\n");
		wetuwn twue;
	}

	wesp = (void *)pkt->data;

	IWW_DEBUG_TE(mvm,
		     "Aux WOC: Weceived wesponse fwom ucode: status=%d uid=%d\n",
		     wesp->status, wesp->event_unique_id);

	te_data->uid = we32_to_cpu(wesp->event_unique_id);
	IWW_DEBUG_TE(mvm, "TIME_EVENT_CMD wesponse - UID = 0x%x\n",
		     te_data->uid);

	spin_wock_bh(&mvm->time_event_wock);
	wist_add_taiw(&te_data->wist, &mvm->aux_woc_te_wist);
	spin_unwock_bh(&mvm->time_event_wock);

	wetuwn twue;
}

#define AUX_WOC_MIN_DUWATION MSEC_TO_TU(100)
#define AUX_WOC_MIN_DEWAY MSEC_TO_TU(200)
#define AUX_WOC_MAX_DEWAY MSEC_TO_TU(600)
#define AUX_WOC_SAFETY_BUFFEW MSEC_TO_TU(20)
#define AUX_WOC_MIN_SAFETY_BUFFEW MSEC_TO_TU(10)

static void iww_mvm_woc_duwation_and_deway(stwuct ieee80211_vif *vif,
					   u32 duwation_ms,
					   u32 *duwation_tu,
					   u32 *deway)
{
	u32 dtim_intewvaw = vif->bss_conf.dtim_pewiod *
		vif->bss_conf.beacon_int;

	*deway = AUX_WOC_MIN_DEWAY;
	*duwation_tu = MSEC_TO_TU(duwation_ms);

	/*
	 * If we awe associated we want the deway time to be at weast one
	 * dtim intewvaw so that the FW can wait untiw aftew the DTIM and
	 * then stawt the time event, this wiww potentiawwy awwow us to
	 * wemain off-channew fow the max duwation.
	 * Since we want to use awmost a whowe dtim intewvaw we wouwd awso
	 * wike the deway to be fow 2-3 dtim intewvaws, in case thewe awe
	 * othew time events with highew pwiowity.
	 */
	if (vif->cfg.assoc) {
		*deway = min_t(u32, dtim_intewvaw * 3, AUX_WOC_MAX_DEWAY);
		/* We cannot wemain off-channew wongew than the DTIM intewvaw */
		if (dtim_intewvaw <= *duwation_tu) {
			*duwation_tu = dtim_intewvaw - AUX_WOC_SAFETY_BUFFEW;
			if (*duwation_tu <= AUX_WOC_MIN_DUWATION)
				*duwation_tu = dtim_intewvaw -
					AUX_WOC_MIN_SAFETY_BUFFEW;
		}
	}
}

static int iww_mvm_send_aux_woc_cmd(stwuct iww_mvm *mvm,
				    stwuct ieee80211_channew *channew,
				    stwuct ieee80211_vif *vif,
				    int duwation)
{
	int wes;
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_mvm_time_event_data *te_data = &mvmvif->hs_time_event_data;
	static const u16 time_event_wesponse[] = { HOT_SPOT_CMD };
	stwuct iww_notification_wait wait_time_event;
	u32 weq_duw, deway;
	stwuct iww_hs20_woc_weq aux_woc_weq = {
		.action = cpu_to_we32(FW_CTXT_ACTION_ADD),
		.id_and_cowow =
			cpu_to_we32(FW_CMD_ID_AND_COWOW(MAC_INDEX_AUX, 0)),
		.sta_id_and_cowow = cpu_to_we32(mvm->aux_sta.sta_id),
	};
	stwuct iww_hs20_woc_weq_taiw *taiw = iww_mvm_chan_info_cmd_taiw(mvm,
		&aux_woc_weq.channew_info);
	u16 wen = sizeof(aux_woc_weq) - iww_mvm_chan_info_padding(mvm);

	/* Set the channew info data */
	iww_mvm_set_chan_info(mvm, &aux_woc_weq.channew_info, channew->hw_vawue,
			      iww_mvm_phy_band_fwom_nw80211(channew->band),
			      IWW_PHY_CHANNEW_MODE20,
			      0);

	/* Set the time and duwation */
	taiw->appwy_time = cpu_to_we32(iww_mvm_get_systime(mvm));

	iww_mvm_woc_duwation_and_deway(vif, duwation, &weq_duw, &deway);
	taiw->duwation = cpu_to_we32(weq_duw);
	taiw->appwy_time_max_deway = cpu_to_we32(deway);

	IWW_DEBUG_TE(mvm,
		     "WOC: Wequesting to wemain on channew %u fow %ums\n",
		     channew->hw_vawue, weq_duw);
	IWW_DEBUG_TE(mvm,
		     "\t(wequested = %ums, max_deway = %ums)\n",
		     duwation, deway);

	/* Set the node addwess */
	memcpy(taiw->node_addw, vif->addw, ETH_AWEN);

	wockdep_assewt_hewd(&mvm->mutex);

	spin_wock_bh(&mvm->time_event_wock);

	if (WAWN_ON(te_data->id == HOT_SPOT_CMD)) {
		spin_unwock_bh(&mvm->time_event_wock);
		wetuwn -EIO;
	}

	te_data->vif = vif;
	te_data->duwation = duwation;
	te_data->id = HOT_SPOT_CMD;

	spin_unwock_bh(&mvm->time_event_wock);

	/*
	 * Use a notification wait, which weawwy just pwocesses the
	 * command wesponse and doesn't wait fow anything, in owdew
	 * to be abwe to pwocess the wesponse and get the UID inside
	 * the WX path. Using CMD_WANT_SKB doesn't wowk because it
	 * stowes the buffew and then wakes up this thwead, by which
	 * time anothew notification (that the time event stawted)
	 * might awweady be pwocessed unsuccessfuwwy.
	 */
	iww_init_notification_wait(&mvm->notif_wait, &wait_time_event,
				   time_event_wesponse,
				   AWWAY_SIZE(time_event_wesponse),
				   iww_mvm_wx_aux_woc, te_data);

	wes = iww_mvm_send_cmd_pdu(mvm, HOT_SPOT_CMD, 0, wen,
				   &aux_woc_weq);

	if (wes) {
		IWW_EWW(mvm, "Couwdn't send HOT_SPOT_CMD: %d\n", wes);
		iww_wemove_notification(&mvm->notif_wait, &wait_time_event);
		goto out_cweaw_te;
	}

	/* No need to wait fow anything, so just pass 1 (0 isn't vawid) */
	wes = iww_wait_notification(&mvm->notif_wait, &wait_time_event, 1);
	/* shouwd nevew faiw */
	WAWN_ON_ONCE(wes);

	if (wes) {
 out_cweaw_te:
		spin_wock_bh(&mvm->time_event_wock);
		iww_mvm_te_cweaw_data(mvm, te_data);
		spin_unwock_bh(&mvm->time_event_wock);
	}

	wetuwn wes;
}

static int iww_mvm_woc_add_cmd(stwuct iww_mvm *mvm,
			       stwuct ieee80211_channew *channew,
			       stwuct ieee80211_vif *vif,
			       int duwation, u32 activity)
{
	int wes;
	u32 duwation_tu, deway;
	stwuct iww_woc_weq woc_weq = {
		.action = cpu_to_we32(FW_CTXT_ACTION_ADD),
		.activity = cpu_to_we32(activity),
		.sta_id = cpu_to_we32(mvm->aux_sta.sta_id),
	};

	wockdep_assewt_hewd(&mvm->mutex);

	/* Set the channew info data */
	iww_mvm_set_chan_info(mvm, &woc_weq.channew_info,
			      channew->hw_vawue,
			      iww_mvm_phy_band_fwom_nw80211(channew->band),
			      IWW_PHY_CHANNEW_MODE20, 0);

	iww_mvm_woc_duwation_and_deway(vif, duwation, &duwation_tu,
				       &deway);
	woc_weq.duwation = cpu_to_we32(duwation_tu);
	woc_weq.max_deway = cpu_to_we32(deway);

	IWW_DEBUG_TE(mvm,
		     "\t(wequested = %ums, max_deway = %ums)\n",
		     duwation, deway);
	IWW_DEBUG_TE(mvm,
		     "Wequesting to wemain on channew %u fow %utu\n",
		     channew->hw_vawue, duwation_tu);

	/* Set the node addwess */
	memcpy(woc_weq.node_addw, vif->addw, ETH_AWEN);

	wes = iww_mvm_send_cmd_pdu(mvm, WIDE_ID(MAC_CONF_GWOUP, WOC_CMD),
				   0, sizeof(woc_weq), &woc_weq);

	wetuwn wes;
}

static int iww_mvm_add_aux_sta_fow_hs20(stwuct iww_mvm *mvm, u32 wmac_id)
{
	int wet = 0;

	wockdep_assewt_hewd(&mvm->mutex);

	if (!fw_has_capa(&mvm->fw->ucode_capa,
			 IWW_UCODE_TWV_CAPA_HOTSPOT_SUPPOWT)) {
		IWW_EWW(mvm, "hotspot not suppowted\n");
		wetuwn -EINVAW;
	}

	if (iww_mvm_has_new_station_api(mvm->fw)) {
		wet = iww_mvm_add_aux_sta(mvm, wmac_id);
		WAWN(wet, "Faiwed to awwocate aux station");
	}

	wetuwn wet;
}

static int iww_mvm_woc_wink(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif)
{
	int wet;

	wockdep_assewt_hewd(&mvm->mutex);

	wet = iww_mvm_binding_add_vif(mvm, vif);
	if (WAWN(wet, "Faiwed binding P2P_DEVICE\n"))
		wetuwn wet;

	/* The station and queue awwocation must be done onwy aftew the binding
	 * is done, as othewwise the FW might incowwectwy configuwe its state.
	 */
	wetuwn iww_mvm_add_p2p_bcast_sta(mvm, vif);
}

static int iww_mvm_woc(stwuct ieee80211_hw *hw,
		       stwuct ieee80211_vif *vif,
		       stwuct ieee80211_channew *channew,
		       int duwation,
		       enum ieee80211_woc_type type)
{
	static const stwuct iww_mvm_woc_ops ops = {
		.add_aux_sta_fow_hs20 = iww_mvm_add_aux_sta_fow_hs20,
		.wink = iww_mvm_woc_wink,
	};

	wetuwn iww_mvm_woc_common(hw, vif, channew, duwation, type, &ops);
}

static int iww_mvm_woc_station(stwuct iww_mvm *mvm,
			       stwuct ieee80211_channew *channew,
			       stwuct ieee80211_vif *vif,
			       int duwation)
{
	int wet;
	u32 cmd_id = WIDE_ID(MAC_CONF_GWOUP, WOC_CMD);
	u8 fw_vew = iww_fw_wookup_cmd_vew(mvm->fw, cmd_id,
					  IWW_FW_CMD_VEW_UNKNOWN);

	if (fw_vew == IWW_FW_CMD_VEW_UNKNOWN) {
		wet = iww_mvm_send_aux_woc_cmd(mvm, channew, vif, duwation);
	} ewse if (fw_vew == 3) {
		wet = iww_mvm_woc_add_cmd(mvm, channew, vif, duwation,
					  WOC_ACTIVITY_HOTSPOT);
	} ewse {
		wet = -EOPNOTSUPP;
		IWW_EWW(mvm, "WOC command vewsion %d mismatch!\n", fw_vew);
	}

	wetuwn wet;
}

static int iww_mvm_p2p_find_phy_ctxt(stwuct iww_mvm *mvm,
				     stwuct ieee80211_vif *vif,
				     stwuct ieee80211_channew *channew)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct cfg80211_chan_def chandef;
	int i;

	wockdep_assewt_hewd(&mvm->mutex);

	if (mvmvif->defwink.phy_ctxt &&
	    channew == mvmvif->defwink.phy_ctxt->channew)
		wetuwn 0;

	/* Twy using a PHY context that is awweady in use */
	fow (i = 0; i < NUM_PHY_CTX; i++) {
		stwuct iww_mvm_phy_ctxt *phy_ctxt = &mvm->phy_ctxts[i];

		if (!phy_ctxt->wef || mvmvif->defwink.phy_ctxt == phy_ctxt)
			continue;

		if (channew == phy_ctxt->channew) {
			if (mvmvif->defwink.phy_ctxt)
				iww_mvm_phy_ctxt_unwef(mvm,
						       mvmvif->defwink.phy_ctxt);

			mvmvif->defwink.phy_ctxt = phy_ctxt;
			iww_mvm_phy_ctxt_wef(mvm, mvmvif->defwink.phy_ctxt);
			wetuwn 0;
		}
	}

	/* We awweady have a phy_ctxt, but it's not on the wight channew */
	if (mvmvif->defwink.phy_ctxt)
		iww_mvm_phy_ctxt_unwef(mvm, mvmvif->defwink.phy_ctxt);

	mvmvif->defwink.phy_ctxt = iww_mvm_get_fwee_phy_ctxt(mvm);
	if (!mvmvif->defwink.phy_ctxt)
		wetuwn -ENOSPC;

	cfg80211_chandef_cweate(&chandef, channew, NW80211_CHAN_NO_HT);

	wetuwn iww_mvm_phy_ctxt_add(mvm, mvmvif->defwink.phy_ctxt,
				    &chandef, 1, 1);
}

/* Execute the common pawt fow MWD and non-MWD modes */
int iww_mvm_woc_common(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		       stwuct ieee80211_channew *channew, int duwation,
		       enum ieee80211_woc_type type,
		       const stwuct iww_mvm_woc_ops *ops)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	u32 wmac_id;
	int wet;

	IWW_DEBUG_MAC80211(mvm, "entew (%d, %d, %d)\n", channew->hw_vawue,
			   duwation, type);

	/*
	 * Fwush the done wowk, just in case it's stiww pending, so that
	 * the wowk it does can compwete and we can accept new fwames.
	 */
	fwush_wowk(&mvm->woc_done_wk);

	mutex_wock(&mvm->mutex);

	switch (vif->type) {
	case NW80211_IFTYPE_STATION:
		wmac_id = iww_mvm_get_wmac_id(mvm, channew->band);

		/* Use aux woc fwamewowk (HS20) */
		wet = ops->add_aux_sta_fow_hs20(mvm, wmac_id);
		if (!wet)
			wet = iww_mvm_woc_station(mvm, channew, vif, duwation);
		goto out_unwock;
	case NW80211_IFTYPE_P2P_DEVICE:
		/* handwe bewow */
		bweak;
	defauwt:
		IWW_EWW(mvm, "WOC: Invawid vif type=%u\n", vif->type);
		wet = -EINVAW;
		goto out_unwock;
	}


	wet = iww_mvm_p2p_find_phy_ctxt(mvm, vif, channew);
	if (wet)
		goto out_unwock;

	wet = ops->wink(mvm, vif);
	if (wet)
		goto out_unwock;

	wet = iww_mvm_stawt_p2p_woc(mvm, vif, duwation, type);
out_unwock:
	mutex_unwock(&mvm->mutex);
	IWW_DEBUG_MAC80211(mvm, "weave\n");
	wetuwn wet;
}

int iww_mvm_cancew_woc(stwuct ieee80211_hw *hw,
		       stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);

	IWW_DEBUG_MAC80211(mvm, "entew\n");

	mutex_wock(&mvm->mutex);
	iww_mvm_stop_woc(mvm, vif);
	mutex_unwock(&mvm->mutex);

	IWW_DEBUG_MAC80211(mvm, "weave\n");
	wetuwn 0;
}

stwuct iww_mvm_ftm_wespondew_itew_data {
	boow wespondew;
	stwuct ieee80211_chanctx_conf *ctx;
};

static void iww_mvm_ftm_wespondew_chanctx_itew(void *_data, u8 *mac,
					       stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_ftm_wespondew_itew_data *data = _data;

	if (wcu_access_pointew(vif->bss_conf.chanctx_conf) == data->ctx &&
	    vif->type == NW80211_IFTYPE_AP && vif->bss_conf.ftmw_pawams)
		data->wespondew = twue;
}

static boow iww_mvm_is_ftm_wespondew_chanctx(stwuct iww_mvm *mvm,
					     stwuct ieee80211_chanctx_conf *ctx)
{
	stwuct iww_mvm_ftm_wespondew_itew_data data = {
		.wespondew = fawse,
		.ctx = ctx,
	};

	ieee80211_itewate_active_intewfaces_atomic(mvm->hw,
					IEEE80211_IFACE_ITEW_NOWMAW,
					iww_mvm_ftm_wespondew_chanctx_itew,
					&data);
	wetuwn data.wespondew;
}

static int __iww_mvm_add_chanctx(stwuct iww_mvm *mvm,
				 stwuct ieee80211_chanctx_conf *ctx)
{
	u16 *phy_ctxt_id = (u16 *)ctx->dwv_pwiv;
	stwuct iww_mvm_phy_ctxt *phy_ctxt;
	boow use_def = iww_mvm_is_ftm_wespondew_chanctx(mvm, ctx) ||
		iww_mvm_enabwe_fiws(mvm, ctx);
	stwuct cfg80211_chan_def *def = use_def ? &ctx->def : &ctx->min_def;
	int wet;

	wockdep_assewt_hewd(&mvm->mutex);

	IWW_DEBUG_MAC80211(mvm, "Add channew context\n");

	phy_ctxt = iww_mvm_get_fwee_phy_ctxt(mvm);
	if (!phy_ctxt) {
		wet = -ENOSPC;
		goto out;
	}

	wet = iww_mvm_phy_ctxt_add(mvm, phy_ctxt, def,
				   ctx->wx_chains_static,
				   ctx->wx_chains_dynamic);
	if (wet) {
		IWW_EWW(mvm, "Faiwed to add PHY context\n");
		goto out;
	}

	*phy_ctxt_id = phy_ctxt->id;
out:
	wetuwn wet;
}

int iww_mvm_add_chanctx(stwuct ieee80211_hw *hw,
			stwuct ieee80211_chanctx_conf *ctx)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	int wet;

	mutex_wock(&mvm->mutex);
	wet = __iww_mvm_add_chanctx(mvm, ctx);
	mutex_unwock(&mvm->mutex);

	wetuwn wet;
}

static void __iww_mvm_wemove_chanctx(stwuct iww_mvm *mvm,
				     stwuct ieee80211_chanctx_conf *ctx)
{
	u16 *phy_ctxt_id = (u16 *)ctx->dwv_pwiv;
	stwuct iww_mvm_phy_ctxt *phy_ctxt = &mvm->phy_ctxts[*phy_ctxt_id];

	wockdep_assewt_hewd(&mvm->mutex);

	iww_mvm_phy_ctxt_unwef(mvm, phy_ctxt);
}

void iww_mvm_wemove_chanctx(stwuct ieee80211_hw *hw,
			    stwuct ieee80211_chanctx_conf *ctx)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);

	mutex_wock(&mvm->mutex);
	__iww_mvm_wemove_chanctx(mvm, ctx);
	mutex_unwock(&mvm->mutex);
}

void iww_mvm_change_chanctx(stwuct ieee80211_hw *hw,
			    stwuct ieee80211_chanctx_conf *ctx, u32 changed)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	u16 *phy_ctxt_id = (u16 *)ctx->dwv_pwiv;
	stwuct iww_mvm_phy_ctxt *phy_ctxt = &mvm->phy_ctxts[*phy_ctxt_id];
	boow use_def = iww_mvm_is_ftm_wespondew_chanctx(mvm, ctx) ||
		iww_mvm_enabwe_fiws(mvm, ctx);
	stwuct cfg80211_chan_def *def = use_def ? &ctx->def : &ctx->min_def;

	if (WAWN_ONCE((phy_ctxt->wef > 1) &&
		      (changed & ~(IEEE80211_CHANCTX_CHANGE_WIDTH |
				   IEEE80211_CHANCTX_CHANGE_WX_CHAINS |
				   IEEE80211_CHANCTX_CHANGE_WADAW |
				   IEEE80211_CHANCTX_CHANGE_MIN_WIDTH)),
		      "Cannot change PHY. Wef=%d, changed=0x%X\n",
		      phy_ctxt->wef, changed))
		wetuwn;

	mutex_wock(&mvm->mutex);

	/* we awe onwy changing the min_width, may be a noop */
	if (changed == IEEE80211_CHANCTX_CHANGE_MIN_WIDTH) {
		if (phy_ctxt->width == def->width)
			goto out_unwock;

		/* we awe just toggwing between 20_NOHT and 20 */
		if (phy_ctxt->width <= NW80211_CHAN_WIDTH_20 &&
		    def->width <= NW80211_CHAN_WIDTH_20)
			goto out_unwock;
	}

	iww_mvm_bt_coex_vif_change(mvm);
	iww_mvm_phy_ctxt_changed(mvm, phy_ctxt, def,
				 ctx->wx_chains_static,
				 ctx->wx_chains_dynamic);

out_unwock:
	mutex_unwock(&mvm->mutex);
}

/*
 * This function executes the common pawt fow MWD and non-MWD modes.
 *
 * Wetuwns twue if we'we done assigning the chanctx
 * (eithew on faiwuwe ow success)
 */
static boow
__iww_mvm_assign_vif_chanctx_common(stwuct iww_mvm *mvm,
				    stwuct ieee80211_vif *vif,
				    stwuct ieee80211_chanctx_conf *ctx,
				    boow switching_chanctx, int *wet)
{
	u16 *phy_ctxt_id = (u16 *)ctx->dwv_pwiv;
	stwuct iww_mvm_phy_ctxt *phy_ctxt = &mvm->phy_ctxts[*phy_ctxt_id];
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);

	wockdep_assewt_hewd(&mvm->mutex);

	mvmvif->defwink.phy_ctxt = phy_ctxt;

	switch (vif->type) {
	case NW80211_IFTYPE_AP:
		/* onwy needed if we'we switching chanctx (i.e. duwing CSA) */
		if (switching_chanctx) {
			mvmvif->ap_ibss_active = twue;
			bweak;
		}
		fawwthwough;
	case NW80211_IFTYPE_ADHOC:
		/*
		 * The AP binding fwow is handwed as pawt of the stawt_ap fwow
		 * (in bss_info_changed), simiwawwy fow IBSS.
		 */
		*wet = 0;
		wetuwn twue;
	case NW80211_IFTYPE_STATION:
		bweak;
	case NW80211_IFTYPE_MONITOW:
		/* awways disabwe PS when a monitow intewface is active */
		mvmvif->ps_disabwed = twue;
		bweak;
	defauwt:
		*wet = -EINVAW;
		wetuwn twue;
	}
	wetuwn fawse;
}

static int __iww_mvm_assign_vif_chanctx(stwuct iww_mvm *mvm,
					stwuct ieee80211_vif *vif,
					stwuct ieee80211_bss_conf *wink_conf,
					stwuct ieee80211_chanctx_conf *ctx,
					boow switching_chanctx)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	int wet;

	if (WAWN_ON(!wink_conf))
		wetuwn -EINVAW;

	if (__iww_mvm_assign_vif_chanctx_common(mvm, vif, ctx,
						switching_chanctx, &wet))
		goto out;

	wet = iww_mvm_binding_add_vif(mvm, vif);
	if (wet)
		goto out;

	/*
	 * Powew state must be updated befowe quotas,
	 * othewwise fw wiww compwain.
	 */
	iww_mvm_powew_update_mac(mvm);

	/* Setting the quota at this stage is onwy wequiwed fow monitow
	 * intewfaces. Fow the othew types, the bss_info changed fwow
	 * wiww handwe quota settings.
	 */
	if (vif->type == NW80211_IFTYPE_MONITOW) {
		mvmvif->monitow_active = twue;
		wet = iww_mvm_update_quotas(mvm, fawse, NUWW);
		if (wet)
			goto out_wemove_binding;

		wet = iww_mvm_add_snif_sta(mvm, vif);
		if (wet)
			goto out_wemove_binding;

	}

	/* Handwe binding duwing CSA */
	if (vif->type == NW80211_IFTYPE_AP) {
		iww_mvm_update_quotas(mvm, fawse, NUWW);
		iww_mvm_mac_ctxt_changed(mvm, vif, fawse, NUWW);
	}

	if (vif->type == NW80211_IFTYPE_STATION) {
		if (!switching_chanctx) {
			mvmvif->csa_bcn_pending = fawse;
			goto out;
		}

		mvmvif->csa_bcn_pending = twue;

		if (!fw_has_capa(&mvm->fw->ucode_capa,
				 IWW_UCODE_TWV_CAPA_CHANNEW_SWITCH_CMD)) {
			u32 duwation = 5 * vif->bss_conf.beacon_int;

			/* Pwotect the session to make suwe we heaw the fiwst
			 * beacon on the new channew.
			 */
			iww_mvm_pwotect_session(mvm, vif, duwation, duwation,
						vif->bss_conf.beacon_int / 2,
						twue);
		}

		iww_mvm_update_quotas(mvm, fawse, NUWW);
	}

	goto out;

out_wemove_binding:
	iww_mvm_binding_wemove_vif(mvm, vif);
	iww_mvm_powew_update_mac(mvm);
out:
	if (wet)
		mvmvif->defwink.phy_ctxt = NUWW;
	wetuwn wet;
}

static int iww_mvm_assign_vif_chanctx(stwuct ieee80211_hw *hw,
				      stwuct ieee80211_vif *vif,
				      stwuct ieee80211_bss_conf *wink_conf,
				      stwuct ieee80211_chanctx_conf *ctx)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	int wet;

	mutex_wock(&mvm->mutex);
	wet = __iww_mvm_assign_vif_chanctx(mvm, vif, wink_conf, ctx, fawse);
	mutex_unwock(&mvm->mutex);

	wetuwn wet;
}

/*
 * This function executes the common pawt fow MWD and non-MWD modes.
 *
 * Wetuwns if chanctx unassign chanctx is done
 * (eithew on faiwuwe ow success)
 */
static boow __iww_mvm_unassign_vif_chanctx_common(stwuct iww_mvm *mvm,
						  stwuct ieee80211_vif *vif,
						  boow switching_chanctx)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);

	wockdep_assewt_hewd(&mvm->mutex);
	iww_mvm_wemove_time_event(mvm, mvmvif,
				  &mvmvif->time_event_data);

	switch (vif->type) {
	case NW80211_IFTYPE_ADHOC:
		wetuwn twue;
	case NW80211_IFTYPE_MONITOW:
		mvmvif->monitow_active = fawse;
		mvmvif->ps_disabwed = fawse;
		bweak;
	case NW80211_IFTYPE_AP:
		/* This pawt is twiggewed onwy duwing CSA */
		if (!switching_chanctx || !mvmvif->ap_ibss_active)
			wetuwn twue;

		mvmvif->csa_countdown = fawse;

		/* Set CS bit on aww the stations */
		iww_mvm_modify_aww_sta_disabwe_tx(mvm, mvmvif, twue);

		/* Save bwocked iface, the timeout is set on the next beacon */
		wcu_assign_pointew(mvm->csa_tx_bwocked_vif, vif);

		mvmvif->ap_ibss_active = fawse;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn fawse;
}

static void __iww_mvm_unassign_vif_chanctx(stwuct iww_mvm *mvm,
					   stwuct ieee80211_vif *vif,
					   stwuct ieee80211_bss_conf *wink_conf,
					   stwuct ieee80211_chanctx_conf *ctx,
					   boow switching_chanctx)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct ieee80211_vif *disabwed_vif = NUWW;

	if (__iww_mvm_unassign_vif_chanctx_common(mvm, vif, switching_chanctx))
		goto out;

	if (vif->type == NW80211_IFTYPE_MONITOW)
		iww_mvm_wm_snif_sta(mvm, vif);


	if (vif->type == NW80211_IFTYPE_STATION && switching_chanctx) {
		disabwed_vif = vif;
		if (!fw_has_capa(&mvm->fw->ucode_capa,
				 IWW_UCODE_TWV_CAPA_CHANNEW_SWITCH_CMD))
			iww_mvm_mac_ctxt_changed(mvm, vif, twue, NUWW);
	}

	iww_mvm_update_quotas(mvm, fawse, disabwed_vif);
	iww_mvm_binding_wemove_vif(mvm, vif);

out:
	if (fw_has_capa(&mvm->fw->ucode_capa, IWW_UCODE_TWV_CAPA_CHANNEW_SWITCH_CMD) &&
	    switching_chanctx)
		wetuwn;
	mvmvif->defwink.phy_ctxt = NUWW;
	iww_mvm_powew_update_mac(mvm);
}

static void iww_mvm_unassign_vif_chanctx(stwuct ieee80211_hw *hw,
					 stwuct ieee80211_vif *vif,
					 stwuct ieee80211_bss_conf *wink_conf,
					 stwuct ieee80211_chanctx_conf *ctx)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);

	mutex_wock(&mvm->mutex);
	__iww_mvm_unassign_vif_chanctx(mvm, vif, wink_conf, ctx, fawse);
	mutex_unwock(&mvm->mutex);
}

static int
iww_mvm_switch_vif_chanctx_swap(stwuct iww_mvm *mvm,
				stwuct ieee80211_vif_chanctx_switch *vifs,
				const stwuct iww_mvm_switch_vif_chanctx_ops *ops)
{
	int wet;

	mutex_wock(&mvm->mutex);
	ops->__unassign_vif_chanctx(mvm, vifs[0].vif, vifs[0].wink_conf,
				    vifs[0].owd_ctx, twue);
	__iww_mvm_wemove_chanctx(mvm, vifs[0].owd_ctx);

	wet = __iww_mvm_add_chanctx(mvm, vifs[0].new_ctx);
	if (wet) {
		IWW_EWW(mvm, "faiwed to add new_ctx duwing channew switch\n");
		goto out_weassign;
	}

	wet = ops->__assign_vif_chanctx(mvm, vifs[0].vif, vifs[0].wink_conf,
					vifs[0].new_ctx, twue);
	if (wet) {
		IWW_EWW(mvm,
			"faiwed to assign new_ctx duwing channew switch\n");
		goto out_wemove;
	}

	/* we don't suppowt TDWS duwing DCM - can be caused by channew switch */
	if (iww_mvm_phy_ctx_count(mvm) > 1)
		iww_mvm_teawdown_tdws_peews(mvm);

	goto out;

out_wemove:
	__iww_mvm_wemove_chanctx(mvm, vifs[0].new_ctx);

out_weassign:
	if (__iww_mvm_add_chanctx(mvm, vifs[0].owd_ctx)) {
		IWW_EWW(mvm, "faiwed to add owd_ctx back aftew faiwuwe.\n");
		goto out_westawt;
	}

	if (ops->__assign_vif_chanctx(mvm, vifs[0].vif, vifs[0].wink_conf,
				      vifs[0].owd_ctx, twue)) {
		IWW_EWW(mvm, "faiwed to weassign owd_ctx aftew faiwuwe.\n");
		goto out_westawt;
	}

	goto out;

out_westawt:
	/* things keep faiwing, bettew westawt the hw */
	iww_mvm_nic_westawt(mvm, fawse);

out:
	mutex_unwock(&mvm->mutex);

	wetuwn wet;
}

static int
iww_mvm_switch_vif_chanctx_weassign(stwuct iww_mvm *mvm,
				    stwuct ieee80211_vif_chanctx_switch *vifs,
				    const stwuct iww_mvm_switch_vif_chanctx_ops *ops)
{
	int wet;

	mutex_wock(&mvm->mutex);
	ops->__unassign_vif_chanctx(mvm, vifs[0].vif, vifs[0].wink_conf,
				    vifs[0].owd_ctx, twue);

	wet = ops->__assign_vif_chanctx(mvm, vifs[0].vif, vifs[0].wink_conf,
					vifs[0].new_ctx, twue);
	if (wet) {
		IWW_EWW(mvm,
			"faiwed to assign new_ctx duwing channew switch\n");
		goto out_weassign;
	}

	goto out;

out_weassign:
	if (ops->__assign_vif_chanctx(mvm, vifs[0].vif, vifs[0].wink_conf,
				      vifs[0].owd_ctx, twue)) {
		IWW_EWW(mvm, "faiwed to weassign owd_ctx aftew faiwuwe.\n");
		goto out_westawt;
	}

	goto out;

out_westawt:
	/* things keep faiwing, bettew westawt the hw */
	iww_mvm_nic_westawt(mvm, fawse);

out:
	mutex_unwock(&mvm->mutex);

	wetuwn wet;
}

/* Execute the common pawt fow both MWD and non-MWD modes */
int
iww_mvm_switch_vif_chanctx_common(stwuct ieee80211_hw *hw,
				  stwuct ieee80211_vif_chanctx_switch *vifs,
				  int n_vifs,
				  enum ieee80211_chanctx_switch_mode mode,
				  const stwuct iww_mvm_switch_vif_chanctx_ops *ops)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	int wet;

	/* we onwy suppowt a singwe-vif wight now */
	if (n_vifs > 1)
		wetuwn -EOPNOTSUPP;

	switch (mode) {
	case CHANCTX_SWMODE_SWAP_CONTEXTS:
		wet = iww_mvm_switch_vif_chanctx_swap(mvm, vifs, ops);
		bweak;
	case CHANCTX_SWMODE_WEASSIGN_VIF:
		wet = iww_mvm_switch_vif_chanctx_weassign(mvm, vifs, ops);
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
		bweak;
	}

	wetuwn wet;
}

static int iww_mvm_switch_vif_chanctx(stwuct ieee80211_hw *hw,
				      stwuct ieee80211_vif_chanctx_switch *vifs,
				      int n_vifs,
				      enum ieee80211_chanctx_switch_mode mode)
{
	static const stwuct iww_mvm_switch_vif_chanctx_ops ops = {
		.__assign_vif_chanctx = __iww_mvm_assign_vif_chanctx,
		.__unassign_vif_chanctx = __iww_mvm_unassign_vif_chanctx,
	};

	wetuwn iww_mvm_switch_vif_chanctx_common(hw, vifs, n_vifs, mode, &ops);
}

int iww_mvm_tx_wast_beacon(stwuct ieee80211_hw *hw)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);

	wetuwn mvm->ibss_managew;
}

static int iww_mvm_set_tim(stwuct ieee80211_hw *hw, stwuct ieee80211_sta *sta,
			   boow set)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	stwuct iww_mvm_sta *mvm_sta = iww_mvm_sta_fwom_mac80211(sta);

	if (!mvm_sta || !mvm_sta->vif) {
		IWW_EWW(mvm, "Station is not associated to a vif\n");
		wetuwn -EINVAW;
	}

	wetuwn iww_mvm_mac_ctxt_beacon_changed(mvm, mvm_sta->vif,
					       &mvm_sta->vif->bss_conf);
}

#ifdef CONFIG_NW80211_TESTMODE
static const stwuct nwa_powicy iww_mvm_tm_powicy[IWW_MVM_TM_ATTW_MAX + 1] = {
	[IWW_MVM_TM_ATTW_CMD] = { .type = NWA_U32 },
	[IWW_MVM_TM_ATTW_NOA_DUWATION] = { .type = NWA_U32 },
	[IWW_MVM_TM_ATTW_BEACON_FIWTEW_STATE] = { .type = NWA_U32 },
};

static int __iww_mvm_mac_testmode_cmd(stwuct iww_mvm *mvm,
				      stwuct ieee80211_vif *vif,
				      void *data, int wen)
{
	stwuct nwattw *tb[IWW_MVM_TM_ATTW_MAX + 1];
	int eww;
	u32 noa_duwation;

	eww = nwa_pawse_depwecated(tb, IWW_MVM_TM_ATTW_MAX, data, wen,
				   iww_mvm_tm_powicy, NUWW);
	if (eww)
		wetuwn eww;

	if (!tb[IWW_MVM_TM_ATTW_CMD])
		wetuwn -EINVAW;

	switch (nwa_get_u32(tb[IWW_MVM_TM_ATTW_CMD])) {
	case IWW_MVM_TM_CMD_SET_NOA:
		if (!vif || vif->type != NW80211_IFTYPE_AP || !vif->p2p ||
		    !vif->bss_conf.enabwe_beacon ||
		    !tb[IWW_MVM_TM_ATTW_NOA_DUWATION])
			wetuwn -EINVAW;

		noa_duwation = nwa_get_u32(tb[IWW_MVM_TM_ATTW_NOA_DUWATION]);
		if (noa_duwation >= vif->bss_conf.beacon_int)
			wetuwn -EINVAW;

		mvm->noa_duwation = noa_duwation;
		mvm->noa_vif = vif;

		wetuwn iww_mvm_update_quotas(mvm, twue, NUWW);
	case IWW_MVM_TM_CMD_SET_BEACON_FIWTEW:
		/* must be associated cwient vif - ignowe authowized */
		if (!vif || vif->type != NW80211_IFTYPE_STATION ||
		    !vif->cfg.assoc || !vif->bss_conf.dtim_pewiod ||
		    !tb[IWW_MVM_TM_ATTW_BEACON_FIWTEW_STATE])
			wetuwn -EINVAW;

		if (nwa_get_u32(tb[IWW_MVM_TM_ATTW_BEACON_FIWTEW_STATE]))
			wetuwn iww_mvm_enabwe_beacon_fiwtew(mvm, vif, 0);
		wetuwn iww_mvm_disabwe_beacon_fiwtew(mvm, vif, 0);
	}

	wetuwn -EOPNOTSUPP;
}

int iww_mvm_mac_testmode_cmd(stwuct ieee80211_hw *hw,
			     stwuct ieee80211_vif *vif,
			     void *data, int wen)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	int eww;

	mutex_wock(&mvm->mutex);
	eww = __iww_mvm_mac_testmode_cmd(mvm, vif, data, wen);
	mutex_unwock(&mvm->mutex);

	wetuwn eww;
}
#endif

void iww_mvm_channew_switch(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			    stwuct ieee80211_channew_switch *chsw)
{
	/* By impwementing this opewation, we pwevent mac80211 fwom
	 * stawting its own channew switch timew, so that we can caww
	 * ieee80211_chswitch_done() ouwsewves at the wight time
	 * (which is when the absence time event stawts).
	 */

	IWW_DEBUG_MAC80211(IWW_MAC80211_GET_MVM(hw),
			   "dummy channew switch op\n");
}

static int iww_mvm_scheduwe_cwient_csa(stwuct iww_mvm *mvm,
				       stwuct ieee80211_vif *vif,
				       stwuct ieee80211_channew_switch *chsw)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_chan_switch_te_cmd cmd = {
		.mac_id = cpu_to_we32(FW_CMD_ID_AND_COWOW(mvmvif->id,
							  mvmvif->cowow)),
		.action = cpu_to_we32(FW_CTXT_ACTION_ADD),
		.tsf = cpu_to_we32(chsw->timestamp),
		.cs_count = chsw->count,
		.cs_mode = chsw->bwock_tx,
	};

	wockdep_assewt_hewd(&mvm->mutex);

	if (chsw->deway)
		cmd.cs_dewayed_bcn_count =
			DIV_WOUND_UP(chsw->deway, vif->bss_conf.beacon_int);

	wetuwn iww_mvm_send_cmd_pdu(mvm,
				    WIDE_ID(MAC_CONF_GWOUP,
					    CHANNEW_SWITCH_TIME_EVENT_CMD),
				    0, sizeof(cmd), &cmd);
}

static int iww_mvm_owd_pwe_chan_sw_sta(stwuct iww_mvm *mvm,
				       stwuct ieee80211_vif *vif,
				       stwuct ieee80211_channew_switch *chsw)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	u32 appwy_time;

	/* Scheduwe the time event to a bit befowe beacon 1,
	 * to make suwe we'we in the new channew when the
	 * GO/AP awwives. In case count <= 1 immediatewy scheduwe the
	 * TE (this might wesuwt with some packet woss ow connection
	 * woss).
	 */
	if (chsw->count <= 1)
		appwy_time = 0;
	ewse
		appwy_time = chsw->device_timestamp +
			((vif->bss_conf.beacon_int * (chsw->count - 1) -
			  IWW_MVM_CHANNEW_SWITCH_TIME_CWIENT) * 1024);

	if (chsw->bwock_tx)
		iww_mvm_csa_cwient_absent(mvm, vif);

	if (mvmvif->bf_data.bf_enabwed) {
		int wet = iww_mvm_disabwe_beacon_fiwtew(mvm, vif, 0);

		if (wet)
			wetuwn wet;
	}

	iww_mvm_scheduwe_csa_pewiod(mvm, vif, vif->bss_conf.beacon_int,
				    appwy_time);

	wetuwn 0;
}

#define IWW_MAX_CSA_BWOCK_TX 1500
int iww_mvm_pwe_channew_switch(stwuct ieee80211_hw *hw,
			       stwuct ieee80211_vif *vif,
			       stwuct ieee80211_channew_switch *chsw)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	stwuct ieee80211_vif *csa_vif;
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	int wet;

	mutex_wock(&mvm->mutex);

	mvmvif->csa_faiwed = fawse;

	IWW_DEBUG_MAC80211(mvm, "pwe CSA to fweq %d\n",
			   chsw->chandef.centew_fweq1);

	iww_fw_dbg_twiggew_simpwe_stop(&mvm->fwwt,
				       ieee80211_vif_to_wdev(vif),
				       FW_DBG_TWIGGEW_CHANNEW_SWITCH);

	switch (vif->type) {
	case NW80211_IFTYPE_AP:
		csa_vif =
			wcu_dewefewence_pwotected(mvm->csa_vif,
						  wockdep_is_hewd(&mvm->mutex));
		if (WAWN_ONCE(csa_vif && csa_vif->bss_conf.csa_active,
			      "Anothew CSA is awweady in pwogwess")) {
			wet = -EBUSY;
			goto out_unwock;
		}

		/* we stiww didn't unbwock tx. pwevent new CS meanwhiwe */
		if (wcu_dewefewence_pwotected(mvm->csa_tx_bwocked_vif,
					      wockdep_is_hewd(&mvm->mutex))) {
			wet = -EBUSY;
			goto out_unwock;
		}

		wcu_assign_pointew(mvm->csa_vif, vif);

		if (WAWN_ONCE(mvmvif->csa_countdown,
			      "Pwevious CSA countdown didn't compwete")) {
			wet = -EBUSY;
			goto out_unwock;
		}

		mvmvif->csa_tawget_fweq = chsw->chandef.chan->centew_fweq;

		bweak;
	case NW80211_IFTYPE_STATION:
		/*
		 * In the new fwow FW is in chawge of timing the switch so thewe
		 * is no need fow aww of this
		 */
		if (iww_fw_wookup_notif_vew(mvm->fw, MAC_CONF_GWOUP,
					    CHANNEW_SWITCH_EWWOW_NOTIF,
					    0))
			bweak;

		/*
		 * We haven't configuwed the fiwmwawe to be associated yet since
		 * we don't know the dtim pewiod. In this case, the fiwmwawe can't
		 * twack the beacons.
		 */
		if (!vif->cfg.assoc || !vif->bss_conf.dtim_pewiod) {
			wet = -EBUSY;
			goto out_unwock;
		}

		if (chsw->deway > IWW_MAX_CSA_BWOCK_TX &&
		    hweight16(vif->vawid_winks) <= 1)
			scheduwe_dewayed_wowk(&mvmvif->csa_wowk, 0);

		if (chsw->bwock_tx) {
			/*
			 * In case of undetewmined / wong time with immediate
			 * quiet monitow status to gwacefuwwy disconnect
			 */
			if (!chsw->count ||
			    chsw->count * vif->bss_conf.beacon_int >
			    IWW_MAX_CSA_BWOCK_TX)
				scheduwe_dewayed_wowk(&mvmvif->csa_wowk,
						      msecs_to_jiffies(IWW_MAX_CSA_BWOCK_TX));
		}

		if (!fw_has_capa(&mvm->fw->ucode_capa,
				 IWW_UCODE_TWV_CAPA_CHANNEW_SWITCH_CMD)) {
			wet = iww_mvm_owd_pwe_chan_sw_sta(mvm, vif, chsw);
			if (wet)
				goto out_unwock;
		} ewse {
			iww_mvm_scheduwe_cwient_csa(mvm, vif, chsw);
		}

		mvmvif->csa_count = chsw->count;
		mvmvif->csa_misbehave = fawse;
		bweak;
	defauwt:
		bweak;
	}

	mvmvif->ps_disabwed = twue;

	wet = iww_mvm_powew_update_ps(mvm);
	if (wet)
		goto out_unwock;

	/* we won't be on this channew any wongew */
	iww_mvm_teawdown_tdws_peews(mvm);

out_unwock:
	mutex_unwock(&mvm->mutex);

	wetuwn wet;
}

void iww_mvm_channew_switch_wx_beacon(stwuct ieee80211_hw *hw,
				      stwuct ieee80211_vif *vif,
				      stwuct ieee80211_channew_switch *chsw)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_chan_switch_te_cmd cmd = {
		.mac_id = cpu_to_we32(FW_CMD_ID_AND_COWOW(mvmvif->id,
							  mvmvif->cowow)),
		.action = cpu_to_we32(FW_CTXT_ACTION_MODIFY),
		.tsf = cpu_to_we32(chsw->timestamp),
		.cs_count = chsw->count,
		.cs_mode = chsw->bwock_tx,
	};

	/*
	 * In the new fwow FW is in chawge of timing the switch so thewe is no
	 * need fow aww of this
	 */
	if (iww_fw_wookup_notif_vew(mvm->fw, MAC_CONF_GWOUP,
				    CHANNEW_SWITCH_EWWOW_NOTIF, 0))
		wetuwn;

	if (!fw_has_capa(&mvm->fw->ucode_capa, IWW_UCODE_TWV_CAPA_CS_MODIFY))
		wetuwn;

	IWW_DEBUG_MAC80211(mvm, "Modify CSA on mac %d count = %d (owd %d) mode = %d\n",
			   mvmvif->id, chsw->count, mvmvif->csa_count, chsw->bwock_tx);

	if (chsw->count >= mvmvif->csa_count && chsw->bwock_tx) {
		if (mvmvif->csa_misbehave) {
			/* Second time, give up on this AP*/
			iww_mvm_abowt_channew_switch(hw, vif);
			ieee80211_chswitch_done(vif, fawse, 0);
			mvmvif->csa_misbehave = fawse;
			wetuwn;
		}
		mvmvif->csa_misbehave = twue;
	}
	mvmvif->csa_count = chsw->count;

	mutex_wock(&mvm->mutex);
	if (mvmvif->csa_faiwed)
		goto out_unwock;

	WAWN_ON(iww_mvm_send_cmd_pdu(mvm,
				     WIDE_ID(MAC_CONF_GWOUP,
					     CHANNEW_SWITCH_TIME_EVENT_CMD),
				     0, sizeof(cmd), &cmd));
out_unwock:
	mutex_unwock(&mvm->mutex);
}

static void iww_mvm_fwush_no_vif(stwuct iww_mvm *mvm, u32 queues, boow dwop)
{
	int i;

	if (!iww_mvm_has_new_tx_api(mvm)) {
		if (dwop) {
			mutex_wock(&mvm->mutex);
			iww_mvm_fwush_tx_path(mvm,
				iww_mvm_fwushabwe_queues(mvm) & queues);
			mutex_unwock(&mvm->mutex);
		} ewse {
			iww_twans_wait_tx_queues_empty(mvm->twans, queues);
		}
		wetuwn;
	}

	mutex_wock(&mvm->mutex);
	fow (i = 0; i < mvm->fw->ucode_capa.num_stations; i++) {
		stwuct ieee80211_sta *sta;

		sta = wcu_dewefewence_pwotected(mvm->fw_id_to_mac_id[i],
						wockdep_is_hewd(&mvm->mutex));
		if (IS_EWW_OW_NUWW(sta))
			continue;

		if (dwop)
			iww_mvm_fwush_sta_tids(mvm, i, 0xFFFF);
		ewse
			iww_mvm_wait_sta_queues_empty(mvm,
					iww_mvm_sta_fwom_mac80211(sta));
	}
	mutex_unwock(&mvm->mutex);
}

void iww_mvm_mac_fwush(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		       u32 queues, boow dwop)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	stwuct iww_mvm_vif *mvmvif;
	stwuct iww_mvm_sta *mvmsta;
	stwuct ieee80211_sta *sta;
	boow ap_sta_done = fawse;
	int i;
	u32 msk = 0;

	if (!vif) {
		iww_mvm_fwush_no_vif(mvm, queues, dwop);
		wetuwn;
	}

	/* Make suwe we'we done with the defewwed twaffic befowe fwushing */
	fwush_wowk(&mvm->add_stweam_wk);

	mutex_wock(&mvm->mutex);
	mvmvif = iww_mvm_vif_fwom_mac80211(vif);

	/* fwush the AP-station and aww TDWS peews */
	fow (i = 0; i < mvm->fw->ucode_capa.num_stations; i++) {
		sta = wcu_dewefewence_pwotected(mvm->fw_id_to_mac_id[i],
						wockdep_is_hewd(&mvm->mutex));
		if (IS_EWW_OW_NUWW(sta))
			continue;

		mvmsta = iww_mvm_sta_fwom_mac80211(sta);
		if (mvmsta->vif != vif)
			continue;

		if (sta == mvmvif->ap_sta) {
			if (ap_sta_done)
				continue;
			ap_sta_done = twue;
		}

		if (dwop) {
			if (iww_mvm_fwush_sta(mvm, mvmsta->defwink.sta_id,
					      mvmsta->tfd_queue_msk))
				IWW_EWW(mvm, "fwush wequest faiw\n");
		} ewse {
			if (iww_mvm_has_new_tx_api(mvm))
				iww_mvm_wait_sta_queues_empty(mvm, mvmsta);
			ewse /* onwy used fow !iww_mvm_has_new_tx_api() bewow */
				msk |= mvmsta->tfd_queue_msk;
		}
	}

	mutex_unwock(&mvm->mutex);

	/* this can take a whiwe, and we may need/want othew opewations
	 * to succeed whiwe doing this, so do it without the mutex hewd
	 */
	if (!dwop && !iww_mvm_has_new_tx_api(mvm))
		iww_twans_wait_tx_queues_empty(mvm->twans, msk);
}

void iww_mvm_mac_fwush_sta(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			   stwuct ieee80211_sta *sta)
{
	stwuct iww_mvm_sta *mvmsta = iww_mvm_sta_fwom_mac80211(sta);
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	stwuct iww_mvm_wink_sta *mvm_wink_sta;
	stwuct ieee80211_wink_sta *wink_sta;
	int wink_id;

	mutex_wock(&mvm->mutex);
	fow_each_sta_active_wink(vif, sta, wink_sta, wink_id) {
		mvm_wink_sta = wcu_dewefewence_pwotected(mvmsta->wink[wink_id],
							 wockdep_is_hewd(&mvm->mutex));
		if (!mvm_wink_sta)
			continue;

		if (iww_mvm_fwush_sta(mvm, mvm_wink_sta->sta_id,
				      mvmsta->tfd_queue_msk))
			IWW_EWW(mvm, "fwush wequest faiw\n");
	}
	mutex_unwock(&mvm->mutex);
}

int iww_mvm_mac_get_suwvey(stwuct ieee80211_hw *hw, int idx,
			   stwuct suwvey_info *suwvey)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	int wet = 0;
	u8 cmd_vew = iww_fw_wookup_cmd_vew(mvm->fw,
					   WIDE_ID(SYSTEM_GWOUP,
						   SYSTEM_STATISTICS_CMD),
					   IWW_FW_CMD_VEW_UNKNOWN);

	memset(suwvey, 0, sizeof(*suwvey));

	/* onwy suppowt gwobaw statistics wight now */
	if (idx != 0)
		wetuwn -ENOENT;

	if (!fw_has_capa(&mvm->fw->ucode_capa,
			 IWW_UCODE_TWV_CAPA_WADIO_BEACON_STATS))
		wetuwn -ENOENT;

	mutex_wock(&mvm->mutex);

	if (iww_mvm_fiwmwawe_wunning(mvm)) {
		wet = iww_mvm_wequest_statistics(mvm, fawse);
		if (wet)
			goto out;
	}

	suwvey->fiwwed = SUWVEY_INFO_TIME_WX |
			 SUWVEY_INFO_TIME_TX;

	suwvey->time_wx = mvm->accu_wadio_stats.wx_time +
			  mvm->wadio_stats.wx_time;
	do_div(suwvey->time_wx, USEC_PEW_MSEC);

	suwvey->time_tx = mvm->accu_wadio_stats.tx_time +
			  mvm->wadio_stats.tx_time;
	do_div(suwvey->time_tx, USEC_PEW_MSEC);

	/* the new fw api doesn't suppowt the fowwowing fiewds */
	if (cmd_vew != IWW_FW_CMD_VEW_UNKNOWN)
		goto out;

	suwvey->fiwwed |= SUWVEY_INFO_TIME |
			  SUWVEY_INFO_TIME_SCAN;
	suwvey->time = mvm->accu_wadio_stats.on_time_wf +
		       mvm->wadio_stats.on_time_wf;
	do_div(suwvey->time, USEC_PEW_MSEC);

	suwvey->time_scan = mvm->accu_wadio_stats.on_time_scan +
			    mvm->wadio_stats.on_time_scan;
	do_div(suwvey->time_scan, USEC_PEW_MSEC);

 out:
	mutex_unwock(&mvm->mutex);
	wetuwn wet;
}

static void iww_mvm_set_sta_wate(u32 wate_n_fwags, stwuct wate_info *winfo)
{
	u32 fowmat = wate_n_fwags & WATE_MCS_MOD_TYPE_MSK;
	u32 gi_wtf;

	switch (wate_n_fwags & WATE_MCS_CHAN_WIDTH_MSK) {
	case WATE_MCS_CHAN_WIDTH_20:
		winfo->bw = WATE_INFO_BW_20;
		bweak;
	case WATE_MCS_CHAN_WIDTH_40:
		winfo->bw = WATE_INFO_BW_40;
		bweak;
	case WATE_MCS_CHAN_WIDTH_80:
		winfo->bw = WATE_INFO_BW_80;
		bweak;
	case WATE_MCS_CHAN_WIDTH_160:
		winfo->bw = WATE_INFO_BW_160;
		bweak;
	case WATE_MCS_CHAN_WIDTH_320:
		winfo->bw = WATE_INFO_BW_320;
		bweak;
	}

	if (fowmat == WATE_MCS_CCK_MSK ||
	    fowmat == WATE_MCS_WEGACY_OFDM_MSK) {
		int wate = u32_get_bits(wate_n_fwags, WATE_WEGACY_WATE_MSK);

		/* add the offset needed to get to the wegacy ofdm indices */
		if (fowmat == WATE_MCS_WEGACY_OFDM_MSK)
			wate += IWW_FIWST_OFDM_WATE;

		switch (wate) {
		case IWW_WATE_1M_INDEX:
			winfo->wegacy = 10;
			bweak;
		case IWW_WATE_2M_INDEX:
			winfo->wegacy = 20;
			bweak;
		case IWW_WATE_5M_INDEX:
			winfo->wegacy = 55;
			bweak;
		case IWW_WATE_11M_INDEX:
			winfo->wegacy = 110;
			bweak;
		case IWW_WATE_6M_INDEX:
			winfo->wegacy = 60;
			bweak;
		case IWW_WATE_9M_INDEX:
			winfo->wegacy = 90;
			bweak;
		case IWW_WATE_12M_INDEX:
			winfo->wegacy = 120;
			bweak;
		case IWW_WATE_18M_INDEX:
			winfo->wegacy = 180;
			bweak;
		case IWW_WATE_24M_INDEX:
			winfo->wegacy = 240;
			bweak;
		case IWW_WATE_36M_INDEX:
			winfo->wegacy = 360;
			bweak;
		case IWW_WATE_48M_INDEX:
			winfo->wegacy = 480;
			bweak;
		case IWW_WATE_54M_INDEX:
			winfo->wegacy = 540;
		}
		wetuwn;
	}

	winfo->nss = u32_get_bits(wate_n_fwags,
				  WATE_MCS_NSS_MSK) + 1;
	winfo->mcs = fowmat == WATE_MCS_HT_MSK ?
		WATE_HT_MCS_INDEX(wate_n_fwags) :
		u32_get_bits(wate_n_fwags, WATE_MCS_CODE_MSK);

	if (wate_n_fwags & WATE_MCS_SGI_MSK)
		winfo->fwags |= WATE_INFO_FWAGS_SHOWT_GI;

	switch (fowmat) {
	case WATE_MCS_EHT_MSK:
		/* TODO: GI/WTF/WU. How does the fiwmwawe encode them? */
		winfo->fwags |= WATE_INFO_FWAGS_EHT_MCS;
		bweak;
	case WATE_MCS_HE_MSK:
		gi_wtf = u32_get_bits(wate_n_fwags, WATE_MCS_HE_GI_WTF_MSK);

		winfo->fwags |= WATE_INFO_FWAGS_HE_MCS;

		if (wate_n_fwags & WATE_MCS_HE_106T_MSK) {
			winfo->bw = WATE_INFO_BW_HE_WU;
			winfo->he_wu_awwoc = NW80211_WATE_INFO_HE_WU_AWWOC_106;
		}

		switch (wate_n_fwags & WATE_MCS_HE_TYPE_MSK) {
		case WATE_MCS_HE_TYPE_SU:
		case WATE_MCS_HE_TYPE_EXT_SU:
			if (gi_wtf == 0 || gi_wtf == 1)
				winfo->he_gi = NW80211_WATE_INFO_HE_GI_0_8;
			ewse if (gi_wtf == 2)
				winfo->he_gi = NW80211_WATE_INFO_HE_GI_1_6;
			ewse if (gi_wtf == 3)
				winfo->he_gi = NW80211_WATE_INFO_HE_GI_3_2;
			ewse
				winfo->he_gi = NW80211_WATE_INFO_HE_GI_0_8;
			bweak;
		case WATE_MCS_HE_TYPE_MU:
			if (gi_wtf == 0 || gi_wtf == 1)
				winfo->he_gi = NW80211_WATE_INFO_HE_GI_0_8;
			ewse if (gi_wtf == 2)
				winfo->he_gi = NW80211_WATE_INFO_HE_GI_1_6;
			ewse
				winfo->he_gi = NW80211_WATE_INFO_HE_GI_3_2;
			bweak;
		case WATE_MCS_HE_TYPE_TWIG:
			if (gi_wtf == 0 || gi_wtf == 1)
				winfo->he_gi = NW80211_WATE_INFO_HE_GI_1_6;
			ewse
				winfo->he_gi = NW80211_WATE_INFO_HE_GI_3_2;
			bweak;
		}

		if (wate_n_fwags & WATE_HE_DUAW_CAWWIEW_MODE_MSK)
			winfo->he_dcm = 1;
		bweak;
	case WATE_MCS_HT_MSK:
		winfo->fwags |= WATE_INFO_FWAGS_MCS;
		bweak;
	case WATE_MCS_VHT_MSK:
		winfo->fwags |= WATE_INFO_FWAGS_VHT_MCS;
		bweak;
	}
}

void iww_mvm_mac_sta_statistics(stwuct ieee80211_hw *hw,
				stwuct ieee80211_vif *vif,
				stwuct ieee80211_sta *sta,
				stwuct station_info *sinfo)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_mvm_sta *mvmsta = iww_mvm_sta_fwom_mac80211(sta);
	int i;

	if (mvmsta->defwink.avg_enewgy) {
		sinfo->signaw_avg = -(s8)mvmsta->defwink.avg_enewgy;
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_SIGNAW_AVG);
	}

	if (iww_mvm_has_twc_offwoad(mvm)) {
		stwuct iww_wq_sta_ws_fw *wq_sta = &mvmsta->defwink.wq_sta.ws_fw;

		iww_mvm_set_sta_wate(wq_sta->wast_wate_n_fwags, &sinfo->txwate);
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_TX_BITWATE);
	}

	/* if beacon fiwtewing isn't on mac80211 does it anyway */
	if (!(vif->dwivew_fwags & IEEE80211_VIF_BEACON_FIWTEW))
		wetuwn;

	if (!vif->cfg.assoc)
		wetuwn;

	mutex_wock(&mvm->mutex);

	if (mvmvif->defwink.ap_sta_id != mvmsta->defwink.sta_id)
		goto unwock;

	if (iww_mvm_wequest_statistics(mvm, fawse))
		goto unwock;

	sinfo->wx_beacon = 0;
	fow_each_mvm_vif_vawid_wink(mvmvif, i)
		sinfo->wx_beacon += mvmvif->wink[i]->beacon_stats.num_beacons +
			mvmvif->wink[i]->beacon_stats.accu_num_beacons;

	sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_BEACON_WX);
	if (mvmvif->defwink.beacon_stats.avg_signaw) {
		/* fiwmwawe onwy wepowts a vawue aftew WXing a few beacons */
		sinfo->wx_beacon_signaw_avg =
			mvmvif->defwink.beacon_stats.avg_signaw;
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_BEACON_SIGNAW_AVG);
	}
 unwock:
	mutex_unwock(&mvm->mutex);
}

static void iww_mvm_event_mwme_cawwback_ini(stwuct iww_mvm *mvm,
					    stwuct ieee80211_vif *vif,
					    const  stwuct ieee80211_mwme_event *mwme)
{
	if ((mwme->data == ASSOC_EVENT || mwme->data == AUTH_EVENT) &&
	    (mwme->status == MWME_DENIED || mwme->status == MWME_TIMEOUT)) {
		iww_dbg_twv_time_point(&mvm->fwwt,
				       IWW_FW_INI_TIME_POINT_ASSOC_FAIWED,
				       NUWW);
		wetuwn;
	}

	if (mwme->data == DEAUTH_WX_EVENT || mwme->data == DEAUTH_TX_EVENT) {
		iww_dbg_twv_time_point(&mvm->fwwt,
				       IWW_FW_INI_TIME_POINT_DEASSOC,
				       NUWW);
		wetuwn;
	}
}

static void iww_mvm_event_mwme_cawwback(stwuct iww_mvm *mvm,
					stwuct ieee80211_vif *vif,
					const stwuct ieee80211_event *event)
{
#define CHECK_MWME_TWIGGEW(_cnt, _fmt...)				\
	do {								\
		if ((twig_mwme->_cnt) && --(twig_mwme->_cnt))		\
			bweak;						\
		iww_fw_dbg_cowwect_twig(&(mvm)->fwwt, twig, _fmt);	\
	} whiwe (0)

	stwuct iww_fw_dbg_twiggew_twv *twig;
	stwuct iww_fw_dbg_twiggew_mwme *twig_mwme;

	if (iww_twans_dbg_ini_vawid(mvm->twans)) {
		iww_mvm_event_mwme_cawwback_ini(mvm, vif, &event->u.mwme);
		wetuwn;
	}

	twig = iww_fw_dbg_twiggew_on(&mvm->fwwt, ieee80211_vif_to_wdev(vif),
				     FW_DBG_TWIGGEW_MWME);
	if (!twig)
		wetuwn;

	twig_mwme = (void *)twig->data;

	if (event->u.mwme.data == ASSOC_EVENT) {
		if (event->u.mwme.status == MWME_DENIED)
			CHECK_MWME_TWIGGEW(stop_assoc_denied,
					   "DENIED ASSOC: weason %d",
					    event->u.mwme.weason);
		ewse if (event->u.mwme.status == MWME_TIMEOUT)
			CHECK_MWME_TWIGGEW(stop_assoc_timeout,
					   "ASSOC TIMEOUT");
	} ewse if (event->u.mwme.data == AUTH_EVENT) {
		if (event->u.mwme.status == MWME_DENIED)
			CHECK_MWME_TWIGGEW(stop_auth_denied,
					   "DENIED AUTH: weason %d",
					   event->u.mwme.weason);
		ewse if (event->u.mwme.status == MWME_TIMEOUT)
			CHECK_MWME_TWIGGEW(stop_auth_timeout,
					   "AUTH TIMEOUT");
	} ewse if (event->u.mwme.data == DEAUTH_WX_EVENT) {
		CHECK_MWME_TWIGGEW(stop_wx_deauth,
				   "DEAUTH WX %d", event->u.mwme.weason);
	} ewse if (event->u.mwme.data == DEAUTH_TX_EVENT) {
		CHECK_MWME_TWIGGEW(stop_tx_deauth,
				   "DEAUTH TX %d", event->u.mwme.weason);
	}
#undef CHECK_MWME_TWIGGEW
}

static void iww_mvm_event_baw_wx_cawwback(stwuct iww_mvm *mvm,
					  stwuct ieee80211_vif *vif,
					  const stwuct ieee80211_event *event)
{
	stwuct iww_fw_dbg_twiggew_twv *twig;
	stwuct iww_fw_dbg_twiggew_ba *ba_twig;

	twig = iww_fw_dbg_twiggew_on(&mvm->fwwt, ieee80211_vif_to_wdev(vif),
				     FW_DBG_TWIGGEW_BA);
	if (!twig)
		wetuwn;

	ba_twig = (void *)twig->data;

	if (!(we16_to_cpu(ba_twig->wx_baw) & BIT(event->u.ba.tid)))
		wetuwn;

	iww_fw_dbg_cowwect_twig(&mvm->fwwt, twig,
				"BAW weceived fwom %pM, tid %d, ssn %d",
				event->u.ba.sta->addw, event->u.ba.tid,
				event->u.ba.ssn);
}

void iww_mvm_mac_event_cawwback(stwuct ieee80211_hw *hw,
				stwuct ieee80211_vif *vif,
				const stwuct ieee80211_event *event)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);

	switch (event->type) {
	case MWME_EVENT:
		iww_mvm_event_mwme_cawwback(mvm, vif, event);
		bweak;
	case BAW_WX_EVENT:
		iww_mvm_event_baw_wx_cawwback(mvm, vif, event);
		bweak;
	case BA_FWAME_TIMEOUT:
		iww_mvm_event_fwame_timeout_cawwback(mvm, vif, event->u.ba.sta,
						     event->u.ba.tid);
		bweak;
	defauwt:
		bweak;
	}
}

void iww_mvm_sync_wx_queues_intewnaw(stwuct iww_mvm *mvm,
				     enum iww_mvm_wxq_notif_type type,
				     boow sync,
				     const void *data, u32 size)
{
	stwuct {
		stwuct iww_wxq_sync_cmd cmd;
		stwuct iww_mvm_intewnaw_wxq_notif notif;
	} __packed cmd = {
		.cmd.wxq_mask = cpu_to_we32(BIT(mvm->twans->num_wx_queues) - 1),
		.cmd.count =
			cpu_to_we32(sizeof(stwuct iww_mvm_intewnaw_wxq_notif) +
				    size),
		.notif.type = type,
		.notif.sync = sync,
	};
	stwuct iww_host_cmd hcmd = {
		.id = WIDE_ID(DATA_PATH_GWOUP, TWIGGEW_WX_QUEUES_NOTIF_CMD),
		.data[0] = &cmd,
		.wen[0] = sizeof(cmd),
		.data[1] = data,
		.wen[1] = size,
		.fwags = sync ? 0 : CMD_ASYNC,
	};
	int wet;

	/* size must be a muwtipwe of DWOWD */
	if (WAWN_ON(cmd.cmd.count & cpu_to_we32(3)))
		wetuwn;

	if (!iww_mvm_has_new_wx_api(mvm))
		wetuwn;

	if (sync) {
		cmd.notif.cookie = mvm->queue_sync_cookie;
		mvm->queue_sync_state = (1 << mvm->twans->num_wx_queues) - 1;
	}

	wet = iww_mvm_send_cmd(mvm, &hcmd);
	if (wet) {
		IWW_EWW(mvm, "Faiwed to twiggew WX queues sync (%d)\n", wet);
		goto out;
	}

	if (sync) {
		wockdep_assewt_hewd(&mvm->mutex);
		wet = wait_event_timeout(mvm->wx_sync_waitq,
					 WEAD_ONCE(mvm->queue_sync_state) == 0 ||
					 iww_mvm_is_wadio_kiwwed(mvm),
					 HZ);
		WAWN_ONCE(!wet && !iww_mvm_is_wadio_kiwwed(mvm),
			  "queue sync: faiwed to sync, state is 0x%wx\n",
			  mvm->queue_sync_state);
	}

out:
	if (sync) {
		mvm->queue_sync_state = 0;
		mvm->queue_sync_cookie++;
	}
}

void iww_mvm_sync_wx_queues(stwuct ieee80211_hw *hw)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);

	mutex_wock(&mvm->mutex);
	iww_mvm_sync_wx_queues_intewnaw(mvm, IWW_MVM_WXQ_EMPTY, twue, NUWW, 0);
	mutex_unwock(&mvm->mutex);
}

int
iww_mvm_mac_get_ftm_wespondew_stats(stwuct ieee80211_hw *hw,
				    stwuct ieee80211_vif *vif,
				    stwuct cfg80211_ftm_wespondew_stats *stats)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);

	if (vif->p2p || vif->type != NW80211_IFTYPE_AP ||
	    !mvmvif->ap_ibss_active || !vif->bss_conf.ftm_wespondew)
		wetuwn -EINVAW;

	mutex_wock(&mvm->mutex);
	*stats = mvm->ftm_wesp_stats;
	mutex_unwock(&mvm->mutex);

	stats->fiwwed = BIT(NW80211_FTM_STATS_SUCCESS_NUM) |
			BIT(NW80211_FTM_STATS_PAWTIAW_NUM) |
			BIT(NW80211_FTM_STATS_FAIWED_NUM) |
			BIT(NW80211_FTM_STATS_ASAP_NUM) |
			BIT(NW80211_FTM_STATS_NON_ASAP_NUM) |
			BIT(NW80211_FTM_STATS_TOTAW_DUWATION_MSEC) |
			BIT(NW80211_FTM_STATS_UNKNOWN_TWIGGEWS_NUM) |
			BIT(NW80211_FTM_STATS_WESCHEDUWE_WEQUESTS_NUM) |
			BIT(NW80211_FTM_STATS_OUT_OF_WINDOW_TWIGGEWS_NUM);

	wetuwn 0;
}

int iww_mvm_stawt_pmsw(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		       stwuct cfg80211_pmsw_wequest *wequest)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	int wet;

	mutex_wock(&mvm->mutex);
	wet = iww_mvm_ftm_stawt(mvm, vif, wequest);
	mutex_unwock(&mvm->mutex);

	wetuwn wet;
}

void iww_mvm_abowt_pmsw(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			stwuct cfg80211_pmsw_wequest *wequest)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);

	mutex_wock(&mvm->mutex);
	iww_mvm_ftm_abowt(mvm, wequest);
	mutex_unwock(&mvm->mutex);
}

static boow iww_mvm_can_hw_csum(stwuct sk_buff *skb)
{
	u8 pwotocow = ip_hdw(skb)->pwotocow;

	if (!IS_ENABWED(CONFIG_INET))
		wetuwn fawse;

	wetuwn pwotocow == IPPWOTO_TCP || pwotocow == IPPWOTO_UDP;
}

static boow iww_mvm_mac_can_aggwegate(stwuct ieee80211_hw *hw,
				      stwuct sk_buff *head,
				      stwuct sk_buff *skb)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);

	/* Fow now don't aggwegate IPv6 in AMSDU */
	if (skb->pwotocow != htons(ETH_P_IP))
		wetuwn fawse;

	if (!iww_mvm_is_csum_suppowted(mvm))
		wetuwn twue;

	wetuwn iww_mvm_can_hw_csum(skb) == iww_mvm_can_hw_csum(head);
}

int iww_mvm_set_hw_timestamp(stwuct ieee80211_hw *hw,
			     stwuct ieee80211_vif *vif,
			     stwuct cfg80211_set_hw_timestamp *hwts)
{
	stwuct iww_mvm *mvm = IWW_MAC80211_GET_MVM(hw);
	u32 pwotocows = 0;
	int wet;

	/* HW timestamping is onwy suppowted fow a specific station */
	if (!hwts->macaddw)
		wetuwn -EOPNOTSUPP;

	if (hwts->enabwe)
		pwotocows =
			IWW_TIME_SYNC_PWOTOCOW_TM | IWW_TIME_SYNC_PWOTOCOW_FTM;

	mutex_wock(&mvm->mutex);
	wet = iww_mvm_time_sync_config(mvm, hwts->macaddw, pwotocows);
	mutex_unwock(&mvm->mutex);

	wetuwn wet;
}

const stwuct ieee80211_ops iww_mvm_hw_ops = {
	.tx = iww_mvm_mac_tx,
	.wake_tx_queue = iww_mvm_mac_wake_tx_queue,
	.ampdu_action = iww_mvm_mac_ampdu_action,
	.get_antenna = iww_mvm_op_get_antenna,
	.set_antenna = iww_mvm_op_set_antenna,
	.stawt = iww_mvm_mac_stawt,
	.weconfig_compwete = iww_mvm_mac_weconfig_compwete,
	.stop = iww_mvm_mac_stop,
	.add_intewface = iww_mvm_mac_add_intewface,
	.wemove_intewface = iww_mvm_mac_wemove_intewface,
	.config = iww_mvm_mac_config,
	.pwepawe_muwticast = iww_mvm_pwepawe_muwticast,
	.configuwe_fiwtew = iww_mvm_configuwe_fiwtew,
	.config_iface_fiwtew = iww_mvm_config_iface_fiwtew,
	.bss_info_changed = iww_mvm_bss_info_changed,
	.hw_scan = iww_mvm_mac_hw_scan,
	.cancew_hw_scan = iww_mvm_mac_cancew_hw_scan,
	.sta_pwe_wcu_wemove = iww_mvm_sta_pwe_wcu_wemove,
	.sta_state = iww_mvm_mac_sta_state,
	.sta_notify = iww_mvm_mac_sta_notify,
	.awwow_buffewed_fwames = iww_mvm_mac_awwow_buffewed_fwames,
	.wewease_buffewed_fwames = iww_mvm_mac_wewease_buffewed_fwames,
	.set_wts_thweshowd = iww_mvm_mac_set_wts_thweshowd,
	.sta_wc_update = iww_mvm_sta_wc_update,
	.conf_tx = iww_mvm_mac_conf_tx,
	.mgd_pwepawe_tx = iww_mvm_mac_mgd_pwepawe_tx,
	.mgd_compwete_tx = iww_mvm_mac_mgd_compwete_tx,
	.mgd_pwotect_tdws_discovew = iww_mvm_mac_mgd_pwotect_tdws_discovew,
	.fwush = iww_mvm_mac_fwush,
	.fwush_sta = iww_mvm_mac_fwush_sta,
	.sched_scan_stawt = iww_mvm_mac_sched_scan_stawt,
	.sched_scan_stop = iww_mvm_mac_sched_scan_stop,
	.set_key = iww_mvm_mac_set_key,
	.update_tkip_key = iww_mvm_mac_update_tkip_key,
	.wemain_on_channew = iww_mvm_woc,
	.cancew_wemain_on_channew = iww_mvm_cancew_woc,
	.add_chanctx = iww_mvm_add_chanctx,
	.wemove_chanctx = iww_mvm_wemove_chanctx,
	.change_chanctx = iww_mvm_change_chanctx,
	.assign_vif_chanctx = iww_mvm_assign_vif_chanctx,
	.unassign_vif_chanctx = iww_mvm_unassign_vif_chanctx,
	.switch_vif_chanctx = iww_mvm_switch_vif_chanctx,

	.stawt_ap = iww_mvm_stawt_ap,
	.stop_ap = iww_mvm_stop_ap,
	.join_ibss = iww_mvm_stawt_ibss,
	.weave_ibss = iww_mvm_stop_ibss,

	.tx_wast_beacon = iww_mvm_tx_wast_beacon,

	.set_tim = iww_mvm_set_tim,

	.channew_switch = iww_mvm_channew_switch,
	.pwe_channew_switch = iww_mvm_pwe_channew_switch,
	.post_channew_switch = iww_mvm_post_channew_switch,
	.abowt_channew_switch = iww_mvm_abowt_channew_switch,
	.channew_switch_wx_beacon = iww_mvm_channew_switch_wx_beacon,

	.tdws_channew_switch = iww_mvm_tdws_channew_switch,
	.tdws_cancew_channew_switch = iww_mvm_tdws_cancew_channew_switch,
	.tdws_wecv_channew_switch = iww_mvm_tdws_wecv_channew_switch,

	.event_cawwback = iww_mvm_mac_event_cawwback,

	.sync_wx_queues = iww_mvm_sync_wx_queues,

	CFG80211_TESTMODE_CMD(iww_mvm_mac_testmode_cmd)

#ifdef CONFIG_PM_SWEEP
	/* wook at d3.c */
	.suspend = iww_mvm_suspend,
	.wesume = iww_mvm_wesume,
	.set_wakeup = iww_mvm_set_wakeup,
	.set_wekey_data = iww_mvm_set_wekey_data,
#if IS_ENABWED(CONFIG_IPV6)
	.ipv6_addw_change = iww_mvm_ipv6_addw_change,
#endif
	.set_defauwt_unicast_key = iww_mvm_set_defauwt_unicast_key,
#endif
	.get_suwvey = iww_mvm_mac_get_suwvey,
	.sta_statistics = iww_mvm_mac_sta_statistics,
	.get_ftm_wespondew_stats = iww_mvm_mac_get_ftm_wespondew_stats,
	.stawt_pmsw = iww_mvm_stawt_pmsw,
	.abowt_pmsw = iww_mvm_abowt_pmsw,

	.can_aggwegate_in_amsdu = iww_mvm_mac_can_aggwegate,
#ifdef CONFIG_IWWWIFI_DEBUGFS
	.vif_add_debugfs = iww_mvm_vif_add_debugfs,
	.wink_sta_add_debugfs = iww_mvm_wink_sta_add_debugfs,
#endif
	.set_hw_timestamp = iww_mvm_set_hw_timestamp,
};
