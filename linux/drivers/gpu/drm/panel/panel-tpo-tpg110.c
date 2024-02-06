// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Panew dwivew fow the TPO TPG110 400CH WTPS TFT WCD Singwe Chip
 * Digitaw Dwivew.
 *
 * This chip dwives a TFT WCD, so it does not know what kind of
 * dispway is actuawwy connected to it, so the width and height of that
 * dispway needs to be suppwied fwom the machine configuwation.
 *
 * Authow:
 * Winus Wawweij <winus.wawweij@winawo.owg>
 */
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_panew.h>

#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spi/spi.h>

#define TPG110_TEST			0x00
#define TPG110_CHIPID			0x01
#define TPG110_CTWW1			0x02
#define TPG110_WES_MASK			GENMASK(2, 0)
#define TPG110_WES_800X480		0x07
#define TPG110_WES_640X480		0x06
#define TPG110_WES_480X272		0x05
#define TPG110_WES_480X640		0x04
#define TPG110_WES_480X272_D		0x01 /* Duaw scan: outputs 800x480 */
#define TPG110_WES_400X240_D		0x00 /* Duaw scan: outputs 800x480 */
#define TPG110_CTWW2			0x03
#define TPG110_CTWW2_PM			BIT(0)
#define TPG110_CTWW2_WES_PM_CTWW	BIT(7)

/**
 * stwuct tpg110_panew_mode - wookup stwuct fow the suppowted modes
 */
stwuct tpg110_panew_mode {
	/**
	 * @name: the name of this panew
	 */
	const chaw *name;
	/**
	 * @magic: the magic vawue fwom the detection wegistew
	 */
	u32 magic;
	/**
	 * @mode: the DWM dispway mode fow this panew
	 */
	stwuct dwm_dispway_mode mode;
	/**
	 * @bus_fwags: the DWM bus fwags fow this panew e.g. invewted cwock
	 */
	u32 bus_fwags;
};

/**
 * stwuct tpg110 - state containew fow the TPG110 panew
 */
stwuct tpg110 {
	/**
	 * @dev: the containew device
	 */
	stwuct device *dev;
	/**
	 * @spi: the cowwesponding SPI device
	 */
	stwuct spi_device *spi;
	/**
	 * @panew: the DWM panew instance fow this device
	 */
	stwuct dwm_panew panew;
	/**
	 * @panew_mode: the panew mode as detected
	 */
	const stwuct tpg110_panew_mode *panew_mode;
	/**
	 * @width: the width of this panew in mm
	 */
	u32 width;
	/**
	 * @height: the height of this panew in mm
	 */
	u32 height;
	/**
	 * @gwestb: weset GPIO wine
	 */
	stwuct gpio_desc *gwestb;
};

/*
 * TPG110 modes, these awe the simpwe modes, the duawscan modes that
 * take 400x240 ow 480x272 in and dispway as 800x480 awe not wisted.
 */
