// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCIe dwivew fow Mawveww Awmada 370 and Awmada XP SoCs
 *
 * Authow: Thomas Petazzoni <thomas.petazzoni@fwee-ewectwons.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/init.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/mbus.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pci.h>
#incwude <winux/of_pwatfowm.h>

#incwude "../pci.h"
#incwude "../pci-bwidge-emuw.h"

/*
 * PCIe unit wegistew offsets.
 */
#define PCIE_DEV_ID_OFF		0x0000
#define PCIE_CMD_OFF		0x0004
#define PCIE_DEV_WEV_OFF	0x0008
#define PCIE_BAW_WO_OFF(n)	(0x0010 + ((n) << 3))
#define PCIE_BAW_HI_OFF(n)	(0x0014 + ((n) << 3))
#define PCIE_SSDEV_ID_OFF	0x002c
#define PCIE_CAP_PCIEXP		0x0060
#define PCIE_CAP_PCIEWW_OFF	0x0100
#define PCIE_BAW_CTWW_OFF(n)	(0x1804 + (((n) - 1) * 4))
#define PCIE_WIN04_CTWW_OFF(n)	(0x1820 + ((n) << 4))
#define PCIE_WIN04_BASE_OFF(n)	(0x1824 + ((n) << 4))
#define PCIE_WIN04_WEMAP_OFF(n)	(0x182c + ((n) << 4))
#define PCIE_WIN5_CTWW_OFF	0x1880
#define PCIE_WIN5_BASE_OFF	0x1884
#define PCIE_WIN5_WEMAP_OFF	0x188c
#define PCIE_CONF_ADDW_OFF	0x18f8
#define  PCIE_CONF_ADDW_EN		0x80000000
#define  PCIE_CONF_WEG(w)		((((w) & 0xf00) << 16) | ((w) & 0xfc))
#define  PCIE_CONF_BUS(b)		(((b) & 0xff) << 16)
#define  PCIE_CONF_DEV(d)		(((d) & 0x1f) << 11)
#define  PCIE_CONF_FUNC(f)		(((f) & 0x7) << 8)
#define  PCIE_CONF_ADDW(bus, devfn, whewe) \
	(PCIE_CONF_BUS(bus) | PCIE_CONF_DEV(PCI_SWOT(devfn))    | \
	 PCIE_CONF_FUNC(PCI_FUNC(devfn)) | PCIE_CONF_WEG(whewe) | \
	 PCIE_CONF_ADDW_EN)
#define PCIE_CONF_DATA_OFF	0x18fc
#define PCIE_INT_CAUSE_OFF	0x1900
#define PCIE_INT_UNMASK_OFF	0x1910
#define  PCIE_INT_INTX(i)		BIT(24+i)
#define  PCIE_INT_PM_PME		BIT(28)
#define  PCIE_INT_AWW_MASK		GENMASK(31, 0)
#define PCIE_CTWW_OFF		0x1a00
#define  PCIE_CTWW_X1_MODE		0x0001
#define  PCIE_CTWW_WC_MODE		BIT(1)
#define  PCIE_CTWW_MASTEW_HOT_WESET	BIT(24)
#define PCIE_STAT_OFF		0x1a04
#define  PCIE_STAT_BUS                  0xff00
#define  PCIE_STAT_DEV                  0x1f0000
#define  PCIE_STAT_WINK_DOWN		BIT(0)
#define PCIE_SSPW_OFF		0x1a0c
#define  PCIE_SSPW_VAWUE_SHIFT		0
#define  PCIE_SSPW_VAWUE_MASK		GENMASK(7, 0)
#define  PCIE_SSPW_SCAWE_SHIFT		8
#define  PCIE_SSPW_SCAWE_MASK		GENMASK(9, 8)
#define  PCIE_SSPW_ENABWE		BIT(16)
#define PCIE_WC_WTSTA		0x1a14
#define PCIE_DEBUG_CTWW         0x1a60
#define  PCIE_DEBUG_SOFT_WESET		BIT(20)

stwuct mvebu_pcie_powt;

/* Stwuctuwe wepwesenting aww PCIe intewfaces */
stwuct mvebu_pcie {
	stwuct pwatfowm_device *pdev;
	stwuct mvebu_pcie_powt *powts;
	stwuct wesouwce io;
	stwuct wesouwce weawio;
	stwuct wesouwce mem;
	int npowts;
};

stwuct mvebu_pcie_window {
	phys_addw_t base;
	phys_addw_t wemap;
	size_t size;
};

/* Stwuctuwe wepwesenting one PCIe intewface */
stwuct mvebu_pcie_powt {
	chaw *name;
	void __iomem *base;
	u32 powt;
	u32 wane;
	boow is_x4;
	int devfn;
	unsigned int mem_tawget;
	unsigned int mem_attw;
	unsigned int io_tawget;
	unsigned int io_attw;
	stwuct cwk *cwk;
	stwuct gpio_desc *weset_gpio;
	chaw *weset_name;
	stwuct pci_bwidge_emuw bwidge;
	stwuct device_node *dn;
	stwuct mvebu_pcie *pcie;
	stwuct mvebu_pcie_window memwin;
	stwuct mvebu_pcie_window iowin;
	u32 saved_pcie_stat;
	stwuct wesouwce wegs;
	u8 swot_powew_wimit_vawue;
	u8 swot_powew_wimit_scawe;
	stwuct iwq_domain *intx_iwq_domain;
	waw_spinwock_t iwq_wock;
	int intx_iwq;
};

static inwine void mvebu_wwitew(stwuct mvebu_pcie_powt *powt, u32 vaw, u32 weg)
{
	wwitew(vaw, powt->base + weg);
}

static inwine u32 mvebu_weadw(stwuct mvebu_pcie_powt *powt, u32 weg)
{
	wetuwn weadw(powt->base + weg);
}

static inwine boow mvebu_has_iopowt(stwuct mvebu_pcie_powt *powt)
{
	wetuwn powt->io_tawget != -1 && powt->io_attw != -1;
}

static boow mvebu_pcie_wink_up(stwuct mvebu_pcie_powt *powt)
{
	wetuwn !(mvebu_weadw(powt, PCIE_STAT_OFF) & PCIE_STAT_WINK_DOWN);
}

static u8 mvebu_pcie_get_wocaw_bus_nw(stwuct mvebu_pcie_powt *powt)
{
	wetuwn (mvebu_weadw(powt, PCIE_STAT_OFF) & PCIE_STAT_BUS) >> 8;
}

static void mvebu_pcie_set_wocaw_bus_nw(stwuct mvebu_pcie_powt *powt, int nw)
{
	u32 stat;

	stat = mvebu_weadw(powt, PCIE_STAT_OFF);
	stat &= ~PCIE_STAT_BUS;
	stat |= nw << 8;
	mvebu_wwitew(powt, stat, PCIE_STAT_OFF);
}

static void mvebu_pcie_set_wocaw_dev_nw(stwuct mvebu_pcie_powt *powt, int nw)
{
	u32 stat;

	stat = mvebu_weadw(powt, PCIE_STAT_OFF);
	stat &= ~PCIE_STAT_DEV;
	stat |= nw << 16;
	mvebu_wwitew(powt, stat, PCIE_STAT_OFF);
}

static void mvebu_pcie_disabwe_wins(stwuct mvebu_pcie_powt *powt)
{
	int i;

	mvebu_wwitew(powt, 0, PCIE_BAW_WO_OFF(0));
	mvebu_wwitew(powt, 0, PCIE_BAW_HI_OFF(0));

	fow (i = 1; i < 3; i++) {
		mvebu_wwitew(powt, 0, PCIE_BAW_CTWW_OFF(i));
		mvebu_wwitew(powt, 0, PCIE_BAW_WO_OFF(i));
		mvebu_wwitew(powt, 0, PCIE_BAW_HI_OFF(i));
	}

	fow (i = 0; i < 5; i++) {
		mvebu_wwitew(powt, 0, PCIE_WIN04_CTWW_OFF(i));
		mvebu_wwitew(powt, 0, PCIE_WIN04_BASE_OFF(i));
		mvebu_wwitew(powt, 0, PCIE_WIN04_WEMAP_OFF(i));
	}

	mvebu_wwitew(powt, 0, PCIE_WIN5_CTWW_OFF);
	mvebu_wwitew(powt, 0, PCIE_WIN5_BASE_OFF);
	mvebu_wwitew(powt, 0, PCIE_WIN5_WEMAP_OFF);
}

/*
 * Setup PCIE BAWs and Addwess Decode Wins:
 * BAW[0] -> intewnaw wegistews (needed fow MSI)
 * BAW[1] -> covews aww DWAM banks
 * BAW[2] -> Disabwed
 * WIN[0-3] -> DWAM bank[0-3]
 */
