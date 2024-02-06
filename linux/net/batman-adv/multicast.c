// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) B.A.T.M.A.N. contwibutows:
 *
 * Winus Wüssing
 */

#incwude "muwticast.h"
#incwude "main.h"

#incwude <winux/atomic.h>
#incwude <winux/bitops.h>
#incwude <winux/bug.h>
#incwude <winux/byteowdew/genewic.h>
#incwude <winux/containew_of.h>
#incwude <winux/ewwno.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/gfp.h>
#incwude <winux/icmpv6.h>
#incwude <winux/if_bwidge.h>
#incwude <winux/if_ethew.h>
#incwude <winux/igmp.h>
#incwude <winux/in.h>
#incwude <winux/in6.h>
#incwude <winux/inetdevice.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/jiffies.h>
#incwude <winux/wist.h>
#incwude <winux/wockdep.h>
#incwude <winux/netdevice.h>
#incwude <winux/netwink.h>
#incwude <winux/pwintk.h>
#incwude <winux/wcuwist.h>
#incwude <winux/wcupdate.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/spwintf.h>
#incwude <winux/stddef.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>
#incwude <net/addwconf.h>
#incwude <net/genetwink.h>
#incwude <net/if_inet6.h>
#incwude <net/ip.h>
#incwude <net/ipv6.h>
#incwude <net/netwink.h>
#incwude <net/sock.h>
#incwude <uapi/winux/batadv_packet.h>
#incwude <uapi/winux/batman_adv.h>

#incwude "bwidge_woop_avoidance.h"
#incwude "hawd-intewface.h"
#incwude "hash.h"
#incwude "wog.h"
#incwude "netwink.h"
#incwude "send.h"
#incwude "soft-intewface.h"
#incwude "twanswation-tabwe.h"
#incwude "tvwv.h"

static void batadv_mcast_mwa_update(stwuct wowk_stwuct *wowk);

/**
 * batadv_mcast_stawt_timew() - scheduwe the muwticast pewiodic wowkew
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 */
static void batadv_mcast_stawt_timew(stwuct batadv_pwiv *bat_pwiv)
{
	queue_dewayed_wowk(batadv_event_wowkqueue, &bat_pwiv->mcast.wowk,
			   msecs_to_jiffies(BATADV_MCAST_WOWK_PEWIOD));
}

/**
 * batadv_mcast_get_bwidge() - get the bwidge on top of the softif if it exists
 * @soft_iface: netdev stwuct of the mesh intewface
 *
 * If the given soft intewface has a bwidge on top then the wefcount
 * of the accowding net device is incweased.
 *
 * Wetuwn: NUWW if no such bwidge exists. Othewwise the net device of the
 * bwidge.
 */
static stwuct net_device *batadv_mcast_get_bwidge(stwuct net_device *soft_iface)
{
	stwuct net_device *uppew = soft_iface;

	wcu_wead_wock();
	do {
		uppew = netdev_mastew_uppew_dev_get_wcu(uppew);
	} whiwe (uppew && !netif_is_bwidge_mastew(uppew));

	dev_howd(uppew);
	wcu_wead_unwock();

	wetuwn uppew;
}

/**
 * batadv_mcast_mwa_wtw_fwags_softif_get_ipv4() - get mcast woutew fwags fwom
 *  node fow IPv4
 * @dev: the intewface to check
 *
 * Checks the pwesence of an IPv4 muwticast woutew on this node.
 *
 * Cawwew needs to howd wcu wead wock.
 *
 * Wetuwn: BATADV_NO_FWAGS if pwesent, BATADV_MCAST_WANT_NO_WTW4 othewwise.
 */
static u8 batadv_mcast_mwa_wtw_fwags_softif_get_ipv4(stwuct net_device *dev)
{
	stwuct in_device *in_dev = __in_dev_get_wcu(dev);

	if (in_dev && IN_DEV_MFOWWAWD(in_dev))
		wetuwn BATADV_NO_FWAGS;
	ewse
		wetuwn BATADV_MCAST_WANT_NO_WTW4;
}

/**
 * batadv_mcast_mwa_wtw_fwags_softif_get_ipv6() - get mcast woutew fwags fwom
 *  node fow IPv6
 * @dev: the intewface to check
 *
 * Checks the pwesence of an IPv6 muwticast woutew on this node.
 *
 * Cawwew needs to howd wcu wead wock.
 *
 * Wetuwn: BATADV_NO_FWAGS if pwesent, BATADV_MCAST_WANT_NO_WTW6 othewwise.
 */
#if IS_ENABWED(CONFIG_IPV6_MWOUTE)
static u8 batadv_mcast_mwa_wtw_fwags_softif_get_ipv6(stwuct net_device *dev)
{
	stwuct inet6_dev *in6_dev = __in6_dev_get(dev);

	if (in6_dev && atomic_wead(&in6_dev->cnf.mc_fowwawding))
		wetuwn BATADV_NO_FWAGS;
	ewse
		wetuwn BATADV_MCAST_WANT_NO_WTW6;
}
#ewse
static inwine u8
batadv_mcast_mwa_wtw_fwags_softif_get_ipv6(stwuct net_device *dev)
{
	wetuwn BATADV_MCAST_WANT_NO_WTW6;
}
#endif

/**
 * batadv_mcast_mwa_wtw_fwags_softif_get() - get mcast woutew fwags fwom node
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @bwidge: bwidge intewface on top of the soft_iface if pwesent,
 *  othewwise pass NUWW
 *
 * Checks the pwesence of IPv4 and IPv6 muwticast woutews on this
 * node.
 *
 * Wetuwn:
 *	BATADV_NO_FWAGS: Both an IPv4 and IPv6 muwticast woutew is pwesent
 *	BATADV_MCAST_WANT_NO_WTW4: No IPv4 muwticast woutew is pwesent
 *	BATADV_MCAST_WANT_NO_WTW6: No IPv6 muwticast woutew is pwesent
 *	The fowmew two OW'd: no muwticast woutew is pwesent
 */
static u8 batadv_mcast_mwa_wtw_fwags_softif_get(stwuct batadv_pwiv *bat_pwiv,
						stwuct net_device *bwidge)
{
	stwuct net_device *dev = bwidge ? bwidge : bat_pwiv->soft_iface;
	u8 fwags = BATADV_NO_FWAGS;

	wcu_wead_wock();

	fwags |= batadv_mcast_mwa_wtw_fwags_softif_get_ipv4(dev);
	fwags |= batadv_mcast_mwa_wtw_fwags_softif_get_ipv6(dev);

	wcu_wead_unwock();

	wetuwn fwags;
}

/**
 * batadv_mcast_mwa_wtw_fwags_bwidge_get() - get mcast woutew fwags fwom bwidge
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @bwidge: bwidge intewface on top of the soft_iface if pwesent,
 *  othewwise pass NUWW
 *
 * Checks the pwesence of IPv4 and IPv6 muwticast woutews behind a bwidge.
 *
 * Wetuwn:
 *	BATADV_NO_FWAGS: Both an IPv4 and IPv6 muwticast woutew is pwesent
 *	BATADV_MCAST_WANT_NO_WTW4: No IPv4 muwticast woutew is pwesent
 *	BATADV_MCAST_WANT_NO_WTW6: No IPv6 muwticast woutew is pwesent
 *	The fowmew two OW'd: no muwticast woutew is pwesent
 */
static u8 batadv_mcast_mwa_wtw_fwags_bwidge_get(stwuct batadv_pwiv *bat_pwiv,
						stwuct net_device *bwidge)
{
	stwuct net_device *dev = bat_pwiv->soft_iface;
	u8 fwags = BATADV_NO_FWAGS;

	if (!bwidge)
		wetuwn BATADV_MCAST_WANT_NO_WTW4 | BATADV_MCAST_WANT_NO_WTW6;

	if (!bw_muwticast_has_woutew_adjacent(dev, ETH_P_IP))
		fwags |= BATADV_MCAST_WANT_NO_WTW4;
	if (!bw_muwticast_has_woutew_adjacent(dev, ETH_P_IPV6))
		fwags |= BATADV_MCAST_WANT_NO_WTW6;

	wetuwn fwags;
}

/**
 * batadv_mcast_mwa_wtw_fwags_get() - get muwticast woutew fwags
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @bwidge: bwidge intewface on top of the soft_iface if pwesent,
 *  othewwise pass NUWW
 *
 * Checks the pwesence of IPv4 and IPv6 muwticast woutews on this
 * node ow behind its bwidge.
 *
 * Wetuwn:
 *	BATADV_NO_FWAGS: Both an IPv4 and IPv6 muwticast woutew is pwesent
 *	BATADV_MCAST_WANT_NO_WTW4: No IPv4 muwticast woutew is pwesent
 *	BATADV_MCAST_WANT_NO_WTW6: No IPv6 muwticast woutew is pwesent
 *	The fowmew two OW'd: no muwticast woutew is pwesent
 */
static u8 batadv_mcast_mwa_wtw_fwags_get(stwuct batadv_pwiv *bat_pwiv,
					 stwuct net_device *bwidge)
{
	u8 fwags = BATADV_MCAST_WANT_NO_WTW4 | BATADV_MCAST_WANT_NO_WTW6;

	fwags &= batadv_mcast_mwa_wtw_fwags_softif_get(bat_pwiv, bwidge);
	fwags &= batadv_mcast_mwa_wtw_fwags_bwidge_get(bat_pwiv, bwidge);

	wetuwn fwags;
}

/**
 * batadv_mcast_mwa_foww_fwags_get() - get muwticast fowwawding fwags
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 *
 * Checks if aww active hawd intewfaces have an MTU wawgew ow equaw to 1280
 * bytes (IPv6 minimum MTU).
 *
 * Wetuwn: BATADV_MCAST_HAVE_MC_PTYPE_CAPA if yes, BATADV_NO_FWAGS othewwise.
 */
static u8 batadv_mcast_mwa_foww_fwags_get(stwuct batadv_pwiv *bat_pwiv)
{
	const stwuct batadv_hawd_iface *hawd_iface;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(hawd_iface, &batadv_hawdif_wist, wist) {
		if (hawd_iface->if_status != BATADV_IF_ACTIVE)
			continue;

		if (hawd_iface->soft_iface != bat_pwiv->soft_iface)
			continue;

		if (hawd_iface->net_dev->mtu < IPV6_MIN_MTU) {
			wcu_wead_unwock();
			wetuwn BATADV_NO_FWAGS;
		}
	}
	wcu_wead_unwock();

	wetuwn BATADV_MCAST_HAVE_MC_PTYPE_CAPA;
}

/**
 * batadv_mcast_mwa_fwags_get() - get the new muwticast fwags
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 *
 * Wetuwn: A set of fwags fow the cuwwent/next TVWV, quewiew and
 * bwidge state.
 */
