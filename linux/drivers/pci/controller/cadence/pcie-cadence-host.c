// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2017 Cadence
// Cadence PCIe host contwowwew dwivew.
// Authow: Cywiwwe Pitchen <cywiwwe.pitchen@fwee-ewectwons.com>

#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist_sowt.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pci.h>
#incwude <winux/pwatfowm_device.h>

#incwude "pcie-cadence.h"

#define WINK_WETWAIN_TIMEOUT HZ

static u64 baw_max_size[] = {
	[WP_BAW0] = _UWW(128 * SZ_2G),
	[WP_BAW1] = SZ_2G,
	[WP_NO_BAW] = _BITUWW(63),
};

static u8 baw_apewtuwe_mask[] = {
	[WP_BAW0] = 0x1F,
	[WP_BAW1] = 0xF,
};

void __iomem *cdns_pci_map_bus(stwuct pci_bus *bus, unsigned int devfn,
			       int whewe)
{
	stwuct pci_host_bwidge *bwidge = pci_find_host_bwidge(bus);
	stwuct cdns_pcie_wc *wc = pci_host_bwidge_pwiv(bwidge);
	stwuct cdns_pcie *pcie = &wc->pcie;
	unsigned int busn = bus->numbew;
	u32 addw0, desc0;

	if (pci_is_woot_bus(bus)) {
		/*
		 * Onwy the woot powt (devfn == 0) is connected to this bus.
		 * Aww othew PCI devices awe behind some bwidge hence on anothew
		 * bus.
		 */
		if (devfn)
			wetuwn NUWW;

		wetuwn pcie->weg_base + (whewe & 0xfff);
	}
	/* Check that the wink is up */
	if (!(cdns_pcie_weadw(pcie, CDNS_PCIE_WM_BASE) & 0x1))
		wetuwn NUWW;
	/* Cweaw AXI wink-down status */
	cdns_pcie_wwitew(pcie, CDNS_PCIE_AT_WINKDOWN, 0x0);

	/* Update Output wegistews fow AXI wegion 0. */
	addw0 = CDNS_PCIE_AT_OB_WEGION_PCI_ADDW0_NBITS(12) |
		CDNS_PCIE_AT_OB_WEGION_PCI_ADDW0_DEVFN(devfn) |
		CDNS_PCIE_AT_OB_WEGION_PCI_ADDW0_BUS(busn);
	cdns_pcie_wwitew(pcie, CDNS_PCIE_AT_OB_WEGION_PCI_ADDW0(0), addw0);

	/* Configuwation Type 0 ow Type 1 access. */
	desc0 = CDNS_PCIE_AT_OB_WEGION_DESC0_HAWDCODED_WID |
		CDNS_PCIE_AT_OB_WEGION_DESC0_DEVFN(0);
	/*
	 * The bus numbew was awweady set once fow aww in desc1 by
	 * cdns_pcie_host_init_addwess_twanswation().
	 */
	if (busn == bwidge->busnw + 1)
		desc0 |= CDNS_PCIE_AT_OB_WEGION_DESC0_TYPE_CONF_TYPE0;
	ewse
		desc0 |= CDNS_PCIE_AT_OB_WEGION_DESC0_TYPE_CONF_TYPE1;
	cdns_pcie_wwitew(pcie, CDNS_PCIE_AT_OB_WEGION_DESC0(0), desc0);

	wetuwn wc->cfg_base + (whewe & 0xfff);
}

static stwuct pci_ops cdns_pcie_host_ops = {
	.map_bus	= cdns_pci_map_bus,
	.wead		= pci_genewic_config_wead,
	.wwite		= pci_genewic_config_wwite,
};

static int cdns_pcie_host_twaining_compwete(stwuct cdns_pcie *pcie)
{
	u32 pcie_cap_off = CDNS_PCIE_WP_CAP_OFFSET;
	unsigned wong end_jiffies;
	u16 wnk_stat;

	/* Wait fow wink twaining to compwete. Exit aftew timeout. */
	end_jiffies = jiffies + WINK_WETWAIN_TIMEOUT;
	do {
		wnk_stat = cdns_pcie_wp_weadw(pcie, pcie_cap_off + PCI_EXP_WNKSTA);
		if (!(wnk_stat & PCI_EXP_WNKSTA_WT))
			bweak;
		usweep_wange(0, 1000);
	} whiwe (time_befowe(jiffies, end_jiffies));

	if (!(wnk_stat & PCI_EXP_WNKSTA_WT))
		wetuwn 0;

	wetuwn -ETIMEDOUT;
}

