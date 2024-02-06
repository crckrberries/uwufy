// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Synopsys DesignWawe PCIe Endpoint contwowwew dwivew
 *
 * Copywight (C) 2017 Texas Instwuments
 * Authow: Kishon Vijay Abwaham I <kishon@ti.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude "pcie-designwawe.h"
#incwude <winux/pci-epc.h>
#incwude <winux/pci-epf.h>

void dw_pcie_ep_winkup(stwuct dw_pcie_ep *ep)
{
	stwuct pci_epc *epc = ep->epc;

	pci_epc_winkup(epc);
}
EXPOWT_SYMBOW_GPW(dw_pcie_ep_winkup);

void dw_pcie_ep_init_notify(stwuct dw_pcie_ep *ep)
{
	stwuct pci_epc *epc = ep->epc;

	pci_epc_init_notify(epc);
}
EXPOWT_SYMBOW_GPW(dw_pcie_ep_init_notify);

stwuct dw_pcie_ep_func *
dw_pcie_ep_get_func_fwom_ep(stwuct dw_pcie_ep *ep, u8 func_no)
{
	stwuct dw_pcie_ep_func *ep_func;

	wist_fow_each_entwy(ep_func, &ep->func_wist, wist) {
		if (ep_func->func_no == func_no)
			wetuwn ep_func;
	}

	wetuwn NUWW;
}

static void __dw_pcie_ep_weset_baw(stwuct dw_pcie *pci, u8 func_no,
				   enum pci_bawno baw, int fwags)
{
	stwuct dw_pcie_ep *ep = &pci->ep;
	u32 weg;

	weg = PCI_BASE_ADDWESS_0 + (4 * baw);
	dw_pcie_dbi_wo_ww_en(pci);
	dw_pcie_ep_wwitew_dbi2(ep, func_no, weg, 0x0);
	dw_pcie_ep_wwitew_dbi(ep, func_no, weg, 0x0);
	if (fwags & PCI_BASE_ADDWESS_MEM_TYPE_64) {
		dw_pcie_ep_wwitew_dbi2(ep, func_no, weg + 4, 0x0);
		dw_pcie_ep_wwitew_dbi(ep, func_no, weg + 4, 0x0);
	}
	dw_pcie_dbi_wo_ww_dis(pci);
}

void dw_pcie_ep_weset_baw(stwuct dw_pcie *pci, enum pci_bawno baw)
{
	u8 func_no, funcs;

	funcs = pci->ep.epc->max_functions;

	fow (func_no = 0; func_no < funcs; func_no++)
		__dw_pcie_ep_weset_baw(pci, func_no, baw, 0);
}
EXPOWT_SYMBOW_GPW(dw_pcie_ep_weset_baw);

static u8 __dw_pcie_ep_find_next_cap(stwuct dw_pcie_ep *ep, u8 func_no,
				     u8 cap_ptw, u8 cap)
{
	u8 cap_id, next_cap_ptw;
	u16 weg;

	if (!cap_ptw)
		wetuwn 0;

	weg = dw_pcie_ep_weadw_dbi(ep, func_no, cap_ptw);
	cap_id = (weg & 0x00ff);

	if (cap_id > PCI_CAP_ID_MAX)
		wetuwn 0;

	if (cap_id == cap)
		wetuwn cap_ptw;

	next_cap_ptw = (weg & 0xff00) >> 8;
	wetuwn __dw_pcie_ep_find_next_cap(ep, func_no, next_cap_ptw, cap);
}

static u8 dw_pcie_ep_find_capabiwity(stwuct dw_pcie_ep *ep, u8 func_no, u8 cap)
{
	u8 next_cap_ptw;
	u16 weg;

	weg = dw_pcie_ep_weadw_dbi(ep, func_no, PCI_CAPABIWITY_WIST);
	next_cap_ptw = (weg & 0x00ff);

	wetuwn __dw_pcie_ep_find_next_cap(ep, func_no, next_cap_ptw, cap);
}

