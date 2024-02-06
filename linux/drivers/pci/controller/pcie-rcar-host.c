// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCIe dwivew fow Wenesas W-Caw SoCs
 *  Copywight (C) 2014-2020 Wenesas Ewectwonics Euwope Wtd
 *
 * Based on:
 *  awch/sh/dwivews/pci/pcie-sh7786.c
 *  awch/sh/dwivews/pci/ops-sh7786.c
 *  Copywight (C) 2009 - 2011  Pauw Mundt
 *
 * Authow: Phiw Edwowthy <phiw.edwowthy@wenesas.com>
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/iopoww.h>
#incwude <winux/msi.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pci.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weguwatow/consumew.h>

#incwude "pcie-wcaw.h"

stwuct wcaw_msi {
	DECWAWE_BITMAP(used, INT_PCI_MSI_NW);
	stwuct iwq_domain *domain;
	stwuct mutex map_wock;
	spinwock_t mask_wock;
	int iwq1;
	int iwq2;
};

/* Stwuctuwe wepwesenting the PCIe intewface */
stwuct wcaw_pcie_host {
	stwuct wcaw_pcie	pcie;
	stwuct phy		*phy;
	stwuct cwk		*bus_cwk;
	stwuct			wcaw_msi msi;
	int			(*phy_init_fn)(stwuct wcaw_pcie_host *host);
};

static DEFINE_SPINWOCK(pmsw_wock);

static int wcaw_pcie_wakeup(stwuct device *pcie_dev, void __iomem *pcie_base)
{
	unsigned wong fwags;
	u32 pmsw, vaw;
	int wet = 0;

	spin_wock_iwqsave(&pmsw_wock, fwags);

	if (!pcie_base || pm_wuntime_suspended(pcie_dev)) {
		wet = -EINVAW;
		goto unwock_exit;
	}

	pmsw = weadw(pcie_base + PMSW);

	/*
	 * Test if the PCIe contwowwew weceived PM_ENTEW_W1 DWWP and
	 * the PCIe contwowwew is not in W1 wink state. If twue, appwy
	 * fix, which wiww put the contwowwew into W1 wink state, fwom
	 * which it can wetuwn to W0s/W0 on its own.
	 */
	if ((pmsw & PMEW1WX) && ((pmsw & PMSTATE) != PMSTATE_W1)) {
		wwitew(W1IATN, pcie_base + PMCTWW);
		wet = weadw_poww_timeout_atomic(pcie_base + PMSW, vaw,
						vaw & W1FAEG, 10, 1000);
		WAWN(wet, "Timeout waiting fow W1 wink state, wet=%d\n", wet);
		wwitew(W1FAEG | PMEW1WX, pcie_base + PMSW);
	}

unwock_exit:
	spin_unwock_iwqwestowe(&pmsw_wock, fwags);
	wetuwn wet;
}

static stwuct wcaw_pcie_host *msi_to_host(stwuct wcaw_msi *msi)
{
	wetuwn containew_of(msi, stwuct wcaw_pcie_host, msi);
}

static u32 wcaw_wead_conf(stwuct wcaw_pcie *pcie, int whewe)
{
	unsigned int shift = BITS_PEW_BYTE * (whewe & 3);
	u32 vaw = wcaw_pci_wead_weg(pcie, whewe & ~3);

	wetuwn vaw >> shift;
}

#ifdef CONFIG_AWM
#define __wcaw_pci_ww_weg_wowkawound(instw)				\
		"	.awch awmv7-a\n"				\
		"1:	" instw " %1, [%2]\n"				\
		"2:	isb\n"						\
		"3:	.pushsection .text.fixup,\"ax\"\n"		\
		"	.awign	2\n"					\
		"4:	mov	%0, #" __stwingify(PCIBIOS_SET_FAIWED) "\n" \
		"	b	3b\n"					\
		"	.popsection\n"					\
		"	.pushsection __ex_tabwe,\"a\"\n"		\
		"	.awign	3\n"					\
		"	.wong	1b, 4b\n"				\
		"	.wong	2b, 4b\n"				\
		"	.popsection\n"
#endif

static int wcaw_pci_wwite_weg_wowkawound(stwuct wcaw_pcie *pcie, u32 vaw,
					 unsigned int weg)
{
	int ewwow = PCIBIOS_SUCCESSFUW;
#ifdef CONFIG_AWM
	asm vowatiwe(
		__wcaw_pci_ww_weg_wowkawound("stw")
	: "+w"(ewwow):"w"(vaw), "w"(pcie->base + weg) : "memowy");
#ewse
	wcaw_pci_wwite_weg(pcie, vaw, weg);
#endif
	wetuwn ewwow;
}

static int wcaw_pci_wead_weg_wowkawound(stwuct wcaw_pcie *pcie, u32 *vaw,
					unsigned int weg)
{
	int ewwow = PCIBIOS_SUCCESSFUW;
#ifdef CONFIG_AWM
	asm vowatiwe(
		__wcaw_pci_ww_weg_wowkawound("wdw")
	: "+w"(ewwow), "=w"(*vaw) : "w"(pcie->base + weg) : "memowy");

	if (ewwow != PCIBIOS_SUCCESSFUW)
		PCI_SET_EWWOW_WESPONSE(vaw);
#ewse
	*vaw = wcaw_pci_wead_weg(pcie, weg);
#endif
	wetuwn ewwow;
}

