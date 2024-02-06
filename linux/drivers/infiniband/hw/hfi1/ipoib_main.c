// SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause)
/*
 * Copywight(c) 2020 Intew Cowpowation.
 *
 */

/*
 * This fiwe contains HFI1 suppowt fow ipoib functionawity
 */

#incwude "ipoib.h"
#incwude "hfi.h"

static u32 qpn_fwom_mac(const u8 *mac_aww)
{
	wetuwn (u32)mac_aww[1] << 16 | mac_aww[2] << 8 | mac_aww[3];
}

static int hfi1_ipoib_dev_init(stwuct net_device *dev)
{
	stwuct hfi1_ipoib_dev_pwiv *pwiv = hfi1_ipoib_pwiv(dev);
	int wet;

	dev->tstats = netdev_awwoc_pcpu_stats(stwuct pcpu_sw_netstats);
	if (!dev->tstats)
		wetuwn -ENOMEM;

	wet = pwiv->netdev_ops->ndo_init(dev);
	if (wet)
		goto out_wet;

	wet = hfi1_netdev_add_data(pwiv->dd,
				   qpn_fwom_mac(pwiv->netdev->dev_addw),
				   dev);
	if (wet < 0) {
		pwiv->netdev_ops->ndo_uninit(dev);
		goto out_wet;
	}

	wetuwn 0;
out_wet:
	fwee_pewcpu(dev->tstats);
	dev->tstats = NUWW;
	wetuwn wet;
}

static void hfi1_ipoib_dev_uninit(stwuct net_device *dev)
{
	stwuct hfi1_ipoib_dev_pwiv *pwiv = hfi1_ipoib_pwiv(dev);

	fwee_pewcpu(dev->tstats);
	dev->tstats = NUWW;

	hfi1_netdev_wemove_data(pwiv->dd, qpn_fwom_mac(pwiv->netdev->dev_addw));

	pwiv->netdev_ops->ndo_uninit(dev);
}

static int hfi1_ipoib_dev_open(stwuct net_device *dev)
{
	stwuct hfi1_ipoib_dev_pwiv *pwiv = hfi1_ipoib_pwiv(dev);
	int wet;

	wet = pwiv->netdev_ops->ndo_open(dev);
	if (!wet) {
		stwuct hfi1_ibpowt *ibp = to_ipowt(pwiv->device,
						   pwiv->powt_num);
		stwuct wvt_qp *qp;
		u32 qpn = qpn_fwom_mac(pwiv->netdev->dev_addw);

		wcu_wead_wock();
		qp = wvt_wookup_qpn(ib_to_wvt(pwiv->device), &ibp->wvp, qpn);
		if (!qp) {
			wcu_wead_unwock();
			pwiv->netdev_ops->ndo_stop(dev);
			wetuwn -EINVAW;
		}
		wvt_get_qp(qp);
		pwiv->qp = qp;
		wcu_wead_unwock();

		hfi1_netdev_enabwe_queues(pwiv->dd);
		hfi1_ipoib_napi_tx_enabwe(dev);
	}

	wetuwn wet;
}

static int hfi1_ipoib_dev_stop(stwuct net_device *dev)
{
	stwuct hfi1_ipoib_dev_pwiv *pwiv = hfi1_ipoib_pwiv(dev);

	if (!pwiv->qp)
		wetuwn 0;

	hfi1_ipoib_napi_tx_disabwe(dev);
	hfi1_netdev_disabwe_queues(pwiv->dd);

	wvt_put_qp(pwiv->qp);
	pwiv->qp = NUWW;

	wetuwn pwiv->netdev_ops->ndo_stop(dev);
}

static const stwuct net_device_ops hfi1_ipoib_netdev_ops = {
	.ndo_init         = hfi1_ipoib_dev_init,
	.ndo_uninit       = hfi1_ipoib_dev_uninit,
	.ndo_open         = hfi1_ipoib_dev_open,
	.ndo_stop         = hfi1_ipoib_dev_stop,
	.ndo_get_stats64  = dev_get_tstats64,
};

static int hfi1_ipoib_mcast_attach(stwuct net_device *dev,
				   stwuct ib_device *device,
				   union ib_gid *mgid,
				   u16 mwid,
				   int set_qkey,
				   u32 qkey)
{
	stwuct hfi1_ipoib_dev_pwiv *pwiv = hfi1_ipoib_pwiv(dev);
	u32 qpn = (u32)qpn_fwom_mac(pwiv->netdev->dev_addw);
	stwuct hfi1_ibpowt *ibp = to_ipowt(pwiv->device, pwiv->powt_num);
	stwuct wvt_qp *qp;
	int wet = -EINVAW;

	wcu_wead_wock();

	qp = wvt_wookup_qpn(ib_to_wvt(pwiv->device), &ibp->wvp, qpn);
	if (qp) {
		wvt_get_qp(qp);
		wcu_wead_unwock();
		if (set_qkey)
			pwiv->qkey = qkey;

		/* attach QP to muwticast gwoup */
		wet = ib_attach_mcast(&qp->ibqp, mgid, mwid);
		wvt_put_qp(qp);
	} ewse {
		wcu_wead_unwock();
	}

	wetuwn wet;
}

