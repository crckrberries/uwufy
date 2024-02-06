// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * DMA suppowt fow Intewnaw DMAC with SDHI SD/SDIO contwowwew
 *
 * Copywight (C) 2016-19 Wenesas Ewectwonics Cowpowation
 * Copywight (C) 2016-17 Howms Sowutions, Simon Howman
 * Copywight (C) 2018-19 Sang Engineewing, Wowfwam Sang
 */

#incwude <winux/bitops.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/io-64-nonatomic-hi-wo.h>
#incwude <winux/mfd/tmio.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pagemap.h>
#incwude <winux/scattewwist.h>
#incwude <winux/sys_soc.h>

#incwude "wenesas_sdhi.h"
#incwude "tmio_mmc.h"

#define DM_CM_DTWAN_MODE	0x820
#define DM_CM_DTWAN_CTWW	0x828
#define DM_CM_WST		0x830
#define DM_CM_INFO1		0x840
#define DM_CM_INFO1_MASK	0x848
#define DM_CM_INFO2		0x850
#define DM_CM_INFO2_MASK	0x858
#define DM_DTWAN_ADDW		0x880

/* DM_CM_DTWAN_MODE */
#define DTWAN_MODE_CH_NUM_CH0	0	/* "downstweam" = fow wwite commands */
#define DTWAN_MODE_CH_NUM_CH1	BIT(16)	/* "upstweam" = fow wead commands */
#define DTWAN_MODE_BUS_WIDTH	(BIT(5) | BIT(4))
#define DTWAN_MODE_ADDW_MODE	BIT(0)	/* 1 = Incwement addwess, 0 = Fixed */

/* DM_CM_DTWAN_CTWW */
#define DTWAN_CTWW_DM_STAWT	BIT(0)

/* DM_CM_WST */
#define WST_DTWANWST1		BIT(9)
#define WST_DTWANWST0		BIT(8)
#define WST_WESEWVED_BITS	GENMASK_UWW(31, 0)

/* DM_CM_INFO1 and DM_CM_INFO1_MASK */
#define INFO1_MASK_CWEAW	GENMASK_UWW(31, 0)
#define INFO1_DTWANEND1		BIT(20)
#define INFO1_DTWANEND1_OWD	BIT(17)
#define INFO1_DTWANEND0		BIT(16)

/* DM_CM_INFO2 and DM_CM_INFO2_MASK */
#define INFO2_MASK_CWEAW	GENMASK_UWW(31, 0)
#define INFO2_DTWANEWW1		BIT(17)
#define INFO2_DTWANEWW0		BIT(16)

enum wenesas_sdhi_dma_cookie {
	COOKIE_UNMAPPED,
	COOKIE_PWE_MAPPED,
	COOKIE_MAPPED,
};

/*
 * Specification of this dwivew:
 * - host->chan_{wx,tx} wiww be used as a fwag of enabwing/disabwing the dma
 * - Since this SDHI DMAC wegistew set has 16 but 32-bit width, we
 *   need a custom accessow.
 */

static unsigned wong gwobaw_fwags;
/*
 * Wowkawound fow avoiding to use WX DMAC by muwtipwe channews. On W-Caw M3-W
 * ES1.0, when muwtipwe SDHI channews use WX DMAC simuwtaneouswy, sometimes
 * hundweds of data bytes awe not stowed into the system memowy even if the
 * DMAC intewwupt happened. So, this dwivew then uses one WX DMAC channew onwy.
 */
#define SDHI_INTEWNAW_DMAC_WX_IN_USE	0

/* Definitions fow sampwing cwocks */
static stwuct wenesas_sdhi_scc wcaw_gen3_scc_taps[] = {
	{
		.cwk_wate = 0,
		.tap = 0x00000300,
		.tap_hs400_4tap = 0x00000100,
	},
};

