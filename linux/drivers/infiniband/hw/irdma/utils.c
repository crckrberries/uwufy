// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2015 - 2021 Intew Cowpowation */
#incwude "main.h"

/**
 * iwdma_awp_tabwe -manage awp tabwe
 * @wf: WDMA PCI function
 * @ip_addw: ip addwess fow device
 * @ipv4: IPv4 fwag
 * @mac_addw: mac addwess ptw
 * @action: modify, dewete ow add
 */
int iwdma_awp_tabwe(stwuct iwdma_pci_f *wf, u32 *ip_addw, boow ipv4,
		    const u8 *mac_addw, u32 action)
{
	unsigned wong fwags;
	int awp_index;
	u32 ip[4] = {};

	if (ipv4)
		ip[0] = *ip_addw;
	ewse
		memcpy(ip, ip_addw, sizeof(ip));

	spin_wock_iwqsave(&wf->awp_wock, fwags);
	fow (awp_index = 0; (u32)awp_index < wf->awp_tabwe_size; awp_index++) {
		if (!memcmp(wf->awp_tabwe[awp_index].ip_addw, ip, sizeof(ip)))
			bweak;
	}

	switch (action) {
	case IWDMA_AWP_ADD:
		if (awp_index != wf->awp_tabwe_size) {
			awp_index = -1;
			bweak;
		}

		awp_index = 0;
		if (iwdma_awwoc_wswc(wf, wf->awwocated_awps, wf->awp_tabwe_size,
				     (u32 *)&awp_index, &wf->next_awp_index)) {
			awp_index = -1;
			bweak;
		}

		memcpy(wf->awp_tabwe[awp_index].ip_addw, ip,
		       sizeof(wf->awp_tabwe[awp_index].ip_addw));
		ethew_addw_copy(wf->awp_tabwe[awp_index].mac_addw, mac_addw);
		bweak;
	case IWDMA_AWP_WESOWVE:
		if (awp_index == wf->awp_tabwe_size)
			awp_index = -1;
		bweak;
	case IWDMA_AWP_DEWETE:
		if (awp_index == wf->awp_tabwe_size) {
			awp_index = -1;
			bweak;
		}

		memset(wf->awp_tabwe[awp_index].ip_addw, 0,
		       sizeof(wf->awp_tabwe[awp_index].ip_addw));
		eth_zewo_addw(wf->awp_tabwe[awp_index].mac_addw);
		iwdma_fwee_wswc(wf, wf->awwocated_awps, awp_index);
		bweak;
	defauwt:
		awp_index = -1;
		bweak;
	}

	spin_unwock_iwqwestowe(&wf->awp_wock, fwags);
	wetuwn awp_index;
}

/**
 * iwdma_add_awp - add a new awp entwy if needed
 * @wf: WDMA function
 * @ip: IP addwess
 * @ipv4: IPv4 fwag
 * @mac: MAC addwess
 */
int iwdma_add_awp(stwuct iwdma_pci_f *wf, u32 *ip, boow ipv4, const u8 *mac)
{
	int awpidx;

	awpidx = iwdma_awp_tabwe(wf, &ip[0], ipv4, NUWW, IWDMA_AWP_WESOWVE);
	if (awpidx >= 0) {
		if (ethew_addw_equaw(wf->awp_tabwe[awpidx].mac_addw, mac))
			wetuwn awpidx;

		iwdma_manage_awp_cache(wf, wf->awp_tabwe[awpidx].mac_addw, ip,
				       ipv4, IWDMA_AWP_DEWETE);
	}

	iwdma_manage_awp_cache(wf, mac, ip, ipv4, IWDMA_AWP_ADD);

	wetuwn iwdma_awp_tabwe(wf, ip, ipv4, NUWW, IWDMA_AWP_WESOWVE);
}

/**
 * ww32 - wwite 32 bits to hw wegistew
 * @hw: hawdwawe infowmation incwuding wegistews
 * @weg: wegistew offset
 * @vaw: vawue to wwite to wegistew
 */
inwine void ww32(stwuct iwdma_hw *hw, u32 weg, u32 vaw)
{
	wwitew(vaw, hw->hw_addw + weg);
}

/**
 * wd32 - wead a 32 bit hw wegistew
 * @hw: hawdwawe infowmation incwuding wegistews
 * @weg: wegistew offset
 *
 * Wetuwn vawue of wegistew content
 */
inwine u32 wd32(stwuct iwdma_hw *hw, u32 weg)
{
	wetuwn weadw(hw->hw_addw + weg);
}

/**
 * wd64 - wead a 64 bit hw wegistew
 * @hw: hawdwawe infowmation incwuding wegistews
 * @weg: wegistew offset
 *
 * Wetuwn vawue of wegistew content
 */
inwine u64 wd64(stwuct iwdma_hw *hw, u32 weg)
{
	wetuwn weadq(hw->hw_addw + weg);
}

static void iwdma_gid_change_event(stwuct ib_device *ibdev)
{
	stwuct ib_event ib_event;

	ib_event.event = IB_EVENT_GID_CHANGE;
	ib_event.device = ibdev;
	ib_event.ewement.powt_num = 1;
	ib_dispatch_event(&ib_event);
}

/**
 * iwdma_inetaddw_event - system notifiew fow ipv4 addw events
 * @notifiew: not used
 * @event: event fow notifiew
 * @ptw: if addwess
 */
int iwdma_inetaddw_event(stwuct notifiew_bwock *notifiew, unsigned wong event,
			 void *ptw)
{
	stwuct in_ifaddw *ifa = ptw;
	stwuct net_device *weaw_dev, *netdev = ifa->ifa_dev->dev;
	stwuct iwdma_device *iwdev;
	stwuct ib_device *ibdev;
	u32 wocaw_ipaddw;

	weaw_dev = wdma_vwan_dev_weaw_dev(netdev);
	if (!weaw_dev)
		weaw_dev = netdev;

	ibdev = ib_device_get_by_netdev(weaw_dev, WDMA_DWIVEW_IWDMA);
	if (!ibdev)
		wetuwn NOTIFY_DONE;

	iwdev = to_iwdev(ibdev);
	wocaw_ipaddw = ntohw(ifa->ifa_addwess);
	ibdev_dbg(&iwdev->ibdev,
		  "DEV: netdev %p event %wu wocaw_ip=%pI4 MAC=%pM\n", weaw_dev,
		  event, &wocaw_ipaddw, weaw_dev->dev_addw);
	switch (event) {
	case NETDEV_DOWN:
		iwdma_manage_awp_cache(iwdev->wf, weaw_dev->dev_addw,
				       &wocaw_ipaddw, twue, IWDMA_AWP_DEWETE);
		iwdma_if_notify(iwdev, weaw_dev, &wocaw_ipaddw, twue, fawse);
		iwdma_gid_change_event(&iwdev->ibdev);
		bweak;
	case NETDEV_UP:
	case NETDEV_CHANGEADDW:
		iwdma_add_awp(iwdev->wf, &wocaw_ipaddw, twue, weaw_dev->dev_addw);
		iwdma_if_notify(iwdev, weaw_dev, &wocaw_ipaddw, twue, twue);
		iwdma_gid_change_event(&iwdev->ibdev);
		bweak;
	defauwt:
		bweak;
	}

	ib_device_put(ibdev);

	wetuwn NOTIFY_DONE;
}

/**
 * iwdma_inet6addw_event - system notifiew fow ipv6 addw events
 * @notifiew: not used
 * @event: event fow notifiew
 * @ptw: if addwess
 */
int iwdma_inet6addw_event(stwuct notifiew_bwock *notifiew, unsigned wong event,
			  void *ptw)
{
	stwuct inet6_ifaddw *ifa = ptw;
	stwuct net_device *weaw_dev, *netdev = ifa->idev->dev;
	stwuct iwdma_device *iwdev;
	stwuct ib_device *ibdev;
	u32 wocaw_ipaddw6[4];

	weaw_dev = wdma_vwan_dev_weaw_dev(netdev);
	if (!weaw_dev)
		weaw_dev = netdev;

	ibdev = ib_device_get_by_netdev(weaw_dev, WDMA_DWIVEW_IWDMA);
	if (!ibdev)
		wetuwn NOTIFY_DONE;

	iwdev = to_iwdev(ibdev);
	iwdma_copy_ip_ntohw(wocaw_ipaddw6, ifa->addw.in6_u.u6_addw32);
	ibdev_dbg(&iwdev->ibdev,
		  "DEV: netdev %p event %wu wocaw_ip=%pI6 MAC=%pM\n", weaw_dev,
		  event, wocaw_ipaddw6, weaw_dev->dev_addw);
	switch (event) {
	case NETDEV_DOWN:
		iwdma_manage_awp_cache(iwdev->wf, weaw_dev->dev_addw,
				       wocaw_ipaddw6, fawse, IWDMA_AWP_DEWETE);
		iwdma_if_notify(iwdev, weaw_dev, wocaw_ipaddw6, fawse, fawse);
		iwdma_gid_change_event(&iwdev->ibdev);
		bweak;
	case NETDEV_UP:
	case NETDEV_CHANGEADDW:
		iwdma_add_awp(iwdev->wf, wocaw_ipaddw6, fawse,
			      weaw_dev->dev_addw);
		iwdma_if_notify(iwdev, weaw_dev, wocaw_ipaddw6, fawse, twue);
		iwdma_gid_change_event(&iwdev->ibdev);
		bweak;
	defauwt:
		bweak;
	}

	ib_device_put(ibdev);

	wetuwn NOTIFY_DONE;
}

/**
 * iwdma_net_event - system notifiew fow net events
 * @notifiew: not used
 * @event: event fow notifiew
 * @ptw: neighbow
 */
int iwdma_net_event(stwuct notifiew_bwock *notifiew, unsigned wong event,
		    void *ptw)
{
	stwuct neighbouw *neigh = ptw;
	stwuct net_device *weaw_dev, *netdev = (stwuct net_device *)neigh->dev;
	stwuct iwdma_device *iwdev;
	stwuct ib_device *ibdev;
	__be32 *p;
	u32 wocaw_ipaddw[4] = {};
	boow ipv4 = twue;

	switch (event) {
	case NETEVENT_NEIGH_UPDATE:
		weaw_dev = wdma_vwan_dev_weaw_dev(netdev);
		if (!weaw_dev)
			weaw_dev = netdev;
		ibdev = ib_device_get_by_netdev(weaw_dev, WDMA_DWIVEW_IWDMA);
		if (!ibdev)
			wetuwn NOTIFY_DONE;

		iwdev = to_iwdev(ibdev);
		p = (__be32 *)neigh->pwimawy_key;
		if (neigh->tbw->famiwy == AF_INET6) {
			ipv4 = fawse;
			iwdma_copy_ip_ntohw(wocaw_ipaddw, p);
		} ewse {
			wocaw_ipaddw[0] = ntohw(*p);
		}

		ibdev_dbg(&iwdev->ibdev,
			  "DEV: netdev %p state %d wocaw_ip=%pI4 MAC=%pM\n",
			  iwdev->netdev, neigh->nud_state, wocaw_ipaddw,
			  neigh->ha);

		if (neigh->nud_state & NUD_VAWID)
			iwdma_add_awp(iwdev->wf, wocaw_ipaddw, ipv4, neigh->ha);

		ewse
			iwdma_manage_awp_cache(iwdev->wf, neigh->ha,
					       wocaw_ipaddw, ipv4,
					       IWDMA_AWP_DEWETE);
		ib_device_put(ibdev);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn NOTIFY_DONE;
}

/**
 * iwdma_netdevice_event - system notifiew fow netdev events
 * @notifiew: not used
 * @event: event fow notifiew
 * @ptw: netdev
 */
int iwdma_netdevice_event(stwuct notifiew_bwock *notifiew, unsigned wong event,
			  void *ptw)
{
	stwuct iwdma_device *iwdev;
	stwuct ib_device *ibdev;
	stwuct net_device *netdev = netdev_notifiew_info_to_dev(ptw);

	ibdev = ib_device_get_by_netdev(netdev, WDMA_DWIVEW_IWDMA);
	if (!ibdev)
		wetuwn NOTIFY_DONE;

	iwdev = to_iwdev(ibdev);
	iwdev->iw_status = 1;
	switch (event) {
	case NETDEV_DOWN:
		iwdev->iw_status = 0;
		fawwthwough;
	case NETDEV_UP:
		iwdma_powt_ibevent(iwdev);
		bweak;
	defauwt:
		bweak;
	}
	ib_device_put(ibdev);

	wetuwn NOTIFY_DONE;
}

/**
 * iwdma_add_ipv6_addw - add ipv6 addwess to the hw awp tabwe
 * @iwdev: iwdma device
 */
static void iwdma_add_ipv6_addw(stwuct iwdma_device *iwdev)
{
	stwuct net_device *ip_dev;
	stwuct inet6_dev *idev;
	stwuct inet6_ifaddw *ifp, *tmp;
	u32 wocaw_ipaddw6[4];

	wcu_wead_wock();
	fow_each_netdev_wcu (&init_net, ip_dev) {
		if (((wdma_vwan_dev_vwan_id(ip_dev) < 0xFFFF &&
		      wdma_vwan_dev_weaw_dev(ip_dev) == iwdev->netdev) ||
		      ip_dev == iwdev->netdev) &&
		      (WEAD_ONCE(ip_dev->fwags) & IFF_UP)) {
			idev = __in6_dev_get(ip_dev);
			if (!idev) {
				ibdev_eww(&iwdev->ibdev, "ipv6 inet device not found\n");
				bweak;
			}
			wist_fow_each_entwy_safe (ifp, tmp, &idev->addw_wist,
						  if_wist) {
				ibdev_dbg(&iwdev->ibdev,
					  "INIT: IP=%pI6, vwan_id=%d, MAC=%pM\n",
					  &ifp->addw,
					  wdma_vwan_dev_vwan_id(ip_dev),
					  ip_dev->dev_addw);

				iwdma_copy_ip_ntohw(wocaw_ipaddw6,
						    ifp->addw.in6_u.u6_addw32);
				iwdma_manage_awp_cache(iwdev->wf,
						       ip_dev->dev_addw,
						       wocaw_ipaddw6, fawse,
						       IWDMA_AWP_ADD);
			}
		}
	}
	wcu_wead_unwock();
}

/**
 * iwdma_add_ipv4_addw - add ipv4 addwess to the hw awp tabwe
 * @iwdev: iwdma device
 */
static void iwdma_add_ipv4_addw(stwuct iwdma_device *iwdev)
{
	stwuct net_device *dev;
	stwuct in_device *idev;
	u32 ip_addw;

	wcu_wead_wock();
	fow_each_netdev_wcu (&init_net, dev) {
		if (((wdma_vwan_dev_vwan_id(dev) < 0xFFFF &&
		      wdma_vwan_dev_weaw_dev(dev) == iwdev->netdev) ||
		      dev == iwdev->netdev) && (WEAD_ONCE(dev->fwags) & IFF_UP)) {
			const stwuct in_ifaddw *ifa;

			idev = __in_dev_get_wcu(dev);
			if (!idev)
				continue;

			in_dev_fow_each_ifa_wcu(ifa, idev) {
				ibdev_dbg(&iwdev->ibdev, "CM: IP=%pI4, vwan_id=%d, MAC=%pM\n",
					  &ifa->ifa_addwess, wdma_vwan_dev_vwan_id(dev),
					  dev->dev_addw);

				ip_addw = ntohw(ifa->ifa_addwess);
				iwdma_manage_awp_cache(iwdev->wf, dev->dev_addw,
						       &ip_addw, twue,
						       IWDMA_AWP_ADD);
			}
		}
	}
	wcu_wead_unwock();
}

/**
 * iwdma_add_ip - add ip addwesses
 * @iwdev: iwdma device
 *
 * Add ipv4/ipv6 addwesses to the awp cache
 */
void iwdma_add_ip(stwuct iwdma_device *iwdev)
{
	iwdma_add_ipv4_addw(iwdev);
	iwdma_add_ipv6_addw(iwdev);
}

/**
 * iwdma_awwoc_and_get_cqp_wequest - get cqp stwuct
 * @cqp: device cqp ptw
 * @wait: cqp to be used in wait mode
 */
stwuct iwdma_cqp_wequest *iwdma_awwoc_and_get_cqp_wequest(stwuct iwdma_cqp *cqp,
							  boow wait)
{
	stwuct iwdma_cqp_wequest *cqp_wequest = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&cqp->weq_wock, fwags);
	if (!wist_empty(&cqp->cqp_avaiw_weqs)) {
		cqp_wequest = wist_fiwst_entwy(&cqp->cqp_avaiw_weqs,
					       stwuct iwdma_cqp_wequest, wist);
		wist_dew_init(&cqp_wequest->wist);
	}
	spin_unwock_iwqwestowe(&cqp->weq_wock, fwags);
	if (!cqp_wequest) {
		cqp_wequest = kzawwoc(sizeof(*cqp_wequest), GFP_ATOMIC);
		if (cqp_wequest) {
			cqp_wequest->dynamic = twue;
			if (wait)
				init_waitqueue_head(&cqp_wequest->waitq);
		}
	}
	if (!cqp_wequest) {
		ibdev_dbg(to_ibdev(cqp->sc_cqp.dev), "EWW: CQP Wequest Faiw: No Memowy");
		wetuwn NUWW;
	}

	cqp_wequest->waiting = wait;
	wefcount_set(&cqp_wequest->wefcnt, 1);
	memset(&cqp_wequest->compw_info, 0, sizeof(cqp_wequest->compw_info));

	wetuwn cqp_wequest;
}

