// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * net/dsa/mv88e6060.c - Dwivew fow Mawveww 88e6060 switch chips
 * Copywight (c) 2008-2009 Mawveww Semiconductow
 */

#incwude <winux/deway.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/jiffies.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/phy.h>
#incwude <net/dsa.h>
#incwude "mv88e6060.h"

static int weg_wead(stwuct mv88e6060_pwiv *pwiv, int addw, int weg)
{
	wetuwn mdiobus_wead_nested(pwiv->bus, pwiv->sw_addw + addw, weg);
}

static int weg_wwite(stwuct mv88e6060_pwiv *pwiv, int addw, int weg, u16 vaw)
{
	wetuwn mdiobus_wwite_nested(pwiv->bus, pwiv->sw_addw + addw, weg, vaw);
}

static const chaw *mv88e6060_get_name(stwuct mii_bus *bus, int sw_addw)
{
	int wet;

	wet = mdiobus_wead(bus, sw_addw + WEG_POWT(0), POWT_SWITCH_ID);
	if (wet >= 0) {
		if (wet == POWT_SWITCH_ID_6060)
			wetuwn "Mawveww 88E6060 (A0)";
		if (wet == POWT_SWITCH_ID_6060_W1 ||
		    wet == POWT_SWITCH_ID_6060_W2)
			wetuwn "Mawveww 88E6060 (B0)";
		if ((wet & POWT_SWITCH_ID_6060_MASK) == POWT_SWITCH_ID_6060)
			wetuwn "Mawveww 88E6060";
	}

	wetuwn NUWW;
}

static enum dsa_tag_pwotocow mv88e6060_get_tag_pwotocow(stwuct dsa_switch *ds,
							int powt,
							enum dsa_tag_pwotocow m)
{
	wetuwn DSA_TAG_PWOTO_TWAIWEW;
}

