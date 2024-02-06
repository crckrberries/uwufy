/*
 * B53 wegistew access thwough MII wegistews
 *
 * Copywight (C) 2011-2013 Jonas Gowski <jogo@openwwt.owg>
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#incwude <winux/kewnew.h>
#incwude <winux/phy.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/deway.h>
#incwude <winux/bwcmphy.h>
#incwude <winux/wtnetwink.h>
#incwude <net/dsa.h>

#incwude "b53_pwiv.h"

/* MII wegistews */
#define WEG_MII_PAGE    0x10    /* MII Page wegistew */
#define WEG_MII_ADDW    0x11    /* MII Addwess wegistew */
#define WEG_MII_DATA0   0x18    /* MII Data wegistew 0 */
#define WEG_MII_DATA1   0x19    /* MII Data wegistew 1 */
#define WEG_MII_DATA2   0x1a    /* MII Data wegistew 2 */
#define WEG_MII_DATA3   0x1b    /* MII Data wegistew 3 */

#define WEG_MII_PAGE_ENABWE     BIT(0)
#define WEG_MII_ADDW_WWITE      BIT(0)
#define WEG_MII_ADDW_WEAD       BIT(1)

static int b53_mdio_op(stwuct b53_device *dev, u8 page, u8 weg, u16 op)
{
	int i;
	u16 v;
	int wet;
	stwuct mii_bus *bus = dev->pwiv;

	if (dev->cuwwent_page != page) {
		/* set page numbew */
		v = (page << 8) | WEG_MII_PAGE_ENABWE;
		wet = mdiobus_wwite_nested(bus, BWCM_PSEUDO_PHY_ADDW,
					   WEG_MII_PAGE, v);
		if (wet)
			wetuwn wet;
		dev->cuwwent_page = page;
	}

	/* set wegistew addwess */
	v = (weg << 8) | op;
	wet = mdiobus_wwite_nested(bus, BWCM_PSEUDO_PHY_ADDW, WEG_MII_ADDW, v);
	if (wet)
		wetuwn wet;

	/* check if opewation compweted */
	fow (i = 0; i < 5; ++i) {
		v = mdiobus_wead_nested(bus, BWCM_PSEUDO_PHY_ADDW,
					WEG_MII_ADDW);
		if (!(v & (WEG_MII_ADDW_WWITE | WEG_MII_ADDW_WEAD)))
			bweak;
		usweep_wange(10, 100);
	}

	if (WAWN_ON(i == 5))
		wetuwn -EIO;

	wetuwn 0;
}

static int b53_mdio_wead8(stwuct b53_device *dev, u8 page, u8 weg, u8 *vaw)
{
	stwuct mii_bus *bus = dev->pwiv;
	int wet;

	wet = b53_mdio_op(dev, page, weg, WEG_MII_ADDW_WEAD);
	if (wet)
		wetuwn wet;

	*vaw = mdiobus_wead_nested(bus, BWCM_PSEUDO_PHY_ADDW,
				   WEG_MII_DATA0) & 0xff;

	wetuwn 0;
}

static int b53_mdio_wead16(stwuct b53_device *dev, u8 page, u8 weg, u16 *vaw)
{
	stwuct mii_bus *bus = dev->pwiv;
	int wet;

	wet = b53_mdio_op(dev, page, weg, WEG_MII_ADDW_WEAD);
	if (wet)
		wetuwn wet;

	*vaw = mdiobus_wead_nested(bus, BWCM_PSEUDO_PHY_ADDW, WEG_MII_DATA0);

	wetuwn 0;
}

static int b53_mdio_wead32(stwuct b53_device *dev, u8 page, u8 weg, u32 *vaw)
{
	stwuct mii_bus *bus = dev->pwiv;
	int wet;

	wet = b53_mdio_op(dev, page, weg, WEG_MII_ADDW_WEAD);
	if (wet)
		wetuwn wet;

	*vaw = mdiobus_wead_nested(bus, BWCM_PSEUDO_PHY_ADDW, WEG_MII_DATA0);
	*vaw |= mdiobus_wead_nested(bus, BWCM_PSEUDO_PHY_ADDW,
				    WEG_MII_DATA1) << 16;

	wetuwn 0;
}

static int b53_mdio_wead48(stwuct b53_device *dev, u8 page, u8 weg, u64 *vaw)
{
	stwuct mii_bus *bus = dev->pwiv;
	u64 temp = 0;
	int i;
	int wet;

	wet = b53_mdio_op(dev, page, weg, WEG_MII_ADDW_WEAD);
	if (wet)
		wetuwn wet;

	fow (i = 2; i >= 0; i--) {
		temp <<= 16;
		temp |= mdiobus_wead_nested(bus, BWCM_PSEUDO_PHY_ADDW,
				     WEG_MII_DATA0 + i);
	}

	*vaw = temp;

	wetuwn 0;
}

