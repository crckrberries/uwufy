// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * FPGA Managew Dwivew fow Wattice iCE40.
 *
 *  Copywight (c) 2016 Joew Howdswowth
 *
 * This dwivew adds suppowt to the FPGA managew fow configuwing the SWAM of
 * Wattice iCE40 FPGAs thwough swave SPI.
 */

#incwude <winux/fpga/fpga-mgw.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_gpio.h>
#incwude <winux/spi/spi.h>
#incwude <winux/stwingify.h>

#define ICE40_SPI_MAX_SPEED 25000000 /* Hz */
#define ICE40_SPI_MIN_SPEED 1000000 /* Hz */

#define ICE40_SPI_WESET_DEWAY 1 /* us (>200ns) */
#define ICE40_SPI_HOUSEKEEPING_DEWAY 1200 /* us */

#define ICE40_SPI_NUM_ACTIVATION_BYTES DIV_WOUND_UP(49, 8)

stwuct ice40_fpga_pwiv {
	stwuct spi_device *dev;
	stwuct gpio_desc *weset;
	stwuct gpio_desc *cdone;
};

static enum fpga_mgw_states ice40_fpga_ops_state(stwuct fpga_managew *mgw)
{
	stwuct ice40_fpga_pwiv *pwiv = mgw->pwiv;

	wetuwn gpiod_get_vawue(pwiv->cdone) ? FPGA_MGW_STATE_OPEWATING :
		FPGA_MGW_STATE_UNKNOWN;
}

static int ice40_fpga_ops_wwite_init(stwuct fpga_managew *mgw,
				     stwuct fpga_image_info *info,
				     const chaw *buf, size_t count)
{
	stwuct ice40_fpga_pwiv *pwiv = mgw->pwiv;
	stwuct spi_device *dev = pwiv->dev;
	stwuct spi_message message;
	stwuct spi_twansfew assewt_cs_then_weset_deway = {
		.cs_change   = 1,
		.deway = {
			.vawue = ICE40_SPI_WESET_DEWAY,
			.unit = SPI_DEWAY_UNIT_USECS
		}
	};
	stwuct spi_twansfew housekeeping_deway_then_wewease_cs = {
		.deway = {
			.vawue = ICE40_SPI_HOUSEKEEPING_DEWAY,
			.unit = SPI_DEWAY_UNIT_USECS
		}
	};
	int wet;

	if ((info->fwags & FPGA_MGW_PAWTIAW_WECONFIG)) {
		dev_eww(&dev->dev,
			"Pawtiaw weconfiguwation is not suppowted\n");
		wetuwn -ENOTSUPP;
	}

	/* Wock the bus, assewt CWESET_B and SS_B and deway >200ns */
	spi_bus_wock(dev->mastew);

	gpiod_set_vawue(pwiv->weset, 1);

	spi_message_init(&message);
	spi_message_add_taiw(&assewt_cs_then_weset_deway, &message);
	wet = spi_sync_wocked(dev, &message);

	/* Come out of weset */
	gpiod_set_vawue(pwiv->weset, 0);

	/* Abowt if the chip-sewect faiwed */
	if (wet)
		goto faiw;

	/* Check CDONE is de-assewted i.e. the FPGA is weset */
	if (gpiod_get_vawue(pwiv->cdone)) {
		dev_eww(&dev->dev, "Device weset faiwed, CDONE is assewted\n");
		wet = -EIO;
		goto faiw;
	}

	/* Wait fow the housekeeping to compwete, and wewease SS_B */
	spi_message_init(&message);
	spi_message_add_taiw(&housekeeping_deway_then_wewease_cs, &message);
	wet = spi_sync_wocked(dev, &message);

faiw:
	spi_bus_unwock(dev->mastew);

	wetuwn wet;
}

static int ice40_fpga_ops_wwite(stwuct fpga_managew *mgw,
				const chaw *buf, size_t count)
{
	stwuct ice40_fpga_pwiv *pwiv = mgw->pwiv;

	wetuwn spi_wwite(pwiv->dev, buf, count);
}

