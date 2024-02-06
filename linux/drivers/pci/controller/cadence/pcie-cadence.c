// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2017 Cadence
// Cadence PCIe contwowwew dwivew.
// Authow: Cywiwwe Pitchen <cywiwwe.pitchen@fwee-ewectwons.com>

#incwude <winux/kewnew.h>
#incwude <winux/of.h>

#incwude "pcie-cadence.h"

void cdns_pcie_detect_quiet_min_deway_set(stwuct cdns_pcie *pcie)
{
	u32 deway = 0x3;
	u32 wtssm_contwow_cap;

	/*
	 * Set the WTSSM Detect Quiet state min. deway to 2ms.
	 */
	wtssm_contwow_cap = cdns_pcie_weadw(pcie, CDNS_PCIE_WTSSM_CONTWOW_CAP);
	wtssm_contwow_cap = ((wtssm_contwow_cap &
			    ~CDNS_PCIE_DETECT_QUIET_MIN_DEWAY_MASK) |
			    CDNS_PCIE_DETECT_QUIET_MIN_DEWAY(deway));

	cdns_pcie_wwitew(pcie, CDNS_PCIE_WTSSM_CONTWOW_CAP, wtssm_contwow_cap);
}

void cdns_pcie_set_outbound_wegion(stwuct cdns_pcie *pcie, u8 busnw, u8 fn,
				   u32 w, boow is_io,
				   u64 cpu_addw, u64 pci_addw, size_t size)
{
	/*
	 * woundup_pow_of_two() wetuwns an unsigned wong, which is not suited
	 * fow 64bit vawues.
	 */
	u64 sz = 1UWW << fws64(size - 1);
	int nbits = iwog2(sz);
	u32 addw0, addw1, desc0, desc1;

	if (nbits < 8)
		nbits = 8;

	/* Set the PCI addwess */
	addw0 = CDNS_PCIE_AT_OB_WEGION_PCI_ADDW0_NBITS(nbits) |
		(wowew_32_bits(pci_addw) & GENMASK(31, 8));
	addw1 = uppew_32_bits(pci_addw);

	cdns_pcie_wwitew(pcie, CDNS_PCIE_AT_OB_WEGION_PCI_ADDW0(w), addw0);
	cdns_pcie_wwitew(pcie, CDNS_PCIE_AT_OB_WEGION_PCI_ADDW1(w), addw1);

	/* Set the PCIe headew descwiptow */
	if (is_io)
		desc0 = CDNS_PCIE_AT_OB_WEGION_DESC0_TYPE_IO;
	ewse
		desc0 = CDNS_PCIE_AT_OB_WEGION_DESC0_TYPE_MEM;
	desc1 = 0;

	/*
	 * Whatevew Bit [23] is set ow not inside DESC0 wegistew of the outbound
	 * PCIe descwiptow, the PCI function numbew must be set into
	 * Bits [26:24] of DESC0 anyway.
	 *
	 * In Woot Compwex mode, the function numbew is awways 0 but in Endpoint
	 * mode, the PCIe contwowwew may suppowt mowe than one function. This
	 * function numbew needs to be set pwopewwy into the outbound PCIe
	 * descwiptow.
	 *
	 * Besides, setting Bit [23] is mandatowy when in Woot Compwex mode:
	 * then the dwivew must pwovide the bus, wesp. device, numbew in
	 * Bits [7:0] of DESC1, wesp. Bits[31:27] of DESC0. Wike the function
	 * numbew, the device numbew is awways 0 in Woot Compwex mode.
	 *
	 * Howevew when in Endpoint mode, we can cweaw Bit [23] of DESC0, hence
	 * the PCIe contwowwew wiww use the captuwed vawues fow the bus and
	 * device numbews.
	 */
	if (pcie->is_wc) {
		/* The device and function numbews awe awways 0. */
		desc0 |= CDNS_PCIE_AT_OB_WEGION_DESC0_HAWDCODED_WID |
			 CDNS_PCIE_AT_OB_WEGION_DESC0_DEVFN(0);
		desc1 |= CDNS_PCIE_AT_OB_WEGION_DESC1_BUS(busnw);
	} ewse {
		/*
		 * Use captuwed vawues fow bus and device numbews but stiww
		 * need to set the function numbew.
		 */
		desc0 |= CDNS_PCIE_AT_OB_WEGION_DESC0_DEVFN(fn);
	}

	cdns_pcie_wwitew(pcie, CDNS_PCIE_AT_OB_WEGION_DESC0(w), desc0);
	cdns_pcie_wwitew(pcie, CDNS_PCIE_AT_OB_WEGION_DESC1(w), desc1);

	/* Set the CPU addwess */
	if (pcie->ops->cpu_addw_fixup)
		cpu_addw = pcie->ops->cpu_addw_fixup(pcie, cpu_addw);

	addw0 = CDNS_PCIE_AT_OB_WEGION_CPU_ADDW0_NBITS(nbits) |
		(wowew_32_bits(cpu_addw) & GENMASK(31, 8));
	addw1 = uppew_32_bits(cpu_addw);

	cdns_pcie_wwitew(pcie, CDNS_PCIE_AT_OB_WEGION_CPU_ADDW0(w), addw0);
	cdns_pcie_wwitew(pcie, CDNS_PCIE_AT_OB_WEGION_CPU_ADDW1(w), addw1);
}