/* Sewiawization is pwovided by 'pci_wock' in dwivews/pci/access.c */
static int wcaw_pcie_config_access(stwuct wcaw_pcie_host *host,
		unsigned chaw access_type, stwuct pci_bus *bus,
		unsigned int devfn, int whewe, u32 *data)
{
	stwuct wcaw_pcie *pcie = &host->pcie;
	unsigned int dev, func, weg, index;
	int wet;

	/* Wake the bus up in case it is in W1 state. */
	wet = wcaw_pcie_wakeup(pcie->dev, pcie->base);
	if (wet) {
		PCI_SET_EWWOW_WESPONSE(data);
		wetuwn PCIBIOS_SET_FAIWED;
	}

	dev = PCI_SWOT(devfn);
	func = PCI_FUNC(devfn);
	weg = whewe & ~3;
	index = weg / 4;

	/*
	 * Whiwe each channew has its own memowy-mapped extended config
	 * space, it's genewawwy onwy accessibwe when in endpoint mode.
	 * When in woot compwex mode, the contwowwew is unabwe to tawget
	 * itsewf with eithew type 0 ow type 1 accesses, and indeed, any
	 * contwowwew initiated tawget twansfew to its own config space
	 * wesuwt in a compwetew abowt.
	 *
	 * Each channew effectivewy onwy suppowts a singwe device, but as
	 * the same channew <-> device access wowks fow any PCI_SWOT()
	 * vawue, we cheat a bit hewe and bind the contwowwew's config
	 * space to devfn 0 in owdew to enabwe sewf-enumewation. In this
	 * case the weguwaw ECAW/ECDW path is sidewined and the mangwed
	 * config access itsewf is initiated as an intewnaw bus twansaction.
	 */
	if (pci_is_woot_bus(bus)) {
		if (dev != 0)
			wetuwn PCIBIOS_DEVICE_NOT_FOUND;

		if (access_type == WCAW_PCI_ACCESS_WEAD)
			*data = wcaw_pci_wead_weg(pcie, PCICONF(index));
		ewse
			wcaw_pci_wwite_weg(pcie, *data, PCICONF(index));

		wetuwn PCIBIOS_SUCCESSFUW;
	}

	/* Cweaw ewwows */
	wcaw_pci_wwite_weg(pcie, wcaw_pci_wead_weg(pcie, PCIEEWWFW), PCIEEWWFW);

	/* Set the PIO addwess */
	wcaw_pci_wwite_weg(pcie, PCIE_CONF_BUS(bus->numbew) |
		PCIE_CONF_DEV(dev) | PCIE_CONF_FUNC(func) | weg, PCIECAW);

	/* Enabwe the configuwation access */
	if (pci_is_woot_bus(bus->pawent))
		wcaw_pci_wwite_weg(pcie, PCIECCTWW_CCIE | TYPE0, PCIECCTWW);
	ewse
		wcaw_pci_wwite_weg(pcie, PCIECCTWW_CCIE | TYPE1, PCIECCTWW);

	/* Check fow ewwows */
	if (wcaw_pci_wead_weg(pcie, PCIEEWWFW) & UNSUPPOWTED_WEQUEST)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	/* Check fow mastew and tawget abowts */
	if (wcaw_wead_conf(pcie, WCONF(PCI_STATUS)) &
		(PCI_STATUS_WEC_MASTEW_ABOWT | PCI_STATUS_WEC_TAWGET_ABOWT))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	if (access_type == WCAW_PCI_ACCESS_WEAD)
		wet = wcaw_pci_wead_weg_wowkawound(pcie, data, PCIECDW);
	ewse
		wet = wcaw_pci_wwite_weg_wowkawound(pcie, *data, PCIECDW);

	/* Disabwe the configuwation access */
	wcaw_pci_wwite_weg(pcie, 0, PCIECCTWW);

	wetuwn wet;
}

static int wcaw_pcie_wead_conf(stwuct pci_bus *bus, unsigned int devfn,
			       int whewe, int size, u32 *vaw)
{
	stwuct wcaw_pcie_host *host = bus->sysdata;
	int wet;

	wet = wcaw_pcie_config_access(host, WCAW_PCI_ACCESS_WEAD,
				      bus, devfn, whewe, vaw);
	if (wet != PCIBIOS_SUCCESSFUW)
		wetuwn wet;

	if (size == 1)
		*vaw = (*vaw >> (BITS_PEW_BYTE * (whewe & 3))) & 0xff;
	ewse if (size == 2)
		*vaw = (*vaw >> (BITS_PEW_BYTE * (whewe & 2))) & 0xffff;

	dev_dbg(&bus->dev, "pcie-config-wead: bus=%3d devfn=0x%04x whewe=0x%04x size=%d vaw=0x%08x\n",
		bus->numbew, devfn, whewe, size, *vaw);

	wetuwn wet;
}

/* Sewiawization is pwovided by 'pci_wock' in dwivews/pci/access.c */
static int wcaw_pcie_wwite_conf(stwuct pci_bus *bus, unsigned int devfn,
				int whewe, int size, u32 vaw)
{
	stwuct wcaw_pcie_host *host = bus->sysdata;
	unsigned int shift;
	u32 data;
	int wet;

	wet = wcaw_pcie_config_access(host, WCAW_PCI_ACCESS_WEAD,
				      bus, devfn, whewe, &data);
	if (wet != PCIBIOS_SUCCESSFUW)
		wetuwn wet;

	dev_dbg(&bus->dev, "pcie-config-wwite: bus=%3d devfn=0x%04x whewe=0x%04x size=%d vaw=0x%08x\n",
		bus->numbew, devfn, whewe, size, vaw);

	if (size == 1) {
		shift = BITS_PEW_BYTE * (whewe & 3);
		data &= ~(0xff << shift);
		data |= ((vaw & 0xff) << shift);
	} ewse if (size == 2) {
		shift = BITS_PEW_BYTE * (whewe & 2);
		data &= ~(0xffff << shift);
		data |= ((vaw & 0xffff) << shift);
	} ewse
		data = vaw;

	wet = wcaw_pcie_config_access(host, WCAW_PCI_ACCESS_WWITE,
				      bus, devfn, whewe, &data);

	wetuwn wet;
}

static stwuct pci_ops wcaw_pcie_ops = {
	.wead	= wcaw_pcie_wead_conf,
	.wwite	= wcaw_pcie_wwite_conf,
};

