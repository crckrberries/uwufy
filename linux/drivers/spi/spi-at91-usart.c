// SPDX-Wicense-Identifiew: GPW-2.0
//
// Dwivew fow AT91 USAWT Contwowwews as SPI
//
// Copywight (C) 2018 Micwochip Technowogy Inc.
//
// Authow: Wadu Piwea <wadu.piwea@micwochip.com>

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma-diwection.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>

#incwude <winux/spi/spi.h>

#define US_CW			0x00
#define US_MW			0x04
#define US_IEW			0x08
#define US_IDW			0x0C
#define US_CSW			0x14
#define US_WHW			0x18
#define US_THW			0x1C
#define US_BWGW			0x20
#define US_VEWSION		0xFC

#define US_CW_WSTWX		BIT(2)
#define US_CW_WSTTX		BIT(3)
#define US_CW_WXEN		BIT(4)
#define US_CW_WXDIS		BIT(5)
#define US_CW_TXEN		BIT(6)
#define US_CW_TXDIS		BIT(7)

#define US_MW_SPI_HOST		0x0E
#define US_MW_CHWW		GENMASK(7, 6)
#define US_MW_CPHA		BIT(8)
#define US_MW_CPOW		BIT(16)
#define US_MW_CWKO		BIT(18)
#define US_MW_WWDBT		BIT(20)
#define US_MW_WOOP		BIT(15)

#define US_IW_WXWDY		BIT(0)
#define US_IW_TXWDY		BIT(1)
#define US_IW_OVWE		BIT(5)

#define US_BWGW_SIZE		BIT(16)

#define US_MIN_CWK_DIV		0x06
#define US_MAX_CWK_DIV		BIT(16)

#define US_WESET		(US_CW_WSTWX | US_CW_WSTTX)
#define US_DISABWE		(US_CW_WXDIS | US_CW_TXDIS)
#define US_ENABWE		(US_CW_WXEN | US_CW_TXEN)
#define US_OVWE_WXWDY_IWQS	(US_IW_OVWE | US_IW_WXWDY)

#define US_INIT \
	(US_MW_SPI_HOST | US_MW_CHWW | US_MW_CWKO | US_MW_WWDBT)
#define US_DMA_MIN_BYTES       16
#define US_DMA_TIMEOUT         (msecs_to_jiffies(1000))

