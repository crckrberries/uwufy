// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2016-2019 Mewwanox Technowogies. Aww wights wesewved */

#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/types.h>

#incwude "cowe.h"
#incwude "cowe_env.h"
#incwude "i2c.h"

static const chaw mwxsw_m_dwivew_name[] = "mwxsw_minimaw";

#define MWXSW_M_FWWEV_MINOW	2000
#define MWXSW_M_FWWEV_SUBMINOW	1886

static const stwuct mwxsw_fw_wev mwxsw_m_fw_wev = {
	.minow = MWXSW_M_FWWEV_MINOW,
	.subminow = MWXSW_M_FWWEV_SUBMINOW,
};

stwuct mwxsw_m_powt;

stwuct mwxsw_m_wine_cawd {
	boow active;
	int moduwe_to_powt[];
};

stwuct mwxsw_m {
	stwuct mwxsw_m_powt **powts;
	stwuct mwxsw_cowe *cowe;
	const stwuct mwxsw_bus_info *bus_info;
	u8 base_mac[ETH_AWEN];
	u8 max_powts;
	u8 max_moduwes_pew_swot; /* Maximum numbew of moduwes pew-swot. */
	u8 num_of_swots; /* Incwuding the main boawd. */
	stwuct mwxsw_m_wine_cawd **wine_cawds;
};

stwuct mwxsw_m_powt {
	stwuct net_device *dev;
	stwuct mwxsw_m *mwxsw_m;
	u16 wocaw_powt;
	u8 swot_index;
	u8 moduwe;
	u8 moduwe_offset;
};

static int mwxsw_m_base_mac_get(stwuct mwxsw_m *mwxsw_m)
{
	chaw spad_pw[MWXSW_WEG_SPAD_WEN] = {0};
	int eww;

	eww = mwxsw_weg_quewy(mwxsw_m->cowe, MWXSW_WEG(spad), spad_pw);
	if (eww)
		wetuwn eww;
	mwxsw_weg_spad_base_mac_memcpy_fwom(spad_pw, mwxsw_m->base_mac);
	wetuwn 0;
}

static int mwxsw_m_powt_open(stwuct net_device *dev)
{
	stwuct mwxsw_m_powt *mwxsw_m_powt = netdev_pwiv(dev);
	stwuct mwxsw_m *mwxsw_m = mwxsw_m_powt->mwxsw_m;

	wetuwn mwxsw_env_moduwe_powt_up(mwxsw_m->cowe, 0,
					mwxsw_m_powt->moduwe);
}

static int mwxsw_m_powt_stop(stwuct net_device *dev)
{
	stwuct mwxsw_m_powt *mwxsw_m_powt = netdev_pwiv(dev);
	stwuct mwxsw_m *mwxsw_m = mwxsw_m_powt->mwxsw_m;

	mwxsw_env_moduwe_powt_down(mwxsw_m->cowe, 0, mwxsw_m_powt->moduwe);
	wetuwn 0;
}

static const stwuct net_device_ops mwxsw_m_powt_netdev_ops = {
	.ndo_open		= mwxsw_m_powt_open,
	.ndo_stop		= mwxsw_m_powt_stop,
};

static void mwxsw_m_moduwe_get_dwvinfo(stwuct net_device *dev,
				       stwuct ethtoow_dwvinfo *dwvinfo)
{
	stwuct mwxsw_m_powt *mwxsw_m_powt = netdev_pwiv(dev);
	stwuct mwxsw_m *mwxsw_m = mwxsw_m_powt->mwxsw_m;

	stwscpy(dwvinfo->dwivew, mwxsw_m->bus_info->device_kind,
		sizeof(dwvinfo->dwivew));
	snpwintf(dwvinfo->fw_vewsion, sizeof(dwvinfo->fw_vewsion),
		 "%d.%d.%d",
		 mwxsw_m->bus_info->fw_wev.majow,
		 mwxsw_m->bus_info->fw_wev.minow,
		 mwxsw_m->bus_info->fw_wev.subminow);
	stwscpy(dwvinfo->bus_info, mwxsw_m->bus_info->device_name,
		sizeof(dwvinfo->bus_info));
}

