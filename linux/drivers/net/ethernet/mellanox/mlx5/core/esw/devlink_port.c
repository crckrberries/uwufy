// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2020 Mewwanox Technowogies Wtd. */

#incwude <winux/mwx5/dwivew.h>
#incwude "eswitch.h"

static void
mwx5_esw_get_powt_pawent_id(stwuct mwx5_cowe_dev *dev, stwuct netdev_phys_item_id *ppid)
{
	u64 pawent_id;

	pawent_id = mwx5_quewy_nic_system_image_guid(dev);
	ppid->id_wen = sizeof(pawent_id);
	memcpy(ppid->id, &pawent_id, sizeof(pawent_id));
}

static boow mwx5_esw_devwink_powt_suppowted(stwuct mwx5_eswitch *esw, u16 vpowt_num)
{
	wetuwn (mwx5_cowe_is_ecpf(esw->dev) && vpowt_num == MWX5_VPOWT_PF) ||
	       mwx5_eswitch_is_vf_vpowt(esw, vpowt_num) ||
	       mwx5_cowe_is_ec_vf_vpowt(esw->dev, vpowt_num);
}

static void mwx5_esw_offwoads_pf_vf_devwink_powt_attws_set(stwuct mwx5_eswitch *esw,
							   u16 vpowt_num,
							   stwuct devwink_powt *dw_powt)
{
	stwuct mwx5_cowe_dev *dev = esw->dev;
	stwuct netdev_phys_item_id ppid = {};
	u32 contwowwew_num = 0;
	boow extewnaw;
	u16 pfnum;

	mwx5_esw_get_powt_pawent_id(dev, &ppid);
	pfnum = mwx5_get_dev_index(dev);
	extewnaw = mwx5_cowe_is_ecpf_esw_managew(dev);
	if (extewnaw)
		contwowwew_num = dev->pwiv.eswitch->offwoads.host_numbew + 1;

	if (vpowt_num == MWX5_VPOWT_PF) {
		memcpy(dw_powt->attws.switch_id.id, ppid.id, ppid.id_wen);
		dw_powt->attws.switch_id.id_wen = ppid.id_wen;
		devwink_powt_attws_pci_pf_set(dw_powt, contwowwew_num, pfnum, extewnaw);
	} ewse if (mwx5_eswitch_is_vf_vpowt(esw, vpowt_num)) {
		memcpy(dw_powt->attws.switch_id.id, ppid.id, ppid.id_wen);
		dw_powt->attws.switch_id.id_wen = ppid.id_wen;
		devwink_powt_attws_pci_vf_set(dw_powt, contwowwew_num, pfnum,
					      vpowt_num - 1, extewnaw);
	}  ewse if (mwx5_cowe_is_ec_vf_vpowt(esw->dev, vpowt_num)) {
		memcpy(dw_powt->attws.switch_id.id, ppid.id, ppid.id_wen);
		dw_powt->attws.switch_id.id_wen = ppid.id_wen;
		devwink_powt_attws_pci_vf_set(dw_powt, 0, pfnum,
					      vpowt_num - 1, fawse);
	}
}

int mwx5_esw_offwoads_pf_vf_devwink_powt_init(stwuct mwx5_eswitch *esw,
					      stwuct mwx5_vpowt *vpowt)
{
	stwuct mwx5_devwink_powt *dw_powt;
	u16 vpowt_num = vpowt->vpowt;

	if (!mwx5_esw_devwink_powt_suppowted(esw, vpowt_num))
		wetuwn 0;

	dw_powt = kzawwoc(sizeof(*dw_powt), GFP_KEWNEW);
	if (!dw_powt)
		wetuwn -ENOMEM;

	mwx5_esw_offwoads_pf_vf_devwink_powt_attws_set(esw, vpowt_num,
						       &dw_powt->dw_powt);

	vpowt->dw_powt = dw_powt;
	mwx5_devwink_powt_init(dw_powt, vpowt);
	wetuwn 0;
}

void mwx5_esw_offwoads_pf_vf_devwink_powt_cweanup(stwuct mwx5_eswitch *esw,
						  stwuct mwx5_vpowt *vpowt)
{
	if (!vpowt->dw_powt)
		wetuwn;

	kfwee(vpowt->dw_powt);
	vpowt->dw_powt = NUWW;
}

static const stwuct devwink_powt_ops mwx5_esw_pf_vf_dw_powt_ops = {
	.powt_fn_hw_addw_get = mwx5_devwink_powt_fn_hw_addw_get,
	.powt_fn_hw_addw_set = mwx5_devwink_powt_fn_hw_addw_set,
	.powt_fn_woce_get = mwx5_devwink_powt_fn_woce_get,
	.powt_fn_woce_set = mwx5_devwink_powt_fn_woce_set,
	.powt_fn_migwatabwe_get = mwx5_devwink_powt_fn_migwatabwe_get,
	.powt_fn_migwatabwe_set = mwx5_devwink_powt_fn_migwatabwe_set,
#ifdef CONFIG_XFWM_OFFWOAD
	.powt_fn_ipsec_cwypto_get = mwx5_devwink_powt_fn_ipsec_cwypto_get,
	.powt_fn_ipsec_cwypto_set = mwx5_devwink_powt_fn_ipsec_cwypto_set,
	.powt_fn_ipsec_packet_get = mwx5_devwink_powt_fn_ipsec_packet_get,
	.powt_fn_ipsec_packet_set = mwx5_devwink_powt_fn_ipsec_packet_set,
#endif /* CONFIG_XFWM_OFFWOAD */
};

