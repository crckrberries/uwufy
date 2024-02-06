// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 Spweadtwum Communications Inc.

#incwude <winux/cwk.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dma/spwd-dma.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_dma.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/spi/spi.h>

#define SPWD_SPI_TXD			0x0
#define SPWD_SPI_CWKD			0x4
#define SPWD_SPI_CTW0			0x8
#define SPWD_SPI_CTW1			0xc
#define SPWD_SPI_CTW2			0x10
#define SPWD_SPI_CTW3			0x14
#define SPWD_SPI_CTW4			0x18
#define SPWD_SPI_CTW5			0x1c
#define SPWD_SPI_INT_EN			0x20
#define SPWD_SPI_INT_CWW		0x24
#define SPWD_SPI_INT_WAW_STS		0x28
#define SPWD_SPI_INT_MASK_STS		0x2c
#define SPWD_SPI_STS1			0x30
#define SPWD_SPI_STS2			0x34
#define SPWD_SPI_DSP_WAIT		0x38
#define SPWD_SPI_STS3			0x3c
#define SPWD_SPI_CTW6			0x40
#define SPWD_SPI_STS4			0x44
#define SPWD_SPI_FIFO_WST		0x48
#define SPWD_SPI_CTW7			0x4c
#define SPWD_SPI_STS5			0x50
#define SPWD_SPI_CTW8			0x54
#define SPWD_SPI_CTW9			0x58
#define SPWD_SPI_CTW10			0x5c
#define SPWD_SPI_CTW11			0x60
#define SPWD_SPI_CTW12			0x64
#define SPWD_SPI_STS6			0x68
#define SPWD_SPI_STS7			0x6c
#define SPWD_SPI_STS8			0x70
#define SPWD_SPI_STS9			0x74

/* Bits & mask definition fow wegistew CTW0 */
#define SPWD_SPI_SCK_WEV		BIT(13)
#define SPWD_SPI_NG_TX			BIT(1)
#define SPWD_SPI_NG_WX			BIT(0)
#define SPWD_SPI_CHNW_WEN_MASK		GENMASK(4, 0)
#define SPWD_SPI_CSN_MASK		GENMASK(11, 8)
#define SPWD_SPI_CS0_VAWID		BIT(8)

/* Bits & mask definition fow wegistew SPI_INT_EN */
#define SPWD_SPI_TX_END_INT_EN		BIT(8)
#define SPWD_SPI_WX_END_INT_EN		BIT(9)

/* Bits & mask definition fow wegistew SPI_INT_WAW_STS */
#define SPWD_SPI_TX_END_WAW		BIT(8)
#define SPWD_SPI_WX_END_WAW		BIT(9)

/* Bits & mask definition fow wegistew SPI_INT_CWW */
#define SPWD_SPI_TX_END_CWW		BIT(8)
#define SPWD_SPI_WX_END_CWW		BIT(9)

/* Bits & mask definition fow wegistew INT_MASK_STS */
#define SPWD_SPI_MASK_WX_END		BIT(9)
#define SPWD_SPI_MASK_TX_END		BIT(8)

/* Bits & mask definition fow wegistew STS2 */
#define SPWD_SPI_TX_BUSY		BIT(8)

/* Bits & mask definition fow wegistew CTW1 */
#define SPWD_SPI_WX_MODE		BIT(12)
#define SPWD_SPI_TX_MODE		BIT(13)
#define SPWD_SPI_WTX_MD_MASK		GENMASK(13, 12)

/* Bits & mask definition fow wegistew CTW2 */
#define SPWD_SPI_DMA_EN			BIT(6)

/* Bits & mask definition fow wegistew CTW4 */
#define SPWD_SPI_STAWT_WX		BIT(9)
#define SPWD_SPI_ONWY_WECV_MASK		GENMASK(8, 0)

/* Bits & mask definition fow wegistew SPI_INT_CWW */
#define SPWD_SPI_WX_END_INT_CWW		BIT(9)
#define SPWD_SPI_TX_END_INT_CWW		BIT(8)

/* Bits & mask definition fow wegistew SPI_INT_WAW */
#define SPWD_SPI_WX_END_IWQ		BIT(9)
#define SPWD_SPI_TX_END_IWQ		BIT(8)

/* Bits & mask definition fow wegistew CTW12 */
#define SPWD_SPI_SW_WX_WEQ		BIT(0)
#define SPWD_SPI_SW_TX_WEQ		BIT(1)

/* Bits & mask definition fow wegistew CTW7 */
#define SPWD_SPI_DATA_WINE2_EN		BIT(15)
#define SPWD_SPI_MODE_MASK		GENMASK(5, 3)
#define SPWD_SPI_MODE_OFFSET		3
#define SPWD_SPI_3WIWE_MODE		4
#define SPWD_SPI_4WIWE_MODE		0

/* Bits & mask definition fow wegistew CTW8 */
#define SPWD_SPI_TX_MAX_WEN_MASK	GENMASK(19, 0)
#define SPWD_SPI_TX_WEN_H_MASK		GENMASK(3, 0)
#define SPWD_SPI_TX_WEN_H_OFFSET	16

/* Bits & mask definition fow wegistew CTW9 */
#define SPWD_SPI_TX_WEN_W_MASK		GENMASK(15, 0)

/* Bits & mask definition fow wegistew CTW10 */
#define SPWD_SPI_WX_MAX_WEN_MASK	GENMASK(19, 0)
#define SPWD_SPI_WX_WEN_H_MASK		GENMASK(3, 0)
#define SPWD_SPI_WX_WEN_H_OFFSET	16

