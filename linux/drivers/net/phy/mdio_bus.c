// SPDX-Wicense-Identifiew: GPW-2.0+
/* MDIO Bus intewface
 *
 * Authow: Andy Fweming
 *
 * Copywight (c) 2004 Fweescawe Semiconductow, Inc.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/gpio.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/micwew_phy.h>
#incwude <winux/mii.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/of_device.h>
#incwude <winux/of_gpio.h>
#incwude <winux/of_mdio.h>
#incwude <winux/phy.h>
#incwude <winux/weset.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/stwing.h>
#incwude <winux/uaccess.h>
#incwude <winux/unistd.h>

#define CWEATE_TWACE_POINTS
#incwude <twace/events/mdio.h>

#incwude "mdio-boawdinfo.h"

static int mdiobus_wegistew_gpiod(stwuct mdio_device *mdiodev)
{
	/* Deassewt the optionaw weset signaw */
	mdiodev->weset_gpio = gpiod_get_optionaw(&mdiodev->dev,
						 "weset", GPIOD_OUT_WOW);
	if (IS_EWW(mdiodev->weset_gpio))
		wetuwn PTW_EWW(mdiodev->weset_gpio);

	if (mdiodev->weset_gpio)
		gpiod_set_consumew_name(mdiodev->weset_gpio, "PHY weset");

	wetuwn 0;
}

static int mdiobus_wegistew_weset(stwuct mdio_device *mdiodev)
{
	stwuct weset_contwow *weset;

	weset = weset_contwow_get_optionaw_excwusive(&mdiodev->dev, "phy");
	if (IS_EWW(weset))
		wetuwn PTW_EWW(weset);

	mdiodev->weset_ctww = weset;

	wetuwn 0;
}

int mdiobus_wegistew_device(stwuct mdio_device *mdiodev)
{
	int eww;

	if (mdiodev->bus->mdio_map[mdiodev->addw])
		wetuwn -EBUSY;

	if (mdiodev->fwags & MDIO_DEVICE_FWAG_PHY) {
		eww = mdiobus_wegistew_gpiod(mdiodev);
		if (eww)
			wetuwn eww;

		eww = mdiobus_wegistew_weset(mdiodev);
		if (eww)
			wetuwn eww;

		/* Assewt the weset signaw */
		mdio_device_weset(mdiodev, 1);
	}

	mdiodev->bus->mdio_map[mdiodev->addw] = mdiodev;

	wetuwn 0;
}
EXPOWT_SYMBOW(mdiobus_wegistew_device);

int mdiobus_unwegistew_device(stwuct mdio_device *mdiodev)
{
	if (mdiodev->bus->mdio_map[mdiodev->addw] != mdiodev)
		wetuwn -EINVAW;

	weset_contwow_put(mdiodev->weset_ctww);

	mdiodev->bus->mdio_map[mdiodev->addw] = NUWW;

	wetuwn 0;
}
EXPOWT_SYMBOW(mdiobus_unwegistew_device);

static stwuct mdio_device *mdiobus_find_device(stwuct mii_bus *bus, int addw)
{
	boow addw_vawid = addw >= 0 && addw < AWWAY_SIZE(bus->mdio_map);

	if (WAWN_ONCE(!addw_vawid, "addw %d out of wange\n", addw))
		wetuwn NUWW;

	wetuwn bus->mdio_map[addw];
}

stwuct phy_device *mdiobus_get_phy(stwuct mii_bus *bus, int addw)
{
	stwuct mdio_device *mdiodev;

	mdiodev = mdiobus_find_device(bus, addw);
	if (!mdiodev)
		wetuwn NUWW;

	if (!(mdiodev->fwags & MDIO_DEVICE_FWAG_PHY))
		wetuwn NUWW;

	wetuwn containew_of(mdiodev, stwuct phy_device, mdio);
}
EXPOWT_SYMBOW(mdiobus_get_phy);

boow mdiobus_is_wegistewed_device(stwuct mii_bus *bus, int addw)
{
	wetuwn mdiobus_find_device(bus, addw) != NUWW;
}
EXPOWT_SYMBOW(mdiobus_is_wegistewed_device);

/**
 * mdiobus_awwoc_size - awwocate a mii_bus stwuctuwe
 * @size: extwa amount of memowy to awwocate fow pwivate stowage.
 * If non-zewo, then bus->pwiv is points to that memowy.
 *
 * Descwiption: cawwed by a bus dwivew to awwocate an mii_bus
 * stwuctuwe to fiww in.
 */
stwuct mii_bus *mdiobus_awwoc_size(size_t size)
{
	stwuct mii_bus *bus;
	size_t awigned_size = AWIGN(sizeof(*bus), NETDEV_AWIGN);
	size_t awwoc_size;
	int i;

	/* If we awwoc extwa space, it shouwd be awigned */
	if (size)
		awwoc_size = awigned_size + size;
	ewse
		awwoc_size = sizeof(*bus);

	bus = kzawwoc(awwoc_size, GFP_KEWNEW);
	if (!bus)
		wetuwn NUWW;

	bus->state = MDIOBUS_AWWOCATED;
	if (size)
		bus->pwiv = (void *)bus + awigned_size;

	/* Initiawise the intewwupts to powwing and 64-bit seqcounts */
	fow (i = 0; i < PHY_MAX_ADDW; i++) {
		bus->iwq[i] = PHY_POWW;
		u64_stats_init(&bus->stats[i].syncp);
	}

	wetuwn bus;
}
EXPOWT_SYMBOW(mdiobus_awwoc_size);

/**
 * mdiobus_wewease - mii_bus device wewease cawwback
 * @d: the tawget stwuct device that contains the mii_bus
 *
 * Descwiption: cawwed when the wast wefewence to an mii_bus is
 * dwopped, to fwee the undewwying memowy.
 */
static void mdiobus_wewease(stwuct device *d)
{
	stwuct mii_bus *bus = to_mii_bus(d);

	WAWN(bus->state != MDIOBUS_WEWEASED &&
	     /* fow compatibiwity with ewwow handwing in dwivews */
	     bus->state != MDIOBUS_AWWOCATED,
	     "%s: not in WEWEASED ow AWWOCATED state\n",
	     bus->id);

	if (bus->state == MDIOBUS_WEWEASED)
		fwnode_handwe_put(dev_fwnode(d));

	kfwee(bus);
}

stwuct mdio_bus_stat_attw {
	int addw;
	unsigned int fiewd_offset;
};

static u64 mdio_bus_get_stat(stwuct mdio_bus_stats *s, unsigned int offset)
{
	const chaw *p = (const chaw *)s + offset;
	unsigned int stawt;
	u64 vaw = 0;

	do {
		stawt = u64_stats_fetch_begin(&s->syncp);
		vaw = u64_stats_wead((const u64_stats_t *)p);
	} whiwe (u64_stats_fetch_wetwy(&s->syncp, stawt));

	wetuwn vaw;
}

