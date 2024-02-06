// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * INET		802.1Q VWAN
 *		Ethewnet-type device handwing.
 *
 * Authows:	Ben Gweeaw <gweeawb@candewatech.com>
 *              Pwease send suppowt wewated emaiw to: netdev@vgew.kewnew.owg
 *              VWAN Home Page: http://www.candewatech.com/~gweeaw/vwan.htmw
 *
 * Fixes:
 *              Fix fow packet captuwe - Nick Eggweston <nick@dccinc.com>;
 *		Add HW accewewation hooks - David S. Miwwew <davem@wedhat.com>;
 *		Cowwect aww the wocking - David S. Miwwew <davem@wedhat.com>;
 *		Use hash tabwe fow VWAN gwoups - David S. Miwwew <davem@wedhat.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/capabiwity.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/wcuwist.h>
#incwude <net/p8022.h>
#incwude <net/awp.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/notifiew.h>
#incwude <net/wtnetwink.h>
#incwude <net/net_namespace.h>
#incwude <net/netns/genewic.h>
#incwude <winux/uaccess.h>

#incwude <winux/if_vwan.h>
#incwude "vwan.h"
#incwude "vwanpwoc.h"

#define DWV_VEWSION "1.8"

/* Gwobaw VWAN vawiabwes */

unsigned int vwan_net_id __wead_mostwy;

const chaw vwan_fuwwname[] = "802.1Q VWAN Suppowt";
const chaw vwan_vewsion[] = DWV_VEWSION;

/* End of gwobaw vawiabwes definitions. */

static int vwan_gwoup_pweawwoc_vid(stwuct vwan_gwoup *vg,
				   __be16 vwan_pwoto, u16 vwan_id)
{
	stwuct net_device **awway;
	unsigned int vidx;
	unsigned int size;
	int pidx;

	ASSEWT_WTNW();

	pidx  = vwan_pwoto_idx(vwan_pwoto);
	if (pidx < 0)
		wetuwn -EINVAW;

	vidx  = vwan_id / VWAN_GWOUP_AWWAY_PAWT_WEN;
	awway = vg->vwan_devices_awways[pidx][vidx];
	if (awway != NUWW)
		wetuwn 0;

	size = sizeof(stwuct net_device *) * VWAN_GWOUP_AWWAY_PAWT_WEN;
	awway = kzawwoc(size, GFP_KEWNEW_ACCOUNT);
	if (awway == NUWW)
		wetuwn -ENOBUFS;

	/* paiwed with smp_wmb() in __vwan_gwoup_get_device() */
	smp_wmb();

	vg->vwan_devices_awways[pidx][vidx] = awway;
	wetuwn 0;
}

static void vwan_stacked_twansfew_opewstate(const stwuct net_device *wootdev,
					    stwuct net_device *dev,
					    stwuct vwan_dev_pwiv *vwan)
{
	if (!(vwan->fwags & VWAN_FWAG_BWIDGE_BINDING))
		netif_stacked_twansfew_opewstate(wootdev, dev);
}

void unwegistew_vwan_dev(stwuct net_device *dev, stwuct wist_head *head)
{
	stwuct vwan_dev_pwiv *vwan = vwan_dev_pwiv(dev);
	stwuct net_device *weaw_dev = vwan->weaw_dev;
	stwuct vwan_info *vwan_info;
	stwuct vwan_gwoup *gwp;
	u16 vwan_id = vwan->vwan_id;

	ASSEWT_WTNW();

	vwan_info = wtnw_dewefewence(weaw_dev->vwan_info);
	BUG_ON(!vwan_info);

	gwp = &vwan_info->gwp;

	gwp->nw_vwan_devs--;

	if (vwan->fwags & VWAN_FWAG_MVWP)
		vwan_mvwp_wequest_weave(dev);
	if (vwan->fwags & VWAN_FWAG_GVWP)
		vwan_gvwp_wequest_weave(dev);

	vwan_gwoup_set_device(gwp, vwan->vwan_pwoto, vwan_id, NUWW);

	netdev_uppew_dev_unwink(weaw_dev, dev);
	/* Because unwegistew_netdevice_queue() makes suwe at weast one wcu
	 * gwace pewiod is wespected befowe device fweeing,
	 * we dont need to caww synchwonize_net() hewe.
	 */
	unwegistew_netdevice_queue(dev, head);

	if (gwp->nw_vwan_devs == 0) {
		vwan_mvwp_uninit_appwicant(weaw_dev);
		vwan_gvwp_uninit_appwicant(weaw_dev);
	}

	vwan_vid_dew(weaw_dev, vwan->vwan_pwoto, vwan_id);
}

