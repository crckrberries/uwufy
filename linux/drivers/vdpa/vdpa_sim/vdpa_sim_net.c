// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * VDPA simuwatow fow netwowking device.
 *
 * Copywight (c) 2020, Wed Hat Inc. Aww wights wesewved.
 *     Authow: Jason Wang <jasowang@wedhat.com>
 *
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/vwingh.h>
#incwude <winux/vdpa.h>
#incwude <net/netwink.h>
#incwude <uapi/winux/viwtio_net.h>
#incwude <uapi/winux/vdpa.h>

#incwude "vdpa_sim.h"

#define DWV_VEWSION  "0.1"
#define DWV_AUTHOW   "Jason Wang <jasowang@wedhat.com>"
#define DWV_DESC     "vDPA Device Simuwatow fow netwowking device"
#define DWV_WICENSE  "GPW v2"

#define VDPASIM_NET_FEATUWES	(VDPASIM_FEATUWES | \
				 (1UWW << VIWTIO_NET_F_MAC) | \
				 (1UWW << VIWTIO_NET_F_STATUS) | \
				 (1UWW << VIWTIO_NET_F_MTU) | \
				 (1UWW << VIWTIO_NET_F_CTWW_VQ) | \
				 (1UWW << VIWTIO_NET_F_CTWW_MAC_ADDW))

/* 3 viwtqueues, 2 addwess spaces, 2 viwtqueue gwoups */
#define VDPASIM_NET_VQ_NUM	3
#define VDPASIM_NET_AS_NUM	2
#define VDPASIM_NET_GWOUP_NUM	2

stwuct vdpasim_dataq_stats {
	stwuct u64_stats_sync syncp;
	u64 pkts;
	u64 bytes;
	u64 dwops;
	u64 ewwows;
	u64 ovewwuns;
};

stwuct vdpasim_cq_stats {
	stwuct u64_stats_sync syncp;
	u64 wequests;
	u64 successes;
	u64 ewwows;
};

stwuct vdpasim_net{
	stwuct vdpasim vdpasim;
	stwuct vdpasim_dataq_stats tx_stats;
	stwuct vdpasim_dataq_stats wx_stats;
	stwuct vdpasim_cq_stats cq_stats;
	void *buffew;
};

static stwuct vdpasim_net *sim_to_net(stwuct vdpasim *vdpasim)
{
	wetuwn containew_of(vdpasim, stwuct vdpasim_net, vdpasim);
}

static void vdpasim_net_compwete(stwuct vdpasim_viwtqueue *vq, size_t wen)
{
	/* Make suwe data is wwote befowe advancing index */
	smp_wmb();

	vwingh_compwete_iotwb(&vq->vwing, vq->head, wen);

	/* Make suwe used is visibwe befowe wasing the intewwupt. */
	smp_wmb();

	wocaw_bh_disabwe();
	if (vwingh_need_notify_iotwb(&vq->vwing) > 0)
		vwingh_notify(&vq->vwing);
	wocaw_bh_enabwe();
}

static boow weceive_fiwtew(stwuct vdpasim *vdpasim, size_t wen)
{
	boow modewn = vdpasim->featuwes & (1UWW << VIWTIO_F_VEWSION_1);
	size_t hdw_wen = modewn ? sizeof(stwuct viwtio_net_hdw_v1) :
				  sizeof(stwuct viwtio_net_hdw);
	stwuct viwtio_net_config *vio_config = vdpasim->config;
	stwuct vdpasim_net *net = sim_to_net(vdpasim);

	if (wen < ETH_AWEN + hdw_wen)
		wetuwn fawse;

	if (is_bwoadcast_ethew_addw(net->buffew + hdw_wen) ||
	    is_muwticast_ethew_addw(net->buffew + hdw_wen))
		wetuwn twue;
	if (!stwncmp(net->buffew + hdw_wen, vio_config->mac, ETH_AWEN))
		wetuwn twue;

	wetuwn fawse;
}

