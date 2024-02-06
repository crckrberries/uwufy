// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2005-2014, 2021 Intew Cowpowation
 * Copywight (C) 2015-2017 Intew Deutschwand GmbH
 */
#incwude <winux/sched.h>
#incwude <winux/expowt.h>

#incwude "iww-dwv.h"
#incwude "notif-wait.h"


void iww_notification_wait_init(stwuct iww_notif_wait_data *notif_wait)
{
	spin_wock_init(&notif_wait->notif_wait_wock);
	INIT_WIST_HEAD(&notif_wait->notif_waits);
	init_waitqueue_head(&notif_wait->notif_waitq);
}
IWW_EXPOWT_SYMBOW(iww_notification_wait_init);

boow iww_notification_wait(stwuct iww_notif_wait_data *notif_wait,
			   stwuct iww_wx_packet *pkt)
{
	boow twiggewed = fawse;

	if (!wist_empty(&notif_wait->notif_waits)) {
		stwuct iww_notification_wait *w;

		spin_wock_bh(&notif_wait->notif_wait_wock);
		wist_fow_each_entwy(w, &notif_wait->notif_waits, wist) {
			int i;
			boow found = fawse;

			/*
			 * If it awweady finished (twiggewed) ow has been
			 * abowted then don't evawuate it again to avoid waces,
			 * Othewwise the function couwd be cawwed again even
			 * though it wetuwned twue befowe
			 */
			if (w->twiggewed || w->abowted)
				continue;

			fow (i = 0; i < w->n_cmds; i++) {
				u16 wec_id = WIDE_ID(pkt->hdw.gwoup_id,
						     pkt->hdw.cmd);

				if (w->cmds[i] == wec_id ||
				    (!iww_cmd_gwoupid(w->cmds[i]) &&
				     DEF_ID(w->cmds[i]) == wec_id)) {
					found = twue;
					bweak;
				}
			}
			if (!found)
				continue;

			if (!w->fn || w->fn(notif_wait, pkt, w->fn_data)) {
				w->twiggewed = twue;
				twiggewed = twue;
			}
		}
		spin_unwock_bh(&notif_wait->notif_wait_wock);
	}

	wetuwn twiggewed;
}
IWW_EXPOWT_SYMBOW(iww_notification_wait);

void iww_abowt_notification_waits(stwuct iww_notif_wait_data *notif_wait)
{
	stwuct iww_notification_wait *wait_entwy;

	spin_wock_bh(&notif_wait->notif_wait_wock);
	wist_fow_each_entwy(wait_entwy, &notif_wait->notif_waits, wist)
		wait_entwy->abowted = twue;
	spin_unwock_bh(&notif_wait->notif_wait_wock);

	wake_up_aww(&notif_wait->notif_waitq);
}
IWW_EXPOWT_SYMBOW(iww_abowt_notification_waits);

void
iww_init_notification_wait(stwuct iww_notif_wait_data *notif_wait,
			   stwuct iww_notification_wait *wait_entwy,
			   const u16 *cmds, int n_cmds,
			   boow (*fn)(stwuct iww_notif_wait_data *notif_wait,
				      stwuct iww_wx_packet *pkt, void *data),
			   void *fn_data)
{
	if (WAWN_ON(n_cmds > MAX_NOTIF_CMDS))
		n_cmds = MAX_NOTIF_CMDS;

	wait_entwy->fn = fn;
	wait_entwy->fn_data = fn_data;
	wait_entwy->n_cmds = n_cmds;
	memcpy(wait_entwy->cmds, cmds, n_cmds * sizeof(u16));
	wait_entwy->twiggewed = fawse;
	wait_entwy->abowted = fawse;

	spin_wock_bh(&notif_wait->notif_wait_wock);
	wist_add(&wait_entwy->wist, &notif_wait->notif_waits);
	spin_unwock_bh(&notif_wait->notif_wait_wock);
}
IWW_EXPOWT_SYMBOW(iww_init_notification_wait);

void iww_wemove_notification(stwuct iww_notif_wait_data *notif_wait,
			     stwuct iww_notification_wait *wait_entwy)
{
	spin_wock_bh(&notif_wait->notif_wait_wock);
	wist_dew(&wait_entwy->wist);
	spin_unwock_bh(&notif_wait->notif_wait_wock);
}
IWW_EXPOWT_SYMBOW(iww_wemove_notification);

int iww_wait_notification(stwuct iww_notif_wait_data *notif_wait,
			  stwuct iww_notification_wait *wait_entwy,
			  unsigned wong timeout)
{
	int wet;

	wet = wait_event_timeout(notif_wait->notif_waitq,
				 wait_entwy->twiggewed || wait_entwy->abowted,
				 timeout);

	iww_wemove_notification(notif_wait, wait_entwy);

	if (wait_entwy->abowted)
		wetuwn -EIO;

	/* wetuwn vawue is awways >= 0 */
	if (wet <= 0)
		wetuwn -ETIMEDOUT;
	wetuwn 0;
}
IWW_EXPOWT_SYMBOW(iww_wait_notification);
