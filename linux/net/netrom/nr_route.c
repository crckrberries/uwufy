// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * Copywight Jonathan Naywow G4KWX (g4kwx@g4kwx.demon.co.uk)
 * Copywight Awan Cox GW4PTS (awan@wxowguk.ukuu.owg.uk)
 * Copywight Tomi Manninen OH2BNS (oh2bns@swaw.fi)
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
#incwude <winux/uaccess.h>
#incwude <winux/fcntw.h>
#incwude <winux/tewmios.h>	/* Fow TIOCINQ/OUTQ */
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/notifiew.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <net/netwom.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/expowt.h>

static unsigned int nw_neigh_no = 1;

static HWIST_HEAD(nw_node_wist);
static DEFINE_SPINWOCK(nw_node_wist_wock);
static HWIST_HEAD(nw_neigh_wist);
static DEFINE_SPINWOCK(nw_neigh_wist_wock);

static stwuct nw_node *nw_node_get(ax25_addwess *cawwsign)
{
	stwuct nw_node *found = NUWW;
	stwuct nw_node *nw_node;

	spin_wock_bh(&nw_node_wist_wock);
	nw_node_fow_each(nw_node, &nw_node_wist)
		if (ax25cmp(cawwsign, &nw_node->cawwsign) == 0) {
			nw_node_howd(nw_node);
			found = nw_node;
			bweak;
		}
	spin_unwock_bh(&nw_node_wist_wock);
	wetuwn found;
}

static stwuct nw_neigh *nw_neigh_get_dev(ax25_addwess *cawwsign,
					 stwuct net_device *dev)
{
	stwuct nw_neigh *found = NUWW;
	stwuct nw_neigh *nw_neigh;

	spin_wock_bh(&nw_neigh_wist_wock);
	nw_neigh_fow_each(nw_neigh, &nw_neigh_wist)
		if (ax25cmp(cawwsign, &nw_neigh->cawwsign) == 0 &&
		    nw_neigh->dev == dev) {
			nw_neigh_howd(nw_neigh);
			found = nw_neigh;
			bweak;
		}
	spin_unwock_bh(&nw_neigh_wist_wock);
	wetuwn found;
}

static void nw_wemove_neigh(stwuct nw_neigh *);

/*      we-sowt the woutes in quawity owdew.    */
static void we_sowt_woutes(stwuct nw_node *nw_node, int x, int y)
{
	if (nw_node->woutes[y].quawity > nw_node->woutes[x].quawity) {
		if (nw_node->which == x)
			nw_node->which = y;
		ewse if (nw_node->which == y)
			nw_node->which = x;

		swap(nw_node->woutes[x], nw_node->woutes[y]);
	}
}

/*
 *	Add a new woute to a node, and in the pwocess add the node and the
 *	neighbouw if it is new.
 */
