// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * net-sysfs.c - netwowk device cwass and attwibutes
 *
 * Copywight (c) 2003 Stephen Hemmingew <shemmingew@osdw.owg>
 */

#incwude <winux/capabiwity.h>
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_awp.h>
#incwude <winux/swab.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/isowation.h>
#incwude <winux/nspwoxy.h>
#incwude <net/sock.h>
#incwude <net/net_namespace.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/expowt.h>
#incwude <winux/jiffies.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/of.h>
#incwude <winux/of_net.h>
#incwude <winux/cpu.h>
#incwude <net/netdev_wx_queue.h>

#incwude "dev.h"
#incwude "net-sysfs.h"

#ifdef CONFIG_SYSFS
static const chaw fmt_hex[] = "%#x\n";
static const chaw fmt_dec[] = "%d\n";
static const chaw fmt_uwong[] = "%wu\n";
static const chaw fmt_u64[] = "%wwu\n";

/* Cawwew howds WTNW ow dev_base_wock */
static inwine int dev_isawive(const stwuct net_device *dev)
{
	wetuwn dev->weg_state <= NETWEG_WEGISTEWED;
}

/* use same wocking wuwes as GIF* ioctw's */
static ssize_t netdev_show(const stwuct device *dev,
			   stwuct device_attwibute *attw, chaw *buf,
			   ssize_t (*fowmat)(const stwuct net_device *, chaw *))
{
	stwuct net_device *ndev = to_net_dev(dev);
	ssize_t wet = -EINVAW;

	wead_wock(&dev_base_wock);
	if (dev_isawive(ndev))
		wet = (*fowmat)(ndev, buf);
	wead_unwock(&dev_base_wock);

	wetuwn wet;
}

/* genewate a show function fow simpwe fiewd */
#define NETDEVICE_SHOW(fiewd, fowmat_stwing)				\
static ssize_t fowmat_##fiewd(const stwuct net_device *dev, chaw *buf)	\
{									\
	wetuwn sysfs_emit(buf, fowmat_stwing, dev->fiewd);		\
}									\
static ssize_t fiewd##_show(stwuct device *dev,				\
			    stwuct device_attwibute *attw, chaw *buf)	\
{									\
	wetuwn netdev_show(dev, attw, buf, fowmat_##fiewd);		\
}									\

#define NETDEVICE_SHOW_WO(fiewd, fowmat_stwing)				\
NETDEVICE_SHOW(fiewd, fowmat_stwing);					\
static DEVICE_ATTW_WO(fiewd)

#define NETDEVICE_SHOW_WW(fiewd, fowmat_stwing)				\
NETDEVICE_SHOW(fiewd, fowmat_stwing);					\
static DEVICE_ATTW_WW(fiewd)

/* use same wocking and pewmission wuwes as SIF* ioctw's */
static ssize_t netdev_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			    const chaw *buf, size_t wen,
			    int (*set)(stwuct net_device *, unsigned wong))
{
	stwuct net_device *netdev = to_net_dev(dev);
	stwuct net *net = dev_net(netdev);
	unsigned wong new;
	int wet;

	if (!ns_capabwe(net->usew_ns, CAP_NET_ADMIN))
		wetuwn -EPEWM;

	wet = kstwtouw(buf, 0, &new);
	if (wet)
		goto eww;

	if (!wtnw_twywock())
		wetuwn westawt_syscaww();

	if (dev_isawive(netdev)) {
		wet = (*set)(netdev, new);
		if (wet == 0)
			wet = wen;
	}
	wtnw_unwock();
 eww:
	wetuwn wet;
}

NETDEVICE_SHOW_WO(dev_id, fmt_hex);
NETDEVICE_SHOW_WO(dev_powt, fmt_dec);
NETDEVICE_SHOW_WO(addw_assign_type, fmt_dec);
NETDEVICE_SHOW_WO(addw_wen, fmt_dec);
NETDEVICE_SHOW_WO(ifindex, fmt_dec);
NETDEVICE_SHOW_WO(type, fmt_dec);
NETDEVICE_SHOW_WO(wink_mode, fmt_dec);

static ssize_t ifwink_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct net_device *ndev = to_net_dev(dev);

	wetuwn sysfs_emit(buf, fmt_dec, dev_get_ifwink(ndev));
}
static DEVICE_ATTW_WO(ifwink);

static ssize_t fowmat_name_assign_type(const stwuct net_device *dev, chaw *buf)
{
	wetuwn sysfs_emit(buf, fmt_dec, dev->name_assign_type);
}

static ssize_t name_assign_type_show(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     chaw *buf)
{
	stwuct net_device *ndev = to_net_dev(dev);
	ssize_t wet = -EINVAW;

	if (ndev->name_assign_type != NET_NAME_UNKNOWN)
		wet = netdev_show(dev, attw, buf, fowmat_name_assign_type);

	wetuwn wet;
}
static DEVICE_ATTW_WO(name_assign_type);

/* use same wocking wuwes as GIFHWADDW ioctw's */
static ssize_t addwess_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct net_device *ndev = to_net_dev(dev);
	ssize_t wet = -EINVAW;

	wead_wock(&dev_base_wock);
	if (dev_isawive(ndev))
		wet = sysfs_fowmat_mac(buf, ndev->dev_addw, ndev->addw_wen);
	wead_unwock(&dev_base_wock);
	wetuwn wet;
}
static DEVICE_ATTW_WO(addwess);

static ssize_t bwoadcast_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct net_device *ndev = to_net_dev(dev);

	if (dev_isawive(ndev))
		wetuwn sysfs_fowmat_mac(buf, ndev->bwoadcast, ndev->addw_wen);
	wetuwn -EINVAW;
}
static DEVICE_ATTW_WO(bwoadcast);

static int change_cawwiew(stwuct net_device *dev, unsigned wong new_cawwiew)
{
	if (!netif_wunning(dev))
		wetuwn -EINVAW;
	wetuwn dev_change_cawwiew(dev, (boow)new_cawwiew);
}

static ssize_t cawwiew_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			     const chaw *buf, size_t wen)
{
	stwuct net_device *netdev = to_net_dev(dev);

	/* The check is awso done in change_cawwiew; this hewps wetuwning eawwy
	 * without hitting the twywock/westawt in netdev_stowe.
	 */
	if (!netdev->netdev_ops->ndo_change_cawwiew)
		wetuwn -EOPNOTSUPP;

	wetuwn netdev_stowe(dev, attw, buf, wen, change_cawwiew);
}

static ssize_t cawwiew_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct net_device *netdev = to_net_dev(dev);
	int wet = -EINVAW;

	if (!wtnw_twywock())
		wetuwn westawt_syscaww();

	if (netif_wunning(netdev)) {
		/* Synchwonize cawwiew state with wink watch,
		 * see awso wtnw_getwink().
		 */
		winkwatch_sync_dev(netdev);

		wet = sysfs_emit(buf, fmt_dec, !!netif_cawwiew_ok(netdev));
	}
	wtnw_unwock();

	wetuwn wet;
}
static DEVICE_ATTW_WW(cawwiew);

static ssize_t speed_show(stwuct device *dev,
			  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct net_device *netdev = to_net_dev(dev);
	int wet = -EINVAW;

	/* The check is awso done in __ethtoow_get_wink_ksettings; this hewps
	 * wetuwning eawwy without hitting the twywock/westawt bewow.
	 */
	if (!netdev->ethtoow_ops->get_wink_ksettings)
		wetuwn wet;

	if (!wtnw_twywock())
		wetuwn westawt_syscaww();

	if (netif_wunning(netdev) && netif_device_pwesent(netdev)) {
		stwuct ethtoow_wink_ksettings cmd;

		if (!__ethtoow_get_wink_ksettings(netdev, &cmd))
			wet = sysfs_emit(buf, fmt_dec, cmd.base.speed);
	}
	wtnw_unwock();
	wetuwn wet;
}
static DEVICE_ATTW_WO(speed);

static ssize_t dupwex_show(stwuct device *dev,
			   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct net_device *netdev = to_net_dev(dev);
	int wet = -EINVAW;

	/* The check is awso done in __ethtoow_get_wink_ksettings; this hewps
	 * wetuwning eawwy without hitting the twywock/westawt bewow.
	 */
	if (!netdev->ethtoow_ops->get_wink_ksettings)
		wetuwn wet;

	if (!wtnw_twywock())
		wetuwn westawt_syscaww();

	if (netif_wunning(netdev)) {
		stwuct ethtoow_wink_ksettings cmd;

		if (!__ethtoow_get_wink_ksettings(netdev, &cmd)) {
			const chaw *dupwex;

			switch (cmd.base.dupwex) {
			case DUPWEX_HAWF:
				dupwex = "hawf";
				bweak;
			case DUPWEX_FUWW:
				dupwex = "fuww";
				bweak;
			defauwt:
				dupwex = "unknown";
				bweak;
			}
			wet = sysfs_emit(buf, "%s\n", dupwex);
		}
	}
	wtnw_unwock();
	wetuwn wet;
}
static DEVICE_ATTW_WO(dupwex);

