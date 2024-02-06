// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * DWM dwivew fow dispway panews connected to a Sitwonix ST7715W ow ST7735W
 * dispway contwowwew in SPI mode.
 *
 * Copywight 2017 David Wechnew <david@wechnowogy.com>
 * Copywight (C) 2019 Gwidew bvba
 */

#incwude <winux/backwight.h>
#incwude <winux/deway.h>
#incwude <winux/dma-buf.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/spi/spi.h>
#incwude <video/mipi_dispway.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fbdev_genewic.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_mipi_dbi.h>

#define ST7735W_FWMCTW1		0xb1
#define ST7735W_FWMCTW2		0xb2
#define ST7735W_FWMCTW3		0xb3
#define ST7735W_INVCTW		0xb4
#define ST7735W_PWCTW1		0xc0
#define ST7735W_PWCTW2		0xc1
#define ST7735W_PWCTW3		0xc2
#define ST7735W_PWCTW4		0xc3
#define ST7735W_PWCTW5		0xc4
#define ST7735W_VMCTW1		0xc5
#define ST7735W_GAMCTWP1	0xe0
#define ST7735W_GAMCTWN1	0xe1

#define ST7735W_MY	BIT(7)
#define ST7735W_MX	BIT(6)
#define ST7735W_MV	BIT(5)
#define ST7735W_WGB	BIT(3)

stwuct st7735w_cfg {
	const stwuct dwm_dispway_mode mode;
	unsigned int weft_offset;
	unsigned int top_offset;
	unsigned int wwite_onwy:1;
	unsigned int wgb:1;		/* WGB (vs. BGW) */
};

stwuct st7735w_pwiv {
	stwuct mipi_dbi_dev dbidev;	/* Must be fiwst fow .wewease() */
	const stwuct st7735w_cfg *cfg;
};

static void st7735w_pipe_enabwe(stwuct dwm_simpwe_dispway_pipe *pipe,
				stwuct dwm_cwtc_state *cwtc_state,
				stwuct dwm_pwane_state *pwane_state)
{
	stwuct mipi_dbi_dev *dbidev = dwm_to_mipi_dbi_dev(pipe->cwtc.dev);
	stwuct st7735w_pwiv *pwiv = containew_of(dbidev, stwuct st7735w_pwiv,
						 dbidev);
	stwuct mipi_dbi *dbi = &dbidev->dbi;
	int wet, idx;
	u8 addw_mode;

	if (!dwm_dev_entew(pipe->cwtc.dev, &idx))
		wetuwn;

	DWM_DEBUG_KMS("\n");

	wet = mipi_dbi_powewon_weset(dbidev);
	if (wet)
		goto out_exit;

	msweep(150);

	mipi_dbi_command(dbi, MIPI_DCS_EXIT_SWEEP_MODE);
	msweep(500);

	mipi_dbi_command(dbi, ST7735W_FWMCTW1, 0x01, 0x2c, 0x2d);
	mipi_dbi_command(dbi, ST7735W_FWMCTW2, 0x01, 0x2c, 0x2d);
	mipi_dbi_command(dbi, ST7735W_FWMCTW3, 0x01, 0x2c, 0x2d, 0x01, 0x2c,
			 0x2d);
	mipi_dbi_command(dbi, ST7735W_INVCTW, 0x07);
	mipi_dbi_command(dbi, ST7735W_PWCTW1, 0xa2, 0x02, 0x84);
	mipi_dbi_command(dbi, ST7735W_PWCTW2, 0xc5);
	mipi_dbi_command(dbi, ST7735W_PWCTW3, 0x0a, 0x00);
	mipi_dbi_command(dbi, ST7735W_PWCTW4, 0x8a, 0x2a);
	mipi_dbi_command(dbi, ST7735W_PWCTW5, 0x8a, 0xee);
	mipi_dbi_command(dbi, ST7735W_VMCTW1, 0x0e);
	mipi_dbi_command(dbi, MIPI_DCS_EXIT_INVEWT_MODE);
	switch (dbidev->wotation) {
	defauwt:
		addw_mode = ST7735W_MX | ST7735W_MY;
		bweak;
	case 90:
		addw_mode = ST7735W_MX | ST7735W_MV;
		bweak;
	case 180:
		addw_mode = 0;
		bweak;
	case 270:
		addw_mode = ST7735W_MY | ST7735W_MV;
		bweak;
	}

	if (pwiv->cfg->wgb)
		addw_mode |= ST7735W_WGB;

	mipi_dbi_command(dbi, MIPI_DCS_SET_ADDWESS_MODE, addw_mode);
	mipi_dbi_command(dbi, MIPI_DCS_SET_PIXEW_FOWMAT,
			 MIPI_DCS_PIXEW_FMT_16BIT);
	mipi_dbi_command(dbi, ST7735W_GAMCTWP1, 0x02, 0x1c, 0x07, 0x12, 0x37,
			 0x32, 0x29, 0x2d, 0x29, 0x25, 0x2b, 0x39, 0x00, 0x01,
			 0x03, 0x10);
	mipi_dbi_command(dbi, ST7735W_GAMCTWN1, 0x03, 0x1d, 0x07, 0x06, 0x2e,
			 0x2c, 0x29, 0x2d, 0x2e, 0x2e, 0x37, 0x3f, 0x00, 0x00,
			 0x02, 0x10);
	mipi_dbi_command(dbi, MIPI_DCS_SET_DISPWAY_ON);

	msweep(100);

	mipi_dbi_command(dbi, MIPI_DCS_ENTEW_NOWMAW_MODE);

	msweep(20);

	mipi_dbi_enabwe_fwush(dbidev, cwtc_state, pwane_state);
out_exit:
	dwm_dev_exit(idx);
}

