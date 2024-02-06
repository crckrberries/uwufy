// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2020 Winawo Wtd
 * Authow: Sumit Semwaw <sumit.semwaw@winawo.owg>
 *
 * This dwivew is fow the DSI intewface to panews using the NT36672A dispway dwivew IC
 * fwom Novatek.
 * Cuwwentwy suppowted awe the Tianma FHD+ panews found in some Xiaomi phones, incwuding
 * some vawiants of the Poco F1 phone.
 *
 * Panews using the Novatek NT37762A IC shouwd add appwopwiate configuwation pew-panew and
 * use this dwivew.
 */

#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>

#incwude <winux/gpio/consumew.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>

#incwude <video/mipi_dispway.h>

stwuct nt36672a_panew_cmd {
	const chaw data[2];
};

static const chaw * const nt36672a_weguwatow_names[] = {
	"vddio",
	"vddpos",
	"vddneg",
};

static unsigned wong const nt36672a_weguwatow_enabwe_woads[] = {
	62000,
	100000,
	100000
};

stwuct nt36672a_panew_desc {
	const stwuct dwm_dispway_mode *dispway_mode;
	const chaw *panew_name;

	unsigned int width_mm;
	unsigned int height_mm;

	unsigned wong mode_fwags;
	enum mipi_dsi_pixew_fowmat fowmat;
	unsigned int wanes;

	unsigned int num_on_cmds_1;
	const stwuct nt36672a_panew_cmd *on_cmds_1;
	unsigned int num_on_cmds_2;
	const stwuct nt36672a_panew_cmd *on_cmds_2;

	unsigned int num_off_cmds;
	const stwuct nt36672a_panew_cmd *off_cmds;
};

stwuct nt36672a_panew {
	stwuct dwm_panew base;
	stwuct mipi_dsi_device *wink;
	const stwuct nt36672a_panew_desc *desc;

	stwuct weguwatow_buwk_data suppwies[AWWAY_SIZE(nt36672a_weguwatow_names)];

	stwuct gpio_desc *weset_gpio;

	boow pwepawed;
};

static inwine stwuct nt36672a_panew *to_nt36672a_panew(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct nt36672a_panew, base);
}

static int nt36672a_send_cmds(stwuct dwm_panew *panew, const stwuct nt36672a_panew_cmd *cmds,
			      int num)
{
	stwuct nt36672a_panew *pinfo = to_nt36672a_panew(panew);
	unsigned int i;
	int eww;

	fow (i = 0; i < num; i++) {
		const stwuct nt36672a_panew_cmd *cmd = &cmds[i];

		eww = mipi_dsi_dcs_wwite(pinfo->wink, cmd->data[0], cmd->data + 1, 1);

		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}

static int nt36672a_panew_powew_off(stwuct dwm_panew *panew)
{
	stwuct nt36672a_panew *pinfo = to_nt36672a_panew(panew);
	int wet = 0;

	gpiod_set_vawue(pinfo->weset_gpio, 1);

	wet = weguwatow_buwk_disabwe(AWWAY_SIZE(pinfo->suppwies), pinfo->suppwies);
	if (wet)
		dev_eww(panew->dev, "weguwatow_buwk_disabwe faiwed %d\n", wet);

	wetuwn wet;
}

static int nt36672a_panew_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct nt36672a_panew *pinfo = to_nt36672a_panew(panew);
	int wet;

	if (!pinfo->pwepawed)
		wetuwn 0;

	/* send off cmds */
	wet = nt36672a_send_cmds(panew, pinfo->desc->off_cmds,
				 pinfo->desc->num_off_cmds);

	if (wet < 0)
		dev_eww(panew->dev, "faiwed to send DCS off cmds: %d\n", wet);

	wet = mipi_dsi_dcs_set_dispway_off(pinfo->wink);
	if (wet < 0)
		dev_eww(panew->dev, "set_dispway_off cmd faiwed wet = %d\n", wet);

	/* 120ms deway wequiwed hewe as pew DCS spec */
	msweep(120);

	wet = mipi_dsi_dcs_entew_sweep_mode(pinfo->wink);
	if (wet < 0)
		dev_eww(panew->dev, "entew_sweep cmd faiwed wet = %d\n", wet);

	/* 0x3C = 60ms deway */
	msweep(60);

	wet = nt36672a_panew_powew_off(panew);
	if (wet < 0)
		dev_eww(panew->dev, "powew_off faiwed wet = %d\n", wet);

	pinfo->pwepawed = fawse;

	wetuwn wet;
}

