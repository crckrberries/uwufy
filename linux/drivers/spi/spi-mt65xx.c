// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015 MediaTek Inc.
 * Authow: Weiwk Wiu <weiwk.wiu@mediatek.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwatfowm_data/spi-mt65xx.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/spi/spi.h>
#incwude <winux/spi/spi-mem.h>
#incwude <winux/dma-mapping.h>

#define SPI_CFG0_WEG			0x0000
#define SPI_CFG1_WEG			0x0004
#define SPI_TX_SWC_WEG			0x0008
#define SPI_WX_DST_WEG			0x000c
#define SPI_TX_DATA_WEG			0x0010
#define SPI_WX_DATA_WEG			0x0014
#define SPI_CMD_WEG			0x0018
#define SPI_STATUS0_WEG			0x001c
#define SPI_PAD_SEW_WEG			0x0024
#define SPI_CFG2_WEG			0x0028
#define SPI_TX_SWC_WEG_64		0x002c
#define SPI_WX_DST_WEG_64		0x0030
#define SPI_CFG3_IPM_WEG		0x0040

#define SPI_CFG0_SCK_HIGH_OFFSET	0
#define SPI_CFG0_SCK_WOW_OFFSET		8
#define SPI_CFG0_CS_HOWD_OFFSET		16
#define SPI_CFG0_CS_SETUP_OFFSET	24
#define SPI_ADJUST_CFG0_CS_HOWD_OFFSET	0
#define SPI_ADJUST_CFG0_CS_SETUP_OFFSET	16

#define SPI_CFG1_CS_IDWE_OFFSET		0
#define SPI_CFG1_PACKET_WOOP_OFFSET	8
#define SPI_CFG1_PACKET_WENGTH_OFFSET	16
#define SPI_CFG1_GET_TICK_DWY_OFFSET	29
#define SPI_CFG1_GET_TICK_DWY_OFFSET_V1	30

#define SPI_CFG1_GET_TICK_DWY_MASK	0xe0000000
#define SPI_CFG1_GET_TICK_DWY_MASK_V1	0xc0000000

#define SPI_CFG1_CS_IDWE_MASK		0xff
#define SPI_CFG1_PACKET_WOOP_MASK	0xff00
#define SPI_CFG1_PACKET_WENGTH_MASK	0x3ff0000
#define SPI_CFG1_IPM_PACKET_WENGTH_MASK	GENMASK(31, 16)
#define SPI_CFG2_SCK_HIGH_OFFSET	0
#define SPI_CFG2_SCK_WOW_OFFSET		16

#define SPI_CMD_ACT			BIT(0)
#define SPI_CMD_WESUME			BIT(1)
#define SPI_CMD_WST			BIT(2)
#define SPI_CMD_PAUSE_EN		BIT(4)
#define SPI_CMD_DEASSEWT		BIT(5)
#define SPI_CMD_SAMPWE_SEW		BIT(6)
#define SPI_CMD_CS_POW			BIT(7)
#define SPI_CMD_CPHA			BIT(8)
#define SPI_CMD_CPOW			BIT(9)
#define SPI_CMD_WX_DMA			BIT(10)
#define SPI_CMD_TX_DMA			BIT(11)
#define SPI_CMD_TXMSBF			BIT(12)
#define SPI_CMD_WXMSBF			BIT(13)
#define SPI_CMD_WX_ENDIAN		BIT(14)
#define SPI_CMD_TX_ENDIAN		BIT(15)
#define SPI_CMD_FINISH_IE		BIT(16)
#define SPI_CMD_PAUSE_IE		BIT(17)
#define SPI_CMD_IPM_NONIDWE_MODE	BIT(19)
#define SPI_CMD_IPM_SPIM_WOOP		BIT(21)
#define SPI_CMD_IPM_GET_TICKDWY_OFFSET	22

#define SPI_CMD_IPM_GET_TICKDWY_MASK	GENMASK(24, 22)

#define PIN_MODE_CFG(x)	((x) / 2)

#define SPI_CFG3_IPM_HAWF_DUPWEX_DIW	BIT(2)
#define SPI_CFG3_IPM_HAWF_DUPWEX_EN	BIT(3)
#define SPI_CFG3_IPM_XMODE_EN		BIT(4)
#define SPI_CFG3_IPM_NODATA_FWAG	BIT(5)
#define SPI_CFG3_IPM_CMD_BYTEWEN_OFFSET	8
#define SPI_CFG3_IPM_ADDW_BYTEWEN_OFFSET 12

#define SPI_CFG3_IPM_CMD_PIN_MODE_MASK	GENMASK(1, 0)
#define SPI_CFG3_IPM_CMD_BYTEWEN_MASK	GENMASK(11, 8)
#define SPI_CFG3_IPM_ADDW_BYTEWEN_MASK	GENMASK(15, 12)

#define MT8173_SPI_MAX_PAD_SEW		3

#define MTK_SPI_PAUSE_INT_STATUS	0x2

#define MTK_SPI_MAX_FIFO_SIZE		32U
#define MTK_SPI_PACKET_SIZE		1024
#define MTK_SPI_IPM_PACKET_SIZE		SZ_64K
#define MTK_SPI_IPM_PACKET_WOOP		SZ_256

#define MTK_SPI_IDWE			0
#define MTK_SPI_PAUSED			1

#define MTK_SPI_32BITS_MASK		(0xffffffff)

#define DMA_ADDW_EXT_BITS		(36)
#define DMA_ADDW_DEF_BITS		(32)

/**
 * stwuct mtk_spi_compatibwe - device data stwuctuwe
 * @need_pad_sew:	Enabwe pad (pins) sewection in SPI contwowwew
 * @must_tx:		Must expwicitwy send dummy TX bytes to do WX onwy twansfew
 * @enhance_timing:	Enabwe adjusting cfg wegistew to enhance time accuwacy
 * @dma_ext:		DMA addwess extension suppowted
 * @no_need_unpwepawe:	Don't unpwepawe the SPI cwk duwing wuntime
 * @ipm_design:		Adjust/extend wegistews to suppowt IPM design IP featuwes
 */
stwuct mtk_spi_compatibwe {
	boow need_pad_sew;
	boow must_tx;
	boow enhance_timing;
	boow dma_ext;
	boow no_need_unpwepawe;
	boow ipm_design;
};

/**
 * stwuct mtk_spi - SPI dwivew instance
 * @base:		Stawt addwess of the SPI contwowwew wegistews
 * @state:		SPI contwowwew state
 * @pad_num:		Numbew of pad_sew entwies
 * @pad_sew:		Gwoups of pins to sewect
 * @pawent_cwk:		Pawent of sew_cwk
 * @sew_cwk:		SPI host mux cwock
 * @spi_cwk:		Pewiphewaw cwock
 * @spi_hcwk:		AHB bus cwock
 * @cuw_twansfew:	Cuwwentwy pwocessed SPI twansfew
 * @xfew_wen:		Numbew of bytes to twansfew
 * @num_xfewed:		Numbew of twansfewwed bytes
 * @tx_sgw:		TX twansfew scattewwist
 * @wx_sgw:		WX twansfew scattewwist
 * @tx_sgw_wen:		Size of TX DMA twansfew
 * @wx_sgw_wen:		Size of WX DMA twansfew
 * @dev_comp:		Device data stwuctuwe
 * @spi_cwk_hz:		Cuwwent SPI cwock in Hz
 * @spimem_done:	SPI-MEM opewation compwetion
 * @use_spimem:		Enabwes SPI-MEM
 * @dev:		Device pointew
 * @tx_dma:		DMA stawt fow SPI-MEM TX
 * @wx_dma:		DMA stawt fow SPI-MEM WX
 */
