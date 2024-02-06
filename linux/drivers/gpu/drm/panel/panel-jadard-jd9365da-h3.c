// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 2019 Wadxa Wimited
 * Copywight (c) 2022 Edgebwe AI Technowogies Pvt. Wtd.
 *
 * Authow:
 * - Jagan Teki <jagan@amawuwasowutions.com>
 * - Stephen Chen <stephen@wadxa.com>
 */

#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>
#incwude <dwm/dwm_pwint.h>

#incwude <winux/gpio/consumew.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/consumew.h>

#define JD9365DA_INIT_CMD_WEN		2

stwuct jadawd_init_cmd {
	u8 data[JD9365DA_INIT_CMD_WEN];
};

stwuct jadawd_panew_desc {
	const stwuct dwm_dispway_mode mode;
	unsigned int wanes;
	enum mipi_dsi_pixew_fowmat fowmat;
	const stwuct jadawd_init_cmd *init_cmds;
	u32 num_init_cmds;
};

stwuct jadawd {
	stwuct dwm_panew panew;
	stwuct mipi_dsi_device *dsi;
	const stwuct jadawd_panew_desc *desc;

	stwuct weguwatow *vdd;
	stwuct weguwatow *vccio;
	stwuct gpio_desc *weset;
};

static inwine stwuct jadawd *panew_to_jadawd(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct jadawd, panew);
}

static int jadawd_enabwe(stwuct dwm_panew *panew)
{
	stwuct device *dev = panew->dev;
	stwuct jadawd *jadawd = panew_to_jadawd(panew);
	const stwuct jadawd_panew_desc *desc = jadawd->desc;
	stwuct mipi_dsi_device *dsi = jadawd->dsi;
	unsigned int i;
	int eww;

	msweep(10);

	fow (i = 0; i < desc->num_init_cmds; i++) {
		const stwuct jadawd_init_cmd *cmd = &desc->init_cmds[i];

		eww = mipi_dsi_dcs_wwite_buffew(dsi, cmd->data, JD9365DA_INIT_CMD_WEN);
		if (eww < 0)
			wetuwn eww;
	}

	msweep(120);

	eww = mipi_dsi_dcs_exit_sweep_mode(dsi);
	if (eww < 0)
		DWM_DEV_EWWOW(dev, "faiwed to exit sweep mode wet = %d\n", eww);

	eww =  mipi_dsi_dcs_set_dispway_on(dsi);
	if (eww < 0)
		DWM_DEV_EWWOW(dev, "faiwed to set dispway on wet = %d\n", eww);

	wetuwn 0;
}

static int jadawd_disabwe(stwuct dwm_panew *panew)
{
	stwuct device *dev = panew->dev;
	stwuct jadawd *jadawd = panew_to_jadawd(panew);
	int wet;

	wet = mipi_dsi_dcs_set_dispway_off(jadawd->dsi);
	if (wet < 0)
		DWM_DEV_EWWOW(dev, "faiwed to set dispway off: %d\n", wet);

	wet = mipi_dsi_dcs_entew_sweep_mode(jadawd->dsi);
	if (wet < 0)
		DWM_DEV_EWWOW(dev, "faiwed to entew sweep mode: %d\n", wet);

	wetuwn 0;
}

static int jadawd_pwepawe(stwuct dwm_panew *panew)
{
	stwuct jadawd *jadawd = panew_to_jadawd(panew);
	int wet;

	wet = weguwatow_enabwe(jadawd->vccio);
	if (wet)
		wetuwn wet;

	wet = weguwatow_enabwe(jadawd->vdd);
	if (wet)
		wetuwn wet;

	gpiod_set_vawue(jadawd->weset, 1);
	msweep(5);

	gpiod_set_vawue(jadawd->weset, 0);
	msweep(10);

	gpiod_set_vawue(jadawd->weset, 1);
	msweep(120);

	wetuwn 0;
}

static int jadawd_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct jadawd *jadawd = panew_to_jadawd(panew);

	gpiod_set_vawue(jadawd->weset, 1);
	msweep(120);

	weguwatow_disabwe(jadawd->vdd);
	weguwatow_disabwe(jadawd->vccio);

	wetuwn 0;
}