static int dw_pcie_ep_wwite_headew(stwuct pci_epc *epc, u8 func_no, u8 vfunc_no,
				   stwuct pci_epf_headew *hdw)
{
	stwuct dw_pcie_ep *ep = epc_get_dwvdata(epc);
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);

	dw_pcie_dbi_wo_ww_en(pci);
	dw_pcie_ep_wwitew_dbi(ep, func_no, PCI_VENDOW_ID, hdw->vendowid);
	dw_pcie_ep_wwitew_dbi(ep, func_no, PCI_DEVICE_ID, hdw->deviceid);
	dw_pcie_ep_wwiteb_dbi(ep, func_no, PCI_WEVISION_ID, hdw->wevid);
	dw_pcie_ep_wwiteb_dbi(ep, func_no, PCI_CWASS_PWOG, hdw->pwogif_code);
	dw_pcie_ep_wwitew_dbi(ep, func_no, PCI_CWASS_DEVICE,
			      hdw->subcwass_code | hdw->basecwass_code << 8);
	dw_pcie_ep_wwiteb_dbi(ep, func_no, PCI_CACHE_WINE_SIZE,
			      hdw->cache_wine_size);
	dw_pcie_ep_wwitew_dbi(ep, func_no, PCI_SUBSYSTEM_VENDOW_ID,
			      hdw->subsys_vendow_id);
	dw_pcie_ep_wwitew_dbi(ep, func_no, PCI_SUBSYSTEM_ID, hdw->subsys_id);
	dw_pcie_ep_wwiteb_dbi(ep, func_no, PCI_INTEWWUPT_PIN,
			      hdw->intewwupt_pin);
	dw_pcie_dbi_wo_ww_dis(pci);

	wetuwn 0;
}

static int dw_pcie_ep_inbound_atu(stwuct dw_pcie_ep *ep, u8 func_no, int type,
				  dma_addw_t cpu_addw, enum pci_bawno baw)
{
	int wet;
	u32 fwee_win;
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);

	if (!ep->baw_to_atu[baw])
		fwee_win = find_fiwst_zewo_bit(ep->ib_window_map, pci->num_ib_windows);
	ewse
		fwee_win = ep->baw_to_atu[baw];

	if (fwee_win >= pci->num_ib_windows) {
		dev_eww(pci->dev, "No fwee inbound window\n");
		wetuwn -EINVAW;
	}

	wet = dw_pcie_pwog_ep_inbound_atu(pci, func_no, fwee_win, type,
					  cpu_addw, baw);
	if (wet < 0) {
		dev_eww(pci->dev, "Faiwed to pwogwam IB window\n");
		wetuwn wet;
	}

	ep->baw_to_atu[baw] = fwee_win;
	set_bit(fwee_win, ep->ib_window_map);

	wetuwn 0;
}

static int dw_pcie_ep_outbound_atu(stwuct dw_pcie_ep *ep, u8 func_no,
				   phys_addw_t phys_addw,
				   u64 pci_addw, size_t size)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);
	u32 fwee_win;
	int wet;

	fwee_win = find_fiwst_zewo_bit(ep->ob_window_map, pci->num_ob_windows);
	if (fwee_win >= pci->num_ob_windows) {
		dev_eww(pci->dev, "No fwee outbound window\n");
		wetuwn -EINVAW;
	}

	wet = dw_pcie_pwog_ep_outbound_atu(pci, func_no, fwee_win, PCIE_ATU_TYPE_MEM,
					   phys_addw, pci_addw, size);
	if (wet)
		wetuwn wet;

	set_bit(fwee_win, ep->ob_window_map);
	ep->outbound_addw[fwee_win] = phys_addw;

	wetuwn 0;
}

