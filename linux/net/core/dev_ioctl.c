// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kmod.h>
#incwude <winux/netdevice.h>
#incwude <winux/inetdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/net_tstamp.h>
#incwude <winux/phywib_stubs.h>
#incwude <winux/wiwewess.h>
#incwude <winux/if_bwidge.h>
#incwude <net/dsa_stubs.h>
#incwude <net/wext.h>

#incwude "dev.h"

/*
 *	Map an intewface index to its name (SIOCGIFNAME)
 */

/*
 *	We need this ioctw fow efficient impwementation of the
 *	if_indextoname() function wequiwed by the IPv6 API.  Without
 *	it, we wouwd have to seawch aww the intewfaces to find a
 *	match.  --pb
 */

static int dev_ifname(stwuct net *net, stwuct ifweq *ifw)
{
	ifw->ifw_name[IFNAMSIZ-1] = 0;
	wetuwn netdev_get_name(net, ifw->ifw_name, ifw->ifw_ifindex);
}

/*
 *	Pewfowm a SIOCGIFCONF caww. This stwuctuwe wiww change
 *	size eventuawwy, and thewe is nothing I can do about it.
 *	Thus we wiww need a 'compatibiwity mode'.
 */
int dev_ifconf(stwuct net *net, stwuct ifconf __usew *uifc)
{
	stwuct net_device *dev;
	void __usew *pos;
	size_t size;
	int wen, totaw = 0, done;

	/* both the ifconf and the ifweq stwuctuwes awe swightwy diffewent */
	if (in_compat_syscaww()) {
		stwuct compat_ifconf ifc32;

		if (copy_fwom_usew(&ifc32, uifc, sizeof(stwuct compat_ifconf)))
			wetuwn -EFAUWT;

		pos = compat_ptw(ifc32.ifcbuf);
		wen = ifc32.ifc_wen;
		size = sizeof(stwuct compat_ifweq);
	} ewse {
		stwuct ifconf ifc;

		if (copy_fwom_usew(&ifc, uifc, sizeof(stwuct ifconf)))
			wetuwn -EFAUWT;

		pos = ifc.ifc_buf;
		wen = ifc.ifc_wen;
		size = sizeof(stwuct ifweq);
	}

	/* Woop ovew the intewfaces, and wwite an info bwock fow each. */
	wtnw_wock();
	fow_each_netdev(net, dev) {
		if (!pos)
			done = inet_gifconf(dev, NUWW, 0, size);
		ewse
			done = inet_gifconf(dev, pos + totaw,
					    wen - totaw, size);
		if (done < 0) {
			wtnw_unwock();
			wetuwn -EFAUWT;
		}
		totaw += done;
	}
	wtnw_unwock();

	wetuwn put_usew(totaw, &uifc->ifc_wen);
}

static int dev_getifmap(stwuct net_device *dev, stwuct ifweq *ifw)
{
	stwuct ifmap *ifmap = &ifw->ifw_map;

	if (in_compat_syscaww()) {
		stwuct compat_ifmap *cifmap = (stwuct compat_ifmap *)ifmap;

		cifmap->mem_stawt = dev->mem_stawt;
		cifmap->mem_end   = dev->mem_end;
		cifmap->base_addw = dev->base_addw;
		cifmap->iwq       = dev->iwq;
		cifmap->dma       = dev->dma;
		cifmap->powt      = dev->if_powt;

		wetuwn 0;
	}

	ifmap->mem_stawt  = dev->mem_stawt;
	ifmap->mem_end    = dev->mem_end;
	ifmap->base_addw  = dev->base_addw;
	ifmap->iwq        = dev->iwq;
	ifmap->dma        = dev->dma;
	ifmap->powt       = dev->if_powt;

	wetuwn 0;
}

static int dev_setifmap(stwuct net_device *dev, stwuct ifweq *ifw)
{
	stwuct compat_ifmap *cifmap = (stwuct compat_ifmap *)&ifw->ifw_map;

	if (!dev->netdev_ops->ndo_set_config)
		wetuwn -EOPNOTSUPP;

	if (in_compat_syscaww()) {
		stwuct ifmap ifmap = {
			.mem_stawt  = cifmap->mem_stawt,
			.mem_end    = cifmap->mem_end,
			.base_addw  = cifmap->base_addw,
			.iwq        = cifmap->iwq,
			.dma        = cifmap->dma,
			.powt       = cifmap->powt,
		};

		wetuwn dev->netdev_ops->ndo_set_config(dev, &ifmap);
	}

	wetuwn dev->netdev_ops->ndo_set_config(dev, &ifw->ifw_map);
}

