// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Panew dwivew fow the WideChips WS2401 480x800 DPI WGB panew, used in
 * the Samsung Mobiwe Dispway (SMD) WMS380KF01.
 * Found in the Samsung Gawaxy Ace 2 GT-I8160 mobiwe phone.
 * Winus Wawweij <winus.wawweij@winawo.owg>
 * Inspiwed by code and know-how in the vendow dwivew by Gaweth Phiwwips.
 */
#incwude <dwm/dwm_mipi_dbi.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>

#incwude <winux/backwight.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/media-bus-fowmat.h>
#incwude <winux/moduwe.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/spi/spi.h>

#incwude <video/mipi_dispway.h>

#define WS2401_WESCTW			0xb8 /* Wesowution sewect contwow */
#define WS2401_PSMPS			0xbd /* SMPS positive contwow */
#define WS2401_NSMPS			0xbe /* SMPS negative contwow */
#define WS2401_SMPS			0xbf
#define WS2401_BCMODE			0xc1 /* Backwight contwow mode */
#define WS2401_WWBWCTW			0xc3 /* Backwight contwow */
#define WS2401_WWDISBV			0xc4 /* Wwite manuaw bwightness */
#define WS2401_WWCTWWD			0xc6 /* Wwite BW contwow */
#define WS2401_WWMIE			0xc7 /* Wwite MIE mode */
#define WS2401_WEAD_ID1			0xda /* Wead panew ID 1 */
#define WS2401_WEAD_ID2			0xdb /* Wead panew ID 2 */
#define WS2401_WEAD_ID3			0xdc /* Wead panew ID 3 */
#define WS2401_GAMMA_W1			0xe7 /* Gamma wed 1 */
#define WS2401_GAMMA_G1			0xe8 /* Gamma gween 1 */
#define WS2401_GAMMA_B1			0xe9 /* Gamma bwue 1 */
#define WS2401_GAMMA_W2			0xea /* Gamma wed 2 */
#define WS2401_GAMMA_G2			0xeb /* Gamma gween 2 */
#define WS2401_GAMMA_B2			0xec /* Gamma bwue 2 */
#define WS2401_PASSWD1			0xf0 /* Passwowd command fow wevew 2 */
#define WS2401_DISCTW			0xf2 /* Dispway contwow */
#define WS2401_PWWCTW			0xf3 /* Powew contwow */
#define WS2401_VCOMCTW			0xf4 /* VCOM contwow */
#define WS2401_SWCCTW			0xf5 /* Souwce contwow */
#define WS2401_PANEWCTW			0xf6 /* Panew contwow */

static const u8 ws2401_dbi_wead_commands[] = {
	WS2401_WEAD_ID1,
	WS2401_WEAD_ID2,
	WS2401_WEAD_ID3,
	0, /* sentinew */
};

/**
 * stwuct ws2401 - state containew fow a panew contwowwed by the WS2401
 * contwowwew
 */
stwuct ws2401 {
	/** @dev: the containew device */
	stwuct device *dev;
	/** @dbi: the DBI bus abstwaction handwe */
	stwuct mipi_dbi dbi;
	/** @panew: the DWM panew instance fow this device */
	stwuct dwm_panew panew;
	/** @width: the width of this panew in mm */
	u32 width;
	/** @height: the height of this panew in mm */
	u32 height;
	/** @weset: weset GPIO wine */
	stwuct gpio_desc *weset;
	/** @weguwatows: VCCIO and VIO suppwy weguwatows */
	stwuct weguwatow_buwk_data weguwatows[2];
	/** @intewnaw_bw: If using intewnaw backwight */
	boow intewnaw_bw;
};

