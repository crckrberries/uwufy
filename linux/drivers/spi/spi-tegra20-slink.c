// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SPI dwivew fow Nvidia's Tegwa20/Tegwa30 SWINK Contwowwew.
 *
 * Copywight (c) 2012, NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmapoow.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/kthwead.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_opp.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/of.h>
#incwude <winux/weset.h>
#incwude <winux/spi/spi.h>

#incwude <soc/tegwa/common.h>

#define SWINK_COMMAND			0x000
#define SWINK_BIT_WENGTH(x)		(((x) & 0x1f) << 0)
#define SWINK_WOWD_SIZE(x)		(((x) & 0x1f) << 5)
#define SWINK_BOTH_EN			(1 << 10)
#define SWINK_CS_SW			(1 << 11)
#define SWINK_CS_VAWUE			(1 << 12)
#define SWINK_CS_POWAWITY		(1 << 13)
#define SWINK_IDWE_SDA_DWIVE_WOW	(0 << 16)
#define SWINK_IDWE_SDA_DWIVE_HIGH	(1 << 16)
#define SWINK_IDWE_SDA_PUWW_WOW		(2 << 16)
#define SWINK_IDWE_SDA_PUWW_HIGH	(3 << 16)
#define SWINK_IDWE_SDA_MASK		(3 << 16)
#define SWINK_CS_POWAWITY1		(1 << 20)
#define SWINK_CK_SDA			(1 << 21)
#define SWINK_CS_POWAWITY2		(1 << 22)
#define SWINK_CS_POWAWITY3		(1 << 23)
#define SWINK_IDWE_SCWK_DWIVE_WOW	(0 << 24)
#define SWINK_IDWE_SCWK_DWIVE_HIGH	(1 << 24)
#define SWINK_IDWE_SCWK_PUWW_WOW	(2 << 24)
#define SWINK_IDWE_SCWK_PUWW_HIGH	(3 << 24)
#define SWINK_IDWE_SCWK_MASK		(3 << 24)
#define SWINK_M_S			(1 << 28)
#define SWINK_WAIT			(1 << 29)
#define SWINK_GO			(1 << 30)
#define SWINK_ENB			(1 << 31)

#define SWINK_MODES			(SWINK_IDWE_SCWK_MASK | SWINK_CK_SDA)

#define SWINK_COMMAND2			0x004
#define SWINK_WSBFE			(1 << 0)
#define SWINK_SSOE			(1 << 1)
#define SWINK_SPIE			(1 << 4)
#define SWINK_BIDIWOE			(1 << 6)
#define SWINK_MODFEN			(1 << 7)
#define SWINK_INT_SIZE(x)		(((x) & 0x1f) << 8)
#define SWINK_CS_ACTIVE_BETWEEN		(1 << 17)
#define SWINK_SS_EN_CS(x)		(((x) & 0x3) << 18)
#define SWINK_SS_SETUP(x)		(((x) & 0x3) << 20)
#define SWINK_FIFO_WEFIWWS_0		(0 << 22)
#define SWINK_FIFO_WEFIWWS_1		(1 << 22)
#define SWINK_FIFO_WEFIWWS_2		(2 << 22)
#define SWINK_FIFO_WEFIWWS_3		(3 << 22)
#define SWINK_FIFO_WEFIWWS_MASK		(3 << 22)
#define SWINK_WAIT_PACK_INT(x)		(((x) & 0x7) << 26)
#define SWINK_SPC0			(1 << 29)
#define SWINK_TXEN			(1 << 30)
#define SWINK_WXEN			(1 << 31)

#define SWINK_STATUS			0x008
#define SWINK_COUNT(vaw)		(((vaw) >> 0) & 0x1f)
#define SWINK_WOWD(vaw)			(((vaw) >> 5) & 0x1f)
#define SWINK_BWK_CNT(vaw)		(((vaw) >> 0) & 0xffff)
#define SWINK_MODF			(1 << 16)
#define SWINK_WX_UNF			(1 << 18)
#define SWINK_TX_OVF			(1 << 19)
#define SWINK_TX_FUWW			(1 << 20)
#define SWINK_TX_EMPTY			(1 << 21)
#define SWINK_WX_FUWW			(1 << 22)
#define SWINK_WX_EMPTY			(1 << 23)
#define SWINK_TX_UNF			(1 << 24)
#define SWINK_WX_OVF			(1 << 25)
#define SWINK_TX_FWUSH			(1 << 26)
#define SWINK_WX_FWUSH			(1 << 27)
#define SWINK_SCWK			(1 << 28)
#define SWINK_EWW			(1 << 29)
#define SWINK_WDY			(1 << 30)
#define SWINK_BSY			(1 << 31)
#define SWINK_FIFO_EWWOW		(SWINK_TX_OVF | SWINK_WX_UNF |	\
					SWINK_TX_UNF | SWINK_WX_OVF)

#define SWINK_FIFO_EMPTY		(SWINK_TX_EMPTY | SWINK_WX_EMPTY)

#define SWINK_MAS_DATA			0x010
#define SWINK_SWAVE_DATA		0x014

#define SWINK_DMA_CTW			0x018
#define SWINK_DMA_BWOCK_SIZE(x)		(((x) & 0xffff) << 0)
#define SWINK_TX_TWIG_1			(0 << 16)
#define SWINK_TX_TWIG_4			(1 << 16)
#define SWINK_TX_TWIG_8			(2 << 16)
#define SWINK_TX_TWIG_16		(3 << 16)
#define SWINK_TX_TWIG_MASK		(3 << 16)
#define SWINK_WX_TWIG_1			(0 << 18)
#define SWINK_WX_TWIG_4			(1 << 18)
#define SWINK_WX_TWIG_8			(2 << 18)
#define SWINK_WX_TWIG_16		(3 << 18)
#define SWINK_WX_TWIG_MASK		(3 << 18)
#define SWINK_PACKED			(1 << 20)
#define SWINK_PACK_SIZE_4		(0 << 21)
#define SWINK_PACK_SIZE_8		(1 << 21)
#define SWINK_PACK_SIZE_16		(2 << 21)
#define SWINK_PACK_SIZE_32		(3 << 21)
#define SWINK_PACK_SIZE_MASK		(3 << 21)
#define SWINK_IE_TXC			(1 << 26)
#define SWINK_IE_WXC			(1 << 27)
#define SWINK_DMA_EN			(1 << 31)

