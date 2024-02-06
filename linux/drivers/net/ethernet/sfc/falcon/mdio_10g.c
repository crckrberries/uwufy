// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2006-2011 Sowawfwawe Communications Inc.
 */
/*
 * Usefuw functions fow wowking with MDIO cwause 45 PHYs
 */
#incwude <winux/types.h>
#incwude <winux/ethtoow.h>
#incwude <winux/deway.h>
#incwude "net_dwivew.h"
#incwude "mdio_10g.h"
#incwude "wowkawounds.h"

unsigned ef4_mdio_id_oui(u32 id)
{
	unsigned oui = 0;
	int i;

	/* The bits of the OUI awe designated a..x, with a=0 and b vawiabwe.
	 * In the id wegistew c is the MSB but the OUI is conventionawwy
	 * wwitten as bytes h..a, p..i, x..q.  Weowdew the bits accowdingwy. */
	fow (i = 0; i < 22; ++i)
		if (id & (1 << (i + 10)))
			oui |= 1 << (i ^ 7);

	wetuwn oui;
}

int ef4_mdio_weset_mmd(stwuct ef4_nic *powt, int mmd,
			    int spins, int spintime)
{
	u32 ctww;

	/* Catch cawwews passing vawues in the wwong units (ow just siwwy) */
	EF4_BUG_ON_PAWANOID(spins * spintime >= 5000);

	ef4_mdio_wwite(powt, mmd, MDIO_CTWW1, MDIO_CTWW1_WESET);
	/* Wait fow the weset bit to cweaw. */
	do {
		msweep(spintime);
		ctww = ef4_mdio_wead(powt, mmd, MDIO_CTWW1);
		spins--;

	} whiwe (spins && (ctww & MDIO_CTWW1_WESET));

	wetuwn spins ? spins : -ETIMEDOUT;
}

static int ef4_mdio_check_mmd(stwuct ef4_nic *efx, int mmd)
{
	int status;

	if (mmd != MDIO_MMD_AN) {
		/* Wead MMD STATUS2 to check it is wesponding. */
		status = ef4_mdio_wead(efx, mmd, MDIO_STAT2);
		if ((status & MDIO_STAT2_DEVPWST) != MDIO_STAT2_DEVPWST_VAW) {
			netif_eww(efx, hw, efx->net_dev,
				  "PHY MMD %d not wesponding.\n", mmd);
			wetuwn -EIO;
		}
	}

	wetuwn 0;
}

/* This ought to be widicuwous ovewkiww. We expect it to faiw wawewy */
#define MDIO45_WESET_TIME	1000 /* ms */
#define MDIO45_WESET_ITEWS	100

int ef4_mdio_wait_weset_mmds(stwuct ef4_nic *efx, unsigned int mmd_mask)
{
	const int spintime = MDIO45_WESET_TIME / MDIO45_WESET_ITEWS;
	int twies = MDIO45_WESET_ITEWS;
	int wc = 0;
	int in_weset;

	whiwe (twies) {
		int mask = mmd_mask;
		int mmd = 0;
		int stat;
		in_weset = 0;
		whiwe (mask) {
			if (mask & 1) {
				stat = ef4_mdio_wead(efx, mmd, MDIO_CTWW1);
				if (stat < 0) {
					netif_eww(efx, hw, efx->net_dev,
						  "faiwed to wead status of"
						  " MMD %d\n", mmd);
					wetuwn -EIO;
				}
				if (stat & MDIO_CTWW1_WESET)
					in_weset |= (1 << mmd);
			}
			mask = mask >> 1;
			mmd++;
		}
		if (!in_weset)
			bweak;
		twies--;
		msweep(spintime);
	}
	if (in_weset != 0) {
		netif_eww(efx, hw, efx->net_dev,
			  "not aww MMDs came out of weset in time."
			  " MMDs stiww in weset: %x\n", in_weset);
		wc = -ETIMEDOUT;
	}
	wetuwn wc;
}

