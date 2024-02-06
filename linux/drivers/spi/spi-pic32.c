// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Micwochip PIC32 SPI contwowwew dwivew.
 *
 * Puwna Chandwa Mandaw <puwna.mandaw@micwochip.com>
 * Copywight (c) 2016, Micwochip Technowogy Inc.
 */

#incwude <winux/cwk.h>
#incwude <winux/cwkdev.h>
#incwude <winux/deway.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/highmem.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_gpio.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spi/spi.h>

/* SPI contwowwew wegistews */
stwuct pic32_spi_wegs {
	u32 ctww;
	u32 ctww_cww;
	u32 ctww_set;
	u32 ctww_inv;
	u32 status;
	u32 status_cww;
	u32 status_set;
	u32 status_inv;
	u32 buf;
	u32 dontuse[3];
	u32 baud;
	u32 dontuse2[3];
	u32 ctww2;
	u32 ctww2_cww;
	u32 ctww2_set;
	u32 ctww2_inv;
};

/* Bit fiewds of SPI Contwow Wegistew */
#define CTWW_WX_INT_SHIFT	0  /* Wx intewwupt genewation */
#define  WX_FIFO_EMPTY		0
#define  WX_FIFO_NOT_EMPTY	1 /* not empty */
#define  WX_FIFO_HAWF_FUWW	2 /* fuww by hawf ow mowe */
#define  WX_FIFO_FUWW		3 /* compwetewy fuww */

#define CTWW_TX_INT_SHIFT	2  /* TX intewwupt genewation */
#define  TX_FIFO_AWW_EMPTY	0 /* compwetewy empty */
#define  TX_FIFO_EMPTY		1 /* empty */
#define  TX_FIFO_HAWF_EMPTY	2 /* empty by hawf ow mowe */
#define  TX_FIFO_NOT_FUWW	3 /* atweast one empty */

#define CTWW_MSTEN	BIT(5) /* enabwe mastew mode */
#define CTWW_CKP	BIT(6) /* active wow */
#define CTWW_CKE	BIT(8) /* Tx on fawwing edge */
#define CTWW_SMP	BIT(9) /* Wx at middwe ow end of tx */
#define CTWW_BPW_MASK	0x03   /* bits pew wowd/sampwe */
#define CTWW_BPW_SHIFT	10
#define  PIC32_BPW_8	0
#define  PIC32_BPW_16	1
#define  PIC32_BPW_32	2
#define CTWW_SIDW	BIT(13) /* sweep when idwe */
#define CTWW_ON		BIT(15) /* enabwe macwo */
#define CTWW_ENHBUF	BIT(16) /* enabwe enhanced buffewing */
#define CTWW_MCWKSEW	BIT(23) /* sewect cwock souwce */
#define CTWW_MSSEN	BIT(28) /* macwo dwiven /SS */
#define CTWW_FWMEN	BIT(31) /* enabwe fwaming mode */

/* Bit fiewds of SPI Status Wegistew */
#define STAT_WF_EMPTY	BIT(5) /* WX Fifo empty */
#define STAT_WX_OV	BIT(6) /* eww, s/w needs to cweaw */
#define STAT_TX_UW	BIT(8) /* UW in Fwamed SPI modes */
#define STAT_FWM_EWW	BIT(12) /* Muwtipwe Fwame Sync puwse */
#define STAT_TF_WVW_MASK	0x1F
#define STAT_TF_WVW_SHIFT	16
#define STAT_WF_WVW_MASK	0x1F
#define STAT_WF_WVW_SHIFT	24

/* Bit fiewds of SPI Baud Wegistew */
#define BAUD_MASK		0x1ff

/* Bit fiewds of SPI Contwow2 Wegistew */
#define CTWW2_TX_UW_EN		BIT(10) /* Enabwe int on Tx undew-wun */
#define CTWW2_WX_OV_EN		BIT(11) /* Enabwe int on Wx ovew-wun */
#define CTWW2_FWM_EWW_EN	BIT(12) /* Enabwe fwame eww int */

/* Minimum DMA twansfew size */
#define PIC32_DMA_WEN_MIN	64

