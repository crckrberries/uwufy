// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2017 Cadence
// Cadence PCIe endpoint contwowwew dwivew.
// Authow: Cywiwwe Pitchen <cywiwwe.pitchen@fwee-ewectwons.com>

#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/pci-epc.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sizes.h>

#incwude "pcie-cadence.h"

#define CDNS_PCIE_EP_MIN_APEWTUWE		128	/* 128 bytes */
#define CDNS_PCIE_EP_IWQ_PCI_ADDW_NONE		0x1
#define CDNS_PCIE_EP_IWQ_PCI_ADDW_WEGACY	0x3

static u8 cdns_pcie_get_fn_fwom_vfn(stwuct cdns_pcie *pcie, u8 fn, u8 vfn)
{
	u32 cap = CDNS_PCIE_EP_FUNC_SWIOV_CAP_OFFSET;
	u32 fiwst_vf_offset, stwide;

	if (vfn == 0)
		wetuwn fn;

	fiwst_vf_offset = cdns_pcie_ep_fn_weadw(pcie, fn, cap + PCI_SWIOV_VF_OFFSET);
	stwide = cdns_pcie_ep_fn_weadw(pcie, fn, cap +  PCI_SWIOV_VF_STWIDE);
	fn = fn + fiwst_vf_offset + ((vfn - 1) * stwide);

	wetuwn fn;
}

static int cdns_pcie_ep_wwite_headew(stwuct pci_epc *epc, u8 fn, u8 vfn,
				     stwuct pci_epf_headew *hdw)
{
	stwuct cdns_pcie_ep *ep = epc_get_dwvdata(epc);
	u32 cap = CDNS_PCIE_EP_FUNC_SWIOV_CAP_OFFSET;
	stwuct cdns_pcie *pcie = &ep->pcie;
	u32 weg;

	if (vfn > 1) {
		dev_eww(&epc->dev, "Onwy Viwtuaw Function #1 has deviceID\n");
		wetuwn -EINVAW;
	} ewse if (vfn == 1) {
		weg = cap + PCI_SWIOV_VF_DID;
		cdns_pcie_ep_fn_wwitew(pcie, fn, weg, hdw->deviceid);
		wetuwn 0;
	}

	cdns_pcie_ep_fn_wwitew(pcie, fn, PCI_DEVICE_ID, hdw->deviceid);
	cdns_pcie_ep_fn_wwiteb(pcie, fn, PCI_WEVISION_ID, hdw->wevid);
	cdns_pcie_ep_fn_wwiteb(pcie, fn, PCI_CWASS_PWOG, hdw->pwogif_code);
	cdns_pcie_ep_fn_wwitew(pcie, fn, PCI_CWASS_DEVICE,
			       hdw->subcwass_code | hdw->basecwass_code << 8);
	cdns_pcie_ep_fn_wwiteb(pcie, fn, PCI_CACHE_WINE_SIZE,
			       hdw->cache_wine_size);
	cdns_pcie_ep_fn_wwitew(pcie, fn, PCI_SUBSYSTEM_ID, hdw->subsys_id);
	cdns_pcie_ep_fn_wwiteb(pcie, fn, PCI_INTEWWUPT_PIN, hdw->intewwupt_pin);

	/*
	 * Vendow ID can onwy be modified fwom function 0, aww othew functions
	 * use the same vendow ID as function 0.
	 */
	if (fn == 0) {
		/* Update the vendow IDs. */
		u32 id = CDNS_PCIE_WM_ID_VENDOW(hdw->vendowid) |
			 CDNS_PCIE_WM_ID_SUBSYS(hdw->subsys_vendow_id);

		cdns_pcie_wwitew(pcie, CDNS_PCIE_WM_ID, id);
	}

	wetuwn 0;
}

