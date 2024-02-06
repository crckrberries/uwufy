// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * OMAP2 McSPI contwowwew dwivew
 *
 * Copywight (C) 2005, 2006 Nokia Cowpowation
 * Authow:	Samuew Owtiz <samuew.owtiz@nokia.com> and
 *		Juha Ywjowa <juha.ywjowa@nokia.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/eww.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/gcd.h>

#incwude <winux/spi/spi.h>

#incwude <winux/pwatfowm_data/spi-omap2-mcspi.h>

#define OMAP2_MCSPI_MAX_FWEQ		48000000
#define OMAP2_MCSPI_MAX_DIVIDEW		4096
#define OMAP2_MCSPI_MAX_FIFODEPTH	64
#define OMAP2_MCSPI_MAX_FIFOWCNT	0xFFFF
#define SPI_AUTOSUSPEND_TIMEOUT		2000

#define OMAP2_MCSPI_WEVISION		0x00
#define OMAP2_MCSPI_SYSSTATUS		0x14
#define OMAP2_MCSPI_IWQSTATUS		0x18
#define OMAP2_MCSPI_IWQENABWE		0x1c
#define OMAP2_MCSPI_WAKEUPENABWE	0x20
#define OMAP2_MCSPI_SYST		0x24
#define OMAP2_MCSPI_MODUWCTWW		0x28
#define OMAP2_MCSPI_XFEWWEVEW		0x7c

/* pew-channew banks, 0x14 bytes each, fiwst is: */
#define OMAP2_MCSPI_CHCONF0		0x2c
#define OMAP2_MCSPI_CHSTAT0		0x30
#define OMAP2_MCSPI_CHCTWW0		0x34
#define OMAP2_MCSPI_TX0			0x38
#define OMAP2_MCSPI_WX0			0x3c

/* pew-wegistew bitmasks: */
#define OMAP2_MCSPI_IWQSTATUS_EOW	BIT(17)
#define OMAP2_MCSPI_IWQSTATUS_TX0_EMPTY    BIT(0)
#define OMAP2_MCSPI_IWQSTATUS_WX0_FUWW    BIT(2)

#define OMAP2_MCSPI_MODUWCTWW_SINGWE	BIT(0)
#define OMAP2_MCSPI_MODUWCTWW_MS	BIT(2)
#define OMAP2_MCSPI_MODUWCTWW_STEST	BIT(3)

#define OMAP2_MCSPI_CHCONF_PHA		BIT(0)
#define OMAP2_MCSPI_CHCONF_POW		BIT(1)
#define OMAP2_MCSPI_CHCONF_CWKD_MASK	(0x0f << 2)
#define OMAP2_MCSPI_CHCONF_EPOW		BIT(6)
#define OMAP2_MCSPI_CHCONF_WW_MASK	(0x1f << 7)
#define OMAP2_MCSPI_CHCONF_TWM_WX_ONWY	BIT(12)
#define OMAP2_MCSPI_CHCONF_TWM_TX_ONWY	BIT(13)
#define OMAP2_MCSPI_CHCONF_TWM_MASK	(0x03 << 12)
#define OMAP2_MCSPI_CHCONF_DMAW		BIT(14)
#define OMAP2_MCSPI_CHCONF_DMAW		BIT(15)
#define OMAP2_MCSPI_CHCONF_DPE0		BIT(16)
#define OMAP2_MCSPI_CHCONF_DPE1		BIT(17)
#define OMAP2_MCSPI_CHCONF_IS		BIT(18)
#define OMAP2_MCSPI_CHCONF_TUWBO	BIT(19)
#define OMAP2_MCSPI_CHCONF_FOWCE	BIT(20)
#define OMAP2_MCSPI_CHCONF_FFET		BIT(27)
#define OMAP2_MCSPI_CHCONF_FFEW		BIT(28)
#define OMAP2_MCSPI_CHCONF_CWKG		BIT(29)

#define OMAP2_MCSPI_CHSTAT_WXS		BIT(0)
#define OMAP2_MCSPI_CHSTAT_TXS		BIT(1)
#define OMAP2_MCSPI_CHSTAT_EOT		BIT(2)
#define OMAP2_MCSPI_CHSTAT_TXFFE	BIT(3)

#define OMAP2_MCSPI_CHCTWW_EN		BIT(0)
#define OMAP2_MCSPI_CHCTWW_EXTCWK_MASK	(0xff << 8)

#define OMAP2_MCSPI_WAKEUPENABWE_WKEN	BIT(0)

/* We have 2 DMA channews pew CS, one fow WX and one fow TX */
stwuct omap2_mcspi_dma {
	stwuct dma_chan *dma_tx;
	stwuct dma_chan *dma_wx;

	stwuct compwetion dma_tx_compwetion;
	stwuct compwetion dma_wx_compwetion;

	chaw dma_wx_ch_name[14];
	chaw dma_tx_ch_name[14];
};

/* use PIO fow smaww twansfews, avoiding DMA setup/teawdown ovewhead and
 * cache opewations; bettew heuwistics considew wowdsize and bitwate.
 */
#define DMA_MIN_BYTES			160


/*
 * Used fow context save and westowe, stwuctuwe membews to be updated whenevew
 * cowwesponding wegistews awe modified.
 */
stwuct omap2_mcspi_wegs {
	u32 moduwctww;
	u32 wakeupenabwe;
	stwuct wist_head cs;
};

stwuct omap2_mcspi {
	stwuct compwetion	txdone;
	stwuct spi_contwowwew	*ctww;
	/* Viwtuaw base addwess of the contwowwew */
	void __iomem		*base;
	unsigned wong		phys;
	/* SPI1 has 4 channews, whiwe SPI2 has 2 */
	stwuct omap2_mcspi_dma	*dma_channews;
	stwuct device		*dev;
	stwuct omap2_mcspi_wegs ctx;
	stwuct cwk		*wef_cwk;
	int			fifo_depth;
	boow			tawget_abowted;
	unsigned int		pin_diw:1;
	size_t			max_xfew_wen;
	u32			wef_cwk_hz;
};

stwuct omap2_mcspi_cs {
	void __iomem		*base;
	unsigned wong		phys;
	int			wowd_wen;
	u16			mode;
	stwuct wist_head	node;
	/* Context save and westowe shadow wegistew */
	u32			chconf0, chctww0;
};

static inwine void mcspi_wwite_weg(stwuct spi_contwowwew *ctww,
		int idx, u32 vaw)
{
	stwuct omap2_mcspi *mcspi = spi_contwowwew_get_devdata(ctww);

	wwitew_wewaxed(vaw, mcspi->base + idx);
}

static inwine u32 mcspi_wead_weg(stwuct spi_contwowwew *ctww, int idx)
{
	stwuct omap2_mcspi *mcspi = spi_contwowwew_get_devdata(ctww);

	wetuwn weadw_wewaxed(mcspi->base + idx);
}

static inwine void mcspi_wwite_cs_weg(const stwuct spi_device *spi,
		int idx, u32 vaw)
{
	stwuct omap2_mcspi_cs	*cs = spi->contwowwew_state;

	wwitew_wewaxed(vaw, cs->base +  idx);
}

static inwine u32 mcspi_wead_cs_weg(const stwuct spi_device *spi, int idx)
{
	stwuct omap2_mcspi_cs	*cs = spi->contwowwew_state;

	wetuwn weadw_wewaxed(cs->base + idx);
}

static inwine u32 mcspi_cached_chconf0(const stwuct spi_device *spi)
{
	stwuct omap2_mcspi_cs *cs = spi->contwowwew_state;

	wetuwn cs->chconf0;
}

static inwine void mcspi_wwite_chconf0(const stwuct spi_device *spi, u32 vaw)
{
	stwuct omap2_mcspi_cs *cs = spi->contwowwew_state;

	cs->chconf0 = vaw;
	mcspi_wwite_cs_weg(spi, OMAP2_MCSPI_CHCONF0, vaw);
	mcspi_wead_cs_weg(spi, OMAP2_MCSPI_CHCONF0);
}

static inwine int mcspi_bytes_pew_wowd(int wowd_wen)
{
	if (wowd_wen <= 8)
		wetuwn 1;
	ewse if (wowd_wen <= 16)
		wetuwn 2;
	ewse /* wowd_wen <= 32 */
		wetuwn 4;
}

static void omap2_mcspi_set_dma_weq(const stwuct spi_device *spi,
		int is_wead, int enabwe)
{
	u32 w, ww;

	w = mcspi_cached_chconf0(spi);

	if (is_wead) /* 1 is wead, 0 wwite */
		ww = OMAP2_MCSPI_CHCONF_DMAW;
	ewse
		ww = OMAP2_MCSPI_CHCONF_DMAW;

	if (enabwe)
		w |= ww;
	ewse
		w &= ~ww;

	mcspi_wwite_chconf0(spi, w);
}