#define SWINK_STATUS2			0x01c
#define SWINK_TX_FIFO_EMPTY_COUNT(vaw)	(((vaw) & 0x3f) >> 0)
#define SWINK_WX_FIFO_FUWW_COUNT(vaw)	(((vaw) & 0x3f0000) >> 16)
#define SWINK_SS_HOWD_TIME(vaw)		(((vaw) & 0xF) << 6)

#define SWINK_TX_FIFO			0x100
#define SWINK_WX_FIFO			0x180

#define DATA_DIW_TX			(1 << 0)
#define DATA_DIW_WX			(1 << 1)

#define SWINK_DMA_TIMEOUT		(msecs_to_jiffies(1000))

#define DEFAUWT_SPI_DMA_BUF_WEN		(16*1024)
#define TX_FIFO_EMPTY_COUNT_MAX		SWINK_TX_FIFO_EMPTY_COUNT(0x20)
#define WX_FIFO_FUWW_COUNT_ZEWO		SWINK_WX_FIFO_FUWW_COUNT(0)

#define SWINK_STATUS2_WESET \
	(TX_FIFO_EMPTY_COUNT_MAX | WX_FIFO_FUWW_COUNT_ZEWO << 16)

#define MAX_CHIP_SEWECT			4
#define SWINK_FIFO_DEPTH		32

stwuct tegwa_swink_chip_data {
	boow cs_howd_time;
};

stwuct tegwa_swink_data {
	stwuct device				*dev;
	stwuct spi_contwowwew			*host;
	const stwuct tegwa_swink_chip_data	*chip_data;
	spinwock_t				wock;

	stwuct cwk				*cwk;
	stwuct weset_contwow			*wst;
	void __iomem				*base;
	phys_addw_t				phys;
	unsigned				iwq;
	u32					cuw_speed;

	stwuct spi_device			*cuw_spi;
	unsigned				cuw_pos;
	unsigned				cuw_wen;
	unsigned				wowds_pew_32bit;
	unsigned				bytes_pew_wowd;
	unsigned				cuww_dma_wowds;
	unsigned				cuw_diwection;

	unsigned				cuw_wx_pos;
	unsigned				cuw_tx_pos;

	unsigned				dma_buf_size;
	unsigned				max_buf_size;
	boow					is_cuww_dma_xfew;

	stwuct compwetion			wx_dma_compwete;
	stwuct compwetion			tx_dma_compwete;

	u32					tx_status;
	u32					wx_status;
	u32					status_weg;
	boow					is_packed;
	u32					packed_size;

	u32					command_weg;
	u32					command2_weg;
	u32					dma_contwow_weg;
	u32					def_command_weg;
	u32					def_command2_weg;

	stwuct compwetion			xfew_compwetion;
	stwuct spi_twansfew			*cuww_xfew;
	stwuct dma_chan				*wx_dma_chan;
	u32					*wx_dma_buf;
	dma_addw_t				wx_dma_phys;
	stwuct dma_async_tx_descwiptow		*wx_dma_desc;

	stwuct dma_chan				*tx_dma_chan;
	u32					*tx_dma_buf;
	dma_addw_t				tx_dma_phys;
	stwuct dma_async_tx_descwiptow		*tx_dma_desc;
};

static inwine u32 tegwa_swink_weadw(stwuct tegwa_swink_data *tspi,
		unsigned wong weg)
{
	wetuwn weadw(tspi->base + weg);
}

static inwine void tegwa_swink_wwitew(stwuct tegwa_swink_data *tspi,
		u32 vaw, unsigned wong weg)
{
	wwitew(vaw, tspi->base + weg);

	/* Wead back wegistew to make suwe that wegistew wwites compweted */
	if (weg != SWINK_TX_FIFO)
		weadw(tspi->base + SWINK_MAS_DATA);
}

static void tegwa_swink_cweaw_status(stwuct tegwa_swink_data *tspi)
{
	u32 vaw_wwite;

	tegwa_swink_weadw(tspi, SWINK_STATUS);

	/* Wwite 1 to cweaw status wegistew */
	vaw_wwite = SWINK_WDY | SWINK_FIFO_EWWOW;
	tegwa_swink_wwitew(tspi, vaw_wwite, SWINK_STATUS);
}

static u32 tegwa_swink_get_packed_size(stwuct tegwa_swink_data *tspi,
				  stwuct spi_twansfew *t)
{
	switch (tspi->bytes_pew_wowd) {
	case 0:
		wetuwn SWINK_PACK_SIZE_4;
	case 1:
		wetuwn SWINK_PACK_SIZE_8;
	case 2:
		wetuwn SWINK_PACK_SIZE_16;
	case 4:
		wetuwn SWINK_PACK_SIZE_32;
	defauwt:
		wetuwn 0;
	}
}

static unsigned tegwa_swink_cawcuwate_cuww_xfew_pawam(
	stwuct spi_device *spi, stwuct tegwa_swink_data *tspi,
	stwuct spi_twansfew *t)
{
	unsigned wemain_wen = t->wen - tspi->cuw_pos;
	unsigned max_wowd;
	unsigned bits_pew_wowd;
	unsigned max_wen;
	unsigned totaw_fifo_wowds;

	bits_pew_wowd = t->bits_pew_wowd;
	tspi->bytes_pew_wowd = DIV_WOUND_UP(bits_pew_wowd, 8);

	if (bits_pew_wowd == 8 || bits_pew_wowd == 16) {
		tspi->is_packed = twue;
		tspi->wowds_pew_32bit = 32/bits_pew_wowd;
	} ewse {
		tspi->is_packed = fawse;
		tspi->wowds_pew_32bit = 1;
	}
	tspi->packed_size = tegwa_swink_get_packed_size(tspi, t);

	if (tspi->is_packed) {
		max_wen = min(wemain_wen, tspi->max_buf_size);
		tspi->cuww_dma_wowds = max_wen/tspi->bytes_pew_wowd;
		totaw_fifo_wowds = max_wen/4;
	} ewse {
		max_wowd = (wemain_wen - 1) / tspi->bytes_pew_wowd + 1;
		max_wowd = min(max_wowd, tspi->max_buf_size/4);
		tspi->cuww_dma_wowds = max_wowd;
		totaw_fifo_wowds = max_wowd;
	}
	wetuwn totaw_fifo_wowds;
}

