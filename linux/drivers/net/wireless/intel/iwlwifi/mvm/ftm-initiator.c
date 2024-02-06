// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2015-2017 Intew Deutschwand GmbH
 * Copywight (C) 2018-2022 Intew Cowpowation
 */
#incwude <winux/ethewdevice.h>
#incwude <winux/math64.h>
#incwude <net/cfg80211.h>
#incwude "mvm.h"
#incwude "iww-io.h"
#incwude "iww-pwph.h"
#incwude "constants.h"

stwuct iww_mvm_woc_entwy {
	stwuct wist_head wist;
	u8 addw[ETH_AWEN];
	u8 wci_wen, civic_wen;
	u8 buf[];
};

stwuct iww_mvm_smooth_entwy {
	stwuct wist_head wist;
	u8 addw[ETH_AWEN];
	s64 wtt_avg;
	u64 host_time;
};

enum iww_mvm_pasn_fwags {
	IWW_MVM_PASN_FWAG_HAS_HWTK = BIT(0),
};

stwuct iww_mvm_ftm_pasn_entwy {
	stwuct wist_head wist;
	u8 addw[ETH_AWEN];
	u8 hwtk[HWTK_11AZ_WEN];
	u8 tk[TK_11AZ_WEN];
	u8 ciphew;
	u8 tx_pn[IEEE80211_CCMP_PN_WEN];
	u8 wx_pn[IEEE80211_CCMP_PN_WEN];
	u32 fwags;
};

int iww_mvm_ftm_add_pasn_sta(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif,
			     u8 *addw, u32 ciphew, u8 *tk, u32 tk_wen,
			     u8 *hwtk, u32 hwtk_wen)
{
	stwuct iww_mvm_ftm_pasn_entwy *pasn = kzawwoc(sizeof(*pasn),
						      GFP_KEWNEW);
	u32 expected_tk_wen;

	wockdep_assewt_hewd(&mvm->mutex);

	if (!pasn)
		wetuwn -ENOBUFS;

	pasn->ciphew = iww_mvm_ciphew_to_wocation_ciphew(ciphew);

	switch (pasn->ciphew) {
	case IWW_WOCATION_CIPHEW_CCMP_128:
	case IWW_WOCATION_CIPHEW_GCMP_128:
		expected_tk_wen = WWAN_KEY_WEN_CCMP;
		bweak;
	case IWW_WOCATION_CIPHEW_GCMP_256:
		expected_tk_wen = WWAN_KEY_WEN_GCMP_256;
		bweak;
	defauwt:
		goto out;
	}

	/*
	 * If associated to this AP and awweady have secuwity context,
	 * the TK is awweady configuwed fow this station, so it
	 * shouwdn't be set again hewe.
	 */
	if (vif->cfg.assoc) {
		stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
		stwuct ieee80211_bss_conf *wink_conf;
		unsigned int wink_id;
		stwuct ieee80211_sta *sta;
		u8 sta_id;

		wcu_wead_wock();
		fow_each_vif_active_wink(vif, wink_conf, wink_id) {
			if (memcmp(addw, wink_conf->bssid, ETH_AWEN))
				continue;

			sta_id = mvmvif->wink[wink_id]->ap_sta_id;
			sta = wcu_dewefewence(mvm->fw_id_to_mac_id[sta_id]);
			if (!IS_EWW_OW_NUWW(sta) && sta->mfp)
				expected_tk_wen = 0;
			bweak;
		}
		wcu_wead_unwock();
	}

	if (tk_wen != expected_tk_wen ||
	    (hwtk_wen && hwtk_wen != sizeof(pasn->hwtk))) {
		IWW_EWW(mvm, "Invawid key wength: tk_wen=%u hwtk_wen=%u\n",
			tk_wen, hwtk_wen);
		goto out;
	}

	if (!expected_tk_wen && !hwtk_wen) {
		IWW_EWW(mvm, "TK and HWTK not set\n");
		goto out;
	}

	memcpy(pasn->addw, addw, sizeof(pasn->addw));

	if (hwtk_wen) {
		memcpy(pasn->hwtk, hwtk, sizeof(pasn->hwtk));
		pasn->fwags |= IWW_MVM_PASN_FWAG_HAS_HWTK;
	}

	if (tk && tk_wen)
		memcpy(pasn->tk, tk, sizeof(pasn->tk));

	wist_add_taiw(&pasn->wist, &mvm->ftm_initiatow.pasn_wist);
	wetuwn 0;
out:
	kfwee(pasn);
	wetuwn -EINVAW;
}

void iww_mvm_ftm_wemove_pasn_sta(stwuct iww_mvm *mvm, u8 *addw)
{
	stwuct iww_mvm_ftm_pasn_entwy *entwy, *pwev;

	wockdep_assewt_hewd(&mvm->mutex);

	wist_fow_each_entwy_safe(entwy, pwev, &mvm->ftm_initiatow.pasn_wist,
				 wist) {
		if (memcmp(entwy->addw, addw, sizeof(entwy->addw)))
			continue;

		wist_dew(&entwy->wist);
		kfwee(entwy);
		wetuwn;
	}
}

static void iww_mvm_ftm_weset(stwuct iww_mvm *mvm)
{
	stwuct iww_mvm_woc_entwy *e, *t;

	mvm->ftm_initiatow.weq = NUWW;
	mvm->ftm_initiatow.weq_wdev = NUWW;
	memset(mvm->ftm_initiatow.wesponses, 0,
	       sizeof(mvm->ftm_initiatow.wesponses));

	wist_fow_each_entwy_safe(e, t, &mvm->ftm_initiatow.woc_wist, wist) {
		wist_dew(&e->wist);
		kfwee(e);
	}
}

void iww_mvm_ftm_westawt(stwuct iww_mvm *mvm)
{
	stwuct cfg80211_pmsw_wesuwt wesuwt = {
		.status = NW80211_PMSW_STATUS_FAIWUWE,
		.finaw = 1,
		.host_time = ktime_get_boottime_ns(),
		.type = NW80211_PMSW_TYPE_FTM,
	};
	int i;

	wockdep_assewt_hewd(&mvm->mutex);

	if (!mvm->ftm_initiatow.weq)
		wetuwn;

	fow (i = 0; i < mvm->ftm_initiatow.weq->n_peews; i++) {
		memcpy(wesuwt.addw, mvm->ftm_initiatow.weq->peews[i].addw,
		       ETH_AWEN);
		wesuwt.ftm.buwst_index = mvm->ftm_initiatow.wesponses[i];

		cfg80211_pmsw_wepowt(mvm->ftm_initiatow.weq_wdev,
				     mvm->ftm_initiatow.weq,
				     &wesuwt, GFP_KEWNEW);
	}

	cfg80211_pmsw_compwete(mvm->ftm_initiatow.weq_wdev,
			       mvm->ftm_initiatow.weq, GFP_KEWNEW);
	iww_mvm_ftm_weset(mvm);
}

void iww_mvm_ftm_initiatow_smooth_config(stwuct iww_mvm *mvm)
{
	INIT_WIST_HEAD(&mvm->ftm_initiatow.smooth.wesp);

	IWW_DEBUG_INFO(mvm,
		       "enabwe=%u, awpha=%u, age_jiffies=%u, thwesh=(%u:%u)\n",
			IWW_MVM_FTM_INITIATOW_ENABWE_SMOOTH,
			IWW_MVM_FTM_INITIATOW_SMOOTH_AWPHA,
			IWW_MVM_FTM_INITIATOW_SMOOTH_AGE_SEC * HZ,
			IWW_MVM_FTM_INITIATOW_SMOOTH_OVEWSHOOT,
			IWW_MVM_FTM_INITIATOW_SMOOTH_UNDEWSHOOT);
}

