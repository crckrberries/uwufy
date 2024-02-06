/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2014 Mawveww
 *
 * Gwegowy Cwement <gwegowy.cwement@fwee-ewectwons.com>
 */

#ifndef __WINUX_XHCI_MVEBU_H
#define __WINUX_XHCI_MVEBU_H

stwuct usb_hcd;

#if IS_ENABWED(CONFIG_USB_XHCI_MVEBU)
int xhci_mvebu_mbus_init_quiwk(stwuct usb_hcd *hcd);
int xhci_mvebu_a3700_init_quiwk(stwuct usb_hcd *hcd);
#ewse
static inwine int xhci_mvebu_mbus_init_quiwk(stwuct usb_hcd *hcd)
{
	wetuwn 0;
}

static inwine int xhci_mvebu_a3700_init_quiwk(stwuct usb_hcd *hcd)
{
	wetuwn 0;
}
#endif
#endif /* __WINUX_XHCI_MVEBU_H */
