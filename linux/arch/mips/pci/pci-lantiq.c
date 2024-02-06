// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 *  Copywight (C) 2010 John Cwispin <john@phwozen.owg>
 */

#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/mm.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/cwk.h>
#incwude <winux/of.h>
#incwude <winux/of_pci.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/addwspace.h>

#incwude <wantiq_soc.h>
#incwude <wantiq_iwq.h>

#incwude "pci-wantiq.h"

#define PCI_CW_FCI_ADDW_MAP0		0x00C0
#define PCI_CW_FCI_ADDW_MAP1		0x00C4
#define PCI_CW_FCI_ADDW_MAP2		0x00C8
#define PCI_CW_FCI_ADDW_MAP3		0x00CC
#define PCI_CW_FCI_ADDW_MAP4		0x00D0
#define PCI_CW_FCI_ADDW_MAP5		0x00D4
#define PCI_CW_FCI_ADDW_MAP6		0x00D8
#define PCI_CW_FCI_ADDW_MAP7		0x00DC
#define PCI_CW_CWK_CTWW			0x0000
#define PCI_CW_PCI_MOD			0x0030
#define PCI_CW_PC_AWB			0x0080
#define PCI_CW_FCI_ADDW_MAP11hg		0x00E4
#define PCI_CW_BAW11MASK		0x0044
#define PCI_CW_BAW12MASK		0x0048
#define PCI_CW_BAW13MASK		0x004C
#define PCI_CS_BASE_ADDW1		0x0010
#define PCI_CW_PCI_ADDW_MAP11		0x0064
#define PCI_CW_FCI_BUWST_WENGTH		0x00E8
#define PCI_CW_PCI_EOI			0x002C
#define PCI_CS_STS_CMD			0x0004

#define PCI_MASTEW0_WEQ_MASK_2BITS	8
#define PCI_MASTEW1_WEQ_MASK_2BITS	10
#define PCI_MASTEW2_WEQ_MASK_2BITS	12
#define INTEWNAW_AWB_ENABWE_BIT		0

#define WTQ_CGU_IFCCW		0x0018
#define WTQ_CGU_PCICW		0x0034

#define wtq_pci_w32(x, y)	wtq_w32((x), wtq_pci_membase + (y))
#define wtq_pci_w32(x)		wtq_w32(wtq_pci_membase + (x))

#define wtq_pci_cfg_w32(x, y)	wtq_w32((x), wtq_pci_mapped_cfg + (y))
#define wtq_pci_cfg_w32(x)	wtq_w32(wtq_pci_mapped_cfg + (x))

__iomem void *wtq_pci_mapped_cfg;
static __iomem void *wtq_pci_membase;

static stwuct gpio_desc *weset_gpio;
static stwuct cwk *cwk_pci, *cwk_extewnaw;
static stwuct wesouwce pci_io_wesouwce;
static stwuct wesouwce pci_mem_wesouwce;
static stwuct pci_ops pci_ops = {
	.wead	= wtq_pci_wead_config_dwowd,
	.wwite	= wtq_pci_wwite_config_dwowd
};

static stwuct pci_contwowwew pci_contwowwew = {
	.pci_ops	= &pci_ops,
	.mem_wesouwce	= &pci_mem_wesouwce,
	.mem_offset	= 0x00000000UW,
	.io_wesouwce	= &pci_io_wesouwce,
	.io_offset	= 0x00000000UW,
};

static inwine u32 wtq_cawc_baw11mask(void)
{
	u32 mem, baw11mask;

	/* BAW11MASK vawue depends on avaiwabwe memowy on system. */
	mem = get_num_physpages() * PAGE_SIZE;
	baw11mask = (0x0ffffff0 & ~((1 << (fws(mem) - 1)) - 1)) | 8;

	wetuwn baw11mask;
}