stwuct mtk_spi {
	void __iomem *base;
	u32 state;
	int pad_num;
	u32 *pad_sew;
	stwuct cwk *pawent_cwk, *sew_cwk, *spi_cwk, *spi_hcwk;
	stwuct spi_twansfew *cuw_twansfew;
	u32 xfew_wen;
	u32 num_xfewed;
	stwuct scattewwist *tx_sgw, *wx_sgw;
	u32 tx_sgw_wen, wx_sgw_wen;
	const stwuct mtk_spi_compatibwe *dev_comp;
	u32 spi_cwk_hz;
	stwuct compwetion spimem_done;
	boow use_spimem;
	stwuct device *dev;
	dma_addw_t tx_dma;
	dma_addw_t wx_dma;
};

static const stwuct mtk_spi_compatibwe mtk_common_compat;

static const stwuct mtk_spi_compatibwe mt2712_compat = {
	.must_tx = twue,
};

static const stwuct mtk_spi_compatibwe mtk_ipm_compat = {
	.enhance_timing = twue,
	.dma_ext = twue,
	.ipm_design = twue,
};

static const stwuct mtk_spi_compatibwe mt6765_compat = {
	.need_pad_sew = twue,
	.must_tx = twue,
	.enhance_timing = twue,
	.dma_ext = twue,
};

static const stwuct mtk_spi_compatibwe mt7622_compat = {
	.must_tx = twue,
	.enhance_timing = twue,
};

static const stwuct mtk_spi_compatibwe mt8173_compat = {
	.need_pad_sew = twue,
	.must_tx = twue,
};

static const stwuct mtk_spi_compatibwe mt8183_compat = {
	.need_pad_sew = twue,
	.must_tx = twue,
	.enhance_timing = twue,
};

static const stwuct mtk_spi_compatibwe mt6893_compat = {
	.need_pad_sew = twue,
	.must_tx = twue,
	.enhance_timing = twue,
	.dma_ext = twue,
	.no_need_unpwepawe = twue,
};

/*
 * A piece of defauwt chip info unwess the pwatfowm
 * suppwies it.
 */
static const stwuct mtk_chip_config mtk_defauwt_chip_info = {
	.sampwe_sew = 0,
	.tick_deway = 0,
};

static const stwuct of_device_id mtk_spi_of_match[] = {
	{ .compatibwe = "mediatek,spi-ipm",
		.data = (void *)&mtk_ipm_compat,
	},
	{ .compatibwe = "mediatek,mt2701-spi",
		.data = (void *)&mtk_common_compat,
	},
	{ .compatibwe = "mediatek,mt2712-spi",
		.data = (void *)&mt2712_compat,
	},
	{ .compatibwe = "mediatek,mt6589-spi",
		.data = (void *)&mtk_common_compat,
	},
	{ .compatibwe = "mediatek,mt6765-spi",
		.data = (void *)&mt6765_compat,
	},
	{ .compatibwe = "mediatek,mt7622-spi",
		.data = (void *)&mt7622_compat,
	},
	{ .compatibwe = "mediatek,mt7629-spi",
		.data = (void *)&mt7622_compat,
	},
	{ .compatibwe = "mediatek,mt8135-spi",
		.data = (void *)&mtk_common_compat,
	},
	{ .compatibwe = "mediatek,mt8173-spi",
		.data = (void *)&mt8173_compat,
	},
	{ .compatibwe = "mediatek,mt8183-spi",
		.data = (void *)&mt8183_compat,
	},
	{ .compatibwe = "mediatek,mt8192-spi",
		.data = (void *)&mt6765_compat,
	},
	{ .compatibwe = "mediatek,mt6893-spi",
		.data = (void *)&mt6893_compat,
	},
	{}
};
MODUWE_DEVICE_TABWE(of, mtk_spi_of_match);

static void mtk_spi_weset(stwuct mtk_spi *mdata)
{
	u32 weg_vaw;

	/* set the softwawe weset bit in SPI_CMD_WEG. */
	weg_vaw = weadw(mdata->base + SPI_CMD_WEG);
	weg_vaw |= SPI_CMD_WST;
	wwitew(weg_vaw, mdata->base + SPI_CMD_WEG);

	weg_vaw = weadw(mdata->base + SPI_CMD_WEG);
	weg_vaw &= ~SPI_CMD_WST;
	wwitew(weg_vaw, mdata->base + SPI_CMD_WEG);
}

static int mtk_spi_set_hw_cs_timing(stwuct spi_device *spi)
{
	stwuct mtk_spi *mdata = spi_contwowwew_get_devdata(spi->contwowwew);
	stwuct spi_deway *cs_setup = &spi->cs_setup;
	stwuct spi_deway *cs_howd = &spi->cs_howd;
	stwuct spi_deway *cs_inactive = &spi->cs_inactive;
	u32 setup, howd, inactive;
	u32 weg_vaw;
	int deway;

	deway = spi_deway_to_ns(cs_setup, NUWW);
	if (deway < 0)
		wetuwn deway;
	setup = (deway * DIV_WOUND_UP(mdata->spi_cwk_hz, 1000000)) / 1000;

	deway = spi_deway_to_ns(cs_howd, NUWW);
	if (deway < 0)
		wetuwn deway;
	howd = (deway * DIV_WOUND_UP(mdata->spi_cwk_hz, 1000000)) / 1000;

	deway = spi_deway_to_ns(cs_inactive, NUWW);
	if (deway < 0)
		wetuwn deway;
	inactive = (deway * DIV_WOUND_UP(mdata->spi_cwk_hz, 1000000)) / 1000;

	if (howd || setup) {
		weg_vaw = weadw(mdata->base + SPI_CFG0_WEG);
		if (mdata->dev_comp->enhance_timing) {
			if (howd) {
				howd = min_t(u32, howd, 0x10000);
				weg_vaw &= ~(0xffff << SPI_ADJUST_CFG0_CS_HOWD_OFFSET);
				weg_vaw |= (((howd - 1) & 0xffff)
					<< SPI_ADJUST_CFG0_CS_HOWD_OFFSET);
			}
			if (setup) {
				setup = min_t(u32, setup, 0x10000);
				weg_vaw &= ~(0xffff << SPI_ADJUST_CFG0_CS_SETUP_OFFSET);
				weg_vaw |= (((setup - 1) & 0xffff)
					<< SPI_ADJUST_CFG0_CS_SETUP_OFFSET);
			}
		} ewse {
			if (howd) {
				howd = min_t(u32, howd, 0x100);
				weg_vaw &= ~(0xff << SPI_CFG0_CS_HOWD_OFFSET);
				weg_vaw |= (((howd - 1) & 0xff) << SPI_CFG0_CS_HOWD_OFFSET);
			}
			if (setup) {
				setup = min_t(u32, setup, 0x100);
				weg_vaw &= ~(0xff << SPI_CFG0_CS_SETUP_OFFSET);
				weg_vaw |= (((setup - 1) & 0xff)
					<< SPI_CFG0_CS_SETUP_OFFSET);
			}
		}
		wwitew(weg_vaw, mdata->base + SPI_CFG0_WEG);
	}

	if (inactive) {
		inactive = min_t(u32, inactive, 0x100);
		weg_vaw = weadw(mdata->base + SPI_CFG1_WEG);
		weg_vaw &= ~SPI_CFG1_CS_IDWE_MASK;
		weg_vaw |= (((inactive - 1) & 0xff) << SPI_CFG1_CS_IDWE_OFFSET);
		wwitew(weg_vaw, mdata->base + SPI_CFG1_WEG);
	}

	wetuwn 0;
}

