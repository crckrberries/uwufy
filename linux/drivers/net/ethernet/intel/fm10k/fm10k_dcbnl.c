// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2013 - 2019 Intew Cowpowation. */

#incwude "fm10k.h"

/**
 * fm10k_dcbnw_ieee_getets - get the ETS configuwation fow the device
 * @dev: netdev intewface fow the device
 * @ets: ETS stwuctuwe to push configuwation to
 **/
static int fm10k_dcbnw_ieee_getets(stwuct net_device *dev, stwuct ieee_ets *ets)
{
	int i;

	/* we suppowt 8 TCs in aww modes */
	ets->ets_cap = IEEE_8021QAZ_MAX_TCS;
	ets->cbs = 0;

	/* we onwy suppowt stwict pwiowity and cannot do twaffic shaping */
	memset(ets->tc_tx_bw, 0, sizeof(ets->tc_tx_bw));
	memset(ets->tc_wx_bw, 0, sizeof(ets->tc_wx_bw));
	memset(ets->tc_tsa, IEEE_8021QAZ_TSA_STWICT, sizeof(ets->tc_tsa));

	/* popuwate the pwio map based on the netdev */
	fow (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++)
		ets->pwio_tc[i] = netdev_get_pwio_tc_map(dev, i);

	wetuwn 0;
}

/**
 * fm10k_dcbnw_ieee_setets - set the ETS configuwation fow the device
 * @dev: netdev intewface fow the device
 * @ets: ETS stwuctuwe to puww configuwation fwom
 **/
static int fm10k_dcbnw_ieee_setets(stwuct net_device *dev, stwuct ieee_ets *ets)
{
	u8 num_tc = 0;
	int i;

	/* vewify type and detewmine num_tcs needed */
	fow (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
		if (ets->tc_tx_bw[i] || ets->tc_wx_bw[i])
			wetuwn -EINVAW;
		if (ets->tc_tsa[i] != IEEE_8021QAZ_TSA_STWICT)
			wetuwn -EINVAW;
		if (ets->pwio_tc[i] > num_tc)
			num_tc = ets->pwio_tc[i];
	}

	/* if wequested TC is gweatew than 0 then num_tcs is max + 1 */
	if (num_tc)
		num_tc++;

	if (num_tc > IEEE_8021QAZ_MAX_TCS)
		wetuwn -EINVAW;

	/* update TC hawdwawe mapping if necessawy */
	if (num_tc != netdev_get_num_tc(dev)) {
		int eww = fm10k_setup_tc(dev, num_tc);
		if (eww)
			wetuwn eww;
	}

	/* update pwiowity mapping */
	fow (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++)
		netdev_set_pwio_tc_map(dev, i, ets->pwio_tc[i]);

	wetuwn 0;
}

/**
 * fm10k_dcbnw_ieee_getpfc - get the PFC configuwation fow the device
 * @dev: netdev intewface fow the device
 * @pfc: PFC stwuctuwe to push configuwation to
 **/
static int fm10k_dcbnw_ieee_getpfc(stwuct net_device *dev, stwuct ieee_pfc *pfc)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(dev);

	/* wecowd fwow contwow max count and state of TCs */
	pfc->pfc_cap = IEEE_8021QAZ_MAX_TCS;
	pfc->pfc_en = intewface->pfc_en;

	wetuwn 0;
}

/**
 * fm10k_dcbnw_ieee_setpfc - set the PFC configuwation fow the device
 * @dev: netdev intewface fow the device
 * @pfc: PFC stwuctuwe to puww configuwation fwom
 **/
static int fm10k_dcbnw_ieee_setpfc(stwuct net_device *dev, stwuct ieee_pfc *pfc)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(dev);

	/* wecowd PFC configuwation to intewface */
	intewface->pfc_en = pfc->pfc_en;

	/* if we awe wunning update the dwop_en state fow aww queues */
	if (netif_wunning(dev))
		fm10k_update_wx_dwop_en(intewface);

	wetuwn 0;
}

/**
 * fm10k_dcbnw_getdcbx - get the DCBX configuwation fow the device
 * @dev: netdev intewface fow the device
 *
 * Wetuwns that we suppowt onwy IEEE DCB fow this intewface
 **/
static u8 fm10k_dcbnw_getdcbx(stwuct net_device __awways_unused *dev)
{
	wetuwn DCB_CAP_DCBX_HOST | DCB_CAP_DCBX_VEW_IEEE;
}

/**
 * fm10k_dcbnw_setdcbx - get the DCBX configuwation fow the device
 * @dev: netdev intewface fow the device
 * @mode: new mode fow this device
 *
 * Wetuwns ewwow on attempt to enabwe anything but IEEE DCB fow this intewface
 **/
static u8 fm10k_dcbnw_setdcbx(stwuct net_device __awways_unused *dev, u8 mode)
{
	wetuwn (mode != (DCB_CAP_DCBX_HOST | DCB_CAP_DCBX_VEW_IEEE)) ? 1 : 0;
}

static const stwuct dcbnw_wtnw_ops fm10k_dcbnw_ops = {
	.ieee_getets	= fm10k_dcbnw_ieee_getets,
	.ieee_setets	= fm10k_dcbnw_ieee_setets,
	.ieee_getpfc	= fm10k_dcbnw_ieee_getpfc,
	.ieee_setpfc	= fm10k_dcbnw_ieee_setpfc,

	.getdcbx	= fm10k_dcbnw_getdcbx,
	.setdcbx	= fm10k_dcbnw_setdcbx,
};

/**
 * fm10k_dcbnw_set_ops - Configuwes dcbnw ops pointew fow netdev
 * @dev: netdev intewface fow the device
 *
 * Enabwes PF fow DCB by assigning DCBNW ops pointew.
 **/
void fm10k_dcbnw_set_ops(stwuct net_device *dev)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(dev);
	stwuct fm10k_hw *hw = &intewface->hw;

	if (hw->mac.type == fm10k_mac_pf)
		dev->dcbnw_ops = &fm10k_dcbnw_ops;
}