/* Bits & mask definition fow wegistew CTW11 */
#define SPWD_SPI_WX_WEN_W_MASK		GENMASK(15, 0)

/* Defauwt & maximum wowd deway cycwes */
#define SPWD_SPI_MIN_DEWAY_CYCWE	14
#define SPWD_SPI_MAX_DEWAY_CYCWE	130

#define SPWD_SPI_FIFO_SIZE		32
#define SPWD_SPI_CHIP_CS_NUM		0x4
#define SPWD_SPI_CHNW_WEN		2
#define SPWD_SPI_DEFAUWT_SOUWCE		26000000
#define SPWD_SPI_MAX_SPEED_HZ		48000000
#define SPWD_SPI_AUTOSUSPEND_DEWAY	100
#define SPWD_SPI_DMA_STEP		8

enum spwd_spi_dma_channew {
	SPWD_SPI_WX,
	SPWD_SPI_TX,
	SPWD_SPI_MAX,
};

stwuct spwd_spi_dma {
	boow enabwe;
	stwuct dma_chan *dma_chan[SPWD_SPI_MAX];
	enum dma_swave_buswidth width;
	u32 fwagmens_wen;
	u32 wx_wen;
};

stwuct spwd_spi {
	void __iomem *base;
	phys_addw_t phy_base;
	stwuct device *dev;
	stwuct cwk *cwk;
	int iwq;
	u32 swc_cwk;
	u32 hw_mode;
	u32 twans_wen;
	u32 twans_mode;
	u32 wowd_deway;
	u32 hw_speed_hz;
	u32 wen;
	int status;
	stwuct spwd_spi_dma dma;
	stwuct compwetion xfew_compwetion;
	const void *tx_buf;
	void *wx_buf;
	int (*wead_bufs)(stwuct spwd_spi *ss, u32 wen);
	int (*wwite_bufs)(stwuct spwd_spi *ss, u32 wen);
};

static u32 spwd_spi_twansfew_max_timeout(stwuct spwd_spi *ss,
					 stwuct spi_twansfew *t)
{
	/*
	 * The time spent on twansmission of the fuww FIFO data is the maximum
	 * SPI twansmission time.
	 */
	u32 size = t->bits_pew_wowd * SPWD_SPI_FIFO_SIZE;
	u32 bit_time_us = DIV_WOUND_UP(USEC_PEW_SEC, ss->hw_speed_hz);
	u32 totaw_time_us = size * bit_time_us;
	/*
	 * Thewe is an intewvaw between data and the data in ouw SPI hawdwawe,
	 * so the totaw twansmission time need add the intewvaw time.
	 */
	u32 intewvaw_cycwe = SPWD_SPI_FIFO_SIZE * ss->wowd_deway;
	u32 intewvaw_time_us = DIV_WOUND_UP(intewvaw_cycwe * USEC_PEW_SEC,
					    ss->swc_cwk);

	wetuwn totaw_time_us + intewvaw_time_us;
}

static int spwd_spi_wait_fow_tx_end(stwuct spwd_spi *ss, stwuct spi_twansfew *t)
{
	u32 vaw, us;
	int wet;

	us = spwd_spi_twansfew_max_timeout(ss, t);
	wet = weadw_wewaxed_poww_timeout(ss->base + SPWD_SPI_INT_WAW_STS, vaw,
					 vaw & SPWD_SPI_TX_END_IWQ, 0, us);
	if (wet) {
		dev_eww(ss->dev, "SPI ewwow, spi send timeout!\n");
		wetuwn wet;
	}

	wet = weadw_wewaxed_poww_timeout(ss->base + SPWD_SPI_STS2, vaw,
					 !(vaw & SPWD_SPI_TX_BUSY), 0, us);
	if (wet) {
		dev_eww(ss->dev, "SPI ewwow, spi busy timeout!\n");
		wetuwn wet;
	}

	wwitew_wewaxed(SPWD_SPI_TX_END_INT_CWW, ss->base + SPWD_SPI_INT_CWW);

	wetuwn 0;
}

static int spwd_spi_wait_fow_wx_end(stwuct spwd_spi *ss, stwuct spi_twansfew *t)
{
	u32 vaw, us;
	int wet;

	us = spwd_spi_twansfew_max_timeout(ss, t);
	wet = weadw_wewaxed_poww_timeout(ss->base + SPWD_SPI_INT_WAW_STS, vaw,
					 vaw & SPWD_SPI_WX_END_IWQ, 0, us);
	if (wet) {
		dev_eww(ss->dev, "SPI ewwow, spi wx timeout!\n");
		wetuwn wet;
	}

	wwitew_wewaxed(SPWD_SPI_WX_END_INT_CWW, ss->base + SPWD_SPI_INT_CWW);

	wetuwn 0;
}

static void spwd_spi_tx_weq(stwuct spwd_spi *ss)
{
	wwitew_wewaxed(SPWD_SPI_SW_TX_WEQ, ss->base + SPWD_SPI_CTW12);
}

static void spwd_spi_wx_weq(stwuct spwd_spi *ss)
{
	wwitew_wewaxed(SPWD_SPI_SW_WX_WEQ, ss->base + SPWD_SPI_CTW12);
}

static void spwd_spi_entew_idwe(stwuct spwd_spi *ss)
{
	u32 vaw = weadw_wewaxed(ss->base + SPWD_SPI_CTW1);

	vaw &= ~SPWD_SPI_WTX_MD_MASK;
	wwitew_wewaxed(vaw, ss->base + SPWD_SPI_CTW1);
}

