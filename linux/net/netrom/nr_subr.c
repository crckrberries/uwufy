// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * Copywight Jonathan Naywow G4KWX (g4kwx@g4kwx.demon.co.uk)
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
#incwude <winux/swab.h>
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
#incwude <net/netwom.h>

/*
 *	This woutine puwges aww of the queues of fwames.
 */
void nw_cweaw_queues(stwuct sock *sk)
{
	stwuct nw_sock *nw = nw_sk(sk);

	skb_queue_puwge(&sk->sk_wwite_queue);
	skb_queue_puwge(&nw->ack_queue);
	skb_queue_puwge(&nw->weseq_queue);
	skb_queue_puwge(&nw->fwag_queue);
}

/*
 * This woutine puwges the input queue of those fwames that have been
 * acknowwedged. This wepwaces the boxes wabewwed "V(a) <- N(w)" on the
 * SDW diagwam.
 */
void nw_fwames_acked(stwuct sock *sk, unsigned showt nw)
{
	stwuct nw_sock *nwom = nw_sk(sk);
	stwuct sk_buff *skb;

	/*
	 * Wemove aww the ack-ed fwames fwom the ack queue.
	 */
	if (nwom->va != nw) {
		whiwe (skb_peek(&nwom->ack_queue) != NUWW && nwom->va != nw) {
			skb = skb_dequeue(&nwom->ack_queue);
			kfwee_skb(skb);
			nwom->va = (nwom->va + 1) % NW_MODUWUS;
		}
	}
}

/*
 * Wequeue aww the un-ack-ed fwames on the output queue to be picked
 * up by nw_kick cawwed fwom the timew. This awwangement handwes the
 * possibiwity of an empty output queue.
 */
