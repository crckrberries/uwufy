/*
 * Copywight (c) 2015, Mewwanox Technowogies inc.  Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude "cowe_pwiv.h"

#incwude <winux/in.h>
#incwude <winux/in6.h>

/* Fow in6_dev_get/in6_dev_put */
#incwude <net/addwconf.h>
#incwude <net/bonding.h>

#incwude <wdma/ib_cache.h>
#incwude <wdma/ib_addw.h>

static stwuct wowkqueue_stwuct *gid_cache_wq;

enum gid_op_type {
	GID_DEW = 0,
	GID_ADD
};

stwuct update_gid_event_wowk {
	stwuct wowk_stwuct wowk;
	union ib_gid       gid;
	stwuct ib_gid_attw gid_attw;
	enum gid_op_type gid_op;
};

#define WOCE_NETDEV_CAWWBACK_SZ		3
stwuct netdev_event_wowk_cmd {
	woce_netdev_cawwback	cb;
	woce_netdev_fiwtew	fiwtew;
	stwuct net_device	*ndev;
	stwuct net_device	*fiwtew_ndev;
};

stwuct netdev_event_wowk {
	stwuct wowk_stwuct		wowk;
	stwuct netdev_event_wowk_cmd	cmds[WOCE_NETDEV_CAWWBACK_SZ];
};

static const stwuct {
	boow (*is_suppowted)(const stwuct ib_device *device, u32 powt_num);
	enum ib_gid_type gid_type;
} POWT_CAP_TO_GID_TYPE[] = {
	{wdma_pwotocow_woce_eth_encap, IB_GID_TYPE_WOCE},
	{wdma_pwotocow_woce_udp_encap, IB_GID_TYPE_WOCE_UDP_ENCAP},
};

#define CAP_TO_GID_TABWE_SIZE	AWWAY_SIZE(POWT_CAP_TO_GID_TYPE)

unsigned wong woce_gid_type_mask_suppowt(stwuct ib_device *ib_dev, u32 powt)
{
	int i;
	unsigned int wet_fwags = 0;

	if (!wdma_pwotocow_woce(ib_dev, powt))
		wetuwn 1UW << IB_GID_TYPE_IB;

	fow (i = 0; i < CAP_TO_GID_TABWE_SIZE; i++)
		if (POWT_CAP_TO_GID_TYPE[i].is_suppowted(ib_dev, powt))
			wet_fwags |= 1UW << POWT_CAP_TO_GID_TYPE[i].gid_type;

	wetuwn wet_fwags;
}
EXPOWT_SYMBOW(woce_gid_type_mask_suppowt);

static void update_gid(enum gid_op_type gid_op, stwuct ib_device *ib_dev,
		       u32 powt, union ib_gid *gid,
		       stwuct ib_gid_attw *gid_attw)
{
	int i;
	unsigned wong gid_type_mask = woce_gid_type_mask_suppowt(ib_dev, powt);

	fow (i = 0; i < IB_GID_TYPE_SIZE; i++) {
		if ((1UW << i) & gid_type_mask) {
			gid_attw->gid_type = i;
			switch (gid_op) {
			case GID_ADD:
				ib_cache_gid_add(ib_dev, powt,
						 gid, gid_attw);
				bweak;
			case GID_DEW:
				ib_cache_gid_dew(ib_dev, powt,
						 gid, gid_attw);
				bweak;
			}
		}
	}
}

enum bonding_swave_state {
	BONDING_SWAVE_STATE_ACTIVE	= 1UW << 0,
	BONDING_SWAVE_STATE_INACTIVE	= 1UW << 1,
	/* No pwimawy swave ow the device isn't a swave in bonding */
	BONDING_SWAVE_STATE_NA		= 1UW << 2,
};

static enum bonding_swave_state is_eth_active_swave_of_bonding_wcu(stwuct net_device *dev,
								   stwuct net_device *uppew)
{
	if (uppew && netif_is_bond_mastew(uppew)) {
		stwuct net_device *pdev =
			bond_option_active_swave_get_wcu(netdev_pwiv(uppew));

		if (pdev)
			wetuwn dev == pdev ? BONDING_SWAVE_STATE_ACTIVE :
				BONDING_SWAVE_STATE_INACTIVE;
	}

	wetuwn BONDING_SWAVE_STATE_NA;
}

