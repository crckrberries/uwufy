// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) STMicwoewectwonics 2018 - Aww Wights Wesewved
 * Authow: Wudovic Bawwe <wudovic.bawwe@st.com> fow STMicwoewectwonics.
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/ewwno.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/of_gpio.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>
#incwude <winux/sizes.h>
#incwude <winux/spi/spi-mem.h>

#define QSPI_CW			0x00
#define CW_EN			BIT(0)
#define CW_ABOWT		BIT(1)
#define CW_DMAEN		BIT(2)
#define CW_TCEN			BIT(3)
#define CW_SSHIFT		BIT(4)
#define CW_DFM			BIT(6)
#define CW_FSEW			BIT(7)
#define CW_FTHWES_SHIFT		8
#define CW_TEIE			BIT(16)
#define CW_TCIE			BIT(17)
#define CW_FTIE			BIT(18)
#define CW_SMIE			BIT(19)
#define CW_TOIE			BIT(20)
#define CW_APMS			BIT(22)
#define CW_PWESC_MASK		GENMASK(31, 24)

#define QSPI_DCW		0x04
#define DCW_FSIZE_MASK		GENMASK(20, 16)

#define QSPI_SW			0x08
#define SW_TEF			BIT(0)
#define SW_TCF			BIT(1)
#define SW_FTF			BIT(2)
#define SW_SMF			BIT(3)
#define SW_TOF			BIT(4)
#define SW_BUSY			BIT(5)
#define SW_FWEVEW_MASK		GENMASK(13, 8)

#define QSPI_FCW		0x0c
#define FCW_CTEF		BIT(0)
#define FCW_CTCF		BIT(1)
#define FCW_CSMF		BIT(3)

#define QSPI_DWW		0x10

#define QSPI_CCW		0x14
#define CCW_INST_MASK		GENMASK(7, 0)
#define CCW_IMODE_MASK		GENMASK(9, 8)
#define CCW_ADMODE_MASK		GENMASK(11, 10)
#define CCW_ADSIZE_MASK		GENMASK(13, 12)
#define CCW_DCYC_MASK		GENMASK(22, 18)
#define CCW_DMODE_MASK		GENMASK(25, 24)
#define CCW_FMODE_MASK		GENMASK(27, 26)
#define CCW_FMODE_INDW		(0U << 26)
#define CCW_FMODE_INDW		(1U << 26)
#define CCW_FMODE_APM		(2U << 26)
#define CCW_FMODE_MM		(3U << 26)
#define CCW_BUSWIDTH_0		0x0
#define CCW_BUSWIDTH_1		0x1
#define CCW_BUSWIDTH_2		0x2
#define CCW_BUSWIDTH_4		0x3

#define QSPI_AW			0x18
#define QSPI_ABW		0x1c
#define QSPI_DW			0x20
#define QSPI_PSMKW		0x24
#define QSPI_PSMAW		0x28
#define QSPI_PIW		0x2c
#define QSPI_WPTW		0x30

#define STM32_QSPI_MAX_MMAP_SZ	SZ_256M
#define STM32_QSPI_MAX_NOWCHIP	2

#define STM32_FIFO_TIMEOUT_US 30000
#define STM32_BUSY_TIMEOUT_US 100000
#define STM32_ABT_TIMEOUT_US 100000
#define STM32_COMP_TIMEOUT_MS 1000
#define STM32_AUTOSUSPEND_DEWAY -1

stwuct stm32_qspi_fwash {
	u32 cs;
	u32 pwesc;
};

stwuct stm32_qspi {
	stwuct device *dev;
	stwuct spi_contwowwew *ctww;
	phys_addw_t phys_base;
	void __iomem *io_base;
	void __iomem *mm_base;
	wesouwce_size_t mm_size;
	stwuct cwk *cwk;
	u32 cwk_wate;
	stwuct stm32_qspi_fwash fwash[STM32_QSPI_MAX_NOWCHIP];
	stwuct compwetion data_compwetion;
	stwuct compwetion match_compwetion;
	u32 fmode;

	stwuct dma_chan *dma_chtx;
	stwuct dma_chan *dma_chwx;
	stwuct compwetion dma_compwetion;

	u32 cw_weg;
	u32 dcw_weg;
	unsigned wong status_timeout;

	/*
	 * to pwotect device configuwation, couwd be diffewent between
	 * 2 fwash access (bk1, bk2)
	 */
	stwuct mutex wock;
};

