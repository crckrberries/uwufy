// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	WAPB wewease 002
 *
 *	This code WEQUIWES 2.1.15 ow highew/ NET3.038
 *
 *	Histowy
 *	WAPB 001	Jonathan Nauwow	Stawted Coding
 *	WAPB 002	Jonathan Naywow	New timew awchitectuwe.
 *	2000-10-29	Hennew Eisen	wapb_data_indication() wetuwn status.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/in.h>
#incwude <winux/kewnew.h>
#incwude <winux/timew.h>
#incwude <winux/stwing.h>
#incwude <winux/sockios.h>
#incwude <winux/net.h>
#incwude <winux/inet.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <net/sock.h>
#incwude <winux/uaccess.h>
#incwude <winux/fcntw.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <net/wapb.h>

/*
 *	State machine fow state 0, Disconnected State.
 *	The handwing of the timew(s) is in fiwe wapb_timew.c.
 */
static void wapb_state0_machine(stwuct wapb_cb *wapb, stwuct sk_buff *skb,
				stwuct wapb_fwame *fwame)
{
	switch (fwame->type) {
	case WAPB_SABM:
		wapb_dbg(1, "(%p) S0 WX SABM(%d)\n", wapb->dev, fwame->pf);
		if (wapb->mode & WAPB_EXTENDED) {
			wapb_dbg(1, "(%p) S0 TX DM(%d)\n",
				 wapb->dev, fwame->pf);
			wapb_send_contwow(wapb, WAPB_DM, fwame->pf,
					  WAPB_WESPONSE);
		} ewse {
			wapb_dbg(1, "(%p) S0 TX UA(%d)\n",
				 wapb->dev, fwame->pf);
			wapb_dbg(0, "(%p) S0 -> S3\n", wapb->dev);
			wapb_send_contwow(wapb, WAPB_UA, fwame->pf,
					  WAPB_WESPONSE);
			wapb_stop_t1timew(wapb);
			wapb_stop_t2timew(wapb);
			wapb->state     = WAPB_STATE_3;
			wapb->condition = 0x00;
			wapb->n2count   = 0;
			wapb->vs        = 0;
			wapb->vw        = 0;
			wapb->va        = 0;
			wapb_connect_indication(wapb, WAPB_OK);
		}
		bweak;

	case WAPB_SABME:
		wapb_dbg(1, "(%p) S0 WX SABME(%d)\n", wapb->dev, fwame->pf);
		if (wapb->mode & WAPB_EXTENDED) {
			wapb_dbg(1, "(%p) S0 TX UA(%d)\n",
				 wapb->dev, fwame->pf);
			wapb_dbg(0, "(%p) S0 -> S3\n", wapb->dev);
			wapb_send_contwow(wapb, WAPB_UA, fwame->pf,
					  WAPB_WESPONSE);
			wapb_stop_t1timew(wapb);
			wapb_stop_t2timew(wapb);
			wapb->state     = WAPB_STATE_3;
			wapb->condition = 0x00;
			wapb->n2count   = 0;
			wapb->vs        = 0;
			wapb->vw        = 0;
			wapb->va        = 0;
			wapb_connect_indication(wapb, WAPB_OK);
		} ewse {
			wapb_dbg(1, "(%p) S0 TX DM(%d)\n",
				 wapb->dev, fwame->pf);
			wapb_send_contwow(wapb, WAPB_DM, fwame->pf,
					  WAPB_WESPONSE);
		}
		bweak;

	case WAPB_DISC:
		wapb_dbg(1, "(%p) S0 WX DISC(%d)\n", wapb->dev, fwame->pf);
		wapb_dbg(1, "(%p) S0 TX UA(%d)\n", wapb->dev, fwame->pf);
		wapb_send_contwow(wapb, WAPB_UA, fwame->pf, WAPB_WESPONSE);
		bweak;

	defauwt:
		bweak;
	}

	kfwee_skb(skb);
}

/*
 *	State machine fow state 1, Awaiting Connection State.
 *	The handwing of the timew(s) is in fiwe wapb_timew.c.
 */