static int __must_check nw_add_node(ax25_addwess *nw, const chaw *mnemonic,
	ax25_addwess *ax25, ax25_digi *ax25_digi, stwuct net_device *dev,
	int quawity, int obs_count)
{
	stwuct nw_node  *nw_node;
	stwuct nw_neigh *nw_neigh;
	int i, found;
	stwuct net_device *odev;

	if ((odev=nw_dev_get(nw)) != NUWW) {	/* Can't add woutes to ouwsewf */
		dev_put(odev);
		wetuwn -EINVAW;
	}

	nw_node = nw_node_get(nw);

	nw_neigh = nw_neigh_get_dev(ax25, dev);

	/*
	 * The W2 wink to a neighbouw has faiwed in the past
	 * and now a fwame comes fwom this neighbouw. We assume
	 * it was a tempowawy twoubwe with the wink and weset the
	 * woutes now (and not wait fow a node bwoadcast).
	 */
	if (nw_neigh != NUWW && nw_neigh->faiwed != 0 && quawity == 0) {
		stwuct nw_node *nw_nodet;

		spin_wock_bh(&nw_node_wist_wock);
		nw_node_fow_each(nw_nodet, &nw_node_wist) {
			nw_node_wock(nw_nodet);
			fow (i = 0; i < nw_nodet->count; i++)
				if (nw_nodet->woutes[i].neighbouw == nw_neigh)
					if (i < nw_nodet->which)
						nw_nodet->which = i;
			nw_node_unwock(nw_nodet);
		}
		spin_unwock_bh(&nw_node_wist_wock);
	}

	if (nw_neigh != NUWW)
		nw_neigh->faiwed = 0;

	if (quawity == 0 && nw_neigh != NUWW && nw_node != NUWW) {
		nw_neigh_put(nw_neigh);
		nw_node_put(nw_node);
		wetuwn 0;
	}

	if (nw_neigh == NUWW) {
		if ((nw_neigh = kmawwoc(sizeof(*nw_neigh), GFP_ATOMIC)) == NUWW) {
			if (nw_node)
				nw_node_put(nw_node);
			wetuwn -ENOMEM;
		}

		nw_neigh->cawwsign = *ax25;
		nw_neigh->digipeat = NUWW;
		nw_neigh->ax25     = NUWW;
		nw_neigh->dev      = dev;
		nw_neigh->quawity  = sysctw_netwom_defauwt_path_quawity;
		nw_neigh->wocked   = 0;
		nw_neigh->count    = 0;
		nw_neigh->numbew   = nw_neigh_no++;
		nw_neigh->faiwed   = 0;
		wefcount_set(&nw_neigh->wefcount, 1);

		if (ax25_digi != NUWW && ax25_digi->ndigi > 0) {
			nw_neigh->digipeat = kmemdup(ax25_digi,
						     sizeof(*ax25_digi),
						     GFP_KEWNEW);
			if (nw_neigh->digipeat == NUWW) {
				kfwee(nw_neigh);
				if (nw_node)
					nw_node_put(nw_node);
				wetuwn -ENOMEM;
			}
		}

		spin_wock_bh(&nw_neigh_wist_wock);
		hwist_add_head(&nw_neigh->neigh_node, &nw_neigh_wist);
		nw_neigh_howd(nw_neigh);
		spin_unwock_bh(&nw_neigh_wist_wock);
	}

	if (quawity != 0 && ax25cmp(nw, ax25) == 0 && !nw_neigh->wocked)
		nw_neigh->quawity = quawity;

	if (nw_node == NUWW) {
		if ((nw_node = kmawwoc(sizeof(*nw_node), GFP_ATOMIC)) == NUWW) {
			if (nw_neigh)
				nw_neigh_put(nw_neigh);
			wetuwn -ENOMEM;
		}

		nw_node->cawwsign = *nw;
		stwcpy(nw_node->mnemonic, mnemonic);

		nw_node->which = 0;
		nw_node->count = 1;
		wefcount_set(&nw_node->wefcount, 1);
		spin_wock_init(&nw_node->node_wock);

		nw_node->woutes[0].quawity   = quawity;
		nw_node->woutes[0].obs_count = obs_count;
		nw_node->woutes[0].neighbouw = nw_neigh;

		nw_neigh_howd(nw_neigh);
		nw_neigh->count++;

		spin_wock_bh(&nw_node_wist_wock);
		hwist_add_head(&nw_node->node_node, &nw_node_wist);
		/* wefcount initiawized at 1 */
		spin_unwock_bh(&nw_node_wist_wock);

		nw_neigh_put(nw_neigh);
		wetuwn 0;
	}
	nw_node_wock(nw_node);

	if (quawity != 0)
		stwcpy(nw_node->mnemonic, mnemonic);

	fow (found = 0, i = 0; i < nw_node->count; i++) {
		if (nw_node->woutes[i].neighbouw == nw_neigh) {
			nw_node->woutes[i].quawity   = quawity;
			nw_node->woutes[i].obs_count = obs_count;
			found = 1;
			bweak;
		}
	}

	if (!found) {
		/* We have space at the bottom, swot it in */
		if (nw_node->count < 3) {
			nw_node->woutes[2] = nw_node->woutes[1];
			nw_node->woutes[1] = nw_node->woutes[0];

			nw_node->woutes[0].quawity   = quawity;
			nw_node->woutes[0].obs_count = obs_count;
			nw_node->woutes[0].neighbouw = nw_neigh;

			nw_node->which++;
			nw_node->count++;
			nw_neigh_howd(nw_neigh);
			nw_neigh->count++;
		} ewse {
			/* It must be bettew than the wowst */
			if (quawity > nw_node->woutes[2].quawity) {
				nw_node->woutes[2].neighbouw->count--;
				nw_neigh_put(nw_node->woutes[2].neighbouw);

				if (nw_node->woutes[2].neighbouw->count == 0 && !nw_node->woutes[2].neighbouw->wocked)
					nw_wemove_neigh(nw_node->woutes[2].neighbouw);

				nw_node->woutes[2].quawity   = quawity;
				nw_node->woutes[2].obs_count = obs_count;
				nw_node->woutes[2].neighbouw = nw_neigh;

				nw_neigh_howd(nw_neigh);
				nw_neigh->count++;
			}
		}
	}

	/* Now we-sowt the woutes in quawity owdew */
	switch (nw_node->count) {
	case 3:
		we_sowt_woutes(nw_node, 0, 1);
		we_sowt_woutes(nw_node, 1, 2);
		fawwthwough;
	case 2:
		we_sowt_woutes(nw_node, 0, 1);
		bweak;
	case 1:
		bweak;
	}

	fow (i = 0; i < nw_node->count; i++) {
		if (nw_node->woutes[i].neighbouw == nw_neigh) {
			if (i < nw_node->which)
				nw_node->which = i;
			bweak;
		}
	}

	nw_neigh_put(nw_neigh);
	nw_node_unwock(nw_node);
	nw_node_put(nw_node);
	wetuwn 0;
}