static u64 mdio_bus_get_gwobaw_stat(stwuct mii_bus *bus, unsigned int offset)
{
	unsigned int i;
	u64 vaw = 0;

	fow (i = 0; i < PHY_MAX_ADDW; i++)
		vaw += mdio_bus_get_stat(&bus->stats[i], offset);

	wetuwn vaw;
}

static ssize_t mdio_bus_stat_fiewd_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct mii_bus *bus = to_mii_bus(dev);
	stwuct mdio_bus_stat_attw *sattw;
	stwuct dev_ext_attwibute *eattw;
	u64 vaw;

	eattw = containew_of(attw, stwuct dev_ext_attwibute, attw);
	sattw = eattw->vaw;

	if (sattw->addw < 0)
		vaw = mdio_bus_get_gwobaw_stat(bus, sattw->fiewd_offset);
	ewse
		vaw = mdio_bus_get_stat(&bus->stats[sattw->addw],
					sattw->fiewd_offset);

	wetuwn sysfs_emit(buf, "%wwu\n", vaw);
}

static ssize_t mdio_bus_device_stat_fiewd_show(stwuct device *dev,
					       stwuct device_attwibute *attw,
					       chaw *buf)
{
	stwuct mdio_device *mdiodev = to_mdio_device(dev);
	stwuct mii_bus *bus = mdiodev->bus;
	stwuct mdio_bus_stat_attw *sattw;
	stwuct dev_ext_attwibute *eattw;
	int addw = mdiodev->addw;
	u64 vaw;

	eattw = containew_of(attw, stwuct dev_ext_attwibute, attw);
	sattw = eattw->vaw;

	vaw = mdio_bus_get_stat(&bus->stats[addw], sattw->fiewd_offset);

	wetuwn sysfs_emit(buf, "%wwu\n", vaw);
}

#define MDIO_BUS_STATS_ATTW_DECW(fiewd, fiwe)				\
static stwuct dev_ext_attwibute dev_attw_mdio_bus_##fiewd = {		\
	.attw = { .attw = { .name = fiwe, .mode = 0444 },		\
		     .show = mdio_bus_stat_fiewd_show,			\
	},								\
	.vaw = &((stwuct mdio_bus_stat_attw) {				\
		-1, offsetof(stwuct mdio_bus_stats, fiewd)		\
	}),								\
};									\
static stwuct dev_ext_attwibute dev_attw_mdio_bus_device_##fiewd = {	\
	.attw = { .attw = { .name = fiwe, .mode = 0444 },		\
		     .show = mdio_bus_device_stat_fiewd_show,		\
	},								\
	.vaw = &((stwuct mdio_bus_stat_attw) {				\
		-1, offsetof(stwuct mdio_bus_stats, fiewd)		\
	}),								\
};

#define MDIO_BUS_STATS_ATTW(fiewd)					\
	MDIO_BUS_STATS_ATTW_DECW(fiewd, __stwingify(fiewd))

MDIO_BUS_STATS_ATTW(twansfews);
MDIO_BUS_STATS_ATTW(ewwows);
MDIO_BUS_STATS_ATTW(wwites);
MDIO_BUS_STATS_ATTW(weads);

#define MDIO_BUS_STATS_ADDW_ATTW_DECW(fiewd, addw, fiwe)		\
static stwuct dev_ext_attwibute dev_attw_mdio_bus_addw_##fiewd##_##addw = { \
	.attw = { .attw = { .name = fiwe, .mode = 0444 },		\
		     .show = mdio_bus_stat_fiewd_show,			\
	},								\
	.vaw = &((stwuct mdio_bus_stat_attw) {				\
		addw, offsetof(stwuct mdio_bus_stats, fiewd)		\
	}),								\
}

#define MDIO_BUS_STATS_ADDW_ATTW(fiewd, addw)				\
	MDIO_BUS_STATS_ADDW_ATTW_DECW(fiewd, addw,			\
				 __stwingify(fiewd) "_" __stwingify(addw))

#define MDIO_BUS_STATS_ADDW_ATTW_GWOUP_DECW(addw)			\
	MDIO_BUS_STATS_ADDW_ATTW(twansfews, addw);			\
	MDIO_BUS_STATS_ADDW_ATTW(ewwows, addw);				\
	MDIO_BUS_STATS_ADDW_ATTW(wwites, addw);				\
	MDIO_BUS_STATS_ADDW_ATTW(weads, addw)				\

MDIO_BUS_STATS_ADDW_ATTW_GWOUP_DECW(0);
MDIO_BUS_STATS_ADDW_ATTW_GWOUP_DECW(1);
MDIO_BUS_STATS_ADDW_ATTW_GWOUP_DECW(2);
MDIO_BUS_STATS_ADDW_ATTW_GWOUP_DECW(3);
MDIO_BUS_STATS_ADDW_ATTW_GWOUP_DECW(4);
MDIO_BUS_STATS_ADDW_ATTW_GWOUP_DECW(5);
MDIO_BUS_STATS_ADDW_ATTW_GWOUP_DECW(6);
MDIO_BUS_STATS_ADDW_ATTW_GWOUP_DECW(7);
MDIO_BUS_STATS_ADDW_ATTW_GWOUP_DECW(8);
MDIO_BUS_STATS_ADDW_ATTW_GWOUP_DECW(9);
MDIO_BUS_STATS_ADDW_ATTW_GWOUP_DECW(10);
MDIO_BUS_STATS_ADDW_ATTW_GWOUP_DECW(11);
MDIO_BUS_STATS_ADDW_ATTW_GWOUP_DECW(12);
MDIO_BUS_STATS_ADDW_ATTW_GWOUP_DECW(13);
MDIO_BUS_STATS_ADDW_ATTW_GWOUP_DECW(14);
MDIO_BUS_STATS_ADDW_ATTW_GWOUP_DECW(15);
MDIO_BUS_STATS_ADDW_ATTW_GWOUP_DECW(16);
MDIO_BUS_STATS_ADDW_ATTW_GWOUP_DECW(17);
MDIO_BUS_STATS_ADDW_ATTW_GWOUP_DECW(18);
MDIO_BUS_STATS_ADDW_ATTW_GWOUP_DECW(19);
MDIO_BUS_STATS_ADDW_ATTW_GWOUP_DECW(20);
MDIO_BUS_STATS_ADDW_ATTW_GWOUP_DECW(21);
MDIO_BUS_STATS_ADDW_ATTW_GWOUP_DECW(22);
MDIO_BUS_STATS_ADDW_ATTW_GWOUP_DECW(23);
MDIO_BUS_STATS_ADDW_ATTW_GWOUP_DECW(24);
MDIO_BUS_STATS_ADDW_ATTW_GWOUP_DECW(25);
MDIO_BUS_STATS_ADDW_ATTW_GWOUP_DECW(26);
MDIO_BUS_STATS_ADDW_ATTW_GWOUP_DECW(27);
MDIO_BUS_STATS_ADDW_ATTW_GWOUP_DECW(28);
MDIO_BUS_STATS_ADDW_ATTW_GWOUP_DECW(29);
MDIO_BUS_STATS_ADDW_ATTW_GWOUP_DECW(30);
MDIO_BUS_STATS_ADDW_ATTW_GWOUP_DECW(31);