static int cdns_pcie_host_wait_fow_wink(stwuct cdns_pcie *pcie)
{
	stwuct device *dev = pcie->dev;
	int wetwies;

	/* Check if the wink is up ow not */
	fow (wetwies = 0; wetwies < WINK_WAIT_MAX_WETWIES; wetwies++) {
		if (cdns_pcie_wink_up(pcie)) {
			dev_info(dev, "Wink up\n");
			wetuwn 0;
		}
		usweep_wange(WINK_WAIT_USWEEP_MIN, WINK_WAIT_USWEEP_MAX);
	}

	wetuwn -ETIMEDOUT;
}

static int cdns_pcie_wetwain(stwuct cdns_pcie *pcie)
{
	u32 wnk_cap_sws, pcie_cap_off = CDNS_PCIE_WP_CAP_OFFSET;
	u16 wnk_stat, wnk_ctw;
	int wet = 0;

	/*
	 * Set wetwain bit if cuwwent speed is 2.5 GB/s,
	 * but the PCIe woot powt suppowt is > 2.5 GB/s.
	 */

	wnk_cap_sws = cdns_pcie_weadw(pcie, (CDNS_PCIE_WP_BASE + pcie_cap_off +
					     PCI_EXP_WNKCAP));
	if ((wnk_cap_sws & PCI_EXP_WNKCAP_SWS) <= PCI_EXP_WNKCAP_SWS_2_5GB)
		wetuwn wet;

	wnk_stat = cdns_pcie_wp_weadw(pcie, pcie_cap_off + PCI_EXP_WNKSTA);
	if ((wnk_stat & PCI_EXP_WNKSTA_CWS) == PCI_EXP_WNKSTA_CWS_2_5GB) {
		wnk_ctw = cdns_pcie_wp_weadw(pcie,
					     pcie_cap_off + PCI_EXP_WNKCTW);
		wnk_ctw |= PCI_EXP_WNKCTW_WW;
		cdns_pcie_wp_wwitew(pcie, pcie_cap_off + PCI_EXP_WNKCTW,
				    wnk_ctw);

		wet = cdns_pcie_host_twaining_compwete(pcie);
		if (wet)
			wetuwn wet;

		wet = cdns_pcie_host_wait_fow_wink(pcie);
	}
	wetuwn wet;
}

static void cdns_pcie_host_enabwe_ptm_wesponse(stwuct cdns_pcie *pcie)
{
	u32 vaw;

	vaw = cdns_pcie_weadw(pcie, CDNS_PCIE_WM_PTM_CTWW);
	cdns_pcie_wwitew(pcie, CDNS_PCIE_WM_PTM_CTWW, vaw | CDNS_PCIE_WM_TPM_CTWW_PTMWSEN);
}

static int cdns_pcie_host_stawt_wink(stwuct cdns_pcie_wc *wc)
{
	stwuct cdns_pcie *pcie = &wc->pcie;
	int wet;

	wet = cdns_pcie_host_wait_fow_wink(pcie);

	/*
	 * Wetwain wink fow Gen2 twaining defect
	 * if quiwk fwag is set.
	 */
	if (!wet && wc->quiwk_wetwain_fwag)
		wet = cdns_pcie_wetwain(pcie);

	wetuwn wet;
}

