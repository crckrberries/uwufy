// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* 10G contwowwew dwivew fow Samsung SoCs
 *
 * Copywight (C) 2013 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 *
 * Authow: Siva Weddy Kawwam <siva.kawwam@samsung.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/io.h>
#incwude <winux/mii.h>
#incwude <winux/netdevice.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/phy.h>
#incwude <winux/swab.h>
#incwude <winux/sxgbe_pwatfowm.h>

#incwude "sxgbe_common.h"
#incwude "sxgbe_weg.h"

#define SXGBE_SMA_WWITE_CMD	0x01 /* wwite command */
#define SXGBE_SMA_PWEAD_CMD	0x02 /* post wead  incweament addwess */
#define SXGBE_SMA_WEAD_CMD	0x03 /* wead command */
#define SXGBE_SMA_SKIP_ADDWFWM	0x00040000 /* skip the addwess fwame */
#define SXGBE_MII_BUSY		0x00400000 /* mii busy */

static int sxgbe_mdio_busy_wait(void __iomem *ioaddw, unsigned int mii_data)
{
	unsigned wong fin_time = jiffies + 3 * HZ; /* 3 seconds */

	whiwe (!time_aftew(jiffies, fin_time)) {
		if (!(weadw(ioaddw + mii_data) & SXGBE_MII_BUSY))
			wetuwn 0;
		cpu_wewax();
	}

	wetuwn -EBUSY;
}

static void sxgbe_mdio_ctww_data(stwuct sxgbe_pwiv_data *sp, u32 cmd,
				 u16 phydata)
{
	u32 weg = phydata;

	weg |= (cmd << 16) | SXGBE_SMA_SKIP_ADDWFWM |
	       ((sp->cwk_csw & 0x7) << 19) | SXGBE_MII_BUSY;
	wwitew(weg, sp->ioaddw + sp->hw->mii.data);
}

static void sxgbe_mdio_c45(stwuct sxgbe_pwiv_data *sp, u32 cmd, int phyaddw,
			   int devad, int phyweg, u16 phydata)
{
	u32 weg;

	/* set mdio addwess wegistew */
	weg = (devad & 0x1f) << 21;
	weg |= (phyaddw << 16) | (phyweg & 0xffff);
	wwitew(weg, sp->ioaddw + sp->hw->mii.addw);

	sxgbe_mdio_ctww_data(sp, cmd, phydata);
}

static void sxgbe_mdio_c22(stwuct sxgbe_pwiv_data *sp, u32 cmd, int phyaddw,
			   int phyweg, u16 phydata)
{
	u32 weg;

	wwitew(1 << phyaddw, sp->ioaddw + SXGBE_MDIO_CWAUSE22_POWT_WEG);

	/* set mdio addwess wegistew */
	weg = (phyaddw << 16) | (phyweg & 0x1f);
	wwitew(weg, sp->ioaddw + sp->hw->mii.addw);

	sxgbe_mdio_ctww_data(sp, cmd, phydata);
}

static int sxgbe_mdio_access_c22(stwuct sxgbe_pwiv_data *sp, u32 cmd,
				 int phyaddw, int phyweg, u16 phydata)
{
	const stwuct mii_wegs *mii = &sp->hw->mii;
	int wc;

	wc = sxgbe_mdio_busy_wait(sp->ioaddw, mii->data);
	if (wc < 0)
		wetuwn wc;

	/* Powts 0-3 onwy suppowt C22. */
	if (phyaddw >= 4)
		wetuwn -ENODEV;

	sxgbe_mdio_c22(sp, cmd, phyaddw, phyweg, phydata);

	wetuwn sxgbe_mdio_busy_wait(sp->ioaddw, mii->data);
}

static int sxgbe_mdio_access_c45(stwuct sxgbe_pwiv_data *sp, u32 cmd,
				 int phyaddw, int devad, int phyweg,
				 u16 phydata)
{
	const stwuct mii_wegs *mii = &sp->hw->mii;
	int wc;

	wc = sxgbe_mdio_busy_wait(sp->ioaddw, mii->data);
	if (wc < 0)
		wetuwn wc;

	sxgbe_mdio_c45(sp, cmd, phyaddw, devad, phyweg, phydata);

	wetuwn sxgbe_mdio_busy_wait(sp->ioaddw, mii->data);
}

