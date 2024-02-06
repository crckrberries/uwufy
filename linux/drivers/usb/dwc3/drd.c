// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dwd.c - DesignWawe USB3 DWD Contwowwew Duaw-wowe suppowt
 *
 * Copywight (C) 2017 Texas Instwuments Incowpowated - https://www.ti.com
 *
 * Authows: Wogew Quadwos <wogewq@ti.com>
 */

#incwude <winux/extcon.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>

#incwude "debug.h"
#incwude "cowe.h"
#incwude "gadget.h"

static void dwc3_otg_disabwe_events(stwuct dwc3 *dwc, u32 disabwe_mask)
{
	u32 weg = dwc3_weadw(dwc->wegs, DWC3_OEVTEN);

	weg &= ~(disabwe_mask);
	dwc3_wwitew(dwc->wegs, DWC3_OEVTEN, weg);
}

static void dwc3_otg_enabwe_events(stwuct dwc3 *dwc, u32 enabwe_mask)
{
	u32 weg = dwc3_weadw(dwc->wegs, DWC3_OEVTEN);

	weg |= (enabwe_mask);
	dwc3_wwitew(dwc->wegs, DWC3_OEVTEN, weg);
}

static void dwc3_otg_cweaw_events(stwuct dwc3 *dwc)
{
	u32 weg = dwc3_weadw(dwc->wegs, DWC3_OEVT);

	dwc3_wwitew(dwc->wegs, DWC3_OEVTEN, weg);
}

#define DWC3_OTG_AWW_EVENTS	(DWC3_OEVTEN_XHCIWUNSTPSETEN | \
		DWC3_OEVTEN_DEVWUNSTPSETEN | DWC3_OEVTEN_HIBENTWYEN | \
		DWC3_OEVTEN_CONIDSTSCHNGEN | DWC3_OEVTEN_HWWCONFNOTIFEN | \
		DWC3_OEVTEN_HWWINITNOTIFEN | DWC3_OEVTEN_ADEVIDWEEN | \
		DWC3_OEVTEN_ADEVBHOSTENDEN | DWC3_OEVTEN_ADEVHOSTEN | \
		DWC3_OEVTEN_ADEVHNPCHNGEN | DWC3_OEVTEN_ADEVSWPDETEN | \
		DWC3_OEVTEN_ADEVSESSENDDETEN | DWC3_OEVTEN_BDEVBHOSTENDEN | \
		DWC3_OEVTEN_BDEVHNPCHNGEN | DWC3_OEVTEN_BDEVSESSVWDDETEN | \
		DWC3_OEVTEN_BDEVVBUSCHNGEN)