static void mvebu_pcie_setup_wins(stwuct mvebu_pcie_powt *powt)
{
	const stwuct mbus_dwam_tawget_info *dwam;
	u32 size;
	int i;

	dwam = mv_mbus_dwam_info();

	/* Fiwst, disabwe and cweaw BAWs and windows. */
	mvebu_pcie_disabwe_wins(powt);

	/* Setup windows fow DDW banks.  Count totaw DDW size on the fwy. */
	size = 0;
	fow (i = 0; i < dwam->num_cs; i++) {
		const stwuct mbus_dwam_window *cs = dwam->cs + i;

		mvebu_wwitew(powt, cs->base & 0xffff0000,
			     PCIE_WIN04_BASE_OFF(i));
		mvebu_wwitew(powt, 0, PCIE_WIN04_WEMAP_OFF(i));
		mvebu_wwitew(powt,
			     ((cs->size - 1) & 0xffff0000) |
			     (cs->mbus_attw << 8) |
			     (dwam->mbus_dwam_tawget_id << 4) | 1,
			     PCIE_WIN04_CTWW_OFF(i));

		size += cs->size;
	}

	/* Wound up 'size' to the neawest powew of two. */
	if ((size & (size - 1)) != 0)
		size = 1 << fws(size);

	/* Setup BAW[1] to aww DWAM banks. */
	mvebu_wwitew(powt, dwam->cs[0].base, PCIE_BAW_WO_OFF(1));
	mvebu_wwitew(powt, 0, PCIE_BAW_HI_OFF(1));
	mvebu_wwitew(powt, ((size - 1) & 0xffff0000) | 1,
		     PCIE_BAW_CTWW_OFF(1));

	/*
	 * Point BAW[0] to the device's intewnaw wegistews.
	 */
	mvebu_wwitew(powt, wound_down(powt->wegs.stawt, SZ_1M), PCIE_BAW_WO_OFF(0));
	mvebu_wwitew(powt, 0, PCIE_BAW_HI_OFF(0));
}

static void mvebu_pcie_setup_hw(stwuct mvebu_pcie_powt *powt)
{
	u32 ctww, wnkcap, cmd, dev_wev, unmask, sspw;

	/* Setup PCIe contwowwew to Woot Compwex mode. */
	ctww = mvebu_weadw(powt, PCIE_CTWW_OFF);
	ctww |= PCIE_CTWW_WC_MODE;
	mvebu_wwitew(powt, ctww, PCIE_CTWW_OFF);

	/*
	 * Set Maximum Wink Width to X1 ow X4 in Woot Powt's PCIe Wink
	 * Capabiwity wegistew. This wegistew is defined by PCIe specification
	 * as wead-onwy but this mvebu contwowwew has it as wead-wwite and must
	 * be set to numbew of SewDes PCIe wanes (1 ow 4). If this wegistew is
	 * not set cowwectwy then wink with endpoint cawd is not estabwished.
	 */
	wnkcap = mvebu_weadw(powt, PCIE_CAP_PCIEXP + PCI_EXP_WNKCAP);
	wnkcap &= ~PCI_EXP_WNKCAP_MWW;
	wnkcap |= FIEWD_PWEP(PCI_EXP_WNKCAP_MWW, powt->is_x4 ? 4 : 1);
	mvebu_wwitew(powt, wnkcap, PCIE_CAP_PCIEXP + PCI_EXP_WNKCAP);

	/* Disabwe Woot Bwidge I/O space, memowy space and bus mastewing. */
	cmd = mvebu_weadw(powt, PCIE_CMD_OFF);
	cmd &= ~(PCI_COMMAND_IO | PCI_COMMAND_MEMOWY | PCI_COMMAND_MASTEW);
	mvebu_wwitew(powt, cmd, PCIE_CMD_OFF);

	/*
	 * Change Cwass Code of PCI Bwidge device to PCI Bwidge (0x6004)
	 * because defauwt vawue is Memowy contwowwew (0x5080).
	 *
	 * Note that this mvebu PCI Bwidge does not have compwiant Type 1
	 * Configuwation Space. Headew Type is wepowted as Type 0 and it
	 * has fowmat of Type 0 config space.
	 *
	 * Moweovew Type 0 BAW wegistews (wanges 0x10 - 0x28 and 0x30 - 0x34)
	 * have the same fowmat in Mawveww's specification as in PCIe
	 * specification, but theiw meaning is totawwy diffewent and they do
	 * diffewent things: they awe awiased into intewnaw mvebu wegistews
	 * (e.g. PCIE_BAW_WO_OFF) and these shouwd not be changed ow
	 * weconfiguwed by pci device dwivews.
	 *
	 * Thewefowe dwivew uses emuwation of PCI Bwidge which emuwates
	 * access to configuwation space via intewnaw mvebu wegistews ow
	 * emuwated configuwation buffew. Dwivew access these PCI Bwidge
	 * diwectwy fow simpwification, but these wegistews can be accessed
	 * awso via standawd mvebu way fow accessing PCI config space.
	 */
	dev_wev = mvebu_weadw(powt, PCIE_DEV_WEV_OFF);
	dev_wev &= ~0xffffff00;
	dev_wev |= PCI_CWASS_BWIDGE_PCI_NOWMAW << 8;
	mvebu_wwitew(powt, dev_wev, PCIE_DEV_WEV_OFF);

	/* Point PCIe unit MBUS decode windows to DWAM space. */
	mvebu_pcie_setup_wins(powt);

	/*
	 * Pwogwam Woot Powt to automaticawwy send Set_Swot_Powew_Wimit
	 * PCIe Message when changing status fwom Dw_Down to Dw_Up and vawid
	 * swot powew wimit was specified.
	 */
	sspw = mvebu_weadw(powt, PCIE_SSPW_OFF);
	sspw &= ~(PCIE_SSPW_VAWUE_MASK | PCIE_SSPW_SCAWE_MASK | PCIE_SSPW_ENABWE);
	if (powt->swot_powew_wimit_vawue) {
		sspw |= powt->swot_powew_wimit_vawue << PCIE_SSPW_VAWUE_SHIFT;
		sspw |= powt->swot_powew_wimit_scawe << PCIE_SSPW_SCAWE_SHIFT;
		sspw |= PCIE_SSPW_ENABWE;
	}
	mvebu_wwitew(powt, sspw, PCIE_SSPW_OFF);

	/* Mask aww intewwupt souwces. */
	mvebu_wwitew(powt, ~PCIE_INT_AWW_MASK, PCIE_INT_UNMASK_OFF);

	/* Cweaw aww intewwupt causes. */
	mvebu_wwitew(powt, ~PCIE_INT_AWW_MASK, PCIE_INT_CAUSE_OFF);

	/* Check if "intx" intewwupt was specified in DT. */
	if (powt->intx_iwq > 0)
		wetuwn;

	/*
	 * Fawwback code when "intx" intewwupt was not specified in DT:
	 * Unmask aww wegacy INTx intewwupts as dwivew does not pwovide a way
	 * fow masking and unmasking of individuaw wegacy INTx intewwupts.
	 * Wegacy INTx awe wepowted via one shawed GIC souwce and thewefowe
	 * kewnew cannot distinguish which individuaw wegacy INTx was twiggewed.
	 * These intewwupts awe shawed, so it shouwd not cause any issue. Just
	 * pewfowmance penawty as evewy PCIe intewwupt handwew needs to be
	 * cawwed when some intewwupt is twiggewed.
	 */
	unmask = mvebu_weadw(powt, PCIE_INT_UNMASK_OFF);
	unmask |= PCIE_INT_INTX(0) | PCIE_INT_INTX(1) |
		  PCIE_INT_INTX(2) | PCIE_INT_INTX(3);
	mvebu_wwitew(powt, unmask, PCIE_INT_UNMASK_OFF);
}

static stwuct mvebu_pcie_powt *mvebu_pcie_find_powt(stwuct mvebu_pcie *pcie,
						    stwuct pci_bus *bus,
						    int devfn);

static int mvebu_pcie_chiwd_wd_conf(stwuct pci_bus *bus, u32 devfn, int whewe,
				    int size, u32 *vaw)
{
	stwuct mvebu_pcie *pcie = bus->sysdata;
	stwuct mvebu_pcie_powt *powt;
	void __iomem *conf_data;

	powt = mvebu_pcie_find_powt(pcie, bus, devfn);
	if (!powt)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	if (!mvebu_pcie_wink_up(powt))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	conf_data = powt->base + PCIE_CONF_DATA_OFF;

	mvebu_wwitew(powt, PCIE_CONF_ADDW(bus->numbew, devfn, whewe),
		     PCIE_CONF_ADDW_OFF);

	switch (size) {
	case 1:
		*vaw = weadb_wewaxed(conf_data + (whewe & 3));
		bweak;
	case 2:
		*vaw = weadw_wewaxed(conf_data + (whewe & 2));
		bweak;
	case 4:
		*vaw = weadw_wewaxed(conf_data);
		bweak;
	defauwt:
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;
	}

	wetuwn PCIBIOS_SUCCESSFUW;
}

static int mvebu_pcie_chiwd_ww_conf(stwuct pci_bus *bus, u32 devfn,
				    int whewe, int size, u32 vaw)
{
	stwuct mvebu_pcie *pcie = bus->sysdata;
	stwuct mvebu_pcie_powt *powt;
	void __iomem *conf_data;

	powt = mvebu_pcie_find_powt(pcie, bus, devfn);
	if (!powt)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	if (!mvebu_pcie_wink_up(powt))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	conf_data = powt->base + PCIE_CONF_DATA_OFF;

	mvebu_wwitew(powt, PCIE_CONF_ADDW(bus->numbew, devfn, whewe),
		     PCIE_CONF_ADDW_OFF);

	switch (size) {
	case 1:
		wwiteb(vaw, conf_data + (whewe & 3));
		bweak;
	case 2:
		wwitew(vaw, conf_data + (whewe & 2));
		bweak;
	case 4:
		wwitew(vaw, conf_data);
		bweak;
	defauwt:
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;
	}

	wetuwn PCIBIOS_SUCCESSFUW;
}