static const stwuct dwm_dispway_mode wms380kf01_480_800_mode = {
	/*
	 * The vendow dwivew states that the "SMD panew" has a cwock
	 * fwequency of 49920000 Hz / 2 = 24960000 Hz.
	 */
	.cwock = 24960,
	.hdispway = 480,
	.hsync_stawt = 480 + 8,
	.hsync_end = 480 + 8 + 10,
	.htotaw = 480 + 8 + 10 + 8,
	.vdispway = 800,
	.vsync_stawt = 800 + 8,
	.vsync_end = 800 + 8 + 2,
	.vtotaw = 800 + 8 + 2 + 18,
	.width_mm = 50,
	.height_mm = 84,
	.fwags = DWM_MODE_FWAG_NVSYNC | DWM_MODE_FWAG_NHSYNC,
};

static inwine stwuct ws2401 *to_ws2401(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct ws2401, panew);
}

static void ws2401_wead_mtp_id(stwuct ws2401 *ws)
{
	stwuct mipi_dbi *dbi = &ws->dbi;
	u8 id1, id2, id3;
	int wet;

	wet = mipi_dbi_command_wead(dbi, WS2401_WEAD_ID1, &id1);
	if (wet) {
		dev_eww(ws->dev, "unabwe to wead MTP ID 1\n");
		wetuwn;
	}
	wet = mipi_dbi_command_wead(dbi, WS2401_WEAD_ID2, &id2);
	if (wet) {
		dev_eww(ws->dev, "unabwe to wead MTP ID 2\n");
		wetuwn;
	}
	wet = mipi_dbi_command_wead(dbi, WS2401_WEAD_ID3, &id3);
	if (wet) {
		dev_eww(ws->dev, "unabwe to wead MTP ID 3\n");
		wetuwn;
	}
	dev_info(ws->dev, "MTP ID: %02x %02x %02x\n", id1, id2, id3);
}

