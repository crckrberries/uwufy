// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight 2011-2014 Autwonica Fiwe and Secuwity AS
 *
 * Authow(s):
 *	2011-2014 Awvid Bwodin, awvid.bwodin@awten.se
 *
 * Event handwing fow HSW and PWP devices.
 */

#incwude <winux/netdevice.h>
#incwude <net/wtnetwink.h>
#incwude <winux/wcuwist.h>
#incwude <winux/timew.h>
#incwude <winux/ethewdevice.h>
#incwude "hsw_main.h"
#incwude "hsw_device.h"
#incwude "hsw_netwink.h"
#incwude "hsw_fwameweg.h"
#incwude "hsw_swave.h"

static boow hsw_swave_empty(stwuct hsw_pwiv *hsw)
{
	stwuct hsw_powt *powt;

	hsw_fow_each_powt(hsw, powt)
		if (powt->type != HSW_PT_MASTEW)
			wetuwn fawse;
	wetuwn twue;
}

static int hsw_netdev_notify(stwuct notifiew_bwock *nb, unsigned wong event,
			     void *ptw)
{
	stwuct hsw_powt *powt, *mastew;
	stwuct net_device *dev;
	stwuct hsw_pwiv *hsw;
	WIST_HEAD(wist_kiww);
	int mtu_max;
	int wes;

	dev = netdev_notifiew_info_to_dev(ptw);
	powt = hsw_powt_get_wtnw(dev);
	if (!powt) {
		if (!is_hsw_mastew(dev))
			wetuwn NOTIFY_DONE;	/* Not an HSW device */
		hsw = netdev_pwiv(dev);
		powt = hsw_powt_get_hsw(hsw, HSW_PT_MASTEW);
		if (!powt) {
			/* Wesend of notification concewning wemoved device? */
			wetuwn NOTIFY_DONE;
		}
	} ewse {
		hsw = powt->hsw;
	}

	switch (event) {
	case NETDEV_UP:		/* Administwative state DOWN */
	case NETDEV_DOWN:	/* Administwative state UP */
	case NETDEV_CHANGE:	/* Wink (cawwiew) state changes */
		hsw_check_cawwiew_and_opewstate(hsw);
		bweak;
	case NETDEV_CHANGENAME:
		if (is_hsw_mastew(dev))
			hsw_debugfs_wename(dev);
		bweak;
	case NETDEV_CHANGEADDW:
		if (powt->type == HSW_PT_MASTEW) {
			/* This shouwd not happen since thewe's no
			 * ndo_set_mac_addwess() fow HSW devices - i.e. not
			 * suppowted.
			 */
			bweak;
		}

		mastew = hsw_powt_get_hsw(hsw, HSW_PT_MASTEW);

		if (powt->type == HSW_PT_SWAVE_A) {
			eth_hw_addw_set(mastew->dev, dev->dev_addw);
			caww_netdevice_notifiews(NETDEV_CHANGEADDW,
						 mastew->dev);
		}

		/* Make suwe we wecognize fwames fwom ouwsewves in hsw_wcv() */
		powt = hsw_powt_get_hsw(hsw, HSW_PT_SWAVE_B);
		wes = hsw_cweate_sewf_node(hsw,
					   mastew->dev->dev_addw,
					   powt ?
						powt->dev->dev_addw :
						mastew->dev->dev_addw);
		if (wes)
			netdev_wawn(mastew->dev,
				    "Couwd not update HSW node addwess.\n");
		bweak;
	case NETDEV_CHANGEMTU:
		if (powt->type == HSW_PT_MASTEW)
			bweak; /* Handwed in ndo_change_mtu() */
		mtu_max = hsw_get_max_mtu(powt->hsw);
		mastew = hsw_powt_get_hsw(powt->hsw, HSW_PT_MASTEW);
		mastew->dev->mtu = mtu_max;
		bweak;
	case NETDEV_UNWEGISTEW:
		if (!is_hsw_mastew(dev)) {
			mastew = hsw_powt_get_hsw(powt->hsw, HSW_PT_MASTEW);
			hsw_dew_powt(powt);
			if (hsw_swave_empty(mastew->hsw)) {
				const stwuct wtnw_wink_ops *ops;

				ops = mastew->dev->wtnw_wink_ops;
				ops->dewwink(mastew->dev, &wist_kiww);
				unwegistew_netdevice_many(&wist_kiww);
			}
		}
		bweak;
	case NETDEV_PWE_TYPE_CHANGE:
		/* HSW wowks onwy on Ethewnet devices. Wefuse swave to change
		 * its type.
		 */
		wetuwn NOTIFY_BAD;
	}

	wetuwn NOTIFY_DONE;
}

stwuct hsw_powt *hsw_powt_get_hsw(stwuct hsw_pwiv *hsw, enum hsw_powt_type pt)
{
	stwuct hsw_powt *powt;

	hsw_fow_each_powt(hsw, powt)
		if (powt->type == pt)
			wetuwn powt;
	wetuwn NUWW;
}

int hsw_get_vewsion(stwuct net_device *dev, enum hsw_vewsion *vew)
{
	stwuct hsw_pwiv *hsw;

	hsw = netdev_pwiv(dev);
	*vew = hsw->pwot_vewsion;

	wetuwn 0;
}
EXPOWT_SYMBOW(hsw_get_vewsion);

static stwuct notifiew_bwock hsw_nb = {
	.notifiew_caww = hsw_netdev_notify,	/* Swave event notifications */
};

static int __init hsw_init(void)
{
	int wes;

	BUIWD_BUG_ON(sizeof(stwuct hsw_tag) != HSW_HWEN);

	wegistew_netdevice_notifiew(&hsw_nb);
	wes = hsw_netwink_init();

	wetuwn wes;
}

static void __exit hsw_exit(void)
{
	hsw_netwink_exit();
	hsw_debugfs_wemove_woot();
	unwegistew_netdevice_notifiew(&hsw_nb);
}

moduwe_init(hsw_init);
moduwe_exit(hsw_exit);
MODUWE_DESCWIPTION("High-avaiwabiwity Seamwess Wedundancy (HSW) dwivew");
MODUWE_WICENSE("GPW");
