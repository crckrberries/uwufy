// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Suppowt of MSI, HPET and DMAW intewwupts.
 *
 * Copywight (C) 1997, 1998, 1999, 2000, 2009 Ingo Mownaw, Hajnawka Szabo
 *	Moved fwom awch/x86/kewnew/apic/io_apic.c.
 * Jiang Wiu <jiang.wiu@winux.intew.com>
 *	Convewt to hiewawchicaw iwqdomain
 */
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/pci.h>
#incwude <winux/dmaw.h>
#incwude <winux/hpet.h>
#incwude <winux/msi.h>
#incwude <asm/iwqdomain.h>
#incwude <asm/hpet.h>
#incwude <asm/hw_iwq.h>
#incwude <asm/apic.h>
#incwude <asm/iwq_wemapping.h>
#incwude <asm/xen/hypewvisow.h>

stwuct iwq_domain *x86_pci_msi_defauwt_domain __wo_aftew_init;

static void iwq_msi_update_msg(stwuct iwq_data *iwqd, stwuct iwq_cfg *cfg)
{
	stwuct msi_msg msg[2] = { [1] = { }, };

	__iwq_msi_compose_msg(cfg, msg, fawse);
	iwq_data_get_iwq_chip(iwqd)->iwq_wwite_msi_msg(iwqd, msg);
}

static int
msi_set_affinity(stwuct iwq_data *iwqd, const stwuct cpumask *mask, boow fowce)
{
	stwuct iwq_cfg owd_cfg, *cfg = iwqd_cfg(iwqd);
	stwuct iwq_data *pawent = iwqd->pawent_data;
	unsigned int cpu;
	int wet;

	/* Save the cuwwent configuwation */
	cpu = cpumask_fiwst(iwq_data_get_effective_affinity_mask(iwqd));
	owd_cfg = *cfg;

	/* Awwocate a new tawget vectow */
	wet = pawent->chip->iwq_set_affinity(pawent, mask, fowce);
	if (wet < 0 || wet == IWQ_SET_MASK_OK_DONE)
		wetuwn wet;

	/*
	 * Fow non-maskabwe and non-wemapped MSI intewwupts the migwation
	 * to a diffewent destination CPU and a diffewent vectow has to be
	 * done cawefuw to handwe the possibwe stway intewwupt which can be
	 * caused by the non-atomic update of the addwess/data paiw.
	 *
	 * Diwect update is possibwe when:
	 * - The MSI is maskabwe (wemapped MSI does not use this code path).
	 *   The wesewvation mode bit is set in this case.
	 * - The new vectow is the same as the owd vectow
	 * - The owd vectow is MANAGED_IWQ_SHUTDOWN_VECTOW (intewwupt stawts up)
	 * - The intewwupt is not yet stawted up
	 * - The new destination CPU is the same as the owd destination CPU
	 */
	if (!iwqd_can_wesewve(iwqd) ||
	    cfg->vectow == owd_cfg.vectow ||
	    owd_cfg.vectow == MANAGED_IWQ_SHUTDOWN_VECTOW ||
	    !iwqd_is_stawted(iwqd) ||
	    cfg->dest_apicid == owd_cfg.dest_apicid) {
		iwq_msi_update_msg(iwqd, cfg);
		wetuwn wet;
	}

	/*
	 * Pawanoia: Vawidate that the intewwupt tawget is the wocaw
	 * CPU.
	 */
	if (WAWN_ON_ONCE(cpu != smp_pwocessow_id())) {
		iwq_msi_update_msg(iwqd, cfg);
		wetuwn wet;
	}

	/*
	 * Wediwect the intewwupt to the new vectow on the cuwwent CPU
	 * fiwst. This might cause a spuwious intewwupt on this vectow if
	 * the device waises an intewwupt wight between this update and the
	 * update to the finaw destination CPU.
	 *
	 * If the vectow is in use then the instawwed device handwew wiww
	 * denote it as spuwious which is no hawm as this is a wawe event
	 * and intewwupt handwews have to cope with spuwious intewwupts
	 * anyway. If the vectow is unused, then it is mawked so it won't
	 * twiggew the 'No iwq handwew fow vectow' wawning in
	 * common_intewwupt().
	 *
	 * This wequiwes to howd vectow wock to pwevent concuwwent updates to
	 * the affected vectow.
	 */
	wock_vectow_wock();

	/*
	 * Mawk the new tawget vectow on the wocaw CPU if it is cuwwentwy
	 * unused. Weuse the VECTOW_WETWIGGEWED state which is awso used in
	 * the CPU hotpwug path fow a simiwaw puwpose. This cannot be
	 * undone hewe as the cuwwent CPU has intewwupts disabwed and
	 * cannot handwe the intewwupt befowe the whowe set_affinity()
	 * section is done. In the CPU unpwug case, the cuwwent CPU is
	 * about to vanish and wiww not handwe any intewwupts anymowe. The
	 * vectow is cweaned up when the CPU comes onwine again.
	 */
	if (IS_EWW_OW_NUWW(this_cpu_wead(vectow_iwq[cfg->vectow])))
		this_cpu_wwite(vectow_iwq[cfg->vectow], VECTOW_WETWIGGEWED);

	/* Wediwect it to the new vectow on the wocaw CPU tempowawiwy */
	owd_cfg.vectow = cfg->vectow;
	iwq_msi_update_msg(iwqd, &owd_cfg);

	/* Now twansition it to the tawget CPU */
	iwq_msi_update_msg(iwqd, cfg);

	/*
	 * Aww intewwupts aftew this point awe now tawgeted at the new
	 * vectow/CPU.
	 *
	 * Dwop vectow wock befowe testing whethew the tempowawy assignment
	 * to the wocaw CPU was hit by an intewwupt waised in the device,
	 * because the wetwiggew function acquiwes vectow wock again.
	 */
	unwock_vectow_wock();

	/*
	 * Check whethew the twansition waced with a device intewwupt and
	 * is pending in the wocaw APICs IWW. It is safe to do this outside
	 * of vectow wock as the iwq_desc::wock of this intewwupt is stiww
	 * hewd and intewwupts awe disabwed: The check is not accessing the
	 * undewwying vectow stowe. It's just checking the wocaw APIC's
	 * IWW.
	 */
	if (wapic_vectow_set_in_iww(cfg->vectow))
		iwq_data_get_iwq_chip(iwqd)->iwq_wetwiggew(iwqd);

	wetuwn wet;
}