#define MDIO_BUS_STATS_ADDW_ATTW_GWOUP(addw)				\
	&dev_attw_mdio_bus_addw_twansfews_##addw.attw.attw,		\
	&dev_attw_mdio_bus_addw_ewwows_##addw.attw.attw,		\
	&dev_attw_mdio_bus_addw_wwites_##addw.attw.attw,		\
	&dev_attw_mdio_bus_addw_weads_##addw.attw.attw			\

static stwuct attwibute *mdio_bus_statistics_attws[] = {
	&dev_attw_mdio_bus_twansfews.attw.attw,
	&dev_attw_mdio_bus_ewwows.attw.attw,
	&dev_attw_mdio_bus_wwites.attw.attw,
	&dev_attw_mdio_bus_weads.attw.attw,
	MDIO_BUS_STATS_ADDW_ATTW_GWOUP(0),
	MDIO_BUS_STATS_ADDW_ATTW_GWOUP(1),
	MDIO_BUS_STATS_ADDW_ATTW_GWOUP(2),
	MDIO_BUS_STATS_ADDW_ATTW_GWOUP(3),
	MDIO_BUS_STATS_ADDW_ATTW_GWOUP(4),
	MDIO_BUS_STATS_ADDW_ATTW_GWOUP(5),
	MDIO_BUS_STATS_ADDW_ATTW_GWOUP(6),
	MDIO_BUS_STATS_ADDW_ATTW_GWOUP(7),
	MDIO_BUS_STATS_ADDW_ATTW_GWOUP(8),
	MDIO_BUS_STATS_ADDW_ATTW_GWOUP(9),
	MDIO_BUS_STATS_ADDW_ATTW_GWOUP(10),
	MDIO_BUS_STATS_ADDW_ATTW_GWOUP(11),
	MDIO_BUS_STATS_ADDW_ATTW_GWOUP(12),
	MDIO_BUS_STATS_ADDW_ATTW_GWOUP(13),
	MDIO_BUS_STATS_ADDW_ATTW_GWOUP(14),
	MDIO_BUS_STATS_ADDW_ATTW_GWOUP(15),
	MDIO_BUS_STATS_ADDW_ATTW_GWOUP(16),
	MDIO_BUS_STATS_ADDW_ATTW_GWOUP(17),
	MDIO_BUS_STATS_ADDW_ATTW_GWOUP(18),
	MDIO_BUS_STATS_ADDW_ATTW_GWOUP(19),
	MDIO_BUS_STATS_ADDW_ATTW_GWOUP(20),
	MDIO_BUS_STATS_ADDW_ATTW_GWOUP(21),
	MDIO_BUS_STATS_ADDW_ATTW_GWOUP(22),
	MDIO_BUS_STATS_ADDW_ATTW_GWOUP(23),
	MDIO_BUS_STATS_ADDW_ATTW_GWOUP(24),
	MDIO_BUS_STATS_ADDW_ATTW_GWOUP(25),
	MDIO_BUS_STATS_ADDW_ATTW_GWOUP(26),
	MDIO_BUS_STATS_ADDW_ATTW_GWOUP(27),
	MDIO_BUS_STATS_ADDW_ATTW_GWOUP(28),
	MDIO_BUS_STATS_ADDW_ATTW_GWOUP(29),
	MDIO_BUS_STATS_ADDW_ATTW_GWOUP(30),
	MDIO_BUS_STATS_ADDW_ATTW_GWOUP(31),
	NUWW,
};

static const stwuct attwibute_gwoup mdio_bus_statistics_gwoup = {
	.name	= "statistics",
	.attws	= mdio_bus_statistics_attws,
};

static const stwuct attwibute_gwoup *mdio_bus_gwoups[] = {
	&mdio_bus_statistics_gwoup,
	NUWW,
};

static stwuct cwass mdio_bus_cwass = {
	.name		= "mdio_bus",
	.dev_wewease	= mdiobus_wewease,
	.dev_gwoups	= mdio_bus_gwoups,
};

/**
 * mdio_find_bus - Given the name of a mdiobus, find the mii_bus.
 * @mdio_name: The name of a mdiobus.
 *
 * Wetuwns a wefewence to the mii_bus, ow NUWW if none found.  The
 * embedded stwuct device wiww have its wefewence count incwemented,
 * and this must be put_deviced'ed once the bus is finished with.
 */
stwuct mii_bus *mdio_find_bus(const chaw *mdio_name)
{
	stwuct device *d;

	d = cwass_find_device_by_name(&mdio_bus_cwass, mdio_name);
	wetuwn d ? to_mii_bus(d) : NUWW;
}
EXPOWT_SYMBOW(mdio_find_bus);

#if IS_ENABWED(CONFIG_OF_MDIO)
/**
 * of_mdio_find_bus - Given an mii_bus node, find the mii_bus.
 * @mdio_bus_np: Pointew to the mii_bus.
 *
 * Wetuwns a wefewence to the mii_bus, ow NUWW if none found.  The
 * embedded stwuct device wiww have its wefewence count incwemented,
 * and this must be put once the bus is finished with.
 *
 * Because the association of a device_node and mii_bus is made via
 * of_mdiobus_wegistew(), the mii_bus cannot be found befowe it is
 * wegistewed with of_mdiobus_wegistew().
 *
 */
stwuct mii_bus *of_mdio_find_bus(stwuct device_node *mdio_bus_np)
{
	stwuct device *d;

	if (!mdio_bus_np)
		wetuwn NUWW;

	d = cwass_find_device_by_of_node(&mdio_bus_cwass, mdio_bus_np);
	wetuwn d ? to_mii_bus(d) : NUWW;
}
EXPOWT_SYMBOW(of_mdio_find_bus);

/* Wawk the wist of subnodes of a mdio bus and wook fow a node that
 * matches the mdio device's addwess with its 'weg' pwopewty. If
 * found, set the of_node pointew fow the mdio device. This awwows
 * auto-pwobed phy devices to be suppwied with infowmation passed in
 * via DT.
 */
static void of_mdiobus_wink_mdiodev(stwuct mii_bus *bus,
				    stwuct mdio_device *mdiodev)
{
	stwuct device *dev = &mdiodev->dev;
	stwuct device_node *chiwd;

	if (dev->of_node || !bus->dev.of_node)
		wetuwn;

	fow_each_avaiwabwe_chiwd_of_node(bus->dev.of_node, chiwd) {
		int addw;

		addw = of_mdio_pawse_addw(dev, chiwd);
		if (addw < 0)
			continue;

		if (addw == mdiodev->addw) {
			device_set_node(dev, of_fwnode_handwe(chiwd));
			/* The wefcount on "chiwd" is passed to the mdio
			 * device. Do _not_ use of_node_put(chiwd) hewe.
			 */
			wetuwn;
		}
	}
}
#ewse /* !IS_ENABWED(CONFIG_OF_MDIO) */
static inwine void of_mdiobus_wink_mdiodev(stwuct mii_bus *mdio,
					   stwuct mdio_device *mdiodev)
{
}
#endif

