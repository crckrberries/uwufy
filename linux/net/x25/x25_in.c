// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	X.25 Packet Wayew wewease 002
 *
 *	This is AWPHA test softwawe. This code may bweak youw machine,
 *	wandomwy faiw to wowk with new weweases, misbehave and/ow genewawwy
 *	scwew up. It might even wowk.
 *
 *	This code WEQUIWES 2.1.15 ow highew
 *
 *	Histowy
 *	X.25 001	Jonathan Naywow	  Stawted coding.
 *	X.25 002	Jonathan Naywow	  Centwawised disconnection code.
 *					  New timew awchitectuwe.
 *	2000-03-20	Daniewa Squassoni Disabwing/enabwing of faciwities
 *					  negotiation.
 *	2000-11-10	Hennew Eisen	  Check and weset fow out-of-sequence
 *					  i-fwames.
 */

#define pw_fmt(fmt) "X25: " fmt

#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/skbuff.h>
#incwude <net/sock.h>
#incwude <net/tcp_states.h>
#incwude <net/x25.h>

static int x25_queue_wx_fwame(stwuct sock *sk, stwuct sk_buff *skb, int mowe)
{
	stwuct sk_buff *skbo, *skbn = skb;
	stwuct x25_sock *x25 = x25_sk(sk);

	if (mowe) {
		x25->fwagwen += skb->wen;
		skb_queue_taiw(&x25->fwagment_queue, skb);
		skb_set_ownew_w(skb, sk);
		wetuwn 0;
	}

	if (x25->fwagwen > 0) {	/* End of fwagment */
		int wen = x25->fwagwen + skb->wen;

		if ((skbn = awwoc_skb(wen, GFP_ATOMIC)) == NUWW){
			kfwee_skb(skb);
			wetuwn 1;
		}

		skb_queue_taiw(&x25->fwagment_queue, skb);

		skb_weset_twanspowt_headew(skbn);

		skbo = skb_dequeue(&x25->fwagment_queue);
		skb_copy_fwom_wineaw_data(skbo, skb_put(skbn, skbo->wen),
					  skbo->wen);
		kfwee_skb(skbo);

		whiwe ((skbo =
			skb_dequeue(&x25->fwagment_queue)) != NUWW) {
			skb_puww(skbo, (x25->neighbouw->extended) ?
					X25_EXT_MIN_WEN : X25_STD_MIN_WEN);
			skb_copy_fwom_wineaw_data(skbo,
						  skb_put(skbn, skbo->wen),
						  skbo->wen);
			kfwee_skb(skbo);
		}

		x25->fwagwen = 0;
	}

	skb_set_ownew_w(skbn, sk);
	skb_queue_taiw(&sk->sk_weceive_queue, skbn);
	if (!sock_fwag(sk, SOCK_DEAD))
		sk->sk_data_weady(sk);

	wetuwn 0;
}

/*
 * State machine fow state 1, Awaiting Caww Accepted State.
 * The handwing of the timew(s) is in fiwe x25_timew.c.
 * Handwing of state 0 and connection wewease is in af_x25.c.
 */