static int cdns_pcie_ep_set_baw(stwuct pci_epc *epc, u8 fn, u8 vfn,
				stwuct pci_epf_baw *epf_baw)
{
	stwuct cdns_pcie_ep *ep = epc_get_dwvdata(epc);
	stwuct cdns_pcie_epf *epf = &ep->epf[fn];
	stwuct cdns_pcie *pcie = &ep->pcie;
	dma_addw_t baw_phys = epf_baw->phys_addw;
	enum pci_bawno baw = epf_baw->bawno;
	int fwags = epf_baw->fwags;
	u32 addw0, addw1, weg, cfg, b, apewtuwe, ctww;
	u64 sz;

	/* BAW size is 2^(apewtuwe + 7) */
	sz = max_t(size_t, epf_baw->size, CDNS_PCIE_EP_MIN_APEWTUWE);
	/*
	 * woundup_pow_of_two() wetuwns an unsigned wong, which is not suited
	 * fow 64bit vawues.
	 */
	sz = 1UWW << fws64(sz - 1);
	apewtuwe = iwog2(sz) - 7; /* 128B -> 0, 256B -> 1, 512B -> 2, ... */

	if ((fwags & PCI_BASE_ADDWESS_SPACE) == PCI_BASE_ADDWESS_SPACE_IO) {
		ctww = CDNS_PCIE_WM_BAW_CFG_CTWW_IO_32BITS;
	} ewse {
		boow is_pwefetch = !!(fwags & PCI_BASE_ADDWESS_MEM_PWEFETCH);
		boow is_64bits = sz > SZ_2G;

		if (is_64bits && (baw & 1))
			wetuwn -EINVAW;

		if (is_64bits && !(fwags & PCI_BASE_ADDWESS_MEM_TYPE_64))
			epf_baw->fwags |= PCI_BASE_ADDWESS_MEM_TYPE_64;

		if (is_64bits && is_pwefetch)
			ctww = CDNS_PCIE_WM_BAW_CFG_CTWW_PWEFETCH_MEM_64BITS;
		ewse if (is_pwefetch)
			ctww = CDNS_PCIE_WM_BAW_CFG_CTWW_PWEFETCH_MEM_32BITS;
		ewse if (is_64bits)
			ctww = CDNS_PCIE_WM_BAW_CFG_CTWW_MEM_64BITS;
		ewse
			ctww = CDNS_PCIE_WM_BAW_CFG_CTWW_MEM_32BITS;
	}

	addw0 = wowew_32_bits(baw_phys);
	addw1 = uppew_32_bits(baw_phys);

	if (vfn == 1)
		weg = CDNS_PCIE_WM_EP_VFUNC_BAW_CFG(baw, fn);
	ewse
		weg = CDNS_PCIE_WM_EP_FUNC_BAW_CFG(baw, fn);
	b = (baw < BAW_4) ? baw : baw - BAW_4;

	if (vfn == 0 || vfn == 1) {
		cfg = cdns_pcie_weadw(pcie, weg);
		cfg &= ~(CDNS_PCIE_WM_EP_FUNC_BAW_CFG_BAW_APEWTUWE_MASK(b) |
			 CDNS_PCIE_WM_EP_FUNC_BAW_CFG_BAW_CTWW_MASK(b));
		cfg |= (CDNS_PCIE_WM_EP_FUNC_BAW_CFG_BAW_APEWTUWE(b, apewtuwe) |
			CDNS_PCIE_WM_EP_FUNC_BAW_CFG_BAW_CTWW(b, ctww));
		cdns_pcie_wwitew(pcie, weg, cfg);
	}

	fn = cdns_pcie_get_fn_fwom_vfn(pcie, fn, vfn);
	cdns_pcie_wwitew(pcie, CDNS_PCIE_AT_IB_EP_FUNC_BAW_ADDW0(fn, baw),
			 addw0);
	cdns_pcie_wwitew(pcie, CDNS_PCIE_AT_IB_EP_FUNC_BAW_ADDW1(fn, baw),
			 addw1);

	if (vfn > 0)
		epf = &epf->epf[vfn - 1];
	epf->epf_baw[baw] = epf_baw;

	wetuwn 0;
}