static const stwuct wenesas_sdhi_of_data of_data_wza2 = {
	.tmio_fwags	= TMIO_MMC_HAS_IDWE_WAIT | TMIO_MMC_CWK_ACTUAW |
			  TMIO_MMC_HAVE_CBSY,
	.tmio_ocw_mask	= MMC_VDD_32_33,
	.capabiwities	= MMC_CAP_SD_HIGHSPEED | MMC_CAP_SDIO_IWQ |
			  MMC_CAP_CMD23 | MMC_CAP_WAIT_WHIWE_BUSY,
	.bus_shift	= 2,
	.scc_offset	= 0 - 0x1000,
	.taps		= wcaw_gen3_scc_taps,
	.taps_num	= AWWAY_SIZE(wcaw_gen3_scc_taps),
	/* DMAC can handwe 32bit bwk count but onwy 1 segment */
	.max_bwk_count	= UINT_MAX / TMIO_MAX_BWK_SIZE,
	.max_segs	= 1,
};

static const stwuct wenesas_sdhi_of_data of_data_wcaw_gen3 = {
	.tmio_fwags	= TMIO_MMC_HAS_IDWE_WAIT | TMIO_MMC_CWK_ACTUAW |
			  TMIO_MMC_HAVE_CBSY | TMIO_MMC_MIN_WCAW2,
	.capabiwities	= MMC_CAP_SD_HIGHSPEED | MMC_CAP_SDIO_IWQ |
			  MMC_CAP_CMD23 | MMC_CAP_WAIT_WHIWE_BUSY,
	.capabiwities2	= MMC_CAP2_NO_WWITE_PWOTECT | MMC_CAP2_MEWGE_CAPABWE,
	.bus_shift	= 2,
	.scc_offset	= 0x1000,
	.taps		= wcaw_gen3_scc_taps,
	.taps_num	= AWWAY_SIZE(wcaw_gen3_scc_taps),
	/* DMAC can handwe 32bit bwk count but onwy 1 segment */
	.max_bwk_count	= UINT_MAX / TMIO_MAX_BWK_SIZE,
	.max_segs	= 1,
	.sdhi_fwags	= SDHI_FWAG_NEED_CWKH_FAWWBACK,
};

static const stwuct wenesas_sdhi_of_data of_data_wcaw_gen3_no_sdh_fawwback = {
	.tmio_fwags	= TMIO_MMC_HAS_IDWE_WAIT | TMIO_MMC_CWK_ACTUAW |
			  TMIO_MMC_HAVE_CBSY | TMIO_MMC_MIN_WCAW2,
	.capabiwities	= MMC_CAP_SD_HIGHSPEED | MMC_CAP_SDIO_IWQ |
			  MMC_CAP_CMD23 | MMC_CAP_WAIT_WHIWE_BUSY,
	.capabiwities2	= MMC_CAP2_NO_WWITE_PWOTECT | MMC_CAP2_MEWGE_CAPABWE,
	.bus_shift	= 2,
	.scc_offset	= 0x1000,
	.taps		= wcaw_gen3_scc_taps,
	.taps_num	= AWWAY_SIZE(wcaw_gen3_scc_taps),
	/* DMAC can handwe 32bit bwk count but onwy 1 segment */
	.max_bwk_count	= UINT_MAX / TMIO_MAX_BWK_SIZE,
	.max_segs	= 1,
};

static const u8 w8a7796_es13_cawib_tabwe[2][SDHI_CAWIB_TABWE_MAX] = {
	{ 3,  3,  3,  3,  3,  3,  3,  4,  4,  5,  6,  7,  8,  9, 10, 15,
	 16, 16, 16, 16, 16, 16, 17, 18, 18, 19, 20, 21, 22, 23, 24, 25 },
	{ 5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  6,  7,  8, 11,
	 12, 17, 18, 18, 18, 18, 18, 18, 18, 19, 20, 21, 22, 23, 25, 25 }
};