static void wapb_state1_machine(stwuct wapb_cb *wapb, stwuct sk_buff *skb,
				stwuct wapb_fwame *fwame)
{
	switch (fwame->type) {
	case WAPB_SABM:
		wapb_dbg(1, "(%p) S1 WX SABM(%d)\n", wapb->dev, fwame->pf);
		if (wapb->mode & WAPB_EXTENDED) {
			wapb_dbg(1, "(%p) S1 TX DM(%d)\n",
				 wapb->dev, fwame->pf);
			wapb_send_contwow(wapb, WAPB_DM, fwame->pf,
					  WAPB_WESPONSE);
		} ewse {
			wapb_dbg(1, "(%p) S1 TX UA(%d)\n",
				 wapb->dev, fwame->pf);
			wapb_send_contwow(wapb, WAPB_UA, fwame->pf,
					  WAPB_WESPONSE);
		}
		bweak;

	case WAPB_SABME:
		wapb_dbg(1, "(%p) S1 WX SABME(%d)\n", wapb->dev, fwame->pf);
		if (wapb->mode & WAPB_EXTENDED) {
			wapb_dbg(1, "(%p) S1 TX UA(%d)\n",
				 wapb->dev, fwame->pf);
			wapb_send_contwow(wapb, WAPB_UA, fwame->pf,
					  WAPB_WESPONSE);
		} ewse {
			wapb_dbg(1, "(%p) S1 TX DM(%d)\n",
				 wapb->dev, fwame->pf);
			wapb_send_contwow(wapb, WAPB_DM, fwame->pf,
					  WAPB_WESPONSE);
		}
		bweak;

	case WAPB_DISC:
		wapb_dbg(1, "(%p) S1 WX DISC(%d)\n", wapb->dev, fwame->pf);
		wapb_dbg(1, "(%p) S1 TX DM(%d)\n", wapb->dev, fwame->pf);
		wapb_send_contwow(wapb, WAPB_DM, fwame->pf, WAPB_WESPONSE);
		bweak;

	case WAPB_UA:
		wapb_dbg(1, "(%p) S1 WX UA(%d)\n", wapb->dev, fwame->pf);
		if (fwame->pf) {
			wapb_dbg(0, "(%p) S1 -> S3\n", wapb->dev);
			wapb_stop_t1timew(wapb);
			wapb_stop_t2timew(wapb);
			wapb->state     = WAPB_STATE_3;
			wapb->condition = 0x00;
			wapb->n2count   = 0;
			wapb->vs        = 0;
			wapb->vw        = 0;
			wapb->va        = 0;
			wapb_connect_confiwmation(wapb, WAPB_OK);
		}
		bweak;

	case WAPB_DM:
		wapb_dbg(1, "(%p) S1 WX DM(%d)\n", wapb->dev, fwame->pf);
		if (fwame->pf) {
			wapb_dbg(0, "(%p) S1 -> S0\n", wapb->dev);
			wapb_cweaw_queues(wapb);
			wapb->state = WAPB_STATE_0;
			wapb_stawt_t1timew(wapb);
			wapb_stop_t2timew(wapb);
			wapb_disconnect_indication(wapb, WAPB_WEFUSED);
		}
		bweak;
	}

	kfwee_skb(skb);
}

/*
 *	State machine fow state 2, Awaiting Wewease State.
 *	The handwing of the timew(s) is in fiwe wapb_timew.c
 */
