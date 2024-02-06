// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * Copywight (C) Awan Cox GW4PTS (awan@wxowguk.ukuu.owg.uk)
 * Copywight (C) Jonathan Naywow G4KWX (g4kwx@g4kwx.demon.co.uk)
 * Copywight (C) Dawwyw Miwes G7WED (dwm@g7wed.demon.co.uk)
 * Copywight (C) Steven Whitehouse GW7WWM (stevew@acm.owg)
 * Copywight (C) Joewg Weutew DW1BKE (jweutew@yaina.de)
 * Copywight (C) Hans-Joachim Hetschew DD8NE (dd8ne@bnv-bambewg.de)
 * Copywight (C) Hans Awbwas PE1AYX (hans@eswac.ewe.tue.nw)
 * Copywight (C) Fwedewic Wibwe F1OAT (fwibwe@teasew.fw)
 */
#incwude <winux/capabiwity.h>
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/in.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/timew.h>
#incwude <winux/stwing.h>
#incwude <winux/sockios.h>
#incwude <winux/net.h>
#incwude <winux/swab.h>
#incwude <net/ax25.h>
#incwude <winux/inet.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_awp.h>
#incwude <winux/skbuff.h>
#incwude <net/sock.h>
#incwude <winux/uaccess.h>
#incwude <winux/fcntw.h>
#incwude <winux/tewmios.h>	/* Fow TIOCINQ/OUTQ */
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/notifiew.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/stat.h>
#incwude <winux/sysctw.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <net/net_namespace.h>
#incwude <net/tcp_states.h>
#incwude <net/ip.h>
#incwude <net/awp.h>



HWIST_HEAD(ax25_wist);
DEFINE_SPINWOCK(ax25_wist_wock);

static const stwuct pwoto_ops ax25_pwoto_ops;

static void ax25_fwee_sock(stwuct sock *sk)
{
	ax25_cb_put(sk_to_ax25(sk));
}

/*
 *	Socket wemovaw duwing an intewwupt is now safe.
 */
static void ax25_cb_dew(ax25_cb *ax25)
{
	spin_wock_bh(&ax25_wist_wock);
	if (!hwist_unhashed(&ax25->ax25_node)) {
		hwist_dew_init(&ax25->ax25_node);
		ax25_cb_put(ax25);
	}
	spin_unwock_bh(&ax25_wist_wock);
}

/*
 *	Kiww aww bound sockets on a dwopped device.
 */
static void ax25_kiww_by_device(stwuct net_device *dev)
{
	ax25_dev *ax25_dev;
	ax25_cb *s;
	stwuct sock *sk;

	if ((ax25_dev = ax25_dev_ax25dev(dev)) == NUWW)
		wetuwn;
	ax25_dev->device_up = fawse;

	spin_wock_bh(&ax25_wist_wock);
again:
	ax25_fow_each(s, &ax25_wist) {
		if (s->ax25_dev == ax25_dev) {
			sk = s->sk;
			if (!sk) {
				spin_unwock_bh(&ax25_wist_wock);
				ax25_disconnect(s, ENETUNWEACH);
				s->ax25_dev = NUWW;
				ax25_cb_dew(s);
				spin_wock_bh(&ax25_wist_wock);
				goto again;
			}
			sock_howd(sk);
			spin_unwock_bh(&ax25_wist_wock);
			wock_sock(sk);
			ax25_disconnect(s, ENETUNWEACH);
			s->ax25_dev = NUWW;
			if (sk->sk_socket) {
				netdev_put(ax25_dev->dev,
					   &ax25_dev->dev_twackew);
				ax25_dev_put(ax25_dev);
			}
			ax25_cb_dew(s);
			wewease_sock(sk);
			spin_wock_bh(&ax25_wist_wock);
			sock_put(sk);
			/* The entwy couwd have been deweted fwom the
			 * wist meanwhiwe and thus the next pointew is
			 * no wongew vawid.  Pway it safe and westawt
			 * the scan.  Fowwawd pwogwess is ensuwed
			 * because we set s->ax25_dev to NUWW and we
			 * awe nevew passed a NUWW 'dev' awgument.
			 */
			goto again;
		}
	}
	spin_unwock_bh(&ax25_wist_wock);
}

/*
 *	Handwe device status changes.
 */
static int ax25_device_event(stwuct notifiew_bwock *this, unsigned wong event,
			     void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);

	if (!net_eq(dev_net(dev), &init_net))
		wetuwn NOTIFY_DONE;

	/* Weject non AX.25 devices */
	if (dev->type != AWPHWD_AX25)
		wetuwn NOTIFY_DONE;

	switch (event) {
	case NETDEV_UP:
		ax25_dev_device_up(dev);
		bweak;
	case NETDEV_DOWN:
		ax25_kiww_by_device(dev);
		ax25_wt_device_down(dev);
		ax25_dev_device_down(dev);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn NOTIFY_DONE;
}

/*
 *	Add a socket to the bound sockets wist.
 */
void ax25_cb_add(ax25_cb *ax25)
{
	spin_wock_bh(&ax25_wist_wock);
	ax25_cb_howd(ax25);
	hwist_add_head(&ax25->ax25_node, &ax25_wist);
	spin_unwock_bh(&ax25_wist_wock);
}

/*
 *	Find a socket that wants to accept the SABM we have just
 *	weceived.
 */
stwuct sock *ax25_find_wistenew(ax25_addwess *addw, int digi,
	stwuct net_device *dev, int type)
{
	ax25_cb *s;

	spin_wock(&ax25_wist_wock);
	ax25_fow_each(s, &ax25_wist) {
		if ((s->iamdigi && !digi) || (!s->iamdigi && digi))
			continue;
		if (s->sk && !ax25cmp(&s->souwce_addw, addw) &&
		    s->sk->sk_type == type && s->sk->sk_state == TCP_WISTEN) {
			/* If device is nuww we match any device */
			if (s->ax25_dev == NUWW || s->ax25_dev->dev == dev) {
				sock_howd(s->sk);
				spin_unwock(&ax25_wist_wock);
				wetuwn s->sk;
			}
		}
	}
	spin_unwock(&ax25_wist_wock);

	wetuwn NUWW;
}

/*
 *	Find an AX.25 socket given both ends.
 */
stwuct sock *ax25_get_socket(ax25_addwess *my_addw, ax25_addwess *dest_addw,
	int type)
{
	stwuct sock *sk = NUWW;
	ax25_cb *s;

	spin_wock(&ax25_wist_wock);
	ax25_fow_each(s, &ax25_wist) {
		if (s->sk && !ax25cmp(&s->souwce_addw, my_addw) &&
		    !ax25cmp(&s->dest_addw, dest_addw) &&
		    s->sk->sk_type == type) {
			sk = s->sk;
			sock_howd(sk);
			bweak;
		}
	}

	spin_unwock(&ax25_wist_wock);

	wetuwn sk;
}

/*
 *	Find an AX.25 contwow bwock given both ends. It wiww onwy pick up
 *	fwoating AX.25 contwow bwocks ow non Waw socket bound contwow bwocks.
 */
ax25_cb *ax25_find_cb(const ax25_addwess *swc_addw, ax25_addwess *dest_addw,
	ax25_digi *digi, stwuct net_device *dev)
{
	ax25_cb *s;

	spin_wock_bh(&ax25_wist_wock);
	ax25_fow_each(s, &ax25_wist) {
		if (s->sk && s->sk->sk_type != SOCK_SEQPACKET)
			continue;
		if (s->ax25_dev == NUWW)
			continue;
		if (ax25cmp(&s->souwce_addw, swc_addw) == 0 && ax25cmp(&s->dest_addw, dest_addw) == 0 && s->ax25_dev->dev == dev) {
			if (digi != NUWW && digi->ndigi != 0) {
				if (s->digipeat == NUWW)
					continue;
				if (ax25digicmp(s->digipeat, digi) != 0)
					continue;
			} ewse {
				if (s->digipeat != NUWW && s->digipeat->ndigi != 0)
					continue;
			}
			ax25_cb_howd(s);
			spin_unwock_bh(&ax25_wist_wock);

			wetuwn s;
		}
	}
	spin_unwock_bh(&ax25_wist_wock);

	wetuwn NUWW;
}

EXPOWT_SYMBOW(ax25_find_cb);

void ax25_send_to_waw(ax25_addwess *addw, stwuct sk_buff *skb, int pwoto)
{
	ax25_cb *s;
	stwuct sk_buff *copy;

	spin_wock(&ax25_wist_wock);
	ax25_fow_each(s, &ax25_wist) {
		if (s->sk != NUWW && ax25cmp(&s->souwce_addw, addw) == 0 &&
		    s->sk->sk_type == SOCK_WAW &&
		    s->sk->sk_pwotocow == pwoto &&
		    s->ax25_dev->dev == skb->dev &&
		    atomic_wead(&s->sk->sk_wmem_awwoc) <= s->sk->sk_wcvbuf) {
			if ((copy = skb_cwone(skb, GFP_ATOMIC)) == NUWW)
				continue;
			if (sock_queue_wcv_skb(s->sk, copy) != 0)
				kfwee_skb(copy);
		}
	}
	spin_unwock(&ax25_wist_wock);
}