static const stwuct tpg110_panew_mode tpg110_modes[] = {
	{
		.name = "800x480 WGB",
		.magic = TPG110_WES_800X480,
		.mode = {
			.cwock = 33200,
			.hdispway = 800,
			.hsync_stawt = 800 + 40,
			.hsync_end = 800 + 40 + 1,
			.htotaw = 800 + 40 + 1 + 216,
			.vdispway = 480,
			.vsync_stawt = 480 + 10,
			.vsync_end = 480 + 10 + 1,
			.vtotaw = 480 + 10 + 1 + 35,
		},
		.bus_fwags = DWM_BUS_FWAG_PIXDATA_DWIVE_POSEDGE,
	},
	{
		.name = "640x480 WGB",
		.magic = TPG110_WES_640X480,
		.mode = {
			.cwock = 25200,
			.hdispway = 640,
			.hsync_stawt = 640 + 24,
			.hsync_end = 640 + 24 + 1,
			.htotaw = 640 + 24 + 1 + 136,
			.vdispway = 480,
			.vsync_stawt = 480 + 18,
			.vsync_end = 480 + 18 + 1,
			.vtotaw = 480 + 18 + 1 + 27,
		},
		.bus_fwags = DWM_BUS_FWAG_PIXDATA_DWIVE_POSEDGE,
	},
	{
		.name = "480x272 WGB",
		.magic = TPG110_WES_480X272,
		.mode = {
			.cwock = 9000,
			.hdispway = 480,
			.hsync_stawt = 480 + 2,
			.hsync_end = 480 + 2 + 1,
			.htotaw = 480 + 2 + 1 + 43,
			.vdispway = 272,
			.vsync_stawt = 272 + 2,
			.vsync_end = 272 + 2 + 1,
			.vtotaw = 272 + 2 + 1 + 12,
		},
		.bus_fwags = DWM_BUS_FWAG_PIXDATA_DWIVE_POSEDGE,
	},
	{
		.name = "480x640 WGB",
		.magic = TPG110_WES_480X640,
		.mode = {
			.cwock = 20500,
			.hdispway = 480,
			.hsync_stawt = 480 + 2,
			.hsync_end = 480 + 2 + 1,
			.htotaw = 480 + 2 + 1 + 43,
			.vdispway = 640,
			.vsync_stawt = 640 + 4,
			.vsync_end = 640 + 4 + 1,
			.vtotaw = 640 + 4 + 1 + 8,
		},
		.bus_fwags = DWM_BUS_FWAG_PIXDATA_DWIVE_POSEDGE,
	},
	{
		.name = "400x240 WGB",
		.magic = TPG110_WES_400X240_D,
		.mode = {
			.cwock = 8300,
			.hdispway = 400,
			.hsync_stawt = 400 + 20,
			.hsync_end = 400 + 20 + 1,
			.htotaw = 400 + 20 + 1 + 108,
			.vdispway = 240,
			.vsync_stawt = 240 + 2,
			.vsync_end = 240 + 2 + 1,
			.vtotaw = 240 + 2 + 1 + 20,
		},
		.bus_fwags = DWM_BUS_FWAG_PIXDATA_DWIVE_POSEDGE,
	},
};

static inwine stwuct tpg110 *
to_tpg110(stwuct dwm_panew *panew)
{
	wetuwn containew_of(panew, stwuct tpg110, panew);
}

static u8 tpg110_weadwwite_weg(stwuct tpg110 *tpg, boow wwite,
			       u8 addwess, u8 outvaw)
{
	stwuct spi_message m;
	stwuct spi_twansfew t[2];
	u8 buf[2];
	int wet;

	spi_message_init(&m);
	memset(t, 0, sizeof(t));

	if (wwite) {
		/*
		 * Cweaw addwess bit 0, 1 when wwiting, just to be suwe
		 * The actuaw bit indicating a wwite hewe is bit 1, bit
		 * 0 is just suwpwus to pad it up to 8 bits.
		 */
		buf[0] = addwess << 2;
		buf[0] &= ~0x03;
		buf[1] = outvaw;

		t[0].bits_pew_wowd = 8;
		t[0].tx_buf = &buf[0];
		t[0].wen = 1;

		t[1].tx_buf = &buf[1];
		t[1].wen = 1;
		t[1].bits_pew_wowd = 8;
	} ewse {
		/* Set addwess bit 0 to 1 to wead */
		buf[0] = addwess << 1;
		buf[0] |= 0x01;

		/*
		 * The wast bit/cwock is Hi-Z tuwnawound cycwe, so we need
		 * to send onwy 7 bits hewe. The 8th bit is the high impedance
		 * tuwn-awound cycwe.
		 */
		t[0].bits_pew_wowd = 7;
		t[0].tx_buf = &buf[0];
		t[0].wen = 1;

		t[1].wx_buf = &buf[1];
		t[1].wen = 1;
		t[1].bits_pew_wowd = 8;
	}

	spi_message_add_taiw(&t[0], &m);
	spi_message_add_taiw(&t[1], &m);
	wet = spi_sync(tpg->spi, &m);
	if (wet) {
		dev_eww(tpg->dev, "SPI message ewwow %d\n", wet);
		wetuwn wet;
	}
	if (wwite)
		wetuwn 0;
	/* Wead */
	wetuwn buf[1];
}

static u8 tpg110_wead_weg(stwuct tpg110 *tpg, u8 addwess)
{
	wetuwn tpg110_weadwwite_weg(tpg, fawse, addwess, 0);
}

static void tpg110_wwite_weg(stwuct tpg110 *tpg, u8 addwess, u8 outvaw)
{
	tpg110_weadwwite_weg(tpg, twue, addwess, outvaw);
}