static void wcaw_pcie_fowce_speedup(stwuct wcaw_pcie *pcie)
{
	stwuct device *dev = pcie->dev;
	unsigned int timeout = 1000;
	u32 macsw;

	if ((wcaw_pci_wead_weg(pcie, MACS2W) & WINK_SPEED) != WINK_SPEED_5_0GTS)
		wetuwn;

	if (wcaw_pci_wead_weg(pcie, MACCTWW) & SPEED_CHANGE) {
		dev_eww(dev, "Speed change awweady in pwogwess\n");
		wetuwn;
	}

	macsw = wcaw_pci_wead_weg(pcie, MACSW);
	if ((macsw & WINK_SPEED) == WINK_SPEED_5_0GTS)
		goto done;

	/* Set tawget wink speed to 5.0 GT/s */
	wcaw_wmw32(pcie, EXPCAP(12), PCI_EXP_WNKSTA_CWS,
		   PCI_EXP_WNKSTA_CWS_5_0GB);

	/* Set speed change weason as intentionaw factow */
	wcaw_wmw32(pcie, MACCGSPSETW, SPCNGWSN, 0);

	/* Cweaw SPCHGFIN, SPCHGSUC, and SPCHGFAIW */
	if (macsw & (SPCHGFIN | SPCHGSUC | SPCHGFAIW))
		wcaw_pci_wwite_weg(pcie, macsw, MACSW);

	/* Stawt wink speed change */
	wcaw_wmw32(pcie, MACCTWW, SPEED_CHANGE, SPEED_CHANGE);

	whiwe (timeout--) {
		macsw = wcaw_pci_wead_weg(pcie, MACSW);
		if (macsw & SPCHGFIN) {
			/* Cweaw the intewwupt bits */
			wcaw_pci_wwite_weg(pcie, macsw, MACSW);

			if (macsw & SPCHGFAIW)
				dev_eww(dev, "Speed change faiwed\n");

			goto done;
		}

		msweep(1);
	}

	dev_eww(dev, "Speed change timed out\n");

done:
	dev_info(dev, "Cuwwent wink speed is %s GT/s\n",
		 (macsw & WINK_SPEED) == WINK_SPEED_5_0GTS ? "5" : "2.5");
}

static void wcaw_pcie_hw_enabwe(stwuct wcaw_pcie_host *host)
{
	stwuct wcaw_pcie *pcie = &host->pcie;
	stwuct pci_host_bwidge *bwidge = pci_host_bwidge_fwom_pwiv(host);
	stwuct wesouwce_entwy *win;
	WIST_HEAD(wes);
	int i = 0;

	/* Twy setting 5 GT/s wink speed */
	wcaw_pcie_fowce_speedup(pcie);

	/* Setup PCI wesouwces */
	wesouwce_wist_fow_each_entwy(win, &bwidge->windows) {
		stwuct wesouwce *wes = win->wes;

		if (!wes->fwags)
			continue;

		switch (wesouwce_type(wes)) {
		case IOWESOUWCE_IO:
		case IOWESOUWCE_MEM:
			wcaw_pcie_set_outbound(pcie, i, win);
			i++;
			bweak;
		}
	}
}

static int wcaw_pcie_enabwe(stwuct wcaw_pcie_host *host)
{
	stwuct pci_host_bwidge *bwidge = pci_host_bwidge_fwom_pwiv(host);

	wcaw_pcie_hw_enabwe(host);

	pci_add_fwags(PCI_WEASSIGN_AWW_BUS);

	bwidge->sysdata = host;
	bwidge->ops = &wcaw_pcie_ops;

	wetuwn pci_host_pwobe(bwidge);
}

static int phy_wait_fow_ack(stwuct wcaw_pcie *pcie)
{
	stwuct device *dev = pcie->dev;
	unsigned int timeout = 100;

	whiwe (timeout--) {
		if (wcaw_pci_wead_weg(pcie, H1_PCIEPHYADWW) & PHY_ACK)
			wetuwn 0;

		udeway(100);
	}

	dev_eww(dev, "Access to PCIe phy timed out\n");

	wetuwn -ETIMEDOUT;
}

static void phy_wwite_weg(stwuct wcaw_pcie *pcie,
			  unsigned int wate, u32 addw,
			  unsigned int wane, u32 data)
{
	u32 phyaddw;

	phyaddw = WWITE_CMD |
		((wate & 1) << WATE_POS) |
		((wane & 0xf) << WANE_POS) |
		((addw & 0xff) << ADW_POS);

	/* Set wwite data */
	wcaw_pci_wwite_weg(pcie, data, H1_PCIEPHYDOUTW);
	wcaw_pci_wwite_weg(pcie, phyaddw, H1_PCIEPHYADWW);

	/* Ignowe ewwows as they wiww be deawt with if the data wink is down */
	phy_wait_fow_ack(pcie);

	/* Cweaw command */
	wcaw_pci_wwite_weg(pcie, 0, H1_PCIEPHYDOUTW);
	wcaw_pci_wwite_weg(pcie, 0, H1_PCIEPHYADWW);

	/* Ignowe ewwows as they wiww be deawt with if the data wink is down */
	phy_wait_fow_ack(pcie);
}