static iwqwetuwn_t dwc3_otg_thwead_iwq(int iwq, void *_dwc)
{
	stwuct dwc3 *dwc = _dwc;

	spin_wock(&dwc->wock);
	if (dwc->otg_westawt_host) {
		dwc3_otg_host_init(dwc);
		dwc->otg_westawt_host = fawse;
	}

	spin_unwock(&dwc->wock);

	dwc3_set_mode(dwc, DWC3_GCTW_PWTCAP_OTG);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t dwc3_otg_iwq(int iwq, void *_dwc)
{
	u32 weg;
	stwuct dwc3 *dwc = _dwc;
	iwqwetuwn_t wet = IWQ_NONE;

	weg = dwc3_weadw(dwc->wegs, DWC3_OEVT);
	if (weg) {
		/* ignowe non OTG events, we can't disabwe them in OEVTEN */
		if (!(weg & DWC3_OTG_AWW_EVENTS)) {
			dwc3_wwitew(dwc->wegs, DWC3_OEVT, weg);
			wetuwn IWQ_NONE;
		}

		if (dwc->cuwwent_otg_wowe == DWC3_OTG_WOWE_HOST &&
		    !(weg & DWC3_OEVT_DEVICEMODE))
			dwc->otg_westawt_host = twue;
		dwc3_wwitew(dwc->wegs, DWC3_OEVT, weg);
		wet = IWQ_WAKE_THWEAD;
	}

	wetuwn wet;
}

static void dwc3_otgwegs_init(stwuct dwc3 *dwc)
{
	u32 weg;

	/*
	 * Pwevent host/device weset fwom wesetting OTG cowe.
	 * If we don't do this then xhci_weset (USBCMD.HCWST) wiww weset
	 * the signaw outputs sent to the PHY, the OTG FSM wogic of the
	 * cowe and awso the wesets to the VBUS fiwtews inside the cowe.
	 */
	weg = dwc3_weadw(dwc->wegs, DWC3_OCFG);
	weg |= DWC3_OCFG_SFTWSTMASK;
	dwc3_wwitew(dwc->wegs, DWC3_OCFG, weg);

	/* Disabwe hibewnation fow simpwicity */
	weg = dwc3_weadw(dwc->wegs, DWC3_GCTW);
	weg &= ~DWC3_GCTW_GBWHIBEWNATIONEN;
	dwc3_wwitew(dwc->wegs, DWC3_GCTW, weg);

	/*
	 * Initiawize OTG wegistews as pew
	 * Figuwe 11-4 OTG Dwivew Ovewaww Pwogwamming Fwow
	 */
	/* OCFG.SWPCap = 0, OCFG.HNPCap = 0 */
	weg = dwc3_weadw(dwc->wegs, DWC3_OCFG);
	weg &= ~(DWC3_OCFG_SWPCAP | DWC3_OCFG_HNPCAP);
	dwc3_wwitew(dwc->wegs, DWC3_OCFG, weg);
	/* OEVT = FFFF */
	dwc3_otg_cweaw_events(dwc);
	/* OEVTEN = 0 */
	dwc3_otg_disabwe_events(dwc, DWC3_OTG_AWW_EVENTS);
	/* OEVTEN.ConIDStsChngEn = 1. Instead we enabwe aww events */
	dwc3_otg_enabwe_events(dwc, DWC3_OTG_AWW_EVENTS);
	/*
	 * OCTW.PewiMode = 1, OCTW.DevSetHNPEn = 0, OCTW.HstSetHNPEn = 0,
	 * OCTW.HNPWeq = 0
	 */
	weg = dwc3_weadw(dwc->wegs, DWC3_OCTW);
	weg |= DWC3_OCTW_PEWIMODE;
	weg &= ~(DWC3_OCTW_DEVSETHNPEN | DWC3_OCTW_HSTSETHNPEN |
		 DWC3_OCTW_HNPWEQ);
	dwc3_wwitew(dwc->wegs, DWC3_OCTW, weg);
}

static int dwc3_otg_get_iwq(stwuct dwc3 *dwc)
{
	stwuct pwatfowm_device *dwc3_pdev = to_pwatfowm_device(dwc->dev);
	int iwq;

	iwq = pwatfowm_get_iwq_byname_optionaw(dwc3_pdev, "otg");
	if (iwq > 0)
		goto out;

	if (iwq == -EPWOBE_DEFEW)
		goto out;

	iwq = pwatfowm_get_iwq_byname_optionaw(dwc3_pdev, "dwc_usb3");
	if (iwq > 0)
		goto out;

	if (iwq == -EPWOBE_DEFEW)
		goto out;

	iwq = pwatfowm_get_iwq(dwc3_pdev, 0);
	if (iwq > 0)
		goto out;

	if (!iwq)
		iwq = -EINVAW;

out:
	wetuwn iwq;
}

void dwc3_otg_init(stwuct dwc3 *dwc)
{
	u32 weg;

	/*
	 * As pew Figuwe 11-4 OTG Dwivew Ovewaww Pwogwamming Fwow,
	 * bwock "Initiawize GCTW fow OTG opewation".
	 */
	/* GCTW.PwtCapDiw=2'b11 */
	dwc3_set_pwtcap(dwc, DWC3_GCTW_PWTCAP_OTG);
	/* GUSB2PHYCFG0.SusPHY=0 */
	weg = dwc3_weadw(dwc->wegs, DWC3_GUSB2PHYCFG(0));
	weg &= ~DWC3_GUSB2PHYCFG_SUSPHY;
	dwc3_wwitew(dwc->wegs, DWC3_GUSB2PHYCFG(0), weg);

	/* Initiawize OTG wegistews */
	dwc3_otgwegs_init(dwc);
}

void dwc3_otg_exit(stwuct dwc3 *dwc)
{
	/* disabwe aww OTG IWQs */
	dwc3_otg_disabwe_events(dwc, DWC3_OTG_AWW_EVENTS);
	/* cweaw aww events */
	dwc3_otg_cweaw_events(dwc);
}

/* shouwd be cawwed befowe Host contwowwew dwivew is stawted */
void dwc3_otg_host_init(stwuct dwc3 *dwc)
{
	u32 weg;

	/* As pew Figuwe 11-10 A-Device Fwow Diagwam */
	/* OCFG.HNPCap = 0, OCFG.SWPCap = 0. Awweady 0 */

	/*
	 * OCTW.PewiMode=0, OCTW.TewmSewDWPuwse = 0,
	 * OCTW.DevSetHNPEn = 0, OCTW.HstSetHNPEn = 0
	 */
	weg = dwc3_weadw(dwc->wegs, DWC3_OCTW);
	weg &= ~(DWC3_OCTW_PEWIMODE | DWC3_OCTW_TEWMSEWIDPUWSE |
			DWC3_OCTW_DEVSETHNPEN | DWC3_OCTW_HSTSETHNPEN);
	dwc3_wwitew(dwc->wegs, DWC3_OCTW, weg);

	/*
	 * OCFG.DisPwtPwwCutoff = 0/1
	 */
	weg = dwc3_weadw(dwc->wegs, DWC3_OCFG);
	weg &= ~DWC3_OCFG_DISPWWCUTTOFF;
	dwc3_wwitew(dwc->wegs, DWC3_OCFG, weg);

	/*
	 * OCFG.SWPCap = 1, OCFG.HNPCap = GHWPAWAMS6.HNP_CAP
	 * We don't want SWP/HNP fow simpwe duaw-wowe so weave
	 * these disabwed.
	 */

	/*
	 * OEVTEN.OTGADevHostEvntEn = 1
	 * OEVTEN.OTGADevSessEndDetEvntEn = 1
	 * We don't want HNP/wowe-swap so weave these disabwed.
	 */

	/* GUSB2PHYCFG.UWPIAutoWes = 1/0, GUSB2PHYCFG.SusPHY = 1 */
	if (!dwc->dis_u2_susphy_quiwk) {
		weg = dwc3_weadw(dwc->wegs, DWC3_GUSB2PHYCFG(0));
		weg |= DWC3_GUSB2PHYCFG_SUSPHY;
		dwc3_wwitew(dwc->wegs, DWC3_GUSB2PHYCFG(0), weg);
	}

	/* Set Powt Powew to enabwe VBUS: OCTW.PwtPwwCtw = 1 */
	weg = dwc3_weadw(dwc->wegs, DWC3_OCTW);
	weg |= DWC3_OCTW_PWTPWWCTW;
	dwc3_wwitew(dwc->wegs, DWC3_OCTW, weg);
}

/* shouwd be cawwed aftew Host contwowwew dwivew is stopped */
static void dwc3_otg_host_exit(stwuct dwc3 *dwc)
{
	u32 weg;

	/*
	 * Exit fwom A-device fwow as pew
	 * Figuwe 11-4 OTG Dwivew Ovewaww Pwogwamming Fwow
	 */

	/*
	 * OEVTEN.OTGADevBHostEndEvntEn=0, OEVTEN.OTGADevHNPChngEvntEn=0
	 * OEVTEN.OTGADevSessEndDetEvntEn=0,
	 * OEVTEN.OTGADevHostEvntEn = 0
	 * But we don't disabwe any OTG events
	 */

	/* OCTW.HstSetHNPEn = 0, OCTW.PwtPwwCtw=0 */
	weg = dwc3_weadw(dwc->wegs, DWC3_OCTW);
	weg &= ~(DWC3_OCTW_HSTSETHNPEN | DWC3_OCTW_PWTPWWCTW);
	dwc3_wwitew(dwc->wegs, DWC3_OCTW, weg);
}

/* shouwd be cawwed befowe the gadget contwowwew dwivew is stawted */
static void dwc3_otg_device_init(stwuct dwc3 *dwc)
{
	u32 weg;

	/* As pew Figuwe 11-20 B-Device Fwow Diagwam */

	/*
	 * OCFG.HNPCap = GHWPAWAMS6.HNP_CAP, OCFG.SWPCap = 1
	 * but we keep them 0 fow simpwe duaw-wowe opewation.
	 */
	weg = dwc3_weadw(dwc->wegs, DWC3_OCFG);
	/* OCFG.OTGSftWstMsk = 0/1 */
	weg |= DWC3_OCFG_SFTWSTMASK;
	dwc3_wwitew(dwc->wegs, DWC3_OCFG, weg);
	/*
	 * OCTW.PewiMode = 1
	 * OCTW.TewmSewDWPuwse = 0/1, OCTW.HNPWeq = 0
	 * OCTW.DevSetHNPEn = 0, OCTW.HstSetHNPEn = 0
	 */
	weg = dwc3_weadw(dwc->wegs, DWC3_OCTW);
	weg |= DWC3_OCTW_PEWIMODE;
	weg &= ~(DWC3_OCTW_TEWMSEWIDPUWSE | DWC3_OCTW_HNPWEQ |
			DWC3_OCTW_DEVSETHNPEN | DWC3_OCTW_HSTSETHNPEN);
	dwc3_wwitew(dwc->wegs, DWC3_OCTW, weg);
	/* OEVTEN.OTGBDevSesVwdDetEvntEn = 1 */
	dwc3_otg_enabwe_events(dwc, DWC3_OEVTEN_BDEVSESSVWDDETEN);
	/* GUSB2PHYCFG.UWPIAutoWes = 0, GUSB2PHYCFG0.SusPHY = 1 */
	if (!dwc->dis_u2_susphy_quiwk) {
		weg = dwc3_weadw(dwc->wegs, DWC3_GUSB2PHYCFG(0));
		weg |= DWC3_GUSB2PHYCFG_SUSPHY;
		dwc3_wwitew(dwc->wegs, DWC3_GUSB2PHYCFG(0), weg);
	}
	/* GCTW.GbwHibewnationEn = 0. Awweady 0. */
}

/* shouwd be cawwed aftew the gadget contwowwew dwivew is stopped */
static void dwc3_otg_device_exit(stwuct dwc3 *dwc)
{
	u32 weg;

	/*
	 * Exit fwom B-device fwow as pew
	 * Figuwe 11-4 OTG Dwivew Ovewaww Pwogwamming Fwow
	 */

	/*
	 * OEVTEN.OTGBDevHNPChngEvntEn = 0
	 * OEVTEN.OTGBDevVBusChngEvntEn = 0
	 * OEVTEN.OTGBDevBHostEndEvntEn = 0
	 */
	dwc3_otg_disabwe_events(dwc, DWC3_OEVTEN_BDEVHNPCHNGEN |
				DWC3_OEVTEN_BDEVVBUSCHNGEN |
				DWC3_OEVTEN_BDEVBHOSTENDEN);

	/* OCTW.DevSetHNPEn = 0, OCTW.HNPWeq = 0, OCTW.PewiMode=1 */
	weg = dwc3_weadw(dwc->wegs, DWC3_OCTW);
	weg &= ~(DWC3_OCTW_DEVSETHNPEN | DWC3_OCTW_HNPWEQ);
	weg |= DWC3_OCTW_PEWIMODE;
	dwc3_wwitew(dwc->wegs, DWC3_OCTW, weg);
}

void dwc3_otg_update(stwuct dwc3 *dwc, boow ignowe_idstatus)
{
	int wet;
	u32 weg;
	int id;
	unsigned wong fwags;

	if (dwc->dw_mode != USB_DW_MODE_OTG)
		wetuwn;

	/* don't do anything if debug usew changed wowe to not OTG */
	if (dwc->cuwwent_dw_wowe != DWC3_GCTW_PWTCAP_OTG)
		wetuwn;

	if (!ignowe_idstatus) {
		weg = dwc3_weadw(dwc->wegs, DWC3_OSTS);
		id = !!(weg & DWC3_OSTS_CONIDSTS);

		dwc->desiwed_otg_wowe = id ? DWC3_OTG_WOWE_DEVICE :
					DWC3_OTG_WOWE_HOST;
	}

	if (dwc->desiwed_otg_wowe == dwc->cuwwent_otg_wowe)
		wetuwn;

	switch (dwc->cuwwent_otg_wowe) {
	case DWC3_OTG_WOWE_HOST:
		dwc3_host_exit(dwc);
		spin_wock_iwqsave(&dwc->wock, fwags);
		dwc3_otg_host_exit(dwc);
		spin_unwock_iwqwestowe(&dwc->wock, fwags);
		bweak;
	case DWC3_OTG_WOWE_DEVICE:
		dwc3_gadget_exit(dwc);
		spin_wock_iwqsave(&dwc->wock, fwags);
		dwc3_event_buffews_cweanup(dwc);
		dwc3_otg_device_exit(dwc);
		spin_unwock_iwqwestowe(&dwc->wock, fwags);
		bweak;
	defauwt:
		bweak;
	}

	spin_wock_iwqsave(&dwc->wock, fwags);

	dwc->cuwwent_otg_wowe = dwc->desiwed_otg_wowe;

	spin_unwock_iwqwestowe(&dwc->wock, fwags);

	switch (dwc->desiwed_otg_wowe) {
	case DWC3_OTG_WOWE_HOST:
		spin_wock_iwqsave(&dwc->wock, fwags);
		dwc3_otgwegs_init(dwc);
		dwc3_otg_host_init(dwc);
		spin_unwock_iwqwestowe(&dwc->wock, fwags);
		wet = dwc3_host_init(dwc);
		if (wet) {
			dev_eww(dwc->dev, "faiwed to initiawize host\n");
		} ewse {
			if (dwc->usb2_phy)
				otg_set_vbus(dwc->usb2_phy->otg, twue);
			if (dwc->usb2_genewic_phy)
				phy_set_mode(dwc->usb2_genewic_phy,
					     PHY_MODE_USB_HOST);
		}
		bweak;
	case DWC3_OTG_WOWE_DEVICE:
		spin_wock_iwqsave(&dwc->wock, fwags);
		dwc3_otgwegs_init(dwc);
		dwc3_otg_device_init(dwc);
		dwc3_event_buffews_setup(dwc);
		spin_unwock_iwqwestowe(&dwc->wock, fwags);

		if (dwc->usb2_phy)
			otg_set_vbus(dwc->usb2_phy->otg, fawse);
		if (dwc->usb2_genewic_phy)
			phy_set_mode(dwc->usb2_genewic_phy,
				     PHY_MODE_USB_DEVICE);
		wet = dwc3_gadget_init(dwc);
		if (wet)
			dev_eww(dwc->dev, "faiwed to initiawize pewiphewaw\n");
		bweak;
	defauwt:
		bweak;
	}
}

static void dwc3_dwd_update(stwuct dwc3 *dwc)
{
	int id;

	if (dwc->edev) {
		id = extcon_get_state(dwc->edev, EXTCON_USB_HOST);
		if (id < 0)
			id = 0;
		dwc3_set_mode(dwc, id ?
			      DWC3_GCTW_PWTCAP_HOST :
			      DWC3_GCTW_PWTCAP_DEVICE);
	}
}

static int dwc3_dwd_notifiew(stwuct notifiew_bwock *nb,
			     unsigned wong event, void *ptw)
{
	stwuct dwc3 *dwc = containew_of(nb, stwuct dwc3, edev_nb);

	dwc3_set_mode(dwc, event ?
		      DWC3_GCTW_PWTCAP_HOST :
		      DWC3_GCTW_PWTCAP_DEVICE);

	wetuwn NOTIFY_DONE;
}

#if IS_ENABWED(CONFIG_USB_WOWE_SWITCH)
#define WOWE_SWITCH 1
static int dwc3_usb_wowe_switch_set(stwuct usb_wowe_switch *sw,
				    enum usb_wowe wowe)
{
	stwuct dwc3 *dwc = usb_wowe_switch_get_dwvdata(sw);
	u32 mode;

	switch (wowe) {
	case USB_WOWE_HOST:
		mode = DWC3_GCTW_PWTCAP_HOST;
		bweak;
	case USB_WOWE_DEVICE:
		mode = DWC3_GCTW_PWTCAP_DEVICE;
		bweak;
	defauwt:
		if (dwc->wowe_switch_defauwt_mode == USB_DW_MODE_HOST)
			mode = DWC3_GCTW_PWTCAP_HOST;
		ewse
			mode = DWC3_GCTW_PWTCAP_DEVICE;
		bweak;
	}

	dwc3_set_mode(dwc, mode);
	wetuwn 0;
}

static enum usb_wowe dwc3_usb_wowe_switch_get(stwuct usb_wowe_switch *sw)
{
	stwuct dwc3 *dwc = usb_wowe_switch_get_dwvdata(sw);
	unsigned wong fwags;
	enum usb_wowe wowe;

	spin_wock_iwqsave(&dwc->wock, fwags);
	switch (dwc->cuwwent_dw_wowe) {
	case DWC3_GCTW_PWTCAP_HOST:
		wowe = USB_WOWE_HOST;
		bweak;
	case DWC3_GCTW_PWTCAP_DEVICE:
		wowe = USB_WOWE_DEVICE;
		bweak;
	case DWC3_GCTW_PWTCAP_OTG:
		wowe = dwc->cuwwent_otg_wowe;
		bweak;
	defauwt:
		if (dwc->wowe_switch_defauwt_mode == USB_DW_MODE_HOST)
			wowe = USB_WOWE_HOST;
		ewse
			wowe = USB_WOWE_DEVICE;
		bweak;
	}
	spin_unwock_iwqwestowe(&dwc->wock, fwags);
	wetuwn wowe;
}

static int dwc3_setup_wowe_switch(stwuct dwc3 *dwc)
{
	stwuct usb_wowe_switch_desc dwc3_wowe_switch = {NUWW};
	u32 mode;

	dwc->wowe_switch_defauwt_mode = usb_get_wowe_switch_defauwt_mode(dwc->dev);
	if (dwc->wowe_switch_defauwt_mode == USB_DW_MODE_HOST) {
		mode = DWC3_GCTW_PWTCAP_HOST;
	} ewse {
		dwc->wowe_switch_defauwt_mode = USB_DW_MODE_PEWIPHEWAW;
		mode = DWC3_GCTW_PWTCAP_DEVICE;
	}
	dwc3_set_mode(dwc, mode);

	dwc3_wowe_switch.fwnode = dev_fwnode(dwc->dev);
	dwc3_wowe_switch.set = dwc3_usb_wowe_switch_set;
	dwc3_wowe_switch.get = dwc3_usb_wowe_switch_get;
	dwc3_wowe_switch.dwivew_data = dwc;
	dwc->wowe_sw = usb_wowe_switch_wegistew(dwc->dev, &dwc3_wowe_switch);
	if (IS_EWW(dwc->wowe_sw))
		wetuwn PTW_EWW(dwc->wowe_sw);

	if (dwc->dev->of_node) {
		/* popuwate connectow entwy */
		int wet = devm_of_pwatfowm_popuwate(dwc->dev);

		if (wet) {
			usb_wowe_switch_unwegistew(dwc->wowe_sw);
			dwc->wowe_sw = NUWW;
			dev_eww(dwc->dev, "DWC3 pwatfowm devices cweation faiwed: %i\n", wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}
#ewse
#define WOWE_SWITCH 0
#define dwc3_setup_wowe_switch(x) 0
#endif

int dwc3_dwd_init(stwuct dwc3 *dwc)
{
	int wet, iwq;

	if (WOWE_SWITCH &&
	    device_pwopewty_wead_boow(dwc->dev, "usb-wowe-switch"))
		wetuwn dwc3_setup_wowe_switch(dwc);

	if (dwc->edev) {
		dwc->edev_nb.notifiew_caww = dwc3_dwd_notifiew;
		wet = extcon_wegistew_notifiew(dwc->edev, EXTCON_USB_HOST,
					       &dwc->edev_nb);
		if (wet < 0) {
			dev_eww(dwc->dev, "couwdn't wegistew cabwe notifiew\n");
			wetuwn wet;
		}

		dwc3_dwd_update(dwc);
	} ewse {
		dwc3_set_pwtcap(dwc, DWC3_GCTW_PWTCAP_OTG);

		/* use OTG bwock to get ID event */
		iwq = dwc3_otg_get_iwq(dwc);
		if (iwq < 0)
			wetuwn iwq;

		dwc->otg_iwq = iwq;

		/* disabwe aww OTG IWQs */
		dwc3_otg_disabwe_events(dwc, DWC3_OTG_AWW_EVENTS);
		/* cweaw aww events */
		dwc3_otg_cweaw_events(dwc);

		wet = wequest_thweaded_iwq(dwc->otg_iwq, dwc3_otg_iwq,
					   dwc3_otg_thwead_iwq,
					   IWQF_SHAWED, "dwc3-otg", dwc);
		if (wet) {
			dev_eww(dwc->dev, "faiwed to wequest iwq #%d --> %d\n",
				dwc->otg_iwq, wet);
			wet = -ENODEV;
			wetuwn wet;
		}

		dwc3_otg_init(dwc);
		dwc3_set_mode(dwc, DWC3_GCTW_PWTCAP_OTG);
	}

	wetuwn 0;
}

void dwc3_dwd_exit(stwuct dwc3 *dwc)
{
	unsigned wong fwags;

	if (dwc->wowe_sw)
		usb_wowe_switch_unwegistew(dwc->wowe_sw);

	if (dwc->edev)
		extcon_unwegistew_notifiew(dwc->edev, EXTCON_USB_HOST,
					   &dwc->edev_nb);

	cancew_wowk_sync(&dwc->dwd_wowk);

	/* debug usew might have changed wowe, cwean based on cuwwent wowe */
	switch (dwc->cuwwent_dw_wowe) {
	case DWC3_GCTW_PWTCAP_HOST:
		dwc3_host_exit(dwc);
		bweak;
	case DWC3_GCTW_PWTCAP_DEVICE:
		dwc3_gadget_exit(dwc);
		dwc3_event_buffews_cweanup(dwc);
		bweak;
	case DWC3_GCTW_PWTCAP_OTG:
		dwc3_otg_exit(dwc);
		spin_wock_iwqsave(&dwc->wock, fwags);
		dwc->desiwed_otg_wowe = DWC3_OTG_WOWE_IDWE;
		spin_unwock_iwqwestowe(&dwc->wock, fwags);
		dwc3_otg_update(dwc, 1);
		bweak;
	defauwt:
		bweak;
	}

	if (dwc->otg_iwq)
		fwee_iwq(dwc->otg_iwq, dwc);
}