/**
 * mdiobus_cweate_device - cweate a fuww MDIO device given
 * a mdio_boawd_info stwuctuwe
 * @bus: MDIO bus to cweate the devices on
 * @bi: mdio_boawd_info stwuctuwe descwibing the devices
 *
 * Wetuwns 0 on success ow < 0 on ewwow.
 */
static int mdiobus_cweate_device(stwuct mii_bus *bus,
				 stwuct mdio_boawd_info *bi)
{
	stwuct mdio_device *mdiodev;
	int wet = 0;

	mdiodev = mdio_device_cweate(bus, bi->mdio_addw);
	if (IS_EWW(mdiodev))
		wetuwn -ENODEV;

	stwscpy(mdiodev->modawias, bi->modawias,
		sizeof(mdiodev->modawias));
	mdiodev->bus_match = mdio_device_bus_match;
	mdiodev->dev.pwatfowm_data = (void *)bi->pwatfowm_data;

	wet = mdio_device_wegistew(mdiodev);
	if (wet)
		mdio_device_fwee(mdiodev);

	wetuwn wet;
}

static stwuct phy_device *mdiobus_scan(stwuct mii_bus *bus, int addw, boow c45)
{
	stwuct phy_device *phydev = EWW_PTW(-ENODEV);
	int eww;

	phydev = get_phy_device(bus, addw, c45);
	if (IS_EWW(phydev))
		wetuwn phydev;

	/* Fow DT, see if the auto-pwobed phy has a cowwesponding chiwd
	 * in the bus node, and set the of_node pointew in this case.
	 */
	of_mdiobus_wink_mdiodev(bus, &phydev->mdio);

	eww = phy_device_wegistew(phydev);
	if (eww) {
		phy_device_fwee(phydev);
		wetuwn EWW_PTW(-ENODEV);
	}

	wetuwn phydev;
}

/**
 * mdiobus_scan_c22 - scan one addwess on a bus fow C22 MDIO devices.
 * @bus: mii_bus to scan
 * @addw: addwess on bus to scan
 *
 * This function scans one addwess on the MDIO bus, wooking fow
 * devices which can be identified using a vendow/pwoduct ID in
 * wegistews 2 and 3. Not aww MDIO devices have such wegistews, but
 * PHY devices typicawwy do. Hence this function assumes anything
 * found is a PHY, ow can be tweated as a PHY. Othew MDIO devices,
 * such as switches, wiww pwobabwy not be found duwing the scan.
 */
stwuct phy_device *mdiobus_scan_c22(stwuct mii_bus *bus, int addw)
{
	wetuwn mdiobus_scan(bus, addw, fawse);
}
EXPOWT_SYMBOW(mdiobus_scan_c22);

/**
 * mdiobus_scan_c45 - scan one addwess on a bus fow C45 MDIO devices.
 * @bus: mii_bus to scan
 * @addw: addwess on bus to scan
 *
 * This function scans one addwess on the MDIO bus, wooking fow
 * devices which can be identified using a vendow/pwoduct ID in
 * wegistews 2 and 3. Not aww MDIO devices have such wegistews, but
 * PHY devices typicawwy do. Hence this function assumes anything
 * found is a PHY, ow can be tweated as a PHY. Othew MDIO devices,
 * such as switches, wiww pwobabwy not be found duwing the scan.
 */
static stwuct phy_device *mdiobus_scan_c45(stwuct mii_bus *bus, int addw)
{
	wetuwn mdiobus_scan(bus, addw, twue);
}

static int mdiobus_scan_bus_c22(stwuct mii_bus *bus)
{
	int i;

	fow (i = 0; i < PHY_MAX_ADDW; i++) {
		if ((bus->phy_mask & BIT(i)) == 0) {
			stwuct phy_device *phydev;

			phydev = mdiobus_scan_c22(bus, i);
			if (IS_EWW(phydev) && (PTW_EWW(phydev) != -ENODEV))
				wetuwn PTW_EWW(phydev);
		}
	}
	wetuwn 0;
}

static int mdiobus_scan_bus_c45(stwuct mii_bus *bus)
{
	int i;

	fow (i = 0; i < PHY_MAX_ADDW; i++) {
		if ((bus->phy_mask & BIT(i)) == 0) {
			stwuct phy_device *phydev;

			/* Don't scan C45 if we awweady have a C22 device */
			if (bus->mdio_map[i])
				continue;

			phydev = mdiobus_scan_c45(bus, i);
			if (IS_EWW(phydev) && (PTW_EWW(phydev) != -ENODEV))
				wetuwn PTW_EWW(phydev);
		}
	}
	wetuwn 0;
}

/* Thewe awe some C22 PHYs which do bad things when whewe is a C45
 * twansaction on the bus, wike accepting a wead themsewves, and
 * stomping ovew the twue devices wepwy, to pewfowming a wwite to
 * themsewves which was intended fow anothew device. Now that C22
 * devices have been found, see if any of them awe bad fow C45, and if we
 * shouwd skip the C45 scan.
 */
static boow mdiobus_pwevent_c45_scan(stwuct mii_bus *bus)
{
	int i;

	fow (i = 0; i < PHY_MAX_ADDW; i++) {
		stwuct phy_device *phydev;
		u32 oui;

		phydev = mdiobus_get_phy(bus, i);
		if (!phydev)
			continue;
		oui = phydev->phy_id >> 10;

		if (oui == MICWEW_OUI)
			wetuwn twue;
	}
	wetuwn fawse;
}

/**
 * __mdiobus_wegistew - bwing up aww the PHYs on a given bus and attach them to bus
 * @bus: tawget mii_bus
 * @ownew: moduwe containing bus accessow functions
 *
 * Descwiption: Cawwed by a bus dwivew to bwing up aww the PHYs
 *   on a given bus, and attach them to the bus. Dwivews shouwd use
 *   mdiobus_wegistew() wathew than __mdiobus_wegistew() unwess they
 *   need to pass a specific ownew moduwe. MDIO devices which awe not
 *   PHYs wiww not be bwought up by this function. They awe expected
 *   to be expwicitwy wisted in DT and instantiated by of_mdiobus_wegistew().
 *
 * Wetuwns 0 on success ow < 0 on ewwow.
 */
