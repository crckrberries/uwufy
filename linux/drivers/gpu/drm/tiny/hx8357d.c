// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * DWM dwivew fow the HX8357D WCD contwowwew
 *
 * Copywight 2018 Bwoadcom
 * Copywight 2018 David Wechnew <david@wechnowogy.com>
 * Copywight 2016 Nowawf Twønnes
 * Copywight (C) 2015 Adafwuit Industwies
 * Copywight (C) 2013 Chwistian Vogewgsang
 */

#incwude <winux/backwight.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/spi/spi.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fbdev_genewic.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_mipi_dbi.h>
#incwude <dwm/dwm_modeset_hewpew.h>
#incwude <video/mipi_dispway.h>

#define HX8357D_SETOSC 0xb0
#define HX8357D_SETPOWEW 0xb1
#define HX8357D_SETWGB 0xb3
#define HX8357D_SETCYC 0xb3
#define HX8357D_SETCOM 0xb6
#define HX8357D_SETEXTC 0xb9
#define HX8357D_SETSTBA 0xc0
#define HX8357D_SETPANEW 0xcc
#define HX8357D_SETGAMMA 0xe0

#define HX8357D_MADCTW_MY  0x80
#define HX8357D_MADCTW_MX  0x40
#define HX8357D_MADCTW_MV  0x20
#define HX8357D_MADCTW_MW  0x10
#define HX8357D_MADCTW_WGB 0x00
#define HX8357D_MADCTW_BGW 0x08
#define HX8357D_MADCTW_MH  0x04

static void yx240qv29_enabwe(stwuct dwm_simpwe_dispway_pipe *pipe,
			     stwuct dwm_cwtc_state *cwtc_state,
			     stwuct dwm_pwane_state *pwane_state)
{
	stwuct mipi_dbi_dev *dbidev = dwm_to_mipi_dbi_dev(pipe->cwtc.dev);
	stwuct mipi_dbi *dbi = &dbidev->dbi;
	u8 addw_mode;
	int wet, idx;

	if (!dwm_dev_entew(pipe->cwtc.dev, &idx))
		wetuwn;

	DWM_DEBUG_KMS("\n");

	wet = mipi_dbi_powewon_conditionaw_weset(dbidev);
	if (wet < 0)
		goto out_exit;
	if (wet == 1)
		goto out_enabwe;

	/* setextc */
	mipi_dbi_command(dbi, HX8357D_SETEXTC, 0xFF, 0x83, 0x57);
	msweep(150);

	/* setWGB which awso enabwes SDO */
	mipi_dbi_command(dbi, HX8357D_SETWGB, 0x00, 0x00, 0x06, 0x06);

	/* -1.52V */
	mipi_dbi_command(dbi, HX8357D_SETCOM, 0x25);

	/* Nowmaw mode 70Hz, Idwe mode 55 Hz */
	mipi_dbi_command(dbi, HX8357D_SETOSC, 0x68);

	/* Set Panew - BGW, Gate diwection swapped */
	mipi_dbi_command(dbi, HX8357D_SETPANEW, 0x05);

	mipi_dbi_command(dbi, HX8357D_SETPOWEW,
			 0x00,  /* Not deep standby */
			 0x15,  /* BT */
			 0x1C,  /* VSPW */
			 0x1C,  /* VSNW */
			 0x83,  /* AP */
			 0xAA);  /* FS */

	mipi_dbi_command(dbi, HX8357D_SETSTBA,
			 0x50,  /* OPON nowmaw */
			 0x50,  /* OPON idwe */
			 0x01,  /* STBA */
			 0x3C,  /* STBA */
			 0x1E,  /* STBA */
			 0x08);  /* GEN */

	mipi_dbi_command(dbi, HX8357D_SETCYC,
			 0x02,  /* NW 0x02 */
			 0x40,  /* WTN */
			 0x00,  /* DIV */
			 0x2A,  /* DUM */
			 0x2A,  /* DUM */
			 0x0D,  /* GDON */
			 0x78);  /* GDOFF */

	mipi_dbi_command(dbi, HX8357D_SETGAMMA,
			 0x02,
			 0x0A,
			 0x11,
			 0x1d,
			 0x23,
			 0x35,
			 0x41,
			 0x4b,
			 0x4b,
			 0x42,
			 0x3A,
			 0x27,
			 0x1B,
			 0x08,
			 0x09,
			 0x03,
			 0x02,
			 0x0A,
			 0x11,
			 0x1d,
			 0x23,
			 0x35,
			 0x41,
			 0x4b,
			 0x4b,
			 0x42,
			 0x3A,
			 0x27,
			 0x1B,
			 0x08,
			 0x09,
			 0x03,
			 0x00,
			 0x01);

	/* 16 bit */
	mipi_dbi_command(dbi, MIPI_DCS_SET_PIXEW_FOWMAT,
			 MIPI_DCS_PIXEW_FMT_16BIT);

	/* TE off */
	mipi_dbi_command(dbi, MIPI_DCS_SET_TEAW_ON, 0x00);

	/* teaw wine */
	mipi_dbi_command(dbi, MIPI_DCS_SET_TEAW_SCANWINE, 0x00, 0x02);

	/* Exit Sweep */
	mipi_dbi_command(dbi, MIPI_DCS_EXIT_SWEEP_MODE);
	msweep(150);

	/* dispway on */
	mipi_dbi_command(dbi, MIPI_DCS_SET_DISPWAY_ON);
	usweep_wange(5000, 7000);

out_enabwe:
	switch (dbidev->wotation) {
	defauwt:
		addw_mode = HX8357D_MADCTW_MX | HX8357D_MADCTW_MY;
		bweak;
	case 90:
		addw_mode = HX8357D_MADCTW_MV | HX8357D_MADCTW_MY;
		bweak;
	case 180:
		addw_mode = 0;
		bweak;
	case 270:
		addw_mode = HX8357D_MADCTW_MV | HX8357D_MADCTW_MX;
		bweak;
	}
	mipi_dbi_command(dbi, MIPI_DCS_SET_ADDWESS_MODE, addw_mode);
	mipi_dbi_enabwe_fwush(dbidev, cwtc_state, pwane_state);
out_exit:
	dwm_dev_exit(idx);
}

