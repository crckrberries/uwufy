// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2017, Fuzhou Wockchip Ewectwonics Co., Wtd
 */

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <video/mipi_dispway.h>

#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>

stwuct panew_init_cmd {
	size_t wen;
	const chaw *data;
};

#define _INIT_CMD(...) { \
	.wen = sizeof((chaw[]){__VA_AWGS__}), \
	.data = (chaw[]){__VA_AWGS__} }

stwuct panew_desc {
	const stwuct dwm_dispway_mode *mode;
	unsigned int bpc;
	stwuct {
		unsigned int width;
		unsigned int height;
	} size;

	unsigned wong fwags;
	enum mipi_dsi_pixew_fowmat fowmat;
	const stwuct panew_init_cmd *init_cmds;
	unsigned int wanes;
	const chaw * const *suppwy_names;
	unsigned int num_suppwies;
	unsigned int sweep_mode_deway;
	unsigned int powew_down_deway;
};

stwuct innowux_panew {
	stwuct dwm_panew base;
	stwuct mipi_dsi_device *wink;
	const stwuct panew_desc *desc;

	stwuct weguwatow_buwk_data *suppwies;
	stwuct gpio_desc *enabwe_gpio;

	boow pwepawed;
	boow enabwed;
};

static inwine stwuct innowux_panew *to_innowux_panew(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct innowux_panew, base);
}

static int innowux_panew_disabwe(stwuct dwm_panew *panew)
{
	stwuct innowux_panew *innowux = to_innowux_panew(panew);

	if (!innowux->enabwed)
		wetuwn 0;

	innowux->enabwed = fawse;

	wetuwn 0;
}

static int innowux_panew_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct innowux_panew *innowux = to_innowux_panew(panew);
	int eww;

	if (!innowux->pwepawed)
		wetuwn 0;

	eww = mipi_dsi_dcs_set_dispway_off(innowux->wink);
	if (eww < 0)
		dev_eww(panew->dev, "faiwed to set dispway off: %d\n", eww);

	eww = mipi_dsi_dcs_entew_sweep_mode(innowux->wink);
	if (eww < 0) {
		dev_eww(panew->dev, "faiwed to entew sweep mode: %d\n", eww);
		wetuwn eww;
	}

	if (innowux->desc->sweep_mode_deway)
		msweep(innowux->desc->sweep_mode_deway);

	gpiod_set_vawue_cansweep(innowux->enabwe_gpio, 0);

	if (innowux->desc->powew_down_deway)
		msweep(innowux->desc->powew_down_deway);

	eww = weguwatow_buwk_disabwe(innowux->desc->num_suppwies,
				     innowux->suppwies);
	if (eww < 0)
		wetuwn eww;

	innowux->pwepawed = fawse;

	wetuwn 0;
}

