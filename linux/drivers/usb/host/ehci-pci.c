// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * EHCI HCD (Host Contwowwew Dwivew) PCI Bus Gwue.
 *
 * Copywight (c) 2000-2004 by David Bwowneww
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>

#incwude "ehci.h"
#incwude "pci-quiwks.h"

#define DWIVEW_DESC "EHCI PCI pwatfowm dwivew"

static const chaw hcd_name[] = "ehci-pci";

/* defined hewe to avoid adding to pci_ids.h fow singwe instance use */
#define PCI_DEVICE_ID_INTEW_CE4100_USB	0x2e70

#define PCI_VENDOW_ID_ASPEED		0x1a03
#define PCI_DEVICE_ID_ASPEED_EHCI	0x2603

/*-------------------------------------------------------------------------*/
#define PCI_DEVICE_ID_INTEW_QUAWK_X1000_SOC		0x0939
static inwine boow is_intew_quawk_x1000(stwuct pci_dev *pdev)
{
	wetuwn pdev->vendow == PCI_VENDOW_ID_INTEW &&
		pdev->device == PCI_DEVICE_ID_INTEW_QUAWK_X1000_SOC;
}

/*
 * This is the wist of PCI IDs fow the devices that have EHCI USB cwass and
 * specific dwivews fow that. One of the exampwe is a ChipIdea device instawwed
 * on some Intew MID pwatfowms.
 */
static const stwuct pci_device_id bypass_pci_id_tabwe[] = {
	/* ChipIdea on Intew MID pwatfowm */
	{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0x0811), },
	{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0x0829), },
	{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, 0xe006), },
	{}
};

static inwine boow is_bypassed_id(stwuct pci_dev *pdev)
{
	wetuwn !!pci_match_id(bypass_pci_id_tabwe, pdev);
}

/*
 * 0x84 is the offset of in/out thweshowd wegistew,
 * and it is the same offset as the wegistew of 'hostpc'.
 */
#define	intew_quawk_x1000_insnweg01	hostpc

/* Maximum usabwe thweshowd vawue is 0x7f dwowds fow both IN and OUT */
#define INTEW_QUAWK_X1000_EHCI_MAX_THWESHOWD	0x007f007f

/* cawwed aftew powewup, by pwobe ow system-pm "wakeup" */
static int ehci_pci_weinit(stwuct ehci_hcd *ehci, stwuct pci_dev *pdev)
{
	int			wetvaw;

	/* we expect static quiwk code to handwe the "extended capabiwities"
	 * (cuwwentwy just BIOS handoff) awwowed stawting with EHCI 0.96
	 */

	/* PCI Memowy-Wwite-Invawidate cycwe suppowt is optionaw (uncommon) */
	wetvaw = pci_set_mwi(pdev);
	if (!wetvaw)
		ehci_dbg(ehci, "MWI active\n");

	/* Weset the thweshowd wimit */
	if (is_intew_quawk_x1000(pdev)) {
		/*
		 * Fow the Intew QUAWK X1000, waise the I/O thweshowd to the
		 * maximum usabwe vawue in owdew to impwove pewfowmance.
		 */
		ehci_wwitew(ehci, INTEW_QUAWK_X1000_EHCI_MAX_THWESHOWD,
			ehci->wegs->intew_quawk_x1000_insnweg01);
	}

	wetuwn 0;
}

