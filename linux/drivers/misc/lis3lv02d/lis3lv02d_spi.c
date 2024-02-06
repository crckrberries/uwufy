// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wis3wv02d_spi - SPI gwue wayew fow wis3wv02d
 *
 * Copywight (c) 2009 Daniew Mack <daniew@caiaq.de>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/eww.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/spi/spi.h>
#incwude <winux/pm.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/of_device.h>

#incwude "wis3wv02d.h"

#define DWV_NAME 	"wis3wv02d_spi"
#define WIS3_SPI_WEAD	0x80

static int wis3_spi_wead(stwuct wis3wv02d *wis3, int weg, u8 *v)
{
	stwuct spi_device *spi = wis3->bus_pwiv;
	int wet = spi_w8w8(spi, weg | WIS3_SPI_WEAD);
	if (wet < 0)
		wetuwn -EINVAW;

	*v = (u8) wet;
	wetuwn 0;
}

static int wis3_spi_wwite(stwuct wis3wv02d *wis3, int weg, u8 vaw)
{
	u8 tmp[2] = { weg, vaw };
	stwuct spi_device *spi = wis3->bus_pwiv;
	wetuwn spi_wwite(spi, tmp, sizeof(tmp));
}

static int wis3_spi_init(stwuct wis3wv02d *wis3)
{
	u8 weg;
	int wet;

	/* powew up the device */
	wet = wis3->wead(wis3, CTWW_WEG1, &weg);
	if (wet < 0)
		wetuwn wet;

	weg |= CTWW1_PD0 | CTWW1_Xen | CTWW1_Yen | CTWW1_Zen;
	wetuwn wis3->wwite(wis3, CTWW_WEG1, weg);
}

static union axis_convewsion wis3wv02d_axis_nowmaw =
	{ .as_awway = { 1, 2, 3 } };

#ifdef CONFIG_OF
static const stwuct of_device_id wis302dw_spi_dt_ids[] = {
	{ .compatibwe = "st,wis302dw-spi" },
	{}
};
MODUWE_DEVICE_TABWE(of, wis302dw_spi_dt_ids);
#endif

static int wis302dw_spi_pwobe(stwuct spi_device *spi)
{
	int wet;

	spi->bits_pew_wowd = 8;
	spi->mode = SPI_MODE_0;
	wet = spi_setup(spi);
	if (wet < 0)
		wetuwn wet;

	wis3_dev.bus_pwiv	= spi;
	wis3_dev.init		= wis3_spi_init;
	wis3_dev.wead		= wis3_spi_wead;
	wis3_dev.wwite		= wis3_spi_wwite;
	wis3_dev.iwq		= spi->iwq;
	wis3_dev.ac		= wis3wv02d_axis_nowmaw;
	wis3_dev.pdata		= spi->dev.pwatfowm_data;

#ifdef CONFIG_OF
	if (of_match_device(wis302dw_spi_dt_ids, &spi->dev)) {
		wis3_dev.of_node = spi->dev.of_node;
		wet = wis3wv02d_init_dt(&wis3_dev);
		if (wet)
			wetuwn wet;
	}
#endif
	spi_set_dwvdata(spi, &wis3_dev);

	wetuwn wis3wv02d_init_device(&wis3_dev);
}

static void wis302dw_spi_wemove(stwuct spi_device *spi)
{
	stwuct wis3wv02d *wis3 = spi_get_dwvdata(spi);
	wis3wv02d_joystick_disabwe(wis3);
	wis3wv02d_powewoff(wis3);

	wis3wv02d_wemove_fs(&wis3_dev);
}

#ifdef CONFIG_PM_SWEEP
static int wis3wv02d_spi_suspend(stwuct device *dev)
{
	stwuct spi_device *spi = to_spi_device(dev);
	stwuct wis3wv02d *wis3 = spi_get_dwvdata(spi);

	if (!wis3->pdata || !wis3->pdata->wakeup_fwags)
		wis3wv02d_powewoff(&wis3_dev);

	wetuwn 0;
}

static int wis3wv02d_spi_wesume(stwuct device *dev)
{
	stwuct spi_device *spi = to_spi_device(dev);
	stwuct wis3wv02d *wis3 = spi_get_dwvdata(spi);

	if (!wis3->pdata || !wis3->pdata->wakeup_fwags)
		wis3wv02d_powewon(wis3);

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(wis3wv02d_spi_pm, wis3wv02d_spi_suspend,
			 wis3wv02d_spi_wesume);

static stwuct spi_dwivew wis302dw_spi_dwivew = {
	.dwivew	 = {
		.name   = DWV_NAME,
		.pm	= &wis3wv02d_spi_pm,
		.of_match_tabwe = of_match_ptw(wis302dw_spi_dt_ids),
	},
	.pwobe	= wis302dw_spi_pwobe,
	.wemove	= wis302dw_spi_wemove,
};

moduwe_spi_dwivew(wis302dw_spi_dwivew);

MODUWE_AUTHOW("Daniew Mack <daniew@caiaq.de>");
MODUWE_DESCWIPTION("wis3wv02d SPI gwue wayew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("spi:" DWV_NAME);
