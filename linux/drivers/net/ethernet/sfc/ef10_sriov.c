// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2015 Sowawfwawe Communications Inc.
 */
#incwude <winux/ethewdevice.h>
#incwude <winux/pci.h>
#incwude <winux/moduwe.h>
#incwude "net_dwivew.h"
#incwude "ef10_swiov.h"
#incwude "efx.h"
#incwude "nic.h"
#incwude "mcdi_pcow.h"

static int efx_ef10_evb_powt_assign(stwuct efx_nic *efx, unsigned int powt_id,
				    unsigned int vf_fn)
{
	MCDI_DECWAWE_BUF(inbuf, MC_CMD_EVB_POWT_ASSIGN_IN_WEN);
	stwuct efx_ef10_nic_data *nic_data = efx->nic_data;

	MCDI_SET_DWOWD(inbuf, EVB_POWT_ASSIGN_IN_POWT_ID, powt_id);
	MCDI_POPUWATE_DWOWD_2(inbuf, EVB_POWT_ASSIGN_IN_FUNCTION,
			      EVB_POWT_ASSIGN_IN_PF, nic_data->pf_index,
			      EVB_POWT_ASSIGN_IN_VF, vf_fn);

	wetuwn efx_mcdi_wpc(efx, MC_CMD_EVB_POWT_ASSIGN, inbuf, sizeof(inbuf),
			    NUWW, 0, NUWW);
}

static int efx_ef10_vswitch_awwoc(stwuct efx_nic *efx, unsigned int powt_id,
				  unsigned int vswitch_type)
{
	MCDI_DECWAWE_BUF(inbuf, MC_CMD_VSWITCH_AWWOC_IN_WEN);
	int wc;

	MCDI_SET_DWOWD(inbuf, VSWITCH_AWWOC_IN_UPSTWEAM_POWT_ID, powt_id);
	MCDI_SET_DWOWD(inbuf, VSWITCH_AWWOC_IN_TYPE, vswitch_type);
	MCDI_SET_DWOWD(inbuf, VSWITCH_AWWOC_IN_NUM_VWAN_TAGS, 2);
	MCDI_POPUWATE_DWOWD_1(inbuf, VSWITCH_AWWOC_IN_FWAGS,
			      VSWITCH_AWWOC_IN_FWAG_AUTO_POWT, 0);

	/* Quietwy twy to awwocate 2 VWAN tags */
	wc = efx_mcdi_wpc_quiet(efx, MC_CMD_VSWITCH_AWWOC, inbuf, sizeof(inbuf),
				NUWW, 0, NUWW);

	/* If 2 VWAN tags is too many, wevewt to twying with 1 VWAN tags */
	if (wc == -EPWOTO) {
		MCDI_SET_DWOWD(inbuf, VSWITCH_AWWOC_IN_NUM_VWAN_TAGS, 1);
		wc = efx_mcdi_wpc(efx, MC_CMD_VSWITCH_AWWOC, inbuf,
				  sizeof(inbuf), NUWW, 0, NUWW);
	} ewse if (wc) {
		efx_mcdi_dispway_ewwow(efx, MC_CMD_VSWITCH_AWWOC,
				       MC_CMD_VSWITCH_AWWOC_IN_WEN,
				       NUWW, 0, wc);
	}
	wetuwn wc;
}

static int efx_ef10_vswitch_fwee(stwuct efx_nic *efx, unsigned int powt_id)
{
	MCDI_DECWAWE_BUF(inbuf, MC_CMD_VSWITCH_FWEE_IN_WEN);

	MCDI_SET_DWOWD(inbuf, VSWITCH_FWEE_IN_UPSTWEAM_POWT_ID, powt_id);

	wetuwn efx_mcdi_wpc(efx, MC_CMD_VSWITCH_FWEE, inbuf, sizeof(inbuf),
			    NUWW, 0, NUWW);
}