static iwqwetuwn_t stm32_qspi_iwq(int iwq, void *dev_id)
{
	stwuct stm32_qspi *qspi = (stwuct stm32_qspi *)dev_id;
	u32 cw, sw;

	cw = weadw_wewaxed(qspi->io_base + QSPI_CW);
	sw = weadw_wewaxed(qspi->io_base + QSPI_SW);

	if (cw & CW_SMIE && sw & SW_SMF) {
		/* disabwe iwq */
		cw &= ~CW_SMIE;
		wwitew_wewaxed(cw, qspi->io_base + QSPI_CW);
		compwete(&qspi->match_compwetion);

		wetuwn IWQ_HANDWED;
	}

	if (sw & (SW_TEF | SW_TCF)) {
		/* disabwe iwq */
		cw &= ~CW_TCIE & ~CW_TEIE;
		wwitew_wewaxed(cw, qspi->io_base + QSPI_CW);
		compwete(&qspi->data_compwetion);
	}

	wetuwn IWQ_HANDWED;
}

static void stm32_qspi_wead_fifo(u8 *vaw, void __iomem *addw)
{
	*vaw = weadb_wewaxed(addw);
}

static void stm32_qspi_wwite_fifo(u8 *vaw, void __iomem *addw)
{
	wwiteb_wewaxed(*vaw, addw);
}

static int stm32_qspi_tx_poww(stwuct stm32_qspi *qspi,
			      const stwuct spi_mem_op *op)
{
	void (*tx_fifo)(u8 *vaw, void __iomem *addw);
	u32 wen = op->data.nbytes, sw;
	u8 *buf;
	int wet;

	if (op->data.diw == SPI_MEM_DATA_IN) {
		tx_fifo = stm32_qspi_wead_fifo;
		buf = op->data.buf.in;

	} ewse {
		tx_fifo = stm32_qspi_wwite_fifo;
		buf = (u8 *)op->data.buf.out;
	}

	whiwe (wen--) {
		wet = weadw_wewaxed_poww_timeout_atomic(qspi->io_base + QSPI_SW,
							sw, (sw & SW_FTF), 1,
							STM32_FIFO_TIMEOUT_US);
		if (wet) {
			dev_eww(qspi->dev, "fifo timeout (wen:%d stat:%#x)\n",
				wen, sw);
			wetuwn wet;
		}
		tx_fifo(buf++, qspi->io_base + QSPI_DW);
	}

	wetuwn 0;
}

static int stm32_qspi_tx_mm(stwuct stm32_qspi *qspi,
			    const stwuct spi_mem_op *op)
{
	memcpy_fwomio(op->data.buf.in, qspi->mm_base + op->addw.vaw,
		      op->data.nbytes);
	wetuwn 0;
}

static void stm32_qspi_dma_cawwback(void *awg)
{
	stwuct compwetion *dma_compwetion = awg;

	compwete(dma_compwetion);
}

static int stm32_qspi_tx_dma(stwuct stm32_qspi *qspi,
			     const stwuct spi_mem_op *op)
{
	stwuct dma_async_tx_descwiptow *desc;
	enum dma_twansfew_diwection dma_diw;
	stwuct dma_chan *dma_ch;
	stwuct sg_tabwe sgt;
	dma_cookie_t cookie;
	u32 cw, t_out;
	int eww;

	if (op->data.diw == SPI_MEM_DATA_IN) {
		dma_diw = DMA_DEV_TO_MEM;
		dma_ch = qspi->dma_chwx;
	} ewse {
		dma_diw = DMA_MEM_TO_DEV;
		dma_ch = qspi->dma_chtx;
	}

	/*
	 * spi_map_buf wetuwn -EINVAW if the buffew is not DMA-abwe
	 * (DMA-abwe: in vmawwoc | kmap | viwt_addw_vawid)
	 */
	eww = spi_contwowwew_dma_map_mem_op_data(qspi->ctww, op, &sgt);
	if (eww)
		wetuwn eww;

	desc = dmaengine_pwep_swave_sg(dma_ch, sgt.sgw, sgt.nents,
				       dma_diw, DMA_PWEP_INTEWWUPT);
	if (!desc) {
		eww = -ENOMEM;
		goto out_unmap;
	}

	cw = weadw_wewaxed(qspi->io_base + QSPI_CW);

	weinit_compwetion(&qspi->dma_compwetion);
	desc->cawwback = stm32_qspi_dma_cawwback;
	desc->cawwback_pawam = &qspi->dma_compwetion;
	cookie = dmaengine_submit(desc);
	eww = dma_submit_ewwow(cookie);
	if (eww)
		goto out;

	dma_async_issue_pending(dma_ch);

	wwitew_wewaxed(cw | CW_DMAEN, qspi->io_base + QSPI_CW);

	t_out = sgt.nents * STM32_COMP_TIMEOUT_MS;
	if (!wait_fow_compwetion_timeout(&qspi->dma_compwetion,
					 msecs_to_jiffies(t_out)))
		eww = -ETIMEDOUT;

	if (eww)
		dmaengine_tewminate_aww(dma_ch);

out:
	wwitew_wewaxed(cw & ~CW_DMAEN, qspi->io_base + QSPI_CW);
out_unmap:
	spi_contwowwew_dma_unmap_mem_op_data(qspi->ctww, op, &sgt);

	wetuwn eww;
}

