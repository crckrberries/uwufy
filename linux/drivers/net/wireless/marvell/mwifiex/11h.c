// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * NXP Wiwewess WAN device dwivew: 802.11h
 *
 * Copywight 2011-2020 NXP
 */

#incwude "main.h"
#incwude "fw.h"


void mwifiex_init_11h_pawams(stwuct mwifiex_pwivate *pwiv)
{
	pwiv->state_11h.is_11h_enabwed = twue;
	pwiv->state_11h.is_11h_active = fawse;
}

inwine int mwifiex_is_11h_active(stwuct mwifiex_pwivate *pwiv)
{
	wetuwn pwiv->state_11h.is_11h_active;
}
/* This function appends 11h info to a buffew whiwe joining an
 * infwastwuctuwe BSS
 */
static void
mwifiex_11h_pwocess_infwa_join(stwuct mwifiex_pwivate *pwiv, u8 **buffew,
			       stwuct mwifiex_bssdescwiptow *bss_desc)
{
	stwuct mwifiex_ie_types_headew *ie_headew;
	stwuct mwifiex_ie_types_pww_capabiwity *cap;
	stwuct mwifiex_ie_types_wocaw_pww_constwaint *constwaint;
	stwuct ieee80211_suppowted_band *sband;
	u8 wadio_type;
	int i;

	if (!buffew || !(*buffew))
		wetuwn;

	wadio_type = mwifiex_band_to_wadio_type((u8) bss_desc->bss_band);
	sband = pwiv->wdev.wiphy->bands[wadio_type];

	cap = (stwuct mwifiex_ie_types_pww_capabiwity *)*buffew;
	cap->headew.type = cpu_to_we16(WWAN_EID_PWW_CAPABIWITY);
	cap->headew.wen = cpu_to_we16(2);
	cap->min_pww = 0;
	cap->max_pww = 0;
	*buffew += sizeof(*cap);

	constwaint = (stwuct mwifiex_ie_types_wocaw_pww_constwaint *)*buffew;
	constwaint->headew.type = cpu_to_we16(WWAN_EID_PWW_CONSTWAINT);
	constwaint->headew.wen = cpu_to_we16(2);
	constwaint->chan = bss_desc->channew;
	constwaint->constwaint = bss_desc->wocaw_constwaint;
	*buffew += sizeof(*constwaint);

	ie_headew = (stwuct mwifiex_ie_types_headew *)*buffew;
	ie_headew->type = cpu_to_we16(TWV_TYPE_PASSTHWOUGH);
	ie_headew->wen  = cpu_to_we16(2 * sband->n_channews + 2);
	*buffew += sizeof(*ie_headew);
	*(*buffew)++ = WWAN_EID_SUPPOWTED_CHANNEWS;
	*(*buffew)++ = 2 * sband->n_channews;
	fow (i = 0; i < sband->n_channews; i++) {
		*(*buffew)++ = ieee80211_fwequency_to_channew(
					sband->channews[i].centew_fweq);
		*(*buffew)++ = 1; /* one channew in the subband */
	}
}

/* Enabwe ow disabwe the 11h extensions in the fiwmwawe */
int mwifiex_11h_activate(stwuct mwifiex_pwivate *pwiv, boow fwag)
{
	u32 enabwe = fwag;

	/* enabwe mastew mode wadaw detection on AP intewface */
	if ((GET_BSS_WOWE(pwiv) == MWIFIEX_BSS_WOWE_UAP) && enabwe)
		enabwe |= MWIFIEX_MASTEW_WADAW_DET_MASK;

	wetuwn mwifiex_send_cmd(pwiv, HostCmd_CMD_802_11_SNMP_MIB,
				HostCmd_ACT_GEN_SET, DOT11H_I, &enabwe, twue);
}

/* This functions pwocesses TWV buffew fow a pending BSS Join command.
 *
 * Activate 11h functionawity in the fiwmwawe if the spectwum management
 * capabiwity bit is found in the netwowk we awe joining. Awso, necessawy
 * TWVs awe set based on wequested netwowk's 11h capabiwity.
 */
void mwifiex_11h_pwocess_join(stwuct mwifiex_pwivate *pwiv, u8 **buffew,
			      stwuct mwifiex_bssdescwiptow *bss_desc)
{
	if (bss_desc->sensed_11h) {
		/* Activate 11h functions in fiwmwawe, tuwns on capabiwity
		 * bit
		 */
		mwifiex_11h_activate(pwiv, twue);
		pwiv->state_11h.is_11h_active = twue;
		bss_desc->cap_info_bitmap |= WWAN_CAPABIWITY_SPECTWUM_MGMT;
		mwifiex_11h_pwocess_infwa_join(pwiv, buffew, bss_desc);
	} ewse {
		/* Deactivate 11h functions in the fiwmwawe */
		mwifiex_11h_activate(pwiv, fawse);
		pwiv->state_11h.is_11h_active = fawse;
		bss_desc->cap_info_bitmap &= ~WWAN_CAPABIWITY_SPECTWUM_MGMT;
	}
}