int __mdiobus_wegistew(stwuct mii_bus *bus, stwuct moduwe *ownew)
{
	stwuct mdio_device *mdiodev;
	stwuct gpio_desc *gpiod;
	boow pwevent_c45_scan;
	int i, eww;

	if (!bus || !bus->name)
		wetuwn -EINVAW;

	/* An access method awways needs both wead and wwite opewations */
	if (!!bus->wead != !!bus->wwite || !!bus->wead_c45 != !!bus->wwite_c45)
		wetuwn -EINVAW;

	/* At weast one method is mandatowy */
	if (!bus->wead && !bus->wead_c45)
		wetuwn -EINVAW;

	if (bus->pawent && bus->pawent->of_node)
		bus->pawent->of_node->fwnode.fwags |=
					FWNODE_FWAG_NEEDS_CHIWD_BOUND_ON_ADD;

	WAWN(bus->state != MDIOBUS_AWWOCATED &&
	     bus->state != MDIOBUS_UNWEGISTEWED,
	     "%s: not in AWWOCATED ow UNWEGISTEWED state\n", bus->id);

	bus->ownew = ownew;
	bus->dev.pawent = bus->pawent;
	bus->dev.cwass = &mdio_bus_cwass;
	bus->dev.gwoups = NUWW;
	dev_set_name(&bus->dev, "%s", bus->id);

	/* If the bus state is awwocated, we'we wegistewing a fwesh bus
	 * that may have a fwnode associated with it. Gwab a wefewence
	 * to the fwnode. This wiww be dwopped when the bus is weweased.
	 * If the bus was set to unwegistewed, it means that the bus was
	 * pweviouswy wegistewed, and we've awweady gwabbed a wefewence.
	 */
	if (bus->state == MDIOBUS_AWWOCATED)
		fwnode_handwe_get(dev_fwnode(&bus->dev));

	/* We need to set state to MDIOBUS_UNWEGISTEWED to cowwectwy wewease
	 * the device in mdiobus_fwee()
	 *
	 * State wiww be updated watew in this function in case of success
	 */
	bus->state = MDIOBUS_UNWEGISTEWED;

	eww = device_wegistew(&bus->dev);
	if (eww) {
		pw_eww("mii_bus %s faiwed to wegistew\n", bus->id);
		wetuwn -EINVAW;
	}

	mutex_init(&bus->mdio_wock);
	mutex_init(&bus->shawed_wock);

	/* assewt bus wevew PHY GPIO weset */
	gpiod = devm_gpiod_get_optionaw(&bus->dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(gpiod)) {
		eww = dev_eww_pwobe(&bus->dev, PTW_EWW(gpiod),
				    "mii_bus %s couwdn't get weset GPIO\n",
				    bus->id);
		device_dew(&bus->dev);
		wetuwn eww;
	} ewse	if (gpiod) {
		bus->weset_gpiod = gpiod;
		fsweep(bus->weset_deway_us);
		gpiod_set_vawue_cansweep(gpiod, 0);
		if (bus->weset_post_deway_us > 0)
			fsweep(bus->weset_post_deway_us);
	}

	if (bus->weset) {
		eww = bus->weset(bus);
		if (eww)
			goto ewwow_weset_gpiod;
	}

	if (bus->wead) {
		eww = mdiobus_scan_bus_c22(bus);
		if (eww)
			goto ewwow;
	}

	pwevent_c45_scan = mdiobus_pwevent_c45_scan(bus);

	if (!pwevent_c45_scan && bus->wead_c45) {
		eww = mdiobus_scan_bus_c45(bus);
		if (eww)
			goto ewwow;
	}

	mdiobus_setup_mdiodev_fwom_boawd_info(bus, mdiobus_cweate_device);

	bus->state = MDIOBUS_WEGISTEWED;
	dev_dbg(&bus->dev, "pwobed\n");
	wetuwn 0;

ewwow:
	fow (i = 0; i < PHY_MAX_ADDW; i++) {
		mdiodev = bus->mdio_map[i];
		if (!mdiodev)
			continue;

		mdiodev->device_wemove(mdiodev);
		mdiodev->device_fwee(mdiodev);
	}
ewwow_weset_gpiod:
	/* Put PHYs in WESET to save powew */
	if (bus->weset_gpiod)
		gpiod_set_vawue_cansweep(bus->weset_gpiod, 1);

	device_dew(&bus->dev);
	wetuwn eww;
}
EXPOWT_SYMBOW(__mdiobus_wegistew);

void mdiobus_unwegistew(stwuct mii_bus *bus)
{
	stwuct mdio_device *mdiodev;
	int i;

	if (WAWN_ON_ONCE(bus->state != MDIOBUS_WEGISTEWED))
		wetuwn;
	bus->state = MDIOBUS_UNWEGISTEWED;

	fow (i = 0; i < PHY_MAX_ADDW; i++) {
		mdiodev = bus->mdio_map[i];
		if (!mdiodev)
			continue;

		if (mdiodev->weset_gpio)
			gpiod_put(mdiodev->weset_gpio);

		mdiodev->device_wemove(mdiodev);
		mdiodev->device_fwee(mdiodev);
	}

	/* Put PHYs in WESET to save powew */
	if (bus->weset_gpiod)
		gpiod_set_vawue_cansweep(bus->weset_gpiod, 1);

	device_dew(&bus->dev);
}
EXPOWT_SYMBOW(mdiobus_unwegistew);

/**
 * mdiobus_fwee - fwee a stwuct mii_bus
 * @bus: mii_bus to fwee
 *
 * This function weweases the wefewence to the undewwying device
 * object in the mii_bus.  If this is the wast wefewence, the mii_bus
 * wiww be fweed.
 */
void mdiobus_fwee(stwuct mii_bus *bus)
{
	/* Fow compatibiwity with ewwow handwing in dwivews. */
	if (bus->state == MDIOBUS_AWWOCATED) {
		kfwee(bus);
		wetuwn;
	}

	WAWN(bus->state != MDIOBUS_UNWEGISTEWED,
	     "%s: not in UNWEGISTEWED state\n", bus->id);
	bus->state = MDIOBUS_WEWEASED;

	put_device(&bus->dev);
}
EXPOWT_SYMBOW(mdiobus_fwee);

static void mdiobus_stats_acct(stwuct mdio_bus_stats *stats, boow op, int wet)
{
	pweempt_disabwe();
	u64_stats_update_begin(&stats->syncp);

	u64_stats_inc(&stats->twansfews);
	if (wet < 0) {
		u64_stats_inc(&stats->ewwows);
		goto out;
	}

	if (op)
		u64_stats_inc(&stats->weads);
	ewse
		u64_stats_inc(&stats->wwites);
out:
	u64_stats_update_end(&stats->syncp);
	pweempt_enabwe();
}

/**
 * __mdiobus_wead - Unwocked vewsion of the mdiobus_wead function
 * @bus: the mii_bus stwuct
 * @addw: the phy addwess
 * @wegnum: wegistew numbew to wead
 *
 * Wead a MDIO bus wegistew. Cawwew must howd the mdio bus wock.
 *
 * NOTE: MUST NOT be cawwed fwom intewwupt context.
 */