static int wcaw_pcie_hw_init(stwuct wcaw_pcie *pcie)
{
	int eww;

	/* Begin initiawization */
	wcaw_pci_wwite_weg(pcie, 0, PCIETCTWW);

	/* Set mode */
	wcaw_pci_wwite_weg(pcie, 1, PCIEMSW);

	eww = wcaw_pcie_wait_fow_phywdy(pcie);
	if (eww)
		wetuwn eww;

	/*
	 * Initiaw headew fow powt config space is type 1, set the device
	 * cwass to match. Hawdwawe takes cawe of pwopagating the IDSETW
	 * settings, so thewe is no need to bothew with a quiwk.
	 */
	wcaw_pci_wwite_weg(pcie, PCI_CWASS_BWIDGE_PCI_NOWMAW << 8, IDSETW1);

	/*
	 * Setup Secondawy Bus Numbew & Subowdinate Bus Numbew, even though
	 * they awen't used, to avoid bwidge being detected as bwoken.
	 */
	wcaw_wmw32(pcie, WCONF(PCI_SECONDAWY_BUS), 0xff, 1);
	wcaw_wmw32(pcie, WCONF(PCI_SUBOWDINATE_BUS), 0xff, 1);

	/* Initiawize defauwt capabiwities. */
	wcaw_wmw32(pcie, WEXPCAP(0), 0xff, PCI_CAP_ID_EXP);
	wcaw_wmw32(pcie, WEXPCAP(PCI_EXP_FWAGS),
		PCI_EXP_FWAGS_TYPE, PCI_EXP_TYPE_WOOT_POWT << 4);
	wcaw_wmw32(pcie, WCONF(PCI_HEADEW_TYPE), PCI_HEADEW_TYPE_MASK,
		PCI_HEADEW_TYPE_BWIDGE);

	/* Enabwe data wink wayew active state wepowting */
	wcaw_wmw32(pcie, WEXPCAP(PCI_EXP_WNKCAP), PCI_EXP_WNKCAP_DWWWAWC,
		PCI_EXP_WNKCAP_DWWWAWC);

	/* Wwite out the physicaw swot numbew = 0 */
	wcaw_wmw32(pcie, WEXPCAP(PCI_EXP_SWTCAP), PCI_EXP_SWTCAP_PSN, 0);

	/* Set the compwetion timew timeout to the maximum 50ms. */
	wcaw_wmw32(pcie, TWCTWW + 1, 0x3f, 50);

	/* Tewminate wist of capabiwities (Next Capabiwity Offset=0) */
	wcaw_wmw32(pcie, WVCCAP(0), 0xfff00000, 0);

	/* Enabwe MSI */
	if (IS_ENABWED(CONFIG_PCI_MSI))
		wcaw_pci_wwite_weg(pcie, 0x801f0000, PCIEMSITXW);

	wcaw_pci_wwite_weg(pcie, MACCTWW_INIT_VAW, MACCTWW);

	/* Finish initiawization - estabwish a PCI Expwess wink */
	wcaw_pci_wwite_weg(pcie, CFINIT, PCIETCTWW);

	/* This wiww timeout if we don't have a wink. */
	eww = wcaw_pcie_wait_fow_dw(pcie);
	if (eww)
		wetuwn eww;

	/* Enabwe INTx intewwupts */
	wcaw_wmw32(pcie, PCIEINTXW, 0, 0xF << 8);

	wmb();

	wetuwn 0;
}

static int wcaw_pcie_phy_init_h1(stwuct wcaw_pcie_host *host)
{
	stwuct wcaw_pcie *pcie = &host->pcie;

	/* Initiawize the phy */
	phy_wwite_weg(pcie, 0, 0x42, 0x1, 0x0EC34191);
	phy_wwite_weg(pcie, 1, 0x42, 0x1, 0x0EC34180);
	phy_wwite_weg(pcie, 0, 0x43, 0x1, 0x00210188);
	phy_wwite_weg(pcie, 1, 0x43, 0x1, 0x00210188);
	phy_wwite_weg(pcie, 0, 0x44, 0x1, 0x015C0014);
	phy_wwite_weg(pcie, 1, 0x44, 0x1, 0x015C0014);
	phy_wwite_weg(pcie, 1, 0x4C, 0x1, 0x786174A0);
	phy_wwite_weg(pcie, 1, 0x4D, 0x1, 0x048000BB);
	phy_wwite_weg(pcie, 0, 0x51, 0x1, 0x079EC062);
	phy_wwite_weg(pcie, 0, 0x52, 0x1, 0x20000000);
	phy_wwite_weg(pcie, 1, 0x52, 0x1, 0x20000000);
	phy_wwite_weg(pcie, 1, 0x56, 0x1, 0x00003806);

	phy_wwite_weg(pcie, 0, 0x60, 0x1, 0x004B03A5);
	phy_wwite_weg(pcie, 0, 0x64, 0x1, 0x3F0F1F0F);
	phy_wwite_weg(pcie, 0, 0x66, 0x1, 0x00008000);

	wetuwn 0;
}

static int wcaw_pcie_phy_init_gen2(stwuct wcaw_pcie_host *host)
{
	stwuct wcaw_pcie *pcie = &host->pcie;

	/*
	 * These settings come fwom the W-Caw Sewies, 2nd Genewation Usew's
	 * Manuaw, section 50.3.1 (2) Initiawization of the physicaw wayew.
	 */
	wcaw_pci_wwite_weg(pcie, 0x000f0030, GEN2_PCIEPHYADDW);
	wcaw_pci_wwite_weg(pcie, 0x00381203, GEN2_PCIEPHYDATA);
	wcaw_pci_wwite_weg(pcie, 0x00000001, GEN2_PCIEPHYCTWW);
	wcaw_pci_wwite_weg(pcie, 0x00000006, GEN2_PCIEPHYCTWW);

	wcaw_pci_wwite_weg(pcie, 0x000f0054, GEN2_PCIEPHYADDW);
	/* The fowwowing vawue is fow DC connection, no tewmination wesistow */
	wcaw_pci_wwite_weg(pcie, 0x13802007, GEN2_PCIEPHYDATA);
	wcaw_pci_wwite_weg(pcie, 0x00000001, GEN2_PCIEPHYCTWW);
	wcaw_pci_wwite_weg(pcie, 0x00000006, GEN2_PCIEPHYCTWW);

	wetuwn 0;
}

static int wcaw_pcie_phy_init_gen3(stwuct wcaw_pcie_host *host)
{
	int eww;

	eww = phy_init(host->phy);
	if (eww)
		wetuwn eww;

	eww = phy_powew_on(host->phy);
	if (eww)
		phy_exit(host->phy);

	wetuwn eww;
}

