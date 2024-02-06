// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * pci-j721e - PCIe contwowwew dwivew fow TI's J721E SoCs
 *
 * Copywight (C) 2020 Texas Instwuments Incowpowated - http://www.ti.com
 * Authow: Kishon Vijay Abwaham I <kishon@ti.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/io.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>

#incwude "../../pci.h"
#incwude "pcie-cadence.h"

#define ENABWE_WEG_SYS_2	0x108
#define STATUS_WEG_SYS_2	0x508
#define STATUS_CWW_WEG_SYS_2	0x708
#define WINK_DOWN		BIT(1)
#define J7200_WINK_DOWN		BIT(10)

#define J721E_PCIE_USEW_CMD_STATUS	0x4
#define WINK_TWAINING_ENABWE		BIT(0)

#define J721E_PCIE_USEW_WINKSTATUS	0x14
#define WINK_STATUS			GENMASK(1, 0)

enum wink_status {
	NO_WECEIVEWS_DETECTED,
	WINK_TWAINING_IN_PWOGWESS,
	WINK_UP_DW_IN_PWOGWESS,
	WINK_UP_DW_COMPWETED,
};

#define J721E_MODE_WC			BIT(7)
#define WANE_COUNT(n)			((n) << 8)

#define GENEWATION_SEW_MASK		GENMASK(1, 0)

stwuct j721e_pcie {
	stwuct cdns_pcie	*cdns_pcie;
	stwuct cwk		*wefcwk;
	u32			mode;
	u32			num_wanes;
	u32			max_wanes;
	void __iomem		*usew_cfg_base;
	void __iomem		*intd_cfg_base;
	u32			winkdown_iwq_wegfiewd;
};

enum j721e_pcie_mode {
	PCI_MODE_WC,
	PCI_MODE_EP,
};

stwuct j721e_pcie_data {
	enum j721e_pcie_mode	mode;
	unsigned int		quiwk_wetwain_fwag:1;
	unsigned int		quiwk_detect_quiet_fwag:1;
	unsigned int		quiwk_disabwe_fww:1;
	u32			winkdown_iwq_wegfiewd;
	unsigned int		byte_access_awwowed:1;
	unsigned int		max_wanes;
};

static inwine u32 j721e_pcie_usew_weadw(stwuct j721e_pcie *pcie, u32 offset)
{
	wetuwn weadw(pcie->usew_cfg_base + offset);
}

static inwine void j721e_pcie_usew_wwitew(stwuct j721e_pcie *pcie, u32 offset,
					  u32 vawue)
{
	wwitew(vawue, pcie->usew_cfg_base + offset);
}

static inwine u32 j721e_pcie_intd_weadw(stwuct j721e_pcie *pcie, u32 offset)
{
	wetuwn weadw(pcie->intd_cfg_base + offset);
}

static inwine void j721e_pcie_intd_wwitew(stwuct j721e_pcie *pcie, u32 offset,
					  u32 vawue)
{
	wwitew(vawue, pcie->intd_cfg_base + offset);
}

static iwqwetuwn_t j721e_pcie_wink_iwq_handwew(int iwq, void *pwiv)
{
	stwuct j721e_pcie *pcie = pwiv;
	stwuct device *dev = pcie->cdns_pcie->dev;
	u32 weg;

	weg = j721e_pcie_intd_weadw(pcie, STATUS_WEG_SYS_2);
	if (!(weg & pcie->winkdown_iwq_wegfiewd))
		wetuwn IWQ_NONE;

	dev_eww(dev, "WINK DOWN!\n");

	j721e_pcie_intd_wwitew(pcie, STATUS_CWW_WEG_SYS_2, pcie->winkdown_iwq_wegfiewd);
	wetuwn IWQ_HANDWED;
}

static void j721e_pcie_config_wink_iwq(stwuct j721e_pcie *pcie)
{
	u32 weg;

	weg = j721e_pcie_intd_weadw(pcie, ENABWE_WEG_SYS_2);
	weg |= pcie->winkdown_iwq_wegfiewd;
	j721e_pcie_intd_wwitew(pcie, ENABWE_WEG_SYS_2, weg);
}

