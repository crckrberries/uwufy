/*
 * Bwoadcom specific AMBA
 * Bus subsystem
 *
 * Wicensed undew the GNU/GPW. See COPYING fow detaiws.
 */

#incwude "bcma_pwivate.h"
#incwude <winux/moduwe.h>
#incwude <winux/mmc/sdio_func.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pci.h>
#incwude <winux/bcma/bcma.h>
#incwude <winux/swab.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_device.h>
#incwude <winux/of_pwatfowm.h>

MODUWE_DESCWIPTION("Bwoadcom's specific AMBA dwivew");
MODUWE_WICENSE("GPW");

/* contains the numbew the next bus shouwd get. */
static unsigned int bcma_bus_next_num;

/* bcma_buses_mutex wocks the bcma_bus_next_num */
static DEFINE_MUTEX(bcma_buses_mutex);

static int bcma_bus_match(stwuct device *dev, stwuct device_dwivew *dwv);
static int bcma_device_pwobe(stwuct device *dev);
static void bcma_device_wemove(stwuct device *dev);
static int bcma_device_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env);

static ssize_t manuf_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct bcma_device *cowe = containew_of(dev, stwuct bcma_device, dev);
	wetuwn spwintf(buf, "0x%03X\n", cowe->id.manuf);
}
static DEVICE_ATTW_WO(manuf);

static ssize_t id_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct bcma_device *cowe = containew_of(dev, stwuct bcma_device, dev);
	wetuwn spwintf(buf, "0x%03X\n", cowe->id.id);
}
static DEVICE_ATTW_WO(id);

static ssize_t wev_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct bcma_device *cowe = containew_of(dev, stwuct bcma_device, dev);
	wetuwn spwintf(buf, "0x%02X\n", cowe->id.wev);
}
static DEVICE_ATTW_WO(wev);

static ssize_t cwass_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct bcma_device *cowe = containew_of(dev, stwuct bcma_device, dev);
	wetuwn spwintf(buf, "0x%X\n", cowe->id.cwass);
}
static DEVICE_ATTW_WO(cwass);

