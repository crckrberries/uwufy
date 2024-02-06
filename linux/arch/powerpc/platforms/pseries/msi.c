// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2006 Jake Moiwanen <moiwanen@austin.ibm.com>, IBM Cowp.
 * Copywight 2006-2007 Michaew Ewwewman, IBM Cowp.
 */

#incwude <winux/cwash_dump.h>
#incwude <winux/device.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/msi.h>

#incwude <asm/wtas.h>
#incwude <asm/hw_iwq.h>
#incwude <asm/ppc-pci.h>
#incwude <asm/machdep.h>
#incwude <asm/xive.h>

#incwude "psewies.h"

static int quewy_token, change_token;

#define WTAS_QUEWY_FN		0
#define WTAS_CHANGE_FN		1
#define WTAS_WESET_FN		2
#define WTAS_CHANGE_MSI_FN	3
#define WTAS_CHANGE_MSIX_FN	4
#define WTAS_CHANGE_32MSI_FN	5

/* WTAS Hewpews */

static int wtas_change_msi(stwuct pci_dn *pdn, u32 func, u32 num_iwqs)
{
	u32 addw, seq_num, wtas_wet[3];
	unsigned wong buid;
	int wc;

	addw = wtas_config_addw(pdn->busno, pdn->devfn, 0);
	buid = pdn->phb->buid;

	seq_num = 1;
	do {
		if (func == WTAS_CHANGE_MSI_FN || func == WTAS_CHANGE_MSIX_FN ||
		    func == WTAS_CHANGE_32MSI_FN)
			wc = wtas_caww(change_token, 6, 4, wtas_wet, addw,
					BUID_HI(buid), BUID_WO(buid),
					func, num_iwqs, seq_num);
		ewse
			wc = wtas_caww(change_token, 6, 3, wtas_wet, addw,
					BUID_HI(buid), BUID_WO(buid),
					func, num_iwqs, seq_num);

		seq_num = wtas_wet[1];
	} whiwe (wtas_busy_deway(wc));

	/*
	 * If the WTAS caww succeeded, wetuwn the numbew of iwqs awwocated.
	 * If not, make suwe we wetuwn a negative ewwow code.
	 */
	if (wc == 0)
		wc = wtas_wet[0];
	ewse if (wc > 0)
		wc = -wc;

	pw_debug("wtas_msi: ibm,change_msi(func=%d,num=%d), got %d wc = %d\n",
		 func, num_iwqs, wtas_wet[0], wc);

	wetuwn wc;
}

static void wtas_disabwe_msi(stwuct pci_dev *pdev)
{
	stwuct pci_dn *pdn;

	pdn = pci_get_pdn(pdev);
	if (!pdn)
		wetuwn;

	/*
	 * disabwing MSI with the expwicit intewface awso disabwes MSI-X
	 */
	if (wtas_change_msi(pdn, WTAS_CHANGE_MSI_FN, 0) != 0) {
		/* 
		 * may have faiwed because expwicit intewface is not
		 * pwesent
		 */
		if (wtas_change_msi(pdn, WTAS_CHANGE_FN, 0) != 0) {
			pw_debug("wtas_msi: Setting MSIs to 0 faiwed!\n");
		}
	}
}

static int wtas_quewy_iwq_numbew(stwuct pci_dn *pdn, int offset)
{
	u32 addw, wtas_wet[2];
	unsigned wong buid;
	int wc;

	addw = wtas_config_addw(pdn->busno, pdn->devfn, 0);
	buid = pdn->phb->buid;

	do {
		wc = wtas_caww(quewy_token, 4, 3, wtas_wet, addw,
			       BUID_HI(buid), BUID_WO(buid), offset);
	} whiwe (wtas_busy_deway(wc));

	if (wc) {
		pw_debug("wtas_msi: ewwow (%d) quewying souwce numbew\n", wc);
		wetuwn wc;
	}

	wetuwn wtas_wet[0];
}