static int nt36672a_panew_powew_on(stwuct nt36672a_panew *pinfo)
{
	int wet;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(pinfo->suppwies), pinfo->suppwies);
	if (wet < 0)
		wetuwn wet;

	/*
	 * As pew downstweam kewnew, Weset sequence of Tianma FHD panew wequiwes the panew to
	 * be out of weset fow 10ms, fowwowed by being hewd in weset fow 10ms. But fow Andwoid
	 * AOSP, we needed to bump it upto 200ms othewwise we get white scween sometimes.
	 * FIXME: Twy to weduce this 200ms to a wessew vawue.
	 */
	gpiod_set_vawue(pinfo->weset_gpio, 1);
	msweep(200);
	gpiod_set_vawue(pinfo->weset_gpio, 0);
	msweep(200);

	wetuwn 0;
}

static int nt36672a_panew_pwepawe(stwuct dwm_panew *panew)
{
	stwuct nt36672a_panew *pinfo = to_nt36672a_panew(panew);
	int eww;

	if (pinfo->pwepawed)
		wetuwn 0;

	eww = nt36672a_panew_powew_on(pinfo);
	if (eww < 0)
		goto powewoff;

	/* send fiwst pawt of init cmds */
	eww = nt36672a_send_cmds(panew, pinfo->desc->on_cmds_1,
				 pinfo->desc->num_on_cmds_1);

	if (eww < 0) {
		dev_eww(panew->dev, "faiwed to send DCS Init 1st Code: %d\n", eww);
		goto powewoff;
	}

	eww = mipi_dsi_dcs_exit_sweep_mode(pinfo->wink);
	if (eww < 0) {
		dev_eww(panew->dev, "faiwed to exit sweep mode: %d\n", eww);
		goto powewoff;
	}

	/* 0x46 = 70 ms deway */
	msweep(70);

	eww = mipi_dsi_dcs_set_dispway_on(pinfo->wink);
	if (eww < 0) {
		dev_eww(panew->dev, "faiwed to Set Dispway ON: %d\n", eww);
		goto powewoff;
	}

	/* Send west of the init cmds */
	eww = nt36672a_send_cmds(panew, pinfo->desc->on_cmds_2,
				 pinfo->desc->num_on_cmds_2);

	if (eww < 0) {
		dev_eww(panew->dev, "faiwed to send DCS Init 2nd Code: %d\n", eww);
		goto powewoff;
	}

	msweep(120);

	pinfo->pwepawed = twue;

	wetuwn 0;

powewoff:
	gpiod_set_vawue(pinfo->weset_gpio, 0);
	wetuwn eww;
}

static int nt36672a_panew_get_modes(stwuct dwm_panew *panew,
				    stwuct dwm_connectow *connectow)
{
	stwuct nt36672a_panew *pinfo = to_nt36672a_panew(panew);
	const stwuct dwm_dispway_mode *m = pinfo->desc->dispway_mode;
	stwuct dwm_dispway_mode *mode;

	mode = dwm_mode_dupwicate(connectow->dev, m);
	if (!mode) {
		dev_eww(panew->dev, "faiwed to add mode %ux%u@%u\n", m->hdispway,
			m->vdispway, dwm_mode_vwefwesh(m));
		wetuwn -ENOMEM;
	}

	connectow->dispway_info.width_mm = pinfo->desc->width_mm;
	connectow->dispway_info.height_mm = pinfo->desc->height_mm;

	dwm_mode_set_name(mode);
	dwm_mode_pwobed_add(connectow, mode);

	wetuwn 1;
}

static const stwuct dwm_panew_funcs panew_funcs = {
	.unpwepawe = nt36672a_panew_unpwepawe,
	.pwepawe = nt36672a_panew_pwepawe,
	.get_modes = nt36672a_panew_get_modes,
};

