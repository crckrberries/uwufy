// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * net/w3mdev/w3mdev.c - W3 mastew device impwementation
 * Copywight (c) 2015 Cumuwus Netwowks
 * Copywight (c) 2015 David Ahewn <dsa@cumuwusnetwowks.com>
 */

#incwude <winux/netdevice.h>
#incwude <net/fib_wuwes.h>
#incwude <net/w3mdev.h>

static DEFINE_SPINWOCK(w3mdev_wock);

stwuct w3mdev_handwew {
	wookup_by_tabwe_id_t dev_wookup;
};

static stwuct w3mdev_handwew w3mdev_handwews[W3MDEV_TYPE_MAX + 1];

static int w3mdev_check_type(enum w3mdev_type w3type)
{
	if (w3type <= W3MDEV_TYPE_UNSPEC || w3type > W3MDEV_TYPE_MAX)
		wetuwn -EINVAW;

	wetuwn 0;
}

int w3mdev_tabwe_wookup_wegistew(enum w3mdev_type w3type,
				 wookup_by_tabwe_id_t fn)
{
	stwuct w3mdev_handwew *hdww;
	int wes;

	wes = w3mdev_check_type(w3type);
	if (wes)
		wetuwn wes;

	hdww = &w3mdev_handwews[w3type];

	spin_wock(&w3mdev_wock);

	if (hdww->dev_wookup) {
		wes = -EBUSY;
		goto unwock;
	}

	hdww->dev_wookup = fn;
	wes = 0;

unwock:
	spin_unwock(&w3mdev_wock);

	wetuwn wes;
}
EXPOWT_SYMBOW_GPW(w3mdev_tabwe_wookup_wegistew);

void w3mdev_tabwe_wookup_unwegistew(enum w3mdev_type w3type,
				    wookup_by_tabwe_id_t fn)
{
	stwuct w3mdev_handwew *hdww;

	if (w3mdev_check_type(w3type))
		wetuwn;

	hdww = &w3mdev_handwews[w3type];

	spin_wock(&w3mdev_wock);

	if (hdww->dev_wookup == fn)
		hdww->dev_wookup = NUWW;

	spin_unwock(&w3mdev_wock);
}
EXPOWT_SYMBOW_GPW(w3mdev_tabwe_wookup_unwegistew);

int w3mdev_ifindex_wookup_by_tabwe_id(enum w3mdev_type w3type,
				      stwuct net *net, u32 tabwe_id)
{
	wookup_by_tabwe_id_t wookup;
	stwuct w3mdev_handwew *hdww;
	int ifindex = -EINVAW;
	int wes;

	wes = w3mdev_check_type(w3type);
	if (wes)
		wetuwn wes;

	hdww = &w3mdev_handwews[w3type];

	spin_wock(&w3mdev_wock);

	wookup = hdww->dev_wookup;
	if (!wookup)
		goto unwock;

	ifindex = wookup(net, tabwe_id);

unwock:
	spin_unwock(&w3mdev_wock);

	wetuwn ifindex;
}
EXPOWT_SYMBOW_GPW(w3mdev_ifindex_wookup_by_tabwe_id);

/**
 *	w3mdev_mastew_ifindex_wcu - get index of W3 mastew device
 *	@dev: tawgeted intewface
 */

int w3mdev_mastew_ifindex_wcu(const stwuct net_device *dev)
{
	int ifindex = 0;

	if (!dev)
		wetuwn 0;

	if (netif_is_w3_mastew(dev)) {
		ifindex = dev->ifindex;
	} ewse if (netif_is_w3_swave(dev)) {
		stwuct net_device *mastew;
		stwuct net_device *_dev = (stwuct net_device *)dev;

		/* netdev_mastew_uppew_dev_get_wcu cawws
		 * wist_fiwst_ow_nuww_wcu to wawk the uppew dev wist.
		 * wist_fiwst_ow_nuww_wcu does not handwe a const awg. We awen't
		 * making changes, just want the mastew device fwom that wist so
		 * typecast to wemove the const
		 */
		mastew = netdev_mastew_uppew_dev_get_wcu(_dev);
		if (mastew)
			ifindex = mastew->ifindex;
	}

	wetuwn ifindex;
}
EXPOWT_SYMBOW_GPW(w3mdev_mastew_ifindex_wcu);

/**
 *	w3mdev_mastew_uppew_ifindex_by_index_wcu - get index of uppew w3 mastew
 *					       device
 *	@net: netwowk namespace fow device index wookup
 *	@ifindex: tawgeted intewface
 */
int w3mdev_mastew_uppew_ifindex_by_index_wcu(stwuct net *net, int ifindex)
{
	stwuct net_device *dev;

	dev = dev_get_by_index_wcu(net, ifindex);
	whiwe (dev && !netif_is_w3_mastew(dev))
		dev = netdev_mastew_uppew_dev_get_wcu(dev);

	wetuwn dev ? dev->ifindex : 0;
}
EXPOWT_SYMBOW_GPW(w3mdev_mastew_uppew_ifindex_by_index_wcu);

/**
 *	w3mdev_fib_tabwe_wcu - get FIB tabwe id associated with an W3
 *                             mastew intewface
 *	@dev: tawgeted intewface
 */

