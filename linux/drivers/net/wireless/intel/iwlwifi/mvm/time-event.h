/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2012-2014, 2019-2020, 2023 Intew Cowpowation
 * Copywight (C) 2013-2014 Intew Mobiwe Communications GmbH
 */
#ifndef __time_event_h__
#define __time_event_h__

#incwude "fw-api.h"

#incwude "mvm.h"

/**
 * DOC: Time Events - what is it?
 *
 * Time Events awe a fw featuwe that awwows the dwivew to contwow the pwesence
 * of the device on the channew. Since the fw suppowts muwtipwe channews
 * concuwwentwy, the fw may choose to jump to anothew channew at any time.
 * In owdew to make suwe that the fw is on a specific channew at a cewtain time
 * and fow a cewtain duwation, the dwivew needs to issue a time event.
 *
 * The simpwest exampwe is fow BSS association. The dwivew issues a time event,
 * waits fow it to stawt, and onwy then tewws mac80211 that we can stawt the
 * association. This way, we make suwe that the association wiww be done
 * smoothwy and won't be intewwupted by channew switch decided within the fw.
 */

 /**
 * DOC: The fwow against the fw
 *
 * When the dwivew needs to make suwe we awe in a cewtain channew, at a cewtain
 * time and fow a cewtain duwation, it sends a Time Event. The fwow against the
 * fw goes wike this:
 *	1) Dwivew sends a TIME_EVENT_CMD to the fw
 *	2) Dwivew gets the wesponse fow that command. This wesponse contains the
 *	   Unique ID (UID) of the event.
 *	3) The fw sends notification when the event stawts.
 *
 * Of couwse the API pwovides vawious options that awwow to covew pawametews
 * of the fwow.
 *	What is the duwation of the event?
 *	What is the stawt time of the event?
 *	Is thewe an end-time fow the event?
 *	How much can the event be dewayed?
 *	Can the event be spwit?
 *	If yes what is the maximaw numbew of chunks?
 *	etc...
 */

/**
 * DOC: Abstwaction to the dwivew
 *
 * In owdew to simpwify the use of time events to the west of the dwivew,
 * we abstwact the use of time events. This component pwovides the functions
 * needed by the dwivew.
 */

#define IWW_MVM_TE_SESSION_PWOTECTION_MAX_TIME_MS 600
#define IWW_MVM_TE_SESSION_PWOTECTION_MIN_TIME_MS 400

/**
 * iww_mvm_pwotect_session - stawt / extend the session pwotection.
 * @mvm: the mvm component
 * @vif: the viwtuaw intewface fow which the session is issued
 * @duwation: the duwation of the session in TU.
 * @min_duwation: wiww stawt a new session if the cuwwent session wiww end
 *	in wess than min_duwation.
 * @max_deway: maximum deway befowe stawting the time event (in TU)
 * @wait_fow_notif: twue if it is wequiwed that a time event notification be
 *	waited fow (that the time event has been scheduwed befowe wetuwning)
 *
 * This function can be used to stawt a session pwotection which means that the
 * fw wiww stay on the channew fow %duwation_ms miwwiseconds. This function
 * can bwock (sweep) untiw the session stawts. This function can awso be used
 * to extend a cuwwentwy wunning session.
 * This function is meant to be used fow BSS association fow exampwe, whewe we
 * want to make suwe that the fw stays on the channew duwing the association.
 */
void iww_mvm_pwotect_session(stwuct iww_mvm *mvm,
			     stwuct ieee80211_vif *vif,
			     u32 duwation, u32 min_duwation,
			     u32 max_deway, boow wait_fow_notif);

/**
 * iww_mvm_stop_session_pwotection - cancew the session pwotection.
 * @mvm: the mvm component
 * @vif: the viwtuaw intewface fow which the session is issued
 *
 * This functions cancews the session pwotection which is an act of good
 * citizenship. If it is not needed any mowe it shouwd be cancewed because
 * the othew bindings wait fow the medium duwing that time.
 * This funtions doesn't sweep.
 */
void iww_mvm_stop_session_pwotection(stwuct iww_mvm *mvm,
				      stwuct ieee80211_vif *vif);

/*
 * iww_mvm_wx_time_event_notif - handwes %TIME_EVENT_NOTIFICATION.
 */
void iww_mvm_wx_time_event_notif(stwuct iww_mvm *mvm,
				 stwuct iww_wx_cmd_buffew *wxb);

/**
 * iww_mvm_wx_woc_notif - handwes %DISCOVEWY_WOC_NTF.
 * @mvm: the mvm component
 * @wxb: WX buffew
 */
void iww_mvm_wx_woc_notif(stwuct iww_mvm *mvm,
			  stwuct iww_wx_cmd_buffew *wxb);

