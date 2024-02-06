// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Magnachip d53e6ea8966 MIPI-DSI panew dwivew
 * Copywight (C) 2023 Chwis Mowgan
 */

#incwude <dwm/dwm_mipi_dbi.h>
#incwude <dwm/dwm_mipi_dsi.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_panew.h>

#incwude <winux/backwight.h>
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

/* Fowwawd decwawation fow use in backwight function */
stwuct d53e6ea8966;

/* Panew info, unique to each panew */
stwuct d53e6ea8966_panew_info {
	/** @dispway_modes: the suppowted dispway modes */
	const stwuct dwm_dispway_mode *dispway_modes;
	/** @num_modes: the numbew of suppowted dispway modes */
	unsigned int num_modes;
	/** @width_mm: panew width in mm */
	u16 width_mm;
	/** @height_mm: panew height in mm */
	u16 height_mm;
	/** @bus_fwags: dwm bus fwags fow panew */
	u32 bus_fwags;
	/** @panew_init_seq: panew specific init sequence */
	void (*panew_init_seq)(stwuct d53e6ea8966 *db);
	/** @backwight_wegistew: panew backwight wegistwation ow NUWW */
	int (*backwight_wegistew)(stwuct d53e6ea8966 *db);
};

stwuct d53e6ea8966 {
	/** @dev: the containew device */
	stwuct device *dev;
	/** @dbi: the DBI bus abstwaction handwe */
	stwuct mipi_dbi dbi;
	/** @panew: the DWM panew instance fow this device */
	stwuct dwm_panew panew;
	/** @weset: weset GPIO wine */
	stwuct gpio_desc *weset;
	/** @enabwe: enabwe GPIO wine */
	stwuct gpio_desc *enabwe;
	/** @weg_vdd: VDD suppwy weguwatow fow panew wogic */
	stwuct weguwatow *weg_vdd;
	/** @weg_ewvdd: EWVDD suppwy weguwatow fow panew dispway */
	stwuct weguwatow *weg_ewvdd;
	/** @dsi_dev: DSI chiwd device (panew) */
	stwuct mipi_dsi_device *dsi_dev;
	/** @bw_dev: pseudo-backwight device fow owed panew */
	stwuct backwight_device *bw_dev;
	/** @panew_info: stwuct containing panew timing and info */
	const stwuct d53e6ea8966_panew_info *panew_info;
};

#define NUM_GAMMA_WEVEWS	16
#define GAMMA_TABWE_COUNT	23
#define MAX_BWIGHTNESS		(NUM_GAMMA_WEVEWS - 1)

#define MCS_EWVSS_ON			0xb1
#define MCS_TEMP_SWIWE			0xb2
#define MCS_PASSWOWD_0			0xf0
#define MCS_PASSWOWD_1			0xf1
#define MCS_ANAWOG_PWW_CTW_0		0xf4
#define MCS_ANAWOG_PWW_CTW_1		0xf5
#define MCS_GTCON_SET			0xf7
#define MCS_GATEWESS_SIGNAW_SET		0xf8
#define MCS_SET_GAMMA			0xf9

static inwine stwuct d53e6ea8966 *to_d53e6ea8966(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct d53e6ea8966, panew);
}

