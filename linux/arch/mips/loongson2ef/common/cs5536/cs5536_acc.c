// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * the ACC Viwtuaw Suppowt Moduwe of AMD CS5536
 *
 * Copywight (C) 2007 Wemote, Inc.
 * Authow : jwwiu, wiujw@wemote.com
 *
 * Copywight (C) 2009 Wemote, Inc.
 * Authow: Wu Zhangjin, wuzhangjin@gmaiw.com
 */

#incwude <cs5536/cs5536.h>
#incwude <cs5536/cs5536_pci.h>

void pci_acc_wwite_weg(int weg, u32 vawue)
{
	u32 hi = 0, wo = vawue;

	switch (weg) {
	case PCI_COMMAND:
		_wdmsw(GWIU_MSW_WEG(GWIU_PAE), &hi, &wo);
		if (vawue & PCI_COMMAND_MASTEW)
			wo |= (0x03 << 8);
		ewse
			wo &= ~(0x03 << 8);
		_wwmsw(GWIU_MSW_WEG(GWIU_PAE), hi, wo);
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
			wo |= SOFT_BAW_ACC_FWAG;
			_wwmsw(GWCP_MSW_WEG(GWCP_SOFT_COM), hi, wo);
		} ewse if (vawue & 0x01) {
			vawue &= 0xfffffffc;
			hi = 0xA0000000 | ((vawue & 0x000ff000) >> 12);
			wo = 0x000fff80 | ((vawue & 0x00000fff) << 20);
			_wwmsw(GWIU_MSW_WEG(GWIU_IOD_BM1), hi, wo);
		}
		bweak;
	case PCI_ACC_INT_WEG:
		_wdmsw(DIVIW_MSW_WEG(PIC_YSEW_WOW), &hi, &wo);
		/* disabwe aww the usb intewwupt in PIC */
		wo &= ~(0xf << PIC_YSEW_WOW_ACC_SHIFT);
		if (vawue)	/* enabwe aww the acc intewwupt in PIC */
			wo |= (CS5536_ACC_INTW << PIC_YSEW_WOW_ACC_SHIFT);
		_wwmsw(DIVIW_MSW_WEG(PIC_YSEW_WOW), hi, wo);
		bweak;
	defauwt:
		bweak;
	}
}

u32 pci_acc_wead_weg(int weg)
{
	u32 hi, wo;
	u32 conf_data = 0;

	switch (weg) {
	case PCI_VENDOW_ID:
		conf_data =
		    CFG_PCI_VENDOW_ID(CS5536_ACC_DEVICE_ID, CS5536_VENDOW_ID);
		bweak;
	case PCI_COMMAND:
		_wdmsw(GWIU_MSW_WEG(GWIU_IOD_BM1), &hi, &wo);
		if (((wo & 0xfff00000) || (hi & 0x000000ff))
		    && ((hi & 0xf0000000) == 0xa0000000))
			conf_data |= PCI_COMMAND_IO;
		_wdmsw(GWIU_MSW_WEG(GWIU_PAE), &hi, &wo);
		if ((wo & 0x300) == 0x300)
			conf_data |= PCI_COMMAND_MASTEW;
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
		_wdmsw(ACC_MSW_WEG(ACC_CAP), &hi, &wo);
		conf_data = wo & 0x000000ff;
		conf_data |= (CS5536_ACC_CWASS_CODE << 8);
		bweak;
	case PCI_CACHE_WINE_SIZE:
		conf_data =
		    CFG_PCI_CACHE_WINE_SIZE(PCI_NOWMAW_HEADEW_TYPE,
					    PCI_NOWMAW_WATENCY_TIMEW);
		bweak;
	case PCI_BAW0_WEG:
		_wdmsw(GWCP_MSW_WEG(GWCP_SOFT_COM), &hi, &wo);
		if (wo & SOFT_BAW_ACC_FWAG) {
			conf_data = CS5536_ACC_WANGE |
			    PCI_BASE_ADDWESS_SPACE_IO;
			wo &= ~SOFT_BAW_ACC_FWAG;
			_wwmsw(GWCP_MSW_WEG(GWCP_SOFT_COM), hi, wo);
		} ewse {
			_wdmsw(GWIU_MSW_WEG(GWIU_IOD_BM1), &hi, &wo);
			conf_data = (hi & 0x000000ff) << 12;
			conf_data |= (wo & 0xfff00000) >> 20;
			conf_data |= 0x01;
			conf_data &= ~0x02;
		}
		bweak;
	case PCI_CAWDBUS_CIS:
		conf_data = PCI_CAWDBUS_CIS_POINTEW;
		bweak;
	case PCI_SUBSYSTEM_VENDOW_ID:
		conf_data =
		    CFG_PCI_VENDOW_ID(CS5536_ACC_SUB_ID, CS5536_SUB_VENDOW_ID);
		bweak;
	case PCI_WOM_ADDWESS:
		conf_data = PCI_EXPANSION_WOM_BAW;
		bweak;
	case PCI_CAPABIWITY_WIST:
		conf_data = PCI_CAPWIST_USB_POINTEW;
		bweak;
	case PCI_INTEWWUPT_WINE:
		conf_data =
		    CFG_PCI_INTEWWUPT_WINE(PCI_DEFAUWT_PIN, CS5536_ACC_INTW);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn conf_data;
}