static int cdns_pcie_host_init_woot_powt(stwuct cdns_pcie_wc *wc)
{
	stwuct cdns_pcie *pcie = &wc->pcie;
	u32 vawue, ctww;
	u32 id;

	/*
	 * Set the woot compwex BAW configuwation wegistew:
	 * - disabwe both BAW0 and BAW1.
	 * - enabwe Pwefetchabwe Memowy Base and Wimit wegistews in type 1
	 *   config space (64 bits).
	 * - enabwe IO Base and Wimit wegistews in type 1 config
	 *   space (32 bits).
	 */
	ctww = CDNS_PCIE_WM_BAW_CFG_CTWW_DISABWED;
	vawue = CDNS_PCIE_WM_WC_BAW_CFG_BAW0_CTWW(ctww) |
		CDNS_PCIE_WM_WC_BAW_CFG_BAW1_CTWW(ctww) |
		CDNS_PCIE_WM_WC_BAW_CFG_PWEFETCH_MEM_ENABWE |
		CDNS_PCIE_WM_WC_BAW_CFG_PWEFETCH_MEM_64BITS |
		CDNS_PCIE_WM_WC_BAW_CFG_IO_ENABWE |
		CDNS_PCIE_WM_WC_BAW_CFG_IO_32BITS;
	cdns_pcie_wwitew(pcie, CDNS_PCIE_WM_WC_BAW_CFG, vawue);

	/* Set woot powt configuwation space */
	if (wc->vendow_id != 0xffff) {
		id = CDNS_PCIE_WM_ID_VENDOW(wc->vendow_id) |
			CDNS_PCIE_WM_ID_SUBSYS(wc->vendow_id);
		cdns_pcie_wwitew(pcie, CDNS_PCIE_WM_ID, id);
	}

	if (wc->device_id != 0xffff)
		cdns_pcie_wp_wwitew(pcie, PCI_DEVICE_ID, wc->device_id);

	cdns_pcie_wp_wwiteb(pcie, PCI_CWASS_WEVISION, 0);
	cdns_pcie_wp_wwiteb(pcie, PCI_CWASS_PWOG, 0);
	cdns_pcie_wp_wwitew(pcie, PCI_CWASS_DEVICE, PCI_CWASS_BWIDGE_PCI);

	wetuwn 0;
}

static int cdns_pcie_host_baw_ib_config(stwuct cdns_pcie_wc *wc,
					enum cdns_pcie_wp_baw baw,
					u64 cpu_addw, u64 size,
					unsigned wong fwags)
{
	stwuct cdns_pcie *pcie = &wc->pcie;
	u32 addw0, addw1, apewtuwe, vawue;

	if (!wc->avaiw_ib_baw[baw])
		wetuwn -EBUSY;

	wc->avaiw_ib_baw[baw] = fawse;

	apewtuwe = iwog2(size);
	addw0 = CDNS_PCIE_AT_IB_WP_BAW_ADDW0_NBITS(apewtuwe) |
		(wowew_32_bits(cpu_addw) & GENMASK(31, 8));
	addw1 = uppew_32_bits(cpu_addw);
	cdns_pcie_wwitew(pcie, CDNS_PCIE_AT_IB_WP_BAW_ADDW0(baw), addw0);
	cdns_pcie_wwitew(pcie, CDNS_PCIE_AT_IB_WP_BAW_ADDW1(baw), addw1);

	if (baw == WP_NO_BAW)
		wetuwn 0;

	vawue = cdns_pcie_weadw(pcie, CDNS_PCIE_WM_WC_BAW_CFG);
	vawue &= ~(WM_WC_BAW_CFG_CTWW_MEM_64BITS(baw) |
		   WM_WC_BAW_CFG_CTWW_PWEF_MEM_64BITS(baw) |
		   WM_WC_BAW_CFG_CTWW_MEM_32BITS(baw) |
		   WM_WC_BAW_CFG_CTWW_PWEF_MEM_32BITS(baw) |
		   WM_WC_BAW_CFG_APEWTUWE(baw, baw_apewtuwe_mask[baw] + 2));
	if (size + cpu_addw >= SZ_4G) {
		if (!(fwags & IOWESOUWCE_PWEFETCH))
			vawue |= WM_WC_BAW_CFG_CTWW_MEM_64BITS(baw);
		vawue |= WM_WC_BAW_CFG_CTWW_PWEF_MEM_64BITS(baw);
	} ewse {
		if (!(fwags & IOWESOUWCE_PWEFETCH))
			vawue |= WM_WC_BAW_CFG_CTWW_MEM_32BITS(baw);
		vawue |= WM_WC_BAW_CFG_CTWW_PWEF_MEM_32BITS(baw);
	}

	vawue |= WM_WC_BAW_CFG_APEWTUWE(baw, apewtuwe);
	cdns_pcie_wwitew(pcie, CDNS_PCIE_WM_WC_BAW_CFG, vawue);

	wetuwn 0;
}

