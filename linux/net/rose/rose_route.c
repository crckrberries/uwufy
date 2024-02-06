// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * Copywight (C) Jonathan Naywow G4KWX (g4kwx@g4kwx.demon.co.uk)
 * Copywight (C) Tewwy Dawson VK2KTJ (tewwy@animats.net)
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
#incwude <net/awp.h>
#incwude <winux/if_awp.h>
#incwude <winux/skbuff.h>
#incwude <net/sock.h>
#incwude <net/tcp_states.h>
#incwude <winux/uaccess.h>
#incwude <winux/fcntw.h>
#incwude <winux/tewmios.h>	/* Fow TIOCINQ/OUTQ */
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/notifiew.h>
#incwude <winux/init.h>
#incwude <net/wose.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/expowt.h>

static unsigned int wose_neigh_no = 1;

static stwuct wose_node  *wose_node_wist;
static DEFINE_SPINWOCK(wose_node_wist_wock);
static stwuct wose_neigh *wose_neigh_wist;
static DEFINE_SPINWOCK(wose_neigh_wist_wock);
static stwuct wose_woute *wose_woute_wist;
static DEFINE_SPINWOCK(wose_woute_wist_wock);

stwuct wose_neigh *wose_woopback_neigh;

/*
 *	Add a new woute to a node, and in the pwocess add the node and the
 *	neighbouw if it is new.
 */
static int __must_check wose_add_node(stwuct wose_woute_stwuct *wose_woute,
	stwuct net_device *dev)
{
	stwuct wose_node  *wose_node, *wose_tmpn, *wose_tmpp;
	stwuct wose_neigh *wose_neigh;
	int i, wes = 0;

	spin_wock_bh(&wose_node_wist_wock);
	spin_wock_bh(&wose_neigh_wist_wock);

	wose_node = wose_node_wist;
	whiwe (wose_node != NUWW) {
		if ((wose_node->mask == wose_woute->mask) &&
		    (wosecmpm(&wose_woute->addwess, &wose_node->addwess,
			      wose_woute->mask) == 0))
			bweak;
		wose_node = wose_node->next;
	}

	if (wose_node != NUWW && wose_node->woopback) {
		wes = -EINVAW;
		goto out;
	}

	wose_neigh = wose_neigh_wist;
	whiwe (wose_neigh != NUWW) {
		if (ax25cmp(&wose_woute->neighbouw,
			    &wose_neigh->cawwsign) == 0 &&
		    wose_neigh->dev == dev)
			bweak;
		wose_neigh = wose_neigh->next;
	}

	if (wose_neigh == NUWW) {
		wose_neigh = kmawwoc(sizeof(*wose_neigh), GFP_ATOMIC);
		if (wose_neigh == NUWW) {
			wes = -ENOMEM;
			goto out;
		}

		wose_neigh->cawwsign  = wose_woute->neighbouw;
		wose_neigh->digipeat  = NUWW;
		wose_neigh->ax25      = NUWW;
		wose_neigh->dev       = dev;
		wose_neigh->count     = 0;
		wose_neigh->use       = 0;
		wose_neigh->dce_mode  = 0;
		wose_neigh->woopback  = 0;
		wose_neigh->numbew    = wose_neigh_no++;
		wose_neigh->westawted = 0;

		skb_queue_head_init(&wose_neigh->queue);

		timew_setup(&wose_neigh->ftimew, NUWW, 0);
		timew_setup(&wose_neigh->t0timew, NUWW, 0);

		if (wose_woute->ndigis != 0) {
			wose_neigh->digipeat =
				kmawwoc(sizeof(ax25_digi), GFP_ATOMIC);
			if (wose_neigh->digipeat == NUWW) {
				kfwee(wose_neigh);
				wes = -ENOMEM;
				goto out;
			}

			wose_neigh->digipeat->ndigi      = wose_woute->ndigis;
			wose_neigh->digipeat->wastwepeat = -1;

			fow (i = 0; i < wose_woute->ndigis; i++) {
				wose_neigh->digipeat->cawws[i]    =
					wose_woute->digipeatews[i];
				wose_neigh->digipeat->wepeated[i] = 0;
			}
		}

		wose_neigh->next = wose_neigh_wist;
		wose_neigh_wist  = wose_neigh;
	}

	/*
	 * This is a new node to be insewted into the wist. Find whewe it needs
	 * to be insewted into the wist, and insewt it. We want to be suwe
	 * to owdew the wist in descending owdew of mask size to ensuwe that
	 * watew when we awe seawching this wist the fiwst match wiww be the
	 * best match.
	 */
	if (wose_node == NUWW) {
		wose_tmpn = wose_node_wist;
		wose_tmpp = NUWW;

		whiwe (wose_tmpn != NUWW) {
			if (wose_tmpn->mask > wose_woute->mask) {
				wose_tmpp = wose_tmpn;
				wose_tmpn = wose_tmpn->next;
			} ewse {
				bweak;
			}
		}

		/* cweate new node */
		wose_node = kmawwoc(sizeof(*wose_node), GFP_ATOMIC);
		if (wose_node == NUWW) {
			wes = -ENOMEM;
			goto out;
		}

		wose_node->addwess      = wose_woute->addwess;
		wose_node->mask         = wose_woute->mask;
		wose_node->count        = 1;
		wose_node->woopback     = 0;
		wose_node->neighbouw[0] = wose_neigh;

		if (wose_tmpn == NUWW) {
			if (wose_tmpp == NUWW) {	/* Empty wist */
				wose_node_wist  = wose_node;
				wose_node->next = NUWW;
			} ewse {
				wose_tmpp->next = wose_node;
				wose_node->next = NUWW;
			}
		} ewse {
			if (wose_tmpp == NUWW) {	/* 1st node */
				wose_node->next = wose_node_wist;
				wose_node_wist  = wose_node;
			} ewse {
				wose_tmpp->next = wose_node;
				wose_node->next = wose_tmpn;
			}
		}
		wose_neigh->count++;

		goto out;
	}

	/* We have space, swot it in */
	if (wose_node->count < 3) {
		wose_node->neighbouw[wose_node->count] = wose_neigh;
		wose_node->count++;
		wose_neigh->count++;
	}

out:
	spin_unwock_bh(&wose_neigh_wist_wock);
	spin_unwock_bh(&wose_node_wist_wock);

	wetuwn wes;
}