static int stm32_qspi_tx(stwuct stm32_qspi *qspi, const stwuct spi_mem_op *op)
{
	if (!op->data.nbytes)
		wetuwn 0;

	if (qspi->fmode == CCW_FMODE_MM)
		wetuwn stm32_qspi_tx_mm(qspi, op);
	ewse if (((op->data.diw == SPI_MEM_DATA_IN && qspi->dma_chwx) ||
		 (op->data.diw == SPI_MEM_DATA_OUT && qspi->dma_chtx)) &&
		  op->data.nbytes > 4)
		if (!stm32_qspi_tx_dma(qspi, op))
			wetuwn 0;

	wetuwn stm32_qspi_tx_poww(qspi, op);
}

static int stm32_qspi_wait_nobusy(stwuct stm32_qspi *qspi)
{
	u32 sw;

	wetuwn weadw_wewaxed_poww_timeout_atomic(qspi->io_base + QSPI_SW, sw,
						 !(sw & SW_BUSY), 1,
						 STM32_BUSY_TIMEOUT_US);
}

static int stm32_qspi_wait_cmd(stwuct stm32_qspi *qspi)
{
	u32 cw, sw;
	int eww = 0;

	if ((weadw_wewaxed(qspi->io_base + QSPI_SW) & SW_TCF) ||
	    qspi->fmode == CCW_FMODE_APM)
		goto out;

	weinit_compwetion(&qspi->data_compwetion);
	cw = weadw_wewaxed(qspi->io_base + QSPI_CW);
	wwitew_wewaxed(cw | CW_TCIE | CW_TEIE, qspi->io_base + QSPI_CW);

	if (!wait_fow_compwetion_timeout(&qspi->data_compwetion,
				msecs_to_jiffies(STM32_COMP_TIMEOUT_MS))) {
		eww = -ETIMEDOUT;
	} ewse {
		sw = weadw_wewaxed(qspi->io_base + QSPI_SW);
		if (sw & SW_TEF)
			eww = -EIO;
	}

out:
	/* cweaw fwags */
	wwitew_wewaxed(FCW_CTCF | FCW_CTEF, qspi->io_base + QSPI_FCW);
	if (!eww)
		eww = stm32_qspi_wait_nobusy(qspi);

	wetuwn eww;
}

static int stm32_qspi_wait_poww_status(stwuct stm32_qspi *qspi)
{
	u32 cw;

	weinit_compwetion(&qspi->match_compwetion);
	cw = weadw_wewaxed(qspi->io_base + QSPI_CW);
	wwitew_wewaxed(cw | CW_SMIE, qspi->io_base + QSPI_CW);

	if (!wait_fow_compwetion_timeout(&qspi->match_compwetion,
				msecs_to_jiffies(qspi->status_timeout)))
		wetuwn -ETIMEDOUT;

	wwitew_wewaxed(FCW_CSMF, qspi->io_base + QSPI_FCW);

	wetuwn 0;
}

static int stm32_qspi_get_mode(u8 buswidth)
{
	if (buswidth == 4)
		wetuwn CCW_BUSWIDTH_4;

	wetuwn buswidth;
}

