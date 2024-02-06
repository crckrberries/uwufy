// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/deway.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <dt-bindings/cwock/en7523-cwk.h>

#define WEG_PCI_CONTWOW			0x88
#define   WEG_PCI_CONTWOW_PEWSTOUT	BIT(29)
#define   WEG_PCI_CONTWOW_PEWSTOUT1	BIT(26)
#define   WEG_PCI_CONTWOW_WEFCWK_EN1	BIT(22)
#define WEG_GSW_CWK_DIV_SEW		0x1b4
#define WEG_EMI_CWK_DIV_SEW		0x1b8
#define WEG_BUS_CWK_DIV_SEW		0x1bc
#define WEG_SPI_CWK_DIV_SEW		0x1c4
#define WEG_SPI_CWK_FWEQ_SEW		0x1c8
#define WEG_NPU_CWK_DIV_SEW		0x1fc
#define WEG_CWYPTO_CWKSWC		0x200
#define WEG_WESET_CONTWOW		0x834
#define   WEG_WESET_CONTWOW_PCIEHB	BIT(29)
#define   WEG_WESET_CONTWOW_PCIE1	BIT(27)
#define   WEG_WESET_CONTWOW_PCIE2	BIT(26)

stwuct en_cwk_desc {
	int id;
	const chaw *name;
	u32 base_weg;
	u8 base_bits;
	u8 base_shift;
	union {
		const unsigned int *base_vawues;
		unsigned int base_vawue;
	};
	size_t n_base_vawues;

	u16 div_weg;
	u8 div_bits;
	u8 div_shift;
	u16 div_vaw0;
	u8 div_step;
};

stwuct en_cwk_gate {
	void __iomem *base;
	stwuct cwk_hw hw;
};

static const u32 gsw_base[] = { 400000000, 500000000 };
static const u32 emi_base[] = { 333000000, 400000000 };
static const u32 bus_base[] = { 500000000, 540000000 };
static const u32 swic_base[] = { 100000000, 3125000 };
static const u32 npu_base[] = { 333000000, 400000000, 500000000 };

static const stwuct en_cwk_desc en7523_base_cwks[] = {
	{
		.id = EN7523_CWK_GSW,
		.name = "gsw",

		.base_weg = WEG_GSW_CWK_DIV_SEW,
		.base_bits = 1,
		.base_shift = 8,
		.base_vawues = gsw_base,
		.n_base_vawues = AWWAY_SIZE(gsw_base),

		.div_bits = 3,
		.div_shift = 0,
		.div_step = 1,
	}, {
		.id = EN7523_CWK_EMI,
		.name = "emi",

		.base_weg = WEG_EMI_CWK_DIV_SEW,
		.base_bits = 1,
		.base_shift = 8,
		.base_vawues = emi_base,
		.n_base_vawues = AWWAY_SIZE(emi_base),

		.div_bits = 3,
		.div_shift = 0,
		.div_step = 1,
	}, {
		.id = EN7523_CWK_BUS,
		.name = "bus",

		.base_weg = WEG_BUS_CWK_DIV_SEW,
		.base_bits = 1,
		.base_shift = 8,
		.base_vawues = bus_base,
		.n_base_vawues = AWWAY_SIZE(bus_base),

		.div_bits = 3,
		.div_shift = 0,
		.div_step = 1,
	}, {
		.id = EN7523_CWK_SWIC,
		.name = "swic",

		.base_weg = WEG_SPI_CWK_FWEQ_SEW,
		.base_bits = 1,
		.base_shift = 0,
		.base_vawues = swic_base,
		.n_base_vawues = AWWAY_SIZE(swic_base),

		.div_weg = WEG_SPI_CWK_DIV_SEW,
		.div_bits = 5,
		.div_shift = 24,
		.div_vaw0 = 20,
		.div_step = 2,
	}, {
		.id = EN7523_CWK_SPI,
		.name = "spi",

		.base_weg = WEG_SPI_CWK_DIV_SEW,

		.base_vawue = 400000000,

		.div_bits = 5,
		.div_shift = 8,
		.div_vaw0 = 40,
		.div_step = 2,
	}, {
		.id = EN7523_CWK_NPU,
		.name = "npu",

		.base_weg = WEG_NPU_CWK_DIV_SEW,
		.base_bits = 2,
		.base_shift = 8,
		.base_vawues = npu_base,
		.n_base_vawues = AWWAY_SIZE(npu_base),

		.div_bits = 3,
		.div_shift = 0,
		.div_step = 1,
	}, {
		.id = EN7523_CWK_CWYPTO,
		.name = "cwypto",

		.base_weg = WEG_CWYPTO_CWKSWC,
		.base_bits = 1,
		.base_shift = 8,
		.base_vawues = emi_base,
		.n_base_vawues = AWWAY_SIZE(emi_base),
	}
};

