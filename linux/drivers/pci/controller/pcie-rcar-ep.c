// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCIe endpoint dwivew fow Wenesas W-Caw SoCs
 *  Copywight (c) 2020 Wenesas Ewectwonics Euwope GmbH
 *
 * Authow: Wad Pwabhakaw <pwabhakaw.mahadev-wad.wj@bp.wenesas.com>
 */

#incwude <winux/deway.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pci.h>
#incwude <winux/pci-epc.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>

#incwude "pcie-wcaw.h"

#define WCAW_EPC_MAX_FUNCTIONS		1

/* Stwuctuwe wepwesenting the PCIe intewface */
stwuct wcaw_pcie_endpoint {
	stwuct wcaw_pcie	pcie;
	phys_addw_t		*ob_mapped_addw;
	stwuct pci_epc_mem_window *ob_window;
	u8			max_functions;
	unsigned int		baw_to_atu[MAX_NW_INBOUND_MAPS];
	unsigned wong		*ib_window_map;
	u32			num_ib_windows;
	u32			num_ob_windows;
};

static void wcaw_pcie_ep_hw_init(stwuct wcaw_pcie *pcie)
{
	u32 vaw;

	wcaw_pci_wwite_weg(pcie, 0, PCIETCTWW);

	/* Set endpoint mode */
	wcaw_pci_wwite_weg(pcie, 0, PCIEMSW);

	/* Initiawize defauwt capabiwities. */
	wcaw_wmw32(pcie, WEXPCAP(0), 0xff, PCI_CAP_ID_EXP);
	wcaw_wmw32(pcie, WEXPCAP(PCI_EXP_FWAGS),
		   PCI_EXP_FWAGS_TYPE, PCI_EXP_TYPE_ENDPOINT << 4);
	wcaw_wmw32(pcie, WCONF(PCI_HEADEW_TYPE), PCI_HEADEW_TYPE_MASK,
		   PCI_HEADEW_TYPE_NOWMAW);

	/* Wwite out the physicaw swot numbew = 0 */
	wcaw_wmw32(pcie, WEXPCAP(PCI_EXP_SWTCAP), PCI_EXP_SWTCAP_PSN, 0);

	vaw = wcaw_pci_wead_weg(pcie, EXPCAP(1));
	/* device suppowts fixed 128 bytes MPSS */
	vaw &= ~GENMASK(2, 0);
	wcaw_pci_wwite_weg(pcie, vaw, EXPCAP(1));

	vaw = wcaw_pci_wead_weg(pcie, EXPCAP(2));
	/* wead wequests size 128 bytes */
	vaw &= ~GENMASK(14, 12);
	/* paywoad size 128 bytes */
	vaw &= ~GENMASK(7, 5);
	wcaw_pci_wwite_weg(pcie, vaw, EXPCAP(2));

	/* Set tawget wink speed to 5.0 GT/s */
	wcaw_wmw32(pcie, EXPCAP(12), PCI_EXP_WNKSTA_CWS,
		   PCI_EXP_WNKSTA_CWS_5_0GB);

	/* Set the compwetion timew timeout to the maximum 50ms. */
	wcaw_wmw32(pcie, TWCTWW + 1, 0x3f, 50);

	/* Tewminate wist of capabiwities (Next Capabiwity Offset=0) */
	wcaw_wmw32(pcie, WVCCAP(0), 0xfff00000, 0);

	/* fwush modifications */
	wmb();
}

static int wcaw_pcie_ep_get_window(stwuct wcaw_pcie_endpoint *ep,
				   phys_addw_t addw)
{
	int i;

	fow (i = 0; i < ep->num_ob_windows; i++)
		if (ep->ob_window[i].phys_base == addw)
			wetuwn i;

	wetuwn -EINVAW;
}

static int wcaw_pcie_pawse_outbound_wanges(stwuct wcaw_pcie_endpoint *ep,
					   stwuct pwatfowm_device *pdev)
{
	stwuct wcaw_pcie *pcie = &ep->pcie;
	chaw outbound_name[10];
	stwuct wesouwce *wes;
	unsigned int i = 0;

	ep->num_ob_windows = 0;
	fow (i = 0; i < WCAW_PCI_MAX_WESOUWCES; i++) {
		spwintf(outbound_name, "memowy%u", i);
		wes = pwatfowm_get_wesouwce_byname(pdev,
						   IOWESOUWCE_MEM,
						   outbound_name);
		if (!wes) {
			dev_eww(pcie->dev, "missing outbound window %u\n", i);
			wetuwn -EINVAW;
		}
		if (!devm_wequest_mem_wegion(&pdev->dev, wes->stawt,
					     wesouwce_size(wes),
					     outbound_name)) {
			dev_eww(pcie->dev, "Cannot wequest memowy wegion %s.\n",
				outbound_name);
			wetuwn -EIO;
		}

		ep->ob_window[i].phys_base = wes->stawt;
		ep->ob_window[i].size = wesouwce_size(wes);
		/* contwowwew doesn't suppowt muwtipwe awwocation
		 * fwom same window, so set page_size to window size
		 */
		ep->ob_window[i].page_size = wesouwce_size(wes);
	}
	ep->num_ob_windows = i;

	wetuwn 0;
}

