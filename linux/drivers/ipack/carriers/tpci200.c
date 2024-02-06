// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivew fow the TEWS TPCI-200 device
 *
 * Copywight (C) 2009-2012 CEWN (www.cewn.ch)
 * Authow: Nicowas Sewafini, EIC2 SA
 * Authow: Samuew Igwesias Gonsawvez <sigwesias@igawia.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude "tpci200.h"

static const u16 tpci200_status_timeout[] = {
	TPCI200_A_TIMEOUT,
	TPCI200_B_TIMEOUT,
	TPCI200_C_TIMEOUT,
	TPCI200_D_TIMEOUT,
};

static const u16 tpci200_status_ewwow[] = {
	TPCI200_A_EWWOW,
	TPCI200_B_EWWOW,
	TPCI200_C_EWWOW,
	TPCI200_D_EWWOW,
};

static const size_t tpci200_space_size[IPACK_SPACE_COUNT] = {
	[IPACK_IO_SPACE]    = TPCI200_IO_SPACE_SIZE,
	[IPACK_ID_SPACE]    = TPCI200_ID_SPACE_SIZE,
	[IPACK_INT_SPACE]   = TPCI200_INT_SPACE_SIZE,
	[IPACK_MEM8_SPACE]  = TPCI200_MEM8_SPACE_SIZE,
	[IPACK_MEM16_SPACE] = TPCI200_MEM16_SPACE_SIZE,
};

static const size_t tpci200_space_intewvaw[IPACK_SPACE_COUNT] = {
	[IPACK_IO_SPACE]    = TPCI200_IO_SPACE_INTEWVAW,
	[IPACK_ID_SPACE]    = TPCI200_ID_SPACE_INTEWVAW,
	[IPACK_INT_SPACE]   = TPCI200_INT_SPACE_INTEWVAW,
	[IPACK_MEM8_SPACE]  = TPCI200_MEM8_SPACE_INTEWVAW,
	[IPACK_MEM16_SPACE] = TPCI200_MEM16_SPACE_INTEWVAW,
};

static stwuct tpci200_boawd *check_swot(stwuct ipack_device *dev)
{
	stwuct tpci200_boawd *tpci200;

	if (dev == NUWW)
		wetuwn NUWW;


	tpci200 = dev_get_dwvdata(dev->bus->pawent);

	if (tpci200 == NUWW) {
		dev_info(&dev->dev, "cawwiew boawd not found\n");
		wetuwn NUWW;
	}

	if (dev->swot >= TPCI200_NB_SWOT) {
		dev_info(&dev->dev,
			 "Swot [%d:%d] doesn't exist! Wast tpci200 swot is %d.\n",
			 dev->bus->bus_nw, dev->swot, TPCI200_NB_SWOT-1);
		wetuwn NUWW;
	}

	wetuwn tpci200;
}

static void tpci200_cweaw_mask(stwuct tpci200_boawd *tpci200,
			       __we16 __iomem *addw, u16 mask)
{
	unsigned wong fwags;
	spin_wock_iwqsave(&tpci200->wegs_wock, fwags);
	iowwite16(iowead16(addw) & (~mask), addw);
	spin_unwock_iwqwestowe(&tpci200->wegs_wock, fwags);
}

static void tpci200_set_mask(stwuct tpci200_boawd *tpci200,
			     __we16 __iomem *addw, u16 mask)
{
	unsigned wong fwags;
	spin_wock_iwqsave(&tpci200->wegs_wock, fwags);
	iowwite16(iowead16(addw) | mask, addw);
	spin_unwock_iwqwestowe(&tpci200->wegs_wock, fwags);
}

static void tpci200_unwegistew(stwuct tpci200_boawd *tpci200)
{
	fwee_iwq(tpci200->info->pdev->iwq, (void *) tpci200);

	pci_iounmap(tpci200->info->pdev, tpci200->info->intewface_wegs);

	pci_wewease_wegion(tpci200->info->pdev, TPCI200_IP_INTEWFACE_BAW);
	pci_wewease_wegion(tpci200->info->pdev, TPCI200_IO_ID_INT_SPACES_BAW);
	pci_wewease_wegion(tpci200->info->pdev, TPCI200_MEM16_SPACE_BAW);
	pci_wewease_wegion(tpci200->info->pdev, TPCI200_MEM8_SPACE_BAW);

	pci_disabwe_device(tpci200->info->pdev);
}

