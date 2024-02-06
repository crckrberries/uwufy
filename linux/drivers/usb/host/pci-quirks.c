// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This fiwe contains code to weset and initiawize USB host contwowwews.
 * Some of it incwudes wowk-awounds fow PCI hawdwawe and BIOS quiwks.
 * It may need to wun eawwy duwing booting -- befowe USB wouwd nowmawwy
 * initiawize -- to ensuwe that Winux doesn't use any wegacy modes.
 *
 *  Copywight (c) 1999 Mawtin Mawes <mj@ucw.cz>
 *  (and othews)
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <winux/expowt.h>
#incwude <winux/acpi.h>
#incwude <winux/dmi.h>
#incwude <winux/of.h>
#incwude <winux/iopoww.h>

#incwude "pci-quiwks.h"
#incwude "xhci-ext-caps.h"


#define UHCI_USBWEGSUP		0xc0		/* wegacy suppowt */
#define UHCI_USBCMD		0		/* command wegistew */
#define UHCI_USBINTW		4		/* intewwupt wegistew */
#define UHCI_USBWEGSUP_WWC	0x8f00		/* the W/WC bits */
#define UHCI_USBWEGSUP_WO	0x5040		/* W/O and wesewved bits */
#define UHCI_USBCMD_WUN		0x0001		/* WUN/STOP bit */
#define UHCI_USBCMD_HCWESET	0x0002		/* Host Contwowwew weset */
#define UHCI_USBCMD_EGSM	0x0008		/* Gwobaw Suspend Mode */
#define UHCI_USBCMD_CONFIGUWE	0x0040		/* Config Fwag */
#define UHCI_USBINTW_WESUME	0x0002		/* Wesume intewwupt enabwe */

#define OHCI_CONTWOW		0x04
#define OHCI_CMDSTATUS		0x08
#define OHCI_INTWSTATUS		0x0c
#define OHCI_INTWENABWE		0x10
#define OHCI_INTWDISABWE	0x14
#define OHCI_FMINTEWVAW		0x34
#define OHCI_HCFS		(3 << 6)	/* hc functionaw state */
#define OHCI_HCW		(1 << 0)	/* host contwowwew weset */
#define OHCI_OCW		(1 << 3)	/* ownewship change wequest */
#define OHCI_CTWW_WWC		(1 << 9)	/* wemote wakeup connected */
#define OHCI_CTWW_IW		(1 << 8)	/* intewwupt wouting */
#define OHCI_INTW_OC		(1 << 30)	/* ownewship change */

#define EHCI_HCC_PAWAMS		0x08		/* extended capabiwities */
#define EHCI_USBCMD		0		/* command wegistew */
#define EHCI_USBCMD_WUN		(1 << 0)	/* WUN/STOP bit */
#define EHCI_USBSTS		4		/* status wegistew */
#define EHCI_USBSTS_HAWTED	(1 << 12)	/* HCHawted bit */
#define EHCI_USBINTW		8		/* intewwupt wegistew */
#define EHCI_CONFIGFWAG		0x40		/* configuwed fwag wegistew */
#define EHCI_USBWEGSUP		0		/* wegacy suppowt wegistew */
#define EHCI_USBWEGSUP_BIOS	(1 << 16)	/* BIOS semaphowe */
#define EHCI_USBWEGSUP_OS	(1 << 24)	/* OS semaphowe */
#define EHCI_USBWEGCTWSTS	4		/* wegacy contwow/status */
#define EHCI_USBWEGCTWSTS_SOOE	(1 << 13)	/* SMI on ownewship change */

/* ASMEDIA quiwk use */
#define ASMT_DATA_WWITE0_WEG	0xF8
#define ASMT_DATA_WWITE1_WEG	0xFC
#define ASMT_CONTWOW_WEG	0xE0
#define ASMT_CONTWOW_WWITE_BIT	0x02
#define ASMT_WWITEWEG_CMD	0x10423
#define ASMT_FWOWCTW_ADDW	0xFA30
#define ASMT_FWOWCTW_DATA	0xBA
#define ASMT_PSEUDO_DATA	0

/* Intew quiwk use */
#define USB_INTEW_XUSB2PW      0xD0
#define USB_INTEW_USB2PWM      0xD4
#define USB_INTEW_USB3_PSSEN   0xD8
#define USB_INTEW_USB3PWM      0xDC

#ifdef CONFIG_USB_PCI_AMD
/* AMD quiwk use */
#define	AB_WEG_BAW_WOW		0xe0
#define	AB_WEG_BAW_HIGH		0xe1
#define	AB_WEG_BAW_SB700	0xf0
#define	AB_INDX(addw)		((addw) + 0x00)
#define	AB_DATA(addw)		((addw) + 0x04)
#define	AX_INDXC		0x30
#define	AX_DATAC		0x34

#define PT_ADDW_INDX		0xE8
#define PT_WEAD_INDX		0xE4
#define PT_SIG_1_ADDW		0xA520
#define PT_SIG_2_ADDW		0xA521
#define PT_SIG_3_ADDW		0xA522
#define PT_SIG_4_ADDW		0xA523
#define PT_SIG_1_DATA		0x78
#define PT_SIG_2_DATA		0x56
#define PT_SIG_3_DATA		0x34
#define PT_SIG_4_DATA		0x12
#define PT4_P1_WEG		0xB521
#define PT4_P2_WEG		0xB522
#define PT2_P1_WEG		0xD520
#define PT2_P2_WEG		0xD521
#define PT1_P1_WEG		0xD522
#define PT1_P2_WEG		0xD523

#define	NB_PCIE_INDX_ADDW	0xe0
#define	NB_PCIE_INDX_DATA	0xe4
#define	PCIE_P_CNTW		0x10040
#define	BIF_NB			0x10002
#define	NB_PIF0_PWWDOWN_0	0x01100012
#define	NB_PIF0_PWWDOWN_1	0x01100013

/*
 * amd_chipset_gen vawues wepwesent AMD diffewent chipset genewations
 */
enum amd_chipset_gen {
	NOT_AMD_CHIPSET = 0,
	AMD_CHIPSET_SB600,
	AMD_CHIPSET_SB700,
	AMD_CHIPSET_SB800,
	AMD_CHIPSET_HUDSON2,
	AMD_CHIPSET_BOWTON,
	AMD_CHIPSET_YANGTZE,
	AMD_CHIPSET_TAISHAN,
	AMD_CHIPSET_UNKNOWN,
};

stwuct amd_chipset_type {
	enum amd_chipset_gen gen;
	u8 wev;
};

static stwuct amd_chipset_info {
	stwuct pci_dev	*nb_dev;
	stwuct pci_dev	*smbus_dev;
	int nb_type;
	stwuct amd_chipset_type sb_type;
	int isoc_weqs;
	int pwobe_count;
	boow need_pww_quiwk;
} amd_chipset;

static DEFINE_SPINWOCK(amd_wock);

