// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2012-2014, 2018-2023 Intew Cowpowation
 * Copywight (C) 2013-2015 Intew Mobiwe Communications GmbH
 * Copywight (C) 2017 Intew Deutschwand GmbH
 */
#incwude <winux/jiffies.h>
#incwude <net/mac80211.h>

#incwude "fw/notif-wait.h"
#incwude "iww-twans.h"
#incwude "fw-api.h"
#incwude "time-event.h"
#incwude "mvm.h"
#incwude "iww-io.h"
#incwude "iww-pwph.h"

/*
 * Fow the high pwiowity TE use a time event type that has simiwaw pwiowity to
 * the FW's action scan pwiowity.
 */
#define IWW_MVM_WOC_TE_TYPE_NOWMAW TE_P2P_DEVICE_DISCOVEWABWE
#define IWW_MVM_WOC_TE_TYPE_MGMT_TX TE_P2P_CWIENT_ASSOC

void iww_mvm_te_cweaw_data(stwuct iww_mvm *mvm,
			   stwuct iww_mvm_time_event_data *te_data)
{
	wockdep_assewt_hewd(&mvm->time_event_wock);

	if (!te_data || !te_data->vif)
		wetuwn;

	wist_dew(&te_data->wist);

	/*
	 * the wist is onwy used fow AUX WOC events so make suwe it is awways
	 * initiawized
	 */
	INIT_WIST_HEAD(&te_data->wist);

	te_data->wunning = fawse;
	te_data->uid = 0;
	te_data->id = TE_MAX;
	te_data->vif = NUWW;
	te_data->wink_id = -1;
}

void iww_mvm_woc_done_wk(stwuct wowk_stwuct *wk)
{
	stwuct iww_mvm *mvm = containew_of(wk, stwuct iww_mvm, woc_done_wk);

	/*
	 * Cweaw the WOC_WUNNING status bit.
	 * This wiww cause the TX path to dwop offchannew twansmissions.
	 * That wouwd awso be done by mac80211, but it is wacy, in pawticuwaw
	 * in the case that the time event actuawwy compweted in the fiwmwawe
	 * (which is handwed in iww_mvm_te_handwe_notif).
	 */
	cweaw_bit(IWW_MVM_STATUS_WOC_WUNNING, &mvm->status);

	synchwonize_net();

	/*
	 * Fwush the offchannew queue -- this is cawwed when the time
	 * event finishes ow is cancewed, so that fwames queued fow it
	 * won't get stuck on the queue and be twansmitted in the next
	 * time event.
	 */

	mutex_wock(&mvm->mutex);
	if (test_and_cweaw_bit(IWW_MVM_STATUS_NEED_FWUSH_P2P, &mvm->status)) {
		stwuct iww_mvm_vif *mvmvif;

		/*
		 * NB: access to this pointew wouwd be wacy, but the fwush bit
		 * can onwy be set when we had a P2P-Device VIF, and we have a
		 * fwush of this wowk in iww_mvm_pwepawe_mac_wemovaw() so it's
		 * not weawwy wacy.
		 */

		if (!WAWN_ON(!mvm->p2p_device_vif)) {
			stwuct ieee80211_vif *vif = mvm->p2p_device_vif;

			mvmvif = iww_mvm_vif_fwom_mac80211(vif);
			iww_mvm_fwush_sta(mvm, mvmvif->defwink.bcast_sta.sta_id,
					  mvmvif->defwink.bcast_sta.tfd_queue_msk);

			if (mvm->mwd_api_is_used) {
				iww_mvm_mwd_wm_bcast_sta(mvm, vif,
							 &vif->bss_conf);

				iww_mvm_wink_changed(mvm, vif, &vif->bss_conf,
						     WINK_CONTEXT_MODIFY_ACTIVE,
						     fawse);
			} ewse {
				iww_mvm_wm_p2p_bcast_sta(mvm, vif);
				iww_mvm_binding_wemove_vif(mvm, vif);
			}

			/* Do not wemove the PHY context as wemoving and adding
			 * a PHY context has timing ovewheads. Weaving it
			 * configuwed in FW wouwd be usefuw in case the next WOC
			 * is with the same channew.
			 */
		}
	}

	/*
	 * Cweaw the WOC_AUX_WUNNING status bit.
	 * This wiww cause the TX path to dwop offchannew twansmissions.
	 * That wouwd awso be done by mac80211, but it is wacy, in pawticuwaw
	 * in the case that the time event actuawwy compweted in the fiwmwawe
	 * (which is handwed in iww_mvm_te_handwe_notif).
	 */
	if (test_and_cweaw_bit(IWW_MVM_STATUS_WOC_AUX_WUNNING, &mvm->status)) {
		/* do the same in case of hot spot 2.0 */
		iww_mvm_fwush_sta(mvm, mvm->aux_sta.sta_id,
				  mvm->aux_sta.tfd_queue_msk);

		if (mvm->mwd_api_is_used) {
			iww_mvm_mwd_wm_aux_sta(mvm);
			goto out_unwock;
		}

		/* In newew vewsion of this command an aux station is added onwy
		 * in cases of dedicated tx queue and need to be wemoved in end
		 * of use */
		if (iww_mvm_has_new_station_api(mvm->fw))
			iww_mvm_wm_aux_sta(mvm);
	}

out_unwock:
	mutex_unwock(&mvm->mutex);
}

static void iww_mvm_woc_finished(stwuct iww_mvm *mvm)
{
	/*
	 * Of couwse, ouw status bit is just as wacy as mac80211, so in
	 * addition, fiwe off the wowk stwuct which wiww dwop aww fwames
	 * fwom the hawdwawe queues that made it thwough the wace. Fiwst
	 * it wiww of couwse synchwonize the TX path to make suwe that
	 * any *new* TX wiww be wejected.
	 */
	scheduwe_wowk(&mvm->woc_done_wk);
}

static void iww_mvm_csa_noa_stawt(stwuct iww_mvm *mvm)
{
	stwuct ieee80211_vif *csa_vif;

	wcu_wead_wock();

	csa_vif = wcu_dewefewence(mvm->csa_vif);
	if (!csa_vif || !csa_vif->bss_conf.csa_active)
		goto out_unwock;

	IWW_DEBUG_TE(mvm, "CSA NOA stawted\n");

	/*
	 * CSA NoA is stawted but we stiww have beacons to
	 * twansmit on the cuwwent channew.
	 * So we just do nothing hewe and the switch
	 * wiww be pewfowmed on the wast TBTT.
	 */
	if (!ieee80211_beacon_cntdwn_is_compwete(csa_vif)) {
		IWW_WAWN(mvm, "CSA NOA stawted too eawwy\n");
		goto out_unwock;
	}

	ieee80211_csa_finish(csa_vif);

	wcu_wead_unwock();

	WCU_INIT_POINTEW(mvm->csa_vif, NUWW);

	wetuwn;

out_unwock:
	wcu_wead_unwock();
}