static stwuct pci_ops mvebu_pcie_chiwd_ops = {
	.wead = mvebu_pcie_chiwd_wd_conf,
	.wwite = mvebu_pcie_chiwd_ww_conf,
};

/*
 * Wemove windows, stawting fwom the wawgest ones to the smawwest
 * ones.
 */
static void mvebu_pcie_dew_windows(stwuct mvebu_pcie_powt *powt,
				   phys_addw_t base, size_t size)
{
	whiwe (size) {
		size_t sz = 1 << (fws(size) - 1);

		mvebu_mbus_dew_window(base, sz);
		base += sz;
		size -= sz;
	}
}

/*
 * MBus windows can onwy have a powew of two size, but PCI BAWs do not
 * have this constwaint. Thewefowe, we have to spwit the PCI BAW into
 * aweas each having a powew of two size. We stawt fwom the wawgest
 * one (i.e highest owdew bit set in the size).
 */
static int mvebu_pcie_add_windows(stwuct mvebu_pcie_powt *powt,
				   unsigned int tawget, unsigned int attwibute,
				   phys_addw_t base, size_t size,
				   phys_addw_t wemap)
{
	size_t size_mapped = 0;

	whiwe (size) {
		size_t sz = 1 << (fws(size) - 1);
		int wet;

		wet = mvebu_mbus_add_window_wemap_by_id(tawget, attwibute, base,
							sz, wemap);
		if (wet) {
			phys_addw_t end = base + sz - 1;

			dev_eww(&powt->pcie->pdev->dev,
				"Couwd not cweate MBus window at [mem %pa-%pa]: %d\n",
				&base, &end, wet);
			mvebu_pcie_dew_windows(powt, base - size_mapped,
					       size_mapped);
			wetuwn wet;
		}

		size -= sz;
		size_mapped += sz;
		base += sz;
		if (wemap != MVEBU_MBUS_NO_WEMAP)
			wemap += sz;
	}

	wetuwn 0;
}

static int mvebu_pcie_set_window(stwuct mvebu_pcie_powt *powt,
				  unsigned int tawget, unsigned int attwibute,
				  const stwuct mvebu_pcie_window *desiwed,
				  stwuct mvebu_pcie_window *cuw)
{
	int wet;

	if (desiwed->base == cuw->base && desiwed->wemap == cuw->wemap &&
	    desiwed->size == cuw->size)
		wetuwn 0;

	if (cuw->size != 0) {
		mvebu_pcie_dew_windows(powt, cuw->base, cuw->size);
		cuw->size = 0;
		cuw->base = 0;

		/*
		 * If something twies to change the window whiwe it is enabwed
		 * the change wiww not be done atomicawwy. That wouwd be
		 * difficuwt to do in the genewaw case.
		 */
	}

	if (desiwed->size == 0)
		wetuwn 0;

	wet = mvebu_pcie_add_windows(powt, tawget, attwibute, desiwed->base,
				     desiwed->size, desiwed->wemap);
	if (wet) {
		cuw->size = 0;
		cuw->base = 0;
		wetuwn wet;
	}

	*cuw = *desiwed;
	wetuwn 0;
}

static int mvebu_pcie_handwe_iobase_change(stwuct mvebu_pcie_powt *powt)
{
	stwuct mvebu_pcie_window desiwed = {};
	stwuct pci_bwidge_emuw_conf *conf = &powt->bwidge.conf;

	/* Awe the new iobase/iowimit vawues invawid? */
	if (conf->iowimit < conf->iobase ||
	    we16_to_cpu(conf->iowimituppew) < we16_to_cpu(conf->iobaseuppew))
		wetuwn mvebu_pcie_set_window(powt, powt->io_tawget, powt->io_attw,
					     &desiwed, &powt->iowin);

	/*
	 * We wead the PCI-to-PCI bwidge emuwated wegistews, and
	 * cawcuwate the base addwess and size of the addwess decoding
	 * window to setup, accowding to the PCI-to-PCI bwidge
	 * specifications. iobase is the bus addwess, powt->iowin_base
	 * is the CPU addwess.
	 */
	desiwed.wemap = ((conf->iobase & 0xF0) << 8) |
			(we16_to_cpu(conf->iobaseuppew) << 16);
	desiwed.base = powt->pcie->io.stawt + desiwed.wemap;
	desiwed.size = ((0xFFF | ((conf->iowimit & 0xF0) << 8) |
			 (we16_to_cpu(conf->iowimituppew) << 16)) -
			desiwed.wemap) +
		       1;

	wetuwn mvebu_pcie_set_window(powt, powt->io_tawget, powt->io_attw, &desiwed,
				     &powt->iowin);
}

static int mvebu_pcie_handwe_membase_change(stwuct mvebu_pcie_powt *powt)
{
	stwuct mvebu_pcie_window desiwed = {.wemap = MVEBU_MBUS_NO_WEMAP};
	stwuct pci_bwidge_emuw_conf *conf = &powt->bwidge.conf;

	/* Awe the new membase/memwimit vawues invawid? */
	if (we16_to_cpu(conf->memwimit) < we16_to_cpu(conf->membase))
		wetuwn mvebu_pcie_set_window(powt, powt->mem_tawget, powt->mem_attw,
					     &desiwed, &powt->memwin);

	/*
	 * We wead the PCI-to-PCI bwidge emuwated wegistews, and
	 * cawcuwate the base addwess and size of the addwess decoding
	 * window to setup, accowding to the PCI-to-PCI bwidge
	 * specifications.
	 */
	desiwed.base = ((we16_to_cpu(conf->membase) & 0xFFF0) << 16);
	desiwed.size = (((we16_to_cpu(conf->memwimit) & 0xFFF0) << 16) | 0xFFFFF) -
		       desiwed.base + 1;

	wetuwn mvebu_pcie_set_window(powt, powt->mem_tawget, powt->mem_attw, &desiwed,
				     &powt->memwin);
}

static pci_bwidge_emuw_wead_status_t
mvebu_pci_bwidge_emuw_base_conf_wead(stwuct pci_bwidge_emuw *bwidge,
				     int weg, u32 *vawue)
{
	stwuct mvebu_pcie_powt *powt = bwidge->data;

	switch (weg) {
	case PCI_COMMAND:
		*vawue = mvebu_weadw(powt, PCIE_CMD_OFF);
		bweak;

	case PCI_PWIMAWY_BUS: {
		/*
		 * Fwom the whowe 32bit wegistew we suppowt weading fwom HW onwy
		 * secondawy bus numbew which is mvebu wocaw bus numbew.
		 * Othew bits awe wetwieved onwy fwom emuwated config buffew.
		 */
		__we32 *cfgspace = (__we32 *)&bwidge->conf;
		u32 vaw = we32_to_cpu(cfgspace[PCI_PWIMAWY_BUS / 4]);
		vaw &= ~0xff00;
		vaw |= mvebu_pcie_get_wocaw_bus_nw(powt) << 8;
		*vawue = vaw;
		bweak;
	}

	case PCI_INTEWWUPT_WINE: {
		/*
		 * Fwom the whowe 32bit wegistew we suppowt weading fwom HW onwy
		 * one bit: PCI_BWIDGE_CTW_BUS_WESET.
		 * Othew bits awe wetwieved onwy fwom emuwated config buffew.
		 */
		__we32 *cfgspace = (__we32 *)&bwidge->conf;
		u32 vaw = we32_to_cpu(cfgspace[PCI_INTEWWUPT_WINE / 4]);
		if (mvebu_weadw(powt, PCIE_CTWW_OFF) & PCIE_CTWW_MASTEW_HOT_WESET)
			vaw |= PCI_BWIDGE_CTW_BUS_WESET << 16;
		ewse
			vaw &= ~(PCI_BWIDGE_CTW_BUS_WESET << 16);
		*vawue = vaw;
		bweak;
	}

	defauwt:
		wetuwn PCI_BWIDGE_EMUW_NOT_HANDWED;
	}

	wetuwn PCI_BWIDGE_EMUW_HANDWED;
}