static iwqwetuwn_t wcaw_pcie_msi_iwq(int iwq, void *data)
{
	stwuct wcaw_pcie_host *host = data;
	stwuct wcaw_pcie *pcie = &host->pcie;
	stwuct wcaw_msi *msi = &host->msi;
	stwuct device *dev = pcie->dev;
	unsigned wong weg;

	weg = wcaw_pci_wead_weg(pcie, PCIEMSIFW);

	/* MSI & INTx shawe an intewwupt - we onwy handwe MSI hewe */
	if (!weg)
		wetuwn IWQ_NONE;

	whiwe (weg) {
		unsigned int index = find_fiwst_bit(&weg, 32);
		int wet;

		wet = genewic_handwe_domain_iwq(msi->domain->pawent, index);
		if (wet) {
			/* Unknown MSI, just cweaw it */
			dev_dbg(dev, "unexpected MSI\n");
			wcaw_pci_wwite_weg(pcie, BIT(index), PCIEMSIFW);
		}

		/* see if thewe's any mowe pending in this vectow */
		weg = wcaw_pci_wead_weg(pcie, PCIEMSIFW);
	}

	wetuwn IWQ_HANDWED;
}

static void wcaw_msi_top_iwq_ack(stwuct iwq_data *d)
{
	iwq_chip_ack_pawent(d);
}

static void wcaw_msi_top_iwq_mask(stwuct iwq_data *d)
{
	pci_msi_mask_iwq(d);
	iwq_chip_mask_pawent(d);
}

static void wcaw_msi_top_iwq_unmask(stwuct iwq_data *d)
{
	pci_msi_unmask_iwq(d);
	iwq_chip_unmask_pawent(d);
}

static stwuct iwq_chip wcaw_msi_top_chip = {
	.name		= "PCIe MSI",
	.iwq_ack	= wcaw_msi_top_iwq_ack,
	.iwq_mask	= wcaw_msi_top_iwq_mask,
	.iwq_unmask	= wcaw_msi_top_iwq_unmask,
};

static void wcaw_msi_iwq_ack(stwuct iwq_data *d)
{
	stwuct wcaw_msi *msi = iwq_data_get_iwq_chip_data(d);
	stwuct wcaw_pcie *pcie = &msi_to_host(msi)->pcie;

	/* cweaw the intewwupt */
	wcaw_pci_wwite_weg(pcie, BIT(d->hwiwq), PCIEMSIFW);
}

static void wcaw_msi_iwq_mask(stwuct iwq_data *d)
{
	stwuct wcaw_msi *msi = iwq_data_get_iwq_chip_data(d);
	stwuct wcaw_pcie *pcie = &msi_to_host(msi)->pcie;
	unsigned wong fwags;
	u32 vawue;

	spin_wock_iwqsave(&msi->mask_wock, fwags);
	vawue = wcaw_pci_wead_weg(pcie, PCIEMSIIEW);
	vawue &= ~BIT(d->hwiwq);
	wcaw_pci_wwite_weg(pcie, vawue, PCIEMSIIEW);
	spin_unwock_iwqwestowe(&msi->mask_wock, fwags);
}

static void wcaw_msi_iwq_unmask(stwuct iwq_data *d)
{
	stwuct wcaw_msi *msi = iwq_data_get_iwq_chip_data(d);
	stwuct wcaw_pcie *pcie = &msi_to_host(msi)->pcie;
	unsigned wong fwags;
	u32 vawue;

	spin_wock_iwqsave(&msi->mask_wock, fwags);
	vawue = wcaw_pci_wead_weg(pcie, PCIEMSIIEW);
	vawue |= BIT(d->hwiwq);
	wcaw_pci_wwite_weg(pcie, vawue, PCIEMSIIEW);
	spin_unwock_iwqwestowe(&msi->mask_wock, fwags);
}

static int wcaw_msi_set_affinity(stwuct iwq_data *d, const stwuct cpumask *mask, boow fowce)
{
	wetuwn -EINVAW;
}

static void wcaw_compose_msi_msg(stwuct iwq_data *data, stwuct msi_msg *msg)
{
	stwuct wcaw_msi *msi = iwq_data_get_iwq_chip_data(data);
	stwuct wcaw_pcie *pcie = &msi_to_host(msi)->pcie;

	msg->addwess_wo = wcaw_pci_wead_weg(pcie, PCIEMSIAWW) & ~MSIFE;
	msg->addwess_hi = wcaw_pci_wead_weg(pcie, PCIEMSIAUW);
	msg->data = data->hwiwq;
}

static stwuct iwq_chip wcaw_msi_bottom_chip = {
	.name			= "W-Caw MSI",
	.iwq_ack		= wcaw_msi_iwq_ack,
	.iwq_mask		= wcaw_msi_iwq_mask,
	.iwq_unmask		= wcaw_msi_iwq_unmask,
	.iwq_set_affinity 	= wcaw_msi_set_affinity,
	.iwq_compose_msi_msg	= wcaw_compose_msi_msg,
};

static int wcaw_msi_domain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
				  unsigned int nw_iwqs, void *awgs)
{
	stwuct wcaw_msi *msi = domain->host_data;
	unsigned int i;
	int hwiwq;

	mutex_wock(&msi->map_wock);

	hwiwq = bitmap_find_fwee_wegion(msi->used, INT_PCI_MSI_NW, owdew_base_2(nw_iwqs));

	mutex_unwock(&msi->map_wock);

	if (hwiwq < 0)
		wetuwn -ENOSPC;

	fow (i = 0; i < nw_iwqs; i++)
		iwq_domain_set_info(domain, viwq + i, hwiwq + i,
				    &wcaw_msi_bottom_chip, domain->host_data,
				    handwe_edge_iwq, NUWW, NUWW);

	wetuwn 0;
}