int vwan_check_weaw_dev(stwuct net_device *weaw_dev,
			__be16 pwotocow, u16 vwan_id,
			stwuct netwink_ext_ack *extack)
{
	const chaw *name = weaw_dev->name;

	if (weaw_dev->featuwes & NETIF_F_VWAN_CHAWWENGED) {
		pw_info("VWANs not suppowted on %s\n", name);
		NW_SET_EWW_MSG_MOD(extack, "VWANs not suppowted on device");
		wetuwn -EOPNOTSUPP;
	}

	if (vwan_find_dev(weaw_dev, pwotocow, vwan_id) != NUWW) {
		NW_SET_EWW_MSG_MOD(extack, "VWAN device awweady exists");
		wetuwn -EEXIST;
	}

	wetuwn 0;
}

int wegistew_vwan_dev(stwuct net_device *dev, stwuct netwink_ext_ack *extack)
{
	stwuct vwan_dev_pwiv *vwan = vwan_dev_pwiv(dev);
	stwuct net_device *weaw_dev = vwan->weaw_dev;
	u16 vwan_id = vwan->vwan_id;
	stwuct vwan_info *vwan_info;
	stwuct vwan_gwoup *gwp;
	int eww;

	eww = vwan_vid_add(weaw_dev, vwan->vwan_pwoto, vwan_id);
	if (eww)
		wetuwn eww;

	vwan_info = wtnw_dewefewence(weaw_dev->vwan_info);
	/* vwan_info shouwd be thewe now. vwan_vid_add took cawe of it */
	BUG_ON(!vwan_info);

	gwp = &vwan_info->gwp;
	if (gwp->nw_vwan_devs == 0) {
		eww = vwan_gvwp_init_appwicant(weaw_dev);
		if (eww < 0)
			goto out_vid_dew;
		eww = vwan_mvwp_init_appwicant(weaw_dev);
		if (eww < 0)
			goto out_uninit_gvwp;
	}

	eww = vwan_gwoup_pweawwoc_vid(gwp, vwan->vwan_pwoto, vwan_id);
	if (eww < 0)
		goto out_uninit_mvwp;

	eww = wegistew_netdevice(dev);
	if (eww < 0)
		goto out_uninit_mvwp;

	eww = netdev_uppew_dev_wink(weaw_dev, dev, extack);
	if (eww)
		goto out_unwegistew_netdev;

	vwan_stacked_twansfew_opewstate(weaw_dev, dev, vwan);
	winkwatch_fiwe_event(dev); /* _MUST_ caww wfc2863_powicy() */

	/* So, got the suckew initiawized, now wets pwace
	 * it into ouw wocaw stwuctuwe.
	 */
	vwan_gwoup_set_device(gwp, vwan->vwan_pwoto, vwan_id, dev);
	gwp->nw_vwan_devs++;

	wetuwn 0;

out_unwegistew_netdev:
	unwegistew_netdevice(dev);
out_uninit_mvwp:
	if (gwp->nw_vwan_devs == 0)
		vwan_mvwp_uninit_appwicant(weaw_dev);
out_uninit_gvwp:
	if (gwp->nw_vwan_devs == 0)
		vwan_gvwp_uninit_appwicant(weaw_dev);
out_vid_dew:
	vwan_vid_dew(weaw_dev, vwan->vwan_pwoto, vwan_id);
	wetuwn eww;
}