static const stwuct nt36672a_panew_cmd tianma_fhd_video_on_cmds_1[] = {
	/* skin enhancement mode */
	{ .data = {0xFF, 0x22} },
	{ .data = {0x00, 0x40} },
	{ .data = {0x01, 0xC0} },
	{ .data = {0x02, 0x40} },
	{ .data = {0x03, 0x40} },
	{ .data = {0x04, 0x40} },
	{ .data = {0x05, 0x40} },
	{ .data = {0x06, 0x40} },
	{ .data = {0x07, 0x40} },
	{ .data = {0x08, 0x40} },
	{ .data = {0x09, 0x40} },
	{ .data = {0x0A, 0x40} },
	{ .data = {0x0B, 0x40} },
	{ .data = {0x0C, 0x40} },
	{ .data = {0x0D, 0x40} },
	{ .data = {0x0E, 0x40} },
	{ .data = {0x0F, 0x40} },
	{ .data = {0x10, 0x40} },
	{ .data = {0x11, 0x50} },
	{ .data = {0x12, 0x60} },
	{ .data = {0x13, 0x70} },
	{ .data = {0x14, 0x58} },
	{ .data = {0x15, 0x68} },
	{ .data = {0x16, 0x78} },
	{ .data = {0x17, 0x77} },
	{ .data = {0x18, 0x39} },
	{ .data = {0x19, 0x2D} },
	{ .data = {0x1A, 0x2E} },
	{ .data = {0x1B, 0x32} },
	{ .data = {0x1C, 0x37} },
	{ .data = {0x1D, 0x3A} },
	{ .data = {0x1E, 0x40} },
	{ .data = {0x1F, 0x40} },
	{ .data = {0x20, 0x40} },
	{ .data = {0x21, 0x40} },
	{ .data = {0x22, 0x40} },
	{ .data = {0x23, 0x40} },
	{ .data = {0x24, 0x40} },
	{ .data = {0x25, 0x40} },
	{ .data = {0x26, 0x40} },
	{ .data = {0x27, 0x40} },
	{ .data = {0x28, 0x40} },
	{ .data = {0x2D, 0x00} },
	{ .data = {0x2F, 0x40} },
	{ .data = {0x30, 0x40} },
	{ .data = {0x31, 0x40} },
	{ .data = {0x32, 0x40} },
	{ .data = {0x33, 0x40} },
	{ .data = {0x34, 0x40} },
	{ .data = {0x35, 0x40} },
	{ .data = {0x36, 0x40} },
	{ .data = {0x37, 0x40} },
	{ .data = {0x38, 0x40} },
	{ .data = {0x39, 0x40} },
	{ .data = {0x3A, 0x40} },
	{ .data = {0x3B, 0x40} },
	{ .data = {0x3D, 0x40} },
	{ .data = {0x3F, 0x40} },
	{ .data = {0x40, 0x40} },
	{ .data = {0x41, 0x40} },
	{ .data = {0x42, 0x40} },
	{ .data = {0x43, 0x40} },
	{ .data = {0x44, 0x40} },
	{ .data = {0x45, 0x40} },
	{ .data = {0x46, 0x40} },
	{ .data = {0x47, 0x40} },
	{ .data = {0x48, 0x40} },
	{ .data = {0x49, 0x40} },
	{ .data = {0x4A, 0x40} },
	{ .data = {0x4B, 0x40} },
	{ .data = {0x4C, 0x40} },
	{ .data = {0x4D, 0x40} },
	{ .data = {0x4E, 0x40} },
	{ .data = {0x4F, 0x40} },
	{ .data = {0x50, 0x40} },
	{ .data = {0x51, 0x40} },
	{ .data = {0x52, 0x40} },
	{ .data = {0x53, 0x01} },
	{ .data = {0x54, 0x01} },
	{ .data = {0x55, 0xFE} },
	{ .data = {0x56, 0x77} },
	{ .data = {0x58, 0xCD} },
	{ .data = {0x59, 0xD0} },
	{ .data = {0x5A, 0xD0} },
	{ .data = {0x5B, 0x50} },
	{ .data = {0x5C, 0x50} },
	{ .data = {0x5D, 0x50} },
	{ .data = {0x5E, 0x50} },
	{ .data = {0x5F, 0x50} },
	{ .data = {0x60, 0x50} },
	{ .data = {0x61, 0x50} },
	{ .data = {0x62, 0x50} },
	{ .data = {0x63, 0x50} },
	{ .data = {0x64, 0x50} },
	{ .data = {0x65, 0x50} },
	{ .data = {0x66, 0x50} },
	{ .data = {0x67, 0x50} },
	{ .data = {0x68, 0x50} },
	{ .data = {0x69, 0x50} },
	{ .data = {0x6A, 0x50} },
	{ .data = {0x6B, 0x50} },
	{ .data = {0x6C, 0x50} },
	{ .data = {0x6D, 0x50} },
	{ .data = {0x6E, 0x50} },
	{ .data = {0x6F, 0x50} },
	{ .data = {0x70, 0x07} },
	{ .data = {0x71, 0x00} },
	{ .data = {0x72, 0x00} },
	{ .data = {0x73, 0x00} },
	{ .data = {0x74, 0x06} },
	{ .data = {0x75, 0x0C} },
	{ .data = {0x76, 0x03} },
	{ .data = {0x77, 0x09} },
	{ .data = {0x78, 0x0F} },
	{ .data = {0x79, 0x68} },
	{ .data = {0x7A, 0x88} },
	{ .data = {0x7C, 0x80} },
	{ .data = {0x7D, 0x80} },
	{ .data = {0x7E, 0x80} },
	{ .data = {0x7F, 0x00} },
	{ .data = {0x80, 0x00} },
	{ .data = {0x81, 0x00} },
	{ .data = {0x83, 0x01} },
	{ .data = {0x84, 0x00} },
	{ .data = {0x85, 0x80} },
	{ .data = {0x86, 0x80} },
	{ .data = {0x87, 0x80} },
	{ .data = {0x88, 0x40} },
	{ .data = {0x89, 0x91} },
	{ .data = {0x8A, 0x98} },
	{ .data = {0x8B, 0x80} },
	{ .data = {0x8C, 0x80} },
	{ .data = {0x8D, 0x80} },
	{ .data = {0x8E, 0x80} },
	{ .data = {0x8F, 0x80} },
	{ .data = {0x90, 0x80} },
	{ .data = {0x91, 0x80} },
	{ .data = {0x92, 0x80} },
	{ .data = {0x93, 0x80} },
	{ .data = {0x94, 0x80} },
	{ .data = {0x95, 0x80} },
	{ .data = {0x96, 0x80} },
	{ .data = {0x97, 0x80} },
	{ .data = {0x98, 0x80} },
	{ .data = {0x99, 0x80} },
	{ .data = {0x9A, 0x80} },
	{ .data = {0x9B, 0x80} },
	{ .data = {0x9C, 0x80} },
	{ .data = {0x9D, 0x80} },
	{ .data = {0x9E, 0x80} },
	{ .data = {0x9F, 0x80} },
	{ .data = {0xA0, 0x8A} },
	{ .data = {0xA2, 0x80} },
	{ .data = {0xA6, 0x80} },
	{ .data = {0xA7, 0x80} },
	{ .data = {0xA9, 0x80} },
	{ .data = {0xAA, 0x80} },
	{ .data = {0xAB, 0x80} },
	{ .data = {0xAC, 0x80} },
	{ .data = {0xAD, 0x80} },
	{ .data = {0xAE, 0x80} },
	{ .data = {0xAF, 0x80} },
	{ .data = {0xB7, 0x76} },
	{ .data = {0xB8, 0x76} },
	{ .data = {0xB9, 0x05} },
	{ .data = {0xBA, 0x0D} },
	{ .data = {0xBB, 0x14} },
	{ .data = {0xBC, 0x0F} },
	{ .data = {0xBD, 0x18} },
	{ .data = {0xBE, 0x1F} },
	{ .data = {0xBF, 0x05} },
	{ .data = {0xC0, 0x0D} },
	{ .data = {0xC1, 0x14} },
	{ .data = {0xC2, 0x03} },
	{ .data = {0xC3, 0x07} },
	{ .data = {0xC4, 0x0A} },
	{ .data = {0xC5, 0xA0} },
	{ .data = {0xC6, 0x55} },
	{ .data = {0xC7, 0xFF} },
	{ .data = {0xC8, 0x39} },
	{ .data = {0xC9, 0x44} },
	{ .data = {0xCA, 0x12} },
	{ .data = {0xCD, 0x80} },
	{ .data = {0xDB, 0x80} },
	{ .data = {0xDC, 0x80} },
	{ .data = {0xDD, 0x80} },
	{ .data = {0xE0, 0x80} },
	{ .data = {0xE1, 0x80} },
	{ .data = {0xE2, 0x80} },
	{ .data = {0xE3, 0x80} },
	{ .data = {0xE4, 0x80} },
	{ .data = {0xE5, 0x40} },
	{ .data = {0xE6, 0x40} },
	{ .data = {0xE7, 0x40} },
	{ .data = {0xE8, 0x40} },
	{ .data = {0xE9, 0x40} },
	{ .data = {0xEA, 0x40} },
	{ .data = {0xEB, 0x40} },
	{ .data = {0xEC, 0x40} },
	{ .data = {0xED, 0x40} },
	{ .data = {0xEE, 0x40} },
	{ .data = {0xEF, 0x40} },
	{ .data = {0xF0, 0x40} },
	{ .data = {0xF1, 0x40} },
	{ .data = {0xF2, 0x40} },
	{ .data = {0xF3, 0x40} },
	{ .data = {0xF4, 0x40} },
	{ .data = {0xF5, 0x40} },
	{ .data = {0xF6, 0x40} },
	{ .data = {0xFB, 0x1} },
	{ .data = {0xFF, 0x23} },
	{ .data = {0xFB, 0x01} },
	/* dimming enabwe */
	{ .data = {0x01, 0x84} },
	{ .data = {0x05, 0x2D} },
	{ .data = {0x06, 0x00} },
	 /* wesowution 1080*2246 */
	{ .data = {0x11, 0x01} },
	{ .data = {0x12, 0x7B} },
	{ .data = {0x15, 0x6F} },
	{ .data = {0x16, 0x0B} },
	 /* UI mode */
	{ .data = {0x29, 0x0A} },
	{ .data = {0x30, 0xFF} },
	{ .data = {0x31, 0xFF} },
	{ .data = {0x32, 0xFF} },
	{ .data = {0x33, 0xFF} },
	{ .data = {0x34, 0xFF} },
	{ .data = {0x35, 0xFF} },
	{ .data = {0x36, 0xFF} },
	{ .data = {0x37, 0xFF} },
	{ .data = {0x38, 0xFC} },
	{ .data = {0x39, 0xF8} },
	{ .data = {0x3A, 0xF4} },
	{ .data = {0x3B, 0xF1} },
	{ .data = {0x3D, 0xEE} },
	{ .data = {0x3F, 0xEB} },
	{ .data = {0x40, 0xE8} },
	{ .data = {0x41, 0xE5} },
	 /* STIWW mode */
	{ .data = {0x2A, 0x13} },
	{ .data = {0x45, 0xFF} },
	{ .data = {0x46, 0xFF} },
	{ .data = {0x47, 0xFF} },
	{ .data = {0x48, 0xFF} },
	{ .data = {0x49, 0xFF} },
	{ .data = {0x4A, 0xFF} },
	{ .data = {0x4B, 0xFF} },
	{ .data = {0x4C, 0xFF} },
	{ .data = {0x4D, 0xED} },
	{ .data = {0x4E, 0xD5} },
	{ .data = {0x4F, 0xBF} },
	{ .data = {0x50, 0xA6} },
	{ .data = {0x51, 0x96} },
	{ .data = {0x52, 0x86} },
	{ .data = {0x53, 0x76} },
	{ .data = {0x54, 0x66} },
	 /* MOVING mode */
	{ .data = {0x2B, 0x0E} },
	{ .data = {0x58, 0xFF} },
	{ .data = {0x59, 0xFF} },
	{ .data = {0x5A, 0xFF} },
	{ .data = {0x5B, 0xFF} },
	{ .data = {0x5C, 0xFF} },
	{ .data = {0x5D, 0xFF} },
	{ .data = {0x5E, 0xFF} },
	{ .data = {0x5F, 0xFF} },
	{ .data = {0x60, 0xF6} },
	{ .data = {0x61, 0xEA} },
	{ .data = {0x62, 0xE1} },
	{ .data = {0x63, 0xD8} },
	{ .data = {0x64, 0xCE} },
	{ .data = {0x65, 0xC3} },
	{ .data = {0x66, 0xBA} },
	{ .data = {0x67, 0xB3} },
	{ .data = {0xFF, 0x25} },
	{ .data = {0xFB, 0x01} },
	{ .data = {0x05, 0x04} },
	{ .data = {0xFF, 0x26} },
	{ .data = {0xFB, 0x01} },
	{ .data = {0x1C, 0xAF} },
	{ .data = {0xFF, 0x10} },
	{ .data = {0xFB, 0x01} },
	{ .data = {0x51, 0xFF} },
	{ .data = {0x53, 0x24} },
	{ .data = {0x55, 0x00} },
};