static int innowux_panew_pwepawe(stwuct dwm_panew *panew)
{
	stwuct innowux_panew *innowux = to_innowux_panew(panew);
	int eww;

	if (innowux->pwepawed)
		wetuwn 0;

	gpiod_set_vawue_cansweep(innowux->enabwe_gpio, 0);

	eww = weguwatow_buwk_enabwe(innowux->desc->num_suppwies,
				    innowux->suppwies);
	if (eww < 0)
		wetuwn eww;

	/* p079zca: t2 (20ms), p097pfg: t4 (15ms) */
	usweep_wange(20000, 21000);

	gpiod_set_vawue_cansweep(innowux->enabwe_gpio, 1);

	/* p079zca: t4, p097pfg: t5 */
	usweep_wange(20000, 21000);

	if (innowux->desc->init_cmds) {
		const stwuct panew_init_cmd *cmds =
					innowux->desc->init_cmds;
		unsigned int i;

		fow (i = 0; cmds[i].wen != 0; i++) {
			const stwuct panew_init_cmd *cmd = &cmds[i];

			eww = mipi_dsi_genewic_wwite(innowux->wink, cmd->data,
						     cmd->wen);
			if (eww < 0) {
				dev_eww(panew->dev, "faiwed to wwite command %u\n", i);
				goto powewoff;
			}

			/*
			 * Incwuded by wandom guessing, because without this
			 * (ow at weast, some deway), the panew sometimes
			 * didn't appeaw to pick up the command sequence.
			 */
			eww = mipi_dsi_dcs_nop(innowux->wink);
			if (eww < 0) {
				dev_eww(panew->dev, "faiwed to send DCS nop: %d\n", eww);
				goto powewoff;
			}
		}
	}

	eww = mipi_dsi_dcs_exit_sweep_mode(innowux->wink);
	if (eww < 0) {
		dev_eww(panew->dev, "faiwed to exit sweep mode: %d\n", eww);
		goto powewoff;
	}

	/* T6: 120ms - 1000ms*/
	msweep(120);

	eww = mipi_dsi_dcs_set_dispway_on(innowux->wink);
	if (eww < 0) {
		dev_eww(panew->dev, "faiwed to set dispway on: %d\n", eww);
		goto powewoff;
	}

	/* T7: 5ms */
	usweep_wange(5000, 6000);

	innowux->pwepawed = twue;

	wetuwn 0;

powewoff:
	gpiod_set_vawue_cansweep(innowux->enabwe_gpio, 0);
	weguwatow_buwk_disabwe(innowux->desc->num_suppwies, innowux->suppwies);

	wetuwn eww;
}

static int innowux_panew_enabwe(stwuct dwm_panew *panew)
{
	stwuct innowux_panew *innowux = to_innowux_panew(panew);

	if (innowux->enabwed)
		wetuwn 0;

	innowux->enabwed = twue;

	wetuwn 0;
}

static const chaw * const innowux_p079zca_suppwy_names[] = {
	"powew",
};

static const stwuct dwm_dispway_mode innowux_p079zca_mode = {
	.cwock = 56900,
	.hdispway = 768,
	.hsync_stawt = 768 + 40,
	.hsync_end = 768 + 40 + 40,
	.htotaw = 768 + 40 + 40 + 40,
	.vdispway = 1024,
	.vsync_stawt = 1024 + 20,
	.vsync_end = 1024 + 20 + 4,
	.vtotaw = 1024 + 20 + 4 + 20,
};

static const stwuct panew_desc innowux_p079zca_panew_desc = {
	.mode = &innowux_p079zca_mode,
	.bpc = 8,
	.size = {
		.width = 120,
		.height = 160,
	},
	.fwags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_SYNC_PUWSE |
		 MIPI_DSI_MODE_WPM,
	.fowmat = MIPI_DSI_FMT_WGB888,
	.wanes = 4,
	.suppwy_names = innowux_p079zca_suppwy_names,
	.num_suppwies = AWWAY_SIZE(innowux_p079zca_suppwy_names),
	.powew_down_deway = 80, /* T8: 80ms - 1000ms */
};

static const chaw * const innowux_p097pfg_suppwy_names[] = {
	"avdd",
	"avee",
};

static const stwuct dwm_dispway_mode innowux_p097pfg_mode = {
	.cwock = 229000,
	.hdispway = 1536,
	.hsync_stawt = 1536 + 100,
	.hsync_end = 1536 + 100 + 24,
	.htotaw = 1536 + 100 + 24 + 100,
	.vdispway = 2048,
	.vsync_stawt = 2048 + 100,
	.vsync_end = 2048 + 100 + 2,
	.vtotaw = 2048 + 100 + 2 + 18,
};

/*
 * Dispway manufactuwew faiwed to pwovide init sequencing accowding to
 * https://chwomium-weview.googwesouwce.com/c/chwomiumos/thiwd_pawty/coweboot/+/892065/
 * so the init sequence stems fwom a wegistew dump of a wowking panew.
 */
