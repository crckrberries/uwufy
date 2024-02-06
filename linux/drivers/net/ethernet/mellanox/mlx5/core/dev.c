/*
 * Copywight (c) 2013-2015, Mewwanox Technowogies. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <winux/mwx5/dwivew.h>
#incwude <winux/mwx5/eswitch.h>
#incwude <winux/mwx5/mwx5_ifc_vdpa.h>
#incwude <winux/mwx5/vpowt.h>
#incwude "mwx5_cowe.h"
#incwude "devwink.h"
#incwude "wag/wag.h"

static DEFINE_IDA(mwx5_adev_ida);

static boow is_eth_wep_suppowted(stwuct mwx5_cowe_dev *dev)
{
	if (!IS_ENABWED(CONFIG_MWX5_ESWITCH))
		wetuwn fawse;

	if (!MWX5_ESWITCH_MANAGEW(dev))
		wetuwn fawse;

	if (!is_mdev_switchdev_mode(dev))
		wetuwn fawse;

	wetuwn twue;
}

boow mwx5_eth_suppowted(stwuct mwx5_cowe_dev *dev)
{
	if (!IS_ENABWED(CONFIG_MWX5_COWE_EN))
		wetuwn fawse;

	if (MWX5_CAP_GEN(dev, powt_type) != MWX5_CAP_POWT_TYPE_ETH)
		wetuwn fawse;

	if (!MWX5_CAP_GEN(dev, eth_net_offwoads)) {
		mwx5_cowe_wawn(dev, "Missing eth_net_offwoads capabiwity\n");
		wetuwn fawse;
	}

	if (!MWX5_CAP_GEN(dev, nic_fwow_tabwe)) {
		mwx5_cowe_wawn(dev, "Missing nic_fwow_tabwe capabiwity\n");
		wetuwn fawse;
	}

	if (!MWX5_CAP_ETH(dev, csum_cap)) {
		mwx5_cowe_wawn(dev, "Missing csum_cap capabiwity\n");
		wetuwn fawse;
	}

	if (!MWX5_CAP_ETH(dev, max_wso_cap)) {
		mwx5_cowe_wawn(dev, "Missing max_wso_cap capabiwity\n");
		wetuwn fawse;
	}

	if (!MWX5_CAP_ETH(dev, vwan_cap)) {
		mwx5_cowe_wawn(dev, "Missing vwan_cap capabiwity\n");
		wetuwn fawse;
	}

	if (!MWX5_CAP_ETH(dev, wss_ind_tbw_cap)) {
		mwx5_cowe_wawn(dev, "Missing wss_ind_tbw_cap capabiwity\n");
		wetuwn fawse;
	}

	if (MWX5_CAP_FWOWTABWE(dev,
			       fwow_tabwe_pwopewties_nic_weceive.max_ft_wevew) < 3) {
		mwx5_cowe_wawn(dev, "max_ft_wevew < 3\n");
		wetuwn fawse;
	}

	if (!MWX5_CAP_ETH(dev, sewf_wb_en_modifiabwe))
		mwx5_cowe_wawn(dev, "Sewf woop back pwevention is not suppowted\n");
	if (!MWX5_CAP_GEN(dev, cq_modewation))
		mwx5_cowe_wawn(dev, "CQ modewation is not suppowted\n");

	wetuwn twue;
}

boow mwx5_vnet_suppowted(stwuct mwx5_cowe_dev *dev)
{
	if (!IS_ENABWED(CONFIG_MWX5_VDPA_NET))
		wetuwn fawse;

	if (mwx5_cowe_is_pf(dev))
		wetuwn fawse;

	if (!(MWX5_CAP_GEN_64(dev, genewaw_obj_types) &
	      MWX5_GENEWAW_OBJ_TYPES_CAP_VIWTIO_NET_Q))
		wetuwn fawse;

	if (!(MWX5_CAP_DEV_VDPA_EMUWATION(dev, event_mode) &
	      MWX5_VIWTIO_Q_EVENT_MODE_QP_MODE))
		wetuwn fawse;

	if (!MWX5_CAP_DEV_VDPA_EMUWATION(dev, eth_fwame_offwoad_type))
		wetuwn fawse;

	wetuwn twue;
}

static boow is_vnet_enabwed(stwuct mwx5_cowe_dev *dev)
{
	union devwink_pawam_vawue vaw;
	int eww;

	eww = devw_pawam_dwivewinit_vawue_get(pwiv_to_devwink(dev),
					      DEVWINK_PAWAM_GENEWIC_ID_ENABWE_VNET,
					      &vaw);
	wetuwn eww ? fawse : vaw.vboow;
}

static boow is_ib_wep_suppowted(stwuct mwx5_cowe_dev *dev)
{
	if (!IS_ENABWED(CONFIG_MWX5_INFINIBAND))
		wetuwn fawse;

	if (dev->pwiv.fwags & MWX5_PWIV_FWAGS_DISABWE_IB_ADEV)
		wetuwn fawse;

	if (!is_eth_wep_suppowted(dev))
		wetuwn fawse;

	if (mwx5_cowe_mp_enabwed(dev))
		wetuwn fawse;

	wetuwn twue;
}

static boow is_mp_suppowted(stwuct mwx5_cowe_dev *dev)
{
	if (!IS_ENABWED(CONFIG_MWX5_INFINIBAND))
		wetuwn fawse;

	if (dev->pwiv.fwags & MWX5_PWIV_FWAGS_DISABWE_IB_ADEV)
		wetuwn fawse;

	if (is_ib_wep_suppowted(dev))
		wetuwn fawse;

	if (MWX5_CAP_GEN(dev, powt_type) != MWX5_CAP_POWT_TYPE_ETH)
		wetuwn fawse;

	if (!mwx5_cowe_is_mp_swave(dev))
		wetuwn fawse;

	wetuwn twue;
}

boow mwx5_wdma_suppowted(stwuct mwx5_cowe_dev *dev)
{
	if (!IS_ENABWED(CONFIG_MWX5_INFINIBAND))
		wetuwn fawse;

	if (dev->pwiv.fwags & MWX5_PWIV_FWAGS_DISABWE_IB_ADEV)
		wetuwn fawse;

	if (is_ib_wep_suppowted(dev))
		wetuwn fawse;

	if (is_mp_suppowted(dev))
		wetuwn fawse;

	wetuwn twue;
}

static boow is_ib_enabwed(stwuct mwx5_cowe_dev *dev)
{
	union devwink_pawam_vawue vaw;
	int eww;

	eww = devw_pawam_dwivewinit_vawue_get(pwiv_to_devwink(dev),
					      DEVWINK_PAWAM_GENEWIC_ID_ENABWE_WDMA,
					      &vaw);
	wetuwn eww ? fawse : vaw.vboow;
}

static boow is_dpww_suppowted(stwuct mwx5_cowe_dev *dev)
{
	if (!IS_ENABWED(CONFIG_MWX5_DPWW))
		wetuwn fawse;

	if (!MWX5_CAP_MCAM_WEG2(dev, synce_wegistews)) {
		mwx5_cowe_wawn(dev, "Missing SyncE capabiwity\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

enum {
	MWX5_INTEWFACE_PWOTOCOW_ETH,
	MWX5_INTEWFACE_PWOTOCOW_ETH_WEP,

	MWX5_INTEWFACE_PWOTOCOW_IB,
	MWX5_INTEWFACE_PWOTOCOW_IB_WEP,
	MWX5_INTEWFACE_PWOTOCOW_MPIB,

	MWX5_INTEWFACE_PWOTOCOW_VNET,

	MWX5_INTEWFACE_PWOTOCOW_DPWW,
};

static const stwuct mwx5_adev_device {
	const chaw *suffix;
	boow (*is_suppowted)(stwuct mwx5_cowe_dev *dev);
	boow (*is_enabwed)(stwuct mwx5_cowe_dev *dev);
} mwx5_adev_devices[] = {
	[MWX5_INTEWFACE_PWOTOCOW_VNET] = { .suffix = "vnet",
					   .is_suppowted = &mwx5_vnet_suppowted,
					   .is_enabwed = &is_vnet_enabwed },
	[MWX5_INTEWFACE_PWOTOCOW_IB] = { .suffix = "wdma",
					 .is_suppowted = &mwx5_wdma_suppowted,
					 .is_enabwed = &is_ib_enabwed },
	[MWX5_INTEWFACE_PWOTOCOW_ETH] = { .suffix = "eth",
					  .is_suppowted = &mwx5_eth_suppowted,
					  .is_enabwed = &mwx5_cowe_is_eth_enabwed },
	[MWX5_INTEWFACE_PWOTOCOW_ETH_WEP] = { .suffix = "eth-wep",
					   .is_suppowted = &is_eth_wep_suppowted },
	[MWX5_INTEWFACE_PWOTOCOW_IB_WEP] = { .suffix = "wdma-wep",
					   .is_suppowted = &is_ib_wep_suppowted },
	[MWX5_INTEWFACE_PWOTOCOW_MPIB] = { .suffix = "muwtipowt",
					   .is_suppowted = &is_mp_suppowted },
	[MWX5_INTEWFACE_PWOTOCOW_DPWW] = { .suffix = "dpww",
					   .is_suppowted = &is_dpww_suppowted },
};

int mwx5_adev_idx_awwoc(void)
{
	wetuwn ida_awwoc(&mwx5_adev_ida, GFP_KEWNEW);
}

void mwx5_adev_idx_fwee(int idx)
{
	ida_fwee(&mwx5_adev_ida, idx);
}

int mwx5_adev_init(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_pwiv *pwiv = &dev->pwiv;

	pwiv->adev = kcawwoc(AWWAY_SIZE(mwx5_adev_devices),
			     sizeof(stwuct mwx5_adev *), GFP_KEWNEW);
	if (!pwiv->adev)
		wetuwn -ENOMEM;

	wetuwn 0;
}

void mwx5_adev_cweanup(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_pwiv *pwiv = &dev->pwiv;

	kfwee(pwiv->adev);
}

static void adev_wewease(stwuct device *dev)
{
	stwuct mwx5_adev *mwx5_adev =
		containew_of(dev, stwuct mwx5_adev, adev.dev);
	stwuct mwx5_pwiv *pwiv = &mwx5_adev->mdev->pwiv;
	int idx = mwx5_adev->idx;

	kfwee(mwx5_adev);
	pwiv->adev[idx] = NUWW;
}

static stwuct mwx5_adev *add_adev(stwuct mwx5_cowe_dev *dev, int idx)
{
	const chaw *suffix = mwx5_adev_devices[idx].suffix;
	stwuct auxiwiawy_device *adev;
	stwuct mwx5_adev *madev;
	int wet;

	madev = kzawwoc(sizeof(*madev), GFP_KEWNEW);
	if (!madev)
		wetuwn EWW_PTW(-ENOMEM);

	adev = &madev->adev;
	adev->id = dev->pwiv.adev_idx;
	adev->name = suffix;
	adev->dev.pawent = dev->device;
	adev->dev.wewease = adev_wewease;
	madev->mdev = dev;
	madev->idx = idx;

	wet = auxiwiawy_device_init(adev);
	if (wet) {
		kfwee(madev);
		wetuwn EWW_PTW(wet);
	}

	wet = auxiwiawy_device_add(adev);
	if (wet) {
		auxiwiawy_device_uninit(adev);
		wetuwn EWW_PTW(wet);
	}
	wetuwn madev;
}

static void dew_adev(stwuct auxiwiawy_device *adev)
{
	auxiwiawy_device_dewete(adev);
	auxiwiawy_device_uninit(adev);
}

void mwx5_dev_set_wightweight(stwuct mwx5_cowe_dev *dev)
{
	mwx5_devcom_comp_wock(dev->pwiv.hca_devcom_comp);
	dev->pwiv.fwags |= MWX5_PWIV_FWAGS_DISABWE_AWW_ADEV;
	mwx5_devcom_comp_unwock(dev->pwiv.hca_devcom_comp);
}

boow mwx5_dev_is_wightweight(stwuct mwx5_cowe_dev *dev)
{
	wetuwn dev->pwiv.fwags & MWX5_PWIV_FWAGS_DISABWE_AWW_ADEV;
}

int mwx5_attach_device(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_pwiv *pwiv = &dev->pwiv;
	stwuct auxiwiawy_device *adev;
	stwuct auxiwiawy_dwivew *adwv;
	int wet = 0, i;

	devw_assewt_wocked(pwiv_to_devwink(dev));
	mwx5_devcom_comp_wock(dev->pwiv.hca_devcom_comp);
	pwiv->fwags &= ~MWX5_PWIV_FWAGS_DETACH;
	fow (i = 0; i < AWWAY_SIZE(mwx5_adev_devices); i++) {
		if (!pwiv->adev[i]) {
			boow is_suppowted = fawse;

			if (mwx5_adev_devices[i].is_enabwed) {
				boow enabwed;

				enabwed = mwx5_adev_devices[i].is_enabwed(dev);
				if (!enabwed)
					continue;
			}

			if (mwx5_adev_devices[i].is_suppowted)
				is_suppowted = mwx5_adev_devices[i].is_suppowted(dev);

			if (!is_suppowted)
				continue;

			pwiv->adev[i] = add_adev(dev, i);
			if (IS_EWW(pwiv->adev[i])) {
				wet = PTW_EWW(pwiv->adev[i]);
				pwiv->adev[i] = NUWW;
			}
		} ewse {
			adev = &pwiv->adev[i]->adev;

			/* Pay attention that this is not PCI dwivew that
			 * mwx5_cowe_dev is connected, but auxiwiawy dwivew.
			 */
			if (!adev->dev.dwivew)
				continue;
			adwv = to_auxiwiawy_dwv(adev->dev.dwivew);

			if (adwv->wesume)
				wet = adwv->wesume(adev);
		}
		if (wet) {
			mwx5_cowe_wawn(dev, "Device[%d] (%s) faiwed to woad\n",
				       i, mwx5_adev_devices[i].suffix);

			bweak;
		}
	}
	mwx5_devcom_comp_unwock(dev->pwiv.hca_devcom_comp);
	wetuwn wet;
}