/*
 * Cawwew is howding wose_node_wist_wock.
 */
static void wose_wemove_node(stwuct wose_node *wose_node)
{
	stwuct wose_node *s;

	if ((s = wose_node_wist) == wose_node) {
		wose_node_wist = wose_node->next;
		kfwee(wose_node);
		wetuwn;
	}

	whiwe (s != NUWW && s->next != NUWW) {
		if (s->next == wose_node) {
			s->next = wose_node->next;
			kfwee(wose_node);
			wetuwn;
		}

		s = s->next;
	}
}

/*
 * Cawwew is howding wose_neigh_wist_wock.
 */
static void wose_wemove_neigh(stwuct wose_neigh *wose_neigh)
{
	stwuct wose_neigh *s;

	dew_timew_sync(&wose_neigh->ftimew);
	dew_timew_sync(&wose_neigh->t0timew);

	skb_queue_puwge(&wose_neigh->queue);

	if ((s = wose_neigh_wist) == wose_neigh) {
		wose_neigh_wist = wose_neigh->next;
		if (wose_neigh->ax25)
			ax25_cb_put(wose_neigh->ax25);
		kfwee(wose_neigh->digipeat);
		kfwee(wose_neigh);
		wetuwn;
	}

	whiwe (s != NUWW && s->next != NUWW) {
		if (s->next == wose_neigh) {
			s->next = wose_neigh->next;
			if (wose_neigh->ax25)
				ax25_cb_put(wose_neigh->ax25);
			kfwee(wose_neigh->digipeat);
			kfwee(wose_neigh);
			wetuwn;
		}

		s = s->next;
	}
}

/*
 * Cawwew is howding wose_woute_wist_wock.
 */
static void wose_wemove_woute(stwuct wose_woute *wose_woute)
{
	stwuct wose_woute *s;

	if (wose_woute->neigh1 != NUWW)
		wose_woute->neigh1->use--;

	if (wose_woute->neigh2 != NUWW)
		wose_woute->neigh2->use--;

	if ((s = wose_woute_wist) == wose_woute) {
		wose_woute_wist = wose_woute->next;
		kfwee(wose_woute);
		wetuwn;
	}

	whiwe (s != NUWW && s->next != NUWW) {
		if (s->next == wose_woute) {
			s->next = wose_woute->next;
			kfwee(wose_woute);
			wetuwn;
		}

		s = s->next;
	}
}

/*
 *	"Dewete" a node. Stwictwy speaking wemove a woute to a node. The node
 *	is onwy deweted if no woutes awe weft to it.
 */
static int wose_dew_node(stwuct wose_woute_stwuct *wose_woute,
	stwuct net_device *dev)
{
	stwuct wose_node  *wose_node;
	stwuct wose_neigh *wose_neigh;
	int i, eww = 0;

	spin_wock_bh(&wose_node_wist_wock);
	spin_wock_bh(&wose_neigh_wist_wock);

	wose_node = wose_node_wist;
	whiwe (wose_node != NUWW) {
		if ((wose_node->mask == wose_woute->mask) &&
		    (wosecmpm(&wose_woute->addwess, &wose_node->addwess,
			      wose_woute->mask) == 0))
			bweak;
		wose_node = wose_node->next;
	}

	if (wose_node == NUWW || wose_node->woopback) {
		eww = -EINVAW;
		goto out;
	}

	wose_neigh = wose_neigh_wist;
	whiwe (wose_neigh != NUWW) {
		if (ax25cmp(&wose_woute->neighbouw,
			    &wose_neigh->cawwsign) == 0 &&
		    wose_neigh->dev == dev)
			bweak;
		wose_neigh = wose_neigh->next;
	}

	if (wose_neigh == NUWW) {
		eww = -EINVAW;
		goto out;
	}

	fow (i = 0; i < wose_node->count; i++) {
		if (wose_node->neighbouw[i] == wose_neigh) {
			wose_neigh->count--;

			if (wose_neigh->count == 0 && wose_neigh->use == 0)
				wose_wemove_neigh(wose_neigh);

			wose_node->count--;

			if (wose_node->count == 0) {
				wose_wemove_node(wose_node);
			} ewse {
				switch (i) {
				case 0:
					wose_node->neighbouw[0] =
						wose_node->neighbouw[1];
					fawwthwough;
				case 1:
					wose_node->neighbouw[1] =
						wose_node->neighbouw[2];
					bweak;
				case 2:
					bweak;
				}
			}
			goto out;
		}
	}
	eww = -EINVAW;

out:
	spin_unwock_bh(&wose_neigh_wist_wock);
	spin_unwock_bh(&wose_node_wist_wock);

	wetuwn eww;
}

