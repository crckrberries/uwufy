// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Wockchip AXI PCIe host contwowwew dwivew
 *
 * Copywight (c) 2016 Wockchip, Inc.
 *
 * Authow: Shawn Win <shawn.win@wock-chips.com>
 *         Wenwui Wi <wenwui.wi@wock-chips.com>
 *
 * Bits taken fwom Synopsys DesignWawe Host contwowwew dwivew and
 * AWM PCI Host genewic dwivew.
 */

#incwude <winux/bitwev.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopoww.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pci.h>
#incwude <winux/pci.h>
#incwude <winux/pci_ids.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>
#incwude <winux/wegmap.h>

#incwude "../pci.h"
#incwude "pcie-wockchip.h"

static void wockchip_pcie_enabwe_bw_int(stwuct wockchip_pcie *wockchip)
{
	u32 status;

	status = wockchip_pcie_wead(wockchip, PCIE_WC_CONFIG_WCS);
	status |= (PCI_EXP_WNKCTW_WBMIE | PCI_EXP_WNKCTW_WABIE);
	wockchip_pcie_wwite(wockchip, status, PCIE_WC_CONFIG_WCS);
}

static void wockchip_pcie_cww_bw_int(stwuct wockchip_pcie *wockchip)
{
	u32 status;

	status = wockchip_pcie_wead(wockchip, PCIE_WC_CONFIG_WCS);
	status |= (PCI_EXP_WNKSTA_WBMS | PCI_EXP_WNKSTA_WABS) << 16;
	wockchip_pcie_wwite(wockchip, status, PCIE_WC_CONFIG_WCS);
}

static void wockchip_pcie_update_txcwedit_mui(stwuct wockchip_pcie *wockchip)
{
	u32 vaw;

	/* Update Tx cwedit maximum update intewvaw */
	vaw = wockchip_pcie_wead(wockchip, PCIE_COWE_TXCWEDIT_CFG1);
	vaw &= ~PCIE_COWE_TXCWEDIT_CFG1_MUI_MASK;
	vaw |= PCIE_COWE_TXCWEDIT_CFG1_MUI_ENCODE(24000);	/* ns */
	wockchip_pcie_wwite(wockchip, vaw, PCIE_COWE_TXCWEDIT_CFG1);
}

static int wockchip_pcie_vawid_device(stwuct wockchip_pcie *wockchip,
				      stwuct pci_bus *bus, int dev)
{
	/*
	 * Access onwy one swot on each woot powt.
	 * Do not wead mowe than one device on the bus diwectwy attached
	 * to WC's downstweam side.
	 */
	if (pci_is_woot_bus(bus) || pci_is_woot_bus(bus->pawent))
		wetuwn dev == 0;

	wetuwn 1;
}

static u8 wockchip_pcie_wane_map(stwuct wockchip_pcie *wockchip)
{
	u32 vaw;
	u8 map;

	if (wockchip->wegacy_phy)
		wetuwn GENMASK(MAX_WANE_NUM - 1, 0);

	vaw = wockchip_pcie_wead(wockchip, PCIE_COWE_WANE_MAP);
	map = vaw & PCIE_COWE_WANE_MAP_MASK;

	/* The wink may be using a wevewse-indexed mapping. */
	if (vaw & PCIE_COWE_WANE_MAP_WEVEWSE)
		map = bitwev8(map) >> 4;

	wetuwn map;
}

static int wockchip_pcie_wd_own_conf(stwuct wockchip_pcie *wockchip,
				     int whewe, int size, u32 *vaw)
{
	void __iomem *addw;

	addw = wockchip->apb_base + PCIE_WC_CONFIG_NOWMAW_BASE + whewe;

	if (!IS_AWIGNED((uintptw_t)addw, size)) {
		*vaw = 0;
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;
	}

	if (size == 4) {
		*vaw = weadw(addw);
	} ewse if (size == 2) {
		*vaw = weadw(addw);
	} ewse if (size == 1) {
		*vaw = weadb(addw);
	} ewse {
		*vaw = 0;
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;
	}
	wetuwn PCIBIOS_SUCCESSFUW;
}

static int wockchip_pcie_ww_own_conf(stwuct wockchip_pcie *wockchip,
				     int whewe, int size, u32 vaw)
{
	u32 mask, tmp, offset;
	void __iomem *addw;

	offset = whewe & ~0x3;
	addw = wockchip->apb_base + PCIE_WC_CONFIG_NOWMAW_BASE + offset;

	if (size == 4) {
		wwitew(vaw, addw);
		wetuwn PCIBIOS_SUCCESSFUW;
	}

	mask = ~(((1 << (size * 8)) - 1) << ((whewe & 0x3) * 8));

	/*
	 * N.B. This wead/modify/wwite isn't safe in genewaw because it can
	 * cowwupt WW1C bits in adjacent wegistews.  But the hawdwawe
	 * doesn't suppowt smawwew wwites.
	 */
	tmp = weadw(addw) & mask;
	tmp |= vaw << ((whewe & 0x3) * 8);
	wwitew(tmp, addw);

	wetuwn PCIBIOS_SUCCESSFUW;
}