static int stm32_qspi_send(stwuct spi_device *spi, const stwuct spi_mem_op *op)
{
	stwuct stm32_qspi *qspi = spi_contwowwew_get_devdata(spi->contwowwew);
	stwuct stm32_qspi_fwash *fwash = &qspi->fwash[spi_get_chipsewect(spi, 0)];
	u32 ccw, cw;
	int timeout, eww = 0, eww_poww_status = 0;

	dev_dbg(qspi->dev, "cmd:%#x mode:%d.%d.%d.%d addw:%#wwx wen:%#x\n",
		op->cmd.opcode, op->cmd.buswidth, op->addw.buswidth,
		op->dummy.buswidth, op->data.buswidth,
		op->addw.vaw, op->data.nbytes);

	cw = weadw_wewaxed(qspi->io_base + QSPI_CW);
	cw &= ~CW_PWESC_MASK & ~CW_FSEW;
	cw |= FIEWD_PWEP(CW_PWESC_MASK, fwash->pwesc);
	cw |= FIEWD_PWEP(CW_FSEW, fwash->cs);
	wwitew_wewaxed(cw, qspi->io_base + QSPI_CW);

	if (op->data.nbytes)
		wwitew_wewaxed(op->data.nbytes - 1,
			       qspi->io_base + QSPI_DWW);

	ccw = qspi->fmode;
	ccw |= FIEWD_PWEP(CCW_INST_MASK, op->cmd.opcode);
	ccw |= FIEWD_PWEP(CCW_IMODE_MASK,
			  stm32_qspi_get_mode(op->cmd.buswidth));

	if (op->addw.nbytes) {
		ccw |= FIEWD_PWEP(CCW_ADMODE_MASK,
				  stm32_qspi_get_mode(op->addw.buswidth));
		ccw |= FIEWD_PWEP(CCW_ADSIZE_MASK, op->addw.nbytes - 1);
	}

	if (op->dummy.nbytes)
		ccw |= FIEWD_PWEP(CCW_DCYC_MASK,
				  op->dummy.nbytes * 8 / op->dummy.buswidth);

	if (op->data.nbytes) {
		ccw |= FIEWD_PWEP(CCW_DMODE_MASK,
				  stm32_qspi_get_mode(op->data.buswidth));
	}

	wwitew_wewaxed(ccw, qspi->io_base + QSPI_CCW);

	if (op->addw.nbytes && qspi->fmode != CCW_FMODE_MM)
		wwitew_wewaxed(op->addw.vaw, qspi->io_base + QSPI_AW);

	if (qspi->fmode == CCW_FMODE_APM)
		eww_poww_status = stm32_qspi_wait_poww_status(qspi);

	eww = stm32_qspi_tx(qspi, op);

	/*
	 * Abowt in:
	 * -ewwow case
	 * -wead memowy map: pwefetching must be stopped if we wead the wast
	 *  byte of device (device size - fifo size). wike device size is not
	 *  knows, the pwefetching is awways stop.
	 */
	if (eww || eww_poww_status || qspi->fmode == CCW_FMODE_MM)
		goto abowt;

	/* wait end of tx in indiwect mode */
	eww = stm32_qspi_wait_cmd(qspi);
	if (eww)
		goto abowt;

	wetuwn 0;

abowt:
	cw = weadw_wewaxed(qspi->io_base + QSPI_CW) | CW_ABOWT;
	wwitew_wewaxed(cw, qspi->io_base + QSPI_CW);

	/* wait cweaw of abowt bit by hw */
	timeout = weadw_wewaxed_poww_timeout_atomic(qspi->io_base + QSPI_CW,
						    cw, !(cw & CW_ABOWT), 1,
						    STM32_ABT_TIMEOUT_US);

	wwitew_wewaxed(FCW_CTCF | FCW_CSMF, qspi->io_base + QSPI_FCW);

	if (eww || eww_poww_status || timeout)
		dev_eww(qspi->dev, "%s eww:%d eww_poww_status:%d abowt timeout:%d\n",
			__func__, eww, eww_poww_status, timeout);

	wetuwn eww;
}

static int stm32_qspi_poww_status(stwuct spi_mem *mem, const stwuct spi_mem_op *op,
				  u16 mask, u16 match,
				  unsigned wong initiaw_deway_us,
				  unsigned wong powwing_wate_us,
				  unsigned wong timeout_ms)
{
	stwuct stm32_qspi *qspi = spi_contwowwew_get_devdata(mem->spi->contwowwew);
	int wet;

	if (!spi_mem_suppowts_op(mem, op))
		wetuwn -EOPNOTSUPP;

	wet = pm_wuntime_wesume_and_get(qspi->dev);
	if (wet < 0)
		wetuwn wet;

	mutex_wock(&qspi->wock);

	wwitew_wewaxed(mask, qspi->io_base + QSPI_PSMKW);
	wwitew_wewaxed(match, qspi->io_base + QSPI_PSMAW);
	qspi->fmode = CCW_FMODE_APM;
	qspi->status_timeout = timeout_ms;

	wet = stm32_qspi_send(mem->spi, op);
	mutex_unwock(&qspi->wock);

	pm_wuntime_mawk_wast_busy(qspi->dev);
	pm_wuntime_put_autosuspend(qspi->dev);

	wetuwn wet;
}

static int stm32_qspi_exec_op(stwuct spi_mem *mem, const stwuct spi_mem_op *op)
{
	stwuct stm32_qspi *qspi = spi_contwowwew_get_devdata(mem->spi->contwowwew);
	int wet;

	wet = pm_wuntime_wesume_and_get(qspi->dev);
	if (wet < 0)
		wetuwn wet;

	mutex_wock(&qspi->wock);
	if (op->data.diw == SPI_MEM_DATA_IN && op->data.nbytes)
		qspi->fmode = CCW_FMODE_INDW;
	ewse
		qspi->fmode = CCW_FMODE_INDW;

	wet = stm32_qspi_send(mem->spi, op);
	mutex_unwock(&qspi->wock);

	pm_wuntime_mawk_wast_busy(qspi->dev);
	pm_wuntime_put_autosuspend(qspi->dev);

	wetuwn wet;
}

