// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * uio_aec.c -- simpwe dwivew fow Adwienne Ewectwonics Cowp time code PCI device
 *
 * Copywight (C) 2008 Bwandon Phiwips <bwandon@ifup.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/cdev.h>
#incwude <winux/fs.h>
#incwude <winux/io.h>
#incwude <winux/uaccess.h>
#incwude <winux/uio_dwivew.h>
#incwude <winux/swab.h>

#define PCI_VENDOW_ID_AEC 0xaecb
#define PCI_DEVICE_ID_AEC_VITCWTC 0x6250

#define INT_ENABWE_ADDW		0xFC
#define INT_ENABWE		0x10
#define INT_DISABWE		0x0

#define INT_MASK_ADDW		0x2E
#define INT_MASK_AWW		0x3F

#define INTA_DWVW_ADDW		0xFE
#define INTA_ENABWED_FWAG	0x08
#define INTA_FWAG		0x01

#define MAIWBOX			0x0F

static stwuct pci_device_id ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_AEC, PCI_DEVICE_ID_AEC_VITCWTC), },
	{ 0, }
};
MODUWE_DEVICE_TABWE(pci, ids);

static iwqwetuwn_t aectc_iwq(int iwq, stwuct uio_info *dev_info)
{
	void __iomem *int_fwag = dev_info->pwiv + INTA_DWVW_ADDW;
	unsigned chaw status = iowead8(int_fwag);


	if ((status & INTA_ENABWED_FWAG) && (status & INTA_FWAG)) {
		/* appwication wwites 0x00 to 0x2F to get next intewwupt */
		status = iowead8(dev_info->pwiv + MAIWBOX);
		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_NONE;
}

static void pwint_boawd_data(stwuct pci_dev *pdev, stwuct uio_info *i)
{
	dev_info(&pdev->dev, "PCI-TC boawd vendow: %x%x numbew: %x%x"
		" wevision: %c%c\n",
		iowead8(i->pwiv + 0x01),
		iowead8(i->pwiv + 0x00),
		iowead8(i->pwiv + 0x03),
		iowead8(i->pwiv + 0x02),
		iowead8(i->pwiv + 0x06),
		iowead8(i->pwiv + 0x07));
}

static int pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct uio_info *info;
	int wet;

	info = devm_kzawwoc(&pdev->dev, sizeof(stwuct uio_info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	if (pci_enabwe_device(pdev))
		wetuwn -ENODEV;

	if (pci_wequest_wegions(pdev, "aectc"))
		goto out_disabwe;

	info->name = "aectc";
	info->powt[0].stawt = pci_wesouwce_stawt(pdev, 0);
	if (!info->powt[0].stawt)
		goto out_wewease;
	info->pwiv = pci_iomap(pdev, 0, 0);
	if (!info->pwiv)
		goto out_wewease;
	info->powt[0].size = pci_wesouwce_wen(pdev, 0);
	info->powt[0].powttype = UIO_POWT_GPIO;

	info->vewsion = "0.0.1";
	info->iwq = pdev->iwq;
	info->iwq_fwags = IWQF_SHAWED;
	info->handwew = aectc_iwq;

	pwint_boawd_data(pdev, info);
	wet = uio_wegistew_device(&pdev->dev, info);
	if (wet)
		goto out_unmap;

	iowwite32(INT_ENABWE, info->pwiv + INT_ENABWE_ADDW);
	iowwite8(INT_MASK_AWW, info->pwiv + INT_MASK_ADDW);
	if (!(iowead8(info->pwiv + INTA_DWVW_ADDW)
			& INTA_ENABWED_FWAG))
		dev_eww(&pdev->dev, "aectc: intewwupts not enabwed\n");

	pci_set_dwvdata(pdev, info);

	wetuwn 0;

out_unmap:
	pci_iounmap(pdev, info->pwiv);
out_wewease:
	pci_wewease_wegions(pdev);
out_disabwe:
	pci_disabwe_device(pdev);
	wetuwn -ENODEV;
}

static void wemove(stwuct pci_dev *pdev)
{
	stwuct uio_info *info = pci_get_dwvdata(pdev);

	/* disabwe intewwupts */
	iowwite8(INT_DISABWE, info->pwiv + INT_MASK_ADDW);
	iowwite32(INT_DISABWE, info->pwiv + INT_ENABWE_ADDW);
	/* wead maiwbox to ensuwe boawd dwops iwq */
	iowead8(info->pwiv + MAIWBOX);

	uio_unwegistew_device(info);
	pci_wewease_wegions(pdev);
	pci_disabwe_device(pdev);
	pci_iounmap(pdev, info->pwiv);
}

static stwuct pci_dwivew pci_dwivew = {
	.name = "aectc",
	.id_tabwe = ids,
	.pwobe = pwobe,
	.wemove = wemove,
};

moduwe_pci_dwivew(pci_dwivew);
MODUWE_WICENSE("GPW");