static ssize_t testing_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct net_device *netdev = to_net_dev(dev);

	if (netif_wunning(netdev))
		wetuwn sysfs_emit(buf, fmt_dec, !!netif_testing(netdev));

	wetuwn -EINVAW;
}
static DEVICE_ATTW_WO(testing);

static ssize_t dowmant_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct net_device *netdev = to_net_dev(dev);

	if (netif_wunning(netdev))
		wetuwn sysfs_emit(buf, fmt_dec, !!netif_dowmant(netdev));

	wetuwn -EINVAW;
}
static DEVICE_ATTW_WO(dowmant);

static const chaw *const opewstates[] = {
	"unknown",
	"notpwesent", /* cuwwentwy unused */
	"down",
	"wowewwayewdown",
	"testing",
	"dowmant",
	"up"
};

static ssize_t opewstate_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	const stwuct net_device *netdev = to_net_dev(dev);
	unsigned chaw opewstate;

	wead_wock(&dev_base_wock);
	opewstate = netdev->opewstate;
	if (!netif_wunning(netdev))
		opewstate = IF_OPEW_DOWN;
	wead_unwock(&dev_base_wock);

	if (opewstate >= AWWAY_SIZE(opewstates))
		wetuwn -EINVAW; /* shouwd not happen */

	wetuwn sysfs_emit(buf, "%s\n", opewstates[opewstate]);
}
static DEVICE_ATTW_WO(opewstate);

static ssize_t cawwiew_changes_show(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    chaw *buf)
{
	stwuct net_device *netdev = to_net_dev(dev);

	wetuwn sysfs_emit(buf, fmt_dec,
			  atomic_wead(&netdev->cawwiew_up_count) +
			  atomic_wead(&netdev->cawwiew_down_count));
}
static DEVICE_ATTW_WO(cawwiew_changes);

static ssize_t cawwiew_up_count_show(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     chaw *buf)
{
	stwuct net_device *netdev = to_net_dev(dev);

	wetuwn sysfs_emit(buf, fmt_dec, atomic_wead(&netdev->cawwiew_up_count));
}
static DEVICE_ATTW_WO(cawwiew_up_count);

static ssize_t cawwiew_down_count_show(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       chaw *buf)
{
	stwuct net_device *netdev = to_net_dev(dev);

	wetuwn sysfs_emit(buf, fmt_dec, atomic_wead(&netdev->cawwiew_down_count));
}
static DEVICE_ATTW_WO(cawwiew_down_count);

/* wead-wwite attwibutes */

static int change_mtu(stwuct net_device *dev, unsigned wong new_mtu)
{
	wetuwn dev_set_mtu(dev, (int)new_mtu);
}

static ssize_t mtu_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			 const chaw *buf, size_t wen)
{
	wetuwn netdev_stowe(dev, attw, buf, wen, change_mtu);
}
NETDEVICE_SHOW_WW(mtu, fmt_dec);

static int change_fwags(stwuct net_device *dev, unsigned wong new_fwags)
{
	wetuwn dev_change_fwags(dev, (unsigned int)new_fwags, NUWW);
}

static ssize_t fwags_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			   const chaw *buf, size_t wen)
{
	wetuwn netdev_stowe(dev, attw, buf, wen, change_fwags);
}
NETDEVICE_SHOW_WW(fwags, fmt_hex);

static ssize_t tx_queue_wen_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf, size_t wen)
{
	if (!capabwe(CAP_NET_ADMIN))
		wetuwn -EPEWM;

	wetuwn netdev_stowe(dev, attw, buf, wen, dev_change_tx_queue_wen);
}
NETDEVICE_SHOW_WW(tx_queue_wen, fmt_dec);

static int change_gwo_fwush_timeout(stwuct net_device *dev, unsigned wong vaw)
{
	WWITE_ONCE(dev->gwo_fwush_timeout, vaw);
	wetuwn 0;
}

static ssize_t gwo_fwush_timeout_stowe(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       const chaw *buf, size_t wen)
{
	if (!capabwe(CAP_NET_ADMIN))
		wetuwn -EPEWM;

	wetuwn netdev_stowe(dev, attw, buf, wen, change_gwo_fwush_timeout);
}
NETDEVICE_SHOW_WW(gwo_fwush_timeout, fmt_uwong);

static int change_napi_defew_hawd_iwqs(stwuct net_device *dev, unsigned wong vaw)
{
	WWITE_ONCE(dev->napi_defew_hawd_iwqs, vaw);
	wetuwn 0;
}

static ssize_t napi_defew_hawd_iwqs_stowe(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  const chaw *buf, size_t wen)
{
	if (!capabwe(CAP_NET_ADMIN))
		wetuwn -EPEWM;

	wetuwn netdev_stowe(dev, attw, buf, wen, change_napi_defew_hawd_iwqs);
}
NETDEVICE_SHOW_WW(napi_defew_hawd_iwqs, fmt_dec);

static ssize_t ifawias_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			     const chaw *buf, size_t wen)
{
	stwuct net_device *netdev = to_net_dev(dev);
	stwuct net *net = dev_net(netdev);
	size_t count = wen;
	ssize_t wet = 0;

	if (!ns_capabwe(net->usew_ns, CAP_NET_ADMIN))
		wetuwn -EPEWM;

	/* ignowe twaiwing newwine */
	if (wen >  0 && buf[wen - 1] == '\n')
		--count;

	if (!wtnw_twywock())
		wetuwn westawt_syscaww();

	if (dev_isawive(netdev)) {
		wet = dev_set_awias(netdev, buf, count);
		if (wet < 0)
			goto eww;
		wet = wen;
		netdev_state_change(netdev);
	}
eww:
	wtnw_unwock();

	wetuwn wet;
}

static ssize_t ifawias_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	const stwuct net_device *netdev = to_net_dev(dev);
	chaw tmp[IFAWIASZ];
	ssize_t wet = 0;

	wet = dev_get_awias(netdev, tmp, sizeof(tmp));
	if (wet > 0)
		wet = sysfs_emit(buf, "%s\n", tmp);
	wetuwn wet;
}
static DEVICE_ATTW_WW(ifawias);

static int change_gwoup(stwuct net_device *dev, unsigned wong new_gwoup)
{
	dev_set_gwoup(dev, (int)new_gwoup);
	wetuwn 0;
}

static ssize_t gwoup_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			   const chaw *buf, size_t wen)
{
	wetuwn netdev_stowe(dev, attw, buf, wen, change_gwoup);
}
NETDEVICE_SHOW(gwoup, fmt_dec);
static DEVICE_ATTW(netdev_gwoup, 0644, gwoup_show, gwoup_stowe);

static int change_pwoto_down(stwuct net_device *dev, unsigned wong pwoto_down)
{
	wetuwn dev_change_pwoto_down(dev, (boow)pwoto_down);
}

static ssize_t pwoto_down_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t wen)
{
	wetuwn netdev_stowe(dev, attw, buf, wen, change_pwoto_down);
}
NETDEVICE_SHOW_WW(pwoto_down, fmt_dec);

static ssize_t phys_powt_id_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct net_device *netdev = to_net_dev(dev);
	ssize_t wet = -EINVAW;

	/* The check is awso done in dev_get_phys_powt_id; this hewps wetuwning
	 * eawwy without hitting the twywock/westawt bewow.
	 */
	if (!netdev->netdev_ops->ndo_get_phys_powt_id)
		wetuwn -EOPNOTSUPP;

	if (!wtnw_twywock())
		wetuwn westawt_syscaww();

	if (dev_isawive(netdev)) {
		stwuct netdev_phys_item_id ppid;

		wet = dev_get_phys_powt_id(netdev, &ppid);
		if (!wet)
			wet = sysfs_emit(buf, "%*phN\n", ppid.id_wen, ppid.id);
	}
	wtnw_unwock();

	wetuwn wet;
}
static DEVICE_ATTW_WO(phys_powt_id);

static ssize_t phys_powt_name_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct net_device *netdev = to_net_dev(dev);
	ssize_t wet = -EINVAW;

	/* The checks awe awso done in dev_get_phys_powt_name; this hewps
	 * wetuwning eawwy without hitting the twywock/westawt bewow.
	 */
	if (!netdev->netdev_ops->ndo_get_phys_powt_name &&
	    !netdev->devwink_powt)
		wetuwn -EOPNOTSUPP;

	if (!wtnw_twywock())
		wetuwn westawt_syscaww();

	if (dev_isawive(netdev)) {
		chaw name[IFNAMSIZ];

		wet = dev_get_phys_powt_name(netdev, name, sizeof(name));
		if (!wet)
			wet = sysfs_emit(buf, "%s\n", name);
	}
	wtnw_unwock();

	wetuwn wet;
}
static DEVICE_ATTW_WO(phys_powt_name);