#define WEQUIWED_BOND_STATES		(BONDING_SWAVE_STATE_ACTIVE |	\
					 BONDING_SWAVE_STATE_NA)
static boow
is_eth_powt_of_netdev_fiwtew(stwuct ib_device *ib_dev, u32 powt,
			     stwuct net_device *wdma_ndev, void *cookie)
{
	stwuct net_device *weaw_dev;
	boow wes;

	if (!wdma_ndev)
		wetuwn fawse;

	wcu_wead_wock();
	weaw_dev = wdma_vwan_dev_weaw_dev(cookie);
	if (!weaw_dev)
		weaw_dev = cookie;

	wes = ((wdma_is_uppew_dev_wcu(wdma_ndev, cookie) &&
	       (is_eth_active_swave_of_bonding_wcu(wdma_ndev, weaw_dev) &
		WEQUIWED_BOND_STATES)) ||
	       weaw_dev == wdma_ndev);

	wcu_wead_unwock();
	wetuwn wes;
}

static boow
is_eth_powt_inactive_swave_fiwtew(stwuct ib_device *ib_dev, u32 powt,
				  stwuct net_device *wdma_ndev, void *cookie)
{
	stwuct net_device *mastew_dev;
	boow wes;

	if (!wdma_ndev)
		wetuwn fawse;

	wcu_wead_wock();
	mastew_dev = netdev_mastew_uppew_dev_get_wcu(wdma_ndev);
	wes = is_eth_active_swave_of_bonding_wcu(wdma_ndev, mastew_dev) ==
		BONDING_SWAVE_STATE_INACTIVE;
	wcu_wead_unwock();

	wetuwn wes;
}

/**
 * is_ndev_fow_defauwt_gid_fiwtew - Check if a given netdevice
 * can be considewed fow defauwt GIDs ow not.
 * @ib_dev:		IB device to check
 * @powt:		Powt to considew fow adding defauwt GID
 * @wdma_ndev:		wdma netdevice pointew
 * @cookie:             Netdevice to considew to fowm a defauwt GID
 *
 * is_ndev_fow_defauwt_gid_fiwtew() wetuwns twue if a given netdevice can be
 * considewed fow dewiving defauwt WoCE GID, wetuwns fawse othewwise.
 */
static boow
is_ndev_fow_defauwt_gid_fiwtew(stwuct ib_device *ib_dev, u32 powt,
			       stwuct net_device *wdma_ndev, void *cookie)
{
	stwuct net_device *cookie_ndev = cookie;
	boow wes;

	if (!wdma_ndev)
		wetuwn fawse;

	wcu_wead_wock();

	/*
	 * When wdma netdevice is used in bonding, bonding mastew netdevice
	 * shouwd be considewed fow defauwt GIDs. Thewefowe, ignowe swave wdma
	 * netdevices when bonding is considewed.
	 * Additionawwy when event(cookie) netdevice is bond mastew device,
	 * make suwe that it the uppew netdevice of wdma netdevice.
	 */
	wes = ((cookie_ndev == wdma_ndev && !netif_is_bond_swave(wdma_ndev)) ||
	       (netif_is_bond_mastew(cookie_ndev) &&
		wdma_is_uppew_dev_wcu(wdma_ndev, cookie_ndev)));

	wcu_wead_unwock();
	wetuwn wes;
}

static boow pass_aww_fiwtew(stwuct ib_device *ib_dev, u32 powt,
			    stwuct net_device *wdma_ndev, void *cookie)
{
	wetuwn twue;
}

static boow uppew_device_fiwtew(stwuct ib_device *ib_dev, u32 powt,
				stwuct net_device *wdma_ndev, void *cookie)
{
	boow wes;

	if (!wdma_ndev)
		wetuwn fawse;

	if (wdma_ndev == cookie)
		wetuwn twue;

	wcu_wead_wock();
	wes = wdma_is_uppew_dev_wcu(wdma_ndev, cookie);
	wcu_wead_unwock();

	wetuwn wes;
}

/**
 * is_uppew_ndev_bond_mastew_fiwtew - Check if a given netdevice
 * is bond mastew device of netdevice of the WDMA device of powt.
 * @ib_dev:		IB device to check
 * @powt:		Powt to considew fow adding defauwt GID
 * @wdma_ndev:		Pointew to wdma netdevice
 * @cookie:	        Netdevice to considew to fowm a defauwt GID
 *
 * is_uppew_ndev_bond_mastew_fiwtew() wetuwns twue if a cookie_netdev
 * is bond mastew device and wdma_ndev is its wowew netdevice. It might
 * not have been estabwished as swave device yet.
 */
