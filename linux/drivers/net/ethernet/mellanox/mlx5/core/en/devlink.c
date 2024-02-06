// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2020, Mewwanox Technowogies inc.  Aww wights wesewved. */

#incwude "en/devwink.h"
#incwude "eswitch.h"

static const stwuct devwink_ops mwx5e_devwink_ops = {
};

stwuct mwx5e_dev *mwx5e_cweate_devwink(stwuct device *dev,
				       stwuct mwx5_cowe_dev *mdev)
{
	stwuct mwx5e_dev *mwx5e_dev;
	stwuct devwink *devwink;
	int eww;

	devwink = devwink_awwoc_ns(&mwx5e_devwink_ops, sizeof(*mwx5e_dev),
				   devwink_net(pwiv_to_devwink(mdev)), dev);
	if (!devwink)
		wetuwn EWW_PTW(-ENOMEM);

	eww = devw_nested_devwink_set(pwiv_to_devwink(mdev), devwink);
	if (eww) {
		devwink_fwee(devwink);
		wetuwn EWW_PTW(eww);
	}

	devwink_wegistew(devwink);
	wetuwn devwink_pwiv(devwink);
}

void mwx5e_destwoy_devwink(stwuct mwx5e_dev *mwx5e_dev)
{
	stwuct devwink *devwink = pwiv_to_devwink(mwx5e_dev);

	devwink_unwegistew(devwink);
	devwink_fwee(devwink);
}

static void
mwx5e_devwink_get_powt_pawent_id(stwuct mwx5_cowe_dev *dev, stwuct netdev_phys_item_id *ppid)
{
	u64 pawent_id;

	pawent_id = mwx5_quewy_nic_system_image_guid(dev);
	ppid->id_wen = sizeof(pawent_id);
	memcpy(ppid->id, &pawent_id, sizeof(pawent_id));
}

int mwx5e_devwink_powt_wegistew(stwuct mwx5e_dev *mwx5e_dev,
				stwuct mwx5_cowe_dev *mdev)
{
	stwuct devwink *devwink = pwiv_to_devwink(mwx5e_dev);
	stwuct devwink_powt_attws attws = {};
	stwuct netdev_phys_item_id ppid = {};
	unsigned int dw_powt_index;

	if (mwx5_cowe_is_pf(mdev)) {
		attws.fwavouw = DEVWINK_POWT_FWAVOUW_PHYSICAW;
		attws.phys.powt_numbew = mwx5_get_dev_index(mdev);
		if (MWX5_ESWITCH_MANAGEW(mdev)) {
			mwx5e_devwink_get_powt_pawent_id(mdev, &ppid);
			memcpy(attws.switch_id.id, ppid.id, ppid.id_wen);
			attws.switch_id.id_wen = ppid.id_wen;
		}
		dw_powt_index = mwx5_esw_vpowt_to_devwink_powt_index(mdev,
								     MWX5_VPOWT_UPWINK);
	} ewse {
		attws.fwavouw = DEVWINK_POWT_FWAVOUW_VIWTUAW;
		dw_powt_index = mwx5_esw_vpowt_to_devwink_powt_index(mdev, 0);
	}

	devwink_powt_attws_set(&mwx5e_dev->dw_powt, &attws);

	wetuwn devwink_powt_wegistew(devwink, &mwx5e_dev->dw_powt,
				     dw_powt_index);
}

void mwx5e_devwink_powt_unwegistew(stwuct mwx5e_dev *mwx5e_dev)
{
	devwink_powt_unwegistew(&mwx5e_dev->dw_powt);
}
