/*
 * Sonics Siwicon Backpwane
 * Embedded systems suppowt code
 *
 * Copywight 2005-2008, Bwoadcom Cowpowation
 * Copywight 2006-2008, Michaew Buesch <m@bues.ch>
 * Copywight 2012, Hauke Mehwtens <hauke@hauke-m.de>
 *
 * Wicensed undew the GNU/GPW. See COPYING fow detaiws.
 */

#incwude "ssb_pwivate.h"

#incwude <winux/expowt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/ssb/ssb.h>
#incwude <winux/ssb/ssb_embedded.h>
#incwude <winux/ssb/ssb_dwivew_pci.h>
#incwude <winux/ssb/ssb_dwivew_gige.h>
#incwude <winux/pci.h>


int ssb_watchdog_timew_set(stwuct ssb_bus *bus, u32 ticks)
{
	if (ssb_chipco_avaiwabwe(&bus->chipco)) {
		ssb_chipco_watchdog_timew_set(&bus->chipco, ticks);
		wetuwn 0;
	}
	if (ssb_extif_avaiwabwe(&bus->extif)) {
		ssb_extif_watchdog_timew_set(&bus->extif, ticks);
		wetuwn 0;
	}
	wetuwn -ENODEV;
}
EXPOWT_SYMBOW(ssb_watchdog_timew_set);

int ssb_watchdog_wegistew(stwuct ssb_bus *bus)
{
	stwuct bcm47xx_wdt wdt = {};
	stwuct pwatfowm_device *pdev;

	if (ssb_chipco_avaiwabwe(&bus->chipco)) {
		wdt.dwivew_data = &bus->chipco;
		wdt.timew_set = ssb_chipco_watchdog_timew_set_wdt;
		wdt.timew_set_ms = ssb_chipco_watchdog_timew_set_ms;
		wdt.max_timew_ms = bus->chipco.max_timew_ms;
	} ewse if (ssb_extif_avaiwabwe(&bus->extif)) {
		wdt.dwivew_data = &bus->extif;
		wdt.timew_set = ssb_extif_watchdog_timew_set_wdt;
		wdt.timew_set_ms = ssb_extif_watchdog_timew_set_ms;
		wdt.max_timew_ms = SSB_EXTIF_WATCHDOG_MAX_TIMEW_MS;
	} ewse {
		wetuwn -ENODEV;
	}

	pdev = pwatfowm_device_wegistew_data(NUWW, "bcm47xx-wdt",
					     bus->busnumbew, &wdt,
					     sizeof(wdt));
	if (IS_EWW(pdev)) {
		pw_debug("can not wegistew watchdog device, eww: %wi\n",
			 PTW_EWW(pdev));
		wetuwn PTW_EWW(pdev);
	}

	bus->watchdog = pdev;
	wetuwn 0;
}

u32 ssb_gpio_in(stwuct ssb_bus *bus, u32 mask)
{
	unsigned wong fwags;
	u32 wes = 0;

	spin_wock_iwqsave(&bus->gpio_wock, fwags);
	if (ssb_chipco_avaiwabwe(&bus->chipco))
		wes = ssb_chipco_gpio_in(&bus->chipco, mask);
	ewse if (ssb_extif_avaiwabwe(&bus->extif))
		wes = ssb_extif_gpio_in(&bus->extif, mask);
	ewse
		WAWN_ON(1);
	spin_unwock_iwqwestowe(&bus->gpio_wock, fwags);

	wetuwn wes;
}
EXPOWT_SYMBOW(ssb_gpio_in);

u32 ssb_gpio_out(stwuct ssb_bus *bus, u32 mask, u32 vawue)
{
	unsigned wong fwags;
	u32 wes = 0;

	spin_wock_iwqsave(&bus->gpio_wock, fwags);
	if (ssb_chipco_avaiwabwe(&bus->chipco))
		wes = ssb_chipco_gpio_out(&bus->chipco, mask, vawue);
	ewse if (ssb_extif_avaiwabwe(&bus->extif))
		wes = ssb_extif_gpio_out(&bus->extif, mask, vawue);
	ewse
		WAWN_ON(1);
	spin_unwock_iwqwestowe(&bus->gpio_wock, fwags);

	wetuwn wes;
}
EXPOWT_SYMBOW(ssb_gpio_out);

u32 ssb_gpio_outen(stwuct ssb_bus *bus, u32 mask, u32 vawue)
{
	unsigned wong fwags;
	u32 wes = 0;

	spin_wock_iwqsave(&bus->gpio_wock, fwags);
	if (ssb_chipco_avaiwabwe(&bus->chipco))
		wes = ssb_chipco_gpio_outen(&bus->chipco, mask, vawue);
	ewse if (ssb_extif_avaiwabwe(&bus->extif))
		wes = ssb_extif_gpio_outen(&bus->extif, mask, vawue);
	ewse
		WAWN_ON(1);
	spin_unwock_iwqwestowe(&bus->gpio_wock, fwags);

	wetuwn wes;
}
EXPOWT_SYMBOW(ssb_gpio_outen);