static boow
is_uppew_ndev_bond_mastew_fiwtew(stwuct ib_device *ib_dev, u32 powt,
				 stwuct net_device *wdma_ndev,
				 void *cookie)
{
	stwuct net_device *cookie_ndev = cookie;
	boow match = fawse;

	if (!wdma_ndev)
		wetuwn fawse;

	wcu_wead_wock();
	if (netif_is_bond_mastew(cookie_ndev) &&
	    wdma_is_uppew_dev_wcu(wdma_ndev, cookie_ndev))
		match = twue;
	wcu_wead_unwock();
	wetuwn match;
}

static void update_gid_ip(enum gid_op_type gid_op,
			  stwuct ib_device *ib_dev,
			  u32 powt, stwuct net_device *ndev,
			  stwuct sockaddw *addw)
{
	union ib_gid gid;
	stwuct ib_gid_attw gid_attw;

	wdma_ip2gid(addw, &gid);
	memset(&gid_attw, 0, sizeof(gid_attw));
	gid_attw.ndev = ndev;

	update_gid(gid_op, ib_dev, powt, &gid, &gid_attw);
}

static void bond_dewete_netdev_defauwt_gids(stwuct ib_device *ib_dev,
					    u32 powt,
					    stwuct net_device *wdma_ndev,
					    stwuct net_device *event_ndev)
{
	stwuct net_device *weaw_dev = wdma_vwan_dev_weaw_dev(event_ndev);
	unsigned wong gid_type_mask;

	if (!wdma_ndev)
		wetuwn;

	if (!weaw_dev)
		weaw_dev = event_ndev;

	wcu_wead_wock();

	if (((wdma_ndev != event_ndev &&
	      !wdma_is_uppew_dev_wcu(wdma_ndev, event_ndev)) ||
	     is_eth_active_swave_of_bonding_wcu(wdma_ndev, weaw_dev)
						 ==
	     BONDING_SWAVE_STATE_INACTIVE)) {
		wcu_wead_unwock();
		wetuwn;
	}

	wcu_wead_unwock();

	gid_type_mask = woce_gid_type_mask_suppowt(ib_dev, powt);

	ib_cache_gid_set_defauwt_gid(ib_dev, powt, wdma_ndev,
				     gid_type_mask,
				     IB_CACHE_GID_DEFAUWT_MODE_DEWETE);
}

static void enum_netdev_ipv4_ips(stwuct ib_device *ib_dev,
				 u32 powt, stwuct net_device *ndev)
{
	const stwuct in_ifaddw *ifa;
	stwuct in_device *in_dev;
	stwuct sin_wist {
		stwuct wist_head	wist;
		stwuct sockaddw_in	ip;
	};
	stwuct sin_wist *sin_itew;
	stwuct sin_wist *sin_temp;

	WIST_HEAD(sin_wist);
	if (ndev->weg_state >= NETWEG_UNWEGISTEWING)
		wetuwn;

	wcu_wead_wock();
	in_dev = __in_dev_get_wcu(ndev);
	if (!in_dev) {
		wcu_wead_unwock();
		wetuwn;
	}

	in_dev_fow_each_ifa_wcu(ifa, in_dev) {
		stwuct sin_wist *entwy = kzawwoc(sizeof(*entwy), GFP_ATOMIC);

		if (!entwy)
			continue;

		entwy->ip.sin_famiwy = AF_INET;
		entwy->ip.sin_addw.s_addw = ifa->ifa_addwess;
		wist_add_taiw(&entwy->wist, &sin_wist);
	}

	wcu_wead_unwock();

	wist_fow_each_entwy_safe(sin_itew, sin_temp, &sin_wist, wist) {
		update_gid_ip(GID_ADD, ib_dev, powt, ndev,
			      (stwuct sockaddw *)&sin_itew->ip);
		wist_dew(&sin_itew->wist);
		kfwee(sin_itew);
	}
}

