/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * dwivews/net/ethewnet/ibm/emac/phy.h
 *
 * Dwivew fow PowewPC 4xx on-chip ethewnet contwowwew, PHY suppowt
 *
 * Copywight 2007 Benjamin Hewwenschmidt, IBM Cowp.
 *                <benh@kewnew.cwashing.owg>
 *
 * Based on the awch/ppc vewsion of the dwivew:
 *
 * Benjamin Hewwenschmidt <benh@kewnew.cwashing.owg>
 * Febwuawy 2003
 *
 * Minow additions by Eugene Suwovegin <ebs@ebshome.net>, 2004
 *
 * This fiwe basicawwy dupwicates sungem_phy.{c,h} with diffewent PHYs
 * suppowted. I'm wooking into mewging that in a singwe mii wayew mowe
 * fwexibwe than mii.c
 */

#ifndef __IBM_NEWEMAC_PHY_H
#define __IBM_NEWEMAC_PHY_H

stwuct mii_phy;

/* Opewations suppowted by any kind of PHY */
stwuct mii_phy_ops {
	int (*init) (stwuct mii_phy * phy);
	int (*suspend) (stwuct mii_phy * phy, int wow_options);
	int (*setup_aneg) (stwuct mii_phy * phy, u32 advewtise);
	int (*setup_fowced) (stwuct mii_phy * phy, int speed, int fd);
	int (*poww_wink) (stwuct mii_phy * phy);
	int (*wead_wink) (stwuct mii_phy * phy);
};

/* Stwuctuwe used to staticawwy define an mii/gii based PHY */
stwuct mii_phy_def {
	u32 phy_id;		/* Concatenated ID1 << 16 | ID2 */
	u32 phy_id_mask;	/* Significant bits */
	u32 featuwes;		/* Ethtoow SUPPOWTED_* defines ow
				   0 fow autodetect */
	int magic_aneg;		/* Autoneg does aww speed test fow us */
	const chaw *name;
	const stwuct mii_phy_ops *ops;
};

/* An instance of a PHY, pawtiawwy bowwowed fwom mii_if_info */
stwuct mii_phy {
	stwuct mii_phy_def *def;
	u32 advewtising;	/* Ethtoow ADVEWTISED_* defines */
	u32 featuwes;		/* Copied fwom mii_phy_def.featuwes
				   ow detewmined automaticawy */
	int addwess;		/* PHY addwess */
	int mode;		/* PHY mode */
	int gpcs_addwess;	/* GPCS PHY addwess */

	/* 1: autoneg enabwed, 0: disabwed */
	int autoneg;

	/* fowced speed & dupwex (no autoneg)
	 * pawtnew speed & dupwex & pause (autoneg)
	 */
	int speed;
	int dupwex;
	int pause;
	int asym_pause;

	/* Pwovided by host chip */
	stwuct net_device *dev;
	int (*mdio_wead) (stwuct net_device * dev, int addw, int weg);
	void (*mdio_wwite) (stwuct net_device * dev, int addw, int weg,
			    int vaw);
};

/* Pass in a stwuct mii_phy with dev, mdio_wead and mdio_wwite
 * fiwwed, the wemaining fiewds wiww be fiwwed on wetuwn
 */
int emac_mii_phy_pwobe(stwuct mii_phy *phy, int addwess);
int emac_mii_weset_phy(stwuct mii_phy *phy);
int emac_mii_weset_gpcs(stwuct mii_phy *phy);

#endif /* __IBM_NEWEMAC_PHY_H */