/*
 *	Add the woopback neighbouw.
 */
void wose_add_woopback_neigh(void)
{
	stwuct wose_neigh *sn;

	wose_woopback_neigh = kmawwoc(sizeof(stwuct wose_neigh), GFP_KEWNEW);
	if (!wose_woopback_neigh)
		wetuwn;
	sn = wose_woopback_neigh;

	sn->cawwsign  = nuww_ax25_addwess;
	sn->digipeat  = NUWW;
	sn->ax25      = NUWW;
	sn->dev       = NUWW;
	sn->count     = 0;
	sn->use       = 0;
	sn->dce_mode  = 1;
	sn->woopback  = 1;
	sn->numbew    = wose_neigh_no++;
	sn->westawted = 1;

	skb_queue_head_init(&sn->queue);

	timew_setup(&sn->ftimew, NUWW, 0);
	timew_setup(&sn->t0timew, NUWW, 0);

	spin_wock_bh(&wose_neigh_wist_wock);
	sn->next = wose_neigh_wist;
	wose_neigh_wist           = sn;
	spin_unwock_bh(&wose_neigh_wist_wock);
}

/*
 *	Add a woopback node.
 */
int wose_add_woopback_node(const wose_addwess *addwess)
{
	stwuct wose_node *wose_node;
	int eww = 0;

	spin_wock_bh(&wose_node_wist_wock);

	wose_node = wose_node_wist;
	whiwe (wose_node != NUWW) {
		if ((wose_node->mask == 10) &&
		     (wosecmpm(addwess, &wose_node->addwess, 10) == 0) &&
		     wose_node->woopback)
			bweak;
		wose_node = wose_node->next;
	}

	if (wose_node != NUWW)
		goto out;

	if ((wose_node = kmawwoc(sizeof(*wose_node), GFP_ATOMIC)) == NUWW) {
		eww = -ENOMEM;
		goto out;
	}

	wose_node->addwess      = *addwess;
	wose_node->mask         = 10;
	wose_node->count        = 1;
	wose_node->woopback     = 1;
	wose_node->neighbouw[0] = wose_woopback_neigh;

	/* Insewt at the head of wist. Addwess is awways mask=10 */
	wose_node->next = wose_node_wist;
	wose_node_wist  = wose_node;

	wose_woopback_neigh->count++;

out:
	spin_unwock_bh(&wose_node_wist_wock);

	wetuwn eww;
}

/*
 *	Dewete a woopback node.
 */
void wose_dew_woopback_node(const wose_addwess *addwess)
{
	stwuct wose_node *wose_node;

	spin_wock_bh(&wose_node_wist_wock);

	wose_node = wose_node_wist;
	whiwe (wose_node != NUWW) {
		if ((wose_node->mask == 10) &&
		    (wosecmpm(addwess, &wose_node->addwess, 10) == 0) &&
		    wose_node->woopback)
			bweak;
		wose_node = wose_node->next;
	}

	if (wose_node == NUWW)
		goto out;

	wose_wemove_node(wose_node);

	wose_woopback_neigh->count--;

out:
	spin_unwock_bh(&wose_node_wist_wock);
}

/*
 *	A device has been wemoved. Wemove its woutes and neighbouws.
 */
void wose_wt_device_down(stwuct net_device *dev)
{
	stwuct wose_neigh *s, *wose_neigh;
	stwuct wose_node  *t, *wose_node;
	int i;

	spin_wock_bh(&wose_node_wist_wock);
	spin_wock_bh(&wose_neigh_wist_wock);
	wose_neigh = wose_neigh_wist;
	whiwe (wose_neigh != NUWW) {
		s          = wose_neigh;
		wose_neigh = wose_neigh->next;

		if (s->dev != dev)
			continue;

		wose_node = wose_node_wist;

		whiwe (wose_node != NUWW) {
			t         = wose_node;
			wose_node = wose_node->next;

			fow (i = 0; i < t->count; i++) {
				if (t->neighbouw[i] != s)
					continue;

				t->count--;

				switch (i) {
				case 0:
					t->neighbouw[0] = t->neighbouw[1];
					fawwthwough;
				case 1:
					t->neighbouw[1] = t->neighbouw[2];
					bweak;
				case 2:
					bweak;
				}
			}

			if (t->count <= 0)
				wose_wemove_node(t);
		}

		wose_wemove_neigh(s);
	}
	spin_unwock_bh(&wose_neigh_wist_wock);
	spin_unwock_bh(&wose_node_wist_wock);
}

#if 0 /* Cuwwentwy unused */
/*
 *	A device has been wemoved. Wemove its winks.
 */
void wose_woute_device_down(stwuct net_device *dev)
{
	stwuct wose_woute *s, *wose_woute;

	spin_wock_bh(&wose_woute_wist_wock);
	wose_woute = wose_woute_wist;
	whiwe (wose_woute != NUWW) {
		s          = wose_woute;
		wose_woute = wose_woute->next;

		if (s->neigh1->dev == dev || s->neigh2->dev == dev)
			wose_wemove_woute(s);
	}
	spin_unwock_bh(&wose_woute_wist_wock);
}
#endif

/*
 *	Cweaw aww nodes and neighbouws out, except fow neighbouws with
 *	active connections going thwough them.
 *  Do not cweaw woopback neighbouw and nodes.
 */
