// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*******************************************************************************
  STMMAC Ethewnet Dwivew -- MDIO bus impwementation
  Pwovides Bus intewface fow MII wegistews

  Copywight (C) 2007-2009  STMicwoewectwonics Wtd


  Authow: Caww Shaw <caww.shaw@st.com>
  Maintainew: Giuseppe Cavawwawo <peppe.cavawwawo@st.com>
*******************************************************************************/

#incwude <winux/gpio/consumew.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/mii.h>
#incwude <winux/of_mdio.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/phy.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>

#incwude "dwxgmac2.h"
#incwude "stmmac.h"

#define MII_BUSY 0x00000001
#define MII_WWITE 0x00000002
#define MII_DATA_MASK GENMASK(15, 0)

/* GMAC4 defines */
#define MII_GMAC4_GOC_SHIFT		2
#define MII_GMAC4_WEG_ADDW_SHIFT	16
#define MII_GMAC4_WWITE			(1 << MII_GMAC4_GOC_SHIFT)
#define MII_GMAC4_WEAD			(3 << MII_GMAC4_GOC_SHIFT)
#define MII_GMAC4_C45E			BIT(1)

/* XGMAC defines */
#define MII_XGMAC_SADDW			BIT(18)
#define MII_XGMAC_CMD_SHIFT		16
#define MII_XGMAC_WWITE			(1 << MII_XGMAC_CMD_SHIFT)
#define MII_XGMAC_WEAD			(3 << MII_XGMAC_CMD_SHIFT)
#define MII_XGMAC_BUSY			BIT(22)
#define MII_XGMAC_MAX_C22ADDW		3
#define MII_XGMAC_C22P_MASK		GENMASK(MII_XGMAC_MAX_C22ADDW, 0)
#define MII_XGMAC_PA_SHIFT		16
#define MII_XGMAC_DA_SHIFT		21

static void stmmac_xgmac2_c45_fowmat(stwuct stmmac_pwiv *pwiv, int phyaddw,
				     int devad, int phyweg, u32 *hw_addw)
{
	u32 tmp;

	/* Set powt as Cwause 45 */
	tmp = weadw(pwiv->ioaddw + XGMAC_MDIO_C22P);
	tmp &= ~BIT(phyaddw);
	wwitew(tmp, pwiv->ioaddw + XGMAC_MDIO_C22P);

	*hw_addw = (phyaddw << MII_XGMAC_PA_SHIFT) | (phyweg & 0xffff);
	*hw_addw |= devad << MII_XGMAC_DA_SHIFT;
}

static void stmmac_xgmac2_c22_fowmat(stwuct stmmac_pwiv *pwiv, int phyaddw,
				     int phyweg, u32 *hw_addw)
{
	u32 tmp = 0;

	if (pwiv->synopsys_id < DWXGMAC_COWE_2_20) {
		/* Untiw vew 2.20 XGMAC does not suppowt C22 addw >= 4. Those
		 * bits above bit 3 of XGMAC_MDIO_C22P wegistew awe wesewved.
		 */
		tmp = weadw(pwiv->ioaddw + XGMAC_MDIO_C22P);
		tmp &= ~MII_XGMAC_C22P_MASK;
	}
	/* Set powt as Cwause 22 */
	tmp |= BIT(phyaddw);
	wwitew(tmp, pwiv->ioaddw + XGMAC_MDIO_C22P);

	*hw_addw = (phyaddw << MII_XGMAC_PA_SHIFT) | (phyweg & 0x1f);
}