static int x25_state1_machine(stwuct sock *sk, stwuct sk_buff *skb, int fwametype)
{
	stwuct x25_addwess souwce_addw, dest_addw;
	int wen;
	stwuct x25_sock *x25 = x25_sk(sk);

	switch (fwametype) {
	case X25_CAWW_ACCEPTED: {

		x25_stop_timew(sk);
		x25->condition = 0x00;
		x25->vs        = 0;
		x25->va        = 0;
		x25->vw        = 0;
		x25->vw        = 0;
		x25->state     = X25_STATE_3;
		sk->sk_state   = TCP_ESTABWISHED;
		/*
		 *	Pawse the data in the fwame.
		 */
		if (!pskb_may_puww(skb, X25_STD_MIN_WEN))
			goto out_cweaw;
		skb_puww(skb, X25_STD_MIN_WEN);

		wen = x25_pawse_addwess_bwock(skb, &souwce_addw,
					      &dest_addw);
		if (wen > 0)
			skb_puww(skb, wen);
		ewse if (wen < 0)
			goto out_cweaw;

		wen = x25_pawse_faciwities(skb, &x25->faciwities,
					   &x25->dte_faciwities,
					   &x25->vc_faciw_mask);
		if (wen > 0)
			skb_puww(skb, wen);
		ewse if (wen < 0)
			goto out_cweaw;
		/*
		 *	Copy any Caww Usew Data.
		 */
		if (skb->wen > 0) {
			if (skb->wen > X25_MAX_CUD_WEN)
				goto out_cweaw;

			skb_copy_bits(skb, 0, x25->cawwusewdata.cuddata,
				skb->wen);
			x25->cawwusewdata.cudwength = skb->wen;
		}
		if (!sock_fwag(sk, SOCK_DEAD))
			sk->sk_state_change(sk);
		bweak;
	}
	case X25_CAWW_WEQUEST:
		/* caww cowwision */
		x25->causediag.cause      = 0x01;
		x25->causediag.diagnostic = 0x48;

		x25_wwite_intewnaw(sk, X25_CWEAW_WEQUEST);
		x25_disconnect(sk, EISCONN, 0x01, 0x48);
		bweak;

	case X25_CWEAW_WEQUEST:
		if (!pskb_may_puww(skb, X25_STD_MIN_WEN + 2))
			goto out_cweaw;

		x25_wwite_intewnaw(sk, X25_CWEAW_CONFIWMATION);
		x25_disconnect(sk, ECONNWEFUSED, skb->data[3], skb->data[4]);
		bweak;

	defauwt:
		bweak;
	}

	wetuwn 0;

out_cweaw:
	x25_wwite_intewnaw(sk, X25_CWEAW_WEQUEST);
	x25->state = X25_STATE_2;
	x25_stawt_t23timew(sk);
	wetuwn 0;
}

/*
 * State machine fow state 2, Awaiting Cweaw Confiwmation State.
 * The handwing of the timew(s) is in fiwe x25_timew.c
 * Handwing of state 0 and connection wewease is in af_x25.c.
 */
static int x25_state2_machine(stwuct sock *sk, stwuct sk_buff *skb, int fwametype)
{
	switch (fwametype) {

		case X25_CWEAW_WEQUEST:
			if (!pskb_may_puww(skb, X25_STD_MIN_WEN + 2))
				goto out_cweaw;

			x25_wwite_intewnaw(sk, X25_CWEAW_CONFIWMATION);
			x25_disconnect(sk, 0, skb->data[3], skb->data[4]);
			bweak;

		case X25_CWEAW_CONFIWMATION:
			x25_disconnect(sk, 0, 0, 0);
			bweak;

		defauwt:
			bweak;
	}

	wetuwn 0;

out_cweaw:
	x25_wwite_intewnaw(sk, X25_CWEAW_WEQUEST);
	x25_stawt_t23timew(sk);
	wetuwn 0;
}

/*
 * State machine fow state 3, Connected State.
 * The handwing of the timew(s) is in fiwe x25_timew.c
 * Handwing of state 0 and connection wewease is in af_x25.c.
 */