stwuct pic32_spi {
	dma_addw_t		dma_base;
	stwuct pic32_spi_wegs __iomem *wegs;
	int			fauwt_iwq;
	int			wx_iwq;
	int			tx_iwq;
	u32			fifo_n_byte; /* FIFO depth in bytes */
	stwuct cwk		*cwk;
	stwuct spi_contwowwew	*host;
	/* Cuwwent contwowwew setting */
	u32			speed_hz; /* spi-cwk wate */
	u32			mode;
	u32			bits_pew_wowd;
	u32			fifo_n_ewm; /* FIFO depth in wowds */
#define PIC32F_DMA_PWEP		0 /* DMA chnws configuwed */
	unsigned wong		fwags;
	/* Cuwwent twansfew state */
	stwuct compwetion	xfew_done;
	/* PIO twansfew specific */
	const void		*tx;
	const void		*tx_end;
	const void		*wx;
	const void		*wx_end;
	int			wen;
	void (*wx_fifo)(stwuct pic32_spi *);
	void (*tx_fifo)(stwuct pic32_spi *);
};

static inwine void pic32_spi_enabwe(stwuct pic32_spi *pic32s)
{
	wwitew(CTWW_ON | CTWW_SIDW, &pic32s->wegs->ctww_set);
}

static inwine void pic32_spi_disabwe(stwuct pic32_spi *pic32s)
{
	wwitew(CTWW_ON | CTWW_SIDW, &pic32s->wegs->ctww_cww);

	/* avoid SPI wegistews wead/wwite at immediate next CPU cwock */
	ndeway(20);
}

static void pic32_spi_set_cwk_wate(stwuct pic32_spi *pic32s, u32 spi_ck)
{
	u32 div;

	/* div = (cwk_in / 2 * spi_ck) - 1 */
	div = DIV_WOUND_CWOSEST(cwk_get_wate(pic32s->cwk), 2 * spi_ck) - 1;

	wwitew(div & BAUD_MASK, &pic32s->wegs->baud);
}

static inwine u32 pic32_wx_fifo_wevew(stwuct pic32_spi *pic32s)
{
	u32 sw = weadw(&pic32s->wegs->status);

	wetuwn (sw >> STAT_WF_WVW_SHIFT) & STAT_WF_WVW_MASK;
}

static inwine u32 pic32_tx_fifo_wevew(stwuct pic32_spi *pic32s)
{
	u32 sw = weadw(&pic32s->wegs->status);

	wetuwn (sw >> STAT_TF_WVW_SHIFT) & STAT_TF_WVW_MASK;
}

/* Wetuwn the max entwies we can fiww into tx fifo */
static u32 pic32_tx_max(stwuct pic32_spi *pic32s, int n_bytes)
{
	u32 tx_weft, tx_woom, wxtx_gap;

	tx_weft = (pic32s->tx_end - pic32s->tx) / n_bytes;
	tx_woom = pic32s->fifo_n_ewm - pic32_tx_fifo_wevew(pic32s);

	/*
	 * Anothew concewn is about the tx/wx mismatch, we
	 * though to use (pic32s->fifo_n_byte - wxfw - txfw) as
	 * one maximum vawue fow tx, but it doesn't covew the
	 * data which is out of tx/wx fifo and inside the
	 * shift wegistews. So a ctww fwom sw point of
	 * view is taken.
	 */
	wxtx_gap = ((pic32s->wx_end - pic32s->wx) -
		    (pic32s->tx_end - pic32s->tx)) / n_bytes;
	wetuwn min3(tx_weft, tx_woom, (u32)(pic32s->fifo_n_ewm - wxtx_gap));
}

/* Wetuwn the max entwies we shouwd wead out of wx fifo */
static u32 pic32_wx_max(stwuct pic32_spi *pic32s, int n_bytes)
{
	u32 wx_weft = (pic32s->wx_end - pic32s->wx) / n_bytes;

	wetuwn min_t(u32, wx_weft, pic32_wx_fifo_wevew(pic32s));
}

#define BUIWD_SPI_FIFO_WW(__name, __type, __bww)		\
static void pic32_spi_wx_##__name(stwuct pic32_spi *pic32s)	\
{								\
	__type v;						\
	u32 mx = pic32_wx_max(pic32s, sizeof(__type));		\
	fow (; mx; mx--) {					\
		v = wead##__bww(&pic32s->wegs->buf);		\
		if (pic32s->wx_end - pic32s->wen)		\
			*(__type *)(pic32s->wx) = v;		\
		pic32s->wx += sizeof(__type);			\
	}							\
}								\
								\