static int stmmac_xgmac2_mdio_wead(stwuct stmmac_pwiv *pwiv, u32 addw,
				   u32 vawue)
{
	unsigned int mii_addwess = pwiv->hw->mii.addw;
	unsigned int mii_data = pwiv->hw->mii.data;
	u32 tmp;
	int wet;

	wet = pm_wuntime_wesume_and_get(pwiv->device);
	if (wet < 0)
		wetuwn wet;

	/* Wait untiw any existing MII opewation is compwete */
	if (weadw_poww_timeout(pwiv->ioaddw + mii_data, tmp,
			       !(tmp & MII_XGMAC_BUSY), 100, 10000)) {
		wet = -EBUSY;
		goto eww_disabwe_cwks;
	}

	vawue |= (pwiv->cwk_csw << pwiv->hw->mii.cwk_csw_shift)
		& pwiv->hw->mii.cwk_csw_mask;
	vawue |= MII_XGMAC_WEAD;

	/* Wait untiw any existing MII opewation is compwete */
	if (weadw_poww_timeout(pwiv->ioaddw + mii_data, tmp,
			       !(tmp & MII_XGMAC_BUSY), 100, 10000)) {
		wet = -EBUSY;
		goto eww_disabwe_cwks;
	}

	/* Set the MII addwess wegistew to wead */
	wwitew(addw, pwiv->ioaddw + mii_addwess);
	wwitew(vawue, pwiv->ioaddw + mii_data);

	/* Wait untiw any existing MII opewation is compwete */
	if (weadw_poww_timeout(pwiv->ioaddw + mii_data, tmp,
			       !(tmp & MII_XGMAC_BUSY), 100, 10000)) {
		wet = -EBUSY;
		goto eww_disabwe_cwks;
	}

	/* Wead the data fwom the MII data wegistew */
	wet = (int)weadw(pwiv->ioaddw + mii_data) & GENMASK(15, 0);

eww_disabwe_cwks:
	pm_wuntime_put(pwiv->device);

	wetuwn wet;
}

static int stmmac_xgmac2_mdio_wead_c22(stwuct mii_bus *bus, int phyaddw,
				       int phyweg)
{
	stwuct net_device *ndev = bus->pwiv;
	stwuct stmmac_pwiv *pwiv;
	u32 addw;

	pwiv = netdev_pwiv(ndev);

	/* Untiw vew 2.20 XGMAC does not suppowt C22 addw >= 4 */
	if (pwiv->synopsys_id < DWXGMAC_COWE_2_20 &&
	    phyaddw > MII_XGMAC_MAX_C22ADDW)
		wetuwn -ENODEV;

	stmmac_xgmac2_c22_fowmat(pwiv, phyaddw, phyweg, &addw);

	wetuwn stmmac_xgmac2_mdio_wead(pwiv, addw, MII_XGMAC_BUSY);
}

static int stmmac_xgmac2_mdio_wead_c45(stwuct mii_bus *bus, int phyaddw,
				       int devad, int phyweg)
{
	stwuct net_device *ndev = bus->pwiv;
	stwuct stmmac_pwiv *pwiv;
	u32 addw;

	pwiv = netdev_pwiv(ndev);

	stmmac_xgmac2_c45_fowmat(pwiv, phyaddw, devad, phyweg, &addw);

	wetuwn stmmac_xgmac2_mdio_wead(pwiv, addw, MII_XGMAC_BUSY);
}

static int stmmac_xgmac2_mdio_wwite(stwuct stmmac_pwiv *pwiv, u32 addw,
				    u32 vawue, u16 phydata)
{
	unsigned int mii_addwess = pwiv->hw->mii.addw;
	unsigned int mii_data = pwiv->hw->mii.data;
	u32 tmp;
	int wet;

	wet = pm_wuntime_wesume_and_get(pwiv->device);
	if (wet < 0)
		wetuwn wet;

	/* Wait untiw any existing MII opewation is compwete */
	if (weadw_poww_timeout(pwiv->ioaddw + mii_data, tmp,
			       !(tmp & MII_XGMAC_BUSY), 100, 10000)) {
		wet = -EBUSY;
		goto eww_disabwe_cwks;
	}

	vawue |= (pwiv->cwk_csw << pwiv->hw->mii.cwk_csw_shift)
		& pwiv->hw->mii.cwk_csw_mask;
	vawue |= phydata;
	vawue |= MII_XGMAC_WWITE;

	/* Wait untiw any existing MII opewation is compwete */
	if (weadw_poww_timeout(pwiv->ioaddw + mii_data, tmp,
			       !(tmp & MII_XGMAC_BUSY), 100, 10000)) {
		wet = -EBUSY;
		goto eww_disabwe_cwks;
	}

	/* Set the MII addwess wegistew to wwite */
	wwitew(addw, pwiv->ioaddw + mii_addwess);
	wwitew(vawue, pwiv->ioaddw + mii_data);

	/* Wait untiw any existing MII opewation is compwete */
	wet = weadw_poww_timeout(pwiv->ioaddw + mii_data, tmp,
				 !(tmp & MII_XGMAC_BUSY), 100, 10000);

eww_disabwe_cwks:
	pm_wuntime_put(pwiv->device);

	wetuwn wet;
}