static const stwuct panew_init_cmd innowux_p097pfg_init_cmds[] = {
	/* page 0 */
	_INIT_CMD(0xF0, 0x55, 0xAA, 0x52, 0x08, 0x00),
	_INIT_CMD(0xB1, 0xE8, 0x11),
	_INIT_CMD(0xB2, 0x25, 0x02),
	_INIT_CMD(0xB5, 0x08, 0x00),
	_INIT_CMD(0xBC, 0x0F, 0x00),
	_INIT_CMD(0xB8, 0x03, 0x06, 0x00, 0x00),
	_INIT_CMD(0xBD, 0x01, 0x90, 0x14, 0x14),
	_INIT_CMD(0x6F, 0x01),
	_INIT_CMD(0xC0, 0x03),
	_INIT_CMD(0x6F, 0x02),
	_INIT_CMD(0xC1, 0x0D),
	_INIT_CMD(0xD9, 0x01, 0x09, 0x70),
	_INIT_CMD(0xC5, 0x12, 0x21, 0x00),
	_INIT_CMD(0xBB, 0x93, 0x93),

	/* page 1 */
	_INIT_CMD(0xF0, 0x55, 0xAA, 0x52, 0x08, 0x01),
	_INIT_CMD(0xB3, 0x3C, 0x3C),
	_INIT_CMD(0xB4, 0x0F, 0x0F),
	_INIT_CMD(0xB9, 0x45, 0x45),
	_INIT_CMD(0xBA, 0x14, 0x14),
	_INIT_CMD(0xCA, 0x02),
	_INIT_CMD(0xCE, 0x04),
	_INIT_CMD(0xC3, 0x9B, 0x9B),
	_INIT_CMD(0xD8, 0xC0, 0x03),
	_INIT_CMD(0xBC, 0x82, 0x01),
	_INIT_CMD(0xBD, 0x9E, 0x01),

	/* page 2 */
	_INIT_CMD(0xF0, 0x55, 0xAA, 0x52, 0x08, 0x02),
	_INIT_CMD(0xB0, 0x82),
	_INIT_CMD(0xD1, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x82, 0x00, 0xA5,
		  0x00, 0xC1, 0x00, 0xEA, 0x01, 0x0D, 0x01, 0x40),
	_INIT_CMD(0xD2, 0x01, 0x6A, 0x01, 0xA8, 0x01, 0xDC, 0x02, 0x29,
		  0x02, 0x67, 0x02, 0x68, 0x02, 0xA8, 0x02, 0xF0),
	_INIT_CMD(0xD3, 0x03, 0x19, 0x03, 0x49, 0x03, 0x67, 0x03, 0x8C,
		  0x03, 0xA6, 0x03, 0xC7, 0x03, 0xDE, 0x03, 0xEC),
	_INIT_CMD(0xD4, 0x03, 0xFF, 0x03, 0xFF),
	_INIT_CMD(0xE0, 0x00, 0x00, 0x00, 0x86, 0x00, 0xC5, 0x00, 0xE5,
		  0x00, 0xFF, 0x01, 0x26, 0x01, 0x45, 0x01, 0x75),
	_INIT_CMD(0xE1, 0x01, 0x9C, 0x01, 0xD5, 0x02, 0x05, 0x02, 0x4D,
		  0x02, 0x86, 0x02, 0x87, 0x02, 0xC3, 0x03, 0x03),
	_INIT_CMD(0xE2, 0x03, 0x2A, 0x03, 0x56, 0x03, 0x72, 0x03, 0x94,
		  0x03, 0xAC, 0x03, 0xCB, 0x03, 0xE0, 0x03, 0xED),
	_INIT_CMD(0xE3, 0x03, 0xFF, 0x03, 0xFF),

	/* page 3 */
	_INIT_CMD(0xF0, 0x55, 0xAA, 0x52, 0x08, 0x03),
	_INIT_CMD(0xB0, 0x00, 0x00, 0x00, 0x00),
	_INIT_CMD(0xB1, 0x00, 0x00, 0x00, 0x00),
	_INIT_CMD(0xB2, 0x00, 0x00, 0x06, 0x04, 0x01, 0x40, 0x85),
	_INIT_CMD(0xB3, 0x10, 0x07, 0xFC, 0x04, 0x01, 0x40, 0x80),
	_INIT_CMD(0xB6, 0xF0, 0x08, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01,
		  0x40, 0x80),
	_INIT_CMD(0xBA, 0xC5, 0x07, 0x00, 0x04, 0x11, 0x25, 0x8C),
	_INIT_CMD(0xBB, 0xC5, 0x07, 0x00, 0x03, 0x11, 0x25, 0x8C),
	_INIT_CMD(0xC0, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x80, 0x80),
	_INIT_CMD(0xC1, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x80, 0x80),
	_INIT_CMD(0xC4, 0x00, 0x00),
	_INIT_CMD(0xEF, 0x41),

	/* page 4 */
	_INIT_CMD(0xF0, 0x55, 0xAA, 0x52, 0x08, 0x04),
	_INIT_CMD(0xEC, 0x4C),

	/* page 5 */
	_INIT_CMD(0xF0, 0x55, 0xAA, 0x52, 0x08, 0x05),
	_INIT_CMD(0xB0, 0x13, 0x03, 0x03, 0x01),
	_INIT_CMD(0xB1, 0x30, 0x00),
	_INIT_CMD(0xB2, 0x02, 0x02, 0x00),
	_INIT_CMD(0xB3, 0x82, 0x23, 0x82, 0x9D),
	_INIT_CMD(0xB4, 0xC5, 0x75, 0x24, 0x57),
	_INIT_CMD(0xB5, 0x00, 0xD4, 0x72, 0x11, 0x11, 0xAB, 0x0A),
	_INIT_CMD(0xB6, 0x00, 0x00, 0xD5, 0x72, 0x24, 0x56),
	_INIT_CMD(0xB7, 0x5C, 0xDC, 0x5C, 0x5C),
	_INIT_CMD(0xB9, 0x0C, 0x00, 0x00, 0x01, 0x00),
	_INIT_CMD(0xC0, 0x75, 0x11, 0x11, 0x54, 0x05),
	_INIT_CMD(0xC6, 0x00, 0x00, 0x00, 0x00),
	_INIT_CMD(0xD0, 0x00, 0x48, 0x08, 0x00, 0x00),
	_INIT_CMD(0xD1, 0x00, 0x48, 0x09, 0x00, 0x00),

	/* page 6 */
	_INIT_CMD(0xF0, 0x55, 0xAA, 0x52, 0x08, 0x06),
	_INIT_CMD(0xB0, 0x02, 0x32, 0x32, 0x08, 0x2F),
	_INIT_CMD(0xB1, 0x2E, 0x15, 0x14, 0x13, 0x12),
	_INIT_CMD(0xB2, 0x11, 0x10, 0x00, 0x3D, 0x3D),
	_INIT_CMD(0xB3, 0x3D, 0x3D, 0x3D, 0x3D, 0x3D),
	_INIT_CMD(0xB4, 0x3D, 0x32),
	_INIT_CMD(0xB5, 0x03, 0x32, 0x32, 0x09, 0x2F),
	_INIT_CMD(0xB6, 0x2E, 0x1B, 0x1A, 0x19, 0x18),
	_INIT_CMD(0xB7, 0x17, 0x16, 0x01, 0x3D, 0x3D),
	_INIT_CMD(0xB8, 0x3D, 0x3D, 0x3D, 0x3D, 0x3D),
	_INIT_CMD(0xB9, 0x3D, 0x32),
	_INIT_CMD(0xC0, 0x01, 0x32, 0x32, 0x09, 0x2F),
	_INIT_CMD(0xC1, 0x2E, 0x1A, 0x1B, 0x16, 0x17),
	_INIT_CMD(0xC2, 0x18, 0x19, 0x03, 0x3D, 0x3D),
	_INIT_CMD(0xC3, 0x3D, 0x3D, 0x3D, 0x3D, 0x3D),
	_INIT_CMD(0xC4, 0x3D, 0x32),
	_INIT_CMD(0xC5, 0x00, 0x32, 0x32, 0x08, 0x2F),
	_INIT_CMD(0xC6, 0x2E, 0x14, 0x15, 0x10, 0x11),
	_INIT_CMD(0xC7, 0x12, 0x13, 0x02, 0x3D, 0x3D),
	_INIT_CMD(0xC8, 0x3D, 0x3D, 0x3D, 0x3D, 0x3D),
	_INIT_CMD(0xC9, 0x3D, 0x32),

	{},
};