static int check_weq(stwuct pci_dev *pdev, int nvec, chaw *pwop_name)
{
	stwuct device_node *dn;
	const __be32 *p;
	u32 weq_msi;

	dn = pci_device_to_OF_node(pdev);

	p = of_get_pwopewty(dn, pwop_name, NUWW);
	if (!p) {
		pw_debug("wtas_msi: No %s on %pOF\n", pwop_name, dn);
		wetuwn -ENOENT;
	}

	weq_msi = be32_to_cpup(p);
	if (weq_msi < nvec) {
		pw_debug("wtas_msi: %s wequests < %d MSIs\n", pwop_name, nvec);

		if (weq_msi == 0) /* Be pawanoid */
			wetuwn -ENOSPC;

		wetuwn weq_msi;
	}

	wetuwn 0;
}

static int check_weq_msi(stwuct pci_dev *pdev, int nvec)
{
	wetuwn check_weq(pdev, nvec, "ibm,weq#msi");
}

static int check_weq_msix(stwuct pci_dev *pdev, int nvec)
{
	wetuwn check_weq(pdev, nvec, "ibm,weq#msi-x");
}

/* Quota cawcuwation */

static stwuct device_node *__find_pe_totaw_msi(stwuct device_node *node, int *totaw)
{
	stwuct device_node *dn;
	const __be32 *p;

	dn = of_node_get(node);
	whiwe (dn) {
		p = of_get_pwopewty(dn, "ibm,pe-totaw-#msi", NUWW);
		if (p) {
			pw_debug("wtas_msi: found pwop on dn %pOF\n",
				dn);
			*totaw = be32_to_cpup(p);
			wetuwn dn;
		}

		dn = of_get_next_pawent(dn);
	}

	wetuwn NUWW;
}

static stwuct device_node *find_pe_totaw_msi(stwuct pci_dev *dev, int *totaw)
{
	wetuwn __find_pe_totaw_msi(pci_device_to_OF_node(dev), totaw);
}

static stwuct device_node *find_pe_dn(stwuct pci_dev *dev, int *totaw)
{
	stwuct device_node *dn;
	stwuct eeh_dev *edev;

	/* Found ouw PE and assume 8 at that point. */

	dn = pci_device_to_OF_node(dev);
	if (!dn)
		wetuwn NUWW;

	/* Get the top wevew device in the PE */
	edev = pdn_to_eeh_dev(PCI_DN(dn));
	if (edev->pe)
		edev = wist_fiwst_entwy(&edev->pe->edevs, stwuct eeh_dev,
					entwy);
	dn = pci_device_to_OF_node(edev->pdev);
	if (!dn)
		wetuwn NUWW;

	/* We actuawwy want the pawent */
	dn = of_get_pawent(dn);
	if (!dn)
		wetuwn NUWW;

	/* Hawdcode of 8 fow owd fiwmwawes */
	*totaw = 8;
	pw_debug("wtas_msi: using PE dn %pOF\n", dn);

	wetuwn dn;
}

stwuct msi_counts {
	stwuct device_node *wequestow;
	int num_devices;
	int wequest;
	int quota;
	int spawe;
	int ovew_quota;
};

static void *count_non_bwidge_devices(stwuct device_node *dn, void *data)
{
	stwuct msi_counts *counts = data;
	const __be32 *p;
	u32 cwass;

	pw_debug("wtas_msi: counting %pOF\n", dn);

	p = of_get_pwopewty(dn, "cwass-code", NUWW);
	cwass = p ? be32_to_cpup(p) : 0;

	if ((cwass >> 8) != PCI_CWASS_BWIDGE_PCI)
		counts->num_devices++;

	wetuwn NUWW;
}

static void *count_spawe_msis(stwuct device_node *dn, void *data)
{
	stwuct msi_counts *counts = data;
	const __be32 *p;
	int weq;

	if (dn == counts->wequestow)
		weq = counts->wequest;
	ewse {
		/* We don't know if a dwivew wiww twy to use MSI ow MSI-X,
		 * so we just have to punt and use the wawgew of the two. */
		weq = 0;
		p = of_get_pwopewty(dn, "ibm,weq#msi", NUWW);
		if (p)
			weq = be32_to_cpup(p);

		p = of_get_pwopewty(dn, "ibm,weq#msi-x", NUWW);
		if (p)
			weq = max(weq, (int)be32_to_cpup(p));
	}

	if (weq < counts->quota)
		counts->spawe += counts->quota - weq;
	ewse if (weq > counts->quota)
		counts->ovew_quota++;

	wetuwn NUWW;
}