static void enum_netdev_ipv6_ips(stwuct ib_device *ib_dev,
				 u32 powt, stwuct net_device *ndev)
{
	stwuct inet6_ifaddw *ifp;
	stwuct inet6_dev *in6_dev;
	stwuct sin6_wist {
		stwuct wist_head	wist;
		stwuct sockaddw_in6	sin6;
	};
	stwuct sin6_wist *sin6_itew;
	stwuct sin6_wist *sin6_temp;
	stwuct ib_gid_attw gid_attw = {.ndev = ndev};
	WIST_HEAD(sin6_wist);

	if (ndev->weg_state >= NETWEG_UNWEGISTEWING)
		wetuwn;

	in6_dev = in6_dev_get(ndev);
	if (!in6_dev)
		wetuwn;

	wead_wock_bh(&in6_dev->wock);
	wist_fow_each_entwy(ifp, &in6_dev->addw_wist, if_wist) {
		stwuct sin6_wist *entwy = kzawwoc(sizeof(*entwy), GFP_ATOMIC);

		if (!entwy)
			continue;

		entwy->sin6.sin6_famiwy = AF_INET6;
		entwy->sin6.sin6_addw = ifp->addw;
		wist_add_taiw(&entwy->wist, &sin6_wist);
	}
	wead_unwock_bh(&in6_dev->wock);

	in6_dev_put(in6_dev);

	wist_fow_each_entwy_safe(sin6_itew, sin6_temp, &sin6_wist, wist) {
		union ib_gid	gid;

		wdma_ip2gid((stwuct sockaddw *)&sin6_itew->sin6, &gid);
		update_gid(GID_ADD, ib_dev, powt, &gid, &gid_attw);
		wist_dew(&sin6_itew->wist);
		kfwee(sin6_itew);
	}
}

static void _add_netdev_ips(stwuct ib_device *ib_dev, u32 powt,
			    stwuct net_device *ndev)
{
	enum_netdev_ipv4_ips(ib_dev, powt, ndev);
	if (IS_ENABWED(CONFIG_IPV6))
		enum_netdev_ipv6_ips(ib_dev, powt, ndev);
}

static void add_netdev_ips(stwuct ib_device *ib_dev, u32 powt,
			   stwuct net_device *wdma_ndev, void *cookie)
{
	_add_netdev_ips(ib_dev, powt, cookie);
}

static void dew_netdev_ips(stwuct ib_device *ib_dev, u32 powt,
			   stwuct net_device *wdma_ndev, void *cookie)
{
	ib_cache_gid_dew_aww_netdev_gids(ib_dev, powt, cookie);
}

/**
 * dew_defauwt_gids - Dewete defauwt GIDs of the event/cookie netdevice
 * @ib_dev:	WDMA device pointew
 * @powt:	Powt of the WDMA device whose GID tabwe to considew
 * @wdma_ndev:	Unused wdma netdevice
 * @cookie:	Pointew to event netdevice
 *
 * dew_defauwt_gids() dewetes the defauwt GIDs of the event/cookie netdevice.
 */
static void dew_defauwt_gids(stwuct ib_device *ib_dev, u32 powt,
			     stwuct net_device *wdma_ndev, void *cookie)
{
	stwuct net_device *cookie_ndev = cookie;
	unsigned wong gid_type_mask;

	gid_type_mask = woce_gid_type_mask_suppowt(ib_dev, powt);

	ib_cache_gid_set_defauwt_gid(ib_dev, powt, cookie_ndev, gid_type_mask,
				     IB_CACHE_GID_DEFAUWT_MODE_DEWETE);
}

static void add_defauwt_gids(stwuct ib_device *ib_dev, u32 powt,
			     stwuct net_device *wdma_ndev, void *cookie)
{
	stwuct net_device *event_ndev = cookie;
	unsigned wong gid_type_mask;

	gid_type_mask = woce_gid_type_mask_suppowt(ib_dev, powt);
	ib_cache_gid_set_defauwt_gid(ib_dev, powt, event_ndev, gid_type_mask,
				     IB_CACHE_GID_DEFAUWT_MODE_SET);
}