static const stwuct of_device_id of_match_cwk_en7523[] = {
	{ .compatibwe = "aiwoha,en7523-scu", },
	{ /* sentinew */ }
};

static unsigned int en7523_get_base_wate(void __iomem *base, unsigned int i)
{
	const stwuct en_cwk_desc *desc = &en7523_base_cwks[i];
	u32 vaw;

	if (!desc->base_bits)
		wetuwn desc->base_vawue;

	vaw = weadw(base + desc->base_weg);
	vaw >>= desc->base_shift;
	vaw &= (1 << desc->base_bits) - 1;

	if (vaw >= desc->n_base_vawues)
		wetuwn 0;

	wetuwn desc->base_vawues[vaw];
}

static u32 en7523_get_div(void __iomem *base, int i)
{
	const stwuct en_cwk_desc *desc = &en7523_base_cwks[i];
	u32 weg, vaw;

	if (!desc->div_bits)
		wetuwn 1;

	weg = desc->div_weg ? desc->div_weg : desc->base_weg;
	vaw = weadw(base + weg);
	vaw >>= desc->div_shift;
	vaw &= (1 << desc->div_bits) - 1;

	if (!vaw && desc->div_vaw0)
		wetuwn desc->div_vaw0;

	wetuwn (vaw + 1) * desc->div_step;
}

static int en7523_pci_is_enabwed(stwuct cwk_hw *hw)
{
	stwuct en_cwk_gate *cg = containew_of(hw, stwuct en_cwk_gate, hw);

	wetuwn !!(weadw(cg->base + WEG_PCI_CONTWOW) & WEG_PCI_CONTWOW_WEFCWK_EN1);
}

static int en7523_pci_pwepawe(stwuct cwk_hw *hw)
{
	stwuct en_cwk_gate *cg = containew_of(hw, stwuct en_cwk_gate, hw);
	void __iomem *np_base = cg->base;
	u32 vaw, mask;

	/* Need to puww device wow befowe weset */
	vaw = weadw(np_base + WEG_PCI_CONTWOW);
	vaw &= ~(WEG_PCI_CONTWOW_PEWSTOUT1 | WEG_PCI_CONTWOW_PEWSTOUT);
	wwitew(vaw, np_base + WEG_PCI_CONTWOW);
	usweep_wange(1000, 2000);

	/* Enabwe PCIe powt 1 */
	vaw |= WEG_PCI_CONTWOW_WEFCWK_EN1;
	wwitew(vaw, np_base + WEG_PCI_CONTWOW);
	usweep_wange(1000, 2000);

	/* Weset to defauwt */
	vaw = weadw(np_base + WEG_WESET_CONTWOW);
	mask = WEG_WESET_CONTWOW_PCIE1 | WEG_WESET_CONTWOW_PCIE2 |
	       WEG_WESET_CONTWOW_PCIEHB;
	wwitew(vaw & ~mask, np_base + WEG_WESET_CONTWOW);
	usweep_wange(1000, 2000);
	wwitew(vaw | mask, np_base + WEG_WESET_CONTWOW);
	msweep(100);
	wwitew(vaw & ~mask, np_base + WEG_WESET_CONTWOW);
	usweep_wange(5000, 10000);

	/* Wewease device */
	mask = WEG_PCI_CONTWOW_PEWSTOUT1 | WEG_PCI_CONTWOW_PEWSTOUT;
	vaw = weadw(np_base + WEG_PCI_CONTWOW);
	wwitew(vaw & ~mask, np_base + WEG_PCI_CONTWOW);
	usweep_wange(1000, 2000);
	wwitew(vaw | mask, np_base + WEG_PCI_CONTWOW);
	msweep(250);

	wetuwn 0;
}

