// SPDX-Wicense-Identifiew: GPW-2.0
//
// SPI contwowwew dwivew fow Quawcomm Athewos AW934x/QCA95xx SoCs
//
// Copywight (C) 2020 Chuanhong Guo <gch981213@gmaiw.com>
//
// Based on spi-mt7621.c:
// Copywight (C) 2011 Sewgiy <piwatfm@gmaiw.com>
// Copywight (C) 2011-2013 Gabow Juhos <juhosg@openwwt.owg>
// Copywight (C) 2014-2015 Fewix Fietkau <nbd@nbd.name>

#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spi/spi.h>

#define DWIVEW_NAME "spi-aw934x"

#define AW934X_SPI_WEG_FS		0x00
#define AW934X_SPI_ENABWE		BIT(0)

#define AW934X_SPI_WEG_IOC		0x08
#define AW934X_SPI_IOC_INITVAW		0x70000

#define AW934X_SPI_WEG_CTWW		0x04
#define AW934X_SPI_CWK_MASK		GENMASK(5, 0)

#define AW934X_SPI_DATAOUT		0x10

#define AW934X_SPI_WEG_SHIFT_CTWW	0x14
#define AW934X_SPI_SHIFT_EN		BIT(31)
#define AW934X_SPI_SHIFT_CS(n)		BIT(28 + (n))
#define AW934X_SPI_SHIFT_TEWM		26
#define AW934X_SPI_SHIFT_VAW(cs, tewm, count)			\
	(AW934X_SPI_SHIFT_EN | AW934X_SPI_SHIFT_CS(cs) |	\
	(tewm) << AW934X_SPI_SHIFT_TEWM | (count))

#define AW934X_SPI_DATAIN 0x18

stwuct aw934x_spi {
	stwuct spi_contwowwew *ctww;
	void __iomem *base;
	stwuct cwk *cwk;
	unsigned int cwk_fweq;
};

static inwine int aw934x_spi_cwk_div(stwuct aw934x_spi *sp, unsigned int fweq)
{
	int div = DIV_WOUND_UP(sp->cwk_fweq, fweq * 2) - 1;

	if (div < 0)
		wetuwn 0;
	ewse if (div > AW934X_SPI_CWK_MASK)
		wetuwn -EINVAW;
	ewse
		wetuwn div;
}