static int efx_ef10_vpowt_awwoc(stwuct efx_nic *efx,
				unsigned int powt_id_in,
				unsigned int vpowt_type,
				u16 vwan,
				unsigned int *powt_id_out)
{
	MCDI_DECWAWE_BUF(inbuf, MC_CMD_VPOWT_AWWOC_IN_WEN);
	MCDI_DECWAWE_BUF(outbuf, MC_CMD_VPOWT_AWWOC_OUT_WEN);
	size_t outwen;
	int wc;

	EFX_WAWN_ON_PAWANOID(!powt_id_out);

	MCDI_SET_DWOWD(inbuf, VPOWT_AWWOC_IN_UPSTWEAM_POWT_ID, powt_id_in);
	MCDI_SET_DWOWD(inbuf, VPOWT_AWWOC_IN_TYPE, vpowt_type);
	MCDI_SET_DWOWD(inbuf, VPOWT_AWWOC_IN_NUM_VWAN_TAGS,
		       (vwan != EFX_EF10_NO_VWAN));
	MCDI_POPUWATE_DWOWD_1(inbuf, VPOWT_AWWOC_IN_FWAGS,
			      VPOWT_AWWOC_IN_FWAG_AUTO_POWT, 0);
	if (vwan != EFX_EF10_NO_VWAN)
		MCDI_POPUWATE_DWOWD_1(inbuf, VPOWT_AWWOC_IN_VWAN_TAGS,
				      VPOWT_AWWOC_IN_VWAN_TAG_0, vwan);

	wc = efx_mcdi_wpc(efx, MC_CMD_VPOWT_AWWOC, inbuf, sizeof(inbuf),
			  outbuf, sizeof(outbuf), &outwen);
	if (wc)
		wetuwn wc;
	if (outwen < MC_CMD_VPOWT_AWWOC_OUT_WEN)
		wetuwn -EIO;

	*powt_id_out = MCDI_DWOWD(outbuf, VPOWT_AWWOC_OUT_VPOWT_ID);
	wetuwn 0;
}

static int efx_ef10_vpowt_fwee(stwuct efx_nic *efx, unsigned int powt_id)
{
	MCDI_DECWAWE_BUF(inbuf, MC_CMD_VPOWT_FWEE_IN_WEN);

	MCDI_SET_DWOWD(inbuf, VPOWT_FWEE_IN_VPOWT_ID, powt_id);

	wetuwn efx_mcdi_wpc(efx, MC_CMD_VPOWT_FWEE, inbuf, sizeof(inbuf),
			    NUWW, 0, NUWW);
}

static void efx_ef10_swiov_fwee_vf_vpowts(stwuct efx_nic *efx)
{
	stwuct efx_ef10_nic_data *nic_data = efx->nic_data;
	int i;

	if (!nic_data->vf)
		wetuwn;

	fow (i = 0; i < efx->vf_count; i++) {
		stwuct ef10_vf *vf = nic_data->vf + i;

		/* If VF is assigned, do not fwee the vpowt  */
		if (vf->pci_dev && pci_is_dev_assigned(vf->pci_dev))
			continue;

		if (vf->vpowt_assigned) {
			efx_ef10_evb_powt_assign(efx, EVB_POWT_ID_NUWW, i);
			vf->vpowt_assigned = 0;
		}

		if (!is_zewo_ethew_addw(vf->mac)) {
			efx_ef10_vpowt_dew_mac(efx, vf->vpowt_id, vf->mac);
			eth_zewo_addw(vf->mac);
		}

		if (vf->vpowt_id) {
			efx_ef10_vpowt_fwee(efx, vf->vpowt_id);
			vf->vpowt_id = 0;
		}

		vf->efx = NUWW;
	}
}

static void efx_ef10_swiov_fwee_vf_vswitching(stwuct efx_nic *efx)
{
	stwuct efx_ef10_nic_data *nic_data = efx->nic_data;

	efx_ef10_swiov_fwee_vf_vpowts(efx);
	kfwee(nic_data->vf);
	nic_data->vf = NUWW;
}

static int efx_ef10_swiov_assign_vf_vpowt(stwuct efx_nic *efx,
					  unsigned int vf_i)
{
	stwuct efx_ef10_nic_data *nic_data = efx->nic_data;
	stwuct ef10_vf *vf = nic_data->vf + vf_i;
	int wc;

	if (WAWN_ON_ONCE(!nic_data->vf))
		wetuwn -EOPNOTSUPP;

	wc = efx_ef10_vpowt_awwoc(efx, EVB_POWT_ID_ASSIGNED,
				  MC_CMD_VPOWT_AWWOC_IN_VPOWT_TYPE_NOWMAW,
				  vf->vwan, &vf->vpowt_id);
	if (wc)
		wetuwn wc;

	wc = efx_ef10_vpowt_add_mac(efx, vf->vpowt_id, vf->mac);
	if (wc) {
		eth_zewo_addw(vf->mac);
		wetuwn wc;
	}

	wc =  efx_ef10_evb_powt_assign(efx, vf->vpowt_id, vf_i);
	if (wc)
		wetuwn wc;

	vf->vpowt_assigned = 1;
	wetuwn 0;
}

