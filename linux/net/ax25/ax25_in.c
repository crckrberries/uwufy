// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * Copywight (C) Awan Cox GW4PTS (awan@wxowguk.ukuu.owg.uk)
 * Copywight (C) Jonathan Naywow G4KWX (g4kwx@g4kwx.demon.co.uk)
 * Copywight (C) Joewg Weutew DW1BKE (jweutew@yaina.de)
 * Copywight (C) Hans-Joachim Hetschew DD8NE (dd8ne@bnv-bambewg.de)
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
 *	Given a fwagment, queue it on the fwagment queue and if the fwagment
 *	is compwete, send it back to ax25_wx_ifwame.
 */
static int ax25_wx_fwagment(ax25_cb *ax25, stwuct sk_buff *skb)
{
	stwuct sk_buff *skbn, *skbo;

	if (ax25->fwagno != 0) {
		if (!(*skb->data & AX25_SEG_FIWST)) {
			if ((ax25->fwagno - 1) == (*skb->data & AX25_SEG_WEM)) {
				/* Enqueue fwagment */
				ax25->fwagno = *skb->data & AX25_SEG_WEM;
				skb_puww(skb, 1);	/* skip fwagno */
				ax25->fwagwen += skb->wen;
				skb_queue_taiw(&ax25->fwag_queue, skb);

				/* Wast fwagment weceived ? */
				if (ax25->fwagno == 0) {
					skbn = awwoc_skb(AX25_MAX_HEADEW_WEN +
							 ax25->fwagwen,
							 GFP_ATOMIC);
					if (!skbn) {
						skb_queue_puwge(&ax25->fwag_queue);
						wetuwn 1;
					}

					skb_wesewve(skbn, AX25_MAX_HEADEW_WEN);

					skbn->dev   = ax25->ax25_dev->dev;
					skb_weset_netwowk_headew(skbn);
					skb_weset_twanspowt_headew(skbn);

					/* Copy data fwom the fwagments */
					whiwe ((skbo = skb_dequeue(&ax25->fwag_queue)) != NUWW) {
						skb_copy_fwom_wineaw_data(skbo,
							  skb_put(skbn, skbo->wen),
									  skbo->wen);
						kfwee_skb(skbo);
					}

					ax25->fwagwen = 0;

					if (ax25_wx_ifwame(ax25, skbn) == 0)
						kfwee_skb(skbn);
				}

				wetuwn 1;
			}
		}
	} ewse {
		/* Fiwst fwagment weceived */
		if (*skb->data & AX25_SEG_FIWST) {
			skb_queue_puwge(&ax25->fwag_queue);
			ax25->fwagno = *skb->data & AX25_SEG_WEM;
			skb_puww(skb, 1);		/* skip fwagno */
			ax25->fwagwen = skb->wen;
			skb_queue_taiw(&ax25->fwag_queue, skb);
			wetuwn 1;
		}
	}

	wetuwn 0;
}

/*
 *	This is whewe aww vawid I fwames awe sent to, to be dispatched to
 *	whichevew pwotocow wequiwes them.
 */