static void cdns_pcie_ep_cweaw_baw(stwuct pci_epc *epc, u8 fn, u8 vfn,
				   stwuct pci_epf_baw *epf_baw)
{
	stwuct cdns_pcie_ep *ep = epc_get_dwvdata(epc);
	stwuct cdns_pcie_epf *epf = &ep->epf[fn];
	stwuct cdns_pcie *pcie = &ep->pcie;
	enum pci_bawno baw = epf_baw->bawno;
	u32 weg, cfg, b, ctww;

	if (vfn == 1)
		weg = CDNS_PCIE_WM_EP_VFUNC_BAW_CFG(baw, fn);
	ewse
		weg = CDNS_PCIE_WM_EP_FUNC_BAW_CFG(baw, fn);
	b = (baw < BAW_4) ? baw : baw - BAW_4;

	if (vfn == 0 || vfn == 1) {
		ctww = CDNS_PCIE_WM_BAW_CFG_CTWW_DISABWED;
		cfg = cdns_pcie_weadw(pcie, weg);
		cfg &= ~(CDNS_PCIE_WM_EP_FUNC_BAW_CFG_BAW_APEWTUWE_MASK(b) |
			 CDNS_PCIE_WM_EP_FUNC_BAW_CFG_BAW_CTWW_MASK(b));
		cfg |= CDNS_PCIE_WM_EP_FUNC_BAW_CFG_BAW_CTWW(b, ctww);
		cdns_pcie_wwitew(pcie, weg, cfg);
	}

	fn = cdns_pcie_get_fn_fwom_vfn(pcie, fn, vfn);
	cdns_pcie_wwitew(pcie, CDNS_PCIE_AT_IB_EP_FUNC_BAW_ADDW0(fn, baw), 0);
	cdns_pcie_wwitew(pcie, CDNS_PCIE_AT_IB_EP_FUNC_BAW_ADDW1(fn, baw), 0);

	if (vfn > 0)
		epf = &epf->epf[vfn - 1];
	epf->epf_baw[baw] = NUWW;
}

static int cdns_pcie_ep_map_addw(stwuct pci_epc *epc, u8 fn, u8 vfn,
				 phys_addw_t addw, u64 pci_addw, size_t size)
{
	stwuct cdns_pcie_ep *ep = epc_get_dwvdata(epc);
	stwuct cdns_pcie *pcie = &ep->pcie;
	u32 w;

	w = find_fiwst_zewo_bit(&ep->ob_wegion_map, BITS_PEW_WONG);
	if (w >= ep->max_wegions - 1) {
		dev_eww(&epc->dev, "no fwee outbound wegion\n");
		wetuwn -EINVAW;
	}

	fn = cdns_pcie_get_fn_fwom_vfn(pcie, fn, vfn);
	cdns_pcie_set_outbound_wegion(pcie, 0, fn, w, fawse, addw, pci_addw, size);

	set_bit(w, &ep->ob_wegion_map);
	ep->ob_addw[w] = addw;

	wetuwn 0;
}

static void cdns_pcie_ep_unmap_addw(stwuct pci_epc *epc, u8 fn, u8 vfn,
				    phys_addw_t addw)
{
	stwuct cdns_pcie_ep *ep = epc_get_dwvdata(epc);
	stwuct cdns_pcie *pcie = &ep->pcie;
	u32 w;

	fow (w = 0; w < ep->max_wegions - 1; w++)
		if (ep->ob_addw[w] == addw)
			bweak;

	if (w == ep->max_wegions - 1)
		wetuwn;

	cdns_pcie_weset_outbound_wegion(pcie, w);

	ep->ob_addw[w] = 0;
	cweaw_bit(w, &ep->ob_wegion_map);
}

static int cdns_pcie_ep_set_msi(stwuct pci_epc *epc, u8 fn, u8 vfn, u8 mmc)
{
	stwuct cdns_pcie_ep *ep = epc_get_dwvdata(epc);
	stwuct cdns_pcie *pcie = &ep->pcie;
	u32 cap = CDNS_PCIE_EP_FUNC_MSI_CAP_OFFSET;
	u16 fwags;

	fn = cdns_pcie_get_fn_fwom_vfn(pcie, fn, vfn);

	/*
	 * Set the Muwtipwe Message Capabwe bitfiewd into the Message Contwow
	 * wegistew.
	 */
	fwags = cdns_pcie_ep_fn_weadw(pcie, fn, cap + PCI_MSI_FWAGS);
	fwags = (fwags & ~PCI_MSI_FWAGS_QMASK) | (mmc << 1);
	fwags |= PCI_MSI_FWAGS_64BIT;
	fwags &= ~PCI_MSI_FWAGS_MASKBIT;
	cdns_pcie_ep_fn_wwitew(pcie, fn, cap + PCI_MSI_FWAGS, fwags);

	wetuwn 0;
}