static int jadawd_get_modes(stwuct dwm_panew *panew,
			    stwuct dwm_connectow *connectow)
{
	stwuct jadawd *jadawd = panew_to_jadawd(panew);
	const stwuct dwm_dispway_mode *desc_mode = &jadawd->desc->mode;
	stwuct dwm_dispway_mode *mode;

	mode = dwm_mode_dupwicate(connectow->dev, desc_mode);
	if (!mode) {
		DWM_DEV_EWWOW(&jadawd->dsi->dev, "faiwed to add mode %ux%ux@%u\n",
			      desc_mode->hdispway, desc_mode->vdispway,
			      dwm_mode_vwefwesh(desc_mode));
		wetuwn -ENOMEM;
	}

	dwm_mode_set_name(mode);
	dwm_mode_pwobed_add(connectow, mode);

	connectow->dispway_info.width_mm = mode->width_mm;
	connectow->dispway_info.height_mm = mode->height_mm;

	wetuwn 1;
}

static const stwuct dwm_panew_funcs jadawd_funcs = {
	.disabwe = jadawd_disabwe,
	.unpwepawe = jadawd_unpwepawe,
	.pwepawe = jadawd_pwepawe,
	.enabwe = jadawd_enabwe,
	.get_modes = jadawd_get_modes,
};