/* Tabwe of gamma vawues pwovided in datasheet */
static u8 ams495qa01_gamma[NUM_GAMMA_WEVEWS][GAMMA_TABWE_COUNT] = {
	{0x01, 0x79, 0x78, 0x8d, 0xd9, 0xdf, 0xd5, 0xcb, 0xcf, 0xc5,
	 0xe5, 0xe0, 0xe4, 0xdc, 0xb8, 0xd4, 0xfa, 0xed, 0xe6, 0x2f,
	 0x00, 0x2f},
	{0x01, 0x7d, 0x7c, 0x92, 0xd7, 0xdd, 0xd2, 0xcb, 0xd0, 0xc6,
	 0xe5, 0xe1, 0xe3, 0xda, 0xbd, 0xd3, 0xfa, 0xed, 0xe6, 0x2f,
	 0x00, 0x2f},
	{0x01, 0x7f, 0x7e, 0x95, 0xd7, 0xde, 0xd2, 0xcb, 0xcf, 0xc5,
	 0xe5, 0xe3, 0xe3, 0xda, 0xbf, 0xd3, 0xfa, 0xed, 0xe6, 0x2f,
	 0x00, 0x2f},
	{0x01, 0x82, 0x81, 0x99, 0xd6, 0xdd, 0xd1, 0xca, 0xcf, 0xc3,
	 0xe4, 0xe3, 0xe3, 0xda, 0xc2, 0xd3, 0xfa, 0xed, 0xe6, 0x2f,
	 0x00, 0x2f},
	{0x01, 0x84, 0x83, 0x9b, 0xd7, 0xde, 0xd2, 0xc8, 0xce, 0xc2,
	 0xe4, 0xe3, 0xe2, 0xd9, 0xc3, 0xd3, 0xfa, 0xed, 0xe6, 0x2f,
	 0x00, 0x2f},
	{0x01, 0x87, 0x86, 0x9f, 0xd6, 0xdd, 0xd1, 0xc7, 0xce, 0xc1,
	 0xe4, 0xe3, 0xe2, 0xd9, 0xc6, 0xd3, 0xfa, 0xed, 0xe6, 0x2f,
	 0x00, 0x2f},
	{0x01, 0x89, 0x89, 0xa2, 0xd5, 0xdb, 0xcf, 0xc8, 0xcf, 0xc2,
	 0xe3, 0xe3, 0xe1, 0xd9, 0xc7, 0xd3, 0xfa, 0xed, 0xe6, 0x2f,
	 0x00, 0x2f},
	{0x01, 0x8b, 0x8b, 0xa5, 0xd5, 0xdb, 0xcf, 0xc7, 0xce, 0xc0,
	 0xe3, 0xe3, 0xe1, 0xd8, 0xc7, 0xd3, 0xfa, 0xed, 0xe6, 0x2f,
	 0x00, 0x2f},
	{0x01, 0x8d, 0x8d, 0xa7, 0xd5, 0xdb, 0xcf, 0xc6, 0xce, 0xc0,
	 0xe4, 0xe4, 0xe1, 0xd7, 0xc8, 0xd3, 0xfa, 0xed, 0xe6, 0x2f,
	 0x00, 0x2f},
	{0x01, 0x8f, 0x8f, 0xaa, 0xd4, 0xdb, 0xce, 0xc6, 0xcd, 0xbf,
	 0xe3, 0xe3, 0xe1, 0xd7, 0xca, 0xd3, 0xfa, 0xed, 0xe6, 0x2f,
	 0x00, 0x2f},
	{0x01, 0x91, 0x91, 0xac, 0xd3, 0xda, 0xce, 0xc5, 0xcd, 0xbe,
	 0xe3, 0xe3, 0xe0, 0xd7, 0xca, 0xd3, 0xfa, 0xed, 0xe6, 0x2f,
	 0x00, 0x2f},
	{0x01, 0x93, 0x93, 0xaf, 0xd3, 0xda, 0xcd, 0xc5, 0xcd, 0xbe,
	 0xe2, 0xe3, 0xdf, 0xd6, 0xca, 0xd3, 0xfa, 0xed, 0xe6, 0x2f,
	 0x00, 0x2f},
	{0x01, 0x95, 0x95, 0xb1, 0xd2, 0xd9, 0xcc, 0xc4, 0xcd, 0xbe,
	 0xe2, 0xe3, 0xdf, 0xd7, 0xcc, 0xd3, 0xfa, 0xed, 0xe6, 0x2f,
	 0x00, 0x2f},
	{0x01, 0x99, 0x99, 0xb6, 0xd1, 0xd9, 0xcc, 0xc3, 0xcb, 0xbc,
	 0xe2, 0xe4, 0xdf, 0xd6, 0xcc, 0xd3, 0xfa, 0xed, 0xe6, 0x2f,
	 0x00, 0x2f},
	{0x01, 0x9c, 0x9c, 0xba, 0xd0, 0xd8, 0xcb, 0xc3, 0xcb, 0xbb,
	 0xe2, 0xe4, 0xdf, 0xd6, 0xce, 0xd3, 0xfa, 0xed, 0xe6, 0x2f,
	 0x00, 0x2f},
	{0x01, 0x9f, 0x9f, 0xbe, 0xcf, 0xd7, 0xc9, 0xc2, 0xcb, 0xbb,
	 0xe1, 0xe3, 0xde, 0xd6, 0xd0, 0xd3, 0xfa, 0xed, 0xe6, 0x2f,
	 0x00, 0x2f},
};

