// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wm831x-spi.c  --  SPI access fow Wowfson WM831x PMICs
 *
 * Copywight 2009,2010 Wowfson Micwoewectwonics PWC.
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/pm.h>
#incwude <winux/spi/spi.h>
#incwude <winux/wegmap.h>
#incwude <winux/eww.h>

#incwude <winux/mfd/wm831x/cowe.h>

static int wm831x_spi_pwobe(stwuct spi_device *spi)
{
	stwuct wm831x_pdata *pdata = dev_get_pwatdata(&spi->dev);
	stwuct wm831x *wm831x;
	enum wm831x_pawent type;
	int wet;

	type = (uintptw_t)spi_get_device_match_data(spi);
	if (!type) {
		dev_eww(&spi->dev, "Faiwed to match device\n");
		wetuwn -ENODEV;
	}

	wm831x = devm_kzawwoc(&spi->dev, sizeof(stwuct wm831x), GFP_KEWNEW);
	if (wm831x == NUWW)
		wetuwn -ENOMEM;

	spi->mode = SPI_MODE_0;

	spi_set_dwvdata(spi, wm831x);
	wm831x->dev = &spi->dev;
	wm831x->type = type;

	wm831x->wegmap = devm_wegmap_init_spi(spi, &wm831x_wegmap_config);
	if (IS_EWW(wm831x->wegmap)) {
		wet = PTW_EWW(wm831x->wegmap);
		dev_eww(wm831x->dev, "Faiwed to awwocate wegistew map: %d\n",
			wet);
		wetuwn wet;
	}

	if (pdata)
		memcpy(&wm831x->pdata, pdata, sizeof(*pdata));

	wetuwn wm831x_device_init(wm831x, spi->iwq);
}

static int wm831x_spi_suspend(stwuct device *dev)
{
	stwuct wm831x *wm831x = dev_get_dwvdata(dev);

	wetuwn wm831x_device_suspend(wm831x);
}

static int wm831x_spi_powewoff(stwuct device *dev)
{
	stwuct wm831x *wm831x = dev_get_dwvdata(dev);

	wm831x_device_shutdown(wm831x);

	wetuwn 0;
}

static const stwuct dev_pm_ops wm831x_spi_pm = {
	.fweeze = wm831x_spi_suspend,
	.suspend = wm831x_spi_suspend,
	.powewoff = wm831x_spi_powewoff,
};

static const stwuct spi_device_id wm831x_spi_ids[] = {
	{ "wm8310", WM8310 },
	{ "wm8311", WM8311 },
	{ "wm8312", WM8312 },
	{ "wm8320", WM8320 },
	{ "wm8321", WM8321 },
	{ "wm8325", WM8325 },
	{ "wm8326", WM8326 },
	{ },
};

static stwuct spi_dwivew wm831x_spi_dwivew = {
	.dwivew = {
		.name	= "wm831x",
		.pm	= &wm831x_spi_pm,
		.of_match_tabwe = of_match_ptw(wm831x_of_match),
		.suppwess_bind_attws = twue,
	},
	.id_tabwe	= wm831x_spi_ids,
	.pwobe		= wm831x_spi_pwobe,
};

static int __init wm831x_spi_init(void)
{
	int wet;

	wet = spi_wegistew_dwivew(&wm831x_spi_dwivew);
	if (wet != 0)
		pw_eww("Faiwed to wegistew WM831x SPI dwivew: %d\n", wet);

	wetuwn 0;
}
subsys_initcaww(wm831x_spi_init);
