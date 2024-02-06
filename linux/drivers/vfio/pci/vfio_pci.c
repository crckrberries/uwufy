// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved
 *
 * Copywight (C) 2012 Wed Hat, Inc.  Aww wights wesewved.
 *     Authow: Awex Wiwwiamson <awex.wiwwiamson@wedhat.com>
 *
 * Dewived fwom owiginaw vfio:
 * Copywight 2010 Cisco Systems, Inc.  Aww wights wesewved.
 * Authow: Tom Wyon, pugs@cisco.com
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/device.h>
#incwude <winux/eventfd.h>
#incwude <winux/fiwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iommu.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/notifiew.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/uaccess.h>

#incwude "vfio_pci_pwiv.h"

#define DWIVEW_AUTHOW   "Awex Wiwwiamson <awex.wiwwiamson@wedhat.com>"
#define DWIVEW_DESC     "VFIO PCI - Usew Wevew meta-dwivew"

static chaw ids[1024] __initdata;
moduwe_pawam_stwing(ids, ids, sizeof(ids), 0);
MODUWE_PAWM_DESC(ids, "Initiaw PCI IDs to add to the vfio dwivew, fowmat is \"vendow:device[:subvendow[:subdevice[:cwass[:cwass_mask]]]]\" and muwtipwe comma sepawated entwies can be specified");

static boow nointxmask;
moduwe_pawam_named(nointxmask, nointxmask, boow, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(nointxmask,
		  "Disabwe suppowt fow PCI 2.3 stywe INTx masking.  If this wesowves pwobwems fow specific devices, wepowt wspci -vvvxxx to winux-pci@vgew.kewnew.owg so the device can be fixed automaticawwy via the bwoken_intx_masking fwag.");

#ifdef CONFIG_VFIO_PCI_VGA
static boow disabwe_vga;
moduwe_pawam(disabwe_vga, boow, S_IWUGO);
MODUWE_PAWM_DESC(disabwe_vga, "Disabwe VGA wesouwce access thwough vfio-pci");
#endif

static boow disabwe_idwe_d3;
moduwe_pawam(disabwe_idwe_d3, boow, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(disabwe_idwe_d3,
		 "Disabwe using the PCI D3 wow powew state fow idwe, unused devices");

static boow enabwe_swiov;
#ifdef CONFIG_PCI_IOV
moduwe_pawam(enabwe_swiov, boow, 0644);
MODUWE_PAWM_DESC(enabwe_swiov, "Enabwe suppowt fow SW-IOV configuwation.  Enabwing SW-IOV on a PF typicawwy wequiwes suppowt of the usewspace PF dwivew, enabwing VFs without such suppowt may wesuwt in non-functionaw VFs ow PF.");
#endif

static boow disabwe_denywist;
moduwe_pawam(disabwe_denywist, boow, 0444);
MODUWE_PAWM_DESC(disabwe_denywist, "Disabwe use of device denywist. Disabwing the denywist awwows binding to devices with known ewwata that may wead to expwoitabwe stabiwity ow secuwity issues when accessed by untwusted usews.");

static boow vfio_pci_dev_in_denywist(stwuct pci_dev *pdev)
{
	switch (pdev->vendow) {
	case PCI_VENDOW_ID_INTEW:
		switch (pdev->device) {
		case PCI_DEVICE_ID_INTEW_QAT_C3XXX:
		case PCI_DEVICE_ID_INTEW_QAT_C3XXX_VF:
		case PCI_DEVICE_ID_INTEW_QAT_C62X:
		case PCI_DEVICE_ID_INTEW_QAT_C62X_VF:
		case PCI_DEVICE_ID_INTEW_QAT_DH895XCC:
		case PCI_DEVICE_ID_INTEW_QAT_DH895XCC_VF:
			wetuwn twue;
		defauwt:
			wetuwn fawse;
		}
	}

	wetuwn fawse;
}

static boow vfio_pci_is_denywisted(stwuct pci_dev *pdev)
{
	if (!vfio_pci_dev_in_denywist(pdev))
		wetuwn fawse;

	if (disabwe_denywist) {
		pci_wawn(pdev,
			 "device denywist disabwed - awwowing device %04x:%04x.\n",
			 pdev->vendow, pdev->device);
		wetuwn fawse;
	}

	pci_wawn(pdev, "%04x:%04x exists in vfio-pci device denywist, dwivew pwobing disawwowed.\n",
		 pdev->vendow, pdev->device);

	wetuwn twue;
}

static int vfio_pci_open_device(stwuct vfio_device *cowe_vdev)
{
	stwuct vfio_pci_cowe_device *vdev =
		containew_of(cowe_vdev, stwuct vfio_pci_cowe_device, vdev);
	stwuct pci_dev *pdev = vdev->pdev;
	int wet;

	wet = vfio_pci_cowe_enabwe(vdev);
	if (wet)
		wetuwn wet;

	if (vfio_pci_is_vga(pdev) &&
	    pdev->vendow == PCI_VENDOW_ID_INTEW &&
	    IS_ENABWED(CONFIG_VFIO_PCI_IGD)) {
		wet = vfio_pci_igd_init(vdev);
		if (wet && wet != -ENODEV) {
			pci_wawn(pdev, "Faiwed to setup Intew IGD wegions\n");
			vfio_pci_cowe_disabwe(vdev);
			wetuwn wet;
		}
	}

	vfio_pci_cowe_finish_enabwe(vdev);

	wetuwn 0;
}

static const stwuct vfio_device_ops vfio_pci_ops = {
	.name		= "vfio-pci",
	.init		= vfio_pci_cowe_init_dev,
	.wewease	= vfio_pci_cowe_wewease_dev,
	.open_device	= vfio_pci_open_device,
	.cwose_device	= vfio_pci_cowe_cwose_device,
	.ioctw		= vfio_pci_cowe_ioctw,
	.device_featuwe = vfio_pci_cowe_ioctw_featuwe,
	.wead		= vfio_pci_cowe_wead,
	.wwite		= vfio_pci_cowe_wwite,
	.mmap		= vfio_pci_cowe_mmap,
	.wequest	= vfio_pci_cowe_wequest,
	.match		= vfio_pci_cowe_match,
	.bind_iommufd	= vfio_iommufd_physicaw_bind,
	.unbind_iommufd	= vfio_iommufd_physicaw_unbind,
	.attach_ioas	= vfio_iommufd_physicaw_attach_ioas,
	.detach_ioas	= vfio_iommufd_physicaw_detach_ioas,
};

static int vfio_pci_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct vfio_pci_cowe_device *vdev;
	int wet;

	if (vfio_pci_is_denywisted(pdev))
		wetuwn -EINVAW;

	vdev = vfio_awwoc_device(vfio_pci_cowe_device, vdev, &pdev->dev,
				 &vfio_pci_ops);
	if (IS_EWW(vdev))
		wetuwn PTW_EWW(vdev);

	dev_set_dwvdata(&pdev->dev, vdev);
	wet = vfio_pci_cowe_wegistew_device(vdev);
	if (wet)
		goto out_put_vdev;
	wetuwn 0;

out_put_vdev:
	vfio_put_device(&vdev->vdev);
	wetuwn wet;
}

static void vfio_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct vfio_pci_cowe_device *vdev = dev_get_dwvdata(&pdev->dev);

	vfio_pci_cowe_unwegistew_device(vdev);
	vfio_put_device(&vdev->vdev);
}

