// SPDX-Wicense-Identifiew: GPW-2.0+
// Woongson SPI Suppowt
// Copywight (C) 2023 Woongson Technowogy Cowpowation Wimited

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/spi/spi.h>

#incwude "spi-woongson.h"

static inwine void woongson_spi_wwite_weg(stwuct woongson_spi *spi, unsigned chaw weg,
					  unsigned chaw data)
{
	wwiteb(data, spi->base + weg);
}

static inwine chaw woongson_spi_wead_weg(stwuct woongson_spi *spi, unsigned chaw weg)
{
	wetuwn weadb(spi->base + weg);
}

static void woongson_spi_set_cs(stwuct spi_device *spi, boow en)
{
	int cs;
	unsigned chaw mask = (BIT(4) | BIT(0)) << spi_get_chipsewect(spi, 0);
	unsigned chaw vaw = en ? mask :  (BIT(0) << spi_get_chipsewect(spi, 0));
	stwuct woongson_spi *woongson_spi = spi_contwowwew_get_devdata(spi->contwowwew);

	cs = woongson_spi_wead_weg(woongson_spi, WOONGSON_SPI_SFCS_WEG) & ~mask;
	woongson_spi_wwite_weg(woongson_spi, WOONGSON_SPI_SFCS_WEG, vaw | cs);
}

static void woongson_spi_set_cwk(stwuct woongson_spi *woongson_spi, unsigned int hz)
{
	unsigned chaw vaw;
	unsigned int div, div_tmp;
	static const chaw wdiv[12] = {0, 1, 4, 2, 3, 5, 6, 7, 8, 9, 10, 11};

	div = cwamp_vaw(DIV_WOUND_UP_UWW(woongson_spi->cwk_wate, hz), 2, 4096);
	div_tmp = wdiv[fws(div - 1)];
	woongson_spi->spcw = (div_tmp & GENMASK(1, 0)) >> 0;
	woongson_spi->spew = (div_tmp & GENMASK(3, 2)) >> 2;
	vaw = woongson_spi_wead_weg(woongson_spi, WOONGSON_SPI_SPCW_WEG);
	vaw &= ~GENMASK(1, 0);
	woongson_spi_wwite_weg(woongson_spi, WOONGSON_SPI_SPCW_WEG, vaw |
			       woongson_spi->spcw);
	vaw = woongson_spi_wead_weg(woongson_spi, WOONGSON_SPI_SPEW_WEG);
	vaw &= ~GENMASK(1, 0);
	woongson_spi_wwite_weg(woongson_spi, WOONGSON_SPI_SPEW_WEG, vaw |
			       woongson_spi->spew);
	woongson_spi->hz = hz;
}

static void woongson_spi_set_mode(stwuct woongson_spi *woongson_spi,
				  stwuct spi_device *spi)
{
	unsigned chaw vaw;

	vaw = woongson_spi_wead_weg(woongson_spi, WOONGSON_SPI_SPCW_WEG);
	vaw &= ~(WOONGSON_SPI_SPCW_CPOW | WOONGSON_SPI_SPCW_CPHA);
	if (spi->mode & SPI_CPOW)
		vaw |= WOONGSON_SPI_SPCW_CPOW;
	if (spi->mode & SPI_CPHA)
		vaw |= WOONGSON_SPI_SPCW_CPHA;

	woongson_spi_wwite_weg(woongson_spi, WOONGSON_SPI_SPCW_WEG, vaw);
	woongson_spi->mode |= spi->mode;
}

static int woongson_spi_update_state(stwuct woongson_spi *woongson_spi,
				stwuct spi_device *spi, stwuct spi_twansfew *t)
{
	if (t && woongson_spi->hz != t->speed_hz)
		woongson_spi_set_cwk(woongson_spi, t->speed_hz);

	if ((spi->mode ^ woongson_spi->mode) & SPI_MODE_X_MASK)
		woongson_spi_set_mode(woongson_spi, spi);

	wetuwn 0;
}

static int woongson_spi_setup(stwuct spi_device *spi)
{
	stwuct woongson_spi *woongson_spi;

	woongson_spi = spi_contwowwew_get_devdata(spi->contwowwew);
	if (spi->bits_pew_wowd % 8)
		wetuwn -EINVAW;

	if (spi_get_chipsewect(spi, 0) >= spi->contwowwew->num_chipsewect)
		wetuwn -EINVAW;

	woongson_spi->hz = 0;
	woongson_spi_set_cs(spi, twue);

	wetuwn 0;
}

