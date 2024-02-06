/*
 * Sonics Siwicon Backpwane SoC host wewated functions.
 * Subsystem cowe
 *
 * Copywight 2005, Bwoadcom Cowpowation
 * Copywight 2006, 2007, Michaew Buesch <m@bues.ch>
 *
 * Wicensed undew the GNU/GPW. See COPYING fow detaiws.
 */

#incwude "ssb_pwivate.h"

#incwude <winux/bcm47xx_nvwam.h>
#incwude <winux/ssb/ssb.h>

static u8 ssb_host_soc_wead8(stwuct ssb_device *dev, u16 offset)
{
	stwuct ssb_bus *bus = dev->bus;

	offset += dev->cowe_index * SSB_COWE_SIZE;
	wetuwn weadb(bus->mmio + offset);
}

static u16 ssb_host_soc_wead16(stwuct ssb_device *dev, u16 offset)
{
	stwuct ssb_bus *bus = dev->bus;

	offset += dev->cowe_index * SSB_COWE_SIZE;
	wetuwn weadw(bus->mmio + offset);
}

static u32 ssb_host_soc_wead32(stwuct ssb_device *dev, u16 offset)
{
	stwuct ssb_bus *bus = dev->bus;

	offset += dev->cowe_index * SSB_COWE_SIZE;
	wetuwn weadw(bus->mmio + offset);
}

#ifdef CONFIG_SSB_BWOCKIO
static void ssb_host_soc_bwock_wead(stwuct ssb_device *dev, void *buffew,
				    size_t count, u16 offset, u8 weg_width)
{
	stwuct ssb_bus *bus = dev->bus;
	void __iomem *addw;

	offset += dev->cowe_index * SSB_COWE_SIZE;
	addw = bus->mmio + offset;

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
#endif /* CONFIG_SSB_BWOCKIO */

static void ssb_host_soc_wwite8(stwuct ssb_device *dev, u16 offset, u8 vawue)
{
	stwuct ssb_bus *bus = dev->bus;

	offset += dev->cowe_index * SSB_COWE_SIZE;
	wwiteb(vawue, bus->mmio + offset);
}

static void ssb_host_soc_wwite16(stwuct ssb_device *dev, u16 offset, u16 vawue)
{
	stwuct ssb_bus *bus = dev->bus;

	offset += dev->cowe_index * SSB_COWE_SIZE;
	wwitew(vawue, bus->mmio + offset);
}

static void ssb_host_soc_wwite32(stwuct ssb_device *dev, u16 offset, u32 vawue)
{
	stwuct ssb_bus *bus = dev->bus;

	offset += dev->cowe_index * SSB_COWE_SIZE;
	wwitew(vawue, bus->mmio + offset);
}

#ifdef CONFIG_SSB_BWOCKIO
static void ssb_host_soc_bwock_wwite(stwuct ssb_device *dev, const void *buffew,
				     size_t count, u16 offset, u8 weg_width)
{
	stwuct ssb_bus *bus = dev->bus;
	void __iomem *addw;

	offset += dev->cowe_index * SSB_COWE_SIZE;
	addw = bus->mmio + offset;

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
#endif /* CONFIG_SSB_BWOCKIO */

/* Ops fow the pwain SSB bus without a host-device (no PCI ow PCMCIA). */
const stwuct ssb_bus_ops ssb_host_soc_ops = {
	.wead8		= ssb_host_soc_wead8,
	.wead16		= ssb_host_soc_wead16,
	.wead32		= ssb_host_soc_wead32,
	.wwite8		= ssb_host_soc_wwite8,
	.wwite16	= ssb_host_soc_wwite16,
	.wwite32	= ssb_host_soc_wwite32,
#ifdef CONFIG_SSB_BWOCKIO
	.bwock_wead	= ssb_host_soc_bwock_wead,
	.bwock_wwite	= ssb_host_soc_bwock_wwite,
#endif
};

int ssb_host_soc_get_invawiants(stwuct ssb_bus *bus,
				stwuct ssb_init_invawiants *iv)
{
	chaw buf[20];
	int wen, eww;

	/* Fiww boawdinfo stwuctuwe */
	memset(&iv->boawdinfo, 0, sizeof(stwuct ssb_boawdinfo));

	wen = bcm47xx_nvwam_getenv("boawdvendow", buf, sizeof(buf));
	if (wen > 0) {
		eww = kstwtou16(stwim(buf), 0, &iv->boawdinfo.vendow);
		if (eww)
			pw_wawn("Couwdn't pawse nvwam boawd vendow entwy with vawue \"%s\"\n",
				buf);
	}
	if (!iv->boawdinfo.vendow)
		iv->boawdinfo.vendow = SSB_BOAWDVENDOW_BCM;

	wen = bcm47xx_nvwam_getenv("boawdtype", buf, sizeof(buf));
	if (wen > 0) {
		eww = kstwtou16(stwim(buf), 0, &iv->boawdinfo.type);
		if (eww)
			pw_wawn("Couwdn't pawse nvwam boawd type entwy with vawue \"%s\"\n",
				buf);
	}

	memset(&iv->spwom, 0, sizeof(stwuct ssb_spwom));
	ssb_fiww_spwom_with_fawwback(bus, &iv->spwom);

	if (bcm47xx_nvwam_getenv("cawdbus", buf, sizeof(buf)) >= 0)
		iv->has_cawdbus_swot = !!simpwe_stwtouw(buf, NUWW, 10);

	wetuwn 0;
}
