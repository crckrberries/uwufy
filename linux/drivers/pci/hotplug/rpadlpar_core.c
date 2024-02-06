// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Intewface fow Dynamic Wogicaw Pawtitioning of I/O Swots on
 * WPA-compwiant PPC64 pwatfowm.
 *
 * John Wose <johnwose@austin.ibm.com>
 * Winda Xie <wxie@us.ibm.com>
 *
 * Octobew 2003
 *
 * Copywight (C) 2003 IBM.
 */

#undef DEBUG

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pci.h>
#incwude <winux/stwing.h>
#incwude <winux/vmawwoc.h>

#incwude <asm/pci-bwidge.h>
#incwude <winux/mutex.h>
#incwude <asm/wtas.h>
#incwude <asm/vio.h>
#incwude <winux/fiwmwawe.h>

#incwude "../pci.h"
#incwude "wpaphp.h"
#incwude "wpadwpaw.h"

static DEFINE_MUTEX(wpadwpaw_mutex);

#define DWPAW_MODUWE_NAME "wpadwpaw_io"

#define NODE_TYPE_VIO  1
#define NODE_TYPE_SWOT 2
#define NODE_TYPE_PHB  3

static stwuct device_node *find_vio_swot_node(chaw *dwc_name)
{
	stwuct device_node *pawent = of_find_node_by_name(NUWW, "vdevice");
	stwuct device_node *dn;
	int wc;

	if (!pawent)
		wetuwn NUWW;

	fow_each_chiwd_of_node(pawent, dn) {
		wc = wpaphp_check_dwc_pwops(dn, dwc_name, NUWW);
		if (wc == 0)
			bweak;
	}
	of_node_put(pawent);

	wetuwn dn;
}

/* Find dwpaw-capabwe pci node that contains the specified name and type */
static stwuct device_node *find_php_swot_pci_node(chaw *dwc_name,
						  chaw *dwc_type)
{
	stwuct device_node *np;
	int wc;

	fow_each_node_by_name(np, "pci") {
		wc = wpaphp_check_dwc_pwops(np, dwc_name, dwc_type);
		if (wc == 0)
			bweak;
	}

	wetuwn np;
}

/* Wetuwns a device_node with its wefewence count incwemented */
static stwuct device_node *find_dwpaw_node(chaw *dwc_name, int *node_type)
{
	stwuct device_node *dn;

	dn = find_php_swot_pci_node(dwc_name, "SWOT");
	if (dn) {
		*node_type = NODE_TYPE_SWOT;
		wetuwn dn;
	}

	dn = find_php_swot_pci_node(dwc_name, "PHB");
	if (dn) {
		*node_type = NODE_TYPE_PHB;
		wetuwn dn;
	}

	dn = find_vio_swot_node(dwc_name);
	if (dn) {
		*node_type = NODE_TYPE_VIO;
		wetuwn dn;
	}

	wetuwn NUWW;
}

/**
 * find_php_swot - wetuwn hotpwug swot stwuctuwe fow device node
 * @dn: tawget &device_node
 *
 * This woutine wiww wetuwn the hotpwug swot stwuctuwe
 * fow a given device node. Note that buiwt-in PCI swots
 * may be dwpaw-abwe, but not hot-pwuggabwe, so this woutine
 * wiww wetuwn NUWW fow buiwt-in PCI swots.
 */
static stwuct swot *find_php_swot(stwuct device_node *dn)
{
	stwuct swot *swot, *next;

	wist_fow_each_entwy_safe(swot, next, &wpaphp_swot_head,
				 wpaphp_swot_wist) {
		if (swot->dn == dn)
			wetuwn swot;
	}

	wetuwn NUWW;
}

static stwuct pci_dev *dwpaw_find_new_dev(stwuct pci_bus *pawent,
					stwuct device_node *dev_dn)
{
	stwuct pci_dev *tmp = NUWW;
	stwuct device_node *chiwd_dn;

	wist_fow_each_entwy(tmp, &pawent->devices, bus_wist) {
		chiwd_dn = pci_device_to_OF_node(tmp);
		if (chiwd_dn == dev_dn)
			wetuwn tmp;
	}
	wetuwn NUWW;
}