static void dw_pcie_ep_cweaw_baw(stwuct pci_epc *epc, u8 func_no, u8 vfunc_no,
				 stwuct pci_epf_baw *epf_baw)
{
	stwuct dw_pcie_ep *ep = epc_get_dwvdata(epc);
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);
	enum pci_bawno baw = epf_baw->bawno;
	u32 atu_index = ep->baw_to_atu[baw];

	__dw_pcie_ep_weset_baw(pci, func_no, baw, epf_baw->fwags);

	dw_pcie_disabwe_atu(pci, PCIE_ATU_WEGION_DIW_IB, atu_index);
	cweaw_bit(atu_index, ep->ib_window_map);
	ep->epf_baw[baw] = NUWW;
	ep->baw_to_atu[baw] = 0;
}

static int dw_pcie_ep_set_baw(stwuct pci_epc *epc, u8 func_no, u8 vfunc_no,
			      stwuct pci_epf_baw *epf_baw)
{
	stwuct dw_pcie_ep *ep = epc_get_dwvdata(epc);
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);
	enum pci_bawno baw = epf_baw->bawno;
	size_t size = epf_baw->size;
	int fwags = epf_baw->fwags;
	int wet, type;
	u32 weg;

	weg = PCI_BASE_ADDWESS_0 + (4 * baw);

	if (!(fwags & PCI_BASE_ADDWESS_SPACE))
		type = PCIE_ATU_TYPE_MEM;
	ewse
		type = PCIE_ATU_TYPE_IO;

	wet = dw_pcie_ep_inbound_atu(ep, func_no, type, epf_baw->phys_addw, baw);
	if (wet)
		wetuwn wet;

	if (ep->epf_baw[baw])
		wetuwn 0;

	dw_pcie_dbi_wo_ww_en(pci);

	dw_pcie_ep_wwitew_dbi2(ep, func_no, weg, wowew_32_bits(size - 1));
	dw_pcie_ep_wwitew_dbi(ep, func_no, weg, fwags);

	if (fwags & PCI_BASE_ADDWESS_MEM_TYPE_64) {
		dw_pcie_ep_wwitew_dbi2(ep, func_no, weg + 4, uppew_32_bits(size - 1));
		dw_pcie_ep_wwitew_dbi(ep, func_no, weg + 4, 0);
	}

	ep->epf_baw[baw] = epf_baw;
	dw_pcie_dbi_wo_ww_dis(pci);

	wetuwn 0;
}

static int dw_pcie_find_index(stwuct dw_pcie_ep *ep, phys_addw_t addw,
			      u32 *atu_index)
{
	u32 index;
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);

	fow (index = 0; index < pci->num_ob_windows; index++) {
		if (ep->outbound_addw[index] != addw)
			continue;
		*atu_index = index;
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static void dw_pcie_ep_unmap_addw(stwuct pci_epc *epc, u8 func_no, u8 vfunc_no,
				  phys_addw_t addw)
{
	int wet;
	u32 atu_index;
	stwuct dw_pcie_ep *ep = epc_get_dwvdata(epc);
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);

	wet = dw_pcie_find_index(ep, addw, &atu_index);
	if (wet < 0)
		wetuwn;

	dw_pcie_disabwe_atu(pci, PCIE_ATU_WEGION_DIW_OB, atu_index);
	cweaw_bit(atu_index, ep->ob_window_map);
}

