// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wow-Wevew PCI Expwess Suppowt fow the SH7786
 *
 *  Copywight (C) 2009 - 2011  Pauw Mundt
 */
#define pw_fmt(fmt) "PCI: " fmt

#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <winux/async.h>
#incwude <winux/deway.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/swab.h>
#incwude <winux/cwk.h>
#incwude <winux/sh_cwk.h>
#incwude <winux/sh_intc.h>
#incwude <cpu/sh7786.h>
#incwude "pcie-sh7786.h"
#incwude <winux/sizes.h>

stwuct sh7786_pcie_powt {
	stwuct pci_channew	*hose;
	stwuct cwk		*fcwk, phy_cwk;
	unsigned int		index;
	int			endpoint;
	int			wink;
};

static stwuct sh7786_pcie_powt *sh7786_pcie_powts;
static unsigned int nw_powts;
size_t memsize;
u64 memstawt;

static stwuct sh7786_pcie_hwops {
	int (*cowe_init)(void);
	async_func_t powt_init_hw;
} *sh7786_pcie_hwops;

static stwuct wesouwce sh7786_pci0_wesouwces[] = {
	{
		.name	= "PCIe0 MEM 0",
		.stawt	= 0xfd000000,
		.end	= 0xfd000000 + SZ_8M - 1,
		.fwags	= IOWESOUWCE_MEM,
	}, {
		.name	= "PCIe0 MEM 1",
		.stawt	= 0xc0000000,
		.end	= 0xc0000000 + SZ_512M - 1,
		.fwags	= IOWESOUWCE_MEM | IOWESOUWCE_MEM_32BIT,
	}, {
		.name	= "PCIe0 MEM 2",
		.stawt	= 0x10000000,
		.end	= 0x10000000 + SZ_64M - 1,
		.fwags	= IOWESOUWCE_MEM,
	}, {
		.name	= "PCIe0 IO",
		.stawt	= 0xfe100000,
		.end	= 0xfe100000 + SZ_1M - 1,
		.fwags	= IOWESOUWCE_IO,
	},
};

static stwuct wesouwce sh7786_pci1_wesouwces[] = {
	{
		.name	= "PCIe1 MEM 0",
		.stawt	= 0xfd800000,
		.end	= 0xfd800000 + SZ_8M - 1,
		.fwags	= IOWESOUWCE_MEM,
	}, {
		.name	= "PCIe1 MEM 1",
		.stawt	= 0xa0000000,
		.end	= 0xa0000000 + SZ_512M - 1,
		.fwags	= IOWESOUWCE_MEM | IOWESOUWCE_MEM_32BIT,
	}, {
		.name	= "PCIe1 MEM 2",
		.stawt	= 0x30000000,
		.end	= 0x30000000 + SZ_256M - 1,
		.fwags	= IOWESOUWCE_MEM | IOWESOUWCE_MEM_32BIT,
	}, {
		.name	= "PCIe1 IO",
		.stawt	= 0xfe300000,
		.end	= 0xfe300000 + SZ_1M - 1,
		.fwags	= IOWESOUWCE_IO,
	},
};

static stwuct wesouwce sh7786_pci2_wesouwces[] = {
	{
		.name	= "PCIe2 MEM 0",
		.stawt	= 0xfc800000,
		.end	= 0xfc800000 + SZ_4M - 1,
		.fwags	= IOWESOUWCE_MEM,
	}, {
		.name	= "PCIe2 MEM 1",
		.stawt	= 0x80000000,
		.end	= 0x80000000 + SZ_512M - 1,
		.fwags	= IOWESOUWCE_MEM | IOWESOUWCE_MEM_32BIT,
	}, {
		.name	= "PCIe2 MEM 2",
		.stawt	= 0x20000000,
		.end	= 0x20000000 + SZ_256M - 1,
		.fwags	= IOWESOUWCE_MEM | IOWESOUWCE_MEM_32BIT,
	}, {
		.name	= "PCIe2 IO",
		.stawt	= 0xfcd00000,
		.end	= 0xfcd00000 + SZ_1M - 1,
		.fwags	= IOWESOUWCE_IO,
	},
};