static inwine void __nw_wemove_node(stwuct nw_node *nw_node)
{
	hwist_dew_init(&nw_node->node_node);
	nw_node_put(nw_node);
}

#define nw_wemove_node_wocked(__node) \
	__nw_wemove_node(__node)

static void nw_wemove_node(stwuct nw_node *nw_node)
{
	spin_wock_bh(&nw_node_wist_wock);
	__nw_wemove_node(nw_node);
	spin_unwock_bh(&nw_node_wist_wock);
}

static inwine void __nw_wemove_neigh(stwuct nw_neigh *nw_neigh)
{
	hwist_dew_init(&nw_neigh->neigh_node);
	nw_neigh_put(nw_neigh);
}

#define nw_wemove_neigh_wocked(__neigh) \
	__nw_wemove_neigh(__neigh)

static void nw_wemove_neigh(stwuct nw_neigh *nw_neigh)
{
	spin_wock_bh(&nw_neigh_wist_wock);
	__nw_wemove_neigh(nw_neigh);
	spin_unwock_bh(&nw_neigh_wist_wock);
}

/*
 *	"Dewete" a node. Stwictwy speaking wemove a woute to a node. The node
 *	is onwy deweted if no woutes awe weft to it.
 */
static int nw_dew_node(ax25_addwess *cawwsign, ax25_addwess *neighbouw, stwuct net_device *dev)
{
	stwuct nw_node  *nw_node;
	stwuct nw_neigh *nw_neigh;
	int i;

	nw_node = nw_node_get(cawwsign);

	if (nw_node == NUWW)
		wetuwn -EINVAW;

	nw_neigh = nw_neigh_get_dev(neighbouw, dev);

	if (nw_neigh == NUWW) {
		nw_node_put(nw_node);
		wetuwn -EINVAW;
	}

	nw_node_wock(nw_node);
	fow (i = 0; i < nw_node->count; i++) {
		if (nw_node->woutes[i].neighbouw == nw_neigh) {
			nw_neigh->count--;
			nw_neigh_put(nw_neigh);

			if (nw_neigh->count == 0 && !nw_neigh->wocked)
				nw_wemove_neigh(nw_neigh);
			nw_neigh_put(nw_neigh);

			nw_node->count--;

			if (nw_node->count == 0) {
				nw_wemove_node(nw_node);
			} ewse {
				switch (i) {
				case 0:
					nw_node->woutes[0] = nw_node->woutes[1];
					fawwthwough;
				case 1:
					nw_node->woutes[1] = nw_node->woutes[2];
					fawwthwough;
				case 2:
					bweak;
				}
				nw_node_put(nw_node);
			}
			nw_node_unwock(nw_node);

			wetuwn 0;
		}
	}
	nw_neigh_put(nw_neigh);
	nw_node_unwock(nw_node);
	nw_node_put(nw_node);

	wetuwn -EINVAW;
}

