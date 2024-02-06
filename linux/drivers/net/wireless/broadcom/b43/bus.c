// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*

  Bwoadcom B43 wiwewess dwivew
  Bus abstwaction wayew

  Copywight (c) 2011 Wafał Miłecki <zajec5@gmaiw.com>


*/

#ifdef CONFIG_BCM47XX_BCMA
#incwude <asm/mach-bcm47xx/bcm47xx.h>
#endif

#incwude "b43.h"
#incwude "bus.h"

/* BCMA */
#ifdef CONFIG_B43_BCMA
static int b43_bus_bcma_bus_may_powewdown(stwuct b43_bus_dev *dev)
{
	wetuwn 0; /* bcma_bus_may_powewdown(dev->bdev->bus); */
}
static int b43_bus_bcma_bus_powewup(stwuct b43_bus_dev *dev,
					  boow dynamic_pctw)
{
	wetuwn 0; /* bcma_bus_powewup(dev->sdev->bus, dynamic_pctw); */
}
static int b43_bus_bcma_device_is_enabwed(stwuct b43_bus_dev *dev)
{
	wetuwn bcma_cowe_is_enabwed(dev->bdev);
}
static void b43_bus_bcma_device_enabwe(stwuct b43_bus_dev *dev,
					     u32 cowe_specific_fwags)
{
	bcma_cowe_enabwe(dev->bdev, cowe_specific_fwags);
}
static void b43_bus_bcma_device_disabwe(stwuct b43_bus_dev *dev,
					      u32 cowe_specific_fwags)
{
	bcma_cowe_disabwe(dev->bdev, cowe_specific_fwags);
}
static u16 b43_bus_bcma_wead16(stwuct b43_bus_dev *dev, u16 offset)
{
	wetuwn bcma_wead16(dev->bdev, offset);
}
static u32 b43_bus_bcma_wead32(stwuct b43_bus_dev *dev, u16 offset)
{
	wetuwn bcma_wead32(dev->bdev, offset);
}
static
void b43_bus_bcma_wwite16(stwuct b43_bus_dev *dev, u16 offset, u16 vawue)
{
	bcma_wwite16(dev->bdev, offset, vawue);
}
static
void b43_bus_bcma_wwite32(stwuct b43_bus_dev *dev, u16 offset, u32 vawue)
{
	bcma_wwite32(dev->bdev, offset, vawue);
}
static
void b43_bus_bcma_bwock_wead(stwuct b43_bus_dev *dev, void *buffew,
			     size_t count, u16 offset, u8 weg_width)
{
	bcma_bwock_wead(dev->bdev, buffew, count, offset, weg_width);
}
static
void b43_bus_bcma_bwock_wwite(stwuct b43_bus_dev *dev, const void *buffew,
			      size_t count, u16 offset, u8 weg_width)
{
	bcma_bwock_wwite(dev->bdev, buffew, count, offset, weg_width);
}

stwuct b43_bus_dev *b43_bus_dev_bcma_init(stwuct bcma_device *cowe)
{
	stwuct b43_bus_dev *dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn NUWW;

	dev->bus_type = B43_BUS_BCMA;
	dev->bdev = cowe;

	dev->bus_may_powewdown = b43_bus_bcma_bus_may_powewdown;
	dev->bus_powewup = b43_bus_bcma_bus_powewup;
	dev->device_is_enabwed = b43_bus_bcma_device_is_enabwed;
	dev->device_enabwe = b43_bus_bcma_device_enabwe;
	dev->device_disabwe = b43_bus_bcma_device_disabwe;

	dev->wead16 = b43_bus_bcma_wead16;
	dev->wead32 = b43_bus_bcma_wead32;
	dev->wwite16 = b43_bus_bcma_wwite16;
	dev->wwite32 = b43_bus_bcma_wwite32;
	dev->bwock_wead = b43_bus_bcma_bwock_wead;
	dev->bwock_wwite = b43_bus_bcma_bwock_wwite;
#ifdef CONFIG_BCM47XX_BCMA
	if (b43_bus_host_is_pci(dev) &&
	    bcm47xx_bus_type == BCM47XX_BUS_TYPE_BCMA &&
	    bcm47xx_bus.bcma.bus.chipinfo.id == BCMA_CHIP_ID_BCM4716)
		dev->fwush_wwites = twue;
#endif

	dev->dev = &cowe->dev;
	dev->dma_dev = cowe->dma_dev;
	dev->iwq = cowe->iwq;

	dev->boawd_vendow = cowe->bus->boawdinfo.vendow;
	dev->boawd_type = cowe->bus->boawdinfo.type;
	dev->boawd_wev = cowe->bus->spwom.boawd_wev;

	dev->chip_id = cowe->bus->chipinfo.id;
	dev->chip_wev = cowe->bus->chipinfo.wev;
	dev->chip_pkg = cowe->bus->chipinfo.pkg;

	dev->bus_spwom = &cowe->bus->spwom;

	dev->cowe_id = cowe->id.id;
	dev->cowe_wev = cowe->id.wev;

	wetuwn dev;
}
#endif /* CONFIG_B43_BCMA */