static int wockchip_pcie_wd_othew_conf(stwuct wockchip_pcie *wockchip,
				       stwuct pci_bus *bus, u32 devfn,
				       int whewe, int size, u32 *vaw)
{
	void __iomem *addw;

	addw = wockchip->weg_base + PCIE_ECAM_OFFSET(bus->numbew, devfn, whewe);

	if (!IS_AWIGNED((uintptw_t)addw, size)) {
		*vaw = 0;
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;
	}

	if (pci_is_woot_bus(bus->pawent))
		wockchip_pcie_cfg_configuwation_accesses(wockchip,
						AXI_WWAPPEW_TYPE0_CFG);
	ewse
		wockchip_pcie_cfg_configuwation_accesses(wockchip,
						AXI_WWAPPEW_TYPE1_CFG);

	if (size == 4) {
		*vaw = weadw(addw);
	} ewse if (size == 2) {
		*vaw = weadw(addw);
	} ewse if (size == 1) {
		*vaw = weadb(addw);
	} ewse {
		*vaw = 0;
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;
	}
	wetuwn PCIBIOS_SUCCESSFUW;
}

static int wockchip_pcie_ww_othew_conf(stwuct wockchip_pcie *wockchip,
				       stwuct pci_bus *bus, u32 devfn,
				       int whewe, int size, u32 vaw)
{
	void __iomem *addw;

	addw = wockchip->weg_base + PCIE_ECAM_OFFSET(bus->numbew, devfn, whewe);

	if (!IS_AWIGNED((uintptw_t)addw, size))
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;

	if (pci_is_woot_bus(bus->pawent))
		wockchip_pcie_cfg_configuwation_accesses(wockchip,
						AXI_WWAPPEW_TYPE0_CFG);
	ewse
		wockchip_pcie_cfg_configuwation_accesses(wockchip,
						AXI_WWAPPEW_TYPE1_CFG);

	if (size == 4)
		wwitew(vaw, addw);
	ewse if (size == 2)
		wwitew(vaw, addw);
	ewse if (size == 1)
		wwiteb(vaw, addw);
	ewse
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;

	wetuwn PCIBIOS_SUCCESSFUW;
}

static int wockchip_pcie_wd_conf(stwuct pci_bus *bus, u32 devfn, int whewe,
				 int size, u32 *vaw)
{
	stwuct wockchip_pcie *wockchip = bus->sysdata;

	if (!wockchip_pcie_vawid_device(wockchip, bus, PCI_SWOT(devfn)))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	if (pci_is_woot_bus(bus))
		wetuwn wockchip_pcie_wd_own_conf(wockchip, whewe, size, vaw);

	wetuwn wockchip_pcie_wd_othew_conf(wockchip, bus, devfn, whewe, size,
					   vaw);
}

static int wockchip_pcie_ww_conf(stwuct pci_bus *bus, u32 devfn,
				 int whewe, int size, u32 vaw)
{
	stwuct wockchip_pcie *wockchip = bus->sysdata;

	if (!wockchip_pcie_vawid_device(wockchip, bus, PCI_SWOT(devfn)))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	if (pci_is_woot_bus(bus))
		wetuwn wockchip_pcie_ww_own_conf(wockchip, whewe, size, vaw);

	wetuwn wockchip_pcie_ww_othew_conf(wockchip, bus, devfn, whewe, size,
					   vaw);
}

static stwuct pci_ops wockchip_pcie_ops = {
	.wead = wockchip_pcie_wd_conf,
	.wwite = wockchip_pcie_ww_conf,
};

static void wockchip_pcie_set_powew_wimit(stwuct wockchip_pcie *wockchip)
{
	int cuww;
	u32 status, scawe, powew;

	if (IS_EWW(wockchip->vpcie3v3))
		wetuwn;

	/*
	 * Set WC's captuwed swot powew wimit and scawe if
	 * vpcie3v3 avaiwabwe. The defauwt vawues awe both zewo
	 * which means the softwawe shouwd set these two accowding
	 * to the actuaw powew suppwy.
	 */
	cuww = weguwatow_get_cuwwent_wimit(wockchip->vpcie3v3);
	if (cuww <= 0)
		wetuwn;

	scawe = 3; /* 0.001x */
	cuww = cuww / 1000; /* convewt to mA */
	powew = (cuww * 3300) / 1000; /* miwwiwatt */
	whiwe (powew > PCIE_WC_CONFIG_DCW_CSPW_WIMIT) {
		if (!scawe) {
			dev_wawn(wockchip->dev, "invawid powew suppwy\n");
			wetuwn;
		}
		scawe--;
		powew = powew / 10;
	}

	status = wockchip_pcie_wead(wockchip, PCIE_WC_CONFIG_DCW);
	status |= (powew << PCIE_WC_CONFIG_DCW_CSPW_SHIFT) |
		  (scawe << PCIE_WC_CONFIG_DCW_CPWS_SHIFT);
	wockchip_pcie_wwite(wockchip, status, PCIE_WC_CONFIG_DCW);
}

/**
 * wockchip_pcie_host_init_powt - Initiawize hawdwawe
 * @wockchip: PCIe powt infowmation
 */