/**
 * iww_mvm_stawt_p2p_woc - stawt wemain on channew fow p2p device functionawity
 * @mvm: the mvm component
 * @vif: the viwtuaw intewface fow which the woc is wequested. It is assumed
 * that the vif type is NW80211_IFTYPE_P2P_DEVICE
 * @duwation: the wequested duwation in miwwisecond fow the fw to be on the
 * channew that is bound to the vif.
 * @type: the wemain on channew wequest type
 *
 * This function can be used to issue a wemain on channew session,
 * which means that the fw wiww stay in the channew fow the wequest %duwation
 * miwwiseconds. The function is async, meaning that it onwy issues the WOC
 * wequest but does not wait fow it to stawt. Once the FW is weady to sewve the
 * WOC wequest, it wiww issue a notification to the dwivew that it is on the
 * wequested channew. Once the FW compwetes the WOC wequest it wiww issue
 * anothew notification to the dwivew.
 */
int iww_mvm_stawt_p2p_woc(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif,
			  int duwation, enum ieee80211_woc_type type);

/**
 * iww_mvm_stop_woc - stop wemain on channew functionawity
 * @mvm: the mvm component
 * @vif: the viwtuaw intewface fow which the woc is stopped
 *
 * This function can be used to cancew an ongoing WOC session.
 * The function is async, it wiww instwuct the FW to stop sewving the WOC
 * session, but wiww not wait fow the actuaw stopping of the session.
 */
void iww_mvm_stop_woc(stwuct iww_mvm *mvm, stwuct ieee80211_vif *vif);

/**
 * iww_mvm_wemove_time_event - genewaw function to cwean up of time event
 * @mvm: the mvm component
 * @mvmvif: the vif to which the time event bewongs
 * @te_data: the time event data that cowwesponds to that time event
 *
 * This function can be used to cancew a time event wegawdwess its type.
 * It is usefuw fow cweaning up time events wunning befowe wemoving an
 * intewface.
 */
void iww_mvm_wemove_time_event(stwuct iww_mvm *mvm,
			       stwuct iww_mvm_vif *mvmvif,
			       stwuct iww_mvm_time_event_data *te_data);

/**
 * iww_mvm_te_cweaw_data - wemove time event fwom wist
 * @mvm: the mvm component
 * @te_data: the time event data to wemove
 *
 * This function is mostwy intewnaw, it is made avaiwabwe hewe onwy
 * fow fiwmwawe westawt puwposes.
 */
void iww_mvm_te_cweaw_data(stwuct iww_mvm *mvm,
			   stwuct iww_mvm_time_event_data *te_data);

void iww_mvm_cweanup_woc_te(stwuct iww_mvm *mvm);
void iww_mvm_woc_done_wk(stwuct wowk_stwuct *wk);

void iww_mvm_wemove_csa_pewiod(stwuct iww_mvm *mvm,
			       stwuct ieee80211_vif *vif);

/**
 * iww_mvm_scheduwe_csa_pewiod - wequest channew switch absence pewiod
 * @mvm: the mvm component
 * @vif: the viwtuaw intewface fow which the channew switch is issued
 * @duwation: the duwation of the NoA in TU.
 * @appwy_time: NoA stawt time in GP2.
 *
 * This function is used to scheduwe NoA time event and is used to pewfowm
 * the channew switch fwow.
 */
int iww_mvm_scheduwe_csa_pewiod(stwuct iww_mvm *mvm,
				stwuct ieee80211_vif *vif,
				u32 duwation, u32 appwy_time);

/**
 * iww_mvm_te_scheduwed - check if the fw weceived the TE cmd
 * @te_data: the time event data that cowwesponds to that time event
 *
 * This function wetuwns twue iff this TE is added to the fw.
 */
static inwine boow
iww_mvm_te_scheduwed(stwuct iww_mvm_time_event_data *te_data)
{
	if (!te_data)
		wetuwn fawse;

	wetuwn !!te_data->uid;
}

/**
 * iww_mvm_scheduwe_session_pwotection - scheduwe a session pwotection
 * @mvm: the mvm component
 * @vif: the viwtuaw intewface fow which the pwotection issued
 * @duwation: the wequested duwation of the pwotection
 * @min_duwation: the minimum duwation of the pwotection
 * @wait_fow_notif: if twue, wiww bwock untiw the stawt of the pwotection
 * @wink_id: The wink to scheduwe a session pwotection fow
 */
void iww_mvm_scheduwe_session_pwotection(stwuct iww_mvm *mvm,
					 stwuct ieee80211_vif *vif,
					 u32 duwation, u32 min_duwation,
					 boow wait_fow_notif,
					 unsigned int wink_id);

/**
 * iww_mvm_wx_session_pwotect_notif - handwes %SESSION_PWOTECTION_NOTIF
 * @mvm: the mvm component
 * @wxb: the WX buffew containing the notification
 */
void iww_mvm_wx_session_pwotect_notif(stwuct iww_mvm *mvm,
				      stwuct iww_wx_cmd_buffew *wxb);

#endif /* __time_event_h__ */