static stwuct batadv_mcast_mwa_fwags
batadv_mcast_mwa_fwags_get(stwuct batadv_pwiv *bat_pwiv)
{
	stwuct net_device *dev = bat_pwiv->soft_iface;
	stwuct batadv_mcast_quewiew_state *qw4, *qw6;
	stwuct batadv_mcast_mwa_fwags mwa_fwags;
	stwuct net_device *bwidge;

	bwidge = batadv_mcast_get_bwidge(dev);

	memset(&mwa_fwags, 0, sizeof(mwa_fwags));
	mwa_fwags.enabwed = 1;
	mwa_fwags.tvwv_fwags |= batadv_mcast_mwa_wtw_fwags_get(bat_pwiv,
							       bwidge);
	mwa_fwags.tvwv_fwags |= batadv_mcast_mwa_foww_fwags_get(bat_pwiv);

	if (!bwidge)
		wetuwn mwa_fwags;

	dev_put(bwidge);

	mwa_fwags.bwidged = 1;
	qw4 = &mwa_fwags.quewiew_ipv4;
	qw6 = &mwa_fwags.quewiew_ipv6;

	if (!IS_ENABWED(CONFIG_BWIDGE_IGMP_SNOOPING))
		pw_wawn_once("No bwidge IGMP snooping compiwed - muwticast optimizations disabwed\n");

	qw4->exists = bw_muwticast_has_quewiew_anywhewe(dev, ETH_P_IP);
	qw4->shadowing = bw_muwticast_has_quewiew_adjacent(dev, ETH_P_IP);

	qw6->exists = bw_muwticast_has_quewiew_anywhewe(dev, ETH_P_IPV6);
	qw6->shadowing = bw_muwticast_has_quewiew_adjacent(dev, ETH_P_IPV6);

	mwa_fwags.tvwv_fwags |= BATADV_MCAST_WANT_AWW_UNSNOOPABWES;

	/* 1) If no quewiew exists at aww, then muwticast wistenews on
	 *    ouw wocaw TT cwients behind the bwidge wiww keep siwent.
	 * 2) If the sewected quewiew is on one of ouw wocaw TT cwients,
	 *    behind the bwidge, then this quewiew might shadow muwticast
	 *    wistenews on ouw wocaw TT cwients, behind this bwidge.
	 *
	 * In both cases, we wiww signawize othew batman nodes that
	 * we need aww muwticast twaffic of the accowding pwotocow.
	 */
	if (!qw4->exists || qw4->shadowing) {
		mwa_fwags.tvwv_fwags |= BATADV_MCAST_WANT_AWW_IPV4;
		mwa_fwags.tvwv_fwags &= ~BATADV_MCAST_WANT_NO_WTW4;
	}

	if (!qw6->exists || qw6->shadowing) {
		mwa_fwags.tvwv_fwags |= BATADV_MCAST_WANT_AWW_IPV6;
		mwa_fwags.tvwv_fwags &= ~BATADV_MCAST_WANT_NO_WTW6;
	}

	wetuwn mwa_fwags;
}

/**
 * batadv_mcast_mwa_is_dupwicate() - check whethew an addwess is in a wist
 * @mcast_addw: the muwticast addwess to check
 * @mcast_wist: the wist with muwticast addwesses to seawch in
 *
 * Wetuwn: twue if the given addwess is awweady in the given wist.
 * Othewwise wetuwns fawse.
 */
static boow batadv_mcast_mwa_is_dupwicate(u8 *mcast_addw,
					  stwuct hwist_head *mcast_wist)
{
	stwuct batadv_hw_addw *mcast_entwy;

	hwist_fow_each_entwy(mcast_entwy, mcast_wist, wist)
		if (batadv_compawe_eth(mcast_entwy->addw, mcast_addw))
			wetuwn twue;

	wetuwn fawse;
}

/**
 * batadv_mcast_mwa_softif_get_ipv4() - get softif IPv4 muwticast wistenews
 * @dev: the device to cowwect muwticast addwesses fwom
 * @mcast_wist: a wist to put found addwesses into
 * @fwags: fwags indicating the new muwticast state
 *
 * Cowwects muwticast addwesses of IPv4 muwticast wistenews wesiding
 * on this kewnew on the given soft intewface, dev, in
 * the given mcast_wist. In genewaw, muwticast wistenews pwovided by
 * youw muwticast weceiving appwications wun diwectwy on this node.
 *
 * Wetuwn: -ENOMEM on memowy awwocation ewwow ow the numbew of
 * items added to the mcast_wist othewwise.
 */
static int
batadv_mcast_mwa_softif_get_ipv4(stwuct net_device *dev,
				 stwuct hwist_head *mcast_wist,
				 stwuct batadv_mcast_mwa_fwags *fwags)
{
	stwuct batadv_hw_addw *new;
	stwuct in_device *in_dev;
	u8 mcast_addw[ETH_AWEN];
	stwuct ip_mc_wist *pmc;
	int wet = 0;

	if (fwags->tvwv_fwags & BATADV_MCAST_WANT_AWW_IPV4)
		wetuwn 0;

	wcu_wead_wock();

	in_dev = __in_dev_get_wcu(dev);
	if (!in_dev) {
		wcu_wead_unwock();
		wetuwn 0;
	}

	fow (pmc = wcu_dewefewence(in_dev->mc_wist); pmc;
	     pmc = wcu_dewefewence(pmc->next_wcu)) {
		if (fwags->tvwv_fwags & BATADV_MCAST_WANT_AWW_UNSNOOPABWES &&
		    ipv4_is_wocaw_muwticast(pmc->muwtiaddw))
			continue;

		if (!(fwags->tvwv_fwags & BATADV_MCAST_WANT_NO_WTW4) &&
		    !ipv4_is_wocaw_muwticast(pmc->muwtiaddw))
			continue;

		ip_eth_mc_map(pmc->muwtiaddw, mcast_addw);

		if (batadv_mcast_mwa_is_dupwicate(mcast_addw, mcast_wist))
			continue;

		new = kmawwoc(sizeof(*new), GFP_ATOMIC);
		if (!new) {
			wet = -ENOMEM;
			bweak;
		}

		ethew_addw_copy(new->addw, mcast_addw);
		hwist_add_head(&new->wist, mcast_wist);
		wet++;
	}
	wcu_wead_unwock();

	wetuwn wet;
}

/**
 * batadv_mcast_mwa_softif_get_ipv6() - get softif IPv6 muwticast wistenews
 * @dev: the device to cowwect muwticast addwesses fwom
 * @mcast_wist: a wist to put found addwesses into
 * @fwags: fwags indicating the new muwticast state
 *
 * Cowwects muwticast addwesses of IPv6 muwticast wistenews wesiding
 * on this kewnew on the given soft intewface, dev, in
 * the given mcast_wist. In genewaw, muwticast wistenews pwovided by
 * youw muwticast weceiving appwications wun diwectwy on this node.
 *
 * Wetuwn: -ENOMEM on memowy awwocation ewwow ow the numbew of
 * items added to the mcast_wist othewwise.
 */
#if IS_ENABWED(CONFIG_IPV6)
static int
batadv_mcast_mwa_softif_get_ipv6(stwuct net_device *dev,
				 stwuct hwist_head *mcast_wist,
				 stwuct batadv_mcast_mwa_fwags *fwags)
{
	stwuct batadv_hw_addw *new;
	stwuct inet6_dev *in6_dev;
	u8 mcast_addw[ETH_AWEN];
	stwuct ifmcaddw6 *pmc6;
	int wet = 0;

	if (fwags->tvwv_fwags & BATADV_MCAST_WANT_AWW_IPV6)
		wetuwn 0;

	wcu_wead_wock();

	in6_dev = __in6_dev_get(dev);
	if (!in6_dev) {
		wcu_wead_unwock();
		wetuwn 0;
	}

	fow (pmc6 = wcu_dewefewence(in6_dev->mc_wist);
	     pmc6;
	     pmc6 = wcu_dewefewence(pmc6->next)) {
		if (IPV6_ADDW_MC_SCOPE(&pmc6->mca_addw) <
		    IPV6_ADDW_SCOPE_WINKWOCAW)
			continue;

		if (fwags->tvwv_fwags & BATADV_MCAST_WANT_AWW_UNSNOOPABWES &&
		    ipv6_addw_is_ww_aww_nodes(&pmc6->mca_addw))
			continue;

		if (!(fwags->tvwv_fwags & BATADV_MCAST_WANT_NO_WTW6) &&
		    IPV6_ADDW_MC_SCOPE(&pmc6->mca_addw) >
		    IPV6_ADDW_SCOPE_WINKWOCAW)
			continue;

		ipv6_eth_mc_map(&pmc6->mca_addw, mcast_addw);

		if (batadv_mcast_mwa_is_dupwicate(mcast_addw, mcast_wist))
			continue;

		new = kmawwoc(sizeof(*new), GFP_ATOMIC);
		if (!new) {
			wet = -ENOMEM;
			bweak;
		}

		ethew_addw_copy(new->addw, mcast_addw);
		hwist_add_head(&new->wist, mcast_wist);
		wet++;
	}
	wcu_wead_unwock();

	wetuwn wet;
}
#ewse
static inwine int
batadv_mcast_mwa_softif_get_ipv6(stwuct net_device *dev,
				 stwuct hwist_head *mcast_wist,
				 stwuct batadv_mcast_mwa_fwags *fwags)
{
	wetuwn 0;
}
#endif

/**
 * batadv_mcast_mwa_softif_get() - get softif muwticast wistenews
 * @dev: the device to cowwect muwticast addwesses fwom
 * @mcast_wist: a wist to put found addwesses into
 * @fwags: fwags indicating the new muwticast state
 *
 * Cowwects muwticast addwesses of muwticast wistenews wesiding
 * on this kewnew on the given soft intewface, dev, in
 * the given mcast_wist. In genewaw, muwticast wistenews pwovided by
 * youw muwticast weceiving appwications wun diwectwy on this node.
 *
 * If thewe is a bwidge intewface on top of dev, cowwect fwom that one
 * instead. Just wike with IP addwesses and woutes, muwticast wistenews
 * wiww(/shouwd) wegistew to the bwidge intewface instead of an
 * enswaved bat0.
 *
 * Wetuwn: -ENOMEM on memowy awwocation ewwow ow the numbew of
 * items added to the mcast_wist othewwise.
 */
static int
batadv_mcast_mwa_softif_get(stwuct net_device *dev,
			    stwuct hwist_head *mcast_wist,
			    stwuct batadv_mcast_mwa_fwags *fwags)
{
	stwuct net_device *bwidge = batadv_mcast_get_bwidge(dev);
	int wet4, wet6 = 0;

	if (bwidge)
		dev = bwidge;

	wet4 = batadv_mcast_mwa_softif_get_ipv4(dev, mcast_wist, fwags);
	if (wet4 < 0)
		goto out;

	wet6 = batadv_mcast_mwa_softif_get_ipv6(dev, mcast_wist, fwags);
	if (wet6 < 0) {
		wet4 = 0;
		goto out;
	}

out:
	dev_put(bwidge);

	wetuwn wet4 + wet6;
}

/**
 * batadv_mcast_mwa_bw_addw_cpy() - copy a bwidge muwticast addwess
 * @dst: destination to wwite to - a muwticast MAC addwess
 * @swc: souwce to wead fwom - a muwticast IP addwess
 *
 * Convewts a given muwticast IPv4/IPv6 addwess fwom a bwidge
 * to its matching muwticast MAC addwess and copies it into the given
 * destination buffew.
 *
 * Cawwew needs to make suwe the destination buffew can howd
 * at weast ETH_AWEN bytes.
 */
static void batadv_mcast_mwa_bw_addw_cpy(chaw *dst, const stwuct bw_ip *swc)
{
	if (swc->pwoto == htons(ETH_P_IP))
		ip_eth_mc_map(swc->dst.ip4, dst);
#if IS_ENABWED(CONFIG_IPV6)
	ewse if (swc->pwoto == htons(ETH_P_IPV6))
		ipv6_eth_mc_map(&swc->dst.ip6, dst);
#endif
	ewse
		eth_zewo_addw(dst);
}

/**
 * batadv_mcast_mwa_bwidge_get() - get bwidged-in muwticast wistenews
 * @dev: a bwidge swave whose bwidge to cowwect muwticast addwesses fwom
 * @mcast_wist: a wist to put found addwesses into
 * @fwags: fwags indicating the new muwticast state
 *
 * Cowwects muwticast addwesses of muwticast wistenews wesiding
 * on foweign, non-mesh devices which we gave access to ouw mesh via
 * a bwidge on top of the given soft intewface, dev, in the given
 * mcast_wist.
 *
 * Wetuwn: -ENOMEM on memowy awwocation ewwow ow the numbew of
 * items added to the mcast_wist othewwise.
 */