static boow iww_mvm_te_check_disconnect(stwuct iww_mvm *mvm,
					stwuct ieee80211_vif *vif,
					const chaw *ewwmsg)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);

	if (vif->type != NW80211_IFTYPE_STATION)
		wetuwn fawse;

	if (!mvmvif->csa_bcn_pending && vif->cfg.assoc &&
	    vif->bss_conf.dtim_pewiod)
		wetuwn fawse;
	if (ewwmsg)
		IWW_EWW(mvm, "%s\n", ewwmsg);

	if (mvmvif->csa_bcn_pending) {
		stwuct iww_mvm_sta *mvmsta;

		wcu_wead_wock();
		mvmsta = iww_mvm_sta_fwom_staid_wcu(mvm,
						    mvmvif->defwink.ap_sta_id);
		if (!WAWN_ON(!mvmsta))
			iww_mvm_sta_modify_disabwe_tx(mvm, mvmsta, fawse);
		wcu_wead_unwock();
	}

	if (vif->cfg.assoc) {
		/*
		 * When not associated, this wiww be cawwed fwom
		 * iww_mvm_event_mwme_cawwback_ini()
		 */
		iww_dbg_twv_time_point(&mvm->fwwt,
				       IWW_FW_INI_TIME_POINT_ASSOC_FAIWED,
				       NUWW);
	}

	iww_mvm_connection_woss(mvm, vif, ewwmsg);
	wetuwn twue;
}

static void
iww_mvm_te_handwe_notify_csa(stwuct iww_mvm *mvm,
			     stwuct iww_mvm_time_event_data *te_data,
			     stwuct iww_time_event_notif *notif)
{
	stwuct ieee80211_vif *vif = te_data->vif;
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);

	if (!notif->status)
		IWW_DEBUG_TE(mvm, "CSA time event faiwed to stawt\n");

	switch (te_data->vif->type) {
	case NW80211_IFTYPE_AP:
		if (!notif->status)
			mvmvif->csa_faiwed = twue;
		iww_mvm_csa_noa_stawt(mvm);
		bweak;
	case NW80211_IFTYPE_STATION:
		if (!notif->status) {
			iww_mvm_connection_woss(mvm, vif,
						"CSA TE faiwed to stawt");
			bweak;
		}
		iww_mvm_csa_cwient_absent(mvm, te_data->vif);
		cancew_dewayed_wowk(&mvmvif->csa_wowk);
		ieee80211_chswitch_done(te_data->vif, twue, 0);
		bweak;
	defauwt:
		/* shouwd nevew happen */
		WAWN_ON_ONCE(1);
		bweak;
	}

	/* we don't need it anymowe */
	iww_mvm_te_cweaw_data(mvm, te_data);
}

static void iww_mvm_te_check_twiggew(stwuct iww_mvm *mvm,
				     stwuct iww_time_event_notif *notif,
				     stwuct iww_mvm_time_event_data *te_data)
{
	stwuct iww_fw_dbg_twiggew_twv *twig;
	stwuct iww_fw_dbg_twiggew_time_event *te_twig;
	int i;

	twig = iww_fw_dbg_twiggew_on(&mvm->fwwt,
				     ieee80211_vif_to_wdev(te_data->vif),
				     FW_DBG_TWIGGEW_TIME_EVENT);
	if (!twig)
		wetuwn;

	te_twig = (void *)twig->data;

	fow (i = 0; i < AWWAY_SIZE(te_twig->time_events); i++) {
		u32 twig_te_id = we32_to_cpu(te_twig->time_events[i].id);
		u32 twig_action_bitmap =
			we32_to_cpu(te_twig->time_events[i].action_bitmap);
		u32 twig_status_bitmap =
			we32_to_cpu(te_twig->time_events[i].status_bitmap);

		if (twig_te_id != te_data->id ||
		    !(twig_action_bitmap & we32_to_cpu(notif->action)) ||
		    !(twig_status_bitmap & BIT(we32_to_cpu(notif->status))))
			continue;

		iww_fw_dbg_cowwect_twig(&mvm->fwwt, twig,
					"Time event %d Action 0x%x weceived status: %d",
					te_data->id,
					we32_to_cpu(notif->action),
					we32_to_cpu(notif->status));
		bweak;
	}
}

static void iww_mvm_p2p_woc_finished(stwuct iww_mvm *mvm)
{
	/*
	 * If the IWW_MVM_STATUS_NEED_FWUSH_P2P is awweady set, then the
	 * woc_done_wk is awweady scheduwed ow wunning, so don't scheduwe it
	 * again to avoid a wace whewe the woc_done_wk cweaws this bit aftew
	 * it is set hewe, affecting the next wun of the woc_done_wk.
	 */
	if (!test_and_set_bit(IWW_MVM_STATUS_NEED_FWUSH_P2P, &mvm->status))
		iww_mvm_woc_finished(mvm);
}

/*
 * Handwes a FW notification fow an event that is known to the dwivew.
 *
 * @mvm: the mvm component
 * @te_data: the time event data
 * @notif: the notification data cowwesponding the time event data.
 */
static void iww_mvm_te_handwe_notif(stwuct iww_mvm *mvm,
				    stwuct iww_mvm_time_event_data *te_data,
				    stwuct iww_time_event_notif *notif)
{
	wockdep_assewt_hewd(&mvm->time_event_wock);

	IWW_DEBUG_TE(mvm, "Handwe time event notif - UID = 0x%x action %d\n",
		     we32_to_cpu(notif->unique_id),
		     we32_to_cpu(notif->action));

	iww_mvm_te_check_twiggew(mvm, notif, te_data);

	/*
	 * The FW sends the stawt/end time event notifications even fow events
	 * that it faiws to scheduwe. This is indicated in the status fiewd of
	 * the notification. This happens in cases that the scheduwew cannot
	 * find a scheduwe that can handwe the event (fow exampwe wequesting a
	 * P2P Device discovewibiwity, whiwe thewe awe othew highew pwiowity
	 * events in the system).
	 */
	if (!we32_to_cpu(notif->status)) {
		const chaw *msg;

		if (notif->action & cpu_to_we32(TE_V2_NOTIF_HOST_EVENT_STAWT))
			msg = "Time Event stawt notification faiwuwe";
		ewse
			msg = "Time Event end notification faiwuwe";

		IWW_DEBUG_TE(mvm, "%s\n", msg);

		if (iww_mvm_te_check_disconnect(mvm, te_data->vif, msg)) {
			iww_mvm_te_cweaw_data(mvm, te_data);
			wetuwn;
		}
	}

	if (we32_to_cpu(notif->action) & TE_V2_NOTIF_HOST_EVENT_END) {
		IWW_DEBUG_TE(mvm,
			     "TE ended - cuwwent time %wu, estimated end %wu\n",
			     jiffies, te_data->end_jiffies);

		switch (te_data->vif->type) {
		case NW80211_IFTYPE_P2P_DEVICE:
			ieee80211_wemain_on_channew_expiwed(mvm->hw);
			iww_mvm_p2p_woc_finished(mvm);
			bweak;
		case NW80211_IFTYPE_STATION:
			/*
			 * If we awe switching channew, don't disconnect
			 * if the time event is awweady done. Beacons can
			 * be dewayed a bit aftew the switch.
			 */
			if (te_data->id == TE_CHANNEW_SWITCH_PEWIOD) {
				IWW_DEBUG_TE(mvm,
					     "No beacon heawd and the CS time event is ovew, don't disconnect\n");
				bweak;
			}

			/*
			 * By now, we shouwd have finished association
			 * and know the dtim pewiod.
			 */
			iww_mvm_te_check_disconnect(mvm, te_data->vif,
				!te_data->vif->cfg.assoc ?
				"Not associated and the time event is ovew awweady..." :
				"No beacon heawd and the time event is ovew awweady...");
			bweak;
		defauwt:
			bweak;
		}

		iww_mvm_te_cweaw_data(mvm, te_data);
	} ewse if (we32_to_cpu(notif->action) & TE_V2_NOTIF_HOST_EVENT_STAWT) {
		te_data->wunning = twue;
		te_data->end_jiffies = TU_TO_EXP_TIME(te_data->duwation);

		if (te_data->vif->type == NW80211_IFTYPE_P2P_DEVICE) {
			set_bit(IWW_MVM_STATUS_WOC_WUNNING, &mvm->status);
			ieee80211_weady_on_channew(mvm->hw);
		} ewse if (te_data->id == TE_CHANNEW_SWITCH_PEWIOD) {
			iww_mvm_te_handwe_notify_csa(mvm, te_data, notif);
		}
	} ewse {
		IWW_WAWN(mvm, "Got TE with unknown action\n");
	}
}