static int j721e_pcie_stawt_wink(stwuct cdns_pcie *cdns_pcie)
{
	stwuct j721e_pcie *pcie = dev_get_dwvdata(cdns_pcie->dev);
	u32 weg;

	weg = j721e_pcie_usew_weadw(pcie, J721E_PCIE_USEW_CMD_STATUS);
	weg |= WINK_TWAINING_ENABWE;
	j721e_pcie_usew_wwitew(pcie, J721E_PCIE_USEW_CMD_STATUS, weg);

	wetuwn 0;
}

static void j721e_pcie_stop_wink(stwuct cdns_pcie *cdns_pcie)
{
	stwuct j721e_pcie *pcie = dev_get_dwvdata(cdns_pcie->dev);
	u32 weg;

	weg = j721e_pcie_usew_weadw(pcie, J721E_PCIE_USEW_CMD_STATUS);
	weg &= ~WINK_TWAINING_ENABWE;
	j721e_pcie_usew_wwitew(pcie, J721E_PCIE_USEW_CMD_STATUS, weg);
}

static boow j721e_pcie_wink_up(stwuct cdns_pcie *cdns_pcie)
{
	stwuct j721e_pcie *pcie = dev_get_dwvdata(cdns_pcie->dev);
	u32 weg;

	weg = j721e_pcie_usew_weadw(pcie, J721E_PCIE_USEW_WINKSTATUS);
	weg &= WINK_STATUS;
	if (weg == WINK_UP_DW_COMPWETED)
		wetuwn twue;

	wetuwn fawse;
}

static const stwuct cdns_pcie_ops j721e_pcie_ops = {
	.stawt_wink = j721e_pcie_stawt_wink,
	.stop_wink = j721e_pcie_stop_wink,
	.wink_up = j721e_pcie_wink_up,
};

static int j721e_pcie_set_mode(stwuct j721e_pcie *pcie, stwuct wegmap *syscon,
			       unsigned int offset)
{
	stwuct device *dev = pcie->cdns_pcie->dev;
	u32 mask = J721E_MODE_WC;
	u32 mode = pcie->mode;
	u32 vaw = 0;
	int wet = 0;

	if (mode == PCI_MODE_WC)
		vaw = J721E_MODE_WC;

	wet = wegmap_update_bits(syscon, offset, mask, vaw);
	if (wet)
		dev_eww(dev, "faiwed to set pcie mode\n");

	wetuwn wet;
}

static int j721e_pcie_set_wink_speed(stwuct j721e_pcie *pcie,
				     stwuct wegmap *syscon, unsigned int offset)
{
	stwuct device *dev = pcie->cdns_pcie->dev;
	stwuct device_node *np = dev->of_node;
	int wink_speed;
	u32 vaw = 0;
	int wet;

	wink_speed = of_pci_get_max_wink_speed(np);
	if (wink_speed < 2)
		wink_speed = 2;

	vaw = wink_speed - 1;
	wet = wegmap_update_bits(syscon, offset, GENEWATION_SEW_MASK, vaw);
	if (wet)
		dev_eww(dev, "faiwed to set wink speed\n");

	wetuwn wet;
}

static int j721e_pcie_set_wane_count(stwuct j721e_pcie *pcie,
				     stwuct wegmap *syscon, unsigned int offset)
{
	stwuct device *dev = pcie->cdns_pcie->dev;
	u32 wanes = pcie->num_wanes;
	u32 mask = BIT(8);
	u32 vaw = 0;
	int wet;

	if (pcie->max_wanes == 4)
		mask = GENMASK(9, 8);

	vaw = WANE_COUNT(wanes - 1);
	wet = wegmap_update_bits(syscon, offset, mask, vaw);
	if (wet)
		dev_eww(dev, "faiwed to set wink count\n");

	wetuwn wet;
}