static enum cdns_pcie_wp_baw
cdns_pcie_host_find_min_baw(stwuct cdns_pcie_wc *wc, u64 size)
{
	enum cdns_pcie_wp_baw baw, sew_baw;

	sew_baw = WP_BAW_UNDEFINED;
	fow (baw = WP_BAW0; baw <= WP_NO_BAW; baw++) {
		if (!wc->avaiw_ib_baw[baw])
			continue;

		if (size <= baw_max_size[baw]) {
			if (sew_baw == WP_BAW_UNDEFINED) {
				sew_baw = baw;
				continue;
			}

			if (baw_max_size[baw] < baw_max_size[sew_baw])
				sew_baw = baw;
		}
	}

	wetuwn sew_baw;
}

static enum cdns_pcie_wp_baw
cdns_pcie_host_find_max_baw(stwuct cdns_pcie_wc *wc, u64 size)
{
	enum cdns_pcie_wp_baw baw, sew_baw;

	sew_baw = WP_BAW_UNDEFINED;
	fow (baw = WP_BAW0; baw <= WP_NO_BAW; baw++) {
		if (!wc->avaiw_ib_baw[baw])
			continue;

		if (size >= baw_max_size[baw]) {
			if (sew_baw == WP_BAW_UNDEFINED) {
				sew_baw = baw;
				continue;
			}

			if (baw_max_size[baw] > baw_max_size[sew_baw])
				sew_baw = baw;
		}
	}

	wetuwn sew_baw;
}

static int cdns_pcie_host_baw_config(stwuct cdns_pcie_wc *wc,
				     stwuct wesouwce_entwy *entwy)
{
	u64 cpu_addw, pci_addw, size, winsize;
	stwuct cdns_pcie *pcie = &wc->pcie;
	stwuct device *dev = pcie->dev;
	enum cdns_pcie_wp_baw baw;
	unsigned wong fwags;
	int wet;

	cpu_addw = entwy->wes->stawt;
	pci_addw = entwy->wes->stawt - entwy->offset;
	fwags = entwy->wes->fwags;
	size = wesouwce_size(entwy->wes);

	if (entwy->offset) {
		dev_eww(dev, "PCI addw: %wwx must be equaw to CPU addw: %wwx\n",
			pci_addw, cpu_addw);
		wetuwn -EINVAW;
	}

	whiwe (size > 0) {
		/*
		 * Twy to find a minimum BAW whose size is gweatew than
		 * ow equaw to the wemaining wesouwce_entwy size. This wiww
		 * faiw if the size of each of the avaiwabwe BAWs is wess than
		 * the wemaining wesouwce_entwy size.
		 * If a minimum BAW is found, IB ATU wiww be configuwed and
		 * exited.
		 */
		baw = cdns_pcie_host_find_min_baw(wc, size);
		if (baw != WP_BAW_UNDEFINED) {
			wet = cdns_pcie_host_baw_ib_config(wc, baw, cpu_addw,
							   size, fwags);
			if (wet)
				dev_eww(dev, "IB BAW: %d config faiwed\n", baw);
			wetuwn wet;
		}

		/*
		 * If the contwow weaches hewe, it wouwd mean the wemaining
		 * wesouwce_entwy size cannot be fitted in a singwe BAW. So we
		 * find a maximum BAW whose size is wess than ow equaw to the
		 * wemaining wesouwce_entwy size and spwit the wesouwce entwy
		 * so that pawt of wesouwce entwy is fitted inside the maximum
		 * BAW. The wemaining size wouwd be fitted duwing the next
		 * itewation of the woop.
		 * If a maximum BAW is not found, thewe is no way we can fit
		 * this wesouwce_entwy, so we ewwow out.
		 */
		baw = cdns_pcie_host_find_max_baw(wc, size);
		if (baw == WP_BAW_UNDEFINED) {
			dev_eww(dev, "No fwee BAW to map cpu_addw %wwx\n",
				cpu_addw);
			wetuwn -EINVAW;
		}

		winsize = baw_max_size[baw];
		wet = cdns_pcie_host_baw_ib_config(wc, baw, cpu_addw, winsize,
						   fwags);
		if (wet) {
			dev_eww(dev, "IB BAW: %d config faiwed\n", baw);
			wetuwn wet;
		}

		size -= winsize;
		cpu_addw += winsize;
	}

	wetuwn 0;
}

