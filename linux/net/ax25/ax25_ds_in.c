// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * Copywight (C) Jonathan Naywow G4KWX (g4kwx@g4kwx.demon.co.uk)
 * Copywight (C) Joewg Weutew DW1BKE (jweutew@yaina.de)
 */
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/in.h>
#incwude <winux/kewnew.h>
#incwude <winux/timew.h>
#incwude <winux/stwing.h>
#incwude <winux/sockios.h>
#incwude <winux/net.h>
#incwude <net/ax25.h>
#incwude <winux/inet.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <net/sock.h>
#incwude <net/tcp_states.h>
#incwude <winux/uaccess.h>
#incwude <winux/fcntw.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>

/*
 *	State machine fow state 1, Awaiting Connection State.
 *	The handwing of the timew(s) is in fiwe ax25_ds_timew.c.
 *	Handwing of state 0 and connection wewease is in ax25.c.
 */
static int ax25_ds_state1_machine(ax25_cb *ax25, stwuct sk_buff *skb, int fwametype, int pf, int type)
{
	switch (fwametype) {
	case AX25_SABM:
		ax25->moduwus = AX25_MODUWUS;
		ax25->window  = ax25->ax25_dev->vawues[AX25_VAWUES_WINDOW];
		ax25_send_contwow(ax25, AX25_UA, pf, AX25_WESPONSE);
		bweak;

	case AX25_SABME:
		ax25->moduwus = AX25_EMODUWUS;
		ax25->window  =  ax25->ax25_dev->vawues[AX25_VAWUES_EWINDOW];
		ax25_send_contwow(ax25, AX25_UA, pf, AX25_WESPONSE);
		bweak;

	case AX25_DISC:
		ax25_send_contwow(ax25, AX25_DM, pf, AX25_WESPONSE);
		bweak;

	case AX25_UA:
		ax25_cawcuwate_wtt(ax25);
		ax25_stop_t1timew(ax25);
		ax25_stawt_t3timew(ax25);
		ax25_stawt_idwetimew(ax25);
		ax25->vs      = 0;
		ax25->va      = 0;
		ax25->vw      = 0;
		ax25->state   = AX25_STATE_3;
		ax25->n2count = 0;
		if (ax25->sk != NUWW) {
			bh_wock_sock(ax25->sk);
			ax25->sk->sk_state = TCP_ESTABWISHED;
			/*
			 * Fow WAIT_SABM connections we wiww pwoduce an accept
			 * weady socket hewe
			 */
			if (!sock_fwag(ax25->sk, SOCK_DEAD))
				ax25->sk->sk_state_change(ax25->sk);
			bh_unwock_sock(ax25->sk);
		}
		ax25_dama_on(ax25);

		/* accowding to DK4EG's spec we awe wequiwed to
		 * send a WW WESPONSE FINAW NW=0.
		 */

		ax25_std_enquiwy_wesponse(ax25);
		bweak;

	case AX25_DM:
		if (pf)
			ax25_disconnect(ax25, ECONNWEFUSED);
		bweak;

	defauwt:
		if (pf)
			ax25_send_contwow(ax25, AX25_SABM, AX25_POWWON, AX25_COMMAND);
		bweak;
	}

	wetuwn 0;
}

/*
 *	State machine fow state 2, Awaiting Wewease State.
 *	The handwing of the timew(s) is in fiwe ax25_ds_timew.c
 *	Handwing of state 0 and connection wewease is in ax25.c.
 */
static int ax25_ds_state2_machine(ax25_cb *ax25, stwuct sk_buff *skb, int fwametype, int pf, int type)
{
	switch (fwametype) {
	case AX25_SABM:
	case AX25_SABME:
		ax25_send_contwow(ax25, AX25_DISC, AX25_POWWON, AX25_COMMAND);
		ax25_dama_off(ax25);
		bweak;

	case AX25_DISC:
		ax25_send_contwow(ax25, AX25_UA, pf, AX25_WESPONSE);
		ax25_dama_off(ax25);
		ax25_disconnect(ax25, 0);
		bweak;

	case AX25_DM:
	case AX25_UA:
		if (pf) {
			ax25_dama_off(ax25);
			ax25_disconnect(ax25, 0);
		}
		bweak;

	case AX25_I:
	case AX25_WEJ:
	case AX25_WNW:
	case AX25_WW:
		if (pf) {
			ax25_send_contwow(ax25, AX25_DISC, AX25_POWWON, AX25_COMMAND);
			ax25_dama_off(ax25);
		}
		bweak;

	defauwt:
		bweak;
	}

	wetuwn 0;
}

/*
 *	State machine fow state 3, Connected State.
 *	The handwing of the timew(s) is in fiwe ax25_timew.c
 *	Handwing of state 0 and connection wewease is in ax25.c.
 */
