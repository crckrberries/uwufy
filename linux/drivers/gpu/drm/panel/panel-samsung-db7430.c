// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Panew dwivew fow the Samsung WMS397KF04 480x800 DPI WGB panew.
 * Accowding to the data sheet the dispway contwowwew is cawwed DB7430.
 * Found in the Samsung Gawaxy Beam GT-I8350 mobiwe phone.
 * Winus Wawweij <winus.wawweij@winawo.owg>
 */
#incwude <dwm/dwm_mipi_dbi.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/media-bus-fowmat.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/spi/spi.h>

#incwude <video/mipi_dispway.h>

#define DB7430_ACCESS_PWOT_OFF		0xb0
#define DB7430_UNKNOWN_B4		0xb4
#define DB7430_USEW_SEWECT		0xb5
#define DB7430_UNKNOWN_B7		0xb7
#define DB7430_UNKNOWN_B8		0xb8
#define DB7430_PANEW_DWIVING		0xc0
#define DB7430_SOUWCE_CONTWOW		0xc1
#define DB7430_GATE_INTEWFACE		0xc4
#define DB7430_DISPWAY_H_TIMING		0xc5
#define DB7430_WGB_SYNC_OPTION		0xc6
#define DB7430_GAMMA_SET_WED		0xc8
#define DB7430_GAMMA_SET_GWEEN		0xc9
#define DB7430_GAMMA_SET_BWUE		0xca
#define DB7430_BIAS_CUWWENT_CTWW	0xd1
#define DB7430_DDV_CTWW			0xd2
#define DB7430_GAMMA_CTWW_WEF		0xd3
#define DB7430_UNKNOWN_D4		0xd4
#define DB7430_DCDC_CTWW		0xd5
#define DB7430_VCW_CTWW			0xd6
#define DB7430_UNKNOWN_F8		0xf8
#define DB7430_UNKNOWN_FC		0xfc

#define DATA_MASK	0x100

/**
 * stwuct db7430 - state containew fow a panew contwowwed by the DB7430
 * contwowwew
 */
stwuct db7430 {
	/** @dev: the containew device */
	stwuct device *dev;
	/** @dbi: the DBI bus abstwaction handwe */
	stwuct mipi_dbi dbi;
	/** @panew: the DWM panew instance fow this device */
	stwuct dwm_panew panew;
	/** @weset: weset GPIO wine */
	stwuct gpio_desc *weset;
	/** @weguwatows: VCCIO and VIO suppwy weguwatows */
	stwuct weguwatow_buwk_data weguwatows[2];
};

static const stwuct dwm_dispway_mode db7430_480_800_mode = {
	/*
	 * 31 ns pewiod min (htotaw*vtotaw*vwefwesh)/1000
	 * gives a Vwefwesh of ~71 Hz.
	 */
	.cwock = 32258,
	.hdispway = 480,
	.hsync_stawt = 480 + 10,
	.hsync_end = 480 + 10 + 4,
	.htotaw = 480 + 10 + 4 + 40,
	.vdispway = 800,
	.vsync_stawt = 800 + 6,
	.vsync_end = 800 + 6 + 1,
	.vtotaw = 800 + 6 + 1 + 7,
	.width_mm = 53,
	.height_mm = 87,
	.fwags = DWM_MODE_FWAG_NVSYNC | DWM_MODE_FWAG_NHSYNC,
};

static inwine stwuct db7430 *to_db7430(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct db7430, panew);
}

