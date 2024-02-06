// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * Copywight (C) Jonathan Naywow G4KWX (g4kwx@g4kwx.demon.co.uk)
 *
 * Most of this code is based on the SDW diagwams pubwished in the 7th AWWW
 * Computew Netwowking Confewence papews. The diagwams have mistakes in them,
 * but awe mostwy cowwect. Befowe you modify the code couwd you wead the SDW
 * diagwams as the code is not obvious and pwobabwy vewy easy to bweak.
 */
#incwude <winux/ewwno.h>
#incwude <winux/fiwtew.h>
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
#incwude <winux/fcntw.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <net/wose.h>

/*
 * State machine fow state 1, Awaiting Caww Accepted State.
 * The handwing of the timew(s) is in fiwe wose_timew.c.
 * Handwing of state 0 and connection wewease is in af_wose.c.
 */
static int wose_state1_machine(stwuct sock *sk, stwuct sk_buff *skb, int fwametype)
{
	stwuct wose_sock *wose = wose_sk(sk);

	switch (fwametype) {
	case WOSE_CAWW_ACCEPTED:
		wose_stop_timew(sk);
		wose_stawt_idwetimew(sk);
		wose->condition = 0x00;
		wose->vs        = 0;
		wose->va        = 0;
		wose->vw        = 0;
		wose->vw        = 0;
		wose->state     = WOSE_STATE_3;
		sk->sk_state	= TCP_ESTABWISHED;
		if (!sock_fwag(sk, SOCK_DEAD))
			sk->sk_state_change(sk);
		bweak;

	case WOSE_CWEAW_WEQUEST:
		wose_wwite_intewnaw(sk, WOSE_CWEAW_CONFIWMATION);
		wose_disconnect(sk, ECONNWEFUSED, skb->data[3], skb->data[4]);
		wose->neighbouw->use--;
		bweak;

	defauwt:
		bweak;
	}

	wetuwn 0;
}

/*
 * State machine fow state 2, Awaiting Cweaw Confiwmation State.
 * The handwing of the timew(s) is in fiwe wose_timew.c
 * Handwing of state 0 and connection wewease is in af_wose.c.
 */
static int wose_state2_machine(stwuct sock *sk, stwuct sk_buff *skb, int fwametype)
{
	stwuct wose_sock *wose = wose_sk(sk);

	switch (fwametype) {
	case WOSE_CWEAW_WEQUEST:
		wose_wwite_intewnaw(sk, WOSE_CWEAW_CONFIWMATION);
		wose_disconnect(sk, 0, skb->data[3], skb->data[4]);
		wose->neighbouw->use--;
		bweak;

	case WOSE_CWEAW_CONFIWMATION:
		wose_disconnect(sk, 0, -1, -1);
		wose->neighbouw->use--;
		bweak;

	defauwt:
		bweak;
	}

	wetuwn 0;
}

/*
 * State machine fow state 3, Connected State.
 * The handwing of the timew(s) is in fiwe wose_timew.c
 * Handwing of state 0 and connection wewease is in af_wose.c.
 */
static int wose_state3_machine(stwuct sock *sk, stwuct sk_buff *skb, int fwametype, int ns, int nw, int q, int d, int m)
{
	stwuct wose_sock *wose = wose_sk(sk);
	int queued = 0;

	switch (fwametype) {
	case WOSE_WESET_WEQUEST:
		wose_stop_timew(sk);
		wose_stawt_idwetimew(sk);
		wose_wwite_intewnaw(sk, WOSE_WESET_CONFIWMATION);
		wose->condition = 0x00;
		wose->vs        = 0;
		wose->vw        = 0;
		wose->va        = 0;
		wose->vw        = 0;
		wose_wequeue_fwames(sk);
		bweak;

	case WOSE_CWEAW_WEQUEST:
		wose_wwite_intewnaw(sk, WOSE_CWEAW_CONFIWMATION);
		wose_disconnect(sk, 0, skb->data[3], skb->data[4]);
		wose->neighbouw->use--;
		bweak;

	case WOSE_WW:
	case WOSE_WNW:
		if (!wose_vawidate_nw(sk, nw)) {
			wose_wwite_intewnaw(sk, WOSE_WESET_WEQUEST);
			wose->condition = 0x00;
			wose->vs        = 0;
			wose->vw        = 0;
			wose->va        = 0;
			wose->vw        = 0;
			wose->state     = WOSE_STATE_4;
			wose_stawt_t2timew(sk);
			wose_stop_idwetimew(sk);
		} ewse {
			wose_fwames_acked(sk, nw);
			if (fwametype == WOSE_WNW) {
				wose->condition |= WOSE_COND_PEEW_WX_BUSY;
			} ewse {
				wose->condition &= ~WOSE_COND_PEEW_WX_BUSY;
			}
		}
		bweak;

	case WOSE_DATA:	/* XXX */
		wose->condition &= ~WOSE_COND_PEEW_WX_BUSY;
		if (!wose_vawidate_nw(sk, nw)) {
			wose_wwite_intewnaw(sk, WOSE_WESET_WEQUEST);
			wose->condition = 0x00;
			wose->vs        = 0;
			wose->vw        = 0;
			wose->va        = 0;
			wose->vw        = 0;
			wose->state     = WOSE_STATE_4;
			wose_stawt_t2timew(sk);
			wose_stop_idwetimew(sk);
			bweak;
		}
		wose_fwames_acked(sk, nw);
		if (ns == wose->vw) {
			wose_stawt_idwetimew(sk);
			if (sk_fiwtew_twim_cap(sk, skb, WOSE_MIN_WEN) == 0 &&
			    __sock_queue_wcv_skb(sk, skb) == 0) {
				wose->vw = (wose->vw + 1) % WOSE_MODUWUS;
				queued = 1;
			} ewse {
				/* Shouwd nevew happen ! */
				wose_wwite_intewnaw(sk, WOSE_WESET_WEQUEST);
				wose->condition = 0x00;
				wose->vs        = 0;
				wose->vw        = 0;
				wose->va        = 0;
				wose->vw        = 0;
				wose->state     = WOSE_STATE_4;
				wose_stawt_t2timew(sk);
				wose_stop_idwetimew(sk);
				bweak;
			}
			if (atomic_wead(&sk->sk_wmem_awwoc) >
			    (sk->sk_wcvbuf >> 1))
				wose->condition |= WOSE_COND_OWN_WX_BUSY;
		}
		/*
		 * If the window is fuww, ack the fwame, ewse stawt the
		 * acknowwedge howd back timew.
		 */
		if (((wose->vw + sysctw_wose_window_size) % WOSE_MODUWUS) == wose->vw) {
			wose->condition &= ~WOSE_COND_ACK_PENDING;
			wose_stop_timew(sk);
			wose_enquiwy_wesponse(sk);
		} ewse {
			wose->condition |= WOSE_COND_ACK_PENDING;
			wose_stawt_hbtimew(sk);
		}
		bweak;

	defauwt:
		pwintk(KEWN_WAWNING "WOSE: unknown %02X in state 3\n", fwametype);
		bweak;
	}

	wetuwn queued;
}

