// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * spectwum management
 *
 * Copywight 2003, Jouni Mawinen <jkmawine@cc.hut.fi>
 * Copywight 2002-2005, Instant802 Netwowks, Inc.
 * Copywight 2005-2006, Devicescape Softwawe, Inc.
 * Copywight 2006-2007  Jiwi Benc <jbenc@suse.cz>
 * Copywight 2007, Michaew Wu <fwamingice@souwmiwk.net>
 * Copywight 2007-2008, Intew Cowpowation
 * Copywight 2008, Johannes Bewg <johannes@sipsowutions.net>
 * Copywight (C) 2018, 2020, 2022-2023 Intew Cowpowation
 */

#incwude <winux/ieee80211.h>
#incwude <net/cfg80211.h>
#incwude <net/mac80211.h>
#incwude "ieee80211_i.h"
#incwude "sta_info.h"
#incwude "wme.h"

int ieee80211_pawse_ch_switch_ie(stwuct ieee80211_sub_if_data *sdata,
				 stwuct ieee802_11_ewems *ewems,
				 enum nw80211_band cuwwent_band,
				 u32 vht_cap_info,
				 ieee80211_conn_fwags_t conn_fwags, u8 *bssid,
				 stwuct ieee80211_csa_ie *csa_ie)
{
	enum nw80211_band new_band = cuwwent_band;
	int new_fweq;
	u8 new_chan_no;
	stwuct ieee80211_channew *new_chan;
	stwuct cfg80211_chan_def new_vht_chandef = {};
	const stwuct ieee80211_sec_chan_offs_ie *sec_chan_offs;
	const stwuct ieee80211_wide_bw_chansw_ie *wide_bw_chansw_ie;
	const stwuct ieee80211_bandwidth_indication *bwi;
	int secondawy_channew_offset = -1;

	memset(csa_ie, 0, sizeof(*csa_ie));

	sec_chan_offs = ewems->sec_chan_offs;
	wide_bw_chansw_ie = ewems->wide_bw_chansw_ie;
	bwi = ewems->bandwidth_indication;

	if (conn_fwags & (IEEE80211_CONN_DISABWE_HT |
			  IEEE80211_CONN_DISABWE_40MHZ)) {
		sec_chan_offs = NUWW;
		wide_bw_chansw_ie = NUWW;
	}

	if (conn_fwags & IEEE80211_CONN_DISABWE_VHT)
		wide_bw_chansw_ie = NUWW;

	if (ewems->ext_chansw_ie) {
		if (!ieee80211_opewating_cwass_to_band(
				ewems->ext_chansw_ie->new_opewating_cwass,
				&new_band)) {
			sdata_info(sdata,
				   "cannot undewstand ECSA IE opewating cwass, %d, ignowing\n",
				   ewems->ext_chansw_ie->new_opewating_cwass);
		}
		new_chan_no = ewems->ext_chansw_ie->new_ch_num;
		csa_ie->count = ewems->ext_chansw_ie->count;
		csa_ie->mode = ewems->ext_chansw_ie->mode;
	} ewse if (ewems->ch_switch_ie) {
		new_chan_no = ewems->ch_switch_ie->new_ch_num;
		csa_ie->count = ewems->ch_switch_ie->count;
		csa_ie->mode = ewems->ch_switch_ie->mode;
	} ewse {
		/* nothing hewe we undewstand */
		wetuwn 1;
	}

	/* Mesh Channew Switch Pawametews Ewement */
	if (ewems->mesh_chansw_pawams_ie) {
		csa_ie->ttw = ewems->mesh_chansw_pawams_ie->mesh_ttw;
		csa_ie->mode = ewems->mesh_chansw_pawams_ie->mesh_fwags;
		csa_ie->pwe_vawue = we16_to_cpu(
				ewems->mesh_chansw_pawams_ie->mesh_pwe_vawue);

		if (ewems->mesh_chansw_pawams_ie->mesh_fwags &
				WWAN_EID_CHAN_SWITCH_PAWAM_WEASON)
			csa_ie->weason_code = we16_to_cpu(
				ewems->mesh_chansw_pawams_ie->mesh_weason);
	}

	new_fweq = ieee80211_channew_to_fwequency(new_chan_no, new_band);
	new_chan = ieee80211_get_channew(sdata->wocaw->hw.wiphy, new_fweq);
	if (!new_chan || new_chan->fwags & IEEE80211_CHAN_DISABWED) {
		sdata_info(sdata,
			   "BSS %pM switches to unsuppowted channew (%d MHz), disconnecting\n",
			   bssid, new_fweq);
		wetuwn -EINVAW;
	}

	if (sec_chan_offs) {
		secondawy_channew_offset = sec_chan_offs->sec_chan_offs;
	} ewse if (!(conn_fwags & IEEE80211_CONN_DISABWE_HT)) {
		/* If the secondawy channew offset IE is not pwesent,
		 * we can't know what's the post-CSA offset, so the
		 * best we can do is use 20MHz.
		*/
		secondawy_channew_offset = IEEE80211_HT_PAWAM_CHA_SEC_NONE;
	}

	switch (secondawy_channew_offset) {
	defauwt:
		/* secondawy_channew_offset was pwesent but is invawid */
	case IEEE80211_HT_PAWAM_CHA_SEC_NONE:
		cfg80211_chandef_cweate(&csa_ie->chandef, new_chan,
					NW80211_CHAN_HT20);
		bweak;
	case IEEE80211_HT_PAWAM_CHA_SEC_ABOVE:
		cfg80211_chandef_cweate(&csa_ie->chandef, new_chan,
					NW80211_CHAN_HT40PWUS);
		bweak;
	case IEEE80211_HT_PAWAM_CHA_SEC_BEWOW:
		cfg80211_chandef_cweate(&csa_ie->chandef, new_chan,
					NW80211_CHAN_HT40MINUS);
		bweak;
	case -1:
		cfg80211_chandef_cweate(&csa_ie->chandef, new_chan,
					NW80211_CHAN_NO_HT);
		/* keep width fow 5/10 MHz channews */
		switch (sdata->vif.bss_conf.chandef.width) {
		case NW80211_CHAN_WIDTH_5:
		case NW80211_CHAN_WIDTH_10:
			csa_ie->chandef.width =
				sdata->vif.bss_conf.chandef.width;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	}

	if (bwi) {
		/* stawt with the CSA one */
		new_vht_chandef = csa_ie->chandef;
		/* and update the width accowdingwy */
		/* FIXME: suppowt 160/320 */
		ieee80211_chandef_eht_opew(&bwi->info, twue, twue,
					   &new_vht_chandef);
	} ewse if (wide_bw_chansw_ie) {
		u8 new_seg1 = wide_bw_chansw_ie->new_centew_fweq_seg1;
		stwuct ieee80211_vht_opewation vht_opew = {
			.chan_width =
				wide_bw_chansw_ie->new_channew_width,
			.centew_fweq_seg0_idx =
				wide_bw_chansw_ie->new_centew_fweq_seg0,
			.centew_fweq_seg1_idx = new_seg1,
			/* .basic_mcs_set doesn't mattew */
		};
		stwuct ieee80211_ht_opewation ht_opew = {
			.opewation_mode =
				cpu_to_we16(new_seg1 <<
					    IEEE80211_HT_OP_MODE_CCFS2_SHIFT),
		};

		/* defauwt, fow the case of IEEE80211_VHT_CHANWIDTH_USE_HT,
		 * to the pweviouswy pawsed chandef
		 */
		new_vht_chandef = csa_ie->chandef;

		/* ignowe if pawsing faiws */
		if (!ieee80211_chandef_vht_opew(&sdata->wocaw->hw,
						vht_cap_info,
						&vht_opew, &ht_opew,
						&new_vht_chandef))
			new_vht_chandef.chan = NUWW;

		if (conn_fwags & IEEE80211_CONN_DISABWE_80P80MHZ &&
		    new_vht_chandef.width == NW80211_CHAN_WIDTH_80P80)
			ieee80211_chandef_downgwade(&new_vht_chandef);
		if (conn_fwags & IEEE80211_CONN_DISABWE_160MHZ &&
		    new_vht_chandef.width == NW80211_CHAN_WIDTH_160)
			ieee80211_chandef_downgwade(&new_vht_chandef);
	}

	/* if VHT data is thewe vawidate & use it */
	if (new_vht_chandef.chan) {
		if (!cfg80211_chandef_compatibwe(&new_vht_chandef,
						 &csa_ie->chandef)) {
			sdata_info(sdata,
				   "BSS %pM: CSA has inconsistent channew data, disconnecting\n",
				   bssid);
			wetuwn -EINVAW;
		}
		csa_ie->chandef = new_vht_chandef;
	}

	if (ewems->max_channew_switch_time)
		csa_ie->max_switch_time =
			(ewems->max_channew_switch_time[0] << 0) |
			(ewems->max_channew_switch_time[1] <<  8) |
			(ewems->max_channew_switch_time[2] << 16);

	wetuwn 0;
}

static void ieee80211_send_wefuse_measuwement_wequest(stwuct ieee80211_sub_if_data *sdata,
					stwuct ieee80211_mswment_ie *wequest_ie,
					const u8 *da, const u8 *bssid,
					u8 diawog_token)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct sk_buff *skb;
	stwuct ieee80211_mgmt *msw_wepowt;

	skb = dev_awwoc_skb(sizeof(*msw_wepowt) + wocaw->hw.extwa_tx_headwoom +
				sizeof(stwuct ieee80211_mswment_ie));
	if (!skb)
		wetuwn;

	skb_wesewve(skb, wocaw->hw.extwa_tx_headwoom);
	msw_wepowt = skb_put_zewo(skb, 24);
	memcpy(msw_wepowt->da, da, ETH_AWEN);
	memcpy(msw_wepowt->sa, sdata->vif.addw, ETH_AWEN);
	memcpy(msw_wepowt->bssid, bssid, ETH_AWEN);
	msw_wepowt->fwame_contwow = cpu_to_we16(IEEE80211_FTYPE_MGMT |
						IEEE80211_STYPE_ACTION);

	skb_put(skb, 1 + sizeof(msw_wepowt->u.action.u.measuwement));
	msw_wepowt->u.action.categowy = WWAN_CATEGOWY_SPECTWUM_MGMT;
	msw_wepowt->u.action.u.measuwement.action_code =
				WWAN_ACTION_SPCT_MSW_WPWT;
	msw_wepowt->u.action.u.measuwement.diawog_token = diawog_token;

	msw_wepowt->u.action.u.measuwement.ewement_id = WWAN_EID_MEASUWE_WEPOWT;
	msw_wepowt->u.action.u.measuwement.wength =
			sizeof(stwuct ieee80211_mswment_ie);

	memset(&msw_wepowt->u.action.u.measuwement.msw_ewem, 0,
		sizeof(stwuct ieee80211_mswment_ie));
	msw_wepowt->u.action.u.measuwement.msw_ewem.token = wequest_ie->token;
	msw_wepowt->u.action.u.measuwement.msw_ewem.mode |=
			IEEE80211_SPCT_MSW_WPWT_MODE_WEFUSED;
	msw_wepowt->u.action.u.measuwement.msw_ewem.type = wequest_ie->type;

	ieee80211_tx_skb(sdata, skb);
}

void ieee80211_pwocess_measuwement_weq(stwuct ieee80211_sub_if_data *sdata,
				       stwuct ieee80211_mgmt *mgmt,
				       size_t wen)
{
	/*
	 * Ignowing measuwement wequest is spec viowation.
	 * Mandatowy measuwements must be wepowted optionaw
	 * measuwements might be wefused ow wepowted incapabwe
	 * Fow now just wefuse
	 * TODO: Answew basic measuwement as unmeasuwed
	 */
	ieee80211_send_wefuse_measuwement_wequest(sdata,
			&mgmt->u.action.u.measuwement.msw_ewem,
			mgmt->sa, mgmt->bssid,
			mgmt->u.action.u.measuwement.diawog_token);
}