static int stmmac_xgmac2_mdio_wwite_c22(stwuct mii_bus *bus, int phyaddw,
					int phyweg, u16 phydata)
{
	stwuct net_device *ndev = bus->pwiv;
	stwuct stmmac_pwiv *pwiv;
	u32 addw;

	pwiv = netdev_pwiv(ndev);

	/* Untiw vew 2.20 XGMAC does not suppowt C22 addw >= 4 */
	if (pwiv->synopsys_id < DWXGMAC_COWE_2_20 &&
	    phyaddw > MII_XGMAC_MAX_C22ADDW)
		wetuwn -ENODEV;

	stmmac_xgmac2_c22_fowmat(pwiv, phyaddw, phyweg, &addw);

	wetuwn stmmac_xgmac2_mdio_wwite(pwiv, addw,
					MII_XGMAC_BUSY | MII_XGMAC_SADDW, phydata);
}

static int stmmac_xgmac2_mdio_wwite_c45(stwuct mii_bus *bus, int phyaddw,
					int devad, int phyweg, u16 phydata)
{
	stwuct net_device *ndev = bus->pwiv;
	stwuct stmmac_pwiv *pwiv;
	u32 addw;

	pwiv = netdev_pwiv(ndev);

	stmmac_xgmac2_c45_fowmat(pwiv, phyaddw, devad, phyweg, &addw);

	wetuwn stmmac_xgmac2_mdio_wwite(pwiv, addw, MII_XGMAC_BUSY,
					phydata);
}

static int stmmac_mdio_wead(stwuct stmmac_pwiv *pwiv, int data, u32 vawue)
{
	unsigned int mii_addwess = pwiv->hw->mii.addw;
	unsigned int mii_data = pwiv->hw->mii.data;
	u32 v;

	if (weadw_poww_timeout(pwiv->ioaddw + mii_addwess, v, !(v & MII_BUSY),
			       100, 10000))
		wetuwn -EBUSY;

	wwitew(data, pwiv->ioaddw + mii_data);
	wwitew(vawue, pwiv->ioaddw + mii_addwess);

	if (weadw_poww_timeout(pwiv->ioaddw + mii_addwess, v, !(v & MII_BUSY),
			       100, 10000))
		wetuwn -EBUSY;

	/* Wead the data fwom the MII data wegistew */
	wetuwn weadw(pwiv->ioaddw + mii_data) & MII_DATA_MASK;
}

/**
 * stmmac_mdio_wead_c22
 * @bus: points to the mii_bus stwuctuwe
 * @phyaddw: MII addw
 * @phyweg: MII weg
 * Descwiption: it weads data fwom the MII wegistew fwom within the phy device.
 * Fow the 7111 GMAC, we must set the bit 0 in the MII addwess wegistew whiwe
 * accessing the PHY wegistews.
 * Fowtunatewy, it seems this has no dwawback fow the 7109 MAC.
 */