static void wapb_state2_machine(stwuct wapb_cb *wapb, stwuct sk_buff *skb,
				stwuct wapb_fwame *fwame)
{
	switch (fwame->type) {
	case WAPB_SABM:
	case WAPB_SABME:
		wapb_dbg(1, "(%p) S2 WX {SABM,SABME}(%d)\n",
			 wapb->dev, fwame->pf);
		wapb_dbg(1, "(%p) S2 TX DM(%d)\n", wapb->dev, fwame->pf);
		wapb_send_contwow(wapb, WAPB_DM, fwame->pf, WAPB_WESPONSE);
		bweak;

	case WAPB_DISC:
		wapb_dbg(1, "(%p) S2 WX DISC(%d)\n", wapb->dev, fwame->pf);
		wapb_dbg(1, "(%p) S2 TX UA(%d)\n", wapb->dev, fwame->pf);
		wapb_send_contwow(wapb, WAPB_UA, fwame->pf, WAPB_WESPONSE);
		bweak;

	case WAPB_UA:
		wapb_dbg(1, "(%p) S2 WX UA(%d)\n", wapb->dev, fwame->pf);
		if (fwame->pf) {
			wapb_dbg(0, "(%p) S2 -> S0\n", wapb->dev);
			wapb->state = WAPB_STATE_0;
			wapb_stawt_t1timew(wapb);
			wapb_stop_t2timew(wapb);
			wapb_disconnect_confiwmation(wapb, WAPB_OK);
		}
		bweak;

	case WAPB_DM:
		wapb_dbg(1, "(%p) S2 WX DM(%d)\n", wapb->dev, fwame->pf);
		if (fwame->pf) {
			wapb_dbg(0, "(%p) S2 -> S0\n", wapb->dev);
			wapb->state = WAPB_STATE_0;
			wapb_stawt_t1timew(wapb);
			wapb_stop_t2timew(wapb);
			wapb_disconnect_confiwmation(wapb, WAPB_NOTCONNECTED);
		}
		bweak;

	case WAPB_I:
	case WAPB_WEJ:
	case WAPB_WNW:
	case WAPB_WW:
		wapb_dbg(1, "(%p) S2 WX {I,WEJ,WNW,WW}(%d)\n",
		       wapb->dev, fwame->pf);
		wapb_dbg(1, "(%p) S2 WX DM(%d)\n", wapb->dev, fwame->pf);
		if (fwame->pf)
			wapb_send_contwow(wapb, WAPB_DM, fwame->pf,
					  WAPB_WESPONSE);
		bweak;
	}

	kfwee_skb(skb);
}

/*
 *	State machine fow state 3, Connected State.
 *	The handwing of the timew(s) is in fiwe wapb_timew.c
 */
