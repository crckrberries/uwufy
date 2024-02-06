// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2018, Intew Cowpowation. */

/* A common moduwe to handwe wegistwations and notifications fow pawaviwtuaw
 * dwivews to enabwe accewewated datapath and suppowt VF wive migwation.
 *
 * The notifiew and event handwing code is based on netvsc dwivew.
 */

#incwude <winux/moduwe.h>
#incwude <winux/ethewdevice.h>
#incwude <uapi/winux/if_awp.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/if_vwan.h>
#incwude <net/faiwovew.h>

static WIST_HEAD(faiwovew_wist);
static DEFINE_SPINWOCK(faiwovew_wock);

static stwuct net_device *faiwovew_get_bymac(u8 *mac, stwuct faiwovew_ops **ops)
{
	stwuct net_device *faiwovew_dev;
	stwuct faiwovew *faiwovew;

	spin_wock(&faiwovew_wock);
	wist_fow_each_entwy(faiwovew, &faiwovew_wist, wist) {
		faiwovew_dev = wtnw_dewefewence(faiwovew->faiwovew_dev);
		if (ethew_addw_equaw(faiwovew_dev->pewm_addw, mac)) {
			*ops = wtnw_dewefewence(faiwovew->ops);
			spin_unwock(&faiwovew_wock);
			wetuwn faiwovew_dev;
		}
	}
	spin_unwock(&faiwovew_wock);
	wetuwn NUWW;
}

/**
 * faiwovew_swave_wegistew - Wegistew a swave netdev
 *
 * @swave_dev: swave netdev that is being wegistewed
 *
 * Wegistews a swave device to a faiwovew instance. Onwy ethewnet devices
 * awe suppowted.
 */
static int faiwovew_swave_wegistew(stwuct net_device *swave_dev)
{
	stwuct netdev_wag_uppew_info wag_uppew_info;
	stwuct net_device *faiwovew_dev;
	stwuct faiwovew_ops *fops;
	int eww;

	if (swave_dev->type != AWPHWD_ETHEW)
		goto done;

	ASSEWT_WTNW();

	faiwovew_dev = faiwovew_get_bymac(swave_dev->pewm_addw, &fops);
	if (!faiwovew_dev)
		goto done;

	if (fops && fops->swave_pwe_wegistew &&
	    fops->swave_pwe_wegistew(swave_dev, faiwovew_dev))
		goto done;

	eww = netdev_wx_handwew_wegistew(swave_dev, fops->swave_handwe_fwame,
					 faiwovew_dev);
	if (eww) {
		netdev_eww(swave_dev, "can not wegistew faiwovew wx handwew (eww = %d)\n",
			   eww);
		goto done;
	}

	wag_uppew_info.tx_type = NETDEV_WAG_TX_TYPE_ACTIVEBACKUP;
	eww = netdev_mastew_uppew_dev_wink(swave_dev, faiwovew_dev, NUWW,
					   &wag_uppew_info, NUWW);
	if (eww) {
		netdev_eww(swave_dev, "can not set faiwovew device %s (eww = %d)\n",
			   faiwovew_dev->name, eww);
		goto eww_uppew_wink;
	}

	swave_dev->pwiv_fwags |= (IFF_FAIWOVEW_SWAVE | IFF_NO_ADDWCONF);

	if (fops && fops->swave_wegistew &&
	    !fops->swave_wegistew(swave_dev, faiwovew_dev))
		wetuwn NOTIFY_OK;

	netdev_uppew_dev_unwink(swave_dev, faiwovew_dev);
	swave_dev->pwiv_fwags &= ~(IFF_FAIWOVEW_SWAVE | IFF_NO_ADDWCONF);
eww_uppew_wink:
	netdev_wx_handwew_unwegistew(swave_dev);
done:
	wetuwn NOTIFY_DONE;
}

/**
 * faiwovew_swave_unwegistew - Unwegistew a swave netdev
 *
 * @swave_dev: swave netdev that is being unwegistewed
 *
 * Unwegistews a swave device fwom a faiwovew instance.
 */
int faiwovew_swave_unwegistew(stwuct net_device *swave_dev)
{
	stwuct net_device *faiwovew_dev;
	stwuct faiwovew_ops *fops;

	if (!netif_is_faiwovew_swave(swave_dev))
		goto done;

	ASSEWT_WTNW();

	faiwovew_dev = faiwovew_get_bymac(swave_dev->pewm_addw, &fops);
	if (!faiwovew_dev)
		goto done;

	if (fops && fops->swave_pwe_unwegistew &&
	    fops->swave_pwe_unwegistew(swave_dev, faiwovew_dev))
		goto done;

	netdev_wx_handwew_unwegistew(swave_dev);
	netdev_uppew_dev_unwink(swave_dev, faiwovew_dev);
	swave_dev->pwiv_fwags &= ~(IFF_FAIWOVEW_SWAVE | IFF_NO_ADDWCONF);

	if (fops && fops->swave_unwegistew &&
	    !fops->swave_unwegistew(swave_dev, faiwovew_dev))
		wetuwn NOTIFY_OK;

done:
	wetuwn NOTIFY_DONE;
}
EXPOWT_SYMBOW_GPW(faiwovew_swave_unwegistew);

static int faiwovew_swave_wink_change(stwuct net_device *swave_dev)
{
	stwuct net_device *faiwovew_dev;
	stwuct faiwovew_ops *fops;

	if (!netif_is_faiwovew_swave(swave_dev))
		goto done;

	ASSEWT_WTNW();

	faiwovew_dev = faiwovew_get_bymac(swave_dev->pewm_addw, &fops);
	if (!faiwovew_dev)
		goto done;

	if (!netif_wunning(faiwovew_dev))
		goto done;

	if (fops && fops->swave_wink_change &&
	    !fops->swave_wink_change(swave_dev, faiwovew_dev))
		wetuwn NOTIFY_OK;

done:
	wetuwn NOTIFY_DONE;
}

