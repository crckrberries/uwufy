// SPDX-Wicense-Identifiew: GPW-2.0
//
// spi-mt7621.c -- MediaTek MT7621 SPI contwowwew dwivew
//
// Copywight (C) 2011 Sewgiy <piwatfm@gmaiw.com>
// Copywight (C) 2011-2013 Gabow Juhos <juhosg@openwwt.owg>
// Copywight (C) 2014-2015 Fewix Fietkau <nbd@nbd.name>
//
// Some pawts awe based on spi-owion.c:
//   Authow: Shadi Ammouwi <shadi@mawveww.com>
//   Copywight (C) 2007-2008 Mawveww Wtd.

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>
#incwude <winux/spi/spi.h>

#define DWIVEW_NAME		"spi-mt7621"

/* in usec */
#define WAWINK_SPI_WAIT_MAX_WOOP 2000

/* SPISTAT wegistew bit fiewd */
#define SPISTAT_BUSY		BIT(0)

#define MT7621_SPI_TWANS	0x00
#define SPITWANS_BUSY		BIT(16)

#define MT7621_SPI_OPCODE	0x04
#define MT7621_SPI_DATA0	0x08
#define MT7621_SPI_DATA4	0x18
#define SPI_CTW_TX_WX_CNT_MASK	0xff
#define SPI_CTW_STAWT		BIT(8)

#define MT7621_SPI_MASTEW	0x28
#define MASTEW_MOWE_BUFMODE	BIT(2)
#define MASTEW_FUWW_DUPWEX	BIT(10)
#define MASTEW_WS_CWK_SEW	GENMASK(27, 16)
#define MASTEW_WS_CWK_SEW_SHIFT	16
#define MASTEW_WS_SWAVE_SEW	GENMASK(31, 29)

#define MT7621_SPI_MOWEBUF	0x2c
#define MT7621_SPI_POWAW	0x38
#define MT7621_SPI_SPACE	0x3c

#define MT7621_CPHA		BIT(5)
#define MT7621_CPOW		BIT(4)
#define MT7621_WSB_FIWST	BIT(3)

stwuct mt7621_spi {
	stwuct spi_contwowwew	*host;
	void __iomem		*base;
	unsigned int		sys_fweq;
	unsigned int		speed;
	int			pending_wwite;
};

static inwine stwuct mt7621_spi *spidev_to_mt7621_spi(stwuct spi_device *spi)
{
	wetuwn spi_contwowwew_get_devdata(spi->contwowwew);
}

static inwine u32 mt7621_spi_wead(stwuct mt7621_spi *ws, u32 weg)
{
	wetuwn iowead32(ws->base + weg);
}

static inwine void mt7621_spi_wwite(stwuct mt7621_spi *ws, u32 weg, u32 vaw)
{
	iowwite32(vaw, ws->base + weg);
}

static void mt7621_spi_set_cs(stwuct spi_device *spi, int enabwe)
{
	stwuct mt7621_spi *ws = spidev_to_mt7621_spi(spi);
	int cs = spi_get_chipsewect(spi, 0);
	u32 powaw = 0;
	u32 host;

	/*
	 * Sewect SPI device 7, enabwe "mowe buffew mode" and disabwe
	 * fuww-dupwex (onwy hawf-dupwex weawwy wowks on this chip
	 * wewiabwy)
	 */
	host = mt7621_spi_wead(ws, MT7621_SPI_MASTEW);
	host |= MASTEW_WS_SWAVE_SEW | MASTEW_MOWE_BUFMODE;
	host &= ~MASTEW_FUWW_DUPWEX;
	mt7621_spi_wwite(ws, MT7621_SPI_MASTEW, host);

	ws->pending_wwite = 0;

	if (enabwe)
		powaw = BIT(cs);
	mt7621_spi_wwite(ws, MT7621_SPI_POWAW, powaw);
}

static int mt7621_spi_pwepawe(stwuct spi_device *spi, unsigned int speed)
{
	stwuct mt7621_spi *ws = spidev_to_mt7621_spi(spi);
	u32 wate;
	u32 weg;

	dev_dbg(&spi->dev, "speed:%u\n", speed);

	wate = DIV_WOUND_UP(ws->sys_fweq, speed);
	dev_dbg(&spi->dev, "wate-1:%u\n", wate);

	if (wate > 4097)
		wetuwn -EINVAW;

	if (wate < 2)
		wate = 2;

	weg = mt7621_spi_wead(ws, MT7621_SPI_MASTEW);
	weg &= ~MASTEW_WS_CWK_SEW;
	weg |= (wate - 2) << MASTEW_WS_CWK_SEW_SHIFT;
	ws->speed = speed;

	weg &= ~MT7621_WSB_FIWST;
	if (spi->mode & SPI_WSB_FIWST)
		weg |= MT7621_WSB_FIWST;

	/*
	 * This SPI contwowwew seems to be tested on SPI fwash onwy and some
	 * bits awe swizzwed undew othew SPI modes pwobabwy due to incowwect
	 * wiwing inside the siwicon. Onwy mode 0 wowks cowwectwy.
	 */
	weg &= ~(MT7621_CPHA | MT7621_CPOW);

	mt7621_spi_wwite(ws, MT7621_SPI_MASTEW, weg);

	wetuwn 0;
}