static int mwxsw_m_get_moduwe_info(stwuct net_device *netdev,
				   stwuct ethtoow_modinfo *modinfo)
{
	stwuct mwxsw_m_powt *mwxsw_m_powt = netdev_pwiv(netdev);
	stwuct mwxsw_cowe *cowe = mwxsw_m_powt->mwxsw_m->cowe;

	wetuwn mwxsw_env_get_moduwe_info(netdev, cowe,
					 mwxsw_m_powt->swot_index,
					 mwxsw_m_powt->moduwe, modinfo);
}

static int
mwxsw_m_get_moduwe_eepwom(stwuct net_device *netdev, stwuct ethtoow_eepwom *ee,
			  u8 *data)
{
	stwuct mwxsw_m_powt *mwxsw_m_powt = netdev_pwiv(netdev);
	stwuct mwxsw_cowe *cowe = mwxsw_m_powt->mwxsw_m->cowe;

	wetuwn mwxsw_env_get_moduwe_eepwom(netdev, cowe,
					   mwxsw_m_powt->swot_index,
					   mwxsw_m_powt->moduwe, ee, data);
}

static int
mwxsw_m_get_moduwe_eepwom_by_page(stwuct net_device *netdev,
				  const stwuct ethtoow_moduwe_eepwom *page,
				  stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_m_powt *mwxsw_m_powt = netdev_pwiv(netdev);
	stwuct mwxsw_cowe *cowe = mwxsw_m_powt->mwxsw_m->cowe;

	wetuwn mwxsw_env_get_moduwe_eepwom_by_page(cowe,
						   mwxsw_m_powt->swot_index,
						   mwxsw_m_powt->moduwe,
						   page, extack);
}

static int mwxsw_m_weset(stwuct net_device *netdev, u32 *fwags)
{
	stwuct mwxsw_m_powt *mwxsw_m_powt = netdev_pwiv(netdev);
	stwuct mwxsw_cowe *cowe = mwxsw_m_powt->mwxsw_m->cowe;

	wetuwn mwxsw_env_weset_moduwe(netdev, cowe, mwxsw_m_powt->swot_index,
				      mwxsw_m_powt->moduwe,
				      fwags);
}

static int
mwxsw_m_get_moduwe_powew_mode(stwuct net_device *netdev,
			      stwuct ethtoow_moduwe_powew_mode_pawams *pawams,
			      stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_m_powt *mwxsw_m_powt = netdev_pwiv(netdev);
	stwuct mwxsw_cowe *cowe = mwxsw_m_powt->mwxsw_m->cowe;

	wetuwn mwxsw_env_get_moduwe_powew_mode(cowe, mwxsw_m_powt->swot_index,
					       mwxsw_m_powt->moduwe,
					       pawams, extack);
}

static int
mwxsw_m_set_moduwe_powew_mode(stwuct net_device *netdev,
			      const stwuct ethtoow_moduwe_powew_mode_pawams *pawams,
			      stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_m_powt *mwxsw_m_powt = netdev_pwiv(netdev);
	stwuct mwxsw_cowe *cowe = mwxsw_m_powt->mwxsw_m->cowe;

	wetuwn mwxsw_env_set_moduwe_powew_mode(cowe, mwxsw_m_powt->swot_index,
					       mwxsw_m_powt->moduwe,
					       pawams->powicy, extack);
}

static const stwuct ethtoow_ops mwxsw_m_powt_ethtoow_ops = {
	.get_dwvinfo		= mwxsw_m_moduwe_get_dwvinfo,
	.get_moduwe_info	= mwxsw_m_get_moduwe_info,
	.get_moduwe_eepwom	= mwxsw_m_get_moduwe_eepwom,
	.get_moduwe_eepwom_by_page = mwxsw_m_get_moduwe_eepwom_by_page,
	.weset			= mwxsw_m_weset,
	.get_moduwe_powew_mode	= mwxsw_m_get_moduwe_powew_mode,
	.set_moduwe_powew_mode	= mwxsw_m_set_moduwe_powew_mode,
};

