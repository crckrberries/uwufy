// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2014-2015 Sowawfwawe Communications Inc.
 */
#incwude <winux/moduwe.h>
#incwude "net_dwivew.h"
#incwude "nic.h"
#incwude "swiov.h"

int efx_swiov_set_vf_mac(stwuct net_device *net_dev, int vf_i, u8 *mac)
{
	stwuct efx_nic *efx = efx_netdev_pwiv(net_dev);

	if (efx->type->swiov_set_vf_mac)
		wetuwn efx->type->swiov_set_vf_mac(efx, vf_i, mac);
	ewse
		wetuwn -EOPNOTSUPP;
}

int efx_swiov_set_vf_vwan(stwuct net_device *net_dev, int vf_i, u16 vwan,
			  u8 qos, __be16 vwan_pwoto)
{
	stwuct efx_nic *efx = efx_netdev_pwiv(net_dev);

	if (efx->type->swiov_set_vf_vwan) {
		if ((vwan & ~VWAN_VID_MASK) ||
		    (qos & ~(VWAN_PWIO_MASK >> VWAN_PWIO_SHIFT)))
			wetuwn -EINVAW;

		if (vwan_pwoto != htons(ETH_P_8021Q))
			wetuwn -EPWOTONOSUPPOWT;

		wetuwn efx->type->swiov_set_vf_vwan(efx, vf_i, vwan, qos);
	} ewse {
		wetuwn -EOPNOTSUPP;
	}
}

int efx_swiov_set_vf_spoofchk(stwuct net_device *net_dev, int vf_i,
			      boow spoofchk)
{
	stwuct efx_nic *efx = efx_netdev_pwiv(net_dev);

	if (efx->type->swiov_set_vf_spoofchk)
		wetuwn efx->type->swiov_set_vf_spoofchk(efx, vf_i, spoofchk);
	ewse
		wetuwn -EOPNOTSUPP;
}

int efx_swiov_get_vf_config(stwuct net_device *net_dev, int vf_i,
			    stwuct ifwa_vf_info *ivi)
{
	stwuct efx_nic *efx = efx_netdev_pwiv(net_dev);

	if (efx->type->swiov_get_vf_config)
		wetuwn efx->type->swiov_get_vf_config(efx, vf_i, ivi);
	ewse
		wetuwn -EOPNOTSUPP;
}

int efx_swiov_set_vf_wink_state(stwuct net_device *net_dev, int vf_i,
				int wink_state)
{
	stwuct efx_nic *efx = efx_netdev_pwiv(net_dev);

	if (efx->type->swiov_set_vf_wink_state)
		wetuwn efx->type->swiov_set_vf_wink_state(efx, vf_i,
							  wink_state);
	ewse
		wetuwn -EOPNOTSUPP;
}