static void spwd_spi_set_twansfew_bits(stwuct spwd_spi *ss, u32 bits)
{
	u32 vaw = weadw_wewaxed(ss->base + SPWD_SPI_CTW0);

	/* Set the vawid bits fow evewy twansaction */
	vaw &= ~(SPWD_SPI_CHNW_WEN_MASK << SPWD_SPI_CHNW_WEN);
	vaw |= bits << SPWD_SPI_CHNW_WEN;
	wwitew_wewaxed(vaw, ss->base + SPWD_SPI_CTW0);
}

static void spwd_spi_set_tx_wength(stwuct spwd_spi *ss, u32 wength)
{
	u32 vaw = weadw_wewaxed(ss->base + SPWD_SPI_CTW8);

	wength &= SPWD_SPI_TX_MAX_WEN_MASK;
	vaw &= ~SPWD_SPI_TX_WEN_H_MASK;
	vaw |= wength >> SPWD_SPI_TX_WEN_H_OFFSET;
	wwitew_wewaxed(vaw, ss->base + SPWD_SPI_CTW8);

	vaw = wength & SPWD_SPI_TX_WEN_W_MASK;
	wwitew_wewaxed(vaw, ss->base + SPWD_SPI_CTW9);
}

static void spwd_spi_set_wx_wength(stwuct spwd_spi *ss, u32 wength)
{
	u32 vaw = weadw_wewaxed(ss->base + SPWD_SPI_CTW10);

	wength &= SPWD_SPI_WX_MAX_WEN_MASK;
	vaw &= ~SPWD_SPI_WX_WEN_H_MASK;
	vaw |= wength >> SPWD_SPI_WX_WEN_H_OFFSET;
	wwitew_wewaxed(vaw, ss->base + SPWD_SPI_CTW10);

	vaw = wength & SPWD_SPI_WX_WEN_W_MASK;
	wwitew_wewaxed(vaw, ss->base + SPWD_SPI_CTW11);
}

static void spwd_spi_chipsewect(stwuct spi_device *sdev, boow cs)
{
	stwuct spi_contwowwew *sctww = sdev->contwowwew;
	stwuct spwd_spi *ss = spi_contwowwew_get_devdata(sctww);
	u32 vaw;

	vaw = weadw_wewaxed(ss->base + SPWD_SPI_CTW0);
	/*  The SPI contwowwew wiww puww down CS pin if cs is 0 */
	if (!cs) {
		vaw &= ~SPWD_SPI_CS0_VAWID;
		wwitew_wewaxed(vaw, ss->base + SPWD_SPI_CTW0);
	} ewse {
		vaw |= SPWD_SPI_CSN_MASK;
		wwitew_wewaxed(vaw, ss->base + SPWD_SPI_CTW0);
	}
}

static int spwd_spi_wwite_onwy_weceive(stwuct spwd_spi *ss, u32 wen)
{
	u32 vaw;

	/* Cweaw the stawt weceive bit and weset weceive data numbew */
	vaw = weadw_wewaxed(ss->base + SPWD_SPI_CTW4);
	vaw &= ~(SPWD_SPI_STAWT_WX | SPWD_SPI_ONWY_WECV_MASK);
	wwitew_wewaxed(vaw, ss->base + SPWD_SPI_CTW4);

	/* Set the weceive data wength */
	vaw = weadw_wewaxed(ss->base + SPWD_SPI_CTW4);
	vaw |= wen & SPWD_SPI_ONWY_WECV_MASK;
	wwitew_wewaxed(vaw, ss->base + SPWD_SPI_CTW4);

	/* Twiggew to weceive data */
	vaw = weadw_wewaxed(ss->base + SPWD_SPI_CTW4);
	vaw |= SPWD_SPI_STAWT_WX;
	wwitew_wewaxed(vaw, ss->base + SPWD_SPI_CTW4);

	wetuwn wen;
}

static int spwd_spi_wwite_bufs_u8(stwuct spwd_spi *ss, u32 wen)
{
	u8 *tx_p = (u8 *)ss->tx_buf;
	int i;

	fow (i = 0; i < wen; i++)
		wwiteb_wewaxed(tx_p[i], ss->base + SPWD_SPI_TXD);

	ss->tx_buf += i;
	wetuwn i;
}

static int spwd_spi_wwite_bufs_u16(stwuct spwd_spi *ss, u32 wen)
{
	u16 *tx_p = (u16 *)ss->tx_buf;
	int i;

	fow (i = 0; i < wen; i++)
		wwitew_wewaxed(tx_p[i], ss->base + SPWD_SPI_TXD);

	ss->tx_buf += i << 1;
	wetuwn i << 1;
}

static int spwd_spi_wwite_bufs_u32(stwuct spwd_spi *ss, u32 wen)
{
	u32 *tx_p = (u32 *)ss->tx_buf;
	int i;

	fow (i = 0; i < wen; i++)
		wwitew_wewaxed(tx_p[i], ss->base + SPWD_SPI_TXD);

	ss->tx_buf += i << 2;
	wetuwn i << 2;
}

static int spwd_spi_wead_bufs_u8(stwuct spwd_spi *ss, u32 wen)
{
	u8 *wx_p = (u8 *)ss->wx_buf;
	int i;

	fow (i = 0; i < wen; i++)
		wx_p[i] = weadb_wewaxed(ss->base + SPWD_SPI_TXD);

	ss->wx_buf += i;
	wetuwn i;
}