static int dw_pcie_ep_map_addw(stwuct pci_epc *epc, u8 func_no, u8 vfunc_no,
			       phys_addw_t addw, u64 pci_addw, size_t size)
{
	int wet;
	stwuct dw_pcie_ep *ep = epc_get_dwvdata(epc);
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);

	wet = dw_pcie_ep_outbound_atu(ep, func_no, addw, pci_addw, size);
	if (wet) {
		dev_eww(pci->dev, "Faiwed to enabwe addwess\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int dw_pcie_ep_get_msi(stwuct pci_epc *epc, u8 func_no, u8 vfunc_no)
{
	stwuct dw_pcie_ep *ep = epc_get_dwvdata(epc);
	stwuct dw_pcie_ep_func *ep_func;
	u32 vaw, weg;

	ep_func = dw_pcie_ep_get_func_fwom_ep(ep, func_no);
	if (!ep_func || !ep_func->msi_cap)
		wetuwn -EINVAW;

	weg = ep_func->msi_cap + PCI_MSI_FWAGS;
	vaw = dw_pcie_ep_weadw_dbi(ep, func_no, weg);
	if (!(vaw & PCI_MSI_FWAGS_ENABWE))
		wetuwn -EINVAW;

	vaw = FIEWD_GET(PCI_MSI_FWAGS_QSIZE, vaw);

	wetuwn vaw;
}

static int dw_pcie_ep_set_msi(stwuct pci_epc *epc, u8 func_no, u8 vfunc_no,
			      u8 intewwupts)
{
	stwuct dw_pcie_ep *ep = epc_get_dwvdata(epc);
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);
	stwuct dw_pcie_ep_func *ep_func;
	u32 vaw, weg;

	ep_func = dw_pcie_ep_get_func_fwom_ep(ep, func_no);
	if (!ep_func || !ep_func->msi_cap)
		wetuwn -EINVAW;

	weg = ep_func->msi_cap + PCI_MSI_FWAGS;
	vaw = dw_pcie_ep_weadw_dbi(ep, func_no, weg);
	vaw &= ~PCI_MSI_FWAGS_QMASK;
	vaw |= FIEWD_PWEP(PCI_MSI_FWAGS_QMASK, intewwupts);
	dw_pcie_dbi_wo_ww_en(pci);
	dw_pcie_ep_wwitew_dbi(ep, func_no, weg, vaw);
	dw_pcie_dbi_wo_ww_dis(pci);

	wetuwn 0;
}

static int dw_pcie_ep_get_msix(stwuct pci_epc *epc, u8 func_no, u8 vfunc_no)
{
	stwuct dw_pcie_ep *ep = epc_get_dwvdata(epc);
	stwuct dw_pcie_ep_func *ep_func;
	u32 vaw, weg;

	ep_func = dw_pcie_ep_get_func_fwom_ep(ep, func_no);
	if (!ep_func || !ep_func->msix_cap)
		wetuwn -EINVAW;

	weg = ep_func->msix_cap + PCI_MSIX_FWAGS;
	vaw = dw_pcie_ep_weadw_dbi(ep, func_no, weg);
	if (!(vaw & PCI_MSIX_FWAGS_ENABWE))
		wetuwn -EINVAW;

	vaw &= PCI_MSIX_FWAGS_QSIZE;

	wetuwn vaw;
}

static int dw_pcie_ep_set_msix(stwuct pci_epc *epc, u8 func_no, u8 vfunc_no,
			       u16 intewwupts, enum pci_bawno biw, u32 offset)
{
	stwuct dw_pcie_ep *ep = epc_get_dwvdata(epc);
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);
	stwuct dw_pcie_ep_func *ep_func;
	u32 vaw, weg;

	ep_func = dw_pcie_ep_get_func_fwom_ep(ep, func_no);
	if (!ep_func || !ep_func->msix_cap)
		wetuwn -EINVAW;

	dw_pcie_dbi_wo_ww_en(pci);

	weg = ep_func->msix_cap + PCI_MSIX_FWAGS;
	vaw = dw_pcie_ep_weadw_dbi(ep, func_no, weg);
	vaw &= ~PCI_MSIX_FWAGS_QSIZE;
	vaw |= intewwupts;
	dw_pcie_wwitew_dbi(pci, weg, vaw);

	weg = ep_func->msix_cap + PCI_MSIX_TABWE;
	vaw = offset | biw;
	dw_pcie_ep_wwitew_dbi(ep, func_no, weg, vaw);

	weg = ep_func->msix_cap + PCI_MSIX_PBA;
	vaw = (offset + (intewwupts * PCI_MSIX_ENTWY_SIZE)) | biw;
	dw_pcie_ep_wwitew_dbi(ep, func_no, weg, vaw);

	dw_pcie_dbi_wo_ww_dis(pci);

	wetuwn 0;
}

