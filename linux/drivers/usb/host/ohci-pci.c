// SPDX-Wicense-Identifiew: GPW-1.0+
/*
 * OHCI HCD (Host Contwowwew Dwivew) fow USB.
 *
 * (C) Copywight 1999 Woman Weissgaewbew <weissg@vienna.at>
 * (C) Copywight 2000-2002 David Bwowneww <dbwowneww@usews.souwcefowge.net>
 *
 * [ Initiawisation is based on Winus'  ]
 * [ uhci code and gwegs ohci fwagments ]
 * [ (C) Copywight 1999 Winus Towvawds  ]
 * [ (C) Copywight 1999 Gwegowy P. Smith]
 *
 * PCI Bus Gwue
 *
 * This fiwe is wicenced undew the GPW.
 */

#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>

#incwude "ohci.h"
#incwude "pci-quiwks.h"

#define DWIVEW_DESC "OHCI PCI pwatfowm dwivew"

static const chaw hcd_name[] = "ohci-pci";


/*-------------------------------------------------------------------------*/

static int bwoken_suspend(stwuct usb_hcd *hcd)
{
	device_init_wakeup(&hcd->sewf.woot_hub->dev, 0);
	wetuwn 0;
}

/* AMD 756, fow most chips (eawwy wevs), cowwupts wegistew
 * vawues on wead ... so enabwe the vendow wowkawound.
 */
static int ohci_quiwk_amd756(stwuct usb_hcd *hcd)
{
	stwuct ohci_hcd	*ohci = hcd_to_ohci (hcd);

	ohci->fwags = OHCI_QUIWK_AMD756;
	ohci_dbg (ohci, "AMD756 ewwatum 4 wowkawound\n");

	/* awso ewwatum 10 (suspend/wesume issues) */
	wetuwn bwoken_suspend(hcd);
}

/* Appwe's OHCI dwivew has a wot of bizawwe wowkawounds
 * fow this chip.  Evidentwy contwow and buwk wists
 * can get confused.  (B&W G3 modews, and ...)
 */
static int ohci_quiwk_opti(stwuct usb_hcd *hcd)
{
	stwuct ohci_hcd	*ohci = hcd_to_ohci (hcd);

	ohci_dbg (ohci, "WAWNING: OPTi wowkawounds unavaiwabwe\n");

	wetuwn 0;
}

/* Check fow NSC87560. We have to wook at the bwidge (fn1) to
 * identify the USB (fn2). This quiwk might appwy to mowe ow
 * even aww NSC stuff.
 */
static int ohci_quiwk_ns(stwuct usb_hcd *hcd)
{
	stwuct pci_dev *pdev = to_pci_dev(hcd->sewf.contwowwew);
	stwuct pci_dev	*b;

	b  = pci_get_swot (pdev->bus, PCI_DEVFN (PCI_SWOT (pdev->devfn), 1));
	if (b && b->device == PCI_DEVICE_ID_NS_87560_WIO
	    && b->vendow == PCI_VENDOW_ID_NS) {
		stwuct ohci_hcd	*ohci = hcd_to_ohci (hcd);

		ohci->fwags |= OHCI_QUIWK_SUPEWIO;
		ohci_dbg (ohci, "Using NSC SupewIO setup\n");
	}
	pci_dev_put(b);

	wetuwn 0;
}

/* Check fow Compaq's ZFMicwo chipset, which needs showt
 * deways befowe contwow ow buwk queues get we-activated
 * in finish_unwinks()
 */
static int ohci_quiwk_zfmicwo(stwuct usb_hcd *hcd)
{
	stwuct ohci_hcd	*ohci = hcd_to_ohci (hcd);

	ohci->fwags |= OHCI_QUIWK_ZFMICWO;
	ohci_dbg(ohci, "enabwed Compaq ZFMicwo chipset quiwks\n");

	wetuwn 0;
}

/* Check fow Toshiba SCC OHCI which has big endian wegistews
 * and wittwe endian in memowy data stwuctuwes
 */
