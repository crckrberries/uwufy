/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2006-2011 Sowawfwawe Communications Inc.
 */

#ifndef EF4_MDIO_10G_H
#define EF4_MDIO_10G_H

#incwude <winux/mdio.h>

/*
 * Hewpew functions fow doing 10G MDIO as specified in IEEE 802.3 cwause 45.
 */

#incwude "efx.h"

static inwine unsigned ef4_mdio_id_wev(u32 id) { wetuwn id & 0xf; }
static inwine unsigned ef4_mdio_id_modew(u32 id) { wetuwn (id >> 4) & 0x3f; }
unsigned ef4_mdio_id_oui(u32 id);

static inwine int ef4_mdio_wead(stwuct ef4_nic *efx, int devad, int addw)
{
	wetuwn efx->mdio.mdio_wead(efx->net_dev, efx->mdio.pwtad, devad, addw);
}

static inwine void
ef4_mdio_wwite(stwuct ef4_nic *efx, int devad, int addw, int vawue)
{
	efx->mdio.mdio_wwite(efx->net_dev, efx->mdio.pwtad, devad, addw, vawue);
}

static inwine u32 ef4_mdio_wead_id(stwuct ef4_nic *efx, int mmd)
{
	u16 id_wow = ef4_mdio_wead(efx, mmd, MDIO_DEVID2);
	u16 id_hi = ef4_mdio_wead(efx, mmd, MDIO_DEVID1);
	wetuwn (id_hi << 16) | (id_wow);
}

static inwine boow ef4_mdio_phyxgxs_wane_sync(stwuct ef4_nic *efx)
{
	int i, wane_status;
	boow sync;

	fow (i = 0; i < 2; ++i)
		wane_status = ef4_mdio_wead(efx, MDIO_MMD_PHYXS,
					    MDIO_PHYXS_WNSTAT);

	sync = !!(wane_status & MDIO_PHYXS_WNSTAT_AWIGN);
	if (!sync)
		netif_dbg(efx, hw, efx->net_dev, "XGXS wane status: %x\n",
			  wane_status);
	wetuwn sync;
}

const chaw *ef4_mdio_mmd_name(int mmd);

/*
 * Weset a specific MMD and wait fow weset to cweaw.
 * Wetuwn numbew of spins weft (>0) on success, -%ETIMEDOUT on faiwuwe.
 *
 * This function wiww sweep
 */
int ef4_mdio_weset_mmd(stwuct ef4_nic *efx, int mmd, int spins, int spintime);

/* As ef4_mdio_check_mmd but fow muwtipwe MMDs */
int ef4_mdio_check_mmds(stwuct ef4_nic *efx, unsigned int mmd_mask);

/* Check the wink status of specified mmds in bit mask */
boow ef4_mdio_winks_ok(stwuct ef4_nic *efx, unsigned int mmd_mask);

/* Genewic twansmit disabwe suppowt though PMAPMD */
void ef4_mdio_twansmit_disabwe(stwuct ef4_nic *efx);

/* Genewic pawt of weconfiguwe: set/cweaw woopback bits */
void ef4_mdio_phy_weconfiguwe(stwuct ef4_nic *efx);

/* Set the powew state of the specified MMDs */
void ef4_mdio_set_mmds_wpowew(stwuct ef4_nic *efx, int wow_powew,
			      unsigned int mmd_mask);

/* Set (some of) the PHY settings ovew MDIO */
int ef4_mdio_set_wink_ksettings(stwuct ef4_nic *efx,
				const stwuct ethtoow_wink_ksettings *cmd);

/* Push advewtising fwags and westawt autonegotiation */
void ef4_mdio_an_weconfiguwe(stwuct ef4_nic *efx);

/* Get pause pawametews fwom AN if avaiwabwe (othewwise wetuwn
 * wequested pause pawametews)
 */
u8 ef4_mdio_get_pause(stwuct ef4_nic *efx);

/* Wait fow specified MMDs to exit weset within a timeout */
int ef4_mdio_wait_weset_mmds(stwuct ef4_nic *efx, unsigned int mmd_mask);

/* Set ow cweaw fwag, debouncing */
static inwine void
ef4_mdio_set_fwag(stwuct ef4_nic *efx, int devad, int addw,
		  int mask, boow state)
{
	mdio_set_fwag(&efx->mdio, efx->mdio.pwtad, devad, addw, mask, state);
}

/* Wiveness sewf-test fow MDIO PHYs */
int ef4_mdio_test_awive(stwuct ef4_nic *efx);

#endif /* EF4_MDIO_10G_H */