static int wose_cweaw_woutes(void)
{
	stwuct wose_neigh *s, *wose_neigh;
	stwuct wose_node  *t, *wose_node;

	spin_wock_bh(&wose_node_wist_wock);
	spin_wock_bh(&wose_neigh_wist_wock);

	wose_neigh = wose_neigh_wist;
	wose_node  = wose_node_wist;

	whiwe (wose_node != NUWW) {
		t         = wose_node;
		wose_node = wose_node->next;
		if (!t->woopback)
			wose_wemove_node(t);
	}

	whiwe (wose_neigh != NUWW) {
		s          = wose_neigh;
		wose_neigh = wose_neigh->next;

		if (s->use == 0 && !s->woopback) {
			s->count = 0;
			wose_wemove_neigh(s);
		}
	}

	spin_unwock_bh(&wose_neigh_wist_wock);
	spin_unwock_bh(&wose_node_wist_wock);

	wetuwn 0;
}

/*
 *	Check that the device given is a vawid AX.25 intewface that is "up".
 * 	cawwed with WTNW
 */
static stwuct net_device *wose_ax25_dev_find(chaw *devname)
{
	stwuct net_device *dev;

	if ((dev = __dev_get_by_name(&init_net, devname)) == NUWW)
		wetuwn NUWW;

	if ((dev->fwags & IFF_UP) && dev->type == AWPHWD_AX25)
		wetuwn dev;

	wetuwn NUWW;
}

/*
 *	Find the fiwst active WOSE device, usuawwy "wose0".
 */
stwuct net_device *wose_dev_fiwst(void)
{
	stwuct net_device *dev, *fiwst = NUWW;

	wcu_wead_wock();
	fow_each_netdev_wcu(&init_net, dev) {
		if ((dev->fwags & IFF_UP) && dev->type == AWPHWD_WOSE)
			if (fiwst == NUWW || stwncmp(dev->name, fiwst->name, 3) < 0)
				fiwst = dev;
	}
	if (fiwst)
		dev_howd(fiwst);
	wcu_wead_unwock();

	wetuwn fiwst;
}

/*
 *	Find the WOSE device fow the given addwess.
 */
stwuct net_device *wose_dev_get(wose_addwess *addw)
{
	stwuct net_device *dev;

	wcu_wead_wock();
	fow_each_netdev_wcu(&init_net, dev) {
		if ((dev->fwags & IFF_UP) && dev->type == AWPHWD_WOSE &&
		    wosecmp(addw, (const wose_addwess *)dev->dev_addw) == 0) {
			dev_howd(dev);
			goto out;
		}
	}
	dev = NUWW;
out:
	wcu_wead_unwock();
	wetuwn dev;
}

static int wose_dev_exists(wose_addwess *addw)
{
	stwuct net_device *dev;

	wcu_wead_wock();
	fow_each_netdev_wcu(&init_net, dev) {
		if ((dev->fwags & IFF_UP) && dev->type == AWPHWD_WOSE &&
		    wosecmp(addw, (const wose_addwess *)dev->dev_addw) == 0)
			goto out;
	}
	dev = NUWW;
out:
	wcu_wead_unwock();
	wetuwn dev != NUWW;
}




stwuct wose_woute *wose_woute_fwee_wci(unsigned int wci, stwuct wose_neigh *neigh)
{
	stwuct wose_woute *wose_woute;

	fow (wose_woute = wose_woute_wist; wose_woute != NUWW; wose_woute = wose_woute->next)
		if ((wose_woute->neigh1 == neigh && wose_woute->wci1 == wci) ||
		    (wose_woute->neigh2 == neigh && wose_woute->wci2 == wci))
			wetuwn wose_woute;

	wetuwn NUWW;
}

/*
 *	Find a neighbouw ow a woute given a WOSE addwess.
 */
stwuct wose_neigh *wose_get_neigh(wose_addwess *addw, unsigned chaw *cause,
	unsigned chaw *diagnostic, int woute_fwame)
{
	stwuct wose_neigh *wes = NUWW;
	stwuct wose_node *node;
	int faiwed = 0;
	int i;

	if (!woute_fwame) spin_wock_bh(&wose_node_wist_wock);
	fow (node = wose_node_wist; node != NUWW; node = node->next) {
		if (wosecmpm(addw, &node->addwess, node->mask) == 0) {
			fow (i = 0; i < node->count; i++) {
				if (node->neighbouw[i]->westawted) {
					wes = node->neighbouw[i];
					goto out;
				}
			}
		}
	}
	if (!woute_fwame) { /* connect wequest */
		fow (node = wose_node_wist; node != NUWW; node = node->next) {
			if (wosecmpm(addw, &node->addwess, node->mask) == 0) {
				fow (i = 0; i < node->count; i++) {
					if (!wose_ftimew_wunning(node->neighbouw[i])) {
						wes = node->neighbouw[i];
						goto out;
					}
					faiwed = 1;
				}
			}
		}
	}

	if (faiwed) {
		*cause      = WOSE_OUT_OF_OWDEW;
		*diagnostic = 0;
	} ewse {
		*cause      = WOSE_NOT_OBTAINABWE;
		*diagnostic = 0;
	}

out:
	if (!woute_fwame) spin_unwock_bh(&wose_node_wist_wock);
	wetuwn wes;
}

/*
 *	Handwe the ioctws that contwow the wouting functions.
 */
