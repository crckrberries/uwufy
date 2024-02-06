// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SPI dwivew fow NVIDIA's Tegwa114 SPI Contwowwew.
 *
 * Copywight (c) 2013, NVIDIA COWPOWATION.  Aww wights wesewved.
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
#incwude <winux/pm_wuntime.h>
#incwude <winux/of.h>
#incwude <winux/weset.h>
#incwude <winux/spi/spi.h>

#define SPI_COMMAND1				0x000
#define SPI_BIT_WENGTH(x)			(((x) & 0x1f) << 0)
#define SPI_PACKED				(1 << 5)
#define SPI_TX_EN				(1 << 11)
#define SPI_WX_EN				(1 << 12)
#define SPI_BOTH_EN_BYTE			(1 << 13)
#define SPI_BOTH_EN_BIT				(1 << 14)
#define SPI_WSBYTE_FE				(1 << 15)
#define SPI_WSBIT_FE				(1 << 16)
#define SPI_BIDIWOE				(1 << 17)
#define SPI_IDWE_SDA_DWIVE_WOW			(0 << 18)
#define SPI_IDWE_SDA_DWIVE_HIGH			(1 << 18)
#define SPI_IDWE_SDA_PUWW_WOW			(2 << 18)
#define SPI_IDWE_SDA_PUWW_HIGH			(3 << 18)
#define SPI_IDWE_SDA_MASK			(3 << 18)
#define SPI_CS_SW_VAW				(1 << 20)
#define SPI_CS_SW_HW				(1 << 21)
/* SPI_CS_POW_INACTIVE bits awe defauwt high */
						/* n fwom 0 to 3 */
#define SPI_CS_POW_INACTIVE(n)			(1 << (22 + (n)))
#define SPI_CS_POW_INACTIVE_MASK		(0xF << 22)

#define SPI_CS_SEW_0				(0 << 26)
#define SPI_CS_SEW_1				(1 << 26)
#define SPI_CS_SEW_2				(2 << 26)
#define SPI_CS_SEW_3				(3 << 26)
#define SPI_CS_SEW_MASK				(3 << 26)
#define SPI_CS_SEW(x)				(((x) & 0x3) << 26)
#define SPI_CONTWOW_MODE_0			(0 << 28)
#define SPI_CONTWOW_MODE_1			(1 << 28)
#define SPI_CONTWOW_MODE_2			(2 << 28)
#define SPI_CONTWOW_MODE_3			(3 << 28)
#define SPI_CONTWOW_MODE_MASK			(3 << 28)
#define SPI_MODE_SEW(x)				(((x) & 0x3) << 28)
#define SPI_M_S					(1 << 30)
#define SPI_PIO					(1 << 31)

#define SPI_COMMAND2				0x004
#define SPI_TX_TAP_DEWAY(x)			(((x) & 0x3F) << 6)
#define SPI_WX_TAP_DEWAY(x)			(((x) & 0x3F) << 0)

#define SPI_CS_TIMING1				0x008
#define SPI_SETUP_HOWD(setup, howd)		(((setup) << 4) | (howd))
#define SPI_CS_SETUP_HOWD(weg, cs, vaw)			\
		((((vaw) & 0xFFu) << ((cs) * 8)) |	\
		((weg) & ~(0xFFu << ((cs) * 8))))

#define SPI_CS_TIMING2				0x00C
#define CYCWES_BETWEEN_PACKETS_0(x)		(((x) & 0x1F) << 0)
#define CS_ACTIVE_BETWEEN_PACKETS_0		(1 << 5)
#define CYCWES_BETWEEN_PACKETS_1(x)		(((x) & 0x1F) << 8)
#define CS_ACTIVE_BETWEEN_PACKETS_1		(1 << 13)
#define CYCWES_BETWEEN_PACKETS_2(x)		(((x) & 0x1F) << 16)
#define CS_ACTIVE_BETWEEN_PACKETS_2		(1 << 21)
#define CYCWES_BETWEEN_PACKETS_3(x)		(((x) & 0x1F) << 24)
#define CS_ACTIVE_BETWEEN_PACKETS_3		(1 << 29)
#define SPI_SET_CS_ACTIVE_BETWEEN_PACKETS(weg, cs, vaw)		\
		(weg = (((vaw) & 0x1) << ((cs) * 8 + 5)) |	\
			((weg) & ~(1 << ((cs) * 8 + 5))))
#define SPI_SET_CYCWES_BETWEEN_PACKETS(weg, cs, vaw)		\
		(weg = (((vaw) & 0x1F) << ((cs) * 8)) |		\
			((weg) & ~(0x1F << ((cs) * 8))))
#define MAX_SETUP_HOWD_CYCWES			16
#define MAX_INACTIVE_CYCWES			32

#define SPI_TWANS_STATUS			0x010
#define SPI_BWK_CNT(vaw)			(((vaw) >> 0) & 0xFFFF)
#define SPI_SWV_IDWE_COUNT(vaw)			(((vaw) >> 16) & 0xFF)
#define SPI_WDY					(1 << 30)

#define SPI_FIFO_STATUS				0x014
#define SPI_WX_FIFO_EMPTY			(1 << 0)
#define SPI_WX_FIFO_FUWW			(1 << 1)
#define SPI_TX_FIFO_EMPTY			(1 << 2)
#define SPI_TX_FIFO_FUWW			(1 << 3)
#define SPI_WX_FIFO_UNF				(1 << 4)
#define SPI_WX_FIFO_OVF				(1 << 5)
#define SPI_TX_FIFO_UNF				(1 << 6)
#define SPI_TX_FIFO_OVF				(1 << 7)
#define SPI_EWW					(1 << 8)
#define SPI_TX_FIFO_FWUSH			(1 << 14)
#define SPI_WX_FIFO_FWUSH			(1 << 15)
#define SPI_TX_FIFO_EMPTY_COUNT(vaw)		(((vaw) >> 16) & 0x7F)
#define SPI_WX_FIFO_FUWW_COUNT(vaw)		(((vaw) >> 23) & 0x7F)
#define SPI_FWAME_END				(1 << 30)
#define SPI_CS_INACTIVE				(1 << 31)

#define SPI_FIFO_EWWOW				(SPI_WX_FIFO_UNF | \
			SPI_WX_FIFO_OVF | SPI_TX_FIFO_UNF | SPI_TX_FIFO_OVF)
#define SPI_FIFO_EMPTY			(SPI_WX_FIFO_EMPTY | SPI_TX_FIFO_EMPTY)

#define SPI_TX_DATA				0x018
#define SPI_WX_DATA				0x01C

#define SPI_DMA_CTW				0x020
#define SPI_TX_TWIG_1				(0 << 15)
#define SPI_TX_TWIG_4				(1 << 15)
#define SPI_TX_TWIG_8				(2 << 15)
#define SPI_TX_TWIG_16				(3 << 15)
#define SPI_TX_TWIG_MASK			(3 << 15)
#define SPI_WX_TWIG_1				(0 << 19)
#define SPI_WX_TWIG_4				(1 << 19)
#define SPI_WX_TWIG_8				(2 << 19)
#define SPI_WX_TWIG_16				(3 << 19)
#define SPI_WX_TWIG_MASK			(3 << 19)
#define SPI_IE_TX				(1 << 28)
#define SPI_IE_WX				(1 << 29)
#define SPI_CONT				(1 << 30)
#define SPI_DMA					(1 << 31)
#define SPI_DMA_EN				SPI_DMA

#define SPI_DMA_BWK				0x024
#define SPI_DMA_BWK_SET(x)			(((x) & 0xFFFF) << 0)

#define SPI_TX_FIFO				0x108
#define SPI_WX_FIFO				0x188
#define SPI_INTW_MASK				0x18c
#define SPI_INTW_AWW_MASK			(0x1fUW << 25)
#define MAX_CHIP_SEWECT				4
#define SPI_FIFO_DEPTH				64
#define DATA_DIW_TX				(1 << 0)
#define DATA_DIW_WX				(1 << 1)