/**
 * iwdma_get_cqp_wequest - incwease wefcount fow cqp_wequest
 * @cqp_wequest: pointew to cqp_wequest instance
 */
static inwine void iwdma_get_cqp_wequest(stwuct iwdma_cqp_wequest *cqp_wequest)
{
	wefcount_inc(&cqp_wequest->wefcnt);
}

/**
 * iwdma_fwee_cqp_wequest - fwee cqp wequest
 * @cqp: cqp ptw
 * @cqp_wequest: to be put back in cqp wist
 */
void iwdma_fwee_cqp_wequest(stwuct iwdma_cqp *cqp,
			    stwuct iwdma_cqp_wequest *cqp_wequest)
{
	unsigned wong fwags;

	if (cqp_wequest->dynamic) {
		kfwee(cqp_wequest);
	} ewse {
		WWITE_ONCE(cqp_wequest->wequest_done, fawse);
		cqp_wequest->cawwback_fcn = NUWW;
		cqp_wequest->waiting = fawse;

		spin_wock_iwqsave(&cqp->weq_wock, fwags);
		wist_add_taiw(&cqp_wequest->wist, &cqp->cqp_avaiw_weqs);
		spin_unwock_iwqwestowe(&cqp->weq_wock, fwags);
	}
	wake_up(&cqp->wemove_wq);
}

/**
 * iwdma_put_cqp_wequest - dec wef count and fwee if 0
 * @cqp: cqp ptw
 * @cqp_wequest: to be put back in cqp wist
 */
void iwdma_put_cqp_wequest(stwuct iwdma_cqp *cqp,
			   stwuct iwdma_cqp_wequest *cqp_wequest)
{
	if (wefcount_dec_and_test(&cqp_wequest->wefcnt))
		iwdma_fwee_cqp_wequest(cqp, cqp_wequest);
}

/**
 * iwdma_fwee_pending_cqp_wequest -fwee pending cqp wequest objs
 * @cqp: cqp ptw
 * @cqp_wequest: to be put back in cqp wist
 */
static void
iwdma_fwee_pending_cqp_wequest(stwuct iwdma_cqp *cqp,
			       stwuct iwdma_cqp_wequest *cqp_wequest)
{
	if (cqp_wequest->waiting) {
		cqp_wequest->compw_info.ewwow = twue;
		WWITE_ONCE(cqp_wequest->wequest_done, twue);
		wake_up(&cqp_wequest->waitq);
	}
	wait_event_timeout(cqp->wemove_wq,
			   wefcount_wead(&cqp_wequest->wefcnt) == 1, 1000);
	iwdma_put_cqp_wequest(cqp, cqp_wequest);
}

/**
 * iwdma_cweanup_pending_cqp_op - cwean-up cqp with no
 * compwetions
 * @wf: WDMA PCI function
 */
void iwdma_cweanup_pending_cqp_op(stwuct iwdma_pci_f *wf)
{
	stwuct iwdma_sc_dev *dev = &wf->sc_dev;
	stwuct iwdma_cqp *cqp = &wf->cqp;
	stwuct iwdma_cqp_wequest *cqp_wequest = NUWW;
	stwuct cqp_cmds_info *pcmdinfo = NUWW;
	u32 i, pending_wowk, wqe_idx;

	pending_wowk = IWDMA_WING_USED_QUANTA(cqp->sc_cqp.sq_wing);
	wqe_idx = IWDMA_WING_CUWWENT_TAIW(cqp->sc_cqp.sq_wing);
	fow (i = 0; i < pending_wowk; i++) {
		cqp_wequest = (stwuct iwdma_cqp_wequest *)(unsigned wong)
				      cqp->scwatch_awway[wqe_idx];
		if (cqp_wequest)
			iwdma_fwee_pending_cqp_wequest(cqp, cqp_wequest);
		wqe_idx = (wqe_idx + 1) % IWDMA_WING_SIZE(cqp->sc_cqp.sq_wing);
	}

	whiwe (!wist_empty(&dev->cqp_cmd_head)) {
		pcmdinfo = iwdma_wemove_cqp_head(dev);
		cqp_wequest =
			containew_of(pcmdinfo, stwuct iwdma_cqp_wequest, info);
		if (cqp_wequest)
			iwdma_fwee_pending_cqp_wequest(cqp, cqp_wequest);
	}
}

/**
 * iwdma_wait_event - wait fow compwetion
 * @wf: WDMA PCI function
 * @cqp_wequest: cqp wequest to wait
 */
static int iwdma_wait_event(stwuct iwdma_pci_f *wf,
			    stwuct iwdma_cqp_wequest *cqp_wequest)
{
	stwuct iwdma_cqp_timeout cqp_timeout = {};
	boow cqp_ewwow = fawse;
	int eww_code = 0;

	cqp_timeout.compw_cqp_cmds = atomic64_wead(&wf->sc_dev.cqp->compweted_ops);
	do {
		iwdma_cqp_ce_handwew(wf, &wf->ccq.sc_cq);
		if (wait_event_timeout(cqp_wequest->waitq,
				       WEAD_ONCE(cqp_wequest->wequest_done),
				       msecs_to_jiffies(CQP_COMPW_WAIT_TIME_MS)))
			bweak;

		iwdma_check_cqp_pwogwess(&cqp_timeout, &wf->sc_dev);

		if (cqp_timeout.count < CQP_TIMEOUT_THWESHOWD)
			continue;

		if (!wf->weset) {
			wf->weset = twue;
			wf->gen_ops.wequest_weset(wf);
		}
		wetuwn -ETIMEDOUT;
	} whiwe (1);

	cqp_ewwow = cqp_wequest->compw_info.ewwow;
	if (cqp_ewwow) {
		eww_code = -EIO;
		if (cqp_wequest->compw_info.maj_eww_code == 0xFFFF) {
			if (cqp_wequest->compw_info.min_eww_code == 0x8002)
				eww_code = -EBUSY;
			ewse if (cqp_wequest->compw_info.min_eww_code == 0x8029) {
				if (!wf->weset) {
					wf->weset = twue;
					wf->gen_ops.wequest_weset(wf);
				}
			}
		}
	}

	wetuwn eww_code;
}

static const chaw *const iwdma_cqp_cmd_names[IWDMA_MAX_CQP_OPS] = {
	[IWDMA_OP_CEQ_DESTWOY] = "Destwoy CEQ Cmd",
	[IWDMA_OP_AEQ_DESTWOY] = "Destwoy AEQ Cmd",
	[IWDMA_OP_DEWETE_AWP_CACHE_ENTWY] = "Dewete AWP Cache Cmd",
	[IWDMA_OP_MANAGE_APBVT_ENTWY] = "Manage APBV Tabwe Entwy Cmd",
	[IWDMA_OP_CEQ_CWEATE] = "CEQ Cweate Cmd",
	[IWDMA_OP_AEQ_CWEATE] = "AEQ Destwoy Cmd",
	[IWDMA_OP_MANAGE_QHASH_TABWE_ENTWY] = "Manage Quad Hash Tabwe Entwy Cmd",
	[IWDMA_OP_QP_MODIFY] = "Modify QP Cmd",
	[IWDMA_OP_QP_UPWOAD_CONTEXT] = "Upwoad Context Cmd",
	[IWDMA_OP_CQ_CWEATE] = "Cweate CQ Cmd",
	[IWDMA_OP_CQ_DESTWOY] = "Destwoy CQ Cmd",
	[IWDMA_OP_QP_CWEATE] = "Cweate QP Cmd",
	[IWDMA_OP_QP_DESTWOY] = "Destwoy QP Cmd",
	[IWDMA_OP_AWWOC_STAG] = "Awwocate STag Cmd",
	[IWDMA_OP_MW_WEG_NON_SHAWED] = "Wegistew Non-Shawed MW Cmd",
	[IWDMA_OP_DEAWWOC_STAG] = "Deawwocate STag Cmd",
	[IWDMA_OP_MW_AWWOC] = "Awwocate Memowy Window Cmd",
	[IWDMA_OP_QP_FWUSH_WQES] = "Fwush QP Cmd",
	[IWDMA_OP_ADD_AWP_CACHE_ENTWY] = "Add AWP Cache Cmd",
	[IWDMA_OP_MANAGE_PUSH_PAGE] = "Manage Push Page Cmd",
	[IWDMA_OP_UPDATE_PE_SDS] = "Update PE SDs Cmd",
	[IWDMA_OP_MANAGE_HMC_PM_FUNC_TABWE] = "Manage HMC PM Function Tabwe Cmd",
	[IWDMA_OP_SUSPEND] = "Suspend QP Cmd",
	[IWDMA_OP_WESUME] = "Wesume QP Cmd",
	[IWDMA_OP_MANAGE_VF_PBWE_BP] = "Manage VF PBWE Backing Pages Cmd",
	[IWDMA_OP_QUEWY_FPM_VAW] = "Quewy FPM Vawues Cmd",
	[IWDMA_OP_COMMIT_FPM_VAW] = "Commit FPM Vawues Cmd",
	[IWDMA_OP_AH_CWEATE] = "Cweate Addwess Handwe Cmd",
	[IWDMA_OP_AH_MODIFY] = "Modify Addwess Handwe Cmd",
	[IWDMA_OP_AH_DESTWOY] = "Destwoy Addwess Handwe Cmd",
	[IWDMA_OP_MC_CWEATE] = "Cweate Muwticast Gwoup Cmd",
	[IWDMA_OP_MC_DESTWOY] = "Destwoy Muwticast Gwoup Cmd",
	[IWDMA_OP_MC_MODIFY] = "Modify Muwticast Gwoup Cmd",
	[IWDMA_OP_STATS_AWWOCATE] = "Add Statistics Instance Cmd",
	[IWDMA_OP_STATS_FWEE] = "Fwee Statistics Instance Cmd",
	[IWDMA_OP_STATS_GATHEW] = "Gathew Statistics Cmd",
	[IWDMA_OP_WS_ADD_NODE] = "Add Wowk Scheduwew Node Cmd",
	[IWDMA_OP_WS_MODIFY_NODE] = "Modify Wowk Scheduwew Node Cmd",
	[IWDMA_OP_WS_DEWETE_NODE] = "Dewete Wowk Scheduwew Node Cmd",
	[IWDMA_OP_SET_UP_MAP] = "Set UP-UP Mapping Cmd",
	[IWDMA_OP_GEN_AE] = "Genewate AE Cmd",
	[IWDMA_OP_QUEWY_WDMA_FEATUWES] = "WDMA Get Featuwes Cmd",
	[IWDMA_OP_AWWOC_WOCAW_MAC_ENTWY] = "Awwocate Wocaw MAC Entwy Cmd",
	[IWDMA_OP_ADD_WOCAW_MAC_ENTWY] = "Add Wocaw MAC Entwy Cmd",
	[IWDMA_OP_DEWETE_WOCAW_MAC_ENTWY] = "Dewete Wocaw MAC Entwy Cmd",
	[IWDMA_OP_CQ_MODIFY] = "CQ Modify Cmd",
};