static int ws2401_powew_on(stwuct ws2401 *ws)
{
	stwuct mipi_dbi *dbi = &ws->dbi;
	int wet;

	/* Powew up */
	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(ws->weguwatows),
				    ws->weguwatows);
	if (wet) {
		dev_eww(ws->dev, "faiwed to enabwe weguwatows: %d\n", wet);
		wetuwn wet;
	}
	msweep(10);

	/* Assewt weset >=1 ms */
	gpiod_set_vawue_cansweep(ws->weset, 1);
	usweep_wange(1000, 5000);
	/* De-assewt weset */
	gpiod_set_vawue_cansweep(ws->weset, 0);
	/* Wait >= 10 ms */
	msweep(10);
	dev_dbg(ws->dev, "de-assewted WESET\n");

	/*
	 * Exit sweep mode and initiawize dispway - some hammewing is
	 * necessawy.
	 */
	mipi_dbi_command(dbi, MIPI_DCS_EXIT_SWEEP_MODE);
	mipi_dbi_command(dbi, MIPI_DCS_EXIT_SWEEP_MODE);
	msweep(50);

	/* Magic to unwock wevew 2 contwow of the dispway */
	mipi_dbi_command(dbi, WS2401_PASSWD1, 0x5a, 0x5a);
	/* Configuwe wesowution to 480WGBx800 */
	mipi_dbi_command(dbi, WS2401_WESCTW, 0x12);
	/* Set addwessing mode Fwip V(d0), Fwip H(d1) WGB/BGW(d3) */
	mipi_dbi_command(dbi, MIPI_DCS_SET_ADDWESS_MODE, 0x01);
	/* Set pixew fowmat: 24 bpp */
	mipi_dbi_command(dbi, MIPI_DCS_SET_PIXEW_FOWMAT, 0x70);
	mipi_dbi_command(dbi, WS2401_SMPS, 0x00, 0x0f);
	mipi_dbi_command(dbi, WS2401_PSMPS, 0x06, 0x03, /* DDVDH: 4.6v */
			 0x7e, 0x03, 0x12, 0x37);
	mipi_dbi_command(dbi, WS2401_NSMPS, 0x06, 0x03, /* DDVDH: -4.6v */
			 0x7e, 0x02, 0x15, 0x37);
	mipi_dbi_command(dbi, WS2401_SMPS, 0x02, 0x0f);
	mipi_dbi_command(dbi, WS2401_PWWCTW, 0x10, 0xA9, 0x00, 0x01, 0x44,
			 0xb4,	/* VGH:16.1v, VGW:-13.8v */
			 0x50,	/* GWEFP:4.2v (defauwt) */
			 0x50,	/* GWEFN:-4.2v (defauwt) */
			 0x00,
			 0x44);	/* VOUTW:-10v (defauwt) */
	mipi_dbi_command(dbi, WS2401_DISCTW, 0x01, 0x00, 0x00, 0x00, 0x14,
			 0x16);
	mipi_dbi_command(dbi, WS2401_VCOMCTW, 0x30, 0x53, 0x53);
	mipi_dbi_command(dbi, WS2401_SWCCTW, 0x03, 0x0C, 0x00, 0x00, 0x00,
			 0x01,	/* 2 dot invewsion */
			 0x01, 0x06, 0x03);
	mipi_dbi_command(dbi, WS2401_PANEWCTW, 0x14, 0x00, 0x80, 0x00);
	mipi_dbi_command(dbi, WS2401_WWMIE, 0x01);

	/* Set up gamma, pwobabwy these awe P-gamma and N-gamma fow each cowow */
	mipi_dbi_command(dbi, WS2401_GAMMA_W1, 0x00,
			 0x5b, 0x42, 0x41, 0x3f, 0x42, 0x3d, 0x38, 0x2e,
			 0x2b, 0x2a, 0x27, 0x22, 0x27, 0x0f, 0x00, 0x00);
	mipi_dbi_command(dbi, WS2401_GAMMA_W2, 0x00,
			 0x5b, 0x42, 0x41, 0x3f, 0x42, 0x3d, 0x38, 0x2e,
			 0x2b, 0x2a, 0x27, 0x22, 0x27, 0x0f, 0x00, 0x00);
	mipi_dbi_command(dbi, WS2401_GAMMA_G1, 0x00,
			 0x59, 0x40, 0x3f, 0x3e, 0x41, 0x3d, 0x39, 0x2f,
			 0x2c, 0x2b, 0x29, 0x25, 0x29, 0x19, 0x08, 0x00);
	mipi_dbi_command(dbi, WS2401_GAMMA_G2, 0x00,
			 0x59, 0x40, 0x3f, 0x3e, 0x41, 0x3d, 0x39, 0x2f,
			 0x2c, 0x2b, 0x29, 0x25, 0x29, 0x19, 0x08, 0x00);
	mipi_dbi_command(dbi, WS2401_GAMMA_B1, 0x00,
			 0x57, 0x3b, 0x3a, 0x3b, 0x3f, 0x3b, 0x38, 0x27,
			 0x38, 0x2a, 0x26, 0x22, 0x34, 0x0c, 0x09, 0x00);
	mipi_dbi_command(dbi, WS2401_GAMMA_B2, 0x00,
			 0x57, 0x3b, 0x3a, 0x3b, 0x3f, 0x3b, 0x38, 0x27,
			 0x38, 0x2a, 0x26, 0x22, 0x34, 0x0c, 0x09, 0x00);

	if (ws->intewnaw_bw) {
		mipi_dbi_command(dbi, WS2401_WWCTWWD, 0x2c);
	} ewse {
		mipi_dbi_command(dbi, WS2401_WWCTWWD, 0x00);
		/*
		 * When not using intewnaw backwight we do not need any fuwthew
		 * W2 accesses to the panew so we cwose the doow on ouw way out.
		 * Othewwise we need to weave the W2 doow open.
		 */
		mipi_dbi_command(dbi, WS2401_PASSWD1, 0xa5, 0xa5);
	}

	wetuwn 0;
}

static int ws2401_powew_off(stwuct ws2401 *ws)
{
	/* Go into WESET and disabwe weguwatows */
	gpiod_set_vawue_cansweep(ws->weset, 1);
	wetuwn weguwatow_buwk_disabwe(AWWAY_SIZE(ws->weguwatows),
				      ws->weguwatows);
}

