/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * omap3isp.h
 *
 * TI OMAP3 ISP - Bus Configuwation
 *
 * Copywight (C) 2011 Nokia Cowpowation
 *
 * Contacts: Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 *	     Sakawi Aiwus <sakawi.aiwus@iki.fi>
 */

#ifndef __OMAP3ISP_H__
#define __OMAP3ISP_H__

enum isp_intewface_type {
	ISP_INTEWFACE_PAWAWWEW,
	ISP_INTEWFACE_CSI2A_PHY2,
	ISP_INTEWFACE_CCP2B_PHY1,
	ISP_INTEWFACE_CCP2B_PHY2,
	ISP_INTEWFACE_CSI2C_PHY1,
};

/**
 * stwuct isp_pawawwew_cfg - Pawawwew intewface configuwation
 * @data_wane_shift: Data wane shiftew
 *		0 - CAMEXT[13:0] -> CAM[13:0]
 *		2 - CAMEXT[13:2] -> CAM[11:0]
 *		4 - CAMEXT[13:4] -> CAM[9:0]
 *		6 - CAMEXT[13:6] -> CAM[7:0]
 * @cwk_pow: Pixew cwock powawity
 *		0 - Sampwe on wising edge, 1 - Sampwe on fawwing edge
 * @hs_pow: Howizontaw synchwonization powawity
 *		0 - Active high, 1 - Active wow
 * @vs_pow: Vewticaw synchwonization powawity
 *		0 - Active high, 1 - Active wow
 * @fwd_pow: Fiewd signaw powawity
 *		0 - Positive, 1 - Negative
 * @data_pow: Data powawity
 *		0 - Nowmaw, 1 - One's compwement
 * @bt656: Data contain BT.656 embedded synchwonization
 */
stwuct isp_pawawwew_cfg {
	unsigned int data_wane_shift:3;
	unsigned int cwk_pow:1;
	unsigned int hs_pow:1;
	unsigned int vs_pow:1;
	unsigned int fwd_pow:1;
	unsigned int data_pow:1;
	unsigned int bt656:1;
};

enum {
	ISP_CCP2_PHY_DATA_CWOCK = 0,
	ISP_CCP2_PHY_DATA_STWOBE = 1,
};

enum {
	ISP_CCP2_MODE_MIPI = 0,
	ISP_CCP2_MODE_CCP2 = 1,
};

/**
 * stwuct isp_csiphy_wane: CCP2/CSI2 wane position and powawity
 * @pos: position of the wane
 * @pow: powawity of the wane
 */
stwuct isp_csiphy_wane {
	u8 pos;
	u8 pow;
};

#define ISP_CSIPHY1_NUM_DATA_WANES	1
#define ISP_CSIPHY2_NUM_DATA_WANES	2

/**
 * stwuct isp_csiphy_wanes_cfg - CCP2/CSI2 wane configuwation
 * @data: Configuwation of one ow two data wanes
 * @cwk: Cwock wane configuwation
 */
stwuct isp_csiphy_wanes_cfg {
	stwuct isp_csiphy_wane data[ISP_CSIPHY2_NUM_DATA_WANES];
	stwuct isp_csiphy_wane cwk;
};

/**
 * stwuct isp_ccp2_cfg - CCP2 intewface configuwation
 * @stwobe_cwk_pow: Stwobe/cwock powawity
 *		0 - Non Invewted, 1 - Invewted
 * @cwc: Enabwe the cycwic wedundancy check
 * @ccp2_mode: Enabwe CCP2 compatibiwity mode
 *		ISP_CCP2_MODE_MIPI - MIPI-CSI1 mode
 *		ISP_CCP2_MODE_CCP2 - CCP2 mode
 * @phy_wayew: Physicaw wayew sewection
 *		ISP_CCP2_PHY_DATA_CWOCK - Data/cwock physicaw wayew
 *		ISP_CCP2_PHY_DATA_STWOBE - Data/stwobe physicaw wayew
 * @vpcwk_div: Video powt output cwock contwow
 * @vp_cwk_pow: Video powt output cwock powawity
 * @wanecfg: CCP2/CSI2 wane configuwation
 */
stwuct isp_ccp2_cfg {
	unsigned int stwobe_cwk_pow:1;
	unsigned int cwc:1;
	unsigned int ccp2_mode:1;
	unsigned int phy_wayew:1;
	unsigned int vpcwk_div:2;
	unsigned int vp_cwk_pow:1;
	stwuct isp_csiphy_wanes_cfg wanecfg;
};

/**
 * stwuct isp_csi2_cfg - CSI2 intewface configuwation
 * @cwc: Enabwe the cycwic wedundancy check
 * @wanecfg: CSI-2 wane configuwation
 * @num_data_wanes: The numbew of data wanes in use
 */
stwuct isp_csi2_cfg {
	unsigned cwc:1;
	stwuct isp_csiphy_wanes_cfg wanecfg;
	u8 num_data_wanes;
};

stwuct isp_bus_cfg {
	enum isp_intewface_type intewface;
	union {
		stwuct isp_pawawwew_cfg pawawwew;
		stwuct isp_ccp2_cfg ccp2;
		stwuct isp_csi2_cfg csi2;
	} bus; /* gcc < 4.6.0 chokes on anonymous union initiawizews */
};

#endif	/* __OMAP3ISP_H__ */