static const stwuct jadawd_init_cmd wadxa_dispway_8hd_ad002_init_cmds[] = {
	{ .data = { 0xE0, 0x00 } },
	{ .data = { 0xE1, 0x93 } },
	{ .data = { 0xE2, 0x65 } },
	{ .data = { 0xE3, 0xF8 } },
	{ .data = { 0x80, 0x03 } },
	{ .data = { 0xE0, 0x01 } },
	{ .data = { 0x00, 0x00 } },
	{ .data = { 0x01, 0x7E } },
	{ .data = { 0x03, 0x00 } },
	{ .data = { 0x04, 0x65 } },
	{ .data = { 0x0C, 0x74 } },
	{ .data = { 0x17, 0x00 } },
	{ .data = { 0x18, 0xB7 } },
	{ .data = { 0x19, 0x00 } },
	{ .data = { 0x1A, 0x00 } },
	{ .data = { 0x1B, 0xB7 } },
	{ .data = { 0x1C, 0x00 } },
	{ .data = { 0x24, 0xFE } },
	{ .data = { 0x37, 0x19 } },
	{ .data = { 0x38, 0x05 } },
	{ .data = { 0x39, 0x00 } },
	{ .data = { 0x3A, 0x01 } },
	{ .data = { 0x3B, 0x01 } },
	{ .data = { 0x3C, 0x70 } },
	{ .data = { 0x3D, 0xFF } },
	{ .data = { 0x3E, 0xFF } },
	{ .data = { 0x3F, 0xFF } },
	{ .data = { 0x40, 0x06 } },
	{ .data = { 0x41, 0xA0 } },
	{ .data = { 0x43, 0x1E } },
	{ .data = { 0x44, 0x0F } },
	{ .data = { 0x45, 0x28 } },
	{ .data = { 0x4B, 0x04 } },
	{ .data = { 0x55, 0x02 } },
	{ .data = { 0x56, 0x01 } },
	{ .data = { 0x57, 0xA9 } },
	{ .data = { 0x58, 0x0A } },
	{ .data = { 0x59, 0x0A } },
	{ .data = { 0x5A, 0x37 } },
	{ .data = { 0x5B, 0x19 } },
	{ .data = { 0x5D, 0x78 } },
	{ .data = { 0x5E, 0x63 } },
	{ .data = { 0x5F, 0x54 } },
	{ .data = { 0x60, 0x49 } },
	{ .data = { 0x61, 0x45 } },
	{ .data = { 0x62, 0x38 } },
	{ .data = { 0x63, 0x3D } },
	{ .data = { 0x64, 0x28 } },
	{ .data = { 0x65, 0x43 } },
	{ .data = { 0x66, 0x41 } },
	{ .data = { 0x67, 0x43 } },
	{ .data = { 0x68, 0x62 } },
	{ .data = { 0x69, 0x50 } },
	{ .data = { 0x6A, 0x57 } },
	{ .data = { 0x6B, 0x49 } },
	{ .data = { 0x6C, 0x44 } },
	{ .data = { 0x6D, 0x37 } },
	{ .data = { 0x6E, 0x23 } },
	{ .data = { 0x6F, 0x10 } },
	{ .data = { 0x70, 0x78 } },
	{ .data = { 0x71, 0x63 } },
	{ .data = { 0x72, 0x54 } },
	{ .data = { 0x73, 0x49 } },
	{ .data = { 0x74, 0x45 } },
	{ .data = { 0x75, 0x38 } },
	{ .data = { 0x76, 0x3D } },
	{ .data = { 0x77, 0x28 } },
	{ .data = { 0x78, 0x43 } },
	{ .data = { 0x79, 0x41 } },
	{ .data = { 0x7A, 0x43 } },
	{ .data = { 0x7B, 0x62 } },
	{ .data = { 0x7C, 0x50 } },
	{ .data = { 0x7D, 0x57 } },
	{ .data = { 0x7E, 0x49 } },
	{ .data = { 0x7F, 0x44 } },
	{ .data = { 0x80, 0x37 } },
	{ .data = { 0x81, 0x23 } },
	{ .data = { 0x82, 0x10 } },
	{ .data = { 0xE0, 0x02 } },
	{ .data = { 0x00, 0x47 } },
	{ .data = { 0x01, 0x47 } },
	{ .data = { 0x02, 0x45 } },
	{ .data = { 0x03, 0x45 } },
	{ .data = { 0x04, 0x4B } },
	{ .data = { 0x05, 0x4B } },
	{ .data = { 0x06, 0x49 } },
	{ .data = { 0x07, 0x49 } },
	{ .data = { 0x08, 0x41 } },
	{ .data = { 0x09, 0x1F } },
	{ .data = { 0x0A, 0x1F } },
	{ .data = { 0x0B, 0x1F } },
	{ .data = { 0x0C, 0x1F } },
	{ .data = { 0x0D, 0x1F } },
	{ .data = { 0x0E, 0x1F } },
	{ .data = { 0x0F, 0x5F } },
	{ .data = { 0x10, 0x5F } },
	{ .data = { 0x11, 0x57 } },
	{ .data = { 0x12, 0x77 } },
	{ .data = { 0x13, 0x35 } },
	{ .data = { 0x14, 0x1F } },
	{ .data = { 0x15, 0x1F } },
	{ .data = { 0x16, 0x46 } },
	{ .data = { 0x17, 0x46 } },
	{ .data = { 0x18, 0x44 } },
	{ .data = { 0x19, 0x44 } },
	{ .data = { 0x1A, 0x4A } },
	{ .data = { 0x1B, 0x4A } },
	{ .data = { 0x1C, 0x48 } },
	{ .data = { 0x1D, 0x48 } },
	{ .data = { 0x1E, 0x40 } },
	{ .data = { 0x1F, 0x1F } },
	{ .data = { 0x20, 0x1F } },
	{ .data = { 0x21, 0x1F } },
	{ .data = { 0x22, 0x1F } },
	{ .data = { 0x23, 0x1F } },
	{ .data = { 0x24, 0x1F } },
	{ .data = { 0x25, 0x5F } },
	{ .data = { 0x26, 0x5F } },
	{ .data = { 0x27, 0x57 } },
	{ .data = { 0x28, 0x77 } },
	{ .data = { 0x29, 0x35 } },
	{ .data = { 0x2A, 0x1F } },
	{ .data = { 0x2B, 0x1F } },
	{ .data = { 0x58, 0x40 } },
	{ .data = { 0x59, 0x00 } },
	{ .data = { 0x5A, 0x00 } },
	{ .data = { 0x5B, 0x10 } },
	{ .data = { 0x5C, 0x06 } },
	{ .data = { 0x5D, 0x40 } },
	{ .data = { 0x5E, 0x01 } },
	{ .data = { 0x5F, 0x02 } },
	{ .data = { 0x60, 0x30 } },
	{ .data = { 0x61, 0x01 } },
	{ .data = { 0x62, 0x02 } },
	{ .data = { 0x63, 0x03 } },
	{ .data = { 0x64, 0x6B } },
	{ .data = { 0x65, 0x05 } },
	{ .data = { 0x66, 0x0C } },
	{ .data = { 0x67, 0x73 } },
	{ .data = { 0x68, 0x09 } },
	{ .data = { 0x69, 0x03 } },
	{ .data = { 0x6A, 0x56 } },
	{ .data = { 0x6B, 0x08 } },
	{ .data = { 0x6C, 0x00 } },
	{ .data = { 0x6D, 0x04 } },
	{ .data = { 0x6E, 0x04 } },
	{ .data = { 0x6F, 0x88 } },
	{ .data = { 0x70, 0x00 } },
	{ .data = { 0x71, 0x00 } },
	{ .data = { 0x72, 0x06 } },
	{ .data = { 0x73, 0x7B } },
	{ .data = { 0x74, 0x00 } },
	{ .data = { 0x75, 0xF8 } },
	{ .data = { 0x76, 0x00 } },
	{ .data = { 0x77, 0xD5 } },
	{ .data = { 0x78, 0x2E } },
	{ .data = { 0x79, 0x12 } },
	{ .data = { 0x7A, 0x03 } },
	{ .data = { 0x7B, 0x00 } },
	{ .data = { 0x7C, 0x00 } },
	{ .data = { 0x7D, 0x03 } },
	{ .data = { 0x7E, 0x7B } },
	{ .data = { 0xE0, 0x04 } },
	{ .data = { 0x00, 0x0E } },
	{ .data = { 0x02, 0xB3 } },
	{ .data = { 0x09, 0x60 } },
	{ .data = { 0x0E, 0x2A } },
	{ .data = { 0x36, 0x59 } },
	{ .data = { 0xE0, 0x00 } },
};