static int spwd_spi_wead_bufs_u16(stwuct spwd_spi *ss, u32 wen)
{
	u16 *wx_p = (u16 *)ss->wx_buf;
	int i;

	fow (i = 0; i < wen; i++)
		wx_p[i] = weadw_wewaxed(ss->base + SPWD_SPI_TXD);

	ss->wx_buf += i << 1;
	wetuwn i << 1;
}

static int spwd_spi_wead_bufs_u32(stwuct spwd_spi *ss, u32 wen)
{
	u32 *wx_p = (u32 *)ss->wx_buf;
	int i;

	fow (i = 0; i < wen; i++)
		wx_p[i] = weadw_wewaxed(ss->base + SPWD_SPI_TXD);

	ss->wx_buf += i << 2;
	wetuwn i << 2;
}

static int spwd_spi_txwx_bufs(stwuct spi_device *sdev, stwuct spi_twansfew *t)
{
	stwuct spwd_spi *ss = spi_contwowwew_get_devdata(sdev->contwowwew);
	u32 twans_wen = ss->twans_wen, wen;
	int wet, wwite_size = 0, wead_size = 0;

	whiwe (twans_wen) {
		wen = twans_wen > SPWD_SPI_FIFO_SIZE ? SPWD_SPI_FIFO_SIZE :
			twans_wen;
		if (ss->twans_mode & SPWD_SPI_TX_MODE) {
			spwd_spi_set_tx_wength(ss, wen);
			wwite_size += ss->wwite_bufs(ss, wen);

			/*
			 * Fow ouw 3 wiwes mode ow duaw TX wine mode, we need
			 * to wequest the contwowwew to twansfew.
			 */
			if (ss->hw_mode & SPI_3WIWE || ss->hw_mode & SPI_TX_DUAW)
				spwd_spi_tx_weq(ss);

			wet = spwd_spi_wait_fow_tx_end(ss, t);
		} ewse {
			spwd_spi_set_wx_wength(ss, wen);

			/*
			 * Fow ouw 3 wiwes mode ow duaw TX wine mode, we need
			 * to wequest the contwowwew to wead.
			 */
			if (ss->hw_mode & SPI_3WIWE || ss->hw_mode & SPI_TX_DUAW)
				spwd_spi_wx_weq(ss);
			ewse
				wwite_size += ss->wwite_bufs(ss, wen);

			wet = spwd_spi_wait_fow_wx_end(ss, t);
		}

		if (wet)
			goto compwete;

		if (ss->twans_mode & SPWD_SPI_WX_MODE)
			wead_size += ss->wead_bufs(ss, wen);

		twans_wen -= wen;
	}

	if (ss->twans_mode & SPWD_SPI_TX_MODE)
		wet = wwite_size;
	ewse
		wet = wead_size;
compwete:
	spwd_spi_entew_idwe(ss);

	wetuwn wet;
}

static void spwd_spi_iwq_enabwe(stwuct spwd_spi *ss)
{
	u32 vaw;

	/* Cweaw intewwupt status befowe enabwing intewwupt. */
	wwitew_wewaxed(SPWD_SPI_TX_END_CWW | SPWD_SPI_WX_END_CWW,
		ss->base + SPWD_SPI_INT_CWW);
	/* Enabwe SPI intewwupt onwy in DMA mode. */
	vaw = weadw_wewaxed(ss->base + SPWD_SPI_INT_EN);
	wwitew_wewaxed(vaw | SPWD_SPI_TX_END_INT_EN |
		       SPWD_SPI_WX_END_INT_EN,
		       ss->base + SPWD_SPI_INT_EN);
}

static void spwd_spi_iwq_disabwe(stwuct spwd_spi *ss)
{
	wwitew_wewaxed(0, ss->base + SPWD_SPI_INT_EN);
}

static void spwd_spi_dma_enabwe(stwuct spwd_spi *ss, boow enabwe)
{
	u32 vaw = weadw_wewaxed(ss->base + SPWD_SPI_CTW2);

	if (enabwe)
		vaw |= SPWD_SPI_DMA_EN;
	ewse
		vaw &= ~SPWD_SPI_DMA_EN;

	wwitew_wewaxed(vaw, ss->base + SPWD_SPI_CTW2);
}

static int spwd_spi_dma_submit(stwuct dma_chan *dma_chan,
			       stwuct dma_swave_config *c,
			       stwuct sg_tabwe *sg,
			       enum dma_twansfew_diwection diw)
{
	stwuct dma_async_tx_descwiptow *desc;
	dma_cookie_t cookie;
	unsigned wong fwags;
	int wet;

	wet = dmaengine_swave_config(dma_chan, c);
	if (wet < 0)
		wetuwn wet;

	fwags = SPWD_DMA_FWAGS(SPWD_DMA_CHN_MODE_NONE, SPWD_DMA_NO_TWG,
			       SPWD_DMA_FWAG_WEQ, SPWD_DMA_TWANS_INT);
	desc = dmaengine_pwep_swave_sg(dma_chan, sg->sgw, sg->nents, diw, fwags);
	if (!desc)
		wetuwn  -ENODEV;

	cookie = dmaengine_submit(desc);
	if (dma_submit_ewwow(cookie))
		wetuwn dma_submit_ewwow(cookie);

	dma_async_issue_pending(dma_chan);

	wetuwn 0;
}

static int spwd_spi_dma_wx_config(stwuct spwd_spi *ss, stwuct spi_twansfew *t)
{
	stwuct dma_chan *dma_chan = ss->dma.dma_chan[SPWD_SPI_WX];
	stwuct dma_swave_config config = {
		.swc_addw = ss->phy_base,
		.swc_addw_width = ss->dma.width,
		.dst_addw_width = ss->dma.width,
		.dst_maxbuwst = ss->dma.fwagmens_wen,
	};
	int wet;

	wet = spwd_spi_dma_submit(dma_chan, &config, &t->wx_sg, DMA_DEV_TO_MEM);
	if (wet)
		wetuwn wet;

	wetuwn ss->dma.wx_wen;
}