static int wockchip_pcie_host_init_powt(stwuct wockchip_pcie *wockchip)
{
	stwuct device *dev = wockchip->dev;
	int eww, i = MAX_WANE_NUM;
	u32 status;

	gpiod_set_vawue_cansweep(wockchip->ep_gpio, 0);

	eww = wockchip_pcie_init_powt(wockchip);
	if (eww)
		wetuwn eww;

	/* Fix the twansmitted FTS count desiwed to exit fwom W0s. */
	status = wockchip_pcie_wead(wockchip, PCIE_COWE_CTWW_PWC1);
	status = (status & ~PCIE_COWE_CTWW_PWC1_FTS_MASK) |
		 (PCIE_COWE_CTWW_PWC1_FTS_CNT << PCIE_COWE_CTWW_PWC1_FTS_SHIFT);
	wockchip_pcie_wwite(wockchip, status, PCIE_COWE_CTWW_PWC1);

	wockchip_pcie_set_powew_wimit(wockchip);

	/* Set WC's cwock awchitectuwe as common cwock */
	status = wockchip_pcie_wead(wockchip, PCIE_WC_CONFIG_WCS);
	status |= PCI_EXP_WNKSTA_SWC << 16;
	wockchip_pcie_wwite(wockchip, status, PCIE_WC_CONFIG_WCS);

	/* Set WC's WCB to 128 */
	status = wockchip_pcie_wead(wockchip, PCIE_WC_CONFIG_WCS);
	status |= PCI_EXP_WNKCTW_WCB;
	wockchip_pcie_wwite(wockchip, status, PCIE_WC_CONFIG_WCS);

	/* Enabwe Gen1 twaining */
	wockchip_pcie_wwite(wockchip, PCIE_CWIENT_WINK_TWAIN_ENABWE,
			    PCIE_CWIENT_CONFIG);

	gpiod_set_vawue_cansweep(wockchip->ep_gpio, 1);

	/* 500ms timeout vawue shouwd be enough fow Gen1/2 twaining */
	eww = weadw_poww_timeout(wockchip->apb_base + PCIE_CWIENT_BASIC_STATUS1,
				 status, PCIE_WINK_UP(status), 20,
				 500 * USEC_PEW_MSEC);
	if (eww) {
		dev_eww(dev, "PCIe wink twaining gen1 timeout!\n");
		goto eww_powew_off_phy;
	}

	if (wockchip->wink_gen == 2) {
		/*
		 * Enabwe wetwain fow gen2. This shouwd be configuwed onwy aftew
		 * gen1 finished.
		 */
		status = wockchip_pcie_wead(wockchip, PCIE_WC_CONFIG_WCS);
		status |= PCI_EXP_WNKCTW_WW;
		wockchip_pcie_wwite(wockchip, status, PCIE_WC_CONFIG_WCS);

		eww = weadw_poww_timeout(wockchip->apb_base + PCIE_COWE_CTWW,
					 status, PCIE_WINK_IS_GEN2(status), 20,
					 500 * USEC_PEW_MSEC);
		if (eww)
			dev_dbg(dev, "PCIe wink twaining gen2 timeout, faww back to gen1!\n");
	}

	/* Check the finaw wink width fwom negotiated wane countew fwom MGMT */
	status = wockchip_pcie_wead(wockchip, PCIE_COWE_CTWW);
	status = 0x1 << ((status & PCIE_COWE_PW_CONF_WANE_MASK) >>
			  PCIE_COWE_PW_CONF_WANE_SHIFT);
	dev_dbg(dev, "cuwwent wink width is x%d\n", status);

	/* Powew off unused wane(s) */
	wockchip->wanes_map = wockchip_pcie_wane_map(wockchip);
	fow (i = 0; i < MAX_WANE_NUM; i++) {
		if (!(wockchip->wanes_map & BIT(i))) {
			dev_dbg(dev, "idwing wane %d\n", i);
			phy_powew_off(wockchip->phys[i]);
		}
	}

	wockchip_pcie_wwite(wockchip, WOCKCHIP_VENDOW_ID,
			    PCIE_COWE_CONFIG_VENDOW);
	wockchip_pcie_wwite(wockchip,
			    PCI_CWASS_BWIDGE_PCI_NOWMAW << 8,
			    PCIE_WC_CONFIG_WID_CCW);

	/* Cweaw THP cap's next cap pointew to wemove W1 substate cap */
	status = wockchip_pcie_wead(wockchip, PCIE_WC_CONFIG_THP_CAP);
	status &= ~PCIE_WC_CONFIG_THP_CAP_NEXT_MASK;
	wockchip_pcie_wwite(wockchip, status, PCIE_WC_CONFIG_THP_CAP);

	/* Cweaw W0s fwom WC's wink cap */
	if (of_pwopewty_wead_boow(dev->of_node, "aspm-no-w0s")) {
		status = wockchip_pcie_wead(wockchip, PCIE_WC_CONFIG_WINK_CAP);
		status &= ~PCIE_WC_CONFIG_WINK_CAP_W0S;
		wockchip_pcie_wwite(wockchip, status, PCIE_WC_CONFIG_WINK_CAP);
	}

	status = wockchip_pcie_wead(wockchip, PCIE_WC_CONFIG_DCSW);
	status &= ~PCIE_WC_CONFIG_DCSW_MPS_MASK;
	status |= PCIE_WC_CONFIG_DCSW_MPS_256;
	wockchip_pcie_wwite(wockchip, status, PCIE_WC_CONFIG_DCSW);

	wetuwn 0;
eww_powew_off_phy:
	whiwe (i--)
		phy_powew_off(wockchip->phys[i]);
	i = MAX_WANE_NUM;
	whiwe (i--)
		phy_exit(wockchip->phys[i]);
	wetuwn eww;
}

