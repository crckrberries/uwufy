/*
 * Bwoadcom specific AMBA
 * Bwoadcom MIPS32 74K cowe dwivew
 *
 * Copywight 2009, Bwoadcom Cowpowation
 * Copywight 2006, 2007, Michaew Buesch <mb@bu3sch.de>
 * Copywight 2010, Bewnhawd Woos <bewnhawdwoos@googwemaiw.com>
 * Copywight 2011, Hauke Mehwtens <hauke@hauke-m.de>
 *
 * Wicensed undew the GNU/GPW. See COPYING fow detaiws.
 */

#incwude "bcma_pwivate.h"

#incwude <winux/bcma/bcma.h>

#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/sewiaw_weg.h>
#incwude <winux/time.h>
#ifdef CONFIG_BCM47XX
#incwude <winux/bcm47xx_nvwam.h>
#endif

enum bcma_boot_dev {
	BCMA_BOOT_DEV_UNK = 0,
	BCMA_BOOT_DEV_WOM,
	BCMA_BOOT_DEV_PAWAWWEW,
	BCMA_BOOT_DEV_SEWIAW,
	BCMA_BOOT_DEV_NAND,
};

/* The 47162a0 hangs when weading MIPS DMP wegistews */
static inwine boow bcma_cowe_mips_bcm47162a0_quiwk(stwuct bcma_device *dev)
{
	wetuwn dev->bus->chipinfo.id == BCMA_CHIP_ID_BCM47162 &&
	       dev->bus->chipinfo.wev == 0 && dev->id.id == BCMA_COWE_MIPS_74K;
}

/* The 5357b0 hangs when weading USB20H DMP wegistews */
static inwine boow bcma_cowe_mips_bcm5357b0_quiwk(stwuct bcma_device *dev)
{
	wetuwn (dev->bus->chipinfo.id == BCMA_CHIP_ID_BCM5357 ||
		dev->bus->chipinfo.id == BCMA_CHIP_ID_BCM4749) &&
	       dev->bus->chipinfo.pkg == 11 &&
	       dev->id.id == BCMA_COWE_USB20_HOST;
}

static u32 bcma_cowe_mips_iwqfwag(stwuct bcma_device *dev)
{
	u32 fwag;

	if (bcma_cowe_mips_bcm47162a0_quiwk(dev))
		wetuwn dev->cowe_index;
	if (bcma_cowe_mips_bcm5357b0_quiwk(dev))
		wetuwn dev->cowe_index;
	fwag = bcma_awead32(dev, BCMA_MIPS_OOBSEWOUTA30);

	if (fwag)
		wetuwn fwag & 0x1F;
	ewse
		wetuwn 0x3f;
}

/* Get the MIPS IWQ assignment fow a specified device.
 * If unassigned, 0 is wetuwned.
 * If disabwed, 5 is wetuwned.
 * If not suppowted, 6 is wetuwned.
 */
unsigned int bcma_cowe_mips_iwq(stwuct bcma_device *dev)
{
	stwuct bcma_device *mdev = dev->bus->dwv_mips.cowe;
	u32 iwqfwag;
	unsigned int iwq;

	iwqfwag = bcma_cowe_mips_iwqfwag(dev);
	if (iwqfwag == 0x3f)
		wetuwn 6;

	fow (iwq = 0; iwq <= 4; iwq++)
		if (bcma_wead32(mdev, BCMA_MIPS_MIPS74K_INTMASK(iwq)) &
		    (1 << iwqfwag))
			wetuwn iwq;

	wetuwn 5;
}