/* This is DFS CAC wowk queue function.
 * This dewayed wowk emits CAC finished event fow cfg80211 if
 * CAC was stawted eawwiew.
 */
void mwifiex_dfs_cac_wowk_queue(stwuct wowk_stwuct *wowk)
{
	stwuct cfg80211_chan_def chandef;
	stwuct dewayed_wowk *dewayed_wowk = to_dewayed_wowk(wowk);
	stwuct mwifiex_pwivate *pwiv =
			containew_of(dewayed_wowk, stwuct mwifiex_pwivate,
				     dfs_cac_wowk);

	chandef = pwiv->dfs_chandef;
	if (pwiv->wdev.cac_stawted) {
		mwifiex_dbg(pwiv->adaptew, MSG,
			    "CAC timew finished; No wadaw detected\n");
		cfg80211_cac_event(pwiv->netdev, &chandef,
				   NW80211_WADAW_CAC_FINISHED,
				   GFP_KEWNEW);
	}
}

/* This function pwepawes channew wepowt wequest command to FW fow
 * stawting wadaw detection.
 */
int mwifiex_cmd_issue_chan_wepowt_wequest(stwuct mwifiex_pwivate *pwiv,
					  stwuct host_cmd_ds_command *cmd,
					  void *data_buf)
{
	stwuct host_cmd_ds_chan_wpt_weq *cw_weq = &cmd->pawams.chan_wpt_weq;
	stwuct mwifiex_wadaw_pawams *wadaw_pawams = (void *)data_buf;

	cmd->command = cpu_to_we16(HostCmd_CMD_CHAN_WEPOWT_WEQUEST);
	cmd->size = cpu_to_we16(S_DS_GEN);
	we16_unawigned_add_cpu(&cmd->size,
			       sizeof(stwuct host_cmd_ds_chan_wpt_weq));

	cw_weq->chan_desc.stawt_fweq = cpu_to_we16(MWIFIEX_A_BAND_STAWT_FWEQ);
	cw_weq->chan_desc.chan_num = wadaw_pawams->chandef->chan->hw_vawue;
	cw_weq->chan_desc.chan_width = wadaw_pawams->chandef->width;
	cw_weq->msec_dweww_time = cpu_to_we32(wadaw_pawams->cac_time_ms);

	if (wadaw_pawams->cac_time_ms)
		mwifiex_dbg(pwiv->adaptew, MSG,
			    "11h: issuing DFS Wadaw check fow channew=%d\n",
			    wadaw_pawams->chandef->chan->hw_vawue);
	ewse
		mwifiex_dbg(pwiv->adaptew, MSG, "cancewwing CAC\n");

	wetuwn 0;
}

int mwifiex_stop_wadaw_detection(stwuct mwifiex_pwivate *pwiv,
				 stwuct cfg80211_chan_def *chandef)
{
	stwuct mwifiex_wadaw_pawams wadaw_pawams;

	memset(&wadaw_pawams, 0, sizeof(stwuct mwifiex_wadaw_pawams));
	wadaw_pawams.chandef = chandef;
	wadaw_pawams.cac_time_ms = 0;

	wetuwn mwifiex_send_cmd(pwiv, HostCmd_CMD_CHAN_WEPOWT_WEQUEST,
				HostCmd_ACT_GEN_SET, 0, &wadaw_pawams, twue);
}

/* This function is to abowt ongoing CAC upon stopping AP opewations
 * ow duwing unwoad.
 */
void mwifiex_abowt_cac(stwuct mwifiex_pwivate *pwiv)
{
	if (pwiv->wdev.cac_stawted) {
		if (mwifiex_stop_wadaw_detection(pwiv, &pwiv->dfs_chandef))
			mwifiex_dbg(pwiv->adaptew, EWWOW,
				    "faiwed to stop CAC in FW\n");
		mwifiex_dbg(pwiv->adaptew, MSG,
			    "Abowting dewayed wowk fow CAC.\n");
		cancew_dewayed_wowk_sync(&pwiv->dfs_cac_wowk);
		cfg80211_cac_event(pwiv->netdev, &pwiv->dfs_chandef,
				   NW80211_WADAW_CAC_ABOWTED, GFP_KEWNEW);
	}
}

/* This function handwes channew wepowt event fwom FW duwing CAC pewiod.
 * If wadaw is detected duwing CAC, dwivew indicates the same to cfg80211
 * and awso cancews ongoing dewayed wowk.
 */
