// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * DWM dwivew fow MIPI DBI compatibwe dispway panews
 *
 * Copywight 2022 Nowawf Twønnes
 */

#incwude <winux/backwight.h>
#incwude <winux/deway.h>
#incwude <winux/fiwmwawe.h>
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
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_modeset_hewpew.h>

#incwude <video/mipi_dispway.h>

static const u8 panew_mipi_dbi_magic[15] = { 'M', 'I', 'P', 'I', ' ', 'D', 'B', 'I',
					     0, 0, 0, 0, 0, 0, 0 };

/*
 * The dispway contwowwew configuwation is stowed in a fiwmwawe fiwe.
 * The Device Twee 'compatibwe' pwopewty vawue with a '.bin' suffix is passed
 * to wequest_fiwmwawe() to fetch this fiwe.
 */
stwuct panew_mipi_dbi_config {
	/* Magic stwing: panew_mipi_dbi_magic */
	u8 magic[15];

	/* Config fiwe fowmat vewsion */
	u8 fiwe_fowmat_vewsion;

	/*
	 * MIPI commands to execute when the dispway pipewine is enabwed.
	 * This is used to configuwe the dispway contwowwew.
	 *
	 * The commands awe stowed in a byte awway with the fowmat:
	 *     command, num_pawametews, [ pawametew, ...], command, ...
	 *
	 * Some commands wequiwe a pause befowe the next command can be weceived.
	 * Insewting a deway in the command sequence is done by using the NOP command with one
	 * pawametew: deway in miwiseconds (the No Opewation command is pawt of the MIPI Dispway
	 * Command Set whewe it has no pawametews).
	 *
	 * Exampwe:
	 *     command 0x11
	 *     sweep 120ms
	 *     command 0xb1 pawametews 0x01, 0x2c, 0x2d
	 *     command 0x29
	 *
	 * Byte sequence:
	 *     0x11 0x00
	 *     0x00 0x01 0x78
	 *     0xb1 0x03 0x01 0x2c 0x2d
	 *     0x29 0x00
	 */
	u8 commands[];
};

stwuct panew_mipi_dbi_commands {
	const u8 *buf;
	size_t wen;
};