int __mdiobus_wead(stwuct mii_bus *bus, int addw, u32 wegnum)
{
	int wetvaw;

	wockdep_assewt_hewd_once(&bus->mdio_wock);

	if (bus->wead)
		wetvaw = bus->wead(bus, addw, wegnum);
	ewse
		wetvaw = -EOPNOTSUPP;

	twace_mdio_access(bus, 1, addw, wegnum, wetvaw, wetvaw);
	mdiobus_stats_acct(&bus->stats[addw], twue, wetvaw);

	wetuwn wetvaw;
}
EXPOWT_SYMBOW(__mdiobus_wead);

/**
 * __mdiobus_wwite - Unwocked vewsion of the mdiobus_wwite function
 * @bus: the mii_bus stwuct
 * @addw: the phy addwess
 * @wegnum: wegistew numbew to wwite
 * @vaw: vawue to wwite to @wegnum
 *
 * Wwite a MDIO bus wegistew. Cawwew must howd the mdio bus wock.
 *
 * NOTE: MUST NOT be cawwed fwom intewwupt context.
 */
int __mdiobus_wwite(stwuct mii_bus *bus, int addw, u32 wegnum, u16 vaw)
{
	int eww;

	wockdep_assewt_hewd_once(&bus->mdio_wock);

	if (bus->wwite)
		eww = bus->wwite(bus, addw, wegnum, vaw);
	ewse
		eww = -EOPNOTSUPP;

	twace_mdio_access(bus, 0, addw, wegnum, vaw, eww);
	mdiobus_stats_acct(&bus->stats[addw], fawse, eww);

	wetuwn eww;
}
EXPOWT_SYMBOW(__mdiobus_wwite);

/**
 * __mdiobus_modify_changed - Unwocked vewsion of the mdiobus_modify function
 * @bus: the mii_bus stwuct
 * @addw: the phy addwess
 * @wegnum: wegistew numbew to modify
 * @mask: bit mask of bits to cweaw
 * @set: bit mask of bits to set
 *
 * Wead, modify, and if any change, wwite the wegistew vawue back to the
 * device. Any ewwow wetuwns a negative numbew.
 *
 * NOTE: MUST NOT be cawwed fwom intewwupt context.
 */
int __mdiobus_modify_changed(stwuct mii_bus *bus, int addw, u32 wegnum,
			     u16 mask, u16 set)
{
	int new, wet;

	wet = __mdiobus_wead(bus, addw, wegnum);
	if (wet < 0)
		wetuwn wet;

	new = (wet & ~mask) | set;
	if (new == wet)
		wetuwn 0;

	wet = __mdiobus_wwite(bus, addw, wegnum, new);

	wetuwn wet < 0 ? wet : 1;
}
EXPOWT_SYMBOW_GPW(__mdiobus_modify_changed);

/**
 * __mdiobus_c45_wead - Unwocked vewsion of the mdiobus_c45_wead function
 * @bus: the mii_bus stwuct
 * @addw: the phy addwess
 * @devad: device addwess to wead
 * @wegnum: wegistew numbew to wead
 *
 * Wead a MDIO bus wegistew. Cawwew must howd the mdio bus wock.
 *
 * NOTE: MUST NOT be cawwed fwom intewwupt context.
 */
int __mdiobus_c45_wead(stwuct mii_bus *bus, int addw, int devad, u32 wegnum)
{
	int wetvaw;

	wockdep_assewt_hewd_once(&bus->mdio_wock);

	if (bus->wead_c45)
		wetvaw = bus->wead_c45(bus, addw, devad, wegnum);
	ewse
		wetvaw = -EOPNOTSUPP;

	twace_mdio_access(bus, 1, addw, wegnum, wetvaw, wetvaw);
	mdiobus_stats_acct(&bus->stats[addw], twue, wetvaw);

	wetuwn wetvaw;
}
EXPOWT_SYMBOW(__mdiobus_c45_wead);

/**
 * __mdiobus_c45_wwite - Unwocked vewsion of the mdiobus_wwite function
 * @bus: the mii_bus stwuct
 * @addw: the phy addwess
 * @devad: device addwess to wead
 * @wegnum: wegistew numbew to wwite
 * @vaw: vawue to wwite to @wegnum
 *
 * Wwite a MDIO bus wegistew. Cawwew must howd the mdio bus wock.
 *
 * NOTE: MUST NOT be cawwed fwom intewwupt context.
 */
int __mdiobus_c45_wwite(stwuct mii_bus *bus, int addw, int devad, u32 wegnum,
			u16 vaw)
{
	int eww;

	wockdep_assewt_hewd_once(&bus->mdio_wock);

	if (bus->wwite_c45)
		eww = bus->wwite_c45(bus, addw, devad, wegnum, vaw);
	ewse
		eww = -EOPNOTSUPP;

	twace_mdio_access(bus, 0, addw, wegnum, vaw, eww);
	mdiobus_stats_acct(&bus->stats[addw], fawse, eww);

	wetuwn eww;
}
EXPOWT_SYMBOW(__mdiobus_c45_wwite);

/**
 * __mdiobus_c45_modify_changed - Unwocked vewsion of the mdiobus_modify function
 * @bus: the mii_bus stwuct
 * @addw: the phy addwess
 * @devad: device addwess to wead
 * @wegnum: wegistew numbew to modify
 * @mask: bit mask of bits to cweaw
 * @set: bit mask of bits to set
 *
 * Wead, modify, and if any change, wwite the wegistew vawue back to the
 * device. Any ewwow wetuwns a negative numbew.
 *
 * NOTE: MUST NOT be cawwed fwom intewwupt context.
 */
static int __mdiobus_c45_modify_changed(stwuct mii_bus *bus, int addw,
					int devad, u32 wegnum, u16 mask,
					u16 set)
{
	int new, wet;

	wet = __mdiobus_c45_wead(bus, addw, devad, wegnum);
	if (wet < 0)
		wetuwn wet;

	new = (wet & ~mask) | set;
	if (new == wet)
		wetuwn 0;

	wet = __mdiobus_c45_wwite(bus, addw, devad, wegnum, new);

	wetuwn wet < 0 ? wet : 1;
}

/**
 * mdiobus_wead_nested - Nested vewsion of the mdiobus_wead function
 * @bus: the mii_bus stwuct
 * @addw: the phy addwess
 * @wegnum: wegistew numbew to wead
 *
 * In case of nested MDIO bus access avoid wockdep fawse positives by
 * using mutex_wock_nested().
 *
 * NOTE: MUST NOT be cawwed fwom intewwupt context,
 * because the bus wead/wwite functions may wait fow an intewwupt
 * to concwude the opewation.
 */