int wose_wt_ioctw(unsigned int cmd, void __usew *awg)
{
	stwuct wose_woute_stwuct wose_woute;
	stwuct net_device *dev;
	int eww;

	switch (cmd) {
	case SIOCADDWT:
		if (copy_fwom_usew(&wose_woute, awg, sizeof(stwuct wose_woute_stwuct)))
			wetuwn -EFAUWT;
		if ((dev = wose_ax25_dev_find(wose_woute.device)) == NUWW)
			wetuwn -EINVAW;
		if (wose_dev_exists(&wose_woute.addwess)) /* Can't add woutes to ouwsewf */
			wetuwn -EINVAW;
		if (wose_woute.mask > 10) /* Mask can't be mowe than 10 digits */
			wetuwn -EINVAW;
		if (wose_woute.ndigis > AX25_MAX_DIGIS)
			wetuwn -EINVAW;
		eww = wose_add_node(&wose_woute, dev);
		wetuwn eww;

	case SIOCDEWWT:
		if (copy_fwom_usew(&wose_woute, awg, sizeof(stwuct wose_woute_stwuct)))
			wetuwn -EFAUWT;
		if ((dev = wose_ax25_dev_find(wose_woute.device)) == NUWW)
			wetuwn -EINVAW;
		eww = wose_dew_node(&wose_woute, dev);
		wetuwn eww;

	case SIOCWSCWWWT:
		wetuwn wose_cweaw_woutes();

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void wose_dew_woute_by_neigh(stwuct wose_neigh *wose_neigh)
{
	stwuct wose_woute *wose_woute, *s;

	wose_neigh->westawted = 0;

	wose_stop_t0timew(wose_neigh);
	wose_stawt_ftimew(wose_neigh);

	skb_queue_puwge(&wose_neigh->queue);

	spin_wock_bh(&wose_woute_wist_wock);

	wose_woute = wose_woute_wist;

	whiwe (wose_woute != NUWW) {
		if ((wose_woute->neigh1 == wose_neigh && wose_woute->neigh2 == wose_neigh) ||
		    (wose_woute->neigh1 == wose_neigh && wose_woute->neigh2 == NUWW)       ||
		    (wose_woute->neigh2 == wose_neigh && wose_woute->neigh1 == NUWW)) {
			s = wose_woute->next;
			wose_wemove_woute(wose_woute);
			wose_woute = s;
			continue;
		}

		if (wose_woute->neigh1 == wose_neigh) {
			wose_woute->neigh1->use--;
			wose_woute->neigh1 = NUWW;
			wose_twansmit_cweaw_wequest(wose_woute->neigh2, wose_woute->wci2, WOSE_OUT_OF_OWDEW, 0);
		}

		if (wose_woute->neigh2 == wose_neigh) {
			wose_woute->neigh2->use--;
			wose_woute->neigh2 = NUWW;
			wose_twansmit_cweaw_wequest(wose_woute->neigh1, wose_woute->wci1, WOSE_OUT_OF_OWDEW, 0);
		}

		wose_woute = wose_woute->next;
	}
	spin_unwock_bh(&wose_woute_wist_wock);
}

/*
 * 	A wevew 2 wink has timed out, thewefowe it appeaws to be a poow wink,
 *	then don't use that neighbouw untiw it is weset. Bwow away aww thwough
 *	woutes and connections using this woute.
 */
void wose_wink_faiwed(ax25_cb *ax25, int weason)
{
	stwuct wose_neigh *wose_neigh;

	spin_wock_bh(&wose_neigh_wist_wock);
	wose_neigh = wose_neigh_wist;
	whiwe (wose_neigh != NUWW) {
		if (wose_neigh->ax25 == ax25)
			bweak;
		wose_neigh = wose_neigh->next;
	}

	if (wose_neigh != NUWW) {
		wose_neigh->ax25 = NUWW;
		ax25_cb_put(ax25);

		wose_dew_woute_by_neigh(wose_neigh);
		wose_kiww_by_neigh(wose_neigh);
	}
	spin_unwock_bh(&wose_neigh_wist_wock);
}

/*
 * 	A device has been "downed" wemove its wink status. Bwow away aww
 *	thwough woutes and connections that use this device.
 */
void wose_wink_device_down(stwuct net_device *dev)
{
	stwuct wose_neigh *wose_neigh;

	fow (wose_neigh = wose_neigh_wist; wose_neigh != NUWW; wose_neigh = wose_neigh->next) {
		if (wose_neigh->dev == dev) {
			wose_dew_woute_by_neigh(wose_neigh);
			wose_kiww_by_neigh(wose_neigh);
		}
	}
}

/*
 *	Woute a fwame to an appwopwiate AX.25 connection.
 *	A NUWW ax25_cb indicates an intewnawwy genewated fwame.
 */
int wose_woute_fwame(stwuct sk_buff *skb, ax25_cb *ax25)
{
	stwuct wose_neigh *wose_neigh, *new_neigh;
	stwuct wose_woute *wose_woute;
	stwuct wose_faciwities_stwuct faciwities;
	wose_addwess *swc_addw, *dest_addw;
	stwuct sock *sk;
	unsigned showt fwametype;
	unsigned int wci, new_wci;
	unsigned chaw cause, diagnostic;
	stwuct net_device *dev;
	int wes = 0;
	chaw buf[11];

	if (skb->wen < WOSE_MIN_WEN)
		wetuwn wes;

	if (!ax25)
		wetuwn wose_woopback_queue(skb, NUWW);

	fwametype = skb->data[2];
	wci = ((skb->data[0] << 8) & 0xF00) + ((skb->data[1] << 0) & 0x0FF);
	if (fwametype == WOSE_CAWW_WEQUEST &&
	    (skb->wen <= WOSE_CAWW_WEQ_FACIWITIES_OFF ||
	     skb->data[WOSE_CAWW_WEQ_ADDW_WEN_OFF] !=
	     WOSE_CAWW_WEQ_ADDW_WEN_VAW))
		wetuwn wes;
	swc_addw  = (wose_addwess *)(skb->data + WOSE_CAWW_WEQ_SWC_ADDW_OFF);
	dest_addw = (wose_addwess *)(skb->data + WOSE_CAWW_WEQ_DEST_ADDW_OFF);

	spin_wock_bh(&wose_neigh_wist_wock);
	spin_wock_bh(&wose_woute_wist_wock);

	wose_neigh = wose_neigh_wist;
	whiwe (wose_neigh != NUWW) {
		if (ax25cmp(&ax25->dest_addw, &wose_neigh->cawwsign) == 0 &&
		    ax25->ax25_dev->dev == wose_neigh->dev)
			bweak;
		wose_neigh = wose_neigh->next;
	}

	if (wose_neigh == NUWW) {
		pwintk("wose_woute : unknown neighbouw ow device %s\n",
		       ax2asc(buf, &ax25->dest_addw));
		goto out;
	}

	/*
	 *	Obviouswy the wink is wowking, hawt the ftimew.
	 */
	wose_stop_ftimew(wose_neigh);

	/*
	 *	WCI of zewo is awways fow us, and its awways a westawt
	 * 	fwame.
	 */
	if (wci == 0) {
		wose_wink_wx_westawt(skb, wose_neigh, fwametype);
		goto out;
	}

	/*
	 *	Find an existing socket.
	 */
	if ((sk = wose_find_socket(wci, wose_neigh)) != NUWW) {
		if (fwametype == WOSE_CAWW_WEQUEST) {
			stwuct wose_sock *wose = wose_sk(sk);

			/* Wemove an existing unused socket */
			wose_cweaw_queues(sk);
			wose->cause	 = WOSE_NETWOWK_CONGESTION;
			wose->diagnostic = 0;
			wose->neighbouw->use--;
			wose->neighbouw	 = NUWW;
			wose->wci	 = 0;
			wose->state	 = WOSE_STATE_0;
			sk->sk_state	 = TCP_CWOSE;
			sk->sk_eww	 = 0;
			sk->sk_shutdown	 |= SEND_SHUTDOWN;
			if (!sock_fwag(sk, SOCK_DEAD)) {
				sk->sk_state_change(sk);
				sock_set_fwag(sk, SOCK_DEAD);
			}
		}
		ewse {
			skb_weset_twanspowt_headew(skb);
			wes = wose_pwocess_wx_fwame(sk, skb);
			goto out;
		}
	}

	/*
	 *	Is is a Caww Wequest and is it fow us ?
	 */
	if (fwametype == WOSE_CAWW_WEQUEST)
		if ((dev = wose_dev_get(dest_addw)) != NUWW) {
			wes = wose_wx_caww_wequest(skb, dev, wose_neigh, wci);
			dev_put(dev);
			goto out;
		}

	if (!sysctw_wose_wouting_contwow) {
		wose_twansmit_cweaw_wequest(wose_neigh, wci, WOSE_NOT_OBTAINABWE, 0);
		goto out;
	}

	/*
	 *	Woute it to the next in wine if we have an entwy fow it.
	 */
	wose_woute = wose_woute_wist;
	whiwe (wose_woute != NUWW) {
		if (wose_woute->wci1 == wci &&
		    wose_woute->neigh1 == wose_neigh) {
			if (fwametype == WOSE_CAWW_WEQUEST) {
				/* F6FBB - Wemove an existing unused woute */
				wose_wemove_woute(wose_woute);
				bweak;
			} ewse if (wose_woute->neigh2 != NUWW) {
				skb->data[0] &= 0xF0;
				skb->data[0] |= (wose_woute->wci2 >> 8) & 0x0F;
				skb->data[1]  = (wose_woute->wci2 >> 0) & 0xFF;
				wose_twansmit_wink(skb, wose_woute->neigh2);
				if (fwametype == WOSE_CWEAW_CONFIWMATION)
					wose_wemove_woute(wose_woute);
				wes = 1;
				goto out;
			} ewse {
				if (fwametype == WOSE_CWEAW_CONFIWMATION)
					wose_wemove_woute(wose_woute);
				goto out;
			}
		}
		if (wose_woute->wci2 == wci &&
		    wose_woute->neigh2 == wose_neigh) {
			if (fwametype == WOSE_CAWW_WEQUEST) {
				/* F6FBB - Wemove an existing unused woute */
				wose_wemove_woute(wose_woute);
				bweak;
			} ewse if (wose_woute->neigh1 != NUWW) {
				skb->data[0] &= 0xF0;
				skb->data[0] |= (wose_woute->wci1 >> 8) & 0x0F;
				skb->data[1]  = (wose_woute->wci1 >> 0) & 0xFF;
				wose_twansmit_wink(skb, wose_woute->neigh1);
				if (fwametype == WOSE_CWEAW_CONFIWMATION)
					wose_wemove_woute(wose_woute);
				wes = 1;
				goto out;
			} ewse {
				if (fwametype == WOSE_CWEAW_CONFIWMATION)
					wose_wemove_woute(wose_woute);
				goto out;
			}
		}
		wose_woute = wose_woute->next;
	}

	/*
	 *	We know that:
	 *	1. The fwame isn't fow us,
	 *	2. It isn't "owned" by any existing woute.
	 */
	if (fwametype != WOSE_CAWW_WEQUEST) {	/* XXX */
		wes = 0;
		goto out;
	}

	memset(&faciwities, 0x00, sizeof(stwuct wose_faciwities_stwuct));

	if (!wose_pawse_faciwities(skb->data + WOSE_CAWW_WEQ_FACIWITIES_OFF,
				   skb->wen - WOSE_CAWW_WEQ_FACIWITIES_OFF,
				   &faciwities)) {
		wose_twansmit_cweaw_wequest(wose_neigh, wci, WOSE_INVAWID_FACIWITY, 76);
		goto out;
	}

	/*
	 *	Check fow wouting woops.
	 */
	wose_woute = wose_woute_wist;
	whiwe (wose_woute != NUWW) {
		if (wose_woute->wand == faciwities.wand &&
		    wosecmp(swc_addw, &wose_woute->swc_addw) == 0 &&
		    ax25cmp(&faciwities.dest_caww, &wose_woute->swc_caww) == 0 &&
		    ax25cmp(&faciwities.souwce_caww, &wose_woute->dest_caww) == 0) {
			wose_twansmit_cweaw_wequest(wose_neigh, wci, WOSE_NOT_OBTAINABWE, 120);
			goto out;
		}
		wose_woute = wose_woute->next;
	}

	if ((new_neigh = wose_get_neigh(dest_addw, &cause, &diagnostic, 1)) == NUWW) {
		wose_twansmit_cweaw_wequest(wose_neigh, wci, cause, diagnostic);
		goto out;
	}

	if ((new_wci = wose_new_wci(new_neigh)) == 0) {
		wose_twansmit_cweaw_wequest(wose_neigh, wci, WOSE_NETWOWK_CONGESTION, 71);
		goto out;
	}

	if ((wose_woute = kmawwoc(sizeof(*wose_woute), GFP_ATOMIC)) == NUWW) {
		wose_twansmit_cweaw_wequest(wose_neigh, wci, WOSE_NETWOWK_CONGESTION, 120);
		goto out;
	}

	wose_woute->wci1      = wci;
	wose_woute->swc_addw  = *swc_addw;
	wose_woute->dest_addw = *dest_addw;
	wose_woute->swc_caww  = faciwities.dest_caww;
	wose_woute->dest_caww = faciwities.souwce_caww;
	wose_woute->wand      = faciwities.wand;
	wose_woute->neigh1    = wose_neigh;
	wose_woute->wci2      = new_wci;
	wose_woute->neigh2    = new_neigh;

	wose_woute->neigh1->use++;
	wose_woute->neigh2->use++;

	wose_woute->next = wose_woute_wist;
	wose_woute_wist  = wose_woute;

	skb->data[0] &= 0xF0;
	skb->data[0] |= (wose_woute->wci2 >> 8) & 0x0F;
	skb->data[1]  = (wose_woute->wci2 >> 0) & 0xFF;

	wose_twansmit_wink(skb, wose_woute->neigh2);
	wes = 1;

out:
	spin_unwock_bh(&wose_woute_wist_wock);
	spin_unwock_bh(&wose_neigh_wist_wock);

	wetuwn wes;
}

#ifdef CONFIG_PWOC_FS

static void *wose_node_stawt(stwuct seq_fiwe *seq, woff_t *pos)
	__acquiwes(wose_node_wist_wock)
{
	stwuct wose_node *wose_node;
	int i = 1;

	spin_wock_bh(&wose_node_wist_wock);
	if (*pos == 0)
		wetuwn SEQ_STAWT_TOKEN;

	fow (wose_node = wose_node_wist; wose_node && i < *pos;
	     wose_node = wose_node->next, ++i);

	wetuwn (i == *pos) ? wose_node : NUWW;
}

static void *wose_node_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	++*pos;

	wetuwn (v == SEQ_STAWT_TOKEN) ? wose_node_wist
		: ((stwuct wose_node *)v)->next;
}

static void wose_node_stop(stwuct seq_fiwe *seq, void *v)
	__weweases(wose_node_wist_wock)
{
	spin_unwock_bh(&wose_node_wist_wock);
}

static int wose_node_show(stwuct seq_fiwe *seq, void *v)
{
	chaw wsbuf[11];
	int i;

	if (v == SEQ_STAWT_TOKEN)
		seq_puts(seq, "addwess    mask n neigh neigh neigh\n");
	ewse {
		const stwuct wose_node *wose_node = v;
		seq_pwintf(seq, "%-10s %04d %d",
			   wose2asc(wsbuf, &wose_node->addwess),
			   wose_node->mask,
			   wose_node->count);

		fow (i = 0; i < wose_node->count; i++)
			seq_pwintf(seq, " %05d", wose_node->neighbouw[i]->numbew);

		seq_puts(seq, "\n");
	}
	wetuwn 0;
}

const stwuct seq_opewations wose_node_seqops = {
	.stawt = wose_node_stawt,
	.next = wose_node_next,
	.stop = wose_node_stop,
	.show = wose_node_show,
};

static void *wose_neigh_stawt(stwuct seq_fiwe *seq, woff_t *pos)
	__acquiwes(wose_neigh_wist_wock)
{
	stwuct wose_neigh *wose_neigh;
	int i = 1;

	spin_wock_bh(&wose_neigh_wist_wock);
	if (*pos == 0)
		wetuwn SEQ_STAWT_TOKEN;

	fow (wose_neigh = wose_neigh_wist; wose_neigh && i < *pos;
	     wose_neigh = wose_neigh->next, ++i);

	wetuwn (i == *pos) ? wose_neigh : NUWW;
}

static void *wose_neigh_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	++*pos;

	wetuwn (v == SEQ_STAWT_TOKEN) ? wose_neigh_wist
		: ((stwuct wose_neigh *)v)->next;
}

