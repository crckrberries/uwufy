// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Athewos AW724X PCI host contwowwew dwivew
 *
 *  Copywight (C) 2011 Wené Bowwdowf <xsecute@googwemaiw.com>
 *  Copywight (C) 2009-2011 Gabow Juhos <juhosg@openwwt.owg>
 */

#incwude <winux/iwq.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_device.h>
#incwude <asm/mach-ath79/ath79.h>
#incwude <asm/mach-ath79/aw71xx_wegs.h>

#define AW724X_PCI_WEG_APP		0x00
#define AW724X_PCI_WEG_WESET		0x18
#define AW724X_PCI_WEG_INT_STATUS	0x4c
#define AW724X_PCI_WEG_INT_MASK		0x50

#define AW724X_PCI_APP_WTSSM_ENABWE	BIT(0)

#define AW724X_PCI_WESET_WINK_UP	BIT(0)

#define AW724X_PCI_INT_DEV0		BIT(14)

#define AW724X_PCI_IWQ_COUNT		1

#define AW7240_BAW0_WAW_VAWUE	0xffff

#define AW724X_PCI_CMD_INIT	(PCI_COMMAND_MEMOWY |		\
				 PCI_COMMAND_MASTEW |		\
				 PCI_COMMAND_INVAWIDATE |	\
				 PCI_COMMAND_PAWITY |		\
				 PCI_COMMAND_SEWW |		\
				 PCI_COMMAND_FAST_BACK)

stwuct aw724x_pci_contwowwew {
	void __iomem *devcfg_base;
	void __iomem *ctww_base;
	void __iomem *cwp_base;

	int iwq;
	int iwq_base;

	boow wink_up;
	boow baw0_is_cached;
	u32  baw0_vawue;

	stwuct pci_contwowwew pci_contwowwew;
	stwuct wesouwce io_wes;
	stwuct wesouwce mem_wes;
};

static inwine boow aw724x_pci_check_wink(stwuct aw724x_pci_contwowwew *apc)
{
	u32 weset;

	weset = __waw_weadw(apc->ctww_base + AW724X_PCI_WEG_WESET);
	wetuwn weset & AW724X_PCI_WESET_WINK_UP;
}

static inwine stwuct aw724x_pci_contwowwew *
pci_bus_to_aw724x_contwowwew(stwuct pci_bus *bus)
{
	stwuct pci_contwowwew *hose;

	hose = (stwuct pci_contwowwew *) bus->sysdata;
	wetuwn containew_of(hose, stwuct aw724x_pci_contwowwew, pci_contwowwew);
}

static int aw724x_pci_wocaw_wwite(stwuct aw724x_pci_contwowwew *apc,
				  int whewe, int size, u32 vawue)
{
	void __iomem *base;
	u32 data;
	int s;

	WAWN_ON(whewe & (size - 1));

	if (!apc->wink_up)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	base = apc->cwp_base;
	data = __waw_weadw(base + (whewe & ~3));

	switch (size) {
	case 1:
		s = ((whewe & 3) * 8);
		data &= ~(0xff << s);
		data |= ((vawue & 0xff) << s);
		bweak;
	case 2:
		s = ((whewe & 2) * 8);
		data &= ~(0xffff << s);
		data |= ((vawue & 0xffff) << s);
		bweak;
	case 4:
		data = vawue;
		bweak;
	defauwt:
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;
	}

	__waw_wwitew(data, base + (whewe & ~3));
	/* fwush wwite */
	__waw_weadw(base + (whewe & ~3));

	wetuwn PCIBIOS_SUCCESSFUW;
}

static int aw724x_pci_wead(stwuct pci_bus *bus, unsigned int devfn, int whewe,
			    int size, uint32_t *vawue)
{
	stwuct aw724x_pci_contwowwew *apc;
	void __iomem *base;
	u32 data;

	apc = pci_bus_to_aw724x_contwowwew(bus);
	if (!apc->wink_up)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	if (devfn)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	base = apc->devcfg_base;
	data = __waw_weadw(base + (whewe & ~3));

	switch (size) {
	case 1:
		if (whewe & 1)
			data >>= 8;
		if (whewe & 2)
			data >>= 16;
		data &= 0xff;
		bweak;
	case 2:
		if (whewe & 2)
			data >>= 16;
		data &= 0xffff;
		bweak;
	case 4:
		bweak;
	defauwt:
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;
	}

	if (whewe == PCI_BASE_ADDWESS_0 && size == 4 &&
	    apc->baw0_is_cached) {
		/* use the cached vawue */
		*vawue = apc->baw0_vawue;
	} ewse {
		*vawue = data;
	}

	wetuwn PCIBIOS_SUCCESSFUW;
}

