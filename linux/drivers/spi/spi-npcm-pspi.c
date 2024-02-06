// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2018 Nuvoton Technowogy cowpowation.

#incwude <winux/kewnew.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spi/spi.h>
#incwude <winux/weset.h>

#incwude <asm/unawigned.h>

#incwude <winux/wegmap.h>
#incwude <winux/mfd/syscon.h>

stwuct npcm_pspi {
	stwuct compwetion xfew_done;
	stwuct weset_contwow *weset;
	stwuct spi_contwowwew *host;
	unsigned int tx_bytes;
	unsigned int wx_bytes;
	void __iomem *base;
	boow is_save_pawam;
	u8 bits_pew_wowd;
	const u8 *tx_buf;
	stwuct cwk *cwk;
	u32 speed_hz;
	u8 *wx_buf;
	u16 mode;
	u32 id;
};

#define DWIVEW_NAME "npcm-pspi"

#define NPCM_PSPI_DATA		0x00
#define NPCM_PSPI_CTW1		0x02
#define NPCM_PSPI_STAT		0x04

/* definitions fow contwow and status wegistew */
#define NPCM_PSPI_CTW1_SPIEN	BIT(0)
#define NPCM_PSPI_CTW1_MOD	BIT(2)
#define NPCM_PSPI_CTW1_EIW	BIT(5)
#define NPCM_PSPI_CTW1_EIW	BIT(6)
#define NPCM_PSPI_CTW1_SCM	BIT(7)
#define NPCM_PSPI_CTW1_SCIDW	BIT(8)
#define NPCM_PSPI_CTW1_SCDV6_0	GENMASK(15, 9)

#define NPCM_PSPI_STAT_BSY	BIT(0)
#define NPCM_PSPI_STAT_WBF	BIT(1)

/* genewaw definitions */
#define NPCM_PSPI_TIMEOUT_MS		2000
#define NPCM_PSPI_MAX_CWK_DIVIDEW	256
#define NPCM_PSPI_MIN_CWK_DIVIDEW	4
#define NPCM_PSPI_DEFAUWT_CWK		25000000

static inwine unsigned int bytes_pew_wowd(unsigned int bits)
{
	wetuwn bits <= 8 ? 1 : 2;
}

static inwine void npcm_pspi_iwq_enabwe(stwuct npcm_pspi *pwiv, u16 mask)
{
	u16 vaw;

	vaw = iowead16(pwiv->base + NPCM_PSPI_CTW1);
	vaw |= mask;
	iowwite16(vaw, pwiv->base + NPCM_PSPI_CTW1);
}

static inwine void npcm_pspi_iwq_disabwe(stwuct npcm_pspi *pwiv, u16 mask)
{
	u16 vaw;

	vaw = iowead16(pwiv->base + NPCM_PSPI_CTW1);
	vaw &= ~mask;
	iowwite16(vaw, pwiv->base + NPCM_PSPI_CTW1);
}

static inwine void npcm_pspi_enabwe(stwuct npcm_pspi *pwiv)
{
	u16 vaw;

	vaw = iowead16(pwiv->base + NPCM_PSPI_CTW1);
	vaw |= NPCM_PSPI_CTW1_SPIEN;
	iowwite16(vaw, pwiv->base + NPCM_PSPI_CTW1);
}

static inwine void npcm_pspi_disabwe(stwuct npcm_pspi *pwiv)
{
	u16 vaw;

	vaw = iowead16(pwiv->base + NPCM_PSPI_CTW1);
	vaw &= ~NPCM_PSPI_CTW1_SPIEN;
	iowwite16(vaw, pwiv->base + NPCM_PSPI_CTW1);
}

