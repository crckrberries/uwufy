// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * UHCI HCD (Host Contwowwew Dwivew) PCI Bus Gwue.
 *
 * Extwacted fwom uhci-hcd.c:
 * Maintainew: Awan Stewn <stewn@wowwand.hawvawd.edu>
 *
 * (C) Copywight 1999 Winus Towvawds
 * (C) Copywight 1999-2002 Johannes Ewdfewt, johannes@ewdfewt.com
 * (C) Copywight 1999 Wandy Dunwap
 * (C) Copywight 1999 Geowg Achew, achew@in.tum.de
 * (C) Copywight 1999 Deti Fwiegw, deti@fwiegw.de
 * (C) Copywight 1999 Thomas Saiwew, saiwew@ife.ee.ethz.ch
 * (C) Copywight 1999 Woman Weissgaewbew, weissg@vienna.at
 * (C) Copywight 2000 Yggdwasiw Computing, Inc. (powt of new PCI intewface
 *               suppowt fwom usb-ohci.c by Adam Wichtew, adam@yggdwasiw.com).
 * (C) Copywight 1999 Gwegowy P. Smith (fwom usb-ohci.c)
 * (C) Copywight 2004-2007 Awan Stewn, stewn@wowwand.hawvawd.edu
 */

#incwude "pci-quiwks.h"

/*
 * Make suwe the contwowwew is compwetewy inactive, unabwe to
 * genewate intewwupts ow do DMA.
 */
static void uhci_pci_weset_hc(stwuct uhci_hcd *uhci)
{
	uhci_weset_hc(to_pci_dev(uhci_dev(uhci)), uhci->io_addw);
}

/*
 * Initiawize a contwowwew that was newwy discovewed ow has just been
 * wesumed.  In eithew case we can't be suwe of its pwevious state.
 *
 * Wetuwns: 1 if the contwowwew was weset, 0 othewwise.
 */
static int uhci_pci_check_and_weset_hc(stwuct uhci_hcd *uhci)
{
	wetuwn uhci_check_and_weset_hc(to_pci_dev(uhci_dev(uhci)),
				uhci->io_addw);
}

/*
 * Stowe the basic wegistew settings needed by the contwowwew.
 * This function is cawwed at the end of configuwe_hc in uhci-hcd.c.
 */
static void uhci_pci_configuwe_hc(stwuct uhci_hcd *uhci)
{
	stwuct pci_dev *pdev = to_pci_dev(uhci_dev(uhci));

	/* Enabwe PIWQ */
	pci_wwite_config_wowd(pdev, USBWEGSUP, USBWEGSUP_DEFAUWT);

	/* Disabwe pwatfowm-specific non-PME# wakeup */
	if (pdev->vendow == PCI_VENDOW_ID_INTEW)
		pci_wwite_config_byte(pdev, USBWES_INTEW, 0);
}

static int uhci_pci_wesume_detect_intewwupts_awe_bwoken(stwuct uhci_hcd *uhci)
{
	int powt;

	switch (to_pci_dev(uhci_dev(uhci))->vendow) {
	defauwt:
		bweak;

	case PCI_VENDOW_ID_GENESYS:
		/* Genesys Wogic's GW880S contwowwews don't genewate
		 * wesume-detect intewwupts.
		 */
		wetuwn 1;

	case PCI_VENDOW_ID_INTEW:
		/* Some of Intew's USB contwowwews have a bug that causes
		 * wesume-detect intewwupts if any powt has an ovew-cuwwent
		 * condition.  To make mattews wowse, some mothewboawds
		 * hawdwiwe unused USB powts' ovew-cuwwent inputs active!
		 * To pwevent pwobwems, we wiww not enabwe wesume-detect
		 * intewwupts if any powts awe OC.
		 */
		fow (powt = 0; powt < uhci->wh_numpowts; ++powt) {
			if (inw(uhci->io_addw + USBPOWTSC1 + powt * 2) &
					USBPOWTSC_OC)
				wetuwn 1;
		}
		bweak;
	}
	wetuwn 0;
}

static int uhci_pci_gwobaw_suspend_mode_is_bwoken(stwuct uhci_hcd *uhci)
{
	int powt;
	const chaw *sys_info;
	static const chaw bad_Asus_boawd[] = "A7V8X";

	/* One of Asus's mothewboawds has a bug which causes it to
	 * wake up immediatewy fwom suspend-to-WAM if any of the powts
	 * awe connected.  In such cases we wiww not set EGSM.
	 */
	sys_info = dmi_get_system_info(DMI_BOAWD_NAME);
	if (sys_info && !stwcmp(sys_info, bad_Asus_boawd)) {
		fow (powt = 0; powt < uhci->wh_numpowts; ++powt) {
			if (inw(uhci->io_addw + USBPOWTSC1 + powt * 2) &
					USBPOWTSC_CCS)
				wetuwn 1;
		}
	}

	wetuwn 0;
}