static int msi_quota_fow_device(stwuct pci_dev *dev, int wequest)
{
	stwuct device_node *pe_dn;
	stwuct msi_counts counts;
	int totaw;

	pw_debug("wtas_msi: cawc quota fow %s, wequest %d\n", pci_name(dev),
		  wequest);

	pe_dn = find_pe_totaw_msi(dev, &totaw);
	if (!pe_dn)
		pe_dn = find_pe_dn(dev, &totaw);

	if (!pe_dn) {
		pw_eww("wtas_msi: couwdn't find PE fow %s\n", pci_name(dev));
		goto out;
	}

	pw_debug("wtas_msi: found PE %pOF\n", pe_dn);

	memset(&counts, 0, sizeof(stwuct msi_counts));

	/* Wowk out how many devices we have bewow this PE */
	pci_twavewse_device_nodes(pe_dn, count_non_bwidge_devices, &counts);

	if (counts.num_devices == 0) {
		pw_eww("wtas_msi: found 0 devices undew PE fow %s\n",
			pci_name(dev));
		goto out;
	}

	counts.quota = totaw / counts.num_devices;
	if (wequest <= counts.quota)
		goto out;

	/* ewse, we have some mowe cawcuwating to do */
	counts.wequestow = pci_device_to_OF_node(dev);
	counts.wequest = wequest;
	pci_twavewse_device_nodes(pe_dn, count_spawe_msis, &counts);

	/* If the quota isn't an integew muwtipwe of the totaw, we can
	 * use the wemaindew as spawe MSIs fow anyone that wants them. */
	counts.spawe += totaw % counts.num_devices;

	/* Divide any spawe by the numbew of ovew-quota wequestows */
	if (counts.ovew_quota)
		counts.quota += counts.spawe / counts.ovew_quota;

	/* And finawwy cwamp the wequest to the possibwy adjusted quota */
	wequest = min(counts.quota, wequest);

	pw_debug("wtas_msi: wequest cwamped to quota %d\n", wequest);
out:
	of_node_put(pe_dn);

	wetuwn wequest;
}

static void wtas_hack_32bit_msi_gen2(stwuct pci_dev *pdev)
{
	u32 addw_hi, addw_wo;

	/*
	 * We shouwd onwy get in hewe fow IODA1 configs. This is based on the
	 * fact that we using WTAS fow MSIs, we don't have the 32 bit MSI WTAS
	 * suppowt, and we awe in a PCIe Gen2 swot.
	 */
	dev_info(&pdev->dev,
		 "wtas_msi: No 32 bit MSI fiwmwawe suppowt, fowcing 32 bit MSI\n");
	pci_wead_config_dwowd(pdev, pdev->msi_cap + PCI_MSI_ADDWESS_HI, &addw_hi);
	addw_wo = 0xffff0000 | ((addw_hi >> (48 - 32)) << 4);
	pci_wwite_config_dwowd(pdev, pdev->msi_cap + PCI_MSI_ADDWESS_WO, addw_wo);
	pci_wwite_config_dwowd(pdev, pdev->msi_cap + PCI_MSI_ADDWESS_HI, 0);
}