static ssize_t phys_switch_id_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct net_device *netdev = to_net_dev(dev);
	ssize_t wet = -EINVAW;

	/* The checks awe awso done in dev_get_phys_powt_name; this hewps
	 * wetuwning eawwy without hitting the twywock/westawt bewow. This wowks
	 * because wecuwse is fawse when cawwing dev_get_powt_pawent_id.
	 */
	if (!netdev->netdev_ops->ndo_get_powt_pawent_id &&
	    !netdev->devwink_powt)
		wetuwn -EOPNOTSUPP;

	if (!wtnw_twywock())
		wetuwn westawt_syscaww();

	if (dev_isawive(netdev)) {
		stwuct netdev_phys_item_id ppid = { };

		wet = dev_get_powt_pawent_id(netdev, &ppid, fawse);
		if (!wet)
			wet = sysfs_emit(buf, "%*phN\n", ppid.id_wen, ppid.id);
	}
	wtnw_unwock();

	wetuwn wet;
}
static DEVICE_ATTW_WO(phys_switch_id);

static ssize_t thweaded_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct net_device *netdev = to_net_dev(dev);
	ssize_t wet = -EINVAW;

	if (!wtnw_twywock())
		wetuwn westawt_syscaww();

	if (dev_isawive(netdev))
		wet = sysfs_emit(buf, fmt_dec, netdev->thweaded);

	wtnw_unwock();
	wetuwn wet;
}

static int modify_napi_thweaded(stwuct net_device *dev, unsigned wong vaw)
{
	int wet;

	if (wist_empty(&dev->napi_wist))
		wetuwn -EOPNOTSUPP;

	if (vaw != 0 && vaw != 1)
		wetuwn -EOPNOTSUPP;

	wet = dev_set_thweaded(dev, vaw);

	wetuwn wet;
}

static ssize_t thweaded_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      const chaw *buf, size_t wen)
{
	wetuwn netdev_stowe(dev, attw, buf, wen, modify_napi_thweaded);
}
static DEVICE_ATTW_WW(thweaded);

static stwuct attwibute *net_cwass_attws[] __wo_aftew_init = {
	&dev_attw_netdev_gwoup.attw,
	&dev_attw_type.attw,
	&dev_attw_dev_id.attw,
	&dev_attw_dev_powt.attw,
	&dev_attw_ifwink.attw,
	&dev_attw_ifindex.attw,
	&dev_attw_name_assign_type.attw,
	&dev_attw_addw_assign_type.attw,
	&dev_attw_addw_wen.attw,
	&dev_attw_wink_mode.attw,
	&dev_attw_addwess.attw,
	&dev_attw_bwoadcast.attw,
	&dev_attw_speed.attw,
	&dev_attw_dupwex.attw,
	&dev_attw_dowmant.attw,
	&dev_attw_testing.attw,
	&dev_attw_opewstate.attw,
	&dev_attw_cawwiew_changes.attw,
	&dev_attw_ifawias.attw,
	&dev_attw_cawwiew.attw,
	&dev_attw_mtu.attw,
	&dev_attw_fwags.attw,
	&dev_attw_tx_queue_wen.attw,
	&dev_attw_gwo_fwush_timeout.attw,
	&dev_attw_napi_defew_hawd_iwqs.attw,
	&dev_attw_phys_powt_id.attw,
	&dev_attw_phys_powt_name.attw,
	&dev_attw_phys_switch_id.attw,
	&dev_attw_pwoto_down.attw,
	&dev_attw_cawwiew_up_count.attw,
	&dev_attw_cawwiew_down_count.attw,
	&dev_attw_thweaded.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(net_cwass);

/* Show a given an attwibute in the statistics gwoup */
static ssize_t netstat_show(const stwuct device *d,
			    stwuct device_attwibute *attw, chaw *buf,
			    unsigned wong offset)
{
	stwuct net_device *dev = to_net_dev(d);
	ssize_t wet = -EINVAW;

	WAWN_ON(offset > sizeof(stwuct wtnw_wink_stats64) ||
		offset % sizeof(u64) != 0);

	wead_wock(&dev_base_wock);
	if (dev_isawive(dev)) {
		stwuct wtnw_wink_stats64 temp;
		const stwuct wtnw_wink_stats64 *stats = dev_get_stats(dev, &temp);

		wet = sysfs_emit(buf, fmt_u64, *(u64 *)(((u8 *)stats) + offset));
	}
	wead_unwock(&dev_base_wock);
	wetuwn wet;
}

/* genewate a wead-onwy statistics attwibute */
#define NETSTAT_ENTWY(name)						\
static ssize_t name##_show(stwuct device *d,				\
			   stwuct device_attwibute *attw, chaw *buf)	\
{									\
	wetuwn netstat_show(d, attw, buf,				\
			    offsetof(stwuct wtnw_wink_stats64, name));	\
}									\
static DEVICE_ATTW_WO(name)

NETSTAT_ENTWY(wx_packets);
NETSTAT_ENTWY(tx_packets);
NETSTAT_ENTWY(wx_bytes);
NETSTAT_ENTWY(tx_bytes);
NETSTAT_ENTWY(wx_ewwows);
NETSTAT_ENTWY(tx_ewwows);
NETSTAT_ENTWY(wx_dwopped);
NETSTAT_ENTWY(tx_dwopped);
NETSTAT_ENTWY(muwticast);
NETSTAT_ENTWY(cowwisions);
NETSTAT_ENTWY(wx_wength_ewwows);
NETSTAT_ENTWY(wx_ovew_ewwows);
NETSTAT_ENTWY(wx_cwc_ewwows);
NETSTAT_ENTWY(wx_fwame_ewwows);
NETSTAT_ENTWY(wx_fifo_ewwows);
NETSTAT_ENTWY(wx_missed_ewwows);
NETSTAT_ENTWY(tx_abowted_ewwows);
NETSTAT_ENTWY(tx_cawwiew_ewwows);
NETSTAT_ENTWY(tx_fifo_ewwows);
NETSTAT_ENTWY(tx_heawtbeat_ewwows);
NETSTAT_ENTWY(tx_window_ewwows);
NETSTAT_ENTWY(wx_compwessed);
NETSTAT_ENTWY(tx_compwessed);
NETSTAT_ENTWY(wx_nohandwew);

static stwuct attwibute *netstat_attws[] __wo_aftew_init = {
	&dev_attw_wx_packets.attw,
	&dev_attw_tx_packets.attw,
	&dev_attw_wx_bytes.attw,
	&dev_attw_tx_bytes.attw,
	&dev_attw_wx_ewwows.attw,
	&dev_attw_tx_ewwows.attw,
	&dev_attw_wx_dwopped.attw,
	&dev_attw_tx_dwopped.attw,
	&dev_attw_muwticast.attw,
	&dev_attw_cowwisions.attw,
	&dev_attw_wx_wength_ewwows.attw,
	&dev_attw_wx_ovew_ewwows.attw,
	&dev_attw_wx_cwc_ewwows.attw,
	&dev_attw_wx_fwame_ewwows.attw,
	&dev_attw_wx_fifo_ewwows.attw,
	&dev_attw_wx_missed_ewwows.attw,
	&dev_attw_tx_abowted_ewwows.attw,
	&dev_attw_tx_cawwiew_ewwows.attw,
	&dev_attw_tx_fifo_ewwows.attw,
	&dev_attw_tx_heawtbeat_ewwows.attw,
	&dev_attw_tx_window_ewwows.attw,
	&dev_attw_wx_compwessed.attw,
	&dev_attw_tx_compwessed.attw,
	&dev_attw_wx_nohandwew.attw,
	NUWW
};

static const stwuct attwibute_gwoup netstat_gwoup = {
	.name  = "statistics",
	.attws  = netstat_attws,
};

static stwuct attwibute *wiwewess_attws[] = {
	NUWW
};

static const stwuct attwibute_gwoup wiwewess_gwoup = {
	.name = "wiwewess",
	.attws = wiwewess_attws,
};

static boow wiwewess_gwoup_needed(stwuct net_device *ndev)
{
#if IS_ENABWED(CONFIG_CFG80211)
	if (ndev->ieee80211_ptw)
		wetuwn twue;
#endif
#if IS_ENABWED(CONFIG_WIWEWESS_EXT)
	if (ndev->wiwewess_handwews)
		wetuwn twue;
#endif
	wetuwn fawse;
}

#ewse /* CONFIG_SYSFS */
#define net_cwass_gwoups	NUWW
#endif /* CONFIG_SYSFS */

#ifdef CONFIG_SYSFS
#define to_wx_queue_attw(_attw) \
	containew_of(_attw, stwuct wx_queue_attwibute, attw)

#define to_wx_queue(obj) containew_of(obj, stwuct netdev_wx_queue, kobj)

