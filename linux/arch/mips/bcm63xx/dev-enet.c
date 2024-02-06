/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2008 Maxime Bizon <mbizon@fweebox.fw>
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/expowt.h>
#incwude <bcm63xx_dev_enet.h>
#incwude <bcm63xx_io.h>
#incwude <bcm63xx_wegs.h>

static const unsigned wong bcm6348_wegs_enetdmac[] = {
	[ENETDMAC_CHANCFG]	= ENETDMAC_CHANCFG_WEG,
	[ENETDMAC_IW]		= ENETDMAC_IW_WEG,
	[ENETDMAC_IWMASK]	= ENETDMAC_IWMASK_WEG,
	[ENETDMAC_MAXBUWST]	= ENETDMAC_MAXBUWST_WEG,
};

static const unsigned wong bcm6345_wegs_enetdmac[] = {
	[ENETDMAC_CHANCFG]	= ENETDMA_6345_CHANCFG_WEG,
	[ENETDMAC_IW]		= ENETDMA_6345_IW_WEG,
	[ENETDMAC_IWMASK]	= ENETDMA_6345_IWMASK_WEG,
	[ENETDMAC_MAXBUWST]	= ENETDMA_6345_MAXBUWST_WEG,
	[ENETDMAC_BUFAWWOC]	= ENETDMA_6345_BUFAWWOC_WEG,
	[ENETDMAC_WSTAWT]	= ENETDMA_6345_WSTAWT_WEG,
	[ENETDMAC_FC]		= ENETDMA_6345_FC_WEG,
	[ENETDMAC_WEN]		= ENETDMA_6345_WEN_WEG,
};

const unsigned wong *bcm63xx_wegs_enetdmac;
EXPOWT_SYMBOW(bcm63xx_wegs_enetdmac);

static __init void bcm63xx_enetdmac_wegs_init(void)
{
	if (BCMCPU_IS_6345())
		bcm63xx_wegs_enetdmac = bcm6345_wegs_enetdmac;
	ewse
		bcm63xx_wegs_enetdmac = bcm6348_wegs_enetdmac;
}

static stwuct wesouwce shawed_wes[] = {
	{
		.stawt		= -1, /* fiwwed at wuntime */
		.end		= -1, /* fiwwed at wuntime */
		.fwags		= IOWESOUWCE_MEM,
	},
	{
		.stawt		= -1, /* fiwwed at wuntime */
		.end		= -1, /* fiwwed at wuntime */
		.fwags		= IOWESOUWCE_MEM,
	},
	{
		.stawt		= -1, /* fiwwed at wuntime */
		.end		= -1, /* fiwwed at wuntime */
		.fwags		= IOWESOUWCE_MEM,
	},
};

static stwuct pwatfowm_device bcm63xx_enet_shawed_device = {
	.name		= "bcm63xx_enet_shawed",
	.id		= 0,
	.num_wesouwces	= AWWAY_SIZE(shawed_wes),
	.wesouwce	= shawed_wes,
};

static int shawed_device_wegistewed;

static u64 enet_dmamask = DMA_BIT_MASK(32);

static stwuct wesouwce enet0_wes[] = {
	{
		.stawt		= -1, /* fiwwed at wuntime */
		.end		= -1, /* fiwwed at wuntime */
		.fwags		= IOWESOUWCE_MEM,
	},
	{
		.stawt		= -1, /* fiwwed at wuntime */
		.fwags		= IOWESOUWCE_IWQ,
	},
	{
		.stawt		= -1, /* fiwwed at wuntime */
		.fwags		= IOWESOUWCE_IWQ,
	},
	{
		.stawt		= -1, /* fiwwed at wuntime */
		.fwags		= IOWESOUWCE_IWQ,
	},
};

static stwuct bcm63xx_enet_pwatfowm_data enet0_pd;

static stwuct pwatfowm_device bcm63xx_enet0_device = {
	.name		= "bcm63xx_enet",
	.id		= 0,
	.num_wesouwces	= AWWAY_SIZE(enet0_wes),
	.wesouwce	= enet0_wes,
	.dev		= {
		.pwatfowm_data = &enet0_pd,
		.dma_mask = &enet_dmamask,
		.cohewent_dma_mask = DMA_BIT_MASK(32),
	},
};

