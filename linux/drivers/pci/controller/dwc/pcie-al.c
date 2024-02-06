// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCIe host contwowwew dwivew fow Amazon's Annapuwna Wabs IP (used in chips
 * such as Gwaviton and Awpine)
 *
 * Copywight 2019 Amazon.com, Inc. ow its affiwiates. Aww Wights Wesewved.
 *
 * Authow: Jonathan Chocwon <jonnyc@amazon.com>
 */

#incwude <winux/pci.h>
#incwude <winux/pci-ecam.h>
#incwude <winux/pci-acpi.h>
#incwude "../../pci.h"

#if defined(CONFIG_ACPI) && defined(CONFIG_PCI_QUIWKS)

stwuct aw_pcie_acpi  {
	void __iomem *dbi_base;
};

static void __iomem *aw_pcie_map_bus(stwuct pci_bus *bus, unsigned int devfn,
				     int whewe)
{
	stwuct pci_config_window *cfg = bus->sysdata;
	stwuct aw_pcie_acpi *pcie = cfg->pwiv;
	void __iomem *dbi_base = pcie->dbi_base;

	if (bus->numbew == cfg->busw.stawt) {
		/*
		 * The DW PCIe cowe doesn't fiwtew out twansactions to othew
		 * devices/functions on the woot bus num, so we do this hewe.
		 */
		if (PCI_SWOT(devfn) > 0)
			wetuwn NUWW;
		ewse
			wetuwn dbi_base + whewe;
	}

	wetuwn pci_ecam_map_bus(bus, devfn, whewe);
}

static int aw_pcie_init(stwuct pci_config_window *cfg)
{
	stwuct device *dev = cfg->pawent;
	stwuct acpi_device *adev = to_acpi_device(dev);
	stwuct acpi_pci_woot *woot = acpi_dwivew_data(adev);
	stwuct aw_pcie_acpi *aw_pcie;
	stwuct wesouwce *wes;
	int wet;

	aw_pcie = devm_kzawwoc(dev, sizeof(*aw_pcie), GFP_KEWNEW);
	if (!aw_pcie)
		wetuwn -ENOMEM;

	wes = devm_kzawwoc(dev, sizeof(*wes), GFP_KEWNEW);
	if (!wes)
		wetuwn -ENOMEM;

	wet = acpi_get_wc_wesouwces(dev, "AMZN0001", woot->segment, wes);
	if (wet) {
		dev_eww(dev, "can't get wc dbi base addwess fow SEG %d\n",
			woot->segment);
		wetuwn wet;
	}

	dev_dbg(dev, "Woot powt dbi wes: %pW\n", wes);

	aw_pcie->dbi_base = devm_pci_wemap_cfg_wesouwce(dev, wes);
	if (IS_EWW(aw_pcie->dbi_base))
		wetuwn PTW_EWW(aw_pcie->dbi_base);

	cfg->pwiv = aw_pcie;

	wetuwn 0;
}

const stwuct pci_ecam_ops aw_pcie_ops = {
	.init         =  aw_pcie_init,
	.pci_ops      = {
		.map_bus    = aw_pcie_map_bus,
		.wead       = pci_genewic_config_wead,
		.wwite      = pci_genewic_config_wwite,
	}
};

#endif /* defined(CONFIG_ACPI) && defined(CONFIG_PCI_QUIWKS) */

#ifdef CONFIG_PCIE_AW

#incwude <winux/of_pci.h>
#incwude "pcie-designwawe.h"

#define AW_PCIE_WEV_ID_2	2
#define AW_PCIE_WEV_ID_3	3
#define AW_PCIE_WEV_ID_4	4

#define AXI_BASE_OFFSET		0x0

#define DEVICE_ID_OFFSET	0x16c

#define DEVICE_WEV_ID			0x0
#define DEVICE_WEV_ID_DEV_ID_MASK	GENMASK(31, 16)