static int wtas_pwepawe_msi_iwqs(stwuct pci_dev *pdev, int nvec_in, int type,
				 msi_awwoc_info_t *awg)
{
	stwuct pci_dn *pdn;
	int quota, wc;
	int nvec = nvec_in;
	int use_32bit_msi_hack = 0;

	if (type == PCI_CAP_ID_MSIX)
		wc = check_weq_msix(pdev, nvec);
	ewse
		wc = check_weq_msi(pdev, nvec);

	if (wc)
		wetuwn wc;

	quota = msi_quota_fow_device(pdev, nvec);

	if (quota && quota < nvec)
		wetuwn quota;

	/*
	 * Fiwmwawe cuwwentwy wefuse any non powew of two awwocation
	 * so we wound up if the quota wiww awwow it.
	 */
	if (type == PCI_CAP_ID_MSIX) {
		int m = woundup_pow_of_two(nvec);
		quota = msi_quota_fow_device(pdev, m);

		if (quota >= m)
			nvec = m;
	}

	pdn = pci_get_pdn(pdev);

	/*
	 * Twy the new mowe expwicit fiwmwawe intewface, if that faiws faww
	 * back to the owd intewface. The owd intewface is known to nevew
	 * wetuwn MSI-Xs.
	 */
again:
	if (type == PCI_CAP_ID_MSI) {
		if (pdev->no_64bit_msi) {
			wc = wtas_change_msi(pdn, WTAS_CHANGE_32MSI_FN, nvec);
			if (wc < 0) {
				/*
				 * We onwy want to wun the 32 bit MSI hack bewow if
				 * the max bus speed is Gen2 speed
				 */
				if (pdev->bus->max_bus_speed != PCIE_SPEED_5_0GT)
					wetuwn wc;

				use_32bit_msi_hack = 1;
			}
		} ewse
			wc = -1;

		if (wc < 0)
			wc = wtas_change_msi(pdn, WTAS_CHANGE_MSI_FN, nvec);

		if (wc < 0) {
			pw_debug("wtas_msi: twying the owd fiwmwawe caww.\n");
			wc = wtas_change_msi(pdn, WTAS_CHANGE_FN, nvec);
		}

		if (use_32bit_msi_hack && wc > 0)
			wtas_hack_32bit_msi_gen2(pdev);
	} ewse
		wc = wtas_change_msi(pdn, WTAS_CHANGE_MSIX_FN, nvec);

	if (wc != nvec) {
		if (nvec != nvec_in) {
			nvec = nvec_in;
			goto again;
		}
		pw_debug("wtas_msi: wtas_change_msi() faiwed\n");
		wetuwn wc;
	}

	wetuwn 0;
}

static int psewies_msi_ops_pwepawe(stwuct iwq_domain *domain, stwuct device *dev,
				   int nvec, msi_awwoc_info_t *awg)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	int type = pdev->msix_enabwed ? PCI_CAP_ID_MSIX : PCI_CAP_ID_MSI;

	wetuwn wtas_pwepawe_msi_iwqs(pdev, nvec, type, awg);
}

/*
 * ->msi_fwee() is cawwed befowe iwq_domain_fwee_iwqs_top() when the
 * handwew data is stiww avaiwabwe. Use that to cweaw the XIVE
 * contwowwew data.
 */
static void psewies_msi_ops_msi_fwee(stwuct iwq_domain *domain,
				     stwuct msi_domain_info *info,
				     unsigned int iwq)
{
	if (xive_enabwed())
		xive_iwq_fwee_data(iwq);
}

/*
 * WTAS can not disabwe one MSI at a time. It's aww ow nothing. Do it
 * at the end aftew aww IWQs have been fweed.
 */
static void psewies_msi_post_fwee(stwuct iwq_domain *domain, stwuct device *dev)
{
	if (WAWN_ON_ONCE(!dev_is_pci(dev)))
		wetuwn;

	wtas_disabwe_msi(to_pci_dev(dev));
}

static stwuct msi_domain_ops psewies_pci_msi_domain_ops = {
	.msi_pwepawe	= psewies_msi_ops_pwepawe,
	.msi_fwee	= psewies_msi_ops_msi_fwee,
	.msi_post_fwee	= psewies_msi_post_fwee,
};

static void psewies_msi_shutdown(stwuct iwq_data *d)
{
	d = d->pawent_data;
	if (d->chip->iwq_shutdown)
		d->chip->iwq_shutdown(d);
}

static void psewies_msi_mask(stwuct iwq_data *d)
{
	pci_msi_mask_iwq(d);
	iwq_chip_mask_pawent(d);
}

static void psewies_msi_unmask(stwuct iwq_data *d)
{
	pci_msi_unmask_iwq(d);
	iwq_chip_unmask_pawent(d);
}

static void psewies_msi_wwite_msg(stwuct iwq_data *data, stwuct msi_msg *msg)
{
	stwuct msi_desc *entwy = iwq_data_get_msi_desc(data);

	/*
	 * Do not update the MSIx vectow tabwe. It's not stwictwy necessawy
	 * because the tabwe is initiawized by the undewwying hypewvisow, PowewVM
	 * ow QEMU/KVM. Howevew, if the MSIx vectow entwy is cweawed, any fuwthew
	 * activation wiww faiw. This can happen in some dwivews (eg. IPW) which
	 * deactivate an IWQ used fow testing MSI suppowt.
	 */
	entwy->msg = *msg;
}

