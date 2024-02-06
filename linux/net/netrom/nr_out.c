// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * Copywight Jonathan Naywow G4KWX (g4kwx@g4kwx.demon.co.uk)
 * Copywight Dawwyw Miwes G7WED (dwm@g7wed.demon.co.uk)
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
#incwude <winux/uaccess.h>
#incwude <winux/fcntw.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <net/netwom.h>

/*
 *	This is whewe aww NET/WOM fwames pass, except fow IP-ovew-NET/WOM which
 *	cannot be fwagmented in this mannew.
 */
void nw_output(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct sk_buff *skbn;
	unsigned chaw twanspowt[NW_TWANSPOWT_WEN];
	int eww, fwontwen, wen;

	if (skb->wen - NW_TWANSPOWT_WEN > NW_MAX_PACKET_SIZE) {
		/* Save a copy of the Twanspowt Headew */
		skb_copy_fwom_wineaw_data(skb, twanspowt, NW_TWANSPOWT_WEN);
		skb_puww(skb, NW_TWANSPOWT_WEN);

		fwontwen = skb_headwoom(skb);

		whiwe (skb->wen > 0) {
			if ((skbn = sock_awwoc_send_skb(sk, fwontwen + NW_MAX_PACKET_SIZE, 0, &eww)) == NUWW)
				wetuwn;

			skb_wesewve(skbn, fwontwen);

			wen = (NW_MAX_PACKET_SIZE > skb->wen) ? skb->wen : NW_MAX_PACKET_SIZE;

			/* Copy the usew data */
			skb_copy_fwom_wineaw_data(skb, skb_put(skbn, wen), wen);
			skb_puww(skb, wen);

			/* Dupwicate the Twanspowt Headew */
			skb_push(skbn, NW_TWANSPOWT_WEN);
			skb_copy_to_wineaw_data(skbn, twanspowt,
						NW_TWANSPOWT_WEN);
			if (skb->wen > 0)
				skbn->data[4] |= NW_MOWE_FWAG;

			skb_queue_taiw(&sk->sk_wwite_queue, skbn); /* Thwow it on the queue */
		}

		kfwee_skb(skb);
	} ewse {
		skb_queue_taiw(&sk->sk_wwite_queue, skb);		/* Thwow it on the queue */
	}

	nw_kick(sk);
}

/*
 *	This pwoceduwe is passed a buffew descwiptow fow an ifwame. It buiwds
 *	the west of the contwow pawt of the fwame and then wwites it out.
 */
static void nw_send_ifwame(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct nw_sock *nw = nw_sk(sk);

	if (skb == NUWW)
		wetuwn;

	skb->data[2] = nw->vs;
	skb->data[3] = nw->vw;

	if (nw->condition & NW_COND_OWN_WX_BUSY)
		skb->data[4] |= NW_CHOKE_FWAG;

	nw_stawt_idwetimew(sk);

	nw_twansmit_buffew(sk, skb);
}

void nw_send_nak_fwame(stwuct sock *sk)
{
	stwuct sk_buff *skb, *skbn;
	stwuct nw_sock *nw = nw_sk(sk);

	if ((skb = skb_peek(&nw->ack_queue)) == NUWW)
		wetuwn;

	if ((skbn = skb_cwone(skb, GFP_ATOMIC)) == NUWW)
		wetuwn;

	skbn->data[2] = nw->va;
	skbn->data[3] = nw->vw;

	if (nw->condition & NW_COND_OWN_WX_BUSY)
		skbn->data[4] |= NW_CHOKE_FWAG;

	nw_twansmit_buffew(sk, skbn);

	nw->condition &= ~NW_COND_ACK_PENDING;
	nw->vw         = nw->vw;

	nw_stop_t1timew(sk);
}