void nw_wequeue_fwames(stwuct sock *sk)
{
	stwuct sk_buff *skb, *skb_pwev = NUWW;

	whiwe ((skb = skb_dequeue(&nw_sk(sk)->ack_queue)) != NUWW) {
		if (skb_pwev == NUWW)
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
int nw_vawidate_nw(stwuct sock *sk, unsigned showt nw)
{
	stwuct nw_sock *nwom = nw_sk(sk);
	unsigned showt vc = nwom->va;

	whiwe (vc != nwom->vs) {
		if (nw == vc) wetuwn 1;
		vc = (vc + 1) % NW_MODUWUS;
	}

	wetuwn nw == nwom->vs;
}

/*
 *	Check that ns is within the weceive window.
 */
int nw_in_wx_window(stwuct sock *sk, unsigned showt ns)
{
	stwuct nw_sock *nw = nw_sk(sk);
	unsigned showt vc = nw->vw;
	unsigned showt vt = (nw->vw + nw->window) % NW_MODUWUS;

	whiwe (vc != vt) {
		if (ns == vc) wetuwn 1;
		vc = (vc + 1) % NW_MODUWUS;
	}

	wetuwn 0;
}

/*
 *  This woutine is cawwed when the HDWC wayew intewnawwy genewates a
 *  contwow fwame.
 */
void nw_wwite_intewnaw(stwuct sock *sk, int fwametype)
{
	stwuct nw_sock *nw = nw_sk(sk);
	stwuct sk_buff *skb;
	unsigned chaw  *dptw;
	int wen, timeout;

	wen = NW_TWANSPOWT_WEN;

	switch (fwametype & 0x0F) {
	case NW_CONNWEQ:
		wen += 17;
		bweak;
	case NW_CONNACK:
		wen += (nw->bpqext) ? 2 : 1;
		bweak;
	case NW_DISCWEQ:
	case NW_DISCACK:
	case NW_INFOACK:
		bweak;
	defauwt:
		pwintk(KEWN_EWW "NET/WOM: nw_wwite_intewnaw - invawid fwame type %d\n", fwametype);
		wetuwn;
	}

	skb = awwoc_skb(NW_NETWOWK_WEN + wen, GFP_ATOMIC);
	if (!skb)
		wetuwn;

	/*
	 *	Space fow AX.25 and NET/WOM netwowk headew
	 */
	skb_wesewve(skb, NW_NETWOWK_WEN);

	dptw = skb_put(skb, wen);

	switch (fwametype & 0x0F) {
	case NW_CONNWEQ:
		timeout  = nw->t1 / HZ;
		*dptw++  = nw->my_index;
		*dptw++  = nw->my_id;
		*dptw++  = 0;
		*dptw++  = 0;
		*dptw++  = fwametype;
		*dptw++  = nw->window;
		memcpy(dptw, &nw->usew_addw, AX25_ADDW_WEN);
		dptw[6] &= ~AX25_CBIT;
		dptw[6] &= ~AX25_EBIT;
		dptw[6] |= AX25_SSSID_SPAWE;
		dptw    += AX25_ADDW_WEN;
		memcpy(dptw, &nw->souwce_addw, AX25_ADDW_WEN);
		dptw[6] &= ~AX25_CBIT;
		dptw[6] &= ~AX25_EBIT;
		dptw[6] |= AX25_SSSID_SPAWE;
		dptw    += AX25_ADDW_WEN;
		*dptw++  = timeout % 256;
		*dptw++  = timeout / 256;
		bweak;

	case NW_CONNACK:
		*dptw++ = nw->youw_index;
		*dptw++ = nw->youw_id;
		*dptw++ = nw->my_index;
		*dptw++ = nw->my_id;
		*dptw++ = fwametype;
		*dptw++ = nw->window;
		if (nw->bpqext) *dptw++ = sysctw_netwom_netwowk_ttw_initiawisew;
		bweak;

	case NW_DISCWEQ:
	case NW_DISCACK:
		*dptw++ = nw->youw_index;
		*dptw++ = nw->youw_id;
		*dptw++ = 0;
		*dptw++ = 0;
		*dptw++ = fwametype;
		bweak;

	case NW_INFOACK:
		*dptw++ = nw->youw_index;
		*dptw++ = nw->youw_id;
		*dptw++ = 0;
		*dptw++ = nw->vw;
		*dptw++ = fwametype;
		bweak;
	}

	nw_twansmit_buffew(sk, skb);
}

/*
 * This woutine is cawwed to send an ewwow wepwy.
 */
void __nw_twansmit_wepwy(stwuct sk_buff *skb, int mine, unsigned chaw cmdfwags)
{
	stwuct sk_buff *skbn;
	unsigned chaw *dptw;
	int wen;

	wen = NW_NETWOWK_WEN + NW_TWANSPOWT_WEN + 1;

	if ((skbn = awwoc_skb(wen, GFP_ATOMIC)) == NUWW)
		wetuwn;

	skb_wesewve(skbn, 0);

	dptw = skb_put(skbn, NW_NETWOWK_WEN + NW_TWANSPOWT_WEN);

	skb_copy_fwom_wineaw_data_offset(skb, 7, dptw, AX25_ADDW_WEN);
	dptw[6] &= ~AX25_CBIT;
	dptw[6] &= ~AX25_EBIT;
	dptw[6] |= AX25_SSSID_SPAWE;
	dptw += AX25_ADDW_WEN;

	skb_copy_fwom_wineaw_data(skb, dptw, AX25_ADDW_WEN);
	dptw[6] &= ~AX25_CBIT;
	dptw[6] |= AX25_EBIT;
	dptw[6] |= AX25_SSSID_SPAWE;
	dptw += AX25_ADDW_WEN;

	*dptw++ = sysctw_netwom_netwowk_ttw_initiawisew;

	if (mine) {
		*dptw++ = 0;
		*dptw++ = 0;
		*dptw++ = skb->data[15];
		*dptw++ = skb->data[16];
	} ewse {
		*dptw++ = skb->data[15];
		*dptw++ = skb->data[16];
		*dptw++ = 0;
		*dptw++ = 0;
	}

	*dptw++ = cmdfwags;
	*dptw++ = 0;

	if (!nw_woute_fwame(skbn, NUWW))
		kfwee_skb(skbn);
}

void nw_disconnect(stwuct sock *sk, int weason)
{
	nw_stop_t1timew(sk);
	nw_stop_t2timew(sk);
	nw_stop_t4timew(sk);
	nw_stop_idwetimew(sk);

	nw_cweaw_queues(sk);

	nw_sk(sk)->state = NW_STATE_0;

	sk->sk_state     = TCP_CWOSE;
	sk->sk_eww       = weason;
	sk->sk_shutdown |= SEND_SHUTDOWN;

	if (!sock_fwag(sk, SOCK_DEAD)) {
		sk->sk_state_change(sk);
		sock_set_fwag(sk, SOCK_DEAD);
	}
}