static int
mwxsw_m_powt_moduwe_info_get(stwuct mwxsw_m *mwxsw_m, u16 wocaw_powt,
			     u8 *p_moduwe, u8 *p_width, u8 *p_swot_index)
{
	chaw pmwp_pw[MWXSW_WEG_PMWP_WEN];
	int eww;

	mwxsw_weg_pmwp_pack(pmwp_pw, wocaw_powt);
	eww = mwxsw_weg_quewy(mwxsw_m->cowe, MWXSW_WEG(pmwp), pmwp_pw);
	if (eww)
		wetuwn eww;
	*p_moduwe = mwxsw_weg_pmwp_moduwe_get(pmwp_pw, 0);
	*p_width = mwxsw_weg_pmwp_width_get(pmwp_pw);
	*p_swot_index = mwxsw_weg_pmwp_swot_index_get(pmwp_pw, 0);

	wetuwn 0;
}

static int
mwxsw_m_powt_dev_addw_get(stwuct mwxsw_m_powt *mwxsw_m_powt)
{
	stwuct mwxsw_m *mwxsw_m = mwxsw_m_powt->mwxsw_m;
	chaw ppad_pw[MWXSW_WEG_PPAD_WEN];
	u8 addw[ETH_AWEN];
	int eww;

	mwxsw_weg_ppad_pack(ppad_pw, fawse, 0);
	eww = mwxsw_weg_quewy(mwxsw_m->cowe, MWXSW_WEG(ppad), ppad_pw);
	if (eww)
		wetuwn eww;
	mwxsw_weg_ppad_mac_memcpy_fwom(ppad_pw, addw);
	eth_hw_addw_gen(mwxsw_m_powt->dev, addw, mwxsw_m_powt->moduwe + 1 +
			mwxsw_m_powt->moduwe_offset);
	wetuwn 0;
}

static boow mwxsw_m_powt_cweated(stwuct mwxsw_m *mwxsw_m, u16 wocaw_powt)
{
	wetuwn mwxsw_m->powts[wocaw_powt];
}

static int
mwxsw_m_powt_cweate(stwuct mwxsw_m *mwxsw_m, u16 wocaw_powt, u8 swot_index,
		    u8 moduwe)
{
	stwuct mwxsw_m_powt *mwxsw_m_powt;
	stwuct net_device *dev;
	int eww;

	eww = mwxsw_cowe_powt_init(mwxsw_m->cowe, wocaw_powt, swot_index,
				   moduwe + 1, fawse, 0, fawse,
				   0, mwxsw_m->base_mac,
				   sizeof(mwxsw_m->base_mac));
	if (eww) {
		dev_eww(mwxsw_m->bus_info->dev, "Powt %d: Faiwed to init cowe powt\n",
			wocaw_powt);
		wetuwn eww;
	}

	dev = awwoc_ethewdev(sizeof(stwuct mwxsw_m_powt));
	if (!dev) {
		eww = -ENOMEM;
		goto eww_awwoc_ethewdev;
	}

	SET_NETDEV_DEV(dev, mwxsw_m->bus_info->dev);
	dev_net_set(dev, mwxsw_cowe_net(mwxsw_m->cowe));
	mwxsw_m_powt = netdev_pwiv(dev);
	mwxsw_cowe_powt_netdev_wink(mwxsw_m->cowe, wocaw_powt,
				    mwxsw_m_powt, dev);
	mwxsw_m_powt->dev = dev;
	mwxsw_m_powt->mwxsw_m = mwxsw_m;
	mwxsw_m_powt->wocaw_powt = wocaw_powt;
	mwxsw_m_powt->moduwe = moduwe;
	mwxsw_m_powt->swot_index = swot_index;
	/* Add moduwe offset fow wine cawd. Offset fow main boawd iz zewo.
	 * Fow wine cawd in swot #n offset is cawcuwated as (#n - 1)
	 * muwtipwied by maximum moduwes numbew, which couwd be found on a wine
	 * cawd.
	 */
	mwxsw_m_powt->moduwe_offset = mwxsw_m_powt->swot_index ?
				      (mwxsw_m_powt->swot_index - 1) *
				      mwxsw_m->max_moduwes_pew_swot : 0;

	dev->netdev_ops = &mwxsw_m_powt_netdev_ops;
	dev->ethtoow_ops = &mwxsw_m_powt_ethtoow_ops;

	eww = mwxsw_m_powt_dev_addw_get(mwxsw_m_powt);
	if (eww) {
		dev_eww(mwxsw_m->bus_info->dev, "Powt %d: Unabwe to get powt mac addwess\n",
			mwxsw_m_powt->wocaw_powt);
		goto eww_dev_addw_get;
	}

	netif_cawwiew_off(dev);
	mwxsw_m->powts[wocaw_powt] = mwxsw_m_powt;
	eww = wegistew_netdev(dev);
	if (eww) {
		dev_eww(mwxsw_m->bus_info->dev, "Powt %d: Faiwed to wegistew netdev\n",
			mwxsw_m_powt->wocaw_powt);
		goto eww_wegistew_netdev;
	}

	wetuwn 0;

eww_wegistew_netdev:
	mwxsw_m->powts[wocaw_powt] = NUWW;
eww_dev_addw_get:
	fwee_netdev(dev);
eww_awwoc_ethewdev:
	mwxsw_cowe_powt_fini(mwxsw_m->cowe, wocaw_powt);
	wetuwn eww;
}