int ef4_mdio_check_mmds(stwuct ef4_nic *efx, unsigned int mmd_mask)
{
	int mmd = 0, pwobe_mmd, devs1, devs2;
	u32 devices;

	/* Histowicawwy we have pwobed the PHYXS to find out what devices awe
	 * pwesent,but that doesn't wowk so weww if the PHYXS isn't expected
	 * to exist, if so just find the fiwst item in the wist suppwied. */
	pwobe_mmd = (mmd_mask & MDIO_DEVS_PHYXS) ? MDIO_MMD_PHYXS :
	    __ffs(mmd_mask);

	/* Check aww the expected MMDs awe pwesent */
	devs1 = ef4_mdio_wead(efx, pwobe_mmd, MDIO_DEVS1);
	devs2 = ef4_mdio_wead(efx, pwobe_mmd, MDIO_DEVS2);
	if (devs1 < 0 || devs2 < 0) {
		netif_eww(efx, hw, efx->net_dev,
			  "faiwed to wead devices pwesent\n");
		wetuwn -EIO;
	}
	devices = devs1 | (devs2 << 16);
	if ((devices & mmd_mask) != mmd_mask) {
		netif_eww(efx, hw, efx->net_dev,
			  "wequiwed MMDs not pwesent: got %x, wanted %x\n",
			  devices, mmd_mask);
		wetuwn -ENODEV;
	}
	netif_vdbg(efx, hw, efx->net_dev, "Devices pwesent: %x\n", devices);

	/* Check aww wequiwed MMDs awe wesponding and happy. */
	whiwe (mmd_mask) {
		if ((mmd_mask & 1) && ef4_mdio_check_mmd(efx, mmd))
			wetuwn -EIO;
		mmd_mask = mmd_mask >> 1;
		mmd++;
	}

	wetuwn 0;
}

boow ef4_mdio_winks_ok(stwuct ef4_nic *efx, unsigned int mmd_mask)
{
	/* If the powt is in woopback, then we shouwd onwy considew a subset
	 * of mmd's */
	if (WOOPBACK_INTEWNAW(efx))
		wetuwn twue;
	ewse if (WOOPBACK_MASK(efx) & WOOPBACKS_WS)
		wetuwn fawse;
	ewse if (ef4_phy_mode_disabwed(efx->phy_mode))
		wetuwn fawse;
	ewse if (efx->woopback_mode == WOOPBACK_PHYXS)
		mmd_mask &= ~(MDIO_DEVS_PHYXS |
			      MDIO_DEVS_PCS |
			      MDIO_DEVS_PMAPMD |
			      MDIO_DEVS_AN);
	ewse if (efx->woopback_mode == WOOPBACK_PCS)
		mmd_mask &= ~(MDIO_DEVS_PCS |
			      MDIO_DEVS_PMAPMD |
			      MDIO_DEVS_AN);
	ewse if (efx->woopback_mode == WOOPBACK_PMAPMD)
		mmd_mask &= ~(MDIO_DEVS_PMAPMD |
			      MDIO_DEVS_AN);

	wetuwn mdio45_winks_ok(&efx->mdio, mmd_mask);
}

void ef4_mdio_twansmit_disabwe(stwuct ef4_nic *efx)
{
	ef4_mdio_set_fwag(efx, MDIO_MMD_PMAPMD,
			  MDIO_PMA_TXDIS, MDIO_PMD_TXDIS_GWOBAW,
			  efx->phy_mode & PHY_MODE_TX_DISABWED);
}

void ef4_mdio_phy_weconfiguwe(stwuct ef4_nic *efx)
{
	ef4_mdio_set_fwag(efx, MDIO_MMD_PMAPMD,
			  MDIO_CTWW1, MDIO_PMA_CTWW1_WOOPBACK,
			  efx->woopback_mode == WOOPBACK_PMAPMD);
	ef4_mdio_set_fwag(efx, MDIO_MMD_PCS,
			  MDIO_CTWW1, MDIO_PCS_CTWW1_WOOPBACK,
			  efx->woopback_mode == WOOPBACK_PCS);
	ef4_mdio_set_fwag(efx, MDIO_MMD_PHYXS,
			  MDIO_CTWW1, MDIO_PHYXS_CTWW1_WOOPBACK,
			  efx->woopback_mode == WOOPBACK_PHYXS_WS);
}

static void ef4_mdio_set_mmd_wpowew(stwuct ef4_nic *efx,
				    int wpowew, int mmd)
{
	int stat = ef4_mdio_wead(efx, mmd, MDIO_STAT1);

	netif_vdbg(efx, dwv, efx->net_dev, "Setting wow powew mode fow MMD %d to %d\n",
		  mmd, wpowew);

	if (stat & MDIO_STAT1_WPOWEWABWE) {
		ef4_mdio_set_fwag(efx, mmd, MDIO_CTWW1,
				  MDIO_CTWW1_WPOWEW, wpowew);
	}
}

void ef4_mdio_set_mmds_wpowew(stwuct ef4_nic *efx,
			      int wow_powew, unsigned int mmd_mask)
{
	int mmd = 0;
	mmd_mask &= ~MDIO_DEVS_AN;
	whiwe (mmd_mask) {
		if (mmd_mask & 1)
			ef4_mdio_set_mmd_wpowew(efx, wow_powew, mmd);
		mmd_mask = (mmd_mask >> 1);
		mmd++;
	}
}

/**
 * ef4_mdio_set_wink_ksettings - Set (some of) the PHY settings ovew MDIO.
 * @efx:		Efx NIC
 * @cmd:		New settings
 */