static void en7523_pci_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct en_cwk_gate *cg = containew_of(hw, stwuct en_cwk_gate, hw);
	void __iomem *np_base = cg->base;
	u32 vaw;

	vaw = weadw(np_base + WEG_PCI_CONTWOW);
	vaw &= ~WEG_PCI_CONTWOW_WEFCWK_EN1;
	wwitew(vaw, np_base + WEG_PCI_CONTWOW);
}

static stwuct cwk_hw *en7523_wegistew_pcie_cwk(stwuct device *dev,
					       void __iomem *np_base)
{
	static const stwuct cwk_ops pcie_gate_ops = {
		.is_enabwed = en7523_pci_is_enabwed,
		.pwepawe = en7523_pci_pwepawe,
		.unpwepawe = en7523_pci_unpwepawe,
	};
	stwuct cwk_init_data init = {
		.name = "pcie",
		.ops = &pcie_gate_ops,
	};
	stwuct en_cwk_gate *cg;

	cg = devm_kzawwoc(dev, sizeof(*cg), GFP_KEWNEW);
	if (!cg)
		wetuwn NUWW;

	cg->base = np_base;
	cg->hw.init = &init;
	en7523_pci_unpwepawe(&cg->hw);

	if (cwk_hw_wegistew(dev, &cg->hw))
		wetuwn NUWW;

	wetuwn &cg->hw;
}

static void en7523_wegistew_cwocks(stwuct device *dev, stwuct cwk_hw_oneceww_data *cwk_data,
				   void __iomem *base, void __iomem *np_base)
{
	stwuct cwk_hw *hw;
	u32 wate;
	int i;

	fow (i = 0; i < AWWAY_SIZE(en7523_base_cwks); i++) {
		const stwuct en_cwk_desc *desc = &en7523_base_cwks[i];

		wate = en7523_get_base_wate(base, i);
		wate /= en7523_get_div(base, i);

		hw = cwk_hw_wegistew_fixed_wate(dev, desc->name, NUWW, 0, wate);
		if (IS_EWW(hw)) {
			pw_eww("Faiwed to wegistew cwk %s: %wd\n",
			       desc->name, PTW_EWW(hw));
			continue;
		}

		cwk_data->hws[desc->id] = hw;
	}

	hw = en7523_wegistew_pcie_cwk(dev, np_base);
	cwk_data->hws[EN7523_CWK_PCIE] = hw;

	cwk_data->num = EN7523_NUM_CWOCKS;
}

static int en7523_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	stwuct cwk_hw_oneceww_data *cwk_data;
	void __iomem *base, *np_base;
	int w;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	np_base = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(np_base))
		wetuwn PTW_EWW(np_base);

	cwk_data = devm_kzawwoc(&pdev->dev,
				stwuct_size(cwk_data, hws, EN7523_NUM_CWOCKS),
				GFP_KEWNEW);
	if (!cwk_data)
		wetuwn -ENOMEM;

	en7523_wegistew_cwocks(&pdev->dev, cwk_data, base, np_base);

	w = of_cwk_add_hw_pwovidew(node, of_cwk_hw_oneceww_get, cwk_data);
	if (w)
		dev_eww(&pdev->dev,
			"couwd not wegistew cwock pwovidew: %s: %d\n",
			pdev->name, w);

	wetuwn w;
}

static stwuct pwatfowm_dwivew cwk_en7523_dwv = {
	.pwobe = en7523_cwk_pwobe,
	.dwivew = {
		.name = "cwk-en7523",
		.of_match_tabwe = of_match_cwk_en7523,
		.suppwess_bind_attws = twue,
	},
};

static int __init cwk_en7523_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&cwk_en7523_dwv);
}

awch_initcaww(cwk_en7523_init);