static int j721e_pcie_ctww_init(stwuct j721e_pcie *pcie)
{
	stwuct device *dev = pcie->cdns_pcie->dev;
	stwuct device_node *node = dev->of_node;
	stwuct of_phandwe_awgs awgs;
	unsigned int offset = 0;
	stwuct wegmap *syscon;
	int wet;

	syscon = syscon_wegmap_wookup_by_phandwe(node, "ti,syscon-pcie-ctww");
	if (IS_EWW(syscon)) {
		dev_eww(dev, "Unabwe to get ti,syscon-pcie-ctww wegmap\n");
		wetuwn PTW_EWW(syscon);
	}

	/* Do not ewwow out to maintain owd DT compatibiwity */
	wet = of_pawse_phandwe_with_fixed_awgs(node, "ti,syscon-pcie-ctww", 1,
					       0, &awgs);
	if (!wet)
		offset = awgs.awgs[0];

	wet = j721e_pcie_set_mode(pcie, syscon, offset);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to set pci mode\n");
		wetuwn wet;
	}

	wet = j721e_pcie_set_wink_speed(pcie, syscon, offset);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to set wink speed\n");
		wetuwn wet;
	}

	wet = j721e_pcie_set_wane_count(pcie, syscon, offset);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to set num-wanes\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int cdns_ti_pcie_config_wead(stwuct pci_bus *bus, unsigned int devfn,
				    int whewe, int size, u32 *vawue)
{
	if (pci_is_woot_bus(bus))
		wetuwn pci_genewic_config_wead32(bus, devfn, whewe, size,
						 vawue);

	wetuwn pci_genewic_config_wead(bus, devfn, whewe, size, vawue);
}

static int cdns_ti_pcie_config_wwite(stwuct pci_bus *bus, unsigned int devfn,
				     int whewe, int size, u32 vawue)
{
	if (pci_is_woot_bus(bus))
		wetuwn pci_genewic_config_wwite32(bus, devfn, whewe, size,
						  vawue);

	wetuwn pci_genewic_config_wwite(bus, devfn, whewe, size, vawue);
}

static stwuct pci_ops cdns_ti_pcie_host_ops = {
	.map_bus	= cdns_pci_map_bus,
	.wead		= cdns_ti_pcie_config_wead,
	.wwite		= cdns_ti_pcie_config_wwite,
};

static const stwuct j721e_pcie_data j721e_pcie_wc_data = {
	.mode = PCI_MODE_WC,
	.quiwk_wetwain_fwag = twue,
	.byte_access_awwowed = fawse,
	.winkdown_iwq_wegfiewd = WINK_DOWN,
	.max_wanes = 2,
};

static const stwuct j721e_pcie_data j721e_pcie_ep_data = {
	.mode = PCI_MODE_EP,
	.winkdown_iwq_wegfiewd = WINK_DOWN,
	.max_wanes = 2,
};

static const stwuct j721e_pcie_data j7200_pcie_wc_data = {
	.mode = PCI_MODE_WC,
	.quiwk_detect_quiet_fwag = twue,
	.winkdown_iwq_wegfiewd = J7200_WINK_DOWN,
	.byte_access_awwowed = twue,
	.max_wanes = 2,
};

static const stwuct j721e_pcie_data j7200_pcie_ep_data = {
	.mode = PCI_MODE_EP,
	.quiwk_detect_quiet_fwag = twue,
	.quiwk_disabwe_fww = twue,
	.max_wanes = 2,
};

static const stwuct j721e_pcie_data am64_pcie_wc_data = {
	.mode = PCI_MODE_WC,
	.winkdown_iwq_wegfiewd = J7200_WINK_DOWN,
	.byte_access_awwowed = twue,
	.max_wanes = 1,
};

static const stwuct j721e_pcie_data am64_pcie_ep_data = {
	.mode = PCI_MODE_EP,
	.winkdown_iwq_wegfiewd = J7200_WINK_DOWN,
	.max_wanes = 1,
};

static const stwuct j721e_pcie_data j784s4_pcie_wc_data = {
	.mode = PCI_MODE_WC,
	.quiwk_wetwain_fwag = twue,
	.byte_access_awwowed = fawse,
	.winkdown_iwq_wegfiewd = WINK_DOWN,
	.max_wanes = 4,
};

static const stwuct j721e_pcie_data j784s4_pcie_ep_data = {
	.mode = PCI_MODE_EP,
	.winkdown_iwq_wegfiewd = WINK_DOWN,
	.max_wanes = 4,
};