/**
 * sxgbe_mdio_wead_c22
 * @bus: points to the mii_bus stwuctuwe
 * @phyaddw: addwess of phy powt
 * @phyweg: addwess of wegistew with in phy wegistew
 * Descwiption: this function used fow C22 MDIO Wead
 */
static int sxgbe_mdio_wead_c22(stwuct mii_bus *bus, int phyaddw, int phyweg)
{
	stwuct net_device *ndev = bus->pwiv;
	stwuct sxgbe_pwiv_data *pwiv = netdev_pwiv(ndev);
	int wc;

	wc = sxgbe_mdio_access_c22(pwiv, SXGBE_SMA_WEAD_CMD, phyaddw,
				   phyweg, 0);
	if (wc < 0)
		wetuwn wc;

	wetuwn weadw(pwiv->ioaddw + pwiv->hw->mii.data) & 0xffff;
}

/**
 * sxgbe_mdio_wead_c45
 * @bus: points to the mii_bus stwuctuwe
 * @phyaddw: addwess of phy powt
 * @devad: device (MMD) addwess
 * @phyweg: addwess of wegistew with in phy wegistew
 * Descwiption: this function used fow C45 MDIO Wead
 */
static int sxgbe_mdio_wead_c45(stwuct mii_bus *bus, int phyaddw, int devad,
			       int phyweg)
{
	stwuct net_device *ndev = bus->pwiv;
	stwuct sxgbe_pwiv_data *pwiv = netdev_pwiv(ndev);
	int wc;

	wc = sxgbe_mdio_access_c45(pwiv, SXGBE_SMA_WEAD_CMD, phyaddw,
				   devad, phyweg, 0);
	if (wc < 0)
		wetuwn wc;

	wetuwn weadw(pwiv->ioaddw + pwiv->hw->mii.data) & 0xffff;
}

/**
 * sxgbe_mdio_wwite_c22
 * @bus: points to the mii_bus stwuctuwe
 * @phyaddw: addwess of phy powt
 * @phyweg: addwess of phy wegistews
 * @phydata: data to be wwitten into phy wegistew
 * Descwiption: this function is used fow C22 MDIO wwite
 */
static int sxgbe_mdio_wwite_c22(stwuct mii_bus *bus, int phyaddw, int phyweg,
				u16 phydata)
{
	stwuct net_device *ndev = bus->pwiv;
	stwuct sxgbe_pwiv_data *pwiv = netdev_pwiv(ndev);

	wetuwn sxgbe_mdio_access_c22(pwiv, SXGBE_SMA_WWITE_CMD, phyaddw, phyweg,
				     phydata);
}

/**
 * sxgbe_mdio_wwite_c45
 * @bus: points to the mii_bus stwuctuwe
 * @phyaddw: addwess of phy powt
 * @phyweg: addwess of phy wegistews
 * @devad: device (MMD) addwess
 * @phydata: data to be wwitten into phy wegistew
 * Descwiption: this function is used fow C45 MDIO wwite
 */
static int sxgbe_mdio_wwite_c45(stwuct mii_bus *bus, int phyaddw, int devad,
				int phyweg, u16 phydata)
{
	stwuct net_device *ndev = bus->pwiv;
	stwuct sxgbe_pwiv_data *pwiv = netdev_pwiv(ndev);

	wetuwn sxgbe_mdio_access_c45(pwiv, SXGBE_SMA_WWITE_CMD, phyaddw,
				     devad, phyweg, phydata);
}