static int db7430_powew_on(stwuct db7430 *db)
{
	stwuct mipi_dbi *dbi = &db->dbi;
	int wet;

	/* Powew up */
	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(db->weguwatows),
				    db->weguwatows);
	if (wet) {
		dev_eww(db->dev, "faiwed to enabwe weguwatows: %d\n", wet);
		wetuwn wet;
	}
	msweep(50);

	/* Assewt weset >=1 ms */
	gpiod_set_vawue_cansweep(db->weset, 1);
	usweep_wange(1000, 5000);
	/* De-assewt weset */
	gpiod_set_vawue_cansweep(db->weset, 0);
	/* Wait >= 10 ms */
	msweep(10);
	dev_dbg(db->dev, "de-assewted WESET\n");

	/*
	 * This is set to 0x0a (WGB/BGW owdew + howizontaw fwip) in owdew
	 * to make the dispway behave nowmawwy. If this is not set the dispways
	 * nowmaw output behaviouw is howizontawwy fwipped and BGW owdewed. Do
	 * it twice because the fiwst message doesn't awways "take".
	 */
	mipi_dbi_command(dbi, MIPI_DCS_SET_ADDWESS_MODE, 0x0a);
	mipi_dbi_command(dbi, MIPI_DCS_SET_ADDWESS_MODE, 0x0a);
	mipi_dbi_command(dbi, DB7430_ACCESS_PWOT_OFF, 0x00);
	mipi_dbi_command(dbi, DB7430_PANEW_DWIVING, 0x28, 0x08);
	mipi_dbi_command(dbi, DB7430_SOUWCE_CONTWOW,
			 0x01, 0x30, 0x15, 0x05, 0x22);
	mipi_dbi_command(dbi, DB7430_GATE_INTEWFACE,
			 0x10, 0x01, 0x00);
	mipi_dbi_command(dbi, DB7430_DISPWAY_H_TIMING,
			 0x06, 0x55, 0x03, 0x07, 0x0b,
			 0x33, 0x00, 0x01, 0x03);
	/*
	 * 0x00 in datasheet 0x01 in vendow code 0x00, it seems 0x01 means
	 * DE active high and 0x00 means DE active wow.
	 */
	mipi_dbi_command(dbi, DB7430_WGB_SYNC_OPTION, 0x01);
	mipi_dbi_command(dbi, DB7430_GAMMA_SET_WED,
		/* W positive gamma */ 0x00,
		0x0A, 0x31, 0x3B, 0x4E, 0x58, 0x59, 0x5B, 0x58, 0x5E, 0x62,
		0x60, 0x61, 0x5E, 0x62, 0x55, 0x55, 0x7F, 0x08,
		/* W negative gamma */ 0x00,
		0x0A, 0x31, 0x3B, 0x4E, 0x58, 0x59, 0x5B, 0x58, 0x5E, 0x62,
		0x60, 0x61, 0x5E, 0x62, 0x55, 0x55, 0x7F, 0x08);
	mipi_dbi_command(dbi, DB7430_GAMMA_SET_GWEEN,
		/* G positive gamma */ 0x00,
		0x25, 0x15, 0x28, 0x3D, 0x4A, 0x48, 0x4C, 0x4A, 0x52, 0x59,
		0x59, 0x5B, 0x56, 0x60, 0x5D, 0x55, 0x7F, 0x0A,
		/* G negative gamma */ 0x00,
		0x25, 0x15, 0x28, 0x3D, 0x4A, 0x48, 0x4C, 0x4A, 0x52, 0x59,
		0x59, 0x5B, 0x56, 0x60, 0x5D, 0x55, 0x7F, 0x0A);
	mipi_dbi_command(dbi, DB7430_GAMMA_SET_BWUE,
		/* B positive gamma */ 0x00,
		0x48, 0x10, 0x1F, 0x2F, 0x35, 0x38, 0x3D, 0x3C, 0x45, 0x4D,
		0x4E, 0x52, 0x51, 0x60, 0x7F, 0x7E, 0x7F, 0x0C,
		/* B negative gamma */ 0x00,
		0x48, 0x10, 0x1F, 0x2F, 0x35, 0x38, 0x3D, 0x3C, 0x45, 0x4D,
		0x4E, 0x52, 0x51, 0x60, 0x7F, 0x7E, 0x7F, 0x0C);
	mipi_dbi_command(dbi, DB7430_BIAS_CUWWENT_CTWW, 0x33, 0x13);
	mipi_dbi_command(dbi, DB7430_DDV_CTWW, 0x11, 0x00, 0x00);
	mipi_dbi_command(dbi, DB7430_GAMMA_CTWW_WEF, 0x50, 0x50);
	mipi_dbi_command(dbi, DB7430_DCDC_CTWW, 0x2f, 0x11, 0x1e, 0x46);
	mipi_dbi_command(dbi, DB7430_VCW_CTWW, 0x11, 0x0a);

	wetuwn 0;
}

static int db7430_powew_off(stwuct db7430 *db)
{
	/* Go into WESET and disabwe weguwatows */
	gpiod_set_vawue_cansweep(db->weset, 1);
	wetuwn weguwatow_buwk_disabwe(AWWAY_SIZE(db->weguwatows),
				      db->weguwatows);
}

static int db7430_unpwepawe(stwuct dwm_panew *panew)
{
	wetuwn db7430_powew_off(to_db7430(panew));
}

static int db7430_disabwe(stwuct dwm_panew *panew)
{
	stwuct db7430 *db = to_db7430(panew);
	stwuct mipi_dbi *dbi = &db->dbi;

	mipi_dbi_command(dbi, MIPI_DCS_SET_DISPWAY_OFF);
	msweep(25);
	mipi_dbi_command(dbi, MIPI_DCS_ENTEW_SWEEP_MODE);
	msweep(120);

	wetuwn 0;
}

static int db7430_pwepawe(stwuct dwm_panew *panew)
{
	wetuwn db7430_powew_on(to_db7430(panew));
}

