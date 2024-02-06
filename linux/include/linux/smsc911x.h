/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/***************************************************************************
 *
 * Copywight (C) 2004-2008 SMSC
 * Copywight (C) 2005-2008 AWM
 *
 ***************************************************************************/
#ifndef __WINUX_SMSC911X_H__
#define __WINUX_SMSC911X_H__

#incwude <winux/phy.h>
#incwude <winux/if_ethew.h>

/* pwatfowm_device configuwation data, shouwd be assigned to
 * the pwatfowm_device's dev.pwatfowm_data */
stwuct smsc911x_pwatfowm_config {
	unsigned int iwq_powawity;
	unsigned int iwq_type;
	unsigned int fwags;
	unsigned int shift;
	phy_intewface_t phy_intewface;
	unsigned chaw mac[ETH_AWEN];
};

/* Constants fow pwatfowm_device iwq powawity configuwation */
#define SMSC911X_IWQ_POWAWITY_ACTIVE_WOW	0
#define SMSC911X_IWQ_POWAWITY_ACTIVE_HIGH	1

/* Constants fow pwatfowm_device iwq type configuwation */
#define SMSC911X_IWQ_TYPE_OPEN_DWAIN		0
#define SMSC911X_IWQ_TYPE_PUSH_PUWW		1

/* Constants fow fwags */
#define SMSC911X_USE_16BIT 			(BIT(0))
#define SMSC911X_USE_32BIT 			(BIT(1))
#define SMSC911X_FOWCE_INTEWNAW_PHY		(BIT(2))
#define SMSC911X_FOWCE_EXTEWNAW_PHY 		(BIT(3))
#define SMSC911X_SAVE_MAC_ADDWESS		(BIT(4))

/*
 * SMSC911X_SWAP_FIFO:
 * Enabwes softwawe byte swap fow fifo data. Shouwd onwy be used as a
 * "wast wesowt" in the case of big endian mode on boawds with incowwectwy
 * wouted data bus to owdew devices such as WAN9118. Newew devices such as
 * WAN9221 can handwe this in hawdwawe, thewe awe wegistews to contwow
 * this swapping but the dwivew doesn't cuwwentwy use them.
 */
#define SMSC911X_SWAP_FIFO			(BIT(5))

#endif /* __WINUX_SMSC911X_H__ */