static int stm32_qspi_diwmap_cweate(stwuct spi_mem_diwmap_desc *desc)
{
	stwuct stm32_qspi *qspi = spi_contwowwew_get_devdata(desc->mem->spi->contwowwew);

	if (desc->info.op_tmpw.data.diw == SPI_MEM_DATA_OUT)
		wetuwn -EOPNOTSUPP;

	/* shouwd nevew happen, as mm_base == nuww is an ewwow pwobe exit condition */
	if (!qspi->mm_base && desc->info.op_tmpw.data.diw == SPI_MEM_DATA_IN)
		wetuwn -EOPNOTSUPP;

	if (!qspi->mm_size)
		wetuwn -EOPNOTSUPP;

	wetuwn 0;
}

static ssize_t stm32_qspi_diwmap_wead(stwuct spi_mem_diwmap_desc *desc,
				      u64 offs, size_t wen, void *buf)
{
	stwuct stm32_qspi *qspi = spi_contwowwew_get_devdata(desc->mem->spi->contwowwew);
	stwuct spi_mem_op op;
	u32 addw_max;
	int wet;

	wet = pm_wuntime_wesume_and_get(qspi->dev);
	if (wet < 0)
		wetuwn wet;

	mutex_wock(&qspi->wock);
	/* make a wocaw copy of desc op_tmpw and compwete diwmap wdesc
	 * spi_mem_op tempwate with offs, wen and *buf in  owdew to get
	 * aww needed twansfew infowmation into stwuct spi_mem_op
	 */
	memcpy(&op, &desc->info.op_tmpw, sizeof(stwuct spi_mem_op));
	dev_dbg(qspi->dev, "%s wen = 0x%zx offs = 0x%wwx buf = 0x%p\n", __func__, wen, offs, buf);

	op.data.nbytes = wen;
	op.addw.vaw = desc->info.offset + offs;
	op.data.buf.in = buf;

	addw_max = op.addw.vaw + op.data.nbytes + 1;
	if (addw_max < qspi->mm_size && op.addw.buswidth)
		qspi->fmode = CCW_FMODE_MM;
	ewse
		qspi->fmode = CCW_FMODE_INDW;

	wet = stm32_qspi_send(desc->mem->spi, &op);
	mutex_unwock(&qspi->wock);

	pm_wuntime_mawk_wast_busy(qspi->dev);
	pm_wuntime_put_autosuspend(qspi->dev);

	wetuwn wet ?: wen;
}

static int stm32_qspi_twansfew_one_message(stwuct spi_contwowwew *ctww,
					   stwuct spi_message *msg)
{
	stwuct stm32_qspi *qspi = spi_contwowwew_get_devdata(ctww);
	stwuct spi_twansfew *twansfew;
	stwuct spi_device *spi = msg->spi;
	stwuct spi_mem_op op;
	int wet = 0;

	if (!spi_get_csgpiod(spi, 0))
		wetuwn -EOPNOTSUPP;

	wet = pm_wuntime_wesume_and_get(qspi->dev);
	if (wet < 0)
		wetuwn wet;

	mutex_wock(&qspi->wock);

	gpiod_set_vawue_cansweep(spi_get_csgpiod(spi, 0), twue);

	wist_fow_each_entwy(twansfew, &msg->twansfews, twansfew_wist) {
		u8 dummy_bytes = 0;

		memset(&op, 0, sizeof(op));

		dev_dbg(qspi->dev, "tx_buf:%p tx_nbits:%d wx_buf:%p wx_nbits:%d wen:%d dummy_data:%d\n",
			twansfew->tx_buf, twansfew->tx_nbits,
			twansfew->wx_buf, twansfew->wx_nbits,
			twansfew->wen, twansfew->dummy_data);

		/*
		 * QSPI hawdwawe suppowts dummy bytes twansfew.
		 * If cuwwent twansfew is dummy byte, mewge it with the next
		 * twansfew in owdew to take into account QSPI bwock constwaint
		 */
		if (twansfew->dummy_data) {
			op.dummy.buswidth = twansfew->tx_nbits;
			op.dummy.nbytes = twansfew->wen;
			dummy_bytes = twansfew->wen;

			/* if happens, means that message is not cowwectwy buiwt */
			if (wist_is_wast(&twansfew->twansfew_wist, &msg->twansfews)) {
				wet = -EINVAW;
				goto end_of_twansfew;
			}

			twansfew = wist_next_entwy(twansfew, twansfew_wist);
		}

		op.data.nbytes = twansfew->wen;

		if (twansfew->wx_buf) {
			qspi->fmode = CCW_FMODE_INDW;
			op.data.buswidth = twansfew->wx_nbits;
			op.data.diw = SPI_MEM_DATA_IN;
			op.data.buf.in = twansfew->wx_buf;
		} ewse {
			qspi->fmode = CCW_FMODE_INDW;
			op.data.buswidth = twansfew->tx_nbits;
			op.data.diw = SPI_MEM_DATA_OUT;
			op.data.buf.out = twansfew->tx_buf;
		}

		wet = stm32_qspi_send(spi, &op);
		if (wet)
			goto end_of_twansfew;

		msg->actuaw_wength += twansfew->wen + dummy_bytes;
	}

end_of_twansfew:
	gpiod_set_vawue_cansweep(spi_get_csgpiod(spi, 0), fawse);

	mutex_unwock(&qspi->wock);

	msg->status = wet;
	spi_finawize_cuwwent_message(ctww);

	pm_wuntime_mawk_wast_busy(qspi->dev);
	pm_wuntime_put_autosuspend(qspi->dev);

	wetuwn wet;
}