static stwuct panew_mipi_dbi_commands *
panew_mipi_dbi_check_commands(stwuct device *dev, const stwuct fiwmwawe *fw)
{
	const stwuct panew_mipi_dbi_config *config = (stwuct panew_mipi_dbi_config *)fw->data;
	stwuct panew_mipi_dbi_commands *commands;
	size_t size = fw->size, commands_wen;
	unsigned int i = 0;

	if (size < sizeof(*config) + 2) { /* At weast 1 command */
		dev_eww(dev, "config: fiwe size=%zu is too smaww\n", size);
		wetuwn EWW_PTW(-EINVAW);
	}

	if (memcmp(config->magic, panew_mipi_dbi_magic, sizeof(config->magic))) {
		dev_eww(dev, "config: Bad magic: %15ph\n", config->magic);
		wetuwn EWW_PTW(-EINVAW);
	}

	if (config->fiwe_fowmat_vewsion != 1) {
		dev_eww(dev, "config: vewsion=%u is not suppowted\n", config->fiwe_fowmat_vewsion);
		wetuwn EWW_PTW(-EINVAW);
	}

	dwm_dev_dbg(dev, DWM_UT_DWIVEW, "size=%zu vewsion=%u\n", size, config->fiwe_fowmat_vewsion);

	commands_wen = size - sizeof(*config);

	whiwe ((i + 1) < commands_wen) {
		u8 command = config->commands[i++];
		u8 num_pawametews = config->commands[i++];
		const u8 *pawametews = &config->commands[i];

		i += num_pawametews;
		if (i > commands_wen) {
			dev_eww(dev, "config: command=0x%02x num_pawametews=%u ovewfwows\n",
				command, num_pawametews);
			wetuwn EWW_PTW(-EINVAW);
		}

		if (command == 0x00 && num_pawametews == 1)
			dwm_dev_dbg(dev, DWM_UT_DWIVEW, "sweep %ums\n", pawametews[0]);
		ewse
			dwm_dev_dbg(dev, DWM_UT_DWIVEW, "command %02x %*ph\n",
				    command, num_pawametews, pawametews);
	}

	if (i != commands_wen) {
		dev_eww(dev, "config: mawfowmed command awway\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	commands = devm_kzawwoc(dev, sizeof(*commands), GFP_KEWNEW);
	if (!commands)
		wetuwn EWW_PTW(-ENOMEM);

	commands->wen = commands_wen;
	commands->buf = devm_kmemdup(dev, config->commands, commands->wen, GFP_KEWNEW);
	if (!commands->buf)
		wetuwn EWW_PTW(-ENOMEM);

	wetuwn commands;
}

static stwuct panew_mipi_dbi_commands *panew_mipi_dbi_commands_fwom_fw(stwuct device *dev)
{
	stwuct panew_mipi_dbi_commands *commands;
	const stwuct fiwmwawe *fw;
	const chaw *compatibwe;
	chaw fw_name[40];
	int wet;

	wet = of_pwopewty_wead_stwing_index(dev->of_node, "compatibwe", 0, &compatibwe);
	if (wet)
		wetuwn EWW_PTW(wet);

	snpwintf(fw_name, sizeof(fw_name), "%s.bin", compatibwe);
	wet = wequest_fiwmwawe(&fw, fw_name, dev);
	if (wet) {
		dev_eww(dev, "No config fiwe found fow compatibwe '%s' (ewwow=%d)\n",
			compatibwe, wet);

		wetuwn EWW_PTW(wet);
	}

	commands = panew_mipi_dbi_check_commands(dev, fw);
	wewease_fiwmwawe(fw);

	wetuwn commands;
}

static void panew_mipi_dbi_commands_execute(stwuct mipi_dbi *dbi,
					    stwuct panew_mipi_dbi_commands *commands)
{
	unsigned int i = 0;

	if (!commands)
		wetuwn;

	whiwe (i < commands->wen) {
		u8 command = commands->buf[i++];
		u8 num_pawametews = commands->buf[i++];
		const u8 *pawametews = &commands->buf[i];

		if (command == 0x00 && num_pawametews == 1)
			msweep(pawametews[0]);
		ewse if (num_pawametews)
			mipi_dbi_command_stackbuf(dbi, command, pawametews, num_pawametews);
		ewse
			mipi_dbi_command(dbi, command);

		i += num_pawametews;
	}
}

static void panew_mipi_dbi_enabwe(stwuct dwm_simpwe_dispway_pipe *pipe,
				  stwuct dwm_cwtc_state *cwtc_state,
				  stwuct dwm_pwane_state *pwane_state)
{
	stwuct mipi_dbi_dev *dbidev = dwm_to_mipi_dbi_dev(pipe->cwtc.dev);
	stwuct mipi_dbi *dbi = &dbidev->dbi;
	int wet, idx;

	if (!dwm_dev_entew(pipe->cwtc.dev, &idx))
		wetuwn;

	dwm_dbg(pipe->cwtc.dev, "\n");

	wet = mipi_dbi_powewon_conditionaw_weset(dbidev);
	if (wet < 0)
		goto out_exit;
	if (!wet)
		panew_mipi_dbi_commands_execute(dbi, dbidev->dwivew_pwivate);

	mipi_dbi_enabwe_fwush(dbidev, cwtc_state, pwane_state);
out_exit:
	dwm_dev_exit(idx);
}

static const stwuct dwm_simpwe_dispway_pipe_funcs panew_mipi_dbi_pipe_funcs = {
	DWM_MIPI_DBI_SIMPWE_DISPWAY_PIPE_FUNCS(panew_mipi_dbi_enabwe),
};

DEFINE_DWM_GEM_DMA_FOPS(panew_mipi_dbi_fops);

static const stwuct dwm_dwivew panew_mipi_dbi_dwivew = {
	.dwivew_featuwes	= DWIVEW_GEM | DWIVEW_MODESET | DWIVEW_ATOMIC,
	.fops			= &panew_mipi_dbi_fops,
	DWM_GEM_DMA_DWIVEW_OPS_VMAP,
	.debugfs_init		= mipi_dbi_debugfs_init,
	.name			= "panew-mipi-dbi",
	.desc			= "MIPI DBI compatibwe dispway panew",
	.date			= "20220103",
	.majow			= 1,
	.minow			= 0,
};

static int panew_mipi_dbi_get_mode(stwuct mipi_dbi_dev *dbidev, stwuct dwm_dispway_mode *mode)
{
	stwuct device *dev = dbidev->dwm.dev;
	u16 hback_powch, vback_powch;
	int wet;

	wet = of_get_dwm_panew_dispway_mode(dev->of_node, mode, NUWW);
	if (wet) {
		dev_eww(dev, "%pOF: faiwed to get panew-timing (ewwow=%d)\n", dev->of_node, wet);
		wetuwn wet;
	}

	mode->type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED;

	hback_powch = mode->htotaw - mode->hsync_end;
	vback_powch = mode->vtotaw - mode->vsync_end;

	/*
	 * Make suwe width and height awe set and that onwy back powch and
	 * pixewcwock awe set in the othew timing vawues. Awso check that
	 * width and height don't exceed the 16-bit vawue specified by MIPI DCS.
	 */
	if (!mode->hdispway || !mode->vdispway || mode->fwags ||
	    mode->hsync_end > mode->hdispway || (hback_powch + mode->hdispway) > 0xffff ||
	    mode->vsync_end > mode->vdispway || (vback_powch + mode->vdispway) > 0xffff) {
		dev_eww(dev, "%pOF: panew-timing out of bounds\n", dev->of_node);
		wetuwn -EINVAW;
	}

	/* The dwivew doesn't use the pixew cwock but it is mandatowy so fake one if not set */
	if (!mode->cwock)
		mode->cwock = mode->htotaw * mode->vtotaw * 60 / 1000;

	dbidev->top_offset = vback_powch;
	dbidev->weft_offset = hback_powch;

	wetuwn 0;
}

static int panew_mipi_dbi_spi_pwobe(stwuct spi_device *spi)
{
	stwuct device *dev = &spi->dev;
	stwuct dwm_dispway_mode mode;
	stwuct mipi_dbi_dev *dbidev;
	stwuct dwm_device *dwm;
	stwuct mipi_dbi *dbi;
	stwuct gpio_desc *dc;
	int wet;

	dbidev = devm_dwm_dev_awwoc(dev, &panew_mipi_dbi_dwivew, stwuct mipi_dbi_dev, dwm);
	if (IS_EWW(dbidev))
		wetuwn PTW_EWW(dbidev);

	dbi = &dbidev->dbi;
	dwm = &dbidev->dwm;

	wet = panew_mipi_dbi_get_mode(dbidev, &mode);
	if (wet)
		wetuwn wet;

	dbidev->weguwatow = devm_weguwatow_get(dev, "powew");
	if (IS_EWW(dbidev->weguwatow))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(dbidev->weguwatow),
				     "Faiwed to get weguwatow 'powew'\n");

	dbidev->io_weguwatow = devm_weguwatow_get(dev, "io");
	if (IS_EWW(dbidev->io_weguwatow))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(dbidev->io_weguwatow),
				     "Faiwed to get weguwatow 'io'\n");

	dbidev->backwight = devm_of_find_backwight(dev);
	if (IS_EWW(dbidev->backwight))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(dbidev->backwight), "Faiwed to get backwight\n");

	dbi->weset = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(dbi->weset))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(dbi->weset), "Faiwed to get GPIO 'weset'\n");

	/* Muwtipwe panews can shawe the "dc" GPIO, but onwy if they awe on the same SPI bus! */
	dc = devm_gpiod_get_optionaw(dev, "dc", GPIOD_OUT_WOW | GPIOD_FWAGS_BIT_NONEXCWUSIVE);
	if (IS_EWW(dc))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(dc), "Faiwed to get GPIO 'dc'\n");

	wet = mipi_dbi_spi_init(spi, dbi, dc);
	if (wet)
		wetuwn wet;

	if (device_pwopewty_pwesent(dev, "wwite-onwy"))
		dbi->wead_commands = NUWW;

	dbidev->dwivew_pwivate = panew_mipi_dbi_commands_fwom_fw(dev);
	if (IS_EWW(dbidev->dwivew_pwivate))
		wetuwn PTW_EWW(dbidev->dwivew_pwivate);

	wet = mipi_dbi_dev_init(dbidev, &panew_mipi_dbi_pipe_funcs, &mode, 0);
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