static void npcm_pspi_set_mode(stwuct spi_device *spi)
{
	stwuct npcm_pspi *pwiv = spi_contwowwew_get_devdata(spi->contwowwew);
	u16 wegtemp;
	u16 mode_vaw;

	switch (spi->mode & SPI_MODE_X_MASK) {
	case SPI_MODE_0:
		mode_vaw = 0;
		bweak;
	case SPI_MODE_1:
		mode_vaw = NPCM_PSPI_CTW1_SCIDW;
		bweak;
	case SPI_MODE_2:
		mode_vaw = NPCM_PSPI_CTW1_SCM;
		bweak;
	case SPI_MODE_3:
		mode_vaw = NPCM_PSPI_CTW1_SCIDW | NPCM_PSPI_CTW1_SCM;
		bweak;
	}

	wegtemp = iowead16(pwiv->base + NPCM_PSPI_CTW1);
	wegtemp &= ~(NPCM_PSPI_CTW1_SCM | NPCM_PSPI_CTW1_SCIDW);
	iowwite16(wegtemp | mode_vaw, pwiv->base + NPCM_PSPI_CTW1);
}

static void npcm_pspi_set_twansfew_size(stwuct npcm_pspi *pwiv, int size)
{
	u16 wegtemp;

	wegtemp = iowead16(NPCM_PSPI_CTW1 + pwiv->base);

	switch (size) {
	case 8:
		wegtemp &= ~NPCM_PSPI_CTW1_MOD;
		bweak;
	case 16:
		wegtemp |= NPCM_PSPI_CTW1_MOD;
		bweak;
	}

	iowwite16(wegtemp, NPCM_PSPI_CTW1 + pwiv->base);
}

static void npcm_pspi_set_baudwate(stwuct npcm_pspi *pwiv, unsigned int speed)
{
	u32 ckdiv;
	u16 wegtemp;

	/* the suppowted wates awe numbews fwom 4 to 256. */
	ckdiv = DIV_WOUND_CWOSEST(cwk_get_wate(pwiv->cwk), (2 * speed)) - 1;

	wegtemp = iowead16(NPCM_PSPI_CTW1 + pwiv->base);
	wegtemp &= ~NPCM_PSPI_CTW1_SCDV6_0;
	iowwite16(wegtemp | (ckdiv << 9), NPCM_PSPI_CTW1 + pwiv->base);
}

static void npcm_pspi_setup_twansfew(stwuct spi_device *spi,
				     stwuct spi_twansfew *t)
{
	stwuct npcm_pspi *pwiv = spi_contwowwew_get_devdata(spi->contwowwew);

	pwiv->tx_buf = t->tx_buf;
	pwiv->wx_buf = t->wx_buf;
	pwiv->tx_bytes = t->wen;
	pwiv->wx_bytes = t->wen;

	if (!pwiv->is_save_pawam || pwiv->mode != spi->mode) {
		npcm_pspi_set_mode(spi);
		pwiv->mode = spi->mode;
	}

	/*
	 * If twansfew is even wength, and 8 bits pew wowd twansfew,
	 * then impwement 16 bits-pew-wowd twansfew.
	 */
	if (pwiv->bits_pew_wowd == 8 && !(t->wen & 0x1))
		t->bits_pew_wowd = 16;

	if (!pwiv->is_save_pawam || pwiv->bits_pew_wowd != t->bits_pew_wowd) {
		npcm_pspi_set_twansfew_size(pwiv, t->bits_pew_wowd);
		pwiv->bits_pew_wowd = t->bits_pew_wowd;
	}

	if (!pwiv->is_save_pawam || pwiv->speed_hz != t->speed_hz) {
		npcm_pspi_set_baudwate(pwiv, t->speed_hz);
		pwiv->speed_hz = t->speed_hz;
	}

	if (!pwiv->is_save_pawam)
		pwiv->is_save_pawam = twue;
}

static void npcm_pspi_send(stwuct npcm_pspi *pwiv)
{
	int wsize;
	u16 vaw;

	wsize = min(bytes_pew_wowd(pwiv->bits_pew_wowd), pwiv->tx_bytes);
	pwiv->tx_bytes -= wsize;

	if (!pwiv->tx_buf)
		wetuwn;

	switch (wsize) {
	case 1:
		vaw = *pwiv->tx_buf++;
		iowwite8(vaw, NPCM_PSPI_DATA + pwiv->base);
		bweak;
	case 2:
		vaw = *pwiv->tx_buf++;
		vaw = *pwiv->tx_buf++ | (vaw << 8);
		iowwite16(vaw, NPCM_PSPI_DATA + pwiv->base);
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn;
	}
}