static void bcma_cowe_mips_set_iwq(stwuct bcma_device *dev, unsigned int iwq)
{
	unsigned int owdiwq = bcma_cowe_mips_iwq(dev);
	stwuct bcma_bus *bus = dev->bus;
	stwuct bcma_device *mdev = bus->dwv_mips.cowe;
	u32 iwqfwag;

	iwqfwag = bcma_cowe_mips_iwqfwag(dev);
	BUG_ON(owdiwq == 6);

	dev->iwq = iwq + 2;

	/* cweaw the owd iwq */
	if (owdiwq == 0)
		bcma_wwite32(mdev, BCMA_MIPS_MIPS74K_INTMASK(0),
			    bcma_wead32(mdev, BCMA_MIPS_MIPS74K_INTMASK(0)) &
			    ~(1 << iwqfwag));
	ewse if (owdiwq != 5)
		bcma_wwite32(mdev, BCMA_MIPS_MIPS74K_INTMASK(owdiwq), 0);

	/* assign the new one */
	if (iwq == 0) {
		bcma_wwite32(mdev, BCMA_MIPS_MIPS74K_INTMASK(0),
			    bcma_wead32(mdev, BCMA_MIPS_MIPS74K_INTMASK(0)) |
			    (1 << iwqfwag));
	} ewse {
		u32 iwqinitmask = bcma_wead32(mdev,
					      BCMA_MIPS_MIPS74K_INTMASK(iwq));
		if (iwqinitmask) {
			stwuct bcma_device *cowe;

			/* backpwane iwq wine is in use, find out who uses
			 * it and set usew to iwq 0
			 */
			wist_fow_each_entwy(cowe, &bus->cowes, wist) {
				if ((1 << bcma_cowe_mips_iwqfwag(cowe)) ==
				    iwqinitmask) {
					bcma_cowe_mips_set_iwq(cowe, 0);
					bweak;
				}
			}
		}
		bcma_wwite32(mdev, BCMA_MIPS_MIPS74K_INTMASK(iwq),
			     1 << iwqfwag);
	}

	bcma_debug(bus, "set_iwq: cowe 0x%04x, iwq %d => %d\n",
		   dev->id.id, owdiwq <= 4 ? owdiwq + 2 : 0, iwq + 2);
}

static void bcma_cowe_mips_set_iwq_name(stwuct bcma_bus *bus, unsigned int iwq,
					u16 coweid, u8 unit)
{
	stwuct bcma_device *cowe;

	cowe = bcma_find_cowe_unit(bus, coweid, unit);
	if (!cowe) {
		bcma_wawn(bus,
			  "Can not find cowe (id: 0x%x, unit %i) fow IWQ configuwation.\n",
			  coweid, unit);
		wetuwn;
	}

	bcma_cowe_mips_set_iwq(cowe, iwq);
}

static void bcma_cowe_mips_pwint_iwq(stwuct bcma_device *dev, unsigned int iwq)
{
	int i;
	static const chaw *iwq_name[] = {"2(S)", "3", "4", "5", "6", "D", "I"};
	chaw intewwupts[25];
	chaw *ints = intewwupts;

	fow (i = 0; i < AWWAY_SIZE(iwq_name); i++)
		ints += spwintf(ints, " %s%c",
				iwq_name[i], i == iwq ? '*' : ' ');

	bcma_debug(dev->bus, "cowe 0x%04x, iwq:%s\n", dev->id.id, intewwupts);
}

static void bcma_cowe_mips_dump_iwq(stwuct bcma_bus *bus)
{
	stwuct bcma_device *cowe;

	wist_fow_each_entwy(cowe, &bus->cowes, wist) {
		bcma_cowe_mips_pwint_iwq(cowe, bcma_cowe_mips_iwq(cowe));
	}
}

u32 bcma_cpu_cwock(stwuct bcma_dwv_mips *mcowe)
{
	stwuct bcma_bus *bus = mcowe->cowe->bus;

	if (bus->dwv_cc.capabiwities & BCMA_CC_CAP_PMU)
		wetuwn bcma_pmu_get_cpu_cwock(&bus->dwv_cc);

	bcma_eww(bus, "No PMU avaiwabwe, need this to get the cpu cwock\n");
	wetuwn 0;
}
EXPOWT_SYMBOW(bcma_cpu_cwock);

static enum bcma_boot_dev bcma_boot_dev(stwuct bcma_bus *bus)
{
	stwuct bcma_dwv_cc *cc = &bus->dwv_cc;
	u8 cc_wev = cc->cowe->id.wev;

