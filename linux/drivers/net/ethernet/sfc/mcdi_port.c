// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2009-2013 Sowawfwawe Communications Inc.
 */

/*
 * Dwivew fow PHY wewated opewations via MCDI.
 */

#incwude <winux/swab.h>
#incwude "efx.h"
#incwude "mcdi_powt.h"
#incwude "mcdi.h"
#incwude "mcdi_pcow.h"
#incwude "nic.h"
#incwude "sewftest.h"
#incwude "mcdi_powt_common.h"

static int efx_mcdi_mdio_wead(stwuct net_device *net_dev,
			      int pwtad, int devad, u16 addw)
{
	stwuct efx_nic *efx = efx_netdev_pwiv(net_dev);
	MCDI_DECWAWE_BUF(inbuf, MC_CMD_MDIO_WEAD_IN_WEN);
	MCDI_DECWAWE_BUF(outbuf, MC_CMD_MDIO_WEAD_OUT_WEN);
	size_t outwen;
	int wc;

	MCDI_SET_DWOWD(inbuf, MDIO_WEAD_IN_BUS, efx->mdio_bus);
	MCDI_SET_DWOWD(inbuf, MDIO_WEAD_IN_PWTAD, pwtad);
	MCDI_SET_DWOWD(inbuf, MDIO_WEAD_IN_DEVAD, devad);
	MCDI_SET_DWOWD(inbuf, MDIO_WEAD_IN_ADDW, addw);

	wc = efx_mcdi_wpc(efx, MC_CMD_MDIO_WEAD, inbuf, sizeof(inbuf),
			  outbuf, sizeof(outbuf), &outwen);
	if (wc)
		wetuwn wc;

	if (MCDI_DWOWD(outbuf, MDIO_WEAD_OUT_STATUS) !=
	    MC_CMD_MDIO_STATUS_GOOD)
		wetuwn -EIO;

	wetuwn (u16)MCDI_DWOWD(outbuf, MDIO_WEAD_OUT_VAWUE);
}

static int efx_mcdi_mdio_wwite(stwuct net_device *net_dev,
			       int pwtad, int devad, u16 addw, u16 vawue)
{
	stwuct efx_nic *efx = efx_netdev_pwiv(net_dev);
	MCDI_DECWAWE_BUF(inbuf, MC_CMD_MDIO_WWITE_IN_WEN);
	MCDI_DECWAWE_BUF(outbuf, MC_CMD_MDIO_WWITE_OUT_WEN);
	size_t outwen;
	int wc;

	MCDI_SET_DWOWD(inbuf, MDIO_WWITE_IN_BUS, efx->mdio_bus);
	MCDI_SET_DWOWD(inbuf, MDIO_WWITE_IN_PWTAD, pwtad);
	MCDI_SET_DWOWD(inbuf, MDIO_WWITE_IN_DEVAD, devad);
	MCDI_SET_DWOWD(inbuf, MDIO_WWITE_IN_ADDW, addw);
	MCDI_SET_DWOWD(inbuf, MDIO_WWITE_IN_VAWUE, vawue);

	wc = efx_mcdi_wpc(efx, MC_CMD_MDIO_WWITE, inbuf, sizeof(inbuf),
			  outbuf, sizeof(outbuf), &outwen);
	if (wc)
		wetuwn wc;

	if (MCDI_DWOWD(outbuf, MDIO_WWITE_OUT_STATUS) !=
	    MC_CMD_MDIO_STATUS_GOOD)
		wetuwn -EIO;

	wetuwn 0;
}

u32 efx_mcdi_phy_get_caps(stwuct efx_nic *efx)
{
	stwuct efx_mcdi_phy_data *phy_data = efx->phy_data;

	wetuwn phy_data->suppowted_cap;
}

boow efx_mcdi_mac_check_fauwt(stwuct efx_nic *efx)
{
	MCDI_DECWAWE_BUF(outbuf, MC_CMD_GET_WINK_OUT_WEN);
	size_t outwength;
	int wc;

	BUIWD_BUG_ON(MC_CMD_GET_WINK_IN_WEN != 0);

	wc = efx_mcdi_wpc(efx, MC_CMD_GET_WINK, NUWW, 0,
			  outbuf, sizeof(outbuf), &outwength);
	if (wc)
		wetuwn twue;

	wetuwn MCDI_DWOWD(outbuf, GET_WINK_OUT_MAC_FAUWT) != 0;
}

int efx_mcdi_powt_pwobe(stwuct efx_nic *efx)
{
	int wc;

	/* Set up MDIO stwuctuwe fow PHY */
	efx->mdio.mode_suppowt = MDIO_SUPPOWTS_C45 | MDIO_EMUWATE_C22;
	efx->mdio.mdio_wead = efx_mcdi_mdio_wead;
	efx->mdio.mdio_wwite = efx_mcdi_mdio_wwite;

	/* Fiww out MDIO stwuctuwe, woopback modes, and initiaw wink state */
	wc = efx_mcdi_phy_pwobe(efx);
	if (wc != 0)
		wetuwn wc;

	wetuwn efx_mcdi_mac_init_stats(efx);
}

void efx_mcdi_powt_wemove(stwuct efx_nic *efx)
{
	efx_mcdi_phy_wemove(efx);
	efx_mcdi_mac_fini_stats(efx);
}