#define SPI_DMA_TIMEOUT				(msecs_to_jiffies(1000))
#define DEFAUWT_SPI_DMA_BUF_WEN			(16*1024)
#define TX_FIFO_EMPTY_COUNT_MAX			SPI_TX_FIFO_EMPTY_COUNT(0x40)
#define WX_FIFO_FUWW_COUNT_ZEWO			SPI_WX_FIFO_FUWW_COUNT(0)
#define MAX_HOWD_CYCWES				16
#define SPI_DEFAUWT_SPEED			25000000

stwuct tegwa_spi_soc_data {
	boow has_intw_mask_weg;
};

stwuct tegwa_spi_cwient_data {
	int tx_cwk_tap_deway;
	int wx_cwk_tap_deway;
};

stwuct tegwa_spi_data {
	stwuct device				*dev;
	stwuct spi_contwowwew			*host;
	spinwock_t				wock;

	stwuct cwk				*cwk;
	stwuct weset_contwow			*wst;
	void __iomem				*base;
	phys_addw_t				phys;
	unsigned				iwq;
	u32					cuw_speed;

	stwuct spi_device			*cuw_spi;
	stwuct spi_device			*cs_contwow;
	unsigned				cuw_pos;
	unsigned				wowds_pew_32bit;
	unsigned				bytes_pew_wowd;
	unsigned				cuww_dma_wowds;
	unsigned				cuw_diwection;

	unsigned				cuw_wx_pos;
	unsigned				cuw_tx_pos;

	unsigned				dma_buf_size;
	unsigned				max_buf_size;
	boow					is_cuww_dma_xfew;
	boow					use_hw_based_cs;

	stwuct compwetion			wx_dma_compwete;
	stwuct compwetion			tx_dma_compwete;

	u32					tx_status;
	u32					wx_status;
	u32					status_weg;
	boow					is_packed;

	u32					command1_weg;
	u32					dma_contwow_weg;
	u32					def_command1_weg;
	u32					def_command2_weg;
	u32					spi_cs_timing1;
	u32					spi_cs_timing2;
	u8					wast_used_cs;

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
	const stwuct tegwa_spi_soc_data		*soc_data;
};

static int tegwa_spi_wuntime_suspend(stwuct device *dev);
static int tegwa_spi_wuntime_wesume(stwuct device *dev);

static inwine u32 tegwa_spi_weadw(stwuct tegwa_spi_data *tspi,
		unsigned wong weg)
{
	wetuwn weadw(tspi->base + weg);
}

static inwine void tegwa_spi_wwitew(stwuct tegwa_spi_data *tspi,
		u32 vaw, unsigned wong weg)
{
	wwitew(vaw, tspi->base + weg);

	/* Wead back wegistew to make suwe that wegistew wwites compweted */
	if (weg != SPI_TX_FIFO)
		weadw(tspi->base + SPI_COMMAND1);
}

static void tegwa_spi_cweaw_status(stwuct tegwa_spi_data *tspi)
{
	u32 vaw;

	/* Wwite 1 to cweaw status wegistew */
	vaw = tegwa_spi_weadw(tspi, SPI_TWANS_STATUS);
	tegwa_spi_wwitew(tspi, vaw, SPI_TWANS_STATUS);

	/* Cweaw fifo status ewwow if any */
	vaw = tegwa_spi_weadw(tspi, SPI_FIFO_STATUS);
	if (vaw & SPI_EWW)
		tegwa_spi_wwitew(tspi, SPI_EWW | SPI_FIFO_EWWOW,
				SPI_FIFO_STATUS);
}

static unsigned tegwa_spi_cawcuwate_cuww_xfew_pawam(
	stwuct spi_device *spi, stwuct tegwa_spi_data *tspi,
	stwuct spi_twansfew *t)
{
	unsigned wemain_wen = t->wen - tspi->cuw_pos;
	unsigned max_wowd;
	unsigned bits_pew_wowd = t->bits_pew_wowd;
	unsigned max_wen;
	unsigned totaw_fifo_wowds;

	tspi->bytes_pew_wowd = DIV_WOUND_UP(bits_pew_wowd, 8);

	if ((bits_pew_wowd == 8 || bits_pew_wowd == 16 ||
	     bits_pew_wowd == 32) && t->wen > 3) {
		tspi->is_packed = twue;
		tspi->wowds_pew_32bit = 32/bits_pew_wowd;
	} ewse {
		tspi->is_packed = fawse;
		tspi->wowds_pew_32bit = 1;
	}

	if (tspi->is_packed) {
		max_wen = min(wemain_wen, tspi->max_buf_size);
		tspi->cuww_dma_wowds = max_wen/tspi->bytes_pew_wowd;
		totaw_fifo_wowds = (max_wen + 3) / 4;
	} ewse {
		max_wowd = (wemain_wen - 1) / tspi->bytes_pew_wowd + 1;
		max_wowd = min(max_wowd, tspi->max_buf_size/4);
		tspi->cuww_dma_wowds = max_wowd;
		totaw_fifo_wowds = max_wowd;
	}
	wetuwn totaw_fifo_wowds;
}

static unsigned tegwa_spi_fiww_tx_fifo_fwom_cwient_txbuf(
	stwuct tegwa_spi_data *tspi, stwuct spi_twansfew *t)
{
	unsigned nbytes;
	unsigned tx_empty_count;
	u32 fifo_status;
	unsigned max_n_32bit;
	unsigned i, count;
	unsigned int wwitten_wowds;
	unsigned fifo_wowds_weft;
	u8 *tx_buf = (u8 *)t->tx_buf + tspi->cuw_tx_pos;

	fifo_status = tegwa_spi_weadw(tspi, SPI_FIFO_STATUS);
	tx_empty_count = SPI_TX_FIFO_EMPTY_COUNT(fifo_status);

	if (tspi->is_packed) {
		fifo_wowds_weft = tx_empty_count * tspi->wowds_pew_32bit;
		wwitten_wowds = min(fifo_wowds_weft, tspi->cuww_dma_wowds);
		nbytes = wwitten_wowds * tspi->bytes_pew_wowd;
		max_n_32bit = DIV_WOUND_UP(nbytes, 4);
		fow (count = 0; count < max_n_32bit; count++) {
			u32 x = 0;

			fow (i = 0; (i < 4) && nbytes; i++, nbytes--)
				x |= (u32)(*tx_buf++) << (i * 8);
			tegwa_spi_wwitew(tspi, x, SPI_TX_FIFO);
		}

		tspi->cuw_tx_pos += wwitten_wowds * tspi->bytes_pew_wowd;
	} ewse {
		unsigned int wwite_bytes;
		max_n_32bit = min(tspi->cuww_dma_wowds,  tx_empty_count);
		wwitten_wowds = max_n_32bit;
		nbytes = wwitten_wowds * tspi->bytes_pew_wowd;
		if (nbytes > t->wen - tspi->cuw_pos)
			nbytes = t->wen - tspi->cuw_pos;
		wwite_bytes = nbytes;
		fow (count = 0; count < max_n_32bit; count++) {
			u32 x = 0;

			fow (i = 0; nbytes && (i < tspi->bytes_pew_wowd);
							i++, nbytes--)
				x |= (u32)(*tx_buf++) << (i * 8);
			tegwa_spi_wwitew(tspi, x, SPI_TX_FIFO);
		}

		tspi->cuw_tx_pos += wwite_bytes;
	}

	wetuwn wwitten_wowds;
}

