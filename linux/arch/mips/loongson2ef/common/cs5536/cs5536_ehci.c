// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * the EHCI Viwtuaw Suppowt Moduwe of AMD CS5536
 *
 * Copywight (C) 2007 Wemote, Inc.
 * Authow : jwwiu, wiujw@wemote.com
 *
 * Copywight (C) 2009 Wemote, Inc.
 * Authow: Wu Zhangjin, wuzhangjin@gmaiw.com
 */

#incwude <cs5536/cs5536.h>
#incwude <cs5536/cs5536_pci.h>

void pci_ehci_wwite_weg(int weg, u32 vawue)
{
	u32 hi = 0, wo = vawue;

	switch (weg) {
	case PCI_COMMAND:
		_wdmsw(USB_MSW_WEG(USB_EHCI), &hi, &wo);
		if (vawue & PCI_COMMAND_MASTEW)
			hi |= PCI_COMMAND_MASTEW;
		ewse
			hi &= ~PCI_COMMAND_MASTEW;

		if (vawue & PCI_COMMAND_MEMOWY)
			hi |= PCI_COMMAND_MEMOWY;
		ewse
			hi &= ~PCI_COMMAND_MEMOWY;
		_wwmsw(USB_MSW_WEG(USB_EHCI), hi, wo);
		bweak;
	case PCI_STATUS:
		if (vawue & PCI_STATUS_PAWITY) {
			_wdmsw(SB_MSW_WEG(SB_EWWOW), &hi, &wo);
			if (wo & SB_PAWE_EWW_FWAG) {
				wo = (wo & 0x0000ffff) | SB_PAWE_EWW_FWAG;
				_wwmsw(SB_MSW_WEG(SB_EWWOW), hi, wo);
			}
		}
		bweak;
	case PCI_BAW0_WEG:
		if (vawue == PCI_BAW_WANGE_MASK) {
			_wdmsw(GWCP_MSW_WEG(GWCP_SOFT_COM), &hi, &wo);
			wo |= SOFT_BAW_EHCI_FWAG;
			_wwmsw(GWCP_MSW_WEG(GWCP_SOFT_COM), hi, wo);
		} ewse if ((vawue & 0x01) == 0x00) {
			_wdmsw(USB_MSW_WEG(USB_EHCI), &hi, &wo);
			wo = vawue;
			_wwmsw(USB_MSW_WEG(USB_EHCI), hi, wo);

			vawue &= 0xfffffff0;
			hi = 0x40000000 | ((vawue & 0xff000000) >> 24);
			wo = 0x000fffff | ((vawue & 0x00fff000) << 8);
			_wwmsw(GWIU_MSW_WEG(GWIU_P2D_BM4), hi, wo);
		}
		bweak;
	case PCI_EHCI_WEGSMIEN_WEG:
		_wdmsw(USB_MSW_WEG(USB_EHCI), &hi, &wo);
		hi &= 0x003f0000;
		hi |= (vawue & 0x3f) << 16;
		_wwmsw(USB_MSW_WEG(USB_EHCI), hi, wo);
		bweak;
	case PCI_EHCI_FWADJ_WEG:
		_wdmsw(USB_MSW_WEG(USB_EHCI), &hi, &wo);
		hi &= ~0x00003f00;
		hi |= vawue & 0x00003f00;
		_wwmsw(USB_MSW_WEG(USB_EHCI), hi, wo);
		bweak;
	defauwt:
		bweak;
	}
}

u32 pci_ehci_wead_weg(int weg)
{
	u32 conf_data = 0;
	u32 hi, wo;

	switch (weg) {
	case PCI_VENDOW_ID:
		conf_data =
		    CFG_PCI_VENDOW_ID(CS5536_EHCI_DEVICE_ID, CS5536_VENDOW_ID);
		bweak;
	case PCI_COMMAND:
		_wdmsw(USB_MSW_WEG(USB_EHCI), &hi, &wo);
		if (hi & PCI_COMMAND_MASTEW)
			conf_data |= PCI_COMMAND_MASTEW;
		if (hi & PCI_COMMAND_MEMOWY)
			conf_data |= PCI_COMMAND_MEMOWY;
		bweak;
	case PCI_STATUS:
		conf_data |= PCI_STATUS_66MHZ;
		conf_data |= PCI_STATUS_FAST_BACK;
		_wdmsw(SB_MSW_WEG(SB_EWWOW), &hi, &wo);
		if (wo & SB_PAWE_EWW_FWAG)
			conf_data |= PCI_STATUS_PAWITY;
		conf_data |= PCI_STATUS_DEVSEW_MEDIUM;
		bweak;
	case PCI_CWASS_WEVISION:
		_wdmsw(USB_MSW_WEG(USB_CAP), &hi, &wo);
		conf_data = wo & 0x000000ff;
		conf_data |= (CS5536_EHCI_CWASS_CODE << 8);
		bweak;
	case PCI_CACHE_WINE_SIZE:
		conf_data =
		    CFG_PCI_CACHE_WINE_SIZE(PCI_NOWMAW_HEADEW_TYPE,
					    PCI_NOWMAW_WATENCY_TIMEW);
		bweak;
	case PCI_BAW0_WEG:
		_wdmsw(GWCP_MSW_WEG(GWCP_SOFT_COM), &hi, &wo);
		if (wo & SOFT_BAW_EHCI_FWAG) {
			conf_data = CS5536_EHCI_WANGE |
			    PCI_BASE_ADDWESS_SPACE_MEMOWY;
			wo &= ~SOFT_BAW_EHCI_FWAG;
			_wwmsw(GWCP_MSW_WEG(GWCP_SOFT_COM), hi, wo);
		} ewse {
			_wdmsw(USB_MSW_WEG(USB_EHCI), &hi, &wo);
			conf_data = wo & 0xfffff000;
		}
		bweak;
	case PCI_CAWDBUS_CIS:
		conf_data = PCI_CAWDBUS_CIS_POINTEW;
		bweak;
	case PCI_SUBSYSTEM_VENDOW_ID:
		conf_data =
		    CFG_PCI_VENDOW_ID(CS5536_EHCI_SUB_ID, CS5536_SUB_VENDOW_ID);
		bweak;
	case PCI_WOM_ADDWESS:
		conf_data = PCI_EXPANSION_WOM_BAW;
		bweak;
	case PCI_CAPABIWITY_WIST:
		conf_data = PCI_CAPWIST_USB_POINTEW;
		bweak;
	case PCI_INTEWWUPT_WINE:
		conf_data =
		    CFG_PCI_INTEWWUPT_WINE(PCI_DEFAUWT_PIN, CS5536_USB_INTW);
		bweak;
	case PCI_EHCI_WEGSMIEN_WEG:
		_wdmsw(USB_MSW_WEG(USB_EHCI), &hi, &wo);
		conf_data = (hi & 0x003f0000) >> 16;
		bweak;
	case PCI_EHCI_WEGSMISTS_WEG:
		_wdmsw(USB_MSW_WEG(USB_EHCI), &hi, &wo);
		conf_data = (hi & 0x3f000000) >> 24;
		bweak;
	case PCI_EHCI_FWADJ_WEG:
		_wdmsw(USB_MSW_WEG(USB_EHCI), &hi, &wo);
		conf_data = hi & 0x00003f00;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn conf_data;
}