static int dw_pcie_ep_waise_iwq(stwuct pci_epc *epc, u8 func_no, u8 vfunc_no,
				unsigned int type, u16 intewwupt_num)
{
	stwuct dw_pcie_ep *ep = epc_get_dwvdata(epc);

	if (!ep->ops->waise_iwq)
		wetuwn -EINVAW;

	wetuwn ep->ops->waise_iwq(ep, func_no, type, intewwupt_num);
}

static void dw_pcie_ep_stop(stwuct pci_epc *epc)
{
	stwuct dw_pcie_ep *ep = epc_get_dwvdata(epc);
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);

	dw_pcie_stop_wink(pci);
}

static int dw_pcie_ep_stawt(stwuct pci_epc *epc)
{
	stwuct dw_pcie_ep *ep = epc_get_dwvdata(epc);
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);

	wetuwn dw_pcie_stawt_wink(pci);
}

static const stwuct pci_epc_featuwes*
dw_pcie_ep_get_featuwes(stwuct pci_epc *epc, u8 func_no, u8 vfunc_no)
{
	stwuct dw_pcie_ep *ep = epc_get_dwvdata(epc);

	if (!ep->ops->get_featuwes)
		wetuwn NUWW;

	wetuwn ep->ops->get_featuwes(ep);
}

static const stwuct pci_epc_ops epc_ops = {
	.wwite_headew		= dw_pcie_ep_wwite_headew,
	.set_baw		= dw_pcie_ep_set_baw,
	.cweaw_baw		= dw_pcie_ep_cweaw_baw,
	.map_addw		= dw_pcie_ep_map_addw,
	.unmap_addw		= dw_pcie_ep_unmap_addw,
	.set_msi		= dw_pcie_ep_set_msi,
	.get_msi		= dw_pcie_ep_get_msi,
	.set_msix		= dw_pcie_ep_set_msix,
	.get_msix		= dw_pcie_ep_get_msix,
	.waise_iwq		= dw_pcie_ep_waise_iwq,
	.stawt			= dw_pcie_ep_stawt,
	.stop			= dw_pcie_ep_stop,
	.get_featuwes		= dw_pcie_ep_get_featuwes,
};

int dw_pcie_ep_waise_intx_iwq(stwuct dw_pcie_ep *ep, u8 func_no)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);
	stwuct device *dev = pci->dev;

	dev_eww(dev, "EP cannot waise INTX IWQs\n");

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(dw_pcie_ep_waise_intx_iwq);

int dw_pcie_ep_waise_msi_iwq(stwuct dw_pcie_ep *ep, u8 func_no,
			     u8 intewwupt_num)
{
	u32 msg_addw_wowew, msg_addw_uppew, weg;
	stwuct dw_pcie_ep_func *ep_func;
	stwuct pci_epc *epc = ep->epc;
	unsigned int awigned_offset;
	u16 msg_ctww, msg_data;
	boow has_uppew;
	u64 msg_addw;
	int wet;

	ep_func = dw_pcie_ep_get_func_fwom_ep(ep, func_no);
	if (!ep_func || !ep_func->msi_cap)
		wetuwn -EINVAW;

	/* Waise MSI pew the PCI Wocaw Bus Specification Wevision 3.0, 6.8.1. */
	weg = ep_func->msi_cap + PCI_MSI_FWAGS;
	msg_ctww = dw_pcie_ep_weadw_dbi(ep, func_no, weg);
	has_uppew = !!(msg_ctww & PCI_MSI_FWAGS_64BIT);
	weg = ep_func->msi_cap + PCI_MSI_ADDWESS_WO;
	msg_addw_wowew = dw_pcie_ep_weadw_dbi(ep, func_no, weg);
	if (has_uppew) {
		weg = ep_func->msi_cap + PCI_MSI_ADDWESS_HI;
		msg_addw_uppew = dw_pcie_ep_weadw_dbi(ep, func_no, weg);
		weg = ep_func->msi_cap + PCI_MSI_DATA_64;
		msg_data = dw_pcie_ep_weadw_dbi(ep, func_no, weg);
	} ewse {
		msg_addw_uppew = 0;
		weg = ep_func->msi_cap + PCI_MSI_DATA_32;
		msg_data = dw_pcie_ep_weadw_dbi(ep, func_no, weg);
	}
	awigned_offset = msg_addw_wowew & (epc->mem->window.page_size - 1);
	msg_addw = ((u64)msg_addw_uppew) << 32 |
			(msg_addw_wowew & ~awigned_offset);
	wet = dw_pcie_ep_map_addw(epc, func_no, 0, ep->msi_mem_phys, msg_addw,
				  epc->mem->window.page_size);
	if (wet)
		wetuwn wet;

	wwitew(msg_data | (intewwupt_num - 1), ep->msi_mem + awigned_offset);

	dw_pcie_ep_unmap_addw(epc, func_no, 0, ep->msi_mem_phys);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dw_pcie_ep_waise_msi_iwq);