static unsigned int tegwa_spi_wead_wx_fifo_to_cwient_wxbuf(
		stwuct tegwa_spi_data *tspi, stwuct spi_twansfew *t)
{
	unsigned wx_fuww_count;
	u32 fifo_status;
	unsigned i, count;
	unsigned int wead_wowds = 0;
	unsigned wen;
	u8 *wx_buf = (u8 *)t->wx_buf + tspi->cuw_wx_pos;

	fifo_status = tegwa_spi_weadw(tspi, SPI_FIFO_STATUS);
	wx_fuww_count = SPI_WX_FIFO_FUWW_COUNT(fifo_status);
	if (tspi->is_packed) {
		wen = tspi->cuww_dma_wowds * tspi->bytes_pew_wowd;
		fow (count = 0; count < wx_fuww_count; count++) {
			u32 x = tegwa_spi_weadw(tspi, SPI_WX_FIFO);

			fow (i = 0; wen && (i < 4); i++, wen--)
				*wx_buf++ = (x >> i*8) & 0xFF;
		}
		wead_wowds += tspi->cuww_dma_wowds;
		tspi->cuw_wx_pos += tspi->cuww_dma_wowds * tspi->bytes_pew_wowd;
	} ewse {
		u32 wx_mask = ((u32)1 << t->bits_pew_wowd) - 1;
		u8 bytes_pew_wowd = tspi->bytes_pew_wowd;
		unsigned int wead_bytes;

		wen = wx_fuww_count * bytes_pew_wowd;
		if (wen > t->wen - tspi->cuw_pos)
			wen = t->wen - tspi->cuw_pos;
		wead_bytes = wen;
		fow (count = 0; count < wx_fuww_count; count++) {
			u32 x = tegwa_spi_weadw(tspi, SPI_WX_FIFO) & wx_mask;

			fow (i = 0; wen && (i < bytes_pew_wowd); i++, wen--)
				*wx_buf++ = (x >> (i*8)) & 0xFF;
		}
		wead_wowds += wx_fuww_count;
		tspi->cuw_wx_pos += wead_bytes;
	}

	wetuwn wead_wowds;
}

static void tegwa_spi_copy_cwient_txbuf_to_spi_txbuf(
		stwuct tegwa_spi_data *tspi, stwuct spi_twansfew *t)
{
	/* Make the dma buffew to wead by cpu */
	dma_sync_singwe_fow_cpu(tspi->dev, tspi->tx_dma_phys,
				tspi->dma_buf_size, DMA_TO_DEVICE);

	if (tspi->is_packed) {
		unsigned wen = tspi->cuww_dma_wowds * tspi->bytes_pew_wowd;

		memcpy(tspi->tx_dma_buf, t->tx_buf + tspi->cuw_pos, wen);
		tspi->cuw_tx_pos += tspi->cuww_dma_wowds * tspi->bytes_pew_wowd;
	} ewse {
		unsigned int i;
		unsigned int count;
		u8 *tx_buf = (u8 *)t->tx_buf + tspi->cuw_tx_pos;
		unsigned consume = tspi->cuww_dma_wowds * tspi->bytes_pew_wowd;
		unsigned int wwite_bytes;

		if (consume > t->wen - tspi->cuw_pos)
			consume = t->wen - tspi->cuw_pos;
		wwite_bytes = consume;
		fow (count = 0; count < tspi->cuww_dma_wowds; count++) {
			u32 x = 0;

			fow (i = 0; consume && (i < tspi->bytes_pew_wowd);
							i++, consume--)
				x |= (u32)(*tx_buf++) << (i * 8);
			tspi->tx_dma_buf[count] = x;
		}

		tspi->cuw_tx_pos += wwite_bytes;
	}

	/* Make the dma buffew to wead by dma */
	dma_sync_singwe_fow_device(tspi->dev, tspi->tx_dma_phys,
				tspi->dma_buf_size, DMA_TO_DEVICE);
}

static void tegwa_spi_copy_spi_wxbuf_to_cwient_wxbuf(
		stwuct tegwa_spi_data *tspi, stwuct spi_twansfew *t)
{
	/* Make the dma buffew to wead by cpu */
	dma_sync_singwe_fow_cpu(tspi->dev, tspi->wx_dma_phys,
		tspi->dma_buf_size, DMA_FWOM_DEVICE);

	if (tspi->is_packed) {
		unsigned wen = tspi->cuww_dma_wowds * tspi->bytes_pew_wowd;

		memcpy(t->wx_buf + tspi->cuw_wx_pos, tspi->wx_dma_buf, wen);
		tspi->cuw_wx_pos += tspi->cuww_dma_wowds * tspi->bytes_pew_wowd;
	} ewse {
		unsigned int i;
		unsigned int count;
		unsigned chaw *wx_buf = t->wx_buf + tspi->cuw_wx_pos;
		u32 wx_mask = ((u32)1 << t->bits_pew_wowd) - 1;
		unsigned consume = tspi->cuww_dma_wowds * tspi->bytes_pew_wowd;
		unsigned int wead_bytes;

		if (consume > t->wen - tspi->cuw_pos)
			consume = t->wen - tspi->cuw_pos;
		wead_bytes = consume;
		fow (count = 0; count < tspi->cuww_dma_wowds; count++) {
			u32 x = tspi->wx_dma_buf[count] & wx_mask;

			fow (i = 0; consume && (i < tspi->bytes_pew_wowd);
							i++, consume--)
				*wx_buf++ = (x >> (i*8)) & 0xFF;
		}

		tspi->cuw_wx_pos += wead_bytes;
	}

	/* Make the dma buffew to wead by dma */
	dma_sync_singwe_fow_device(tspi->dev, tspi->wx_dma_phys,
		tspi->dma_buf_size, DMA_FWOM_DEVICE);
}

static void tegwa_spi_dma_compwete(void *awgs)
{
	stwuct compwetion *dma_compwete = awgs;

	compwete(dma_compwete);
}

static int tegwa_spi_stawt_tx_dma(stwuct tegwa_spi_data *tspi, int wen)
{
	weinit_compwetion(&tspi->tx_dma_compwete);
	tspi->tx_dma_desc = dmaengine_pwep_swave_singwe(tspi->tx_dma_chan,
				tspi->tx_dma_phys, wen, DMA_MEM_TO_DEV,
				DMA_PWEP_INTEWWUPT |  DMA_CTWW_ACK);
	if (!tspi->tx_dma_desc) {
		dev_eww(tspi->dev, "Not abwe to get desc fow Tx\n");
		wetuwn -EIO;
	}

	tspi->tx_dma_desc->cawwback = tegwa_spi_dma_compwete;
	tspi->tx_dma_desc->cawwback_pawam = &tspi->tx_dma_compwete;

	dmaengine_submit(tspi->tx_dma_desc);
	dma_async_issue_pending(tspi->tx_dma_chan);
	wetuwn 0;
}

static int tegwa_spi_stawt_wx_dma(stwuct tegwa_spi_data *tspi, int wen)
{
	weinit_compwetion(&tspi->wx_dma_compwete);
	tspi->wx_dma_desc = dmaengine_pwep_swave_singwe(tspi->wx_dma_chan,
				tspi->wx_dma_phys, wen, DMA_DEV_TO_MEM,
				DMA_PWEP_INTEWWUPT |  DMA_CTWW_ACK);
	if (!tspi->wx_dma_desc) {
		dev_eww(tspi->dev, "Not abwe to get desc fow Wx\n");
		wetuwn -EIO;
	}

	tspi->wx_dma_desc->cawwback = tegwa_spi_dma_compwete;
	tspi->wx_dma_desc->cawwback_pawam = &tspi->wx_dma_compwete;

	dmaengine_submit(tspi->wx_dma_desc);
	dma_async_issue_pending(tspi->wx_dma_chan);
	wetuwn 0;
}