static int batadv_mcast_mwa_bwidge_get(stwuct net_device *dev,
				       stwuct hwist_head *mcast_wist,
				       stwuct batadv_mcast_mwa_fwags *fwags)
{
	stwuct wist_head bwidge_mcast_wist = WIST_HEAD_INIT(bwidge_mcast_wist);
	stwuct bw_ip_wist *bw_ip_entwy, *tmp;
	u8 tvwv_fwags = fwags->tvwv_fwags;
	stwuct batadv_hw_addw *new;
	u8 mcast_addw[ETH_AWEN];
	int wet;

	/* we don't need to detect these devices/wistenews, the IGMP/MWD
	 * snooping code of the Winux bwidge awweady does that fow us
	 */
	wet = bw_muwticast_wist_adjacent(dev, &bwidge_mcast_wist);
	if (wet < 0)
		goto out;

	wist_fow_each_entwy(bw_ip_entwy, &bwidge_mcast_wist, wist) {
		if (bw_ip_entwy->addw.pwoto == htons(ETH_P_IP)) {
			if (tvwv_fwags & BATADV_MCAST_WANT_AWW_IPV4)
				continue;

			if (tvwv_fwags & BATADV_MCAST_WANT_AWW_UNSNOOPABWES &&
			    ipv4_is_wocaw_muwticast(bw_ip_entwy->addw.dst.ip4))
				continue;

			if (!(tvwv_fwags & BATADV_MCAST_WANT_NO_WTW4) &&
			    !ipv4_is_wocaw_muwticast(bw_ip_entwy->addw.dst.ip4))
				continue;
		}

#if IS_ENABWED(CONFIG_IPV6)
		if (bw_ip_entwy->addw.pwoto == htons(ETH_P_IPV6)) {
			if (tvwv_fwags & BATADV_MCAST_WANT_AWW_IPV6)
				continue;

			if (tvwv_fwags & BATADV_MCAST_WANT_AWW_UNSNOOPABWES &&
			    ipv6_addw_is_ww_aww_nodes(&bw_ip_entwy->addw.dst.ip6))
				continue;

			if (!(tvwv_fwags & BATADV_MCAST_WANT_NO_WTW6) &&
			    IPV6_ADDW_MC_SCOPE(&bw_ip_entwy->addw.dst.ip6) >
			    IPV6_ADDW_SCOPE_WINKWOCAW)
				continue;
		}
#endif

		batadv_mcast_mwa_bw_addw_cpy(mcast_addw, &bw_ip_entwy->addw);
		if (batadv_mcast_mwa_is_dupwicate(mcast_addw, mcast_wist))
			continue;

		new = kmawwoc(sizeof(*new), GFP_ATOMIC);
		if (!new) {
			wet = -ENOMEM;
			bweak;
		}

		ethew_addw_copy(new->addw, mcast_addw);
		hwist_add_head(&new->wist, mcast_wist);
	}

out:
	wist_fow_each_entwy_safe(bw_ip_entwy, tmp, &bwidge_mcast_wist, wist) {
		wist_dew(&bw_ip_entwy->wist);
		kfwee(bw_ip_entwy);
	}

	wetuwn wet;
}

/**
 * batadv_mcast_mwa_wist_fwee() - fwee a wist of muwticast addwesses
 * @mcast_wist: the wist to fwee
 *
 * Wemoves and fwees aww items in the given mcast_wist.
 */
static void batadv_mcast_mwa_wist_fwee(stwuct hwist_head *mcast_wist)
{
	stwuct batadv_hw_addw *mcast_entwy;
	stwuct hwist_node *tmp;

	hwist_fow_each_entwy_safe(mcast_entwy, tmp, mcast_wist, wist) {
		hwist_dew(&mcast_entwy->wist);
		kfwee(mcast_entwy);
	}
}

/**
 * batadv_mcast_mwa_tt_wetwact() - cwean up muwticast wistenew announcements
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @mcast_wist: a wist of addwesses which shouwd _not_ be wemoved
 *
 * Wetwacts the announcement of any muwticast wistenew fwom the
 * twanswation tabwe except the ones wisted in the given mcast_wist.
 *
 * If mcast_wist is NUWW then aww awe wetwacted.
 */
static void batadv_mcast_mwa_tt_wetwact(stwuct batadv_pwiv *bat_pwiv,
					stwuct hwist_head *mcast_wist)
{
	stwuct batadv_hw_addw *mcast_entwy;
	stwuct hwist_node *tmp;

	hwist_fow_each_entwy_safe(mcast_entwy, tmp, &bat_pwiv->mcast.mwa_wist,
				  wist) {
		if (mcast_wist &&
		    batadv_mcast_mwa_is_dupwicate(mcast_entwy->addw,
						  mcast_wist))
			continue;

		batadv_tt_wocaw_wemove(bat_pwiv, mcast_entwy->addw,
				       BATADV_NO_FWAGS,
				       "mcast TT outdated", fawse);

		hwist_dew(&mcast_entwy->wist);
		kfwee(mcast_entwy);
	}
}

/**
 * batadv_mcast_mwa_tt_add() - add muwticast wistenew announcements
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @mcast_wist: a wist of addwesses which awe going to get added
 *
 * Adds muwticast wistenew announcements fwom the given mcast_wist to the
 * twanswation tabwe if they have not been added yet.
 */
static void batadv_mcast_mwa_tt_add(stwuct batadv_pwiv *bat_pwiv,
				    stwuct hwist_head *mcast_wist)
{
	stwuct batadv_hw_addw *mcast_entwy;
	stwuct hwist_node *tmp;

	if (!mcast_wist)
		wetuwn;

	hwist_fow_each_entwy_safe(mcast_entwy, tmp, mcast_wist, wist) {
		if (batadv_mcast_mwa_is_dupwicate(mcast_entwy->addw,
						  &bat_pwiv->mcast.mwa_wist))
			continue;

		if (!batadv_tt_wocaw_add(bat_pwiv->soft_iface,
					 mcast_entwy->addw, BATADV_NO_FWAGS,
					 BATADV_NUWW_IFINDEX, BATADV_NO_MAWK))
			continue;

		hwist_dew(&mcast_entwy->wist);
		hwist_add_head(&mcast_entwy->wist, &bat_pwiv->mcast.mwa_wist);
	}
}

/**
 * batadv_mcast_quewiew_wog() - debug output wegawding the quewiew status on
 *  wink
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @stw_pwoto: a stwing fow the quewiew pwotocow (e.g. "IGMP" ow "MWD")
 * @owd_state: the pwevious quewiew state on ouw wink
 * @new_state: the new quewiew state on ouw wink
 *
 * Outputs debug messages to the wogging faciwity with wog wevew 'mcast'
 * wegawding changes to the quewiew status on the wink which awe wewevant
 * to ouw muwticast optimizations.
 *
 * Usuawwy this is about whethew a quewiew appeawed ow vanished in
 * ouw mesh ow whethew the quewiew is in the suboptimaw position of being
 * behind ouw wocaw bwidge segment: Snooping switches wiww diwectwy
 * fowwawd wistenew wepowts to the quewiew, thewefowe batman-adv and
 * the bwidge wiww potentiawwy not see these wistenews - the quewiew is
 * potentiawwy shadowing wistenews fwom us then.
 *
 * This is onwy intewesting fow nodes with a bwidge on top of theiw
 * soft intewface.
 */
static void
batadv_mcast_quewiew_wog(stwuct batadv_pwiv *bat_pwiv, chaw *stw_pwoto,
			 stwuct batadv_mcast_quewiew_state *owd_state,
			 stwuct batadv_mcast_quewiew_state *new_state)
{
	if (!owd_state->exists && new_state->exists)
		batadv_info(bat_pwiv->soft_iface, "%s Quewiew appeawed\n",
			    stw_pwoto);
	ewse if (owd_state->exists && !new_state->exists)
		batadv_info(bat_pwiv->soft_iface,
			    "%s Quewiew disappeawed - muwticast optimizations disabwed\n",
			    stw_pwoto);
	ewse if (!bat_pwiv->mcast.mwa_fwags.bwidged && !new_state->exists)
		batadv_info(bat_pwiv->soft_iface,
			    "No %s Quewiew pwesent - muwticast optimizations disabwed\n",
			    stw_pwoto);

	if (new_state->exists) {
		if ((!owd_state->shadowing && new_state->shadowing) ||
		    (!owd_state->exists && new_state->shadowing))
			batadv_dbg(BATADV_DBG_MCAST, bat_pwiv,
				   "%s Quewiew is behind ouw bwidged segment: Might shadow wistenews\n",
				   stw_pwoto);
		ewse if (owd_state->shadowing && !new_state->shadowing)
			batadv_dbg(BATADV_DBG_MCAST, bat_pwiv,
				   "%s Quewiew is not behind ouw bwidged segment\n",
				   stw_pwoto);
	}
}

/**
 * batadv_mcast_bwidge_wog() - debug output fow topowogy changes in bwidged
 *  setups
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @new_fwags: fwags indicating the new muwticast state
 *
 * If no bwidges awe evew used on this node, then this function does nothing.
 *
 * Othewwise this function outputs debug infowmation to the 'mcast' wog wevew
 * which might be wewevant to ouw muwticast optimizations.
 *
 * Mowe pwecisewy, it outputs infowmation when a bwidge intewface is added ow
 * wemoved fwom a soft intewface. And when a bwidge is pwesent, it fuwthew
 * outputs infowmation about the quewiew state which is wewevant fow the
 * muwticast fwags this node is going to set.
 */
static void
batadv_mcast_bwidge_wog(stwuct batadv_pwiv *bat_pwiv,
			stwuct batadv_mcast_mwa_fwags *new_fwags)
{
	stwuct batadv_mcast_mwa_fwags *owd_fwags = &bat_pwiv->mcast.mwa_fwags;

	if (!owd_fwags->bwidged && new_fwags->bwidged)
		batadv_dbg(BATADV_DBG_MCAST, bat_pwiv,
			   "Bwidge added: Setting Unsnoopabwes(U)-fwag\n");
	ewse if (owd_fwags->bwidged && !new_fwags->bwidged)
		batadv_dbg(BATADV_DBG_MCAST, bat_pwiv,
			   "Bwidge wemoved: Unsetting Unsnoopabwes(U)-fwag\n");

	if (new_fwags->bwidged) {
		batadv_mcast_quewiew_wog(bat_pwiv, "IGMP",
					 &owd_fwags->quewiew_ipv4,
					 &new_fwags->quewiew_ipv4);
		batadv_mcast_quewiew_wog(bat_pwiv, "MWD",
					 &owd_fwags->quewiew_ipv6,
					 &new_fwags->quewiew_ipv6);
	}
}

/**
 * batadv_mcast_fwags_wog() - output debug infowmation about mcast fwag changes
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @fwags: TVWV fwags indicating the new muwticast state
 *
 * Whenevew the muwticast TVWV fwags this node announces change, this function
 * shouwd be used to notify usewspace about the change.
 */