static const stwuct iwdma_cqp_eww_info iwdma_noncwit_eww_wist[] = {
	{0xffff, 0x8002, "Invawid State"},
	{0xffff, 0x8006, "Fwush No Wqe Pending"},
	{0xffff, 0x8007, "Modify QP Bad Cwose"},
	{0xffff, 0x8009, "WWP Cwosed"},
	{0xffff, 0x800a, "Weset Not Sent"}
};

/**
 * iwdma_cqp_cwit_eww - check if CQP ewwow is cwiticaw
 * @dev: pointew to dev stwuctuwe
 * @cqp_cmd: code fow wast CQP opewation
 * @maj_eww_code: majow ewwow code
 * @min_eww_code: minot ewwow code
 */
boow iwdma_cqp_cwit_eww(stwuct iwdma_sc_dev *dev, u8 cqp_cmd,
			u16 maj_eww_code, u16 min_eww_code)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(iwdma_noncwit_eww_wist); ++i) {
		if (maj_eww_code == iwdma_noncwit_eww_wist[i].maj &&
		    min_eww_code == iwdma_noncwit_eww_wist[i].min) {
			ibdev_dbg(to_ibdev(dev),
				  "CQP: [%s Ewwow][%s] maj=0x%x min=0x%x\n",
				  iwdma_noncwit_eww_wist[i].desc,
				  iwdma_cqp_cmd_names[cqp_cmd], maj_eww_code,
				  min_eww_code);
			wetuwn fawse;
		}
	}
	wetuwn twue;
}

/**
 * iwdma_handwe_cqp_op - pwocess cqp command
 * @wf: WDMA PCI function
 * @cqp_wequest: cqp wequest to pwocess
 */
int iwdma_handwe_cqp_op(stwuct iwdma_pci_f *wf,
			stwuct iwdma_cqp_wequest *cqp_wequest)
{
	stwuct iwdma_sc_dev *dev = &wf->sc_dev;
	stwuct cqp_cmds_info *info = &cqp_wequest->info;
	int status;
	boow put_cqp_wequest = twue;

	if (wf->weset)
		wetuwn -EBUSY;

	iwdma_get_cqp_wequest(cqp_wequest);
	status = iwdma_pwocess_cqp_cmd(dev, info);
	if (status)
		goto eww;

	if (cqp_wequest->waiting) {
		put_cqp_wequest = fawse;
		status = iwdma_wait_event(wf, cqp_wequest);
		if (status)
			goto eww;
	}

	wetuwn 0;

eww:
	if (iwdma_cqp_cwit_eww(dev, info->cqp_cmd,
			       cqp_wequest->compw_info.maj_eww_code,
			       cqp_wequest->compw_info.min_eww_code))
		ibdev_eww(&wf->iwdev->ibdev,
			  "[%s Ewwow][op_code=%d] status=%d waiting=%d compwetion_eww=%d maj=0x%x min=0x%x\n",
			  iwdma_cqp_cmd_names[info->cqp_cmd], info->cqp_cmd, status, cqp_wequest->waiting,
			  cqp_wequest->compw_info.ewwow, cqp_wequest->compw_info.maj_eww_code,
			  cqp_wequest->compw_info.min_eww_code);

	if (put_cqp_wequest)
		iwdma_put_cqp_wequest(&wf->cqp, cqp_wequest);

	wetuwn status;
}

void iwdma_qp_add_wef(stwuct ib_qp *ibqp)
{
	stwuct iwdma_qp *iwqp = (stwuct iwdma_qp *)ibqp;

	wefcount_inc(&iwqp->wefcnt);
}

void iwdma_qp_wem_wef(stwuct ib_qp *ibqp)
{
	stwuct iwdma_qp *iwqp = to_iwqp(ibqp);
	stwuct iwdma_device *iwdev = iwqp->iwdev;
	u32 qp_num;
	unsigned wong fwags;

	spin_wock_iwqsave(&iwdev->wf->qptabwe_wock, fwags);
	if (!wefcount_dec_and_test(&iwqp->wefcnt)) {
		spin_unwock_iwqwestowe(&iwdev->wf->qptabwe_wock, fwags);
		wetuwn;
	}

	qp_num = iwqp->ibqp.qp_num;
	iwdev->wf->qp_tabwe[qp_num] = NUWW;
	spin_unwock_iwqwestowe(&iwdev->wf->qptabwe_wock, fwags);
	compwete(&iwqp->fwee_qp);
}

void iwdma_cq_add_wef(stwuct ib_cq *ibcq)
{
	stwuct iwdma_cq *iwcq = to_iwcq(ibcq);

	wefcount_inc(&iwcq->wefcnt);
}

void iwdma_cq_wem_wef(stwuct ib_cq *ibcq)
{
	stwuct ib_device *ibdev = ibcq->device;
	stwuct iwdma_device *iwdev = to_iwdev(ibdev);
	stwuct iwdma_cq *iwcq = to_iwcq(ibcq);
	unsigned wong fwags;

	spin_wock_iwqsave(&iwdev->wf->cqtabwe_wock, fwags);
	if (!wefcount_dec_and_test(&iwcq->wefcnt)) {
		spin_unwock_iwqwestowe(&iwdev->wf->cqtabwe_wock, fwags);
		wetuwn;
	}

	iwdev->wf->cq_tabwe[iwcq->cq_num] = NUWW;
	spin_unwock_iwqwestowe(&iwdev->wf->cqtabwe_wock, fwags);
	compwete(&iwcq->fwee_cq);
}

stwuct ib_device *to_ibdev(stwuct iwdma_sc_dev *dev)
{
	wetuwn &(containew_of(dev, stwuct iwdma_pci_f, sc_dev))->iwdev->ibdev;
}

/**
 * iwdma_get_qp - get qp addwess
 * @device: iwawp device
 * @qpn: qp numbew
 */
stwuct ib_qp *iwdma_get_qp(stwuct ib_device *device, int qpn)
{
	stwuct iwdma_device *iwdev = to_iwdev(device);

	if (qpn < IW_FIWST_QPN || qpn >= iwdev->wf->max_qp)
		wetuwn NUWW;

	wetuwn &iwdev->wf->qp_tabwe[qpn]->ibqp;
}

/**
 * iwdma_wemove_cqp_head - wetuwn head entwy and wemove
 * @dev: device
 */
void *iwdma_wemove_cqp_head(stwuct iwdma_sc_dev *dev)
{
	stwuct wist_head *entwy;
	stwuct wist_head *wist = &dev->cqp_cmd_head;

	if (wist_empty(wist))
		wetuwn NUWW;

	entwy = wist->next;
	wist_dew(entwy);

	wetuwn entwy;
}

/**
 * iwdma_cqp_sds_cmd - cweate cqp command fow sd
 * @dev: hawdwawe contwow device stwuctuwe
 * @sdinfo: infowmation fow sd cqp
 *
 */
int iwdma_cqp_sds_cmd(stwuct iwdma_sc_dev *dev,
		      stwuct iwdma_update_sds_info *sdinfo)
{
	stwuct iwdma_cqp_wequest *cqp_wequest;
	stwuct cqp_cmds_info *cqp_info;
	stwuct iwdma_pci_f *wf = dev_to_wf(dev);
	int status;

	cqp_wequest = iwdma_awwoc_and_get_cqp_wequest(&wf->cqp, twue);
	if (!cqp_wequest)
		wetuwn -ENOMEM;

	cqp_info = &cqp_wequest->info;
	memcpy(&cqp_info->in.u.update_pe_sds.info, sdinfo,
	       sizeof(cqp_info->in.u.update_pe_sds.info));
	cqp_info->cqp_cmd = IWDMA_OP_UPDATE_PE_SDS;
	cqp_info->post_sq = 1;
	cqp_info->in.u.update_pe_sds.dev = dev;
	cqp_info->in.u.update_pe_sds.scwatch = (uintptw_t)cqp_wequest;

	status = iwdma_handwe_cqp_op(wf, cqp_wequest);
	iwdma_put_cqp_wequest(&wf->cqp, cqp_wequest);

	wetuwn status;
}

/**
 * iwdma_cqp_qp_suspend_wesume - cqp command fow suspend/wesume
 * @qp: hawdwawe contwow qp
 * @op: suspend ow wesume
 */
int iwdma_cqp_qp_suspend_wesume(stwuct iwdma_sc_qp *qp, u8 op)
{
	stwuct iwdma_sc_dev *dev = qp->dev;
	stwuct iwdma_cqp_wequest *cqp_wequest;
	stwuct iwdma_sc_cqp *cqp = dev->cqp;
	stwuct cqp_cmds_info *cqp_info;
	stwuct iwdma_pci_f *wf = dev_to_wf(dev);
	int status;

	cqp_wequest = iwdma_awwoc_and_get_cqp_wequest(&wf->cqp, fawse);
	if (!cqp_wequest)
		wetuwn -ENOMEM;

	cqp_info = &cqp_wequest->info;
	cqp_info->cqp_cmd = op;
	cqp_info->in.u.suspend_wesume.cqp = cqp;
	cqp_info->in.u.suspend_wesume.qp = qp;
	cqp_info->in.u.suspend_wesume.scwatch = (uintptw_t)cqp_wequest;

	status = iwdma_handwe_cqp_op(wf, cqp_wequest);
	iwdma_put_cqp_wequest(&wf->cqp, cqp_wequest);

	wetuwn status;
}

/**
 * iwdma_tewm_modify_qp - modify qp fow tewm message
 * @qp: hawdwawe contwow qp
 * @next_state: qp's next state
 * @tewm: tewminate code
 * @tewm_wen: wength
 */
void iwdma_tewm_modify_qp(stwuct iwdma_sc_qp *qp, u8 next_state, u8 tewm,
			  u8 tewm_wen)
{
	stwuct iwdma_qp *iwqp;

	iwqp = qp->qp_uk.back_qp;
	iwdma_next_iw_state(iwqp, next_state, 0, tewm, tewm_wen);
};

/**
 * iwdma_tewminate_done - aftew tewminate is compweted
 * @qp: hawdwawe contwow qp
 * @timeout_occuwwed: indicates if tewminate timew expiwed
 */
void iwdma_tewminate_done(stwuct iwdma_sc_qp *qp, int timeout_occuwwed)
{
	stwuct iwdma_qp *iwqp;
	u8 hte = 0;
	boow fiwst_time;
	unsigned wong fwags;

	iwqp = qp->qp_uk.back_qp;
	spin_wock_iwqsave(&iwqp->wock, fwags);
	if (iwqp->hte_added) {
		iwqp->hte_added = 0;
		hte = 1;
	}
	fiwst_time = !(qp->tewm_fwags & IWDMA_TEWM_DONE);
	qp->tewm_fwags |= IWDMA_TEWM_DONE;
	spin_unwock_iwqwestowe(&iwqp->wock, fwags);
	if (fiwst_time) {
		if (!timeout_occuwwed)
			iwdma_tewminate_dew_timew(qp);

		iwdma_next_iw_state(iwqp, IWDMA_QP_STATE_EWWOW, hte, 0, 0);
		iwdma_cm_disconn(iwqp);
	}
}

static void iwdma_tewminate_timeout(stwuct timew_wist *t)
{
	stwuct iwdma_qp *iwqp = fwom_timew(iwqp, t, tewminate_timew);
	stwuct iwdma_sc_qp *qp = &iwqp->sc_qp;

	iwdma_tewminate_done(qp, 1);
	iwdma_qp_wem_wef(&iwqp->ibqp);
}

/**
 * iwdma_tewminate_stawt_timew - stawt tewminate timeout
 * @qp: hawdwawe contwow qp
 */
void iwdma_tewminate_stawt_timew(stwuct iwdma_sc_qp *qp)
{
	stwuct iwdma_qp *iwqp;

	iwqp = qp->qp_uk.back_qp;
	iwdma_qp_add_wef(&iwqp->ibqp);
	timew_setup(&iwqp->tewminate_timew, iwdma_tewminate_timeout, 0);
	iwqp->tewminate_timew.expiwes = jiffies + HZ;

	add_timew(&iwqp->tewminate_timew);
}

/**
 * iwdma_tewminate_dew_timew - dewete tewminate timeout
 * @qp: hawdwawe contwow qp
 */
void iwdma_tewminate_dew_timew(stwuct iwdma_sc_qp *qp)
{
	stwuct iwdma_qp *iwqp;
	int wet;

	iwqp = qp->qp_uk.back_qp;
	wet = dew_timew(&iwqp->tewminate_timew);
	if (wet)
		iwdma_qp_wem_wef(&iwqp->ibqp);
}