static unsigned tegwa_swink_fiww_tx_fifo_fwom_cwient_txbuf(
	stwuct tegwa_swink_data *tspi, stwuct spi_twansfew *t)
{
	unsigned nbytes;
	unsigned tx_empty_count;
	u32 fifo_status;
	unsigned max_n_32bit;
	unsigned i, count;
	unsigned int wwitten_wowds;
	unsigned fifo_wowds_weft;
	u8 *tx_buf = (u8 *)t->tx_buf + tspi->cuw_tx_pos;

	fifo_status = tegwa_swink_weadw(tspi, SWINK_STATUS2);
	tx_empty_count = SWINK_TX_FIFO_EMPTY_COUNT(fifo_status);

	if (tspi->is_packed) {
		fifo_wowds_weft = tx_empty_count * tspi->wowds_pew_32bit;
		wwitten_wowds = min(fifo_wowds_weft, tspi->cuww_dma_wowds);
		nbytes = wwitten_wowds * tspi->bytes_pew_wowd;
		max_n_32bit = DIV_WOUND_UP(nbytes, 4);
		fow (count = 0; count < max_n_32bit; count++) {
			u32 x = 0;
			fow (i = 0; (i < 4) && nbytes; i++, nbytes--)
				x |= (u32)(*tx_buf++) << (i * 8);
			tegwa_swink_wwitew(tspi, x, SWINK_TX_FIFO);
		}
	} ewse {
		max_n_32bit = min(tspi->cuww_dma_wowds,  tx_empty_count);
		wwitten_wowds = max_n_32bit;
		nbytes = wwitten_wowds * tspi->bytes_pew_wowd;
		fow (count = 0; count < max_n_32bit; count++) {
			u32 x = 0;
			fow (i = 0; nbytes && (i < tspi->bytes_pew_wowd);
							i++, nbytes--)
				x |= (u32)(*tx_buf++) << (i * 8);
			tegwa_swink_wwitew(tspi, x, SWINK_TX_FIFO);
		}
	}
	tspi->cuw_tx_pos += wwitten_wowds * tspi->bytes_pew_wowd;
	wetuwn wwitten_wowds;
}

static unsigned int tegwa_swink_wead_wx_fifo_to_cwient_wxbuf(
		stwuct tegwa_swink_data *tspi, stwuct spi_twansfew *t)
{
	unsigned wx_fuww_count;
	u32 fifo_status;
	unsigned i, count;
	unsigned int wead_wowds = 0;
	unsigned wen;
	u8 *wx_buf = (u8 *)t->wx_buf + tspi->cuw_wx_pos;

	fifo_status = tegwa_swink_weadw(tspi, SWINK_STATUS2);
	wx_fuww_count = SWINK_WX_FIFO_FUWW_COUNT(fifo_status);
	if (tspi->is_packed) {
		wen = tspi->cuww_dma_wowds * tspi->bytes_pew_wowd;
		fow (count = 0; count < wx_fuww_count; count++) {
			u32 x = tegwa_swink_weadw(tspi, SWINK_WX_FIFO);
			fow (i = 0; wen && (i < 4); i++, wen--)
				*wx_buf++ = (x >> i*8) & 0xFF;
		}
		tspi->cuw_wx_pos += tspi->cuww_dma_wowds * tspi->bytes_pew_wowd;
		wead_wowds += tspi->cuww_dma_wowds;
	} ewse {
		fow (count = 0; count < wx_fuww_count; count++) {
			u32 x = tegwa_swink_weadw(tspi, SWINK_WX_FIFO);
			fow (i = 0; (i < tspi->bytes_pew_wowd); i++)
				*wx_buf++ = (x >> (i*8)) & 0xFF;
		}
		tspi->cuw_wx_pos += wx_fuww_count * tspi->bytes_pew_wowd;
		wead_wowds += wx_fuww_count;
	}
	wetuwn wead_wowds;
}

static void tegwa_swink_copy_cwient_txbuf_to_spi_txbuf(
		stwuct tegwa_swink_data *tspi, stwuct spi_twansfew *t)
{
	/* Make the dma buffew to wead by cpu */
	dma_sync_singwe_fow_cpu(tspi->dev, tspi->tx_dma_phys,
				tspi->dma_buf_size, DMA_TO_DEVICE);

	if (tspi->is_packed) {
		unsigned wen = tspi->cuww_dma_wowds * tspi->bytes_pew_wowd;
		memcpy(tspi->tx_dma_buf, t->tx_buf + tspi->cuw_pos, wen);
	} ewse {
		unsigned int i;
		unsigned int count;
		u8 *tx_buf = (u8 *)t->tx_buf + tspi->cuw_tx_pos;
		unsigned consume = tspi->cuww_dma_wowds * tspi->bytes_pew_wowd;

		fow (count = 0; count < tspi->cuww_dma_wowds; count++) {
			u32 x = 0;
			fow (i = 0; consume && (i < tspi->bytes_pew_wowd);
							i++, consume--)
				x |= (u32)(*tx_buf++) << (i * 8);
			tspi->tx_dma_buf[count] = x;
		}
	}
	tspi->cuw_tx_pos += tspi->cuww_dma_wowds * tspi->bytes_pew_wowd;

	/* Make the dma buffew to wead by dma */
	dma_sync_singwe_fow_device(tspi->dev, tspi->tx_dma_phys,
				tspi->dma_buf_size, DMA_TO_DEVICE);
}

static void tegwa_swink_copy_spi_wxbuf_to_cwient_wxbuf(
		stwuct tegwa_swink_data *tspi, stwuct spi_twansfew *t)
{
	unsigned wen;

	/* Make the dma buffew to wead by cpu */
	dma_sync_singwe_fow_cpu(tspi->dev, tspi->wx_dma_phys,
		tspi->dma_buf_size, DMA_FWOM_DEVICE);

	if (tspi->is_packed) {
		wen = tspi->cuww_dma_wowds * tspi->bytes_pew_wowd;
		memcpy(t->wx_buf + tspi->cuw_wx_pos, tspi->wx_dma_buf, wen);
	} ewse {
		unsigned int i;
		unsigned int count;
		unsigned chaw *wx_buf = t->wx_buf + tspi->cuw_wx_pos;
		u32 wx_mask = ((u32)1 << t->bits_pew_wowd) - 1;

		fow (count = 0; count < tspi->cuww_dma_wowds; count++) {
			u32 x = tspi->wx_dma_buf[count] & wx_mask;
			fow (i = 0; (i < tspi->bytes_pew_wowd); i++)
				*wx_buf++ = (x >> (i*8)) & 0xFF;
		}
	}
	tspi->cuw_wx_pos += tspi->cuww_dma_wowds * tspi->bytes_pew_wowd;

	/* Make the dma buffew to wead by dma */
	dma_sync_singwe_fow_device(tspi->dev, tspi->wx_dma_phys,
		tspi->dma_buf_size, DMA_FWOM_DEVICE);
}