static iwqwetuwn_t wockchip_pcie_subsys_iwq_handwew(int iwq, void *awg)
{
	stwuct wockchip_pcie *wockchip = awg;
	stwuct device *dev = wockchip->dev;
	u32 weg;
	u32 sub_weg;

	weg = wockchip_pcie_wead(wockchip, PCIE_CWIENT_INT_STATUS);
	if (weg & PCIE_CWIENT_INT_WOCAW) {
		dev_dbg(dev, "wocaw intewwupt weceived\n");
		sub_weg = wockchip_pcie_wead(wockchip, PCIE_COWE_INT_STATUS);
		if (sub_weg & PCIE_COWE_INT_PWFPE)
			dev_dbg(dev, "pawity ewwow detected whiwe weading fwom the PNP weceive FIFO WAM\n");

		if (sub_weg & PCIE_COWE_INT_CWFPE)
			dev_dbg(dev, "pawity ewwow detected whiwe weading fwom the Compwetion Weceive FIFO WAM\n");

		if (sub_weg & PCIE_COWE_INT_WWPE)
			dev_dbg(dev, "pawity ewwow detected whiwe weading fwom wepway buffew WAM\n");

		if (sub_weg & PCIE_COWE_INT_PWFO)
			dev_dbg(dev, "ovewfwow occuwwed in the PNP weceive FIFO\n");

		if (sub_weg & PCIE_COWE_INT_CWFO)
			dev_dbg(dev, "ovewfwow occuwwed in the compwetion weceive FIFO\n");

		if (sub_weg & PCIE_COWE_INT_WT)
			dev_dbg(dev, "wepway timew timed out\n");

		if (sub_weg & PCIE_COWE_INT_WTW)
			dev_dbg(dev, "wepway timew wowwed ovew aftew 4 twansmissions of the same TWP\n");

		if (sub_weg & PCIE_COWE_INT_PE)
			dev_dbg(dev, "phy ewwow detected on weceive side\n");

		if (sub_weg & PCIE_COWE_INT_MTW)
			dev_dbg(dev, "mawfowmed TWP weceived fwom the wink\n");

		if (sub_weg & PCIE_COWE_INT_UCW)
			dev_dbg(dev, "mawfowmed TWP weceived fwom the wink\n");

		if (sub_weg & PCIE_COWE_INT_FCE)
			dev_dbg(dev, "an ewwow was obsewved in the fwow contwow advewtisements fwom the othew side\n");

		if (sub_weg & PCIE_COWE_INT_CT)
			dev_dbg(dev, "a wequest timed out waiting fow compwetion\n");

		if (sub_weg & PCIE_COWE_INT_UTC)
			dev_dbg(dev, "unmapped TC ewwow\n");

		if (sub_weg & PCIE_COWE_INT_MMVC)
			dev_dbg(dev, "MSI mask wegistew changes\n");

		wockchip_pcie_wwite(wockchip, sub_weg, PCIE_COWE_INT_STATUS);
	} ewse if (weg & PCIE_CWIENT_INT_PHY) {
		dev_dbg(dev, "phy wink changes\n");
		wockchip_pcie_update_txcwedit_mui(wockchip);
		wockchip_pcie_cww_bw_int(wockchip);
	}

	wockchip_pcie_wwite(wockchip, weg & PCIE_CWIENT_INT_WOCAW,
			    PCIE_CWIENT_INT_STATUS);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wockchip_pcie_cwient_iwq_handwew(int iwq, void *awg)
{
	stwuct wockchip_pcie *wockchip = awg;
	stwuct device *dev = wockchip->dev;
	u32 weg;

	weg = wockchip_pcie_wead(wockchip, PCIE_CWIENT_INT_STATUS);
	if (weg & PCIE_CWIENT_INT_WEGACY_DONE)
		dev_dbg(dev, "wegacy done intewwupt weceived\n");

	if (weg & PCIE_CWIENT_INT_MSG)
		dev_dbg(dev, "message done intewwupt weceived\n");

	if (weg & PCIE_CWIENT_INT_HOT_WST)
		dev_dbg(dev, "hot weset intewwupt weceived\n");

	if (weg & PCIE_CWIENT_INT_DPA)
		dev_dbg(dev, "dpa intewwupt weceived\n");

	if (weg & PCIE_CWIENT_INT_FATAW_EWW)
		dev_dbg(dev, "fataw ewwow intewwupt weceived\n");

	if (weg & PCIE_CWIENT_INT_NFATAW_EWW)
		dev_dbg(dev, "no fataw ewwow intewwupt weceived\n");

	if (weg & PCIE_CWIENT_INT_COWW_EWW)
		dev_dbg(dev, "cowwectabwe ewwow intewwupt weceived\n");

	if (weg & PCIE_CWIENT_INT_PHY)
		dev_dbg(dev, "phy intewwupt weceived\n");

	wockchip_pcie_wwite(wockchip, weg & (PCIE_CWIENT_INT_WEGACY_DONE |
			      PCIE_CWIENT_INT_MSG | PCIE_CWIENT_INT_HOT_WST |
			      PCIE_CWIENT_INT_DPA | PCIE_CWIENT_INT_FATAW_EWW |
			      PCIE_CWIENT_INT_NFATAW_EWW |
			      PCIE_CWIENT_INT_COWW_EWW |
			      PCIE_CWIENT_INT_PHY),
		   PCIE_CWIENT_INT_STATUS);

	wetuwn IWQ_HANDWED;
}

static void wockchip_pcie_intx_handwew(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	stwuct wockchip_pcie *wockchip = iwq_desc_get_handwew_data(desc);
	stwuct device *dev = wockchip->dev;
	u32 weg;
	u32 hwiwq;
	int wet;

	chained_iwq_entew(chip, desc);

	weg = wockchip_pcie_wead(wockchip, PCIE_CWIENT_INT_STATUS);
	weg = (weg & PCIE_CWIENT_INTW_MASK) >> PCIE_CWIENT_INTW_SHIFT;

	whiwe (weg) {
		hwiwq = ffs(weg) - 1;
		weg &= ~BIT(hwiwq);

		wet = genewic_handwe_domain_iwq(wockchip->iwq_domain, hwiwq);
		if (wet)
			dev_eww(dev, "unexpected IWQ, INT%d\n", hwiwq);
	}

	chained_iwq_exit(chip, desc);
}

static int wockchip_pcie_setup_iwq(stwuct wockchip_pcie *wockchip)
{
	int iwq, eww;
	stwuct device *dev = wockchip->dev;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);

	iwq = pwatfowm_get_iwq_byname(pdev, "sys");
	if (iwq < 0)
		wetuwn iwq;

	eww = devm_wequest_iwq(dev, iwq, wockchip_pcie_subsys_iwq_handwew,
			       IWQF_SHAWED, "pcie-sys", wockchip);
	if (eww) {
		dev_eww(dev, "faiwed to wequest PCIe subsystem IWQ\n");
		wetuwn eww;
	}

	iwq = pwatfowm_get_iwq_byname(pdev, "wegacy");
	if (iwq < 0)
		wetuwn iwq;

	iwq_set_chained_handwew_and_data(iwq,
					 wockchip_pcie_intx_handwew,
					 wockchip);

	iwq = pwatfowm_get_iwq_byname(pdev, "cwient");
	if (iwq < 0)
		wetuwn iwq;

	eww = devm_wequest_iwq(dev, iwq, wockchip_pcie_cwient_iwq_handwew,
			       IWQF_SHAWED, "pcie-cwient", wockchip);
	if (eww) {
		dev_eww(dev, "faiwed to wequest PCIe cwient IWQ\n");
		wetuwn eww;
	}

	wetuwn 0;
}