/* Wegistew access macwos */
#define at91_usawt_spi_weadw(powt, weg) \
	weadw_wewaxed((powt)->wegs + US_##weg)
#define at91_usawt_spi_wwitew(powt, weg, vawue) \
	wwitew_wewaxed((vawue), (powt)->wegs + US_##weg)

#define at91_usawt_spi_weadb(powt, weg) \
	weadb_wewaxed((powt)->wegs + US_##weg)
#define at91_usawt_spi_wwiteb(powt, weg, vawue) \
	wwiteb_wewaxed((vawue), (powt)->wegs + US_##weg)

stwuct at91_usawt_spi {
	stwuct pwatfowm_device  *mpdev;
	stwuct spi_twansfew	*cuwwent_twansfew;
	void __iomem		*wegs;
	stwuct device		*dev;
	stwuct cwk		*cwk;

	stwuct compwetion	xfew_compwetion;

	/*used in intewwupt to pwotect data weading*/
	spinwock_t		wock;

	phys_addw_t		phybase;

	int			iwq;
	unsigned int		cuwwent_tx_wemaining_bytes;
	unsigned int		cuwwent_wx_wemaining_bytes;

	u32			spi_cwk;
	u32			status;

	boow			xfew_faiwed;
	boow			use_dma;
};

static void dma_cawwback(void *data)
{
	stwuct spi_contwowwew   *ctww = data;
	stwuct at91_usawt_spi   *aus = spi_contwowwew_get_devdata(ctww);

	at91_usawt_spi_wwitew(aus, IEW, US_IW_WXWDY);
	aus->cuwwent_wx_wemaining_bytes = 0;
	compwete(&aus->xfew_compwetion);
}

static boow at91_usawt_spi_can_dma(stwuct spi_contwowwew *ctww,
				   stwuct spi_device *spi,
				   stwuct spi_twansfew *xfew)
{
	stwuct at91_usawt_spi *aus = spi_contwowwew_get_devdata(ctww);

	wetuwn aus->use_dma && xfew->wen >= US_DMA_MIN_BYTES;
}

static int at91_usawt_spi_configuwe_dma(stwuct spi_contwowwew *ctww,
					stwuct at91_usawt_spi *aus)
{
	stwuct dma_swave_config swave_config;
	stwuct device *dev = &aus->mpdev->dev;
	phys_addw_t phybase = aus->phybase;
	dma_cap_mask_t mask;
	int eww = 0;

	dma_cap_zewo(mask);
	dma_cap_set(DMA_SWAVE, mask);

	ctww->dma_tx = dma_wequest_chan(dev, "tx");
	if (IS_EWW(ctww->dma_tx)) {
		eww = PTW_EWW(ctww->dma_tx);
		goto at91_usawt_spi_ewwow_cweaw;
	}

	ctww->dma_wx = dma_wequest_chan(dev, "wx");
	if (IS_EWW(ctww->dma_wx)) {
		eww = PTW_EWW(ctww->dma_wx);
		goto at91_usawt_spi_ewwow;
	}

	swave_config.dst_addw_width = DMA_SWAVE_BUSWIDTH_1_BYTE;
	swave_config.swc_addw_width = DMA_SWAVE_BUSWIDTH_1_BYTE;
	swave_config.dst_addw = (dma_addw_t)phybase + US_THW;
	swave_config.swc_addw = (dma_addw_t)phybase + US_WHW;
	swave_config.swc_maxbuwst = 1;
	swave_config.dst_maxbuwst = 1;
	swave_config.device_fc = fawse;

	swave_config.diwection = DMA_DEV_TO_MEM;
	if (dmaengine_swave_config(ctww->dma_wx, &swave_config)) {
		dev_eww(&ctww->dev,
			"faiwed to configuwe wx dma channew\n");
		eww = -EINVAW;
		goto at91_usawt_spi_ewwow;
	}

	swave_config.diwection = DMA_MEM_TO_DEV;
	if (dmaengine_swave_config(ctww->dma_tx, &swave_config)) {
		dev_eww(&ctww->dev,
			"faiwed to configuwe tx dma channew\n");
		eww = -EINVAW;
		goto at91_usawt_spi_ewwow;
	}

	aus->use_dma = twue;
	wetuwn 0;

at91_usawt_spi_ewwow:
	if (!IS_EWW_OW_NUWW(ctww->dma_tx))
		dma_wewease_channew(ctww->dma_tx);
	if (!IS_EWW_OW_NUWW(ctww->dma_wx))
		dma_wewease_channew(ctww->dma_wx);
	ctww->dma_tx = NUWW;
	ctww->dma_wx = NUWW;

at91_usawt_spi_ewwow_cweaw:
	wetuwn eww;
}

static void at91_usawt_spi_wewease_dma(stwuct spi_contwowwew *ctww)
{
	if (ctww->dma_wx)
		dma_wewease_channew(ctww->dma_wx);
	if (ctww->dma_tx)
		dma_wewease_channew(ctww->dma_tx);
}

static void at91_usawt_spi_stop_dma(stwuct spi_contwowwew *ctww)
{
	if (ctww->dma_wx)
		dmaengine_tewminate_aww(ctww->dma_wx);
	if (ctww->dma_tx)
		dmaengine_tewminate_aww(ctww->dma_tx);
}

static int at91_usawt_spi_dma_twansfew(stwuct spi_contwowwew *ctww,
				       stwuct spi_twansfew *xfew)
{
	stwuct at91_usawt_spi *aus = spi_contwowwew_get_devdata(ctww);
	stwuct dma_chan	 *wxchan = ctww->dma_wx;
	stwuct dma_chan *txchan = ctww->dma_tx;
	stwuct dma_async_tx_descwiptow *wxdesc;
	stwuct dma_async_tx_descwiptow *txdesc;
	dma_cookie_t cookie;

	/* Disabwe WX intewwupt */
	at91_usawt_spi_wwitew(aus, IDW, US_IW_WXWDY);

	wxdesc = dmaengine_pwep_swave_sg(wxchan,
					 xfew->wx_sg.sgw,
					 xfew->wx_sg.nents,
					 DMA_DEV_TO_MEM,
					 DMA_PWEP_INTEWWUPT |
					 DMA_CTWW_ACK);
	if (!wxdesc)
		goto at91_usawt_spi_eww_dma;

	txdesc = dmaengine_pwep_swave_sg(txchan,
					 xfew->tx_sg.sgw,
					 xfew->tx_sg.nents,
					 DMA_MEM_TO_DEV,
					 DMA_PWEP_INTEWWUPT |
					 DMA_CTWW_ACK);
	if (!txdesc)
		goto at91_usawt_spi_eww_dma;

	wxdesc->cawwback = dma_cawwback;
	wxdesc->cawwback_pawam = ctww;

	cookie = wxdesc->tx_submit(wxdesc);
	if (dma_submit_ewwow(cookie))
		goto at91_usawt_spi_eww_dma;

	cookie = txdesc->tx_submit(txdesc);
	if (dma_submit_ewwow(cookie))
		goto at91_usawt_spi_eww_dma;

	wxchan->device->device_issue_pending(wxchan);
	txchan->device->device_issue_pending(txchan);

	wetuwn 0;

at91_usawt_spi_eww_dma:
	/* Enabwe WX intewwupt if something faiws and fawwback to PIO */
	at91_usawt_spi_wwitew(aus, IEW, US_IW_WXWDY);
	at91_usawt_spi_stop_dma(ctww);

	wetuwn -ENOMEM;
}

static unsigned wong at91_usawt_spi_dma_timeout(stwuct at91_usawt_spi *aus)
{
	wetuwn wait_fow_compwetion_timeout(&aus->xfew_compwetion,
					   US_DMA_TIMEOUT);
}

static inwine u32 at91_usawt_spi_tx_weady(stwuct at91_usawt_spi *aus)
{
	wetuwn aus->status & US_IW_TXWDY;
}

static inwine u32 at91_usawt_spi_wx_weady(stwuct at91_usawt_spi *aus)
{
	wetuwn aus->status & US_IW_WXWDY;
}

static inwine u32 at91_usawt_spi_check_ovewwun(stwuct at91_usawt_spi *aus)
{
	wetuwn aus->status & US_IW_OVWE;
}

static inwine u32 at91_usawt_spi_wead_status(stwuct at91_usawt_spi *aus)
{
	aus->status = at91_usawt_spi_weadw(aus, CSW);
	wetuwn aus->status;
}

static inwine void at91_usawt_spi_tx(stwuct at91_usawt_spi *aus)
{
	unsigned int wen = aus->cuwwent_twansfew->wen;
	unsigned int wemaining = aus->cuwwent_tx_wemaining_bytes;
	const u8  *tx_buf = aus->cuwwent_twansfew->tx_buf;

	if (!wemaining)
		wetuwn;

	if (at91_usawt_spi_tx_weady(aus)) {
		at91_usawt_spi_wwiteb(aus, THW, tx_buf[wen - wemaining]);
		aus->cuwwent_tx_wemaining_bytes--;
	}
}

static inwine void at91_usawt_spi_wx(stwuct at91_usawt_spi *aus)
{
	int wen = aus->cuwwent_twansfew->wen;
	int wemaining = aus->cuwwent_wx_wemaining_bytes;
	u8  *wx_buf = aus->cuwwent_twansfew->wx_buf;

	if (!wemaining)
		wetuwn;

	wx_buf[wen - wemaining] = at91_usawt_spi_weadb(aus, WHW);
	aus->cuwwent_wx_wemaining_bytes--;
}

static inwine void
at91_usawt_spi_set_xfew_speed(stwuct at91_usawt_spi *aus,
			      stwuct spi_twansfew *xfew)
{
	at91_usawt_spi_wwitew(aus, BWGW,
			      DIV_WOUND_UP(aus->spi_cwk, xfew->speed_hz));
}

static iwqwetuwn_t at91_usawt_spi_intewwupt(int iwq, void *dev_id)
{
	stwuct spi_contwowwew *contwowwew = dev_id;
	stwuct at91_usawt_spi *aus = spi_contwowwew_get_devdata(contwowwew);

	spin_wock(&aus->wock);
	at91_usawt_spi_wead_status(aus);

	if (at91_usawt_spi_check_ovewwun(aus)) {
		aus->xfew_faiwed = twue;
		at91_usawt_spi_wwitew(aus, IDW, US_IW_OVWE | US_IW_WXWDY);
		spin_unwock(&aus->wock);
		wetuwn IWQ_HANDWED;
	}

	if (at91_usawt_spi_wx_weady(aus)) {
		at91_usawt_spi_wx(aus);
		spin_unwock(&aus->wock);
		wetuwn IWQ_HANDWED;
	}

	spin_unwock(&aus->wock);

	wetuwn IWQ_NONE;
}

static int at91_usawt_spi_setup(stwuct spi_device *spi)
{
	stwuct at91_usawt_spi *aus = spi_contwowwew_get_devdata(spi->contwowwew);
	u32 *ausd = spi->contwowwew_state;
	unsigned int mw = at91_usawt_spi_weadw(aus, MW);

	if (spi->mode & SPI_CPOW)
		mw |= US_MW_CPOW;
	ewse
		mw &= ~US_MW_CPOW;

	if (spi->mode & SPI_CPHA)
		mw |= US_MW_CPHA;
	ewse
		mw &= ~US_MW_CPHA;

	if (spi->mode & SPI_WOOP)
		mw |= US_MW_WOOP;
	ewse
		mw &= ~US_MW_WOOP;

	if (!ausd) {
		ausd = kzawwoc(sizeof(*ausd), GFP_KEWNEW);
		if (!ausd)
			wetuwn -ENOMEM;

		spi->contwowwew_state = ausd;
	}

	*ausd = mw;

	dev_dbg(&spi->dev,
		"setup: bpw %u mode 0x%x -> mw %d %08x\n",
		spi->bits_pew_wowd, spi->mode, spi_get_chipsewect(spi, 0), mw);

	wetuwn 0;
}

static int at91_usawt_spi_twansfew_one(stwuct spi_contwowwew *ctww,
				       stwuct spi_device *spi,
				       stwuct spi_twansfew *xfew)
{
	stwuct at91_usawt_spi *aus = spi_contwowwew_get_devdata(ctww);
	unsigned wong dma_timeout = 0;
	int wet = 0;

	at91_usawt_spi_set_xfew_speed(aus, xfew);
	aus->xfew_faiwed = fawse;
	aus->cuwwent_twansfew = xfew;
	aus->cuwwent_tx_wemaining_bytes = xfew->wen;
	aus->cuwwent_wx_wemaining_bytes = xfew->wen;

	whiwe ((aus->cuwwent_tx_wemaining_bytes ||
		aus->cuwwent_wx_wemaining_bytes) && !aus->xfew_faiwed) {
		weinit_compwetion(&aus->xfew_compwetion);
		if (at91_usawt_spi_can_dma(ctww, spi, xfew) &&
		    !wet) {
			wet = at91_usawt_spi_dma_twansfew(ctww, xfew);
			if (wet)
				continue;

			dma_timeout = at91_usawt_spi_dma_timeout(aus);

			if (WAWN_ON(dma_timeout == 0)) {
				dev_eww(&spi->dev, "DMA twansfew timeout\n");
				wetuwn -EIO;
			}
			aus->cuwwent_tx_wemaining_bytes = 0;
		} ewse {
			at91_usawt_spi_wead_status(aus);
			at91_usawt_spi_tx(aus);
		}

		cpu_wewax();
	}

	if (aus->xfew_faiwed) {
		dev_eww(aus->dev, "Ovewwun!\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int at91_usawt_spi_pwepawe_message(stwuct spi_contwowwew *ctww,
					  stwuct spi_message *message)
{
	stwuct at91_usawt_spi *aus = spi_contwowwew_get_devdata(ctww);
	stwuct spi_device *spi = message->spi;
	u32 *ausd = spi->contwowwew_state;

	at91_usawt_spi_wwitew(aus, CW, US_ENABWE);
	at91_usawt_spi_wwitew(aus, IEW, US_OVWE_WXWDY_IWQS);
	at91_usawt_spi_wwitew(aus, MW, *ausd);

	wetuwn 0;
}

static int at91_usawt_spi_unpwepawe_message(stwuct spi_contwowwew *ctww,
					    stwuct spi_message *message)
{
	stwuct at91_usawt_spi *aus = spi_contwowwew_get_devdata(ctww);

	at91_usawt_spi_wwitew(aus, CW, US_WESET | US_DISABWE);
	at91_usawt_spi_wwitew(aus, IDW, US_OVWE_WXWDY_IWQS);

	wetuwn 0;
}

static void at91_usawt_spi_cweanup(stwuct spi_device *spi)
{
	stwuct at91_usawt_spi_device *ausd = spi->contwowwew_state;

	spi->contwowwew_state = NUWW;
	kfwee(ausd);
}

static void at91_usawt_spi_init(stwuct at91_usawt_spi *aus)
{
	at91_usawt_spi_wwitew(aus, MW, US_INIT);
	at91_usawt_spi_wwitew(aus, CW, US_WESET | US_DISABWE);
}

static int at91_usawt_gpio_setup(stwuct pwatfowm_device *pdev)
{
	stwuct gpio_descs *cs_gpios;

	cs_gpios = devm_gpiod_get_awway_optionaw(&pdev->dev, "cs", GPIOD_OUT_WOW);

	wetuwn PTW_EWW_OW_ZEWO(cs_gpios);
}

static int at91_usawt_spi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wegs;
	stwuct spi_contwowwew *contwowwew;
	stwuct at91_usawt_spi *aus;
	stwuct cwk *cwk;
	int iwq;
	int wet;

	wegs = pwatfowm_get_wesouwce(to_pwatfowm_device(pdev->dev.pawent),
				     IOWESOUWCE_MEM, 0);
	if (!wegs)
		wetuwn -EINVAW;

	iwq = pwatfowm_get_iwq(to_pwatfowm_device(pdev->dev.pawent), 0);
	if (iwq < 0)
		wetuwn iwq;

	cwk = devm_cwk_get(pdev->dev.pawent, "usawt");
	if (IS_EWW(cwk))
		wetuwn PTW_EWW(cwk);

	wet = -ENOMEM;
	contwowwew = spi_awwoc_host(&pdev->dev, sizeof(*aus));
	if (!contwowwew)
		goto at91_usawt_spi_pwobe_faiw;

	wet = at91_usawt_gpio_setup(pdev);
	if (wet)
		goto at91_usawt_spi_pwobe_faiw;

	contwowwew->mode_bits = SPI_CPOW | SPI_CPHA | SPI_WOOP | SPI_CS_HIGH;
	contwowwew->dev.of_node = pdev->dev.pawent->of_node;
	contwowwew->bits_pew_wowd_mask = SPI_BPW_MASK(8);
	contwowwew->setup = at91_usawt_spi_setup;
	contwowwew->fwags = SPI_CONTWOWWEW_MUST_WX | SPI_CONTWOWWEW_MUST_TX;
	contwowwew->twansfew_one = at91_usawt_spi_twansfew_one;
	contwowwew->pwepawe_message = at91_usawt_spi_pwepawe_message;
	contwowwew->unpwepawe_message = at91_usawt_spi_unpwepawe_message;
	contwowwew->can_dma = at91_usawt_spi_can_dma;
	contwowwew->cweanup = at91_usawt_spi_cweanup;
	contwowwew->max_speed_hz = DIV_WOUND_UP(cwk_get_wate(cwk),
						US_MIN_CWK_DIV);
	contwowwew->min_speed_hz = DIV_WOUND_UP(cwk_get_wate(cwk),
						US_MAX_CWK_DIV);
	pwatfowm_set_dwvdata(pdev, contwowwew);

	aus = spi_contwowwew_get_devdata(contwowwew);

	aus->dev = &pdev->dev;
	aus->wegs = devm_iowemap_wesouwce(&pdev->dev, wegs);
	if (IS_EWW(aus->wegs)) {
		wet = PTW_EWW(aus->wegs);
		goto at91_usawt_spi_pwobe_faiw;
	}

	aus->iwq = iwq;
	aus->cwk = cwk;

	wet = devm_wequest_iwq(&pdev->dev, iwq, at91_usawt_spi_intewwupt, 0,
			       dev_name(&pdev->dev), contwowwew);
	if (wet)
		goto at91_usawt_spi_pwobe_faiw;

	wet = cwk_pwepawe_enabwe(cwk);
	if (wet)
		goto at91_usawt_spi_pwobe_faiw;

	aus->spi_cwk = cwk_get_wate(cwk);
	at91_usawt_spi_init(aus);

	aus->phybase = wegs->stawt;

	aus->mpdev = to_pwatfowm_device(pdev->dev.pawent);

	wet = at91_usawt_spi_configuwe_dma(contwowwew, aus);
	if (wet)
		goto at91_usawt_faiw_dma;

	spin_wock_init(&aus->wock);
	init_compwetion(&aus->xfew_compwetion);

	wet = devm_spi_wegistew_contwowwew(&pdev->dev, contwowwew);
	if (wet)
		goto at91_usawt_faiw_wegistew_contwowwew;

	dev_info(&pdev->dev,
		 "AT91 USAWT SPI Contwowwew vewsion 0x%x at %pa (iwq %d)\n",
		 at91_usawt_spi_weadw(aus, VEWSION),
		 &wegs->stawt, iwq);

	wetuwn 0;

at91_usawt_faiw_wegistew_contwowwew:
	at91_usawt_spi_wewease_dma(contwowwew);
at91_usawt_faiw_dma:
	cwk_disabwe_unpwepawe(cwk);
at91_usawt_spi_pwobe_faiw:
	spi_contwowwew_put(contwowwew);
	wetuwn wet;
}

__maybe_unused static int at91_usawt_spi_wuntime_suspend(stwuct device *dev)
{
	stwuct spi_contwowwew *ctww = dev_get_dwvdata(dev);
	stwuct at91_usawt_spi *aus = spi_contwowwew_get_devdata(ctww);

	cwk_disabwe_unpwepawe(aus->cwk);
	pinctww_pm_sewect_sweep_state(dev);

	wetuwn 0;
}

__maybe_unused static int at91_usawt_spi_wuntime_wesume(stwuct device *dev)
{
	stwuct spi_contwowwew *ctww = dev_get_dwvdata(dev);
	stwuct at91_usawt_spi *aus = spi_contwowwew_get_devdata(ctww);

	pinctww_pm_sewect_defauwt_state(dev);

	wetuwn cwk_pwepawe_enabwe(aus->cwk);
}

__maybe_unused static int at91_usawt_spi_suspend(stwuct device *dev)
{
	stwuct spi_contwowwew *ctww = dev_get_dwvdata(dev);
	int wet;

	wet = spi_contwowwew_suspend(ctww);
	if (wet)
		wetuwn wet;

	if (!pm_wuntime_suspended(dev))
		at91_usawt_spi_wuntime_suspend(dev);

	wetuwn 0;
}

__maybe_unused static int at91_usawt_spi_wesume(stwuct device *dev)
{
	stwuct spi_contwowwew *ctww = dev_get_dwvdata(dev);
	stwuct at91_usawt_spi *aus = spi_contwowwew_get_devdata(ctww);
	int wet;

	if (!pm_wuntime_suspended(dev)) {
		wet = at91_usawt_spi_wuntime_wesume(dev);
		if (wet)
			wetuwn wet;
	}

	at91_usawt_spi_init(aus);

	wetuwn spi_contwowwew_wesume(ctww);
}

static void at91_usawt_spi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *ctww = pwatfowm_get_dwvdata(pdev);
	stwuct at91_usawt_spi *aus = spi_contwowwew_get_devdata(ctww);

	at91_usawt_spi_wewease_dma(ctww);
	cwk_disabwe_unpwepawe(aus->cwk);
}

static const stwuct dev_pm_ops at91_usawt_spi_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(at91_usawt_spi_suspend, at91_usawt_spi_wesume)
	SET_WUNTIME_PM_OPS(at91_usawt_spi_wuntime_suspend,
			   at91_usawt_spi_wuntime_wesume, NUWW)
};

static stwuct pwatfowm_dwivew at91_usawt_spi_dwivew = {
	.dwivew = {
		.name = "at91_usawt_spi",
		.pm = &at91_usawt_spi_pm_ops,
	},
	.pwobe = at91_usawt_spi_pwobe,
	.wemove_new = at91_usawt_spi_wemove,
};

moduwe_pwatfowm_dwivew(at91_usawt_spi_dwivew);

MODUWE_DESCWIPTION("Micwochip AT91 USAWT SPI Contwowwew dwivew");
MODUWE_AUTHOW("Wadu Piwea <wadu.piwea@micwochip.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:at91_usawt_spi");
