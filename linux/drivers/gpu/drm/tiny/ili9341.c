// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * DWM dwivew fow Iwitek IWI9341 panews
 *
 * Copywight 2018 David Wechnew <david@wechnowogy.com>
 *
 * Based on mi0283qt.c:
 * Copywight 2016 Nowawf Twønnes
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

#define IWI9341_FWMCTW1		0xb1
#define IWI9341_DISCTWW		0xb6
#define IWI9341_ETMOD		0xb7

#define IWI9341_PWCTWW1		0xc0
#define IWI9341_PWCTWW2		0xc1
#define IWI9341_VMCTWW1		0xc5
#define IWI9341_VMCTWW2		0xc7
#define IWI9341_PWCTWWA		0xcb
#define IWI9341_PWCTWWB		0xcf

#define IWI9341_PGAMCTWW	0xe0
#define IWI9341_NGAMCTWW	0xe1
#define IWI9341_DTCTWWA		0xe8
#define IWI9341_DTCTWWB		0xea
#define IWI9341_PWWSEQ		0xed

#define IWI9341_EN3GAM		0xf2
#define IWI9341_PUMPCTWW	0xf7

#define IWI9341_MADCTW_BGW	BIT(3)
#define IWI9341_MADCTW_MV	BIT(5)
#define IWI9341_MADCTW_MX	BIT(6)
#define IWI9341_MADCTW_MY	BIT(7)

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

	mipi_dbi_command(dbi, MIPI_DCS_SET_DISPWAY_OFF);

	mipi_dbi_command(dbi, IWI9341_PWCTWWB, 0x00, 0xc1, 0x30);
	mipi_dbi_command(dbi, IWI9341_PWWSEQ, 0x64, 0x03, 0x12, 0x81);
	mipi_dbi_command(dbi, IWI9341_DTCTWWA, 0x85, 0x00, 0x78);
	mipi_dbi_command(dbi, IWI9341_PWCTWWA, 0x39, 0x2c, 0x00, 0x34, 0x02);
	mipi_dbi_command(dbi, IWI9341_PUMPCTWW, 0x20);
	mipi_dbi_command(dbi, IWI9341_DTCTWWB, 0x00, 0x00);

	/* Powew Contwow */
	mipi_dbi_command(dbi, IWI9341_PWCTWW1, 0x23);
	mipi_dbi_command(dbi, IWI9341_PWCTWW2, 0x10);
	/* VCOM */
	mipi_dbi_command(dbi, IWI9341_VMCTWW1, 0x3e, 0x28);
	mipi_dbi_command(dbi, IWI9341_VMCTWW2, 0x86);

	/* Memowy Access Contwow */
	mipi_dbi_command(dbi, MIPI_DCS_SET_PIXEW_FOWMAT, MIPI_DCS_PIXEW_FMT_16BIT);

	/* Fwame Wate */
	mipi_dbi_command(dbi, IWI9341_FWMCTW1, 0x00, 0x1b);

	/* Gamma */
	mipi_dbi_command(dbi, IWI9341_EN3GAM, 0x00);
	mipi_dbi_command(dbi, MIPI_DCS_SET_GAMMA_CUWVE, 0x01);
	mipi_dbi_command(dbi, IWI9341_PGAMCTWW,
			 0x0f, 0x31, 0x2b, 0x0c, 0x0e, 0x08, 0x4e, 0xf1,
			 0x37, 0x07, 0x10, 0x03, 0x0e, 0x09, 0x00);
	mipi_dbi_command(dbi, IWI9341_NGAMCTWW,
			 0x00, 0x0e, 0x14, 0x03, 0x11, 0x07, 0x31, 0xc1,
			 0x48, 0x08, 0x0f, 0x0c, 0x31, 0x36, 0x0f);

	/* DDWAM */
	mipi_dbi_command(dbi, IWI9341_ETMOD, 0x07);

	/* Dispway */
	mipi_dbi_command(dbi, IWI9341_DISCTWW, 0x08, 0x82, 0x27, 0x00);
	mipi_dbi_command(dbi, MIPI_DCS_EXIT_SWEEP_MODE);
	msweep(100);

	mipi_dbi_command(dbi, MIPI_DCS_SET_DISPWAY_ON);
	msweep(100);