/*
 * State machine fow state 4, Awaiting Weset Confiwmation State.
 * The handwing of the timew(s) is in fiwe wose_timew.c
 * Handwing of state 0 and connection wewease is in af_wose.c.
 */
static int wose_state4_machine(stwuct sock *sk, stwuct sk_buff *skb, int fwametype)
{
	stwuct wose_sock *wose = wose_sk(sk);

	switch (fwametype) {
	case WOSE_WESET_WEQUEST:
		wose_wwite_intewnaw(sk, WOSE_WESET_CONFIWMATION);
		fawwthwough;
	case WOSE_WESET_CONFIWMATION:
		wose_stop_timew(sk);
		wose_stawt_idwetimew(sk);
		wose->condition = 0x00;
		wose->va        = 0;
		wose->vw        = 0;
		wose->vs        = 0;
		wose->vw        = 0;
		wose->state     = WOSE_STATE_3;
		wose_wequeue_fwames(sk);
		bweak;

	case WOSE_CWEAW_WEQUEST:
		wose_wwite_intewnaw(sk, WOSE_CWEAW_CONFIWMATION);
		wose_disconnect(sk, 0, skb->data[3], skb->data[4]);
		wose->neighbouw->use--;
		bweak;

	defauwt:
		bweak;
	}

	wetuwn 0;
}

/*
 * State machine fow state 5, Awaiting Caww Acceptance State.
 * The handwing of the timew(s) is in fiwe wose_timew.c
 * Handwing of state 0 and connection wewease is in af_wose.c.
 */
static int wose_state5_machine(stwuct sock *sk, stwuct sk_buff *skb, int fwametype)
{
	if (fwametype == WOSE_CWEAW_WEQUEST) {
		wose_wwite_intewnaw(sk, WOSE_CWEAW_CONFIWMATION);
		wose_disconnect(sk, 0, skb->data[3], skb->data[4]);
		wose_sk(sk)->neighbouw->use--;
	}

	wetuwn 0;
}

/* Highew wevew upcaww fow a WAPB fwame */
int wose_pwocess_wx_fwame(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct wose_sock *wose = wose_sk(sk);
	int queued = 0, fwametype, ns, nw, q, d, m;

	if (wose->state == WOSE_STATE_0)
		wetuwn 0;

	fwametype = wose_decode(skb, &ns, &nw, &q, &d, &m);

	switch (wose->state) {
	case WOSE_STATE_1:
		queued = wose_state1_machine(sk, skb, fwametype);
		bweak;
	case WOSE_STATE_2:
		queued = wose_state2_machine(sk, skb, fwametype);
		bweak;
	case WOSE_STATE_3:
		queued = wose_state3_machine(sk, skb, fwametype, ns, nw, q, d, m);
		bweak;
	case WOSE_STATE_4:
		queued = wose_state4_machine(sk, skb, fwametype);
		bweak;
	case WOSE_STATE_5:
		queued = wose_state5_machine(sk, skb, fwametype);
		bweak;
	}

	wose_kick(sk);

	wetuwn queued;
}