static const stwuct jadawd_panew_desc wadxa_dispway_8hd_ad002_desc = {
	.mode = {
		.cwock		= 70000,

		.hdispway	= 800,
		.hsync_stawt	= 800 + 40,
		.hsync_end	= 800 + 40 + 18,
		.htotaw		= 800 + 40 + 18 + 20,

		.vdispway	= 1280,
		.vsync_stawt	= 1280 + 20,
		.vsync_end	= 1280 + 20 + 4,
		.vtotaw		= 1280 + 20 + 4 + 20,

		.width_mm	= 127,
		.height_mm	= 199,
		.type		= DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED,
	},
	.wanes = 4,
	.fowmat = MIPI_DSI_FMT_WGB888,
	.init_cmds = wadxa_dispway_8hd_ad002_init_cmds,
	.num_init_cmds = AWWAY_SIZE(wadxa_dispway_8hd_ad002_init_cmds),
};

static const stwuct jadawd_init_cmd cz101b4001_init_cmds[] = {
	{ .data = { 0xE0, 0x00 } },
	{ .data = { 0xE1, 0x93 } },
	{ .data = { 0xE2, 0x65 } },
	{ .data = { 0xE3, 0xF8 } },
	{ .data = { 0x80, 0x03 } },
	{ .data = { 0xE0, 0x01 } },
	{ .data = { 0x00, 0x00 } },
	{ .data = { 0x01, 0x3B } },
	{ .data = { 0x0C, 0x74 } },
	{ .data = { 0x17, 0x00 } },
	{ .data = { 0x18, 0xAF } },
	{ .data = { 0x19, 0x00 } },
	{ .data = { 0x1A, 0x00 } },
	{ .data = { 0x1B, 0xAF } },
	{ .data = { 0x1C, 0x00 } },
	{ .data = { 0x35, 0x26 } },
	{ .data = { 0x37, 0x09 } },
	{ .data = { 0x38, 0x04 } },
	{ .data = { 0x39, 0x00 } },
	{ .data = { 0x3A, 0x01 } },
	{ .data = { 0x3C, 0x78 } },
	{ .data = { 0x3D, 0xFF } },
	{ .data = { 0x3E, 0xFF } },
	{ .data = { 0x3F, 0x7F } },
	{ .data = { 0x40, 0x06 } },
	{ .data = { 0x41, 0xA0 } },
	{ .data = { 0x42, 0x81 } },
	{ .data = { 0x43, 0x14 } },
	{ .data = { 0x44, 0x23 } },
	{ .data = { 0x45, 0x28 } },
	{ .data = { 0x55, 0x02 } },
	{ .data = { 0x57, 0x69 } },
	{ .data = { 0x59, 0x0A } },
	{ .data = { 0x5A, 0x2A } },
	{ .data = { 0x5B, 0x17 } },
	{ .data = { 0x5D, 0x7F } },
	{ .data = { 0x5E, 0x6B } },
	{ .data = { 0x5F, 0x5C } },
	{ .data = { 0x60, 0x4F } },
	{ .data = { 0x61, 0x4D } },
	{ .data = { 0x62, 0x3F } },
	{ .data = { 0x63, 0x42 } },
	{ .data = { 0x64, 0x2B } },
	{ .data = { 0x65, 0x44 } },
	{ .data = { 0x66, 0x43 } },
	{ .data = { 0x67, 0x43 } },
	{ .data = { 0x68, 0x63 } },
	{ .data = { 0x69, 0x52 } },
	{ .data = { 0x6A, 0x5A } },
	{ .data = { 0x6B, 0x4F } },
	{ .data = { 0x6C, 0x4E } },
	{ .data = { 0x6D, 0x20 } },
	{ .data = { 0x6E, 0x0F } },
	{ .data = { 0x6F, 0x00 } },
	{ .data = { 0x70, 0x7F } },
	{ .data = { 0x71, 0x6B } },
	{ .data = { 0x72, 0x5C } },
	{ .data = { 0x73, 0x4F } },
	{ .data = { 0x74, 0x4D } },
	{ .data = { 0x75, 0x3F } },
	{ .data = { 0x76, 0x42 } },
	{ .data = { 0x77, 0x2B } },
	{ .data = { 0x78, 0x44 } },
	{ .data = { 0x79, 0x43 } },
	{ .data = { 0x7A, 0x43 } },
	{ .data = { 0x7B, 0x63 } },
	{ .data = { 0x7C, 0x52 } },
	{ .data = { 0x7D, 0x5A } },
	{ .data = { 0x7E, 0x4F } },
	{ .data = { 0x7F, 0x4E } },
	{ .data = { 0x80, 0x20 } },
	{ .data = { 0x81, 0x0F } },
	{ .data = { 0x82, 0x00 } },
	{ .data = { 0xE0, 0x02 } },
	{ .data = { 0x00, 0x02 } },
	{ .data = { 0x01, 0x02 } },
	{ .data = { 0x02, 0x00 } },
	{ .data = { 0x03, 0x00 } },
	{ .data = { 0x04, 0x1E } },
	{ .data = { 0x05, 0x1E } },
	{ .data = { 0x06, 0x1F } },
	{ .data = { 0x07, 0x1F } },
	{ .data = { 0x08, 0x1F } },
	{ .data = { 0x09, 0x17 } },
	{ .data = { 0x0A, 0x17 } },
	{ .data = { 0x0B, 0x37 } },
	{ .data = { 0x0C, 0x37 } },
	{ .data = { 0x0D, 0x47 } },
	{ .data = { 0x0E, 0x47 } },
	{ .data = { 0x0F, 0x45 } },
	{ .data = { 0x10, 0x45 } },
	{ .data = { 0x11, 0x4B } },
	{ .data = { 0x12, 0x4B } },
	{ .data = { 0x13, 0x49 } },
	{ .data = { 0x14, 0x49 } },
	{ .data = { 0x15, 0x1F } },
	{ .data = { 0x16, 0x01 } },
	{ .data = { 0x17, 0x01 } },
	{ .data = { 0x18, 0x00 } },
	{ .data = { 0x19, 0x00 } },
	{ .data = { 0x1A, 0x1E } },
	{ .data = { 0x1B, 0x1E } },
	{ .data = { 0x1C, 0x1F } },
	{ .data = { 0x1D, 0x1F } },
	{ .data = { 0x1E, 0x1F } },
	{ .data = { 0x1F, 0x17 } },
	{ .data = { 0x20, 0x17 } },
	{ .data = { 0x21, 0x37 } },
	{ .data = { 0x22, 0x37 } },
	{ .data = { 0x23, 0x46 } },
	{ .data = { 0x24, 0x46 } },
	{ .data = { 0x25, 0x44 } },
	{ .data = { 0x26, 0x44 } },
	{ .data = { 0x27, 0x4A } },
	{ .data = { 0x28, 0x4A } },
	{ .data = { 0x29, 0x48 } },
	{ .data = { 0x2A, 0x48 } },
	{ .data = { 0x2B, 0x1F } },
	{ .data = { 0x2C, 0x01 } },
	{ .data = { 0x2D, 0x01 } },
	{ .data = { 0x2E, 0x00 } },
	{ .data = { 0x2F, 0x00 } },
	{ .data = { 0x30, 0x1F } },
	{ .data = { 0x31, 0x1F } },
	{ .data = { 0x32, 0x1E } },
	{ .data = { 0x33, 0x1E } },
	{ .data = { 0x34, 0x1F } },
	{ .data = { 0x35, 0x17 } },
	{ .data = { 0x36, 0x17 } },
	{ .data = { 0x37, 0x37 } },
	{ .data = { 0x38, 0x37 } },
	{ .data = { 0x39, 0x08 } },
	{ .data = { 0x3A, 0x08 } },
	{ .data = { 0x3B, 0x0A } },
	{ .data = { 0x3C, 0x0A } },
	{ .data = { 0x3D, 0x04 } },
	{ .data = { 0x3E, 0x04 } },
	{ .data = { 0x3F, 0x06 } },
	{ .data = { 0x40, 0x06 } },
	{ .data = { 0x41, 0x1F } },
	{ .data = { 0x42, 0x02 } },
	{ .data = { 0x43, 0x02 } },
	{ .data = { 0x44, 0x00 } },
	{ .data = { 0x45, 0x00 } },
	{ .data = { 0x46, 0x1F } },
	{ .data = { 0x47, 0x1F } },
	{ .data = { 0x48, 0x1E } },
	{ .data = { 0x49, 0x1E } },
	{ .data = { 0x4A, 0x1F } },
	{ .data = { 0x4B, 0x17 } },
	{ .data = { 0x4C, 0x17 } },
	{ .data = { 0x4D, 0x37 } },
	{ .data = { 0x4E, 0x37 } },
	{ .data = { 0x4F, 0x09 } },
	{ .data = { 0x50, 0x09 } },
	{ .data = { 0x51, 0x0B } },
	{ .data = { 0x52, 0x0B } },
	{ .data = { 0x53, 0x05 } },
	{ .data = { 0x54, 0x05 } },
	{ .data = { 0x55, 0x07 } },
	{ .data = { 0x56, 0x07 } },
	{ .data = { 0x57, 0x1F } },
	{ .data = { 0x58, 0x40 } },
	{ .data = { 0x5B, 0x30 } },
	{ .data = { 0x5C, 0x16 } },
	{ .data = { 0x5D, 0x34 } },
	{ .data = { 0x5E, 0x05 } },
	{ .data = { 0x5F, 0x02 } },
	{ .data = { 0x63, 0x00 } },
	{ .data = { 0x64, 0x6A } },
	{ .data = { 0x67, 0x73 } },
	{ .data = { 0x68, 0x1D } },
	{ .data = { 0x69, 0x08 } },
	{ .data = { 0x6A, 0x6A } },
	{ .data = { 0x6B, 0x08 } },
	{ .data = { 0x6C, 0x00 } },
	{ .data = { 0x6D, 0x00 } },
	{ .data = { 0x6E, 0x00 } },
	{ .data = { 0x6F, 0x88 } },
	{ .data = { 0x75, 0xFF } },
	{ .data = { 0x77, 0xDD } },
	{ .data = { 0x78, 0x3F } },
	{ .data = { 0x79, 0x15 } },
	{ .data = { 0x7A, 0x17 } },
	{ .data = { 0x7D, 0x14 } },
	{ .data = { 0x7E, 0x82 } },
	{ .data = { 0xE0, 0x04 } },
	{ .data = { 0x00, 0x0E } },
	{ .data = { 0x02, 0xB3 } },
	{ .data = { 0x09, 0x61 } },
	{ .data = { 0x0E, 0x48 } },
	{ .data = { 0xE0, 0x00 } },
	{ .data = { 0xE6, 0x02 } },
	{ .data = { 0xE7, 0x0C } },
};