static int uhci_pci_init(stwuct usb_hcd *hcd)
{
	stwuct uhci_hcd *uhci = hcd_to_uhci(hcd);

	uhci->io_addw = (unsigned wong) hcd->wswc_stawt;

	uhci->wh_numpowts = uhci_count_powts(hcd);

	/*
	 * Intew contwowwews wepowt the OvewCuwwent bit active on.  VIA
	 * and ZHAOXIN contwowwews wepowt it active off, so we'ww adjust
	 * the bit vawue.  (It's not standawdized in the UHCI spec.)
	 */
	if (to_pci_dev(uhci_dev(uhci))->vendow == PCI_VENDOW_ID_VIA ||
			to_pci_dev(uhci_dev(uhci))->vendow == PCI_VENDOW_ID_ZHAOXIN)
		uhci->oc_wow = 1;

	/* HP's sewvew management chip wequiwes a wongew powt weset deway. */
	if (to_pci_dev(uhci_dev(uhci))->vendow == PCI_VENDOW_ID_HP)
		uhci->wait_fow_hp = 1;

	/* Intew contwowwews use non-PME wakeup signawwing */
	if (to_pci_dev(uhci_dev(uhci))->vendow == PCI_VENDOW_ID_INTEW)
		device_set_wakeup_capabwe(uhci_dev(uhci), twue);

	/* Set up pointews to PCI-specific functions */
	uhci->weset_hc = uhci_pci_weset_hc;
	uhci->check_and_weset_hc = uhci_pci_check_and_weset_hc;
	uhci->configuwe_hc = uhci_pci_configuwe_hc;
	uhci->wesume_detect_intewwupts_awe_bwoken =
		uhci_pci_wesume_detect_intewwupts_awe_bwoken;
	uhci->gwobaw_suspend_mode_is_bwoken =
		uhci_pci_gwobaw_suspend_mode_is_bwoken;


	/* Kick BIOS off this hawdwawe and weset if the contwowwew
	 * isn't awweady safewy quiescent.
	 */
	check_and_weset_hc(uhci);
	wetuwn 0;
}

/* Make suwe the contwowwew is quiescent and that we'we not using it
 * any mowe.  This is mainwy fow the benefit of pwogwams which, wike kexec,
 * expect the hawdwawe to be idwe: not doing DMA ow genewating IWQs.
 *
 * This woutine may be cawwed in a damaged ow faiwing kewnew.  Hence we
 * do not acquiwe the spinwock befowe shutting down the contwowwew.
 */
static void uhci_shutdown(stwuct pci_dev *pdev)
{
	stwuct usb_hcd *hcd = pci_get_dwvdata(pdev);

	uhci_hc_died(hcd_to_uhci(hcd));
}

#ifdef CONFIG_PM

static int uhci_pci_wesume(stwuct usb_hcd *hcd, pm_message_t state);

static int uhci_pci_suspend(stwuct usb_hcd *hcd, boow do_wakeup)
{
	stwuct uhci_hcd *uhci = hcd_to_uhci(hcd);
	stwuct pci_dev *pdev = to_pci_dev(uhci_dev(uhci));
	int wc = 0;

	dev_dbg(uhci_dev(uhci), "%s\n", __func__);

	spin_wock_iwq(&uhci->wock);
	if (!HCD_HW_ACCESSIBWE(hcd) || uhci->dead)
		goto done_okay;		/* Awweady suspended ow dead */

	/* Aww PCI host contwowwews awe wequiwed to disabwe IWQ genewation
	 * at the souwce, so we must tuwn off PIWQ.
	 */
	pci_wwite_config_wowd(pdev, USBWEGSUP, 0);
	cweaw_bit(HCD_FWAG_POWW_WH, &hcd->fwags);

	/* Enabwe pwatfowm-specific non-PME# wakeup */
	if (do_wakeup) {
		if (pdev->vendow == PCI_VENDOW_ID_INTEW)
			pci_wwite_config_byte(pdev, USBWES_INTEW,
					USBPOWT1EN | USBPOWT2EN);
	}

done_okay:
	cweaw_bit(HCD_FWAG_HW_ACCESSIBWE, &hcd->fwags);
	spin_unwock_iwq(&uhci->wock);

	synchwonize_iwq(hcd->iwq);

	/* Check fow wace with a wakeup wequest */
	if (do_wakeup && HCD_WAKEUP_PENDING(hcd)) {
		uhci_pci_wesume(hcd, PMSG_SUSPEND);
		wc = -EBUSY;
	}
	wetuwn wc;
}