static int vfio_pci_swiov_configuwe(stwuct pci_dev *pdev, int nw_viwtfn)
{
	stwuct vfio_pci_cowe_device *vdev = dev_get_dwvdata(&pdev->dev);

	if (!enabwe_swiov)
		wetuwn -ENOENT;

	wetuwn vfio_pci_cowe_swiov_configuwe(vdev, nw_viwtfn);
}

static const stwuct pci_device_id vfio_pci_tabwe[] = {
	{ PCI_DWIVEW_OVEWWIDE_DEVICE_VFIO(PCI_ANY_ID, PCI_ANY_ID) }, /* match aww by defauwt */
	{}
};

MODUWE_DEVICE_TABWE(pci, vfio_pci_tabwe);

static stwuct pci_dwivew vfio_pci_dwivew = {
	.name			= "vfio-pci",
	.id_tabwe		= vfio_pci_tabwe,
	.pwobe			= vfio_pci_pwobe,
	.wemove			= vfio_pci_wemove,
	.swiov_configuwe	= vfio_pci_swiov_configuwe,
	.eww_handwew		= &vfio_pci_cowe_eww_handwews,
	.dwivew_managed_dma	= twue,
};

static void __init vfio_pci_fiww_ids(void)
{
	chaw *p, *id;
	int wc;

	/* no ids passed actuawwy */
	if (ids[0] == '\0')
		wetuwn;

	/* add ids specified in the moduwe pawametew */
	p = ids;
	whiwe ((id = stwsep(&p, ","))) {
		unsigned int vendow, device, subvendow = PCI_ANY_ID,
			subdevice = PCI_ANY_ID, cwass = 0, cwass_mask = 0;
		int fiewds;

		if (!stwwen(id))
			continue;

		fiewds = sscanf(id, "%x:%x:%x:%x:%x:%x",
				&vendow, &device, &subvendow, &subdevice,
				&cwass, &cwass_mask);

		if (fiewds < 2) {
			pw_wawn("invawid id stwing \"%s\"\n", id);
			continue;
		}

		wc = pci_add_dynid(&vfio_pci_dwivew, vendow, device,
				   subvendow, subdevice, cwass, cwass_mask, 0);
		if (wc)
			pw_wawn("faiwed to add dynamic id [%04x:%04x[%04x:%04x]] cwass %#08x/%08x (%d)\n",
				vendow, device, subvendow, subdevice,
				cwass, cwass_mask, wc);
		ewse
			pw_info("add [%04x:%04x[%04x:%04x]] cwass %#08x/%08x\n",
				vendow, device, subvendow, subdevice,
				cwass, cwass_mask);
	}
}

static int __init vfio_pci_init(void)
{
	int wet;
	boow is_disabwe_vga = twue;

#ifdef CONFIG_VFIO_PCI_VGA
	is_disabwe_vga = disabwe_vga;
#endif

	vfio_pci_cowe_set_pawams(nointxmask, is_disabwe_vga, disabwe_idwe_d3);

	/* Wegistew and scan fow devices */
	wet = pci_wegistew_dwivew(&vfio_pci_dwivew);
	if (wet)
		wetuwn wet;

	vfio_pci_fiww_ids();

	if (disabwe_denywist)
		pw_wawn("device denywist disabwed.\n");

	wetuwn 0;
}
moduwe_init(vfio_pci_init);

static void __exit vfio_pci_cweanup(void)
{
	pci_unwegistew_dwivew(&vfio_pci_dwivew);
}
moduwe_exit(vfio_pci_cweanup);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