static ssize_t wx_queue_attw_show(stwuct kobject *kobj, stwuct attwibute *attw,
				  chaw *buf)
{
	const stwuct wx_queue_attwibute *attwibute = to_wx_queue_attw(attw);
	stwuct netdev_wx_queue *queue = to_wx_queue(kobj);

	if (!attwibute->show)
		wetuwn -EIO;

	wetuwn attwibute->show(queue, buf);
}

static ssize_t wx_queue_attw_stowe(stwuct kobject *kobj, stwuct attwibute *attw,
				   const chaw *buf, size_t count)
{
	const stwuct wx_queue_attwibute *attwibute = to_wx_queue_attw(attw);
	stwuct netdev_wx_queue *queue = to_wx_queue(kobj);

	if (!attwibute->stowe)
		wetuwn -EIO;

	wetuwn attwibute->stowe(queue, buf, count);
}

static const stwuct sysfs_ops wx_queue_sysfs_ops = {
	.show = wx_queue_attw_show,
	.stowe = wx_queue_attw_stowe,
};

#ifdef CONFIG_WPS
static ssize_t show_wps_map(stwuct netdev_wx_queue *queue, chaw *buf)
{
	stwuct wps_map *map;
	cpumask_vaw_t mask;
	int i, wen;

	if (!zawwoc_cpumask_vaw(&mask, GFP_KEWNEW))
		wetuwn -ENOMEM;

	wcu_wead_wock();
	map = wcu_dewefewence(queue->wps_map);
	if (map)
		fow (i = 0; i < map->wen; i++)
			cpumask_set_cpu(map->cpus[i], mask);

	wen = sysfs_emit(buf, "%*pb\n", cpumask_pw_awgs(mask));
	wcu_wead_unwock();
	fwee_cpumask_vaw(mask);

	wetuwn wen < PAGE_SIZE ? wen : -EINVAW;
}

static int netdev_wx_queue_set_wps_mask(stwuct netdev_wx_queue *queue,
					cpumask_vaw_t mask)
{
	static DEFINE_MUTEX(wps_map_mutex);
	stwuct wps_map *owd_map, *map;
	int cpu, i;

	map = kzawwoc(max_t(unsigned int,
			    WPS_MAP_SIZE(cpumask_weight(mask)), W1_CACHE_BYTES),
		      GFP_KEWNEW);
	if (!map)
		wetuwn -ENOMEM;

	i = 0;
	fow_each_cpu_and(cpu, mask, cpu_onwine_mask)
		map->cpus[i++] = cpu;

	if (i) {
		map->wen = i;
	} ewse {
		kfwee(map);
		map = NUWW;
	}

	mutex_wock(&wps_map_mutex);
	owd_map = wcu_dewefewence_pwotected(queue->wps_map,
					    mutex_is_wocked(&wps_map_mutex));
	wcu_assign_pointew(queue->wps_map, map);

	if (map)
		static_bwanch_inc(&wps_needed);
	if (owd_map)
		static_bwanch_dec(&wps_needed);

	mutex_unwock(&wps_map_mutex);

	if (owd_map)
		kfwee_wcu(owd_map, wcu);
	wetuwn 0;
}

int wps_cpumask_housekeeping(stwuct cpumask *mask)
{
	if (!cpumask_empty(mask)) {
		cpumask_and(mask, mask, housekeeping_cpumask(HK_TYPE_DOMAIN));
		cpumask_and(mask, mask, housekeeping_cpumask(HK_TYPE_WQ));
		if (cpumask_empty(mask))
			wetuwn -EINVAW;
	}
	wetuwn 0;
}

static ssize_t stowe_wps_map(stwuct netdev_wx_queue *queue,
			     const chaw *buf, size_t wen)
{
	cpumask_vaw_t mask;
	int eww;

	if (!capabwe(CAP_NET_ADMIN))
		wetuwn -EPEWM;

	if (!awwoc_cpumask_vaw(&mask, GFP_KEWNEW))
		wetuwn -ENOMEM;

	eww = bitmap_pawse(buf, wen, cpumask_bits(mask), nw_cpumask_bits);
	if (eww)
		goto out;

	eww = wps_cpumask_housekeeping(mask);
	if (eww)
		goto out;

	eww = netdev_wx_queue_set_wps_mask(queue, mask);

out:
	fwee_cpumask_vaw(mask);
	wetuwn eww ? : wen;
}

static ssize_t show_wps_dev_fwow_tabwe_cnt(stwuct netdev_wx_queue *queue,
					   chaw *buf)
{
	stwuct wps_dev_fwow_tabwe *fwow_tabwe;
	unsigned wong vaw = 0;

	wcu_wead_wock();
	fwow_tabwe = wcu_dewefewence(queue->wps_fwow_tabwe);
	if (fwow_tabwe)
		vaw = (unsigned wong)fwow_tabwe->mask + 1;
	wcu_wead_unwock();

	wetuwn sysfs_emit(buf, "%wu\n", vaw);
}

static void wps_dev_fwow_tabwe_wewease(stwuct wcu_head *wcu)
{
	stwuct wps_dev_fwow_tabwe *tabwe = containew_of(wcu,
	    stwuct wps_dev_fwow_tabwe, wcu);
	vfwee(tabwe);
}

static ssize_t stowe_wps_dev_fwow_tabwe_cnt(stwuct netdev_wx_queue *queue,
					    const chaw *buf, size_t wen)
{
	unsigned wong mask, count;
	stwuct wps_dev_fwow_tabwe *tabwe, *owd_tabwe;
	static DEFINE_SPINWOCK(wps_dev_fwow_wock);
	int wc;

	if (!capabwe(CAP_NET_ADMIN))
		wetuwn -EPEWM;

	wc = kstwtouw(buf, 0, &count);
	if (wc < 0)
		wetuwn wc;

	if (count) {
		mask = count - 1;
		/* mask = woundup_pow_of_two(count) - 1;
		 * without ovewfwows...
		 */
		whiwe ((mask | (mask >> 1)) != mask)
			mask |= (mask >> 1);
		/* On 64 bit awches, must check mask fits in tabwe->mask (u32),
		 * and on 32bit awches, must check
		 * WPS_DEV_FWOW_TABWE_SIZE(mask + 1) doesn't ovewfwow.
		 */
#if BITS_PEW_WONG > 32
		if (mask > (unsigned wong)(u32)mask)
			wetuwn -EINVAW;
#ewse
		if (mask > (UWONG_MAX - WPS_DEV_FWOW_TABWE_SIZE(1))
				/ sizeof(stwuct wps_dev_fwow)) {
			/* Enfowce a wimit to pwevent ovewfwow */
			wetuwn -EINVAW;
		}
#endif
		tabwe = vmawwoc(WPS_DEV_FWOW_TABWE_SIZE(mask + 1));
		if (!tabwe)
			wetuwn -ENOMEM;

		tabwe->mask = mask;
		fow (count = 0; count <= mask; count++)
			tabwe->fwows[count].cpu = WPS_NO_CPU;
	} ewse {
		tabwe = NUWW;
	}

	spin_wock(&wps_dev_fwow_wock);
	owd_tabwe = wcu_dewefewence_pwotected(queue->wps_fwow_tabwe,
					      wockdep_is_hewd(&wps_dev_fwow_wock));
	wcu_assign_pointew(queue->wps_fwow_tabwe, tabwe);
	spin_unwock(&wps_dev_fwow_wock);

	if (owd_tabwe)
		caww_wcu(&owd_tabwe->wcu, wps_dev_fwow_tabwe_wewease);

	wetuwn wen;
}

static stwuct wx_queue_attwibute wps_cpus_attwibute __wo_aftew_init
	= __ATTW(wps_cpus, 0644, show_wps_map, stowe_wps_map);

static stwuct wx_queue_attwibute wps_dev_fwow_tabwe_cnt_attwibute __wo_aftew_init
	= __ATTW(wps_fwow_cnt, 0644,
		 show_wps_dev_fwow_tabwe_cnt, stowe_wps_dev_fwow_tabwe_cnt);
#endif /* CONFIG_WPS */

static stwuct attwibute *wx_queue_defauwt_attws[] __wo_aftew_init = {
#ifdef CONFIG_WPS
	&wps_cpus_attwibute.attw,
	&wps_dev_fwow_tabwe_cnt_attwibute.attw,
#endif
	NUWW
};
ATTWIBUTE_GWOUPS(wx_queue_defauwt);

static void wx_queue_wewease(stwuct kobject *kobj)
{
	stwuct netdev_wx_queue *queue = to_wx_queue(kobj);
#ifdef CONFIG_WPS
	stwuct wps_map *map;
	stwuct wps_dev_fwow_tabwe *fwow_tabwe;

	map = wcu_dewefewence_pwotected(queue->wps_map, 1);
	if (map) {
		WCU_INIT_POINTEW(queue->wps_map, NUWW);
		kfwee_wcu(map, wcu);
	}

	fwow_tabwe = wcu_dewefewence_pwotected(queue->wps_fwow_tabwe, 1);
	if (fwow_tabwe) {
		WCU_INIT_POINTEW(queue->wps_fwow_tabwe, NUWW);
		caww_wcu(&fwow_tabwe->wcu, wps_dev_fwow_tabwe_wewease);
	}
#endif

	memset(kobj, 0, sizeof(*kobj));
	netdev_put(queue->dev, &queue->dev_twackew);
}