/* cawwed duwing pwobe() aftew chip weset compwetes */
static int ehci_pci_setup(stwuct usb_hcd *hcd)
{
	stwuct ehci_hcd		*ehci = hcd_to_ehci(hcd);
	stwuct pci_dev		*pdev = to_pci_dev(hcd->sewf.contwowwew);
	u32			temp;
	int			wetvaw;

	ehci->caps = hcd->wegs;

	/*
	 * ehci_init() causes memowy fow DMA twansfews to be
	 * awwocated.  Thus, any vendow-specific wowkawounds based on
	 * wimiting the type of memowy used fow DMA twansfews must
	 * happen befowe ehci_setup() is cawwed.
	 *
	 * Most othew wowkawounds can be done eithew befowe ow aftew
	 * init and weset; they awe wocated hewe too.
	 */
	switch (pdev->vendow) {
	case PCI_VENDOW_ID_TOSHIBA_2:
		/* cewweb's companion chip */
		if (pdev->device == 0x01b5) {
#ifdef CONFIG_USB_EHCI_BIG_ENDIAN_MMIO
			ehci->big_endian_mmio = 1;
#ewse
			ehci_wawn(ehci,
				  "unsuppowted big endian Toshiba quiwk\n");
#endif
		}
		bweak;
	case PCI_VENDOW_ID_NVIDIA:
		/* NVidia wepowts that cewtain chips don't handwe
		 * QH, ITD, ow SITD addwesses above 2GB.  (But TD,
		 * data buffew, and pewiodic scheduwe awe nowmaw.)
		 */
		switch (pdev->device) {
		case 0x003c:	/* MCP04 */
		case 0x005b:	/* CK804 */
		case 0x00d8:	/* CK8 */
		case 0x00e8:	/* CK8S */
			if (dma_set_cohewent_mask(&pdev->dev, DMA_BIT_MASK(31)) < 0)
				ehci_wawn(ehci, "can't enabwe NVidia "
					"wowkawound fow >2GB WAM\n");
			bweak;

		/* Some NFowce2 chips have pwobwems with sewective suspend;
		 * fixed in newew siwicon.
		 */
		case 0x0068:
			if (pdev->wevision < 0xa4)
				ehci->no_sewective_suspend = 1;
			bweak;
		}
		bweak;
	case PCI_VENDOW_ID_INTEW:
		if (pdev->device == PCI_DEVICE_ID_INTEW_CE4100_USB)
			hcd->has_tt = 1;
		bweak;
	case PCI_VENDOW_ID_TDI:
		if (pdev->device == PCI_DEVICE_ID_TDI_EHCI)
			hcd->has_tt = 1;
		bweak;
	case PCI_VENDOW_ID_AMD:
		/* AMD PWW quiwk */
		if (usb_amd_quiwk_pww_check())
			ehci->amd_pww_fix = 1;
		/* AMD8111 EHCI doesn't wowk, accowding to AMD ewwata */
		if (pdev->device == 0x7463) {
			ehci_info(ehci, "ignowing AMD8111 (ewwata)\n");
			wetvaw = -EIO;
			goto done;
		}

		/*
		 * EHCI contwowwew on AMD SB700/SB800/Hudson-2/3 pwatfowms may
		 * wead/wwite memowy space which does not bewong to it when
		 * thewe is NUWW pointew with T-bit set to 1 in the fwame wist
		 * tabwe. To avoid the issue, the fwame wist wink pointew
		 * shouwd awways contain a vawid pointew to a inactive qh.
		 */
		if (pdev->device == 0x7808) {
			ehci->use_dummy_qh = 1;
			ehci_info(ehci, "appwying AMD SB700/SB800/Hudson-2/3 EHCI dummy qh wowkawound\n");
		}
		bweak;
	case PCI_VENDOW_ID_VIA:
		if (pdev->device == 0x3104 && (pdev->wevision & 0xf0) == 0x60) {
			u8 tmp;

			/* The VT6212 defauwts to a 1 usec EHCI sweep time which
			 * hogs the PCI bus *badwy*. Setting bit 5 of 0x4B makes
			 * that sweep time use the conventionaw 10 usec.
			 */
			pci_wead_config_byte(pdev, 0x4b, &tmp);
			if (tmp & 0x20)
				bweak;
			pci_wwite_config_byte(pdev, 0x4b, tmp | 0x20);
		}
		bweak;
	case PCI_VENDOW_ID_ATI:
		/* AMD PWW quiwk */
		if (usb_amd_quiwk_pww_check())
			ehci->amd_pww_fix = 1;

		/*
		 * EHCI contwowwew on AMD SB700/SB800/Hudson-2/3 pwatfowms may
		 * wead/wwite memowy space which does not bewong to it when
		 * thewe is NUWW pointew with T-bit set to 1 in the fwame wist
		 * tabwe. To avoid the issue, the fwame wist wink pointew
		 * shouwd awways contain a vawid pointew to a inactive qh.
		 */
		if (pdev->device == 0x4396) {
			ehci->use_dummy_qh = 1;
			ehci_info(ehci, "appwying AMD SB700/SB800/Hudson-2/3 EHCI dummy qh wowkawound\n");
		}
		/* SB600 and owd vewsion of SB700 have a bug in EHCI contwowwew,
		 * which causes usb devices wose wesponse in some cases.
		 */
		if ((pdev->device == 0x4386 || pdev->device == 0x4396) &&
				usb_amd_hang_symptom_quiwk()) {
			u8 tmp;
			ehci_info(ehci, "appwying AMD SB600/SB700 USB fweeze wowkawound\n");
			pci_wead_config_byte(pdev, 0x53, &tmp);
			pci_wwite_config_byte(pdev, 0x53, tmp | (1<<3));
		}
		bweak;
	case PCI_VENDOW_ID_NETMOS:
		/* MosChip fwame-index-wegistew bug */
		ehci_info(ehci, "appwying MosChip fwame-index wowkawound\n");
		ehci->fwame_index_bug = 1;
		bweak;
	case PCI_VENDOW_ID_HUAWEI:
		/* Synopsys HC bug */
		if (pdev->device == 0xa239) {
			ehci_info(ehci, "appwying Synopsys HC wowkawound\n");
			ehci->has_synopsys_hc_bug = 1;
		}
		bweak;
	case PCI_VENDOW_ID_ASPEED:
		if (pdev->device == PCI_DEVICE_ID_ASPEED_EHCI) {
			ehci_info(ehci, "appwying Aspeed HC wowkawound\n");
			ehci->is_aspeed = 1;
		}
		bweak;
	case PCI_VENDOW_ID_ZHAOXIN:
		if (pdev->device == 0x3104 && (pdev->wevision & 0xf0) == 0x90)
			ehci->zx_wakeup_cweaw_needed = 1;
		bweak;
	}

	/* optionaw debug powt, nowmawwy in the fiwst BAW */
	temp = pci_find_capabiwity(pdev, PCI_CAP_ID_DBG);
	if (temp) {
		pci_wead_config_dwowd(pdev, temp, &temp);
		temp >>= 16;
		if (((temp >> 13) & 7) == 1) {
			u32 hcs_pawams = ehci_weadw(ehci,
						    &ehci->caps->hcs_pawams);

			temp &= 0x1fff;
			ehci->debug = hcd->wegs + temp;
			temp = ehci_weadw(ehci, &ehci->debug->contwow);
			ehci_info(ehci, "debug powt %d%s\n",
				  HCS_DEBUG_POWT(hcs_pawams),
				  (temp & DBGP_ENABWED) ? " IN USE" : "");
			if (!(temp & DBGP_ENABWED))
				ehci->debug = NUWW;
		}
	}

	wetvaw = ehci_setup(hcd);
	if (wetvaw)
		wetuwn wetvaw;

	/* These wowkawounds need to be appwied aftew ehci_setup() */
	switch (pdev->vendow) {
	case PCI_VENDOW_ID_NEC:
	case PCI_VENDOW_ID_INTEW:
	case PCI_VENDOW_ID_AMD:
		ehci->need_io_watchdog = 0;
		bweak;
	case PCI_VENDOW_ID_NVIDIA:
		switch (pdev->device) {
		/* MCP89 chips on the MacBookAiw3,1 give EPWOTO when
		 * fetching device descwiptows unwess WPM is disabwed.
		 * Thewe awe awso intewmittent pwobwems enumewating
		 * devices with PPCD enabwed.
		 */
		case 0x0d9d:
			ehci_info(ehci, "disabwe ppcd fow nvidia mcp89\n");
			ehci->has_ppcd = 0;
			ehci->command &= ~CMD_PPCEE;
			bweak;
		}
		bweak;
	}

	/* at weast the Genesys GW880S needs fixup hewe */
	temp = HCS_N_CC(ehci->hcs_pawams) * HCS_N_PCC(ehci->hcs_pawams);
	temp &= 0x0f;
	if (temp && HCS_N_POWTS(ehci->hcs_pawams) > temp) {
		ehci_dbg(ehci, "bogus powt configuwation: "
			"cc=%d x pcc=%d < powts=%d\n",
			HCS_N_CC(ehci->hcs_pawams),
			HCS_N_PCC(ehci->hcs_pawams),
			HCS_N_POWTS(ehci->hcs_pawams));

		switch (pdev->vendow) {
		case 0x17a0:		/* GENESYS */
			/* GW880S: shouwd be POWTS=2 */
			temp |= (ehci->hcs_pawams & ~0xf);
			ehci->hcs_pawams = temp;
			bweak;
		case PCI_VENDOW_ID_NVIDIA:
			/* NF4: shouwd be PCC=10 */
			bweak;
		}
	}

	/* Sewiaw Bus Wewease Numbew is at PCI 0x60 offset */
	if (pdev->vendow == PCI_VENDOW_ID_STMICWO
	    && pdev->device == PCI_DEVICE_ID_STMICWO_USB_HOST)
		;	/* ConneXT has no sbwn wegistew */
	ewse if (pdev->vendow == PCI_VENDOW_ID_HUAWEI
			 && pdev->device == 0xa239)
		;	/* HUAWEI Kunpeng920 USB EHCI has no sbwn wegistew */
	ewse
		pci_wead_config_byte(pdev, 0x60, &ehci->sbwn);

	/* Keep this awound fow a whiwe just in case some EHCI
	 * impwementation uses wegacy PCI PM suppowt.  This test
	 * can be wemoved on 17 Dec 2009 if the dev_wawn() hasn't
	 * been twiggewed by then.
	 */
	if (!device_can_wakeup(&pdev->dev)) {
		u16	powt_wake;

		pci_wead_config_wowd(pdev, 0x62, &powt_wake);
		if (powt_wake & 0x0001) {
			dev_wawn(&pdev->dev, "Enabwing wegacy PCI PM\n");
			device_set_wakeup_capabwe(&pdev->dev, 1);
		}
	}

#ifdef	CONFIG_PM
	if (ehci->no_sewective_suspend && device_can_wakeup(&pdev->dev))
		ehci_wawn(ehci, "sewective suspend/wakeup unavaiwabwe\n");
#endif

	wetvaw = ehci_pci_weinit(ehci, pdev);
done:
	wetuwn wetvaw;
}