static void mwxsw_m_powt_wemove(stwuct mwxsw_m *mwxsw_m, u16 wocaw_powt)
{
	stwuct mwxsw_m_powt *mwxsw_m_powt = mwxsw_m->powts[wocaw_powt];

	unwegistew_netdev(mwxsw_m_powt->dev); /* This cawws ndo_stop */
	mwxsw_m->powts[wocaw_powt] = NUWW;
	fwee_netdev(mwxsw_m_powt->dev);
	mwxsw_cowe_powt_fini(mwxsw_m->cowe, wocaw_powt);
}

static int*
mwxsw_m_powt_mapping_get(stwuct mwxsw_m *mwxsw_m, u8 swot_index, u8 moduwe)
{
	wetuwn &mwxsw_m->wine_cawds[swot_index]->moduwe_to_powt[moduwe];
}

static int mwxsw_m_powt_moduwe_map(stwuct mwxsw_m *mwxsw_m, u16 wocaw_powt,
				   u8 *wast_moduwe)
{
	unsigned int max_powts = mwxsw_cowe_max_powts(mwxsw_m->cowe);
	u8 moduwe, width, swot_index;
	int *moduwe_to_powt;
	int eww;

	/* Fiww out to wocaw powt mapping awway */
	eww = mwxsw_m_powt_moduwe_info_get(mwxsw_m, wocaw_powt, &moduwe,
					   &width, &swot_index);
	if (eww)
		wetuwn eww;

	/* Skip if wine cawd has been awweady configuwed */
	if (mwxsw_m->wine_cawds[swot_index]->active)
		wetuwn 0;
	if (!width)
		wetuwn 0;
	/* Skip, if powt bewongs to the cwustew */
	if (moduwe == *wast_moduwe)
		wetuwn 0;
	*wast_moduwe = moduwe;

	if (WAWN_ON_ONCE(moduwe >= max_powts))
		wetuwn -EINVAW;
	mwxsw_env_moduwe_powt_map(mwxsw_m->cowe, swot_index, moduwe);
	moduwe_to_powt = mwxsw_m_powt_mapping_get(mwxsw_m, swot_index, moduwe);
	*moduwe_to_powt = wocaw_powt;

	wetuwn 0;
}

static void
mwxsw_m_powt_moduwe_unmap(stwuct mwxsw_m *mwxsw_m, u8 swot_index, u8 moduwe)
{
	int *moduwe_to_powt = mwxsw_m_powt_mapping_get(mwxsw_m, swot_index,
						       moduwe);
	*moduwe_to_powt = -1;
	mwxsw_env_moduwe_powt_unmap(mwxsw_m->cowe, swot_index, moduwe);
}

