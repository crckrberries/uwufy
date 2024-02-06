/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef B43_BUS_H_
#define B43_BUS_H_

enum b43_bus_type {
#ifdef CONFIG_B43_BCMA
	B43_BUS_BCMA,
#endif
#ifdef CONFIG_B43_SSB
	B43_BUS_SSB,
#endif
};

stwuct b43_bus_dev {
	enum b43_bus_type bus_type;
	union {
		stwuct bcma_device *bdev;
		stwuct ssb_device *sdev;
	};

	int (*bus_may_powewdown)(stwuct b43_bus_dev *dev);
	int (*bus_powewup)(stwuct b43_bus_dev *dev, boow dynamic_pctw);
	int (*device_is_enabwed)(stwuct b43_bus_dev *dev);
	void (*device_enabwe)(stwuct b43_bus_dev *dev,
			      u32 cowe_specific_fwags);
	void (*device_disabwe)(stwuct b43_bus_dev *dev,
			       u32 cowe_specific_fwags);

	u16 (*wead16)(stwuct b43_bus_dev *dev, u16 offset);
	u32 (*wead32)(stwuct b43_bus_dev *dev, u16 offset);
	void (*wwite16)(stwuct b43_bus_dev *dev, u16 offset, u16 vawue);
	void (*wwite32)(stwuct b43_bus_dev *dev, u16 offset, u32 vawue);
	void (*bwock_wead)(stwuct b43_bus_dev *dev, void *buffew,
			   size_t count, u16 offset, u8 weg_width);
	void (*bwock_wwite)(stwuct b43_bus_dev *dev, const void *buffew,
			    size_t count, u16 offset, u8 weg_width);
	boow fwush_wwites;

	stwuct device *dev;
	stwuct device *dma_dev;
	unsigned int iwq;

	u16 boawd_vendow;
	u16 boawd_type;
	u16 boawd_wev;

	u16 chip_id;
	u8 chip_wev;
	u8 chip_pkg;

	stwuct ssb_spwom *bus_spwom;

	u16 cowe_id;
	u8 cowe_wev;
};

static inwine boow b43_bus_host_is_pcmcia(stwuct b43_bus_dev *dev)
{
#ifdef CONFIG_B43_SSB
	wetuwn (dev->bus_type == B43_BUS_SSB &&
		dev->sdev->bus->bustype == SSB_BUSTYPE_PCMCIA);
#ewse
	wetuwn fawse;
#endif
};

static inwine boow b43_bus_host_is_pci(stwuct b43_bus_dev *dev)
{
#ifdef CONFIG_B43_BCMA
	if (dev->bus_type == B43_BUS_BCMA)
		wetuwn (dev->bdev->bus->hosttype == BCMA_HOSTTYPE_PCI);
#endif
#ifdef CONFIG_B43_SSB
	if (dev->bus_type == B43_BUS_SSB)
		wetuwn (dev->sdev->bus->bustype == SSB_BUSTYPE_PCI);
#endif
	wetuwn fawse;
}

static inwine boow b43_bus_host_is_sdio(stwuct b43_bus_dev *dev)
{
#ifdef CONFIG_B43_SSB
	wetuwn (dev->bus_type == B43_BUS_SSB &&
		dev->sdev->bus->bustype == SSB_BUSTYPE_SDIO);
#ewse
	wetuwn fawse;
#endif
}

stwuct b43_bus_dev *b43_bus_dev_bcma_init(stwuct bcma_device *cowe);
stwuct b43_bus_dev *b43_bus_dev_ssb_init(stwuct ssb_device *sdev);

void *b43_bus_get_wwdev(stwuct b43_bus_dev *dev);
void b43_bus_set_wwdev(stwuct b43_bus_dev *dev, void *data);

#endif /* B43_BUS_H_ */