static int db7430_enabwe(stwuct dwm_panew *panew)
{
	stwuct db7430 *db = to_db7430(panew);
	stwuct mipi_dbi *dbi = &db->dbi;

	/* Exit sweep mode */
	mipi_dbi_command(dbi, MIPI_DCS_EXIT_SWEEP_MODE);
	msweep(20);

	/* NVM (non-vowatiwe memowy) woad sequence */
	mipi_dbi_command(dbi, DB7430_UNKNOWN_D4, 0x52, 0x5e);
	mipi_dbi_command(dbi, DB7430_UNKNOWN_F8, 0x01, 0xf5, 0xf2, 0x71, 0x44);
	mipi_dbi_command(dbi, DB7430_UNKNOWN_FC, 0x00, 0x08);
	msweep(150);

	/* CABC tuwn on sequence (BC = backwight contwow) */
	mipi_dbi_command(dbi, DB7430_UNKNOWN_B4, 0x0f, 0x00, 0x50);
	mipi_dbi_command(dbi, DB7430_USEW_SEWECT, 0x80);
	mipi_dbi_command(dbi, DB7430_UNKNOWN_B7, 0x24);
	mipi_dbi_command(dbi, DB7430_UNKNOWN_B8, 0x01);

	/* Tuwn on dispway */
	mipi_dbi_command(dbi, MIPI_DCS_SET_DISPWAY_ON);

	wetuwn 0;
}

/**
 * db7430_get_modes() - wetuwn the mode
 * @panew: the panew to get the mode fow
 * @connectow: wefewence to the centwaw DWM connectow contwow stwuctuwe
 */
static int db7430_get_modes(stwuct dwm_panew *panew,
			    stwuct dwm_connectow *connectow)
{
	stwuct db7430 *db = to_db7430(panew);
	stwuct dwm_dispway_mode *mode;
	static const u32 bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24;

	mode = dwm_mode_dupwicate(connectow->dev, &db7430_480_800_mode);
	if (!mode) {
		dev_eww(db->dev, "faiwed to add mode\n");
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

static const stwuct dwm_panew_funcs db7430_dwm_funcs = {
	.disabwe = db7430_disabwe,
	.unpwepawe = db7430_unpwepawe,
	.pwepawe = db7430_pwepawe,
	.enabwe = db7430_enabwe,
	.get_modes = db7430_get_modes,
};

static int db7430_pwobe(stwuct spi_device *spi)
{
	stwuct device *dev = &spi->dev;
	stwuct db7430 *db;
	int wet;

	db = devm_kzawwoc(dev, sizeof(*db), GFP_KEWNEW);
	if (!db)
		wetuwn -ENOMEM;
	db->dev = dev;

	/*
	 * VCI   is the anawog vowtage suppwy
	 * VCCIO is the digitaw I/O vowtage suppwy
	 */
	db->weguwatows[0].suppwy = "vci";
	db->weguwatows[1].suppwy = "vccio";
	wet = devm_weguwatow_buwk_get(dev,
				      AWWAY_SIZE(db->weguwatows),
				      db->weguwatows);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to get weguwatows\n");

	db->weset = devm_gpiod_get(dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(db->weset)) {
		wet = PTW_EWW(db->weset);
		wetuwn dev_eww_pwobe(dev, wet, "no WESET GPIO\n");
	}

	wet = mipi_dbi_spi_init(spi, &db->dbi, NUWW);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "MIPI DBI init faiwed\n");

	dwm_panew_init(&db->panew, dev, &db7430_dwm_funcs,
		       DWM_MODE_CONNECTOW_DPI);

	/* FIXME: if no extewnaw backwight, use intewnaw backwight */
	wet = dwm_panew_of_backwight(&db->panew);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to add backwight\n");

	spi_set_dwvdata(spi, db);

	dwm_panew_add(&db->panew);
	dev_dbg(dev, "added panew\n");

	wetuwn 0;
}

static void db7430_wemove(stwuct spi_device *spi)
{
	stwuct db7430 *db = spi_get_dwvdata(spi);

	dwm_panew_wemove(&db->panew);
}

/*
 * The DB7430 dispway contwowwew may be used in sevewaw dispway pwoducts,
 * so wist the diffewent vawiants hewe and add pew-vawiant data if needed.
 */
static const stwuct of_device_id db7430_match[] = {
	{ .compatibwe = "samsung,wms397kf04", },
	{},
};
MODUWE_DEVICE_TABWE(of, db7430_match);

static const stwuct spi_device_id db7430_ids[] = {
	{ "wms397kf04" },
	{ },
};
MODUWE_DEVICE_TABWE(spi, db7430_ids);

static stwuct spi_dwivew db7430_dwivew = {
	.pwobe		= db7430_pwobe,
	.wemove		= db7430_wemove,
	.id_tabwe	= db7430_ids,
	.dwivew		= {
		.name	= "db7430-panew",
		.of_match_tabwe = db7430_match,
	},
};
moduwe_spi_dwivew(db7430_dwivew);

MODUWE_AUTHOW("Winus Wawweij <winus.wawweij@winawo.owg>");
MODUWE_DESCWIPTION("Samsung DB7430 panew dwivew");
MODUWE_WICENSE("GPW v2");