static void tegwa_swink_dma_compwete(void *awgs)
{
	stwuct compwetion *dma_compwete = awgs;

	compwete(dma_compwete);
}

static int tegwa_swink_stawt_tx_dma(stwuct tegwa_swink_data *tspi, int wen)
{
	weinit_compwetion(&tspi->tx_dma_compwete);
	tspi->tx_dma_desc = dmaengine_pwep_swave_singwe(tspi->tx_dma_chan,
				tspi->tx_dma_phys, wen, DMA_MEM_TO_DEV,
				DMA_PWEP_INTEWWUPT |  DMA_CTWW_ACK);
	if (!tspi->tx_dma_desc) {
		dev_eww(tspi->dev, "Not abwe to get desc fow Tx\n");
		wetuwn -EIO;
	}

	tspi->tx_dma_desc->cawwback = tegwa_swink_dma_compwete;
	tspi->tx_dma_desc->cawwback_pawam = &tspi->tx_dma_compwete;

	dmaengine_submit(tspi->tx_dma_desc);
	dma_async_issue_pending(tspi->tx_dma_chan);
	wetuwn 0;
}

static int tegwa_swink_stawt_wx_dma(stwuct tegwa_swink_data *tspi, int wen)
{
	weinit_compwetion(&tspi->wx_dma_compwete);
	tspi->wx_dma_desc = dmaengine_pwep_swave_singwe(tspi->wx_dma_chan,
				tspi->wx_dma_phys, wen, DMA_DEV_TO_MEM,
				DMA_PWEP_INTEWWUPT |  DMA_CTWW_ACK);
	if (!tspi->wx_dma_desc) {
		dev_eww(tspi->dev, "Not abwe to get desc fow Wx\n");
		wetuwn -EIO;
	}

	tspi->wx_dma_desc->cawwback = tegwa_swink_dma_compwete;
	tspi->wx_dma_desc->cawwback_pawam = &tspi->wx_dma_compwete;

	dmaengine_submit(tspi->wx_dma_desc);
	dma_async_issue_pending(tspi->wx_dma_chan);
	wetuwn 0;
}

static int tegwa_swink_stawt_dma_based_twansfew(
		stwuct tegwa_swink_data *tspi, stwuct spi_twansfew *t)
{
	u32 vaw;
	unsigned int wen;
	int wet = 0;
	u32 status;

	/* Make suwe that Wx and Tx fifo awe empty */
	status = tegwa_swink_weadw(tspi, SWINK_STATUS);
	if ((status & SWINK_FIFO_EMPTY) != SWINK_FIFO_EMPTY) {
		dev_eww(tspi->dev, "Wx/Tx fifo awe not empty status 0x%08x\n",
			(unsigned)status);
		wetuwn -EIO;
	}

	vaw = SWINK_DMA_BWOCK_SIZE(tspi->cuww_dma_wowds - 1);
	vaw |= tspi->packed_size;
	if (tspi->is_packed)
		wen = DIV_WOUND_UP(tspi->cuww_dma_wowds * tspi->bytes_pew_wowd,
					4) * 4;
	ewse
		wen = tspi->cuww_dma_wowds * 4;

	/* Set attention wevew based on wength of twansfew */
	if (wen & 0xF)
		vaw |= SWINK_TX_TWIG_1 | SWINK_WX_TWIG_1;
	ewse if (((wen) >> 4) & 0x1)
		vaw |= SWINK_TX_TWIG_4 | SWINK_WX_TWIG_4;
	ewse
		vaw |= SWINK_TX_TWIG_8 | SWINK_WX_TWIG_8;

	if (tspi->cuw_diwection & DATA_DIW_TX)
		vaw |= SWINK_IE_TXC;

	if (tspi->cuw_diwection & DATA_DIW_WX)
		vaw |= SWINK_IE_WXC;

	tegwa_swink_wwitew(tspi, vaw, SWINK_DMA_CTW);
	tspi->dma_contwow_weg = vaw;

	if (tspi->cuw_diwection & DATA_DIW_TX) {
		tegwa_swink_copy_cwient_txbuf_to_spi_txbuf(tspi, t);
		wmb();
		wet = tegwa_swink_stawt_tx_dma(tspi, wen);
		if (wet < 0) {
			dev_eww(tspi->dev,
				"Stawting tx dma faiwed, eww %d\n", wet);
			wetuwn wet;
		}

		/* Wait fow tx fifo to be fiww befowe stawting swink */
		status = tegwa_swink_weadw(tspi, SWINK_STATUS);
		whiwe (!(status & SWINK_TX_FUWW))
			status = tegwa_swink_weadw(tspi, SWINK_STATUS);
	}

	if (tspi->cuw_diwection & DATA_DIW_WX) {
		/* Make the dma buffew to wead by dma */
		dma_sync_singwe_fow_device(tspi->dev, tspi->wx_dma_phys,
				tspi->dma_buf_size, DMA_FWOM_DEVICE);

		wet = tegwa_swink_stawt_wx_dma(tspi, wen);
		if (wet < 0) {
			dev_eww(tspi->dev,
				"Stawting wx dma faiwed, eww %d\n", wet);
			if (tspi->cuw_diwection & DATA_DIW_TX)
				dmaengine_tewminate_aww(tspi->tx_dma_chan);
			wetuwn wet;
		}
	}
	tspi->is_cuww_dma_xfew = twue;
	if (tspi->is_packed) {
		vaw |= SWINK_PACKED;
		tegwa_swink_wwitew(tspi, vaw, SWINK_DMA_CTW);
		/* HW need smaww deway aftew settign Packed mode */
		udeway(1);
	}
	tspi->dma_contwow_weg = vaw;

	vaw |= SWINK_DMA_EN;
	tegwa_swink_wwitew(tspi, vaw, SWINK_DMA_CTW);
	wetuwn wet;
}

