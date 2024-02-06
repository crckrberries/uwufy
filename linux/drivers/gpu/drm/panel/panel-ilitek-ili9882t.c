// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Panews based on the Iwitek IWI9882T dispway contwowwew.
 */
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_panew.h>

#incwude <video/mipi_dispway.h>

/*
 * Use this descwiptow stwuct to descwibe diffewent panews using the
 * Iwitek IWI9882T dispway contwowwew.
 */
stwuct panew_desc {
	const stwuct dwm_dispway_mode *modes;
	unsigned int bpc;

	/**
	 * @width_mm: width of the panew's active dispway awea
	 * @height_mm: height of the panew's active dispway awea
	 */
	stwuct {
		unsigned int width_mm;
		unsigned int height_mm;
	} size;

	unsigned wong mode_fwags;
	enum mipi_dsi_pixew_fowmat fowmat;
	const stwuct panew_init_cmd *init_cmds;
	unsigned int wanes;
};

stwuct iwi9882t {
	stwuct dwm_panew base;
	stwuct mipi_dsi_device *dsi;

	const stwuct panew_desc *desc;

	enum dwm_panew_owientation owientation;
	stwuct weguwatow *pp3300;
	stwuct weguwatow *pp1800;
	stwuct weguwatow *avee;
	stwuct weguwatow *avdd;
	stwuct gpio_desc *enabwe_gpio;
};

enum dsi_cmd_type {
	INIT_DCS_CMD,
	DEWAY_CMD,
};

stwuct panew_init_cmd {
	enum dsi_cmd_type type;
	size_t wen;
	const chaw *data;
};

#define _INIT_DCS_CMD(...) { \
	.type = INIT_DCS_CMD, \
	.wen = sizeof((chaw[]){__VA_AWGS__}), \
	.data = (chaw[]){__VA_AWGS__} }

#define _INIT_DEWAY_CMD(...) { \
	.type = DEWAY_CMD,\
	.wen = sizeof((chaw[]){__VA_AWGS__}), \
	.data = (chaw[]){__VA_AWGS__} }

/* IWI9882-specific commands, add new commands as you decode them */
#define IWI9882T_DCS_SWITCH_PAGE	0xFF

#define _INIT_SWITCH_PAGE_CMD(page) \
	_INIT_DCS_CMD(IWI9882T_DCS_SWITCH_PAGE, 0x98, 0x82, (page))