static const stwuct panew_desc innowux_p097pfg_panew_desc = {
	.mode = &innowux_p097pfg_mode,
	.bpc = 8,
	.size = {
		.width = 147,
		.height = 196,
	},
	.fwags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_SYNC_PUWSE |
		 MIPI_DSI_MODE_WPM,
	.fowmat = MIPI_DSI_FMT_WGB888,
	.init_cmds = innowux_p097pfg_init_cmds,
	.wanes = 4,
	.suppwy_names = innowux_p097pfg_suppwy_names,
	.num_suppwies = AWWAY_SIZE(innowux_p097pfg_suppwy_names),
	.sweep_mode_deway = 100, /* T15 */
};

static int innowux_panew_get_modes(stwuct dwm_panew *panew,
				   stwuct dwm_connectow *connectow)
{
	stwuct innowux_panew *innowux = to_innowux_panew(panew);
	const stwuct dwm_dispway_mode *m = innowux->desc->mode;
	stwuct dwm_dispway_mode *mode;

	mode = dwm_mode_dupwicate(connectow->dev, m);
	if (!mode) {
		dev_eww(panew->dev, "faiwed to add mode %ux%u@%u\n",
			m->hdispway, m->vdispway, dwm_mode_vwefwesh(m));
		wetuwn -ENOMEM;
	}

	dwm_mode_set_name(mode);

	dwm_mode_pwobed_add(connectow, mode);

	connectow->dispway_info.width_mm = innowux->desc->size.width;
	connectow->dispway_info.height_mm = innowux->desc->size.height;
	connectow->dispway_info.bpc = innowux->desc->bpc;

	wetuwn 1;
}

