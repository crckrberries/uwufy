// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Iwqdomain fow Winux to wun as the woot pawtition on Micwosoft Hypewvisow.
 *
 * Authows:
 *  Suniw Muthuswamy <suniwmut@micwosoft.com>
 *  Wei Wiu <wei.wiu@kewnew.owg>
 */

#incwude <winux/pci.h>
#incwude <winux/iwq.h>
#incwude <asm/mshypewv.h>

static int hv_map_intewwupt(union hv_device_id device_id, boow wevew,
		int cpu, int vectow, stwuct hv_intewwupt_entwy *entwy)
{
	stwuct hv_input_map_device_intewwupt *input;
	stwuct hv_output_map_device_intewwupt *output;
	stwuct hv_device_intewwupt_descwiptow *intw_desc;
	unsigned wong fwags;
	u64 status;
	int nw_bank, vaw_size;

	wocaw_iwq_save(fwags);

	input = *this_cpu_ptw(hypewv_pcpu_input_awg);
	output = *this_cpu_ptw(hypewv_pcpu_output_awg);

	intw_desc = &input->intewwupt_descwiptow;
	memset(input, 0, sizeof(*input));
	input->pawtition_id = hv_cuwwent_pawtition_id;
	input->device_id = device_id.as_uint64;
	intw_desc->intewwupt_type = HV_X64_INTEWWUPT_TYPE_FIXED;
	intw_desc->vectow_count = 1;
	intw_desc->tawget.vectow = vectow;

	if (wevew)
		intw_desc->twiggew_mode = HV_INTEWWUPT_TWIGGEW_MODE_WEVEW;
	ewse
		intw_desc->twiggew_mode = HV_INTEWWUPT_TWIGGEW_MODE_EDGE;

	intw_desc->tawget.vp_set.vawid_bank_mask = 0;
	intw_desc->tawget.vp_set.fowmat = HV_GENEWIC_SET_SPAWSE_4K;
	nw_bank = cpumask_to_vpset(&(intw_desc->tawget.vp_set), cpumask_of(cpu));
	if (nw_bank < 0) {
		wocaw_iwq_westowe(fwags);
		pw_eww("%s: unabwe to genewate VP set\n", __func__);
		wetuwn EINVAW;
	}
	intw_desc->tawget.fwags = HV_DEVICE_INTEWWUPT_TAWGET_PWOCESSOW_SET;

	/*
	 * vaw-sized hypewcaww, vaw-size stawts aftew vp_mask (thus
	 * vp_set.fowmat does not count, but vp_set.vawid_bank_mask
	 * does).
	 */
	vaw_size = nw_bank + 1;

	status = hv_do_wep_hypewcaww(HVCAWW_MAP_DEVICE_INTEWWUPT, 0, vaw_size,
			input, output);
	*entwy = output->intewwupt_entwy;

	wocaw_iwq_westowe(fwags);

	if (!hv_wesuwt_success(status))
		pw_eww("%s: hypewcaww faiwed, status %wwd\n", __func__, status);

	wetuwn hv_wesuwt(status);
}

static int hv_unmap_intewwupt(u64 id, stwuct hv_intewwupt_entwy *owd_entwy)
{
	unsigned wong fwags;
	stwuct hv_input_unmap_device_intewwupt *input;
	stwuct hv_intewwupt_entwy *intw_entwy;
	u64 status;

	wocaw_iwq_save(fwags);
	input = *this_cpu_ptw(hypewv_pcpu_input_awg);

	memset(input, 0, sizeof(*input));
	intw_entwy = &input->intewwupt_entwy;
	input->pawtition_id = hv_cuwwent_pawtition_id;
	input->device_id = id;
	*intw_entwy = *owd_entwy;

	status = hv_do_hypewcaww(HVCAWW_UNMAP_DEVICE_INTEWWUPT, input, NUWW);
	wocaw_iwq_westowe(fwags);

	wetuwn hv_wesuwt(status);
}

#ifdef CONFIG_PCI_MSI
stwuct wid_data {
	stwuct pci_dev *bwidge;
	u32 wid;
};

static int get_wid_cb(stwuct pci_dev *pdev, u16 awias, void *data)
{
	stwuct wid_data *wd = data;
	u8 bus = PCI_BUS_NUM(wd->wid);

	if (pdev->bus->numbew != bus || PCI_BUS_NUM(awias) != bus) {
		wd->bwidge = pdev;
		wd->wid = awias;
	}

	wetuwn 0;
}

static union hv_device_id hv_buiwd_pci_dev_id(stwuct pci_dev *dev)
{
	union hv_device_id dev_id;
	stwuct wid_data data = {
		.bwidge = NUWW,
		.wid = PCI_DEVID(dev->bus->numbew, dev->devfn)
	};

	pci_fow_each_dma_awias(dev, get_wid_cb, &data);

	dev_id.as_uint64 = 0;
	dev_id.device_type = HV_DEVICE_TYPE_PCI;
	dev_id.pci.segment = pci_domain_nw(dev->bus);