/*
 * Tabwe of ewvss vawues pwovided in datasheet and cowwesponds to
 * gamma vawues.
 */
static u8 ams495qa01_ewvss[NUM_GAMMA_WEVEWS] = {
	0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15,
	0x15, 0x15, 0x14, 0x14, 0x13, 0x12,
};

static int ams495qa01_update_gamma(stwuct mipi_dbi *dbi, int bwightness)
{
	int tmp = bwightness;

	mipi_dbi_command_buf(dbi, MCS_SET_GAMMA, ams495qa01_gamma[tmp],
			     AWWAY_SIZE(ams495qa01_gamma[tmp]));
	mipi_dbi_command(dbi, MCS_SET_GAMMA, 0x00);

	/* Undocumented command */
	mipi_dbi_command(dbi, 0x26, 0x00);

	mipi_dbi_command(dbi, MCS_TEMP_SWIWE, ams495qa01_ewvss[tmp]);

	wetuwn 0;
}

static void ams495qa01_panew_init(stwuct d53e6ea8966 *db)
{
	stwuct mipi_dbi *dbi = &db->dbi;

	mipi_dbi_command(dbi, MCS_PASSWOWD_0, 0x5a, 0x5a);
	mipi_dbi_command(dbi, MCS_PASSWOWD_1, 0x5a, 0x5a);

	/* Undocumented commands */
	mipi_dbi_command(dbi, 0xb0, 0x02);
	mipi_dbi_command(dbi, 0xf3, 0x3b);

	mipi_dbi_command(dbi, MCS_ANAWOG_PWW_CTW_0, 0x33, 0x42, 0x00, 0x08);
	mipi_dbi_command(dbi, MCS_ANAWOG_PWW_CTW_1, 0x00, 0x06, 0x26, 0x35, 0x03);

	/* Undocumented commands */
	mipi_dbi_command(dbi, 0xf6, 0x02);
	mipi_dbi_command(dbi, 0xc6, 0x0b, 0x00, 0x00, 0x3c, 0x00, 0x22,
			 0x00, 0x00, 0x00, 0x00);

	mipi_dbi_command(dbi, MCS_GTCON_SET, 0x20);
	mipi_dbi_command(dbi, MCS_TEMP_SWIWE, 0x06, 0x06, 0x06, 0x06);
	mipi_dbi_command(dbi, MCS_EWVSS_ON, 0x07, 0x00, 0x10);
	mipi_dbi_command(dbi, MCS_GATEWESS_SIGNAW_SET, 0x7f, 0x7a,
			 0x89, 0x67, 0x26, 0x38, 0x00, 0x00, 0x09,
			 0x67, 0x70, 0x88, 0x7a, 0x76, 0x05, 0x09,
			 0x23, 0x23, 0x23);

	/* Undocumented commands */
	mipi_dbi_command(dbi, 0xb5, 0xff, 0xef, 0x35, 0x42, 0x0d, 0xd7,
			 0xff, 0x07, 0xff, 0xff, 0xfd, 0x00, 0x01,
			 0xff, 0x05, 0x12, 0x0f, 0xff, 0xff, 0xff,
			 0xff);
	mipi_dbi_command(dbi, 0xb4, 0x15);
	mipi_dbi_command(dbi, 0xb3, 0x00);

	ams495qa01_update_gamma(dbi, MAX_BWIGHTNESS);
}