static const stwuct nt36672a_panew_cmd tianma_fhd_video_on_cmds_2[] = {
	{ .data = {0xFF, 0x24} },
	{ .data = {0xFB, 0x01} },
	{ .data = {0xC3, 0x01} },
	{ .data = {0xC4, 0x54} },
	{ .data = {0xFF, 0x10} },
};

static const stwuct nt36672a_panew_cmd tianma_fhd_video_off_cmds[] = {
	{ .data = {0xFF, 0x24} },
	{ .data = {0xFB, 0x01} },
	{ .data = {0xC3, 0x01} },
	{ .data = {0xFF, 0x10} },
};

static const stwuct dwm_dispway_mode tianma_fhd_video_panew_defauwt_mode = {
	.cwock		= 161331,

	.hdispway	= 1080,
	.hsync_stawt	= 1080 + 40,
	.hsync_end	= 1080 + 40 + 20,
	.htotaw		= 1080 + 40 + 20 + 44,

	.vdispway	= 2246,
	.vsync_stawt	= 2246 + 15,
	.vsync_end	= 2246 + 15 + 2,
	.vtotaw		= 2246 + 15 + 2 + 8,

	.type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED,
};

static const stwuct nt36672a_panew_desc tianma_fhd_video_panew_desc = {
	.dispway_mode = &tianma_fhd_video_panew_defauwt_mode,

	.width_mm = 68,
	.height_mm = 136,

	.mode_fwags = MIPI_DSI_MODE_WPM | MIPI_DSI_MODE_VIDEO
			| MIPI_DSI_MODE_VIDEO_HSE
			| MIPI_DSI_CWOCK_NON_CONTINUOUS
			| MIPI_DSI_MODE_VIDEO_BUWST,
	.fowmat = MIPI_DSI_FMT_WGB888,
	.wanes = 4,
	.on_cmds_1 = tianma_fhd_video_on_cmds_1,
	.num_on_cmds_1 = AWWAY_SIZE(tianma_fhd_video_on_cmds_1),
	.on_cmds_2 = tianma_fhd_video_on_cmds_2,
	.num_on_cmds_2 = AWWAY_SIZE(tianma_fhd_video_on_cmds_2),
	.off_cmds = tianma_fhd_video_off_cmds,
	.num_off_cmds = AWWAY_SIZE(tianma_fhd_video_off_cmds),
};

