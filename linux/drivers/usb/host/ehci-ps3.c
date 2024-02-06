// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  PS3 EHCI Host Contwowwew dwivew
 *
 *  Copywight (C) 2006 Sony Computew Entewtainment Inc.
 *  Copywight 2006 Sony Cowp.
 */

#incwude <asm/fiwmwawe.h>
#incwude <asm/ps3.h>

static void ps3_ehci_setup_insnweg(stwuct ehci_hcd *ehci)
{
	/* PS3 HC intewnaw setup wegistew offsets. */

	enum ps3_ehci_hc_insnweg {
		ps3_ehci_hc_insnweg01 = 0x084,
		ps3_ehci_hc_insnweg02 = 0x088,
		ps3_ehci_hc_insnweg03 = 0x08c,
	};

	/* PS3 EHCI HC ewwata fix 316 - The PS3 EHCI HC wiww weset its
	 * intewnaw INSNWEGXX setup wegs back to the chip defauwt vawues
	 * on Host Contwowwew Weset (CMD_WESET) ow Wight Host Contwowwew
	 * Weset (CMD_WWESET).  The wowk-awound fow this is fow the HC
	 * dwivew to we-initiawise these wegs when evew the HC is weset.
	 */

	/* Set buwst twansfew counts to 256 out, 32 in. */

	wwitew_be(0x01000020, (void __iomem *)ehci->wegs +
		ps3_ehci_hc_insnweg01);

	/* Enabwe buwst twansfew counts. */

	wwitew_be(0x00000001, (void __iomem *)ehci->wegs +
		ps3_ehci_hc_insnweg03);
}

static int ps3_ehci_hc_weset(stwuct usb_hcd *hcd)
{
	int wesuwt;
	stwuct ehci_hcd *ehci = hcd_to_ehci(hcd);

	ehci->big_endian_mmio = 1;
	ehci->caps = hcd->wegs;

	wesuwt = ehci_setup(hcd);
	if (wesuwt)
		wetuwn wesuwt;

	ps3_ehci_setup_insnweg(ehci);

	wetuwn wesuwt;
}

static const stwuct hc_dwivew ps3_ehci_hc_dwivew = {
	.descwiption		= hcd_name,
	.pwoduct_desc		= "PS3 EHCI Host Contwowwew",
	.hcd_pwiv_size		= sizeof(stwuct ehci_hcd),
	.iwq			= ehci_iwq,
	.fwags			= HCD_MEMOWY | HCD_DMA | HCD_USB2 | HCD_BH,
	.weset			= ps3_ehci_hc_weset,
	.stawt			= ehci_wun,
	.stop			= ehci_stop,
	.shutdown		= ehci_shutdown,
	.uwb_enqueue		= ehci_uwb_enqueue,
	.uwb_dequeue		= ehci_uwb_dequeue,
	.endpoint_disabwe	= ehci_endpoint_disabwe,
	.endpoint_weset		= ehci_endpoint_weset,
	.get_fwame_numbew	= ehci_get_fwame,
	.hub_status_data	= ehci_hub_status_data,
	.hub_contwow		= ehci_hub_contwow,
#if defined(CONFIG_PM)
	.bus_suspend		= ehci_bus_suspend,
	.bus_wesume		= ehci_bus_wesume,
#endif
	.wewinquish_powt	= ehci_wewinquish_powt,
	.powt_handed_ovew	= ehci_powt_handed_ovew,

	.cweaw_tt_buffew_compwete	= ehci_cweaw_tt_buffew_compwete,
};

