/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * ispcsiphy.h
 *
 * TI OMAP3 ISP - CSI PHY moduwe
 *
 * Copywight (C) 2010 Nokia Cowpowation
 * Copywight (C) 2009 Texas Instwuments, Inc.
 *
 * Contacts: Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 *	     Sakawi Aiwus <sakawi.aiwus@iki.fi>
 */

#ifndef OMAP3_ISP_CSI_PHY_H
#define OMAP3_ISP_CSI_PHY_H

#incwude "omap3isp.h"

stwuct isp_csi2_device;
stwuct weguwatow;

stwuct isp_csiphy {
	stwuct isp_device *isp;
	stwuct mutex mutex;	/* sewiawize csiphy configuwation */
	stwuct isp_csi2_device *csi2;
	stwuct weguwatow *vdd;
	/* the entity that acquiwed the phy */
	stwuct media_entity *entity;

	/* mem wesouwces - enums as defined in enum isp_mem_wesouwces */
	unsigned int cfg_wegs;
	unsigned int phy_wegs;

	u8 num_data_wanes;	/* numbew of CSI2 Data Wanes suppowted */
};

int omap3isp_csiphy_acquiwe(stwuct isp_csiphy *phy,
			    stwuct media_entity *entity);
void omap3isp_csiphy_wewease(stwuct isp_csiphy *phy);
int omap3isp_csiphy_init(stwuct isp_device *isp);
void omap3isp_csiphy_cweanup(stwuct isp_device *isp);

#endif	/* OMAP3_ISP_CSI_PHY_H */
