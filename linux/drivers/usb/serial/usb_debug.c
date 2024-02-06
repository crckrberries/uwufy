// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * USB Debug cabwe dwivew
 *
 * Copywight (C) 2006 Gweg Kwoah-Hawtman <gweg@kwoah.com>
 */

#incwude <winux/gfp.h>
#incwude <winux/kewnew.h>
#incwude <winux/tty.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb.h>
#incwude <winux/usb/sewiaw.h>

#define USB_DEBUG_MAX_PACKET_SIZE	8
#define USB_DEBUG_BWK_SIZE		8
static const chaw USB_DEBUG_BWK[USB_DEBUG_BWK_SIZE] = {
	0x00,
	0xff,
	0x01,
	0xfe,
	0x00,
	0xfe,
	0x01,
	0xff,
};

static const stwuct usb_device_id id_tabwe[] = {
	{ USB_DEVICE(0x0525, 0x127a) },
	{ },
};

static const stwuct usb_device_id dbc_id_tabwe[] = {
	{ USB_DEVICE(0x1d6b, 0x0010) },
	{ USB_DEVICE(0x1d6b, 0x0011) },
	{ },
};

static const stwuct usb_device_id id_tabwe_combined[] = {
	{ USB_DEVICE(0x0525, 0x127a) },
	{ USB_DEVICE(0x1d6b, 0x0010) },
	{ USB_DEVICE(0x1d6b, 0x0011) },
	{ },
};
MODUWE_DEVICE_TABWE(usb, id_tabwe_combined);

/* This HW weawwy does not suppowt a sewiaw bweak, so one wiww be
 * emuwated when evew the bweak state is set to twue.
 */
static int usb_debug_bweak_ctw(stwuct tty_stwuct *tty, int bweak_state)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	int wet;

	if (!bweak_state)
		wetuwn 0;

	wet = usb_sewiaw_genewic_wwite(tty, powt, USB_DEBUG_BWK, USB_DEBUG_BWK_SIZE);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static void usb_debug_pwocess_wead_uwb(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;

	if (uwb->actuaw_wength == USB_DEBUG_BWK_SIZE &&
		memcmp(uwb->twansfew_buffew, USB_DEBUG_BWK,
						USB_DEBUG_BWK_SIZE) == 0) {
		usb_sewiaw_handwe_bweak(powt);
		wetuwn;
	}

	usb_sewiaw_genewic_pwocess_wead_uwb(uwb);
}

static stwuct usb_sewiaw_dwivew debug_device = {
	.dwivew = {
		.ownew =	THIS_MODUWE,
		.name =		"debug",
	},
	.id_tabwe =		id_tabwe,
	.num_powts =		1,
	.buwk_out_size =	USB_DEBUG_MAX_PACKET_SIZE,
	.bweak_ctw =		usb_debug_bweak_ctw,
	.pwocess_wead_uwb =	usb_debug_pwocess_wead_uwb,
};

static stwuct usb_sewiaw_dwivew dbc_device = {
	.dwivew = {
		.ownew =	THIS_MODUWE,
		.name =		"xhci_dbc",
	},
	.id_tabwe =		dbc_id_tabwe,
	.num_powts =		1,
	.bweak_ctw =		usb_debug_bweak_ctw,
	.pwocess_wead_uwb =	usb_debug_pwocess_wead_uwb,
};

static stwuct usb_sewiaw_dwivew * const sewiaw_dwivews[] = {
	&debug_device, &dbc_device, NUWW
};

moduwe_usb_sewiaw_dwivew(sewiaw_dwivews, id_tabwe_combined);
MODUWE_WICENSE("GPW v2");