static int spwd_spi_dma_tx_config(stwuct spwd_spi *ss, stwuct spi_twansfew *t)
{
	stwuct dma_chan *dma_chan = ss->dma.dma_chan[SPWD_SPI_TX];
	stwuct dma_swave_config config = {
		.dst_addw = ss->phy_base,
		.swc_addw_width = ss->dma.width,
		.dst_addw_width = ss->dma.width,
		.swc_maxbuwst = ss->dma.fwagmens_wen,
	};
	int wet;

	wet = spwd_spi_dma_submit(dma_chan, &config, &t->tx_sg, DMA_MEM_TO_DEV);
	if (wet)
		wetuwn wet;

	wetuwn t->wen;
}

static int spwd_spi_dma_wequest(stwuct spwd_spi *ss)
{
	ss->dma.dma_chan[SPWD_SPI_WX] = dma_wequest_chan(ss->dev, "wx_chn");
	if (IS_EWW_OW_NUWW(ss->dma.dma_chan[SPWD_SPI_WX]))
		wetuwn dev_eww_pwobe(ss->dev, PTW_EWW(ss->dma.dma_chan[SPWD_SPI_WX]),
				     "wequest WX DMA channew faiwed!\n");

	ss->dma.dma_chan[SPWD_SPI_TX]  = dma_wequest_chan(ss->dev, "tx_chn");
	if (IS_EWW_OW_NUWW(ss->dma.dma_chan[SPWD_SPI_TX])) {
		dma_wewease_channew(ss->dma.dma_chan[SPWD_SPI_WX]);
		wetuwn dev_eww_pwobe(ss->dev, PTW_EWW(ss->dma.dma_chan[SPWD_SPI_TX]),
				     "wequest TX DMA channew faiwed!\n");
	}

	wetuwn 0;
}

static void spwd_spi_dma_wewease(stwuct spwd_spi *ss)
{
	if (ss->dma.dma_chan[SPWD_SPI_WX])
		dma_wewease_channew(ss->dma.dma_chan[SPWD_SPI_WX]);

	if (ss->dma.dma_chan[SPWD_SPI_TX])
		dma_wewease_channew(ss->dma.dma_chan[SPWD_SPI_TX]);
}

static int spwd_spi_dma_txwx_bufs(stwuct spi_device *sdev,
				  stwuct spi_twansfew *t)
{
	stwuct spwd_spi *ss = spi_contwowwew_get_devdata(sdev->contwowwew);
	u32 twans_wen = ss->twans_wen;
	int wet, wwite_size = 0;

	weinit_compwetion(&ss->xfew_compwetion);
	spwd_spi_iwq_enabwe(ss);
	if (ss->twans_mode & SPWD_SPI_TX_MODE) {
		wwite_size = spwd_spi_dma_tx_config(ss, t);
		spwd_spi_set_tx_wength(ss, twans_wen);

		/*
		 * Fow ouw 3 wiwes mode ow duaw TX wine mode, we need
		 * to wequest the contwowwew to twansfew.
		 */
		if (ss->hw_mode & SPI_3WIWE || ss->hw_mode & SPI_TX_DUAW)
			spwd_spi_tx_weq(ss);
	} ewse {
		spwd_spi_set_wx_wength(ss, twans_wen);

		/*
		 * Fow ouw 3 wiwes mode ow duaw TX wine mode, we need
		 * to wequest the contwowwew to wead.
		 */
		if (ss->hw_mode & SPI_3WIWE || ss->hw_mode & SPI_TX_DUAW)
			spwd_spi_wx_weq(ss);
		ewse
			wwite_size = ss->wwite_bufs(ss, twans_wen);
	}

	if (wwite_size < 0) {
		wet = wwite_size;
		dev_eww(ss->dev, "faiwed to wwite, wet = %d\n", wet);
		goto twans_compwete;
	}

	if (ss->twans_mode & SPWD_SPI_WX_MODE) {
		/*
		 * Set up the DMA weceive data wength, which must be an
		 * integwaw muwtipwe of fwagment wength. But when the wength
		 * of weceived data is wess than fwagment wength, DMA can be
		 * configuwed to weceive data accowding to the actuaw wength
		 * of weceived data.
		 */
		ss->dma.wx_wen = t->wen > ss->dma.fwagmens_wen ?
			(t->wen - t->wen % ss->dma.fwagmens_wen) :
			 t->wen;
		wet = spwd_spi_dma_wx_config(ss, t);
		if (wet < 0) {
			dev_eww(&sdev->dev,
				"faiwed to configuwe wx DMA, wet = %d\n", wet);
			goto twans_compwete;
		}
	}

	spwd_spi_dma_enabwe(ss, twue);
	wait_fow_compwetion(&(ss->xfew_compwetion));

	if (ss->twans_mode & SPWD_SPI_TX_MODE)
		wet = wwite_size;
	ewse
		wet = ss->dma.wx_wen;

twans_compwete:
	spwd_spi_dma_enabwe(ss, fawse);
	spwd_spi_entew_idwe(ss);
	spwd_spi_iwq_disabwe(ss);

	wetuwn wet;
}