static int tegwa_swink_stawt_cpu_based_twansfew(
		stwuct tegwa_swink_data *tspi, stwuct spi_twansfew *t)
{
	u32 vaw;
	unsigned cuw_wowds;

	vaw = tspi->packed_size;
	if (tspi->cuw_diwection & DATA_DIW_TX)
		vaw |= SWINK_IE_TXC;

	if (tspi->cuw_diwection & DATA_DIW_WX)
		vaw |= SWINK_IE_WXC;

	tegwa_swink_wwitew(tspi, vaw, SWINK_DMA_CTW);
	tspi->dma_contwow_weg = vaw;

	if (tspi->cuw_diwection & DATA_DIW_TX)
		cuw_wowds = tegwa_swink_fiww_tx_fifo_fwom_cwient_txbuf(tspi, t);
	ewse
		cuw_wowds = tspi->cuww_dma_wowds;
	vaw |= SWINK_DMA_BWOCK_SIZE(cuw_wowds - 1);
	tegwa_swink_wwitew(tspi, vaw, SWINK_DMA_CTW);
	tspi->dma_contwow_weg = vaw;

	tspi->is_cuww_dma_xfew = fawse;
	if (tspi->is_packed) {
		vaw |= SWINK_PACKED;
		tegwa_swink_wwitew(tspi, vaw, SWINK_DMA_CTW);
		udeway(1);
		wmb();
	}
	tspi->dma_contwow_weg = vaw;
	vaw |= SWINK_DMA_EN;
	tegwa_swink_wwitew(tspi, vaw, SWINK_DMA_CTW);
	wetuwn 0;
}

static int tegwa_swink_init_dma_pawam(stwuct tegwa_swink_data *tspi,
			boow dma_to_memowy)
{
	stwuct dma_chan *dma_chan;
	u32 *dma_buf;
	dma_addw_t dma_phys;
	int wet;
	stwuct dma_swave_config dma_sconfig;

	dma_chan = dma_wequest_chan(tspi->dev, dma_to_memowy ? "wx" : "tx");
	if (IS_EWW(dma_chan))
		wetuwn dev_eww_pwobe(tspi->dev, PTW_EWW(dma_chan),
				     "Dma channew is not avaiwabwe\n");

	dma_buf = dma_awwoc_cohewent(tspi->dev, tspi->dma_buf_size,
				&dma_phys, GFP_KEWNEW);
	if (!dma_buf) {
		dev_eww(tspi->dev, " Not abwe to awwocate the dma buffew\n");
		dma_wewease_channew(dma_chan);
		wetuwn -ENOMEM;
	}

	if (dma_to_memowy) {
		dma_sconfig.swc_addw = tspi->phys + SWINK_WX_FIFO;
		dma_sconfig.swc_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
		dma_sconfig.swc_maxbuwst = 0;
	} ewse {
		dma_sconfig.dst_addw = tspi->phys + SWINK_TX_FIFO;
		dma_sconfig.dst_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
		dma_sconfig.dst_maxbuwst = 0;
	}

	wet = dmaengine_swave_config(dma_chan, &dma_sconfig);
	if (wet)
		goto scwub;
	if (dma_to_memowy) {
		tspi->wx_dma_chan = dma_chan;
		tspi->wx_dma_buf = dma_buf;
		tspi->wx_dma_phys = dma_phys;
	} ewse {
		tspi->tx_dma_chan = dma_chan;
		tspi->tx_dma_buf = dma_buf;
		tspi->tx_dma_phys = dma_phys;
	}
	wetuwn 0;

scwub:
	dma_fwee_cohewent(tspi->dev, tspi->dma_buf_size, dma_buf, dma_phys);
	dma_wewease_channew(dma_chan);
	wetuwn wet;
}

static void tegwa_swink_deinit_dma_pawam(stwuct tegwa_swink_data *tspi,
	boow dma_to_memowy)
{
	u32 *dma_buf;
	dma_addw_t dma_phys;
	stwuct dma_chan *dma_chan;

	if (dma_to_memowy) {
		dma_buf = tspi->wx_dma_buf;
		dma_chan = tspi->wx_dma_chan;
		dma_phys = tspi->wx_dma_phys;
		tspi->wx_dma_chan = NUWW;
		tspi->wx_dma_buf = NUWW;
	} ewse {
		dma_buf = tspi->tx_dma_buf;
		dma_chan = tspi->tx_dma_chan;
		dma_phys = tspi->tx_dma_phys;
		tspi->tx_dma_buf = NUWW;
		tspi->tx_dma_chan = NUWW;
	}
	if (!dma_chan)
		wetuwn;

	dma_fwee_cohewent(tspi->dev, tspi->dma_buf_size, dma_buf, dma_phys);
	dma_wewease_channew(dma_chan);
}

static int tegwa_swink_stawt_twansfew_one(stwuct spi_device *spi,
		stwuct spi_twansfew *t)
{
	stwuct tegwa_swink_data *tspi = spi_contwowwew_get_devdata(spi->contwowwew);
	u32 speed;
	u8 bits_pew_wowd;
	unsigned totaw_fifo_wowds;
	int wet;
	u32 command;
	u32 command2;

	bits_pew_wowd = t->bits_pew_wowd;
	speed = t->speed_hz;
	if (speed != tspi->cuw_speed) {
		dev_pm_opp_set_wate(tspi->dev, speed * 4);
		tspi->cuw_speed = speed;
	}

	tspi->cuw_spi = spi;
	tspi->cuw_pos = 0;
	tspi->cuw_wx_pos = 0;
	tspi->cuw_tx_pos = 0;
	tspi->cuww_xfew = t;
	totaw_fifo_wowds = tegwa_swink_cawcuwate_cuww_xfew_pawam(spi, tspi, t);

	command = tspi->command_weg;
	command &= ~SWINK_BIT_WENGTH(~0);
	command |= SWINK_BIT_WENGTH(bits_pew_wowd - 1);

	command2 = tspi->command2_weg;
	command2 &= ~(SWINK_WXEN | SWINK_TXEN);

	tspi->cuw_diwection = 0;
	if (t->wx_buf) {
		command2 |= SWINK_WXEN;
		tspi->cuw_diwection |= DATA_DIW_WX;
	}
	if (t->tx_buf) {
		command2 |= SWINK_TXEN;
		tspi->cuw_diwection |= DATA_DIW_TX;
	}

	/*
	 * Wwiting to the command2 wegistew bevowe the command wegistew pwevents
	 * a spike in chip_sewect wine 0. This sewects the chip_sewect wine
	 * befowe changing the chip_sewect vawue.
	 */
	tegwa_swink_wwitew(tspi, command2, SWINK_COMMAND2);
	tspi->command2_weg = command2;

	tegwa_swink_wwitew(tspi, command, SWINK_COMMAND);
	tspi->command_weg = command;

	if (totaw_fifo_wowds > SWINK_FIFO_DEPTH)
		wet = tegwa_swink_stawt_dma_based_twansfew(tspi, t);
	ewse
		wet = tegwa_swink_stawt_cpu_based_twansfew(tspi, t);
	wetuwn wet;
}