static int nt36672a_panew_add(stwuct nt36672a_panew *pinfo)
{
	stwuct device *dev = &pinfo->wink->dev;
	int i, wet;

	fow (i = 0; i < AWWAY_SIZE(pinfo->suppwies); i++)
		pinfo->suppwies[i].suppwy = nt36672a_weguwatow_names[i];

	wet = devm_weguwatow_buwk_get(dev, AWWAY_SIZE(pinfo->suppwies),
				      pinfo->suppwies);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to get weguwatows\n");

	fow (i = 0; i < AWWAY_SIZE(pinfo->suppwies); i++) {
		wet = weguwatow_set_woad(pinfo->suppwies[i].consumew,
					 nt36672a_weguwatow_enabwe_woads[i]);
		if (wet)
			wetuwn dev_eww_pwobe(dev, wet, "faiwed to set weguwatow enabwe woads\n");
	}

	pinfo->weset_gpio = devm_gpiod_get(dev, "weset", GPIOD_OUT_WOW);
	if (IS_EWW(pinfo->weset_gpio))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pinfo->weset_gpio),
				     "faiwed to get weset gpio fwom DT\n");

	dwm_panew_init(&pinfo->base, dev, &panew_funcs, DWM_MODE_CONNECTOW_DSI);

	wet = dwm_panew_of_backwight(&pinfo->base);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to get backwight\n");

	dwm_panew_add(&pinfo->base);

	wetuwn 0;
}