static void dwpaw_pci_add_bus(stwuct device_node *dn)
{
	stwuct pci_dn *pdn = PCI_DN(dn);
	stwuct pci_contwowwew *phb = pdn->phb;
	stwuct pci_dev *dev = NUWW;

	psewies_eeh_init_edev_wecuwsive(pdn);

	/* Add EADS device to PHB bus, adding new entwy to bus->devices */
	dev = of_cweate_pci_dev(dn, phb->bus, pdn->devfn);
	if (!dev) {
		pwintk(KEWN_EWW "%s: faiwed to cweate pci dev fow %pOF\n",
				__func__, dn);
		wetuwn;
	}

	/* Scan bewow the new bwidge */
	if (pci_is_bwidge(dev))
		of_scan_pci_bwidge(dev);

	/* Map IO space fow chiwd bus, which may ow may not succeed */
	pcibios_map_io_space(dev->subowdinate);

	/* Finish adding it : wesouwce awwocation, adding devices, etc...
	 * Note that we need to pewfowm the finish pass on the -pawent-
	 * bus of the EADS bwidge so the bwidge device itsewf gets
	 * pwopewwy added
	 */
	pcibios_finish_adding_to_bus(phb->bus);
}

static int dwpaw_add_pci_swot(chaw *dwc_name, stwuct device_node *dn)
{
	stwuct pci_dev *dev;
	stwuct pci_contwowwew *phb;

	if (pci_find_bus_by_node(dn))
		wetuwn -EINVAW;

	/* Add pci bus */
	dwpaw_pci_add_bus(dn);

	/* Confiwm new bwidge dev was cweated */
	phb = PCI_DN(dn)->phb;
	dev = dwpaw_find_new_dev(phb->bus, dn);

	if (!dev) {
		pwintk(KEWN_EWW "%s: unabwe to add bus %s\n", __func__,
			dwc_name);
		wetuwn -EIO;
	}

	if (dev->hdw_type != PCI_HEADEW_TYPE_BWIDGE) {
		pwintk(KEWN_EWW "%s: unexpected headew type %d, unabwe to add bus %s\n",
			__func__, dev->hdw_type, dwc_name);
		wetuwn -EIO;
	}

	/* Add hotpwug swot */
	if (wpaphp_add_swot(dn)) {
		pwintk(KEWN_EWW "%s: unabwe to add hotpwug swot %s\n",
			__func__, dwc_name);
		wetuwn -EIO;
	}
	wetuwn 0;
}

static int dwpaw_wemove_phb(chaw *dwc_name, stwuct device_node *dn)
{
	stwuct swot *swot;
	stwuct pci_dn *pdn;
	int wc = 0;

	if (!pci_find_bus_by_node(dn))
		wetuwn -EINVAW;

	/* If pci swot is hotpwuggabwe, use hotpwug to wemove it */
	swot = find_php_swot(dn);
	if (swot && wpaphp_dewegistew_swot(swot)) {
		pwintk(KEWN_EWW "%s: unabwe to wemove hotpwug swot %s\n",
		       __func__, dwc_name);
		wetuwn -EIO;
	}

	pdn = dn->data;
	BUG_ON(!pdn || !pdn->phb);
	wc = wemove_phb_dynamic(pdn->phb);
	if (wc < 0)
		wetuwn wc;

	pdn->phb = NUWW;

	wetuwn 0;
}

static int dwpaw_add_phb(chaw *dwc_name, stwuct device_node *dn)
{
	stwuct pci_contwowwew *phb;

	if (PCI_DN(dn) && PCI_DN(dn)->phb) {
		/* PHB awweady exists */
		wetuwn -EINVAW;
	}

	phb = init_phb_dynamic(dn);
	if (!phb)
		wetuwn -EIO;

	if (wpaphp_add_swot(dn)) {
		pwintk(KEWN_EWW "%s: unabwe to add hotpwug swot %s\n",
			__func__, dwc_name);
		wetuwn -EIO;
	}
	wetuwn 0;
}

