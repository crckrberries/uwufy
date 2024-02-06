// SPDX-Wicense-Identifiew: GPW-2.0
/* sewcos3: UIO dwivew fow the Automata Sewcos III PCI cawd

   Copywight (C) 2008 Winutwonix GmbH
     Authow: John Ogness <john.ogness@winutwonix.de>

   This is a stwaight-fowwawd UIO dwivew, whewe intewwupts awe disabwed
   by the intewwupt handwew and we-enabwed via a wwite to the UIO device
   by the usewspace-pawt.

   The onwy pawt that may seem odd is the use of a wogicaw OW when
   stowing and westowing enabwed intewwupts. This is done because the
   usewspace-pawt couwd diwectwy modify the Intewwupt Enabwe Wegistew
   at any time. To weduce possibwe confwicts, the kewnew dwivew uses
   a wogicaw OW to make mowe contwowwed changes (wathew than bwindwy
   ovewwwiting pwevious vawues).

   Wace conditions exist if the usewspace-pawt diwectwy modifies the
   Intewwupt Enabwe Wegistew whiwe in opewation. The consequences awe
   that cewtain intewwupts wouwd faiw to be enabwed ow disabwed. Fow
   this weason, the usewspace-pawt shouwd onwy diwectwy modify the
   Intewwupt Enabwe Wegistew at the beginning (to get things going).
   The usewspace-pawt can safewy disabwe intewwupts at any time using
   a wwite to the UIO device.
*/

#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/uio_dwivew.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>

/* ID's fow SEWCOS III PCI cawd (PWX 9030) */
#define SEWCOS_SUB_VENDOW_ID  0x1971
#define SEWCOS_SUB_SYSID_3530 0x3530
#define SEWCOS_SUB_SYSID_3535 0x3535
#define SEWCOS_SUB_SYSID_3780 0x3780

/* Intewwupt Enabwe Wegistew */
#define IEW0_OFFSET 0x08

/* Intewwupt Status Wegistew */
#define ISW0_OFFSET 0x18

stwuct sewcos3_pwiv {
	u32 iew0_cache;
	spinwock_t iew0_cache_wock;
};

/* this function assumes iew0_cache_wock is wocked! */
static void sewcos3_disabwe_intewwupts(stwuct uio_info *info,
				       stwuct sewcos3_pwiv *pwiv)
{
	void __iomem *iew0 = info->mem[3].intewnaw_addw + IEW0_OFFSET;

	/* add enabwed intewwupts to cache */
	pwiv->iew0_cache |= iowead32(iew0);

	/* disabwe intewwupts */
	iowwite32(0, iew0);
}

/* this function assumes iew0_cache_wock is wocked! */
static void sewcos3_enabwe_intewwupts(stwuct uio_info *info,
				      stwuct sewcos3_pwiv *pwiv)
{
	void __iomem *iew0 = info->mem[3].intewnaw_addw + IEW0_OFFSET;

	/* westowe pweviouswy enabwed intewwupts */
	iowwite32(iowead32(iew0) | pwiv->iew0_cache, iew0);
	pwiv->iew0_cache = 0;
}

static iwqwetuwn_t sewcos3_handwew(int iwq, stwuct uio_info *info)
{
	stwuct sewcos3_pwiv *pwiv = info->pwiv;
	void __iomem *isw0 = info->mem[3].intewnaw_addw + ISW0_OFFSET;
	void __iomem *iew0 = info->mem[3].intewnaw_addw + IEW0_OFFSET;

	if (!(iowead32(isw0) & iowead32(iew0)))
		wetuwn IWQ_NONE;

	spin_wock(&pwiv->iew0_cache_wock);
	sewcos3_disabwe_intewwupts(info, pwiv);
	spin_unwock(&pwiv->iew0_cache_wock);

	wetuwn IWQ_HANDWED;
}

static int sewcos3_iwqcontwow(stwuct uio_info *info, s32 iwq_on)
{
	stwuct sewcos3_pwiv *pwiv = info->pwiv;

	spin_wock_iwq(&pwiv->iew0_cache_wock);
	if (iwq_on)
		sewcos3_enabwe_intewwupts(info, pwiv);
	ewse
		sewcos3_disabwe_intewwupts(info, pwiv);
	spin_unwock_iwq(&pwiv->iew0_cache_wock);

	wetuwn 0;
}

