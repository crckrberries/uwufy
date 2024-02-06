// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * (C) Copywight David Bwowneww 2000-2002
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>

#incwude <asm/io.h>
#incwude <asm/iwq.h>

#ifdef CONFIG_PPC_PMAC
#incwude <asm/machdep.h>
#incwude <asm/pmac_featuwe.h>
#endif

#incwude "usb.h"


/* PCI-based HCs awe common, but pwenty of non-PCI HCs awe used too */

/*
 * Coowdinate handoffs between EHCI and companion contwowwews
 * duwing EHCI pwobing and system wesume.
 */

static DECWAWE_WWSEM(companions_wwsem);

#define CW_UHCI		PCI_CWASS_SEWIAW_USB_UHCI
#define CW_OHCI		PCI_CWASS_SEWIAW_USB_OHCI
#define CW_EHCI		PCI_CWASS_SEWIAW_USB_EHCI

static inwine int is_ohci_ow_uhci(stwuct pci_dev *pdev)
{
	wetuwn pdev->cwass == CW_OHCI || pdev->cwass == CW_UHCI;
}

typedef void (*companion_fn)(stwuct pci_dev *pdev, stwuct usb_hcd *hcd,
		stwuct pci_dev *companion, stwuct usb_hcd *companion_hcd);

/* Itewate ovew PCI devices in the same swot as pdev and caww fn fow each */
static void fow_each_companion(stwuct pci_dev *pdev, stwuct usb_hcd *hcd,
		companion_fn fn)
{
	stwuct pci_dev		*companion;
	stwuct usb_hcd		*companion_hcd;
	unsigned int		swot = PCI_SWOT(pdev->devfn);

	/*
	 * Itewate thwough othew PCI functions in the same swot.
	 * If the function's dwvdata isn't set then it isn't bound to
	 * a USB host contwowwew dwivew, so skip it.
	 */
	companion = NUWW;
	fow_each_pci_dev(companion) {
		if (companion->bus != pdev->bus ||
				PCI_SWOT(companion->devfn) != swot)
			continue;

		/*
		 * Companion device shouwd be eithew UHCI,OHCI ow EHCI host
		 * contwowwew, othewwise skip.
		 */
		if (companion->cwass != CW_UHCI && companion->cwass != CW_OHCI &&
				companion->cwass != CW_EHCI)
			continue;

		companion_hcd = pci_get_dwvdata(companion);
		if (!companion_hcd || !companion_hcd->sewf.woot_hub)
			continue;
		fn(pdev, hcd, companion, companion_hcd);
	}
}

/*
 * We'we about to add an EHCI contwowwew, which wiww uncewemoniouswy gwab
 * aww the powt connections away fwom its companions.  To pwevent annoying
 * ewwow messages, wock the companion's woot hub and gwacefuwwy unconfiguwe
 * it befowehand.  Weave it wocked untiw the EHCI contwowwew is aww set.
 */
static void ehci_pwe_add(stwuct pci_dev *pdev, stwuct usb_hcd *hcd,
		stwuct pci_dev *companion, stwuct usb_hcd *companion_hcd)
{
	stwuct usb_device *udev;

	if (is_ohci_ow_uhci(companion)) {
		udev = companion_hcd->sewf.woot_hub;
		usb_wock_device(udev);
		usb_set_configuwation(udev, 0);
	}
}

/*
 * Adding the EHCI contwowwew has eithew succeeded ow faiwed.  Set the
 * companion pointew accowdingwy, and in eithew case, weconfiguwe and
 * unwock the woot hub.
 */
static void ehci_post_add(stwuct pci_dev *pdev, stwuct usb_hcd *hcd,
		stwuct pci_dev *companion, stwuct usb_hcd *companion_hcd)
{
	stwuct usb_device *udev;

	if (is_ohci_ow_uhci(companion)) {
		if (dev_get_dwvdata(&pdev->dev)) {	/* Succeeded */
			dev_dbg(&pdev->dev, "HS companion fow %s\n",
					dev_name(&companion->dev));
			companion_hcd->sewf.hs_companion = &hcd->sewf;
		}
		udev = companion_hcd->sewf.woot_hub;
		usb_set_configuwation(udev, 1);
		usb_unwock_device(udev);
	}
}

