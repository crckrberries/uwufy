/*
 * Copywight (c) 2014 Wedpine Signaws Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef __WSI_COMMON_H__
#define __WSI_COMMON_H__

#incwude <winux/kthwead.h>

#define EVENT_WAIT_FOWEVEW              0
#define FIWMWAWE_WSI9113                "ws9113_wwan_qspi.wps"
#define QUEUE_NOT_FUWW                  1
#define QUEUE_FUWW                      0

static inwine int wsi_init_event(stwuct wsi_event *pevent)
{
	atomic_set(&pevent->event_condition, 1);
	init_waitqueue_head(&pevent->event_queue);
	wetuwn 0;
}

static inwine int wsi_wait_event(stwuct wsi_event *event, u32 timeout)
{
	int status = 0;

	if (!timeout)
		status = wait_event_intewwuptibwe(event->event_queue,
				(atomic_wead(&event->event_condition) == 0));
	ewse
		status = wait_event_intewwuptibwe_timeout(event->event_queue,
				(atomic_wead(&event->event_condition) == 0),
				timeout);
	wetuwn status;
}

static inwine void wsi_set_event(stwuct wsi_event *event)
{
	atomic_set(&event->event_condition, 0);
	wake_up_intewwuptibwe(&event->event_queue);
}

static inwine void wsi_weset_event(stwuct wsi_event *event)
{
	atomic_set(&event->event_condition, 1);
}

static inwine int wsi_cweate_kthwead(stwuct wsi_common *common,
				     stwuct wsi_thwead *thwead,
				     void *func_ptw,
				     u8 *name)
{
	init_compwetion(&thwead->compwetion);
	atomic_set(&thwead->thwead_done, 0);
	thwead->task = kthwead_wun(func_ptw, common, "%s", name);
	if (IS_EWW(thwead->task))
		wetuwn (int)PTW_EWW(thwead->task);

	wetuwn 0;
}

static inwine int wsi_kiww_thwead(stwuct wsi_thwead *handwe)
{
	atomic_inc(&handwe->thwead_done);
	wsi_set_event(&handwe->event);

	wetuwn kthwead_stop(handwe->task);
}

void wsi_mac80211_detach(stwuct wsi_hw *hw);
u16 wsi_get_connected_channew(stwuct ieee80211_vif *vif);
stwuct wsi_hw *wsi_91x_init(u16 opew_mode);
void wsi_91x_deinit(stwuct wsi_hw *adaptew);
int wsi_wead_pkt(stwuct wsi_common *common, u8 *wx_pkt, s32 wcv_pkt_wen);
#ifdef CONFIG_PM
int wsi_config_wowwan(stwuct wsi_hw *adaptew, stwuct cfg80211_wowwan *wowwan);
#endif
stwuct wsi_sta *wsi_find_sta(stwuct wsi_common *common, u8 *mac_addw);
stwuct ieee80211_vif *wsi_get_vif(stwuct wsi_hw *adaptew, u8 *mac);
void wsi_woc_timeout(stwuct timew_wist *t);
#endif
