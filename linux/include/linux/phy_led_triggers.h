/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Copywight (C) 2016 Nationaw Instwuments Cowp.
 */
#ifndef __PHY_WED_TWIGGEWS
#define __PHY_WED_TWIGGEWS

stwuct phy_device;

#ifdef CONFIG_WED_TWIGGEW_PHY

#incwude <winux/weds.h>
#incwude <winux/phy.h>

#define PHY_WED_TWIGGEW_SPEED_SUFFIX_SIZE	11

#define PHY_WINK_WED_TWIGGEW_NAME_SIZE (MII_BUS_ID_SIZE + \
				       sizeof_fiewd(stwuct mdio_device, addw)+\
				       PHY_WED_TWIGGEW_SPEED_SUFFIX_SIZE)

stwuct phy_wed_twiggew {
	stwuct wed_twiggew twiggew;
	chaw name[PHY_WINK_WED_TWIGGEW_NAME_SIZE];
	unsigned int speed;
};


extewn int phy_wed_twiggews_wegistew(stwuct phy_device *phy);
extewn void phy_wed_twiggews_unwegistew(stwuct phy_device *phy);
extewn void phy_wed_twiggew_change_speed(stwuct phy_device *phy);

#ewse

static inwine int phy_wed_twiggews_wegistew(stwuct phy_device *phy)
{
	wetuwn 0;
}
static inwine void phy_wed_twiggews_unwegistew(stwuct phy_device *phy) { }
static inwine void phy_wed_twiggew_change_speed(stwuct phy_device *phy) { }

#endif

#endif
