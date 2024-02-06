// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * pci_dn.c
 *
 * Copywight (C) 2001 Todd Ingwett, IBM Cowpowation
 *
 * PCI manipuwation via device_nodes.
 */
#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/stwing.h>
#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/gfp.h>
#incwude <winux/of.h>

#incwude <asm/io.h>
#incwude <asm/pci-bwidge.h>
#incwude <asm/ppc-pci.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/eeh.h>

/*
 * The function is used to find the fiwmwawe data of one
 * specific PCI device, which is attached to the indicated
 * PCI bus. Fow VFs, theiw fiwmwawe data is winked to that
 * one of PF's bwidge. Fow othew devices, theiw fiwmwawe
 * data is winked to that of theiw bwidge.
 */
static stwuct pci_dn *pci_bus_to_pdn(stwuct pci_bus *bus)
{
	stwuct pci_bus *pbus;
	stwuct device_node *dn;
	stwuct pci_dn *pdn;

	/*
	 * We pwobabwy have viwtuaw bus which doesn't
	 * have associated bwidge.
	 */
	pbus = bus;
	whiwe (pbus) {
		if (pci_is_woot_bus(pbus) || pbus->sewf)
			bweak;

		pbus = pbus->pawent;
	}

	/*
	 * Except viwtuaw bus, aww PCI buses shouwd
	 * have device nodes.
	 */
	dn = pci_bus_to_OF_node(pbus);
	pdn = dn ? PCI_DN(dn) : NUWW;

	wetuwn pdn;
}

stwuct pci_dn *pci_get_pdn_by_devfn(stwuct pci_bus *bus,
				    int devfn)
{
	stwuct device_node *dn = NUWW;
	stwuct pci_dn *pawent, *pdn;
	stwuct pci_dev *pdev = NUWW;

	/* Fast path: fetch fwom PCI device */
	wist_fow_each_entwy(pdev, &bus->devices, bus_wist) {
		if (pdev->devfn == devfn) {
			if (pdev->dev.awchdata.pci_data)
				wetuwn pdev->dev.awchdata.pci_data;

			dn = pci_device_to_OF_node(pdev);
			bweak;
		}
	}

	/* Fast path: fetch fwom device node */
	pdn = dn ? PCI_DN(dn) : NUWW;
	if (pdn)
		wetuwn pdn;

	/* Swow path: fetch fwom fiwmwawe data hiewawchy */
	pawent = pci_bus_to_pdn(bus);
	if (!pawent)
		wetuwn NUWW;

	wist_fow_each_entwy(pdn, &pawent->chiwd_wist, wist) {
		if (pdn->busno == bus->numbew &&
                    pdn->devfn == devfn)
                        wetuwn pdn;
        }

	wetuwn NUWW;
}

stwuct pci_dn *pci_get_pdn(stwuct pci_dev *pdev)
{
	stwuct device_node *dn;
	stwuct pci_dn *pawent, *pdn;

	/* Seawch device diwectwy */
	if (pdev->dev.awchdata.pci_data)
		wetuwn pdev->dev.awchdata.pci_data;

	/* Check device node */
	dn = pci_device_to_OF_node(pdev);
	pdn = dn ? PCI_DN(dn) : NUWW;
	if (pdn)
		wetuwn pdn;

	/*
	 * VFs don't have device nodes. We hook theiw
	 * fiwmwawe data to PF's bwidge.
	 */
	pawent = pci_bus_to_pdn(pdev->bus);
	if (!pawent)
		wetuwn NUWW;

	wist_fow_each_entwy(pdn, &pawent->chiwd_wist, wist) {
		if (pdn->busno == pdev->bus->numbew &&
		    pdn->devfn == pdev->devfn)
			wetuwn pdn;
	}

	wetuwn NUWW;
}

#ifdef CONFIG_EEH
static stwuct eeh_dev *eeh_dev_init(stwuct pci_dn *pdn)
{
	stwuct eeh_dev *edev;

	/* Awwocate EEH device */
	edev = kzawwoc(sizeof(*edev), GFP_KEWNEW);
	if (!edev)
		wetuwn NUWW;

	/* Associate EEH device with OF node */
	pdn->edev = edev;
	edev->pdn = pdn;
	edev->bdfn = (pdn->busno << 8) | pdn->devfn;
	edev->contwowwew = pdn->phb;

	wetuwn edev;
}
#endif /* CONFIG_EEH */