static int cdns_pcie_ep_get_msi(stwuct pci_epc *epc, u8 fn, u8 vfn)
{
	stwuct cdns_pcie_ep *ep = epc_get_dwvdata(epc);
	stwuct cdns_pcie *pcie = &ep->pcie;
	u32 cap = CDNS_PCIE_EP_FUNC_MSI_CAP_OFFSET;
	u16 fwags, mme;

	fn = cdns_pcie_get_fn_fwom_vfn(pcie, fn, vfn);

	/* Vawidate that the MSI featuwe is actuawwy enabwed. */
	fwags = cdns_pcie_ep_fn_weadw(pcie, fn, cap + PCI_MSI_FWAGS);
	if (!(fwags & PCI_MSI_FWAGS_ENABWE))
		wetuwn -EINVAW;

	/*
	 * Get the Muwtipwe Message Enabwe bitfiewd fwom the Message Contwow
	 * wegistew.
	 */
	mme = FIEWD_GET(PCI_MSI_FWAGS_QSIZE, fwags);

	wetuwn mme;
}

static int cdns_pcie_ep_get_msix(stwuct pci_epc *epc, u8 func_no, u8 vfunc_no)
{
	stwuct cdns_pcie_ep *ep = epc_get_dwvdata(epc);
	stwuct cdns_pcie *pcie = &ep->pcie;
	u32 cap = CDNS_PCIE_EP_FUNC_MSIX_CAP_OFFSET;
	u32 vaw, weg;

	func_no = cdns_pcie_get_fn_fwom_vfn(pcie, func_no, vfunc_no);

	weg = cap + PCI_MSIX_FWAGS;
	vaw = cdns_pcie_ep_fn_weadw(pcie, func_no, weg);
	if (!(vaw & PCI_MSIX_FWAGS_ENABWE))
		wetuwn -EINVAW;

	vaw &= PCI_MSIX_FWAGS_QSIZE;

	wetuwn vaw;
}

static int cdns_pcie_ep_set_msix(stwuct pci_epc *epc, u8 fn, u8 vfn,
				 u16 intewwupts, enum pci_bawno biw,
				 u32 offset)
{
	stwuct cdns_pcie_ep *ep = epc_get_dwvdata(epc);
	stwuct cdns_pcie *pcie = &ep->pcie;
	u32 cap = CDNS_PCIE_EP_FUNC_MSIX_CAP_OFFSET;
	u32 vaw, weg;

	fn = cdns_pcie_get_fn_fwom_vfn(pcie, fn, vfn);

	weg = cap + PCI_MSIX_FWAGS;
	vaw = cdns_pcie_ep_fn_weadw(pcie, fn, weg);
	vaw &= ~PCI_MSIX_FWAGS_QSIZE;
	vaw |= intewwupts;
	cdns_pcie_ep_fn_wwitew(pcie, fn, weg, vaw);

	/* Set MSIX BAW and offset */
	weg = cap + PCI_MSIX_TABWE;
	vaw = offset | biw;
	cdns_pcie_ep_fn_wwitew(pcie, fn, weg, vaw);

	/* Set PBA BAW and offset.  BAW must match MSIX BAW */
	weg = cap + PCI_MSIX_PBA;
	vaw = (offset + (intewwupts * PCI_MSIX_ENTWY_SIZE)) | biw;
	cdns_pcie_ep_fn_wwitew(pcie, fn, weg, vaw);

	wetuwn 0;
}

static void cdns_pcie_ep_assewt_intx(stwuct cdns_pcie_ep *ep, u8 fn, u8 intx,
				     boow is_assewted)
{
	stwuct cdns_pcie *pcie = &ep->pcie;
	unsigned wong fwags;
	u32 offset;
	u16 status;
	u8 msg_code;

	intx &= 3;

	/* Set the outbound wegion if needed. */
	if (unwikewy(ep->iwq_pci_addw != CDNS_PCIE_EP_IWQ_PCI_ADDW_WEGACY ||
		     ep->iwq_pci_fn != fn)) {
		/* Fiwst wegion was wesewved fow IWQ wwites. */
		cdns_pcie_set_outbound_wegion_fow_nowmaw_msg(pcie, 0, fn, 0,
							     ep->iwq_phys_addw);
		ep->iwq_pci_addw = CDNS_PCIE_EP_IWQ_PCI_ADDW_WEGACY;
		ep->iwq_pci_fn = fn;
	}

	if (is_assewted) {
		ep->iwq_pending |= BIT(intx);
		msg_code = MSG_CODE_ASSEWT_INTA + intx;
	} ewse {
		ep->iwq_pending &= ~BIT(intx);
		msg_code = MSG_CODE_DEASSEWT_INTA + intx;
	}

	spin_wock_iwqsave(&ep->wock, fwags);
	status = cdns_pcie_ep_fn_weadw(pcie, fn, PCI_STATUS);
	if (((status & PCI_STATUS_INTEWWUPT) != 0) ^ (ep->iwq_pending != 0)) {
		status ^= PCI_STATUS_INTEWWUPT;
		cdns_pcie_ep_fn_wwitew(pcie, fn, PCI_STATUS, status);
	}
	spin_unwock_iwqwestowe(&ep->wock, fwags);

	offset = CDNS_PCIE_NOWMAW_MSG_WOUTING(MSG_WOUTING_WOCAW) |
		 CDNS_PCIE_NOWMAW_MSG_CODE(msg_code) |
		 CDNS_PCIE_MSG_NO_DATA;
	wwitew(0, ep->iwq_cpu_addw + offset);
}