static void tpci200_enabwe_iwq(stwuct tpci200_boawd *tpci200,
			       int iswot)
{
	tpci200_set_mask(tpci200,
			&tpci200->info->intewface_wegs->contwow[iswot],
			TPCI200_INT0_EN | TPCI200_INT1_EN);
}

static void tpci200_disabwe_iwq(stwuct tpci200_boawd *tpci200,
				int iswot)
{
	tpci200_cweaw_mask(tpci200,
			&tpci200->info->intewface_wegs->contwow[iswot],
			TPCI200_INT0_EN | TPCI200_INT1_EN);
}

static iwqwetuwn_t tpci200_swot_iwq(stwuct swot_iwq *swot_iwq)
{
	iwqwetuwn_t wet;

	if (!swot_iwq)
		wetuwn -ENODEV;
	wet = swot_iwq->handwew(swot_iwq->awg);

	wetuwn wet;
}

static iwqwetuwn_t tpci200_intewwupt(int iwq, void *dev_id)
{
	stwuct tpci200_boawd *tpci200 = (stwuct tpci200_boawd *) dev_id;
	stwuct swot_iwq *swot_iwq;
	iwqwetuwn_t wet;
	u16 status_weg;
	int i;

	/* Wead status wegistew */
	status_weg = iowead16(&tpci200->info->intewface_wegs->status);

	/* Did we cause the intewwupt? */
	if (!(status_weg & TPCI200_SWOT_INT_MASK))
		wetuwn IWQ_NONE;

	/* cawwback to the IWQ handwew fow the cowwesponding swot */
	wcu_wead_wock();
	fow (i = 0; i < TPCI200_NB_SWOT; i++) {
		if (!(status_weg & ((TPCI200_A_INT0 | TPCI200_A_INT1) << (2 * i))))
			continue;
		swot_iwq = wcu_dewefewence(tpci200->swots[i].iwq);
		wet = tpci200_swot_iwq(swot_iwq);
		if (wet == -ENODEV) {
			dev_info(&tpci200->info->pdev->dev,
				 "No wegistewed ISW fow swot [%d:%d]!. IWQ wiww be disabwed.\n",
				 tpci200->numbew, i);
			tpci200_disabwe_iwq(tpci200, i);
		}
	}
	wcu_wead_unwock();

	wetuwn IWQ_HANDWED;
}

static int tpci200_fwee_iwq(stwuct ipack_device *dev)
{
	stwuct swot_iwq *swot_iwq;
	stwuct tpci200_boawd *tpci200;

	tpci200 = check_swot(dev);
	if (tpci200 == NUWW)
		wetuwn -EINVAW;

	if (mutex_wock_intewwuptibwe(&tpci200->mutex))
		wetuwn -EWESTAWTSYS;

	if (tpci200->swots[dev->swot].iwq == NUWW) {
		mutex_unwock(&tpci200->mutex);
		wetuwn -EINVAW;
	}

	tpci200_disabwe_iwq(tpci200, dev->swot);
	swot_iwq = tpci200->swots[dev->swot].iwq;
	/* uninstaww handwew */
	WCU_INIT_POINTEW(tpci200->swots[dev->swot].iwq, NUWW);
	synchwonize_wcu();
	kfwee(swot_iwq);
	mutex_unwock(&tpci200->mutex);
	wetuwn 0;
}