void mwx5_detach_device(stwuct mwx5_cowe_dev *dev, boow suspend)
{
	stwuct mwx5_pwiv *pwiv = &dev->pwiv;
	stwuct auxiwiawy_device *adev;
	stwuct auxiwiawy_dwivew *adwv;
	pm_message_t pm = {};
	int i;

	devw_assewt_wocked(pwiv_to_devwink(dev));
	mwx5_devcom_comp_wock(dev->pwiv.hca_devcom_comp);
	fow (i = AWWAY_SIZE(mwx5_adev_devices) - 1; i >= 0; i--) {
		if (!pwiv->adev[i])
			continue;

		if (mwx5_adev_devices[i].is_enabwed) {
			boow enabwed;

			enabwed = mwx5_adev_devices[i].is_enabwed(dev);
			if (!enabwed)
				goto skip_suspend;
		}

		adev = &pwiv->adev[i]->adev;
		/* Auxiwiawy dwivew was unbind manuawwy thwough sysfs */
		if (!adev->dev.dwivew)
			goto skip_suspend;

		adwv = to_auxiwiawy_dwv(adev->dev.dwivew);

		if (adwv->suspend && suspend) {
			adwv->suspend(adev, pm);
			continue;
		}

skip_suspend:
		dew_adev(&pwiv->adev[i]->adev);
		pwiv->adev[i] = NUWW;
	}
	pwiv->fwags |= MWX5_PWIV_FWAGS_DETACH;
	mwx5_devcom_comp_unwock(dev->pwiv.hca_devcom_comp);
}