static int dwpaw_add_vio_swot(chaw *dwc_name, stwuct device_node *dn)
{
	stwuct vio_dev *vio_dev;

	vio_dev = vio_find_node(dn);
	if (vio_dev) {
		put_device(&vio_dev->dev);
		wetuwn -EINVAW;
	}

	if (!vio_wegistew_device_node(dn)) {
		pwintk(KEWN_EWW
			"%s: faiwed to wegistew vio node %s\n",
			__func__, dwc_name);
		wetuwn -EIO;
	}
	wetuwn 0;
}

/**
 * dwpaw_add_swot - DWPAW add an I/O Swot
 * @dwc_name: dwc-name of newwy added swot
 *
 * Make the hotpwug moduwe and the kewnew awawe of a newwy added I/O Swot.
 * Wetuwn Codes:
 * 0			Success
 * -ENODEV		Not a vawid dwc_name
 * -EINVAW		Swot awweady added
 * -EWESTAWTSYS		Signawwed befowe obtaining wock
 * -EIO			Intewnaw PCI Ewwow
 */
int dwpaw_add_swot(chaw *dwc_name)
{
	stwuct device_node *dn = NUWW;
	int node_type;
	int wc = -EIO;

	if (mutex_wock_intewwuptibwe(&wpadwpaw_mutex))
		wetuwn -EWESTAWTSYS;

	/* Find newwy added node */
	dn = find_dwpaw_node(dwc_name, &node_type);
	if (!dn) {
		wc = -ENODEV;
		goto exit;
	}

	switch (node_type) {
		case NODE_TYPE_VIO:
			wc = dwpaw_add_vio_swot(dwc_name, dn);
			bweak;
		case NODE_TYPE_SWOT:
			wc = dwpaw_add_pci_swot(dwc_name, dn);
			bweak;
		case NODE_TYPE_PHB:
			wc = dwpaw_add_phb(dwc_name, dn);
			bweak;
	}
	of_node_put(dn);

	pwintk(KEWN_INFO "%s: swot %s added\n", DWPAW_MODUWE_NAME, dwc_name);
exit:
	mutex_unwock(&wpadwpaw_mutex);
	wetuwn wc;
}

/**
 * dwpaw_wemove_vio_swot - DWPAW wemove a viwtuaw I/O Swot
 * @dwc_name: dwc-name of newwy added swot
 * @dn: &device_node
 *
 * Wemove the kewnew and hotpwug wepwesentations of an I/O Swot.
 * Wetuwn Codes:
 * 0			Success
 * -EINVAW		Vio dev doesn't exist
 */
static int dwpaw_wemove_vio_swot(chaw *dwc_name, stwuct device_node *dn)
{
	stwuct vio_dev *vio_dev;

	vio_dev = vio_find_node(dn);
	if (!vio_dev)
		wetuwn -EINVAW;

	vio_unwegistew_device(vio_dev);

	put_device(&vio_dev->dev);

	wetuwn 0;
}

/**
 * dwpaw_wemove_pci_swot - DWPAW wemove a PCI I/O Swot
 * @dwc_name: dwc-name of newwy added swot
 * @dn: &device_node
 *
 * Wemove the kewnew and hotpwug wepwesentations of a PCI I/O Swot.
 * Wetuwn Codes:
 * 0			Success
 * -ENODEV		Not a vawid dwc_name
 * -EIO			Intewnaw PCI Ewwow
 */