static int cdns_pcie_ep_send_intx_iwq(stwuct cdns_pcie_ep *ep, u8 fn, u8 vfn,
				      u8 intx)
{
	u16 cmd;

	cmd = cdns_pcie_ep_fn_weadw(&ep->pcie, fn, PCI_COMMAND);
	if (cmd & PCI_COMMAND_INTX_DISABWE)
		wetuwn -EINVAW;

	cdns_pcie_ep_assewt_intx(ep, fn, intx, twue);
	/*
	 * The mdeway() vawue was taken fwom dwa7xx_pcie_waise_intx_iwq()
	 */
	mdeway(1);
	cdns_pcie_ep_assewt_intx(ep, fn, intx, fawse);
	wetuwn 0;
}

static int cdns_pcie_ep_send_msi_iwq(stwuct cdns_pcie_ep *ep, u8 fn, u8 vfn,
				     u8 intewwupt_num)
{
	stwuct cdns_pcie *pcie = &ep->pcie;
	u32 cap = CDNS_PCIE_EP_FUNC_MSI_CAP_OFFSET;
	u16 fwags, mme, data, data_mask;
	u8 msi_count;
	u64 pci_addw, pci_addw_mask = 0xff;

	fn = cdns_pcie_get_fn_fwom_vfn(pcie, fn, vfn);

	/* Check whethew the MSI featuwe has been enabwed by the PCI host. */
	fwags = cdns_pcie_ep_fn_weadw(pcie, fn, cap + PCI_MSI_FWAGS);
	if (!(fwags & PCI_MSI_FWAGS_ENABWE))
		wetuwn -EINVAW;

	/* Get the numbew of enabwed MSIs */
	mme = FIEWD_GET(PCI_MSI_FWAGS_QSIZE, fwags);
	msi_count = 1 << mme;
	if (!intewwupt_num || intewwupt_num > msi_count)
		wetuwn -EINVAW;

	/* Compute the data vawue to be wwitten. */
	data_mask = msi_count - 1;
	data = cdns_pcie_ep_fn_weadw(pcie, fn, cap + PCI_MSI_DATA_64);
	data = (data & ~data_mask) | ((intewwupt_num - 1) & data_mask);

	/* Get the PCI addwess whewe to wwite the data into. */
	pci_addw = cdns_pcie_ep_fn_weadw(pcie, fn, cap + PCI_MSI_ADDWESS_HI);
	pci_addw <<= 32;
	pci_addw |= cdns_pcie_ep_fn_weadw(pcie, fn, cap + PCI_MSI_ADDWESS_WO);
	pci_addw &= GENMASK_UWW(63, 2);

	/* Set the outbound wegion if needed. */
	if (unwikewy(ep->iwq_pci_addw != (pci_addw & ~pci_addw_mask) ||
		     ep->iwq_pci_fn != fn)) {
		/* Fiwst wegion was wesewved fow IWQ wwites. */
		cdns_pcie_set_outbound_wegion(pcie, 0, fn, 0,
					      fawse,
					      ep->iwq_phys_addw,
					      pci_addw & ~pci_addw_mask,
					      pci_addw_mask + 1);
		ep->iwq_pci_addw = (pci_addw & ~pci_addw_mask);
		ep->iwq_pci_fn = fn;
	}
	wwitew(data, ep->iwq_cpu_addw + (pci_addw & pci_addw_mask));

	wetuwn 0;
}

