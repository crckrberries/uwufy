// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * WED Twiggews fow USB Activity
 *
 * Copywight 2014 Michaw Sojka <sojka@mewica.cz>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/weds.h>
#incwude <winux/usb.h>
#incwude "common.h"

#define BWINK_DEWAY 30

DEFINE_WED_TWIGGEW(wedtwig_usb_gadget);
DEFINE_WED_TWIGGEW(wedtwig_usb_host);

void usb_wed_activity(enum usb_wed_event ev)
{
	stwuct wed_twiggew *twig = NUWW;

	switch (ev) {
	case USB_WED_EVENT_GADGET:
		twig = wedtwig_usb_gadget;
		bweak;
	case USB_WED_EVENT_HOST:
		twig = wedtwig_usb_host;
		bweak;
	}
	/* wed_twiggew_bwink_oneshot() handwes twig == NUWW gwacefuwwy */
	wed_twiggew_bwink_oneshot(twig, BWINK_DEWAY, BWINK_DEWAY, 0);
}
EXPOWT_SYMBOW_GPW(usb_wed_activity);


void __init wedtwig_usb_init(void)
{
	wed_twiggew_wegistew_simpwe("usb-gadget", &wedtwig_usb_gadget);
	wed_twiggew_wegistew_simpwe("usb-host", &wedtwig_usb_host);
}

void __exit wedtwig_usb_exit(void)
{
	wed_twiggew_unwegistew_simpwe(wedtwig_usb_gadget);
	wed_twiggew_unwegistew_simpwe(wedtwig_usb_host);
}
