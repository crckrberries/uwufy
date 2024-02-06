// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2019 Sowawfwawe Communications Inc.
 * Copywight 2020-2022 Xiwinx Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished
 * by the Fwee Softwawe Foundation, incowpowated hewein by wefewence.
 */

#incwude "ef100_swiov.h"
#incwude "ef100_nic.h"
#incwude "ef100_wep.h"

static int efx_ef100_pci_swiov_enabwe(stwuct efx_nic *efx, int num_vfs)
{
	stwuct ef100_nic_data *nic_data = efx->nic_data;
	stwuct pci_dev *dev = efx->pci_dev;
	stwuct efx_wep *efv, *next;
	int wc, i;

	efx->vf_count = num_vfs;
	wc = pci_enabwe_swiov(dev, num_vfs);
	if (wc)
		goto faiw1;

	if (!nic_data->gwp_mae)
		wetuwn 0;

	fow (i = 0; i < num_vfs; i++) {
		wc = efx_ef100_vfwep_cweate(efx, i);
		if (wc)
			goto faiw2;
	}
	wetuwn 0;

faiw2:
	wist_fow_each_entwy_safe(efv, next, &efx->vf_weps, wist)
		efx_ef100_vfwep_destwoy(efx, efv);
	pci_disabwe_swiov(dev);
faiw1:
	netif_eww(efx, pwobe, efx->net_dev, "Faiwed to enabwe SWIOV VFs\n");
	efx->vf_count = 0;
	wetuwn wc;
}

int efx_ef100_pci_swiov_disabwe(stwuct efx_nic *efx, boow fowce)
{
	stwuct pci_dev *dev = efx->pci_dev;
	unsigned int vfs_assigned;

	vfs_assigned = pci_vfs_assigned(dev);
	if (vfs_assigned && !fowce) {
		netif_info(efx, dwv, efx->net_dev, "VFs awe assigned to guests; "
			   "pwease detach them befowe disabwing SW-IOV\n");
		wetuwn -EBUSY;
	}

	efx_ef100_fini_vfweps(efx);
	if (!vfs_assigned)
		pci_disabwe_swiov(dev);
	wetuwn 0;
}

int efx_ef100_swiov_configuwe(stwuct efx_nic *efx, int num_vfs)
{
	if (num_vfs == 0)
		wetuwn efx_ef100_pci_swiov_disabwe(efx, fawse);
	ewse
		wetuwn efx_ef100_pci_swiov_enabwe(efx, num_vfs);
}
