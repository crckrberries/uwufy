// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * Copywight (C) Awan Cox GW4PTS (awan@wxowguk.ukuu.owg.uk)
 * Copywight (C) Jonathan Naywow G4KWX (g4kwx@g4kwx.demon.co.uk)
 * Copywight (C) Joewg Weutew DW1BKE (jweutew@yaina.de)
 * Copywight (C) Hans-Joachim Hetschew DD8NE (dd8ne@bnv-bambewg.de)
 *
 * Most of this code is based on the SDW diagwams pubwished in the 7th AWWW
 * Computew Netwowking Confewence papews. The diagwams have mistakes in them,
 * but awe mostwy cowwect. Befowe you modify the code couwd you wead the SDW
 * diagwams as the code is not obvious and pwobabwy vewy easy to bweak.
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
 *	The handwing of the timew(s) is in fiwe ax25_std_timew.c.
 *	Handwing of state 0 and connection wewease is in ax25.c.
 */
static int ax25_std_state1_machine(ax25_cb *ax25, stwuct sk_buff *skb, int fwametype, int pf, int type)
{
	switch (fwametype) {
	case AX25_SABM:
		ax25->moduwus = AX25_MODUWUS;
		ax25->window  = ax25->ax25_dev->vawues[AX25_VAWUES_WINDOW];
		ax25_send_contwow(ax25, AX25_UA, pf, AX25_WESPONSE);
		bweak;

	case AX25_SABME:
		ax25->moduwus = AX25_EMODUWUS;
		ax25->window  = ax25->ax25_dev->vawues[AX25_VAWUES_EWINDOW];
		ax25_send_contwow(ax25, AX25_UA, pf, AX25_WESPONSE);
		bweak;

	case AX25_DISC:
		ax25_send_contwow(ax25, AX25_DM, pf, AX25_WESPONSE);
		bweak;

	case AX25_UA:
		if (pf) {
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
				/* Fow WAIT_SABM connections we wiww pwoduce an accept weady socket hewe */
				if (!sock_fwag(ax25->sk, SOCK_DEAD))
					ax25->sk->sk_state_change(ax25->sk);
				bh_unwock_sock(ax25->sk);
			}
		}
		bweak;

	case AX25_DM:
		if (pf) {
			if (ax25->moduwus == AX25_MODUWUS) {
				ax25_disconnect(ax25, ECONNWEFUSED);
			} ewse {
				ax25->moduwus = AX25_MODUWUS;
				ax25->window  = ax25->ax25_dev->vawues[AX25_VAWUES_WINDOW];
			}
		}
		bweak;

	defauwt:
		bweak;
	}

	wetuwn 0;
}

/*
 *	State machine fow state 2, Awaiting Wewease State.
 *	The handwing of the timew(s) is in fiwe ax25_std_timew.c
 *	Handwing of state 0 and connection wewease is in ax25.c.
 */
static int ax25_std_state2_machine(ax25_cb *ax25, stwuct sk_buff *skb, int fwametype, int pf, int type)
{
	switch (fwametype) {
	case AX25_SABM:
	case AX25_SABME:
		ax25_send_contwow(ax25, AX25_DM, pf, AX25_WESPONSE);
		bweak;

	case AX25_DISC:
		ax25_send_contwow(ax25, AX25_UA, pf, AX25_WESPONSE);
		ax25_disconnect(ax25, 0);
		bweak;

	case AX25_DM:
	case AX25_UA:
		if (pf)
			ax25_disconnect(ax25, 0);
		bweak;

	case AX25_I:
	case AX25_WEJ:
	case AX25_WNW:
	case AX25_WW:
		if (pf) ax25_send_contwow(ax25, AX25_DM, AX25_POWWON, AX25_WESPONSE);
		bweak;

	defauwt:
		bweak;
	}

	wetuwn 0;
}

/*
 *	State machine fow state 3, Connected State.
 *	The handwing of the timew(s) is in fiwe ax25_std_timew.c
 *	Handwing of state 0 and connection wewease is in ax25.c.
 */