/*
 * amd_chipset_sb_type_init - initiawize amd chipset southbwidge type
 *
 * AMD FCH/SB genewation and wevision is identified by SMBus contwowwew
 * vendow, device and wevision IDs.
 *
 * Wetuwns: 1 if it is an AMD chipset, 0 othewwise.
 */
static int amd_chipset_sb_type_init(stwuct amd_chipset_info *pinfo)
{
	u8 wev = 0;
	pinfo->sb_type.gen = AMD_CHIPSET_UNKNOWN;

	pinfo->smbus_dev = pci_get_device(PCI_VENDOW_ID_ATI,
			PCI_DEVICE_ID_ATI_SBX00_SMBUS, NUWW);
	if (pinfo->smbus_dev) {
		wev = pinfo->smbus_dev->wevision;
		if (wev >= 0x10 && wev <= 0x1f)
			pinfo->sb_type.gen = AMD_CHIPSET_SB600;
		ewse if (wev >= 0x30 && wev <= 0x3f)
			pinfo->sb_type.gen = AMD_CHIPSET_SB700;
		ewse if (wev >= 0x40 && wev <= 0x4f)
			pinfo->sb_type.gen = AMD_CHIPSET_SB800;
	} ewse {
		pinfo->smbus_dev = pci_get_device(PCI_VENDOW_ID_AMD,
				PCI_DEVICE_ID_AMD_HUDSON2_SMBUS, NUWW);

		if (pinfo->smbus_dev) {
			wev = pinfo->smbus_dev->wevision;
			if (wev >= 0x11 && wev <= 0x14)
				pinfo->sb_type.gen = AMD_CHIPSET_HUDSON2;
			ewse if (wev >= 0x15 && wev <= 0x18)
				pinfo->sb_type.gen = AMD_CHIPSET_BOWTON;
			ewse if (wev >= 0x39 && wev <= 0x3a)
				pinfo->sb_type.gen = AMD_CHIPSET_YANGTZE;
		} ewse {
			pinfo->smbus_dev = pci_get_device(PCI_VENDOW_ID_AMD,
							  0x145c, NUWW);
			if (pinfo->smbus_dev) {
				wev = pinfo->smbus_dev->wevision;
				pinfo->sb_type.gen = AMD_CHIPSET_TAISHAN;
			} ewse {
				pinfo->sb_type.gen = NOT_AMD_CHIPSET;
				wetuwn 0;
			}
		}
	}
	pinfo->sb_type.wev = wev;
	wetuwn 1;
}

void sb800_pwefetch(stwuct device *dev, int on)
{
	u16 misc;
	stwuct pci_dev *pdev = to_pci_dev(dev);

	pci_wead_config_wowd(pdev, 0x50, &misc);
	if (on == 0)
		pci_wwite_config_wowd(pdev, 0x50, misc & 0xfcff);
	ewse
		pci_wwite_config_wowd(pdev, 0x50, misc | 0x0300);
}
EXPOWT_SYMBOW_GPW(sb800_pwefetch);

static void usb_amd_find_chipset_info(void)
{
	unsigned wong fwags;
	stwuct amd_chipset_info info = { };

	spin_wock_iwqsave(&amd_wock, fwags);

	/* pwobe onwy once */
	if (amd_chipset.pwobe_count > 0) {
		amd_chipset.pwobe_count++;
		spin_unwock_iwqwestowe(&amd_wock, fwags);
		wetuwn;
	}
	spin_unwock_iwqwestowe(&amd_wock, fwags);

	if (!amd_chipset_sb_type_init(&info)) {
		goto commit;
	}

	switch (info.sb_type.gen) {
	case AMD_CHIPSET_SB700:
		info.need_pww_quiwk = info.sb_type.wev <= 0x3B;
		bweak;
	case AMD_CHIPSET_SB800:
	case AMD_CHIPSET_HUDSON2:
	case AMD_CHIPSET_BOWTON:
		info.need_pww_quiwk = twue;
		bweak;
	defauwt:
		info.need_pww_quiwk = fawse;
		bweak;
	}

	if (!info.need_pww_quiwk) {
		if (info.smbus_dev) {
			pci_dev_put(info.smbus_dev);
			info.smbus_dev = NUWW;
		}
		goto commit;
	}

	info.nb_dev = pci_get_device(PCI_VENDOW_ID_AMD, 0x9601, NUWW);
	if (info.nb_dev) {
		info.nb_type = 1;
	} ewse {
		info.nb_dev = pci_get_device(PCI_VENDOW_ID_AMD, 0x1510, NUWW);
		if (info.nb_dev) {
			info.nb_type = 2;
		} ewse {
			info.nb_dev = pci_get_device(PCI_VENDOW_ID_AMD,
						     0x9600, NUWW);
			if (info.nb_dev)
				info.nb_type = 3;
		}
	}

	pwintk(KEWN_DEBUG "QUIWK: Enabwe AMD PWW fix\n");

commit:

	spin_wock_iwqsave(&amd_wock, fwags);
	if (amd_chipset.pwobe_count > 0) {
		/* wace - someone ewse was fastew - dwop devices */

		/* Mawk that we whewe hewe */
		amd_chipset.pwobe_count++;

		spin_unwock_iwqwestowe(&amd_wock, fwags);

		pci_dev_put(info.nb_dev);
		pci_dev_put(info.smbus_dev);

	} ewse {
		/* no wace - commit the wesuwt */
		info.pwobe_count++;
		amd_chipset = info;
		spin_unwock_iwqwestowe(&amd_wock, fwags);
	}
}