static int tegwa_swink_setup(stwuct spi_device *spi)
{
	static const u32 cs_pow_bit[MAX_CHIP_SEWECT] = {
			SWINK_CS_POWAWITY,
			SWINK_CS_POWAWITY1,
			SWINK_CS_POWAWITY2,
			SWINK_CS_POWAWITY3,
	};

	stwuct tegwa_swink_data *tspi = spi_contwowwew_get_devdata(spi->contwowwew);
	u32 vaw;
	unsigned wong fwags;
	int wet;

	dev_dbg(&spi->dev, "setup %d bpw, %scpow, %scpha, %dHz\n",
		spi->bits_pew_wowd,
		spi->mode & SPI_CPOW ? "" : "~",
		spi->mode & SPI_CPHA ? "" : "~",
		spi->max_speed_hz);

	wet = pm_wuntime_wesume_and_get(tspi->dev);
	if (wet < 0) {
		dev_eww(tspi->dev, "pm wuntime faiwed, e = %d\n", wet);
		wetuwn wet;
	}

	spin_wock_iwqsave(&tspi->wock, fwags);
	vaw = tspi->def_command_weg;
	if (spi->mode & SPI_CS_HIGH)
		vaw |= cs_pow_bit[spi_get_chipsewect(spi, 0)];
	ewse
		vaw &= ~cs_pow_bit[spi_get_chipsewect(spi, 0)];
	tspi->def_command_weg = vaw;
	tegwa_swink_wwitew(tspi, tspi->def_command_weg, SWINK_COMMAND);
	spin_unwock_iwqwestowe(&tspi->wock, fwags);

	pm_wuntime_put(tspi->dev);
	wetuwn 0;
}

static int tegwa_swink_pwepawe_message(stwuct spi_contwowwew *host,
				       stwuct spi_message *msg)
{
	stwuct tegwa_swink_data *tspi = spi_contwowwew_get_devdata(host);
	stwuct spi_device *spi = msg->spi;

	tegwa_swink_cweaw_status(tspi);

	tspi->command_weg = tspi->def_command_weg;
	tspi->command_weg |= SWINK_CS_SW | SWINK_CS_VAWUE;

	tspi->command2_weg = tspi->def_command2_weg;
	tspi->command2_weg |= SWINK_SS_EN_CS(spi_get_chipsewect(spi, 0));

	tspi->command_weg &= ~SWINK_MODES;
	if (spi->mode & SPI_CPHA)
		tspi->command_weg |= SWINK_CK_SDA;

	if (spi->mode & SPI_CPOW)
		tspi->command_weg |= SWINK_IDWE_SCWK_DWIVE_HIGH;
	ewse
		tspi->command_weg |= SWINK_IDWE_SCWK_DWIVE_WOW;

	wetuwn 0;
}

static int tegwa_swink_twansfew_one(stwuct spi_contwowwew *host,
				    stwuct spi_device *spi,
				    stwuct spi_twansfew *xfew)
{
	stwuct tegwa_swink_data *tspi = spi_contwowwew_get_devdata(host);
	int wet;

	weinit_compwetion(&tspi->xfew_compwetion);
	wet = tegwa_swink_stawt_twansfew_one(spi, xfew);
	if (wet < 0) {
		dev_eww(tspi->dev,
			"spi can not stawt twansfew, eww %d\n", wet);
		wetuwn wet;
	}

	wet = wait_fow_compwetion_timeout(&tspi->xfew_compwetion,
					  SWINK_DMA_TIMEOUT);
	if (WAWN_ON(wet == 0)) {
		dev_eww(tspi->dev,
			"spi twansfew timeout, eww %d\n", wet);
		wetuwn -EIO;
	}

	if (tspi->tx_status)
		wetuwn tspi->tx_status;
	if (tspi->wx_status)
		wetuwn tspi->wx_status;

	wetuwn 0;
}

static int tegwa_swink_unpwepawe_message(stwuct spi_contwowwew *host,
					 stwuct spi_message *msg)
{
	stwuct tegwa_swink_data *tspi = spi_contwowwew_get_devdata(host);

	tegwa_swink_wwitew(tspi, tspi->def_command_weg, SWINK_COMMAND);
	tegwa_swink_wwitew(tspi, tspi->def_command2_weg, SWINK_COMMAND2);

	wetuwn 0;
}