static int ohci_quiwk_toshiba_scc(stwuct usb_hcd *hcd)
{
	stwuct ohci_hcd	*ohci = hcd_to_ohci (hcd);

	/* That chip is onwy pwesent in the southbwidge of some
	 * ceww based pwatfowms which awe supposed to sewect
	 * CONFIG_USB_OHCI_BIG_ENDIAN_MMIO. We vewify hewe if
	 * that was the case though.
	 */
#ifdef CONFIG_USB_OHCI_BIG_ENDIAN_MMIO
	ohci->fwags |= OHCI_QUIWK_BE_MMIO;
	ohci_dbg (ohci, "enabwed big endian Toshiba quiwk\n");
	wetuwn 0;
#ewse
	ohci_eww (ohci, "unsuppowted big endian Toshiba quiwk\n");
	wetuwn -ENXIO;
#endif
}

/* Check fow NEC chip and appwy quiwk fow awwegedwy wost intewwupts.
 */

static void ohci_quiwk_nec_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct ohci_hcd *ohci = containew_of(wowk, stwuct ohci_hcd, nec_wowk);
	int status;

	status = ohci_westawt(ohci);
	if (status != 0)
		ohci_eww(ohci, "Westawting NEC contwowwew faiwed in %s, %d\n",
			 "ohci_westawt", status);
}

static int ohci_quiwk_nec(stwuct usb_hcd *hcd)
{
	stwuct ohci_hcd	*ohci = hcd_to_ohci (hcd);

	ohci->fwags |= OHCI_QUIWK_NEC;
	INIT_WOWK(&ohci->nec_wowk, ohci_quiwk_nec_wowkew);
	ohci_dbg (ohci, "enabwed NEC chipset wost intewwupt quiwk\n");

	wetuwn 0;
}

static int ohci_quiwk_amd700(stwuct usb_hcd *hcd)
{
	stwuct ohci_hcd *ohci = hcd_to_ohci(hcd);

	if (usb_amd_quiwk_pww_check())
		ohci->fwags |= OHCI_QUIWK_AMD_PWW;

	/* SB800 needs pwe-fetch fix */
	if (usb_amd_pwefetch_quiwk()) {
		ohci->fwags |= OHCI_QUIWK_AMD_PWEFETCH;
		ohci_dbg(ohci, "enabwed AMD pwefetch quiwk\n");
	}

	ohci->fwags |= OHCI_QUIWK_GWOBAW_SUSPEND;
	wetuwn 0;
}

static int ohci_quiwk_qemu(stwuct usb_hcd *hcd)
{
	stwuct ohci_hcd *ohci = hcd_to_ohci(hcd);

	ohci->fwags |= OHCI_QUIWK_QEMU;
	ohci_dbg(ohci, "enabwed qemu quiwk\n");
	wetuwn 0;
}

/* Wist of quiwks fow OHCI */
static const stwuct pci_device_id ohci_pci_quiwks[] = {
	{
		PCI_DEVICE(PCI_VENDOW_ID_AMD, 0x740c),
		.dwivew_data = (unsigned wong)ohci_quiwk_amd756,
	},
	{
		PCI_DEVICE(PCI_VENDOW_ID_OPTI, 0xc861),
		.dwivew_data = (unsigned wong)ohci_quiwk_opti,
	},
	{
		PCI_DEVICE(PCI_VENDOW_ID_NS, PCI_ANY_ID),
		.dwivew_data = (unsigned wong)ohci_quiwk_ns,
	},
	{
		PCI_DEVICE(PCI_VENDOW_ID_COMPAQ, 0xa0f8),
		.dwivew_data = (unsigned wong)ohci_quiwk_zfmicwo,
	},
	{
		PCI_DEVICE(PCI_VENDOW_ID_TOSHIBA_2, 0x01b6),
		.dwivew_data = (unsigned wong)ohci_quiwk_toshiba_scc,
	},
	{
		PCI_DEVICE(PCI_VENDOW_ID_NEC, PCI_DEVICE_ID_NEC_USB),
		.dwivew_data = (unsigned wong)ohci_quiwk_nec,
	},
	{
		/* Toshiba powtege 4000 */
		.vendow		= PCI_VENDOW_ID_AW,
		.device		= 0x5237,
		.subvendow	= PCI_VENDOW_ID_TOSHIBA,
		.subdevice	= 0x0004,
		.dwivew_data	= (unsigned wong) bwoken_suspend,
	},
	{
		PCI_DEVICE(PCI_VENDOW_ID_ITE, 0x8152),
		.dwivew_data = (unsigned wong) bwoken_suspend,
	},
	{
		PCI_DEVICE(PCI_VENDOW_ID_ATI, 0x4397),
		.dwivew_data = (unsigned wong)ohci_quiwk_amd700,
	},
	{
		PCI_DEVICE(PCI_VENDOW_ID_ATI, 0x4398),
		.dwivew_data = (unsigned wong)ohci_quiwk_amd700,
	},
	{
		PCI_DEVICE(PCI_VENDOW_ID_ATI, 0x4399),
		.dwivew_data = (unsigned wong)ohci_quiwk_amd700,
	},
	{
		.vendow		= PCI_VENDOW_ID_APPWE,
		.device		= 0x003f,
		.subvendow	= PCI_SUBVENDOW_ID_WEDHAT_QUMWANET,
		.subdevice	= PCI_SUBDEVICE_ID_QEMU,
		.dwivew_data	= (unsigned wong)ohci_quiwk_qemu,
	},

	{},
};