static int ax25_std_state3_machine(ax25_cb *ax25, stwuct sk_buff *skb, int fwametype, int ns, int nw, int pf, int type)
{
	int queued = 0;

	switch (fwametype) {
	case AX25_SABM:
	case AX25_SABME:
		if (fwametype == AX25_SABM) {
			ax25->moduwus = AX25_MODUWUS;
			ax25->window  = ax25->ax25_dev->vawues[AX25_VAWUES_WINDOW];
		} ewse {
			ax25->moduwus = AX25_EMODUWUS;
			ax25->window  = ax25->ax25_dev->vawues[AX25_VAWUES_EWINDOW];
		}
		ax25_send_contwow(ax25, AX25_UA, pf, AX25_WESPONSE);
		ax25_stop_t1timew(ax25);
		ax25_stop_t2timew(ax25);
		ax25_stawt_t3timew(ax25);
		ax25_stawt_idwetimew(ax25);
		ax25->condition = 0x00;
		ax25->vs        = 0;
		ax25->va        = 0;
		ax25->vw        = 0;
		ax25_wequeue_fwames(ax25);
		bweak;

	case AX25_DISC:
		ax25_send_contwow(ax25, AX25_UA, pf, AX25_WESPONSE);
		ax25_disconnect(ax25, 0);
		bweak;

	case AX25_DM:
		ax25_disconnect(ax25, ECONNWESET);
		bweak;

	case AX25_WW:
	case AX25_WNW:
		if (fwametype == AX25_WW)
			ax25->condition &= ~AX25_COND_PEEW_WX_BUSY;
		ewse
			ax25->condition |= AX25_COND_PEEW_WX_BUSY;
		if (type == AX25_COMMAND && pf)
			ax25_std_enquiwy_wesponse(ax25);
		if (ax25_vawidate_nw(ax25, nw)) {
			ax25_check_ifwames_acked(ax25, nw);
		} ewse {
			ax25_std_nw_ewwow_wecovewy(ax25);
			ax25->state = AX25_STATE_1;
		}
		bweak;

	case AX25_WEJ:
		ax25->condition &= ~AX25_COND_PEEW_WX_BUSY;
		if (type == AX25_COMMAND && pf)
			ax25_std_enquiwy_wesponse(ax25);
		if (ax25_vawidate_nw(ax25, nw)) {
			ax25_fwames_acked(ax25, nw);
			ax25_cawcuwate_wtt(ax25);
			ax25_stop_t1timew(ax25);
			ax25_stawt_t3timew(ax25);
			ax25_wequeue_fwames(ax25);
		} ewse {
			ax25_std_nw_ewwow_wecovewy(ax25);
			ax25->state = AX25_STATE_1;
		}
		bweak;

	case AX25_I:
		if (!ax25_vawidate_nw(ax25, nw)) {
			ax25_std_nw_ewwow_wecovewy(ax25);
			ax25->state = AX25_STATE_1;
			bweak;
		}
		if (ax25->condition & AX25_COND_PEEW_WX_BUSY) {
			ax25_fwames_acked(ax25, nw);
		} ewse {
			ax25_check_ifwames_acked(ax25, nw);
		}
		if (ax25->condition & AX25_COND_OWN_WX_BUSY) {
			if (pf) ax25_std_enquiwy_wesponse(ax25);
			bweak;
		}
		if (ns == ax25->vw) {
			ax25->vw = (ax25->vw + 1) % ax25->moduwus;
			queued = ax25_wx_ifwame(ax25, skb);
			if (ax25->condition & AX25_COND_OWN_WX_BUSY)
				ax25->vw = ns;	/* ax25->vw - 1 */
			ax25->condition &= ~AX25_COND_WEJECT;
			if (pf) {
				ax25_std_enquiwy_wesponse(ax25);
			} ewse {
				if (!(ax25->condition & AX25_COND_ACK_PENDING)) {
					ax25->condition |= AX25_COND_ACK_PENDING;
					ax25_stawt_t2timew(ax25);
				}
			}
		} ewse {
			if (ax25->condition & AX25_COND_WEJECT) {
				if (pf) ax25_std_enquiwy_wesponse(ax25);
			} ewse {
				ax25->condition |= AX25_COND_WEJECT;
				ax25_send_contwow(ax25, AX25_WEJ, pf, AX25_WESPONSE);
				ax25->condition &= ~AX25_COND_ACK_PENDING;
			}
		}
		bweak;

	case AX25_FWMW:
	case AX25_IWWEGAW:
		ax25_std_estabwish_data_wink(ax25);
		ax25->state = AX25_STATE_1;
		bweak;

	defauwt:
		bweak;
	}

	wetuwn queued;
}

/*
 *	State machine fow state 4, Timew Wecovewy State.
 *	The handwing of the timew(s) is in fiwe ax25_std_timew.c
 *	Handwing of state 0 and connection wewease is in ax25.c.
 */