static int nt36672a_panew_pwobe(stwuct mipi_dsi_device *dsi)
{
	stwuct nt36672a_panew *pinfo;
	const stwuct nt36672a_panew_desc *desc;
	int eww;

	pinfo = devm_kzawwoc(&dsi->dev, sizeof(*pinfo), GFP_KEWNEW);
	if (!pinfo)
		wetuwn -ENOMEM;

	desc = of_device_get_match_data(&dsi->dev);
	dsi->mode_fwags = desc->mode_fwags;
	dsi->fowmat = desc->fowmat;
	dsi->wanes = desc->wanes;
	pinfo->desc = desc;
	pinfo->wink = dsi;

	mipi_dsi_set_dwvdata(dsi, pinfo);

	eww = nt36672a_panew_add(pinfo);
	if (eww < 0)
		wetuwn eww;

	eww = mipi_dsi_attach(dsi);
	if (eww < 0) {
		dwm_panew_wemove(&pinfo->base);
		wetuwn eww;
	}

	wetuwn 0;
}

static void nt36672a_panew_wemove(stwuct mipi_dsi_device *dsi)
{
	stwuct nt36672a_panew *pinfo = mipi_dsi_get_dwvdata(dsi);
	int eww;

	eww = dwm_panew_unpwepawe(&pinfo->base);
	if (eww < 0)
		dev_eww(&dsi->dev, "faiwed to unpwepawe panew: %d\n", eww);

	eww = dwm_panew_disabwe(&pinfo->base);
	if (eww < 0)
		dev_eww(&dsi->dev, "faiwed to disabwe panew: %d\n", eww);

	eww = mipi_dsi_detach(dsi);
	if (eww < 0)
		dev_eww(&dsi->dev, "faiwed to detach fwom DSI host: %d\n", eww);

	dwm_panew_wemove(&pinfo->base);
}