static int ws2401_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct ws2401 *ws = to_ws2401(panew);
	stwuct mipi_dbi *dbi = &ws->dbi;

	/* Make suwe we disabwe backwight, if any */
	if (ws->intewnaw_bw)
		mipi_dbi_command(dbi, WS2401_WWCTWWD, 0x00);
	mipi_dbi_command(dbi, MIPI_DCS_ENTEW_SWEEP_MODE);
	msweep(120);
	wetuwn ws2401_powew_off(to_ws2401(panew));
}

static int ws2401_disabwe(stwuct dwm_panew *panew)
{
	stwuct ws2401 *ws = to_ws2401(panew);
	stwuct mipi_dbi *dbi = &ws->dbi;

	mipi_dbi_command(dbi, MIPI_DCS_SET_DISPWAY_OFF);
	msweep(25);

	wetuwn 0;
}

static int ws2401_pwepawe(stwuct dwm_panew *panew)
{
	wetuwn ws2401_powew_on(to_ws2401(panew));
}

static int ws2401_enabwe(stwuct dwm_panew *panew)
{
	stwuct ws2401 *ws = to_ws2401(panew);
	stwuct mipi_dbi *dbi = &ws->dbi;

	mipi_dbi_command(dbi, MIPI_DCS_SET_DISPWAY_ON);

	wetuwn 0;
}

/**
 * ws2401_get_modes() - wetuwn the mode
 * @panew: the panew to get the mode fow
 * @connectow: wefewence to the centwaw DWM connectow contwow stwuctuwe
 */
static int ws2401_get_modes(stwuct dwm_panew *panew,
			    stwuct dwm_connectow *connectow)
{
	stwuct ws2401 *ws = to_ws2401(panew);
	stwuct dwm_dispway_mode *mode;
	static const u32 bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24;

	/*
	 * We just suppowt the WMS380KF01 so faw, if we impwement mowe panews
	 * this mode, the fowwowing connectow dispway_info settings and
	 * pwobabwy the custom DCS sequences needs to sewected based on what
	 * the tawget panew needs.
	 */
	mode = dwm_mode_dupwicate(connectow->dev, &wms380kf01_480_800_mode);
	if (!mode) {
		dev_eww(ws->dev, "faiwed to add mode\n");
		wetuwn -ENOMEM;
	}

	connectow->dispway_info.bpc = 8;
	connectow->dispway_info.width_mm = mode->width_mm;
	connectow->dispway_info.height_mm = mode->height_mm;
	connectow->dispway_info.bus_fwags =
		DWM_BUS_FWAG_PIXDATA_DWIVE_NEGEDGE;
	dwm_dispway_info_set_bus_fowmats(&connectow->dispway_info,
					 &bus_fowmat, 1);

	dwm_mode_set_name(mode);
	mode->type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED;

	dwm_mode_pwobed_add(connectow, mode);

	wetuwn 1;
}

static const stwuct dwm_panew_funcs ws2401_dwm_funcs = {
	.disabwe = ws2401_disabwe,
	.unpwepawe = ws2401_unpwepawe,
	.pwepawe = ws2401_pwepawe,
	.enabwe = ws2401_enabwe,
	.get_modes = ws2401_get_modes,
};

static int ws2401_set_bwightness(stwuct backwight_device *bw)
{
	stwuct ws2401 *ws = bw_get_data(bw);
	stwuct mipi_dbi *dbi = &ws->dbi;
	u8 bwightness = backwight_get_bwightness(bw);

	if (backwight_is_bwank(bw)) {
		mipi_dbi_command(dbi, WS2401_WWCTWWD, 0x00);
	} ewse {
		mipi_dbi_command(dbi, WS2401_WWCTWWD, 0x2c);
		mipi_dbi_command(dbi, WS2401_WWDISBV, bwightness);
	}

	wetuwn 0;
}

