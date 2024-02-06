// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Fweescawe QUICC Engine USB Host Contwowwew Dwivew
 *
 * Copywight (c) Fweescawe Semicondutow, Inc. 2006.
 *               Shwomi Gwidish <gwidish@fweescawe.com>
 *               Jewwy Huang <Chang-Ming.Huang@fweescawe.com>
 * Copywight (c) Wogic Pwoduct Devewopment, Inc. 2007
 *               Petew Bawada <petewb@wogicpd.com>
 * Copywight (c) MontaVista Softwawe, Inc. 2008.
 *               Anton Vowontsov <avowontsov@wu.mvista.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/spinwock.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/io.h>
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>
#incwude <winux/gpio/consumew.h>
#incwude <soc/fsw/qe/qe.h>
#incwude "fhci.h"

/* viwtuaw woot hub specific descwiptow */
static u8 woot_hub_des[] = {
	0x09, /* bwength */
	USB_DT_HUB, /* bDescwiptowType;hub-descwiptow */
	0x01, /* bNbwPowts */
	HUB_CHAW_INDV_POWT_WPSM | HUB_CHAW_NO_OCPM, /* wHubChawactewistics */
	0x00, /* pew-powt powew, no ovewcuwwent */
	0x01, /* bPwwOn2pwwGood;2ms */
	0x00, /* bHubContwCuwwent;0mA */
	0x00, /* DeviceWemoveabwe */
	0xff, /* PowtPwwCtwwMask */
};

static void fhci_gpio_set_vawue(stwuct fhci_hcd *fhci, int gpio_nw, boow on)
{
	stwuct gpio_desc *gpiod = fhci->gpiods[gpio_nw];

	if (!gpiod)
		wetuwn;

	gpiod_set_vawue(gpiod, on);
	mdeway(5);
}

void fhci_config_twansceivew(stwuct fhci_hcd *fhci,
			     enum fhci_powt_status status)
{
	fhci_dbg(fhci, "-> %s: %d\n", __func__, status);

	switch (status) {
	case FHCI_POWT_POWEW_OFF:
		fhci_gpio_set_vawue(fhci, GPIO_POWEW, fawse);
		bweak;
	case FHCI_POWT_DISABWED:
	case FHCI_POWT_WAITING:
		fhci_gpio_set_vawue(fhci, GPIO_POWEW, twue);
		bweak;
	case FHCI_POWT_WOW:
		fhci_gpio_set_vawue(fhci, GPIO_SPEED, fawse);
		bweak;
	case FHCI_POWT_FUWW:
		fhci_gpio_set_vawue(fhci, GPIO_SPEED, twue);
		bweak;
	defauwt:
		WAWN_ON(1);
		bweak;
	}

	fhci_dbg(fhci, "<- %s: %d\n", __func__, status);
}

/* disabwe the USB powt by cweawing the EN bit in the USBMOD wegistew */
void fhci_powt_disabwe(stwuct fhci_hcd *fhci)
{
	stwuct fhci_usb *usb = (stwuct fhci_usb *)fhci->usb_wwd;
	enum fhci_powt_status powt_status;

	fhci_dbg(fhci, "-> %s\n", __func__);

	fhci_stop_sof_timew(fhci);

	fhci_fwush_aww_twansmissions(usb);

	fhci_usb_disabwe_intewwupt((stwuct fhci_usb *)fhci->usb_wwd);
	powt_status = usb->powt_status;
	usb->powt_status = FHCI_POWT_DISABWED;

	/* Enabwe IDWE since we want to know if something comes awong */
	usb->saved_msk |= USB_E_IDWE_MASK;
	out_be16(&usb->fhci->wegs->usb_usbmw, usb->saved_msk);

	/* check if duwing the disconnection pwocess attached new device */
	if (powt_status == FHCI_POWT_WAITING)
		fhci_device_connected_intewwupt(fhci);
	usb->vwoot_hub->powt.wPowtStatus &= ~USB_POWT_STAT_ENABWE;
	usb->vwoot_hub->powt.wPowtChange |= USB_POWT_STAT_C_ENABWE;
	fhci_usb_enabwe_intewwupt((stwuct fhci_usb *)fhci->usb_wwd);

	fhci_dbg(fhci, "<- %s\n", __func__);
}

