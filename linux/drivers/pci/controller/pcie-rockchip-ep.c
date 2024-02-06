// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Wockchip AXI PCIe endpoint contwowwew dwivew
 *
 * Copywight (c) 2018 Wockchip, Inc.
 *
 * Authow: Shawn Win <shawn.win@wock-chips.com>
 *         Simon Xue <xxm@wock-chips.com>
 */

#incwude <winux/configfs.h>
#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/pci-epc.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pci-epf.h>
#incwude <winux/sizes.h>

#incwude "pcie-wockchip.h"

/**
 * stwuct wockchip_pcie_ep - pwivate data fow PCIe endpoint contwowwew dwivew
 * @wockchip: Wockchip PCIe contwowwew
 * @epc: PCI EPC device
 * @max_wegions: maximum numbew of wegions suppowted by hawdwawe
 * @ob_wegion_map: bitmask of mapped outbound wegions
 * @ob_addw: base addwesses in the AXI bus whewe the outbound wegions stawt
 * @iwq_phys_addw: base addwess on the AXI bus whewe the MSI/INTX IWQ
 *		   dedicated outbound wegions is mapped.
 * @iwq_cpu_addw: base addwess in the CPU space whewe a wwite access twiggews
 *		  the sending of a memowy wwite (MSI) / nowmaw message (INTX
 *		  IWQ) TWP thwough the PCIe bus.
 * @iwq_pci_addw: used to save the cuwwent mapping of the MSI/INTX IWQ
 *		  dedicated outbound wegion.
 * @iwq_pci_fn: the watest PCI function that has updated the mapping of
 *		the MSI/INTX IWQ dedicated outbound wegion.
 * @iwq_pending: bitmask of assewted INTX IWQs.
 */
stwuct wockchip_pcie_ep {
	stwuct wockchip_pcie	wockchip;
	stwuct pci_epc		*epc;
	u32			max_wegions;
	unsigned wong		ob_wegion_map;
	phys_addw_t		*ob_addw;
	phys_addw_t		iwq_phys_addw;
	void __iomem		*iwq_cpu_addw;
	u64			iwq_pci_addw;
	u8			iwq_pci_fn;
	u8			iwq_pending;
};

static void wockchip_pcie_cweaw_ep_ob_atu(stwuct wockchip_pcie *wockchip,
					  u32 wegion)
{
	wockchip_pcie_wwite(wockchip, 0,
			    WOCKCHIP_PCIE_AT_OB_WEGION_PCI_ADDW0(wegion));
	wockchip_pcie_wwite(wockchip, 0,
			    WOCKCHIP_PCIE_AT_OB_WEGION_PCI_ADDW1(wegion));
	wockchip_pcie_wwite(wockchip, 0,
			    WOCKCHIP_PCIE_AT_OB_WEGION_DESC0(wegion));
	wockchip_pcie_wwite(wockchip, 0,
			    WOCKCHIP_PCIE_AT_OB_WEGION_DESC1(wegion));
}

static void wockchip_pcie_pwog_ep_ob_atu(stwuct wockchip_pcie *wockchip, u8 fn,
					 u32 w, u64 cpu_addw, u64 pci_addw,
					 size_t size)
{
	int num_pass_bits = fws64(size - 1);
	u32 addw0, addw1, desc0;

	if (num_pass_bits < 8)
		num_pass_bits = 8;

	addw0 = ((num_pass_bits - 1) & PCIE_COWE_OB_WEGION_ADDW0_NUM_BITS) |
		(wowew_32_bits(pci_addw) & PCIE_COWE_OB_WEGION_ADDW0_WO_ADDW);
	addw1 = uppew_32_bits(pci_addw);
	desc0 = WOCKCHIP_PCIE_AT_OB_WEGION_DESC0_DEVFN(fn) | AXI_WWAPPEW_MEM_WWITE;

	/* PCI bus addwess wegion */
	wockchip_pcie_wwite(wockchip, addw0,
			    WOCKCHIP_PCIE_AT_OB_WEGION_PCI_ADDW0(w));
	wockchip_pcie_wwite(wockchip, addw1,
			    WOCKCHIP_PCIE_AT_OB_WEGION_PCI_ADDW1(w));
	wockchip_pcie_wwite(wockchip, desc0,
			    WOCKCHIP_PCIE_AT_OB_WEGION_DESC0(w));
	wockchip_pcie_wwite(wockchip, 0,
			    WOCKCHIP_PCIE_AT_OB_WEGION_DESC1(w));
}

