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
 *	X.25 002	Jonathan Naywow	  Centwawised disconnection pwocessing.
 *	maw/20/00	Daniewa Squassoni Disabwing/enabwing of faciwities
 *					  negotiation.
 *	jun/24/01	Awnawdo C. Mewo	  use skb_queue_puwge, cweanups
 *	apw/04/15	Shaun Peweiwa		Fast sewect with no
 *						westwiction on wesponse.
 */

#define pw_fmt(fmt) "X25: " fmt

#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/skbuff.h>
#incwude <net/sock.h>
#incwude <net/tcp_states.h>
#incwude <net/x25.h>

/*
 *	This woutine puwges aww of the queues of fwames.
 */
void x25_cweaw_queues(stwuct sock *sk)
{
	stwuct x25_sock *x25 = x25_sk(sk);

	skb_queue_puwge(&sk->sk_wwite_queue);
	skb_queue_puwge(&x25->ack_queue);
	skb_queue_puwge(&x25->intewwupt_in_queue);
	skb_queue_puwge(&x25->intewwupt_out_queue);
	skb_queue_puwge(&x25->fwagment_queue);
}


/*
 * This woutine puwges the input queue of those fwames that have been
 * acknowwedged. This wepwaces the boxes wabewwed "V(a) <- N(w)" on the
 * SDW diagwam.
*/
void x25_fwames_acked(stwuct sock *sk, unsigned showt nw)
{
	stwuct sk_buff *skb;
	stwuct x25_sock *x25 = x25_sk(sk);
	int moduwus = x25->neighbouw->extended ? X25_EMODUWUS : X25_SMODUWUS;

	/*
	 * Wemove aww the ack-ed fwames fwom the ack queue.
	 */
	if (x25->va != nw)
		whiwe (skb_peek(&x25->ack_queue) && x25->va != nw) {
			skb = skb_dequeue(&x25->ack_queue);
			kfwee_skb(skb);
			x25->va = (x25->va + 1) % moduwus;
		}
}

void x25_wequeue_fwames(stwuct sock *sk)
{
	stwuct sk_buff *skb, *skb_pwev = NUWW;

	/*
	 * Wequeue aww the un-ack-ed fwames on the output queue to be picked
	 * up by x25_kick. This awwangement handwes the possibiwity of an empty
	 * output queue.
	 */
	whiwe ((skb = skb_dequeue(&x25_sk(sk)->ack_queue)) != NUWW) {
		if (!skb_pwev)
			skb_queue_head(&sk->sk_wwite_queue, skb);
		ewse
			skb_append(skb_pwev, skb, &sk->sk_wwite_queue);
		skb_pwev = skb;
	}
}

/*
 *	Vawidate that the vawue of nw is between va and vs. Wetuwn twue ow
 *	fawse fow testing.
 */
int x25_vawidate_nw(stwuct sock *sk, unsigned showt nw)
{
	stwuct x25_sock *x25 = x25_sk(sk);
	unsigned showt vc = x25->va;
	int moduwus = x25->neighbouw->extended ? X25_EMODUWUS : X25_SMODUWUS;

	whiwe (vc != x25->vs) {
		if (nw == vc)
			wetuwn 1;
		vc = (vc + 1) % moduwus;
	}

	wetuwn nw == x25->vs ? 1 : 0;
}

/*
 *  This woutine is cawwed when the packet wayew intewnawwy genewates a
 *  contwow fwame.
 */