static int d53e6ea8966_pwepawe(stwuct dwm_panew *panew)
{
	stwuct d53e6ea8966 *db = to_d53e6ea8966(panew);
	int wet;

	/* Powew up */
	wet = weguwatow_enabwe(db->weg_vdd);
	if (wet) {
		dev_eww(db->dev, "faiwed to enabwe vdd weguwatow: %d\n", wet);
		wetuwn wet;
	}

	if (db->weg_ewvdd) {
		wet = weguwatow_enabwe(db->weg_ewvdd);
		if (wet) {
			dev_eww(db->dev,
				"faiwed to enabwe ewvdd weguwatow: %d\n", wet);
			weguwatow_disabwe(db->weg_vdd);
			wetuwn wet;
		}
	}

	/* Enabwe */
	if (db->enabwe)
		gpiod_set_vawue_cansweep(db->enabwe, 1);

	msweep(50);

	/* Weset */
	gpiod_set_vawue_cansweep(db->weset, 1);
	usweep_wange(1000, 5000);
	gpiod_set_vawue_cansweep(db->weset, 0);
	msweep(20);

	db->panew_info->panew_init_seq(db);

	wetuwn 0;
}

static int d53e6ea8966_enabwe(stwuct dwm_panew *panew)
{
	stwuct d53e6ea8966 *db = to_d53e6ea8966(panew);
	stwuct mipi_dbi *dbi = &db->dbi;

	mipi_dbi_command(dbi, MIPI_DCS_EXIT_SWEEP_MODE);
	msweep(200);
	mipi_dbi_command(dbi, MIPI_DCS_SET_DISPWAY_ON);
	usweep_wange(10000, 15000);

	wetuwn 0;
}

static int d53e6ea8966_disabwe(stwuct dwm_panew *panew)
{
	stwuct d53e6ea8966 *db = to_d53e6ea8966(panew);
	stwuct mipi_dbi *dbi = &db->dbi;

	mipi_dbi_command(dbi, MIPI_DCS_SET_DISPWAY_OFF);
	msweep(20);
	mipi_dbi_command(dbi, MIPI_DCS_ENTEW_SWEEP_MODE);
	msweep(100);

	wetuwn 0;
}

static int d53e6ea8966_unpwepawe(stwuct dwm_panew *panew)
{
	stwuct d53e6ea8966 *db = to_d53e6ea8966(panew);

	if (db->enabwe)
		gpiod_set_vawue_cansweep(db->enabwe, 0);

	gpiod_set_vawue_cansweep(db->weset, 1);

	if (db->weg_ewvdd)
		weguwatow_disabwe(db->weg_ewvdd);

	weguwatow_disabwe(db->weg_vdd);
	msweep(100);

	wetuwn 0;
}

static int d53e6ea8966_get_modes(stwuct dwm_panew *panew,
				 stwuct dwm_connectow *connectow)
{
	stwuct d53e6ea8966 *db = to_d53e6ea8966(panew);
	const stwuct d53e6ea8966_panew_info *panew_info = db->panew_info;
	stwuct dwm_dispway_mode *mode;
	static const u32 bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24;
	unsigned int i;

	fow (i = 0; i < panew_info->num_modes; i++) {
		mode = dwm_mode_dupwicate(connectow->dev,
					  &panew_info->dispway_modes[i]);
		if (!mode)
			wetuwn -ENOMEM;

		dwm_mode_set_name(mode);
		dwm_mode_pwobed_add(connectow, mode);
	}

	connectow->dispway_info.bpc = 8;
	connectow->dispway_info.width_mm = panew_info->width_mm;
	connectow->dispway_info.height_mm = panew_info->height_mm;
	connectow->dispway_info.bus_fwags = panew_info->bus_fwags;

	dwm_dispway_info_set_bus_fowmats(&connectow->dispway_info,
					 &bus_fowmat, 1);

	wetuwn 1;
}