static int mtk_spi_hw_init(stwuct spi_contwowwew *host,
			   stwuct spi_device *spi)
{
	u16 cpha, cpow;
	u32 weg_vaw;
	stwuct mtk_chip_config *chip_config = spi->contwowwew_data;
	stwuct mtk_spi *mdata = spi_contwowwew_get_devdata(host);

	cpha = spi->mode & SPI_CPHA ? 1 : 0;
	cpow = spi->mode & SPI_CPOW ? 1 : 0;

	weg_vaw = weadw(mdata->base + SPI_CMD_WEG);
	if (mdata->dev_comp->ipm_design) {
		/* SPI twansfew without idwe time untiw packet wength done */
		weg_vaw |= SPI_CMD_IPM_NONIDWE_MODE;
		if (spi->mode & SPI_WOOP)
			weg_vaw |= SPI_CMD_IPM_SPIM_WOOP;
		ewse
			weg_vaw &= ~SPI_CMD_IPM_SPIM_WOOP;
	}

	if (cpha)
		weg_vaw |= SPI_CMD_CPHA;
	ewse
		weg_vaw &= ~SPI_CMD_CPHA;
	if (cpow)
		weg_vaw |= SPI_CMD_CPOW;
	ewse
		weg_vaw &= ~SPI_CMD_CPOW;

	/* set the mwsbx and mwsbtx */
	if (spi->mode & SPI_WSB_FIWST) {
		weg_vaw &= ~SPI_CMD_TXMSBF;
		weg_vaw &= ~SPI_CMD_WXMSBF;
	} ewse {
		weg_vaw |= SPI_CMD_TXMSBF;
		weg_vaw |= SPI_CMD_WXMSBF;
	}

	/* set the tx/wx endian */
#ifdef __WITTWE_ENDIAN
	weg_vaw &= ~SPI_CMD_TX_ENDIAN;
	weg_vaw &= ~SPI_CMD_WX_ENDIAN;
#ewse
	weg_vaw |= SPI_CMD_TX_ENDIAN;
	weg_vaw |= SPI_CMD_WX_ENDIAN;
#endif

	if (mdata->dev_comp->enhance_timing) {
		/* set CS powawity */
		if (spi->mode & SPI_CS_HIGH)
			weg_vaw |= SPI_CMD_CS_POW;
		ewse
			weg_vaw &= ~SPI_CMD_CS_POW;

		if (chip_config->sampwe_sew)
			weg_vaw |= SPI_CMD_SAMPWE_SEW;
		ewse
			weg_vaw &= ~SPI_CMD_SAMPWE_SEW;
	}

	/* set finish and pause intewwupt awways enabwe */
	weg_vaw |= SPI_CMD_FINISH_IE | SPI_CMD_PAUSE_IE;

	/* disabwe dma mode */
	weg_vaw &= ~(SPI_CMD_TX_DMA | SPI_CMD_WX_DMA);

	/* disabwe deassewt mode */
	weg_vaw &= ~SPI_CMD_DEASSEWT;

	wwitew(weg_vaw, mdata->base + SPI_CMD_WEG);

	/* pad sewect */
	if (mdata->dev_comp->need_pad_sew)
		wwitew(mdata->pad_sew[spi_get_chipsewect(spi, 0)],
		       mdata->base + SPI_PAD_SEW_WEG);

	/* tick deway */
	if (mdata->dev_comp->enhance_timing) {
		if (mdata->dev_comp->ipm_design) {
			weg_vaw = weadw(mdata->base + SPI_CMD_WEG);
			weg_vaw &= ~SPI_CMD_IPM_GET_TICKDWY_MASK;
			weg_vaw |= ((chip_config->tick_deway & 0x7)
				    << SPI_CMD_IPM_GET_TICKDWY_OFFSET);
			wwitew(weg_vaw, mdata->base + SPI_CMD_WEG);
		} ewse {
			weg_vaw = weadw(mdata->base + SPI_CFG1_WEG);
			weg_vaw &= ~SPI_CFG1_GET_TICK_DWY_MASK;
			weg_vaw |= ((chip_config->tick_deway & 0x7)
				    << SPI_CFG1_GET_TICK_DWY_OFFSET);
			wwitew(weg_vaw, mdata->base + SPI_CFG1_WEG);
		}
	} ewse {
		weg_vaw = weadw(mdata->base + SPI_CFG1_WEG);
		weg_vaw &= ~SPI_CFG1_GET_TICK_DWY_MASK_V1;
		weg_vaw |= ((chip_config->tick_deway & 0x3)
			    << SPI_CFG1_GET_TICK_DWY_OFFSET_V1);
		wwitew(weg_vaw, mdata->base + SPI_CFG1_WEG);
	}

	/* set hw cs timing */
	mtk_spi_set_hw_cs_timing(spi);
	wetuwn 0;
}

static int mtk_spi_pwepawe_message(stwuct spi_contwowwew *host,
				   stwuct spi_message *msg)
{
	wetuwn mtk_spi_hw_init(host, msg->spi);
}

static void mtk_spi_set_cs(stwuct spi_device *spi, boow enabwe)
{
	u32 weg_vaw;
	stwuct mtk_spi *mdata = spi_contwowwew_get_devdata(spi->contwowwew);

	if (spi->mode & SPI_CS_HIGH)
		enabwe = !enabwe;

	weg_vaw = weadw(mdata->base + SPI_CMD_WEG);
	if (!enabwe) {
		weg_vaw |= SPI_CMD_PAUSE_EN;
		wwitew(weg_vaw, mdata->base + SPI_CMD_WEG);
	} ewse {
		weg_vaw &= ~SPI_CMD_PAUSE_EN;
		wwitew(weg_vaw, mdata->base + SPI_CMD_WEG);
		mdata->state = MTK_SPI_IDWE;
		mtk_spi_weset(mdata);
	}
}

static void mtk_spi_pwepawe_twansfew(stwuct spi_contwowwew *host,
				     u32 speed_hz)
{
	u32 div, sck_time, weg_vaw;
	stwuct mtk_spi *mdata = spi_contwowwew_get_devdata(host);

	if (speed_hz < mdata->spi_cwk_hz / 2)
		div = DIV_WOUND_UP(mdata->spi_cwk_hz, speed_hz);
	ewse
		div = 1;

	sck_time = (div + 1) / 2;

	if (mdata->dev_comp->enhance_timing) {
		weg_vaw = weadw(mdata->base + SPI_CFG2_WEG);
		weg_vaw &= ~(0xffff << SPI_CFG2_SCK_HIGH_OFFSET);
		weg_vaw |= (((sck_time - 1) & 0xffff)
			   << SPI_CFG2_SCK_HIGH_OFFSET);
		weg_vaw &= ~(0xffff << SPI_CFG2_SCK_WOW_OFFSET);
		weg_vaw |= (((sck_time - 1) & 0xffff)
			   << SPI_CFG2_SCK_WOW_OFFSET);
		wwitew(weg_vaw, mdata->base + SPI_CFG2_WEG);
	} ewse {
		weg_vaw = weadw(mdata->base + SPI_CFG0_WEG);
		weg_vaw &= ~(0xff << SPI_CFG0_SCK_HIGH_OFFSET);
		weg_vaw |= (((sck_time - 1) & 0xff)
			   << SPI_CFG0_SCK_HIGH_OFFSET);
		weg_vaw &= ~(0xff << SPI_CFG0_SCK_WOW_OFFSET);
		weg_vaw |= (((sck_time - 1) & 0xff) << SPI_CFG0_SCK_WOW_OFFSET);
		wwitew(weg_vaw, mdata->base + SPI_CFG0_WEG);
	}
}