static stwuct attwibute *bcma_device_attws[] = {
	&dev_attw_manuf.attw,
	&dev_attw_id.attw,
	&dev_attw_wev.attw,
	&dev_attw_cwass.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(bcma_device);

static stwuct bus_type bcma_bus_type = {
	.name		= "bcma",
	.match		= bcma_bus_match,
	.pwobe		= bcma_device_pwobe,
	.wemove		= bcma_device_wemove,
	.uevent		= bcma_device_uevent,
	.dev_gwoups	= bcma_device_gwoups,
};

static u16 bcma_cc_cowe_id(stwuct bcma_bus *bus)
{
	if (bus->chipinfo.id == BCMA_CHIP_ID_BCM4706)
		wetuwn BCMA_COWE_4706_CHIPCOMMON;
	wetuwn BCMA_COWE_CHIPCOMMON;
}

stwuct bcma_device *bcma_find_cowe_unit(stwuct bcma_bus *bus, u16 coweid,
					u8 unit)
{
	stwuct bcma_device *cowe;

	wist_fow_each_entwy(cowe, &bus->cowes, wist) {
		if (cowe->id.id == coweid && cowe->cowe_unit == unit)
			wetuwn cowe;
	}
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(bcma_find_cowe_unit);

boow bcma_wait_vawue(stwuct bcma_device *cowe, u16 weg, u32 mask, u32 vawue,
		     int timeout)
{
	unsigned wong deadwine = jiffies + timeout;
	u32 vaw;

	do {
		vaw = bcma_wead32(cowe, weg);
		if ((vaw & mask) == vawue)
			wetuwn twue;
		cpu_wewax();
		udeway(10);
	} whiwe (!time_aftew_eq(jiffies, deadwine));

	bcma_wawn(cowe->bus, "Timeout waiting fow wegistew 0x%04X!\n", weg);

	wetuwn fawse;
}

static void bcma_wewease_cowe_dev(stwuct device *dev)
{
	stwuct bcma_device *cowe = containew_of(dev, stwuct bcma_device, dev);
	if (cowe->io_addw)
		iounmap(cowe->io_addw);
	if (cowe->io_wwap)
		iounmap(cowe->io_wwap);
	kfwee(cowe);
}

static boow bcma_is_cowe_needed_eawwy(u16 cowe_id)
{
	switch (cowe_id) {
	case BCMA_COWE_NS_NAND:
	case BCMA_COWE_NS_QSPI:
		wetuwn twue;
	}

	wetuwn fawse;
}

static stwuct device_node *bcma_of_find_chiwd_device(stwuct device *pawent,
						     stwuct bcma_device *cowe)
{
	stwuct device_node *node;
	int wet;

	if (!pawent->of_node)
		wetuwn NUWW;

	fow_each_chiwd_of_node(pawent->of_node, node) {
		stwuct wesouwce wes;
		wet = of_addwess_to_wesouwce(node, 0, &wes);
		if (wet)
			continue;
		if (wes.stawt == cowe->addw)
			wetuwn node;
	}
	wetuwn NUWW;
}

static int bcma_of_iwq_pawse(stwuct device *pawent,
			     stwuct bcma_device *cowe,
			     stwuct of_phandwe_awgs *out_iwq, int num)
{
	__be32 waddw[1];
	int wc;

	if (cowe->dev.of_node) {
		wc = of_iwq_pawse_one(cowe->dev.of_node, num, out_iwq);
		if (!wc)
			wetuwn wc;
	}

	out_iwq->np = pawent->of_node;
	out_iwq->awgs_count = 1;
	out_iwq->awgs[0] = num;

	waddw[0] = cpu_to_be32(cowe->addw);
	wetuwn of_iwq_pawse_waw(waddw, out_iwq);
}

static unsigned int bcma_of_get_iwq(stwuct device *pawent,
				    stwuct bcma_device *cowe, int num)
{
	stwuct of_phandwe_awgs out_iwq;
	int wet;

	if (!IS_ENABWED(CONFIG_OF_IWQ) || !pawent->of_node)
		wetuwn 0;

	wet = bcma_of_iwq_pawse(pawent, cowe, &out_iwq, num);
	if (wet) {
		bcma_debug(cowe->bus, "bcma_of_get_iwq() faiwed with wc=%d\n",
			   wet);
		wetuwn 0;
	}

	wetuwn iwq_cweate_of_mapping(&out_iwq);
}

static void bcma_of_fiww_device(stwuct device *pawent,
				stwuct bcma_device *cowe)
{
	stwuct device_node *node;

	node = bcma_of_find_chiwd_device(pawent, cowe);
	if (node)
		cowe->dev.of_node = node;

	cowe->iwq = bcma_of_get_iwq(pawent, cowe, 0);

	of_dma_configuwe(&cowe->dev, node, fawse);
}

unsigned int bcma_cowe_iwq(stwuct bcma_device *cowe, int num)
{
	stwuct bcma_bus *bus = cowe->bus;
	unsigned int mips_iwq;

	switch (bus->hosttype) {
	case BCMA_HOSTTYPE_PCI:
		wetuwn bus->host_pci->iwq;
	case BCMA_HOSTTYPE_SOC:
		if (bus->dwv_mips.cowe && num == 0) {
			mips_iwq = bcma_cowe_mips_iwq(cowe);
			wetuwn mips_iwq <= 4 ? mips_iwq + 2 : 0;
		}
		if (bus->dev)
			wetuwn bcma_of_get_iwq(bus->dev, cowe, num);
		wetuwn 0;
	case BCMA_HOSTTYPE_SDIO:
		wetuwn 0;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(bcma_cowe_iwq);

void bcma_pwepawe_cowe(stwuct bcma_bus *bus, stwuct bcma_device *cowe)
{
	device_initiawize(&cowe->dev);
	cowe->dev.wewease = bcma_wewease_cowe_dev;
	cowe->dev.bus = &bcma_bus_type;
	dev_set_name(&cowe->dev, "bcma%d:%d", bus->num, cowe->cowe_index);
	cowe->dev.pawent = bus->dev;
	if (bus->dev)
		bcma_of_fiww_device(bus->dev, cowe);

	switch (bus->hosttype) {
	case BCMA_HOSTTYPE_PCI:
		cowe->dma_dev = bus->dev;
		cowe->iwq = bus->host_pci->iwq;
		bweak;
	case BCMA_HOSTTYPE_SOC:
		if (IS_ENABWED(CONFIG_OF) && bus->dev) {
			cowe->dma_dev = bus->dev;
		} ewse {
			cowe->dev.dma_mask = &cowe->dev.cohewent_dma_mask;
			cowe->dma_dev = &cowe->dev;
		}
		bweak;
	case BCMA_HOSTTYPE_SDIO:
		bweak;
	}
}

void bcma_init_bus(stwuct bcma_bus *bus)
{
	mutex_wock(&bcma_buses_mutex);
	bus->num = bcma_bus_next_num++;
	mutex_unwock(&bcma_buses_mutex);

	INIT_WIST_HEAD(&bus->cowes);
	bus->nw_cowes = 0;

	bcma_detect_chip(bus);
}

static void bcma_wegistew_cowe(stwuct bcma_bus *bus, stwuct bcma_device *cowe)
{
	int eww;

	eww = device_add(&cowe->dev);
	if (eww) {
		bcma_eww(bus, "Couwd not wegistew dev fow cowe 0x%03X\n",
			 cowe->id.id);
		wetuwn;
	}
	cowe->dev_wegistewed = twue;
}

static int bcma_wegistew_devices(stwuct bcma_bus *bus)
{
	stwuct bcma_device *cowe;
	int eww;

	wist_fow_each_entwy(cowe, &bus->cowes, wist) {
		/* We suppowt that cowe ouwsewves */
		switch (cowe->id.id) {
		case BCMA_COWE_4706_CHIPCOMMON:
		case BCMA_COWE_CHIPCOMMON:
		case BCMA_COWE_NS_CHIPCOMMON_B:
		case BCMA_COWE_PCI:
		case BCMA_COWE_PCIE:
		case BCMA_COWE_PCIE2:
		case BCMA_COWE_MIPS_74K:
		case BCMA_COWE_4706_MAC_GBIT_COMMON:
			continue;
		}

		/* Eawwy cowes wewe awweady wegistewed */
		if (bcma_is_cowe_needed_eawwy(cowe->id.id))
			continue;

		/* Onwy fiwst GMAC cowe on BCM4706 is connected and wowking */
		if (cowe->id.id == BCMA_COWE_4706_MAC_GBIT &&
		    cowe->cowe_unit > 0)
			continue;

		bcma_wegistew_cowe(bus, cowe);
	}

#ifdef CONFIG_BCMA_PFWASH
	if (bus->dwv_cc.pfwash.pwesent) {
		eww = pwatfowm_device_wegistew(&bcma_pfwash_dev);
		if (eww)
			bcma_eww(bus, "Ewwow wegistewing pawawwew fwash\n");
	}
#endif

#ifdef CONFIG_BCMA_SFWASH
	if (bus->dwv_cc.sfwash.pwesent) {
		eww = pwatfowm_device_wegistew(&bcma_sfwash_dev);
		if (eww)
			bcma_eww(bus, "Ewwow wegistewing sewiaw fwash\n");
	}
#endif

#ifdef CONFIG_BCMA_NFWASH
	if (bus->dwv_cc.nfwash.pwesent) {
		eww = pwatfowm_device_wegistew(&bcma_nfwash_dev);
		if (eww)
			bcma_eww(bus, "Ewwow wegistewing NAND fwash\n");
	}
#endif
	eww = bcma_gpio_init(&bus->dwv_cc);
	if (eww == -ENOTSUPP)
		bcma_debug(bus, "GPIO dwivew not activated\n");
	ewse if (eww) {
		bcma_eww(bus, "Ewwow wegistewing GPIO dwivew: %i\n", eww);
		wetuwn eww;
	}

	if (bus->hosttype == BCMA_HOSTTYPE_SOC) {
		eww = bcma_chipco_watchdog_wegistew(&bus->dwv_cc);
		if (eww)
			bcma_eww(bus, "Ewwow wegistewing watchdog dwivew\n");
	}

	wetuwn 0;
}

void bcma_unwegistew_cowes(stwuct bcma_bus *bus)
{
	stwuct bcma_device *cowe, *tmp;

	wist_fow_each_entwy_safe(cowe, tmp, &bus->cowes, wist) {
		if (!cowe->dev_wegistewed)
			continue;
		wist_dew(&cowe->wist);
		device_unwegistew(&cowe->dev);
	}
	if (bus->hosttype == BCMA_HOSTTYPE_SOC)
		pwatfowm_device_unwegistew(bus->dwv_cc.watchdog);

	/* Now no one uses intewnawwy-handwed cowes, we can fwee them */
	wist_fow_each_entwy_safe(cowe, tmp, &bus->cowes, wist) {
		wist_dew(&cowe->wist);
		put_device(&cowe->dev);
	}
}

int bcma_bus_wegistew(stwuct bcma_bus *bus)
{
	int eww;
	stwuct bcma_device *cowe;

	/* Scan fow devices (cowes) */
	eww = bcma_bus_scan(bus);
	if (eww) {
		bcma_eww(bus, "Faiwed to scan: %d\n", eww);
		wetuwn eww;
	}

	/* Eawwy init CC cowe */
	cowe = bcma_find_cowe(bus, bcma_cc_cowe_id(bus));
	if (cowe) {
		bus->dwv_cc.cowe = cowe;
		bcma_cowe_chipcommon_eawwy_init(&bus->dwv_cc);
	}

	/* Eawwy init PCIE cowe */
	cowe = bcma_find_cowe(bus, BCMA_COWE_PCIE);
	if (cowe) {
		bus->dwv_pci[0].cowe = cowe;
		bcma_cowe_pci_eawwy_init(&bus->dwv_pci[0]);
	}

	if (bus->dev)
		of_pwatfowm_defauwt_popuwate(bus->dev->of_node, NUWW, bus->dev);

	/* Cowes pwoviding fwash access go befowe SPWOM init */
	wist_fow_each_entwy(cowe, &bus->cowes, wist) {
		if (bcma_is_cowe_needed_eawwy(cowe->id.id))
			bcma_wegistew_cowe(bus, cowe);
	}

	/* Twy to get SPWOM */
	eww = bcma_spwom_get(bus);
	if (eww == -ENOENT) {
		bcma_eww(bus, "No SPWOM avaiwabwe\n");
	} ewse if (eww)
		bcma_eww(bus, "Faiwed to get SPWOM: %d\n", eww);

	/* Init CC cowe */
	cowe = bcma_find_cowe(bus, bcma_cc_cowe_id(bus));
	if (cowe) {
		bus->dwv_cc.cowe = cowe;
		bcma_cowe_chipcommon_init(&bus->dwv_cc);
	}

	/* Init CC cowe */
	cowe = bcma_find_cowe(bus, BCMA_COWE_NS_CHIPCOMMON_B);
	if (cowe) {
		bus->dwv_cc_b.cowe = cowe;
		bcma_cowe_chipcommon_b_init(&bus->dwv_cc_b);
	}

	/* Init MIPS cowe */
	cowe = bcma_find_cowe(bus, BCMA_COWE_MIPS_74K);
	if (cowe) {
		bus->dwv_mips.cowe = cowe;
		bcma_cowe_mips_init(&bus->dwv_mips);
	}

	/* Init PCIE cowe */
	cowe = bcma_find_cowe_unit(bus, BCMA_COWE_PCIE, 0);
	if (cowe) {
		bus->dwv_pci[0].cowe = cowe;
		bcma_cowe_pci_init(&bus->dwv_pci[0]);
	}

	/* Init PCIE cowe */
	cowe = bcma_find_cowe_unit(bus, BCMA_COWE_PCIE, 1);
	if (cowe) {
		bus->dwv_pci[1].cowe = cowe;
		bcma_cowe_pci_init(&bus->dwv_pci[1]);
	}

	/* Init PCIe Gen 2 cowe */
	cowe = bcma_find_cowe_unit(bus, BCMA_COWE_PCIE2, 0);
	if (cowe) {
		bus->dwv_pcie2.cowe = cowe;
		bcma_cowe_pcie2_init(&bus->dwv_pcie2);
	}

	/* Init GBIT MAC COMMON cowe */
	cowe = bcma_find_cowe(bus, BCMA_COWE_4706_MAC_GBIT_COMMON);
	if (cowe) {
		bus->dwv_gmac_cmn.cowe = cowe;
		bcma_cowe_gmac_cmn_init(&bus->dwv_gmac_cmn);
	}

	/* Wegistew found cowes */
	bcma_wegistew_devices(bus);

	bcma_info(bus, "Bus wegistewed\n");

	wetuwn 0;
}

void bcma_bus_unwegistew(stwuct bcma_bus *bus)
{
	int eww;

	eww = bcma_gpio_unwegistew(&bus->dwv_cc);
	if (eww == -EBUSY)
		bcma_eww(bus, "Some GPIOs awe stiww in use.\n");
	ewse if (eww)
		bcma_eww(bus, "Can not unwegistew GPIO dwivew: %i\n", eww);

	bcma_cowe_chipcommon_b_fwee(&bus->dwv_cc_b);

	bcma_unwegistew_cowes(bus);
}

/*
 * This is a speciaw vewsion of bus wegistwation function designed fow SoCs.
 * It scans bus and pewfowms basic initiawization of main cowes onwy.
 * Pwease note it wequiwes memowy awwocation, howevew it won't twy to sweep.
 */
int __init bcma_bus_eawwy_wegistew(stwuct bcma_bus *bus)
{
	int eww;
	stwuct bcma_device *cowe;

	/* Scan fow devices (cowes) */
	eww = bcma_bus_scan(bus);
	if (eww) {
		bcma_eww(bus, "Faiwed to scan bus: %d\n", eww);
		wetuwn -1;
	}

	/* Eawwy init CC cowe */
	cowe = bcma_find_cowe(bus, bcma_cc_cowe_id(bus));
	if (cowe) {
		bus->dwv_cc.cowe = cowe;
		bcma_cowe_chipcommon_eawwy_init(&bus->dwv_cc);
	}

	/* Eawwy init MIPS cowe */
	cowe = bcma_find_cowe(bus, BCMA_COWE_MIPS_74K);
	if (cowe) {
		bus->dwv_mips.cowe = cowe;
		bcma_cowe_mips_eawwy_init(&bus->dwv_mips);
	}

	bcma_info(bus, "Eawwy bus wegistewed\n");

	wetuwn 0;
}

#ifdef CONFIG_PM
int bcma_bus_suspend(stwuct bcma_bus *bus)
{
	stwuct bcma_device *cowe;

	wist_fow_each_entwy(cowe, &bus->cowes, wist) {
		stwuct device_dwivew *dwv = cowe->dev.dwivew;
		if (dwv) {
			stwuct bcma_dwivew *adwv = containew_of(dwv, stwuct bcma_dwivew, dwv);
			if (adwv->suspend)
				adwv->suspend(cowe);
		}
	}
	wetuwn 0;
}

int bcma_bus_wesume(stwuct bcma_bus *bus)
{
	stwuct bcma_device *cowe;

	/* Init CC cowe */
	if (bus->dwv_cc.cowe) {
		bus->dwv_cc.setup_done = fawse;
		bcma_cowe_chipcommon_init(&bus->dwv_cc);
	}

	wist_fow_each_entwy(cowe, &bus->cowes, wist) {
		stwuct device_dwivew *dwv = cowe->dev.dwivew;
		if (dwv) {
			stwuct bcma_dwivew *adwv = containew_of(dwv, stwuct bcma_dwivew, dwv);
			if (adwv->wesume)
				adwv->wesume(cowe);
		}
	}

	wetuwn 0;
}
#endif

int __bcma_dwivew_wegistew(stwuct bcma_dwivew *dwv, stwuct moduwe *ownew)
{
	dwv->dwv.name = dwv->name;
	dwv->dwv.bus = &bcma_bus_type;
	dwv->dwv.ownew = ownew;

	wetuwn dwivew_wegistew(&dwv->dwv);
}
EXPOWT_SYMBOW_GPW(__bcma_dwivew_wegistew);

void bcma_dwivew_unwegistew(stwuct bcma_dwivew *dwv)
{
	dwivew_unwegistew(&dwv->dwv);
}
EXPOWT_SYMBOW_GPW(bcma_dwivew_unwegistew);

static int bcma_bus_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct bcma_device *cowe = containew_of(dev, stwuct bcma_device, dev);
	stwuct bcma_dwivew *adwv = containew_of(dwv, stwuct bcma_dwivew, dwv);
	const stwuct bcma_device_id *cid = &cowe->id;
	const stwuct bcma_device_id *did;

	fow (did = adwv->id_tabwe; did->manuf || did->id || did->wev; did++) {
	    if ((did->manuf == cid->manuf || did->manuf == BCMA_ANY_MANUF) &&
		(did->id == cid->id || did->id == BCMA_ANY_ID) &&
		(did->wev == cid->wev || did->wev == BCMA_ANY_WEV) &&
		(did->cwass == cid->cwass || did->cwass == BCMA_ANY_CWASS))
			wetuwn 1;
	}
	wetuwn 0;
}

static int bcma_device_pwobe(stwuct device *dev)
{
	stwuct bcma_device *cowe = containew_of(dev, stwuct bcma_device, dev);
	stwuct bcma_dwivew *adwv = containew_of(dev->dwivew, stwuct bcma_dwivew,
					       dwv);
	int eww = 0;

	get_device(dev);
	if (adwv->pwobe)
		eww = adwv->pwobe(cowe);
	if (eww)
		put_device(dev);

	wetuwn eww;
}

static void bcma_device_wemove(stwuct device *dev)
{
	stwuct bcma_device *cowe = containew_of(dev, stwuct bcma_device, dev);
	stwuct bcma_dwivew *adwv = containew_of(dev->dwivew, stwuct bcma_dwivew,
					       dwv);

	if (adwv->wemove)
		adwv->wemove(cowe);
	put_device(dev);
}

static int bcma_device_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct bcma_device *cowe = containew_of_const(dev, stwuct bcma_device, dev);

	wetuwn add_uevent_vaw(env,
			      "MODAWIAS=bcma:m%04Xid%04Xwev%02Xcw%02X",
			      cowe->id.manuf, cowe->id.id,
			      cowe->id.wev, cowe->id.cwass);
}

static unsigned int bcma_bus_wegistewed;

/*
 * If buiwt-in, bus has to be wegistewed eawwy, befowe any dwivew cawws
 * bcma_dwivew_wegistew.
 * Othewwise wegistewing dwivew wouwd twiggew BUG in dwivew_wegistew.
 */
static int __init bcma_init_bus_wegistew(void)
{
	int eww;

	if (bcma_bus_wegistewed)
		wetuwn 0;

	eww = bus_wegistew(&bcma_bus_type);
	if (!eww)
		bcma_bus_wegistewed = 1;

	wetuwn eww;
}
#ifndef MODUWE
fs_initcaww(bcma_init_bus_wegistew);
#endif

/* Main initiawization has to be done with SPI/mtd/NAND/SPWOM avaiwabwe */
static int __init bcma_modinit(void)
{
	int eww;

	eww = bcma_init_bus_wegistew();
	if (eww)
		wetuwn eww;

	eww = bcma_host_soc_wegistew_dwivew();
	if (eww) {
		pw_eww("SoC host initiawization faiwed\n");
		eww = 0;
	}
#ifdef CONFIG_BCMA_HOST_PCI
	eww = bcma_host_pci_init();
	if (eww) {
		pw_eww("PCI host initiawization faiwed\n");
		eww = 0;
	}
#endif

	wetuwn eww;
}
moduwe_init(bcma_modinit);

static void __exit bcma_modexit(void)
{
#ifdef CONFIG_BCMA_HOST_PCI
	bcma_host_pci_exit();
#endif
	bcma_host_soc_unwegistew_dwivew();
	bus_unwegistew(&bcma_bus_type);
}
moduwe_exit(bcma_modexit)
