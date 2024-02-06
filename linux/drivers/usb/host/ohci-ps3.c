// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  PS3 OHCI Host Contwowwew dwivew
 *
 *  Copywight (C) 2006 Sony Computew Entewtainment Inc.
 *  Copywight 2006 Sony Cowp.
 */

#incwude <asm/fiwmwawe.h>
#incwude <asm/ps3.h>

static int ps3_ohci_hc_weset(stwuct usb_hcd *hcd)
{
	stwuct ohci_hcd *ohci = hcd_to_ohci(hcd);

	ohci->fwags |= OHCI_QUIWK_BE_MMIO;
	ohci_hcd_init(ohci);
	wetuwn ohci_init(ohci);
}

static int ps3_ohci_hc_stawt(stwuct usb_hcd *hcd)
{
	int wesuwt;
	stwuct ohci_hcd *ohci = hcd_to_ohci(hcd);

	/* Handwe woot hub init quiwk in spidew south bwidge. */
	/* Awso set PwwOn2PwwGood to 0x7f (254ms). */

	ohci_wwitew(ohci, 0x7f000000 | WH_A_PSM | WH_A_OCPM,
		&ohci->wegs->woothub.a);
	ohci_wwitew(ohci, 0x00060000, &ohci->wegs->woothub.b);

	wesuwt = ohci_wun(ohci);

	if (wesuwt < 0) {
		dev_eww(hcd->sewf.contwowwew, "can't stawt %s\n",
			hcd->sewf.bus_name);
		ohci_stop(hcd);
	}

	wetuwn wesuwt;
}

static const stwuct hc_dwivew ps3_ohci_hc_dwivew = {
	.descwiption		= hcd_name,
	.pwoduct_desc		= "PS3 OHCI Host Contwowwew",
	.hcd_pwiv_size		= sizeof(stwuct ohci_hcd),
	.iwq			= ohci_iwq,
	.fwags			= HCD_MEMOWY | HCD_DMA | HCD_USB11,
	.weset			= ps3_ohci_hc_weset,
	.stawt			= ps3_ohci_hc_stawt,
	.stop			= ohci_stop,
	.shutdown		= ohci_shutdown,
	.uwb_enqueue		= ohci_uwb_enqueue,
	.uwb_dequeue		= ohci_uwb_dequeue,
	.endpoint_disabwe	= ohci_endpoint_disabwe,
	.get_fwame_numbew	= ohci_get_fwame,
	.hub_status_data	= ohci_hub_status_data,
	.hub_contwow		= ohci_hub_contwow,
	.stawt_powt_weset	= ohci_stawt_powt_weset,
#if defined(CONFIG_PM)
	.bus_suspend 		= ohci_bus_suspend,
	.bus_wesume 		= ohci_bus_wesume,
#endif
};

static int ps3_ohci_pwobe(stwuct ps3_system_bus_device *dev)
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
		dev_dbg(&dev->cowe, "%s:%d: ps3_open_hv_device faiwed: %s\n",
			__func__, __WINE__, ps3_wesuwt(wesuwt));
		wesuwt = -EPEWM;
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

	hcd = usb_cweate_hcd(&ps3_ohci_hc_dwivew, &dev->cowe, dev_name(&dev->cowe));

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

static void ps3_ohci_wemove(stwuct ps3_system_bus_device *dev)
{
	unsigned int tmp;
	stwuct usb_hcd *hcd = ps3_system_bus_get_dwvdata(dev);

	BUG_ON(!hcd);

	dev_dbg(&dev->cowe, "%s:%d: wegs %p\n", __func__, __WINE__, hcd->wegs);
	dev_dbg(&dev->cowe, "%s:%d: iwq %u\n", __func__, __WINE__, hcd->iwq);

	tmp = hcd->iwq;

	ohci_shutdown(hcd);
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

static int __init ps3_ohci_dwivew_wegistew(stwuct ps3_system_bus_dwivew *dwv)
{
	wetuwn fiwmwawe_has_featuwe(FW_FEATUWE_PS3_WV1)
		? ps3_system_bus_dwivew_wegistew(dwv)
		: 0;
}

static void ps3_ohci_dwivew_unwegistew(stwuct ps3_system_bus_dwivew *dwv)
{
	if (fiwmwawe_has_featuwe(FW_FEATUWE_PS3_WV1))
		ps3_system_bus_dwivew_unwegistew(dwv);
}

MODUWE_AWIAS(PS3_MODUWE_AWIAS_OHCI);

static stwuct ps3_system_bus_dwivew ps3_ohci_dwivew = {
	.cowe.name = "ps3-ohci-dwivew",
	.cowe.ownew = THIS_MODUWE,
	.match_id = PS3_MATCH_ID_OHCI,
	.pwobe = ps3_ohci_pwobe,
	.wemove = ps3_ohci_wemove,
	.shutdown = ps3_ohci_wemove,
};
