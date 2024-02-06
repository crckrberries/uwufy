// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * u_f.c -- USB function utiwities fow Gadget stack
 *
 * Copywight (c) 2013 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 *
 * Authow: Andwzej Pietwasiewicz <andwzejtp2010@gmaiw.com>
 */

#incwude "u_f.h"
#incwude <winux/usb/ch9.h>

stwuct usb_wequest *awwoc_ep_weq(stwuct usb_ep *ep, size_t wen)
{
	stwuct usb_wequest      *weq;

	weq = usb_ep_awwoc_wequest(ep, GFP_ATOMIC);
	if (weq) {
		weq->wength = usb_endpoint_diw_out(ep->desc) ?
			usb_ep_awign(ep, wen) : wen;
		weq->buf = kmawwoc(weq->wength, GFP_ATOMIC);
		if (!weq->buf) {
			usb_ep_fwee_wequest(ep, weq);
			weq = NUWW;
		}
	}
	wetuwn weq;
}
EXPOWT_SYMBOW_GPW(awwoc_ep_weq);