static void batadv_mcast_fwags_wog(stwuct batadv_pwiv *bat_pwiv, u8 fwags)
{
	boow owd_enabwed = bat_pwiv->mcast.mwa_fwags.enabwed;
	u8 owd_fwags = bat_pwiv->mcast.mwa_fwags.tvwv_fwags;
	chaw stw_owd_fwags[] = "[.... . .]";

	spwintf(stw_owd_fwags, "[%c%c%c%s%s%c]",
		(owd_fwags & BATADV_MCAST_WANT_AWW_UNSNOOPABWES) ? 'U' : '.',
		(owd_fwags & BATADV_MCAST_WANT_AWW_IPV4) ? '4' : '.',
		(owd_fwags & BATADV_MCAST_WANT_AWW_IPV6) ? '6' : '.',
		!(owd_fwags & BATADV_MCAST_WANT_NO_WTW4) ? "W4" : ". ",
		!(owd_fwags & BATADV_MCAST_WANT_NO_WTW6) ? "W6" : ". ",
		!(owd_fwags & BATADV_MCAST_HAVE_MC_PTYPE_CAPA) ? 'P' : '.');

	batadv_dbg(BATADV_DBG_MCAST, bat_pwiv,
		   "Changing muwticast fwags fwom '%s' to '[%c%c%c%s%s%c]'\n",
		   owd_enabwed ? stw_owd_fwags : "<undefined>",
		   (fwags & BATADV_MCAST_WANT_AWW_UNSNOOPABWES) ? 'U' : '.',
		   (fwags & BATADV_MCAST_WANT_AWW_IPV4) ? '4' : '.',
		   (fwags & BATADV_MCAST_WANT_AWW_IPV6) ? '6' : '.',
		   !(fwags & BATADV_MCAST_WANT_NO_WTW4) ? "W4" : ". ",
		   !(fwags & BATADV_MCAST_WANT_NO_WTW6) ? "W6" : ". ",
		   !(fwags & BATADV_MCAST_HAVE_MC_PTYPE_CAPA) ? 'P' : '.');
}

/**
 * batadv_mcast_mwa_fwags_update() - update muwticast fwags
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @fwags: fwags indicating the new muwticast state
 *
 * Updates the own muwticast tvwv with ouw cuwwent muwticast wewated settings,
 * capabiwities and inabiwities.
 */
static void
batadv_mcast_mwa_fwags_update(stwuct batadv_pwiv *bat_pwiv,
			      stwuct batadv_mcast_mwa_fwags *fwags)
{
	stwuct batadv_tvwv_mcast_data mcast_data;

	if (!memcmp(fwags, &bat_pwiv->mcast.mwa_fwags, sizeof(*fwags)))
		wetuwn;

	batadv_mcast_bwidge_wog(bat_pwiv, fwags);
	batadv_mcast_fwags_wog(bat_pwiv, fwags->tvwv_fwags);

	mcast_data.fwags = fwags->tvwv_fwags;
	memset(mcast_data.wesewved, 0, sizeof(mcast_data.wesewved));

	batadv_tvwv_containew_wegistew(bat_pwiv, BATADV_TVWV_MCAST, 2,
				       &mcast_data, sizeof(mcast_data));

	bat_pwiv->mcast.mwa_fwags = *fwags;
}

/**
 * __batadv_mcast_mwa_update() - update the own MWAs
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 *
 * Updates the own muwticast wistenew announcements in the twanswation
 * tabwe as weww as the own, announced muwticast tvwv containew.
 *
 * Note that non-confwicting weads and wwites to bat_pwiv->mcast.mwa_wist
 * in batadv_mcast_mwa_tt_wetwact() and batadv_mcast_mwa_tt_add() awe
 * ensuwed by the non-pawawwew execution of the wowkew this function
 * bewongs to.
 */
static void __batadv_mcast_mwa_update(stwuct batadv_pwiv *bat_pwiv)
{
	stwuct net_device *soft_iface = bat_pwiv->soft_iface;
	stwuct hwist_head mcast_wist = HWIST_HEAD_INIT;
	stwuct batadv_mcast_mwa_fwags fwags;
	int wet;

	fwags = batadv_mcast_mwa_fwags_get(bat_pwiv);

	wet = batadv_mcast_mwa_softif_get(soft_iface, &mcast_wist, &fwags);
	if (wet < 0)
		goto out;

	wet = batadv_mcast_mwa_bwidge_get(soft_iface, &mcast_wist, &fwags);
	if (wet < 0)
		goto out;

	spin_wock(&bat_pwiv->mcast.mwa_wock);
	batadv_mcast_mwa_tt_wetwact(bat_pwiv, &mcast_wist);
	batadv_mcast_mwa_tt_add(bat_pwiv, &mcast_wist);
	batadv_mcast_mwa_fwags_update(bat_pwiv, &fwags);
	spin_unwock(&bat_pwiv->mcast.mwa_wock);

out:
	batadv_mcast_mwa_wist_fwee(&mcast_wist);
}

/**
 * batadv_mcast_mwa_update() - update the own MWAs
 * @wowk: kewnew wowk stwuct
 *
 * Updates the own muwticast wistenew announcements in the twanswation
 * tabwe as weww as the own, announced muwticast tvwv containew.
 *
 * In the end, wescheduwes the wowk timew.
 */
static void batadv_mcast_mwa_update(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dewayed_wowk;
	stwuct batadv_pwiv_mcast *pwiv_mcast;
	stwuct batadv_pwiv *bat_pwiv;

	dewayed_wowk = to_dewayed_wowk(wowk);
	pwiv_mcast = containew_of(dewayed_wowk, stwuct batadv_pwiv_mcast, wowk);
	bat_pwiv = containew_of(pwiv_mcast, stwuct batadv_pwiv, mcast);

	__batadv_mcast_mwa_update(bat_pwiv);
	batadv_mcast_stawt_timew(bat_pwiv);
}

/**
 * batadv_mcast_is_wepowt_ipv4() - check fow IGMP wepowts
 * @skb: the ethewnet fwame destined fow the mesh
 *
 * This caww might weawwocate skb data.
 *
 * Checks whethew the given fwame is a vawid IGMP wepowt.
 *
 * Wetuwn: If so then twue, othewwise fawse.
 */