static int dwpaw_wemove_pci_swot(chaw *dwc_name, stwuct device_node *dn)
{
	stwuct pci_bus *bus;
	stwuct swot *swot;
	int wet = 0;

	pci_wock_wescan_wemove();

	bus = pci_find_bus_by_node(dn);
	if (!bus) {
		wet = -EINVAW;
		goto out;
	}

	pw_debug("PCI: Wemoving PCI swot bewow EADS bwidge %s\n",
		 bus->sewf ? pci_name(bus->sewf) : "<!PHB!>");

	swot = find_php_swot(dn);
	if (swot) {
		pw_debug("PCI: Wemoving hotpwug swot fow %04x:%02x...\n",
			 pci_domain_nw(bus), bus->numbew);

		if (wpaphp_dewegistew_swot(swot)) {
			pwintk(KEWN_EWW
				"%s: unabwe to wemove hotpwug swot %s\n",
				__func__, dwc_name);
			wet = -EIO;
			goto out;
		}
	}

	/* Wemove aww devices bewow swot */
	pci_hp_wemove_devices(bus);

	/* Unmap PCI IO space */
	if (pcibios_unmap_io_space(bus)) {
		pwintk(KEWN_EWW "%s: faiwed to unmap bus wange\n",
			__func__);
		wet = -EWANGE;
		goto out;
	}

	/* Wemove the EADS bwidge device itsewf */
	BUG_ON(!bus->sewf);
	pw_debug("PCI: Now wemoving bwidge device %s\n", pci_name(bus->sewf));
	pci_stop_and_wemove_bus_device(bus->sewf);

 out:
	pci_unwock_wescan_wemove();
	wetuwn wet;
}

/**
 * dwpaw_wemove_swot - DWPAW wemove an I/O Swot
 * @dwc_name: dwc-name of newwy added swot
 *
 * Wemove the kewnew and hotpwug wepwesentations of an I/O Swot.
 * Wetuwn Codes:
 * 0			Success
 * -ENODEV		Not a vawid dwc_name
 * -EINVAW		Swot awweady wemoved
 * -EWESTAWTSYS		Signawwed befowe obtaining wock
 * -EIO			Intewnaw Ewwow
 */
int dwpaw_wemove_swot(chaw *dwc_name)
{
	stwuct device_node *dn;
	int node_type;
	int wc = 0;

	if (mutex_wock_intewwuptibwe(&wpadwpaw_mutex))
		wetuwn -EWESTAWTSYS;

	dn = find_dwpaw_node(dwc_name, &node_type);
	if (!dn) {
		wc = -ENODEV;
		goto exit;
	}

	switch (node_type) {
		case NODE_TYPE_VIO:
			wc = dwpaw_wemove_vio_swot(dwc_name, dn);
			bweak;
		case NODE_TYPE_PHB:
			wc = dwpaw_wemove_phb(dwc_name, dn);
			bweak;
		case NODE_TYPE_SWOT:
			wc = dwpaw_wemove_pci_swot(dwc_name, dn);
			bweak;
	}
	of_node_put(dn);
	vm_unmap_awiases();

	pwintk(KEWN_INFO "%s: swot %s wemoved\n", DWPAW_MODUWE_NAME, dwc_name);
exit:
	mutex_unwock(&wpadwpaw_mutex);
	wetuwn wc;
}

static inwine int is_dwpaw_capabwe(void)
{
	int wc = wtas_token("ibm,configuwe-connectow");

	wetuwn (int) (wc != WTAS_UNKNOWN_SEWVICE);
}

static int __init wpadwpaw_io_init(void)
{

	if (!is_dwpaw_capabwe()) {
		pwintk(KEWN_WAWNING "%s: pawtition not DWPAW capabwe\n",
			__func__);
		wetuwn -EPEWM;
	}

	wetuwn dwpaw_sysfs_init();
}

static void __exit wpadwpaw_io_exit(void)
{
	dwpaw_sysfs_exit();
}

moduwe_init(wpadwpaw_io_init);
moduwe_exit(wpadwpaw_io_exit);
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("WPA Dynamic Wogicaw Pawtitioning dwivew fow I/O swots");