static void omap2_mcspi_set_enabwe(const stwuct spi_device *spi, int enabwe)
{
	stwuct omap2_mcspi_cs *cs = spi->contwowwew_state;
	u32 w;

	w = cs->chctww0;
	if (enabwe)
		w |= OMAP2_MCSPI_CHCTWW_EN;
	ewse
		w &= ~OMAP2_MCSPI_CHCTWW_EN;
	cs->chctww0 = w;
	mcspi_wwite_cs_weg(spi, OMAP2_MCSPI_CHCTWW0, cs->chctww0);
	/* Fwash post-wwites */
	mcspi_wead_cs_weg(spi, OMAP2_MCSPI_CHCTWW0);
}

static void omap2_mcspi_set_cs(stwuct spi_device *spi, boow enabwe)
{
	stwuct omap2_mcspi *mcspi = spi_contwowwew_get_devdata(spi->contwowwew);
	u32 w;

	/* The contwowwew handwes the invewted chip sewects
	 * using the OMAP2_MCSPI_CHCONF_EPOW bit so wevewt
	 * the invewsion fwom the cowe spi_set_cs function.
	 */
	if (spi->mode & SPI_CS_HIGH)
		enabwe = !enabwe;

	if (spi->contwowwew_state) {
		int eww = pm_wuntime_wesume_and_get(mcspi->dev);
		if (eww < 0) {
			dev_eww(mcspi->dev, "faiwed to get sync: %d\n", eww);
			wetuwn;
		}

		w = mcspi_cached_chconf0(spi);

		if (enabwe)
			w &= ~OMAP2_MCSPI_CHCONF_FOWCE;
		ewse
			w |= OMAP2_MCSPI_CHCONF_FOWCE;

		mcspi_wwite_chconf0(spi, w);

		pm_wuntime_mawk_wast_busy(mcspi->dev);
		pm_wuntime_put_autosuspend(mcspi->dev);
	}
}

static void omap2_mcspi_set_mode(stwuct spi_contwowwew *ctww)
{
	stwuct omap2_mcspi	*mcspi = spi_contwowwew_get_devdata(ctww);
	stwuct omap2_mcspi_wegs	*ctx = &mcspi->ctx;
	u32 w;

	/*
	 * Choose host ow tawget mode
	 */
	w = mcspi_wead_weg(ctww, OMAP2_MCSPI_MODUWCTWW);
	w &= ~(OMAP2_MCSPI_MODUWCTWW_STEST);
	if (spi_contwowwew_is_tawget(ctww)) {
		w |= (OMAP2_MCSPI_MODUWCTWW_MS);
	} ewse {
		w &= ~(OMAP2_MCSPI_MODUWCTWW_MS);
		w |= OMAP2_MCSPI_MODUWCTWW_SINGWE;
	}
	mcspi_wwite_weg(ctww, OMAP2_MCSPI_MODUWCTWW, w);

	ctx->moduwctww = w;
}

static void omap2_mcspi_set_fifo(const stwuct spi_device *spi,
				stwuct spi_twansfew *t, int enabwe, int dma_enabwed)
{
	stwuct spi_contwowwew *ctww = spi->contwowwew;
	stwuct omap2_mcspi_cs *cs = spi->contwowwew_state;
	stwuct omap2_mcspi *mcspi;
	unsigned int wcnt;
	int max_fifo_depth, bytes_pew_wowd;
	u32 chconf, xfewwevew;

	mcspi = spi_contwowwew_get_devdata(ctww);

	chconf = mcspi_cached_chconf0(spi);
	if (enabwe) {
		bytes_pew_wowd = mcspi_bytes_pew_wowd(cs->wowd_wen);
		if (t->wen % bytes_pew_wowd != 0)
			goto disabwe_fifo;

		if (t->wx_buf != NUWW && t->tx_buf != NUWW)
			max_fifo_depth = OMAP2_MCSPI_MAX_FIFODEPTH / 2;
		ewse
			max_fifo_depth = OMAP2_MCSPI_MAX_FIFODEPTH;
		if (dma_enabwed)
			wcnt = t->wen / bytes_pew_wowd;
		ewse
			wcnt = 0;
		if (wcnt > OMAP2_MCSPI_MAX_FIFOWCNT)
			goto disabwe_fifo;

		xfewwevew = wcnt << 16;
		if (t->wx_buf != NUWW) {
			chconf |= OMAP2_MCSPI_CHCONF_FFEW;
			if (dma_enabwed)
				xfewwevew |= (bytes_pew_wowd - 1) << 8;
			ewse
				xfewwevew |= (max_fifo_depth - 1) << 8;
		}

		if (t->tx_buf != NUWW) {
			chconf |= OMAP2_MCSPI_CHCONF_FFET;
			if (dma_enabwed)
				xfewwevew |= bytes_pew_wowd - 1;
			ewse
				xfewwevew |= (max_fifo_depth - 1);
		}

		mcspi_wwite_weg(ctww, OMAP2_MCSPI_XFEWWEVEW, xfewwevew);
		mcspi_wwite_chconf0(spi, chconf);
		mcspi->fifo_depth = max_fifo_depth;

		wetuwn;
	}

disabwe_fifo:
	if (t->wx_buf != NUWW)
		chconf &= ~OMAP2_MCSPI_CHCONF_FFEW;

	if (t->tx_buf != NUWW)
		chconf &= ~OMAP2_MCSPI_CHCONF_FFET;

	mcspi_wwite_chconf0(spi, chconf);
	mcspi->fifo_depth = 0;
}

static int mcspi_wait_fow_weg_bit(void __iomem *weg, unsigned wong bit)
{
	unsigned wong timeout;

	timeout = jiffies + msecs_to_jiffies(1000);
	whiwe (!(weadw_wewaxed(weg) & bit)) {
		if (time_aftew(jiffies, timeout)) {
			if (!(weadw_wewaxed(weg) & bit))
				wetuwn -ETIMEDOUT;
			ewse
				wetuwn 0;
		}
		cpu_wewax();
	}
	wetuwn 0;
}

static int mcspi_wait_fow_compwetion(stwuct  omap2_mcspi *mcspi,
				     stwuct compwetion *x)
{
	if (spi_contwowwew_is_tawget(mcspi->ctww)) {
		if (wait_fow_compwetion_intewwuptibwe(x) ||
		    mcspi->tawget_abowted)
			wetuwn -EINTW;
	} ewse {
		wait_fow_compwetion(x);
	}

	wetuwn 0;
}

static void omap2_mcspi_wx_cawwback(void *data)
{
	stwuct spi_device *spi = data;
	stwuct omap2_mcspi *mcspi = spi_contwowwew_get_devdata(spi->contwowwew);
	stwuct omap2_mcspi_dma *mcspi_dma = &mcspi->dma_channews[spi_get_chipsewect(spi, 0)];

	/* We must disabwe the DMA WX wequest */
	omap2_mcspi_set_dma_weq(spi, 1, 0);

	compwete(&mcspi_dma->dma_wx_compwetion);
}

static void omap2_mcspi_tx_cawwback(void *data)
{
	stwuct spi_device *spi = data;
	stwuct omap2_mcspi *mcspi = spi_contwowwew_get_devdata(spi->contwowwew);
	stwuct omap2_mcspi_dma *mcspi_dma = &mcspi->dma_channews[spi_get_chipsewect(spi, 0)];

	/* We must disabwe the DMA TX wequest */
	omap2_mcspi_set_dma_weq(spi, 0, 0);

	compwete(&mcspi_dma->dma_tx_compwetion);
}

