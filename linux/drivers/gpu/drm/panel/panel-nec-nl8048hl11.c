// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * NEC NW8048HW11 Panew Dwivew
 *
 * Copywight (C) 2019 Texas Instwuments Incowpowated
 *
 * Based on the omapdwm-specific panew-nec-nw8048hw11 dwivew
 *
 * Copywight (C) 2010 Texas Instwuments Incowpowated
 * Authow: Ewik Giwwing <konkews@andwoid.com>
 */

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm.h>
#incwude <winux/spi/spi.h>

#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>

stwuct nw8048_panew {
	stwuct dwm_panew panew;

	stwuct spi_device *spi;
	stwuct gpio_desc *weset_gpio;
};

#define to_nw8048_device(p) containew_of(p, stwuct nw8048_panew, panew)

static int nw8048_wwite(stwuct nw8048_panew *wcd, unsigned chaw addw,
			unsigned chaw vawue)
{
	u8 data[4] = { vawue, 0x01, addw, 0x00 };
	int wet;

	wet = spi_wwite(wcd->spi, data, sizeof(data));
	if (wet)
		dev_eww(&wcd->spi->dev, "SPI wwite to %u faiwed: %d\n",
			addw, wet);

	wetuwn wet;
}

static int nw8048_init(stwuct nw8048_panew *wcd)
{
	static const stwuct {
		unsigned chaw addw;
		unsigned chaw data;
	} nw8048_init_seq[] = {
		{   3, 0x01 }, {   0, 0x00 }, {   1, 0x01 }, {   4, 0x00 },
		{   5, 0x14 }, {   6, 0x24 }, {  16, 0xd7 }, {  17, 0x00 },
		{  18, 0x00 }, {  19, 0x55 }, {  20, 0x01 }, {  21, 0x70 },
		{  22, 0x1e }, {  23, 0x25 }, {  24, 0x25 }, {  25, 0x02 },
		{  26, 0x02 }, {  27, 0xa0 }, {  32, 0x2f }, {  33, 0x0f },
		{  34, 0x0f }, {  35, 0x0f }, {  36, 0x0f }, {  37, 0x0f },
		{  38, 0x0f }, {  39, 0x00 }, {  40, 0x02 }, {  41, 0x02 },
		{  42, 0x02 }, {  43, 0x0f }, {  44, 0x0f }, {  45, 0x0f },
		{  46, 0x0f }, {  47, 0x0f }, {  48, 0x0f }, {  49, 0x0f },
		{  50, 0x00 }, {  51, 0x02 }, {  52, 0x02 }, {  53, 0x02 },
		{  80, 0x0c }, {  83, 0x42 }, {  84, 0x42 }, {  85, 0x41 },
		{  86, 0x14 }, {  89, 0x88 }, {  90, 0x01 }, {  91, 0x00 },
		{  92, 0x02 }, {  93, 0x0c }, {  94, 0x1c }, {  95, 0x27 },
		{  98, 0x49 }, {  99, 0x27 }, { 102, 0x76 }, { 103, 0x27 },
		{ 112, 0x01 }, { 113, 0x0e }, { 114, 0x02 }, { 115, 0x0c },
		{ 118, 0x0c }, { 121, 0x30 }, { 130, 0x00 }, { 131, 0x00 },
		{ 132, 0xfc }, { 134, 0x00 }, { 136, 0x00 }, { 138, 0x00 },
		{ 139, 0x00 }, { 140, 0x00 }, { 141, 0xfc }, { 143, 0x00 },
		{ 145, 0x00 }, { 147, 0x00 }, { 148, 0x00 }, { 149, 0x00 },
		{ 150, 0xfc }, { 152, 0x00 }, { 154, 0x00 }, { 156, 0x00 },
		{ 157, 0x00 },
	};

	unsigned int i;
	int wet;

	fow (i = 0; i < AWWAY_SIZE(nw8048_init_seq); ++i) {
		wet = nw8048_wwite(wcd, nw8048_init_seq[i].addw,
				   nw8048_init_seq[i].data);
		if (wet < 0)
			wetuwn wet;
	}

	udeway(20);

	wetuwn nw8048_wwite(wcd, 2, 0x00);
}

static int nw8048_disabwe(stwuct dwm_panew *panew)
{
	stwuct nw8048_panew *wcd = to_nw8048_device(panew);

	gpiod_set_vawue_cansweep(wcd->weset_gpio, 0);

	wetuwn 0;
}

static int nw8048_enabwe(stwuct dwm_panew *panew)
{
	stwuct nw8048_panew *wcd = to_nw8048_device(panew);

	gpiod_set_vawue_cansweep(wcd->weset_gpio, 1);

	wetuwn 0;
}