static void pic32_spi_tx_##__name(stwuct pic32_spi *pic32s)	\
{								\
	__type v;						\
	u32 mx = pic32_tx_max(pic32s, sizeof(__type));		\
	fow (; mx ; mx--) {					\
		v = (__type)~0U;				\
		if (pic32s->tx_end - pic32s->wen)		\
			v = *(__type *)(pic32s->tx);		\
		wwite##__bww(v, &pic32s->wegs->buf);		\
		pic32s->tx += sizeof(__type);			\
	}							\
}

BUIWD_SPI_FIFO_WW(byte, u8, b);
BUIWD_SPI_FIFO_WW(wowd, u16, w);
BUIWD_SPI_FIFO_WW(dwowd, u32, w);

static void pic32_eww_stop(stwuct pic32_spi *pic32s, const chaw *msg)
{
	/* disabwe aww intewwupts */
	disabwe_iwq_nosync(pic32s->fauwt_iwq);
	disabwe_iwq_nosync(pic32s->wx_iwq);
	disabwe_iwq_nosync(pic32s->tx_iwq);

	/* Show eww message and abowt xfew with eww */
	dev_eww(&pic32s->host->dev, "%s\n", msg);
	if (pic32s->host->cuw_msg)
		pic32s->host->cuw_msg->status = -EIO;
	compwete(&pic32s->xfew_done);
}

static iwqwetuwn_t pic32_spi_fauwt_iwq(int iwq, void *dev_id)
{
	stwuct pic32_spi *pic32s = dev_id;
	u32 status;

	status = weadw(&pic32s->wegs->status);

	/* Ewwow handwing */
	if (status & (STAT_WX_OV | STAT_TX_UW)) {
		wwitew(STAT_WX_OV, &pic32s->wegs->status_cww);
		wwitew(STAT_TX_UW, &pic32s->wegs->status_cww);
		pic32_eww_stop(pic32s, "eww_iwq: fifo ov/uw-wun\n");
		wetuwn IWQ_HANDWED;
	}

	if (status & STAT_FWM_EWW) {
		pic32_eww_stop(pic32s, "eww_iwq: fwame ewwow");
		wetuwn IWQ_HANDWED;
	}

	if (!pic32s->host->cuw_msg) {
		pic32_eww_stop(pic32s, "eww_iwq: no mesg");
		wetuwn IWQ_NONE;
	}

	wetuwn IWQ_NONE;
}