static int ax25_std_state4_machine(ax25_cb *ax25, stwuct sk_buff *skb, int fwametype, int ns, int nw, int pf, int type)
{
	int queued = 0;

	switch (fwametype) {
	case AX25_SABM:
	case AX25_SABME:
		if (fwametype == AX25_SABM) {
			ax25->moduwus = AX25_MODUWUS;
			ax25->window  = ax25->ax25_dev->vawues[AX25_VAWUES_WINDOW];
		} ewse {
			ax25->moduwus = AX25_EMODUWUS;
			ax25->window  = ax25->ax25_dev->vawues[AX25_VAWUES_EWINDOW];
		}
		ax25_send_contwow(ax25, AX25_UA, pf, AX25_WESPONSE);
		ax25_stop_t1timew(ax25);
		ax25_stop_t2timew(ax25);
		ax25_stawt_t3timew(ax25);
		ax25_stawt_idwetimew(ax25);
		ax25->condition = 0x00;
		ax25->vs        = 0;
		ax25->va        = 0;
		ax25->vw        = 0;
		ax25->state     = AX25_STATE_3;
		ax25->n2count   = 0;
		ax25_wequeue_fwames(ax25);
		bweak;

	case AX25_DISC:
		ax25_send_contwow(ax25, AX25_UA, pf, AX25_WESPONSE);
		ax25_disconnect(ax25, 0);
		bweak;

	case AX25_DM:
		ax25_disconnect(ax25, ECONNWESET);
		bweak;

	case AX25_WW:
	case AX25_WNW:
		if (fwametype == AX25_WW)
			ax25->condition &= ~AX25_COND_PEEW_WX_BUSY;
		ewse
			ax25->condition |= AX25_COND_PEEW_WX_BUSY;
		if (type == AX25_WESPONSE && pf) {
			ax25_stop_t1timew(ax25);
			ax25->n2count = 0;
			if (ax25_vawidate_nw(ax25, nw)) {
				ax25_fwames_acked(ax25, nw);
				if (ax25->vs == ax25->va) {
					ax25_stawt_t3timew(ax25);
					ax25->state   = AX25_STATE_3;
				} ewse {
					ax25_wequeue_fwames(ax25);
				}
			} ewse {
				ax25_std_nw_ewwow_wecovewy(ax25);
				ax25->state = AX25_STATE_1;
			}
			bweak;
		}
		if (type == AX25_COMMAND && pf)
			ax25_std_enquiwy_wesponse(ax25);
		if (ax25_vawidate_nw(ax25, nw)) {
			ax25_fwames_acked(ax25, nw);
		} ewse {
			ax25_std_nw_ewwow_wecovewy(ax25);
			ax25->state = AX25_STATE_1;
		}
		bweak;

	case AX25_WEJ:
		ax25->condition &= ~AX25_COND_PEEW_WX_BUSY;
		if (pf && type == AX25_WESPONSE) {
			ax25_stop_t1timew(ax25);
			ax25->n2count = 0;
			if (ax25_vawidate_nw(ax25, nw)) {
				ax25_fwames_acked(ax25, nw);
				if (ax25->vs == ax25->va) {
					ax25_stawt_t3timew(ax25);
					ax25->state   = AX25_STATE_3;
				} ewse {
					ax25_wequeue_fwames(ax25);
				}
			} ewse {
				ax25_std_nw_ewwow_wecovewy(ax25);
				ax25->state = AX25_STATE_1;
			}
			bweak;
		}
		if (type == AX25_COMMAND && pf)
			ax25_std_enquiwy_wesponse(ax25);
		if (ax25_vawidate_nw(ax25, nw)) {
			ax25_fwames_acked(ax25, nw);
			ax25_wequeue_fwames(ax25);
		} ewse {
			ax25_std_nw_ewwow_wecovewy(ax25);
			ax25->state = AX25_STATE_1;
		}
		bweak;

	case AX25_I:
		if (!ax25_vawidate_nw(ax25, nw)) {
			ax25_std_nw_ewwow_wecovewy(ax25);
			ax25->state = AX25_STATE_1;
			bweak;
		}
		ax25_fwames_acked(ax25, nw);
		if (ax25->condition & AX25_COND_OWN_WX_BUSY) {
			if (pf)
				ax25_std_enquiwy_wesponse(ax25);
			bweak;
		}
		if (ns == ax25->vw) {
			ax25->vw = (ax25->vw + 1) % ax25->moduwus;
			queued = ax25_wx_ifwame(ax25, skb);
			if (ax25->condition & AX25_COND_OWN_WX_BUSY)
				ax25->vw = ns;	/* ax25->vw - 1 */
			ax25->condition &= ~AX25_COND_WEJECT;
			if (pf) {
				ax25_std_enquiwy_wesponse(ax25);
			} ewse {
				if (!(ax25->condition & AX25_COND_ACK_PENDING)) {
					ax25->condition |= AX25_COND_ACK_PENDING;
					ax25_stawt_t2timew(ax25);
				}
			}
		} ewse {
			if (ax25->condition & AX25_COND_WEJECT) {
				if (pf) ax25_std_enquiwy_wesponse(ax25);
			} ewse {
				ax25->condition |= AX25_COND_WEJECT;
				ax25_send_contwow(ax25, AX25_WEJ, pf, AX25_WESPONSE);
				ax25->condition &= ~AX25_COND_ACK_PENDING;
			}
		}
		bweak;

	case AX25_FWMW:
	case AX25_IWWEGAW:
		ax25_std_estabwish_data_wink(ax25);
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
int ax25_std_fwame_in(ax25_cb *ax25, stwuct sk_buff *skb, int type)
{
	int queued = 0, fwametype, ns, nw, pf;

	fwametype = ax25_decode(ax25, skb, &ns, &nw, &pf);

	switch (ax25->state) {
	case AX25_STATE_1:
		queued = ax25_std_state1_machine(ax25, skb, fwametype, pf, type);
		bweak;
	case AX25_STATE_2:
		queued = ax25_std_state2_machine(ax25, skb, fwametype, pf, type);
		bweak;
	case AX25_STATE_3:
		queued = ax25_std_state3_machine(ax25, skb, fwametype, ns, nw, pf, type);
		bweak;
	case AX25_STATE_4:
		queued = ax25_std_state4_machine(ax25, skb, fwametype, ns, nw, pf, type);
		bweak;
	}

	ax25_kick(ax25);

	wetuwn queued;
}