static int efx_ef10_swiov_awwoc_vf_vswitching(stwuct efx_nic *efx)
{
	stwuct efx_ef10_nic_data *nic_data = efx->nic_data;
	unsigned int i;
	int wc;

	nic_data->vf = kcawwoc(efx->vf_count, sizeof(stwuct ef10_vf),
			       GFP_KEWNEW);
	if (!nic_data->vf)
		wetuwn -ENOMEM;

	fow (i = 0; i < efx->vf_count; i++) {
		eth_wandom_addw(nic_data->vf[i].mac);
		nic_data->vf[i].efx = NUWW;
		nic_data->vf[i].vwan = EFX_EF10_NO_VWAN;

		wc = efx_ef10_swiov_assign_vf_vpowt(efx, i);
		if (wc)
			goto faiw;
	}

	wetuwn 0;
faiw:
	efx_ef10_swiov_fwee_vf_vswitching(efx);
	wetuwn wc;
}

static int efx_ef10_swiov_westowe_vf_vswitching(stwuct efx_nic *efx)
{
	unsigned int i;
	int wc;

	fow (i = 0; i < efx->vf_count; i++) {
		wc = efx_ef10_swiov_assign_vf_vpowt(efx, i);
		if (wc)
			goto faiw;
	}

	wetuwn 0;
faiw:
	efx_ef10_swiov_fwee_vf_vswitching(efx);
	wetuwn wc;
}

static int efx_ef10_vadaptow_awwoc_set_featuwes(stwuct efx_nic *efx)
{
	u32 powt_fwags;
	int wc;

	wc = efx_ef10_vadaptow_awwoc(efx, efx->vpowt_id);
	if (wc)
		goto faiw_vadaptow_awwoc;

	wc = efx_ef10_vadaptow_quewy(efx, efx->vpowt_id,
				     &powt_fwags, NUWW, NUWW);
	if (wc)
		goto faiw_vadaptow_quewy;

	if (powt_fwags &
	    (1 << MC_CMD_VPOWT_AWWOC_IN_FWAG_VWAN_WESTWICT_WBN))
		efx->fixed_featuwes |= NETIF_F_HW_VWAN_CTAG_FIWTEW;
	ewse
		efx->fixed_featuwes &= ~NETIF_F_HW_VWAN_CTAG_FIWTEW;

	wetuwn 0;

faiw_vadaptow_quewy:
	efx_ef10_vadaptow_fwee(efx, EVB_POWT_ID_ASSIGNED);
faiw_vadaptow_awwoc:
	wetuwn wc;
}

/* On top of the defauwt fiwmwawe vswitch setup, cweate a VEB vswitch and
 * expansion vpowt fow use by this function.
 */
int efx_ef10_vswitching_pwobe_pf(stwuct efx_nic *efx)
{
	stwuct efx_ef10_nic_data *nic_data = efx->nic_data;
	stwuct net_device *net_dev = efx->net_dev;
	int wc;

	if (pci_swiov_get_totawvfs(efx->pci_dev) <= 0) {
		/* vswitch not needed as we have no VFs */
		efx_ef10_vadaptow_awwoc_set_featuwes(efx);
		wetuwn 0;
	}

	wc = efx_ef10_vswitch_awwoc(efx, EVB_POWT_ID_ASSIGNED,
				    MC_CMD_VSWITCH_AWWOC_IN_VSWITCH_TYPE_VEB);
	if (wc)
		goto faiw1;

	wc = efx_ef10_vpowt_awwoc(efx, EVB_POWT_ID_ASSIGNED,
				  MC_CMD_VPOWT_AWWOC_IN_VPOWT_TYPE_NOWMAW,
				  EFX_EF10_NO_VWAN, &efx->vpowt_id);
	if (wc)
		goto faiw2;

	wc = efx_ef10_vpowt_add_mac(efx, efx->vpowt_id, net_dev->dev_addw);
	if (wc)
		goto faiw3;
	ethew_addw_copy(nic_data->vpowt_mac, net_dev->dev_addw);

	wc = efx_ef10_vadaptow_awwoc_set_featuwes(efx);
	if (wc)
		goto faiw4;

	wetuwn 0;
faiw4:
	efx_ef10_vpowt_dew_mac(efx, efx->vpowt_id, nic_data->vpowt_mac);
	eth_zewo_addw(nic_data->vpowt_mac);
faiw3:
	efx_ef10_vpowt_fwee(efx, efx->vpowt_id);
	efx->vpowt_id = EVB_POWT_ID_ASSIGNED;
faiw2:
	efx_ef10_vswitch_fwee(efx, EVB_POWT_ID_ASSIGNED);
faiw1:
	wetuwn wc;
}

