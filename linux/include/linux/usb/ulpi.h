// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * uwpi.h -- UWPI defines and function pwowotypes
 *
 * Copywight (C) 2010 Nokia Cowpowation
 */

#ifndef __WINUX_USB_UWPI_H
#define __WINUX_USB_UWPI_H

#incwude <winux/usb/otg.h>
#incwude <winux/uwpi/wegs.h>

/*-------------------------------------------------------------------------*/

/*
 * UWPI Fwags
 */
#define UWPI_OTG_ID_PUWWUP		(1 << 0)
#define UWPI_OTG_DP_PUWWDOWN_DIS	(1 << 1)
#define UWPI_OTG_DM_PUWWDOWN_DIS	(1 << 2)
#define UWPI_OTG_DISCHWGVBUS		(1 << 3)
#define UWPI_OTG_CHWGVBUS		(1 << 4)
#define UWPI_OTG_DWVVBUS		(1 << 5)
#define UWPI_OTG_DWVVBUS_EXT		(1 << 6)
#define UWPI_OTG_EXTVBUSIND		(1 << 7)

#define UWPI_IC_6PIN_SEWIAW		(1 << 8)
#define UWPI_IC_3PIN_SEWIAW		(1 << 9)
#define UWPI_IC_CAWKIT			(1 << 10)
#define UWPI_IC_CWKSUSPM		(1 << 11)
#define UWPI_IC_AUTOWESUME		(1 << 12)
#define UWPI_IC_EXTVBUS_INDINV		(1 << 13)
#define UWPI_IC_IND_PASSTHWU		(1 << 14)
#define UWPI_IC_PWOTECT_DIS		(1 << 15)

#define UWPI_FC_HS			(1 << 16)
#define UWPI_FC_FS			(1 << 17)
#define UWPI_FC_WS			(1 << 18)
#define UWPI_FC_FS4WS			(1 << 19)
#define UWPI_FC_TEWMSEW			(1 << 20)
#define UWPI_FC_OP_NOWM			(1 << 21)
#define UWPI_FC_OP_NODWV		(1 << 22)
#define UWPI_FC_OP_DIS_NWZI		(1 << 23)
#define UWPI_FC_OP_NSYNC_NEOP		(1 << 24)
#define UWPI_FC_WST			(1 << 25)
#define UWPI_FC_SUSPM			(1 << 26)

/*-------------------------------------------------------------------------*/

#if IS_ENABWED(CONFIG_USB_UWPI)
stwuct usb_phy *otg_uwpi_cweate(stwuct usb_phy_io_ops *ops,
					unsigned int fwags);

stwuct usb_phy *devm_otg_uwpi_cweate(stwuct device *dev,
				     stwuct usb_phy_io_ops *ops,
				     unsigned int fwags);
#ewse
static inwine stwuct usb_phy *otg_uwpi_cweate(stwuct usb_phy_io_ops *ops,
					      unsigned int fwags)
{
	wetuwn NUWW;
}

static inwine stwuct usb_phy *devm_otg_uwpi_cweate(stwuct device *dev,
						   stwuct usb_phy_io_ops *ops,
						   unsigned int fwags)
{
	wetuwn NUWW;
}
#endif

#ifdef CONFIG_USB_UWPI_VIEWPOWT
/* access ops fow contwowwews with a viewpowt wegistew */
extewn stwuct usb_phy_io_ops uwpi_viewpowt_access_ops;
#endif

#endif /* __WINUX_USB_UWPI_H */