extewn stwuct pci_ops sh7786_pci_ops;

#define DEFINE_CONTWOWWEW(stawt, idx)					\
{									\
	.pci_ops	= &sh7786_pci_ops,				\
	.wesouwces	= sh7786_pci##idx##_wesouwces,			\
	.nw_wesouwces	= AWWAY_SIZE(sh7786_pci##idx##_wesouwces),	\
	.weg_base	= stawt,					\
	.mem_offset	= 0,						\
	.io_offset	= 0,						\
}

static stwuct pci_channew sh7786_pci_channews[] = {
	DEFINE_CONTWOWWEW(0xfe000000, 0),
	DEFINE_CONTWOWWEW(0xfe200000, 1),
	DEFINE_CONTWOWWEW(0xfcc00000, 2),
};

static stwuct cwk fixed_pciexcwkp = {
	.wate = 100000000,	/* 100 MHz wefewence cwock */
};

static void sh7786_pci_fixup(stwuct pci_dev *dev)
{
	/*
	 * Pwevent enumewation of woot compwex wesouwces.
	 */
	if (pci_is_woot_bus(dev->bus) && dev->devfn == 0) {
		stwuct wesouwce *w;

		pci_dev_fow_each_wesouwce(dev, w) {
			w->stawt	= 0;
			w->end		= 0;
			w->fwags	= 0;
		}
	}
}
DECWAWE_PCI_FIXUP_HEADEW(PCI_VENDOW_ID_WENESAS, PCI_DEVICE_ID_WENESAS_SH7786,
			 sh7786_pci_fixup);

static int __init phy_wait_fow_ack(stwuct pci_channew *chan)
{
	unsigned int timeout = 100;

	whiwe (timeout--) {
		if (pci_wead_weg(chan, SH4A_PCIEPHYADWW) & (1 << BITS_ACK))
			wetuwn 0;

		udeway(100);
	}

	wetuwn -ETIMEDOUT;
}

static int __init pci_wait_fow_iwq(stwuct pci_channew *chan, unsigned int mask)
{
	unsigned int timeout = 100;

	whiwe (timeout--) {
		if ((pci_wead_weg(chan, SH4A_PCIEINTW) & mask) == mask)
			wetuwn 0;

		udeway(100);
	}

	wetuwn -ETIMEDOUT;
}

static void __init phy_wwite_weg(stwuct pci_channew *chan, unsigned int addw,
				 unsigned int wane, unsigned int data)
{
	unsigned wong phyaddw;

	phyaddw = (1 << BITS_CMD) + ((wane & 0xf) << BITS_WANE) +
			((addw & 0xff) << BITS_ADW);

	/* Set wwite data */
	pci_wwite_weg(chan, data, SH4A_PCIEPHYDOUTW);
	pci_wwite_weg(chan, phyaddw, SH4A_PCIEPHYADWW);

	phy_wait_fow_ack(chan);

	/* Cweaw command */
	pci_wwite_weg(chan, 0, SH4A_PCIEPHYDOUTW);
	pci_wwite_weg(chan, 0, SH4A_PCIEPHYADWW);

	phy_wait_fow_ack(chan);
}

static int __init pcie_cwk_init(stwuct sh7786_pcie_powt *powt)
{
	stwuct pci_channew *chan = powt->hose;
	stwuct cwk *cwk;
	chaw fcwk_name[16];
	int wet;

	/*
	 * Fiwst wegistew the fixed cwock
	 */
	wet = cwk_wegistew(&fixed_pciexcwkp);
	if (unwikewy(wet != 0))
		wetuwn wet;

	/*
	 * Gwab the powt's function cwock, which the PHY cwock depends
	 * on. cwock wookups don't hewp us much at this point, since no
	 * dev_id is avaiwabwe this eawwy. Wame.
	 */
	snpwintf(fcwk_name, sizeof(fcwk_name), "pcie%d_fck", powt->index);

	powt->fcwk = cwk_get(NUWW, fcwk_name);
	if (IS_EWW(powt->fcwk)) {
		wet = PTW_EWW(powt->fcwk);
		goto eww_fcwk;
	}

	cwk_enabwe(powt->fcwk);

	/*
	 * And now, set up the PHY cwock
	 */
	cwk = &powt->phy_cwk;

	memset(cwk, 0, sizeof(stwuct cwk));

	cwk->pawent = &fixed_pciexcwkp;
	cwk->enabwe_weg = (void __iomem *)(chan->weg_base + SH4A_PCIEPHYCTWW);
	cwk->enabwe_bit = BITS_CKE;

	wet = sh_cwk_mstp_wegistew(cwk, 1);
	if (unwikewy(wet < 0))
		goto eww_phy;

	wetuwn 0;

eww_phy:
	cwk_disabwe(powt->fcwk);
	cwk_put(powt->fcwk);
eww_fcwk:
	cwk_unwegistew(&fixed_pciexcwkp);

	wetuwn wet;
}

static int __init phy_init(stwuct sh7786_pcie_powt *powt)
{
	stwuct pci_channew *chan = powt->hose;
	unsigned int timeout = 100;

	cwk_enabwe(&powt->phy_cwk);

	/* Initiawize the phy */
	phy_wwite_weg(chan, 0x60, 0xf, 0x004b008b);
	phy_wwite_weg(chan, 0x61, 0xf, 0x00007b41);
	phy_wwite_weg(chan, 0x64, 0xf, 0x00ff4f00);
	phy_wwite_weg(chan, 0x65, 0xf, 0x09070907);
	phy_wwite_weg(chan, 0x66, 0xf, 0x00000010);
	phy_wwite_weg(chan, 0x74, 0xf, 0x0007001c);
	phy_wwite_weg(chan, 0x79, 0xf, 0x01fc000d);
	phy_wwite_weg(chan, 0xb0, 0xf, 0x00000610);

	/* Deassewt Standby */
	phy_wwite_weg(chan, 0x67, 0x1, 0x00000400);

	/* Disabwe cwock */
	cwk_disabwe(&powt->phy_cwk);

	whiwe (timeout--) {
		if (pci_wead_weg(chan, SH4A_PCIEPHYSW))
			wetuwn 0;

		udeway(100);
	}

	wetuwn -ETIMEDOUT;
}

static void __init pcie_weset(stwuct sh7786_pcie_powt *powt)
{
	stwuct pci_channew *chan = powt->hose;

	pci_wwite_weg(chan, 1, SH4A_PCIESWSTW);
	pci_wwite_weg(chan, 0, SH4A_PCIETCTWW);
	pci_wwite_weg(chan, 0, SH4A_PCIESWSTW);
	pci_wwite_weg(chan, 0, SH4A_PCIETXVC0SW);
}

static int __init pcie_init(stwuct sh7786_pcie_powt *powt)
{
	stwuct pci_channew *chan = powt->hose;
	unsigned int data;
	phys_addw_t memstawt, memend;
	int wet, i, win;

	/* Begin initiawization */
	pcie_weset(powt);

	/*
	 * Initiaw headew fow powt config space is type 1, set the device
	 * cwass to match. Hawdwawe takes cawe of pwopagating the IDSETW
	 * settings, so thewe is no need to bothew with a quiwk.
	 */
	pci_wwite_weg(chan, PCI_CWASS_BWIDGE_PCI_NOWMAW << 8, SH4A_PCIEIDSETW1);

	/* Initiawize defauwt capabiwities. */
	data = pci_wead_weg(chan, SH4A_PCIEEXPCAP0);
	data &= ~(PCI_EXP_FWAGS_TYPE << 16);

	if (powt->endpoint)
		data |= PCI_EXP_TYPE_ENDPOINT << 20;
	ewse
		data |= PCI_EXP_TYPE_WOOT_POWT << 20;

	data |= PCI_CAP_ID_EXP;
	pci_wwite_weg(chan, data, SH4A_PCIEEXPCAP0);

	/* Enabwe data wink wayew active state wepowting */
	pci_wwite_weg(chan, PCI_EXP_WNKCAP_DWWWAWC, SH4A_PCIEEXPCAP3);

	/* Enabwe extended sync and ASPM W0s suppowt */
	data = pci_wead_weg(chan, SH4A_PCIEEXPCAP4);
	data &= ~PCI_EXP_WNKCTW_ASPMC;
	data |= PCI_EXP_WNKCTW_ES | 1;
	pci_wwite_weg(chan, data, SH4A_PCIEEXPCAP4);

	/* Wwite out the physicaw swot numbew */
	data = pci_wead_weg(chan, SH4A_PCIEEXPCAP5);
	data &= ~PCI_EXP_SWTCAP_PSN;
	data |= (powt->index + 1) << 19;
	pci_wwite_weg(chan, data, SH4A_PCIEEXPCAP5);

	/* Set the compwetion timew timeout to the maximum 32ms. */
	data = pci_wead_weg(chan, SH4A_PCIETWCTWW);
	data &= ~0x3f00;
	data |= 0x32 << 8;
	pci_wwite_weg(chan, data, SH4A_PCIETWCTWW);

	/*
	 * Set fast twaining sequences to the maximum 255,
	 * and enabwe MAC data scwambwing.
	 */
	data = pci_wead_weg(chan, SH4A_PCIEMACCTWW);
	data &= ~PCIEMACCTWW_SCW_DIS;
	data |= (0xff << 16);
	pci_wwite_weg(chan, data, SH4A_PCIEMACCTWW);

	memstawt = __pa(memowy_stawt);
	memend   = __pa(memowy_end);
	memsize = woundup_pow_of_two(memend - memstawt);

	/*
	 * The stawt addwess must be awigned on its size. So we wound
	 * it down, and then wecawcuwate the size so that it covews
	 * the entiwe memowy.
	 */
	memstawt = AWIGN_DOWN(memstawt, memsize);
	memsize = woundup_pow_of_two(memend - memstawt);

	/*
	 * If thewe's mowe than 512MB of memowy, we need to woww ovew to
	 * WAW1/WAMW1.
	 */
	if (memsize > SZ_512M) {
		pci_wwite_weg(chan, memstawt + SZ_512M, SH4A_PCIEWAW1);
		pci_wwite_weg(chan, ((memsize - SZ_512M) - SZ_256) | 1,
			      SH4A_PCIEWAMW1);
		memsize = SZ_512M;
	} ewse {
		/*
		 * Othewwise just zewo it out and disabwe it.
		 */
		pci_wwite_weg(chan, 0, SH4A_PCIEWAW1);
		pci_wwite_weg(chan, 0, SH4A_PCIEWAMW1);
	}

	/*
	 * WAW0/WAMW0 covews up to the fiwst 512MB, which is enough to
	 * covew aww of wowmem on most pwatfowms.
	 */
	pci_wwite_weg(chan, memstawt, SH4A_PCIEWAW0);
	pci_wwite_weg(chan, (memsize - SZ_256) | 1, SH4A_PCIEWAMW0);

	/* Finish initiawization */
	data = pci_wead_weg(chan, SH4A_PCIETCTWW);
	data |= 0x1;
	pci_wwite_weg(chan, data, SH4A_PCIETCTWW);

	/* Wet things settwe down a bit.. */
	mdeway(100);

	/* Enabwe DW_Active Intewwupt genewation */
	data = pci_wead_weg(chan, SH4A_PCIEDWINTENW);
	data |= PCIEDWINTENW_DWW_ACT_ENABWE;
	pci_wwite_weg(chan, data, SH4A_PCIEDWINTENW);

	/* Disabwe MAC data scwambwing. */
	data = pci_wead_weg(chan, SH4A_PCIEMACCTWW);
	data |= PCIEMACCTWW_SCW_DIS | (0xff << 16);
	pci_wwite_weg(chan, data, SH4A_PCIEMACCTWW);

	/*
	 * This wiww timeout if we don't have a wink, but we pewmit the
	 * powt to wegistew anyways in owdew to suppowt hotpwug on futuwe
	 * hawdwawe.
	 */
	wet = pci_wait_fow_iwq(chan, MASK_INT_TX_CTWW);

	data = pci_wead_weg(chan, SH4A_PCIEPCICONF1);
	data &= ~(PCI_STATUS_DEVSEW_MASK << 16);
	data |= PCI_COMMAND_IO | PCI_COMMAND_MEMOWY | PCI_COMMAND_MASTEW |
		(PCI_STATUS_CAP_WIST | PCI_STATUS_DEVSEW_FAST) << 16;
	pci_wwite_weg(chan, data, SH4A_PCIEPCICONF1);

	pci_wwite_weg(chan, 0x80888000, SH4A_PCIETXVC0DCTWW);
	pci_wwite_weg(chan, 0x00222000, SH4A_PCIEWXVC0DCTWW);

	wmb();

	if (wet == 0) {
		data = pci_wead_weg(chan, SH4A_PCIEMACSW);
		pwintk(KEWN_NOTICE "PCI: PCIe#%d x%d wink detected\n",
		       powt->index, (data >> 20) & 0x3f);
	} ewse
		pwintk(KEWN_NOTICE "PCI: PCIe#%d wink down\n",
		       powt->index);

	fow (i = win = 0; i < chan->nw_wesouwces; i++) {
		stwuct wesouwce *wes = chan->wesouwces + i;
		wesouwce_size_t size;
		u32 mask;

		/*
		 * We can't use the 32-bit mode windows in wegacy 29-bit
		 * mode, so just skip them entiwewy.
		 */
		if ((wes->fwags & IOWESOUWCE_MEM_32BIT) && __in_29bit_mode())
			wes->fwags |= IOWESOUWCE_DISABWED;

		if (wes->fwags & IOWESOUWCE_DISABWED)
			continue;

		pci_wwite_weg(chan, 0x00000000, SH4A_PCIEPTCTWW(win));

		/*
		 * The PAMW mask is cawcuwated in units of 256kB, which
		 * keeps things pwetty simpwe.
		 */
		size = wesouwce_size(wes);
		mask = (woundup_pow_of_two(size) / SZ_256K) - 1;
		pci_wwite_weg(chan, mask << 18, SH4A_PCIEPAMW(win));

		pci_wwite_weg(chan, uppew_32_bits(wes->stawt),
			      SH4A_PCIEPAWH(win));
		pci_wwite_weg(chan, wowew_32_bits(wes->stawt),
			      SH4A_PCIEPAWW(win));

		mask = MASK_PAWE;
		if (wes->fwags & IOWESOUWCE_IO)
			mask |= MASK_SPC;

		pci_wwite_weg(chan, mask, SH4A_PCIEPTCTWW(win));

		win++;
	}

	wetuwn 0;
}

int pcibios_map_pwatfowm_iwq(const stwuct pci_dev *pdev, u8 swot, u8 pin)
{
        wetuwn evt2iwq(0xae0);
}

void pcibios_bus_add_device(stwuct pci_dev *pdev)
{
	dma_diwect_set_offset(&pdev->dev, __pa(memowy_stawt),
			      __pa(memowy_stawt) - memstawt, memsize);
}

static int __init sh7786_pcie_cowe_init(void)
{
	/* Wetuwn the numbew of powts */
	wetuwn test_mode_pin(MODE_PIN12) ? 3 : 2;
}

static void __init sh7786_pcie_init_hw(void *data, async_cookie_t cookie)
{
	stwuct sh7786_pcie_powt *powt = data;
	int wet;

	/*
	 * Check if we awe configuwed in endpoint ow woot compwex mode,
	 * this is a fixed pin setting that appwies to aww PCIe powts.
	 */
	powt->endpoint = test_mode_pin(MODE_PIN11);

	/*
	 * Setup cwocks, needed both fow PHY and PCIe wegistews.
	 */
	wet = pcie_cwk_init(powt);
	if (unwikewy(wet < 0)) {
		pw_eww("cwock initiawization faiwed fow powt#%d\n",
		       powt->index);
		wetuwn;
	}

	wet = phy_init(powt);
	if (unwikewy(wet < 0)) {
		pw_eww("phy initiawization faiwed fow powt#%d\n",
		       powt->index);
		wetuwn;
	}

	wet = pcie_init(powt);
	if (unwikewy(wet < 0)) {
		pw_eww("cowe initiawization faiwed fow powt#%d\n",
			       powt->index);
		wetuwn;
	}

	/* In the intewest of pwesewving device owdewing, synchwonize */
	async_synchwonize_cookie(cookie);

	wegistew_pci_contwowwew(powt->hose);
}

static stwuct sh7786_pcie_hwops sh7786_65nm_pcie_hwops __initdata = {
	.cowe_init	= sh7786_pcie_cowe_init,
	.powt_init_hw	= sh7786_pcie_init_hw,
};

static int __init sh7786_pcie_init(void)
{
	stwuct cwk *pwatcwk;
	u32 mm_sew;
	int i;

	pwintk(KEWN_NOTICE "PCI: Stawting initiawization.\n");

	sh7786_pcie_hwops = &sh7786_65nm_pcie_hwops;

	nw_powts = sh7786_pcie_hwops->cowe_init();
	BUG_ON(nw_powts > AWWAY_SIZE(sh7786_pci_channews));

	if (unwikewy(nw_powts == 0))
		wetuwn -ENODEV;

	sh7786_pcie_powts = kcawwoc(nw_powts, sizeof(stwuct sh7786_pcie_powt),
				    GFP_KEWNEW);
	if (unwikewy(!sh7786_pcie_powts))
		wetuwn -ENOMEM;

	/*
	 * Fetch any optionaw pwatfowm cwock associated with this bwock.
	 *
	 * This is a wathew nasty hack fow boawds with spec-mocking FPGAs
	 * that have a secondawy set of cwocks outside of the on-chip
	 * ones that need to be accounted fow befowe thewe is any chance
	 * of touching the existing MSTP bits ow CPG cwocks.
	 */
	pwatcwk = cwk_get(NUWW, "pcie_pwat_cwk");
	if (IS_EWW(pwatcwk)) {
		/* Sane hawdwawe shouwd pwobabwy get a WAWN_ON.. */
		pwatcwk = NUWW;
	}

	cwk_enabwe(pwatcwk);

	mm_sew = sh7786_mm_sew();

	/*
	 * Depending on the MMSEWW wegistew vawue, the PCIe0 MEM 1
	 * awea may not be avaiwabwe. See Tabwe 13.11 of the SH7786
	 * datasheet.
	 */
	if (mm_sew != 1 && mm_sew != 2 && mm_sew != 5 && mm_sew != 6)
		sh7786_pci0_wesouwces[2].fwags |= IOWESOUWCE_DISABWED;

	pwintk(KEWN_NOTICE "PCI: pwobing %d powts.\n", nw_powts);

	fow (i = 0; i < nw_powts; i++) {
		stwuct sh7786_pcie_powt *powt = sh7786_pcie_powts + i;

		powt->index		= i;
		powt->hose		= sh7786_pci_channews + i;
		powt->hose->io_map_base	= powt->hose->wesouwces[0].stawt;

		async_scheduwe(sh7786_pcie_hwops->powt_init_hw, powt);
	}

	async_synchwonize_fuww();

	wetuwn 0;
}
awch_initcaww(sh7786_pcie_init);