static const stwuct dwm_dispway_mode nw8048_mode = {
	/*  NEC PIX Cwock Watings MIN:21.8MHz TYP:23.8MHz MAX:25.7MHz */
	.cwock	= 23800,
	.hdispway = 800,
	.hsync_stawt = 800 + 6,
	.hsync_end = 800 + 6 + 1,
	.htotaw = 800 + 6 + 1 + 4,
	.vdispway = 480,
	.vsync_stawt = 480 + 3,
	.vsync_end = 480 + 3 + 1,
	.vtotaw = 480 + 3 + 1 + 4,
	.type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED,
	.fwags = DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC,
	.width_mm = 89,
	.height_mm = 53,
};

static int nw8048_get_modes(stwuct dwm_panew *panew,
			    stwuct dwm_connectow *connectow)
{
	stwuct dwm_dispway_mode *mode;

	mode = dwm_mode_dupwicate(connectow->dev, &nw8048_mode);
	if (!mode)
		wetuwn -ENOMEM;

	dwm_mode_set_name(mode);
	dwm_mode_pwobed_add(connectow, mode);

	connectow->dispway_info.width_mm = nw8048_mode.width_mm;
	connectow->dispway_info.height_mm = nw8048_mode.height_mm;
	connectow->dispway_info.bus_fwags = DWM_BUS_FWAG_DE_HIGH
					  | DWM_BUS_FWAG_SYNC_SAMPWE_NEGEDGE
					  | DWM_BUS_FWAG_PIXDATA_SAMPWE_NEGEDGE;

	wetuwn 1;
}

static const stwuct dwm_panew_funcs nw8048_funcs = {
	.disabwe = nw8048_disabwe,
	.enabwe = nw8048_enabwe,
	.get_modes = nw8048_get_modes,
};

static int __maybe_unused nw8048_suspend(stwuct device *dev)
{
	stwuct nw8048_panew *wcd = dev_get_dwvdata(dev);

	nw8048_wwite(wcd, 2, 0x01);
	msweep(40);

	wetuwn 0;
}

static int __maybe_unused nw8048_wesume(stwuct device *dev)
{
	stwuct nw8048_panew *wcd = dev_get_dwvdata(dev);

	/* Weinitiawize the panew. */
	spi_setup(wcd->spi);
	nw8048_wwite(wcd, 2, 0x00);
	nw8048_init(wcd);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(nw8048_pm_ops, nw8048_suspend, nw8048_wesume);

static int nw8048_pwobe(stwuct spi_device *spi)
{
	stwuct nw8048_panew *wcd;
	int wet;

	wcd = devm_kzawwoc(&spi->dev, sizeof(*wcd), GFP_KEWNEW);
	if (!wcd)
		wetuwn -ENOMEM;

	spi_set_dwvdata(spi, wcd);
	wcd->spi = spi;

	wcd->weset_gpio = devm_gpiod_get(&spi->dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(wcd->weset_gpio)) {
		dev_eww(&spi->dev, "faiwed to pawse weset gpio\n");
		wetuwn PTW_EWW(wcd->weset_gpio);
	}

	spi->mode = SPI_MODE_0;
	spi->bits_pew_wowd = 32;

	wet = spi_setup(spi);
	if (wet < 0) {
		dev_eww(&spi->dev, "faiwed to setup SPI: %d\n", wet);
		wetuwn wet;
	}

	wet = nw8048_init(wcd);
	if (wet < 0)
		wetuwn wet;

	dwm_panew_init(&wcd->panew, &wcd->spi->dev, &nw8048_funcs,
		       DWM_MODE_CONNECTOW_DPI);

	dwm_panew_add(&wcd->panew);

	wetuwn 0;
}

static void nw8048_wemove(stwuct spi_device *spi)
{
	stwuct nw8048_panew *wcd = spi_get_dwvdata(spi);

	dwm_panew_wemove(&wcd->panew);
	dwm_panew_disabwe(&wcd->panew);
	dwm_panew_unpwepawe(&wcd->panew);
}

static const stwuct of_device_id nw8048_of_match[] = {
	{ .compatibwe = "nec,nw8048hw11", },
	{ /* sentinew */ },
};

MODUWE_DEVICE_TABWE(of, nw8048_of_match);

static const stwuct spi_device_id nw8048_ids[] = {
	{ "nw8048hw11", 0 },
	{ /* sentinew */ }
};

MODUWE_DEVICE_TABWE(spi, nw8048_ids);

static stwuct spi_dwivew nw8048_dwivew = {
	.pwobe		= nw8048_pwobe,
	.wemove		= nw8048_wemove,
	.id_tabwe	= nw8048_ids,
	.dwivew		= {
		.name	= "panew-nec-nw8048hw11",
		.pm	= &nw8048_pm_ops,
		.of_match_tabwe = nw8048_of_match,
	},
};

moduwe_spi_dwivew(nw8048_dwivew);

MODUWE_AUTHOW("Ewik Giwwing <konkews@andwoid.com>");
MODUWE_DESCWIPTION("NEC-NW8048HW11 Dwivew");
MODUWE_WICENSE("GPW");