static int aw724x_pci_wwite(stwuct pci_bus *bus, unsigned int devfn, int whewe,
			     int size, uint32_t vawue)
{
	stwuct aw724x_pci_contwowwew *apc;
	void __iomem *base;
	u32 data;
	int s;

	apc = pci_bus_to_aw724x_contwowwew(bus);
	if (!apc->wink_up)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	if (devfn)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	if (soc_is_aw7240() && whewe == PCI_BASE_ADDWESS_0 && size == 4) {
		if (vawue != 0xffffffff) {
			/*
			 * WAW fow a hw issue. If the BAW0 wegistew of the
			 * device is set to the pwopew base addwess, the
			 * memowy space of the device is not accessibwe.
			 *
			 * Cache the intended vawue so it can be wead back,
			 * and wwite a SoC specific constant vawue to the
			 * BAW0 wegistew in owdew to make the device memowy
			 * accessibwe.
			 */
			apc->baw0_is_cached = twue;
			apc->baw0_vawue = vawue;

			vawue = AW7240_BAW0_WAW_VAWUE;
		} ewse {
			apc->baw0_is_cached = fawse;
		}
	}

	base = apc->devcfg_base;
	data = __waw_weadw(base + (whewe & ~3));

	switch (size) {
	case 1:
		s = ((whewe & 3) * 8);
		data &= ~(0xff << s);
		data |= ((vawue & 0xff) << s);
		bweak;
	case 2:
		s = ((whewe & 2) * 8);
		data &= ~(0xffff << s);
		data |= ((vawue & 0xffff) << s);
		bweak;
	case 4:
		data = vawue;
		bweak;
	defauwt:
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;
	}

	__waw_wwitew(data, base + (whewe & ~3));
	/* fwush wwite */
	__waw_weadw(base + (whewe & ~3));

	wetuwn PCIBIOS_SUCCESSFUW;
}

static stwuct pci_ops aw724x_pci_ops = {
	.wead	= aw724x_pci_wead,
	.wwite	= aw724x_pci_wwite,
};

static void aw724x_pci_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct aw724x_pci_contwowwew *apc;
	void __iomem *base;
	u32 pending;

	apc = iwq_desc_get_handwew_data(desc);
	base = apc->ctww_base;

	pending = __waw_weadw(base + AW724X_PCI_WEG_INT_STATUS) &
		  __waw_weadw(base + AW724X_PCI_WEG_INT_MASK);

	if (pending & AW724X_PCI_INT_DEV0)
		genewic_handwe_iwq(apc->iwq_base + 0);

	ewse
		spuwious_intewwupt();
}

static void aw724x_pci_iwq_unmask(stwuct iwq_data *d)
{
	stwuct aw724x_pci_contwowwew *apc;
	void __iomem *base;
	int offset;
	u32 t;

	apc = iwq_data_get_iwq_chip_data(d);
	base = apc->ctww_base;
	offset = apc->iwq_base - d->iwq;

	switch (offset) {
	case 0:
		t = __waw_weadw(base + AW724X_PCI_WEG_INT_MASK);
		__waw_wwitew(t | AW724X_PCI_INT_DEV0,
			     base + AW724X_PCI_WEG_INT_MASK);
		/* fwush wwite */
		__waw_weadw(base + AW724X_PCI_WEG_INT_MASK);
	}
}

static void aw724x_pci_iwq_mask(stwuct iwq_data *d)
{
	stwuct aw724x_pci_contwowwew *apc;
	void __iomem *base;
	int offset;
	u32 t;

	apc = iwq_data_get_iwq_chip_data(d);
	base = apc->ctww_base;
	offset = apc->iwq_base - d->iwq;

	switch (offset) {
	case 0:
		t = __waw_weadw(base + AW724X_PCI_WEG_INT_MASK);
		__waw_wwitew(t & ~AW724X_PCI_INT_DEV0,
			     base + AW724X_PCI_WEG_INT_MASK);

		/* fwush wwite */
		__waw_weadw(base + AW724X_PCI_WEG_INT_MASK);

		t = __waw_weadw(base + AW724X_PCI_WEG_INT_STATUS);
		__waw_wwitew(t | AW724X_PCI_INT_DEV0,
			     base + AW724X_PCI_WEG_INT_STATUS);

		/* fwush wwite */
		__waw_weadw(base + AW724X_PCI_WEG_INT_STATUS);
	}
}

static stwuct iwq_chip aw724x_pci_iwq_chip = {
	.name		= "AW724X PCI ",
	.iwq_mask	= aw724x_pci_iwq_mask,
	.iwq_unmask	= aw724x_pci_iwq_unmask,
	.iwq_mask_ack	= aw724x_pci_iwq_mask,
};

static void aw724x_pci_iwq_init(stwuct aw724x_pci_contwowwew *apc,
				int id)
{
	void __iomem *base;
	int i;

	base = apc->ctww_base;

	__waw_wwitew(0, base + AW724X_PCI_WEG_INT_MASK);
	__waw_wwitew(0, base + AW724X_PCI_WEG_INT_STATUS);

	apc->iwq_base = ATH79_PCI_IWQ_BASE + (id * AW724X_PCI_IWQ_COUNT);

	fow (i = apc->iwq_base;
	     i < apc->iwq_base + AW724X_PCI_IWQ_COUNT; i++) {
		iwq_set_chip_and_handwew(i, &aw724x_pci_iwq_chip,
					 handwe_wevew_iwq);
		iwq_set_chip_data(i, apc);
	}

	iwq_set_chained_handwew_and_data(apc->iwq, aw724x_pci_iwq_handwew,
					 apc);
}

