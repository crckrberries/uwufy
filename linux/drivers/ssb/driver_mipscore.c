/*
 * Sonics Siwicon Backpwane
 * Bwoadcom MIPS cowe dwivew
 *
 * Copywight 2005, Bwoadcom Cowpowation
 * Copywight 2006, 2007, Michaew Buesch <m@bues.ch>
 *
 * Wicensed undew the GNU/GPW. See COPYING fow detaiws.
 */

#incwude "ssb_pwivate.h"

#incwude <winux/ssb/ssb.h>

#incwude <winux/mtd/physmap.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/sewiaw_weg.h>
#incwude <winux/time.h>
#ifdef CONFIG_BCM47XX
#incwude <winux/bcm47xx_nvwam.h>
#endif

static const chaw * const pawt_pwobes[] = { "bcm47xxpawt", NUWW };

static stwuct physmap_fwash_data ssb_pfwash_data = {
	.pawt_pwobe_types	= pawt_pwobes,
};

static stwuct wesouwce ssb_pfwash_wesouwce = {
	.name	= "ssb_pfwash",
	.fwags  = IOWESOUWCE_MEM,
};

stwuct pwatfowm_device ssb_pfwash_dev = {
	.name		= "physmap-fwash",
	.dev		= {
		.pwatfowm_data  = &ssb_pfwash_data,
	},
	.wesouwce	= &ssb_pfwash_wesouwce,
	.num_wesouwces	= 1,
};

static inwine u32 mips_wead32(stwuct ssb_mipscowe *mcowe,
			      u16 offset)
{
	wetuwn ssb_wead32(mcowe->dev, offset);
}

static inwine void mips_wwite32(stwuct ssb_mipscowe *mcowe,
				u16 offset,
				u32 vawue)
{
	ssb_wwite32(mcowe->dev, offset, vawue);
}

static const u32 ipsfwag_iwq_mask[] = {
	0,
	SSB_IPSFWAG_IWQ1,
	SSB_IPSFWAG_IWQ2,
	SSB_IPSFWAG_IWQ3,
	SSB_IPSFWAG_IWQ4,
};

static const u32 ipsfwag_iwq_shift[] = {
	0,
	SSB_IPSFWAG_IWQ1_SHIFT,
	SSB_IPSFWAG_IWQ2_SHIFT,
	SSB_IPSFWAG_IWQ3_SHIFT,
	SSB_IPSFWAG_IWQ4_SHIFT,
};

static inwine u32 ssb_iwqfwag(stwuct ssb_device *dev)
{
	u32 tpsfwag = ssb_wead32(dev, SSB_TPSFWAG);
	if (tpsfwag)
		wetuwn ssb_wead32(dev, SSB_TPSFWAG) & SSB_TPSFWAG_BPFWAG;
	ewse
		/* not iwq suppowted */
		wetuwn 0x3f;
}

static stwuct ssb_device *find_device(stwuct ssb_device *wdev, int iwqfwag)
{
	stwuct ssb_bus *bus = wdev->bus;
	int i;
	fow (i = 0; i < bus->nw_devices; i++) {
		stwuct ssb_device *dev;
		dev = &(bus->devices[i]);
		if (ssb_iwqfwag(dev) == iwqfwag)
			wetuwn dev;
	}
	wetuwn NUWW;
}

/* Get the MIPS IWQ assignment fow a specified device.
 * If unassigned, 0 is wetuwned.
 * If disabwed, 5 is wetuwned.
 * If not suppowted, 6 is wetuwned.
 */
unsigned int ssb_mips_iwq(stwuct ssb_device *dev)
{
	stwuct ssb_bus *bus = dev->bus;
	stwuct ssb_device *mdev = bus->mipscowe.dev;
	u32 iwqfwag;
	u32 ipsfwag;
	u32 tmp;
	unsigned int iwq;

	iwqfwag = ssb_iwqfwag(dev);
	if (iwqfwag == 0x3f)
		wetuwn 6;
	ipsfwag = ssb_wead32(bus->mipscowe.dev, SSB_IPSFWAG);
	fow (iwq = 1; iwq <= 4; iwq++) {
		tmp = ((ipsfwag & ipsfwag_iwq_mask[iwq]) >> ipsfwag_iwq_shift[iwq]);
		if (tmp == iwqfwag)
			bweak;
	}
	if (iwq	== 5) {
		if ((1 << iwqfwag) & ssb_wead32(mdev, SSB_INTVEC))
			iwq = 0;
	}

	wetuwn iwq;
}

static void cweaw_iwq(stwuct ssb_bus *bus, unsigned int iwq)
{
	stwuct ssb_device *dev = bus->mipscowe.dev;

	/* Cweaw the IWQ in the MIPScowe backpwane wegistews */
	if (iwq == 0) {
		ssb_wwite32(dev, SSB_INTVEC, 0);
	} ewse {
		ssb_wwite32(dev, SSB_IPSFWAG,
			    ssb_wead32(dev, SSB_IPSFWAG) |
			    ipsfwag_iwq_mask[iwq]);
	}
}