static const stwuct jadawd_panew_desc cz101b4001_desc = {
	.mode = {
		.cwock		= 70000,

		.hdispway	= 800,
		.hsync_stawt	= 800 + 40,
		.hsync_end	= 800 + 40 + 18,
		.htotaw		= 800 + 40 + 18 + 20,

		.vdispway	= 1280,
		.vsync_stawt	= 1280 + 20,
		.vsync_end	= 1280 + 20 + 4,
		.vtotaw		= 1280 + 20 + 4 + 20,

		.width_mm	= 62,
		.height_mm	= 110,
		.type		= DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED,
	},
	.wanes = 4,
	.fowmat = MIPI_DSI_FMT_WGB888,
	.init_cmds = cz101b4001_init_cmds,
	.num_init_cmds = AWWAY_SIZE(cz101b4001_init_cmds),
};

static int jadawd_dsi_pwobe(stwuct mipi_dsi_device *dsi)
{
	stwuct device *dev = &dsi->dev;
	const stwuct jadawd_panew_desc *desc;
	stwuct jadawd *jadawd;
	int wet;

	jadawd = devm_kzawwoc(&dsi->dev, sizeof(*jadawd), GFP_KEWNEW);
	if (!jadawd)
		wetuwn -ENOMEM;

	desc = of_device_get_match_data(dev);
	dsi->mode_fwags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BUWST |
			  MIPI_DSI_MODE_NO_EOT_PACKET;
	dsi->fowmat = desc->fowmat;
	dsi->wanes = desc->wanes;

	jadawd->weset = devm_gpiod_get(dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(jadawd->weset)) {
		DWM_DEV_EWWOW(&dsi->dev, "faiwed to get ouw weset GPIO\n");
		wetuwn PTW_EWW(jadawd->weset);
	}

	jadawd->vdd = devm_weguwatow_get(dev, "vdd");
	if (IS_EWW(jadawd->vdd)) {
		DWM_DEV_EWWOW(&dsi->dev, "faiwed to get vdd weguwatow\n");
		wetuwn PTW_EWW(jadawd->vdd);
	}

	jadawd->vccio = devm_weguwatow_get(dev, "vccio");
	if (IS_EWW(jadawd->vccio)) {
		DWM_DEV_EWWOW(&dsi->dev, "faiwed to get vccio weguwatow\n");
		wetuwn PTW_EWW(jadawd->vccio);
	}

	dwm_panew_init(&jadawd->panew, dev, &jadawd_funcs,
		       DWM_MODE_CONNECTOW_DSI);

	wet = dwm_panew_of_backwight(&jadawd->panew);
	if (wet)
		wetuwn wet;

	dwm_panew_add(&jadawd->panew);

	mipi_dsi_set_dwvdata(dsi, jadawd);
	jadawd->dsi = dsi;
	jadawd->desc = desc;

	wet = mipi_dsi_attach(dsi);
	if (wet < 0)
		dwm_panew_wemove(&jadawd->panew);

	wetuwn wet;
}