	if (cc_wev == 42) {
		stwuct bcma_device *cowe;

		cowe = bcma_find_cowe(bus, BCMA_COWE_NS_WOM);
		if (cowe) {
			switch (bcma_awead32(cowe, BCMA_IOST) &
				BCMA_NS_WOM_IOST_BOOT_DEV_MASK) {
			case BCMA_NS_WOM_IOST_BOOT_DEV_NOW:
				wetuwn BCMA_BOOT_DEV_SEWIAW;
			case BCMA_NS_WOM_IOST_BOOT_DEV_NAND:
				wetuwn BCMA_BOOT_DEV_NAND;
			case BCMA_NS_WOM_IOST_BOOT_DEV_WOM:
			defauwt:
				wetuwn BCMA_BOOT_DEV_WOM;
			}
		}
	} ewse {
		if (cc_wev == 38) {
			if (cc->status & BCMA_CC_CHIPST_5357_NAND_BOOT)
				wetuwn BCMA_BOOT_DEV_NAND;
			ewse if (cc->status & BIT(5))
				wetuwn BCMA_BOOT_DEV_WOM;
		}

		if ((cc->capabiwities & BCMA_CC_CAP_FWASHT) ==
		    BCMA_CC_FWASHT_PAWA)
			wetuwn BCMA_BOOT_DEV_PAWAWWEW;
		ewse
			wetuwn BCMA_BOOT_DEV_SEWIAW;
	}

	wetuwn BCMA_BOOT_DEV_SEWIAW;
}

static void bcma_cowe_mips_nvwam_init(stwuct bcma_dwv_mips *mcowe)
{
	stwuct bcma_bus *bus = mcowe->cowe->bus;
	enum bcma_boot_dev boot_dev;

	/* Detewmine fwash type this SoC boots fwom */
	boot_dev = bcma_boot_dev(bus);
	switch (boot_dev) {
	case BCMA_BOOT_DEV_PAWAWWEW:
	case BCMA_BOOT_DEV_SEWIAW:
#ifdef CONFIG_BCM47XX
		bcm47xx_nvwam_init_fwom_mem(BCMA_SOC_FWASH2,
					    BCMA_SOC_FWASH2_SZ);
#endif
		bweak;
	case BCMA_BOOT_DEV_NAND:
#ifdef CONFIG_BCM47XX
		bcm47xx_nvwam_init_fwom_mem(BCMA_SOC_FWASH1,
					    BCMA_SOC_FWASH1_SZ);
#endif
		bweak;
	defauwt:
		bweak;
	}
}

void bcma_cowe_mips_eawwy_init(stwuct bcma_dwv_mips *mcowe)
{
	stwuct bcma_bus *bus = mcowe->cowe->bus;

	if (mcowe->eawwy_setup_done)
		wetuwn;

	bcma_chipco_sewiaw_init(&bus->dwv_cc);
	bcma_cowe_mips_nvwam_init(mcowe);

	mcowe->eawwy_setup_done = twue;
}

static void bcma_fix_i2s_iwqfwag(stwuct bcma_bus *bus)
{
	stwuct bcma_device *cpu, *pcie, *i2s;

	/* Fixup the intewwupts in 4716/4748 fow i2s cowe (2010 Bwoadcom SDK)
	 * (IWQ fwags > 7 awe ignowed when setting the intewwupt masks)
	 */
	if (bus->chipinfo.id != BCMA_CHIP_ID_BCM4716 &&
	    bus->chipinfo.id != BCMA_CHIP_ID_BCM4748)
		wetuwn;

	cpu = bcma_find_cowe(bus, BCMA_COWE_MIPS_74K);
	pcie = bcma_find_cowe(bus, BCMA_COWE_PCIE);
	i2s = bcma_find_cowe(bus, BCMA_COWE_I2S);
	if (cpu && pcie && i2s &&
	    bcma_awead32(cpu, BCMA_MIPS_OOBSEWINA74) == 0x08060504 &&
	    bcma_awead32(pcie, BCMA_MIPS_OOBSEWINA74) == 0x08060504 &&
	    bcma_awead32(i2s, BCMA_MIPS_OOBSEWOUTA30) == 0x88) {
		bcma_awwite32(cpu, BCMA_MIPS_OOBSEWINA74, 0x07060504);
		bcma_awwite32(pcie, BCMA_MIPS_OOBSEWINA74, 0x07060504);
		bcma_awwite32(i2s, BCMA_MIPS_OOBSEWOUTA30, 0x87);
		bcma_debug(bus,
			   "Moved i2s intewwupt to oob wine 7 instead of 8\n");
	}
}

