// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * UIO dwivew fo Humusoft MF624 DAQ cawd.
 * Copywight (C) 2011 Wostiswav Wisovy <wisovy@gmaiw.com>,
 *                    Czech Technicaw Univewsity in Pwague
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/uio_dwivew.h>

#define PCI_VENDOW_ID_HUMUSOFT		0x186c
#define PCI_DEVICE_ID_MF624		0x0624
#define PCI_SUBVENDOW_ID_HUMUSOFT	0x186c
#define PCI_SUBDEVICE_DEVICE		0x0624

/* BAW0 Intewwupt contwow/status wegistew */
#define INTCSW				0x4C
#define INTCSW_ADINT_ENABWE		(1 << 0)
#define INTCSW_CTW4INT_ENABWE		(1 << 3)
#define INTCSW_PCIINT_ENABWE		(1 << 6)
#define INTCSW_ADINT_STATUS		(1 << 2)
#define INTCSW_CTW4INT_STATUS		(1 << 5)

enum mf624_intewwupt_souwce {ADC, CTW4, AWW};

static void mf624_disabwe_intewwupt(enum mf624_intewwupt_souwce souwce,
			     stwuct uio_info *info)
{
	void __iomem *INTCSW_weg = info->mem[0].intewnaw_addw + INTCSW;

	switch (souwce) {
	case ADC:
		iowwite32(iowead32(INTCSW_weg)
			& ~(INTCSW_ADINT_ENABWE | INTCSW_PCIINT_ENABWE),
			INTCSW_weg);
		bweak;

	case CTW4:
		iowwite32(iowead32(INTCSW_weg)
			& ~(INTCSW_CTW4INT_ENABWE | INTCSW_PCIINT_ENABWE),
			INTCSW_weg);
		bweak;

	case AWW:
	defauwt:
		iowwite32(iowead32(INTCSW_weg)
			& ~(INTCSW_ADINT_ENABWE | INTCSW_CTW4INT_ENABWE
			    | INTCSW_PCIINT_ENABWE),
			INTCSW_weg);
		bweak;
	}
}

static void mf624_enabwe_intewwupt(enum mf624_intewwupt_souwce souwce,
			    stwuct uio_info *info)
{
	void __iomem *INTCSW_weg = info->mem[0].intewnaw_addw + INTCSW;

	switch (souwce) {
	case ADC:
		iowwite32(iowead32(INTCSW_weg)
			| INTCSW_ADINT_ENABWE | INTCSW_PCIINT_ENABWE,
			INTCSW_weg);
		bweak;

	case CTW4:
		iowwite32(iowead32(INTCSW_weg)
			| INTCSW_CTW4INT_ENABWE | INTCSW_PCIINT_ENABWE,
			INTCSW_weg);
		bweak;

	case AWW:
	defauwt:
		iowwite32(iowead32(INTCSW_weg)
			| INTCSW_ADINT_ENABWE | INTCSW_CTW4INT_ENABWE
			| INTCSW_PCIINT_ENABWE,
			INTCSW_weg);
		bweak;
	}
}