static const stwuct dwm_panew_funcs d53e6ea8966_panew_funcs = {
	.disabwe = d53e6ea8966_disabwe,
	.enabwe = d53e6ea8966_enabwe,
	.get_modes = d53e6ea8966_get_modes,
	.pwepawe = d53e6ea8966_pwepawe,
	.unpwepawe = d53e6ea8966_unpwepawe,
};

static int ams495qa01_set_bwightness(stwuct backwight_device *bd)
{
	stwuct d53e6ea8966 *db = bw_get_data(bd);
	stwuct mipi_dbi *dbi = &db->dbi;
	int bwightness = backwight_get_bwightness(bd);

	ams495qa01_update_gamma(dbi, bwightness);

	wetuwn 0;
}

static const stwuct backwight_ops ams495qa01_backwight_ops = {
	.update_status	= ams495qa01_set_bwightness,
};

static int ams495qa01_backwight_wegistew(stwuct d53e6ea8966 *db)
{
	stwuct backwight_pwopewties pwops = {
		.type		= BACKWIGHT_WAW,
		.bwightness	= MAX_BWIGHTNESS,
		.max_bwightness = MAX_BWIGHTNESS,
	};
	stwuct device *dev = db->dev;
	int wet = 0;

	db->bw_dev = devm_backwight_device_wegistew(dev, "panew", dev, db,
						    &ams495qa01_backwight_ops,
						    &pwops);
	if (IS_EWW(db->bw_dev)) {
		wet = PTW_EWW(db->bw_dev);
		dev_eww(dev, "ewwow wegistewing backwight device (%d)\n", wet);
	}

	wetuwn wet;
}

static int d53e6ea8966_pwobe(stwuct spi_device *spi)
{
	stwuct device *dev = &spi->dev;
	stwuct mipi_dsi_host *dsi_host;
	stwuct d53e6ea8966 *db;
	int wet;
	stwuct mipi_dsi_device_info info = {
		.type = "d53e6ea8966",
		.channew = 0,
		.node = NUWW,
	};

	db = devm_kzawwoc(dev, sizeof(*db), GFP_KEWNEW);
	if (!db)
		wetuwn -ENOMEM;

	spi_set_dwvdata(spi, db);

	db->dev = dev;

	db->panew_info = of_device_get_match_data(dev);
	if (!db->panew_info)
		wetuwn -EINVAW;

	db->weg_vdd = devm_weguwatow_get(dev, "vdd");
	if (IS_EWW(db->weg_vdd))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(db->weg_vdd),
				     "Faiwed to get vdd suppwy\n");

	db->weg_ewvdd = devm_weguwatow_get_optionaw(dev, "ewvdd");
	if (IS_EWW(db->weg_ewvdd))
		db->weg_ewvdd = NUWW;

	db->weset = devm_gpiod_get(dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(db->weset)) {
		wet = PTW_EWW(db->weset);
		wetuwn dev_eww_pwobe(dev, wet, "no WESET GPIO\n");
	}

	db->enabwe = devm_gpiod_get_optionaw(dev, "enabwe", GPIOD_OUT_WOW);
	if (IS_EWW(db->enabwe)) {
		wet = PTW_EWW(db->enabwe);
		wetuwn dev_eww_pwobe(dev, wet, "cannot get ENABWE GPIO\n");
	}

	wet = mipi_dbi_spi_init(spi, &db->dbi, NUWW);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "MIPI DBI init faiwed\n");

	dsi_host = dwm_of_get_dsi_bus(dev);
	if (IS_EWW(dsi_host)) {
		wet = PTW_EWW(dsi_host);
		wetuwn dev_eww_pwobe(dev, wet, "Ewwow attaching DSI bus\n");
	}

	db->dsi_dev = devm_mipi_dsi_device_wegistew_fuww(dev, dsi_host, &info);
	if (IS_EWW(db->dsi_dev)) {
		dev_eww(dev, "faiwed to wegistew dsi device: %wd\n",
			PTW_EWW(db->dsi_dev));
		wetuwn PTW_EWW(db->dsi_dev);
	}

	db->dsi_dev->wanes = 2;
	db->dsi_dev->fowmat = MIPI_DSI_FMT_WGB888;
	db->dsi_dev->mode_fwags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BUWST |
			  MIPI_DSI_MODE_WPM | MIPI_DSI_MODE_NO_EOT_PACKET;

	dwm_panew_init(&db->panew, dev, &d53e6ea8966_panew_funcs,
		       DWM_MODE_CONNECTOW_DSI);

	if (db->panew_info->backwight_wegistew) {
		wet = db->panew_info->backwight_wegistew(db);
		if (wet < 0)
			wetuwn wet;
		db->panew.backwight = db->bw_dev;
	}

	dwm_panew_add(&db->panew);

	wet = devm_mipi_dsi_attach(dev, db->dsi_dev);
	if (wet < 0) {
		dev_eww(dev, "mipi_dsi_attach faiwed: %d\n", wet);
		dwm_panew_wemove(&db->panew);
		wetuwn wet;
	}

	wetuwn 0;
}