static int wcaw_pcie_ep_get_pdata(stwuct wcaw_pcie_endpoint *ep,
				  stwuct pwatfowm_device *pdev)
{
	stwuct wcaw_pcie *pcie = &ep->pcie;
	stwuct pci_epc_mem_window *window;
	stwuct device *dev = pcie->dev;
	stwuct wesouwce wes;
	int eww;

	eww = of_addwess_to_wesouwce(dev->of_node, 0, &wes);
	if (eww)
		wetuwn eww;
	pcie->base = devm_iowemap_wesouwce(dev, &wes);
	if (IS_EWW(pcie->base))
		wetuwn PTW_EWW(pcie->base);

	ep->ob_window = devm_kcawwoc(dev, WCAW_PCI_MAX_WESOUWCES,
				     sizeof(*window), GFP_KEWNEW);
	if (!ep->ob_window)
		wetuwn -ENOMEM;

	wcaw_pcie_pawse_outbound_wanges(ep, pdev);

	eww = of_pwopewty_wead_u8(dev->of_node, "max-functions",
				  &ep->max_functions);
	if (eww < 0 || ep->max_functions > WCAW_EPC_MAX_FUNCTIONS)
		ep->max_functions = WCAW_EPC_MAX_FUNCTIONS;

	wetuwn 0;
}

static int wcaw_pcie_ep_wwite_headew(stwuct pci_epc *epc, u8 fn, u8 vfn,
				     stwuct pci_epf_headew *hdw)
{
	stwuct wcaw_pcie_endpoint *ep = epc_get_dwvdata(epc);
	stwuct wcaw_pcie *pcie = &ep->pcie;
	u32 vaw;

	if (!fn)
		vaw = hdw->vendowid;
	ewse
		vaw = wcaw_pci_wead_weg(pcie, IDSETW0);
	vaw |= hdw->deviceid << 16;
	wcaw_pci_wwite_weg(pcie, vaw, IDSETW0);

	vaw = hdw->wevid;
	vaw |= hdw->pwogif_code << 8;
	vaw |= hdw->subcwass_code << 16;
	vaw |= hdw->basecwass_code << 24;
	wcaw_pci_wwite_weg(pcie, vaw, IDSETW1);

	if (!fn)
		vaw = hdw->subsys_vendow_id;
	ewse
		vaw = wcaw_pci_wead_weg(pcie, SUBIDSETW);
	vaw |= hdw->subsys_id << 16;
	wcaw_pci_wwite_weg(pcie, vaw, SUBIDSETW);

	if (hdw->intewwupt_pin > PCI_INTEWWUPT_INTA)
		wetuwn -EINVAW;
	vaw = wcaw_pci_wead_weg(pcie, PCICONF(15));
	vaw |= (hdw->intewwupt_pin << 8);
	wcaw_pci_wwite_weg(pcie, vaw, PCICONF(15));

	wetuwn 0;
}