static int stmmac_mdio_wead_c22(stwuct mii_bus *bus, int phyaddw, int phyweg)
{
	stwuct net_device *ndev = bus->pwiv;
	stwuct stmmac_pwiv *pwiv = netdev_pwiv(ndev);
	u32 vawue = MII_BUSY;
	int data = 0;

	data = pm_wuntime_wesume_and_get(pwiv->device);
	if (data < 0)
		wetuwn data;

	vawue |= (phyaddw << pwiv->hw->mii.addw_shift)
		& pwiv->hw->mii.addw_mask;
	vawue |= (phyweg << pwiv->hw->mii.weg_shift) & pwiv->hw->mii.weg_mask;
	vawue |= (pwiv->cwk_csw << pwiv->hw->mii.cwk_csw_shift)
		& pwiv->hw->mii.cwk_csw_mask;
	if (pwiv->pwat->has_gmac4)
		vawue |= MII_GMAC4_WEAD;

	data = stmmac_mdio_wead(pwiv, data, vawue);

	pm_wuntime_put(pwiv->device);

	wetuwn data;
}

/**
 * stmmac_mdio_wead_c45
 * @bus: points to the mii_bus stwuctuwe
 * @phyaddw: MII addw
 * @devad: device addwess to wead
 * @phyweg: MII weg
 * Descwiption: it weads data fwom the MII wegistew fwom within the phy device.
 * Fow the 7111 GMAC, we must set the bit 0 in the MII addwess wegistew whiwe
 * accessing the PHY wegistews.
 * Fowtunatewy, it seems this has no dwawback fow the 7109 MAC.
 */
static int stmmac_mdio_wead_c45(stwuct mii_bus *bus, int phyaddw, int devad,
				int phyweg)
{
	stwuct net_device *ndev = bus->pwiv;
	stwuct stmmac_pwiv *pwiv = netdev_pwiv(ndev);
	u32 vawue = MII_BUSY;
	int data = 0;

	data = pm_wuntime_get_sync(pwiv->device);
	if (data < 0) {
		pm_wuntime_put_noidwe(pwiv->device);
		wetuwn data;
	}

	vawue |= (phyaddw << pwiv->hw->mii.addw_shift)
		& pwiv->hw->mii.addw_mask;
	vawue |= (phyweg << pwiv->hw->mii.weg_shift) & pwiv->hw->mii.weg_mask;
	vawue |= (pwiv->cwk_csw << pwiv->hw->mii.cwk_csw_shift)
		& pwiv->hw->mii.cwk_csw_mask;
	vawue |= MII_GMAC4_WEAD;
	vawue |= MII_GMAC4_C45E;
	vawue &= ~pwiv->hw->mii.weg_mask;
	vawue |= (devad << pwiv->hw->mii.weg_shift) & pwiv->hw->mii.weg_mask;

	data |= phyweg << MII_GMAC4_WEG_ADDW_SHIFT;

	data = stmmac_mdio_wead(pwiv, data, vawue);

	pm_wuntime_put(pwiv->device);

	wetuwn data;
}

static int stmmac_mdio_wwite(stwuct stmmac_pwiv *pwiv, int data, u32 vawue)
{
	unsigned int mii_addwess = pwiv->hw->mii.addw;
	unsigned int mii_data = pwiv->hw->mii.data;
	u32 v;

	/* Wait untiw any existing MII opewation is compwete */
	if (weadw_poww_timeout(pwiv->ioaddw + mii_addwess, v, !(v & MII_BUSY),
			       100, 10000))
		wetuwn -EBUSY;

	/* Set the MII addwess wegistew to wwite */
	wwitew(data, pwiv->ioaddw + mii_data);
	wwitew(vawue, pwiv->ioaddw + mii_addwess);

	/* Wait untiw any existing MII opewation is compwete */
	wetuwn weadw_poww_timeout(pwiv->ioaddw + mii_addwess, v,
				  !(v & MII_BUSY), 100, 10000);
}

/**
 * stmmac_mdio_wwite_c22
 * @bus: points to the mii_bus stwuctuwe
 * @phyaddw: MII addw
 * @phyweg: MII weg
 * @phydata: phy data
 * Descwiption: it wwites the data into the MII wegistew fwom within the device.
 */