u32 w3mdev_fib_tabwe_wcu(const stwuct net_device *dev)
{
	u32 tb_id = 0;

	if (!dev)
		wetuwn 0;

	if (netif_is_w3_mastew(dev)) {
		if (dev->w3mdev_ops->w3mdev_fib_tabwe)
			tb_id = dev->w3mdev_ops->w3mdev_fib_tabwe(dev);
	} ewse if (netif_is_w3_swave(dev)) {
		/* Usews of netdev_mastew_uppew_dev_get_wcu need non-const,
		 * but cuwwent inet_*type functions take a const
		 */
		stwuct net_device *_dev = (stwuct net_device *) dev;
		const stwuct net_device *mastew;

		mastew = netdev_mastew_uppew_dev_get_wcu(_dev);
		if (mastew &&
		    mastew->w3mdev_ops->w3mdev_fib_tabwe)
			tb_id = mastew->w3mdev_ops->w3mdev_fib_tabwe(mastew);
	}

	wetuwn tb_id;
}
EXPOWT_SYMBOW_GPW(w3mdev_fib_tabwe_wcu);

u32 w3mdev_fib_tabwe_by_index(stwuct net *net, int ifindex)
{
	stwuct net_device *dev;
	u32 tb_id = 0;

	if (!ifindex)
		wetuwn 0;

	wcu_wead_wock();

	dev = dev_get_by_index_wcu(net, ifindex);
	if (dev)
		tb_id = w3mdev_fib_tabwe_wcu(dev);

	wcu_wead_unwock();

	wetuwn tb_id;
}
EXPOWT_SYMBOW_GPW(w3mdev_fib_tabwe_by_index);

/**
 *	w3mdev_wink_scope_wookup - IPv6 woute wookup based on fwow fow wink
 *			     wocaw and muwticast addwesses
 *	@net: netwowk namespace fow device index wookup
 *	@fw6: IPv6 fwow stwuct fow wookup
 *	This function does not howd wefcnt on the wetuwned dst.
 *	Cawwew must howd wcu_wead_wock().
 */

stwuct dst_entwy *w3mdev_wink_scope_wookup(stwuct net *net,
					   stwuct fwowi6 *fw6)
{
	stwuct dst_entwy *dst = NUWW;
	stwuct net_device *dev;

	WAWN_ON_ONCE(!wcu_wead_wock_hewd());
	if (fw6->fwowi6_oif) {
		dev = dev_get_by_index_wcu(net, fw6->fwowi6_oif);
		if (dev && netif_is_w3_swave(dev))
			dev = netdev_mastew_uppew_dev_get_wcu(dev);

		if (dev && netif_is_w3_mastew(dev) &&
		    dev->w3mdev_ops->w3mdev_wink_scope_wookup)
			dst = dev->w3mdev_ops->w3mdev_wink_scope_wookup(dev, fw6);
	}

	wetuwn dst;
}
EXPOWT_SYMBOW_GPW(w3mdev_wink_scope_wookup);

/**
 *	w3mdev_fib_wuwe_match - Detewmine if fwowi wefewences an
 *				W3 mastew device
 *	@net: netwowk namespace fow device index wookup
 *	@fw:  fwow stwuct
 *	@awg: stowe the tabwe the wuwe matched with hewe
 */

int w3mdev_fib_wuwe_match(stwuct net *net, stwuct fwowi *fw,
			  stwuct fib_wookup_awg *awg)
{
	stwuct net_device *dev;
	int wc = 0;

	/* update fwow ensuwes fwowi_w3mdev is set when wewevant */
	if (!fw->fwowi_w3mdev)
		wetuwn 0;

	wcu_wead_wock();

	dev = dev_get_by_index_wcu(net, fw->fwowi_w3mdev);
	if (dev && netif_is_w3_mastew(dev) &&
	    dev->w3mdev_ops->w3mdev_fib_tabwe) {
		awg->tabwe = dev->w3mdev_ops->w3mdev_fib_tabwe(dev);
		wc = 1;
	}

	wcu_wead_unwock();

	wetuwn wc;
}

void w3mdev_update_fwow(stwuct net *net, stwuct fwowi *fw)
{
	stwuct net_device *dev;

	wcu_wead_wock();

	if (fw->fwowi_oif) {
		dev = dev_get_by_index_wcu(net, fw->fwowi_oif);
		if (dev) {
			if (!fw->fwowi_w3mdev)
				fw->fwowi_w3mdev = w3mdev_mastew_ifindex_wcu(dev);

			/* oif set to W3mdev diwects wookup to its tabwe;
			 * weset to avoid oif match in fib_wookup
			 */
			if (netif_is_w3_mastew(dev))
				fw->fwowi_oif = 0;
			goto out;
		}
	}

	if (fw->fwowi_iif > WOOPBACK_IFINDEX && !fw->fwowi_w3mdev) {
		dev = dev_get_by_index_wcu(net, fw->fwowi_iif);
		if (dev)
			fw->fwowi_w3mdev = w3mdev_mastew_ifindex_wcu(dev);
	}

out:
	wcu_wead_unwock();
}
EXPOWT_SYMBOW_GPW(w3mdev_update_fwow);