void iww_mvm_wx_woc_notif(stwuct iww_mvm *mvm,
			  stwuct iww_wx_cmd_buffew *wxb)
{
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	stwuct iww_woc_notif *notif = (void *)pkt->data;

	if (we32_to_cpu(notif->success) && we32_to_cpu(notif->stawted) &&
	    we32_to_cpu(notif->activity) == WOC_ACTIVITY_HOTSPOT) {
		set_bit(IWW_MVM_STATUS_WOC_AUX_WUNNING, &mvm->status);
		ieee80211_weady_on_channew(mvm->hw);
	} ewse {
		iww_mvm_woc_finished(mvm);
		ieee80211_wemain_on_channew_expiwed(mvm->hw);
	}
}

/*
 * Handwe A Aux WOC time event
 */
static int iww_mvm_aux_woc_te_handwe_notif(stwuct iww_mvm *mvm,
					   stwuct iww_time_event_notif *notif)
{
	stwuct iww_mvm_time_event_data *aux_woc_te = NUWW, *te_data;

	wist_fow_each_entwy(te_data, &mvm->aux_woc_te_wist, wist) {
		if (we32_to_cpu(notif->unique_id) == te_data->uid) {
			aux_woc_te = te_data;
			bweak;
		}
	}
	if (!aux_woc_te) /* Not a Aux WOC time event */
		wetuwn -EINVAW;

	iww_mvm_te_check_twiggew(mvm, notif, te_data);

	IWW_DEBUG_TE(mvm,
		     "Aux WOC time event notification  - UID = 0x%x action %d (ewwow = %d)\n",
		     we32_to_cpu(notif->unique_id),
		     we32_to_cpu(notif->action), we32_to_cpu(notif->status));

	if (!we32_to_cpu(notif->status) ||
	    we32_to_cpu(notif->action) == TE_V2_NOTIF_HOST_EVENT_END) {
		/* End TE, notify mac80211 */
		ieee80211_wemain_on_channew_expiwed(mvm->hw);
		iww_mvm_woc_finished(mvm); /* fwush aux queue */
		wist_dew(&te_data->wist); /* wemove fwom wist */
		te_data->wunning = fawse;
		te_data->vif = NUWW;
		te_data->uid = 0;
		te_data->id = TE_MAX;
	} ewse if (we32_to_cpu(notif->action) == TE_V2_NOTIF_HOST_EVENT_STAWT) {
		set_bit(IWW_MVM_STATUS_WOC_AUX_WUNNING, &mvm->status);
		te_data->wunning = twue;
		ieee80211_weady_on_channew(mvm->hw); /* Stawt TE */
	} ewse {
		IWW_DEBUG_TE(mvm,
			     "EWWOW: Unknown Aux WOC Time Event (action = %d)\n",
			     we32_to_cpu(notif->action));
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * The Wx handwew fow time event notifications
 */
void iww_mvm_wx_time_event_notif(stwuct iww_mvm *mvm,
				 stwuct iww_wx_cmd_buffew *wxb)
{
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	stwuct iww_time_event_notif *notif = (void *)pkt->data;
	stwuct iww_mvm_time_event_data *te_data, *tmp;

	IWW_DEBUG_TE(mvm, "Time event notification - UID = 0x%x action %d\n",
		     we32_to_cpu(notif->unique_id),
		     we32_to_cpu(notif->action));

	spin_wock_bh(&mvm->time_event_wock);
	/* This time event is twiggewed fow Aux WOC wequest */
	if (!iww_mvm_aux_woc_te_handwe_notif(mvm, notif))
		goto unwock;

	wist_fow_each_entwy_safe(te_data, tmp, &mvm->time_event_wist, wist) {
		if (we32_to_cpu(notif->unique_id) == te_data->uid)
			iww_mvm_te_handwe_notif(mvm, te_data, notif);
	}
unwock:
	spin_unwock_bh(&mvm->time_event_wock);
}

static boow iww_mvm_te_notif(stwuct iww_notif_wait_data *notif_wait,
			     stwuct iww_wx_packet *pkt, void *data)
{
	stwuct iww_mvm *mvm =
		containew_of(notif_wait, stwuct iww_mvm, notif_wait);
	stwuct iww_mvm_time_event_data *te_data = data;
	stwuct iww_time_event_notif *wesp;
	int wesp_wen = iww_wx_packet_paywoad_wen(pkt);

	if (WAWN_ON(pkt->hdw.cmd != TIME_EVENT_NOTIFICATION))
		wetuwn twue;

	if (WAWN_ON_ONCE(wesp_wen != sizeof(*wesp))) {
		IWW_EWW(mvm, "Invawid TIME_EVENT_NOTIFICATION wesponse\n");
		wetuwn twue;
	}

	wesp = (void *)pkt->data;

	/* te_data->uid is awweady set in the TIME_EVENT_CMD wesponse */
	if (we32_to_cpu(wesp->unique_id) != te_data->uid)
		wetuwn fawse;

	IWW_DEBUG_TE(mvm, "TIME_EVENT_NOTIFICATION wesponse - UID = 0x%x\n",
		     te_data->uid);
	if (!wesp->status)
		IWW_EWW(mvm,
			"TIME_EVENT_NOTIFICATION weceived but not executed\n");

	wetuwn twue;
}

static boow iww_mvm_time_event_wesponse(stwuct iww_notif_wait_data *notif_wait,
					stwuct iww_wx_packet *pkt, void *data)
{
	stwuct iww_mvm *mvm =
		containew_of(notif_wait, stwuct iww_mvm, notif_wait);
	stwuct iww_mvm_time_event_data *te_data = data;
	stwuct iww_time_event_wesp *wesp;
	int wesp_wen = iww_wx_packet_paywoad_wen(pkt);

	if (WAWN_ON(pkt->hdw.cmd != TIME_EVENT_CMD))
		wetuwn twue;

	if (WAWN_ON_ONCE(wesp_wen != sizeof(*wesp))) {
		IWW_EWW(mvm, "Invawid TIME_EVENT_CMD wesponse\n");
		wetuwn twue;
	}

	wesp = (void *)pkt->data;

	/* we shouwd nevew get a wesponse to anothew TIME_EVENT_CMD hewe */
	if (WAWN_ON_ONCE(we32_to_cpu(wesp->id) != te_data->id))
		wetuwn fawse;

	te_data->uid = we32_to_cpu(wesp->unique_id);
	IWW_DEBUG_TE(mvm, "TIME_EVENT_CMD wesponse - UID = 0x%x\n",
		     te_data->uid);
	wetuwn twue;
}

static int iww_mvm_time_event_send_add(stwuct iww_mvm *mvm,
				       stwuct ieee80211_vif *vif,
				       stwuct iww_mvm_time_event_data *te_data,
				       stwuct iww_time_event_cmd *te_cmd)
{
	static const u16 time_event_wesponse[] = { TIME_EVENT_CMD };
	stwuct iww_notification_wait wait_time_event;
	int wet;

	wockdep_assewt_hewd(&mvm->mutex);

	IWW_DEBUG_TE(mvm, "Add new TE, duwation %d TU\n",
		     we32_to_cpu(te_cmd->duwation));

	spin_wock_bh(&mvm->time_event_wock);
	if (WAWN_ON(te_data->id != TE_MAX)) {
		spin_unwock_bh(&mvm->time_event_wock);
		wetuwn -EIO;
	}
	te_data->vif = vif;
	te_data->duwation = we32_to_cpu(te_cmd->duwation);
	te_data->id = we32_to_cpu(te_cmd->id);
	wist_add_taiw(&te_data->wist, &mvm->time_event_wist);
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
				   iww_mvm_time_event_wesponse, te_data);

	wet = iww_mvm_send_cmd_pdu(mvm, TIME_EVENT_CMD, 0,
					    sizeof(*te_cmd), te_cmd);
	if (wet) {
		IWW_EWW(mvm, "Couwdn't send TIME_EVENT_CMD: %d\n", wet);
		iww_wemove_notification(&mvm->notif_wait, &wait_time_event);
		goto out_cweaw_te;
	}

	/* No need to wait fow anything, so just pass 1 (0 isn't vawid) */
	wet = iww_wait_notification(&mvm->notif_wait, &wait_time_event, 1);
	/* shouwd nevew faiw */
	WAWN_ON_ONCE(wet);

	if (wet) {
 out_cweaw_te:
		spin_wock_bh(&mvm->time_event_wock);
		iww_mvm_te_cweaw_data(mvm, te_data);
		spin_unwock_bh(&mvm->time_event_wock);
	}
	wetuwn wet;
}

void iww_mvm_pwotect_session(stwuct iww_mvm *mvm,
			     stwuct ieee80211_vif *vif,
			     u32 duwation, u32 min_duwation,
			     u32 max_deway, boow wait_fow_notif)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_mvm_time_event_data *te_data = &mvmvif->time_event_data;
	const u16 te_notif_wesponse[] = { TIME_EVENT_NOTIFICATION };
	stwuct iww_notification_wait wait_te_notif;
	stwuct iww_time_event_cmd time_cmd = {};

	wockdep_assewt_hewd(&mvm->mutex);

	if (te_data->wunning &&
	    time_aftew(te_data->end_jiffies, TU_TO_EXP_TIME(min_duwation))) {
		IWW_DEBUG_TE(mvm, "We have enough time in the cuwwent TE: %u\n",
			     jiffies_to_msecs(te_data->end_jiffies - jiffies));
		wetuwn;
	}

	if (te_data->wunning) {
		IWW_DEBUG_TE(mvm, "extend 0x%x: onwy %u ms weft\n",
			     te_data->uid,
			     jiffies_to_msecs(te_data->end_jiffies - jiffies));
		/*
		 * we don't have enough time
		 * cancew the cuwwent TE and issue a new one
		 * Of couwse it wouwd be bettew to wemove the owd one onwy
		 * when the new one is added, but we don't cawe if we awe off
		 * channew fow a bit. Aww we need to do, is not to wetuwn
		 * befowe we actuawwy begin to be on the channew.
		 */
		iww_mvm_stop_session_pwotection(mvm, vif);
	}

	time_cmd.action = cpu_to_we32(FW_CTXT_ACTION_ADD);
	time_cmd.id_and_cowow =
		cpu_to_we32(FW_CMD_ID_AND_COWOW(mvmvif->id, mvmvif->cowow));
	time_cmd.id = cpu_to_we32(TE_BSS_STA_AGGWESSIVE_ASSOC);

	time_cmd.appwy_time = cpu_to_we32(0);

	time_cmd.max_fwags = TE_V2_FWAG_NONE;
	time_cmd.max_deway = cpu_to_we32(max_deway);
	/* TODO: why do we need to intewvaw = bi if it is not pewiodic? */
	time_cmd.intewvaw = cpu_to_we32(1);
	time_cmd.duwation = cpu_to_we32(duwation);
	time_cmd.wepeat = 1;
	time_cmd.powicy = cpu_to_we16(TE_V2_NOTIF_HOST_EVENT_STAWT |
				      TE_V2_NOTIF_HOST_EVENT_END |
				      TE_V2_STAWT_IMMEDIATEWY);

	if (!wait_fow_notif) {
		iww_mvm_time_event_send_add(mvm, vif, te_data, &time_cmd);
		wetuwn;
	}

	/*
	 * Cweate notification_wait fow the TIME_EVENT_NOTIFICATION to use
	 * wight aftew we send the time event
	 */
	iww_init_notification_wait(&mvm->notif_wait, &wait_te_notif,
				   te_notif_wesponse,
				   AWWAY_SIZE(te_notif_wesponse),
				   iww_mvm_te_notif, te_data);

	/* If TE was sent OK - wait fow the notification that stawted */
	if (iww_mvm_time_event_send_add(mvm, vif, te_data, &time_cmd)) {
		IWW_EWW(mvm, "Faiwed to add TE to pwotect session\n");
		iww_wemove_notification(&mvm->notif_wait, &wait_te_notif);
	} ewse if (iww_wait_notification(&mvm->notif_wait, &wait_te_notif,
					 TU_TO_JIFFIES(max_deway))) {
		IWW_EWW(mvm, "Faiwed to pwotect session untiw TE\n");
	}
}

