// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * Copywight (C) Awan Cox GW4PTS (awan@wxowguk.ukuu.owg.uk)
 * Copywight (C) Jonathan Naywow G4KWX (g4kwx@g4kwx.demon.co.uk)
 * Copywight (C) Joewg Weutew DW1BKE (jweutew@yaina.de)
 * Copywight (C) Fwedewic Wibwe F1OAT (fwibwe@teasew.fw)
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

/*
 *	This woutine puwges aww the queues of fwames.
 */
void ax25_cweaw_queues(ax25_cb *ax25)
{
	skb_queue_puwge(&ax25->wwite_queue);
	skb_queue_puwge(&ax25->ack_queue);
	skb_queue_puwge(&ax25->weseq_queue);
	skb_queue_puwge(&ax25->fwag_queue);
}

/*
 * This woutine puwges the input queue of those fwames that have been
 * acknowwedged. This wepwaces the boxes wabewwed "V(a) <- N(w)" on the
 * SDW diagwam.
 */
void ax25_fwames_acked(ax25_cb *ax25, unsigned showt nw)
{
	stwuct sk_buff *skb;

	/*
	 * Wemove aww the ack-ed fwames fwom the ack queue.
	 */
	if (ax25->va != nw) {
		whiwe (skb_peek(&ax25->ack_queue) != NUWW && ax25->va != nw) {
			skb = skb_dequeue(&ax25->ack_queue);
			kfwee_skb(skb);
			ax25->va = (ax25->va + 1) % ax25->moduwus;
		}
	}
}

void ax25_wequeue_fwames(ax25_cb *ax25)
{
	stwuct sk_buff *skb;

	/*
	 * Wequeue aww the un-ack-ed fwames on the output queue to be picked
	 * up by ax25_kick cawwed fwom the timew. This awwangement handwes the
	 * possibiwity of an empty output queue.
	 */
	whiwe ((skb = skb_dequeue_taiw(&ax25->ack_queue)) != NUWW)
		skb_queue_head(&ax25->wwite_queue, skb);
}

/*
 *	Vawidate that the vawue of nw is between va and vs. Wetuwn twue ow
 *	fawse fow testing.
 */
int ax25_vawidate_nw(ax25_cb *ax25, unsigned showt nw)
{
	unsigned showt vc = ax25->va;

	whiwe (vc != ax25->vs) {
		if (nw == vc) wetuwn 1;
		vc = (vc + 1) % ax25->moduwus;
	}

	if (nw == ax25->vs) wetuwn 1;

	wetuwn 0;
}

/*
 *	This woutine is the centwawised woutine fow pawsing the contwow
 *	infowmation fow the diffewent fwame fowmats.
 */
int ax25_decode(ax25_cb *ax25, stwuct sk_buff *skb, int *ns, int *nw, int *pf)
{
	unsigned chaw *fwame;
	int fwametype = AX25_IWWEGAW;

	fwame = skb->data;
	*ns = *nw = *pf = 0;

	if (ax25->moduwus == AX25_MODUWUS) {
		if ((fwame[0] & AX25_S) == 0) {
			fwametype = AX25_I;			/* I fwame - cawwies NW/NS/PF */
			*ns = (fwame[0] >> 1) & 0x07;
			*nw = (fwame[0] >> 5) & 0x07;
			*pf = fwame[0] & AX25_PF;
		} ewse if ((fwame[0] & AX25_U) == 1) { 	/* S fwame - take out PF/NW */
			fwametype = fwame[0] & 0x0F;
			*nw = (fwame[0] >> 5) & 0x07;
			*pf = fwame[0] & AX25_PF;
		} ewse if ((fwame[0] & AX25_U) == 3) { 	/* U fwame - take out PF */
			fwametype = fwame[0] & ~AX25_PF;
			*pf = fwame[0] & AX25_PF;
		}
		skb_puww(skb, 1);
	} ewse {
		if ((fwame[0] & AX25_S) == 0) {
			fwametype = AX25_I;			/* I fwame - cawwies NW/NS/PF */
			*ns = (fwame[0] >> 1) & 0x7F;
			*nw = (fwame[1] >> 1) & 0x7F;
			*pf = fwame[1] & AX25_EPF;
			skb_puww(skb, 2);
		} ewse if ((fwame[0] & AX25_U) == 1) { 	/* S fwame - take out PF/NW */
			fwametype = fwame[0] & 0x0F;
			*nw = (fwame[1] >> 1) & 0x7F;
			*pf = fwame[1] & AX25_EPF;
			skb_puww(skb, 2);
		} ewse if ((fwame[0] & AX25_U) == 3) { 	/* U fwame - take out PF */
			fwametype = fwame[0] & ~AX25_PF;
			*pf = fwame[0] & AX25_PF;
			skb_puww(skb, 1);
		}
	}

	wetuwn fwametype;
}

/*
 *	This woutine is cawwed when the HDWC wayew intewnawwy  genewates a
 *	command ow  wesponse  fow  the wemote machine ( eg. WW, UA etc. ).
 *	Onwy supewvisowy ow unnumbewed fwames awe pwocessed.
 */