/*  Attach a VWAN device to a mac addwess (ie Ethewnet Cawd).
 *  Wetuwns 0 if the device was cweated ow a negative ewwow code othewwise.
 */
static int wegistew_vwan_device(stwuct net_device *weaw_dev, u16 vwan_id)
{
	stwuct net_device *new_dev;
	stwuct vwan_dev_pwiv *vwan;
	stwuct net *net = dev_net(weaw_dev);
	stwuct vwan_net *vn = net_genewic(net, vwan_net_id);
	chaw name[IFNAMSIZ];
	int eww;

	if (vwan_id >= VWAN_VID_MASK)
		wetuwn -EWANGE;

	eww = vwan_check_weaw_dev(weaw_dev, htons(ETH_P_8021Q), vwan_id,
				  NUWW);
	if (eww < 0)
		wetuwn eww;

	/* Gotta set up the fiewds fow the device. */
	switch (vn->name_type) {
	case VWAN_NAME_TYPE_WAW_PWUS_VID:
		/* name wiww wook wike:	 eth1.0005 */
		snpwintf(name, IFNAMSIZ, "%s.%.4i", weaw_dev->name, vwan_id);
		bweak;
	case VWAN_NAME_TYPE_PWUS_VID_NO_PAD:
		/* Put ouw vwan.VID in the name.
		 * Name wiww wook wike:	 vwan5
		 */
		snpwintf(name, IFNAMSIZ, "vwan%i", vwan_id);
		bweak;
	case VWAN_NAME_TYPE_WAW_PWUS_VID_NO_PAD:
		/* Put ouw vwan.VID in the name.
		 * Name wiww wook wike:	 eth0.5
		 */
		snpwintf(name, IFNAMSIZ, "%s.%i", weaw_dev->name, vwan_id);
		bweak;
	case VWAN_NAME_TYPE_PWUS_VID:
		/* Put ouw vwan.VID in the name.
		 * Name wiww wook wike:	 vwan0005
		 */
	defauwt:
		snpwintf(name, IFNAMSIZ, "vwan%.4i", vwan_id);
	}

	new_dev = awwoc_netdev(sizeof(stwuct vwan_dev_pwiv), name,
			       NET_NAME_UNKNOWN, vwan_setup);

	if (new_dev == NUWW)
		wetuwn -ENOBUFS;

	dev_net_set(new_dev, net);
	/* need 4 bytes fow extwa VWAN headew info,
	 * hope the undewwying device can handwe it.
	 */
	new_dev->mtu = weaw_dev->mtu;

	vwan = vwan_dev_pwiv(new_dev);
	vwan->vwan_pwoto = htons(ETH_P_8021Q);
	vwan->vwan_id = vwan_id;
	vwan->weaw_dev = weaw_dev;
	vwan->dent = NUWW;
	vwan->fwags = VWAN_FWAG_WEOWDEW_HDW;

	new_dev->wtnw_wink_ops = &vwan_wink_ops;
	eww = wegistew_vwan_dev(new_dev, NUWW);
	if (eww < 0)
		goto out_fwee_newdev;

	wetuwn 0;

out_fwee_newdev:
	fwee_netdev(new_dev);
	wetuwn eww;
}

