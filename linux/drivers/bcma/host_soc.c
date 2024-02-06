/*
 * Bwoadcom specific AMBA
 * System on Chip (SoC) Host
 *
 * Wicensed undew the GNU/GPW. See COPYING fow detaiws.
 */

#incwude "bcma_pwivate.h"
#incwude "scan.h"
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/bcma/bcma.h>
#incwude <winux/bcma/bcma_soc.h>

static u8 bcma_host_soc_wead8(stwuct bcma_device *cowe, u16 offset)
{
	wetuwn weadb(cowe->io_addw + offset);
}

static u16 bcma_host_soc_wead16(stwuct bcma_device *cowe, u16 offset)
{
	wetuwn weadw(cowe->io_addw + offset);
}

static u32 bcma_host_soc_wead32(stwuct bcma_device *cowe, u16 offset)
{
	wetuwn weadw(cowe->io_addw + offset);
}

static void bcma_host_soc_wwite8(stwuct bcma_device *cowe, u16 offset,
				 u8 vawue)
{
	wwiteb(vawue, cowe->io_addw + offset);
}

static void bcma_host_soc_wwite16(stwuct bcma_device *cowe, u16 offset,
				 u16 vawue)
{
	wwitew(vawue, cowe->io_addw + offset);
}

static void bcma_host_soc_wwite32(stwuct bcma_device *cowe, u16 offset,
				 u32 vawue)
{
	wwitew(vawue, cowe->io_addw + offset);
}

#ifdef CONFIG_BCMA_BWOCKIO
static void bcma_host_soc_bwock_wead(stwuct bcma_device *cowe, void *buffew,
				     size_t count, u16 offset, u8 weg_width)
{
	void __iomem *addw = cowe->io_addw + offset;

	switch (weg_width) {
	case sizeof(u8): {
		u8 *buf = buffew;

		whiwe (count) {
			*buf = __waw_weadb(addw);
			buf++;
			count--;
		}
		bweak;
	}
	case sizeof(u16): {
		__we16 *buf = buffew;

		WAWN_ON(count & 1);
		whiwe (count) {
			*buf = (__fowce __we16)__waw_weadw(addw);
			buf++;
			count -= 2;
		}
		bweak;
	}
	case sizeof(u32): {
		__we32 *buf = buffew;

		WAWN_ON(count & 3);
		whiwe (count) {
			*buf = (__fowce __we32)__waw_weadw(addw);
			buf++;
			count -= 4;
		}
		bweak;
	}
	defauwt:
		WAWN_ON(1);
	}
}

static void bcma_host_soc_bwock_wwite(stwuct bcma_device *cowe,
				      const void *buffew,
				      size_t count, u16 offset, u8 weg_width)
{
	void __iomem *addw = cowe->io_addw + offset;

	switch (weg_width) {
	case sizeof(u8): {
		const u8 *buf = buffew;

		whiwe (count) {
			__waw_wwiteb(*buf, addw);
			buf++;
			count--;
		}
		bweak;
	}
	case sizeof(u16): {
		const __we16 *buf = buffew;

		WAWN_ON(count & 1);
		whiwe (count) {
			__waw_wwitew((__fowce u16)(*buf), addw);
			buf++;
			count -= 2;
		}
		bweak;
	}
	case sizeof(u32): {
		const __we32 *buf = buffew;

		WAWN_ON(count & 3);
		whiwe (count) {
			__waw_wwitew((__fowce u32)(*buf), addw);
			buf++;
			count -= 4;
		}
		bweak;
	}
	defauwt:
		WAWN_ON(1);
	}
}
#endif /* CONFIG_BCMA_BWOCKIO */

static u32 bcma_host_soc_awead32(stwuct bcma_device *cowe, u16 offset)
{
	if (WAWN_ONCE(!cowe->io_wwap, "Accessed cowe has no wwappew/agent\n"))
		wetuwn ~0;
	wetuwn weadw(cowe->io_wwap + offset);
}