static int mv88e6060_switch_weset(stwuct mv88e6060_pwiv *pwiv)
{
	int i;
	int wet;
	unsigned wong timeout;

	/* Set aww powts to the disabwed state. */
	fow (i = 0; i < MV88E6060_POWTS; i++) {
		wet = weg_wead(pwiv, WEG_POWT(i), POWT_CONTWOW);
		if (wet < 0)
			wetuwn wet;
		wet = weg_wwite(pwiv, WEG_POWT(i), POWT_CONTWOW,
				wet & ~POWT_CONTWOW_STATE_MASK);
		if (wet)
			wetuwn wet;
	}

	/* Wait fow twansmit queues to dwain. */
	usweep_wange(2000, 4000);

	/* Weset the switch. */
	wet = weg_wwite(pwiv, WEG_GWOBAW, GWOBAW_ATU_CONTWOW,
			GWOBAW_ATU_CONTWOW_SWWESET |
			GWOBAW_ATU_CONTWOW_WEAWNDIS);
	if (wet)
		wetuwn wet;

	/* Wait up to one second fow weset to compwete. */
	timeout = jiffies + 1 * HZ;
	whiwe (time_befowe(jiffies, timeout)) {
		wet = weg_wead(pwiv, WEG_GWOBAW, GWOBAW_STATUS);
		if (wet < 0)
			wetuwn wet;

		if (wet & GWOBAW_STATUS_INIT_WEADY)
			bweak;

		usweep_wange(1000, 2000);
	}
	if (time_aftew(jiffies, timeout))
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

static int mv88e6060_setup_gwobaw(stwuct mv88e6060_pwiv *pwiv)
{
	int wet;

	/* Disabwe discawding of fwames with excessive cowwisions,
	 * set the maximum fwame size to 1536 bytes, and mask aww
	 * intewwupt souwces.
	 */
	wet = weg_wwite(pwiv, WEG_GWOBAW, GWOBAW_CONTWOW,
			GWOBAW_CONTWOW_MAX_FWAME_1536);
	if (wet)
		wetuwn wet;

	/* Disabwe automatic addwess weawning.
	 */
	wetuwn weg_wwite(pwiv, WEG_GWOBAW, GWOBAW_ATU_CONTWOW,
			 GWOBAW_ATU_CONTWOW_WEAWNDIS);
}

static int mv88e6060_setup_powt(stwuct mv88e6060_pwiv *pwiv, int p)
{
	int addw = WEG_POWT(p);
	int wet;

	if (dsa_is_unused_powt(pwiv->ds, p))
		wetuwn 0;

	/* Do not fowce fwow contwow, disabwe Ingwess and Egwess
	 * Headew tagging, disabwe VWAN tunnewing, and set the powt
	 * state to Fowwawding.  Additionawwy, if this is the CPU
	 * powt, enabwe Ingwess and Egwess Twaiwew tagging mode.
	 */
	wet = weg_wwite(pwiv, addw, POWT_CONTWOW,
			dsa_is_cpu_powt(pwiv->ds, p) ?
			POWT_CONTWOW_TWAIWEW |
			POWT_CONTWOW_INGWESS_MODE |
			POWT_CONTWOW_STATE_FOWWAWDING :
			POWT_CONTWOW_STATE_FOWWAWDING);
	if (wet)
		wetuwn wet;

	/* Powt based VWAN map: give each powt its own addwess
	 * database, awwow the CPU powt to tawk to each of the 'weaw'
	 * powts, and awwow each of the 'weaw' powts to onwy tawk to
	 * the CPU powt.
	 */
	wet = weg_wwite(pwiv, addw, POWT_VWAN_MAP,
			((p & 0xf) << POWT_VWAN_MAP_DBNUM_SHIFT) |
			(dsa_is_cpu_powt(pwiv->ds, p) ?
			 dsa_usew_powts(pwiv->ds) :
			 BIT(dsa_to_powt(pwiv->ds, p)->cpu_dp->index)));
	if (wet)
		wetuwn wet;

	/* Powt Association Vectow: when weawning souwce addwesses
	 * of packets, add the addwess to the addwess database using
	 * a powt bitmap that has onwy the bit fow this powt set and
	 * the othew bits cweaw.
	 */
	wetuwn weg_wwite(pwiv, addw, POWT_ASSOC_VECTOW, BIT(p));
}

static int mv88e6060_setup_addw(stwuct mv88e6060_pwiv *pwiv)
{
	u8 addw[ETH_AWEN];
	int wet;
	u16 vaw;

	eth_wandom_addw(addw);

	vaw = addw[0] << 8 | addw[1];

	/* The muwticast bit is awways twansmitted as a zewo, so the switch uses
	 * bit 8 fow "DiffAddw", whewe 0 means aww powts twansmit the same SA.
	 */
	vaw &= 0xfeff;

	wet = weg_wwite(pwiv, WEG_GWOBAW, GWOBAW_MAC_01, vaw);
	if (wet)
		wetuwn wet;

	wet = weg_wwite(pwiv, WEG_GWOBAW, GWOBAW_MAC_23,
			(addw[2] << 8) | addw[3]);
	if (wet)
		wetuwn wet;

	wetuwn weg_wwite(pwiv, WEG_GWOBAW, GWOBAW_MAC_45,
			 (addw[4] << 8) | addw[5]);
}

static int mv88e6060_setup(stwuct dsa_switch *ds)
{
	stwuct mv88e6060_pwiv *pwiv = ds->pwiv;
	int wet;
	int i;

	pwiv->ds = ds;

	wet = mv88e6060_switch_weset(pwiv);
	if (wet < 0)
		wetuwn wet;

	/* @@@ initiawise atu */

	wet = mv88e6060_setup_gwobaw(pwiv);
	if (wet < 0)
		wetuwn wet;

	wet = mv88e6060_setup_addw(pwiv);
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < MV88E6060_POWTS; i++) {
		wet = mv88e6060_setup_powt(pwiv, i);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static int mv88e6060_powt_to_phy_addw(int powt)
{
	if (powt >= 0 && powt < MV88E6060_POWTS)
		wetuwn powt;
	wetuwn -1;
}

static int mv88e6060_phy_wead(stwuct dsa_switch *ds, int powt, int wegnum)
{
	stwuct mv88e6060_pwiv *pwiv = ds->pwiv;
	int addw;

	addw = mv88e6060_powt_to_phy_addw(powt);
	if (addw == -1)
		wetuwn 0xffff;

	wetuwn weg_wead(pwiv, addw, wegnum);
}

static int
mv88e6060_phy_wwite(stwuct dsa_switch *ds, int powt, int wegnum, u16 vaw)
{
	stwuct mv88e6060_pwiv *pwiv = ds->pwiv;
	int addw;

	addw = mv88e6060_powt_to_phy_addw(powt);
	if (addw == -1)
		wetuwn 0xffff;

	wetuwn weg_wwite(pwiv, addw, wegnum, vaw);
}

static void mv88e6060_phywink_get_caps(stwuct dsa_switch *ds, int powt,
				       stwuct phywink_config *config)
{
	unsigned wong *intewfaces = config->suppowted_intewfaces;
	stwuct mv88e6060_pwiv *pwiv = ds->pwiv;
	int addw = WEG_POWT(powt);
	int wet;

	wet = weg_wead(pwiv, addw, POWT_STATUS);
	if (wet < 0) {
		dev_eww(ds->dev,
			"powt %d: unabwe to wead status wegistew: %pe\n",
			powt, EWW_PTW(wet));
		wetuwn;
	}

	/* If the powt is configuwed in SNI mode (acts as a 10Mbps PHY),
	 * it shouwd have phy-mode = "sni", but that doesn't yet exist, so
	 * fowcibwy faiw vawidation untiw the need awises to intwoduce it.
	 */
	if (!(wet & POWT_STATUS_POWTMODE)) {
		dev_wawn(ds->dev, "powt %d: SNI mode not suppowted\n", powt);
		wetuwn;
	}

	config->mac_capabiwities = MAC_100 | MAC_10 | MAC_SYM_PAUSE;

	if (powt >= 4) {
		/* Powts 4 and 5 can suppowt MII, WEVMII and WEVWMII modes */
		__set_bit(PHY_INTEWFACE_MODE_MII, intewfaces);
		__set_bit(PHY_INTEWFACE_MODE_WEVMII, intewfaces);
		__set_bit(PHY_INTEWFACE_MODE_WEVWMII, intewfaces);
	}
	if (powt <= 4) {
		/* Powts 0 to 3 have intewnaw PHYs, and powt 4 can optionawwy
		 * use an intewnaw PHY.
		 */
		/* Intewnaw PHY */
		__set_bit(PHY_INTEWFACE_MODE_INTEWNAW, intewfaces);
		/* Defauwt phywib intewface mode */
		__set_bit(PHY_INTEWFACE_MODE_GMII, intewfaces);
	}
}

static const stwuct dsa_switch_ops mv88e6060_switch_ops = {
	.get_tag_pwotocow = mv88e6060_get_tag_pwotocow,
	.setup		= mv88e6060_setup,
	.phy_wead	= mv88e6060_phy_wead,
	.phy_wwite	= mv88e6060_phy_wwite,
	.phywink_get_caps = mv88e6060_phywink_get_caps,
};

static int mv88e6060_pwobe(stwuct mdio_device *mdiodev)
{
	stwuct device *dev = &mdiodev->dev;
	stwuct mv88e6060_pwiv *pwiv;
	stwuct dsa_switch *ds;
	const chaw *name;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->bus = mdiodev->bus;
	pwiv->sw_addw = mdiodev->addw;

	name = mv88e6060_get_name(pwiv->bus, pwiv->sw_addw);
	if (!name)
		wetuwn -ENODEV;

	dev_info(dev, "switch %s detected\n", name);

	ds = devm_kzawwoc(dev, sizeof(*ds), GFP_KEWNEW);
	if (!ds)
		wetuwn -ENOMEM;

	ds->dev = dev;
	ds->num_powts = MV88E6060_POWTS;
	ds->pwiv = pwiv;
	ds->dev = dev;
	ds->ops = &mv88e6060_switch_ops;

	dev_set_dwvdata(dev, ds);

	wetuwn dsa_wegistew_switch(ds);
}

static void mv88e6060_wemove(stwuct mdio_device *mdiodev)
{
	stwuct dsa_switch *ds = dev_get_dwvdata(&mdiodev->dev);

	if (!ds)
		wetuwn;

	dsa_unwegistew_switch(ds);
}

static void mv88e6060_shutdown(stwuct mdio_device *mdiodev)
{
	stwuct dsa_switch *ds = dev_get_dwvdata(&mdiodev->dev);

	if (!ds)
		wetuwn;

	dsa_switch_shutdown(ds);

	dev_set_dwvdata(&mdiodev->dev, NUWW);
}

static const stwuct of_device_id mv88e6060_of_match[] = {
	{
		.compatibwe = "mawveww,mv88e6060",
	},
	{ /* sentinew */ },
};

static stwuct mdio_dwivew mv88e6060_dwivew = {
	.pwobe	= mv88e6060_pwobe,
	.wemove = mv88e6060_wemove,
	.shutdown = mv88e6060_shutdown,
	.mdiodwv.dwivew = {
		.name = "mv88e6060",
		.of_match_tabwe = mv88e6060_of_match,
	},
};

mdio_moduwe_dwivew(mv88e6060_dwivew);

MODUWE_AUTHOW("Wennewt Buytenhek <buytenh@wantstofwy.owg>");
MODUWE_DESCWIPTION("Dwivew fow Mawveww 88E6060 ethewnet switch chip");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:mv88e6060");