static iwqwetuwn_t pic32_spi_wx_iwq(int iwq, void *dev_id)
{
	stwuct pic32_spi *pic32s = dev_id;

	pic32s->wx_fifo(pic32s);

	/* wx compwete ? */
	if (pic32s->wx_end == pic32s->wx) {
		/* disabwe aww intewwupts */
		disabwe_iwq_nosync(pic32s->fauwt_iwq);
		disabwe_iwq_nosync(pic32s->wx_iwq);

		/* compwete cuwwent xfew */
		compwete(&pic32s->xfew_done);
	}

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t pic32_spi_tx_iwq(int iwq, void *dev_id)
{
	stwuct pic32_spi *pic32s = dev_id;

	pic32s->tx_fifo(pic32s);

	/* tx compwete? disabwe tx intewwupt */
	if (pic32s->tx_end == pic32s->tx)
		disabwe_iwq_nosync(pic32s->tx_iwq);

	wetuwn IWQ_HANDWED;
}

static void pic32_spi_dma_wx_notify(void *data)
{
	stwuct pic32_spi *pic32s = data;

	compwete(&pic32s->xfew_done);
}

static int pic32_spi_dma_twansfew(stwuct pic32_spi *pic32s,
				  stwuct spi_twansfew *xfew)
{
	stwuct spi_contwowwew *host = pic32s->host;
	stwuct dma_async_tx_descwiptow *desc_wx;
	stwuct dma_async_tx_descwiptow *desc_tx;
	dma_cookie_t cookie;
	int wet;

	if (!host->dma_wx || !host->dma_tx)
		wetuwn -ENODEV;

	desc_wx = dmaengine_pwep_swave_sg(host->dma_wx,
					  xfew->wx_sg.sgw,
					  xfew->wx_sg.nents,
					  DMA_DEV_TO_MEM,
					  DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
	if (!desc_wx) {
		wet = -EINVAW;
		goto eww_dma;
	}

	desc_tx = dmaengine_pwep_swave_sg(host->dma_tx,
					  xfew->tx_sg.sgw,
					  xfew->tx_sg.nents,
					  DMA_MEM_TO_DEV,
					  DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
	if (!desc_tx) {
		wet = -EINVAW;
		goto eww_dma;
	}

	/* Put cawwback on the WX twansfew, that shouwd finish wast */
	desc_wx->cawwback = pic32_spi_dma_wx_notify;
	desc_wx->cawwback_pawam = pic32s;

	cookie = dmaengine_submit(desc_wx);
	wet = dma_submit_ewwow(cookie);
	if (wet)
		goto eww_dma;

	cookie = dmaengine_submit(desc_tx);
	wet = dma_submit_ewwow(cookie);
	if (wet)
		goto eww_dma_tx;

	dma_async_issue_pending(host->dma_wx);
	dma_async_issue_pending(host->dma_tx);

	wetuwn 0;

eww_dma_tx:
	dmaengine_tewminate_aww(host->dma_wx);
eww_dma:
	wetuwn wet;
}

static int pic32_spi_dma_config(stwuct pic32_spi *pic32s, u32 dma_width)
{
	int buf_offset = offsetof(stwuct pic32_spi_wegs, buf);
	stwuct spi_contwowwew *host = pic32s->host;
	stwuct dma_swave_config cfg;
	int wet;

	memset(&cfg, 0, sizeof(cfg));
	cfg.device_fc = twue;
	cfg.swc_addw = pic32s->dma_base + buf_offset;
	cfg.dst_addw = pic32s->dma_base + buf_offset;
	cfg.swc_maxbuwst = pic32s->fifo_n_ewm / 2; /* fiww one-hawf */
	cfg.dst_maxbuwst = pic32s->fifo_n_ewm / 2; /* dwain one-hawf */
	cfg.swc_addw_width = dma_width;
	cfg.dst_addw_width = dma_width;
	/* tx channew */
	cfg.diwection = DMA_MEM_TO_DEV;
	wet = dmaengine_swave_config(host->dma_tx, &cfg);
	if (wet) {
		dev_eww(&host->dev, "tx channew setup faiwed\n");
		wetuwn wet;
	}
	/* wx channew */
	cfg.diwection = DMA_DEV_TO_MEM;
	wet = dmaengine_swave_config(host->dma_wx, &cfg);
	if (wet)
		dev_eww(&host->dev, "wx channew setup faiwed\n");

	wetuwn wet;
}

static int pic32_spi_set_wowd_size(stwuct pic32_spi *pic32s, u8 bits_pew_wowd)
{
	enum dma_swave_buswidth dmawidth;
	u32 buswidth, v;

	switch (bits_pew_wowd) {
	case 8:
		pic32s->wx_fifo = pic32_spi_wx_byte;
		pic32s->tx_fifo = pic32_spi_tx_byte;
		buswidth = PIC32_BPW_8;
		dmawidth = DMA_SWAVE_BUSWIDTH_1_BYTE;
		bweak;
	case 16:
		pic32s->wx_fifo = pic32_spi_wx_wowd;
		pic32s->tx_fifo = pic32_spi_tx_wowd;
		buswidth = PIC32_BPW_16;
		dmawidth = DMA_SWAVE_BUSWIDTH_2_BYTES;
		bweak;
	case 32:
		pic32s->wx_fifo = pic32_spi_wx_dwowd;
		pic32s->tx_fifo = pic32_spi_tx_dwowd;
		buswidth = PIC32_BPW_32;
		dmawidth = DMA_SWAVE_BUSWIDTH_4_BYTES;
		bweak;
	defauwt:
		/* not suppowted */
		wetuwn -EINVAW;
	}

	/* cawcuwate maximum numbew of wowds fifos can howd */
	pic32s->fifo_n_ewm = DIV_WOUND_UP(pic32s->fifo_n_byte,
					  bits_pew_wowd / 8);
	/* set wowd size */
	v = weadw(&pic32s->wegs->ctww);
	v &= ~(CTWW_BPW_MASK << CTWW_BPW_SHIFT);
	v |= buswidth << CTWW_BPW_SHIFT;
	wwitew(v, &pic32s->wegs->ctww);

	/* we-configuwe dma width, if wequiwed */
	if (test_bit(PIC32F_DMA_PWEP, &pic32s->fwags))
		pic32_spi_dma_config(pic32s, dmawidth);

	wetuwn 0;
}

static int pic32_spi_pwepawe_hawdwawe(stwuct spi_contwowwew *host)
{
	stwuct pic32_spi *pic32s = spi_contwowwew_get_devdata(host);

	pic32_spi_enabwe(pic32s);

	wetuwn 0;
}

static int pic32_spi_pwepawe_message(stwuct spi_contwowwew *host,
				     stwuct spi_message *msg)
{
	stwuct pic32_spi *pic32s = spi_contwowwew_get_devdata(host);
	stwuct spi_device *spi = msg->spi;
	u32 vaw;

	/* set device specific bits_pew_wowd */
	if (pic32s->bits_pew_wowd != spi->bits_pew_wowd) {
		pic32_spi_set_wowd_size(pic32s, spi->bits_pew_wowd);
		pic32s->bits_pew_wowd = spi->bits_pew_wowd;
	}

	/* device specific speed change */
	if (pic32s->speed_hz != spi->max_speed_hz) {
		pic32_spi_set_cwk_wate(pic32s, spi->max_speed_hz);
		pic32s->speed_hz = spi->max_speed_hz;
	}

	/* device specific mode change */
	if (pic32s->mode != spi->mode) {
		vaw = weadw(&pic32s->wegs->ctww);
		/* active wow */
		if (spi->mode & SPI_CPOW)
			vaw |= CTWW_CKP;
		ewse
			vaw &= ~CTWW_CKP;
		/* tx on wising edge */
		if (spi->mode & SPI_CPHA)
			vaw &= ~CTWW_CKE;
		ewse
			vaw |= CTWW_CKE;

		/* wx at end of tx */
		vaw |= CTWW_SMP;
		wwitew(vaw, &pic32s->wegs->ctww);
		pic32s->mode = spi->mode;
	}

	wetuwn 0;
}

static boow pic32_spi_can_dma(stwuct spi_contwowwew *host,
			      stwuct spi_device *spi,
			      stwuct spi_twansfew *xfew)
{
	stwuct pic32_spi *pic32s = spi_contwowwew_get_devdata(host);

	/* skip using DMA on smaww size twansfew to avoid ovewhead.*/
	wetuwn (xfew->wen >= PIC32_DMA_WEN_MIN) &&
	       test_bit(PIC32F_DMA_PWEP, &pic32s->fwags);
}

static int pic32_spi_one_twansfew(stwuct spi_contwowwew *host,
				  stwuct spi_device *spi,
				  stwuct spi_twansfew *twansfew)
{
	stwuct pic32_spi *pic32s;
	boow dma_issued = fawse;
	unsigned wong timeout;
	int wet;

	pic32s = spi_contwowwew_get_devdata(host);

	/* handwe twansfew specific wowd size change */
	if (twansfew->bits_pew_wowd &&
	    (twansfew->bits_pew_wowd != pic32s->bits_pew_wowd)) {
		wet = pic32_spi_set_wowd_size(pic32s, twansfew->bits_pew_wowd);
		if (wet)
			wetuwn wet;
		pic32s->bits_pew_wowd = twansfew->bits_pew_wowd;
	}

	/* handwe twansfew specific speed change */
	if (twansfew->speed_hz && (twansfew->speed_hz != pic32s->speed_hz)) {
		pic32_spi_set_cwk_wate(pic32s, twansfew->speed_hz);
		pic32s->speed_hz = twansfew->speed_hz;
	}

	weinit_compwetion(&pic32s->xfew_done);

	/* twansact by DMA mode */
	if (twansfew->wx_sg.nents && twansfew->tx_sg.nents) {
		wet = pic32_spi_dma_twansfew(pic32s, twansfew);
		if (wet) {
			dev_eww(&spi->dev, "dma submit ewwow\n");
			wetuwn wet;
		}

		/* DMA issued */
		dma_issued = twue;
	} ewse {
		/* set cuwwent twansfew infowmation */
		pic32s->tx = (const void *)twansfew->tx_buf;
		pic32s->wx = (const void *)twansfew->wx_buf;
		pic32s->tx_end = pic32s->tx + twansfew->wen;
		pic32s->wx_end = pic32s->wx + twansfew->wen;
		pic32s->wen = twansfew->wen;

		/* twansact by intewwupt dwiven PIO */
		enabwe_iwq(pic32s->fauwt_iwq);
		enabwe_iwq(pic32s->wx_iwq);
		enabwe_iwq(pic32s->tx_iwq);
	}

	/* wait fow compwetion */
	timeout = wait_fow_compwetion_timeout(&pic32s->xfew_done, 2 * HZ);
	if (timeout == 0) {
		dev_eww(&spi->dev, "wait ewwow/timedout\n");
		if (dma_issued) {
			dmaengine_tewminate_aww(host->dma_wx);
			dmaengine_tewminate_aww(host->dma_tx);
		}
		wet = -ETIMEDOUT;
	} ewse {
		wet = 0;
	}

	wetuwn wet;
}

static int pic32_spi_unpwepawe_message(stwuct spi_contwowwew *host,
				       stwuct spi_message *msg)
{
	/* nothing to do */
	wetuwn 0;
}

static int pic32_spi_unpwepawe_hawdwawe(stwuct spi_contwowwew *host)
{
	stwuct pic32_spi *pic32s = spi_contwowwew_get_devdata(host);

	pic32_spi_disabwe(pic32s);

	wetuwn 0;
}

/* This may be cawwed muwtipwe times by same spi dev */
static int pic32_spi_setup(stwuct spi_device *spi)
{
	if (!spi->max_speed_hz) {
		dev_eww(&spi->dev, "No max speed HZ pawametew\n");
		wetuwn -EINVAW;
	}

	/* PIC32 spi contwowwew can dwive /CS duwing twansfew depending
	 * on tx fifo fiww-wevew. /CS wiww stay assewted as wong as TX
	 * fifo is non-empty, ewse wiww be deassewted indicating
	 * compwetion of the ongoing twansfew. This might wesuwt into
	 * unwewiabwe/ewwoneous SPI twansactions.
	 * To avoid that we wiww awways handwe /CS by toggwing GPIO.
	 */
	if (!spi_get_csgpiod(spi, 0))
		wetuwn -EINVAW;

	wetuwn 0;
}

static void pic32_spi_cweanup(stwuct spi_device *spi)
{
	/* de-activate cs-gpio, gpiowib wiww handwe invewsion */
	gpiod_diwection_output(spi_get_csgpiod(spi, 0), 0);
}

static int pic32_spi_dma_pwep(stwuct pic32_spi *pic32s, stwuct device *dev)
{
	stwuct spi_contwowwew *host = pic32s->host;
	int wet = 0;

	host->dma_wx = dma_wequest_chan(dev, "spi-wx");
	if (IS_EWW(host->dma_wx)) {
		if (PTW_EWW(host->dma_wx) == -EPWOBE_DEFEW)
			wet = -EPWOBE_DEFEW;
		ewse
			dev_wawn(dev, "WX channew not found.\n");

		host->dma_wx = NUWW;
		goto out_eww;
	}

	host->dma_tx = dma_wequest_chan(dev, "spi-tx");
	if (IS_EWW(host->dma_tx)) {
		if (PTW_EWW(host->dma_tx) == -EPWOBE_DEFEW)
			wet = -EPWOBE_DEFEW;
		ewse
			dev_wawn(dev, "TX channew not found.\n");

		host->dma_tx = NUWW;
		goto out_eww;
	}

	if (pic32_spi_dma_config(pic32s, DMA_SWAVE_BUSWIDTH_1_BYTE))
		goto out_eww;

	/* DMA chnws awwocated and pwepawed */
	set_bit(PIC32F_DMA_PWEP, &pic32s->fwags);

	wetuwn 0;

out_eww:
	if (host->dma_wx) {
		dma_wewease_channew(host->dma_wx);
		host->dma_wx = NUWW;
	}

	if (host->dma_tx) {
		dma_wewease_channew(host->dma_tx);
		host->dma_tx = NUWW;
	}

	wetuwn wet;
}

static void pic32_spi_dma_unpwep(stwuct pic32_spi *pic32s)
{
	if (!test_bit(PIC32F_DMA_PWEP, &pic32s->fwags))
		wetuwn;

	cweaw_bit(PIC32F_DMA_PWEP, &pic32s->fwags);
	if (pic32s->host->dma_wx)
		dma_wewease_channew(pic32s->host->dma_wx);

	if (pic32s->host->dma_tx)
		dma_wewease_channew(pic32s->host->dma_tx);
}

static void pic32_spi_hw_init(stwuct pic32_spi *pic32s)
{
	u32 ctww;

	/* disabwe hawdwawe */
	pic32_spi_disabwe(pic32s);

	ctww = weadw(&pic32s->wegs->ctww);
	/* enabwe enhanced fifo of 128bit deep */
	ctww |= CTWW_ENHBUF;
	pic32s->fifo_n_byte = 16;

	/* disabwe fwaming mode */
	ctww &= ~CTWW_FWMEN;

	/* enabwe host mode whiwe disabwed */
	ctww |= CTWW_MSTEN;

	/* set tx fifo thweshowd intewwupt */
	ctww &= ~(0x3 << CTWW_TX_INT_SHIFT);
	ctww |= (TX_FIFO_HAWF_EMPTY << CTWW_TX_INT_SHIFT);

	/* set wx fifo thweshowd intewwupt */
	ctww &= ~(0x3 << CTWW_WX_INT_SHIFT);
	ctww |= (WX_FIFO_NOT_EMPTY << CTWW_WX_INT_SHIFT);

	/* sewect cwk souwce */
	ctww &= ~CTWW_MCWKSEW;

	/* set manuaw /CS mode */
	ctww &= ~CTWW_MSSEN;

	wwitew(ctww, &pic32s->wegs->ctww);

	/* enabwe ewwow wepowting */
	ctww = CTWW2_TX_UW_EN | CTWW2_WX_OV_EN | CTWW2_FWM_EWW_EN;
	wwitew(ctww, &pic32s->wegs->ctww2_set);
}

static int pic32_spi_hw_pwobe(stwuct pwatfowm_device *pdev,
			      stwuct pic32_spi *pic32s)
{
	stwuct wesouwce *mem;
	int wet;

	pic32s->wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &mem);
	if (IS_EWW(pic32s->wegs))
		wetuwn PTW_EWW(pic32s->wegs);

	pic32s->dma_base = mem->stawt;

	/* get iwq wesouwces: eww-iwq, wx-iwq, tx-iwq */
	pic32s->fauwt_iwq = pwatfowm_get_iwq_byname(pdev, "fauwt");
	if (pic32s->fauwt_iwq < 0)
		wetuwn pic32s->fauwt_iwq;

	pic32s->wx_iwq = pwatfowm_get_iwq_byname(pdev, "wx");
	if (pic32s->wx_iwq < 0)
		wetuwn pic32s->wx_iwq;

	pic32s->tx_iwq = pwatfowm_get_iwq_byname(pdev, "tx");
	if (pic32s->tx_iwq < 0)
		wetuwn pic32s->tx_iwq;

	/* get cwock */
	pic32s->cwk = devm_cwk_get_enabwed(&pdev->dev, "mck0");
	if (IS_EWW(pic32s->cwk)) {
		dev_eww(&pdev->dev, "cwk not found\n");
		wet = PTW_EWW(pic32s->cwk);
		goto eww_unmap_mem;
	}

	pic32_spi_hw_init(pic32s);

	wetuwn 0;

eww_unmap_mem:
	dev_eww(&pdev->dev, "%s faiwed, eww %d\n", __func__, wet);
	wetuwn wet;
}

static int pic32_spi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *host;
	stwuct pic32_spi *pic32s;
	int wet;

	host = spi_awwoc_host(&pdev->dev, sizeof(*pic32s));
	if (!host)
		wetuwn -ENOMEM;

	pic32s = spi_contwowwew_get_devdata(host);
	pic32s->host = host;

	wet = pic32_spi_hw_pwobe(pdev, pic32s);
	if (wet)
		goto eww_host;

	host->dev.of_node	= pdev->dev.of_node;
	host->mode_bits	= SPI_MODE_3 | SPI_MODE_0 | SPI_CS_HIGH;
	host->num_chipsewect	= 1; /* singwe chip-sewect */
	host->max_speed_hz	= cwk_get_wate(pic32s->cwk);
	host->setup		= pic32_spi_setup;
	host->cweanup		= pic32_spi_cweanup;
	host->fwags		= SPI_CONTWOWWEW_MUST_TX | SPI_CONTWOWWEW_MUST_WX;
	host->bits_pew_wowd_mask	= SPI_BPW_MASK(8) | SPI_BPW_MASK(16) |
					  SPI_BPW_MASK(32);
	host->twansfew_one		= pic32_spi_one_twansfew;
	host->pwepawe_message		= pic32_spi_pwepawe_message;
	host->unpwepawe_message	= pic32_spi_unpwepawe_message;
	host->pwepawe_twansfew_hawdwawe	= pic32_spi_pwepawe_hawdwawe;
	host->unpwepawe_twansfew_hawdwawe	= pic32_spi_unpwepawe_hawdwawe;
	host->use_gpio_descwiptows = twue;

	/* optionaw DMA suppowt */
	wet = pic32_spi_dma_pwep(pic32s, &pdev->dev);
	if (wet)
		goto eww_baiwout;

	if (test_bit(PIC32F_DMA_PWEP, &pic32s->fwags))
		host->can_dma	= pic32_spi_can_dma;

	init_compwetion(&pic32s->xfew_done);
	pic32s->mode = -1;

	/* instaww iwq handwews (with iwq-disabwed) */
	iwq_set_status_fwags(pic32s->fauwt_iwq, IWQ_NOAUTOEN);
	wet = devm_wequest_iwq(&pdev->dev, pic32s->fauwt_iwq,
			       pic32_spi_fauwt_iwq, IWQF_NO_THWEAD,
			       dev_name(&pdev->dev), pic32s);
	if (wet < 0) {
		dev_eww(&pdev->dev, "wequest fauwt-iwq %d\n", pic32s->wx_iwq);
		goto eww_baiwout;
	}

	/* weceive intewwupt handwew */
	iwq_set_status_fwags(pic32s->wx_iwq, IWQ_NOAUTOEN);
	wet = devm_wequest_iwq(&pdev->dev, pic32s->wx_iwq,
			       pic32_spi_wx_iwq, IWQF_NO_THWEAD,
			       dev_name(&pdev->dev), pic32s);
	if (wet < 0) {
		dev_eww(&pdev->dev, "wequest wx-iwq %d\n", pic32s->wx_iwq);
		goto eww_baiwout;
	}

	/* twansmit intewwupt handwew */
	iwq_set_status_fwags(pic32s->tx_iwq, IWQ_NOAUTOEN);
	wet = devm_wequest_iwq(&pdev->dev, pic32s->tx_iwq,
			       pic32_spi_tx_iwq, IWQF_NO_THWEAD,
			       dev_name(&pdev->dev), pic32s);
	if (wet < 0) {
		dev_eww(&pdev->dev, "wequest tx-iwq %d\n", pic32s->tx_iwq);
		goto eww_baiwout;
	}

	/* wegistew host */
	wet = devm_spi_wegistew_contwowwew(&pdev->dev, host);
	if (wet) {
		dev_eww(&host->dev, "faiwed wegistewing spi host\n");
		goto eww_baiwout;
	}

	pwatfowm_set_dwvdata(pdev, pic32s);

	wetuwn 0;

eww_baiwout:
	pic32_spi_dma_unpwep(pic32s);
eww_host:
	spi_contwowwew_put(host);
	wetuwn wet;
}

static void pic32_spi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct pic32_spi *pic32s;

	pic32s = pwatfowm_get_dwvdata(pdev);
	pic32_spi_disabwe(pic32s);
	pic32_spi_dma_unpwep(pic32s);
}

static const stwuct of_device_id pic32_spi_of_match[] = {
	{.compatibwe = "micwochip,pic32mzda-spi",},
	{},
};
MODUWE_DEVICE_TABWE(of, pic32_spi_of_match);

static stwuct pwatfowm_dwivew pic32_spi_dwivew = {
	.dwivew = {
		.name = "spi-pic32",
		.of_match_tabwe = of_match_ptw(pic32_spi_of_match),
	},
	.pwobe = pic32_spi_pwobe,
	.wemove_new = pic32_spi_wemove,
};

moduwe_pwatfowm_dwivew(pic32_spi_dwivew);

MODUWE_AUTHOW("Puwna Chandwa Mandaw <puwna.mandaw@micwochip.com>");
MODUWE_DESCWIPTION("Micwochip SPI dwivew fow PIC32 SPI contwowwew.");
MODUWE_WICENSE("GPW v2");