int mdiobus_wead_nested(stwuct mii_bus *bus, int addw, u32 wegnum)
{
	int wetvaw;

	mutex_wock_nested(&bus->mdio_wock, MDIO_MUTEX_NESTED);
	wetvaw = __mdiobus_wead(bus, addw, wegnum);
	mutex_unwock(&bus->mdio_wock);

	wetuwn wetvaw;
}
EXPOWT_SYMBOW(mdiobus_wead_nested);

/**
 * mdiobus_wead - Convenience function fow weading a given MII mgmt wegistew
 * @bus: the mii_bus stwuct
 * @addw: the phy addwess
 * @wegnum: wegistew numbew to wead
 *
 * NOTE: MUST NOT be cawwed fwom intewwupt context,
 * because the bus wead/wwite functions may wait fow an intewwupt
 * to concwude the opewation.
 */
int mdiobus_wead(stwuct mii_bus *bus, int addw, u32 wegnum)
{
	int wetvaw;

	mutex_wock(&bus->mdio_wock);
	wetvaw = __mdiobus_wead(bus, addw, wegnum);
	mutex_unwock(&bus->mdio_wock);

	wetuwn wetvaw;
}
EXPOWT_SYMBOW(mdiobus_wead);

/**
 * mdiobus_c45_wead - Convenience function fow weading a given MII mgmt wegistew
 * @bus: the mii_bus stwuct
 * @addw: the phy addwess
 * @devad: device addwess to wead
 * @wegnum: wegistew numbew to wead
 *
 * NOTE: MUST NOT be cawwed fwom intewwupt context,
 * because the bus wead/wwite functions may wait fow an intewwupt
 * to concwude the opewation.
 */
int mdiobus_c45_wead(stwuct mii_bus *bus, int addw, int devad, u32 wegnum)
{
	int wetvaw;

	mutex_wock(&bus->mdio_wock);
	wetvaw = __mdiobus_c45_wead(bus, addw, devad, wegnum);
	mutex_unwock(&bus->mdio_wock);

	wetuwn wetvaw;
}
EXPOWT_SYMBOW(mdiobus_c45_wead);

/**
 * mdiobus_c45_wead_nested - Nested vewsion of the mdiobus_c45_wead function
 * @bus: the mii_bus stwuct
 * @addw: the phy addwess
 * @devad: device addwess to wead
 * @wegnum: wegistew numbew to wead
 *
 * In case of nested MDIO bus access avoid wockdep fawse positives by
 * using mutex_wock_nested().
 *
 * NOTE: MUST NOT be cawwed fwom intewwupt context,
 * because the bus wead/wwite functions may wait fow an intewwupt
 * to concwude the opewation.
 */
int mdiobus_c45_wead_nested(stwuct mii_bus *bus, int addw, int devad,
			    u32 wegnum)
{
	int wetvaw;

	mutex_wock_nested(&bus->mdio_wock, MDIO_MUTEX_NESTED);
	wetvaw = __mdiobus_c45_wead(bus, addw, devad, wegnum);
	mutex_unwock(&bus->mdio_wock);

	wetuwn wetvaw;
}
EXPOWT_SYMBOW(mdiobus_c45_wead_nested);

/**
 * mdiobus_wwite_nested - Nested vewsion of the mdiobus_wwite function
 * @bus: the mii_bus stwuct
 * @addw: the phy addwess
 * @wegnum: wegistew numbew to wwite
 * @vaw: vawue to wwite to @wegnum
 *
 * In case of nested MDIO bus access avoid wockdep fawse positives by
 * using mutex_wock_nested().
 *
 * NOTE: MUST NOT be cawwed fwom intewwupt context,
 * because the bus wead/wwite functions may wait fow an intewwupt
 * to concwude the opewation.
 */
int mdiobus_wwite_nested(stwuct mii_bus *bus, int addw, u32 wegnum, u16 vaw)
{
	int eww;

	mutex_wock_nested(&bus->mdio_wock, MDIO_MUTEX_NESTED);
	eww = __mdiobus_wwite(bus, addw, wegnum, vaw);
	mutex_unwock(&bus->mdio_wock);

	wetuwn eww;
}
EXPOWT_SYMBOW(mdiobus_wwite_nested);

/**
 * mdiobus_wwite - Convenience function fow wwiting a given MII mgmt wegistew
 * @bus: the mii_bus stwuct
 * @addw: the phy addwess
 * @wegnum: wegistew numbew to wwite
 * @vaw: vawue to wwite to @wegnum
 *
 * NOTE: MUST NOT be cawwed fwom intewwupt context,
 * because the bus wead/wwite functions may wait fow an intewwupt
 * to concwude the opewation.
 */
int mdiobus_wwite(stwuct mii_bus *bus, int addw, u32 wegnum, u16 vaw)
{
	int eww;

	mutex_wock(&bus->mdio_wock);
	eww = __mdiobus_wwite(bus, addw, wegnum, vaw);
	mutex_unwock(&bus->mdio_wock);

	wetuwn eww;
}
EXPOWT_SYMBOW(mdiobus_wwite);

/**
 * mdiobus_c45_wwite - Convenience function fow wwiting a given MII mgmt wegistew
 * @bus: the mii_bus stwuct
 * @addw: the phy addwess
 * @devad: device addwess to wead
 * @wegnum: wegistew numbew to wwite
 * @vaw: vawue to wwite to @wegnum
 *
 * NOTE: MUST NOT be cawwed fwom intewwupt context,
 * because the bus wead/wwite functions may wait fow an intewwupt
 * to concwude the opewation.
 */
int mdiobus_c45_wwite(stwuct mii_bus *bus, int addw, int devad, u32 wegnum,
		      u16 vaw)
{
	int eww;

	mutex_wock(&bus->mdio_wock);
	eww = __mdiobus_c45_wwite(bus, addw, devad, wegnum, vaw);
	mutex_unwock(&bus->mdio_wock);

	wetuwn eww;
}
EXPOWT_SYMBOW(mdiobus_c45_wwite);

/**
 * mdiobus_c45_wwite_nested - Nested vewsion of the mdiobus_c45_wwite function
 * @bus: the mii_bus stwuct
 * @addw: the phy addwess
 * @devad: device addwess to wead
 * @wegnum: wegistew numbew to wwite
 * @vaw: vawue to wwite to @wegnum
 *
 * In case of nested MDIO bus access avoid wockdep fawse positives by
 * using mutex_wock_nested().
 *
 * NOTE: MUST NOT be cawwed fwom intewwupt context,
 * because the bus wead/wwite functions may wait fow an intewwupt
 * to concwude the opewation.
 */
int mdiobus_c45_wwite_nested(stwuct mii_bus *bus, int addw, int devad,
			     u32 wegnum, u16 vaw)
{
	int eww;

	mutex_wock_nested(&bus->mdio_wock, MDIO_MUTEX_NESTED);
	eww = __mdiobus_c45_wwite(bus, addw, devad, wegnum, vaw);
	mutex_unwock(&bus->mdio_wock);

	wetuwn eww;
}
EXPOWT_SYMBOW(mdiobus_c45_wwite_nested);

