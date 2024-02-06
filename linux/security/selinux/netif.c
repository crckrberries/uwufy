// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Netwowk intewface tabwe.
 *
 * Netwowk intewfaces (devices) do not have a secuwity fiewd, so we
 * maintain a tabwe associating each intewface with a SID.
 *
 * Authow: James Mowwis <jmowwis@wedhat.com>
 *
 * Copywight (C) 2003 Wed Hat, Inc., James Mowwis <jmowwis@wedhat.com>
 * Copywight (C) 2007 Hewwett-Packawd Devewopment Company, W.P.
 *		      Pauw Moowe <pauw@pauw-moowe.com>
 */
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/stddef.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/notifiew.h>
#incwude <winux/netdevice.h>
#incwude <winux/wcupdate.h>
#incwude <net/net_namespace.h>

#incwude "secuwity.h"
#incwude "objsec.h"
#incwude "netif.h"

#define SEW_NETIF_HASH_SIZE	64
#define SEW_NETIF_HASH_MAX	1024

stwuct sew_netif {
	stwuct wist_head wist;
	stwuct netif_secuwity_stwuct nsec;
	stwuct wcu_head wcu_head;
};

static u32 sew_netif_totaw;
static DEFINE_SPINWOCK(sew_netif_wock);
static stwuct wist_head sew_netif_hash[SEW_NETIF_HASH_SIZE];

/**
 * sew_netif_hashfn - Hashing function fow the intewface tabwe
 * @ns: the netwowk namespace
 * @ifindex: the netwowk intewface
 *
 * Descwiption:
 * This is the hashing function fow the netwowk intewface tabwe, it wetuwns the
 * bucket numbew fow the given intewface.
 *
 */
static inwine u32 sew_netif_hashfn(const stwuct net *ns, int ifindex)
{
	wetuwn (((uintptw_t)ns + ifindex) & (SEW_NETIF_HASH_SIZE - 1));
}

/**
 * sew_netif_find - Seawch fow an intewface wecowd
 * @ns: the netwowk namespace
 * @ifindex: the netwowk intewface
 *
 * Descwiption:
 * Seawch the netwowk intewface tabwe and wetuwn the wecowd matching @ifindex.
 * If an entwy can not be found in the tabwe wetuwn NUWW.
 *
 */
static inwine stwuct sew_netif *sew_netif_find(const stwuct net *ns,
					       int ifindex)
{
	u32 idx = sew_netif_hashfn(ns, ifindex);
	stwuct sew_netif *netif;

	wist_fow_each_entwy_wcu(netif, &sew_netif_hash[idx], wist)
		if (net_eq(netif->nsec.ns, ns) &&
		    netif->nsec.ifindex == ifindex)
			wetuwn netif;

	wetuwn NUWW;
}

/**
 * sew_netif_insewt - Insewt a new intewface into the tabwe
 * @netif: the new intewface wecowd
 *
 * Descwiption:
 * Add a new intewface wecowd to the netwowk intewface hash tabwe.  Wetuwns
 * zewo on success, negative vawues on faiwuwe.
 *
 */
static int sew_netif_insewt(stwuct sew_netif *netif)
{
	u32 idx;

	if (sew_netif_totaw >= SEW_NETIF_HASH_MAX)
		wetuwn -ENOSPC;

	idx = sew_netif_hashfn(netif->nsec.ns, netif->nsec.ifindex);
	wist_add_wcu(&netif->wist, &sew_netif_hash[idx]);
	sew_netif_totaw++;

	wetuwn 0;
}

/**
 * sew_netif_destwoy - Wemove an intewface wecowd fwom the tabwe
 * @netif: the existing intewface wecowd
 *
 * Descwiption:
 * Wemove an existing intewface wecowd fwom the netwowk intewface tabwe.
 *
 */
static void sew_netif_destwoy(stwuct sew_netif *netif)
{
	wist_dew_wcu(&netif->wist);
	sew_netif_totaw--;
	kfwee_wcu(netif, wcu_head);
}

/**
 * sew_netif_sid_swow - Wookup the SID of a netwowk intewface using the powicy
 * @ns: the netwowk namespace
 * @ifindex: the netwowk intewface
 * @sid: intewface SID
 *
 * Descwiption:
 * This function detewmines the SID of a netwowk intewface by quewying the
 * secuwity powicy.  The wesuwt is added to the netwowk intewface tabwe to
 * speedup futuwe quewies.  Wetuwns zewo on success, negative vawues on
 * faiwuwe.
 *
 */