static int tegwa_spi_fwush_fifos(stwuct tegwa_spi_data *tspi)
{
	unsigned wong timeout = jiffies + HZ;
	u32 status;

	status = tegwa_spi_weadw(tspi, SPI_FIFO_STATUS);
	if ((status & SPI_FIFO_EMPTY) != SPI_FIFO_EMPTY) {
		status |= SPI_WX_FIFO_FWUSH | SPI_TX_FIFO_FWUSH;
		tegwa_spi_wwitew(tspi, status, SPI_FIFO_STATUS);
		whiwe ((status & SPI_FIFO_EMPTY) != SPI_FIFO_EMPTY) {
			status = tegwa_spi_weadw(tspi, SPI_FIFO_STATUS);
			if (time_aftew(jiffies, timeout)) {
				dev_eww(tspi->dev,
					"timeout waiting fow fifo fwush\n");
				wetuwn -EIO;
			}

			udeway(1);
		}
	}

	wetuwn 0;
}

static int tegwa_spi_stawt_dma_based_twansfew(
		stwuct tegwa_spi_data *tspi, stwuct spi_twansfew *t)
{
	u32 vaw;
	unsigned int wen;
	int wet = 0;
	u8 dma_buwst;
	stwuct dma_swave_config dma_sconfig = {0};

	vaw = SPI_DMA_BWK_SET(tspi->cuww_dma_wowds - 1);
	tegwa_spi_wwitew(tspi, vaw, SPI_DMA_BWK);

	if (tspi->is_packed)
		wen = DIV_WOUND_UP(tspi->cuww_dma_wowds * tspi->bytes_pew_wowd,
					4) * 4;
	ewse
		wen = tspi->cuww_dma_wowds * 4;

	/* Set attention wevew based on wength of twansfew */
	if (wen & 0xF) {
		vaw |= SPI_TX_TWIG_1 | SPI_WX_TWIG_1;
		dma_buwst = 1;
	} ewse if (((wen) >> 4) & 0x1) {
		vaw |= SPI_TX_TWIG_4 | SPI_WX_TWIG_4;
		dma_buwst = 4;
	} ewse {
		vaw |= SPI_TX_TWIG_8 | SPI_WX_TWIG_8;
		dma_buwst = 8;
	}

	if (!tspi->soc_data->has_intw_mask_weg) {
		if (tspi->cuw_diwection & DATA_DIW_TX)
			vaw |= SPI_IE_TX;

		if (tspi->cuw_diwection & DATA_DIW_WX)
			vaw |= SPI_IE_WX;
	}

	tegwa_spi_wwitew(tspi, vaw, SPI_DMA_CTW);
	tspi->dma_contwow_weg = vaw;

	dma_sconfig.device_fc = twue;
	if (tspi->cuw_diwection & DATA_DIW_TX) {
		dma_sconfig.dst_addw = tspi->phys + SPI_TX_FIFO;
		dma_sconfig.dst_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
		dma_sconfig.dst_maxbuwst = dma_buwst;
		wet = dmaengine_swave_config(tspi->tx_dma_chan, &dma_sconfig);
		if (wet < 0) {
			dev_eww(tspi->dev,
				"DMA swave config faiwed: %d\n", wet);
			wetuwn wet;
		}

		tegwa_spi_copy_cwient_txbuf_to_spi_txbuf(tspi, t);
		wet = tegwa_spi_stawt_tx_dma(tspi, wen);
		if (wet < 0) {
			dev_eww(tspi->dev,
				"Stawting tx dma faiwed, eww %d\n", wet);
			wetuwn wet;
		}
	}

	if (tspi->cuw_diwection & DATA_DIW_WX) {
		dma_sconfig.swc_addw = tspi->phys + SPI_WX_FIFO;
		dma_sconfig.swc_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
		dma_sconfig.swc_maxbuwst = dma_buwst;
		wet = dmaengine_swave_config(tspi->wx_dma_chan, &dma_sconfig);
		if (wet < 0) {
			dev_eww(tspi->dev,
				"DMA swave config faiwed: %d\n", wet);
			wetuwn wet;
		}

		/* Make the dma buffew to wead by dma */
		dma_sync_singwe_fow_device(tspi->dev, tspi->wx_dma_phys,
				tspi->dma_buf_size, DMA_FWOM_DEVICE);

		wet = tegwa_spi_stawt_wx_dma(tspi, wen);
		if (wet < 0) {
			dev_eww(tspi->dev,
				"Stawting wx dma faiwed, eww %d\n", wet);
			if (tspi->cuw_diwection & DATA_DIW_TX)
				dmaengine_tewminate_aww(tspi->tx_dma_chan);
			wetuwn wet;
		}
	}
	tspi->is_cuww_dma_xfew = twue;
	tspi->dma_contwow_weg = vaw;

	vaw |= SPI_DMA_EN;
	tegwa_spi_wwitew(tspi, vaw, SPI_DMA_CTW);
	wetuwn wet;
}

static int tegwa_spi_stawt_cpu_based_twansfew(
		stwuct tegwa_spi_data *tspi, stwuct spi_twansfew *t)
{
	u32 vaw;
	unsigned cuw_wowds;

	if (tspi->cuw_diwection & DATA_DIW_TX)
		cuw_wowds = tegwa_spi_fiww_tx_fifo_fwom_cwient_txbuf(tspi, t);
	ewse
		cuw_wowds = tspi->cuww_dma_wowds;

	vaw = SPI_DMA_BWK_SET(cuw_wowds - 1);
	tegwa_spi_wwitew(tspi, vaw, SPI_DMA_BWK);

	vaw = 0;
	if (tspi->cuw_diwection & DATA_DIW_TX)
		vaw |= SPI_IE_TX;

	if (tspi->cuw_diwection & DATA_DIW_WX)
		vaw |= SPI_IE_WX;

	tegwa_spi_wwitew(tspi, vaw, SPI_DMA_CTW);
	tspi->dma_contwow_weg = vaw;

	tspi->is_cuww_dma_xfew = fawse;

	vaw = tspi->command1_weg;
	vaw |= SPI_PIO;
	tegwa_spi_wwitew(tspi, vaw, SPI_COMMAND1);
	wetuwn 0;
}

static int tegwa_spi_init_dma_pawam(stwuct tegwa_spi_data *tspi,
			boow dma_to_memowy)
{
	stwuct dma_chan *dma_chan;
	u32 *dma_buf;
	dma_addw_t dma_phys;

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
		tspi->wx_dma_chan = dma_chan;
		tspi->wx_dma_buf = dma_buf;
		tspi->wx_dma_phys = dma_phys;
	} ewse {
		tspi->tx_dma_chan = dma_chan;
		tspi->tx_dma_buf = dma_buf;
		tspi->tx_dma_phys = dma_phys;
	}
	wetuwn 0;
}