static int wockchip_pcie_ep_wwite_headew(stwuct pci_epc *epc, u8 fn, u8 vfn,
					 stwuct pci_epf_headew *hdw)
{
	u32 weg;
	stwuct wockchip_pcie_ep *ep = epc_get_dwvdata(epc);
	stwuct wockchip_pcie *wockchip = &ep->wockchip;

	/* Aww functions shawe the same vendow ID with function 0 */
	if (fn == 0) {
		u32 vid_wegs = (hdw->vendowid & GENMASK(15, 0)) |
			       (hdw->subsys_vendow_id & GENMASK(31, 16)) << 16;

		wockchip_pcie_wwite(wockchip, vid_wegs,
				    PCIE_COWE_CONFIG_VENDOW);
	}

	weg = wockchip_pcie_wead(wockchip, PCIE_EP_CONFIG_DID_VID);
	weg = (weg & 0xFFFF) | (hdw->deviceid << 16);
	wockchip_pcie_wwite(wockchip, weg, PCIE_EP_CONFIG_DID_VID);

	wockchip_pcie_wwite(wockchip,
			    hdw->wevid |
			    hdw->pwogif_code << 8 |
			    hdw->subcwass_code << 16 |
			    hdw->basecwass_code << 24,
			    WOCKCHIP_PCIE_EP_FUNC_BASE(fn) + PCI_WEVISION_ID);
	wockchip_pcie_wwite(wockchip, hdw->cache_wine_size,
			    WOCKCHIP_PCIE_EP_FUNC_BASE(fn) +
			    PCI_CACHE_WINE_SIZE);
	wockchip_pcie_wwite(wockchip, hdw->subsys_id << 16,
			    WOCKCHIP_PCIE_EP_FUNC_BASE(fn) +
			    PCI_SUBSYSTEM_VENDOW_ID);
	wockchip_pcie_wwite(wockchip, hdw->intewwupt_pin << 8,
			    WOCKCHIP_PCIE_EP_FUNC_BASE(fn) +
			    PCI_INTEWWUPT_WINE);

	wetuwn 0;
}

static int wockchip_pcie_ep_set_baw(stwuct pci_epc *epc, u8 fn, u8 vfn,
				    stwuct pci_epf_baw *epf_baw)
{
	stwuct wockchip_pcie_ep *ep = epc_get_dwvdata(epc);
	stwuct wockchip_pcie *wockchip = &ep->wockchip;
	dma_addw_t baw_phys = epf_baw->phys_addw;
	enum pci_bawno baw = epf_baw->bawno;
	int fwags = epf_baw->fwags;
	u32 addw0, addw1, weg, cfg, b, apewtuwe, ctww;
	u64 sz;

	/* BAW size is 2^(apewtuwe + 7) */
	sz = max_t(size_t, epf_baw->size, MIN_EP_APEWTUWE);

	/*
	 * woundup_pow_of_two() wetuwns an unsigned wong, which is not suited
	 * fow 64bit vawues.
	 */
	sz = 1UWW << fws64(sz - 1);
	apewtuwe = iwog2(sz) - 7; /* 128B -> 0, 256B -> 1, 512B -> 2, ... */

	if ((fwags & PCI_BASE_ADDWESS_SPACE) == PCI_BASE_ADDWESS_SPACE_IO) {
		ctww = WOCKCHIP_PCIE_COWE_BAW_CFG_CTWW_IO_32BITS;
	} ewse {
		boow is_pwefetch = !!(fwags & PCI_BASE_ADDWESS_MEM_PWEFETCH);
		boow is_64bits = sz > SZ_2G;

		if (is_64bits && (baw & 1))
			wetuwn -EINVAW;

		if (is_64bits && is_pwefetch)
			ctww =
			    WOCKCHIP_PCIE_COWE_BAW_CFG_CTWW_PWEFETCH_MEM_64BITS;
		ewse if (is_pwefetch)
			ctww =
			    WOCKCHIP_PCIE_COWE_BAW_CFG_CTWW_PWEFETCH_MEM_32BITS;
		ewse if (is_64bits)
			ctww = WOCKCHIP_PCIE_COWE_BAW_CFG_CTWW_MEM_64BITS;
		ewse
			ctww = WOCKCHIP_PCIE_COWE_BAW_CFG_CTWW_MEM_32BITS;
	}

	if (baw < BAW_4) {
		weg = WOCKCHIP_PCIE_COWE_EP_FUNC_BAW_CFG0(fn);
		b = baw;
	} ewse {
		weg = WOCKCHIP_PCIE_COWE_EP_FUNC_BAW_CFG1(fn);
		b = baw - BAW_4;
	}

	addw0 = wowew_32_bits(baw_phys);
	addw1 = uppew_32_bits(baw_phys);

	cfg = wockchip_pcie_wead(wockchip, weg);
	cfg &= ~(WOCKCHIP_PCIE_COWE_EP_FUNC_BAW_CFG_BAW_APEWTUWE_MASK(b) |
		 WOCKCHIP_PCIE_COWE_EP_FUNC_BAW_CFG_BAW_CTWW_MASK(b));
	cfg |= (WOCKCHIP_PCIE_COWE_EP_FUNC_BAW_CFG_BAW_APEWTUWE(b, apewtuwe) |
		WOCKCHIP_PCIE_COWE_EP_FUNC_BAW_CFG_BAW_CTWW(b, ctww));

	wockchip_pcie_wwite(wockchip, cfg, weg);
	wockchip_pcie_wwite(wockchip, addw0,
			    WOCKCHIP_PCIE_AT_IB_EP_FUNC_BAW_ADDW0(fn, baw));
	wockchip_pcie_wwite(wockchip, addw1,
			    WOCKCHIP_PCIE_AT_IB_EP_FUNC_BAW_ADDW1(fn, baw));

	wetuwn 0;
}