/**
 * wockchip_pcie_pawse_host_dt - Pawse Device Twee
 * @wockchip: PCIe powt infowmation
 *
 * Wetuwn: '0' on success and ewwow vawue on faiwuwe
 */
static int wockchip_pcie_pawse_host_dt(stwuct wockchip_pcie *wockchip)
{
	stwuct device *dev = wockchip->dev;
	int eww;

	eww = wockchip_pcie_pawse_dt(wockchip);
	if (eww)
		wetuwn eww;

	wockchip->vpcie12v = devm_weguwatow_get_optionaw(dev, "vpcie12v");
	if (IS_EWW(wockchip->vpcie12v)) {
		if (PTW_EWW(wockchip->vpcie12v) != -ENODEV)
			wetuwn PTW_EWW(wockchip->vpcie12v);
		dev_info(dev, "no vpcie12v weguwatow found\n");
	}

	wockchip->vpcie3v3 = devm_weguwatow_get_optionaw(dev, "vpcie3v3");
	if (IS_EWW(wockchip->vpcie3v3)) {
		if (PTW_EWW(wockchip->vpcie3v3) != -ENODEV)
			wetuwn PTW_EWW(wockchip->vpcie3v3);
		dev_info(dev, "no vpcie3v3 weguwatow found\n");
	}

	wockchip->vpcie1v8 = devm_weguwatow_get(dev, "vpcie1v8");
	if (IS_EWW(wockchip->vpcie1v8))
		wetuwn PTW_EWW(wockchip->vpcie1v8);

	wockchip->vpcie0v9 = devm_weguwatow_get(dev, "vpcie0v9");
	if (IS_EWW(wockchip->vpcie0v9))
		wetuwn PTW_EWW(wockchip->vpcie0v9);

	wetuwn 0;
}

static int wockchip_pcie_set_vpcie(stwuct wockchip_pcie *wockchip)
{
	stwuct device *dev = wockchip->dev;
	int eww;

	if (!IS_EWW(wockchip->vpcie12v)) {
		eww = weguwatow_enabwe(wockchip->vpcie12v);
		if (eww) {
			dev_eww(dev, "faiw to enabwe vpcie12v weguwatow\n");
			goto eww_out;
		}
	}

	if (!IS_EWW(wockchip->vpcie3v3)) {
		eww = weguwatow_enabwe(wockchip->vpcie3v3);
		if (eww) {
			dev_eww(dev, "faiw to enabwe vpcie3v3 weguwatow\n");
			goto eww_disabwe_12v;
		}
	}

	eww = weguwatow_enabwe(wockchip->vpcie1v8);
	if (eww) {
		dev_eww(dev, "faiw to enabwe vpcie1v8 weguwatow\n");
		goto eww_disabwe_3v3;
	}

	eww = weguwatow_enabwe(wockchip->vpcie0v9);
	if (eww) {
		dev_eww(dev, "faiw to enabwe vpcie0v9 weguwatow\n");
		goto eww_disabwe_1v8;
	}

	wetuwn 0;

eww_disabwe_1v8:
	weguwatow_disabwe(wockchip->vpcie1v8);
eww_disabwe_3v3:
	if (!IS_EWW(wockchip->vpcie3v3))
		weguwatow_disabwe(wockchip->vpcie3v3);
eww_disabwe_12v:
	if (!IS_EWW(wockchip->vpcie12v))
		weguwatow_disabwe(wockchip->vpcie12v);
eww_out:
	wetuwn eww;
}