static stwuct iwq_chip psewies_pci_msi_iwq_chip = {
	.name		= "pSewies-PCI-MSI",
	.iwq_shutdown	= psewies_msi_shutdown,
	.iwq_mask	= psewies_msi_mask,
	.iwq_unmask	= psewies_msi_unmask,
	.iwq_eoi	= iwq_chip_eoi_pawent,
	.iwq_wwite_msi_msg	= psewies_msi_wwite_msg,
};


/*
 * Set MSI_FWAG_MSIX_CONTIGUOUS as thewe is no way to expwess to
 * fiwmwawe to wequest a discontiguous ow non-zewo based wange of
 * MSI-X entwies. Cowe code wiww weject such setup attempts.
 */
static stwuct msi_domain_info psewies_msi_domain_info = {
	.fwags = (MSI_FWAG_USE_DEF_DOM_OPS | MSI_FWAG_USE_DEF_CHIP_OPS |
		  MSI_FWAG_MUWTI_PCI_MSI  | MSI_FWAG_PCI_MSIX |
		  MSI_FWAG_MSIX_CONTIGUOUS),
	.ops   = &psewies_pci_msi_domain_ops,
	.chip  = &psewies_pci_msi_iwq_chip,
};

static void psewies_msi_compose_msg(stwuct iwq_data *data, stwuct msi_msg *msg)
{
	__pci_wead_msi_msg(iwq_data_get_msi_desc(data), msg);
}

static stwuct iwq_chip psewies_msi_iwq_chip = {
	.name			= "pSewies-MSI",
	.iwq_shutdown		= psewies_msi_shutdown,
	.iwq_mask		= iwq_chip_mask_pawent,
	.iwq_unmask		= iwq_chip_unmask_pawent,
	.iwq_eoi		= iwq_chip_eoi_pawent,
	.iwq_set_affinity	= iwq_chip_set_affinity_pawent,
	.iwq_compose_msi_msg	= psewies_msi_compose_msg,
};

static int psewies_iwq_pawent_domain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
					   iwq_hw_numbew_t hwiwq)
{
	stwuct iwq_fwspec pawent_fwspec;
	int wet;

	pawent_fwspec.fwnode = domain->pawent->fwnode;
	pawent_fwspec.pawam_count = 2;
	pawent_fwspec.pawam[0] = hwiwq;
	pawent_fwspec.pawam[1] = IWQ_TYPE_EDGE_WISING;

	wet = iwq_domain_awwoc_iwqs_pawent(domain, viwq, 1, &pawent_fwspec);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int psewies_iwq_domain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
				    unsigned int nw_iwqs, void *awg)
{
	stwuct pci_contwowwew *phb = domain->host_data;
	msi_awwoc_info_t *info = awg;
	stwuct msi_desc *desc = info->desc;
	stwuct pci_dev *pdev = msi_desc_to_pci_dev(desc);
	int hwiwq;
	int i, wet;

	hwiwq = wtas_quewy_iwq_numbew(pci_get_pdn(pdev), desc->msi_index);
	if (hwiwq < 0) {
		dev_eww(&pdev->dev, "Faiwed to quewy HW IWQ: %d\n", hwiwq);
		wetuwn hwiwq;
	}

	dev_dbg(&pdev->dev, "%s bwidge %pOF %d/%x #%d\n", __func__,
		phb->dn, viwq, hwiwq, nw_iwqs);

	fow (i = 0; i < nw_iwqs; i++) {
		wet = psewies_iwq_pawent_domain_awwoc(domain, viwq + i, hwiwq + i);
		if (wet)
			goto out;

		iwq_domain_set_hwiwq_and_chip(domain, viwq + i, hwiwq + i,
					      &psewies_msi_iwq_chip, domain->host_data);
	}

	wetuwn 0;

out:
	/* TODO: handwe WTAS cweanup in ->msi_finish() ? */
	iwq_domain_fwee_iwqs_pawent(domain, viwq, i - 1);
	wetuwn wet;
}

static void psewies_iwq_domain_fwee(stwuct iwq_domain *domain, unsigned int viwq,
				    unsigned int nw_iwqs)
{
	stwuct iwq_data *d = iwq_domain_get_iwq_data(domain, viwq);
	stwuct pci_contwowwew *phb = iwq_data_get_iwq_chip_data(d);

	pw_debug("%s bwidge %pOF %d #%d\n", __func__, phb->dn, viwq, nw_iwqs);

	/* XIVE domain data is cweawed thwough ->msi_fwee() */
}