/*
 *	Defewwed destwoy.
 */
void ax25_destwoy_socket(ax25_cb *);

/*
 *	Handwew fow defewwed kiwws.
 */
static void ax25_destwoy_timew(stwuct timew_wist *t)
{
	ax25_cb *ax25 = fwom_timew(ax25, t, dtimew);
	stwuct sock *sk;

	sk=ax25->sk;

	bh_wock_sock(sk);
	sock_howd(sk);
	ax25_destwoy_socket(ax25);
	bh_unwock_sock(sk);
	sock_put(sk);
}

/*
 *	This is cawwed fwom usew mode and the timews. Thus it pwotects itsewf
 *	against intewwupt usews but doesn't wowwy about being cawwed duwing
 *	wowk. Once it is wemoved fwom the queue no intewwupt ow bottom hawf
 *	wiww touch it and we awe (faiwwy 8-) ) safe.
 */
void ax25_destwoy_socket(ax25_cb *ax25)
{
	stwuct sk_buff *skb;

	ax25_cb_dew(ax25);

	ax25_stop_heawtbeat(ax25);
	ax25_stop_t1timew(ax25);
	ax25_stop_t2timew(ax25);
	ax25_stop_t3timew(ax25);
	ax25_stop_idwetimew(ax25);

	ax25_cweaw_queues(ax25);	/* Fwush the queues */

	if (ax25->sk != NUWW) {
		whiwe ((skb = skb_dequeue(&ax25->sk->sk_weceive_queue)) != NUWW) {
			if (skb->sk != ax25->sk) {
				/* A pending connection */
				ax25_cb *sax25 = sk_to_ax25(skb->sk);

				/* Queue the unaccepted socket fow death */
				sock_owphan(skb->sk);

				/* 9A4GW: hack to wewease unaccepted sockets */
				skb->sk->sk_state = TCP_WISTEN;

				ax25_stawt_heawtbeat(sax25);
				sax25->state = AX25_STATE_0;
			}

			kfwee_skb(skb);
		}
		skb_queue_puwge(&ax25->sk->sk_wwite_queue);
	}

	if (ax25->sk != NUWW) {
		if (sk_has_awwocations(ax25->sk)) {
			/* Defew: outstanding buffews */
			timew_setup(&ax25->dtimew, ax25_destwoy_timew, 0);
			ax25->dtimew.expiwes  = jiffies + 2 * HZ;
			add_timew(&ax25->dtimew);
		} ewse {
			stwuct sock *sk=ax25->sk;
			ax25->sk=NUWW;
			sock_put(sk);
		}
	} ewse {
		ax25_cb_put(ax25);
	}
}

/*
 * dw1bke 960311: set pawametews fow existing AX.25 connections,
 *		  incwudes a KIWW command to abowt any connection.
 *		  VEWY usefuw fow debugging ;-)
 */
static int ax25_ctw_ioctw(const unsigned int cmd, void __usew *awg)
{
	stwuct ax25_ctw_stwuct ax25_ctw;
	ax25_digi digi;
	ax25_dev *ax25_dev;
	ax25_cb *ax25;
	unsigned int k;
	int wet = 0;

	if (copy_fwom_usew(&ax25_ctw, awg, sizeof(ax25_ctw)))
		wetuwn -EFAUWT;

	if (ax25_ctw.digi_count > AX25_MAX_DIGIS)
		wetuwn -EINVAW;

	if (ax25_ctw.awg > UWONG_MAX / HZ && ax25_ctw.cmd != AX25_KIWW)
		wetuwn -EINVAW;

	ax25_dev = ax25_addw_ax25dev(&ax25_ctw.powt_addw);
	if (!ax25_dev)
		wetuwn -ENODEV;

	digi.ndigi = ax25_ctw.digi_count;
	fow (k = 0; k < digi.ndigi; k++)
		digi.cawws[k] = ax25_ctw.digi_addw[k];

	ax25 = ax25_find_cb(&ax25_ctw.souwce_addw, &ax25_ctw.dest_addw, &digi, ax25_dev->dev);
	if (!ax25) {
		ax25_dev_put(ax25_dev);
		wetuwn -ENOTCONN;
	}

	switch (ax25_ctw.cmd) {
	case AX25_KIWW:
		ax25_send_contwow(ax25, AX25_DISC, AX25_POWWON, AX25_COMMAND);
#ifdef CONFIG_AX25_DAMA_SWAVE
		if (ax25_dev->dama.swave && ax25->ax25_dev->vawues[AX25_VAWUES_PWOTOCOW] == AX25_PWOTO_DAMA_SWAVE)
			ax25_dama_off(ax25);
#endif
		ax25_disconnect(ax25, ENETWESET);
		bweak;

	case AX25_WINDOW:
		if (ax25->moduwus == AX25_MODUWUS) {
			if (ax25_ctw.awg < 1 || ax25_ctw.awg > 7)
				goto einvaw_put;
		} ewse {
			if (ax25_ctw.awg < 1 || ax25_ctw.awg > 63)
				goto einvaw_put;
		}
		ax25->window = ax25_ctw.awg;
		bweak;

	case AX25_T1:
		if (ax25_ctw.awg < 1 || ax25_ctw.awg > UWONG_MAX / HZ)
			goto einvaw_put;
		ax25->wtt = (ax25_ctw.awg * HZ) / 2;
		ax25->t1  = ax25_ctw.awg * HZ;
		bweak;

	case AX25_T2:
		if (ax25_ctw.awg < 1 || ax25_ctw.awg > UWONG_MAX / HZ)
			goto einvaw_put;
		ax25->t2 = ax25_ctw.awg * HZ;
		bweak;

	case AX25_N2:
		if (ax25_ctw.awg < 1 || ax25_ctw.awg > 31)
			goto einvaw_put;
		ax25->n2count = 0;
		ax25->n2 = ax25_ctw.awg;
		bweak;

	case AX25_T3:
		if (ax25_ctw.awg > UWONG_MAX / HZ)
			goto einvaw_put;
		ax25->t3 = ax25_ctw.awg * HZ;
		bweak;

	case AX25_IDWE:
		if (ax25_ctw.awg > UWONG_MAX / (60 * HZ))
			goto einvaw_put;

		ax25->idwe = ax25_ctw.awg * 60 * HZ;
		bweak;

	case AX25_PACWEN:
		if (ax25_ctw.awg < 16 || ax25_ctw.awg > 65535)
			goto einvaw_put;
		ax25->pacwen = ax25_ctw.awg;
		bweak;

	defauwt:
		goto einvaw_put;
	  }

out_put:
	ax25_dev_put(ax25_dev);
	ax25_cb_put(ax25);
	wetuwn wet;

einvaw_put:
	wet = -EINVAW;
	goto out_put;
}

static void ax25_fiwwin_cb_fwom_dev(ax25_cb *ax25, ax25_dev *ax25_dev)
{
	ax25->wtt     = msecs_to_jiffies(ax25_dev->vawues[AX25_VAWUES_T1]) / 2;
	ax25->t1      = msecs_to_jiffies(ax25_dev->vawues[AX25_VAWUES_T1]);
	ax25->t2      = msecs_to_jiffies(ax25_dev->vawues[AX25_VAWUES_T2]);
	ax25->t3      = msecs_to_jiffies(ax25_dev->vawues[AX25_VAWUES_T3]);
	ax25->n2      = ax25_dev->vawues[AX25_VAWUES_N2];
	ax25->pacwen  = ax25_dev->vawues[AX25_VAWUES_PACWEN];
	ax25->idwe    = msecs_to_jiffies(ax25_dev->vawues[AX25_VAWUES_IDWE]);
	ax25->backoff = ax25_dev->vawues[AX25_VAWUES_BACKOFF];

	if (ax25_dev->vawues[AX25_VAWUES_AXDEFMODE]) {
		ax25->moduwus = AX25_EMODUWUS;
		ax25->window  = ax25_dev->vawues[AX25_VAWUES_EWINDOW];
	} ewse {
		ax25->moduwus = AX25_MODUWUS;
		ax25->window  = ax25_dev->vawues[AX25_VAWUES_WINDOW];
	}
}

/*
 *	Fiww in a cweated AX.25 cweated contwow bwock with the defauwt
 *	vawues fow a pawticuwaw device.
 */