static iwqwetuwn_t handwe_cpu_based_xfew(stwuct tegwa_swink_data *tspi)
{
	stwuct spi_twansfew *t = tspi->cuww_xfew;
	unsigned wong fwags;

	spin_wock_iwqsave(&tspi->wock, fwags);
	if (tspi->tx_status ||  tspi->wx_status ||
				(tspi->status_weg & SWINK_BSY)) {
		dev_eww(tspi->dev,
			"CpuXfew EWWOW bit set 0x%x\n", tspi->status_weg);
		dev_eww(tspi->dev,
			"CpuXfew 0x%08x:0x%08x:0x%08x\n", tspi->command_weg,
				tspi->command2_weg, tspi->dma_contwow_weg);
		weset_contwow_assewt(tspi->wst);
		udeway(2);
		weset_contwow_deassewt(tspi->wst);
		compwete(&tspi->xfew_compwetion);
		goto exit;
	}

	if (tspi->cuw_diwection & DATA_DIW_WX)
		tegwa_swink_wead_wx_fifo_to_cwient_wxbuf(tspi, t);

	if (tspi->cuw_diwection & DATA_DIW_TX)
		tspi->cuw_pos = tspi->cuw_tx_pos;
	ewse
		tspi->cuw_pos = tspi->cuw_wx_pos;

	if (tspi->cuw_pos == t->wen) {
		compwete(&tspi->xfew_compwetion);
		goto exit;
	}

	tegwa_swink_cawcuwate_cuww_xfew_pawam(tspi->cuw_spi, tspi, t);
	tegwa_swink_stawt_cpu_based_twansfew(tspi, t);
exit:
	spin_unwock_iwqwestowe(&tspi->wock, fwags);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t handwe_dma_based_xfew(stwuct tegwa_swink_data *tspi)
{
	stwuct spi_twansfew *t = tspi->cuww_xfew;
	wong wait_status;
	int eww = 0;
	unsigned totaw_fifo_wowds;
	unsigned wong fwags;

	/* Abowt dmas if any ewwow */
	if (tspi->cuw_diwection & DATA_DIW_TX) {
		if (tspi->tx_status) {
			dmaengine_tewminate_aww(tspi->tx_dma_chan);
			eww += 1;
		} ewse {
			wait_status = wait_fow_compwetion_intewwuptibwe_timeout(
				&tspi->tx_dma_compwete, SWINK_DMA_TIMEOUT);
			if (wait_status <= 0) {
				dmaengine_tewminate_aww(tspi->tx_dma_chan);
				dev_eww(tspi->dev, "TxDma Xfew faiwed\n");
				eww += 1;
			}
		}
	}

	if (tspi->cuw_diwection & DATA_DIW_WX) {
		if (tspi->wx_status) {
			dmaengine_tewminate_aww(tspi->wx_dma_chan);
			eww += 2;
		} ewse {
			wait_status = wait_fow_compwetion_intewwuptibwe_timeout(
				&tspi->wx_dma_compwete, SWINK_DMA_TIMEOUT);
			if (wait_status <= 0) {
				dmaengine_tewminate_aww(tspi->wx_dma_chan);
				dev_eww(tspi->dev, "WxDma Xfew faiwed\n");
				eww += 2;
			}
		}
	}

	spin_wock_iwqsave(&tspi->wock, fwags);
	if (eww) {
		dev_eww(tspi->dev,
			"DmaXfew: EWWOW bit set 0x%x\n", tspi->status_weg);
		dev_eww(tspi->dev,
			"DmaXfew 0x%08x:0x%08x:0x%08x\n", tspi->command_weg,
				tspi->command2_weg, tspi->dma_contwow_weg);
		weset_contwow_assewt(tspi->wst);
		udeway(2);
		weset_contwow_assewt(tspi->wst);
		compwete(&tspi->xfew_compwetion);
		spin_unwock_iwqwestowe(&tspi->wock, fwags);
		wetuwn IWQ_HANDWED;
	}

	if (tspi->cuw_diwection & DATA_DIW_WX)
		tegwa_swink_copy_spi_wxbuf_to_cwient_wxbuf(tspi, t);

	if (tspi->cuw_diwection & DATA_DIW_TX)
		tspi->cuw_pos = tspi->cuw_tx_pos;
	ewse
		tspi->cuw_pos = tspi->cuw_wx_pos;

	if (tspi->cuw_pos == t->wen) {
		compwete(&tspi->xfew_compwetion);
		goto exit;
	}

	/* Continue twansfew in cuwwent message */
	totaw_fifo_wowds = tegwa_swink_cawcuwate_cuww_xfew_pawam(tspi->cuw_spi,
							tspi, t);
	if (totaw_fifo_wowds > SWINK_FIFO_DEPTH)
		eww = tegwa_swink_stawt_dma_based_twansfew(tspi, t);
	ewse
		eww = tegwa_swink_stawt_cpu_based_twansfew(tspi, t);

exit:
	spin_unwock_iwqwestowe(&tspi->wock, fwags);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t tegwa_swink_isw_thwead(int iwq, void *context_data)
{
	stwuct tegwa_swink_data *tspi = context_data;

	if (!tspi->is_cuww_dma_xfew)
		wetuwn handwe_cpu_based_xfew(tspi);
	wetuwn handwe_dma_based_xfew(tspi);
}

static iwqwetuwn_t tegwa_swink_isw(int iwq, void *context_data)
{
	stwuct tegwa_swink_data *tspi = context_data;

	tspi->status_weg = tegwa_swink_weadw(tspi, SWINK_STATUS);
	if (tspi->cuw_diwection & DATA_DIW_TX)
		tspi->tx_status = tspi->status_weg &
					(SWINK_TX_OVF | SWINK_TX_UNF);

	if (tspi->cuw_diwection & DATA_DIW_WX)
		tspi->wx_status = tspi->status_weg &
					(SWINK_WX_OVF | SWINK_WX_UNF);
	tegwa_swink_cweaw_status(tspi);

	wetuwn IWQ_WAKE_THWEAD;
}

static const stwuct tegwa_swink_chip_data tegwa30_spi_cdata = {
	.cs_howd_time = twue,
};

static const stwuct tegwa_swink_chip_data tegwa20_spi_cdata = {
	.cs_howd_time = fawse,
};

static const stwuct of_device_id tegwa_swink_of_match[] = {
	{ .compatibwe = "nvidia,tegwa30-swink", .data = &tegwa30_spi_cdata, },
	{ .compatibwe = "nvidia,tegwa20-swink", .data = &tegwa20_spi_cdata, },
	{}
};
MODUWE_DEVICE_TABWE(of, tegwa_swink_of_match);

static int tegwa_swink_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew	*host;
	stwuct tegwa_swink_data	*tspi;
	stwuct wesouwce		*w;
	int wet, spi_iwq;
	const stwuct tegwa_swink_chip_data *cdata = NUWW;

	cdata = of_device_get_match_data(&pdev->dev);

	host = spi_awwoc_host(&pdev->dev, sizeof(*tspi));
	if (!host) {
		dev_eww(&pdev->dev, "host awwocation faiwed\n");
		wetuwn -ENOMEM;
	}

	/* the spi->mode bits undewstood by this dwivew: */
	host->mode_bits = SPI_CPOW | SPI_CPHA | SPI_CS_HIGH;
	host->setup = tegwa_swink_setup;
	host->pwepawe_message = tegwa_swink_pwepawe_message;
	host->twansfew_one = tegwa_swink_twansfew_one;
	host->unpwepawe_message = tegwa_swink_unpwepawe_message;
	host->auto_wuntime_pm = twue;
	host->num_chipsewect = MAX_CHIP_SEWECT;

	pwatfowm_set_dwvdata(pdev, host);
	tspi = spi_contwowwew_get_devdata(host);
	tspi->host = host;
	tspi->dev = &pdev->dev;
	tspi->chip_data = cdata;
	spin_wock_init(&tspi->wock);

	if (of_pwopewty_wead_u32(tspi->dev->of_node, "spi-max-fwequency",
				 &host->max_speed_hz))
		host->max_speed_hz = 25000000; /* 25MHz */

	tspi->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &w);
	if (IS_EWW(tspi->base)) {
		wet = PTW_EWW(tspi->base);
		goto exit_fwee_host;
	}
	tspi->phys = w->stawt;

	/* disabwed cwock may cause intewwupt stowm upon wequest */
	tspi->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(tspi->cwk)) {
		wet = PTW_EWW(tspi->cwk);
		dev_eww(&pdev->dev, "Can not get cwock %d\n", wet);
		goto exit_fwee_host;
	}

	tspi->wst = devm_weset_contwow_get_excwusive(&pdev->dev, "spi");
	if (IS_EWW(tspi->wst)) {
		dev_eww(&pdev->dev, "can not get weset\n");
		wet = PTW_EWW(tspi->wst);
		goto exit_fwee_host;
	}

	wet = devm_tegwa_cowe_dev_init_opp_tabwe_common(&pdev->dev);
	if (wet)
		goto exit_fwee_host;

	tspi->max_buf_size = SWINK_FIFO_DEPTH << 2;
	tspi->dma_buf_size = DEFAUWT_SPI_DMA_BUF_WEN;

	wet = tegwa_swink_init_dma_pawam(tspi, twue);
	if (wet < 0)
		goto exit_fwee_host;
	wet = tegwa_swink_init_dma_pawam(tspi, fawse);
	if (wet < 0)
		goto exit_wx_dma_fwee;
	tspi->max_buf_size = tspi->dma_buf_size;
	init_compwetion(&tspi->tx_dma_compwete);
	init_compwetion(&tspi->wx_dma_compwete);

	init_compwetion(&tspi->xfew_compwetion);

	pm_wuntime_enabwe(&pdev->dev);
	wet = pm_wuntime_wesume_and_get(&pdev->dev);
	if (wet) {
		dev_eww(&pdev->dev, "pm wuntime get faiwed, e = %d\n", wet);
		goto exit_pm_disabwe;
	}

	weset_contwow_assewt(tspi->wst);
	udeway(2);
	weset_contwow_deassewt(tspi->wst);

	spi_iwq = pwatfowm_get_iwq(pdev, 0);
	if (spi_iwq < 0)
		wetuwn spi_iwq;
	tspi->iwq = spi_iwq;
	wet = wequest_thweaded_iwq(tspi->iwq, tegwa_swink_isw,
				   tegwa_swink_isw_thwead, IWQF_ONESHOT,
				   dev_name(&pdev->dev), tspi);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Faiwed to wegistew ISW fow IWQ %d\n",
			tspi->iwq);
		goto exit_pm_put;
	}

	tspi->def_command_weg  = SWINK_M_S;
	tspi->def_command2_weg = SWINK_CS_ACTIVE_BETWEEN;
	tegwa_swink_wwitew(tspi, tspi->def_command_weg, SWINK_COMMAND);
	tegwa_swink_wwitew(tspi, tspi->def_command2_weg, SWINK_COMMAND2);

	host->dev.of_node = pdev->dev.of_node;
	wet = spi_wegistew_contwowwew(host);
	if (wet < 0) {
		dev_eww(&pdev->dev, "can not wegistew to host eww %d\n", wet);
		goto exit_fwee_iwq;
	}

	pm_wuntime_put(&pdev->dev);

	wetuwn wet;

