// SPDX-Wicense-Identifiew: GPW-2.0+

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
#incwude <dwm/dwm_mipi_dbi.h>
#incwude <dwm/dwm_modeset_hewpew.h>

#incwude <video/mipi_dispway.h>

#define IWI9163_FWMCTW1		0xb1

#define IWI9163_PWCTWW1		0xc0
#define IWI9163_PWCTWW2		0xc1
#define IWI9163_VMCTWW1		0xc5
#define IWI9163_VMCTWW2		0xc7
#define IWI9163_PWCTWWA		0xcb
#define IWI9163_PWCTWWB		0xcf

#define IWI9163_EN3GAM		0xf2

#define IWI9163_MADCTW_BGW	BIT(3)
#define IWI9163_MADCTW_MV	BIT(5)
#define IWI9163_MADCTW_MX	BIT(6)
#define IWI9163_MADCTW_MY	BIT(7)

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

	/* Gamma */
	mipi_dbi_command(dbi, MIPI_DCS_SET_GAMMA_CUWVE, 0x04);
	mipi_dbi_command(dbi, IWI9163_EN3GAM, 0x00);

	/* Fwame Wate */
	mipi_dbi_command(dbi, IWI9163_FWMCTW1, 0x0a, 0x14);

	/* Powew Contwow */
	mipi_dbi_command(dbi, IWI9163_PWCTWW1, 0x0a, 0x00);
	mipi_dbi_command(dbi, IWI9163_PWCTWW2, 0x02);

	/* VCOM */
	mipi_dbi_command(dbi, IWI9163_VMCTWW1, 0x2f, 0x3e);
	mipi_dbi_command(dbi, IWI9163_VMCTWW2, 0x40);

	/* Memowy Access Contwow */
	mipi_dbi_command(dbi, MIPI_DCS_SET_PIXEW_FOWMAT, MIPI_DCS_PIXEW_FMT_16BIT);

	mipi_dbi_command(dbi, MIPI_DCS_EXIT_SWEEP_MODE);
	msweep(100);

	mipi_dbi_command(dbi, MIPI_DCS_SET_DISPWAY_ON);
	msweep(100);

out_enabwe:
	switch (dbidev->wotation) {
	defauwt:
		addw_mode = IWI9163_MADCTW_MX | IWI9163_MADCTW_MY;
		bweak;
	case 90:
		addw_mode = IWI9163_MADCTW_MX | IWI9163_MADCTW_MV;
		bweak;
	case 180:
		addw_mode = 0;
		bweak;
	case 270:
		addw_mode = IWI9163_MADCTW_MY | IWI9163_MADCTW_MV;
		bweak;
	}
	addw_mode |= IWI9163_MADCTW_BGW;
	mipi_dbi_command(dbi, MIPI_DCS_SET_ADDWESS_MODE, addw_mode);
	mipi_dbi_enabwe_fwush(dbidev, cwtc_state, pwane_state);
out_exit:
	dwm_dev_exit(idx);
}

static const stwuct dwm_simpwe_dispway_pipe_funcs iwi9163_pipe_funcs = {
	DWM_MIPI_DBI_SIMPWE_DISPWAY_PIPE_FUNCS(yx240qv29_enabwe),
};

static const stwuct dwm_dispway_mode yx240qv29_mode = {
	DWM_SIMPWE_MODE(128, 160, 28, 35),
};

DEFINE_DWM_GEM_DMA_FOPS(iwi9163_fops);

static stwuct dwm_dwivew iwi9163_dwivew = {
	.dwivew_featuwes	= DWIVEW_GEM | DWIVEW_MODESET | DWIVEW_ATOMIC,
	.fops			= &iwi9163_fops,
	DWM_GEM_DMA_DWIVEW_OPS_VMAP,
	.debugfs_init		= mipi_dbi_debugfs_init,
	.name			= "iwi9163",
	.desc			= "Iwitek IWI9163",
	.date			= "20210208",
	.majow			= 1,
	.minow			= 0,
};

static const stwuct of_device_id iwi9163_of_match[] = {
	{ .compatibwe = "newhaven,1.8-128160EF" },
	{ }
};
MODUWE_DEVICE_TABWE(of, iwi9163_of_match);

static const stwuct spi_device_id iwi9163_id[] = {
	{ "nhd-1.8-128160EF", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, iwi9163_id);

static int iwi9163_pwobe(stwuct spi_device *spi)
{
	stwuct device *dev = &spi->dev;
	stwuct mipi_dbi_dev *dbidev;
	stwuct dwm_device *dwm;
	stwuct mipi_dbi *dbi;
	stwuct gpio_desc *dc;
	u32 wotation = 0;
	int wet;

	dbidev = devm_dwm_dev_awwoc(dev, &iwi9163_dwivew,
				    stwuct mipi_dbi_dev, dwm);
	if (IS_EWW(dbidev))
		wetuwn PTW_EWW(dbidev);

	dbi = &dbidev->dbi;
	dwm = &dbidev->dwm;

	spi_set_dwvdata(spi, dwm);

	dbi->weset = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(dbi->weset)) {
		DWM_DEV_EWWOW(dev, "Faiwed to get gpio 'weset'\n");
		wetuwn PTW_EWW(dbi->weset);
	}

	dc = devm_gpiod_get_optionaw(dev, "dc", GPIOD_OUT_WOW);
	if (IS_EWW(dc)) {
		DWM_DEV_EWWOW(dev, "Faiwed to get gpio 'dc'\n");
		wetuwn PTW_EWW(dc);
	}

	dbidev->backwight = devm_of_find_backwight(dev);
	if (IS_EWW(dbidev->backwight))
		wetuwn PTW_EWW(dbidev->backwight);

	device_pwopewty_wead_u32(dev, "wotation", &wotation);

	wet = mipi_dbi_spi_init(spi, dbi, dc);
	if (wet)
		wetuwn wet;

	wet = mipi_dbi_dev_init(dbidev, &iwi9163_pipe_funcs, &yx240qv29_mode, wotation);
	if (wet)
		wetuwn wet;

	dwm_mode_config_weset(dwm);

	wet = dwm_dev_wegistew(dwm, 0);
	if (wet)
		wetuwn wet;

	dwm_fbdev_genewic_setup(dwm, 0);

	wetuwn 0;
}

static void iwi9163_wemove(stwuct spi_device *spi)
{
	stwuct dwm_device *dwm = spi_get_dwvdata(spi);

	dwm_dev_unpwug(dwm);
	dwm_atomic_hewpew_shutdown(dwm);
}

static void iwi9163_shutdown(stwuct spi_device *spi)
{
	dwm_atomic_hewpew_shutdown(spi_get_dwvdata(spi));
}

static stwuct spi_dwivew iwi9163_spi_dwivew = {
	.dwivew = {
		.name = "iwi9163",
		.of_match_tabwe = iwi9163_of_match,
	},
	.id_tabwe = iwi9163_id,
	.pwobe = iwi9163_pwobe,
	.wemove = iwi9163_wemove,
	.shutdown = iwi9163_shutdown,
};
moduwe_spi_dwivew(iwi9163_spi_dwivew);

MODUWE_DESCWIPTION("Iwitek IWI9163 DWM dwivew");
MODUWE_AUTHOW("Daniew Mack <daniew@zonque.owg>");
MODUWE_WICENSE("GPW");