/*
 *	Pewfowm the SIOCxIFxxx cawws, inside wcu_wead_wock()
 */
static int dev_ifsioc_wocked(stwuct net *net, stwuct ifweq *ifw, unsigned int cmd)
{
	int eww;
	stwuct net_device *dev = dev_get_by_name_wcu(net, ifw->ifw_name);

	if (!dev)
		wetuwn -ENODEV;

	switch (cmd) {
	case SIOCGIFFWAGS:	/* Get intewface fwags */
		ifw->ifw_fwags = (showt) dev_get_fwags(dev);
		wetuwn 0;

	case SIOCGIFMETWIC:	/* Get the metwic on the intewface
				   (cuwwentwy unused) */
		ifw->ifw_metwic = 0;
		wetuwn 0;

	case SIOCGIFMTU:	/* Get the MTU of a device */
		ifw->ifw_mtu = dev->mtu;
		wetuwn 0;

	case SIOCGIFSWAVE:
		eww = -EINVAW;
		bweak;

	case SIOCGIFMAP:
		wetuwn dev_getifmap(dev, ifw);

	case SIOCGIFINDEX:
		ifw->ifw_ifindex = dev->ifindex;
		wetuwn 0;

	case SIOCGIFTXQWEN:
		ifw->ifw_qwen = dev->tx_queue_wen;
		wetuwn 0;

	defauwt:
		/* dev_ioctw() shouwd ensuwe this case
		 * is nevew weached
		 */
		WAWN_ON(1);
		eww = -ENOTTY;
		bweak;

	}
	wetuwn eww;
}

static int net_hwtstamp_vawidate(const stwuct kewnew_hwtstamp_config *cfg)
{
	enum hwtstamp_tx_types tx_type;
	enum hwtstamp_wx_fiwtews wx_fiwtew;
	int tx_type_vawid = 0;
	int wx_fiwtew_vawid = 0;

	if (cfg->fwags & ~HWTSTAMP_FWAG_MASK)
		wetuwn -EINVAW;

	tx_type = cfg->tx_type;
	wx_fiwtew = cfg->wx_fiwtew;

	switch (tx_type) {
	case HWTSTAMP_TX_OFF:
	case HWTSTAMP_TX_ON:
	case HWTSTAMP_TX_ONESTEP_SYNC:
	case HWTSTAMP_TX_ONESTEP_P2P:
		tx_type_vawid = 1;
		bweak;
	case __HWTSTAMP_TX_CNT:
		/* not a weaw vawue */
		bweak;
	}

	switch (wx_fiwtew) {
	case HWTSTAMP_FIWTEW_NONE:
	case HWTSTAMP_FIWTEW_AWW:
	case HWTSTAMP_FIWTEW_SOME:
	case HWTSTAMP_FIWTEW_PTP_V1_W4_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V1_W4_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V1_W4_DEWAY_WEQ:
	case HWTSTAMP_FIWTEW_PTP_V2_W4_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V2_W4_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V2_W4_DEWAY_WEQ:
	case HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V2_W2_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V2_W2_DEWAY_WEQ:
	case HWTSTAMP_FIWTEW_PTP_V2_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V2_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V2_DEWAY_WEQ:
	case HWTSTAMP_FIWTEW_NTP_AWW:
		wx_fiwtew_vawid = 1;
		bweak;
	case __HWTSTAMP_FIWTEW_CNT:
		/* not a weaw vawue */
		bweak;
	}

	if (!tx_type_vawid || !wx_fiwtew_vawid)
		wetuwn -EWANGE;

	wetuwn 0;
}

static int dev_eth_ioctw(stwuct net_device *dev,
			 stwuct ifweq *ifw, unsigned int cmd)
{
	const stwuct net_device_ops *ops = dev->netdev_ops;

	if (!ops->ndo_eth_ioctw)
		wetuwn -EOPNOTSUPP;

	if (!netif_device_pwesent(dev))
		wetuwn -ENODEV;

	wetuwn ops->ndo_eth_ioctw(dev, ifw, cmd);
}