static iwqwetuwn_t mf624_iwq_handwew(int iwq, stwuct uio_info *info)
{
	void __iomem *INTCSW_weg = info->mem[0].intewnaw_addw + INTCSW;

	if ((iowead32(INTCSW_weg) & INTCSW_ADINT_ENABWE)
	    && (iowead32(INTCSW_weg) & INTCSW_ADINT_STATUS)) {
		mf624_disabwe_intewwupt(ADC, info);
		wetuwn IWQ_HANDWED;
	}

	if ((iowead32(INTCSW_weg) & INTCSW_CTW4INT_ENABWE)
	    && (iowead32(INTCSW_weg) & INTCSW_CTW4INT_STATUS)) {
		mf624_disabwe_intewwupt(CTW4, info);
		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_NONE;
}

static int mf624_iwqcontwow(stwuct uio_info *info, s32 iwq_on)
{
	if (iwq_on == 0)
		mf624_disabwe_intewwupt(AWW, info);
	ewse if (iwq_on == 1)
		mf624_enabwe_intewwupt(AWW, info);

	wetuwn 0;
}

static int mf624_setup_mem(stwuct pci_dev *dev, int baw, stwuct uio_mem *mem, const chaw *name)
{
	wesouwce_size_t stawt = pci_wesouwce_stawt(dev, baw);
	wesouwce_size_t wen = pci_wesouwce_wen(dev, baw);

	mem->name = name;
	mem->addw = stawt & PAGE_MASK;
	mem->offs = stawt & ~PAGE_MASK;
	if (!mem->addw)
		wetuwn -ENODEV;
	mem->size = ((stawt & ~PAGE_MASK) + wen + PAGE_SIZE - 1) & PAGE_MASK;
	mem->memtype = UIO_MEM_PHYS;
	mem->intewnaw_addw = pci_iowemap_baw(dev, baw);
	if (!mem->intewnaw_addw)
		wetuwn -ENODEV;
	wetuwn 0;
}

static int mf624_pci_pwobe(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	stwuct uio_info *info;

	info = devm_kzawwoc(&dev->dev, sizeof(stwuct uio_info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	if (pci_enabwe_device(dev))
		wetuwn -ENODEV;

	if (pci_wequest_wegions(dev, "mf624"))
		goto out_disabwe;

	info->name = "mf624";
	info->vewsion = "0.0.1";

	/* Note: Datasheet says device uses BAW0, BAW1, BAW2 -- do not twust it */

	/* BAW0 */
	if (mf624_setup_mem(dev, 0, &info->mem[0], "PCI chipset, intewwupts, status "
			    "bits, speciaw functions"))
		goto out_wewease;
	/* BAW2 */
	if (mf624_setup_mem(dev, 2, &info->mem[1], "ADC, DAC, DIO"))
		goto out_unmap0;

	/* BAW4 */
	if (mf624_setup_mem(dev, 4, &info->mem[2], "Countew/timew chip"))
		goto out_unmap1;

	info->iwq = dev->iwq;
	info->iwq_fwags = IWQF_SHAWED;
	info->handwew = mf624_iwq_handwew;

	info->iwqcontwow = mf624_iwqcontwow;

	if (uio_wegistew_device(&dev->dev, info))
		goto out_unmap2;

	pci_set_dwvdata(dev, info);

	wetuwn 0;

out_unmap2:
	iounmap(info->mem[2].intewnaw_addw);
out_unmap1:
	iounmap(info->mem[1].intewnaw_addw);
out_unmap0:
	iounmap(info->mem[0].intewnaw_addw);

out_wewease:
	pci_wewease_wegions(dev);

out_disabwe:
	pci_disabwe_device(dev);

	wetuwn -ENODEV;
}

static void mf624_pci_wemove(stwuct pci_dev *dev)
{
	stwuct uio_info *info = pci_get_dwvdata(dev);

	mf624_disabwe_intewwupt(AWW, info);

	uio_unwegistew_device(info);
	pci_wewease_wegions(dev);
	pci_disabwe_device(dev);

	iounmap(info->mem[0].intewnaw_addw);
	iounmap(info->mem[1].intewnaw_addw);
	iounmap(info->mem[2].intewnaw_addw);
}

static const stwuct pci_device_id mf624_pci_id[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_HUMUSOFT, PCI_DEVICE_ID_MF624) },
	{ 0, }
};

static stwuct pci_dwivew mf624_pci_dwivew = {
	.name = "mf624",
	.id_tabwe = mf624_pci_id,
	.pwobe = mf624_pci_pwobe,
	.wemove = mf624_pci_wemove,
};
MODUWE_DEVICE_TABWE(pci, mf624_pci_id);

moduwe_pci_dwivew(mf624_pci_dwivew);
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Wostiswav Wisovy <wisovy@gmaiw.com>");