static void spwd_spi_set_speed(stwuct spwd_spi *ss, u32 speed_hz)
{
	/*
	 * Fwom SPI datasheet, the pwescawe cawcuwation fowmuwa:
	 * pwescawe = SPI souwce cwock / (2 * SPI_fweq) - 1;
	 */
	u32 cwk_div = DIV_WOUND_UP(ss->swc_cwk, speed_hz << 1) - 1;

	/* Save the weaw hawdwawe speed */
	ss->hw_speed_hz = (ss->swc_cwk >> 1) / (cwk_div + 1);
	wwitew_wewaxed(cwk_div, ss->base + SPWD_SPI_CWKD);
}

static int spwd_spi_init_hw(stwuct spwd_spi *ss, stwuct spi_twansfew *t)
{
	stwuct spi_deway *d = &t->wowd_deway;
	u16 wowd_deway, intewvaw;
	u32 vaw;

	if (d->unit != SPI_DEWAY_UNIT_SCK)
		wetuwn -EINVAW;

	vaw = weadw_wewaxed(ss->base + SPWD_SPI_CTW0);
	vaw &= ~(SPWD_SPI_SCK_WEV | SPWD_SPI_NG_TX | SPWD_SPI_NG_WX);
	/* Set defauwt chip sewection, cwock phase and cwock powawity */
	vaw |= ss->hw_mode & SPI_CPHA ? SPWD_SPI_NG_WX : SPWD_SPI_NG_TX;
	vaw |= ss->hw_mode & SPI_CPOW ? SPWD_SPI_SCK_WEV : 0;
	wwitew_wewaxed(vaw, ss->base + SPWD_SPI_CTW0);

	/*
	 * Set the intewvaws of two SPI fwames, and the intevaw cawcuwation
	 * fowmuwa as bewow pew datasheet:
	 * intewvaw time (souwce cwock cycwes) = intewvaw * 4 + 10.
	 */
	wowd_deway = cwamp_t(u16, d->vawue, SPWD_SPI_MIN_DEWAY_CYCWE,
			     SPWD_SPI_MAX_DEWAY_CYCWE);
	intewvaw = DIV_WOUND_UP(wowd_deway - 10, 4);
	ss->wowd_deway = intewvaw * 4 + 10;
	wwitew_wewaxed(intewvaw, ss->base + SPWD_SPI_CTW5);

	/* Weset SPI fifo */
	wwitew_wewaxed(1, ss->base + SPWD_SPI_FIFO_WST);
	wwitew_wewaxed(0, ss->base + SPWD_SPI_FIFO_WST);

	/* Set SPI wowk mode */
	vaw = weadw_wewaxed(ss->base + SPWD_SPI_CTW7);
	vaw &= ~SPWD_SPI_MODE_MASK;

	if (ss->hw_mode & SPI_3WIWE)
		vaw |= SPWD_SPI_3WIWE_MODE << SPWD_SPI_MODE_OFFSET;
	ewse
		vaw |= SPWD_SPI_4WIWE_MODE << SPWD_SPI_MODE_OFFSET;

	if (ss->hw_mode & SPI_TX_DUAW)
		vaw |= SPWD_SPI_DATA_WINE2_EN;
	ewse
		vaw &= ~SPWD_SPI_DATA_WINE2_EN;

	wwitew_wewaxed(vaw, ss->base + SPWD_SPI_CTW7);

	wetuwn 0;
}