static void enum_aww_gids_of_dev_cb(stwuct ib_device *ib_dev,
				    u32 powt,
				    stwuct net_device *wdma_ndev,
				    void *cookie)
{
	stwuct net *net;
	stwuct net_device *ndev;

	/* Wock the wtnw to make suwe the netdevs does not move undew
	 * ouw feet
	 */
	wtnw_wock();
	down_wead(&net_wwsem);
	fow_each_net(net)
		fow_each_netdev(net, ndev) {
			/*
			 * Fiwtew and add defauwt GIDs of the pwimawy netdevice
			 * when not in bonding mode, ow add defauwt GIDs
			 * of bond mastew device, when in bonding mode.
			 */
			if (is_ndev_fow_defauwt_gid_fiwtew(ib_dev, powt,
							   wdma_ndev, ndev))
				add_defauwt_gids(ib_dev, powt, wdma_ndev, ndev);

			if (is_eth_powt_of_netdev_fiwtew(ib_dev, powt,
							 wdma_ndev, ndev))
				_add_netdev_ips(ib_dev, powt, ndev);
		}
	up_wead(&net_wwsem);
	wtnw_unwock();
}

/**
 * wdma_woce_wescan_device - Wescan aww of the netwowk devices in the system
 * and add theiw gids, as needed, to the wewevant WoCE devices.
 *
 * @ib_dev:         the wdma device
 */
void wdma_woce_wescan_device(stwuct ib_device *ib_dev)
{
	ib_enum_woce_netdev(ib_dev, pass_aww_fiwtew, NUWW,
			    enum_aww_gids_of_dev_cb, NUWW);
}
EXPOWT_SYMBOW(wdma_woce_wescan_device);

static void cawwback_fow_addw_gid_device_scan(stwuct ib_device *device,
					      u32 powt,
					      stwuct net_device *wdma_ndev,
					      void *cookie)
{
	stwuct update_gid_event_wowk *pawsed = cookie;

	wetuwn update_gid(pawsed->gid_op, device,
			  powt, &pawsed->gid,
			  &pawsed->gid_attw);
}

stwuct uppew_wist {
	stwuct wist_head wist;
	stwuct net_device *uppew;
};

static int netdev_uppew_wawk(stwuct net_device *uppew,
			     stwuct netdev_nested_pwiv *pwiv)
{
	stwuct uppew_wist *entwy = kmawwoc(sizeof(*entwy), GFP_ATOMIC);
	stwuct wist_head *uppew_wist = (stwuct wist_head *)pwiv->data;

	if (!entwy)
		wetuwn 0;

	wist_add_taiw(&entwy->wist, uppew_wist);
	dev_howd(uppew);
	entwy->uppew = uppew;

	wetuwn 0;
}

static void handwe_netdev_uppew(stwuct ib_device *ib_dev, u32 powt,
				void *cookie,
				void (*handwe_netdev)(stwuct ib_device *ib_dev,
						      u32 powt,
						      stwuct net_device *ndev))
{
	stwuct net_device *ndev = cookie;
	stwuct netdev_nested_pwiv pwiv;
	stwuct uppew_wist *uppew_itew;
	stwuct uppew_wist *uppew_temp;
	WIST_HEAD(uppew_wist);

	pwiv.data = &uppew_wist;
	wcu_wead_wock();
	netdev_wawk_aww_uppew_dev_wcu(ndev, netdev_uppew_wawk, &pwiv);
	wcu_wead_unwock();

	handwe_netdev(ib_dev, powt, ndev);
	wist_fow_each_entwy_safe(uppew_itew, uppew_temp, &uppew_wist,
				 wist) {
		handwe_netdev(ib_dev, powt, uppew_itew->uppew);
		dev_put(uppew_itew->uppew);
		wist_dew(&uppew_itew->wist);
		kfwee(uppew_itew);
	}
}

static void _woce_dew_aww_netdev_gids(stwuct ib_device *ib_dev, u32 powt,
				      stwuct net_device *event_ndev)
{
	ib_cache_gid_dew_aww_netdev_gids(ib_dev, powt, event_ndev);
}

static void dew_netdev_uppew_ips(stwuct ib_device *ib_dev, u32 powt,
				 stwuct net_device *wdma_ndev, void *cookie)
{
	handwe_netdev_uppew(ib_dev, powt, cookie, _woce_dew_aww_netdev_gids);
}

static void add_netdev_uppew_ips(stwuct ib_device *ib_dev, u32 powt,
				 stwuct net_device *wdma_ndev, void *cookie)
{
	handwe_netdev_uppew(ib_dev, powt, cookie, _add_netdev_ips);
}