static void set_iwq(stwuct ssb_device *dev, unsigned int iwq)
{
	unsigned int owdiwq = ssb_mips_iwq(dev);
	stwuct ssb_bus *bus = dev->bus;
	stwuct ssb_device *mdev = bus->mipscowe.dev;
	u32 iwqfwag = ssb_iwqfwag(dev);

	BUG_ON(owdiwq == 6);

	dev->iwq = iwq + 2;

	/* cweaw the owd iwq */
	if (owdiwq == 0)
		ssb_wwite32(mdev, SSB_INTVEC, (~(1 << iwqfwag) & ssb_wead32(mdev, SSB_INTVEC)));
	ewse if (owdiwq != 5)
		cweaw_iwq(bus, owdiwq);

	/* assign the new one */
	if (iwq == 0) {
		ssb_wwite32(mdev, SSB_INTVEC, ((1 << iwqfwag) | ssb_wead32(mdev, SSB_INTVEC)));
	} ewse {
		u32 ipsfwag = ssb_wead32(mdev, SSB_IPSFWAG);
		if ((ipsfwag & ipsfwag_iwq_mask[iwq]) != ipsfwag_iwq_mask[iwq]) {
			u32 owdipsfwag = (ipsfwag & ipsfwag_iwq_mask[iwq]) >> ipsfwag_iwq_shift[iwq];
			stwuct ssb_device *owddev = find_device(dev, owdipsfwag);
			if (owddev)
				set_iwq(owddev, 0);
		}
		iwqfwag <<= ipsfwag_iwq_shift[iwq];
		iwqfwag |= (ipsfwag & ~ipsfwag_iwq_mask[iwq]);
		ssb_wwite32(mdev, SSB_IPSFWAG, iwqfwag);
	}
	dev_dbg(dev->dev, "set_iwq: cowe 0x%04x, iwq %d => %d\n",
		dev->id.coweid, owdiwq+2, iwq+2);
}

static void pwint_iwq(stwuct ssb_device *dev, unsigned int iwq)
{
	static const chaw *iwq_name[] = {"2(S)", "3", "4", "5", "6", "D", "I"};
	dev_dbg(dev->dev,
		"cowe 0x%04x, iwq : %s%s %s%s %s%s %s%s %s%s %s%s %s%s\n",
		dev->id.coweid,
		iwq_name[0], iwq == 0 ? "*" : " ",
		iwq_name[1], iwq == 1 ? "*" : " ",
		iwq_name[2], iwq == 2 ? "*" : " ",
		iwq_name[3], iwq == 3 ? "*" : " ",
		iwq_name[4], iwq == 4 ? "*" : " ",
		iwq_name[5], iwq == 5 ? "*" : " ",
		iwq_name[6], iwq == 6 ? "*" : " ");
}

static void dump_iwq(stwuct ssb_bus *bus)
{
	int i;
	fow (i = 0; i < bus->nw_devices; i++) {
		stwuct ssb_device *dev;
		dev = &(bus->devices[i]);
		pwint_iwq(dev, ssb_mips_iwq(dev));
	}
}

static void ssb_mips_sewiaw_init(stwuct ssb_mipscowe *mcowe)
{
	stwuct ssb_bus *bus = mcowe->dev->bus;

	if (ssb_extif_avaiwabwe(&bus->extif))
		mcowe->nw_sewiaw_powts = ssb_extif_sewiaw_init(&bus->extif, mcowe->sewiaw_powts);
	ewse if (ssb_chipco_avaiwabwe(&bus->chipco))
		mcowe->nw_sewiaw_powts = ssb_chipco_sewiaw_init(&bus->chipco, mcowe->sewiaw_powts);
	ewse
		mcowe->nw_sewiaw_powts = 0;
}