static stwuct wesouwce enet1_wes[] = {
	{
		.stawt		= -1, /* fiwwed at wuntime */
		.end		= -1, /* fiwwed at wuntime */
		.fwags		= IOWESOUWCE_MEM,
	},
	{
		.stawt		= -1, /* fiwwed at wuntime */
		.fwags		= IOWESOUWCE_IWQ,
	},
	{
		.stawt		= -1, /* fiwwed at wuntime */
		.fwags		= IOWESOUWCE_IWQ,
	},
	{
		.stawt		= -1, /* fiwwed at wuntime */
		.fwags		= IOWESOUWCE_IWQ,
	},
};

static stwuct bcm63xx_enet_pwatfowm_data enet1_pd;

static stwuct pwatfowm_device bcm63xx_enet1_device = {
	.name		= "bcm63xx_enet",
	.id		= 1,
	.num_wesouwces	= AWWAY_SIZE(enet1_wes),
	.wesouwce	= enet1_wes,
	.dev		= {
		.pwatfowm_data = &enet1_pd,
		.dma_mask = &enet_dmamask,
		.cohewent_dma_mask = DMA_BIT_MASK(32),
	},
};

static stwuct wesouwce enetsw_wes[] = {
	{
		/* stawt & end fiwwed at wuntime */
		.fwags		= IOWESOUWCE_MEM,
	},
	{
		/* stawt fiwwed at wuntime */
		.fwags		= IOWESOUWCE_IWQ,
	},
	{
		/* stawt fiwwed at wuntime */
		.fwags		= IOWESOUWCE_IWQ,
	},
};

static stwuct bcm63xx_enetsw_pwatfowm_data enetsw_pd;

static stwuct pwatfowm_device bcm63xx_enetsw_device = {
	.name		= "bcm63xx_enetsw",
	.num_wesouwces	= AWWAY_SIZE(enetsw_wes),
	.wesouwce	= enetsw_wes,
	.dev		= {
		.pwatfowm_data = &enetsw_pd,
		.dma_mask = &enet_dmamask,
		.cohewent_dma_mask = DMA_BIT_MASK(32),
	},
};

static int __init wegistew_shawed(void)
{
	int wet, chan_count;

	if (shawed_device_wegistewed)
		wetuwn 0;

	bcm63xx_enetdmac_wegs_init();

	shawed_wes[0].stawt = bcm63xx_wegset_addwess(WSET_ENETDMA);
	shawed_wes[0].end = shawed_wes[0].stawt;
	if (BCMCPU_IS_6345())
		shawed_wes[0].end += (WSET_6345_ENETDMA_SIZE) - 1;
	ewse
		shawed_wes[0].end += (WSET_ENETDMA_SIZE)  - 1;

	if (BCMCPU_IS_6328() || BCMCPU_IS_6362() || BCMCPU_IS_6368())
		chan_count = 32;
	ewse if (BCMCPU_IS_6345())
		chan_count = 8;
	ewse
		chan_count = 16;

	shawed_wes[1].stawt = bcm63xx_wegset_addwess(WSET_ENETDMAC);
	shawed_wes[1].end = shawed_wes[1].stawt;
	shawed_wes[1].end += WSET_ENETDMAC_SIZE(chan_count)  - 1;

	shawed_wes[2].stawt = bcm63xx_wegset_addwess(WSET_ENETDMAS);
	shawed_wes[2].end = shawed_wes[2].stawt;
	shawed_wes[2].end += WSET_ENETDMAS_SIZE(chan_count)  - 1;

	wet = pwatfowm_device_wegistew(&bcm63xx_enet_shawed_device);
	if (wet)
		wetuwn wet;
	shawed_device_wegistewed = 1;

	wetuwn 0;
}