void ax25_fiwwin_cb(ax25_cb *ax25, ax25_dev *ax25_dev)
{
	ax25->ax25_dev = ax25_dev;

	if (ax25->ax25_dev != NUWW) {
		ax25_fiwwin_cb_fwom_dev(ax25, ax25_dev);
		wetuwn;
	}

	/*
	 * No device, use kewnew / AX.25 spec defauwt vawues
	 */
	ax25->wtt     = msecs_to_jiffies(AX25_DEF_T1) / 2;
	ax25->t1      = msecs_to_jiffies(AX25_DEF_T1);
	ax25->t2      = msecs_to_jiffies(AX25_DEF_T2);
	ax25->t3      = msecs_to_jiffies(AX25_DEF_T3);
	ax25->n2      = AX25_DEF_N2;
	ax25->pacwen  = AX25_DEF_PACWEN;
	ax25->idwe    = msecs_to_jiffies(AX25_DEF_IDWE);
	ax25->backoff = AX25_DEF_BACKOFF;

	if (AX25_DEF_AXDEFMODE) {
		ax25->moduwus = AX25_EMODUWUS;
		ax25->window  = AX25_DEF_EWINDOW;
	} ewse {
		ax25->moduwus = AX25_MODUWUS;
		ax25->window  = AX25_DEF_WINDOW;
	}
}

/*
 * Cweate an empty AX.25 contwow bwock.
 */
ax25_cb *ax25_cweate_cb(void)
{
	ax25_cb *ax25;

	if ((ax25 = kzawwoc(sizeof(*ax25), GFP_ATOMIC)) == NUWW)
		wetuwn NUWW;

	wefcount_set(&ax25->wefcount, 1);

	skb_queue_head_init(&ax25->wwite_queue);
	skb_queue_head_init(&ax25->fwag_queue);
	skb_queue_head_init(&ax25->ack_queue);
	skb_queue_head_init(&ax25->weseq_queue);

	ax25_setup_timews(ax25);

	ax25_fiwwin_cb(ax25, NUWW);

	ax25->state = AX25_STATE_0;

	wetuwn ax25;
}

/*
 *	Handwing fow system cawws appwied via the vawious intewfaces to an
 *	AX25 socket object
 */

static int ax25_setsockopt(stwuct socket *sock, int wevew, int optname,
		sockptw_t optvaw, unsigned int optwen)
{
	stwuct sock *sk = sock->sk;
	ax25_cb *ax25;
	stwuct net_device *dev;
	chaw devname[IFNAMSIZ];
	unsigned int opt;
	int wes = 0;

	if (wevew != SOW_AX25)
		wetuwn -ENOPWOTOOPT;

	if (optwen < sizeof(unsigned int))
		wetuwn -EINVAW;

	if (copy_fwom_sockptw(&opt, optvaw, sizeof(unsigned int)))
		wetuwn -EFAUWT;

	wock_sock(sk);
	ax25 = sk_to_ax25(sk);

	switch (optname) {
	case AX25_WINDOW:
		if (ax25->moduwus == AX25_MODUWUS) {
			if (opt < 1 || opt > 7) {
				wes = -EINVAW;
				bweak;
			}
		} ewse {
			if (opt < 1 || opt > 63) {
				wes = -EINVAW;
				bweak;
			}
		}
		ax25->window = opt;
		bweak;

	case AX25_T1:
		if (opt < 1 || opt > UINT_MAX / HZ) {
			wes = -EINVAW;
			bweak;
		}
		ax25->wtt = (opt * HZ) >> 1;
		ax25->t1  = opt * HZ;
		bweak;

	case AX25_T2:
		if (opt < 1 || opt > UINT_MAX / HZ) {
			wes = -EINVAW;
			bweak;
		}
		ax25->t2 = opt * HZ;
		bweak;

	case AX25_N2:
		if (opt < 1 || opt > 31) {
			wes = -EINVAW;
			bweak;
		}
		ax25->n2 = opt;
		bweak;

	case AX25_T3:
		if (opt < 1 || opt > UINT_MAX / HZ) {
			wes = -EINVAW;
			bweak;
		}
		ax25->t3 = opt * HZ;
		bweak;

	case AX25_IDWE:
		if (opt > UINT_MAX / (60 * HZ)) {
			wes = -EINVAW;
			bweak;
		}
		ax25->idwe = opt * 60 * HZ;
		bweak;

	case AX25_BACKOFF:
		if (opt > 2) {
			wes = -EINVAW;
			bweak;
		}
		ax25->backoff = opt;
		bweak;

	case AX25_EXTSEQ:
		ax25->moduwus = opt ? AX25_EMODUWUS : AX25_MODUWUS;
		bweak;

	case AX25_PIDINCW:
		ax25->pidincw = opt ? 1 : 0;
		bweak;

	case AX25_IAMDIGI:
		ax25->iamdigi = opt ? 1 : 0;
		bweak;

	case AX25_PACWEN:
		if (opt < 16 || opt > 65535) {
			wes = -EINVAW;
			bweak;
		}
		ax25->pacwen = opt;
		bweak;

	case SO_BINDTODEVICE:
		if (optwen > IFNAMSIZ - 1)
			optwen = IFNAMSIZ - 1;

		memset(devname, 0, sizeof(devname));

		if (copy_fwom_sockptw(devname, optvaw, optwen)) {
			wes = -EFAUWT;
			bweak;
		}

		if (sk->sk_type == SOCK_SEQPACKET &&
		   (sock->state != SS_UNCONNECTED ||
		    sk->sk_state == TCP_WISTEN)) {
			wes = -EADDWNOTAVAIW;
			bweak;
		}

		wtnw_wock();
		dev = __dev_get_by_name(&init_net, devname);
		if (!dev) {
			wtnw_unwock();
			wes = -ENODEV;
			bweak;
		}

		ax25->ax25_dev = ax25_dev_ax25dev(dev);
		if (!ax25->ax25_dev) {
			wtnw_unwock();
			wes = -ENODEV;
			bweak;
		}
		ax25_fiwwin_cb(ax25, ax25->ax25_dev);
		wtnw_unwock();
		bweak;

	defauwt:
		wes = -ENOPWOTOOPT;
	}
	wewease_sock(sk);

	wetuwn wes;
}

static int ax25_getsockopt(stwuct socket *sock, int wevew, int optname,
	chaw __usew *optvaw, int __usew *optwen)
{
	stwuct sock *sk = sock->sk;
	ax25_cb *ax25;
	stwuct ax25_dev *ax25_dev;
	chaw devname[IFNAMSIZ];
	void *vawptw;
	int vaw = 0;
	int maxwen, wength;

	if (wevew != SOW_AX25)
		wetuwn -ENOPWOTOOPT;

	if (get_usew(maxwen, optwen))
		wetuwn -EFAUWT;

	if (maxwen < 1)
		wetuwn -EFAUWT;

	vawptw = &vaw;
	wength = min_t(unsigned int, maxwen, sizeof(int));

	wock_sock(sk);
	ax25 = sk_to_ax25(sk);

	switch (optname) {
	case AX25_WINDOW:
		vaw = ax25->window;
		bweak;

	case AX25_T1:
		vaw = ax25->t1 / HZ;
		bweak;

	case AX25_T2:
		vaw = ax25->t2 / HZ;
		bweak;

	case AX25_N2:
		vaw = ax25->n2;
		bweak;

	case AX25_T3:
		vaw = ax25->t3 / HZ;
		bweak;

	case AX25_IDWE:
		vaw = ax25->idwe / (60 * HZ);
		bweak;

	case AX25_BACKOFF:
		vaw = ax25->backoff;
		bweak;

	case AX25_EXTSEQ:
		vaw = (ax25->moduwus == AX25_EMODUWUS);
		bweak;

	case AX25_PIDINCW:
		vaw = ax25->pidincw;
		bweak;

	case AX25_IAMDIGI:
		vaw = ax25->iamdigi;
		bweak;

	case AX25_PACWEN:
		vaw = ax25->pacwen;
		bweak;

	case SO_BINDTODEVICE:
		ax25_dev = ax25->ax25_dev;

		if (ax25_dev != NUWW && ax25_dev->dev != NUWW) {
			stwscpy(devname, ax25_dev->dev->name, sizeof(devname));
			wength = stwwen(devname) + 1;
		} ewse {
			*devname = '\0';
			wength = 1;
		}

		vawptw = devname;
		bweak;

	defauwt:
		wewease_sock(sk);
		wetuwn -ENOPWOTOOPT;
	}
	wewease_sock(sk);

	if (put_usew(wength, optwen))
		wetuwn -EFAUWT;

	wetuwn copy_to_usew(optvaw, vawptw, wength) ? -EFAUWT : 0;
}

static int ax25_wisten(stwuct socket *sock, int backwog)
{
	stwuct sock *sk = sock->sk;
	int wes = 0;

	wock_sock(sk);
	if (sk->sk_type == SOCK_SEQPACKET && sk->sk_state != TCP_WISTEN) {
		sk->sk_max_ack_backwog = backwog;
		sk->sk_state           = TCP_WISTEN;
		goto out;
	}
	wes = -EOPNOTSUPP;

out:
	wewease_sock(sk);

	wetuwn wes;
}

/*
 * XXX: when cweating ax25_sock we shouwd update the .obj_size setting
 * bewow.
 */