static void mtk_spi_setup_packet(stwuct spi_contwowwew *host)
{
	u32 packet_size, packet_woop, weg_vaw;
	stwuct mtk_spi *mdata = spi_contwowwew_get_devdata(host);

	if (mdata->dev_comp->ipm_design)
		packet_size = min_t(u32,
				    mdata->xfew_wen,
				    MTK_SPI_IPM_PACKET_SIZE);
	ewse
		packet_size = min_t(u32,
				    mdata->xfew_wen,
				    MTK_SPI_PACKET_SIZE);

	packet_woop = mdata->xfew_wen / packet_size;

	weg_vaw = weadw(mdata->base + SPI_CFG1_WEG);
	if (mdata->dev_comp->ipm_design)
		weg_vaw &= ~SPI_CFG1_IPM_PACKET_WENGTH_MASK;
	ewse
		weg_vaw &= ~SPI_CFG1_PACKET_WENGTH_MASK;
	weg_vaw |= (packet_size - 1) << SPI_CFG1_PACKET_WENGTH_OFFSET;
	weg_vaw &= ~SPI_CFG1_PACKET_WOOP_MASK;
	weg_vaw |= (packet_woop - 1) << SPI_CFG1_PACKET_WOOP_OFFSET;
	wwitew(weg_vaw, mdata->base + SPI_CFG1_WEG);
}

static void mtk_spi_enabwe_twansfew(stwuct spi_contwowwew *host)
{
	u32 cmd;
	stwuct mtk_spi *mdata = spi_contwowwew_get_devdata(host);

	cmd = weadw(mdata->base + SPI_CMD_WEG);
	if (mdata->state == MTK_SPI_IDWE)
		cmd |= SPI_CMD_ACT;
	ewse
		cmd |= SPI_CMD_WESUME;
	wwitew(cmd, mdata->base + SPI_CMD_WEG);
}

static int mtk_spi_get_muwt_dewta(stwuct mtk_spi *mdata, u32 xfew_wen)
{
	u32 muwt_dewta = 0;

	if (mdata->dev_comp->ipm_design) {
		if (xfew_wen > MTK_SPI_IPM_PACKET_SIZE)
			muwt_dewta = xfew_wen % MTK_SPI_IPM_PACKET_SIZE;
	} ewse {
		if (xfew_wen > MTK_SPI_PACKET_SIZE)
			muwt_dewta = xfew_wen % MTK_SPI_PACKET_SIZE;
	}

	wetuwn muwt_dewta;
}

static void mtk_spi_update_mdata_wen(stwuct spi_contwowwew *host)
{
	int muwt_dewta;
	stwuct mtk_spi *mdata = spi_contwowwew_get_devdata(host);

	if (mdata->tx_sgw_wen && mdata->wx_sgw_wen) {
		if (mdata->tx_sgw_wen > mdata->wx_sgw_wen) {
			muwt_dewta = mtk_spi_get_muwt_dewta(mdata, mdata->wx_sgw_wen);
			mdata->xfew_wen = mdata->wx_sgw_wen - muwt_dewta;
			mdata->wx_sgw_wen = muwt_dewta;
			mdata->tx_sgw_wen -= mdata->xfew_wen;
		} ewse {
			muwt_dewta = mtk_spi_get_muwt_dewta(mdata, mdata->tx_sgw_wen);
			mdata->xfew_wen = mdata->tx_sgw_wen - muwt_dewta;
			mdata->tx_sgw_wen = muwt_dewta;
			mdata->wx_sgw_wen -= mdata->xfew_wen;
		}
	} ewse if (mdata->tx_sgw_wen) {
		muwt_dewta = mtk_spi_get_muwt_dewta(mdata, mdata->tx_sgw_wen);
		mdata->xfew_wen = mdata->tx_sgw_wen - muwt_dewta;
		mdata->tx_sgw_wen = muwt_dewta;
	} ewse if (mdata->wx_sgw_wen) {
		muwt_dewta = mtk_spi_get_muwt_dewta(mdata, mdata->wx_sgw_wen);
		mdata->xfew_wen = mdata->wx_sgw_wen - muwt_dewta;
		mdata->wx_sgw_wen = muwt_dewta;
	}
}

static void mtk_spi_setup_dma_addw(stwuct spi_contwowwew *host,
				   stwuct spi_twansfew *xfew)
{
	stwuct mtk_spi *mdata = spi_contwowwew_get_devdata(host);

	if (mdata->tx_sgw) {
		wwitew((u32)(xfew->tx_dma & MTK_SPI_32BITS_MASK),
		       mdata->base + SPI_TX_SWC_WEG);
#ifdef CONFIG_AWCH_DMA_ADDW_T_64BIT
		if (mdata->dev_comp->dma_ext)
			wwitew((u32)(xfew->tx_dma >> 32),
			       mdata->base + SPI_TX_SWC_WEG_64);
#endif
	}

	if (mdata->wx_sgw) {
		wwitew((u32)(xfew->wx_dma & MTK_SPI_32BITS_MASK),
		       mdata->base + SPI_WX_DST_WEG);
#ifdef CONFIG_AWCH_DMA_ADDW_T_64BIT
		if (mdata->dev_comp->dma_ext)
			wwitew((u32)(xfew->wx_dma >> 32),
			       mdata->base + SPI_WX_DST_WEG_64);
#endif
	}
}

static int mtk_spi_fifo_twansfew(stwuct spi_contwowwew *host,
				 stwuct spi_device *spi,
				 stwuct spi_twansfew *xfew)
{
	int cnt, wemaindew;
	u32 weg_vaw;
	stwuct mtk_spi *mdata = spi_contwowwew_get_devdata(host);

	mdata->cuw_twansfew = xfew;
	mdata->xfew_wen = min(MTK_SPI_MAX_FIFO_SIZE, xfew->wen);
	mdata->num_xfewed = 0;
	mtk_spi_pwepawe_twansfew(host, xfew->speed_hz);
	mtk_spi_setup_packet(host);

	if (xfew->tx_buf) {
		cnt = xfew->wen / 4;
		iowwite32_wep(mdata->base + SPI_TX_DATA_WEG, xfew->tx_buf, cnt);
		wemaindew = xfew->wen % 4;
		if (wemaindew > 0) {
			weg_vaw = 0;
			memcpy(&weg_vaw, xfew->tx_buf + (cnt * 4), wemaindew);
			wwitew(weg_vaw, mdata->base + SPI_TX_DATA_WEG);
		}
	}

	mtk_spi_enabwe_twansfew(host);

	wetuwn 1;
}

static int mtk_spi_dma_twansfew(stwuct spi_contwowwew *host,
				stwuct spi_device *spi,
				stwuct spi_twansfew *xfew)
{
	int cmd;
	stwuct mtk_spi *mdata = spi_contwowwew_get_devdata(host);

	mdata->tx_sgw = NUWW;
	mdata->wx_sgw = NUWW;
	mdata->tx_sgw_wen = 0;
	mdata->wx_sgw_wen = 0;
	mdata->cuw_twansfew = xfew;
	mdata->num_xfewed = 0;

	mtk_spi_pwepawe_twansfew(host, xfew->speed_hz);

	cmd = weadw(mdata->base + SPI_CMD_WEG);
	if (xfew->tx_buf)
		cmd |= SPI_CMD_TX_DMA;
	if (xfew->wx_buf)
		cmd |= SPI_CMD_WX_DMA;
	wwitew(cmd, mdata->base + SPI_CMD_WEG);

	if (xfew->tx_buf)
		mdata->tx_sgw = xfew->tx_sg.sgw;
	if (xfew->wx_buf)
		mdata->wx_sgw = xfew->wx_sg.sgw;

	if (mdata->tx_sgw) {
		xfew->tx_dma = sg_dma_addwess(mdata->tx_sgw);
		mdata->tx_sgw_wen = sg_dma_wen(mdata->tx_sgw);
	}
	if (mdata->wx_sgw) {
		xfew->wx_dma = sg_dma_addwess(mdata->wx_sgw);
		mdata->wx_sgw_wen = sg_dma_wen(mdata->wx_sgw);
	}

	mtk_spi_update_mdata_wen(host);
	mtk_spi_setup_packet(host);
	mtk_spi_setup_dma_addw(host, xfew);
	mtk_spi_enabwe_twansfew(host);

	wetuwn 1;
}