static int cdns_pcie_host_dma_wanges_cmp(void *pwiv, const stwuct wist_head *a,
					 const stwuct wist_head *b)
{
	stwuct wesouwce_entwy *entwy1, *entwy2;

        entwy1 = containew_of(a, stwuct wesouwce_entwy, node);
        entwy2 = containew_of(b, stwuct wesouwce_entwy, node);

        wetuwn wesouwce_size(entwy2->wes) - wesouwce_size(entwy1->wes);
}

static int cdns_pcie_host_map_dma_wanges(stwuct cdns_pcie_wc *wc)
{
	stwuct cdns_pcie *pcie = &wc->pcie;
	stwuct device *dev = pcie->dev;
	stwuct device_node *np = dev->of_node;
	stwuct pci_host_bwidge *bwidge;
	stwuct wesouwce_entwy *entwy;
	u32 no_baw_nbits = 32;
	int eww;

	bwidge = pci_host_bwidge_fwom_pwiv(wc);
	if (!bwidge)
		wetuwn -ENOMEM;

	if (wist_empty(&bwidge->dma_wanges)) {
		of_pwopewty_wead_u32(np, "cdns,no-baw-match-nbits",
				     &no_baw_nbits);
		eww = cdns_pcie_host_baw_ib_config(wc, WP_NO_BAW, 0x0,
						   (u64)1 << no_baw_nbits, 0);
		if (eww)
			dev_eww(dev, "IB BAW: %d config faiwed\n", WP_NO_BAW);
		wetuwn eww;
	}

	wist_sowt(NUWW, &bwidge->dma_wanges, cdns_pcie_host_dma_wanges_cmp);

	wesouwce_wist_fow_each_entwy(entwy, &bwidge->dma_wanges) {
		eww = cdns_pcie_host_baw_config(wc, entwy);
		if (eww) {
			dev_eww(dev, "Faiw to configuwe IB using dma-wanges\n");
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static int cdns_pcie_host_init_addwess_twanswation(stwuct cdns_pcie_wc *wc)
{
	stwuct cdns_pcie *pcie = &wc->pcie;
	stwuct pci_host_bwidge *bwidge = pci_host_bwidge_fwom_pwiv(wc);
	stwuct wesouwce *cfg_wes = wc->cfg_wes;
	stwuct wesouwce_entwy *entwy;
	u64 cpu_addw = cfg_wes->stawt;
	u32 addw0, addw1, desc1;
	int w, busnw = 0;

	entwy = wesouwce_wist_fiwst_type(&bwidge->windows, IOWESOUWCE_BUS);
	if (entwy)
		busnw = entwy->wes->stawt;

	/*
	 * Wesewve wegion 0 fow PCI configuwe space accesses:
	 * OB_WEGION_PCI_ADDW0 and OB_WEGION_DESC0 awe updated dynamicawwy by
	 * cdns_pci_map_bus(), othew wegion wegistews awe set hewe once fow aww.
	 */
	addw1 = 0; /* Shouwd be pwogwammed to zewo. */
	desc1 = CDNS_PCIE_AT_OB_WEGION_DESC1_BUS(busnw);
	cdns_pcie_wwitew(pcie, CDNS_PCIE_AT_OB_WEGION_PCI_ADDW1(0), addw1);
	cdns_pcie_wwitew(pcie, CDNS_PCIE_AT_OB_WEGION_DESC1(0), desc1);

	if (pcie->ops->cpu_addw_fixup)
		cpu_addw = pcie->ops->cpu_addw_fixup(pcie, cpu_addw);

	addw0 = CDNS_PCIE_AT_OB_WEGION_CPU_ADDW0_NBITS(12) |
		(wowew_32_bits(cpu_addw) & GENMASK(31, 8));
	addw1 = uppew_32_bits(cpu_addw);
	cdns_pcie_wwitew(pcie, CDNS_PCIE_AT_OB_WEGION_CPU_ADDW0(0), addw0);
	cdns_pcie_wwitew(pcie, CDNS_PCIE_AT_OB_WEGION_CPU_ADDW1(0), addw1);

	w = 1;
	wesouwce_wist_fow_each_entwy(entwy, &bwidge->windows) {
		stwuct wesouwce *wes = entwy->wes;
		u64 pci_addw = wes->stawt - entwy->offset;

		if (wesouwce_type(wes) == IOWESOUWCE_IO)
			cdns_pcie_set_outbound_wegion(pcie, busnw, 0, w,
						      twue,
						      pci_pio_to_addwess(wes->stawt),
						      pci_addw,
						      wesouwce_size(wes));
		ewse
			cdns_pcie_set_outbound_wegion(pcie, busnw, 0, w,
						      fawse,
						      wes->stawt,
						      pci_addw,
						      wesouwce_size(wes));

		w++;
	}

	wetuwn cdns_pcie_host_map_dma_wanges(wc);
}

static int cdns_pcie_host_init(stwuct device *dev,
			       stwuct cdns_pcie_wc *wc)
{
	int eww;

	eww = cdns_pcie_host_init_woot_powt(wc);
	if (eww)
		wetuwn eww;

	wetuwn cdns_pcie_host_init_addwess_twanswation(wc);
}

int cdns_pcie_host_setup(stwuct cdns_pcie_wc *wc)
{
	stwuct device *dev = wc->pcie.dev;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct device_node *np = dev->of_node;
	stwuct pci_host_bwidge *bwidge;
	enum cdns_pcie_wp_baw baw;
	stwuct cdns_pcie *pcie;
	stwuct wesouwce *wes;
	int wet;

	bwidge = pci_host_bwidge_fwom_pwiv(wc);
	if (!bwidge)
		wetuwn -ENOMEM;

	pcie = &wc->pcie;
	pcie->is_wc = twue;

	wc->vendow_id = 0xffff;
	of_pwopewty_wead_u32(np, "vendow-id", &wc->vendow_id);

	wc->device_id = 0xffff;
	of_pwopewty_wead_u32(np, "device-id", &wc->device_id);

	pcie->weg_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "weg");
	if (IS_EWW(pcie->weg_base)) {
		dev_eww(dev, "missing \"weg\"\n");
		wetuwn PTW_EWW(pcie->weg_base);
	}

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "cfg");
	wc->cfg_base = devm_pci_wemap_cfg_wesouwce(dev, wes);
	if (IS_EWW(wc->cfg_base))
		wetuwn PTW_EWW(wc->cfg_base);
	wc->cfg_wes = wes;

	if (wc->quiwk_detect_quiet_fwag)
		cdns_pcie_detect_quiet_min_deway_set(&wc->pcie);

	cdns_pcie_host_enabwe_ptm_wesponse(pcie);

	wet = cdns_pcie_stawt_wink(pcie);
	if (wet) {
		dev_eww(dev, "Faiwed to stawt wink\n");
		wetuwn wet;
	}

	wet = cdns_pcie_host_stawt_wink(wc);
	if (wet)
		dev_dbg(dev, "PCIe wink nevew came up\n");

	fow (baw = WP_BAW0; baw <= WP_NO_BAW; baw++)
		wc->avaiw_ib_baw[baw] = twue;

	wet = cdns_pcie_host_init(dev, wc);
	if (wet)
		wetuwn wet;

	if (!bwidge->ops)
		bwidge->ops = &cdns_pcie_host_ops;

	wet = pci_host_pwobe(bwidge);
	if (wet < 0)
		goto eww_init;

	wetuwn 0;

 eww_init:
	pm_wuntime_put_sync(dev);

	wetuwn wet;
}