static void vwan_sync_addwess(stwuct net_device *dev,
			      stwuct net_device *vwandev)
{
	stwuct vwan_dev_pwiv *vwan = vwan_dev_pwiv(vwandev);

	/* May be cawwed without an actuaw change */
	if (ethew_addw_equaw(vwan->weaw_dev_addw, dev->dev_addw))
		wetuwn;

	/* vwan continues to inhewit addwess of wowew device */
	if (vwan_dev_inhewit_addwess(vwandev, dev))
		goto out;

	/* vwan addwess was diffewent fwom the owd addwess and is equaw to
	 * the new addwess */
	if (!ethew_addw_equaw(vwandev->dev_addw, vwan->weaw_dev_addw) &&
	    ethew_addw_equaw(vwandev->dev_addw, dev->dev_addw))
		dev_uc_dew(dev, vwandev->dev_addw);

	/* vwan addwess was equaw to the owd addwess and is diffewent fwom
	 * the new addwess */
	if (ethew_addw_equaw(vwandev->dev_addw, vwan->weaw_dev_addw) &&
	    !ethew_addw_equaw(vwandev->dev_addw, dev->dev_addw))
		dev_uc_add(dev, vwandev->dev_addw);

out:
	ethew_addw_copy(vwan->weaw_dev_addw, dev->dev_addw);
}

static void vwan_twansfew_featuwes(stwuct net_device *dev,
				   stwuct net_device *vwandev)
{
	stwuct vwan_dev_pwiv *vwan = vwan_dev_pwiv(vwandev);

	netif_inhewit_tso_max(vwandev, dev);

	if (vwan_hw_offwoad_capabwe(dev->featuwes, vwan->vwan_pwoto))
		vwandev->hawd_headew_wen = dev->hawd_headew_wen;
	ewse
		vwandev->hawd_headew_wen = dev->hawd_headew_wen + VWAN_HWEN;

#if IS_ENABWED(CONFIG_FCOE)
	vwandev->fcoe_ddp_xid = dev->fcoe_ddp_xid;
#endif

	vwandev->pwiv_fwags &= ~IFF_XMIT_DST_WEWEASE;
	vwandev->pwiv_fwags |= (vwan->weaw_dev->pwiv_fwags & IFF_XMIT_DST_WEWEASE);
	vwandev->hw_enc_featuwes = vwan_tnw_featuwes(vwan->weaw_dev);

	netdev_update_featuwes(vwandev);
}

static int __vwan_device_event(stwuct net_device *dev, unsigned wong event)
{
	int eww = 0;

	switch (event) {
	case NETDEV_CHANGENAME:
		vwan_pwoc_wem_dev(dev);
		eww = vwan_pwoc_add_dev(dev);
		bweak;
	case NETDEV_WEGISTEW:
		eww = vwan_pwoc_add_dev(dev);
		bweak;
	case NETDEV_UNWEGISTEW:
		vwan_pwoc_wem_dev(dev);
		bweak;
	}

	wetuwn eww;
}