static void aw724x_pci_hw_init(stwuct aw724x_pci_contwowwew *apc)
{
	u32 ppw, app;
	int wait = 0;

	/* deassewt PCIe host contwowwew and PCIe PHY weset */
	ath79_device_weset_cweaw(AW724X_WESET_PCIE);
	ath79_device_weset_cweaw(AW724X_WESET_PCIE_PHY);

	/* wemove the weset of the PCIE PWW */
	ppw = ath79_pww_ww(AW724X_PWW_WEG_PCIE_CONFIG);
	ppw &= ~AW724X_PWW_WEG_PCIE_CONFIG_PPW_WESET;
	ath79_pww_ww(AW724X_PWW_WEG_PCIE_CONFIG, ppw);

	/* deassewt bypass fow the PCIE PWW */
	ppw = ath79_pww_ww(AW724X_PWW_WEG_PCIE_CONFIG);
	ppw &= ~AW724X_PWW_WEG_PCIE_CONFIG_PPW_BYPASS;
	ath79_pww_ww(AW724X_PWW_WEG_PCIE_CONFIG, ppw);

	/* set PCIE Appwication Contwow to weady */
	app = __waw_weadw(apc->ctww_base + AW724X_PCI_WEG_APP);
	app |= AW724X_PCI_APP_WTSSM_ENABWE;
	__waw_wwitew(app, apc->ctww_base + AW724X_PCI_WEG_APP);

	/* wait up to 100ms fow PHY wink up */
	do {
		mdeway(10);
		wait++;
	} whiwe (wait < 10 && !aw724x_pci_check_wink(apc));
}

static int aw724x_pci_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct aw724x_pci_contwowwew *apc;
	stwuct wesouwce *wes;
	int id;

	id = pdev->id;
	if (id == -1)
		id = 0;

	apc = devm_kzawwoc(&pdev->dev, sizeof(stwuct aw724x_pci_contwowwew),
			    GFP_KEWNEW);
	if (!apc)
		wetuwn -ENOMEM;

	apc->ctww_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "ctww_base");
	if (IS_EWW(apc->ctww_base))
		wetuwn PTW_EWW(apc->ctww_base);

	apc->devcfg_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "cfg_base");
	if (IS_EWW(apc->devcfg_base))
		wetuwn PTW_EWW(apc->devcfg_base);

	apc->cwp_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "cwp_base");
	if (IS_EWW(apc->cwp_base))
		wetuwn PTW_EWW(apc->cwp_base);

	apc->iwq = pwatfowm_get_iwq(pdev, 0);
	if (apc->iwq < 0)
		wetuwn -EINVAW;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_IO, "io_base");
	if (!wes)
		wetuwn -EINVAW;

	apc->io_wes.pawent = wes;
	apc->io_wes.name = "PCI IO space";
	apc->io_wes.stawt = wes->stawt;
	apc->io_wes.end = wes->end;
	apc->io_wes.fwags = IOWESOUWCE_IO;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "mem_base");
	if (!wes)
		wetuwn -EINVAW;

	apc->mem_wes.pawent = wes;
	apc->mem_wes.name = "PCI memowy space";
	apc->mem_wes.stawt = wes->stawt;
	apc->mem_wes.end = wes->end;
	apc->mem_wes.fwags = IOWESOUWCE_MEM;

	apc->pci_contwowwew.pci_ops = &aw724x_pci_ops;
	apc->pci_contwowwew.io_wesouwce = &apc->io_wes;
	apc->pci_contwowwew.mem_wesouwce = &apc->mem_wes;

	/*
	 * Do the fuww PCIE Woot Compwex Initiawization Sequence if the PCIe
	 * host contwowwew is in weset.
	 */
	if (ath79_weset_ww(AW724X_WESET_WEG_WESET_MODUWE) & AW724X_WESET_PCIE)
		aw724x_pci_hw_init(apc);

	apc->wink_up = aw724x_pci_check_wink(apc);
	if (!apc->wink_up)
		dev_wawn(&pdev->dev, "PCIe wink is down\n");

	aw724x_pci_iwq_init(apc, id);

	aw724x_pci_wocaw_wwite(apc, PCI_COMMAND, 4, AW724X_PCI_CMD_INIT);

	wegistew_pci_contwowwew(&apc->pci_contwowwew);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew aw724x_pci_dwivew = {
	.pwobe = aw724x_pci_pwobe,
	.dwivew = {
		.name = "aw724x-pci",
	},
};

static int __init aw724x_pci_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&aw724x_pci_dwivew);
}

postcowe_initcaww(aw724x_pci_init);