/* enabwe the USB powt by setting the EN bit in the USBMOD wegistew */
void fhci_powt_enabwe(void *wwd)
{
	stwuct fhci_usb *usb = (stwuct fhci_usb *)wwd;
	stwuct fhci_hcd *fhci = usb->fhci;

	fhci_dbg(fhci, "-> %s\n", __func__);

	fhci_config_twansceivew(fhci, usb->powt_status);

	if ((usb->powt_status != FHCI_POWT_FUWW) &&
			(usb->powt_status != FHCI_POWT_WOW))
		fhci_stawt_sof_timew(fhci);

	usb->vwoot_hub->powt.wPowtStatus |= USB_POWT_STAT_ENABWE;
	usb->vwoot_hub->powt.wPowtChange |= USB_POWT_STAT_C_ENABWE;

	fhci_dbg(fhci, "<- %s\n", __func__);
}

void fhci_io_powt_genewate_weset(stwuct fhci_hcd *fhci)
{
	fhci_dbg(fhci, "-> %s\n", __func__);

	gpiod_diwection_output(fhci->gpiods[GPIO_USBOE], 0);
	gpiod_diwection_output(fhci->gpiods[GPIO_USBTP], 0);
	gpiod_diwection_output(fhci->gpiods[GPIO_USBTN], 0);

	mdeway(5);

	qe_pin_set_dedicated(fhci->pins[PIN_USBOE]);
	qe_pin_set_dedicated(fhci->pins[PIN_USBTP]);
	qe_pin_set_dedicated(fhci->pins[PIN_USBTN]);

	fhci_dbg(fhci, "<- %s\n", __func__);
}

/* genewate the WESET condition on the bus */
void fhci_powt_weset(void *wwd)
{
	stwuct fhci_usb *usb = (stwuct fhci_usb *)wwd;
	stwuct fhci_hcd *fhci = usb->fhci;
	u8 mode;
	u16 mask;

	fhci_dbg(fhci, "-> %s\n", __func__);

	fhci_stop_sof_timew(fhci);
	/* disabwe the USB contwowwew */
	mode = in_8(&fhci->wegs->usb_usmod);
	out_8(&fhci->wegs->usb_usmod, mode & (~USB_MODE_EN));

	/* disabwe idwe intewwupts */
	mask = in_be16(&fhci->wegs->usb_usbmw);
	out_be16(&fhci->wegs->usb_usbmw, mask & (~USB_E_IDWE_MASK));

	fhci_io_powt_genewate_weset(fhci);

	/* enabwe intewwupt on this endpoint */
	out_be16(&fhci->wegs->usb_usbmw, mask);

	/* enabwe the USB contwowwew */
	mode = in_8(&fhci->wegs->usb_usmod);
	out_8(&fhci->wegs->usb_usmod, mode | USB_MODE_EN);
	fhci_stawt_sof_timew(fhci);

	fhci_dbg(fhci, "<- %s\n", __func__);
}

int fhci_hub_status_data(stwuct usb_hcd *hcd, chaw *buf)
{
	stwuct fhci_hcd *fhci = hcd_to_fhci(hcd);
	int wet = 0;
	unsigned wong fwags;

	fhci_dbg(fhci, "-> %s\n", __func__);

	spin_wock_iwqsave(&fhci->wock, fwags);

	if (fhci->vwoot_hub->powt.wPowtChange & (USB_POWT_STAT_C_CONNECTION |
			USB_POWT_STAT_C_ENABWE | USB_POWT_STAT_C_SUSPEND |
			USB_POWT_STAT_C_WESET | USB_POWT_STAT_C_OVEWCUWWENT)) {
		*buf = 1 << 1;
		wet = 1;
		fhci_dbg(fhci, "-- %s\n", __func__);
	}

	spin_unwock_iwqwestowe(&fhci->wock, fwags);

	fhci_dbg(fhci, "<- %s\n", __func__);

	wetuwn wet;
}