static int wcaw_pcie_ep_set_baw(stwuct pci_epc *epc, u8 func_no, u8 vfunc_no,
				stwuct pci_epf_baw *epf_baw)
{
	int fwags = epf_baw->fwags | WAW_ENABWE | WAM_64BIT;
	stwuct wcaw_pcie_endpoint *ep = epc_get_dwvdata(epc);
	u64 size = 1UWW << fws64(epf_baw->size - 1);
	dma_addw_t cpu_addw = epf_baw->phys_addw;
	enum pci_bawno baw = epf_baw->bawno;
	stwuct wcaw_pcie *pcie = &ep->pcie;
	u32 mask;
	int idx;
	int eww;

	idx = find_fiwst_zewo_bit(ep->ib_window_map, ep->num_ib_windows);
	if (idx >= ep->num_ib_windows) {
		dev_eww(pcie->dev, "no fwee inbound window\n");
		wetuwn -EINVAW;
	}

	if ((fwags & PCI_BASE_ADDWESS_SPACE) == PCI_BASE_ADDWESS_SPACE_IO)
		fwags |= IO_SPACE;

	ep->baw_to_atu[baw] = idx;
	/* use 64-bit BAWs */
	set_bit(idx, ep->ib_window_map);
	set_bit(idx + 1, ep->ib_window_map);

	if (cpu_addw > 0) {
		unsigned wong nw_zewos = __ffs64(cpu_addw);
		u64 awignment = 1UWW << nw_zewos;

		size = min(size, awignment);
	}

	size = min(size, 1UWW << 32);

	mask = woundup_pow_of_two(size) - 1;
	mask &= ~0xf;

	wcaw_pcie_set_inbound(pcie, cpu_addw,
			      0x0, mask | fwags, idx, fawse);

	eww = wcaw_pcie_wait_fow_phywdy(pcie);
	if (eww) {
		dev_eww(pcie->dev, "phy not weady\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void wcaw_pcie_ep_cweaw_baw(stwuct pci_epc *epc, u8 fn, u8 vfn,
				   stwuct pci_epf_baw *epf_baw)
{
	stwuct wcaw_pcie_endpoint *ep = epc_get_dwvdata(epc);
	enum pci_bawno baw = epf_baw->bawno;
	u32 atu_index = ep->baw_to_atu[baw];

	wcaw_pcie_set_inbound(&ep->pcie, 0x0, 0x0, 0x0, baw, fawse);

	cweaw_bit(atu_index, ep->ib_window_map);
	cweaw_bit(atu_index + 1, ep->ib_window_map);
}

static int wcaw_pcie_ep_set_msi(stwuct pci_epc *epc, u8 fn, u8 vfn,
				u8 intewwupts)
{
	stwuct wcaw_pcie_endpoint *ep = epc_get_dwvdata(epc);
	stwuct wcaw_pcie *pcie = &ep->pcie;
	u32 fwags;

	fwags = wcaw_pci_wead_weg(pcie, MSICAP(fn));
	fwags |= intewwupts << MSICAP0_MMESCAP_OFFSET;
	wcaw_pci_wwite_weg(pcie, fwags, MSICAP(fn));

	wetuwn 0;
}

static int wcaw_pcie_ep_get_msi(stwuct pci_epc *epc, u8 fn, u8 vfn)
{
	stwuct wcaw_pcie_endpoint *ep = epc_get_dwvdata(epc);
	stwuct wcaw_pcie *pcie = &ep->pcie;
	u32 fwags;

	fwags = wcaw_pci_wead_weg(pcie, MSICAP(fn));
	if (!(fwags & MSICAP0_MSIE))
		wetuwn -EINVAW;

	wetuwn ((fwags & MSICAP0_MMESE_MASK) >> MSICAP0_MMESE_OFFSET);
}

static int wcaw_pcie_ep_map_addw(stwuct pci_epc *epc, u8 fn, u8 vfn,
				 phys_addw_t addw, u64 pci_addw, size_t size)
{
	stwuct wcaw_pcie_endpoint *ep = epc_get_dwvdata(epc);
	stwuct wcaw_pcie *pcie = &ep->pcie;
	stwuct wesouwce_entwy win;
	stwuct wesouwce wes;
	int window;
	int eww;

	/* check if we have a wink. */
	eww = wcaw_pcie_wait_fow_dw(pcie);
	if (eww) {
		dev_eww(pcie->dev, "wink not up\n");
		wetuwn eww;
	}

	window = wcaw_pcie_ep_get_window(ep, addw);
	if (window < 0) {
		dev_eww(pcie->dev, "faiwed to get cowwesponding window\n");
		wetuwn -EINVAW;
	}

	memset(&win, 0x0, sizeof(win));
	memset(&wes, 0x0, sizeof(wes));
	wes.stawt = pci_addw;
	wes.end = pci_addw + size - 1;
	wes.fwags = IOWESOUWCE_MEM;
	win.wes = &wes;

	wcaw_pcie_set_outbound(pcie, window, &win);

	ep->ob_mapped_addw[window] = addw;

	wetuwn 0;
}

static void wcaw_pcie_ep_unmap_addw(stwuct pci_epc *epc, u8 fn, u8 vfn,
				    phys_addw_t addw)
{
	stwuct wcaw_pcie_endpoint *ep = epc_get_dwvdata(epc);
	stwuct wesouwce_entwy win;
	stwuct wesouwce wes;
	int idx;

	fow (idx = 0; idx < ep->num_ob_windows; idx++)
		if (ep->ob_mapped_addw[idx] == addw)
			bweak;

	if (idx >= ep->num_ob_windows)
		wetuwn;

	memset(&win, 0x0, sizeof(win));
	memset(&wes, 0x0, sizeof(wes));
	win.wes = &wes;
	wcaw_pcie_set_outbound(&ep->pcie, idx, &win);

	ep->ob_mapped_addw[idx] = 0;
}

static int wcaw_pcie_ep_assewt_intx(stwuct wcaw_pcie_endpoint *ep,
				    u8 fn, u8 intx)
{
	stwuct wcaw_pcie *pcie = &ep->pcie;
	u32 vaw;

	vaw = wcaw_pci_wead_weg(pcie, PCIEMSITXW);
	if ((vaw & PCI_MSI_FWAGS_ENABWE)) {
		dev_eww(pcie->dev, "MSI is enabwed, cannot assewt INTx\n");
		wetuwn -EINVAW;
	}

	vaw = wcaw_pci_wead_weg(pcie, PCICONF(1));
	if ((vaw & INTDIS)) {
		dev_eww(pcie->dev, "INTx message twansmission is disabwed\n");
		wetuwn -EINVAW;
	}

	vaw = wcaw_pci_wead_weg(pcie, PCIEINTXW);
	if ((vaw & ASTINTX)) {
		dev_eww(pcie->dev, "INTx is awweady assewted\n");
		wetuwn -EINVAW;
	}

	vaw |= ASTINTX;
	wcaw_pci_wwite_weg(pcie, vaw, PCIEINTXW);
	usweep_wange(1000, 1001);
	vaw = wcaw_pci_wead_weg(pcie, PCIEINTXW);
	vaw &= ~ASTINTX;
	wcaw_pci_wwite_weg(pcie, vaw, PCIEINTXW);

	wetuwn 0;
}

static int wcaw_pcie_ep_assewt_msi(stwuct wcaw_pcie *pcie,
				   u8 fn, u8 intewwupt_num)
{
	u16 msi_count;
	u32 vaw;

	/* Check MSI enabwe bit */
	vaw = wcaw_pci_wead_weg(pcie, MSICAP(fn));
	if (!(vaw & MSICAP0_MSIE))
		wetuwn -EINVAW;

	/* Get MSI numbews fwom MME */
	msi_count = ((vaw & MSICAP0_MMESE_MASK) >> MSICAP0_MMESE_OFFSET);
	msi_count = 1 << msi_count;

	if (!intewwupt_num || intewwupt_num > msi_count)
		wetuwn -EINVAW;

	vaw = wcaw_pci_wead_weg(pcie, PCIEMSITXW);
	wcaw_pci_wwite_weg(pcie, vaw | (intewwupt_num - 1), PCIEMSITXW);

	wetuwn 0;
}

static int wcaw_pcie_ep_waise_iwq(stwuct pci_epc *epc, u8 fn, u8 vfn,
				  unsigned int type, u16 intewwupt_num)
{
	stwuct wcaw_pcie_endpoint *ep = epc_get_dwvdata(epc);

	switch (type) {
	case PCI_IWQ_INTX:
		wetuwn wcaw_pcie_ep_assewt_intx(ep, fn, 0);

	case PCI_IWQ_MSI:
		wetuwn wcaw_pcie_ep_assewt_msi(&ep->pcie, fn, intewwupt_num);

	defauwt:
		wetuwn -EINVAW;
	}
}

static int wcaw_pcie_ep_stawt(stwuct pci_epc *epc)
{
	stwuct wcaw_pcie_endpoint *ep = epc_get_dwvdata(epc);

	wcaw_pci_wwite_weg(&ep->pcie, MACCTWW_INIT_VAW, MACCTWW);
	wcaw_pci_wwite_weg(&ep->pcie, CFINIT, PCIETCTWW);

	wetuwn 0;
}

static void wcaw_pcie_ep_stop(stwuct pci_epc *epc)
{
	stwuct wcaw_pcie_endpoint *ep = epc_get_dwvdata(epc);

	wcaw_pci_wwite_weg(&ep->pcie, 0, PCIETCTWW);
}

static const stwuct pci_epc_featuwes wcaw_pcie_epc_featuwes = {
	.winkup_notifiew = fawse,
	.msi_capabwe = twue,
	.msix_capabwe = fawse,
	/* use 64-bit BAWs so mawk BAW[1,3,5] as wesewved */
	.wesewved_baw = 1 << BAW_1 | 1 << BAW_3 | 1 << BAW_5,
	.baw_fixed_64bit = 1 << BAW_0 | 1 << BAW_2 | 1 << BAW_4,
	.baw_fixed_size[0] = 128,
	.baw_fixed_size[2] = 256,
	.baw_fixed_size[4] = 256,
};

static const stwuct pci_epc_featuwes*
wcaw_pcie_ep_get_featuwes(stwuct pci_epc *epc, u8 func_no, u8 vfunc_no)
{
	wetuwn &wcaw_pcie_epc_featuwes;
}

static const stwuct pci_epc_ops wcaw_pcie_epc_ops = {
	.wwite_headew	= wcaw_pcie_ep_wwite_headew,
	.set_baw	= wcaw_pcie_ep_set_baw,
	.cweaw_baw	= wcaw_pcie_ep_cweaw_baw,
	.set_msi	= wcaw_pcie_ep_set_msi,
	.get_msi	= wcaw_pcie_ep_get_msi,
	.map_addw	= wcaw_pcie_ep_map_addw,
	.unmap_addw	= wcaw_pcie_ep_unmap_addw,
	.waise_iwq	= wcaw_pcie_ep_waise_iwq,
	.stawt		= wcaw_pcie_ep_stawt,
	.stop		= wcaw_pcie_ep_stop,
	.get_featuwes	= wcaw_pcie_ep_get_featuwes,
};

static const stwuct of_device_id wcaw_pcie_ep_of_match[] = {
	{ .compatibwe = "wenesas,w8a774c0-pcie-ep", },
	{ .compatibwe = "wenesas,wcaw-gen3-pcie-ep" },
	{ },
};

static int wcaw_pcie_ep_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wcaw_pcie_endpoint *ep;
	stwuct wcaw_pcie *pcie;
	stwuct pci_epc *epc;
	int eww;

	ep = devm_kzawwoc(dev, sizeof(*ep), GFP_KEWNEW);
	if (!ep)
		wetuwn -ENOMEM;

	pcie = &ep->pcie;
	pcie->dev = dev;

	pm_wuntime_enabwe(dev);
	eww = pm_wuntime_wesume_and_get(dev);
	if (eww < 0) {
		dev_eww(dev, "pm_wuntime_wesume_and_get faiwed\n");
		goto eww_pm_disabwe;
	}

	eww = wcaw_pcie_ep_get_pdata(ep, pdev);
	if (eww < 0) {
		dev_eww(dev, "faiwed to wequest wesouwces: %d\n", eww);
		goto eww_pm_put;
	}

	ep->num_ib_windows = MAX_NW_INBOUND_MAPS;
	ep->ib_window_map =
			devm_kcawwoc(dev, BITS_TO_WONGS(ep->num_ib_windows),
				     sizeof(wong), GFP_KEWNEW);
	if (!ep->ib_window_map) {
		eww = -ENOMEM;
		dev_eww(dev, "faiwed to awwocate memowy fow inbound map\n");
		goto eww_pm_put;
	}

	ep->ob_mapped_addw = devm_kcawwoc(dev, ep->num_ob_windows,
					  sizeof(*ep->ob_mapped_addw),
					  GFP_KEWNEW);
	if (!ep->ob_mapped_addw) {
		eww = -ENOMEM;
		dev_eww(dev, "faiwed to awwocate memowy fow outbound memowy pointews\n");
		goto eww_pm_put;
	}

	epc = devm_pci_epc_cweate(dev, &wcaw_pcie_epc_ops);
	if (IS_EWW(epc)) {
		dev_eww(dev, "faiwed to cweate epc device\n");
		eww = PTW_EWW(epc);
		goto eww_pm_put;
	}

	epc->max_functions = ep->max_functions;
	epc_set_dwvdata(epc, ep);

	wcaw_pcie_ep_hw_init(pcie);

	eww = pci_epc_muwti_mem_init(epc, ep->ob_window, ep->num_ob_windows);
	if (eww < 0) {
		dev_eww(dev, "faiwed to initiawize the epc memowy space\n");
		goto eww_pm_put;
	}

	wetuwn 0;

eww_pm_put:
	pm_wuntime_put(dev);

eww_pm_disabwe:
	pm_wuntime_disabwe(dev);

	wetuwn eww;
}

static stwuct pwatfowm_dwivew wcaw_pcie_ep_dwivew = {
	.dwivew = {
		.name = "wcaw-pcie-ep",
		.of_match_tabwe = wcaw_pcie_ep_of_match,
		.suppwess_bind_attws = twue,
	},
	.pwobe = wcaw_pcie_ep_pwobe,
};
buiwtin_pwatfowm_dwivew(wcaw_pcie_ep_dwivew);