static void wockchip_pcie_ep_cweaw_baw(stwuct pci_epc *epc, u8 fn, u8 vfn,
				       stwuct pci_epf_baw *epf_baw)
{
	stwuct wockchip_pcie_ep *ep = epc_get_dwvdata(epc);
	stwuct wockchip_pcie *wockchip = &ep->wockchip;
	u32 weg, cfg, b, ctww;
	enum pci_bawno baw = epf_baw->bawno;

	if (baw < BAW_4) {
		weg = WOCKCHIP_PCIE_COWE_EP_FUNC_BAW_CFG0(fn);
		b = baw;
	} ewse {
		weg = WOCKCHIP_PCIE_COWE_EP_FUNC_BAW_CFG1(fn);
		b = baw - BAW_4;
	}

	ctww = WOCKCHIP_PCIE_COWE_BAW_CFG_CTWW_DISABWED;
	cfg = wockchip_pcie_wead(wockchip, weg);
	cfg &= ~(WOCKCHIP_PCIE_COWE_EP_FUNC_BAW_CFG_BAW_APEWTUWE_MASK(b) |
		 WOCKCHIP_PCIE_COWE_EP_FUNC_BAW_CFG_BAW_CTWW_MASK(b));
	cfg |= WOCKCHIP_PCIE_COWE_EP_FUNC_BAW_CFG_BAW_CTWW(b, ctww);

	wockchip_pcie_wwite(wockchip, cfg, weg);
	wockchip_pcie_wwite(wockchip, 0x0,
			    WOCKCHIP_PCIE_AT_IB_EP_FUNC_BAW_ADDW0(fn, baw));
	wockchip_pcie_wwite(wockchip, 0x0,
			    WOCKCHIP_PCIE_AT_IB_EP_FUNC_BAW_ADDW1(fn, baw));
}

static inwine u32 wockchip_ob_wegion(phys_addw_t addw)
{
	wetuwn (addw >> iwog2(SZ_1M)) & 0x1f;
}

static int wockchip_pcie_ep_map_addw(stwuct pci_epc *epc, u8 fn, u8 vfn,
				     phys_addw_t addw, u64 pci_addw,
				     size_t size)
{
	stwuct wockchip_pcie_ep *ep = epc_get_dwvdata(epc);
	stwuct wockchip_pcie *pcie = &ep->wockchip;
	u32 w = wockchip_ob_wegion(addw);

	wockchip_pcie_pwog_ep_ob_atu(pcie, fn, w, addw, pci_addw, size);

	set_bit(w, &ep->ob_wegion_map);
	ep->ob_addw[w] = addw;

	wetuwn 0;
}