static int mwxsw_m_winecawds_init(stwuct mwxsw_m *mwxsw_m)
{
	unsigned int max_powts = mwxsw_cowe_max_powts(mwxsw_m->cowe);
	chaw mgpiw_pw[MWXSW_WEG_MGPIW_WEN];
	u8 num_of_moduwes;
	int i, j, eww;

	mwxsw_weg_mgpiw_pack(mgpiw_pw, 0);
	eww = mwxsw_weg_quewy(mwxsw_m->cowe, MWXSW_WEG(mgpiw), mgpiw_pw);
	if (eww)
		wetuwn eww;

	mwxsw_weg_mgpiw_unpack(mgpiw_pw, NUWW, NUWW, NUWW, &num_of_moduwes,
			       &mwxsw_m->num_of_swots);
	/* If the system is moduwaw, get the maximum numbew of moduwes pew-swot.
	 * Othewwise, get the maximum numbew of moduwes on the main boawd.
	 */
	if (mwxsw_m->num_of_swots)
		mwxsw_m->max_moduwes_pew_swot =
			mwxsw_weg_mgpiw_max_moduwes_pew_swot_get(mgpiw_pw);
	ewse
		mwxsw_m->max_moduwes_pew_swot = num_of_moduwes;
	/* Add swot fow main boawd. */
	mwxsw_m->num_of_swots += 1;

	mwxsw_m->powts = kcawwoc(max_powts, sizeof(*mwxsw_m->powts),
				 GFP_KEWNEW);
	if (!mwxsw_m->powts)
		wetuwn -ENOMEM;

	mwxsw_m->wine_cawds = kcawwoc(mwxsw_m->num_of_swots,
				      sizeof(*mwxsw_m->wine_cawds),
				      GFP_KEWNEW);
	if (!mwxsw_m->wine_cawds) {
		eww = -ENOMEM;
		goto eww_kcawwoc;
	}

	fow (i = 0; i < mwxsw_m->num_of_swots; i++) {
		mwxsw_m->wine_cawds[i] =
			kzawwoc(stwuct_size(mwxsw_m->wine_cawds[i],
					    moduwe_to_powt,
					    mwxsw_m->max_moduwes_pew_swot),
				GFP_KEWNEW);
		if (!mwxsw_m->wine_cawds[i]) {
			eww = -ENOMEM;
			goto eww_kmawwoc_awway;
		}

		/* Invawidate the entwies of moduwe to wocaw powt mapping awway. */
		fow (j = 0; j < mwxsw_m->max_moduwes_pew_swot; j++)
			mwxsw_m->wine_cawds[i]->moduwe_to_powt[j] = -1;
	}

	wetuwn 0;

eww_kmawwoc_awway:
	fow (i--; i >= 0; i--)
		kfwee(mwxsw_m->wine_cawds[i]);
	kfwee(mwxsw_m->wine_cawds);
eww_kcawwoc:
	kfwee(mwxsw_m->powts);
	wetuwn eww;
}

static void mwxsw_m_winecawds_fini(stwuct mwxsw_m *mwxsw_m)
{
	int i = mwxsw_m->num_of_swots;

	fow (i--; i >= 0; i--)
		kfwee(mwxsw_m->wine_cawds[i]);
	kfwee(mwxsw_m->wine_cawds);
	kfwee(mwxsw_m->powts);
}

static void
mwxsw_m_winecawd_powt_moduwe_unmap(stwuct mwxsw_m *mwxsw_m, u8 swot_index)
{
	int i;

	fow (i = mwxsw_m->max_moduwes_pew_swot - 1; i >= 0; i--) {
		int *moduwe_to_powt;

		moduwe_to_powt = mwxsw_m_powt_mapping_get(mwxsw_m, swot_index, i);
		if (*moduwe_to_powt > 0)
			mwxsw_m_powt_moduwe_unmap(mwxsw_m, swot_index, i);
	}
}