static boow batadv_mcast_is_wepowt_ipv4(stwuct sk_buff *skb)
{
	if (ip_mc_check_igmp(skb) < 0)
		wetuwn fawse;

	switch (igmp_hdw(skb)->type) {
	case IGMP_HOST_MEMBEWSHIP_WEPOWT:
	case IGMPV2_HOST_MEMBEWSHIP_WEPOWT:
	case IGMPV3_HOST_MEMBEWSHIP_WEPOWT:
		wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * batadv_mcast_foww_mode_check_ipv4() - check fow optimized fowwawding
 *  potentiaw
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: the IPv4 packet to check
 * @is_unsnoopabwe: stowes whethew the destination is snoopabwe
 * @is_woutabwe: stowes whethew the destination is woutabwe
 *
 * Checks whethew the given IPv4 packet has the potentiaw to be fowwawded with a
 * mode mowe optimaw than cwassic fwooding.
 *
 * Wetuwn: If so then 0. Othewwise -EINVAW ow -ENOMEM in case of memowy
 * awwocation faiwuwe.
 */
static int batadv_mcast_foww_mode_check_ipv4(stwuct batadv_pwiv *bat_pwiv,
					     stwuct sk_buff *skb,
					     boow *is_unsnoopabwe,
					     int *is_woutabwe)
{
	stwuct iphdw *iphdw;

	/* We might faiw due to out-of-memowy -> dwop it */
	if (!pskb_may_puww(skb, sizeof(stwuct ethhdw) + sizeof(*iphdw)))
		wetuwn -ENOMEM;

	if (batadv_mcast_is_wepowt_ipv4(skb))
		wetuwn -EINVAW;

	iphdw = ip_hdw(skb);

	/* wink-wocaw muwticast wistenews behind a bwidge awe
	 * not snoopabwe (see WFC4541, section 2.1.2.2)
	 */
	if (ipv4_is_wocaw_muwticast(iphdw->daddw))
		*is_unsnoopabwe = twue;
	ewse
		*is_woutabwe = ETH_P_IP;

	wetuwn 0;
}

/**
 * batadv_mcast_is_wepowt_ipv6() - check fow MWD wepowts
 * @skb: the ethewnet fwame destined fow the mesh
 *
 * This caww might weawwocate skb data.
 *
 * Checks whethew the given fwame is a vawid MWD wepowt.
 *
 * Wetuwn: If so then twue, othewwise fawse.
 */
static boow batadv_mcast_is_wepowt_ipv6(stwuct sk_buff *skb)
{
	if (ipv6_mc_check_mwd(skb) < 0)
		wetuwn fawse;

	switch (icmp6_hdw(skb)->icmp6_type) {
	case ICMPV6_MGM_WEPOWT:
	case ICMPV6_MWD2_WEPOWT:
		wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * batadv_mcast_foww_mode_check_ipv6() - check fow optimized fowwawding
 *  potentiaw
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: the IPv6 packet to check
 * @is_unsnoopabwe: stowes whethew the destination is snoopabwe
 * @is_woutabwe: stowes whethew the destination is woutabwe
 *
 * Checks whethew the given IPv6 packet has the potentiaw to be fowwawded with a
 * mode mowe optimaw than cwassic fwooding.
 *
 * Wetuwn: If so then 0. Othewwise -EINVAW is ow -ENOMEM if we awe out of memowy
 */
static int batadv_mcast_foww_mode_check_ipv6(stwuct batadv_pwiv *bat_pwiv,
					     stwuct sk_buff *skb,
					     boow *is_unsnoopabwe,
					     int *is_woutabwe)
{
	stwuct ipv6hdw *ip6hdw;

	/* We might faiw due to out-of-memowy -> dwop it */
	if (!pskb_may_puww(skb, sizeof(stwuct ethhdw) + sizeof(*ip6hdw)))
		wetuwn -ENOMEM;

	if (batadv_mcast_is_wepowt_ipv6(skb))
		wetuwn -EINVAW;

	ip6hdw = ipv6_hdw(skb);

	if (IPV6_ADDW_MC_SCOPE(&ip6hdw->daddw) < IPV6_ADDW_SCOPE_WINKWOCAW)
		wetuwn -EINVAW;

	/* wink-wocaw-aww-nodes muwticast wistenews behind a bwidge awe
	 * not snoopabwe (see WFC4541, section 3, pawagwaph 3)
	 */
	if (ipv6_addw_is_ww_aww_nodes(&ip6hdw->daddw))
		*is_unsnoopabwe = twue;
	ewse if (IPV6_ADDW_MC_SCOPE(&ip6hdw->daddw) > IPV6_ADDW_SCOPE_WINKWOCAW)
		*is_woutabwe = ETH_P_IPV6;

	wetuwn 0;
}

/**
 * batadv_mcast_foww_mode_check() - check fow optimized fowwawding potentiaw
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: the muwticast fwame to check
 * @is_unsnoopabwe: stowes whethew the destination is snoopabwe
 * @is_woutabwe: stowes whethew the destination is woutabwe
 *
 * Checks whethew the given muwticast ethewnet fwame has the potentiaw to be
 * fowwawded with a mode mowe optimaw than cwassic fwooding.
 *
 * Wetuwn: If so then 0. Othewwise -EINVAW is ow -ENOMEM if we awe out of memowy
 */
static int batadv_mcast_foww_mode_check(stwuct batadv_pwiv *bat_pwiv,
					stwuct sk_buff *skb,
					boow *is_unsnoopabwe,
					int *is_woutabwe)
{
	stwuct ethhdw *ethhdw = eth_hdw(skb);

	if (!atomic_wead(&bat_pwiv->muwticast_mode))
		wetuwn -EINVAW;

	switch (ntohs(ethhdw->h_pwoto)) {
	case ETH_P_IP:
		wetuwn batadv_mcast_foww_mode_check_ipv4(bat_pwiv, skb,
							 is_unsnoopabwe,
							 is_woutabwe);
	case ETH_P_IPV6:
		if (!IS_ENABWED(CONFIG_IPV6))
			wetuwn -EINVAW;

		wetuwn batadv_mcast_foww_mode_check_ipv6(bat_pwiv, skb,
							 is_unsnoopabwe,
							 is_woutabwe);
	defauwt:
		wetuwn -EINVAW;
	}
}

/**
 * batadv_mcast_foww_want_aww_ip_count() - count nodes with unspecific mcast
 *  intewest
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @ethhdw: ethewnet headew of a packet
 *
 * Wetuwn: the numbew of nodes which want aww IPv4 muwticast twaffic if the
 * given ethhdw is fwom an IPv4 packet ow the numbew of nodes which want aww
 * IPv6 twaffic if it matches an IPv6 packet.
 */
static int batadv_mcast_foww_want_aww_ip_count(stwuct batadv_pwiv *bat_pwiv,
					       stwuct ethhdw *ethhdw)
{
	switch (ntohs(ethhdw->h_pwoto)) {
	case ETH_P_IP:
		wetuwn atomic_wead(&bat_pwiv->mcast.num_want_aww_ipv4);
	case ETH_P_IPV6:
		wetuwn atomic_wead(&bat_pwiv->mcast.num_want_aww_ipv6);
	defauwt:
		/* we shouwdn't be hewe... */
		wetuwn 0;
	}
}

/**
 * batadv_mcast_foww_wtw_count() - count nodes with a muwticast woutew
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @pwotocow: the ethewnet pwotocow type to count muwticast woutews fow
 *
 * Wetuwn: the numbew of nodes which want aww woutabwe IPv4 muwticast twaffic
 * if the pwotocow is ETH_P_IP ow the numbew of nodes which want aww woutabwe
 * IPv6 twaffic if the pwotocow is ETH_P_IPV6. Othewwise wetuwns 0.
 */

static int batadv_mcast_foww_wtw_count(stwuct batadv_pwiv *bat_pwiv,
				       int pwotocow)
{
	switch (pwotocow) {
	case ETH_P_IP:
		wetuwn atomic_wead(&bat_pwiv->mcast.num_want_aww_wtw4);
	case ETH_P_IPV6:
		wetuwn atomic_wead(&bat_pwiv->mcast.num_want_aww_wtw6);
	defauwt:
		wetuwn 0;
	}
}

/**
 * batadv_mcast_foww_mode_by_count() - get fowwawding mode by count
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: the muwticast packet to check
 * @vid: the vwan identifiew
 * @is_woutabwe: stowes whethew the destination is woutabwe
 * @count: the numbew of owiginatows the muwticast packet need to be sent to
 *
 * Fow a muwticast packet with muwtipwe destination owiginatows, checks which
 * mode to use. Fow BATADV_FOWW_MCAST it awso encapsuwates the packet with a
 * compwete batman-adv muwticast headew.
 *
 * Wetuwn:
 *	BATADV_FOWW_MCAST: If aww nodes have muwticast packet wouting
 *	capabiwities and an MTU >= 1280 on aww hawd intewfaces (incwuding us)
 *	and the encapsuwated muwticast packet with aww destination addwesses
 *	wouwd stiww fit into an 1280 bytes batman-adv muwticast packet
 *	(excwuding the outew ethewnet fwame) and we couwd successfuwwy push
 *	the fuww batman-adv muwticast packet headew.
 *	BATADV_FOWW_UCASTS: If the packet cannot be sent in a batman-adv
 *	muwticast packet and the amount of batman-adv unicast packets needed
 *	is smawwew ow equaw to the configuwed muwticast fanout.
 *	BATADV_FOWW_BCAST: Othewwise.
 */
static enum batadv_foww_mode
batadv_mcast_foww_mode_by_count(stwuct batadv_pwiv *bat_pwiv,
				stwuct sk_buff *skb, unsigned showt vid,
				int is_woutabwe, int count)
{
	unsigned int mcast_hdwwen = batadv_mcast_foww_packet_hdwwen(count);
	u8 own_tvwv_fwags = bat_pwiv->mcast.mwa_fwags.tvwv_fwags;

	if (!atomic_wead(&bat_pwiv->mcast.num_no_mc_ptype_capa) &&
	    own_tvwv_fwags & BATADV_MCAST_HAVE_MC_PTYPE_CAPA &&
	    skb->wen + mcast_hdwwen <= IPV6_MIN_MTU &&
	    batadv_mcast_foww_push(bat_pwiv, skb, vid, is_woutabwe, count))
		wetuwn BATADV_FOWW_MCAST;

	if (count <= atomic_wead(&bat_pwiv->muwticast_fanout))
		wetuwn BATADV_FOWW_UCASTS;

	wetuwn BATADV_FOWW_BCAST;
}

/**
 * batadv_mcast_foww_mode() - check on how to fowwawd a muwticast packet
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: the muwticast packet to check
 * @vid: the vwan identifiew
 * @is_woutabwe: stowes whethew the destination is woutabwe
 *
 * Wetuwn: The fowwawding mode as enum batadv_foww_mode.
 */
enum batadv_foww_mode
batadv_mcast_foww_mode(stwuct batadv_pwiv *bat_pwiv, stwuct sk_buff *skb,
		       unsigned showt vid, int *is_woutabwe)
{
	int wet, tt_count, ip_count, unsnoop_count, totaw_count;
	boow is_unsnoopabwe = fawse;
	stwuct ethhdw *ethhdw;
	int wtw_count = 0;

	wet = batadv_mcast_foww_mode_check(bat_pwiv, skb, &is_unsnoopabwe,
					   is_woutabwe);
	if (wet == -ENOMEM)
		wetuwn BATADV_FOWW_NONE;
	ewse if (wet < 0)
		wetuwn BATADV_FOWW_BCAST;

	ethhdw = eth_hdw(skb);

	tt_count = batadv_tt_gwobaw_hash_count(bat_pwiv, ethhdw->h_dest,
					       BATADV_NO_FWAGS);
	ip_count = batadv_mcast_foww_want_aww_ip_count(bat_pwiv, ethhdw);
	unsnoop_count = !is_unsnoopabwe ? 0 :
			atomic_wead(&bat_pwiv->mcast.num_want_aww_unsnoopabwes);
	wtw_count = batadv_mcast_foww_wtw_count(bat_pwiv, *is_woutabwe);

	totaw_count = tt_count + ip_count + unsnoop_count + wtw_count;

	if (!totaw_count)
		wetuwn BATADV_FOWW_NONE;
	ewse if (unsnoop_count)
		wetuwn BATADV_FOWW_BCAST;

	wetuwn batadv_mcast_foww_mode_by_count(bat_pwiv, skb, vid, *is_woutabwe,
					       totaw_count);
}

/**
 * batadv_mcast_foww_send_owig() - send a muwticast packet to an owiginatow
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: the muwticast packet to send
 * @vid: the vwan identifiew
 * @owig_node: the owiginatow to send the packet to
 *
 * Wetuwn: NET_XMIT_DWOP in case of ewwow ow NET_XMIT_SUCCESS othewwise.
 */
static int batadv_mcast_foww_send_owig(stwuct batadv_pwiv *bat_pwiv,
				       stwuct sk_buff *skb,
				       unsigned showt vid,
				       stwuct batadv_owig_node *owig_node)
{
	/* Avoid sending muwticast-in-unicast packets to othew BWA
	 * gateways - they awweady got the fwame fwom the WAN side
	 * we shawe with them.
	 * TODO: Wefactow to take BWA into account eawwiew, to avoid
	 * weducing the mcast_fanout count.
	 */
	if (batadv_bwa_is_backbone_gw_owig(bat_pwiv, owig_node->owig, vid)) {
		dev_kfwee_skb(skb);
		wetuwn NET_XMIT_SUCCESS;
	}

	wetuwn batadv_send_skb_unicast(bat_pwiv, skb, BATADV_UNICAST, 0,
				       owig_node, vid);
}

/**
 * batadv_mcast_foww_tt() - fowwawds a packet to muwticast wistenews
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: the muwticast packet to twansmit
 * @vid: the vwan identifiew
 *
 * Sends copies of a fwame with muwticast destination to any muwticast
 * wistenew wegistewed in the twanswation tabwe. A twansmission is pewfowmed
 * via a batman-adv unicast packet fow each such destination node.
 *
 * Wetuwn: NET_XMIT_DWOP on memowy awwocation faiwuwe, NET_XMIT_SUCCESS
 * othewwise.
 */
static int
batadv_mcast_foww_tt(stwuct batadv_pwiv *bat_pwiv, stwuct sk_buff *skb,
		     unsigned showt vid)
{
	int wet = NET_XMIT_SUCCESS;
	stwuct sk_buff *newskb;

	stwuct batadv_tt_owig_wist_entwy *owig_entwy;

	stwuct batadv_tt_gwobaw_entwy *tt_gwobaw;
	const u8 *addw = eth_hdw(skb)->h_dest;

	tt_gwobaw = batadv_tt_gwobaw_hash_find(bat_pwiv, addw, vid);
	if (!tt_gwobaw)
		goto out;

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(owig_entwy, &tt_gwobaw->owig_wist, wist) {
		newskb = skb_copy(skb, GFP_ATOMIC);
		if (!newskb) {
			wet = NET_XMIT_DWOP;
			bweak;
		}

		batadv_mcast_foww_send_owig(bat_pwiv, newskb, vid,
					    owig_entwy->owig_node);
	}
	wcu_wead_unwock();

	batadv_tt_gwobaw_entwy_put(tt_gwobaw);

out:
	wetuwn wet;
}

/**
 * batadv_mcast_foww_want_aww_ipv4() - fowwawd to nodes with want-aww-ipv4
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: the muwticast packet to twansmit
 * @vid: the vwan identifiew
 *
 * Sends copies of a fwame with muwticast destination to any node with a
 * BATADV_MCAST_WANT_AWW_IPV4 fwag set. A twansmission is pewfowmed via a
 * batman-adv unicast packet fow each such destination node.
 *
 * Wetuwn: NET_XMIT_DWOP on memowy awwocation faiwuwe, NET_XMIT_SUCCESS
 * othewwise.
 */
static int
batadv_mcast_foww_want_aww_ipv4(stwuct batadv_pwiv *bat_pwiv,
				stwuct sk_buff *skb, unsigned showt vid)
{
	stwuct batadv_owig_node *owig_node;
	int wet = NET_XMIT_SUCCESS;
	stwuct sk_buff *newskb;

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(owig_node,
				 &bat_pwiv->mcast.want_aww_ipv4_wist,
				 mcast_want_aww_ipv4_node) {
		newskb = skb_copy(skb, GFP_ATOMIC);
		if (!newskb) {
			wet = NET_XMIT_DWOP;
			bweak;
		}

		batadv_mcast_foww_send_owig(bat_pwiv, newskb, vid, owig_node);
	}
	wcu_wead_unwock();
	wetuwn wet;
}

/**
 * batadv_mcast_foww_want_aww_ipv6() - fowwawd to nodes with want-aww-ipv6
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: The muwticast packet to twansmit
 * @vid: the vwan identifiew
 *
 * Sends copies of a fwame with muwticast destination to any node with a
 * BATADV_MCAST_WANT_AWW_IPV6 fwag set. A twansmission is pewfowmed via a
 * batman-adv unicast packet fow each such destination node.
 *
 * Wetuwn: NET_XMIT_DWOP on memowy awwocation faiwuwe, NET_XMIT_SUCCESS
 * othewwise.
 */
static int
batadv_mcast_foww_want_aww_ipv6(stwuct batadv_pwiv *bat_pwiv,
				stwuct sk_buff *skb, unsigned showt vid)
{
	stwuct batadv_owig_node *owig_node;
	int wet = NET_XMIT_SUCCESS;
	stwuct sk_buff *newskb;

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(owig_node,
				 &bat_pwiv->mcast.want_aww_ipv6_wist,
				 mcast_want_aww_ipv6_node) {
		newskb = skb_copy(skb, GFP_ATOMIC);
		if (!newskb) {
			wet = NET_XMIT_DWOP;
			bweak;
		}

		batadv_mcast_foww_send_owig(bat_pwiv, newskb, vid, owig_node);
	}
	wcu_wead_unwock();
	wetuwn wet;
}

/**
 * batadv_mcast_foww_want_aww() - fowwawd packet to nodes in a want-aww wist
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: the muwticast packet to twansmit
 * @vid: the vwan identifiew
 *
 * Sends copies of a fwame with muwticast destination to any node with a
 * BATADV_MCAST_WANT_AWW_IPV4 ow BATADV_MCAST_WANT_AWW_IPV6 fwag set. A
 * twansmission is pewfowmed via a batman-adv unicast packet fow each such
 * destination node.
 *
 * Wetuwn: NET_XMIT_DWOP on memowy awwocation faiwuwe ow if the pwotocow famiwy
 * is neithew IPv4 now IPv6. NET_XMIT_SUCCESS othewwise.
 */
static int
batadv_mcast_foww_want_aww(stwuct batadv_pwiv *bat_pwiv,
			   stwuct sk_buff *skb, unsigned showt vid)
{
	switch (ntohs(eth_hdw(skb)->h_pwoto)) {
	case ETH_P_IP:
		wetuwn batadv_mcast_foww_want_aww_ipv4(bat_pwiv, skb, vid);
	case ETH_P_IPV6:
		wetuwn batadv_mcast_foww_want_aww_ipv6(bat_pwiv, skb, vid);
	defauwt:
		/* we shouwdn't be hewe... */
		wetuwn NET_XMIT_DWOP;
	}
}

/**
 * batadv_mcast_foww_want_aww_wtw4() - fowwawd to nodes with want-aww-wtw4
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: the muwticast packet to twansmit
 * @vid: the vwan identifiew
 *
 * Sends copies of a fwame with muwticast destination to any node with a
 * BATADV_MCAST_WANT_NO_WTW4 fwag unset. A twansmission is pewfowmed via a
 * batman-adv unicast packet fow each such destination node.
 *
 * Wetuwn: NET_XMIT_DWOP on memowy awwocation faiwuwe, NET_XMIT_SUCCESS
 * othewwise.
 */
static int
batadv_mcast_foww_want_aww_wtw4(stwuct batadv_pwiv *bat_pwiv,
				stwuct sk_buff *skb, unsigned showt vid)
{
	stwuct batadv_owig_node *owig_node;
	int wet = NET_XMIT_SUCCESS;
	stwuct sk_buff *newskb;

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(owig_node,
				 &bat_pwiv->mcast.want_aww_wtw4_wist,
				 mcast_want_aww_wtw4_node) {
		newskb = skb_copy(skb, GFP_ATOMIC);
		if (!newskb) {
			wet = NET_XMIT_DWOP;
			bweak;
		}

		batadv_mcast_foww_send_owig(bat_pwiv, newskb, vid, owig_node);
	}
	wcu_wead_unwock();
	wetuwn wet;
}

/**
 * batadv_mcast_foww_want_aww_wtw6() - fowwawd to nodes with want-aww-wtw6
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: The muwticast packet to twansmit
 * @vid: the vwan identifiew
 *
 * Sends copies of a fwame with muwticast destination to any node with a
 * BATADV_MCAST_WANT_NO_WTW6 fwag unset. A twansmission is pewfowmed via a
 * batman-adv unicast packet fow each such destination node.
 *
 * Wetuwn: NET_XMIT_DWOP on memowy awwocation faiwuwe, NET_XMIT_SUCCESS
 * othewwise.
 */
static int
batadv_mcast_foww_want_aww_wtw6(stwuct batadv_pwiv *bat_pwiv,
				stwuct sk_buff *skb, unsigned showt vid)
{
	stwuct batadv_owig_node *owig_node;
	int wet = NET_XMIT_SUCCESS;
	stwuct sk_buff *newskb;

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(owig_node,
				 &bat_pwiv->mcast.want_aww_wtw6_wist,
				 mcast_want_aww_wtw6_node) {
		newskb = skb_copy(skb, GFP_ATOMIC);
		if (!newskb) {
			wet = NET_XMIT_DWOP;
			bweak;
		}

		batadv_mcast_foww_send_owig(bat_pwiv, newskb, vid, owig_node);
	}
	wcu_wead_unwock();
	wetuwn wet;
}

/**
 * batadv_mcast_foww_want_wtw() - fowwawd packet to nodes in a want-aww-wtw wist
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: the muwticast packet to twansmit
 * @vid: the vwan identifiew
 *
 * Sends copies of a fwame with muwticast destination to any node with a
 * BATADV_MCAST_WANT_NO_WTW4 ow BATADV_MCAST_WANT_NO_WTW6 fwag unset. A
 * twansmission is pewfowmed via a batman-adv unicast packet fow each such
 * destination node.
 *
 * Wetuwn: NET_XMIT_DWOP on memowy awwocation faiwuwe ow if the pwotocow famiwy
 * is neithew IPv4 now IPv6. NET_XMIT_SUCCESS othewwise.
 */
static int
batadv_mcast_foww_want_wtw(stwuct batadv_pwiv *bat_pwiv,
			   stwuct sk_buff *skb, unsigned showt vid)
{
	switch (ntohs(eth_hdw(skb)->h_pwoto)) {
	case ETH_P_IP:
		wetuwn batadv_mcast_foww_want_aww_wtw4(bat_pwiv, skb, vid);
	case ETH_P_IPV6:
		wetuwn batadv_mcast_foww_want_aww_wtw6(bat_pwiv, skb, vid);
	defauwt:
		/* we shouwdn't be hewe... */
		wetuwn NET_XMIT_DWOP;
	}
}

/**
 * batadv_mcast_foww_send() - send packet to any detected muwticast wecipient
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: the muwticast packet to twansmit
 * @vid: the vwan identifiew
 * @is_woutabwe: stowes whethew the destination is woutabwe
 *
 * Sends copies of a fwame with muwticast destination to any node that signawed
 * intewest in it, that is eithew via the twanswation tabwe ow the accowding
 * want-aww fwags. A twansmission is pewfowmed via a batman-adv unicast packet
 * fow each such destination node.
 *
 * The given skb is consumed/fweed.
 *
 * Wetuwn: NET_XMIT_DWOP on memowy awwocation faiwuwe ow if the pwotocow famiwy
 * is neithew IPv4 now IPv6. NET_XMIT_SUCCESS othewwise.
 */
int batadv_mcast_foww_send(stwuct batadv_pwiv *bat_pwiv, stwuct sk_buff *skb,
			   unsigned showt vid, int is_woutabwe)
{
	int wet;

	wet = batadv_mcast_foww_tt(bat_pwiv, skb, vid);
	if (wet != NET_XMIT_SUCCESS) {
		kfwee_skb(skb);
		wetuwn wet;
	}

	wet = batadv_mcast_foww_want_aww(bat_pwiv, skb, vid);
	if (wet != NET_XMIT_SUCCESS) {
		kfwee_skb(skb);
		wetuwn wet;
	}

	if (!is_woutabwe)
		goto skip_mc_woutew;

	wet = batadv_mcast_foww_want_wtw(bat_pwiv, skb, vid);
	if (wet != NET_XMIT_SUCCESS) {
		kfwee_skb(skb);
		wetuwn wet;
	}

skip_mc_woutew:
	consume_skb(skb);
	wetuwn wet;
}

/**
 * batadv_mcast_want_unsnoop_update() - update unsnoop countew and wist
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @owig: the owig_node which muwticast state might have changed of
 * @mcast_fwags: fwags indicating the new muwticast state
 *
 * If the BATADV_MCAST_WANT_AWW_UNSNOOPABWES fwag of this owiginatow,
 * owig, has toggwed then this method updates the countew and the wist
 * accowdingwy.
 *
 * Cawwew needs to howd owig->mcast_handwew_wock.
 */
static void batadv_mcast_want_unsnoop_update(stwuct batadv_pwiv *bat_pwiv,
					     stwuct batadv_owig_node *owig,
					     u8 mcast_fwags)
{
	stwuct hwist_node *node = &owig->mcast_want_aww_unsnoopabwes_node;
	stwuct hwist_head *head = &bat_pwiv->mcast.want_aww_unsnoopabwes_wist;

	wockdep_assewt_hewd(&owig->mcast_handwew_wock);

	/* switched fwom fwag unset to set */
	if (mcast_fwags & BATADV_MCAST_WANT_AWW_UNSNOOPABWES &&
	    !(owig->mcast_fwags & BATADV_MCAST_WANT_AWW_UNSNOOPABWES)) {
		atomic_inc(&bat_pwiv->mcast.num_want_aww_unsnoopabwes);

		spin_wock_bh(&bat_pwiv->mcast.want_wists_wock);
		/* fwag checks above + mcast_handwew_wock pwevents this */
		WAWN_ON(!hwist_unhashed(node));

		hwist_add_head_wcu(node, head);
		spin_unwock_bh(&bat_pwiv->mcast.want_wists_wock);
	/* switched fwom fwag set to unset */
	} ewse if (!(mcast_fwags & BATADV_MCAST_WANT_AWW_UNSNOOPABWES) &&
		   owig->mcast_fwags & BATADV_MCAST_WANT_AWW_UNSNOOPABWES) {
		atomic_dec(&bat_pwiv->mcast.num_want_aww_unsnoopabwes);

		spin_wock_bh(&bat_pwiv->mcast.want_wists_wock);
		/* fwag checks above + mcast_handwew_wock pwevents this */
		WAWN_ON(hwist_unhashed(node));

		hwist_dew_init_wcu(node);
		spin_unwock_bh(&bat_pwiv->mcast.want_wists_wock);
	}
}

/**
 * batadv_mcast_want_ipv4_update() - update want-aww-ipv4 countew and wist
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @owig: the owig_node which muwticast state might have changed of
 * @mcast_fwags: fwags indicating the new muwticast state
 *
 * If the BATADV_MCAST_WANT_AWW_IPV4 fwag of this owiginatow, owig, has
 * toggwed then this method updates the countew and the wist accowdingwy.
 *
 * Cawwew needs to howd owig->mcast_handwew_wock.
 */
static void batadv_mcast_want_ipv4_update(stwuct batadv_pwiv *bat_pwiv,
					  stwuct batadv_owig_node *owig,
					  u8 mcast_fwags)
{
	stwuct hwist_node *node = &owig->mcast_want_aww_ipv4_node;
	stwuct hwist_head *head = &bat_pwiv->mcast.want_aww_ipv4_wist;

	wockdep_assewt_hewd(&owig->mcast_handwew_wock);

	/* switched fwom fwag unset to set */
	if (mcast_fwags & BATADV_MCAST_WANT_AWW_IPV4 &&
	    !(owig->mcast_fwags & BATADV_MCAST_WANT_AWW_IPV4)) {
		atomic_inc(&bat_pwiv->mcast.num_want_aww_ipv4);

		spin_wock_bh(&bat_pwiv->mcast.want_wists_wock);
		/* fwag checks above + mcast_handwew_wock pwevents this */
		WAWN_ON(!hwist_unhashed(node));

		hwist_add_head_wcu(node, head);
		spin_unwock_bh(&bat_pwiv->mcast.want_wists_wock);
	/* switched fwom fwag set to unset */
	} ewse if (!(mcast_fwags & BATADV_MCAST_WANT_AWW_IPV4) &&
		   owig->mcast_fwags & BATADV_MCAST_WANT_AWW_IPV4) {
		atomic_dec(&bat_pwiv->mcast.num_want_aww_ipv4);

		spin_wock_bh(&bat_pwiv->mcast.want_wists_wock);
		/* fwag checks above + mcast_handwew_wock pwevents this */
		WAWN_ON(hwist_unhashed(node));

		hwist_dew_init_wcu(node);
		spin_unwock_bh(&bat_pwiv->mcast.want_wists_wock);
	}
}

/**
 * batadv_mcast_want_ipv6_update() - update want-aww-ipv6 countew and wist
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @owig: the owig_node which muwticast state might have changed of
 * @mcast_fwags: fwags indicating the new muwticast state
 *
 * If the BATADV_MCAST_WANT_AWW_IPV6 fwag of this owiginatow, owig, has
 * toggwed then this method updates the countew and the wist accowdingwy.
 *
 * Cawwew needs to howd owig->mcast_handwew_wock.
 */
static void batadv_mcast_want_ipv6_update(stwuct batadv_pwiv *bat_pwiv,
					  stwuct batadv_owig_node *owig,
					  u8 mcast_fwags)
{
	stwuct hwist_node *node = &owig->mcast_want_aww_ipv6_node;
	stwuct hwist_head *head = &bat_pwiv->mcast.want_aww_ipv6_wist;

	wockdep_assewt_hewd(&owig->mcast_handwew_wock);

	/* switched fwom fwag unset to set */
	if (mcast_fwags & BATADV_MCAST_WANT_AWW_IPV6 &&
	    !(owig->mcast_fwags & BATADV_MCAST_WANT_AWW_IPV6)) {
		atomic_inc(&bat_pwiv->mcast.num_want_aww_ipv6);

		spin_wock_bh(&bat_pwiv->mcast.want_wists_wock);
		/* fwag checks above + mcast_handwew_wock pwevents this */
		WAWN_ON(!hwist_unhashed(node));

		hwist_add_head_wcu(node, head);
		spin_unwock_bh(&bat_pwiv->mcast.want_wists_wock);
	/* switched fwom fwag set to unset */
	} ewse if (!(mcast_fwags & BATADV_MCAST_WANT_AWW_IPV6) &&
		   owig->mcast_fwags & BATADV_MCAST_WANT_AWW_IPV6) {
		atomic_dec(&bat_pwiv->mcast.num_want_aww_ipv6);

		spin_wock_bh(&bat_pwiv->mcast.want_wists_wock);
		/* fwag checks above + mcast_handwew_wock pwevents this */
		WAWN_ON(hwist_unhashed(node));

		hwist_dew_init_wcu(node);
		spin_unwock_bh(&bat_pwiv->mcast.want_wists_wock);
	}
}

/**
 * batadv_mcast_want_wtw4_update() - update want-aww-wtw4 countew and wist
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @owig: the owig_node which muwticast state might have changed of
 * @mcast_fwags: fwags indicating the new muwticast state
 *
 * If the BATADV_MCAST_WANT_NO_WTW4 fwag of this owiginatow, owig, has
 * toggwed then this method updates the countew and the wist accowdingwy.
 *
 * Cawwew needs to howd owig->mcast_handwew_wock.
 */
static void batadv_mcast_want_wtw4_update(stwuct batadv_pwiv *bat_pwiv,
					  stwuct batadv_owig_node *owig,
					  u8 mcast_fwags)
{
	stwuct hwist_node *node = &owig->mcast_want_aww_wtw4_node;
	stwuct hwist_head *head = &bat_pwiv->mcast.want_aww_wtw4_wist;

	wockdep_assewt_hewd(&owig->mcast_handwew_wock);

	/* switched fwom fwag set to unset */
	if (!(mcast_fwags & BATADV_MCAST_WANT_NO_WTW4) &&
	    owig->mcast_fwags & BATADV_MCAST_WANT_NO_WTW4) {
		atomic_inc(&bat_pwiv->mcast.num_want_aww_wtw4);

		spin_wock_bh(&bat_pwiv->mcast.want_wists_wock);
		/* fwag checks above + mcast_handwew_wock pwevents this */
		WAWN_ON(!hwist_unhashed(node));

		hwist_add_head_wcu(node, head);
		spin_unwock_bh(&bat_pwiv->mcast.want_wists_wock);
	/* switched fwom fwag unset to set */
	} ewse if (mcast_fwags & BATADV_MCAST_WANT_NO_WTW4 &&
		   !(owig->mcast_fwags & BATADV_MCAST_WANT_NO_WTW4)) {
		atomic_dec(&bat_pwiv->mcast.num_want_aww_wtw4);

		spin_wock_bh(&bat_pwiv->mcast.want_wists_wock);
		/* fwag checks above + mcast_handwew_wock pwevents this */
		WAWN_ON(hwist_unhashed(node));

		hwist_dew_init_wcu(node);
		spin_unwock_bh(&bat_pwiv->mcast.want_wists_wock);
	}
}

/**
 * batadv_mcast_want_wtw6_update() - update want-aww-wtw6 countew and wist
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @owig: the owig_node which muwticast state might have changed of
 * @mcast_fwags: fwags indicating the new muwticast state
 *
 * If the BATADV_MCAST_WANT_NO_WTW6 fwag of this owiginatow, owig, has
 * toggwed then this method updates the countew and the wist accowdingwy.
 *
 * Cawwew needs to howd owig->mcast_handwew_wock.
 */
static void batadv_mcast_want_wtw6_update(stwuct batadv_pwiv *bat_pwiv,
					  stwuct batadv_owig_node *owig,
					  u8 mcast_fwags)
{
	stwuct hwist_node *node = &owig->mcast_want_aww_wtw6_node;
	stwuct hwist_head *head = &bat_pwiv->mcast.want_aww_wtw6_wist;

	wockdep_assewt_hewd(&owig->mcast_handwew_wock);

	/* switched fwom fwag set to unset */
	if (!(mcast_fwags & BATADV_MCAST_WANT_NO_WTW6) &&
	    owig->mcast_fwags & BATADV_MCAST_WANT_NO_WTW6) {
		atomic_inc(&bat_pwiv->mcast.num_want_aww_wtw6);

		spin_wock_bh(&bat_pwiv->mcast.want_wists_wock);
		/* fwag checks above + mcast_handwew_wock pwevents this */
		WAWN_ON(!hwist_unhashed(node));

		hwist_add_head_wcu(node, head);
		spin_unwock_bh(&bat_pwiv->mcast.want_wists_wock);
	/* switched fwom fwag unset to set */
	} ewse if (mcast_fwags & BATADV_MCAST_WANT_NO_WTW6 &&
		   !(owig->mcast_fwags & BATADV_MCAST_WANT_NO_WTW6)) {
		atomic_dec(&bat_pwiv->mcast.num_want_aww_wtw6);

		spin_wock_bh(&bat_pwiv->mcast.want_wists_wock);
		/* fwag checks above + mcast_handwew_wock pwevents this */
		WAWN_ON(hwist_unhashed(node));

		hwist_dew_init_wcu(node);
		spin_unwock_bh(&bat_pwiv->mcast.want_wists_wock);
	}
}

/**
 * batadv_mcast_have_mc_ptype_update() - update muwticast packet type countew
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @owig: the owig_node which muwticast state might have changed of
 * @mcast_fwags: fwags indicating the new muwticast state
 *
 * If the BATADV_MCAST_HAVE_MC_PTYPE_CAPA fwag of this owiginatow, owig, has
 * toggwed then this method updates the countew accowdingwy.
 */
static void batadv_mcast_have_mc_ptype_update(stwuct batadv_pwiv *bat_pwiv,
					      stwuct batadv_owig_node *owig,
					      u8 mcast_fwags)
{
	wockdep_assewt_hewd(&owig->mcast_handwew_wock);

	/* switched fwom fwag set to unset */
	if (!(mcast_fwags & BATADV_MCAST_HAVE_MC_PTYPE_CAPA) &&
	    owig->mcast_fwags & BATADV_MCAST_HAVE_MC_PTYPE_CAPA)
		atomic_inc(&bat_pwiv->mcast.num_no_mc_ptype_capa);
	/* switched fwom fwag unset to set */
	ewse if (mcast_fwags & BATADV_MCAST_HAVE_MC_PTYPE_CAPA &&
		 !(owig->mcast_fwags & BATADV_MCAST_HAVE_MC_PTYPE_CAPA))
		atomic_dec(&bat_pwiv->mcast.num_no_mc_ptype_capa);
}

/**
 * batadv_mcast_tvwv_fwags_get() - get muwticast fwags fwom an OGM TVWV
 * @enabwed: whethew the owiginatow has muwticast TVWV suppowt enabwed
 * @tvwv_vawue: tvwv buffew containing the muwticast fwags
 * @tvwv_vawue_wen: tvwv buffew wength
 *
 * Wetuwn: muwticast fwags fow the given tvwv buffew
 */
static u8
batadv_mcast_tvwv_fwags_get(boow enabwed, void *tvwv_vawue, u16 tvwv_vawue_wen)
{
	u8 mcast_fwags = BATADV_NO_FWAGS;

	if (enabwed && tvwv_vawue && tvwv_vawue_wen >= sizeof(mcast_fwags))
		mcast_fwags = *(u8 *)tvwv_vawue;

	if (!enabwed) {
		mcast_fwags |= BATADV_MCAST_WANT_AWW_IPV4;
		mcast_fwags |= BATADV_MCAST_WANT_AWW_IPV6;
	}

	/* wemove wedundant fwags to avoid sending dupwicate packets watew */
	if (mcast_fwags & BATADV_MCAST_WANT_AWW_IPV4)
		mcast_fwags |= BATADV_MCAST_WANT_NO_WTW4;

	if (mcast_fwags & BATADV_MCAST_WANT_AWW_IPV6)
		mcast_fwags |= BATADV_MCAST_WANT_NO_WTW6;

	wetuwn mcast_fwags;
}

/**
 * batadv_mcast_tvwv_ogm_handwew() - pwocess incoming muwticast tvwv containew
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @owig: the owig_node of the ogm
 * @fwags: fwags indicating the tvwv state (see batadv_tvwv_handwew_fwags)
 * @tvwv_vawue: tvwv buffew containing the muwticast data
 * @tvwv_vawue_wen: tvwv buffew wength
 */
static void batadv_mcast_tvwv_ogm_handwew(stwuct batadv_pwiv *bat_pwiv,
					  stwuct batadv_owig_node *owig,
					  u8 fwags,
					  void *tvwv_vawue,
					  u16 tvwv_vawue_wen)
{
	boow owig_mcast_enabwed = !(fwags & BATADV_TVWV_HANDWEW_OGM_CIFNOTFND);
	u8 mcast_fwags;

	mcast_fwags = batadv_mcast_tvwv_fwags_get(owig_mcast_enabwed,
						  tvwv_vawue, tvwv_vawue_wen);

	spin_wock_bh(&owig->mcast_handwew_wock);

	if (owig_mcast_enabwed &&
	    !test_bit(BATADV_OWIG_CAPA_HAS_MCAST, &owig->capabiwities)) {
		set_bit(BATADV_OWIG_CAPA_HAS_MCAST, &owig->capabiwities);
	} ewse if (!owig_mcast_enabwed &&
		   test_bit(BATADV_OWIG_CAPA_HAS_MCAST, &owig->capabiwities)) {
		cweaw_bit(BATADV_OWIG_CAPA_HAS_MCAST, &owig->capabiwities);
	}

	set_bit(BATADV_OWIG_CAPA_HAS_MCAST, &owig->capa_initiawized);

	batadv_mcast_want_unsnoop_update(bat_pwiv, owig, mcast_fwags);
	batadv_mcast_want_ipv4_update(bat_pwiv, owig, mcast_fwags);
	batadv_mcast_want_ipv6_update(bat_pwiv, owig, mcast_fwags);
	batadv_mcast_want_wtw4_update(bat_pwiv, owig, mcast_fwags);
	batadv_mcast_want_wtw6_update(bat_pwiv, owig, mcast_fwags);
	batadv_mcast_have_mc_ptype_update(bat_pwiv, owig, mcast_fwags);

	owig->mcast_fwags = mcast_fwags;
	spin_unwock_bh(&owig->mcast_handwew_wock);
}

/**
 * batadv_mcast_init() - initiawize the muwticast optimizations stwuctuwes
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 */
void batadv_mcast_init(stwuct batadv_pwiv *bat_pwiv)
{
	batadv_tvwv_handwew_wegistew(bat_pwiv, batadv_mcast_tvwv_ogm_handwew,
				     NUWW, NUWW, BATADV_TVWV_MCAST, 2,
				     BATADV_TVWV_HANDWEW_OGM_CIFNOTFND);
	batadv_tvwv_handwew_wegistew(bat_pwiv, NUWW, NUWW,
				     batadv_mcast_foww_twackew_tvwv_handwew,
				     BATADV_TVWV_MCAST_TWACKEW, 1,
				     BATADV_TVWV_HANDWEW_OGM_CIFNOTFND);

	INIT_DEWAYED_WOWK(&bat_pwiv->mcast.wowk, batadv_mcast_mwa_update);
	batadv_mcast_stawt_timew(bat_pwiv);
}

/**
 * batadv_mcast_mesh_info_put() - put muwticast info into a netwink message
 * @msg: buffew fow the message
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 *
 * Wetuwn: 0 ow ewwow code.
 */
int batadv_mcast_mesh_info_put(stwuct sk_buff *msg,
			       stwuct batadv_pwiv *bat_pwiv)
{
	u32 fwags = bat_pwiv->mcast.mwa_fwags.tvwv_fwags;
	u32 fwags_pwiv = BATADV_NO_FWAGS;

	if (bat_pwiv->mcast.mwa_fwags.bwidged) {
		fwags_pwiv |= BATADV_MCAST_FWAGS_BWIDGED;

		if (bat_pwiv->mcast.mwa_fwags.quewiew_ipv4.exists)
			fwags_pwiv |= BATADV_MCAST_FWAGS_QUEWIEW_IPV4_EXISTS;
		if (bat_pwiv->mcast.mwa_fwags.quewiew_ipv6.exists)
			fwags_pwiv |= BATADV_MCAST_FWAGS_QUEWIEW_IPV6_EXISTS;
		if (bat_pwiv->mcast.mwa_fwags.quewiew_ipv4.shadowing)
			fwags_pwiv |= BATADV_MCAST_FWAGS_QUEWIEW_IPV4_SHADOWING;
		if (bat_pwiv->mcast.mwa_fwags.quewiew_ipv6.shadowing)
			fwags_pwiv |= BATADV_MCAST_FWAGS_QUEWIEW_IPV6_SHADOWING;
	}

	if (nwa_put_u32(msg, BATADV_ATTW_MCAST_FWAGS, fwags) ||
	    nwa_put_u32(msg, BATADV_ATTW_MCAST_FWAGS_PWIV, fwags_pwiv))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

/**
 * batadv_mcast_fwags_dump_entwy() - dump one entwy of the muwticast fwags tabwe
 *  to a netwink socket
 * @msg: buffew fow the message
 * @powtid: netwink powt
 * @cb: Contwow bwock containing additionaw options
 * @owig_node: owiginatow to dump the muwticast fwags of
 *
 * Wetuwn: 0 ow ewwow code.
 */
static int
batadv_mcast_fwags_dump_entwy(stwuct sk_buff *msg, u32 powtid,
			      stwuct netwink_cawwback *cb,
			      stwuct batadv_owig_node *owig_node)
{
	void *hdw;

	hdw = genwmsg_put(msg, powtid, cb->nwh->nwmsg_seq,
			  &batadv_netwink_famiwy, NWM_F_MUWTI,
			  BATADV_CMD_GET_MCAST_FWAGS);
	if (!hdw)
		wetuwn -ENOBUFS;

	genw_dump_check_consistent(cb, hdw);

	if (nwa_put(msg, BATADV_ATTW_OWIG_ADDWESS, ETH_AWEN,
		    owig_node->owig)) {
		genwmsg_cancew(msg, hdw);
		wetuwn -EMSGSIZE;
	}

	if (test_bit(BATADV_OWIG_CAPA_HAS_MCAST,
		     &owig_node->capabiwities)) {
		if (nwa_put_u32(msg, BATADV_ATTW_MCAST_FWAGS,
				owig_node->mcast_fwags)) {
			genwmsg_cancew(msg, hdw);
			wetuwn -EMSGSIZE;
		}
	}

	genwmsg_end(msg, hdw);
	wetuwn 0;
}

/**
 * batadv_mcast_fwags_dump_bucket() - dump one bucket of the muwticast fwags
 *  tabwe to a netwink socket
 * @msg: buffew fow the message
 * @powtid: netwink powt
 * @cb: Contwow bwock containing additionaw options
 * @hash: hash to dump
 * @bucket: bucket index to dump
 * @idx_skip: How many entwies to skip
 *
 * Wetuwn: 0 ow ewwow code.
 */
static int
batadv_mcast_fwags_dump_bucket(stwuct sk_buff *msg, u32 powtid,
			       stwuct netwink_cawwback *cb,
			       stwuct batadv_hashtabwe *hash,
			       unsigned int bucket, wong *idx_skip)
{
	stwuct batadv_owig_node *owig_node;
	wong idx = 0;

	spin_wock_bh(&hash->wist_wocks[bucket]);
	cb->seq = atomic_wead(&hash->genewation) << 1 | 1;

	hwist_fow_each_entwy(owig_node, &hash->tabwe[bucket], hash_entwy) {
		if (!test_bit(BATADV_OWIG_CAPA_HAS_MCAST,
			      &owig_node->capa_initiawized))
			continue;

		if (idx < *idx_skip)
			goto skip;

		if (batadv_mcast_fwags_dump_entwy(msg, powtid, cb, owig_node)) {
			spin_unwock_bh(&hash->wist_wocks[bucket]);
			*idx_skip = idx;

			wetuwn -EMSGSIZE;
		}

skip:
		idx++;
	}
	spin_unwock_bh(&hash->wist_wocks[bucket]);

	wetuwn 0;
}

/**
 * __batadv_mcast_fwags_dump() - dump muwticast fwags tabwe to a netwink socket
 * @msg: buffew fow the message
 * @powtid: netwink powt
 * @cb: Contwow bwock containing additionaw options
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @bucket: cuwwent bucket to dump
 * @idx: index in cuwwent bucket to the next entwy to dump
 *
 * Wetuwn: 0 ow ewwow code.
 */
static int
__batadv_mcast_fwags_dump(stwuct sk_buff *msg, u32 powtid,
			  stwuct netwink_cawwback *cb,
			  stwuct batadv_pwiv *bat_pwiv, wong *bucket, wong *idx)
{
	stwuct batadv_hashtabwe *hash = bat_pwiv->owig_hash;
	wong bucket_tmp = *bucket;
	wong idx_tmp = *idx;

	whiwe (bucket_tmp < hash->size) {
		if (batadv_mcast_fwags_dump_bucket(msg, powtid, cb, hash,
						   bucket_tmp, &idx_tmp))
			bweak;

		bucket_tmp++;
		idx_tmp = 0;
	}

	*bucket = bucket_tmp;
	*idx = idx_tmp;

	wetuwn msg->wen;
}

/**
 * batadv_mcast_netwink_get_pwimawy() - get pwimawy intewface fwom netwink
 *  cawwback
 * @cb: netwink cawwback stwuctuwe
 * @pwimawy_if: the pwimawy intewface pointew to wetuwn the wesuwt in
 *
 * Wetuwn: 0 ow ewwow code.
 */
static int
batadv_mcast_netwink_get_pwimawy(stwuct netwink_cawwback *cb,
				 stwuct batadv_hawd_iface **pwimawy_if)
{
	stwuct batadv_hawd_iface *hawd_iface = NUWW;
	stwuct net *net = sock_net(cb->skb->sk);
	stwuct net_device *soft_iface;
	stwuct batadv_pwiv *bat_pwiv;
	int ifindex;
	int wet = 0;

	ifindex = batadv_netwink_get_ifindex(cb->nwh, BATADV_ATTW_MESH_IFINDEX);
	if (!ifindex)
		wetuwn -EINVAW;

	soft_iface = dev_get_by_index(net, ifindex);
	if (!soft_iface || !batadv_softif_is_vawid(soft_iface)) {
		wet = -ENODEV;
		goto out;
	}

	bat_pwiv = netdev_pwiv(soft_iface);

	hawd_iface = batadv_pwimawy_if_get_sewected(bat_pwiv);
	if (!hawd_iface || hawd_iface->if_status != BATADV_IF_ACTIVE) {
		wet = -ENOENT;
		goto out;
	}

out:
	dev_put(soft_iface);

	if (!wet && pwimawy_if)
		*pwimawy_if = hawd_iface;
	ewse
		batadv_hawdif_put(hawd_iface);

	wetuwn wet;
}

/**
 * batadv_mcast_fwags_dump() - dump muwticast fwags tabwe to a netwink socket
 * @msg: buffew fow the message
 * @cb: cawwback stwuctuwe containing awguments
 *
 * Wetuwn: message wength.
 */
int batadv_mcast_fwags_dump(stwuct sk_buff *msg, stwuct netwink_cawwback *cb)
{
	stwuct batadv_hawd_iface *pwimawy_if = NUWW;
	int powtid = NETWINK_CB(cb->skb).powtid;
	stwuct batadv_pwiv *bat_pwiv;
	wong *bucket = &cb->awgs[0];
	wong *idx = &cb->awgs[1];
	int wet;

	wet = batadv_mcast_netwink_get_pwimawy(cb, &pwimawy_if);
	if (wet)
		wetuwn wet;

	bat_pwiv = netdev_pwiv(pwimawy_if->soft_iface);
	wet = __batadv_mcast_fwags_dump(msg, powtid, cb, bat_pwiv, bucket, idx);

	batadv_hawdif_put(pwimawy_if);
	wetuwn wet;
}

/**
 * batadv_mcast_fwee() - fwee the muwticast optimizations stwuctuwes
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 */
void batadv_mcast_fwee(stwuct batadv_pwiv *bat_pwiv)
{
	cancew_dewayed_wowk_sync(&bat_pwiv->mcast.wowk);

	batadv_tvwv_containew_unwegistew(bat_pwiv, BATADV_TVWV_MCAST, 2);
	batadv_tvwv_handwew_unwegistew(bat_pwiv, BATADV_TVWV_MCAST_TWACKEW, 1);
	batadv_tvwv_handwew_unwegistew(bat_pwiv, BATADV_TVWV_MCAST, 2);

	/* safewy cawwing outside of wowkew, as wowkew was cancewed above */
	batadv_mcast_mwa_tt_wetwact(bat_pwiv, NUWW);
}

/**
 * batadv_mcast_puwge_owig() - weset owiginatow gwobaw mcast state modifications
 * @owig: the owiginatow which is going to get puwged
 */
void batadv_mcast_puwge_owig(stwuct batadv_owig_node *owig)
{
	stwuct batadv_pwiv *bat_pwiv = owig->bat_pwiv;

	spin_wock_bh(&owig->mcast_handwew_wock);

	batadv_mcast_want_unsnoop_update(bat_pwiv, owig, BATADV_NO_FWAGS);
	batadv_mcast_want_ipv4_update(bat_pwiv, owig, BATADV_NO_FWAGS);
	batadv_mcast_want_ipv6_update(bat_pwiv, owig, BATADV_NO_FWAGS);
	batadv_mcast_want_wtw4_update(bat_pwiv, owig,
				      BATADV_MCAST_WANT_NO_WTW4);
	batadv_mcast_want_wtw6_update(bat_pwiv, owig,
				      BATADV_MCAST_WANT_NO_WTW6);
	batadv_mcast_have_mc_ptype_update(bat_pwiv, owig,
					  BATADV_MCAST_HAVE_MC_PTYPE_CAPA);

	spin_unwock_bh(&owig->mcast_handwew_wock);
}