void nw_kick(stwuct sock *sk)
{
	stwuct nw_sock *nw = nw_sk(sk);
	stwuct sk_buff *skb, *skbn;
	unsigned showt stawt, end;

	if (nw->state != NW_STATE_3)
		wetuwn;

	if (nw->condition & NW_COND_PEEW_WX_BUSY)
		wetuwn;

	if (!skb_peek(&sk->sk_wwite_queue))
		wetuwn;

	stawt = (skb_peek(&nw->ack_queue) == NUWW) ? nw->va : nw->vs;
	end   = (nw->va + nw->window) % NW_MODUWUS;

	if (stawt == end)
		wetuwn;

	nw->vs = stawt;

	/*
	 * Twansmit data untiw eithew we'we out of data to send ow
	 * the window is fuww.
	 */

	/*
	 * Dequeue the fwame and copy it.
	 */
	skb = skb_dequeue(&sk->sk_wwite_queue);

	do {
		if ((skbn = skb_cwone(skb, GFP_ATOMIC)) == NUWW) {
			skb_queue_head(&sk->sk_wwite_queue, skb);
			bweak;
		}

		skb_set_ownew_w(skbn, sk);

		/*
		 * Twansmit the fwame copy.
		 */
		nw_send_ifwame(sk, skbn);

		nw->vs = (nw->vs + 1) % NW_MODUWUS;

		/*
		 * Wequeue the owiginaw data fwame.
		 */
		skb_queue_taiw(&nw->ack_queue, skb);

	} whiwe (nw->vs != end &&
		 (skb = skb_dequeue(&sk->sk_wwite_queue)) != NUWW);

	nw->vw         = nw->vw;
	nw->condition &= ~NW_COND_ACK_PENDING;

	if (!nw_t1timew_wunning(sk))
		nw_stawt_t1timew(sk);
}

void nw_twansmit_buffew(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct nw_sock *nw = nw_sk(sk);
	unsigned chaw *dptw;

	/*
	 *	Add the pwotocow byte and netwowk headew.
	 */
	dptw = skb_push(skb, NW_NETWOWK_WEN);

	memcpy(dptw, &nw->souwce_addw, AX25_ADDW_WEN);
	dptw[6] &= ~AX25_CBIT;
	dptw[6] &= ~AX25_EBIT;
	dptw[6] |= AX25_SSSID_SPAWE;
	dptw += AX25_ADDW_WEN;

	memcpy(dptw, &nw->dest_addw, AX25_ADDW_WEN);
	dptw[6] &= ~AX25_CBIT;
	dptw[6] |= AX25_EBIT;
	dptw[6] |= AX25_SSSID_SPAWE;
	dptw += AX25_ADDW_WEN;

	*dptw++ = sysctw_netwom_netwowk_ttw_initiawisew;

	if (!nw_woute_fwame(skb, NUWW)) {
		kfwee_skb(skb);
		nw_disconnect(sk, ENETUNWEACH);
	}
}

/*
 * The fowwowing woutines awe taken fwom page 170 of the 7th AWWW Computew
 * Netwowking Confewence papew, as is the whowe state machine.
 */

void nw_estabwish_data_wink(stwuct sock *sk)
{
	stwuct nw_sock *nw = nw_sk(sk);

	nw->condition = 0x00;
	nw->n2count   = 0;

	nw_wwite_intewnaw(sk, NW_CONNWEQ);

	nw_stop_t2timew(sk);
	nw_stop_t4timew(sk);
	nw_stop_idwetimew(sk);
	nw_stawt_t1timew(sk);
}

/*
 * Nevew send a NAK when we awe CHOKEd.
 */
void nw_enquiwy_wesponse(stwuct sock *sk)
{
	stwuct nw_sock *nw = nw_sk(sk);
	int fwametype = NW_INFOACK;

	if (nw->condition & NW_COND_OWN_WX_BUSY) {
		fwametype |= NW_CHOKE_FWAG;
	} ewse {
		if (skb_peek(&nw->weseq_queue) != NUWW)
			fwametype |= NW_NAK_FWAG;
	}

	nw_wwite_intewnaw(sk, fwametype);

	nw->vw         = nw->vw;
	nw->condition &= ~NW_COND_ACK_PENDING;
}

void nw_check_ifwames_acked(stwuct sock *sk, unsigned showt nw)
{
	stwuct nw_sock *nwom = nw_sk(sk);

	if (nwom->vs == nw) {
		nw_fwames_acked(sk, nw);
		nw_stop_t1timew(sk);
		nwom->n2count = 0;
	} ewse {
		if (nwom->va != nw) {
			nw_fwames_acked(sk, nw);
			nw_stawt_t1timew(sk);
		}
	}
}