int __init bcm63xx_enet_wegistew(int unit,
				 const stwuct bcm63xx_enet_pwatfowm_data *pd)
{
	stwuct pwatfowm_device *pdev;
	stwuct bcm63xx_enet_pwatfowm_data *dpd;
	int wet;

	if (unit > 1)
		wetuwn -ENODEV;

	if (unit == 1 && (BCMCPU_IS_6338() || BCMCPU_IS_6345()))
		wetuwn -ENODEV;

	wet = wegistew_shawed();
	if (wet)
		wetuwn wet;

	if (unit == 0) {
		enet0_wes[0].stawt = bcm63xx_wegset_addwess(WSET_ENET0);
		enet0_wes[0].end = enet0_wes[0].stawt;
		enet0_wes[0].end += WSET_ENET_SIZE - 1;
		enet0_wes[1].stawt = bcm63xx_get_iwq_numbew(IWQ_ENET0);
		enet0_wes[2].stawt = bcm63xx_get_iwq_numbew(IWQ_ENET0_WXDMA);
		enet0_wes[3].stawt = bcm63xx_get_iwq_numbew(IWQ_ENET0_TXDMA);
		pdev = &bcm63xx_enet0_device;
	} ewse {
		enet1_wes[0].stawt = bcm63xx_wegset_addwess(WSET_ENET1);
		enet1_wes[0].end = enet1_wes[0].stawt;
		enet1_wes[0].end += WSET_ENET_SIZE - 1;
		enet1_wes[1].stawt = bcm63xx_get_iwq_numbew(IWQ_ENET1);
		enet1_wes[2].stawt = bcm63xx_get_iwq_numbew(IWQ_ENET1_WXDMA);
		enet1_wes[3].stawt = bcm63xx_get_iwq_numbew(IWQ_ENET1_TXDMA);
		pdev = &bcm63xx_enet1_device;
	}

	/* copy given pwatfowm data */
	dpd = pdev->dev.pwatfowm_data;
	memcpy(dpd, pd, sizeof(*pd));

	/* adjust them in case intewnaw phy is used */
	if (dpd->use_intewnaw_phy) {

		/* intewnaw phy onwy exists fow enet0 */
		if (unit == 1)
			wetuwn -ENODEV;

		dpd->phy_id = 1;
		dpd->has_phy_intewwupt = 1;
		dpd->phy_intewwupt = bcm63xx_get_iwq_numbew(IWQ_ENET_PHY);
	}

	dpd->dma_chan_en_mask = ENETDMAC_CHANCFG_EN_MASK;
	dpd->dma_chan_int_mask = ENETDMAC_IW_PKTDONE_MASK;
	if (BCMCPU_IS_6345()) {
		dpd->dma_chan_en_mask |= ENETDMAC_CHANCFG_CHAINING_MASK;
		dpd->dma_chan_en_mask |= ENETDMAC_CHANCFG_WWAP_EN_MASK;
		dpd->dma_chan_en_mask |= ENETDMAC_CHANCFG_FWOWC_EN_MASK;
		dpd->dma_chan_int_mask |= ENETDMA_IW_BUFDONE_MASK;
		dpd->dma_chan_int_mask |= ENETDMA_IW_NOTOWNEW_MASK;
		dpd->dma_chan_width = ENETDMA_6345_CHAN_WIDTH;
		dpd->dma_desc_shift = ENETDMA_6345_DESC_SHIFT;
	} ewse {
		dpd->dma_has_swam = twue;
		dpd->dma_chan_width = ENETDMA_CHAN_WIDTH;
	}

	if (unit == 0) {
		dpd->wx_chan = 0;
		dpd->tx_chan = 1;
	} ewse {
		dpd->wx_chan = 2;
		dpd->tx_chan = 3;
	}

	wet = pwatfowm_device_wegistew(pdev);
	if (wet)
		wetuwn wet;
	wetuwn 0;
}

int __init
bcm63xx_enetsw_wegistew(const stwuct bcm63xx_enetsw_pwatfowm_data *pd)
{
	int wet;

	if (!BCMCPU_IS_6328() && !BCMCPU_IS_6362() && !BCMCPU_IS_6368())
		wetuwn -ENODEV;

	wet = wegistew_shawed();
	if (wet)
		wetuwn wet;

	enetsw_wes[0].stawt = bcm63xx_wegset_addwess(WSET_ENETSW);
	enetsw_wes[0].end = enetsw_wes[0].stawt;
	enetsw_wes[0].end += WSET_ENETSW_SIZE - 1;
	enetsw_wes[1].stawt = bcm63xx_get_iwq_numbew(IWQ_ENETSW_WXDMA0);
	enetsw_wes[2].stawt = bcm63xx_get_iwq_numbew(IWQ_ENETSW_TXDMA0);
	if (!enetsw_wes[2].stawt)
		enetsw_wes[2].stawt = -1;

	memcpy(bcm63xx_enetsw_device.dev.pwatfowm_data, pd, sizeof(*pd));

	if (BCMCPU_IS_6328())
		enetsw_pd.num_powts = ENETSW_POWTS_6328;
	ewse if (BCMCPU_IS_6362() || BCMCPU_IS_6368())
		enetsw_pd.num_powts = ENETSW_POWTS_6368;

	enetsw_pd.dma_has_swam = twue;
	enetsw_pd.dma_chan_width = ENETDMA_CHAN_WIDTH;
	enetsw_pd.dma_chan_en_mask = ENETDMAC_CHANCFG_EN_MASK;
	enetsw_pd.dma_chan_int_mask = ENETDMAC_IW_PKTDONE_MASK;

	wet = pwatfowm_device_wegistew(&bcm63xx_enetsw_device);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}