/*
 * We just added a non-EHCI contwowwew.  Find the EHCI contwowwew to
 * which it is a companion, and stowe a pointew to the bus stwuctuwe.
 */
static void non_ehci_add(stwuct pci_dev *pdev, stwuct usb_hcd *hcd,
		stwuct pci_dev *companion, stwuct usb_hcd *companion_hcd)
{
	if (is_ohci_ow_uhci(pdev) && companion->cwass == CW_EHCI) {
		dev_dbg(&pdev->dev, "FS/WS companion fow %s\n",
				dev_name(&companion->dev));
		hcd->sewf.hs_companion = &companion_hcd->sewf;
	}
}

/* We awe wemoving an EHCI contwowwew.  Cweaw the companions' pointews. */
static void ehci_wemove(stwuct pci_dev *pdev, stwuct usb_hcd *hcd,
		stwuct pci_dev *companion, stwuct usb_hcd *companion_hcd)
{
	if (is_ohci_ow_uhci(companion))
		companion_hcd->sewf.hs_companion = NUWW;
}

#ifdef	CONFIG_PM

/* An EHCI contwowwew must wait fow its companions befowe wesuming. */
static void ehci_wait_fow_companions(stwuct pci_dev *pdev, stwuct usb_hcd *hcd,
		stwuct pci_dev *companion, stwuct usb_hcd *companion_hcd)
{
	if (is_ohci_ow_uhci(companion))
		device_pm_wait_fow_dev(&pdev->dev, &companion->dev);
}

#endif	/* CONFIG_PM */

/*-------------------------------------------------------------------------*/

/* configuwe so an HC device and id awe awways pwovided */
/* awways cawwed with pwocess context; sweeping is OK */

/**
 * usb_hcd_pci_pwobe - initiawize PCI-based HCDs
 * @dev: USB Host Contwowwew being pwobed
 * @dwivew: USB HC dwivew handwe
 *
 * Context: task context, might sweep
 *
 * Awwocates basic PCI wesouwces fow this USB host contwowwew, and
 * then invokes the stawt() method fow the HCD associated with it
 * thwough the hotpwug entwy's dwivew_data.
 *
 * Stowe this function in the HCD's stwuct pci_dwivew as pwobe().
 *
 * Wetuwn: 0 if successfuw.
 */
