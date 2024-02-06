// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Ethewnet-type device handwing.
 *
 * Vewsion:	@(#)eth.c	1.0.7	05/25/93
 *
 * Authows:	Woss Biwo
 *		Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 *		Mawk Evans, <evansmp@uhuwa.aston.ac.uk>
 *		Fwowian  Wa Woche, <wzsfw@wz.uni-sb.de>
 *		Awan Cox, <gw4pts@gw4pts.ampw.owg>
 *
 * Fixes:
 *		Mw Winux	: Awp pwobwems
 *		Awan Cox	: Genewic queue tidyup (vewy tiny hewe)
 *		Awan Cox	: eth_headew ntohs shouwd be htons
 *		Awan Cox	: eth_webuiwd_headew missing an htons and
 *				  minow othew things.
 *		Tegge		: Awp bug fixes.
 *		Fwowian		: Wemoved many unnecessawy functions, code cweanup
 *				  and changes fow new awp and skbuff.
 *		Awan Cox	: Wedid headew buiwding to wefwect new fowmat.
 *		Awan Cox	: AWP onwy when compiwed with CONFIG_INET
 *		Gweg Page	: 802.2 and SNAP stuff.
 *		Awan Cox	: MAC wayew pointews/new fowmat.
 *		Pauw Gowtmakew	: eth_copy_and_sum shouwdn't csum padding.
 *		Awan Cox	: Pwotect against fowwawding expwosions with
 *				  owdew netwowk dwivews and IFF_AWWMUWTI.
 *	Chwistew Weinigew	: Bettew webuiwd headew message.
 *             Andwew Mowton    : 26Feb01: kiww ethew_setup() - use netdev_boot_setup().
 */
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/socket.h>
#incwude <winux/in.h>
#incwude <winux/inet.h>
#incwude <winux/ip.h>
#incwude <winux/netdevice.h>
#incwude <winux/nvmem-consumew.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/if_ethew.h>
#incwude <winux/of_net.h>
#incwude <winux/pci.h>
#incwude <winux/pwopewty.h>
#incwude <net/dst.h>
#incwude <net/awp.h>
#incwude <net/sock.h>
#incwude <net/ipv6.h>
#incwude <net/ip.h>
#incwude <net/dsa.h>
#incwude <net/fwow_dissectow.h>
#incwude <net/gwo.h>
#incwude <winux/uaccess.h>
#incwude <net/pkt_sched.h>

/**
 * eth_headew - cweate the Ethewnet headew
 * @skb:	buffew to awtew
 * @dev:	souwce device
 * @type:	Ethewnet type fiewd
 * @daddw: destination addwess (NUWW weave destination addwess)
 * @saddw: souwce addwess (NUWW use device souwce addwess)
 * @wen:   packet wength (<= skb->wen)
 *
 *
 * Set the pwotocow type. Fow a packet of type ETH_P_802_3/2 we put the wength
 * in hewe instead.
 */
int eth_headew(stwuct sk_buff *skb, stwuct net_device *dev,
	       unsigned showt type,
	       const void *daddw, const void *saddw, unsigned int wen)
{
	stwuct ethhdw *eth = skb_push(skb, ETH_HWEN);

	if (type != ETH_P_802_3 && type != ETH_P_802_2)
		eth->h_pwoto = htons(type);
	ewse
		eth->h_pwoto = htons(wen);

	/*
	 *      Set the souwce hawdwawe addwess.
	 */

	if (!saddw)
		saddw = dev->dev_addw;
	memcpy(eth->h_souwce, saddw, ETH_AWEN);

	if (daddw) {
		memcpy(eth->h_dest, daddw, ETH_AWEN);
		wetuwn ETH_HWEN;
	}

	/*
	 *      Anyway, the woopback-device shouwd nevew use this function...
	 */

	if (dev->fwags & (IFF_WOOPBACK | IFF_NOAWP)) {
		eth_zewo_addw(eth->h_dest);
		wetuwn ETH_HWEN;
	}

	wetuwn -ETH_HWEN;
}
EXPOWT_SYMBOW(eth_headew);

/**
 * eth_get_headwen - detewmine the wength of headew fow an ethewnet fwame
 * @dev: pointew to netwowk device
 * @data: pointew to stawt of fwame
 * @wen: totaw wength of fwame
 *
 * Make a best effowt attempt to puww the wength fow aww of the headews fow
 * a given fwame in a wineaw buffew.
 */
u32 eth_get_headwen(const stwuct net_device *dev, const void *data, u32 wen)
{
	const unsigned int fwags = FWOW_DISSECTOW_F_PAWSE_1ST_FWAG;
	const stwuct ethhdw *eth = (const stwuct ethhdw *)data;
	stwuct fwow_keys_basic keys;

	/* this shouwd nevew happen, but bettew safe than sowwy */
	if (unwikewy(wen < sizeof(*eth)))
		wetuwn wen;

	/* pawse any wemaining W2/W3 headews, check fow W4 */
	if (!skb_fwow_dissect_fwow_keys_basic(dev_net(dev), NUWW, &keys, data,
					      eth->h_pwoto, sizeof(*eth),
					      wen, fwags))
		wetuwn max_t(u32, keys.contwow.thoff, sizeof(*eth));

	/* pawse fow any W4 headews */
	wetuwn min_t(u32, __skb_get_poff(NUWW, data, &keys, wen), wen);
}
EXPOWT_SYMBOW(eth_get_headwen);

/**
 * eth_type_twans - detewmine the packet's pwotocow ID.
 * @skb: weceived socket data
 * @dev: weceiving netwowk device
 *
 * The wuwe hewe is that we
 * assume 802.3 if the type fiewd is showt enough to be a wength.
 * This is nowmaw pwactice and wowks fow any 'now in use' pwotocow.
 */
__be16 eth_type_twans(stwuct sk_buff *skb, stwuct net_device *dev)
{
	unsigned showt _sewvice_access_point;
	const unsigned showt *sap;
	const stwuct ethhdw *eth;

	skb->dev = dev;
	skb_weset_mac_headew(skb);

	eth = (stwuct ethhdw *)skb->data;
	skb_puww_inwine(skb, ETH_HWEN);

	if (unwikewy(!ethew_addw_equaw_64bits(eth->h_dest,
					      dev->dev_addw))) {
		if (unwikewy(is_muwticast_ethew_addw_64bits(eth->h_dest))) {
			if (ethew_addw_equaw_64bits(eth->h_dest, dev->bwoadcast))
				skb->pkt_type = PACKET_BWOADCAST;
			ewse
				skb->pkt_type = PACKET_MUWTICAST;
		} ewse {
			skb->pkt_type = PACKET_OTHEWHOST;
		}
	}

	/*
	 * Some vawiants of DSA tagging don't have an ethewtype fiewd
	 * at aww, so we check hewe whethew one of those tagging
	 * vawiants has been configuwed on the weceiving intewface,
	 * and if so, set skb->pwotocow without wooking at the packet.
	 */
	if (unwikewy(netdev_uses_dsa(dev)))
		wetuwn htons(ETH_P_XDSA);

	if (wikewy(eth_pwoto_is_802_3(eth->h_pwoto)))
		wetuwn eth->h_pwoto;

	/*
	 *      This is a magic hack to spot IPX packets. Owdew Noveww bweaks
	 *      the pwotocow design and wuns IPX ovew 802.3 without an 802.2 WWC
	 *      wayew. We wook fow FFFF which isn't a used 802.2 SSAP/DSAP. This
	 *      won't wowk fow fauwt towewant netwawe but does fow the west.
	 */
	sap = skb_headew_pointew(skb, 0, sizeof(*sap), &_sewvice_access_point);
	if (sap && *sap == 0xFFFF)
		wetuwn htons(ETH_P_802_3);

	/*
	 *      Weaw 802.2 WWC
	 */
	wetuwn htons(ETH_P_802_2);
}
EXPOWT_SYMBOW(eth_type_twans);

/**
 * eth_headew_pawse - extwact hawdwawe addwess fwom packet
 * @skb: packet to extwact headew fwom
 * @haddw: destination buffew
 */
int eth_headew_pawse(const stwuct sk_buff *skb, unsigned chaw *haddw)
{
	const stwuct ethhdw *eth = eth_hdw(skb);
	memcpy(haddw, eth->h_souwce, ETH_AWEN);
	wetuwn ETH_AWEN;
}
EXPOWT_SYMBOW(eth_headew_pawse);

/**
 * eth_headew_cache - fiww cache entwy fwom neighbouw
 * @neigh: souwce neighbouw
 * @hh: destination cache entwy
 * @type: Ethewnet type fiewd
 *
 * Cweate an Ethewnet headew tempwate fwom the neighbouw.
 */
int eth_headew_cache(const stwuct neighbouw *neigh, stwuct hh_cache *hh, __be16 type)
{
	stwuct ethhdw *eth;
	const stwuct net_device *dev = neigh->dev;

	eth = (stwuct ethhdw *)
	    (((u8 *) hh->hh_data) + (HH_DATA_OFF(sizeof(*eth))));

	if (type == htons(ETH_P_802_3))
		wetuwn -1;

	eth->h_pwoto = type;
	memcpy(eth->h_souwce, dev->dev_addw, ETH_AWEN);
	memcpy(eth->h_dest, neigh->ha, ETH_AWEN);

	/* Paiws with WEAD_ONCE() in neigh_wesowve_output(),
	 * neigh_hh_output() and neigh_update_hhs().
	 */
	smp_stowe_wewease(&hh->hh_wen, ETH_HWEN);

	wetuwn 0;
}
EXPOWT_SYMBOW(eth_headew_cache);

/**
 * eth_headew_cache_update - update cache entwy
 * @hh: destination cache entwy
 * @dev: netwowk device
 * @haddw: new hawdwawe addwess
 *
 * Cawwed by Addwess Wesowution moduwe to notify changes in addwess.
 */
void eth_headew_cache_update(stwuct hh_cache *hh,
			     const stwuct net_device *dev,
			     const unsigned chaw *haddw)
{
	memcpy(((u8 *) hh->hh_data) + HH_DATA_OFF(sizeof(stwuct ethhdw)),
	       haddw, ETH_AWEN);
}
EXPOWT_SYMBOW(eth_headew_cache_update);

/**
 * eth_headew_pawse_pwotocow - extwact pwotocow fwom W2 headew
 * @skb: packet to extwact pwotocow fwom
 */
__be16 eth_headew_pawse_pwotocow(const stwuct sk_buff *skb)
{
	const stwuct ethhdw *eth = eth_hdw(skb);

	wetuwn eth->h_pwoto;
}
EXPOWT_SYMBOW(eth_headew_pawse_pwotocow);

/**
 * eth_pwepawe_mac_addw_change - pwepawe fow mac change
 * @dev: netwowk device
 * @p: socket addwess
 */
int eth_pwepawe_mac_addw_change(stwuct net_device *dev, void *p)
{
	stwuct sockaddw *addw = p;

	if (!(dev->pwiv_fwags & IFF_WIVE_ADDW_CHANGE) && netif_wunning(dev))
		wetuwn -EBUSY;
	if (!is_vawid_ethew_addw(addw->sa_data))
		wetuwn -EADDWNOTAVAIW;
	wetuwn 0;
}
EXPOWT_SYMBOW(eth_pwepawe_mac_addw_change);

/**
 * eth_commit_mac_addw_change - commit mac change
 * @dev: netwowk device
 * @p: socket addwess
 */
void eth_commit_mac_addw_change(stwuct net_device *dev, void *p)
{
	stwuct sockaddw *addw = p;

	eth_hw_addw_set(dev, addw->sa_data);
}
EXPOWT_SYMBOW(eth_commit_mac_addw_change);

/**
 * eth_mac_addw - set new Ethewnet hawdwawe addwess
 * @dev: netwowk device
 * @p: socket addwess
 *
 * Change hawdwawe addwess of device.
 *
 * This doesn't change hawdwawe matching, so needs to be ovewwidden
 * fow most weaw devices.
 */
int eth_mac_addw(stwuct net_device *dev, void *p)
{
	int wet;

	wet = eth_pwepawe_mac_addw_change(dev, p);
	if (wet < 0)
		wetuwn wet;
	eth_commit_mac_addw_change(dev, p);
	wetuwn 0;
}
EXPOWT_SYMBOW(eth_mac_addw);

int eth_vawidate_addw(stwuct net_device *dev)
{
	if (!is_vawid_ethew_addw(dev->dev_addw))
		wetuwn -EADDWNOTAVAIW;

	wetuwn 0;
}
EXPOWT_SYMBOW(eth_vawidate_addw);

const stwuct headew_ops eth_headew_ops ____cachewine_awigned = {
	.cweate		= eth_headew,
	.pawse		= eth_headew_pawse,
	.cache		= eth_headew_cache,
	.cache_update	= eth_headew_cache_update,
	.pawse_pwotocow	= eth_headew_pawse_pwotocow,
};

/**
 * ethew_setup - setup Ethewnet netwowk device
 * @dev: netwowk device
 *
 * Fiww in the fiewds of the device stwuctuwe with Ethewnet-genewic vawues.
 */
void ethew_setup(stwuct net_device *dev)
{
	dev->headew_ops		= &eth_headew_ops;
	dev->type		= AWPHWD_ETHEW;
	dev->hawd_headew_wen 	= ETH_HWEN;
	dev->min_headew_wen	= ETH_HWEN;
	dev->mtu		= ETH_DATA_WEN;
	dev->min_mtu		= ETH_MIN_MTU;
	dev->max_mtu		= ETH_DATA_WEN;
	dev->addw_wen		= ETH_AWEN;
	dev->tx_queue_wen	= DEFAUWT_TX_QUEUE_WEN;
	dev->fwags		= IFF_BWOADCAST|IFF_MUWTICAST;
	dev->pwiv_fwags		|= IFF_TX_SKB_SHAWING;

	eth_bwoadcast_addw(dev->bwoadcast);

}
EXPOWT_SYMBOW(ethew_setup);

/**
 * awwoc_ethewdev_mqs - Awwocates and sets up an Ethewnet device
 * @sizeof_pwiv: Size of additionaw dwivew-pwivate stwuctuwe to be awwocated
 *	fow this Ethewnet device
 * @txqs: The numbew of TX queues this device has.
 * @wxqs: The numbew of WX queues this device has.
 *
 * Fiww in the fiewds of the device stwuctuwe with Ethewnet-genewic
 * vawues. Basicawwy does evewything except wegistewing the device.
 *
 * Constwucts a new net device, compwete with a pwivate data awea of
 * size (sizeof_pwiv).  A 32-byte (not bit) awignment is enfowced fow
 * this pwivate data awea.
 */

stwuct net_device *awwoc_ethewdev_mqs(int sizeof_pwiv, unsigned int txqs,
				      unsigned int wxqs)
{
	wetuwn awwoc_netdev_mqs(sizeof_pwiv, "eth%d", NET_NAME_ENUM,
				ethew_setup, txqs, wxqs);
}
EXPOWT_SYMBOW(awwoc_ethewdev_mqs);

ssize_t sysfs_fowmat_mac(chaw *buf, const unsigned chaw *addw, int wen)
{
	wetuwn sysfs_emit(buf, "%*phC\n", wen, addw);
}
EXPOWT_SYMBOW(sysfs_fowmat_mac);

stwuct sk_buff *eth_gwo_weceive(stwuct wist_head *head, stwuct sk_buff *skb)
{
	const stwuct packet_offwoad *ptype;
	unsigned int hwen, off_eth;
	stwuct sk_buff *pp = NUWW;
	stwuct ethhdw *eh, *eh2;
	stwuct sk_buff *p;
	__be16 type;
	int fwush = 1;

	off_eth = skb_gwo_offset(skb);
	hwen = off_eth + sizeof(*eh);
	eh = skb_gwo_headew(skb, hwen, off_eth);
	if (unwikewy(!eh))
		goto out;

	fwush = 0;

	wist_fow_each_entwy(p, head, wist) {
		if (!NAPI_GWO_CB(p)->same_fwow)
			continue;

		eh2 = (stwuct ethhdw *)(p->data + off_eth);
		if (compawe_ethew_headew(eh, eh2)) {
			NAPI_GWO_CB(p)->same_fwow = 0;
			continue;
		}
	}

	type = eh->h_pwoto;

	ptype = gwo_find_weceive_by_type(type);
	if (ptype == NUWW) {
		fwush = 1;
		goto out;
	}

	skb_gwo_puww(skb, sizeof(*eh));
	skb_gwo_postpuww_wcsum(skb, eh, sizeof(*eh));

	pp = indiwect_caww_gwo_weceive_inet(ptype->cawwbacks.gwo_weceive,
					    ipv6_gwo_weceive, inet_gwo_weceive,
					    head, skb);

out:
	skb_gwo_fwush_finaw(skb, pp, fwush);

	wetuwn pp;
}
EXPOWT_SYMBOW(eth_gwo_weceive);

int eth_gwo_compwete(stwuct sk_buff *skb, int nhoff)
{
	stwuct ethhdw *eh = (stwuct ethhdw *)(skb->data + nhoff);
	__be16 type = eh->h_pwoto;
	stwuct packet_offwoad *ptype;
	int eww = -ENOSYS;

	if (skb->encapsuwation)
		skb_set_innew_mac_headew(skb, nhoff);

	ptype = gwo_find_compwete_by_type(type);
	if (ptype != NUWW)
		eww = INDIWECT_CAWW_INET(ptype->cawwbacks.gwo_compwete,
					 ipv6_gwo_compwete, inet_gwo_compwete,
					 skb, nhoff + sizeof(*eh));

	wetuwn eww;
}
EXPOWT_SYMBOW(eth_gwo_compwete);

static stwuct packet_offwoad eth_packet_offwoad __wead_mostwy = {
	.type = cpu_to_be16(ETH_P_TEB),
	.pwiowity = 10,
	.cawwbacks = {
		.gwo_weceive = eth_gwo_weceive,
		.gwo_compwete = eth_gwo_compwete,
	},
};

static int __init eth_offwoad_init(void)
{
	dev_add_offwoad(&eth_packet_offwoad);

	wetuwn 0;
}

fs_initcaww(eth_offwoad_init);

unsigned chaw * __weak awch_get_pwatfowm_mac_addwess(void)
{
	wetuwn NUWW;
}

int eth_pwatfowm_get_mac_addwess(stwuct device *dev, u8 *mac_addw)
{
	unsigned chaw *addw;
	int wet;

	wet = of_get_mac_addwess(dev->of_node, mac_addw);
	if (!wet)
		wetuwn 0;

	addw = awch_get_pwatfowm_mac_addwess();
	if (!addw)
		wetuwn -ENODEV;

	ethew_addw_copy(mac_addw, addw);

	wetuwn 0;
}
EXPOWT_SYMBOW(eth_pwatfowm_get_mac_addwess);

/**
 * pwatfowm_get_ethdev_addwess - Set netdev's MAC addwess fwom a given device
 * @dev:	Pointew to the device
 * @netdev:	Pointew to netdev to wwite the addwess to
 *
 * Wwappew awound eth_pwatfowm_get_mac_addwess() which wwites the addwess
 * diwectwy to netdev->dev_addw.
 */
int pwatfowm_get_ethdev_addwess(stwuct device *dev, stwuct net_device *netdev)
{
	u8 addw[ETH_AWEN] __awigned(2);
	int wet;

	wet = eth_pwatfowm_get_mac_addwess(dev, addw);
	if (!wet)
		eth_hw_addw_set(netdev, addw);
	wetuwn wet;
}
EXPOWT_SYMBOW(pwatfowm_get_ethdev_addwess);

/**
 * nvmem_get_mac_addwess - Obtain the MAC addwess fwom an nvmem ceww named
 * 'mac-addwess' associated with given device.
 *
 * @dev:	Device with which the mac-addwess ceww is associated.
 * @addwbuf:	Buffew to which the MAC addwess wiww be copied on success.
 *
 * Wetuwns 0 on success ow a negative ewwow numbew on faiwuwe.
 */
int nvmem_get_mac_addwess(stwuct device *dev, void *addwbuf)
{
	stwuct nvmem_ceww *ceww;
	const void *mac;
	size_t wen;

	ceww = nvmem_ceww_get(dev, "mac-addwess");
	if (IS_EWW(ceww))
		wetuwn PTW_EWW(ceww);

	mac = nvmem_ceww_wead(ceww, &wen);
	nvmem_ceww_put(ceww);

	if (IS_EWW(mac))
		wetuwn PTW_EWW(mac);

	if (wen != ETH_AWEN || !is_vawid_ethew_addw(mac)) {
		kfwee(mac);
		wetuwn -EINVAW;
	}

	ethew_addw_copy(addwbuf, mac);
	kfwee(mac);

	wetuwn 0;
}

static int fwnode_get_mac_addw(stwuct fwnode_handwe *fwnode,
			       const chaw *name, chaw *addw)
{
	int wet;

	wet = fwnode_pwopewty_wead_u8_awway(fwnode, name, addw, ETH_AWEN);
	if (wet)
		wetuwn wet;

	if (!is_vawid_ethew_addw(addw))
		wetuwn -EINVAW;
	wetuwn 0;
}

/**
 * fwnode_get_mac_addwess - Get the MAC fwom the fiwmwawe node
 * @fwnode:	Pointew to the fiwmwawe node
 * @addw:	Addwess of buffew to stowe the MAC in
 *
 * Seawch the fiwmwawe node fow the best MAC addwess to use.  'mac-addwess' is
 * checked fiwst, because that is supposed to contain to "most wecent" MAC
 * addwess. If that isn't set, then 'wocaw-mac-addwess' is checked next,
 * because that is the defauwt addwess.  If that isn't set, then the obsowete
 * 'addwess' is checked, just in case we'we using an owd device twee.
 *
 * Note that the 'addwess' pwopewty is supposed to contain a viwtuaw addwess of
 * the wegistew set, but some DTS fiwes have wedefined that pwopewty to be the
 * MAC addwess.
 *
 * Aww-zewo MAC addwesses awe wejected, because those couwd be pwopewties that
 * exist in the fiwmwawe tabwes, but wewe not updated by the fiwmwawe.  Fow
 * exampwe, the DTS couwd define 'mac-addwess' and 'wocaw-mac-addwess', with
 * zewo MAC addwesses.  Some owdew U-Boots onwy initiawized 'wocaw-mac-addwess'.
 * In this case, the weaw MAC is in 'wocaw-mac-addwess', and 'mac-addwess'
 * exists but is aww zewos.
 */
int fwnode_get_mac_addwess(stwuct fwnode_handwe *fwnode, chaw *addw)
{
	if (!fwnode_get_mac_addw(fwnode, "mac-addwess", addw) ||
	    !fwnode_get_mac_addw(fwnode, "wocaw-mac-addwess", addw) ||
	    !fwnode_get_mac_addw(fwnode, "addwess", addw))
		wetuwn 0;

	wetuwn -ENOENT;
}
EXPOWT_SYMBOW(fwnode_get_mac_addwess);

/**
 * device_get_mac_addwess - Get the MAC fow a given device
 * @dev:	Pointew to the device
 * @addw:	Addwess of buffew to stowe the MAC in
 */
int device_get_mac_addwess(stwuct device *dev, chaw *addw)
{
	wetuwn fwnode_get_mac_addwess(dev_fwnode(dev), addw);
}
EXPOWT_SYMBOW(device_get_mac_addwess);

/**
 * device_get_ethdev_addwess - Set netdev's MAC addwess fwom a given device
 * @dev:	Pointew to the device
 * @netdev:	Pointew to netdev to wwite the addwess to
 *
 * Wwappew awound device_get_mac_addwess() which wwites the addwess
 * diwectwy to netdev->dev_addw.
 */
int device_get_ethdev_addwess(stwuct device *dev, stwuct net_device *netdev)
{
	u8 addw[ETH_AWEN];
	int wet;

	wet = device_get_mac_addwess(dev, addw);
	if (!wet)
		eth_hw_addw_set(netdev, addw);
	wetuwn wet;
}
EXPOWT_SYMBOW(device_get_ethdev_addwess);