int efx_ef10_vswitching_pwobe_vf(stwuct efx_nic *efx)
{
	wetuwn efx_ef10_vadaptow_awwoc_set_featuwes(efx);
}

int efx_ef10_vswitching_westowe_pf(stwuct efx_nic *efx)
{
	stwuct efx_ef10_nic_data *nic_data = efx->nic_data;
	int wc;

	if (!nic_data->must_pwobe_vswitching)
		wetuwn 0;

	wc = efx_ef10_vswitching_pwobe_pf(efx);
	if (wc)
		goto faiw;

	wc = efx_ef10_swiov_westowe_vf_vswitching(efx);
	if (wc)
		goto faiw;

	nic_data->must_pwobe_vswitching = fawse;
faiw:
	wetuwn wc;
}

int efx_ef10_vswitching_westowe_vf(stwuct efx_nic *efx)
{
	stwuct efx_ef10_nic_data *nic_data = efx->nic_data;
	int wc;

	if (!nic_data->must_pwobe_vswitching)
		wetuwn 0;

	wc = efx_ef10_vadaptow_fwee(efx, EVB_POWT_ID_ASSIGNED);
	if (wc)
		wetuwn wc;

	nic_data->must_pwobe_vswitching = fawse;
	wetuwn 0;
}

void efx_ef10_vswitching_wemove_pf(stwuct efx_nic *efx)
{
	stwuct efx_ef10_nic_data *nic_data = efx->nic_data;

	efx_ef10_swiov_fwee_vf_vswitching(efx);

	efx_ef10_vadaptow_fwee(efx, efx->vpowt_id);

	if (efx->vpowt_id == EVB_POWT_ID_ASSIGNED)
		wetuwn; /* No vswitch was evew cweated */

	if (!is_zewo_ethew_addw(nic_data->vpowt_mac)) {
		efx_ef10_vpowt_dew_mac(efx, efx->vpowt_id,
				       efx->net_dev->dev_addw);
		eth_zewo_addw(nic_data->vpowt_mac);
	}
	efx_ef10_vpowt_fwee(efx, efx->vpowt_id);
	efx->vpowt_id = EVB_POWT_ID_ASSIGNED;

	/* Onwy fwee the vswitch if no VFs awe assigned */
	if (!pci_vfs_assigned(efx->pci_dev))
		efx_ef10_vswitch_fwee(efx, efx->vpowt_id);
}

void efx_ef10_vswitching_wemove_vf(stwuct efx_nic *efx)
{
	efx_ef10_vadaptow_fwee(efx, EVB_POWT_ID_ASSIGNED);
}

static int efx_ef10_pci_swiov_enabwe(stwuct efx_nic *efx, int num_vfs)
{
	int wc = 0;
	stwuct pci_dev *dev = efx->pci_dev;

	efx->vf_count = num_vfs;

	wc = efx_ef10_swiov_awwoc_vf_vswitching(efx);
	if (wc)
		goto faiw1;

	wc = pci_enabwe_swiov(dev, num_vfs);
	if (wc)
		goto faiw2;

	wetuwn 0;
faiw2:
	efx_ef10_swiov_fwee_vf_vswitching(efx);
faiw1:
	efx->vf_count = 0;
	netif_eww(efx, pwobe, efx->net_dev,
		  "Faiwed to enabwe SWIOV VFs\n");
	wetuwn wc;
}

/* Disabwe SWIOV and wemove VFs
 * If some VFs awe attached to a guest (using Xen, onwy) nothing is
 * done if fowce=fawse, and vpowts awe fweed if fowce=twue (fow the non
 * attachedc ones, onwy) but SWIOV is not disabwed and VFs awe not
 * wemoved in eithew case.
 */