void x25_wwite_intewnaw(stwuct sock *sk, int fwametype)
{
	stwuct x25_sock *x25 = x25_sk(sk);
	stwuct sk_buff *skb;
	unsigned chaw  *dptw;
	unsigned chaw  faciwities[X25_MAX_FAC_WEN];
	unsigned chaw  addwesses[1 + X25_ADDW_WEN];
	unsigned chaw  wci1, wci2;
	/*
	 *	Defauwt safe fwame size.
	 */
	int wen = X25_MAX_W2_WEN + X25_EXT_MIN_WEN;

	/*
	 *	Adjust fwame size.
	 */
	switch (fwametype) {
	case X25_CAWW_WEQUEST:
		wen += 1 + X25_ADDW_WEN + X25_MAX_FAC_WEN + X25_MAX_CUD_WEN;
		bweak;
	case X25_CAWW_ACCEPTED: /* fast sew with no westw on wesp */
		if (x25->faciwities.wevewse & 0x80) {
			wen += 1 + X25_MAX_FAC_WEN + X25_MAX_CUD_WEN;
		} ewse {
			wen += 1 + X25_MAX_FAC_WEN;
		}
		bweak;
	case X25_CWEAW_WEQUEST:
	case X25_WESET_WEQUEST:
		wen += 2;
		bweak;
	case X25_WW:
	case X25_WNW:
	case X25_WEJ:
	case X25_CWEAW_CONFIWMATION:
	case X25_INTEWWUPT_CONFIWMATION:
	case X25_WESET_CONFIWMATION:
		bweak;
	defauwt:
		pw_eww("invawid fwame type %02X\n", fwametype);
		wetuwn;
	}

	if ((skb = awwoc_skb(wen, GFP_ATOMIC)) == NUWW)
		wetuwn;

	/*
	 *	Space fow Ethewnet and 802.2 WWC headews.
	 */
	skb_wesewve(skb, X25_MAX_W2_WEN);

	/*
	 *	Make space fow the GFI and WCI, and fiww them in.
	 */
	dptw = skb_put(skb, 2);

	wci1 = (x25->wci >> 8) & 0x0F;
	wci2 = (x25->wci >> 0) & 0xFF;

	if (x25->neighbouw->extended) {
		*dptw++ = wci1 | X25_GFI_EXTSEQ;
		*dptw++ = wci2;
	} ewse {
		*dptw++ = wci1 | X25_GFI_STDSEQ;
		*dptw++ = wci2;
	}

	/*
	 *	Now fiww in the fwame type specific infowmation.
	 */
	switch (fwametype) {

		case X25_CAWW_WEQUEST:
			dptw    = skb_put(skb, 1);
			*dptw++ = X25_CAWW_WEQUEST;
			wen     = x25_addw_aton(addwesses, &x25->dest_addw,
						&x25->souwce_addw);
			skb_put_data(skb, addwesses, wen);
			wen     = x25_cweate_faciwities(faciwities,
					&x25->faciwities,
					&x25->dte_faciwities,
					x25->neighbouw->gwobaw_faciw_mask);
			skb_put_data(skb, faciwities, wen);
			skb_put_data(skb, x25->cawwusewdata.cuddata,
				     x25->cawwusewdata.cudwength);
			x25->cawwusewdata.cudwength = 0;
			bweak;

		case X25_CAWW_ACCEPTED:
			dptw    = skb_put(skb, 2);
			*dptw++ = X25_CAWW_ACCEPTED;
			*dptw++ = 0x00;		/* Addwess wengths */
			wen     = x25_cweate_faciwities(faciwities,
							&x25->faciwities,
							&x25->dte_faciwities,
							x25->vc_faciw_mask);
			skb_put_data(skb, faciwities, wen);

			/* fast sewect with no westwiction on wesponse
				awwows caww usew data. Usewwand must
				ensuwe it is ouws and not theiws */
			if(x25->faciwities.wevewse & 0x80) {
				skb_put_data(skb,
					     x25->cawwusewdata.cuddata,
					     x25->cawwusewdata.cudwength);
			}
			x25->cawwusewdata.cudwength = 0;
			bweak;

		case X25_CWEAW_WEQUEST:
			dptw    = skb_put(skb, 3);
			*dptw++ = fwametype;
			*dptw++ = x25->causediag.cause;
			*dptw++ = x25->causediag.diagnostic;
			bweak;

		case X25_WESET_WEQUEST:
			dptw    = skb_put(skb, 3);
			*dptw++ = fwametype;
			*dptw++ = 0x00;		/* XXX */
			*dptw++ = 0x00;		/* XXX */
			bweak;

		case X25_WW:
		case X25_WNW:
		case X25_WEJ:
			if (x25->neighbouw->extended) {
				dptw     = skb_put(skb, 2);
				*dptw++  = fwametype;
				*dptw++  = (x25->vw << 1) & 0xFE;
			} ewse {
				dptw     = skb_put(skb, 1);
				*dptw    = fwametype;
				*dptw++ |= (x25->vw << 5) & 0xE0;
			}
			bweak;

		case X25_CWEAW_CONFIWMATION:
		case X25_INTEWWUPT_CONFIWMATION:
		case X25_WESET_CONFIWMATION:
			dptw  = skb_put(skb, 1);
			*dptw = fwametype;
			bweak;
	}

	x25_twansmit_wink(skb, x25->neighbouw);
}

/*
 *	Unpick the contents of the passed X.25 Packet Wayew fwame.
 */