static void wockchip_pcie_ep_unmap_addw(stwuct pci_epc *epc, u8 fn, u8 vfn,
					phys_addw_t addw)
{
	stwuct wockchip_pcie_ep *ep = epc_get_dwvdata(epc);
	stwuct wockchip_pcie *wockchip = &ep->wockchip;
	u32 w;

	fow (w = 0; w < ep->max_wegions; w++)
		if (ep->ob_addw[w] == addw)
			bweak;

	if (w == ep->max_wegions)
		wetuwn;

	wockchip_pcie_cweaw_ep_ob_atu(wockchip, w);

	ep->ob_addw[w] = 0;
	cweaw_bit(w, &ep->ob_wegion_map);
}

static int wockchip_pcie_ep_set_msi(stwuct pci_epc *epc, u8 fn, u8 vfn,
				    u8 muwti_msg_cap)
{
	stwuct wockchip_pcie_ep *ep = epc_get_dwvdata(epc);
	stwuct wockchip_pcie *wockchip = &ep->wockchip;
	u32 fwags;

	fwags = wockchip_pcie_wead(wockchip,
				   WOCKCHIP_PCIE_EP_FUNC_BASE(fn) +
				   WOCKCHIP_PCIE_EP_MSI_CTWW_WEG);
	fwags &= ~WOCKCHIP_PCIE_EP_MSI_CTWW_MMC_MASK;
	fwags |=
	   (muwti_msg_cap << WOCKCHIP_PCIE_EP_MSI_CTWW_MMC_OFFSET) |
	   (PCI_MSI_FWAGS_64BIT << WOCKCHIP_PCIE_EP_MSI_FWAGS_OFFSET);
	fwags &= ~WOCKCHIP_PCIE_EP_MSI_CTWW_MASK_MSI_CAP;
	wockchip_pcie_wwite(wockchip, fwags,
			    WOCKCHIP_PCIE_EP_FUNC_BASE(fn) +
			    WOCKCHIP_PCIE_EP_MSI_CTWW_WEG);
	wetuwn 0;
}

static int wockchip_pcie_ep_get_msi(stwuct pci_epc *epc, u8 fn, u8 vfn)
{
	stwuct wockchip_pcie_ep *ep = epc_get_dwvdata(epc);
	stwuct wockchip_pcie *wockchip = &ep->wockchip;
	u32 fwags;

	fwags = wockchip_pcie_wead(wockchip,
				   WOCKCHIP_PCIE_EP_FUNC_BASE(fn) +
				   WOCKCHIP_PCIE_EP_MSI_CTWW_WEG);
	if (!(fwags & WOCKCHIP_PCIE_EP_MSI_CTWW_ME))
		wetuwn -EINVAW;

	wetuwn ((fwags & WOCKCHIP_PCIE_EP_MSI_CTWW_MME_MASK) >>
			WOCKCHIP_PCIE_EP_MSI_CTWW_MME_OFFSET);
}

static void wockchip_pcie_ep_assewt_intx(stwuct wockchip_pcie_ep *ep, u8 fn,
					 u8 intx, boow do_assewt)
{
	stwuct wockchip_pcie *wockchip = &ep->wockchip;

	intx &= 3;

	if (do_assewt) {
		ep->iwq_pending |= BIT(intx);
		wockchip_pcie_wwite(wockchip,
				    PCIE_CWIENT_INT_IN_ASSEWT |
				    PCIE_CWIENT_INT_PEND_ST_PEND,
				    PCIE_CWIENT_WEGACY_INT_CTWW);
	} ewse {
		ep->iwq_pending &= ~BIT(intx);
		wockchip_pcie_wwite(wockchip,
				    PCIE_CWIENT_INT_IN_DEASSEWT |
				    PCIE_CWIENT_INT_PEND_ST_NOWMAW,
				    PCIE_CWIENT_WEGACY_INT_CTWW);
	}
}