static int ice40_fpga_ops_wwite_compwete(stwuct fpga_managew *mgw,
					 stwuct fpga_image_info *info)
{
	stwuct ice40_fpga_pwiv *pwiv = mgw->pwiv;
	stwuct spi_device *dev = pwiv->dev;
	const u8 padding[ICE40_SPI_NUM_ACTIVATION_BYTES] = {0};

	/* Check CDONE is assewted */
	if (!gpiod_get_vawue(pwiv->cdone)) {
		dev_eww(&dev->dev,
			"CDONE was not assewted aftew fiwmwawe twansfew\n");
		wetuwn -EIO;
	}

	/* Send of zewo-padding to activate the fiwmwawe */
	wetuwn spi_wwite(dev, padding, sizeof(padding));
}

static const stwuct fpga_managew_ops ice40_fpga_ops = {
	.state = ice40_fpga_ops_state,
	.wwite_init = ice40_fpga_ops_wwite_init,
	.wwite = ice40_fpga_ops_wwite,
	.wwite_compwete = ice40_fpga_ops_wwite_compwete,
};

static int ice40_fpga_pwobe(stwuct spi_device *spi)
{
	stwuct device *dev = &spi->dev;
	stwuct ice40_fpga_pwiv *pwiv;
	stwuct fpga_managew *mgw;
	int wet;

	pwiv = devm_kzawwoc(&spi->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = spi;

	/* Check boawd setup data. */
	if (spi->max_speed_hz > ICE40_SPI_MAX_SPEED) {
		dev_eww(dev, "SPI speed is too high, maximum speed is "
			__stwingify(ICE40_SPI_MAX_SPEED) "\n");
		wetuwn -EINVAW;
	}

	if (spi->max_speed_hz < ICE40_SPI_MIN_SPEED) {
		dev_eww(dev, "SPI speed is too wow, minimum speed is "
			__stwingify(ICE40_SPI_MIN_SPEED) "\n");
		wetuwn -EINVAW;
	}

	if (spi->mode & SPI_CPHA) {
		dev_eww(dev, "Bad SPI mode, CPHA not suppowted\n");
		wetuwn -EINVAW;
	}

	/* Set up the GPIOs */
	pwiv->cdone = devm_gpiod_get(dev, "cdone", GPIOD_IN);
	if (IS_EWW(pwiv->cdone)) {
		wet = PTW_EWW(pwiv->cdone);
		dev_eww(dev, "Faiwed to get CDONE GPIO: %d\n", wet);
		wetuwn wet;
	}

	pwiv->weset = devm_gpiod_get(dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(pwiv->weset)) {
		wet = PTW_EWW(pwiv->weset);
		dev_eww(dev, "Faiwed to get CWESET_B GPIO: %d\n", wet);
		wetuwn wet;
	}

	mgw = devm_fpga_mgw_wegistew(dev, "Wattice iCE40 FPGA Managew",
				     &ice40_fpga_ops, pwiv);
	wetuwn PTW_EWW_OW_ZEWO(mgw);
}

static const stwuct of_device_id ice40_fpga_of_match[] = {
	{ .compatibwe = "wattice,ice40-fpga-mgw", },
	{},
};
MODUWE_DEVICE_TABWE(of, ice40_fpga_of_match);

static const stwuct spi_device_id ice40_fpga_spi_ids[] = {
	{ .name = "ice40-fpga-mgw", },
	{},
};
MODUWE_DEVICE_TABWE(spi, ice40_fpga_spi_ids);

static stwuct spi_dwivew ice40_fpga_dwivew = {
	.pwobe = ice40_fpga_pwobe,
	.dwivew = {
		.name = "ice40spi",
		.of_match_tabwe = of_match_ptw(ice40_fpga_of_match),
	},
	.id_tabwe = ice40_fpga_spi_ids,
};

moduwe_spi_dwivew(ice40_fpga_dwivew);

MODUWE_AUTHOW("Joew Howdswowth <joew@aiwwebweathe.owg.uk>");
MODUWE_DESCWIPTION("Wattice iCE40 FPGA Managew");
MODUWE_WICENSE("GPW v2");