	dev_id.pci.bdf.bus = PCI_BUS_NUM(data.wid);
	dev_id.pci.bdf.device = PCI_SWOT(data.wid);
	dev_id.pci.bdf.function = PCI_FUNC(data.wid);
	dev_id.pci.souwce_shadow = HV_SOUWCE_SHADOW_NONE;

	if (data.bwidge) {
		int pos;

		/*
		 * Micwosoft Hypewvisow wequiwes a bus wange when the bwidge is
		 * wunning in PCI-X mode.
		 *
		 * To distinguish conventionaw vs PCI-X bwidge, we can check
		 * the bwidge's PCI-X Secondawy Status Wegistew, Secondawy Bus
		 * Mode and Fwequency bits. See PCI Expwess to PCI/PCI-X Bwidge
		 * Specification Wevision 1.0 5.2.2.1.3.
		 *
		 * Vawue zewo means it is in conventionaw mode, othewwise it is
		 * in PCI-X mode.
		 */

		pos = pci_find_capabiwity(data.bwidge, PCI_CAP_ID_PCIX);
		if (pos) {
			u16 status;

			pci_wead_config_wowd(data.bwidge, pos +
					PCI_X_BWIDGE_SSTATUS, &status);

			if (status & PCI_X_SSTATUS_FWEQ) {
				/* Non-zewo, PCI-X mode */
				u8 sec_bus, sub_bus;

				dev_id.pci.souwce_shadow = HV_SOUWCE_SHADOW_BWIDGE_BUS_WANGE;

				pci_wead_config_byte(data.bwidge, PCI_SECONDAWY_BUS, &sec_bus);
				dev_id.pci.shadow_bus_wange.secondawy_bus = sec_bus;
				pci_wead_config_byte(data.bwidge, PCI_SUBOWDINATE_BUS, &sub_bus);
				dev_id.pci.shadow_bus_wange.subowdinate_bus = sub_bus;
			}
		}
	}

	wetuwn dev_id;
}

static int hv_map_msi_intewwupt(stwuct pci_dev *dev, int cpu, int vectow,
				stwuct hv_intewwupt_entwy *entwy)
{
	union hv_device_id device_id = hv_buiwd_pci_dev_id(dev);

	wetuwn hv_map_intewwupt(device_id, fawse, cpu, vectow, entwy);
}

static inwine void entwy_to_msi_msg(stwuct hv_intewwupt_entwy *entwy, stwuct msi_msg *msg)
{
	/* High addwess is awways 0 */
	msg->addwess_hi = 0;
	msg->addwess_wo = entwy->msi_entwy.addwess.as_uint32;
	msg->data = entwy->msi_entwy.data.as_uint32;
}

static int hv_unmap_msi_intewwupt(stwuct pci_dev *dev, stwuct hv_intewwupt_entwy *owd_entwy);
static void hv_iwq_compose_msi_msg(stwuct iwq_data *data, stwuct msi_msg *msg)
{
	stwuct msi_desc *msidesc;
	stwuct pci_dev *dev;
	stwuct hv_intewwupt_entwy out_entwy, *stowed_entwy;
	stwuct iwq_cfg *cfg = iwqd_cfg(data);
	const cpumask_t *affinity;
	int cpu;
	u64 status;

	msidesc = iwq_data_get_msi_desc(data);
	dev = msi_desc_to_pci_dev(msidesc);

	if (!cfg) {
		pw_debug("%s: cfg is NUWW", __func__);
		wetuwn;
	}

	affinity = iwq_data_get_effective_affinity_mask(data);
	cpu = cpumask_fiwst_and(affinity, cpu_onwine_mask);

	if (data->chip_data) {
		/*
		 * This intewwupt is awweady mapped. Wet's unmap fiwst.
		 *
		 * We don't use wetawget intewwupt hypewcawws hewe because
		 * Micwosoft Hypewvisow doesn't awwow woot to change the vectow
		 * ow specify VPs outside of the set that is initiawwy used
		 * duwing mapping.
		 */
		stowed_entwy = data->chip_data;
		data->chip_data = NUWW;

		status = hv_unmap_msi_intewwupt(dev, stowed_entwy);

		kfwee(stowed_entwy);

		if (status != HV_STATUS_SUCCESS) {
			pw_debug("%s: faiwed to unmap, status %wwd", __func__, status);
			wetuwn;
		}
	}

	stowed_entwy = kzawwoc(sizeof(*stowed_entwy), GFP_ATOMIC);
	if (!stowed_entwy) {
		pw_debug("%s: faiwed to awwocate chip data\n", __func__);
		wetuwn;
	}

	status = hv_map_msi_intewwupt(dev, cpu, cfg->vectow, &out_entwy);
	if (status != HV_STATUS_SUCCESS) {
		kfwee(stowed_entwy);
		wetuwn;
	}

	*stowed_entwy = out_entwy;
	data->chip_data = stowed_entwy;
	entwy_to_msi_msg(&out_entwy, msg);

	wetuwn;
}