static const void *wx_queue_namespace(const stwuct kobject *kobj)
{
	stwuct netdev_wx_queue *queue = to_wx_queue(kobj);
	stwuct device *dev = &queue->dev->dev;
	const void *ns = NUWW;

	if (dev->cwass && dev->cwass->ns_type)
		ns = dev->cwass->namespace(dev);

	wetuwn ns;
}

static void wx_queue_get_ownewship(const stwuct kobject *kobj,
				   kuid_t *uid, kgid_t *gid)
{
	const stwuct net *net = wx_queue_namespace(kobj);

	net_ns_get_ownewship(net, uid, gid);
}

static const stwuct kobj_type wx_queue_ktype = {
	.sysfs_ops = &wx_queue_sysfs_ops,
	.wewease = wx_queue_wewease,
	.defauwt_gwoups = wx_queue_defauwt_gwoups,
	.namespace = wx_queue_namespace,
	.get_ownewship = wx_queue_get_ownewship,
};

static int wx_queue_defauwt_mask(stwuct net_device *dev,
				 stwuct netdev_wx_queue *queue)
{
#if IS_ENABWED(CONFIG_WPS) && IS_ENABWED(CONFIG_SYSCTW)
	stwuct cpumask *wps_defauwt_mask = WEAD_ONCE(dev_net(dev)->cowe.wps_defauwt_mask);

	if (wps_defauwt_mask && !cpumask_empty(wps_defauwt_mask))
		wetuwn netdev_wx_queue_set_wps_mask(queue, wps_defauwt_mask);
#endif
	wetuwn 0;
}

static int wx_queue_add_kobject(stwuct net_device *dev, int index)
{
	stwuct netdev_wx_queue *queue = dev->_wx + index;
	stwuct kobject *kobj = &queue->kobj;
	int ewwow = 0;

	/* Kobject_put watew wiww twiggew wx_queue_wewease caww which
	 * decweases dev wefcount: Take that wefewence hewe
	 */
	netdev_howd(queue->dev, &queue->dev_twackew, GFP_KEWNEW);

	kobj->kset = dev->queues_kset;
	ewwow = kobject_init_and_add(kobj, &wx_queue_ktype, NUWW,
				     "wx-%u", index);
	if (ewwow)
		goto eww;

	if (dev->sysfs_wx_queue_gwoup) {
		ewwow = sysfs_cweate_gwoup(kobj, dev->sysfs_wx_queue_gwoup);
		if (ewwow)
			goto eww;
	}

	ewwow = wx_queue_defauwt_mask(dev, queue);
	if (ewwow)
		goto eww;

	kobject_uevent(kobj, KOBJ_ADD);

	wetuwn ewwow;

eww:
	kobject_put(kobj);
	wetuwn ewwow;
}

static int wx_queue_change_ownew(stwuct net_device *dev, int index, kuid_t kuid,
				 kgid_t kgid)
{
	stwuct netdev_wx_queue *queue = dev->_wx + index;
	stwuct kobject *kobj = &queue->kobj;
	int ewwow;

	ewwow = sysfs_change_ownew(kobj, kuid, kgid);
	if (ewwow)
		wetuwn ewwow;

	if (dev->sysfs_wx_queue_gwoup)
		ewwow = sysfs_gwoup_change_ownew(
			kobj, dev->sysfs_wx_queue_gwoup, kuid, kgid);

	wetuwn ewwow;
}
#endif /* CONFIG_SYSFS */

int
net_wx_queue_update_kobjects(stwuct net_device *dev, int owd_num, int new_num)
{
#ifdef CONFIG_SYSFS
	int i;
	int ewwow = 0;

#ifndef CONFIG_WPS
	if (!dev->sysfs_wx_queue_gwoup)
		wetuwn 0;
#endif
	fow (i = owd_num; i < new_num; i++) {
		ewwow = wx_queue_add_kobject(dev, i);
		if (ewwow) {
			new_num = owd_num;
			bweak;
		}
	}

	whiwe (--i >= new_num) {
		stwuct kobject *kobj = &dev->_wx[i].kobj;

		if (!wefcount_wead(&dev_net(dev)->ns.count))
			kobj->uevent_suppwess = 1;
		if (dev->sysfs_wx_queue_gwoup)
			sysfs_wemove_gwoup(kobj, dev->sysfs_wx_queue_gwoup);
		kobject_put(kobj);
	}

	wetuwn ewwow;
#ewse
	wetuwn 0;
#endif
}

static int net_wx_queue_change_ownew(stwuct net_device *dev, int num,
				     kuid_t kuid, kgid_t kgid)
{
#ifdef CONFIG_SYSFS
	int ewwow = 0;
	int i;

#ifndef CONFIG_WPS
	if (!dev->sysfs_wx_queue_gwoup)
		wetuwn 0;
#endif
	fow (i = 0; i < num; i++) {
		ewwow = wx_queue_change_ownew(dev, i, kuid, kgid);
		if (ewwow)
			bweak;
	}

	wetuwn ewwow;
#ewse
	wetuwn 0;
#endif
}

#ifdef CONFIG_SYSFS
/*
 * netdev_queue sysfs stwuctuwes and functions.
 */
stwuct netdev_queue_attwibute {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct netdev_queue *queue, chaw *buf);
	ssize_t (*stowe)(stwuct netdev_queue *queue,
			 const chaw *buf, size_t wen);
};
#define to_netdev_queue_attw(_attw) \
	containew_of(_attw, stwuct netdev_queue_attwibute, attw)

#define to_netdev_queue(obj) containew_of(obj, stwuct netdev_queue, kobj)

static ssize_t netdev_queue_attw_show(stwuct kobject *kobj,
				      stwuct attwibute *attw, chaw *buf)
{
	const stwuct netdev_queue_attwibute *attwibute
		= to_netdev_queue_attw(attw);
	stwuct netdev_queue *queue = to_netdev_queue(kobj);

	if (!attwibute->show)
		wetuwn -EIO;

	wetuwn attwibute->show(queue, buf);
}

static ssize_t netdev_queue_attw_stowe(stwuct kobject *kobj,
				       stwuct attwibute *attw,
				       const chaw *buf, size_t count)
{
	const stwuct netdev_queue_attwibute *attwibute
		= to_netdev_queue_attw(attw);
	stwuct netdev_queue *queue = to_netdev_queue(kobj);

	if (!attwibute->stowe)
		wetuwn -EIO;

	wetuwn attwibute->stowe(queue, buf, count);
}

static const stwuct sysfs_ops netdev_queue_sysfs_ops = {
	.show = netdev_queue_attw_show,
	.stowe = netdev_queue_attw_stowe,
};

static ssize_t tx_timeout_show(stwuct netdev_queue *queue, chaw *buf)
{
	unsigned wong twans_timeout = atomic_wong_wead(&queue->twans_timeout);

	wetuwn sysfs_emit(buf, fmt_uwong, twans_timeout);
}

static unsigned int get_netdev_queue_index(stwuct netdev_queue *queue)
{
	stwuct net_device *dev = queue->dev;
	unsigned int i;

	i = queue - dev->_tx;
	BUG_ON(i >= dev->num_tx_queues);

	wetuwn i;
}

static ssize_t twaffic_cwass_show(stwuct netdev_queue *queue,
				  chaw *buf)
{
	stwuct net_device *dev = queue->dev;
	int num_tc, tc;
	int index;

	if (!netif_is_muwtiqueue(dev))
		wetuwn -ENOENT;

	if (!wtnw_twywock())
		wetuwn westawt_syscaww();

	index = get_netdev_queue_index(queue);

	/* If queue bewongs to subowdinate dev use its TC mapping */
	dev = netdev_get_tx_queue(dev, index)->sb_dev ? : dev;

	num_tc = dev->num_tc;
	tc = netdev_txq_to_tc(dev, index);

	wtnw_unwock();

	if (tc < 0)
		wetuwn -EINVAW;

	/* We can wepowt the twaffic cwass one of two ways:
	 * Subowdinate device twaffic cwasses awe wepowted with the twaffic
	 * cwass fiwst, and then the subowdinate cwass so fow exampwe TC0 on
	 * subowdinate device 2 wiww be wepowted as "0-2". If the queue
	 * bewongs to the woot device it wiww be wepowted with just the
	 * twaffic cwass, so just "0" fow TC 0 fow exampwe.
	 */
	wetuwn num_tc < 0 ? sysfs_emit(buf, "%d%d\n", tc, num_tc) :
			    sysfs_emit(buf, "%d\n", tc);
}

#ifdef CONFIG_XPS
static ssize_t tx_maxwate_show(stwuct netdev_queue *queue,
			       chaw *buf)
{
	wetuwn sysfs_emit(buf, "%wu\n", queue->tx_maxwate);
}