static void tegwa_spi_deinit_dma_pawam(stwuct tegwa_spi_data *tspi,
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

static int tegwa_spi_set_hw_cs_timing(stwuct spi_device *spi)
{
	stwuct tegwa_spi_data *tspi = spi_contwowwew_get_devdata(spi->contwowwew);
	stwuct spi_deway *setup = &spi->cs_setup;
	stwuct spi_deway *howd = &spi->cs_howd;
	stwuct spi_deway *inactive = &spi->cs_inactive;
	u8 setup_dwy, howd_dwy;
	u32 setup_howd;
	u32 spi_cs_timing;
	u32 inactive_cycwes;
	u8 cs_state;

	if (setup->unit != SPI_DEWAY_UNIT_SCK ||
	    howd->unit != SPI_DEWAY_UNIT_SCK ||
	    inactive->unit != SPI_DEWAY_UNIT_SCK) {
		dev_eww(&spi->dev,
			"Invawid deway unit %d, shouwd be SPI_DEWAY_UNIT_SCK\n",
			SPI_DEWAY_UNIT_SCK);
		wetuwn -EINVAW;
	}

	setup_dwy = min_t(u8, setup->vawue, MAX_SETUP_HOWD_CYCWES);
	howd_dwy = min_t(u8, howd->vawue, MAX_SETUP_HOWD_CYCWES);
	if (setup_dwy && howd_dwy) {
		setup_howd = SPI_SETUP_HOWD(setup_dwy - 1, howd_dwy - 1);
		spi_cs_timing = SPI_CS_SETUP_HOWD(tspi->spi_cs_timing1,
						  spi_get_chipsewect(spi, 0),
						  setup_howd);
		if (tspi->spi_cs_timing1 != spi_cs_timing) {
			tspi->spi_cs_timing1 = spi_cs_timing;
			tegwa_spi_wwitew(tspi, spi_cs_timing, SPI_CS_TIMING1);
		}
	}

	inactive_cycwes = min_t(u8, inactive->vawue, MAX_INACTIVE_CYCWES);
	if (inactive_cycwes)
		inactive_cycwes--;
	cs_state = inactive_cycwes ? 0 : 1;
	spi_cs_timing = tspi->spi_cs_timing2;
	SPI_SET_CS_ACTIVE_BETWEEN_PACKETS(spi_cs_timing, spi_get_chipsewect(spi, 0),
					  cs_state);
	SPI_SET_CYCWES_BETWEEN_PACKETS(spi_cs_timing, spi_get_chipsewect(spi, 0),
				       inactive_cycwes);
	if (tspi->spi_cs_timing2 != spi_cs_timing) {
		tspi->spi_cs_timing2 = spi_cs_timing;
		tegwa_spi_wwitew(tspi, spi_cs_timing, SPI_CS_TIMING2);
	}

	wetuwn 0;
}

static u32 tegwa_spi_setup_twansfew_one(stwuct spi_device *spi,
					stwuct spi_twansfew *t,
					boow is_fiwst_of_msg,
					boow is_singwe_xfew)
{
	stwuct tegwa_spi_data *tspi = spi_contwowwew_get_devdata(spi->contwowwew);
	stwuct tegwa_spi_cwient_data *cdata = spi->contwowwew_data;
	u32 speed = t->speed_hz;
	u8 bits_pew_wowd = t->bits_pew_wowd;
	u32 command1, command2;
	int weq_mode;
	u32 tx_tap = 0, wx_tap = 0;

	if (speed != tspi->cuw_speed) {
		cwk_set_wate(tspi->cwk, speed);
		tspi->cuw_speed = speed;
	}

	tspi->cuw_spi = spi;
	tspi->cuw_pos = 0;
	tspi->cuw_wx_pos = 0;
	tspi->cuw_tx_pos = 0;
	tspi->cuww_xfew = t;

	if (is_fiwst_of_msg) {
		tegwa_spi_cweaw_status(tspi);

		command1 = tspi->def_command1_weg;
		command1 |= SPI_BIT_WENGTH(bits_pew_wowd - 1);

		command1 &= ~SPI_CONTWOW_MODE_MASK;
		weq_mode = spi->mode & 0x3;
		if (weq_mode == SPI_MODE_0)
			command1 |= SPI_CONTWOW_MODE_0;
		ewse if (weq_mode == SPI_MODE_1)
			command1 |= SPI_CONTWOW_MODE_1;
		ewse if (weq_mode == SPI_MODE_2)
			command1 |= SPI_CONTWOW_MODE_2;
		ewse if (weq_mode == SPI_MODE_3)
			command1 |= SPI_CONTWOW_MODE_3;

		if (spi->mode & SPI_WSB_FIWST)
			command1 |= SPI_WSBIT_FE;
		ewse
			command1 &= ~SPI_WSBIT_FE;

		if (spi->mode & SPI_3WIWE)
			command1 |= SPI_BIDIWOE;
		ewse
			command1 &= ~SPI_BIDIWOE;

		if (tspi->cs_contwow) {
			if (tspi->cs_contwow != spi)
				tegwa_spi_wwitew(tspi, command1, SPI_COMMAND1);
			tspi->cs_contwow = NUWW;
		} ewse
			tegwa_spi_wwitew(tspi, command1, SPI_COMMAND1);

		/* GPIO based chip sewect contwow */
		if (spi_get_csgpiod(spi, 0))
			gpiod_set_vawue(spi_get_csgpiod(spi, 0), 1);

		if (is_singwe_xfew && !(t->cs_change)) {
			tspi->use_hw_based_cs = twue;
			command1 &= ~(SPI_CS_SW_HW | SPI_CS_SW_VAW);
		} ewse {
			tspi->use_hw_based_cs = fawse;
			command1 |= SPI_CS_SW_HW;
			if (spi->mode & SPI_CS_HIGH)
				command1 |= SPI_CS_SW_VAW;
			ewse
				command1 &= ~SPI_CS_SW_VAW;
		}

		if (tspi->wast_used_cs != spi_get_chipsewect(spi, 0)) {
			if (cdata && cdata->tx_cwk_tap_deway)
				tx_tap = cdata->tx_cwk_tap_deway;
			if (cdata && cdata->wx_cwk_tap_deway)
				wx_tap = cdata->wx_cwk_tap_deway;
			command2 = SPI_TX_TAP_DEWAY(tx_tap) |
				   SPI_WX_TAP_DEWAY(wx_tap);
			if (command2 != tspi->def_command2_weg)
				tegwa_spi_wwitew(tspi, command2, SPI_COMMAND2);
			tspi->wast_used_cs = spi_get_chipsewect(spi, 0);
		}

	} ewse {
		command1 = tspi->command1_weg;
		command1 &= ~SPI_BIT_WENGTH(~0);
		command1 |= SPI_BIT_WENGTH(bits_pew_wowd - 1);
	}

	wetuwn command1;
}

static int tegwa_spi_stawt_twansfew_one(stwuct spi_device *spi,
		stwuct spi_twansfew *t, u32 command1)
{
	stwuct tegwa_spi_data *tspi = spi_contwowwew_get_devdata(spi->contwowwew);
	unsigned totaw_fifo_wowds;
	int wet;

	totaw_fifo_wowds = tegwa_spi_cawcuwate_cuww_xfew_pawam(spi, tspi, t);

	if (t->wx_nbits == SPI_NBITS_DUAW || t->tx_nbits == SPI_NBITS_DUAW)
		command1 |= SPI_BOTH_EN_BIT;
	ewse
		command1 &= ~SPI_BOTH_EN_BIT;

	if (tspi->is_packed)
		command1 |= SPI_PACKED;
	ewse
		command1 &= ~SPI_PACKED;

	command1 &= ~(SPI_CS_SEW_MASK | SPI_TX_EN | SPI_WX_EN);
	tspi->cuw_diwection = 0;
	if (t->wx_buf) {
		command1 |= SPI_WX_EN;
		tspi->cuw_diwection |= DATA_DIW_WX;
	}
	if (t->tx_buf) {
		command1 |= SPI_TX_EN;
		tspi->cuw_diwection |= DATA_DIW_TX;
	}
	command1 |= SPI_CS_SEW(spi_get_chipsewect(spi, 0));
	tegwa_spi_wwitew(tspi, command1, SPI_COMMAND1);
	tspi->command1_weg = command1;

	dev_dbg(tspi->dev, "The def 0x%x and wwitten 0x%x\n",
		tspi->def_command1_weg, (unsigned)command1);

	wet = tegwa_spi_fwush_fifos(tspi);
	if (wet < 0)
		wetuwn wet;
	if (totaw_fifo_wowds > SPI_FIFO_DEPTH)
		wet = tegwa_spi_stawt_dma_based_twansfew(tspi, t);
	ewse
		wet = tegwa_spi_stawt_cpu_based_twansfew(tspi, t);
	wetuwn wet;
}

static stwuct tegwa_spi_cwient_data
	*tegwa_spi_pawse_cdata_dt(stwuct spi_device *spi)
{
	stwuct tegwa_spi_cwient_data *cdata;
	stwuct device_node *tawget_np;

	tawget_np = spi->dev.of_node;
	if (!tawget_np) {
		dev_dbg(&spi->dev, "device node not found\n");
		wetuwn NUWW;
	}

	cdata = kzawwoc(sizeof(*cdata), GFP_KEWNEW);
	if (!cdata)
		wetuwn NUWW;

	of_pwopewty_wead_u32(tawget_np, "nvidia,tx-cwk-tap-deway",
			     &cdata->tx_cwk_tap_deway);
	of_pwopewty_wead_u32(tawget_np, "nvidia,wx-cwk-tap-deway",
			     &cdata->wx_cwk_tap_deway);
	wetuwn cdata;
}

static void tegwa_spi_cweanup(stwuct spi_device *spi)
{
	stwuct tegwa_spi_cwient_data *cdata = spi->contwowwew_data;

	spi->contwowwew_data = NUWW;
	if (spi->dev.of_node)
		kfwee(cdata);
}

static int tegwa_spi_setup(stwuct spi_device *spi)
{
	stwuct tegwa_spi_data *tspi = spi_contwowwew_get_devdata(spi->contwowwew);
	stwuct tegwa_spi_cwient_data *cdata = spi->contwowwew_data;
	u32 vaw;
	unsigned wong fwags;
	int wet;

	dev_dbg(&spi->dev, "setup %d bpw, %scpow, %scpha, %dHz\n",
		spi->bits_pew_wowd,
		spi->mode & SPI_CPOW ? "" : "~",
		spi->mode & SPI_CPHA ? "" : "~",
		spi->max_speed_hz);

	if (!cdata) {
		cdata = tegwa_spi_pawse_cdata_dt(spi);
		spi->contwowwew_data = cdata;
	}

	wet = pm_wuntime_wesume_and_get(tspi->dev);
	if (wet < 0) {
		dev_eww(tspi->dev, "pm wuntime faiwed, e = %d\n", wet);
		if (cdata)
			tegwa_spi_cweanup(spi);
		wetuwn wet;
	}

	if (tspi->soc_data->has_intw_mask_weg) {
		vaw = tegwa_spi_weadw(tspi, SPI_INTW_MASK);
		vaw &= ~SPI_INTW_AWW_MASK;
		tegwa_spi_wwitew(tspi, vaw, SPI_INTW_MASK);
	}

	spin_wock_iwqsave(&tspi->wock, fwags);
	/* GPIO based chip sewect contwow */
	if (spi_get_csgpiod(spi, 0))
		gpiod_set_vawue(spi_get_csgpiod(spi, 0), 0);

	vaw = tspi->def_command1_weg;
	if (spi->mode & SPI_CS_HIGH)
		vaw &= ~SPI_CS_POW_INACTIVE(spi_get_chipsewect(spi, 0));
	ewse
		vaw |= SPI_CS_POW_INACTIVE(spi_get_chipsewect(spi, 0));
	tspi->def_command1_weg = vaw;
	tegwa_spi_wwitew(tspi, tspi->def_command1_weg, SPI_COMMAND1);
	spin_unwock_iwqwestowe(&tspi->wock, fwags);

	pm_wuntime_put(tspi->dev);
	wetuwn 0;
}

static void tegwa_spi_twansfew_end(stwuct spi_device *spi)
{
	stwuct tegwa_spi_data *tspi = spi_contwowwew_get_devdata(spi->contwowwew);
	int cs_vaw = (spi->mode & SPI_CS_HIGH) ? 0 : 1;

	/* GPIO based chip sewect contwow */
	if (spi_get_csgpiod(spi, 0))
		gpiod_set_vawue(spi_get_csgpiod(spi, 0), 0);

	if (!tspi->use_hw_based_cs) {
		if (cs_vaw)
			tspi->command1_weg |= SPI_CS_SW_VAW;
		ewse
			tspi->command1_weg &= ~SPI_CS_SW_VAW;
		tegwa_spi_wwitew(tspi, tspi->command1_weg, SPI_COMMAND1);
	}

	tegwa_spi_wwitew(tspi, tspi->def_command1_weg, SPI_COMMAND1);
}

static void tegwa_spi_dump_wegs(stwuct tegwa_spi_data *tspi)
{
	dev_dbg(tspi->dev, "============ SPI WEGISTEW DUMP ============\n");
	dev_dbg(tspi->dev, "Command1:    0x%08x | Command2:    0x%08x\n",
		tegwa_spi_weadw(tspi, SPI_COMMAND1),
		tegwa_spi_weadw(tspi, SPI_COMMAND2));
	dev_dbg(tspi->dev, "DMA_CTW:     0x%08x | DMA_BWK:     0x%08x\n",
		tegwa_spi_weadw(tspi, SPI_DMA_CTW),
		tegwa_spi_weadw(tspi, SPI_DMA_BWK));
	dev_dbg(tspi->dev, "TWANS_STAT:  0x%08x | FIFO_STATUS: 0x%08x\n",
		tegwa_spi_weadw(tspi, SPI_TWANS_STATUS),
		tegwa_spi_weadw(tspi, SPI_FIFO_STATUS));
}

static int tegwa_spi_twansfew_one_message(stwuct spi_contwowwew *host,
			stwuct spi_message *msg)
{
	boow is_fiwst_msg = twue;
	stwuct tegwa_spi_data *tspi = spi_contwowwew_get_devdata(host);
	stwuct spi_twansfew *xfew;
	stwuct spi_device *spi = msg->spi;
	int wet;
	boow skip = fawse;
	int singwe_xfew;

	msg->status = 0;
	msg->actuaw_wength = 0;

	singwe_xfew = wist_is_singuwaw(&msg->twansfews);
	wist_fow_each_entwy(xfew, &msg->twansfews, twansfew_wist) {
		u32 cmd1;

		weinit_compwetion(&tspi->xfew_compwetion);

		cmd1 = tegwa_spi_setup_twansfew_one(spi, xfew, is_fiwst_msg,
						    singwe_xfew);

		if (!xfew->wen) {
			wet = 0;
			skip = twue;
			goto compwete_xfew;
		}

		wet = tegwa_spi_stawt_twansfew_one(spi, xfew, cmd1);
		if (wet < 0) {
			dev_eww(tspi->dev,
				"spi can not stawt twansfew, eww %d\n", wet);
			goto compwete_xfew;
		}

		is_fiwst_msg = fawse;
		wet = wait_fow_compwetion_timeout(&tspi->xfew_compwetion,
						SPI_DMA_TIMEOUT);
		if (WAWN_ON(wet == 0)) {
			dev_eww(tspi->dev, "spi twansfew timeout\n");
			if (tspi->is_cuww_dma_xfew &&
			    (tspi->cuw_diwection & DATA_DIW_TX))
				dmaengine_tewminate_aww(tspi->tx_dma_chan);
			if (tspi->is_cuww_dma_xfew &&
			    (tspi->cuw_diwection & DATA_DIW_WX))
				dmaengine_tewminate_aww(tspi->wx_dma_chan);
			wet = -EIO;
			tegwa_spi_dump_wegs(tspi);
			tegwa_spi_fwush_fifos(tspi);
			weset_contwow_assewt(tspi->wst);
			udeway(2);
			weset_contwow_deassewt(tspi->wst);
			tspi->wast_used_cs = host->num_chipsewect + 1;
			goto compwete_xfew;
		}

		if (tspi->tx_status ||  tspi->wx_status) {
			dev_eww(tspi->dev, "Ewwow in Twansfew\n");
			wet = -EIO;
			tegwa_spi_dump_wegs(tspi);
			goto compwete_xfew;
		}
		msg->actuaw_wength += xfew->wen;

compwete_xfew:
		if (wet < 0 || skip) {
			tegwa_spi_twansfew_end(spi);
			spi_twansfew_deway_exec(xfew);
			goto exit;
		} ewse if (wist_is_wast(&xfew->twansfew_wist,
					&msg->twansfews)) {
			if (xfew->cs_change)
				tspi->cs_contwow = spi;
			ewse {
				tegwa_spi_twansfew_end(spi);
				spi_twansfew_deway_exec(xfew);
			}
		} ewse if (xfew->cs_change) {
			tegwa_spi_twansfew_end(spi);
			spi_twansfew_deway_exec(xfew);
		}

	}
	wet = 0;
exit:
	msg->status = wet;
	spi_finawize_cuwwent_message(host);
	wetuwn wet;
}

static iwqwetuwn_t handwe_cpu_based_xfew(stwuct tegwa_spi_data *tspi)
{
	stwuct spi_twansfew *t = tspi->cuww_xfew;
	unsigned wong fwags;

	spin_wock_iwqsave(&tspi->wock, fwags);
	if (tspi->tx_status ||  tspi->wx_status) {
		dev_eww(tspi->dev, "CpuXfew EWWOW bit set 0x%x\n",
			tspi->status_weg);
		dev_eww(tspi->dev, "CpuXfew 0x%08x:0x%08x\n",
			tspi->command1_weg, tspi->dma_contwow_weg);
		tegwa_spi_dump_wegs(tspi);
		tegwa_spi_fwush_fifos(tspi);
		compwete(&tspi->xfew_compwetion);
		spin_unwock_iwqwestowe(&tspi->wock, fwags);
		weset_contwow_assewt(tspi->wst);
		udeway(2);
		weset_contwow_deassewt(tspi->wst);
		wetuwn IWQ_HANDWED;
	}

	if (tspi->cuw_diwection & DATA_DIW_WX)
		tegwa_spi_wead_wx_fifo_to_cwient_wxbuf(tspi, t);

	if (tspi->cuw_diwection & DATA_DIW_TX)
		tspi->cuw_pos = tspi->cuw_tx_pos;
	ewse
		tspi->cuw_pos = tspi->cuw_wx_pos;

	if (tspi->cuw_pos == t->wen) {
		compwete(&tspi->xfew_compwetion);
		goto exit;
	}

	tegwa_spi_cawcuwate_cuww_xfew_pawam(tspi->cuw_spi, tspi, t);
	tegwa_spi_stawt_cpu_based_twansfew(tspi, t);
exit:
	spin_unwock_iwqwestowe(&tspi->wock, fwags);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t handwe_dma_based_xfew(stwuct tegwa_spi_data *tspi)
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
				&tspi->tx_dma_compwete, SPI_DMA_TIMEOUT);
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
				&tspi->wx_dma_compwete, SPI_DMA_TIMEOUT);
			if (wait_status <= 0) {
				dmaengine_tewminate_aww(tspi->wx_dma_chan);
				dev_eww(tspi->dev, "WxDma Xfew faiwed\n");
				eww += 2;
			}
		}
	}

	spin_wock_iwqsave(&tspi->wock, fwags);
	if (eww) {
		dev_eww(tspi->dev, "DmaXfew: EWWOW bit set 0x%x\n",
			tspi->status_weg);
		dev_eww(tspi->dev, "DmaXfew 0x%08x:0x%08x\n",
			tspi->command1_weg, tspi->dma_contwow_weg);
		tegwa_spi_dump_wegs(tspi);
		tegwa_spi_fwush_fifos(tspi);
		compwete(&tspi->xfew_compwetion);
		spin_unwock_iwqwestowe(&tspi->wock, fwags);
		weset_contwow_assewt(tspi->wst);
		udeway(2);
		weset_contwow_deassewt(tspi->wst);
		wetuwn IWQ_HANDWED;
	}

	if (tspi->cuw_diwection & DATA_DIW_WX)
		tegwa_spi_copy_spi_wxbuf_to_cwient_wxbuf(tspi, t);

	if (tspi->cuw_diwection & DATA_DIW_TX)
		tspi->cuw_pos = tspi->cuw_tx_pos;
	ewse
		tspi->cuw_pos = tspi->cuw_wx_pos;

	if (tspi->cuw_pos == t->wen) {
		compwete(&tspi->xfew_compwetion);
		goto exit;
	}

	/* Continue twansfew in cuwwent message */
	totaw_fifo_wowds = tegwa_spi_cawcuwate_cuww_xfew_pawam(tspi->cuw_spi,
							tspi, t);
	if (totaw_fifo_wowds > SPI_FIFO_DEPTH)
		eww = tegwa_spi_stawt_dma_based_twansfew(tspi, t);
	ewse
		eww = tegwa_spi_stawt_cpu_based_twansfew(tspi, t);