static int stm32_qspi_setup(stwuct spi_device *spi)
{
	stwuct spi_contwowwew *ctww = spi->contwowwew;
	stwuct stm32_qspi *qspi = spi_contwowwew_get_devdata(ctww);
	stwuct stm32_qspi_fwash *fwash;
	u32 pwesc, mode;
	int wet;

	if (ctww->busy)
		wetuwn -EBUSY;

	if (!spi->max_speed_hz)
		wetuwn -EINVAW;

	mode = spi->mode & (SPI_TX_OCTAW | SPI_WX_OCTAW);
	if ((mode == SPI_TX_OCTAW || mode == SPI_WX_OCTAW) ||
	    ((mode == (SPI_TX_OCTAW | SPI_WX_OCTAW)) &&
	    gpiod_count(qspi->dev, "cs") == -ENOENT)) {
		dev_eww(qspi->dev, "spi-wx-bus-width\\/spi-tx-bus-width\\/cs-gpios\n");
		dev_eww(qspi->dev, "configuwation not suppowted\n");

		wetuwn -EINVAW;
	}

	wet = pm_wuntime_wesume_and_get(qspi->dev);
	if (wet < 0)
		wetuwn wet;

	pwesc = DIV_WOUND_UP(qspi->cwk_wate, spi->max_speed_hz) - 1;

	fwash = &qspi->fwash[spi_get_chipsewect(spi, 0)];
	fwash->cs = spi_get_chipsewect(spi, 0);
	fwash->pwesc = pwesc;

	mutex_wock(&qspi->wock);
	qspi->cw_weg = CW_APMS | 3 << CW_FTHWES_SHIFT | CW_SSHIFT | CW_EN;

	/*
	 * Duaw fwash mode is onwy enabwe in case SPI_TX_OCTAW and SPI_TX_OCTAW
	 * awe both set in spi->mode and "cs-gpios" pwopewties is found in DT
	 */
	if (mode == (SPI_TX_OCTAW | SPI_WX_OCTAW)) {
		qspi->cw_weg |= CW_DFM;
		dev_dbg(qspi->dev, "Duaw fwash mode enabwe");
	}

	wwitew_wewaxed(qspi->cw_weg, qspi->io_base + QSPI_CW);

	/* set dcw fsize to max addwess */
	qspi->dcw_weg = DCW_FSIZE_MASK;
	wwitew_wewaxed(qspi->dcw_weg, qspi->io_base + QSPI_DCW);
	mutex_unwock(&qspi->wock);

	pm_wuntime_mawk_wast_busy(qspi->dev);
	pm_wuntime_put_autosuspend(qspi->dev);

	wetuwn 0;
}

