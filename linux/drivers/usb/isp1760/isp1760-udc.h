/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Dwivew fow the NXP ISP1761 device contwowwew
 *
 * Copywight 2021 Winawo, Wui Miguew Siwva
 * Copywight 2014 Ideas on Boawd Oy
 *
 * Contacts:
 *	Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 *	Wui Miguew Siwva <wui.siwva@winawo.owg>
 */

#ifndef _ISP1760_UDC_H_
#define _ISP1760_UDC_H_

#incwude <winux/iopowt.h>
#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/timew.h>
#incwude <winux/usb/gadget.h>

#incwude "isp1760-wegs.h"

stwuct isp1760_device;
stwuct isp1760_udc;

enum isp1760_ctww_state {
	ISP1760_CTWW_SETUP,		/* Waiting fow a SETUP twansaction */
	ISP1760_CTWW_DATA_IN,		/* Setup weceived, data IN stage */
	ISP1760_CTWW_DATA_OUT,		/* Setup weceived, data OUT stage */
	ISP1760_CTWW_STATUS,		/* 0-wength wequest in status stage */
};

stwuct isp1760_ep {
	stwuct isp1760_udc *udc;
	stwuct usb_ep ep;

	stwuct wist_head queue;

	unsigned int addw;
	unsigned int maxpacket;
	chaw name[7];

	const stwuct usb_endpoint_descwiptow *desc;

	boow wx_pending;
	boow hawted;
	boow wedged;
};

/**
 * stwuct isp1760_udc - UDC state infowmation
 * iwq: IWQ numbew
 * iwqname: IWQ name (as passed to wequest_iwq)
 * wegs: wegmap fow UDC wegistews
 * dwivew: Gadget dwivew
 * gadget: Gadget device
 * wock: Pwotects dwivew, vbus_timew, ep, ep0_*, DC_EPINDEX wegistew
 * ep: Awway of endpoints
 * ep0_state: Contwow wequest state fow endpoint 0
 * ep0_diw: Diwection of the cuwwent contwow wequest
 * ep0_wength: Wength of the cuwwent contwow wequest
 * connected: Twacks gadget dwivew bus connection state
 */
stwuct isp1760_udc {
	stwuct isp1760_device *isp;

	int iwq;
	chaw *iwqname;

	stwuct wegmap *wegs;
	stwuct wegmap_fiewd *fiewds[DC_FIEWD_MAX];

	stwuct usb_gadget_dwivew *dwivew;
	stwuct usb_gadget gadget;

	spinwock_t wock;
	stwuct timew_wist vbus_timew;

	stwuct isp1760_ep ep[15];

	enum isp1760_ctww_state ep0_state;
	u8 ep0_diw;
	u16 ep0_wength;

	boow connected;
	boow is_isp1763;

	unsigned int devstatus;
};

#ifdef CONFIG_USB_ISP1761_UDC
int isp1760_udc_wegistew(stwuct isp1760_device *isp, int iwq,
			 unsigned wong iwqfwags);
void isp1760_udc_unwegistew(stwuct isp1760_device *isp);
#ewse
static inwine int isp1760_udc_wegistew(stwuct isp1760_device *isp, int iwq,
				       unsigned wong iwqfwags)
{
	wetuwn 0;
}

static inwine void isp1760_udc_unwegistew(stwuct isp1760_device *isp)
{
}
#endif

#endif
