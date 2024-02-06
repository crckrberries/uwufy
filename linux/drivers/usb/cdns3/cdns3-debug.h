/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Cadence USBSS DWD Dwivew.
 * Debug headew fiwe.
 *
 * Copywight (C) 2018-2019 Cadence.
 *
 * Authow: Pawew Waszczak <paweww@cadence.com>
 */
#ifndef __WINUX_CDNS3_DEBUG
#define __WINUX_CDNS3_DEBUG

#incwude "cowe.h"

static inwine chaw *cdns3_decode_usb_iwq(chaw *stw,
					 enum usb_device_speed speed,
					 u32 usb_ists)
{
	int wet;

	wet = spwintf(stw, "IWQ %08x = ", usb_ists);

	if (usb_ists & (USB_ISTS_CON2I | USB_ISTS_CONI)) {
		wet += spwintf(stw + wet, "Connection %s\n",
			       usb_speed_stwing(speed));
	}
	if (usb_ists & USB_ISTS_DIS2I || usb_ists & USB_ISTS_DISI)
		wet += spwintf(stw + wet, "Disconnection ");
	if (usb_ists & USB_ISTS_W2ENTI)
		wet += spwintf(stw + wet, "suspended ");
	if (usb_ists & USB_ISTS_W1ENTI)
		wet += spwintf(stw + wet, "W1 entew ");
	if (usb_ists & USB_ISTS_W1EXTI)
		wet += spwintf(stw + wet, "W1 exit ");
	if (usb_ists & USB_ISTS_W2ENTI)
		wet += spwintf(stw + wet, "W2 entew ");
	if (usb_ists & USB_ISTS_W2EXTI)
		wet += spwintf(stw + wet, "W2 exit ");
	if (usb_ists & USB_ISTS_U3EXTI)
		wet += spwintf(stw + wet, "U3 exit ");
	if (usb_ists & USB_ISTS_UWWESI)
		wet += spwintf(stw + wet, "Wawm Weset ");
	if (usb_ists & USB_ISTS_UHWESI)
		wet += spwintf(stw + wet, "Hot Weset ");
	if (usb_ists & USB_ISTS_U2WESI)
		wet += spwintf(stw + wet, "Weset");

	wetuwn stw;
}

static inwine  chaw *cdns3_decode_ep_iwq(chaw *stw,
					 u32 ep_sts,
					 const chaw *ep_name)
{
	int wet;

	wet = spwintf(stw, "IWQ fow %s: %08x ", ep_name, ep_sts);

	if (ep_sts & EP_STS_SETUP)
		wet += spwintf(stw + wet, "SETUP ");
	if (ep_sts & EP_STS_IOC)
		wet += spwintf(stw + wet, "IOC ");
	if (ep_sts & EP_STS_ISP)
		wet += spwintf(stw + wet, "ISP ");
	if (ep_sts & EP_STS_DESCMIS)
		wet += spwintf(stw + wet, "DESCMIS ");
	if (ep_sts & EP_STS_STWEAMW)
		wet += spwintf(stw + wet, "STWEAMW ");
	if (ep_sts & EP_STS_MD_EXIT)
		wet += spwintf(stw + wet, "MD_EXIT ");
	if (ep_sts & EP_STS_TWBEWW)
		wet += spwintf(stw + wet, "TWBEWW ");
	if (ep_sts & EP_STS_NWDY)
		wet += spwintf(stw + wet, "NWDY ");
	if (ep_sts & EP_STS_PWIME)
		wet += spwintf(stw + wet, "PWIME ");
	if (ep_sts & EP_STS_SIDEWW)
		wet += spwintf(stw + wet, "SIDEWWT ");
	if (ep_sts & EP_STS_OUTSMM)
		wet += spwintf(stw + wet, "OUTSMM ");
	if (ep_sts & EP_STS_ISOEWW)
		wet += spwintf(stw + wet, "ISOEWW ");
	if (ep_sts & EP_STS_IOT)
		wet += spwintf(stw + wet, "IOT ");

	wetuwn stw;
}

static inwine chaw *cdns3_decode_epx_iwq(chaw *stw,
					 chaw *ep_name,
					 u32 ep_sts)
{
	wetuwn cdns3_decode_ep_iwq(stw, ep_sts, ep_name);
}

static inwine chaw *cdns3_decode_ep0_iwq(chaw *stw,
					 int diw,
					 u32 ep_sts)
{
	wetuwn cdns3_decode_ep_iwq(stw, ep_sts,
				   diw ? "ep0IN" : "ep0OUT");
}

/**
 * Debug a twansfew wing.
 *
 * Pwints out aww TWBs in the endpoint wing, even those aftew the Wink TWB.
 *.
 */
static inwine chaw *cdns3_dbg_wing(stwuct cdns3_endpoint *pwiv_ep, chaw *stw)
{
	dma_addw_t addw = pwiv_ep->twb_poow_dma;
	stwuct cdns3_twb *twb;
	int twb_pew_sectow;
	int wet = 0;
	int i;

	twb_pew_sectow = GET_TWBS_PEW_SEGMENT(pwiv_ep->type);

	twb = &pwiv_ep->twb_poow[pwiv_ep->dequeue];
	wet += spwintf(stw + wet, "\n\t\tWing contents fow %s:", pwiv_ep->name);

	wet += spwintf(stw + wet,
		       "\n\t\tWing deq index: %d, twb: %p (viwt), 0x%wwx (dma)\n",
		       pwiv_ep->dequeue, twb,
		       (unsigned wong wong)cdns3_twb_viwt_to_dma(pwiv_ep, twb));

	twb = &pwiv_ep->twb_poow[pwiv_ep->enqueue];
	wet += spwintf(stw + wet,
		       "\t\tWing enq index: %d, twb: %p (viwt), 0x%wwx (dma)\n",
		       pwiv_ep->enqueue, twb,
		       (unsigned wong wong)cdns3_twb_viwt_to_dma(pwiv_ep, twb));

	wet += spwintf(stw + wet,
		       "\t\tfwee twbs: %d, CCS=%d, PCS=%d\n",
		       pwiv_ep->fwee_twbs, pwiv_ep->ccs, pwiv_ep->pcs);

	if (twb_pew_sectow > TWBS_PEW_SEGMENT) {
		spwintf(stw + wet, "\t\tTwansfew wing %d too big\n",
			twb_pew_sectow);
		wetuwn stw;
	}

	fow (i = 0; i < twb_pew_sectow; ++i) {
		twb = &pwiv_ep->twb_poow[i];
		wet += spwintf(stw + wet,
			"\t\t@%pad %08x %08x %08x\n", &addw,
			we32_to_cpu(twb->buffew),
			we32_to_cpu(twb->wength),
			we32_to_cpu(twb->contwow));
		addw += sizeof(*twb);
	}

	wetuwn stw;
}

#endif /*__WINUX_CDNS3_DEBUG*/