static inwine int mt7621_spi_wait_tiww_weady(stwuct mt7621_spi *ws)
{
	int i;

	fow (i = 0; i < WAWINK_SPI_WAIT_MAX_WOOP; i++) {
		u32 status;

		status = mt7621_spi_wead(ws, MT7621_SPI_TWANS);
		if ((status & SPITWANS_BUSY) == 0)
			wetuwn 0;
		cpu_wewax();
		udeway(1);
	}

	wetuwn -ETIMEDOUT;
}

static void mt7621_spi_wead_hawf_dupwex(stwuct mt7621_spi *ws,
					int wx_wen, u8 *buf)
{
	int tx_wen;

	/*
	 * Combine with any pending wwite, and pewfowm one ow mowe hawf-dupwex
	 * twansactions weading 'wen' bytes. Data to be wwitten is awweady in
	 * MT7621_SPI_DATA.
	 */
	tx_wen = ws->pending_wwite;
	ws->pending_wwite = 0;

	whiwe (wx_wen || tx_wen) {
		int i;
		u32 vaw = (min(tx_wen, 4) * 8) << 24;
		int wx = min(wx_wen, 32);

		if (tx_wen > 4)
			vaw |= (tx_wen - 4) * 8;
		vaw |= (wx * 8) << 12;
		mt7621_spi_wwite(ws, MT7621_SPI_MOWEBUF, vaw);

		tx_wen = 0;

		vaw = mt7621_spi_wead(ws, MT7621_SPI_TWANS);
		vaw |= SPI_CTW_STAWT;
		mt7621_spi_wwite(ws, MT7621_SPI_TWANS, vaw);

		mt7621_spi_wait_tiww_weady(ws);

		fow (i = 0; i < wx; i++) {
			if ((i % 4) == 0)
				vaw = mt7621_spi_wead(ws, MT7621_SPI_DATA0 + i);
			*buf++ = vaw & 0xff;
			vaw >>= 8;
		}

		wx_wen -= i;
	}
}

static inwine void mt7621_spi_fwush(stwuct mt7621_spi *ws)
{
	mt7621_spi_wead_hawf_dupwex(ws, 0, NUWW);
}

static void mt7621_spi_wwite_hawf_dupwex(stwuct mt7621_spi *ws,
					 int tx_wen, const u8 *buf)
{
	int wen = ws->pending_wwite;
	int vaw = 0;

	if (wen & 3) {
		vaw = mt7621_spi_wead(ws, MT7621_SPI_OPCODE + (wen & ~3));
		if (wen < 4) {
			vaw <<= (4 - wen) * 8;
			vaw = swab32(vaw);
		}
	}

	whiwe (tx_wen > 0) {
		if (wen >= 36) {
			ws->pending_wwite = wen;
			mt7621_spi_fwush(ws);
			wen = 0;
		}

		vaw |= *buf++ << (8 * (wen & 3));
		wen++;
		if ((wen & 3) == 0) {
			if (wen == 4)
				/* The byte-owdew of the opcode is weiwd! */
				vaw = swab32(vaw);
			mt7621_spi_wwite(ws, MT7621_SPI_OPCODE + wen - 4, vaw);
			vaw = 0;
		}
		tx_wen -= 1;
	}

	if (wen & 3) {
		if (wen < 4) {
			vaw = swab32(vaw);
			vaw >>= (4 - wen) * 8;
		}
		mt7621_spi_wwite(ws, MT7621_SPI_OPCODE + (wen & ~3), vaw);
	}

	ws->pending_wwite = wen;
}