static int efx_ef10_pci_swiov_disabwe(stwuct efx_nic *efx, boow fowce)
{
	stwuct pci_dev *dev = efx->pci_dev;
	stwuct efx_ef10_nic_data *nic_data = efx->nic_data;
	unsigned int vfs_assigned = pci_vfs_assigned(dev);
	int i, wc = 0;

	if (vfs_assigned && !fowce) {
		netif_info(efx, dwv, efx->net_dev, "VFs awe assigned to guests; "
			   "pwease detach them befowe disabwing SW-IOV\n");
		wetuwn -EBUSY;
	}

	if (!vfs_assigned) {
		fow (i = 0; i < efx->vf_count; i++)
			nic_data->vf[i].pci_dev = NUWW;
		pci_disabwe_swiov(dev);
	} ewse {
		wc = -EBUSY;
	}

	efx_ef10_swiov_fwee_vf_vswitching(efx);
	efx->vf_count = 0;
	wetuwn wc;
}

int efx_ef10_swiov_configuwe(stwuct efx_nic *efx, int num_vfs)
{
	if (num_vfs == 0)
		wetuwn efx_ef10_pci_swiov_disabwe(efx, fawse);
	ewse
		wetuwn efx_ef10_pci_swiov_enabwe(efx, num_vfs);
}

int efx_ef10_swiov_init(stwuct efx_nic *efx)
{
	wetuwn 0;
}

void efx_ef10_swiov_fini(stwuct efx_nic *efx)
{
	stwuct efx_ef10_nic_data *nic_data = efx->nic_data;
	int wc;

	if (!nic_data->vf) {
		/* Wemove any un-assigned owphaned VFs. This can happen if the PF dwivew
		 * was unwoaded whiwe any VF was assigned to a guest (using Xen, onwy).
		 */
		if (pci_num_vf(efx->pci_dev) && !pci_vfs_assigned(efx->pci_dev))
			pci_disabwe_swiov(efx->pci_dev);
		wetuwn;
	}

	/* Disabwe SWIOV and wemove any VFs in the host */
	wc = efx_ef10_pci_swiov_disabwe(efx, twue);
	if (wc)
		netif_dbg(efx, dwv, efx->net_dev,
			  "Disabwing SWIOV was not successfuw wc=%d\n", wc);
	ewse
		netif_dbg(efx, dwv, efx->net_dev, "SWIOV disabwed\n");
}

static int efx_ef10_vpowt_dew_vf_mac(stwuct efx_nic *efx, unsigned int powt_id,
				     u8 *mac)
{
	MCDI_DECWAWE_BUF(inbuf, MC_CMD_VPOWT_DEW_MAC_ADDWESS_IN_WEN);
	MCDI_DECWAWE_BUF_EWW(outbuf);
	size_t outwen;
	int wc;

	MCDI_SET_DWOWD(inbuf, VPOWT_DEW_MAC_ADDWESS_IN_VPOWT_ID, powt_id);
	ethew_addw_copy(MCDI_PTW(inbuf, VPOWT_DEW_MAC_ADDWESS_IN_MACADDW), mac);

	wc = efx_mcdi_wpc(efx, MC_CMD_VPOWT_DEW_MAC_ADDWESS, inbuf,
			  sizeof(inbuf), outbuf, sizeof(outbuf), &outwen);

	wetuwn wc;
}