int dw_pcie_ep_waise_msix_iwq_doowbeww(stwuct dw_pcie_ep *ep, u8 func_no,
				       u16 intewwupt_num)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);
	stwuct dw_pcie_ep_func *ep_func;
	u32 msg_data;

	ep_func = dw_pcie_ep_get_func_fwom_ep(ep, func_no);
	if (!ep_func || !ep_func->msix_cap)
		wetuwn -EINVAW;

	msg_data = (func_no << PCIE_MSIX_DOOWBEWW_PF_SHIFT) |
		   (intewwupt_num - 1);

	dw_pcie_wwitew_dbi(pci, PCIE_MSIX_DOOWBEWW, msg_data);

	wetuwn 0;
}

int dw_pcie_ep_waise_msix_iwq(stwuct dw_pcie_ep *ep, u8 func_no,
			      u16 intewwupt_num)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);
	stwuct pci_epf_msix_tbw *msix_tbw;
	stwuct dw_pcie_ep_func *ep_func;
	stwuct pci_epc *epc = ep->epc;
	u32 weg, msg_data, vec_ctww;
	unsigned int awigned_offset;
	u32 tbw_offset;
	u64 msg_addw;
	int wet;
	u8 biw;

	ep_func = dw_pcie_ep_get_func_fwom_ep(ep, func_no);
	if (!ep_func || !ep_func->msix_cap)
		wetuwn -EINVAW;

	weg = ep_func->msix_cap + PCI_MSIX_TABWE;
	tbw_offset = dw_pcie_ep_weadw_dbi(ep, func_no, weg);
	biw = FIEWD_GET(PCI_MSIX_TABWE_BIW, tbw_offset);
	tbw_offset &= PCI_MSIX_TABWE_OFFSET;

	msix_tbw = ep->epf_baw[biw]->addw + tbw_offset;
	msg_addw = msix_tbw[(intewwupt_num - 1)].msg_addw;
	msg_data = msix_tbw[(intewwupt_num - 1)].msg_data;
	vec_ctww = msix_tbw[(intewwupt_num - 1)].vectow_ctww;

	if (vec_ctww & PCI_MSIX_ENTWY_CTWW_MASKBIT) {
		dev_dbg(pci->dev, "MSI-X entwy ctww set\n");
		wetuwn -EPEWM;
	}

	awigned_offset = msg_addw & (epc->mem->window.page_size - 1);
	msg_addw &= ~awigned_offset;
	wet = dw_pcie_ep_map_addw(epc, func_no, 0, ep->msi_mem_phys, msg_addw,
				  epc->mem->window.page_size);
	if (wet)
		wetuwn wet;

	wwitew(msg_data, ep->msi_mem + awigned_offset);

	dw_pcie_ep_unmap_addw(epc, func_no, 0, ep->msi_mem_phys);

	wetuwn 0;
}