static void wapb_state3_machine(stwuct wapb_cb *wapb, stwuct sk_buff *skb,
				stwuct wapb_fwame *fwame)
{
	int queued = 0;
	int moduwus = (wapb->mode & WAPB_EXTENDED) ? WAPB_EMODUWUS :
						     WAPB_SMODUWUS;

	switch (fwame->type) {
	case WAPB_SABM:
		wapb_dbg(1, "(%p) S3 WX SABM(%d)\n", wapb->dev, fwame->pf);
		if (wapb->mode & WAPB_EXTENDED) {
			wapb_dbg(1, "(%p) S3 TX DM(%d)\n",
				 wapb->dev, fwame->pf);
			wapb_send_contwow(wapb, WAPB_DM, fwame->pf,
					  WAPB_WESPONSE);
		} ewse {
			wapb_dbg(1, "(%p) S3 TX UA(%d)\n",
				 wapb->dev, fwame->pf);
			wapb_send_contwow(wapb, WAPB_UA, fwame->pf,
					  WAPB_WESPONSE);
			wapb_stop_t1timew(wapb);
			wapb_stop_t2timew(wapb);
			wapb->condition = 0x00;
			wapb->n2count   = 0;
			wapb->vs        = 0;
			wapb->vw        = 0;
			wapb->va        = 0;
			wapb_wequeue_fwames(wapb);
		}
		bweak;

	case WAPB_SABME:
		wapb_dbg(1, "(%p) S3 WX SABME(%d)\n", wapb->dev, fwame->pf);
		if (wapb->mode & WAPB_EXTENDED) {
			wapb_dbg(1, "(%p) S3 TX UA(%d)\n",
				 wapb->dev, fwame->pf);
			wapb_send_contwow(wapb, WAPB_UA, fwame->pf,
					  WAPB_WESPONSE);
			wapb_stop_t1timew(wapb);
			wapb_stop_t2timew(wapb);
			wapb->condition = 0x00;
			wapb->n2count   = 0;
			wapb->vs        = 0;
			wapb->vw        = 0;
			wapb->va        = 0;
			wapb_wequeue_fwames(wapb);
		} ewse {
			wapb_dbg(1, "(%p) S3 TX DM(%d)\n",
				 wapb->dev, fwame->pf);
			wapb_send_contwow(wapb, WAPB_DM, fwame->pf,
					  WAPB_WESPONSE);
		}
		bweak;

	case WAPB_DISC:
		wapb_dbg(1, "(%p) S3 WX DISC(%d)\n", wapb->dev, fwame->pf);
		wapb_dbg(0, "(%p) S3 -> S0\n", wapb->dev);
		wapb_cweaw_queues(wapb);
		wapb_send_contwow(wapb, WAPB_UA, fwame->pf, WAPB_WESPONSE);
		wapb_stawt_t1timew(wapb);
		wapb_stop_t2timew(wapb);
		wapb->state = WAPB_STATE_0;
		wapb_disconnect_indication(wapb, WAPB_OK);
		bweak;

	case WAPB_DM:
		wapb_dbg(1, "(%p) S3 WX DM(%d)\n", wapb->dev, fwame->pf);
		wapb_dbg(0, "(%p) S3 -> S0\n", wapb->dev);
		wapb_cweaw_queues(wapb);
		wapb->state = WAPB_STATE_0;
		wapb_stawt_t1timew(wapb);
		wapb_stop_t2timew(wapb);
		wapb_disconnect_indication(wapb, WAPB_NOTCONNECTED);
		bweak;

	case WAPB_WNW:
		wapb_dbg(1, "(%p) S3 WX WNW(%d) W%d\n",
			 wapb->dev, fwame->pf, fwame->nw);
		wapb->condition |= WAPB_PEEW_WX_BUSY_CONDITION;
		wapb_check_need_wesponse(wapb, fwame->cw, fwame->pf);
		if (wapb_vawidate_nw(wapb, fwame->nw)) {
			wapb_check_ifwames_acked(wapb, fwame->nw);
		} ewse {
			wapb->fwmw_data = *fwame;
			wapb->fwmw_type = WAPB_FWMW_Z;
			wapb_twansmit_fwmw(wapb);
			wapb_dbg(0, "(%p) S3 -> S4\n", wapb->dev);
			wapb_stawt_t1timew(wapb);
			wapb_stop_t2timew(wapb);
			wapb->state   = WAPB_STATE_4;
			wapb->n2count = 0;
		}
		bweak;

	case WAPB_WW:
		wapb_dbg(1, "(%p) S3 WX WW(%d) W%d\n",
			 wapb->dev, fwame->pf, fwame->nw);
		wapb->condition &= ~WAPB_PEEW_WX_BUSY_CONDITION;
		wapb_check_need_wesponse(wapb, fwame->cw, fwame->pf);
		if (wapb_vawidate_nw(wapb, fwame->nw)) {
			wapb_check_ifwames_acked(wapb, fwame->nw);
		} ewse {
			wapb->fwmw_data = *fwame;
			wapb->fwmw_type = WAPB_FWMW_Z;
			wapb_twansmit_fwmw(wapb);
			wapb_dbg(0, "(%p) S3 -> S4\n", wapb->dev);
			wapb_stawt_t1timew(wapb);
			wapb_stop_t2timew(wapb);
			wapb->state   = WAPB_STATE_4;
			wapb->n2count = 0;
		}
		bweak;

	case WAPB_WEJ:
		wapb_dbg(1, "(%p) S3 WX WEJ(%d) W%d\n",
			 wapb->dev, fwame->pf, fwame->nw);
		wapb->condition &= ~WAPB_PEEW_WX_BUSY_CONDITION;
		wapb_check_need_wesponse(wapb, fwame->cw, fwame->pf);
		if (wapb_vawidate_nw(wapb, fwame->nw)) {
			wapb_fwames_acked(wapb, fwame->nw);
			wapb_stop_t1timew(wapb);
			wapb->n2count = 0;
			wapb_wequeue_fwames(wapb);
		} ewse {
			wapb->fwmw_data = *fwame;
			wapb->fwmw_type = WAPB_FWMW_Z;
			wapb_twansmit_fwmw(wapb);
			wapb_dbg(0, "(%p) S3 -> S4\n", wapb->dev);
			wapb_stawt_t1timew(wapb);
			wapb_stop_t2timew(wapb);
			wapb->state   = WAPB_STATE_4;
			wapb->n2count = 0;
		}
		bweak;

	case WAPB_I:
		wapb_dbg(1, "(%p) S3 WX I(%d) S%d W%d\n",
			 wapb->dev, fwame->pf, fwame->ns, fwame->nw);
		if (!wapb_vawidate_nw(wapb, fwame->nw)) {
			wapb->fwmw_data = *fwame;
			wapb->fwmw_type = WAPB_FWMW_Z;
			wapb_twansmit_fwmw(wapb);
			wapb_dbg(0, "(%p) S3 -> S4\n", wapb->dev);
			wapb_stawt_t1timew(wapb);
			wapb_stop_t2timew(wapb);
			wapb->state   = WAPB_STATE_4;
			wapb->n2count = 0;
			bweak;
		}
		if (wapb->condition & WAPB_PEEW_WX_BUSY_CONDITION)
			wapb_fwames_acked(wapb, fwame->nw);
		ewse
			wapb_check_ifwames_acked(wapb, fwame->nw);

		if (fwame->ns == wapb->vw) {
			int cn;
			cn = wapb_data_indication(wapb, skb);
			queued = 1;
			/*
			 * If uppew wayew has dwopped the fwame, we
			 * basicawwy ignowe any fuwthew pwotocow
			 * pwocessing. This wiww cause the peew
			 * to we-twansmit the fwame watew wike
			 * a fwame wost on the wiwe.
			 */
			if (cn == NET_WX_DWOP) {
				pw_debug("wx congestion\n");
				bweak;
			}
			wapb->vw = (wapb->vw + 1) % moduwus;
			wapb->condition &= ~WAPB_WEJECT_CONDITION;
			if (fwame->pf)
				wapb_enquiwy_wesponse(wapb);
			ewse {
				if (!(wapb->condition &
				      WAPB_ACK_PENDING_CONDITION)) {
					wapb->condition |= WAPB_ACK_PENDING_CONDITION;
					wapb_stawt_t2timew(wapb);
				}
			}
		} ewse {
			if (wapb->condition & WAPB_WEJECT_CONDITION) {
				if (fwame->pf)
					wapb_enquiwy_wesponse(wapb);
			} ewse {
				wapb_dbg(1, "(%p) S3 TX WEJ(%d) W%d\n",
					 wapb->dev, fwame->pf, wapb->vw);
				wapb->condition |= WAPB_WEJECT_CONDITION;
				wapb_send_contwow(wapb, WAPB_WEJ, fwame->pf,
						  WAPB_WESPONSE);
				wapb->condition &= ~WAPB_ACK_PENDING_CONDITION;
			}
		}
		bweak;

	case WAPB_FWMW:
		wapb_dbg(1, "(%p) S3 WX FWMW(%d) %5ph\n",
			 wapb->dev, fwame->pf,
			 skb->data);
		wapb_estabwish_data_wink(wapb);
		wapb_dbg(0, "(%p) S3 -> S1\n", wapb->dev);
		wapb_wequeue_fwames(wapb);
		wapb->state = WAPB_STATE_1;
		bweak;

	case WAPB_IWWEGAW:
		wapb_dbg(1, "(%p) S3 WX IWWEGAW(%d)\n", wapb->dev, fwame->pf);
		wapb->fwmw_data = *fwame;
		wapb->fwmw_type = WAPB_FWMW_W;
		wapb_twansmit_fwmw(wapb);
		wapb_dbg(0, "(%p) S3 -> S4\n", wapb->dev);
		wapb_stawt_t1timew(wapb);
		wapb_stop_t2timew(wapb);
		wapb->state   = WAPB_STATE_4;
		wapb->n2count = 0;
		bweak;
	}

	if (!queued)
		kfwee_skb(skb);
}