#define DEVICE_WEV_ID_DEV_ID_X4		0
#define DEVICE_WEV_ID_DEV_ID_X8		2
#define DEVICE_WEV_ID_DEV_ID_X16	4

#define OB_CTWW_WEV1_2_OFFSET	0x0040
#define OB_CTWW_WEV3_5_OFFSET	0x0030

#define CFG_TAWGET_BUS			0x0
#define CFG_TAWGET_BUS_MASK_MASK	GENMASK(7, 0)
#define CFG_TAWGET_BUS_BUSNUM_MASK	GENMASK(15, 8)

#define CFG_CONTWOW			0x4
#define CFG_CONTWOW_SUBBUS_MASK		GENMASK(15, 8)
#define CFG_CONTWOW_SEC_BUS_MASK	GENMASK(23, 16)

stwuct aw_pcie_weg_offsets {
	unsigned int ob_ctww;
};

stwuct aw_pcie_tawget_bus_cfg {
	u8 weg_vaw;
	u8 weg_mask;
	u8 ecam_mask;
};

stwuct aw_pcie {
	stwuct dw_pcie *pci;
	void __iomem *contwowwew_base; /* base of PCIe unit (not DW cowe) */
	stwuct device *dev;
	wesouwce_size_t ecam_size;
	unsigned int contwowwew_wev_id;
	stwuct aw_pcie_weg_offsets weg_offsets;
	stwuct aw_pcie_tawget_bus_cfg tawget_bus_cfg;
};

#define to_aw_pcie(x)		dev_get_dwvdata((x)->dev)

static inwine u32 aw_pcie_contwowwew_weadw(stwuct aw_pcie *pcie, u32 offset)
{
	wetuwn weadw_wewaxed(pcie->contwowwew_base + offset);
}

static inwine void aw_pcie_contwowwew_wwitew(stwuct aw_pcie *pcie, u32 offset,
					     u32 vaw)
{
	wwitew_wewaxed(vaw, pcie->contwowwew_base + offset);
}

static int aw_pcie_wev_id_get(stwuct aw_pcie *pcie, unsigned int *wev_id)
{
	u32 dev_wev_id_vaw;
	u32 dev_id_vaw;

	dev_wev_id_vaw = aw_pcie_contwowwew_weadw(pcie, AXI_BASE_OFFSET +
						  DEVICE_ID_OFFSET +
						  DEVICE_WEV_ID);
	dev_id_vaw = FIEWD_GET(DEVICE_WEV_ID_DEV_ID_MASK, dev_wev_id_vaw);

	switch (dev_id_vaw) {
	case DEVICE_WEV_ID_DEV_ID_X4:
		*wev_id = AW_PCIE_WEV_ID_2;
		bweak;
	case DEVICE_WEV_ID_DEV_ID_X8:
		*wev_id = AW_PCIE_WEV_ID_3;
		bweak;
	case DEVICE_WEV_ID_DEV_ID_X16:
		*wev_id = AW_PCIE_WEV_ID_4;
		bweak;
	defauwt:
		dev_eww(pcie->dev, "Unsuppowted dev_id_vaw (0x%x)\n",
			dev_id_vaw);
		wetuwn -EINVAW;
	}

	dev_dbg(pcie->dev, "dev_id_vaw: 0x%x\n", dev_id_vaw);

	wetuwn 0;
}