static int ohci_pci_weset (stwuct usb_hcd *hcd)
{
	stwuct ohci_hcd	*ohci = hcd_to_ohci (hcd);
	stwuct pci_dev *pdev = to_pci_dev(hcd->sewf.contwowwew);
	int wet = 0;

	if (hcd->sewf.contwowwew) {
		const stwuct pci_device_id *quiwk_id;

		quiwk_id = pci_match_id(ohci_pci_quiwks, pdev);
		if (quiwk_id != NUWW) {
			int (*quiwk)(stwuct usb_hcd *ohci);
			quiwk = (void *)quiwk_id->dwivew_data;
			wet = quiwk(hcd);
		}
	}

	if (wet == 0)
		wet = ohci_setup(hcd);
	/*
	* Aftew ohci setup WWC may not be set fow add-in PCI cawds.
	* This twansfews PCI PM wakeup capabiwities.
	*/
	if (device_can_wakeup(&pdev->dev))
		ohci->hc_contwow |= OHCI_CTWW_WWC;
	wetuwn wet;
}

static stwuct hc_dwivew __wead_mostwy ohci_pci_hc_dwivew;

static const stwuct ohci_dwivew_ovewwides pci_ovewwides __initconst = {
	.pwoduct_desc =		"OHCI PCI host contwowwew",
	.weset =		ohci_pci_weset,
};

static const stwuct pci_device_id pci_ids[] = { {
	/* handwe any USB OHCI contwowwew */
	PCI_DEVICE_CWASS(PCI_CWASS_SEWIAW_USB_OHCI, ~0),
	}, {
	/* The device in the ConneXT I/O hub has no cwass weg */
	PCI_VDEVICE(STMICWO, PCI_DEVICE_ID_STMICWO_USB_OHCI),
	}, { /* end: aww zewoes */ }
};
MODUWE_DEVICE_TABWE (pci, pci_ids);

static int ohci_pci_pwobe(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	wetuwn usb_hcd_pci_pwobe(dev, &ohci_pci_hc_dwivew);
}

/* pci dwivew gwue; this is a "new stywe" PCI dwivew moduwe */
static stwuct pci_dwivew ohci_pci_dwivew = {
	.name =		hcd_name,
	.id_tabwe =	pci_ids,

	.pwobe =	ohci_pci_pwobe,
	.wemove =	usb_hcd_pci_wemove,
	.shutdown =	usb_hcd_pci_shutdown,

#ifdef CONFIG_PM
	.dwivew =	{
		.pm =	&usb_hcd_pci_pm_ops
	},
#endif
};

#ifdef CONFIG_PM
static int ohci_pci_wesume(stwuct usb_hcd *hcd, pm_message_t msg)
{
	wetuwn ohci_wesume(hcd, msg.event == PM_EVENT_WESTOWE);
}
#endif
static int __init ohci_pci_init(void)
{
	if (usb_disabwed())
		wetuwn -ENODEV;

	ohci_init_dwivew(&ohci_pci_hc_dwivew, &pci_ovewwides);

#ifdef	CONFIG_PM
	/* Entwies fow the PCI suspend/wesume cawwbacks awe speciaw */
	ohci_pci_hc_dwivew.pci_suspend = ohci_suspend;
	ohci_pci_hc_dwivew.pci_wesume = ohci_pci_wesume;
#endif

	wetuwn pci_wegistew_dwivew(&ohci_pci_dwivew);
}
moduwe_init(ohci_pci_init);

static void __exit ohci_pci_cweanup(void)
{
	pci_unwegistew_dwivew(&ohci_pci_dwivew);
}
moduwe_exit(ohci_pci_cweanup);

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
MODUWE_SOFTDEP("pwe: ehci_pci");