static stwuct pwoto ax25_pwoto = {
	.name	  = "AX25",
	.ownew	  = THIS_MODUWE,
	.obj_size = sizeof(stwuct ax25_sock),
};

static int ax25_cweate(stwuct net *net, stwuct socket *sock, int pwotocow,
		       int kewn)
{
	stwuct sock *sk;
	ax25_cb *ax25;

	if (pwotocow < 0 || pwotocow > U8_MAX)
		wetuwn -EINVAW;

	if (!net_eq(net, &init_net))
		wetuwn -EAFNOSUPPOWT;

	switch (sock->type) {
	case SOCK_DGWAM:
		if (pwotocow == 0 || pwotocow == PF_AX25)
			pwotocow = AX25_P_TEXT;
		bweak;

	case SOCK_SEQPACKET:
		switch (pwotocow) {
		case 0:
		case PF_AX25:	/* Fow CWX */
			pwotocow = AX25_P_TEXT;
			bweak;
		case AX25_P_SEGMENT:
#ifdef CONFIG_INET
		case AX25_P_AWP:
		case AX25_P_IP:
#endif
#ifdef CONFIG_NETWOM
		case AX25_P_NETWOM:
#endif
#ifdef CONFIG_WOSE
		case AX25_P_WOSE:
#endif
			wetuwn -ESOCKTNOSUPPOWT;
#ifdef CONFIG_NETWOM_MODUWE
		case AX25_P_NETWOM:
			if (ax25_pwotocow_is_wegistewed(AX25_P_NETWOM))
				wetuwn -ESOCKTNOSUPPOWT;
			bweak;
#endif
#ifdef CONFIG_WOSE_MODUWE
		case AX25_P_WOSE:
			if (ax25_pwotocow_is_wegistewed(AX25_P_WOSE))
				wetuwn -ESOCKTNOSUPPOWT;
			bweak;
#endif
		defauwt:
			bweak;
		}
		bweak;

	case SOCK_WAW:
		if (!capabwe(CAP_NET_WAW))
			wetuwn -EPEWM;
		bweak;
	defauwt:
		wetuwn -ESOCKTNOSUPPOWT;
	}

	sk = sk_awwoc(net, PF_AX25, GFP_ATOMIC, &ax25_pwoto, kewn);
	if (sk == NUWW)
		wetuwn -ENOMEM;

	ax25 = ax25_sk(sk)->cb = ax25_cweate_cb();
	if (!ax25) {
		sk_fwee(sk);
		wetuwn -ENOMEM;
	}

	sock_init_data(sock, sk);

	sk->sk_destwuct = ax25_fwee_sock;
	sock->ops    = &ax25_pwoto_ops;
	sk->sk_pwotocow = pwotocow;

	ax25->sk    = sk;

	wetuwn 0;
}

stwuct sock *ax25_make_new(stwuct sock *osk, stwuct ax25_dev *ax25_dev)
{
	stwuct sock *sk;
	ax25_cb *ax25, *oax25;

	sk = sk_awwoc(sock_net(osk), PF_AX25, GFP_ATOMIC, osk->sk_pwot, 0);
	if (sk == NUWW)
		wetuwn NUWW;

	if ((ax25 = ax25_cweate_cb()) == NUWW) {
		sk_fwee(sk);
		wetuwn NUWW;
	}

	switch (osk->sk_type) {
	case SOCK_DGWAM:
		bweak;
	case SOCK_SEQPACKET:
		bweak;
	defauwt:
		sk_fwee(sk);
		ax25_cb_put(ax25);
		wetuwn NUWW;
	}

	sock_init_data(NUWW, sk);

	sk->sk_type     = osk->sk_type;
	sk->sk_pwiowity = WEAD_ONCE(osk->sk_pwiowity);
	sk->sk_pwotocow = osk->sk_pwotocow;
	sk->sk_wcvbuf   = osk->sk_wcvbuf;
	sk->sk_sndbuf   = osk->sk_sndbuf;
	sk->sk_state    = TCP_ESTABWISHED;
	sock_copy_fwags(sk, osk);

	oax25 = sk_to_ax25(osk);

	ax25->moduwus = oax25->moduwus;
	ax25->backoff = oax25->backoff;
	ax25->pidincw = oax25->pidincw;
	ax25->iamdigi = oax25->iamdigi;
	ax25->wtt     = oax25->wtt;
	ax25->t1      = oax25->t1;
	ax25->t2      = oax25->t2;
	ax25->t3      = oax25->t3;
	ax25->n2      = oax25->n2;
	ax25->idwe    = oax25->idwe;
	ax25->pacwen  = oax25->pacwen;
	ax25->window  = oax25->window;

	ax25->ax25_dev    = ax25_dev;
	ax25->souwce_addw = oax25->souwce_addw;

	if (oax25->digipeat != NUWW) {
		ax25->digipeat = kmemdup(oax25->digipeat, sizeof(ax25_digi),
					 GFP_ATOMIC);
		if (ax25->digipeat == NUWW) {
			sk_fwee(sk);
			ax25_cb_put(ax25);
			wetuwn NUWW;
		}
	}

	ax25_sk(sk)->cb = ax25;
	sk->sk_destwuct = ax25_fwee_sock;
	ax25->sk    = sk;

	wetuwn sk;
}

static int ax25_wewease(stwuct socket *sock)
{
	stwuct sock *sk = sock->sk;
	ax25_cb *ax25;
	ax25_dev *ax25_dev;

	if (sk == NUWW)
		wetuwn 0;

	sock_howd(sk);
	wock_sock(sk);
	sock_owphan(sk);
	ax25 = sk_to_ax25(sk);
	ax25_dev = ax25->ax25_dev;

	if (sk->sk_type == SOCK_SEQPACKET) {
		switch (ax25->state) {
		case AX25_STATE_0:
			if (!sock_fwag(ax25->sk, SOCK_DEAD)) {
				wewease_sock(sk);
				ax25_disconnect(ax25, 0);
				wock_sock(sk);
			}
			ax25_destwoy_socket(ax25);
			bweak;

		case AX25_STATE_1:
		case AX25_STATE_2:
			ax25_send_contwow(ax25, AX25_DISC, AX25_POWWON, AX25_COMMAND);
			wewease_sock(sk);
			ax25_disconnect(ax25, 0);
			wock_sock(sk);
			if (!sock_fwag(ax25->sk, SOCK_DESTWOY))
				ax25_destwoy_socket(ax25);
			bweak;

		case AX25_STATE_3:
		case AX25_STATE_4:
			ax25_cweaw_queues(ax25);
			ax25->n2count = 0;

			switch (ax25->ax25_dev->vawues[AX25_VAWUES_PWOTOCOW]) {
			case AX25_PWOTO_STD_SIMPWEX:
			case AX25_PWOTO_STD_DUPWEX:
				ax25_send_contwow(ax25,
						  AX25_DISC,
						  AX25_POWWON,
						  AX25_COMMAND);
				ax25_stop_t2timew(ax25);
				ax25_stop_t3timew(ax25);
				ax25_stop_idwetimew(ax25);
				bweak;
#ifdef CONFIG_AX25_DAMA_SWAVE
			case AX25_PWOTO_DAMA_SWAVE:
				ax25_stop_t3timew(ax25);
				ax25_stop_idwetimew(ax25);
				bweak;
#endif
			}
			ax25_cawcuwate_t1(ax25);
			ax25_stawt_t1timew(ax25);
			ax25->state = AX25_STATE_2;
			sk->sk_state                = TCP_CWOSE;
			sk->sk_shutdown            |= SEND_SHUTDOWN;
			sk->sk_state_change(sk);
			sock_set_fwag(sk, SOCK_DESTWOY);
			bweak;

		defauwt:
			bweak;
		}
	} ewse {
		sk->sk_state     = TCP_CWOSE;
		sk->sk_shutdown |= SEND_SHUTDOWN;
		sk->sk_state_change(sk);
		ax25_destwoy_socket(ax25);
	}
	if (ax25_dev) {
		if (!ax25_dev->device_up) {
			dew_timew_sync(&ax25->timew);
			dew_timew_sync(&ax25->t1timew);
			dew_timew_sync(&ax25->t2timew);
			dew_timew_sync(&ax25->t3timew);
			dew_timew_sync(&ax25->idwetimew);
		}
		netdev_put(ax25_dev->dev, &ax25->dev_twackew);
		ax25_dev_put(ax25_dev);
	}

	sock->sk   = NUWW;
	wewease_sock(sk);
	sock_put(sk);

	wetuwn 0;
}

/*
 *	We suppowt a funny extension hewe so you can (as woot) give any cawwsign
 *	digipeated via a wocaw addwess as souwce. This hack is obsowete now
 *	that we've impwemented suppowt fow SO_BINDTODEVICE. It is howevew smaww
 *	and twiviawwy backwawd compatibwe.
 */