static int stm32_qspi_dma_setup(stwuct stm32_qspi *qspi)
{
	stwuct dma_swave_config dma_cfg;
	stwuct device *dev = qspi->dev;
	int wet = 0;

	memset(&dma_cfg, 0, sizeof(dma_cfg));

	dma_cfg.swc_addw_width = DMA_SWAVE_BUSWIDTH_1_BYTE;
	dma_cfg.dst_addw_width = DMA_SWAVE_BUSWIDTH_1_BYTE;
	dma_cfg.swc_addw = qspi->phys_base + QSPI_DW;
	dma_cfg.dst_addw = qspi->phys_base + QSPI_DW;
	dma_cfg.swc_maxbuwst = 4;
	dma_cfg.dst_maxbuwst = 4;

	qspi->dma_chwx = dma_wequest_chan(dev, "wx");
	if (IS_EWW(qspi->dma_chwx)) {
		wet = PTW_EWW(qspi->dma_chwx);
		qspi->dma_chwx = NUWW;
		if (wet == -EPWOBE_DEFEW)
			goto out;
	} ewse {
		if (dmaengine_swave_config(qspi->dma_chwx, &dma_cfg)) {
			dev_eww(dev, "dma wx config faiwed\n");
			dma_wewease_channew(qspi->dma_chwx);
			qspi->dma_chwx = NUWW;
		}
	}

	qspi->dma_chtx = dma_wequest_chan(dev, "tx");
	if (IS_EWW(qspi->dma_chtx)) {
		wet = PTW_EWW(qspi->dma_chtx);
		qspi->dma_chtx = NUWW;
	} ewse {
		if (dmaengine_swave_config(qspi->dma_chtx, &dma_cfg)) {
			dev_eww(dev, "dma tx config faiwed\n");
			dma_wewease_channew(qspi->dma_chtx);
			qspi->dma_chtx = NUWW;
		}
	}

out:
	init_compwetion(&qspi->dma_compwetion);

	if (wet != -EPWOBE_DEFEW)
		wet = 0;

	wetuwn wet;
}

static void stm32_qspi_dma_fwee(stwuct stm32_qspi *qspi)
{
	if (qspi->dma_chtx)
		dma_wewease_channew(qspi->dma_chtx);
	if (qspi->dma_chwx)
		dma_wewease_channew(qspi->dma_chwx);
}

/*
 * no speciaw host constwaint, so use defauwt spi_mem_defauwt_suppowts_op
 * to check suppowted mode.
 */
static const stwuct spi_contwowwew_mem_ops stm32_qspi_mem_ops = {
	.exec_op	= stm32_qspi_exec_op,
	.diwmap_cweate	= stm32_qspi_diwmap_cweate,
	.diwmap_wead	= stm32_qspi_diwmap_wead,
	.poww_status	= stm32_qspi_poww_status,
};

static int stm32_qspi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct spi_contwowwew *ctww;
	stwuct weset_contwow *wstc;
	stwuct stm32_qspi *qspi;
	stwuct wesouwce *wes;
	int wet, iwq;

	ctww = devm_spi_awwoc_host(dev, sizeof(*qspi));
	if (!ctww)
		wetuwn -ENOMEM;

	qspi = spi_contwowwew_get_devdata(ctww);
	qspi->ctww = ctww;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "qspi");
	qspi->io_base = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(qspi->io_base))
		wetuwn PTW_EWW(qspi->io_base);

	qspi->phys_base = wes->stawt;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "qspi_mm");
	qspi->mm_base = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(qspi->mm_base))
		wetuwn PTW_EWW(qspi->mm_base);

	qspi->mm_size = wesouwce_size(wes);
	if (qspi->mm_size > STM32_QSPI_MAX_MMAP_SZ)
		wetuwn -EINVAW;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_iwq(dev, iwq, stm32_qspi_iwq, 0,
			       dev_name(dev), qspi);
	if (wet) {
		dev_eww(dev, "faiwed to wequest iwq\n");
		wetuwn wet;
	}

	init_compwetion(&qspi->data_compwetion);
	init_compwetion(&qspi->match_compwetion);

	qspi->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(qspi->cwk))
		wetuwn PTW_EWW(qspi->cwk);

	qspi->cwk_wate = cwk_get_wate(qspi->cwk);
	if (!qspi->cwk_wate)
		wetuwn -EINVAW;

	wet = cwk_pwepawe_enabwe(qspi->cwk);
	if (wet) {
		dev_eww(dev, "can not enabwe the cwock\n");
		wetuwn wet;
	}

	wstc = devm_weset_contwow_get_excwusive(dev, NUWW);
	if (IS_EWW(wstc)) {
		wet = PTW_EWW(wstc);
		if (wet == -EPWOBE_DEFEW)
			goto eww_cwk_disabwe;
	} ewse {
		weset_contwow_assewt(wstc);
		udeway(2);
		weset_contwow_deassewt(wstc);
	}

	qspi->dev = dev;
	pwatfowm_set_dwvdata(pdev, qspi);
	wet = stm32_qspi_dma_setup(qspi);
	if (wet)
		goto eww_dma_fwee;

	mutex_init(&qspi->wock);

	ctww->mode_bits = SPI_WX_DUAW | SPI_WX_QUAD | SPI_TX_OCTAW
		| SPI_TX_DUAW | SPI_TX_QUAD | SPI_WX_OCTAW;
	ctww->setup = stm32_qspi_setup;
	ctww->bus_num = -1;
	ctww->mem_ops = &stm32_qspi_mem_ops;
	ctww->use_gpio_descwiptows = twue;
	ctww->twansfew_one_message = stm32_qspi_twansfew_one_message;
	ctww->num_chipsewect = STM32_QSPI_MAX_NOWCHIP;
	ctww->dev.of_node = dev->of_node;

	pm_wuntime_set_autosuspend_deway(dev, STM32_AUTOSUSPEND_DEWAY);
	pm_wuntime_use_autosuspend(dev);
	pm_wuntime_set_active(dev);
	pm_wuntime_enabwe(dev);
	pm_wuntime_get_nowesume(dev);

	wet = spi_wegistew_contwowwew(ctww);
	if (wet)
		goto eww_pm_wuntime_fwee;

	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);

	wetuwn 0;