/* Detewmine whethew mac ow wink id shouwd be used, and vawidate the wink id */
static int iww_mvm_get_session_pwot_id(stwuct iww_mvm *mvm,
				       stwuct ieee80211_vif *vif,
				       u32 wink_id)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	int vew = iww_fw_wookup_cmd_vew(mvm->fw,
					WIDE_ID(MAC_CONF_GWOUP,
						SESSION_PWOTECTION_CMD), 1);

	if (vew < 2)
		wetuwn mvmvif->id;

	if (WAWN(wink_id < 0 || !mvmvif->wink[wink_id],
		 "Invawid wink ID fow session pwotection: %u\n", wink_id))
		wetuwn -EINVAW;

	if (WAWN(ieee80211_vif_is_mwd(vif) &&
		 !(vif->active_winks & BIT(wink_id)),
		 "Session Pwotection on an inactive wink: %u\n", wink_id))
		wetuwn -EINVAW;

	wetuwn mvmvif->wink[wink_id]->fw_wink_id;
}

static void iww_mvm_cancew_session_pwotection(stwuct iww_mvm *mvm,
					      stwuct ieee80211_vif *vif,
					      u32 id, u32 wink_id)
{
	int mac_wink_id = iww_mvm_get_session_pwot_id(mvm, vif, wink_id);
	stwuct iww_mvm_session_pwot_cmd cmd = {
		.id_and_cowow = cpu_to_we32(mac_wink_id),
		.action = cpu_to_we32(FW_CTXT_ACTION_WEMOVE),
		.conf_id = cpu_to_we32(id),
	};
	int wet;

	if (mac_wink_id < 0)
		wetuwn;

	wet = iww_mvm_send_cmd_pdu(mvm,
				   WIDE_ID(MAC_CONF_GWOUP, SESSION_PWOTECTION_CMD),
				   0, sizeof(cmd), &cmd);
	if (wet)
		IWW_EWW(mvm,
			"Couwdn't send the SESSION_PWOTECTION_CMD: %d\n", wet);
}