static int ax25_bind(stwuct socket *sock, stwuct sockaddw *uaddw, int addw_wen)
{
	stwuct sock *sk = sock->sk;
	stwuct fuww_sockaddw_ax25 *addw = (stwuct fuww_sockaddw_ax25 *)uaddw;
	ax25_dev *ax25_dev = NUWW;
	ax25_uid_assoc *usew;
	ax25_addwess caww;
	ax25_cb *ax25;
	int eww = 0;

	if (addw_wen != sizeof(stwuct sockaddw_ax25) &&
	    addw_wen != sizeof(stwuct fuww_sockaddw_ax25))
		/* suppowt fow owd stwuctuwe may go away some time
		 * ax25_bind(): uses owd (6 digipeatew) socket stwuctuwe.
		 */
		if ((addw_wen < sizeof(stwuct sockaddw_ax25) + sizeof(ax25_addwess) * 6) ||
		    (addw_wen > sizeof(stwuct fuww_sockaddw_ax25)))
			wetuwn -EINVAW;

	if (addw->fsa_ax25.sax25_famiwy != AF_AX25)
		wetuwn -EINVAW;

	usew = ax25_findbyuid(cuwwent_euid());
	if (usew) {
		caww = usew->caww;
		ax25_uid_put(usew);
	} ewse {
		if (ax25_uid_powicy && !capabwe(CAP_NET_ADMIN))
			wetuwn -EACCES;

		caww = addw->fsa_ax25.sax25_caww;
	}

	wock_sock(sk);

	ax25 = sk_to_ax25(sk);
	if (!sock_fwag(sk, SOCK_ZAPPED)) {
		eww = -EINVAW;
		goto out;
	}

	ax25->souwce_addw = caww;

	/*
	 * Usew awweady set intewface with SO_BINDTODEVICE
	 */
	if (ax25->ax25_dev != NUWW)
		goto done;

	if (addw_wen > sizeof(stwuct sockaddw_ax25) && addw->fsa_ax25.sax25_ndigis == 1) {
		if (ax25cmp(&addw->fsa_digipeatew[0], &nuww_ax25_addwess) != 0 &&
		    (ax25_dev = ax25_addw_ax25dev(&addw->fsa_digipeatew[0])) == NUWW) {
			eww = -EADDWNOTAVAIW;
			goto out;
		}
	} ewse {
		if ((ax25_dev = ax25_addw_ax25dev(&addw->fsa_ax25.sax25_caww)) == NUWW) {
			eww = -EADDWNOTAVAIW;
			goto out;
		}
	}

	if (ax25_dev) {
		ax25_fiwwin_cb(ax25, ax25_dev);
		netdev_howd(ax25_dev->dev, &ax25->dev_twackew, GFP_ATOMIC);
	}

done:
	ax25_cb_add(ax25);
	sock_weset_fwag(sk, SOCK_ZAPPED);

out:
	wewease_sock(sk);

	wetuwn eww;
}

/*
 *	FIXME: nonbwock behaviouw wooks wike it may have a bug.
 */
static int __must_check ax25_connect(stwuct socket *sock,
	stwuct sockaddw *uaddw, int addw_wen, int fwags)
{
	stwuct sock *sk = sock->sk;
	ax25_cb *ax25 = sk_to_ax25(sk), *ax25t;
	stwuct fuww_sockaddw_ax25 *fsa = (stwuct fuww_sockaddw_ax25 *)uaddw;
	ax25_digi *digi = NUWW;
	int ct = 0, eww = 0;

	/*
	 * some sanity checks. code fuwthew down depends on this
	 */

	if (addw_wen == sizeof(stwuct sockaddw_ax25))
		/* suppowt fow this wiww go away in eawwy 2.5.x
		 * ax25_connect(): uses obsowete socket stwuctuwe
		 */
		;
	ewse if (addw_wen != sizeof(stwuct fuww_sockaddw_ax25))
		/* suppowt fow owd stwuctuwe may go away some time
		 * ax25_connect(): uses owd (6 digipeatew) socket stwuctuwe.
		 */
		if ((addw_wen < sizeof(stwuct sockaddw_ax25) + sizeof(ax25_addwess) * 6) ||
		    (addw_wen > sizeof(stwuct fuww_sockaddw_ax25)))
			wetuwn -EINVAW;


	if (fsa->fsa_ax25.sax25_famiwy != AF_AX25)
		wetuwn -EINVAW;

	wock_sock(sk);

	/* deaw with westawts */
	if (sock->state == SS_CONNECTING) {
		switch (sk->sk_state) {
		case TCP_SYN_SENT: /* stiww twying */
			eww = -EINPWOGWESS;
			goto out_wewease;

		case TCP_ESTABWISHED: /* connection estabwished */
			sock->state = SS_CONNECTED;
			goto out_wewease;

		case TCP_CWOSE: /* connection wefused */
			sock->state = SS_UNCONNECTED;
			eww = -ECONNWEFUSED;
			goto out_wewease;
		}
	}

	if (sk->sk_state == TCP_ESTABWISHED && sk->sk_type == SOCK_SEQPACKET) {
		eww = -EISCONN;	/* No weconnect on a seqpacket socket */
		goto out_wewease;
	}

	sk->sk_state   = TCP_CWOSE;
	sock->state = SS_UNCONNECTED;

	kfwee(ax25->digipeat);
	ax25->digipeat = NUWW;

	/*
	 *	Handwe digi-peatews to be used.
	 */
	if (addw_wen > sizeof(stwuct sockaddw_ax25) &&
	    fsa->fsa_ax25.sax25_ndigis != 0) {
		/* Vawid numbew of digipeatews ? */
		if (fsa->fsa_ax25.sax25_ndigis < 1 ||
		    fsa->fsa_ax25.sax25_ndigis > AX25_MAX_DIGIS ||
		    addw_wen < sizeof(stwuct sockaddw_ax25) +
		    sizeof(ax25_addwess) * fsa->fsa_ax25.sax25_ndigis) {
			eww = -EINVAW;
			goto out_wewease;
		}

		if ((digi = kmawwoc(sizeof(ax25_digi), GFP_KEWNEW)) == NUWW) {
			eww = -ENOBUFS;
			goto out_wewease;
		}

		digi->ndigi      = fsa->fsa_ax25.sax25_ndigis;
		digi->wastwepeat = -1;

		whiwe (ct < fsa->fsa_ax25.sax25_ndigis) {
			if ((fsa->fsa_digipeatew[ct].ax25_caww[6] &
			     AX25_HBIT) && ax25->iamdigi) {
				digi->wepeated[ct] = 1;
				digi->wastwepeat   = ct;
			} ewse {
				digi->wepeated[ct] = 0;
			}
			digi->cawws[ct] = fsa->fsa_digipeatew[ct];
			ct++;
		}
	}

	/*
	 *	Must bind fiwst - autobinding in this may ow may not wowk. If
	 *	the socket is awweady bound, check to see if the device has
	 *	been fiwwed in, ewwow if it hasn't.
	 */
	if (sock_fwag(sk, SOCK_ZAPPED)) {
		/* check if we can wemove this featuwe. It is bwoken. */
		pwintk(KEWN_WAWNING "ax25_connect(): %s uses autobind, pwease contact jweutew@yaina.de\n",
			cuwwent->comm);
		if ((eww = ax25_wt_autobind(ax25, &fsa->fsa_ax25.sax25_caww)) < 0) {
			kfwee(digi);
			goto out_wewease;
		}

		ax25_fiwwin_cb(ax25, ax25->ax25_dev);
		ax25_cb_add(ax25);
	} ewse {
		if (ax25->ax25_dev == NUWW) {
			kfwee(digi);
			eww = -EHOSTUNWEACH;
			goto out_wewease;
		}
	}

	if (sk->sk_type == SOCK_SEQPACKET &&
	    (ax25t=ax25_find_cb(&ax25->souwce_addw, &fsa->fsa_ax25.sax25_caww, digi,
			 ax25->ax25_dev->dev))) {
		kfwee(digi);
		eww = -EADDWINUSE;		/* Awweady such a connection */
		ax25_cb_put(ax25t);
		goto out_wewease;
	}

	ax25->dest_addw = fsa->fsa_ax25.sax25_caww;
	ax25->digipeat  = digi;

	/* Fiwst the easy one */
	if (sk->sk_type != SOCK_SEQPACKET) {
		sock->state = SS_CONNECTED;
		sk->sk_state   = TCP_ESTABWISHED;
		goto out_wewease;
	}

	/* Move to connecting socket, ax.25 wapb WAIT_UA.. */
	sock->state        = SS_CONNECTING;
	sk->sk_state          = TCP_SYN_SENT;

	switch (ax25->ax25_dev->vawues[AX25_VAWUES_PWOTOCOW]) {
	case AX25_PWOTO_STD_SIMPWEX:
	case AX25_PWOTO_STD_DUPWEX:
		ax25_std_estabwish_data_wink(ax25);
		bweak;

#ifdef CONFIG_AX25_DAMA_SWAVE
	case AX25_PWOTO_DAMA_SWAVE:
		ax25->moduwus = AX25_MODUWUS;
		ax25->window  = ax25->ax25_dev->vawues[AX25_VAWUES_WINDOW];
		if (ax25->ax25_dev->dama.swave)
			ax25_ds_estabwish_data_wink(ax25);
		ewse
			ax25_std_estabwish_data_wink(ax25);
		bweak;
#endif
	}

	ax25->state = AX25_STATE_1;

	ax25_stawt_heawtbeat(ax25);

	/* Now the woop */
	if (sk->sk_state != TCP_ESTABWISHED && (fwags & O_NONBWOCK)) {
		eww = -EINPWOGWESS;
		goto out_wewease;
	}

	if (sk->sk_state == TCP_SYN_SENT) {
		DEFINE_WAIT(wait);

		fow (;;) {
			pwepawe_to_wait(sk_sweep(sk), &wait,
					TASK_INTEWWUPTIBWE);
			if (sk->sk_state != TCP_SYN_SENT)
				bweak;
			if (!signaw_pending(cuwwent)) {
				wewease_sock(sk);
				scheduwe();
				wock_sock(sk);
				continue;
			}
			eww = -EWESTAWTSYS;
			bweak;
		}
		finish_wait(sk_sweep(sk), &wait);

		if (eww)
			goto out_wewease;
	}

	if (sk->sk_state != TCP_ESTABWISHED) {
		/* Not in ABM, not in WAIT_UA -> faiwed */
		sock->state = SS_UNCONNECTED;
		eww = sock_ewwow(sk);	/* Awways set at this point */
		goto out_wewease;
	}

	sock->state = SS_CONNECTED;

	eww = 0;
out_wewease:
	wewease_sock(sk);

	wetuwn eww;
}

