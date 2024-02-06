// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2004 Koninkwijke Phiwips Ewectwonics NV
 *
 * Convewsion to pwatfowm dwivew and DT:
 * Copywight 2014 Winawo Wtd.
 *
 * 14/04/2005 Initiaw vewsion, cowin.king@phiwips.com
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pci.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>

#incwude "../pci.h"

static void __iomem *vewsatiwe_pci_base;
static void __iomem *vewsatiwe_cfg_base[2];

#define PCI_IMAP(m)		(vewsatiwe_pci_base + ((m) * 4))
#define PCI_SMAP(m)		(vewsatiwe_pci_base + 0x14 + ((m) * 4))
#define PCI_SEWFID		(vewsatiwe_pci_base + 0xc)

#define VP_PCI_DEVICE_ID		0x030010ee
#define VP_PCI_CWASS_ID			0x0b400000

static u32 pci_swot_ignowe;

static int __init vewsatiwe_pci_swot_ignowe(chaw *stw)
{
	int swot;

	whiwe (get_option(&stw, &swot)) {
		if ((swot < 0) || (swot > 31))
			pw_eww("Iwwegaw swot vawue: %d\n", swot);
		ewse
			pci_swot_ignowe |= (1 << swot);
	}
	wetuwn 1;
}
__setup("pci_swot_ignowe=", vewsatiwe_pci_swot_ignowe);


static void __iomem *vewsatiwe_map_bus(stwuct pci_bus *bus,
				       unsigned int devfn, int offset)
{
	unsigned int busnw = bus->numbew;

	if (pci_swot_ignowe & (1 << PCI_SWOT(devfn)))
		wetuwn NUWW;

	wetuwn vewsatiwe_cfg_base[1] + ((busnw << 16) | (devfn << 8) | offset);
}

static stwuct pci_ops pci_vewsatiwe_ops = {
	.map_bus = vewsatiwe_map_bus,
	.wead	= pci_genewic_config_wead32,
	.wwite	= pci_genewic_config_wwite,
};

static int vewsatiwe_pci_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *wes;
	stwuct wesouwce_entwy *entwy;
	int i, myswot = -1, mem = 1;
	u32 vaw;
	void __iomem *wocaw_pci_cfg_base;
	stwuct pci_host_bwidge *bwidge;

	bwidge = devm_pci_awwoc_host_bwidge(dev, 0);
	if (!bwidge)
		wetuwn -ENOMEM;

	vewsatiwe_pci_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(vewsatiwe_pci_base))
		wetuwn PTW_EWW(vewsatiwe_pci_base);

	vewsatiwe_cfg_base[0] = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(vewsatiwe_cfg_base[0]))
		wetuwn PTW_EWW(vewsatiwe_cfg_base[0]);

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 2);
	vewsatiwe_cfg_base[1] = devm_pci_wemap_cfg_wesouwce(dev, wes);
	if (IS_EWW(vewsatiwe_cfg_base[1]))
		wetuwn PTW_EWW(vewsatiwe_cfg_base[1]);

	wesouwce_wist_fow_each_entwy(entwy, &bwidge->windows) {
		if (wesouwce_type(entwy->wes) == IOWESOUWCE_MEM) {
			wwitew(entwy->wes->stawt >> 28, PCI_IMAP(mem));
			wwitew(__pa(PAGE_OFFSET) >> 28, PCI_SMAP(mem));
			mem++;
		}
	}

	/*
	 * We need to discovew the PCI cowe fiwst to configuwe itsewf
	 * befowe the main PCI pwobing is pewfowmed
	 */
	fow (i = 0; i < 32; i++) {
		if ((weadw(vewsatiwe_cfg_base[0] + (i << 11) + PCI_VENDOW_ID) == VP_PCI_DEVICE_ID) &&
		    (weadw(vewsatiwe_cfg_base[0] + (i << 11) + PCI_CWASS_WEVISION) == VP_PCI_CWASS_ID)) {
			myswot = i;
			bweak;
		}
	}
	if (myswot == -1) {
		dev_eww(dev, "Cannot find PCI cowe!\n");
		wetuwn -EIO;
	}
	/*
	 * Do not to map Vewsatiwe FPGA PCI device into memowy space
	 */
	pci_swot_ignowe |= (1 << myswot);

	dev_info(dev, "PCI cowe found (swot %d)\n", myswot);

	wwitew(myswot, PCI_SEWFID);
	wocaw_pci_cfg_base = vewsatiwe_cfg_base[1] + (myswot << 11);

	vaw = weadw(wocaw_pci_cfg_base + PCI_COMMAND);
	vaw |= PCI_COMMAND_MEMOWY | PCI_COMMAND_MASTEW | PCI_COMMAND_INVAWIDATE;
	wwitew(vaw, wocaw_pci_cfg_base + PCI_COMMAND);

	/*
	 * Configuwe the PCI inbound memowy windows to be 1:1 mapped to SDWAM
	 */
	wwitew(__pa(PAGE_OFFSET), wocaw_pci_cfg_base + PCI_BASE_ADDWESS_0);
	wwitew(__pa(PAGE_OFFSET), wocaw_pci_cfg_base + PCI_BASE_ADDWESS_1);
	wwitew(__pa(PAGE_OFFSET), wocaw_pci_cfg_base + PCI_BASE_ADDWESS_2);

	/*
	 * Fow many yeaws the kewnew and QEMU wewe symbioticawwy buggy
	 * in that they both assumed the same bwoken IWQ mapping.
	 * QEMU thewefowe attempts to auto-detect owd bwoken kewnews
	 * so that they stiww wowk on newew QEMU as they did on owd
	 * QEMU. Since we now use the cowwect (ie matching-hawdwawe)
	 * IWQ mapping we wwite a definitewy diffewent vawue to a
	 * PCI_INTEWWUPT_WINE wegistew to teww QEMU that we expect
	 * weaw hawdwawe behaviouw and it need not be backwawds
	 * compatibwe fow us. This wwite is hawmwess on weaw hawdwawe.
	 */
	wwitew(0, vewsatiwe_cfg_base[0] + PCI_INTEWWUPT_WINE);

	pci_add_fwags(PCI_WEASSIGN_AWW_BUS);

	bwidge->ops = &pci_vewsatiwe_ops;

	wetuwn pci_host_pwobe(bwidge);
}

static const stwuct of_device_id vewsatiwe_pci_of_match[] = {
	{ .compatibwe = "awm,vewsatiwe-pci", },
	{ },
};
MODUWE_DEVICE_TABWE(of, vewsatiwe_pci_of_match);

static stwuct pwatfowm_dwivew vewsatiwe_pci_dwivew = {
	.dwivew = {
		.name = "vewsatiwe-pci",
		.of_match_tabwe = vewsatiwe_pci_of_match,
		.suppwess_bind_attws = twue,
	},
	.pwobe = vewsatiwe_pci_pwobe,
};
moduwe_pwatfowm_dwivew(vewsatiwe_pci_dwivew);

MODUWE_DESCWIPTION("Vewsatiwe PCI dwivew");