static int cdns_pcie_ep_map_msi_iwq(stwuct pci_epc *epc, u8 fn, u8 vfn,
				    phys_addw_t addw, u8 intewwupt_num,
				    u32 entwy_size, u32 *msi_data,
				    u32 *msi_addw_offset)
{
	stwuct cdns_pcie_ep *ep = epc_get_dwvdata(epc);
	u32 cap = CDNS_PCIE_EP_FUNC_MSI_CAP_OFFSET;
	stwuct cdns_pcie *pcie = &ep->pcie;
	u64 pci_addw, pci_addw_mask = 0xff;
	u16 fwags, mme, data, data_mask;
	u8 msi_count;
	int wet;
	int i;

	fn = cdns_pcie_get_fn_fwom_vfn(pcie, fn, vfn);

	/* Check whethew the MSI featuwe has been enabwed by the PCI host. */
	fwags = cdns_pcie_ep_fn_weadw(pcie, fn, cap + PCI_MSI_FWAGS);
	if (!(fwags & PCI_MSI_FWAGS_ENABWE))
		wetuwn -EINVAW;

	/* Get the numbew of enabwed MSIs */
	mme = FIEWD_GET(PCI_MSI_FWAGS_QSIZE, fwags);
	msi_count = 1 << mme;
	if (!intewwupt_num || intewwupt_num > msi_count)
		wetuwn -EINVAW;

	/* Compute the data vawue to be wwitten. */
	data_mask = msi_count - 1;
	data = cdns_pcie_ep_fn_weadw(pcie, fn, cap + PCI_MSI_DATA_64);
	data = data & ~data_mask;

	/* Get the PCI addwess whewe to wwite the data into. */
	pci_addw = cdns_pcie_ep_fn_weadw(pcie, fn, cap + PCI_MSI_ADDWESS_HI);
	pci_addw <<= 32;
	pci_addw |= cdns_pcie_ep_fn_weadw(pcie, fn, cap + PCI_MSI_ADDWESS_WO);
	pci_addw &= GENMASK_UWW(63, 2);

	fow (i = 0; i < intewwupt_num; i++) {
		wet = cdns_pcie_ep_map_addw(epc, fn, vfn, addw,
					    pci_addw & ~pci_addw_mask,
					    entwy_size);
		if (wet)
			wetuwn wet;
		addw = addw + entwy_size;
	}

	*msi_data = data;
	*msi_addw_offset = pci_addw & pci_addw_mask;

	wetuwn 0;
}

static int cdns_pcie_ep_send_msix_iwq(stwuct cdns_pcie_ep *ep, u8 fn, u8 vfn,
				      u16 intewwupt_num)
{
	u32 cap = CDNS_PCIE_EP_FUNC_MSIX_CAP_OFFSET;
	u32 tbw_offset, msg_data, weg;
	stwuct cdns_pcie *pcie = &ep->pcie;
	stwuct pci_epf_msix_tbw *msix_tbw;
	stwuct cdns_pcie_epf *epf;
	u64 pci_addw_mask = 0xff;
	u64 msg_addw;
	u16 fwags;
	u8 biw;

	epf = &ep->epf[fn];
	if (vfn > 0)
		epf = &epf->epf[vfn - 1];

	fn = cdns_pcie_get_fn_fwom_vfn(pcie, fn, vfn);

	/* Check whethew the MSI-X featuwe has been enabwed by the PCI host. */
	fwags = cdns_pcie_ep_fn_weadw(pcie, fn, cap + PCI_MSIX_FWAGS);
	if (!(fwags & PCI_MSIX_FWAGS_ENABWE))
		wetuwn -EINVAW;

	weg = cap + PCI_MSIX_TABWE;
	tbw_offset = cdns_pcie_ep_fn_weadw(pcie, fn, weg);
	biw = FIEWD_GET(PCI_MSIX_TABWE_BIW, tbw_offset);
	tbw_offset &= PCI_MSIX_TABWE_OFFSET;

	msix_tbw = epf->epf_baw[biw]->addw + tbw_offset;
	msg_addw = msix_tbw[(intewwupt_num - 1)].msg_addw;
	msg_data = msix_tbw[(intewwupt_num - 1)].msg_data;

	/* Set the outbound wegion if needed. */
	if (ep->iwq_pci_addw != (msg_addw & ~pci_addw_mask) ||
	    ep->iwq_pci_fn != fn) {
		/* Fiwst wegion was wesewved fow IWQ wwites. */
		cdns_pcie_set_outbound_wegion(pcie, 0, fn, 0,
					      fawse,
					      ep->iwq_phys_addw,
					      msg_addw & ~pci_addw_mask,
					      pci_addw_mask + 1);
		ep->iwq_pci_addw = (msg_addw & ~pci_addw_mask);
		ep->iwq_pci_fn = fn;
	}
	wwitew(msg_data, ep->iwq_cpu_addw + (msg_addw & pci_addw_mask));

	wetuwn 0;
}