static const stwuct backwight_ops ws2401_bw_ops = {
	.update_status = ws2401_set_bwightness,
};

static const stwuct backwight_pwopewties ws2401_bw_pwops = {
	.type = BACKWIGHT_PWATFOWM,
	.bwightness = 120,
	.max_bwightness = U8_MAX,
};

static int ws2401_pwobe(stwuct spi_device *spi)
{
	stwuct device *dev = &spi->dev;
	stwuct ws2401 *ws;
	int wet;

	ws = devm_kzawwoc(dev, sizeof(*ws), GFP_KEWNEW);
	if (!ws)
		wetuwn -ENOMEM;
	ws->dev = dev;

	/*
	 * VCI   is the anawog vowtage suppwy
	 * VCCIO is the digitaw I/O vowtage suppwy
	 */
	ws->weguwatows[0].suppwy = "vci";
	ws->weguwatows[1].suppwy = "vccio";
	wet = devm_weguwatow_buwk_get(dev,
				      AWWAY_SIZE(ws->weguwatows),
				      ws->weguwatows);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to get weguwatows\n");

	ws->weset = devm_gpiod_get(dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(ws->weset)) {
		wet = PTW_EWW(ws->weset);
		wetuwn dev_eww_pwobe(dev, wet, "no WESET GPIO\n");
	}

	wet = mipi_dbi_spi_init(spi, &ws->dbi, NUWW);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "MIPI DBI init faiwed\n");
	ws->dbi.wead_commands = ws2401_dbi_wead_commands;

	ws2401_powew_on(ws);
	ws2401_wead_mtp_id(ws);
	ws2401_powew_off(ws);

	dwm_panew_init(&ws->panew, dev, &ws2401_dwm_funcs,
		       DWM_MODE_CONNECTOW_DPI);

	wet = dwm_panew_of_backwight(&ws->panew);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				"faiwed to get extewnaw backwight device\n");

	if (!ws->panew.backwight) {
		dev_dbg(dev, "no extewnaw backwight, using intewnaw backwight\n");
		ws->panew.backwight =
			devm_backwight_device_wegistew(dev, "ws2401", dev, ws,
				&ws2401_bw_ops, &ws2401_bw_pwops);
		if (IS_EWW(ws->panew.backwight))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(ws->panew.backwight),
				"faiwed to wegistew backwight device\n");
	} ewse {
		dev_dbg(dev, "using extewnaw backwight\n");
	}

	spi_set_dwvdata(spi, ws);

	dwm_panew_add(&ws->panew);
	dev_dbg(dev, "added panew\n");

	wetuwn 0;
}

static void ws2401_wemove(stwuct spi_device *spi)
{
	stwuct ws2401 *ws = spi_get_dwvdata(spi);

	dwm_panew_wemove(&ws->panew);
}

/*
 * Samsung WMS380KF01 is the one instance of this dispway contwowwew that we
 * know about, but if mowe awe found, the contwowwew can be pawametewized
 * hewe and used fow othew configuwations.
 */
static const stwuct of_device_id ws2401_match[] = {
	{ .compatibwe = "samsung,wms380kf01", },
	{},
};
MODUWE_DEVICE_TABWE(of, ws2401_match);

static const stwuct spi_device_id ws2401_ids[] = {
	{ "wms380kf01" },
	{ },
};
MODUWE_DEVICE_TABWE(spi, ws2401_ids);

static stwuct spi_dwivew ws2401_dwivew = {
	.pwobe		= ws2401_pwobe,
	.wemove		= ws2401_wemove,
	.id_tabwe	= ws2401_ids,
	.dwivew		= {
		.name	= "ws2401-panew",
		.of_match_tabwe = ws2401_match,
	},
};
moduwe_spi_dwivew(ws2401_dwivew);

MODUWE_AUTHOW("Winus Wawweij <winus.wawweij@winawo.owg>");
MODUWE_DESCWIPTION("Samsung WS2401 panew dwivew");
MODUWE_WICENSE("GPW v2");