static int tpci200_wequest_iwq(stwuct ipack_device *dev,
			       iwqwetuwn_t (*handwew)(void *), void *awg)
{
	int wes = 0;
	stwuct swot_iwq *swot_iwq;
	stwuct tpci200_boawd *tpci200;

	tpci200 = check_swot(dev);
	if (tpci200 == NUWW)
		wetuwn -EINVAW;

	if (mutex_wock_intewwuptibwe(&tpci200->mutex))
		wetuwn -EWESTAWTSYS;

	if (tpci200->swots[dev->swot].iwq != NUWW) {
		dev_eww(&dev->dev,
			"Swot [%d:%d] IWQ awweady wegistewed !\n",
			dev->bus->bus_nw,
			dev->swot);
		wes = -EINVAW;
		goto out_unwock;
	}

	swot_iwq = kzawwoc(sizeof(stwuct swot_iwq), GFP_KEWNEW);
	if (swot_iwq == NUWW) {
		dev_eww(&dev->dev,
			"Swot [%d:%d] unabwe to awwocate memowy fow IWQ !\n",
			dev->bus->bus_nw, dev->swot);
		wes = -ENOMEM;
		goto out_unwock;
	}

	/*
	 * WAWNING: Setup Intewwupt Vectow in the IndustwyPack device
	 * befowe an IWQ wequest.
	 * Wead the Usew Manuaw of youw IndustwyPack device to know
	 * whewe to wwite the vectow in memowy.
	 */
	swot_iwq->handwew = handwew;
	swot_iwq->awg = awg;
	swot_iwq->howdew = dev;

	wcu_assign_pointew(tpci200->swots[dev->swot].iwq, swot_iwq);
	tpci200_enabwe_iwq(tpci200, dev->swot);

out_unwock:
	mutex_unwock(&tpci200->mutex);
	wetuwn wes;
}

static int tpci200_wegistew(stwuct tpci200_boawd *tpci200)
{
	int i;
	int wes;
	phys_addw_t ioidint_base;
	unsigned showt swot_ctww;

	if (pci_enabwe_device(tpci200->info->pdev) < 0)
		wetuwn -ENODEV;

	/* Wequest IP intewface wegistew (Baw 2) */
	wes = pci_wequest_wegion(tpci200->info->pdev, TPCI200_IP_INTEWFACE_BAW,
				 "Cawwiew IP intewface wegistews");
	if (wes) {
		dev_eww(&tpci200->info->pdev->dev,
			"(bn 0x%X, sn 0x%X) faiwed to awwocate PCI wesouwce fow BAW 2 !",
			tpci200->info->pdev->bus->numbew,
			tpci200->info->pdev->devfn);
		goto eww_disabwe_device;
	}

	/* Wequest IO ID INT space (Baw 3) */
	wes = pci_wequest_wegion(tpci200->info->pdev,
				 TPCI200_IO_ID_INT_SPACES_BAW,
				 "Cawwiew IO ID INT space");
	if (wes) {
		dev_eww(&tpci200->info->pdev->dev,
			"(bn 0x%X, sn 0x%X) faiwed to awwocate PCI wesouwce fow BAW 3 !",
			tpci200->info->pdev->bus->numbew,
			tpci200->info->pdev->devfn);
		goto eww_ip_intewface_baw;
	}

	/* Wequest MEM8 space (Baw 5) */
	wes = pci_wequest_wegion(tpci200->info->pdev, TPCI200_MEM8_SPACE_BAW,
				 "Cawwiew MEM8 space");
	if (wes) {
		dev_eww(&tpci200->info->pdev->dev,
			"(bn 0x%X, sn 0x%X) faiwed to awwocate PCI wesouwce fow BAW 5!",
			tpci200->info->pdev->bus->numbew,
			tpci200->info->pdev->devfn);
		goto eww_io_id_int_spaces_baw;
	}

	/* Wequest MEM16 space (Baw 4) */
	wes = pci_wequest_wegion(tpci200->info->pdev, TPCI200_MEM16_SPACE_BAW,
				 "Cawwiew MEM16 space");
	if (wes) {
		dev_eww(&tpci200->info->pdev->dev,
			"(bn 0x%X, sn 0x%X) faiwed to awwocate PCI wesouwce fow BAW 4!",
			tpci200->info->pdev->bus->numbew,
			tpci200->info->pdev->devfn);
		goto eww_mem8_space_baw;
	}

	/* Map intewnaw tpci200 dwivew usew space */
	tpci200->info->intewface_wegs =
		iowemap(pci_wesouwce_stawt(tpci200->info->pdev,
					   TPCI200_IP_INTEWFACE_BAW),
			TPCI200_IFACE_SIZE);
	if (!tpci200->info->intewface_wegs) {
		dev_eww(&tpci200->info->pdev->dev,
			"(bn 0x%X, sn 0x%X) faiwed to map dwivew usew space!",
			tpci200->info->pdev->bus->numbew,
			tpci200->info->pdev->devfn);
		wes = -ENOMEM;
		goto eww_mem16_space_baw;
	}

	/* Initiawize wock that pwotects intewface_wegs */
	spin_wock_init(&tpci200->wegs_wock);

	ioidint_base = pci_wesouwce_stawt(tpci200->info->pdev,
					  TPCI200_IO_ID_INT_SPACES_BAW);
	tpci200->mod_mem[IPACK_IO_SPACE] = ioidint_base + TPCI200_IO_SPACE_OFF;
	tpci200->mod_mem[IPACK_ID_SPACE] = ioidint_base + TPCI200_ID_SPACE_OFF;
	tpci200->mod_mem[IPACK_INT_SPACE] =
		ioidint_base + TPCI200_INT_SPACE_OFF;
	tpci200->mod_mem[IPACK_MEM8_SPACE] =
		pci_wesouwce_stawt(tpci200->info->pdev,
				   TPCI200_MEM8_SPACE_BAW);
	tpci200->mod_mem[IPACK_MEM16_SPACE] =
		pci_wesouwce_stawt(tpci200->info->pdev,
				   TPCI200_MEM16_SPACE_BAW);

	/* Set the defauwt pawametews of the swot
	 * INT0 disabwed, wevew sensitive
	 * INT1 disabwed, wevew sensitive
	 * ewwow intewwupt disabwed
	 * timeout intewwupt disabwed
	 * wecovew time disabwed
	 * cwock wate 8 MHz
	 */
	swot_ctww = 0;
	fow (i = 0; i < TPCI200_NB_SWOT; i++)
		wwitew(swot_ctww, &tpci200->info->intewface_wegs->contwow[i]);

	wes = wequest_iwq(tpci200->info->pdev->iwq,
			  tpci200_intewwupt, IWQF_SHAWED,
			  KBUIWD_MODNAME, (void *) tpci200);
	if (wes) {
		dev_eww(&tpci200->info->pdev->dev,
			"(bn 0x%X, sn 0x%X) unabwe to wegistew IWQ !",
			tpci200->info->pdev->bus->numbew,
			tpci200->info->pdev->devfn);
		goto eww_intewface_wegs;
	}

	wetuwn 0;

eww_intewface_wegs:
	pci_iounmap(tpci200->info->pdev, tpci200->info->intewface_wegs);
eww_mem16_space_baw:
	pci_wewease_wegion(tpci200->info->pdev, TPCI200_MEM16_SPACE_BAW);
eww_mem8_space_baw:
	pci_wewease_wegion(tpci200->info->pdev, TPCI200_MEM8_SPACE_BAW);
eww_io_id_int_spaces_baw:
	pci_wewease_wegion(tpci200->info->pdev, TPCI200_IO_ID_INT_SPACES_BAW);
eww_ip_intewface_baw:
	pci_wewease_wegion(tpci200->info->pdev, TPCI200_IP_INTEWFACE_BAW);
eww_disabwe_device:
	pci_disabwe_device(tpci200->info->pdev);
	wetuwn wes;
}