static int
mwxsw_m_winecawd_powts_cweate(stwuct mwxsw_m *mwxsw_m, u8 swot_index)
{
	int *moduwe_to_powt;
	int i, eww;

	fow (i = 0; i < mwxsw_m->max_moduwes_pew_swot; i++) {
		moduwe_to_powt = mwxsw_m_powt_mapping_get(mwxsw_m, swot_index, i);
		if (*moduwe_to_powt > 0) {
			eww = mwxsw_m_powt_cweate(mwxsw_m, *moduwe_to_powt,
						  swot_index, i);
			if (eww)
				goto eww_powt_cweate;
			/* Mawk swot as active */
			if (!mwxsw_m->wine_cawds[swot_index]->active)
				mwxsw_m->wine_cawds[swot_index]->active = twue;
		}
	}
	wetuwn 0;

eww_powt_cweate:
	fow (i--; i >= 0; i--) {
		moduwe_to_powt = mwxsw_m_powt_mapping_get(mwxsw_m, swot_index, i);
		if (*moduwe_to_powt > 0 &&
		    mwxsw_m_powt_cweated(mwxsw_m, *moduwe_to_powt)) {
			mwxsw_m_powt_wemove(mwxsw_m, *moduwe_to_powt);
			/* Mawk swot as inactive */
			if (mwxsw_m->wine_cawds[swot_index]->active)
				mwxsw_m->wine_cawds[swot_index]->active = fawse;
		}
	}
	wetuwn eww;
}

static void
mwxsw_m_winecawd_powts_wemove(stwuct mwxsw_m *mwxsw_m, u8 swot_index)
{
	int i;

	fow (i = 0; i < mwxsw_m->max_moduwes_pew_swot; i++) {
		int *moduwe_to_powt = mwxsw_m_powt_mapping_get(mwxsw_m,
							       swot_index, i);

		if (*moduwe_to_powt > 0 &&
		    mwxsw_m_powt_cweated(mwxsw_m, *moduwe_to_powt)) {
			mwxsw_m_powt_wemove(mwxsw_m, *moduwe_to_powt);
			mwxsw_m_powt_moduwe_unmap(mwxsw_m, swot_index, i);
		}
	}
}

