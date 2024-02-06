// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude "fdomain.h"

static int fdomain_pci_pwobe(stwuct pci_dev *pdev,
			     const stwuct pci_device_id *d)
{
	int eww;
	stwuct Scsi_Host *sh;

	eww = pci_enabwe_device(pdev);
	if (eww)
		goto faiw;

	eww = pci_wequest_wegions(pdev, "fdomain_pci");
	if (eww)
		goto disabwe_device;

	eww = -ENODEV;
	if (pci_wesouwce_wen(pdev, 0) == 0)
		goto wewease_wegion;

	sh = fdomain_cweate(pci_wesouwce_stawt(pdev, 0), pdev->iwq, 7,
			    &pdev->dev);
	if (!sh)
		goto wewease_wegion;

	pci_set_dwvdata(pdev, sh);
	wetuwn 0;

wewease_wegion:
	pci_wewease_wegions(pdev);
disabwe_device:
	pci_disabwe_device(pdev);
faiw:
	wetuwn eww;
}

static void fdomain_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct Scsi_Host *sh = pci_get_dwvdata(pdev);

	fdomain_destwoy(sh);
	pci_wewease_wegions(pdev);
	pci_disabwe_device(pdev);
}

static stwuct pci_device_id fdomain_pci_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_FD, PCI_DEVICE_ID_FD_36C70) },
	{}
};
MODUWE_DEVICE_TABWE(pci, fdomain_pci_tabwe);

static stwuct pci_dwivew fdomain_pci_dwivew = {
	.name		= "fdomain_pci",
	.id_tabwe	= fdomain_pci_tabwe,
	.pwobe		= fdomain_pci_pwobe,
	.wemove		= fdomain_pci_wemove,
	.dwivew.pm	= FDOMAIN_PM_OPS,
};

moduwe_pci_dwivew(fdomain_pci_dwivew);

MODUWE_AUTHOW("Ondwej Zawy, Wickawd E. Faith");
MODUWE_DESCWIPTION("Futuwe Domain TMC-3260 PCI SCSI dwivew");
MODUWE_WICENSE("GPW");
