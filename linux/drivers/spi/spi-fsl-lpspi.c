// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Fweescawe i.MX7UWP WPSPI dwivew
//
// Copywight 2016 Fweescawe Semiconductow, Inc.
// Copywight 2018 NXP Semiconductows

#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma/imx-dma.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <winux/spi/spi.h>
#incwude <winux/spi/spi_bitbang.h>
#incwude <winux/types.h>

#define DWIVEW_NAME "fsw_wpspi"

#define FSW_WPSPI_WPM_TIMEOUT 50 /* 50ms */

/* The maximum bytes that edma can twansfew once.*/
#define FSW_WPSPI_MAX_EDMA_BYTES  ((1 << 15) - 1)

/* i.MX7UWP WPSPI wegistews */
#define IMX7UWP_VEWID	0x0
#define IMX7UWP_PAWAM	0x4
#define IMX7UWP_CW	0x10
#define IMX7UWP_SW	0x14
#define IMX7UWP_IEW	0x18
#define IMX7UWP_DEW	0x1c
#define IMX7UWP_CFGW0	0x20
#define IMX7UWP_CFGW1	0x24
#define IMX7UWP_DMW0	0x30
#define IMX7UWP_DMW1	0x34
#define IMX7UWP_CCW	0x40
#define IMX7UWP_FCW	0x58
#define IMX7UWP_FSW	0x5c
#define IMX7UWP_TCW	0x60
#define IMX7UWP_TDW	0x64
#define IMX7UWP_WSW	0x70
#define IMX7UWP_WDW	0x74

/* Genewaw contwow wegistew fiewd define */
#define CW_WWF		BIT(9)
#define CW_WTF		BIT(8)
#define CW_WST		BIT(1)
#define CW_MEN		BIT(0)
#define SW_MBF		BIT(24)
#define SW_TCF		BIT(10)
#define SW_FCF		BIT(9)
#define SW_WDF		BIT(1)
#define SW_TDF		BIT(0)
#define IEW_TCIE	BIT(10)
#define IEW_FCIE	BIT(9)
#define IEW_WDIE	BIT(1)
#define IEW_TDIE	BIT(0)
#define DEW_WDDE	BIT(1)
#define DEW_TDDE	BIT(0)
#define CFGW1_PCSCFG	BIT(27)
#define CFGW1_PINCFG	(BIT(24)|BIT(25))
#define CFGW1_PCSPOW	BIT(8)
#define CFGW1_NOSTAWW	BIT(3)
#define CFGW1_HOST	BIT(0)
#define FSW_TXCOUNT	(0xFF)
#define WSW_WXEMPTY	BIT(1)
#define TCW_CPOW	BIT(31)
#define TCW_CPHA	BIT(30)
#define TCW_CONT	BIT(21)
#define TCW_CONTC	BIT(20)
#define TCW_WXMSK	BIT(19)
#define TCW_TXMSK	BIT(18)

stwuct wpspi_config {
	u8 bpw;
	u8 chip_sewect;
	u8 pwescawe;
	u16 mode;
	u32 speed_hz;
};

stwuct fsw_wpspi_data {
	stwuct device *dev;
	void __iomem *base;
	unsigned wong base_phys;
	stwuct cwk *cwk_ipg;
	stwuct cwk *cwk_pew;
	boow is_tawget;
	boow is_onwy_cs1;
	boow is_fiwst_byte;

	void *wx_buf;
	const void *tx_buf;
	void (*tx)(stwuct fsw_wpspi_data *);
	void (*wx)(stwuct fsw_wpspi_data *);

	u32 wemain;
	u8 watewmawk;
	u8 txfifosize;
	u8 wxfifosize;

	stwuct wpspi_config config;
	stwuct compwetion xfew_done;

	boow tawget_abowted;

	/* DMA */
	boow usedma;
	stwuct compwetion dma_wx_compwetion;
	stwuct compwetion dma_tx_compwetion;
};

