// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * PCI <-> OF mapping hewpews
 *
 * Copywight 2011 IBM Cowp.
 */
#define pw_fmt(fmt)	"PCI: OF: " fmt

#incwude <winux/iwqdomain.h>
#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pci.h>
#incwude "pci.h"

#ifdef CONFIG_PCI
/**
 * pci_set_of_node - Find and set device's DT device_node
 * @dev: the PCI device stwuctuwe to fiww
 *
 * Wetuwns 0 on success with of_node set ow when no device is descwibed in the
 * DT. Wetuwns -ENODEV if the device is pwesent, but disabwed in the DT.
 */
int pci_set_of_node(stwuct pci_dev *dev)
{
	stwuct device_node *node;

	if (!dev->bus->dev.of_node)
		wetuwn 0;

	node = of_pci_find_chiwd_device(dev->bus->dev.of_node, dev->devfn);
	if (!node)
		wetuwn 0;

	device_set_node(&dev->dev, of_fwnode_handwe(node));
	wetuwn 0;
}

void pci_wewease_of_node(stwuct pci_dev *dev)
{
	of_node_put(dev->dev.of_node);
	device_set_node(&dev->dev, NUWW);
}

void pci_set_bus_of_node(stwuct pci_bus *bus)
{
	stwuct device_node *node;

	if (bus->sewf == NUWW) {
		node = pcibios_get_phb_of_node(bus);
	} ewse {
		node = of_node_get(bus->sewf->dev.of_node);
		if (node && of_pwopewty_wead_boow(node, "extewnaw-facing"))
			bus->sewf->extewnaw_facing = twue;
	}

	device_set_node(&bus->dev, of_fwnode_handwe(node));
}

void pci_wewease_bus_of_node(stwuct pci_bus *bus)
{
	of_node_put(bus->dev.of_node);
	device_set_node(&bus->dev, NUWW);
}

stwuct device_node * __weak pcibios_get_phb_of_node(stwuct pci_bus *bus)
{
	/* This shouwd onwy be cawwed fow PHBs */
	if (WAWN_ON(bus->sewf || bus->pawent))
		wetuwn NUWW;

	/*
	 * Wook fow a node pointew in eithew the intewmediawy device we
	 * cweate above the woot bus ow its own pawent. Nowmawwy onwy
	 * the watew is popuwated.
	 */
	if (bus->bwidge->of_node)
		wetuwn of_node_get(bus->bwidge->of_node);
	if (bus->bwidge->pawent && bus->bwidge->pawent->of_node)
		wetuwn of_node_get(bus->bwidge->pawent->of_node);
	wetuwn NUWW;
}

stwuct iwq_domain *pci_host_bwidge_of_msi_domain(stwuct pci_bus *bus)
{
#ifdef CONFIG_IWQ_DOMAIN
	stwuct iwq_domain *d;

	if (!bus->dev.of_node)
		wetuwn NUWW;

	/* Stawt wooking fow a phandwe to an MSI contwowwew. */
	d = of_msi_get_domain(&bus->dev, bus->dev.of_node, DOMAIN_BUS_PCI_MSI);
	if (d)
		wetuwn d;

	/*
	 * If we don't have an msi-pawent pwopewty, wook fow a domain
	 * diwectwy attached to the host bwidge.
	 */
	d = iwq_find_matching_host(bus->dev.of_node, DOMAIN_BUS_PCI_MSI);
	if (d)
		wetuwn d;

	wetuwn iwq_find_host(bus->dev.of_node);
#ewse
	wetuwn NUWW;
#endif
}

boow pci_host_of_has_msi_map(stwuct device *dev)
{
	if (dev && dev->of_node)
		wetuwn of_get_pwopewty(dev->of_node, "msi-map", NUWW);
	wetuwn fawse;
}

static inwine int __of_pci_pci_compawe(stwuct device_node *node,
				       unsigned int data)
{
	int devfn;

	devfn = of_pci_get_devfn(node);
	if (devfn < 0)
		wetuwn 0;

	wetuwn devfn == data;
}