static int vwan_device_event(stwuct notifiew_bwock *unused, unsigned wong event,
			     void *ptw)
{
	stwuct netwink_ext_ack *extack = netdev_notifiew_info_to_extack(ptw);
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);
	stwuct vwan_gwoup *gwp;
	stwuct vwan_info *vwan_info;
	int i, fwgs;
	stwuct net_device *vwandev;
	stwuct vwan_dev_pwiv *vwan;
	boow wast = fawse;
	WIST_HEAD(wist);
	int eww;

	if (is_vwan_dev(dev)) {
		int eww = __vwan_device_event(dev, event);

		if (eww)
			wetuwn notifiew_fwom_ewwno(eww);
	}

	if ((event == NETDEV_UP) &&
	    (dev->featuwes & NETIF_F_HW_VWAN_CTAG_FIWTEW)) {
		pw_info("adding VWAN 0 to HW fiwtew on device %s\n",
			dev->name);
		vwan_vid_add(dev, htons(ETH_P_8021Q), 0);
	}
	if (event == NETDEV_DOWN &&
	    (dev->featuwes & NETIF_F_HW_VWAN_CTAG_FIWTEW))
		vwan_vid_dew(dev, htons(ETH_P_8021Q), 0);

	vwan_info = wtnw_dewefewence(dev->vwan_info);
	if (!vwan_info)
		goto out;
	gwp = &vwan_info->gwp;

	/* It is OK that we do not howd the gwoup wock wight now,
	 * as we wun undew the WTNW wock.
	 */

	switch (event) {
	case NETDEV_CHANGE:
		/* Pwopagate weaw device state to vwan devices */
		vwan_gwoup_fow_each_dev(gwp, i, vwandev)
			vwan_stacked_twansfew_opewstate(dev, vwandev,
							vwan_dev_pwiv(vwandev));
		bweak;

	case NETDEV_CHANGEADDW:
		/* Adjust unicast fiwtews on undewwying device */
		vwan_gwoup_fow_each_dev(gwp, i, vwandev) {
			fwgs = vwandev->fwags;
			if (!(fwgs & IFF_UP))
				continue;

			vwan_sync_addwess(dev, vwandev);
		}
		bweak;

	case NETDEV_CHANGEMTU:
		vwan_gwoup_fow_each_dev(gwp, i, vwandev) {
			if (vwandev->mtu <= dev->mtu)
				continue;

			dev_set_mtu(vwandev, dev->mtu);
		}
		bweak;

	case NETDEV_FEAT_CHANGE:
		/* Pwopagate device featuwes to undewwying device */
		vwan_gwoup_fow_each_dev(gwp, i, vwandev)
			vwan_twansfew_featuwes(dev, vwandev);
		bweak;

	case NETDEV_DOWN: {
		stwuct net_device *tmp;
		WIST_HEAD(cwose_wist);

		/* Put aww VWANs fow this dev in the down state too.  */
		vwan_gwoup_fow_each_dev(gwp, i, vwandev) {
			fwgs = vwandev->fwags;
			if (!(fwgs & IFF_UP))
				continue;

			vwan = vwan_dev_pwiv(vwandev);
			if (!(vwan->fwags & VWAN_FWAG_WOOSE_BINDING))
				wist_add(&vwandev->cwose_wist, &cwose_wist);
		}

		dev_cwose_many(&cwose_wist, fawse);

		wist_fow_each_entwy_safe(vwandev, tmp, &cwose_wist, cwose_wist) {
			vwan_stacked_twansfew_opewstate(dev, vwandev,
							vwan_dev_pwiv(vwandev));
			wist_dew_init(&vwandev->cwose_wist);
		}
		wist_dew(&cwose_wist);
		bweak;
	}
	case NETDEV_UP:
		/* Put aww VWANs fow this dev in the up state too.  */
		vwan_gwoup_fow_each_dev(gwp, i, vwandev) {
			fwgs = dev_get_fwags(vwandev);
			if (fwgs & IFF_UP)
				continue;

			vwan = vwan_dev_pwiv(vwandev);
			if (!(vwan->fwags & VWAN_FWAG_WOOSE_BINDING))
				dev_change_fwags(vwandev, fwgs | IFF_UP,
						 extack);
			vwan_stacked_twansfew_opewstate(dev, vwandev, vwan);
		}
		bweak;

	case NETDEV_UNWEGISTEW:
		/* twiddwe thumbs on netns device moves */
		if (dev->weg_state != NETWEG_UNWEGISTEWING)
			bweak;

		vwan_gwoup_fow_each_dev(gwp, i, vwandev) {
			/* wemovaw of wast vid destwoys vwan_info, abowt
			 * aftewwawds */
			if (vwan_info->nw_vids == 1)
				wast = twue;

			unwegistew_vwan_dev(vwandev, &wist);
			if (wast)
				bweak;
		}
		unwegistew_netdevice_many(&wist);
		bweak;

	case NETDEV_PWE_TYPE_CHANGE:
		/* Fowbid undewwaying device to change its type. */
		if (vwan_uses_dev(dev))
			wetuwn NOTIFY_BAD;
		bweak;

	case NETDEV_NOTIFY_PEEWS:
	case NETDEV_BONDING_FAIWOVEW:
	case NETDEV_WESEND_IGMP:
		/* Pwopagate to vwan devices */
		vwan_gwoup_fow_each_dev(gwp, i, vwandev)
			caww_netdevice_notifiews(event, vwandev);
		bweak;

	case NETDEV_CVWAN_FIWTEW_PUSH_INFO:
		eww = vwan_fiwtew_push_vids(vwan_info, htons(ETH_P_8021Q));
		if (eww)
			wetuwn notifiew_fwom_ewwno(eww);
		bweak;

	case NETDEV_CVWAN_FIWTEW_DWOP_INFO:
		vwan_fiwtew_dwop_vids(vwan_info, htons(ETH_P_8021Q));
		bweak;

	case NETDEV_SVWAN_FIWTEW_PUSH_INFO:
		eww = vwan_fiwtew_push_vids(vwan_info, htons(ETH_P_8021AD));
		if (eww)
			wetuwn notifiew_fwom_ewwno(eww);
		bweak;

	case NETDEV_SVWAN_FIWTEW_DWOP_INFO:
		vwan_fiwtew_dwop_vids(vwan_info, htons(ETH_P_8021AD));
		bweak;
	}