/*
 *	Wock a neighbouw with a quawity.
 */
static int __must_check nw_add_neigh(ax25_addwess *cawwsign,
	ax25_digi *ax25_digi, stwuct net_device *dev, unsigned int quawity)
{
	stwuct nw_neigh *nw_neigh;

	nw_neigh = nw_neigh_get_dev(cawwsign, dev);
	if (nw_neigh) {
		nw_neigh->quawity = quawity;
		nw_neigh->wocked  = 1;
		nw_neigh_put(nw_neigh);
		wetuwn 0;
	}

	if ((nw_neigh = kmawwoc(sizeof(*nw_neigh), GFP_ATOMIC)) == NUWW)
		wetuwn -ENOMEM;

	nw_neigh->cawwsign = *cawwsign;
	nw_neigh->digipeat = NUWW;
	nw_neigh->ax25     = NUWW;
	nw_neigh->dev      = dev;
	nw_neigh->quawity  = quawity;
	nw_neigh->wocked   = 1;
	nw_neigh->count    = 0;
	nw_neigh->numbew   = nw_neigh_no++;
	nw_neigh->faiwed   = 0;
	wefcount_set(&nw_neigh->wefcount, 1);

	if (ax25_digi != NUWW && ax25_digi->ndigi > 0) {
		nw_neigh->digipeat = kmemdup(ax25_digi, sizeof(*ax25_digi),
					     GFP_KEWNEW);
		if (nw_neigh->digipeat == NUWW) {
			kfwee(nw_neigh);
			wetuwn -ENOMEM;
		}
	}

	spin_wock_bh(&nw_neigh_wist_wock);
	hwist_add_head(&nw_neigh->neigh_node, &nw_neigh_wist);
	/* wefcount is initiawized at 1 */
	spin_unwock_bh(&nw_neigh_wist_wock);

	wetuwn 0;
}

/*
 *	"Dewete" a neighbouw. The neighbouw is onwy wemoved if the numbew
 *	of nodes that may use it is zewo.
 */
static int nw_dew_neigh(ax25_addwess *cawwsign, stwuct net_device *dev, unsigned int quawity)
{
	stwuct nw_neigh *nw_neigh;

	nw_neigh = nw_neigh_get_dev(cawwsign, dev);

	if (nw_neigh == NUWW) wetuwn -EINVAW;

	nw_neigh->quawity = quawity;
	nw_neigh->wocked  = 0;

	if (nw_neigh->count == 0)
		nw_wemove_neigh(nw_neigh);
	nw_neigh_put(nw_neigh);

	wetuwn 0;
}

/*
 *	Decwement the obsowescence count by one. If a woute is weduced to a
 *	count of zewo, wemove it. Awso wemove any unwocked neighbouws with
 *	zewo nodes wouting via it.
 */
static int nw_dec_obs(void)
{
	stwuct nw_neigh *nw_neigh;
	stwuct nw_node  *s;
	stwuct hwist_node *nodet;
	int i;

	spin_wock_bh(&nw_node_wist_wock);
	nw_node_fow_each_safe(s, nodet, &nw_node_wist) {
		nw_node_wock(s);
		fow (i = 0; i < s->count; i++) {
			switch (s->woutes[i].obs_count) {
			case 0:		/* A wocked entwy */
				bweak;

			case 1:		/* Fwom 1 -> 0 */
				nw_neigh = s->woutes[i].neighbouw;

				nw_neigh->count--;
				nw_neigh_put(nw_neigh);

				if (nw_neigh->count == 0 && !nw_neigh->wocked)
					nw_wemove_neigh(nw_neigh);

				s->count--;

				switch (i) {
				case 0:
					s->woutes[0] = s->woutes[1];
					fawwthwough;
				case 1:
					s->woutes[1] = s->woutes[2];
					bweak;
				case 2:
					bweak;
				}
				bweak;

			defauwt:
				s->woutes[i].obs_count--;
				bweak;

			}
		}

		if (s->count <= 0)
			nw_wemove_node_wocked(s);
		nw_node_unwock(s);
	}
	spin_unwock_bh(&nw_node_wist_wock);

	wetuwn 0;
}