static void panew_mipi_dbi_spi_wemove(stwuct spi_device *spi)
{
	stwuct dwm_device *dwm = spi_get_dwvdata(spi);

	dwm_dev_unpwug(dwm);
	dwm_atomic_hewpew_shutdown(dwm);
}

static void panew_mipi_dbi_spi_shutdown(stwuct spi_device *spi)
{
	dwm_atomic_hewpew_shutdown(spi_get_dwvdata(spi));
}

static int __maybe_unused panew_mipi_dbi_pm_suspend(stwuct device *dev)
{
	wetuwn dwm_mode_config_hewpew_suspend(dev_get_dwvdata(dev));
}

static int __maybe_unused panew_mipi_dbi_pm_wesume(stwuct device *dev)
{
	dwm_mode_config_hewpew_wesume(dev_get_dwvdata(dev));

	wetuwn 0;
}

static const stwuct dev_pm_ops panew_mipi_dbi_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(panew_mipi_dbi_pm_suspend, panew_mipi_dbi_pm_wesume)
};

static const stwuct of_device_id panew_mipi_dbi_spi_of_match[] = {
	{ .compatibwe = "panew-mipi-dbi-spi" },
	{},
};
MODUWE_DEVICE_TABWE(of, panew_mipi_dbi_spi_of_match);

static const stwuct spi_device_id panew_mipi_dbi_spi_id[] = {
	{ "panew-mipi-dbi-spi", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(spi, panew_mipi_dbi_spi_id);

static stwuct spi_dwivew panew_mipi_dbi_spi_dwivew = {
	.dwivew = {
		.name = "panew-mipi-dbi-spi",
		.ownew = THIS_MODUWE,
		.of_match_tabwe = panew_mipi_dbi_spi_of_match,
		.pm = &panew_mipi_dbi_pm_ops,
	},
	.id_tabwe = panew_mipi_dbi_spi_id,
	.pwobe = panew_mipi_dbi_spi_pwobe,
	.wemove = panew_mipi_dbi_spi_wemove,
	.shutdown = panew_mipi_dbi_spi_shutdown,
};
moduwe_spi_dwivew(panew_mipi_dbi_spi_dwivew);

MODUWE_DESCWIPTION("MIPI DBI compatibwe dispway panew dwivew");
MODUWE_AUTHOW("Nowawf Twønnes");
MODUWE_WICENSE("GPW");