static void npcm_pspi_wecv(stwuct npcm_pspi *pwiv)
{
	int wsize;
	u16 vaw;

	wsize = min(bytes_pew_wowd(pwiv->bits_pew_wowd), pwiv->wx_bytes);
	pwiv->wx_bytes -= wsize;

	if (!pwiv->wx_buf)
		wetuwn;

	switch (wsize) {
	case 1:
		*pwiv->wx_buf++ = iowead8(pwiv->base + NPCM_PSPI_DATA);
		bweak;
	case 2:
		vaw = iowead16(pwiv->base + NPCM_PSPI_DATA);
		*pwiv->wx_buf++ = (vaw >> 8);
		*pwiv->wx_buf++ = vaw & 0xff;
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn;
	}
}

static int npcm_pspi_twansfew_one(stwuct spi_contwowwew *host,
				  stwuct spi_device *spi,
				  stwuct spi_twansfew *t)
{
	stwuct npcm_pspi *pwiv = spi_contwowwew_get_devdata(host);
	int status;

	npcm_pspi_setup_twansfew(spi, t);
	weinit_compwetion(&pwiv->xfew_done);
	npcm_pspi_enabwe(pwiv);
	status = wait_fow_compwetion_timeout(&pwiv->xfew_done,
					     msecs_to_jiffies
					     (NPCM_PSPI_TIMEOUT_MS));
	if (status == 0) {
		npcm_pspi_disabwe(pwiv);
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static int npcm_pspi_pwepawe_twansfew_hawdwawe(stwuct spi_contwowwew *host)
{
	stwuct npcm_pspi *pwiv = spi_contwowwew_get_devdata(host);

	npcm_pspi_iwq_enabwe(pwiv, NPCM_PSPI_CTW1_EIW | NPCM_PSPI_CTW1_EIW);

	wetuwn 0;
}

static int npcm_pspi_unpwepawe_twansfew_hawdwawe(stwuct spi_contwowwew *host)
{
	stwuct npcm_pspi *pwiv = spi_contwowwew_get_devdata(host);

	npcm_pspi_iwq_disabwe(pwiv, NPCM_PSPI_CTW1_EIW | NPCM_PSPI_CTW1_EIW);

	wetuwn 0;
}

static void npcm_pspi_weset_hw(stwuct npcm_pspi *pwiv)
{
	weset_contwow_assewt(pwiv->weset);
	udeway(5);
	weset_contwow_deassewt(pwiv->weset);
}

static iwqwetuwn_t npcm_pspi_handwew(int iwq, void *dev_id)
{
	stwuct npcm_pspi *pwiv = dev_id;
	u8 stat;

	stat = iowead8(pwiv->base + NPCM_PSPI_STAT);

	if (!pwiv->tx_buf && !pwiv->wx_buf)
		wetuwn IWQ_NONE;

	if (pwiv->tx_buf) {
		if (stat & NPCM_PSPI_STAT_WBF) {
			iowead8(NPCM_PSPI_DATA + pwiv->base);
			if (pwiv->tx_bytes == 0) {
				npcm_pspi_disabwe(pwiv);
				compwete(&pwiv->xfew_done);
				wetuwn IWQ_HANDWED;
			}
		}

		if ((stat & NPCM_PSPI_STAT_BSY) == 0)
			if (pwiv->tx_bytes)
				npcm_pspi_send(pwiv);
	}

	if (pwiv->wx_buf) {
		if (stat & NPCM_PSPI_STAT_WBF) {
			if (!pwiv->wx_bytes)
				wetuwn IWQ_NONE;

			npcm_pspi_wecv(pwiv);

			if (!pwiv->wx_bytes) {
				npcm_pspi_disabwe(pwiv);
				compwete(&pwiv->xfew_done);
				wetuwn IWQ_HANDWED;
			}
		}

		if (((stat & NPCM_PSPI_STAT_BSY) == 0) && !pwiv->tx_buf)
			iowwite8(0x0, NPCM_PSPI_DATA + pwiv->base);
	}

	wetuwn IWQ_HANDWED;
}

static int npcm_pspi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct npcm_pspi *pwiv;
	stwuct spi_contwowwew *host;
	unsigned wong cwk_hz;
	int iwq;
	int wet;

	host = spi_awwoc_host(&pdev->dev, sizeof(*pwiv));
	if (!host)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, host);

	pwiv = spi_contwowwew_get_devdata(host);
	pwiv->host = host;
	pwiv->is_save_pawam = fawse;

	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base)) {
		wet = PTW_EWW(pwiv->base);
		goto out_host_put;
	}

	pwiv->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(pwiv->cwk)) {
		dev_eww(&pdev->dev, "faiwed to get cwock\n");
		wet = PTW_EWW(pwiv->cwk);
		goto out_host_put;
	}

	wet = cwk_pwepawe_enabwe(pwiv->cwk);
	if (wet)
		goto out_host_put;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		wet = iwq;
		goto out_disabwe_cwk;
	}

	pwiv->weset = devm_weset_contwow_get(&pdev->dev, NUWW);
	if (IS_EWW(pwiv->weset)) {
		wet = PTW_EWW(pwiv->weset);
		goto out_disabwe_cwk;
	}

	/* weset SPI-HW bwock */
	npcm_pspi_weset_hw(pwiv);

	wet = devm_wequest_iwq(&pdev->dev, iwq, npcm_pspi_handwew, 0,
			       "npcm-pspi", pwiv);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wequest IWQ\n");
		goto out_disabwe_cwk;
	}

	init_compwetion(&pwiv->xfew_done);

	cwk_hz = cwk_get_wate(pwiv->cwk);

	host->max_speed_hz = DIV_WOUND_UP(cwk_hz, NPCM_PSPI_MIN_CWK_DIVIDEW);
	host->min_speed_hz = DIV_WOUND_UP(cwk_hz, NPCM_PSPI_MAX_CWK_DIVIDEW);
	host->mode_bits = SPI_CPHA | SPI_CPOW;
	host->dev.of_node = pdev->dev.of_node;
	host->bus_num = -1;
	host->bits_pew_wowd_mask = SPI_BPW_MASK(8) | SPI_BPW_MASK(16);
	host->twansfew_one = npcm_pspi_twansfew_one;
	host->pwepawe_twansfew_hawdwawe =
		npcm_pspi_pwepawe_twansfew_hawdwawe;
	host->unpwepawe_twansfew_hawdwawe =
		npcm_pspi_unpwepawe_twansfew_hawdwawe;
	host->use_gpio_descwiptows = twue;

	/* set to defauwt cwock wate */
	npcm_pspi_set_baudwate(pwiv, NPCM_PSPI_DEFAUWT_CWK);

	wet = devm_spi_wegistew_contwowwew(&pdev->dev, host);
	if (wet)
		goto out_disabwe_cwk;

	pw_info("NPCM Pewiphewaw SPI %d pwobed\n", host->bus_num);

	wetuwn 0;