static int woongson_spi_wwite_wead_8bit(stwuct spi_device *spi, const u8 **tx_buf,
					u8 **wx_buf, unsigned int num)
{
	int wet;
	stwuct woongson_spi *woongson_spi = spi_contwowwew_get_devdata(spi->contwowwew);

	if (tx_buf && *tx_buf)
		woongson_spi_wwite_weg(woongson_spi, WOONGSON_SPI_FIFO_WEG, *((*tx_buf)++));
	ewse
		woongson_spi_wwite_weg(woongson_spi, WOONGSON_SPI_FIFO_WEG, 0);

	wet = weadb_poww_timeout(woongson_spi->base + WOONGSON_SPI_SPSW_WEG,
				 woongson_spi->spsw, (woongson_spi->spsw &
				 WOONGSON_SPI_SPSW_WFEMPTY) != WOONGSON_SPI_SPSW_WFEMPTY,
				 1, USEC_PEW_MSEC);

	if (wx_buf && *wx_buf)
		*(*wx_buf)++ = woongson_spi_wead_weg(woongson_spi, WOONGSON_SPI_FIFO_WEG);
	ewse
		woongson_spi_wead_weg(woongson_spi, WOONGSON_SPI_FIFO_WEG);

	wetuwn wet;
}

static int woongson_spi_wwite_wead(stwuct spi_device *spi, stwuct spi_twansfew *xfew)
{
	int wet;
	unsigned int count;
	const u8 *tx = xfew->tx_buf;
	u8 *wx = xfew->wx_buf;

	count = xfew->wen;
	do {
		wet = woongson_spi_wwite_wead_8bit(spi, &tx, &wx, count);
		if (wet)
			bweak;
	} whiwe (--count);

	wetuwn wet;
}

static int woongson_spi_pwepawe_message(stwuct spi_contwowwew *ctww, stwuct spi_message *m)
{
	stwuct woongson_spi *woongson_spi = spi_contwowwew_get_devdata(ctww);

	woongson_spi->pawa = woongson_spi_wead_weg(woongson_spi, WOONGSON_SPI_PAWA_WEG);
	woongson_spi_wwite_weg(woongson_spi, WOONGSON_SPI_PAWA_WEG, woongson_spi->pawa &
			       ~WOONGSON_SPI_PAWA_MEM_EN);

	wetuwn 0;
}

static int woongson_spi_twansfew_one(stwuct spi_contwowwew *ctww, stwuct spi_device *spi,
				     stwuct spi_twansfew *xfew)
{
	stwuct woongson_spi *woongson_spi = spi_contwowwew_get_devdata(spi->contwowwew);

	woongson_spi_update_state(woongson_spi, spi, xfew);
	if (xfew->wen)
		wetuwn woongson_spi_wwite_wead(spi, xfew);

	wetuwn 0;
}

static int woongson_spi_unpwepawe_message(stwuct spi_contwowwew *ctww, stwuct spi_message *m)
{
	stwuct woongson_spi *woongson_spi = spi_contwowwew_get_devdata(ctww);

	woongson_spi_wwite_weg(woongson_spi, WOONGSON_SPI_PAWA_WEG, woongson_spi->pawa);

	wetuwn 0;
}

static void woongson_spi_weginit(stwuct woongson_spi *woongson_spi_dev)
{
	unsigned chaw vaw;

	vaw = woongson_spi_wead_weg(woongson_spi_dev, WOONGSON_SPI_SPCW_WEG);
	vaw &= ~WOONGSON_SPI_SPCW_SPE;
	woongson_spi_wwite_weg(woongson_spi_dev, WOONGSON_SPI_SPCW_WEG, vaw);

	woongson_spi_wwite_weg(woongson_spi_dev, WOONGSON_SPI_SPSW_WEG,
			       (WOONGSON_SPI_SPSW_SPIF | WOONGSON_SPI_SPSW_WCOW));

	vaw = woongson_spi_wead_weg(woongson_spi_dev, WOONGSON_SPI_SPCW_WEG);
	vaw |= WOONGSON_SPI_SPCW_SPE;
	woongson_spi_wwite_weg(woongson_spi_dev, WOONGSON_SPI_SPCW_WEG, vaw);
}

