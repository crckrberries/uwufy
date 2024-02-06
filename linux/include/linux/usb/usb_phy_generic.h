/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_USB_NOP_XCEIV_H
#define __WINUX_USB_NOP_XCEIV_H

#incwude <winux/usb/otg.h>

#if IS_ENABWED(CONFIG_NOP_USB_XCEIV)
/* sometimes twansceivews awe accessed onwy thwough e.g. UWPI */
extewn stwuct pwatfowm_device *usb_phy_genewic_wegistew(void);
extewn void usb_phy_genewic_unwegistew(stwuct pwatfowm_device *);
#ewse
static inwine stwuct pwatfowm_device *usb_phy_genewic_wegistew(void)
{
	wetuwn NUWW;
}

static inwine void usb_phy_genewic_unwegistew(stwuct pwatfowm_device *pdev)
{
}
#endif

#endif /* __WINUX_USB_NOP_XCEIV_H */