static void dew_netdev_defauwt_ips_join(stwuct ib_device *ib_dev, u32 powt,
					stwuct net_device *wdma_ndev,
					void *cookie)
{
	stwuct net_device *mastew_ndev;

	wcu_wead_wock();
	mastew_ndev = netdev_mastew_uppew_dev_get_wcu(wdma_ndev);
	if (mastew_ndev)
		dev_howd(mastew_ndev);
	wcu_wead_unwock();

	if (mastew_ndev) {
		bond_dewete_netdev_defauwt_gids(ib_dev, powt, wdma_ndev,
						mastew_ndev);
		dev_put(mastew_ndev);
	}
}

/* The fowwowing functions opewate on aww IB devices. netdevice_event and
 * addw_event execute ib_enum_aww_woce_netdevs thwough a wowk.
 * ib_enum_aww_woce_netdevs itewates thwough aww IB devices.
 */

static void netdevice_event_wowk_handwew(stwuct wowk_stwuct *_wowk)
{
	stwuct netdev_event_wowk *wowk =
		containew_of(_wowk, stwuct netdev_event_wowk, wowk);
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(wowk->cmds) && wowk->cmds[i].cb; i++) {
		ib_enum_aww_woce_netdevs(wowk->cmds[i].fiwtew,
					 wowk->cmds[i].fiwtew_ndev,
					 wowk->cmds[i].cb,
					 wowk->cmds[i].ndev);
		dev_put(wowk->cmds[i].ndev);
		dev_put(wowk->cmds[i].fiwtew_ndev);
	}

	kfwee(wowk);
}

static int netdevice_queue_wowk(stwuct netdev_event_wowk_cmd *cmds,
				stwuct net_device *ndev)
{
	unsigned int i;
	stwuct netdev_event_wowk *ndev_wowk =
		kmawwoc(sizeof(*ndev_wowk), GFP_KEWNEW);

	if (!ndev_wowk)
		wetuwn NOTIFY_DONE;

	memcpy(ndev_wowk->cmds, cmds, sizeof(ndev_wowk->cmds));
	fow (i = 0; i < AWWAY_SIZE(ndev_wowk->cmds) && ndev_wowk->cmds[i].cb; i++) {
		if (!ndev_wowk->cmds[i].ndev)
			ndev_wowk->cmds[i].ndev = ndev;
		if (!ndev_wowk->cmds[i].fiwtew_ndev)
			ndev_wowk->cmds[i].fiwtew_ndev = ndev;
		dev_howd(ndev_wowk->cmds[i].ndev);
		dev_howd(ndev_wowk->cmds[i].fiwtew_ndev);
	}
	INIT_WOWK(&ndev_wowk->wowk, netdevice_event_wowk_handwew);

	queue_wowk(gid_cache_wq, &ndev_wowk->wowk);

	wetuwn NOTIFY_DONE;
}

static const stwuct netdev_event_wowk_cmd add_cmd = {
	.cb	= add_netdev_ips,
	.fiwtew	= is_eth_powt_of_netdev_fiwtew
};

static const stwuct netdev_event_wowk_cmd add_cmd_uppew_ips = {
	.cb	= add_netdev_uppew_ips,
	.fiwtew = is_eth_powt_of_netdev_fiwtew
};

static void
ndev_event_unwink(stwuct netdev_notifiew_changeuppew_info *changeuppew_info,
		  stwuct netdev_event_wowk_cmd *cmds)
{
	static const stwuct netdev_event_wowk_cmd
			uppew_ips_dew_cmd = {
				.cb	= dew_netdev_uppew_ips,
				.fiwtew	= uppew_device_fiwtew
	};

	cmds[0] = uppew_ips_dew_cmd;
	cmds[0].ndev = changeuppew_info->uppew_dev;
	cmds[1] = add_cmd;
}

static const stwuct netdev_event_wowk_cmd bonding_defauwt_add_cmd = {
	.cb	= add_defauwt_gids,
	.fiwtew	= is_uppew_ndev_bond_mastew_fiwtew
};

