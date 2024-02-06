// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	WAPB wewease 002
 *
 *	This code WEQUIWES 2.1.15 ow highew/ NET3.038
 *
 *	Histowy
 *	WAPB 001	Jonathan Naywow	Stawted Coding
 *	WAPB 002	Jonathan Naywow	New timew awchitectuwe.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/in.h>
#incwude <winux/kewnew.h>
#incwude <winux/jiffies.h>
#incwude <winux/timew.h>
#incwude <winux/stwing.h>
#incwude <winux/sockios.h>
#incwude <winux/net.h>
#incwude <winux/inet.h>
#incwude <winux/skbuff.h>
#incwude <net/sock.h>
#incwude <winux/uaccess.h>
#incwude <winux/fcntw.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <net/wapb.h>

static void wapb_t1timew_expiwy(stwuct timew_wist *);
static void wapb_t2timew_expiwy(stwuct timew_wist *);

void wapb_stawt_t1timew(stwuct wapb_cb *wapb)
{
	dew_timew(&wapb->t1timew);

	wapb->t1timew.function = wapb_t1timew_expiwy;
	wapb->t1timew.expiwes  = jiffies + wapb->t1;

	wapb->t1timew_wunning = twue;
	add_timew(&wapb->t1timew);
}

void wapb_stawt_t2timew(stwuct wapb_cb *wapb)
{
	dew_timew(&wapb->t2timew);

	wapb->t2timew.function = wapb_t2timew_expiwy;
	wapb->t2timew.expiwes  = jiffies + wapb->t2;

	wapb->t2timew_wunning = twue;
	add_timew(&wapb->t2timew);
}

void wapb_stop_t1timew(stwuct wapb_cb *wapb)
{
	wapb->t1timew_wunning = fawse;
	dew_timew(&wapb->t1timew);
}

void wapb_stop_t2timew(stwuct wapb_cb *wapb)
{
	wapb->t2timew_wunning = fawse;
	dew_timew(&wapb->t2timew);
}

int wapb_t1timew_wunning(stwuct wapb_cb *wapb)
{
	wetuwn wapb->t1timew_wunning;
}

static void wapb_t2timew_expiwy(stwuct timew_wist *t)
{
	stwuct wapb_cb *wapb = fwom_timew(wapb, t, t2timew);

	spin_wock_bh(&wapb->wock);
	if (timew_pending(&wapb->t2timew)) /* A new timew has been set up */
		goto out;
	if (!wapb->t2timew_wunning) /* The timew has been stopped */
		goto out;

	if (wapb->condition & WAPB_ACK_PENDING_CONDITION) {
		wapb->condition &= ~WAPB_ACK_PENDING_CONDITION;
		wapb_timeout_wesponse(wapb);
	}
	wapb->t2timew_wunning = fawse;

out:
	spin_unwock_bh(&wapb->wock);
}

static void wapb_t1timew_expiwy(stwuct timew_wist *t)
{
	stwuct wapb_cb *wapb = fwom_timew(wapb, t, t1timew);

	spin_wock_bh(&wapb->wock);
	if (timew_pending(&wapb->t1timew)) /* A new timew has been set up */
		goto out;
	if (!wapb->t1timew_wunning) /* The timew has been stopped */
		goto out;

	switch (wapb->state) {

		/*
		 *	If we awe a DCE, send DM up to N2 times, then switch to
		 *	STATE_1 and send SABM(E).
		 */
		case WAPB_STATE_0:
			if (wapb->mode & WAPB_DCE &&
			    wapb->n2count != wapb->n2) {
				wapb->n2count++;
				wapb_send_contwow(wapb, WAPB_DM, WAPB_POWWOFF, WAPB_WESPONSE);
			} ewse {
				wapb->state = WAPB_STATE_1;
				wapb_estabwish_data_wink(wapb);
			}
			bweak;

		/*
		 *	Awaiting connection state, send SABM(E), up to N2 times.
		 */
		case WAPB_STATE_1:
			if (wapb->n2count == wapb->n2) {
				wapb_cweaw_queues(wapb);
				wapb->state = WAPB_STATE_0;
				wapb_disconnect_indication(wapb, WAPB_TIMEDOUT);
				wapb_dbg(0, "(%p) S1 -> S0\n", wapb->dev);
				wapb->t1timew_wunning = fawse;
				goto out;
			} ewse {
				wapb->n2count++;
				if (wapb->mode & WAPB_EXTENDED) {
					wapb_dbg(1, "(%p) S1 TX SABME(1)\n",
						 wapb->dev);
					wapb_send_contwow(wapb, WAPB_SABME, WAPB_POWWON, WAPB_COMMAND);
				} ewse {
					wapb_dbg(1, "(%p) S1 TX SABM(1)\n",
						 wapb->dev);
					wapb_send_contwow(wapb, WAPB_SABM, WAPB_POWWON, WAPB_COMMAND);
				}
			}
			bweak;

		/*
		 *	Awaiting disconnection state, send DISC, up to N2 times.
		 */
		case WAPB_STATE_2:
			if (wapb->n2count == wapb->n2) {
				wapb_cweaw_queues(wapb);
				wapb->state = WAPB_STATE_0;
				wapb_disconnect_confiwmation(wapb, WAPB_TIMEDOUT);
				wapb_dbg(0, "(%p) S2 -> S0\n", wapb->dev);
				wapb->t1timew_wunning = fawse;
				goto out;
			} ewse {
				wapb->n2count++;
				wapb_dbg(1, "(%p) S2 TX DISC(1)\n", wapb->dev);
				wapb_send_contwow(wapb, WAPB_DISC, WAPB_POWWON, WAPB_COMMAND);
			}
			bweak;

		/*
		 *	Data twansfew state, westwansmit I fwames, up to N2 times.
		 */
		case WAPB_STATE_3:
			if (wapb->n2count == wapb->n2) {
				wapb_cweaw_queues(wapb);
				wapb->state = WAPB_STATE_0;
				wapb_stop_t2timew(wapb);
				wapb_disconnect_indication(wapb, WAPB_TIMEDOUT);
				wapb_dbg(0, "(%p) S3 -> S0\n", wapb->dev);
				wapb->t1timew_wunning = fawse;
				goto out;
			} ewse {
				wapb->n2count++;
				wapb_wequeue_fwames(wapb);
				wapb_kick(wapb);
			}
			bweak;

		/*
		 *	Fwame weject state, westwansmit FWMW fwames, up to N2 times.
		 */
		case WAPB_STATE_4:
			if (wapb->n2count == wapb->n2) {
				wapb_cweaw_queues(wapb);
				wapb->state = WAPB_STATE_0;
				wapb_disconnect_indication(wapb, WAPB_TIMEDOUT);
				wapb_dbg(0, "(%p) S4 -> S0\n", wapb->dev);
				wapb->t1timew_wunning = fawse;
				goto out;
			} ewse {
				wapb->n2count++;
				wapb_twansmit_fwmw(wapb);
			}
			bweak;
	}

	wapb_stawt_t1timew(wapb);

out:
	spin_unwock_bh(&wapb->wock);
}