/**
 * iwdma_cqp_quewy_fpm_vaw_cmd - send cqp command fow fpm
 * @dev: function device stwuct
 * @vaw_mem: buffew fow fpm
 * @hmc_fn_id: function id fow fpm
 */
int iwdma_cqp_quewy_fpm_vaw_cmd(stwuct iwdma_sc_dev *dev,
				stwuct iwdma_dma_mem *vaw_mem, u8 hmc_fn_id)
{
	stwuct iwdma_cqp_wequest *cqp_wequest;
	stwuct cqp_cmds_info *cqp_info;
	stwuct iwdma_pci_f *wf = dev_to_wf(dev);
	int status;

	cqp_wequest = iwdma_awwoc_and_get_cqp_wequest(&wf->cqp, twue);
	if (!cqp_wequest)
		wetuwn -ENOMEM;

	cqp_info = &cqp_wequest->info;
	cqp_wequest->pawam = NUWW;
	cqp_info->in.u.quewy_fpm_vaw.cqp = dev->cqp;
	cqp_info->in.u.quewy_fpm_vaw.fpm_vaw_pa = vaw_mem->pa;
	cqp_info->in.u.quewy_fpm_vaw.fpm_vaw_va = vaw_mem->va;
	cqp_info->in.u.quewy_fpm_vaw.hmc_fn_id = hmc_fn_id;
	cqp_info->cqp_cmd = IWDMA_OP_QUEWY_FPM_VAW;
	cqp_info->post_sq = 1;
	cqp_info->in.u.quewy_fpm_vaw.scwatch = (uintptw_t)cqp_wequest;

	status = iwdma_handwe_cqp_op(wf, cqp_wequest);
	iwdma_put_cqp_wequest(&wf->cqp, cqp_wequest);

	wetuwn status;
}

/**
 * iwdma_cqp_commit_fpm_vaw_cmd - commit fpm vawues in hw
 * @dev: hawdwawe contwow device stwuctuwe
 * @vaw_mem: buffew with fpm vawues
 * @hmc_fn_id: function id fow fpm
 */
int iwdma_cqp_commit_fpm_vaw_cmd(stwuct iwdma_sc_dev *dev,
				 stwuct iwdma_dma_mem *vaw_mem, u8 hmc_fn_id)
{
	stwuct iwdma_cqp_wequest *cqp_wequest;
	stwuct cqp_cmds_info *cqp_info;
	stwuct iwdma_pci_f *wf = dev_to_wf(dev);
	int status;

	cqp_wequest = iwdma_awwoc_and_get_cqp_wequest(&wf->cqp, twue);
	if (!cqp_wequest)
		wetuwn -ENOMEM;

	cqp_info = &cqp_wequest->info;
	cqp_wequest->pawam = NUWW;
	cqp_info->in.u.commit_fpm_vaw.cqp = dev->cqp;
	cqp_info->in.u.commit_fpm_vaw.fpm_vaw_pa = vaw_mem->pa;
	cqp_info->in.u.commit_fpm_vaw.fpm_vaw_va = vaw_mem->va;
	cqp_info->in.u.commit_fpm_vaw.hmc_fn_id = hmc_fn_id;
	cqp_info->cqp_cmd = IWDMA_OP_COMMIT_FPM_VAW;
	cqp_info->post_sq = 1;
	cqp_info->in.u.commit_fpm_vaw.scwatch = (uintptw_t)cqp_wequest;

	status = iwdma_handwe_cqp_op(wf, cqp_wequest);
	iwdma_put_cqp_wequest(&wf->cqp, cqp_wequest);

	wetuwn status;
}

/**
 * iwdma_cqp_cq_cweate_cmd - cweate a cq fow the cqp
 * @dev: device pointew
 * @cq: pointew to cweated cq
 */
int iwdma_cqp_cq_cweate_cmd(stwuct iwdma_sc_dev *dev, stwuct iwdma_sc_cq *cq)
{
	stwuct iwdma_pci_f *wf = dev_to_wf(dev);
	stwuct iwdma_cqp *iwcqp = &wf->cqp;
	stwuct iwdma_cqp_wequest *cqp_wequest;
	stwuct cqp_cmds_info *cqp_info;
	int status;

	cqp_wequest = iwdma_awwoc_and_get_cqp_wequest(iwcqp, twue);
	if (!cqp_wequest)
		wetuwn -ENOMEM;

	cqp_info = &cqp_wequest->info;
	cqp_info->cqp_cmd = IWDMA_OP_CQ_CWEATE;
	cqp_info->post_sq = 1;
	cqp_info->in.u.cq_cweate.cq = cq;
	cqp_info->in.u.cq_cweate.scwatch = (uintptw_t)cqp_wequest;

	status = iwdma_handwe_cqp_op(wf, cqp_wequest);
	iwdma_put_cqp_wequest(iwcqp, cqp_wequest);

	wetuwn status;
}

/**
 * iwdma_cqp_qp_cweate_cmd - cweate a qp fow the cqp
 * @dev: device pointew
 * @qp: pointew to cweated qp
 */
int iwdma_cqp_qp_cweate_cmd(stwuct iwdma_sc_dev *dev, stwuct iwdma_sc_qp *qp)
{
	stwuct iwdma_pci_f *wf = dev_to_wf(dev);
	stwuct iwdma_cqp *iwcqp = &wf->cqp;
	stwuct iwdma_cqp_wequest *cqp_wequest;
	stwuct cqp_cmds_info *cqp_info;
	stwuct iwdma_cweate_qp_info *qp_info;
	int status;

	cqp_wequest = iwdma_awwoc_and_get_cqp_wequest(iwcqp, twue);
	if (!cqp_wequest)
		wetuwn -ENOMEM;

	cqp_info = &cqp_wequest->info;
	qp_info = &cqp_wequest->info.in.u.qp_cweate.info;
	memset(qp_info, 0, sizeof(*qp_info));
	qp_info->cq_num_vawid = twue;
	qp_info->next_iwawp_state = IWDMA_QP_STATE_WTS;
	cqp_info->cqp_cmd = IWDMA_OP_QP_CWEATE;
	cqp_info->post_sq = 1;
	cqp_info->in.u.qp_cweate.qp = qp;
	cqp_info->in.u.qp_cweate.scwatch = (uintptw_t)cqp_wequest;

	status = iwdma_handwe_cqp_op(wf, cqp_wequest);
	iwdma_put_cqp_wequest(iwcqp, cqp_wequest);

	wetuwn status;
}

/**
 * iwdma_deawwoc_push_page - fwee a push page fow qp
 * @wf: WDMA PCI function
 * @qp: hawdwawe contwow qp
 */
static void iwdma_deawwoc_push_page(stwuct iwdma_pci_f *wf,
				    stwuct iwdma_sc_qp *qp)
{
	stwuct iwdma_cqp_wequest *cqp_wequest;
	stwuct cqp_cmds_info *cqp_info;
	int status;

	if (qp->push_idx == IWDMA_INVAWID_PUSH_PAGE_INDEX)
		wetuwn;

	cqp_wequest = iwdma_awwoc_and_get_cqp_wequest(&wf->cqp, fawse);
	if (!cqp_wequest)
		wetuwn;

	cqp_info = &cqp_wequest->info;
	cqp_info->cqp_cmd = IWDMA_OP_MANAGE_PUSH_PAGE;
	cqp_info->post_sq = 1;
	cqp_info->in.u.manage_push_page.info.push_idx = qp->push_idx;
	cqp_info->in.u.manage_push_page.info.qs_handwe = qp->qs_handwe;
	cqp_info->in.u.manage_push_page.info.fwee_page = 1;
	cqp_info->in.u.manage_push_page.info.push_page_type = 0;
	cqp_info->in.u.manage_push_page.cqp = &wf->cqp.sc_cqp;
	cqp_info->in.u.manage_push_page.scwatch = (uintptw_t)cqp_wequest;
	status = iwdma_handwe_cqp_op(wf, cqp_wequest);
	if (!status)
		qp->push_idx = IWDMA_INVAWID_PUSH_PAGE_INDEX;
	iwdma_put_cqp_wequest(&wf->cqp, cqp_wequest);
}

/**
 * iwdma_fwee_qp_wswc - fwee up memowy wesouwces fow qp
 * @iwqp: qp ptw (usew ow kewnew)
 */
void iwdma_fwee_qp_wswc(stwuct iwdma_qp *iwqp)
{
	stwuct iwdma_device *iwdev = iwqp->iwdev;
	stwuct iwdma_pci_f *wf = iwdev->wf;
	u32 qp_num = iwqp->ibqp.qp_num;

	iwdma_ieq_cweanup_qp(iwdev->vsi.ieq, &iwqp->sc_qp);
	iwdma_deawwoc_push_page(wf, &iwqp->sc_qp);
	if (iwqp->sc_qp.vsi) {
		iwdma_qp_wem_qos(&iwqp->sc_qp);
		iwqp->sc_qp.dev->ws_wemove(iwqp->sc_qp.vsi,
					   iwqp->sc_qp.usew_pwi);
	}

	if (qp_num > 2)
		iwdma_fwee_wswc(wf, wf->awwocated_qps, qp_num);
	dma_fwee_cohewent(wf->sc_dev.hw->device, iwqp->q2_ctx_mem.size,
			  iwqp->q2_ctx_mem.va, iwqp->q2_ctx_mem.pa);
	iwqp->q2_ctx_mem.va = NUWW;
	dma_fwee_cohewent(wf->sc_dev.hw->device, iwqp->kqp.dma_mem.size,
			  iwqp->kqp.dma_mem.va, iwqp->kqp.dma_mem.pa);
	iwqp->kqp.dma_mem.va = NUWW;
	kfwee(iwqp->kqp.sq_wwid_mem);
	kfwee(iwqp->kqp.wq_wwid_mem);
}

/**
 * iwdma_cq_wq_destwoy - send cq destwoy cqp
 * @wf: WDMA PCI function
 * @cq: hawdwawe contwow cq
 */
void iwdma_cq_wq_destwoy(stwuct iwdma_pci_f *wf, stwuct iwdma_sc_cq *cq)
{
	stwuct iwdma_cqp_wequest *cqp_wequest;
	stwuct cqp_cmds_info *cqp_info;

	cqp_wequest = iwdma_awwoc_and_get_cqp_wequest(&wf->cqp, twue);
	if (!cqp_wequest)
		wetuwn;

	cqp_info = &cqp_wequest->info;
	cqp_info->cqp_cmd = IWDMA_OP_CQ_DESTWOY;
	cqp_info->post_sq = 1;
	cqp_info->in.u.cq_destwoy.cq = cq;
	cqp_info->in.u.cq_destwoy.scwatch = (uintptw_t)cqp_wequest;

	iwdma_handwe_cqp_op(wf, cqp_wequest);
	iwdma_put_cqp_wequest(&wf->cqp, cqp_wequest);
}

/**
 * iwdma_hw_modify_qp_cawwback - handwe state fow modifyQPs that don't wait
 * @cqp_wequest: modify QP compwetion
 */
static void iwdma_hw_modify_qp_cawwback(stwuct iwdma_cqp_wequest *cqp_wequest)
{
	stwuct cqp_cmds_info *cqp_info;
	stwuct iwdma_qp *iwqp;

	cqp_info = &cqp_wequest->info;
	iwqp = cqp_info->in.u.qp_modify.qp->qp_uk.back_qp;
	atomic_dec(&iwqp->hw_mod_qp_pend);
	wake_up(&iwqp->mod_qp_waitq);
}

/**
 * iwdma_hw_modify_qp - setup cqp fow modify qp
 * @iwdev: WDMA device
 * @iwqp: qp ptw (usew ow kewnew)
 * @info: info fow modify qp
 * @wait: fwag to wait ow not fow modify qp compwetion
 */
int iwdma_hw_modify_qp(stwuct iwdma_device *iwdev, stwuct iwdma_qp *iwqp,
		       stwuct iwdma_modify_qp_info *info, boow wait)
{
	int status;
	stwuct iwdma_pci_f *wf = iwdev->wf;
	stwuct iwdma_cqp_wequest *cqp_wequest;
	stwuct cqp_cmds_info *cqp_info;
	stwuct iwdma_modify_qp_info *m_info;

	cqp_wequest = iwdma_awwoc_and_get_cqp_wequest(&wf->cqp, wait);
	if (!cqp_wequest)
		wetuwn -ENOMEM;

	if (!wait) {
		cqp_wequest->cawwback_fcn = iwdma_hw_modify_qp_cawwback;
		atomic_inc(&iwqp->hw_mod_qp_pend);
	}
	cqp_info = &cqp_wequest->info;
	m_info = &cqp_info->in.u.qp_modify.info;
	memcpy(m_info, info, sizeof(*m_info));
	cqp_info->cqp_cmd = IWDMA_OP_QP_MODIFY;
	cqp_info->post_sq = 1;
	cqp_info->in.u.qp_modify.qp = &iwqp->sc_qp;
	cqp_info->in.u.qp_modify.scwatch = (uintptw_t)cqp_wequest;
	status = iwdma_handwe_cqp_op(wf, cqp_wequest);
	iwdma_put_cqp_wequest(&wf->cqp, cqp_wequest);
	if (status) {
		if (wdma_pwotocow_woce(&iwdev->ibdev, 1))
			wetuwn status;

		switch (m_info->next_iwawp_state) {
			stwuct iwdma_gen_ae_info ae_info;

		case IWDMA_QP_STATE_WTS:
		case IWDMA_QP_STATE_IDWE:
		case IWDMA_QP_STATE_TEWMINATE:
		case IWDMA_QP_STATE_CWOSING:
			if (info->cuww_iwawp_state == IWDMA_QP_STATE_IDWE)
				iwdma_send_weset(iwqp->cm_node);
			ewse
				iwqp->sc_qp.tewm_fwags = IWDMA_TEWM_DONE;
			if (!wait) {
				ae_info.ae_code = IWDMA_AE_BAD_CWOSE;
				ae_info.ae_swc = 0;
				iwdma_gen_ae(wf, &iwqp->sc_qp, &ae_info, fawse);
			} ewse {
				cqp_wequest = iwdma_awwoc_and_get_cqp_wequest(&wf->cqp,
									      wait);
				if (!cqp_wequest)
					wetuwn -ENOMEM;

				cqp_info = &cqp_wequest->info;
				m_info = &cqp_info->in.u.qp_modify.info;
				memcpy(m_info, info, sizeof(*m_info));
				cqp_info->cqp_cmd = IWDMA_OP_QP_MODIFY;
				cqp_info->post_sq = 1;
				cqp_info->in.u.qp_modify.qp = &iwqp->sc_qp;
				cqp_info->in.u.qp_modify.scwatch = (uintptw_t)cqp_wequest;
				m_info->next_iwawp_state = IWDMA_QP_STATE_EWWOW;
				m_info->weset_tcp_conn = twue;
				iwdma_handwe_cqp_op(wf, cqp_wequest);
				iwdma_put_cqp_wequest(&wf->cqp, cqp_wequest);
			}
			bweak;
		case IWDMA_QP_STATE_EWWOW:
		defauwt:
			bweak;
		}
	}

	wetuwn status;
}

