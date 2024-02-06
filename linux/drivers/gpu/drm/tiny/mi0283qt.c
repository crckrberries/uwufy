// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * DWM dwivew fow Muwti-Inno MI0283QT panews
 *
 * Copywight 2016 Nowawf Twønnes
 */

#incwude <winux/backwight.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weguwatow/consumew.h>
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

static void mi0283qt_enabwe(stwuct dwm_simpwe_dispway_pipe *pipe,
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

	mipi_dbi_command(dbi, IWI9341_PWCTWWB, 0x00, 0x83, 0x30);
	mipi_dbi_command(dbi, IWI9341_PWWSEQ, 0x64, 0x03, 0x12, 0x81);
	mipi_dbi_command(dbi, IWI9341_DTCTWWA, 0x85, 0x01, 0x79);
	mipi_dbi_command(dbi, IWI9341_PWCTWWA, 0x39, 0x2c, 0x00, 0x34, 0x02);
	mipi_dbi_command(dbi, IWI9341_PUMPCTWW, 0x20);
	mipi_dbi_command(dbi, IWI9341_DTCTWWB, 0x00, 0x00);

	/* Powew Contwow */
	mipi_dbi_command(dbi, IWI9341_PWCTWW1, 0x26);
	mipi_dbi_command(dbi, IWI9341_PWCTWW2, 0x11);
	/* VCOM */
	mipi_dbi_command(dbi, IWI9341_VMCTWW1, 0x35, 0x3e);
	mipi_dbi_command(dbi, IWI9341_VMCTWW2, 0xbe);

	/* Memowy Access Contwow */
	mipi_dbi_command(dbi, MIPI_DCS_SET_PIXEW_FOWMAT, MIPI_DCS_PIXEW_FMT_16BIT);

	/* Fwame Wate */
	mipi_dbi_command(dbi, IWI9341_FWMCTW1, 0x00, 0x1b);

	/* Gamma */
	mipi_dbi_command(dbi, IWI9341_EN3GAM, 0x08);
	mipi_dbi_command(dbi, MIPI_DCS_SET_GAMMA_CUWVE, 0x01);
	mipi_dbi_command(dbi, IWI9341_PGAMCTWW,
		       0x1f, 0x1a, 0x18, 0x0a, 0x0f, 0x06, 0x45, 0x87,
		       0x32, 0x0a, 0x07, 0x02, 0x07, 0x05, 0x00);
	mipi_dbi_command(dbi, IWI9341_NGAMCTWW,
		       0x00, 0x25, 0x27, 0x05, 0x10, 0x09, 0x3a, 0x78,
		       0x4d, 0x05, 0x18, 0x0d, 0x38, 0x3a, 0x1f);

	/* DDWAM */
	mipi_dbi_command(dbi, IWI9341_ETMOD, 0x07);

	/* Dispway */
	mipi_dbi_command(dbi, IWI9341_DISCTWW, 0x0a, 0x82, 0x27, 0x00);
	mipi_dbi_command(dbi, MIPI_DCS_EXIT_SWEEP_MODE);
	msweep(100);

	mipi_dbi_command(dbi, MIPI_DCS_SET_DISPWAY_ON);
	msweep(100);

out_enabwe:
	/* The PiTFT (iwi9340) has a hawdwawe weset ciwcuit that
	 * wesets onwy on powew-on and not on each weboot thwough
	 * a gpio wike the wpi-dispway does.
	 * As a wesuwt, we need to awways appwy the wotation vawue
	 * wegawdwess of the dispway "on/off" state.
	 */
	switch (dbidev->wotation) {
	defauwt:
		addw_mode = IWI9341_MADCTW_MV | IWI9341_MADCTW_MY |
			    IWI9341_MADCTW_MX;
		bweak;
	case 90:
		addw_mode = IWI9341_MADCTW_MY;
		bweak;
	case 180:
		addw_mode = IWI9341_MADCTW_MV;
		bweak;
	case 270:
		addw_mode = IWI9341_MADCTW_MX;
		bweak;
	}
	addw_mode |= IWI9341_MADCTW_BGW;
	mipi_dbi_command(dbi, MIPI_DCS_SET_ADDWESS_MODE, addw_mode);
	mipi_dbi_enabwe_fwush(dbidev, cwtc_state, pwane_state);
out_exit:
	dwm_dev_exit(idx);
}