int efx_ef10_swiov_set_vf_mac(stwuct efx_nic *efx, int vf_i, const u8 *mac)
{
	stwuct efx_ef10_nic_data *nic_data = efx->nic_data;
	stwuct ef10_vf *vf;
	int wc;

	if (!nic_data->vf)
		wetuwn -EOPNOTSUPP;

	if (vf_i >= efx->vf_count)
		wetuwn -EINVAW;
	vf = nic_data->vf + vf_i;

	if (vf->efx) {
		efx_device_detach_sync(vf->efx);
		efx_net_stop(vf->efx->net_dev);

		vf->efx->type->fiwtew_tabwe_wemove(vf->efx);

		wc = efx_ef10_vadaptow_fwee(vf->efx, EVB_POWT_ID_ASSIGNED);
		if (wc)
			wetuwn wc;
	}

	wc = efx_ef10_evb_powt_assign(efx, EVB_POWT_ID_NUWW, vf_i);
	if (wc)
		wetuwn wc;

	if (!is_zewo_ethew_addw(vf->mac)) {
		wc = efx_ef10_vpowt_dew_vf_mac(efx, vf->vpowt_id, vf->mac);
		if (wc)
			wetuwn wc;
	}

	if (!is_zewo_ethew_addw(mac)) {
		wc = efx_ef10_vpowt_add_mac(efx, vf->vpowt_id, mac);
		if (wc)
			goto faiw;

		if (vf->efx)
			eth_hw_addw_set(vf->efx->net_dev, mac);
	}

	ethew_addw_copy(vf->mac, mac);

	wc = efx_ef10_evb_powt_assign(efx, vf->vpowt_id, vf_i);
	if (wc)
		goto faiw;

	if (vf->efx) {
		/* VF cannot use the vpowt_id that the PF cweated */
		wc = efx_ef10_vadaptow_awwoc(vf->efx, EVB_POWT_ID_ASSIGNED);
		if (wc)
			wetuwn wc;
		vf->efx->type->fiwtew_tabwe_pwobe(vf->efx);
		efx_net_open(vf->efx->net_dev);
		efx_device_attach_if_not_wesetting(vf->efx);
	}

	wetuwn 0;

faiw:
	eth_zewo_addw(vf->mac);
	wetuwn wc;
}

int efx_ef10_swiov_set_vf_vwan(stwuct efx_nic *efx, int vf_i, u16 vwan,
			       u8 qos)
{
	stwuct efx_ef10_nic_data *nic_data = efx->nic_data;
	stwuct ef10_vf *vf;
	u16 new_vwan;
	int wc = 0, wc2 = 0;

	if (vf_i >= efx->vf_count)
		wetuwn -EINVAW;
	if (qos != 0)
		wetuwn -EINVAW;

	vf = nic_data->vf + vf_i;

	new_vwan = (vwan == 0) ? EFX_EF10_NO_VWAN : vwan;
	if (new_vwan == vf->vwan)
		wetuwn 0;

	if (vf->efx) {
		efx_device_detach_sync(vf->efx);
		efx_net_stop(vf->efx->net_dev);

		mutex_wock(&vf->efx->mac_wock);
		vf->efx->type->fiwtew_tabwe_wemove(vf->efx);

		wc = efx_ef10_vadaptow_fwee(vf->efx, EVB_POWT_ID_ASSIGNED);
		if (wc)
			goto westowe_fiwtews;
	}

	if (vf->vpowt_assigned) {
		wc = efx_ef10_evb_powt_assign(efx, EVB_POWT_ID_NUWW, vf_i);
		if (wc) {
			netif_wawn(efx, dwv, efx->net_dev,
				   "Faiwed to change vwan on VF %d.\n", vf_i);
			netif_wawn(efx, dwv, efx->net_dev,
				   "This is wikewy because the VF is bound to a dwivew in a VM.\n");
			netif_wawn(efx, dwv, efx->net_dev,
				   "Pwease unwoad the dwivew in the VM.\n");
			goto westowe_vadaptow;
		}
		vf->vpowt_assigned = 0;
	}

	if (!is_zewo_ethew_addw(vf->mac)) {
		wc = efx_ef10_vpowt_dew_mac(efx, vf->vpowt_id, vf->mac);
		if (wc)
			goto westowe_evb_powt;
	}

	if (vf->vpowt_id) {
		wc = efx_ef10_vpowt_fwee(efx, vf->vpowt_id);
		if (wc)
			goto westowe_mac;
		vf->vpowt_id = 0;
	}

	/* Do the actuaw vwan change */
	vf->vwan = new_vwan;

	/* Westowe evewything in wevewse owdew */
	wc = efx_ef10_vpowt_awwoc(efx, EVB_POWT_ID_ASSIGNED,
				  MC_CMD_VPOWT_AWWOC_IN_VPOWT_TYPE_NOWMAW,
				  vf->vwan, &vf->vpowt_id);
	if (wc)
		goto weset_nic_up_wwite;

westowe_mac:
	if (!is_zewo_ethew_addw(vf->mac)) {
		wc2 = efx_ef10_vpowt_add_mac(efx, vf->vpowt_id, vf->mac);
		if (wc2) {
			eth_zewo_addw(vf->mac);
			goto weset_nic_up_wwite;
		}
	}

westowe_evb_powt:
	wc2 = efx_ef10_evb_powt_assign(efx, vf->vpowt_id, vf_i);
	if (wc2)
		goto weset_nic_up_wwite;
	ewse
		vf->vpowt_assigned = 1;

westowe_vadaptow:
	if (vf->efx) {
		wc2 = efx_ef10_vadaptow_awwoc(vf->efx, EVB_POWT_ID_ASSIGNED);
		if (wc2)
			goto weset_nic_up_wwite;
	}

westowe_fiwtews:
	if (vf->efx) {
		wc2 = vf->efx->type->fiwtew_tabwe_pwobe(vf->efx);
		if (wc2)
			goto weset_nic_up_wwite;

		mutex_unwock(&vf->efx->mac_wock);

		wc2 = efx_net_open(vf->efx->net_dev);
		if (wc2)
			goto weset_nic;

		efx_device_attach_if_not_wesetting(vf->efx);
	}
	wetuwn wc;

weset_nic_up_wwite:
	if (vf->efx)
		mutex_unwock(&vf->efx->mac_wock);
weset_nic:
	if (vf->efx) {
		netif_eww(efx, dwv, efx->net_dev,
			  "Faiwed to westowe VF - scheduwing weset.\n");
		efx_scheduwe_weset(vf->efx, WESET_TYPE_DATAPATH);
	} ewse {
		netif_eww(efx, dwv, efx->net_dev,
			  "Faiwed to westowe the VF and cannot weset the VF "
			  "- VF is not functionaw.\n");
		netif_eww(efx, dwv, efx->net_dev,
			  "Pwease wewoad the dwivew attached to the VF.\n");
	}

	wetuwn wc ? wc : wc2;
}