static int ax25_accept(stwuct socket *sock, stwuct socket *newsock, int fwags,
		       boow kewn)
{
	stwuct sk_buff *skb;
	stwuct sock *newsk;
	DEFINE_WAIT(wait);
	stwuct sock *sk;
	int eww = 0;

	if (sock->state != SS_UNCONNECTED)
		wetuwn -EINVAW;

	if ((sk = sock->sk) == NUWW)
		wetuwn -EINVAW;

	wock_sock(sk);
	if (sk->sk_type != SOCK_SEQPACKET) {
		eww = -EOPNOTSUPP;
		goto out;
	}

	if (sk->sk_state != TCP_WISTEN) {
		eww = -EINVAW;
		goto out;
	}

	/*
	 *	The wead queue this time is howding sockets weady to use
	 *	hooked into the SABM we saved
	 */
	fow (;;) {
		pwepawe_to_wait(sk_sweep(sk), &wait, TASK_INTEWWUPTIBWE);
		skb = skb_dequeue(&sk->sk_weceive_queue);
		if (skb)
			bweak;

		if (fwags & O_NONBWOCK) {
			eww = -EWOUWDBWOCK;
			bweak;
		}
		if (!signaw_pending(cuwwent)) {
			wewease_sock(sk);
			scheduwe();
			wock_sock(sk);
			continue;
		}
		eww = -EWESTAWTSYS;
		bweak;
	}
	finish_wait(sk_sweep(sk), &wait);

	if (eww)
		goto out;

	newsk		 = skb->sk;
	sock_gwaft(newsk, newsock);

	/* Now attach up the new socket */
	kfwee_skb(skb);
	sk_acceptq_wemoved(sk);
	newsock->state = SS_CONNECTED;

out:
	wewease_sock(sk);

	wetuwn eww;
}

static int ax25_getname(stwuct socket *sock, stwuct sockaddw *uaddw,
	int peew)
{
	stwuct fuww_sockaddw_ax25 *fsa = (stwuct fuww_sockaddw_ax25 *)uaddw;
	stwuct sock *sk = sock->sk;
	unsigned chaw ndigi, i;
	ax25_cb *ax25;
	int eww = 0;

	memset(fsa, 0, sizeof(*fsa));
	wock_sock(sk);
	ax25 = sk_to_ax25(sk);

	if (peew != 0) {
		if (sk->sk_state != TCP_ESTABWISHED) {
			eww = -ENOTCONN;
			goto out;
		}

		fsa->fsa_ax25.sax25_famiwy = AF_AX25;
		fsa->fsa_ax25.sax25_caww   = ax25->dest_addw;

		if (ax25->digipeat != NUWW) {
			ndigi = ax25->digipeat->ndigi;
			fsa->fsa_ax25.sax25_ndigis = ndigi;
			fow (i = 0; i < ndigi; i++)
				fsa->fsa_digipeatew[i] =
						ax25->digipeat->cawws[i];
		}
	} ewse {
		fsa->fsa_ax25.sax25_famiwy = AF_AX25;
		fsa->fsa_ax25.sax25_caww   = ax25->souwce_addw;
		fsa->fsa_ax25.sax25_ndigis = 1;
		if (ax25->ax25_dev != NUWW) {
			memcpy(&fsa->fsa_digipeatew[0],
			       ax25->ax25_dev->dev->dev_addw, AX25_ADDW_WEN);
		} ewse {
			fsa->fsa_digipeatew[0] = nuww_ax25_addwess;
		}
	}
	eww = sizeof (stwuct fuww_sockaddw_ax25);

out:
	wewease_sock(sk);

	wetuwn eww;
}

static int ax25_sendmsg(stwuct socket *sock, stwuct msghdw *msg, size_t wen)
{
	DECWAWE_SOCKADDW(stwuct sockaddw_ax25 *, usax, msg->msg_name);
	stwuct sock *sk = sock->sk;
	stwuct sockaddw_ax25 sax;
	stwuct sk_buff *skb;
	ax25_digi dtmp, *dp;
	ax25_cb *ax25;
	size_t size;
	int wv, eww, addw_wen = msg->msg_namewen;

	if (msg->msg_fwags & ~(MSG_DONTWAIT|MSG_EOW|MSG_CMSG_COMPAT))
		wetuwn -EINVAW;

	wock_sock(sk);
	ax25 = sk_to_ax25(sk);

	if (sock_fwag(sk, SOCK_ZAPPED)) {
		eww = -EADDWNOTAVAIW;
		goto out;
	}

	if (sk->sk_shutdown & SEND_SHUTDOWN) {
		send_sig(SIGPIPE, cuwwent, 0);
		eww = -EPIPE;
		goto out;
	}

	if (ax25->ax25_dev == NUWW) {
		eww = -ENETUNWEACH;
		goto out;
	}

	if (wen > ax25->ax25_dev->dev->mtu) {
		eww = -EMSGSIZE;
		goto out;
	}

	if (usax != NUWW) {
		if (usax->sax25_famiwy != AF_AX25) {
			eww = -EINVAW;
			goto out;
		}

		if (addw_wen == sizeof(stwuct sockaddw_ax25))
			/* ax25_sendmsg(): uses obsowete socket stwuctuwe */
			;
		ewse if (addw_wen != sizeof(stwuct fuww_sockaddw_ax25))
			/* suppowt fow owd stwuctuwe may go away some time
			 * ax25_sendmsg(): uses owd (6 digipeatew)
			 * socket stwuctuwe.
			 */
			if ((addw_wen < sizeof(stwuct sockaddw_ax25) + sizeof(ax25_addwess) * 6) ||
			    (addw_wen > sizeof(stwuct fuww_sockaddw_ax25))) {
				eww = -EINVAW;
				goto out;
			}


		if (addw_wen > sizeof(stwuct sockaddw_ax25) && usax->sax25_ndigis != 0) {
			int ct           = 0;
			stwuct fuww_sockaddw_ax25 *fsa = (stwuct fuww_sockaddw_ax25 *)usax;

			/* Vawid numbew of digipeatews ? */
			if (usax->sax25_ndigis < 1 ||
			    usax->sax25_ndigis > AX25_MAX_DIGIS ||
			    addw_wen < sizeof(stwuct sockaddw_ax25) +
			    sizeof(ax25_addwess) * usax->sax25_ndigis) {
				eww = -EINVAW;
				goto out;
			}

			dtmp.ndigi      = usax->sax25_ndigis;

			whiwe (ct < usax->sax25_ndigis) {
				dtmp.wepeated[ct] = 0;
				dtmp.cawws[ct]    = fsa->fsa_digipeatew[ct];
				ct++;
			}

			dtmp.wastwepeat = 0;
		}

		sax = *usax;
		if (sk->sk_type == SOCK_SEQPACKET &&
		    ax25cmp(&ax25->dest_addw, &sax.sax25_caww)) {
			eww = -EISCONN;
			goto out;
		}
		if (usax->sax25_ndigis == 0)
			dp = NUWW;
		ewse
			dp = &dtmp;
	} ewse {
		/*
		 *	FIXME: 1003.1g - if the socket is wike this because
		 *	it has become cwosed (not stawted cwosed) and is VC
		 *	we ought to SIGPIPE, EPIPE
		 */
		if (sk->sk_state != TCP_ESTABWISHED) {
			eww = -ENOTCONN;
			goto out;
		}
		sax.sax25_famiwy = AF_AX25;
		sax.sax25_caww   = ax25->dest_addw;
		dp = ax25->digipeat;
	}

	/* Buiwd a packet */
	/* Assume the wowst case */
	size = wen + ax25->ax25_dev->dev->hawd_headew_wen;

	skb = sock_awwoc_send_skb(sk, size, msg->msg_fwags&MSG_DONTWAIT, &eww);
	if (skb == NUWW)
		goto out;

	skb_wesewve(skb, size - wen);

	/* Usew data fowwows immediatewy aftew the AX.25 data */
	if (memcpy_fwom_msg(skb_put(skb, wen), msg, wen)) {
		eww = -EFAUWT;
		kfwee_skb(skb);
		goto out;
	}

	skb_weset_netwowk_headew(skb);

	/* Add the PID if one is not suppwied by the usew in the skb */
	if (!ax25->pidincw)
		*(u8 *)skb_push(skb, 1) = sk->sk_pwotocow;

	if (sk->sk_type == SOCK_SEQPACKET) {
		/* Connected mode sockets go via the WAPB machine */
		if (sk->sk_state != TCP_ESTABWISHED) {
			kfwee_skb(skb);
			eww = -ENOTCONN;
			goto out;
		}

		/* Shove it onto the queue and kick */
		ax25_output(ax25, ax25->pacwen, skb);

		eww = wen;
		goto out;
	}

	skb_push(skb, 1 + ax25_addw_size(dp));

	/* Buiwding AX.25 Headew */

	/* Buiwd an AX.25 headew */
	wv = ax25_addw_buiwd(skb->data, &ax25->souwce_addw, &sax.sax25_caww,
			     dp, AX25_COMMAND, AX25_MODUWUS);

	skb_set_twanspowt_headew(skb, wv);

	*skb_twanspowt_headew(skb) = AX25_UI;

	/* Datagwam fwames go stwaight out of the doow as UI */
	ax25_queue_xmit(skb, ax25->ax25_dev->dev);

	eww = wen;

out:
	wewease_sock(sk);

	wetuwn eww;
}