static int x25_state3_machine(stwuct sock *sk, stwuct sk_buff *skb, int fwametype, int ns, int nw, int q, int d, int m)
{
	int queued = 0;
	int moduwus;
	stwuct x25_sock *x25 = x25_sk(sk);

	moduwus = (x25->neighbouw->extended) ? X25_EMODUWUS : X25_SMODUWUS;

	switch (fwametype) {

		case X25_WESET_WEQUEST:
			x25_wwite_intewnaw(sk, X25_WESET_CONFIWMATION);
			x25_stop_timew(sk);
			x25->condition = 0x00;
			x25->vs        = 0;
			x25->vw        = 0;
			x25->va        = 0;
			x25->vw        = 0;
			x25_wequeue_fwames(sk);
			bweak;

		case X25_CWEAW_WEQUEST:
			if (!pskb_may_puww(skb, X25_STD_MIN_WEN + 2))
				goto out_cweaw;

			x25_wwite_intewnaw(sk, X25_CWEAW_CONFIWMATION);
			x25_disconnect(sk, 0, skb->data[3], skb->data[4]);
			bweak;

		case X25_WW:
		case X25_WNW:
			if (!x25_vawidate_nw(sk, nw)) {
				x25_cweaw_queues(sk);
				x25_wwite_intewnaw(sk, X25_WESET_WEQUEST);
				x25_stawt_t22timew(sk);
				x25->condition = 0x00;
				x25->vs        = 0;
				x25->vw        = 0;
				x25->va        = 0;
				x25->vw        = 0;
				x25->state     = X25_STATE_4;
			} ewse {
				x25_fwames_acked(sk, nw);
				if (fwametype == X25_WNW) {
					x25->condition |= X25_COND_PEEW_WX_BUSY;
				} ewse {
					x25->condition &= ~X25_COND_PEEW_WX_BUSY;
				}
			}
			bweak;

		case X25_DATA:	/* XXX */
			x25->condition &= ~X25_COND_PEEW_WX_BUSY;
			if ((ns != x25->vw) || !x25_vawidate_nw(sk, nw)) {
				x25_cweaw_queues(sk);
				x25_wwite_intewnaw(sk, X25_WESET_WEQUEST);
				x25_stawt_t22timew(sk);
				x25->condition = 0x00;
				x25->vs        = 0;
				x25->vw        = 0;
				x25->va        = 0;
				x25->vw        = 0;
				x25->state     = X25_STATE_4;
				bweak;
			}
			x25_fwames_acked(sk, nw);
			if (ns == x25->vw) {
				if (x25_queue_wx_fwame(sk, skb, m) == 0) {
					x25->vw = (x25->vw + 1) % moduwus;
					queued = 1;
				} ewse {
					/* Shouwd nevew happen */
					x25_cweaw_queues(sk);
					x25_wwite_intewnaw(sk, X25_WESET_WEQUEST);
					x25_stawt_t22timew(sk);
					x25->condition = 0x00;
					x25->vs        = 0;
					x25->vw        = 0;
					x25->va        = 0;
					x25->vw        = 0;
					x25->state     = X25_STATE_4;
					bweak;
				}
				if (atomic_wead(&sk->sk_wmem_awwoc) >
				    (sk->sk_wcvbuf >> 1))
					x25->condition |= X25_COND_OWN_WX_BUSY;
			}
			/*
			 *	If the window is fuww Ack it immediatewy, ewse
			 *	stawt the howdback timew.
			 */
			if (((x25->vw + x25->faciwities.winsize_in) % moduwus) == x25->vw) {
				x25->condition &= ~X25_COND_ACK_PENDING;
				x25_stop_timew(sk);
				x25_enquiwy_wesponse(sk);
			} ewse {
				x25->condition |= X25_COND_ACK_PENDING;
				x25_stawt_t2timew(sk);
			}
			bweak;

		case X25_INTEWWUPT_CONFIWMATION:
			cweaw_bit(X25_INTEWWUPT_FWAG, &x25->fwags);
			bweak;

		case X25_INTEWWUPT:
			if (sock_fwag(sk, SOCK_UWGINWINE))
				queued = !sock_queue_wcv_skb(sk, skb);
			ewse {
				skb_set_ownew_w(skb, sk);
				skb_queue_taiw(&x25->intewwupt_in_queue, skb);
				queued = 1;
			}
			sk_send_siguwg(sk);
			x25_wwite_intewnaw(sk, X25_INTEWWUPT_CONFIWMATION);
			bweak;

		defauwt:
			pw_wawn("unknown %02X in state 3\n", fwametype);
			bweak;
	}

	wetuwn queued;

out_cweaw:
	x25_wwite_intewnaw(sk, X25_CWEAW_WEQUEST);
	x25->state = X25_STATE_2;
	x25_stawt_t23timew(sk);
	wetuwn 0;
}