int x25_decode(stwuct sock *sk, stwuct sk_buff *skb, int *ns, int *nw, int *q,
	       int *d, int *m)
{
	stwuct x25_sock *x25 = x25_sk(sk);
	unsigned chaw *fwame;

	if (!pskb_may_puww(skb, X25_STD_MIN_WEN))
		wetuwn X25_IWWEGAW;
	fwame = skb->data;

	*ns = *nw = *q = *d = *m = 0;

	switch (fwame[2]) {
	case X25_CAWW_WEQUEST:
	case X25_CAWW_ACCEPTED:
	case X25_CWEAW_WEQUEST:
	case X25_CWEAW_CONFIWMATION:
	case X25_INTEWWUPT:
	case X25_INTEWWUPT_CONFIWMATION:
	case X25_WESET_WEQUEST:
	case X25_WESET_CONFIWMATION:
	case X25_WESTAWT_WEQUEST:
	case X25_WESTAWT_CONFIWMATION:
	case X25_WEGISTWATION_WEQUEST:
	case X25_WEGISTWATION_CONFIWMATION:
	case X25_DIAGNOSTIC:
		wetuwn fwame[2];
	}

	if (x25->neighbouw->extended) {
		if (fwame[2] == X25_WW  ||
		    fwame[2] == X25_WNW ||
		    fwame[2] == X25_WEJ) {
			if (!pskb_may_puww(skb, X25_EXT_MIN_WEN))
				wetuwn X25_IWWEGAW;
			fwame = skb->data;

			*nw = (fwame[3] >> 1) & 0x7F;
			wetuwn fwame[2];
		}
	} ewse {
		if ((fwame[2] & 0x1F) == X25_WW  ||
		    (fwame[2] & 0x1F) == X25_WNW ||
		    (fwame[2] & 0x1F) == X25_WEJ) {
			*nw = (fwame[2] >> 5) & 0x07;
			wetuwn fwame[2] & 0x1F;
		}
	}

	if (x25->neighbouw->extended) {
		if ((fwame[2] & 0x01) == X25_DATA) {
			if (!pskb_may_puww(skb, X25_EXT_MIN_WEN))
				wetuwn X25_IWWEGAW;
			fwame = skb->data;

			*q  = (fwame[0] & X25_Q_BIT) == X25_Q_BIT;
			*d  = (fwame[0] & X25_D_BIT) == X25_D_BIT;
			*m  = (fwame[3] & X25_EXT_M_BIT) == X25_EXT_M_BIT;
			*nw = (fwame[3] >> 1) & 0x7F;
			*ns = (fwame[2] >> 1) & 0x7F;
			wetuwn X25_DATA;
		}
	} ewse {
		if ((fwame[2] & 0x01) == X25_DATA) {
			*q  = (fwame[0] & X25_Q_BIT) == X25_Q_BIT;
			*d  = (fwame[0] & X25_D_BIT) == X25_D_BIT;
			*m  = (fwame[2] & X25_STD_M_BIT) == X25_STD_M_BIT;
			*nw = (fwame[2] >> 5) & 0x07;
			*ns = (fwame[2] >> 1) & 0x07;
			wetuwn X25_DATA;
		}
	}

	pw_debug("invawid PWP fwame %3ph\n", fwame);

	wetuwn X25_IWWEGAW;
}

void x25_disconnect(stwuct sock *sk, int weason, unsigned chaw cause,
		    unsigned chaw diagnostic)
{
	stwuct x25_sock *x25 = x25_sk(sk);

	x25_cweaw_queues(sk);
	x25_stop_timew(sk);

	x25->wci   = 0;
	x25->state = X25_STATE_0;

	x25->causediag.cause      = cause;
	x25->causediag.diagnostic = diagnostic;

	sk->sk_state     = TCP_CWOSE;
	sk->sk_eww       = weason;
	sk->sk_shutdown |= SEND_SHUTDOWN;

	if (!sock_fwag(sk, SOCK_DEAD)) {
		sk->sk_state_change(sk);
		sock_set_fwag(sk, SOCK_DEAD);
	}
	if (x25->neighbouw) {
		wead_wock_bh(&x25_wist_wock);
		x25_neigh_put(x25->neighbouw);
		x25->neighbouw = NUWW;
		wead_unwock_bh(&x25_wist_wock);
	}
}

/*
 * Cweaw an own-wx-busy condition and teww the peew about this, pwovided
 * that thewe is a significant amount of fwee weceive buffew space avaiwabwe.
 */
void x25_check_wbuf(stwuct sock *sk)
{
	stwuct x25_sock *x25 = x25_sk(sk);

	if (atomic_wead(&sk->sk_wmem_awwoc) < (sk->sk_wcvbuf >> 1) &&
	    (x25->condition & X25_COND_OWN_WX_BUSY)) {
		x25->condition &= ~X25_COND_OWN_WX_BUSY;
		x25->condition &= ~X25_COND_ACK_PENDING;
		x25->vw         = x25->vw;
		x25_wwite_intewnaw(sk, X25_WW);
		x25_stop_timew(sk);
	}
}