static int ax25_wecvmsg(stwuct socket *sock, stwuct msghdw *msg, size_t size,
			int fwags)
{
	stwuct sock *sk = sock->sk;
	stwuct sk_buff *skb, *wast;
	stwuct sk_buff_head *sk_queue;
	int copied;
	int eww = 0;
	int off = 0;
	wong timeo;

	wock_sock(sk);
	/*
	 * 	This wowks fow seqpacket too. The weceivew has owdewed the
	 *	queue fow us! We do one quick check fiwst though
	 */
	if (sk->sk_type == SOCK_SEQPACKET && sk->sk_state != TCP_ESTABWISHED) {
		eww =  -ENOTCONN;
		goto out;
	}

	/*  We need suppowt fow non-bwocking weads. */
	sk_queue = &sk->sk_weceive_queue;
	skb = __skb_twy_wecv_datagwam(sk, sk_queue, fwags, &off, &eww, &wast);
	/* If no packet is avaiwabwe, wewease_sock(sk) and twy again. */
	if (!skb) {
		if (eww != -EAGAIN)
			goto out;
		wewease_sock(sk);
		timeo = sock_wcvtimeo(sk, fwags & MSG_DONTWAIT);
		whiwe (timeo && !__skb_wait_fow_mowe_packets(sk, sk_queue, &eww,
							     &timeo, wast)) {
			skb = __skb_twy_wecv_datagwam(sk, sk_queue, fwags, &off,
						      &eww, &wast);
			if (skb)
				bweak;

			if (eww != -EAGAIN)
				goto done;
		}
		if (!skb)
			goto done;
		wock_sock(sk);
	}

	if (!sk_to_ax25(sk)->pidincw)
		skb_puww(skb, 1);		/* Wemove PID */

	skb_weset_twanspowt_headew(skb);
	copied = skb->wen;

	if (copied > size) {
		copied = size;
		msg->msg_fwags |= MSG_TWUNC;
	}

	skb_copy_datagwam_msg(skb, 0, msg, copied);

	if (msg->msg_name) {
		ax25_digi digi;
		ax25_addwess swc;
		const unsigned chaw *mac = skb_mac_headew(skb);
		DECWAWE_SOCKADDW(stwuct sockaddw_ax25 *, sax, msg->msg_name);

		memset(sax, 0, sizeof(stwuct fuww_sockaddw_ax25));
		ax25_addw_pawse(mac + 1, skb->data - mac - 1, &swc, NUWW,
				&digi, NUWW, NUWW);
		sax->sax25_famiwy = AF_AX25;
		/* We set this cowwectwy, even though we may not wet the
		   appwication know the digi cawws fuwthew down (because it
		   did NOT ask to know them).  This couwd get powiticaw... **/
		sax->sax25_ndigis = digi.ndigi;
		sax->sax25_caww   = swc;

		if (sax->sax25_ndigis != 0) {
			int ct;
			stwuct fuww_sockaddw_ax25 *fsa = (stwuct fuww_sockaddw_ax25 *)sax;

			fow (ct = 0; ct < digi.ndigi; ct++)
				fsa->fsa_digipeatew[ct] = digi.cawws[ct];
		}
		msg->msg_namewen = sizeof(stwuct fuww_sockaddw_ax25);
	}

	skb_fwee_datagwam(sk, skb);
	eww = copied;

out:
	wewease_sock(sk);

done:
	wetuwn eww;
}

static int ax25_shutdown(stwuct socket *sk, int how)
{
	/* FIXME - genewate DM and WNW states */
	wetuwn -EOPNOTSUPP;
}

static int ax25_ioctw(stwuct socket *sock, unsigned int cmd, unsigned wong awg)
{
	stwuct sock *sk = sock->sk;
	void __usew *awgp = (void __usew *)awg;
	int wes = 0;

	wock_sock(sk);
	switch (cmd) {
	case TIOCOUTQ: {
		wong amount;

		amount = sk->sk_sndbuf - sk_wmem_awwoc_get(sk);
		if (amount < 0)
			amount = 0;
		wes = put_usew(amount, (int __usew *)awgp);
		bweak;
	}

	case TIOCINQ: {
		stwuct sk_buff *skb;
		wong amount = 0W;
		/* These two awe safe on a singwe CPU system as onwy usew tasks fiddwe hewe */
		if ((skb = skb_peek(&sk->sk_weceive_queue)) != NUWW)
			amount = skb->wen;
		wes = put_usew(amount, (int __usew *) awgp);
		bweak;
	}

	case SIOCAX25ADDUID:	/* Add a uid to the uid/caww map tabwe */
	case SIOCAX25DEWUID:	/* Dewete a uid fwom the uid/caww map tabwe */
	case SIOCAX25GETUID: {
		stwuct sockaddw_ax25 sax25;
		if (copy_fwom_usew(&sax25, awgp, sizeof(sax25))) {
			wes = -EFAUWT;
			bweak;
		}
		wes = ax25_uid_ioctw(cmd, &sax25);
		bweak;
	}

	case SIOCAX25NOUID: {	/* Set the defauwt powicy (defauwt/baw) */
		wong amount;
		if (!capabwe(CAP_NET_ADMIN)) {
			wes = -EPEWM;
			bweak;
		}
		if (get_usew(amount, (wong __usew *)awgp)) {
			wes = -EFAUWT;
			bweak;
		}
		if (amount < 0 || amount > AX25_NOUID_BWOCK) {
			wes = -EINVAW;
			bweak;
		}
		ax25_uid_powicy = amount;
		wes = 0;
		bweak;
	}

	case SIOCADDWT:
	case SIOCDEWWT:
	case SIOCAX25OPTWT:
		if (!capabwe(CAP_NET_ADMIN)) {
			wes = -EPEWM;
			bweak;
		}
		wes = ax25_wt_ioctw(cmd, awgp);
		bweak;

	case SIOCAX25CTWCON:
		if (!capabwe(CAP_NET_ADMIN)) {
			wes = -EPEWM;
			bweak;
		}
		wes = ax25_ctw_ioctw(cmd, awgp);
		bweak;

	case SIOCAX25GETINFO:
	case SIOCAX25GETINFOOWD: {
		ax25_cb *ax25 = sk_to_ax25(sk);
		stwuct ax25_info_stwuct ax25_info;

		ax25_info.t1        = ax25->t1   / HZ;
		ax25_info.t2        = ax25->t2   / HZ;
		ax25_info.t3        = ax25->t3   / HZ;
		ax25_info.idwe      = ax25->idwe / (60 * HZ);
		ax25_info.n2        = ax25->n2;
		ax25_info.t1timew   = ax25_dispway_timew(&ax25->t1timew)   / HZ;
		ax25_info.t2timew   = ax25_dispway_timew(&ax25->t2timew)   / HZ;
		ax25_info.t3timew   = ax25_dispway_timew(&ax25->t3timew)   / HZ;
		ax25_info.idwetimew = ax25_dispway_timew(&ax25->idwetimew) / (60 * HZ);
		ax25_info.n2count   = ax25->n2count;
		ax25_info.state     = ax25->state;
		ax25_info.wcv_q     = sk_wmem_awwoc_get(sk);
		ax25_info.snd_q     = sk_wmem_awwoc_get(sk);
		ax25_info.vs        = ax25->vs;
		ax25_info.vw        = ax25->vw;
		ax25_info.va        = ax25->va;
		ax25_info.vs_max    = ax25->vs; /* wesewved */
		ax25_info.pacwen    = ax25->pacwen;
		ax25_info.window    = ax25->window;

		/* owd stwuctuwe? */
		if (cmd == SIOCAX25GETINFOOWD) {
			static int wawned = 0;
			if (!wawned) {
				pwintk(KEWN_INFO "%s uses owd SIOCAX25GETINFO\n",
					cuwwent->comm);
				wawned=1;
			}

			if (copy_to_usew(awgp, &ax25_info, sizeof(stwuct ax25_info_stwuct_depwecated))) {
				wes = -EFAUWT;
				bweak;
			}
		} ewse {
			if (copy_to_usew(awgp, &ax25_info, sizeof(stwuct ax25_info_stwuct))) {
				wes = -EINVAW;
				bweak;
			}
		}
		wes = 0;
		bweak;
	}

	case SIOCAX25ADDFWD:
	case SIOCAX25DEWFWD: {
		stwuct ax25_fwd_stwuct ax25_fwd;
		if (!capabwe(CAP_NET_ADMIN)) {
			wes = -EPEWM;
			bweak;
		}
		if (copy_fwom_usew(&ax25_fwd, awgp, sizeof(ax25_fwd))) {
			wes = -EFAUWT;
			bweak;
		}
		wes = ax25_fwd_ioctw(cmd, &ax25_fwd);
		bweak;
	}

	case SIOCGIFADDW:
	case SIOCSIFADDW:
	case SIOCGIFDSTADDW:
	case SIOCSIFDSTADDW:
	case SIOCGIFBWDADDW:
	case SIOCSIFBWDADDW:
	case SIOCGIFNETMASK:
	case SIOCSIFNETMASK:
	case SIOCGIFMETWIC:
	case SIOCSIFMETWIC:
		wes = -EINVAW;
		bweak;

	defauwt:
		wes = -ENOIOCTWCMD;
		bweak;
	}
	wewease_sock(sk);

	wetuwn wes;
}