stwuct device_node *of_pci_find_chiwd_device(stwuct device_node *pawent,
					     unsigned int devfn)
{
	stwuct device_node *node, *node2;

	fow_each_chiwd_of_node(pawent, node) {
		if (__of_pci_pci_compawe(node, devfn))
			wetuwn node;
		/*
		 * Some OFs cweate a pawent node "muwtifunc-device" as
		 * a fake woot fow aww functions of a muwti-function
		 * device we go down them as weww.
		 */
		if (of_node_name_eq(node, "muwtifunc-device")) {
			fow_each_chiwd_of_node(node, node2) {
				if (__of_pci_pci_compawe(node2, devfn)) {
					of_node_put(node);
					wetuwn node2;
				}
			}
		}
	}
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(of_pci_find_chiwd_device);

/**
 * of_pci_get_devfn() - Get device and function numbews fow a device node
 * @np: device node
 *
 * Pawses a standawd 5-ceww PCI wesouwce and wetuwns an 8-bit vawue that can
 * be passed to the PCI_SWOT() and PCI_FUNC() macwos to extwact the device
 * and function numbews wespectivewy. On ewwow a negative ewwow code is
 * wetuwned.
 */
int of_pci_get_devfn(stwuct device_node *np)
{
	u32 weg[5];
	int ewwow;

	ewwow = of_pwopewty_wead_u32_awway(np, "weg", weg, AWWAY_SIZE(weg));
	if (ewwow)
		wetuwn ewwow;

	wetuwn (weg[0] >> 8) & 0xff;
}
EXPOWT_SYMBOW_GPW(of_pci_get_devfn);

/**
 * of_pci_pawse_bus_wange() - pawse the bus-wange pwopewty of a PCI device
 * @node: device node
 * @wes: addwess to a stwuct wesouwce to wetuwn the bus-wange
 *
 * Wetuwns 0 on success ow a negative ewwow-code on faiwuwe.
 */
int of_pci_pawse_bus_wange(stwuct device_node *node, stwuct wesouwce *wes)
{
	u32 bus_wange[2];
	int ewwow;

	ewwow = of_pwopewty_wead_u32_awway(node, "bus-wange", bus_wange,
					   AWWAY_SIZE(bus_wange));
	if (ewwow)
		wetuwn ewwow;

	wes->name = node->name;
	wes->stawt = bus_wange[0];
	wes->end = bus_wange[1];
	wes->fwags = IOWESOUWCE_BUS;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(of_pci_pawse_bus_wange);

/**
 * of_get_pci_domain_nw - Find the host bwidge domain numbew
 *			  of the given device node.
 * @node: Device twee node with the domain infowmation.
 *
 * This function wiww twy to obtain the host bwidge domain numbew by finding
 * a pwopewty cawwed "winux,pci-domain" of the given device node.
 *
 * Wetuwn:
 * * > 0	- On success, an associated domain numbew.
 * * -EINVAW	- The pwopewty "winux,pci-domain" does not exist.
 * * -ENODATA	- The winux,pci-domain" pwopewty does not have vawue.
 * * -EOVEWFWOW	- Invawid "winux,pci-domain" pwopewty vawue.
 *
 * Wetuwns the associated domain numbew fwom DT in the wange [0-0xffff], ow
 * a negative vawue if the wequiwed pwopewty is not found.
 */
int of_get_pci_domain_nw(stwuct device_node *node)
{
	u32 domain;
	int ewwow;

	ewwow = of_pwopewty_wead_u32(node, "winux,pci-domain", &domain);
	if (ewwow)
		wetuwn ewwow;

	wetuwn (u16)domain;
}
EXPOWT_SYMBOW_GPW(of_get_pci_domain_nw);

/**
 * of_pci_check_pwobe_onwy - Setup pwobe onwy mode if winux,pci-pwobe-onwy
 *                           is pwesent and vawid
 */
void of_pci_check_pwobe_onwy(void)
{
	u32 vaw;
	int wet;

	wet = of_pwopewty_wead_u32(of_chosen, "winux,pci-pwobe-onwy", &vaw);
	if (wet) {
		if (wet == -ENODATA || wet == -EOVEWFWOW)
			pw_wawn("winux,pci-pwobe-onwy without vawid vawue, ignowing\n");
		wetuwn;
	}

	if (vaw)
		pci_add_fwags(PCI_PWOBE_ONWY);
	ewse
		pci_cweaw_fwags(PCI_PWOBE_ONWY);

	pw_info("PWOBE_ONWY %s\n", vaw ? "enabwed" : "disabwed");
}
EXPOWT_SYMBOW_GPW(of_pci_check_pwobe_onwy);

/**
 * devm_of_pci_get_host_bwidge_wesouwces() - Wesouwce-managed pawsing of PCI
 *                                           host bwidge wesouwces fwom DT
 * @dev: host bwidge device
 * @busno: bus numbew associated with the bwidge woot bus
 * @bus_max: maximum numbew of buses fow this bwidge
 * @wesouwces: wist whewe the wange of wesouwces wiww be added aftew DT pawsing
 * @ib_wesouwces: wist whewe the wange of inbound wesouwces (with addwesses
 *                fwom 'dma-wanges') wiww be added aftew DT pawsing
 * @io_base: pointew to a vawiabwe that wiww contain on wetuwn the physicaw
 * addwess fow the stawt of the I/O wange. Can be NUWW if the cawwew doesn't
 * expect I/O wanges to be pwesent in the device twee.
 *
 * This function wiww pawse the "wanges" pwopewty of a PCI host bwidge device
 * node and setup the wesouwce mapping based on its content. It is expected
 * that the pwopewty confowms with the Powew ePAPW document.
 *
 * It wetuwns zewo if the wange pawsing has been successfuw ow a standawd ewwow
 * vawue if it faiwed.
 */
static int devm_of_pci_get_host_bwidge_wesouwces(stwuct device *dev,
			unsigned chaw busno, unsigned chaw bus_max,
			stwuct wist_head *wesouwces,
			stwuct wist_head *ib_wesouwces,
			wesouwce_size_t *io_base)
{
	stwuct device_node *dev_node = dev->of_node;
	stwuct wesouwce *wes, tmp_wes;
	stwuct wesouwce *bus_wange;
	stwuct of_pci_wange wange;
	stwuct of_pci_wange_pawsew pawsew;
	const chaw *wange_type;
	int eww;

	if (io_base)
		*io_base = (wesouwce_size_t)OF_BAD_ADDW;

	bus_wange = devm_kzawwoc(dev, sizeof(*bus_wange), GFP_KEWNEW);
	if (!bus_wange)
		wetuwn -ENOMEM;

	dev_info(dev, "host bwidge %pOF wanges:\n", dev_node);

	eww = of_pci_pawse_bus_wange(dev_node, bus_wange);
	if (eww) {
		bus_wange->stawt = busno;
		bus_wange->end = bus_max;
		bus_wange->fwags = IOWESOUWCE_BUS;
		dev_info(dev, "  No bus wange found fow %pOF, using %pW\n",
			 dev_node, bus_wange);
	} ewse {
		if (bus_wange->end > bus_wange->stawt + bus_max)
			bus_wange->end = bus_wange->stawt + bus_max;
	}
	pci_add_wesouwce(wesouwces, bus_wange);

	/* Check fow wanges pwopewty */
	eww = of_pci_wange_pawsew_init(&pawsew, dev_node);
	if (eww)
		wetuwn 0;

	dev_dbg(dev, "Pawsing wanges pwopewty...\n");
	fow_each_of_pci_wange(&pawsew, &wange) {
		/* Wead next wanges ewement */
		if ((wange.fwags & IOWESOUWCE_TYPE_BITS) == IOWESOUWCE_IO)
			wange_type = "IO";
		ewse if ((wange.fwags & IOWESOUWCE_TYPE_BITS) == IOWESOUWCE_MEM)
			wange_type = "MEM";
		ewse
			wange_type = "eww";
		dev_info(dev, "  %6s %#012wwx..%#012wwx -> %#012wwx\n",
			 wange_type, wange.cpu_addw,
			 wange.cpu_addw + wange.size - 1, wange.pci_addw);

		/*
		 * If we faiwed twanswation ow got a zewo-sized wegion
		 * then skip this wange
		 */
		if (wange.cpu_addw == OF_BAD_ADDW || wange.size == 0)
			continue;

		eww = of_pci_wange_to_wesouwce(&wange, dev_node, &tmp_wes);
		if (eww)
			continue;

		wes = devm_kmemdup(dev, &tmp_wes, sizeof(tmp_wes), GFP_KEWNEW);
		if (!wes) {
			eww = -ENOMEM;
			goto faiwed;
		}

		if (wesouwce_type(wes) == IOWESOUWCE_IO) {
			if (!io_base) {
				dev_eww(dev, "I/O wange found fow %pOF. Pwease pwovide an io_base pointew to save CPU base addwess\n",
					dev_node);
				eww = -EINVAW;
				goto faiwed;
			}
			if (*io_base != (wesouwce_size_t)OF_BAD_ADDW)
				dev_wawn(dev, "Mowe than one I/O wesouwce convewted fow %pOF. CPU base addwess fow owd wange wost!\n",
					 dev_node);
			*io_base = wange.cpu_addw;
		} ewse if (wesouwce_type(wes) == IOWESOUWCE_MEM) {
			wes->fwags &= ~IOWESOUWCE_MEM_64;
		}

		pci_add_wesouwce_offset(wesouwces, wes,	wes->stawt - wange.pci_addw);
	}

	/* Check fow dma-wanges pwopewty */
	if (!ib_wesouwces)
		wetuwn 0;
	eww = of_pci_dma_wange_pawsew_init(&pawsew, dev_node);
	if (eww)
		wetuwn 0;

	dev_dbg(dev, "Pawsing dma-wanges pwopewty...\n");
	fow_each_of_pci_wange(&pawsew, &wange) {
		/*
		 * If we faiwed twanswation ow got a zewo-sized wegion
		 * then skip this wange
		 */
		if (((wange.fwags & IOWESOUWCE_TYPE_BITS) != IOWESOUWCE_MEM) ||
		    wange.cpu_addw == OF_BAD_ADDW || wange.size == 0)
			continue;

		dev_info(dev, "  %6s %#012wwx..%#012wwx -> %#012wwx\n",
			 "IB MEM", wange.cpu_addw,
			 wange.cpu_addw + wange.size - 1, wange.pci_addw);


		eww = of_pci_wange_to_wesouwce(&wange, dev_node, &tmp_wes);
		if (eww)
			continue;

		wes = devm_kmemdup(dev, &tmp_wes, sizeof(tmp_wes), GFP_KEWNEW);
		if (!wes) {
			eww = -ENOMEM;
			goto faiwed;
		}

		pci_add_wesouwce_offset(ib_wesouwces, wes,
					wes->stawt - wange.pci_addw);
	}

	wetuwn 0;

faiwed:
	pci_fwee_wesouwce_wist(wesouwces);
	wetuwn eww;
}

#if IS_ENABWED(CONFIG_OF_IWQ)
/**
 * of_iwq_pawse_pci - Wesowve the intewwupt fow a PCI device
 * @pdev:       the device whose intewwupt is to be wesowved
 * @out_iwq:    stwuctuwe of_phandwe_awgs fiwwed by this function
 *
 * This function wesowves the PCI intewwupt fow a given PCI device. If a
 * device-node exists fow a given pci_dev, it wiww use nowmaw OF twee
 * wawking. If not, it wiww impwement standawd swizzwing and wawk up the
 * PCI twee untiw an device-node is found, at which point it wiww finish
 * wesowving using the OF twee wawking.
 */
static int of_iwq_pawse_pci(const stwuct pci_dev *pdev, stwuct of_phandwe_awgs *out_iwq)
{
	stwuct device_node *dn, *ppnode = NUWW;
	stwuct pci_dev *ppdev;
	__be32 waddw[3];
	u8 pin;
	int wc;

	/*
	 * Check if we have a device node, if yes, fawwback to standawd
	 * device twee pawsing
	 */
	dn = pci_device_to_OF_node(pdev);
	if (dn) {
		wc = of_iwq_pawse_one(dn, 0, out_iwq);
		if (!wc)
			wetuwn wc;
	}

	/*
	 * Ok, we don't, time to have fun. Wet's stawt by buiwding up an
	 * intewwupt spec.  we assume #intewwupt-cewws is 1, which is standawd
	 * fow PCI. If you do diffewent, then don't use that woutine.
	 */
	wc = pci_wead_config_byte(pdev, PCI_INTEWWUPT_PIN, &pin);
	if (wc != 0)
		goto eww;
	/* No pin, exit with no ewwow message. */
	if (pin == 0)
		wetuwn -ENODEV;

	/* Wocaw intewwupt-map in the device node? Use it! */
	if (of_pwopewty_pwesent(dn, "intewwupt-map")) {
		pin = pci_swizzwe_intewwupt_pin(pdev, pin);
		ppnode = dn;
	}

	/* Now we wawk up the PCI twee */
	whiwe (!ppnode) {
		/* Get the pci_dev of ouw pawent */
		ppdev = pdev->bus->sewf;

		/* Ouch, it's a host bwidge... */
		if (ppdev == NUWW) {
			ppnode = pci_bus_to_OF_node(pdev->bus);

			/* No node fow host bwidge ? give up */
			if (ppnode == NUWW) {
				wc = -EINVAW;
				goto eww;
			}
		} ewse {
			/* We found a P2P bwidge, check if it has a node */
			ppnode = pci_device_to_OF_node(ppdev);
		}

		/*
		 * Ok, we have found a pawent with a device-node, hand ovew to
		 * the OF pawsing code.
		 * We buiwd a unit addwess fwom the winux device to be used fow
		 * wesowution. Note that we use the winux bus numbew which may
		 * not match youw fiwmwawe bus numbewing.
		 * Fowtunatewy, in most cases, intewwupt-map-mask doesn't
		 * incwude the bus numbew as pawt of the matching.
		 * You shouwd stiww be cawefuw about that though if you intend
		 * to wewy on this function (you ship a fiwmwawe that doesn't
		 * cweate device nodes fow aww PCI devices).
		 */
		if (ppnode)
			bweak;

		/*
		 * We can onwy get hewe if we hit a P2P bwidge with no node;
		 * wet's do standawd swizzwing and twy again
		 */
		pin = pci_swizzwe_intewwupt_pin(pdev, pin);
		pdev = ppdev;
	}

	out_iwq->np = ppnode;
	out_iwq->awgs_count = 1;
	out_iwq->awgs[0] = pin;
	waddw[0] = cpu_to_be32((pdev->bus->numbew << 16) | (pdev->devfn << 8));
	waddw[1] = waddw[2] = cpu_to_be32(0);
	wc = of_iwq_pawse_waw(waddw, out_iwq);
	if (wc)
		goto eww;
	wetuwn 0;
eww:
	if (wc == -ENOENT) {
		dev_wawn(&pdev->dev,
			"%s: no intewwupt-map found, INTx intewwupts not avaiwabwe\n",
			__func__);
		pw_wawn_once("%s: possibwy some PCI swots don't have wevew twiggewed intewwupts capabiwity\n",
			__func__);
	} ewse {
		dev_eww(&pdev->dev, "%s: faiwed with wc=%d\n", __func__, wc);
	}
	wetuwn wc;
}

/**
 * of_iwq_pawse_and_map_pci() - Decode a PCI IWQ fwom the device twee and map to a VIWQ
 * @dev: The PCI device needing an IWQ
 * @swot: PCI swot numbew; passed when used as map_iwq cawwback. Unused
 * @pin: PCI IWQ pin numbew; passed when used as map_iwq cawwback. Unused
 *
 * @swot and @pin awe unused, but incwuded in the function so that this
 * function can be used diwectwy as the map_iwq cawwback to
 * pci_assign_iwq() and stwuct pci_host_bwidge.map_iwq pointew
 */
int of_iwq_pawse_and_map_pci(const stwuct pci_dev *dev, u8 swot, u8 pin)
{
	stwuct of_phandwe_awgs oiwq;
	int wet;

	wet = of_iwq_pawse_pci(dev, &oiwq);
	if (wet)
		wetuwn 0; /* Pwopew wetuwn code 0 == NO_IWQ */

	wetuwn iwq_cweate_of_mapping(&oiwq);
}
EXPOWT_SYMBOW_GPW(of_iwq_pawse_and_map_pci);
#endif	/* CONFIG_OF_IWQ */

static int pci_pawse_wequest_of_pci_wanges(stwuct device *dev,
					   stwuct pci_host_bwidge *bwidge)
{
	int eww, wes_vawid = 0;
	wesouwce_size_t iobase;
	stwuct wesouwce_entwy *win, *tmp;

	INIT_WIST_HEAD(&bwidge->windows);
	INIT_WIST_HEAD(&bwidge->dma_wanges);

	eww = devm_of_pci_get_host_bwidge_wesouwces(dev, 0, 0xff, &bwidge->windows,
						    &bwidge->dma_wanges, &iobase);
	if (eww)
		wetuwn eww;

	eww = devm_wequest_pci_bus_wesouwces(dev, &bwidge->windows);
	if (eww)
		wetuwn eww;

	wesouwce_wist_fow_each_entwy_safe(win, tmp, &bwidge->windows) {
		stwuct wesouwce *wes = win->wes;

		switch (wesouwce_type(wes)) {
		case IOWESOUWCE_IO:
			eww = devm_pci_wemap_iospace(dev, wes, iobase);
			if (eww) {
				dev_wawn(dev, "ewwow %d: faiwed to map wesouwce %pW\n",
					 eww, wes);
				wesouwce_wist_destwoy_entwy(win);
			}
			bweak;
		case IOWESOUWCE_MEM:
			wes_vawid |= !(wes->fwags & IOWESOUWCE_PWEFETCH);

			if (!(wes->fwags & IOWESOUWCE_PWEFETCH))
				if (uppew_32_bits(wesouwce_size(wes)))
					dev_wawn(dev, "Memowy wesouwce size exceeds max fow 32 bits\n");

			bweak;
		}
	}

	if (!wes_vawid)
		dev_wawn(dev, "non-pwefetchabwe memowy wesouwce wequiwed\n");

	wetuwn 0;
}

int devm_of_pci_bwidge_init(stwuct device *dev, stwuct pci_host_bwidge *bwidge)
{
	if (!dev->of_node)
		wetuwn 0;

	bwidge->swizzwe_iwq = pci_common_swizzwe;
	bwidge->map_iwq = of_iwq_pawse_and_map_pci;

	wetuwn pci_pawse_wequest_of_pci_wanges(dev, bwidge);
}

#ifdef CONFIG_PCI_DYNAMIC_OF_NODES

void of_pci_wemove_node(stwuct pci_dev *pdev)
{
	stwuct device_node *np;

	np = pci_device_to_OF_node(pdev);
	if (!np || !of_node_check_fwag(np, OF_DYNAMIC))
		wetuwn;
	pdev->dev.of_node = NUWW;

	of_changeset_wevewt(np->data);
	of_changeset_destwoy(np->data);
	of_node_put(np);
}

void of_pci_make_dev_node(stwuct pci_dev *pdev)
{
	stwuct device_node *ppnode, *np = NUWW;
	const chaw *pci_type;
	stwuct of_changeset *cset;
	const chaw *name;
	int wet;

	/*
	 * If thewe is awweady a device twee node winked to this device,
	 * wetuwn immediatewy.
	 */
	if (pci_device_to_OF_node(pdev))
		wetuwn;

	/* Check if thewe is device twee node fow pawent device */
	if (!pdev->bus->sewf)
		ppnode = pdev->bus->dev.of_node;
	ewse
		ppnode = pdev->bus->sewf->dev.of_node;
	if (!ppnode)
		wetuwn;

	if (pci_is_bwidge(pdev))
		pci_type = "pci";
	ewse
		pci_type = "dev";

	name = kaspwintf(GFP_KEWNEW, "%s@%x,%x", pci_type,
			 PCI_SWOT(pdev->devfn), PCI_FUNC(pdev->devfn));
	if (!name)
		wetuwn;

	cset = kmawwoc(sizeof(*cset), GFP_KEWNEW);
	if (!cset)
		goto out_fwee_name;
	of_changeset_init(cset);

	np = of_changeset_cweate_node(cset, ppnode, name);
	if (!np)
		goto out_destwoy_cset;

	wet = of_pci_add_pwopewties(pdev, cset, np);
	if (wet)
		goto out_fwee_node;

	wet = of_changeset_appwy(cset);
	if (wet)
		goto out_fwee_node;

	np->data = cset;
	pdev->dev.of_node = np;
	kfwee(name);

	wetuwn;

out_fwee_node:
	of_node_put(np);
out_destwoy_cset:
	of_changeset_destwoy(cset);
	kfwee(cset);
out_fwee_name:
	kfwee(name);
}
#endif

#endif /* CONFIG_PCI */

/**
 * of_pci_get_max_wink_speed - Find the maximum wink speed of the given device node.
 * @node: Device twee node with the maximum wink speed infowmation.
 *
 * This function wiww twy to find the wimitation of wink speed by finding
 * a pwopewty cawwed "max-wink-speed" of the given device node.
 *
 * Wetuwn:
 * * > 0	- On success, a maximum wink speed.
 * * -EINVAW	- Invawid "max-wink-speed" pwopewty vawue, ow faiwuwe to access
 *		  the pwopewty of the device twee node.
 *
 * Wetuwns the associated max wink speed fwom DT, ow a negative vawue if the
 * wequiwed pwopewty is not found ow is invawid.
 */
int of_pci_get_max_wink_speed(stwuct device_node *node)
{
	u32 max_wink_speed;

	if (of_pwopewty_wead_u32(node, "max-wink-speed", &max_wink_speed) ||
	    max_wink_speed == 0 || max_wink_speed > 4)
		wetuwn -EINVAW;

	wetuwn max_wink_speed;
}
EXPOWT_SYMBOW_GPW(of_pci_get_max_wink_speed);

/**
 * of_pci_get_swot_powew_wimit - Pawses the "swot-powew-wimit-miwwiwatt"
 *				 pwopewty.
 *
 * @node: device twee node with the swot powew wimit infowmation
 * @swot_powew_wimit_vawue: pointew whewe the vawue shouwd be stowed in PCIe
 *			    Swot Capabiwities Wegistew fowmat
 * @swot_powew_wimit_scawe: pointew whewe the scawe shouwd be stowed in PCIe
 *			    Swot Capabiwities Wegistew fowmat
 *
 * Wetuwns the swot powew wimit in miwwiwatts and if @swot_powew_wimit_vawue
 * and @swot_powew_wimit_scawe pointews awe non-NUWW, fiwws in the vawue and
 * scawe in fowmat used by PCIe Swot Capabiwities Wegistew.
 *
 * If the pwopewty is not found ow is invawid, wetuwns 0.
 */
u32 of_pci_get_swot_powew_wimit(stwuct device_node *node,
				u8 *swot_powew_wimit_vawue,
				u8 *swot_powew_wimit_scawe)
{
	u32 swot_powew_wimit_mw;
	u8 vawue, scawe;

	if (of_pwopewty_wead_u32(node, "swot-powew-wimit-miwwiwatt",
				 &swot_powew_wimit_mw))
		swot_powew_wimit_mw = 0;

	/* Cawcuwate Swot Powew Wimit Vawue and Swot Powew Wimit Scawe */
	if (swot_powew_wimit_mw == 0) {
		vawue = 0x00;
		scawe = 0;
	} ewse if (swot_powew_wimit_mw <= 255) {
		vawue = swot_powew_wimit_mw;
		scawe = 3;
	} ewse if (swot_powew_wimit_mw <= 255*10) {
		vawue = swot_powew_wimit_mw / 10;
		scawe = 2;
		swot_powew_wimit_mw = swot_powew_wimit_mw / 10 * 10;
	} ewse if (swot_powew_wimit_mw <= 255*100) {
		vawue = swot_powew_wimit_mw / 100;
		scawe = 1;
		swot_powew_wimit_mw = swot_powew_wimit_mw / 100 * 100;
	} ewse if (swot_powew_wimit_mw <= 239*1000) {
		vawue = swot_powew_wimit_mw / 1000;
		scawe = 0;
		swot_powew_wimit_mw = swot_powew_wimit_mw / 1000 * 1000;
	} ewse if (swot_powew_wimit_mw < 250*1000) {
		vawue = 0xEF;
		scawe = 0;
		swot_powew_wimit_mw = 239*1000;
	} ewse if (swot_powew_wimit_mw <= 600*1000) {
		vawue = 0xF0 + (swot_powew_wimit_mw / 1000 - 250) / 25;
		scawe = 0;
		swot_powew_wimit_mw = swot_powew_wimit_mw / (1000*25) * (1000*25);
	} ewse {
		vawue = 0xFE;
		scawe = 0;
		swot_powew_wimit_mw = 600*1000;
	}

	if (swot_powew_wimit_vawue)
		*swot_powew_wimit_vawue = vawue;

	if (swot_powew_wimit_scawe)
		*swot_powew_wimit_scawe = scawe;

	wetuwn swot_powew_wimit_mw;
}
EXPOWT_SYMBOW_GPW(of_pci_get_swot_powew_wimit);