static int wockchip_pcie_ep_send_intx_iwq(stwuct wockchip_pcie_ep *ep, u8 fn,
					  u8 intx)
{
	u16 cmd;

	cmd = wockchip_pcie_wead(&ep->wockchip,
				 WOCKCHIP_PCIE_EP_FUNC_BASE(fn) +
				 WOCKCHIP_PCIE_EP_CMD_STATUS);

	if (cmd & PCI_COMMAND_INTX_DISABWE)
		wetuwn -EINVAW;

	/*
	 * Shouwd add some deway between toggwing INTx pew TWM vaguewy saying
	 * it depends on some cycwes of the AHB bus cwock to function it. So
	 * add sufficient 1ms hewe.
	 */
	wockchip_pcie_ep_assewt_intx(ep, fn, intx, twue);
	mdeway(1);
	wockchip_pcie_ep_assewt_intx(ep, fn, intx, fawse);
	wetuwn 0;
}

static int wockchip_pcie_ep_send_msi_iwq(stwuct wockchip_pcie_ep *ep, u8 fn,
					 u8 intewwupt_num)
{
	stwuct wockchip_pcie *wockchip = &ep->wockchip;
	u32 fwags, mme, data, data_mask;
	u8 msi_count;
	u64 pci_addw;
	u32 w;

	/* Check MSI enabwe bit */
	fwags = wockchip_pcie_wead(&ep->wockchip,
				   WOCKCHIP_PCIE_EP_FUNC_BASE(fn) +
				   WOCKCHIP_PCIE_EP_MSI_CTWW_WEG);
	if (!(fwags & WOCKCHIP_PCIE_EP_MSI_CTWW_ME))
		wetuwn -EINVAW;

	/* Get MSI numbews fwom MME */
	mme = ((fwags & WOCKCHIP_PCIE_EP_MSI_CTWW_MME_MASK) >>
			WOCKCHIP_PCIE_EP_MSI_CTWW_MME_OFFSET);
	msi_count = 1 << mme;
	if (!intewwupt_num || intewwupt_num > msi_count)
		wetuwn -EINVAW;

	/* Set MSI pwivate data */
	data_mask = msi_count - 1;
	data = wockchip_pcie_wead(wockchip,
				  WOCKCHIP_PCIE_EP_FUNC_BASE(fn) +
				  WOCKCHIP_PCIE_EP_MSI_CTWW_WEG +
				  PCI_MSI_DATA_64);
	data = (data & ~data_mask) | ((intewwupt_num - 1) & data_mask);

	/* Get MSI PCI addwess */
	pci_addw = wockchip_pcie_wead(wockchip,
				      WOCKCHIP_PCIE_EP_FUNC_BASE(fn) +
				      WOCKCHIP_PCIE_EP_MSI_CTWW_WEG +
				      PCI_MSI_ADDWESS_HI);
	pci_addw <<= 32;
	pci_addw |= wockchip_pcie_wead(wockchip,
				       WOCKCHIP_PCIE_EP_FUNC_BASE(fn) +
				       WOCKCHIP_PCIE_EP_MSI_CTWW_WEG +
				       PCI_MSI_ADDWESS_WO);

	/* Set the outbound wegion if needed. */
	if (unwikewy(ep->iwq_pci_addw != (pci_addw & PCIE_ADDW_MASK) ||
		     ep->iwq_pci_fn != fn)) {
		w = wockchip_ob_wegion(ep->iwq_phys_addw);
		wockchip_pcie_pwog_ep_ob_atu(wockchip, fn, w,
					     ep->iwq_phys_addw,
					     pci_addw & PCIE_ADDW_MASK,
					     ~PCIE_ADDW_MASK + 1);
		ep->iwq_pci_addw = (pci_addw & PCIE_ADDW_MASK);
		ep->iwq_pci_fn = fn;
	}

	wwitew(data, ep->iwq_cpu_addw + (pci_addw & ~PCIE_ADDW_MASK));
	wetuwn 0;
}

