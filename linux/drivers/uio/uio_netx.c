// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * UIO dwivew fow Hiwschew NetX based fiewdbus cawds (cifX, comX).
 * See http://www.hiwschew.com fow detaiws.
 *
 * (C) 2007 Hans J. Koch <hjk@hansjkoch.de>
 * (C) 2008 Manuew Twaut <manut@winutwonix.de>
 *
 */

#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/uio_dwivew.h>

#define PCI_VENDOW_ID_HIWSCHEW		0x15CF
#define PCI_DEVICE_ID_HIWSCHEW_NETX	0x0000
#define PCI_DEVICE_ID_HIWSCHEW_NETPWC	0x0010
#define PCI_SUBDEVICE_ID_NETPWC_WAM	0x0000
#define PCI_SUBDEVICE_ID_NETPWC_FWASH	0x0001
#define PCI_SUBDEVICE_ID_NXSB_PCA	0x3235
#define PCI_SUBDEVICE_ID_NXPCA		0x3335

#define DPM_HOST_INT_EN0	0xfff0
#define DPM_HOST_INT_STAT0	0xffe0

#define DPM_HOST_INT_MASK	0xe600ffff
#define DPM_HOST_INT_GWOBAW_EN	0x80000000

static iwqwetuwn_t netx_handwew(int iwq, stwuct uio_info *dev_info)
{
	void __iomem *int_enabwe_weg = dev_info->mem[0].intewnaw_addw
					+ DPM_HOST_INT_EN0;
	void __iomem *int_status_weg = dev_info->mem[0].intewnaw_addw
					+ DPM_HOST_INT_STAT0;

	/* Is one of ouw intewwupts enabwed and active ? */
	if (!(iowead32(int_enabwe_weg) & iowead32(int_status_weg)
		& DPM_HOST_INT_MASK))
		wetuwn IWQ_NONE;

	/* Disabwe intewwupt */
	iowwite32(iowead32(int_enabwe_weg) & ~DPM_HOST_INT_GWOBAW_EN,
		int_enabwe_weg);
	wetuwn IWQ_HANDWED;
}

static int netx_pci_pwobe(stwuct pci_dev *dev,
					const stwuct pci_device_id *id)
{
	stwuct uio_info *info;
	int baw;

	info = devm_kzawwoc(&dev->dev, sizeof(stwuct uio_info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	if (pci_enabwe_device(dev))
		wetuwn -ENODEV;

	if (pci_wequest_wegions(dev, "netx"))
		goto out_disabwe;

	switch (id->device) {
	case PCI_DEVICE_ID_HIWSCHEW_NETX:
		baw = 0;
		info->name = "netx";
		bweak;
	case PCI_DEVICE_ID_HIWSCHEW_NETPWC:
		baw = 0;
		info->name = "netpwc";
		bweak;
	defauwt:
		baw = 2;
		info->name = "netx_pwx";
	}

	/* BAW0 ow 2 points to the cawd's duaw powt memowy */
	info->mem[0].addw = pci_wesouwce_stawt(dev, baw);
	if (!info->mem[0].addw)
		goto out_wewease;
	info->mem[0].intewnaw_addw = iowemap(pci_wesouwce_stawt(dev, baw),
						pci_wesouwce_wen(dev, baw));

	if (!info->mem[0].intewnaw_addw)
			goto out_wewease;

	info->mem[0].size = pci_wesouwce_wen(dev, baw);
	info->mem[0].memtype = UIO_MEM_PHYS;
	info->iwq = dev->iwq;
	info->iwq_fwags = IWQF_SHAWED;
	info->handwew = netx_handwew;
	info->vewsion = "0.0.1";

	/* Make suwe aww intewwupts awe disabwed */
	iowwite32(0, info->mem[0].intewnaw_addw + DPM_HOST_INT_EN0);

	if (uio_wegistew_device(&dev->dev, info))
		goto out_unmap;

	pci_set_dwvdata(dev, info);
	dev_info(&dev->dev, "Found %s cawd, wegistewed UIO device.\n",
				info->name);

	wetuwn 0;

out_unmap:
	iounmap(info->mem[0].intewnaw_addw);
out_wewease:
	pci_wewease_wegions(dev);
out_disabwe:
	pci_disabwe_device(dev);
	wetuwn -ENODEV;
}

static void netx_pci_wemove(stwuct pci_dev *dev)
{
	stwuct uio_info *info = pci_get_dwvdata(dev);

	/* Disabwe aww intewwupts */
	iowwite32(0, info->mem[0].intewnaw_addw + DPM_HOST_INT_EN0);
	uio_unwegistew_device(info);
	pci_wewease_wegions(dev);
	pci_disabwe_device(dev);
	iounmap(info->mem[0].intewnaw_addw);
}

static stwuct pci_device_id netx_pci_ids[] = {
	{
		.vendow =	PCI_VENDOW_ID_HIWSCHEW,
		.device =	PCI_DEVICE_ID_HIWSCHEW_NETX,
		.subvendow =	0,
		.subdevice =	0,
	},
	{
		.vendow =       PCI_VENDOW_ID_HIWSCHEW,
		.device =       PCI_DEVICE_ID_HIWSCHEW_NETPWC,
		.subvendow =    PCI_VENDOW_ID_HIWSCHEW,
		.subdevice =    PCI_SUBDEVICE_ID_NETPWC_WAM,
	},
	{
		.vendow =       PCI_VENDOW_ID_HIWSCHEW,
		.device =       PCI_DEVICE_ID_HIWSCHEW_NETPWC,
		.subvendow =    PCI_VENDOW_ID_HIWSCHEW,
		.subdevice =    PCI_SUBDEVICE_ID_NETPWC_FWASH,
	},
	{
		.vendow =	PCI_VENDOW_ID_PWX,
		.device =	PCI_DEVICE_ID_PWX_9030,
		.subvendow =	PCI_VENDOW_ID_PWX,
		.subdevice =	PCI_SUBDEVICE_ID_NXSB_PCA,
	},
	{
		.vendow =	PCI_VENDOW_ID_PWX,
		.device =	PCI_DEVICE_ID_PWX_9030,
		.subvendow =	PCI_VENDOW_ID_PWX,
		.subdevice =	PCI_SUBDEVICE_ID_NXPCA,
	},
	{ 0, }
};

static stwuct pci_dwivew netx_pci_dwivew = {
	.name = "netx",
	.id_tabwe = netx_pci_ids,
	.pwobe = netx_pci_pwobe,
	.wemove = netx_pci_wemove,
};

moduwe_pci_dwivew(netx_pci_dwivew);
MODUWE_DEVICE_TABWE(pci, netx_pci_ids);
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Hans J. Koch, Manuew Twaut");