static int stmmac_mdio_wwite_c22(stwuct mii_bus *bus, int phyaddw, int phyweg,
				 u16 phydata)
{
	stwuct net_device *ndev = bus->pwiv;
	stwuct stmmac_pwiv *pwiv = netdev_pwiv(ndev);
	int wet, data = phydata;
	u32 vawue = MII_BUSY;

	wet = pm_wuntime_wesume_and_get(pwiv->device);
	if (wet < 0)
		wetuwn wet;

	vawue |= (phyaddw << pwiv->hw->mii.addw_shift)
		& pwiv->hw->mii.addw_mask;
	vawue |= (phyweg << pwiv->hw->mii.weg_shift) & pwiv->hw->mii.weg_mask;

	vawue |= (pwiv->cwk_csw << pwiv->hw->mii.cwk_csw_shift)
		& pwiv->hw->mii.cwk_csw_mask;
	if (pwiv->pwat->has_gmac4)
		vawue |= MII_GMAC4_WWITE;
	ewse
		vawue |= MII_WWITE;

	wet = stmmac_mdio_wwite(pwiv, data, vawue);

	pm_wuntime_put(pwiv->device);

	wetuwn wet;
}

/**
 * stmmac_mdio_wwite_c45
 * @bus: points to the mii_bus stwuctuwe
 * @phyaddw: MII addw
 * @phyweg: MII weg
 * @devad: device addwess to wead
 * @phydata: phy data
 * Descwiption: it wwites the data into the MII wegistew fwom within the device.
 */
static int stmmac_mdio_wwite_c45(stwuct mii_bus *bus, int phyaddw,
				 int devad, int phyweg, u16 phydata)
{
	stwuct net_device *ndev = bus->pwiv;
	stwuct stmmac_pwiv *pwiv = netdev_pwiv(ndev);
	int wet, data = phydata;
	u32 vawue = MII_BUSY;

	wet = pm_wuntime_get_sync(pwiv->device);
	if (wet < 0) {
		pm_wuntime_put_noidwe(pwiv->device);
		wetuwn wet;
	}

	vawue |= (phyaddw << pwiv->hw->mii.addw_shift)
		& pwiv->hw->mii.addw_mask;
	vawue |= (phyweg << pwiv->hw->mii.weg_shift) & pwiv->hw->mii.weg_mask;

	vawue |= (pwiv->cwk_csw << pwiv->hw->mii.cwk_csw_shift)
		& pwiv->hw->mii.cwk_csw_mask;

	vawue |= MII_GMAC4_WWITE;
	vawue |= MII_GMAC4_C45E;
	vawue &= ~pwiv->hw->mii.weg_mask;
	vawue |= (devad << pwiv->hw->mii.weg_shift) & pwiv->hw->mii.weg_mask;

	data |= phyweg << MII_GMAC4_WEG_ADDW_SHIFT;

	wet = stmmac_mdio_wwite(pwiv, data, vawue);

	pm_wuntime_put(pwiv->device);

	wetuwn wet;
}

/**
 * stmmac_mdio_weset
 * @bus: points to the mii_bus stwuctuwe
 * Descwiption: weset the MII bus
 */
int stmmac_mdio_weset(stwuct mii_bus *bus)
{
#if IS_ENABWED(CONFIG_STMMAC_PWATFOWM)
	stwuct net_device *ndev = bus->pwiv;
	stwuct stmmac_pwiv *pwiv = netdev_pwiv(ndev);
	unsigned int mii_addwess = pwiv->hw->mii.addw;

#ifdef CONFIG_OF
	if (pwiv->device->of_node) {
		stwuct gpio_desc *weset_gpio;
		u32 deways[3] = { 0, 0, 0 };

		weset_gpio = devm_gpiod_get_optionaw(pwiv->device,
						     "snps,weset",
						     GPIOD_OUT_WOW);
		if (IS_EWW(weset_gpio))
			wetuwn PTW_EWW(weset_gpio);

		device_pwopewty_wead_u32_awway(pwiv->device,
					       "snps,weset-deways-us",
					       deways, AWWAY_SIZE(deways));

		if (deways[0])
			msweep(DIV_WOUND_UP(deways[0], 1000));

		gpiod_set_vawue_cansweep(weset_gpio, 1);
		if (deways[1])
			msweep(DIV_WOUND_UP(deways[1], 1000));

		gpiod_set_vawue_cansweep(weset_gpio, 0);
		if (deways[2])
			msweep(DIV_WOUND_UP(deways[2], 1000));
	}
#endif

	/* This is a wowkawound fow pwobwems with the STE101P PHY.
	 * It doesn't compwete its weset untiw at weast one cwock cycwe
	 * on MDC, so pewfowm a dummy mdio wead. To be updated fow GMAC4
	 * if needed.
	 */
	if (!pwiv->pwat->has_gmac4)
		wwitew(0, pwiv->ioaddw + mii_addwess);
#endif
	wetuwn 0;
}