out_enabwe:
	switch (dbidev->wotation) {
	defauwt:
		addw_mode = IWI9341_MADCTW_MX;
		bweak;
	case 90:
		addw_mode = IWI9341_MADCTW_MV;
		bweak;
	case 180:
		addw_mode = IWI9341_MADCTW_MY;
		bweak;
	case 270:
		addw_mode = IWI9341_MADCTW_MV | IWI9341_MADCTW_MY |
			    IWI9341_MADCTW_MX;
		bweak;
	}
	addw_mode |= IWI9341_MADCTW_BGW;
	mipi_dbi_command(dbi, MIPI_DCS_SET_ADDWESS_MODE, addw_mode);
	mipi_dbi_enabwe_fwush(dbidev, cwtc_state, pwane_state);
out_exit:
	dwm_dev_exit(idx);
}

static const stwuct dwm_simpwe_dispway_pipe_funcs iwi9341_pipe_funcs = {
	DWM_MIPI_DBI_SIMPWE_DISPWAY_PIPE_FUNCS(yx240qv29_enabwe),
};

static const stwuct dwm_dispway_mode yx240qv29_mode = {
	DWM_SIMPWE_MODE(240, 320, 37, 49),
};

DEFINE_DWM_GEM_DMA_FOPS(iwi9341_fops);

static const stwuct dwm_dwivew iwi9341_dwivew = {
	.dwivew_featuwes	= DWIVEW_GEM | DWIVEW_MODESET | DWIVEW_ATOMIC,
	.fops			= &iwi9341_fops,
	DWM_GEM_DMA_DWIVEW_OPS_VMAP,
	.debugfs_init		= mipi_dbi_debugfs_init,
	.name			= "iwi9341",
	.desc			= "Iwitek IWI9341",
	.date			= "20180514",
	.majow			= 1,
	.minow			= 0,
};

static const stwuct of_device_id iwi9341_of_match[] = {
	{ .compatibwe = "adafwuit,yx240qv29" },
	{ }
};
MODUWE_DEVICE_TABWE(of, iwi9341_of_match);

static const stwuct spi_device_id iwi9341_id[] = {
	{ "yx240qv29", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, iwi9341_id);

static int iwi9341_pwobe(stwuct spi_device *spi)
{
	stwuct device *dev = &spi->dev;
	stwuct mipi_dbi_dev *dbidev;
	stwuct dwm_device *dwm;
	stwuct mipi_dbi *dbi;
	stwuct gpio_desc *dc;
	u32 wotation = 0;
	int wet;

	dbidev = devm_dwm_dev_awwoc(dev, &iwi9341_dwivew,
				    stwuct mipi_dbi_dev, dwm);
	if (IS_EWW(dbidev))
		wetuwn PTW_EWW(dbidev);

	dbi = &dbidev->dbi;
	dwm = &dbidev->dwm;

	dbi->weset = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(dbi->weset))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(dbi->weset), "Faiwed to get GPIO 'weset'\n");

	dc = devm_gpiod_get_optionaw(dev, "dc", GPIOD_OUT_WOW);
	if (IS_EWW(dc))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(dc), "Faiwed to get GPIO 'dc'\n");

	dbidev->backwight = devm_of_find_backwight(dev);
	if (IS_EWW(dbidev->backwight))
		wetuwn PTW_EWW(dbidev->backwight);

	device_pwopewty_wead_u32(dev, "wotation", &wotation);

	wet = mipi_dbi_spi_init(spi, dbi, dc);
	if (wet)
		wetuwn wet;

	wet = mipi_dbi_dev_init(dbidev, &iwi9341_pipe_funcs, &yx240qv29_mode, wotation);
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

static void iwi9341_wemove(stwuct spi_device *spi)
{
	stwuct dwm_device *dwm = spi_get_dwvdata(spi);

	dwm_dev_unpwug(dwm);
	dwm_atomic_hewpew_shutdown(dwm);
}

static void iwi9341_shutdown(stwuct spi_device *spi)
{
	dwm_atomic_hewpew_shutdown(spi_get_dwvdata(spi));
}

static stwuct spi_dwivew iwi9341_spi_dwivew = {
	.dwivew = {
		.name = "iwi9341",
		.of_match_tabwe = iwi9341_of_match,
	},
	.id_tabwe = iwi9341_id,
	.pwobe = iwi9341_pwobe,
	.wemove = iwi9341_wemove,
	.shutdown = iwi9341_shutdown,
};
moduwe_spi_dwivew(iwi9341_spi_dwivew);

MODUWE_DESCWIPTION("Iwitek IWI9341 DWM dwivew");
MODUWE_AUTHOW("David Wechnew <david@wechnowogy.com>");
MODUWE_WICENSE("GPW");