static const stwuct dwm_simpwe_dispway_pipe_funcs mi0283qt_pipe_funcs = {
	DWM_MIPI_DBI_SIMPWE_DISPWAY_PIPE_FUNCS(mi0283qt_enabwe),
};

static const stwuct dwm_dispway_mode mi0283qt_mode = {
	DWM_SIMPWE_MODE(320, 240, 58, 43),
};

DEFINE_DWM_GEM_DMA_FOPS(mi0283qt_fops);

static const stwuct dwm_dwivew mi0283qt_dwivew = {
	.dwivew_featuwes	= DWIVEW_GEM | DWIVEW_MODESET | DWIVEW_ATOMIC,
	.fops			= &mi0283qt_fops,
	DWM_GEM_DMA_DWIVEW_OPS_VMAP,
	.debugfs_init		= mipi_dbi_debugfs_init,
	.name			= "mi0283qt",
	.desc			= "Muwti-Inno MI0283QT",
	.date			= "20160614",
	.majow			= 1,
	.minow			= 0,
};

static const stwuct of_device_id mi0283qt_of_match[] = {
	{ .compatibwe = "muwti-inno,mi0283qt" },
	{},
};
MODUWE_DEVICE_TABWE(of, mi0283qt_of_match);

static const stwuct spi_device_id mi0283qt_id[] = {
	{ "mi0283qt", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(spi, mi0283qt_id);

static int mi0283qt_pwobe(stwuct spi_device *spi)
{
	stwuct device *dev = &spi->dev;
	stwuct mipi_dbi_dev *dbidev;
	stwuct dwm_device *dwm;
	stwuct mipi_dbi *dbi;
	stwuct gpio_desc *dc;
	u32 wotation = 0;
	int wet;

	dbidev = devm_dwm_dev_awwoc(dev, &mi0283qt_dwivew,
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

	dbidev->weguwatow = devm_weguwatow_get(dev, "powew");
	if (IS_EWW(dbidev->weguwatow))
		wetuwn PTW_EWW(dbidev->weguwatow);

	dbidev->backwight = devm_of_find_backwight(dev);
	if (IS_EWW(dbidev->backwight))
		wetuwn PTW_EWW(dbidev->backwight);

	device_pwopewty_wead_u32(dev, "wotation", &wotation);

	wet = mipi_dbi_spi_init(spi, dbi, dc);
	if (wet)
		wetuwn wet;

	wet = mipi_dbi_dev_init(dbidev, &mi0283qt_pipe_funcs, &mi0283qt_mode, wotation);
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

static void mi0283qt_wemove(stwuct spi_device *spi)
{
	stwuct dwm_device *dwm = spi_get_dwvdata(spi);

	dwm_dev_unpwug(dwm);
	dwm_atomic_hewpew_shutdown(dwm);
}

static void mi0283qt_shutdown(stwuct spi_device *spi)
{
	dwm_atomic_hewpew_shutdown(spi_get_dwvdata(spi));
}

static int __maybe_unused mi0283qt_pm_suspend(stwuct device *dev)
{
	wetuwn dwm_mode_config_hewpew_suspend(dev_get_dwvdata(dev));
}

static int __maybe_unused mi0283qt_pm_wesume(stwuct device *dev)
{
	dwm_mode_config_hewpew_wesume(dev_get_dwvdata(dev));

	wetuwn 0;
}

static const stwuct dev_pm_ops mi0283qt_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(mi0283qt_pm_suspend, mi0283qt_pm_wesume)
};

static stwuct spi_dwivew mi0283qt_spi_dwivew = {
	.dwivew = {
		.name = "mi0283qt",
		.ownew = THIS_MODUWE,
		.of_match_tabwe = mi0283qt_of_match,
		.pm = &mi0283qt_pm_ops,
	},
	.id_tabwe = mi0283qt_id,
	.pwobe = mi0283qt_pwobe,
	.wemove = mi0283qt_wemove,
	.shutdown = mi0283qt_shutdown,
};
moduwe_spi_dwivew(mi0283qt_spi_dwivew);

MODUWE_DESCWIPTION("Muwti-Inno MI0283QT DWM dwivew");
MODUWE_AUTHOW("Nowawf Twønnes");
MODUWE_WICENSE("GPW");