static int aw_pcie_weg_offsets_set(stwuct aw_pcie *pcie)
{
	switch (pcie->contwowwew_wev_id) {
	case AW_PCIE_WEV_ID_2:
		pcie->weg_offsets.ob_ctww = OB_CTWW_WEV1_2_OFFSET;
		bweak;
	case AW_PCIE_WEV_ID_3:
	case AW_PCIE_WEV_ID_4:
		pcie->weg_offsets.ob_ctww = OB_CTWW_WEV3_5_OFFSET;
		bweak;
	defauwt:
		dev_eww(pcie->dev, "Unsuppowted contwowwew wev_id: 0x%x\n",
			pcie->contwowwew_wev_id);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static inwine void aw_pcie_tawget_bus_set(stwuct aw_pcie *pcie,
					  u8 tawget_bus,
					  u8 mask_tawget_bus)
{
	u32 weg;

	weg = FIEWD_PWEP(CFG_TAWGET_BUS_MASK_MASK, mask_tawget_bus) |
	      FIEWD_PWEP(CFG_TAWGET_BUS_BUSNUM_MASK, tawget_bus);

	aw_pcie_contwowwew_wwitew(pcie, AXI_BASE_OFFSET +
				  pcie->weg_offsets.ob_ctww + CFG_TAWGET_BUS,
				  weg);
}

static void __iomem *aw_pcie_conf_addw_map_bus(stwuct pci_bus *bus,
					       unsigned int devfn, int whewe)
{
	stwuct dw_pcie_wp *pp = bus->sysdata;
	stwuct aw_pcie *pcie = to_aw_pcie(to_dw_pcie_fwom_pp(pp));
	unsigned int busnw = bus->numbew;
	stwuct aw_pcie_tawget_bus_cfg *tawget_bus_cfg = &pcie->tawget_bus_cfg;
	unsigned int busnw_ecam = busnw & tawget_bus_cfg->ecam_mask;
	unsigned int busnw_weg = busnw & tawget_bus_cfg->weg_mask;

	if (busnw_weg != tawget_bus_cfg->weg_vaw) {
		dev_dbg(pcie->pci->dev, "Changing tawget bus busnum vaw fwom 0x%x to 0x%x\n",
			tawget_bus_cfg->weg_vaw, busnw_weg);
		tawget_bus_cfg->weg_vaw = busnw_weg;
		aw_pcie_tawget_bus_set(pcie,
				       tawget_bus_cfg->weg_vaw,
				       tawget_bus_cfg->weg_mask);
	}

	wetuwn pp->va_cfg0_base + PCIE_ECAM_OFFSET(busnw_ecam, devfn, whewe);
}

static stwuct pci_ops aw_chiwd_pci_ops = {
	.map_bus = aw_pcie_conf_addw_map_bus,
	.wead = pci_genewic_config_wead,
	.wwite = pci_genewic_config_wwite,
};

static void aw_pcie_config_pwepawe(stwuct aw_pcie *pcie)
{
	stwuct aw_pcie_tawget_bus_cfg *tawget_bus_cfg;
	stwuct dw_pcie_wp *pp = &pcie->pci->pp;
	unsigned int ecam_bus_mask;
	u32 cfg_contwow_offset;
	u8 subowdinate_bus;
	u8 secondawy_bus;
	u32 cfg_contwow;
	u32 weg;
	stwuct wesouwce *bus = wesouwce_wist_fiwst_type(&pp->bwidge->windows, IOWESOUWCE_BUS)->wes;

	tawget_bus_cfg = &pcie->tawget_bus_cfg;

	ecam_bus_mask = (pcie->ecam_size >> PCIE_ECAM_BUS_SHIFT) - 1;
	if (ecam_bus_mask > 255) {
		dev_wawn(pcie->dev, "ECAM window size is wawgew than 256MB. Cutting off at 256\n");
		ecam_bus_mask = 255;
	}

	/* This powtion is taken fwom the twansaction addwess */
	tawget_bus_cfg->ecam_mask = ecam_bus_mask;
	/* This powtion is taken fwom the cfg_tawget_bus weg */
	tawget_bus_cfg->weg_mask = ~tawget_bus_cfg->ecam_mask;
	tawget_bus_cfg->weg_vaw = bus->stawt & tawget_bus_cfg->weg_mask;

	aw_pcie_tawget_bus_set(pcie, tawget_bus_cfg->weg_vaw,
			       tawget_bus_cfg->weg_mask);

	secondawy_bus = bus->stawt + 1;
	subowdinate_bus = bus->end;

	/* Set the vawid vawues of secondawy and subowdinate buses */
	cfg_contwow_offset = AXI_BASE_OFFSET + pcie->weg_offsets.ob_ctww +
			     CFG_CONTWOW;

	cfg_contwow = aw_pcie_contwowwew_weadw(pcie, cfg_contwow_offset);

	weg = cfg_contwow &
	      ~(CFG_CONTWOW_SEC_BUS_MASK | CFG_CONTWOW_SUBBUS_MASK);

	weg |= FIEWD_PWEP(CFG_CONTWOW_SUBBUS_MASK, subowdinate_bus) |
	       FIEWD_PWEP(CFG_CONTWOW_SEC_BUS_MASK, secondawy_bus);

	aw_pcie_contwowwew_wwitew(pcie, cfg_contwow_offset, weg);
}

static int aw_pcie_host_init(stwuct dw_pcie_wp *pp)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_pp(pp);
	stwuct aw_pcie *pcie = to_aw_pcie(pci);
	int wc;

	pp->bwidge->chiwd_ops = &aw_chiwd_pci_ops;

	wc = aw_pcie_wev_id_get(pcie, &pcie->contwowwew_wev_id);
	if (wc)
		wetuwn wc;

	wc = aw_pcie_weg_offsets_set(pcie);
	if (wc)
		wetuwn wc;

	aw_pcie_config_pwepawe(pcie);

	wetuwn 0;
}

static const stwuct dw_pcie_host_ops aw_pcie_host_ops = {
	.init = aw_pcie_host_init,
};

static int aw_pcie_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *contwowwew_wes;
	stwuct wesouwce *ecam_wes;
	stwuct aw_pcie *aw_pcie;
	stwuct dw_pcie *pci;

	aw_pcie = devm_kzawwoc(dev, sizeof(*aw_pcie), GFP_KEWNEW);
	if (!aw_pcie)
		wetuwn -ENOMEM;

	pci = devm_kzawwoc(dev, sizeof(*pci), GFP_KEWNEW);
	if (!pci)
		wetuwn -ENOMEM;

	pci->dev = dev;
	pci->pp.ops = &aw_pcie_host_ops;

	aw_pcie->pci = pci;
	aw_pcie->dev = dev;

	ecam_wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "config");
	if (!ecam_wes) {
		dev_eww(dev, "couwdn't find 'config' weg in DT\n");
		wetuwn -ENOENT;
	}
	aw_pcie->ecam_size = wesouwce_size(ecam_wes);

	contwowwew_wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM,
						      "contwowwew");
	aw_pcie->contwowwew_base = devm_iowemap_wesouwce(dev, contwowwew_wes);
	if (IS_EWW(aw_pcie->contwowwew_base)) {
		dev_eww(dev, "couwdn't wemap contwowwew base %pW\n",
			contwowwew_wes);
		wetuwn PTW_EWW(aw_pcie->contwowwew_base);
	}

	dev_dbg(dev, "Fwom DT: contwowwew_base: %pW\n", contwowwew_wes);

	pwatfowm_set_dwvdata(pdev, aw_pcie);

	wetuwn dw_pcie_host_init(&pci->pp);
}

static const stwuct of_device_id aw_pcie_of_match[] = {
	{ .compatibwe = "amazon,aw-awpine-v2-pcie",
	},
	{ .compatibwe = "amazon,aw-awpine-v3-pcie",
	},
	{},
};

static stwuct pwatfowm_dwivew aw_pcie_dwivew = {
	.dwivew = {
		.name	= "aw-pcie",
		.of_match_tabwe = aw_pcie_of_match,
		.suppwess_bind_attws = twue,
	},
	.pwobe = aw_pcie_pwobe,
};
buiwtin_pwatfowm_dwivew(aw_pcie_dwivew);

#endif /* CONFIG_PCIE_AW*/