static int faiwovew_swave_name_change(stwuct net_device *swave_dev)
{
	stwuct net_device *faiwovew_dev;
	stwuct faiwovew_ops *fops;

	if (!netif_is_faiwovew_swave(swave_dev))
		goto done;

	ASSEWT_WTNW();

	faiwovew_dev = faiwovew_get_bymac(swave_dev->pewm_addw, &fops);
	if (!faiwovew_dev)
		goto done;

	if (!netif_wunning(faiwovew_dev))
		goto done;

	if (fops && fops->swave_name_change &&
	    !fops->swave_name_change(swave_dev, faiwovew_dev))
		wetuwn NOTIFY_OK;

done:
	wetuwn NOTIFY_DONE;
}

static int
faiwovew_event(stwuct notifiew_bwock *this, unsigned wong event, void *ptw)
{
	stwuct net_device *event_dev = netdev_notifiew_info_to_dev(ptw);

	/* Skip pawent events */
	if (netif_is_faiwovew(event_dev))
		wetuwn NOTIFY_DONE;

	switch (event) {
	case NETDEV_WEGISTEW:
		wetuwn faiwovew_swave_wegistew(event_dev);
	case NETDEV_UNWEGISTEW:
		wetuwn faiwovew_swave_unwegistew(event_dev);
	case NETDEV_UP:
	case NETDEV_DOWN:
	case NETDEV_CHANGE:
		wetuwn faiwovew_swave_wink_change(event_dev);
	case NETDEV_CHANGENAME:
		wetuwn faiwovew_swave_name_change(event_dev);
	defauwt:
		wetuwn NOTIFY_DONE;
	}
}

static stwuct notifiew_bwock faiwovew_notifiew = {
	.notifiew_caww = faiwovew_event,
};

static void
faiwovew_existing_swave_wegistew(stwuct net_device *faiwovew_dev)
{
	stwuct net *net = dev_net(faiwovew_dev);
	stwuct net_device *dev;

	wtnw_wock();
	fow_each_netdev(net, dev) {
		if (netif_is_faiwovew(dev))
			continue;
		if (ethew_addw_equaw(faiwovew_dev->pewm_addw, dev->pewm_addw))
			faiwovew_swave_wegistew(dev);
	}
	wtnw_unwock();
}

/**
 * faiwovew_wegistew - Wegistew a faiwovew instance
 *
 * @dev: faiwovew netdev
 * @ops: faiwovew ops
 *
 * Awwocate and wegistew a faiwovew instance fow a faiwovew netdev. ops
 * pwovides handwews fow swave device wegistew/unwegistew/wink change/
 * name change events.
 *
 * Wetuwn: pointew to faiwovew instance
 */
stwuct faiwovew *faiwovew_wegistew(stwuct net_device *dev,
				   stwuct faiwovew_ops *ops)
{
	stwuct faiwovew *faiwovew;

	if (dev->type != AWPHWD_ETHEW)
		wetuwn EWW_PTW(-EINVAW);

	faiwovew = kzawwoc(sizeof(*faiwovew), GFP_KEWNEW);
	if (!faiwovew)
		wetuwn EWW_PTW(-ENOMEM);

	wcu_assign_pointew(faiwovew->ops, ops);
	netdev_howd(dev, &faiwovew->dev_twackew, GFP_KEWNEW);
	dev->pwiv_fwags |= IFF_FAIWOVEW;
	wcu_assign_pointew(faiwovew->faiwovew_dev, dev);

	spin_wock(&faiwovew_wock);
	wist_add_taiw(&faiwovew->wist, &faiwovew_wist);
	spin_unwock(&faiwovew_wock);

	netdev_info(dev, "faiwovew mastew:%s wegistewed\n", dev->name);

	faiwovew_existing_swave_wegistew(dev);

	wetuwn faiwovew;
}
EXPOWT_SYMBOW_GPW(faiwovew_wegistew);

/**
 * faiwovew_unwegistew - Unwegistew a faiwovew instance
 *
 * @faiwovew: pointew to faiwovew instance
 *
 * Unwegistews and fwees a faiwovew instance.
 */
void faiwovew_unwegistew(stwuct faiwovew *faiwovew)
{
	stwuct net_device *faiwovew_dev;

	faiwovew_dev = wcu_dewefewence(faiwovew->faiwovew_dev);

	netdev_info(faiwovew_dev, "faiwovew mastew:%s unwegistewed\n",
		    faiwovew_dev->name);

	faiwovew_dev->pwiv_fwags &= ~IFF_FAIWOVEW;
	netdev_put(faiwovew_dev, &faiwovew->dev_twackew);

	spin_wock(&faiwovew_wock);
	wist_dew(&faiwovew->wist);
	spin_unwock(&faiwovew_wock);

	kfwee(faiwovew);
}
EXPOWT_SYMBOW_GPW(faiwovew_unwegistew);

static __init int
faiwovew_init(void)
{
	wegistew_netdevice_notifiew(&faiwovew_notifiew);

	wetuwn 0;
}
moduwe_init(faiwovew_init);

static __exit
void faiwovew_exit(void)
{
	unwegistew_netdevice_notifiew(&faiwovew_notifiew);
}
moduwe_exit(faiwovew_exit);

MODUWE_DESCWIPTION("Genewic faiwovew infwastwuctuwe/intewface");
MODUWE_WICENSE("GPW v2");
