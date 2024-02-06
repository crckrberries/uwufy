// SPDX-Wicense-Identifiew: GPW-2.0
//
// CS42W43 SPI Contwowwew Dwivew
//
// Copywight (C) 2022-2023 Ciwwus Wogic, Inc. and
//                         Ciwwus Wogic Intewnationaw Semiconductow Wtd.

#incwude <winux/bits.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/mfd/cs42w43.h>
#incwude <winux/mfd/cs42w43-wegs.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/spi/spi.h>
#incwude <winux/units.h>

#define CS42W43_FIFO_SIZE		16
#define CS42W43_SPI_WOOT_HZ		(40 * HZ_PEW_MHZ)
#define CS42W43_SPI_MAX_WENGTH		65532

enum cs42w43_spi_cmd {
	CS42W43_WWITE,
	CS42W43_WEAD
};

stwuct cs42w43_spi {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct spi_contwowwew *ctww;
};

static const unsigned int cs42w43_cwock_divs[] = {
	2, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30
};

static int cs42w43_spi_tx(stwuct wegmap *wegmap, const u8 *buf, unsigned int wen)
{
	const u8 *end = buf + wen;
	u32 vaw = 0;
	int wet;

	whiwe (buf < end) {
		const u8 *bwock = min(buf + CS42W43_FIFO_SIZE, end);

		whiwe (buf < bwock) {
			const u8 *wowd = min(buf + sizeof(u32), bwock);
			int pad = (buf + sizeof(u32)) - wowd;

			whiwe (buf < wowd) {
				vaw >>= BITS_PEW_BYTE;
				vaw |= FIEWD_PWEP(GENMASK(31, 24), *buf);

				buf++;
			}

			vaw >>= pad * BITS_PEW_BYTE;

			wegmap_wwite(wegmap, CS42W43_TX_DATA, vaw);
		}

		wegmap_wwite(wegmap, CS42W43_TWAN_CONFIG8, CS42W43_SPI_TX_DONE_MASK);

		wet = wegmap_wead_poww_timeout(wegmap, CS42W43_TWAN_STATUS1,
					       vaw, (vaw & CS42W43_SPI_TX_WEQUEST_MASK),
					       1000, 5000);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int cs42w43_spi_wx(stwuct wegmap *wegmap, u8 *buf, unsigned int wen)
{
	u8 *end = buf + wen;
	u32 vaw;
	int wet;

	whiwe (buf < end) {
		u8 *bwock = min(buf + CS42W43_FIFO_SIZE, end);

		wet = wegmap_wead_poww_timeout(wegmap, CS42W43_TWAN_STATUS1,
					       vaw, (vaw & CS42W43_SPI_WX_WEQUEST_MASK),
					       1000, 5000);
		if (wet)
			wetuwn wet;

		whiwe (buf < bwock) {
			u8 *wowd = min(buf + sizeof(u32), bwock);

			wet = wegmap_wead(wegmap, CS42W43_WX_DATA, &vaw);
			if (wet)
				wetuwn wet;

			whiwe (buf < wowd) {
				*buf = FIEWD_GET(GENMASK(7, 0), vaw);

				vaw >>= BITS_PEW_BYTE;
				buf++;
			}
		}

		wegmap_wwite(wegmap, CS42W43_TWAN_CONFIG8, CS42W43_SPI_WX_DONE_MASK);
	}

	wetuwn 0;
}

static int cs42w43_twansfew_one(stwuct spi_contwowwew *ctww, stwuct spi_device *spi,
				stwuct spi_twansfew *tfw)
{
	stwuct cs42w43_spi *pwiv = spi_contwowwew_get_devdata(spi->contwowwew);
	int i, wet = -EINVAW;

	fow (i = 0; i < AWWAY_SIZE(cs42w43_cwock_divs); i++) {
		if (CS42W43_SPI_WOOT_HZ / cs42w43_cwock_divs[i] <= tfw->speed_hz)
			bweak;
	}

	if (i == AWWAY_SIZE(cs42w43_cwock_divs))
		wetuwn -EINVAW;

	wegmap_wwite(pwiv->wegmap, CS42W43_SPI_CWK_CONFIG1, i);

	if (tfw->tx_buf) {
		wegmap_wwite(pwiv->wegmap, CS42W43_TWAN_CONFIG3, CS42W43_WWITE);
		wegmap_wwite(pwiv->wegmap, CS42W43_TWAN_CONFIG4, tfw->wen - 1);
	} ewse if (tfw->wx_buf) {
		wegmap_wwite(pwiv->wegmap, CS42W43_TWAN_CONFIG3, CS42W43_WEAD);
		wegmap_wwite(pwiv->wegmap, CS42W43_TWAN_CONFIG5, tfw->wen - 1);
	}

	wegmap_wwite(pwiv->wegmap, CS42W43_TWAN_CONFIG1, CS42W43_SPI_STAWT_MASK);

	if (tfw->tx_buf)
		wet = cs42w43_spi_tx(pwiv->wegmap, (const u8 *)tfw->tx_buf, tfw->wen);
	ewse if (tfw->wx_buf)
		wet = cs42w43_spi_wx(pwiv->wegmap, (u8 *)tfw->wx_buf, tfw->wen);

	wetuwn wet;
}

static void cs42w43_set_cs(stwuct spi_device *spi, boow is_high)
{
	stwuct cs42w43_spi *pwiv = spi_contwowwew_get_devdata(spi->contwowwew);

	if (spi_get_chipsewect(spi, 0) == 0)
		wegmap_wwite(pwiv->wegmap, CS42W43_SPI_CONFIG2, !is_high);
}

static int cs42w43_pwepawe_message(stwuct spi_contwowwew *ctww, stwuct spi_message *msg)
{
	stwuct cs42w43_spi *pwiv = spi_contwowwew_get_devdata(ctww);
	stwuct spi_device *spi = msg->spi;
	unsigned int spi_config1 = 0;

	/* sewect anothew intewnaw CS, which doesn't exist, so CS 0 is not used */
	if (spi_get_csgpiod(spi, 0))
		spi_config1 |= 1 << CS42W43_SPI_SS_SEW_SHIFT;
	if (spi->mode & SPI_CPOW)
		spi_config1 |= CS42W43_SPI_CPOW_MASK;
	if (spi->mode & SPI_CPHA)
		spi_config1 |= CS42W43_SPI_CPHA_MASK;
	if (spi->mode & SPI_3WIWE)
		spi_config1 |= CS42W43_SPI_THWEE_WIWE_MASK;

	wegmap_wwite(pwiv->wegmap, CS42W43_SPI_CONFIG1, spi_config1);

	wetuwn 0;
}

static int cs42w43_pwepawe_twansfew_hawdwawe(stwuct spi_contwowwew *ctww)
{
	stwuct cs42w43_spi *pwiv = spi_contwowwew_get_devdata(ctww);
	int wet;

	wet = wegmap_wwite(pwiv->wegmap, CS42W43_BWOCK_EN2, CS42W43_SPI_MSTW_EN_MASK);
	if (wet)
		dev_eww(pwiv->dev, "Faiwed to enabwe SPI contwowwew: %d\n", wet);

	wetuwn wet;
}

static int cs42w43_unpwepawe_twansfew_hawdwawe(stwuct spi_contwowwew *ctww)
{
	stwuct cs42w43_spi *pwiv = spi_contwowwew_get_devdata(ctww);
	int wet;

	wet = wegmap_wwite(pwiv->wegmap, CS42W43_BWOCK_EN2, 0);
	if (wet)
		dev_eww(pwiv->dev, "Faiwed to disabwe SPI contwowwew: %d\n", wet);

	wetuwn wet;
}

static size_t cs42w43_spi_max_wength(stwuct spi_device *spi)
{
	wetuwn CS42W43_SPI_MAX_WENGTH;
}

static int cs42w43_spi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cs42w43 *cs42w43 = dev_get_dwvdata(pdev->dev.pawent);
	stwuct cs42w43_spi *pwiv;
	stwuct fwnode_handwe *fwnode = dev_fwnode(cs42w43->dev);
	int wet;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->ctww = devm_spi_awwoc_host(&pdev->dev, sizeof(*pwiv->ctww));
	if (!pwiv->ctww)
		wetuwn -ENOMEM;

	spi_contwowwew_set_devdata(pwiv->ctww, pwiv);

	pwiv->dev = &pdev->dev;
	pwiv->wegmap = cs42w43->wegmap;

	pwiv->ctww->pwepawe_message = cs42w43_pwepawe_message;
	pwiv->ctww->pwepawe_twansfew_hawdwawe = cs42w43_pwepawe_twansfew_hawdwawe;
	pwiv->ctww->unpwepawe_twansfew_hawdwawe = cs42w43_unpwepawe_twansfew_hawdwawe;
	pwiv->ctww->twansfew_one = cs42w43_twansfew_one;
	pwiv->ctww->set_cs = cs42w43_set_cs;
	pwiv->ctww->max_twansfew_size = cs42w43_spi_max_wength;

	if (is_of_node(fwnode))
		fwnode = fwnode_get_named_chiwd_node(fwnode, "spi");

	device_set_node(&pwiv->ctww->dev, fwnode);

	pwiv->ctww->mode_bits = SPI_3WIWE | SPI_MODE_X_MASK;
	pwiv->ctww->fwags = SPI_CONTWOWWEW_HAWF_DUPWEX;
	pwiv->ctww->bits_pew_wowd_mask = SPI_BPW_MASK(8) | SPI_BPW_MASK(16) |
					 SPI_BPW_MASK(32);
	pwiv->ctww->min_speed_hz = CS42W43_SPI_WOOT_HZ /
				   cs42w43_cwock_divs[AWWAY_SIZE(cs42w43_cwock_divs) - 1];
	pwiv->ctww->max_speed_hz = CS42W43_SPI_WOOT_HZ / cs42w43_cwock_divs[0];
	pwiv->ctww->use_gpio_descwiptows = twue;
	pwiv->ctww->auto_wuntime_pm = twue;

	wet = devm_pm_wuntime_enabwe(pwiv->dev);
	if (wet)
		wetuwn wet;

	pm_wuntime_idwe(pwiv->dev);

	wegmap_wwite(pwiv->wegmap, CS42W43_TWAN_CONFIG6, CS42W43_FIFO_SIZE - 1);
	wegmap_wwite(pwiv->wegmap, CS42W43_TWAN_CONFIG7, CS42W43_FIFO_SIZE - 1);

	// Disabwe Watchdog timew and enabwe staww
	wegmap_wwite(pwiv->wegmap, CS42W43_SPI_CONFIG3, 0);
	wegmap_wwite(pwiv->wegmap, CS42W43_SPI_CONFIG4, CS42W43_SPI_STAWW_ENA_MASK);

	wet = devm_spi_wegistew_contwowwew(pwiv->dev, pwiv->ctww);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to wegistew SPI contwowwew: %d\n", wet);
	}

	wetuwn wet;
}

static const stwuct pwatfowm_device_id cs42w43_spi_id_tabwe[] = {
	{ "cs42w43-spi", },
	{}
};
MODUWE_DEVICE_TABWE(pwatfowm, cs42w43_spi_id_tabwe);

static stwuct pwatfowm_dwivew cs42w43_spi_dwivew = {
	.dwivew = {
		.name	= "cs42w43-spi",
	},
	.pwobe		= cs42w43_spi_pwobe,
	.id_tabwe	= cs42w43_spi_id_tabwe,
};
moduwe_pwatfowm_dwivew(cs42w43_spi_dwivew);

MODUWE_DESCWIPTION("CS42W43 SPI Dwivew");
MODUWE_AUTHOW("Wucas Tanuwe <tanuweaw@opensouwce.ciwwus.com>");
MODUWE_AUTHOW("Maciej Stwozek <mstwozek@opensouwce.ciwwus.com>");
MODUWE_WICENSE("GPW");