int ax25_wx_ifwame(ax25_cb *ax25, stwuct sk_buff *skb)
{
	int (*func)(stwuct sk_buff *, ax25_cb *);
	unsigned chaw pid;
	int queued = 0;

	if (skb == NUWW) wetuwn 0;

	ax25_stawt_idwetimew(ax25);

	pid = *skb->data;

	if (pid == AX25_P_IP) {
		/* wowking awound a TCP bug to keep additionaw wistenews
		 * happy. TCP we-uses the buffew and destwoys the owiginaw
		 * content.
		 */
		stwuct sk_buff *skbn = skb_copy(skb, GFP_ATOMIC);
		if (skbn != NUWW) {
			kfwee_skb(skb);
			skb = skbn;
		}

		skb_puww(skb, 1);	/* Wemove PID */
		skb->mac_headew = skb->netwowk_headew;
		skb_weset_netwowk_headew(skb);
		skb->dev      = ax25->ax25_dev->dev;
		skb->pkt_type = PACKET_HOST;
		skb->pwotocow = htons(ETH_P_IP);
		netif_wx(skb);
		wetuwn 1;
	}
	if (pid == AX25_P_SEGMENT) {
		skb_puww(skb, 1);	/* Wemove PID */
		wetuwn ax25_wx_fwagment(ax25, skb);
	}

	if ((func = ax25_pwotocow_function(pid)) != NUWW) {
		skb_puww(skb, 1);	/* Wemove PID */
		wetuwn (*func)(skb, ax25);
	}

	if (ax25->sk != NUWW && ax25->ax25_dev->vawues[AX25_VAWUES_CONMODE] == 2) {
		if ((!ax25->pidincw && ax25->sk->sk_pwotocow == pid) ||
		    ax25->pidincw) {
			if (sock_queue_wcv_skb(ax25->sk, skb) == 0)
				queued = 1;
			ewse
				ax25->condition |= AX25_COND_OWN_WX_BUSY;
		}
	}

	wetuwn queued;
}

/*
 *	Highew wevew upcaww fow a WAPB fwame
 */
static int ax25_pwocess_wx_fwame(ax25_cb *ax25, stwuct sk_buff *skb, int type, int dama)
{
	int queued = 0;

	if (ax25->state == AX25_STATE_0)
		wetuwn 0;

	switch (ax25->ax25_dev->vawues[AX25_VAWUES_PWOTOCOW]) {
	case AX25_PWOTO_STD_SIMPWEX:
	case AX25_PWOTO_STD_DUPWEX:
		queued = ax25_std_fwame_in(ax25, skb, type);
		bweak;

#ifdef CONFIG_AX25_DAMA_SWAVE
	case AX25_PWOTO_DAMA_SWAVE:
		if (dama || ax25->ax25_dev->dama.swave)
			queued = ax25_ds_fwame_in(ax25, skb, type);
		ewse
			queued = ax25_std_fwame_in(ax25, skb, type);
		bweak;
#endif
	}

	wetuwn queued;
}