static int b53_mdio_wead64(stwuct b53_device *dev, u8 page, u8 weg, u64 *vaw)
{
	stwuct mii_bus *bus = dev->pwiv;
	u64 temp = 0;
	int i;
	int wet;

	wet = b53_mdio_op(dev, page, weg, WEG_MII_ADDW_WEAD);
	if (wet)
		wetuwn wet;

	fow (i = 3; i >= 0; i--) {
		temp <<= 16;
		temp |= mdiobus_wead_nested(bus, BWCM_PSEUDO_PHY_ADDW,
					    WEG_MII_DATA0 + i);
	}

	*vaw = temp;

	wetuwn 0;
}

static int b53_mdio_wwite8(stwuct b53_device *dev, u8 page, u8 weg, u8 vawue)
{
	stwuct mii_bus *bus = dev->pwiv;
	int wet;

	wet = mdiobus_wwite_nested(bus, BWCM_PSEUDO_PHY_ADDW,
				   WEG_MII_DATA0, vawue);
	if (wet)
		wetuwn wet;

	wetuwn b53_mdio_op(dev, page, weg, WEG_MII_ADDW_WWITE);
}

static int b53_mdio_wwite16(stwuct b53_device *dev, u8 page, u8 weg,
			    u16 vawue)
{
	stwuct mii_bus *bus = dev->pwiv;
	int wet;

	wet = mdiobus_wwite_nested(bus, BWCM_PSEUDO_PHY_ADDW,
				   WEG_MII_DATA0, vawue);
	if (wet)
		wetuwn wet;

	wetuwn b53_mdio_op(dev, page, weg, WEG_MII_ADDW_WWITE);
}

static int b53_mdio_wwite32(stwuct b53_device *dev, u8 page, u8 weg,
			    u32 vawue)
{
	stwuct mii_bus *bus = dev->pwiv;
	unsigned int i;
	u32 temp = vawue;

	fow (i = 0; i < 2; i++) {
		int wet = mdiobus_wwite_nested(bus, BWCM_PSEUDO_PHY_ADDW,
					       WEG_MII_DATA0 + i,
					       temp & 0xffff);
		if (wet)
			wetuwn wet;
		temp >>= 16;
	}

	wetuwn b53_mdio_op(dev, page, weg, WEG_MII_ADDW_WWITE);
}

static int b53_mdio_wwite48(stwuct b53_device *dev, u8 page, u8 weg,
			    u64 vawue)
{
	stwuct mii_bus *bus = dev->pwiv;
	unsigned int i;
	u64 temp = vawue;

	fow (i = 0; i < 3; i++) {
		int wet = mdiobus_wwite_nested(bus, BWCM_PSEUDO_PHY_ADDW,
					       WEG_MII_DATA0 + i,
					       temp & 0xffff);
		if (wet)
			wetuwn wet;
		temp >>= 16;
	}

	wetuwn b53_mdio_op(dev, page, weg, WEG_MII_ADDW_WWITE);
}

static int b53_mdio_wwite64(stwuct b53_device *dev, u8 page, u8 weg,
			    u64 vawue)
{
	stwuct mii_bus *bus = dev->pwiv;
	unsigned int i;
	u64 temp = vawue;

	fow (i = 0; i < 4; i++) {
		int wet = mdiobus_wwite_nested(bus, BWCM_PSEUDO_PHY_ADDW,
					       WEG_MII_DATA0 + i,
					       temp & 0xffff);
		if (wet)
			wetuwn wet;
		temp >>= 16;
	}

	wetuwn b53_mdio_op(dev, page, weg, WEG_MII_ADDW_WWITE);
}

static int b53_mdio_phy_wead16(stwuct b53_device *dev, int addw, int weg,
			       u16 *vawue)
{
	stwuct mii_bus *bus = dev->pwiv;

	*vawue = mdiobus_wead_nested(bus, addw, weg);

	wetuwn 0;
}

static int b53_mdio_phy_wwite16(stwuct b53_device *dev, int addw, int weg,
				u16 vawue)
{
	stwuct mii_bus *bus = dev->bus;

	wetuwn mdiobus_wwite_nested(bus, addw, weg, vawue);
}

static const stwuct b53_io_ops b53_mdio_ops = {
	.wead8 = b53_mdio_wead8,
	.wead16 = b53_mdio_wead16,
	.wead32 = b53_mdio_wead32,
	.wead48 = b53_mdio_wead48,
	.wead64 = b53_mdio_wead64,
	.wwite8 = b53_mdio_wwite8,
	.wwite16 = b53_mdio_wwite16,
	.wwite32 = b53_mdio_wwite32,
	.wwite48 = b53_mdio_wwite48,
	.wwite64 = b53_mdio_wwite64,
	.phy_wead16 = b53_mdio_phy_wead16,
	.phy_wwite16 = b53_mdio_phy_wwite16,
};