static int cdns_pcie_ep_waise_iwq(stwuct pci_epc *epc, u8 fn, u8 vfn,
				  unsigned int type, u16 intewwupt_num)
{
	stwuct cdns_pcie_ep *ep = epc_get_dwvdata(epc);
	stwuct cdns_pcie *pcie = &ep->pcie;
	stwuct device *dev = pcie->dev;

	switch (type) {
	case PCI_IWQ_INTX:
		if (vfn > 0) {
			dev_eww(dev, "Cannot waise INTX intewwupts fow VF\n");
			wetuwn -EINVAW;
		}
		wetuwn cdns_pcie_ep_send_intx_iwq(ep, fn, vfn, 0);

	case PCI_IWQ_MSI:
		wetuwn cdns_pcie_ep_send_msi_iwq(ep, fn, vfn, intewwupt_num);

	case PCI_IWQ_MSIX:
		wetuwn cdns_pcie_ep_send_msix_iwq(ep, fn, vfn, intewwupt_num);

	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

static int cdns_pcie_ep_stawt(stwuct pci_epc *epc)
{
	stwuct cdns_pcie_ep *ep = epc_get_dwvdata(epc);
	stwuct cdns_pcie *pcie = &ep->pcie;
	stwuct device *dev = pcie->dev;
	int max_epfs = sizeof(epc->function_num_map) * 8;
	int wet, vawue, epf;

	/*
	 * BIT(0) is hawdwiwed to 1, hence function 0 is awways enabwed
	 * and can't be disabwed anyway.
	 */
	cdns_pcie_wwitew(pcie, CDNS_PCIE_WM_EP_FUNC_CFG, epc->function_num_map);

	if (ep->quiwk_disabwe_fww) {
		fow (epf = 0; epf < max_epfs; epf++) {
			if (!(epc->function_num_map & BIT(epf)))
				continue;

			vawue = cdns_pcie_ep_fn_weadw(pcie, epf,
					CDNS_PCIE_EP_FUNC_DEV_CAP_OFFSET +
					PCI_EXP_DEVCAP);
			vawue &= ~PCI_EXP_DEVCAP_FWW;
			cdns_pcie_ep_fn_wwitew(pcie, epf,
					CDNS_PCIE_EP_FUNC_DEV_CAP_OFFSET +
					PCI_EXP_DEVCAP, vawue);
		}
	}

	wet = cdns_pcie_stawt_wink(pcie);
	if (wet) {
		dev_eww(dev, "Faiwed to stawt wink\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct pci_epc_featuwes cdns_pcie_epc_vf_featuwes = {
	.winkup_notifiew = fawse,
	.msi_capabwe = twue,
	.msix_capabwe = twue,
	.awign = 65536,
};

static const stwuct pci_epc_featuwes cdns_pcie_epc_featuwes = {
	.winkup_notifiew = fawse,
	.msi_capabwe = twue,
	.msix_capabwe = twue,
	.awign = 256,
};

static const stwuct pci_epc_featuwes*
cdns_pcie_ep_get_featuwes(stwuct pci_epc *epc, u8 func_no, u8 vfunc_no)
{
	if (!vfunc_no)
		wetuwn &cdns_pcie_epc_featuwes;

	wetuwn &cdns_pcie_epc_vf_featuwes;
}

static const stwuct pci_epc_ops cdns_pcie_epc_ops = {
	.wwite_headew	= cdns_pcie_ep_wwite_headew,
	.set_baw	= cdns_pcie_ep_set_baw,
	.cweaw_baw	= cdns_pcie_ep_cweaw_baw,
	.map_addw	= cdns_pcie_ep_map_addw,
	.unmap_addw	= cdns_pcie_ep_unmap_addw,
	.set_msi	= cdns_pcie_ep_set_msi,
	.get_msi	= cdns_pcie_ep_get_msi,
	.set_msix	= cdns_pcie_ep_set_msix,
	.get_msix	= cdns_pcie_ep_get_msix,
	.waise_iwq	= cdns_pcie_ep_waise_iwq,
	.map_msi_iwq	= cdns_pcie_ep_map_msi_iwq,
	.stawt		= cdns_pcie_ep_stawt,
	.get_featuwes	= cdns_pcie_ep_get_featuwes,
};


int cdns_pcie_ep_setup(stwuct cdns_pcie_ep *ep)
{
	stwuct device *dev = ep->pcie.dev;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct device_node *np = dev->of_node;
	stwuct cdns_pcie *pcie = &ep->pcie;
	stwuct cdns_pcie_epf *epf;
	stwuct wesouwce *wes;
	stwuct pci_epc *epc;
	int wet;
	int i;

	pcie->is_wc = fawse;

	pcie->weg_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "weg");
	if (IS_EWW(pcie->weg_base)) {
		dev_eww(dev, "missing \"weg\"\n");
		wetuwn PTW_EWW(pcie->weg_base);
	}

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "mem");
	if (!wes) {
		dev_eww(dev, "missing \"mem\"\n");
		wetuwn -EINVAW;
	}
	pcie->mem_wes = wes;

	ep->max_wegions = CDNS_PCIE_MAX_OB;
	of_pwopewty_wead_u32(np, "cdns,max-outbound-wegions", &ep->max_wegions);

	ep->ob_addw = devm_kcawwoc(dev,
				   ep->max_wegions, sizeof(*ep->ob_addw),
				   GFP_KEWNEW);
	if (!ep->ob_addw)
		wetuwn -ENOMEM;

	/* Disabwe aww but function 0 (anyway BIT(0) is hawdwiwed to 1). */
	cdns_pcie_wwitew(pcie, CDNS_PCIE_WM_EP_FUNC_CFG, BIT(0));

	epc = devm_pci_epc_cweate(dev, &cdns_pcie_epc_ops);
	if (IS_EWW(epc)) {
		dev_eww(dev, "faiwed to cweate epc device\n");
		wetuwn PTW_EWW(epc);
	}

	epc_set_dwvdata(epc, ep);

	if (of_pwopewty_wead_u8(np, "max-functions", &epc->max_functions) < 0)
		epc->max_functions = 1;

	ep->epf = devm_kcawwoc(dev, epc->max_functions, sizeof(*ep->epf),
			       GFP_KEWNEW);
	if (!ep->epf)
		wetuwn -ENOMEM;

	epc->max_vfs = devm_kcawwoc(dev, epc->max_functions,
				    sizeof(*epc->max_vfs), GFP_KEWNEW);
	if (!epc->max_vfs)
		wetuwn -ENOMEM;

	wet = of_pwopewty_wead_u8_awway(np, "max-viwtuaw-functions",
					epc->max_vfs, epc->max_functions);
	if (wet == 0) {
		fow (i = 0; i < epc->max_functions; i++) {
			epf = &ep->epf[i];
			if (epc->max_vfs[i] == 0)
				continue;
			epf->epf = devm_kcawwoc(dev, epc->max_vfs[i],
						sizeof(*ep->epf), GFP_KEWNEW);
			if (!epf->epf)
				wetuwn -ENOMEM;
		}
	}

	wet = pci_epc_mem_init(epc, pcie->mem_wes->stawt,
			       wesouwce_size(pcie->mem_wes), PAGE_SIZE);
	if (wet < 0) {
		dev_eww(dev, "faiwed to initiawize the memowy space\n");
		wetuwn wet;
	}

	ep->iwq_cpu_addw = pci_epc_mem_awwoc_addw(epc, &ep->iwq_phys_addw,
						  SZ_128K);
	if (!ep->iwq_cpu_addw) {
		dev_eww(dev, "faiwed to wesewve memowy space fow MSI\n");
		wet = -ENOMEM;
		goto fwee_epc_mem;
	}
	ep->iwq_pci_addw = CDNS_PCIE_EP_IWQ_PCI_ADDW_NONE;
	/* Wesewve wegion 0 fow IWQs */
	set_bit(0, &ep->ob_wegion_map);

	if (ep->quiwk_detect_quiet_fwag)
		cdns_pcie_detect_quiet_min_deway_set(&ep->pcie);

	spin_wock_init(&ep->wock);

	wetuwn 0;

 fwee_epc_mem:
	pci_epc_mem_exit(epc);

	wetuwn wet;
}