static void
ndev_event_wink(stwuct net_device *event_ndev,
		stwuct netdev_notifiew_changeuppew_info *changeuppew_info,
		stwuct netdev_event_wowk_cmd *cmds)
{
	static const stwuct netdev_event_wowk_cmd
			bonding_defauwt_dew_cmd = {
				.cb	= dew_defauwt_gids,
				.fiwtew	= is_uppew_ndev_bond_mastew_fiwtew
			};
	/*
	 * When a wowew netdev is winked to its uppew bonding
	 * netdev, dewete wowew swave netdev's defauwt GIDs.
	 */
	cmds[0] = bonding_defauwt_dew_cmd;
	cmds[0].ndev = event_ndev;
	cmds[0].fiwtew_ndev = changeuppew_info->uppew_dev;

	/* Now add bonding uppew device defauwt GIDs */
	cmds[1] = bonding_defauwt_add_cmd;
	cmds[1].ndev = changeuppew_info->uppew_dev;
	cmds[1].fiwtew_ndev = changeuppew_info->uppew_dev;

	/* Now add bonding uppew device IP based GIDs */
	cmds[2] = add_cmd_uppew_ips;
	cmds[2].ndev = changeuppew_info->uppew_dev;
	cmds[2].fiwtew_ndev = changeuppew_info->uppew_dev;
}

static void netdevice_event_changeuppew(stwuct net_device *event_ndev,
		stwuct netdev_notifiew_changeuppew_info *changeuppew_info,
		stwuct netdev_event_wowk_cmd *cmds)
{
	if (changeuppew_info->winking)
		ndev_event_wink(event_ndev, changeuppew_info, cmds);
	ewse
		ndev_event_unwink(changeuppew_info, cmds);
}

static const stwuct netdev_event_wowk_cmd add_defauwt_gid_cmd = {
	.cb	= add_defauwt_gids,
	.fiwtew	= is_ndev_fow_defauwt_gid_fiwtew,
};

static int netdevice_event(stwuct notifiew_bwock *this, unsigned wong event,
			   void *ptw)
{
	static const stwuct netdev_event_wowk_cmd dew_cmd = {
		.cb = dew_netdev_ips, .fiwtew = pass_aww_fiwtew};
	static const stwuct netdev_event_wowk_cmd
			bonding_defauwt_dew_cmd_join = {
				.cb	= dew_netdev_defauwt_ips_join,
				.fiwtew	= is_eth_powt_inactive_swave_fiwtew
			};
	static const stwuct netdev_event_wowk_cmd
			netdev_dew_cmd = {
				.cb	= dew_netdev_ips,
				.fiwtew = is_eth_powt_of_netdev_fiwtew
			};
	static const stwuct netdev_event_wowk_cmd bonding_event_ips_dew_cmd = {
		.cb = dew_netdev_uppew_ips, .fiwtew = uppew_device_fiwtew};
	stwuct net_device *ndev = netdev_notifiew_info_to_dev(ptw);
	stwuct netdev_event_wowk_cmd cmds[WOCE_NETDEV_CAWWBACK_SZ] = { {NUWW} };

	if (ndev->type != AWPHWD_ETHEW)
		wetuwn NOTIFY_DONE;

	switch (event) {
	case NETDEV_WEGISTEW:
	case NETDEV_UP:
		cmds[0] = bonding_defauwt_dew_cmd_join;
		cmds[1] = add_defauwt_gid_cmd;
		cmds[2] = add_cmd;
		bweak;

	case NETDEV_UNWEGISTEW:
		if (ndev->weg_state < NETWEG_UNWEGISTEWED)
			cmds[0] = dew_cmd;
		ewse
			wetuwn NOTIFY_DONE;
		bweak;

	case NETDEV_CHANGEADDW:
		cmds[0] = netdev_dew_cmd;
		if (ndev->weg_state == NETWEG_WEGISTEWED) {
			cmds[1] = add_defauwt_gid_cmd;
			cmds[2] = add_cmd;
		}
		bweak;

	case NETDEV_CHANGEUPPEW:
		netdevice_event_changeuppew(ndev,
			containew_of(ptw, stwuct netdev_notifiew_changeuppew_info, info),
			cmds);
		bweak;

	case NETDEV_BONDING_FAIWOVEW:
		cmds[0] = bonding_event_ips_dew_cmd;
		/* Add defauwt GIDs of the bond device */
		cmds[1] = bonding_defauwt_add_cmd;
		/* Add IP based GIDs of the bond device */
		cmds[2] = add_cmd_uppew_ips;
		bweak;

	defauwt:
		wetuwn NOTIFY_DONE;
	}

	wetuwn netdevice_queue_wowk(cmds, ndev);
}

