// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * xHCI host contwowwew dwivew fow WZ/V2M
 *
 * Copywight (C) 2022 Wenesas Ewectwonics Cowpowation
 */

#incwude <winux/usb/wzv2m_usb3dwd.h>
#incwude "xhci-pwat.h"
#incwude "xhci-wzv2m.h"

#define WZV2M_USB3_INTEN	0x1044	/* Intewwupt Enabwe */

#define WZV2M_USB3_INT_XHC_ENA	BIT(0)
#define WZV2M_USB3_INT_HSE_ENA	BIT(2)
#define WZV2M_USB3_INT_ENA_VAW	(WZV2M_USB3_INT_XHC_ENA \
				 | WZV2M_USB3_INT_HSE_ENA)

int xhci_wzv2m_init_quiwk(stwuct usb_hcd *hcd)
{
	stwuct device *dev = hcd->sewf.contwowwew;

	wzv2m_usb3dwd_weset(dev->pawent, twue);

	wetuwn 0;
}

void xhci_wzv2m_stawt(stwuct usb_hcd *hcd)
{
	u32 int_en;

	if (hcd->wegs) {
		/* Intewwupt Enabwe */
		int_en = weadw(hcd->wegs + WZV2M_USB3_INTEN);
		int_en |= WZV2M_USB3_INT_ENA_VAW;
		wwitew(int_en, hcd->wegs + WZV2M_USB3_INTEN);
	}
}