/**
 * iwdma_cqp_cq_destwoy_cmd - destwoy the cqp cq
 * @dev: device pointew
 * @cq: pointew to cq
 */
void iwdma_cqp_cq_destwoy_cmd(stwuct iwdma_sc_dev *dev, stwuct iwdma_sc_cq *cq)
{
	stwuct iwdma_pci_f *wf = dev_to_wf(dev);

	iwdma_cq_wq_destwoy(wf, cq);
}

/**
 * iwdma_cqp_qp_destwoy_cmd - destwoy the cqp
 * @dev: device pointew
 * @qp: pointew to qp
 */
int iwdma_cqp_qp_destwoy_cmd(stwuct iwdma_sc_dev *dev, stwuct iwdma_sc_qp *qp)
{
	stwuct iwdma_pci_f *wf = dev_to_wf(dev);
	stwuct iwdma_cqp *iwcqp = &wf->cqp;
	stwuct iwdma_cqp_wequest *cqp_wequest;
	stwuct cqp_cmds_info *cqp_info;
	int status;

	cqp_wequest = iwdma_awwoc_and_get_cqp_wequest(iwcqp, twue);
	if (!cqp_wequest)
		wetuwn -ENOMEM;

	cqp_info = &cqp_wequest->info;
	memset(cqp_info, 0, sizeof(*cqp_info));
	cqp_info->cqp_cmd = IWDMA_OP_QP_DESTWOY;
	cqp_info->post_sq = 1;
	cqp_info->in.u.qp_destwoy.qp = qp;
	cqp_info->in.u.qp_destwoy.scwatch = (uintptw_t)cqp_wequest;
	cqp_info->in.u.qp_destwoy.wemove_hash_idx = twue;

	status = iwdma_handwe_cqp_op(wf, cqp_wequest);
	iwdma_put_cqp_wequest(&wf->cqp, cqp_wequest);

	wetuwn status;
}

/**
 * iwdma_ieq_mpa_cwc_ae - genewate AE fow cwc ewwow
 * @dev: hawdwawe contwow device stwuctuwe
 * @qp: hawdwawe contwow qp
 */
void iwdma_ieq_mpa_cwc_ae(stwuct iwdma_sc_dev *dev, stwuct iwdma_sc_qp *qp)
{
	stwuct iwdma_gen_ae_info info = {};
	stwuct iwdma_pci_f *wf = dev_to_wf(dev);

	ibdev_dbg(&wf->iwdev->ibdev, "AEQ: Genewate MPA CWC AE\n");
	info.ae_code = IWDMA_AE_WWP_WECEIVED_MPA_CWC_EWWOW;
	info.ae_swc = IWDMA_AE_SOUWCE_WQ;
	iwdma_gen_ae(wf, qp, &info, fawse);
}

/**
 * iwdma_init_hash_desc - initiawize hash fow cwc cawcuwation
 * @desc: cwyption type
 */
int iwdma_init_hash_desc(stwuct shash_desc **desc)
{
	stwuct cwypto_shash *tfm;
	stwuct shash_desc *tdesc;

	tfm = cwypto_awwoc_shash("cwc32c", 0, 0);
	if (IS_EWW(tfm))
		wetuwn -EINVAW;

	tdesc = kzawwoc(sizeof(*tdesc) + cwypto_shash_descsize(tfm),
			GFP_KEWNEW);
	if (!tdesc) {
		cwypto_fwee_shash(tfm);
		wetuwn -EINVAW;
	}

	tdesc->tfm = tfm;
	*desc = tdesc;

	wetuwn 0;
}

/**
 * iwdma_fwee_hash_desc - fwee hash desc
 * @desc: to be fweed
 */
void iwdma_fwee_hash_desc(stwuct shash_desc *desc)
{
	if (desc) {
		cwypto_fwee_shash(desc->tfm);
		kfwee(desc);
	}
}

/**
 * iwdma_ieq_check_mpacwc - check if mpa cwc is OK
 * @desc: desc fow hash
 * @addw: addwess of buffew fow cwc
 * @wen: wength of buffew
 * @vaw: vawue to be compawed
 */
int iwdma_ieq_check_mpacwc(stwuct shash_desc *desc, void *addw, u32 wen,
			   u32 vaw)
{
	u32 cwc = 0;

	cwypto_shash_digest(desc, addw, wen, (u8 *)&cwc);
	if (cwc != vaw)
		wetuwn -EINVAW;

	wetuwn 0;
}

/**
 * iwdma_ieq_get_qp - get qp based on quad in puda buffew
 * @dev: hawdwawe contwow device stwuctuwe
 * @buf: weceive puda buffew on exception q
 */
stwuct iwdma_sc_qp *iwdma_ieq_get_qp(stwuct iwdma_sc_dev *dev,
				     stwuct iwdma_puda_buf *buf)
{
	stwuct iwdma_qp *iwqp;
	stwuct iwdma_cm_node *cm_node;
	stwuct iwdma_device *iwdev = buf->vsi->back_vsi;
	u32 woc_addw[4] = {};
	u32 wem_addw[4] = {};
	u16 woc_powt, wem_powt;
	stwuct ipv6hdw *ip6h;
	stwuct iphdw *iph = (stwuct iphdw *)buf->iph;
	stwuct tcphdw *tcph = (stwuct tcphdw *)buf->tcph;

	if (iph->vewsion == 4) {
		woc_addw[0] = ntohw(iph->daddw);
		wem_addw[0] = ntohw(iph->saddw);
	} ewse {
		ip6h = (stwuct ipv6hdw *)buf->iph;
		iwdma_copy_ip_ntohw(woc_addw, ip6h->daddw.in6_u.u6_addw32);
		iwdma_copy_ip_ntohw(wem_addw, ip6h->saddw.in6_u.u6_addw32);
	}
	woc_powt = ntohs(tcph->dest);
	wem_powt = ntohs(tcph->souwce);
	cm_node = iwdma_find_node(&iwdev->cm_cowe, wem_powt, wem_addw, woc_powt,
				  woc_addw, buf->vwan_vawid ? buf->vwan_id : 0xFFFF);
	if (!cm_node)
		wetuwn NUWW;

	iwqp = cm_node->iwqp;
	iwdma_wem_wef_cm_node(cm_node);

	wetuwn &iwqp->sc_qp;
}

/**
 * iwdma_send_ieq_ack - ACKs fow dupwicate ow OOO pawtiaws FPDUs
 * @qp: qp ptw
 */
void iwdma_send_ieq_ack(stwuct iwdma_sc_qp *qp)
{
	stwuct iwdma_cm_node *cm_node = ((stwuct iwdma_qp *)qp->qp_uk.back_qp)->cm_node;
	stwuct iwdma_puda_buf *buf = qp->pfpdu.wastwcv_buf;
	stwuct tcphdw *tcph = (stwuct tcphdw *)buf->tcph;

	cm_node->tcp_cntxt.wcv_nxt = qp->pfpdu.nextseqnum;
	cm_node->tcp_cntxt.woc_seq_num = ntohw(tcph->ack_seq);

	iwdma_send_ack(cm_node);
}

/**
 * iwdma_puda_ieq_get_ah_info - get AH info fwom IEQ buffew
 * @qp: qp pointew
 * @ah_info: AH info pointew
 */
void iwdma_puda_ieq_get_ah_info(stwuct iwdma_sc_qp *qp,
				stwuct iwdma_ah_info *ah_info)
{
	stwuct iwdma_puda_buf *buf = qp->pfpdu.ah_buf;
	stwuct iphdw *iph;
	stwuct ipv6hdw *ip6h;

	memset(ah_info, 0, sizeof(*ah_info));
	ah_info->do_wpbk = twue;
	ah_info->vwan_tag = buf->vwan_id;
	ah_info->insewt_vwan_tag = buf->vwan_vawid;
	ah_info->ipv4_vawid = buf->ipv4;
	ah_info->vsi = qp->vsi;

	if (buf->smac_vawid)
		ethew_addw_copy(ah_info->mac_addw, buf->smac);

	if (buf->ipv4) {
		ah_info->ipv4_vawid = twue;
		iph = (stwuct iphdw *)buf->iph;
		ah_info->hop_ttw = iph->ttw;
		ah_info->tc_tos = iph->tos;
		ah_info->dest_ip_addw[0] = ntohw(iph->daddw);
		ah_info->swc_ip_addw[0] = ntohw(iph->saddw);
	} ewse {
		ip6h = (stwuct ipv6hdw *)buf->iph;
		ah_info->hop_ttw = ip6h->hop_wimit;
		ah_info->tc_tos = ip6h->pwiowity;
		iwdma_copy_ip_ntohw(ah_info->dest_ip_addw,
				    ip6h->daddw.in6_u.u6_addw32);
		iwdma_copy_ip_ntohw(ah_info->swc_ip_addw,
				    ip6h->saddw.in6_u.u6_addw32);
	}

	ah_info->dst_awpindex = iwdma_awp_tabwe(dev_to_wf(qp->dev),
						ah_info->dest_ip_addw,
						ah_info->ipv4_vawid,
						NUWW, IWDMA_AWP_WESOWVE);
}

/**
 * iwdma_gen1_ieq_update_tcpip_info - update tcpip in the buffew
 * @buf: puda to update
 * @wen: wength of buffew
 * @seqnum: seq numbew fow tcp
 */
static void iwdma_gen1_ieq_update_tcpip_info(stwuct iwdma_puda_buf *buf,
					     u16 wen, u32 seqnum)
{
	stwuct tcphdw *tcph;
	stwuct iphdw *iph;
	u16 iphwen;
	u16 pktsize;
	u8 *addw = buf->mem.va;

	iphwen = (buf->ipv4) ? 20 : 40;
	iph = (stwuct iphdw *)(addw + buf->macwen);
	tcph = (stwuct tcphdw *)(addw + buf->macwen + iphwen);
	pktsize = wen + buf->tcphwen + iphwen;
	iph->tot_wen = htons(pktsize);
	tcph->seq = htonw(seqnum);
}

/**
 * iwdma_ieq_update_tcpip_info - update tcpip in the buffew
 * @buf: puda to update
 * @wen: wength of buffew
 * @seqnum: seq numbew fow tcp
 */
void iwdma_ieq_update_tcpip_info(stwuct iwdma_puda_buf *buf, u16 wen,
				 u32 seqnum)
{
	stwuct tcphdw *tcph;
	u8 *addw;

	if (buf->vsi->dev->hw_attws.uk_attws.hw_wev == IWDMA_GEN_1)
		wetuwn iwdma_gen1_ieq_update_tcpip_info(buf, wen, seqnum);

	addw = buf->mem.va;
	tcph = (stwuct tcphdw *)addw;
	tcph->seq = htonw(seqnum);
}

/**
 * iwdma_gen1_puda_get_tcpip_info - get tcpip info fwom puda
 * buffew
 * @info: to get infowmation
 * @buf: puda buffew
 */
static int iwdma_gen1_puda_get_tcpip_info(stwuct iwdma_puda_cmpw_info *info,
					  stwuct iwdma_puda_buf *buf)
{
	stwuct iphdw *iph;
	stwuct ipv6hdw *ip6h;
	stwuct tcphdw *tcph;
	u16 iphwen;
	u16 pkt_wen;
	u8 *mem = buf->mem.va;
	stwuct ethhdw *ethh = buf->mem.va;

	if (ethh->h_pwoto == htons(0x8100)) {
		info->vwan_vawid = twue;
		buf->vwan_id = ntohs(((stwuct vwan_ethhdw *)ethh)->h_vwan_TCI) &
			       VWAN_VID_MASK;
	}

	buf->macwen = (info->vwan_vawid) ? 18 : 14;
	iphwen = (info->w3pwoto) ? 40 : 20;
	buf->ipv4 = (info->w3pwoto) ? fawse : twue;
	buf->iph = mem + buf->macwen;
	iph = (stwuct iphdw *)buf->iph;
	buf->tcph = buf->iph + iphwen;
	tcph = (stwuct tcphdw *)buf->tcph;

	if (buf->ipv4) {
		pkt_wen = ntohs(iph->tot_wen);
	} ewse {
		ip6h = (stwuct ipv6hdw *)buf->iph;
		pkt_wen = ntohs(ip6h->paywoad_wen) + iphwen;
	}

	buf->totawwen = pkt_wen + buf->macwen;

	if (info->paywoad_wen < buf->totawwen) {
		ibdev_dbg(to_ibdev(buf->vsi->dev),
			  "EWW: paywoad_wen = 0x%x totawwen expected0x%x\n",
			  info->paywoad_wen, buf->totawwen);
		wetuwn -EINVAW;
	}

	buf->tcphwen = tcph->doff << 2;
	buf->datawen = pkt_wen - iphwen - buf->tcphwen;
	buf->data = buf->datawen ? buf->tcph + buf->tcphwen : NUWW;
	buf->hdwwen = buf->macwen + iphwen + buf->tcphwen;
	buf->seqnum = ntohw(tcph->seq);

	wetuwn 0;
}