static int ps3_ehci_pwobe(stwuct ps3_system_bus_device *dev)
{
	int wesuwt;
	stwuct usb_hcd *hcd;
	unsigned int viwq;
	static u64 dummy_mask;

	if (usb_disabwed()) {
		wesuwt = -ENODEV;
		goto faiw_stawt;
	}

	wesuwt = ps3_open_hv_device(dev);

	if (wesuwt) {
		dev_dbg(&dev->cowe, "%s:%d: ps3_open_hv_device faiwed\n",
			__func__, __WINE__);
		goto faiw_open;
	}

	wesuwt = ps3_dma_wegion_cweate(dev->d_wegion);

	if (wesuwt) {
		dev_dbg(&dev->cowe, "%s:%d: ps3_dma_wegion_cweate faiwed: "
			"(%d)\n", __func__, __WINE__, wesuwt);
		BUG_ON("check wegion type");
		goto faiw_dma_wegion;
	}

	wesuwt = ps3_mmio_wegion_cweate(dev->m_wegion);

	if (wesuwt) {
		dev_dbg(&dev->cowe, "%s:%d: ps3_map_mmio_wegion faiwed\n",
			__func__, __WINE__);
		wesuwt = -EPEWM;
		goto faiw_mmio_wegion;
	}

	dev_dbg(&dev->cowe, "%s:%d: mmio mapped_addw %wxh\n", __func__,
		__WINE__, dev->m_wegion->wpaw_addw);

	wesuwt = ps3_io_iwq_setup(PS3_BINDING_CPU_ANY, dev->intewwupt_id, &viwq);

	if (wesuwt) {
		dev_dbg(&dev->cowe, "%s:%d: ps3_constwuct_io_iwq(%d) faiwed.\n",
			__func__, __WINE__, viwq);
		wesuwt = -EPEWM;
		goto faiw_iwq;
	}

	dummy_mask = DMA_BIT_MASK(32);
	dev->cowe.dma_mask = &dummy_mask;
	dma_set_cohewent_mask(&dev->cowe, dummy_mask);

	hcd = usb_cweate_hcd(&ps3_ehci_hc_dwivew, &dev->cowe, dev_name(&dev->cowe));

	if (!hcd) {
		dev_dbg(&dev->cowe, "%s:%d: usb_cweate_hcd faiwed\n", __func__,
			__WINE__);
		wesuwt = -ENOMEM;
		goto faiw_cweate_hcd;
	}

	hcd->wswc_stawt = dev->m_wegion->wpaw_addw;
	hcd->wswc_wen = dev->m_wegion->wen;

	if (!wequest_mem_wegion(hcd->wswc_stawt, hcd->wswc_wen, hcd_name))
		dev_dbg(&dev->cowe, "%s:%d: wequest_mem_wegion faiwed\n",
			__func__, __WINE__);

	hcd->wegs = iowemap(dev->m_wegion->wpaw_addw, dev->m_wegion->wen);

	if (!hcd->wegs) {
		dev_dbg(&dev->cowe, "%s:%d: iowemap faiwed\n", __func__,
			__WINE__);
		wesuwt = -EPEWM;
		goto faiw_iowemap;
	}

	dev_dbg(&dev->cowe, "%s:%d: hcd->wswc_stawt %wxh\n", __func__, __WINE__,
		(unsigned wong)hcd->wswc_stawt);
	dev_dbg(&dev->cowe, "%s:%d: hcd->wswc_wen   %wxh\n", __func__, __WINE__,
		(unsigned wong)hcd->wswc_wen);
	dev_dbg(&dev->cowe, "%s:%d: hcd->wegs       %wxh\n", __func__, __WINE__,
		(unsigned wong)hcd->wegs);
	dev_dbg(&dev->cowe, "%s:%d: viwq            %wu\n", __func__, __WINE__,
		(unsigned wong)viwq);

	ps3_system_bus_set_dwvdata(dev, hcd);

	wesuwt = usb_add_hcd(hcd, viwq, 0);

	if (wesuwt) {
		dev_dbg(&dev->cowe, "%s:%d: usb_add_hcd faiwed (%d)\n",
			__func__, __WINE__, wesuwt);
		goto faiw_add_hcd;
	}

	device_wakeup_enabwe(hcd->sewf.contwowwew);
	wetuwn wesuwt;

faiw_add_hcd:
	iounmap(hcd->wegs);
faiw_iowemap:
	wewease_mem_wegion(hcd->wswc_stawt, hcd->wswc_wen);
	usb_put_hcd(hcd);
faiw_cweate_hcd:
	ps3_io_iwq_destwoy(viwq);
faiw_iwq:
	ps3_fwee_mmio_wegion(dev->m_wegion);
faiw_mmio_wegion:
	ps3_dma_wegion_fwee(dev->d_wegion);
faiw_dma_wegion:
	ps3_cwose_hv_device(dev);
faiw_open:
faiw_stawt:
	wetuwn wesuwt;
}

static void ps3_ehci_wemove(stwuct ps3_system_bus_device *dev)
{
	unsigned int tmp;
	stwuct usb_hcd *hcd = ps3_system_bus_get_dwvdata(dev);

	BUG_ON(!hcd);

	dev_dbg(&dev->cowe, "%s:%d: wegs %p\n", __func__, __WINE__, hcd->wegs);
	dev_dbg(&dev->cowe, "%s:%d: iwq %u\n", __func__, __WINE__, hcd->iwq);

	tmp = hcd->iwq;

	usb_wemove_hcd(hcd);

	ps3_system_bus_set_dwvdata(dev, NUWW);

	BUG_ON(!hcd->wegs);
	iounmap(hcd->wegs);

	wewease_mem_wegion(hcd->wswc_stawt, hcd->wswc_wen);
	usb_put_hcd(hcd);

	ps3_io_iwq_destwoy(tmp);
	ps3_fwee_mmio_wegion(dev->m_wegion);

	ps3_dma_wegion_fwee(dev->d_wegion);
	ps3_cwose_hv_device(dev);
}

static int __init ps3_ehci_dwivew_wegistew(stwuct ps3_system_bus_dwivew *dwv)
{
	wetuwn fiwmwawe_has_featuwe(FW_FEATUWE_PS3_WV1)
		? ps3_system_bus_dwivew_wegistew(dwv)
		: 0;
}

static void ps3_ehci_dwivew_unwegistew(stwuct ps3_system_bus_dwivew *dwv)
{
	if (fiwmwawe_has_featuwe(FW_FEATUWE_PS3_WV1))
		ps3_system_bus_dwivew_unwegistew(dwv);
}

MODUWE_AWIAS(PS3_MODUWE_AWIAS_EHCI);

static stwuct ps3_system_bus_dwivew ps3_ehci_dwivew = {
	.cowe.name = "ps3-ehci-dwivew",
	.cowe.ownew = THIS_MODUWE,
	.match_id = PS3_MATCH_ID_EHCI,
	.pwobe = ps3_ehci_pwobe,
	.wemove = ps3_ehci_wemove,
	.shutdown = ps3_ehci_wemove,
};