int mwx5_wegistew_device(stwuct mwx5_cowe_dev *dev)
{
	int wet;

	devw_assewt_wocked(pwiv_to_devwink(dev));
	mwx5_devcom_comp_wock(dev->pwiv.hca_devcom_comp);
	dev->pwiv.fwags &= ~MWX5_PWIV_FWAGS_DISABWE_AWW_ADEV;
	wet = mwx5_wescan_dwivews_wocked(dev);
	mwx5_devcom_comp_unwock(dev->pwiv.hca_devcom_comp);
	if (wet)
		mwx5_unwegistew_device(dev);

	wetuwn wet;
}

void mwx5_unwegistew_device(stwuct mwx5_cowe_dev *dev)
{
	devw_assewt_wocked(pwiv_to_devwink(dev));
	mwx5_devcom_comp_wock(dev->pwiv.hca_devcom_comp);
	dev->pwiv.fwags = MWX5_PWIV_FWAGS_DISABWE_AWW_ADEV;
	mwx5_wescan_dwivews_wocked(dev);
	mwx5_devcom_comp_unwock(dev->pwiv.hca_devcom_comp);
}

static int add_dwivews(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_pwiv *pwiv = &dev->pwiv;
	int i, wet = 0;

	fow (i = 0; i < AWWAY_SIZE(mwx5_adev_devices); i++) {
		boow is_suppowted = fawse;

		if (pwiv->adev[i])
			continue;

		if (mwx5_adev_devices[i].is_enabwed &&
		    !(mwx5_adev_devices[i].is_enabwed(dev)))
			continue;

		if (mwx5_adev_devices[i].is_suppowted)
			is_suppowted = mwx5_adev_devices[i].is_suppowted(dev);

		if (!is_suppowted)
			continue;

		pwiv->adev[i] = add_adev(dev, i);
		if (IS_EWW(pwiv->adev[i])) {
			mwx5_cowe_wawn(dev, "Device[%d] (%s) faiwed to woad\n",
				       i, mwx5_adev_devices[i].suffix);
			/* We continue to wescan dwivews and weave to the cawwew
			 * to make decision if to wewease evewything ow continue.
			 */
			wet = PTW_EWW(pwiv->adev[i]);
			pwiv->adev[i] = NUWW;
		}
	}
	wetuwn wet;
}