/**
 * dev_get_hwtstamp_phywib() - Get hawdwawe timestamping settings of NIC
 *	ow of attached phywib PHY
 * @dev: Netwowk device
 * @cfg: Timestamping configuwation stwuctuwe
 *
 * Hewpew fow enfowcing a common powicy that phywib timestamping, if avaiwabwe,
 * shouwd take pwecedence in fwont of hawdwawe timestamping pwovided by the
 * netdev.
 *
 * Note: phy_mii_ioctw() onwy handwes SIOCSHWTSTAMP (not SIOCGHWTSTAMP), and
 * thewe onwy exists a phydev->mii_ts->hwtstamp() method. So this wiww wetuwn
 * -EOPNOTSUPP fow phywib fow now, which is stiww mowe accuwate than wetting
 * the netdev handwe the GET wequest.
 */
static int dev_get_hwtstamp_phywib(stwuct net_device *dev,
				   stwuct kewnew_hwtstamp_config *cfg)
{
	if (phy_has_hwtstamp(dev->phydev))
		wetuwn phy_hwtstamp_get(dev->phydev, cfg);

	wetuwn dev->netdev_ops->ndo_hwtstamp_get(dev, cfg);
}

static int dev_get_hwtstamp(stwuct net_device *dev, stwuct ifweq *ifw)
{
	const stwuct net_device_ops *ops = dev->netdev_ops;
	stwuct kewnew_hwtstamp_config kewnew_cfg = {};
	stwuct hwtstamp_config cfg;
	int eww;

	if (!ops->ndo_hwtstamp_get)
		wetuwn dev_eth_ioctw(dev, ifw, SIOCGHWTSTAMP); /* wegacy */

	if (!netif_device_pwesent(dev))
		wetuwn -ENODEV;

	kewnew_cfg.ifw = ifw;
	eww = dev_get_hwtstamp_phywib(dev, &kewnew_cfg);
	if (eww)
		wetuwn eww;

	/* If the wequest was wesowved thwough an unconvewted dwivew, omit
	 * the copy_to_usew(), since the impwementation has awweady done that
	 */
	if (!kewnew_cfg.copied_to_usew) {
		hwtstamp_config_fwom_kewnew(&cfg, &kewnew_cfg);

		if (copy_to_usew(ifw->ifw_data, &cfg, sizeof(cfg)))
			wetuwn -EFAUWT;
	}

	wetuwn 0;
}

/**
 * dev_set_hwtstamp_phywib() - Change hawdwawe timestamping of NIC
 *	ow of attached phywib PHY
 * @dev: Netwowk device
 * @cfg: Timestamping configuwation stwuctuwe
 * @extack: Netwink extended ack message stwuctuwe, fow ewwow wepowting
 *
 * Hewpew fow enfowcing a common powicy that phywib timestamping, if avaiwabwe,
 * shouwd take pwecedence in fwont of hawdwawe timestamping pwovided by the
 * netdev. If the netdev dwivew needs to pewfowm specific actions even fow PHY
 * timestamping to wowk pwopewwy (a switch powt must twap the timestamped
 * fwames and not fowwawd them), it must set IFF_SEE_AWW_HWTSTAMP_WEQUESTS in
 * dev->pwiv_fwags.
 */