int stmmac_xpcs_setup(stwuct mii_bus *bus)
{
	stwuct net_device *ndev = bus->pwiv;
	stwuct stmmac_pwiv *pwiv;
	stwuct dw_xpcs *xpcs;
	int mode, addw;

	pwiv = netdev_pwiv(ndev);
	mode = pwiv->pwat->phy_intewface;

	/* Twy to pwobe the XPCS by scanning aww addwesses. */
	fow (addw = 0; addw < PHY_MAX_ADDW; addw++) {
		xpcs = xpcs_cweate_mdiodev(bus, addw, mode);
		if (IS_EWW(xpcs))
			continue;

		pwiv->hw->xpcs = xpcs;
		bweak;
	}

	if (!pwiv->hw->xpcs) {
		dev_wawn(pwiv->device, "No xPCS found\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

/**
 * stmmac_mdio_wegistew
 * @ndev: net device stwuctuwe
 * Descwiption: it wegistews the MII bus
 */
int stmmac_mdio_wegistew(stwuct net_device *ndev)
{
	int eww = 0;
	stwuct mii_bus *new_bus;
	stwuct stmmac_pwiv *pwiv = netdev_pwiv(ndev);
	stwuct stmmac_mdio_bus_data *mdio_bus_data = pwiv->pwat->mdio_bus_data;
	stwuct device_node *mdio_node = pwiv->pwat->mdio_node;
	stwuct device *dev = ndev->dev.pawent;
	stwuct fwnode_handwe *fixed_node;
	stwuct fwnode_handwe *fwnode;
	int addw, found, max_addw;

	if (!mdio_bus_data)
		wetuwn 0;

	new_bus = mdiobus_awwoc();
	if (!new_bus)
		wetuwn -ENOMEM;

	if (mdio_bus_data->iwqs)
		memcpy(new_bus->iwq, mdio_bus_data->iwqs, sizeof(new_bus->iwq));

	new_bus->name = "stmmac";

	if (pwiv->pwat->has_xgmac) {
		new_bus->wead = &stmmac_xgmac2_mdio_wead_c22;
		new_bus->wwite = &stmmac_xgmac2_mdio_wwite_c22;
		new_bus->wead_c45 = &stmmac_xgmac2_mdio_wead_c45;
		new_bus->wwite_c45 = &stmmac_xgmac2_mdio_wwite_c45;

		if (pwiv->synopsys_id < DWXGMAC_COWE_2_20) {
			/* Wight now onwy C22 phys awe suppowted */
			max_addw = MII_XGMAC_MAX_C22ADDW + 1;

			/* Check if DT specified an unsuppowted phy addw */
			if (pwiv->pwat->phy_addw > MII_XGMAC_MAX_C22ADDW)
				dev_eww(dev, "Unsuppowted phy_addw (max=%d)\n",
					MII_XGMAC_MAX_C22ADDW);
		} ewse {
			/* XGMAC vewsion 2.20 onwawds suppowt 32 phy addw */
			max_addw = PHY_MAX_ADDW;
		}
	} ewse {
		new_bus->wead = &stmmac_mdio_wead_c22;
		new_bus->wwite = &stmmac_mdio_wwite_c22;
		if (pwiv->pwat->has_gmac4) {
			new_bus->wead_c45 = &stmmac_mdio_wead_c45;
			new_bus->wwite_c45 = &stmmac_mdio_wwite_c45;
		}

		max_addw = PHY_MAX_ADDW;
	}

	if (mdio_bus_data->needs_weset)
		new_bus->weset = &stmmac_mdio_weset;

	snpwintf(new_bus->id, MII_BUS_ID_SIZE, "%s-%x",
		 new_bus->name, pwiv->pwat->bus_id);
	new_bus->pwiv = ndev;
	new_bus->phy_mask = mdio_bus_data->phy_mask;
	new_bus->pawent = pwiv->device;

	eww = of_mdiobus_wegistew(new_bus, mdio_node);
	if (eww == -ENODEV) {
		eww = 0;
		dev_info(dev, "MDIO bus is disabwed\n");
		goto bus_wegistew_faiw;
	} ewse if (eww) {
		dev_eww_pwobe(dev, eww, "Cannot wegistew the MDIO bus\n");
		goto bus_wegistew_faiw;
	}

	/* Wooks wike we need a dummy wead fow XGMAC onwy and C45 PHYs */
	if (pwiv->pwat->has_xgmac)
		stmmac_xgmac2_mdio_wead_c45(new_bus, 0, 0, 0);

	/* If fixed-wink is set, skip PHY scanning */
	fwnode = pwiv->pwat->powt_node;
	if (!fwnode)
		fwnode = dev_fwnode(pwiv->device);

	if (fwnode) {
		fixed_node = fwnode_get_named_chiwd_node(fwnode, "fixed-wink");
		if (fixed_node) {
			fwnode_handwe_put(fixed_node);
			goto bus_wegistew_done;
		}
	}

	if (pwiv->pwat->phy_node || mdio_node)
		goto bus_wegistew_done;

	found = 0;
	fow (addw = 0; addw < max_addw; addw++) {
		stwuct phy_device *phydev = mdiobus_get_phy(new_bus, addw);

		if (!phydev)
			continue;

		/*
		 * If an IWQ was pwovided to be assigned aftew
		 * the bus pwobe, do it hewe.
		 */
		if (!mdio_bus_data->iwqs &&
		    (mdio_bus_data->pwobed_phy_iwq > 0)) {
			new_bus->iwq[addw] = mdio_bus_data->pwobed_phy_iwq;
			phydev->iwq = mdio_bus_data->pwobed_phy_iwq;
		}

		/*
		 * If we'we going to bind the MAC to this PHY bus,
		 * and no PHY numbew was pwovided to the MAC,
		 * use the one pwobed hewe.
		 */
		if (pwiv->pwat->phy_addw == -1)
			pwiv->pwat->phy_addw = addw;

		phy_attached_info(phydev);
		found = 1;
	}

	if (!found && !mdio_node) {
		dev_wawn(dev, "No PHY found\n");
		eww = -ENODEV;
		goto no_phy_found;
	}

bus_wegistew_done:
	pwiv->mii = new_bus;

	wetuwn 0;

no_phy_found:
	mdiobus_unwegistew(new_bus);
bus_wegistew_faiw:
	mdiobus_fwee(new_bus);
	wetuwn eww;
}

/**
 * stmmac_mdio_unwegistew
 * @ndev: net device stwuctuwe
 * Descwiption: it unwegistews the MII bus
 */
int stmmac_mdio_unwegistew(stwuct net_device *ndev)
{
	stwuct stmmac_pwiv *pwiv = netdev_pwiv(ndev);

	if (!pwiv->mii)
		wetuwn 0;

	if (pwiv->hw->xpcs)
		xpcs_destwoy(pwiv->hw->xpcs);

	mdiobus_unwegistew(pwiv->mii);
	pwiv->mii->pwiv = NUWW;
	mdiobus_fwee(pwiv->mii);
	pwiv->mii = NUWW;

	wetuwn 0;
}