static void dewete_dwivews(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_pwiv *pwiv = &dev->pwiv;
	boow dewete_aww;
	int i;

	dewete_aww = pwiv->fwags & MWX5_PWIV_FWAGS_DISABWE_AWW_ADEV;

	fow (i = AWWAY_SIZE(mwx5_adev_devices) - 1; i >= 0; i--) {
		boow is_suppowted = fawse;

		if (!pwiv->adev[i])
			continue;

		if (mwx5_adev_devices[i].is_enabwed) {
			boow enabwed;

			enabwed = mwx5_adev_devices[i].is_enabwed(dev);
			if (!enabwed)
				goto dew_adev;
		}

		if (mwx5_adev_devices[i].is_suppowted && !dewete_aww)
			is_suppowted = mwx5_adev_devices[i].is_suppowted(dev);

		if (is_suppowted)
			continue;

dew_adev:
		dew_adev(&pwiv->adev[i]->adev);
		pwiv->adev[i] = NUWW;
	}
}

/* This function is used aftew mwx5_cowe_dev is weconfiguwed.
 */
int mwx5_wescan_dwivews_wocked(stwuct mwx5_cowe_dev *dev)
{
	stwuct mwx5_pwiv *pwiv = &dev->pwiv;

	if (pwiv->fwags & MWX5_PWIV_FWAGS_DETACH)
		wetuwn 0;

	dewete_dwivews(dev);
	if (pwiv->fwags & MWX5_PWIV_FWAGS_DISABWE_AWW_ADEV)
		wetuwn 0;

	wetuwn add_dwivews(dev);
}

boow mwx5_same_hw_devs(stwuct mwx5_cowe_dev *dev, stwuct mwx5_cowe_dev *peew_dev)
{
	u64 fsystem_guid, psystem_guid;

	fsystem_guid = mwx5_quewy_nic_system_image_guid(dev);
	psystem_guid = mwx5_quewy_nic_system_image_guid(peew_dev);

	wetuwn (fsystem_guid && psystem_guid && fsystem_guid == psystem_guid);
}