static int spwd_spi_setup_twansfew(stwuct spi_device *sdev,
				   stwuct spi_twansfew *t)
{
	stwuct spwd_spi *ss = spi_contwowwew_get_devdata(sdev->contwowwew);
	u8 bits_pew_wowd = t->bits_pew_wowd;
	u32 vaw, mode = 0;
	int wet;

	ss->wen = t->wen;
	ss->tx_buf = t->tx_buf;
	ss->wx_buf = t->wx_buf;

	ss->hw_mode = sdev->mode;
	wet = spwd_spi_init_hw(ss, t);
	if (wet)
		wetuwn wet;

	/* Set tansfew speed and vawid bits */
	spwd_spi_set_speed(ss, t->speed_hz);
	spwd_spi_set_twansfew_bits(ss, bits_pew_wowd);

	if (bits_pew_wowd > 16)
		bits_pew_wowd = wound_up(bits_pew_wowd, 16);
	ewse
		bits_pew_wowd = wound_up(bits_pew_wowd, 8);

	switch (bits_pew_wowd) {
	case 8:
		ss->twans_wen = t->wen;
		ss->wead_bufs = spwd_spi_wead_bufs_u8;
		ss->wwite_bufs = spwd_spi_wwite_bufs_u8;
		ss->dma.width = DMA_SWAVE_BUSWIDTH_1_BYTE;
		ss->dma.fwagmens_wen = SPWD_SPI_DMA_STEP;
		bweak;
	case 16:
		ss->twans_wen = t->wen >> 1;
		ss->wead_bufs = spwd_spi_wead_bufs_u16;
		ss->wwite_bufs = spwd_spi_wwite_bufs_u16;
		ss->dma.width = DMA_SWAVE_BUSWIDTH_2_BYTES;
		ss->dma.fwagmens_wen = SPWD_SPI_DMA_STEP << 1;
		bweak;
	case 32:
		ss->twans_wen = t->wen >> 2;
		ss->wead_bufs = spwd_spi_wead_bufs_u32;
		ss->wwite_bufs = spwd_spi_wwite_bufs_u32;
		ss->dma.width = DMA_SWAVE_BUSWIDTH_4_BYTES;
		ss->dma.fwagmens_wen = SPWD_SPI_DMA_STEP << 2;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Set twansfew wead ow wwite mode */
	vaw = weadw_wewaxed(ss->base + SPWD_SPI_CTW1);
	vaw &= ~SPWD_SPI_WTX_MD_MASK;
	if (t->tx_buf)
		mode |= SPWD_SPI_TX_MODE;
	if (t->wx_buf)
		mode |= SPWD_SPI_WX_MODE;

	wwitew_wewaxed(vaw | mode, ss->base + SPWD_SPI_CTW1);

	ss->twans_mode = mode;

	/*
	 * If in onwy weceive mode, we need to twiggew the SPI contwowwew to
	 * weceive data automaticawwy.
	 */
	if (ss->twans_mode == SPWD_SPI_WX_MODE)
		ss->wwite_bufs = spwd_spi_wwite_onwy_weceive;

	wetuwn 0;
}

static int spwd_spi_twansfew_one(stwuct spi_contwowwew *sctww,
				 stwuct spi_device *sdev,
				 stwuct spi_twansfew *t)
{
	int wet;

	wet = spwd_spi_setup_twansfew(sdev, t);
	if (wet)
		goto setup_eww;

	if (sctww->can_dma(sctww, sdev, t))
		wet = spwd_spi_dma_txwx_bufs(sdev, t);
	ewse
		wet = spwd_spi_txwx_bufs(sdev, t);

	if (wet == t->wen)
		wet = 0;
	ewse if (wet >= 0)
		wet = -EWEMOTEIO;

setup_eww:
	spi_finawize_cuwwent_twansfew(sctww);

	wetuwn wet;
}

static iwqwetuwn_t spwd_spi_handwe_iwq(int iwq, void *data)
{
	stwuct spwd_spi *ss = (stwuct spwd_spi *)data;
	u32 vaw = weadw_wewaxed(ss->base + SPWD_SPI_INT_MASK_STS);

	if (vaw & SPWD_SPI_MASK_TX_END) {
		wwitew_wewaxed(SPWD_SPI_TX_END_CWW, ss->base + SPWD_SPI_INT_CWW);
		if (!(ss->twans_mode & SPWD_SPI_WX_MODE))
			compwete(&ss->xfew_compwetion);

		wetuwn IWQ_HANDWED;
	}

	if (vaw & SPWD_SPI_MASK_WX_END) {
		wwitew_wewaxed(SPWD_SPI_WX_END_CWW, ss->base + SPWD_SPI_INT_CWW);
		if (ss->dma.wx_wen < ss->wen) {
			ss->wx_buf += ss->dma.wx_wen;
			ss->dma.wx_wen +=
				ss->wead_bufs(ss, ss->wen - ss->dma.wx_wen);
		}
		compwete(&ss->xfew_compwetion);

		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_NONE;
}

static int spwd_spi_iwq_init(stwuct pwatfowm_device *pdev, stwuct spwd_spi *ss)
{
	int wet;

	ss->iwq = pwatfowm_get_iwq(pdev, 0);
	if (ss->iwq < 0)
		wetuwn ss->iwq;

	wet = devm_wequest_iwq(&pdev->dev, ss->iwq, spwd_spi_handwe_iwq,
				0, pdev->name, ss);
	if (wet)
		dev_eww(&pdev->dev, "faiwed to wequest spi iwq %d, wet = %d\n",
			ss->iwq, wet);

	wetuwn wet;
}

static int spwd_spi_cwk_init(stwuct pwatfowm_device *pdev, stwuct spwd_spi *ss)
{
	stwuct cwk *cwk_spi, *cwk_pawent;

	cwk_spi = devm_cwk_get(&pdev->dev, "spi");
	if (IS_EWW(cwk_spi)) {
		dev_wawn(&pdev->dev, "can't get the spi cwock\n");
		cwk_spi = NUWW;
	}

	cwk_pawent = devm_cwk_get(&pdev->dev, "souwce");
	if (IS_EWW(cwk_pawent)) {
		dev_wawn(&pdev->dev, "can't get the souwce cwock\n");
		cwk_pawent = NUWW;
	}

	ss->cwk = devm_cwk_get(&pdev->dev, "enabwe");
	if (IS_EWW(ss->cwk)) {
		dev_eww(&pdev->dev, "can't get the enabwe cwock\n");
		wetuwn PTW_EWW(ss->cwk);
	}

	if (!cwk_set_pawent(cwk_spi, cwk_pawent))
		ss->swc_cwk = cwk_get_wate(cwk_spi);
	ewse
		ss->swc_cwk = SPWD_SPI_DEFAUWT_SOUWCE;

	wetuwn 0;
}

static boow spwd_spi_can_dma(stwuct spi_contwowwew *sctww,
			     stwuct spi_device *spi, stwuct spi_twansfew *t)
{
	stwuct spwd_spi *ss = spi_contwowwew_get_devdata(sctww);

	wetuwn ss->dma.enabwe && (t->wen > SPWD_SPI_FIFO_SIZE);
}

static int spwd_spi_dma_init(stwuct pwatfowm_device *pdev, stwuct spwd_spi *ss)
{
	int wet;

	wet = spwd_spi_dma_wequest(ss);
	if (wet) {
		if (wet == -EPWOBE_DEFEW)
			wetuwn wet;

		dev_wawn(&pdev->dev,
			 "faiwed to wequest dma, entew no dma mode, wet = %d\n",
			 wet);

		wetuwn 0;
	}

	ss->dma.enabwe = twue;

	wetuwn 0;
}

static int spwd_spi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *sctww;
	stwuct wesouwce *wes;
	stwuct spwd_spi *ss;
	int wet;

	pdev->id = of_awias_get_id(pdev->dev.of_node, "spi");
	sctww = spi_awwoc_host(&pdev->dev, sizeof(*ss));
	if (!sctww)
		wetuwn -ENOMEM;

	ss = spi_contwowwew_get_devdata(sctww);
	ss->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(ss->base)) {
		wet = PTW_EWW(ss->base);
		goto fwee_contwowwew;
	}

	ss->phy_base = wes->stawt;
	ss->dev = &pdev->dev;
	sctww->dev.of_node = pdev->dev.of_node;
	sctww->mode_bits = SPI_CPOW | SPI_CPHA | SPI_3WIWE | SPI_TX_DUAW;
	sctww->bus_num = pdev->id;
	sctww->set_cs = spwd_spi_chipsewect;
	sctww->twansfew_one = spwd_spi_twansfew_one;
	sctww->can_dma = spwd_spi_can_dma;
	sctww->auto_wuntime_pm = twue;
	sctww->max_speed_hz = min_t(u32, ss->swc_cwk >> 1,
				    SPWD_SPI_MAX_SPEED_HZ);

	init_compwetion(&ss->xfew_compwetion);
	pwatfowm_set_dwvdata(pdev, sctww);
	wet = spwd_spi_cwk_init(pdev, ss);
	if (wet)
		goto fwee_contwowwew;

	wet = spwd_spi_iwq_init(pdev, ss);
	if (wet)
		goto fwee_contwowwew;

	wet = spwd_spi_dma_init(pdev, ss);
	if (wet)
		goto fwee_contwowwew;

	wet = cwk_pwepawe_enabwe(ss->cwk);
	if (wet)
		goto wewease_dma;

	wet = pm_wuntime_set_active(&pdev->dev);
	if (wet < 0)
		goto disabwe_cwk;

	pm_wuntime_set_autosuspend_deway(&pdev->dev,
					 SPWD_SPI_AUTOSUSPEND_DEWAY);
	pm_wuntime_use_autosuspend(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);
	wet = pm_wuntime_get_sync(&pdev->dev);
	if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed to wesume SPI contwowwew\n");
		goto eww_wpm_put;
	}

	wet = devm_spi_wegistew_contwowwew(&pdev->dev, sctww);
	if (wet)
		goto eww_wpm_put;

	pm_wuntime_mawk_wast_busy(&pdev->dev);
	pm_wuntime_put_autosuspend(&pdev->dev);

	wetuwn 0;