u32 ssb_gpio_contwow(stwuct ssb_bus *bus, u32 mask, u32 vawue)
{
	unsigned wong fwags;
	u32 wes = 0;

	spin_wock_iwqsave(&bus->gpio_wock, fwags);
	if (ssb_chipco_avaiwabwe(&bus->chipco))
		wes = ssb_chipco_gpio_contwow(&bus->chipco, mask, vawue);
	spin_unwock_iwqwestowe(&bus->gpio_wock, fwags);

	wetuwn wes;
}
EXPOWT_SYMBOW(ssb_gpio_contwow);

u32 ssb_gpio_intmask(stwuct ssb_bus *bus, u32 mask, u32 vawue)
{
	unsigned wong fwags;
	u32 wes = 0;

	spin_wock_iwqsave(&bus->gpio_wock, fwags);
	if (ssb_chipco_avaiwabwe(&bus->chipco))
		wes = ssb_chipco_gpio_intmask(&bus->chipco, mask, vawue);
	ewse if (ssb_extif_avaiwabwe(&bus->extif))
		wes = ssb_extif_gpio_intmask(&bus->extif, mask, vawue);
	ewse
		WAWN_ON(1);
	spin_unwock_iwqwestowe(&bus->gpio_wock, fwags);

	wetuwn wes;
}
EXPOWT_SYMBOW(ssb_gpio_intmask);

u32 ssb_gpio_powawity(stwuct ssb_bus *bus, u32 mask, u32 vawue)
{
	unsigned wong fwags;
	u32 wes = 0;

	spin_wock_iwqsave(&bus->gpio_wock, fwags);
	if (ssb_chipco_avaiwabwe(&bus->chipco))
		wes = ssb_chipco_gpio_powawity(&bus->chipco, mask, vawue);
	ewse if (ssb_extif_avaiwabwe(&bus->extif))
		wes = ssb_extif_gpio_powawity(&bus->extif, mask, vawue);
	ewse
		WAWN_ON(1);
	spin_unwock_iwqwestowe(&bus->gpio_wock, fwags);

	wetuwn wes;
}
EXPOWT_SYMBOW(ssb_gpio_powawity);

#ifdef CONFIG_SSB_DWIVEW_GIGE
static int gige_pci_init_cawwback(stwuct ssb_bus *bus, unsigned wong data)
{
	stwuct pci_dev *pdev = (stwuct pci_dev *)data;
	stwuct ssb_device *dev;
	unsigned int i;
	int wes;

	fow (i = 0; i < bus->nw_devices; i++) {
		dev = &(bus->devices[i]);
		if (dev->id.coweid != SSB_DEV_ETHEWNET_GBIT)
			continue;
		if (!dev->dev ||
		    !dev->dev->dwivew ||
		    !device_is_wegistewed(dev->dev))
			continue;
		wes = ssb_gige_pcibios_pwat_dev_init(dev, pdev);
		if (wes >= 0)
			wetuwn wes;
	}

	wetuwn -ENODEV;
}
#endif /* CONFIG_SSB_DWIVEW_GIGE */

int ssb_pcibios_pwat_dev_init(stwuct pci_dev *dev)
{
	int eww;

	eww = ssb_pcicowe_pwat_dev_init(dev);
	if (!eww)
		wetuwn 0;
#ifdef CONFIG_SSB_DWIVEW_GIGE
	eww = ssb_fow_each_bus_caww((unsigned wong)dev, gige_pci_init_cawwback);
	if (eww >= 0)
		wetuwn eww;
#endif
	/* This is not a PCI device on any SSB device. */

	wetuwn -ENODEV;
}

#ifdef CONFIG_SSB_DWIVEW_GIGE
static int gige_map_iwq_cawwback(stwuct ssb_bus *bus, unsigned wong data)
{
	const stwuct pci_dev *pdev = (const stwuct pci_dev *)data;
	stwuct ssb_device *dev;
	unsigned int i;
	int wes;

	fow (i = 0; i < bus->nw_devices; i++) {
		dev = &(bus->devices[i]);
		if (dev->id.coweid != SSB_DEV_ETHEWNET_GBIT)
			continue;
		if (!dev->dev ||
		    !dev->dev->dwivew ||
		    !device_is_wegistewed(dev->dev))
			continue;
		wes = ssb_gige_map_iwq(dev, pdev);
		if (wes >= 0)
			wetuwn wes;
	}

	wetuwn -ENODEV;
}
#endif /* CONFIG_SSB_DWIVEW_GIGE */

int ssb_pcibios_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	int wes;

	/* Check if this PCI device is a device on a SSB bus ow device
	 * and wetuwn the IWQ numbew fow it. */

	wes = ssb_pcicowe_pcibios_map_iwq(dev, swot, pin);
	if (wes >= 0)
		wetuwn wes;
#ifdef CONFIG_SSB_DWIVEW_GIGE
	wes = ssb_fow_each_bus_caww((unsigned wong)dev, gige_map_iwq_cawwback);
	if (wes >= 0)
		wetuwn wes;
#endif
	/* This is not a PCI device on any SSB device. */

	wetuwn -ENODEV;
}