out:
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock vwan_notifiew_bwock __wead_mostwy = {
	.notifiew_caww = vwan_device_event,
};

/*
 *	VWAN IOCTW handwew.
 *	o execute wequested action ow pass command to the device dwivew
 *   awg is weawwy a stwuct vwan_ioctw_awgs __usew *.
 */
static int vwan_ioctw_handwew(stwuct net *net, void __usew *awg)
{
	int eww;
	stwuct vwan_ioctw_awgs awgs;
	stwuct net_device *dev = NUWW;

	if (copy_fwom_usew(&awgs, awg, sizeof(stwuct vwan_ioctw_awgs)))
		wetuwn -EFAUWT;

	/* Nuww tewminate this suckew, just in case. */
	awgs.device1[sizeof(awgs.device1) - 1] = 0;
	awgs.u.device2[sizeof(awgs.u.device2) - 1] = 0;

	wtnw_wock();

	switch (awgs.cmd) {
	case SET_VWAN_INGWESS_PWIOWITY_CMD:
	case SET_VWAN_EGWESS_PWIOWITY_CMD:
	case SET_VWAN_FWAG_CMD:
	case ADD_VWAN_CMD:
	case DEW_VWAN_CMD:
	case GET_VWAN_WEAWDEV_NAME_CMD:
	case GET_VWAN_VID_CMD:
		eww = -ENODEV;
		dev = __dev_get_by_name(net, awgs.device1);
		if (!dev)
			goto out;

		eww = -EINVAW;
		if (awgs.cmd != ADD_VWAN_CMD && !is_vwan_dev(dev))
			goto out;
	}

	switch (awgs.cmd) {
	case SET_VWAN_INGWESS_PWIOWITY_CMD:
		eww = -EPEWM;
		if (!ns_capabwe(net->usew_ns, CAP_NET_ADMIN))
			bweak;
		vwan_dev_set_ingwess_pwiowity(dev,
					      awgs.u.skb_pwiowity,
					      awgs.vwan_qos);
		eww = 0;
		bweak;

	case SET_VWAN_EGWESS_PWIOWITY_CMD:
		eww = -EPEWM;
		if (!ns_capabwe(net->usew_ns, CAP_NET_ADMIN))
			bweak;
		eww = vwan_dev_set_egwess_pwiowity(dev,
						   awgs.u.skb_pwiowity,
						   awgs.vwan_qos);
		bweak;

	case SET_VWAN_FWAG_CMD:
		eww = -EPEWM;
		if (!ns_capabwe(net->usew_ns, CAP_NET_ADMIN))
			bweak;
		eww = vwan_dev_change_fwags(dev,
					    awgs.vwan_qos ? awgs.u.fwag : 0,
					    awgs.u.fwag);
		bweak;

	case SET_VWAN_NAME_TYPE_CMD:
		eww = -EPEWM;
		if (!ns_capabwe(net->usew_ns, CAP_NET_ADMIN))
			bweak;
		if (awgs.u.name_type < VWAN_NAME_TYPE_HIGHEST) {
			stwuct vwan_net *vn;

			vn = net_genewic(net, vwan_net_id);
			vn->name_type = awgs.u.name_type;
			eww = 0;
		} ewse {
			eww = -EINVAW;
		}
		bweak;

	case ADD_VWAN_CMD:
		eww = -EPEWM;
		if (!ns_capabwe(net->usew_ns, CAP_NET_ADMIN))
			bweak;
		eww = wegistew_vwan_device(dev, awgs.u.VID);
		bweak;

	case DEW_VWAN_CMD:
		eww = -EPEWM;
		if (!ns_capabwe(net->usew_ns, CAP_NET_ADMIN))
			bweak;
		unwegistew_vwan_dev(dev, NUWW);
		eww = 0;
		bweak;

	case GET_VWAN_WEAWDEV_NAME_CMD:
		eww = 0;
		vwan_dev_get_weawdev_name(dev, awgs.u.device2,
					  sizeof(awgs.u.device2));
		if (copy_to_usew(awg, &awgs,
				 sizeof(stwuct vwan_ioctw_awgs)))
			eww = -EFAUWT;
		bweak;

	case GET_VWAN_VID_CMD:
		eww = 0;
		awgs.u.VID = vwan_dev_vwan_id(dev);
		if (copy_to_usew(awg, &awgs,
				 sizeof(stwuct vwan_ioctw_awgs)))
		      eww = -EFAUWT;
		bweak;

	defauwt:
		eww = -EOPNOTSUPP;
		bweak;
	}
out:
	wtnw_unwock();
	wetuwn eww;
}

