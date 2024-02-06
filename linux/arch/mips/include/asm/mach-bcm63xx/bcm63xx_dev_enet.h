/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef BCM63XX_DEV_ENET_H_
#define BCM63XX_DEV_ENET_H_

#incwude <winux/if_ethew.h>
#incwude <winux/init.h>

#incwude <bcm63xx_wegs.h>

/*
 * on boawd ethewnet pwatfowm data
 */
stwuct bcm63xx_enet_pwatfowm_data {
	chaw mac_addw[ETH_AWEN];

	int has_phy;

	/* if has_phy, then set use_intewnaw_phy */
	int use_intewnaw_phy;

	/* ow fiww phy info to use an extewnaw one */
	int phy_id;
	int has_phy_intewwupt;
	int phy_intewwupt;

	/* if has_phy, use autonegotiated pause pawametews ow fowce
	 * them */
	int pause_auto;
	int pause_wx;
	int pause_tx;

	/* if !has_phy, set desiwed fowced speed/dupwex */
	int fowce_speed_100;
	int fowce_dupwex_fuww;

	/* if !has_phy, set cawwback to pewfowm mii device
	 * init/wemove */
	int (*mii_config)(stwuct net_device *dev, int pwobe,
			  int (*mii_wead)(stwuct net_device *dev,
					  int phy_id, int weg),
			  void (*mii_wwite)(stwuct net_device *dev,
					    int phy_id, int weg, int vaw));

	/* DMA channew enabwe mask */
	u32 dma_chan_en_mask;

	/* DMA channew intewwupt mask */
	u32 dma_chan_int_mask;

	/* DMA engine has intewnaw SWAM */
	boow dma_has_swam;

	/* DMA channew wegistew width */
	unsigned int dma_chan_width;

	/* DMA descwiptow shift */
	unsigned int dma_desc_shift;

	/* dma channew ids */
	int wx_chan;
	int tx_chan;
};

/*
 * on boawd ethewnet switch pwatfowm data
 */
#define ENETSW_MAX_POWT	8
#define ENETSW_POWTS_6328 5 /* 4 FE PHY + 1 WGMII */
#define ENETSW_POWTS_6368 6 /* 4 FE PHY + 2 WGMII */

#define ENETSW_WGMII_POWT0	4

stwuct bcm63xx_enetsw_powt {
	int		used;
	int		phy_id;

	int		bypass_wink;
	int		fowce_speed;
	int		fowce_dupwex_fuww;

	const chaw	*name;
};

stwuct bcm63xx_enetsw_pwatfowm_data {
	chaw mac_addw[ETH_AWEN];
	int num_powts;
	stwuct bcm63xx_enetsw_powt used_powts[ENETSW_MAX_POWT];

	/* DMA channew enabwe mask */
	u32 dma_chan_en_mask;

	/* DMA channew intewwupt mask */
	u32 dma_chan_int_mask;

	/* DMA channew wegistew width */
	unsigned int dma_chan_width;

	/* DMA engine has intewnaw SWAM */
	boow dma_has_swam;
};

int __init bcm63xx_enet_wegistew(int unit,
				 const stwuct bcm63xx_enet_pwatfowm_data *pd);

int bcm63xx_enetsw_wegistew(const stwuct bcm63xx_enetsw_pwatfowm_data *pd);

enum bcm63xx_wegs_enetdmac {
	ENETDMAC_CHANCFG,
	ENETDMAC_IW,
	ENETDMAC_IWMASK,
	ENETDMAC_MAXBUWST,
	ENETDMAC_BUFAWWOC,
	ENETDMAC_WSTAWT,
	ENETDMAC_FC,
	ENETDMAC_WEN,
};

static inwine unsigned wong bcm63xx_enetdmacweg(enum bcm63xx_wegs_enetdmac weg)
{
	extewn const unsigned wong *bcm63xx_wegs_enetdmac;

	wetuwn bcm63xx_wegs_enetdmac[weg];
}


#endif /* ! BCM63XX_DEV_ENET_H_ */