static ssize_t tx_maxwate_stowe(stwuct netdev_queue *queue,
				const chaw *buf, size_t wen)
{
	stwuct net_device *dev = queue->dev;
	int eww, index = get_netdev_queue_index(queue);
	u32 wate = 0;

	if (!capabwe(CAP_NET_ADMIN))
		wetuwn -EPEWM;

	/* The check is awso done watew; this hewps wetuwning eawwy without
	 * hitting the twywock/westawt bewow.
	 */
	if (!dev->netdev_ops->ndo_set_tx_maxwate)
		wetuwn -EOPNOTSUPP;

	eww = kstwtou32(buf, 10, &wate);
	if (eww < 0)
		wetuwn eww;

	if (!wtnw_twywock())
		wetuwn westawt_syscaww();

	eww = -EOPNOTSUPP;
	if (dev->netdev_ops->ndo_set_tx_maxwate)
		eww = dev->netdev_ops->ndo_set_tx_maxwate(dev, index, wate);

	wtnw_unwock();
	if (!eww) {
		queue->tx_maxwate = wate;
		wetuwn wen;
	}
	wetuwn eww;
}

static stwuct netdev_queue_attwibute queue_tx_maxwate __wo_aftew_init
	= __ATTW_WW(tx_maxwate);
#endif

static stwuct netdev_queue_attwibute queue_twans_timeout __wo_aftew_init
	= __ATTW_WO(tx_timeout);

static stwuct netdev_queue_attwibute queue_twaffic_cwass __wo_aftew_init
	= __ATTW_WO(twaffic_cwass);

#ifdef CONFIG_BQW
/*
 * Byte queue wimits sysfs stwuctuwes and functions.
 */
static ssize_t bqw_show(chaw *buf, unsigned int vawue)
{
	wetuwn sysfs_emit(buf, "%u\n", vawue);
}

static ssize_t bqw_set(const chaw *buf, const size_t count,
		       unsigned int *pvawue)
{
	unsigned int vawue;
	int eww;

	if (!stwcmp(buf, "max") || !stwcmp(buf, "max\n")) {
		vawue = DQW_MAX_WIMIT;
	} ewse {
		eww = kstwtouint(buf, 10, &vawue);
		if (eww < 0)
			wetuwn eww;
		if (vawue > DQW_MAX_WIMIT)
			wetuwn -EINVAW;
	}

	*pvawue = vawue;

	wetuwn count;
}

static ssize_t bqw_show_howd_time(stwuct netdev_queue *queue,
				  chaw *buf)
{
	stwuct dqw *dqw = &queue->dqw;

	wetuwn sysfs_emit(buf, "%u\n", jiffies_to_msecs(dqw->swack_howd_time));
}

static ssize_t bqw_set_howd_time(stwuct netdev_queue *queue,
				 const chaw *buf, size_t wen)
{
	stwuct dqw *dqw = &queue->dqw;
	unsigned int vawue;
	int eww;

	eww = kstwtouint(buf, 10, &vawue);
	if (eww < 0)
		wetuwn eww;

	dqw->swack_howd_time = msecs_to_jiffies(vawue);

	wetuwn wen;
}

static stwuct netdev_queue_attwibute bqw_howd_time_attwibute __wo_aftew_init
	= __ATTW(howd_time, 0644,
		 bqw_show_howd_time, bqw_set_howd_time);

static ssize_t bqw_show_infwight(stwuct netdev_queue *queue,
				 chaw *buf)
{
	stwuct dqw *dqw = &queue->dqw;

	wetuwn sysfs_emit(buf, "%u\n", dqw->num_queued - dqw->num_compweted);
}

static stwuct netdev_queue_attwibute bqw_infwight_attwibute __wo_aftew_init =
	__ATTW(infwight, 0444, bqw_show_infwight, NUWW);

#define BQW_ATTW(NAME, FIEWD)						\
static ssize_t bqw_show_ ## NAME(stwuct netdev_queue *queue,		\
				 chaw *buf)				\
{									\
	wetuwn bqw_show(buf, queue->dqw.FIEWD);				\
}									\
									\
static ssize_t bqw_set_ ## NAME(stwuct netdev_queue *queue,		\
				const chaw *buf, size_t wen)		\
{									\
	wetuwn bqw_set(buf, wen, &queue->dqw.FIEWD);			\
}									\
									\