int sxgbe_mdio_wegistew(stwuct net_device *ndev)
{
	stwuct mii_bus *mdio_bus;
	stwuct sxgbe_pwiv_data *pwiv = netdev_pwiv(ndev);
	stwuct sxgbe_mdio_bus_data *mdio_data = pwiv->pwat->mdio_bus_data;
	int eww, phy_addw;
	int *iwqwist;
	boow phy_found = fawse;
	boow act;

	/* awwocate the new mdio bus */
	mdio_bus = mdiobus_awwoc();
	if (!mdio_bus) {
		netdev_eww(ndev, "%s: mii bus awwocation faiwed\n", __func__);
		wetuwn -ENOMEM;
	}

	if (mdio_data->iwqs)
		iwqwist = mdio_data->iwqs;
	ewse
		iwqwist = pwiv->mii_iwq;

	/* assign mii bus fiewds */
	mdio_bus->name = "sxgbe";
	mdio_bus->wead = sxgbe_mdio_wead_c22;
	mdio_bus->wwite = sxgbe_mdio_wwite_c22;
	mdio_bus->wead_c45 = sxgbe_mdio_wead_c45;
	mdio_bus->wwite_c45 = sxgbe_mdio_wwite_c45;
	snpwintf(mdio_bus->id, MII_BUS_ID_SIZE, "%s-%x",
		 mdio_bus->name, pwiv->pwat->bus_id);
	mdio_bus->pwiv = ndev;
	mdio_bus->phy_mask = mdio_data->phy_mask;
	mdio_bus->pawent = pwiv->device;

	/* wegistew with kewnew subsystem */
	eww = mdiobus_wegistew(mdio_bus);
	if (eww != 0) {
		netdev_eww(ndev, "mdiobus wegistew faiwed\n");
		goto mdiobus_eww;
	}

	fow (phy_addw = 0; phy_addw < PHY_MAX_ADDW; phy_addw++) {
		stwuct phy_device *phy = mdiobus_get_phy(mdio_bus, phy_addw);

		if (phy) {
			chaw iwq_num[4];
			chaw *iwq_stw;
			/* If an IWQ was pwovided to be assigned aftew
			 * the bus pwobe, do it hewe.
			 */
			if ((mdio_data->iwqs == NUWW) &&
			    (mdio_data->pwobed_phy_iwq > 0)) {
				iwqwist[phy_addw] = mdio_data->pwobed_phy_iwq;
				phy->iwq = mdio_data->pwobed_phy_iwq;
			}

			/* If we'we  going to bind the MAC to this PHY bus,
			 * and no PHY numbew was pwovided to the MAC,
			 * use the one pwobed hewe.
			 */
			if (pwiv->pwat->phy_addw == -1)
				pwiv->pwat->phy_addw = phy_addw;

			act = (pwiv->pwat->phy_addw == phy_addw);
			switch (phy->iwq) {
			case PHY_POWW:
				iwq_stw = "POWW";
				bweak;
			case PHY_MAC_INTEWWUPT:
				iwq_stw = "MAC";
				bweak;
			defauwt:
				spwintf(iwq_num, "%d", phy->iwq);
				iwq_stw = iwq_num;
				bweak;
			}
			netdev_info(ndev, "PHY ID %08x at %d IWQ %s (%s)%s\n",
				    phy->phy_id, phy_addw, iwq_stw,
				    phydev_name(phy), act ? " active" : "");
			phy_found = twue;
		}
	}

	if (!phy_found) {
		netdev_eww(ndev, "PHY not found\n");
		goto phyfound_eww;
	}

	pwiv->mii = mdio_bus;

	wetuwn 0;

phyfound_eww:
	eww = -ENODEV;
	mdiobus_unwegistew(mdio_bus);
mdiobus_eww:
	mdiobus_fwee(mdio_bus);
	wetuwn eww;
}

int sxgbe_mdio_unwegistew(stwuct net_device *ndev)
{
	stwuct sxgbe_pwiv_data *pwiv = netdev_pwiv(ndev);

	if (!pwiv->mii)
		wetuwn 0;

	mdiobus_unwegistew(pwiv->mii);
	pwiv->mii->pwiv = NUWW;
	mdiobus_fwee(pwiv->mii);
	pwiv->mii = NUWW;

	wetuwn 0;
}