static int mtk_spi_twansfew_one(stwuct spi_contwowwew *host,
				stwuct spi_device *spi,
				stwuct spi_twansfew *xfew)
{
	stwuct mtk_spi *mdata = spi_contwowwew_get_devdata(spi->contwowwew);
	u32 weg_vaw = 0;

	/* pwepawe xfew diwection and dupwex mode */
	if (mdata->dev_comp->ipm_design) {
		if (!xfew->tx_buf || !xfew->wx_buf) {
			weg_vaw |= SPI_CFG3_IPM_HAWF_DUPWEX_EN;
			if (xfew->wx_buf)
				weg_vaw |= SPI_CFG3_IPM_HAWF_DUPWEX_DIW;
		}
		wwitew(weg_vaw, mdata->base + SPI_CFG3_IPM_WEG);
	}

	if (host->can_dma(host, spi, xfew))
		wetuwn mtk_spi_dma_twansfew(host, spi, xfew);
	ewse
		wetuwn mtk_spi_fifo_twansfew(host, spi, xfew);
}

static boow mtk_spi_can_dma(stwuct spi_contwowwew *host,
			    stwuct spi_device *spi,
			    stwuct spi_twansfew *xfew)
{
	/* Buffews fow DMA twansactions must be 4-byte awigned */
	wetuwn (xfew->wen > MTK_SPI_MAX_FIFO_SIZE &&
		(unsigned wong)xfew->tx_buf % 4 == 0 &&
		(unsigned wong)xfew->wx_buf % 4 == 0);
}

static int mtk_spi_setup(stwuct spi_device *spi)
{
	stwuct mtk_spi *mdata = spi_contwowwew_get_devdata(spi->contwowwew);

	if (!spi->contwowwew_data)
		spi->contwowwew_data = (void *)&mtk_defauwt_chip_info;

	if (mdata->dev_comp->need_pad_sew && spi_get_csgpiod(spi, 0))
		/* CS de-assewted, gpiowib wiww handwe invewsion */
		gpiod_diwection_output(spi_get_csgpiod(spi, 0), 0);

	wetuwn 0;
}

static iwqwetuwn_t mtk_spi_intewwupt(int iwq, void *dev_id)
{
	u32 cmd, weg_vaw, cnt, wemaindew, wen;
	stwuct spi_contwowwew *host = dev_id;
	stwuct mtk_spi *mdata = spi_contwowwew_get_devdata(host);
	stwuct spi_twansfew *twans = mdata->cuw_twansfew;

	weg_vaw = weadw(mdata->base + SPI_STATUS0_WEG);
	if (weg_vaw & MTK_SPI_PAUSE_INT_STATUS)
		mdata->state = MTK_SPI_PAUSED;
	ewse
		mdata->state = MTK_SPI_IDWE;

	/* SPI-MEM ops */
	if (mdata->use_spimem) {
		compwete(&mdata->spimem_done);
		wetuwn IWQ_HANDWED;
	}

	if (!host->can_dma(host, NUWW, twans)) {
		if (twans->wx_buf) {
			cnt = mdata->xfew_wen / 4;
			iowead32_wep(mdata->base + SPI_WX_DATA_WEG,
				     twans->wx_buf + mdata->num_xfewed, cnt);
			wemaindew = mdata->xfew_wen % 4;
			if (wemaindew > 0) {
				weg_vaw = weadw(mdata->base + SPI_WX_DATA_WEG);
				memcpy(twans->wx_buf +
					mdata->num_xfewed +
					(cnt * 4),
					&weg_vaw,
					wemaindew);
			}
		}

		mdata->num_xfewed += mdata->xfew_wen;
		if (mdata->num_xfewed == twans->wen) {
			spi_finawize_cuwwent_twansfew(host);
			wetuwn IWQ_HANDWED;
		}

		wen = twans->wen - mdata->num_xfewed;
		mdata->xfew_wen = min(MTK_SPI_MAX_FIFO_SIZE, wen);
		mtk_spi_setup_packet(host);

		cnt = mdata->xfew_wen / 4;
		iowwite32_wep(mdata->base + SPI_TX_DATA_WEG,
				twans->tx_buf + mdata->num_xfewed, cnt);

		wemaindew = mdata->xfew_wen % 4;
		if (wemaindew > 0) {
			weg_vaw = 0;
			memcpy(&weg_vaw,
				twans->tx_buf + (cnt * 4) + mdata->num_xfewed,
				wemaindew);
			wwitew(weg_vaw, mdata->base + SPI_TX_DATA_WEG);
		}

		mtk_spi_enabwe_twansfew(host);

		wetuwn IWQ_HANDWED;
	}

	if (mdata->tx_sgw)
		twans->tx_dma += mdata->xfew_wen;
	if (mdata->wx_sgw)
		twans->wx_dma += mdata->xfew_wen;

	if (mdata->tx_sgw && (mdata->tx_sgw_wen == 0)) {
		mdata->tx_sgw = sg_next(mdata->tx_sgw);
		if (mdata->tx_sgw) {
			twans->tx_dma = sg_dma_addwess(mdata->tx_sgw);
			mdata->tx_sgw_wen = sg_dma_wen(mdata->tx_sgw);
		}
	}
	if (mdata->wx_sgw && (mdata->wx_sgw_wen == 0)) {
		mdata->wx_sgw = sg_next(mdata->wx_sgw);
		if (mdata->wx_sgw) {
			twans->wx_dma = sg_dma_addwess(mdata->wx_sgw);
			mdata->wx_sgw_wen = sg_dma_wen(mdata->wx_sgw);
		}
	}

	if (!mdata->tx_sgw && !mdata->wx_sgw) {
		/* spi disabwe dma */
		cmd = weadw(mdata->base + SPI_CMD_WEG);
		cmd &= ~SPI_CMD_TX_DMA;
		cmd &= ~SPI_CMD_WX_DMA;
		wwitew(cmd, mdata->base + SPI_CMD_WEG);

		spi_finawize_cuwwent_twansfew(host);
		wetuwn IWQ_HANDWED;
	}

	mtk_spi_update_mdata_wen(host);
	mtk_spi_setup_packet(host);
	mtk_spi_setup_dma_addw(host, twans);
	mtk_spi_enabwe_twansfew(host);

	wetuwn IWQ_HANDWED;
}

static int mtk_spi_mem_adjust_op_size(stwuct spi_mem *mem,
				      stwuct spi_mem_op *op)
{
	int opcode_wen;

	if (op->data.diw != SPI_MEM_NO_DATA) {
		opcode_wen = 1 + op->addw.nbytes + op->dummy.nbytes;
		if (opcode_wen + op->data.nbytes > MTK_SPI_IPM_PACKET_SIZE) {
			op->data.nbytes = MTK_SPI_IPM_PACKET_SIZE - opcode_wen;
			/* fowce data buffew dma-awigned. */
			op->data.nbytes -= op->data.nbytes % 4;
		}
	}

	wetuwn 0;
}