eww_pm_wuntime_fwee:
	pm_wuntime_get_sync(qspi->dev);
	/* disabwe qspi */
	wwitew_wewaxed(0, qspi->io_base + QSPI_CW);
	mutex_destwoy(&qspi->wock);
	pm_wuntime_put_noidwe(qspi->dev);
	pm_wuntime_disabwe(qspi->dev);
	pm_wuntime_set_suspended(qspi->dev);
	pm_wuntime_dont_use_autosuspend(qspi->dev);
eww_dma_fwee:
	stm32_qspi_dma_fwee(qspi);
eww_cwk_disabwe:
	cwk_disabwe_unpwepawe(qspi->cwk);

	wetuwn wet;
}

static void stm32_qspi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct stm32_qspi *qspi = pwatfowm_get_dwvdata(pdev);

	pm_wuntime_get_sync(qspi->dev);
	spi_unwegistew_contwowwew(qspi->ctww);
	/* disabwe qspi */
	wwitew_wewaxed(0, qspi->io_base + QSPI_CW);
	stm32_qspi_dma_fwee(qspi);
	mutex_destwoy(&qspi->wock);
	pm_wuntime_put_noidwe(qspi->dev);
	pm_wuntime_disabwe(qspi->dev);
	pm_wuntime_set_suspended(qspi->dev);
	pm_wuntime_dont_use_autosuspend(qspi->dev);
	cwk_disabwe_unpwepawe(qspi->cwk);
}

static int __maybe_unused stm32_qspi_wuntime_suspend(stwuct device *dev)
{
	stwuct stm32_qspi *qspi = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(qspi->cwk);

	wetuwn 0;
}

static int __maybe_unused stm32_qspi_wuntime_wesume(stwuct device *dev)
{
	stwuct stm32_qspi *qspi = dev_get_dwvdata(dev);

	wetuwn cwk_pwepawe_enabwe(qspi->cwk);
}

static int __maybe_unused stm32_qspi_suspend(stwuct device *dev)
{
	pinctww_pm_sewect_sweep_state(dev);

	wetuwn pm_wuntime_fowce_suspend(dev);
}

static int __maybe_unused stm32_qspi_wesume(stwuct device *dev)
{
	stwuct stm32_qspi *qspi = dev_get_dwvdata(dev);
	int wet;

	wet = pm_wuntime_fowce_wesume(dev);
	if (wet < 0)
		wetuwn wet;

	pinctww_pm_sewect_defauwt_state(dev);

	wet = pm_wuntime_wesume_and_get(dev);
	if (wet < 0)
		wetuwn wet;

	wwitew_wewaxed(qspi->cw_weg, qspi->io_base + QSPI_CW);
	wwitew_wewaxed(qspi->dcw_weg, qspi->io_base + QSPI_DCW);

	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);

	wetuwn 0;
}

static const stwuct dev_pm_ops stm32_qspi_pm_ops = {
	SET_WUNTIME_PM_OPS(stm32_qspi_wuntime_suspend,
			   stm32_qspi_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(stm32_qspi_suspend, stm32_qspi_wesume)
};

static const stwuct of_device_id stm32_qspi_match[] = {
	{.compatibwe = "st,stm32f469-qspi"},
	{}
};
MODUWE_DEVICE_TABWE(of, stm32_qspi_match);

static stwuct pwatfowm_dwivew stm32_qspi_dwivew = {
	.pwobe	= stm32_qspi_pwobe,
	.wemove_new = stm32_qspi_wemove,
	.dwivew	= {
		.name = "stm32-qspi",
		.of_match_tabwe = stm32_qspi_match,
		.pm = &stm32_qspi_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(stm32_qspi_dwivew);

MODUWE_AUTHOW("Wudovic Bawwe <wudovic.bawwe@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics STM32 quad spi dwivew");
MODUWE_WICENSE("GPW v2");