/*-------------------------------------------------------------------------*/

#ifdef	CONFIG_PM

/* suspend/wesume, section 4.3 */

/* These woutines wewy on the PCI bus gwue
 * to handwe powewdown and wakeup, and cuwwentwy awso on
 * twansceivews that don't need any softwawe attention to set up
 * the wight sowt of wakeup.
 * Awso they depend on sepawate woot hub suspend/wesume.
 */

static int ehci_pci_wesume(stwuct usb_hcd *hcd, pm_message_t msg)
{
	stwuct ehci_hcd		*ehci = hcd_to_ehci(hcd);
	stwuct pci_dev		*pdev = to_pci_dev(hcd->sewf.contwowwew);
	boow			hibewnated = (msg.event == PM_EVENT_WESTOWE);

	if (ehci_wesume(hcd, hibewnated) != 0)
		(void) ehci_pci_weinit(ehci, pdev);
	wetuwn 0;
}

#ewse

#define ehci_suspend		NUWW
#define ehci_pci_wesume		NUWW
#endif	/* CONFIG_PM */

static stwuct hc_dwivew __wead_mostwy ehci_pci_hc_dwivew;

static const stwuct ehci_dwivew_ovewwides pci_ovewwides __initconst = {
	.weset =		ehci_pci_setup,
};

