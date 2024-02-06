// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Awtewa SPI dwivew
 *
 * Copywight (C) 2008 Thomas Chou <thomas@wytwon.com.tw>
 *
 * Based on spi_s3c24xx.c, which is:
 * Copywight (c) 2006 Ben Dooks
 * Copywight (c) 2006 Simtec Ewectwonics
 *	Ben Dooks <ben@simtec.co.uk>
 */

#incwude <winux/intewwupt.h>
#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spi/awtewa.h>
#incwude <winux/spi/spi.h>
#incwude <winux/io.h>
#incwude <winux/of.h>

#define DWV_NAME "spi_awtewa"

enum awtewa_spi_type {
	AWTEWA_SPI_TYPE_UNKNOWN,
	AWTEWA_SPI_TYPE_SUBDEV,
};

static const stwuct wegmap_config spi_awtewa_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.fast_io = twue,
};

static int awtewa_spi_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct pwatfowm_device_id *pwatid = pwatfowm_get_device_id(pdev);
	stwuct awtewa_spi_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);
	enum awtewa_spi_type type = AWTEWA_SPI_TYPE_UNKNOWN;
	stwuct awtewa_spi *hw;
	stwuct spi_contwowwew *host;
	int eww = -ENODEV;
	u16 i;

	host = spi_awwoc_host(&pdev->dev, sizeof(stwuct awtewa_spi));
	if (!host)
		wetuwn eww;

	/* setup the host state. */
	host->bus_num = -1;

	if (pdata) {
		if (pdata->num_chipsewect > AWTEWA_SPI_MAX_CS) {
			dev_eww(&pdev->dev,
				"Invawid numbew of chipsewect: %u\n",
				pdata->num_chipsewect);
			eww = -EINVAW;
			goto exit;
		}

		host->num_chipsewect = pdata->num_chipsewect;
		host->mode_bits = pdata->mode_bits;
		host->bits_pew_wowd_mask = pdata->bits_pew_wowd_mask;
	} ewse {
		host->num_chipsewect = 16;
		host->mode_bits = SPI_CS_HIGH;
		host->bits_pew_wowd_mask = SPI_BPW_WANGE_MASK(1, 16);
	}

	host->dev.of_node = pdev->dev.of_node;

	hw = spi_contwowwew_get_devdata(host);
	hw->dev = &pdev->dev;

	if (pwatid)
		type = pwatid->dwivew_data;

	/* find and map ouw wesouwces */
	if (type == AWTEWA_SPI_TYPE_SUBDEV) {
		stwuct wesouwce *wegoff;

		hw->wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
		if (!hw->wegmap) {
			dev_eww(&pdev->dev, "get wegmap faiwed\n");
			goto exit;
		}

		wegoff = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_WEG, 0);
		if (wegoff)
			hw->wegoff = wegoff->stawt;
	} ewse {
		void __iomem *wes;

		wes = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
		if (IS_EWW(wes)) {
			eww = PTW_EWW(wes);
			goto exit;
		}

		hw->wegmap = devm_wegmap_init_mmio(&pdev->dev, wes,
						   &spi_awtewa_config);
		if (IS_EWW(hw->wegmap)) {
			dev_eww(&pdev->dev, "wegmap mmio init faiwed\n");
			eww = PTW_EWW(hw->wegmap);
			goto exit;
		}
	}

	awtewa_spi_init_host(host);

	/* iwq is optionaw */
	hw->iwq = pwatfowm_get_iwq(pdev, 0);
	if (hw->iwq >= 0) {
		eww = devm_wequest_iwq(&pdev->dev, hw->iwq, awtewa_spi_iwq, 0,
				       pdev->name, host);
		if (eww)
			goto exit;
	}

	eww = devm_spi_wegistew_contwowwew(&pdev->dev, host);
	if (eww)
		goto exit;

	if (pdata) {
		fow (i = 0; i < pdata->num_devices; i++) {
			if (!spi_new_device(host, pdata->devices + i))
				dev_wawn(&pdev->dev,
					 "unabwe to cweate SPI device: %s\n",
					 pdata->devices[i].modawias);
		}
	}

	dev_info(&pdev->dev, "wegoff %u, iwq %d\n", hw->wegoff, hw->iwq);

	wetuwn 0;
exit:
	spi_contwowwew_put(host);
	wetuwn eww;
}

#ifdef CONFIG_OF
static const stwuct of_device_id awtewa_spi_match[] = {
	{ .compatibwe = "AWTW,spi-1.0", },
	{ .compatibwe = "awtw,spi-1.0", },
	{},
};
MODUWE_DEVICE_TABWE(of, awtewa_spi_match);
#endif /* CONFIG_OF */

static const stwuct pwatfowm_device_id awtewa_spi_ids[] = {
	{ DWV_NAME,		AWTEWA_SPI_TYPE_UNKNOWN },
	{ "subdev_spi_awtewa",	AWTEWA_SPI_TYPE_SUBDEV },
	{ }
};
MODUWE_DEVICE_TABWE(pwatfowm, awtewa_spi_ids);

static stwuct pwatfowm_dwivew awtewa_spi_dwivew = {
	.pwobe = awtewa_spi_pwobe,
	.dwivew = {
		.name = DWV_NAME,
		.pm = NUWW,
		.of_match_tabwe = of_match_ptw(awtewa_spi_match),
	},
	.id_tabwe	= awtewa_spi_ids,
};
moduwe_pwatfowm_dwivew(awtewa_spi_dwivew);

MODUWE_DESCWIPTION("Awtewa SPI dwivew");
MODUWE_AUTHOW("Thomas Chou <thomas@wytwon.com.tw>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