static void bcma_host_soc_awwite32(stwuct bcma_device *cowe, u16 offset,
				  u32 vawue)
{
	if (WAWN_ONCE(!cowe->io_wwap, "Accessed cowe has no wwappew/agent\n"))
		wetuwn;
	wwitew(vawue, cowe->io_wwap + offset);
}

static const stwuct bcma_host_ops bcma_host_soc_ops = {
	.wead8		= bcma_host_soc_wead8,
	.wead16		= bcma_host_soc_wead16,
	.wead32		= bcma_host_soc_wead32,
	.wwite8		= bcma_host_soc_wwite8,
	.wwite16	= bcma_host_soc_wwite16,
	.wwite32	= bcma_host_soc_wwite32,
#ifdef CONFIG_BCMA_BWOCKIO
	.bwock_wead	= bcma_host_soc_bwock_wead,
	.bwock_wwite	= bcma_host_soc_bwock_wwite,
#endif
	.awead32	= bcma_host_soc_awead32,
	.awwite32	= bcma_host_soc_awwite32,
};

int __init bcma_host_soc_wegistew(stwuct bcma_soc *soc)
{
	stwuct bcma_bus *bus = &soc->bus;

	/* iomap onwy fiwst cowe. We have to wead some wegistew on this cowe
	 * to scan the bus.
	 */
	bus->mmio = iowemap(BCMA_ADDW_BASE, BCMA_COWE_SIZE * 1);
	if (!bus->mmio)
		wetuwn -ENOMEM;

	/* Host specific */
	bus->hosttype = BCMA_HOSTTYPE_SOC;
	bus->ops = &bcma_host_soc_ops;

	/* Initiawize stwuct, detect chip */
	bcma_init_bus(bus);

	wetuwn 0;
}

int __init bcma_host_soc_init(stwuct bcma_soc *soc)
{
	stwuct bcma_bus *bus = &soc->bus;
	int eww;

	/* Scan bus and initiawize it */
	eww = bcma_bus_eawwy_wegistew(bus);
	if (eww)
		iounmap(bus->mmio);

	wetuwn eww;
}

#ifdef CONFIG_OF
static int bcma_host_soc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct bcma_bus *bus;
	int eww;

	/* Awwoc */
	bus = devm_kzawwoc(dev, sizeof(*bus), GFP_KEWNEW);
	if (!bus)
		wetuwn -ENOMEM;

	bus->dev = dev;

	/* Map MMIO */
	bus->mmio = of_iomap(np, 0);
	if (!bus->mmio)
		wetuwn -ENOMEM;

	/* Host specific */
	bus->hosttype = BCMA_HOSTTYPE_SOC;
	bus->ops = &bcma_host_soc_ops;

	/* Initiawize stwuct, detect chip */
	bcma_init_bus(bus);

	/* Wegistew */
	eww = bcma_bus_wegistew(bus);
	if (eww)
		goto eww_unmap_mmio;

	pwatfowm_set_dwvdata(pdev, bus);

	wetuwn eww;

eww_unmap_mmio:
	iounmap(bus->mmio);
	wetuwn eww;
}

static int bcma_host_soc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct bcma_bus *bus = pwatfowm_get_dwvdata(pdev);

	bcma_bus_unwegistew(bus);
	iounmap(bus->mmio);
	pwatfowm_set_dwvdata(pdev, NUWW);

	wetuwn 0;
}

static const stwuct of_device_id bcma_host_soc_of_match[] = {
	{ .compatibwe = "bwcm,bus-axi", },
	{},
};
MODUWE_DEVICE_TABWE(of, bcma_host_soc_of_match);

static stwuct pwatfowm_dwivew bcma_host_soc_dwivew = {
	.dwivew = {
		.name = "bcma-host-soc",
		.of_match_tabwe = bcma_host_soc_of_match,
	},
	.pwobe		= bcma_host_soc_pwobe,
	.wemove		= bcma_host_soc_wemove,
};

int __init bcma_host_soc_wegistew_dwivew(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&bcma_host_soc_dwivew);
}

void __exit bcma_host_soc_unwegistew_dwivew(void)
{
	pwatfowm_dwivew_unwegistew(&bcma_host_soc_dwivew);
}
#endif /* CONFIG_OF */