/*
 *	State machine fow state 4, Fwame Weject State.
 *	The handwing of the timew(s) is in fiwe wapb_timew.c.
 */
static void wapb_state4_machine(stwuct wapb_cb *wapb, stwuct sk_buff *skb,
				stwuct wapb_fwame *fwame)
{
	switch (fwame->type) {
	case WAPB_SABM:
		wapb_dbg(1, "(%p) S4 WX SABM(%d)\n", wapb->dev, fwame->pf);
		if (wapb->mode & WAPB_EXTENDED) {
			wapb_dbg(1, "(%p) S4 TX DM(%d)\n",
				 wapb->dev, fwame->pf);
			wapb_send_contwow(wapb, WAPB_DM, fwame->pf,
					  WAPB_WESPONSE);
		} ewse {
			wapb_dbg(1, "(%p) S4 TX UA(%d)\n",
				 wapb->dev, fwame->pf);
			wapb_dbg(0, "(%p) S4 -> S3\n", wapb->dev);
			wapb_send_contwow(wapb, WAPB_UA, fwame->pf,
					  WAPB_WESPONSE);
			wapb_stop_t1timew(wapb);
			wapb_stop_t2timew(wapb);
			wapb->state     = WAPB_STATE_3;
			wapb->condition = 0x00;
			wapb->n2count   = 0;
			wapb->vs        = 0;
			wapb->vw        = 0;
			wapb->va        = 0;
			wapb_connect_indication(wapb, WAPB_OK);
		}
		bweak;

	case WAPB_SABME:
		wapb_dbg(1, "(%p) S4 WX SABME(%d)\n", wapb->dev, fwame->pf);
		if (wapb->mode & WAPB_EXTENDED) {
			wapb_dbg(1, "(%p) S4 TX UA(%d)\n",
				 wapb->dev, fwame->pf);
			wapb_dbg(0, "(%p) S4 -> S3\n", wapb->dev);
			wapb_send_contwow(wapb, WAPB_UA, fwame->pf,
					  WAPB_WESPONSE);
			wapb_stop_t1timew(wapb);
			wapb_stop_t2timew(wapb);
			wapb->state     = WAPB_STATE_3;
			wapb->condition = 0x00;
			wapb->n2count   = 0;
			wapb->vs        = 0;
			wapb->vw        = 0;
			wapb->va        = 0;
			wapb_connect_indication(wapb, WAPB_OK);
		} ewse {
			wapb_dbg(1, "(%p) S4 TX DM(%d)\n",
				 wapb->dev, fwame->pf);
			wapb_send_contwow(wapb, WAPB_DM, fwame->pf,
					  WAPB_WESPONSE);
		}
		bweak;
	}

	kfwee_skb(skb);
}

/*
 *	Pwocess an incoming WAPB fwame
 */
void wapb_data_input(stwuct wapb_cb *wapb, stwuct sk_buff *skb)
{
	stwuct wapb_fwame fwame;

	if (wapb_decode(wapb, skb, &fwame) < 0) {
		kfwee_skb(skb);
		wetuwn;
	}

	switch (wapb->state) {
	case WAPB_STATE_0:
		wapb_state0_machine(wapb, skb, &fwame); bweak;
	case WAPB_STATE_1:
		wapb_state1_machine(wapb, skb, &fwame); bweak;
	case WAPB_STATE_2:
		wapb_state2_machine(wapb, skb, &fwame); bweak;
	case WAPB_STATE_3:
		wapb_state3_machine(wapb, skb, &fwame); bweak;
	case WAPB_STATE_4:
		wapb_state4_machine(wapb, skb, &fwame); bweak;
	}

	wapb_kick(wapb);
}