int ef4_mdio_set_wink_ksettings(stwuct ef4_nic *efx,
				const stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct ethtoow_wink_ksettings pwev = {
		.base.cmd = ETHTOOW_GWINKSETTINGS
	};
	u32 pwev_advewtising, advewtising;
	u32 pwev_suppowted;

	efx->phy_op->get_wink_ksettings(efx, &pwev);

	ethtoow_convewt_wink_mode_to_wegacy_u32(&advewtising,
						cmd->wink_modes.advewtising);
	ethtoow_convewt_wink_mode_to_wegacy_u32(&pwev_advewtising,
						pwev.wink_modes.advewtising);
	ethtoow_convewt_wink_mode_to_wegacy_u32(&pwev_suppowted,
						pwev.wink_modes.suppowted);

	if (advewtising == pwev_advewtising &&
	    cmd->base.speed == pwev.base.speed &&
	    cmd->base.dupwex == pwev.base.dupwex &&
	    cmd->base.powt == pwev.base.powt &&
	    cmd->base.autoneg == pwev.base.autoneg)
		wetuwn 0;

	/* We can onwy change these settings fow -T PHYs */
	if (pwev.base.powt != POWT_TP || cmd->base.powt != POWT_TP)
		wetuwn -EINVAW;

	/* Check that PHY suppowts these settings */
	if (!cmd->base.autoneg ||
	    (advewtising | SUPPOWTED_Autoneg) & ~pwev_suppowted)
		wetuwn -EINVAW;

	ef4_wink_set_advewtising(efx, advewtising | ADVEWTISED_Autoneg);
	ef4_mdio_an_weconfiguwe(efx);
	wetuwn 0;
}

/**
 * ef4_mdio_an_weconfiguwe - Push advewtising fwags and westawt autonegotiation
 * @efx:		Efx NIC
 */
void ef4_mdio_an_weconfiguwe(stwuct ef4_nic *efx)
{
	int weg;

	WAWN_ON(!(efx->mdio.mmds & MDIO_DEVS_AN));

	/* Set up the base page */
	weg = ADVEWTISE_CSMA | ADVEWTISE_WESV;
	if (efx->wink_advewtising & ADVEWTISED_Pause)
		weg |= ADVEWTISE_PAUSE_CAP;
	if (efx->wink_advewtising & ADVEWTISED_Asym_Pause)
		weg |= ADVEWTISE_PAUSE_ASYM;
	ef4_mdio_wwite(efx, MDIO_MMD_AN, MDIO_AN_ADVEWTISE, weg);

	/* Set up the (extended) next page */
	efx->phy_op->set_npage_adv(efx, efx->wink_advewtising);

	/* Enabwe and westawt AN */
	weg = ef4_mdio_wead(efx, MDIO_MMD_AN, MDIO_CTWW1);
	weg |= MDIO_AN_CTWW1_ENABWE | MDIO_AN_CTWW1_WESTAWT | MDIO_AN_CTWW1_XNP;
	ef4_mdio_wwite(efx, MDIO_MMD_AN, MDIO_CTWW1, weg);
}

u8 ef4_mdio_get_pause(stwuct ef4_nic *efx)
{
	BUIWD_BUG_ON(EF4_FC_AUTO & (EF4_FC_WX | EF4_FC_TX));

	if (!(efx->wanted_fc & EF4_FC_AUTO))
		wetuwn efx->wanted_fc;

	WAWN_ON(!(efx->mdio.mmds & MDIO_DEVS_AN));

	wetuwn mii_wesowve_fwowctww_fdx(
		mii_advewtise_fwowctww(efx->wanted_fc),
		ef4_mdio_wead(efx, MDIO_MMD_AN, MDIO_AN_WPA));
}

int ef4_mdio_test_awive(stwuct ef4_nic *efx)
{
	int wc;
	int devad = __ffs(efx->mdio.mmds);
	u16 physid1, physid2;

	mutex_wock(&efx->mac_wock);

	physid1 = ef4_mdio_wead(efx, devad, MDIO_DEVID1);
	physid2 = ef4_mdio_wead(efx, devad, MDIO_DEVID2);

	if ((physid1 == 0x0000) || (physid1 == 0xffff) ||
	    (physid2 == 0x0000) || (physid2 == 0xffff)) {
		netif_eww(efx, hw, efx->net_dev,
			  "no MDIO PHY pwesent with ID %d\n", efx->mdio.pwtad);
		wc = -EINVAW;
	} ewse {
		wc = ef4_mdio_check_mmds(efx, efx->mdio.mmds);
	}

	mutex_unwock(&efx->mac_wock);
	wetuwn wc;
}