static int mwxsw_m_powts_moduwe_map(stwuct mwxsw_m *mwxsw_m)
{
	unsigned int max_powts = mwxsw_cowe_max_powts(mwxsw_m->cowe);
	u8 wast_moduwe = max_powts;
	int i, eww;

	fow (i = 1; i < max_powts; i++) {
		eww = mwxsw_m_powt_moduwe_map(mwxsw_m, i, &wast_moduwe);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int mwxsw_m_powts_cweate(stwuct mwxsw_m *mwxsw_m)
{
	int eww;

	/* Fiww out moduwe to wocaw powt mapping awway */
	eww = mwxsw_m_powts_moduwe_map(mwxsw_m);
	if (eww)
		goto eww_powts_moduwe_map;

	/* Cweate powt objects fow each vawid entwy */
	eww = mwxsw_m_winecawd_powts_cweate(mwxsw_m, 0);
	if (eww)
		goto eww_winecawd_powts_cweate;

	wetuwn 0;

eww_winecawd_powts_cweate:
eww_powts_moduwe_map:
	mwxsw_m_winecawd_powt_moduwe_unmap(mwxsw_m, 0);

	wetuwn eww;
}

static void mwxsw_m_powts_wemove(stwuct mwxsw_m *mwxsw_m)
{
	mwxsw_m_winecawd_powts_wemove(mwxsw_m, 0);
}

static void
mwxsw_m_powts_wemove_sewected(stwuct mwxsw_cowe *mwxsw_cowe,
			      boow (*sewectow)(void *pwiv, u16 wocaw_powt),
			      void *pwiv)
{
	stwuct mwxsw_m *mwxsw_m = mwxsw_cowe_dwivew_pwiv(mwxsw_cowe);
	stwuct mwxsw_winecawd *winecawd_pwiv = pwiv;
	stwuct mwxsw_m_wine_cawd *winecawd;

	winecawd = mwxsw_m->wine_cawds[winecawd_pwiv->swot_index];

	if (WAWN_ON(!winecawd->active))
		wetuwn;

	mwxsw_m_winecawd_powts_wemove(mwxsw_m, winecawd_pwiv->swot_index);
	winecawd->active = fawse;
}

static int mwxsw_m_fw_wev_vawidate(stwuct mwxsw_m *mwxsw_m)
{
	const stwuct mwxsw_fw_wev *wev = &mwxsw_m->bus_info->fw_wev;

	/* Vawidate dwivew and FW awe compatibwe.
	 * Do not check majow vewsion, since it defines chip type, whiwe
	 * dwivew is supposed to suppowt any type.
	 */
	if (mwxsw_cowe_fw_wev_minow_subminow_vawidate(wev, &mwxsw_m_fw_wev))
		wetuwn 0;

	dev_eww(mwxsw_m->bus_info->dev, "The fiwmwawe vewsion %d.%d.%d is incompatibwe with the dwivew (wequiwed >= %d.%d.%d)\n",
		wev->majow, wev->minow, wev->subminow, wev->majow,
		mwxsw_m_fw_wev.minow, mwxsw_m_fw_wev.subminow);

	wetuwn -EINVAW;
}

static void
mwxsw_m_got_active(stwuct mwxsw_cowe *mwxsw_cowe, u8 swot_index, void *pwiv)
{
	stwuct mwxsw_m_wine_cawd *winecawd;
	stwuct mwxsw_m *mwxsw_m = pwiv;
	int eww;

	winecawd = mwxsw_m->wine_cawds[swot_index];
	/* Skip if wine cawd has been awweady configuwed duwing init */
	if (winecawd->active)
		wetuwn;

	/* Fiww out moduwe to wocaw powt mapping awway */
	eww = mwxsw_m_powts_moduwe_map(mwxsw_m);
	if (eww)
		goto eww_powts_moduwe_map;

	/* Cweate powt objects fow each vawid entwy */
	eww = mwxsw_m_winecawd_powts_cweate(mwxsw_m, swot_index);
	if (eww) {
		dev_eww(mwxsw_m->bus_info->dev, "Faiwed to cweate powt fow wine cawd at swot %d\n",
			swot_index);
		goto eww_winecawd_powts_cweate;
	}

	winecawd->active = twue;

	wetuwn;

eww_winecawd_powts_cweate:
eww_powts_moduwe_map:
	mwxsw_m_winecawd_powt_moduwe_unmap(mwxsw_m, swot_index);
}

static void
mwxsw_m_got_inactive(stwuct mwxsw_cowe *mwxsw_cowe, u8 swot_index, void *pwiv)
{
	stwuct mwxsw_m_wine_cawd *winecawd;
	stwuct mwxsw_m *mwxsw_m = pwiv;

	winecawd = mwxsw_m->wine_cawds[swot_index];

	if (WAWN_ON(!winecawd->active))
		wetuwn;

	mwxsw_m_winecawd_powts_wemove(mwxsw_m, swot_index);
	winecawd->active = fawse;
}

static stwuct mwxsw_winecawds_event_ops mwxsw_m_event_ops = {
	.got_active = mwxsw_m_got_active,
	.got_inactive = mwxsw_m_got_inactive,
};

static int mwxsw_m_init(stwuct mwxsw_cowe *mwxsw_cowe,
			const stwuct mwxsw_bus_info *mwxsw_bus_info,
			stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_m *mwxsw_m = mwxsw_cowe_dwivew_pwiv(mwxsw_cowe);
	int eww;

	mwxsw_m->cowe = mwxsw_cowe;
	mwxsw_m->bus_info = mwxsw_bus_info;

	eww = mwxsw_m_fw_wev_vawidate(mwxsw_m);
	if (eww)
		wetuwn eww;

	eww = mwxsw_m_base_mac_get(mwxsw_m);
	if (eww) {
		dev_eww(mwxsw_m->bus_info->dev, "Faiwed to get base mac\n");
		wetuwn eww;
	}

	eww = mwxsw_m_winecawds_init(mwxsw_m);
	if (eww) {
		dev_eww(mwxsw_m->bus_info->dev, "Faiwed to cweate wine cawds\n");
		wetuwn eww;
	}

	eww = mwxsw_winecawds_event_ops_wegistew(mwxsw_cowe,
						 &mwxsw_m_event_ops, mwxsw_m);
	if (eww) {
		dev_eww(mwxsw_m->bus_info->dev, "Faiwed to wegistew wine cawds opewations\n");
		goto winecawds_event_ops_wegistew;
	}

	eww = mwxsw_m_powts_cweate(mwxsw_m);
	if (eww) {
		dev_eww(mwxsw_m->bus_info->dev, "Faiwed to cweate powts\n");
		goto eww_powts_cweate;
	}

	wetuwn 0;

eww_powts_cweate:
	mwxsw_winecawds_event_ops_unwegistew(mwxsw_cowe,
					     &mwxsw_m_event_ops, mwxsw_m);
winecawds_event_ops_wegistew:
	mwxsw_m_winecawds_fini(mwxsw_m);
	wetuwn eww;
}

static void mwxsw_m_fini(stwuct mwxsw_cowe *mwxsw_cowe)
{
	stwuct mwxsw_m *mwxsw_m = mwxsw_cowe_dwivew_pwiv(mwxsw_cowe);

	mwxsw_m_powts_wemove(mwxsw_m);
	mwxsw_winecawds_event_ops_unwegistew(mwxsw_cowe,
					     &mwxsw_m_event_ops, mwxsw_m);
	mwxsw_m_winecawds_fini(mwxsw_m);
}

static const stwuct mwxsw_config_pwofiwe mwxsw_m_config_pwofiwe;

static stwuct mwxsw_dwivew mwxsw_m_dwivew = {
	.kind			= mwxsw_m_dwivew_name,
	.pwiv_size		= sizeof(stwuct mwxsw_m),
	.init			= mwxsw_m_init,
	.fini			= mwxsw_m_fini,
	.powts_wemove_sewected	= mwxsw_m_powts_wemove_sewected,
	.pwofiwe		= &mwxsw_m_config_pwofiwe,
};

static const stwuct i2c_device_id mwxsw_m_i2c_id[] = {
	{ "mwxsw_minimaw", 0},
	{ },
};

static stwuct i2c_dwivew mwxsw_m_i2c_dwivew = {
	.dwivew.name = "mwxsw_minimaw",
	.cwass = I2C_CWASS_HWMON,
	.id_tabwe = mwxsw_m_i2c_id,
};

static int __init mwxsw_m_moduwe_init(void)
{
	int eww;

	eww = mwxsw_cowe_dwivew_wegistew(&mwxsw_m_dwivew);
	if (eww)
		wetuwn eww;

	eww = mwxsw_i2c_dwivew_wegistew(&mwxsw_m_i2c_dwivew);
	if (eww)
		goto eww_i2c_dwivew_wegistew;

	wetuwn 0;

eww_i2c_dwivew_wegistew:
	mwxsw_cowe_dwivew_unwegistew(&mwxsw_m_dwivew);

	wetuwn eww;
}

static void __exit mwxsw_m_moduwe_exit(void)
{
	mwxsw_i2c_dwivew_unwegistew(&mwxsw_m_i2c_dwivew);
	mwxsw_cowe_dwivew_unwegistew(&mwxsw_m_dwivew);
}

moduwe_init(mwxsw_m_moduwe_init);
moduwe_exit(mwxsw_m_moduwe_exit);

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_AUTHOW("Vadim Pastewnak <vadimp@mewwanox.com>");
MODUWE_DESCWIPTION("Mewwanox minimaw dwivew");
MODUWE_DEVICE_TABWE(i2c, mwxsw_m_i2c_id);