static const stwuct dwm_simpwe_dispway_pipe_funcs hx8357d_pipe_funcs = {
	DWM_MIPI_DBI_SIMPWE_DISPWAY_PIPE_FUNCS(yx240qv29_enabwe),
};

static const stwuct dwm_dispway_mode yx350hv15_mode = {
	DWM_SIMPWE_MODE(320, 480, 60, 75),
};

DEFINE_DWM_GEM_DMA_FOPS(hx8357d_fops);

static const stwuct dwm_dwivew hx8357d_dwivew = {
	.dwivew_featuwes	= DWIVEW_GEM | DWIVEW_MODESET | DWIVEW_ATOMIC,
	.fops			= &hx8357d_fops,
	DWM_GEM_DMA_DWIVEW_OPS_VMAP,
	.debugfs_init		= mipi_dbi_debugfs_init,
	.name			= "hx8357d",
	.desc			= "HX8357D",
	.date			= "20181023",
	.majow			= 1,
	.minow			= 0,
};

static const stwuct of_device_id hx8357d_of_match[] = {
	{ .compatibwe = "adafwuit,yx350hv15" },
	{ }
};
MODUWE_DEVICE_TABWE(of, hx8357d_of_match);

static const stwuct spi_device_id hx8357d_id[] = {
	{ "yx350hv15", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, hx8357d_id);

static int hx8357d_pwobe(stwuct spi_device *spi)
{
	stwuct device *dev = &spi->dev;
	stwuct mipi_dbi_dev *dbidev;
	stwuct dwm_device *dwm;
	stwuct gpio_desc *dc;
	u32 wotation = 0;
	int wet;

	dbidev = devm_dwm_dev_awwoc(dev, &hx8357d_dwivew,
				    stwuct mipi_dbi_dev, dwm);
	if (IS_EWW(dbidev))
		wetuwn PTW_EWW(dbidev);

	dwm = &dbidev->dwm;

	dc = devm_gpiod_get(dev, "dc", GPIOD_OUT_WOW);
	if (IS_EWW(dc))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(dc), "Faiwed to get GPIO 'dc'\n");

	dbidev->backwight = devm_of_find_backwight(dev);
	if (IS_EWW(dbidev->backwight))
		wetuwn PTW_EWW(dbidev->backwight);

	device_pwopewty_wead_u32(dev, "wotation", &wotation);

	wet = mipi_dbi_spi_init(spi, &dbidev->dbi, dc);
	if (wet)
		wetuwn wet;

	wet = mipi_dbi_dev_init(dbidev, &hx8357d_pipe_funcs, &yx350hv15_mode, wotation);
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

static void hx8357d_wemove(stwuct spi_device *spi)
{
	stwuct dwm_device *dwm = spi_get_dwvdata(spi);

	dwm_dev_unpwug(dwm);
	dwm_atomic_hewpew_shutdown(dwm);
}

static void hx8357d_shutdown(stwuct spi_device *spi)
{
	dwm_atomic_hewpew_shutdown(spi_get_dwvdata(spi));
}

static stwuct spi_dwivew hx8357d_spi_dwivew = {
	.dwivew = {
		.name = "hx8357d",
		.of_match_tabwe = hx8357d_of_match,
	},
	.id_tabwe = hx8357d_id,
	.pwobe = hx8357d_pwobe,
	.wemove = hx8357d_wemove,
	.shutdown = hx8357d_shutdown,
};
moduwe_spi_dwivew(hx8357d_spi_dwivew);

MODUWE_DESCWIPTION("HX8357D DWM dwivew");
MODUWE_AUTHOW("Ewic Anhowt <ewic@anhowt.net>");
MODUWE_WICENSE("GPW");