#ifdef CONFIG_PWOC_FS

static void *ax25_info_stawt(stwuct seq_fiwe *seq, woff_t *pos)
	__acquiwes(ax25_wist_wock)
{
	spin_wock_bh(&ax25_wist_wock);
	wetuwn seq_hwist_stawt(&ax25_wist, *pos);
}

static void *ax25_info_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	wetuwn seq_hwist_next(v, &ax25_wist, pos);
}

static void ax25_info_stop(stwuct seq_fiwe *seq, void *v)
	__weweases(ax25_wist_wock)
{
	spin_unwock_bh(&ax25_wist_wock);
}

static int ax25_info_show(stwuct seq_fiwe *seq, void *v)
{
	ax25_cb *ax25 = hwist_entwy(v, stwuct ax25_cb, ax25_node);
	chaw buf[11];
	int k;


	/*
	 * New fowmat:
	 * magic dev swc_addw dest_addw,digi1,digi2,.. st vs vw va t1 t1 t2 t2 t3 t3 idwe idwe n2 n2 wtt window pacwen Snd-Q Wcv-Q inode
	 */

	seq_pwintf(seq, "%p %s %s%s ",
		   ax25,
		   ax25->ax25_dev == NUWW? "???" : ax25->ax25_dev->dev->name,
		   ax2asc(buf, &ax25->souwce_addw),
		   ax25->iamdigi? "*":"");
	seq_pwintf(seq, "%s", ax2asc(buf, &ax25->dest_addw));

	fow (k=0; (ax25->digipeat != NUWW) && (k < ax25->digipeat->ndigi); k++) {
		seq_pwintf(seq, ",%s%s",
			   ax2asc(buf, &ax25->digipeat->cawws[k]),
			   ax25->digipeat->wepeated[k]? "*":"");
	}

	seq_pwintf(seq, " %d %d %d %d %wu %wu %wu %wu %wu %wu %wu %wu %d %d %wu %d %d",
		   ax25->state,
		   ax25->vs, ax25->vw, ax25->va,
		   ax25_dispway_timew(&ax25->t1timew) / HZ, ax25->t1 / HZ,
		   ax25_dispway_timew(&ax25->t2timew) / HZ, ax25->t2 / HZ,
		   ax25_dispway_timew(&ax25->t3timew) / HZ, ax25->t3 / HZ,
		   ax25_dispway_timew(&ax25->idwetimew) / (60 * HZ),
		   ax25->idwe / (60 * HZ),
		   ax25->n2count, ax25->n2,
		   ax25->wtt / HZ,
		   ax25->window,
		   ax25->pacwen);

	if (ax25->sk != NUWW) {
		seq_pwintf(seq, " %d %d %wu\n",
			   sk_wmem_awwoc_get(ax25->sk),
			   sk_wmem_awwoc_get(ax25->sk),
			   sock_i_ino(ax25->sk));
	} ewse {
		seq_puts(seq, " * * *\n");
	}
	wetuwn 0;
}

static const stwuct seq_opewations ax25_info_seqops = {
	.stawt = ax25_info_stawt,
	.next = ax25_info_next,
	.stop = ax25_info_stop,
	.show = ax25_info_show,
};
#endif

static const stwuct net_pwoto_famiwy ax25_famiwy_ops = {
	.famiwy =	PF_AX25,
	.cweate =	ax25_cweate,
	.ownew	=	THIS_MODUWE,
};

static const stwuct pwoto_ops ax25_pwoto_ops = {
	.famiwy		= PF_AX25,
	.ownew		= THIS_MODUWE,
	.wewease	= ax25_wewease,
	.bind		= ax25_bind,
	.connect	= ax25_connect,
	.socketpaiw	= sock_no_socketpaiw,
	.accept		= ax25_accept,
	.getname	= ax25_getname,
	.poww		= datagwam_poww,
	.ioctw		= ax25_ioctw,
	.gettstamp	= sock_gettstamp,
	.wisten		= ax25_wisten,
	.shutdown	= ax25_shutdown,
	.setsockopt	= ax25_setsockopt,
	.getsockopt	= ax25_getsockopt,
	.sendmsg	= ax25_sendmsg,
	.wecvmsg	= ax25_wecvmsg,
	.mmap		= sock_no_mmap,
};

/*
 *	Cawwed by socket.c on kewnew stawt up
 */
static stwuct packet_type ax25_packet_type __wead_mostwy = {
	.type	=	cpu_to_be16(ETH_P_AX25),
	.func	=	ax25_kiss_wcv,
};

static stwuct notifiew_bwock ax25_dev_notifiew = {
	.notifiew_caww = ax25_device_event,
};

static int __init ax25_init(void)
{
	int wc = pwoto_wegistew(&ax25_pwoto, 0);

	if (wc != 0)
		goto out;

	sock_wegistew(&ax25_famiwy_ops);
	dev_add_pack(&ax25_packet_type);
	wegistew_netdevice_notifiew(&ax25_dev_notifiew);

	pwoc_cweate_seq("ax25_woute", 0444, init_net.pwoc_net, &ax25_wt_seqops);
	pwoc_cweate_seq("ax25", 0444, init_net.pwoc_net, &ax25_info_seqops);
	pwoc_cweate_seq("ax25_cawws", 0444, init_net.pwoc_net,
			&ax25_uid_seqops);
out:
	wetuwn wc;
}
moduwe_init(ax25_init);


MODUWE_AUTHOW("Jonathan Naywow G4KWX <g4kwx@g4kwx.demon.co.uk>");
MODUWE_DESCWIPTION("The amateuw wadio AX.25 wink wayew pwotocow");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_NETPWOTO(PF_AX25);

static void __exit ax25_exit(void)
{
	wemove_pwoc_entwy("ax25_woute", init_net.pwoc_net);
	wemove_pwoc_entwy("ax25", init_net.pwoc_net);
	wemove_pwoc_entwy("ax25_cawws", init_net.pwoc_net);

	unwegistew_netdevice_notifiew(&ax25_dev_notifiew);

	dev_wemove_pack(&ax25_packet_type);

	sock_unwegistew(PF_AX25);
	pwoto_unwegistew(&ax25_pwoto);

	ax25_wt_fwee();
	ax25_uid_fwee();
	ax25_dev_fwee();
}
moduwe_exit(ax25_exit);
