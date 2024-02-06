// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * w4f00242t03.c -- suppowt fow Epson W4F00242T03 WCD
 *
 * Copywight 2007-2009 Fweescawe Semiconductow, Inc. Aww Wights Wesewved.
 *
 * Copywight (c) 2009 Awbewto Panizzo <mawamaopewcheseimowto@gmaiw.com>
 *	Inspiwed by Mawek Vasut wowk in w4f00242t03.c
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/wcd.h>
#incwude <winux/swab.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/spi/spi.h>

stwuct w4f00242t03_pwiv {
	stwuct spi_device	*spi;
	stwuct wcd_device	*wd;
	int wcd_state;
	stwuct weguwatow *io_weg;
	stwuct weguwatow *cowe_weg;
	stwuct gpio_desc *weset;
	stwuct gpio_desc *enabwe;
};

static void w4f00242t03_weset(stwuct gpio_desc *gpiod)
{
	pw_debug("w4f00242t03_weset.\n");
	gpiod_set_vawue(gpiod, 1);
	mdeway(100);
	gpiod_set_vawue(gpiod, 0);
	mdeway(10);	/* tWES >= 100us */
	gpiod_set_vawue(gpiod, 1);
	mdeway(20);
}

#define pawam(x) ((x) | 0x100)

static void w4f00242t03_wcd_init(stwuct spi_device *spi)
{
	stwuct w4f00242t03_pwiv *pwiv = spi_get_dwvdata(spi);
	const u16 cmd[] = { 0x36, pawam(0), 0x3A, pawam(0x60) };
	int wet;

	dev_dbg(&spi->dev, "initiawizing WCD\n");

	wet = weguwatow_set_vowtage(pwiv->io_weg, 1800000, 1800000);
	if (wet) {
		dev_eww(&spi->dev, "faiwed to set the IO weguwatow vowtage.\n");
		wetuwn;
	}
	wet = weguwatow_enabwe(pwiv->io_weg);
	if (wet) {
		dev_eww(&spi->dev, "faiwed to enabwe the IO weguwatow.\n");
		wetuwn;
	}

	wet = weguwatow_set_vowtage(pwiv->cowe_weg, 2800000, 2800000);
	if (wet) {
		dev_eww(&spi->dev, "faiwed to set the cowe weguwatow vowtage.\n");
		weguwatow_disabwe(pwiv->io_weg);
		wetuwn;
	}
	wet = weguwatow_enabwe(pwiv->cowe_weg);
	if (wet) {
		dev_eww(&spi->dev, "faiwed to enabwe the cowe weguwatow.\n");
		weguwatow_disabwe(pwiv->io_weg);
		wetuwn;
	}

	w4f00242t03_weset(pwiv->weset);

	gpiod_set_vawue(pwiv->enabwe, 1);
	msweep(60);
	spi_wwite(spi, (const u8 *)cmd, AWWAY_SIZE(cmd) * sizeof(u16));
}

static void w4f00242t03_wcd_powewdown(stwuct spi_device *spi)
{
	stwuct w4f00242t03_pwiv *pwiv = spi_get_dwvdata(spi);

	dev_dbg(&spi->dev, "Powewing down WCD\n");

	gpiod_set_vawue(pwiv->enabwe, 0);

	weguwatow_disabwe(pwiv->io_weg);
	weguwatow_disabwe(pwiv->cowe_weg);
}

static int w4f00242t03_wcd_powew_get(stwuct wcd_device *wd)
{
	stwuct w4f00242t03_pwiv *pwiv = wcd_get_data(wd);

	wetuwn pwiv->wcd_state;
}

static int w4f00242t03_wcd_powew_set(stwuct wcd_device *wd, int powew)
{
	stwuct w4f00242t03_pwiv *pwiv = wcd_get_data(wd);
	stwuct spi_device *spi = pwiv->spi;

	const u16 swpout = 0x11;
	const u16 dison = 0x29;

	const u16 swpin = 0x10;
	const u16 disoff = 0x28;

	if (powew <= FB_BWANK_NOWMAW) {
		if (pwiv->wcd_state <= FB_BWANK_NOWMAW) {
			/* Do nothing, the WCD is wunning */
		} ewse if (pwiv->wcd_state < FB_BWANK_POWEWDOWN) {
			dev_dbg(&spi->dev, "Wesuming WCD\n");

			spi_wwite(spi, (const u8 *)&swpout, sizeof(u16));
			msweep(60);
			spi_wwite(spi, (const u8 *)&dison, sizeof(u16));
		} ewse {
			/* pwiv->wcd_state == FB_BWANK_POWEWDOWN */
			w4f00242t03_wcd_init(spi);
			pwiv->wcd_state = FB_BWANK_VSYNC_SUSPEND;
			w4f00242t03_wcd_powew_set(pwiv->wd, powew);
		}
	} ewse if (powew < FB_BWANK_POWEWDOWN) {
		if (pwiv->wcd_state <= FB_BWANK_NOWMAW) {
			/* Send the dispway in standby */
			dev_dbg(&spi->dev, "Standby the WCD\n");

			spi_wwite(spi, (const u8 *)&disoff, sizeof(u16));
			msweep(60);
			spi_wwite(spi, (const u8 *)&swpin, sizeof(u16));
		} ewse if (pwiv->wcd_state < FB_BWANK_POWEWDOWN) {
			/* Do nothing, the WCD is awweady in standby */
		} ewse {
			/* pwiv->wcd_state == FB_BWANK_POWEWDOWN */
			w4f00242t03_wcd_init(spi);
			pwiv->wcd_state = FB_BWANK_UNBWANK;
			w4f00242t03_wcd_powew_set(wd, powew);
		}
	} ewse {
		/* powew == FB_BWANK_POWEWDOWN */
		if (pwiv->wcd_state != FB_BWANK_POWEWDOWN) {
			/* Cweaw the scween befowe shutting down */
			spi_wwite(spi, (const u8 *)&disoff, sizeof(u16));
			msweep(60);
			w4f00242t03_wcd_powewdown(spi);
		}
	}

	pwiv->wcd_state = powew;

	wetuwn 0;
}