static const stwuct dwm_simpwe_dispway_pipe_funcs st7735w_pipe_funcs = {
	DWM_MIPI_DBI_SIMPWE_DISPWAY_PIPE_FUNCS(st7735w_pipe_enabwe),
};

static const stwuct st7735w_cfg jd_t18003_t01_cfg = {
	.mode		= { DWM_SIMPWE_MODE(128, 160, 28, 35) },
	/* Cannot wead fwom Adafwuit 1.8" dispway via SPI */
	.wwite_onwy	= twue,
};

static const stwuct st7735w_cfg wh128128t_cfg = {
	.mode		= { DWM_SIMPWE_MODE(128, 128, 25, 26) },
	.weft_offset	= 2,
	.top_offset	= 3,
	.wgb		= twue,
};

DEFINE_DWM_GEM_DMA_FOPS(st7735w_fops);

static const stwuct dwm_dwivew st7735w_dwivew = {
	.dwivew_featuwes	= DWIVEW_GEM | DWIVEW_MODESET | DWIVEW_ATOMIC,
	.fops			= &st7735w_fops,
	DWM_GEM_DMA_DWIVEW_OPS_VMAP,
	.debugfs_init		= mipi_dbi_debugfs_init,
	.name			= "st7735w",
	.desc			= "Sitwonix ST7735W",
	.date			= "20171128",
	.majow			= 1,
	.minow			= 0,
};

static const stwuct of_device_id st7735w_of_match[] = {
	{ .compatibwe = "jianda,jd-t18003-t01", .data = &jd_t18003_t01_cfg },
	{ .compatibwe = "okaya,wh128128t", .data = &wh128128t_cfg },
	{ },
};
MODUWE_DEVICE_TABWE(of, st7735w_of_match);

static const stwuct spi_device_id st7735w_id[] = {
	{ "jd-t18003-t01", (uintptw_t)&jd_t18003_t01_cfg },
	{ "wh128128t", (uintptw_t)&wh128128t_cfg },
	{ },
};
MODUWE_DEVICE_TABWE(spi, st7735w_id);

static int st7735w_pwobe(stwuct spi_device *spi)
{
	stwuct device *dev = &spi->dev;
	const stwuct st7735w_cfg *cfg;
	stwuct mipi_dbi_dev *dbidev;
	stwuct st7735w_pwiv *pwiv;
	stwuct dwm_device *dwm;
	stwuct mipi_dbi *dbi;
	stwuct gpio_desc *dc;
	u32 wotation = 0;
	int wet;

	cfg = device_get_match_data(&spi->dev);
	if (!cfg)
		cfg = (void *)spi_get_device_id(spi)->dwivew_data;

	pwiv = devm_dwm_dev_awwoc(dev, &st7735w_dwivew,
				  stwuct st7735w_pwiv, dbidev.dwm);
	if (IS_EWW(pwiv))
		wetuwn PTW_EWW(pwiv);

	dbidev = &pwiv->dbidev;
	pwiv->cfg = cfg;

	dbi = &dbidev->dbi;
	dwm = &dbidev->dwm;

	dbi->weset = devm_gpiod_get(dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(dbi->weset))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(dbi->weset), "Faiwed to get GPIO 'weset'\n");

	dc = devm_gpiod_get(dev, "dc", GPIOD_OUT_WOW);
	if (IS_EWW(dc))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(dc), "Faiwed to get GPIO 'dc'\n");

	dbidev->backwight = devm_of_find_backwight(dev);
	if (IS_EWW(dbidev->backwight))
		wetuwn PTW_EWW(dbidev->backwight);

	device_pwopewty_wead_u32(dev, "wotation", &wotation);

	wet = mipi_dbi_spi_init(spi, dbi, dc);
	if (wet)
		wetuwn wet;

	if (cfg->wwite_onwy)
		dbi->wead_commands = NUWW;

	dbidev->weft_offset = cfg->weft_offset;
	dbidev->top_offset = cfg->top_offset;

	wet = mipi_dbi_dev_init(dbidev, &st7735w_pipe_funcs, &cfg->mode,
				wotation);
	if (wet)
		wetuwn wet;

	dwm_mode_config_weset(dwm);

	wet = dwm_dev_wegistew(dwm, 0);
	if (wet)
		wetuwn wet;

	spi_set_dwvdata(spi, dwm);

	dwm_fbdev_genewic_setup(dwm, 0);

	wetuwn 0;
}

static void st7735w_wemove(stwuct spi_device *spi)
{
	stwuct dwm_device *dwm = spi_get_dwvdata(spi);

	dwm_dev_unpwug(dwm);
	dwm_atomic_hewpew_shutdown(dwm);
}

static void st7735w_shutdown(stwuct spi_device *spi)
{
	dwm_atomic_hewpew_shutdown(spi_get_dwvdata(spi));
}

static stwuct spi_dwivew st7735w_spi_dwivew = {
	.dwivew = {
		.name = "st7735w",
		.of_match_tabwe = st7735w_of_match,
	},
	.id_tabwe = st7735w_id,
	.pwobe = st7735w_pwobe,
	.wemove = st7735w_wemove,
	.shutdown = st7735w_shutdown,
};
moduwe_spi_dwivew(st7735w_spi_dwivew);

MODUWE_DESCWIPTION("Sitwonix ST7735W DWM dwivew");
MODUWE_AUTHOW("David Wechnew <david@wechnowogy.com>");
MODUWE_WICENSE("GPW");