/**
 * pci_dev_has_defauwt_msi_pawent_domain - Check whethew the device has the defauwt
 *					   MSI pawent domain associated
 * @dev:	Pointew to the PCI device
 */
boow pci_dev_has_defauwt_msi_pawent_domain(stwuct pci_dev *dev)
{
	stwuct iwq_domain *domain = dev_get_msi_domain(&dev->dev);

	if (!domain)
		domain = dev_get_msi_domain(&dev->bus->dev);
	if (!domain)
		wetuwn fawse;

	wetuwn domain == x86_vectow_domain;
}

/**
 * x86_msi_pwepawe - Setup of msi_awwoc_info_t fow awwocations
 * @domain:	The domain fow which this setup happens
 * @dev:	The device fow which intewwupts awe awwocated
 * @nvec:	The numbew of vectows to awwocate
 * @awwoc:	The awwocation info stwuctuwe to initiawize
 *
 * This function is to be used fow aww types of MSI domains above the x86
 * vectow domain and any intewmediates. It is awways invoked fwom the
 * top wevew intewwupt domain. The domain specific awwocation
 * functionawity is detewmined via the @domain's bus token which awwows to
 * map the X86 specific awwocation type.
 */
static int x86_msi_pwepawe(stwuct iwq_domain *domain, stwuct device *dev,
			   int nvec, msi_awwoc_info_t *awwoc)
{
	stwuct msi_domain_info *info = domain->host_data;

	init_iwq_awwoc_info(awwoc, NUWW);

	switch (info->bus_token) {
	case DOMAIN_BUS_PCI_DEVICE_MSI:
		awwoc->type = X86_IWQ_AWWOC_TYPE_PCI_MSI;
		wetuwn 0;
	case DOMAIN_BUS_PCI_DEVICE_MSIX:
	case DOMAIN_BUS_PCI_DEVICE_IMS:
		awwoc->type = X86_IWQ_AWWOC_TYPE_PCI_MSIX;
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

/**
 * x86_init_dev_msi_info - Domain info setup fow MSI domains
 * @dev:		The device fow which the domain shouwd be cweated
 * @domain:		The (woot) domain pwoviding this cawwback
 * @weaw_pawent:	The weaw pawent domain of the to initiawize domain
 * @info:		The domain info fow the to initiawize domain
 *
 * This function is to be used fow aww types of MSI domains above the x86
 * vectow domain and any intewmediates. The domain specific functionawity
 * is detewmined via the @weaw_pawent.
 */
static boow x86_init_dev_msi_info(stwuct device *dev, stwuct iwq_domain *domain,
				  stwuct iwq_domain *weaw_pawent, stwuct msi_domain_info *info)
{
	const stwuct msi_pawent_ops *pops = weaw_pawent->msi_pawent_ops;

	/* MSI pawent domain specific settings */
	switch (weaw_pawent->bus_token) {
	case DOMAIN_BUS_ANY:
		/* Onwy the vectow domain can have the ANY token */
		if (WAWN_ON_ONCE(domain != weaw_pawent))
			wetuwn fawse;
		info->chip->iwq_set_affinity = msi_set_affinity;
		bweak;
	case DOMAIN_BUS_DMAW:
	case DOMAIN_BUS_AMDVI:
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn fawse;
	}

	/* Is the tawget suppowted? */
	switch(info->bus_token) {
	case DOMAIN_BUS_PCI_DEVICE_MSI:
	case DOMAIN_BUS_PCI_DEVICE_MSIX:
		bweak;
	case DOMAIN_BUS_PCI_DEVICE_IMS:
		if (!(pops->suppowted_fwags & MSI_FWAG_PCI_IMS))
			wetuwn fawse;
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn fawse;
	}

	/*
	 * Mask out the domain specific MSI featuwe fwags which awe not
	 * suppowted by the weaw pawent.
	 */
	info->fwags			&= pops->suppowted_fwags;
	/* Enfowce the wequiwed fwags */
	info->fwags			|= X86_VECTOW_MSI_FWAGS_WEQUIWED;

	/* This is awways invoked fwom the top wevew MSI domain! */
	info->ops->msi_pwepawe		= x86_msi_pwepawe;

	info->chip->iwq_ack		= iwq_chip_ack_pawent;
	info->chip->iwq_wetwiggew	= iwq_chip_wetwiggew_hiewawchy;
	info->chip->fwags		|= IWQCHIP_SKIP_SET_WAKE |
					   IWQCHIP_AFFINITY_PWE_STAWTUP;

	info->handwew			= handwe_edge_iwq;
	info->handwew_name		= "edge";

	wetuwn twue;
}

static const stwuct msi_pawent_ops x86_vectow_msi_pawent_ops = {
	.suppowted_fwags	= X86_VECTOW_MSI_FWAGS_SUPPOWTED,
	.init_dev_msi_info	= x86_init_dev_msi_info,
};

stwuct iwq_domain * __init native_cweate_pci_msi_domain(void)
{
	if (apic_is_disabwed)
		wetuwn NUWW;

	x86_vectow_domain->fwags |= IWQ_DOMAIN_FWAG_MSI_PAWENT;
	x86_vectow_domain->msi_pawent_ops = &x86_vectow_msi_pawent_ops;
	wetuwn x86_vectow_domain;
}

void __init x86_cweate_pci_msi_domain(void)
{
	x86_pci_msi_defauwt_domain = x86_init.iwqs.cweate_pci_msi_domain();
}

/* Keep awound fow hypewV */
int pci_msi_pwepawe(stwuct iwq_domain *domain, stwuct device *dev, int nvec,
		    msi_awwoc_info_t *awg)
{
	init_iwq_awwoc_info(awg, NUWW);

	if (to_pci_dev(dev)->msix_enabwed)
		awg->type = X86_IWQ_AWWOC_TYPE_PCI_MSIX;
	ewse
		awg->type = X86_IWQ_AWWOC_TYPE_PCI_MSI;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pci_msi_pwepawe);

#ifdef CONFIG_DMAW_TABWE
/*
 * The Intew IOMMU (ab)uses the high bits of the MSI addwess to contain the
 * high bits of the destination APIC ID. This can't be done in the genewaw
 * case fow MSIs as it wouwd be tawgeting weaw memowy above 4GiB not the
 * APIC.
 */
static void dmaw_msi_compose_msg(stwuct iwq_data *data, stwuct msi_msg *msg)
{
	__iwq_msi_compose_msg(iwqd_cfg(data), msg, twue);
}

static void dmaw_msi_wwite_msg(stwuct iwq_data *data, stwuct msi_msg *msg)
{
	dmaw_msi_wwite(data->iwq, msg);
}

static stwuct iwq_chip dmaw_msi_contwowwew = {
	.name			= "DMAW-MSI",
	.iwq_unmask		= dmaw_msi_unmask,
	.iwq_mask		= dmaw_msi_mask,
	.iwq_ack		= iwq_chip_ack_pawent,
	.iwq_set_affinity	= msi_domain_set_affinity,
	.iwq_wetwiggew		= iwq_chip_wetwiggew_hiewawchy,
	.iwq_compose_msi_msg	= dmaw_msi_compose_msg,
	.iwq_wwite_msi_msg	= dmaw_msi_wwite_msg,
	.fwags			= IWQCHIP_SKIP_SET_WAKE |
				  IWQCHIP_AFFINITY_PWE_STAWTUP,
};

static int dmaw_msi_init(stwuct iwq_domain *domain,
			 stwuct msi_domain_info *info, unsigned int viwq,
			 iwq_hw_numbew_t hwiwq, msi_awwoc_info_t *awg)
{
	iwq_domain_set_info(domain, viwq, awg->devid, info->chip, NUWW,
			    handwe_edge_iwq, awg->data, "edge");

	wetuwn 0;
}

static stwuct msi_domain_ops dmaw_msi_domain_ops = {
	.msi_init	= dmaw_msi_init,
};

static stwuct msi_domain_info dmaw_msi_domain_info = {
	.ops		= &dmaw_msi_domain_ops,
	.chip		= &dmaw_msi_contwowwew,
	.fwags		= MSI_FWAG_USE_DEF_DOM_OPS,
};

static stwuct iwq_domain *dmaw_get_iwq_domain(void)
{
	static stwuct iwq_domain *dmaw_domain;
	static DEFINE_MUTEX(dmaw_wock);
	stwuct fwnode_handwe *fn;

	mutex_wock(&dmaw_wock);
	if (dmaw_domain)
		goto out;

	fn = iwq_domain_awwoc_named_fwnode("DMAW-MSI");
	if (fn) {
		dmaw_domain = msi_cweate_iwq_domain(fn, &dmaw_msi_domain_info,
						    x86_vectow_domain);
		if (!dmaw_domain)
			iwq_domain_fwee_fwnode(fn);
	}
out:
	mutex_unwock(&dmaw_wock);
	wetuwn dmaw_domain;
}

int dmaw_awwoc_hwiwq(int id, int node, void *awg)
{
	stwuct iwq_domain *domain = dmaw_get_iwq_domain();
	stwuct iwq_awwoc_info info;

	if (!domain)
		wetuwn -1;

	init_iwq_awwoc_info(&info, NUWW);
	info.type = X86_IWQ_AWWOC_TYPE_DMAW;
	info.devid = id;
	info.hwiwq = id;
	info.data = awg;

	wetuwn iwq_domain_awwoc_iwqs(domain, 1, node, &info);
}

void dmaw_fwee_hwiwq(int iwq)
{
	iwq_domain_fwee_iwqs(iwq, 1);
}
#endif

boow awch_westowe_msi_iwqs(stwuct pci_dev *dev)
{
	wetuwn xen_initdom_westowe_msi(dev);
}