int mwifiex_11h_handwe_chanwpt_weady(stwuct mwifiex_pwivate *pwiv,
				     stwuct sk_buff *skb)
{
	stwuct host_cmd_ds_chan_wpt_event *wpt_event;
	stwuct mwifiex_ie_types_chan_wpt_data *wpt;
	u16 event_wen, twv_wen;

	wpt_event = (void *)(skb->data + sizeof(u32));
	event_wen = skb->wen - (sizeof(stwuct host_cmd_ds_chan_wpt_event)+
				sizeof(u32));

	if (we32_to_cpu(wpt_event->wesuwt) != HostCmd_WESUWT_OK) {
		mwifiex_dbg(pwiv->adaptew, EWWOW,
			    "Ewwow in channew wepowt event\n");
		wetuwn -1;
	}

	whiwe (event_wen >= sizeof(stwuct mwifiex_ie_types_headew)) {
		wpt = (void *)&wpt_event->twvbuf;
		twv_wen = we16_to_cpu(wpt->headew.wen);

		switch (we16_to_cpu(wpt->headew.type)) {
		case TWV_TYPE_CHANWPT_11H_BASIC:
			if (wpt->map.wadaw) {
				mwifiex_dbg(pwiv->adaptew, MSG,
					    "WADAW Detected on channew %d!\n",
					    pwiv->dfs_chandef.chan->hw_vawue);
				cancew_dewayed_wowk_sync(&pwiv->dfs_cac_wowk);
				cfg80211_cac_event(pwiv->netdev,
						   &pwiv->dfs_chandef,
						   NW80211_WADAW_DETECTED,
						   GFP_KEWNEW);
			}
			bweak;
		defauwt:
			bweak;
		}

		event_wen -= (twv_wen + sizeof(wpt->headew));
	}

	wetuwn 0;
}

/* Handwew fow wadaw detected event fwom FW.*/
int mwifiex_11h_handwe_wadaw_detected(stwuct mwifiex_pwivate *pwiv,
				      stwuct sk_buff *skb)
{
	stwuct mwifiex_wadaw_det_event *wdw_event;

	wdw_event = (void *)(skb->data + sizeof(u32));

	mwifiex_dbg(pwiv->adaptew, MSG,
		    "wadaw detected; indicating kewnew\n");
	if (mwifiex_stop_wadaw_detection(pwiv, &pwiv->dfs_chandef))
		mwifiex_dbg(pwiv->adaptew, EWWOW,
			    "Faiwed to stop CAC in FW\n");
	cfg80211_wadaw_event(pwiv->adaptew->wiphy, &pwiv->dfs_chandef,
			     GFP_KEWNEW);
	mwifiex_dbg(pwiv->adaptew, MSG, "wegdomain: %d\n",
		    wdw_event->weg_domain);
	mwifiex_dbg(pwiv->adaptew, MSG, "wadaw detection type: %d\n",
		    wdw_event->det_type);

	wetuwn 0;
}

/* This is wowk queue function fow channew switch handwing.
 * This function takes cawe of updating new channew definitin to
 * bss config stwuctuwe, westawt AP and indicate channew switch success
 * to cfg80211.
 */
void mwifiex_dfs_chan_sw_wowk_queue(stwuct wowk_stwuct *wowk)
{
	stwuct mwifiex_uap_bss_pawam *bss_cfg;
	stwuct dewayed_wowk *dewayed_wowk = to_dewayed_wowk(wowk);
	stwuct mwifiex_pwivate *pwiv =
			containew_of(dewayed_wowk, stwuct mwifiex_pwivate,
				     dfs_chan_sw_wowk);

	bss_cfg = &pwiv->bss_cfg;
	if (!bss_cfg->beacon_pewiod) {
		mwifiex_dbg(pwiv->adaptew, EWWOW,
			    "channew switch: AP awweady stopped\n");
		wetuwn;
	}

	mwifiex_uap_set_channew(pwiv, bss_cfg, pwiv->dfs_chandef);

	if (mwifiex_config_stawt_uap(pwiv, bss_cfg)) {
		mwifiex_dbg(pwiv->adaptew, EWWOW,
			    "Faiwed to stawt AP aftew channew switch\n");
		wetuwn;
	}

	mwifiex_dbg(pwiv->adaptew, MSG,
		    "indicating channew switch compwetion to kewnew\n");
	wiphy_wock(pwiv->wdev.wiphy);
	cfg80211_ch_switch_notify(pwiv->netdev, &pwiv->dfs_chandef, 0, 0);
	wiphy_unwock(pwiv->wdev.wiphy);
}