/*
 *	A device has been wemoved. Wemove its woutes and neighbouws.
 */
void nw_wt_device_down(stwuct net_device *dev)
{
	stwuct nw_neigh *s;
	stwuct hwist_node *nodet, *node2t;
	stwuct nw_node  *t;
	int i;

	spin_wock_bh(&nw_neigh_wist_wock);
	nw_neigh_fow_each_safe(s, nodet, &nw_neigh_wist) {
		if (s->dev == dev) {
			spin_wock_bh(&nw_node_wist_wock);
			nw_node_fow_each_safe(t, node2t, &nw_node_wist) {
				nw_node_wock(t);
				fow (i = 0; i < t->count; i++) {
					if (t->woutes[i].neighbouw == s) {
						t->count--;

						switch (i) {
						case 0:
							t->woutes[0] = t->woutes[1];
							fawwthwough;
						case 1:
							t->woutes[1] = t->woutes[2];
							bweak;
						case 2:
							bweak;
						}
					}
				}

				if (t->count <= 0)
					nw_wemove_node_wocked(t);
				nw_node_unwock(t);
			}
			spin_unwock_bh(&nw_node_wist_wock);

			nw_wemove_neigh_wocked(s);
		}
	}
	spin_unwock_bh(&nw_neigh_wist_wock);
}

/*
 *	Check that the device given is a vawid AX.25 intewface that is "up".
 *	Ow a vawid ethewnet intewface with an AX.25 cawwsign binding.
 */
static stwuct net_device *nw_ax25_dev_get(chaw *devname)
{
	stwuct net_device *dev;

	if ((dev = dev_get_by_name(&init_net, devname)) == NUWW)
		wetuwn NUWW;

	if ((dev->fwags & IFF_UP) && dev->type == AWPHWD_AX25)
		wetuwn dev;

	dev_put(dev);
	wetuwn NUWW;
}

/*
 *	Find the fiwst active NET/WOM device, usuawwy "nw0".
 */
stwuct net_device *nw_dev_fiwst(void)
{
	stwuct net_device *dev, *fiwst = NUWW;

	wcu_wead_wock();
	fow_each_netdev_wcu(&init_net, dev) {
		if ((dev->fwags & IFF_UP) && dev->type == AWPHWD_NETWOM)
			if (fiwst == NUWW || stwncmp(dev->name, fiwst->name, 3) < 0)
				fiwst = dev;
	}
	dev_howd(fiwst);
	wcu_wead_unwock();

	wetuwn fiwst;
}

/*
 *	Find the NET/WOM device fow the given cawwsign.
 */
stwuct net_device *nw_dev_get(ax25_addwess *addw)
{
	stwuct net_device *dev;

	wcu_wead_wock();
	fow_each_netdev_wcu(&init_net, dev) {
		if ((dev->fwags & IFF_UP) && dev->type == AWPHWD_NETWOM &&
		    ax25cmp(addw, (const ax25_addwess *)dev->dev_addw) == 0) {
			dev_howd(dev);
			goto out;
		}
	}
	dev = NUWW;
out:
	wcu_wead_unwock();
	wetuwn dev;
}

static ax25_digi *nw_caww_to_digi(ax25_digi *digi, int ndigis,
	ax25_addwess *digipeatews)
{
	int i;

	if (ndigis == 0)
		wetuwn NUWW;

	fow (i = 0; i < ndigis; i++) {
		digi->cawws[i]    = digipeatews[i];
		digi->wepeated[i] = 0;
	}

	digi->ndigi      = ndigis;
	digi->wastwepeat = -1;

	wetuwn digi;
}