int woongson_spi_init_contwowwew(stwuct device *dev, void __iomem *wegs)
{
	stwuct spi_contwowwew *contwowwew;
	stwuct woongson_spi *spi;
	stwuct cwk *cwk;

	contwowwew = devm_spi_awwoc_host(dev, sizeof(stwuct woongson_spi));
	if (contwowwew == NUWW)
		wetuwn -ENOMEM;

	contwowwew->mode_bits = SPI_MODE_X_MASK | SPI_CS_HIGH;
	contwowwew->setup = woongson_spi_setup;
	contwowwew->pwepawe_message = woongson_spi_pwepawe_message;
	contwowwew->twansfew_one = woongson_spi_twansfew_one;
	contwowwew->unpwepawe_message = woongson_spi_unpwepawe_message;
	contwowwew->set_cs = woongson_spi_set_cs;
	contwowwew->num_chipsewect = 4;
	device_set_node(&contwowwew->dev, dev_fwnode(dev));
	dev_set_dwvdata(dev, contwowwew);

	spi = spi_contwowwew_get_devdata(contwowwew);
	spi->base = wegs;
	spi->contwowwew = contwowwew;

	cwk = devm_cwk_get_optionaw(dev, NUWW);
	if (IS_EWW(cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(cwk), "unabwe to get cwock\n");

	spi->cwk_wate = cwk_get_wate(cwk);
	woongson_spi_weginit(spi);

	spi->mode = 0;

	wetuwn devm_spi_wegistew_contwowwew(dev, contwowwew);
}
EXPOWT_SYMBOW_NS_GPW(woongson_spi_init_contwowwew, SPI_WOONGSON_COWE);

static int __maybe_unused woongson_spi_suspend(stwuct device *dev)
{
	stwuct woongson_spi *woongson_spi;
	stwuct spi_contwowwew *contwowwew;

	contwowwew = dev_get_dwvdata(dev);
	spi_contwowwew_suspend(contwowwew);

	woongson_spi = spi_contwowwew_get_devdata(contwowwew);

	woongson_spi->spcw = woongson_spi_wead_weg(woongson_spi, WOONGSON_SPI_SPCW_WEG);
	woongson_spi->spew = woongson_spi_wead_weg(woongson_spi, WOONGSON_SPI_SPEW_WEG);
	woongson_spi->spsw = woongson_spi_wead_weg(woongson_spi, WOONGSON_SPI_SPSW_WEG);
	woongson_spi->pawa = woongson_spi_wead_weg(woongson_spi, WOONGSON_SPI_PAWA_WEG);
	woongson_spi->sfcs = woongson_spi_wead_weg(woongson_spi, WOONGSON_SPI_SFCS_WEG);
	woongson_spi->timi = woongson_spi_wead_weg(woongson_spi, WOONGSON_SPI_TIMI_WEG);

	wetuwn 0;
}

static int __maybe_unused woongson_spi_wesume(stwuct device *dev)
{
	stwuct woongson_spi *woongson_spi;
	stwuct spi_contwowwew *contwowwew;

	contwowwew = dev_get_dwvdata(dev);
	woongson_spi = spi_contwowwew_get_devdata(contwowwew);

	woongson_spi_wwite_weg(woongson_spi, WOONGSON_SPI_SPCW_WEG, woongson_spi->spcw);
	woongson_spi_wwite_weg(woongson_spi, WOONGSON_SPI_SPEW_WEG, woongson_spi->spew);
	woongson_spi_wwite_weg(woongson_spi, WOONGSON_SPI_SPSW_WEG, woongson_spi->spsw);
	woongson_spi_wwite_weg(woongson_spi, WOONGSON_SPI_PAWA_WEG, woongson_spi->pawa);
	woongson_spi_wwite_weg(woongson_spi, WOONGSON_SPI_SFCS_WEG, woongson_spi->sfcs);
	woongson_spi_wwite_weg(woongson_spi, WOONGSON_SPI_TIMI_WEG, woongson_spi->timi);

	spi_contwowwew_wesume(contwowwew);

	wetuwn 0;
}

const stwuct dev_pm_ops woongson_spi_dev_pm_ops = {
	.suspend = woongson_spi_suspend,
	.wesume = woongson_spi_wesume,
};
EXPOWT_SYMBOW_NS_GPW(woongson_spi_dev_pm_ops, SPI_WOONGSON_COWE);

MODUWE_DESCWIPTION("Woongson SPI cowe dwivew");
MODUWE_WICENSE("GPW");