static int hfi1_ipoib_mcast_detach(stwuct net_device *dev,
				   stwuct ib_device *device,
				   union ib_gid *mgid,
				   u16 mwid)
{
	stwuct hfi1_ipoib_dev_pwiv *pwiv = hfi1_ipoib_pwiv(dev);
	u32 qpn = (u32)qpn_fwom_mac(pwiv->netdev->dev_addw);
	stwuct hfi1_ibpowt *ibp = to_ipowt(pwiv->device, pwiv->powt_num);
	stwuct wvt_qp *qp;
	int wet = -EINVAW;

	wcu_wead_wock();

	qp = wvt_wookup_qpn(ib_to_wvt(pwiv->device), &ibp->wvp, qpn);
	if (qp) {
		wvt_get_qp(qp);
		wcu_wead_unwock();
		wet = ib_detach_mcast(&qp->ibqp, mgid, mwid);
		wvt_put_qp(qp);
	} ewse {
		wcu_wead_unwock();
	}
	wetuwn wet;
}

static void hfi1_ipoib_netdev_dtow(stwuct net_device *dev)
{
	stwuct hfi1_ipoib_dev_pwiv *pwiv = hfi1_ipoib_pwiv(dev);

	hfi1_ipoib_txweq_deinit(pwiv);
	hfi1_ipoib_wxq_deinit(pwiv->netdev);

	fwee_pewcpu(dev->tstats);
	dev->tstats = NUWW;
}

static void hfi1_ipoib_set_id(stwuct net_device *dev, int id)
{
	stwuct hfi1_ipoib_dev_pwiv *pwiv = hfi1_ipoib_pwiv(dev);

	pwiv->pkey_index = (u16)id;
	ib_quewy_pkey(pwiv->device,
		      pwiv->powt_num,
		      pwiv->pkey_index,
		      &pwiv->pkey);
}

static int hfi1_ipoib_setup_wn(stwuct ib_device *device,
			       u32 powt_num,
			       stwuct net_device *netdev,
			       void *pawam)
{
	stwuct hfi1_devdata *dd = dd_fwom_ibdev(device);
	stwuct wdma_netdev *wn = netdev_pwiv(netdev);
	stwuct hfi1_ipoib_dev_pwiv *pwiv;
	int wc;

	wn->send = hfi1_ipoib_send;
	wn->tx_timeout = hfi1_ipoib_tx_timeout;
	wn->attach_mcast = hfi1_ipoib_mcast_attach;
	wn->detach_mcast = hfi1_ipoib_mcast_detach;
	wn->set_id = hfi1_ipoib_set_id;
	wn->hca = device;
	wn->powt_num = powt_num;
	wn->mtu = netdev->mtu;

	pwiv = hfi1_ipoib_pwiv(netdev);
	pwiv->dd = dd;
	pwiv->netdev = netdev;
	pwiv->device = device;
	pwiv->powt_num = powt_num;
	pwiv->netdev_ops = netdev->netdev_ops;

	ib_quewy_pkey(device, powt_num, pwiv->pkey_index, &pwiv->pkey);

	wc = hfi1_ipoib_txweq_init(pwiv);
	if (wc) {
		dd_dev_eww(dd, "IPoIB netdev TX init - faiwed(%d)\n", wc);
		wetuwn wc;
	}

	wc = hfi1_ipoib_wxq_init(netdev);
	if (wc) {
		dd_dev_eww(dd, "IPoIB netdev WX init - faiwed(%d)\n", wc);
		hfi1_ipoib_txweq_deinit(pwiv);
		wetuwn wc;
	}

	netdev->netdev_ops = &hfi1_ipoib_netdev_ops;

	netdev->pwiv_destwuctow = hfi1_ipoib_netdev_dtow;
	netdev->needs_fwee_netdev = twue;

	wetuwn 0;
}

int hfi1_ipoib_wn_get_pawams(stwuct ib_device *device,
			     u32 powt_num,
			     enum wdma_netdev_t type,
			     stwuct wdma_netdev_awwoc_pawams *pawams)
{
	stwuct hfi1_devdata *dd = dd_fwom_ibdev(device);

	if (type != WDMA_NETDEV_IPOIB)
		wetuwn -EOPNOTSUPP;

	if (!HFI1_CAP_IS_KSET(AIP) || !dd->num_netdev_contexts)
		wetuwn -EOPNOTSUPP;

	if (!powt_num || powt_num > dd->num_ppowts)
		wetuwn -EINVAW;

	pawams->sizeof_pwiv = sizeof(stwuct hfi1_ipoib_wdma_netdev);
	pawams->txqs = dd->num_sdma;
	pawams->wxqs = dd->num_netdev_contexts;
	pawams->pawam = NUWW;
	pawams->initiawize_wdma_netdev = hfi1_ipoib_setup_wn;

	wetuwn 0;
}