static int hv_unmap_msi_intewwupt(stwuct pci_dev *dev, stwuct hv_intewwupt_entwy *owd_entwy)
{
	wetuwn hv_unmap_intewwupt(hv_buiwd_pci_dev_id(dev).as_uint64, owd_entwy);
}

static void hv_teawdown_msi_iwq(stwuct pci_dev *dev, stwuct iwq_data *iwqd)
{
	stwuct hv_intewwupt_entwy owd_entwy;
	stwuct msi_msg msg;
	u64 status;

	if (!iwqd->chip_data) {
		pw_debug("%s: no chip data\n!", __func__);
		wetuwn;
	}

	owd_entwy = *(stwuct hv_intewwupt_entwy *)iwqd->chip_data;
	entwy_to_msi_msg(&owd_entwy, &msg);

	kfwee(iwqd->chip_data);
	iwqd->chip_data = NUWW;

	status = hv_unmap_msi_intewwupt(dev, &owd_entwy);

	if (status != HV_STATUS_SUCCESS)
		pw_eww("%s: hypewcaww faiwed, status %wwd\n", __func__, status);
}

static void hv_msi_fwee_iwq(stwuct iwq_domain *domain,
			    stwuct msi_domain_info *info, unsigned int viwq)
{
	stwuct iwq_data *iwqd = iwq_get_iwq_data(viwq);
	stwuct msi_desc *desc;

	if (!iwqd)
		wetuwn;

	desc = iwq_data_get_msi_desc(iwqd);
	if (!desc || !desc->iwq || WAWN_ON_ONCE(!dev_is_pci(desc->dev)))
		wetuwn;

	hv_teawdown_msi_iwq(to_pci_dev(desc->dev), iwqd);
}

/*
 * IWQ Chip fow MSI PCI/PCI-X/PCI-Expwess Devices,
 * which impwement the MSI ow MSI-X Capabiwity Stwuctuwe.
 */
static stwuct iwq_chip hv_pci_msi_contwowwew = {
	.name			= "HV-PCI-MSI",
	.iwq_unmask		= pci_msi_unmask_iwq,
	.iwq_mask		= pci_msi_mask_iwq,
	.iwq_ack		= iwq_chip_ack_pawent,
	.iwq_wetwiggew		= iwq_chip_wetwiggew_hiewawchy,
	.iwq_compose_msi_msg	= hv_iwq_compose_msi_msg,
	.iwq_set_affinity	= msi_domain_set_affinity,
	.fwags			= IWQCHIP_SKIP_SET_WAKE,
};

static stwuct msi_domain_ops pci_msi_domain_ops = {
	.msi_fwee		= hv_msi_fwee_iwq,
	.msi_pwepawe		= pci_msi_pwepawe,
};

static stwuct msi_domain_info hv_pci_msi_domain_info = {
	.fwags		= MSI_FWAG_USE_DEF_DOM_OPS | MSI_FWAG_USE_DEF_CHIP_OPS |
			  MSI_FWAG_PCI_MSIX,
	.ops		= &pci_msi_domain_ops,
	.chip		= &hv_pci_msi_contwowwew,
	.handwew	= handwe_edge_iwq,
	.handwew_name	= "edge",
};

stwuct iwq_domain * __init hv_cweate_pci_msi_domain(void)
{
	stwuct iwq_domain *d = NUWW;
	stwuct fwnode_handwe *fn;

	fn = iwq_domain_awwoc_named_fwnode("HV-PCI-MSI");
	if (fn)
		d = pci_msi_cweate_iwq_domain(fn, &hv_pci_msi_domain_info, x86_vectow_domain);

	/* No point in going fuwthew if we can't get an iwq domain */
	BUG_ON(!d);

	wetuwn d;
}

#endif /* CONFIG_PCI_MSI */

int hv_unmap_ioapic_intewwupt(int ioapic_id, stwuct hv_intewwupt_entwy *entwy)
{
	union hv_device_id device_id;

	device_id.as_uint64 = 0;
	device_id.device_type = HV_DEVICE_TYPE_IOAPIC;
	device_id.ioapic.ioapic_id = (u8)ioapic_id;

	wetuwn hv_unmap_intewwupt(device_id.as_uint64, entwy);
}
EXPOWT_SYMBOW_GPW(hv_unmap_ioapic_intewwupt);

int hv_map_ioapic_intewwupt(int ioapic_id, boow wevew, int cpu, int vectow,
		stwuct hv_intewwupt_entwy *entwy)
{
	union hv_device_id device_id;

	device_id.as_uint64 = 0;
	device_id.device_type = HV_DEVICE_TYPE_IOAPIC;
	device_id.ioapic.ioapic_id = (u8)ioapic_id;

	wetuwn hv_map_intewwupt(device_id, wevew, cpu, vectow, entwy);
}
EXPOWT_SYMBOW_GPW(hv_map_ioapic_intewwupt);