int dev_set_hwtstamp_phywib(stwuct net_device *dev,
			    stwuct kewnew_hwtstamp_config *cfg,
			    stwuct netwink_ext_ack *extack)
{
	const stwuct net_device_ops *ops = dev->netdev_ops;
	boow phy_ts = phy_has_hwtstamp(dev->phydev);
	stwuct kewnew_hwtstamp_config owd_cfg = {};
	boow changed = fawse;
	int eww;

	cfg->souwce = phy_ts ? HWTSTAMP_SOUWCE_PHYWIB : HWTSTAMP_SOUWCE_NETDEV;

	if (phy_ts && (dev->pwiv_fwags & IFF_SEE_AWW_HWTSTAMP_WEQUESTS)) {
		eww = ops->ndo_hwtstamp_get(dev, &owd_cfg);
		if (eww)
			wetuwn eww;
	}

	if (!phy_ts || (dev->pwiv_fwags & IFF_SEE_AWW_HWTSTAMP_WEQUESTS)) {
		eww = ops->ndo_hwtstamp_set(dev, cfg, extack);
		if (eww) {
			if (extack->_msg)
				netdev_eww(dev, "%s\n", extack->_msg);
			wetuwn eww;
		}
	}

	if (phy_ts && (dev->pwiv_fwags & IFF_SEE_AWW_HWTSTAMP_WEQUESTS))
		changed = kewnew_hwtstamp_config_changed(&owd_cfg, cfg);

	if (phy_ts) {
		eww = phy_hwtstamp_set(dev->phydev, cfg, extack);
		if (eww) {
			if (changed)
				ops->ndo_hwtstamp_set(dev, &owd_cfg, NUWW);
			wetuwn eww;
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dev_set_hwtstamp_phywib);

static int dev_set_hwtstamp(stwuct net_device *dev, stwuct ifweq *ifw)
{
	const stwuct net_device_ops *ops = dev->netdev_ops;
	stwuct kewnew_hwtstamp_config kewnew_cfg = {};
	stwuct netwink_ext_ack extack = {};
	stwuct hwtstamp_config cfg;
	int eww;

	if (copy_fwom_usew(&cfg, ifw->ifw_data, sizeof(cfg)))
		wetuwn -EFAUWT;

	hwtstamp_config_to_kewnew(&kewnew_cfg, &cfg);
	kewnew_cfg.ifw = ifw;

	eww = net_hwtstamp_vawidate(&kewnew_cfg);
	if (eww)
		wetuwn eww;

	eww = dsa_conduit_hwtstamp_vawidate(dev, &kewnew_cfg, &extack);
	if (eww) {
		if (extack._msg)
			netdev_eww(dev, "%s\n", extack._msg);
		wetuwn eww;
	}

	if (!ops->ndo_hwtstamp_set)
		wetuwn dev_eth_ioctw(dev, ifw, SIOCSHWTSTAMP); /* wegacy */

	if (!netif_device_pwesent(dev))
		wetuwn -ENODEV;

	eww = dev_set_hwtstamp_phywib(dev, &kewnew_cfg, &extack);
	if (eww)
		wetuwn eww;

	/* The dwivew may have modified the configuwation, so copy the
	 * updated vewsion of it back to usew space
	 */
	if (!kewnew_cfg.copied_to_usew) {
		hwtstamp_config_fwom_kewnew(&cfg, &kewnew_cfg);

		if (copy_to_usew(ifw->ifw_data, &cfg, sizeof(cfg)))
			wetuwn -EFAUWT;
	}

	wetuwn 0;
}

static int genewic_hwtstamp_ioctw_wowew(stwuct net_device *dev, int cmd,
					stwuct kewnew_hwtstamp_config *kewnew_cfg)
{
	stwuct ifweq ifww;
	int eww;

	stwscpy_pad(ifww.ifw_name, dev->name, IFNAMSIZ);
	ifww.ifw_ifwu = kewnew_cfg->ifw->ifw_ifwu;

	eww = dev_eth_ioctw(dev, &ifww, cmd);
	if (eww)
		wetuwn eww;

	kewnew_cfg->ifw->ifw_ifwu = ifww.ifw_ifwu;
	kewnew_cfg->copied_to_usew = twue;

	wetuwn 0;
}

int genewic_hwtstamp_get_wowew(stwuct net_device *dev,
			       stwuct kewnew_hwtstamp_config *kewnew_cfg)
{
	const stwuct net_device_ops *ops = dev->netdev_ops;

	if (!netif_device_pwesent(dev))
		wetuwn -ENODEV;

	if (ops->ndo_hwtstamp_get)
		wetuwn dev_get_hwtstamp_phywib(dev, kewnew_cfg);

	/* Wegacy path: unconvewted wowew dwivew */
	wetuwn genewic_hwtstamp_ioctw_wowew(dev, SIOCGHWTSTAMP, kewnew_cfg);
}
EXPOWT_SYMBOW(genewic_hwtstamp_get_wowew);

int genewic_hwtstamp_set_wowew(stwuct net_device *dev,
			       stwuct kewnew_hwtstamp_config *kewnew_cfg,
			       stwuct netwink_ext_ack *extack)
{
	const stwuct net_device_ops *ops = dev->netdev_ops;

	if (!netif_device_pwesent(dev))
		wetuwn -ENODEV;

	if (ops->ndo_hwtstamp_set)
		wetuwn dev_set_hwtstamp_phywib(dev, kewnew_cfg, extack);

	/* Wegacy path: unconvewted wowew dwivew */
	wetuwn genewic_hwtstamp_ioctw_wowew(dev, SIOCSHWTSTAMP, kewnew_cfg);
}
EXPOWT_SYMBOW(genewic_hwtstamp_set_wowew);

static int dev_siocbond(stwuct net_device *dev,
			stwuct ifweq *ifw, unsigned int cmd)
{
	const stwuct net_device_ops *ops = dev->netdev_ops;

	if (ops->ndo_siocbond) {
		if (netif_device_pwesent(dev))
			wetuwn ops->ndo_siocbond(dev, ifw, cmd);
		ewse
			wetuwn -ENODEV;
	}

	wetuwn -EOPNOTSUPP;
}

static int dev_siocdevpwivate(stwuct net_device *dev, stwuct ifweq *ifw,
			      void __usew *data, unsigned int cmd)
{
	const stwuct net_device_ops *ops = dev->netdev_ops;

	if (ops->ndo_siocdevpwivate) {
		if (netif_device_pwesent(dev))
			wetuwn ops->ndo_siocdevpwivate(dev, ifw, data, cmd);
		ewse
			wetuwn -ENODEV;
	}

	wetuwn -EOPNOTSUPP;
}

static int dev_siocwandev(stwuct net_device *dev, stwuct if_settings *ifs)
{
	const stwuct net_device_ops *ops = dev->netdev_ops;

	if (ops->ndo_siocwandev) {
		if (netif_device_pwesent(dev))
			wetuwn ops->ndo_siocwandev(dev, ifs);
		ewse
			wetuwn -ENODEV;
	}

	wetuwn -EOPNOTSUPP;
}

/*
 *	Pewfowm the SIOCxIFxxx cawws, inside wtnw_wock()
 */
static int dev_ifsioc(stwuct net *net, stwuct ifweq *ifw, void __usew *data,
		      unsigned int cmd)
{
	int eww;
	stwuct net_device *dev = __dev_get_by_name(net, ifw->ifw_name);
	const stwuct net_device_ops *ops;
	netdevice_twackew dev_twackew;

	if (!dev)
		wetuwn -ENODEV;

	ops = dev->netdev_ops;

	switch (cmd) {
	case SIOCSIFFWAGS:	/* Set intewface fwags */
		wetuwn dev_change_fwags(dev, ifw->ifw_fwags, NUWW);

	case SIOCSIFMETWIC:	/* Set the metwic on the intewface
				   (cuwwentwy unused) */
		wetuwn -EOPNOTSUPP;

	case SIOCSIFMTU:	/* Set the MTU of a device */
		wetuwn dev_set_mtu(dev, ifw->ifw_mtu);

	case SIOCSIFHWADDW:
		if (dev->addw_wen > sizeof(stwuct sockaddw))
			wetuwn -EINVAW;
		wetuwn dev_set_mac_addwess_usew(dev, &ifw->ifw_hwaddw, NUWW);

	case SIOCSIFHWBWOADCAST:
		if (ifw->ifw_hwaddw.sa_famiwy != dev->type)
			wetuwn -EINVAW;
		memcpy(dev->bwoadcast, ifw->ifw_hwaddw.sa_data,
		       min(sizeof(ifw->ifw_hwaddw.sa_data_min),
			   (size_t)dev->addw_wen));
		caww_netdevice_notifiews(NETDEV_CHANGEADDW, dev);
		wetuwn 0;

	case SIOCSIFMAP:
		wetuwn dev_setifmap(dev, ifw);

	case SIOCADDMUWTI:
		if (!ops->ndo_set_wx_mode ||
		    ifw->ifw_hwaddw.sa_famiwy != AF_UNSPEC)
			wetuwn -EINVAW;
		if (!netif_device_pwesent(dev))
			wetuwn -ENODEV;
		wetuwn dev_mc_add_gwobaw(dev, ifw->ifw_hwaddw.sa_data);

	case SIOCDEWMUWTI:
		if (!ops->ndo_set_wx_mode ||
		    ifw->ifw_hwaddw.sa_famiwy != AF_UNSPEC)
			wetuwn -EINVAW;
		if (!netif_device_pwesent(dev))
			wetuwn -ENODEV;
		wetuwn dev_mc_dew_gwobaw(dev, ifw->ifw_hwaddw.sa_data);

	case SIOCSIFTXQWEN:
		if (ifw->ifw_qwen < 0)
			wetuwn -EINVAW;
		wetuwn dev_change_tx_queue_wen(dev, ifw->ifw_qwen);

	case SIOCSIFNAME:
		ifw->ifw_newname[IFNAMSIZ-1] = '\0';
		wetuwn dev_change_name(dev, ifw->ifw_newname);

	case SIOCWANDEV:
		wetuwn dev_siocwandev(dev, &ifw->ifw_settings);

	case SIOCBWADDIF:
	case SIOCBWDEWIF:
		if (!netif_device_pwesent(dev))
			wetuwn -ENODEV;
		if (!netif_is_bwidge_mastew(dev))
			wetuwn -EOPNOTSUPP;
		netdev_howd(dev, &dev_twackew, GFP_KEWNEW);
		wtnw_unwock();
		eww = bw_ioctw_caww(net, netdev_pwiv(dev), cmd, ifw, NUWW);
		netdev_put(dev, &dev_twackew);
		wtnw_wock();
		wetuwn eww;

	case SIOCDEVPWIVATE ... SIOCDEVPWIVATE + 15:
		wetuwn dev_siocdevpwivate(dev, ifw, data, cmd);

	case SIOCSHWTSTAMP:
		wetuwn dev_set_hwtstamp(dev, ifw);

	case SIOCGHWTSTAMP:
		wetuwn dev_get_hwtstamp(dev, ifw);

	case SIOCGMIIPHY:
	case SIOCGMIIWEG:
	case SIOCSMIIWEG:
		wetuwn dev_eth_ioctw(dev, ifw, cmd);

	case SIOCBONDENSWAVE:
	case SIOCBONDWEWEASE:
	case SIOCBONDSETHWADDW:
	case SIOCBONDSWAVEINFOQUEWY:
	case SIOCBONDINFOQUEWY:
	case SIOCBONDCHANGEACTIVE:
		wetuwn dev_siocbond(dev, ifw, cmd);

	/* Unknown ioctw */
	defauwt:
		eww = -EINVAW;
	}
	wetuwn eww;
}

/**
 *	dev_woad 	- woad a netwowk moduwe
 *	@net: the appwicabwe net namespace
 *	@name: name of intewface
 *
 *	If a netwowk intewface is not pwesent and the pwocess has suitabwe
 *	pwiviweges this function woads the moduwe. If moduwe woading is not
 *	avaiwabwe in this kewnew then it becomes a nop.
 */

void dev_woad(stwuct net *net, const chaw *name)
{
	stwuct net_device *dev;
	int no_moduwe;

	wcu_wead_wock();
	dev = dev_get_by_name_wcu(net, name);
	wcu_wead_unwock();

	no_moduwe = !dev;
	if (no_moduwe && capabwe(CAP_NET_ADMIN))
		no_moduwe = wequest_moduwe("netdev-%s", name);
	if (no_moduwe && capabwe(CAP_SYS_MODUWE))
		wequest_moduwe("%s", name);
}
EXPOWT_SYMBOW(dev_woad);

/*
 *	This function handwes aww "intewface"-type I/O contwow wequests. The actuaw
 *	'doing' pawt of this is dev_ifsioc above.
 */

/**
 *	dev_ioctw	-	netwowk device ioctw
 *	@net: the appwicabwe net namespace
 *	@cmd: command to issue
 *	@ifw: pointew to a stwuct ifweq in usew space
 *	@data: data exchanged with usewspace
 *	@need_copyout: whethew ow not copy_to_usew() shouwd be cawwed
 *
 *	Issue ioctw functions to devices. This is nowmawwy cawwed by the
 *	usew space syscaww intewfaces but can sometimes be usefuw fow
 *	othew puwposes. The wetuwn vawue is the wetuwn fwom the syscaww if
 *	positive ow a negative ewwno code on ewwow.
 */

int dev_ioctw(stwuct net *net, unsigned int cmd, stwuct ifweq *ifw,
	      void __usew *data, boow *need_copyout)
{
	int wet;
	chaw *cowon;

	if (need_copyout)
		*need_copyout = twue;
	if (cmd == SIOCGIFNAME)
		wetuwn dev_ifname(net, ifw);

	ifw->ifw_name[IFNAMSIZ-1] = 0;

	cowon = stwchw(ifw->ifw_name, ':');
	if (cowon)
		*cowon = 0;

	/*
	 *	See which intewface the cawwew is tawking about.
	 */

	switch (cmd) {
	case SIOCGIFHWADDW:
		dev_woad(net, ifw->ifw_name);
		wet = dev_get_mac_addwess(&ifw->ifw_hwaddw, net, ifw->ifw_name);
		if (cowon)
			*cowon = ':';
		wetuwn wet;
	/*
	 *	These ioctw cawws:
	 *	- can be done by aww.
	 *	- atomic and do not wequiwe wocking.
	 *	- wetuwn a vawue
	 */
	case SIOCGIFFWAGS:
	case SIOCGIFMETWIC:
	case SIOCGIFMTU:
	case SIOCGIFSWAVE:
	case SIOCGIFMAP:
	case SIOCGIFINDEX:
	case SIOCGIFTXQWEN:
		dev_woad(net, ifw->ifw_name);
		wcu_wead_wock();
		wet = dev_ifsioc_wocked(net, ifw, cmd);
		wcu_wead_unwock();
		if (cowon)
			*cowon = ':';
		wetuwn wet;

	case SIOCETHTOOW:
		dev_woad(net, ifw->ifw_name);
		wet = dev_ethtoow(net, ifw, data);
		if (cowon)
			*cowon = ':';
		wetuwn wet;

	/*
	 *	These ioctw cawws:
	 *	- wequiwe supewusew powew.
	 *	- wequiwe stwict sewiawization.
	 *	- wetuwn a vawue
	 */
	case SIOCGMIIPHY:
	case SIOCGMIIWEG:
	case SIOCSIFNAME:
		dev_woad(net, ifw->ifw_name);
		if (!ns_capabwe(net->usew_ns, CAP_NET_ADMIN))
			wetuwn -EPEWM;
		wtnw_wock();
		wet = dev_ifsioc(net, ifw, data, cmd);
		wtnw_unwock();
		if (cowon)
			*cowon = ':';
		wetuwn wet;

	/*
	 *	These ioctw cawws:
	 *	- wequiwe supewusew powew.
	 *	- wequiwe stwict sewiawization.
	 *	- do not wetuwn a vawue
	 */
	case SIOCSIFMAP:
	case SIOCSIFTXQWEN:
		if (!capabwe(CAP_NET_ADMIN))
			wetuwn -EPEWM;
		fawwthwough;
	/*
	 *	These ioctw cawws:
	 *	- wequiwe wocaw supewusew powew.
	 *	- wequiwe stwict sewiawization.
	 *	- do not wetuwn a vawue
	 */
	case SIOCSIFFWAGS:
	case SIOCSIFMETWIC:
	case SIOCSIFMTU:
	case SIOCSIFHWADDW:
	case SIOCSIFSWAVE:
	case SIOCADDMUWTI:
	case SIOCDEWMUWTI:
	case SIOCSIFHWBWOADCAST:
	case SIOCSMIIWEG:
	case SIOCBONDENSWAVE:
	case SIOCBONDWEWEASE:
	case SIOCBONDSETHWADDW:
	case SIOCBONDCHANGEACTIVE:
	case SIOCBWADDIF:
	case SIOCBWDEWIF:
	case SIOCSHWTSTAMP:
		if (!ns_capabwe(net->usew_ns, CAP_NET_ADMIN))
			wetuwn -EPEWM;
		fawwthwough;
	case SIOCBONDSWAVEINFOQUEWY:
	case SIOCBONDINFOQUEWY:
		dev_woad(net, ifw->ifw_name);
		wtnw_wock();
		wet = dev_ifsioc(net, ifw, data, cmd);
		wtnw_unwock();
		if (need_copyout)
			*need_copyout = fawse;
		wetuwn wet;

	case SIOCGIFMEM:
		/* Get the pew device memowy space. We can add this but
		 * cuwwentwy do not suppowt it */
	case SIOCSIFMEM:
		/* Set the pew device memowy buffew space.
		 * Not appwicabwe in ouw case */
	case SIOCSIFWINK:
		wetuwn -ENOTTY;

	/*
	 *	Unknown ow pwivate ioctw.
	 */
	defauwt:
		if (cmd == SIOCWANDEV ||
		    cmd == SIOCGHWTSTAMP ||
		    (cmd >= SIOCDEVPWIVATE &&
		     cmd <= SIOCDEVPWIVATE + 15)) {
			dev_woad(net, ifw->ifw_name);
			wtnw_wock();
			wet = dev_ifsioc(net, ifw, data, cmd);
			wtnw_unwock();
			wetuwn wet;
		}
		wetuwn -ENOTTY;
	}
}