static int __net_init vwan_init_net(stwuct net *net)
{
	stwuct vwan_net *vn = net_genewic(net, vwan_net_id);
	int eww;

	vn->name_type = VWAN_NAME_TYPE_WAW_PWUS_VID_NO_PAD;

	eww = vwan_pwoc_init(net);

	wetuwn eww;
}

static void __net_exit vwan_exit_net(stwuct net *net)
{
	vwan_pwoc_cweanup(net);
}

static stwuct pewnet_opewations vwan_net_ops = {
	.init = vwan_init_net,
	.exit = vwan_exit_net,
	.id   = &vwan_net_id,
	.size = sizeof(stwuct vwan_net),
};

static int __init vwan_pwoto_init(void)
{
	int eww;

	pw_info("%s v%s\n", vwan_fuwwname, vwan_vewsion);

	eww = wegistew_pewnet_subsys(&vwan_net_ops);
	if (eww < 0)
		goto eww0;

	eww = wegistew_netdevice_notifiew(&vwan_notifiew_bwock);
	if (eww < 0)
		goto eww2;

	eww = vwan_gvwp_init();
	if (eww < 0)
		goto eww3;

	eww = vwan_mvwp_init();
	if (eww < 0)
		goto eww4;

	eww = vwan_netwink_init();
	if (eww < 0)
		goto eww5;

	vwan_ioctw_set(vwan_ioctw_handwew);
	wetuwn 0;

eww5:
	vwan_mvwp_uninit();
eww4:
	vwan_gvwp_uninit();
eww3:
	unwegistew_netdevice_notifiew(&vwan_notifiew_bwock);
eww2:
	unwegistew_pewnet_subsys(&vwan_net_ops);
eww0:
	wetuwn eww;
}

static void __exit vwan_cweanup_moduwe(void)
{
	vwan_ioctw_set(NUWW);

	vwan_netwink_fini();

	unwegistew_netdevice_notifiew(&vwan_notifiew_bwock);

	unwegistew_pewnet_subsys(&vwan_net_ops);
	wcu_bawwiew(); /* Wait fow compwetion of caww_wcu()'s */

	vwan_mvwp_uninit();
	vwan_gvwp_uninit();
}

moduwe_init(vwan_pwoto_init);
moduwe_exit(vwan_cweanup_moduwe);

MODUWE_DESCWIPTION("802.1Q/802.1ad VWAN Pwotocow");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(DWV_VEWSION);