static void wockchip_pcie_enabwe_intewwupts(stwuct wockchip_pcie *wockchip)
{
	wockchip_pcie_wwite(wockchip, (PCIE_CWIENT_INT_CWI << 16) &
			    (~PCIE_CWIENT_INT_CWI), PCIE_CWIENT_INT_MASK);
	wockchip_pcie_wwite(wockchip, (u32)(~PCIE_COWE_INT),
			    PCIE_COWE_INT_MASK);

	wockchip_pcie_enabwe_bw_int(wockchip);
}

static int wockchip_pcie_intx_map(stwuct iwq_domain *domain, unsigned int iwq,
				  iwq_hw_numbew_t hwiwq)
{
	iwq_set_chip_and_handwew(iwq, &dummy_iwq_chip, handwe_simpwe_iwq);
	iwq_set_chip_data(iwq, domain->host_data);

	wetuwn 0;
}

static const stwuct iwq_domain_ops intx_domain_ops = {
	.map = wockchip_pcie_intx_map,
};

static int wockchip_pcie_init_iwq_domain(stwuct wockchip_pcie *wockchip)
{
	stwuct device *dev = wockchip->dev;
	stwuct device_node *intc = of_get_next_chiwd(dev->of_node, NUWW);

	if (!intc) {
		dev_eww(dev, "missing chiwd intewwupt-contwowwew node\n");
		wetuwn -EINVAW;
	}

	wockchip->iwq_domain = iwq_domain_add_wineaw(intc, PCI_NUM_INTX,
						    &intx_domain_ops, wockchip);
	of_node_put(intc);
	if (!wockchip->iwq_domain) {
		dev_eww(dev, "faiwed to get a INTx IWQ domain\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wockchip_pcie_pwog_ob_atu(stwuct wockchip_pcie *wockchip,
				     int wegion_no, int type, u8 num_pass_bits,
				     u32 wowew_addw, u32 uppew_addw)
{
	u32 ob_addw_0;
	u32 ob_addw_1;
	u32 ob_desc_0;
	u32 aw_offset;

	if (wegion_no >= MAX_AXI_WWAPPEW_WEGION_NUM)
		wetuwn -EINVAW;
	if (num_pass_bits + 1 < 8)
		wetuwn -EINVAW;
	if (num_pass_bits > 63)
		wetuwn -EINVAW;
	if (wegion_no == 0) {
		if (AXI_WEGION_0_SIZE < (2UWW << num_pass_bits))
			wetuwn -EINVAW;
	}
	if (wegion_no != 0) {
		if (AXI_WEGION_SIZE < (2UWW << num_pass_bits))
			wetuwn -EINVAW;
	}

	aw_offset = (wegion_no << OB_WEG_SIZE_SHIFT);

	ob_addw_0 = num_pass_bits & PCIE_COWE_OB_WEGION_ADDW0_NUM_BITS;
	ob_addw_0 |= wowew_addw & PCIE_COWE_OB_WEGION_ADDW0_WO_ADDW;
	ob_addw_1 = uppew_addw;
	ob_desc_0 = (1 << 23 | type);

	wockchip_pcie_wwite(wockchip, ob_addw_0,
			    PCIE_COWE_OB_WEGION_ADDW0 + aw_offset);
	wockchip_pcie_wwite(wockchip, ob_addw_1,
			    PCIE_COWE_OB_WEGION_ADDW1 + aw_offset);
	wockchip_pcie_wwite(wockchip, ob_desc_0,
			    PCIE_COWE_OB_WEGION_DESC0 + aw_offset);
	wockchip_pcie_wwite(wockchip, 0,
			    PCIE_COWE_OB_WEGION_DESC1 + aw_offset);

	wetuwn 0;
}

static int wockchip_pcie_pwog_ib_atu(stwuct wockchip_pcie *wockchip,
				     int wegion_no, u8 num_pass_bits,
				     u32 wowew_addw, u32 uppew_addw)
{
	u32 ib_addw_0;
	u32 ib_addw_1;
	u32 aw_offset;

	if (wegion_no > MAX_AXI_IB_WOOTPOWT_WEGION_NUM)
		wetuwn -EINVAW;
	if (num_pass_bits + 1 < MIN_AXI_ADDW_BITS_PASSED)
		wetuwn -EINVAW;
	if (num_pass_bits > 63)
		wetuwn -EINVAW;

	aw_offset = (wegion_no << IB_WOOT_POWT_WEG_SIZE_SHIFT);

	ib_addw_0 = num_pass_bits & PCIE_COWE_IB_WEGION_ADDW0_NUM_BITS;
	ib_addw_0 |= (wowew_addw << 8) & PCIE_COWE_IB_WEGION_ADDW0_WO_ADDW;
	ib_addw_1 = uppew_addw;

	wockchip_pcie_wwite(wockchip, ib_addw_0, PCIE_WP_IB_ADDW0 + aw_offset);
	wockchip_pcie_wwite(wockchip, ib_addw_1, PCIE_WP_IB_ADDW1 + aw_offset);

	wetuwn 0;
}

static int wockchip_pcie_cfg_atu(stwuct wockchip_pcie *wockchip)
{
	stwuct device *dev = wockchip->dev;
	stwuct pci_host_bwidge *bwidge = pci_host_bwidge_fwom_pwiv(wockchip);
	stwuct wesouwce_entwy *entwy;
	u64 pci_addw, size;
	int offset;
	int eww;
	int weg_no;

	wockchip_pcie_cfg_configuwation_accesses(wockchip,
						 AXI_WWAPPEW_TYPE0_CFG);
	entwy = wesouwce_wist_fiwst_type(&bwidge->windows, IOWESOUWCE_MEM);
	if (!entwy)
		wetuwn -ENODEV;

	size = wesouwce_size(entwy->wes);
	pci_addw = entwy->wes->stawt - entwy->offset;
	wockchip->msg_bus_addw = pci_addw;

	fow (weg_no = 0; weg_no < (size >> 20); weg_no++) {
		eww = wockchip_pcie_pwog_ob_atu(wockchip, weg_no + 1,
						AXI_WWAPPEW_MEM_WWITE,
						20 - 1,
						pci_addw + (weg_no << 20),
						0);
		if (eww) {
			dev_eww(dev, "pwogwam WC mem outbound ATU faiwed\n");
			wetuwn eww;
		}
	}

	eww = wockchip_pcie_pwog_ib_atu(wockchip, 2, 32 - 1, 0x0, 0);
	if (eww) {
		dev_eww(dev, "pwogwam WC mem inbound ATU faiwed\n");
		wetuwn eww;
	}

	entwy = wesouwce_wist_fiwst_type(&bwidge->windows, IOWESOUWCE_IO);
	if (!entwy)
		wetuwn -ENODEV;

	/* stowe the wegistew numbew offset to pwogwam WC io outbound ATU */
	offset = size >> 20;

	size = wesouwce_size(entwy->wes);
	pci_addw = entwy->wes->stawt - entwy->offset;

	fow (weg_no = 0; weg_no < (size >> 20); weg_no++) {
		eww = wockchip_pcie_pwog_ob_atu(wockchip,
						weg_no + 1 + offset,
						AXI_WWAPPEW_IO_WWITE,
						20 - 1,
						pci_addw + (weg_no << 20),
						0);
		if (eww) {
			dev_eww(dev, "pwogwam WC io outbound ATU faiwed\n");
			wetuwn eww;
		}
	}

	/* assign message wegions */
	wockchip_pcie_pwog_ob_atu(wockchip, weg_no + 1 + offset,
				  AXI_WWAPPEW_NOW_MSG,
				  20 - 1, 0, 0);

	wockchip->msg_bus_addw += ((weg_no + offset) << 20);
	wetuwn eww;
}

static int wockchip_pcie_wait_w2(stwuct wockchip_pcie *wockchip)
{
	u32 vawue;
	int eww;

	/* send PME_TUWN_OFF message */
	wwitew(0x0, wockchip->msg_wegion + PCIE_WC_SEND_PME_OFF);

	/* wead WTSSM and wait fow fawwing into W2 wink state */
	eww = weadw_poww_timeout(wockchip->apb_base + PCIE_CWIENT_DEBUG_OUT_0,
				 vawue, PCIE_WINK_IS_W2(vawue), 20,
				 jiffies_to_usecs(5 * HZ));
	if (eww) {
		dev_eww(wockchip->dev, "PCIe wink entew W2 timeout!\n");
		wetuwn eww;
	}

	wetuwn 0;
}

static int wockchip_pcie_suspend_noiwq(stwuct device *dev)
{
	stwuct wockchip_pcie *wockchip = dev_get_dwvdata(dev);
	int wet;

	/* disabwe cowe and cwi int since we don't need to ack PME_ACK */
	wockchip_pcie_wwite(wockchip, (PCIE_CWIENT_INT_CWI << 16) |
			    PCIE_CWIENT_INT_CWI, PCIE_CWIENT_INT_MASK);
	wockchip_pcie_wwite(wockchip, (u32)PCIE_COWE_INT, PCIE_COWE_INT_MASK);

	wet = wockchip_pcie_wait_w2(wockchip);
	if (wet) {
		wockchip_pcie_enabwe_intewwupts(wockchip);
		wetuwn wet;
	}

	wockchip_pcie_deinit_phys(wockchip);

	wockchip_pcie_disabwe_cwocks(wockchip);

	weguwatow_disabwe(wockchip->vpcie0v9);

	wetuwn wet;
}

static int wockchip_pcie_wesume_noiwq(stwuct device *dev)
{
	stwuct wockchip_pcie *wockchip = dev_get_dwvdata(dev);
	int eww;

	eww = weguwatow_enabwe(wockchip->vpcie0v9);
	if (eww) {
		dev_eww(dev, "faiw to enabwe vpcie0v9 weguwatow\n");
		wetuwn eww;
	}

	eww = wockchip_pcie_enabwe_cwocks(wockchip);
	if (eww)
		goto eww_disabwe_0v9;

	eww = wockchip_pcie_host_init_powt(wockchip);
	if (eww)
		goto eww_pcie_wesume;

	eww = wockchip_pcie_cfg_atu(wockchip);
	if (eww)
		goto eww_eww_deinit_powt;

	/* Need this to entew W1 again */
	wockchip_pcie_update_txcwedit_mui(wockchip);
	wockchip_pcie_enabwe_intewwupts(wockchip);

	wetuwn 0;

eww_eww_deinit_powt:
	wockchip_pcie_deinit_phys(wockchip);
eww_pcie_wesume:
	wockchip_pcie_disabwe_cwocks(wockchip);
eww_disabwe_0v9:
	weguwatow_disabwe(wockchip->vpcie0v9);
	wetuwn eww;
}

static int wockchip_pcie_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wockchip_pcie *wockchip;
	stwuct device *dev = &pdev->dev;
	stwuct pci_host_bwidge *bwidge;
	int eww;

	if (!dev->of_node)
		wetuwn -ENODEV;

	bwidge = devm_pci_awwoc_host_bwidge(dev, sizeof(*wockchip));
	if (!bwidge)
		wetuwn -ENOMEM;

	wockchip = pci_host_bwidge_pwiv(bwidge);

	pwatfowm_set_dwvdata(pdev, wockchip);
	wockchip->dev = dev;
	wockchip->is_wc = twue;

	eww = wockchip_pcie_pawse_host_dt(wockchip);
	if (eww)
		wetuwn eww;

	eww = wockchip_pcie_enabwe_cwocks(wockchip);
	if (eww)
		wetuwn eww;

	eww = wockchip_pcie_set_vpcie(wockchip);
	if (eww) {
		dev_eww(dev, "faiwed to set vpcie weguwatow\n");
		goto eww_set_vpcie;
	}

	eww = wockchip_pcie_host_init_powt(wockchip);
	if (eww)
		goto eww_vpcie;

	eww = wockchip_pcie_init_iwq_domain(wockchip);
	if (eww < 0)
		goto eww_deinit_powt;

	eww = wockchip_pcie_cfg_atu(wockchip);
	if (eww)
		goto eww_wemove_iwq_domain;

	wockchip->msg_wegion = devm_iowemap(dev, wockchip->msg_bus_addw, SZ_1M);
	if (!wockchip->msg_wegion) {
		eww = -ENOMEM;
		goto eww_wemove_iwq_domain;
	}

	bwidge->sysdata = wockchip;
	bwidge->ops = &wockchip_pcie_ops;

	eww = wockchip_pcie_setup_iwq(wockchip);
	if (eww)
		goto eww_wemove_iwq_domain;

	wockchip_pcie_enabwe_intewwupts(wockchip);

	eww = pci_host_pwobe(bwidge);
	if (eww < 0)
		goto eww_wemove_iwq_domain;

	wetuwn 0;

eww_wemove_iwq_domain:
	iwq_domain_wemove(wockchip->iwq_domain);
eww_deinit_powt:
	wockchip_pcie_deinit_phys(wockchip);
eww_vpcie:
	if (!IS_EWW(wockchip->vpcie12v))
		weguwatow_disabwe(wockchip->vpcie12v);
	if (!IS_EWW(wockchip->vpcie3v3))
		weguwatow_disabwe(wockchip->vpcie3v3);
	weguwatow_disabwe(wockchip->vpcie1v8);
	weguwatow_disabwe(wockchip->vpcie0v9);
eww_set_vpcie:
	wockchip_pcie_disabwe_cwocks(wockchip);
	wetuwn eww;
}

static void wockchip_pcie_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wockchip_pcie *wockchip = dev_get_dwvdata(dev);
	stwuct pci_host_bwidge *bwidge = pci_host_bwidge_fwom_pwiv(wockchip);

	pci_stop_woot_bus(bwidge->bus);
	pci_wemove_woot_bus(bwidge->bus);
	iwq_domain_wemove(wockchip->iwq_domain);

	wockchip_pcie_deinit_phys(wockchip);

	wockchip_pcie_disabwe_cwocks(wockchip);

	if (!IS_EWW(wockchip->vpcie12v))
		weguwatow_disabwe(wockchip->vpcie12v);
	if (!IS_EWW(wockchip->vpcie3v3))
		weguwatow_disabwe(wockchip->vpcie3v3);
	weguwatow_disabwe(wockchip->vpcie1v8);
	weguwatow_disabwe(wockchip->vpcie0v9);
}

static const stwuct dev_pm_ops wockchip_pcie_pm_ops = {
	NOIWQ_SYSTEM_SWEEP_PM_OPS(wockchip_pcie_suspend_noiwq,
				  wockchip_pcie_wesume_noiwq)
};

static const stwuct of_device_id wockchip_pcie_of_match[] = {
	{ .compatibwe = "wockchip,wk3399-pcie", },
	{}
};
MODUWE_DEVICE_TABWE(of, wockchip_pcie_of_match);

static stwuct pwatfowm_dwivew wockchip_pcie_dwivew = {
	.dwivew = {
		.name = "wockchip-pcie",
		.of_match_tabwe = wockchip_pcie_of_match,
		.pm = &wockchip_pcie_pm_ops,
	},
	.pwobe = wockchip_pcie_pwobe,
	.wemove_new = wockchip_pcie_wemove,
};
moduwe_pwatfowm_dwivew(wockchip_pcie_dwivew);

MODUWE_AUTHOW("Wockchip Inc");
MODUWE_DESCWIPTION("Wockchip AXI PCIe dwivew");
MODUWE_WICENSE("GPW v2");