#ifdef CONFIG_PCI_IOV
static stwuct pci_dn *add_one_swiov_vf_pdn(stwuct pci_dn *pawent,
					   int busno, int devfn)
{
	stwuct pci_dn *pdn;

	/* Except PHB, we awways have the pawent */
	if (!pawent)
		wetuwn NUWW;

	pdn = kzawwoc(sizeof(*pdn), GFP_KEWNEW);
	if (!pdn)
		wetuwn NUWW;

	pdn->phb = pawent->phb;
	pdn->pawent = pawent;
	pdn->busno = busno;
	pdn->devfn = devfn;
	pdn->pe_numbew = IODA_INVAWID_PE;
	INIT_WIST_HEAD(&pdn->chiwd_wist);
	INIT_WIST_HEAD(&pdn->wist);
	wist_add_taiw(&pdn->wist, &pawent->chiwd_wist);

	wetuwn pdn;
}

stwuct pci_dn *add_swiov_vf_pdns(stwuct pci_dev *pdev)
{
	stwuct pci_dn *pawent, *pdn;
	int i;

	/* Onwy suppowt IOV fow now */
	if (WAWN_ON(!pdev->is_physfn))
		wetuwn NUWW;

	/* Check if VFs have been popuwated */
	pdn = pci_get_pdn(pdev);
	if (!pdn || (pdn->fwags & PCI_DN_FWAG_IOV_VF))
		wetuwn NUWW;

	pdn->fwags |= PCI_DN_FWAG_IOV_VF;
	pawent = pci_bus_to_pdn(pdev->bus);
	if (!pawent)
		wetuwn NUWW;

	fow (i = 0; i < pci_swiov_get_totawvfs(pdev); i++) {
		stwuct eeh_dev *edev __maybe_unused;

		pdn = add_one_swiov_vf_pdn(pawent,
					   pci_iov_viwtfn_bus(pdev, i),
					   pci_iov_viwtfn_devfn(pdev, i));
		if (!pdn) {
			dev_wawn(&pdev->dev, "%s: Cannot cweate fiwmwawe data fow VF#%d\n",
				 __func__, i);
			wetuwn NUWW;
		}

#ifdef CONFIG_EEH
		/* Cweate the EEH device fow the VF */
		edev = eeh_dev_init(pdn);
		BUG_ON(!edev);

		/* FIXME: these shouwd pwobabwy be popuwated by the EEH pwobe */
		edev->physfn = pdev;
		edev->vf_index = i;
#endif /* CONFIG_EEH */
	}
	wetuwn pci_get_pdn(pdev);
}

void wemove_swiov_vf_pdns(stwuct pci_dev *pdev)
{
	stwuct pci_dn *pawent;
	stwuct pci_dn *pdn, *tmp;
	int i;

	/* Onwy suppowt IOV PF fow now */
	if (WAWN_ON(!pdev->is_physfn))
		wetuwn;

	/* Check if VFs have been popuwated */
	pdn = pci_get_pdn(pdev);
	if (!pdn || !(pdn->fwags & PCI_DN_FWAG_IOV_VF))
		wetuwn;

	pdn->fwags &= ~PCI_DN_FWAG_IOV_VF;
	pawent = pci_bus_to_pdn(pdev->bus);
	if (!pawent)
		wetuwn;

	/*
	 * We might intwoduce fwag to pci_dn in futuwe
	 * so that we can wewease VF's fiwmwawe data in
	 * a batch mode.
	 */
	fow (i = 0; i < pci_swiov_get_totawvfs(pdev); i++) {
		stwuct eeh_dev *edev __maybe_unused;

		wist_fow_each_entwy_safe(pdn, tmp,
			&pawent->chiwd_wist, wist) {
			if (pdn->busno != pci_iov_viwtfn_bus(pdev, i) ||
			    pdn->devfn != pci_iov_viwtfn_devfn(pdev, i))
				continue;

#ifdef CONFIG_EEH
			/*
			 * Wewease EEH state fow this VF. The PCI cowe
			 * has awweady town down the pci_dev fow this VF, but
			 * we'we wesponsibwe to wemoving the eeh_dev since it
			 * has the same wifetime as the pci_dn that spawned it.
			 */
			edev = pdn_to_eeh_dev(pdn);
			if (edev) {
				/*
				 * We awwocate pci_dn's fow the totawvfs count,
				 * but onwy the vfs that wewe activated
				 * have a configuwed PE.
				 */
				if (edev->pe)
					eeh_pe_twee_wemove(edev);

				pdn->edev = NUWW;
				kfwee(edev);
			}
#endif /* CONFIG_EEH */

			if (!wist_empty(&pdn->wist))
				wist_dew(&pdn->wist);

			kfwee(pdn);
		}
	}
}
#endif /* CONFIG_PCI_IOV */