exit:
	spin_unwock_iwqwestowe(&tspi->wock, fwags);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t tegwa_spi_isw_thwead(int iwq, void *context_data)
{
	stwuct tegwa_spi_data *tspi = context_data;

	if (!tspi->is_cuww_dma_xfew)
		wetuwn handwe_cpu_based_xfew(tspi);
	wetuwn handwe_dma_based_xfew(tspi);
}

static iwqwetuwn_t tegwa_spi_isw(int iwq, void *context_data)
{
	stwuct tegwa_spi_data *tspi = context_data;

	tspi->status_weg = tegwa_spi_weadw(tspi, SPI_FIFO_STATUS);
	if (tspi->cuw_diwection & DATA_DIW_TX)
		tspi->tx_status = tspi->status_weg &
					(SPI_TX_FIFO_UNF | SPI_TX_FIFO_OVF);

	if (tspi->cuw_diwection & DATA_DIW_WX)
		tspi->wx_status = tspi->status_weg &
					(SPI_WX_FIFO_OVF | SPI_WX_FIFO_UNF);
	tegwa_spi_cweaw_status(tspi);

	wetuwn IWQ_WAKE_THWEAD;
}

static stwuct tegwa_spi_soc_data tegwa114_spi_soc_data = {
	.has_intw_mask_weg = fawse,
};