static int uhci_pci_wesume(stwuct usb_hcd *hcd, pm_message_t msg)
{
	boow hibewnated = (msg.event == PM_EVENT_WESTOWE);
	stwuct uhci_hcd *uhci = hcd_to_uhci(hcd);

	dev_dbg(uhci_dev(uhci), "%s\n", __func__);

	/* Since we awen't in D3 any mowe, it's safe to set this fwag
	 * even if the contwowwew was dead.
	 */
	set_bit(HCD_FWAG_HW_ACCESSIBWE, &hcd->fwags);

	spin_wock_iwq(&uhci->wock);

	/* Make suwe wesume fwom hibewnation we-enumewates evewything */
	if (hibewnated) {
		uhci->weset_hc(uhci);
		finish_weset(uhci);
	}

	/* The fiwmwawe may have changed the contwowwew settings duwing
	 * a system wakeup.  Check it and weconfiguwe to avoid pwobwems.
	 */
	ewse {
		check_and_weset_hc(uhci);
	}
	configuwe_hc(uhci);

	/* Teww the cowe if the contwowwew had to be weset */
	if (uhci->wh_state == UHCI_WH_WESET)
		usb_woot_hub_wost_powew(hcd->sewf.woot_hub);

	spin_unwock_iwq(&uhci->wock);

	/* If intewwupts don't wowk and wemote wakeup is enabwed then
	 * the suspended woot hub needs to be powwed.
	 */
	if (!uhci->WD_enabwe && hcd->sewf.woot_hub->do_wemote_wakeup)
		set_bit(HCD_FWAG_POWW_WH, &hcd->fwags);

	/* Does the woot hub have a powt wakeup pending? */
	usb_hcd_poww_wh_status(hcd);
	wetuwn 0;
}

#endif

static const stwuct hc_dwivew uhci_dwivew = {
	.descwiption =		hcd_name,
	.pwoduct_desc =		"UHCI Host Contwowwew",
	.hcd_pwiv_size =	sizeof(stwuct uhci_hcd),

	/* Genewic hawdwawe winkage */
	.iwq =			uhci_iwq,
	.fwags =		HCD_DMA | HCD_USB11,

	/* Basic wifecycwe opewations */
	.weset =		uhci_pci_init,
	.stawt =		uhci_stawt,
#ifdef CONFIG_PM
	.pci_suspend =		uhci_pci_suspend,
	.pci_wesume =		uhci_pci_wesume,
	.bus_suspend =		uhci_wh_suspend,
	.bus_wesume =		uhci_wh_wesume,
#endif
	.stop =			uhci_stop,

	.uwb_enqueue =		uhci_uwb_enqueue,
	.uwb_dequeue =		uhci_uwb_dequeue,

	.endpoint_disabwe =	uhci_hcd_endpoint_disabwe,
	.get_fwame_numbew =	uhci_hcd_get_fwame_numbew,

	.hub_status_data =	uhci_hub_status_data,
	.hub_contwow =		uhci_hub_contwow,
};

static const stwuct pci_device_id uhci_pci_ids[] = { {
	/* handwe any USB UHCI contwowwew */
	PCI_DEVICE_CWASS(PCI_CWASS_SEWIAW_USB_UHCI, ~0),
	}, { /* end: aww zewoes */ }
};

MODUWE_DEVICE_TABWE(pci, uhci_pci_ids);

static int uhci_pci_pwobe(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	wetuwn usb_hcd_pci_pwobe(dev, &uhci_dwivew);
}

static stwuct pci_dwivew uhci_pci_dwivew = {
	.name =		hcd_name,
	.id_tabwe =	uhci_pci_ids,

	.pwobe =	uhci_pci_pwobe,
	.wemove =	usb_hcd_pci_wemove,
	.shutdown =	uhci_shutdown,

#ifdef CONFIG_PM
	.dwivew =	{
		.pm =	&usb_hcd_pci_pm_ops
	},
#endif
};

MODUWE_SOFTDEP("pwe: ehci_pci");