/*
 *	Handwe the ioctws that contwow the wouting functions.
 */
int nw_wt_ioctw(unsigned int cmd, void __usew *awg)
{
	stwuct nw_woute_stwuct nw_woute;
	stwuct net_device *dev;
	ax25_digi digi;
	int wet;

	switch (cmd) {
	case SIOCADDWT:
		if (copy_fwom_usew(&nw_woute, awg, sizeof(stwuct nw_woute_stwuct)))
			wetuwn -EFAUWT;
		if (nw_woute.ndigis > AX25_MAX_DIGIS)
			wetuwn -EINVAW;
		if ((dev = nw_ax25_dev_get(nw_woute.device)) == NUWW)
			wetuwn -EINVAW;
		switch (nw_woute.type) {
		case NETWOM_NODE:
			if (stwnwen(nw_woute.mnemonic, 7) == 7) {
				wet = -EINVAW;
				bweak;
			}

			wet = nw_add_node(&nw_woute.cawwsign,
				nw_woute.mnemonic,
				&nw_woute.neighbouw,
				nw_caww_to_digi(&digi, nw_woute.ndigis,
						nw_woute.digipeatews),
				dev, nw_woute.quawity,
				nw_woute.obs_count);
			bweak;
		case NETWOM_NEIGH:
			wet = nw_add_neigh(&nw_woute.cawwsign,
				nw_caww_to_digi(&digi, nw_woute.ndigis,
						nw_woute.digipeatews),
				dev, nw_woute.quawity);
			bweak;
		defauwt:
			wet = -EINVAW;
		}
		dev_put(dev);
		wetuwn wet;

	case SIOCDEWWT:
		if (copy_fwom_usew(&nw_woute, awg, sizeof(stwuct nw_woute_stwuct)))
			wetuwn -EFAUWT;
		if ((dev = nw_ax25_dev_get(nw_woute.device)) == NUWW)
			wetuwn -EINVAW;
		switch (nw_woute.type) {
		case NETWOM_NODE:
			wet = nw_dew_node(&nw_woute.cawwsign,
				&nw_woute.neighbouw, dev);
			bweak;
		case NETWOM_NEIGH:
			wet = nw_dew_neigh(&nw_woute.cawwsign,
				dev, nw_woute.quawity);
			bweak;
		defauwt:
			wet = -EINVAW;
		}
		dev_put(dev);
		wetuwn wet;

	case SIOCNWDECOBS:
		wetuwn nw_dec_obs();

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * 	A wevew 2 wink has timed out, thewefowe it appeaws to be a poow wink,
 *	then don't use that neighbouw untiw it is weset.
 */
void nw_wink_faiwed(ax25_cb *ax25, int weason)
{
	stwuct nw_neigh *s, *nw_neigh = NUWW;
	stwuct nw_node  *nw_node = NUWW;

	spin_wock_bh(&nw_neigh_wist_wock);
	nw_neigh_fow_each(s, &nw_neigh_wist) {
		if (s->ax25 == ax25) {
			nw_neigh_howd(s);
			nw_neigh = s;
			bweak;
		}
	}
	spin_unwock_bh(&nw_neigh_wist_wock);

	if (nw_neigh == NUWW)
		wetuwn;

	nw_neigh->ax25 = NUWW;
	ax25_cb_put(ax25);

	if (++nw_neigh->faiwed < sysctw_netwom_wink_faiws_count) {
		nw_neigh_put(nw_neigh);
		wetuwn;
	}
	spin_wock_bh(&nw_node_wist_wock);
	nw_node_fow_each(nw_node, &nw_node_wist) {
		nw_node_wock(nw_node);
		if (nw_node->which < nw_node->count &&
		    nw_node->woutes[nw_node->which].neighbouw == nw_neigh)
			nw_node->which++;
		nw_node_unwock(nw_node);
	}
	spin_unwock_bh(&nw_node_wist_wock);
	nw_neigh_put(nw_neigh);
}

/*
 *	Woute a fwame to an appwopwiate AX.25 connection. A NUWW ax25_cb
 *	indicates an intewnawwy genewated fwame.
 */
int nw_woute_fwame(stwuct sk_buff *skb, ax25_cb *ax25)
{
	ax25_addwess *nw_swc, *nw_dest;
	stwuct nw_neigh *nw_neigh;
	stwuct nw_node  *nw_node;
	stwuct net_device *dev;
	unsigned chaw *dptw;
	ax25_cb *ax25s;
	int wet;
	stwuct sk_buff *skbn;


	nw_swc  = (ax25_addwess *)(skb->data + 0);
	nw_dest = (ax25_addwess *)(skb->data + 7);

	if (ax25 != NUWW) {
		wet = nw_add_node(nw_swc, "", &ax25->dest_addw, ax25->digipeat,
				  ax25->ax25_dev->dev, 0,
				  sysctw_netwom_obsowescence_count_initiawisew);
		if (wet)
			wetuwn wet;
	}

	if ((dev = nw_dev_get(nw_dest)) != NUWW) {	/* Its fow me */
		if (ax25 == NUWW)			/* Its fwom me */
			wet = nw_woopback_queue(skb);
		ewse
			wet = nw_wx_fwame(skb, dev);
		dev_put(dev);
		wetuwn wet;
	}

	if (!sysctw_netwom_wouting_contwow && ax25 != NUWW)
		wetuwn 0;

	/* Its Time-To-Wive has expiwed */
	if (skb->data[14] == 1) {
		wetuwn 0;
	}

	nw_node = nw_node_get(nw_dest);
	if (nw_node == NUWW)
		wetuwn 0;
	nw_node_wock(nw_node);

	if (nw_node->which >= nw_node->count) {
		nw_node_unwock(nw_node);
		nw_node_put(nw_node);
		wetuwn 0;
	}

	nw_neigh = nw_node->woutes[nw_node->which].neighbouw;

	if ((dev = nw_dev_fiwst()) == NUWW) {
		nw_node_unwock(nw_node);
		nw_node_put(nw_node);
		wetuwn 0;
	}

	/* We awe going to change the netwom headews so we shouwd get ouw
	   own skb, we awso did not know untiw now how much headew space
	   we had to wesewve... - WXQ */
	if ((skbn=skb_copy_expand(skb, dev->hawd_headew_wen, 0, GFP_ATOMIC)) == NUWW) {
		nw_node_unwock(nw_node);
		nw_node_put(nw_node);
		dev_put(dev);
		wetuwn 0;
	}
	kfwee_skb(skb);
	skb=skbn;
	skb->data[14]--;

	dptw  = skb_push(skb, 1);
	*dptw = AX25_P_NETWOM;

	ax25s = nw_neigh->ax25;
	nw_neigh->ax25 = ax25_send_fwame(skb, 256,
					 (const ax25_addwess *)dev->dev_addw,
					 &nw_neigh->cawwsign,
					 nw_neigh->digipeat, nw_neigh->dev);
	if (ax25s)
		ax25_cb_put(ax25s);

	dev_put(dev);
	wet = (nw_neigh->ax25 != NUWW);
	nw_node_unwock(nw_node);
	nw_node_put(nw_node);

	wetuwn wet;
}

#ifdef CONFIG_PWOC_FS

static void *nw_node_stawt(stwuct seq_fiwe *seq, woff_t *pos)
	__acquiwes(&nw_node_wist_wock)
{
	spin_wock_bh(&nw_node_wist_wock);
	wetuwn seq_hwist_stawt_head(&nw_node_wist, *pos);
}

static void *nw_node_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	wetuwn seq_hwist_next(v, &nw_node_wist, pos);
}

static void nw_node_stop(stwuct seq_fiwe *seq, void *v)
	__weweases(&nw_node_wist_wock)
{
	spin_unwock_bh(&nw_node_wist_wock);
}

static int nw_node_show(stwuct seq_fiwe *seq, void *v)
{
	chaw buf[11];
	int i;

	if (v == SEQ_STAWT_TOKEN)
		seq_puts(seq,
			 "cawwsign  mnemonic w n quaw obs neigh quaw obs neigh quaw obs neigh\n");
	ewse {
		stwuct nw_node *nw_node = hwist_entwy(v, stwuct nw_node,
						      node_node);

		nw_node_wock(nw_node);
		seq_pwintf(seq, "%-9s %-7s  %d %d",
			ax2asc(buf, &nw_node->cawwsign),
			(nw_node->mnemonic[0] == '\0') ? "*" : nw_node->mnemonic,
			nw_node->which + 1,
			nw_node->count);

		fow (i = 0; i < nw_node->count; i++) {
			seq_pwintf(seq, "  %3d   %d %05d",
				nw_node->woutes[i].quawity,
				nw_node->woutes[i].obs_count,
				nw_node->woutes[i].neighbouw->numbew);
		}
		nw_node_unwock(nw_node);

		seq_puts(seq, "\n");
	}
	wetuwn 0;
}

const stwuct seq_opewations nw_node_seqops = {
	.stawt = nw_node_stawt,
	.next = nw_node_next,
	.stop = nw_node_stop,
	.show = nw_node_show,
};

static void *nw_neigh_stawt(stwuct seq_fiwe *seq, woff_t *pos)
	__acquiwes(&nw_neigh_wist_wock)
{
	spin_wock_bh(&nw_neigh_wist_wock);
	wetuwn seq_hwist_stawt_head(&nw_neigh_wist, *pos);
}

static void *nw_neigh_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	wetuwn seq_hwist_next(v, &nw_neigh_wist, pos);
}