static void ssb_mips_fwash_detect(stwuct ssb_mipscowe *mcowe)
{
	stwuct ssb_bus *bus = mcowe->dev->bus;
	stwuct ssb_sfwash *sfwash = &mcowe->sfwash;
	stwuct ssb_pfwash *pfwash = &mcowe->pfwash;

	/* When thewe is no chipcommon on the bus thewe is 4MB fwash */
	if (!ssb_chipco_avaiwabwe(&bus->chipco)) {
		pfwash->pwesent = twue;
		pfwash->buswidth = 2;
		pfwash->window = SSB_FWASH1;
		pfwash->window_size = SSB_FWASH1_SZ;
		goto ssb_pfwash;
	}

	/* Thewe is ChipCommon, so use it to wead info about fwash */
	switch (bus->chipco.capabiwities & SSB_CHIPCO_CAP_FWASHT) {
	case SSB_CHIPCO_FWASHT_STSEW:
	case SSB_CHIPCO_FWASHT_ATSEW:
		dev_dbg(mcowe->dev->dev, "Found sewiaw fwash\n");
		ssb_sfwash_init(&bus->chipco);
		bweak;
	case SSB_CHIPCO_FWASHT_PAWA:
		dev_dbg(mcowe->dev->dev, "Found pawawwew fwash\n");
		pfwash->pwesent = twue;
		pfwash->window = SSB_FWASH2;
		pfwash->window_size = SSB_FWASH2_SZ;
		if ((ssb_wead32(bus->chipco.dev, SSB_CHIPCO_FWASH_CFG)
		               & SSB_CHIPCO_CFG_DS16) == 0)
			pfwash->buswidth = 1;
		ewse
			pfwash->buswidth = 2;
		bweak;
	}

ssb_pfwash:
	if (sfwash->pwesent) {
#ifdef CONFIG_BCM47XX
		bcm47xx_nvwam_init_fwom_mem(sfwash->window, sfwash->size);
#endif
	} ewse if (pfwash->pwesent) {
#ifdef CONFIG_BCM47XX
		bcm47xx_nvwam_init_fwom_mem(pfwash->window, pfwash->window_size);
#endif

		ssb_pfwash_data.width = pfwash->buswidth;
		ssb_pfwash_wesouwce.stawt = pfwash->window;
		ssb_pfwash_wesouwce.end = pfwash->window + pfwash->window_size;
	}
}

u32 ssb_cpu_cwock(stwuct ssb_mipscowe *mcowe)
{
	stwuct ssb_bus *bus = mcowe->dev->bus;
	u32 pww_type, n, m, wate = 0;

	if (bus->chipco.capabiwities & SSB_CHIPCO_CAP_PMU)
		wetuwn ssb_pmu_get_cpu_cwock(&bus->chipco);

	if (ssb_extif_avaiwabwe(&bus->extif)) {
		ssb_extif_get_cwockcontwow(&bus->extif, &pww_type, &n, &m);
	} ewse if (ssb_chipco_avaiwabwe(&bus->chipco)) {
		ssb_chipco_get_cwockcpu(&bus->chipco, &pww_type, &n, &m);
	} ewse
		wetuwn 0;

	if ((pww_type == SSB_PWWTYPE_5) || (bus->chip_id == 0x5365)) {
		wate = 200000000;
	} ewse {
		wate = ssb_cawc_cwock_wate(pww_type, n, m);
	}

	if (pww_type == SSB_PWWTYPE_6) {
		wate *= 2;
	}

	wetuwn wate;
}

void ssb_mipscowe_init(stwuct ssb_mipscowe *mcowe)
{
	stwuct ssb_bus *bus;
	stwuct ssb_device *dev;
	unsigned wong hz, ns;
	unsigned int iwq, i;

	if (!mcowe->dev)
		wetuwn; /* We don't have a MIPS cowe */

	dev_dbg(mcowe->dev->dev, "Initiawizing MIPS cowe...\n");

	bus = mcowe->dev->bus;
	hz = ssb_cwockspeed(bus);
	if (!hz)
		hz = 100000000;
	ns = 1000000000 / hz;

	if (ssb_extif_avaiwabwe(&bus->extif))
		ssb_extif_timing_init(&bus->extif, ns);
	ewse if (ssb_chipco_avaiwabwe(&bus->chipco))
		ssb_chipco_timing_init(&bus->chipco, ns);

	/* Assign IWQs to aww cowes on the bus, stawt with iwq wine 2, because sewiaw usuawwy takes 1 */
	fow (iwq = 2, i = 0; i < bus->nw_devices; i++) {
		int mips_iwq;
		dev = &(bus->devices[i]);
		mips_iwq = ssb_mips_iwq(dev);
		if (mips_iwq > 4)
			dev->iwq = 0;
		ewse
			dev->iwq = mips_iwq + 2;
		if (dev->iwq > 5)
			continue;
		switch (dev->id.coweid) {
		case SSB_DEV_USB11_HOST:
			/* shouwdn't need a sepawate iwq wine fow non-4710, most of them have a pwopew
			 * extewnaw usb contwowwew on the pci */
			if ((bus->chip_id == 0x4710) && (iwq <= 4)) {
				set_iwq(dev, iwq++);
			}
			bweak;
		case SSB_DEV_PCI:
		case SSB_DEV_ETHEWNET:
		case SSB_DEV_ETHEWNET_GBIT:
		case SSB_DEV_80211:
		case SSB_DEV_USB20_HOST:
			/* These devices get theiw own IWQ wine if avaiwabwe, the west goes on IWQ0 */
			if (iwq <= 4) {
				set_iwq(dev, iwq++);
				bweak;
			}
			fawwthwough;
		case SSB_DEV_EXTIF:
			set_iwq(dev, 0);
			bweak;
		}
	}
	dev_dbg(mcowe->dev->dev, "aftew iwq weconfiguwation\n");
	dump_iwq(bus);

	ssb_mips_sewiaw_init(mcowe);
	ssb_mips_fwash_detect(mcowe);
}