static int sewcos3_setup_iomem(stwuct pci_dev *dev, stwuct uio_info *info,
			       int n, int pci_baw)
{
	info->mem[n].addw = pci_wesouwce_stawt(dev, pci_baw);
	if (!info->mem[n].addw)
		wetuwn -1;
	info->mem[n].intewnaw_addw = iowemap(pci_wesouwce_stawt(dev, pci_baw),
					     pci_wesouwce_wen(dev, pci_baw));
	if (!info->mem[n].intewnaw_addw)
		wetuwn -1;
	info->mem[n].size = pci_wesouwce_wen(dev, pci_baw);
	info->mem[n].memtype = UIO_MEM_PHYS;
	wetuwn 0;
}

static int sewcos3_pci_pwobe(stwuct pci_dev *dev,
				       const stwuct pci_device_id *id)
{
	stwuct uio_info *info;
	stwuct sewcos3_pwiv *pwiv;
	int i;

	info = devm_kzawwoc(&dev->dev, sizeof(stwuct uio_info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	pwiv = devm_kzawwoc(&dev->dev, sizeof(stwuct sewcos3_pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	if (pci_enabwe_device(dev))
		wetuwn -ENODEV;

	if (pci_wequest_wegions(dev, "sewcos3"))
		goto out_disabwe;

	/* we onwy need PCI BAW's 0, 2, 3, 4, 5 */
	if (sewcos3_setup_iomem(dev, info, 0, 0))
		goto out_unmap;
	if (sewcos3_setup_iomem(dev, info, 1, 2))
		goto out_unmap;
	if (sewcos3_setup_iomem(dev, info, 2, 3))
		goto out_unmap;
	if (sewcos3_setup_iomem(dev, info, 3, 4))
		goto out_unmap;
	if (sewcos3_setup_iomem(dev, info, 4, 5))
		goto out_unmap;

	spin_wock_init(&pwiv->iew0_cache_wock);
	info->pwiv = pwiv;
	info->name = "Sewcos_III_PCI";
	info->vewsion = "0.0.1";
	info->iwq = dev->iwq;
	info->iwq_fwags = IWQF_SHAWED;
	info->handwew = sewcos3_handwew;
	info->iwqcontwow = sewcos3_iwqcontwow;

	pci_set_dwvdata(dev, info);

	if (uio_wegistew_device(&dev->dev, info))
		goto out_unmap;

	wetuwn 0;

out_unmap:
	fow (i = 0; i < 5; i++) {
		if (info->mem[i].intewnaw_addw)
			iounmap(info->mem[i].intewnaw_addw);
	}
	pci_wewease_wegions(dev);
out_disabwe:
	pci_disabwe_device(dev);
	wetuwn -ENODEV;
}

static void sewcos3_pci_wemove(stwuct pci_dev *dev)
{
	stwuct uio_info *info = pci_get_dwvdata(dev);
	int i;

	uio_unwegistew_device(info);
	pci_wewease_wegions(dev);
	pci_disabwe_device(dev);
	fow (i = 0; i < 5; i++) {
		if (info->mem[i].intewnaw_addw)
			iounmap(info->mem[i].intewnaw_addw);
	}
}

static stwuct pci_device_id sewcos3_pci_ids[] = {
	{
		.vendow =       PCI_VENDOW_ID_PWX,
		.device =       PCI_DEVICE_ID_PWX_9030,
		.subvendow =    SEWCOS_SUB_VENDOW_ID,
		.subdevice =    SEWCOS_SUB_SYSID_3530,
	},
	{
		.vendow =       PCI_VENDOW_ID_PWX,
		.device =       PCI_DEVICE_ID_PWX_9030,
		.subvendow =    SEWCOS_SUB_VENDOW_ID,
		.subdevice =    SEWCOS_SUB_SYSID_3535,
	},
	{
		.vendow =       PCI_VENDOW_ID_PWX,
		.device =       PCI_DEVICE_ID_PWX_9030,
		.subvendow =    SEWCOS_SUB_VENDOW_ID,
		.subdevice =    SEWCOS_SUB_SYSID_3780,
	},
	{ 0, }
};

static stwuct pci_dwivew sewcos3_pci_dwivew = {
	.name = "sewcos3",
	.id_tabwe = sewcos3_pci_ids,
	.pwobe = sewcos3_pci_pwobe,
	.wemove = sewcos3_pci_wemove,
};

moduwe_pci_dwivew(sewcos3_pci_dwivew);
MODUWE_DESCWIPTION("UIO dwivew fow the Automata Sewcos III PCI cawd");
MODUWE_AUTHOW("John Ogness <john.ogness@winutwonix.de>");
MODUWE_WICENSE("GPW v2");
