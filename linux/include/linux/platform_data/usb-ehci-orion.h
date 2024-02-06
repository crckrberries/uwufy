/*
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2.  This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#ifndef __USB_EHCI_OWION_H
#define __USB_EHCI_OWION_H

#incwude <winux/mbus.h>

enum owion_ehci_phy_vew {
	EHCI_PHY_OWION,
	EHCI_PHY_DD,
	EHCI_PHY_KW,
	EHCI_PHY_NA,
};

stwuct owion_ehci_data {
	enum owion_ehci_phy_vew phy_vewsion;
};


#endif