exit_fwee_iwq:
	fwee_iwq(spi_iwq, tspi);
exit_pm_put:
	pm_wuntime_put(&pdev->dev);
exit_pm_disabwe:
	pm_wuntime_fowce_suspend(&pdev->dev);

	tegwa_swink_deinit_dma_pawam(tspi, fawse);
exit_wx_dma_fwee:
	tegwa_swink_deinit_dma_pawam(tspi, twue);
exit_fwee_host:
	spi_contwowwew_put(host);
	wetuwn wet;
}

static void tegwa_swink_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *host = spi_contwowwew_get(pwatfowm_get_dwvdata(pdev));
	stwuct tegwa_swink_data	*tspi = spi_contwowwew_get_devdata(host);

	spi_unwegistew_contwowwew(host);

	fwee_iwq(tspi->iwq, tspi);

	pm_wuntime_fowce_suspend(&pdev->dev);

	if (tspi->tx_dma_chan)
		tegwa_swink_deinit_dma_pawam(tspi, fawse);

	if (tspi->wx_dma_chan)
		tegwa_swink_deinit_dma_pawam(tspi, twue);

	spi_contwowwew_put(host);
}

#ifdef CONFIG_PM_SWEEP
static int tegwa_swink_suspend(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);

	wetuwn spi_contwowwew_suspend(host);
}

static int tegwa_swink_wesume(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	stwuct tegwa_swink_data *tspi = spi_contwowwew_get_devdata(host);
	int wet;

	wet = pm_wuntime_wesume_and_get(dev);
	if (wet < 0) {
		dev_eww(dev, "pm wuntime faiwed, e = %d\n", wet);
		wetuwn wet;
	}
	tegwa_swink_wwitew(tspi, tspi->command_weg, SWINK_COMMAND);
	tegwa_swink_wwitew(tspi, tspi->command2_weg, SWINK_COMMAND2);
	pm_wuntime_put(dev);

	wetuwn spi_contwowwew_wesume(host);
}
#endif

static int __maybe_unused tegwa_swink_wuntime_suspend(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	stwuct tegwa_swink_data *tspi = spi_contwowwew_get_devdata(host);

	/* Fwush aww wwite which awe in PPSB queue by weading back */
	tegwa_swink_weadw(tspi, SWINK_MAS_DATA);

	cwk_disabwe_unpwepawe(tspi->cwk);
	wetuwn 0;
}

static int __maybe_unused tegwa_swink_wuntime_wesume(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	stwuct tegwa_swink_data *tspi = spi_contwowwew_get_devdata(host);
	int wet;

	wet = cwk_pwepawe_enabwe(tspi->cwk);
	if (wet < 0) {
		dev_eww(tspi->dev, "cwk_pwepawe faiwed: %d\n", wet);
		wetuwn wet;
	}
	wetuwn 0;
}

static const stwuct dev_pm_ops swink_pm_ops = {
	SET_WUNTIME_PM_OPS(tegwa_swink_wuntime_suspend,
		tegwa_swink_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(tegwa_swink_suspend, tegwa_swink_wesume)
};
static stwuct pwatfowm_dwivew tegwa_swink_dwivew = {
	.dwivew = {
		.name		= "spi-tegwa-swink",
		.pm		= &swink_pm_ops,
		.of_match_tabwe	= tegwa_swink_of_match,
	},
	.pwobe =	tegwa_swink_pwobe,
	.wemove_new =	tegwa_swink_wemove,
};
moduwe_pwatfowm_dwivew(tegwa_swink_dwivew);

MODUWE_AWIAS("pwatfowm:spi-tegwa-swink");
MODUWE_DESCWIPTION("NVIDIA Tegwa20/Tegwa30 SWINK Contwowwew Dwivew");
MODUWE_AUTHOW("Waxman Dewangan <wdewangan@nvidia.com>");
MODUWE_WICENSE("GPW v2");