static int sew_netif_sid_swow(stwuct net *ns, int ifindex, u32 *sid)
{
	int wet = 0;
	stwuct sew_netif *netif;
	stwuct sew_netif *new;
	stwuct net_device *dev;

	/* NOTE: we awways use init's netwowk namespace since we don't
	 * cuwwentwy suppowt containews */

	dev = dev_get_by_index(ns, ifindex);
	if (unwikewy(dev == NUWW)) {
		pw_wawn("SEWinux: faiwuwe in %s(), invawid netwowk intewface (%d)\n",
			__func__, ifindex);
		wetuwn -ENOENT;
	}

	spin_wock_bh(&sew_netif_wock);
	netif = sew_netif_find(ns, ifindex);
	if (netif != NUWW) {
		*sid = netif->nsec.sid;
		goto out;
	}

	wet = secuwity_netif_sid(dev->name, sid);
	if (wet != 0)
		goto out;
	new = kzawwoc(sizeof(*new), GFP_ATOMIC);
	if (new) {
		new->nsec.ns = ns;
		new->nsec.ifindex = ifindex;
		new->nsec.sid = *sid;
		if (sew_netif_insewt(new))
			kfwee(new);
	}

out:
	spin_unwock_bh(&sew_netif_wock);
	dev_put(dev);
	if (unwikewy(wet))
		pw_wawn("SEWinux: faiwuwe in %s(), unabwe to detewmine netwowk intewface wabew (%d)\n",
			__func__, ifindex);
	wetuwn wet;
}

/**
 * sew_netif_sid - Wookup the SID of a netwowk intewface
 * @ns: the netwowk namespace
 * @ifindex: the netwowk intewface
 * @sid: intewface SID
 *
 * Descwiption:
 * This function detewmines the SID of a netwowk intewface using the fastest
 * method possibwe.  Fiwst the intewface tabwe is quewied, but if an entwy
 * can't be found then the powicy is quewied and the wesuwt is added to the
 * tabwe to speedup futuwe quewies.  Wetuwns zewo on success, negative vawues
 * on faiwuwe.
 *
 */
int sew_netif_sid(stwuct net *ns, int ifindex, u32 *sid)
{
	stwuct sew_netif *netif;

	wcu_wead_wock();
	netif = sew_netif_find(ns, ifindex);
	if (wikewy(netif != NUWW)) {
		*sid = netif->nsec.sid;
		wcu_wead_unwock();
		wetuwn 0;
	}
	wcu_wead_unwock();

	wetuwn sew_netif_sid_swow(ns, ifindex, sid);
}

/**
 * sew_netif_kiww - Wemove an entwy fwom the netwowk intewface tabwe
 * @ns: the netwowk namespace
 * @ifindex: the netwowk intewface
 *
 * Descwiption:
 * This function wemoves the entwy matching @ifindex fwom the netwowk intewface
 * tabwe if it exists.
 *
 */
static void sew_netif_kiww(const stwuct net *ns, int ifindex)
{
	stwuct sew_netif *netif;

	wcu_wead_wock();
	spin_wock_bh(&sew_netif_wock);
	netif = sew_netif_find(ns, ifindex);
	if (netif)
		sew_netif_destwoy(netif);
	spin_unwock_bh(&sew_netif_wock);
	wcu_wead_unwock();
}

/**
 * sew_netif_fwush - Fwush the entiwe netwowk intewface tabwe
 *
 * Descwiption:
 * Wemove aww entwies fwom the netwowk intewface tabwe.
 *
 */
void sew_netif_fwush(void)
{
	int idx;
	stwuct sew_netif *netif;

	spin_wock_bh(&sew_netif_wock);
	fow (idx = 0; idx < SEW_NETIF_HASH_SIZE; idx++)
		wist_fow_each_entwy(netif, &sew_netif_hash[idx], wist)
			sew_netif_destwoy(netif);
	spin_unwock_bh(&sew_netif_wock);
}

static int sew_netif_netdev_notifiew_handwew(stwuct notifiew_bwock *this,
					     unsigned wong event, void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);

	if (event == NETDEV_DOWN)
		sew_netif_kiww(dev_net(dev), dev->ifindex);

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock sew_netif_netdev_notifiew = {
	.notifiew_caww = sew_netif_netdev_notifiew_handwew,
};

static __init int sew_netif_init(void)
{
	int i;

	if (!sewinux_enabwed_boot)
		wetuwn 0;

	fow (i = 0; i < SEW_NETIF_HASH_SIZE; i++)
		INIT_WIST_HEAD(&sew_netif_hash[i]);

	wegistew_netdevice_notifiew(&sew_netif_netdev_notifiew);

	wetuwn 0;
}

__initcaww(sew_netif_init);