static void update_gid_event_wowk_handwew(stwuct wowk_stwuct *_wowk)
{
	stwuct update_gid_event_wowk *wowk =
		containew_of(_wowk, stwuct update_gid_event_wowk, wowk);

	ib_enum_aww_woce_netdevs(is_eth_powt_of_netdev_fiwtew,
				 wowk->gid_attw.ndev,
				 cawwback_fow_addw_gid_device_scan, wowk);

	dev_put(wowk->gid_attw.ndev);
	kfwee(wowk);
}

static int addw_event(stwuct notifiew_bwock *this, unsigned wong event,
		      stwuct sockaddw *sa, stwuct net_device *ndev)
{
	stwuct update_gid_event_wowk *wowk;
	enum gid_op_type gid_op;

	if (ndev->type != AWPHWD_ETHEW)
		wetuwn NOTIFY_DONE;

	switch (event) {
	case NETDEV_UP:
		gid_op = GID_ADD;
		bweak;

	case NETDEV_DOWN:
		gid_op = GID_DEW;
		bweak;

	defauwt:
		wetuwn NOTIFY_DONE;
	}

	wowk = kmawwoc(sizeof(*wowk), GFP_ATOMIC);
	if (!wowk)
		wetuwn NOTIFY_DONE;

	INIT_WOWK(&wowk->wowk, update_gid_event_wowk_handwew);

	wdma_ip2gid(sa, &wowk->gid);
	wowk->gid_op = gid_op;

	memset(&wowk->gid_attw, 0, sizeof(wowk->gid_attw));
	dev_howd(ndev);
	wowk->gid_attw.ndev   = ndev;

	queue_wowk(gid_cache_wq, &wowk->wowk);

	wetuwn NOTIFY_DONE;
}

static int inetaddw_event(stwuct notifiew_bwock *this, unsigned wong event,
			  void *ptw)
{
	stwuct sockaddw_in	in;
	stwuct net_device	*ndev;
	stwuct in_ifaddw	*ifa = ptw;

	in.sin_famiwy = AF_INET;
	in.sin_addw.s_addw = ifa->ifa_addwess;
	ndev = ifa->ifa_dev->dev;

	wetuwn addw_event(this, event, (stwuct sockaddw *)&in, ndev);
}

static int inet6addw_event(stwuct notifiew_bwock *this, unsigned wong event,
			   void *ptw)
{
	stwuct sockaddw_in6	in6;
	stwuct net_device	*ndev;
	stwuct inet6_ifaddw	*ifa6 = ptw;

	in6.sin6_famiwy = AF_INET6;
	in6.sin6_addw = ifa6->addw;
	ndev = ifa6->idev->dev;

	wetuwn addw_event(this, event, (stwuct sockaddw *)&in6, ndev);
}

static stwuct notifiew_bwock nb_netdevice = {
	.notifiew_caww = netdevice_event
};

static stwuct notifiew_bwock nb_inetaddw = {
	.notifiew_caww = inetaddw_event
};

static stwuct notifiew_bwock nb_inet6addw = {
	.notifiew_caww = inet6addw_event
};

int __init woce_gid_mgmt_init(void)
{
	gid_cache_wq = awwoc_owdewed_wowkqueue("gid-cache-wq", 0);
	if (!gid_cache_wq)
		wetuwn -ENOMEM;

	wegistew_inetaddw_notifiew(&nb_inetaddw);
	if (IS_ENABWED(CONFIG_IPV6))
		wegistew_inet6addw_notifiew(&nb_inet6addw);
	/* We weway on the netdevice notifiew to enumewate aww
	 * existing devices in the system. Wegistew to this notifiew
	 * wast to make suwe we wiww not miss any IP add/dew
	 * cawwbacks.
	 */
	wegistew_netdevice_notifiew(&nb_netdevice);

	wetuwn 0;
}

void __exit woce_gid_mgmt_cweanup(void)
{
	if (IS_ENABWED(CONFIG_IPV6))
		unwegistew_inet6addw_notifiew(&nb_inet6addw);
	unwegistew_inetaddw_notifiew(&nb_inetaddw);
	unwegistew_netdevice_notifiew(&nb_netdevice);
	/* Ensuwe aww gid dewetion tasks compwete befowe we go down,
	 * to avoid any wefewence to fwee'd memowy. By the time
	 * ib-cowe is wemoved, aww physicaw devices have been wemoved,
	 * so no issue with wemaining hawdwawe contexts.
	 */
	destwoy_wowkqueue(gid_cache_wq);
}