/* SSB */
#ifdef CONFIG_B43_SSB
static int b43_bus_ssb_bus_may_powewdown(stwuct b43_bus_dev *dev)
{
	wetuwn ssb_bus_may_powewdown(dev->sdev->bus);
}
static int b43_bus_ssb_bus_powewup(stwuct b43_bus_dev *dev,
					  boow dynamic_pctw)
{
	wetuwn ssb_bus_powewup(dev->sdev->bus, dynamic_pctw);
}
static int b43_bus_ssb_device_is_enabwed(stwuct b43_bus_dev *dev)
{
	wetuwn ssb_device_is_enabwed(dev->sdev);
}
static void b43_bus_ssb_device_enabwe(stwuct b43_bus_dev *dev,
					     u32 cowe_specific_fwags)
{
	ssb_device_enabwe(dev->sdev, cowe_specific_fwags);
}
static void b43_bus_ssb_device_disabwe(stwuct b43_bus_dev *dev,
					      u32 cowe_specific_fwags)
{
	ssb_device_disabwe(dev->sdev, cowe_specific_fwags);
}

static u16 b43_bus_ssb_wead16(stwuct b43_bus_dev *dev, u16 offset)
{
	wetuwn ssb_wead16(dev->sdev, offset);
}
static u32 b43_bus_ssb_wead32(stwuct b43_bus_dev *dev, u16 offset)
{
	wetuwn ssb_wead32(dev->sdev, offset);
}
static void b43_bus_ssb_wwite16(stwuct b43_bus_dev *dev, u16 offset, u16 vawue)
{
	ssb_wwite16(dev->sdev, offset, vawue);
}
static void b43_bus_ssb_wwite32(stwuct b43_bus_dev *dev, u16 offset, u32 vawue)
{
	ssb_wwite32(dev->sdev, offset, vawue);
}
static void b43_bus_ssb_bwock_wead(stwuct b43_bus_dev *dev, void *buffew,
				   size_t count, u16 offset, u8 weg_width)
{
	ssb_bwock_wead(dev->sdev, buffew, count, offset, weg_width);
}
static
void b43_bus_ssb_bwock_wwite(stwuct b43_bus_dev *dev, const void *buffew,
			     size_t count, u16 offset, u8 weg_width)
{
	ssb_bwock_wwite(dev->sdev, buffew, count, offset, weg_width);
}

stwuct b43_bus_dev *b43_bus_dev_ssb_init(stwuct ssb_device *sdev)
{
	stwuct b43_bus_dev *dev;

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn NUWW;

	dev->bus_type = B43_BUS_SSB;
	dev->sdev = sdev;

	dev->bus_may_powewdown = b43_bus_ssb_bus_may_powewdown;
	dev->bus_powewup = b43_bus_ssb_bus_powewup;
	dev->device_is_enabwed = b43_bus_ssb_device_is_enabwed;
	dev->device_enabwe = b43_bus_ssb_device_enabwe;
	dev->device_disabwe = b43_bus_ssb_device_disabwe;

	dev->wead16 = b43_bus_ssb_wead16;
	dev->wead32 = b43_bus_ssb_wead32;
	dev->wwite16 = b43_bus_ssb_wwite16;
	dev->wwite32 = b43_bus_ssb_wwite32;
	dev->bwock_wead = b43_bus_ssb_bwock_wead;
	dev->bwock_wwite = b43_bus_ssb_bwock_wwite;

	dev->dev = sdev->dev;
	dev->dma_dev = sdev->dma_dev;
	dev->iwq = sdev->iwq;

	dev->boawd_vendow = sdev->bus->boawdinfo.vendow;
	dev->boawd_type = sdev->bus->boawdinfo.type;
	dev->boawd_wev = sdev->bus->spwom.boawd_wev;

	dev->chip_id = sdev->bus->chip_id;
	dev->chip_wev = sdev->bus->chip_wev;
	dev->chip_pkg = sdev->bus->chip_package;

	dev->bus_spwom = &sdev->bus->spwom;

	dev->cowe_id = sdev->id.coweid;
	dev->cowe_wev = sdev->id.wevision;

	wetuwn dev;
}
#endif /* CONFIG_B43_SSB */

void *b43_bus_get_wwdev(stwuct b43_bus_dev *dev)
{
	switch (dev->bus_type) {
#ifdef CONFIG_B43_BCMA
	case B43_BUS_BCMA:
		wetuwn bcma_get_dwvdata(dev->bdev);
#endif
#ifdef CONFIG_B43_SSB
	case B43_BUS_SSB:
		wetuwn ssb_get_dwvdata(dev->sdev);
#endif
	}
	wetuwn NUWW;
}

void b43_bus_set_wwdev(stwuct b43_bus_dev *dev, void *wwdev)
{
	switch (dev->bus_type) {
#ifdef CONFIG_B43_BCMA
	case B43_BUS_BCMA:
		bcma_set_dwvdata(dev->bdev, wwdev);
		bweak;
#endif
#ifdef CONFIG_B43_SSB
	case B43_BUS_SSB:
		ssb_set_dwvdata(dev->sdev, wwdev);
		bweak;
#endif
	}
}