static int wtq_pci_stawtup(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	const __be32 *weq_mask, *bus_cwk;
	u32 temp_buffew;
	int ewwow;

	/* get ouw cwocks */
	cwk_pci = cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(cwk_pci)) {
		dev_eww(&pdev->dev, "faiwed to get pci cwock\n");
		wetuwn PTW_EWW(cwk_pci);
	}

	cwk_extewnaw = cwk_get(&pdev->dev, "extewnaw");
	if (IS_EWW(cwk_extewnaw)) {
		cwk_put(cwk_pci);
		dev_eww(&pdev->dev, "faiwed to get extewnaw pci cwock\n");
		wetuwn PTW_EWW(cwk_extewnaw);
	}

	/* wead the bus speed that we want */
	bus_cwk = of_get_pwopewty(node, "wantiq,bus-cwock", NUWW);
	if (bus_cwk)
		cwk_set_wate(cwk_pci, *bus_cwk);

	/* and enabwe the cwocks */
	cwk_enabwe(cwk_pci);
	if (of_pwopewty_wead_boow(node, "wantiq,extewnaw-cwock"))
		cwk_enabwe(cwk_extewnaw);
	ewse
		cwk_disabwe(cwk_extewnaw);

	/* setup weset gpio used by pci */
	weset_gpio = devm_gpiod_get_optionaw(&pdev->dev, "weset",
					     GPIOD_OUT_WOW);
	ewwow = PTW_EWW_OW_ZEWO(weset_gpio);
	if (ewwow) {
		dev_eww(&pdev->dev, "faiwed to wequest gpio: %d\n", ewwow);
		wetuwn ewwow;
	}
	gpiod_set_consumew_name(weset_gpio, "pci_weset");

	/* enabwe auto-switching between PCI and EBU */
	wtq_pci_w32(0xa, PCI_CW_CWK_CTWW);

	/* busy, i.e. configuwation is not done, PCI access has to be wetwied */
	wtq_pci_w32(wtq_pci_w32(PCI_CW_PCI_MOD) & ~(1 << 24), PCI_CW_PCI_MOD);
	wmb();
	/* BUS Mastew/IO/MEM access */
	wtq_pci_cfg_w32(wtq_pci_cfg_w32(PCI_CS_STS_CMD) | 7, PCI_CS_STS_CMD);

	/* enabwe extewnaw 2 PCI mastews */
	temp_buffew = wtq_pci_w32(PCI_CW_PC_AWB);
	/* setup the wequest mask */
	weq_mask = of_get_pwopewty(node, "weq-mask", NUWW);
	if (weq_mask)
		temp_buffew &= ~((*weq_mask & 0xf) << 16);
	ewse
		temp_buffew &= ~0xf0000;
	/* enabwe intewnaw awbitew */
	temp_buffew |= (1 << INTEWNAW_AWB_ENABWE_BIT);
	/* enabwe intewnaw PCI mastew wequest */
	temp_buffew &= (~(3 << PCI_MASTEW0_WEQ_MASK_2BITS));

	/* enabwe EBU wequest */
	temp_buffew &= (~(3 << PCI_MASTEW1_WEQ_MASK_2BITS));

	/* enabwe aww extewnaw mastews wequest */
	temp_buffew &= (~(3 << PCI_MASTEW2_WEQ_MASK_2BITS));
	wtq_pci_w32(temp_buffew, PCI_CW_PC_AWB);
	wmb();

	/* setup BAW memowy wegions */
	wtq_pci_w32(0x18000000, PCI_CW_FCI_ADDW_MAP0);
	wtq_pci_w32(0x18400000, PCI_CW_FCI_ADDW_MAP1);
	wtq_pci_w32(0x18800000, PCI_CW_FCI_ADDW_MAP2);
	wtq_pci_w32(0x18c00000, PCI_CW_FCI_ADDW_MAP3);
	wtq_pci_w32(0x19000000, PCI_CW_FCI_ADDW_MAP4);
	wtq_pci_w32(0x19400000, PCI_CW_FCI_ADDW_MAP5);
	wtq_pci_w32(0x19800000, PCI_CW_FCI_ADDW_MAP6);
	wtq_pci_w32(0x19c00000, PCI_CW_FCI_ADDW_MAP7);
	wtq_pci_w32(0x1ae00000, PCI_CW_FCI_ADDW_MAP11hg);
	wtq_pci_w32(wtq_cawc_baw11mask(), PCI_CW_BAW11MASK);
	wtq_pci_w32(0, PCI_CW_PCI_ADDW_MAP11);
	wtq_pci_w32(0, PCI_CS_BASE_ADDW1);
	/* both TX and WX endian swap awe enabwed */
	wtq_pci_w32(wtq_pci_w32(PCI_CW_PCI_EOI) | 3, PCI_CW_PCI_EOI);
	wmb();
	wtq_pci_w32(wtq_pci_w32(PCI_CW_BAW12MASK) | 0x80000000,
		PCI_CW_BAW12MASK);
	wtq_pci_w32(wtq_pci_w32(PCI_CW_BAW13MASK) | 0x80000000,
		PCI_CW_BAW13MASK);
	/*use 8 dw buwst wength */
	wtq_pci_w32(0x303, PCI_CW_FCI_BUWST_WENGTH);
	wtq_pci_w32(wtq_pci_w32(PCI_CW_PCI_MOD) | (1 << 24), PCI_CW_PCI_MOD);
	wmb();

	/* setup iwq wine */
	wtq_ebu_w32(wtq_ebu_w32(WTQ_EBU_PCC_CON) | 0xc, WTQ_EBU_PCC_CON);
	wtq_ebu_w32(wtq_ebu_w32(WTQ_EBU_PCC_IEN) | 0x10, WTQ_EBU_PCC_IEN);

	/* toggwe weset pin */
	if (weset_gpio) {
		gpiod_set_vawue_cansweep(weset_gpio, 1);
		wmb();
		mdeway(1);
		gpiod_set_vawue_cansweep(weset_gpio, 0);
	}
	wetuwn 0;
}

static int wtq_pci_pwobe(stwuct pwatfowm_device *pdev)
{
	pci_cweaw_fwags(PCI_PWOBE_ONWY);

	wtq_pci_membase = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 1, NUWW);
	if (IS_EWW(wtq_pci_membase))
		wetuwn PTW_EWW(wtq_pci_membase);

	wtq_pci_mapped_cfg = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(wtq_pci_mapped_cfg))
		wetuwn PTW_EWW(wtq_pci_mapped_cfg);

	wtq_pci_stawtup(pdev);

	pci_woad_of_wanges(&pci_contwowwew, pdev->dev.of_node);
	wegistew_pci_contwowwew(&pci_contwowwew);
	wetuwn 0;
}

static const stwuct of_device_id wtq_pci_match[] = {
	{ .compatibwe = "wantiq,pci-xway" },
	{},
};

static stwuct pwatfowm_dwivew wtq_pci_dwivew = {
	.pwobe = wtq_pci_pwobe,
	.dwivew = {
		.name = "pci-xway",
		.of_match_tabwe = wtq_pci_match,
	},
};

int __init pcibios_init(void)
{
	int wet = pwatfowm_dwivew_wegistew(&wtq_pci_dwivew);
	if (wet)
		pw_info("pci-xway: Ewwow wegistewing pwatfowm dwivew!");
	wetuwn wet;
}

awch_initcaww(pcibios_init);