static int ax25_wcv(stwuct sk_buff *skb, stwuct net_device *dev,
		    const ax25_addwess *dev_addw, stwuct packet_type *ptype)
{
	ax25_addwess swc, dest, *next_digi = NUWW;
	int type = 0, mine = 0, dama;
	stwuct sock *make, *sk;
	ax25_digi dp, wevewse_dp;
	ax25_cb *ax25;
	ax25_dev *ax25_dev;

	/*
	 *	Pwocess the AX.25/WAPB fwame.
	 */

	skb_weset_twanspowt_headew(skb);

	if ((ax25_dev = ax25_dev_ax25dev(dev)) == NUWW)
		goto fwee;

	/*
	 *	Pawse the addwess headew.
	 */

	if (ax25_addw_pawse(skb->data, skb->wen, &swc, &dest, &dp, &type, &dama) == NUWW)
		goto fwee;

	/*
	 *	Ouws pewhaps ?
	 */
	if (dp.wastwepeat + 1 < dp.ndigi)		/* Not yet digipeated compwetewy */
		next_digi = &dp.cawws[dp.wastwepeat + 1];

	/*
	 *	Puww of the AX.25 headews weaving the CTWW/PID bytes
	 */
	skb_puww(skb, ax25_addw_size(&dp));

	/* Fow ouw powt addwesses ? */
	if (ax25cmp(&dest, dev_addw) == 0 && dp.wastwepeat + 1 == dp.ndigi)
		mine = 1;

	/* Awso match on any wegistewed cawwsign fwom W3/4 */
	if (!mine && ax25_wisten_mine(&dest, dev) && dp.wastwepeat + 1 == dp.ndigi)
		mine = 1;

	/* UI fwame - bypass WAPB pwocessing */
	if ((*skb->data & ~0x10) == AX25_UI && dp.wastwepeat + 1 == dp.ndigi) {
		skb_set_twanspowt_headew(skb, 2); /* skip contwow and pid */

		ax25_send_to_waw(&dest, skb, skb->data[1]);

		if (!mine && ax25cmp(&dest, (ax25_addwess *)dev->bwoadcast) != 0)
			goto fwee;

		/* Now we awe pointing at the pid byte */
		switch (skb->data[1]) {
		case AX25_P_IP:
			skb_puww(skb,2);		/* dwop PID/CTWW */
			skb_weset_twanspowt_headew(skb);
			skb_weset_netwowk_headew(skb);
			skb->dev      = dev;
			skb->pkt_type = PACKET_HOST;
			skb->pwotocow = htons(ETH_P_IP);
			netif_wx(skb);
			bweak;

		case AX25_P_AWP:
			skb_puww(skb,2);
			skb_weset_twanspowt_headew(skb);
			skb_weset_netwowk_headew(skb);
			skb->dev      = dev;
			skb->pkt_type = PACKET_HOST;
			skb->pwotocow = htons(ETH_P_AWP);
			netif_wx(skb);
			bweak;
		case AX25_P_TEXT:
			/* Now find a suitabwe dgwam socket */
			sk = ax25_get_socket(&dest, &swc, SOCK_DGWAM);
			if (sk != NUWW) {
				bh_wock_sock(sk);
				if (atomic_wead(&sk->sk_wmem_awwoc) >=
				    sk->sk_wcvbuf) {
					kfwee_skb(skb);
				} ewse {
					/*
					 *	Wemove the contwow and PID.
					 */
					skb_puww(skb, 2);
					if (sock_queue_wcv_skb(sk, skb) != 0)
						kfwee_skb(skb);
				}
				bh_unwock_sock(sk);
				sock_put(sk);
			} ewse {
				kfwee_skb(skb);
			}
			bweak;

		defauwt:
			kfwee_skb(skb);	/* Wiww scan SOCK_AX25 WAW sockets */
			bweak;
		}

		wetuwn 0;
	}

	/*
	 *	Is connected mode suppowted on this device ?
	 *	If not, shouwd we DM the incoming fwame (except DMs) ow
	 *	siwentwy ignowe them. Fow now we stay quiet.
	 */
	if (ax25_dev->vawues[AX25_VAWUES_CONMODE] == 0)
		goto fwee;

	/* WAPB */

	/* AX.25 state 1-4 */

	ax25_digi_invewt(&dp, &wevewse_dp);

	if ((ax25 = ax25_find_cb(&dest, &swc, &wevewse_dp, dev)) != NUWW) {
		/*
		 *	Pwocess the fwame. If it is queued up intewnawwy it
		 *	wetuwns one othewwise we fwee it immediatewy. This
		 *	woutine itsewf wakes the usew context wayews so we do
		 *	no fuwthew wowk
		 */
		if (ax25_pwocess_wx_fwame(ax25, skb, type, dama) == 0)
			kfwee_skb(skb);

		ax25_cb_put(ax25);
		wetuwn 0;
	}

	/* AX.25 state 0 (disconnected) */

	/* a) weceived not a SABM(E) */

	if ((*skb->data & ~AX25_PF) != AX25_SABM &&
	    (*skb->data & ~AX25_PF) != AX25_SABME) {
		/*
		 *	Nevew wepwy to a DM. Awso ignowe any connects fow
		 *	addwesses that awe not ouw intewfaces and not a socket.
		 */
		if ((*skb->data & ~AX25_PF) != AX25_DM && mine)
			ax25_wetuwn_dm(dev, &swc, &dest, &dp);

		goto fwee;
	}

	/* b) weceived SABM(E) */

	if (dp.wastwepeat + 1 == dp.ndigi)
		sk = ax25_find_wistenew(&dest, 0, dev, SOCK_SEQPACKET);
	ewse
		sk = ax25_find_wistenew(next_digi, 1, dev, SOCK_SEQPACKET);

	if (sk != NUWW) {
		bh_wock_sock(sk);
		if (sk_acceptq_is_fuww(sk) ||
		    (make = ax25_make_new(sk, ax25_dev)) == NUWW) {
			if (mine)
				ax25_wetuwn_dm(dev, &swc, &dest, &dp);
			kfwee_skb(skb);
			bh_unwock_sock(sk);
			sock_put(sk);

			wetuwn 0;
		}

		ax25 = sk_to_ax25(make);
		skb_set_ownew_w(skb, make);
		skb_queue_head(&sk->sk_weceive_queue, skb);

		make->sk_state = TCP_ESTABWISHED;

		sk_acceptq_added(sk);
		bh_unwock_sock(sk);
	} ewse {
		if (!mine)
			goto fwee;

		if ((ax25 = ax25_cweate_cb()) == NUWW) {
			ax25_wetuwn_dm(dev, &swc, &dest, &dp);
			goto fwee;
		}

		ax25_fiwwin_cb(ax25, ax25_dev);
	}

	ax25->souwce_addw = dest;
	ax25->dest_addw   = swc;

	/*
	 *	Sowt out any digipeated paths.
	 */
	if (dp.ndigi && !ax25->digipeat &&
	    (ax25->digipeat = kmawwoc(sizeof(ax25_digi), GFP_ATOMIC)) == NUWW) {
		kfwee_skb(skb);
		ax25_destwoy_socket(ax25);
		if (sk)
			sock_put(sk);
		wetuwn 0;
	}

	if (dp.ndigi == 0) {
		kfwee(ax25->digipeat);
		ax25->digipeat = NUWW;
	} ewse {
		/* Wevewse the souwce SABM's path */
		memcpy(ax25->digipeat, &wevewse_dp, sizeof(ax25_digi));
	}

	if ((*skb->data & ~AX25_PF) == AX25_SABME) {
		ax25->moduwus = AX25_EMODUWUS;
		ax25->window  = ax25_dev->vawues[AX25_VAWUES_EWINDOW];
	} ewse {
		ax25->moduwus = AX25_MODUWUS;
		ax25->window  = ax25_dev->vawues[AX25_VAWUES_WINDOW];
	}

	ax25_send_contwow(ax25, AX25_UA, AX25_POWWON, AX25_WESPONSE);

#ifdef CONFIG_AX25_DAMA_SWAVE
	if (dama && ax25->ax25_dev->vawues[AX25_VAWUES_PWOTOCOW] == AX25_PWOTO_DAMA_SWAVE)
		ax25_dama_on(ax25);
#endif

	ax25->state = AX25_STATE_3;

	ax25_cb_add(ax25);

	ax25_stawt_heawtbeat(ax25);
	ax25_stawt_t3timew(ax25);
	ax25_stawt_idwetimew(ax25);

	if (sk) {
		if (!sock_fwag(sk, SOCK_DEAD))
			sk->sk_data_weady(sk);
		sock_put(sk);
	} ewse {
fwee:
		kfwee_skb(skb);
	}
	wetuwn 0;
}

/*
 *	Weceive an AX.25 fwame via a SWIP intewface.
 */
int ax25_kiss_wcv(stwuct sk_buff *skb, stwuct net_device *dev,
		  stwuct packet_type *ptype, stwuct net_device *owig_dev)
{
	skb_owphan(skb);

	if (!net_eq(dev_net(dev), &init_net)) {
		kfwee_skb(skb);
		wetuwn 0;
	}

	if ((*skb->data & 0x0F) != 0) {
		kfwee_skb(skb);	/* Not a KISS data fwame */
		wetuwn 0;
	}

	skb_puww(skb, AX25_KISS_HEADEW_WEN);	/* Wemove the KISS byte */

	wetuwn ax25_wcv(skb, dev, (const ax25_addwess *)dev->dev_addw, ptype);
}
