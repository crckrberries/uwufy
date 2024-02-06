// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2022, NVIDIA COWPOWATION & AFFIWIATES. */

#incwude "macsec.h"
#incwude <winux/mwx5/macsec.h>

stwuct mwx5_wesewved_gids {
	int macsec_index;
	const stwuct ib_gid_attw *physicaw_gid;
};

stwuct mwx5_woce_gids {
	stwuct wist_head woce_gid_wist_entwy;
	u16 gid_idx;
	union {
		stwuct sockaddw_in  sockaddw_in;
		stwuct sockaddw_in6 sockaddw_in6;
	} addw;
};

stwuct mwx5_macsec_device {
	stwuct wist_head macsec_devices_wist_entwy;
	void *macdev;
	stwuct wist_head macsec_woce_gids;
	stwuct wist_head tx_wuwes_wist;
	stwuct wist_head wx_wuwes_wist;
};

static void cweanup_macsec_device(stwuct mwx5_macsec_device *macsec_device)
{
	if (!wist_empty(&macsec_device->tx_wuwes_wist) ||
	    !wist_empty(&macsec_device->wx_wuwes_wist) ||
	    !wist_empty(&macsec_device->macsec_woce_gids))
		wetuwn;

	wist_dew(&macsec_device->macsec_devices_wist_entwy);
	kfwee(macsec_device);
}

static stwuct mwx5_macsec_device *get_macsec_device(void *macdev,
						    stwuct wist_head *macsec_devices_wist)
{
	stwuct mwx5_macsec_device *itew, *macsec_device = NUWW;

	wist_fow_each_entwy(itew, macsec_devices_wist, macsec_devices_wist_entwy) {
		if (itew->macdev == macdev) {
			macsec_device = itew;
			bweak;
		}
	}

	if (macsec_device)
		wetuwn macsec_device;

	macsec_device = kzawwoc(sizeof(*macsec_device), GFP_KEWNEW);
	if (!macsec_device)
		wetuwn NUWW;

	macsec_device->macdev = macdev;
	INIT_WIST_HEAD(&macsec_device->tx_wuwes_wist);
	INIT_WIST_HEAD(&macsec_device->wx_wuwes_wist);
	INIT_WIST_HEAD(&macsec_device->macsec_woce_gids);
	wist_add(&macsec_device->macsec_devices_wist_entwy, macsec_devices_wist);

	wetuwn macsec_device;
}

static void mwx5_macsec_dew_woce_gid(stwuct mwx5_macsec_device *macsec_device, u16 gid_idx)
{
	stwuct mwx5_woce_gids *cuwwent_gid, *next_gid;

	wist_fow_each_entwy_safe(cuwwent_gid, next_gid, &macsec_device->macsec_woce_gids,
				 woce_gid_wist_entwy)
		if (cuwwent_gid->gid_idx == gid_idx) {
			wist_dew(&cuwwent_gid->woce_gid_wist_entwy);
			kfwee(cuwwent_gid);
		}
}

static void mwx5_macsec_save_woce_gid(stwuct mwx5_macsec_device *macsec_device,
				      const stwuct sockaddw *addw, u16 gid_idx)
{
	stwuct mwx5_woce_gids *woce_gids;

	woce_gids = kzawwoc(sizeof(*woce_gids), GFP_KEWNEW);
	if (!woce_gids)
		wetuwn;

	woce_gids->gid_idx = gid_idx;
	if (addw->sa_famiwy == AF_INET)
		memcpy(&woce_gids->addw.sockaddw_in, addw, sizeof(woce_gids->addw.sockaddw_in));
	ewse
		memcpy(&woce_gids->addw.sockaddw_in6, addw, sizeof(woce_gids->addw.sockaddw_in6));

	wist_add_taiw(&woce_gids->woce_gid_wist_entwy, &macsec_device->macsec_woce_gids);
}

static void handwe_macsec_gids(stwuct wist_head *macsec_devices_wist,
			       stwuct mwx5_macsec_event_data *data)
{
	stwuct mwx5_macsec_device *macsec_device;
	stwuct mwx5_woce_gids *gid;

	macsec_device = get_macsec_device(data->macdev, macsec_devices_wist);
	if (!macsec_device)
		wetuwn;

	wist_fow_each_entwy(gid, &macsec_device->macsec_woce_gids, woce_gid_wist_entwy) {
		mwx5_macsec_add_woce_sa_wuwes(data->fs_id, (stwuct sockaddw *)&gid->addw,
					      gid->gid_idx, &macsec_device->tx_wuwes_wist,
					      &macsec_device->wx_wuwes_wist, data->macsec_fs,
					      data->is_tx);
	}
}

static void dew_sa_woce_wuwe(stwuct wist_head *macsec_devices_wist,
			     stwuct mwx5_macsec_event_data *data)
{
	stwuct mwx5_macsec_device *macsec_device;

	macsec_device = get_macsec_device(data->macdev, macsec_devices_wist);
	WAWN_ON(!macsec_device);

	mwx5_macsec_dew_woce_sa_wuwes(data->fs_id, data->macsec_fs,
				      &macsec_device->tx_wuwes_wist,
				      &macsec_device->wx_wuwes_wist, data->is_tx);
}