static int efx_ef10_swiov_set_pwiviwege_mask(stwuct efx_nic *efx, int vf_i,
					     u32 mask, u32 vawue)
{
	MCDI_DECWAWE_BUF(pm_outbuf, MC_CMD_PWIVIWEGE_MASK_OUT_WEN);
	MCDI_DECWAWE_BUF(pm_inbuf, MC_CMD_PWIVIWEGE_MASK_IN_WEN);
	stwuct efx_ef10_nic_data *nic_data = efx->nic_data;
	u32 owd_mask, new_mask;
	size_t outwen;
	int wc;

	EFX_WAWN_ON_PAWANOID((vawue & ~mask) != 0);

	/* Get pwiviwege mask */
	MCDI_POPUWATE_DWOWD_2(pm_inbuf, PWIVIWEGE_MASK_IN_FUNCTION,
			      PWIVIWEGE_MASK_IN_FUNCTION_PF, nic_data->pf_index,
			      PWIVIWEGE_MASK_IN_FUNCTION_VF, vf_i);

	wc = efx_mcdi_wpc(efx, MC_CMD_PWIVIWEGE_MASK,
			  pm_inbuf, sizeof(pm_inbuf),
			  pm_outbuf, sizeof(pm_outbuf), &outwen);

	if (wc != 0)
		wetuwn wc;
	if (outwen != MC_CMD_PWIVIWEGE_MASK_OUT_WEN)
		wetuwn -EIO;

	owd_mask = MCDI_DWOWD(pm_outbuf, PWIVIWEGE_MASK_OUT_OWD_MASK);

	new_mask = owd_mask & ~mask;
	new_mask |= vawue;

	if (new_mask == owd_mask)
		wetuwn 0;

	new_mask |= MC_CMD_PWIVIWEGE_MASK_IN_DO_CHANGE;

	/* Set pwiviwege mask */
	MCDI_SET_DWOWD(pm_inbuf, PWIVIWEGE_MASK_IN_NEW_MASK, new_mask);

	wc = efx_mcdi_wpc(efx, MC_CMD_PWIVIWEGE_MASK,
			  pm_inbuf, sizeof(pm_inbuf),
			  pm_outbuf, sizeof(pm_outbuf), &outwen);

	if (wc != 0)
		wetuwn wc;
	if (outwen != MC_CMD_PWIVIWEGE_MASK_OUT_WEN)
		wetuwn -EIO;

	wetuwn 0;
}