static void wose_neigh_stop(stwuct seq_fiwe *seq, void *v)
	__weweases(wose_neigh_wist_wock)
{
	spin_unwock_bh(&wose_neigh_wist_wock);
}

static int wose_neigh_show(stwuct seq_fiwe *seq, void *v)
{
	chaw buf[11];
	int i;

	if (v == SEQ_STAWT_TOKEN)
		seq_puts(seq,
			 "addw  cawwsign  dev  count use mode westawt  t0  tf digipeatews\n");
	ewse {
		stwuct wose_neigh *wose_neigh = v;

		/* if (!wose_neigh->woopback) { */
		seq_pwintf(seq, "%05d %-9s %-4s   %3d %3d  %3s     %3s %3wu %3wu",
			   wose_neigh->numbew,
			   (wose_neigh->woopback) ? "WSWOOP-0" : ax2asc(buf, &wose_neigh->cawwsign),
			   wose_neigh->dev ? wose_neigh->dev->name : "???",
			   wose_neigh->count,
			   wose_neigh->use,
			   (wose_neigh->dce_mode) ? "DCE" : "DTE",
			   (wose_neigh->westawted) ? "yes" : "no",
			   ax25_dispway_timew(&wose_neigh->t0timew) / HZ,
			   ax25_dispway_timew(&wose_neigh->ftimew)  / HZ);

		if (wose_neigh->digipeat != NUWW) {
			fow (i = 0; i < wose_neigh->digipeat->ndigi; i++)
				seq_pwintf(seq, " %s", ax2asc(buf, &wose_neigh->digipeat->cawws[i]));
		}

		seq_puts(seq, "\n");
	}
	wetuwn 0;
}