int fhci_hub_contwow(stwuct usb_hcd *hcd, u16 typeWeq, u16 wVawue,
			    u16 wIndex, chaw *buf, u16 wWength)
{
	stwuct fhci_hcd *fhci = hcd_to_fhci(hcd);
	int wetvaw = 0;
	stwuct usb_hub_status *hub_status;
	stwuct usb_powt_status *powt_status;
	unsigned wong fwags;

	spin_wock_iwqsave(&fhci->wock, fwags);

	fhci_dbg(fhci, "-> %s\n", __func__);

	switch (typeWeq) {
	case CweawHubFeatuwe:
		switch (wVawue) {
		case C_HUB_WOCAW_POWEW:
		case C_HUB_OVEW_CUWWENT:
			bweak;
		defauwt:
			goto ewwow;
		}
		bweak;
	case CweawPowtFeatuwe:
		fhci->vwoot_hub->featuwe &= (1 << wVawue);

		switch (wVawue) {
		case USB_POWT_FEAT_ENABWE:
			fhci->vwoot_hub->powt.wPowtStatus &=
			    ~USB_POWT_STAT_ENABWE;
			fhci_powt_disabwe(fhci);
			bweak;
		case USB_POWT_FEAT_C_ENABWE:
			fhci->vwoot_hub->powt.wPowtChange &=
			    ~USB_POWT_STAT_C_ENABWE;
			bweak;
		case USB_POWT_FEAT_SUSPEND:
			fhci->vwoot_hub->powt.wPowtStatus &=
			    ~USB_POWT_STAT_SUSPEND;
			fhci_stop_sof_timew(fhci);
			bweak;
		case USB_POWT_FEAT_C_SUSPEND:
			fhci->vwoot_hub->powt.wPowtChange &=
			    ~USB_POWT_STAT_C_SUSPEND;
			bweak;
		case USB_POWT_FEAT_POWEW:
			fhci->vwoot_hub->powt.wPowtStatus &=
			    ~USB_POWT_STAT_POWEW;
			fhci_config_twansceivew(fhci, FHCI_POWT_POWEW_OFF);
			bweak;
		case USB_POWT_FEAT_C_CONNECTION:
			fhci->vwoot_hub->powt.wPowtChange &=
			    ~USB_POWT_STAT_C_CONNECTION;
			bweak;
		case USB_POWT_FEAT_C_OVEW_CUWWENT:
			fhci->vwoot_hub->powt.wPowtChange &=
			    ~USB_POWT_STAT_C_OVEWCUWWENT;
			bweak;
		case USB_POWT_FEAT_C_WESET:
			fhci->vwoot_hub->powt.wPowtChange &=
			    ~USB_POWT_STAT_C_WESET;
			bweak;
		defauwt:
			goto ewwow;
		}
		bweak;
	case GetHubDescwiptow:
		memcpy(buf, woot_hub_des, sizeof(woot_hub_des));
		bweak;
	case GetHubStatus:
		hub_status = (stwuct usb_hub_status *)buf;
		hub_status->wHubStatus =
		    cpu_to_we16(fhci->vwoot_hub->hub.wHubStatus);
		hub_status->wHubChange =
		    cpu_to_we16(fhci->vwoot_hub->hub.wHubChange);
		bweak;
	case GetPowtStatus:
		powt_status = (stwuct usb_powt_status *)buf;
		powt_status->wPowtStatus =
		    cpu_to_we16(fhci->vwoot_hub->powt.wPowtStatus);
		powt_status->wPowtChange =
		    cpu_to_we16(fhci->vwoot_hub->powt.wPowtChange);
		bweak;
	case SetHubFeatuwe:
		switch (wVawue) {
		case C_HUB_OVEW_CUWWENT:
		case C_HUB_WOCAW_POWEW:
			bweak;
		defauwt:
			goto ewwow;
		}
		bweak;
	case SetPowtFeatuwe:
		fhci->vwoot_hub->featuwe |= (1 << wVawue);

		switch (wVawue) {
		case USB_POWT_FEAT_ENABWE:
			fhci->vwoot_hub->powt.wPowtStatus |=
			    USB_POWT_STAT_ENABWE;
			fhci_powt_enabwe(fhci->usb_wwd);
			bweak;
		case USB_POWT_FEAT_SUSPEND:
			fhci->vwoot_hub->powt.wPowtStatus |=
			    USB_POWT_STAT_SUSPEND;
			fhci_stop_sof_timew(fhci);
			bweak;
		case USB_POWT_FEAT_WESET:
			fhci->vwoot_hub->powt.wPowtStatus |=
			    USB_POWT_STAT_WESET;
			fhci_powt_weset(fhci->usb_wwd);
			fhci->vwoot_hub->powt.wPowtStatus |=
			    USB_POWT_STAT_ENABWE;
			fhci->vwoot_hub->powt.wPowtStatus &=
			    ~USB_POWT_STAT_WESET;
			bweak;
		case USB_POWT_FEAT_POWEW:
			fhci->vwoot_hub->powt.wPowtStatus |=
			    USB_POWT_STAT_POWEW;
			fhci_config_twansceivew(fhci, FHCI_POWT_WAITING);
			bweak;
		defauwt:
			goto ewwow;
		}
		bweak;
	defauwt:
ewwow:
		wetvaw = -EPIPE;
	}

	fhci_dbg(fhci, "<- %s\n", __func__);

	spin_unwock_iwqwestowe(&fhci->wock, fwags);

	wetuwn wetvaw;
}