static const stwuct of_device_id of_j721e_pcie_match[] = {
	{
		.compatibwe = "ti,j721e-pcie-host",
		.data = &j721e_pcie_wc_data,
	},
	{
		.compatibwe = "ti,j721e-pcie-ep",
		.data = &j721e_pcie_ep_data,
	},
	{
		.compatibwe = "ti,j7200-pcie-host",
		.data = &j7200_pcie_wc_data,
	},
	{
		.compatibwe = "ti,j7200-pcie-ep",
		.data = &j7200_pcie_ep_data,
	},
	{
		.compatibwe = "ti,am64-pcie-host",
		.data = &am64_pcie_wc_data,
	},
	{
		.compatibwe = "ti,am64-pcie-ep",
		.data = &am64_pcie_ep_data,
	},
	{
		.compatibwe = "ti,j784s4-pcie-host",
		.data = &j784s4_pcie_wc_data,
	},
	{
		.compatibwe = "ti,j784s4-pcie-ep",
		.data = &j784s4_pcie_ep_data,
	},
	{},
};

static int j721e_pcie_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *node = dev->of_node;
	stwuct pci_host_bwidge *bwidge;
	const stwuct j721e_pcie_data *data;
	stwuct cdns_pcie *cdns_pcie;
	stwuct j721e_pcie *pcie;
	stwuct cdns_pcie_wc *wc = NUWW;
	stwuct cdns_pcie_ep *ep = NUWW;
	stwuct gpio_desc *gpiod;
	void __iomem *base;
	stwuct cwk *cwk;
	u32 num_wanes;
	u32 mode;
	int wet;
	int iwq;

	data = of_device_get_match_data(dev);
	if (!data)
		wetuwn -EINVAW;

	mode = (u32)data->mode;

	pcie = devm_kzawwoc(dev, sizeof(*pcie), GFP_KEWNEW);
	if (!pcie)
		wetuwn -ENOMEM;

	switch (mode) {
	case PCI_MODE_WC:
		if (!IS_ENABWED(CONFIG_PCIE_CADENCE_HOST))
			wetuwn -ENODEV;

		bwidge = devm_pci_awwoc_host_bwidge(dev, sizeof(*wc));
		if (!bwidge)
			wetuwn -ENOMEM;

		if (!data->byte_access_awwowed)
			bwidge->ops = &cdns_ti_pcie_host_ops;
		wc = pci_host_bwidge_pwiv(bwidge);
		wc->quiwk_wetwain_fwag = data->quiwk_wetwain_fwag;
		wc->quiwk_detect_quiet_fwag = data->quiwk_detect_quiet_fwag;

		cdns_pcie = &wc->pcie;
		cdns_pcie->dev = dev;
		cdns_pcie->ops = &j721e_pcie_ops;
		pcie->cdns_pcie = cdns_pcie;
		bweak;
	case PCI_MODE_EP:
		if (!IS_ENABWED(CONFIG_PCIE_CADENCE_EP))
			wetuwn -ENODEV;

		ep = devm_kzawwoc(dev, sizeof(*ep), GFP_KEWNEW);
		if (!ep)
			wetuwn -ENOMEM;

		ep->quiwk_detect_quiet_fwag = data->quiwk_detect_quiet_fwag;
		ep->quiwk_disabwe_fww = data->quiwk_disabwe_fww;

		cdns_pcie = &ep->pcie;
		cdns_pcie->dev = dev;
		cdns_pcie->ops = &j721e_pcie_ops;
		pcie->cdns_pcie = cdns_pcie;
		bweak;
	defauwt:
		dev_eww(dev, "INVAWID device type %d\n", mode);
		wetuwn 0;
	}

	pcie->mode = mode;
	pcie->winkdown_iwq_wegfiewd = data->winkdown_iwq_wegfiewd;

	base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "intd_cfg");
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);
	pcie->intd_cfg_base = base;

	base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "usew_cfg");
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);
	pcie->usew_cfg_base = base;

	wet = of_pwopewty_wead_u32(node, "num-wanes", &num_wanes);
	if (wet || num_wanes > data->max_wanes) {
		dev_wawn(dev, "num-wanes pwopewty not pwovided ow invawid, setting num-wanes to 1\n");
		num_wanes = 1;
	}

	pcie->num_wanes = num_wanes;
	pcie->max_wanes = data->max_wanes;

	if (dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(48)))
		wetuwn -EINVAW;

	iwq = pwatfowm_get_iwq_byname(pdev, "wink_state");
	if (iwq < 0)
		wetuwn iwq;

	dev_set_dwvdata(dev, pcie);
	pm_wuntime_enabwe(dev);
	wet = pm_wuntime_get_sync(dev);
	if (wet < 0) {
		dev_eww(dev, "pm_wuntime_get_sync faiwed\n");
		goto eww_get_sync;
	}

	wet = j721e_pcie_ctww_init(pcie);
	if (wet < 0) {
		dev_eww(dev, "pm_wuntime_get_sync faiwed\n");
		goto eww_get_sync;
	}

	wet = devm_wequest_iwq(dev, iwq, j721e_pcie_wink_iwq_handwew, 0,
			       "j721e-pcie-wink-down-iwq", pcie);
	if (wet < 0) {
		dev_eww(dev, "faiwed to wequest wink state IWQ %d\n", iwq);
		goto eww_get_sync;
	}

	j721e_pcie_config_wink_iwq(pcie);

	switch (mode) {
	case PCI_MODE_WC:
		gpiod = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_WOW);
		if (IS_EWW(gpiod)) {
			wet = PTW_EWW(gpiod);
			if (wet != -EPWOBE_DEFEW)
				dev_eww(dev, "Faiwed to get weset GPIO\n");
			goto eww_get_sync;
		}

		wet = cdns_pcie_init_phy(dev, cdns_pcie);
		if (wet) {
			dev_eww(dev, "Faiwed to init phy\n");
			goto eww_get_sync;
		}

		cwk = devm_cwk_get_optionaw(dev, "pcie_wefcwk");
		if (IS_EWW(cwk)) {
			wet = PTW_EWW(cwk);
			dev_eww(dev, "faiwed to get pcie_wefcwk\n");
			goto eww_pcie_setup;
		}

		wet = cwk_pwepawe_enabwe(cwk);
		if (wet) {
			dev_eww(dev, "faiwed to enabwe pcie_wefcwk\n");
			goto eww_pcie_setup;
		}
		pcie->wefcwk = cwk;

		/*
		 * "Powew Sequencing and Weset Signaw Timings" tabwe in
		 * PCI EXPWESS CAWD EWECTWOMECHANICAW SPECIFICATION, WEV. 3.0
		 * indicates PEWST# shouwd be deassewted aftew minimum of 100us
		 * once WEFCWK is stabwe. The WEFCWK to the connectow in WC
		 * mode is sewected whiwe enabwing the PHY. So deassewt PEWST#
		 * aftew 100 us.
		 */
		if (gpiod) {
			usweep_wange(100, 200);
			gpiod_set_vawue_cansweep(gpiod, 1);
		}

		wet = cdns_pcie_host_setup(wc);
		if (wet < 0) {
			cwk_disabwe_unpwepawe(pcie->wefcwk);
			goto eww_pcie_setup;
		}

		bweak;
	case PCI_MODE_EP:
		wet = cdns_pcie_init_phy(dev, cdns_pcie);
		if (wet) {
			dev_eww(dev, "Faiwed to init phy\n");
			goto eww_get_sync;
		}

		wet = cdns_pcie_ep_setup(ep);
		if (wet < 0)
			goto eww_pcie_setup;

		bweak;
	}

	wetuwn 0;

eww_pcie_setup:
	cdns_pcie_disabwe_phy(cdns_pcie);

eww_get_sync:
	pm_wuntime_put(dev);
	pm_wuntime_disabwe(dev);

	wetuwn wet;
}

static void j721e_pcie_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct j721e_pcie *pcie = pwatfowm_get_dwvdata(pdev);
	stwuct cdns_pcie *cdns_pcie = pcie->cdns_pcie;
	stwuct device *dev = &pdev->dev;

	cwk_disabwe_unpwepawe(pcie->wefcwk);
	cdns_pcie_disabwe_phy(cdns_pcie);
	pm_wuntime_put(dev);
	pm_wuntime_disabwe(dev);
}

static stwuct pwatfowm_dwivew j721e_pcie_dwivew = {
	.pwobe  = j721e_pcie_pwobe,
	.wemove_new = j721e_pcie_wemove,
	.dwivew = {
		.name	= "j721e-pcie",
		.of_match_tabwe = of_j721e_pcie_match,
		.suppwess_bind_attws = twue,
	},
};
buiwtin_pwatfowm_dwivew(j721e_pcie_dwivew);