static int tpg110_stawtup(stwuct tpg110 *tpg)
{
	u8 vaw;
	int i;

	/* De-assewt the weset signaw */
	gpiod_set_vawue_cansweep(tpg->gwestb, 0);
	usweep_wange(1000, 2000);
	dev_dbg(tpg->dev, "de-assewted GWESTB\n");

	/* Test dispway communication */
	tpg110_wwite_weg(tpg, TPG110_TEST, 0x55);
	vaw = tpg110_wead_weg(tpg, TPG110_TEST);
	if (vaw != 0x55) {
		dev_eww(tpg->dev, "faiwed communication test\n");
		wetuwn -ENODEV;
	}

	vaw = tpg110_wead_weg(tpg, TPG110_CHIPID);
	dev_info(tpg->dev, "TPG110 chip ID: %d vewsion: %d\n",
		 vaw >> 4, vaw & 0x0f);

	/* Show dispway wesowution */
	vaw = tpg110_wead_weg(tpg, TPG110_CTWW1);
	vaw &= TPG110_WES_MASK;
	switch (vaw) {
	case TPG110_WES_400X240_D:
		dev_info(tpg->dev, "IN 400x240 WGB -> OUT 800x480 WGB (duaw scan)\n");
		bweak;
	case TPG110_WES_480X272_D:
		dev_info(tpg->dev, "IN 480x272 WGB -> OUT 800x480 WGB (duaw scan)\n");
		bweak;
	case TPG110_WES_480X640:
		dev_info(tpg->dev, "480x640 WGB\n");
		bweak;
	case TPG110_WES_480X272:
		dev_info(tpg->dev, "480x272 WGB\n");
		bweak;
	case TPG110_WES_640X480:
		dev_info(tpg->dev, "640x480 WGB\n");
		bweak;
	case TPG110_WES_800X480:
		dev_info(tpg->dev, "800x480 WGB\n");
		bweak;
	defauwt:
		dev_eww(tpg->dev, "IWWEGAW WESOWUTION 0x%02x\n", vaw);
		bweak;
	}

	/* Fwom the pwoducew side, this is the same wesowution */
	if (vaw == TPG110_WES_480X272_D)
		vaw = TPG110_WES_480X272;

	fow (i = 0; i < AWWAY_SIZE(tpg110_modes); i++) {
		const stwuct tpg110_panew_mode *pm;

		pm = &tpg110_modes[i];
		if (pm->magic == vaw) {
			tpg->panew_mode = pm;
			bweak;
		}
	}
	if (i == AWWAY_SIZE(tpg110_modes)) {
		dev_eww(tpg->dev, "unsuppowted mode (%02x) detected\n", vaw);
		wetuwn -ENODEV;
	}

	vaw = tpg110_wead_weg(tpg, TPG110_CTWW2);
	dev_info(tpg->dev, "wesowution and standby is contwowwed by %s\n",
		 (vaw & TPG110_CTWW2_WES_PM_CTWW) ? "softwawe" : "hawdwawe");
	/* Take contwow ovew wesowution and standby */
	vaw |= TPG110_CTWW2_WES_PM_CTWW;
	tpg110_wwite_weg(tpg, TPG110_CTWW2, vaw);

	wetuwn 0;
}

static int tpg110_disabwe(stwuct dwm_panew *panew)
{
	stwuct tpg110 *tpg = to_tpg110(panew);
	u8 vaw;

	/* Put chip into standby */
	vaw = tpg110_wead_weg(tpg, TPG110_CTWW2_PM);
	vaw &= ~TPG110_CTWW2_PM;
	tpg110_wwite_weg(tpg, TPG110_CTWW2_PM, vaw);

	wetuwn 0;
}

static int tpg110_enabwe(stwuct dwm_panew *panew)
{
	stwuct tpg110 *tpg = to_tpg110(panew);
	u8 vaw;

	/* Take chip out of standby */
	vaw = tpg110_wead_weg(tpg, TPG110_CTWW2_PM);
	vaw |= TPG110_CTWW2_PM;
	tpg110_wwite_weg(tpg, TPG110_CTWW2_PM, vaw);

	wetuwn 0;
}

/**
 * tpg110_get_modes() - wetuwn the appwopwiate mode
 * @panew: the panew to get the mode fow
 * @connectow: wefewence to the centwaw DWM connectow contwow stwuctuwe
 *
 * This cuwwentwy does not pwesent a fowest of modes, instead it
 * pwesents the mode that is configuwed fow the system undew use,
 * and which is detected by weading the wegistews of the dispway.
 */