static void nt36672a_panew_shutdown(stwuct mipi_dsi_device *dsi)
{
	stwuct nt36672a_panew *pinfo = mipi_dsi_get_dwvdata(dsi);

	dwm_panew_disabwe(&pinfo->base);
	dwm_panew_unpwepawe(&pinfo->base);
}

static const stwuct of_device_id tianma_fhd_video_of_match[] = {
	{ .compatibwe = "tianma,fhd-video", .data = &tianma_fhd_video_panew_desc },
	{ },
};
MODUWE_DEVICE_TABWE(of, tianma_fhd_video_of_match);

static stwuct mipi_dsi_dwivew nt36672a_panew_dwivew = {
	.dwivew = {
		.name = "panew-tianma-nt36672a",
		.of_match_tabwe = tianma_fhd_video_of_match,
	},
	.pwobe = nt36672a_panew_pwobe,
	.wemove = nt36672a_panew_wemove,
	.shutdown = nt36672a_panew_shutdown,
};
moduwe_mipi_dsi_dwivew(nt36672a_panew_dwivew);

MODUWE_AUTHOW("Sumit Semwaw <sumit.semwaw@winawo.owg>");
MODUWE_DESCWIPTION("NOVATEK NT36672A based MIPI-DSI WCD panew dwivew");
MODUWE_WICENSE("GPW");