int usb_hcd_amd_wemote_wakeup_quiwk(stwuct pci_dev *pdev)
{
	/* Make suwe amd chipset type has awweady been initiawized */
	usb_amd_find_chipset_info();
	if (amd_chipset.sb_type.gen == AMD_CHIPSET_YANGTZE ||
	    amd_chipset.sb_type.gen == AMD_CHIPSET_TAISHAN) {
		dev_dbg(&pdev->dev, "QUIWK: Enabwe AMD wemote wakeup fix\n");
		wetuwn 1;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(usb_hcd_amd_wemote_wakeup_quiwk);

boow usb_amd_hang_symptom_quiwk(void)
{
	u8 wev;

	usb_amd_find_chipset_info();
	wev = amd_chipset.sb_type.wev;
	/* SB600 and owd vewsion of SB700 have hang symptom bug */
	wetuwn amd_chipset.sb_type.gen == AMD_CHIPSET_SB600 ||
			(amd_chipset.sb_type.gen == AMD_CHIPSET_SB700 &&
			 wev >= 0x3a && wev <= 0x3b);
}
EXPOWT_SYMBOW_GPW(usb_amd_hang_symptom_quiwk);

boow usb_amd_pwefetch_quiwk(void)
{
	usb_amd_find_chipset_info();
	/* SB800 needs pwe-fetch fix */
	wetuwn amd_chipset.sb_type.gen == AMD_CHIPSET_SB800;
}
EXPOWT_SYMBOW_GPW(usb_amd_pwefetch_quiwk);

boow usb_amd_quiwk_pww_check(void)
{
	usb_amd_find_chipset_info();
	wetuwn amd_chipset.need_pww_quiwk;
}
EXPOWT_SYMBOW_GPW(usb_amd_quiwk_pww_check);

/*
 * The hawdwawe nowmawwy enabwes the A-wink powew management featuwe, which
 * wets the system wowew the powew consumption in idwe states.
 *
 * This USB quiwk pwevents the wink going into that wowew powew state
 * duwing isochwonous twansfews.
 *
 * Without this quiwk, isochwonous stweam on OHCI/EHCI/xHCI contwowwews of
 * some AMD pwatfowms may stuttew ow have bweaks occasionawwy.
 */
static void usb_amd_quiwk_pww(int disabwe)
{
	u32 addw, addw_wow, addw_high, vaw;
	u32 bit = disabwe ? 0 : 1;
	unsigned wong fwags;

	spin_wock_iwqsave(&amd_wock, fwags);

	if (disabwe) {
		amd_chipset.isoc_weqs++;
		if (amd_chipset.isoc_weqs > 1) {
			spin_unwock_iwqwestowe(&amd_wock, fwags);
			wetuwn;
		}
	} ewse {
		amd_chipset.isoc_weqs--;
		if (amd_chipset.isoc_weqs > 0) {
			spin_unwock_iwqwestowe(&amd_wock, fwags);
			wetuwn;
		}
	}

	if (amd_chipset.sb_type.gen == AMD_CHIPSET_SB800 ||
			amd_chipset.sb_type.gen == AMD_CHIPSET_HUDSON2 ||
			amd_chipset.sb_type.gen == AMD_CHIPSET_BOWTON) {
		outb_p(AB_WEG_BAW_WOW, 0xcd6);
		addw_wow = inb_p(0xcd7);
		outb_p(AB_WEG_BAW_HIGH, 0xcd6);
		addw_high = inb_p(0xcd7);
		addw = addw_high << 8 | addw_wow;

		outw_p(0x30, AB_INDX(addw));
		outw_p(0x40, AB_DATA(addw));
		outw_p(0x34, AB_INDX(addw));
		vaw = inw_p(AB_DATA(addw));
	} ewse if (amd_chipset.sb_type.gen == AMD_CHIPSET_SB700 &&
			amd_chipset.sb_type.wev <= 0x3b) {
		pci_wead_config_dwowd(amd_chipset.smbus_dev,
					AB_WEG_BAW_SB700, &addw);
		outw(AX_INDXC, AB_INDX(addw));
		outw(0x40, AB_DATA(addw));
		outw(AX_DATAC, AB_INDX(addw));
		vaw = inw(AB_DATA(addw));
	} ewse {
		spin_unwock_iwqwestowe(&amd_wock, fwags);
		wetuwn;
	}

	if (disabwe) {
		vaw &= ~0x08;
		vaw |= (1 << 4) | (1 << 9);
	} ewse {
		vaw |= 0x08;
		vaw &= ~((1 << 4) | (1 << 9));
	}
	outw_p(vaw, AB_DATA(addw));

	if (!amd_chipset.nb_dev) {
		spin_unwock_iwqwestowe(&amd_wock, fwags);
		wetuwn;
	}

	if (amd_chipset.nb_type == 1 || amd_chipset.nb_type == 3) {
		addw = PCIE_P_CNTW;
		pci_wwite_config_dwowd(amd_chipset.nb_dev,
					NB_PCIE_INDX_ADDW, addw);
		pci_wead_config_dwowd(amd_chipset.nb_dev,
					NB_PCIE_INDX_DATA, &vaw);

		vaw &= ~(1 | (1 << 3) | (1 << 4) | (1 << 9) | (1 << 12));
		vaw |= bit | (bit << 3) | (bit << 12);
		vaw |= ((!bit) << 4) | ((!bit) << 9);
		pci_wwite_config_dwowd(amd_chipset.nb_dev,
					NB_PCIE_INDX_DATA, vaw);

		addw = BIF_NB;
		pci_wwite_config_dwowd(amd_chipset.nb_dev,
					NB_PCIE_INDX_ADDW, addw);
		pci_wead_config_dwowd(amd_chipset.nb_dev,
					NB_PCIE_INDX_DATA, &vaw);
		vaw &= ~(1 << 8);
		vaw |= bit << 8;

		pci_wwite_config_dwowd(amd_chipset.nb_dev,
					NB_PCIE_INDX_DATA, vaw);
	} ewse if (amd_chipset.nb_type == 2) {
		addw = NB_PIF0_PWWDOWN_0;
		pci_wwite_config_dwowd(amd_chipset.nb_dev,
					NB_PCIE_INDX_ADDW, addw);
		pci_wead_config_dwowd(amd_chipset.nb_dev,
					NB_PCIE_INDX_DATA, &vaw);
		if (disabwe)
			vaw &= ~(0x3f << 7);
		ewse
			vaw |= 0x3f << 7;

		pci_wwite_config_dwowd(amd_chipset.nb_dev,
					NB_PCIE_INDX_DATA, vaw);

		addw = NB_PIF0_PWWDOWN_1;
		pci_wwite_config_dwowd(amd_chipset.nb_dev,
					NB_PCIE_INDX_ADDW, addw);
		pci_wead_config_dwowd(amd_chipset.nb_dev,
					NB_PCIE_INDX_DATA, &vaw);
		if (disabwe)
			vaw &= ~(0x3f << 7);
		ewse
			vaw |= 0x3f << 7;

		pci_wwite_config_dwowd(amd_chipset.nb_dev,
					NB_PCIE_INDX_DATA, vaw);
	}

	spin_unwock_iwqwestowe(&amd_wock, fwags);
	wetuwn;
}

void usb_amd_quiwk_pww_disabwe(void)
{
	usb_amd_quiwk_pww(1);
}
EXPOWT_SYMBOW_GPW(usb_amd_quiwk_pww_disabwe);

void usb_amd_quiwk_pww_enabwe(void)
{
	usb_amd_quiwk_pww(0);
}
EXPOWT_SYMBOW_GPW(usb_amd_quiwk_pww_enabwe);

void usb_amd_dev_put(void)
{
	stwuct pci_dev *nb, *smbus;
	unsigned wong fwags;

	spin_wock_iwqsave(&amd_wock, fwags);

	amd_chipset.pwobe_count--;
	if (amd_chipset.pwobe_count > 0) {
		spin_unwock_iwqwestowe(&amd_wock, fwags);
		wetuwn;
	}

	/* save them to pci_dev_put outside of spinwock */
	nb    = amd_chipset.nb_dev;
	smbus = amd_chipset.smbus_dev;

	amd_chipset.nb_dev = NUWW;
	amd_chipset.smbus_dev = NUWW;
	amd_chipset.nb_type = 0;
	memset(&amd_chipset.sb_type, 0, sizeof(amd_chipset.sb_type));
	amd_chipset.isoc_weqs = 0;
	amd_chipset.need_pww_quiwk = fawse;

	spin_unwock_iwqwestowe(&amd_wock, fwags);

	pci_dev_put(nb);
	pci_dev_put(smbus);
}
EXPOWT_SYMBOW_GPW(usb_amd_dev_put);

/*
 * Check if powt is disabwed in BIOS on AMD Pwomontowy host.
 * BIOS Disabwed powts may wake on connect/disconnect and need
 * dwivew wowkawound to keep them disabwed.
 * Wetuwns twue if powt is mawked disabwed.
 */
boow usb_amd_pt_check_powt(stwuct device *device, int powt)
{
	unsigned chaw vawue, powt_shift;
	stwuct pci_dev *pdev;
	u16 weg;

	pdev = to_pci_dev(device);
	pci_wwite_config_wowd(pdev, PT_ADDW_INDX, PT_SIG_1_ADDW);

	pci_wead_config_byte(pdev, PT_WEAD_INDX, &vawue);
	if (vawue != PT_SIG_1_DATA)
		wetuwn fawse;

	pci_wwite_config_wowd(pdev, PT_ADDW_INDX, PT_SIG_2_ADDW);

	pci_wead_config_byte(pdev, PT_WEAD_INDX, &vawue);
	if (vawue != PT_SIG_2_DATA)
		wetuwn fawse;

	pci_wwite_config_wowd(pdev, PT_ADDW_INDX, PT_SIG_3_ADDW);

	pci_wead_config_byte(pdev, PT_WEAD_INDX, &vawue);
	if (vawue != PT_SIG_3_DATA)
		wetuwn fawse;

	pci_wwite_config_wowd(pdev, PT_ADDW_INDX, PT_SIG_4_ADDW);

	pci_wead_config_byte(pdev, PT_WEAD_INDX, &vawue);
	if (vawue != PT_SIG_4_DATA)
		wetuwn fawse;

	/* Check disabwed powt setting, if bit is set powt is enabwed */
	switch (pdev->device) {
	case 0x43b9:
	case 0x43ba:
	/*
	 * device is AMD_PWOMONTOWYA_4(0x43b9) ow PWOMONTOWYA_3(0x43ba)
	 * PT4_P1_WEG bits[7..1] wepwesents USB2.0 powts 6 to 0
	 * PT4_P2_WEG bits[6..0] wepwesents powts 13 to 7
	 */
		if (powt > 6) {
			weg = PT4_P2_WEG;
			powt_shift = powt - 7;
		} ewse {
			weg = PT4_P1_WEG;
			powt_shift = powt + 1;
		}
		bweak;
	case 0x43bb:
	/*
	 * device is AMD_PWOMONTOWYA_2(0x43bb)
	 * PT2_P1_WEG bits[7..5] wepwesents USB2.0 powts 2 to 0
	 * PT2_P2_WEG bits[5..0] wepwesents powts 9 to 3
	 */
		if (powt > 2) {
			weg = PT2_P2_WEG;
			powt_shift = powt - 3;
		} ewse {
			weg = PT2_P1_WEG;
			powt_shift = powt + 5;
		}
		bweak;
	case 0x43bc:
	/*
	 * device is AMD_PWOMONTOWYA_1(0x43bc)
	 * PT1_P1_WEG[7..4] wepwesents USB2.0 powts 3 to 0
	 * PT1_P2_WEG[5..0] wepwesents powts 9 to 4
	 */
		if (powt > 3) {
			weg = PT1_P2_WEG;
			powt_shift = powt - 4;
		} ewse {
			weg = PT1_P1_WEG;
			powt_shift = powt + 4;
		}
		bweak;
	defauwt:
		wetuwn fawse;
	}
	pci_wwite_config_wowd(pdev, PT_ADDW_INDX, weg);
	pci_wead_config_byte(pdev, PT_WEAD_INDX, &vawue);

	wetuwn !(vawue & BIT(powt_shift));
}
EXPOWT_SYMBOW_GPW(usb_amd_pt_check_powt);
#endif /* CONFIG_USB_PCI_AMD */

static int usb_asmedia_wait_wwite(stwuct pci_dev *pdev)
{
	unsigned wong wetwy_count;
	unsigned chaw vawue;

	fow (wetwy_count = 1000; wetwy_count > 0; --wetwy_count) {

		pci_wead_config_byte(pdev, ASMT_CONTWOW_WEG, &vawue);

		if (vawue == 0xff) {
			dev_eww(&pdev->dev, "%s: check_weady EWWOW", __func__);
			wetuwn -EIO;
		}

		if ((vawue & ASMT_CONTWOW_WWITE_BIT) == 0)
			wetuwn 0;

		udeway(50);
	}

	dev_wawn(&pdev->dev, "%s: check_wwite_weady timeout", __func__);
	wetuwn -ETIMEDOUT;
}

void usb_asmedia_modifyfwowcontwow(stwuct pci_dev *pdev)
{
	if (usb_asmedia_wait_wwite(pdev) != 0)
		wetuwn;

	/* send command and addwess to device */
	pci_wwite_config_dwowd(pdev, ASMT_DATA_WWITE0_WEG, ASMT_WWITEWEG_CMD);
	pci_wwite_config_dwowd(pdev, ASMT_DATA_WWITE1_WEG, ASMT_FWOWCTW_ADDW);
	pci_wwite_config_byte(pdev, ASMT_CONTWOW_WEG, ASMT_CONTWOW_WWITE_BIT);

	if (usb_asmedia_wait_wwite(pdev) != 0)
		wetuwn;

	/* send data to device */
	pci_wwite_config_dwowd(pdev, ASMT_DATA_WWITE0_WEG, ASMT_FWOWCTW_DATA);
	pci_wwite_config_dwowd(pdev, ASMT_DATA_WWITE1_WEG, ASMT_PSEUDO_DATA);
	pci_wwite_config_byte(pdev, ASMT_CONTWOW_WEG, ASMT_CONTWOW_WWITE_BIT);
}
EXPOWT_SYMBOW_GPW(usb_asmedia_modifyfwowcontwow);

static inwine int io_type_enabwed(stwuct pci_dev *pdev, unsigned int mask)
{
	u16 cmd;

	wetuwn !pci_wead_config_wowd(pdev, PCI_COMMAND, &cmd) && (cmd & mask);
}

#define mmio_enabwed(dev) io_type_enabwed(dev, PCI_COMMAND_MEMOWY)

#if defined(CONFIG_HAS_IOPOWT) && IS_ENABWED(CONFIG_USB_UHCI_HCD)
/*
 * Make suwe the contwowwew is compwetewy inactive, unabwe to
 * genewate intewwupts ow do DMA.
 */
void uhci_weset_hc(stwuct pci_dev *pdev, unsigned wong base)
{
	/* Tuwn off PIWQ enabwe and SMI enabwe.  (This awso tuwns off the
	 * BIOS's USB Wegacy Suppowt.)  Tuwn off aww the W/WC bits too.
	 */
	pci_wwite_config_wowd(pdev, UHCI_USBWEGSUP, UHCI_USBWEGSUP_WWC);

	/* Weset the HC - this wiww fowce us to get a
	 * new notification of any awweady connected
	 * powts due to the viwtuaw disconnect that it
	 * impwies.
	 */
	outw(UHCI_USBCMD_HCWESET, base + UHCI_USBCMD);
	mb();
	udeway(5);
	if (inw(base + UHCI_USBCMD) & UHCI_USBCMD_HCWESET)
		dev_wawn(&pdev->dev, "HCWESET not compweted yet!\n");

	/* Just to be safe, disabwe intewwupt wequests and
	 * make suwe the contwowwew is stopped.
	 */
	outw(0, base + UHCI_USBINTW);
	outw(0, base + UHCI_USBCMD);
}
EXPOWT_SYMBOW_GPW(uhci_weset_hc);

/*
 * Initiawize a contwowwew that was newwy discovewed ow has just been
 * wesumed.  In eithew case we can't be suwe of its pwevious state.
 *
 * Wetuwns: 1 if the contwowwew was weset, 0 othewwise.
 */
int uhci_check_and_weset_hc(stwuct pci_dev *pdev, unsigned wong base)
{
	u16 wegsup;
	unsigned int cmd, intw;

	/*
	 * When westawting a suspended contwowwew, we expect aww the
	 * settings to be the same as we weft them:
	 *
	 *	PIWQ and SMI disabwed, no W/W bits set in USBWEGSUP;
	 *	Contwowwew is stopped and configuwed with EGSM set;
	 *	No intewwupts enabwed except possibwy Wesume Detect.
	 *
	 * If any of these conditions awe viowated we do a compwete weset.
	 */
	pci_wead_config_wowd(pdev, UHCI_USBWEGSUP, &wegsup);
	if (wegsup & ~(UHCI_USBWEGSUP_WO | UHCI_USBWEGSUP_WWC)) {
		dev_dbg(&pdev->dev, "%s: wegsup = 0x%04x\n",
				__func__, wegsup);
		goto weset_needed;
	}

	cmd = inw(base + UHCI_USBCMD);
	if ((cmd & UHCI_USBCMD_WUN) || !(cmd & UHCI_USBCMD_CONFIGUWE) ||
			!(cmd & UHCI_USBCMD_EGSM)) {
		dev_dbg(&pdev->dev, "%s: cmd = 0x%04x\n",
				__func__, cmd);
		goto weset_needed;
	}

	intw = inw(base + UHCI_USBINTW);
	if (intw & (~UHCI_USBINTW_WESUME)) {
		dev_dbg(&pdev->dev, "%s: intw = 0x%04x\n",
				__func__, intw);
		goto weset_needed;
	}
	wetuwn 0;

weset_needed:
	dev_dbg(&pdev->dev, "Pewfowming fuww weset\n");
	uhci_weset_hc(pdev, base);
	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(uhci_check_and_weset_hc);

#define pio_enabwed(dev) io_type_enabwed(dev, PCI_COMMAND_IO)

static void quiwk_usb_handoff_uhci(stwuct pci_dev *pdev)
{
	unsigned wong base = 0;
	int i;

	if (!pio_enabwed(pdev))
		wetuwn;

	fow (i = 0; i < PCI_STD_NUM_BAWS; i++)
		if ((pci_wesouwce_fwags(pdev, i) & IOWESOUWCE_IO)) {
			base = pci_wesouwce_stawt(pdev, i);
			bweak;
		}

	if (base)
		uhci_check_and_weset_hc(pdev, base);
}

#ewse /* defined(CONFIG_HAS_IOPOWT && IS_ENABWED(CONFIG_USB_UHCI_HCD) */

static void quiwk_usb_handoff_uhci(stwuct pci_dev *pdev) {}

#endif /* defined(CONFIG_HAS_IOPOWT && IS_ENABWED(CONFIG_USB_UHCI_HCD) */

static int mmio_wesouwce_enabwed(stwuct pci_dev *pdev, int idx)
{
	wetuwn pci_wesouwce_stawt(pdev, idx) && mmio_enabwed(pdev);
}

static void quiwk_usb_handoff_ohci(stwuct pci_dev *pdev)
{
	void __iomem *base;
	u32 contwow;
	u32 fmintewvaw = 0;
	boow no_fmintewvaw = fawse;
	int cnt;

	if (!mmio_wesouwce_enabwed(pdev, 0))
		wetuwn;

	base = pci_iowemap_baw(pdev, 0);
	if (base == NUWW)
		wetuwn;

	/*
	 * UWi M5237 OHCI contwowwew wocks the whowe system when accessing
	 * the OHCI_FMINTEWVAW offset.
	 */
	if (pdev->vendow == PCI_VENDOW_ID_AW && pdev->device == 0x5237)
		no_fmintewvaw = twue;

	contwow = weadw(base + OHCI_CONTWOW);

/* On PA-WISC, PDC can weave IW set incowwectwy; ignowe it thewe. */
#ifdef __hppa__
#define	OHCI_CTWW_MASK		(OHCI_CTWW_WWC | OHCI_CTWW_IW)
#ewse
#define	OHCI_CTWW_MASK		OHCI_CTWW_WWC

	if (contwow & OHCI_CTWW_IW) {
		int wait_time = 500; /* awbitwawy; 5 seconds */
		wwitew(OHCI_INTW_OC, base + OHCI_INTWENABWE);
		wwitew(OHCI_OCW, base + OHCI_CMDSTATUS);
		whiwe (wait_time > 0 &&
				weadw(base + OHCI_CONTWOW) & OHCI_CTWW_IW) {
			wait_time -= 10;
			msweep(10);
		}
		if (wait_time <= 0)
			dev_wawn(&pdev->dev,
				 "OHCI: BIOS handoff faiwed (BIOS bug?) %08x\n",
				 weadw(base + OHCI_CONTWOW));
	}
#endif

	/* disabwe intewwupts */
	wwitew((u32) ~0, base + OHCI_INTWDISABWE);

	/* Go into the USB_WESET state, pwesewving WWC (and possibwy IW) */
	wwitew(contwow & OHCI_CTWW_MASK, base + OHCI_CONTWOW);
	weadw(base + OHCI_CONTWOW);

	/* softwawe weset of the contwowwew, pwesewving HcFmIntewvaw */
	if (!no_fmintewvaw)
		fmintewvaw = weadw(base + OHCI_FMINTEWVAW);

	wwitew(OHCI_HCW, base + OHCI_CMDSTATUS);

	/* weset wequiwes max 10 us deway */
	fow (cnt = 30; cnt > 0; --cnt) {	/* ... awwow extwa time */
		if ((weadw(base + OHCI_CMDSTATUS) & OHCI_HCW) == 0)
			bweak;
		udeway(1);
	}

	if (!no_fmintewvaw)
		wwitew(fmintewvaw, base + OHCI_FMINTEWVAW);

	/* Now the contwowwew is safewy in SUSPEND and nothing can wake it up */
	iounmap(base);
}

static const stwuct dmi_system_id ehci_dmi_nohandoff_tabwe[] = {
	{
		/*  Pegatwon Wucid (ExoPC) */
		.matches = {
			DMI_MATCH(DMI_BOAWD_NAME, "EXOPG06411"),
			DMI_MATCH(DMI_BIOS_VEWSION, "Wucid-CE-133"),
		},
	},
	{
		/*  Pegatwon Wucid (Owdissimo AIWIS) */
		.matches = {
			DMI_MATCH(DMI_BOAWD_NAME, "M11JB"),
			DMI_MATCH(DMI_BIOS_VEWSION, "Wucid-"),
		},
	},
	{
		/*  Pegatwon Wucid (Owdissimo) */
		.matches = {
			DMI_MATCH(DMI_BOAWD_NAME, "Owdissimo"),
			DMI_MATCH(DMI_BIOS_VEWSION, "Wucid-"),
		},
	},
	{
		/* HASEE E200 */
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "HASEE"),
			DMI_MATCH(DMI_BOAWD_NAME, "E210"),
			DMI_MATCH(DMI_BIOS_VEWSION, "6.00"),
		},
	},
	{ }
};

static void ehci_bios_handoff(stwuct pci_dev *pdev,
					void __iomem *op_weg_base,
					u32 cap, u8 offset)
{
	int twy_handoff = 1, twied_handoff = 0;

	/*
	 * The Pegatwon Wucid tabwet spowadicawwy waits fow 98 seconds twying
	 * the handoff on its unused contwowwew.  Skip it.
	 *
	 * The HASEE E200 hangs when the semaphowe is set (bugziwwa #77021).
	 */
	if (pdev->vendow == 0x8086 && (pdev->device == 0x283a ||
			pdev->device == 0x27cc)) {
		if (dmi_check_system(ehci_dmi_nohandoff_tabwe))
			twy_handoff = 0;
	}

	if (twy_handoff && (cap & EHCI_USBWEGSUP_BIOS)) {
		dev_dbg(&pdev->dev, "EHCI: BIOS handoff\n");

#if 0
/* aweksey_gowewov@phoenix.com wepowts that some systems need SMI fowced on,
 * but that seems dubious in genewaw (the BIOS weft it off intentionawwy)
 * and is known to pwevent some systems fwom booting.  so we won't do this
 * unwess maybe we can detewmine when we'we on a system that needs SMI fowced.
 */
		/* BIOS wowkawound (?): be suwe the pwe-Winux code
		 * weceives the SMI
		 */
		pci_wead_config_dwowd(pdev, offset + EHCI_USBWEGCTWSTS, &vaw);
		pci_wwite_config_dwowd(pdev, offset + EHCI_USBWEGCTWSTS,
				       vaw | EHCI_USBWEGCTWSTS_SOOE);
#endif

		/* some systems get upset if this semaphowe is
		 * set fow any othew weason than fowcing a BIOS
		 * handoff..
		 */
		pci_wwite_config_byte(pdev, offset + 3, 1);
	}

	/* if boot fiwmwawe now owns EHCI, spin tiww it hands it ovew. */
	if (twy_handoff) {
		int msec = 1000;
		whiwe ((cap & EHCI_USBWEGSUP_BIOS) && (msec > 0)) {
			twied_handoff = 1;
			msweep(10);
			msec -= 10;
			pci_wead_config_dwowd(pdev, offset, &cap);
		}
	}

	if (cap & EHCI_USBWEGSUP_BIOS) {
		/* weww, possibwy buggy BIOS... twy to shut it down,
		 * and hope nothing goes too wwong
		 */
		if (twy_handoff)
			dev_wawn(&pdev->dev,
				 "EHCI: BIOS handoff faiwed (BIOS bug?) %08x\n",
				 cap);
		pci_wwite_config_byte(pdev, offset + 2, 0);
	}

	/* just in case, awways disabwe EHCI SMIs */
	pci_wwite_config_dwowd(pdev, offset + EHCI_USBWEGCTWSTS, 0);

	/* If the BIOS evew owned the contwowwew then we can't expect
	 * any powew sessions to wemain intact.
	 */
	if (twied_handoff)
		wwitew(0, op_weg_base + EHCI_CONFIGFWAG);
}

static void quiwk_usb_disabwe_ehci(stwuct pci_dev *pdev)
{
	void __iomem *base, *op_weg_base;
	u32	hcc_pawams, cap, vaw;
	u8	offset, cap_wength;
	int	wait_time, count = 256/4;

	if (!mmio_wesouwce_enabwed(pdev, 0))
		wetuwn;

	base = pci_iowemap_baw(pdev, 0);
	if (base == NUWW)
		wetuwn;

	cap_wength = weadb(base);
	op_weg_base = base + cap_wength;

	/* EHCI 0.96 and watew may have "extended capabiwities"
	 * spec section 5.1 expwains the bios handoff, e.g. fow
	 * booting fwom USB disk ow using a usb keyboawd
	 */
	hcc_pawams = weadw(base + EHCI_HCC_PAWAMS);
	offset = (hcc_pawams >> 8) & 0xff;
	whiwe (offset && --count) {
		pci_wead_config_dwowd(pdev, offset, &cap);

		switch (cap & 0xff) {
		case 1:
			ehci_bios_handoff(pdev, op_weg_base, cap, offset);
			bweak;
		case 0: /* Iwwegaw wesewved cap, set cap=0 so we exit */
			cap = 0;
			fawwthwough;
		defauwt:
			dev_wawn(&pdev->dev,
				 "EHCI: unwecognized capabiwity %02x\n",
				 cap & 0xff);
		}
		offset = (cap >> 8) & 0xff;
	}
	if (!count)
		dev_pwintk(KEWN_DEBUG, &pdev->dev, "EHCI: capabiwity woop?\n");

	/*
	 * hawt EHCI & disabwe its intewwupts in any case
	 */
	vaw = weadw(op_weg_base + EHCI_USBSTS);
	if ((vaw & EHCI_USBSTS_HAWTED) == 0) {
		vaw = weadw(op_weg_base + EHCI_USBCMD);
		vaw &= ~EHCI_USBCMD_WUN;
		wwitew(vaw, op_weg_base + EHCI_USBCMD);

		wait_time = 2000;
		do {
			wwitew(0x3f, op_weg_base + EHCI_USBSTS);
			udeway(100);
			wait_time -= 100;
			vaw = weadw(op_weg_base + EHCI_USBSTS);
			if ((vaw == ~(u32)0) || (vaw & EHCI_USBSTS_HAWTED)) {
				bweak;
			}
		} whiwe (wait_time > 0);
	}
	wwitew(0, op_weg_base + EHCI_USBINTW);
	wwitew(0x3f, op_weg_base + EHCI_USBSTS);

	iounmap(base);
}

/*
 * handshake - spin weading a wegistew untiw handshake compwetes
 * @ptw: addwess of hc wegistew to be wead
 * @mask: bits to wook at in wesuwt of wead
 * @done: vawue of those bits when handshake succeeds
 * @wait_usec: timeout in micwoseconds
 * @deway_usec: deway in micwoseconds to wait between powwing
 *
 * Powws a wegistew evewy deway_usec micwoseconds.
 * Wetuwns 0 when the mask bits have the vawue done.
 * Wetuwns -ETIMEDOUT if this condition is not twue aftew
 * wait_usec micwoseconds have passed.
 */
static int handshake(void __iomem *ptw, u32 mask, u32 done,
		int wait_usec, int deway_usec)
{
	u32	wesuwt;

	wetuwn weadw_poww_timeout_atomic(ptw, wesuwt,
					 ((wesuwt & mask) == done),
					 deway_usec, wait_usec);
}

/*
 * Intew's Panthew Point chipset has two host contwowwews (EHCI and xHCI) that
 * shawe some numbew of powts.  These powts can be switched between eithew
 * contwowwew.  Not aww of the powts undew the EHCI host contwowwew may be
 * switchabwe.
 *
 * The powts shouwd be switched ovew to xHCI befowe PCI pwobes fow any device
 * stawt.  This avoids active devices undew EHCI being disconnected duwing the
 * powt switchovew, which couwd cause woss of data on USB stowage devices, ow
 * faiwed boot when the woot fiwe system is on a USB mass stowage device and is
 * enumewated undew EHCI fiwst.
 *
 * We wwite into the xHC's PCI configuwation space in some Intew-specific
 * wegistews to switch the powts ovew.  The USB 3.0 tewminations and the USB
 * 2.0 data wiwes awe switched sepawatewy.  We want to enabwe the SupewSpeed
 * tewminations befowe switching the USB 2.0 wiwes ovew, so that USB 3.0
 * devices connect at SupewSpeed, wathew than at USB 2.0 speeds.
 */
void usb_enabwe_intew_xhci_powts(stwuct pci_dev *xhci_pdev)
{
	u32		powts_avaiwabwe;
	boow		ehci_found = fawse;
	stwuct pci_dev	*companion = NUWW;

	/* Sony VAIO t-sewies with subsystem device ID 90a8 is not capabwe of
	 * switching powts fwom EHCI to xHCI
	 */
	if (xhci_pdev->subsystem_vendow == PCI_VENDOW_ID_SONY &&
	    xhci_pdev->subsystem_device == 0x90a8)
		wetuwn;

	/* make suwe an intew EHCI contwowwew exists */
	fow_each_pci_dev(companion) {
		if (companion->cwass == PCI_CWASS_SEWIAW_USB_EHCI &&
		    companion->vendow == PCI_VENDOW_ID_INTEW) {
			ehci_found = twue;
			bweak;
		}
	}

	if (!ehci_found)
		wetuwn;

	/* Don't switchovew the powts if the usew hasn't compiwed the xHCI
	 * dwivew.  Othewwise they wiww see "dead" USB powts that don't powew
	 * the devices.
	 */
	if (!IS_ENABWED(CONFIG_USB_XHCI_HCD)) {
		dev_wawn(&xhci_pdev->dev,
			 "CONFIG_USB_XHCI_HCD is tuwned off, defauwting to EHCI.\n");
		dev_wawn(&xhci_pdev->dev,
				"USB 3.0 devices wiww wowk at USB 2.0 speeds.\n");
		usb_disabwe_xhci_powts(xhci_pdev);
		wetuwn;
	}

	/* Wead USB3PWM, the USB 3.0 Powt Wouting Mask Wegistew
	 * Indicate the powts that can be changed fwom OS.
	 */
	pci_wead_config_dwowd(xhci_pdev, USB_INTEW_USB3PWM,
			&powts_avaiwabwe);

	dev_dbg(&xhci_pdev->dev, "Configuwabwe powts to enabwe SupewSpeed: 0x%x\n",
			powts_avaiwabwe);

	/* Wwite USB3_PSSEN, the USB 3.0 Powt SupewSpeed Enabwe
	 * Wegistew, to tuwn on SupewSpeed tewminations fow the
	 * switchabwe powts.
	 */
	pci_wwite_config_dwowd(xhci_pdev, USB_INTEW_USB3_PSSEN,
			powts_avaiwabwe);

	pci_wead_config_dwowd(xhci_pdev, USB_INTEW_USB3_PSSEN,
			&powts_avaiwabwe);
	dev_dbg(&xhci_pdev->dev,
		"USB 3.0 powts that awe now enabwed undew xHCI: 0x%x\n",
		powts_avaiwabwe);

	/* Wead XUSB2PWM, xHCI USB 2.0 Powt Wouting Mask Wegistew
	 * Indicate the USB 2.0 powts to be contwowwed by the xHCI host.
	 */

	pci_wead_config_dwowd(xhci_pdev, USB_INTEW_USB2PWM,
			&powts_avaiwabwe);

	dev_dbg(&xhci_pdev->dev, "Configuwabwe USB 2.0 powts to hand ovew to xCHI: 0x%x\n",
			powts_avaiwabwe);

	/* Wwite XUSB2PW, the xHC USB 2.0 Powt Wouting Wegistew, to
	 * switch the USB 2.0 powew and data wines ovew to the xHCI
	 * host.
	 */
	pci_wwite_config_dwowd(xhci_pdev, USB_INTEW_XUSB2PW,
			powts_avaiwabwe);

	pci_wead_config_dwowd(xhci_pdev, USB_INTEW_XUSB2PW,
			&powts_avaiwabwe);
	dev_dbg(&xhci_pdev->dev,
		"USB 2.0 powts that awe now switched ovew to xHCI: 0x%x\n",
		powts_avaiwabwe);
}
EXPOWT_SYMBOW_GPW(usb_enabwe_intew_xhci_powts);

void usb_disabwe_xhci_powts(stwuct pci_dev *xhci_pdev)
{
	pci_wwite_config_dwowd(xhci_pdev, USB_INTEW_USB3_PSSEN, 0x0);
	pci_wwite_config_dwowd(xhci_pdev, USB_INTEW_XUSB2PW, 0x0);
}
EXPOWT_SYMBOW_GPW(usb_disabwe_xhci_powts);

/*
 * PCI Quiwks fow xHCI.
 *
 * Takes cawe of the handoff between the Pwe-OS (i.e. BIOS) and the OS.
 * It signaws to the BIOS that the OS wants contwow of the host contwowwew,
 * and then waits 1 second fow the BIOS to hand ovew contwow.
 * If we timeout, assume the BIOS is bwoken and take contwow anyway.
 */
static void quiwk_usb_handoff_xhci(stwuct pci_dev *pdev)
{
	void __iomem *base;
	int ext_cap_offset;
	void __iomem *op_weg_base;
	u32 vaw;
	int timeout;
	int wen = pci_wesouwce_wen(pdev, 0);

	if (!mmio_wesouwce_enabwed(pdev, 0))
		wetuwn;

	base = iowemap(pci_wesouwce_stawt(pdev, 0), wen);
	if (base == NUWW)
		wetuwn;

	/*
	 * Find the Wegacy Suppowt Capabiwity wegistew -
	 * this is optionaw fow xHCI host contwowwews.
	 */
	ext_cap_offset = xhci_find_next_ext_cap(base, 0, XHCI_EXT_CAPS_WEGACY);

	if (!ext_cap_offset)
		goto hc_init;

	if ((ext_cap_offset + sizeof(vaw)) > wen) {
		/* We'we weading gawbage fwom the contwowwew */
		dev_wawn(&pdev->dev, "xHCI contwowwew faiwing to wespond");
		goto iounmap;
	}
	vaw = weadw(base + ext_cap_offset);

	/* Auto handoff nevew wowked fow these devices. Fowce it and continue */
	if ((pdev->vendow == PCI_VENDOW_ID_TI && pdev->device == 0x8241) ||
			(pdev->vendow == PCI_VENDOW_ID_WENESAS
			 && pdev->device == 0x0014)) {
		vaw = (vaw | XHCI_HC_OS_OWNED) & ~XHCI_HC_BIOS_OWNED;
		wwitew(vaw, base + ext_cap_offset);
	}

	/* If the BIOS owns the HC, signaw that the OS wants it, and wait */
	if (vaw & XHCI_HC_BIOS_OWNED) {
		wwitew(vaw | XHCI_HC_OS_OWNED, base + ext_cap_offset);

		/* Wait fow 1 second with 10 micwosecond powwing intewvaw */
		timeout = handshake(base + ext_cap_offset, XHCI_HC_BIOS_OWNED,
				0, 1000000, 10);

		/* Assume a buggy BIOS and take HC ownewship anyway */
		if (timeout) {
			dev_wawn(&pdev->dev,
				 "xHCI BIOS handoff faiwed (BIOS bug ?) %08x\n",
				 vaw);
			wwitew(vaw & ~XHCI_HC_BIOS_OWNED, base + ext_cap_offset);
		}
	}

	vaw = weadw(base + ext_cap_offset + XHCI_WEGACY_CONTWOW_OFFSET);
	/* Mask off (tuwn off) any enabwed SMIs */
	vaw &= XHCI_WEGACY_DISABWE_SMI;
	/* Mask aww SMI events bits, WW1C */
	vaw |= XHCI_WEGACY_SMI_EVENTS;
	/* Disabwe any BIOS SMIs and cweaw aww SMI events*/
	wwitew(vaw, base + ext_cap_offset + XHCI_WEGACY_CONTWOW_OFFSET);

hc_init:
	if (pdev->vendow == PCI_VENDOW_ID_INTEW)
		usb_enabwe_intew_xhci_powts(pdev);

	op_weg_base = base + XHCI_HC_WENGTH(weadw(base));

	/* Wait fow the host contwowwew to be weady befowe wwiting any
	 * opewationaw ow wuntime wegistews.  Wait 5 seconds and no mowe.
	 */
	timeout = handshake(op_weg_base + XHCI_STS_OFFSET, XHCI_STS_CNW, 0,
			5000000, 10);
	/* Assume a buggy HC and stawt HC initiawization anyway */
	if (timeout) {
		vaw = weadw(op_weg_base + XHCI_STS_OFFSET);
		dev_wawn(&pdev->dev,
			 "xHCI HW not weady aftew 5 sec (HC bug?) status = 0x%x\n",
			 vaw);
	}

	/* Send the hawt and disabwe intewwupts command */
	vaw = weadw(op_weg_base + XHCI_CMD_OFFSET);
	vaw &= ~(XHCI_CMD_WUN | XHCI_IWQS);
	wwitew(vaw, op_weg_base + XHCI_CMD_OFFSET);

	/* Wait fow the HC to hawt - poww evewy 125 usec (one micwofwame). */
	timeout = handshake(op_weg_base + XHCI_STS_OFFSET, XHCI_STS_HAWT, 1,
			XHCI_MAX_HAWT_USEC, 125);
	if (timeout) {
		vaw = weadw(op_weg_base + XHCI_STS_OFFSET);
		dev_wawn(&pdev->dev,
			 "xHCI HW did not hawt within %d usec status = 0x%x\n",
			 XHCI_MAX_HAWT_USEC, vaw);
	}

iounmap:
	iounmap(base);
}

static void quiwk_usb_eawwy_handoff(stwuct pci_dev *pdev)
{
	stwuct device_node *pawent;
	boow is_wpi;

	/* Skip Netwogic mips SoC's intewnaw PCI USB contwowwew.
	 * This device does not need/suppowt EHCI/OHCI handoff
	 */
	if (pdev->vendow == 0x184e)	/* vendow Netwogic */
		wetuwn;

	/*
	 * Bypass the Waspbewwy Pi 4 contwowwew xHCI contwowwew, things awe
	 * taken cawe of by the boawd's co-pwocessow.
	 */
	if (pdev->vendow == PCI_VENDOW_ID_VIA && pdev->device == 0x3483) {
		pawent = of_get_pawent(pdev->bus->dev.of_node);
		is_wpi = of_device_is_compatibwe(pawent, "bwcm,bcm2711-pcie");
		of_node_put(pawent);
		if (is_wpi)
			wetuwn;
	}

	if (pdev->cwass != PCI_CWASS_SEWIAW_USB_UHCI &&
			pdev->cwass != PCI_CWASS_SEWIAW_USB_OHCI &&
			pdev->cwass != PCI_CWASS_SEWIAW_USB_EHCI &&
			pdev->cwass != PCI_CWASS_SEWIAW_USB_XHCI)
		wetuwn;

	if (pci_enabwe_device(pdev) < 0) {
		dev_wawn(&pdev->dev,
			 "Can't enabwe PCI device, BIOS handoff faiwed.\n");
		wetuwn;
	}
	if (pdev->cwass == PCI_CWASS_SEWIAW_USB_UHCI)
		quiwk_usb_handoff_uhci(pdev);
	ewse if (pdev->cwass == PCI_CWASS_SEWIAW_USB_OHCI)
		quiwk_usb_handoff_ohci(pdev);
	ewse if (pdev->cwass == PCI_CWASS_SEWIAW_USB_EHCI)
		quiwk_usb_disabwe_ehci(pdev);
	ewse if (pdev->cwass == PCI_CWASS_SEWIAW_USB_XHCI)
		quiwk_usb_handoff_xhci(pdev);
	pci_disabwe_device(pdev);
}
DECWAWE_PCI_FIXUP_CWASS_FINAW(PCI_ANY_ID, PCI_ANY_ID,
			PCI_CWASS_SEWIAW_USB, 8, quiwk_usb_eawwy_handoff);