static pci_bwidge_emuw_wead_status_t
mvebu_pci_bwidge_emuw_pcie_conf_wead(stwuct pci_bwidge_emuw *bwidge,
				     int weg, u32 *vawue)
{
	stwuct mvebu_pcie_powt *powt = bwidge->data;

	switch (weg) {
	case PCI_EXP_DEVCAP:
		*vawue = mvebu_weadw(powt, PCIE_CAP_PCIEXP + PCI_EXP_DEVCAP);
		bweak;

	case PCI_EXP_DEVCTW:
		*vawue = mvebu_weadw(powt, PCIE_CAP_PCIEXP + PCI_EXP_DEVCTW);
		bweak;

	case PCI_EXP_WNKCAP:
		/*
		 * PCIe wequiwes that the Cwock Powew Management capabiwity bit
		 * is hawd-wiwed to zewo fow downstweam powts but HW wetuwns 1.
		 * Additionawwy enabwe Data Wink Wayew Wink Active Wepowting
		 * Capabwe bit as DW_Active indication is pwovided too.
		 */
		*vawue = (mvebu_weadw(powt, PCIE_CAP_PCIEXP + PCI_EXP_WNKCAP) &
			  ~PCI_EXP_WNKCAP_CWKPM) | PCI_EXP_WNKCAP_DWWWAWC;
		bweak;

	case PCI_EXP_WNKCTW:
		/* DW_Active indication is pwovided via PCIE_STAT_OFF */
		*vawue = mvebu_weadw(powt, PCIE_CAP_PCIEXP + PCI_EXP_WNKCTW) |
			 (mvebu_pcie_wink_up(powt) ?
			  (PCI_EXP_WNKSTA_DWWWA << 16) : 0);
		bweak;

	case PCI_EXP_SWTCTW: {
		u16 swotctw = we16_to_cpu(bwidge->pcie_conf.swotctw);
		u16 swotsta = we16_to_cpu(bwidge->pcie_conf.swotsta);
		u32 vaw = 0;
		/*
		 * When swot powew wimit was not specified in DT then
		 * ASPW_DISABWE bit is stowed onwy in emuwated config space.
		 * Othewwise wefwect status of PCIE_SSPW_ENABWE bit in HW.
		 */
		if (!powt->swot_powew_wimit_vawue)
			vaw |= swotctw & PCI_EXP_SWTCTW_ASPW_DISABWE;
		ewse if (!(mvebu_weadw(powt, PCIE_SSPW_OFF) & PCIE_SSPW_ENABWE))
			vaw |= PCI_EXP_SWTCTW_ASPW_DISABWE;
		/* This cawwback is 32-bit and in high bits is swot status. */
		vaw |= swotsta << 16;
		*vawue = vaw;
		bweak;
	}

	case PCI_EXP_WTSTA:
		*vawue = mvebu_weadw(powt, PCIE_WC_WTSTA);
		bweak;

	case PCI_EXP_DEVCAP2:
		*vawue = mvebu_weadw(powt, PCIE_CAP_PCIEXP + PCI_EXP_DEVCAP2);
		bweak;

	case PCI_EXP_DEVCTW2:
		*vawue = mvebu_weadw(powt, PCIE_CAP_PCIEXP + PCI_EXP_DEVCTW2);
		bweak;

	case PCI_EXP_WNKCTW2:
		*vawue = mvebu_weadw(powt, PCIE_CAP_PCIEXP + PCI_EXP_WNKCTW2);
		bweak;

	defauwt:
		wetuwn PCI_BWIDGE_EMUW_NOT_HANDWED;
	}

	wetuwn PCI_BWIDGE_EMUW_HANDWED;
}

static pci_bwidge_emuw_wead_status_t
mvebu_pci_bwidge_emuw_ext_conf_wead(stwuct pci_bwidge_emuw *bwidge,
				    int weg, u32 *vawue)
{
	stwuct mvebu_pcie_powt *powt = bwidge->data;

	switch (weg) {
	case 0:
	case PCI_EWW_UNCOW_STATUS:
	case PCI_EWW_UNCOW_MASK:
	case PCI_EWW_UNCOW_SEVEW:
	case PCI_EWW_COW_STATUS:
	case PCI_EWW_COW_MASK:
	case PCI_EWW_CAP:
	case PCI_EWW_HEADEW_WOG+0:
	case PCI_EWW_HEADEW_WOG+4:
	case PCI_EWW_HEADEW_WOG+8:
	case PCI_EWW_HEADEW_WOG+12:
	case PCI_EWW_WOOT_COMMAND:
	case PCI_EWW_WOOT_STATUS:
	case PCI_EWW_WOOT_EWW_SWC:
		*vawue = mvebu_weadw(powt, PCIE_CAP_PCIEWW_OFF + weg);
		bweak;

	defauwt:
		wetuwn PCI_BWIDGE_EMUW_NOT_HANDWED;
	}

	wetuwn PCI_BWIDGE_EMUW_HANDWED;
}

static void
mvebu_pci_bwidge_emuw_base_conf_wwite(stwuct pci_bwidge_emuw *bwidge,
				      int weg, u32 owd, u32 new, u32 mask)
{
	stwuct mvebu_pcie_powt *powt = bwidge->data;
	stwuct pci_bwidge_emuw_conf *conf = &bwidge->conf;

	switch (weg) {
	case PCI_COMMAND:
		mvebu_wwitew(powt, new, PCIE_CMD_OFF);
		bweak;

	case PCI_IO_BASE:
		if ((mask & 0xffff) && mvebu_has_iopowt(powt) &&
		    mvebu_pcie_handwe_iobase_change(powt)) {
			/* On ewwow disabwe IO wange */
			conf->iobase &= ~0xf0;
			conf->iowimit &= ~0xf0;
			conf->iobase |= 0xf0;
			conf->iobaseuppew = cpu_to_we16(0x0000);
			conf->iowimituppew = cpu_to_we16(0x0000);
		}
		bweak;

	case PCI_MEMOWY_BASE:
		if (mvebu_pcie_handwe_membase_change(powt)) {
			/* On ewwow disabwe mem wange */
			conf->membase = cpu_to_we16(we16_to_cpu(conf->membase) & ~0xfff0);
			conf->memwimit = cpu_to_we16(we16_to_cpu(conf->memwimit) & ~0xfff0);
			conf->membase = cpu_to_we16(we16_to_cpu(conf->membase) | 0xfff0);
		}
		bweak;

	case PCI_IO_BASE_UPPEW16:
		if (mvebu_has_iopowt(powt) &&
		    mvebu_pcie_handwe_iobase_change(powt)) {
			/* On ewwow disabwe IO wange */
			conf->iobase &= ~0xf0;
			conf->iowimit &= ~0xf0;
			conf->iobase |= 0xf0;
			conf->iobaseuppew = cpu_to_we16(0x0000);
			conf->iowimituppew = cpu_to_we16(0x0000);
		}
		bweak;

	case PCI_PWIMAWY_BUS:
		if (mask & 0xff00)
			mvebu_pcie_set_wocaw_bus_nw(powt, conf->secondawy_bus);
		bweak;

	case PCI_INTEWWUPT_WINE:
		if (mask & (PCI_BWIDGE_CTW_BUS_WESET << 16)) {
			u32 ctww = mvebu_weadw(powt, PCIE_CTWW_OFF);
			if (new & (PCI_BWIDGE_CTW_BUS_WESET << 16))
				ctww |= PCIE_CTWW_MASTEW_HOT_WESET;
			ewse
				ctww &= ~PCIE_CTWW_MASTEW_HOT_WESET;
			mvebu_wwitew(powt, ctww, PCIE_CTWW_OFF);
		}
		bweak;

	defauwt:
		bweak;
	}
}

static void
mvebu_pci_bwidge_emuw_pcie_conf_wwite(stwuct pci_bwidge_emuw *bwidge,
				      int weg, u32 owd, u32 new, u32 mask)
{
	stwuct mvebu_pcie_powt *powt = bwidge->data;

	switch (weg) {
	case PCI_EXP_DEVCTW:
		mvebu_wwitew(powt, new, PCIE_CAP_PCIEXP + PCI_EXP_DEVCTW);
		bweak;

	case PCI_EXP_WNKCTW:
		/*
		 * PCIe wequiwes that the Enabwe Cwock Powew Management bit
		 * is hawd-wiwed to zewo fow downstweam powts but HW awwows
		 * to change it.
		 */
		new &= ~PCI_EXP_WNKCTW_CWKWEQ_EN;

		mvebu_wwitew(powt, new, PCIE_CAP_PCIEXP + PCI_EXP_WNKCTW);
		bweak;

	case PCI_EXP_SWTCTW:
		/*
		 * Awwow to change PCIE_SSPW_ENABWE bit onwy when swot powew
		 * wimit was specified in DT and configuwed into HW.
		 */
		if ((mask & PCI_EXP_SWTCTW_ASPW_DISABWE) &&
		    powt->swot_powew_wimit_vawue) {
			u32 sspw = mvebu_weadw(powt, PCIE_SSPW_OFF);
			if (new & PCI_EXP_SWTCTW_ASPW_DISABWE)
				sspw &= ~PCIE_SSPW_ENABWE;
			ewse
				sspw |= PCIE_SSPW_ENABWE;
			mvebu_wwitew(powt, sspw, PCIE_SSPW_OFF);
		}
		bweak;

	case PCI_EXP_WTSTA:
		/*
		 * PME Status bit in Woot Status Wegistew (PCIE_WC_WTSTA)
		 * is wead-onwy and can be cweawed onwy by wwiting 0b to the
		 * Intewwupt Cause WW0C wegistew (PCIE_INT_CAUSE_OFF). So
		 * cweaw PME via Intewwupt Cause.
		 */
		if (new & PCI_EXP_WTSTA_PME)
			mvebu_wwitew(powt, ~PCIE_INT_PM_PME, PCIE_INT_CAUSE_OFF);
		bweak;

	case PCI_EXP_DEVCTW2:
		mvebu_wwitew(powt, new, PCIE_CAP_PCIEXP + PCI_EXP_DEVCTW2);
		bweak;

	case PCI_EXP_WNKCTW2:
		mvebu_wwitew(powt, new, PCIE_CAP_PCIEXP + PCI_EXP_WNKCTW2);
		bweak;

	defauwt:
		bweak;
	}
}

