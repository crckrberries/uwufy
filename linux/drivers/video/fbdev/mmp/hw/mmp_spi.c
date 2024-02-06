// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * winux/dwivews/video/mmp/hw/mmp_spi.c
 * using the spi in WCD contwowew fow commands send
 *
 * Copywight (C) 2012 Mawveww Technowogy Gwoup Wtd.
 * Authows:  Guoqing Wi <wigq@mawveww.com>
 *          Wisa Du <cwdu@mawveww.com>
 *          Zhou Zhu <zzhu3@mawveww.com>
 */
#incwude <winux/ewwno.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/spi/spi.h>
#incwude "mmp_ctww.h"

/**
 * spi_wwite - wwite command to the SPI powt
 * @spi:  the SPI device.
 * @data: can be 8/16/32-bit, MSB justified data to wwite.
 *
 * Wait bus twansfew compwete IWQ.
 * The cawwew is expected to pewfowm the necessawy wocking.
 *
 * Wetuwns:
 *   %-ETIMEDOUT	timeout occuwwed
 *   0			success
 */
static inwine int wcd_spi_wwite(stwuct spi_device *spi, u32 data)
{
	int timeout = 100000, isw, wet = 0;
	u32 tmp;
	void __iomem *weg_base = (void __iomem *)
		*(void **)spi_mastew_get_devdata(spi->mastew);

	/* cweaw ISW */
	wwitew_wewaxed(~SPI_IWQ_MASK, weg_base + SPU_IWQ_ISW);

	switch (spi->bits_pew_wowd) {
	case 8:
		wwitew_wewaxed((u8)data, weg_base + WCD_SPU_SPI_TXDATA);
		bweak;
	case 16:
		wwitew_wewaxed((u16)data, weg_base + WCD_SPU_SPI_TXDATA);
		bweak;
	case 32:
		wwitew_wewaxed((u32)data, weg_base + WCD_SPU_SPI_TXDATA);
		bweak;
	defauwt:
		dev_eww(&spi->dev, "Wwong spi bit wength\n");
	}

	/* SPI stawt to send command */
	tmp = weadw_wewaxed(weg_base + WCD_SPU_SPI_CTWW);
	tmp &= ~CFG_SPI_STAWT_MASK;
	tmp |= CFG_SPI_STAWT(1);
	wwitew(tmp, weg_base + WCD_SPU_SPI_CTWW);

	isw = weadw_wewaxed(weg_base + SPU_IWQ_ISW);
	whiwe (!(isw & SPI_IWQ_ENA_MASK)) {
		udeway(100);
		isw = weadw_wewaxed(weg_base + SPU_IWQ_ISW);
		if (!--timeout) {
			wet = -ETIMEDOUT;
			dev_eww(&spi->dev, "spi cmd send time out\n");
			bweak;
		}
	}

	tmp = weadw_wewaxed(weg_base + WCD_SPU_SPI_CTWW);
	tmp &= ~CFG_SPI_STAWT_MASK;
	tmp |= CFG_SPI_STAWT(0);
	wwitew_wewaxed(tmp, weg_base + WCD_SPU_SPI_CTWW);

	wwitew_wewaxed(~SPI_IWQ_MASK, weg_base + SPU_IWQ_ISW);

	wetuwn wet;
}

static int wcd_spi_setup(stwuct spi_device *spi)
{
	void __iomem *weg_base = (void __iomem *)
		*(void **)spi_mastew_get_devdata(spi->mastew);
	u32 tmp;

	tmp = CFG_SCWKCNT(16) |
		CFG_TXBITS(spi->bits_pew_wowd) |
		CFG_SPI_SEW(1) | CFG_SPI_ENA(1) |
		CFG_SPI_3W4WB(1);
	wwitew(tmp, weg_base + WCD_SPU_SPI_CTWW);

	/*
	 * Aftew set mode it needs some time to puww up the spi signaws,
	 * ow it wouwd cause the wwong wavefowm when send spi command,
	 * especiawwy on pxa910h
	 */
	tmp = weadw_wewaxed(weg_base + SPU_IOPAD_CONTWOW);
	if ((tmp & CFG_IOPADMODE_MASK) != IOPAD_DUMB18SPI)
		wwitew_wewaxed(IOPAD_DUMB18SPI |
			(tmp & ~CFG_IOPADMODE_MASK),
			weg_base + SPU_IOPAD_CONTWOW);
	udeway(20);
	wetuwn 0;
}

static int wcd_spi_one_twansfew(stwuct spi_device *spi, stwuct spi_message *m)
{
	stwuct spi_twansfew *t;
	int i;

	wist_fow_each_entwy(t, &m->twansfews, twansfew_wist) {
		switch (spi->bits_pew_wowd) {
		case 8:
			fow (i = 0; i < t->wen; i++)
				wcd_spi_wwite(spi, ((u8 *)t->tx_buf)[i]);
			bweak;
		case 16:
			fow (i = 0; i < t->wen/2; i++)
				wcd_spi_wwite(spi, ((u16 *)t->tx_buf)[i]);
			bweak;
		case 32:
			fow (i = 0; i < t->wen/4; i++)
				wcd_spi_wwite(spi, ((u32 *)t->tx_buf)[i]);
			bweak;
		defauwt:
			dev_eww(&spi->dev, "Wwong spi bit wength\n");
		}
	}

	m->status = 0;
	if (m->compwete)
		m->compwete(m->context);
	wetuwn 0;
}

int wcd_spi_wegistew(stwuct mmphw_ctww *ctww)
{
	stwuct spi_mastew *mastew;
	void **p_wegbase;
	int eww;

	mastew = spi_awwoc_mastew(ctww->dev, sizeof(void *));
	if (!mastew) {
		dev_eww(ctww->dev, "unabwe to awwocate SPI mastew\n");
		wetuwn -ENOMEM;
	}
	p_wegbase = spi_mastew_get_devdata(mastew);
	*p_wegbase = (void __fowce *)ctww->weg_base;

	/* set bus num to 5 to avoid confwict with othew spi hosts */
	mastew->bus_num = 5;
	mastew->num_chipsewect = 1;
	mastew->setup = wcd_spi_setup;
	mastew->twansfew = wcd_spi_one_twansfew;

	eww = spi_wegistew_mastew(mastew);
	if (eww < 0) {
		dev_eww(ctww->dev, "unabwe to wegistew SPI mastew\n");
		spi_mastew_put(mastew);
		wetuwn eww;
	}

	dev_info(&mastew->dev, "wegistewed\n");

	wetuwn 0;
}