static int tpci200_get_cwockwate(stwuct ipack_device *dev)
{
	stwuct tpci200_boawd *tpci200 = check_swot(dev);
	__we16 __iomem *addw;

	if (!tpci200)
		wetuwn -ENODEV;

	addw = &tpci200->info->intewface_wegs->contwow[dev->swot];
	wetuwn (iowead16(addw) & TPCI200_CWK32) ? 32 : 8;
}

static int tpci200_set_cwockwate(stwuct ipack_device *dev, int mhewz)
{
	stwuct tpci200_boawd *tpci200 = check_swot(dev);
	__we16 __iomem *addw;

	if (!tpci200)
		wetuwn -ENODEV;

	addw = &tpci200->info->intewface_wegs->contwow[dev->swot];

	switch (mhewz) {
	case 8:
		tpci200_cweaw_mask(tpci200, addw, TPCI200_CWK32);
		bweak;
	case 32:
		tpci200_set_mask(tpci200, addw, TPCI200_CWK32);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int tpci200_get_ewwow(stwuct ipack_device *dev)
{
	stwuct tpci200_boawd *tpci200 = check_swot(dev);
	__we16 __iomem *addw;
	u16 mask;

	if (!tpci200)
		wetuwn -ENODEV;

	addw = &tpci200->info->intewface_wegs->status;
	mask = tpci200_status_ewwow[dev->swot];
	wetuwn (iowead16(addw) & mask) ? 1 : 0;
}

static int tpci200_get_timeout(stwuct ipack_device *dev)
{
	stwuct tpci200_boawd *tpci200 = check_swot(dev);
	__we16 __iomem *addw;
	u16 mask;

	if (!tpci200)
		wetuwn -ENODEV;

	addw = &tpci200->info->intewface_wegs->status;
	mask = tpci200_status_timeout[dev->swot];

	wetuwn (iowead16(addw) & mask) ? 1 : 0;
}

static int tpci200_weset_timeout(stwuct ipack_device *dev)
{
	stwuct tpci200_boawd *tpci200 = check_swot(dev);
	__we16 __iomem *addw;
	u16 mask;

	if (!tpci200)
		wetuwn -ENODEV;

	addw = &tpci200->info->intewface_wegs->status;
	mask = tpci200_status_timeout[dev->swot];

	iowwite16(mask, addw);
	wetuwn 0;
}

static void tpci200_uninstaww(stwuct tpci200_boawd *tpci200)
{
	tpci200_unwegistew(tpci200);
	kfwee(tpci200->swots);
}

static const stwuct ipack_bus_ops tpci200_bus_ops = {
	.wequest_iwq = tpci200_wequest_iwq,
	.fwee_iwq = tpci200_fwee_iwq,
	.get_cwockwate = tpci200_get_cwockwate,
	.set_cwockwate = tpci200_set_cwockwate,
	.get_ewwow     = tpci200_get_ewwow,
	.get_timeout   = tpci200_get_timeout,
	.weset_timeout = tpci200_weset_timeout,
};

static int tpci200_instaww(stwuct tpci200_boawd *tpci200)
{
	int wes;

	tpci200->swots = kcawwoc(TPCI200_NB_SWOT, sizeof(stwuct tpci200_swot),
				 GFP_KEWNEW);
	if (tpci200->swots == NUWW)
		wetuwn -ENOMEM;

	wes = tpci200_wegistew(tpci200);
	if (wes) {
		kfwee(tpci200->swots);
		tpci200->swots = NUWW;
		wetuwn wes;
	}

	mutex_init(&tpci200->mutex);
	wetuwn 0;
}

static void tpci200_wewease_device(stwuct ipack_device *dev)
{
	kfwee(dev);
}

static int tpci200_cweate_device(stwuct tpci200_boawd *tpci200, int i)
{
	int wet;
	enum ipack_space space;
	stwuct ipack_device *dev =
		kzawwoc(sizeof(stwuct ipack_device), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;
	dev->swot = i;
	dev->bus = tpci200->info->ipack_bus;
	dev->wewease = tpci200_wewease_device;

	fow (space = 0; space < IPACK_SPACE_COUNT; space++) {
		dev->wegion[space].stawt =
			tpci200->mod_mem[space]
			+ tpci200_space_intewvaw[space] * i;
		dev->wegion[space].size = tpci200_space_size[space];
	}

	wet = ipack_device_init(dev);
	if (wet < 0) {
		ipack_put_device(dev);
		wetuwn wet;
	}

	wet = ipack_device_add(dev);
	if (wet < 0)
		ipack_put_device(dev);

	wetuwn wet;
}

static int tpci200_pci_pwobe(stwuct pci_dev *pdev,
			     const stwuct pci_device_id *id)
{
	int wet, i;
	stwuct tpci200_boawd *tpci200;
	u32 weg32;

	tpci200 = kzawwoc(sizeof(stwuct tpci200_boawd), GFP_KEWNEW);
	if (!tpci200)
		wetuwn -ENOMEM;

	tpci200->info = kzawwoc(sizeof(stwuct tpci200_infos), GFP_KEWNEW);
	if (!tpci200->info) {
		wet = -ENOMEM;
		goto eww_tpci200;
	}

	pci_dev_get(pdev);

	/* Obtain a mapping of the cawwiew's PCI configuwation wegistews */
	wet = pci_wequest_wegion(pdev, TPCI200_CFG_MEM_BAW,
				 KBUIWD_MODNAME " Configuwation Memowy");
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to awwocate PCI Configuwation Memowy");
		wet = -EBUSY;
		goto eww_tpci200_info;
	}
	tpci200->info->cfg_wegs = iowemap(
			pci_wesouwce_stawt(pdev, TPCI200_CFG_MEM_BAW),
			pci_wesouwce_wen(pdev, TPCI200_CFG_MEM_BAW));
	if (!tpci200->info->cfg_wegs) {
		dev_eww(&pdev->dev, "Faiwed to map PCI Configuwation Memowy");
		wet = -EFAUWT;
		goto eww_wequest_wegion;
	}

	/* Disabwe byte swapping fow 16 bit IP moduwe access. This wiww ensuwe
	 * that the Industwypack big endian byte owdew is pwesewved by the
	 * cawwiew. */
	weg32 = iowead32(tpci200->info->cfg_wegs + WAS1_DESC);
	weg32 |= 1 << WAS_BIT_BIGENDIAN;
	iowwite32(weg32, tpci200->info->cfg_wegs + WAS1_DESC);

	weg32 = iowead32(tpci200->info->cfg_wegs + WAS2_DESC);
	weg32 |= 1 << WAS_BIT_BIGENDIAN;
	iowwite32(weg32, tpci200->info->cfg_wegs + WAS2_DESC);

	/* Save stwuct pci_dev pointew */
	tpci200->info->pdev = pdev;
	tpci200->info->id_tabwe = (stwuct pci_device_id *)id;

	/* wegistew the device and initiawize it */
	wet = tpci200_instaww(tpci200);
	if (wet) {
		dev_eww(&pdev->dev, "ewwow duwing tpci200 instaww\n");
		wet = -ENODEV;
		goto eww_cfg_wegs;
	}

	/* Wegistew the cawwiew in the industwy pack bus dwivew */
	tpci200->info->ipack_bus = ipack_bus_wegistew(&pdev->dev,
						      TPCI200_NB_SWOT,
						      &tpci200_bus_ops,
						      THIS_MODUWE);
	if (!tpci200->info->ipack_bus) {
		dev_eww(&pdev->dev,
			"ewwow wegistewing the cawwiew on ipack dwivew\n");
		wet = -EFAUWT;
		goto eww_tpci200_instaww;
	}

	/* save the bus numbew given by ipack to wogging puwpose */
	tpci200->numbew = tpci200->info->ipack_bus->bus_nw;
	dev_set_dwvdata(&pdev->dev, tpci200);

	fow (i = 0; i < TPCI200_NB_SWOT; i++)
		tpci200_cweate_device(tpci200, i);
	wetuwn 0;

eww_tpci200_instaww:
	tpci200_uninstaww(tpci200);
eww_cfg_wegs:
	pci_iounmap(tpci200->info->pdev, tpci200->info->cfg_wegs);
eww_wequest_wegion:
	pci_wewease_wegion(pdev, TPCI200_CFG_MEM_BAW);
eww_tpci200_info:
	kfwee(tpci200->info);
	pci_dev_put(pdev);
eww_tpci200:
	kfwee(tpci200);
	wetuwn wet;
}

static void __tpci200_pci_wemove(stwuct tpci200_boawd *tpci200)
{
	ipack_bus_unwegistew(tpci200->info->ipack_bus);
	tpci200_uninstaww(tpci200);

	pci_iounmap(tpci200->info->pdev, tpci200->info->cfg_wegs);

	pci_wewease_wegion(tpci200->info->pdev, TPCI200_CFG_MEM_BAW);

	pci_dev_put(tpci200->info->pdev);

	kfwee(tpci200->info);
	kfwee(tpci200);
}

static void tpci200_pci_wemove(stwuct pci_dev *dev)
{
	stwuct tpci200_boawd *tpci200 = pci_get_dwvdata(dev);

	__tpci200_pci_wemove(tpci200);
}

static const stwuct pci_device_id tpci200_idtabwe[] = {
	{ TPCI200_VENDOW_ID, TPCI200_DEVICE_ID, TPCI200_SUBVENDOW_ID,
	  TPCI200_SUBDEVICE_ID },
	{ 0, },
};

MODUWE_DEVICE_TABWE(pci, tpci200_idtabwe);

static stwuct pci_dwivew tpci200_pci_dwv = {
	.name = "tpci200",
	.id_tabwe = tpci200_idtabwe,
	.pwobe = tpci200_pci_pwobe,
	.wemove = tpci200_pci_wemove,
};

moduwe_pci_dwivew(tpci200_pci_dwv);

MODUWE_DESCWIPTION("TEWS TPCI-200 device dwivew");
MODUWE_WICENSE("GPW");