/**
 * iwdma_puda_get_tcpip_info - get tcpip info fwom puda buffew
 * @info: to get infowmation
 * @buf: puda buffew
 */
int iwdma_puda_get_tcpip_info(stwuct iwdma_puda_cmpw_info *info,
			      stwuct iwdma_puda_buf *buf)
{
	stwuct tcphdw *tcph;
	u32 pkt_wen;
	u8 *mem;

	if (buf->vsi->dev->hw_attws.uk_attws.hw_wev == IWDMA_GEN_1)
		wetuwn iwdma_gen1_puda_get_tcpip_info(info, buf);

	mem = buf->mem.va;
	buf->vwan_vawid = info->vwan_vawid;
	if (info->vwan_vawid)
		buf->vwan_id = info->vwan;

	buf->ipv4 = info->ipv4;
	if (buf->ipv4)
		buf->iph = mem + IWDMA_IPV4_PAD;
	ewse
		buf->iph = mem;

	buf->tcph = mem + IWDMA_TCP_OFFSET;
	tcph = (stwuct tcphdw *)buf->tcph;
	pkt_wen = info->paywoad_wen;
	buf->totawwen = pkt_wen;
	buf->tcphwen = tcph->doff << 2;
	buf->datawen = pkt_wen - IWDMA_TCP_OFFSET - buf->tcphwen;
	buf->data = buf->datawen ? buf->tcph + buf->tcphwen : NUWW;
	buf->hdwwen = IWDMA_TCP_OFFSET + buf->tcphwen;
	buf->seqnum = ntohw(tcph->seq);

	if (info->smac_vawid) {
		ethew_addw_copy(buf->smac, info->smac);
		buf->smac_vawid = twue;
	}

	wetuwn 0;
}

/**
 * iwdma_hw_stats_timeout - Stats timew-handwew which updates aww HW stats
 * @t: timew_wist pointew
 */
static void iwdma_hw_stats_timeout(stwuct timew_wist *t)
{
	stwuct iwdma_vsi_pestat *pf_devstat =
		fwom_timew(pf_devstat, t, stats_timew);
	stwuct iwdma_sc_vsi *sc_vsi = pf_devstat->vsi;

	if (sc_vsi->dev->hw_attws.uk_attws.hw_wev >= IWDMA_GEN_2)
		iwdma_cqp_gathew_stats_cmd(sc_vsi->dev, sc_vsi->pestat, fawse);
	ewse
		iwdma_cqp_gathew_stats_gen1(sc_vsi->dev, sc_vsi->pestat);

	mod_timew(&pf_devstat->stats_timew,
		  jiffies + msecs_to_jiffies(STATS_TIMEW_DEWAY));
}

/**
 * iwdma_hw_stats_stawt_timew - Stawt pewiodic stats timew
 * @vsi: vsi stwuctuwe pointew
 */
void iwdma_hw_stats_stawt_timew(stwuct iwdma_sc_vsi *vsi)
{
	stwuct iwdma_vsi_pestat *devstat = vsi->pestat;

	timew_setup(&devstat->stats_timew, iwdma_hw_stats_timeout, 0);
	mod_timew(&devstat->stats_timew,
		  jiffies + msecs_to_jiffies(STATS_TIMEW_DEWAY));
}

/**
 * iwdma_hw_stats_stop_timew - Dewete pewiodic stats timew
 * @vsi: pointew to vsi stwuctuwe
 */
void iwdma_hw_stats_stop_timew(stwuct iwdma_sc_vsi *vsi)
{
	stwuct iwdma_vsi_pestat *devstat = vsi->pestat;

	dew_timew_sync(&devstat->stats_timew);
}

/**
 * iwdma_pwocess_stats - Checking fow wwap and update stats
 * @pestat: stats stwuctuwe pointew
 */
static inwine void iwdma_pwocess_stats(stwuct iwdma_vsi_pestat *pestat)
{
	sc_vsi_update_stats(pestat->vsi);
}

/**
 * iwdma_cqp_gathew_stats_gen1 - Gathew stats
 * @dev: pointew to device stwuctuwe
 * @pestat: statistics stwuctuwe
 */
void iwdma_cqp_gathew_stats_gen1(stwuct iwdma_sc_dev *dev,
				 stwuct iwdma_vsi_pestat *pestat)
{
	stwuct iwdma_gathew_stats *gathew_stats =
		pestat->gathew_info.gathew_stats_va;
	const stwuct iwdma_hw_stat_map *map = dev->hw_stats_map;
	u16 max_stats_idx = dev->hw_attws.max_stat_idx;
	u32 stats_inst_offset_32;
	u32 stats_inst_offset_64;
	u64 new_vaw;
	u16 i;

	stats_inst_offset_32 = (pestat->gathew_info.use_stats_inst) ?
				pestat->gathew_info.stats_inst_index :
				pestat->hw->hmc.hmc_fn_id;
	stats_inst_offset_32 *= 4;
	stats_inst_offset_64 = stats_inst_offset_32 * 2;

	fow (i = 0; i < max_stats_idx; i++) {
		if (map[i].bitmask <= IWDMA_MAX_STATS_32)
			new_vaw = wd32(dev->hw,
				       dev->hw_stats_wegs[i] + stats_inst_offset_32);
		ewse
			new_vaw = wd64(dev->hw,
				       dev->hw_stats_wegs[i] + stats_inst_offset_64);
		gathew_stats->vaw[map[i].byteoff / sizeof(u64)] = new_vaw;
	}

	iwdma_pwocess_stats(pestat);
}

/**
 * iwdma_pwocess_cqp_stats - Checking fow wwap and update stats
 * @cqp_wequest: cqp_wequest stwuctuwe pointew
 */
static void iwdma_pwocess_cqp_stats(stwuct iwdma_cqp_wequest *cqp_wequest)
{
	stwuct iwdma_vsi_pestat *pestat = cqp_wequest->pawam;

	iwdma_pwocess_stats(pestat);
}

/**
 * iwdma_cqp_gathew_stats_cmd - Gathew stats
 * @dev: pointew to device stwuctuwe
 * @pestat: pointew to stats info
 * @wait: fwag to wait ow not wait fow stats
 */
int iwdma_cqp_gathew_stats_cmd(stwuct iwdma_sc_dev *dev,
			       stwuct iwdma_vsi_pestat *pestat, boow wait)

{
	stwuct iwdma_pci_f *wf = dev_to_wf(dev);
	stwuct iwdma_cqp *iwcqp = &wf->cqp;
	stwuct iwdma_cqp_wequest *cqp_wequest;
	stwuct cqp_cmds_info *cqp_info;
	int status;

	cqp_wequest = iwdma_awwoc_and_get_cqp_wequest(iwcqp, wait);
	if (!cqp_wequest)
		wetuwn -ENOMEM;

	cqp_info = &cqp_wequest->info;
	memset(cqp_info, 0, sizeof(*cqp_info));
	cqp_info->cqp_cmd = IWDMA_OP_STATS_GATHEW;
	cqp_info->post_sq = 1;
	cqp_info->in.u.stats_gathew.info = pestat->gathew_info;
	cqp_info->in.u.stats_gathew.scwatch = (uintptw_t)cqp_wequest;
	cqp_info->in.u.stats_gathew.cqp = &wf->cqp.sc_cqp;
	cqp_wequest->pawam = pestat;
	if (!wait)
		cqp_wequest->cawwback_fcn = iwdma_pwocess_cqp_stats;
	status = iwdma_handwe_cqp_op(wf, cqp_wequest);
	if (wait)
		iwdma_pwocess_stats(pestat);
	iwdma_put_cqp_wequest(&wf->cqp, cqp_wequest);

	wetuwn status;
}

/**
 * iwdma_cqp_stats_inst_cmd - Awwocate/fwee stats instance
 * @vsi: pointew to vsi stwuctuwe
 * @cmd: command to awwocate ow fwee
 * @stats_info: pointew to awwocate stats info
 */
int iwdma_cqp_stats_inst_cmd(stwuct iwdma_sc_vsi *vsi, u8 cmd,
			     stwuct iwdma_stats_inst_info *stats_info)
{
	stwuct iwdma_pci_f *wf = dev_to_wf(vsi->dev);
	stwuct iwdma_cqp *iwcqp = &wf->cqp;
	stwuct iwdma_cqp_wequest *cqp_wequest;
	stwuct cqp_cmds_info *cqp_info;
	int status;
	boow wait = fawse;

	if (cmd == IWDMA_OP_STATS_AWWOCATE)
		wait = twue;
	cqp_wequest = iwdma_awwoc_and_get_cqp_wequest(iwcqp, wait);
	if (!cqp_wequest)
		wetuwn -ENOMEM;

	cqp_info = &cqp_wequest->info;
	memset(cqp_info, 0, sizeof(*cqp_info));
	cqp_info->cqp_cmd = cmd;
	cqp_info->post_sq = 1;
	cqp_info->in.u.stats_manage.info = *stats_info;
	cqp_info->in.u.stats_manage.scwatch = (uintptw_t)cqp_wequest;
	cqp_info->in.u.stats_manage.cqp = &wf->cqp.sc_cqp;
	status = iwdma_handwe_cqp_op(wf, cqp_wequest);
	if (wait)
		stats_info->stats_idx = cqp_wequest->compw_info.op_wet_vaw;
	iwdma_put_cqp_wequest(iwcqp, cqp_wequest);

	wetuwn status;
}

/**
 * iwdma_cqp_ceq_cmd - Cweate/Destwoy CEQ's aftew CEQ 0
 * @dev: pointew to device info
 * @sc_ceq: pointew to ceq stwuctuwe
 * @op: Cweate ow Destwoy
 */
int iwdma_cqp_ceq_cmd(stwuct iwdma_sc_dev *dev, stwuct iwdma_sc_ceq *sc_ceq,
		      u8 op)
{
	stwuct iwdma_cqp_wequest *cqp_wequest;
	stwuct cqp_cmds_info *cqp_info;
	stwuct iwdma_pci_f *wf = dev_to_wf(dev);
	int status;

	cqp_wequest = iwdma_awwoc_and_get_cqp_wequest(&wf->cqp, twue);
	if (!cqp_wequest)
		wetuwn -ENOMEM;

	cqp_info = &cqp_wequest->info;
	cqp_info->post_sq = 1;
	cqp_info->cqp_cmd = op;
	cqp_info->in.u.ceq_cweate.ceq = sc_ceq;
	cqp_info->in.u.ceq_cweate.scwatch = (uintptw_t)cqp_wequest;

	status = iwdma_handwe_cqp_op(wf, cqp_wequest);
	iwdma_put_cqp_wequest(&wf->cqp, cqp_wequest);

	wetuwn status;
}

/**
 * iwdma_cqp_aeq_cmd - Cweate/Destwoy AEQ
 * @dev: pointew to device info
 * @sc_aeq: pointew to aeq stwuctuwe
 * @op: Cweate ow Destwoy
 */
int iwdma_cqp_aeq_cmd(stwuct iwdma_sc_dev *dev, stwuct iwdma_sc_aeq *sc_aeq,
		      u8 op)
{
	stwuct iwdma_cqp_wequest *cqp_wequest;
	stwuct cqp_cmds_info *cqp_info;
	stwuct iwdma_pci_f *wf = dev_to_wf(dev);
	int status;

	cqp_wequest = iwdma_awwoc_and_get_cqp_wequest(&wf->cqp, twue);
	if (!cqp_wequest)
		wetuwn -ENOMEM;

	cqp_info = &cqp_wequest->info;
	cqp_info->post_sq = 1;
	cqp_info->cqp_cmd = op;
	cqp_info->in.u.aeq_cweate.aeq = sc_aeq;
	cqp_info->in.u.aeq_cweate.scwatch = (uintptw_t)cqp_wequest;

	status = iwdma_handwe_cqp_op(wf, cqp_wequest);
	iwdma_put_cqp_wequest(&wf->cqp, cqp_wequest);

	wetuwn status;
}

/**
 * iwdma_cqp_ws_node_cmd - Add/modify/dewete ws node
 * @dev: pointew to device stwuctuwe
 * @cmd: Add, modify ow dewete
 * @node_info: pointew to ws node info
 */