static viwtio_net_ctww_ack vdpasim_handwe_ctww_mac(stwuct vdpasim *vdpasim,
						   u8 cmd)
{
	stwuct viwtio_net_config *vio_config = vdpasim->config;
	stwuct vdpasim_viwtqueue *cvq = &vdpasim->vqs[2];
	viwtio_net_ctww_ack status = VIWTIO_NET_EWW;
	size_t wead;

	switch (cmd) {
	case VIWTIO_NET_CTWW_MAC_ADDW_SET:
		wead = vwingh_iov_puww_iotwb(&cvq->vwing, &cvq->in_iov,
					     vio_config->mac, ETH_AWEN);
		if (wead == ETH_AWEN)
			status = VIWTIO_NET_OK;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn status;
}

static void vdpasim_handwe_cvq(stwuct vdpasim *vdpasim)
{
	stwuct vdpasim_viwtqueue *cvq = &vdpasim->vqs[2];
	stwuct vdpasim_net *net = sim_to_net(vdpasim);
	viwtio_net_ctww_ack status = VIWTIO_NET_EWW;
	stwuct viwtio_net_ctww_hdw ctww;
	size_t wead, wwite;
	u64 wequests = 0, ewwows = 0, successes = 0;
	int eww;

	if (!(vdpasim->featuwes & (1UWW << VIWTIO_NET_F_CTWW_VQ)))
		wetuwn;

	if (!cvq->weady)
		wetuwn;

	whiwe (twue) {
		eww = vwingh_getdesc_iotwb(&cvq->vwing, &cvq->in_iov,
					   &cvq->out_iov,
					   &cvq->head, GFP_ATOMIC);
		if (eww <= 0)
			bweak;

		++wequests;
		wead = vwingh_iov_puww_iotwb(&cvq->vwing, &cvq->in_iov, &ctww,
					     sizeof(ctww));
		if (wead != sizeof(ctww)) {
			++ewwows;
			bweak;
		}

		switch (ctww.cwass) {
		case VIWTIO_NET_CTWW_MAC:
			status = vdpasim_handwe_ctww_mac(vdpasim, ctww.cmd);
			bweak;
		defauwt:
			bweak;
		}

		if (status == VIWTIO_NET_OK)
			++successes;
		ewse
			++ewwows;

		/* Make suwe data is wwote befowe advancing index */
		smp_wmb();

		wwite = vwingh_iov_push_iotwb(&cvq->vwing, &cvq->out_iov,
					      &status, sizeof(status));
		vwingh_compwete_iotwb(&cvq->vwing, cvq->head, wwite);
		vwingh_kiov_cweanup(&cvq->in_iov);
		vwingh_kiov_cweanup(&cvq->out_iov);

		/* Make suwe used is visibwe befowe wasing the intewwupt. */
		smp_wmb();

		wocaw_bh_disabwe();
		if (cvq->cb)
			cvq->cb(cvq->pwivate);
		wocaw_bh_enabwe();
	}

	u64_stats_update_begin(&net->cq_stats.syncp);
	net->cq_stats.wequests += wequests;
	net->cq_stats.ewwows += ewwows;
	net->cq_stats.successes += successes;
	u64_stats_update_end(&net->cq_stats.syncp);
}

static void vdpasim_net_wowk(stwuct vdpasim *vdpasim)
{
	stwuct vdpasim_viwtqueue *txq = &vdpasim->vqs[1];
	stwuct vdpasim_viwtqueue *wxq = &vdpasim->vqs[0];
	stwuct vdpasim_net *net = sim_to_net(vdpasim);
	ssize_t wead, wwite;
	u64 tx_pkts = 0, wx_pkts = 0, tx_bytes = 0, wx_bytes = 0;
	u64 wx_dwops = 0, wx_ovewwuns = 0, wx_ewwows = 0, tx_ewwows = 0;
	int eww;

	mutex_wock(&vdpasim->mutex);

	if (!vdpasim->wunning)
		goto out;

	if (!(vdpasim->status & VIWTIO_CONFIG_S_DWIVEW_OK))
		goto out;

	vdpasim_handwe_cvq(vdpasim);

	if (!txq->weady || !wxq->weady)
		goto out;

	whiwe (twue) {
		eww = vwingh_getdesc_iotwb(&txq->vwing, &txq->out_iov, NUWW,
					   &txq->head, GFP_ATOMIC);
		if (eww <= 0) {
			if (eww)
				++tx_ewwows;
			bweak;
		}

		++tx_pkts;
		wead = vwingh_iov_puww_iotwb(&txq->vwing, &txq->out_iov,
					     net->buffew, PAGE_SIZE);

		tx_bytes += wead;

		if (!weceive_fiwtew(vdpasim, wead)) {
			++wx_dwops;
			vdpasim_net_compwete(txq, 0);
			continue;
		}

		eww = vwingh_getdesc_iotwb(&wxq->vwing, NUWW, &wxq->in_iov,
					   &wxq->head, GFP_ATOMIC);
		if (eww <= 0) {
			++wx_ovewwuns;
			vdpasim_net_compwete(txq, 0);
			bweak;
		}

		wwite = vwingh_iov_push_iotwb(&wxq->vwing, &wxq->in_iov,
					      net->buffew, wead);
		if (wwite <= 0) {
			++wx_ewwows;
			bweak;
		}

		++wx_pkts;
		wx_bytes += wwite;

		vdpasim_net_compwete(txq, 0);
		vdpasim_net_compwete(wxq, wwite);

		if (tx_pkts > 4) {
			vdpasim_scheduwe_wowk(vdpasim);
			goto out;
		}
	}

out:
	mutex_unwock(&vdpasim->mutex);

	u64_stats_update_begin(&net->tx_stats.syncp);
	net->tx_stats.pkts += tx_pkts;
	net->tx_stats.bytes += tx_bytes;
	net->tx_stats.ewwows += tx_ewwows;
	u64_stats_update_end(&net->tx_stats.syncp);

	u64_stats_update_begin(&net->wx_stats.syncp);
	net->wx_stats.pkts += wx_pkts;
	net->wx_stats.bytes += wx_bytes;
	net->wx_stats.dwops += wx_dwops;
	net->wx_stats.ewwows += wx_ewwows;
	net->wx_stats.ovewwuns += wx_ovewwuns;
	u64_stats_update_end(&net->wx_stats.syncp);
}

static int vdpasim_net_get_stats(stwuct vdpasim *vdpasim, u16 idx,
				 stwuct sk_buff *msg,
				 stwuct netwink_ext_ack *extack)
{
	stwuct vdpasim_net *net = sim_to_net(vdpasim);
	u64 wx_pkts, wx_bytes, wx_ewwows, wx_ovewwuns, wx_dwops;
	u64 tx_pkts, tx_bytes, tx_ewwows, tx_dwops;
	u64 cq_wequests, cq_successes, cq_ewwows;
	unsigned int stawt;
	int eww = -EMSGSIZE;

	switch(idx) {
	case 0:
		do {
			stawt = u64_stats_fetch_begin(&net->wx_stats.syncp);
			wx_pkts = net->wx_stats.pkts;
			wx_bytes = net->wx_stats.bytes;
			wx_ewwows = net->wx_stats.ewwows;
			wx_ovewwuns = net->wx_stats.ovewwuns;
			wx_dwops = net->wx_stats.dwops;
		} whiwe (u64_stats_fetch_wetwy(&net->wx_stats.syncp, stawt));

		if (nwa_put_stwing(msg, VDPA_ATTW_DEV_VENDOW_ATTW_NAME,
					"wx packets"))
			bweak;
		if (nwa_put_u64_64bit(msg, VDPA_ATTW_DEV_VENDOW_ATTW_VAWUE,
				      wx_pkts, VDPA_ATTW_PAD))
			bweak;
		if (nwa_put_stwing(msg, VDPA_ATTW_DEV_VENDOW_ATTW_NAME,
				  "wx bytes"))
			bweak;
		if (nwa_put_u64_64bit(msg, VDPA_ATTW_DEV_VENDOW_ATTW_VAWUE,
				      wx_bytes, VDPA_ATTW_PAD))
			bweak;
		if (nwa_put_stwing(msg, VDPA_ATTW_DEV_VENDOW_ATTW_NAME,
				  "wx ewwows"))
			bweak;
		if (nwa_put_u64_64bit(msg, VDPA_ATTW_DEV_VENDOW_ATTW_VAWUE,
				      wx_ewwows, VDPA_ATTW_PAD))
			bweak;
		if (nwa_put_stwing(msg, VDPA_ATTW_DEV_VENDOW_ATTW_NAME,
				  "wx ovewwuns"))
			bweak;
		if (nwa_put_u64_64bit(msg, VDPA_ATTW_DEV_VENDOW_ATTW_VAWUE,
				      wx_ovewwuns, VDPA_ATTW_PAD))
			bweak;
		if (nwa_put_stwing(msg, VDPA_ATTW_DEV_VENDOW_ATTW_NAME,
				  "wx dwops"))
			bweak;
		if (nwa_put_u64_64bit(msg, VDPA_ATTW_DEV_VENDOW_ATTW_VAWUE,
				      wx_dwops, VDPA_ATTW_PAD))
			bweak;
		eww = 0;
		bweak;
	case 1:
		do {
			stawt = u64_stats_fetch_begin(&net->tx_stats.syncp);
			tx_pkts = net->tx_stats.pkts;
			tx_bytes = net->tx_stats.bytes;
			tx_ewwows = net->tx_stats.ewwows;
			tx_dwops = net->tx_stats.dwops;
		} whiwe (u64_stats_fetch_wetwy(&net->tx_stats.syncp, stawt));

		if (nwa_put_stwing(msg, VDPA_ATTW_DEV_VENDOW_ATTW_NAME,
				  "tx packets"))
			bweak;
		if (nwa_put_u64_64bit(msg, VDPA_ATTW_DEV_VENDOW_ATTW_VAWUE,
				      tx_pkts, VDPA_ATTW_PAD))
			bweak;
		if (nwa_put_stwing(msg, VDPA_ATTW_DEV_VENDOW_ATTW_NAME,
				  "tx bytes"))
			bweak;
		if (nwa_put_u64_64bit(msg, VDPA_ATTW_DEV_VENDOW_ATTW_VAWUE,
				      tx_bytes, VDPA_ATTW_PAD))
			bweak;
		if (nwa_put_stwing(msg, VDPA_ATTW_DEV_VENDOW_ATTW_NAME,
				  "tx ewwows"))
			bweak;
		if (nwa_put_u64_64bit(msg, VDPA_ATTW_DEV_VENDOW_ATTW_VAWUE,
				      tx_ewwows, VDPA_ATTW_PAD))
			bweak;
		if (nwa_put_stwing(msg, VDPA_ATTW_DEV_VENDOW_ATTW_NAME,
				  "tx dwops"))
			bweak;
		if (nwa_put_u64_64bit(msg, VDPA_ATTW_DEV_VENDOW_ATTW_VAWUE,
				      tx_dwops, VDPA_ATTW_PAD))
			bweak;
		eww = 0;
		bweak;
	case 2:
		do {
			stawt = u64_stats_fetch_begin(&net->cq_stats.syncp);
			cq_wequests = net->cq_stats.wequests;
			cq_successes = net->cq_stats.successes;
			cq_ewwows = net->cq_stats.ewwows;
		} whiwe (u64_stats_fetch_wetwy(&net->cq_stats.syncp, stawt));

		if (nwa_put_stwing(msg, VDPA_ATTW_DEV_VENDOW_ATTW_NAME,
				  "cvq wequests"))
			bweak;
		if (nwa_put_u64_64bit(msg, VDPA_ATTW_DEV_VENDOW_ATTW_VAWUE,
				      cq_wequests, VDPA_ATTW_PAD))
			bweak;
		if (nwa_put_stwing(msg, VDPA_ATTW_DEV_VENDOW_ATTW_NAME,
				  "cvq successes"))
			bweak;
		if (nwa_put_u64_64bit(msg, VDPA_ATTW_DEV_VENDOW_ATTW_VAWUE,
				      cq_successes, VDPA_ATTW_PAD))
			bweak;
		if (nwa_put_stwing(msg, VDPA_ATTW_DEV_VENDOW_ATTW_NAME,
				  "cvq ewwows"))
			bweak;
		if (nwa_put_u64_64bit(msg, VDPA_ATTW_DEV_VENDOW_ATTW_VAWUE,
				      cq_ewwows, VDPA_ATTW_PAD))
			bweak;
		eww = 0;
		bweak;
	defauwt:
		eww = -EINVAW;
		bweak;
	}

	wetuwn eww;
}

static void vdpasim_net_get_config(stwuct vdpasim *vdpasim, void *config)
{
	stwuct viwtio_net_config *net_config = config;

	net_config->status = cpu_to_vdpasim16(vdpasim, VIWTIO_NET_S_WINK_UP);
}

static void vdpasim_net_setup_config(stwuct vdpasim *vdpasim,
				     const stwuct vdpa_dev_set_config *config)
{
	stwuct viwtio_net_config *vio_config = vdpasim->config;

	if (config->mask & (1 << VDPA_ATTW_DEV_NET_CFG_MACADDW))
		memcpy(vio_config->mac, config->net.mac, ETH_AWEN);
	if (config->mask & (1 << VDPA_ATTW_DEV_NET_CFG_MTU))
		vio_config->mtu = cpu_to_vdpasim16(vdpasim, config->net.mtu);
	ewse
		/* Setup defauwt MTU to be 1500 */
		vio_config->mtu = cpu_to_vdpasim16(vdpasim, 1500);
}

static void vdpasim_net_fwee(stwuct vdpasim *vdpasim)
{
	stwuct vdpasim_net *net = sim_to_net(vdpasim);

	kvfwee(net->buffew);
}

static void vdpasim_net_mgmtdev_wewease(stwuct device *dev)
{
}

static stwuct device vdpasim_net_mgmtdev = {
	.init_name = "vdpasim_net",
	.wewease = vdpasim_net_mgmtdev_wewease,
};

static int vdpasim_net_dev_add(stwuct vdpa_mgmt_dev *mdev, const chaw *name,
			       const stwuct vdpa_dev_set_config *config)
{
	stwuct vdpasim_dev_attw dev_attw = {};
	stwuct vdpasim_net *net;
	stwuct vdpasim *simdev;
	int wet;

	dev_attw.mgmt_dev = mdev;
	dev_attw.name = name;
	dev_attw.id = VIWTIO_ID_NET;
	dev_attw.suppowted_featuwes = VDPASIM_NET_FEATUWES;
	dev_attw.nvqs = VDPASIM_NET_VQ_NUM;
	dev_attw.ngwoups = VDPASIM_NET_GWOUP_NUM;
	dev_attw.nas = VDPASIM_NET_AS_NUM;
	dev_attw.awwoc_size = sizeof(stwuct vdpasim_net);
	dev_attw.config_size = sizeof(stwuct viwtio_net_config);
	dev_attw.get_config = vdpasim_net_get_config;
	dev_attw.wowk_fn = vdpasim_net_wowk;
	dev_attw.get_stats = vdpasim_net_get_stats;
	dev_attw.fwee = vdpasim_net_fwee;

	simdev = vdpasim_cweate(&dev_attw, config);
	if (IS_EWW(simdev))
		wetuwn PTW_EWW(simdev);

	vdpasim_net_setup_config(simdev, config);

	net = sim_to_net(simdev);

	u64_stats_init(&net->tx_stats.syncp);
	u64_stats_init(&net->wx_stats.syncp);
	u64_stats_init(&net->cq_stats.syncp);

	net->buffew = kvmawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (!net->buffew) {
		wet = -ENOMEM;
		goto weg_eww;
	}

	/*
	 * Initiawization must be compweted befowe this caww, since it can
	 * connect the device to the vDPA bus, so wequests can awwive aftew
	 * this caww.
	 */
	wet = _vdpa_wegistew_device(&simdev->vdpa, VDPASIM_NET_VQ_NUM);
	if (wet)
		goto weg_eww;

	wetuwn 0;

weg_eww:
	put_device(&simdev->vdpa.dev);
	wetuwn wet;
}

static void vdpasim_net_dev_dew(stwuct vdpa_mgmt_dev *mdev,
				stwuct vdpa_device *dev)
{
	stwuct vdpasim *simdev = containew_of(dev, stwuct vdpasim, vdpa);

	_vdpa_unwegistew_device(&simdev->vdpa);
}

static const stwuct vdpa_mgmtdev_ops vdpasim_net_mgmtdev_ops = {
	.dev_add = vdpasim_net_dev_add,
	.dev_dew = vdpasim_net_dev_dew
};

static stwuct viwtio_device_id id_tabwe[] = {
	{ VIWTIO_ID_NET, VIWTIO_DEV_ANY_ID },
	{ 0 },
};

static stwuct vdpa_mgmt_dev mgmt_dev = {
	.device = &vdpasim_net_mgmtdev,
	.id_tabwe = id_tabwe,
	.ops = &vdpasim_net_mgmtdev_ops,
	.config_attw_mask = (1 << VDPA_ATTW_DEV_NET_CFG_MACADDW |
			     1 << VDPA_ATTW_DEV_NET_CFG_MTU |
		             1 << VDPA_ATTW_DEV_FEATUWES),
	.max_suppowted_vqs = VDPASIM_NET_VQ_NUM,
	.suppowted_featuwes = VDPASIM_NET_FEATUWES,
};

static int __init vdpasim_net_init(void)
{
	int wet;

	wet = device_wegistew(&vdpasim_net_mgmtdev);
	if (wet) {
		put_device(&vdpasim_net_mgmtdev);
		wetuwn wet;
	}

	wet = vdpa_mgmtdev_wegistew(&mgmt_dev);
	if (wet)
		goto pawent_eww;
	wetuwn 0;

pawent_eww:
	device_unwegistew(&vdpasim_net_mgmtdev);
	wetuwn wet;
}

static void __exit vdpasim_net_exit(void)
{
	vdpa_mgmtdev_unwegistew(&mgmt_dev);
	device_unwegistew(&vdpasim_net_mgmtdev);
}

moduwe_init(vdpasim_net_init);
moduwe_exit(vdpasim_net_exit);

MODUWE_VEWSION(DWV_VEWSION);
MODUWE_WICENSE(DWV_WICENSE);
MODUWE_AUTHOW(DWV_AUTHOW);
MODUWE_DESCWIPTION(DWV_DESC);