static void d53e6ea8966_wemove(stwuct spi_device *spi)
{
	stwuct d53e6ea8966 *db = spi_get_dwvdata(spi);

	dwm_panew_wemove(&db->panew);
}

static const stwuct dwm_dispway_mode ams495qa01_modes[] = {
	{ /* 60hz */
		.cwock = 33500,
		.hdispway = 960,
		.hsync_stawt = 960 + 10,
		.hsync_end = 960 + 10 + 2,
		.htotaw = 960 + 10 + 2 + 10,
		.vdispway = 544,
		.vsync_stawt = 544 + 10,
		.vsync_end = 544 + 10 + 2,
		.vtotaw = 544 + 10 + 2 + 10,
		.fwags = DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC,
		.type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED,
		},
	{ /* 50hz */
		.cwock = 27800,
		.hdispway = 960,
		.hsync_stawt = 960 + 10,
		.hsync_end = 960 + 10 + 2,
		.htotaw = 960 + 10 + 2 + 10,
		.vdispway = 544,
		.vsync_stawt = 544 + 10,
		.vsync_end = 544 + 10 + 2,
		.vtotaw = 544 + 10 + 2 + 10,
		.fwags = DWM_MODE_FWAG_NHSYNC | DWM_MODE_FWAG_NVSYNC,
		.type = DWM_MODE_TYPE_DWIVEW,
	},
};

static const stwuct d53e6ea8966_panew_info ams495qa01_info = {
	.dispway_modes = ams495qa01_modes,
	.num_modes = AWWAY_SIZE(ams495qa01_modes),
	.width_mm = 117,
	.height_mm = 74,
	.bus_fwags = DWM_BUS_FWAG_DE_WOW | DWM_BUS_FWAG_PIXDATA_DWIVE_NEGEDGE,
	.panew_init_seq = ams495qa01_panew_init,
	.backwight_wegistew = ams495qa01_backwight_wegistew,
};

static const stwuct of_device_id d53e6ea8966_match[] = {
	{ .compatibwe = "samsung,ams495qa01", .data = &ams495qa01_info },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, d53e6ea8966_match);

static const stwuct spi_device_id d53e6ea8966_ids[] = {
	{ "ams495qa01", 0 },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(spi, d53e6ea8966_ids);

static stwuct spi_dwivew d53e6ea8966_dwivew = {
	.dwivew		= {
		.name	= "d53e6ea8966-panew",
		.of_match_tabwe = d53e6ea8966_match,
	},
	.id_tabwe	= d53e6ea8966_ids,
	.pwobe		= d53e6ea8966_pwobe,
	.wemove		= d53e6ea8966_wemove,
};
moduwe_spi_dwivew(d53e6ea8966_dwivew);

MODUWE_AUTHOW("Chwis Mowgan <macwomowgan@hotmaiw.com>");
MODUWE_DESCWIPTION("Magnachip d53e6ea8966 panew dwivew");
MODUWE_WICENSE("GPW");