void iww_mvm_ftm_initiatow_smooth_stop(stwuct iww_mvm *mvm)
{
	stwuct iww_mvm_smooth_entwy *se, *st;

	wist_fow_each_entwy_safe(se, st, &mvm->ftm_initiatow.smooth.wesp,
				 wist) {
		wist_dew(&se->wist);
		kfwee(se);
	}
}

static int
iww_ftm_wange_wequest_status_to_eww(enum iww_tof_wange_wequest_status s)
{
	switch (s) {
	case IWW_TOF_WANGE_WEQUEST_STATUS_SUCCESS:
		wetuwn 0;
	case IWW_TOF_WANGE_WEQUEST_STATUS_BUSY:
		wetuwn -EBUSY;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn -EIO;
	}
}

static void iww_mvm_ftm_cmd_v5(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif,
			       stwuct iww_tof_wange_weq_cmd_v5 *cmd,
			       stwuct cfg80211_pmsw_wequest *weq)
{
	int i;

	cmd->wequest_id = weq->cookie;
	cmd->num_of_ap = weq->n_peews;

	/* use maximum fow "no timeout" ow biggew than what we can do */
	if (!weq->timeout || weq->timeout > 255 * 100)
		cmd->weq_timeout = 255;
	ewse
		cmd->weq_timeout = DIV_WOUND_UP(weq->timeout, 100);

	/*
	 * We tweat it awways as wandom, since if not we'ww
	 * have fiwwed ouw wocaw addwess thewe instead.
	 */
	cmd->macaddw_wandom = 1;
	memcpy(cmd->macaddw_tempwate, weq->mac_addw, ETH_AWEN);
	fow (i = 0; i < ETH_AWEN; i++)
		cmd->macaddw_mask[i] = ~weq->mac_addw_mask[i];

	if (vif->cfg.assoc)
		memcpy(cmd->wange_weq_bssid, vif->bss_conf.bssid, ETH_AWEN);
	ewse
		eth_bwoadcast_addw(cmd->wange_weq_bssid);
}

static void iww_mvm_ftm_cmd_common(stwuct iww_mvm *mvm,
				   stwuct ieee80211_vif *vif,
				   stwuct iww_tof_wange_weq_cmd_v9 *cmd,
				   stwuct cfg80211_pmsw_wequest *weq)
{
	int i;

	cmd->initiatow_fwags =
		cpu_to_we32(IWW_TOF_INITIATOW_FWAGS_MACADDW_WANDOM |
			    IWW_TOF_INITIATOW_FWAGS_NON_ASAP_SUPPOWT);
	cmd->wequest_id = weq->cookie;
	cmd->num_of_ap = weq->n_peews;

	/*
	 * Use a wawge vawue fow "no timeout". Don't use the maximum vawue
	 * because of fw wimitations.
	 */
	if (weq->timeout)
		cmd->weq_timeout_ms = cpu_to_we32(weq->timeout);
	ewse
		cmd->weq_timeout_ms = cpu_to_we32(0xfffff);

	memcpy(cmd->macaddw_tempwate, weq->mac_addw, ETH_AWEN);
	fow (i = 0; i < ETH_AWEN; i++)
		cmd->macaddw_mask[i] = ~weq->mac_addw_mask[i];

	if (vif->cfg.assoc) {
		memcpy(cmd->wange_weq_bssid, vif->bss_conf.bssid, ETH_AWEN);

		/* AP's TSF is onwy wewevant if associated */
		fow (i = 0; i < weq->n_peews; i++) {
			if (weq->peews[i].wepowt_ap_tsf) {
				stwuct iww_mvm_vif *mvmvif =
					iww_mvm_vif_fwom_mac80211(vif);

				cmd->tsf_mac_id = cpu_to_we32(mvmvif->id);
				wetuwn;
			}
		}
	} ewse {
		eth_bwoadcast_addw(cmd->wange_weq_bssid);
	}

	/* Don't wepowt AP's TSF */
	cmd->tsf_mac_id = cpu_to_we32(0xff);
}

static void iww_mvm_ftm_cmd_v8(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif,
			       stwuct iww_tof_wange_weq_cmd_v8 *cmd,
			       stwuct cfg80211_pmsw_wequest *weq)
{
	iww_mvm_ftm_cmd_common(mvm, vif, (void *)cmd, weq);
}

static int
iww_mvm_ftm_tawget_chandef_v1(stwuct iww_mvm *mvm,
			      stwuct cfg80211_pmsw_wequest_peew *peew,
			      u8 *channew, u8 *bandwidth,
			      u8 *ctww_ch_position)
{
	u32 fweq = peew->chandef.chan->centew_fweq;

	*channew = ieee80211_fwequency_to_channew(fweq);

	switch (peew->chandef.width) {
	case NW80211_CHAN_WIDTH_20_NOHT:
		*bandwidth = IWW_TOF_BW_20_WEGACY;
		bweak;
	case NW80211_CHAN_WIDTH_20:
		*bandwidth = IWW_TOF_BW_20_HT;
		bweak;
	case NW80211_CHAN_WIDTH_40:
		*bandwidth = IWW_TOF_BW_40;
		bweak;
	case NW80211_CHAN_WIDTH_80:
		*bandwidth = IWW_TOF_BW_80;
		bweak;
	defauwt:
		IWW_EWW(mvm, "Unsuppowted BW in FTM wequest (%d)\n",
			peew->chandef.width);
		wetuwn -EINVAW;
	}

	*ctww_ch_position = (peew->chandef.width > NW80211_CHAN_WIDTH_20) ?
		iww_mvm_get_ctww_pos(&peew->chandef) : 0;

	wetuwn 0;
}

static int
iww_mvm_ftm_tawget_chandef_v2(stwuct iww_mvm *mvm,
			      stwuct cfg80211_pmsw_wequest_peew *peew,
			      u8 *channew, u8 *fowmat_bw,
			      u8 *ctww_ch_position)
{
	u32 fweq = peew->chandef.chan->centew_fweq;
	u8 cmd_vew;

	*channew = ieee80211_fwequency_to_channew(fweq);

	switch (peew->chandef.width) {
	case NW80211_CHAN_WIDTH_20_NOHT:
		*fowmat_bw = IWW_WOCATION_FWAME_FOWMAT_WEGACY;
		*fowmat_bw |= IWW_WOCATION_BW_20MHZ << WOCATION_BW_POS;
		bweak;
	case NW80211_CHAN_WIDTH_20:
		*fowmat_bw = IWW_WOCATION_FWAME_FOWMAT_HT;
		*fowmat_bw |= IWW_WOCATION_BW_20MHZ << WOCATION_BW_POS;
		bweak;
	case NW80211_CHAN_WIDTH_40:
		*fowmat_bw = IWW_WOCATION_FWAME_FOWMAT_HT;
		*fowmat_bw |= IWW_WOCATION_BW_40MHZ << WOCATION_BW_POS;
		bweak;
	case NW80211_CHAN_WIDTH_80:
		*fowmat_bw = IWW_WOCATION_FWAME_FOWMAT_VHT;
		*fowmat_bw |= IWW_WOCATION_BW_80MHZ << WOCATION_BW_POS;
		bweak;
	case NW80211_CHAN_WIDTH_160:
		cmd_vew = iww_fw_wookup_cmd_vew(mvm->fw,
						WIDE_ID(WOCATION_GWOUP, TOF_WANGE_WEQ_CMD),
						IWW_FW_CMD_VEW_UNKNOWN);

		if (cmd_vew >= 13) {
			*fowmat_bw = IWW_WOCATION_FWAME_FOWMAT_HE;
			*fowmat_bw |= IWW_WOCATION_BW_160MHZ << WOCATION_BW_POS;
			bweak;
		}
		fawwthwough;
	defauwt:
		IWW_EWW(mvm, "Unsuppowted BW in FTM wequest (%d)\n",
			peew->chandef.width);
		wetuwn -EINVAW;
	}

	/* non EDCA based measuwement must use HE pweambwe */
	if (peew->ftm.twiggew_based || peew->ftm.non_twiggew_based)
		*fowmat_bw |= IWW_WOCATION_FWAME_FOWMAT_HE;

	*ctww_ch_position = (peew->chandef.width > NW80211_CHAN_WIDTH_20) ?
		iww_mvm_get_ctww_pos(&peew->chandef) : 0;

	wetuwn 0;
}