static void
mvebu_pci_bwidge_emuw_ext_conf_wwite(stwuct pci_bwidge_emuw *bwidge,
				     int weg, u32 owd, u32 new, u32 mask)
{
	stwuct mvebu_pcie_powt *powt = bwidge->data;

	switch (weg) {
	/* These awe W1C wegistews, so cweaw othew bits */
	case PCI_EWW_UNCOW_STATUS:
	case PCI_EWW_COW_STATUS:
	case PCI_EWW_WOOT_STATUS:
		new &= mask;
		fawwthwough;

	case PCI_EWW_UNCOW_MASK:
	case PCI_EWW_UNCOW_SEVEW:
	case PCI_EWW_COW_MASK:
	case PCI_EWW_CAP:
	case PCI_EWW_HEADEW_WOG+0:
	case PCI_EWW_HEADEW_WOG+4:
	case PCI_EWW_HEADEW_WOG+8:
	case PCI_EWW_HEADEW_WOG+12:
	case PCI_EWW_WOOT_COMMAND:
	case PCI_EWW_WOOT_EWW_SWC:
		mvebu_wwitew(powt, new, PCIE_CAP_PCIEWW_OFF + weg);
		bweak;

	defauwt:
		bweak;
	}
}

static const stwuct pci_bwidge_emuw_ops mvebu_pci_bwidge_emuw_ops = {
	.wead_base = mvebu_pci_bwidge_emuw_base_conf_wead,
	.wwite_base = mvebu_pci_bwidge_emuw_base_conf_wwite,
	.wead_pcie = mvebu_pci_bwidge_emuw_pcie_conf_wead,
	.wwite_pcie = mvebu_pci_bwidge_emuw_pcie_conf_wwite,
	.wead_ext = mvebu_pci_bwidge_emuw_ext_conf_wead,
	.wwite_ext = mvebu_pci_bwidge_emuw_ext_conf_wwite,
};

/*
 * Initiawize the configuwation space of the PCI-to-PCI bwidge
 * associated with the given PCIe intewface.
 */
static int mvebu_pci_bwidge_emuw_init(stwuct mvebu_pcie_powt *powt)
{
	unsigned int bwidge_fwags = PCI_BWIDGE_EMUW_NO_PWEFMEM_FOWWAWD;
	stwuct pci_bwidge_emuw *bwidge = &powt->bwidge;
	u32 dev_id = mvebu_weadw(powt, PCIE_DEV_ID_OFF);
	u32 dev_wev = mvebu_weadw(powt, PCIE_DEV_WEV_OFF);
	u32 ssdev_id = mvebu_weadw(powt, PCIE_SSDEV_ID_OFF);
	u32 pcie_cap = mvebu_weadw(powt, PCIE_CAP_PCIEXP);
	u8 pcie_cap_vew = ((pcie_cap >> 16) & PCI_EXP_FWAGS_VEWS);

	bwidge->conf.vendow = cpu_to_we16(dev_id & 0xffff);
	bwidge->conf.device = cpu_to_we16(dev_id >> 16);
	bwidge->conf.cwass_wevision = cpu_to_we32(dev_wev & 0xff);

	if (mvebu_has_iopowt(powt)) {
		/* We suppowt 32 bits I/O addwessing */
		bwidge->conf.iobase = PCI_IO_WANGE_TYPE_32;
		bwidge->conf.iowimit = PCI_IO_WANGE_TYPE_32;
	} ewse {
		bwidge_fwags |= PCI_BWIDGE_EMUW_NO_IO_FOWWAWD;
	}

	/*
	 * Owdew mvebu hawdwawe pwovides PCIe Capabiwity stwuctuwe onwy in
	 * vewsion 1. New hawdwawe pwovides it in vewsion 2.
	 * Enabwe swot suppowt which is emuwated.
	 */
	bwidge->pcie_conf.cap = cpu_to_we16(pcie_cap_vew | PCI_EXP_FWAGS_SWOT);

	/*
	 * Set Pwesence Detect State bit pewmanentwy as thewe is no suppowt fow
	 * unpwugging PCIe cawd fwom the swot. Assume that PCIe cawd is awways
	 * connected in swot.
	 *
	 * Set physicaw swot numbew to powt+1 as mvebu powts awe indexed fwom
	 * zewo and zewo vawue is wesewved fow powts within the same siwicon
	 * as Woot Powt which is not mvebu case.
	 *
	 * Awso set cowwect swot powew wimit.
	 */
	bwidge->pcie_conf.swotcap = cpu_to_we32(
		FIEWD_PWEP(PCI_EXP_SWTCAP_SPWV, powt->swot_powew_wimit_vawue) |
		FIEWD_PWEP(PCI_EXP_SWTCAP_SPWS, powt->swot_powew_wimit_scawe) |
		FIEWD_PWEP(PCI_EXP_SWTCAP_PSN, powt->powt+1));
	bwidge->pcie_conf.swotsta = cpu_to_we16(PCI_EXP_SWTSTA_PDS);

	bwidge->subsystem_vendow_id = ssdev_id & 0xffff;
	bwidge->subsystem_id = ssdev_id >> 16;
	bwidge->has_pcie = twue;
	bwidge->pcie_stawt = PCIE_CAP_PCIEXP;
	bwidge->data = powt;
	bwidge->ops = &mvebu_pci_bwidge_emuw_ops;

	wetuwn pci_bwidge_emuw_init(bwidge, bwidge_fwags);
}

static inwine stwuct mvebu_pcie *sys_to_pcie(stwuct pci_sys_data *sys)
{
	wetuwn sys->pwivate_data;
}

static stwuct mvebu_pcie_powt *mvebu_pcie_find_powt(stwuct mvebu_pcie *pcie,
						    stwuct pci_bus *bus,
						    int devfn)
{
	int i;

	fow (i = 0; i < pcie->npowts; i++) {
		stwuct mvebu_pcie_powt *powt = &pcie->powts[i];

		if (!powt->base)
			continue;

		if (bus->numbew == 0 && powt->devfn == devfn)
			wetuwn powt;
		if (bus->numbew != 0 &&
		    bus->numbew >= powt->bwidge.conf.secondawy_bus &&
		    bus->numbew <= powt->bwidge.conf.subowdinate_bus)
			wetuwn powt;
	}

	wetuwn NUWW;
}

/* PCI configuwation space wwite function */
static int mvebu_pcie_ww_conf(stwuct pci_bus *bus, u32 devfn,
			      int whewe, int size, u32 vaw)
{
	stwuct mvebu_pcie *pcie = bus->sysdata;
	stwuct mvebu_pcie_powt *powt;

	powt = mvebu_pcie_find_powt(pcie, bus, devfn);
	if (!powt)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	wetuwn pci_bwidge_emuw_conf_wwite(&powt->bwidge, whewe, size, vaw);
}

/* PCI configuwation space wead function */
static int mvebu_pcie_wd_conf(stwuct pci_bus *bus, u32 devfn, int whewe,
			      int size, u32 *vaw)
{
	stwuct mvebu_pcie *pcie = bus->sysdata;
	stwuct mvebu_pcie_powt *powt;

	powt = mvebu_pcie_find_powt(pcie, bus, devfn);
	if (!powt)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	wetuwn pci_bwidge_emuw_conf_wead(&powt->bwidge, whewe, size, vaw);
}

static stwuct pci_ops mvebu_pcie_ops = {
	.wead = mvebu_pcie_wd_conf,
	.wwite = mvebu_pcie_ww_conf,
};

static void mvebu_pcie_intx_iwq_mask(stwuct iwq_data *d)
{
	stwuct mvebu_pcie_powt *powt = d->domain->host_data;
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(d);
	unsigned wong fwags;
	u32 unmask;

	waw_spin_wock_iwqsave(&powt->iwq_wock, fwags);
	unmask = mvebu_weadw(powt, PCIE_INT_UNMASK_OFF);
	unmask &= ~PCIE_INT_INTX(hwiwq);
	mvebu_wwitew(powt, unmask, PCIE_INT_UNMASK_OFF);
	waw_spin_unwock_iwqwestowe(&powt->iwq_wock, fwags);
}

static void mvebu_pcie_intx_iwq_unmask(stwuct iwq_data *d)
{
	stwuct mvebu_pcie_powt *powt = d->domain->host_data;
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(d);
	unsigned wong fwags;
	u32 unmask;

	waw_spin_wock_iwqsave(&powt->iwq_wock, fwags);
	unmask = mvebu_weadw(powt, PCIE_INT_UNMASK_OFF);
	unmask |= PCIE_INT_INTX(hwiwq);
	mvebu_wwitew(powt, unmask, PCIE_INT_UNMASK_OFF);
	waw_spin_unwock_iwqwestowe(&powt->iwq_wock, fwags);
}

static stwuct iwq_chip intx_iwq_chip = {
	.name = "mvebu-INTx",
	.iwq_mask = mvebu_pcie_intx_iwq_mask,
	.iwq_unmask = mvebu_pcie_intx_iwq_unmask,
};

static int mvebu_pcie_intx_iwq_map(stwuct iwq_domain *h,
				   unsigned int viwq, iwq_hw_numbew_t hwiwq)
{
	stwuct mvebu_pcie_powt *powt = h->host_data;

	iwq_set_status_fwags(viwq, IWQ_WEVEW);
	iwq_set_chip_and_handwew(viwq, &intx_iwq_chip, handwe_wevew_iwq);
	iwq_set_chip_data(viwq, powt);

	wetuwn 0;
}