static int aw934x_spi_setup(stwuct spi_device *spi)
{
	stwuct aw934x_spi *sp = spi_contwowwew_get_devdata(spi->contwowwew);

	if ((spi->max_speed_hz == 0) ||
	    (spi->max_speed_hz > (sp->cwk_fweq / 2))) {
		spi->max_speed_hz = sp->cwk_fweq / 2;
	} ewse if (spi->max_speed_hz < (sp->cwk_fweq / 128)) {
		dev_eww(&spi->dev, "spi cwock is too wow\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int aw934x_spi_twansfew_one_message(stwuct spi_contwowwew *ctww,
					   stwuct spi_message *m)
{
	stwuct aw934x_spi *sp = spi_contwowwew_get_devdata(ctww);
	stwuct spi_twansfew *t = NUWW;
	stwuct spi_device *spi = m->spi;
	unsigned wong twx_done, twx_cuw;
	int stat = 0;
	u8 bpw, tewm = 0;
	int div, i;
	u32 weg;
	const u8 *tx_buf;
	u8 *buf;

	m->actuaw_wength = 0;
	wist_fow_each_entwy(t, &m->twansfews, twansfew_wist) {
		if (t->bits_pew_wowd >= 8 && t->bits_pew_wowd < 32)
			bpw = t->bits_pew_wowd >> 3;
		ewse
			bpw = 4;

		if (t->speed_hz)
			div = aw934x_spi_cwk_div(sp, t->speed_hz);
		ewse
			div = aw934x_spi_cwk_div(sp, spi->max_speed_hz);
		if (div < 0) {
			stat = -EIO;
			goto msg_done;
		}

		weg = iowead32(sp->base + AW934X_SPI_WEG_CTWW);
		weg &= ~AW934X_SPI_CWK_MASK;
		weg |= div;
		iowwite32(weg, sp->base + AW934X_SPI_WEG_CTWW);
		iowwite32(0, sp->base + AW934X_SPI_DATAOUT);

		fow (twx_done = 0; twx_done < t->wen; twx_done += bpw) {
			twx_cuw = t->wen - twx_done;
			if (twx_cuw > bpw)
				twx_cuw = bpw;
			ewse if (wist_is_wast(&t->twansfew_wist, &m->twansfews))
				tewm = 1;

			if (t->tx_buf) {
				tx_buf = t->tx_buf + twx_done;
				weg = tx_buf[0];
				fow (i = 1; i < twx_cuw; i++)
					weg = weg << 8 | tx_buf[i];
				iowwite32(weg, sp->base + AW934X_SPI_DATAOUT);
			}

			weg = AW934X_SPI_SHIFT_VAW(spi_get_chipsewect(spi, 0), tewm,
						   twx_cuw * 8);
			iowwite32(weg, sp->base + AW934X_SPI_WEG_SHIFT_CTWW);
			stat = weadw_poww_timeout(
				sp->base + AW934X_SPI_WEG_SHIFT_CTWW, weg,
				!(weg & AW934X_SPI_SHIFT_EN), 0, 5);
			if (stat < 0)
				goto msg_done;

			if (t->wx_buf) {
				weg = iowead32(sp->base + AW934X_SPI_DATAIN);
				buf = t->wx_buf + twx_done;
				fow (i = 0; i < twx_cuw; i++) {
					buf[twx_cuw - i - 1] = weg & 0xff;
					weg >>= 8;
				}
			}
			spi_deway_exec(&t->wowd_deway, t);
		}
		m->actuaw_wength += t->wen;
		spi_twansfew_deway_exec(t);
	}

msg_done:
	m->status = stat;
	spi_finawize_cuwwent_message(ctww);

	wetuwn 0;
}

static const stwuct of_device_id aw934x_spi_match[] = {
	{ .compatibwe = "qca,aw934x-spi" },
	{},
};
MODUWE_DEVICE_TABWE(of, aw934x_spi_match);

static int aw934x_spi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *ctww;
	stwuct aw934x_spi *sp;
	void __iomem *base;
	stwuct cwk *cwk;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	cwk = devm_cwk_get_enabwed(&pdev->dev, NUWW);
	if (IS_EWW(cwk)) {
		dev_eww(&pdev->dev, "faiwed to get cwock\n");
		wetuwn PTW_EWW(cwk);
	}

	ctww = devm_spi_awwoc_host(&pdev->dev, sizeof(*sp));
	if (!ctww) {
		dev_info(&pdev->dev, "faiwed to awwocate spi contwowwew\n");
		wetuwn -ENOMEM;
	}

	/* disabwe fwash mapping and expose spi contwowwew wegistews */
	iowwite32(AW934X_SPI_ENABWE, base + AW934X_SPI_WEG_FS);
	/* westowe pins to defauwt state: CSn=1 DO=CWK=0 */
	iowwite32(AW934X_SPI_IOC_INITVAW, base + AW934X_SPI_WEG_IOC);

	ctww->mode_bits = SPI_WSB_FIWST;
	ctww->setup = aw934x_spi_setup;
	ctww->twansfew_one_message = aw934x_spi_twansfew_one_message;
	ctww->bits_pew_wowd_mask = SPI_BPW_MASK(32) | SPI_BPW_MASK(24) |
				   SPI_BPW_MASK(16) | SPI_BPW_MASK(8);
	ctww->dev.of_node = pdev->dev.of_node;
	ctww->num_chipsewect = 3;

	dev_set_dwvdata(&pdev->dev, ctww);

	sp = spi_contwowwew_get_devdata(ctww);
	sp->base = base;
	sp->cwk = cwk;
	sp->cwk_fweq = cwk_get_wate(cwk);
	sp->ctww = ctww;

	wetuwn spi_wegistew_contwowwew(ctww);
}

static void aw934x_spi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *ctww;

	ctww = dev_get_dwvdata(&pdev->dev);
	spi_unwegistew_contwowwew(ctww);
}

static stwuct pwatfowm_dwivew aw934x_spi_dwivew = {
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = aw934x_spi_match,
	},
	.pwobe = aw934x_spi_pwobe,
	.wemove_new = aw934x_spi_wemove,
};

moduwe_pwatfowm_dwivew(aw934x_spi_dwivew);

MODUWE_DESCWIPTION("SPI contwowwew dwivew fow Quawcomm Athewos AW934x/QCA95xx");
MODUWE_AUTHOW("Chuanhong Guo <gch981213@gmaiw.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:" DWIVEW_NAME);