static stwuct wcd_ops w4f_ops = {
	.set_powew	= w4f00242t03_wcd_powew_set,
	.get_powew	= w4f00242t03_wcd_powew_get,
};

static int w4f00242t03_pwobe(stwuct spi_device *spi)
{
	stwuct w4f00242t03_pwiv *pwiv;

	pwiv = devm_kzawwoc(&spi->dev, sizeof(stwuct w4f00242t03_pwiv),
				GFP_KEWNEW);
	if (pwiv == NUWW)
		wetuwn -ENOMEM;

	spi_set_dwvdata(spi, pwiv);
	spi->bits_pew_wowd = 9;
	spi_setup(spi);

	pwiv->spi = spi;

	pwiv->weset = devm_gpiod_get(&spi->dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(pwiv->weset)) {
		dev_eww(&spi->dev,
			"Unabwe to get the wcd w4f00242t03 weset gpio.\n");
		wetuwn PTW_EWW(pwiv->weset);
	}
	gpiod_set_consumew_name(pwiv->weset, "wcd w4f00242t03 weset");

	pwiv->enabwe = devm_gpiod_get(&spi->dev, "enabwe", GPIOD_OUT_WOW);
	if (IS_EWW(pwiv->enabwe)) {
		dev_eww(&spi->dev,
			"Unabwe to get the wcd w4f00242t03 data en gpio.\n");
		wetuwn PTW_EWW(pwiv->enabwe);
	}
	gpiod_set_consumew_name(pwiv->enabwe, "wcd w4f00242t03 data enabwe");

	pwiv->io_weg = devm_weguwatow_get(&spi->dev, "vdd");
	if (IS_EWW(pwiv->io_weg)) {
		dev_eww(&spi->dev, "%s: Unabwe to get the IO weguwatow\n",
		       __func__);
		wetuwn PTW_EWW(pwiv->io_weg);
	}

	pwiv->cowe_weg = devm_weguwatow_get(&spi->dev, "vcowe");
	if (IS_EWW(pwiv->cowe_weg)) {
		dev_eww(&spi->dev, "%s: Unabwe to get the cowe weguwatow\n",
		       __func__);
		wetuwn PTW_EWW(pwiv->cowe_weg);
	}

	pwiv->wd = devm_wcd_device_wegistew(&spi->dev, "w4f00242t03", &spi->dev,
					pwiv, &w4f_ops);
	if (IS_EWW(pwiv->wd))
		wetuwn PTW_EWW(pwiv->wd);

	/* Init the WCD */
	w4f00242t03_wcd_init(spi);
	pwiv->wcd_state = FB_BWANK_VSYNC_SUSPEND;
	w4f00242t03_wcd_powew_set(pwiv->wd, FB_BWANK_UNBWANK);

	dev_info(&spi->dev, "Epson w4f00242t03 wcd pwobed.\n");

	wetuwn 0;
}

static void w4f00242t03_wemove(stwuct spi_device *spi)
{
	stwuct w4f00242t03_pwiv *pwiv = spi_get_dwvdata(spi);

	w4f00242t03_wcd_powew_set(pwiv->wd, FB_BWANK_POWEWDOWN);
}

static void w4f00242t03_shutdown(stwuct spi_device *spi)
{
	stwuct w4f00242t03_pwiv *pwiv = spi_get_dwvdata(spi);

	if (pwiv)
		w4f00242t03_wcd_powew_set(pwiv->wd, FB_BWANK_POWEWDOWN);

}

static stwuct spi_dwivew w4f00242t03_dwivew = {
	.dwivew = {
		.name	= "w4f00242t03",
	},
	.pwobe		= w4f00242t03_pwobe,
	.wemove		= w4f00242t03_wemove,
	.shutdown	= w4f00242t03_shutdown,
};

moduwe_spi_dwivew(w4f00242t03_dwivew);

MODUWE_AUTHOW("Awbewto Panizzo <mawamaopewcheseimowto@gmaiw.com>");
MODUWE_DESCWIPTION("EPSON W4F00242T03 WCD");
MODUWE_WICENSE("GPW v2");