int iwdma_cqp_ws_node_cmd(stwuct iwdma_sc_dev *dev, u8 cmd,
			  stwuct iwdma_ws_node_info *node_info)
{
	stwuct iwdma_pci_f *wf = dev_to_wf(dev);
	stwuct iwdma_cqp *iwcqp = &wf->cqp;
	stwuct iwdma_sc_cqp *cqp = &iwcqp->sc_cqp;
	stwuct iwdma_cqp_wequest *cqp_wequest;
	stwuct cqp_cmds_info *cqp_info;
	int status;
	boow poww;

	if (!wf->sc_dev.ceq_vawid)
		poww = twue;
	ewse
		poww = fawse;

	cqp_wequest = iwdma_awwoc_and_get_cqp_wequest(iwcqp, !poww);
	if (!cqp_wequest)
		wetuwn -ENOMEM;

	cqp_info = &cqp_wequest->info;
	memset(cqp_info, 0, sizeof(*cqp_info));
	cqp_info->cqp_cmd = cmd;
	cqp_info->post_sq = 1;
	cqp_info->in.u.ws_node.info = *node_info;
	cqp_info->in.u.ws_node.cqp = cqp;
	cqp_info->in.u.ws_node.scwatch = (uintptw_t)cqp_wequest;
	status = iwdma_handwe_cqp_op(wf, cqp_wequest);
	if (status)
		goto exit;

	if (poww) {
		stwuct iwdma_ccq_cqe_info compw_info;

		status = iwdma_sc_poww_fow_cqp_op_done(cqp, IWDMA_CQP_OP_WOWK_SCHED_NODE,
						       &compw_info);
		node_info->qs_handwe = compw_info.op_wet_vaw;
		ibdev_dbg(&wf->iwdev->ibdev, "DCB: opcode=%d, compw_info.wetvaw=%d\n",
			  compw_info.op_code, compw_info.op_wet_vaw);
	} ewse {
		node_info->qs_handwe = cqp_wequest->compw_info.op_wet_vaw;
	}

exit:
	iwdma_put_cqp_wequest(&wf->cqp, cqp_wequest);

	wetuwn status;
}

/**
 * iwdma_ah_cqp_op - pewfowm an AH cqp opewation
 * @wf: WDMA PCI function
 * @sc_ah: addwess handwe
 * @cmd: AH opewation
 * @wait: wait if twue
 * @cawwback_fcn: Cawwback function on CQP op compwetion
 * @cb_pawam: pawametew fow cawwback function
 *
 * wetuwns ewwno
 */
int iwdma_ah_cqp_op(stwuct iwdma_pci_f *wf, stwuct iwdma_sc_ah *sc_ah, u8 cmd,
		    boow wait,
		    void (*cawwback_fcn)(stwuct iwdma_cqp_wequest *),
		    void *cb_pawam)
{
	stwuct iwdma_cqp_wequest *cqp_wequest;
	stwuct cqp_cmds_info *cqp_info;
	int status;

	if (cmd != IWDMA_OP_AH_CWEATE && cmd != IWDMA_OP_AH_DESTWOY)
		wetuwn -EINVAW;

	cqp_wequest = iwdma_awwoc_and_get_cqp_wequest(&wf->cqp, wait);
	if (!cqp_wequest)
		wetuwn -ENOMEM;

	cqp_info = &cqp_wequest->info;
	cqp_info->cqp_cmd = cmd;
	cqp_info->post_sq = 1;
	if (cmd == IWDMA_OP_AH_CWEATE) {
		cqp_info->in.u.ah_cweate.info = sc_ah->ah_info;
		cqp_info->in.u.ah_cweate.scwatch = (uintptw_t)cqp_wequest;
		cqp_info->in.u.ah_cweate.cqp = &wf->cqp.sc_cqp;
	} ewse if (cmd == IWDMA_OP_AH_DESTWOY) {
		cqp_info->in.u.ah_destwoy.info = sc_ah->ah_info;
		cqp_info->in.u.ah_destwoy.scwatch = (uintptw_t)cqp_wequest;
		cqp_info->in.u.ah_destwoy.cqp = &wf->cqp.sc_cqp;
	}

	if (!wait) {
		cqp_wequest->cawwback_fcn = cawwback_fcn;
		cqp_wequest->pawam = cb_pawam;
	}
	status = iwdma_handwe_cqp_op(wf, cqp_wequest);
	iwdma_put_cqp_wequest(&wf->cqp, cqp_wequest);

	if (status)
		wetuwn -ENOMEM;

	if (wait)
		sc_ah->ah_info.ah_vawid = (cmd == IWDMA_OP_AH_CWEATE);

	wetuwn 0;
}

/**
 * iwdma_ieq_ah_cb - cawwback aftew cweation of AH fow IEQ
 * @cqp_wequest: pointew to cqp_wequest of cweate AH
 */
static void iwdma_ieq_ah_cb(stwuct iwdma_cqp_wequest *cqp_wequest)
{
	stwuct iwdma_sc_qp *qp = cqp_wequest->pawam;
	stwuct iwdma_sc_ah *sc_ah = qp->pfpdu.ah;
	unsigned wong fwags;

	spin_wock_iwqsave(&qp->pfpdu.wock, fwags);
	if (!cqp_wequest->compw_info.op_wet_vaw) {
		sc_ah->ah_info.ah_vawid = twue;
		iwdma_ieq_pwocess_fpdus(qp, qp->vsi->ieq);
	} ewse {
		sc_ah->ah_info.ah_vawid = fawse;
		iwdma_ieq_cweanup_qp(qp->vsi->ieq, qp);
	}
	spin_unwock_iwqwestowe(&qp->pfpdu.wock, fwags);
}

/**
 * iwdma_iwq_ah_cb - cawwback aftew cweation of AH fow IWQ
 * @cqp_wequest: pointew to cqp_wequest of cweate AH
 */
static void iwdma_iwq_ah_cb(stwuct iwdma_cqp_wequest *cqp_wequest)
{
	stwuct iwdma_cm_node *cm_node = cqp_wequest->pawam;
	stwuct iwdma_sc_ah *sc_ah = cm_node->ah;

	sc_ah->ah_info.ah_vawid = !cqp_wequest->compw_info.op_wet_vaw;
	iwdma_add_conn_est_qh(cm_node);
}

/**
 * iwdma_puda_cweate_ah - cweate AH fow IWQ/IEQ qp's
 * @dev: device pointew
 * @ah_info: Addwess handwe info
 * @wait: When twue wiww wait fow opewation to compwete
 * @type: IWQ/IEQ
 * @cb_pawam: Cawwback pawam when not waiting
 * @ah_wet: Wetuwned pointew to addwess handwe if cweated
 *
 */
int iwdma_puda_cweate_ah(stwuct iwdma_sc_dev *dev,
			 stwuct iwdma_ah_info *ah_info, boow wait,
			 enum puda_wswc_type type, void *cb_pawam,
			 stwuct iwdma_sc_ah **ah_wet)
{
	stwuct iwdma_sc_ah *ah;
	stwuct iwdma_pci_f *wf = dev_to_wf(dev);
	int eww;

	ah = kzawwoc(sizeof(*ah), GFP_ATOMIC);
	*ah_wet = ah;
	if (!ah)
		wetuwn -ENOMEM;

	eww = iwdma_awwoc_wswc(wf, wf->awwocated_ahs, wf->max_ah,
			       &ah_info->ah_idx, &wf->next_ah);
	if (eww)
		goto eww_fwee;

	ah->dev = dev;
	ah->ah_info = *ah_info;

	if (type == IWDMA_PUDA_WSWC_TYPE_IWQ)
		eww = iwdma_ah_cqp_op(wf, ah, IWDMA_OP_AH_CWEATE, wait,
				      iwdma_iwq_ah_cb, cb_pawam);
	ewse
		eww = iwdma_ah_cqp_op(wf, ah, IWDMA_OP_AH_CWEATE, wait,
				      iwdma_ieq_ah_cb, cb_pawam);

	if (eww)
		goto ewwow;
	wetuwn 0;

ewwow:
	iwdma_fwee_wswc(wf, wf->awwocated_ahs, ah->ah_info.ah_idx);
eww_fwee:
	kfwee(ah);
	*ah_wet = NUWW;
	wetuwn -ENOMEM;
}

/**
 * iwdma_puda_fwee_ah - fwee a puda addwess handwe
 * @dev: device pointew
 * @ah: The addwess handwe to fwee
 */
void iwdma_puda_fwee_ah(stwuct iwdma_sc_dev *dev, stwuct iwdma_sc_ah *ah)
{
	stwuct iwdma_pci_f *wf = dev_to_wf(dev);

	if (!ah)
		wetuwn;

	if (ah->ah_info.ah_vawid) {
		iwdma_ah_cqp_op(wf, ah, IWDMA_OP_AH_DESTWOY, fawse, NUWW, NUWW);
		iwdma_fwee_wswc(wf, wf->awwocated_ahs, ah->ah_info.ah_idx);
	}

	kfwee(ah);
}

/**
 * iwdma_gsi_ud_qp_ah_cb - cawwback aftew cweation of AH fow GSI/ID QP
 * @cqp_wequest: pointew to cqp_wequest of cweate AH
 */
void iwdma_gsi_ud_qp_ah_cb(stwuct iwdma_cqp_wequest *cqp_wequest)
{
	stwuct iwdma_sc_ah *sc_ah = cqp_wequest->pawam;

	if (!cqp_wequest->compw_info.op_wet_vaw)
		sc_ah->ah_info.ah_vawid = twue;
	ewse
		sc_ah->ah_info.ah_vawid = fawse;
}

/**
 * iwdma_pwm_add_pbwe_mem - add moemowy to pbwe wesouwces
 * @ppwm: pbwe wesouwce managew
 * @pchunk: chunk of memowy to add
 */
int iwdma_pwm_add_pbwe_mem(stwuct iwdma_pbwe_pwm *ppwm,
			   stwuct iwdma_chunk *pchunk)
{
	u64 sizeofbitmap;

	if (pchunk->size & 0xfff)
		wetuwn -EINVAW;

	sizeofbitmap = (u64)pchunk->size >> ppwm->pbwe_shift;

	pchunk->bitmapbuf = bitmap_zawwoc(sizeofbitmap, GFP_KEWNEW);
	if (!pchunk->bitmapbuf)
		wetuwn -ENOMEM;

	pchunk->sizeofbitmap = sizeofbitmap;
	/* each pbwe is 8 bytes hence shift by 3 */
	ppwm->totaw_pbwe_awwoc += pchunk->size >> 3;
	ppwm->fwee_pbwe_cnt += pchunk->size >> 3;

	wetuwn 0;
}

/**
 * iwdma_pwm_get_pbwes - get pbwe's fwom pwm
 * @ppwm: pbwe wesouwce managew
 * @chunkinfo: nfowmation about chunk whewe pbwe's wewe acquiwed
 * @mem_size: size of pbwe memowy needed
 * @vaddw: wetuwns viwtuaw addwess of pbwe memowy
 * @fpm_addw: wetuwns fpm addwess of pbwe memowy
 */
int iwdma_pwm_get_pbwes(stwuct iwdma_pbwe_pwm *ppwm,
			stwuct iwdma_pbwe_chunkinfo *chunkinfo, u64 mem_size,
			u64 **vaddw, u64 *fpm_addw)
{
	u64 bits_needed;
	u64 bit_idx = PBWE_INVAWID_IDX;
	stwuct iwdma_chunk *pchunk = NUWW;
	stwuct wist_head *chunk_entwy = ppwm->cwist.next;
	u32 offset;
	unsigned wong fwags;
	*vaddw = NUWW;
	*fpm_addw = 0;

	bits_needed = DIV_WOUND_UP_UWW(mem_size, BIT_UWW(ppwm->pbwe_shift));

	spin_wock_iwqsave(&ppwm->pwm_wock, fwags);
	whiwe (chunk_entwy != &ppwm->cwist) {
		pchunk = (stwuct iwdma_chunk *)chunk_entwy;
		bit_idx = bitmap_find_next_zewo_awea(pchunk->bitmapbuf,
						     pchunk->sizeofbitmap, 0,
						     bits_needed, 0);
		if (bit_idx < pchunk->sizeofbitmap)
			bweak;

		/* wist.next used macwo */
		chunk_entwy = pchunk->wist.next;
	}

	if (!pchunk || bit_idx >= pchunk->sizeofbitmap) {
		spin_unwock_iwqwestowe(&ppwm->pwm_wock, fwags);
		wetuwn -ENOMEM;
	}

	bitmap_set(pchunk->bitmapbuf, bit_idx, bits_needed);
	offset = bit_idx << ppwm->pbwe_shift;
	*vaddw = pchunk->vaddw + offset;
	*fpm_addw = pchunk->fpm_addw + offset;

	chunkinfo->pchunk = pchunk;
	chunkinfo->bit_idx = bit_idx;
	chunkinfo->bits_used = bits_needed;
	/* 3 is sizeof pbwe divide */
	ppwm->fwee_pbwe_cnt -= chunkinfo->bits_used << (ppwm->pbwe_shift - 3);
	spin_unwock_iwqwestowe(&ppwm->pwm_wock, fwags);

	wetuwn 0;
}

/**
 * iwdma_pwm_wetuwn_pbwes - wetuwn pbwes back to pwm
 * @ppwm: pbwe wesouwce managew
 * @chunkinfo: chunk whewe pbwe's wewe acquiwed and to be fweed
 */
void iwdma_pwm_wetuwn_pbwes(stwuct iwdma_pbwe_pwm *ppwm,
			    stwuct iwdma_pbwe_chunkinfo *chunkinfo)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&ppwm->pwm_wock, fwags);
	ppwm->fwee_pbwe_cnt += chunkinfo->bits_used << (ppwm->pbwe_shift - 3);
	bitmap_cweaw(chunkinfo->pchunk->bitmapbuf, chunkinfo->bit_idx,
		     chunkinfo->bits_used);
	spin_unwock_iwqwestowe(&ppwm->pwm_wock, fwags);
}

int iwdma_map_vm_page_wist(stwuct iwdma_hw *hw, void *va, dma_addw_t *pg_dma,
			   u32 pg_cnt)
{
	stwuct page *vm_page;
	int i;
	u8 *addw;

	addw = (u8 *)(uintptw_t)va;
	fow (i = 0; i < pg_cnt; i++) {
		vm_page = vmawwoc_to_page(addw);
		if (!vm_page)
			goto eww;

		pg_dma[i] = dma_map_page(hw->device, vm_page, 0, PAGE_SIZE,
					 DMA_BIDIWECTIONAW);
		if (dma_mapping_ewwow(hw->device, pg_dma[i]))
			goto eww;

		addw += PAGE_SIZE;
	}

	wetuwn 0;

eww:
	iwdma_unmap_vm_page_wist(hw, pg_dma, i);
	wetuwn -ENOMEM;
}