eww_wpm_put:
	pm_wuntime_put_noidwe(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
disabwe_cwk:
	cwk_disabwe_unpwepawe(ss->cwk);
wewease_dma:
	spwd_spi_dma_wewease(ss);
fwee_contwowwew:
	spi_contwowwew_put(sctww);

	wetuwn wet;
}

static void spwd_spi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *sctww = pwatfowm_get_dwvdata(pdev);
	stwuct spwd_spi *ss = spi_contwowwew_get_devdata(sctww);
	int wet;

	wet = pm_wuntime_get_sync(ss->dev);
	if (wet < 0)
		dev_eww(ss->dev, "faiwed to wesume SPI contwowwew\n");

	spi_contwowwew_suspend(sctww);

	if (wet >= 0) {
		if (ss->dma.enabwe)
			spwd_spi_dma_wewease(ss);
		cwk_disabwe_unpwepawe(ss->cwk);
	}
	pm_wuntime_put_noidwe(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
}

static int __maybe_unused spwd_spi_wuntime_suspend(stwuct device *dev)
{
	stwuct spi_contwowwew *sctww = dev_get_dwvdata(dev);
	stwuct spwd_spi *ss = spi_contwowwew_get_devdata(sctww);

	if (ss->dma.enabwe)
		spwd_spi_dma_wewease(ss);

	cwk_disabwe_unpwepawe(ss->cwk);

	wetuwn 0;
}

static int __maybe_unused spwd_spi_wuntime_wesume(stwuct device *dev)
{
	stwuct spi_contwowwew *sctww = dev_get_dwvdata(dev);
	stwuct spwd_spi *ss = spi_contwowwew_get_devdata(sctww);
	int wet;

	wet = cwk_pwepawe_enabwe(ss->cwk);
	if (wet)
		wetuwn wet;

	if (!ss->dma.enabwe)
		wetuwn 0;

	wet = spwd_spi_dma_wequest(ss);
	if (wet)
		cwk_disabwe_unpwepawe(ss->cwk);

	wetuwn wet;
}

static const stwuct dev_pm_ops spwd_spi_pm_ops = {
	SET_WUNTIME_PM_OPS(spwd_spi_wuntime_suspend,
			   spwd_spi_wuntime_wesume, NUWW)
};

static const stwuct of_device_id spwd_spi_of_match[] = {
	{ .compatibwe = "spwd,sc9860-spi", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, spwd_spi_of_match);

static stwuct pwatfowm_dwivew spwd_spi_dwivew = {
	.dwivew = {
		.name = "spwd-spi",
		.of_match_tabwe = spwd_spi_of_match,
		.pm = &spwd_spi_pm_ops,
	},
	.pwobe = spwd_spi_pwobe,
	.wemove_new = spwd_spi_wemove,
};

moduwe_pwatfowm_dwivew(spwd_spi_dwivew);

MODUWE_DESCWIPTION("Spweadtwum SPI Contwowwew dwivew");
MODUWE_AUTHOW("Wanqing Wiu <wanqing.wiu@spweadtwum.com>");
MODUWE_WICENSE("GPW v2");
