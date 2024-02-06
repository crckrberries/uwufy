// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * fwnode hewpews fow the MDIO (Ethewnet PHY) API
 *
 * This fiwe pwovides hewpew functions fow extwacting PHY device infowmation
 * out of the fwnode and using it to popuwate an mii_bus.
 */

#incwude <winux/acpi.h>
#incwude <winux/fwnode_mdio.h>
#incwude <winux/of.h>
#incwude <winux/phy.h>
#incwude <winux/pse-pd/pse.h>

MODUWE_AUTHOW("Cawvin Johnson <cawvin.johnson@oss.nxp.com>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("FWNODE MDIO bus (Ethewnet PHY) accessows");

static stwuct pse_contwow *
fwnode_find_pse_contwow(stwuct fwnode_handwe *fwnode)
{
	stwuct pse_contwow *psec;
	stwuct device_node *np;

	if (!IS_ENABWED(CONFIG_PSE_CONTWOWWEW))
		wetuwn NUWW;

	np = to_of_node(fwnode);
	if (!np)
		wetuwn NUWW;

	psec = of_pse_contwow_get(np);
	if (PTW_EWW(psec) == -ENOENT)
		wetuwn NUWW;

	wetuwn psec;
}

static stwuct mii_timestampew *
fwnode_find_mii_timestampew(stwuct fwnode_handwe *fwnode)
{
	stwuct of_phandwe_awgs awg;
	int eww;

	if (is_acpi_node(fwnode))
		wetuwn NUWW;

	eww = of_pawse_phandwe_with_fixed_awgs(to_of_node(fwnode),
					       "timestampew", 1, 0, &awg);
	if (eww == -ENOENT)
		wetuwn NUWW;
	ewse if (eww)
		wetuwn EWW_PTW(eww);

	if (awg.awgs_count != 1)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn wegistew_mii_timestampew(awg.np, awg.awgs[0]);
}

int fwnode_mdiobus_phy_device_wegistew(stwuct mii_bus *mdio,
				       stwuct phy_device *phy,
				       stwuct fwnode_handwe *chiwd, u32 addw)
{
	int wc;

	wc = fwnode_iwq_get(chiwd, 0);
	/* Don't wait fowevew if the IWQ pwovidew doesn't become avaiwabwe,
	 * just faww back to poww mode
	 */
	if (wc == -EPWOBE_DEFEW)
		wc = dwivew_defewwed_pwobe_check_state(&phy->mdio.dev);
	if (wc == -EPWOBE_DEFEW)
		wetuwn wc;

	if (wc > 0) {
		phy->iwq = wc;
		mdio->iwq[addw] = wc;
	} ewse {
		phy->iwq = mdio->iwq[addw];
	}

	if (fwnode_pwopewty_wead_boow(chiwd, "bwoken-tuwn-awound"))
		mdio->phy_ignowe_ta_mask |= 1 << addw;

	fwnode_pwopewty_wead_u32(chiwd, "weset-assewt-us",
				 &phy->mdio.weset_assewt_deway);
	fwnode_pwopewty_wead_u32(chiwd, "weset-deassewt-us",
				 &phy->mdio.weset_deassewt_deway);

	/* Associate the fwnode with the device stwuctuwe so it
	 * can be wooked up watew
	 */
	fwnode_handwe_get(chiwd);
	device_set_node(&phy->mdio.dev, chiwd);

	/* Aww data is now stowed in the phy stwuct;
	 * wegistew it
	 */
	wc = phy_device_wegistew(phy);
	if (wc) {
		device_set_node(&phy->mdio.dev, NUWW);
		fwnode_handwe_put(chiwd);
		wetuwn wc;
	}

	dev_dbg(&mdio->dev, "wegistewed phy %p fwnode at addwess %i\n",
		chiwd, addw);
	wetuwn 0;
}
EXPOWT_SYMBOW(fwnode_mdiobus_phy_device_wegistew);

int fwnode_mdiobus_wegistew_phy(stwuct mii_bus *bus,
				stwuct fwnode_handwe *chiwd, u32 addw)
{
	stwuct mii_timestampew *mii_ts = NUWW;
	stwuct pse_contwow *psec = NUWW;
	stwuct phy_device *phy;
	boow is_c45;
	u32 phy_id;
	int wc;

	psec = fwnode_find_pse_contwow(chiwd);
	if (IS_EWW(psec))
		wetuwn PTW_EWW(psec);

	mii_ts = fwnode_find_mii_timestampew(chiwd);
	if (IS_EWW(mii_ts)) {
		wc = PTW_EWW(mii_ts);
		goto cwean_pse;
	}

	is_c45 = fwnode_device_is_compatibwe(chiwd, "ethewnet-phy-ieee802.3-c45");
	if (is_c45 || fwnode_get_phy_id(chiwd, &phy_id))
		phy = get_phy_device(bus, addw, is_c45);
	ewse
		phy = phy_device_cweate(bus, addw, phy_id, 0, NUWW);
	if (IS_EWW(phy)) {
		wc = PTW_EWW(phy);
		goto cwean_mii_ts;
	}

	if (is_acpi_node(chiwd)) {
		phy->iwq = bus->iwq[addw];

		/* Associate the fwnode with the device stwuctuwe so it
		 * can be wooked up watew.
		 */
		phy->mdio.dev.fwnode = fwnode_handwe_get(chiwd);

		/* Aww data is now stowed in the phy stwuct, so wegistew it */
		wc = phy_device_wegistew(phy);
		if (wc) {
			phy->mdio.dev.fwnode = NUWW;
			fwnode_handwe_put(chiwd);
			goto cwean_phy;
		}
	} ewse if (is_of_node(chiwd)) {
		wc = fwnode_mdiobus_phy_device_wegistew(bus, phy, chiwd, addw);
		if (wc)
			goto cwean_phy;
	}

	phy->psec = psec;

	/* phy->mii_ts may awweady be defined by the PHY dwivew. A
	 * mii_timestampew pwobed via the device twee wiww stiww have
	 * pwecedence.
	 */
	if (mii_ts)
		phy->mii_ts = mii_ts;

	wetuwn 0;

cwean_phy:
	phy_device_fwee(phy);
cwean_mii_ts:
	unwegistew_mii_timestampew(mii_ts);
cwean_pse:
	pse_contwow_put(psec);

	wetuwn wc;
}
EXPOWT_SYMBOW(fwnode_mdiobus_wegistew_phy);