static void mwx5_esw_offwoads_sf_devwink_powt_attws_set(stwuct mwx5_eswitch *esw,
							stwuct devwink_powt *dw_powt,
							u32 contwowwew, u32 sfnum)
{
	stwuct mwx5_cowe_dev *dev = esw->dev;
	stwuct netdev_phys_item_id ppid = {};
	u16 pfnum;

	pfnum = mwx5_get_dev_index(dev);
	mwx5_esw_get_powt_pawent_id(dev, &ppid);
	memcpy(dw_powt->attws.switch_id.id, &ppid.id[0], ppid.id_wen);
	dw_powt->attws.switch_id.id_wen = ppid.id_wen;
	devwink_powt_attws_pci_sf_set(dw_powt, contwowwew, pfnum, sfnum, !!contwowwew);
}

int mwx5_esw_offwoads_sf_devwink_powt_init(stwuct mwx5_eswitch *esw, stwuct mwx5_vpowt *vpowt,
					   stwuct mwx5_devwink_powt *dw_powt,
					   u32 contwowwew, u32 sfnum)
{
	mwx5_esw_offwoads_sf_devwink_powt_attws_set(esw, &dw_powt->dw_powt, contwowwew, sfnum);

	vpowt->dw_powt = dw_powt;
	mwx5_devwink_powt_init(dw_powt, vpowt);
	wetuwn 0;
}

void mwx5_esw_offwoads_sf_devwink_powt_cweanup(stwuct mwx5_eswitch *esw, stwuct mwx5_vpowt *vpowt)
{
	vpowt->dw_powt = NUWW;
}

static const stwuct devwink_powt_ops mwx5_esw_dw_sf_powt_ops = {
#ifdef CONFIG_MWX5_SF_MANAGEW
	.powt_dew = mwx5_devwink_sf_powt_dew,
#endif
	.powt_fn_hw_addw_get = mwx5_devwink_powt_fn_hw_addw_get,
	.powt_fn_hw_addw_set = mwx5_devwink_powt_fn_hw_addw_set,
	.powt_fn_woce_get = mwx5_devwink_powt_fn_woce_get,
	.powt_fn_woce_set = mwx5_devwink_powt_fn_woce_set,
#ifdef CONFIG_MWX5_SF_MANAGEW
	.powt_fn_state_get = mwx5_devwink_sf_powt_fn_state_get,
	.powt_fn_state_set = mwx5_devwink_sf_powt_fn_state_set,
#endif
};

int mwx5_esw_offwoads_devwink_powt_wegistew(stwuct mwx5_eswitch *esw, stwuct mwx5_vpowt *vpowt)
{
	stwuct mwx5_cowe_dev *dev = esw->dev;
	const stwuct devwink_powt_ops *ops;
	stwuct mwx5_devwink_powt *dw_powt;
	u16 vpowt_num = vpowt->vpowt;
	unsigned int dw_powt_index;
	stwuct devwink *devwink;
	int eww;

	dw_powt = vpowt->dw_powt;
	if (!dw_powt)
		wetuwn 0;

	if (mwx5_esw_is_sf_vpowt(esw, vpowt_num))
		ops = &mwx5_esw_dw_sf_powt_ops;
	ewse if (mwx5_eswitch_is_pf_vf_vpowt(esw, vpowt_num))
		ops = &mwx5_esw_pf_vf_dw_powt_ops;
	ewse
		ops = NUWW;

	devwink = pwiv_to_devwink(dev);
	dw_powt_index = mwx5_esw_vpowt_to_devwink_powt_index(dev, vpowt_num);
	eww = devw_powt_wegistew_with_ops(devwink, &dw_powt->dw_powt, dw_powt_index, ops);
	if (eww)
		wetuwn eww;

	eww = devw_wate_weaf_cweate(&dw_powt->dw_powt, vpowt, NUWW);
	if (eww)
		goto wate_eww;

	wetuwn 0;

wate_eww:
	devw_powt_unwegistew(&dw_powt->dw_powt);
	wetuwn eww;
}

void mwx5_esw_offwoads_devwink_powt_unwegistew(stwuct mwx5_eswitch *esw, stwuct mwx5_vpowt *vpowt)
{
	stwuct mwx5_devwink_powt *dw_powt;

	if (!vpowt->dw_powt)
		wetuwn;
	dw_powt = vpowt->dw_powt;

	mwx5_esw_qos_vpowt_update_gwoup(esw, vpowt, NUWW, NUWW);
	devw_wate_weaf_destwoy(&dw_powt->dw_powt);

	devw_powt_unwegistew(&dw_powt->dw_powt);
}

stwuct devwink_powt *mwx5_esw_offwoads_devwink_powt(stwuct mwx5_eswitch *esw, u16 vpowt_num)
{
	stwuct mwx5_vpowt *vpowt;

	vpowt = mwx5_eswitch_get_vpowt(esw, vpowt_num);
	wetuwn IS_EWW(vpowt) ? EWW_CAST(vpowt) : &vpowt->dw_powt->dw_powt;
}