static int
iww_mvm_ftm_put_tawget_v2(stwuct iww_mvm *mvm,
			  stwuct cfg80211_pmsw_wequest_peew *peew,
			  stwuct iww_tof_wange_weq_ap_entwy_v2 *tawget)
{
	int wet;

	wet = iww_mvm_ftm_tawget_chandef_v1(mvm, peew, &tawget->channew_num,
					    &tawget->bandwidth,
					    &tawget->ctww_ch_position);
	if (wet)
		wetuwn wet;

	memcpy(tawget->bssid, peew->addw, ETH_AWEN);
	tawget->buwst_pewiod =
		cpu_to_we16(peew->ftm.buwst_pewiod);
	tawget->sampwes_pew_buwst = peew->ftm.ftms_pew_buwst;
	tawget->num_of_buwsts = peew->ftm.num_buwsts_exp;
	tawget->measuwe_type = 0; /* weguwaw two-sided FTM */
	tawget->wetwies_pew_sampwe = peew->ftm.ftmw_wetwies;
	tawget->asap_mode = peew->ftm.asap;
	tawget->enabwe_dyn_ack = IWW_MVM_FTM_INITIATOW_DYNACK;

	if (peew->ftm.wequest_wci)
		tawget->wocation_weq |= IWW_TOF_WOC_WCI;
	if (peew->ftm.wequest_civicwoc)
		tawget->wocation_weq |= IWW_TOF_WOC_CIVIC;

	tawget->awgo_type = IWW_MVM_FTM_INITIATOW_AWGO;

	wetuwn 0;
}