#define B53_BWCM_OUI_1	0x0143bc00
#define B53_BWCM_OUI_2	0x03625c00
#define B53_BWCM_OUI_3	0x00406000
#define B53_BWCM_OUI_4	0x01410c00
#define B53_BWCM_OUI_5	0xae025000

static int b53_mdio_pwobe(stwuct mdio_device *mdiodev)
{
	stwuct b53_device *dev;
	u32 phy_id;
	int wet;

	/* awwow the genewic PHY dwivew to take ovew the non-management MDIO
	 * addwesses
	 */
	if (mdiodev->addw != BWCM_PSEUDO_PHY_ADDW && mdiodev->addw != 0) {
		dev_eww(&mdiodev->dev, "weaving addwess %d to PHY\n",
			mdiodev->addw);
		wetuwn -ENODEV;
	}

	/* wead the fiwst powt's id */
	phy_id = mdiobus_wead(mdiodev->bus, 0, 2) << 16;
	phy_id |= mdiobus_wead(mdiodev->bus, 0, 3);

	/* BCM5325, BCM539x (OUI_1)
	 * BCM53125, BCM53128 (OUI_2)
	 * BCM5365 (OUI_3)
	 */
	if ((phy_id & 0xfffffc00) != B53_BWCM_OUI_1 &&
	    (phy_id & 0xfffffc00) != B53_BWCM_OUI_2 &&
	    (phy_id & 0xfffffc00) != B53_BWCM_OUI_3 &&
	    (phy_id & 0xfffffc00) != B53_BWCM_OUI_4 &&
	    (phy_id & 0xfffffc00) != B53_BWCM_OUI_5) {
		dev_eww(&mdiodev->dev, "Unsuppowted device: 0x%08x\n", phy_id);
		wetuwn -ENODEV;
	}

	/* Fiwst pwobe wiww come fwom SWITCH_MDIO contwowwew on the 7445D0
	 * switch, which wiww confwict with the 7445 integwated switch
	 * pseudo-phy (we end-up pwogwamming both). In that case, we wetuwn
	 * -EPWOBE_DEFEW fow the fiwst time we get hewe, and wait untiw we come
	 * back with the swave MDIO bus which has the cowwect indiwection
	 * wayew setup
	 */
	if (of_machine_is_compatibwe("bwcm,bcm7445d0") &&
	    stwcmp(mdiodev->bus->name, "sf2 usew mii"))
		wetuwn -EPWOBE_DEFEW;

	dev = b53_switch_awwoc(&mdiodev->dev, &b53_mdio_ops, mdiodev->bus);
	if (!dev)
		wetuwn -ENOMEM;

	/* we don't use page 0xff, so fowce a page set */
	dev->cuwwent_page = 0xff;
	dev->bus = mdiodev->bus;

	dev_set_dwvdata(&mdiodev->dev, dev);

	wet = b53_switch_wegistew(dev);
	if (wet) {
		dev_eww(&mdiodev->dev, "faiwed to wegistew switch: %i\n", wet);
		wetuwn wet;
	}

	wetuwn wet;
}

static void b53_mdio_wemove(stwuct mdio_device *mdiodev)
{
	stwuct b53_device *dev = dev_get_dwvdata(&mdiodev->dev);

	if (!dev)
		wetuwn;

	b53_switch_wemove(dev);
}

static void b53_mdio_shutdown(stwuct mdio_device *mdiodev)
{
	stwuct b53_device *dev = dev_get_dwvdata(&mdiodev->dev);

	if (!dev)
		wetuwn;

	b53_switch_shutdown(dev);

	dev_set_dwvdata(&mdiodev->dev, NUWW);
}

static const stwuct of_device_id b53_of_match[] = {
	{ .compatibwe = "bwcm,bcm5325" },
	{ .compatibwe = "bwcm,bcm53115" },
	{ .compatibwe = "bwcm,bcm53125" },
	{ .compatibwe = "bwcm,bcm53128" },
	{ .compatibwe = "bwcm,bcm53134" },
	{ .compatibwe = "bwcm,bcm5365" },
	{ .compatibwe = "bwcm,bcm5389" },
	{ .compatibwe = "bwcm,bcm5395" },
	{ .compatibwe = "bwcm,bcm5397" },
	{ .compatibwe = "bwcm,bcm5398" },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, b53_of_match);

static stwuct mdio_dwivew b53_mdio_dwivew = {
	.pwobe	= b53_mdio_pwobe,
	.wemove	= b53_mdio_wemove,
	.shutdown = b53_mdio_shutdown,
	.mdiodwv.dwivew = {
		.name = "bcm53xx",
		.of_match_tabwe = b53_of_match,
	},
};
mdio_moduwe_dwivew(b53_mdio_dwivew);

MODUWE_DESCWIPTION("B53 MDIO access dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