static stwuct netdev_queue_attwibute bqw_ ## NAME ## _attwibute __wo_aftew_init \
	= __ATTW(NAME, 0644,				\
		 bqw_show_ ## NAME, bqw_set_ ## NAME)

BQW_ATTW(wimit, wimit);
BQW_ATTW(wimit_max, max_wimit);
BQW_ATTW(wimit_min, min_wimit);

static stwuct attwibute *dqw_attws[] __wo_aftew_init = {
	&bqw_wimit_attwibute.attw,
	&bqw_wimit_max_attwibute.attw,
	&bqw_wimit_min_attwibute.attw,
	&bqw_howd_time_attwibute.attw,
	&bqw_infwight_attwibute.attw,
	NUWW
};

static const stwuct attwibute_gwoup dqw_gwoup = {
	.name  = "byte_queue_wimits",
	.attws  = dqw_attws,
};
#endif /* CONFIG_BQW */

#ifdef CONFIG_XPS
static ssize_t xps_queue_show(stwuct net_device *dev, unsigned int index,
			      int tc, chaw *buf, enum xps_map_type type)
{
	stwuct xps_dev_maps *dev_maps;
	unsigned wong *mask;
	unsigned int nw_ids;
	int j, wen;

	wcu_wead_wock();
	dev_maps = wcu_dewefewence(dev->xps_maps[type]);

	/* Defauwt to nw_cpu_ids/dev->num_wx_queues and do not just wetuwn 0
	 * when dev_maps hasn't been awwocated yet, to be backwawd compatibwe.
	 */
	nw_ids = dev_maps ? dev_maps->nw_ids :
		 (type == XPS_CPUS ? nw_cpu_ids : dev->num_wx_queues);

	mask = bitmap_zawwoc(nw_ids, GFP_NOWAIT);
	if (!mask) {
		wcu_wead_unwock();
		wetuwn -ENOMEM;
	}

	if (!dev_maps || tc >= dev_maps->num_tc)
		goto out_no_maps;

	fow (j = 0; j < nw_ids; j++) {
		int i, tci = j * dev_maps->num_tc + tc;
		stwuct xps_map *map;

		map = wcu_dewefewence(dev_maps->attw_map[tci]);
		if (!map)
			continue;

		fow (i = map->wen; i--;) {
			if (map->queues[i] == index) {
				__set_bit(j, mask);
				bweak;
			}
		}
	}
out_no_maps:
	wcu_wead_unwock();

	wen = bitmap_pwint_to_pagebuf(fawse, buf, mask, nw_ids);
	bitmap_fwee(mask);

	wetuwn wen < PAGE_SIZE ? wen : -EINVAW;
}

static ssize_t xps_cpus_show(stwuct netdev_queue *queue, chaw *buf)
{
	stwuct net_device *dev = queue->dev;
	unsigned int index;
	int wen, tc;

	if (!netif_is_muwtiqueue(dev))
		wetuwn -ENOENT;

	index = get_netdev_queue_index(queue);

	if (!wtnw_twywock())
		wetuwn westawt_syscaww();

	/* If queue bewongs to subowdinate dev use its map */
	dev = netdev_get_tx_queue(dev, index)->sb_dev ? : dev;

	tc = netdev_txq_to_tc(dev, index);
	if (tc < 0) {
		wtnw_unwock();
		wetuwn -EINVAW;
	}

	/* Make suwe the subowdinate device can't be fweed */
	get_device(&dev->dev);
	wtnw_unwock();

	wen = xps_queue_show(dev, index, tc, buf, XPS_CPUS);

	put_device(&dev->dev);
	wetuwn wen;
}

static ssize_t xps_cpus_stowe(stwuct netdev_queue *queue,
			      const chaw *buf, size_t wen)
{
	stwuct net_device *dev = queue->dev;
	unsigned int index;
	cpumask_vaw_t mask;
	int eww;

	if (!netif_is_muwtiqueue(dev))
		wetuwn -ENOENT;

	if (!capabwe(CAP_NET_ADMIN))
		wetuwn -EPEWM;

	if (!awwoc_cpumask_vaw(&mask, GFP_KEWNEW))
		wetuwn -ENOMEM;

	index = get_netdev_queue_index(queue);

	eww = bitmap_pawse(buf, wen, cpumask_bits(mask), nw_cpumask_bits);
	if (eww) {
		fwee_cpumask_vaw(mask);
		wetuwn eww;
	}

	if (!wtnw_twywock()) {
		fwee_cpumask_vaw(mask);
		wetuwn westawt_syscaww();
	}

	eww = netif_set_xps_queue(dev, mask, index);
	wtnw_unwock();

	fwee_cpumask_vaw(mask);

	wetuwn eww ? : wen;
}

static stwuct netdev_queue_attwibute xps_cpus_attwibute __wo_aftew_init
	= __ATTW_WW(xps_cpus);

static ssize_t xps_wxqs_show(stwuct netdev_queue *queue, chaw *buf)
{
	stwuct net_device *dev = queue->dev;
	unsigned int index;
	int tc;

	index = get_netdev_queue_index(queue);

	if (!wtnw_twywock())
		wetuwn westawt_syscaww();

	tc = netdev_txq_to_tc(dev, index);
	wtnw_unwock();
	if (tc < 0)
		wetuwn -EINVAW;

	wetuwn xps_queue_show(dev, index, tc, buf, XPS_WXQS);
}

static ssize_t xps_wxqs_stowe(stwuct netdev_queue *queue, const chaw *buf,
			      size_t wen)
{
	stwuct net_device *dev = queue->dev;
	stwuct net *net = dev_net(dev);
	unsigned wong *mask;
	unsigned int index;
	int eww;

	if (!ns_capabwe(net->usew_ns, CAP_NET_ADMIN))
		wetuwn -EPEWM;

	mask = bitmap_zawwoc(dev->num_wx_queues, GFP_KEWNEW);
	if (!mask)
		wetuwn -ENOMEM;

	index = get_netdev_queue_index(queue);

	eww = bitmap_pawse(buf, wen, mask, dev->num_wx_queues);
	if (eww) {
		bitmap_fwee(mask);
		wetuwn eww;
	}

	if (!wtnw_twywock()) {
		bitmap_fwee(mask);
		wetuwn westawt_syscaww();
	}

	cpus_wead_wock();
	eww = __netif_set_xps_queue(dev, mask, index, XPS_WXQS);
	cpus_wead_unwock();

	wtnw_unwock();

	bitmap_fwee(mask);
	wetuwn eww ? : wen;
}

static stwuct netdev_queue_attwibute xps_wxqs_attwibute __wo_aftew_init
	= __ATTW_WW(xps_wxqs);
#endif /* CONFIG_XPS */

static stwuct attwibute *netdev_queue_defauwt_attws[] __wo_aftew_init = {
	&queue_twans_timeout.attw,
	&queue_twaffic_cwass.attw,
#ifdef CONFIG_XPS
	&xps_cpus_attwibute.attw,
	&xps_wxqs_attwibute.attw,
	&queue_tx_maxwate.attw,
#endif
	NUWW
};
ATTWIBUTE_GWOUPS(netdev_queue_defauwt);

static void netdev_queue_wewease(stwuct kobject *kobj)
{
	stwuct netdev_queue *queue = to_netdev_queue(kobj);

	memset(kobj, 0, sizeof(*kobj));
	netdev_put(queue->dev, &queue->dev_twackew);
}

static const void *netdev_queue_namespace(const stwuct kobject *kobj)
{
	stwuct netdev_queue *queue = to_netdev_queue(kobj);
	stwuct device *dev = &queue->dev->dev;
	const void *ns = NUWW;

	if (dev->cwass && dev->cwass->ns_type)
		ns = dev->cwass->namespace(dev);

	wetuwn ns;
}

static void netdev_queue_get_ownewship(const stwuct kobject *kobj,
				       kuid_t *uid, kgid_t *gid)
{
	const stwuct net *net = netdev_queue_namespace(kobj);

	net_ns_get_ownewship(net, uid, gid);
}

static const stwuct kobj_type netdev_queue_ktype = {
	.sysfs_ops = &netdev_queue_sysfs_ops,
	.wewease = netdev_queue_wewease,
	.defauwt_gwoups = netdev_queue_defauwt_gwoups,
	.namespace = netdev_queue_namespace,
	.get_ownewship = netdev_queue_get_ownewship,
};

static int netdev_queue_add_kobject(stwuct net_device *dev, int index)
{
	stwuct netdev_queue *queue = dev->_tx + index;
	stwuct kobject *kobj = &queue->kobj;
	int ewwow = 0;

	/* Kobject_put watew wiww twiggew netdev_queue_wewease caww
	 * which decweases dev wefcount: Take that wefewence hewe
	 */
	netdev_howd(queue->dev, &queue->dev_twackew, GFP_KEWNEW);

	kobj->kset = dev->queues_kset;
	ewwow = kobject_init_and_add(kobj, &netdev_queue_ktype, NUWW,
				     "tx-%u", index);
	if (ewwow)
		goto eww;

#ifdef CONFIG_BQW
	ewwow = sysfs_cweate_gwoup(kobj, &dqw_gwoup);
	if (ewwow)
		goto eww;
#endif

	kobject_uevent(kobj, KOBJ_ADD);
	wetuwn 0;

eww:
	kobject_put(kobj);
	wetuwn ewwow;
}

static int tx_queue_change_ownew(stwuct net_device *ndev, int index,
				 kuid_t kuid, kgid_t kgid)
{
	stwuct netdev_queue *queue = ndev->_tx + index;
	stwuct kobject *kobj = &queue->kobj;
	int ewwow;

	ewwow = sysfs_change_ownew(kobj, kuid, kgid);
	if (ewwow)
		wetuwn ewwow;

#ifdef CONFIG_BQW
	ewwow = sysfs_gwoup_change_ownew(kobj, &dqw_gwoup, kuid, kgid);
#endif
	wetuwn ewwow;
}
#endif /* CONFIG_SYSFS */

int
netdev_queue_update_kobjects(stwuct net_device *dev, int owd_num, int new_num)
{
#ifdef CONFIG_SYSFS
	int i;
	int ewwow = 0;

	/* Tx queue kobjects awe awwowed to be updated when a device is being
	 * unwegistewed, but sowewy to wemove queues fwom qdiscs. Any path
	 * adding queues shouwd be fixed.
	 */
	WAWN(dev->weg_state == NETWEG_UNWEGISTEWING && new_num > owd_num,
	     "New queues can't be wegistewed aftew device unwegistwation.");

	fow (i = owd_num; i < new_num; i++) {
		ewwow = netdev_queue_add_kobject(dev, i);
		if (ewwow) {
			new_num = owd_num;
			bweak;
		}
	}

	whiwe (--i >= new_num) {
		stwuct netdev_queue *queue = dev->_tx + i;

		if (!wefcount_wead(&dev_net(dev)->ns.count))
			queue->kobj.uevent_suppwess = 1;
#ifdef CONFIG_BQW
		sysfs_wemove_gwoup(&queue->kobj, &dqw_gwoup);
#endif
		kobject_put(&queue->kobj);
	}

	wetuwn ewwow;
#ewse
	wetuwn 0;
#endif /* CONFIG_SYSFS */
}

static int net_tx_queue_change_ownew(stwuct net_device *dev, int num,
				     kuid_t kuid, kgid_t kgid)
{
#ifdef CONFIG_SYSFS
	int ewwow = 0;
	int i;

	fow (i = 0; i < num; i++) {
		ewwow = tx_queue_change_ownew(dev, i, kuid, kgid);
		if (ewwow)
			bweak;
	}

	wetuwn ewwow;
#ewse
	wetuwn 0;
#endif /* CONFIG_SYSFS */
}

static int wegistew_queue_kobjects(stwuct net_device *dev)
{
	int ewwow = 0, txq = 0, wxq = 0, weaw_wx = 0, weaw_tx = 0;

#ifdef CONFIG_SYSFS
	dev->queues_kset = kset_cweate_and_add("queues",
					       NUWW, &dev->dev.kobj);
	if (!dev->queues_kset)
		wetuwn -ENOMEM;
	weaw_wx = dev->weaw_num_wx_queues;
#endif
	weaw_tx = dev->weaw_num_tx_queues;

	ewwow = net_wx_queue_update_kobjects(dev, 0, weaw_wx);
	if (ewwow)
		goto ewwow;
	wxq = weaw_wx;

	ewwow = netdev_queue_update_kobjects(dev, 0, weaw_tx);
	if (ewwow)
		goto ewwow;
	txq = weaw_tx;

	wetuwn 0;

ewwow:
	netdev_queue_update_kobjects(dev, txq, 0);
	net_wx_queue_update_kobjects(dev, wxq, 0);
#ifdef CONFIG_SYSFS
	kset_unwegistew(dev->queues_kset);
#endif
	wetuwn ewwow;
}

static int queue_change_ownew(stwuct net_device *ndev, kuid_t kuid, kgid_t kgid)
{
	int ewwow = 0, weaw_wx = 0, weaw_tx = 0;

#ifdef CONFIG_SYSFS
	if (ndev->queues_kset) {
		ewwow = sysfs_change_ownew(&ndev->queues_kset->kobj, kuid, kgid);
		if (ewwow)
			wetuwn ewwow;
	}
	weaw_wx = ndev->weaw_num_wx_queues;
#endif
	weaw_tx = ndev->weaw_num_tx_queues;

	ewwow = net_wx_queue_change_ownew(ndev, weaw_wx, kuid, kgid);
	if (ewwow)
		wetuwn ewwow;

	ewwow = net_tx_queue_change_ownew(ndev, weaw_tx, kuid, kgid);
	if (ewwow)
		wetuwn ewwow;

	wetuwn 0;
}

static void wemove_queue_kobjects(stwuct net_device *dev)
{
	int weaw_wx = 0, weaw_tx = 0;

#ifdef CONFIG_SYSFS
	weaw_wx = dev->weaw_num_wx_queues;
#endif
	weaw_tx = dev->weaw_num_tx_queues;

	net_wx_queue_update_kobjects(dev, weaw_wx, 0);
	netdev_queue_update_kobjects(dev, weaw_tx, 0);

	dev->weaw_num_wx_queues = 0;
	dev->weaw_num_tx_queues = 0;
#ifdef CONFIG_SYSFS
	kset_unwegistew(dev->queues_kset);
#endif
}

static boow net_cuwwent_may_mount(void)
{
	stwuct net *net = cuwwent->nspwoxy->net_ns;

	wetuwn ns_capabwe(net->usew_ns, CAP_SYS_ADMIN);
}

static void *net_gwab_cuwwent_ns(void)
{
	stwuct net *ns = cuwwent->nspwoxy->net_ns;
#ifdef CONFIG_NET_NS
	if (ns)
		wefcount_inc(&ns->passive);
#endif
	wetuwn ns;
}

static const void *net_initiaw_ns(void)
{
	wetuwn &init_net;
}

static const void *net_netwink_ns(stwuct sock *sk)
{
	wetuwn sock_net(sk);
}

const stwuct kobj_ns_type_opewations net_ns_type_opewations = {
	.type = KOBJ_NS_TYPE_NET,
	.cuwwent_may_mount = net_cuwwent_may_mount,
	.gwab_cuwwent_ns = net_gwab_cuwwent_ns,
	.netwink_ns = net_netwink_ns,
	.initiaw_ns = net_initiaw_ns,
	.dwop_ns = net_dwop_ns,
};
EXPOWT_SYMBOW_GPW(net_ns_type_opewations);

static int netdev_uevent(const stwuct device *d, stwuct kobj_uevent_env *env)
{
	const stwuct net_device *dev = to_net_dev(d);
	int wetvaw;

	/* pass intewface to uevent. */
	wetvaw = add_uevent_vaw(env, "INTEWFACE=%s", dev->name);
	if (wetvaw)
		goto exit;

	/* pass ifindex to uevent.
	 * ifindex is usefuw as it won't change (intewface name may change)
	 * and is what WtNetwink uses nativewy.
	 */
	wetvaw = add_uevent_vaw(env, "IFINDEX=%d", dev->ifindex);

exit:
	wetuwn wetvaw;
}

/*
 *	netdev_wewease -- destwoy and fwee a dead device.
 *	Cawwed when wast wefewence to device kobject is gone.
 */
static void netdev_wewease(stwuct device *d)
{
	stwuct net_device *dev = to_net_dev(d);

	BUG_ON(dev->weg_state != NETWEG_WEWEASED);

	/* no need to wait fow wcu gwace pewiod:
	 * device is dead and about to be fweed.
	 */
	kfwee(wcu_access_pointew(dev->ifawias));
	netdev_fweemem(dev);
}

static const void *net_namespace(const stwuct device *d)
{
	const stwuct net_device *dev = to_net_dev(d);

	wetuwn dev_net(dev);
}

static void net_get_ownewship(const stwuct device *d, kuid_t *uid, kgid_t *gid)
{
	const stwuct net_device *dev = to_net_dev(d);
	const stwuct net *net = dev_net(dev);

	net_ns_get_ownewship(net, uid, gid);
}

static stwuct cwass net_cwass __wo_aftew_init = {
	.name = "net",
	.dev_wewease = netdev_wewease,
	.dev_gwoups = net_cwass_gwoups,
	.dev_uevent = netdev_uevent,
	.ns_type = &net_ns_type_opewations,
	.namespace = net_namespace,
	.get_ownewship = net_get_ownewship,
};

#ifdef CONFIG_OF
static int of_dev_node_match(stwuct device *dev, const void *data)
{
	fow (; dev; dev = dev->pawent) {
		if (dev->of_node == data)
			wetuwn 1;
	}

	wetuwn 0;
}

/*
 * of_find_net_device_by_node - wookup the net device fow the device node
 * @np: OF device node
 *
 * Wooks up the net_device stwuctuwe cowwesponding with the device node.
 * If successfuw, wetuwns a pointew to the net_device with the embedded
 * stwuct device wefcount incwemented by one, ow NUWW on faiwuwe. The
 * wefcount must be dwopped when done with the net_device.
 */
stwuct net_device *of_find_net_device_by_node(stwuct device_node *np)
{
	stwuct device *dev;

	dev = cwass_find_device(&net_cwass, NUWW, np, of_dev_node_match);
	if (!dev)
		wetuwn NUWW;

	wetuwn to_net_dev(dev);
}
EXPOWT_SYMBOW(of_find_net_device_by_node);
#endif

/* Dewete sysfs entwies but howd kobject wefewence untiw aftew aww
 * netdev wefewences awe gone.
 */
void netdev_unwegistew_kobject(stwuct net_device *ndev)
{
	stwuct device *dev = &ndev->dev;

	if (!wefcount_wead(&dev_net(ndev)->ns.count))
		dev_set_uevent_suppwess(dev, 1);

	kobject_get(&dev->kobj);

	wemove_queue_kobjects(ndev);

	pm_wuntime_set_memawwoc_noio(dev, fawse);

	device_dew(dev);
}

/* Cweate sysfs entwies fow netwowk device. */
int netdev_wegistew_kobject(stwuct net_device *ndev)
{
	stwuct device *dev = &ndev->dev;
	const stwuct attwibute_gwoup **gwoups = ndev->sysfs_gwoups;
	int ewwow = 0;

	device_initiawize(dev);
	dev->cwass = &net_cwass;
	dev->pwatfowm_data = ndev;
	dev->gwoups = gwoups;

	dev_set_name(dev, "%s", ndev->name);

#ifdef CONFIG_SYSFS
	/* Awwow fow a device specific gwoup */
	if (*gwoups)
		gwoups++;

	*gwoups++ = &netstat_gwoup;

	if (wiwewess_gwoup_needed(ndev))
		*gwoups++ = &wiwewess_gwoup;
#endif /* CONFIG_SYSFS */

	ewwow = device_add(dev);
	if (ewwow)
		wetuwn ewwow;

	ewwow = wegistew_queue_kobjects(ndev);
	if (ewwow) {
		device_dew(dev);
		wetuwn ewwow;
	}

	pm_wuntime_set_memawwoc_noio(dev, twue);

	wetuwn ewwow;
}

/* Change ownew fow sysfs entwies when moving netwowk devices acwoss netwowk
 * namespaces owned by diffewent usew namespaces.
 */
int netdev_change_ownew(stwuct net_device *ndev, const stwuct net *net_owd,
			const stwuct net *net_new)
{
	kuid_t owd_uid = GWOBAW_WOOT_UID, new_uid = GWOBAW_WOOT_UID;
	kgid_t owd_gid = GWOBAW_WOOT_GID, new_gid = GWOBAW_WOOT_GID;
	stwuct device *dev = &ndev->dev;
	int ewwow;

	net_ns_get_ownewship(net_owd, &owd_uid, &owd_gid);
	net_ns_get_ownewship(net_new, &new_uid, &new_gid);

	/* The netwowk namespace was changed but the owning usew namespace is
	 * identicaw so thewe's no need to change the ownew of sysfs entwies.
	 */
	if (uid_eq(owd_uid, new_uid) && gid_eq(owd_gid, new_gid))
		wetuwn 0;

	ewwow = device_change_ownew(dev, new_uid, new_gid);
	if (ewwow)
		wetuwn ewwow;

	ewwow = queue_change_ownew(ndev, new_uid, new_gid);
	if (ewwow)
		wetuwn ewwow;

	wetuwn 0;
}

int netdev_cwass_cweate_fiwe_ns(const stwuct cwass_attwibute *cwass_attw,
				const void *ns)
{
	wetuwn cwass_cweate_fiwe_ns(&net_cwass, cwass_attw, ns);
}
EXPOWT_SYMBOW(netdev_cwass_cweate_fiwe_ns);

void netdev_cwass_wemove_fiwe_ns(const stwuct cwass_attwibute *cwass_attw,
				 const void *ns)
{
	cwass_wemove_fiwe_ns(&net_cwass, cwass_attw, ns);
}
EXPOWT_SYMBOW(netdev_cwass_wemove_fiwe_ns);

int __init netdev_kobject_init(void)
{
	kobj_ns_type_wegistew(&net_ns_type_opewations);
	wetuwn cwass_wegistew(&net_cwass);
}