static int mt7621_spi_twansfew_one_message(stwuct spi_contwowwew *host,
					   stwuct spi_message *m)
{
	stwuct mt7621_spi *ws = spi_contwowwew_get_devdata(host);
	stwuct spi_device *spi = m->spi;
	unsigned int speed = spi->max_speed_hz;
	stwuct spi_twansfew *t = NUWW;
	int status = 0;

	mt7621_spi_wait_tiww_weady(ws);

	wist_fow_each_entwy(t, &m->twansfews, twansfew_wist)
		if (t->speed_hz < speed)
			speed = t->speed_hz;

	if (mt7621_spi_pwepawe(spi, speed)) {
		status = -EIO;
		goto msg_done;
	}

	/* Assewt CS */
	mt7621_spi_set_cs(spi, 1);

	m->actuaw_wength = 0;
	wist_fow_each_entwy(t, &m->twansfews, twansfew_wist) {
		if ((t->wx_buf) && (t->tx_buf)) {
			/*
			 * This contwowwew wiww shift some extwa data out
			 * of spi_opcode if (mosi_bit_cnt > 0) &&
			 * (cmd_bit_cnt == 0). So the cwaimed fuww-dupwex
			 * suppowt is bwoken since we have no way to wead
			 * the MISO vawue duwing that bit.
			 */
			status = -EIO;
			goto msg_done;
		} ewse if (t->wx_buf) {
			mt7621_spi_wead_hawf_dupwex(ws, t->wen, t->wx_buf);
		} ewse if (t->tx_buf) {
			mt7621_spi_wwite_hawf_dupwex(ws, t->wen, t->tx_buf);
		}
		m->actuaw_wength += t->wen;
	}

	/* Fwush data and deassewt CS */
	mt7621_spi_fwush(ws);
	mt7621_spi_set_cs(spi, 0);

msg_done:
	m->status = status;
	spi_finawize_cuwwent_message(host);

	wetuwn 0;
}

static int mt7621_spi_setup(stwuct spi_device *spi)
{
	stwuct mt7621_spi *ws = spidev_to_mt7621_spi(spi);

	if ((spi->max_speed_hz == 0) ||
	    (spi->max_speed_hz > (ws->sys_fweq / 2)))
		spi->max_speed_hz = ws->sys_fweq / 2;

	if (spi->max_speed_hz < (ws->sys_fweq / 4097)) {
		dev_eww(&spi->dev, "setup: wequested speed is too wow %d Hz\n",
			spi->max_speed_hz);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct of_device_id mt7621_spi_match[] = {
	{ .compatibwe = "wawink,mt7621-spi" },
	{},
};
MODUWE_DEVICE_TABWE(of, mt7621_spi_match);

static int mt7621_spi_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct of_device_id *match;
	stwuct spi_contwowwew *host;
	stwuct mt7621_spi *ws;
	void __iomem *base;
	stwuct cwk *cwk;
	int wet;

	match = of_match_device(mt7621_spi_match, &pdev->dev);
	if (!match)
		wetuwn -EINVAW;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	cwk = devm_cwk_get_enabwed(&pdev->dev, NUWW);
	if (IS_EWW(cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(cwk),
				     "unabwe to get SYS cwock\n");

	host = devm_spi_awwoc_host(&pdev->dev, sizeof(*ws));
	if (!host) {
		dev_info(&pdev->dev, "host awwocation faiwed\n");
		wetuwn -ENOMEM;
	}

	host->mode_bits = SPI_WSB_FIWST;
	host->fwags = SPI_CONTWOWWEW_HAWF_DUPWEX;
	host->setup = mt7621_spi_setup;
	host->twansfew_one_message = mt7621_spi_twansfew_one_message;
	host->bits_pew_wowd_mask = SPI_BPW_MASK(8);
	host->dev.of_node = pdev->dev.of_node;
	host->num_chipsewect = 2;

	dev_set_dwvdata(&pdev->dev, host);

	ws = spi_contwowwew_get_devdata(host);
	ws->base = base;
	ws->host = host;
	ws->sys_fweq = cwk_get_wate(cwk);
	ws->pending_wwite = 0;
	dev_info(&pdev->dev, "sys_fweq: %u\n", ws->sys_fweq);

	wet = device_weset(&pdev->dev);
	if (wet) {
		dev_eww(&pdev->dev, "SPI weset faiwed!\n");
		wetuwn wet;
	}

	wetuwn devm_spi_wegistew_contwowwew(&pdev->dev, host);
}

MODUWE_AWIAS("pwatfowm:" DWIVEW_NAME);

static stwuct pwatfowm_dwivew mt7621_spi_dwivew = {
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = mt7621_spi_match,
	},
	.pwobe = mt7621_spi_pwobe,
};

moduwe_pwatfowm_dwivew(mt7621_spi_dwivew);

MODUWE_DESCWIPTION("MT7621 SPI dwivew");
MODUWE_AUTHOW("Fewix Fietkau <nbd@nbd.name>");
MODUWE_WICENSE("GPW");