static const stwuct panew_init_cmd stawwy_iwi9882t_init_cmd[] = {
	_INIT_DEWAY_CMD(5),
	_INIT_SWITCH_PAGE_CMD(0x01),
	_INIT_DCS_CMD(0x00, 0x42),
	_INIT_DCS_CMD(0x01, 0x11),
	_INIT_DCS_CMD(0x02, 0x00),
	_INIT_DCS_CMD(0x03, 0x00),

	_INIT_DCS_CMD(0x04, 0x01),
	_INIT_DCS_CMD(0x05, 0x11),
	_INIT_DCS_CMD(0x06, 0x00),
	_INIT_DCS_CMD(0x07, 0x00),

	_INIT_DCS_CMD(0x08, 0x80),
	_INIT_DCS_CMD(0x09, 0x81),
	_INIT_DCS_CMD(0x0A, 0x71),
	_INIT_DCS_CMD(0x0B, 0x00),

	_INIT_DCS_CMD(0x0C, 0x00),
	_INIT_DCS_CMD(0x0E, 0x1A),

	_INIT_DCS_CMD(0x24, 0x00),
	_INIT_DCS_CMD(0x25, 0x00),
	_INIT_DCS_CMD(0x26, 0x00),
	_INIT_DCS_CMD(0x27, 0x00),

	_INIT_DCS_CMD(0x2C, 0xD4),
	_INIT_DCS_CMD(0xB9, 0x40),

	_INIT_DCS_CMD(0xB0, 0x11),

	_INIT_DCS_CMD(0xE6, 0x32),
	_INIT_DCS_CMD(0xD1, 0x30),

	_INIT_DCS_CMD(0xD6, 0x55),

	_INIT_DCS_CMD(0xD0, 0x01),
	_INIT_DCS_CMD(0xE3, 0x93),
	_INIT_DCS_CMD(0xE4, 0x00),
	_INIT_DCS_CMD(0xE5, 0x80),

	_INIT_DCS_CMD(0x31, 0x07),
	_INIT_DCS_CMD(0x32, 0x07),
	_INIT_DCS_CMD(0x33, 0x07),
	_INIT_DCS_CMD(0x34, 0x07),
	_INIT_DCS_CMD(0x35, 0x07),
	_INIT_DCS_CMD(0x36, 0x01),
	_INIT_DCS_CMD(0x37, 0x00),
	_INIT_DCS_CMD(0x38, 0x28),
	_INIT_DCS_CMD(0x39, 0x29),
	_INIT_DCS_CMD(0x3A, 0x11),
	_INIT_DCS_CMD(0x3B, 0x13),
	_INIT_DCS_CMD(0x3C, 0x15),
	_INIT_DCS_CMD(0x3D, 0x17),
	_INIT_DCS_CMD(0x3E, 0x09),
	_INIT_DCS_CMD(0x3F, 0x0D),
	_INIT_DCS_CMD(0x40, 0x02),
	_INIT_DCS_CMD(0x41, 0x02),
	_INIT_DCS_CMD(0x42, 0x02),
	_INIT_DCS_CMD(0x43, 0x02),
	_INIT_DCS_CMD(0x44, 0x02),
	_INIT_DCS_CMD(0x45, 0x02),
	_INIT_DCS_CMD(0x46, 0x02),

	_INIT_DCS_CMD(0x47, 0x07),
	_INIT_DCS_CMD(0x48, 0x07),
	_INIT_DCS_CMD(0x49, 0x07),
	_INIT_DCS_CMD(0x4A, 0x07),
	_INIT_DCS_CMD(0x4B, 0x07),
	_INIT_DCS_CMD(0x4C, 0x01),
	_INIT_DCS_CMD(0x4D, 0x00),
	_INIT_DCS_CMD(0x4E, 0x28),
	_INIT_DCS_CMD(0x4F, 0x29),
	_INIT_DCS_CMD(0x50, 0x10),
	_INIT_DCS_CMD(0x51, 0x12),
	_INIT_DCS_CMD(0x52, 0x14),
	_INIT_DCS_CMD(0x53, 0x16),
	_INIT_DCS_CMD(0x54, 0x08),
	_INIT_DCS_CMD(0x55, 0x0C),
	_INIT_DCS_CMD(0x56, 0x02),
	_INIT_DCS_CMD(0x57, 0x02),
	_INIT_DCS_CMD(0x58, 0x02),
	_INIT_DCS_CMD(0x59, 0x02),
	_INIT_DCS_CMD(0x5A, 0x02),
	_INIT_DCS_CMD(0x5B, 0x02),
	_INIT_DCS_CMD(0x5C, 0x02),

	_INIT_DCS_CMD(0x61, 0x07),
	_INIT_DCS_CMD(0x62, 0x07),
	_INIT_DCS_CMD(0x63, 0x07),
	_INIT_DCS_CMD(0x64, 0x07),
	_INIT_DCS_CMD(0x65, 0x07),
	_INIT_DCS_CMD(0x66, 0x01),
	_INIT_DCS_CMD(0x67, 0x00),
	_INIT_DCS_CMD(0x68, 0x28),
	_INIT_DCS_CMD(0x69, 0x29),
	_INIT_DCS_CMD(0x6A, 0x16),
	_INIT_DCS_CMD(0x6B, 0x14),
	_INIT_DCS_CMD(0x6C, 0x12),
	_INIT_DCS_CMD(0x6D, 0x10),
	_INIT_DCS_CMD(0x6E, 0x0C),
	_INIT_DCS_CMD(0x6F, 0x08),
	_INIT_DCS_CMD(0x70, 0x02),
	_INIT_DCS_CMD(0x71, 0x02),
	_INIT_DCS_CMD(0x72, 0x02),
	_INIT_DCS_CMD(0x73, 0x02),
	_INIT_DCS_CMD(0x74, 0x02),
	_INIT_DCS_CMD(0x75, 0x02),
	_INIT_DCS_CMD(0x76, 0x02),

	_INIT_DCS_CMD(0x77, 0x07),
	_INIT_DCS_CMD(0x78, 0x07),
	_INIT_DCS_CMD(0x79, 0x07),
	_INIT_DCS_CMD(0x7A, 0x07),
	_INIT_DCS_CMD(0x7B, 0x07),
	_INIT_DCS_CMD(0x7C, 0x01),
	_INIT_DCS_CMD(0x7D, 0x00),
	_INIT_DCS_CMD(0x7E, 0x28),
	_INIT_DCS_CMD(0x7F, 0x29),
	_INIT_DCS_CMD(0x80, 0x17),
	_INIT_DCS_CMD(0x81, 0x15),
	_INIT_DCS_CMD(0x82, 0x13),
	_INIT_DCS_CMD(0x83, 0x11),
	_INIT_DCS_CMD(0x84, 0x0D),
	_INIT_DCS_CMD(0x85, 0x09),
	_INIT_DCS_CMD(0x86, 0x02),
	_INIT_DCS_CMD(0x87, 0x07),
	_INIT_DCS_CMD(0x88, 0x07),
	_INIT_DCS_CMD(0x89, 0x07),
	_INIT_DCS_CMD(0x8A, 0x07),
	_INIT_DCS_CMD(0x8B, 0x07),
	_INIT_DCS_CMD(0x8C, 0x07),

	_INIT_SWITCH_PAGE_CMD(0x02),
	_INIT_DCS_CMD(0x29, 0x3A),
	_INIT_DCS_CMD(0x2A, 0x3B),

	_INIT_DCS_CMD(0x06, 0x01),
	_INIT_DCS_CMD(0x07, 0x01),
	_INIT_DCS_CMD(0x08, 0x0C),
	_INIT_DCS_CMD(0x09, 0x44),

	_INIT_DCS_CMD(0x3C, 0x0A),
	_INIT_DCS_CMD(0x39, 0x11),
	_INIT_DCS_CMD(0x3D, 0x00),
	_INIT_DCS_CMD(0x3A, 0x0C),
	_INIT_DCS_CMD(0x3B, 0x44),

	_INIT_DCS_CMD(0x53, 0x1F),
	_INIT_DCS_CMD(0x5E, 0x40),
	_INIT_DCS_CMD(0x84, 0x00),

	_INIT_SWITCH_PAGE_CMD(0x03),
	_INIT_DCS_CMD(0x20, 0x01),
	_INIT_DCS_CMD(0x21, 0x3C),
	_INIT_DCS_CMD(0x22, 0xFA),

	_INIT_SWITCH_PAGE_CMD(0x0A),
	_INIT_DCS_CMD(0xE0, 0x01),
	_INIT_DCS_CMD(0xE2, 0x01),
	_INIT_DCS_CMD(0xE5, 0x91),
	_INIT_DCS_CMD(0xE6, 0x3C),
	_INIT_DCS_CMD(0xE7, 0x00),
	_INIT_DCS_CMD(0xE8, 0xFA),

	_INIT_SWITCH_PAGE_CMD(0x12),
	_INIT_DCS_CMD(0x87, 0x2C),

	_INIT_SWITCH_PAGE_CMD(0x05),
	_INIT_DCS_CMD(0x73, 0xE5),
	_INIT_DCS_CMD(0x7F, 0x6B),
	_INIT_DCS_CMD(0x6D, 0xA4),
	_INIT_DCS_CMD(0x79, 0x54),
	_INIT_DCS_CMD(0x69, 0x97),
	_INIT_DCS_CMD(0x6A, 0x97),
	_INIT_DCS_CMD(0xA5, 0x3F),
	_INIT_DCS_CMD(0x61, 0xDA),
	_INIT_DCS_CMD(0xA7, 0xF1),
	_INIT_DCS_CMD(0x5F, 0x01),
	_INIT_DCS_CMD(0x62, 0x3F),
	_INIT_DCS_CMD(0x1D, 0x90),
	_INIT_DCS_CMD(0x86, 0x87),

	_INIT_SWITCH_PAGE_CMD(0x06),
	_INIT_DCS_CMD(0xC0, 0x80),
	_INIT_DCS_CMD(0xC1, 0x07),
	_INIT_DCS_CMD(0xCA, 0x58),
	_INIT_DCS_CMD(0xCB, 0x02),
	_INIT_DCS_CMD(0xCE, 0x58),
	_INIT_DCS_CMD(0xCF, 0x02),
	_INIT_DCS_CMD(0x67, 0x60),
	_INIT_DCS_CMD(0x10, 0x00),
	_INIT_DCS_CMD(0x92, 0x22),
	_INIT_DCS_CMD(0xD3, 0x08),
	_INIT_DCS_CMD(0xD6, 0x55),
	_INIT_DCS_CMD(0xDC, 0x38),

	_INIT_SWITCH_PAGE_CMD(0x08),
	_INIT_DCS_CMD(0xE0, 0x00, 0x10, 0x2A, 0x4D, 0x61, 0x56, 0x6A, 0x6E, 0x79, 0x76, 0x8F, 0x95, 0x98, 0xAE, 0xAA, 0xB2, 0xBB, 0xCE, 0xC6, 0xBD, 0xD5, 0xE2, 0xE8),
	_INIT_DCS_CMD(0xE1, 0x00, 0x10, 0x2A, 0x4D, 0x61, 0x56, 0x6A, 0x6E, 0x79, 0x76, 0x8F, 0x95, 0x98, 0xAE, 0xAA, 0xB2, 0xBB, 0xCE, 0xC6, 0xBD, 0xD5, 0xE2, 0xE8),

	_INIT_SWITCH_PAGE_CMD(0x04),
	_INIT_DCS_CMD(0xBA, 0x81),

	_INIT_SWITCH_PAGE_CMD(0x0C),
	_INIT_DCS_CMD(0x00, 0x02),
	_INIT_DCS_CMD(0x01, 0x00),
	_INIT_DCS_CMD(0x02, 0x03),
	_INIT_DCS_CMD(0x03, 0x01),
	_INIT_DCS_CMD(0x04, 0x03),
	_INIT_DCS_CMD(0x05, 0x02),
	_INIT_DCS_CMD(0x06, 0x04),
	_INIT_DCS_CMD(0x07, 0x03),
	_INIT_DCS_CMD(0x08, 0x03),
	_INIT_DCS_CMD(0x09, 0x04),
	_INIT_DCS_CMD(0x0A, 0x04),
	_INIT_DCS_CMD(0x0B, 0x05),
	_INIT_DCS_CMD(0x0C, 0x04),
	_INIT_DCS_CMD(0x0D, 0x06),
	_INIT_DCS_CMD(0x0E, 0x05),
	_INIT_DCS_CMD(0x0F, 0x07),
	_INIT_DCS_CMD(0x10, 0x04),
	_INIT_DCS_CMD(0x11, 0x08),
	_INIT_DCS_CMD(0x12, 0x05),
	_INIT_DCS_CMD(0x13, 0x09),
	_INIT_DCS_CMD(0x14, 0x05),
	_INIT_DCS_CMD(0x15, 0x0A),
	_INIT_DCS_CMD(0x16, 0x06),
	_INIT_DCS_CMD(0x17, 0x0B),
	_INIT_DCS_CMD(0x18, 0x05),
	_INIT_DCS_CMD(0x19, 0x0C),
	_INIT_DCS_CMD(0x1A, 0x06),
	_INIT_DCS_CMD(0x1B, 0x0D),
	_INIT_DCS_CMD(0x1C, 0x06),
	_INIT_DCS_CMD(0x1D, 0x0E),
	_INIT_DCS_CMD(0x1E, 0x07),
	_INIT_DCS_CMD(0x1F, 0x0F),
	_INIT_DCS_CMD(0x20, 0x06),
	_INIT_DCS_CMD(0x21, 0x10),
	_INIT_DCS_CMD(0x22, 0x07),
	_INIT_DCS_CMD(0x23, 0x11),
	_INIT_DCS_CMD(0x24, 0x07),
	_INIT_DCS_CMD(0x25, 0x12),
	_INIT_DCS_CMD(0x26, 0x08),
	_INIT_DCS_CMD(0x27, 0x13),
	_INIT_DCS_CMD(0x28, 0x07),
	_INIT_DCS_CMD(0x29, 0x14),
	_INIT_DCS_CMD(0x2A, 0x08),
	_INIT_DCS_CMD(0x2B, 0x15),
	_INIT_DCS_CMD(0x2C, 0x08),
	_INIT_DCS_CMD(0x2D, 0x16),
	_INIT_DCS_CMD(0x2E, 0x09),
	_INIT_DCS_CMD(0x2F, 0x17),
	_INIT_DCS_CMD(0x30, 0x08),
	_INIT_DCS_CMD(0x31, 0x18),
	_INIT_DCS_CMD(0x32, 0x09),
	_INIT_DCS_CMD(0x33, 0x19),
	_INIT_DCS_CMD(0x34, 0x09),
	_INIT_DCS_CMD(0x35, 0x1A),
	_INIT_DCS_CMD(0x36, 0x0A),
	_INIT_DCS_CMD(0x37, 0x1B),
	_INIT_DCS_CMD(0x38, 0x0A),
	_INIT_DCS_CMD(0x39, 0x1C),
	_INIT_DCS_CMD(0x3A, 0x0A),
	_INIT_DCS_CMD(0x3B, 0x1D),
	_INIT_DCS_CMD(0x3C, 0x0A),
	_INIT_DCS_CMD(0x3D, 0x1E),
	_INIT_DCS_CMD(0x3E, 0x0A),
	_INIT_DCS_CMD(0x3F, 0x1F),

	_INIT_SWITCH_PAGE_CMD(0x04),
	_INIT_DCS_CMD(0xBA, 0x01),

	_INIT_SWITCH_PAGE_CMD(0x0E),
	_INIT_DCS_CMD(0x02, 0x0C),
	_INIT_DCS_CMD(0x20, 0x10),
	_INIT_DCS_CMD(0x25, 0x16),
	_INIT_DCS_CMD(0x26, 0xE0),
	_INIT_DCS_CMD(0x27, 0x00),
	_INIT_DCS_CMD(0x29, 0x71),
	_INIT_DCS_CMD(0x2A, 0x46),
	_INIT_DCS_CMD(0x2B, 0x1F),
	_INIT_DCS_CMD(0x2D, 0xC7),
	_INIT_DCS_CMD(0x31, 0x02),
	_INIT_DCS_CMD(0x32, 0xDF),
	_INIT_DCS_CMD(0x33, 0x5A),
	_INIT_DCS_CMD(0x34, 0xC0),
	_INIT_DCS_CMD(0x35, 0x5A),
	_INIT_DCS_CMD(0x36, 0xC0),
	_INIT_DCS_CMD(0x38, 0x65),
	_INIT_DCS_CMD(0x80, 0x3E),
	_INIT_DCS_CMD(0x81, 0xA0),
	_INIT_DCS_CMD(0xB0, 0x01),
	_INIT_DCS_CMD(0xB1, 0xCC),
	_INIT_DCS_CMD(0xC0, 0x12),
	_INIT_DCS_CMD(0xC2, 0xCC),
	_INIT_DCS_CMD(0xC3, 0xCC),
	_INIT_DCS_CMD(0xC4, 0xCC),
	_INIT_DCS_CMD(0xC5, 0xCC),
	_INIT_DCS_CMD(0xC6, 0xCC),
	_INIT_DCS_CMD(0xC7, 0xCC),
	_INIT_DCS_CMD(0xC8, 0xCC),
	_INIT_DCS_CMD(0xC9, 0xCC),
	_INIT_DCS_CMD(0x30, 0x00),
	_INIT_DCS_CMD(0x00, 0x81),
	_INIT_DCS_CMD(0x08, 0x02),
	_INIT_DCS_CMD(0x09, 0x00),
	_INIT_DCS_CMD(0x07, 0x21),
	_INIT_DCS_CMD(0x04, 0x10),

	_INIT_SWITCH_PAGE_CMD(0x1E),
	_INIT_DCS_CMD(0x60, 0x00),
	_INIT_DCS_CMD(0x64, 0x00),
	_INIT_DCS_CMD(0x6D, 0x00),

	_INIT_SWITCH_PAGE_CMD(0x0B),
	_INIT_DCS_CMD(0xA6, 0x44),
	_INIT_DCS_CMD(0xA7, 0xB6),
	_INIT_DCS_CMD(0xA8, 0x03),
	_INIT_DCS_CMD(0xA9, 0x03),
	_INIT_DCS_CMD(0xAA, 0x51),
	_INIT_DCS_CMD(0xAB, 0x51),
	_INIT_DCS_CMD(0xAC, 0x04),
	_INIT_DCS_CMD(0xBD, 0x92),
	_INIT_DCS_CMD(0xBE, 0xA1),

	_INIT_SWITCH_PAGE_CMD(0x05),
	_INIT_DCS_CMD(0x86, 0x87),

	_INIT_SWITCH_PAGE_CMD(0x06),
	_INIT_DCS_CMD(0x92, 0x22),

	_INIT_SWITCH_PAGE_CMD(0x00),
	_INIT_DCS_CMD(MIPI_DCS_EXIT_SWEEP_MODE),
	_INIT_DEWAY_CMD(120),
	_INIT_DCS_CMD(MIPI_DCS_SET_DISPWAY_ON),
	_INIT_DEWAY_CMD(20),
	{},
};