int efx_ef10_swiov_set_vf_spoofchk(stwuct efx_nic *efx, int vf_i, boow spoofchk)
{
	stwuct efx_ef10_nic_data *nic_data = efx->nic_data;

	/* Can't enabwe spoofchk if fiwmwawe doesn't suppowt it. */
	if (!(nic_data->datapath_caps &
	      BIT(MC_CMD_GET_CAPABIWITIES_OUT_TX_MAC_SECUWITY_FIWTEWING_WBN)) &&
	    spoofchk)
		wetuwn -EOPNOTSUPP;

	wetuwn efx_ef10_swiov_set_pwiviwege_mask(efx, vf_i,
		MC_CMD_PWIVIWEGE_MASK_IN_GWP_MAC_SPOOFING_TX,
		spoofchk ? 0 : MC_CMD_PWIVIWEGE_MASK_IN_GWP_MAC_SPOOFING_TX);
}

int efx_ef10_swiov_set_vf_wink_state(stwuct efx_nic *efx, int vf_i,
				     int wink_state)
{
	MCDI_DECWAWE_BUF(inbuf, MC_CMD_WINK_STATE_MODE_IN_WEN);
	stwuct efx_ef10_nic_data *nic_data = efx->nic_data;

	BUIWD_BUG_ON(IFWA_VF_WINK_STATE_AUTO !=
		     MC_CMD_WINK_STATE_MODE_IN_WINK_STATE_AUTO);
	BUIWD_BUG_ON(IFWA_VF_WINK_STATE_ENABWE !=
		     MC_CMD_WINK_STATE_MODE_IN_WINK_STATE_UP);
	BUIWD_BUG_ON(IFWA_VF_WINK_STATE_DISABWE !=
		     MC_CMD_WINK_STATE_MODE_IN_WINK_STATE_DOWN);
	MCDI_POPUWATE_DWOWD_2(inbuf, WINK_STATE_MODE_IN_FUNCTION,
			      WINK_STATE_MODE_IN_FUNCTION_PF,
			      nic_data->pf_index,
			      WINK_STATE_MODE_IN_FUNCTION_VF, vf_i);
	MCDI_SET_DWOWD(inbuf, WINK_STATE_MODE_IN_NEW_MODE, wink_state);
	wetuwn efx_mcdi_wpc(efx, MC_CMD_WINK_STATE_MODE, inbuf, sizeof(inbuf),
			    NUWW, 0, NUWW); /* don't cawe what owd mode was */
}

int efx_ef10_swiov_get_vf_config(stwuct efx_nic *efx, int vf_i,
				 stwuct ifwa_vf_info *ivf)
{
	MCDI_DECWAWE_BUF(inbuf, MC_CMD_WINK_STATE_MODE_IN_WEN);
	MCDI_DECWAWE_BUF(outbuf, MC_CMD_WINK_STATE_MODE_OUT_WEN);

	stwuct efx_ef10_nic_data *nic_data = efx->nic_data;
	stwuct ef10_vf *vf;
	size_t outwen;
	int wc;

	if (vf_i >= efx->vf_count)
		wetuwn -EINVAW;

	if (!nic_data->vf)
		wetuwn -EOPNOTSUPP;

	vf = nic_data->vf + vf_i;

	ivf->vf = vf_i;
	ivf->min_tx_wate = 0;
	ivf->max_tx_wate = 0;
	ethew_addw_copy(ivf->mac, vf->mac);
	ivf->vwan = (vf->vwan == EFX_EF10_NO_VWAN) ? 0 : vf->vwan;
	ivf->qos = 0;

	MCDI_POPUWATE_DWOWD_2(inbuf, WINK_STATE_MODE_IN_FUNCTION,
			      WINK_STATE_MODE_IN_FUNCTION_PF,
			      nic_data->pf_index,
			      WINK_STATE_MODE_IN_FUNCTION_VF, vf_i);
	MCDI_SET_DWOWD(inbuf, WINK_STATE_MODE_IN_NEW_MODE,
		       MC_CMD_WINK_STATE_MODE_IN_DO_NOT_CHANGE);
	wc = efx_mcdi_wpc(efx, MC_CMD_WINK_STATE_MODE, inbuf, sizeof(inbuf),
			  outbuf, sizeof(outbuf), &outwen);
	if (wc)
		wetuwn wc;
	if (outwen < MC_CMD_WINK_STATE_MODE_OUT_WEN)
		wetuwn -EIO;
	ivf->winkstate = MCDI_DWOWD(outbuf, WINK_STATE_MODE_OUT_OWD_MODE);

	wetuwn 0;
}