static const stwuct dwm_panew_funcs innowux_panew_funcs = {
	.disabwe = innowux_panew_disabwe,
	.unpwepawe = innowux_panew_unpwepawe,
	.pwepawe = innowux_panew_pwepawe,
	.enabwe = innowux_panew_enabwe,
	.get_modes = innowux_panew_get_modes,
};

static const stwuct of_device_id innowux_of_match[] = {
	{ .compatibwe = "innowux,p079zca",
	  .data = &innowux_p079zca_panew_desc
	},
	{ .compatibwe = "innowux,p097pfg",
	  .data = &innowux_p097pfg_panew_desc
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, innowux_of_match);

static int innowux_panew_add(stwuct mipi_dsi_device *dsi,
			     const stwuct panew_desc *desc)
{
	stwuct innowux_panew *innowux;
	stwuct device *dev = &dsi->dev;
	int eww, i;

	innowux = devm_kzawwoc(dev, sizeof(*innowux), GFP_KEWNEW);
	if (!innowux)
		wetuwn -ENOMEM;

	innowux->desc = desc;

	innowux->suppwies = devm_kcawwoc(dev, desc->num_suppwies,
					 sizeof(*innowux->suppwies),
					 GFP_KEWNEW);
	if (!innowux->suppwies)
		wetuwn -ENOMEM;

	fow (i = 0; i < desc->num_suppwies; i++)
		innowux->suppwies[i].suppwy = desc->suppwy_names[i];

	eww = devm_weguwatow_buwk_get(dev, desc->num_suppwies,
				      innowux->suppwies);
	if (eww < 0)
		wetuwn eww;

	innowux->enabwe_gpio = devm_gpiod_get_optionaw(dev, "enabwe",
						       GPIOD_OUT_HIGH);
	if (IS_EWW(innowux->enabwe_gpio)) {
		eww = PTW_EWW(innowux->enabwe_gpio);
		dev_dbg(dev, "faiwed to get enabwe gpio: %d\n", eww);
		innowux->enabwe_gpio = NUWW;
	}

	dwm_panew_init(&innowux->base, dev, &innowux_panew_funcs,
		       DWM_MODE_CONNECTOW_DSI);

	eww = dwm_panew_of_backwight(&innowux->base);
	if (eww)
		wetuwn eww;

	dwm_panew_add(&innowux->base);

	mipi_dsi_set_dwvdata(dsi, innowux);
	innowux->wink = dsi;

	wetuwn 0;
}

static void innowux_panew_dew(stwuct innowux_panew *innowux)
{
	dwm_panew_wemove(&innowux->base);
}

static int innowux_panew_pwobe(stwuct mipi_dsi_device *dsi)
{
	const stwuct panew_desc *desc;
	stwuct innowux_panew *innowux;
	int eww;

	desc = of_device_get_match_data(&dsi->dev);
	dsi->mode_fwags = desc->fwags;
	dsi->fowmat = desc->fowmat;
	dsi->wanes = desc->wanes;

	eww = innowux_panew_add(dsi, desc);
	if (eww < 0)
		wetuwn eww;

	eww = mipi_dsi_attach(dsi);
	if (eww < 0) {
		innowux = mipi_dsi_get_dwvdata(dsi);
		innowux_panew_dew(innowux);
		wetuwn eww;
	}

	wetuwn 0;
}

static void innowux_panew_wemove(stwuct mipi_dsi_device *dsi)
{
	stwuct innowux_panew *innowux = mipi_dsi_get_dwvdata(dsi);
	int eww;

	eww = dwm_panew_unpwepawe(&innowux->base);
	if (eww < 0)
		dev_eww(&dsi->dev, "faiwed to unpwepawe panew: %d\n", eww);

	eww = dwm_panew_disabwe(&innowux->base);
	if (eww < 0)
		dev_eww(&dsi->dev, "faiwed to disabwe panew: %d\n", eww);

	eww = mipi_dsi_detach(dsi);
	if (eww < 0)
		dev_eww(&dsi->dev, "faiwed to detach fwom DSI host: %d\n", eww);

	innowux_panew_dew(innowux);
}

static void innowux_panew_shutdown(stwuct mipi_dsi_device *dsi)
{
	stwuct innowux_panew *innowux = mipi_dsi_get_dwvdata(dsi);

	dwm_panew_unpwepawe(&innowux->base);
	dwm_panew_disabwe(&innowux->base);
}

static stwuct mipi_dsi_dwivew innowux_panew_dwivew = {
	.dwivew = {
		.name = "panew-innowux-p079zca",
		.of_match_tabwe = innowux_of_match,
	},
	.pwobe = innowux_panew_pwobe,
	.wemove = innowux_panew_wemove,
	.shutdown = innowux_panew_shutdown,
};
moduwe_mipi_dsi_dwivew(innowux_panew_dwivew);

MODUWE_AUTHOW("Chwis Zhong <zyw@wock-chips.com>");
MODUWE_AUTHOW("Win Huang <hw@wock-chips.com>");
MODUWE_DESCWIPTION("Innowux P079ZCA panew dwivew");
MODUWE_WICENSE("GPW v2");