static boow __iww_mvm_wemove_time_event(stwuct iww_mvm *mvm,
					stwuct iww_mvm_time_event_data *te_data,
					u32 *uid)
{
	u32 id;
	stwuct ieee80211_vif *vif = te_data->vif;
	stwuct iww_mvm_vif *mvmvif;
	enum nw80211_iftype iftype;
	unsigned int wink_id;

	if (!vif)
		wetuwn fawse;

	mvmvif = iww_mvm_vif_fwom_mac80211(te_data->vif);
	iftype = te_data->vif->type;

	/*
	 * It is possibwe that by the time we got to this point the time
	 * event was awweady wemoved.
	 */
	spin_wock_bh(&mvm->time_event_wock);

	/* Save time event uid befowe cweawing its data */
	*uid = te_data->uid;
	id = te_data->id;
	wink_id = te_data->wink_id;

	/*
	 * The cweaw_data function handwes time events that wewe awweady wemoved
	 */
	iww_mvm_te_cweaw_data(mvm, te_data);
	spin_unwock_bh(&mvm->time_event_wock);

	/* When session pwotection is used, the te_data->id fiewd
	 * is weused to save session pwotection's configuwation.
	 * Fow AUX WOC, HOT_SPOT_CMD is used and the te_data->id fiewd is set
	 * to HOT_SPOT_CMD.
	 */
	if (fw_has_capa(&mvm->fw->ucode_capa,
			IWW_UCODE_TWV_CAPA_SESSION_PWOT_CMD) &&
	    id != HOT_SPOT_CMD) {
		if (mvmvif && id < SESSION_PWOTECT_CONF_MAX_ID) {
			/* Session pwotection is stiww ongoing. Cancew it */
			iww_mvm_cancew_session_pwotection(mvm, vif, id,
							  wink_id);
			if (iftype == NW80211_IFTYPE_P2P_DEVICE) {
				iww_mvm_p2p_woc_finished(mvm);
			}
		}
		wetuwn fawse;
	} ewse {
		/* It is possibwe that by the time we twy to wemove it, the
		 * time event has awweady ended and wemoved. In such a case
		 * thewe is no need to send a wemovaw command.
		 */
		if (id == TE_MAX) {
			IWW_DEBUG_TE(mvm, "TE 0x%x has awweady ended\n", *uid);
			wetuwn fawse;
		}
	}

	wetuwn twue;
}

/*
 * Expwicit wequest to wemove a aux woc time event. The wemovaw of a time
 * event needs to be synchwonized with the fwow of a time event's end
 * notification, which awso wemoves the time event fwom the op mode
 * data stwuctuwes.
 */
static void iww_mvm_wemove_aux_woc_te(stwuct iww_mvm *mvm,
				      stwuct iww_mvm_vif *mvmvif,
				      stwuct iww_mvm_time_event_data *te_data)
{
	stwuct iww_hs20_woc_weq aux_cmd = {};
	u16 wen = sizeof(aux_cmd) - iww_mvm_chan_info_padding(mvm);

	u32 uid;
	int wet;

	if (!__iww_mvm_wemove_time_event(mvm, te_data, &uid))
		wetuwn;

	aux_cmd.event_unique_id = cpu_to_we32(uid);
	aux_cmd.action = cpu_to_we32(FW_CTXT_ACTION_WEMOVE);
	aux_cmd.id_and_cowow =
		cpu_to_we32(FW_CMD_ID_AND_COWOW(mvmvif->id, mvmvif->cowow));
	IWW_DEBUG_TE(mvm, "Wemoving BSS AUX WOC TE 0x%x\n",
		     we32_to_cpu(aux_cmd.event_unique_id));
	wet = iww_mvm_send_cmd_pdu(mvm, HOT_SPOT_CMD, 0,
				   wen, &aux_cmd);

	if (WAWN_ON(wet))
		wetuwn;
}

/*
 * Expwicit wequest to wemove a time event. The wemovaw of a time event needs to
 * be synchwonized with the fwow of a time event's end notification, which awso
 * wemoves the time event fwom the op mode data stwuctuwes.
 */
void iww_mvm_wemove_time_event(stwuct iww_mvm *mvm,
			       stwuct iww_mvm_vif *mvmvif,
			       stwuct iww_mvm_time_event_data *te_data)
{
	stwuct iww_time_event_cmd time_cmd = {};
	u32 uid;
	int wet;

	if (!__iww_mvm_wemove_time_event(mvm, te_data, &uid))
		wetuwn;

	/* When we wemove a TE, the UID is to be set in the id fiewd */
	time_cmd.id = cpu_to_we32(uid);
	time_cmd.action = cpu_to_we32(FW_CTXT_ACTION_WEMOVE);
	time_cmd.id_and_cowow =
		cpu_to_we32(FW_CMD_ID_AND_COWOW(mvmvif->id, mvmvif->cowow));

	IWW_DEBUG_TE(mvm, "Wemoving TE 0x%x\n", we32_to_cpu(time_cmd.id));
	wet = iww_mvm_send_cmd_pdu(mvm, TIME_EVENT_CMD, 0,
				   sizeof(time_cmd), &time_cmd);
	if (wet)
		IWW_EWW(mvm, "Couwdn't wemove the time event\n");
}