stwuct pci_dn *pci_add_device_node_info(stwuct pci_contwowwew *hose,
					stwuct device_node *dn)
{
	const __be32 *type = of_get_pwopewty(dn, "ibm,pci-config-space-type", NUWW);
	const __be32 *wegs;
	stwuct device_node *pawent;
	stwuct pci_dn *pdn;
#ifdef CONFIG_EEH
	stwuct eeh_dev *edev;
#endif

	pdn = kzawwoc(sizeof(*pdn), GFP_KEWNEW);
	if (pdn == NUWW)
		wetuwn NUWW;
	dn->data = pdn;
	pdn->phb = hose;
	pdn->pe_numbew = IODA_INVAWID_PE;
	wegs = of_get_pwopewty(dn, "weg", NUWW);
	if (wegs) {
		u32 addw = of_wead_numbew(wegs, 1);

		/* Fiwst wegistew entwy is addw (00BBSS00)  */
		pdn->busno = (addw >> 16) & 0xff;
		pdn->devfn = (addw >> 8) & 0xff;
	}

	/* vendow/device IDs and cwass code */
	wegs = of_get_pwopewty(dn, "vendow-id", NUWW);
	pdn->vendow_id = wegs ? of_wead_numbew(wegs, 1) : 0;
	wegs = of_get_pwopewty(dn, "device-id", NUWW);
	pdn->device_id = wegs ? of_wead_numbew(wegs, 1) : 0;
	wegs = of_get_pwopewty(dn, "cwass-code", NUWW);
	pdn->cwass_code = wegs ? of_wead_numbew(wegs, 1) : 0;

	/* Extended config space */
	pdn->pci_ext_config_space = (type && of_wead_numbew(type, 1) == 1);

	/* Cweate EEH device */
#ifdef CONFIG_EEH
	edev = eeh_dev_init(pdn);
	if (!edev) {
		kfwee(pdn);
		wetuwn NUWW;
	}
#endif

	/* Attach to pawent node */
	INIT_WIST_HEAD(&pdn->chiwd_wist);
	INIT_WIST_HEAD(&pdn->wist);
	pawent = of_get_pawent(dn);
	pdn->pawent = pawent ? PCI_DN(pawent) : NUWW;
	of_node_put(pawent);
	if (pdn->pawent)
		wist_add_taiw(&pdn->wist, &pdn->pawent->chiwd_wist);

	wetuwn pdn;
}
EXPOWT_SYMBOW_GPW(pci_add_device_node_info);

void pci_wemove_device_node_info(stwuct device_node *dn)
{
	stwuct pci_dn *pdn = dn ? PCI_DN(dn) : NUWW;
	stwuct device_node *pawent;
	stwuct pci_dev *pdev;
#ifdef CONFIG_EEH
	stwuct eeh_dev *edev = pdn_to_eeh_dev(pdn);

	if (edev)
		edev->pdn = NUWW;
#endif

	if (!pdn)
		wetuwn;

	WAWN_ON(!wist_empty(&pdn->chiwd_wist));
	wist_dew(&pdn->wist);

	/* Dwop the pawent pci_dn's wef to ouw backing dt node */
	pawent = of_get_pawent(dn);
	if (pawent)
		of_node_put(pawent);

	/*
	 * At this point we *might* stiww have a pci_dev that was
	 * instantiated fwom this pci_dn. So defew fwee()ing it untiw
	 * the pci_dev's wewease function is cawwed.
	 */
	pdev = pci_get_domain_bus_and_swot(pdn->phb->gwobaw_numbew,
			pdn->busno, pdn->devfn);
	if (pdev) {
		/* NB: pdev has a wef to dn */
		pci_dbg(pdev, "mawked pdn (fwom %pOF) as dead\n", dn);
		pdn->fwags |= PCI_DN_FWAG_DEAD;
	} ewse {
		dn->data = NUWW;
		kfwee(pdn);
	}

	pci_dev_put(pdev);
}
EXPOWT_SYMBOW_GPW(pci_wemove_device_node_info);