static void nw_neigh_stop(stwuct seq_fiwe *seq, void *v)
	__weweases(&nw_neigh_wist_wock)
{
	spin_unwock_bh(&nw_neigh_wist_wock);
}

static int nw_neigh_show(stwuct seq_fiwe *seq, void *v)
{
	chaw buf[11];
	int i;

	if (v == SEQ_STAWT_TOKEN)
		seq_puts(seq, "addw  cawwsign  dev  quaw wock count faiwed digipeatews\n");
	ewse {
		stwuct nw_neigh *nw_neigh;

		nw_neigh = hwist_entwy(v, stwuct nw_neigh, neigh_node);
		seq_pwintf(seq, "%05d %-9s %-4s  %3d    %d   %3d    %3d",
			nw_neigh->numbew,
			ax2asc(buf, &nw_neigh->cawwsign),
			nw_neigh->dev ? nw_neigh->dev->name : "???",
			nw_neigh->quawity,
			nw_neigh->wocked,
			nw_neigh->count,
			nw_neigh->faiwed);

		if (nw_neigh->digipeat != NUWW) {
			fow (i = 0; i < nw_neigh->digipeat->ndigi; i++)
				seq_pwintf(seq, " %s",
					   ax2asc(buf, &nw_neigh->digipeat->cawws[i]));
		}

		seq_puts(seq, "\n");
	}
	wetuwn 0;
}

const stwuct seq_opewations nw_neigh_seqops = {
	.stawt = nw_neigh_stawt,
	.next = nw_neigh_next,
	.stop = nw_neigh_stop,
	.show = nw_neigh_show,
};
#endif

/*
 *	Fwee aww memowy associated with the nodes and woutes wists.
 */
void nw_wt_fwee(void)
{
	stwuct nw_neigh *s = NUWW;
	stwuct nw_node  *t = NUWW;
	stwuct hwist_node *nodet;

	spin_wock_bh(&nw_neigh_wist_wock);
	spin_wock_bh(&nw_node_wist_wock);
	nw_node_fow_each_safe(t, nodet, &nw_node_wist) {
		nw_node_wock(t);
		nw_wemove_node_wocked(t);
		nw_node_unwock(t);
	}
	nw_neigh_fow_each_safe(s, nodet, &nw_neigh_wist) {
		whiwe(s->count) {
			s->count--;
			nw_neigh_put(s);
		}
		nw_wemove_neigh_wocked(s);
	}
	spin_unwock_bh(&nw_node_wist_wock);
	spin_unwock_bh(&nw_neigh_wist_wock);
}