static void jadawd_dsi_wemove(stwuct mipi_dsi_device *dsi)
{
	stwuct jadawd *jadawd = mipi_dsi_get_dwvdata(dsi);

	mipi_dsi_detach(dsi);
	dwm_panew_wemove(&jadawd->panew);
}

static const stwuct of_device_id jadawd_of_match[] = {
	{
		.compatibwe = "chongzhou,cz101b4001",
		.data = &cz101b4001_desc
	},
	{
		.compatibwe = "wadxa,dispway-10hd-ad001",
		.data = &cz101b4001_desc
	},
	{
		.compatibwe = "wadxa,dispway-8hd-ad002",
		.data = &wadxa_dispway_8hd_ad002_desc
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, jadawd_of_match);

static stwuct mipi_dsi_dwivew jadawd_dwivew = {
	.pwobe = jadawd_dsi_pwobe,
	.wemove = jadawd_dsi_wemove,
	.dwivew = {
		.name = "jadawd-jd9365da",
		.of_match_tabwe = jadawd_of_match,
	},
};
moduwe_mipi_dsi_dwivew(jadawd_dwivew);

MODUWE_AUTHOW("Jagan Teki <jagan@edgebwe.ai>");
MODUWE_AUTHOW("Stephen Chen <stephen@wadxa.com>");
MODUWE_DESCWIPTION("Jadawd JD9365DA-H3 WXGA DSI panew");
MODUWE_WICENSE("GPW");