static inwine stwuct iwi9882t *to_iwi9882t(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct iwi9882t, base);
}

static int iwi9882t_init_dcs_cmd(stwuct iwi9882t *iwi)
{
	stwuct mipi_dsi_device *dsi = iwi->dsi;
	stwuct dwm_panew *panew = &iwi->base;
	int i, eww = 0;

	if (iwi->desc->init_cmds) {
		const stwuct panew_init_cmd *init_cmds = iwi->desc->init_cmds;

		fow (i = 0; init_cmds[i].wen != 0; i++) {
			const stwuct panew_init_cmd *cmd = &init_cmds[i];

			switch (cmd->type) {
			case DEWAY_CMD:
				msweep(cmd->data[0]);
				eww = 0;
				bweak;

			case INIT_DCS_CMD:
				eww = mipi_dsi_dcs_wwite(dsi, cmd->data[0],
							 cmd->wen <= 1 ? NUWW :
							 &cmd->data[1],
							 cmd->wen - 1);
				bweak;

			defauwt:
				eww = -EINVAW;
			}

			if (eww < 0) {
				dev_eww(panew->dev,
					"faiwed to wwite command %u\n", i);
				wetuwn eww;
			}
		}
	}
	wetuwn 0;
}

static int iwi9882t_switch_page(stwuct mipi_dsi_device *dsi, u8 page)
{
	int wet;
	const stwuct panew_init_cmd cmd = _INIT_SWITCH_PAGE_CMD(page);

	wet = mipi_dsi_dcs_wwite(dsi, cmd.data[0],
				 cmd.wen <= 1 ? NUWW :
				 &cmd.data[1],
				 cmd.wen - 1);
	if (wet) {
		dev_eww(&dsi->dev,
			"ewwow switching panew contwowwew page (%d)\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int iwi9882t_entew_sweep_mode(stwuct iwi9882t *iwi)
{
	stwuct mipi_dsi_device *dsi = iwi->dsi;
	int wet;

	dsi->mode_fwags &= ~MIPI_DSI_MODE_WPM;

	wet = mipi_dsi_dcs_set_dispway_off(dsi);
	if (wet < 0)
		wetuwn wet;

	wet = mipi_dsi_dcs_entew_sweep_mode(dsi);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int iwi9882t_disabwe(stwuct dwm_panew *panew)
{
	stwuct iwi9882t *iwi = to_iwi9882t(panew);
	stwuct mipi_dsi_device *dsi = iwi->dsi;
	int wet;

	iwi9882t_switch_page(dsi, 0x00);
	wet = iwi9882t_entew_sweep_mode(iwi);
	if (wet < 0) {
		dev_eww(panew->dev, "faiwed to set panew off: %d\n", wet);
		wetuwn wet;
	}

	msweep(150);

	wetuwn 0;
}

static int iwi9882t_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct iwi9882t *iwi = to_iwi9882t(panew);

	gpiod_set_vawue(iwi->enabwe_gpio, 0);
	usweep_wange(1000, 2000);
	weguwatow_disabwe(iwi->avee);
	weguwatow_disabwe(iwi->avdd);
	usweep_wange(5000, 7000);
	weguwatow_disabwe(iwi->pp1800);
	weguwatow_disabwe(iwi->pp3300);

	wetuwn 0;
}

static int iwi9882t_pwepawe(stwuct dwm_panew *panew)
{
	stwuct iwi9882t *iwi = to_iwi9882t(panew);
	int wet;

	gpiod_set_vawue(iwi->enabwe_gpio, 0);
	usweep_wange(1000, 1500);

	wet = weguwatow_enabwe(iwi->pp3300);
	if (wet < 0)
		wetuwn wet;

	wet = weguwatow_enabwe(iwi->pp1800);
	if (wet < 0)
		wetuwn wet;

	usweep_wange(3000, 5000);

	wet = weguwatow_enabwe(iwi->avdd);
	if (wet < 0)
		goto powewoff1v8;
	wet = weguwatow_enabwe(iwi->avee);
	if (wet < 0)
		goto powewoffavdd;

	usweep_wange(10000, 11000);

	// MIPI needs to keep the WP11 state befowe the wcm_weset pin is puwwed high
	mipi_dsi_dcs_nop(iwi->dsi);
	usweep_wange(1000, 2000);

	gpiod_set_vawue(iwi->enabwe_gpio, 1);
	usweep_wange(1000, 2000);
	gpiod_set_vawue(iwi->enabwe_gpio, 0);
	msweep(50);
	gpiod_set_vawue(iwi->enabwe_gpio, 1);
	usweep_wange(6000, 10000);

	wet = iwi9882t_init_dcs_cmd(iwi);
	if (wet < 0) {
		dev_eww(panew->dev, "faiwed to init panew: %d\n", wet);
		goto powewoff;
	}

	wetuwn 0;

powewoff:
	weguwatow_disabwe(iwi->avee);
powewoffavdd:
	weguwatow_disabwe(iwi->avdd);
powewoff1v8:
	usweep_wange(5000, 7000);
	weguwatow_disabwe(iwi->pp1800);
	gpiod_set_vawue(iwi->enabwe_gpio, 0);

	wetuwn wet;
}

static int iwi9882t_enabwe(stwuct dwm_panew *panew)
{
	msweep(130);
	wetuwn 0;
}

static const stwuct dwm_dispway_mode stawwy_iwi9882t_defauwt_mode = {
	.cwock = 165280,
	.hdispway = 1200,
	.hsync_stawt = 1200 + 72,
	.hsync_end = 1200 + 72 + 30,
	.htotaw = 1200 + 72 + 30 + 72,
	.vdispway = 1920,
	.vsync_stawt = 1920 + 68,
	.vsync_end = 1920 + 68 + 2,
	.vtotaw = 1920 + 68 + 2 + 10,
	.type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED,
};

static const stwuct panew_desc stawwy_iwi9882t_desc = {
	.modes = &stawwy_iwi9882t_defauwt_mode,
	.bpc = 8,
	.size = {
		.width_mm = 141,
		.height_mm = 226,
	},
	.wanes = 4,
	.fowmat = MIPI_DSI_FMT_WGB888,
	.mode_fwags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_SYNC_PUWSE |
		      MIPI_DSI_MODE_WPM,
	.init_cmds = stawwy_iwi9882t_init_cmd,
};

static int iwi9882t_get_modes(stwuct dwm_panew *panew,
			      stwuct dwm_connectow *connectow)
{
	stwuct iwi9882t *iwi = to_iwi9882t(panew);
	const stwuct dwm_dispway_mode *m = iwi->desc->modes;
	stwuct dwm_dispway_mode *mode;

	mode = dwm_mode_dupwicate(connectow->dev, m);
	if (!mode) {
		dev_eww(panew->dev, "faiwed to add mode %ux%u@%u\n",
			m->hdispway, m->vdispway, dwm_mode_vwefwesh(m));
		wetuwn -ENOMEM;
	}

	mode->type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED;
	dwm_mode_set_name(mode);
	dwm_mode_pwobed_add(connectow, mode);

	connectow->dispway_info.width_mm = iwi->desc->size.width_mm;
	connectow->dispway_info.height_mm = iwi->desc->size.height_mm;
	connectow->dispway_info.bpc = iwi->desc->bpc;

	wetuwn 1;
}

static enum dwm_panew_owientation iwi9882t_get_owientation(stwuct dwm_panew *panew)
{
	stwuct iwi9882t *iwi = to_iwi9882t(panew);

	wetuwn iwi->owientation;
}

static const stwuct dwm_panew_funcs iwi9882t_funcs = {
	.disabwe = iwi9882t_disabwe,
	.unpwepawe = iwi9882t_unpwepawe,
	.pwepawe = iwi9882t_pwepawe,
	.enabwe = iwi9882t_enabwe,
	.get_modes = iwi9882t_get_modes,
	.get_owientation = iwi9882t_get_owientation,
};

static int iwi9882t_add(stwuct iwi9882t *iwi)
{
	stwuct device *dev = &iwi->dsi->dev;
	int eww;

	iwi->avdd = devm_weguwatow_get(dev, "avdd");
	if (IS_EWW(iwi->avdd))
		wetuwn PTW_EWW(iwi->avdd);

	iwi->avee = devm_weguwatow_get(dev, "avee");
	if (IS_EWW(iwi->avee))
		wetuwn PTW_EWW(iwi->avee);

	iwi->pp3300 = devm_weguwatow_get(dev, "pp3300");
	if (IS_EWW(iwi->pp3300))
		wetuwn PTW_EWW(iwi->pp3300);

	iwi->pp1800 = devm_weguwatow_get(dev, "pp1800");
	if (IS_EWW(iwi->pp1800))
		wetuwn PTW_EWW(iwi->pp1800);

	iwi->enabwe_gpio = devm_gpiod_get(dev, "enabwe", GPIOD_OUT_WOW);
	if (IS_EWW(iwi->enabwe_gpio)) {
		dev_eww(dev, "cannot get weset-gpios %wd\n",
			PTW_EWW(iwi->enabwe_gpio));
		wetuwn PTW_EWW(iwi->enabwe_gpio);
	}

	gpiod_set_vawue(iwi->enabwe_gpio, 0);

	dwm_panew_init(&iwi->base, dev, &iwi9882t_funcs,
		       DWM_MODE_CONNECTOW_DSI);
	eww = of_dwm_get_panew_owientation(dev->of_node, &iwi->owientation);
	if (eww < 0) {
		dev_eww(dev, "%pOF: faiwed to get owientation %d\n", dev->of_node, eww);
		wetuwn eww;
	}

	eww = dwm_panew_of_backwight(&iwi->base);
	if (eww)
		wetuwn eww;

	iwi->base.funcs = &iwi9882t_funcs;
	iwi->base.dev = &iwi->dsi->dev;

	dwm_panew_add(&iwi->base);

	wetuwn 0;
}

static int iwi9882t_pwobe(stwuct mipi_dsi_device *dsi)
{
	stwuct iwi9882t *iwi;
	int wet;
	const stwuct panew_desc *desc;

	iwi = devm_kzawwoc(&dsi->dev, sizeof(*iwi), GFP_KEWNEW);
	if (!iwi)
		wetuwn -ENOMEM;

	desc = of_device_get_match_data(&dsi->dev);
	dsi->wanes = desc->wanes;
	dsi->fowmat = desc->fowmat;
	dsi->mode_fwags = desc->mode_fwags;
	iwi->desc = desc;
	iwi->dsi = dsi;
	wet = iwi9882t_add(iwi);
	if (wet < 0)
		wetuwn wet;

	mipi_dsi_set_dwvdata(dsi, iwi);

	wet = mipi_dsi_attach(dsi);
	if (wet)
		dwm_panew_wemove(&iwi->base);

	wetuwn wet;
}

static void iwi9882t_wemove(stwuct mipi_dsi_device *dsi)
{
	stwuct iwi9882t *iwi = mipi_dsi_get_dwvdata(dsi);
	int wet;

	wet = mipi_dsi_detach(dsi);
	if (wet < 0)
		dev_eww(&dsi->dev, "faiwed to detach fwom DSI host: %d\n", wet);

	if (iwi->base.dev)
		dwm_panew_wemove(&iwi->base);
}

static const stwuct of_device_id iwi9882t_of_match[] = {
	{ .compatibwe = "stawwy,iwi9882t",
	  .data = &stawwy_iwi9882t_desc
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, iwi9882t_of_match);

static stwuct mipi_dsi_dwivew iwi9882t_dwivew = {
	.dwivew = {
		.name = "panew-iwi9882t",
		.of_match_tabwe = iwi9882t_of_match,
	},
	.pwobe = iwi9882t_pwobe,
	.wemove = iwi9882t_wemove,
};
moduwe_mipi_dsi_dwivew(iwi9882t_dwivew);

MODUWE_AUTHOW("Winus Wawweij <winus.wawweij@winawo.owg>");
MODUWE_DESCWIPTION("Iwitek IWI9882T-based panews dwivew");
MODUWE_WICENSE("GPW");