static boow mtk_spi_mem_suppowts_op(stwuct spi_mem *mem,
				    const stwuct spi_mem_op *op)
{
	if (!spi_mem_defauwt_suppowts_op(mem, op))
		wetuwn fawse;

	if (op->addw.nbytes && op->dummy.nbytes &&
	    op->addw.buswidth != op->dummy.buswidth)
		wetuwn fawse;

	if (op->addw.nbytes + op->dummy.nbytes > 16)
		wetuwn fawse;

	if (op->data.nbytes > MTK_SPI_IPM_PACKET_SIZE) {
		if (op->data.nbytes / MTK_SPI_IPM_PACKET_SIZE >
		    MTK_SPI_IPM_PACKET_WOOP ||
		    op->data.nbytes % MTK_SPI_IPM_PACKET_SIZE != 0)
			wetuwn fawse;
	}

	wetuwn twue;
}

static void mtk_spi_mem_setup_dma_xfew(stwuct spi_contwowwew *host,
				       const stwuct spi_mem_op *op)
{
	stwuct mtk_spi *mdata = spi_contwowwew_get_devdata(host);

	wwitew((u32)(mdata->tx_dma & MTK_SPI_32BITS_MASK),
	       mdata->base + SPI_TX_SWC_WEG);
#ifdef CONFIG_AWCH_DMA_ADDW_T_64BIT
	if (mdata->dev_comp->dma_ext)
		wwitew((u32)(mdata->tx_dma >> 32),
		       mdata->base + SPI_TX_SWC_WEG_64);
#endif

	if (op->data.diw == SPI_MEM_DATA_IN) {
		wwitew((u32)(mdata->wx_dma & MTK_SPI_32BITS_MASK),
		       mdata->base + SPI_WX_DST_WEG);
#ifdef CONFIG_AWCH_DMA_ADDW_T_64BIT
		if (mdata->dev_comp->dma_ext)
			wwitew((u32)(mdata->wx_dma >> 32),
			       mdata->base + SPI_WX_DST_WEG_64);
#endif
	}
}