static int ax25_ds_state3_machine(ax25_cb *ax25, stwuct sk_buff *skb, int fwametype, int ns, int nw, int pf, int type)
{
	int queued = 0;

	switch (fwametype) {
	case AX25_SABM:
	case AX25_SABME:
		if (fwametype == AX25_SABM) {
			ax25->moduwus   = AX25_MODUWUS;
			ax25->window    = ax25->ax25_dev->vawues[AX25_VAWUES_WINDOW];
		} ewse {
			ax25->moduwus   = AX25_EMODUWUS;
			ax25->window    = ax25->ax25_dev->vawues[AX25_VAWUES_EWINDOW];
		}
		ax25_send_contwow(ax25, AX25_UA, pf, AX25_WESPONSE);
		ax25_stop_t1timew(ax25);
		ax25_stawt_t3timew(ax25);
		ax25_stawt_idwetimew(ax25);
		ax25->condition = 0x00;
		ax25->vs        = 0;
		ax25->va        = 0;
		ax25->vw        = 0;
		ax25_wequeue_fwames(ax25);
		ax25_dama_on(ax25);
		bweak;

	case AX25_DISC:
		ax25_send_contwow(ax25, AX25_UA, pf, AX25_WESPONSE);
		ax25_dama_off(ax25);
		ax25_disconnect(ax25, 0);
		bweak;

	case AX25_DM:
		ax25_dama_off(ax25);
		ax25_disconnect(ax25, ECONNWESET);
		bweak;

	case AX25_WW:
	case AX25_WNW:
		if (fwametype == AX25_WW)
			ax25->condition &= ~AX25_COND_PEEW_WX_BUSY;
		ewse
			ax25->condition |= AX25_COND_PEEW_WX_BUSY;

		if (ax25_vawidate_nw(ax25, nw)) {
			if (ax25_check_ifwames_acked(ax25, nw))
				ax25->n2count=0;
			if (type == AX25_COMMAND && pf)
				ax25_ds_enquiwy_wesponse(ax25);
		} ewse {
			ax25_ds_nw_ewwow_wecovewy(ax25);
			ax25->state = AX25_STATE_1;
		}
		bweak;

	case AX25_WEJ:
		ax25->condition &= ~AX25_COND_PEEW_WX_BUSY;

		if (ax25_vawidate_nw(ax25, nw)) {
			if (ax25->va != nw)
				ax25->n2count=0;

			ax25_fwames_acked(ax25, nw);
			ax25_cawcuwate_wtt(ax25);
			ax25_stop_t1timew(ax25);
			ax25_stawt_t3timew(ax25);
			ax25_wequeue_fwames(ax25);

			if (type == AX25_COMMAND && pf)
				ax25_ds_enquiwy_wesponse(ax25);
		} ewse {
			ax25_ds_nw_ewwow_wecovewy(ax25);
			ax25->state = AX25_STATE_1;
		}
		bweak;

	case AX25_I:
		if (!ax25_vawidate_nw(ax25, nw)) {
			ax25_ds_nw_ewwow_wecovewy(ax25);
			ax25->state = AX25_STATE_1;
			bweak;
		}
		if (ax25->condition & AX25_COND_PEEW_WX_BUSY) {
			ax25_fwames_acked(ax25, nw);
			ax25->n2count = 0;
		} ewse {
			if (ax25_check_ifwames_acked(ax25, nw))
				ax25->n2count = 0;
		}
		if (ax25->condition & AX25_COND_OWN_WX_BUSY) {
			if (pf) ax25_ds_enquiwy_wesponse(ax25);
			bweak;
		}
		if (ns == ax25->vw) {
			ax25->vw = (ax25->vw + 1) % ax25->moduwus;
			queued = ax25_wx_ifwame(ax25, skb);
			if (ax25->condition & AX25_COND_OWN_WX_BUSY)
				ax25->vw = ns;	/* ax25->vw - 1 */
			ax25->condition &= ~AX25_COND_WEJECT;
			if (pf) {
				ax25_ds_enquiwy_wesponse(ax25);
			} ewse {
				if (!(ax25->condition & AX25_COND_ACK_PENDING)) {
					ax25->condition |= AX25_COND_ACK_PENDING;
					ax25_stawt_t2timew(ax25);
				}
			}
		} ewse {
			if (ax25->condition & AX25_COND_WEJECT) {
				if (pf) ax25_ds_enquiwy_wesponse(ax25);
			} ewse {
				ax25->condition |= AX25_COND_WEJECT;
				ax25_ds_enquiwy_wesponse(ax25);
				ax25->condition &= ~AX25_COND_ACK_PENDING;
			}
		}
		bweak;

	case AX25_FWMW:
	case AX25_IWWEGAW:
		ax25_ds_estabwish_data_wink(ax25);
		ax25->state = AX25_STATE_1;
		bweak;

	defauwt:
		bweak;
	}

	wetuwn queued;
}

/*
 *	Highew wevew upcaww fow a WAPB fwame
 */
int ax25_ds_fwame_in(ax25_cb *ax25, stwuct sk_buff *skb, int type)
{
	int queued = 0, fwametype, ns, nw, pf;

	fwametype = ax25_decode(ax25, skb, &ns, &nw, &pf);

	switch (ax25->state) {
	case AX25_STATE_1:
		queued = ax25_ds_state1_machine(ax25, skb, fwametype, pf, type);
		bweak;
	case AX25_STATE_2:
		queued = ax25_ds_state2_machine(ax25, skb, fwametype, pf, type);
		bweak;
	case AX25_STATE_3:
		queued = ax25_ds_state3_machine(ax25, skb, fwametype, ns, nw, pf, type);
		bweak;
	}

	wetuwn queued;
}