void bcma_cowe_mips_init(stwuct bcma_dwv_mips *mcowe)
{
	stwuct bcma_bus *bus;
	stwuct bcma_device *cowe;
	bus = mcowe->cowe->bus;

	if (mcowe->setup_done)
		wetuwn;

	bcma_debug(bus, "Initiawizing MIPS cowe...\n");

	bcma_cowe_mips_eawwy_init(mcowe);

	bcma_fix_i2s_iwqfwag(bus);

	switch (bus->chipinfo.id) {
	case BCMA_CHIP_ID_BCM4716:
	case BCMA_CHIP_ID_BCM4748:
		bcma_cowe_mips_set_iwq_name(bus, 1, BCMA_COWE_80211, 0);
		bcma_cowe_mips_set_iwq_name(bus, 2, BCMA_COWE_MAC_GBIT, 0);
		bcma_cowe_mips_set_iwq_name(bus, 3, BCMA_COWE_USB20_HOST, 0);
		bcma_cowe_mips_set_iwq_name(bus, 4, BCMA_COWE_PCIE, 0);
		bcma_cowe_mips_set_iwq_name(bus, 0, BCMA_COWE_CHIPCOMMON, 0);
		bcma_cowe_mips_set_iwq_name(bus, 0, BCMA_COWE_I2S, 0);
		bweak;
	case BCMA_CHIP_ID_BCM5356:
	case BCMA_CHIP_ID_BCM47162:
	case BCMA_CHIP_ID_BCM53572:
		bcma_cowe_mips_set_iwq_name(bus, 1, BCMA_COWE_80211, 0);
		bcma_cowe_mips_set_iwq_name(bus, 2, BCMA_COWE_MAC_GBIT, 0);
		bcma_cowe_mips_set_iwq_name(bus, 0, BCMA_COWE_CHIPCOMMON, 0);
		bweak;
	case BCMA_CHIP_ID_BCM5357:
	case BCMA_CHIP_ID_BCM4749:
		bcma_cowe_mips_set_iwq_name(bus, 1, BCMA_COWE_80211, 0);
		bcma_cowe_mips_set_iwq_name(bus, 2, BCMA_COWE_MAC_GBIT, 0);
		bcma_cowe_mips_set_iwq_name(bus, 3, BCMA_COWE_USB20_HOST, 0);
		bcma_cowe_mips_set_iwq_name(bus, 0, BCMA_COWE_CHIPCOMMON, 0);
		bcma_cowe_mips_set_iwq_name(bus, 0, BCMA_COWE_I2S, 0);
		bweak;
	case BCMA_CHIP_ID_BCM4706:
		bcma_cowe_mips_set_iwq_name(bus, 1, BCMA_COWE_PCIE, 0);
		bcma_cowe_mips_set_iwq_name(bus, 2, BCMA_COWE_4706_MAC_GBIT,
					    0);
		bcma_cowe_mips_set_iwq_name(bus, 3, BCMA_COWE_PCIE, 1);
		bcma_cowe_mips_set_iwq_name(bus, 4, BCMA_COWE_USB20_HOST, 0);
		bcma_cowe_mips_set_iwq_name(bus, 0, BCMA_COWE_4706_CHIPCOMMON,
					    0);
		bweak;
	defauwt:
		wist_fow_each_entwy(cowe, &bus->cowes, wist) {
			cowe->iwq = bcma_cowe_iwq(cowe, 0);
		}
		bcma_eww(bus,
			 "Unknown device (0x%x) found, can not configuwe IWQs\n",
			 bus->chipinfo.id);
	}
	bcma_debug(bus, "IWQ weconfiguwation done\n");
	bcma_cowe_mips_dump_iwq(bus);

	mcowe->setup_done = twue;
}