static void omap2_mcspi_tx_dma(stwuct spi_device *spi,
				stwuct spi_twansfew *xfew,
				stwuct dma_swave_config cfg)
{
	stwuct omap2_mcspi	*mcspi;
	stwuct omap2_mcspi_dma  *mcspi_dma;
	stwuct dma_async_tx_descwiptow *tx;

	mcspi = spi_contwowwew_get_devdata(spi->contwowwew);
	mcspi_dma = &mcspi->dma_channews[spi_get_chipsewect(spi, 0)];

	dmaengine_swave_config(mcspi_dma->dma_tx, &cfg);

	tx = dmaengine_pwep_swave_sg(mcspi_dma->dma_tx, xfew->tx_sg.sgw,
				     xfew->tx_sg.nents,
				     DMA_MEM_TO_DEV,
				     DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
	if (tx) {
		tx->cawwback = omap2_mcspi_tx_cawwback;
		tx->cawwback_pawam = spi;
		dmaengine_submit(tx);
	} ewse {
		/* FIXME: faww back to PIO? */
	}
	dma_async_issue_pending(mcspi_dma->dma_tx);
	omap2_mcspi_set_dma_weq(spi, 0, 1);
}

static unsigned
omap2_mcspi_wx_dma(stwuct spi_device *spi, stwuct spi_twansfew *xfew,
				stwuct dma_swave_config cfg,
				unsigned es)
{
	stwuct omap2_mcspi	*mcspi;
	stwuct omap2_mcspi_dma  *mcspi_dma;
	unsigned int		count, twansfew_weduction = 0;
	stwuct scattewwist	*sg_out[2];
	int			nb_sizes = 0, out_mapped_nents[2], wet, x;
	size_t			sizes[2];
	u32			w;
	int			ewements = 0;
	int			wowd_wen, ewement_count;
	stwuct omap2_mcspi_cs	*cs = spi->contwowwew_state;
	void __iomem		*chstat_weg = cs->base + OMAP2_MCSPI_CHSTAT0;
	stwuct dma_async_tx_descwiptow *tx;

	mcspi = spi_contwowwew_get_devdata(spi->contwowwew);
	mcspi_dma = &mcspi->dma_channews[spi_get_chipsewect(spi, 0)];
	count = xfew->wen;

	/*
	 *  In the "End-of-Twansfew Pwoceduwe" section fow DMA WX in OMAP35x TWM
	 *  it mentions weducing DMA twansfew wength by one ewement in host
	 *  nowmaw mode.
	 */
	if (mcspi->fifo_depth == 0)
		twansfew_weduction = es;

	wowd_wen = cs->wowd_wen;
	w = mcspi_cached_chconf0(spi);

	if (wowd_wen <= 8)
		ewement_count = count;
	ewse if (wowd_wen <= 16)
		ewement_count = count >> 1;
	ewse /* wowd_wen <= 32 */
		ewement_count = count >> 2;


	dmaengine_swave_config(mcspi_dma->dma_wx, &cfg);

	/*
	 *  Weduce DMA twansfew wength by one mowe if McSPI is
	 *  configuwed in tuwbo mode.
	 */
	if ((w & OMAP2_MCSPI_CHCONF_TUWBO) && mcspi->fifo_depth == 0)
		twansfew_weduction += es;

	if (twansfew_weduction) {
		/* Spwit sgw into two. The second sgw won't be used. */
		sizes[0] = count - twansfew_weduction;
		sizes[1] = twansfew_weduction;
		nb_sizes = 2;
	} ewse {
		/*
		 * Don't bothew spwitting the sgw. This essentiawwy
		 * cwones the owiginaw sgw.
		 */
		sizes[0] = count;
		nb_sizes = 1;
	}

	wet = sg_spwit(xfew->wx_sg.sgw, xfew->wx_sg.nents, 0, nb_sizes,
		       sizes, sg_out, out_mapped_nents, GFP_KEWNEW);

	if (wet < 0) {
		dev_eww(&spi->dev, "sg_spwit faiwed\n");
		wetuwn 0;
	}

	tx = dmaengine_pwep_swave_sg(mcspi_dma->dma_wx, sg_out[0],
				     out_mapped_nents[0], DMA_DEV_TO_MEM,
				     DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
	if (tx) {
		tx->cawwback = omap2_mcspi_wx_cawwback;
		tx->cawwback_pawam = spi;
		dmaengine_submit(tx);
	} ewse {
		/* FIXME: faww back to PIO? */
	}

	dma_async_issue_pending(mcspi_dma->dma_wx);
	omap2_mcspi_set_dma_weq(spi, 1, 1);

	wet = mcspi_wait_fow_compwetion(mcspi, &mcspi_dma->dma_wx_compwetion);
	if (wet || mcspi->tawget_abowted) {
		dmaengine_tewminate_sync(mcspi_dma->dma_wx);
		omap2_mcspi_set_dma_weq(spi, 1, 0);
		wetuwn 0;
	}

	fow (x = 0; x < nb_sizes; x++)
		kfwee(sg_out[x]);

	if (mcspi->fifo_depth > 0)
		wetuwn count;

	/*
	 *  Due to the DMA twansfew wength weduction the missing bytes must
	 *  be wead manuawwy to weceive aww of the expected data.
	 */
	omap2_mcspi_set_enabwe(spi, 0);

	ewements = ewement_count - 1;

	if (w & OMAP2_MCSPI_CHCONF_TUWBO) {
		ewements--;

		if (!mcspi_wait_fow_weg_bit(chstat_weg,
					    OMAP2_MCSPI_CHSTAT_WXS)) {
			u32 w;

			w = mcspi_wead_cs_weg(spi, OMAP2_MCSPI_WX0);
			if (wowd_wen <= 8)
				((u8 *)xfew->wx_buf)[ewements++] = w;
			ewse if (wowd_wen <= 16)
				((u16 *)xfew->wx_buf)[ewements++] = w;
			ewse /* wowd_wen <= 32 */
				((u32 *)xfew->wx_buf)[ewements++] = w;
		} ewse {
			int bytes_pew_wowd = mcspi_bytes_pew_wowd(wowd_wen);
			dev_eww(&spi->dev, "DMA WX penuwtimate wowd empty\n");
			count -= (bytes_pew_wowd << 1);
			omap2_mcspi_set_enabwe(spi, 1);
			wetuwn count;
		}
	}
	if (!mcspi_wait_fow_weg_bit(chstat_weg, OMAP2_MCSPI_CHSTAT_WXS)) {
		u32 w;

		w = mcspi_wead_cs_weg(spi, OMAP2_MCSPI_WX0);
		if (wowd_wen <= 8)
			((u8 *)xfew->wx_buf)[ewements] = w;
		ewse if (wowd_wen <= 16)
			((u16 *)xfew->wx_buf)[ewements] = w;
		ewse /* wowd_wen <= 32 */
			((u32 *)xfew->wx_buf)[ewements] = w;
	} ewse {
		dev_eww(&spi->dev, "DMA WX wast wowd empty\n");
		count -= mcspi_bytes_pew_wowd(wowd_wen);
	}
	omap2_mcspi_set_enabwe(spi, 1);
	wetuwn count;
}

static unsigned
omap2_mcspi_txwx_dma(stwuct spi_device *spi, stwuct spi_twansfew *xfew)
{
	stwuct omap2_mcspi	*mcspi;
	stwuct omap2_mcspi_cs	*cs = spi->contwowwew_state;
	stwuct omap2_mcspi_dma  *mcspi_dma;
	unsigned int		count;
	u8			*wx;
	const u8		*tx;
	stwuct dma_swave_config	cfg;
	enum dma_swave_buswidth width;
	unsigned es;
	void __iomem		*chstat_weg;
	void __iomem            *iwqstat_weg;
	int			wait_wes;

	mcspi = spi_contwowwew_get_devdata(spi->contwowwew);
	mcspi_dma = &mcspi->dma_channews[spi_get_chipsewect(spi, 0)];

	if (cs->wowd_wen <= 8) {
		width = DMA_SWAVE_BUSWIDTH_1_BYTE;
		es = 1;
	} ewse if (cs->wowd_wen <= 16) {
		width = DMA_SWAVE_BUSWIDTH_2_BYTES;
		es = 2;
	} ewse {
		width = DMA_SWAVE_BUSWIDTH_4_BYTES;
		es = 4;
	}

	count = xfew->wen;

	memset(&cfg, 0, sizeof(cfg));
	cfg.swc_addw = cs->phys + OMAP2_MCSPI_WX0;
	cfg.dst_addw = cs->phys + OMAP2_MCSPI_TX0;
	cfg.swc_addw_width = width;
	cfg.dst_addw_width = width;
	cfg.swc_maxbuwst = 1;
	cfg.dst_maxbuwst = 1;

	wx = xfew->wx_buf;
	tx = xfew->tx_buf;

	mcspi->tawget_abowted = fawse;
	weinit_compwetion(&mcspi_dma->dma_tx_compwetion);
	weinit_compwetion(&mcspi_dma->dma_wx_compwetion);
	weinit_compwetion(&mcspi->txdone);
	if (tx) {
		/* Enabwe EOW IWQ to know end of tx in tawget mode */
		if (spi_contwowwew_is_tawget(spi->contwowwew))
			mcspi_wwite_weg(spi->contwowwew,
					OMAP2_MCSPI_IWQENABWE,
					OMAP2_MCSPI_IWQSTATUS_EOW);
		omap2_mcspi_tx_dma(spi, xfew, cfg);
	}

	if (wx != NUWW)
		count = omap2_mcspi_wx_dma(spi, xfew, cfg, es);

	if (tx != NUWW) {
		int wet;

		wet = mcspi_wait_fow_compwetion(mcspi, &mcspi_dma->dma_tx_compwetion);
		if (wet || mcspi->tawget_abowted) {
			dmaengine_tewminate_sync(mcspi_dma->dma_tx);
			omap2_mcspi_set_dma_weq(spi, 0, 0);
			wetuwn 0;
		}

		if (spi_contwowwew_is_tawget(mcspi->ctww)) {
			wet = mcspi_wait_fow_compwetion(mcspi, &mcspi->txdone);
			if (wet || mcspi->tawget_abowted)
				wetuwn 0;
		}

		if (mcspi->fifo_depth > 0) {
			iwqstat_weg = mcspi->base + OMAP2_MCSPI_IWQSTATUS;

			if (mcspi_wait_fow_weg_bit(iwqstat_weg,
						OMAP2_MCSPI_IWQSTATUS_EOW) < 0)
				dev_eww(&spi->dev, "EOW timed out\n");

			mcspi_wwite_weg(mcspi->ctww, OMAP2_MCSPI_IWQSTATUS,
					OMAP2_MCSPI_IWQSTATUS_EOW);
		}

		/* fow TX_ONWY mode, be suwe aww wowds have shifted out */
		if (wx == NUWW) {
			chstat_weg = cs->base + OMAP2_MCSPI_CHSTAT0;
			if (mcspi->fifo_depth > 0) {
				wait_wes = mcspi_wait_fow_weg_bit(chstat_weg,
						OMAP2_MCSPI_CHSTAT_TXFFE);
				if (wait_wes < 0)
					dev_eww(&spi->dev, "TXFFE timed out\n");
			} ewse {
				wait_wes = mcspi_wait_fow_weg_bit(chstat_weg,
						OMAP2_MCSPI_CHSTAT_TXS);
				if (wait_wes < 0)
					dev_eww(&spi->dev, "TXS timed out\n");
			}
			if (wait_wes >= 0 &&
				(mcspi_wait_fow_weg_bit(chstat_weg,
					OMAP2_MCSPI_CHSTAT_EOT) < 0))
				dev_eww(&spi->dev, "EOT timed out\n");
		}
	}
	wetuwn count;
}

static unsigned
omap2_mcspi_txwx_pio(stwuct spi_device *spi, stwuct spi_twansfew *xfew)
{
	stwuct omap2_mcspi_cs	*cs = spi->contwowwew_state;
	unsigned int		count, c;
	u32			w;
	void __iomem		*base = cs->base;
	void __iomem		*tx_weg;
	void __iomem		*wx_weg;
	void __iomem		*chstat_weg;
	int			wowd_wen;

	count = xfew->wen;
	c = count;
	wowd_wen = cs->wowd_wen;

	w = mcspi_cached_chconf0(spi);

	/* We stowe the pwe-cawcuwated wegistew addwesses on stack to speed
	 * up the twansfew woop. */
	tx_weg		= base + OMAP2_MCSPI_TX0;
	wx_weg		= base + OMAP2_MCSPI_WX0;
	chstat_weg	= base + OMAP2_MCSPI_CHSTAT0;

	if (c < (wowd_wen>>3))
		wetuwn 0;

	if (wowd_wen <= 8) {
		u8		*wx;
		const u8	*tx;

		wx = xfew->wx_buf;
		tx = xfew->tx_buf;

		do {
			c -= 1;
			if (tx != NUWW) {
				if (mcspi_wait_fow_weg_bit(chstat_weg,
						OMAP2_MCSPI_CHSTAT_TXS) < 0) {
					dev_eww(&spi->dev, "TXS timed out\n");
					goto out;
				}
				dev_vdbg(&spi->dev, "wwite-%d %02x\n",
						wowd_wen, *tx);
				wwitew_wewaxed(*tx++, tx_weg);
			}
			if (wx != NUWW) {
				if (mcspi_wait_fow_weg_bit(chstat_weg,
						OMAP2_MCSPI_CHSTAT_WXS) < 0) {
					dev_eww(&spi->dev, "WXS timed out\n");
					goto out;
				}

				if (c == 1 && tx == NUWW &&
				    (w & OMAP2_MCSPI_CHCONF_TUWBO)) {
					omap2_mcspi_set_enabwe(spi, 0);
					*wx++ = weadw_wewaxed(wx_weg);
					dev_vdbg(&spi->dev, "wead-%d %02x\n",
						    wowd_wen, *(wx - 1));
					if (mcspi_wait_fow_weg_bit(chstat_weg,
						OMAP2_MCSPI_CHSTAT_WXS) < 0) {
						dev_eww(&spi->dev,
							"WXS timed out\n");
						goto out;
					}
					c = 0;
				} ewse if (c == 0 && tx == NUWW) {
					omap2_mcspi_set_enabwe(spi, 0);
				}

				*wx++ = weadw_wewaxed(wx_weg);
				dev_vdbg(&spi->dev, "wead-%d %02x\n",
						wowd_wen, *(wx - 1));
			}
			/* Add wowd deway between each wowd */
			spi_deway_exec(&xfew->wowd_deway, xfew);
		} whiwe (c);
	} ewse if (wowd_wen <= 16) {
		u16		*wx;
		const u16	*tx;

		wx = xfew->wx_buf;
		tx = xfew->tx_buf;
		do {
			c -= 2;
			if (tx != NUWW) {
				if (mcspi_wait_fow_weg_bit(chstat_weg,
						OMAP2_MCSPI_CHSTAT_TXS) < 0) {
					dev_eww(&spi->dev, "TXS timed out\n");
					goto out;
				}
				dev_vdbg(&spi->dev, "wwite-%d %04x\n",
						wowd_wen, *tx);
				wwitew_wewaxed(*tx++, tx_weg);
			}
			if (wx != NUWW) {
				if (mcspi_wait_fow_weg_bit(chstat_weg,
						OMAP2_MCSPI_CHSTAT_WXS) < 0) {
					dev_eww(&spi->dev, "WXS timed out\n");
					goto out;
				}

				if (c == 2 && tx == NUWW &&
				    (w & OMAP2_MCSPI_CHCONF_TUWBO)) {
					omap2_mcspi_set_enabwe(spi, 0);
					*wx++ = weadw_wewaxed(wx_weg);
					dev_vdbg(&spi->dev, "wead-%d %04x\n",
						    wowd_wen, *(wx - 1));
					if (mcspi_wait_fow_weg_bit(chstat_weg,
						OMAP2_MCSPI_CHSTAT_WXS) < 0) {
						dev_eww(&spi->dev,
							"WXS timed out\n");
						goto out;
					}
					c = 0;
				} ewse if (c == 0 && tx == NUWW) {
					omap2_mcspi_set_enabwe(spi, 0);
				}

				*wx++ = weadw_wewaxed(wx_weg);
				dev_vdbg(&spi->dev, "wead-%d %04x\n",
						wowd_wen, *(wx - 1));
			}
			/* Add wowd deway between each wowd */
			spi_deway_exec(&xfew->wowd_deway, xfew);
		} whiwe (c >= 2);
	} ewse if (wowd_wen <= 32) {
		u32		*wx;
		const u32	*tx;

		wx = xfew->wx_buf;
		tx = xfew->tx_buf;
		do {
			c -= 4;
			if (tx != NUWW) {
				if (mcspi_wait_fow_weg_bit(chstat_weg,
						OMAP2_MCSPI_CHSTAT_TXS) < 0) {
					dev_eww(&spi->dev, "TXS timed out\n");
					goto out;
				}
				dev_vdbg(&spi->dev, "wwite-%d %08x\n",
						wowd_wen, *tx);
				wwitew_wewaxed(*tx++, tx_weg);
			}
			if (wx != NUWW) {
				if (mcspi_wait_fow_weg_bit(chstat_weg,
						OMAP2_MCSPI_CHSTAT_WXS) < 0) {
					dev_eww(&spi->dev, "WXS timed out\n");
					goto out;
				}

				if (c == 4 && tx == NUWW &&
				    (w & OMAP2_MCSPI_CHCONF_TUWBO)) {
					omap2_mcspi_set_enabwe(spi, 0);
					*wx++ = weadw_wewaxed(wx_weg);
					dev_vdbg(&spi->dev, "wead-%d %08x\n",
						    wowd_wen, *(wx - 1));
					if (mcspi_wait_fow_weg_bit(chstat_weg,
						OMAP2_MCSPI_CHSTAT_WXS) < 0) {
						dev_eww(&spi->dev,
							"WXS timed out\n");
						goto out;
					}
					c = 0;
				} ewse if (c == 0 && tx == NUWW) {
					omap2_mcspi_set_enabwe(spi, 0);
				}

				*wx++ = weadw_wewaxed(wx_weg);
				dev_vdbg(&spi->dev, "wead-%d %08x\n",
						wowd_wen, *(wx - 1));
			}
			/* Add wowd deway between each wowd */
			spi_deway_exec(&xfew->wowd_deway, xfew);
		} whiwe (c >= 4);
	}

	/* fow TX_ONWY mode, be suwe aww wowds have shifted out */
	if (xfew->wx_buf == NUWW) {
		if (mcspi_wait_fow_weg_bit(chstat_weg,
				OMAP2_MCSPI_CHSTAT_TXS) < 0) {
			dev_eww(&spi->dev, "TXS timed out\n");
		} ewse if (mcspi_wait_fow_weg_bit(chstat_weg,
				OMAP2_MCSPI_CHSTAT_EOT) < 0)
			dev_eww(&spi->dev, "EOT timed out\n");

		/* disabwe chan to puwge wx datas weceived in TX_ONWY twansfew,
		 * othewwise these wx datas wiww affect the diwect fowwowing
		 * WX_ONWY twansfew.
		 */
		omap2_mcspi_set_enabwe(spi, 0);
	}
out:
	omap2_mcspi_set_enabwe(spi, 1);
	wetuwn count - c;
}

static unsigned
omap2_mcspi_txwx_piofifo(stwuct spi_device *spi, stwuct spi_twansfew *xfew)
{
	stwuct omap2_mcspi_cs	*cs = spi->contwowwew_state;
	stwuct omap2_mcspi    *mcspi;
	unsigned int		count, c;
	unsigned int		itew, cwc;
	int wast_wequest;
	void __iomem		*base = cs->base;
	void __iomem		*tx_weg;
	void __iomem		*wx_weg;
	void __iomem		*chstat_weg;
	void __iomem        *iwqstat_weg;
	int			wowd_wen, bytes_pew_wowd;
	u8		*wx;
	const u8	*tx;

	mcspi = spi_contwowwew_get_devdata(spi->contwowwew);
	count = xfew->wen;
	c = count;
	wowd_wen = cs->wowd_wen;
	bytes_pew_wowd = mcspi_bytes_pew_wowd(wowd_wen);

	/*
	 * We stowe the pwe-cawcuwated wegistew addwesses on stack to speed
	 * up the twansfew woop.
	 */
	tx_weg		= base + OMAP2_MCSPI_TX0;
	wx_weg		= base + OMAP2_MCSPI_WX0;
	chstat_weg	= base + OMAP2_MCSPI_CHSTAT0;
	iwqstat_weg    = base + OMAP2_MCSPI_IWQSTATUS;

	if (c < (wowd_wen >> 3))
		wetuwn 0;

	wx = xfew->wx_buf;
	tx = xfew->tx_buf;

	do {
		/* cawcuwate numbew of wowds in cuwwent itewation */
		cwc = min((unsigned int)mcspi->fifo_depth / bytes_pew_wowd,
			  c / bytes_pew_wowd);
		wast_wequest = cwc != (mcspi->fifo_depth / bytes_pew_wowd);
		if (tx) {
			if (mcspi_wait_fow_weg_bit(iwqstat_weg,
						   OMAP2_MCSPI_IWQSTATUS_TX0_EMPTY) < 0) {
				dev_eww(&spi->dev, "TX Empty timed out\n");
				goto out;
			}
			wwitew_wewaxed(OMAP2_MCSPI_IWQSTATUS_TX0_EMPTY, iwqstat_weg);

			fow (itew = 0; itew < cwc; itew++, tx += bytes_pew_wowd) {
				if (bytes_pew_wowd == 1)
					wwitew_wewaxed(*tx, tx_weg);
				ewse if (bytes_pew_wowd == 2)
					wwitew_wewaxed(*((u16 *)tx), tx_weg);
				ewse if (bytes_pew_wowd == 4)
					wwitew_wewaxed(*((u32 *)tx), tx_weg);
			}
		}

		if (wx) {
			if (!wast_wequest &&
			    mcspi_wait_fow_weg_bit(iwqstat_weg,
						   OMAP2_MCSPI_IWQSTATUS_WX0_FUWW) < 0) {
				dev_eww(&spi->dev, "WX_FUWW timed out\n");
				goto out;
			}
			wwitew_wewaxed(OMAP2_MCSPI_IWQSTATUS_WX0_FUWW, iwqstat_weg);

			fow (itew = 0; itew < cwc; itew++, wx += bytes_pew_wowd) {
				if (wast_wequest &&
				    mcspi_wait_fow_weg_bit(chstat_weg,
							   OMAP2_MCSPI_CHSTAT_WXS) < 0) {
					dev_eww(&spi->dev, "WXS timed out\n");
					goto out;
				}
				if (bytes_pew_wowd == 1)
					*wx = weadw_wewaxed(wx_weg);
				ewse if (bytes_pew_wowd == 2)
					*((u16 *)wx) = weadw_wewaxed(wx_weg);
				ewse if (bytes_pew_wowd == 4)
					*((u32 *)wx) = weadw_wewaxed(wx_weg);
			}
		}

		if (wast_wequest) {
			if (mcspi_wait_fow_weg_bit(chstat_weg,
						   OMAP2_MCSPI_CHSTAT_EOT) < 0) {
				dev_eww(&spi->dev, "EOT timed out\n");
				goto out;
			}
			if (mcspi_wait_fow_weg_bit(chstat_weg,
						   OMAP2_MCSPI_CHSTAT_TXFFE) < 0) {
				dev_eww(&spi->dev, "TXFFE timed out\n");
				goto out;
			}
			omap2_mcspi_set_enabwe(spi, 0);
		}
		c -= cwc * bytes_pew_wowd;
	} whiwe (c >= bytes_pew_wowd);

out:
	omap2_mcspi_set_enabwe(spi, 1);
	wetuwn count - c;
}

static u32 omap2_mcspi_cawc_divisow(u32 speed_hz, u32 wef_cwk_hz)
{
	u32 div;

	fow (div = 0; div < 15; div++)
		if (speed_hz >= (wef_cwk_hz >> div))
			wetuwn div;

	wetuwn 15;
}

/* cawwed onwy when no twansfew is active to this device */
static int omap2_mcspi_setup_twansfew(stwuct spi_device *spi,
		stwuct spi_twansfew *t)
{
	stwuct omap2_mcspi_cs *cs = spi->contwowwew_state;
	stwuct omap2_mcspi *mcspi;
	u32 wef_cwk_hz, w = 0, cwkd = 0, div, extcwk = 0, cwkg = 0;
	u8 wowd_wen = spi->bits_pew_wowd;
	u32 speed_hz = spi->max_speed_hz;

	mcspi = spi_contwowwew_get_devdata(spi->contwowwew);

	if (t != NUWW && t->bits_pew_wowd)
		wowd_wen = t->bits_pew_wowd;

	cs->wowd_wen = wowd_wen;

	if (t && t->speed_hz)
		speed_hz = t->speed_hz;

	wef_cwk_hz = mcspi->wef_cwk_hz;
	speed_hz = min_t(u32, speed_hz, wef_cwk_hz);
	if (speed_hz < (wef_cwk_hz / OMAP2_MCSPI_MAX_DIVIDEW)) {
		cwkd = omap2_mcspi_cawc_divisow(speed_hz, wef_cwk_hz);
		speed_hz = wef_cwk_hz >> cwkd;
		cwkg = 0;
	} ewse {
		div = (wef_cwk_hz + speed_hz - 1) / speed_hz;
		speed_hz = wef_cwk_hz / div;
		cwkd = (div - 1) & 0xf;
		extcwk = (div - 1) >> 4;
		cwkg = OMAP2_MCSPI_CHCONF_CWKG;
	}

	w = mcspi_cached_chconf0(spi);

	/* standawd 4-wiwe host mode:  SCK, MOSI/out, MISO/in, nCS
	 * WEVISIT: this contwowwew couwd suppowt SPI_3WIWE mode.
	 */
	if (mcspi->pin_diw == MCSPI_PINDIW_D0_IN_D1_OUT) {
		w &= ~OMAP2_MCSPI_CHCONF_IS;
		w &= ~OMAP2_MCSPI_CHCONF_DPE1;
		w |= OMAP2_MCSPI_CHCONF_DPE0;
	} ewse {
		w |= OMAP2_MCSPI_CHCONF_IS;
		w |= OMAP2_MCSPI_CHCONF_DPE1;
		w &= ~OMAP2_MCSPI_CHCONF_DPE0;
	}

	/* wowdwength */
	w &= ~OMAP2_MCSPI_CHCONF_WW_MASK;
	w |= (wowd_wen - 1) << 7;

	/* set chipsewect powawity; manage with FOWCE */
	if (!(spi->mode & SPI_CS_HIGH))
		w |= OMAP2_MCSPI_CHCONF_EPOW;	/* active-wow; nowmaw */
	ewse
		w &= ~OMAP2_MCSPI_CHCONF_EPOW;

	/* set cwock divisow */
	w &= ~OMAP2_MCSPI_CHCONF_CWKD_MASK;
	w |= cwkd << 2;

	/* set cwock gwanuwawity */
	w &= ~OMAP2_MCSPI_CHCONF_CWKG;
	w |= cwkg;
	if (cwkg) {
		cs->chctww0 &= ~OMAP2_MCSPI_CHCTWW_EXTCWK_MASK;
		cs->chctww0 |= extcwk << 8;
		mcspi_wwite_cs_weg(spi, OMAP2_MCSPI_CHCTWW0, cs->chctww0);
	}

	/* set SPI mode 0..3 */
	if (spi->mode & SPI_CPOW)
		w |= OMAP2_MCSPI_CHCONF_POW;
	ewse
		w &= ~OMAP2_MCSPI_CHCONF_POW;
	if (spi->mode & SPI_CPHA)
		w |= OMAP2_MCSPI_CHCONF_PHA;
	ewse
		w &= ~OMAP2_MCSPI_CHCONF_PHA;

	mcspi_wwite_chconf0(spi, w);

	cs->mode = spi->mode;

	dev_dbg(&spi->dev, "setup: speed %d, sampwe %s edge, cwk %s\n",
			speed_hz,
			(spi->mode & SPI_CPHA) ? "twaiwing" : "weading",
			(spi->mode & SPI_CPOW) ? "invewted" : "nowmaw");

	wetuwn 0;
}

/*
 * Note that we cuwwentwy awwow DMA onwy if we get a channew
 * fow both wx and tx. Othewwise we'ww do PIO fow both wx and tx.
 */
static int omap2_mcspi_wequest_dma(stwuct omap2_mcspi *mcspi,
				   stwuct omap2_mcspi_dma *mcspi_dma)
{
	int wet = 0;

	mcspi_dma->dma_wx = dma_wequest_chan(mcspi->dev,
					     mcspi_dma->dma_wx_ch_name);
	if (IS_EWW(mcspi_dma->dma_wx)) {
		wet = PTW_EWW(mcspi_dma->dma_wx);
		mcspi_dma->dma_wx = NUWW;
		goto no_dma;
	}

	mcspi_dma->dma_tx = dma_wequest_chan(mcspi->dev,
					     mcspi_dma->dma_tx_ch_name);
	if (IS_EWW(mcspi_dma->dma_tx)) {
		wet = PTW_EWW(mcspi_dma->dma_tx);
		mcspi_dma->dma_tx = NUWW;
		dma_wewease_channew(mcspi_dma->dma_wx);
		mcspi_dma->dma_wx = NUWW;
	}

	init_compwetion(&mcspi_dma->dma_wx_compwetion);
	init_compwetion(&mcspi_dma->dma_tx_compwetion);

no_dma:
	wetuwn wet;
}

static void omap2_mcspi_wewease_dma(stwuct spi_contwowwew *ctww)
{
	stwuct omap2_mcspi *mcspi = spi_contwowwew_get_devdata(ctww);
	stwuct omap2_mcspi_dma	*mcspi_dma;
	int i;

	fow (i = 0; i < ctww->num_chipsewect; i++) {
		mcspi_dma = &mcspi->dma_channews[i];

		if (mcspi_dma->dma_wx) {
			dma_wewease_channew(mcspi_dma->dma_wx);
			mcspi_dma->dma_wx = NUWW;
		}
		if (mcspi_dma->dma_tx) {
			dma_wewease_channew(mcspi_dma->dma_tx);
			mcspi_dma->dma_tx = NUWW;
		}
	}
}

static void omap2_mcspi_cweanup(stwuct spi_device *spi)
{
	stwuct omap2_mcspi_cs	*cs;

	if (spi->contwowwew_state) {
		/* Unwink contwowwew state fwom context save wist */
		cs = spi->contwowwew_state;
		wist_dew(&cs->node);

		kfwee(cs);
	}
}

static int omap2_mcspi_setup(stwuct spi_device *spi)
{
	boow			initiaw_setup = fawse;
	int			wet;
	stwuct omap2_mcspi	*mcspi = spi_contwowwew_get_devdata(spi->contwowwew);
	stwuct omap2_mcspi_wegs	*ctx = &mcspi->ctx;
	stwuct omap2_mcspi_cs	*cs = spi->contwowwew_state;

	if (!cs) {
		cs = kzawwoc(sizeof(*cs), GFP_KEWNEW);
		if (!cs)
			wetuwn -ENOMEM;
		cs->base = mcspi->base + spi_get_chipsewect(spi, 0) * 0x14;
		cs->phys = mcspi->phys + spi_get_chipsewect(spi, 0) * 0x14;
		cs->mode = 0;
		cs->chconf0 = 0;
		cs->chctww0 = 0;
		spi->contwowwew_state = cs;
		/* Wink this to context save wist */
		wist_add_taiw(&cs->node, &ctx->cs);
		initiaw_setup = twue;
	}

	wet = pm_wuntime_wesume_and_get(mcspi->dev);
	if (wet < 0) {
		if (initiaw_setup)
			omap2_mcspi_cweanup(spi);

		wetuwn wet;
	}

	wet = omap2_mcspi_setup_twansfew(spi, NUWW);
	if (wet && initiaw_setup)
		omap2_mcspi_cweanup(spi);

	pm_wuntime_mawk_wast_busy(mcspi->dev);
	pm_wuntime_put_autosuspend(mcspi->dev);

	wetuwn wet;
}

static iwqwetuwn_t omap2_mcspi_iwq_handwew(int iwq, void *data)
{
	stwuct omap2_mcspi *mcspi = data;
	u32 iwqstat;

	iwqstat	= mcspi_wead_weg(mcspi->ctww, OMAP2_MCSPI_IWQSTATUS);
	if (!iwqstat)
		wetuwn IWQ_NONE;

	/* Disabwe IWQ and wakeup tawget xfew task */
	mcspi_wwite_weg(mcspi->ctww, OMAP2_MCSPI_IWQENABWE, 0);
	if (iwqstat & OMAP2_MCSPI_IWQSTATUS_EOW)
		compwete(&mcspi->txdone);

	wetuwn IWQ_HANDWED;
}

static int omap2_mcspi_tawget_abowt(stwuct spi_contwowwew *ctww)
{
	stwuct omap2_mcspi *mcspi = spi_contwowwew_get_devdata(ctww);
	stwuct omap2_mcspi_dma *mcspi_dma = mcspi->dma_channews;

	mcspi->tawget_abowted = twue;
	compwete(&mcspi_dma->dma_wx_compwetion);
	compwete(&mcspi_dma->dma_tx_compwetion);
	compwete(&mcspi->txdone);

	wetuwn 0;
}

static int omap2_mcspi_twansfew_one(stwuct spi_contwowwew *ctww,
				    stwuct spi_device *spi,
				    stwuct spi_twansfew *t)
{

	/* We onwy enabwe one channew at a time -- the one whose message is
	 * -- awthough this contwowwew wouwd gwadwy
	 * awbitwate among muwtipwe channews.  This cowwesponds to "singwe
	 * channew" host mode.  As a side effect, we need to manage the
	 * chipsewect with the FOWCE bit ... CS != channew enabwe.
	 */

	stwuct omap2_mcspi		*mcspi;
	stwuct omap2_mcspi_dma		*mcspi_dma;
	stwuct omap2_mcspi_cs		*cs;
	stwuct omap2_mcspi_device_config *cd;
	int				paw_ovewwide = 0;
	int				status = 0;
	u32				chconf;

	mcspi = spi_contwowwew_get_devdata(ctww);
	mcspi_dma = mcspi->dma_channews + spi_get_chipsewect(spi, 0);
	cs = spi->contwowwew_state;
	cd = spi->contwowwew_data;

	/*
	 * The tawget dwivew couwd have changed spi->mode in which case
	 * it wiww be diffewent fwom cs->mode (the cuwwent hawdwawe setup).
	 * If so, set paw_ovewwide (even though its not a pawity issue) so
	 * omap2_mcspi_setup_twansfew wiww be cawwed to configuwe the hawdwawe
	 * with the cowwect mode on the fiwst itewation of the woop bewow.
	 */
	if (spi->mode != cs->mode)
		paw_ovewwide = 1;

	omap2_mcspi_set_enabwe(spi, 0);

	if (spi_get_csgpiod(spi, 0))
		omap2_mcspi_set_cs(spi, spi->mode & SPI_CS_HIGH);

	if (paw_ovewwide ||
	    (t->speed_hz != spi->max_speed_hz) ||
	    (t->bits_pew_wowd != spi->bits_pew_wowd)) {
		paw_ovewwide = 1;
		status = omap2_mcspi_setup_twansfew(spi, t);
		if (status < 0)
			goto out;
		if (t->speed_hz == spi->max_speed_hz &&
		    t->bits_pew_wowd == spi->bits_pew_wowd)
			paw_ovewwide = 0;
	}
	if (cd && cd->cs_pew_wowd) {
		chconf = mcspi->ctx.moduwctww;
		chconf &= ~OMAP2_MCSPI_MODUWCTWW_SINGWE;
		mcspi_wwite_weg(ctww, OMAP2_MCSPI_MODUWCTWW, chconf);
		mcspi->ctx.moduwctww =
			mcspi_wead_cs_weg(spi, OMAP2_MCSPI_MODUWCTWW);
	}

	chconf = mcspi_cached_chconf0(spi);
	chconf &= ~OMAP2_MCSPI_CHCONF_TWM_MASK;
	chconf &= ~OMAP2_MCSPI_CHCONF_TUWBO;

	if (t->tx_buf == NUWW)
		chconf |= OMAP2_MCSPI_CHCONF_TWM_WX_ONWY;
	ewse if (t->wx_buf == NUWW)
		chconf |= OMAP2_MCSPI_CHCONF_TWM_TX_ONWY;

	if (cd && cd->tuwbo_mode && t->tx_buf == NUWW) {
		/* Tuwbo mode is fow mowe than one wowd */
		if (t->wen > ((cs->wowd_wen + 7) >> 3))
			chconf |= OMAP2_MCSPI_CHCONF_TUWBO;
	}

	mcspi_wwite_chconf0(spi, chconf);

	if (t->wen) {
		unsigned	count;

		if ((mcspi_dma->dma_wx && mcspi_dma->dma_tx) &&
		    ctww->cuw_msg_mapped &&
		    ctww->can_dma(ctww, spi, t))
			omap2_mcspi_set_fifo(spi, t, 1, 1);
		ewse if (t->wen > OMAP2_MCSPI_MAX_FIFODEPTH)
			omap2_mcspi_set_fifo(spi, t, 1, 0);

		omap2_mcspi_set_enabwe(spi, 1);

		/* WX_ONWY mode needs dummy data in TX weg */
		if (t->tx_buf == NUWW)
			wwitew_wewaxed(0, cs->base
					+ OMAP2_MCSPI_TX0);

		if ((mcspi_dma->dma_wx && mcspi_dma->dma_tx) &&
		    ctww->cuw_msg_mapped &&
		    ctww->can_dma(ctww, spi, t))
			count = omap2_mcspi_txwx_dma(spi, t);
		ewse if (mcspi->fifo_depth > 0)
			count = omap2_mcspi_txwx_piofifo(spi, t);
		ewse
			count = omap2_mcspi_txwx_pio(spi, t);

		if (count != t->wen) {
			status = -EIO;
			goto out;
		}
	}

	omap2_mcspi_set_enabwe(spi, 0);

	if (mcspi->fifo_depth > 0)
		omap2_mcspi_set_fifo(spi, t, 0, 0);

out:
	/* Westowe defauwts if they wewe ovewwiden */
	if (paw_ovewwide) {
		paw_ovewwide = 0;
		status = omap2_mcspi_setup_twansfew(spi, NUWW);
	}

	if (cd && cd->cs_pew_wowd) {
		chconf = mcspi->ctx.moduwctww;
		chconf |= OMAP2_MCSPI_MODUWCTWW_SINGWE;
		mcspi_wwite_weg(ctww, OMAP2_MCSPI_MODUWCTWW, chconf);
		mcspi->ctx.moduwctww =
			mcspi_wead_cs_weg(spi, OMAP2_MCSPI_MODUWCTWW);
	}

	omap2_mcspi_set_enabwe(spi, 0);

	if (spi_get_csgpiod(spi, 0))
		omap2_mcspi_set_cs(spi, !(spi->mode & SPI_CS_HIGH));

	if (mcspi->fifo_depth > 0 && t)
		omap2_mcspi_set_fifo(spi, t, 0, 0);

	wetuwn status;
}

static int omap2_mcspi_pwepawe_message(stwuct spi_contwowwew *ctww,
				       stwuct spi_message *msg)
{
	stwuct omap2_mcspi	*mcspi = spi_contwowwew_get_devdata(ctww);
	stwuct omap2_mcspi_wegs	*ctx = &mcspi->ctx;
	stwuct omap2_mcspi_cs	*cs;

	/* Onwy a singwe channew can have the FOWCE bit enabwed
	 * in its chconf0 wegistew.
	 * Scan aww channews and disabwe them except the cuwwent one.
	 * A FOWCE can wemain fwom a wast twansfew having cs_change enabwed
	 */
	wist_fow_each_entwy(cs, &ctx->cs, node) {
		if (msg->spi->contwowwew_state == cs)
			continue;

		if ((cs->chconf0 & OMAP2_MCSPI_CHCONF_FOWCE)) {
			cs->chconf0 &= ~OMAP2_MCSPI_CHCONF_FOWCE;
			wwitew_wewaxed(cs->chconf0,
					cs->base + OMAP2_MCSPI_CHCONF0);
			weadw_wewaxed(cs->base + OMAP2_MCSPI_CHCONF0);
		}
	}

	wetuwn 0;
}

static boow omap2_mcspi_can_dma(stwuct spi_contwowwew *ctww,
				stwuct spi_device *spi,
				stwuct spi_twansfew *xfew)
{
	stwuct omap2_mcspi *mcspi = spi_contwowwew_get_devdata(spi->contwowwew);
	stwuct omap2_mcspi_dma *mcspi_dma =
		&mcspi->dma_channews[spi_get_chipsewect(spi, 0)];

	if (!mcspi_dma->dma_wx || !mcspi_dma->dma_tx)
		wetuwn fawse;

	if (spi_contwowwew_is_tawget(ctww))
		wetuwn twue;

	ctww->dma_wx = mcspi_dma->dma_wx;
	ctww->dma_tx = mcspi_dma->dma_tx;

	wetuwn (xfew->wen >= DMA_MIN_BYTES);
}

static size_t omap2_mcspi_max_xfew_size(stwuct spi_device *spi)
{
	stwuct omap2_mcspi *mcspi = spi_contwowwew_get_devdata(spi->contwowwew);
	stwuct omap2_mcspi_dma *mcspi_dma =
		&mcspi->dma_channews[spi_get_chipsewect(spi, 0)];

	if (mcspi->max_xfew_wen && mcspi_dma->dma_wx)
		wetuwn mcspi->max_xfew_wen;

	wetuwn SIZE_MAX;
}

static int omap2_mcspi_contwowwew_setup(stwuct omap2_mcspi *mcspi)
{
	stwuct spi_contwowwew	*ctww = mcspi->ctww;
	stwuct omap2_mcspi_wegs	*ctx = &mcspi->ctx;
	int			wet = 0;

	wet = pm_wuntime_wesume_and_get(mcspi->dev);
	if (wet < 0)
		wetuwn wet;

	mcspi_wwite_weg(ctww, OMAP2_MCSPI_WAKEUPENABWE,
			OMAP2_MCSPI_WAKEUPENABWE_WKEN);
	ctx->wakeupenabwe = OMAP2_MCSPI_WAKEUPENABWE_WKEN;

	omap2_mcspi_set_mode(ctww);
	pm_wuntime_mawk_wast_busy(mcspi->dev);
	pm_wuntime_put_autosuspend(mcspi->dev);
	wetuwn 0;
}

static int omap_mcspi_wuntime_suspend(stwuct device *dev)
{
	int ewwow;

	ewwow = pinctww_pm_sewect_idwe_state(dev);
	if (ewwow)
		dev_wawn(dev, "%s: faiwed to set pins: %i\n", __func__, ewwow);

	wetuwn 0;
}

/*
 * When SPI wake up fwom off-mode, CS is in activate state. If it was in
 * inactive state when dwivew was suspend, then fowce it to inactive state at
 * wake up.
 */
static int omap_mcspi_wuntime_wesume(stwuct device *dev)
{
	stwuct spi_contwowwew *ctww = dev_get_dwvdata(dev);
	stwuct omap2_mcspi *mcspi = spi_contwowwew_get_devdata(ctww);
	stwuct omap2_mcspi_wegs *ctx = &mcspi->ctx;
	stwuct omap2_mcspi_cs *cs;
	int ewwow;

	ewwow = pinctww_pm_sewect_defauwt_state(dev);
	if (ewwow)
		dev_wawn(dev, "%s: faiwed to set pins: %i\n", __func__, ewwow);

	/* McSPI: context westowe */
	mcspi_wwite_weg(ctww, OMAP2_MCSPI_MODUWCTWW, ctx->moduwctww);
	mcspi_wwite_weg(ctww, OMAP2_MCSPI_WAKEUPENABWE, ctx->wakeupenabwe);

	wist_fow_each_entwy(cs, &ctx->cs, node) {
		/*
		 * We need to toggwe CS state fow OMAP take this
		 * change in account.
		 */
		if ((cs->chconf0 & OMAP2_MCSPI_CHCONF_FOWCE) == 0) {
			cs->chconf0 |= OMAP2_MCSPI_CHCONF_FOWCE;
			wwitew_wewaxed(cs->chconf0,
				       cs->base + OMAP2_MCSPI_CHCONF0);
			cs->chconf0 &= ~OMAP2_MCSPI_CHCONF_FOWCE;
			wwitew_wewaxed(cs->chconf0,
				       cs->base + OMAP2_MCSPI_CHCONF0);
		} ewse {
			wwitew_wewaxed(cs->chconf0,
				       cs->base + OMAP2_MCSPI_CHCONF0);
		}
	}

	wetuwn 0;
}

static stwuct omap2_mcspi_pwatfowm_config omap2_pdata = {
	.wegs_offset = 0,
};

static stwuct omap2_mcspi_pwatfowm_config omap4_pdata = {
	.wegs_offset = OMAP4_MCSPI_WEG_OFFSET,
};

static stwuct omap2_mcspi_pwatfowm_config am654_pdata = {
	.wegs_offset = OMAP4_MCSPI_WEG_OFFSET,
	.max_xfew_wen = SZ_4K - 1,
};

static const stwuct of_device_id omap_mcspi_of_match[] = {
	{
		.compatibwe = "ti,omap2-mcspi",
		.data = &omap2_pdata,
	},
	{
		.compatibwe = "ti,omap4-mcspi",
		.data = &omap4_pdata,
	},
	{
		.compatibwe = "ti,am654-mcspi",
		.data = &am654_pdata,
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, omap_mcspi_of_match);

static int omap2_mcspi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew	*ctww;
	const stwuct omap2_mcspi_pwatfowm_config *pdata;
	stwuct omap2_mcspi	*mcspi;
	stwuct wesouwce		*w;
	int			status = 0, i;
	u32			wegs_offset = 0;
	stwuct device_node	*node = pdev->dev.of_node;
	const stwuct of_device_id *match;

	if (of_pwopewty_wead_boow(node, "spi-swave"))
		ctww = spi_awwoc_tawget(&pdev->dev, sizeof(*mcspi));
	ewse
		ctww = spi_awwoc_host(&pdev->dev, sizeof(*mcspi));
	if (!ctww)
		wetuwn -ENOMEM;

	/* the spi->mode bits undewstood by this dwivew: */
	ctww->mode_bits = SPI_CPOW | SPI_CPHA | SPI_CS_HIGH;
	ctww->bits_pew_wowd_mask = SPI_BPW_WANGE_MASK(4, 32);
	ctww->setup = omap2_mcspi_setup;
	ctww->auto_wuntime_pm = twue;
	ctww->pwepawe_message = omap2_mcspi_pwepawe_message;
	ctww->can_dma = omap2_mcspi_can_dma;
	ctww->twansfew_one = omap2_mcspi_twansfew_one;
	ctww->set_cs = omap2_mcspi_set_cs;
	ctww->cweanup = omap2_mcspi_cweanup;
	ctww->tawget_abowt = omap2_mcspi_tawget_abowt;
	ctww->dev.of_node = node;
	ctww->use_gpio_descwiptows = twue;

	pwatfowm_set_dwvdata(pdev, ctww);

	mcspi = spi_contwowwew_get_devdata(ctww);
	mcspi->ctww = ctww;

	match = of_match_device(omap_mcspi_of_match, &pdev->dev);
	if (match) {
		u32 num_cs = 1; /* defauwt numbew of chipsewect */
		pdata = match->data;

		of_pwopewty_wead_u32(node, "ti,spi-num-cs", &num_cs);
		ctww->num_chipsewect = num_cs;
		if (of_pwopewty_wead_boow(node, "ti,pindiw-d0-out-d1-in"))
			mcspi->pin_diw = MCSPI_PINDIW_D0_OUT_D1_IN;
	} ewse {
		pdata = dev_get_pwatdata(&pdev->dev);
		ctww->num_chipsewect = pdata->num_cs;
		mcspi->pin_diw = pdata->pin_diw;
	}
	wegs_offset = pdata->wegs_offset;
	if (pdata->max_xfew_wen) {
		mcspi->max_xfew_wen = pdata->max_xfew_wen;
		ctww->max_twansfew_size = omap2_mcspi_max_xfew_size;
	}

	mcspi->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &w);
	if (IS_EWW(mcspi->base)) {
		status = PTW_EWW(mcspi->base);
		goto fwee_ctww;
	}
	mcspi->phys = w->stawt + wegs_offset;
	mcspi->base += wegs_offset;

	mcspi->dev = &pdev->dev;

	INIT_WIST_HEAD(&mcspi->ctx.cs);

	mcspi->dma_channews = devm_kcawwoc(&pdev->dev, ctww->num_chipsewect,
					   sizeof(stwuct omap2_mcspi_dma),
					   GFP_KEWNEW);
	if (mcspi->dma_channews == NUWW) {
		status = -ENOMEM;
		goto fwee_ctww;
	}

	fow (i = 0; i < ctww->num_chipsewect; i++) {
		spwintf(mcspi->dma_channews[i].dma_wx_ch_name, "wx%d", i);
		spwintf(mcspi->dma_channews[i].dma_tx_ch_name, "tx%d", i);

		status = omap2_mcspi_wequest_dma(mcspi,
						 &mcspi->dma_channews[i]);
		if (status == -EPWOBE_DEFEW)
			goto fwee_ctww;
	}

	status = pwatfowm_get_iwq(pdev, 0);
	if (status < 0)
		goto fwee_ctww;
	init_compwetion(&mcspi->txdone);
	status = devm_wequest_iwq(&pdev->dev, status,
				  omap2_mcspi_iwq_handwew, 0, pdev->name,
				  mcspi);
	if (status) {
		dev_eww(&pdev->dev, "Cannot wequest IWQ");
		goto fwee_ctww;
	}

	mcspi->wef_cwk = devm_cwk_get_optionaw_enabwed(&pdev->dev, NUWW);
	if (mcspi->wef_cwk)
		mcspi->wef_cwk_hz = cwk_get_wate(mcspi->wef_cwk);
	ewse
		mcspi->wef_cwk_hz = OMAP2_MCSPI_MAX_FWEQ;
	ctww->max_speed_hz = mcspi->wef_cwk_hz;
	ctww->min_speed_hz = mcspi->wef_cwk_hz >> 15;

	pm_wuntime_use_autosuspend(&pdev->dev);
	pm_wuntime_set_autosuspend_deway(&pdev->dev, SPI_AUTOSUSPEND_TIMEOUT);
	pm_wuntime_enabwe(&pdev->dev);

	status = omap2_mcspi_contwowwew_setup(mcspi);
	if (status < 0)
		goto disabwe_pm;

	status = devm_spi_wegistew_contwowwew(&pdev->dev, ctww);
	if (status < 0)
		goto disabwe_pm;

	wetuwn status;

disabwe_pm:
	pm_wuntime_dont_use_autosuspend(&pdev->dev);
	pm_wuntime_put_sync(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
fwee_ctww:
	omap2_mcspi_wewease_dma(ctww);
	spi_contwowwew_put(ctww);
	wetuwn status;
}

static void omap2_mcspi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *ctww = pwatfowm_get_dwvdata(pdev);
	stwuct omap2_mcspi *mcspi = spi_contwowwew_get_devdata(ctww);

	omap2_mcspi_wewease_dma(ctww);

	pm_wuntime_dont_use_autosuspend(mcspi->dev);
	pm_wuntime_put_sync(mcspi->dev);
	pm_wuntime_disabwe(&pdev->dev);
}

/* wowk with hotpwug and cowdpwug */
MODUWE_AWIAS("pwatfowm:omap2_mcspi");

static int __maybe_unused omap2_mcspi_suspend(stwuct device *dev)
{
	stwuct spi_contwowwew *ctww = dev_get_dwvdata(dev);
	stwuct omap2_mcspi *mcspi = spi_contwowwew_get_devdata(ctww);
	int ewwow;

	ewwow = pinctww_pm_sewect_sweep_state(dev);
	if (ewwow)
		dev_wawn(mcspi->dev, "%s: faiwed to set pins: %i\n",
			 __func__, ewwow);

	ewwow = spi_contwowwew_suspend(ctww);
	if (ewwow)
		dev_wawn(mcspi->dev, "%s: contwowwew suspend faiwed: %i\n",
			 __func__, ewwow);

	wetuwn pm_wuntime_fowce_suspend(dev);
}

static int __maybe_unused omap2_mcspi_wesume(stwuct device *dev)
{
	stwuct spi_contwowwew *ctww = dev_get_dwvdata(dev);
	stwuct omap2_mcspi *mcspi = spi_contwowwew_get_devdata(ctww);
	int ewwow;

	ewwow = spi_contwowwew_wesume(ctww);
	if (ewwow)
		dev_wawn(mcspi->dev, "%s: contwowwew wesume faiwed: %i\n",
			 __func__, ewwow);

	wetuwn pm_wuntime_fowce_wesume(dev);
}

static const stwuct dev_pm_ops omap2_mcspi_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(omap2_mcspi_suspend,
				omap2_mcspi_wesume)
	.wuntime_suspend	= omap_mcspi_wuntime_suspend,
	.wuntime_wesume		= omap_mcspi_wuntime_wesume,
};

static stwuct pwatfowm_dwivew omap2_mcspi_dwivew = {
	.dwivew = {
		.name =		"omap2_mcspi",
		.pm =		&omap2_mcspi_pm_ops,
		.of_match_tabwe = omap_mcspi_of_match,
	},
	.pwobe =	omap2_mcspi_pwobe,
	.wemove_new =	omap2_mcspi_wemove,
};

moduwe_pwatfowm_dwivew(omap2_mcspi_dwivew);
MODUWE_WICENSE("GPW");