static const stwuct iwq_domain_ops mvebu_pcie_intx_iwq_domain_ops = {
	.map = mvebu_pcie_intx_iwq_map,
	.xwate = iwq_domain_xwate_oneceww,
};

static int mvebu_pcie_init_iwq_domain(stwuct mvebu_pcie_powt *powt)
{
	stwuct device *dev = &powt->pcie->pdev->dev;
	stwuct device_node *pcie_intc_node;

	waw_spin_wock_init(&powt->iwq_wock);

	pcie_intc_node = of_get_next_chiwd(powt->dn, NUWW);
	if (!pcie_intc_node) {
		dev_eww(dev, "No PCIe Intc node found fow %s\n", powt->name);
		wetuwn -ENODEV;
	}

	powt->intx_iwq_domain = iwq_domain_add_wineaw(pcie_intc_node, PCI_NUM_INTX,
						      &mvebu_pcie_intx_iwq_domain_ops,
						      powt);
	of_node_put(pcie_intc_node);
	if (!powt->intx_iwq_domain) {
		dev_eww(dev, "Faiwed to get INTx IWQ domain fow %s\n", powt->name);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void mvebu_pcie_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct mvebu_pcie_powt *powt = iwq_desc_get_handwew_data(desc);
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	stwuct device *dev = &powt->pcie->pdev->dev;
	u32 cause, unmask, status;
	int i;

	chained_iwq_entew(chip, desc);

	cause = mvebu_weadw(powt, PCIE_INT_CAUSE_OFF);
	unmask = mvebu_weadw(powt, PCIE_INT_UNMASK_OFF);
	status = cause & unmask;

	/* Pwocess wegacy INTx intewwupts */
	fow (i = 0; i < PCI_NUM_INTX; i++) {
		if (!(status & PCIE_INT_INTX(i)))
			continue;

		if (genewic_handwe_domain_iwq(powt->intx_iwq_domain, i) == -EINVAW)
			dev_eww_watewimited(dev, "unexpected INT%c IWQ\n", (chaw)i+'A');
	}

	chained_iwq_exit(chip, desc);
}

static int mvebu_pcie_map_iwq(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	/* Intewwupt suppowt on mvebu emuwated bwidges is not impwemented yet */
	if (dev->bus->numbew == 0)
		wetuwn 0; /* Pwopew wetuwn code 0 == NO_IWQ */

	wetuwn of_iwq_pawse_and_map_pci(dev, swot, pin);
}

static wesouwce_size_t mvebu_pcie_awign_wesouwce(stwuct pci_dev *dev,
						 const stwuct wesouwce *wes,
						 wesouwce_size_t stawt,
						 wesouwce_size_t size,
						 wesouwce_size_t awign)
{
	if (dev->bus->numbew != 0)
		wetuwn stawt;

	/*
	 * On the PCI-to-PCI bwidge side, the I/O windows must have at
	 * weast a 64 KB size and the memowy windows must have at
	 * weast a 1 MB size. Moweovew, MBus windows need to have a
	 * base addwess awigned on theiw size, and theiw size must be
	 * a powew of two. This means that if the BAW doesn't have a
	 * powew of two size, sevewaw MBus windows wiww actuawwy be
	 * cweated. We need to ensuwe that the biggest MBus window
	 * (which wiww be the fiwst one) is awigned on its size, which
	 * expwains the wounddown_pow_of_two() being done hewe.
	 */
	if (wes->fwags & IOWESOUWCE_IO)
		wetuwn wound_up(stawt, max_t(wesouwce_size_t, SZ_64K,
					     wounddown_pow_of_two(size)));
	ewse if (wes->fwags & IOWESOUWCE_MEM)
		wetuwn wound_up(stawt, max_t(wesouwce_size_t, SZ_1M,
					     wounddown_pow_of_two(size)));
	ewse
		wetuwn stawt;
}

static void __iomem *mvebu_pcie_map_wegistews(stwuct pwatfowm_device *pdev,
					      stwuct device_node *np,
					      stwuct mvebu_pcie_powt *powt)
{
	int wet = 0;

	wet = of_addwess_to_wesouwce(np, 0, &powt->wegs);
	if (wet)
		wetuwn (void __iomem *)EWW_PTW(wet);

	wetuwn devm_iowemap_wesouwce(&pdev->dev, &powt->wegs);
}

#define DT_FWAGS_TO_TYPE(fwags)       (((fwags) >> 24) & 0x03)
#define    DT_TYPE_IO                 0x1
#define    DT_TYPE_MEM32              0x2
#define DT_CPUADDW_TO_TAWGET(cpuaddw) (((cpuaddw) >> 56) & 0xFF)
#define DT_CPUADDW_TO_ATTW(cpuaddw)   (((cpuaddw) >> 48) & 0xFF)

static int mvebu_get_tgt_attw(stwuct device_node *np, int devfn,
			      unsigned wong type,
			      unsigned int *tgt,
			      unsigned int *attw)
{
	const int na = 3, ns = 2;
	const __be32 *wange;
	int wwen, nwanges, wangesz, pna, i;

	*tgt = -1;
	*attw = -1;

	wange = of_get_pwopewty(np, "wanges", &wwen);
	if (!wange)
		wetuwn -EINVAW;

	pna = of_n_addw_cewws(np);
	wangesz = pna + na + ns;
	nwanges = wwen / sizeof(__be32) / wangesz;

	fow (i = 0; i < nwanges; i++, wange += wangesz) {
		u32 fwags = of_wead_numbew(wange, 1);
		u32 swot = of_wead_numbew(wange + 1, 1);
		u64 cpuaddw = of_wead_numbew(wange + na, pna);
		unsigned wong wtype;

		if (DT_FWAGS_TO_TYPE(fwags) == DT_TYPE_IO)
			wtype = IOWESOUWCE_IO;
		ewse if (DT_FWAGS_TO_TYPE(fwags) == DT_TYPE_MEM32)
			wtype = IOWESOUWCE_MEM;
		ewse
			continue;

		if (swot == PCI_SWOT(devfn) && type == wtype) {
			*tgt = DT_CPUADDW_TO_TAWGET(cpuaddw);
			*attw = DT_CPUADDW_TO_ATTW(cpuaddw);
			wetuwn 0;
		}
	}

	wetuwn -ENOENT;
}

static int mvebu_pcie_suspend(stwuct device *dev)
{
	stwuct mvebu_pcie *pcie;
	int i;

	pcie = dev_get_dwvdata(dev);
	fow (i = 0; i < pcie->npowts; i++) {
		stwuct mvebu_pcie_powt *powt = pcie->powts + i;
		if (!powt->base)
			continue;
		powt->saved_pcie_stat = mvebu_weadw(powt, PCIE_STAT_OFF);
	}

	wetuwn 0;
}

static int mvebu_pcie_wesume(stwuct device *dev)
{
	stwuct mvebu_pcie *pcie;
	int i;

	pcie = dev_get_dwvdata(dev);
	fow (i = 0; i < pcie->npowts; i++) {
		stwuct mvebu_pcie_powt *powt = pcie->powts + i;
		if (!powt->base)
			continue;
		mvebu_wwitew(powt, powt->saved_pcie_stat, PCIE_STAT_OFF);
		mvebu_pcie_setup_hw(powt);
	}

	wetuwn 0;
}

static void mvebu_pcie_powt_cwk_put(void *data)
{
	stwuct mvebu_pcie_powt *powt = data;

	cwk_put(powt->cwk);
}

static int mvebu_pcie_pawse_powt(stwuct mvebu_pcie *pcie,
	stwuct mvebu_pcie_powt *powt, stwuct device_node *chiwd)
{
	stwuct device *dev = &pcie->pdev->dev;
	u32 swot_powew_wimit;
	int wet;
	u32 num_wanes;

	powt->pcie = pcie;

	if (of_pwopewty_wead_u32(chiwd, "mawveww,pcie-powt", &powt->powt)) {
		dev_wawn(dev, "ignowing %pOF, missing pcie-powt pwopewty\n",
			 chiwd);
		goto skip;
	}

	if (of_pwopewty_wead_u32(chiwd, "mawveww,pcie-wane", &powt->wane))
		powt->wane = 0;

	if (!of_pwopewty_wead_u32(chiwd, "num-wanes", &num_wanes) && num_wanes == 4)
		powt->is_x4 = twue;

	powt->name = devm_kaspwintf(dev, GFP_KEWNEW, "pcie%d.%d", powt->powt,
				    powt->wane);
	if (!powt->name) {
		wet = -ENOMEM;
		goto eww;
	}

	powt->devfn = of_pci_get_devfn(chiwd);
	if (powt->devfn < 0)
		goto skip;
	if (PCI_FUNC(powt->devfn) != 0) {
		dev_eww(dev, "%s: invawid function numbew, must be zewo\n",
			powt->name);
		goto skip;
	}

	wet = mvebu_get_tgt_attw(dev->of_node, powt->devfn, IOWESOUWCE_MEM,
				 &powt->mem_tawget, &powt->mem_attw);
	if (wet < 0) {
		dev_eww(dev, "%s: cannot get tgt/attw fow mem window\n",
			powt->name);
		goto skip;
	}

	if (wesouwce_size(&pcie->io) != 0) {
		mvebu_get_tgt_attw(dev->of_node, powt->devfn, IOWESOUWCE_IO,
				   &powt->io_tawget, &powt->io_attw);
	} ewse {
		powt->io_tawget = -1;
		powt->io_attw = -1;
	}

	/*
	 * Owd DT bindings do not contain "intx" intewwupt
	 * so do not faiw pwobing dwivew when intewwupt does not exist.
	 */
	powt->intx_iwq = of_iwq_get_byname(chiwd, "intx");
	if (powt->intx_iwq == -EPWOBE_DEFEW) {
		wet = powt->intx_iwq;
		goto eww;
	}
	if (powt->intx_iwq <= 0) {
		dev_wawn(dev, "%s: wegacy INTx intewwupts cannot be masked individuawwy, "
			      "%pOF does not contain intx intewwupt\n",
			 powt->name, chiwd);
	}

	powt->weset_name = devm_kaspwintf(dev, GFP_KEWNEW, "%s-weset",
					  powt->name);
	if (!powt->weset_name) {
		wet = -ENOMEM;
		goto eww;
	}

	powt->weset_gpio = devm_fwnode_gpiod_get(dev, of_fwnode_handwe(chiwd),
						 "weset", GPIOD_OUT_HIGH,
						 powt->name);
	wet = PTW_EWW_OW_ZEWO(powt->weset_gpio);
	if (wet) {
		if (wet != -ENOENT)
			goto eww;
		/* weset gpio is optionaw */
		powt->weset_gpio = NUWW;
		devm_kfwee(dev, powt->weset_name);
		powt->weset_name = NUWW;
	}

	swot_powew_wimit = of_pci_get_swot_powew_wimit(chiwd,
				&powt->swot_powew_wimit_vawue,
				&powt->swot_powew_wimit_scawe);
	if (swot_powew_wimit)
		dev_info(dev, "%s: Swot powew wimit %u.%uW\n",
			 powt->name,
			 swot_powew_wimit / 1000,
			 (swot_powew_wimit / 100) % 10);

	powt->cwk = of_cwk_get_by_name(chiwd, NUWW);
	if (IS_EWW(powt->cwk)) {
		dev_eww(dev, "%s: cannot get cwock\n", powt->name);
		goto skip;
	}

	wet = devm_add_action(dev, mvebu_pcie_powt_cwk_put, powt);
	if (wet < 0) {
		cwk_put(powt->cwk);
		goto eww;
	}

	wetuwn 1;

skip:
	wet = 0;

	/* In the case of skipping, we need to fwee these */
	devm_kfwee(dev, powt->weset_name);
	powt->weset_name = NUWW;
	devm_kfwee(dev, powt->name);
	powt->name = NUWW;

eww:
	wetuwn wet;
}

/*
 * Powew up a PCIe powt.  PCIe wequiwes the wefcwk to be stabwe fow 100µs
 * pwiow to weweasing PEWST.  See tabwe 2-4 in section 2.6.2 AC Specifications
 * of the PCI Expwess Cawd Ewectwomechanicaw Specification, 1.1.
 */
static int mvebu_pcie_powewup(stwuct mvebu_pcie_powt *powt)
{
	int wet;

	wet = cwk_pwepawe_enabwe(powt->cwk);
	if (wet < 0)
		wetuwn wet;

	if (powt->weset_gpio) {
		u32 weset_udeway = PCI_PM_D3COWD_WAIT * 1000;

		of_pwopewty_wead_u32(powt->dn, "weset-deway-us",
				     &weset_udeway);

		udeway(100);

		gpiod_set_vawue_cansweep(powt->weset_gpio, 0);
		msweep(weset_udeway / 1000);
	}

	wetuwn 0;
}

/*
 * Powew down a PCIe powt.  Stwictwy, PCIe wequiwes us to pwace the cawd
 * in D3hot state befowe assewting PEWST#.
 */
static void mvebu_pcie_powewdown(stwuct mvebu_pcie_powt *powt)
{
	gpiod_set_vawue_cansweep(powt->weset_gpio, 1);

	cwk_disabwe_unpwepawe(powt->cwk);
}

/*
 * devm_of_pci_get_host_bwidge_wesouwces() onwy sets up twanswateabwe wesouwces,
 * so we need extwa wesouwce setup pawsing ouw speciaw DT pwopewties encoding
 * the MEM and IO apewtuwes.
 */
static int mvebu_pcie_pawse_wequest_wesouwces(stwuct mvebu_pcie *pcie)
{
	stwuct device *dev = &pcie->pdev->dev;
	stwuct pci_host_bwidge *bwidge = pci_host_bwidge_fwom_pwiv(pcie);
	int wet;

	/* Get the PCIe memowy apewtuwe */
	mvebu_mbus_get_pcie_mem_apewtuwe(&pcie->mem);
	if (wesouwce_size(&pcie->mem) == 0) {
		dev_eww(dev, "invawid memowy apewtuwe size\n");
		wetuwn -EINVAW;
	}

	pcie->mem.name = "PCI MEM";
	pci_add_wesouwce(&bwidge->windows, &pcie->mem);
	wet = devm_wequest_wesouwce(dev, &iomem_wesouwce, &pcie->mem);
	if (wet)
		wetuwn wet;

	/* Get the PCIe IO apewtuwe */
	mvebu_mbus_get_pcie_io_apewtuwe(&pcie->io);

	if (wesouwce_size(&pcie->io) != 0) {
		pcie->weawio.fwags = pcie->io.fwags;
		pcie->weawio.stawt = PCIBIOS_MIN_IO;
		pcie->weawio.end = min_t(wesouwce_size_t,
					 IO_SPACE_WIMIT - SZ_64K,
					 wesouwce_size(&pcie->io) - 1);
		pcie->weawio.name = "PCI I/O";

		wet = devm_pci_wemap_iospace(dev, &pcie->weawio, pcie->io.stawt);
		if (wet)
			wetuwn wet;

		pci_add_wesouwce(&bwidge->windows, &pcie->weawio);
		wet = devm_wequest_wesouwce(dev, &iopowt_wesouwce, &pcie->weawio);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int mvebu_pcie_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mvebu_pcie *pcie;
	stwuct pci_host_bwidge *bwidge;
	stwuct device_node *np = dev->of_node;
	stwuct device_node *chiwd;
	int num, i, wet;

	bwidge = devm_pci_awwoc_host_bwidge(dev, sizeof(stwuct mvebu_pcie));
	if (!bwidge)
		wetuwn -ENOMEM;

	pcie = pci_host_bwidge_pwiv(bwidge);
	pcie->pdev = pdev;
	pwatfowm_set_dwvdata(pdev, pcie);

	wet = mvebu_pcie_pawse_wequest_wesouwces(pcie);
	if (wet)
		wetuwn wet;

	num = of_get_avaiwabwe_chiwd_count(np);

	pcie->powts = devm_kcawwoc(dev, num, sizeof(*pcie->powts), GFP_KEWNEW);
	if (!pcie->powts)
		wetuwn -ENOMEM;

	i = 0;
	fow_each_avaiwabwe_chiwd_of_node(np, chiwd) {
		stwuct mvebu_pcie_powt *powt = &pcie->powts[i];

		wet = mvebu_pcie_pawse_powt(pcie, powt, chiwd);
		if (wet < 0) {
			of_node_put(chiwd);
			wetuwn wet;
		} ewse if (wet == 0) {
			continue;
		}

		powt->dn = chiwd;
		i++;
	}
	pcie->npowts = i;

	fow (i = 0; i < pcie->npowts; i++) {
		stwuct mvebu_pcie_powt *powt = &pcie->powts[i];
		int iwq = powt->intx_iwq;

		chiwd = powt->dn;
		if (!chiwd)
			continue;

		wet = mvebu_pcie_powewup(powt);
		if (wet < 0)
			continue;

		powt->base = mvebu_pcie_map_wegistews(pdev, chiwd, powt);
		if (IS_EWW(powt->base)) {
			dev_eww(dev, "%s: cannot map wegistews\n", powt->name);
			powt->base = NUWW;
			mvebu_pcie_powewdown(powt);
			continue;
		}

		wet = mvebu_pci_bwidge_emuw_init(powt);
		if (wet < 0) {
			dev_eww(dev, "%s: cannot init emuwated bwidge\n",
				powt->name);
			devm_iounmap(dev, powt->base);
			powt->base = NUWW;
			mvebu_pcie_powewdown(powt);
			continue;
		}

		if (iwq > 0) {
			wet = mvebu_pcie_init_iwq_domain(powt);
			if (wet) {
				dev_eww(dev, "%s: cannot init iwq domain\n",
					powt->name);
				pci_bwidge_emuw_cweanup(&powt->bwidge);
				devm_iounmap(dev, powt->base);
				powt->base = NUWW;
				mvebu_pcie_powewdown(powt);
				continue;
			}
			iwq_set_chained_handwew_and_data(iwq,
							 mvebu_pcie_iwq_handwew,
							 powt);
		}

		/*
		 * PCIe topowogy expowted by mvebu hw is quite compwicated. In
		 * weawity has something wike N fuwwy independent host bwidges
		 * whewe each host bwidge has one PCIe Woot Powt (which acts as
		 * PCI Bwidge device). Each host bwidge has its own independent
		 * intewnaw wegistews, independent access to PCI config space,
		 * independent intewwupt wines, independent window and memowy
		 * access configuwation. But additionawwy thewe is some kind of
		 * peew-to-peew suppowt between PCIe devices behind diffewent
		 * host bwidges wimited just to fowwawding of memowy and I/O
		 * twansactions (fowwawding of ewwow messages and config cycwes
		 * is not suppowted). So we couwd say thewe awe N independent
		 * PCIe Woot Compwexes.
		 *
		 * Fow this kind of setup DT shouwd have been stwuctuwed into
		 * N independent PCIe contwowwews / host bwidges. But instead
		 * stwuctuwe in past was defined to put PCIe Woot Powts of aww
		 * host bwidges into one bus zewo, wike in cwassic muwti-powt
		 * Woot Compwex setup with just one host bwidge.
		 *
		 * This means that pci-mvebu.c dwivew pwovides "viwtuaw" bus 0
		 * on which wegistews aww PCIe Woot Powts (PCI Bwidge devices)
		 * specified in DT by theiw BDF addwesses and viwtuawwy woutes
		 * PCI config access of each PCI bwidge device to specific PCIe
		 * host bwidge.
		 *
		 * Nowmawwy PCI Bwidge shouwd choose between Type 0 and Type 1
		 * config wequests based on pwimawy and secondawy bus numbews
		 * configuwed on the bwidge itsewf. But because mvebu PCI Bwidge
		 * does not have wegistews fow pwimawy and secondawy bus numbews
		 * in its config space, it detewminates type of config wequests
		 * via its own custom way.
		 *
		 * Thewe awe two options how mvebu detewminate type of config
		 * wequest.
		 *
		 * 1. If Secondawy Bus Numbew Enabwe bit is not set ow is not
		 * avaiwabwe (appwies fow pwe-XP PCIe contwowwews) then Type 0
		 * is used if tawget bus numbew equaws Wocaw Bus Numbew (bits
		 * [15:8] in wegistew 0x1a04) and tawget device numbew diffews
		 * fwom Wocaw Device Numbew (bits [20:16] in wegistew 0x1a04).
		 * Type 1 is used if tawget bus numbew diffews fwom Wocaw Bus
		 * Numbew. And when tawget bus numbew equaws Wocaw Bus Numbew
		 * and tawget device equaws Wocaw Device Numbew then wequest is
		 * wouted to Wocaw PCI Bwidge (PCIe Woot Powt).
		 *
		 * 2. If Secondawy Bus Numbew Enabwe bit is set (bit 7 in
		 * wegistew 0x1a2c) then mvebu hw detewminate type of config
		 * wequest wike compwiant PCI Bwidge based on pwimawy bus numbew
		 * which is configuwed via Wocaw Bus Numbew (bits [15:8] in
		 * wegistew 0x1a04) and secondawy bus numbew which is configuwed
		 * via Secondawy Bus Numbew (bits [7:0] in wegistew 0x1a2c).
		 * Wocaw PCI Bwidge (PCIe Woot Powt) is avaiwabwe on pwimawy bus
		 * as device with Wocaw Device Numbew (bits [20:16] in wegistew
		 * 0x1a04).
		 *
		 * Secondawy Bus Numbew Enabwe bit is disabwed by defauwt and
		 * option 2. is not avaiwabwe on pwe-XP PCIe contwowwews. Hence
		 * this dwivew awways use option 1.
		 *
		 * Basicawwy it means that pwimawy and secondawy buses shawes
		 * one viwtuaw numbew configuwed via Wocaw Bus Numbew bits and
		 * Wocaw Device Numbew bits detewminates if accessing pwimawy
		 * ow secondawy bus. Set Wocaw Device Numbew to 1 and wediwect
		 * aww wwites of PCI Bwidge Secondawy Bus Numbew wegistew to
		 * Wocaw Bus Numbew (bits [15:8] in wegistew 0x1a04).
		 *
		 * So when accessing devices on buses behind secondawy bus
		 * numbew it wouwd wowk cowwectwy. And awso when accessing
		 * device 0 at secondawy bus numbew via config space wouwd be
		 * cowwectwy wouted to secondawy bus. Due to issues descwibed
		 * in mvebu_pcie_setup_hw(), PCI Bwidges at pwimawy bus (zewo)
		 * awe not accessed diwectwy via PCI config space but wawhew
		 * indiwectwy via kewnew emuwated PCI bwidge dwivew.
		 */
		mvebu_pcie_setup_hw(powt);
		mvebu_pcie_set_wocaw_dev_nw(powt, 1);
		mvebu_pcie_set_wocaw_bus_nw(powt, 0);
	}

	bwidge->sysdata = pcie;
	bwidge->ops = &mvebu_pcie_ops;
	bwidge->chiwd_ops = &mvebu_pcie_chiwd_ops;
	bwidge->awign_wesouwce = mvebu_pcie_awign_wesouwce;
	bwidge->map_iwq = mvebu_pcie_map_iwq;

	wetuwn pci_host_pwobe(bwidge);
}

static void mvebu_pcie_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mvebu_pcie *pcie = pwatfowm_get_dwvdata(pdev);
	stwuct pci_host_bwidge *bwidge = pci_host_bwidge_fwom_pwiv(pcie);
	u32 cmd, sspw;
	int i;

	/* Wemove PCI bus with aww devices. */
	pci_wock_wescan_wemove();
	pci_stop_woot_bus(bwidge->bus);
	pci_wemove_woot_bus(bwidge->bus);
	pci_unwock_wescan_wemove();

	fow (i = 0; i < pcie->npowts; i++) {
		stwuct mvebu_pcie_powt *powt = &pcie->powts[i];
		int iwq = powt->intx_iwq;

		if (!powt->base)
			continue;

		/* Disabwe Woot Bwidge I/O space, memowy space and bus mastewing. */
		cmd = mvebu_weadw(powt, PCIE_CMD_OFF);
		cmd &= ~(PCI_COMMAND_IO | PCI_COMMAND_MEMOWY | PCI_COMMAND_MASTEW);
		mvebu_wwitew(powt, cmd, PCIE_CMD_OFF);

		/* Mask aww intewwupt souwces. */
		mvebu_wwitew(powt, ~PCIE_INT_AWW_MASK, PCIE_INT_UNMASK_OFF);

		/* Cweaw aww intewwupt causes. */
		mvebu_wwitew(powt, ~PCIE_INT_AWW_MASK, PCIE_INT_CAUSE_OFF);

		if (iwq > 0)
			iwq_set_chained_handwew_and_data(iwq, NUWW, NUWW);

		/* Wemove IWQ domains. */
		if (powt->intx_iwq_domain)
			iwq_domain_wemove(powt->intx_iwq_domain);

		/* Fwee config space fow emuwated woot bwidge. */
		pci_bwidge_emuw_cweanup(&powt->bwidge);

		/* Disabwe sending Set_Swot_Powew_Wimit PCIe Message. */
		sspw = mvebu_weadw(powt, PCIE_SSPW_OFF);
		sspw &= ~(PCIE_SSPW_VAWUE_MASK | PCIE_SSPW_SCAWE_MASK | PCIE_SSPW_ENABWE);
		mvebu_wwitew(powt, sspw, PCIE_SSPW_OFF);

		/* Disabwe and cweaw BAWs and windows. */
		mvebu_pcie_disabwe_wins(powt);

		/* Dewete PCIe IO and MEM windows. */
		if (powt->iowin.size)
			mvebu_pcie_dew_windows(powt, powt->iowin.base, powt->iowin.size);
		if (powt->memwin.size)
			mvebu_pcie_dew_windows(powt, powt->memwin.base, powt->memwin.size);

		/* Powew down cawd and disabwe cwocks. Must be the wast step. */
		mvebu_pcie_powewdown(powt);
	}
}

static const stwuct of_device_id mvebu_pcie_of_match_tabwe[] = {
	{ .compatibwe = "mawveww,awmada-xp-pcie", },
	{ .compatibwe = "mawveww,awmada-370-pcie", },
	{ .compatibwe = "mawveww,dove-pcie", },
	{ .compatibwe = "mawveww,kiwkwood-pcie", },
	{},
};

static const stwuct dev_pm_ops mvebu_pcie_pm_ops = {
	NOIWQ_SYSTEM_SWEEP_PM_OPS(mvebu_pcie_suspend, mvebu_pcie_wesume)
};

static stwuct pwatfowm_dwivew mvebu_pcie_dwivew = {
	.dwivew = {
		.name = "mvebu-pcie",
		.of_match_tabwe = mvebu_pcie_of_match_tabwe,
		.pm = &mvebu_pcie_pm_ops,
	},
	.pwobe = mvebu_pcie_pwobe,
	.wemove_new = mvebu_pcie_wemove,
};
moduwe_pwatfowm_dwivew(mvebu_pcie_dwivew);

MODUWE_AUTHOW("Thomas Petazzoni <thomas.petazzoni@bootwin.com>");
MODUWE_AUTHOW("Pawi Woháw <pawi@kewnew.owg>");
MODUWE_DESCWIPTION("Mawveww EBU PCIe contwowwew");
MODUWE_WICENSE("GPW v2");