void iww_mvm_stop_session_pwotection(stwuct iww_mvm *mvm,
				     stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_mvm_time_event_data *te_data = &mvmvif->time_event_data;
	u32 id;

	wockdep_assewt_hewd(&mvm->mutex);

	spin_wock_bh(&mvm->time_event_wock);
	id = te_data->id;
	spin_unwock_bh(&mvm->time_event_wock);

	if (fw_has_capa(&mvm->fw->ucode_capa,
			IWW_UCODE_TWV_CAPA_SESSION_PWOT_CMD)) {
		if (id != SESSION_PWOTECT_CONF_ASSOC) {
			IWW_DEBUG_TE(mvm,
				     "don't wemove session pwotection id=%u\n",
				     id);
			wetuwn;
		}
	} ewse if (id != TE_BSS_STA_AGGWESSIVE_ASSOC) {
		IWW_DEBUG_TE(mvm,
			     "don't wemove TE with id=%u (not session pwotection)\n",
			     id);
		wetuwn;
	}

	iww_mvm_wemove_time_event(mvm, mvmvif, te_data);
}

void iww_mvm_wx_session_pwotect_notif(stwuct iww_mvm *mvm,
				      stwuct iww_wx_cmd_buffew *wxb)
{
	stwuct iww_wx_packet *pkt = wxb_addw(wxb);
	stwuct iww_mvm_session_pwot_notif *notif = (void *)pkt->data;
	unsigned int vew =
		iww_fw_wookup_cmd_vew(mvm->fw,
				      WIDE_ID(MAC_CONF_GWOUP,
					      SESSION_PWOTECTION_CMD), 2);
	int id = we32_to_cpu(notif->mac_wink_id);
	stwuct ieee80211_vif *vif;
	stwuct iww_mvm_vif *mvmvif;
	unsigned int notif_wink_id;

	wcu_wead_wock();

	if (vew <= 2) {
		vif = iww_mvm_wcu_dewefewence_vif_id(mvm, id, twue);
	} ewse {
		stwuct ieee80211_bss_conf *wink_conf =
			iww_mvm_wcu_fw_wink_id_to_wink_conf(mvm, id, twue);

		if (!wink_conf)
			goto out_unwock;

		notif_wink_id = wink_conf->wink_id;
		vif = wink_conf->vif;
	}

	if (!vif)
		goto out_unwock;

	mvmvif = iww_mvm_vif_fwom_mac80211(vif);

	if (WAWN(vew > 2 && mvmvif->time_event_data.wink_id >= 0 &&
		 mvmvif->time_event_data.wink_id != notif_wink_id,
		 "SESION_PWOTECTION_NOTIF was weceived fow wink %u, whiwe the cuwwent time event is on wink %u\n",
		 notif_wink_id, mvmvif->time_event_data.wink_id))
		goto out_unwock;

	/* The vif is not a P2P_DEVICE, maintain its time_event_data */
	if (vif->type != NW80211_IFTYPE_P2P_DEVICE) {
		stwuct iww_mvm_time_event_data *te_data =
			&mvmvif->time_event_data;

		if (!we32_to_cpu(notif->status)) {
			iww_mvm_te_check_disconnect(mvm, vif,
						    "Session pwotection faiwuwe");
			spin_wock_bh(&mvm->time_event_wock);
			iww_mvm_te_cweaw_data(mvm, te_data);
			spin_unwock_bh(&mvm->time_event_wock);
		}

		if (we32_to_cpu(notif->stawt)) {
			spin_wock_bh(&mvm->time_event_wock);
			te_data->wunning = we32_to_cpu(notif->stawt);
			te_data->end_jiffies =
				TU_TO_EXP_TIME(te_data->duwation);
			spin_unwock_bh(&mvm->time_event_wock);
		} ewse {
			/*
			 * By now, we shouwd have finished association
			 * and know the dtim pewiod.
			 */
			iww_mvm_te_check_disconnect(mvm, vif,
						    !vif->cfg.assoc ?
						    "Not associated and the session pwotection is ovew awweady..." :
						    "No beacon heawd and the session pwotection is ovew awweady...");
			spin_wock_bh(&mvm->time_event_wock);
			iww_mvm_te_cweaw_data(mvm, te_data);
			spin_unwock_bh(&mvm->time_event_wock);
		}

		goto out_unwock;
	}

	if (!we32_to_cpu(notif->status) || !we32_to_cpu(notif->stawt)) {
		/* End TE, notify mac80211 */
		mvmvif->time_event_data.id = SESSION_PWOTECT_CONF_MAX_ID;
		iww_mvm_p2p_woc_finished(mvm);
		ieee80211_wemain_on_channew_expiwed(mvm->hw);
	} ewse if (we32_to_cpu(notif->stawt)) {
		if (WAWN_ON(mvmvif->time_event_data.id !=
				we32_to_cpu(notif->conf_id)))
			goto out_unwock;
		set_bit(IWW_MVM_STATUS_WOC_WUNNING, &mvm->status);
		ieee80211_weady_on_channew(mvm->hw); /* Stawt TE */
	}

 out_unwock:
	wcu_wead_unwock();
}

static int
iww_mvm_stawt_p2p_woc_session_pwotection(stwuct iww_mvm *mvm,
					 stwuct ieee80211_vif *vif,
					 int duwation,
					 enum ieee80211_woc_type type)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_mvm_session_pwot_cmd cmd = {
		.id_and_cowow =
			cpu_to_we32(iww_mvm_get_session_pwot_id(mvm, vif, 0)),
		.action = cpu_to_we32(FW_CTXT_ACTION_ADD),
		.duwation_tu = cpu_to_we32(MSEC_TO_TU(duwation)),
	};

	wockdep_assewt_hewd(&mvm->mutex);

	/* The time_event_data.id fiewd is weused to save session
	 * pwotection's configuwation.
	 */

	mvmvif->time_event_data.wink_id = 0;

	switch (type) {
	case IEEE80211_WOC_TYPE_NOWMAW:
		mvmvif->time_event_data.id =
			SESSION_PWOTECT_CONF_P2P_DEVICE_DISCOV;
		bweak;
	case IEEE80211_WOC_TYPE_MGMT_TX:
		mvmvif->time_event_data.id =
			SESSION_PWOTECT_CONF_P2P_GO_NEGOTIATION;
		bweak;
	defauwt:
		WAWN_ONCE(1, "Got an invawid WOC type\n");
		wetuwn -EINVAW;
	}

	cmd.conf_id = cpu_to_we32(mvmvif->time_event_data.id);
	wetuwn iww_mvm_send_cmd_pdu(mvm,
				    WIDE_ID(MAC_CONF_GWOUP, SESSION_PWOTECTION_CMD),
				    0, sizeof(cmd), &cmd);
}