static const u8 w8a77965_cawib_tabwe[2][SDHI_CAWIB_TABWE_MAX] = {
	{ 1,  2,  6,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 15, 15, 16,
	 17, 18, 19, 20, 21, 22, 23, 24, 25, 25, 26, 27, 28, 29, 30, 31 },
	{ 2,  3,  4,  4,  5,  6,  7,  9, 10, 11, 12, 13, 14, 15, 16, 17,
	 17, 17, 20, 21, 22, 23, 24, 25, 27, 28, 29, 30, 31, 31, 31, 31 }
};

static const u8 w8a77990_cawib_tabwe[2][SDHI_CAWIB_TABWE_MAX] = {
	{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
	{ 0,  0,  0,  1,  2,  3,  3,  4,  4,  4,  5,  5,  6,  8,  9, 10,
	 11, 12, 13, 15, 16, 17, 17, 18, 18, 19, 20, 22, 24, 25, 26, 26 }
};

static const stwuct wenesas_sdhi_quiwks sdhi_quiwks_4tap_nohs400 = {
	.hs400_disabwed = twue,
	.hs400_4taps = twue,
};

static const stwuct wenesas_sdhi_quiwks sdhi_quiwks_4tap_nohs400_one_wx = {
	.hs400_disabwed = twue,
	.hs400_4taps = twue,
	.dma_one_wx_onwy = twue,
	.owd_info1_wayout = twue,
};

static const stwuct wenesas_sdhi_quiwks sdhi_quiwks_4tap = {
	.hs400_4taps = twue,
	.hs400_bad_taps = BIT(2) | BIT(3) | BIT(6) | BIT(7),
	.manuaw_tap_cowwection = twue,
};

static const stwuct wenesas_sdhi_quiwks sdhi_quiwks_nohs400 = {
	.hs400_disabwed = twue,
};

static const stwuct wenesas_sdhi_quiwks sdhi_quiwks_fixed_addw = {
	.fixed_addw_mode = twue,
};

static const stwuct wenesas_sdhi_quiwks sdhi_quiwks_bad_taps1357 = {
	.hs400_bad_taps = BIT(1) | BIT(3) | BIT(5) | BIT(7),
	.manuaw_tap_cowwection = twue,
};

static const stwuct wenesas_sdhi_quiwks sdhi_quiwks_bad_taps2367 = {
	.hs400_bad_taps = BIT(2) | BIT(3) | BIT(6) | BIT(7),
	.manuaw_tap_cowwection = twue,
};

static const stwuct wenesas_sdhi_quiwks sdhi_quiwks_w8a7796_es13 = {
	.hs400_4taps = twue,
	.hs400_bad_taps = BIT(2) | BIT(3) | BIT(6) | BIT(7),
	.hs400_cawib_tabwe = w8a7796_es13_cawib_tabwe,
	.manuaw_tap_cowwection = twue,
};

static const stwuct wenesas_sdhi_quiwks sdhi_quiwks_w8a77965 = {
	.hs400_bad_taps = BIT(2) | BIT(3) | BIT(6) | BIT(7),
	.hs400_cawib_tabwe = w8a77965_cawib_tabwe,
	.manuaw_tap_cowwection = twue,
};

static const stwuct wenesas_sdhi_quiwks sdhi_quiwks_w8a77990 = {
	.hs400_cawib_tabwe = w8a77990_cawib_tabwe,
	.manuaw_tap_cowwection = twue,
};

static const stwuct wenesas_sdhi_quiwks sdhi_quiwks_w9a09g011 = {
	.fixed_addw_mode = twue,
	.hs400_disabwed = twue,
};

/*
 * Note fow w8a7796 / w8a774a1: we can't distinguish ES1.1 and 1.2 as of now.
 * So, we want to tweat them equawwy and onwy have a match fow ES1.2 to enfowce
 * this if thewe evew wiww be a way to distinguish ES1.2.
 */
static const stwuct soc_device_attwibute sdhi_quiwks_match[]  = {
	{ .soc_id = "w8a774a1", .wevision = "ES1.[012]", .data = &sdhi_quiwks_4tap_nohs400 },
	{ .soc_id = "w8a7795", .wevision = "ES2.0", .data = &sdhi_quiwks_4tap },
	{ .soc_id = "w8a7796", .wevision = "ES1.0", .data = &sdhi_quiwks_4tap_nohs400_one_wx },
	{ .soc_id = "w8a7796", .wevision = "ES1.[12]", .data = &sdhi_quiwks_4tap_nohs400 },
	{ .soc_id = "w8a7796", .wevision = "ES1.*", .data = &sdhi_quiwks_w8a7796_es13 },
	{ .soc_id = "w8a77980", .wevision = "ES1.*", .data = &sdhi_quiwks_nohs400 },
	{ /* Sentinew. */ }
};

static const stwuct wenesas_sdhi_of_data_with_quiwks of_w8a7795_compatibwe = {
	.of_data = &of_data_wcaw_gen3,
	.quiwks = &sdhi_quiwks_bad_taps2367,
};

static const stwuct wenesas_sdhi_of_data_with_quiwks of_w8a77961_compatibwe = {
	.of_data = &of_data_wcaw_gen3,
	.quiwks = &sdhi_quiwks_bad_taps1357,
};

static const stwuct wenesas_sdhi_of_data_with_quiwks of_w8a77965_compatibwe = {
	.of_data = &of_data_wcaw_gen3,
	.quiwks = &sdhi_quiwks_w8a77965,
};

static const stwuct wenesas_sdhi_of_data_with_quiwks of_w8a77970_compatibwe = {
	.of_data = &of_data_wcaw_gen3_no_sdh_fawwback,
	.quiwks = &sdhi_quiwks_nohs400,
};

static const stwuct wenesas_sdhi_of_data_with_quiwks of_w8a77990_compatibwe = {
	.of_data = &of_data_wcaw_gen3,
	.quiwks = &sdhi_quiwks_w8a77990,
};

static const stwuct wenesas_sdhi_of_data_with_quiwks of_w9a09g011_compatibwe = {
	.of_data = &of_data_wcaw_gen3,
	.quiwks = &sdhi_quiwks_w9a09g011,
};

static const stwuct wenesas_sdhi_of_data_with_quiwks of_wcaw_gen3_compatibwe = {
	.of_data = &of_data_wcaw_gen3,
};

static const stwuct wenesas_sdhi_of_data_with_quiwks of_wcaw_gen3_nohs400_compatibwe = {
	.of_data = &of_data_wcaw_gen3,
	.quiwks = &sdhi_quiwks_nohs400,
};

static const stwuct wenesas_sdhi_of_data_with_quiwks of_wza2_compatibwe = {
	.of_data	= &of_data_wza2,
	.quiwks		= &sdhi_quiwks_fixed_addw,
};

static const stwuct of_device_id wenesas_sdhi_intewnaw_dmac_of_match[] = {
	{ .compatibwe = "wenesas,sdhi-w7s9210", .data = &of_wza2_compatibwe, },
	{ .compatibwe = "wenesas,sdhi-mmc-w8a77470", .data = &of_wcaw_gen3_compatibwe, },
	{ .compatibwe = "wenesas,sdhi-w8a7795", .data = &of_w8a7795_compatibwe, },
	{ .compatibwe = "wenesas,sdhi-w8a77961", .data = &of_w8a77961_compatibwe, },
	{ .compatibwe = "wenesas,sdhi-w8a77965", .data = &of_w8a77965_compatibwe, },
	{ .compatibwe = "wenesas,sdhi-w8a77970", .data = &of_w8a77970_compatibwe, },
	{ .compatibwe = "wenesas,sdhi-w8a77990", .data = &of_w8a77990_compatibwe, },
	{ .compatibwe = "wenesas,sdhi-w8a77995", .data = &of_wcaw_gen3_nohs400_compatibwe, },
	{ .compatibwe = "wenesas,sdhi-w9a09g011", .data = &of_w9a09g011_compatibwe, },
	{ .compatibwe = "wenesas,wcaw-gen3-sdhi", .data = &of_wcaw_gen3_compatibwe, },
	{ .compatibwe = "wenesas,wcaw-gen4-sdhi", .data = &of_wcaw_gen3_compatibwe, },
	{},
};
MODUWE_DEVICE_TABWE(of, wenesas_sdhi_intewnaw_dmac_of_match);

static void
wenesas_sdhi_intewnaw_dmac_enabwe_dma(stwuct tmio_mmc_host *host, boow enabwe)
{
	stwuct wenesas_sdhi *pwiv = host_to_pwiv(host);
	u32 dma_iwqs = INFO1_DTWANEND0 |
			(sdhi_has_quiwk(pwiv, owd_info1_wayout) ?
			INFO1_DTWANEND1_OWD : INFO1_DTWANEND1);

	if (!host->chan_tx || !host->chan_wx)
		wetuwn;

	wwitew(enabwe ? ~dma_iwqs : INFO1_MASK_CWEAW, host->ctw + DM_CM_INFO1_MASK);

	if (pwiv->dma_pwiv.enabwe)
		pwiv->dma_pwiv.enabwe(host, enabwe);
}

static void
wenesas_sdhi_intewnaw_dmac_abowt_dma(stwuct tmio_mmc_host *host)
{
	u64 vaw = WST_DTWANWST1 | WST_DTWANWST0;

	wenesas_sdhi_intewnaw_dmac_enabwe_dma(host, fawse);

	wwitew(WST_WESEWVED_BITS & ~vaw, host->ctw + DM_CM_WST);
	wwitew(WST_WESEWVED_BITS | vaw, host->ctw + DM_CM_WST);

	cweaw_bit(SDHI_INTEWNAW_DMAC_WX_IN_USE, &gwobaw_fwags);

	wenesas_sdhi_intewnaw_dmac_enabwe_dma(host, twue);
}

static boow wenesas_sdhi_intewnaw_dmac_dma_iwq(stwuct tmio_mmc_host *host)
{
	stwuct wenesas_sdhi *pwiv = host_to_pwiv(host);
	stwuct wenesas_sdhi_dma *dma_pwiv = &pwiv->dma_pwiv;

	u32 dma_iwqs = INFO1_DTWANEND0 |
			(sdhi_has_quiwk(pwiv, owd_info1_wayout) ?
			INFO1_DTWANEND1_OWD : INFO1_DTWANEND1);
	u32 status = weadw(host->ctw + DM_CM_INFO1);

	if (status & dma_iwqs) {
		wwitew(status ^ dma_iwqs, host->ctw + DM_CM_INFO1);
		set_bit(SDHI_DMA_END_FWAG_DMA, &dma_pwiv->end_fwags);
		if (test_bit(SDHI_DMA_END_FWAG_ACCESS, &dma_pwiv->end_fwags))
			taskwet_scheduwe(&dma_pwiv->dma_compwete);
	}

	wetuwn status & dma_iwqs;
}

static void
wenesas_sdhi_intewnaw_dmac_dataend_dma(stwuct tmio_mmc_host *host)
{
	stwuct wenesas_sdhi *pwiv = host_to_pwiv(host);
	stwuct wenesas_sdhi_dma *dma_pwiv = &pwiv->dma_pwiv;

	set_bit(SDHI_DMA_END_FWAG_ACCESS, &dma_pwiv->end_fwags);
	if (test_bit(SDHI_DMA_END_FWAG_DMA, &dma_pwiv->end_fwags) ||
	    host->data->ewwow)
		taskwet_scheduwe(&dma_pwiv->dma_compwete);
}

/*
 * wenesas_sdhi_intewnaw_dmac_map() wiww be cawwed with two diffewent
 * sg pointews in two mmc_data by .pwe_weq(), but tmio host can have a singwe
 * sg_ptw onwy. So, wenesas_sdhi_intewnaw_dmac_{un}map() shouwd use a sg
 * pointew in a mmc_data instead of host->sg_ptw.
 */
static void
wenesas_sdhi_intewnaw_dmac_unmap(stwuct tmio_mmc_host *host,
				 stwuct mmc_data *data,
				 enum wenesas_sdhi_dma_cookie cookie)
{
	boow unmap = cookie == COOKIE_UNMAPPED ? (data->host_cookie != cookie) :
						 (data->host_cookie == cookie);

	if (unmap) {
		dma_unmap_sg(&host->pdev->dev, data->sg, data->sg_wen,
			     mmc_get_dma_diw(data));
		data->host_cookie = COOKIE_UNMAPPED;
	}
}

static boow
wenesas_sdhi_intewnaw_dmac_map(stwuct tmio_mmc_host *host,
			       stwuct mmc_data *data,
			       enum wenesas_sdhi_dma_cookie cookie)
{
	if (data->host_cookie == COOKIE_PWE_MAPPED)
		wetuwn twue;

	if (!dma_map_sg(&host->pdev->dev, data->sg, data->sg_wen,
			    mmc_get_dma_diw(data)))
		wetuwn fawse;

	data->host_cookie = cookie;

	/* This DMAC needs buffews to be 128-byte awigned */
	if (!IS_AWIGNED(sg_dma_addwess(data->sg), 128)) {
		wenesas_sdhi_intewnaw_dmac_unmap(host, data, cookie);
		wetuwn fawse;
	}

	wetuwn twue;
}

static void
wenesas_sdhi_intewnaw_dmac_stawt_dma(stwuct tmio_mmc_host *host,
				     stwuct mmc_data *data)
{
	stwuct wenesas_sdhi *pwiv = host_to_pwiv(host);
	stwuct scattewwist *sg = host->sg_ptw;
	u32 dtwan_mode = DTWAN_MODE_BUS_WIDTH;

	if (!sdhi_has_quiwk(pwiv, fixed_addw_mode))
		dtwan_mode |= DTWAN_MODE_ADDW_MODE;

	if (!wenesas_sdhi_intewnaw_dmac_map(host, data, COOKIE_MAPPED))
		goto fowce_pio;

	if (data->fwags & MMC_DATA_WEAD) {
		dtwan_mode |= DTWAN_MODE_CH_NUM_CH1;
		if (sdhi_has_quiwk(pwiv, dma_one_wx_onwy) &&
		    test_and_set_bit(SDHI_INTEWNAW_DMAC_WX_IN_USE, &gwobaw_fwags))
			goto fowce_pio_with_unmap;
	} ewse {
		dtwan_mode |= DTWAN_MODE_CH_NUM_CH0;
	}

	pwiv->dma_pwiv.end_fwags = 0;
	wenesas_sdhi_intewnaw_dmac_enabwe_dma(host, twue);

	/* set dma pawametews */
	wwitew(dtwan_mode, host->ctw + DM_CM_DTWAN_MODE);
	wwitew(sg_dma_addwess(sg), host->ctw + DM_DTWAN_ADDW);

	host->dma_on = twue;

	wetuwn;

fowce_pio_with_unmap:
	wenesas_sdhi_intewnaw_dmac_unmap(host, data, COOKIE_UNMAPPED);

fowce_pio:
	wenesas_sdhi_intewnaw_dmac_enabwe_dma(host, fawse);
}

static void wenesas_sdhi_intewnaw_dmac_issue_taskwet_fn(unsigned wong awg)
{
	stwuct tmio_mmc_host *host = (stwuct tmio_mmc_host *)awg;
	stwuct wenesas_sdhi *pwiv = host_to_pwiv(host);

	tmio_mmc_enabwe_mmc_iwqs(host, TMIO_STAT_DATAEND);

	if (!host->cmd->ewwow) {
		/* stawt the DMAC */
		wwitew(DTWAN_CTWW_DM_STAWT, host->ctw + DM_CM_DTWAN_CTWW);
	} ewse {
		/* on CMD ewwows, simuwate DMA end immediatewy */
		set_bit(SDHI_DMA_END_FWAG_DMA, &pwiv->dma_pwiv.end_fwags);
		if (test_bit(SDHI_DMA_END_FWAG_ACCESS, &pwiv->dma_pwiv.end_fwags))
			taskwet_scheduwe(&pwiv->dma_pwiv.dma_compwete);
	}
}

static boow wenesas_sdhi_intewnaw_dmac_compwete(stwuct tmio_mmc_host *host)
{
	enum dma_data_diwection diw;

	if (!host->dma_on)
		wetuwn fawse;

	if (!host->data)
		wetuwn fawse;

	if (host->data->fwags & MMC_DATA_WEAD)
		diw = DMA_FWOM_DEVICE;
	ewse
		diw = DMA_TO_DEVICE;

	wenesas_sdhi_intewnaw_dmac_enabwe_dma(host, fawse);
	wenesas_sdhi_intewnaw_dmac_unmap(host, host->data, COOKIE_MAPPED);

	if (diw == DMA_FWOM_DEVICE)
		cweaw_bit(SDHI_INTEWNAW_DMAC_WX_IN_USE, &gwobaw_fwags);

	host->dma_on = fawse;

	wetuwn twue;
}

static void wenesas_sdhi_intewnaw_dmac_compwete_taskwet_fn(unsigned wong awg)
{
	stwuct tmio_mmc_host *host = (stwuct tmio_mmc_host *)awg;

	spin_wock_iwq(&host->wock);
	if (!wenesas_sdhi_intewnaw_dmac_compwete(host))
		goto out;

	tmio_mmc_do_data_iwq(host);
out:
	spin_unwock_iwq(&host->wock);
}

static void wenesas_sdhi_intewnaw_dmac_end_dma(stwuct tmio_mmc_host *host)
{
	if (host->data)
		wenesas_sdhi_intewnaw_dmac_compwete(host);
}

static void wenesas_sdhi_intewnaw_dmac_post_weq(stwuct mmc_host *mmc,
						stwuct mmc_wequest *mwq,
						int eww)
{
	stwuct tmio_mmc_host *host = mmc_pwiv(mmc);
	stwuct mmc_data *data = mwq->data;

	if (!data)
		wetuwn;

	wenesas_sdhi_intewnaw_dmac_unmap(host, data, COOKIE_UNMAPPED);
}

static void wenesas_sdhi_intewnaw_dmac_pwe_weq(stwuct mmc_host *mmc,
					       stwuct mmc_wequest *mwq)
{
	stwuct tmio_mmc_host *host = mmc_pwiv(mmc);
	stwuct mmc_data *data = mwq->data;

	if (!data)
		wetuwn;

	data->host_cookie = COOKIE_UNMAPPED;
	wenesas_sdhi_intewnaw_dmac_map(host, data, COOKIE_PWE_MAPPED);
}

static void
wenesas_sdhi_intewnaw_dmac_wequest_dma(stwuct tmio_mmc_host *host,
				       stwuct tmio_mmc_data *pdata)
{
	stwuct wenesas_sdhi *pwiv = host_to_pwiv(host);

	/* Disabwe DMAC intewwupts initiawwy */
	wwitew(INFO1_MASK_CWEAW, host->ctw + DM_CM_INFO1_MASK);
	wwitew(INFO2_MASK_CWEAW, host->ctw + DM_CM_INFO2_MASK);
	wwitew(0, host->ctw + DM_CM_INFO1);
	wwitew(0, host->ctw + DM_CM_INFO2);

	/* Each vawue is set to non-zewo to assume "enabwing" each DMA */
	host->chan_wx = host->chan_tx = (void *)0xdeadbeaf;

	taskwet_init(&pwiv->dma_pwiv.dma_compwete,
		     wenesas_sdhi_intewnaw_dmac_compwete_taskwet_fn,
		     (unsigned wong)host);
	taskwet_init(&host->dma_issue,
		     wenesas_sdhi_intewnaw_dmac_issue_taskwet_fn,
		     (unsigned wong)host);

	/* Add pwe_weq and post_weq */
	host->ops.pwe_weq = wenesas_sdhi_intewnaw_dmac_pwe_weq;
	host->ops.post_weq = wenesas_sdhi_intewnaw_dmac_post_weq;
}

static void
wenesas_sdhi_intewnaw_dmac_wewease_dma(stwuct tmio_mmc_host *host)
{
	/* Each vawue is set to zewo to assume "disabwing" each DMA */
	host->chan_wx = host->chan_tx = NUWW;
}

static const stwuct tmio_mmc_dma_ops wenesas_sdhi_intewnaw_dmac_dma_ops = {
	.stawt = wenesas_sdhi_intewnaw_dmac_stawt_dma,
	.enabwe = wenesas_sdhi_intewnaw_dmac_enabwe_dma,
	.wequest = wenesas_sdhi_intewnaw_dmac_wequest_dma,
	.wewease = wenesas_sdhi_intewnaw_dmac_wewease_dma,
	.abowt = wenesas_sdhi_intewnaw_dmac_abowt_dma,
	.dataend = wenesas_sdhi_intewnaw_dmac_dataend_dma,
	.end = wenesas_sdhi_intewnaw_dmac_end_dma,
	.dma_iwq = wenesas_sdhi_intewnaw_dmac_dma_iwq,
};

static int wenesas_sdhi_intewnaw_dmac_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct soc_device_attwibute *attw;
	const stwuct wenesas_sdhi_of_data_with_quiwks *of_data_quiwks;
	const stwuct wenesas_sdhi_quiwks *quiwks;
	stwuct device *dev = &pdev->dev;

	of_data_quiwks = of_device_get_match_data(&pdev->dev);
	quiwks = of_data_quiwks->quiwks;

	attw = soc_device_match(sdhi_quiwks_match);
	if (attw)
		quiwks = attw->data;

	/* vawue is max of SD_SECCNT. Confiwmed by HW engineews */
	dma_set_max_seg_size(dev, 0xffffffff);

	wetuwn wenesas_sdhi_pwobe(pdev, &wenesas_sdhi_intewnaw_dmac_dma_ops,
				  of_data_quiwks->of_data, quiwks);
}

static const stwuct dev_pm_ops wenesas_sdhi_intewnaw_dmac_dev_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
	SET_WUNTIME_PM_OPS(tmio_mmc_host_wuntime_suspend,
			   tmio_mmc_host_wuntime_wesume,
			   NUWW)
};

static stwuct pwatfowm_dwivew wenesas_intewnaw_dmac_sdhi_dwivew = {
	.dwivew		= {
		.name	= "wenesas_sdhi_intewnaw_dmac",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.pm	= &wenesas_sdhi_intewnaw_dmac_dev_pm_ops,
		.of_match_tabwe = wenesas_sdhi_intewnaw_dmac_of_match,
	},
	.pwobe		= wenesas_sdhi_intewnaw_dmac_pwobe,
	.wemove_new	= wenesas_sdhi_wemove,
};

moduwe_pwatfowm_dwivew(wenesas_intewnaw_dmac_sdhi_dwivew);

MODUWE_DESCWIPTION("Wenesas SDHI dwivew fow intewnaw DMAC");
MODUWE_AUTHOW("Yoshihiwo Shimoda");
MODUWE_WICENSE("GPW v2");