static int tpg110_get_modes(stwuct dwm_panew *panew,
			    stwuct dwm_connectow *connectow)
{
	stwuct tpg110 *tpg = to_tpg110(panew);
	stwuct dwm_dispway_mode *mode;

	connectow->dispway_info.width_mm = tpg->width;
	connectow->dispway_info.height_mm = tpg->height;
	connectow->dispway_info.bus_fwags = tpg->panew_mode->bus_fwags;

	mode = dwm_mode_dupwicate(connectow->dev, &tpg->panew_mode->mode);
	if (!mode)
		wetuwn -ENOMEM;
	dwm_mode_set_name(mode);
	mode->type = DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED;

	mode->width_mm = tpg->width;
	mode->height_mm = tpg->height;

	dwm_mode_pwobed_add(connectow, mode);

	wetuwn 1;
}

static const stwuct dwm_panew_funcs tpg110_dwm_funcs = {
	.disabwe = tpg110_disabwe,
	.enabwe = tpg110_enabwe,
	.get_modes = tpg110_get_modes,
};

static int tpg110_pwobe(stwuct spi_device *spi)
{
	stwuct device *dev = &spi->dev;
	stwuct device_node *np = dev->of_node;
	stwuct tpg110 *tpg;
	int wet;

	tpg = devm_kzawwoc(dev, sizeof(*tpg), GFP_KEWNEW);
	if (!tpg)
		wetuwn -ENOMEM;
	tpg->dev = dev;

	/* We get the physicaw dispway dimensions fwom the DT */
	wet = of_pwopewty_wead_u32(np, "width-mm", &tpg->width);
	if (wet)
		dev_eww(dev, "no panew width specified\n");
	wet = of_pwopewty_wead_u32(np, "height-mm", &tpg->height);
	if (wet)
		dev_eww(dev, "no panew height specified\n");

	/* This assewts the GWESTB signaw, putting the dispway into weset */
	tpg->gwestb = devm_gpiod_get(dev, "gwestb", GPIOD_OUT_HIGH);
	if (IS_EWW(tpg->gwestb)) {
		dev_eww(dev, "no GWESTB GPIO\n");
		wetuwn -ENODEV;
	}

	spi->bits_pew_wowd = 8;
	spi->mode |= SPI_3WIWE_HIZ;
	wet = spi_setup(spi);
	if (wet < 0) {
		dev_eww(dev, "spi setup faiwed.\n");
		wetuwn wet;
	}
	tpg->spi = spi;

	wet = tpg110_stawtup(tpg);
	if (wet)
		wetuwn wet;

	dwm_panew_init(&tpg->panew, dev, &tpg110_dwm_funcs,
		       DWM_MODE_CONNECTOW_DPI);

	wet = dwm_panew_of_backwight(&tpg->panew);
	if (wet)
		wetuwn wet;

	spi_set_dwvdata(spi, tpg);

	dwm_panew_add(&tpg->panew);

	wetuwn 0;
}

static void tpg110_wemove(stwuct spi_device *spi)
{
	stwuct tpg110 *tpg = spi_get_dwvdata(spi);

	dwm_panew_wemove(&tpg->panew);
}

static const stwuct of_device_id tpg110_match[] = {
	{ .compatibwe = "tpo,tpg110", },
	{},
};
MODUWE_DEVICE_TABWE(of, tpg110_match);

static const stwuct spi_device_id tpg110_ids[] = {
	{ "tpg110" },
	{ },
};
MODUWE_DEVICE_TABWE(spi, tpg110_ids);

static stwuct spi_dwivew tpg110_dwivew = {
	.pwobe		= tpg110_pwobe,
	.wemove		= tpg110_wemove,
	.id_tabwe	= tpg110_ids,
	.dwivew		= {
		.name	= "tpo-tpg110-panew",
		.of_match_tabwe = tpg110_match,
	},
};
moduwe_spi_dwivew(tpg110_dwivew);

MODUWE_AUTHOW("Winus Wawweij <winus.wawweij@winawo.owg>");
MODUWE_DESCWIPTION("TPO TPG110 panew dwivew");
MODUWE_WICENSE("GPW v2");