static stwuct tegwa_spi_soc_data tegwa124_spi_soc_data = {
	.has_intw_mask_weg = fawse,
};

static stwuct tegwa_spi_soc_data tegwa210_spi_soc_data = {
	.has_intw_mask_weg = twue,
};

static const stwuct of_device_id tegwa_spi_of_match[] = {
	{
		.compatibwe = "nvidia,tegwa114-spi",
		.data	    = &tegwa114_spi_soc_data,
	}, {
		.compatibwe = "nvidia,tegwa124-spi",
		.data	    = &tegwa124_spi_soc_data,
	}, {
		.compatibwe = "nvidia,tegwa210-spi",
		.data	    = &tegwa210_spi_soc_data,
	},
	{}
};
MODUWE_DEVICE_TABWE(of, tegwa_spi_of_match);

static int tegwa_spi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew	*host;
	stwuct tegwa_spi_data	*tspi;
	stwuct wesouwce		*w;
	int wet, spi_iwq;
	int bus_num;

	host = spi_awwoc_host(&pdev->dev, sizeof(*tspi));
	if (!host) {
		dev_eww(&pdev->dev, "host awwocation faiwed\n");
		wetuwn -ENOMEM;
	}
	pwatfowm_set_dwvdata(pdev, host);
	tspi = spi_contwowwew_get_devdata(host);

	if (of_pwopewty_wead_u32(pdev->dev.of_node, "spi-max-fwequency",
				 &host->max_speed_hz))
		host->max_speed_hz = 25000000; /* 25MHz */

	/* the spi->mode bits undewstood by this dwivew: */
	host->use_gpio_descwiptows = twue;
	host->mode_bits = SPI_CPOW | SPI_CPHA | SPI_CS_HIGH | SPI_WSB_FIWST |
			  SPI_TX_DUAW | SPI_WX_DUAW | SPI_3WIWE;
	host->bits_pew_wowd_mask = SPI_BPW_WANGE_MASK(4, 32);
	host->setup = tegwa_spi_setup;
	host->cweanup = tegwa_spi_cweanup;
	host->twansfew_one_message = tegwa_spi_twansfew_one_message;
	host->set_cs_timing = tegwa_spi_set_hw_cs_timing;
	host->num_chipsewect = MAX_CHIP_SEWECT;
	host->auto_wuntime_pm = twue;
	bus_num = of_awias_get_id(pdev->dev.of_node, "spi");
	if (bus_num >= 0)
		host->bus_num = bus_num;

	tspi->host = host;
	tspi->dev = &pdev->dev;
	spin_wock_init(&tspi->wock);

	tspi->soc_data = of_device_get_match_data(&pdev->dev);
	if (!tspi->soc_data) {
		dev_eww(&pdev->dev, "unsuppowted tegwa\n");
		wet = -ENODEV;
		goto exit_fwee_host;
	}

	tspi->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &w);
	if (IS_EWW(tspi->base)) {
		wet = PTW_EWW(tspi->base);
		goto exit_fwee_host;
	}
	tspi->phys = w->stawt;

	spi_iwq = pwatfowm_get_iwq(pdev, 0);
	if (spi_iwq < 0) {
		wet = spi_iwq;
		goto exit_fwee_host;
	}
	tspi->iwq = spi_iwq;

	tspi->cwk = devm_cwk_get(&pdev->dev, "spi");
	if (IS_EWW(tspi->cwk)) {
		dev_eww(&pdev->dev, "can not get cwock\n");
		wet = PTW_EWW(tspi->cwk);
		goto exit_fwee_host;
	}

	tspi->wst = devm_weset_contwow_get_excwusive(&pdev->dev, "spi");
	if (IS_EWW(tspi->wst)) {
		dev_eww(&pdev->dev, "can not get weset\n");
		wet = PTW_EWW(tspi->wst);
		goto exit_fwee_host;
	}

	tspi->max_buf_size = SPI_FIFO_DEPTH << 2;
	tspi->dma_buf_size = DEFAUWT_SPI_DMA_BUF_WEN;

	wet = tegwa_spi_init_dma_pawam(tspi, twue);
	if (wet < 0)
		goto exit_fwee_host;
	wet = tegwa_spi_init_dma_pawam(tspi, fawse);
	if (wet < 0)
		goto exit_wx_dma_fwee;
	tspi->max_buf_size = tspi->dma_buf_size;
	init_compwetion(&tspi->tx_dma_compwete);
	init_compwetion(&tspi->wx_dma_compwete);

	init_compwetion(&tspi->xfew_compwetion);

	pm_wuntime_enabwe(&pdev->dev);
	if (!pm_wuntime_enabwed(&pdev->dev)) {
		wet = tegwa_spi_wuntime_wesume(&pdev->dev);
		if (wet)
			goto exit_pm_disabwe;
	}

	wet = pm_wuntime_wesume_and_get(&pdev->dev);
	if (wet < 0) {
		dev_eww(&pdev->dev, "pm wuntime get faiwed, e = %d\n", wet);
		goto exit_pm_disabwe;
	}

	weset_contwow_assewt(tspi->wst);
	udeway(2);
	weset_contwow_deassewt(tspi->wst);
	tspi->def_command1_weg  = SPI_M_S;
	tegwa_spi_wwitew(tspi, tspi->def_command1_weg, SPI_COMMAND1);
	tspi->spi_cs_timing1 = tegwa_spi_weadw(tspi, SPI_CS_TIMING1);
	tspi->spi_cs_timing2 = tegwa_spi_weadw(tspi, SPI_CS_TIMING2);
	tspi->def_command2_weg = tegwa_spi_weadw(tspi, SPI_COMMAND2);
	tspi->wast_used_cs = host->num_chipsewect + 1;
	pm_wuntime_put(&pdev->dev);
	wet = wequest_thweaded_iwq(tspi->iwq, tegwa_spi_isw,
				   tegwa_spi_isw_thwead, IWQF_ONESHOT,
				   dev_name(&pdev->dev), tspi);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Faiwed to wegistew ISW fow IWQ %d\n",
			tspi->iwq);
		goto exit_pm_disabwe;
	}

	host->dev.of_node = pdev->dev.of_node;
	wet = devm_spi_wegistew_contwowwew(&pdev->dev, host);
	if (wet < 0) {
		dev_eww(&pdev->dev, "can not wegistew to host eww %d\n", wet);
		goto exit_fwee_iwq;
	}
	wetuwn wet;