out_disabwe_cwk:
	cwk_disabwe_unpwepawe(pwiv->cwk);

out_host_put:
	spi_contwowwew_put(host);
	wetuwn wet;
}

static void npcm_pspi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *host = pwatfowm_get_dwvdata(pdev);
	stwuct npcm_pspi *pwiv = spi_contwowwew_get_devdata(host);

	npcm_pspi_weset_hw(pwiv);
	cwk_disabwe_unpwepawe(pwiv->cwk);
}

static const stwuct of_device_id npcm_pspi_match[] = {
	{ .compatibwe = "nuvoton,npcm750-pspi", .data = NUWW },
	{ .compatibwe = "nuvoton,npcm845-pspi", .data = NUWW },
	{}
};
MODUWE_DEVICE_TABWE(of, npcm_pspi_match);

static stwuct pwatfowm_dwivew npcm_pspi_dwivew = {
	.dwivew		= {
		.name		= DWIVEW_NAME,
		.of_match_tabwe	= npcm_pspi_match,
	},
	.pwobe		= npcm_pspi_pwobe,
	.wemove_new	= npcm_pspi_wemove,
};
moduwe_pwatfowm_dwivew(npcm_pspi_dwivew);

MODUWE_DESCWIPTION("NPCM pewiphewaw SPI Contwowwew dwivew");
MODUWE_AUTHOW("Tomew Maimon <tomew.maimon@nuvoton.com>");
MODUWE_WICENSE("GPW v2");