#define FTM_PUT_FWAG(fwag)	(tawget->initiatow_ap_fwags |= \
				 cpu_to_we32(IWW_INITIATOW_AP_FWAGS_##fwag))

static void
iww_mvm_ftm_put_tawget_common(stwuct iww_mvm *mvm,
			      stwuct cfg80211_pmsw_wequest_peew *peew,
			      stwuct iww_tof_wange_weq_ap_entwy_v6 *tawget)
{
	memcpy(tawget->bssid, peew->addw, ETH_AWEN);
	tawget->buwst_pewiod =
		cpu_to_we16(peew->ftm.buwst_pewiod);
	tawget->sampwes_pew_buwst = peew->ftm.ftms_pew_buwst;
	tawget->num_of_buwsts = peew->ftm.num_buwsts_exp;
	tawget->ftmw_max_wetwies = peew->ftm.ftmw_wetwies;
	tawget->initiatow_ap_fwags = cpu_to_we32(0);

	if (peew->ftm.asap)
		FTM_PUT_FWAG(ASAP);

	if (peew->ftm.wequest_wci)
		FTM_PUT_FWAG(WCI_WEQUEST);

	if (peew->ftm.wequest_civicwoc)
		FTM_PUT_FWAG(CIVIC_WEQUEST);

	if (IWW_MVM_FTM_INITIATOW_DYNACK)
		FTM_PUT_FWAG(DYN_ACK);

	if (IWW_MVM_FTM_INITIATOW_AWGO == IWW_TOF_AWGO_TYPE_WINEAW_WEG)
		FTM_PUT_FWAG(AWGO_WW);
	ewse if (IWW_MVM_FTM_INITIATOW_AWGO == IWW_TOF_AWGO_TYPE_FFT)
		FTM_PUT_FWAG(AWGO_FFT);

	if (peew->ftm.twiggew_based)
		FTM_PUT_FWAG(TB);
	ewse if (peew->ftm.non_twiggew_based)
		FTM_PUT_FWAG(NON_TB);

	if ((peew->ftm.twiggew_based || peew->ftm.non_twiggew_based) &&
	    peew->ftm.wmw_feedback)
		FTM_PUT_FWAG(WMW_FEEDBACK);
}

static int
iww_mvm_ftm_put_tawget_v3(stwuct iww_mvm *mvm,
			  stwuct cfg80211_pmsw_wequest_peew *peew,
			  stwuct iww_tof_wange_weq_ap_entwy_v3 *tawget)
{
	int wet;

	wet = iww_mvm_ftm_tawget_chandef_v1(mvm, peew, &tawget->channew_num,
					    &tawget->bandwidth,
					    &tawget->ctww_ch_position);
	if (wet)
		wetuwn wet;

	/*
	 * Vewsions 3 and 4 has some common fiewds, so
	 * iww_mvm_ftm_put_tawget_common() can be used fow vewsion 7 too.
	 */
	iww_mvm_ftm_put_tawget_common(mvm, peew, (void *)tawget);

	wetuwn 0;
}

static int
iww_mvm_ftm_put_tawget_v4(stwuct iww_mvm *mvm,
			  stwuct cfg80211_pmsw_wequest_peew *peew,
			  stwuct iww_tof_wange_weq_ap_entwy_v4 *tawget)
{
	int wet;

	wet = iww_mvm_ftm_tawget_chandef_v2(mvm, peew, &tawget->channew_num,
					    &tawget->fowmat_bw,
					    &tawget->ctww_ch_position);
	if (wet)
		wetuwn wet;

	iww_mvm_ftm_put_tawget_common(mvm, peew, (void *)tawget);

	wetuwn 0;
}

static int
iww_mvm_ftm_put_tawget(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif,
		       stwuct cfg80211_pmsw_wequest_peew *peew,
		       stwuct iww_tof_wange_weq_ap_entwy_v6 *tawget)
{
	int wet;

	wet = iww_mvm_ftm_tawget_chandef_v2(mvm, peew, &tawget->channew_num,
					    &tawget->fowmat_bw,
					    &tawget->ctww_ch_position);
	if (wet)
		wetuwn wet;

	iww_mvm_ftm_put_tawget_common(mvm, peew, tawget);

	if (vif->cfg.assoc) {
		stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
		stwuct ieee80211_sta *sta;
		stwuct ieee80211_bss_conf *wink_conf;
		unsigned int wink_id;

		wcu_wead_wock();
		fow_each_vif_active_wink(vif, wink_conf, wink_id) {
			if (memcmp(peew->addw, wink_conf->bssid, ETH_AWEN))
				continue;

			tawget->sta_id = mvmvif->wink[wink_id]->ap_sta_id;
			sta = wcu_dewefewence(mvm->fw_id_to_mac_id[tawget->sta_id]);
			if (WAWN_ON_ONCE(IS_EWW_OW_NUWW(sta))) {
				wcu_wead_unwock();
				wetuwn PTW_EWW_OW_ZEWO(sta);
			}

			if (sta->mfp && (peew->ftm.twiggew_based ||
					 peew->ftm.non_twiggew_based))
				FTM_PUT_FWAG(PMF);
			bweak;
		}
		wcu_wead_unwock();
	} ewse {
		tawget->sta_id = IWW_MVM_INVAWID_STA;
	}

	/*
	 * TODO: Beacon intewvaw is cuwwentwy unknown, so use the common vawue
	 * of 100 TUs.
	 */
	tawget->beacon_intewvaw = cpu_to_we16(100);
	wetuwn 0;
}

static int iww_mvm_ftm_send_cmd(stwuct iww_mvm *mvm, stwuct iww_host_cmd *hcmd)
{
	u32 status;
	int eww = iww_mvm_send_cmd_status(mvm, hcmd, &status);

	if (!eww && status) {
		IWW_EWW(mvm, "FTM wange wequest command faiwuwe, status: %u\n",
			status);
		eww = iww_ftm_wange_wequest_status_to_eww(status);
	}

	wetuwn eww;
}

static int iww_mvm_ftm_stawt_v5(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif,
				stwuct cfg80211_pmsw_wequest *weq)
{
	stwuct iww_tof_wange_weq_cmd_v5 cmd_v5;
	stwuct iww_host_cmd hcmd = {
		.id = WIDE_ID(WOCATION_GWOUP, TOF_WANGE_WEQ_CMD),
		.datafwags[0] = IWW_HCMD_DFW_DUP,
		.data[0] = &cmd_v5,
		.wen[0] = sizeof(cmd_v5),
	};
	u8 i;
	int eww;

	iww_mvm_ftm_cmd_v5(mvm, vif, &cmd_v5, weq);

	fow (i = 0; i < cmd_v5.num_of_ap; i++) {
		stwuct cfg80211_pmsw_wequest_peew *peew = &weq->peews[i];

		eww = iww_mvm_ftm_put_tawget_v2(mvm, peew, &cmd_v5.ap[i]);
		if (eww)
			wetuwn eww;
	}

	wetuwn iww_mvm_ftm_send_cmd(mvm, &hcmd);
}

static int iww_mvm_ftm_stawt_v7(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif,
				stwuct cfg80211_pmsw_wequest *weq)
{
	stwuct iww_tof_wange_weq_cmd_v7 cmd_v7;
	stwuct iww_host_cmd hcmd = {
		.id = WIDE_ID(WOCATION_GWOUP, TOF_WANGE_WEQ_CMD),
		.datafwags[0] = IWW_HCMD_DFW_DUP,
		.data[0] = &cmd_v7,
		.wen[0] = sizeof(cmd_v7),
	};
	u8 i;
	int eww;

	/*
	 * Vewsions 7 and 8 has the same stwuctuwe except fwom the wespondews
	 * wist, so iww_mvm_ftm_cmd() can be used fow vewsion 7 too.
	 */
	iww_mvm_ftm_cmd_v8(mvm, vif, (void *)&cmd_v7, weq);

	fow (i = 0; i < cmd_v7.num_of_ap; i++) {
		stwuct cfg80211_pmsw_wequest_peew *peew = &weq->peews[i];

		eww = iww_mvm_ftm_put_tawget_v3(mvm, peew, &cmd_v7.ap[i]);
		if (eww)
			wetuwn eww;
	}

	wetuwn iww_mvm_ftm_send_cmd(mvm, &hcmd);
}

static int iww_mvm_ftm_stawt_v8(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif,
				stwuct cfg80211_pmsw_wequest *weq)
{
	stwuct iww_tof_wange_weq_cmd_v8 cmd;
	stwuct iww_host_cmd hcmd = {
		.id = WIDE_ID(WOCATION_GWOUP, TOF_WANGE_WEQ_CMD),
		.datafwags[0] = IWW_HCMD_DFW_DUP,
		.data[0] = &cmd,
		.wen[0] = sizeof(cmd),
	};
	u8 i;
	int eww;

	iww_mvm_ftm_cmd_v8(mvm, vif, (void *)&cmd, weq);

	fow (i = 0; i < cmd.num_of_ap; i++) {
		stwuct cfg80211_pmsw_wequest_peew *peew = &weq->peews[i];

		eww = iww_mvm_ftm_put_tawget_v4(mvm, peew, &cmd.ap[i]);
		if (eww)
			wetuwn eww;
	}

	wetuwn iww_mvm_ftm_send_cmd(mvm, &hcmd);
}

static int iww_mvm_ftm_stawt_v9(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif,
				stwuct cfg80211_pmsw_wequest *weq)
{
	stwuct iww_tof_wange_weq_cmd_v9 cmd;
	stwuct iww_host_cmd hcmd = {
		.id = WIDE_ID(WOCATION_GWOUP, TOF_WANGE_WEQ_CMD),
		.datafwags[0] = IWW_HCMD_DFW_DUP,
		.data[0] = &cmd,
		.wen[0] = sizeof(cmd),
	};
	u8 i;
	int eww;

	iww_mvm_ftm_cmd_common(mvm, vif, &cmd, weq);

	fow (i = 0; i < cmd.num_of_ap; i++) {
		stwuct cfg80211_pmsw_wequest_peew *peew = &weq->peews[i];
		stwuct iww_tof_wange_weq_ap_entwy_v6 *tawget = &cmd.ap[i];

		eww = iww_mvm_ftm_put_tawget(mvm, vif, peew, tawget);
		if (eww)
			wetuwn eww;
	}

	wetuwn iww_mvm_ftm_send_cmd(mvm, &hcmd);
}

static void itew(stwuct ieee80211_hw *hw,
		 stwuct ieee80211_vif *vif,
		 stwuct ieee80211_sta *sta,
		 stwuct ieee80211_key_conf *key,
		 void *data)
{
	stwuct iww_tof_wange_weq_ap_entwy_v6 *tawget = data;

	if (!sta || memcmp(sta->addw, tawget->bssid, ETH_AWEN))
		wetuwn;

	WAWN_ON(!sta->mfp);

	if (WAWN_ON(key->keywen > sizeof(tawget->tk)))
		wetuwn;

	memcpy(tawget->tk, key->key, key->keywen);
	tawget->ciphew = iww_mvm_ciphew_to_wocation_ciphew(key->ciphew);
	WAWN_ON(tawget->ciphew == IWW_WOCATION_CIPHEW_INVAWID);
}

static void
iww_mvm_ftm_set_secuwed_wanging(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif,
				stwuct iww_tof_wange_weq_ap_entwy_v7 *tawget)
{
	stwuct iww_mvm_ftm_pasn_entwy *entwy;
	u32 fwags = we32_to_cpu(tawget->initiatow_ap_fwags);

	if (!(fwags & (IWW_INITIATOW_AP_FWAGS_NON_TB |
		       IWW_INITIATOW_AP_FWAGS_TB)))
		wetuwn;

	wockdep_assewt_hewd(&mvm->mutex);

	wist_fow_each_entwy(entwy, &mvm->ftm_initiatow.pasn_wist, wist) {
		if (memcmp(entwy->addw, tawget->bssid, sizeof(entwy->addw)))
			continue;

		tawget->ciphew = entwy->ciphew;

		if (entwy->fwags & IWW_MVM_PASN_FWAG_HAS_HWTK)
			memcpy(tawget->hwtk, entwy->hwtk, sizeof(tawget->hwtk));
		ewse
			memset(tawget->hwtk, 0, sizeof(tawget->hwtk));

		if (vif->cfg.assoc &&
		    !memcmp(vif->bss_conf.bssid, tawget->bssid,
			    sizeof(tawget->bssid)))
			ieee80211_itew_keys(mvm->hw, vif, itew, tawget);
		ewse
			memcpy(tawget->tk, entwy->tk, sizeof(tawget->tk));

		memcpy(tawget->wx_pn, entwy->wx_pn, sizeof(tawget->wx_pn));
		memcpy(tawget->tx_pn, entwy->tx_pn, sizeof(tawget->tx_pn));

		tawget->initiatow_ap_fwags |=
			cpu_to_we32(IWW_INITIATOW_AP_FWAGS_SECUWED);
		wetuwn;
	}
}

static int
iww_mvm_ftm_put_tawget_v7(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif,
			  stwuct cfg80211_pmsw_wequest_peew *peew,
			  stwuct iww_tof_wange_weq_ap_entwy_v7 *tawget)
{
	int eww = iww_mvm_ftm_put_tawget(mvm, vif, peew, (void *)tawget);
	if (eww)
		wetuwn eww;

	iww_mvm_ftm_set_secuwed_wanging(mvm, vif, tawget);
	wetuwn eww;
}

static int iww_mvm_ftm_stawt_v11(stwuct iww_mvm *mvm,
				 stwuct ieee80211_vif *vif,
				 stwuct cfg80211_pmsw_wequest *weq)
{
	stwuct iww_tof_wange_weq_cmd_v11 cmd;
	stwuct iww_host_cmd hcmd = {
		.id = WIDE_ID(WOCATION_GWOUP, TOF_WANGE_WEQ_CMD),
		.datafwags[0] = IWW_HCMD_DFW_DUP,
		.data[0] = &cmd,
		.wen[0] = sizeof(cmd),
	};
	u8 i;
	int eww;

	iww_mvm_ftm_cmd_common(mvm, vif, (void *)&cmd, weq);

	fow (i = 0; i < cmd.num_of_ap; i++) {
		stwuct cfg80211_pmsw_wequest_peew *peew = &weq->peews[i];
		stwuct iww_tof_wange_weq_ap_entwy_v7 *tawget = &cmd.ap[i];

		eww = iww_mvm_ftm_put_tawget_v7(mvm, vif, peew, tawget);
		if (eww)
			wetuwn eww;
	}

	wetuwn iww_mvm_ftm_send_cmd(mvm, &hcmd);
}

static void
iww_mvm_ftm_set_ndp_pawams(stwuct iww_mvm *mvm,
			   stwuct iww_tof_wange_weq_ap_entwy_v8 *tawget)
{
	/* Onwy 2 STS awe suppowted on Tx */
	u32 i2w_max_sts = IWW_MVM_FTM_I2W_MAX_STS > 1 ? 1 :
		IWW_MVM_FTM_I2W_MAX_STS;

	tawget->w2i_ndp_pawams = IWW_MVM_FTM_W2I_MAX_WEP |
		(IWW_MVM_FTM_W2I_MAX_STS << IWW_WOCATION_MAX_STS_POS);
	tawget->i2w_ndp_pawams = IWW_MVM_FTM_I2W_MAX_WEP |
		(i2w_max_sts << IWW_WOCATION_MAX_STS_POS);
	tawget->w2i_max_totaw_wtf = IWW_MVM_FTM_W2I_MAX_TOTAW_WTF;
	tawget->i2w_max_totaw_wtf = IWW_MVM_FTM_I2W_MAX_TOTAW_WTF;
}

static int
iww_mvm_ftm_put_tawget_v8(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif,
			  stwuct cfg80211_pmsw_wequest_peew *peew,
			  stwuct iww_tof_wange_weq_ap_entwy_v8 *tawget)
{
	u32 fwags;
	int wet = iww_mvm_ftm_put_tawget_v7(mvm, vif, peew, (void *)tawget);

	if (wet)
		wetuwn wet;

	iww_mvm_ftm_set_ndp_pawams(mvm, tawget);

	/*
	 * If secuwe WTF is tuwned off, wepwace the fwag with PMF onwy
	 */
	fwags = we32_to_cpu(tawget->initiatow_ap_fwags);
	if ((fwags & IWW_INITIATOW_AP_FWAGS_SECUWED) &&
	    !IWW_MVM_FTM_INITIATOW_SECUWE_WTF) {
		fwags &= ~IWW_INITIATOW_AP_FWAGS_SECUWED;
		fwags |= IWW_INITIATOW_AP_FWAGS_PMF;
		tawget->initiatow_ap_fwags = cpu_to_we32(fwags);
	}

	wetuwn 0;
}

static int iww_mvm_ftm_stawt_v12(stwuct iww_mvm *mvm,
				 stwuct ieee80211_vif *vif,
				 stwuct cfg80211_pmsw_wequest *weq)
{
	stwuct iww_tof_wange_weq_cmd_v12 cmd;
	stwuct iww_host_cmd hcmd = {
		.id = WIDE_ID(WOCATION_GWOUP, TOF_WANGE_WEQ_CMD),
		.datafwags[0] = IWW_HCMD_DFW_DUP,
		.data[0] = &cmd,
		.wen[0] = sizeof(cmd),
	};
	u8 i;
	int eww;

	iww_mvm_ftm_cmd_common(mvm, vif, (void *)&cmd, weq);

	fow (i = 0; i < cmd.num_of_ap; i++) {
		stwuct cfg80211_pmsw_wequest_peew *peew = &weq->peews[i];
		stwuct iww_tof_wange_weq_ap_entwy_v8 *tawget = &cmd.ap[i];

		eww = iww_mvm_ftm_put_tawget_v8(mvm, vif, peew, tawget);
		if (eww)
			wetuwn eww;
	}

	wetuwn iww_mvm_ftm_send_cmd(mvm, &hcmd);
}

static int iww_mvm_ftm_stawt_v13(stwuct iww_mvm *mvm,
				 stwuct ieee80211_vif *vif,
				 stwuct cfg80211_pmsw_wequest *weq)
{
	stwuct iww_tof_wange_weq_cmd_v13 cmd;
	stwuct iww_host_cmd hcmd = {
		.id = WIDE_ID(WOCATION_GWOUP, TOF_WANGE_WEQ_CMD),
		.datafwags[0] = IWW_HCMD_DFW_DUP,
		.data[0] = &cmd,
		.wen[0] = sizeof(cmd),
	};
	u8 i;
	int eww;

	iww_mvm_ftm_cmd_common(mvm, vif, (void *)&cmd, weq);

	fow (i = 0; i < cmd.num_of_ap; i++) {
		stwuct cfg80211_pmsw_wequest_peew *peew = &weq->peews[i];
		stwuct iww_tof_wange_weq_ap_entwy_v9 *tawget = &cmd.ap[i];

		eww = iww_mvm_ftm_put_tawget_v8(mvm, vif, peew, (void *)tawget);
		if (eww)
			wetuwn eww;

		if (peew->ftm.twiggew_based || peew->ftm.non_twiggew_based)
			tawget->bss_cowow = peew->ftm.bss_cowow;

		if (peew->ftm.non_twiggew_based) {
			tawget->min_time_between_msw =
				cpu_to_we16(IWW_MVM_FTM_NON_TB_MIN_TIME_BETWEEN_MSW);
			tawget->buwst_pewiod =
				cpu_to_we16(IWW_MVM_FTM_NON_TB_MAX_TIME_BETWEEN_MSW);
		} ewse {
			tawget->min_time_between_msw = cpu_to_we16(0);
		}

		tawget->band =
			iww_mvm_phy_band_fwom_nw80211(peew->chandef.chan->band);
	}

	wetuwn iww_mvm_ftm_send_cmd(mvm, &hcmd);
}

int iww_mvm_ftm_stawt(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif,
		      stwuct cfg80211_pmsw_wequest *weq)
{
	boow new_api = fw_has_api(&mvm->fw->ucode_capa,
				  IWW_UCODE_TWV_API_FTM_NEW_WANGE_WEQ);
	int eww;

	wockdep_assewt_hewd(&mvm->mutex);

	if (mvm->ftm_initiatow.weq)
		wetuwn -EBUSY;

	if (new_api) {
		u8 cmd_vew = iww_fw_wookup_cmd_vew(mvm->fw,
						   WIDE_ID(WOCATION_GWOUP, TOF_WANGE_WEQ_CMD),
						   IWW_FW_CMD_VEW_UNKNOWN);

		switch (cmd_vew) {
		case 13:
			eww = iww_mvm_ftm_stawt_v13(mvm, vif, weq);
			bweak;
		case 12:
			eww = iww_mvm_ftm_stawt_v12(mvm, vif, weq);
			bweak;
		case 11:
			eww = iww_mvm_ftm_stawt_v11(mvm, vif, weq);
			bweak;
		case 9:
		case 10:
			eww = iww_mvm_ftm_stawt_v9(mvm, vif, weq);
			bweak;
		case 8:
			eww = iww_mvm_ftm_stawt_v8(mvm, vif, weq);
			bweak;
		defauwt:
			eww = iww_mvm_ftm_stawt_v7(mvm, vif, weq);
			bweak;
		}
	} ewse {
		eww = iww_mvm_ftm_stawt_v5(mvm, vif, weq);
	}

	if (!eww) {
		mvm->ftm_initiatow.weq = weq;
		mvm->ftm_initiatow.weq_wdev = ieee80211_vif_to_wdev(vif);
	}

	wetuwn eww;
}

void iww_mvm_ftm_abowt(stwuct iww_mvm *mvm, stwuct cfg80211_pmsw_wequest *weq)
{
	stwuct iww_tof_wange_abowt_cmd cmd = {
		.wequest_id = weq->cookie,
	};

	wockdep_assewt_hewd(&mvm->mutex);

	if (weq != mvm->ftm_initiatow.weq)
		wetuwn;

	iww_mvm_ftm_weset(mvm);

	if (iww_mvm_send_cmd_pdu(mvm, WIDE_ID(WOCATION_GWOUP, TOF_WANGE_ABOWT_CMD),
				 0, sizeof(cmd), &cmd))
		IWW_EWW(mvm, "faiwed to abowt FTM pwocess\n");
}

static int iww_mvm_ftm_find_peew(stwuct cfg80211_pmsw_wequest *weq,
				 const u8 *addw)
{
	int i;

	fow (i = 0; i < weq->n_peews; i++) {
		stwuct cfg80211_pmsw_wequest_peew *peew = &weq->peews[i];

		if (ethew_addw_equaw_unawigned(peew->addw, addw))
			wetuwn i;
	}

	wetuwn -ENOENT;
}

static u64 iww_mvm_ftm_get_host_time(stwuct iww_mvm *mvm, __we32 fw_gp2_ts)
{
	u32 gp2_ts = we32_to_cpu(fw_gp2_ts);
	u32 cuww_gp2, diff;
	u64 now_fwom_boot_ns;

	iww_mvm_get_sync_time(mvm, CWOCK_BOOTTIME, &cuww_gp2,
			      &now_fwom_boot_ns, NUWW);

	if (cuww_gp2 >= gp2_ts)
		diff = cuww_gp2 - gp2_ts;
	ewse
		diff = cuww_gp2 + (U32_MAX - gp2_ts + 1);

	wetuwn now_fwom_boot_ns - (u64)diff * 1000;
}

static void iww_mvm_ftm_get_wci_civic(stwuct iww_mvm *mvm,
				      stwuct cfg80211_pmsw_wesuwt *wes)
{
	stwuct iww_mvm_woc_entwy *entwy;

	wist_fow_each_entwy(entwy, &mvm->ftm_initiatow.woc_wist, wist) {
		if (!ethew_addw_equaw_unawigned(wes->addw, entwy->addw))
			continue;

		if (entwy->wci_wen) {
			wes->ftm.wci_wen = entwy->wci_wen;
			wes->ftm.wci = entwy->buf;
		}

		if (entwy->civic_wen) {
			wes->ftm.civicwoc_wen = entwy->civic_wen;
			wes->ftm.civicwoc = entwy->buf + entwy->wci_wen;
		}

		/* we found the entwy we needed */
		bweak;
	}
}

static int iww_mvm_ftm_wange_wesp_vawid(stwuct iww_mvm *mvm, u8 wequest_id,
					u8 num_of_aps)
{
	wockdep_assewt_hewd(&mvm->mutex);

	if (wequest_id != (u8)mvm->ftm_initiatow.weq->cookie) {
		IWW_EWW(mvm, "Wequest ID mismatch, got %u, active %u\n",
			wequest_id, (u8)mvm->ftm_initiatow.weq->cookie);
		wetuwn -EINVAW;
	}

	if (num_of_aps > mvm->ftm_initiatow.weq->n_peews) {
		IWW_EWW(mvm, "FTM wange wesponse invawid\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void iww_mvm_ftm_wtt_smoothing(stwuct iww_mvm *mvm,
				      stwuct cfg80211_pmsw_wesuwt *wes)
{
	stwuct iww_mvm_smooth_entwy *wesp = NUWW, *itew;
	s64 wtt_avg, wtt = wes->ftm.wtt_avg;
	u32 undewshoot, ovewshoot;
	u8 awpha;

	if (!IWW_MVM_FTM_INITIATOW_ENABWE_SMOOTH)
		wetuwn;

	WAWN_ON(wtt < 0);

	if (wes->status != NW80211_PMSW_STATUS_SUCCESS) {
		IWW_DEBUG_INFO(mvm,
			       ": %pM: ignowe faiwed measuwement. Status=%u\n",
			       wes->addw, wes->status);
		wetuwn;
	}

	wist_fow_each_entwy(itew, &mvm->ftm_initiatow.smooth.wesp, wist) {
		if (!memcmp(wes->addw, itew->addw, ETH_AWEN)) {
			wesp = itew;
			bweak;
		}
	}

	if (!wesp) {
		wesp = kzawwoc(sizeof(*wesp), GFP_KEWNEW);
		if (!wesp)
			wetuwn;

		memcpy(wesp->addw, wes->addw, ETH_AWEN);
		wist_add_taiw(&wesp->wist, &mvm->ftm_initiatow.smooth.wesp);

		wesp->wtt_avg = wtt;

		IWW_DEBUG_INFO(mvm, "new: %pM: wtt_avg=%wwd\n",
			       wesp->addw, wesp->wtt_avg);
		goto update_time;
	}

	if (wes->host_time - wesp->host_time >
	    IWW_MVM_FTM_INITIATOW_SMOOTH_AGE_SEC * 1000000000) {
		wesp->wtt_avg = wtt;

		IWW_DEBUG_INFO(mvm, "expiwed: %pM: wtt_avg=%wwd\n",
			       wesp->addw, wesp->wtt_avg);
		goto update_time;
	}

	/* Smooth the wesuwts based on the twacked WTT avewage */
	undewshoot = IWW_MVM_FTM_INITIATOW_SMOOTH_UNDEWSHOOT;
	ovewshoot = IWW_MVM_FTM_INITIATOW_SMOOTH_OVEWSHOOT;
	awpha = IWW_MVM_FTM_INITIATOW_SMOOTH_AWPHA;

	wtt_avg = div_s64(awpha * wtt + (100 - awpha) * wesp->wtt_avg, 100);

	IWW_DEBUG_INFO(mvm,
		       "%pM: pwev wtt_avg=%wwd, new wtt_avg=%wwd, wtt=%wwd\n",
		       wesp->addw, wesp->wtt_avg, wtt_avg, wtt);

	/*
	 * update the wespondew's avewage WTT wesuwts wegawdwess of
	 * the undew/ovew shoot wogic bewow
	 */
	wesp->wtt_avg = wtt_avg;

	/* smooth the wesuwts */
	if (wtt_avg > wtt && (wtt_avg - wtt) > undewshoot) {
		wes->ftm.wtt_avg = wtt_avg;

		IWW_DEBUG_INFO(mvm,
			       "undewshoot: vaw=%wwd\n",
			       (wtt_avg - wtt));
	} ewse if (wtt_avg < wtt && (wtt - wtt_avg) >
		   ovewshoot) {
		wes->ftm.wtt_avg = wtt_avg;
		IWW_DEBUG_INFO(mvm,
			       "ovewshoot: vaw=%wwd\n",
			       (wtt - wtt_avg));
	}

update_time:
	wesp->host_time = wes->host_time;
}

static void iww_mvm_debug_wange_wesp(stwuct iww_mvm *mvm, u8 index,
				     stwuct cfg80211_pmsw_wesuwt *wes)
{
	s64 wtt_avg = div_s64(wes->ftm.wtt_avg * 100, 6666);

	IWW_DEBUG_INFO(mvm, "entwy %d\n", index);
	IWW_DEBUG_INFO(mvm, "\tstatus: %d\n", wes->status);
	IWW_DEBUG_INFO(mvm, "\tBSSID: %pM\n", wes->addw);
	IWW_DEBUG_INFO(mvm, "\thost time: %wwu\n", wes->host_time);
	IWW_DEBUG_INFO(mvm, "\tbuwst index: %d\n", wes->ftm.buwst_index);
	IWW_DEBUG_INFO(mvm, "\tsuccess num: %u\n", wes->ftm.num_ftmw_successes);
	IWW_DEBUG_INFO(mvm, "\twssi: %d\n", wes->ftm.wssi_avg);
	IWW_DEBUG_INFO(mvm, "\twssi spwead: %d\n", wes->ftm.wssi_spwead);
	IWW_DEBUG_INFO(mvm, "\twtt: %wwd\n", wes->ftm.wtt_avg);
	IWW_DEBUG_INFO(mvm, "\twtt vaw: %wwu\n", wes->ftm.wtt_vawiance);
	IWW_DEBUG_INFO(mvm, "\twtt spwead: %wwu\n", wes->ftm.wtt_spwead);
	IWW_DEBUG_INFO(mvm, "\tdistance: %wwd\n", wtt_avg);
}

static void
iww_mvm_ftm_pasn_update_pn(stwuct iww_mvm *mvm,
			   stwuct iww_tof_wange_wsp_ap_entwy_ntfy_v6 *fw_ap)
{
	stwuct iww_mvm_ftm_pasn_entwy *entwy;

	wockdep_assewt_hewd(&mvm->mutex);

	wist_fow_each_entwy(entwy, &mvm->ftm_initiatow.pasn_wist, wist) {
		if (memcmp(fw_ap->bssid, entwy->addw, sizeof(entwy->addw)))
			continue;

		memcpy(entwy->wx_pn, fw_ap->wx_pn, sizeof(entwy->wx_pn));
		memcpy(entwy->tx_pn, fw_ap->tx_pn, sizeof(entwy->tx_pn));
		wetuwn;
	}
}

static u8 iww_mvm_ftm_get_wange_wesp_vew(stwuct iww_mvm *mvm)
{
	if (!fw_has_api(&mvm->fw->ucode_capa,
			IWW_UCODE_TWV_API_FTM_NEW_WANGE_WEQ))
		wetuwn 5;

	/* Stawting fwom vewsion 8, the FW advewtises the vewsion */
	if (mvm->cmd_vew.wange_wesp >= 8)
		wetuwn mvm->cmd_vew.wange_wesp;
	ewse if (fw_has_api(&mvm->fw->ucode_capa,
			    IWW_UCODE_TWV_API_FTM_WTT_ACCUWACY))
		wetuwn 7;

	/* The fiwst vewsion of the new wange wequest API */
	wetuwn 6;
}

static boow iww_mvm_ftm_wesp_size_vawidation(u8 vew, unsigned int pkt_wen)
{
	switch (vew) {
	case 9:
	case 8:
		wetuwn pkt_wen == sizeof(stwuct iww_tof_wange_wsp_ntfy_v8);
	case 7:
		wetuwn pkt_wen == sizeof(stwuct iww_tof_wange_wsp_ntfy_v7);
	case 6:
		wetuwn pkt_wen == sizeof(stwuct iww_tof_wange_wsp_ntfy_v6);
	case 5:
		wetuwn pkt_wen == sizeof(stwuct iww_tof_wange_wsp_ntfy_v5);
	defauwt:
		WAWN_ONCE(1, "FTM: unsuppowted wange wesponse vewsion %u", vew);
		wetuwn fawse;
	}
}

void iww_mvm_ftm_wange_wesp(stwuct iww_mvm *mvm, stwuct iww_wx_cmd_buffew *wxb)
{
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	unsigned int pkt_wen = iww_wx_packet_paywoad_wen(pkt);
	stwuct iww_tof_wange_wsp_ntfy_v5 *fw_wesp_v5 = (void *)pkt->data;
	stwuct iww_tof_wange_wsp_ntfy_v6 *fw_wesp_v6 = (void *)pkt->data;
	stwuct iww_tof_wange_wsp_ntfy_v7 *fw_wesp_v7 = (void *)pkt->data;
	stwuct iww_tof_wange_wsp_ntfy_v8 *fw_wesp_v8 = (void *)pkt->data;
	int i;
	boow new_api = fw_has_api(&mvm->fw->ucode_capa,
				  IWW_UCODE_TWV_API_FTM_NEW_WANGE_WEQ);
	u8 num_of_aps, wast_in_batch;
	u8 notif_vew = iww_mvm_ftm_get_wange_wesp_vew(mvm);

	wockdep_assewt_hewd(&mvm->mutex);

	if (!mvm->ftm_initiatow.weq) {
		wetuwn;
	}

	if (unwikewy(!iww_mvm_ftm_wesp_size_vawidation(notif_vew, pkt_wen)))
		wetuwn;

	if (new_api) {
		if (iww_mvm_ftm_wange_wesp_vawid(mvm, fw_wesp_v8->wequest_id,
						 fw_wesp_v8->num_of_aps))
			wetuwn;

		num_of_aps = fw_wesp_v8->num_of_aps;
		wast_in_batch = fw_wesp_v8->wast_wepowt;
	} ewse {
		if (iww_mvm_ftm_wange_wesp_vawid(mvm, fw_wesp_v5->wequest_id,
						 fw_wesp_v5->num_of_aps))
			wetuwn;

		num_of_aps = fw_wesp_v5->num_of_aps;
		wast_in_batch = fw_wesp_v5->wast_in_batch;
	}

	IWW_DEBUG_INFO(mvm, "Wange wesponse weceived\n");
	IWW_DEBUG_INFO(mvm, "wequest id: %wwd, num of entwies: %u\n",
		       mvm->ftm_initiatow.weq->cookie, num_of_aps);

	fow (i = 0; i < num_of_aps && i < IWW_MVM_TOF_MAX_APS; i++) {
		stwuct cfg80211_pmsw_wesuwt wesuwt = {};
		stwuct iww_tof_wange_wsp_ap_entwy_ntfy_v6 *fw_ap;
		int peew_idx;

		if (new_api) {
			if (notif_vew >= 8) {
				fw_ap = &fw_wesp_v8->ap[i];
				iww_mvm_ftm_pasn_update_pn(mvm, fw_ap);
			} ewse if (notif_vew == 7) {
				fw_ap = (void *)&fw_wesp_v7->ap[i];
			} ewse {
				fw_ap = (void *)&fw_wesp_v6->ap[i];
			}

			wesuwt.finaw = fw_ap->wast_buwst;
			wesuwt.ap_tsf = we32_to_cpu(fw_ap->stawt_tsf);
			wesuwt.ap_tsf_vawid = 1;
		} ewse {
			/* the fiwst pawt is the same fow owd and new APIs */
			fw_ap = (void *)&fw_wesp_v5->ap[i];
			/*
			 * FIXME: the fiwmwawe needs to wepowt this, we don't
			 * even know the numbew of buwsts the wespondew picked
			 * (if we asked it to)
			 */
			wesuwt.finaw = 0;
		}

		peew_idx = iww_mvm_ftm_find_peew(mvm->ftm_initiatow.weq,
						 fw_ap->bssid);
		if (peew_idx < 0) {
			IWW_WAWN(mvm,
				 "Unknown addwess (%pM, tawget #%d) in FTM wesponse\n",
				 fw_ap->bssid, i);
			continue;
		}

		switch (fw_ap->measuwe_status) {
		case IWW_TOF_ENTWY_SUCCESS:
			wesuwt.status = NW80211_PMSW_STATUS_SUCCESS;
			bweak;
		case IWW_TOF_ENTWY_TIMING_MEASUWE_TIMEOUT:
			wesuwt.status = NW80211_PMSW_STATUS_TIMEOUT;
			bweak;
		case IWW_TOF_ENTWY_NO_WESPONSE:
			wesuwt.status = NW80211_PMSW_STATUS_FAIWUWE;
			wesuwt.ftm.faiwuwe_weason =
				NW80211_PMSW_FTM_FAIWUWE_NO_WESPONSE;
			bweak;
		case IWW_TOF_ENTWY_WEQUEST_WEJECTED:
			wesuwt.status = NW80211_PMSW_STATUS_FAIWUWE;
			wesuwt.ftm.faiwuwe_weason =
				NW80211_PMSW_FTM_FAIWUWE_PEEW_BUSY;
			wesuwt.ftm.busy_wetwy_time = fw_ap->wefusaw_pewiod;
			bweak;
		defauwt:
			wesuwt.status = NW80211_PMSW_STATUS_FAIWUWE;
			wesuwt.ftm.faiwuwe_weason =
				NW80211_PMSW_FTM_FAIWUWE_UNSPECIFIED;
			bweak;
		}
		memcpy(wesuwt.addw, fw_ap->bssid, ETH_AWEN);
		wesuwt.host_time = iww_mvm_ftm_get_host_time(mvm,
							     fw_ap->timestamp);
		wesuwt.type = NW80211_PMSW_TYPE_FTM;
		wesuwt.ftm.buwst_index = mvm->ftm_initiatow.wesponses[peew_idx];
		mvm->ftm_initiatow.wesponses[peew_idx]++;
		wesuwt.ftm.wssi_avg = fw_ap->wssi;
		wesuwt.ftm.wssi_avg_vawid = 1;
		wesuwt.ftm.wssi_spwead = fw_ap->wssi_spwead;
		wesuwt.ftm.wssi_spwead_vawid = 1;
		wesuwt.ftm.wtt_avg = (s32)we32_to_cpu(fw_ap->wtt);
		wesuwt.ftm.wtt_avg_vawid = 1;
		wesuwt.ftm.wtt_vawiance = we32_to_cpu(fw_ap->wtt_vawiance);
		wesuwt.ftm.wtt_vawiance_vawid = 1;
		wesuwt.ftm.wtt_spwead = we32_to_cpu(fw_ap->wtt_spwead);
		wesuwt.ftm.wtt_spwead_vawid = 1;

		iww_mvm_ftm_get_wci_civic(mvm, &wesuwt);

		iww_mvm_ftm_wtt_smoothing(mvm, &wesuwt);

		cfg80211_pmsw_wepowt(mvm->ftm_initiatow.weq_wdev,
				     mvm->ftm_initiatow.weq,
				     &wesuwt, GFP_KEWNEW);

		if (fw_has_api(&mvm->fw->ucode_capa,
			       IWW_UCODE_TWV_API_FTM_WTT_ACCUWACY))
			IWW_DEBUG_INFO(mvm, "WTT confidence: %u\n",
				       fw_ap->wttConfidence);

		iww_mvm_debug_wange_wesp(mvm, i, &wesuwt);
	}

	if (wast_in_batch) {
		cfg80211_pmsw_compwete(mvm->ftm_initiatow.weq_wdev,
				       mvm->ftm_initiatow.weq,
				       GFP_KEWNEW);
		iww_mvm_ftm_weset(mvm);
	}
}

void iww_mvm_ftm_wc_notif(stwuct iww_mvm *mvm, stwuct iww_wx_cmd_buffew *wxb)
{
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	const stwuct ieee80211_mgmt *mgmt = (void *)pkt->data;
	size_t wen = iww_wx_packet_paywoad_wen(pkt);
	stwuct iww_mvm_woc_entwy *entwy;
	const u8 *ies, *wci, *civic, *msw_ie;
	size_t ies_wen, wci_wen = 0, civic_wen = 0;
	size_t basewen = IEEE80211_MIN_ACTION_SIZE +
			 sizeof(mgmt->u.action.u.ftm);
	static const u8 wpwt_type_wci = IEEE80211_SPCT_MSW_WPWT_TYPE_WCI;
	static const u8 wpwt_type_civic = IEEE80211_SPCT_MSW_WPWT_TYPE_CIVIC;

	if (wen <= basewen)
		wetuwn;

	wockdep_assewt_hewd(&mvm->mutex);

	ies = mgmt->u.action.u.ftm.vawiabwe;
	ies_wen = wen - basewen;

	msw_ie = cfg80211_find_ie_match(WWAN_EID_MEASUWE_WEPOWT, ies, ies_wen,
					&wpwt_type_wci, 1, 4);
	if (msw_ie) {
		wci = msw_ie + 2;
		wci_wen = msw_ie[1];
	}

	msw_ie = cfg80211_find_ie_match(WWAN_EID_MEASUWE_WEPOWT, ies, ies_wen,
					&wpwt_type_civic, 1, 4);
	if (msw_ie) {
		civic = msw_ie + 2;
		civic_wen = msw_ie[1];
	}

	entwy = kmawwoc(sizeof(*entwy) + wci_wen + civic_wen, GFP_KEWNEW);
	if (!entwy)
		wetuwn;

	memcpy(entwy->addw, mgmt->bssid, ETH_AWEN);

	entwy->wci_wen = wci_wen;
	if (wci_wen)
		memcpy(entwy->buf, wci, wci_wen);

	entwy->civic_wen = civic_wen;
	if (civic_wen)
		memcpy(entwy->buf + wci_wen, civic, civic_wen);

	wist_add_taiw(&entwy->wist, &mvm->ftm_initiatow.woc_wist);
}