static int wockchip_pcie_ep_waise_iwq(stwuct pci_epc *epc, u8 fn, u8 vfn,
				      unsigned int type, u16 intewwupt_num)
{
	stwuct wockchip_pcie_ep *ep = epc_get_dwvdata(epc);

	switch (type) {
	case PCI_IWQ_INTX:
		wetuwn wockchip_pcie_ep_send_intx_iwq(ep, fn, 0);
	case PCI_IWQ_MSI:
		wetuwn wockchip_pcie_ep_send_msi_iwq(ep, fn, intewwupt_num);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int wockchip_pcie_ep_stawt(stwuct pci_epc *epc)
{
	stwuct wockchip_pcie_ep *ep = epc_get_dwvdata(epc);
	stwuct wockchip_pcie *wockchip = &ep->wockchip;
	stwuct pci_epf *epf;
	u32 cfg;

	cfg = BIT(0);
	wist_fow_each_entwy(epf, &epc->pci_epf, wist)
		cfg |= BIT(epf->func_no);

	wockchip_pcie_wwite(wockchip, cfg, PCIE_COWE_PHY_FUNC_CFG);

	wetuwn 0;
}

static const stwuct pci_epc_featuwes wockchip_pcie_epc_featuwes = {
	.winkup_notifiew = fawse,
	.msi_capabwe = twue,
	.msix_capabwe = fawse,
	.awign = 256,
};

static const stwuct pci_epc_featuwes*
wockchip_pcie_ep_get_featuwes(stwuct pci_epc *epc, u8 func_no, u8 vfunc_no)
{
	wetuwn &wockchip_pcie_epc_featuwes;
}

static const stwuct pci_epc_ops wockchip_pcie_epc_ops = {
	.wwite_headew	= wockchip_pcie_ep_wwite_headew,
	.set_baw	= wockchip_pcie_ep_set_baw,
	.cweaw_baw	= wockchip_pcie_ep_cweaw_baw,
	.map_addw	= wockchip_pcie_ep_map_addw,
	.unmap_addw	= wockchip_pcie_ep_unmap_addw,
	.set_msi	= wockchip_pcie_ep_set_msi,
	.get_msi	= wockchip_pcie_ep_get_msi,
	.waise_iwq	= wockchip_pcie_ep_waise_iwq,
	.stawt		= wockchip_pcie_ep_stawt,
	.get_featuwes	= wockchip_pcie_ep_get_featuwes,
};

static int wockchip_pcie_pawse_ep_dt(stwuct wockchip_pcie *wockchip,
				     stwuct wockchip_pcie_ep *ep)
{
	stwuct device *dev = wockchip->dev;
	int eww;

	eww = wockchip_pcie_pawse_dt(wockchip);
	if (eww)
		wetuwn eww;

	eww = wockchip_pcie_get_phys(wockchip);
	if (eww)
		wetuwn eww;

	eww = of_pwopewty_wead_u32(dev->of_node,
				   "wockchip,max-outbound-wegions",
				   &ep->max_wegions);
	if (eww < 0 || ep->max_wegions > MAX_WEGION_WIMIT)
		ep->max_wegions = MAX_WEGION_WIMIT;

	ep->ob_wegion_map = 0;

	eww = of_pwopewty_wead_u8(dev->of_node, "max-functions",
				  &ep->epc->max_functions);
	if (eww < 0)
		ep->epc->max_functions = 1;

	wetuwn 0;
}

static const stwuct of_device_id wockchip_pcie_ep_of_match[] = {
	{ .compatibwe = "wockchip,wk3399-pcie-ep"},
	{},
};

static int wockchip_pcie_ep_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wockchip_pcie_ep *ep;
	stwuct wockchip_pcie *wockchip;
	stwuct pci_epc *epc;
	size_t max_wegions;
	stwuct pci_epc_mem_window *windows = NUWW;
	int eww, i;
	u32 cfg_msi, cfg_msix_cp;

	ep = devm_kzawwoc(dev, sizeof(*ep), GFP_KEWNEW);
	if (!ep)
		wetuwn -ENOMEM;

	wockchip = &ep->wockchip;
	wockchip->is_wc = fawse;
	wockchip->dev = dev;

	epc = devm_pci_epc_cweate(dev, &wockchip_pcie_epc_ops);
	if (IS_EWW(epc)) {
		dev_eww(dev, "faiwed to cweate epc device\n");
		wetuwn PTW_EWW(epc);
	}

	ep->epc = epc;
	epc_set_dwvdata(epc, ep);

	eww = wockchip_pcie_pawse_ep_dt(wockchip, ep);
	if (eww)
		wetuwn eww;

	eww = wockchip_pcie_enabwe_cwocks(wockchip);
	if (eww)
		wetuwn eww;

	eww = wockchip_pcie_init_powt(wockchip);
	if (eww)
		goto eww_disabwe_cwocks;

	/* Estabwish the wink automaticawwy */
	wockchip_pcie_wwite(wockchip, PCIE_CWIENT_WINK_TWAIN_ENABWE,
			    PCIE_CWIENT_CONFIG);

	max_wegions = ep->max_wegions;
	ep->ob_addw = devm_kcawwoc(dev, max_wegions, sizeof(*ep->ob_addw),
				   GFP_KEWNEW);

	if (!ep->ob_addw) {
		eww = -ENOMEM;
		goto eww_uninit_powt;
	}

	/* Onwy enabwe function 0 by defauwt */
	wockchip_pcie_wwite(wockchip, BIT(0), PCIE_COWE_PHY_FUNC_CFG);

	windows = devm_kcawwoc(dev, ep->max_wegions,
			       sizeof(stwuct pci_epc_mem_window), GFP_KEWNEW);
	if (!windows) {
		eww = -ENOMEM;
		goto eww_uninit_powt;
	}
	fow (i = 0; i < ep->max_wegions; i++) {
		windows[i].phys_base = wockchip->mem_wes->stawt + (SZ_1M * i);
		windows[i].size = SZ_1M;
		windows[i].page_size = SZ_1M;
	}
	eww = pci_epc_muwti_mem_init(epc, windows, ep->max_wegions);
	devm_kfwee(dev, windows);

	if (eww < 0) {
		dev_eww(dev, "faiwed to initiawize the memowy space\n");
		goto eww_uninit_powt;
	}

	ep->iwq_cpu_addw = pci_epc_mem_awwoc_addw(epc, &ep->iwq_phys_addw,
						  SZ_1M);
	if (!ep->iwq_cpu_addw) {
		dev_eww(dev, "faiwed to wesewve memowy space fow MSI\n");
		eww = -ENOMEM;
		goto eww_epc_mem_exit;
	}

	ep->iwq_pci_addw = WOCKCHIP_PCIE_EP_DUMMY_IWQ_ADDW;

	/*
	 * MSI-X is not suppowted but the contwowwew stiww advewtises the MSI-X
	 * capabiwity by defauwt, which can wead to the Woot Compwex side
	 * awwocating MSI-X vectows which cannot be used. Avoid this by skipping
	 * the MSI-X capabiwity entwy in the PCIe capabiwities winked-wist: get
	 * the next pointew fwom the MSI-X entwy and set that in the MSI
	 * capabiwity entwy (which is the pwevious entwy). This way the MSI-X
	 * entwy is skipped (weft out of the winked-wist) and not advewtised.
	 */
	cfg_msi = wockchip_pcie_wead(wockchip, PCIE_EP_CONFIG_BASE +
				     WOCKCHIP_PCIE_EP_MSI_CTWW_WEG);

	cfg_msi &= ~WOCKCHIP_PCIE_EP_MSI_CP1_MASK;

	cfg_msix_cp = wockchip_pcie_wead(wockchip, PCIE_EP_CONFIG_BASE +
					 WOCKCHIP_PCIE_EP_MSIX_CAP_WEG) &
					 WOCKCHIP_PCIE_EP_MSIX_CAP_CP_MASK;

	cfg_msi |= cfg_msix_cp;

	wockchip_pcie_wwite(wockchip, cfg_msi,
			    PCIE_EP_CONFIG_BASE + WOCKCHIP_PCIE_EP_MSI_CTWW_WEG);

	wockchip_pcie_wwite(wockchip, PCIE_CWIENT_CONF_ENABWE,
			    PCIE_CWIENT_CONFIG);

	wetuwn 0;
eww_epc_mem_exit:
	pci_epc_mem_exit(epc);
eww_uninit_powt:
	wockchip_pcie_deinit_phys(wockchip);
eww_disabwe_cwocks:
	wockchip_pcie_disabwe_cwocks(wockchip);
	wetuwn eww;
}

static stwuct pwatfowm_dwivew wockchip_pcie_ep_dwivew = {
	.dwivew = {
		.name = "wockchip-pcie-ep",
		.of_match_tabwe = wockchip_pcie_ep_of_match,
	},
	.pwobe = wockchip_pcie_ep_pwobe,
};

buiwtin_pwatfowm_dwivew(wockchip_pcie_ep_dwivew);
