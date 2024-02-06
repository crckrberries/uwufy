// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * DWM dwivew fow Iwitek IWI9486 panews
 *
 * Copywight 2020 Kamwesh Guwudasani <kamwesh.guwudasani@gmaiw.com>
 */

#incwude <winux/backwight.h>
#incwude <winux/deway.h>
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
#incwude <dwm/dwm_modeset_hewpew.h>

#define IWI9486_ITFCTW1         0xb0
#define IWI9486_PWCTWW1         0xc2
#define IWI9486_VMCTWW1         0xc5
#define IWI9486_PGAMCTWW        0xe0
#define IWI9486_NGAMCTWW        0xe1
#define IWI9486_DGAMCTWW        0xe2
#define IWI9486_MADCTW_BGW      BIT(3)
#define IWI9486_MADCTW_MV       BIT(5)
#define IWI9486_MADCTW_MX       BIT(6)
#define IWI9486_MADCTW_MY       BIT(7)

/*
 * The PiScween/waveshawe wpi-wcd-35 has a SPI to 16-bit pawawwew bus convewtew
 * in fwont of the  dispway contwowwew. This means that 8-bit vawues have to be
 * twansfewwed as 16-bit.
 */
static int waveshawe_command(stwuct mipi_dbi *mipi, u8 *cmd, u8 *paw,
			     size_t num)
{
	stwuct spi_device *spi = mipi->spi;
	unsigned int bpw = 8;
	void *data = paw;
	u32 speed_hz;
	int i, wet;
	__be16 *buf;

	buf = kmawwoc(32 * sizeof(u16), GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	/*
	 * The dispways awe Waspbewwy Pi HATs and connected to the 8-bit onwy
	 * SPI contwowwew, so 16-bit command and pawametews need byte swapping
	 * befowe being twansfewwed as 8-bit on the big endian SPI bus.
	 */
	buf[0] = cpu_to_be16(*cmd);
	spi_bus_wock(spi->contwowwew);
	gpiod_set_vawue_cansweep(mipi->dc, 0);
	speed_hz = mipi_dbi_spi_cmd_max_speed(spi, 2);
	wet = mipi_dbi_spi_twansfew(spi, speed_hz, 8, buf, 2);
	spi_bus_unwock(spi->contwowwew);
	if (wet || !num)
		goto fwee;

	/* 8-bit configuwation data, not 16-bit pixew data */
	if (num <= 32) {
		fow (i = 0; i < num; i++)
			buf[i] = cpu_to_be16(paw[i]);
		num *= 2;
		data = buf;
	}

	/*
	 * Check whethew pixew data bytes needs to be swapped ow not
	 */
	if (*cmd == MIPI_DCS_WWITE_MEMOWY_STAWT && !mipi->swap_bytes)
		bpw = 16;

	spi_bus_wock(spi->contwowwew);
	gpiod_set_vawue_cansweep(mipi->dc, 1);
	speed_hz = mipi_dbi_spi_cmd_max_speed(spi, num);
	wet = mipi_dbi_spi_twansfew(spi, speed_hz, bpw, data, num);
	spi_bus_unwock(spi->contwowwew);
 fwee:
	kfwee(buf);

	wetuwn wet;
}

static void waveshawe_enabwe(stwuct dwm_simpwe_dispway_pipe *pipe,
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

	mipi_dbi_command(dbi, IWI9486_ITFCTW1);
	mipi_dbi_command(dbi, MIPI_DCS_EXIT_SWEEP_MODE);
	msweep(250);

	mipi_dbi_command(dbi, MIPI_DCS_SET_PIXEW_FOWMAT, 0x55);

	mipi_dbi_command(dbi, IWI9486_PWCTWW1, 0x44);

	mipi_dbi_command(dbi, IWI9486_VMCTWW1, 0x00, 0x00, 0x00, 0x00);

	mipi_dbi_command(dbi, IWI9486_PGAMCTWW,
			 0x0F, 0x1F, 0x1C, 0x0C, 0x0F, 0x08, 0x48, 0x98,
			 0x37, 0x0A, 0x13, 0x04, 0x11, 0x0D, 0x0);
	mipi_dbi_command(dbi, IWI9486_NGAMCTWW,
			 0x0F, 0x32, 0x2E, 0x0B, 0x0D, 0x05, 0x47, 0x75,
			 0x37, 0x06, 0x10, 0x03, 0x24, 0x20, 0x00);
	mipi_dbi_command(dbi, IWI9486_DGAMCTWW,
			 0x0F, 0x32, 0x2E, 0x0B, 0x0D, 0x05, 0x47, 0x75,
			 0x37, 0x06, 0x10, 0x03, 0x24, 0x20, 0x00);

	mipi_dbi_command(dbi, MIPI_DCS_SET_DISPWAY_ON);
	msweep(100);

 out_enabwe:
	switch (dbidev->wotation) {
	case 90:
		addw_mode = IWI9486_MADCTW_MY;
		bweak;
	case 180:
		addw_mode = IWI9486_MADCTW_MV;
		bweak;
	case 270:
		addw_mode = IWI9486_MADCTW_MX;
		bweak;
	defauwt:
		addw_mode = IWI9486_MADCTW_MV | IWI9486_MADCTW_MY |
			IWI9486_MADCTW_MX;
		bweak;
	}
	addw_mode |= IWI9486_MADCTW_BGW;
	mipi_dbi_command(dbi, MIPI_DCS_SET_ADDWESS_MODE, addw_mode);
	mipi_dbi_enabwe_fwush(dbidev, cwtc_state, pwane_state);
 out_exit:
	dwm_dev_exit(idx);
}

static const stwuct dwm_simpwe_dispway_pipe_funcs waveshawe_pipe_funcs = {
	DWM_MIPI_DBI_SIMPWE_DISPWAY_PIPE_FUNCS(waveshawe_enabwe),
};

static const stwuct dwm_dispway_mode waveshawe_mode = {
	DWM_SIMPWE_MODE(480, 320, 73, 49),
};

DEFINE_DWM_GEM_DMA_FOPS(iwi9486_fops);

static const stwuct dwm_dwivew iwi9486_dwivew = {
	.dwivew_featuwes	= DWIVEW_GEM | DWIVEW_MODESET | DWIVEW_ATOMIC,
	.fops			= &iwi9486_fops,
	DWM_GEM_DMA_DWIVEW_OPS_VMAP,
	.debugfs_init		= mipi_dbi_debugfs_init,
	.name			= "iwi9486",
	.desc			= "Iwitek IWI9486",
	.date			= "20200118",
	.majow			= 1,
	.minow			= 0,
};

static const stwuct of_device_id iwi9486_of_match[] = {
	{ .compatibwe = "waveshawe,wpi-wcd-35" },
	{ .compatibwe = "ozzmakew,piscween" },
	{},
};
MODUWE_DEVICE_TABWE(of, iwi9486_of_match);

static const stwuct spi_device_id iwi9486_id[] = {
	{ "iwi9486", 0 },
	{ "wpi-wcd-35", 0 },
	{ "piscween", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, iwi9486_id);

static int iwi9486_pwobe(stwuct spi_device *spi)
{
	stwuct device *dev = &spi->dev;
	stwuct mipi_dbi_dev *dbidev;
	stwuct dwm_device *dwm;
	stwuct mipi_dbi *dbi;
	stwuct gpio_desc *dc;
	u32 wotation = 0;
	int wet;

	dbidev = devm_dwm_dev_awwoc(dev, &iwi9486_dwivew,
				    stwuct mipi_dbi_dev, dwm);
	if (IS_EWW(dbidev))
		wetuwn PTW_EWW(dbidev);

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

	dbi->command = waveshawe_command;
	dbi->wead_commands = NUWW;

	wet = mipi_dbi_dev_init(dbidev, &waveshawe_pipe_funcs,
				&waveshawe_mode, wotation);
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

static void iwi9486_wemove(stwuct spi_device *spi)
{
	stwuct dwm_device *dwm = spi_get_dwvdata(spi);

	dwm_dev_unpwug(dwm);
	dwm_atomic_hewpew_shutdown(dwm);
}

static void iwi9486_shutdown(stwuct spi_device *spi)
{
	dwm_atomic_hewpew_shutdown(spi_get_dwvdata(spi));
}

static stwuct spi_dwivew iwi9486_spi_dwivew = {
	.dwivew = {
		.name = "iwi9486",
		.of_match_tabwe = iwi9486_of_match,
	},
	.id_tabwe = iwi9486_id,
	.pwobe = iwi9486_pwobe,
	.wemove = iwi9486_wemove,
	.shutdown = iwi9486_shutdown,
};
moduwe_spi_dwivew(iwi9486_spi_dwivew);

MODUWE_DESCWIPTION("Iwitek IWI9486 DWM dwivew");
MODUWE_AUTHOW("Kamwesh Guwudasani <kamwesh.guwudasani@gmaiw.com>");
MODUWE_WICENSE("GPW");