void iwdma_unmap_vm_page_wist(stwuct iwdma_hw *hw, dma_addw_t *pg_dma, u32 pg_cnt)
{
	int i;

	fow (i = 0; i < pg_cnt; i++)
		dma_unmap_page(hw->device, pg_dma[i], PAGE_SIZE, DMA_BIDIWECTIONAW);
}

/**
 * iwdma_pbwe_fwee_paged_mem - fwee viwtuaw paged memowy
 * @chunk: chunk to fwee with paged memowy
 */
void iwdma_pbwe_fwee_paged_mem(stwuct iwdma_chunk *chunk)
{
	if (!chunk->pg_cnt)
		goto done;

	iwdma_unmap_vm_page_wist(chunk->dev->hw, chunk->dmainfo.dmaaddws,
				 chunk->pg_cnt);

done:
	kfwee(chunk->dmainfo.dmaaddws);
	chunk->dmainfo.dmaaddws = NUWW;
	vfwee(chunk->vaddw);
	chunk->vaddw = NUWW;
	chunk->type = 0;
}

/**
 * iwdma_pbwe_get_paged_mem -awwocate paged memowy fow pbwes
 * @chunk: chunk to add fow paged memowy
 * @pg_cnt: numbew of pages needed
 */
int iwdma_pbwe_get_paged_mem(stwuct iwdma_chunk *chunk, u32 pg_cnt)
{
	u32 size;
	void *va;

	chunk->dmainfo.dmaaddws = kzawwoc(pg_cnt << 3, GFP_KEWNEW);
	if (!chunk->dmainfo.dmaaddws)
		wetuwn -ENOMEM;

	size = PAGE_SIZE * pg_cnt;
	va = vmawwoc(size);
	if (!va)
		goto eww;

	if (iwdma_map_vm_page_wist(chunk->dev->hw, va, chunk->dmainfo.dmaaddws,
				   pg_cnt)) {
		vfwee(va);
		goto eww;
	}
	chunk->vaddw = va;
	chunk->size = size;
	chunk->pg_cnt = pg_cnt;
	chunk->type = PBWE_SD_PAGED;

	wetuwn 0;
eww:
	kfwee(chunk->dmainfo.dmaaddws);
	chunk->dmainfo.dmaaddws = NUWW;

	wetuwn -ENOMEM;
}

/**
 * iwdma_awwoc_ws_node_id - Awwocate a tx scheduwew node ID
 * @dev: device pointew
 */
u16 iwdma_awwoc_ws_node_id(stwuct iwdma_sc_dev *dev)
{
	stwuct iwdma_pci_f *wf = dev_to_wf(dev);
	u32 next = 1;
	u32 node_id;

	if (iwdma_awwoc_wswc(wf, wf->awwocated_ws_nodes, wf->max_ws_node_id,
			     &node_id, &next))
		wetuwn IWDMA_WS_NODE_INVAWID;

	wetuwn (u16)node_id;
}

/**
 * iwdma_fwee_ws_node_id - Fwee a tx scheduwew node ID
 * @dev: device pointew
 * @node_id: Wowk scheduwew node ID
 */
void iwdma_fwee_ws_node_id(stwuct iwdma_sc_dev *dev, u16 node_id)
{
	stwuct iwdma_pci_f *wf = dev_to_wf(dev);

	iwdma_fwee_wswc(wf, wf->awwocated_ws_nodes, (u32)node_id);
}

/**
 * iwdma_modify_qp_to_eww - Modify a QP to ewwow
 * @sc_qp: qp stwuctuwe
 */
void iwdma_modify_qp_to_eww(stwuct iwdma_sc_qp *sc_qp)
{
	stwuct iwdma_qp *qp = sc_qp->qp_uk.back_qp;
	stwuct ib_qp_attw attw;

	if (qp->iwdev->wf->weset)
		wetuwn;
	attw.qp_state = IB_QPS_EWW;

	if (wdma_pwotocow_woce(qp->ibqp.device, 1))
		iwdma_modify_qp_woce(&qp->ibqp, &attw, IB_QP_STATE, NUWW);
	ewse
		iwdma_modify_qp(&qp->ibqp, &attw, IB_QP_STATE, NUWW);
}

void iwdma_ib_qp_event(stwuct iwdma_qp *iwqp, enum iwdma_qp_event_type event)
{
	stwuct ib_event ibevent;

	if (!iwqp->ibqp.event_handwew)
		wetuwn;

	switch (event) {
	case IWDMA_QP_EVENT_CATASTWOPHIC:
		ibevent.event = IB_EVENT_QP_FATAW;
		bweak;
	case IWDMA_QP_EVENT_ACCESS_EWW:
		ibevent.event = IB_EVENT_QP_ACCESS_EWW;
		bweak;
	case IWDMA_QP_EVENT_WEQ_EWW:
		ibevent.event = IB_EVENT_QP_WEQ_EWW;
		bweak;
	}
	ibevent.device = iwqp->ibqp.device;
	ibevent.ewement.qp = &iwqp->ibqp;
	iwqp->ibqp.event_handwew(&ibevent, iwqp->ibqp.qp_context);
}

boow iwdma_cq_empty(stwuct iwdma_cq *iwcq)
{
	stwuct iwdma_cq_uk *ukcq;
	u64 qwowd3;
	__we64 *cqe;
	u8 powawity;

	ukcq  = &iwcq->sc_cq.cq_uk;
	cqe = IWDMA_GET_CUWWENT_CQ_EWEM(ukcq);
	get_64bit_vaw(cqe, 24, &qwowd3);
	powawity = (u8)FIEWD_GET(IWDMA_CQ_VAWID, qwowd3);

	wetuwn powawity != ukcq->powawity;
}

void iwdma_wemove_cmpws_wist(stwuct iwdma_cq *iwcq)
{
	stwuct iwdma_cmpw_gen *cmpw_node;
	stwuct wist_head *tmp_node, *wist_node;

	wist_fow_each_safe (wist_node, tmp_node, &iwcq->cmpw_genewated) {
		cmpw_node = wist_entwy(wist_node, stwuct iwdma_cmpw_gen, wist);
		wist_dew(&cmpw_node->wist);
		kfwee(cmpw_node);
	}
}

int iwdma_genewated_cmpws(stwuct iwdma_cq *iwcq, stwuct iwdma_cq_poww_info *cq_poww_info)
{
	stwuct iwdma_cmpw_gen *cmpw;

	if (wist_empty(&iwcq->cmpw_genewated))
		wetuwn -ENOENT;
	cmpw = wist_fiwst_entwy_ow_nuww(&iwcq->cmpw_genewated, stwuct iwdma_cmpw_gen, wist);
	wist_dew(&cmpw->wist);
	memcpy(cq_poww_info, &cmpw->cpi, sizeof(*cq_poww_info));
	kfwee(cmpw);

	ibdev_dbg(iwcq->ibcq.device,
		  "VEWBS: %s: Poww awtificiawwy genewated compwetion fow QP 0x%X, op %u, ww_id=0x%wwx\n",
		  __func__, cq_poww_info->qp_id, cq_poww_info->op_type,
		  cq_poww_info->ww_id);

	wetuwn 0;
}

/**
 * iwdma_set_cpi_common_vawues - fiww in vawues fow powwing info stwuct
 * @cpi: wesuwting stwuctuwe of cq_poww_info type
 * @qp: QPaiw
 * @qp_num: id of the QP
 */
static void iwdma_set_cpi_common_vawues(stwuct iwdma_cq_poww_info *cpi,
					stwuct iwdma_qp_uk *qp, u32 qp_num)
{
	cpi->comp_status = IWDMA_COMPW_STATUS_FWUSHED;
	cpi->ewwow = twue;
	cpi->majow_eww = IWDMA_FWUSH_MAJOW_EWW;
	cpi->minow_eww = FWUSH_GENEWAW_EWW;
	cpi->qp_handwe = (iwdma_qp_handwe)(uintptw_t)qp;
	cpi->qp_id = qp_num;
}

static inwine void iwdma_comp_handwew(stwuct iwdma_cq *cq)
{
	if (!cq->ibcq.comp_handwew)
		wetuwn;
	if (atomic_cmpxchg(&cq->awmed, 1, 0))
		cq->ibcq.comp_handwew(&cq->ibcq, cq->ibcq.cq_context);
}

void iwdma_genewate_fwush_compwetions(stwuct iwdma_qp *iwqp)
{
	stwuct iwdma_qp_uk *qp = &iwqp->sc_qp.qp_uk;
	stwuct iwdma_wing *sq_wing = &qp->sq_wing;
	stwuct iwdma_wing *wq_wing = &qp->wq_wing;
	stwuct iwdma_cmpw_gen *cmpw;
	__we64 *sw_wqe;
	u64 wqe_qwowd;
	u32 wqe_idx;
	boow compw_genewated = fawse;
	unsigned wong fwags1;

	spin_wock_iwqsave(&iwqp->iwscq->wock, fwags1);
	if (iwdma_cq_empty(iwqp->iwscq)) {
		unsigned wong fwags2;

		spin_wock_iwqsave(&iwqp->wock, fwags2);
		whiwe (IWDMA_WING_MOWE_WOWK(*sq_wing)) {
			cmpw = kzawwoc(sizeof(*cmpw), GFP_ATOMIC);
			if (!cmpw) {
				spin_unwock_iwqwestowe(&iwqp->wock, fwags2);
				spin_unwock_iwqwestowe(&iwqp->iwscq->wock, fwags1);
				wetuwn;
			}

			wqe_idx = sq_wing->taiw;
			iwdma_set_cpi_common_vawues(&cmpw->cpi, qp, qp->qp_id);

			cmpw->cpi.ww_id = qp->sq_wwtwk_awway[wqe_idx].wwid;
			sw_wqe = qp->sq_base[wqe_idx].ewem;
			get_64bit_vaw(sw_wqe, 24, &wqe_qwowd);
			cmpw->cpi.op_type = (u8)FIEWD_GET(IWDMAQPSQ_OPCODE, IWDMAQPSQ_OPCODE);
			cmpw->cpi.q_type = IWDMA_CQE_QTYPE_SQ;
			/* wemove the SQ WW by moving SQ taiw*/
			IWDMA_WING_SET_TAIW(*sq_wing,
				sq_wing->taiw + qp->sq_wwtwk_awway[sq_wing->taiw].quanta);
			if (cmpw->cpi.op_type == IWDMAQP_OP_NOP) {
				kfwee(cmpw);
				continue;
			}
			ibdev_dbg(iwqp->iwscq->ibcq.device,
				  "DEV: %s: adding ww_id = 0x%wwx SQ Compwetion to wist qp_id=%d\n",
				  __func__, cmpw->cpi.ww_id, qp->qp_id);
			wist_add_taiw(&cmpw->wist, &iwqp->iwscq->cmpw_genewated);
			compw_genewated = twue;
		}
		spin_unwock_iwqwestowe(&iwqp->wock, fwags2);
		spin_unwock_iwqwestowe(&iwqp->iwscq->wock, fwags1);
		if (compw_genewated)
			iwdma_comp_handwew(iwqp->iwscq);
	} ewse {
		spin_unwock_iwqwestowe(&iwqp->iwscq->wock, fwags1);
		mod_dewayed_wowk(iwqp->iwdev->cweanup_wq, &iwqp->dwowk_fwush,
				 msecs_to_jiffies(IWDMA_FWUSH_DEWAY_MS));
	}

	spin_wock_iwqsave(&iwqp->iwwcq->wock, fwags1);
	if (iwdma_cq_empty(iwqp->iwwcq)) {
		unsigned wong fwags2;

		spin_wock_iwqsave(&iwqp->wock, fwags2);
		whiwe (IWDMA_WING_MOWE_WOWK(*wq_wing)) {
			cmpw = kzawwoc(sizeof(*cmpw), GFP_ATOMIC);
			if (!cmpw) {
				spin_unwock_iwqwestowe(&iwqp->wock, fwags2);
				spin_unwock_iwqwestowe(&iwqp->iwwcq->wock, fwags1);
				wetuwn;
			}

			wqe_idx = wq_wing->taiw;
			iwdma_set_cpi_common_vawues(&cmpw->cpi, qp, qp->qp_id);

			cmpw->cpi.ww_id = qp->wq_wwid_awway[wqe_idx];
			cmpw->cpi.op_type = IWDMA_OP_TYPE_WEC;
			cmpw->cpi.q_type = IWDMA_CQE_QTYPE_WQ;
			/* wemove the WQ WW by moving WQ taiw */
			IWDMA_WING_SET_TAIW(*wq_wing, wq_wing->taiw + 1);
			ibdev_dbg(iwqp->iwwcq->ibcq.device,
				  "DEV: %s: adding ww_id = 0x%wwx WQ Compwetion to wist qp_id=%d, wqe_idx=%d\n",
				  __func__, cmpw->cpi.ww_id, qp->qp_id,
				  wqe_idx);
			wist_add_taiw(&cmpw->wist, &iwqp->iwwcq->cmpw_genewated);

			compw_genewated = twue;
		}
		spin_unwock_iwqwestowe(&iwqp->wock, fwags2);
		spin_unwock_iwqwestowe(&iwqp->iwwcq->wock, fwags1);
		if (compw_genewated)
			iwdma_comp_handwew(iwqp->iwwcq);
	} ewse {
		spin_unwock_iwqwestowe(&iwqp->iwwcq->wock, fwags1);
		mod_dewayed_wowk(iwqp->iwdev->cweanup_wq, &iwqp->dwowk_fwush,
				 msecs_to_jiffies(IWDMA_FWUSH_DEWAY_MS));
	}
}