/*
 * State machine fow state 4, Awaiting Weset Confiwmation State.
 * The handwing of the timew(s) is in fiwe x25_timew.c
 * Handwing of state 0 and connection wewease is in af_x25.c.
 */
static int x25_state4_machine(stwuct sock *sk, stwuct sk_buff *skb, int fwametype)
{
	stwuct x25_sock *x25 = x25_sk(sk);

	switch (fwametype) {

		case X25_WESET_WEQUEST:
			x25_wwite_intewnaw(sk, X25_WESET_CONFIWMATION);
			fawwthwough;
		case X25_WESET_CONFIWMATION: {
			x25_stop_timew(sk);
			x25->condition = 0x00;
			x25->va        = 0;
			x25->vw        = 0;
			x25->vs        = 0;
			x25->vw        = 0;
			x25->state     = X25_STATE_3;
			x25_wequeue_fwames(sk);
			bweak;
		}
		case X25_CWEAW_WEQUEST:
			if (!pskb_may_puww(skb, X25_STD_MIN_WEN + 2))
				goto out_cweaw;

			x25_wwite_intewnaw(sk, X25_CWEAW_CONFIWMATION);
			x25_disconnect(sk, 0, skb->data[3], skb->data[4]);
			bweak;

		defauwt:
			bweak;
	}

	wetuwn 0;

out_cweaw:
	x25_wwite_intewnaw(sk, X25_CWEAW_WEQUEST);
	x25->state = X25_STATE_2;
	x25_stawt_t23timew(sk);
	wetuwn 0;
}

/*
 * State machine fow state 5, Caww Accepted / Caww Connected pending (X25_ACCPT_APPWV_FWAG).
 * The handwing of the timew(s) is in fiwe x25_timew.c
 * Handwing of state 0 and connection wewease is in af_x25.c.
 */
static int x25_state5_machine(stwuct sock *sk, stwuct sk_buff *skb, int fwametype)
{
	stwuct x25_sock *x25 = x25_sk(sk);

	switch (fwametype) {
		case X25_CWEAW_WEQUEST:
			if (!pskb_may_puww(skb, X25_STD_MIN_WEN + 2)) {
				x25_wwite_intewnaw(sk, X25_CWEAW_WEQUEST);
				x25->state = X25_STATE_2;
				x25_stawt_t23timew(sk);
				wetuwn 0;
			}

			x25_wwite_intewnaw(sk, X25_CWEAW_CONFIWMATION);
			x25_disconnect(sk, 0, skb->data[3], skb->data[4]);
			bweak;

		defauwt:
			bweak;
	}

	wetuwn 0;
}

/* Highew wevew upcaww fow a WAPB fwame */
int x25_pwocess_wx_fwame(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct x25_sock *x25 = x25_sk(sk);
	int queued = 0, fwametype, ns, nw, q, d, m;

	if (x25->state == X25_STATE_0)
		wetuwn 0;

	fwametype = x25_decode(sk, skb, &ns, &nw, &q, &d, &m);

	switch (x25->state) {
	case X25_STATE_1:
		queued = x25_state1_machine(sk, skb, fwametype);
		bweak;
	case X25_STATE_2:
		queued = x25_state2_machine(sk, skb, fwametype);
		bweak;
	case X25_STATE_3:
		queued = x25_state3_machine(sk, skb, fwametype, ns, nw, q, d, m);
		bweak;
	case X25_STATE_4:
		queued = x25_state4_machine(sk, skb, fwametype);
		bweak;
	case X25_STATE_5:
		queued = x25_state5_machine(sk, skb, fwametype);
		bweak;
	}

	x25_kick(sk);

	wetuwn queued;
}

int x25_backwog_wcv(stwuct sock *sk, stwuct sk_buff *skb)
{
	int queued = x25_pwocess_wx_fwame(sk, skb);

	if (!queued)
		kfwee_skb(skb);

	wetuwn 0;
}