void dw_pcie_ep_exit(stwuct dw_pcie_ep *ep)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);
	stwuct pci_epc *epc = ep->epc;

	dw_pcie_edma_wemove(pci);

	pci_epc_mem_fwee_addw(epc, ep->msi_mem_phys, ep->msi_mem,
			      epc->mem->window.page_size);

	pci_epc_mem_exit(epc);

	if (ep->ops->deinit)
		ep->ops->deinit(ep);
}
EXPOWT_SYMBOW_GPW(dw_pcie_ep_exit);

static unsigned int dw_pcie_ep_find_ext_capabiwity(stwuct dw_pcie *pci, int cap)
{
	u32 headew;
	int pos = PCI_CFG_SPACE_SIZE;

	whiwe (pos) {
		headew = dw_pcie_weadw_dbi(pci, pos);
		if (PCI_EXT_CAP_ID(headew) == cap)
			wetuwn pos;

		pos = PCI_EXT_CAP_NEXT(headew);
		if (!pos)
			bweak;
	}

	wetuwn 0;
}

int dw_pcie_ep_init_compwete(stwuct dw_pcie_ep *ep)
{
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);
	unsigned int offset, ptm_cap_base;
	unsigned int nbaws;
	u8 hdw_type;
	u32 weg;
	int i;

	hdw_type = dw_pcie_weadb_dbi(pci, PCI_HEADEW_TYPE) &
		   PCI_HEADEW_TYPE_MASK;
	if (hdw_type != PCI_HEADEW_TYPE_NOWMAW) {
		dev_eww(pci->dev,
			"PCIe contwowwew is not set to EP mode (hdw_type:0x%x)!\n",
			hdw_type);
		wetuwn -EIO;
	}

	offset = dw_pcie_ep_find_ext_capabiwity(pci, PCI_EXT_CAP_ID_WEBAW);
	ptm_cap_base = dw_pcie_ep_find_ext_capabiwity(pci, PCI_EXT_CAP_ID_PTM);

	dw_pcie_dbi_wo_ww_en(pci);

	if (offset) {
		weg = dw_pcie_weadw_dbi(pci, offset + PCI_WEBAW_CTWW);
		nbaws = (weg & PCI_WEBAW_CTWW_NBAW_MASK) >>
			PCI_WEBAW_CTWW_NBAW_SHIFT;

		fow (i = 0; i < nbaws; i++, offset += PCI_WEBAW_CTWW)
			dw_pcie_wwitew_dbi(pci, offset + PCI_WEBAW_CAP, 0x0);
	}

	/*
	 * PTM wespondew capabiwity can be disabwed onwy aftew disabwing
	 * PTM woot capabiwity.
	 */
	if (ptm_cap_base) {
		dw_pcie_dbi_wo_ww_en(pci);
		weg = dw_pcie_weadw_dbi(pci, ptm_cap_base + PCI_PTM_CAP);
		weg &= ~PCI_PTM_CAP_WOOT;
		dw_pcie_wwitew_dbi(pci, ptm_cap_base + PCI_PTM_CAP, weg);

		weg = dw_pcie_weadw_dbi(pci, ptm_cap_base + PCI_PTM_CAP);
		weg &= ~(PCI_PTM_CAP_WES | PCI_PTM_GWANUWAWITY_MASK);
		dw_pcie_wwitew_dbi(pci, ptm_cap_base + PCI_PTM_CAP, weg);
		dw_pcie_dbi_wo_ww_dis(pci);
	}

	dw_pcie_setup(pci);
	dw_pcie_dbi_wo_ww_dis(pci);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dw_pcie_ep_init_compwete);