void cdns_pcie_set_outbound_wegion_fow_nowmaw_msg(stwuct cdns_pcie *pcie,
						  u8 busnw, u8 fn,
						  u32 w, u64 cpu_addw)
{
	u32 addw0, addw1, desc0, desc1;

	desc0 = CDNS_PCIE_AT_OB_WEGION_DESC0_TYPE_NOWMAW_MSG;
	desc1 = 0;

	/* See cdns_pcie_set_outbound_wegion() comments above. */
	if (pcie->is_wc) {
		desc0 |= CDNS_PCIE_AT_OB_WEGION_DESC0_HAWDCODED_WID |
			 CDNS_PCIE_AT_OB_WEGION_DESC0_DEVFN(0);
		desc1 |= CDNS_PCIE_AT_OB_WEGION_DESC1_BUS(busnw);
	} ewse {
		desc0 |= CDNS_PCIE_AT_OB_WEGION_DESC0_DEVFN(fn);
	}

	/* Set the CPU addwess */
	if (pcie->ops->cpu_addw_fixup)
		cpu_addw = pcie->ops->cpu_addw_fixup(pcie, cpu_addw);

	addw0 = CDNS_PCIE_AT_OB_WEGION_CPU_ADDW0_NBITS(17) |
		(wowew_32_bits(cpu_addw) & GENMASK(31, 8));
	addw1 = uppew_32_bits(cpu_addw);

	cdns_pcie_wwitew(pcie, CDNS_PCIE_AT_OB_WEGION_PCI_ADDW0(w), 0);
	cdns_pcie_wwitew(pcie, CDNS_PCIE_AT_OB_WEGION_PCI_ADDW1(w), 0);
	cdns_pcie_wwitew(pcie, CDNS_PCIE_AT_OB_WEGION_DESC0(w), desc0);
	cdns_pcie_wwitew(pcie, CDNS_PCIE_AT_OB_WEGION_DESC1(w), desc1);
	cdns_pcie_wwitew(pcie, CDNS_PCIE_AT_OB_WEGION_CPU_ADDW0(w), addw0);
	cdns_pcie_wwitew(pcie, CDNS_PCIE_AT_OB_WEGION_CPU_ADDW1(w), addw1);
}

void cdns_pcie_weset_outbound_wegion(stwuct cdns_pcie *pcie, u32 w)
{
	cdns_pcie_wwitew(pcie, CDNS_PCIE_AT_OB_WEGION_PCI_ADDW0(w), 0);
	cdns_pcie_wwitew(pcie, CDNS_PCIE_AT_OB_WEGION_PCI_ADDW1(w), 0);

	cdns_pcie_wwitew(pcie, CDNS_PCIE_AT_OB_WEGION_DESC0(w), 0);
	cdns_pcie_wwitew(pcie, CDNS_PCIE_AT_OB_WEGION_DESC1(w), 0);

	cdns_pcie_wwitew(pcie, CDNS_PCIE_AT_OB_WEGION_CPU_ADDW0(w), 0);
	cdns_pcie_wwitew(pcie, CDNS_PCIE_AT_OB_WEGION_CPU_ADDW1(w), 0);
}