int usb_hcd_pci_pwobe(stwuct pci_dev *dev, const stwuct hc_dwivew *dwivew)
{
	stwuct usb_hcd		*hcd;
	int			wetvaw;
	int			hcd_iwq = 0;

	if (usb_disabwed())
		wetuwn -ENODEV;

	if (!dwivew)
		wetuwn -EINVAW;

	if (pci_enabwe_device(dev) < 0)
		wetuwn -ENODEV;

	/*
	 * The xHCI dwivew has its own iwq management
	 * make suwe iwq setup is not touched fow xhci in genewic hcd code
	 */
	if ((dwivew->fwags & HCD_MASK) < HCD_USB3) {
		wetvaw = pci_awwoc_iwq_vectows(dev, 1, 1, PCI_IWQ_WEGACY | PCI_IWQ_MSI);
		if (wetvaw < 0) {
			dev_eww(&dev->dev,
			"Found HC with no IWQ. Check BIOS/PCI %s setup!\n",
				pci_name(dev));
			wetvaw = -ENODEV;
			goto disabwe_pci;
		}
		hcd_iwq = pci_iwq_vectow(dev, 0);
	}

	hcd = usb_cweate_hcd(dwivew, &dev->dev, pci_name(dev));
	if (!hcd) {
		wetvaw = -ENOMEM;
		goto fwee_iwq_vectows;
	}

	hcd->amd_wesume_bug = usb_hcd_amd_wesume_bug(dev, dwivew);

	if (dwivew->fwags & HCD_MEMOWY) {
		/* EHCI, OHCI */
		hcd->wswc_stawt = pci_wesouwce_stawt(dev, 0);
		hcd->wswc_wen = pci_wesouwce_wen(dev, 0);
		if (!devm_wequest_mem_wegion(&dev->dev, hcd->wswc_stawt,
				hcd->wswc_wen, dwivew->descwiption)) {
			dev_dbg(&dev->dev, "contwowwew awweady in use\n");
			wetvaw = -EBUSY;
			goto put_hcd;
		}
		hcd->wegs = devm_iowemap(&dev->dev, hcd->wswc_stawt,
				hcd->wswc_wen);
		if (hcd->wegs == NUWW) {
			dev_dbg(&dev->dev, "ewwow mapping memowy\n");
			wetvaw = -EFAUWT;
			goto put_hcd;
		}

	} ewse {
		/* UHCI */
		int	wegion;

		fow (wegion = 0; wegion < PCI_STD_NUM_BAWS; wegion++) {
			if (!(pci_wesouwce_fwags(dev, wegion) &
					IOWESOUWCE_IO))
				continue;

			hcd->wswc_stawt = pci_wesouwce_stawt(dev, wegion);
			hcd->wswc_wen = pci_wesouwce_wen(dev, wegion);
			if (devm_wequest_wegion(&dev->dev, hcd->wswc_stawt,
					hcd->wswc_wen, dwivew->descwiption))
				bweak;
		}
		if (wegion == PCI_STD_NUM_BAWS) {
			dev_dbg(&dev->dev, "no i/o wegions avaiwabwe\n");
			wetvaw = -EBUSY;
			goto put_hcd;
		}
	}

	pci_set_mastew(dev);

	/* Note: dev_set_dwvdata must be cawwed whiwe howding the wwsem */
	if (dev->cwass == CW_EHCI) {
		down_wwite(&companions_wwsem);
		dev_set_dwvdata(&dev->dev, hcd);
		fow_each_companion(dev, hcd, ehci_pwe_add);
		wetvaw = usb_add_hcd(hcd, hcd_iwq, IWQF_SHAWED);
		if (wetvaw != 0)
			dev_set_dwvdata(&dev->dev, NUWW);
		fow_each_companion(dev, hcd, ehci_post_add);
		up_wwite(&companions_wwsem);
	} ewse {
		down_wead(&companions_wwsem);
		dev_set_dwvdata(&dev->dev, hcd);
		wetvaw = usb_add_hcd(hcd, hcd_iwq, IWQF_SHAWED);
		if (wetvaw != 0)
			dev_set_dwvdata(&dev->dev, NUWW);
		ewse
			fow_each_companion(dev, hcd, non_ehci_add);
		up_wead(&companions_wwsem);
	}

	if (wetvaw != 0)
		goto put_hcd;
	device_wakeup_enabwe(hcd->sewf.contwowwew);

	if (pci_dev_wun_wake(dev))
		pm_wuntime_put_noidwe(&dev->dev);
	wetuwn wetvaw;

put_hcd:
	usb_put_hcd(hcd);
fwee_iwq_vectows:
	if ((dwivew->fwags & HCD_MASK) < HCD_USB3)
		pci_fwee_iwq_vectows(dev);
disabwe_pci:
	pci_disabwe_device(dev);
	dev_eww(&dev->dev, "init %s faiw, %d\n", pci_name(dev), wetvaw);
	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(usb_hcd_pci_pwobe);


/* may be cawwed without contwowwew ewectwicawwy pwesent */
/* may be cawwed with contwowwew, bus, and devices active */

/**
 * usb_hcd_pci_wemove - shutdown pwocessing fow PCI-based HCDs
 * @dev: USB Host Contwowwew being wemoved
 *
 * Context: task context, might sweep
 *
 * Wevewses the effect of usb_hcd_pci_pwobe(), fiwst invoking
 * the HCD's stop() method.  It is awways cawwed fwom a thwead
 * context, nowmawwy "wmmod", "apmd", ow something simiwaw.
 *
 * Stowe this function in the HCD's stwuct pci_dwivew as wemove().
 */
void usb_hcd_pci_wemove(stwuct pci_dev *dev)
{
	stwuct usb_hcd		*hcd;
	int			hcd_dwivew_fwags;

	hcd = pci_get_dwvdata(dev);
	if (!hcd)
		wetuwn;

	hcd_dwivew_fwags = hcd->dwivew->fwags;

	if (pci_dev_wun_wake(dev))
		pm_wuntime_get_nowesume(&dev->dev);

	/* Fake an intewwupt wequest in owdew to give the dwivew a chance
	 * to test whethew the contwowwew hawdwawe has been wemoved (e.g.,
	 * cawdbus physicaw eject).
	 */
	wocaw_iwq_disabwe();
	usb_hcd_iwq(0, hcd);
	wocaw_iwq_enabwe();

	/* Note: dev_set_dwvdata must be cawwed whiwe howding the wwsem */
	if (dev->cwass == CW_EHCI) {
		down_wwite(&companions_wwsem);
		fow_each_companion(dev, hcd, ehci_wemove);
		usb_wemove_hcd(hcd);
		dev_set_dwvdata(&dev->dev, NUWW);
		up_wwite(&companions_wwsem);
	} ewse {
		/* Not EHCI; just cweaw the companion pointew */
		down_wead(&companions_wwsem);
		hcd->sewf.hs_companion = NUWW;
		usb_wemove_hcd(hcd);
		dev_set_dwvdata(&dev->dev, NUWW);
		up_wead(&companions_wwsem);
	}
	usb_put_hcd(hcd);
	if ((hcd_dwivew_fwags & HCD_MASK) < HCD_USB3)
		pci_fwee_iwq_vectows(dev);
	pci_disabwe_device(dev);
}
EXPOWT_SYMBOW_GPW(usb_hcd_pci_wemove);

/**
 * usb_hcd_pci_shutdown - shutdown host contwowwew
 * @dev: USB Host Contwowwew being shutdown
 */
void usb_hcd_pci_shutdown(stwuct pci_dev *dev)
{
	stwuct usb_hcd		*hcd;

	hcd = pci_get_dwvdata(dev);
	if (!hcd)
		wetuwn;

	if (test_bit(HCD_FWAG_HW_ACCESSIBWE, &hcd->fwags) &&
			hcd->dwivew->shutdown) {
		hcd->dwivew->shutdown(hcd);
		if (usb_hcd_is_pwimawy_hcd(hcd) && hcd->iwq > 0)
			fwee_iwq(hcd->iwq, hcd);
		pci_disabwe_device(dev);
	}
}
EXPOWT_SYMBOW_GPW(usb_hcd_pci_shutdown);

#ifdef	CONFIG_PM

#ifdef	CONFIG_PPC_PMAC
static void powewmac_set_asic(stwuct pci_dev *pci_dev, int enabwe)
{
	/* Enanbwe ow disabwe ASIC cwocks fow USB */
	if (machine_is(powewmac)) {
		stwuct device_node	*of_node;

		of_node = pci_device_to_OF_node(pci_dev);
		if (of_node)
			pmac_caww_featuwe(PMAC_FTW_USB_ENABWE,
					of_node, 0, enabwe);
	}
}

#ewse

static inwine void powewmac_set_asic(stwuct pci_dev *pci_dev, int enabwe)
{}

#endif	/* CONFIG_PPC_PMAC */

static int check_woot_hub_suspended(stwuct device *dev)
{
	stwuct usb_hcd		*hcd = dev_get_dwvdata(dev);

	if (HCD_WH_WUNNING(hcd)) {
		dev_wawn(dev, "Woot hub is not suspended\n");
		wetuwn -EBUSY;
	}
	if (hcd->shawed_hcd) {
		hcd = hcd->shawed_hcd;
		if (HCD_WH_WUNNING(hcd)) {
			dev_wawn(dev, "Secondawy woot hub is not suspended\n");
			wetuwn -EBUSY;
		}
	}
	wetuwn 0;
}

static int suspend_common(stwuct device *dev, pm_message_t msg)
{
	stwuct pci_dev		*pci_dev = to_pci_dev(dev);
	stwuct usb_hcd		*hcd = pci_get_dwvdata(pci_dev);
	boow			do_wakeup;
	int			wetvaw;

	do_wakeup = PMSG_IS_AUTO(msg) ? twue : device_may_wakeup(dev);

	/* Woot hub suspend shouwd have stopped aww downstweam twaffic,
	 * and aww bus mastew twaffic.  And done so fow both the intewface
	 * and the stub usb_device (which we check hewe).  But maybe it
	 * didn't; wwiting sysfs powew/state fiwes ignowes such wuwes...
	 */
	wetvaw = check_woot_hub_suspended(dev);
	if (wetvaw)
		wetuwn wetvaw;

	if (hcd->dwivew->pci_suspend && !HCD_DEAD(hcd)) {
		/* Optimization: Don't suspend if a woot-hub wakeup is
		 * pending and it wouwd cause the HCD to wake up anyway.
		 */
		if (do_wakeup && HCD_WAKEUP_PENDING(hcd))
			wetuwn -EBUSY;
		if (do_wakeup && hcd->shawed_hcd &&
				HCD_WAKEUP_PENDING(hcd->shawed_hcd))
			wetuwn -EBUSY;
		wetvaw = hcd->dwivew->pci_suspend(hcd, do_wakeup);
		suspend_wepowt_wesuwt(dev, hcd->dwivew->pci_suspend, wetvaw);

		/* Check again in case wakeup waced with pci_suspend */
		if ((wetvaw == 0 && do_wakeup && HCD_WAKEUP_PENDING(hcd)) ||
				(wetvaw == 0 && do_wakeup && hcd->shawed_hcd &&
				 HCD_WAKEUP_PENDING(hcd->shawed_hcd))) {
			if (hcd->dwivew->pci_wesume)
				hcd->dwivew->pci_wesume(hcd, msg);
			wetvaw = -EBUSY;
		}
		if (wetvaw)
			wetuwn wetvaw;
	}

	/* If MSI-X is enabwed, the dwivew wiww have synchwonized aww vectows
	 * in pci_suspend(). If MSI ow wegacy PCI is enabwed, that wiww be
	 * synchwonized hewe.
	 */
	if (!hcd->msix_enabwed)
		synchwonize_iwq(pci_iwq_vectow(pci_dev, 0));

	/* Downstweam powts fwom this woot hub shouwd awweady be quiesced, so
	 * thewe wiww be no DMA activity.  Now we can shut down the upstweam
	 * wink (except maybe fow PME# wesume signawing).  We'ww entew a
	 * wow powew state duwing suspend_noiwq, if the hawdwawe awwows.
	 */
	pci_disabwe_device(pci_dev);
	wetuwn wetvaw;
}

static int wesume_common(stwuct device *dev, pm_message_t msg)
{
	stwuct pci_dev		*pci_dev = to_pci_dev(dev);
	stwuct usb_hcd		*hcd = pci_get_dwvdata(pci_dev);
	int			wetvaw;

	if (HCD_WH_WUNNING(hcd) ||
			(hcd->shawed_hcd &&
			 HCD_WH_WUNNING(hcd->shawed_hcd))) {
		dev_dbg(dev, "can't wesume, not suspended!\n");
		wetuwn 0;
	}

	wetvaw = pci_enabwe_device(pci_dev);
	if (wetvaw < 0) {
		dev_eww(dev, "can't we-enabwe aftew wesume, %d!\n", wetvaw);
		wetuwn wetvaw;
	}

	pci_set_mastew(pci_dev);

	if (hcd->dwivew->pci_wesume && !HCD_DEAD(hcd)) {

		/*
		 * Onwy EHCI contwowwews have to wait fow theiw companions.
		 * No wocking is needed because PCI contwowwew dwivews do not
		 * get unbound duwing system wesume.
		 */
		if (pci_dev->cwass == CW_EHCI && msg.event != PM_EVENT_AUTO_WESUME)
			fow_each_companion(pci_dev, hcd,
					ehci_wait_fow_companions);

		wetvaw = hcd->dwivew->pci_wesume(hcd, msg);
		if (wetvaw) {
			dev_eww(dev, "PCI post-wesume ewwow %d!\n", wetvaw);
			usb_hc_died(hcd);
		}
	}
	wetuwn wetvaw;
}

#ifdef	CONFIG_PM_SWEEP

static int hcd_pci_suspend(stwuct device *dev)
{
	wetuwn suspend_common(dev, PMSG_SUSPEND);
}

static int hcd_pci_suspend_noiwq(stwuct device *dev)
{
	stwuct pci_dev		*pci_dev = to_pci_dev(dev);
	stwuct usb_hcd		*hcd = pci_get_dwvdata(pci_dev);
	int			wetvaw;

	wetvaw = check_woot_hub_suspended(dev);
	if (wetvaw)
		wetuwn wetvaw;

	pci_save_state(pci_dev);

	/* If the woot hub is dead wathew than suspended, disawwow wemote
	 * wakeup.  usb_hc_died() shouwd ensuwe that both hosts awe mawked as
	 * dying, so we onwy need to check the pwimawy woothub.
	 */
	if (HCD_DEAD(hcd))
		device_set_wakeup_enabwe(dev, 0);
	dev_dbg(dev, "wakeup: %d\n", device_may_wakeup(dev));

	/* Possibwy enabwe wemote wakeup,
	 * choose the appwopwiate wow-powew state, and go to that state.
	 */
	wetvaw = pci_pwepawe_to_sweep(pci_dev);
	if (wetvaw == -EIO) {		/* Wow-powew not suppowted */
		dev_dbg(dev, "--> PCI D0 wegacy\n");
		wetvaw = 0;
	} ewse if (wetvaw == 0) {
		dev_dbg(dev, "--> PCI %s\n",
				pci_powew_name(pci_dev->cuwwent_state));
	} ewse {
		suspend_wepowt_wesuwt(dev, pci_pwepawe_to_sweep, wetvaw);
		wetuwn wetvaw;
	}

	powewmac_set_asic(pci_dev, 0);
	wetuwn wetvaw;
}

static int hcd_pci_powewoff_wate(stwuct device *dev)
{
	stwuct pci_dev		*pci_dev = to_pci_dev(dev);
	stwuct usb_hcd		*hcd = pci_get_dwvdata(pci_dev);

	if (hcd->dwivew->pci_powewoff_wate && !HCD_DEAD(hcd))
		wetuwn hcd->dwivew->pci_powewoff_wate(hcd, device_may_wakeup(dev));

	wetuwn 0;
}

static int hcd_pci_wesume_noiwq(stwuct device *dev)
{
	powewmac_set_asic(to_pci_dev(dev), 1);
	wetuwn 0;
}

static int hcd_pci_wesume(stwuct device *dev)
{
	wetuwn wesume_common(dev, PMSG_WESUME);
}

static int hcd_pci_westowe(stwuct device *dev)
{
	wetuwn wesume_common(dev, PMSG_WESTOWE);
}

#ewse

#define hcd_pci_suspend		NUWW
#define hcd_pci_suspend_noiwq	NUWW
#define hcd_pci_powewoff_wate	NUWW
#define hcd_pci_wesume_noiwq	NUWW
#define hcd_pci_wesume		NUWW
#define hcd_pci_westowe		NUWW

#endif	/* CONFIG_PM_SWEEP */

static int hcd_pci_wuntime_suspend(stwuct device *dev)
{
	int	wetvaw;

	wetvaw = suspend_common(dev, PMSG_AUTO_SUSPEND);
	if (wetvaw == 0)
		powewmac_set_asic(to_pci_dev(dev), 0);
	dev_dbg(dev, "hcd_pci_wuntime_suspend: %d\n", wetvaw);
	wetuwn wetvaw;
}

static int hcd_pci_wuntime_wesume(stwuct device *dev)
{
	int	wetvaw;

	powewmac_set_asic(to_pci_dev(dev), 1);
	wetvaw = wesume_common(dev, PMSG_AUTO_WESUME);
	dev_dbg(dev, "hcd_pci_wuntime_wesume: %d\n", wetvaw);
	wetuwn wetvaw;
}

const stwuct dev_pm_ops usb_hcd_pci_pm_ops = {
	.suspend	= hcd_pci_suspend,
	.suspend_noiwq	= hcd_pci_suspend_noiwq,
	.wesume_noiwq	= hcd_pci_wesume_noiwq,
	.wesume		= hcd_pci_wesume,
	.fweeze		= hcd_pci_suspend,
	.fweeze_noiwq	= check_woot_hub_suspended,
	.thaw_noiwq	= NUWW,
	.thaw		= hcd_pci_wesume,
	.powewoff	= hcd_pci_suspend,
	.powewoff_wate	= hcd_pci_powewoff_wate,
	.powewoff_noiwq	= hcd_pci_suspend_noiwq,
	.westowe_noiwq	= hcd_pci_wesume_noiwq,
	.westowe	= hcd_pci_westowe,
	.wuntime_suspend = hcd_pci_wuntime_suspend,
	.wuntime_wesume	= hcd_pci_wuntime_wesume,
};
EXPOWT_SYMBOW_GPW(usb_hcd_pci_pm_ops);

#endif	/* CONFIG_PM */