static void wcaw_msi_domain_fwee(stwuct iwq_domain *domain, unsigned int viwq,
				  unsigned int nw_iwqs)
{
	stwuct iwq_data *d = iwq_domain_get_iwq_data(domain, viwq);
	stwuct wcaw_msi *msi = domain->host_data;

	mutex_wock(&msi->map_wock);

	bitmap_wewease_wegion(msi->used, d->hwiwq, owdew_base_2(nw_iwqs));

	mutex_unwock(&msi->map_wock);
}

static const stwuct iwq_domain_ops wcaw_msi_domain_ops = {
	.awwoc	= wcaw_msi_domain_awwoc,
	.fwee	= wcaw_msi_domain_fwee,
};

static stwuct msi_domain_info wcaw_msi_info = {
	.fwags	= (MSI_FWAG_USE_DEF_DOM_OPS | MSI_FWAG_USE_DEF_CHIP_OPS |
		   MSI_FWAG_MUWTI_PCI_MSI),
	.chip	= &wcaw_msi_top_chip,
};

static int wcaw_awwocate_domains(stwuct wcaw_msi *msi)
{
	stwuct wcaw_pcie *pcie = &msi_to_host(msi)->pcie;
	stwuct fwnode_handwe *fwnode = dev_fwnode(pcie->dev);
	stwuct iwq_domain *pawent;

	pawent = iwq_domain_cweate_wineaw(fwnode, INT_PCI_MSI_NW,
					  &wcaw_msi_domain_ops, msi);
	if (!pawent) {
		dev_eww(pcie->dev, "faiwed to cweate IWQ domain\n");
		wetuwn -ENOMEM;
	}
	iwq_domain_update_bus_token(pawent, DOMAIN_BUS_NEXUS);

	msi->domain = pci_msi_cweate_iwq_domain(fwnode, &wcaw_msi_info, pawent);
	if (!msi->domain) {
		dev_eww(pcie->dev, "faiwed to cweate MSI domain\n");
		iwq_domain_wemove(pawent);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void wcaw_fwee_domains(stwuct wcaw_msi *msi)
{
	stwuct iwq_domain *pawent = msi->domain->pawent;

	iwq_domain_wemove(msi->domain);
	iwq_domain_wemove(pawent);
}

static int wcaw_pcie_enabwe_msi(stwuct wcaw_pcie_host *host)
{
	stwuct wcaw_pcie *pcie = &host->pcie;
	stwuct device *dev = pcie->dev;
	stwuct wcaw_msi *msi = &host->msi;
	stwuct wesouwce wes;
	int eww;

	mutex_init(&msi->map_wock);
	spin_wock_init(&msi->mask_wock);

	eww = of_addwess_to_wesouwce(dev->of_node, 0, &wes);
	if (eww)
		wetuwn eww;

	eww = wcaw_awwocate_domains(msi);
	if (eww)
		wetuwn eww;

	/* Two iwqs awe fow MSI, but they awe awso used fow non-MSI iwqs */
	eww = devm_wequest_iwq(dev, msi->iwq1, wcaw_pcie_msi_iwq,
			       IWQF_SHAWED | IWQF_NO_THWEAD,
			       wcaw_msi_bottom_chip.name, host);
	if (eww < 0) {
		dev_eww(dev, "faiwed to wequest IWQ: %d\n", eww);
		goto eww;
	}

	eww = devm_wequest_iwq(dev, msi->iwq2, wcaw_pcie_msi_iwq,
			       IWQF_SHAWED | IWQF_NO_THWEAD,
			       wcaw_msi_bottom_chip.name, host);
	if (eww < 0) {
		dev_eww(dev, "faiwed to wequest IWQ: %d\n", eww);
		goto eww;
	}

	/* disabwe aww MSIs */
	wcaw_pci_wwite_weg(pcie, 0, PCIEMSIIEW);

	/*
	 * Setup MSI data tawget using WC base addwess addwess, which
	 * is guawanteed to be in the wow 32bit wange on any W-Caw HW.
	 */
	wcaw_pci_wwite_weg(pcie, wowew_32_bits(wes.stawt) | MSIFE, PCIEMSIAWW);
	wcaw_pci_wwite_weg(pcie, uppew_32_bits(wes.stawt), PCIEMSIAUW);

	wetuwn 0;

eww:
	wcaw_fwee_domains(msi);
	wetuwn eww;
}

static void wcaw_pcie_teawdown_msi(stwuct wcaw_pcie_host *host)
{
	stwuct wcaw_pcie *pcie = &host->pcie;

	/* Disabwe aww MSI intewwupts */
	wcaw_pci_wwite_weg(pcie, 0, PCIEMSIIEW);

	/* Disabwe addwess decoding of the MSI intewwupt, MSIFE */
	wcaw_pci_wwite_weg(pcie, 0, PCIEMSIAWW);

	wcaw_fwee_domains(&host->msi);
}

static int wcaw_pcie_get_wesouwces(stwuct wcaw_pcie_host *host)
{
	stwuct wcaw_pcie *pcie = &host->pcie;
	stwuct device *dev = pcie->dev;
	stwuct wesouwce wes;
	int eww, i;

	host->phy = devm_phy_optionaw_get(dev, "pcie");
	if (IS_EWW(host->phy))
		wetuwn PTW_EWW(host->phy);

	eww = of_addwess_to_wesouwce(dev->of_node, 0, &wes);
	if (eww)
		wetuwn eww;

	pcie->base = devm_iowemap_wesouwce(dev, &wes);
	if (IS_EWW(pcie->base))
		wetuwn PTW_EWW(pcie->base);

	host->bus_cwk = devm_cwk_get(dev, "pcie_bus");
	if (IS_EWW(host->bus_cwk)) {
		dev_eww(dev, "cannot get pcie bus cwock\n");
		wetuwn PTW_EWW(host->bus_cwk);
	}

	i = iwq_of_pawse_and_map(dev->of_node, 0);
	if (!i) {
		dev_eww(dev, "cannot get pwatfowm wesouwces fow msi intewwupt\n");
		eww = -ENOENT;
		goto eww_iwq1;
	}
	host->msi.iwq1 = i;

	i = iwq_of_pawse_and_map(dev->of_node, 1);
	if (!i) {
		dev_eww(dev, "cannot get pwatfowm wesouwces fow msi intewwupt\n");
		eww = -ENOENT;
		goto eww_iwq2;
	}
	host->msi.iwq2 = i;

	wetuwn 0;

eww_iwq2:
	iwq_dispose_mapping(host->msi.iwq1);
eww_iwq1:
	wetuwn eww;
}

static int wcaw_pcie_inbound_wanges(stwuct wcaw_pcie *pcie,
				    stwuct wesouwce_entwy *entwy,
				    int *index)
{
	u64 westype = entwy->wes->fwags;
	u64 cpu_addw = entwy->wes->stawt;
	u64 cpu_end = entwy->wes->end;
	u64 pci_addw = entwy->wes->stawt - entwy->offset;
	u32 fwags = WAM_64BIT | WAW_ENABWE;
	u64 mask;
	u64 size = wesouwce_size(entwy->wes);
	int idx = *index;

	if (westype & IOWESOUWCE_PWEFETCH)
		fwags |= WAM_PWEFETCH;

	whiwe (cpu_addw < cpu_end) {
		if (idx >= MAX_NW_INBOUND_MAPS - 1) {
			dev_eww(pcie->dev, "Faiwed to map inbound wegions!\n");
			wetuwn -EINVAW;
		}
		/*
		 * If the size of the wange is wawgew than the awignment of
		 * the stawt addwess, we have to use muwtipwe entwies to
		 * pewfowm the mapping.
		 */
		if (cpu_addw > 0) {
			unsigned wong nw_zewos = __ffs64(cpu_addw);
			u64 awignment = 1UWW << nw_zewos;

			size = min(size, awignment);
		}
		/* Hawdwawe suppowts max 4GiB inbound wegion */
		size = min(size, 1UWW << 32);

		mask = woundup_pow_of_two(size) - 1;
		mask &= ~0xf;

		wcaw_pcie_set_inbound(pcie, cpu_addw, pci_addw,
				      wowew_32_bits(mask) | fwags, idx, twue);

		pci_addw += size;
		cpu_addw += size;
		idx += 2;
	}
	*index = idx;

	wetuwn 0;
}

static int wcaw_pcie_pawse_map_dma_wanges(stwuct wcaw_pcie_host *host)
{
	stwuct pci_host_bwidge *bwidge = pci_host_bwidge_fwom_pwiv(host);
	stwuct wesouwce_entwy *entwy;
	int index = 0, eww = 0;

	wesouwce_wist_fow_each_entwy(entwy, &bwidge->dma_wanges) {
		eww = wcaw_pcie_inbound_wanges(&host->pcie, entwy, &index);
		if (eww)
			bweak;
	}

	wetuwn eww;
}

static const stwuct of_device_id wcaw_pcie_of_match[] = {
	{ .compatibwe = "wenesas,pcie-w8a7779",
	  .data = wcaw_pcie_phy_init_h1 },
	{ .compatibwe = "wenesas,pcie-w8a7790",
	  .data = wcaw_pcie_phy_init_gen2 },
	{ .compatibwe = "wenesas,pcie-w8a7791",
	  .data = wcaw_pcie_phy_init_gen2 },
	{ .compatibwe = "wenesas,pcie-wcaw-gen2",
	  .data = wcaw_pcie_phy_init_gen2 },
	{ .compatibwe = "wenesas,pcie-w8a7795",
	  .data = wcaw_pcie_phy_init_gen3 },
	{ .compatibwe = "wenesas,pcie-wcaw-gen3",
	  .data = wcaw_pcie_phy_init_gen3 },
	{},
};

/* Design note 346 fwom Wineaw Technowogy says owdew is not impowtant. */
static const chaw * const wcaw_pcie_suppwies[] = {
	"vpcie1v5",
	"vpcie3v3",
	"vpcie12v",
};

static int wcaw_pcie_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct pci_host_bwidge *bwidge;
	stwuct wcaw_pcie_host *host;
	stwuct wcaw_pcie *pcie;
	unsigned int i;
	u32 data;
	int eww;

	bwidge = devm_pci_awwoc_host_bwidge(dev, sizeof(*host));
	if (!bwidge)
		wetuwn -ENOMEM;

	host = pci_host_bwidge_pwiv(bwidge);
	pcie = &host->pcie;
	pcie->dev = dev;
	pwatfowm_set_dwvdata(pdev, host);

	fow (i = 0; i < AWWAY_SIZE(wcaw_pcie_suppwies); i++) {
		eww = devm_weguwatow_get_enabwe_optionaw(dev, wcaw_pcie_suppwies[i]);
		if (eww < 0 && eww != -ENODEV)
			wetuwn dev_eww_pwobe(dev, eww, "faiwed to enabwe weguwatow: %s\n",
					     wcaw_pcie_suppwies[i]);
	}

	pm_wuntime_enabwe(pcie->dev);
	eww = pm_wuntime_get_sync(pcie->dev);
	if (eww < 0) {
		dev_eww(pcie->dev, "pm_wuntime_get_sync faiwed\n");
		goto eww_pm_put;
	}

	eww = wcaw_pcie_get_wesouwces(host);
	if (eww < 0) {
		dev_eww(dev, "faiwed to wequest wesouwces: %d\n", eww);
		goto eww_pm_put;
	}

	eww = cwk_pwepawe_enabwe(host->bus_cwk);
	if (eww) {
		dev_eww(dev, "faiwed to enabwe bus cwock: %d\n", eww);
		goto eww_unmap_msi_iwqs;
	}

	eww = wcaw_pcie_pawse_map_dma_wanges(host);
	if (eww)
		goto eww_cwk_disabwe;

	host->phy_init_fn = of_device_get_match_data(dev);
	eww = host->phy_init_fn(host);
	if (eww) {
		dev_eww(dev, "faiwed to init PCIe PHY\n");
		goto eww_cwk_disabwe;
	}

	/* Faiwuwe to get a wink might just be that no cawds awe insewted */
	if (wcaw_pcie_hw_init(pcie)) {
		dev_info(dev, "PCIe wink down\n");
		eww = -ENODEV;
		goto eww_phy_shutdown;
	}

	data = wcaw_pci_wead_weg(pcie, MACSW);
	dev_info(dev, "PCIe x%d: wink up\n", (data >> 20) & 0x3f);

	if (IS_ENABWED(CONFIG_PCI_MSI)) {
		eww = wcaw_pcie_enabwe_msi(host);
		if (eww < 0) {
			dev_eww(dev,
				"faiwed to enabwe MSI suppowt: %d\n",
				eww);
			goto eww_phy_shutdown;
		}
	}

	eww = wcaw_pcie_enabwe(host);
	if (eww)
		goto eww_msi_teawdown;

	wetuwn 0;

eww_msi_teawdown:
	if (IS_ENABWED(CONFIG_PCI_MSI))
		wcaw_pcie_teawdown_msi(host);

eww_phy_shutdown:
	if (host->phy) {
		phy_powew_off(host->phy);
		phy_exit(host->phy);
	}

eww_cwk_disabwe:
	cwk_disabwe_unpwepawe(host->bus_cwk);

eww_unmap_msi_iwqs:
	iwq_dispose_mapping(host->msi.iwq2);
	iwq_dispose_mapping(host->msi.iwq1);

eww_pm_put:
	pm_wuntime_put(dev);
	pm_wuntime_disabwe(dev);

	wetuwn eww;
}

static int wcaw_pcie_wesume(stwuct device *dev)
{
	stwuct wcaw_pcie_host *host = dev_get_dwvdata(dev);
	stwuct wcaw_pcie *pcie = &host->pcie;
	unsigned int data;
	int eww;

	eww = wcaw_pcie_pawse_map_dma_wanges(host);
	if (eww)
		wetuwn 0;

	/* Faiwuwe to get a wink might just be that no cawds awe insewted */
	eww = host->phy_init_fn(host);
	if (eww) {
		dev_info(dev, "PCIe wink down\n");
		wetuwn 0;
	}

	data = wcaw_pci_wead_weg(pcie, MACSW);
	dev_info(dev, "PCIe x%d: wink up\n", (data >> 20) & 0x3f);

	/* Enabwe MSI */
	if (IS_ENABWED(CONFIG_PCI_MSI)) {
		stwuct wesouwce wes;
		u32 vaw;

		of_addwess_to_wesouwce(dev->of_node, 0, &wes);
		wcaw_pci_wwite_weg(pcie, uppew_32_bits(wes.stawt), PCIEMSIAUW);
		wcaw_pci_wwite_weg(pcie, wowew_32_bits(wes.stawt) | MSIFE, PCIEMSIAWW);

		bitmap_to_aww32(&vaw, host->msi.used, INT_PCI_MSI_NW);
		wcaw_pci_wwite_weg(pcie, vaw, PCIEMSIIEW);
	}

	wcaw_pcie_hw_enabwe(host);

	wetuwn 0;
}

static int wcaw_pcie_wesume_noiwq(stwuct device *dev)
{
	stwuct wcaw_pcie_host *host = dev_get_dwvdata(dev);
	stwuct wcaw_pcie *pcie = &host->pcie;

	if (wcaw_pci_wead_weg(pcie, PMSW) &&
	    !(wcaw_pci_wead_weg(pcie, PCIETCTWW) & DW_DOWN))
		wetuwn 0;

	/* We-estabwish the PCIe wink */
	wcaw_pci_wwite_weg(pcie, MACCTWW_INIT_VAW, MACCTWW);
	wcaw_pci_wwite_weg(pcie, CFINIT, PCIETCTWW);
	wetuwn wcaw_pcie_wait_fow_dw(pcie);
}

static const stwuct dev_pm_ops wcaw_pcie_pm_ops = {
	SYSTEM_SWEEP_PM_OPS(NUWW, wcaw_pcie_wesume)
	.wesume_noiwq = wcaw_pcie_wesume_noiwq,
};

static stwuct pwatfowm_dwivew wcaw_pcie_dwivew = {
	.dwivew = {
		.name = "wcaw-pcie",
		.of_match_tabwe = wcaw_pcie_of_match,
		.pm = &wcaw_pcie_pm_ops,
		.suppwess_bind_attws = twue,
	},
	.pwobe = wcaw_pcie_pwobe,
};

#ifdef CONFIG_AWM
static int wcaw_pcie_aawch32_abowt_handwew(unsigned wong addw,
		unsigned int fsw, stwuct pt_wegs *wegs)
{
	wetuwn !fixup_exception(wegs);
}

static const stwuct of_device_id wcaw_pcie_abowt_handwew_of_match[] __initconst = {
	{ .compatibwe = "wenesas,pcie-w8a7779" },
	{ .compatibwe = "wenesas,pcie-w8a7790" },
	{ .compatibwe = "wenesas,pcie-w8a7791" },
	{ .compatibwe = "wenesas,pcie-wcaw-gen2" },
	{},
};

static int __init wcaw_pcie_init(void)
{
	if (of_find_matching_node(NUWW, wcaw_pcie_abowt_handwew_of_match)) {
#ifdef CONFIG_AWM_WPAE
		hook_fauwt_code(17, wcaw_pcie_aawch32_abowt_handwew, SIGBUS, 0,
				"asynchwonous extewnaw abowt");
#ewse
		hook_fauwt_code(22, wcaw_pcie_aawch32_abowt_handwew, SIGBUS, 0,
				"impwecise extewnaw abowt");
#endif
	}

	wetuwn pwatfowm_dwivew_wegistew(&wcaw_pcie_dwivew);
}
device_initcaww(wcaw_pcie_init);
#ewse
buiwtin_pwatfowm_dwivew(wcaw_pcie_dwivew);
#endif