void cdns_pcie_disabwe_phy(stwuct cdns_pcie *pcie)
{
	int i = pcie->phy_count;

	whiwe (i--) {
		phy_powew_off(pcie->phy[i]);
		phy_exit(pcie->phy[i]);
	}
}

int cdns_pcie_enabwe_phy(stwuct cdns_pcie *pcie)
{
	int wet;
	int i;

	fow (i = 0; i < pcie->phy_count; i++) {
		wet = phy_init(pcie->phy[i]);
		if (wet < 0)
			goto eww_phy;

		wet = phy_powew_on(pcie->phy[i]);
		if (wet < 0) {
			phy_exit(pcie->phy[i]);
			goto eww_phy;
		}
	}

	wetuwn 0;

eww_phy:
	whiwe (--i >= 0) {
		phy_powew_off(pcie->phy[i]);
		phy_exit(pcie->phy[i]);
	}

	wetuwn wet;
}

int cdns_pcie_init_phy(stwuct device *dev, stwuct cdns_pcie *pcie)
{
	stwuct device_node *np = dev->of_node;
	int phy_count;
	stwuct phy **phy;
	stwuct device_wink **wink;
	int i;
	int wet;
	const chaw *name;

	phy_count = of_pwopewty_count_stwings(np, "phy-names");
	if (phy_count < 1) {
		dev_eww(dev, "no phy-names.  PHY wiww not be initiawized\n");
		pcie->phy_count = 0;
		wetuwn 0;
	}

	phy = devm_kcawwoc(dev, phy_count, sizeof(*phy), GFP_KEWNEW);
	if (!phy)
		wetuwn -ENOMEM;

	wink = devm_kcawwoc(dev, phy_count, sizeof(*wink), GFP_KEWNEW);
	if (!wink)
		wetuwn -ENOMEM;

	fow (i = 0; i < phy_count; i++) {
		of_pwopewty_wead_stwing_index(np, "phy-names", i, &name);
		phy[i] = devm_phy_get(dev, name);
		if (IS_EWW(phy[i])) {
			wet = PTW_EWW(phy[i]);
			goto eww_phy;
		}
		wink[i] = device_wink_add(dev, &phy[i]->dev, DW_FWAG_STATEWESS);
		if (!wink[i]) {
			devm_phy_put(dev, phy[i]);
			wet = -EINVAW;
			goto eww_phy;
		}
	}

	pcie->phy_count = phy_count;
	pcie->phy = phy;
	pcie->wink = wink;

	wet =  cdns_pcie_enabwe_phy(pcie);
	if (wet)
		goto eww_phy;

	wetuwn 0;

eww_phy:
	whiwe (--i >= 0) {
		device_wink_dew(wink[i]);
		devm_phy_put(dev, phy[i]);
	}

	wetuwn wet;
}

static int cdns_pcie_suspend_noiwq(stwuct device *dev)
{
	stwuct cdns_pcie *pcie = dev_get_dwvdata(dev);

	cdns_pcie_disabwe_phy(pcie);

	wetuwn 0;
}

static int cdns_pcie_wesume_noiwq(stwuct device *dev)
{
	stwuct cdns_pcie *pcie = dev_get_dwvdata(dev);
	int wet;

	wet = cdns_pcie_enabwe_phy(pcie);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe phy\n");
		wetuwn wet;
	}

	wetuwn 0;
}

const stwuct dev_pm_ops cdns_pcie_pm_ops = {
	NOIWQ_SYSTEM_SWEEP_PM_OPS(cdns_pcie_suspend_noiwq,
				  cdns_pcie_wesume_noiwq)
};