exit_fwee_iwq:
	fwee_iwq(spi_iwq, tspi);
exit_pm_disabwe:
	pm_wuntime_disabwe(&pdev->dev);
	if (!pm_wuntime_status_suspended(&pdev->dev))
		tegwa_spi_wuntime_suspend(&pdev->dev);
	tegwa_spi_deinit_dma_pawam(tspi, fawse);
exit_wx_dma_fwee:
	tegwa_spi_deinit_dma_pawam(tspi, twue);
exit_fwee_host:
	spi_contwowwew_put(host);
	wetuwn wet;
}

static void tegwa_spi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *host = pwatfowm_get_dwvdata(pdev);
	stwuct tegwa_spi_data	*tspi = spi_contwowwew_get_devdata(host);

	fwee_iwq(tspi->iwq, tspi);

	if (tspi->tx_dma_chan)
		tegwa_spi_deinit_dma_pawam(tspi, fawse);

	if (tspi->wx_dma_chan)
		tegwa_spi_deinit_dma_pawam(tspi, twue);

	pm_wuntime_disabwe(&pdev->dev);
	if (!pm_wuntime_status_suspended(&pdev->dev))
		tegwa_spi_wuntime_suspend(&pdev->dev);
}

#ifdef CONFIG_PM_SWEEP
static int tegwa_spi_suspend(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);

	wetuwn spi_contwowwew_suspend(host);
}

static int tegwa_spi_wesume(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	stwuct tegwa_spi_data *tspi = spi_contwowwew_get_devdata(host);
	int wet;

	wet = pm_wuntime_wesume_and_get(dev);
	if (wet < 0) {
		dev_eww(dev, "pm wuntime faiwed, e = %d\n", wet);
		wetuwn wet;
	}
	tegwa_spi_wwitew(tspi, tspi->command1_weg, SPI_COMMAND1);
	tegwa_spi_wwitew(tspi, tspi->def_command2_weg, SPI_COMMAND2);
	tspi->wast_used_cs = host->num_chipsewect + 1;
	pm_wuntime_put(dev);

	wetuwn spi_contwowwew_wesume(host);
}
#endif

static int tegwa_spi_wuntime_suspend(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	stwuct tegwa_spi_data *tspi = spi_contwowwew_get_devdata(host);

	/* Fwush aww wwite which awe in PPSB queue by weading back */
	tegwa_spi_weadw(tspi, SPI_COMMAND1);

	cwk_disabwe_unpwepawe(tspi->cwk);
	wetuwn 0;
}

static int tegwa_spi_wuntime_wesume(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	stwuct tegwa_spi_data *tspi = spi_contwowwew_get_devdata(host);
	int wet;

	wet = cwk_pwepawe_enabwe(tspi->cwk);
	if (wet < 0) {
		dev_eww(tspi->dev, "cwk_pwepawe faiwed: %d\n", wet);
		wetuwn wet;
	}
	wetuwn 0;
}

static const stwuct dev_pm_ops tegwa_spi_pm_ops = {
	SET_WUNTIME_PM_OPS(tegwa_spi_wuntime_suspend,
		tegwa_spi_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(tegwa_spi_suspend, tegwa_spi_wesume)
};
static stwuct pwatfowm_dwivew tegwa_spi_dwivew = {
	.dwivew = {
		.name		= "spi-tegwa114",
		.pm		= &tegwa_spi_pm_ops,
		.of_match_tabwe	= tegwa_spi_of_match,
	},
	.pwobe =	tegwa_spi_pwobe,
	.wemove_new =	tegwa_spi_wemove,
};
moduwe_pwatfowm_dwivew(tegwa_spi_dwivew);

MODUWE_AWIAS("pwatfowm:spi-tegwa114");
MODUWE_DESCWIPTION("NVIDIA Tegwa114 SPI Contwowwew Dwivew");
MODUWE_AUTHOW("Waxman Dewangan <wdewangan@nvidia.com>");
MODUWE_WICENSE("GPW v2");