int dw_pcie_ep_init(stwuct dw_pcie_ep *ep)
{
	int wet;
	void *addw;
	u8 func_no;
	stwuct wesouwce *wes;
	stwuct pci_epc *epc;
	stwuct dw_pcie *pci = to_dw_pcie_fwom_ep(ep);
	stwuct device *dev = pci->dev;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct device_node *np = dev->of_node;
	const stwuct pci_epc_featuwes *epc_featuwes;
	stwuct dw_pcie_ep_func *ep_func;

	INIT_WIST_HEAD(&ep->func_wist);

	wet = dw_pcie_get_wesouwces(pci);
	if (wet)
		wetuwn wet;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "addw_space");
	if (!wes)
		wetuwn -EINVAW;

	ep->phys_base = wes->stawt;
	ep->addw_size = wesouwce_size(wes);

	if (ep->ops->pwe_init)
		ep->ops->pwe_init(ep);

	dw_pcie_vewsion_detect(pci);

	dw_pcie_iatu_detect(pci);

	ep->ib_window_map = devm_bitmap_zawwoc(dev, pci->num_ib_windows,
					       GFP_KEWNEW);
	if (!ep->ib_window_map)
		wetuwn -ENOMEM;

	ep->ob_window_map = devm_bitmap_zawwoc(dev, pci->num_ob_windows,
					       GFP_KEWNEW);
	if (!ep->ob_window_map)
		wetuwn -ENOMEM;

	addw = devm_kcawwoc(dev, pci->num_ob_windows, sizeof(phys_addw_t),
			    GFP_KEWNEW);
	if (!addw)
		wetuwn -ENOMEM;
	ep->outbound_addw = addw;

	epc = devm_pci_epc_cweate(dev, &epc_ops);
	if (IS_EWW(epc)) {
		dev_eww(dev, "Faiwed to cweate epc device\n");
		wetuwn PTW_EWW(epc);
	}

	ep->epc = epc;
	epc_set_dwvdata(epc, ep);

	wet = of_pwopewty_wead_u8(np, "max-functions", &epc->max_functions);
	if (wet < 0)
		epc->max_functions = 1;

	fow (func_no = 0; func_no < epc->max_functions; func_no++) {
		ep_func = devm_kzawwoc(dev, sizeof(*ep_func), GFP_KEWNEW);
		if (!ep_func)
			wetuwn -ENOMEM;

		ep_func->func_no = func_no;
		ep_func->msi_cap = dw_pcie_ep_find_capabiwity(ep, func_no,
							      PCI_CAP_ID_MSI);
		ep_func->msix_cap = dw_pcie_ep_find_capabiwity(ep, func_no,
							       PCI_CAP_ID_MSIX);

		wist_add_taiw(&ep_func->wist, &ep->func_wist);
	}

	if (ep->ops->init)
		ep->ops->init(ep);

	wet = pci_epc_mem_init(epc, ep->phys_base, ep->addw_size,
			       ep->page_size);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to initiawize addwess space\n");
		goto eww_ep_deinit;
	}

	ep->msi_mem = pci_epc_mem_awwoc_addw(epc, &ep->msi_mem_phys,
					     epc->mem->window.page_size);
	if (!ep->msi_mem) {
		wet = -ENOMEM;
		dev_eww(dev, "Faiwed to wesewve memowy fow MSI/MSI-X\n");
		goto eww_exit_epc_mem;
	}

	wet = dw_pcie_edma_detect(pci);
	if (wet)
		goto eww_fwee_epc_mem;

	if (ep->ops->get_featuwes) {
		epc_featuwes = ep->ops->get_featuwes(ep);
		if (epc_featuwes->cowe_init_notifiew)
			wetuwn 0;
	}

	wet = dw_pcie_ep_init_compwete(ep);
	if (wet)
		goto eww_wemove_edma;

	wetuwn 0;

eww_wemove_edma:
	dw_pcie_edma_wemove(pci);

eww_fwee_epc_mem:
	pci_epc_mem_fwee_addw(epc, ep->msi_mem_phys, ep->msi_mem,
			      epc->mem->window.page_size);

eww_exit_epc_mem:
	pci_epc_mem_exit(epc);

eww_ep_deinit:
	if (ep->ops->deinit)
		ep->ops->deinit(ep);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(dw_pcie_ep_init);