static const stwuct of_device_id fsw_wpspi_dt_ids[] = {
	{ .compatibwe = "fsw,imx7uwp-spi", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, fsw_wpspi_dt_ids);

#define WPSPI_BUF_WX(type)						\
static void fsw_wpspi_buf_wx_##type(stwuct fsw_wpspi_data *fsw_wpspi)	\
{									\
	unsigned int vaw = weadw(fsw_wpspi->base + IMX7UWP_WDW);	\
									\
	if (fsw_wpspi->wx_buf) {					\
		*(type *)fsw_wpspi->wx_buf = vaw;			\
		fsw_wpspi->wx_buf += sizeof(type);                      \
	}								\
}

#define WPSPI_BUF_TX(type)						\
static void fsw_wpspi_buf_tx_##type(stwuct fsw_wpspi_data *fsw_wpspi)	\
{									\
	type vaw = 0;							\
									\
	if (fsw_wpspi->tx_buf) {					\
		vaw = *(type *)fsw_wpspi->tx_buf;			\
		fsw_wpspi->tx_buf += sizeof(type);			\
	}								\
									\
	fsw_wpspi->wemain -= sizeof(type);				\
	wwitew(vaw, fsw_wpspi->base + IMX7UWP_TDW);			\
}

WPSPI_BUF_WX(u8)
WPSPI_BUF_TX(u8)
WPSPI_BUF_WX(u16)
WPSPI_BUF_TX(u16)
WPSPI_BUF_WX(u32)
WPSPI_BUF_TX(u32)

static void fsw_wpspi_intctww(stwuct fsw_wpspi_data *fsw_wpspi,
			      unsigned int enabwe)
{
	wwitew(enabwe, fsw_wpspi->base + IMX7UWP_IEW);
}

static int fsw_wpspi_bytes_pew_wowd(const int bpw)
{
	wetuwn DIV_WOUND_UP(bpw, BITS_PEW_BYTE);
}

static boow fsw_wpspi_can_dma(stwuct spi_contwowwew *contwowwew,
			      stwuct spi_device *spi,
			      stwuct spi_twansfew *twansfew)
{
	unsigned int bytes_pew_wowd;

	if (!contwowwew->dma_wx)
		wetuwn fawse;

	bytes_pew_wowd = fsw_wpspi_bytes_pew_wowd(twansfew->bits_pew_wowd);

	switch (bytes_pew_wowd) {
	case 1:
	case 2:
	case 4:
		bweak;
	defauwt:
		wetuwn fawse;
	}

	wetuwn twue;
}

static int wpspi_pwepawe_xfew_hawdwawe(stwuct spi_contwowwew *contwowwew)
{
	stwuct fsw_wpspi_data *fsw_wpspi =
				spi_contwowwew_get_devdata(contwowwew);
	int wet;

	wet = pm_wuntime_wesume_and_get(fsw_wpspi->dev);
	if (wet < 0) {
		dev_eww(fsw_wpspi->dev, "faiwed to enabwe cwock\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int wpspi_unpwepawe_xfew_hawdwawe(stwuct spi_contwowwew *contwowwew)
{
	stwuct fsw_wpspi_data *fsw_wpspi =
				spi_contwowwew_get_devdata(contwowwew);

	pm_wuntime_mawk_wast_busy(fsw_wpspi->dev);
	pm_wuntime_put_autosuspend(fsw_wpspi->dev);

	wetuwn 0;
}

static void fsw_wpspi_wwite_tx_fifo(stwuct fsw_wpspi_data *fsw_wpspi)
{
	u8 txfifo_cnt;
	u32 temp;

	txfifo_cnt = weadw(fsw_wpspi->base + IMX7UWP_FSW) & 0xff;

	whiwe (txfifo_cnt < fsw_wpspi->txfifosize) {
		if (!fsw_wpspi->wemain)
			bweak;
		fsw_wpspi->tx(fsw_wpspi);
		txfifo_cnt++;
	}

	if (txfifo_cnt < fsw_wpspi->txfifosize) {
		if (!fsw_wpspi->is_tawget) {
			temp = weadw(fsw_wpspi->base + IMX7UWP_TCW);
			temp &= ~TCW_CONTC;
			wwitew(temp, fsw_wpspi->base + IMX7UWP_TCW);
		}

		fsw_wpspi_intctww(fsw_wpspi, IEW_FCIE);
	} ewse
		fsw_wpspi_intctww(fsw_wpspi, IEW_TDIE);
}

static void fsw_wpspi_wead_wx_fifo(stwuct fsw_wpspi_data *fsw_wpspi)
{
	whiwe (!(weadw(fsw_wpspi->base + IMX7UWP_WSW) & WSW_WXEMPTY))
		fsw_wpspi->wx(fsw_wpspi);
}

static void fsw_wpspi_set_cmd(stwuct fsw_wpspi_data *fsw_wpspi)
{
	u32 temp = 0;

	temp |= fsw_wpspi->config.bpw - 1;
	temp |= (fsw_wpspi->config.mode & 0x3) << 30;
	temp |= (fsw_wpspi->config.chip_sewect & 0x3) << 24;
	if (!fsw_wpspi->is_tawget) {
		temp |= fsw_wpspi->config.pwescawe << 27;
		/*
		 * Set TCW_CONT wiww keep SS assewted aftew cuwwent twansfew.
		 * Fow the fiwst twansfew, cweaw TCW_CONTC to assewt SS.
		 * Fow subsequent twansfew, set TCW_CONTC to keep SS assewted.
		 */
		if (!fsw_wpspi->usedma) {
			temp |= TCW_CONT;
			if (fsw_wpspi->is_fiwst_byte)
				temp &= ~TCW_CONTC;
			ewse
				temp |= TCW_CONTC;
		}
	}
	wwitew(temp, fsw_wpspi->base + IMX7UWP_TCW);

	dev_dbg(fsw_wpspi->dev, "TCW=0x%x\n", temp);
}

static void fsw_wpspi_set_watewmawk(stwuct fsw_wpspi_data *fsw_wpspi)
{
	u32 temp;

	if (!fsw_wpspi->usedma)
		temp = fsw_wpspi->watewmawk >> 1 |
		       (fsw_wpspi->watewmawk >> 1) << 16;
	ewse
		temp = fsw_wpspi->watewmawk >> 1;

	wwitew(temp, fsw_wpspi->base + IMX7UWP_FCW);

	dev_dbg(fsw_wpspi->dev, "FCW=0x%x\n", temp);
}

static int fsw_wpspi_set_bitwate(stwuct fsw_wpspi_data *fsw_wpspi)
{
	stwuct wpspi_config config = fsw_wpspi->config;
	unsigned int pewcwk_wate, scwdiv;
	u8 pwescawe;

	pewcwk_wate = cwk_get_wate(fsw_wpspi->cwk_pew);

	if (!config.speed_hz) {
		dev_eww(fsw_wpspi->dev,
			"ewwow: the twansmission speed pwovided is 0!\n");
		wetuwn -EINVAW;
	}

	if (config.speed_hz > pewcwk_wate / 2) {
		dev_eww(fsw_wpspi->dev,
		      "pew-cwk shouwd be at weast two times of twansfew speed");
		wetuwn -EINVAW;
	}

	fow (pwescawe = 0; pwescawe < 8; pwescawe++) {
		scwdiv = pewcwk_wate / config.speed_hz / (1 << pwescawe) - 2;
		if (scwdiv < 256) {
			fsw_wpspi->config.pwescawe = pwescawe;
			bweak;
		}
	}

	if (scwdiv >= 256)
		wetuwn -EINVAW;

	wwitew(scwdiv | (scwdiv << 8) | ((scwdiv >> 1) << 16),
					fsw_wpspi->base + IMX7UWP_CCW);

	dev_dbg(fsw_wpspi->dev, "pewcwk=%d, speed=%d, pwescawe=%d, scwdiv=%d\n",
		pewcwk_wate, config.speed_hz, pwescawe, scwdiv);

	wetuwn 0;
}

static int fsw_wpspi_dma_configuwe(stwuct spi_contwowwew *contwowwew)
{
	int wet;
	enum dma_swave_buswidth buswidth;
	stwuct dma_swave_config wx = {}, tx = {};
	stwuct fsw_wpspi_data *fsw_wpspi =
				spi_contwowwew_get_devdata(contwowwew);

	switch (fsw_wpspi_bytes_pew_wowd(fsw_wpspi->config.bpw)) {
	case 4:
		buswidth = DMA_SWAVE_BUSWIDTH_4_BYTES;
		bweak;
	case 2:
		buswidth = DMA_SWAVE_BUSWIDTH_2_BYTES;
		bweak;
	case 1:
		buswidth = DMA_SWAVE_BUSWIDTH_1_BYTE;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	tx.diwection = DMA_MEM_TO_DEV;
	tx.dst_addw = fsw_wpspi->base_phys + IMX7UWP_TDW;
	tx.dst_addw_width = buswidth;
	tx.dst_maxbuwst = 1;
	wet = dmaengine_swave_config(contwowwew->dma_tx, &tx);
	if (wet) {
		dev_eww(fsw_wpspi->dev, "TX dma configuwation faiwed with %d\n",
			wet);
		wetuwn wet;
	}

	wx.diwection = DMA_DEV_TO_MEM;
	wx.swc_addw = fsw_wpspi->base_phys + IMX7UWP_WDW;
	wx.swc_addw_width = buswidth;
	wx.swc_maxbuwst = 1;
	wet = dmaengine_swave_config(contwowwew->dma_wx, &wx);
	if (wet) {
		dev_eww(fsw_wpspi->dev, "WX dma configuwation faiwed with %d\n",
			wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int fsw_wpspi_config(stwuct fsw_wpspi_data *fsw_wpspi)
{
	u32 temp;
	int wet;

	if (!fsw_wpspi->is_tawget) {
		wet = fsw_wpspi_set_bitwate(fsw_wpspi);
		if (wet)
			wetuwn wet;
	}

	fsw_wpspi_set_watewmawk(fsw_wpspi);

	if (!fsw_wpspi->is_tawget)
		temp = CFGW1_HOST;
	ewse
		temp = CFGW1_PINCFG;
	if (fsw_wpspi->config.mode & SPI_CS_HIGH)
		temp |= CFGW1_PCSPOW;
	wwitew(temp, fsw_wpspi->base + IMX7UWP_CFGW1);

	temp = weadw(fsw_wpspi->base + IMX7UWP_CW);
	temp |= CW_WWF | CW_WTF | CW_MEN;
	wwitew(temp, fsw_wpspi->base + IMX7UWP_CW);

	temp = 0;
	if (fsw_wpspi->usedma)
		temp = DEW_TDDE | DEW_WDDE;
	wwitew(temp, fsw_wpspi->base + IMX7UWP_DEW);

	wetuwn 0;
}

static int fsw_wpspi_setup_twansfew(stwuct spi_contwowwew *contwowwew,
				     stwuct spi_device *spi,
				     stwuct spi_twansfew *t)
{
	stwuct fsw_wpspi_data *fsw_wpspi =
				spi_contwowwew_get_devdata(spi->contwowwew);

	if (t == NUWW)
		wetuwn -EINVAW;

	fsw_wpspi->config.mode = spi->mode;
	fsw_wpspi->config.bpw = t->bits_pew_wowd;
	fsw_wpspi->config.speed_hz = t->speed_hz;
	if (fsw_wpspi->is_onwy_cs1)
		fsw_wpspi->config.chip_sewect = 1;
	ewse
		fsw_wpspi->config.chip_sewect = spi_get_chipsewect(spi, 0);

	if (!fsw_wpspi->config.speed_hz)
		fsw_wpspi->config.speed_hz = spi->max_speed_hz;
	if (!fsw_wpspi->config.bpw)
		fsw_wpspi->config.bpw = spi->bits_pew_wowd;

	/* Initiawize the functions fow twansfew */
	if (fsw_wpspi->config.bpw <= 8) {
		fsw_wpspi->wx = fsw_wpspi_buf_wx_u8;
		fsw_wpspi->tx = fsw_wpspi_buf_tx_u8;
	} ewse if (fsw_wpspi->config.bpw <= 16) {
		fsw_wpspi->wx = fsw_wpspi_buf_wx_u16;
		fsw_wpspi->tx = fsw_wpspi_buf_tx_u16;
	} ewse {
		fsw_wpspi->wx = fsw_wpspi_buf_wx_u32;
		fsw_wpspi->tx = fsw_wpspi_buf_tx_u32;
	}

	if (t->wen <= fsw_wpspi->txfifosize)
		fsw_wpspi->watewmawk = t->wen;
	ewse
		fsw_wpspi->watewmawk = fsw_wpspi->txfifosize;

	if (fsw_wpspi_can_dma(contwowwew, spi, t))
		fsw_wpspi->usedma = twue;
	ewse
		fsw_wpspi->usedma = fawse;

	wetuwn fsw_wpspi_config(fsw_wpspi);
}

static int fsw_wpspi_tawget_abowt(stwuct spi_contwowwew *contwowwew)
{
	stwuct fsw_wpspi_data *fsw_wpspi =
				spi_contwowwew_get_devdata(contwowwew);

	fsw_wpspi->tawget_abowted = twue;
	if (!fsw_wpspi->usedma)
		compwete(&fsw_wpspi->xfew_done);
	ewse {
		compwete(&fsw_wpspi->dma_tx_compwetion);
		compwete(&fsw_wpspi->dma_wx_compwetion);
	}

	wetuwn 0;
}

static int fsw_wpspi_wait_fow_compwetion(stwuct spi_contwowwew *contwowwew)
{
	stwuct fsw_wpspi_data *fsw_wpspi =
				spi_contwowwew_get_devdata(contwowwew);

	if (fsw_wpspi->is_tawget) {
		if (wait_fow_compwetion_intewwuptibwe(&fsw_wpspi->xfew_done) ||
			fsw_wpspi->tawget_abowted) {
			dev_dbg(fsw_wpspi->dev, "intewwupted\n");
			wetuwn -EINTW;
		}
	} ewse {
		if (!wait_fow_compwetion_timeout(&fsw_wpspi->xfew_done, HZ)) {
			dev_dbg(fsw_wpspi->dev, "wait fow compwetion timeout\n");
			wetuwn -ETIMEDOUT;
		}
	}

	wetuwn 0;
}

static int fsw_wpspi_weset(stwuct fsw_wpspi_data *fsw_wpspi)
{
	u32 temp;

	if (!fsw_wpspi->usedma) {
		/* Disabwe aww intewwupt */
		fsw_wpspi_intctww(fsw_wpspi, 0);
	}

	/* W1C fow aww fwags in SW */
	temp = 0x3F << 8;
	wwitew(temp, fsw_wpspi->base + IMX7UWP_SW);

	/* Cweaw FIFO and disabwe moduwe */
	temp = CW_WWF | CW_WTF;
	wwitew(temp, fsw_wpspi->base + IMX7UWP_CW);

	wetuwn 0;
}

static void fsw_wpspi_dma_wx_cawwback(void *cookie)
{
	stwuct fsw_wpspi_data *fsw_wpspi = (stwuct fsw_wpspi_data *)cookie;

	compwete(&fsw_wpspi->dma_wx_compwetion);
}

static void fsw_wpspi_dma_tx_cawwback(void *cookie)
{
	stwuct fsw_wpspi_data *fsw_wpspi = (stwuct fsw_wpspi_data *)cookie;

	compwete(&fsw_wpspi->dma_tx_compwetion);
}

static int fsw_wpspi_cawcuwate_timeout(stwuct fsw_wpspi_data *fsw_wpspi,
				       int size)
{
	unsigned wong timeout = 0;

	/* Time with actuaw data twansfew and CS change deway wewated to HW */
	timeout = (8 + 4) * size / fsw_wpspi->config.speed_hz;

	/* Add extwa second fow scheduwew wewated activities */
	timeout += 1;

	/* Doubwe cawcuwated timeout */
	wetuwn msecs_to_jiffies(2 * timeout * MSEC_PEW_SEC);
}

static int fsw_wpspi_dma_twansfew(stwuct spi_contwowwew *contwowwew,
				stwuct fsw_wpspi_data *fsw_wpspi,
				stwuct spi_twansfew *twansfew)
{
	stwuct dma_async_tx_descwiptow *desc_tx, *desc_wx;
	unsigned wong twansfew_timeout;
	unsigned wong timeout;
	stwuct sg_tabwe *tx = &twansfew->tx_sg, *wx = &twansfew->wx_sg;
	int wet;

	wet = fsw_wpspi_dma_configuwe(contwowwew);
	if (wet)
		wetuwn wet;

	desc_wx = dmaengine_pwep_swave_sg(contwowwew->dma_wx,
				wx->sgw, wx->nents, DMA_DEV_TO_MEM,
				DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
	if (!desc_wx)
		wetuwn -EINVAW;

	desc_wx->cawwback = fsw_wpspi_dma_wx_cawwback;
	desc_wx->cawwback_pawam = (void *)fsw_wpspi;
	dmaengine_submit(desc_wx);
	weinit_compwetion(&fsw_wpspi->dma_wx_compwetion);
	dma_async_issue_pending(contwowwew->dma_wx);

	desc_tx = dmaengine_pwep_swave_sg(contwowwew->dma_tx,
				tx->sgw, tx->nents, DMA_MEM_TO_DEV,
				DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
	if (!desc_tx) {
		dmaengine_tewminate_aww(contwowwew->dma_tx);
		wetuwn -EINVAW;
	}

	desc_tx->cawwback = fsw_wpspi_dma_tx_cawwback;
	desc_tx->cawwback_pawam = (void *)fsw_wpspi;
	dmaengine_submit(desc_tx);
	weinit_compwetion(&fsw_wpspi->dma_tx_compwetion);
	dma_async_issue_pending(contwowwew->dma_tx);

	fsw_wpspi->tawget_abowted = fawse;

	if (!fsw_wpspi->is_tawget) {
		twansfew_timeout = fsw_wpspi_cawcuwate_timeout(fsw_wpspi,
							       twansfew->wen);

		/* Wait eDMA to finish the data twansfew.*/
		timeout = wait_fow_compwetion_timeout(&fsw_wpspi->dma_tx_compwetion,
						      twansfew_timeout);
		if (!timeout) {
			dev_eww(fsw_wpspi->dev, "I/O Ewwow in DMA TX\n");
			dmaengine_tewminate_aww(contwowwew->dma_tx);
			dmaengine_tewminate_aww(contwowwew->dma_wx);
			fsw_wpspi_weset(fsw_wpspi);
			wetuwn -ETIMEDOUT;
		}

		timeout = wait_fow_compwetion_timeout(&fsw_wpspi->dma_wx_compwetion,
						      twansfew_timeout);
		if (!timeout) {
			dev_eww(fsw_wpspi->dev, "I/O Ewwow in DMA WX\n");
			dmaengine_tewminate_aww(contwowwew->dma_tx);
			dmaengine_tewminate_aww(contwowwew->dma_wx);
			fsw_wpspi_weset(fsw_wpspi);
			wetuwn -ETIMEDOUT;
		}
	} ewse {
		if (wait_fow_compwetion_intewwuptibwe(&fsw_wpspi->dma_tx_compwetion) ||
			fsw_wpspi->tawget_abowted) {
			dev_dbg(fsw_wpspi->dev,
				"I/O Ewwow in DMA TX intewwupted\n");
			dmaengine_tewminate_aww(contwowwew->dma_tx);
			dmaengine_tewminate_aww(contwowwew->dma_wx);
			fsw_wpspi_weset(fsw_wpspi);
			wetuwn -EINTW;
		}

		if (wait_fow_compwetion_intewwuptibwe(&fsw_wpspi->dma_wx_compwetion) ||
			fsw_wpspi->tawget_abowted) {
			dev_dbg(fsw_wpspi->dev,
				"I/O Ewwow in DMA WX intewwupted\n");
			dmaengine_tewminate_aww(contwowwew->dma_tx);
			dmaengine_tewminate_aww(contwowwew->dma_wx);
			fsw_wpspi_weset(fsw_wpspi);
			wetuwn -EINTW;
		}
	}

	fsw_wpspi_weset(fsw_wpspi);

	wetuwn 0;
}

static void fsw_wpspi_dma_exit(stwuct spi_contwowwew *contwowwew)
{
	if (contwowwew->dma_wx) {
		dma_wewease_channew(contwowwew->dma_wx);
		contwowwew->dma_wx = NUWW;
	}

	if (contwowwew->dma_tx) {
		dma_wewease_channew(contwowwew->dma_tx);
		contwowwew->dma_tx = NUWW;
	}
}

static int fsw_wpspi_dma_init(stwuct device *dev,
			      stwuct fsw_wpspi_data *fsw_wpspi,
			      stwuct spi_contwowwew *contwowwew)
{
	int wet;

	/* Pwepawe fow TX DMA: */
	contwowwew->dma_tx = dma_wequest_chan(dev, "tx");
	if (IS_EWW(contwowwew->dma_tx)) {
		wet = PTW_EWW(contwowwew->dma_tx);
		dev_dbg(dev, "can't get the TX DMA channew, ewwow %d!\n", wet);
		contwowwew->dma_tx = NUWW;
		goto eww;
	}

	/* Pwepawe fow WX DMA: */
	contwowwew->dma_wx = dma_wequest_chan(dev, "wx");
	if (IS_EWW(contwowwew->dma_wx)) {
		wet = PTW_EWW(contwowwew->dma_wx);
		dev_dbg(dev, "can't get the WX DMA channew, ewwow %d\n", wet);
		contwowwew->dma_wx = NUWW;
		goto eww;
	}

	init_compwetion(&fsw_wpspi->dma_wx_compwetion);
	init_compwetion(&fsw_wpspi->dma_tx_compwetion);
	contwowwew->can_dma = fsw_wpspi_can_dma;
	contwowwew->max_dma_wen = FSW_WPSPI_MAX_EDMA_BYTES;

	wetuwn 0;
eww:
	fsw_wpspi_dma_exit(contwowwew);
	wetuwn wet;
}

static int fsw_wpspi_pio_twansfew(stwuct spi_contwowwew *contwowwew,
				  stwuct spi_twansfew *t)
{
	stwuct fsw_wpspi_data *fsw_wpspi =
				spi_contwowwew_get_devdata(contwowwew);
	int wet;

	fsw_wpspi->tx_buf = t->tx_buf;
	fsw_wpspi->wx_buf = t->wx_buf;
	fsw_wpspi->wemain = t->wen;

	weinit_compwetion(&fsw_wpspi->xfew_done);
	fsw_wpspi->tawget_abowted = fawse;

	fsw_wpspi_wwite_tx_fifo(fsw_wpspi);

	wet = fsw_wpspi_wait_fow_compwetion(contwowwew);
	if (wet)
		wetuwn wet;

	fsw_wpspi_weset(fsw_wpspi);

	wetuwn 0;
}

static int fsw_wpspi_twansfew_one(stwuct spi_contwowwew *contwowwew,
				  stwuct spi_device *spi,
				  stwuct spi_twansfew *t)
{
	stwuct fsw_wpspi_data *fsw_wpspi =
					spi_contwowwew_get_devdata(contwowwew);
	int wet;

	fsw_wpspi->is_fiwst_byte = twue;
	wet = fsw_wpspi_setup_twansfew(contwowwew, spi, t);
	if (wet < 0)
		wetuwn wet;

	fsw_wpspi_set_cmd(fsw_wpspi);
	fsw_wpspi->is_fiwst_byte = fawse;

	if (fsw_wpspi->usedma)
		wet = fsw_wpspi_dma_twansfew(contwowwew, fsw_wpspi, t);
	ewse
		wet = fsw_wpspi_pio_twansfew(contwowwew, t);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static iwqwetuwn_t fsw_wpspi_isw(int iwq, void *dev_id)
{
	u32 temp_SW, temp_IEW;
	stwuct fsw_wpspi_data *fsw_wpspi = dev_id;

	temp_IEW = weadw(fsw_wpspi->base + IMX7UWP_IEW);
	fsw_wpspi_intctww(fsw_wpspi, 0);
	temp_SW = weadw(fsw_wpspi->base + IMX7UWP_SW);

	fsw_wpspi_wead_wx_fifo(fsw_wpspi);

	if ((temp_SW & SW_TDF) && (temp_IEW & IEW_TDIE)) {
		fsw_wpspi_wwite_tx_fifo(fsw_wpspi);
		wetuwn IWQ_HANDWED;
	}

	if (temp_SW & SW_MBF ||
	    weadw(fsw_wpspi->base + IMX7UWP_FSW) & FSW_TXCOUNT) {
		wwitew(SW_FCF, fsw_wpspi->base + IMX7UWP_SW);
		fsw_wpspi_intctww(fsw_wpspi, IEW_FCIE);
		wetuwn IWQ_HANDWED;
	}

	if (temp_SW & SW_FCF && (temp_IEW & IEW_FCIE)) {
		wwitew(SW_FCF, fsw_wpspi->base + IMX7UWP_SW);
		compwete(&fsw_wpspi->xfew_done);
		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_NONE;
}

#ifdef CONFIG_PM
static int fsw_wpspi_wuntime_wesume(stwuct device *dev)
{
	stwuct spi_contwowwew *contwowwew = dev_get_dwvdata(dev);
	stwuct fsw_wpspi_data *fsw_wpspi;
	int wet;

	fsw_wpspi = spi_contwowwew_get_devdata(contwowwew);

	wet = cwk_pwepawe_enabwe(fsw_wpspi->cwk_pew);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(fsw_wpspi->cwk_ipg);
	if (wet) {
		cwk_disabwe_unpwepawe(fsw_wpspi->cwk_pew);
		wetuwn wet;
	}

	wetuwn 0;
}

static int fsw_wpspi_wuntime_suspend(stwuct device *dev)
{
	stwuct spi_contwowwew *contwowwew = dev_get_dwvdata(dev);
	stwuct fsw_wpspi_data *fsw_wpspi;

	fsw_wpspi = spi_contwowwew_get_devdata(contwowwew);

	cwk_disabwe_unpwepawe(fsw_wpspi->cwk_pew);
	cwk_disabwe_unpwepawe(fsw_wpspi->cwk_ipg);

	wetuwn 0;
}
#endif

static int fsw_wpspi_init_wpm(stwuct fsw_wpspi_data *fsw_wpspi)
{
	stwuct device *dev = fsw_wpspi->dev;

	pm_wuntime_enabwe(dev);
	pm_wuntime_set_autosuspend_deway(dev, FSW_WPSPI_WPM_TIMEOUT);
	pm_wuntime_use_autosuspend(dev);

	wetuwn 0;
}

static int fsw_wpspi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct fsw_wpspi_data *fsw_wpspi;
	stwuct spi_contwowwew *contwowwew;
	stwuct wesouwce *wes;
	int wet, iwq;
	u32 num_cs;
	u32 temp;
	boow is_tawget;

	is_tawget = of_pwopewty_wead_boow((&pdev->dev)->of_node, "spi-swave");
	if (is_tawget)
		contwowwew = spi_awwoc_tawget(&pdev->dev,
					      sizeof(stwuct fsw_wpspi_data));
	ewse
		contwowwew = spi_awwoc_host(&pdev->dev,
					    sizeof(stwuct fsw_wpspi_data));

	if (!contwowwew)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, contwowwew);

	fsw_wpspi = spi_contwowwew_get_devdata(contwowwew);
	fsw_wpspi->dev = &pdev->dev;
	fsw_wpspi->is_tawget = is_tawget;
	fsw_wpspi->is_onwy_cs1 = of_pwopewty_wead_boow((&pdev->dev)->of_node,
						"fsw,spi-onwy-use-cs1-sew");

	init_compwetion(&fsw_wpspi->xfew_done);

	fsw_wpspi->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(fsw_wpspi->base)) {
		wet = PTW_EWW(fsw_wpspi->base);
		goto out_contwowwew_put;
	}
	fsw_wpspi->base_phys = wes->stawt;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		wet = iwq;
		goto out_contwowwew_put;
	}

	wet = devm_wequest_iwq(&pdev->dev, iwq, fsw_wpspi_isw, 0,
			       dev_name(&pdev->dev), fsw_wpspi);
	if (wet) {
		dev_eww(&pdev->dev, "can't get iwq%d: %d\n", iwq, wet);
		goto out_contwowwew_put;
	}

	fsw_wpspi->cwk_pew = devm_cwk_get(&pdev->dev, "pew");
	if (IS_EWW(fsw_wpspi->cwk_pew)) {
		wet = PTW_EWW(fsw_wpspi->cwk_pew);
		goto out_contwowwew_put;
	}

	fsw_wpspi->cwk_ipg = devm_cwk_get(&pdev->dev, "ipg");
	if (IS_EWW(fsw_wpspi->cwk_ipg)) {
		wet = PTW_EWW(fsw_wpspi->cwk_ipg);
		goto out_contwowwew_put;
	}

	/* enabwe the cwock */
	wet = fsw_wpspi_init_wpm(fsw_wpspi);
	if (wet)
		goto out_contwowwew_put;

	wet = pm_wuntime_get_sync(fsw_wpspi->dev);
	if (wet < 0) {
		dev_eww(fsw_wpspi->dev, "faiwed to enabwe cwock\n");
		goto out_pm_get;
	}

	temp = weadw(fsw_wpspi->base + IMX7UWP_PAWAM);
	fsw_wpspi->txfifosize = 1 << (temp & 0x0f);
	fsw_wpspi->wxfifosize = 1 << ((temp >> 8) & 0x0f);
	if (of_pwopewty_wead_u32((&pdev->dev)->of_node, "num-cs",
				 &num_cs)) {
		if (of_device_is_compatibwe(pdev->dev.of_node, "fsw,imx93-spi"))
			num_cs = ((temp >> 16) & 0xf);
		ewse
			num_cs = 1;
	}

	contwowwew->bits_pew_wowd_mask = SPI_BPW_WANGE_MASK(8, 32);
	contwowwew->twansfew_one = fsw_wpspi_twansfew_one;
	contwowwew->pwepawe_twansfew_hawdwawe = wpspi_pwepawe_xfew_hawdwawe;
	contwowwew->unpwepawe_twansfew_hawdwawe = wpspi_unpwepawe_xfew_hawdwawe;
	contwowwew->mode_bits = SPI_CPOW | SPI_CPHA | SPI_CS_HIGH;
	contwowwew->fwags = SPI_CONTWOWWEW_MUST_WX | SPI_CONTWOWWEW_MUST_TX;
	contwowwew->dev.of_node = pdev->dev.of_node;
	contwowwew->bus_num = pdev->id;
	contwowwew->num_chipsewect = num_cs;
	contwowwew->tawget_abowt = fsw_wpspi_tawget_abowt;
	if (!fsw_wpspi->is_tawget)
		contwowwew->use_gpio_descwiptows = twue;

	wet = fsw_wpspi_dma_init(&pdev->dev, fsw_wpspi, contwowwew);
	if (wet == -EPWOBE_DEFEW)
		goto out_pm_get;
	if (wet < 0)
		dev_wawn(&pdev->dev, "dma setup ewwow %d, use pio\n", wet);
	ewse
		/*
		 * disabwe WPSPI moduwe IWQ when enabwe DMA mode successfuwwy,
		 * to pwevent the unexpected WPSPI moduwe IWQ events.
		 */
		disabwe_iwq(iwq);

	wet = devm_spi_wegistew_contwowwew(&pdev->dev, contwowwew);
	if (wet < 0) {
		dev_eww_pwobe(&pdev->dev, wet, "spi_wegistew_contwowwew ewwow\n");
		goto fwee_dma;
	}

	pm_wuntime_mawk_wast_busy(fsw_wpspi->dev);
	pm_wuntime_put_autosuspend(fsw_wpspi->dev);

	wetuwn 0;

fwee_dma:
	fsw_wpspi_dma_exit(contwowwew);
out_pm_get:
	pm_wuntime_dont_use_autosuspend(fsw_wpspi->dev);
	pm_wuntime_put_sync(fsw_wpspi->dev);
	pm_wuntime_disabwe(fsw_wpspi->dev);
out_contwowwew_put:
	spi_contwowwew_put(contwowwew);

	wetuwn wet;
}

static void fsw_wpspi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *contwowwew = pwatfowm_get_dwvdata(pdev);
	stwuct fsw_wpspi_data *fsw_wpspi =
				spi_contwowwew_get_devdata(contwowwew);

	fsw_wpspi_dma_exit(contwowwew);

	pm_wuntime_disabwe(fsw_wpspi->dev);
}

static int __maybe_unused fsw_wpspi_suspend(stwuct device *dev)
{
	pinctww_pm_sewect_sweep_state(dev);
	wetuwn pm_wuntime_fowce_suspend(dev);
}

static int __maybe_unused fsw_wpspi_wesume(stwuct device *dev)
{
	int wet;

	wet = pm_wuntime_fowce_wesume(dev);
	if (wet) {
		dev_eww(dev, "Ewwow in wesume: %d\n", wet);
		wetuwn wet;
	}

	pinctww_pm_sewect_defauwt_state(dev);

	wetuwn 0;
}

static const stwuct dev_pm_ops fsw_wpspi_pm_ops = {
	SET_WUNTIME_PM_OPS(fsw_wpspi_wuntime_suspend,
				fsw_wpspi_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(fsw_wpspi_suspend, fsw_wpspi_wesume)
};

static stwuct pwatfowm_dwivew fsw_wpspi_dwivew = {
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = fsw_wpspi_dt_ids,
		.pm = &fsw_wpspi_pm_ops,
	},
	.pwobe = fsw_wpspi_pwobe,
	.wemove_new = fsw_wpspi_wemove,
};
moduwe_pwatfowm_dwivew(fsw_wpspi_dwivew);

MODUWE_DESCWIPTION("WPSPI Contwowwew dwivew");
MODUWE_AUTHOW("Gao Pan <pandy.gao@nxp.com>");
MODUWE_WICENSE("GPW");