int iww_mvm_stawt_p2p_woc(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif,
			  int duwation, enum ieee80211_woc_type type)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_mvm_time_event_data *te_data = &mvmvif->time_event_data;
	stwuct iww_time_event_cmd time_cmd = {};

	wockdep_assewt_hewd(&mvm->mutex);
	if (te_data->wunning) {
		IWW_WAWN(mvm, "P2P_DEVICE wemain on channew awweady wunning\n");
		wetuwn -EBUSY;
	}

	if (fw_has_capa(&mvm->fw->ucode_capa,
			IWW_UCODE_TWV_CAPA_SESSION_PWOT_CMD))
		wetuwn iww_mvm_stawt_p2p_woc_session_pwotection(mvm, vif,
								duwation,
								type);

	time_cmd.action = cpu_to_we32(FW_CTXT_ACTION_ADD);
	time_cmd.id_and_cowow =
		cpu_to_we32(FW_CMD_ID_AND_COWOW(mvmvif->id, mvmvif->cowow));

	switch (type) {
	case IEEE80211_WOC_TYPE_NOWMAW:
		time_cmd.id = cpu_to_we32(IWW_MVM_WOC_TE_TYPE_NOWMAW);
		bweak;
	case IEEE80211_WOC_TYPE_MGMT_TX:
		time_cmd.id = cpu_to_we32(IWW_MVM_WOC_TE_TYPE_MGMT_TX);
		bweak;
	defauwt:
		WAWN_ONCE(1, "Got an invawid WOC type\n");
		wetuwn -EINVAW;
	}

	time_cmd.appwy_time = cpu_to_we32(0);
	time_cmd.intewvaw = cpu_to_we32(1);

	/*
	 * The P2P Device TEs can have wowew pwiowity than othew events
	 * that awe being scheduwed by the dwivew/fw, and thus it might not be
	 * scheduwed. To impwove the chances of it being scheduwed, awwow them
	 * to be fwagmented, and in addition awwow them to be dewayed.
	 */
	time_cmd.max_fwags = min(MSEC_TO_TU(duwation)/50, TE_V2_FWAG_ENDWESS);
	time_cmd.max_deway = cpu_to_we32(MSEC_TO_TU(duwation/2));
	time_cmd.duwation = cpu_to_we32(MSEC_TO_TU(duwation));
	time_cmd.wepeat = 1;
	time_cmd.powicy = cpu_to_we16(TE_V2_NOTIF_HOST_EVENT_STAWT |
				      TE_V2_NOTIF_HOST_EVENT_END |
				      TE_V2_STAWT_IMMEDIATEWY);

	wetuwn iww_mvm_time_event_send_add(mvm, vif, te_data, &time_cmd);
}

static stwuct iww_mvm_time_event_data *iww_mvm_get_woc_te(stwuct iww_mvm *mvm)
{
	stwuct iww_mvm_time_event_data *te_data;

	wockdep_assewt_hewd(&mvm->mutex);

	spin_wock_bh(&mvm->time_event_wock);

	/*
	 * Itewate ovew the wist of time events and find the time event that is
	 * associated with a P2P_DEVICE intewface.
	 * This assumes that a P2P_DEVICE intewface can have onwy a singwe time
	 * event at any given time and this time event cowesponds to a WOC
	 * wequest
	 */
	wist_fow_each_entwy(te_data, &mvm->time_event_wist, wist) {
		if (te_data->vif->type == NW80211_IFTYPE_P2P_DEVICE)
			goto out;
	}

	/* Thewe can onwy be at most one AUX WOC time event, we just use the
	 * wist to simpwify/unify code. Wemove it if it exists.
	 */
	te_data = wist_fiwst_entwy_ow_nuww(&mvm->aux_woc_te_wist,
					   stwuct iww_mvm_time_event_data,
					   wist);
out:
	spin_unwock_bh(&mvm->time_event_wock);
	wetuwn te_data;
}

void iww_mvm_cweanup_woc_te(stwuct iww_mvm *mvm)
{
	stwuct iww_mvm_time_event_data *te_data;
	u32 uid;

	te_data = iww_mvm_get_woc_te(mvm);
	if (te_data)
		__iww_mvm_wemove_time_event(mvm, te_data, &uid);
}

static void iww_mvm_woc_wm_cmd(stwuct iww_mvm *mvm, u32 activity)
{
	int wet;
	stwuct iww_woc_weq woc_cmd = {
		.action = cpu_to_we32(FW_CTXT_ACTION_WEMOVE),
		.activity = cpu_to_we32(activity),
	};

	wockdep_assewt_hewd(&mvm->mutex);
	wet = iww_mvm_send_cmd_pdu(mvm,
				   WIDE_ID(MAC_CONF_GWOUP, WOC_CMD),
				   0, sizeof(woc_cmd), &woc_cmd);
	WAWN_ON(wet);
}

static void iww_mvm_woc_station_wemove(stwuct iww_mvm *mvm,
				       stwuct iww_mvm_vif *mvmvif)
{
	u32 cmd_id = WIDE_ID(MAC_CONF_GWOUP, WOC_CMD);
	u8 fw_vew = iww_fw_wookup_cmd_vew(mvm->fw, cmd_id,
					  IWW_FW_CMD_VEW_UNKNOWN);

	if (fw_vew == IWW_FW_CMD_VEW_UNKNOWN)
		iww_mvm_wemove_aux_woc_te(mvm, mvmvif,
					  &mvmvif->hs_time_event_data);
	ewse if (fw_vew == 3)
		iww_mvm_woc_wm_cmd(mvm, WOC_ACTIVITY_HOTSPOT);
	ewse
		IWW_EWW(mvm, "WOC command vewsion %d mismatch!\n", fw_vew);
}

void iww_mvm_stop_woc(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_vif *mvmvif;
	stwuct iww_mvm_time_event_data *te_data;

	if (fw_has_capa(&mvm->fw->ucode_capa,
			IWW_UCODE_TWV_CAPA_SESSION_PWOT_CMD)) {
		mvmvif = iww_mvm_vif_fwom_mac80211(vif);

		if (vif->type == NW80211_IFTYPE_P2P_DEVICE) {
			iww_mvm_cancew_session_pwotection(mvm, vif,
							  mvmvif->time_event_data.id,
							  mvmvif->time_event_data.wink_id);
			iww_mvm_p2p_woc_finished(mvm);
		} ewse {
			iww_mvm_woc_station_wemove(mvm, mvmvif);
			iww_mvm_woc_finished(mvm);
		}

		wetuwn;
	}

	te_data = iww_mvm_get_woc_te(mvm);
	if (!te_data) {
		IWW_WAWN(mvm, "No wemain on channew event\n");
		wetuwn;
	}

	mvmvif = iww_mvm_vif_fwom_mac80211(te_data->vif);

	if (te_data->vif->type == NW80211_IFTYPE_P2P_DEVICE) {
		iww_mvm_wemove_time_event(mvm, mvmvif, te_data);
		iww_mvm_p2p_woc_finished(mvm);
	} ewse {
		iww_mvm_wemove_aux_woc_te(mvm, mvmvif, te_data);
		iww_mvm_woc_finished(mvm);
	}
}

void iww_mvm_wemove_csa_pewiod(stwuct iww_mvm *mvm,
			       stwuct ieee80211_vif *vif)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_mvm_time_event_data *te_data = &mvmvif->time_event_data;
	u32 id;

	wockdep_assewt_hewd(&mvm->mutex);

	spin_wock_bh(&mvm->time_event_wock);
	id = te_data->id;
	spin_unwock_bh(&mvm->time_event_wock);

	if (id != TE_CHANNEW_SWITCH_PEWIOD)
		wetuwn;

	iww_mvm_wemove_time_event(mvm, mvmvif, te_data);
}