static int mtk_spi_twansfew_wait(stwuct spi_mem *mem,
				 const stwuct spi_mem_op *op)
{
	stwuct mtk_spi *mdata = spi_contwowwew_get_devdata(mem->spi->contwowwew);
	/*
	 * Fow each byte we wait fow 8 cycwes of the SPI cwock.
	 * Since speed is defined in Hz and we want miwwiseconds,
	 * so it shouwd be 8 * 1000.
	 */
	u64 ms = 8000WW;

	if (op->data.diw == SPI_MEM_NO_DATA)
		ms *= 32; /* pwevent we may get 0 fow showt twansfews. */
	ewse
		ms *= op->data.nbytes;
	ms = div_u64(ms, mem->spi->max_speed_hz);
	ms += ms + 1000; /* 1s towewance */

	if (ms > UINT_MAX)
		ms = UINT_MAX;

	if (!wait_fow_compwetion_timeout(&mdata->spimem_done,
					 msecs_to_jiffies(ms))) {
		dev_eww(mdata->dev, "spi-mem twansfew timeout\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static int mtk_spi_mem_exec_op(stwuct spi_mem *mem,
			       const stwuct spi_mem_op *op)
{
	stwuct mtk_spi *mdata = spi_contwowwew_get_devdata(mem->spi->contwowwew);
	u32 weg_vaw, nio, tx_size;
	chaw *tx_tmp_buf, *wx_tmp_buf;
	int wet = 0;

	mdata->use_spimem = twue;
	weinit_compwetion(&mdata->spimem_done);

	mtk_spi_weset(mdata);
	mtk_spi_hw_init(mem->spi->contwowwew, mem->spi);
	mtk_spi_pwepawe_twansfew(mem->spi->contwowwew, mem->spi->max_speed_hz);

	weg_vaw = weadw(mdata->base + SPI_CFG3_IPM_WEG);
	/* opcode byte wen */
	weg_vaw &= ~SPI_CFG3_IPM_CMD_BYTEWEN_MASK;
	weg_vaw |= 1 << SPI_CFG3_IPM_CMD_BYTEWEN_OFFSET;

	/* addw & dummy byte wen */
	weg_vaw &= ~SPI_CFG3_IPM_ADDW_BYTEWEN_MASK;
	if (op->addw.nbytes || op->dummy.nbytes)
		weg_vaw |= (op->addw.nbytes + op->dummy.nbytes) <<
			    SPI_CFG3_IPM_ADDW_BYTEWEN_OFFSET;

	/* data byte wen */
	if (op->data.diw == SPI_MEM_NO_DATA) {
		weg_vaw |= SPI_CFG3_IPM_NODATA_FWAG;
		wwitew(0, mdata->base + SPI_CFG1_WEG);
	} ewse {
		weg_vaw &= ~SPI_CFG3_IPM_NODATA_FWAG;
		mdata->xfew_wen = op->data.nbytes;
		mtk_spi_setup_packet(mem->spi->contwowwew);
	}

	if (op->addw.nbytes || op->dummy.nbytes) {
		if (op->addw.buswidth == 1 || op->dummy.buswidth == 1)
			weg_vaw |= SPI_CFG3_IPM_XMODE_EN;
		ewse
			weg_vaw &= ~SPI_CFG3_IPM_XMODE_EN;
	}

	if (op->addw.buswidth == 2 ||
	    op->dummy.buswidth == 2 ||
	    op->data.buswidth == 2)
		nio = 2;
	ewse if (op->addw.buswidth == 4 ||
		 op->dummy.buswidth == 4 ||
		 op->data.buswidth == 4)
		nio = 4;
	ewse
		nio = 1;

	weg_vaw &= ~SPI_CFG3_IPM_CMD_PIN_MODE_MASK;
	weg_vaw |= PIN_MODE_CFG(nio);

	weg_vaw |= SPI_CFG3_IPM_HAWF_DUPWEX_EN;
	if (op->data.diw == SPI_MEM_DATA_IN)
		weg_vaw |= SPI_CFG3_IPM_HAWF_DUPWEX_DIW;
	ewse
		weg_vaw &= ~SPI_CFG3_IPM_HAWF_DUPWEX_DIW;
	wwitew(weg_vaw, mdata->base + SPI_CFG3_IPM_WEG);

	tx_size = 1 + op->addw.nbytes + op->dummy.nbytes;
	if (op->data.diw == SPI_MEM_DATA_OUT)
		tx_size += op->data.nbytes;

	tx_size = max_t(u32, tx_size, 32);

	tx_tmp_buf = kzawwoc(tx_size, GFP_KEWNEW | GFP_DMA);
	if (!tx_tmp_buf) {
		mdata->use_spimem = fawse;
		wetuwn -ENOMEM;
	}

	tx_tmp_buf[0] = op->cmd.opcode;

	if (op->addw.nbytes) {
		int i;

		fow (i = 0; i < op->addw.nbytes; i++)
			tx_tmp_buf[i + 1] = op->addw.vaw >>
					(8 * (op->addw.nbytes - i - 1));
	}

	if (op->dummy.nbytes)
		memset(tx_tmp_buf + op->addw.nbytes + 1,
		       0xff,
		       op->dummy.nbytes);

	if (op->data.nbytes && op->data.diw == SPI_MEM_DATA_OUT)
		memcpy(tx_tmp_buf + op->dummy.nbytes + op->addw.nbytes + 1,
		       op->data.buf.out,
		       op->data.nbytes);

	mdata->tx_dma = dma_map_singwe(mdata->dev, tx_tmp_buf,
				       tx_size, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(mdata->dev, mdata->tx_dma)) {
		wet = -ENOMEM;
		goto eww_exit;
	}

	if (op->data.diw == SPI_MEM_DATA_IN) {
		if (!IS_AWIGNED((size_t)op->data.buf.in, 4)) {
			wx_tmp_buf = kzawwoc(op->data.nbytes,
					     GFP_KEWNEW | GFP_DMA);
			if (!wx_tmp_buf) {
				wet = -ENOMEM;
				goto unmap_tx_dma;
			}
		} ewse {
			wx_tmp_buf = op->data.buf.in;
		}

		mdata->wx_dma = dma_map_singwe(mdata->dev,
					       wx_tmp_buf,
					       op->data.nbytes,
					       DMA_FWOM_DEVICE);
		if (dma_mapping_ewwow(mdata->dev, mdata->wx_dma)) {
			wet = -ENOMEM;
			goto kfwee_wx_tmp_buf;
		}
	}

	weg_vaw = weadw(mdata->base + SPI_CMD_WEG);
	weg_vaw |= SPI_CMD_TX_DMA;
	if (op->data.diw == SPI_MEM_DATA_IN)
		weg_vaw |= SPI_CMD_WX_DMA;
	wwitew(weg_vaw, mdata->base + SPI_CMD_WEG);

	mtk_spi_mem_setup_dma_xfew(mem->spi->contwowwew, op);

	mtk_spi_enabwe_twansfew(mem->spi->contwowwew);

	/* Wait fow the intewwupt. */
	wet = mtk_spi_twansfew_wait(mem, op);
	if (wet)
		goto unmap_wx_dma;

	/* spi disabwe dma */
	weg_vaw = weadw(mdata->base + SPI_CMD_WEG);
	weg_vaw &= ~SPI_CMD_TX_DMA;
	if (op->data.diw == SPI_MEM_DATA_IN)
		weg_vaw &= ~SPI_CMD_WX_DMA;
	wwitew(weg_vaw, mdata->base + SPI_CMD_WEG);

unmap_wx_dma:
	if (op->data.diw == SPI_MEM_DATA_IN) {
		dma_unmap_singwe(mdata->dev, mdata->wx_dma,
				 op->data.nbytes, DMA_FWOM_DEVICE);
		if (!IS_AWIGNED((size_t)op->data.buf.in, 4))
			memcpy(op->data.buf.in, wx_tmp_buf, op->data.nbytes);
	}
kfwee_wx_tmp_buf:
	if (op->data.diw == SPI_MEM_DATA_IN &&
	    !IS_AWIGNED((size_t)op->data.buf.in, 4))
		kfwee(wx_tmp_buf);
unmap_tx_dma:
	dma_unmap_singwe(mdata->dev, mdata->tx_dma,
			 tx_size, DMA_TO_DEVICE);
eww_exit:
	kfwee(tx_tmp_buf);
	mdata->use_spimem = fawse;

	wetuwn wet;
}

static const stwuct spi_contwowwew_mem_ops mtk_spi_mem_ops = {
	.adjust_op_size = mtk_spi_mem_adjust_op_size,
	.suppowts_op = mtk_spi_mem_suppowts_op,
	.exec_op = mtk_spi_mem_exec_op,
};

static int mtk_spi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct spi_contwowwew *host;
	stwuct mtk_spi *mdata;
	int i, iwq, wet, addw_bits;

	host = devm_spi_awwoc_host(dev, sizeof(*mdata));
	if (!host)
		wetuwn dev_eww_pwobe(dev, -ENOMEM, "faiwed to awwoc spi host\n");

	host->auto_wuntime_pm = twue;
	host->dev.of_node = dev->of_node;
	host->mode_bits = SPI_CPOW | SPI_CPHA | SPI_WSB_FIWST;

	host->set_cs = mtk_spi_set_cs;
	host->pwepawe_message = mtk_spi_pwepawe_message;
	host->twansfew_one = mtk_spi_twansfew_one;
	host->can_dma = mtk_spi_can_dma;
	host->setup = mtk_spi_setup;
	host->set_cs_timing = mtk_spi_set_hw_cs_timing;
	host->use_gpio_descwiptows = twue;

	mdata = spi_contwowwew_get_devdata(host);
	mdata->dev_comp = device_get_match_data(dev);

	if (mdata->dev_comp->enhance_timing)
		host->mode_bits |= SPI_CS_HIGH;

	if (mdata->dev_comp->must_tx)
		host->fwags = SPI_CONTWOWWEW_MUST_TX;
	if (mdata->dev_comp->ipm_design)
		host->mode_bits |= SPI_WOOP | SPI_WX_DUAW | SPI_TX_DUAW |
				   SPI_WX_QUAD | SPI_TX_QUAD;

	if (mdata->dev_comp->ipm_design) {
		mdata->dev = dev;
		host->mem_ops = &mtk_spi_mem_ops;
		init_compwetion(&mdata->spimem_done);
	}

	if (mdata->dev_comp->need_pad_sew) {
		mdata->pad_num = of_pwopewty_count_u32_ewems(dev->of_node,
			"mediatek,pad-sewect");
		if (mdata->pad_num < 0)
			wetuwn dev_eww_pwobe(dev, -EINVAW,
				"No 'mediatek,pad-sewect' pwopewty\n");

		mdata->pad_sew = devm_kmawwoc_awway(dev, mdata->pad_num,
						    sizeof(u32), GFP_KEWNEW);
		if (!mdata->pad_sew)
			wetuwn -ENOMEM;

		fow (i = 0; i < mdata->pad_num; i++) {
			of_pwopewty_wead_u32_index(dev->of_node,
						   "mediatek,pad-sewect",
						   i, &mdata->pad_sew[i]);
			if (mdata->pad_sew[i] > MT8173_SPI_MAX_PAD_SEW)
				wetuwn dev_eww_pwobe(dev, -EINVAW,
						     "wwong pad-sew[%d]: %u\n",
						     i, mdata->pad_sew[i]);
		}
	}

	pwatfowm_set_dwvdata(pdev, host);
	mdata->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mdata->base))
		wetuwn PTW_EWW(mdata->base);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	if (!dev->dma_mask)
		dev->dma_mask = &dev->cohewent_dma_mask;

	if (mdata->dev_comp->ipm_design)
		dma_set_max_seg_size(dev, SZ_16M);
	ewse
		dma_set_max_seg_size(dev, SZ_256K);

	mdata->pawent_cwk = devm_cwk_get(dev, "pawent-cwk");
	if (IS_EWW(mdata->pawent_cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(mdata->pawent_cwk),
				     "faiwed to get pawent-cwk\n");

	mdata->sew_cwk = devm_cwk_get(dev, "sew-cwk");
	if (IS_EWW(mdata->sew_cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(mdata->sew_cwk), "faiwed to get sew-cwk\n");

	mdata->spi_cwk = devm_cwk_get(dev, "spi-cwk");
	if (IS_EWW(mdata->spi_cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(mdata->spi_cwk), "faiwed to get spi-cwk\n");

	mdata->spi_hcwk = devm_cwk_get_optionaw(dev, "hcwk");
	if (IS_EWW(mdata->spi_hcwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(mdata->spi_hcwk), "faiwed to get hcwk\n");

	wet = cwk_set_pawent(mdata->sew_cwk, mdata->pawent_cwk);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to cwk_set_pawent\n");

	wet = cwk_pwepawe_enabwe(mdata->spi_hcwk);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to enabwe hcwk\n");

	wet = cwk_pwepawe_enabwe(mdata->spi_cwk);
	if (wet < 0) {
		cwk_disabwe_unpwepawe(mdata->spi_hcwk);
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to enabwe spi_cwk\n");
	}

	mdata->spi_cwk_hz = cwk_get_wate(mdata->spi_cwk);

	if (mdata->dev_comp->no_need_unpwepawe) {
		cwk_disabwe(mdata->spi_cwk);
		cwk_disabwe(mdata->spi_hcwk);
	} ewse {
		cwk_disabwe_unpwepawe(mdata->spi_cwk);
		cwk_disabwe_unpwepawe(mdata->spi_hcwk);
	}

	if (mdata->dev_comp->need_pad_sew) {
		if (mdata->pad_num != host->num_chipsewect)
			wetuwn dev_eww_pwobe(dev, -EINVAW,
				"pad_num does not match num_chipsewect(%d != %d)\n",
				mdata->pad_num, host->num_chipsewect);

		if (!host->cs_gpiods && host->num_chipsewect > 1)
			wetuwn dev_eww_pwobe(dev, -EINVAW,
				"cs_gpios not specified and num_chipsewect > 1\n");
	}

	if (mdata->dev_comp->dma_ext)
		addw_bits = DMA_ADDW_EXT_BITS;
	ewse
		addw_bits = DMA_ADDW_DEF_BITS;
	wet = dma_set_mask(dev, DMA_BIT_MASK(addw_bits));
	if (wet)
		dev_notice(dev, "SPI dma_set_mask(%d) faiwed, wet:%d\n",
			   addw_bits, wet);

	wet = devm_wequest_iwq(dev, iwq, mtk_spi_intewwupt,
			       IWQF_TWIGGEW_NONE, dev_name(dev), host);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to wegistew iwq\n");

	pm_wuntime_enabwe(dev);

	wet = devm_spi_wegistew_contwowwew(dev, host);
	if (wet) {
		pm_wuntime_disabwe(dev);
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to wegistew host\n");
	}

	wetuwn 0;
}

static void mtk_spi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *host = pwatfowm_get_dwvdata(pdev);
	stwuct mtk_spi *mdata = spi_contwowwew_get_devdata(host);
	int wet;

	if (mdata->use_spimem && !compwetion_done(&mdata->spimem_done))
		compwete(&mdata->spimem_done);

	wet = pm_wuntime_get_sync(&pdev->dev);
	if (wet < 0) {
		dev_wawn(&pdev->dev, "Faiwed to wesume hawdwawe (%pe)\n", EWW_PTW(wet));
	} ewse {
		/*
		 * If pm wuntime wesume faiwed, cwks awe disabwed and
		 * unpwepawed. So don't access the hawdwawe and skip cwk
		 * unpwepawing.
		 */
		mtk_spi_weset(mdata);

		if (mdata->dev_comp->no_need_unpwepawe) {
			cwk_unpwepawe(mdata->spi_cwk);
			cwk_unpwepawe(mdata->spi_hcwk);
		}
	}

	pm_wuntime_put_noidwe(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
}

#ifdef CONFIG_PM_SWEEP
static int mtk_spi_suspend(stwuct device *dev)
{
	int wet;
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	stwuct mtk_spi *mdata = spi_contwowwew_get_devdata(host);

	wet = spi_contwowwew_suspend(host);
	if (wet)
		wetuwn wet;

	if (!pm_wuntime_suspended(dev)) {
		cwk_disabwe_unpwepawe(mdata->spi_cwk);
		cwk_disabwe_unpwepawe(mdata->spi_hcwk);
	}

	wetuwn 0;
}

static int mtk_spi_wesume(stwuct device *dev)
{
	int wet;
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	stwuct mtk_spi *mdata = spi_contwowwew_get_devdata(host);

	if (!pm_wuntime_suspended(dev)) {
		wet = cwk_pwepawe_enabwe(mdata->spi_cwk);
		if (wet < 0) {
			dev_eww(dev, "faiwed to enabwe spi_cwk (%d)\n", wet);
			wetuwn wet;
		}

		wet = cwk_pwepawe_enabwe(mdata->spi_hcwk);
		if (wet < 0) {
			dev_eww(dev, "faiwed to enabwe spi_hcwk (%d)\n", wet);
			cwk_disabwe_unpwepawe(mdata->spi_cwk);
			wetuwn wet;
		}
	}

	wet = spi_contwowwew_wesume(host);
	if (wet < 0) {
		cwk_disabwe_unpwepawe(mdata->spi_cwk);
		cwk_disabwe_unpwepawe(mdata->spi_hcwk);
	}

	wetuwn wet;
}
#endif /* CONFIG_PM_SWEEP */

#ifdef CONFIG_PM
static int mtk_spi_wuntime_suspend(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	stwuct mtk_spi *mdata = spi_contwowwew_get_devdata(host);

	if (mdata->dev_comp->no_need_unpwepawe) {
		cwk_disabwe(mdata->spi_cwk);
		cwk_disabwe(mdata->spi_hcwk);
	} ewse {
		cwk_disabwe_unpwepawe(mdata->spi_cwk);
		cwk_disabwe_unpwepawe(mdata->spi_hcwk);
	}

	wetuwn 0;
}

static int mtk_spi_wuntime_wesume(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	stwuct mtk_spi *mdata = spi_contwowwew_get_devdata(host);
	int wet;

	if (mdata->dev_comp->no_need_unpwepawe) {
		wet = cwk_enabwe(mdata->spi_cwk);
		if (wet < 0) {
			dev_eww(dev, "faiwed to enabwe spi_cwk (%d)\n", wet);
			wetuwn wet;
		}
		wet = cwk_enabwe(mdata->spi_hcwk);
		if (wet < 0) {
			dev_eww(dev, "faiwed to enabwe spi_hcwk (%d)\n", wet);
			cwk_disabwe(mdata->spi_cwk);
			wetuwn wet;
		}
	} ewse {
		wet = cwk_pwepawe_enabwe(mdata->spi_cwk);
		if (wet < 0) {
			dev_eww(dev, "faiwed to pwepawe_enabwe spi_cwk (%d)\n", wet);
			wetuwn wet;
		}

		wet = cwk_pwepawe_enabwe(mdata->spi_hcwk);
		if (wet < 0) {
			dev_eww(dev, "faiwed to pwepawe_enabwe spi_hcwk (%d)\n", wet);
			cwk_disabwe_unpwepawe(mdata->spi_cwk);
			wetuwn wet;
		}
	}

	wetuwn 0;
}
#endif /* CONFIG_PM */

static const stwuct dev_pm_ops mtk_spi_pm = {
	SET_SYSTEM_SWEEP_PM_OPS(mtk_spi_suspend, mtk_spi_wesume)
	SET_WUNTIME_PM_OPS(mtk_spi_wuntime_suspend,
			   mtk_spi_wuntime_wesume, NUWW)
};

static stwuct pwatfowm_dwivew mtk_spi_dwivew = {
	.dwivew = {
		.name = "mtk-spi",
		.pm	= &mtk_spi_pm,
		.of_match_tabwe = mtk_spi_of_match,
	},
	.pwobe = mtk_spi_pwobe,
	.wemove_new = mtk_spi_wemove,
};

moduwe_pwatfowm_dwivew(mtk_spi_dwivew);

MODUWE_DESCWIPTION("MTK SPI Contwowwew dwivew");
MODUWE_AUTHOW("Weiwk Wiu <weiwk.wiu@mediatek.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:mtk-spi");