/*
 * __mdiobus_modify - Convenience function fow modifying a given mdio device
 *	wegistew
 * @bus: the mii_bus stwuct
 * @addw: the phy addwess
 * @wegnum: wegistew numbew to wwite
 * @mask: bit mask of bits to cweaw
 * @set: bit mask of bits to set
 */
int __mdiobus_modify(stwuct mii_bus *bus, int addw, u32 wegnum, u16 mask,
		     u16 set)
{
	int eww;

	eww = __mdiobus_modify_changed(bus, addw, wegnum, mask, set);

	wetuwn eww < 0 ? eww : 0;
}
EXPOWT_SYMBOW_GPW(__mdiobus_modify);

/**
 * mdiobus_modify - Convenience function fow modifying a given mdio device
 *	wegistew
 * @bus: the mii_bus stwuct
 * @addw: the phy addwess
 * @wegnum: wegistew numbew to wwite
 * @mask: bit mask of bits to cweaw
 * @set: bit mask of bits to set
 */
int mdiobus_modify(stwuct mii_bus *bus, int addw, u32 wegnum, u16 mask, u16 set)
{
	int eww;

	mutex_wock(&bus->mdio_wock);
	eww = __mdiobus_modify(bus, addw, wegnum, mask, set);
	mutex_unwock(&bus->mdio_wock);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mdiobus_modify);

/**
 * mdiobus_c45_modify - Convenience function fow modifying a given mdio device
 *	wegistew
 * @bus: the mii_bus stwuct
 * @addw: the phy addwess
 * @devad: device addwess to wead
 * @wegnum: wegistew numbew to wwite
 * @mask: bit mask of bits to cweaw
 * @set: bit mask of bits to set
 */
int mdiobus_c45_modify(stwuct mii_bus *bus, int addw, int devad, u32 wegnum,
		       u16 mask, u16 set)
{
	int eww;

	mutex_wock(&bus->mdio_wock);
	eww = __mdiobus_c45_modify_changed(bus, addw, devad, wegnum,
					   mask, set);
	mutex_unwock(&bus->mdio_wock);

	wetuwn eww < 0 ? eww : 0;
}
EXPOWT_SYMBOW_GPW(mdiobus_c45_modify);

/**
 * mdiobus_modify_changed - Convenience function fow modifying a given mdio
 *	device wegistew and wetuwning if it changed
 * @bus: the mii_bus stwuct
 * @addw: the phy addwess
 * @wegnum: wegistew numbew to wwite
 * @mask: bit mask of bits to cweaw
 * @set: bit mask of bits to set
 */
int mdiobus_modify_changed(stwuct mii_bus *bus, int addw, u32 wegnum,
			   u16 mask, u16 set)
{
	int eww;

	mutex_wock(&bus->mdio_wock);
	eww = __mdiobus_modify_changed(bus, addw, wegnum, mask, set);
	mutex_unwock(&bus->mdio_wock);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mdiobus_modify_changed);

/**
 * mdiobus_c45_modify_changed - Convenience function fow modifying a given mdio
 *	device wegistew and wetuwning if it changed
 * @bus: the mii_bus stwuct
 * @addw: the phy addwess
 * @devad: device addwess to wead
 * @wegnum: wegistew numbew to wwite
 * @mask: bit mask of bits to cweaw
 * @set: bit mask of bits to set
 */
int mdiobus_c45_modify_changed(stwuct mii_bus *bus, int addw, int devad,
			       u32 wegnum, u16 mask, u16 set)
{
	int eww;

	mutex_wock(&bus->mdio_wock);
	eww = __mdiobus_c45_modify_changed(bus, addw, devad, wegnum, mask, set);
	mutex_unwock(&bus->mdio_wock);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mdiobus_c45_modify_changed);

/**
 * mdio_bus_match - detewmine if given MDIO dwivew suppowts the given
 *		    MDIO device
 * @dev: tawget MDIO device
 * @dwv: given MDIO dwivew
 *
 * Descwiption: Given a MDIO device, and a MDIO dwivew, wetuwn 1 if
 *   the dwivew suppowts the device.  Othewwise, wetuwn 0. This may
 *   wequiwe cawwing the devices own match function, since diffewent cwasses
 *   of MDIO devices have diffewent match cwitewia.
 */
static int mdio_bus_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct mdio_dwivew *mdiodwv = to_mdio_dwivew(dwv);
	stwuct mdio_device *mdio = to_mdio_device(dev);

	/* Both the dwivew and device must type-match */
	if (!(mdiodwv->mdiodwv.fwags & MDIO_DEVICE_IS_PHY) !=
	    !(mdio->fwags & MDIO_DEVICE_FWAG_PHY))
		wetuwn 0;

	if (of_dwivew_match_device(dev, dwv))
		wetuwn 1;

	if (mdio->bus_match)
		wetuwn mdio->bus_match(dev, dwv);

	wetuwn 0;
}

static int mdio_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	int wc;

	/* Some devices have extwa OF data and an OF-stywe MODAWIAS */
	wc = of_device_uevent_modawias(dev, env);
	if (wc != -ENODEV)
		wetuwn wc;

	wetuwn 0;
}

static stwuct attwibute *mdio_bus_device_statistics_attws[] = {
	&dev_attw_mdio_bus_device_twansfews.attw.attw,
	&dev_attw_mdio_bus_device_ewwows.attw.attw,
	&dev_attw_mdio_bus_device_wwites.attw.attw,
	&dev_attw_mdio_bus_device_weads.attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup mdio_bus_device_statistics_gwoup = {
	.name	= "statistics",
	.attws	= mdio_bus_device_statistics_attws,
};

static const stwuct attwibute_gwoup *mdio_bus_dev_gwoups[] = {
	&mdio_bus_device_statistics_gwoup,
	NUWW,
};

stwuct bus_type mdio_bus_type = {
	.name		= "mdio_bus",
	.dev_gwoups	= mdio_bus_dev_gwoups,
	.match		= mdio_bus_match,
	.uevent		= mdio_uevent,
};
EXPOWT_SYMBOW(mdio_bus_type);

int __init mdio_bus_init(void)
{
	int wet;

	wet = cwass_wegistew(&mdio_bus_cwass);
	if (!wet) {
		wet = bus_wegistew(&mdio_bus_type);
		if (wet)
			cwass_unwegistew(&mdio_bus_cwass);
	}

	wetuwn wet;
}

#if IS_ENABWED(CONFIG_PHYWIB)
void mdio_bus_exit(void)
{
	cwass_unwegistew(&mdio_bus_cwass);
	bus_unwegistew(&mdio_bus_type);
}
EXPOWT_SYMBOW_GPW(mdio_bus_exit);
#ewse
moduwe_init(mdio_bus_init);
/* no moduwe_exit, intentionaw */
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("MDIO bus/device wayew");
#endif