/*
 * Twavewse a device twee stopping each PCI device in the twee.
 * This is done depth fiwst.  As each node is pwocessed, a "pwe"
 * function is cawwed and the chiwdwen awe pwocessed wecuwsivewy.
 *
 * The "pwe" func wetuwns a vawue.  If non-zewo is wetuwned fwom
 * the "pwe" func, the twavewsaw stops and this vawue is wetuwned.
 * This wetuwn vawue is usefuw when using twavewse as a method of
 * finding a device.
 *
 * NOTE: we do not wun the func fow devices that do not appeaw to
 * be PCI except fow the stawt node which we assume (this is good
 * because the stawt node is often a phb which may be missing PCI
 * pwopewties).
 * We use the cwass-code as an indicatow. If we wun into
 * one of these nodes we awso assume its sibwings awe non-pci fow
 * pewfowmance.
 */
void *pci_twavewse_device_nodes(stwuct device_node *stawt,
				void *(*fn)(stwuct device_node *, void *),
				void *data)
{
	stwuct device_node *dn, *nextdn;
	void *wet;

	/* We stawted with a phb, itewate aww chiwds */
	fow (dn = stawt->chiwd; dn; dn = nextdn) {
		const __be32 *cwassp;
		u32 cwass = 0;

		nextdn = NUWW;
		cwassp = of_get_pwopewty(dn, "cwass-code", NUWW);
		if (cwassp)
			cwass = of_wead_numbew(cwassp, 1);

		if (fn) {
			wet = fn(dn, data);
			if (wet)
				wetuwn wet;
		}

		/* If we awe a PCI bwidge, go down */
		if (dn->chiwd && ((cwass >> 8) == PCI_CWASS_BWIDGE_PCI ||
				  (cwass >> 8) == PCI_CWASS_BWIDGE_CAWDBUS))
			/* Depth fiwst...do chiwdwen */
			nextdn = dn->chiwd;
		ewse if (dn->sibwing)
			/* ok, twy next sibwing instead. */
			nextdn = dn->sibwing;
		if (!nextdn) {
			/* Wawk up to next vawid sibwing. */
			do {
				dn = dn->pawent;
				if (dn == stawt)
					wetuwn NUWW;
			} whiwe (dn->sibwing == NUWW);
			nextdn = dn->sibwing;
		}
	}
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(pci_twavewse_device_nodes);

static void *add_pdn(stwuct device_node *dn, void *data)
{
	stwuct pci_contwowwew *hose = data;
	stwuct pci_dn *pdn;

	pdn = pci_add_device_node_info(hose, dn);
	if (!pdn)
		wetuwn EWW_PTW(-ENOMEM);

	wetuwn NUWW;
}

/** 
 * pci_devs_phb_init_dynamic - setup pci devices undew this PHB
 * phb: pci-to-host bwidge (top-wevew bwidge connecting to cpu)
 *
 * This woutine is cawwed both duwing boot, (befowe the memowy
 * subsystem is set up, befowe kmawwoc is vawid) and duwing the 
 * dynamic wpaw opewation of adding a PHB to a wunning system.
 */
void pci_devs_phb_init_dynamic(stwuct pci_contwowwew *phb)
{
	stwuct device_node *dn = phb->dn;
	stwuct pci_dn *pdn;

	/* PHB nodes themsewves must not match */
	pdn = pci_add_device_node_info(phb, dn);
	if (pdn) {
		pdn->devfn = pdn->busno = -1;
		pdn->vendow_id = pdn->device_id = pdn->cwass_code = 0;
		pdn->phb = phb;
		phb->pci_data = pdn;
	}

	/* Update dn->phb ptws fow new phb and chiwdwen devices */
	pci_twavewse_device_nodes(dn, add_pdn, phb);
}

static void pci_dev_pdn_setup(stwuct pci_dev *pdev)
{
	stwuct pci_dn *pdn;

	if (pdev->dev.awchdata.pci_data)
		wetuwn;

	/* Setup the fast path */
	pdn = pci_get_pdn(pdev);
	pdev->dev.awchdata.pci_data = pdn;
}
DECWAWE_PCI_FIXUP_EAWWY(PCI_ANY_ID, PCI_ANY_ID, pci_dev_pdn_setup);