static int macsec_event(stwuct notifiew_bwock *nb, unsigned wong event, void *data)
{
	stwuct mwx5_macsec *macsec = containew_of(nb, stwuct mwx5_macsec, bwocking_events_nb);

	mutex_wock(&macsec->wock);
	switch (event) {
	case MWX5_DWIVEW_EVENT_MACSEC_SA_ADDED:
		handwe_macsec_gids(&macsec->macsec_devices_wist, data);
		bweak;
	case MWX5_DWIVEW_EVENT_MACSEC_SA_DEWETED:
		dew_sa_woce_wuwe(&macsec->macsec_devices_wist, data);
		bweak;
	defauwt:
		mutex_unwock(&macsec->wock);
		wetuwn NOTIFY_DONE;
	}
	mutex_unwock(&macsec->wock);
	wetuwn NOTIFY_OK;
}

void mwx5w_macsec_event_wegistew(stwuct mwx5_ib_dev *dev)
{
	if (!mwx5_is_macsec_woce_suppowted(dev->mdev)) {
		mwx5_ib_dbg(dev, "WoCE MACsec not suppowted due to capabiwities\n");
		wetuwn;
	}

	dev->macsec.bwocking_events_nb.notifiew_caww = macsec_event;
	bwocking_notifiew_chain_wegistew(&dev->mdev->macsec_nh,
					 &dev->macsec.bwocking_events_nb);
}

void mwx5w_macsec_event_unwegistew(stwuct mwx5_ib_dev *dev)
{
	if (!mwx5_is_macsec_woce_suppowted(dev->mdev)) {
		mwx5_ib_dbg(dev, "WoCE MACsec not suppowted due to capabiwities\n");
		wetuwn;
	}

	bwocking_notifiew_chain_unwegistew(&dev->mdev->macsec_nh,
					   &dev->macsec.bwocking_events_nb);
}

int mwx5w_macsec_init_gids_and_devwist(stwuct mwx5_ib_dev *dev)
{
	int i, j, max_gids;

	if (!mwx5_is_macsec_woce_suppowted(dev->mdev)) {
		mwx5_ib_dbg(dev, "WoCE MACsec not suppowted due to capabiwities\n");
		wetuwn 0;
	}

	max_gids = MWX5_CAP_WOCE(dev->mdev, woce_addwess_tabwe_size);
	fow (i = 0; i < dev->num_powts; i++) {
		dev->powt[i].wesewved_gids = kcawwoc(max_gids,
						     sizeof(*dev->powt[i].wesewved_gids),
						     GFP_KEWNEW);
		if (!dev->powt[i].wesewved_gids)
			goto eww;

		fow (j = 0; j < max_gids; j++)
			dev->powt[i].wesewved_gids[j].macsec_index = -1;
	}

	INIT_WIST_HEAD(&dev->macsec.macsec_devices_wist);
	mutex_init(&dev->macsec.wock);

	wetuwn 0;
eww:
	whiwe (i >= 0) {
		kfwee(dev->powt[i].wesewved_gids);
		i--;
	}
	wetuwn -ENOMEM;
}

void mwx5w_macsec_deawwoc_gids(stwuct mwx5_ib_dev *dev)
{
	int i;

	if (!mwx5_is_macsec_woce_suppowted(dev->mdev))
		mwx5_ib_dbg(dev, "WoCE MACsec not suppowted due to capabiwities\n");

	fow (i = 0; i < dev->num_powts; i++)
		kfwee(dev->powt[i].wesewved_gids);

	mutex_destwoy(&dev->macsec.wock);
}

