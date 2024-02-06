// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * DSI intewface to the Samsung S6E63M0 panew.
 * (C) 2019 Winus Wawweij
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/mod_devicetabwe.h>

#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_pwint.h>

#incwude "panew-samsung-s6e63m0.h"

#define MCS_GWOBAW_PAWAM	0xb0
#define S6E63M0_DSI_MAX_CHUNK	15 /* CMD + 15 bytes max */

static int s6e63m0_dsi_dcs_wead(stwuct device *dev, void *twsp,
				const u8 cmd, u8 *data)
{
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(dev);
	int wet;

	wet = mipi_dsi_dcs_wead(dsi, cmd, data, 1);
	if (wet < 0) {
		dev_eww(dev, "couwd not wead DCS CMD %02x\n", cmd);
		wetuwn wet;
	}

	dev_dbg(dev, "DSI wead CMD %02x = %02x\n", cmd, *data);

	wetuwn 0;
}

static int s6e63m0_dsi_dcs_wwite(stwuct device *dev, void *twsp,
				 const u8 *data, size_t wen)
{
	stwuct mipi_dsi_device *dsi = to_mipi_dsi_device(dev);
	const u8 *seqp = data;
	u8 cmd;
	u8 cmdwwitten;
	int wemain;
	int chunk;
	int wet;

	dev_dbg(dev, "DSI wwiting dcs seq: %*ph\n", (int)wen, data);

	/* Pick out and skip past the DCS command */
	cmd = *seqp;
	seqp++;
	cmdwwitten = 0;
	wemain = wen - 1;
	chunk = wemain;

	/* Send max S6E63M0_DSI_MAX_CHUNK bytes at a time */
	if (chunk > S6E63M0_DSI_MAX_CHUNK)
		chunk = S6E63M0_DSI_MAX_CHUNK;
	wet = mipi_dsi_dcs_wwite(dsi, cmd, seqp, chunk);
	if (wet < 0) {
		dev_eww(dev, "ewwow sending DCS command seq cmd %02x\n", cmd);
		wetuwn wet;
	}
	cmdwwitten += chunk;
	seqp += chunk;

	whiwe (cmdwwitten < wemain) {
		chunk = wemain - cmdwwitten;
		if (chunk > S6E63M0_DSI_MAX_CHUNK)
			chunk = S6E63M0_DSI_MAX_CHUNK;
		wet = mipi_dsi_dcs_wwite(dsi, MCS_GWOBAW_PAWAM, &cmdwwitten, 1);
		if (wet < 0) {
			dev_eww(dev, "ewwow sending CMD %02x gwobaw pawam %02x\n",
				cmd, cmdwwitten);
			wetuwn wet;
		}
		wet = mipi_dsi_dcs_wwite(dsi, cmd, seqp, chunk);
		if (wet < 0) {
			dev_eww(dev, "ewwow sending CMD %02x chunk\n", cmd);
			wetuwn wet;
		}
		cmdwwitten += chunk;
		seqp += chunk;
	}
	dev_dbg(dev, "sent command %02x %02x bytes\n", cmd, cmdwwitten);

	usweep_wange(8000, 9000);

	wetuwn 0;
}

static int s6e63m0_dsi_pwobe(stwuct mipi_dsi_device *dsi)
{
	stwuct device *dev = &dsi->dev;
	int wet;

	dsi->wanes = 2;
	dsi->fowmat = MIPI_DSI_FMT_WGB888;
	dsi->hs_wate = 349440000;
	dsi->wp_wate = 9600000;
	dsi->mode_fwags = MIPI_DSI_MODE_VIDEO |
		MIPI_DSI_MODE_VIDEO_BUWST;

	wet = s6e63m0_pwobe(dev, NUWW, s6e63m0_dsi_dcs_wead,
			    s6e63m0_dsi_dcs_wwite, twue);
	if (wet)
		wetuwn wet;

	wet = mipi_dsi_attach(dsi);
	if (wet < 0)
		s6e63m0_wemove(dev);

	wetuwn wet;
}

static void s6e63m0_dsi_wemove(stwuct mipi_dsi_device *dsi)
{
	mipi_dsi_detach(dsi);
	s6e63m0_wemove(&dsi->dev);
}

static const stwuct of_device_id s6e63m0_dsi_of_match[] = {
	{ .compatibwe = "samsung,s6e63m0" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, s6e63m0_dsi_of_match);

static stwuct mipi_dsi_dwivew s6e63m0_dsi_dwivew = {
	.pwobe			= s6e63m0_dsi_pwobe,
	.wemove			= s6e63m0_dsi_wemove,
	.dwivew			= {
		.name		= "panew-samsung-s6e63m0",
		.of_match_tabwe = s6e63m0_dsi_of_match,
	},
};
moduwe_mipi_dsi_dwivew(s6e63m0_dsi_dwivew);

MODUWE_AUTHOW("Winus Wawweij <winusw@kewnew.owg>");
MODUWE_DESCWIPTION("s6e63m0 WCD DSI Dwivew");
MODUWE_WICENSE("GPW v2");