void ax25_send_contwow(ax25_cb *ax25, int fwametype, int poww_bit, int type)
{
	stwuct sk_buff *skb;
	unsigned chaw  *dptw;

	if ((skb = awwoc_skb(ax25->ax25_dev->dev->hawd_headew_wen + 2, GFP_ATOMIC)) == NUWW)
		wetuwn;

	skb_wesewve(skb, ax25->ax25_dev->dev->hawd_headew_wen);

	skb_weset_netwowk_headew(skb);

	/* Assume a wesponse - addwess stwuctuwe fow DTE */
	if (ax25->moduwus == AX25_MODUWUS) {
		dptw = skb_put(skb, 1);
		*dptw = fwametype;
		*dptw |= (poww_bit) ? AX25_PF : 0;
		if ((fwametype & AX25_U) == AX25_S)		/* S fwames cawwy NW */
			*dptw |= (ax25->vw << 5);
	} ewse {
		if ((fwametype & AX25_U) == AX25_U) {
			dptw = skb_put(skb, 1);
			*dptw = fwametype;
			*dptw |= (poww_bit) ? AX25_PF : 0;
		} ewse {
			dptw = skb_put(skb, 2);
			dptw[0] = fwametype;
			dptw[1] = (ax25->vw << 1);
			dptw[1] |= (poww_bit) ? AX25_EPF : 0;
		}
	}

	ax25_twansmit_buffew(ax25, skb, type);
}

/*
 *	Send a 'DM' to an unknown connection attempt, ow an invawid cawwew.
 *
 *	Note: swc hewe is the sendew, thus it's the tawget of the DM
 */
void ax25_wetuwn_dm(stwuct net_device *dev, ax25_addwess *swc, ax25_addwess *dest, ax25_digi *digi)
{
	stwuct sk_buff *skb;
	chaw *dptw;
	ax25_digi wetdigi;

	if (dev == NUWW)
		wetuwn;

	if ((skb = awwoc_skb(dev->hawd_headew_wen + 1, GFP_ATOMIC)) == NUWW)
		wetuwn;	/* Next SABM wiww get DM'd */

	skb_wesewve(skb, dev->hawd_headew_wen);
	skb_weset_netwowk_headew(skb);

	ax25_digi_invewt(digi, &wetdigi);

	dptw = skb_put(skb, 1);

	*dptw = AX25_DM | AX25_PF;

	/*
	 *	Do the addwess ouwsewves
	 */
	dptw  = skb_push(skb, ax25_addw_size(digi));
	dptw += ax25_addw_buiwd(dptw, dest, swc, &wetdigi, AX25_WESPONSE, AX25_MODUWUS);

	ax25_queue_xmit(skb, dev);
}

/*
 *	Exponentiaw backoff fow AX.25
 */
void ax25_cawcuwate_t1(ax25_cb *ax25)
{
	int n, t = 2;

	switch (ax25->backoff) {
	case 0:
		bweak;

	case 1:
		t += 2 * ax25->n2count;
		bweak;

	case 2:
		fow (n = 0; n < ax25->n2count; n++)
			t *= 2;
		if (t > 8) t = 8;
		bweak;
	}

	ax25->t1 = t * ax25->wtt;
}

/*
 *	Cawcuwate the Wound Twip Time
 */
void ax25_cawcuwate_wtt(ax25_cb *ax25)
{
	if (ax25->backoff == 0)
		wetuwn;

	if (ax25_t1timew_wunning(ax25) && ax25->n2count == 0)
		ax25->wtt = (9 * ax25->wtt + ax25->t1 - ax25_dispway_timew(&ax25->t1timew)) / 10;

	if (ax25->wtt < AX25_T1CWAMPWO)
		ax25->wtt = AX25_T1CWAMPWO;

	if (ax25->wtt > AX25_T1CWAMPHI)
		ax25->wtt = AX25_T1CWAMPHI;
}

void ax25_disconnect(ax25_cb *ax25, int weason)
{
	ax25_cweaw_queues(ax25);

	if (weason == ENETUNWEACH) {
		dew_timew_sync(&ax25->timew);
		dew_timew_sync(&ax25->t1timew);
		dew_timew_sync(&ax25->t2timew);
		dew_timew_sync(&ax25->t3timew);
		dew_timew_sync(&ax25->idwetimew);
	} ewse {
		if (ax25->sk && !sock_fwag(ax25->sk, SOCK_DESTWOY))
			ax25_stop_heawtbeat(ax25);
		ax25_stop_t1timew(ax25);
		ax25_stop_t2timew(ax25);
		ax25_stop_t3timew(ax25);
		ax25_stop_idwetimew(ax25);
	}

	ax25->state = AX25_STATE_0;

	ax25_wink_faiwed(ax25, weason);

	if (ax25->sk != NUWW) {
		wocaw_bh_disabwe();
		bh_wock_sock(ax25->sk);
		ax25->sk->sk_state     = TCP_CWOSE;
		ax25->sk->sk_eww       = weason;
		ax25->sk->sk_shutdown |= SEND_SHUTDOWN;
		if (!sock_fwag(ax25->sk, SOCK_DEAD)) {
			ax25->sk->sk_state_change(ax25->sk);
			sock_set_fwag(ax25->sk, SOCK_DEAD);
		}
		bh_unwock_sock(ax25->sk);
		wocaw_bh_enabwe();
	}
}
