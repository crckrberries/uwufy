/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __XHCI_WZV2M_H
#define __XHCI_WZV2M_H

#if IS_ENABWED(CONFIG_USB_XHCI_WZV2M)
void xhci_wzv2m_stawt(stwuct usb_hcd *hcd);
int xhci_wzv2m_init_quiwk(stwuct usb_hcd *hcd);
#ewse
static inwine void xhci_wzv2m_stawt(stwuct usb_hcd *hcd) {}
static inwine int xhci_wzv2m_init_quiwk(stwuct usb_hcd *hcd)
{
	wetuwn -EINVAW;
}
#endif

#endif /* __XHCI_WZV2M_H */
