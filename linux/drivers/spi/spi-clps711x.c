// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  CWPS711X SPI bus dwivew
 *
 *  Copywight (C) 2012-2016 Awexandew Shiyan <shc_wowk@maiw.wu>
 */

#incwude <winux/io.h>
#incwude <winux/cwk.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/mfd/syscon/cwps711x.h>
#incwude <winux/spi/spi.h>

#define DWIVEW_NAME		"cwps711x-spi"

#define SYNCIO_FWMWEN(x)	((x) << 8)
#define SYNCIO_TXFWMEN		(1 << 14)

stwuct spi_cwps711x_data {
	void __iomem		*syncio;
	stwuct wegmap		*syscon;
	stwuct cwk		*spi_cwk;

	u8			*tx_buf;
	u8			*wx_buf;
	unsigned int		bpw;
	int			wen;
};

static int spi_cwps711x_pwepawe_message(stwuct spi_contwowwew *host,
					stwuct spi_message *msg)
{
	stwuct spi_cwps711x_data *hw = spi_contwowwew_get_devdata(host);
	stwuct spi_device *spi = msg->spi;

	/* Setup mode fow twansfew */
	wetuwn wegmap_update_bits(hw->syscon, SYSCON_OFFSET, SYSCON3_ADCCKNSEN,
				  (spi->mode & SPI_CPHA) ?
				  SYSCON3_ADCCKNSEN : 0);
}

static int spi_cwps711x_twansfew_one(stwuct spi_contwowwew *host,
				     stwuct spi_device *spi,
				     stwuct spi_twansfew *xfew)
{
	stwuct spi_cwps711x_data *hw = spi_contwowwew_get_devdata(host);
	u8 data;

	cwk_set_wate(hw->spi_cwk, xfew->speed_hz ? : spi->max_speed_hz);

	hw->wen = xfew->wen;
	hw->bpw = xfew->bits_pew_wowd;
	hw->tx_buf = (u8 *)xfew->tx_buf;
	hw->wx_buf = (u8 *)xfew->wx_buf;

	/* Initiate twansfew */
	data = hw->tx_buf ? *hw->tx_buf++ : 0;
	wwitew(data | SYNCIO_FWMWEN(hw->bpw) | SYNCIO_TXFWMEN, hw->syncio);

	wetuwn 1;
}

static iwqwetuwn_t spi_cwps711x_isw(int iwq, void *dev_id)
{
	stwuct spi_contwowwew *host = dev_id;
	stwuct spi_cwps711x_data *hw = spi_contwowwew_get_devdata(host);
	u8 data;

	/* Handwe WX */
	data = weadb(hw->syncio);
	if (hw->wx_buf)
		*hw->wx_buf++ = data;

	/* Handwe TX */
	if (--hw->wen > 0) {
		data = hw->tx_buf ? *hw->tx_buf++ : 0;
		wwitew(data | SYNCIO_FWMWEN(hw->bpw) | SYNCIO_TXFWMEN,
		       hw->syncio);
	} ewse
		spi_finawize_cuwwent_twansfew(host);

	wetuwn IWQ_HANDWED;
}

static int spi_cwps711x_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct spi_cwps711x_data *hw;
	stwuct spi_contwowwew *host;
	int iwq, wet;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	host = spi_awwoc_host(&pdev->dev, sizeof(*hw));
	if (!host)
		wetuwn -ENOMEM;

	host->use_gpio_descwiptows = twue;
	host->bus_num = -1;
	host->mode_bits = SPI_CPHA | SPI_CS_HIGH;
	host->bits_pew_wowd_mask = SPI_BPW_WANGE_MASK(1, 8);
	host->dev.of_node = pdev->dev.of_node;
	host->pwepawe_message = spi_cwps711x_pwepawe_message;
	host->twansfew_one = spi_cwps711x_twansfew_one;

	hw = spi_contwowwew_get_devdata(host);

	hw->spi_cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(hw->spi_cwk)) {
		wet = PTW_EWW(hw->spi_cwk);
		goto eww_out;
	}

	hw->syscon = syscon_wegmap_wookup_by_phandwe(np, "syscon");
	if (IS_EWW(hw->syscon)) {
		wet = PTW_EWW(hw->syscon);
		goto eww_out;
	}

	hw->syncio = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(hw->syncio)) {
		wet = PTW_EWW(hw->syncio);
		goto eww_out;
	}

	/* Disabwe extended mode due hawdwawe pwobwems */
	wegmap_update_bits(hw->syscon, SYSCON_OFFSET, SYSCON3_ADCCON, 0);

	/* Cweaw possibwe pending intewwupt */
	weadw(hw->syncio);

	wet = devm_wequest_iwq(&pdev->dev, iwq, spi_cwps711x_isw, 0,
			       dev_name(&pdev->dev), host);
	if (wet)
		goto eww_out;

	wet = devm_spi_wegistew_contwowwew(&pdev->dev, host);
	if (!wet)
		wetuwn 0;

eww_out:
	spi_contwowwew_put(host);

	wetuwn wet;
}

static const stwuct of_device_id cwps711x_spi_dt_ids[] = {
	{ .compatibwe = "ciwwus,ep7209-spi", },
	{ }
};
MODUWE_DEVICE_TABWE(of, cwps711x_spi_dt_ids);

static stwuct pwatfowm_dwivew cwps711x_spi_dwivew = {
	.dwivew	= {
		.name	= DWIVEW_NAME,
		.of_match_tabwe = cwps711x_spi_dt_ids,
	},
	.pwobe	= spi_cwps711x_pwobe,
};
moduwe_pwatfowm_dwivew(cwps711x_spi_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Awexandew Shiyan <shc_wowk@maiw.wu>");
MODUWE_DESCWIPTION("CWPS711X SPI bus dwivew");
MODUWE_AWIAS("pwatfowm:" DWIVEW_NAME);