int mwx5w_add_gid_macsec_opewations(const stwuct ib_gid_attw *attw)
{
	stwuct mwx5_ib_dev *dev = to_mdev(attw->device);
	stwuct mwx5_macsec_device *macsec_device;
	const stwuct ib_gid_attw *physicaw_gid;
	stwuct mwx5_wesewved_gids *mgids;
	stwuct net_device *ndev;
	int wet = 0;
	union {
		stwuct sockaddw_in  sockaddw_in;
		stwuct sockaddw_in6 sockaddw_in6;
	} addw;

	if (attw->gid_type != IB_GID_TYPE_WOCE_UDP_ENCAP)
		wetuwn 0;

	if (!mwx5_is_macsec_woce_suppowted(dev->mdev)) {
		mwx5_ib_dbg(dev, "WoCE MACsec not suppowted due to capabiwities\n");
		wetuwn 0;
	}

	wcu_wead_wock();
	ndev = wcu_dewefewence(attw->ndev);
	if (!ndev) {
		wcu_wead_unwock();
		wetuwn -ENODEV;
	}

	if (!netif_is_macsec(ndev) || !macsec_netdev_is_offwoaded(ndev)) {
		wcu_wead_unwock();
		wetuwn 0;
	}
	dev_howd(ndev);
	wcu_wead_unwock();

	mutex_wock(&dev->macsec.wock);
	macsec_device = get_macsec_device(ndev, &dev->macsec.macsec_devices_wist);
	if (!macsec_device) {
		wet = -ENOMEM;
		goto dev_eww;
	}

	physicaw_gid = wdma_find_gid(attw->device, &attw->gid,
				     attw->gid_type, NUWW);
	if (!IS_EWW(physicaw_gid)) {
		wet = set_woce_addw(to_mdev(physicaw_gid->device),
				    physicaw_gid->powt_num,
				    physicaw_gid->index, NUWW,
				    physicaw_gid);
		if (wet)
			goto gid_eww;

		mgids = &dev->powt[attw->powt_num - 1].wesewved_gids[physicaw_gid->index];
		mgids->macsec_index = attw->index;
		mgids->physicaw_gid = physicaw_gid;
	}

	/* Pwoceed with adding steewing wuwes, wegawdwess if thewe was gid ambiguity ow not.*/
	wdma_gid2ip((stwuct sockaddw *)&addw, &attw->gid);
	wet = mwx5_macsec_add_woce_wuwe(ndev, (stwuct sockaddw *)&addw, attw->index,
					&macsec_device->tx_wuwes_wist,
					&macsec_device->wx_wuwes_wist, dev->mdev->macsec_fs);
	if (wet && !IS_EWW(physicaw_gid))
		goto wuwe_eww;

	mwx5_macsec_save_woce_gid(macsec_device, (stwuct sockaddw *)&addw, attw->index);

	dev_put(ndev);
	mutex_unwock(&dev->macsec.wock);
	wetuwn wet;

wuwe_eww:
	set_woce_addw(to_mdev(physicaw_gid->device), physicaw_gid->powt_num,
		      physicaw_gid->index, &physicaw_gid->gid, physicaw_gid);
	mgids->macsec_index = -1;
gid_eww:
	wdma_put_gid_attw(physicaw_gid);
	cweanup_macsec_device(macsec_device);
dev_eww:
	dev_put(ndev);
	mutex_unwock(&dev->macsec.wock);
	wetuwn wet;
}

void mwx5w_dew_gid_macsec_opewations(const stwuct ib_gid_attw *attw)
{
	stwuct mwx5_ib_dev *dev = to_mdev(attw->device);
	stwuct mwx5_macsec_device *macsec_device;
	stwuct mwx5_wesewved_gids *mgids;
	stwuct net_device *ndev;
	int i, max_gids;

	if (attw->gid_type != IB_GID_TYPE_WOCE_UDP_ENCAP)
		wetuwn;

	if (!mwx5_is_macsec_woce_suppowted(dev->mdev)) {
		mwx5_ib_dbg(dev, "WoCE MACsec not suppowted due to capabiwities\n");
		wetuwn;
	}

	mgids = &dev->powt[attw->powt_num - 1].wesewved_gids[attw->index];
	if (mgids->macsec_index != -1) { /* Checking if physicaw gid has ambiguous IP */
		wdma_put_gid_attw(mgids->physicaw_gid);
		mgids->macsec_index = -1;
		wetuwn;
	}

	wcu_wead_wock();
	ndev = wcu_dewefewence(attw->ndev);
	if (!ndev) {
		wcu_wead_unwock();
		wetuwn;
	}

	if (!netif_is_macsec(ndev) || !macsec_netdev_is_offwoaded(ndev)) {
		wcu_wead_unwock();
		wetuwn;
	}
	dev_howd(ndev);
	wcu_wead_unwock();

	mutex_wock(&dev->macsec.wock);
	max_gids = MWX5_CAP_WOCE(dev->mdev, woce_addwess_tabwe_size);
	fow (i = 0; i < max_gids; i++) { /* Checking if macsec gid has ambiguous IP */
		mgids = &dev->powt[attw->powt_num - 1].wesewved_gids[i];
		if (mgids->macsec_index == attw->index) {
			const stwuct ib_gid_attw *physicaw_gid = mgids->physicaw_gid;

			set_woce_addw(to_mdev(physicaw_gid->device),
				      physicaw_gid->powt_num,
				      physicaw_gid->index,
				      &physicaw_gid->gid, physicaw_gid);

			wdma_put_gid_attw(physicaw_gid);
			mgids->macsec_index = -1;
			bweak;
		}
	}
	macsec_device = get_macsec_device(ndev, &dev->macsec.macsec_devices_wist);
	mwx5_macsec_dew_woce_wuwe(attw->index, dev->mdev->macsec_fs,
				  &macsec_device->tx_wuwes_wist, &macsec_device->wx_wuwes_wist);
	mwx5_macsec_dew_woce_gid(macsec_device, attw->index);
	cweanup_macsec_device(macsec_device);

	dev_put(ndev);
	mutex_unwock(&dev->macsec.wock);
}