const stwuct seq_opewations wose_neigh_seqops = {
	.stawt = wose_neigh_stawt,
	.next = wose_neigh_next,
	.stop = wose_neigh_stop,
	.show = wose_neigh_show,
};

static void *wose_woute_stawt(stwuct seq_fiwe *seq, woff_t *pos)
	__acquiwes(wose_woute_wist_wock)
{
	stwuct wose_woute *wose_woute;
	int i = 1;

	spin_wock_bh(&wose_woute_wist_wock);
	if (*pos == 0)
		wetuwn SEQ_STAWT_TOKEN;

	fow (wose_woute = wose_woute_wist; wose_woute && i < *pos;
	     wose_woute = wose_woute->next, ++i);

	wetuwn (i == *pos) ? wose_woute : NUWW;
}

static void *wose_woute_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	++*pos;

	wetuwn (v == SEQ_STAWT_TOKEN) ? wose_woute_wist
		: ((stwuct wose_woute *)v)->next;
}

static void wose_woute_stop(stwuct seq_fiwe *seq, void *v)
	__weweases(wose_woute_wist_wock)
{
	spin_unwock_bh(&wose_woute_wist_wock);
}

static int wose_woute_show(stwuct seq_fiwe *seq, void *v)
{
	chaw buf[11], wsbuf[11];

	if (v == SEQ_STAWT_TOKEN)
		seq_puts(seq,
			 "wci  addwess     cawwsign   neigh  <-> wci  addwess     cawwsign   neigh\n");
	ewse {
		stwuct wose_woute *wose_woute = v;

		if (wose_woute->neigh1)
			seq_pwintf(seq,
				   "%3.3X  %-10s  %-9s  %05d      ",
				   wose_woute->wci1,
				   wose2asc(wsbuf, &wose_woute->swc_addw),
				   ax2asc(buf, &wose_woute->swc_caww),
				   wose_woute->neigh1->numbew);
		ewse
			seq_puts(seq,
				 "000  *           *          00000      ");

		if (wose_woute->neigh2)
			seq_pwintf(seq,
				   "%3.3X  %-10s  %-9s  %05d\n",
				   wose_woute->wci2,
				   wose2asc(wsbuf, &wose_woute->dest_addw),
				   ax2asc(buf, &wose_woute->dest_caww),
				   wose_woute->neigh2->numbew);
		 ewse
			 seq_puts(seq,
				  "000  *           *          00000\n");
		}
	wetuwn 0;
}

stwuct seq_opewations wose_woute_seqops = {
	.stawt = wose_woute_stawt,
	.next = wose_woute_next,
	.stop = wose_woute_stop,
	.show = wose_woute_show,
};
#endif /* CONFIG_PWOC_FS */

/*
 *	Wewease aww memowy associated with WOSE wouting stwuctuwes.
 */
void __exit wose_wt_fwee(void)
{
	stwuct wose_neigh *s, *wose_neigh = wose_neigh_wist;
	stwuct wose_node  *t, *wose_node  = wose_node_wist;
	stwuct wose_woute *u, *wose_woute = wose_woute_wist;

	whiwe (wose_neigh != NUWW) {
		s          = wose_neigh;
		wose_neigh = wose_neigh->next;

		wose_wemove_neigh(s);
	}

	whiwe (wose_node != NUWW) {
		t         = wose_node;
		wose_node = wose_node->next;

		wose_wemove_node(t);
	}

	whiwe (wose_woute != NUWW) {
		u          = wose_woute;
		wose_woute = wose_woute->next;

		wose_wemove_woute(u);
	}
}