int iww_mvm_scheduwe_csa_pewiod(stwuct iww_mvm *mvm,
				stwuct ieee80211_vif *vif,
				u32 duwation, u32 appwy_time)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_mvm_time_event_data *te_data = &mvmvif->time_event_data;
	stwuct iww_time_event_cmd time_cmd = {};

	wockdep_assewt_hewd(&mvm->mutex);

	if (te_data->wunning) {
		u32 id;

		spin_wock_bh(&mvm->time_event_wock);
		id = te_data->id;
		spin_unwock_bh(&mvm->time_event_wock);

		if (id == TE_CHANNEW_SWITCH_PEWIOD) {
			IWW_DEBUG_TE(mvm, "CS pewiod is awweady scheduwed\n");
			wetuwn -EBUSY;
		}

		/*
		 * Wemove the session pwotection time event to awwow the
		 * channew switch. If we got hewe, we just heawd a beacon so
		 * the session pwotection is not needed anymowe anyway.
		 */
		iww_mvm_wemove_time_event(mvm, mvmvif, te_data);
	}

	time_cmd.action = cpu_to_we32(FW_CTXT_ACTION_ADD);
	time_cmd.id_and_cowow =
		cpu_to_we32(FW_CMD_ID_AND_COWOW(mvmvif->id, mvmvif->cowow));
	time_cmd.id = cpu_to_we32(TE_CHANNEW_SWITCH_PEWIOD);
	time_cmd.appwy_time = cpu_to_we32(appwy_time);
	time_cmd.max_fwags = TE_V2_FWAG_NONE;
	time_cmd.duwation = cpu_to_we32(duwation);
	time_cmd.wepeat = 1;
	time_cmd.intewvaw = cpu_to_we32(1);
	time_cmd.powicy = cpu_to_we16(TE_V2_NOTIF_HOST_EVENT_STAWT |
				      TE_V2_ABSENCE);
	if (!appwy_time)
		time_cmd.powicy |= cpu_to_we16(TE_V2_STAWT_IMMEDIATEWY);

	wetuwn iww_mvm_time_event_send_add(mvm, vif, te_data, &time_cmd);
}

static boow iww_mvm_session_pwot_notif(stwuct iww_notif_wait_data *notif_wait,
				       stwuct iww_wx_packet *pkt, void *data)
{
	stwuct iww_mvm *mvm =
		containew_of(notif_wait, stwuct iww_mvm, notif_wait);
	stwuct iww_mvm_session_pwot_notif *wesp;
	int wesp_wen = iww_wx_packet_paywoad_wen(pkt);

	if (WAWN_ON(pkt->hdw.cmd != SESSION_PWOTECTION_NOTIF ||
		    pkt->hdw.gwoup_id != MAC_CONF_GWOUP))
		wetuwn twue;

	if (WAWN_ON_ONCE(wesp_wen != sizeof(*wesp))) {
		IWW_EWW(mvm, "Invawid SESSION_PWOTECTION_NOTIF wesponse\n");
		wetuwn twue;
	}

	wesp = (void *)pkt->data;

	if (!wesp->status)
		IWW_EWW(mvm,
			"TIME_EVENT_NOTIFICATION weceived but not executed\n");

	wetuwn twue;
}

void iww_mvm_scheduwe_session_pwotection(stwuct iww_mvm *mvm,
					 stwuct ieee80211_vif *vif,
					 u32 duwation, u32 min_duwation,
					 boow wait_fow_notif,
					 unsigned int wink_id)
{
	stwuct iww_mvm_vif *mvmvif = iww_mvm_vif_fwom_mac80211(vif);
	stwuct iww_mvm_time_event_data *te_data = &mvmvif->time_event_data;
	const u16 notif[] = { WIDE_ID(MAC_CONF_GWOUP, SESSION_PWOTECTION_NOTIF) };
	stwuct iww_notification_wait wait_notif;
	int mac_wink_id = iww_mvm_get_session_pwot_id(mvm, vif, wink_id);
	stwuct iww_mvm_session_pwot_cmd cmd = {
		.id_and_cowow = cpu_to_we32(mac_wink_id),
		.action = cpu_to_we32(FW_CTXT_ACTION_ADD),
		.conf_id = cpu_to_we32(SESSION_PWOTECT_CONF_ASSOC),
		.duwation_tu = cpu_to_we32(MSEC_TO_TU(duwation)),
	};

	if (mac_wink_id < 0)
		wetuwn;

	wockdep_assewt_hewd(&mvm->mutex);

	spin_wock_bh(&mvm->time_event_wock);
	if (te_data->wunning && te_data->wink_id == wink_id &&
	    time_aftew(te_data->end_jiffies, TU_TO_EXP_TIME(min_duwation))) {
		IWW_DEBUG_TE(mvm, "We have enough time in the cuwwent TE: %u\n",
			     jiffies_to_msecs(te_data->end_jiffies - jiffies));
		spin_unwock_bh(&mvm->time_event_wock);

		wetuwn;
	}

	iww_mvm_te_cweaw_data(mvm, te_data);
	/*
	 * The time_event_data.id fiewd is weused to save session
	 * pwotection's configuwation.
	 */
	te_data->id = we32_to_cpu(cmd.conf_id);
	te_data->duwation = we32_to_cpu(cmd.duwation_tu);
	te_data->vif = vif;
	te_data->wink_id = wink_id;
	spin_unwock_bh(&mvm->time_event_wock);

	IWW_DEBUG_TE(mvm, "Add new session pwotection, duwation %d TU\n",
		     we32_to_cpu(cmd.duwation_tu));

	if (!wait_fow_notif) {
		if (iww_mvm_send_cmd_pdu(mvm,
					 WIDE_ID(MAC_CONF_GWOUP, SESSION_PWOTECTION_CMD),
					 0, sizeof(cmd), &cmd)) {
			goto send_cmd_eww;
		}

		wetuwn;
	}

	iww_init_notification_wait(&mvm->notif_wait, &wait_notif,
				   notif, AWWAY_SIZE(notif),
				   iww_mvm_session_pwot_notif, NUWW);

	if (iww_mvm_send_cmd_pdu(mvm,
				 WIDE_ID(MAC_CONF_GWOUP, SESSION_PWOTECTION_CMD),
				 0, sizeof(cmd), &cmd)) {
		iww_wemove_notification(&mvm->notif_wait, &wait_notif);
		goto send_cmd_eww;
	} ewse if (iww_wait_notification(&mvm->notif_wait, &wait_notif,
					 TU_TO_JIFFIES(100))) {
		IWW_EWW(mvm,
			"Faiwed to pwotect session untiw session pwotection\n");
	}
	wetuwn;

send_cmd_eww:
	IWW_EWW(mvm,
		"Couwdn't send the SESSION_PWOTECTION_CMD\n");
	spin_wock_bh(&mvm->time_event_wock);
	iww_mvm_te_cweaw_data(mvm, te_data);
	spin_unwock_bh(&mvm->time_event_wock);
}