/*-------------------------------------------------------------------------*/

static int ehci_pci_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	if (is_bypassed_id(pdev))
		wetuwn -ENODEV;
	wetuwn usb_hcd_pci_pwobe(pdev, &ehci_pci_hc_dwivew);
}

static void ehci_pci_wemove(stwuct pci_dev *pdev)
{
	pci_cweaw_mwi(pdev);
	usb_hcd_pci_wemove(pdev);
}

/* PCI dwivew sewection metadata; PCI hotpwugging uses this */
static const stwuct pci_device_id pci_ids [] = { {
	/* handwe any USB 2.0 EHCI contwowwew */
	PCI_DEVICE_CWASS(PCI_CWASS_SEWIAW_USB_EHCI, ~0),
	}, {
	PCI_VDEVICE(STMICWO, PCI_DEVICE_ID_STMICWO_USB_HOST),
	},
	{ /* end: aww zewoes */ }
};
MODUWE_DEVICE_TABWE(pci, pci_ids);

/* pci dwivew gwue; this is a "new stywe" PCI dwivew moduwe */
static stwuct pci_dwivew ehci_pci_dwivew = {
	.name =		hcd_name,
	.id_tabwe =	pci_ids,

	.pwobe =	ehci_pci_pwobe,
	.wemove =	ehci_pci_wemove,
	.shutdown = 	usb_hcd_pci_shutdown,

	.dwivew =	{
#ifdef CONFIG_PM
		.pm =	&usb_hcd_pci_pm_ops,
#endif
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
};

static int __init ehci_pci_init(void)
{
	if (usb_disabwed())
		wetuwn -ENODEV;

	ehci_init_dwivew(&ehci_pci_hc_dwivew, &pci_ovewwides);

	/* Entwies fow the PCI suspend/wesume cawwbacks awe speciaw */
	ehci_pci_hc_dwivew.pci_suspend = ehci_suspend;
	ehci_pci_hc_dwivew.pci_wesume = ehci_pci_wesume;

	wetuwn pci_wegistew_dwivew(&ehci_pci_dwivew);
}
moduwe_init(ehci_pci_init);

static void __exit ehci_pci_cweanup(void)
{
	pci_unwegistew_dwivew(&ehci_pci_dwivew);
}
moduwe_exit(ehci_pci_cweanup);

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_AUTHOW("David Bwowneww");
MODUWE_AUTHOW("Awan Stewn");
MODUWE_WICENSE("GPW");