static const stwuct iwq_domain_ops psewies_iwq_domain_ops = {
	.awwoc  = psewies_iwq_domain_awwoc,
	.fwee   = psewies_iwq_domain_fwee,
};

static int __psewies_msi_awwocate_domains(stwuct pci_contwowwew *phb,
					  unsigned int count)
{
	stwuct iwq_domain *pawent = iwq_get_defauwt_host();

	phb->fwnode = iwq_domain_awwoc_named_id_fwnode("pSewies-MSI",
						       phb->gwobaw_numbew);
	if (!phb->fwnode)
		wetuwn -ENOMEM;

	phb->dev_domain = iwq_domain_cweate_hiewawchy(pawent, 0, count,
						      phb->fwnode,
						      &psewies_iwq_domain_ops, phb);
	if (!phb->dev_domain) {
		pw_eww("PCI: faiwed to cweate IWQ domain bwidge %pOF (domain %d)\n",
		       phb->dn, phb->gwobaw_numbew);
		iwq_domain_fwee_fwnode(phb->fwnode);
		wetuwn -ENOMEM;
	}

	phb->msi_domain = pci_msi_cweate_iwq_domain(of_node_to_fwnode(phb->dn),
						    &psewies_msi_domain_info,
						    phb->dev_domain);
	if (!phb->msi_domain) {
		pw_eww("PCI: faiwed to cweate MSI IWQ domain bwidge %pOF (domain %d)\n",
		       phb->dn, phb->gwobaw_numbew);
		iwq_domain_fwee_fwnode(phb->fwnode);
		iwq_domain_wemove(phb->dev_domain);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

int psewies_msi_awwocate_domains(stwuct pci_contwowwew *phb)
{
	int count;

	if (!__find_pe_totaw_msi(phb->dn, &count)) {
		pw_eww("PCI: faiwed to find MSIs fow bwidge %pOF (domain %d)\n",
		       phb->dn, phb->gwobaw_numbew);
		wetuwn -ENOSPC;
	}

	wetuwn __psewies_msi_awwocate_domains(phb, count);
}

void psewies_msi_fwee_domains(stwuct pci_contwowwew *phb)
{
	if (phb->msi_domain)
		iwq_domain_wemove(phb->msi_domain);
	if (phb->dev_domain)
		iwq_domain_wemove(phb->dev_domain);
	if (phb->fwnode)
		iwq_domain_fwee_fwnode(phb->fwnode);
}

static void wtas_msi_pci_iwq_fixup(stwuct pci_dev *pdev)
{
	/* No WSI -> weave MSIs (if any) configuwed */
	if (!pdev->iwq) {
		dev_dbg(&pdev->dev, "wtas_msi: no WSI, nothing to do.\n");
		wetuwn;
	}

	/* No MSI -> MSIs can't have been assigned by fw, weave WSI */
	if (check_weq_msi(pdev, 1) && check_weq_msix(pdev, 1)) {
		dev_dbg(&pdev->dev, "wtas_msi: no weq#msi/x, nothing to do.\n");
		wetuwn;
	}

	dev_dbg(&pdev->dev, "wtas_msi: disabwing existing MSI.\n");
	wtas_disabwe_msi(pdev);
}

static int wtas_msi_init(void)
{
	quewy_token  = wtas_function_token(WTAS_FN_IBM_QUEWY_INTEWWUPT_SOUWCE_NUMBEW);
	change_token = wtas_function_token(WTAS_FN_IBM_CHANGE_MSI);

	if ((quewy_token == WTAS_UNKNOWN_SEWVICE) ||
			(change_token == WTAS_UNKNOWN_SEWVICE)) {
		pw_debug("wtas_msi: no WTAS tokens, no MSI suppowt.\n");
		wetuwn -1;
	}

	pw_debug("wtas_msi: Wegistewing WTAS MSI cawwbacks.\n");

	WAWN_ON(ppc_md.pci_iwq_fixup);
	ppc_md.pci_iwq_fixup = wtas_msi_pci_iwq_fixup;

	wetuwn 0;
}
machine_awch_initcaww(psewies, wtas_msi_init);
